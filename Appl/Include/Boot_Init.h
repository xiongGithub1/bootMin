/**********************************************************************************************************************
 * Boot_Init.h — Slim Boot driver bring-up + COM cyclic
 *********************************************************************************************************************/
#ifndef BOOT_INIT_H
#define BOOT_INIT_H

#include "Std_Types.h"

void Boot_Init(void);
void Boot_StartCommunication(void);
void Boot_ComMainFunctions(void);
void Boot_CanRxNotify(uint8 pduId, uint8 sid);

#endif /* BOOT_INIT_H */
