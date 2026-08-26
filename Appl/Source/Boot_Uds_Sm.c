/**********************************************************************************************************************
 * Boot_Uds_Sm.c — Bootloader programming state machine + per-session security
 *********************************************************************************************************************/
#include "Boot_Uds_Sm.h"
#include "Boot_Uds.h"
#include "Boot_Dcm_Cfg.h"

static Boot_SmStateType Boot_Sm_State = BOOT_SM_DEFAULT;
static uint8 Boot_Sm_UnlockExt = BOOT_DCM_SEC_LEVEL_NONE;
static uint8 Boot_Sm_UnlockProg = BOOT_DCM_SEC_LEVEL_NONE;

void Boot_Sm_Init(void)
{
  Boot_Sm_State = BOOT_SM_DEFAULT;
  Boot_Sm_UnlockExt = BOOT_DCM_SEC_LEVEL_NONE;
  Boot_Sm_UnlockProg = BOOT_DCM_SEC_LEVEL_NONE;
}

Boot_SmStateType Boot_Sm_GetState(void)
{
  return Boot_Sm_State;
}

boolean Boot_Sm_IsSecurityUnlocked(void)
{
  return ((Boot_Sm_State == BOOT_SM_SECURED) ||
          (Boot_Sm_State == BOOT_SM_ERASED) ||
          (Boot_Sm_State == BOOT_SM_DOWNLOADING) ||
          (Boot_Sm_State == BOOT_SM_PROGRAMMED) ||
          (Boot_Sm_State == BOOT_SM_CHECKED)) ? TRUE : FALSE;
}

boolean Boot_Sm_IsSecLevelOpen(uint8 level)
{
  uint8 cur;

  if (level == BOOT_DCM_SEC_LEVEL_NONE)
  {
    return TRUE;
  }
  if (Boot_Sm_State == BOOT_SM_DEFAULT)
  {
    return FALSE;
  }
  if (Boot_Sm_State == BOOT_SM_EXTENDED)
  {
    cur = Boot_Sm_UnlockExt;
  }
  else
  {
    cur = Boot_Sm_UnlockProg;
  }
  return (cur == level) ? TRUE : FALSE;
}

void Boot_Sm_OnSession(uint8 session)
{
  switch (session)
  {
    case BOOT_UDS_SESSION_DEFAULT:
      Boot_Sm_UnlockExt = BOOT_DCM_SEC_LEVEL_NONE;
      Boot_Sm_UnlockProg = BOOT_DCM_SEC_LEVEL_NONE;
      Boot_Sm_State = BOOT_SM_DEFAULT;
      break;
    case BOOT_UDS_SESSION_EXTENDED:
      Boot_Sm_State = BOOT_SM_EXTENDED;
      break;
    case BOOT_UDS_SESSION_PROGRAMMING:
      /* Restart flash sequence; restore SECURED if this session still has L1. */
      if (Boot_Sm_UnlockProg == BOOT_UDS_FLASH_SEC_LEVEL)
      {
        Boot_Sm_State = BOOT_SM_SECURED;
      }
      else
      {
        Boot_Sm_State = BOOT_SM_PROG;
      }
      break;
    default:
      Boot_Sm_UnlockExt = BOOT_DCM_SEC_LEVEL_NONE;
      Boot_Sm_UnlockProg = BOOT_DCM_SEC_LEVEL_NONE;
      Boot_Sm_State = BOOT_SM_DEFAULT;
      break;
  }
}

void Boot_Sm_OnSecurityUnlockedLevel(uint8 level)
{
  if ((level != BOOT_DCM_SEC_LEVEL_L1) && (level != BOOT_DCM_SEC_LEVEL_L3))
  {
    return;
  }

  if (Boot_Sm_State == BOOT_SM_EXTENDED)
  {
    Boot_Sm_UnlockExt = level;
    return;
  }

  Boot_Sm_UnlockProg = level;
  if ((Boot_Sm_State == BOOT_SM_PROG) && (level == BOOT_UDS_FLASH_SEC_LEVEL))
  {
    Boot_Sm_State = BOOT_SM_SECURED;
  }
}

