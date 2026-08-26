# Boot 看门狗（Wdg）配置与问题记录

> **工程：** `autosarTc364_Boot (2)`  
> **驱动：** Infineon `Wdg_17_Scu` + Vector `WdgIf`  
> **触发定时器：** `STM_TIMER`（非 GTM）  
> **更新日期：** 2026-08-17

---

## 0. Boot 要不要加 Wdg？

| 阶段 | 建议 |
|------|------|
| 联调 UDS / 刷写 | 可暂不加，少踩 STM/ResourceM 生成坑 |
| 量产前 | **建议加**：卡死/擦写异常时可复位；注意刷写长操作超时与喂狗 |

本文记录的是 **已加入 Wdg 后** 的 DaVinci 配置要点、**当前超时/喂狗时间**、与踩坑。

---

## 1. 正确配置一览（CORE0）

Wdg 选 `STM_TIMER` 时，生成脚本会校验：**ResourceM 给该核分配了 STM，且 MCU 上该 STM 的 CMP 标明给 WDG 用**。

### 1.1 Wdg 模块（`last364_Wdg_Wdg_ecuc.arxml`）— 当前工程取值

| 项 | 当前值 | 说明 |
|----|--------|------|
| `WdgTriggerTimerSelection` | `STM_TIMER` | 用 STM 比较中断自动喂硬件 |
| `WdgCoreId` | `0` | CORE0 |
| `WdgDefaultMode` | `WDGIF_SLOW_MODE` | Init 后进入 Slow |
| `WdgDisableAllowed` / `WdgCPUDisableAllowed` | `false` | 不允许切 OFF |
| `WdgInitialTimeout` / `WdgCPUInitialTimeout` | **5 s** | Init 后软件存活时间（生成 5000 ms） |
| `WdgMaxTimeout` / `WdgCPUMaxTimeout` | **32 s** | `SetTriggerCondition` 上限（生成 32000 ms） |
| `WdgSlowModeTimeoutValue` | **0.02 s（20 ms）** | Slow 硬件超时窗口 |
| `WdgFastModeTimeoutValue` | **0.01 s（10 ms）** | Fast 硬件超时窗口 |
| `WdgSlowRefreshTime` | **0.015 s（15 ms）** | Slow 下 STM 喂硬件周期 |
| `WdgFastRefreshTime` | **0.007 s（7 ms）** | Fast 下 STM 喂硬件周期 |
| `WdgCPUInitialPassword` | `60` | 硬件密码 |
| `WdgTriggerMode` | `WDG_WINDOW` | 窗口模式 |
| `WdgSystemClockRef` | Mcu 时钟参考点 | 算 reload / STM 用 |

**硬性规则：** 同模式下 `RefreshTime < ModeTimeout`（当前 Slow 15&lt;20、Fast 7&lt;10，合法）。

生成核对：`Appl/GenData/src/Wdg_17_Scu_PBcfg.c`  
→ `InitialTimeout=5000`，`MaxTimeout=32000`，`SlowRefresh=15`，`FastRefresh=7`，`DefaultMode=WDGIF_SLOW_MODE`，STM CmpRegId=`0x1`（CMP1）。

### 1.2 ResourceM（关键）

路径：`ResourceM` → `ResourceMMcalConfig_0` → `ResourceMMcalCore_0`（**CORE0**）→ 新建 **Allocation**：

| 项 | 取值 |
|----|------|
| `ResourceMModuleName` | **`STM`** |
| `ResourceMResourceRef` | **`/Mcu/Mcu/McuHardwareResourceAllocationConf_0/McuStmAllocationConf_0`** |

- CORE0 用 **STM0** → 必须指向 **`McuStmAllocationConf_0`**  
- **不要**指到 `McuStmAllocationConf_1`（那是 STM1，报错文案里会写成 `STM timer 1`）

磁盘文件：`Config/ECUC/last364_ResourceM_ResourceM_ecuc.arxml`  
容器名示例：`ResourceMAllocation_STM0`

### 1.3 Mcu STM 比较寄存器

路径：`Mcu` → `McuHardwareResourceAllocationConf_0` → **与 ResourceM Ref 同一条** `McuStmAllocationConf_*`

| 寄存器 | 建议（Boot） | 说明 |
|--------|----------------|------|
| `McuStmCmp0RegAllocationConf` | `STM_CMP0_NOT_USED` | Os `SystemTimer` 已用 **STM0_Ch0**，避免与 Wdg 抢 CMP0 |
| `McuStmCmp1RegAllocationConf` | **`STM_CMP1_USED_BY_WDG`** | 给 Wdg 自动喂狗/刷新定时 |

Infineon Demo 常用 CMP0 给 WDG；本工程因 Os 已占 Ch0，优先 **CMP1**。

校验逻辑（生成模板 `Wdg_17_Scu.m`）要求 **Cmp0 或 Cmp1 至少一个** 为 `*_USED_BY_WDG`。

### 1.4 对应关系示意

