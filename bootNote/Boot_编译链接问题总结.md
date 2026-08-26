# autosarTc364_Boot 编译 / 链接问题总结

> **工程：** `autosarTc364_Boot`（Tasking VX TriCore + Vector MICROSAR + Infineon MCAL）  
> **产物：** `Debug/autosar_tc364_Boot.elf` / `.hex` / `.map`  
> **形态：** Slim 可编程 Boot（无 Dcm/EcuM/BswM/Rte/Com…，见配置清单）  
> **更新日期：** 2026-08-14

---

## 1. 问题总览

| 序号 | 现象 | 根因 | 处理 | 状态 |
|------|------|------|------|------|
| 1 | `Unknown compiler` / `Compiler not yet supported` | 未定义 `BRS_COMP_TASKING` | Defined symbols：`BRS_COMP_TASKING`、`BRS_PLATFORM_AURIX` | 已解决 |
| 2 | 大量 `ctc W509`：`#pragma section ...` | MemMap 未生成 Typed Pragma | DaVinci：**Generate Typed Pragmas** ON，Near OFF，再 Generate | 已解决 |
| 3 | `BrsMain_CoreConfig*` unresolved | `GenData/BrsHw.h` 假头把版本宏置 0 | 删除 `Appl/GenData/BrsHw.h` | 已解决 |
| 4 | `Appl_Unlock/LockEndinit` unresolved | EndInit 包在 `BRS_ENABLE_CAN_SUPPORT` 内，Boot 未开 | `BrsHw.c` 中 EndInit **始终编译** | 已解决 |
| 5 | `ApplCanInterruptDisable/Restore` unresolved | `CAN_INTLOCK=CAN_APPL`，缺应用回调 | 实现放在 `BrsMain_Callout_Stubs.c`（勿只靠易被 makefile 丢掉的独立 .c） | 已解决 |
| 6 | `BrsMain_Types` 语法错 | `GenData/BrsMain_Types.h` 空壳遮蔽 Include | 删除假头 | 已解决 |
| 7 | `ltc E123`：需要 `_lc_ub_table` | BRS 自定义启动仍用标准 copy table | Linker：**Do not use standard copy table** | 已解决 |
| 8 | 缺 `Rte_Compiler_Cfg.h` / `CDD_CODE` | 无 RTE；Compiler_Cfg 仅有 `_CDD_*` | stub `Rte_Compiler_Cfg.h`；`Compiler_Cfg.h` 增加 `CDD_CODE`/`CDD_APPL_DATA` | 已解决 |
| 9 | CanIf CDD 回调 unresolved / 声明缺失 | Dispatch UL=CDD，未配 Cdd Header | `Appl_CanIf_Cbk.h` + 实现；DaVinci：`CanIfPublicCfg/CanIfPublicCddHeaderFile` = `Appl_CanIf_Cbk.h` | 已解决 |
| 10 | 缺 `SchM_Can/CanIf/CanTp/PduR/Mcu/McalLib.h` | 无 RTE 生成 SchM | `Appl/Include/SchM_*.h` 宏 stub（`SuspendOSInterrupts`） | 已解决 |
| 11 | 缺 `EcuM.h` / `EcuM_Init` | 去掉 EcuM BSW，BRS 仍调 `EcuM_Init` | `Appl/Include/EcuM.h` + `EcuM_Stub.c`（内 `StartOS`） | 已解决 |
| 12 | `MemMap_Common.h`：`No MemMap section found`（编 `vBrs_Lcfg`） | `BrsMain.h` 仍 `#include` `COMM_START_SEC_CODE`，MemMap 无 ComM 段 | `#if 0` 关掉 CanSM/ComM 的 MemMap+原型（`.h` 与 `.c` 都要） | 已解决 |
| 13 | 缺 `FlsLdr_ExclArea.h` | Infineon FlsLoader 集成文件，非工具生成 | `Appl/Include/FlsLdr_ExclArea.h` + `Appl/Source/FlsLdr_ExclArea.c` | 已解决 |
| 14 | `Cdd_*` TP 五个符号 unresolved | PduR UL=Cdd，无实现；独立 `.c` 易被 Tasking 刷新 makefile 丢掉 | 实现写入 **已在工程内的** `BrsMain_Callout_Stubs.c` | 已解决 |
| 15 | `SchM_*_CanIf_*_AREA_0` unresolved | `BRS_ENABLE_CAN_SUPPORT` 未开，`BrsMain.c` 内实现未编译 | `SchM_CanIf.h` 中 AREA_0 改为宏，与 AREA_1…7 一致 | 已解决 |
| 16 | FlsLoader Generate 失败 | 实例名须带 `_0` | `FlsLoaderPFLASHConfig_0` / `FlsLoaderDFLASHConfig_0` | 已解决 |
| 17 | Wdg Generate：STM / CMP 报错 | ResourceM 未分 STM 或指错 `McuStmAllocationConf_1`；CMP 未标 WDG | 见 `Boot_看门狗Wdg配置与问题.md` | 已记录 |
| 18 | 缺 `SchM_Wdg_17_Scu.h` | 无 RTE | `Appl/Include/SchM_Wdg_17_Scu.h` stub | 已解决 |
| 19 | `CanTp_MainFunction` 隐式声明 | `CANTP_RXTX_MAINFUNCTION_API=OFF`，原型在 SchM | `SchM_CanTp.h` 声明 + `Boot_Init.c` include | 已解决 |

