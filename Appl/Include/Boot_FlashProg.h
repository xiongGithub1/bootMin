/**********************************************************************************************************************
 * Boot_FlashProg.h — UDS download / erase (0x34/0x36/0x37/0x31) via FlsLoader
 * With BOOT_SWAP_PROGRAM_INACTIVE: erase/write go to inactive physical bank
 * (A active → PF1 @ 0xA03xxxxx; B active → PF0 @ 0xA00xxxxx). UDS addresses stay logical.
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
