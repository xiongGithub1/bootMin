#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ZxDocTest.py - UDS/DCM automated test for autosarTc364_Boot (2), ZXDoc native.

Runs inside ZXDoc (ZLG / 致远电子) Python script environment:
  - load in ZXDoc script editor and run;
  - the suite uses ZXDoc's own UDS interface (ZDoCanInterface),
    so python-can / CANoe are NOT required;
  - CAN IDs are from the project config:
      physical request 0x74C, response 0x75C, functional 0x7DF, 500 kbit/s.

Test matrix (same as Boot_Dcm_TestSpec.md):
  A1..A7  session control / session change
  B1..B8  SecurityAccess (L1/L3, wrong key, already unlocked)
  C1..C21 service permission matrix + negative response codes
  D1..D4  P2 latency, P2/P2* advertisement, S3 timeout, 3E keepalive
  E1..E9  flash programming flow + error paths (destructive, gated)
  F1..F3  ECU reset (gated)
  G1..G2  functional addressing (0x7DF)

Set RUN_FLASH / RUN_RESET to True before running if the destructive
flash and reset tests are required (E group erases the APP area!).
"""

from ZXDoc import *
import time

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------
CHANNEL_INDEX = 1          # ZXDoc channel where the ECU is connected
REQ_ADDR = 0x74C           # physical diagnostic request address
RSP_ADDR = 0x75C           # response address
FUNCT_ADDR = 0x7DF         # functional request address
APP_START = 0x80020000

RUN_FLASH = False          # True: run E1..E9 (erases APP area!)
RUN_RESET = False          # True: run F1..F3 (resets the ECU)

P2_LIMIT_S = 0.060         # D1 tolerance (P2 is 50 ms + margin)
S3_WAIT_S = 6.0            # D3 wait (> S3 = 5 s)

# ---------------------------------------------------------------------------
# UDS transport (ZXDoc API wrapper)
# ---------------------------------------------------------------------------
class Uds:
    def __init__(self):
        self.iface = ZDoCanInterface(
            channelIndex=CHANNEL_INDEX,
            cfg=ZUdsCANCfg(
                frameType=CAN_FRAME_TYPE_CAN,
                protocolVersion=CAN_TP_ISO15765_2_2016,
                fillByte=0xAA,
                isFillByte=True,
                p2Timeout=2000,
                p2xTimeout=5000,
                isReplaceEcuSTmin=False,
                remoteSTmin=0,
                localSTmin=0,
                blockSize=0,
                fcTimeout=1000,
            ),
        )
        self.handle = self.iface.handle()

    def ok(self):
        return self.handle >= 0

    def request(self, data, timeout_ms=2000, functional=False):
        """Send [sid, ...] and return (response, elapsed_seconds)."""
        sid = data[0]
        payload = list(data[1:])
        req = ZUdsRequest(
            src_addr=REQ_ADDR,          # request / flow-control address
            dst_addr=RSP_ADDR,          # response address
            is_extend=False,
            suppress_response=False,
            sid=sid,
            data=payload,
        )
        t0 = time.monotonic()
        if functional:
            rsp = self.iface.functional_request(FUNCT_ADDR, req, msTimeout=timeout_ms)
        else:
            rsp = self.iface.request(req, msTimeout=timeout_ms)
        return rsp, time.monotonic() - t0


def pos_bytes(rsp):
    """Full positive response bytes = [sid] + data (ZXDoc data excludes SID)."""
    return bytes([rsp.sid]) + bytes(rsp.data)


def is_pos(rsp):
    return rsp is not None and rsp.responseType == UDS_RSP_TYPE_POSITIVE


def is_neg(rsp):
    return rsp is not None and rsp.responseType == UDS_RSP_TYPE_NEGATIVE


def is_no_response(rsp):
    return not (is_pos(rsp) or is_neg(rsp))


# ---------------------------------------------------------------------------
# Test runner
# ---------------------------------------------------------------------------
class Runner:
    def __init__(self, uds):
        self.uds = uds
        self.results = []

    # ---- low level -----------------------------------------------------
    def request(self, data, timeout_ms=2000, functional=False):
        rsp, elapsed = self.uds.request(data, timeout_ms=timeout_ms, functional=functional)
        # CanTp is half-duplex: the next request can be dropped while 67 02 / 50 xx
        # is still confirming. ZXDoc returns as soon as the response is seen.
        time.sleep(0.02)
        return rsp, elapsed

    def expect(self, data, expected, timeout_ms=2000, functional=False):
        rsp, elapsed = self.request(data, timeout_ms=timeout_ms, functional=functional)
        return (is_pos(rsp) and pos_bytes(rsp) == bytes(expected)), rsp, elapsed

    def expect_neg(self, data, sid, nrc, timeout_ms=2000, functional=False):
        rsp, elapsed = self.request(data, timeout_ms=timeout_ms, functional=functional)
        return (is_neg(rsp) and rsp.NRC == nrc), rsp, elapsed

    def expect_no_response(self, data, timeout_ms=3000, functional=False):
        rsp, elapsed = self.request(data, timeout_ms=timeout_ms, functional=functional)
        return is_no_response(rsp), rsp, elapsed

    def to_default(self):
        self.request([0x10, 0x01], timeout_ms=1000)
        time.sleep(0.1)

    def enter(self, session):
        rsp, _ = self.request([0x10, session])
        return is_pos(rsp) and pos_bytes(rsp)[:2] == bytes([0x50, session])

    def unlock(self, level):
        """Unlock SecurityAccess level 1 or 3 (key = bitwise NOT of seed)."""
        seed_sf = 0x01 if level == 1 else 0x03
        key_sf = 0x02 if level == 1 else 0x04
        rsp, _ = self.request([0x27, seed_sf])
        if not is_pos(rsp) or rsp.sid != 0x67:
            return False
        seed_data = list(rsp.data)           # [sub-function, s0, s1, s2, s3]
        if len(seed_data) != 5:
            return False
        seed = (seed_data[1] << 24) | (seed_data[2] << 16) | (seed_data[3] << 8) | seed_data[4]
        key = (~seed) & 0xFFFFFFFF
        rsp2, _ = self.request([0x27, key_sf, (key >> 24) & 0xFF, (key >> 16) & 0xFF,
                                (key >> 8) & 0xFF, key & 0xFF])
        return is_pos(rsp2) and rsp2.sid == 0x67

    def prog_erased(self):
        """Enter programming, unlock L1 and erase the whole APP area."""
        if not self.enter(0x02):
            return False
        if not self.unlock(1):
            return False
        rsp, _ = self.request([0x31, 0x01, 0xFF, 0x00], timeout_ms=10000)
        return is_pos(rsp) and pos_bytes(rsp) == bytes([0x71, 0x01, 0xFF, 0x00])

    def start_download(self, size=0x20, addr=APP_START):
        req = [0x34, 0x00, 0x44]
        req += [(addr >> 24) & 0xFF, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, addr & 0xFF]
        req += [(size >> 24) & 0xFF, (size >> 16) & 0xFF, (size >> 8) & 0xFF, size & 0xFF]
        rsp, _ = self.request(req)
        return rsp

    @staticmethod
    def download_req(addr, size):
        req = [0x34, 0x00, 0x44]
        req += [(addr >> 24) & 0xFF, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, addr & 0xFF]
        req += [(size >> 24) & 0xFF, (size >> 16) & 0xFF, (size >> 8) & 0xFF, size & 0xFF]
        return req

    # ---- case execution ------------------------------------------------
    def run_one(self, group, tc_id, name, fn):
        try:
            ok, detail = fn(self)
        except Exception as exc:
            ok, detail = False, "exception: %r" % (exc,)
        finally:
            if group != "reset":
                self.to_default()
        self.results.append((group, tc_id, name, ok, detail))
        mark = "PASS" if ok else "FAIL"
        print("[%s] [%s] %-4s %-52s %s" % (mark, group, tc_id, name, detail))

    def summary(self):
        total = len(self.results)
        passed = sum(1 for r in self.results if r[3])
        print("\n" + "=" * 72)
        print("SUMMARY: %d/%d passed" % (passed, total))
        for group, tc_id, name, ok, detail in self.results:
            if not ok:
                print("  FAIL %-4s %-52s %s" % (tc_id, name, detail))
        print("=" * 72)
        app.log_i("ZXDoc UDS test: %d/%d passed" % (passed, total))
        return passed == total


# ---------------------------------------------------------------------------
# Test cases
# ---------------------------------------------------------------------------
def build_cases():
    cases = []

    def case(group, tc_id, name, fn, requires=None):
        cases.append((group, tc_id, name, fn, requires))

    # ---- A. session control ----
    def a1(r):
        ok, rsp, el = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s (%.1f ms)" % (pos_bytes(rsp) if is_pos(rsp) else rsp, el * 1000)
    case("session", "A1", "10 01 default (P2/P2* advertisement)", a1)

    def a2(r):
        ok, rsp, _ = r.expect([0x10, 0x02], [0x50, 0x02, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("session", "A2", "10 02 enter programming", a2)

    def a3(r):
        ok, rsp, _ = r.expect([0x10, 0x03], [0x50, 0x03, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("session", "A3", "10 03 enter extended", a3)

    def a4(r):
        ok, rsp, _ = r.expect_neg([0x10, 0x04], 0x10, 0x12)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("session", "A4", "10 04 invalid sub-function -> SFNS", a4)

    def a5(r):
        ok, rsp, _ = r.expect_no_response([0x10, 0x81])
        return ok, "resp=%s" % (rsp,)
    case("session", "A5", "10 81 suppressPosRsp -> no response", a5)

    def a6(r):
        ok, rsp, _ = r.expect_neg([0x10], 0x10, 0x13)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("session", "A6", "10 (len 1) -> IMLOIF", a6)

    def a7(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        if not r.enter(0x01):
            return False, "cannot return to default"
        if not r.enter(0x02):
            return False, "cannot re-enter programming"
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x33)
        return ok, "nrc=%s (security must be locked after session change)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("session", "A7", "session change locks SecurityAccess", a7)

    # ---- B. security access ----
    def b1(r):
        ok, rsp, _ = r.expect_neg([0x27, 0x01], 0x27, 0x7F)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("security", "B1", "27 01 in default -> SNSIAS", b1)

    def b2(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        rsp, _ = r.request([0x27, 0x01])
        ok = is_pos(rsp) and rsp.sid == 0x67 and len(rsp.data) == 5
        return ok, "resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("security", "B2", "27 01 seed request in programming", b2)

    def b3(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        rsp, _ = r.request([0x27, 0x01])
        if not is_pos(rsp) or len(rsp.data) != 5:
            return False, "no seed: %s" % (rsp,)
        d = list(rsp.data)
        seed = (d[1] << 24) | (d[2] << 16) | (d[3] << 8) | d[4]
        wrong = ((~seed) & 0xFFFFFFFF) ^ 0x55
        ok, rsp, _ = r.expect_neg([0x27, 0x02, (wrong >> 24) & 0xFF, (wrong >> 16) & 0xFF,
                                   (wrong >> 8) & 0xFF, wrong & 0xFF], 0x27, 0x35)
        if not ok:
            return False, "wrong key NRC=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
        ok2, rsp2, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x33)
        return ok2, "locked after bad key, 34 nrc=%s" % (rsp2.NRC if is_neg(rsp2) else rsp2,)
    case("security", "B3", "27 02 wrong key -> IK and stays locked", b3)

    def b4(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x22)
        return ok, "nrc=%s (past security gate, not erased -> CNC)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("security", "B4", "27 02 correct key unlocks security", b4)

    def b5(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect([0x27, 0x01], [0x67, 0x01, 0x00, 0x00, 0x00, 0x00])
        return ok, "resp=%s (already unlocked -> zero seed)" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("security", "B5", "27 01 when already unlocked -> zero seed", b5)

    def b6(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        ok, rsp, _ = r.expect_neg([0x27, 0x02, 0xAA, 0xBB, 0xCC, 0xDD], 0x27, 0x24)
        return ok, "nrc=%s (key without seed -> RSE)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("security", "B6", "27 02 key without seed -> RSE", b6)

    def b7(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        ok, rsp, _ = r.expect_neg([0x27, 0x05], 0x27, 0x12)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("security", "B7", "27 05 invalid sub-function -> SFNS", b7)

    def b8(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(3):
            return False, "L3 unlock failed"
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x33)
        return ok, "nrc=%s (L3 must not open L1 services)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("security", "B8", "L3 unlock does not grant L1 services", b8)

    # ---- C. permission matrix / negative codes ----
    def c1(r):
        ok, rsp, _ = r.expect([0x22, 0xF1, 0x80], [0x62, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54])
        return ok, "resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("matrix", "C1", "22 F180 read boot software", c1)

    def c2(r):
        ok, rsp, _ = r.expect_neg([0x22, 0xF2, 0x00], 0x22, 0x31)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C2", "22 invalid DID -> ROOR", c2)

    def c3(r):
        ok, rsp, _ = r.expect_neg([0x22, 0xF1], 0x22, 0x13)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C3", "22 wrong length -> IMLOIF", c3)

    def c4(r):
        ok, rsp, _ = r.expect_neg([0x2E, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD], 0x2E, 0x7F)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C4", "2E in default -> SNSIAS", c4)

    def c5(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        ok, rsp, _ = r.expect_neg([0x2E, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD], 0x2E, 0x33)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C5", "2E in extended locked -> SAD", c5)

    def c6(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect([0x2E, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD], [0x6E, 0xF1, 0x80])
        if not ok:
            return False, "write resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        ok2, rsp2, _ = r.expect([0x22, 0xF1, 0x80], [0x62, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD])
        # restore the original F180 content so later cases (D1/G2) stay order-independent
        r.expect([0x2E, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54], [0x6E, 0xF1, 0x80])
        return ok2, "write ok, read-back=%s" % (pos_bytes(rsp2) if is_pos(rsp2) else rsp2,)
    case("matrix", "C6", "2E/22 write-readback in extended with L1", c6)

    def c7(r):
        ok, rsp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x01], 0x31, 0x7F)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C7", "31 in default -> SNSIAS", c7)

    def c8(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        ok, rsp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x01], 0x31, 0x33)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C8", "31 in programming locked -> SAD", c8)

    def c9(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x01], 0x31, 0x22)
        return ok, "nrc=%s (check dep before program -> CNC)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C9", "31 FF01 before programming -> CNC", c9)

    def c10(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg([0x31, 0x02, 0xFF, 0x01], 0x31, 0x12)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C10", "31 SF=stop -> SFNS", c10)

    def c11(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x99], 0x31, 0x31)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C11", "31 invalid RID -> ROOR", c11)

    def c12(r):
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x7F)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C12", "34 in default -> SNSIAS", c12)

    def c13(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x7F)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C13", "34 in extended -> SNSIAS", c13)

    def c14(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x33)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C14", "34 in programming locked -> SAD", c14)

    def c15(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x22)
        return ok, "nrc=%s (not erased -> CNC)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C15", "34 before erase -> CNC", c15)

    def c16(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg([0x36, 0x01] + [0xAA] * 32, 0x36, 0x24)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C16", "36 before RequestDownload -> RSE", c16)

    def c17(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg([0x37], 0x37, 0x24)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C17", "37 before RequestDownload -> RSE", c17)

    def c18(r):
        ok, rsp, _ = r.expect([0x3E, 0x00], [0x7E, 0x00])
        return ok, "resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("matrix", "C18", "3E 00 tester present", c18)

    def c19(r):
        ok, rsp, _ = r.expect_no_response([0x3E, 0x80])
        return ok, "resp=%s" % (rsp,)
    case("matrix", "C19", "3E 80 suppress -> no response", c19)

    def c20(r):
        ok, rsp, _ = r.expect_neg([0x3E, 0x01], 0x3E, 0x12)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C20", "3E invalid sub-function -> SFNS", c20)

    def c21(r):
        ok, rsp, _ = r.expect_neg([0x99, 0x00], 0x99, 0x11)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("matrix", "C21", "unknown SID -> SNS", c21)

    # ---- D. timing ----
    def d1(r):
        rsp, elapsed = r.request([0x22, 0xF1, 0x80])
        ok = is_pos(rsp) and pos_bytes(rsp) == bytes([0x62, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54]) \
            and elapsed < P2_LIMIT_S
        return ok, "latency=%.1f ms (limit %.0f ms)" % (elapsed * 1000, P2_LIMIT_S * 1000)
    case("timing", "D1", "P2: response latency < 50 ms", d1)

    def d2(r):
        ok, rsp, _ = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s (P2=50ms P2*=5000ms)" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("timing", "D2", "0x10 advertises P2/P2* values", d2)

    def d3(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        time.sleep(S3_WAIT_S)
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START, 0x20), 0x34, 0x7F)
        return ok, "nrc=%s (back to default session after S3)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("timing", "D3", "S3 timeout returns to default session", d3)

    def d4(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        for _ in range(4):
            ok, rsp, _ = r.expect([0x3E, 0x00], [0x7E, 0x00])
            if not ok:
                return False, "3E keepalive failed: %s" % (rsp,)
            time.sleep(1.0)
        rsp, _ = r.request([0x27, 0x01])
        ok = is_pos(rsp) and rsp.sid == 0x67 and len(rsp.data) == 5
        return ok, "resp=%s (still in extended, S3 kept alive)" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("timing", "D4", "3E keepalive prevents S3 expiry", d4)

    # ---- E. flash programming (destructive) ----
    def e1(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect([0x31, 0x01, 0xFF, 0x00], [0x71, 0x01, 0xFF, 0x00], timeout_ms=10000)
        if not ok:
            return False, "erase resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        ok, rsp, _ = r.expect(r.download_req(APP_START, 0x20), [0x74, 0x20, 0x02, 0x00])
        if not ok:
            return False, "requestDownload resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        ok, rsp, _ = r.expect([0x36, 0x01] + list(range(32)), [0x76, 0x01])
        if not ok:
            return False, "transferData resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        ok, rsp, _ = r.expect([0x37], [0x77])
        if not ok:
            return False, "transferExit resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        ok, rsp, _ = r.expect([0x31, 0x01, 0xFF, 0x02], [0x71, 0x01, 0xFF, 0x02])
        if not ok:
            return False, "checkMemory resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        ok, rsp, _ = r.expect([0x31, 0x01, 0xFF, 0x01], [0x71, 0x01, 0xFF, 0x01, 0x00])
        return ok, "full flow OK, checkDependency resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("flash", "E1", "full download flow (erase/RD/TD/RTE/check)", e1, requires="flash")

    def e2(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        rsp = r.start_download()
        if not is_pos(rsp) or pos_bytes(rsp) != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (rsp,)
        ok, rsp, _ = r.expect_neg([0x36, 0x02] + list(range(32)), 0x36, 0x73)
        return ok, "nrc=%s (wrong block sequence counter)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E2", "36 wrong block counter -> WBSC", e2, requires="flash")

    def e3(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        rsp = r.start_download()
        if not is_pos(rsp) or pos_bytes(rsp) != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (rsp,)
        ok, rsp, _ = r.expect_neg([0x36, 0x01] + list(range(40)), 0x36, 0x31)
        return ok, "nrc=%s (block exceeds remaining size)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E3", "36 block larger than download size -> ROOR", e3, requires="flash")

    def e4(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        rsp = r.start_download()
        if not is_pos(rsp) or pos_bytes(rsp) != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (rsp,)
        ok, rsp, _ = r.expect_neg([0x36, 0x01, 0xAA, 0xBB, 0xCC], 0x36, 0x31)
        return ok, "nrc=%s (unaligned block)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E4", "36 unaligned block -> ROOR", e4, requires="flash")

    def e5(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        ok, rsp, _ = r.expect_neg(r.download_req(0x80000000, 0x20), 0x34, 0x31)
        return ok, "nrc=%s (boot area address)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E5", "34 address in boot area -> ROOR", e5, requires="flash")

    def e6(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        ok, rsp, _ = r.expect_neg(r.download_req(APP_START + 1, 0x20), 0x34, 0x31)
        return ok, "nrc=%s (unaligned address)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E6", "34 unaligned address -> ROOR", e6, requires="flash")

    def e7(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        rsp = r.start_download()
        if not is_pos(rsp) or pos_bytes(rsp) != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (rsp,)
        ok, rsp, _ = r.expect_neg([0x37], 0x37, 0x22)
        return ok, "nrc=%s (exit before all data received)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E7", "37 before download complete -> CNC", e7, requires="flash")

    def e8(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        rsp = r.start_download()
        if not is_pos(rsp) or pos_bytes(rsp) != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (rsp,)
        if not r.enter(0x01):
            return False, "cannot return to default"
        if not r.enter(0x02):
            return False, "cannot re-enter programming"
        ok, rsp, _ = r.expect_neg([0x36, 0x01] + list(range(32)), 0x36, 0x33)
        return ok, "nrc=%s (session change locked security and reset state)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E8", "session change mid-download -> locked", e8, requires="flash")

    def e9(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, rsp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x00, 0x00], 0x31, 0x13)
        return ok, "nrc=%s (erase with wrong length)" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("flash", "E9", "31 erase wrong length -> IMLOIF", e9, requires="flash")

    # ---- F. ECU reset (optional) ----
    def f1(r):
        ok, rsp, _ = r.expect([0x11, 0x01], [0x51, 0x01], timeout_ms=3000)
        if not ok:
            return False, "hardReset resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        time.sleep(3.0)
        ok2, rsp2, _ = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4], timeout_ms=4000)
        return ok2, "reset ack ok, re-init resp=%s" % (pos_bytes(rsp2) if is_pos(rsp2) else rsp2,)
    case("reset", "F1", "11 01 hardReset + ECU comes back", f1, requires="reset")

    def f2(r):
        ok, rsp, _ = r.expect([0x11, 0x03], [0x51, 0x03], timeout_ms=3000)
        if not ok:
            return False, "softReset resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
        time.sleep(2.0)
        ok2, rsp2, _ = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4], timeout_ms=4000)
        return ok2, "reset ack ok, re-init resp=%s" % (pos_bytes(rsp2) if is_pos(rsp2) else rsp2,)
    case("reset", "F2", "11 03 softReset + ECU comes back", f2, requires="reset")

    def f3(r):
        ok, rsp, _ = r.expect_neg([0x11, 0x02], 0x11, 0x12)
        return ok, "nrc=%s" % (rsp.NRC if is_neg(rsp) else rsp,)
    case("reset", "F3", "11 02 invalid sub-function -> SFNS", f3, requires="reset")

    # ---- G. functional addressing ----
    def g1(r):
        ok, rsp, _ = r.expect([0x3E, 0x00], [0x7E, 0x00], functional=True)
        return ok, "resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("functional", "G1", "functional 3E 00 via 0x7DF", g1)

    def g2(r):
        ok, rsp, _ = r.expect([0x22, 0xF1, 0x80], [0x62, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54],
                              functional=True)
        return ok, "resp=%s" % (pos_bytes(rsp) if is_pos(rsp) else rsp,)
    case("functional", "G2", "functional 22 F180 via 0x7DF", g2)

    return cases


# ---------------------------------------------------------------------------
# ZXDoc entry points
# ---------------------------------------------------------------------------
def __zxdoc_init__():
    pass


def __zxdoc_main__():
    if not measurement.is_started():
        measurement.start()

    uds = Uds()
    if not uds.ok():
        app.log_e("ZDoCanInterface: failed to create (check channel %d and device)" % CHANNEL_INDEX)
        measurement.stop()
        return

    app.log_i("ZXDoc UDS test started (req=0x%03X rsp=0x%03X funct=0x%03X)"
              % (REQ_ADDR, RSP_ADDR, FUNCT_ADDR))

    runner = Runner(uds)
    cases = build_cases()

    for group, tc_id, name, fn, requires in cases:
        if requires == "flash" and not RUN_FLASH:
            continue
        if requires == "reset" and not RUN_RESET:
            continue
        runner.run_one(group, tc_id, name, fn)

    runner.summary()
    measurement.stop()


def __zxdoc_on_exit__():
    if measurement.is_started():
        measurement.stop()
