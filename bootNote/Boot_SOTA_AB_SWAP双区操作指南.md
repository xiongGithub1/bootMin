# boot364 + last364：A/B SWAP 双区（Boot+APP）操作指南

> **目标工程：** `boot364`（Boot）+ `last364`（APP）  
> **芯片前提：** **TC364 · TQFP-144 · PFlash 4MB**（Datasheet：`Program Flash Size 4 MB`，`Banks 2 x 2 MB`）  
> **参考资料：**  
> - `last364/infineon-sak-tc36xdp-datasheet-en.pdf`（TC36x 平台：4MB = 2×2MB）  
> - TC36x UM Memory Map：PFI0 @ `0x80000000`/`0xA0000000`，PFI1 @ `0x80300000`/`0xA0300000`（各 2MB）  
> - `Swap/AP32404-Tutorial_Using_the_2nd_Generation_AURIX_SWAP_mechanism_for_SW_updates_Over_The_Air_v1.1.pdf`  
> - `Swap/506_SOTA_SWAP and Secure_Boot_v0.1.pdf`（同类 **2×2MB → SWAP 后 2MB/2MB**）  
> - `Swap/illD-Swap_1_KIT_TC397_TFT`（UCB 写流程 Demo，芯片为 TC397，逻辑可移植）  
> - AURIX TC3xx UM §1.5 Software over the Air (SOTA)  
> **状态：** 操作设计文档；地址表已按 **本板 4MB** 校正（勿再用旧稿的 1MB/1MB、`0x80100000` 当 B 区）  
> **日期：** 2026-09-04

---

## 0. 一句话结论

要把现在的 Boot+APP 做成 **双区 OTA**：

1. **镜像体积压进每个 Bank 的 2MB**（本芯片 4MB = 2×2MB；开 SWAP 后 A/B 各 2MB，不是 1MB）。  
2. **A/B 各烧一份完整「Boot + APP」**（逻辑链接地址相同，始终按 A 标准图 `0x80000000` 起）。  
3. **OTA 只擦写物理“非激活 Bank”**，校验通过后写 `UCB_SWAP`，再发 **System Reset**。  
4. **先写好合法 UCB_SWAP，再开 SWAPEN**——顺序反了可能永久卡在复位。

下面按「为什么 → 怎么做 → 落点文件」展开。

---

## 1. 为什么要双区 + 每区都有 Boot+APP

### 1.1 Infineon A/B SWAP 在解决什么

| 点 | 说明 | 为何重要 |
|----|------|----------|
| 读写分离 | 激活组执行，非激活组可擦写 | 运行中可写新固件，停机时间只剩一次复位（506 / AP32404） |
| 逻辑地址不变 | 切 Bank 只改映射，不拷贝代码 | Boot/APP 链接地址始终按 **A 区标准地址图** 编译 |
| 写走物理地址 | DMU 擦写永远用 **标准物理地址** | Boot 刷写必须按当前激活态换算 inactive 物理基址（UM §1.5） |
| System Reset 生效 | Application Reset **无效** | UDS `11 01` 若只是 App Reset，Swap 不会生效 |

### 1.2 为何「双区都是 Bootloader + APP」

开 SWAP 后，CPU 每次只执行 **一组 Bank**。复位后逻辑窗口仍是 `0x80000000…`，但背后可能是物理 A 或物理 B。

因此：

- **每个物理 Bank 都必须能独立启动**：含 Boot（启动/诊断/刷写/跳转）+ APP。  
- 只刷 APP、不刷 Boot 到 inactive 区：若两区 Boot 版本不一致，可能出现“切过去能跑 APP、诊断/回滚行为却不同”。推荐 **整区镜像（Boot+APP）成对更新**；若 Boot 长期不变，至少保证 inactive 区仍有一份可工作的 Boot。  
- 506 文档也建议：更新失败/挂死时，用 **始终可用的 Bootloader** 根据外部条件强制写回上一份 SWAP 配置。

### 1.3 本板：TC364 TQFP-144 · PFlash 4MB（与旧稿 / TC397 Demo 的差别）

