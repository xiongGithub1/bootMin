/**********************************************************************************************************************
 * Boot slim SchM stubs (no RTE). Exclusive areas -> Suspend/Resume OS interrupts.
 *********************************************************************************************************************/
#ifndef SCHM_PDUR_H
#define SCHM_PDUR_H

#include "Os.h"

#define SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0() SuspendOSInterrupts()
#define SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0()  ResumeOSInterrupts()

#endif /* SCHM_PDUR_H */
