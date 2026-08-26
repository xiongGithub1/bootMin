# Boot CANoe CAPL 测试问题总结

> **工程：** `autosarTc364_Boot (2)`  
> **脚本：** `Test/Boot_Dcm_CanoeTest.can`  
> **对照：** `Test/ZxDocTest.py`（周立功 ZXDoc，同一套用例 A/B/C/…）  
> **CAN：** 物理请求 `0x74C`，应答 `0x75C`，功能寻址 `0x7DF`，仲裁 500 kbit/s  
> **更新日期：** 2026-08-19  
> **刷写 / FlashPanel / CHIPID：** 见同目录 `Boot_APP分区与刷写联调总结.md`

ZXDoc 能过、CANoe 不过，多数不是 DCM 判据错，而是 **CAPL 语法 / 发帧 DLC / CanTp TX 排队 / ISO-TP 收包 / 用例间会话未复位**。

CanTp 丢 `50 02` 的完整说明见 **第 5 节**；CAPL 回归见 **第 11 节 H1–H5**。

---

## 1. 问题总览

| 序号 | 现象 | 根因 | 处理 | 状态 |
|------|------|------|------|------|
| 1 | CAPL 编译 38 errors：`message gReq`、`Unknown symbol`、`Exp` 参数不匹配 | 无 DBC 不能写裸 `message`；`Exp`/`exp` 与数学 `exp()` 冲突；`?:`、`(void)` 非法 | `message 0x000`；`ExpectResp`；改 if/else | 已解决 |
| 2 | `dword key` parse error | `key` 是 CAPL 保留字（`on key`） | 改名为 `secKey` | 已解决 |
| 3 | Start 后立刻 `(Failed)`，Write：`09-0017 TestStep ignored` | `TestStep*` 只能写在 `testcase` 内；E/F 跳过写在 `MainTest` | `TC_E_Skipped` / `TC_F_Skipped`；入口 `MainTest` | 已解决 |
| 4 | 几乎全超时 2 s，仅 `10 81`/`3E 80` 过 | CanIf `DLC_CHECK=ON` 要求 DLC=8；CAPL 按实际长度发（DLC=2）被丢掉 | `SendRaw` 固定 DLC=8，不足补 0 | 已解决 |
| 5 | A2：`10 02` 无 `50 02`（默认会话发 10 02 是允许的） | CanTp 通道虽是 FULL_DUPLEX，**同一条 Tx N-PDU（0x75C）未 TxConfirmation 前不能再 Transmit**；旧代码 `(void)PduR_CddTransmit` 失败即丢；在 RxIndication 里嵌套 Transmit 也常 E_NOT_OK | `Cdd_TpTxBusy`/`Retry`/`Cdd_RxDeferred`；`Boot_Uds_MainFunction` 在 `CanTp_MainFunction` 之后重试；CAPL H1–H5 回归 | 已解决 |
| 6 | A7 约 2.4 s 失败；ZXDoc 能过 | A7 首次走 ISO-TP 多帧 `34`；CANoe 发完 First Frame 再 `TestWaitForMessage`，**FC 已到却没人收** | `on message 0x75C` 入队，按 PCI 取 FC/应答 | 已解决 |
| 7 | B3 秒表、无 Runtime，整模块停 | `byte req[6]` 后又 `BuildDownloadReq` 写 11 字节，CAPL 越界崩溃 | `req[11]` | 已解决 |
| 8 | B5 零种子、C 组 SNSIAS/RSE 等几十 ms 失败 | ZXDoc 每例后 `to_default()`；CANoe 会话/安全串台，NRC 对不上 | 每个 `TC_*` 后 `ToDefault()` | 已解决 |

---

## 2. 在 CANoe 12 上挂脚本

Ribbon 上 **Test Module 灰色** 是正常的：没有 Test Setup 上下文。

1. **View → Test Setup** 打开窗口  
2. 右键 → **Insert Test Environment** → 再插入 **CAPL Test Module**  
3. 选 `Test/Boot_Dcm_CanoeTest.can`，**F7 编译**  
4. 先 **Start 测量**，再 Start 该测试模块  
5. 看 Write 的 **Test** 页签 / Test Report  

