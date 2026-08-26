# last364 独立启动 + UDE 调试（vLinkGen 配置）

> 工程：`last364`（APP，双核）/ 配套 `autosarTc364_Boot (2)`
> 目标：last364 单独启动（不依赖 Boot），在 UDE 里直接复位运行调试
> 更新日期：2026-08-22

## 1. 背景

当前 last364 是“Boot 共存布局”：APP 链接在 `0x80020000`（PFlash Offset `0x20000`），BMHD 被禁用（`BrsHw.c` 的 `bmiField0` 被 `# if 0` 包住），由 Boot 校验头后跳转启动。

独立启动 = 恢复“单镜像布局”：APP 从 `0x80000000` 起 + 自带 BMHD（UCB `0xAF400000`）+ 启动代码 + 异常向量。

参考 Boot 工程（能独立启动）的 vLinkGen 布局：
- `StartupCode_FirstExecInst` @ `0x80000000`（0x500）
- `CoreExceptions_FirstExecInst` @ `0x80000500`（0x200）
- `PFlash0_Cached` @ `0x80000700`
- `BMHD0` @ `0xAF400000`（UCB，512 B）
- `section_setup start_address = "brsStartupEntry"`（last364 模板已有）

## 2. DaVinci vLinkGen 修改（last364 → MICROSAR → vLinkGen → vLinkGenMemLayout）

### 2.1 Memory Region `PFlash0_Cached`（改）
- Offset `0x20000` → `0`；Size `0x1E0000` → `0x200000`
- 区域下新增 Block：
  - `StartupCode_FirstExecInst`：ContentType=`STARTUP_CODE`，Position=`0`，Address=`0x80000000`，Size=`0x500`，Boundary=`LOWER`，InitStage=`NONE`
  - `CoreExceptions_FirstExecInst`：ContentType=`GLOBAL_EXCVEC_CONST`，Position=`1`，Address=`0x80000500`，Size=`0x200`，Boundary=`LOWER`，InitStage=`NONE`
- 主 Block（`PFlash0_Cached`）Position 顺延为 `2`，起始 `0x80000700`，Size 覆盖剩余（`0x200000 − 0x700 = 0x1FF900`）

### 2.2 新增 Memory Region `MemRegion_BMHD0`
- Address=`0xAF400000`，Size=`512`，Available=`true`，HwRegion=`vBaseEnvGeneral/BMHD0`
- Block `BMHD0`：Position=`0`，Size=`512`，Address=`0xAF400000`，Boundary=`LOWER`，InitStage=`NONE`

### 2.3 新增 Logical Const Group `BMHD0`
- Region=`MemRegion_BMHD0/BMHD0`，Position=`5`
- SectionGroup：Init=`NONE`、Stage=`ONE`、Flags=`ORDERED/CONTIGUOUS/FILL/READ`，SectionGroupRef → Linker Sections 的 `BMHD0`（const section 已存在）

### 2.4 生成后核对 `vLinkGen_Template.lsl`
应出现：
```
memory StartupCode_FirstExecInst   @ 0x80000000
memory CoreExceptions_FirstExecInst @ 0x80000500
memory PFlash0_Cached              @ 0x80000700
memory BMHD0                       @ 0xAF400000
start_address (symbol = "brsStartupEntry");
```

## 3. 源码修改（last364）

- `Appl\Source\BrsHw.c:118`：`# if 0` → `# if 1`，重新启用 `bmiField0`（BMHD：start=`0x80000000`、magic=`0xB359000E`、CRC 现成）
- `Appl\Source\Appl_BootCompat.c`：`Appl_BootHeader __at(0x80020000)` 加宏开关（独立模式不定义），避免在代码区中间强制留洞
- post-build `Tools\patch_app_header.py`：独立模式不再需要往 `0x80020000` 写 length/crc，检查脚本是否依赖固定地址

## 4. UDE 调试

1. 烧写 / 加载 `last364.hex`（现在含 UCB BMHD + `0x80000000` 启动代码）
2. Connect → Reset → Run：BootROM 读 UCB BMHD（magic + CRC）→ 跳 `0x80000000` → `brsStartupEntry` → 独立启动
3. 双核：Core1 由 Core0 的 BRS 启动拉起，UDE 里可把 Core1 也加入会话

## 5. 注意

- 独立布局与 Boot 共存**互斥**：占用 `0x80000000` 起 + UCB BMHD，会覆盖 Boot 的 BMHD
- 来回切换 = 改 Offset（`0` / `0x20000`）+ `BrsHw.c`（`# if 1` / `# if 0`）+ BMHD 区启用 / 禁用
- 若 UDE 连接失败（有 `__connection_failed_report__Controller0_Core0_*.txt`），先解决 DAS / 2PIN DAP 连接