/**********************************************************************************************************************
 * Boot_Swap.c — ADDRCFG helpers + UCB_SWAP Activate (from illD DemoSwap / FlashUcb)
 *********************************************************************************************************************/
#include "Boot_Swap.h"
#include "Boot_App.h"
#include "IfxDmu_reg.h"

#define BOOT_SWAP_SCU_SWAPCTRL           (*(volatile uint32 *)BOOT_SWAP_SCU_SWAPCTRL_ADDR)

/* UCB_SWAP (UM / Demo) */
#define BOOT_UCB_SWAP_ORIG               (0xAF402E00u)
#define BOOT_UCB_SWAP_COPY               (0xAF403E00u)
#define BOOT_UCB_SWAP_ORIG_CONFIRM       (0xAF402FF0u)
#define BOOT_UCB_SWAP_COPY_CONFIRM       (0xAF403FF0u)

#define BOOT_UCB_UNLOCKED                (0x43211234u)
#define BOOT_UCB_CONFIRMED               (0x57B5327Fu)
#define BOOT_UCB_INVALIDATION            (0xFFFFFFFFu)
#define BOOT_UCB_MARKER_A                (0x00000055u)
#define BOOT_UCB_MARKER_B                (0x000000AAu)

#define BOOT_FLASHUCB_CMD_BASE           (0xAF000000u)

/* TC36x = BRS_WATCHDOG_GROUP_B Safety WDT */
#define BOOT_WDTS_CON0                   (*(volatile uint32 *)0xF00362A8u)

typedef enum
{
  BOOT_SWAP_UCB_ORIG = 0,
  BOOT_SWAP_UCB_COPY
} Boot_Swap_UcbSelType;

typedef struct
{
  Boot_Swap_UcbSelType ucbSel;
  uint32 slotAddr;          /* current CONFIRMED marker base (16 B aligned) */
  uint8  slotIndex;
  uint8  eraseNext;         /* 1 = full sector rollover on next Activate */
  uint8  inited;
} Boot_Swap_StateType;

static Boot_Swap_StateType Boot_Swap_State;

static void Boot_Swap_SafetyUnlock(void)
{
  volatile uint32 w = BOOT_WDTS_CON0;
  w &= 0xFFFFFF01u;
  w |= 0xF0u;
  w |= 0x01u;
  BOOT_WDTS_CON0 = w;
  w &= 0xFFFFFFF0u;
  w |= 0x02u; /* WDTLCK=1, ENDINIT=0 */
#if defined (BRS_COMP_TASKING)
  __isync();
#endif
  BOOT_WDTS_CON0 = w;
  (void)BOOT_WDTS_CON0;
#if defined (BRS_COMP_TASKING)
  __isync();
  __dsync();
#endif
}

static void Boot_Swap_SafetyLock(void)
{
  volatile uint32 w = BOOT_WDTS_CON0;
  w &= 0xFFFFFF01u;
  w |= 0xF0u;
  w |= 0x01u;
  BOOT_WDTS_CON0 = w;
  w &= 0xFFFFFFF0u;
  w |= 0x03u; /* WDTLCK=1, ENDINIT=1 */
#if defined (BRS_COMP_TASKING)
  __isync();
#endif
  BOOT_WDTS_CON0 = w;
  (void)BOOT_WDTS_CON0;
#if defined (BRS_COMP_TASKING)
  __isync();
  __dsync();
#endif
}

static void Boot_Swap_UcbWaitUnbusy(void)
{
  while ((DMU_HF_STATUS.U & 0x1u) != 0u)
  {
  }
#if defined (BRS_COMP_TASKING)
  __dsync();
#endif
}

static void Boot_Swap_UcbEnterPageMode(void)
{
  volatile uint32 *a = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0x5554u);
  *a = 0x5Du;
#if defined (BRS_COMP_TASKING)
  __dsync();
#endif
}

static void Boot_Swap_UcbLoadPage2x32(uint32 lo, uint32 hi)
{
  volatile uint32 *a = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0x55F0u);
  *a = lo;
  a++;
  *a = hi;
#if defined (BRS_COMP_TASKING)
  __dsync();
#endif
}

static void Boot_Swap_UcbWritePage(uint32 pageAddr)
{
  volatile uint32 *a1 = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0xAA50u);
  volatile uint32 *a2 = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0xAA58u);
  volatile uint32 *a3 = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0xAAA8u);
  *a1 = pageAddr;
  *a2 = 0x00u;
  *a3 = 0xA0u;
  *a3 = 0xAAu;