Datasheet（TC36x Platform Feature Overview）：

| 项 | 本板 |
|----|------|
| Program Flash | **4 MB** |
| Banks | **2 × 2 MB**（PF0 + PF1） |
| 封装 | **TQFP-144** |

SWAP 能力（对齐 506「4MB = 2×2MB」类器件，MemTool 亦见 `Pflash0/1 Sectors = 128`×16KB）：

| 状态 | 可用空间 |
|------|----------|
| SWAP **关闭** | 连续观感约 **4MB**（两物理 Bank） |
| SWAP **开启** | **2MB / 2MB**（Group A ↔ Group B） |

> **注意：** 旧稿曾按「TC364DP-48 → 3MB → SWAP 后 1MB/1MB」写，**不适用于本板 4MB**。  
> 另有部分 TC364 衍生物是 2MB+1MB；**以你芯片 Datasheet / MemTool 扇区数为准。**

物理标准地址图（**NVM 擦写永远用此图**，UM Memory Map）：

| 物理 Bank | Cached | Non-cached（MemTool / FlsLoader） | 大小 | SWAP 角色 |
|-----------|--------|-----------------------------------|------|-----------|
| PF0 | `0x80000000` | `0xA0000000` | **2MB** | Group **A**（MARKER=`0x55` / standard） |
| PF1 | **`0x80300000`** | **`0xA0300000`** | **2MB** | Group **B**（MARKER=`0xAA` / alternative） |

**禁止**把 B 区当成 `0x80100000` / `0xA0100000`——那仍在 **PF0 的第 2MB** 内，不是 PF1。

FlsLoader：非缓存 = cached + `0x20000000`（`0x8xxxxxxx` ↔ `0xAxxxxxxx`）。

---

## 2. 推荐双区内存布局（逻辑视图）

### 2.1 链接/执行始终按 A 区标准地址（AP32404）

**所有 `.elf/.hex` 只按 Group A 地址生成一次**，不要为 B 区另做一套链接脚本。

```
逻辑地址（A 标准图，Boot/APP 工程共用；本板 SWAP 后每区 2MB）
┌──────────────────────────────────────────────┐
│ 0x80000000 .. 0x8001FFFF  Boot 128KB         │  Startup + FBL（BMHD 在 UCB）
│ 0x80020000 .. 0x801FFFFF  APP  ~1920KB       │  32B 头 + 镜像
└──────────────────────────────────────────────┘
合计 ≤ 2MB（0x80000000 .. 0x801FFFFF）
```

| 宏（建议改 `Boot_Mem.h`） | 说明 | SWAP 双区后 |
|---------------------------|------|-------------|
| `BOOT_FLASH_BOOT_*` | Boot 128KB | **保持** `0x80000000`～`0x8001FFFF` |
| `BOOT_FLASH_APP_START` | APP 头 | **保持** `0x80020000` |
| `BOOT_FLASH_APP_END` | APP 末 | **`0x801FFFFF`**（本板 2MB/2MB；旧稿误写成 `0x800FFFFF` 的 1MB 上限） |

> **为什么不把 Boot 放到每区不同地址？**  
> SWAP 只改“哪块物理 Flash 映射到同一逻辑窗口”。链接地址必须两边一致，否则切 Bank 后入口/向量全错。

### 2.2 物理烧写视图（OTA 时 Boot 必须按此换算）

读 `SCU_SWAPCTRL.B.ADDRCFG`（`0xF003614C`）：

| ADDRCFG | 含义 | 当前执行物理区 | OTA 擦写目标（inactive） |
|---------|------|----------------|---------------------------|
| `1` | A 激活（`0x55`） | PF0 @ `0x80000000` | PF1：逻辑偏移 + **`0x00300000`** → 基址 **`0x80300000`** |
| `2` | B 激活（`0xAA`） | PF1 映射到逻辑 `0x800…` | PF0：逻辑地址 **原样**（物理 A） |
| 其它 | 非法 | — | 禁止写 UCB / 禁止跳 APP |

地址换算（推荐实现）：

