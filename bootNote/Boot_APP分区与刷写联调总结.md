# Boot ↔ APP 分区与刷写联调总结

> **工程：** `autosarTc364_Boot (2)`（Boot）+ `last364`（APP）  
> **主题：** Flash 分区、共享握手 RAM、Security seed 死机、CANoe FlashPanel 刷写  
> **更新日期：** 2026-08-20

APP 侧 DaVinci / 头文件 / patch 脚本详见：  
`last364/note/FixNote/Boot共存_vLinkGen与APP头_CRC补丁.md`

---

## 1. 已锁定布局

| 区域 | 地址 | 说明 |
|------|------|------|
| Boot PFlash | `0x80000000`～`0x8001FFFF` | 128 KB；含 BMHD / Startup；**禁止 APP 占用** |
| APP PFlash | `0x80020000`～`0x801FFFFF` | 镜像头 32 B 起 + 代码 |
| BMHD | 仅 Boot（UCB） | APP 工程禁用 `bmiField0` |
| 诊断 CAN | 请求 `0x74C` / 应答 `0x75C` / 功能 `0x7DF`，500 kbit/s | |
| Security 开发桩 | `BOOT_UDS_SECURITY_DEV_STUB=1` → key = `~seed` | |

### 共享 RAM（Boot / last364 必须一致）

| 块 | Offset | Size |
|----|--------|------|
| `DSPR_Core0` | `0x70000000` | **159616** |
| `Variables_Shared` | **`0x70026F80`** | **128** |
| `StartupStack_Shared` | `0x70027000` | 36864 |

握手结构固定在 **`0x70026FC0`（64 B）**，低 64 B 留给 BRS `brsSharedVar`（如 `brsMain_ResetReason`）。

---

## 2. 问题与处理一览

| # | 现象 | 根因 | 处理 |
|---|------|------|------|
| 1 | `ltc E112`：`Brs_Shared_Var_SEC` 要 0x42 B，区只有 64 B | 握手 64 B + BRS ResetReason 挤在同一段 | Shared 扩到 **128** @ `0x70026F80`；栈仍 `0x70027000` |
| 2 | CANoe 会话/安全几乎全红，单条约 2～3 s | ECU 无应答或已死机 | 先看 Trace 有无 `0x75C`；修 CHIPID 后再测 |
| 3 | `27 01` 后进 `Os_Hal_CoreFreeze`，栈在 `Boot_App_MixEntropy` | `SCU_CHIPID` 地址写成 `0xF0036200`（非法） | 改为 **`0xF0036140`**（`IfxScu_reg.h`） |
| 4 | FlashPanel 挂到 Simulation「ECU 3」编译失败 | `testcase` / `TestWaitForTimeout` 只能用于 **CAPL Test Module** | Test Setup → CAPL Test Module |
| 5 | `Output to CAN channel 1 not allowed` / `10 02 failed` | 实车在 **CAN 3**，脚本默认通道 1 | `cCanCh = 3`，`gReq.can = cCanCh` |
| 6 | 擦除停在 `SVLCX` | Boot/APP 同 PFlash0，擦写时代码仍从该 bank 取指 | **vLinkGen：WRITEERASE → PSPR0 COPY_TO_RAM + MemMap pragma** |

---

## 3. Boot 侧关键文件

| 文件 | 作用 |
|------|------|
| `Appl/Include/Boot_Mem.h` | 分区 / APP 头 / 握手定义 |
| `Appl/Source/Boot_App.c` | 镜像校验、跳转、CHIPID+STM 混熵、握手 `@0x70026FC0` |
| `Appl/Source/Boot_FlashProg.c` | `34/36/37`、`31 FF00/FF01/FF02`，仅 APP 窗 |
| `Appl/Source/Boot_Uds.c` | Security；开发桩 `~seed` |
| `Test/FlashPanel/Boot_FlashPanel.can` | CANoe 刷写面板 CAPL |
| `Test/Boot_Dcm_CanoeTest.can` | 协议回归（`gRunFlash=1` 才跑 E 组） |

---

## 4. 操作流程：用 FlashPanel 刷 APP

### 4.1 准备

1. 板子上已烧 **能通诊断的 Boot**（CHIPID 已修）。  
2. last364 已编译，且 **post-build / patch** 成功（头含合法 `length`/`crc32`）。  
3. HEX：`last364\Debug\last364.hex`（或 Release 同路径）。  
4. CANoe：500 kbit/s，通道与 `cCanCh` 一致（本工程 **CAN 3**）。