void Boot_Sm_OnSecurityLocked(void)
{
  if (Boot_Sm_State == BOOT_SM_EXTENDED)
  {
    Boot_Sm_UnlockExt = BOOT_DCM_SEC_LEVEL_NONE;
    return;
  }

  Boot_Sm_UnlockProg = BOOT_DCM_SEC_LEVEL_NONE;

  if ((Boot_Sm_State == BOOT_SM_SECURED) ||
      (Boot_Sm_State == BOOT_SM_ERASED) ||
      (Boot_Sm_State == BOOT_SM_DOWNLOADING) ||
      (Boot_Sm_State == BOOT_SM_PROGRAMMED) ||
      (Boot_Sm_State == BOOT_SM_CHECKED))
  {
    Boot_Sm_State = BOOT_SM_PROG;
  }
}

Std_ReturnType Boot_Sm_OnEraseOk(void)
{
  if ((Boot_Sm_State != BOOT_SM_SECURED) &&
      (Boot_Sm_State != BOOT_SM_ERASED) &&
      (Boot_Sm_State != BOOT_SM_PROGRAMMED) &&
      (Boot_Sm_State != BOOT_SM_CHECKED))
  {
    return E_NOT_OK;
  }
  Boot_Sm_State = BOOT_SM_ERASED;
  return E_OK;
}

Std_ReturnType Boot_Sm_OnDownloadStart(void)
{
  if (Boot_Sm_State != BOOT_SM_ERASED)
  {
    return E_NOT_OK;
  }
  Boot_Sm_State = BOOT_SM_DOWNLOADING;
  return E_OK;
}

void Boot_Sm_OnDownloadAbort(void)
{
  if ((Boot_Sm_State == BOOT_SM_DOWNLOADING) || (Boot_Sm_State == BOOT_SM_ERASED))
  {
    /* Require erase again before next download */
    Boot_Sm_State = BOOT_SM_SECURED;
  }
}

Std_ReturnType Boot_Sm_OnTransferExitOk(void)
{
  if (Boot_Sm_State != BOOT_SM_DOWNLOADING)
  {
    return E_NOT_OK;
  }
  Boot_Sm_State = BOOT_SM_PROGRAMMED;
  return E_OK;
}

Std_ReturnType Boot_Sm_OnCheckDepOk(void)
{
  if (Boot_Sm_State != BOOT_SM_PROGRAMMED)
  {
    return E_NOT_OK;
  }
  Boot_Sm_State = BOOT_SM_CHECKED;
  return E_OK;
}

boolean Boot_Sm_AllowSecurityAccess(void)
{
  return ((Boot_Sm_State == BOOT_SM_PROG) ||
          (Boot_Sm_State == BOOT_SM_EXTENDED) ||
          (Boot_Sm_IsSecurityUnlocked() == TRUE)) ? TRUE : FALSE;
}

boolean Boot_Sm_AllowErase(void)
{
  /* Erase allowed when secured; also allow re-erase from ERASED/PROGRAMMED */
  return ((Boot_Sm_State == BOOT_SM_SECURED) ||
          (Boot_Sm_State == BOOT_SM_ERASED) ||
          (Boot_Sm_State == BOOT_SM_PROGRAMMED) ||
          (Boot_Sm_State == BOOT_SM_CHECKED)) ? TRUE : FALSE;
}

boolean Boot_Sm_AllowDownload(void)
{
  return (Boot_Sm_State == BOOT_SM_ERASED) ? TRUE : FALSE;
}

boolean Boot_Sm_AllowTransferData(void)
{
  return (Boot_Sm_State == BOOT_SM_DOWNLOADING) ? TRUE : FALSE;
}

boolean Boot_Sm_AllowTransferExit(void)
{
  return (Boot_Sm_State == BOOT_SM_DOWNLOADING) ? TRUE : FALSE;
}

boolean Boot_Sm_AllowCheckDep(void)
{
  return (Boot_Sm_State == BOOT_SM_PROGRAMMED) ? TRUE : FALSE;
}