```text
logical = 0x80000000 + offset          // offset ∈ [0, 0x200000)  // 本板每区 2MB
if (ADDRCFG == 1)  // A 跑着，刷 B
    physical = 0x80300000 + offset     // 或 logical + 0x00300000
else if (ADDRCFG == 2) // B 跑着，刷 A
    physical = 0x80000000 + offset
```

例：要更新逻辑 APP `0x80020000`：

- A 激活 → 写物理 **`0x80320000`**（或 `0xA0320000`）  
- B 激活 → 写物理 `0x80020000`  

Boot 刷到 B：

- A 激活 → 写物理 **`0x80300000`**（或 `0xA0300000`）

**为什么必须换算：** UM 写明 NVM 擦写永远走 **物理标准地址图**，与当前映射无关；写错会毁掉正在运行的 Bank。

### 2.3 双区内容应对齐什么

| 内容 | A 物理 | B 物理 | 说明 |
|------|--------|--------|------|
| Boot 镜像 | `0x80000000` / `0xA0000000` | **`0x80300000` / `0xA0300000`** | 建议同版本；至少都能进编程会话 |
| APP 头+体 | `0x80020000` / `0xA0020000` | **`0x80320000` / `0xA0320000`** | OTA 主要更新对象；CRC/头规则同现网 |
| BMHD（UCB） | `UCB_BMHD*` | 同一份 UCB | BMHD 在 UCB，**不随 PFlash Bank 复制**；STAD 仍指逻辑 `0x80000000` |
| `UCB_SWAP` | ORIG+COPY | — | MARKER `0x55`=A / `0xAA`=B（MemTool 显示为 standard / alternative） |

---

## 3. 与现行工程差异（迁移前必读）

| 项 | 现行 boot364/last364 | SWAP 双区后（本板 4MB） |
|----|----------------------|---------------------------|
| APP 末端 | 多为 `0x801FFFFF` | **仍可用 `0x801FFFFF`**（每区 2MB）；勿再按 1MB 砍到 `0x800FFFFF` |
| 刷写目标 | 固定逻辑 APP 窗 | **inactive 物理窗**（B=`0x80300000+`） |
| 刷写内容 | 主要刷 APP | 推荐 **Boot+APP 整区** 或至少保证 inactive Boot 可用 |
| 复位后跳转 | 校验 `0x80020000` 头 | 逻辑不变；物理已由 SWAP 切换 |
| UCB | 仅 BMHD 等 | 新增 `UCB_SWAP` + `PROCONTP.SWAPEN` |
| PFlash 同 bank 擦写 | 已把 FlsLoader 拷 PSPR | inactive 擦写仍建议保持 **WriteErase 在 RAM**（安全） |
| 性能 | 本地 PFlash 快路径可用 | 开 SWAP 后 SSW 会关本地快路径，性能可能下降（506/AP32404） |

**本板不要按「缩到 1MB」做 Phase1**；镜像只要 ≤ **2MB/区** 即可。误把 B 刷到 `0x80100000` 才会“有数据却切不过去”。

---

## 4. 分阶段操作（推荐顺序）

整体流程对齐 AP32404「Basic flow」+ UM「Initial / Runtime SWAP」：

```text
Phase0 评估体积
Phase1 改链接分区（仍可不开 SWAP）
Phase2 产线/实验室：A 区烧完整镜像 + 配 UCB_SWAP(A) + 开 SWAPEN
Phase3 把同一镜像再写到 B 物理区（首套双备份）
Phase4 改造 Boot 刷写：只写 inactive + CheckMemory + 写 UCB_SWAP + System Reset
Phase5 回滚 / 安全策略
```

---

### Phase 0 — 评估（为什么先做）

**操作**

1. 看 `last364` map：代码+常量是否 **≤ ~1920KB**（APP：`0x80020000`～`0x801FFFFF`）。  
2. 看 `boot364` map：是否仍 **≤ 128KB**。  
3. 若超：裁剪、拆段、或放弃 SWAP。

**为什么：** 本板 SWAP 开启后每区 **2MB**；超了装不进对应物理 Bank。