#if defined (BRS_COMP_TASKING)
  __dsync();
#endif
}

static void Boot_Swap_UcbEraseSector(uint32 sectorAddr)
{
  volatile uint32 *a1 = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0xAA50u);
  volatile uint32 *a2 = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0xAA58u);
  volatile uint32 *a3 = (volatile uint32 *)(BOOT_FLASHUCB_CMD_BASE | 0xAAA8u);
  *a1 = sectorAddr;
  *a2 = 1u;
  *a3 = 0x80u;
  *a3 = 0x50u;
#if defined (BRS_COMP_TASKING)
  __dsync();
#endif
}

static void Boot_Swap_UcbWritePageProtected(uint32 pageAddr, uint32 lo, uint32 hi)
{
  Boot_Swap_UcbWaitUnbusy();
  Boot_Swap_UcbEnterPageMode();
  Boot_Swap_UcbWaitUnbusy();
  Boot_Swap_UcbLoadPage2x32(lo, hi);
  Boot_Swap_SafetyUnlock();
  Boot_Swap_UcbWritePage(pageAddr);
  Boot_Swap_SafetyLock();
  Boot_Swap_UcbWaitUnbusy();
}

uint32 Boot_Swap_GetAddrCfg(void)
{
  return (BOOT_SWAP_SCU_SWAPCTRL & 0x3u);
}

boolean Boot_Swap_IsMappingLegal(void)
{
  uint32 cfg = Boot_Swap_GetAddrCfg();
  if ((cfg == BOOT_SWAP_ADDRCFG_NONE) ||
      (cfg == BOOT_SWAP_ADDRCFG_A) ||
      (cfg == BOOT_SWAP_ADDRCFG_B))
  {
    return TRUE;
  }
  return FALSE;
}

uint32 Boot_Swap_LogicalToInactiveCached(uint32 logicalCachedOrHw)
{
  uint32 cached = Boot_App_ToCached(logicalCachedOrHw);
  uint32 cfg;
  uint32 offset;

  if (cached < BOOT_FLASH_BOOT_START)
  {
    return cached;
  }
  offset = cached - BOOT_FLASH_BOOT_START;
  if (offset >= BOOT_SWAP_BANK_SIZE)
  {
    return cached;
  }

  cfg = Boot_Swap_GetAddrCfg();
  if (cfg == BOOT_SWAP_ADDRCFG_A)
  {
    return (BOOT_SWAP_PF1_CACHED_BASE + offset);
  }
  return (BOOT_FLASH_BOOT_START + offset);
}

uint32 Boot_Swap_LogicalToInactiveHw(uint32 logicalCachedOrHw)
{
  return Boot_App_ToHw(Boot_Swap_LogicalToInactiveCached(logicalCachedOrHw));
}

void Boot_Swap_Init(void)
{
  uint8 i;
  uint32 confirm;
  uint32 base;

  Boot_Swap_State.inited = 0u;
  Boot_Swap_State.eraseNext = 0u;
  Boot_Swap_State.slotIndex = 0u;

  confirm = *(volatile uint32 *)BOOT_UCB_SWAP_ORIG_CONFIRM;
  if ((confirm == BOOT_UCB_UNLOCKED) || (confirm == BOOT_UCB_CONFIRMED))
  {
    Boot_Swap_State.ucbSel = BOOT_SWAP_UCB_ORIG;
    base = BOOT_UCB_SWAP_ORIG;
  }
  else
  {
    Boot_Swap_State.ucbSel = BOOT_SWAP_UCB_COPY;
    base = BOOT_UCB_SWAP_COPY;
  }

  Boot_Swap_State.slotAddr = base;
  for (i = 0u; i < 16u; i++)
  {
    confirm = *(volatile uint32 *)(Boot_Swap_State.slotAddr + 0x08u);
    if (confirm != BOOT_UCB_CONFIRMED)
    {
      Boot_Swap_State.slotAddr += 0x10u;
    }
    else
    {
      Boot_Swap_State.slotIndex = i;
      break;
    }
  }

  if (i >= 15u)
  {
    Boot_Swap_State.slotIndex = 0u;
    Boot_Swap_State.eraseNext = 1u;
    if (Boot_Swap_State.ucbSel == BOOT_SWAP_UCB_ORIG)
    {
      Boot_Swap_State.slotAddr = BOOT_UCB_SWAP_ORIG + 0xF0u;
    }
    else
    {
      Boot_Swap_State.slotAddr = BOOT_UCB_SWAP_COPY + 0xF0u;
    }
  }

  Boot_Swap_State.inited = 1u;
}