硬件（周立功 USBCANFD 等）仲裁域 **500 kbps**，通道绑到 Trace 上实际有 `0x74C`/`0x75C` 的那一路（本工程常见 **CAN 3**）。  
破坏性用例默认关：`gRunFlash` / `gRunReset`（variables 里改成 1 才跑 E/F）。

---

## 3. CAPL 编译（与 C 的差异）

无 DBC 时：

```capl
message 0x000 gReq;
message 0x000 gFrame;
```

不要用 `int Exp(...)`（与 `exp()` 冲突，大小写不敏感）。  
不要用 `?:`、`(void)fn(...)`、变量名 `key`。

---

## 4. CanIf DLC 检查

`CanIf_Cfg.h`：`CANIF_DLC_CHECK = STD_ON`  
Rx PDU（`0x74C` / `0x7DF`）配置 DLC=**8**。

ZXDoc 发诊断帧一律 DLC=8 补 0；CAPL 原先 `gReq.dlc = len`（`10 01` 只有 2）→ ECU 直接丢弃 → 2 s 超时。  
只有「期望无应答」的 `10 81` / `3E 80` 会过。

**处理：** `SendRaw` 固定 `dlc = 8`，剩余字节 `0x00`。

---

## 5. CanTp：全双工 ≠ 可以连发两条 TX（丢 `50 02` 的根因）

### 5.1 配置是什么

`Appl/GenData/CanTp_Cfg.h`：

- `CANTP_MODE_FULL_DUPLEX`（Rx/Tx SDU 的 `ChannelMode` 都是 FULL_DUPLEX）
- **没有** HALF_DUPLEX 通道

诊断 PDU 只有一对：

| 方向 | CAN ID | 角色 |
|------|--------|------|
| Tester → ECU | `0x74C` 物理 / `0x7DF` 功能 | CanTp Rx |
| ECU → Tester | `0x75C` | CanTp Tx（应答 + 对 tester 多帧的 FC） |

### 5.2 容易混淆的两点

ISO-TP / Vector CanTp 的 **FULL_DUPLEX** 只表示：**同一通道上可以同时进行一次 RX 会话和一次 TX 会话**（例如正在发 `50 01` 时，可以再收下一条 `10 02`）。

它 **不** 表示：

- 可以对 **同一条 Tx N-PDU（`0x75C`）** 在上一次 `PduR_CddTransmit` 尚未 `TxConfirmation` 时再调一次 `Transmit`
- CanTp 会把第二次 `Transmit` 自动排队

第二次 `PduR_CddTransmit` 在 TX 仍 busy 时返回 **`E_NOT_OK` 是 AUTOSAR 正常行为**。正式 Dcm 的做法是：失败则等确认后在 `MainFunction` 里再发；**不是**在总线上自动重发同一帧。

若把通道改成 HALF_DUPLEX，则更严：TX 进行中连 RX 都会被拒。本工程没有走这条配置，问题出在 **应用层把 `E_NOT_OK` 当成功丢掉了下一包 UDS 应答**。

### 5.3 现象（ZXDoc 过、CANoe A2 无 `50 02`）

默认会话允许 `10 02`。若 DCM 会话门拒绝，应是 `7F 10 7F`，**不应静默**。

时间线（CANoe 旧脚本，请求间隔约 1～2 ms）：

```text
Tester:  10 01
ECU:     50 01          ← PduR_CddTransmit 已接受，等待 TxConfirmation
Tester:  10 02          ← FULL_DUPLEX 允许此时再收
ECU:     处理 10 02，再 Transmit(50 02)
         PduR 返回 E_NOT_OK（0x75C 仍 busy）
旧代码:  (void)PduR_CddTransmit(...);   ← 失败当成功，50 02 再也不会发
Tester:  等 2 s 超时
```

ZXDoc 用例间隔更大，`TxConfirmation` 往往已经回来，所以同一套 A2 能过。

### 5.4 三条会丢应答的路径（旧 Boot）

