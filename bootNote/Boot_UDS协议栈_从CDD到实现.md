# 从 Tc364Boot.cdd 建立量产 UDS 协议栈（CAN 接入）

> **工程：** `autosarTc364_Boot`  
> **规范源：** `Config_Vector/Tc364Boot.cdd`（ISO 14229-1 UDS / CANdela）  
> **矩阵源：** `Config_Vector/CANFD364.dbc`（Boot 仅诊断帧）  
> **栈形态：** Slim AUTOSAR — **无 Dcm**，上端为 **Cdd**；传输层为 **CanTp**  
> **日期：** 2026-08-14

---

## 1. 量产视角：CDD 是什么、不是什么

| 角色 | 说明 |
|------|------|
| **Tc364Boot.cdd** | 诊断**产品规格**：会话、服务、安全访问、DID/Routine、时序（P2/S3）、寻址参数模板 |
| **CANFD364.dbc** | 总线**通信矩阵**：诊断 CAN-ID、DLC、波特率、DiagRequest/Response 属性 |
| **DaVinci ECUC** | AUTOSAR **实现配置**：Can/CanIf/CanTp/PduR/Os/Mcu… |
| **Cdd 应用代码** | 把 CDD 规定的 UDS **行为**落到 ECU（本项目不用 Dcm/CANdesc 生成） |

量产原则：

1. **一份 CDD** 对 OEM/产线/台架（CANoe+CDD）与 ECU 实现同源。  
2. **DBC 与 CDD 寻址必须一致**（物理/功能 ID、波特率）。  
3. Boot 只实现刷写所需服务子集；APP 用完整 CDD/Dcm，**寻址与安全策略与 Boot 对齐**。

---

## 2. 本项目已锁定的 CAN 接入参数

来自 `CANFD364.dbc` + 已 Generate 的 `CanIf_Lcfg.c`：

| 方向 | 报文 | CAN-ID | 用途 |
|------|------|--------|------|
| Rx Phys | `msg_diag_Request_MyECU` | **0x74C** | 物理请求 → CanTp Rx |
| Tx Phys | `msg_diag_Response_MyECU` | **0x75C** | 物理响应 ← CanTp Tx |
| Rx Func | `msg_diag_RequestGlobal` | **0x7DF** | 功能请求 → CanTp Rx |
| 总线 | Classic CAN 8 字节 | **500 kbit/s** | `Baudrate=500000` |

**CANdela 核对：** 在 Studio 打开 `Tc364Boot.cdd`，协议接口选 **CAN（标准寻址）**，把 ECU 实例的：

- `CAN.ReqCanId` → `0x74C`
- `CAN.ResCanId` → `0x75C`
- `CAN.ReqCanIdFunc` → `0x7DF`
- `CAN.Baudrate` → `500000`

与 DBC/ECU 配置对齐（模板默认值常见为 `0x600` 一类，**不能直接用模板默认**）。

时序建议从 CDD/OEM 规范抄入 CanTp/Cdd（示例模板常见值，以你 CDD 实例为准）：

| 参数 | 典型含义 | 落到 |
|------|----------|------|
| P2Server | 收到请求后开始响应的时限 | Cdd 会话/NRC 0x78 |
| P2*Server | 扩展时限 | 同上 |
| S3Server | 会话保持超时 | Cdd 会话定时器 |
| STmin / Blocksize | ISO-TP 流控 | **CanTp** |

---

## 3. 量产协议栈分层（本 Boot）

```text
┌─────────────────────────────────────────────┐
│  Tc364Boot.cdd 定义的 UDS 行为（会话/服务）   │  ← 规格
│  实现：Appl Cdd（mini UDS）                  │  ← 现无 Dcm
├─────────────────────────────────────────────┤
│  PduR（CanTp ↔ Cdd）                        │
├─────────────────────────────────────────────┤
│  CanTp（ISO 15765-2）                       │
├─────────────────────────────────────────────┤
│  CanIf（诊断 PDU UL=CAN_TP）                │
├─────────────────────────────────────────────┤
│  Can + Mcu(MCAN clk) + Port                 │
└─────────────────────────────────────────────┘
         CAN 总线：0x74C / 0x75C / 0x7DF @ 500k
```

