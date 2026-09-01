/**********************************************************************************************************************
 * Boot_App.h — APP validity, CheckMemory CRC, stay-in-boot / jump
 *********************************************************************************************************************/
#ifndef BOOT_APP_H
#define BOOT_APP_H

#include "Std_Types.h"
#include "Boot_Mem.h"

/* 1 = measure APP image CRC time in Boot_App_IsImageValid (STM0 TIM0). Watch globals below. */
#ifndef BOOT_APP_CRC_TIME_MEASURE
# define BOOT_APP_CRC_TIME_MEASURE  (0u)
#endif

#if (BOOT_APP_CRC_TIME_MEASURE == 1)
/* After IsImageValid: Ticks = STM0 delta; Us ≈ Ticks/100 @ fSTM=100 MHz. */
extern volatile uint32 Boot_App_CrcMeas_Ticks;
extern volatile uint32 Boot_App_CrcMeas_Us;
extern volatile uint32 Boot_App_CrcMeas_Len;
extern volatile uint32 Boot_App_CrcMeas_Crc;
extern volatile uint32 Boot_App_CrcMeas_Ok; /* 1 = matched hdr->crc32 */
#endif

uint32 Boot_App_Crc32(const uint8* data, uint32 length);
/* Continue CRC: crcPrev is the previous Crc_CalculateCRC32 result (IsFirstCall=FALSE). */
uint32 Boot_App_Crc32Acc(uint32 crcPrev, const uint8* data, uint32 length);

boolean Boot_App_IsRangeInApp(uint32 start, uint32 length);
uint32  Boot_App_ToCached(uint32 addr);
uint32  Boot_App_ToHw(uint32 cachedOrHw);

boolean Boot_App_IsImageValid(void);
boolean Boot_App_IsRequestBoot(void);
void    Boot_App_ClearRequestBoot(void);
/* HIS: after APP 10 02 reset, Boot sends 50 02 once COM is up. */
boolean Boot_App_IsPendingProgPosResp(void);
boolean Boot_App_TakePendingProgPosResp(void);
uint32  Boot_App_MixEntropy(void);

/* Call as first step of Boot_Init — before Mcu/CAN/Fls — so jump sees a clean HW state. */
void    Boot_App_TryStart(void);

/* Arm deinit path if TryStart is ever used after stack/com init (or late re-entry). */
void    Boot_App_NotifyFlsInit(void);
void    Boot_App_NotifyComStart(void);

#endif /* BOOT_APP_H */