---

### Phase 1 — 链接与分区确认（仍可不启用 SWAP）

**操作**

1. **`boot364/Appl/Include/Boot_Mem.h`**  
   - `BOOT_FLASH_APP_END` → **`0x801FFFFF`**（本板 2MB/区；若曾误改成 `0x800FFFFF` 请改回）  
   - 保留握手 RAM（`0x70026FC0`）。  
2. **`last364` vLinkGen / LSL**  
   - 逻辑布局仍在 `0x80000000`～`0x801FFFFF`  
   - **禁止**把工程链接到物理 B（`0x80300000` / `0xA0300000`）；B 只在烧录时做落点偏移  
3. 保持：APP **不生成 BMHD**；Boot 独占 BMHD（UCB）。  
4. 重编 last364，确认 post-build `patch_app_header` 仍写 `0x80020000`。  
5. 用现 FlashPanel **单区方式**再刷一轮，确认功能正常。

**为什么：** 本板不必「缩到 1MB」；先保证 A 逻辑布局正确，再开 SWAP / 镜像 B。UCB/SWAPEN 误配会导致 **永久复位**（AP32404 重点警告）。

---

### Phase 2 — 首次启用 SOTA（实验室/产线一次性）

严格按 UM / AP32404 **Initial device configuration**：

| 步骤 | 做什么 | 为什么 |
|------|--------|--------|
| 2.1 | 调试器/产线工具把 **Boot+APP** 烧到 **物理 A**（`0x80000000` 起 **2MB**） | 交付态先跑标准地址图 |
| 2.2 | 配置 `UCB_BMHD` 入口为逻辑 `0x80000000` | SSW 启动仍靠 BMHD；**不要**改成 `0x80300000` |
| 2.3 | 写 `UCB_SWAP_ORIG`（建议同步 COPY）首条：MARKERL=`0x55`，CONFIRMATIONL=`0x57B5327F`，MARKERH/CONFIRMATIONH 填对应字段地址 | 明确下次映射为 A；无合法条目就开 SWAP 会砖 |
| 2.4 | （可选）`UCB_PFLASH` 写保护激活 Bank | 防误擦运行区 |
| 2.5 | 在 **UCB_OTP / PROCONTP** 写 `SWAPEN=11b`（AP32404：写入含 `0x00030000` 一类使能值；以 UM 位域为准） | 真正打开 SOTA 模式 |
| 2.6 | **System Reset** | SWAPEN / SWAP 配置只在系统复位后由 SSW 安装 |

UCB 关键地址（与 TC397 Demo / AP32404 一致，TC36x 亦用此图）：

| 符号 | 地址 |
|------|------|
| `UCB_SWAP_ORIG` | `0xAF402E00` |
| `UCB_SWAP_COPY` | `0xAF403E00` |
| ORIG Confirmation Code | `0xAF402FF0` |
| COPY Confirmation Code | `0xAF403FF0` |

常量：

| 值 | 含义 |
|----|------|
| `0x00000055` | 选 A（标准图） |
| `0x000000AA` | 选 B（交替图） |
| `0x57B5327F` | CONFIRMED |
| `0x43211234` | UNLOCKED（UCB 区状态） |
| `0xFFFFFFFF` | 作废旧 confirmation（UCB 可 over-program） |

槽位：每条 16B，最多 16 条；**SSW 取最后一条合法项**。写满后擦整 UCB 再从 0 重写（Demo 与 AP32404 相同）。

**验证**

- `SCU_SWAPCTRL.ADDRCFG == 1`  
- `DMU_HF_PROCONTP.SWAPEN` 为使能  
- `SCU_STMEM1` 可核对安装来源索引（AP32404）  
- Boot 仍可进 `10 02`，APP 可跳转

**危险顺序（禁止）**

1. ~~先 SWAPEN，UCB_SWAP 却无合法条目~~ → 可能 **永远复位**  
2. ~~只擦 ORIG、COPY 也坏掉且无备份~~ → 同上  

推荐：改 UCB 时 **先 COPY 后 ORIG**（AP32404 Dual Password 流程）。