```text
Wdg (CORE0, STM_TIMER)
    │
    ▼
ResourceM / CORE0 / Allocation
    ModuleName = STM
    ResourceRef ──► McuStmAllocationConf_0          ◄── 必须是 _0（STM0）
                         │
                         ├─ CMP0: NOT_USED（留给 Os STM0_Ch0）
                         └─ CMP1: STM_CMP1_USED_BY_WDG
```

---

## 2. 超时与喂狗时间（当前配置详解）

### 2.1 三层时间（不要混）

```text
硬件窗口（ModeTimeout）     Slow 20 ms / Fast 10 ms
        ▲ 必须比 Refresh 大
STM 自动喂硬件（Refresh）   Slow 15 ms / Fast 7 ms     ← Wdg_17_Scu_Isr
        ▲
软件存活（应用续命）         Init 先给 5 s；之后靠
                            SetTriggerCondition(ms)     ← 应用周期调用
上限 MaxTimeout              单次参数 ≤ 32 s
```

| 名字 | 配哪里 | 当前值 | 作用 |
|------|--------|--------|------|
| ModeTimeout | DaVinci Slow/Fast | 20 ms / 10 ms | 硬件多久不服务就复位 |
| RefreshTime | DaVinci TriggerTimer | 15 ms / 7 ms | STM 多久自动喂一次硬件 |
| InitialTimeout | DaVinci | **5 s** | Init 后白送的软件存活时间 |
| MaxTimeout | DaVinci | **32 s** | `SetTriggerCondition` 允许最大值 |
| `SetTriggerCondition(ms)` | **应用代码** | （建议见下） | 之后每次续软件存活时间 |

驱动逻辑（STM）：`Init`/`SetTriggerCondition` 把超时换成计数  
`TimeoutCounter ≈ timeout_ms / RefreshTime_ms`；  
每次 `Wdg_17_Scu_Isr`：若 Counter&gt;0 则喂硬件并 Counter−−；为 0 则停止喂硬件 → 等硬件窗口后复位。

### 2.2 为何 Init 后不调喂狗也能跑一阵？

1. **InitialTimeout=5 s**：这段时间内 STM ISR（若已接通）会自动喂硬件。  
2. **调试器连接**：Aurix 常挂起/禁用 CPU WDT，脱调试器才能验证真复位。  
3. **Os 需挂 STM0 CMP1 → `Wdg_17_Scu_Isr`**：否则自动喂硬件路径不完整。

超过约 5 s 仍不调用 `SetTriggerCondition`，设计上应停止续命并最终复位（无 debugger 时）。

### 2.3 应用侧喂狗怎么配（推荐）

`Boot_Init.c` 已有：`Wdg_17_Scu_Init(&Wdg_17_Scu_Config_0);`  
主循环（如 1 ms `OsTask_MainFunction` → `Boot_ComMainFunctions`）应周期调用：

```c
/* 每 1 ms 喂一次，每次续 100 ms（<< MaxTimeout 32000） */
Wdg_17_Scu_SetTriggerCondition(100u);
/* 或：WdgIf_SetTriggerCondition(0u, 100u); */
```

| 项 | 建议 |
|----|------|
| 调用周期 `T_feed` | 与 Task 一致（本工程约 **1 ms**） |
| 参数 `timeout_ms` | 约 **(5～20)×T_feed**，且 **≤ 32000**；日常可用 **100** |
| 刷写长操作 | 擦写循环内继续喂，或临时加大（如 5000），仍 ≤ 32000 |
| 单位 | API 为 **毫秒**；DaVinci 浮点多为 **秒** |

### 2.4 改时间时改哪

| 想改的效果 | 改什么 |
|------------|--------|
| Init 后更久才必须开始周期喂狗 | ↑ `WdgInitialTimeout`（秒） |
| 允许一次续命更长（大块擦写） | ↑ `WdgMaxTimeout`（秒） |
| STM 喂硬件更勤/更疏 | `WdgSlow/FastRefreshTime`（须仍 &lt; ModeTimeout） |
| 硬件更敏感/更宽松 | `WdgSlow/FastModeTimeoutValue` |
| 运行中实际存活窗口 | 代码里 `SetTriggerCondition` 的 ms 与调用频率 |

改 DaVinci 后 **Generate**，再核对 `Wdg_17_Scu_PBcfg.c`。

---

## 3. 生成错误与处理

### 3.1 `STM timer has to be allocated to CORE0 in Resource Manager`

**含义：** CORE0 下没有 `ResourceMAllocation`，或有 Allocation 但没有 `ModuleName=STM`。

**处理：** 按 §1.2 增加 STM 分配并指向 `McuStmAllocationConf_0`。

### 3.2 `STM timer 1 compare register is not configured for WDG ... CORE0`

**含义：** ResourceM 已指向某个 `McuStmAllocationConf_N`，但该容器上 **CMP0/CMP1 都不是 `USED_BY_WDG`**。

文案里的 **`timer 1`** 来自路径名拆分：引用了 **`McuStmAllocationConf_1`**，而不是 `_0`。

**处理（二选一，推荐 A）：**

