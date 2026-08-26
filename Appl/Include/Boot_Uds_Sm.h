/**********************************************************************************************************************
 * Boot_Uds_Sm.h â€?Bootloader programming state machine (ISO 14229 sequence gate)
 *********************************************************************************************************************/
#ifndef BOOT_UDS_SM_H
#define BOOT_UDS_SM_H

#include "Std_Types.h"

/*
 *  DEFAULT â”€â”€10 02â”€â”€â–?PROG â”€â”€27 unlockâ”€â”€â–?SECURED â”€â”€31 eraseâ”€â”€â–?ERASED
 *     â–?                 â”?                   â–?                   â”?
 *     â”?                 â”?                   â”?                   â”?34
 *   10 01 / leave        â”?                   â””â”€â”€ fail/abort â”€â”€â”€â”€â”€â”€â”?
 *                        â”?                                        â–?
 *  EXTENDED â—„â”€â”€10 03â”€â”€   â”?                             DOWNLOADING â”€â”€36â”€â”€â”?
 *                        â”?                                        â”?     â”?
 *                        â”?                                        â””â”€â”€â—„â”€â”€â”€â”?
 *                        â”?                                        â”?37
 *                        â”?                                        â–?
 *                        â”?                                  PROGRAMMED â”€â”€31 FF01â”€â”€â–?CHECKED
 *                        â”?                                        â”?
 *                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ session leave / 10 01 â”€â”€â”€â”€â”€â”€â”?
 */

typedef enum
{
  BOOT_SM_DEFAULT = 0,
  BOOT_SM_EXTENDED,
  BOOT_SM_PROG,         /* programming session, security locked */
  BOOT_SM_SECURED,      /* unlocked, not erased yet */
  BOOT_SM_ERASED,       /* ready for RequestDownload */
  BOOT_SM_DOWNLOADING,  /* TransferData in progress */
  BOOT_SM_PROGRAMMED,   /* TransferExit OK */
  BOOT_SM_CHECKED       /* CheckProgrammingDependencies OK */
} Boot_SmStateType;

void Boot_Sm_Init(void);
Boot_SmStateType Boot_Sm_GetState(void);

void Boot_Sm_OnSession(uint8 session);
void Boot_Sm_OnSecurityUnlockedLevel(uint8 level);
void Boot_Sm_OnSecurityLocked(void);

boolean Boot_Sm_IsSecLevelOpen(uint8 level);

Std_ReturnType Boot_Sm_OnEraseOk(void);
Std_ReturnType Boot_Sm_OnDownloadStart(void);
void Boot_Sm_OnDownloadAbort(void);
Std_ReturnType Boot_Sm_OnTransferExitOk(void);
Std_ReturnType Boot_Sm_OnCheckDepOk(void);

boolean Boot_Sm_AllowSecurityAccess(void);
boolean Boot_Sm_AllowErase(void);
boolean Boot_Sm_AllowDownload(void);
boolean Boot_Sm_AllowTransferData(void);
boolean Boot_Sm_AllowTransferExit(void);
boolean Boot_Sm_AllowCheckDep(void);

boolean Boot_Sm_IsSecurityUnlocked(void);

#endif /* BOOT_UDS_SM_H */
