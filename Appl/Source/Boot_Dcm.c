/**********************************************************************************************************************
 * Boot_Dcm.c - Production hand-written mini-DCM core
 *
 * Flow for every received request:
 *   1. SID lookup in Boot_Dcm_SvcTable            -> NRC 0x11 (SNS)
 *   2. session permission (SessionMask)           -> NRC 0x7F (SNSIAS)
 *   3. SecurityAccess permission (SecLevel)       -> NRC 0x33 (SAD)
 *   4. dispatch handler inside the P2 window
 *
 * The core also owns:
 *   - S3 session watchdog (return to default session + lock security)
 *   - P2 / P2* response watchdogs and NRC 0x78 responsePending support
 *********************************************************************************************************************/
#include "Boot_Dcm.h"
#include "Boot_Uds.h"
#include "Boot_Uds_Sm.h"
#include "Boot_FlashProg.h"

typedef enum
{
  BOOT_DCM_RSP_IDLE = 0,
  BOOT_DCM_RSP_RUNNING,  /* request dispatched, final response expected within P2  */
  BOOT_DCM_RSP_PENDING   /* NRC 0x78 sent, final response expected within P2*      */
} Boot_Dcm_RspStateType;

static uint8 Boot_Dcm_Session = BOOT_UDS_SESSION_DEFAULT;
static uint8 Boot_Dcm_PendingSid;

static uint16 Boot_Dcm_S3Ms;
static uint16 Boot_Dcm_P2Ms;
static uint16 Boot_Dcm_P2StarMs;
static Boot_Dcm_RspStateType Boot_Dcm_RspState = BOOT_DCM_RSP_IDLE;

/* A service overran its response window (P2 or P2*): abort the flash sequence
 * and free the response state machine. In this synchronous bootloader this is a
 * defensive path; it becomes active once a handler uses ResponsePending(). */
static void Boot_Dcm_AbortActive(void)
{
  Boot_Sm_OnDownloadAbort();
  Boot_FlashProg_Init();
  Boot_Dcm_RspState = BOOT_DCM_RSP_IDLE;
  Boot_Dcm_P2Ms = 0u;
  Boot_Dcm_P2StarMs = 0u;
}

void Boot_Dcm_Init(void)
{
  Boot_Dcm_Session = BOOT_UDS_SESSION_DEFAULT;
  Boot_Dcm_PendingSid = 0u;
  Boot_Dcm_S3Ms = 0u;
  Boot_Dcm_P2Ms = 0u;
  Boot_Dcm_P2StarMs = 0u;
  Boot_Dcm_RspState = BOOT_DCM_RSP_IDLE;
  Boot_Uds_DidReset();
}

uint8 Boot_Dcm_GetSession(void)
{
  return Boot_Dcm_Session;
}

void Boot_Dcm_ChangeSession(uint8 session)
{
  Boot_Dcm_S3Ms = BOOT_DCM_S3_SERVER_MS;

  if (Boot_Dcm_Session == session)
  {
    return; /* same session: keep programming state, only refresh S3 */
  }

  /* Seed/key handshake is always dropped. Unlock is stored per session
   * (extended vs programming) so L1 in extended does not unlock flash. */
  Boot_Uds_ResetSecurityAccess();
  Boot_Sm_OnSession(session);
  Boot_FlashProg_OnSessionChange(session);

  if (session == BOOT_UDS_SESSION_DEFAULT)
  {
    Boot_Uds_DidReset();
  }

  Boot_Dcm_Session = session;
}

void Boot_Dcm_MainFunction(void)
{
  /* --- S3 session watchdog --------------------------------------------- */
  if (Boot_Dcm_Session != BOOT_UDS_SESSION_DEFAULT)
  {
    if (Boot_Dcm_S3Ms > 0u)
    {
      Boot_Dcm_S3Ms--;
    }
    else
    {
      Boot_Dcm_ChangeSession(BOOT_UDS_SESSION_DEFAULT);
    }
  }

  /* --- P2 / P2* response watchdogs ------------------------------------- */
  switch (Boot_Dcm_RspState)
  {
    case BOOT_DCM_RSP_RUNNING:
      if (Boot_Dcm_P2Ms > 0u)
      {
        Boot_Dcm_P2Ms--;
      }
      else
      {
        Boot_Dcm_AbortActive();
      }
      break;

    case BOOT_DCM_RSP_PENDING:
      if (Boot_Dcm_P2StarMs > 0u)
      {
        Boot_Dcm_P2StarMs--;
      }
      else
      {
        Boot_Dcm_AbortActive();
      }
      break;

    default:
      break;
  }
}

void Boot_Dcm_ResponsePending(void)
{
  if (Boot_Dcm_RspState != BOOT_DCM_RSP_RUNNING)
  {
    return;
  }

  Boot_Dcm_RspState = BOOT_DCM_RSP_PENDING;
  Boot_Dcm_P2StarMs = BOOT_DCM_P2STAR_SERVER_MS;
  Boot_Uds_SendNeg(Boot_Dcm_PendingSid, BOOT_UDS_NRC_RESPONSE_PENDING);
}

void Boot_Dcm_ProcessRequest(void)
{
  uint8 sid;
  uint8 sessionBit;
  uint8 i;
  const Boot_Dcm_SvcTableEntryType* svc;

  if (Boot_Uds_GetRxLen() < 1u)
  {
    return;
  }

  sid = Boot_Uds_GetRxBuf()[0];

  /* Any diagnostic request keeps the current session alive (S3 reset). */
  Boot_Dcm_S3Ms = BOOT_DCM_S3_SERVER_MS;

  /* 1) service lookup ---------------------------------------------------- */
  for (i = 0u; i < BOOT_DCM_SVC_TABLE_SIZE; i++)
  {
    if (Boot_Dcm_SvcTable[i].Sid == sid)
    {
      break;
    }
  }

  if (i == BOOT_DCM_SVC_TABLE_SIZE)
  {
    Boot_Uds_SendNeg(sid, BOOT_UDS_NRC_SNS);
    return;
  }

  svc = &Boot_Dcm_SvcTable[i];

  /* 2) session permission ------------------------------------------------ */
  sessionBit = BOOT_DCM_SESSION_BIT(Boot_Dcm_Session);
  if ((svc->SessionMask & sessionBit) == 0u)
  {
    Boot_Uds_SendNeg(sid, BOOT_UDS_NRC_SNSIAS);
    return;
  }

  /* 3) SecurityAccess permission ----------------------------------------- */
  if (Boot_Sm_IsSecLevelOpen(svc->SecLevel) != TRUE)
  {
    Boot_Uds_SendNeg(sid, BOOT_UDS_NRC_SAD);
    return;
  }

  /* 4) dispatch: open the P2 window and call the service ----------------- */
  Boot_Dcm_RspState = BOOT_DCM_RSP_RUNNING;
  Boot_Dcm_P2Ms = BOOT_DCM_P2_SERVER_MS;
  Boot_Dcm_PendingSid = sid;

  svc->Handler();

  /* Synchronous services are finished here. Services that called
   * Boot_Dcm_ResponsePending() keep the P2* window open until the handler
   * sends its final response. */
  if (Boot_Dcm_RspState == BOOT_DCM_RSP_RUNNING)
  {
    Boot_Dcm_RspState = BOOT_DCM_RSP_IDLE;
    Boot_Dcm_P2Ms = 0u;
  }
}