---

### Phase 3 — 建立 B 区首份镜像（双备份）

**操作**

1. 确认当前为 A 激活（`ADDRCFG=1` / Current memory: standard）。  
2. 把 **同一份** Boot+APP hex（仍按 `0x800…` 链接），按物理落点写到 B：  
   - Boot → **`0x80300000`** 或 **`0xA0300000`**  
   - APP → **`0x80320000`** 或 **`0xA0320000`**  
   - 可用 UDE SOTA / Simulate alternative，或只偏移 hex **load address**（勿改镜像内绝对常量）  
3. 在 A 激活下读物理 B 校验（`0xA0300000` 起应有代码，不是全 0）。  
4. （可选）写一条 `UCB_SWAP` 切到 alternative（`0xAA`），System Reset，确认能从 B 启动；再写回 standard（`0x55`）切回 A。

**为什么：** 没有 B 备份就没有真正的 A/B；首次切 B 失败时可回切 A。

调试器提示（AP32404）：Lauterbach `FLASH.CreateALIAS` / UDE≥4.9 支持 SOTA 重定位烧写。

---

### Phase 4 — 改造 boot364 运行时 OTA（合入代码时照此做）

#### 4.1 模块划分建议

| 模块 | 职责 | 参考 |
|------|------|------|
| `Boot_Swap.c/h` | 读 ADDRCFG；算 inactive 基址；Init 扫 UCB 槽；写新 MARKER+CONFIRM；作废旧槽；满槽擦 COPY/ORIG | `DemoSwap.c` + `FlashUcb.h` |
| `Boot_FlashProg.c` | Erase/Download/Exit 目标改为 inactive 物理窗；长度门限 ≤**2MB**；B 基址 **`0x80300000`** | 现有 `34/36/37/31` |
| `Boot_App.c` | 跳转仍校验逻辑 `0x80020000`；可选拒绝在 SWAP 非法态跳转 | 现逻辑基本可留 |
| UDS 收尾 | CheckMemory OK →（可选 CheckDep）→ `Boot_Swap_Commit(newBank)` → **System Reset** | UM Runtime SWAP |

#### 4.2 推荐刷写状态机（相对现 FlashPanel）

现行：

`10 02 → 27 → 31 FF00 擦 APP → 34/36/37 → 31 FF02 → 31 FF01 → 11`

双区建议：

```text
10 02 / 27
    → 31 FF00  EraseMemory：擦 **inactive 整区**（Boot+APP 或策略约定的子窗）
    → 34/36/37 写 inactive（地址可用逻辑窗，Boot 内部换算物理；或诊断直接下发物理址）
    → 31 FF02  CheckMemory：对 **刚写入的物理区** 算 CRC
    → 31 FF01  CheckProgrammingDependencies（可选：版本/兼容性）
    → 31 xxxx  ActivateSwap（新 RID）或并入 FF01：写 UCB_SWAP
    → System Reset（非 App Reset）
复位后：
    SSW 装新映射 → Boot 跑在新 Bank → 校验 APP 头 → 跳 APP
失败回滚：
    再写 UCB 指回旧 Bank + System Reset
    或外部条件强制 Boot 写回旧 MARKER（506 Safety 建议）
```

**为什么擦 inactive 而不是当前执行区：** 当前区在跑代码；擦自己等于自杀。这也是 SWAP 相对“原地刷写”的核心收益。

**为什么 System Reset：** UM 明确 Application Reset 不安装新 SWAP 映射。

#### 4.3 Demo 代码可直接借鉴的点

`illD-Swap_1_KIT_TC397_TFT/Demo_Swap`：

| Demo API | 合入 Boot 时建议 |
|----------|------------------|
| `DemoSwap_Init` | 启动读 ADDRCFG + 扫 ORIG/COPY 找下一空槽 |
| `DemoSwap_DemoCore0` | 改成 `Boot_Swap_Activate(targetBank)`，由 UDS 调，不要靠全局 flag |
| `FlashUcb_*` | UCB 在 DFlash 命令空间；可沿用 Demo 序列，**注意 Safety EndInit**；与 PFlash `FlsLoader` 分开 |
| `UCB_SWAP_Restore` | 实验室恢复 A；量产做成受控回滚 RID |

