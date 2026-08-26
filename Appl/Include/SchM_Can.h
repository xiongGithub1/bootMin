/**********************************************************************************************************************
 * Boot slim SchM stubs (no RTE)
 *********************************************************************************************************************/
#ifndef SCHM_CAN_H
#define SCHM_CAN_H

#include "Os.h"

#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()  ResumeOSInterrupts()
#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_1() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_1()  ResumeOSInterrupts()
#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_2() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_2()  ResumeOSInterrupts()
#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_3() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_3()  ResumeOSInterrupts()
#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_4() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_4()  ResumeOSInterrupts()
#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_5() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_5()  ResumeOSInterrupts()
#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_6() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_6()  ResumeOSInterrupts()
#define SchM_Enter_Can_CAN_EXCLUSIVE_AREA_7() SuspendOSInterrupts()
#define SchM_Exit_Can_CAN_EXCLUSIVE_AREA_7()  ResumeOSInterrupts()

#endif /* SCHM_CAN_H */