Std_ReturnType Boot_Swap_Activate(uint8 marker)
{
  uint32 cfg;
  uint32 newMarker;
  uint32 markerHi;
  uint32 confirmHi;

  if (Boot_Swap_State.inited == 0u)
  {
    Boot_Swap_Init();
  }
  if (Boot_Swap_State.inited == 0u)
  {
    return E_NOT_OK;
  }

  cfg = Boot_Swap_GetAddrCfg();
  if ((cfg != BOOT_SWAP_ADDRCFG_A) && (cfg != BOOT_SWAP_ADDRCFG_B))
  {
    /* SWAP not installed / illegal — cannot Activate via UCB alone. */
    return E_NOT_OK;
  }

  if (marker == BOOT_SWAP_MARKER_TOGGLE)
  {
    newMarker = (cfg == BOOT_SWAP_ADDRCFG_A) ? BOOT_UCB_MARKER_B : BOOT_UCB_MARKER_A;
  }
  else if (marker == BOOT_SWAP_MARKER_A)
  {
    newMarker = BOOT_UCB_MARKER_A;
  }
  else if (marker == BOOT_SWAP_MARKER_B)
  {
    newMarker = BOOT_UCB_MARKER_B;
  }
  else
  {
    return E_NOT_OK;
  }

  /* Already on requested bank — nothing to program. */
  if (((newMarker == BOOT_UCB_MARKER_A) && (cfg == BOOT_SWAP_ADDRCFG_A)) ||
      ((newMarker == BOOT_UCB_MARKER_B) && (cfg == BOOT_SWAP_ADDRCFG_B)))
  {
    return E_OK;
  }

#if defined (BRS_COMP_TASKING)
  __disable();
#endif

  if (Boot_Swap_State.eraseNext != 0u)
  {
    /* Invalidate last confirmation, erase opposite UCB sector, unlock it. */
    Boot_Swap_UcbWritePageProtected(
        Boot_Swap_State.slotAddr + 0x08u,
        BOOT_UCB_INVALIDATION,
        BOOT_UCB_INVALIDATION);

    Boot_Swap_SafetyUnlock();
    if (Boot_Swap_State.ucbSel == BOOT_SWAP_UCB_ORIG)
    {
      Boot_Swap_UcbEraseSector(BOOT_UCB_SWAP_COPY);
    }
    else
    {
      Boot_Swap_UcbEraseSector(BOOT_UCB_SWAP_ORIG);
    }
    Boot_Swap_SafetyLock();
    Boot_Swap_UcbWaitUnbusy();

    if (Boot_Swap_State.ucbSel == BOOT_SWAP_UCB_ORIG)
    {
      Boot_Swap_UcbWritePageProtected(BOOT_UCB_SWAP_COPY_CONFIRM, BOOT_UCB_UNLOCKED, 0u);
      Boot_Swap_State.ucbSel = BOOT_SWAP_UCB_COPY;
      Boot_Swap_State.slotAddr = BOOT_UCB_SWAP_COPY;
    }
    else
    {
      Boot_Swap_UcbWritePageProtected(BOOT_UCB_SWAP_ORIG_CONFIRM, BOOT_UCB_UNLOCKED, 0u);
      Boot_Swap_State.ucbSel = BOOT_SWAP_UCB_ORIG;
      Boot_Swap_State.slotAddr = BOOT_UCB_SWAP_ORIG;
    }
    Boot_Swap_State.eraseNext = 0u;
  }
  else
  {
    /* Invalidate current confirmation; advance to next 16 B slot. */
    Boot_Swap_UcbWritePageProtected(
        Boot_Swap_State.slotAddr + 0x08u,
        BOOT_UCB_INVALIDATION,
        BOOT_UCB_INVALIDATION);
    Boot_Swap_State.slotAddr += 0x10u;
  }

  markerHi = Boot_Swap_State.slotAddr;
  confirmHi = Boot_Swap_State.slotAddr + 0x08u;

  Boot_Swap_UcbWritePageProtected(Boot_Swap_State.slotAddr, newMarker, markerHi);
  Boot_Swap_UcbWritePageProtected(Boot_Swap_State.slotAddr + 0x08u, BOOT_UCB_CONFIRMED, confirmHi);

#if defined (BRS_COMP_TASKING)
  __enable();
#endif

  /* Refresh next-slot bookkeeping for a following Activate without reset. */
  Boot_Swap_Init();
  return E_OK;
}
