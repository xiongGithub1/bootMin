/**********************************************************************************************************************
 * Boot_Dcm_Cfg.h - Production hand-written mini-DCM configuration
 *
 * Single place that defines:
 *   - which sessions exist and their bit positions
 *   - the SecurityAccess levels used for service gating
 *   - P2 / P2* / S3 server timings
 *   - the number of entries in the service table
 *
 * The service table itself lives in Boot_Dcm_Cfg.c (Boot_Dcm_SvcTable).
 *********************************************************************************************************************/
#ifndef BOOT_DCM_CFG_H
#define BOOT_DCM_CFG_H

#include "Std_Types.h"
#include "Boot_Uds_Cfg.h"
#include "Boot_Uds_Sid.h"

/* ============================================================================
 * Sessions
 * Session sub-functions are 0x01 (default) / 0x02 (programming) / 0x03 (extended).
 * Each session owns one bit in the service table's SessionMask:
 *   default = 0x01, programming = 0x02, extended = 0x04
 * ==========================================================================*/
#define BOOT_DCM_SESSION_BIT(session)       ((uint8)(1u << ((session) - 1u)))

#define BOOT_DCM_SESSION_MASK_ALL           (BOOT_DCM_SESSION_BIT(BOOT_SF_DSC_DEFAULT) | \
                                             BOOT_DCM_SESSION_BIT(BOOT_SF_DSC_PROGRAMMING) | \
                                             BOOT_DCM_SESSION_BIT(BOOT_SF_DSC_EXTENDED))
#define BOOT_DCM_SESSION_MASK_PROG_EXT      (BOOT_DCM_SESSION_BIT(BOOT_SF_DSC_PROGRAMMING) | \
                                             BOOT_DCM_SESSION_BIT(BOOT_SF_DSC_EXTENDED))
#define BOOT_DCM_SESSION_MASK_PROG_ONLY     (BOOT_DCM_SESSION_BIT(BOOT_SF_DSC_PROGRAMMING))
#define BOOT_DCM_SESSION_MASK_EXT_ONLY      (BOOT_DCM_SESSION_BIT(BOOT_SF_DSC_EXTENDED))

/* ============================================================================
 * SecurityAccess levels
 * 0x00 = no access restriction, otherwise the SecurityAccess level that must be
 * unlocked (Boot_Uds_Sm tracks which level is currently open).
 * ==========================================================================*/
#define BOOT_DCM_SEC_LEVEL_NONE             (0x00u)
#define BOOT_DCM_SEC_LEVEL_L1               (BOOT_UDS_FLASH_SEC_LEVEL)  /* 0x01/0x02 seed/key */
#define BOOT_DCM_SEC_LEVEL_L3               (3u)                         /* 0x03/0x04 seed/key */

/* ============================================================================
 * Server timings
 * P2 / P2* derive from the values reported in the 0x10 positive response so
 * that "advertised" and "enforced" timing can never drift apart.
 * ==========================================================================*/
#define BOOT_DCM_P2_SERVER_MS               ((uint16)(BOOT_UDS_P2_SERVER_10MS * 10u))
#define BOOT_DCM_P2STAR_SERVER_MS           ((uint16)(BOOT_UDS_P2EX_SERVER_10MS * 10u))

/* S3: session timeout in a non-default session. On expiry the DCM returns to
 * the default session and locks SecurityAccess again. */
#define BOOT_DCM_S3_SERVER_MS               (5000u)

/* Number of entries in Boot_Dcm_SvcTable (Boot_Dcm_Cfg.c) */
#define BOOT_DCM_SVC_TABLE_SIZE             (10u)

#endif /* BOOT_DCM_CFG_H */
