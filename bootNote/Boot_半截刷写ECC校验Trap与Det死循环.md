# Boot 半截刷写 / 坏 APP 校验 ECC Trap 与 Det 死循环

> **工程：** `boot364` / `autosarTc364_Boot (2)`（Boot）+ `last364`（APP）  
> **主题：** 刷写到一半断电、Flash 残留坏数据时，上电 Boot 校验 APP 触发 PFlash ECC Trap，卡在 `Det_EndlessLoop`  
> **涉及文件：** `Appl/Source/Boot_App.c`  
> **更新日期：** 2026-08-28

---

## 1. 现象

### 1.1 刷写到一半重新上电

- 通过 CAN/UDE 正在下载 APP，**未完成整包刷写**时断电或复位。
- 再次上电后 **不是** 正常「留在 Boot 等 UDS 刷写」，而是调试器显示 CPU 停在：

```text
Det_EndlessLoop()  ← Os_Hal_CoreFreeze()
  ← Os_Hal_UnhandledExc()
  ← Os_Hal_UnhandledExceptionHandler()
  ← Boot_App_IsImageValid() / Boot_App_IsEntryCodeOk()
  ← Boot_App_TryStart()
  ← Boot_Init()
```

- 所有 PC 均在 **`0x8000xxxx`**（Boot 区），说明异常发生在 **Boot 跳转 APP 前的镜像校验**，尚未进入 APP。

### 1.2 未再刷写也会报错

- 若 Flash 中 **仍保留上次半截/损坏的 APP**（magic 可能仍合法），即使本次 **没有发起刷写**，上电同样会 Trap。
- 这不是「本次刷写逻辑错了」，而是 **残留镜像 + 校验读 Flash** 的组合问题。

---

## 2. 根因分析

### 2.1 上电流程

```text
复位 → main → EcuM_Init → Boot_Init
                              └→ Boot_App_TryStart()
                                   └→ Boot_App_IsImageValid()
                                        ├ 读 APP 头 @ 0x80020000
                                        ├ 读 entry 处指令字（原 IsEntryCodeOk）
                                        └ 全镜像 CRC32
                                   合法 → Boot_App_Jump(entry)
                                   非法 → return，留在 Boot（期望行为）
```

### 2.2 半截 APP 在 Flash 里的状态

| 状态 | 说明 |
|------|------|
| 扇区已擦除 | 内容为 **`0x00000000`**（TC3xx PFlash 擦除态为全 0，**不是** 常见 NOR 的 `0xFF`） |
| 部分页写一半 | **ECC 与数据不匹配**（不可纠 UECC） |
| APP 头可能仍在 | `magic = 0xA5C3B007` 仍可能匹配（若头所在页已完整写入） |

> 同工程其它文档亦注明：TC3xx PFlash 擦除态 = `0x00`（见 `Boot_APP分区与刷写联调总结.md`、`last364/note/FixNote/Boot共存_vLinkGen与APP头_CRC补丁.md`）。

Boot 按「完整合法镜像」去读 entry / 跑 CRC 时，访问 **半写区域** 会触发 **PFlash 不可纠 ECC → CPU Trap**。

### 2.3 为何变成 Det 死循环而不是「软失败」

| 环节 | 问题 |
|------|------|
| OS 未启动完整 Trap 处理 | `Boot_App_TryStart()` 在 `StartOS` **之前**调用，无应用级 Trap 恢复 |
| 未处理异常 | 进入 `Os_Hal_UnhandledExc` → `Det_EndlessLoop`，**无法回到 Boot 主循环** |
| 原 `IsEntryCodeOk` | 对 `entry` 做 `*p` 读 Flash，是 **第一个容易踩 UECC 的点** |

### 2.4 第一次加固仍失败的原因（排查记录）

| 尝试 | 结果 | 原因 |
|------|------|------|
| `Appl_UnlockEndinit()` + `CPU0_FLASHCON1 \|= MASKUECC` | 仍 Trap | CPU EndInit 保护寄存器需 **Mcal 正确解锁**；简单 RMW 可能 **未真正写入** |
| 读 `PFI0_ECCS` 判断 ECC | **死在 `Boot_App_PfHadUncorrEcc` 内** | 坏 Flash 访问后 **读 ECC 状态 SFR 本身也可能再 Trap** |
| 仍保留 `Boot_App_IsEntryCodeOk` 读 entry 指令 | Trap 在 `IsEntryCodeOk` | MASKUECC 未生效时，读 entry 即死 |

---

## 3. 解决方案（已实现）

修改 **`Appl/Source/Boot_App.c`** 中 `Boot_App_IsImageValid()` 及辅助函数。

### 3.1 用 Mcal 写 MASKUECC（关 PFlash UECC Trap）

在 **任何 APP 区深度读取之前** 执行（等价于 Vector `BrsHwDisableEccErrorReporting` 中对 `CPU0_FLASHCON1` 的处理）：

