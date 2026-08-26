/**********************************************************************************************************************
 * Boot_Dcm_Cfg.c - UDS service table (source of truth for service gating)
 *
 * One row per supported service (aligned with Dcm_Lcfg.c, 10 services):
 *   SID          service identifier
 *   SessionMask  sessions that may call the service
 *   SecLevel     SecurityAccess level that must be unlocked (0 = none)
 *   Handler      service processor
 *
 * Add/remove services here only - no switch-case in the dispatch path.
 *********************************************************************************************************************/
#include "Boot_Dcm.h"
#include "Boot_Uds.h"
#include "Boot_FlashProg.h"

const Boot_Dcm_SvcTableEntryType Boot_Dcm_SvcTable[BOOT_DCM_SVC_TABLE_SIZE] =
{
  /* SID   Session mask                     SecLevel  Handler */
  { BOOT_SID_DSC,  BOOT_DCM_SESSION_MASK_ALL,       BOOT_DCM_SEC_LEVEL_NONE, Boot_Uds_HandleDsc },
  { BOOT_SID_ER,   BOOT_DCM_SESSION_MASK_ALL,       BOOT_DCM_SEC_LEVEL_NONE, Boot_Uds_HandleEcuReset },
  { BOOT_SID_RDBI, BOOT_DCM_SESSION_MASK_ALL,       BOOT_DCM_SEC_LEVEL_NONE, Boot_Uds_HandleRdbi },
  { BOOT_SID_SA,   BOOT_DCM_SESSION_MASK_PROG_EXT,  BOOT_DCM_SEC_LEVEL_NONE, Boot_Uds_HandleSecurityAccess },
  { BOOT_SID_WDBI, BOOT_DCM_SESSION_MASK_PROG_EXT,  BOOT_DCM_SEC_LEVEL_L1,   Boot_Uds_HandleWdbi },
  { BOOT_SID_RC,   BOOT_DCM_SESSION_MASK_PROG_EXT,  BOOT_DCM_SEC_LEVEL_L1,   Boot_FlashProg_HandleRoutineControl },
  { BOOT_SID_RD,   BOOT_DCM_SESSION_MASK_PROG_ONLY, BOOT_DCM_SEC_LEVEL_L1,   Boot_FlashProg_HandleRequestDownload },
  { BOOT_SID_TD,   BOOT_DCM_SESSION_MASK_PROG_ONLY, BOOT_DCM_SEC_LEVEL_L1,   Boot_FlashProg_HandleTransferData },
  { BOOT_SID_RTE,  BOOT_DCM_SESSION_MASK_PROG_ONLY, BOOT_DCM_SEC_LEVEL_L1,   Boot_FlashProg_HandleRequestTransferExit },
  { BOOT_SID_TP,   BOOT_DCM_SESSION_MASK_ALL,       BOOT_DCM_SEC_LEVEL_NONE, Boot_Uds_HandleTesterPresent }
};