- **A（推荐）：** ResourceRef 改成 **`McuStmAllocationConf_0`**，并在 **Conf_0** 上设 `STM_CMP1_USED_BY_WDG`  
- **B：** 若坚持用 Conf_1，则必须在 **Conf_1** 上设 `USED_BY_WDG`（CORE0 绑 STM1 一般不符合习惯）

### 3.3 DaVinci 与磁盘 ARXML 不同步

现象：Cursor/磁盘已改 `last364_ResourceM_*.arxml`，Generate 仍报旧错；或 Save 后又把 ResourceM 存成“空 CORE0”。

**处理：**

1. 在 DaVinci **Reload / 重新打开工程**，确认 UI 里 Allocation / CMP 与 §1 一致  
2. **以 UI 配置为准** 再 Save + Generate  
3. 仅改 ARXML 而不 Reload，生成仍用工程库里的旧配置

### 3.4 编译：`cannot open #include file "SchM_Wdg_17_Scu.h"`

无 RTE 时不会自动生成 SchM。已增加 Boot stub：

- 文件：`Appl/Include/SchM_Wdg_17_Scu.h`  
- 内容：`TimerHandling` / `ChangeMode` / `CpuEndInit` 的 Enter/Exit → `SuspendOSInterrupts` / `ResumeOSInterrupts`

驱动实际使用：`SchM_Enter/Exit_Wdg_17_Scu_TimerHandling`、`..._CpuEndInit`。

### 3.5 编译警告：`implicit declaration of function "CanTp_MainFunction"`（顺带）

与 Wdg 同批编译时出现：`CANTP_RXTX_MAINFUNCTION_API = STD_OFF` 时 **`CanTp.h` 不声明** 合并版 `CanTp_MainFunction`（RTE 工程靠 `SchM_CanTp.h`）。

**处理：**

- `Appl/Include/SchM_CanTp.h` 中声明 `void CanTp_MainFunction(void);`  
- `Boot_Init.c` `#include "SchM_CanTp.h"`  
- 实现仍在 `CanTp.c`，可继续在 `Boot_ComMainFunctions` 里调用

---

## 4. 集成清单（配置通过后）

| 步骤 | 当前状态 / 说明 |
|------|-----------------|
| 源文件进工程 | `Wdg_17_Scu.c`、`Wdg_17_Scu_PBcfg.c`、`WdgIf_Lcfg.c` 等 |
| Init | `Boot_Init.c`：`Wdg_17_Scu_Init(&Wdg_17_Scu_Config_0)` |
| 周期喂狗 | 应在 1 ms Task 调 `SetTriggerCondition(100)`（若未加则仅靠 Initial 5 s） |
| 中断 | Os：STM0 **CMP1** → `Wdg_17_Scu_Isr`，并 Enable |
| 刷写 | 擦写循环内继续喂狗，或临时加大 timeout（≤ 32 s） |
| 验证 | **脱调试器** 跑；连 debugger 时常不复位 |

调试时一停步就复位属正常；联调可用调大 InitialTimeout / 周期喂狗窗口。

---

## 5. 相关文件

| 文件 | 用途 |
|------|------|
| `Config/ECUC/last364_Wdg_Wdg_ecuc.arxml` | Wdg 超时/Refresh/模式（§1.1 / §2） |
| `Config/ECUC/last364_ResourceM_ResourceM_ecuc.arxml` | CORE0 ← STM0 |
| `Config/ECUC/last364_Mcu_Mcu_ecuc.arxml` | `McuStmAllocationConf_*` CMP |
| `Appl/Include/SchM_Wdg_17_Scu.h` | 无 RTE 临界区 stub |
| `Appl/Source/Boot_Init.c` | `Wdg_17_Scu_Init` |
| `Appl/GenData/src/Wdg_17_Scu_PBcfg.c` | 生成后的数值核对 |
| `MCAL364/Wdg_17_Scu/ssc/src/Wdg_17_Scu.c` | 驱动源 |

生成模板校验位置（只读）：  
`CBD2200508_D00/.../Wdg_17_Scu_Aurix2G/generate/template/Wdg_17_Scu.m` → `Wdg_StmTimerValidation`

---

## 6. 快速检查表（Generate / 联调前）

- [ ] ResourceM CORE0 有 Allocation，`ModuleName=STM`  
- [ ] ResourceRef = **`McuStmAllocationConf_0`**（不是 `_1`）  
- [ ] 同一 Conf 上 Cmp0 或 Cmp1 = **`*_USED_BY_WDG`**（Boot 建议 Cmp1）  
- [ ] Wdg：`CoreId=0`，`STM_TIMER`，Slow Refresh **15 ms** &lt; Mode **20 ms**  
- [ ] Initial **5 s** / Max **32 s** 符合产品  
- [ ] `PBcfg` 与 DaVinci 一致  
- [ ] 工程含 `SchM_Wdg_17_Scu.h`  
- [ ] 主循环有周期 `SetTriggerCondition`  
- [ ] Os 已接 `Wdg_17_Scu_Isr`（STM0 CMP1）  
- [ ] 真复位验证在无 debugger 下进行  
