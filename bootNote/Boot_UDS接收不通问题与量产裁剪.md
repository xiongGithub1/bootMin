# Boot UDS 接收不通问题总结 & 量产裁剪记录

> **工程：** `autosarTc364_Boot (2)`  
> **相关代码：** `Appl/Source/Boot_Init.c`、`Appl/Source/Boot_Uds.c`  
> **栈形态：** Can → CanIf → CanTp → PduR → **Cdd**（无 Dcm）  
> **日期：** 2026-08-14

---

## 1. 现象

| 现象 | 说明 |
|------|------|
| CANoe Diagnostic Console Timeout | `10 01` / `10 02` / `3E` 无应答 |
| `Cdd_TpRxIndication` 长时间不进 | 断点不停 |
| 后期：`CanInterrupt` / `CanIf_RxIndicationAsr403` / `CanTp_RxIndication` 能进 | 硬件与 CanIf→CanTp 已通 |
| 仍到不了 `Cdd_StartOfReception` | 卡在 PduR 未真正初始化 |

探测帧 `0x123`（`BOOT_CAN_TX_TEST`）能周期性发出 → **波特率 / TX / 控制器基本正常**。

---

## 2. 诊断 CAN-ID（必须一致）

| 方向 | CAN-ID | 配置位置 |
|------|--------|----------|
| 物理请求 Tester→ECU | **0x74C** | `CanIf_Lcfg.c` / `CANFD364.dbc` / `Tc364Boot.cdd`（1868） |
| 物理响应 ECU→Tester | **0x75C** | 同上（1884） |
| 功能请求 | **0x7DF** | 同上（2015） |

**踩坑：** CANoe Trace 曾出现请求 **0x740**。Boot 只认 **0x74C**，ID 不对时即使 ISR 能进，CanIf 也会丢掉，到不了 Cdd。

ISO-TP 单帧示例（DLC=8，Padding ON）：

```text
74C: 02 10 01 00 00 00 00 00
     ^^ PCI=SF, DL=2
应答在 75C，例如：50 01 ...
```

首字节若是裸 UDS `10 01...`（无 PCI `02`），CanTp 会当 FF 丢掉，**不会**调 `Cdd_StartOfReception`。

---

## 3. 接收调用链（本工程）

```text
SRC_CAN0INT0
  → ISR(CanIsr_0)                 Can_Irq.c
  → CanInterrupt()                Can.c
  → CanBasicInterruptRx()
  → CanIf_RxIndicationAsr403()    CanIf.c
  → CanTp_RxIndication()          CanTp.c
  → CanTp_CanIfRxIndicationSF()
  → PduR_CanTpStartOfReception()
  → Cdd_StartOfReception()        Boot_Uds.c
  → Cdd_CopyRxData()
  → Cdd_TpRxIndication()
  → Boot_Uds_Dispatch()
```

配置：`CAN_RX_PROCESSING = INTERRUPT`，`CAN_TX_PROCESSING = POLLING`。  
因此 **不要**指望 `Can_MainFunction_Read()` 收诊断帧；TX 回 `75C` 仍需 `Can_MainFunction_Write()`。

---

## 4. 问题清单与处理

| 序号 | 问题 | 根因 | 处理 | 状态 |
|------|------|------|------|------|
| 1 | PDU 收不到 | `CanIf_Init` 后 PDU 模式仍 OFFLINE | `Boot_StartCommunication()` 中 `CanIf_SetPduMode(..., CANIF_SET_ONLINE)` | 已改代码 |
| 2 | RX ISR 从不跑 | `Os_Isr_Lcfg.c` 中 `CanIsr_0.IsEnabledOnInitialization = FALSE`，`Os_InitialEnableInterruptSources()` 跳过 | `Boot_ComMainFunctions()` 首次调用 `Os_EnableInterruptSource(CanIsr_0, FALSE)` | 已改代码；**长期应在 DaVinci 勾 Enabled on init** |
| 3 | CANoe 无应答 / ID 错 | 请求发成 `0x740`，Boot 只收 `0x74C` | 台架/CDD/IG 统一为 `74C`/`75C` | 台架配置 |
| 4 | 进了 CanIf 但 CanId 怪异 | BasicCAN 收所有标准帧（HW filter accept-all） | 正常；以 `CanId==0x74C` 条件断点过滤 | 说明项 |
| 5 | `CanTp_RxIndication` 能进，`Cdd_StartOfReception` 不进 | **未调用 `PduR_PreInit`**，`PduR_Init` 报 `PDUR_E_NO_PREINIT`，PduR 拒绝转发 | `Boot_Init()`：`PduR_PreInit(PduR_Config_Ptr)` 再 `PduR_Init(...)` | **已改代码（关键）** |
| 6 | 功能寻址 7DF | `CANTP_EXISTS_FUNCTIONAL_RXTATYPE=OFF`，两路 RxSdu 都是 PHYSICAL；7DF Mask=`0x47FF`（last364 为 `0x07FF`） | DaVinci：7DF 改为 Functional；Mask 改 `0x07FF` | 待配置 |
| 7 | 调试符号跳到 `0x0` | 从 Core0 Symbols 点未执行到的函数 | 直接打开源文件下断点 | 调试方法 |

