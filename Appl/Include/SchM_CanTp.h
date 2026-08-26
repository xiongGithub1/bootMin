/**********************************************************************************************************************
 * Boot slim SchM stubs (no RTE)
 *********************************************************************************************************************/
#ifndef SCHM_CANTP_H
#define SCHM_CANTP_H

#include "Os.h"

/* CANTP_RXTX_MAINFUNCTION_API=STD_OFF → CanTp.h has no prototype; declare like RTE SchM */
void CanTp_MainFunction(void);

#define SchM_Enter_CanTp_CANTP_EXCLUSIVE_AREA_0() SuspendAllInterrupts()
#define SchM_Exit_CanTp_CANTP_EXCLUSIVE_AREA_0()  ResumeAllInterrupts()

#endif /* SCHM_CANTP_H */