| # | 路径 | 结果 |
|---|------|------|
| A | 在 `Cdd_TpRxIndication` / CanTp 回调里直接 `PduR_CddTransmit` | 嵌套 `CanTp_Transmit`，经常 `E_NOT_OK` |
| B | `(void)PduR_CddTransmit`，不看返回值、不重试 | busy 时 **本条应答永久丢失**（A2 的 `50 02`） |
| C | `TxConfirmation(E_OK)` 时无条件清掉 `Cdd_TpTxBuf` | 若确认到达前已经把 **下一条** 应答写进同一 buffer 并置了 retry，确认成功会把新应答清掉 |

### 5.5 现实现（`Appl/Source/Boot_Uds.c`）

三个标志：

| 变量 | 含义 |
|------|------|
| `Cdd_TpTxBusy` | PduR 已接受，等 `Cdd_TpTxConfirmation` |
| `Cdd_TpTxRetry` | buffer 里已有要发的 N-SDU，PduR 尚未接受（或确认失败要重发） |
| `Cdd_RxDeferred` | 请求已收全，**等 TX 空闲** 再 `Boot_Dcm_ProcessRequest` |

规则：

1. **`Cdd_TpRxIndication` 只置 `Cdd_RxDeferred`，禁止在 CanTp 回调里 Transmit**（堵住路径 A）。
2. `Boot_Uds_Transmit`：若 `Busy`，只置 `Retry` 并保留 buffer，不调用 PduR。
3. `Boot_Uds_MainFunction`（见下节调度顺序）：先 `TryTransmit` 重试，再在 `Busy==0 && Retry==0` 时处理 deferred 请求。
4. `Cdd_TpTxConfirmation`：
   - 失败 → `Retry=1`（同一 payload 再发）；
   - 成功且 `Retry==0` → 清 `Cdd_TpTxLen`；
   - 成功且 `Retry==1` → **不清 buffer**（已排了下一条应答，堵住路径 C）。

这是应用层排队，不是 CanTp 内部把两次 Transmit 合成一次。

### 5.6 周期任务顺序（必须 CanTp 之后）

`Boot_Init.c` → `Boot_ComMainFunctions`：

```text
Can_MainFunction_Write / Read / Mode
  → CanTp_MainFunction          ← 推进 ISO-TP，可能 TxConfirmation
    → Boot_Uds_MainFunction     ← 此时 Busy 才可能已经清掉，才能重试 / 处理 deferred RX
      → Boot_Dcm_MainFunction   ← S3 等
```

若把 `Boot_Uds_MainFunction` 放到 `CanTp_MainFunction` **之前**，本周期的 Confirmation 还没来，retry 会再空转一轮，贴着发的 `10 02` 更容易在 P2 内发不出 `50 02`。

### 5.7 Tester 侧：20 ms 间隔 vs 间隔 0

`Boot_Dcm_CanoeTest.can`：

- `UdsRequest()`：应答后再等 **20 ms** 再发下一请求（降低误伤，对应用例 A/B/C/D）。
- `UdsRequestEx(..., gapMs=0)`：**H 组**专用，上一包 UDS 收齐立刻发下一包，专门打 5.3 的时间线。

20 ms **不能代替** Boot 侧的 busy/retry。H 组若仍丢 `50 02`，说明固件排队又坏了，而不是 CAPL 间隔不够。

回归用例见第 11 节。

---

## 6. A7 与 ISO-TP 多帧（ZXDoc 能过）

A7：`10 02` → 解锁 → `10 01` → `10 02` → **11 字节 `34`** 期望 `7F 34 33`。  
`34` 是脚本里 **第一次多帧**（FF → FC → CF）。

ZXDoc 后台一直收 `0x75C`。CANoe 旧逻辑：`output(FF)` 后再 `TestWaitForMessage`，ECU 的 FC 已经到了却漏收，随后空等约 2 s。  
残留的 `50 02` 也曾被误当成 FC（PCI 不是 `0x30`）。

**处理：** `on message 0x75C` 入队；`WaitRaw` / `WaitRawPci` 从队列取帧并按 PCI 过滤。

---

## 7. B3 写爆数组导致模块停跑

`TestStepFail` **不会**停止 `MainTest`。B3 秒表、无 Runtime、后面不跑，是 CAPL **越界崩溃**：