### 4.1 关键代码（`Boot_Init.c`）

```c
/* Init 顺序 */
Can_Init(Can_Config_Ptr);
CanIf_Init(CanIf_Config_Ptr);
PduR_PreInit(PduR_Config_Ptr);   /* 不可省略 */
PduR_Init(PduR_Config_Ptr);
CanTp_Init(CanTp_Config_Ptr);

/* 开通信 */
CanIf_SetControllerMode(..., CANIF_CS_STARTED);
CanIf_SetPduMode(..., CANIF_SET_ONLINE);

/* 周期：使能 CanIsr + TX/Mode/CanTp 轮询 */
Os_EnableInterruptSource(CanIsr_0, FALSE);  /* 一次即可 */
Can_MainFunction_Write();
Can_MainFunction_Mode();
CanTp_MainFunction();
```

### 4.2 调试时快速核对

在 `CanTp_RxIndication` 入口：

| 变量 | 期望 |
|------|------|
| `RxPduId` | `0`（74C） |
| `SduLength` | `8` |
| `SduDataPtr[0]` | `0x02`（SF） |
| `lErrorId==0xFF` | 正常（`CANTP_E_NO_ERROR` 就是 `0xFF`） |
| `PduR_PreInitialized` | `TRUE` |
| `CanTp_InitState` | `1` |

---

## 5. 物理路径配置核对（GenData，接线正确）

```text
CanIf Rx 0x74C → CanTp RxPdu(0)  （与 RxFcNPdu 同句柄，Vector 常规）
CanTp RxSdu0 → PduRSrcPdu_1
PduR → CddPduRUpperLayerRxPdu_74c → Cdd_StartOfReception / CopyRx / TpRxIndication
Cdd TX 75c → CanTp TxSdu → CanIf Tx 0x75C
```

接收不通时，**优先查 Init/ISR/台架 ID/PCI**，不是 PduR 路由表错绑。

---

## 6. 量产 Boot：模块清单与 Dcm 取舍

### 6.1 推荐：不加 Dcm（当前方向）

| 类别 | 模块 |
|------|------|
| 必须 | Mcu, Port, Can, CanIf, CanTp, PduR, Os（裁剪）, FlsLoader, Crc, Boot_Uds/Cdd |
| 按需 | Dio, Wdg, Det（量产可关上报） |
| 不要进 Boot | **Dcm, Dem, NvM, Fee, Ea, Com, ComM, CanSM, Nm, 全量 EcuM/BswM/Rte** |

UDS 服务在 `Boot_Uds` 按需扩展：`0x10` / `0x3E` / `0x27` / `0x34` / `0x36` / `0x37` / `0x31`。

### 6.2 为何加 Dcm 后 Flash 很大

- Boot 区预算约 **256 KB**。
- 历史带 Dcm 的镜像中，大致：Os ≫ Dem ≫ Dcm；**Dem（及 NvM）往往比 Dcm 本体更贵**。
- 量产刷写不需要 App 全套诊断；**Cdd 精简 UDS 是常见量产做法**。

若 OEM 强制 Dcm：只开刷写相关服务；Dem 仅接口壳且 **NvM OFF**；同时狠裁 Os；并设镜像大小门禁。

### 6.3 量产前还应收尾

1. DaVinci：`CanIsr_0` **Enabled on initialization = TRUE**（去掉代码补丁依赖）。  
2. `BOOT_CAN_TX_TEST` 默认 **0**，禁止量产带 `0x123` 探测。  
3. InitTask 死循环 → 改为周期 Task + 看门狗。  
4. 7DF Functional + Mask 修正。  
5. 编译改为 size/速度优化（勿长期 `-O0` 量产）。  
6. Flash 预算 CI：超 Boot 区直接失败。

---

## 7. 台架最小验证步骤

1. 重新编译下载（含 `PduR_PreInit` + `Os_EnableInterruptSource`）。  
2. 确认 `0x123` 探测可关可开；开时 Trace 有周期性 Tx。  
3. IG 发：`ID=74C, DLC=8, Data=02 10 01 00 00 00 00 00`。  
4. 断点：`Cdd_StartOfReception` → `Cdd_TpRxIndication` → Trace 见 **75C** 应答。  
5. 再用 Diagnostic Console（CDD 请求/响应 ID 必须为 74C/75C）。

---

## 8. 相关文档

- `Boot_UDS协议栈_从CDD到实现.md` — CDD/DBC/Cdd 栈设计  
- `Boot_A2_配置清单.md` — 配置裁剪清单  
- `Boot_编译链接问题总结.md` — 编译链接类问题  

---

*记录目的：避免重复踩「PDU OFFLINE / ISR 未使能 / 漏 PduR_PreInit / 台架 ID 740」四类坑；并固定量产 Boot「无 Dcm」裁剪策略。*
