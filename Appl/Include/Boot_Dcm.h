/**********************************************************************************************************************
 * Boot_Dcm.h - Production hand-written mini-DCM public API
 *
 * The dispatcher is table-driven: every service is one entry in
 * Boot_Dcm_SvcTable (Boot_Dcm_Cfg.c) that carries its session permission mask,
 * required SecurityAccess level and its handler function. The DCM core
 * (Boot_Dcm.c) performs lookup, session/security gating, P2 / P2* / S3 timing and
 * negative response generation before/after calling the handler.
 *********************************************************************************************************************/
#ifndef BOOT_DCM_H
#define BOOT_DCM_H

#include "Std_Types.h"
#include "Boot_Dcm_Cfg.h"

/* Service processor signature: one function per SID */
typedef void (*Boot_Dcm_SvcHandlerType)(void);

typedef struct
{
  uint8  Sid;                       /* service identifier (e.g. 0x10 .. 0x3E) */
  uint8  SessionMask;               /* bit mask of sessions that may call it  */
  uint8  SecLevel;                  /* required SecurityAccess level, 0 = none */
  Boot_Dcm_SvcHandlerType Handler;  /* service processor                     */
} Boot_Dcm_SvcTableEntryType;

/* Service table, defined in Boot_Dcm_Cfg.c (const, flash) */
extern const Boot_Dcm_SvcTableEntryType Boot_Dcm_SvcTable[BOOT_DCM_SVC_TABLE_SIZE];

/* --- DCM core ------------------------------------------------------------- */
void Boot_Dcm_Init(void);

/* 1 ms tick: runs S3 session watchdog and P2/P2* response watchdogs.
 * Call from the 1 ms cyclic task (Boot_ComMainFunctions). */
void Boot_Dcm_MainFunction(void);

/* Dispatch one completely received UDS request (transport Rx indication). */
void Boot_Dcm_ProcessRequest(void);

/* --- Session management --------------------------------------------------- */
uint8 Boot_Dcm_GetSession(void);

/* Switch to another session (locks security, resets programming sequence on a
 * real session change; same-session request only refreshes S3). */
void Boot_Dcm_ChangeSession(uint8 session);

/* --- Long-running service support ----------------------------------------- */
/* Handler hook: sends NRC 0x78 (responsePending) and restarts the P2* window.
 * The handler must send the final positive/negative response before P2*
 * expires. */
void Boot_Dcm_ResponsePending(void);

#endif /* BOOT_DCM_H */