---

## 2. 编译器宏 `BRS_COMP_TASKING`

**现象：** `#error "Unknown compiler specified!"`

**处理：** Tasking → Preprocessor → Defined symbols 增加 `BRS_COMP_TASKING`、`BRS_PLATFORM_AURIX`。

---

## 3. MemMap W509（Typed Pragma）

**现象：** `ctc W509: ignored unrecognized "#pragma section MSR_CONST"`

Tasking 需要带类型：`#pragma section farrom "MSR_CONST"`。

**DaVinci：** MemMapGeneral → Generate Pragmas ON、**Generate Typed Pragmas ON**、Near Addressing **OFF** → Generate → Clean Build。

---

## 4. GenData 假头遮蔽

| 假头 | 后果 | 处理 |
|------|------|------|
| `Appl/GenData/BrsHw.h` | `BRSHW_*_VERSION=0` → 不生成 `BrsMain_CoreConfig` | 删除 |
| `Appl/GenData/BrsMain_Types.h` | 类型为空 → 语法错 | 删除 |

**原则：** 不要在 `GenData` 放会抢先于 `Appl/Include` 的同名空头。

---

## 5. EndInit / Can 中断回调

- `Appl_UnlockEndinit` / `Appl_LockEndinit`：在 `BrsHw.c` **始终编译**（不要绑 `BRS_ENABLE_CAN_SUPPORT`）。
- `ApplCanInterruptDisable` / `Restore`：`CAN_INTLOCK=CAN_APPL` 时必需要；当前在 `BrsMain_Callout_Stubs.c`：

```c
void ApplCanInterruptDisable(uint8 Controller)
{
  (void)Controller;
  SuspendAllInterrupts();
}
void ApplCanInterruptRestore(uint8 Controller)
{
  (void)Controller;
  ResumeAllInterrupts();
}
```

---

## 6. 无 RTE / 无 EcuM 的 stub 体系

| 文件 | 作用 |
|------|------|
| `Appl/Include/Rte_Compiler_Cfg.h` | 空/最小，满足 include |
| `Appl/Include/Compiler_Cfg.h` | 含真实 `CDD_CODE`、`CDD_APPL_DATA`（不仅 `_CDD_*`） |
| `Appl/Include/SchM_Can.h` 等 | SchM Enter/Exit → `SuspendOSInterrupts` / `ResumeOSInterrupts` |
| `Appl/Include/EcuM.h` + `EcuM_Stub.c` | `EcuM_Init()` → `StartOS`；后续改为 `Boot_Init` |
| `Appl/Include/Appl_CanIf_Cbk.h` | CanIf CDD：`Appl_CanIf_ControllerBusOff` / `Appl_CanIf_ControllerModeIndicat`（名可能被截断） |

**注意：** Tasking 自动生成的 `subdir.mk` 会在刷新后丢掉**新加**的 `.c`。关键符号优先放进已参与编译的文件（如 `BrsMain_Callout_Stubs.c`），或刷新后确认仍在工程中。

---

## 7. MemMap：`COMM_START_SEC_CODE` → No MemMap section

**现象：**

```text
MemMap_Common.h: #error No MemMap section found in MemMap_Common.h
```

编 `vBrs_Lcfg.c` 时：`BrsHw.h` → `BrsMain.h`，头文件末尾仍有：

```c
#define COMM_START_SEC_CODE
#include "MemMap.h"
```

Slim Boot 的 `MemMap.h` **没有** ComM 的 `COMM_*`（只有 Com 的 `COM_*`）。

**处理：** `BrsMain.h` / `BrsMain.c` 中 CanSM、ComM 的 MemMap + SchM 声明整段 `#if 0`。

