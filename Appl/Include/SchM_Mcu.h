/**********************************************************************************************************************
 * Boot slim SchM stubs (no RTE)
 *********************************************************************************************************************/
#ifndef SCHM_MCU_H
#define SCHM_MCU_H

#include "Os.h"

#define SchM_Enter_Mcu_AtomAgcReg() SuspendOSInterrupts()
#define SchM_Exit_Mcu_AtomAgcReg()  ResumeOSInterrupts()
#define SchM_Enter_Mcu_TomTgcReg()  SuspendOSInterrupts()
#define SchM_Exit_Mcu_TomTgcReg()   ResumeOSInterrupts()

#endif /* SCHM_MCU_H */
