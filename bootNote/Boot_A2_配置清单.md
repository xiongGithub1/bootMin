# Boot A2 配置清单（Slim：Cdd + FlsLoader）

> **工程：** `autosarTc364_Boot`（Boot）+ `last364`（APP）  
> **目标：** 可编程 Boot，Flash **≤128KB**；校验/跳转 + ISO-TP + mini UDS（Cdd）+ FlsLoader  
> **明确不做：** Dcm / Dem / Com / ComM / CanSM / BswM / EcuM BSW / Rte / Fee / NvM  
> **CDD/DBC：** `Config_Vector/Tc364Boot.cdd`、`CANFD364.dbc`  
> **更新日期：** 2026-08-14

---

## 0. 已拍板参数

| 项 | 取值 |
|----|------|
| 形态 | A2 Slim |
| Boot 代码预算 | ≤ **128 KB**（当前 map ≈ **41 KB**） |
| Boot Flash 区 | `0x80000000` ~ `0x8001FFFF`（**128 KB**） |
| APP Flash | `0x80020000` ~ `0x801FFFFF` |
| BMHD | 仅 Boot（`0xAF400000`） |
| 诊断上端 | **Cdd**（PduR UL），非 Dcm |
| Flash 驱动 | Infineon **FlsLoader** |
| 留 Boot | APP 非法 / 共享标志 /（可选）诊断窗 |

建议地址细分：

| 区 | 地址 | 说明 |
|----|------|------|
| StartupCode | `0x80000000` | First Exec |
| Exception | `0x80000500` | CoreExceptions |
| Boot Code/Const | `0x80000700` ~ Boot 区末 | 代码须 ≤128KB |
| APP Image | APP 基址起 | 剩余 PFlash |
| Shared RAM | `Variables_Shared` @ **`0x70026F80` / 128B**；握手 @ **`0x70026FC0` / 64B** | 低 64B 留给 BRS；Boot/APP LSL 须一致 |

> 当前 LSL 仍可能把 `PFlash0_Cached` 开得很大——**分区要在 vLinkGen 收紧**，与代码预算是两件事。

---

## 1. 模块总览（Boot）

### 1.1 保留并使用

| 模块 | 用途 | 备注 |
|------|------|------|
| vBRS / vLinkGen / MemMap | 启动、链接、段 | Typed Pragmas；`BRS_COMP_TASKING` |
| Os | 最小单核 + `SystemTimer`（STM） | `CanCounterRef` → `/ActiveEcuC/Os/SystemTimer` |
| Det | 开发期错误 | 可精简 |
| Can / CanIf / CanTp / PduR | 诊断通信 | CanIf 诊断 PDU → CanTp；PduR → Cdd |
| Cdd | TP 上端 + mini UDS | 回调在 Appl，见 `Cdd_Cbk.h` |
| McalLib / Mcu / Port / Dio | 时钟、引脚 | Can 时钟走 Mcu `McuMCanFrequency` |
| Crc | 校验 | 可选自写 |
| **FlsLoader** | PFlash/DFlash 擦写 | 实例名必须 `*_0`；需 `FlsLdr_ExclArea` |

### 1.2 不要引入（体积）

| 模块 | 说明 |
|------|------|
| Dcm / Dem / FiM | 用 Cdd 自研服务 |
| Com / ComM / CanSM / CanNm | 无应用通信/网络管理 |
| BswM / EcuM / Rte | stub：`EcuM_Stub` + `SchM_*.h` |
| Fee / NvM / MemIf / Fls_17_Dmu | 刷写用 FlsLoader |
| Xcp / Adc / Spi / Pwm / 电机 | APP 专属 |

### 1.3 工程内 BSW / MCAL 目录（现状）

- `BSW364/`：Can、CanIf、CanTp、PduR、Os、Det、VStdLib、`_Common`
- `MCAL364/`：Mcu、Port、Dio、McalLib、Crc、FlsLoader、TC36xA

---

## 2. vLinkGen / MemMap / Tasking

### 2.1 Boot · vLinkGen

| 配置项 | 建议 |
|--------|------|
| `StartupCode_FirstExecInst` | `0x80000000` |
| `CoreExceptions_FirstExecInst` | `0x80000500` |
| Boot `PFlash0_Cached` | 限制在 Boot 区，**勿占满 2MB** |
| APP 预留 | Boot 不链接代码进去 |
| `BMHD0` | 仅 Boot |
| Generate | 更新 `Appl/Source/vLinkGen_Template.lsl` |

### 2.2 APP · vLinkGen（last364）

| 配置项 | 建议 |
|--------|------|
| 代码基址 | APP 区起始 |
| BMHD / FirstExec | **不生成**（留给 Boot） |
| Shared RAM | 与 Boot 同地址 |
| 验收 | `.map` 与 Boot 无重叠 |

### 2.3 MemMap / Tasking

| 项 | 值 |
|----|----|
| Generate Pragmas / Typed Pragmas | ON / ON |
| Near Addressing | OFF |
| Defined symbols | `BRS_COMP_TASKING`、`BRS_PLATFORM_AURIX` |
| Do not use standard copy table | ON |
| LSL | `vLinkGen_Template.lsl` |
| near size | 0 |

---

## 3. 通信诊断栈

### 3.1 数据路径

```text
CAN HW → Can → CanIf（诊断 PDU UL = CAN_TP）
              → CanTp → PduR → Cdd（StartOfReception / CopyRxData / …）
              ← CanTp ← PduR ← Cdd
```

### 3.2 Can

