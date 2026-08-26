/**********************************************************************************************************************
 * Boot slim SchM stubs (no RTE)
 *********************************************************************************************************************/
#ifndef SCHM_CANIF_H
#define SCHM_CANIF_H

#include "Os.h"

/* vBRS CAN exclusive-area helpers are off (no BRS_ENABLE_CAN_SUPPORT) — use OS lock */
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0()  ResumeOSInterrupts()
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_1() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_1()  ResumeOSInterrupts()
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_2() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_2()  ResumeOSInterrupts()
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_3() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_3()  ResumeOSInterrupts()
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_4() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_4()  ResumeOSInterrupts()
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_5() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_5()  ResumeOSInterrupts()
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_6() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_6()  ResumeOSInterrupts()
#define SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_7() SuspendOSInterrupts()
#define SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_7()  ResumeOSInterrupts()

#endif /* SCHM_CANIF_H */
