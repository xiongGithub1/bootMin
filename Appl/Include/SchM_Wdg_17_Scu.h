/**********************************************************************************************************************
 * Boot slim SchM stubs for Wdg_17_Scu (no RTE)
 *********************************************************************************************************************/
#ifndef SCHM_WDG_17_SCU_H
#define SCHM_WDG_17_SCU_H

#include "Os.h"

#define SchM_Enter_Wdg_17_Scu_TimerHandling() SuspendOSInterrupts()
#define SchM_Exit_Wdg_17_Scu_TimerHandling()  ResumeOSInterrupts()

#define SchM_Enter_Wdg_17_Scu_ChangeMode()    SuspendOSInterrupts()
#define SchM_Exit_Wdg_17_Scu_ChangeMode()     ResumeOSInterrupts()

#define SchM_Enter_Wdg_17_Scu_CpuEndInit()    SuspendOSInterrupts()
#define SchM_Exit_Wdg_17_Scu_CpuEndInit()     ResumeOSInterrupts()

#endif /* SCHM_WDG_17_SCU_H */
