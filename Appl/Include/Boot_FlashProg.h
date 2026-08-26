/**********************************************************************************************************************
 * Boot_FlashProg.h — UDS download / erase (0x34/0x36/0x37/0x31) via FlsLoader
 *********************************************************************************************************************/
#ifndef BOOT_FLASHPROG_H
#define BOOT_FLASHPROG_H

#include "Std_Types.h"

void Boot_FlashProg_Init(void);
void Boot_FlashProg_OnSessionChange(uint8 session);
void Boot_FlashProg_HandleRequestDownload(void);
void Boot_FlashProg_HandleTransferData(void);
void Boot_FlashProg_HandleRequestTransferExit(void);
void Boot_FlashProg_HandleRoutineControl(void);

#endif /* BOOT_FLASHPROG_H */
