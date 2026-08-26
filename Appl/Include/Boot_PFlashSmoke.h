/**********************************************************************************************************************
 * Boot_PFlashSmoke.h — PSPR erase/write (TC234-style, no FlsLoader busy-path)
 *********************************************************************************************************************/
#ifndef BOOT_PFLASH_SMOKE_H
#define BOOT_PFLASH_SMOKE_H

#include "Std_Types.h"

/* 1 = RID erase + 0x36 write use PSPR smoke path; 0 = FlsLoader */
#ifndef BOOT_PFLASH_SMOKE_TEST
# define BOOT_PFLASH_SMOKE_TEST  0
#endif

#ifndef BOOT_PFLASH_SMOKE_HALT_ON_OK
# define BOOT_PFLASH_SMOKE_HALT_ON_OK  0
#endif

void Boot_PFlashSmoke_Init(void);

/* Erase one 16 KB sector at hardware address (0xAxxx). */
Std_ReturnType Boot_PFlashSmoke_EraseOneSector(uint32 hwSectorAddr);

/* Erase sectorCount consecutive 16 KB sectors starting at hwSectorAddr. */
Std_ReturnType Boot_PFlashSmoke_EraseSectors(uint32 hwSectorAddr, uint32 sectorCount);

/* Program length bytes (multiple of 32) at hwAddr; data must be in RAM. */
Std_ReturnType Boot_PFlashSmoke_Write(uint32 hwAddr, uint32 length, const uint8 *data);

extern volatile uint32 Boot_Smoke_OpResult; /* 0=OK */
extern volatile uint32 Boot_Smoke_ErrSr;
extern volatile uint32 Boot_Smoke_Status;
extern volatile uint32 Boot_Smoke_PsprOk;
extern volatile uint32 Boot_Smoke_CopyLen;
extern volatile uint32 Boot_Smoke_Phase;
extern volatile uint32 Boot_Smoke_PsprWord;
extern volatile uint32 Boot_Smoke_HwAddr;

#endif /* BOOT_PFLASH_SMOKE_H */
