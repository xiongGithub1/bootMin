# Boot 擦除 Trap 0x8000C060（osTrap_3_Core0 / Class 3）排查与解决

> 工程：`autosarTc364_Boot (2)`
> 现象：UDS `31 01 FF00` 擦除 APP 时，程序停在 `0x8000C060`，指令 `0D 00 00 02`（= `svlcx`）
> 更新日期：2026-08-22

## 1. 现象解读

- `0x8000C060` = `osTrap_3_Core0`，即 Core0 **Class 3（Context Management）Trap 入口**，不是 FlsLoader 返回的错误码。
- `0D 00 00 02` 是 `svlcx`（保存低上下文）的机器码，是 Trap 入口第一条指令，说明 CPU 真的进了 Class 3 异常。

## 2. 排查过程（按时间）

| # | 假设 | 验证结果 |
|---|------|---------|
| 1 | 擦写代码仍在 PFlash0，busy 时同 bank 取指 → Trap | 部分成立：vLinkGen 已把 `FlsLoader_WriteErase` 拷到 PSPR0（`FlsLoader_Erase @ 0x701000b4`），但忙等路径里仍有 Flash 调用残留 |
| 2 | `Mcal_DelayGetTick()` 忙等里调用 Flash 里的真函数 | 已用宏覆盖（见 §3），`FlsLoader.o` 不再引用 Flash 版（`0x80005826`） |
| 3 | `FlsLdr_ExclArea_PfErase_Exit()`（空函数）在 Flash `0x8000290a`，ERASE 位置位后才调用 → 同 bank 取指 | 方案 B 把 Enter/Exit 放进 `FlsLoader_WriteErase` 段后：**Enter 进 PSPR（`0x70100004`），但 TASKING 没把空函数放进指定段，Exit 仍在 Flash**；随后删掉 3 处 Exit 调用，**Trap 依旧** → 同 bank 取指不是（唯一）根因 |
| 4 | **`Mcal_DelayGetTick()` 宏读错地址 `0xF0000010`** | **确认是根因**：STM0_TIM0 应为 `0xF0001010`（见 §3） |

## 3. 根因：FlsLoader_Cfg.h 的 STM0 地址笔误

`Appl\GenData\inc\FlsLoader_Cfg.h` 手加宏块（**DaVinci 重新生成后会被冲掉，需重贴**）：

```c
#ifndef Mcal_DelayGetTick
# define Mcal_DelayGetTick()  ((uint32)(*(volatile uint32 *)0xF0000010u))   // 错：读未实现地址
# define Mcal_DelayGetTick()  ((uint32)(*(volatile uint32 *)0xF0001010u))   // 对：STM0_TIM0
#endif
```

证据：
- `MCAL364\TC36xA\_Reg\IfxStm_reg.h`：`STM0_TIM0 = 0xF0001010`
- `McalLib.c`：`MCAL_GET_STM_TICK() = MODULE_STM0.TIM0.U`
- `Boot_OsFlashTimer.c`：`BOOT_STM0_TIM0 = 0xF0001010`
- 364Motor / last364 的 `IfxStm_reg.h` 一致，确认 `0xF0000010` 是笔误

后果：擦除忙等 `ElapsedTicks = (CurrTicks - BaseTicks)` 永远算不出（读未实现地址返回 0/垃圾）→ 忙等/超时逻辑失效 → 擦除路径异常 / Trap。

## 4. 为什么 smoke 测试能过

`Boot_PFlashSmoke.c` 的擦除叶子：
- 整段 `#pragma optimize 0` + 运行时 memcpy 到 PSPR（`0x70102000`），自包含、零函数调用、零 OS API、零 STM 读取；
- 忙等直接轮询 `DMU_HF_STATUS`（`0xF8040010`）；
- 一次 `Erase Logical Sector Range` 命令擦全部扇区。

FlsLoader 路径依赖 `Mcal_DelayGetTick()`（当时读错地址）→ 一对比就暴露了宏地址问题。

## 5. 已做修改 / 需要维护

- [x] `FlsLoader_Cfg.h`：`0xF0000010` → `0xF0001010`（2026-08-22）
- [x] `FlsLdr_ExclArea.c`：4 个 Enter/Exit 放入 `FlsLoader_WriteErase` 段（Enter 已进 PSPR0 `0x70100004`）
- [x] `FlsLoader.c`：删除 3 处空 `Exit()` 调用（与根因无关，可还原为 Infineon 原始版本）
- [ ] **DaVinci 每次重新生成 FlsLoader 配置 / vLinkGen 后，必须把 §3 手加宏块重新贴回**（2026-08-21 21:01 已实际发生一次被冲掉）

## 6. 若仍 Trap，抓这两个值

停在 `0x8000C060` 时：
1. **TIN**：读 D15（Trap 入口硬件自动写入）。`0=FCD`（CSA 耗尽）、`1=CSU`、`2=CTYP`、`3=NEST`
2. **出错指令地址**：`Os_UnhandledExc` 第 2 参数 `ExceptionInstructionAddress`（或 `Os_Hal_UnhandledExceptionHandler` 的 A4）

---

## 附：last364 独立启动 + UDE 调试

见 `Boot_APP独立启动UDE调试_vLinkGen配置.md`