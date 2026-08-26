/**********************************************************************************************************************
 *  Appl_CanIf_Cbk.h — CanIf CDD callbacks (no CanSM)
 *********************************************************************************************************************/
#ifndef APPL_CANIF_CBK_H
#define APPL_CANIF_CBK_H

#include "CanIf.h"

FUNC(void, CANIF_APPL_CODE) Appl_CanIf_ControllerBusOff(uint8 ControllerId);
FUNC(void, CANIF_APPL_CODE) Appl_CanIf_ControllerModeIndicat(uint8 ControllerId, CanIf_ControllerModeType ControllerMode);

#endif /* APPL_CANIF_CBK_H */