与完整 MSR 应用对比：

| 层 | 量产 APP（last364 类） | 本 Boot Slim |
|----|------------------------|--------------|
| 诊断应用 | Dcm + SWC/Rte | **Cdd 手写/自研** |
| 网络 | ComM/CanSM | **直接 CanIf Start** |
| 刷写 | 常 Fls/Fee 等 | **FlsLoader** |

这样 Flash 可控（当前 ≈41KB），同时仍满足产线 UDS-on-CAN。

---

## 4. 从 CDD 到实现的服务裁剪（Boot）

`Tc364Boot.cdd` 基于完整 UDS 模板，含 ProgrammingSession、RequestDownload、SecurityAccess 等。  
**Boot 量产最小集（建议按优先级实现）：**

| SID | 服务 | Boot 必要性 | 说明 |
|-----|------|-------------|------|
| 0x10 | DiagnosticSessionControl | 必须 | Default / Programming（+ 按需 Extended） |
| 0x3E | TesterPresent | 必须 | 保会话；功能寻址常 suppressPosRsp |
| 0x27 | SecurityAccess | 强烈建议 | 进刷写前；种子密钥与 APP/OEM 一致 |
| 0x22 / 0x2E | DID 读/写 | 按需 | 指纹、Boot 版本、编程日期等 |
| 0x31 | RoutineControl | 必须（刷写） | 擦除、CheckMemory、CheckProgrammingDependencies |
| 0x34 / 0x36 / 0x37 | Download 三件套 | 必须 | 写 APP 区；调 FlsLoader |
| 0x11 | ECUReset | 必须 | 刷完复位；配合 StayInBoot/跳 APP |
| 0x14 / 0x19 / 0x85… | DTC 类 | Boot 通常 **不做** | 留给 APP/Dem |

否定响应：至少实现 `0x11/0x12/0x13/0x22/0x31/0x33/0x35/0x70/0x72/0x78` 中与刷写相关的子集（与 CDD NRC 表一致）。

---

## 5. DaVinci / 工程落地顺序（CAN → UDS）

### 阶段 A — CAN 物理接入（已大部分具备）

1. **Mcu**：`McuMCanFrequency` / CAN clock ref；`CanCpuClockRef` 指向它。  
2. **Port**：MCAN TX/RX 引脚与板级一致。  
3. **Can**：500k、过滤器覆盖 `0x74C`、`0x7DF`；`CanCounterRef`→`SystemTimer`。  
4. **CanIf**：  
   - Rx：`*_Tp_*` PDU，UL=**CAN_TP**，ID 0x74C / 0x7DF  
   - Tx：响应 PDU，UL=**CAN_TP**，ID 0x75C  
   - Controller 指示 UL=**CDD**（BusOff/Mode 回调）  
5. **Boot_Init**：`Can_Init` → `CanIf_Init` → `CanIf_SetControllerMode(STARTED)`（无 ComM/CanSM）。  
6. **Os**：周期调用 `Can_MainFunction_Read/Write/...`（按配置）、`CanIf_MainFunction`。

验收：示波器/分析仪看到 ECU ACK；空闲不 Error Passive。

### 阶段 B — ISO-TP（已配置骨架）

1. **CanTp**：Phys + Func Rx SDU，Tx 仅 Phys；STmin/BS/N_As… 对齐 CDD。  
2. **PduR**：CanTp ↔ Cdd 路由（现 `PduR_Lcfg` 已挂 Cdd 五回调）。  
3. 周期：`CanTp_MainFunction`、`PduR_MainFunction`（若需要）。

验收：发多帧请求能看到 FC；`Cdd_StartOfReception`→`CopyRxData`→`TpRxIndication` 被调用。

### 阶段 C — 按 CDD 实现 Cdd UDS

**已落地骨架（2026-08-14）：**