```capl
byte req[6];
/* 27 02 错误 key 用 6 字节 */
BuildDownloadReq(req, ...);   /* 写入 11 字节 → 越界 */
```

ZXDoc 用 Python list 会自动变长。已改为 `byte req[11]`。

---

## 8. 用例间必须回默认会话

ZXDoc `Runner.run_one()` 的 `finally` 里（除复位组）都会 `to_default()`。

CANoe 若不复位：B8 留在编程会话后，C4 的 `2E` 按「默认 → `7F 2E 7F`」去判，实际先过会话门、再被安全门挡成 **`7F 2E 33`**。

DCM 查表顺序：**会话 `0x7F` → 安全 `0x33` → 处理函数（RSE `0x24` 等）**。

`MainTest` 里每个 `TC_*` 之后调用 `ToDefault()`。

---

## 9. 关键文件

| 文件 | 内容 |
|------|------|
| `Test/Boot_Dcm_CanoeTest.can` | CANoe 测试模块（ISO-TP、H 组 gap=0、用例、MainTest） |
| `Test/ZxDocTest.py` | ZXDoc 对照脚本（例间 20 ms + `to_default`） |
| `Test/Boot_Dcm_TestSpec.md` | 用例规格（含 H 组、刷写顺序 E14–E16） |
| `Appl/Source/Boot_Uds.c` | Cdd TP、`Busy`/`Retry`/`RxDeferred`、TxConfirmation |
| `Appl/Source/Boot_Init.c` | `CanTp_MainFunction` 之后调 `Boot_Uds_MainFunction` |
| `Appl/GenData/CanTp_Cfg.h` | `CANTP_MODE_FULL_DUPLEX` |
| `Appl/Source/Boot_Dcm.c` / `Boot_Dcm_Cfg.c` | 会话/安全门、服务表 |
| `Appl/Source/Boot_Uds_Sm.c` | 刷写状态机（34/36/37/31 顺序，与 CanTp 无关） |

---

## 10. 再跑检查清单

1. 重新编译烧录 Boot（含 Transmit 重试 / RxDeferred）  
2. CANoe F7 编译当前 `.can`  
3. Trace：`0x74C` DLC=8，应有 `0x75C`  
4. A2 应有 `50 02`；A7 的 `34` 应看到 FC `0x30`  
5. **H1–H5 全部 Pass**（间隔 0，专门打 CanTp TX 排队）  
6. B3 不应再把整个模块打停  
7. C 组 SNSIAS 用例前 ECU 应在默认会话  

---

## 11. CanTp 回归用例（CAPL H 组，默认执行）

规格见 `Test/Boot_Dcm_TestSpec.md` 第 3 节 H。`MainTest` 在 D 组之后、E 组之前跑，**不依赖** `gRunFlash`。

| ID | 打哪条路径 | 步骤（gap=0） | 失败时像什么 |
|----|------------|---------------|--------------|
| H1 | 路径 B：连续 `50 xx` 来不及 Confirmation | `10 01`→`10 02`→`10 03`→`10 01` | 缺 `50 02`（与旧 A2 相同） |
| H2 | 连续单帧 TX | 8 次 `22 F180` | 某次 `62` 丢失 |
| H3 | 路径 C：ECU 多帧 TX 尚未结束就处理下一请求 | `22 F190`（20 B）立刻 `22 F180` 立刻 `10 02` | VIN 之后的 `62`/`50 02` 被冲掉 |
| H4 | SF TX 刚结束 + tester 多帧 RX（FF/FC/CF） | `10 02` 立刻 11 字节 `34` | 无 FC 或无 `7F 34 33` |
| H5 | 功能寻址 TX 后立刻物理 TX | `0x7DF` 的 `3E 00` 立刻物理 `22 F180` | 只有 `7E 00`，没有 `62 F180` |

H 组失败时优先查第 5 节，不要先改用例判据。

刷写服务 **访问顺序**（必须先擦再 `34` 再 `36` 再 `37`）是 `Boot_Uds_Sm` 的状态机，不是 CanTp 半双工。对应破坏性用例 **E14–E16**（`gRunFlash=1`），说明写在 `Boot_Dcm_TestSpec.md`。

---
