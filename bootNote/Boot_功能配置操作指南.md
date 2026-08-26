# autosarTc364_Boot 功能配置操作指南

> **工程：** `autosarTc364_Boot`  
> **对照应用：** `last364`  
> **形态：** Slim A2 可编程 Boot（目标 Flash **≤128KB**）  
> **更新日期：** 2026-08-14  
> **编译问题：** 见 `Boot_编译链接问题总结.md`  
> **模块级清单：** 见 `Boot_A2_配置清单.md`

---

## 0. 现状结论（先看清）

当前 Boot **已编译链接通过**，但 **还不是完整 Bootloader**，而是：

| 已有 | 尚未完成 |
|------|----------|
| 精简 BSW：Can / CanIf / CanTp / PduR / Cdd(桩) / Os / Det | 真 UDS 状态机与刷写流程 |
| MCAL：Mcu / Port / Dio / McalLib / Crc / **FlsLoader** | `Boot_Init` 调用链（Mcu→…→Can 启动） |
| BRS 启动 + `EcuM_Stub`→`StartOS` | APP 校验 / JumpToApp |
| 体积约 **41KB ROM**（map） | vLinkGen 正式切出 APP 预留区 |

**刻意不做（为省 Flash）：**  
Dcm、Dem、Com、ComM、CanSM、BswM、EcuM BSW、Rte、Fee/NvM、完整应用栈。

数据路径目标：

```text
CAN → Can → CanIf → CanTp → PduR → Cdd(mini UDS)
                              ↓
                         FlsLoader 擦写 APP 区
```

---

## 1. 已拍板决策

| 项 | 取值 |
|----|------|
| 形态 | A2 Slim（Cdd + FlsLoader，**不用**完整 Dcm） |
| Boot 代码预算 | **≤ 128 KB**（当前 ≈41 KB，余量大） |
| Boot 分区 | `0x80000000` ~ `0x8001FFFF`（128 KB） |
| APP 基址 | `0x80020000` |
| BMHD | 仅 Boot |
| Flash 驱动 | Infineon **FlsLoader**（非 Fls_17_Dmu） |
| 诊断上端 | **Cdd** TP 回调，自研 mini UDS |

---

## 2. 推荐实施顺序

```text
① 保持可编译 Slim 栈（当前） ✓
② EcuM_Stub → Boot_Init：Mcu/Port/Can/CanIf/PduR/CanTp/FlsLoader
③ Cdd：最小 UDS（至少 0x10/0x3E/0x34/0x36/0x37 或产品规定子集）
④ FlsLoader 擦写 APP 区联调
⑤ vLinkGen 分区：Boot/APP 不重叠；APP 工程改基址
⑥ Boot_CheckAndJumpToApp + StayInBoot 标志
⑦ 体积验收：map PFlash ≤128KB；功能验收：刷写后跳 APP
```

---

## 3. 启动链（当前 vs 目标）

### 当前

```text
brsStartupEntry → main → BrsMainInit → EcuM_Init(stub)
  → StartOS → Default_Init_Task → EcuM_StartupTwo(空) → Idle
```

- LED 未开（`BRS_ENABLE_SUPPORT_LEDS` 关）
- **未**调 `Mcu_Init` / `Can_Init` 等 → 板级“业务”尚未跑

### 目标

```text
main → BrsMainInit
  → Boot_CheckAndJumpToApp（合法 APP 且无 StayInBoot 则跳）
  → Boot_Init（Mcu/Port/Can…/FlsLoader）
  → StartOS
  → 周期：Can_MainFunction_* / CanIf / CanTp / PduR / Cdd 调度
```

`EcuM_Stub.c` 中 `EcuM_Init()` 最终应改为调用 `Boot_Init` 再 `StartOS`（或把 Init 放到 Init_Task）。

---

## 4. 如何确认“系统在跑”

### 阶段 A：仅启动框架（当前）

调试器断点顺序：

1. `main` → `BrsMainInit` → `EcuM_Init` / `StartOS`
2. `Default_Init_Task` → 之后 PC 在 Idle
3. `CounterIsr_SystemTimer` 周期性进入 → Os 时钟正常  
若进 `ErrorHook` / `BrsMainExceptionHandler` → 异常。

### 阶段 B：通信就绪后

- CAN 总线有控制器 Start；Tester 发功能寻址 `0x3E 0x00`（或项目 ID）有响应  
- 再测下载服务 / FlsLoader 擦写  

### 不要用

- `.hex` 文件大小判断是否正常  
- 期望 LED 闪（当前未使能 BRS LED）

---

## 5. Flash 体积怎么看

| 看什么 | 路径 |
|--------|------|
| 真实占用 | `Debug/autosar_tc364_Boot.map` → `PFlash0_Cached` Code / `Native used Rom` |
| 不要看 | 资源管理器里 `.hex` KB（ASCII，约为镜像 2～3 倍） |

Debug `-O0` 时 Os 会膨胀；体积吃紧时用 Release / `-O2` 或继续砍 Os 特性。

---

## 6. Boot ↔ APP 职责

| 职责 | Boot | APP（last364） |
|------|------|----------------|
| BMHD / 上电入口 | ✅ | ❌ |
| 校验 & 跳转 | ✅ | ❌ |
| UDS 刷写（Slim Cdd） | ✅ | ❌（可请求进 Boot） |
| 完整应用 / 双核业务 | ❌ | ✅ |

---

## 7. Appl 侧应保留的集成文件

| 文件 | 说明 |
|------|------|
| `EcuM_Stub.c` / `EcuM.h` | 无 EcuM BSW |
| `SchM_*.h` | 无 RTE |
| `FlsLdr_ExclArea.*` | FlsLoader 独占区 |
| `BrsMain_Callout_Stubs.c` | CanIf CDD、Can INTLOCK、Cdd TP 桩 |
| `Appl_CanIf_Cbk.h` | CanIf 回调声明 |
| `Rte_Compiler_Cfg.h` | 占位 |
| `Compiler_Cfg.h` | 含 `CDD_CODE` |

`BrsMain.h/.c` 中 CanSM/ComM MemMap 保持 `#if 0`。

---

## 8. 联调检查清单

- [ ] map：Boot 代码 < 128KB，且落在 Boot 分区内  
- [ ] 调试：能进 StartOS，Idle + SystemTimer 正常  
- [ ] Boot_Init 后 CAN 可通信  
- [ ] Cdd 能收完整 TP SDU 并回正响应（至少 TesterPresent）  
- [ ] FlsLoader 仅擦写 APP 区，不碰 Boot/BMHD  
- [ ] 合法 APP → 冷启动跳转；StayInBoot → 留 Boot  
- [ ] APP 工程 map 与 Boot 无地址重叠  

---

## 9. 相关文档

- `Boot_编译链接问题总结.md` — 已踩坑与改法  
- `Boot_A2_配置清单.md` — DaVinci/模块级配置（Slim）  
- 对照：`last364` 全栈应用配置（勿原样搬进 Boot）