注意：Demo 里软复位变量赋值后需确认是否写回 `SCU_SWRSTCON`；量产优先 `Mcu_PerformReset` / 明确的 System Reset 路径。

#### 4.4 last364 侧

| 操作 | 为什么 |
|------|--------|
| 仅保证体积与基址符合 **2MB** 窗 | APP 不负责写 UCB_SWAP（除非你们把 OTA 放在 APP；当前架构在 Boot） |
| `10 02` JumpToBoot / HIS 握手保持 | 进 Boot 再刷 inactive |
| 不要假设 `0x803xxxxx` / `0xA03xxxxx` 是“多出来的 APP” | 那是 **物理 B（PF1）**；开 SWAP 后逻辑执行窗仍是 `0x80000000`～`0x801FFFFF` |

---

### Phase 5 — 安全、回滚、寿命

| 主题 | 做法 | 为什么 |
|------|------|--------|
| 完整性 | FF02 CRC + APP 头 CRC；可选签名（Secure Boot/HSM，见 506，本指南不展开） | 坏镜像切过去变砖 |
| 回滚 | 保留旧 Bank 不擦到不可用；失败再 Swap 回去 | 506 Solution A/B |
| 挂死救援 | Boot 读引脚/诊断会话强制写 `0x55`/`0xAA` | 新 APP 起不来时仍能救 |
| UCB 寿命 | 每 16 次 Swap 擦一次 UCB；PFlash ~1000 次；UCB 擦写次数更严 | AP32404 寿命计算 |
| OTP 确认后 | 若 OTP CONFIRMED，**SWAP 可能关不掉** | 量产前想清楚 |
| HSM | 若用 HSM：S0–S39 在 **A、B 都要有** HSM 镜像 | AP32404 §HSM |

Secure Boot（HSM 验签后再放 Host）与 A/B SWAP **正交**：SWAP 管“跑哪份镜像”，Secure Boot 管“这份镜像是否可信”。本阶段可只做 SWAP；签名放到后续。

---

## 5. 操作检查清单（落地用）

### 5.1 启用前

- [ ] APP map ≤ `0x801FFFFF`（本板每区 2MB）  
- [ ] Boot map ≤ `0x8001FFFF`  
- [ ] `Boot_Mem.h` APP_END = `0x801FFFFF`（勿误用旧稿 `0x800FFFFF`）  
- [ ] 单区刷写与跳转已验证  

### 5.2 首次开 SWAP

- [ ] A 区 Boot+APP 完整  
- [ ] `UCB_SWAP` 至少一条合法 `0x55` + CONFIRMED（ORIG，建议 COPY 镜像）  
- [ ] 再写 `SWAPEN`  
- [ ] System Reset 后 `ADDRCFG==1`，诊断仍通  

### 5.3 双备份

- [ ] B 物理区有完整 Boot+APP  
- [ ] 试切 `0xAA` 能起；再切回 `0x55`  

### 5.4 OTA 联调

- [ ] 擦写地址始终是 inactive  
- [ ] FF02 校验的是写入区  
- [ ] Swap 后必须 System Reset  
- [ ] 故意写坏 inactive → 不得 Swap；或 Swap 失败可回滚  

---

## 6. 关键寄存器 / 地址速查

| 名称 | 地址 | 用途 |
|------|------|------|
| `SCU_SWAPCTRL` | `0xF003614C` | `ADDRCFG`：1=A，2=B |
| `SCU_STMEM1` | `0xF0036184` | 安装来源/索引核对 |
| `DMU_HF_PROCONTP` | `0xF8040084` | `SWAPEN` 等（镜像自 UCB） |
| `UCB_SWAP_ORIG` | `0xAF402E00` | Swap 配置主份 |
| `UCB_SWAP_COPY` | `0xAF403E00` | 备份；ORIG 坏才用 |
| BMHD UCB | `0xAF400000` 一带 | 启动头（仅一份，不随 Bank 双份存储） |

