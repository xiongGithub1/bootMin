/**********************************************************************************************************************
 * Boot_Uds_Sid.h — UDS SID / sub-function / RID / DID from Boot Dcm (autosarTc364_Boot)
 *
 * Source of truth (aligned with last364 session/security numbering):
 *   autosarTc364_Boot/Appl/GenData/Dcm_Lcfg.c  (SvcId / SubFunc / RID / DID look-up)
 *   last364/Appl/GenData/Dcm_Lcfg.c            (same 0x10/0x27 SF values)
 *********************************************************************************************************************/
#ifndef BOOT_UDS_SID_H
#define BOOT_UDS_SID_H

/* ========== Service Identifiers (Dcm_CfgDiagSvcIdLookUpTable) ========== */
#define BOOT_SID_DSC                         (0x10u) /* DiagnosticSessionControl */
#define BOOT_SID_ER                          (0x11u) /* ECUReset */
#define BOOT_SID_RDBI                        (0x22u) /* ReadDataByIdentifier */
#define BOOT_SID_SA                          (0x27u) /* SecurityAccess */
#define BOOT_SID_WDBI                        (0x2Eu) /* WriteDataByIdentifier */
#define BOOT_SID_RC                          (0x31u) /* RoutineControl */
#define BOOT_SID_RD                          (0x34u) /* RequestDownload */
#define BOOT_SID_TD                          (0x36u) /* TransferData */
#define BOOT_SID_RTE                         (0x37u) /* RequestTransferExit */
#define BOOT_SID_TP                          (0x3Eu) /* TesterPresent */

/* Positive response = SID | 0x40 */
#define BOOT_POS(sid)                        ((uint8)((sid) + 0x40u))

/* ========== 0x10 DiagnosticSessionControl (Dcm_CfgSvc10SubFuncLookUpTable) ========== */
#define BOOT_SF_DSC_DEFAULT                  (0x01u)
#define BOOT_SF_DSC_PROGRAMMING              (0x02u)
#define BOOT_SF_DSC_EXTENDED                 (0x03u)

/* ========== 0x11 ECUReset (Dcm_CfgSvc11SubFuncLookUpTable) ========== */
#define BOOT_SF_ER_HARD                      (0x01u) /* hardReset */
#define BOOT_SF_ER_SOFT                      (0x03u) /* softReset */

/* ========== 0x27 SecurityAccess (Dcm_CfgSvc27SubFuncLookUpTable) ========== */
/* Level UnlockedL1 (programming): seed 0x01 / key 0x02, 4 bytes */
#define BOOT_SF_SA_L1_SEED                   (0x01u)
#define BOOT_SF_SA_L1_KEY                    (0x02u)
/* Level_3: seed 0x03 / key 0x04, 4 bytes (Boot Dcm) */
#define BOOT_SF_SA_L3_SEED                   (0x03u)
#define BOOT_SF_SA_L3_KEY                    (0x04u)

#define BOOT_SA_SEED_LEN_L1                  (4u)
#define BOOT_SA_KEY_LEN_L1                   (4u)
#define BOOT_SA_SEED_LEN_L3                  (4u)
#define BOOT_SA_KEY_LEN_L3                   (4u)

/* ========== 0x3E TesterPresent ========== */
#define BOOT_SF_TP_ZERO                      (0x00u)

/* ========== 0x31 RoutineControl sub-functions (ISO 14229) ========== */
#define BOOT_SF_RC_START                     (0x01u)
#define BOOT_SF_RC_STOP                      (0x02u)
#define BOOT_SF_RC_REQ_RESULTS               (0x03u)

/* RIDs — Boot Dcm_CfgRidMgrRidLookUpTable */
#define BOOT_RID_ERASE_MEMORY                (0xFF00u) /* EraseMemory — Start only */
#define BOOT_RID_CHECK_PROG_DEP              (0xFF01u) /* CheckProgrammingDependencies — Start (+1 byte in Dcm) */
#define BOOT_RID_CHECK_MEMORY                (0xFF02u) /* CheckMemory — Start + 4 B CRC32 BE */

/* ========== DIDs — Boot Dcm_CfgDidMgrDidLookUpTable ========== */
#define BOOT_DID_DATA_DIAG                   (0x0101u)
#define BOOT_DID_BOOT_SOFTWARE               (0xF180u) /* 1+4 bytes: NumberOfModules + Boot SW ID */
#define BOOT_DID_SPARE_PART_NUMBER           (0xF187u) /* 4 bytes */
#define BOOT_DID_ECU_PART_NUMBER             (0xF189u) /* 13 bytes */
#define BOOT_DID_SERIAL_NUMBER               (0xF18Cu) /* 4 bytes */
#define BOOT_DID_VIN                         (0xF190u) /* 17 bytes */
#define BOOT_DID_HW_VERSION                  (0xF193u) /* 4 bytes */
#define BOOT_DID_FINGERPRINT                 (0xF198u) /* write: tool serial 8 + shop 1 + date 8 */

#define BOOT_DID_F180_LEN                    (5u)
#define BOOT_DID_F187_LEN                    (4u)
#define BOOT_DID_F189_LEN                    (13u)
#define BOOT_DID_F18C_LEN                    (4u)
#define BOOT_DID_F190_LEN                    (17u)
#define BOOT_DID_F193_LEN                    (4u)
#define BOOT_DID_F198_LEN                    (17u)

/* ========== 0x34 format (common / ISO) ========== */
#define BOOT_RD_DATA_FORMAT_ID               (0x00u) /* uncompressed */
#define BOOT_RD_ALFID_44                     (0x44u) /* 4-byte addr + 4-byte size */
#define BOOT_RD_MAXBLK_LEN_FORMAT            (0x20u) /* 2-byte maxNumberOfBlockLength */

/* ========== suppressPosRspMsgIndicationBit ========== */
#define BOOT_SF_SUPPRESS_POS_RSP             (0x80u)

#endif /* BOOT_UDS_SID_H */
