/**********************************************************************************************************************
 * Boot_OsFlashTimer.c
 *
 * TC36x SystemTimer = STM0 CMP0 / SRC_STM0SR0.
 * Pause IRQ during PFlash busy; on Resume set next compare to now+Period and update
 * OS PFRT HwCompare so missed ticks are NOT catch-up'd (avoids ErrorHook).
 *
 * No Os_*Int.h — those need OS_FUNC_* macros and break Tasking when included alone.
 *********************************************************************************************************************/
#include "Boot_OsFlashTimer.h"
#include "Os_Hal_Cfg.h"

#define BOOT_STM0_TIM0     (*(volatile uint32 *)0xF0001010u)
#define BOOT_STM0_CMP0     (*(volatile uint32 *)0xF0001030u)
#define BOOT_SRC_STM0SR0   (*(volatile uint32 *)0xF0038300u)

#define BOOT_SRC_SRE_MASK  (0x00000400uL)
#define BOOT_SRC_CLRR_MASK (0x02000000uL)

#define BOOT_OSTIMER_PERIOD ((uint32)OSTICKSPERBASE_SystemTimer)

/* Matches Vector Os_TimerPfrtType: { Value, JobCompare, HwCompare }. */
typedef struct
{
  uint32 Value;
  uint32 JobCompare;
  uint32 HwCompare;
} Boot_OsPfrtDyn;

extern const uint8 OsCfg_Counter_SystemTimer[];

static uint8 Boot_OsFlashTimer_Nest;
static Boot_OsPfrtDyn *Boot_OsPfrtDynPtr;

static boolean Boot_OsFlashTimer_IsDsprPtr(uint32 p)
{
  /* CPU0 DSPR global / local views used by OS vars. */
  if ((p >= 0x70000000u) && (p < 0x70100000u))
  {
    return TRUE;
  }
  if ((p >= 0xD0000000u) && (p < 0xD0100000u))
  {
    return TRUE;
  }
  return FALSE;
}

static Boot_OsPfrtDyn *Boot_OsFlashTimer_FindDyn(void)
{
  const uint32 *w;
  uint32 i;
  uint32 cand;

  if (Boot_OsPfrtDynPtr != 0)
  {
    return Boot_OsPfrtDynPtr;
  }

  /* OsCfg_Counter_SystemTimer: ... Dyn*, Period(100000), MaxDiff, MaxCount, HwConfig*
   * TicksPerBase is also 100000 — skip if previous word is not a DSPR pointer. */
  w = (const uint32 *)(const void *)&OsCfg_Counter_SystemTimer[0];
  for (i = 1u; i < 64u; i++)
  {
    if (w[i] == BOOT_OSTIMER_PERIOD)
    {
      cand = w[i - 1u];
      if (Boot_OsFlashTimer_IsDsprPtr(cand) == TRUE)
      {
        Boot_OsPfrtDynPtr = (Boot_OsPfrtDyn *)(void *)cand;
        break;
      }
    }
  }
  return Boot_OsPfrtDynPtr;
}

void Boot_OsFlashTimer_Pause(void)
{
  if (Boot_OsFlashTimer_Nest == 0u)
  {
    BOOT_SRC_STM0SR0 &= ~BOOT_SRC_SRE_MASK;
    BOOT_SRC_STM0SR0 |= BOOT_SRC_CLRR_MASK;
  }
  if (Boot_OsFlashTimer_Nest < 255u)
  {
    Boot_OsFlashTimer_Nest++;
  }
}

void Boot_OsFlashTimer_Resume(void)
{
  Boot_OsPfrtDyn *dyn;
  uint32 now;
  uint32 next;

  if (Boot_OsFlashTimer_Nest == 0u)
  {
    return;
  }
  Boot_OsFlashTimer_Nest--;
  if (Boot_OsFlashTimer_Nest != 0u)
  {
    return;
  }

  now = BOOT_STM0_TIM0;
  next = now + BOOT_OSTIMER_PERIOD;

  dyn = Boot_OsFlashTimer_FindDyn();
  if (dyn != 0)
  {
    dyn->HwCompare = next;
  }
  BOOT_STM0_CMP0 = next;

  BOOT_SRC_STM0SR0 |= BOOT_SRC_CLRR_MASK;
  BOOT_SRC_STM0SR0 |= BOOT_SRC_SRE_MASK;
}
