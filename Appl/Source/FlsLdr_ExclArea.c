/**********************************************************************************************************************
 * FlsLoader exclusive area stubs for Boot (PFlash erase/program critical sections).
 *
 * While PFlash0 is busy, code must not fetch from PFlash0. ResumeAllInterrupts lives
 * in Flash → Exit must stay empty during the op; call PfBusy_Release after return.
 *
 * Pause OS SystemTimer once for the whole busy window (FlsLoader may Enter many times
 * per multi-sector erase). Resync on PfBusy_Release to avoid PFRT catch-up → ErrorHook.
 *********************************************************************************************************************/
#include "Os.h"
#include "FlsLdr_ExclArea.h"
#include "Boot_OsFlashTimer.h"

static uint8 FlsLdr_IrqHeld;

/* These Enter/Exit stubs are called while PFlash0 is busy (erase/program
 * already started), so they must run from PSPR0 RAM, not from PFlash0.
 * vLinkGen maps the FlsLoader_WriteErase section to PSPR0 with COPY_TO_RAM. */
#define FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
#include "FlsLoader_MemMap.h"

void FlsLdr_ExclArea_PfProg_Enter(void)
{
  if (FlsLdr_IrqHeld == 0u)
  {
    Boot_OsFlashTimer_Pause();
    SuspendAllInterrupts();
    FlsLdr_IrqHeld = 1u;
  }
}

void FlsLdr_ExclArea_PfProg_Exit(void)
{
  /* Intentionally empty — PFlash may already be busy. */
}

void FlsLdr_ExclArea_PfErase_Enter(void)
{
  if (FlsLdr_IrqHeld == 0u)
  {
    Boot_OsFlashTimer_Pause();
    SuspendAllInterrupts();
    FlsLdr_IrqHeld = 1u;
  }
}

void FlsLdr_ExclArea_PfErase_Exit(void)
{
  /* Intentionally empty — PFlash may already be busy. */
}

#define FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
#include "FlsLoader_MemMap.h"

void FlsLdr_ExclArea_PfBusy_Release(void)
{
  if (FlsLdr_IrqHeld != 0u)
  {
    FlsLdr_IrqHeld = 0u;
    Boot_OsFlashTimer_Resume();
    ResumeAllInterrupts();
  }
}
