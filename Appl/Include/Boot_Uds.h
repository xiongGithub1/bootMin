/**********************************************************************************************************************
 * Boot_Uds.h â€?Cdd mini-UDS public API
 *********************************************************************************************************************/
#ifndef BOOT_UDS_H
#define BOOT_UDS_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Boot_Uds_Cfg.h"

/* Session IDs == 0x10 sub-functions */
#define BOOT_UDS_SESSION_DEFAULT         BOOT_SF_DSC_DEFAULT
#define BOOT_UDS_SESSION_PROGRAMMING     BOOT_SF_DSC_PROGRAMMING
#define BOOT_UDS_SESSION_EXTENDED        BOOT_SF_DSC_EXTENDED

#define BOOT_UDS_NEG                     (0x7Fu)
#define BOOT_UDS_NRC_SNS                 (0x11u)
#define BOOT_UDS_NRC_SFNS                (0x12u)
#define BOOT_UDS_NRC_IMLOIF              (0x13u)
#define BOOT_UDS_NRC_CNC                 (0x22u)
#define BOOT_UDS_NRC_RSE                 (0x24u)
#define BOOT_UDS_NRC_ROOR                (0x31u)
#define BOOT_UDS_NRC_SAD                 (0x33u)
#define BOOT_UDS_NRC_IK                  (0x35u)
#define BOOT_UDS_NRC_EAT                 (0x36u) /* exceededNumberOfAttempts */
#define BOOT_UDS_NRC_RTDNE               (0x37u) /* requiredTimeDelayNotExpired */
#define BOOT_UDS_NRC_ENOA                (0x70u) /* uploadDownloadNotAccepted */
#define BOOT_UDS_NRC_GPF                 (0x72u)
#define BOOT_UDS_NRC_WBSC                (0x73u)
#define BOOT_UDS_NRC_RESPONSE_PENDING    (0x78u)
#define BOOT_UDS_NRC_SNSIAS              (0x7Fu) /* serviceNotSupportedInActiveSession */
#define BOOT_UDS_SUPPRESS_POS_RSP        BOOT_SF_SUPPRESS_POS_RSP

/* Service processors registered in Boot_Dcm_SvcTable (table-driven dispatch) */
void Boot_Uds_HandleDsc(void);
void Boot_Uds_HandleEcuReset(void);
void Boot_Uds_HandleTesterPresent(void);
void Boot_Uds_HandleRdbi(void);
void Boot_Uds_HandleWdbi(void);
void Boot_Uds_HandleSecurityAccess(void);

/* Clear SecurityAccess seed/key state on session change (called by Boot_Dcm) */
void Boot_Uds_ResetSecurityAccess(void);

/* Factory DID contents (S3 / 10 01). Business DIDs are extended-session only. */
void Boot_Uds_DidReset(void);

uint8 Boot_Uds_GetSession(void);
boolean Boot_Uds_IsSecurityUnlocked(void);

void Boot_Uds_SendNeg(uint8 sid, uint8 nrc);
void Boot_Uds_Transmit(PduLengthType len);
void Boot_Uds_MainFunction(void);
/* After ActivateSwap / 0x11: queue System Reset once TX is done. */
void Boot_Uds_RequestSoftwareReset(void);

uint8* Boot_Uds_GetRxBuf(void);
PduLengthType Boot_Uds_GetRxLen(void);
uint8* Boot_Uds_GetTxBuf(void);

#endif /* BOOT_UDS_H */