### 4.2 CANoe 挂载（勿挂 Simulation ECU）

1. **View → Test Setup**  
2. 插入 **CAPL Test Module** → 选 `Test/FlashPanel/Boot_FlashPanel.can`  
3. 导入 `Boot_FlashPanel.vsysvar`，加载 `Boot_FlashPanel.xvp`  
4. **F7** → 先 **Start 测量**，再 Start 该测试模块  
5. 面板确认 HEX 路径 → **Start Flash**

### 4.3 刷写顺序

`10 02` → `27` L1（`~seed`）→ `31 01 FF00` → `34` → `36…` → `37` → `31 FF02` → `31 FF01` →（可选）`11 01`

### 4.4 擦除失败时怎么查

看 Write / Trace 在 `31 01 FF00` 之后：

| 日志 / Trace | 含义 |
|--------------|------|
| `erase: NRC 7F 31 72` | FlsLoader 失败 |
| `erase: NRC 7F 31 33` | 安全未过 |
| `erase: timeout` | 无应答；整片擦很久或擦写中 WDG 复位 |
| `71 01 FF00` | 实际成功 |
| 调试器停在 `SVLCX` / `0x8000Cxxx` | **PFlash0 同 bank 取指 trap**（见下节） |

全 APP 擦约 `0x1E0000`、16 KB 扇区；`FlsLoader_Erase` 第二参是**扇区数**（`0x1E0000/0x4000=120`），不是字节。Watch 里 trap 后的 `Length=0x9FFFF` 多为栈垃圾。

### 4.5 PFlash 同 bank 擦写（现行方案）

Boot 与 APP 同属 **PFlash0**。busy 时不能从该 bank 取指。

**现行（vLinkGen 自动拷贝）：**

1. **DaVinci vLinkGen**  
   - Memory Region：`PSPR0`，`0x70100000`，size `0x8000`  
   - Logical Group：`FlsLoader_WriteErase`，`GLOBAL_CODE`，ROM=`PFlash0_Cached`，RAM=`PSPR0`，Init=`COPY_TO_RAM`  
   - Linker Section Name：`FlsLoader_WriteErase`  
   - PSPR0 Block Content：`RAM_CODE_COPY`  
2. **MemMap**（Appl）：`FLSLOADER_*_WRITEERASE_CODE` → `#pragma section code "FlsLoader_WriteErase"`  
3. 启动代码经 `vLinkGen_Init_One` 把段拷到 PSPR；擦写走 `FlsLoader_Erase` / `FlsLoader_Write`  
4. 忙等：在 `FlsLoader_Cfg.h` 把 `Mcal_DelayGetTick()` 宏成读 `STM0_TIM0`（同 TC234 不 call Flash Delay）；`Mcu_InitClock` 仍用 Flash 里真函数  
5. `ExclArea_Exit` 为空，返回后 `PfBusy_Release`

重编后：`Mcal_DelayGetTick` **不应**再出现在 `0x701xxxxx`；`FlsLoader_Erase` 应在 PSPR。

---

## 5. 流式 CRC vs 镜像头 CRC

| 用途 | 时机 | 说明 |
|------|------|------|
| `Boot_DlCrcOpen` / `Boot_LastCrc` | `36` 边收边算 | 给本次 `31 FF02` CheckMemory |
| APP 头 `length`/`crc32` | 写在 Flash `0x80020000` | **上电跳转**用；会话结束 RAM 状态会丢 |

故仍需编译后 patch（或将来 Boot 收完再写回头）。  
TC3xx **PFlash 擦除态为 `0x00`**（不是 `0xFF`）；patch 空洞按 `0x00` 填。

---

## 6. 建议验证清单

- [ ] Boot 链接：Shared 128 B @ `0x70026F80`，无 `ltc E112`  
- [ ] `27 01` 不死机；CHIPID=`0xF0036140`  
- [ ] FlashPanel 在 **Test Module** + 正确 **CAN 通道**  
- [ ] 擦除有 `71 01 FF00` 或明确 NRC  
- [ ] 刷完复位后 Boot 校验头通过并跳 APP（头已 patch）

---

## 7. 相关笔记

- `Boot_A2_配置清单.md` — 总分区与 Slim 模块范围  
- `Boot_CANoe_CAPL测试问题总结.md` — 协议 CAPL / CanTp / DLC  
- `Boot_看门狗Wdg配置与问题.md` — 长擦写时注意喂狗  
- last364：`note/FixNote/Boot共存_vLinkGen与APP头_CRC补丁.md`
