/**********************************************************************************************************************
 * Boot_Uds_Cfg.h — Bootloader UDS product config (aligned with Boot Dcm + last364)
 *********************************************************************************************************************/
#ifndef BOOT_UDS_CFG_H
#define BOOT_UDS_CFG_H

#include "Std_Types.h"
#include "Boot_Uds_Sid.h"
#include "Boot_Mem.h"

/* --- ISO-TP / UDS buffers --- */
#ifndef CDD_TP_RX_BUF_SIZE
# define CDD_TP_RX_BUF_SIZE              (512u)
#endif
#ifndef CDD_TP_TX_BUF_SIZE
# define CDD_TP_TX_BUF_SIZE              (64u)
#endif

#define BOOT_UDS_MAX_BLOCK_LENGTH        ((uint16)CDD_TP_RX_BUF_SIZE)

/* P2 / P2* in 10 ms units for 0x50 response (same timing as Dcm session rows: 50 ms / 5000 ms) */
#define BOOT_UDS_P2_SERVER_10MS          (0x0005u)
#define BOOT_UDS_P2EX_SERVER_10MS        (0x01F4u)

/* Which SecurityAccess level unlocks flash programming (Boot Dcm UnlockedL1) */
#define BOOT_UDS_FLASH_SEC_LEVEL         (1u) /* use SF 0x01/0x02 */

/* 0x27 anti-brute: 3 consecutive invalid keys -> NRC 0x36, then 10 s delay (NRC 0x37) */
#define BOOT_SA_MAX_ATTEMPTS             (3u)
#define BOOT_SA_DELAY_MS                 (10000u)

/* After 0x51 is on the bus (TxConfirmation), wait this many MainFunction ticks
 * before BrsHwSoftwareResetECU so the tester can receive the positive response. */
#define BOOT_UDS_RESET_HOLD_MS           (2u)

/* Development unlock: key = ~seed (CANoe / FlashPanel).
 * Production: set 0 and replace Boot_Uds_CalcKey() in Boot_Uds.c. */
#ifndef BOOT_UDS_SECURITY_DEV_STUB
# define BOOT_UDS_SECURITY_DEV_STUB      (1u)
#endif

#endif /* BOOT_UDS_CFG_H */