---

## 8. FlsLoader 集成：`FlsLdr_ExclArea`

**现象：** `cannot open #include file "FlsLdr_ExclArea.h"`

**说明：** Infineon 要求应用提供；SIP Demo 在  
`.../McalDemo/.../Infra/Integration/FlsLdr_ExclArea.*`  
Vector `MIPconfig.xml` 也排除不改名该文件。

**Boot 放置：**

- `Appl/Include/FlsLdr_ExclArea.h`
- `Appl/Source/FlsLdr_ExclArea.c`（`SuspendAllInterrupts` / `ResumeAllInterrupts`）

FlsLoader 配置实例名须为：`FlsLoaderPFLASHConfig_0`、`FlsLoaderDFLASHConfig_0`。

---

## 9. PduR → Cdd TP 回调

**现象：** `Cdd_StartOfReception` / `CopyRxData` / `TpRxIndication` / `CopyTxData` / `TpTxConfirmation` unresolved

**处理：** 五个函数实现在 `BrsMain_Callout_Stubs.c`（512B 收/发缓冲桩，后续换真 UDS）。声明见 `Appl/GenData/Cdd_Cbk.h`。

---

## 10. CanIf Exclusive Area 0

`vBrsCfg.h` **未定义** `BRS_ENABLE_CAN_SUPPORT` → `BrsMain.c` 里 `SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0` 不编译。

**处理：** `SchM_CanIf.h` 全部 AREA 用宏（含 AREA_0）。改宏后需**重编 CanIf**（旧 `.o` 仍按外部函数引用）。

---

## 11. Linker / 启动检查清单

1. Defined symbols：`BRS_COMP_TASKING`、`BRS_PLATFORM_AURIX`
2. Linker：**Do not use standard copy table**（`--user-provided-initialization-code`）
3. LSL：`Appl/Source/vLinkGen_Template.lsl`
4. near size = 0
5. MemMap：Typed Pragmas ON，Near OFF
6. 无 GenData 假头遮蔽 Include
7. `FlsLdr_ExclArea.c`、`EcuM_Stub.c` 在工程中
8. CanIf：`CanIfPublicCddHeaderFile` = `Appl_CanIf_Cbk.h`（不必手改 GenData）

---

## 12. Flash 大小：`.hex` vs map

| 指标 | 含义 | 本工程参考（2026-08-14） |
|------|------|-------------------------|
| 资源管理器 `.hex` | Intel HEX **文件**体积（ASCII+记录头） | 常为真实镜像 2～3 倍，**不要**当预算 |
| map `PFlash0_Cached` Code | **真实 Flash 代码占用** | ≈ `0xA0E6`（约 **40 KB**） |
| map `Native used Rom` | ROM 合计（含 BMHD/Startup 等） | ≈ `0xA434`（约 **41 KB**） |
| 预算 | Boot 代码目标 | **≤ 128 KB** |

看 Flash 只用 map，不看 hex 文件大小。

---

## 13. 关键路径

| 项 | 路径 |
|----|------|
| 工程 | `autosarTc364_Boot/` |
| 应用 stub | `Appl/Source/BrsMain_Callout_Stubs.c`、`EcuM_Stub.c`、`FlsLdr_ExclArea.c` |
| SchM / EcuM stub | `Appl/Include/SchM_*.h`、`EcuM.h` |
| GenData | `Appl/GenData/`（Can/CanIf/CanTp/PduR/Os/Cdd_Cbk…） |
| BSW | `BSW364/`：Can、CanIf、CanTp、PduR、Os、Det、VStdLib |
| MCAL | `MCAL364/`：Mcu、Port、Dio、McalLib、Crc、FlsLoader |
| map | `Debug/autosar_tc364_Boot.map` |
| 配置说明 | `bootNote/Boot_A2_配置清单.md`、`Boot_功能配置操作指南.md` |

---

## 14. 经验总结

1. Slim Boot 去掉 RTE/EcuM 后，链接错误几乎都是 **缺 stub / 缺 MemMap 段 / makefile 未收录新 .c**。
2. **不要**在 `BrsMain.h` 残留已删除模块（ComM/CanSM）的 MemMap。
3. Infineon **FlsLoader** ≠ Vector Fls_17_Dmu；独占区文件要自己放 Appl。
4. 新 `.c` 写入 Tasking 后务必确认 `Debug/Appl/Source/subdir.mk` 仍包含；关键符号优先并入已有 TU。
5. 评估体积看 **map 的 PFlash Code**，不看 `.hex`。
