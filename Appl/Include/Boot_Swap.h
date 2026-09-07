/**********************************************************************************************************************
 * Boot_Swap.h — SOTA A/B mapping + UCB_SWAP Activate (TC364 4MB = 2×2MB)
 *
 * Logical link view is always Group-A style (0x80000000..0x801FFFFF).
 * NVM erase/write must use the inactive *physical* bank:
 *   ADDRCFG==1 (A active) → inactive PF1 @ 0x80300000 / 0xA0300000
 *   ADDRCFG==2 (B active) → inactive PF0 @ 0x80000000 / 0xA0000000
 *
 * Bank switch: Boot_Swap_Activate() writes UCB_SWAP then caller does System Reset
 * (BrsHwSoftwareResetECU / UDS 0x11). Application Reset does NOT install SWAP.
 *********************************************************************************************************************/
#ifndef BOOT_SWAP_H
#define BOOT_SWAP_H

#include "Std_Types.h"
#include "Boot_Mem.h"

#ifndef BOOT_SWAP_PROGRAM_INACTIVE
/* 1 = SOTA: erase/write inactive physical bank (A active → PF1 @ 0xA03…).
 * 0 = lab only: write running bank logical APP (no bank switch). */
# define BOOT_SWAP_PROGRAM_INACTIVE  (1u)
#endif

#define BOOT_SWAP_SCU_SWAPCTRL_ADDR      (0xF003614Cu)
#define BOOT_SWAP_ADDRCFG_NONE           (0u)
#define BOOT_SWAP_ADDRCFG_A              (1u) /* MARKER 0x55 / standard */
#define BOOT_SWAP_ADDRCFG_B              (2u) /* MARKER 0xAA / alternative */

#define BOOT_SWAP_MARKER_A               (0x55u)
#define BOOT_SWAP_MARKER_B               (0xAAu)
#define BOOT_SWAP_MARKER_TOGGLE          (0x00u) /* Activate: switch to the other bank */

#define BOOT_SWAP_BANK_SIZE              (0x00200000u) /* 2 MB per group */
#define BOOT_SWAP_PF1_CACHED_BASE        (0x80300000u)
#define BOOT_SWAP_PF1_PHYS_OFFSET        (0x00300000u)

void    Boot_Swap_Init(void);
uint32  Boot_Swap_GetAddrCfg(void);
boolean Boot_Swap_IsMappingLegal(void);

uint32  Boot_Swap_LogicalToInactiveCached(uint32 logicalCachedOrHw);
uint32  Boot_Swap_LogicalToInactiveHw(uint32 logicalCachedOrHw);

/* Write next UCB_SWAP slot for target bank. Does NOT reset.
 * marker: BOOT_SWAP_MARKER_A / _B / _TOGGLE.
 * Requires UCB_SWAP already initialized (MemTool / production). */
Std_ReturnType Boot_Swap_Activate(uint8 marker);

#endif /* BOOT_SWAP_H */