```c
#include "McalLib.h"

#define BOOT_CPU0_FLASHCON1           (*(volatile uint32 *)0xF8801104u)
#define BOOT_FLASHCON1_MASKUECC       (0x00010000u)   /* MASKUECC[17:16]=01b */
#define BOOT_FLASHCON1_MASKUECC_BITS  (0x00030000u)

static void Boot_App_MaskPfUeecc(void)
{
  uint32 v;

  v = (BOOT_CPU0_FLASHCON1 & ~BOOT_FLASHCON1_MASKUECC_BITS) | BOOT_FLASHCON1_MASKUECC;
  Mcal_WriteCpuEndInitProtReg((volatile void *)0xF8801104u, v);
#if defined (BRS_COMP_TASKING)
  __dsync();
#endif
}
```

**不要**用 `Appl_UnlockEndinit()` + 直接 `|=` 代替（Boot 极早期可能写不进去）。

### 3.2 禁止读 PFI0_ECCS

- **不要**在 Flash 读失败后读 `PFI0_ECCS`（`0xA8080020`）做「有无 ECC」判断。
- 完整性交给：**magic / length / 范围 / CRC**；失败则 `return FALSE`。

### 3.3 删除 `Boot_App_IsEntryCodeOk`（读 entry 指令字）

- 原逻辑：读 `hdr->entry` 处第一个 `uint32`，排除 `0` / `0xFFFFFFFF`。
- 说明：在 **TC3xx 上擦除态已是 `0x00`**，用「排除 0」无法区分「已擦空」与「合法代码」；且读 entry 本身仍可能 UECC Trap，故已删除该检查。
- 问题：该读操作在 **MASKUECC 未生效或半写 entry 区** 时直接 Trap。
- 现逻辑：仅校验 **entry 地址在 APP 范围内**；**不再 fetch entry 处代码**；镜像合法性由 **CRC** 保证。

### 3.4 MASKUECC 未生效则不再深读

```c
Boot_App_MaskPfUeecc();
hdr = Boot_App_Hdr();
if (hdr->magic != BOOT_APP_HDR_MAGIC) { return FALSE; }
if (Boot_App_IsPfUeeccMasked() != TRUE) { return FALSE; }  /* 安全留在 Boot */
/* 再 length / CRC … */
```

### 3.5 CRC 使用 cached 视图

- CRC 扫描使用 **`0x80020000` cached 视图**（`BOOT_FLASH_APP_START`），在 MASKUECC 已确认生效后读取。

---

## 4. 期望行为（修复后）

| 场景 | 修复前 | 修复后 |
|------|--------|--------|
| APP 完整合法 | 跳 APP | 跳 APP（不变） |
| APP 区擦空 / magic 不对 | 留 Boot（擦除后全 `0x00`，magic 通常为 0） | 留 Boot（不变） |
| APP 刷到一半 / ECC 坏 | **Det_EndlessLoop** | **留 Boot**，可 UDS 擦除重刷 |
| 未刷写但 Flash 有旧坏镜像 | **Det_EndlessLoop** | **留 Boot** |

---

## 5. 联调与恢复步骤

1. **重新编译并烧录 Boot**（只改 APP 不够，必须更新 Boot 镜像）。
2. 若板子已卡死：调试器复位；必要时手动擦 APP 区。
3. 通过 UDS：**先 Erase APP（`0x80020000` 起）**，再 **完整下载**，不要中途断电。
4. 调试器可确认 MASKUECC（与 UDE 脚本一致）：

```text
set CPU0_FLASHCON1 0x10000
```

5. 观察 `CPU0_FLASHCON1` bit `[17:16]` 非 0，表示 MASKUECC 已置位。

---

## 6. 可选后续加固（未做 / 建议）

| 项 | 说明 |
|----|------|
| **Commit 顺序** | 刷写时 **最后写 magic**（`0xA5C3B007`）；中途断电 magic 无效，Boot 只读头即失败，无需扫 CRC |
| **Boot 极早期 MASKUECC** | 在 `Boot_Init()` 最开头、`Boot_App_TryStart()` 之前再调一次 `Boot_App_MaskPfUeecc()`（双保险） |
| **启用 `BRS_ENABLE_FBL_SUPPORT`** | 可调用 `BrsHwDisableEccErrorReporting()`，但当前工程该宏为 **关闭**，故在 `Boot_App.c` 内自实现 |

---

## 7. 相关文档

| 文档 | 内容 |
|------|------|
| `Boot_APP分区与刷写联调总结.md` | 分区、握手 RAM、CAN 刷写 |
| `Boot_擦除Trap_0x8000C060_排查总结.md` | 擦除路径 Trap（STM 地址笔误等） |
| `last364/note/FixNote/Boot共存_vLinkGen与APP头_CRC补丁.md` | APP 头、CRC patch、vLinkGen |

---

## 8. 变更记录

| 日期 | 说明 |
|------|------|
| 2026-08-28 | 初版：半截刷写 ECC Trap、`PFI0_ECCS` 误读、`Mcal_WriteCpuEndInitProtReg`、移除 `IsEntryCodeOk` |
| 2026-08-28 | 修正：TC3xx PFlash **擦除态为 `0x00`**，非 `0xFFFFFFFF` |
