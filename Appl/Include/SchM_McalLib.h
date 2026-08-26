/**********************************************************************************************************************
 * Boot slim SchM stubs (no RTE)
 *********************************************************************************************************************/
#ifndef SCHM_MCALLIB_H
#define SCHM_MCALLIB_H

#include "Os.h"

#define SchM_Enter_McalLib_CpuEndInit()         SuspendOSInterrupts()
#define SchM_Exit_McalLib_CpuEndInit()          ResumeOSInterrupts()
#define SchM_Enter_McalLib_PeripheralEndInit()  SuspendOSInterrupts()
#define SchM_Exit_McalLib_PeripheralEndInit()   ResumeOSInterrupts()
#define SchM_Enter_McalLib_SafetyEndInit()      SuspendOSInterrupts()
#define SchM_Exit_McalLib_SafetyEndInit()       ResumeOSInterrupts()
#define SchM_Enter_McalLib_StmTimerResolution() SuspendOSInterrupts()
#define SchM_Exit_McalLib_StmTimerResolution()  ResumeOSInterrupts()

#endif /* SCHM_MCALLIB_H */