| 文件 | 内容 |
|------|------|
| `Appl/Source/Boot_Init.c` | Mcu/Port/Can/CanIf/PduR/CanTp/FlsLoader Init；`Boot_StartCommunication`；COM MainFunctions |
| `Appl/Source/Boot_Uds.c` | Cdd TP + **0x10 / 0x3E**（正/负响应） |
| `EcuM_Stub.c` | `Boot_Init` → `StartOS`；`StartupTwo` → Start CanIf |
| `BrsMain.c` `Default_Init_Task_Trusted` | 开中断后循环 `Boot_ComMainFunctions()` |

联调：500k，物理 `0x74C` 发 `02 3E 00` → 应回 `02 7E 00`（或 SF：`02 3E 80` 无正响应）。

后续在 `Boot_Uds.c` 继续加 `0x27/0x34/0x36/0x37/0x31/0x11`。

在 `Cdd_TpRxIndication`（或独立状态机）中：

1. 解析 SID / subfunction（对齐 CDD 会话与 `mayBeExec`）。  
2. 组正响应 / NRC；经 `PduR_CddTransmit`（或工程生成的 Tx API）发回。  
3. 会话与 S3：定时器在 Os Alarm/周期任务里跑。  
4. `0x34/36/37`：地址窗口校验（仅 APP Flash）→ FlsLoader 擦写。  
5. `0x31`：校验镜像 → 置位“可跳转”/依赖检查。  
6. `0x11`：复位；可选 StayInBoot。

CDD 仍用于：台架加载同一 `Tc364Boot.cdd` 做 CAPL/诊断自动化；ECU 侧行为与之一致即可，**不必**上 Dcm。

### 阶段 D — 产线闭环

1. 功能寻址进 Boot / 物理寻址刷写。  
2. 安全访问失败次数与延时符合 CDD。  
3. 刷写失败可恢复（不砖化 Boot）。  
4. 成功后复位进 APP；APP 诊断 ID 与 Boot **不冲突**（通常同 Phys ID，会话/服务表不同）。

---

## 6. CDD ↔ 代码映射表（实施用）

| CDD 概念 | ECU 落点 |
|----------|----------|
| Req/Res/Func CAN-ID | DBC + CanIf Rx/Tx PDU CanId |
| Baudrate | Can Baudrate + Mcu MCAN clk |
| StMin / Blocksize / N_As… | CanTp channel 参数 |
| P2 / P2* / S3 | Cdd 会话与响应时序 |
| DiagnosticSession | Cdd 会话状态机 |
| SecurityAccess | Cdd + 种子密钥算法（可与 APP 共用库） |
| RequestDownload… | Cdd + FlsLoader + 地址白名单 |
| RoutineControl | Cdd + 擦除/CRC/依赖检查 |
| ECUReset | Mcu_PerformReset / 软复位钩子 |

---

## 7. 与当前工程差距

| 项 | 状态 |
|----|------|
| DBC 诊断三帧 + CanIf/CanTp/PduR→Cdd | ✅ 已 Generate |
| Boot_Init（Mcu/Port/Can Start） | ✅ `Boot_Init.c` + `EcuM_Stub` |
| Cdd `0x10` / `0x3E` | ✅ `Boot_Uds.c` |
| COM MainFunctions 调度 | ✅ `Default_Init_Task_Trusted` 循环 |
| 按 Tc364Boot.cdd 其余刷写服务 | ❌ 待开发 |
| FlsLoader 接入 0x34/36/37 | ❌ Init 已调，业务未接 |
| CDD 内 CAN-ID 与 DBC 一致性人工确认 | ⚠️ 在 Studio 核对 |

---

## 8. 推荐联调顺序（产线视角）

1. **链路：** `3E 00`（物理 0x74C）→ 正响应 `7E 00`  
2. **会话：** `10 02` → Programming；S3 超时回 Default  
3. **安全：** `27 xx` 种子/密钥  
4. **下载：** `34`→`36`*→`37`（小镜像）  
5. **校验/复位：** `31` → `11 01` → APP 跑起来  

台架：CANoe 加载 **同一套** `Tc364Boot.cdd` + 总线 500k / ID 与上表一致。

---

## 9. 相关文档

- `Boot_A2_配置清单.md` — 模块与 DaVinci 项  
- `Boot_功能配置操作指南.md` — 启动链与体积  
- `Boot_编译链接问题总结.md` — Cdd/SchM/FlsLoader 链接坑
