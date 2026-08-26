# Boot UDS 架构（Cdd mini-UDS，无 Dcm）

## 为何不用 Dcm

Boot Flash 预算紧；完整 Dcm 会拉 Dem/NvM。本工程用 **AUTOSAR 通信栈 + 应用层 Cdd** 实现 ISO 14229 子集，**服务号/子服务/RID/DID 对齐 Boot Dcm**（`autosarTc364_Boot`），会话与安全 SF 与 **last364** App Dcm 一致。

权威宏表：`Appl/Include/Boot_Uds_Sid.h`（对照 `autosarTc364_Boot/Appl/GenData/Dcm_Lcfg.c`）。

## 分层

```text
Tester (ISO 14229)
    │
Can / CanIf / CanTp / PduR          ← AUTOSAR BSW（已有）
    │
Cdd_StartOfReception / CopyRxData / TpRxIndication   ← Boot_Uds.c（TP 适配）
    │
Boot_Uds_Dispatch()
    ├─ 0x10 / 0x11 / 0x22 / 0x27 / 0x2E / 0x3E   ← Boot_Uds.c
    └─ 0x31 / 0x34 / 0x36 / 0x37                   ← Boot_FlashProg.c → FlsLoader
```

| 文件 | 职责 |
|------|------|
| `Boot_Uds_Sid.h` | SID / SF / RID / DID（Dcm 对齐） |
| `Boot_Uds_Cfg.h` | 地址窗、缓冲、P2、安全 stub |
| `Boot_Uds_Sm.h` / `.c` | 刷写状态机 |
| `Boot_Uds.h` / `Boot_Uds.c` | 会话/安全/DID/分发、Cdd TP |
| `Boot_FlashProg.h` / `.c` | 0x31/34/36/37 |

## Dcm 对齐一览（相对 last364 / Boot Dcm）

| SID | 服务 | 子服务 / 备注 |
|-----|------|----------------|
| 0x10 | DiagnosticSessionControl | 01 Default / 02 Programming / 03 Extended |
| 0x11 | ECUReset | **01 Hard** / **03 Soft**；先发 `51 xx`，TxConfirmation 后再软复位 |
| 0x22 | ReadDataByIdentifier | F180 三会话可读；F187/F189/F18C/F190/F193 **仅扩展**；错会话 `0x31` |
| 0x27 | SecurityAccess | L1: 01 seed / 02 key（4B）；L3: 03/04（4B）；刷写用 L1；解锁按会话隔离 |
| 0x2E | WriteDataByIdentifier | F180/F198 在 P/E+L1；业务 DID 仅扩展+L1 |
| 0x3E | TesterPresent | 00（+ suppressPosRsp bit7） |
| 0x31 | RoutineControl | SF **01 Start** only；RID 见下 |
| 0x34/36/37 | Download | Boot Dcm 有；last364 App **无** |

### RID（`Dcm_CfgRidMgrRidLookUpTable`）

| RID | 名称 | 请求长度 | 正响应 |
|-----|------|----------|--------|
| FF00 | EraseMemory | 4（整 APP）或 13（44+addr+size） | 71 01 FF 00 + status |
| FF01 | CheckProgrammingDependencies | 4 或 5（Dcm 多 1B In） | 71 01 FF 01 + 00 |
| FF02 | CheckMemory | 4（0 in/out stub） | 71 01 FF 02 |

Stop / RequestResults（02/03）对本 Boot RID 返回 NRC 0x12。

## 刷写状态机（`Boot_Uds_Sm`）

```text
DEFAULT ──10 02──► PROG ──27──► SECURED ──31 FF00──► ERASED
   ▲                              ▲                    │
   │                              │                    │ 34
 10 01 / 离开编程                  └── 失败 abort ──────┤
   │                                                   ▼
EXTENDED ◄─10 03─                                 DOWNLOADING ◄─36─┐
                                                      │            │
                                                      └──37──► PROGRAMMED
                                                                    │
                                                    ┌─31 FF02 stub──┤
                                                    └──31 FF01──────► CHECKED
```

## 刷写顺序（典型）

1. `10 02` ProgrammingSession  
2. `27 01` → `27 02` + key（开发 stub：`~seed`；量产关 `BOOT_UDS_SECURITY_DEV_STUB`）  
3. `31 01 FF 00` 擦除 APP（禁止擦 Boot `0x80000000`～`0x8001FFFF`）  
4. `34 00 44` + addr + size（仅 APP 窗，32 字节对齐）  
5. 循环 `36` + BSC + data  
6. `37`  
7. `31 01 FF 02` CheckMemory（MCAL `Crc_CalculateCRC32` 回读比对）  
8. `31 01 FF 01` CheckProgrammingDependencies  
9. `11 01` 或 `11 03` 复位 → Boot 若 APP 头合法则跳转  

## 量产分区与启动

| 区 | 地址 | 规则 |
|----|------|------|
| Boot | `0x80000000`～`0x8001FFFF`（128 KB） | BMHD 仅此区；禁止 34/36/31 FF00 |
| APP 头 | `0x80020000` 起 32 B | magic `0xA5C3B007` + entry + length + CRC32 |
| APP | `0x80020000`～`0x801FFFFF` | last364 从此基址链接，无 BMHD |

复位永远进 Boot。`Boot_App_TryStart()`：共享 RAM 请求留 Boot，或头/CRC 非法 → 留在 Boot；否则跳 `entry`。  
APP 回刷：写 `BOOT_HS_MAGIC` + `REQUEST_BOOT` 后复位（APP 侧尚未接）。

## 配置注意

- 布局：`Appl/Include/Boot_Mem.h`（`Boot_Uds_Cfg.h` 引用）。  
- 量产：`BOOT_UDS_SECURITY_DEV_STUB=0`，改 `Boot_Uds.c` 里 `Boot_Uds_CalcKey()`。  
- Tasking 须加入 `Boot_App.c`（以及 `Boot_Uds*.c` / `Boot_FlashProg.c` / `Boot_Uds_Sm.c`）。
