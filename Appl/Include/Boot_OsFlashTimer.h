/**********************************************************************************************************************
 * Boot_OsFlashTimer.h — Pause / resync OS SystemTimer around PFlash erase/program.
 *
 * Long DISABLE (or masked STM) without resync → Os_TimerPfrt catch-up → CounterWorkJobs → ErrorHook.
 *********************************************************************************************************************/
#ifndef BOOT_OS_FLASH_TIMER_H
#define BOOT_OS_FLASH_TIMER_H

#include "Std_Types.h"

/* Mask STM0 CMP0 IRQ (SystemTimer). Nestable. */
void Boot_OsFlashTimer_Pause(void);

/* Clear pending, set next CMP = now + Period, update OS PFRT HwCompare, unmask. Nestable. */
void Boot_OsFlashTimer_Resume(void);

#endif /* BOOT_OS_FLASH_TIMER_H */