---

## 7. 与现有笔记的关系

| 文档 | 关系 |
|------|------|
| `Boot_APP分区与刷写联调总结.md` | 现行单区刷写；双区启用后 APP_END / 擦写目标以本文为准 |
| `Boot_A2_配置清单.md` | Slim Boot 模块范围仍适用；新增 `Boot_Swap` + UCB 写 |
| `Boot_半截刷写ECC…` | inactive 半截刷仍会 ECC；MASKUECC / 先擦后写原则不变 |
| `Swap/illD-Swap_…/DemoSwap.c` | UCB 槽位状态机参考实现 |

---

## 8. 建议实施顺序（工程任务拆分）

1. **文档评审**：确认本板为 **4MB = 2×2MB → SWAP 后 2MB/2MB**，B 物理基址 **`0x80300000`/`0xA0300000`**。  
2. **Phase1 分区确认**：`Boot_Mem.h` / 链接在 `0x80000000`～`0x801FFFFF`，**不**链到 `0x803…`。  
3. **移植 `Boot_Swap`**：从 Demo 抽 UCB 读写，加 EndInit/错误码。  
4. **FlashProg 换算 inactive**：A 激活时写 B = `logical + 0x00300000`；实验室先验证物理写 B。  
5. **ActivateSwap（已实现）**：UDS `31 01 FF 03 [55|AA|省略=toggle]` → `Boot_Swap_Activate` 写 `UCB_SWAP` → `Boot_Uds_RequestSoftwareReset`（System Reset）。  
6. **产线脚本**：A 烧写 → UCB_SWAP(A) → SWAPEN → 写 B → 抽检切 Bank。  
7. **CANoe FlashPanel**：刷完 FF02/FF01 后加 `31 01 FF 03`（或 `… AA`）；勿只发 App Reset。  
8. （可选）Secure Boot / 签名。

---

## 9. 常见误区

| 误区 | 正确理解 |
|------|----------|
| “双区 = 再给 APP 多 2MB 同时执行” | 开 SWAP 后是 **2MB 执行 + 2MB 备用**，CPU 同时只跑一边 |
| “B 区单独链接到 `0x80300000` 或 `0x80100000`” | hex **永远按 A 逻辑 `0x800…` 链**；写 B 只改烧录落点 |
| “B = `0x80100000`” | **错**；本板 PF1 在 **`0x80300000`/`0xA0300000`**（MemTool PFLASH1） |
| “只刷 APP 到 B，Boot 共用 A” | 映射切换后 Boot 也来自当前 Bank；B 里必须有 Boot |
| “`11 01` 就能激活 Swap” | 需要 **System Reset**；确认复位类型 |
| “先开 SWAPEN 再配 UCB” | 极易变砖；必须 **先合法 UCB_SWAP** |
| “TC397 Demo 地址/Bank 组可照搬布局” | UCB 地址通常相同；**Bank 大小与物理基址以本板 Datasheet 为准** |

---

## 10. 小结

对 **boot364 + last364（TC364 TQFP-144 · 4MB PFlash）**：

1. **硬件是 PF0/PF1 各 2MB 的 A/B SWAP**（逻辑窗 `0x80000000`～`0x801FFFFF`；物理 B @ `0x80300000`）。  
2. **操作主线：** 确认 2MB 分区 → A 烧完整 Boot+APP → 配 UCB_SWAP → 开 SWAPEN → 镜像到 B（`0x803…`）→ Boot OTA 只写 inactive → 校验 → 写 SWAP → System Reset。  
3. **最危险操作：** 无合法 `UCB_SWAP` 时写 `SWAPEN`；以及把镜像刷到错误物理基址（如 `0x80100000`）。  
4. **Demo 用途：** 抄 UCB 槽位与擦写时序，不要抄 TC397 的 Bank 编组与地址。

若需要下一步，可在本指南 Phase4 基础上直接起草 `Boot_Swap.h` API 与 `Boot_FlashProg` 插入点补丁清单（仍先改文档/接口，再动代码）。