| 项 | 说明 |
|----|------|
| 时钟 | **不在** `CanGeneral` 配 OSC；用 Mcu `McuMCanFrequency` / `McuClockReferencePoint_can` + `CanCpuClockRef` |
| 波特率 | 与整车/DBC 一致（见 `CANFD364.dbc`） |
| `CanCounterRef` | **必须** → `/ActiveEcuC/Os/SystemTimer` |
| `CAN_INTLOCK` | `CAN_APPL` → 需 `ApplCanInterruptDisable/Restore` |

### 3.3 Os（配合 Can）

| 项 | 说明 |
|----|------|
| `SystemTimer` | STM0，PFRT |
| `CounterIsr_SystemTimer` | 入口 `Os_TimerPfrtIsr`（**不要**绑在 `CanIsr_0` 上） |
| 任务 | 至少 Init + Idle；周期任务里调 Can/CanIf/CanTp MainFunction |
| 体积 | Os 是最大头；Debug -O0 会暴涨；Release/-O2；能关的 ORTI/多余对象尽量关 |

### 3.4 CanIf

| 项 | 说明 |
|----|------|
| 诊断 Rx/Tx PDU | User UL = **CAN_TP**，接 CanTp |
| Controller 模式/BusOff | Dispatch UL = **CDD** |
| 回调名 | 工具可能截断，如 `Appl_CanIf_ControllerModeIndicat` |
| **CanIfPublicCfg → Cdd Header Files** | 填 `Appl_CanIf_Cbk.h`（`CanIfPublicCddHeaderFile`），Generate 会自动 `#include`，**不要手改** `CanIf_Lcfg.c` |

### 3.5 CanTp / PduR / Cdd

| 项 | 说明 |
|----|------|
| CanTp | Phys + Func 通道；与 CDD/DBC 寻址一致 |
| PduR | CanTp ↔ Cdd 路由（见 `PduR_Lcfg.c` 中 Cdd 函数表） |
| Cdd 实现 | `BrsMain_Callout_Stubs.c` 现为缓冲桩 → 换成真 UDS |
| 建议服务 | `0x10`、`0x3E`、`0x22`/`0x2E`（按需）、`0x34`/`0x36`/`0x37`、`0x31`（校验/跳转） |

### 3.6 不需要 CanSM / ComM / RTE

控制器启动由 Boot 代码直接 `CanIf_SetControllerMode(... STARTED)`（或等价流程）；SchM 用 `Appl/Include/SchM_*.h`。

---

## 4. FlsLoader（Infineon）

| 项 | 说明 |
|----|------|
| 配置名 | `FlsLoaderPFLASHConfig_0`、`FlsLoaderDFLASHConfig_0`（必须 `_0`） |
| 擦写范围 | **仅 APP 区**；禁止 Boot / BMHD |
| 集成文件 | `FlsLdr_ExclArea.h/.c`（Appl，非 Generate） |
| 调用方 | Cdd 下载流程中调用 FlsLoader API |
| 与 Fls_17_Dmu | **不要**混用进 Boot |

---

## 5. 无 EcuM / RTE 时的 Appl 约定

| 文件 | 内容 |
|------|------|
| `EcuM_Stub.c` | 现 `StartOS`；改为 `Boot_Init` + `StartOS` |
| `SchM_Can.h` 等 | 临界区宏 |
| `SchM_CanIf.h` | 含 AREA_0 宏（因未开 `BRS_ENABLE_CAN_SUPPORT`） |
| `BrsMain.h/.c` | CanSM/ComM MemMap **#if 0** |
| `Compiler_Cfg.h` | `CDD_CODE` / `CDD_APPL_DATA` |
| `Rte_Compiler_Cfg.h` | 占位 |

**Boot_Init 建议顺序：**

```text
Mcu_Init → Port_Init → Dio（按需）→ Can_Init → CanIf_Init
→ PduR_Init → CanTp_Init → FlsLoader_Init → CanIf Start
```

---

## 6. 校验 / 跳转（待实现）

| 项 | 说明 |
|----|------|
| `Boot_CheckAndJumpToApp` | 合法 header/入口/CRC 且无 StayInBoot → 跳 APP |
| StayInBoot | 共享 RAM no-init 或软复位钩子 `BrsMain_SoftwareResetECU_Hook` |
| Jump | 关中断、必要外设停稳、跳 APP 入口不返回 |

调用点建议：`main` 中 `BrsMainInit` 之后、`StartOS` 之前。

---

## 7. 验收

### 体积

- [ ] map：`PFlash0_Cached` Code ≤ 128KB  
- [ ] 不拿 `.hex` 文件大小当 Flash  

### 功能

- [ ] StartOS + SystemTimer 正常  
- [ ] Boot_Init 后 CAN 通信  
- [ ] Cdd 响应 TesterPresent / 会话  
- [ ] 下载仅写 APP 区  
- [ ] 合法 APP 跳转；StayInBoot 留 Boot  
- [ ] Boot/APP map 无重叠  

### 编译回归（Generate 后）

- [ ] Typed MemMap  
- [ ] `CanIfPublicCfg` / Cdd Header Files = `Appl_CanIf_Cbk.h`  
- [ ] 无 ComM MemMap 复活  
- [ ] 新 `.c` 仍在 Tasking 工程中  

---

## 8. 与旧版 A2 文档的差异

| 旧计划（已废弃） | 现行 Slim |
|------------------|-----------|
| Dcm + DigApp SWC | **Cdd** mini UDS |
| Fls_17_Dmu + Fee/NvM | **FlsLoader** |
| EcuM/BswM/Rte/Com/CanSM | **去掉**，stub 替代 |
| Boot 区示例 256KB 且堆全栈 | **代码 ≤128KB**，分区可按产品定 |

详细踩坑与改法见：`Boot_编译链接问题总结.md`。  
操作节奏见：`Boot_功能配置操作指南.md`。
