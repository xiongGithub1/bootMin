#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Boot_Dcm_UdsTest.py - Automated UDS/DCM test runner for autosarTc364_Boot (2).

The test drives the ECU through a CAN interface and checks the table-driven
mini-DCM behaviour: session control, SecurityAccess, the service/session/security
permission matrix, P2/P2*/S3 timings, negative response codes, the full flash
programming sequence and ECU reset.

Dependencies:
    pip install python-can
    (plus the driver for your CAN hardware, e.g. PCAN-Basic, Vector XL)

Usage:
    python Boot_Dcm_UdsTest.py --interface pcan --channel PCAN_USBBUS1 --bitrate 500000
    python Boot_Dcm_UdsTest.py --interface vector --channel 0 --bitrate 500000
    python Boot_Dcm_UdsTest.py --list
    python Boot_Dcm_UdsTest.py --group session --group security --group matrix
    python Boot_Dcm_UdsTest.py --flash-test --reset-test        # destructive: erases APP

Default diagnostic IDs come from the project configuration:
    request (physical) 0x74C, response 0x75C, functional 0x7DF, 500 kbit/s.
"""

import argparse
import sys
import time

try:
    import can
except ImportError:
    print("python-can is not installed. Run:  pip install python-can")
    sys.exit(2)


# ---------------------------------------------------------------------------
# Configuration defaults (match the project)
# ---------------------------------------------------------------------------
DEFAULT_INTERFACE = "pcan"
DEFAULT_CHANNEL = "PCAN_USBBUS1"
DEFAULT_BITRATE = 500000
DEFAULT_REQ_ID = 0x74C
DEFAULT_RESP_ID = 0x75C
DEFAULT_FUNCT_ID = 0x7DF

P2_SERVER_S = 0.050
P2STAR_SERVER_S = 5.000
S3_SERVER_S = 5.000

APP_START = 0x80020000


# ---------------------------------------------------------------------------
# Minimal ISO-TP (single frame + first/consecutive + flow control)
# ---------------------------------------------------------------------------
class IsoTp:
    """Enough ISO-TP for the UDS test traffic (tester side)."""

    def __init__(self, bus, req_id, resp_id, funct_id):
        self.bus = bus
        self.req_id = req_id
        self.resp_id = resp_id
        self.funct_id = funct_id

    def _send_frame(self, arb_id, data):
        msg = can.Message(arbitration_id=arb_id, data=data, is_extended_id=False, is_fd=False)
        self.bus.send(msg)

    def _recv_frame(self, arb_id, timeout):
        deadline = time.monotonic() + timeout
        while True:
            remain = deadline - time.monotonic()
            if remain <= 0.0:
                return None
            msg = self.bus.recv(remain)
            if msg is None:
                return None
            if msg.arbitration_id == arb_id:
                return bytes(msg.data)

    def send(self, data, tx_id=None):
        tx_id = self.req_id if tx_id is None else tx_id
        data = bytes(data)
        n = len(data)

        if n <= 7:  # single frame
            self._send_frame(tx_id, bytes([n]) + data)
            return

        # first frame
        ff = bytes([0x10 | ((n >> 8) & 0x0F), n & 0xFF]) + data[:6]
        self._send_frame(tx_id, ff)

        # wait for flow control (ECU is the receiver of our request)
        fc = self._recv_frame(self.resp_id, 2.0)
        if fc is None or (fc[0] & 0xF0) != 0x30:
            raise RuntimeError("ISO-TP: no flow control for request")

        stmin = fc[2] & 0x7F if len(fc) > 2 else 0
        off = 6
        seq = 1
        while off < n:
            chunk = data[off:off + 7]
            self._send_frame(tx_id, bytes([0x20 | (seq & 0x0F)]) + chunk)
            # the ECU processes one consecutive frame per CanTp main cycle
            time.sleep(max(stmin / 1000.0, 0.002))
            seq += 1
            off += 7

    def recv(self, timeout=2.0):
        start = time.monotonic()
        frame = self._recv_frame(self.resp_id, timeout)
        if frame is None:
            return None, time.monotonic() - start

        pci = frame[0]
        if pci <= 0x0F:  # single frame
            ln = pci
            return bytes(frame[1:1 + ln]), time.monotonic() - start

        if (pci & 0xF0) == 0x10:  # first frame -> receive consecutive frames
            total = ((pci & 0x0F) << 8) | frame[1]
            buf = bytearray(frame[2:8])
            self._send_frame(self.req_id, bytes([0x30, 0x00, 0x00]))  # CTS, BS=0
            while len(buf) < total:
                remain = timeout - (time.monotonic() - start)
                if remain <= 0.0:
                    return None, time.monotonic() - start
                fr = self._recv_frame(self.resp_id, remain)
                if fr is None:
                    return None, time.monotonic() - start
                if (fr[0] & 0xF0) == 0x20:
                    buf.extend(fr[1:])
            return bytes(buf[:total]), time.monotonic() - start

        return None, time.monotonic() - start

    def request(self, data, timeout=2.0, tx_id=None):
        start = time.monotonic()
        self.send(data, tx_id=tx_id)
        resp, _ = self.recv(timeout)
        return resp, time.monotonic() - start


# ---------------------------------------------------------------------------
# Test runner
# ---------------------------------------------------------------------------
class TestRunner:
    def __init__(self, args):
        self.args = args
        self.bus = can.Bus(interface=args.interface, channel=args.channel, bitrate=args.bitrate)
        self.tp = IsoTp(self.bus, args.req_id, args.resp_id, args.funct_id)
        self.results = []

    # ---------- low level helpers -----------------------------------------
    def request(self, data, timeout=2.0, tx_id=None):
        return self.tp.request(data, timeout=timeout, tx_id=tx_id)

    def expect(self, data, expected, timeout=2.0, tx_id=None):
        resp, elapsed = self.request(data, timeout=timeout, tx_id=tx_id)
        return (resp == bytes(expected)), resp, elapsed

    def expect_neg(self, data, sid, nrc, timeout=2.0, tx_id=None):
        resp, elapsed = self.request(data, timeout=timeout, tx_id=tx_id)
        return (resp == bytes([0x7F, sid, nrc])), resp, elapsed

    def expect_no_response(self, data, timeout=0.5, tx_id=None):
        resp, elapsed = self.request(data, timeout=timeout, tx_id=tx_id)
        return (resp is None), resp, elapsed

    def to_default(self):
        try:
            self.tp.request(bytes([0x10, 0x01]), timeout=1.0)
        except Exception:
            pass
        time.sleep(0.1)

    def enter(self, session):
        resp, _ = self.tp.request(bytes([0x10, session]), timeout=2.0)
        return resp is not None and resp[:2] == bytes([0x50, session])

    def unlock(self, level):
        """Unlock SecurityAccess level 1 or 3 (key = bitwise NOT of seed)."""
        seed_sf = 0x01 if level == 1 else 0x03
        key_sf = 0x02 if level == 1 else 0x04
        resp, _ = self.tp.request(bytes([0x27, seed_sf]), timeout=2.0)
        if resp is None or len(resp) != 6 or resp[0] != 0x67 or resp[1] != seed_sf:
            return False
        seed = int.from_bytes(resp[2:6], "big")
        key = (~seed) & 0xFFFFFFFF
        resp2, _ = self.tp.request(bytes([0x27, key_sf]) + key.to_bytes(4, "big"), timeout=2.0)
        return resp2 == bytes([0x67, key_sf])

    def prog_erased(self):
        """Enter programming session, unlock L1 and erase the whole APP area."""
        if not self.enter(0x02):
            return False
        if not self.unlock(1):
            return False
        resp, _ = self.tp.request(bytes([0x31, 0x01, 0xFF, 0x00]), timeout=10.0)
        return resp == bytes([0x71, 0x01, 0xFF, 0x00])

    def start_download(self, size=0x20, addr=APP_START):
        req = bytes([0x34, 0x00, 0x44]) + addr.to_bytes(4, "big") + size.to_bytes(4, "big")
        resp, _ = self.tp.request(req, timeout=2.0)
        return resp

    # ---------- case execution --------------------------------------------
    def run_one(self, group, tc_id, name, fn):
        try:
            ok, detail = fn(self)
        except Exception as exc:  # noqa: BLE001 - test harness must not die
            ok, detail = False, "exception: %r" % (exc,)
        finally:
            if group != "reset":
                self.to_default()

        self.results.append((group, tc_id, name, ok, detail))
        mark = "PASS" if ok else "FAIL"
        print("[%s] [%s] %-4s %-52s %s" % (mark, group, tc_id, name, detail))
        return ok

    def summary(self):
        total = len(self.results)
        passed = sum(1 for r in self.results if r[3])
        print("\n" + "=" * 72)
        print("SUMMARY: %d/%d passed" % (passed, total))
        for group, tc_id, name, ok, detail in self.results:
            if not ok:
                print("  FAIL %-4s %-52s %s" % (tc_id, name, detail))
        print("=" * 72)
        return passed == total


# ---------------------------------------------------------------------------
# Test cases
# ---------------------------------------------------------------------------
def build_cases():
    cases = []

    def case(group, tc_id, name, fn, requires=None):
        cases.append((group, tc_id, name, fn, requires))

    # ---------------- A. session control ----------------------------------
    def a1(r):
        ok, resp, el = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s (%.1f ms)" % (resp, el * 1000)
    case("session", "A1", "10 01 default (P2/P2* advertisement)", a1)

    def a2(r):
        ok, resp, _ = r.expect([0x10, 0x02], [0x50, 0x02, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s" % (resp,)
    case("session", "A2", "10 02 enter programming", a2)

    def a3(r):
        ok, resp, _ = r.expect([0x10, 0x03], [0x50, 0x03, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s" % (resp,)
    case("session", "A3", "10 03 enter extended", a3)

    def a4(r):
        ok, resp, _ = r.expect_neg([0x10, 0x04], 0x10, 0x12)
        return ok, "resp=%s" % (resp,)
    case("session", "A4", "10 04 invalid sub-function -> SFNS", a4)

    def a5(r):
        ok, resp, _ = r.expect_no_response([0x10, 0x81])
        return ok, "resp=%s" % (resp,)
    case("session", "A5", "10 81 suppressPosRsp -> no response", a5)

    def a6(r):
        ok, resp, _ = r.expect_neg([0x10], 0x10, 0x13)
        return ok, "resp=%s" % (resp,)
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
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x33)
        return ok, "resp=%s (security must be locked after session change)" % (resp,)
    case("session", "A7", "session change locks SecurityAccess", a7)

    # ---------------- B. security access ----------------------------------
    def b1(r):
        ok, resp, _ = r.expect_neg([0x27, 0x01], 0x27, 0x7F)
        return ok, "resp=%s" % (resp,)
    case("security", "B1", "27 01 in default -> SNSIAS", b1)

    def b2(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        resp, _ = r.request([0x27, 0x01])
        ok = resp is not None and len(resp) == 6 and resp[:2] == bytes([0x67, 0x01])
        return ok, "resp=%s" % (resp,)
    case("security", "B2", "27 01 seed request in programming", b2)

    def b3(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        resp, _ = r.request([0x27, 0x01])
        if resp is None or len(resp) != 6:
            return False, "no seed: %s" % (resp,)
        seed = int.from_bytes(resp[2:6], "big")
        wrong = ((~seed) & 0xFFFFFFFF) ^ 0x55
        ok, resp, _ = r.expect_neg([0x27, 0x02] + wrong.to_bytes(4, "big"), 0x27, 0x35)
        if not ok:
            return False, "wrong key NRC=%s" % (resp,)
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok2, resp2, _ = r.expect_neg(req, 0x34, 0x33)
        return ok2, "locked after bad key, 34->%s" % (resp2,)
    case("security", "B3", "27 02 wrong key -> IK and stays locked", b3)

    def b4(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x22)
        return ok, "resp=%s (past security gate, not erased -> CNC)" % (resp,)
    case("security", "B4", "27 02 correct key unlocks security", b4)

    def b5(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect([0x27, 0x01], [0x67, 0x01, 0x00, 0x00, 0x00, 0x00])
        return ok, "resp=%s (already unlocked -> zero seed)" % (resp,)
    case("security", "B5", "27 01 when already unlocked -> zero seed", b5)

    def b6(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        ok, resp, _ = r.expect_neg([0x27, 0x02, 0xAA, 0xBB, 0xCC, 0xDD], 0x27, 0x24)
        return ok, "resp=%s (key without seed -> RSE)" % (resp,)
    case("security", "B6", "27 02 key without seed -> RSE", b6)

    def b7(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        ok, resp, _ = r.expect_neg([0x27, 0x05], 0x27, 0x12)
        return ok, "resp=%s" % (resp,)
    case("security", "B7", "27 05 invalid sub-function -> SFNS", b7)

    def b8(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(3):
            return False, "L3 unlock failed"
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x33)
        return ok, "resp=%s (L3 must not open L1 services)" % (resp,)
    case("security", "B8", "L3 unlock does not grant L1 services", b8)

    # ---------------- C. permission matrix / negative codes ----------------
    def c1(r):
        ok, resp, _ = r.expect([0x22, 0xF1, 0x80], [0x62, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54])
        return ok, "resp=%s" % (resp,)
    case("matrix", "C1", "22 F180 read boot software", c1)

    def c2(r):
        ok, resp, _ = r.expect_neg([0x22, 0xF2, 0x00], 0x22, 0x31)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C2", "22 invalid DID -> ROOR", c2)

    def c3(r):
        ok, resp, _ = r.expect_neg([0x22, 0xF1], 0x22, 0x13)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C3", "22 wrong length -> IMLOIF", c3)

    def c4(r):
        ok, resp, _ = r.expect_neg([0x2E, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD], 0x2E, 0x7F)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C4", "2E in default -> SNSIAS", c4)

    def c5(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        ok, resp, _ = r.expect_neg([0x2E, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD], 0x2E, 0x33)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C5", "2E in extended locked -> SAD", c5)

    def c6(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect([0x2E, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD], [0x6E, 0xF1, 0x80])
        if not ok:
            return False, "write resp=%s" % (resp,)
        ok2, resp2, _ = r.expect([0x22, 0xF1, 0x80], [0x62, 0xF1, 0x80, 0x01, 0xAA, 0xBB, 0xCC, 0xDD])
        # restore the original F180 content so later cases (D1/G2) stay order-independent
        r.expect([0x2E, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54], [0x6E, 0xF1, 0x80])
        return ok2, "write ok, read-back=%s" % (resp2,)
    case("matrix", "C6", "2E/22 write-readback in extended with L1", c6)

    def c7(r):
        ok, resp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x01], 0x31, 0x7F)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C7", "31 in default -> SNSIAS", c7)

    def c8(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        ok, resp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x01], 0x31, 0x33)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C8", "31 in programming locked -> SAD", c8)

    def c9(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x01], 0x31, 0x22)
        return ok, "resp=%s (check dep before program -> CNC)" % (resp,)
    case("matrix", "C9", "31 FF01 before programming -> CNC", c9)

    def c10(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect_neg([0x31, 0x02, 0xFF, 0x01], 0x31, 0x12)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C10", "31 SF=stop -> SFNS", c10)

    def c11(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x99], 0x31, 0x31)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C11", "31 invalid RID -> ROOR", c11)

    def c12(r):
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x7F)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C12", "34 in default -> SNSIAS", c12)

    def c13(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        if not r.unlock(1):
            return False, "unlock failed"
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x7F)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C13", "34 in extended -> SNSIAS", c13)

    def c14(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x33)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C14", "34 in programming locked -> SAD", c14)

    def c15(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x22)
        return ok, "resp=%s (not erased -> CNC)" % (resp,)
    case("matrix", "C15", "34 before erase -> CNC", c15)

    def c16(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect_neg([0x36, 0x01] + [0xAA] * 32, 0x36, 0x24)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C16", "36 before RequestDownload -> RSE", c16)

    def c17(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect_neg([0x37], 0x37, 0x24)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C17", "37 before RequestDownload -> RSE", c17)

    def c18(r):
        ok, resp, _ = r.expect([0x3E, 0x00], [0x7E, 0x00])
        return ok, "resp=%s" % (resp,)
    case("matrix", "C18", "3E 00 tester present", c18)

    def c19(r):
        ok, resp, _ = r.expect_no_response([0x3E, 0x80])
        return ok, "resp=%s" % (resp,)
    case("matrix", "C19", "3E 80 suppress -> no response", c19)

    def c20(r):
        ok, resp, _ = r.expect_neg([0x3E, 0x01], 0x3E, 0x12)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C20", "3E invalid sub-function -> SFNS", c20)

    def c21(r):
        ok, resp, _ = r.expect_neg([0x99, 0x00], 0x99, 0x11)
        return ok, "resp=%s" % (resp,)
    case("matrix", "C21", "unknown SID -> SNS", c21)

    # ---------------- D. timing --------------------------------------------
    def d1(r):
        resp, elapsed = r.request([0x22, 0xF1, 0x80])
        ok = resp == bytes([0x62, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54]) and elapsed < (P2_SERVER_S + 0.010)
        return ok, "latency=%.1f ms (limit %.0f ms)" % (elapsed * 1000, (P2_SERVER_S + 0.010) * 1000)
    case("timing", "D1", "P2: response latency < 50 ms", d1)

    def d2(r):
        ok, resp, _ = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4])
        return ok, "resp=%s (P2=50ms P2*=5000ms)" % (resp,)
    case("timing", "D2", "0x10 advertises P2/P2* values", d2)

    def d3(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        time.sleep(S3_SERVER_S + 1.0)  # wait until S3 expires
        req = bytes([0x34, 0x00, 0x44]) + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x7F)
        return ok, "resp=%s (back to default session after S3)" % (resp,)
    case("timing", "D3", "S3 timeout returns to default session", d3)

    def d4(r):
        if not r.enter(0x03):
            return False, "cannot enter extended"
        for _ in range(4):
            ok, resp, _ = r.expect([0x3E, 0x00], [0x7E, 0x00])
            if not ok:
                return False, "3E keepalive failed: %s" % (resp,)
            time.sleep(1.0)
        resp, _ = r.request([0x27, 0x01])
        ok = resp is not None and len(resp) == 6 and resp[:2] == bytes([0x67, 0x01])
        return ok, "resp=%s (still in extended, S3 kept alive)" % (resp,)
    case("timing", "D4", "3E keepalive prevents S3 expiry", d4)

    # ---------------- E. flash programming (destructive) --------------------
    def e1(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect([0x31, 0x01, 0xFF, 0x00], [0x71, 0x01, 0xFF, 0x00], timeout=10.0)
        if not ok:
            return False, "erase resp=%s" % (resp,)
        ok, resp, _ = r.expect(
            [0x34, 0x00, 0x44] + APP_START.to_bytes(4, "big") + (0x20).to_bytes(4, "big"),
            [0x74, 0x20, 0x02, 0x00])
        if not ok:
            return False, "requestDownload resp=%s" % (resp,)
        ok, resp, _ = r.expect([0x36, 0x01] + list(range(32)), [0x76, 0x01])
        if not ok:
            return False, "transferData resp=%s" % (resp,)
        ok, resp, _ = r.expect([0x37], [0x77])
        if not ok:
            return False, "transferExit resp=%s" % (resp,)
        ok, resp, _ = r.expect([0x31, 0x01, 0xFF, 0x02], [0x71, 0x01, 0xFF, 0x02])
        if not ok:
            return False, "checkMemory resp=%s" % (resp,)
        ok, resp, _ = r.expect([0x31, 0x01, 0xFF, 0x01], [0x71, 0x01, 0xFF, 0x01, 0x00])
        return ok, "full flow OK, checkDependency resp=%s" % (resp,)
    case("flash", "E1", "full download flow (erase/RD/TD/RTE/check)", e1, requires="flash")

    def e2(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        resp = r.start_download()
        if resp != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (resp,)
        ok, resp, _ = r.expect_neg([0x36, 0x02] + list(range(32)), 0x36, 0x73)
        return ok, "resp=%s (wrong block sequence counter)" % (resp,)
    case("flash", "E2", "36 wrong block counter -> WBSC", e2, requires="flash")

    def e3(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        resp = r.start_download()
        if resp != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (resp,)
        ok, resp, _ = r.expect_neg([0x36, 0x01] + list(range(40)), 0x36, 0x31)
        return ok, "resp=%s (block exceeds remaining size)" % (resp,)
    case("flash", "E3", "36 block larger than download size -> ROOR", e3, requires="flash")

    def e4(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        resp = r.start_download()
        if resp != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (resp,)
        ok, resp, _ = r.expect_neg([0x36, 0x01, 0xAA, 0xBB, 0xCC], 0x36, 0x31)
        return ok, "resp=%s (unaligned block)" % (resp,)
    case("flash", "E4", "36 unaligned block -> ROOR", e4, requires="flash")

    def e5(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        req = bytes([0x34, 0x00, 0x44]) + (0x80000000).to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x31)
        return ok, "resp=%s (boot area address)" % (resp,)
    case("flash", "E5", "34 address in boot area -> ROOR", e5, requires="flash")

    def e6(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        req = bytes([0x34, 0x00, 0x44]) + (APP_START + 1).to_bytes(4, "big") + (0x20).to_bytes(4, "big")
        ok, resp, _ = r.expect_neg(req, 0x34, 0x31)
        return ok, "resp=%s (unaligned address)" % (resp,)
    case("flash", "E6", "34 unaligned address -> ROOR", e6, requires="flash")

    def e7(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        resp = r.start_download()
        if resp != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (resp,)
        ok, resp, _ = r.expect_neg([0x37], 0x37, 0x22)
        return ok, "resp=%s (exit before all data received)" % (resp,)
    case("flash", "E7", "37 before download complete -> CNC", e7, requires="flash")

    def e8(r):
        if not r.prog_erased():
            return False, "erase/unlock precondition failed"
        resp = r.start_download()
        if resp != bytes([0x74, 0x20, 0x02, 0x00]):
            return False, "requestDownload resp=%s" % (resp,)
        if not r.enter(0x01):
            return False, "cannot return to default"
        if not r.enter(0x02):
            return False, "cannot re-enter programming"
        ok, resp, _ = r.expect_neg([0x36, 0x01] + list(range(32)), 0x36, 0x33)
        return ok, "resp=%s (session change locked security and reset state)" % (resp,)
    case("flash", "E8", "session change mid-download -> locked", e8, requires="flash")

    def e9(r):
        if not r.enter(0x02):
            return False, "cannot enter programming"
        if not r.unlock(1):
            return False, "unlock failed"
        ok, resp, _ = r.expect_neg([0x31, 0x01, 0xFF, 0x00, 0x00], 0x31, 0x13)
        return ok, "resp=%s (erase with wrong length)" % (resp,)
    case("flash", "E9", "31 erase wrong length -> IMLOIF", e9, requires="flash")

    # ---------------- F. ECU reset (optional) ------------------------------
    def f1(r):
        ok, resp, _ = r.expect([0x11, 0x01], [0x51, 0x01], timeout=3.0)
        if not ok:
            return False, "hardReset resp=%s" % (resp,)
        time.sleep(3.0)
        ok2, resp2, _ = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4], timeout=4.0)
        return ok2, "reset ack ok, re-init resp=%s" % (resp2,)
    case("reset", "F1", "11 01 hardReset + ECU comes back", f1, requires="reset")

    def f2(r):
        ok, resp, _ = r.expect([0x11, 0x03], [0x51, 0x03], timeout=3.0)
        if not ok:
            return False, "softReset resp=%s" % (resp,)
        time.sleep(2.0)
        ok2, resp2, _ = r.expect([0x10, 0x01], [0x50, 0x01, 0x00, 0x05, 0x01, 0xF4], timeout=4.0)
        return ok2, "reset ack ok, re-init resp=%s" % (resp2,)
    case("reset", "F2", "11 03 softReset + ECU comes back", f2, requires="reset")

    def f3(r):
        ok, resp, _ = r.expect_neg([0x11, 0x02], 0x11, 0x12)
        return ok, "resp=%s" % (resp,)
    case("reset", "F3", "11 02 invalid sub-function -> SFNS", f3, requires="reset")

    # ---------------- G. functional addressing ------------------------------
    def g1(r):
        ok, resp, _ = r.expect([0x3E, 0x00], [0x7E, 0x00], tx_id=r.args.funct_id)
        return ok, "resp=%s" % (resp,)
    case("functional", "G1", "functional 3E 00 via 0x7DF", g1)

    def g2(r):
        ok, resp, _ = r.expect([0x22, 0xF1, 0x80], [0x62, 0xF1, 0x80, 0x01, 0x42, 0x4F, 0x4F, 0x54],
                               tx_id=r.args.funct_id)
        return ok, "resp=%s" % (resp,)
    case("functional", "G2", "functional 22 F180 via 0x7DF", g2)

    return cases


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
def parse_args():
    ap = argparse.ArgumentParser(description="UDS/DCM automated test for autosarTc364_Boot (2)")
    ap.add_argument("--interface", default=DEFAULT_INTERFACE, help="python-can interface (default: %(default)s)")
    ap.add_argument("--channel", default=DEFAULT_CHANNEL, help="python-can channel (default: %(default)s)")
    ap.add_argument("--bitrate", type=int, default=DEFAULT_BITRATE, help="CAN bitrate (default: %(default)s)")
    ap.add_argument("--req-id", type=lambda x: int(x, 0), default=DEFAULT_REQ_ID, help="physical request ID")
    ap.add_argument("--resp-id", type=lambda x: int(x, 0), default=DEFAULT_RESP_ID, help="response ID")
    ap.add_argument("--funct-id", type=lambda x: int(x, 0), default=DEFAULT_FUNCT_ID, help="functional request ID")
    ap.add_argument("--group", action="append", choices=["session", "security", "matrix", "timing", "flash",
                                                         "reset", "functional"],
                    help="run only selected groups (repeatable)")
    ap.add_argument("--flash-test", action="store_true", help="run destructive flash tests (erases APP!)")
    ap.add_argument("--reset-test", action="store_true", help="run ECU reset tests")
    ap.add_argument("--list", action="store_true", help="list test cases and exit")
    return ap.parse_args()


def main():
    args = parse_args()
    cases = build_cases()

    if args.list:
        print("%-10s %-6s %s" % ("GROUP", "ID", "NAME"))
        for group, tc_id, name, _fn, requires in cases:
            flag = " [%s]" % requires if requires else ""
            print("%-10s %-6s %s%s" % (group, tc_id, name, flag))
        return 0

    selected = args.group

    runner = TestRunner(args)
    print("Connected: interface=%s channel=%s bitrate=%d req=0x%03X resp=0x%03X funct=0x%03X"
          % (args.interface, args.channel, args.bitrate, args.req_id, args.resp_id, args.funct_id))
    print("=" * 72)

    for group, tc_id, name, fn, requires in cases:
        if requires == "flash" and not args.flash_test:
            continue
        if requires == "reset" and not args.reset_test:
            continue
        if selected and group not in selected:
            continue
        runner.run_one(group, tc_id, name, fn)

    ok = runner.summary()
    try:
        runner.bus.shutdown()
    except Exception:
        pass
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
