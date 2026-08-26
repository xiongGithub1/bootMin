/**********************************************************************************************************************
 * Boot_Uds.c â€?Cdd mini-UDS aligned with Boot Dcm (autosarTc364_Boot) + last364 SF numbers
 *********************************************************************************************************************/
#include "Cdd_Cbk.h"
#include "PduR_Cdd.h"
#include "Boot_Init.h"
#include "Boot_Uds.h"
#include "Boot_Dcm.h"
#include "Boot_FlashProg.h"
#include "Boot_Uds_Sm.h"
#include "Boot_App.h"
#include "BrsHw.h"

static uint8 Cdd_TpRxBuf[CDD_TP_RX_BUF_SIZE];
static uint8 Cdd_TpTxBuf[CDD_TP_TX_BUF_SIZE];
static PduLengthType Cdd_TpRxIdx;
static PduLengthType Cdd_TpRxLen;
static PduLengthType Cdd_TpTxIdx;
static PduLengthType Cdd_TpTxLen;
static uint8 Cdd_TpTxBusy;   /* PduR accepted; waiting Cdd_TpTxConfirmation */
static uint8 Cdd_TpTxRetry;  /* buffer ready; PduR not accepted yet         */
static uint8 Cdd_RxDeferred; /* request in RxBuf, wait until TX idle        */

static uint32 Boot_Uds_Seed;
static uint8 Boot_Uds_SeedRequested;
static uint8 Boot_Uds_PendingSecLevel; /* 1 or 3 */
static uint8 Boot_Uds_SaAttempts;
static uint16 Boot_Uds_SaDelayMs;
static uint8 Boot_Uds_ResetPending; /* 0x11: wait for 0x51 TX, then reset */
static uint8 Boot_Uds_ResetHoldMs;

/* DID mirrors Boot Dcm lengths (stubs / RAM) */
static uint8 Boot_Did_F180[BOOT_DID_F180_LEN] = { 0x01u, 0x42u, 0x4Fu, 0x4Fu, 0x54u }; /* 1 module + "BOOT" */
static uint8 Boot_Did_F187[BOOT_DID_F187_LEN];
static uint8 Boot_Did_F189[BOOT_DID_F189_LEN];
static uint8 Boot_Did_F18C[BOOT_DID_F18C_LEN];
static uint8 Boot_Did_F190[BOOT_DID_F190_LEN];
static uint8 Boot_Did_F193[BOOT_DID_F193_LEN];
static uint8 Boot_Did_F198[BOOT_DID_F198_LEN];

uint8 Boot_Uds_GetSession(void)
{
  return Boot_Dcm_GetSession();
}

boolean Boot_Uds_IsSecurityUnlocked(void)
{
  return Boot_Sm_IsSecurityUnlocked();
}

uint8* Boot_Uds_GetRxBuf(void)
{
  return Cdd_TpRxBuf;
}

PduLengthType Boot_Uds_GetRxLen(void)
{
  return Cdd_TpRxLen;
}

uint8* Boot_Uds_GetTxBuf(void)
{
  return Cdd_TpTxBuf;
}

static Std_ReturnType Boot_Uds_TryTransmit(void)
{
  PduInfoType info;

  Cdd_TpTxIdx = 0u;
  info.SduDataPtr = Cdd_TpTxBuf;
  info.SduLength = Cdd_TpTxLen;
  if (PduR_CddTransmit(CddConf_CddPduRUpperLayerTxPdu_CddPduRUpperLayerTxPdu_75c, &info) == E_OK)
  {
    Cdd_TpTxBusy = 1u;
    Cdd_TpTxRetry = 0u;
    return E_OK;
  }

  Cdd_TpTxBusy = 0u;
  Cdd_TpTxRetry = 1u;
  return E_NOT_OK;
}

void Boot_Uds_Transmit(PduLengthType len)
{
  if ((len == 0u) || (len > CDD_TP_TX_BUF_SIZE))
  {
    return;
  }

  /* Buffer already filled by the caller (or by SendNeg). Do not start a new
   * PduR TX while the previous confirmation is still outstanding: CanTp is
   * half-duplex and would return E_NOT_OK; the old implementation discarded
   * that and the tester saw a missing 50 02. */
  Cdd_TpTxLen = len;
  if (Cdd_TpTxBusy != 0u)
  {
    Cdd_TpTxRetry = 1u;
    return;
  }

  (void)Boot_Uds_TryTransmit();
}

void Boot_Uds_MainFunction(void)
{
  if (Boot_Uds_SaDelayMs > 0u)
  {
    Boot_Uds_SaDelayMs--;
    if (Boot_Uds_SaDelayMs == 0u)
    {
      Boot_Uds_SaAttempts = 0u;
    }
  }

  if ((Cdd_TpTxRetry != 0u) && (Cdd_TpTxBusy == 0u) && (Cdd_TpTxLen > 0u))
  {
    (void)Boot_Uds_TryTransmit();
  }

  /* Never dispatch from CanTp RxIndication: PduR_Transmit inside CanTp_MainFunction
   * / ISR is often E_NOT_OK, and TxConfirmation of the previous N-SDU would then
   * wipe the queued next response. */
  if ((Cdd_RxDeferred != 0u) && (Cdd_TpTxBusy == 0u) && (Cdd_TpTxRetry == 0u))
  {
    Cdd_RxDeferred = 0u;
    Boot_Dcm_ProcessRequest();
  }

  /* 0x11: response must leave the bus before the MCU resets. */
  if (Boot_Uds_ResetPending != 0u)
  {
    if ((Cdd_TpTxBusy != 0u) || (Cdd_TpTxRetry != 0u))
    {
      /* 0x51 still queued or waiting for TpTxConfirmation */
    }
    else if (Boot_Uds_ResetHoldMs > 0u)
    {
      Boot_Uds_ResetHoldMs--;
    }
    else
    {
      BrsHwSoftwareResetECU();
    }
  }
}

void Boot_Uds_SendNeg(uint8 sid, uint8 nrc)
{
  Cdd_TpTxBuf[0] = BOOT_UDS_NEG;
  Cdd_TpTxBuf[1] = sid;
  Cdd_TpTxBuf[2] = nrc;
  Boot_Uds_Transmit(3u);
}

void Boot_Uds_ResetSecurityAccess(void)
{
  /* Drop seed/key handshake only. Per-session unlock is owned by Boot_Uds_Sm. */
  Boot_Uds_SeedRequested = 0u;
  Boot_Uds_PendingSecLevel = 0u;
  Boot_Uds_Seed = 0u;
}

static uint32 Boot_Uds_MakeSeed(void)
{
  static uint32 s = 0x13579BDFu;
  uint32 mix;

  mix = Boot_App_MixEntropy();
  s = (s * 1664525u) + 1013904223u;
  s ^= mix;
  if (s == 0u)
  {
    s = 0xA5A5A5A5u;
  }
  return s;
}

#if (BOOT_UDS_SECURITY_DEV_STUB == 1)
static uint32 Boot_Uds_CalcKey(uint32 seed)
{
  return (uint32)(~seed);
}
#else
/* Production: replace with OEM seed-key algorithm. Default refuses (~seed). */
static uint32 Boot_Uds_CalcKey(uint32 seed)
{
  (void)seed;
  return 0u;
}
#endif

static void Boot_Uds_CopyToTx(uint16 did, const uint8* data, uint8 dataLen)
{
  uint8 i;

  Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_RDBI);
  Cdd_TpTxBuf[1] = (uint8)((did >> 8) & 0xFFu);
  Cdd_TpTxBuf[2] = (uint8)(did & 0xFFu);
  for (i = 0u; i < dataLen; i++)
  {
    Cdd_TpTxBuf[3u + i] = data[i];
  }
  Boot_Uds_Transmit((PduLengthType)(3u + dataLen));
}

void Boot_Uds_DidReset(void)
{
  uint8 i;

  Boot_Did_F180[0] = 0x01u;
  Boot_Did_F180[1] = 0x42u;
  Boot_Did_F180[2] = 0x4Fu;
  Boot_Did_F180[3] = 0x4Fu;
  Boot_Did_F180[4] = 0x54u;
  for (i = 0u; i < BOOT_DID_F187_LEN; i++) { Boot_Did_F187[i] = 0u; }
  for (i = 0u; i < BOOT_DID_F189_LEN; i++) { Boot_Did_F189[i] = 0u; }
  for (i = 0u; i < BOOT_DID_F18C_LEN; i++) { Boot_Did_F18C[i] = 0u; }
  for (i = 0u; i < BOOT_DID_F190_LEN; i++) { Boot_Did_F190[i] = 0u; }
  for (i = 0u; i < BOOT_DID_F193_LEN; i++) { Boot_Did_F193[i] = 0u; }
  for (i = 0u; i < BOOT_DID_F198_LEN; i++) { Boot_Did_F198[i] = 0u; }
}

static boolean Boot_Uds_DidSessionOk(uint8 mask)
{
  uint8 bit = BOOT_DCM_SESSION_BIT(Boot_Dcm_GetSession());
  return ((mask & bit) != 0u) ? TRUE : FALSE;
}

static uint8 Boot_Uds_DidReadMask(uint16 did)
{
  switch (did)
  {
    case BOOT_DID_BOOT_SOFTWARE:
      return BOOT_DCM_SESSION_MASK_ALL;
    case BOOT_DID_SPARE_PART_NUMBER:
    case BOOT_DID_ECU_PART_NUMBER:
    case BOOT_DID_SERIAL_NUMBER:
    case BOOT_DID_VIN:
    case BOOT_DID_HW_VERSION:
      return BOOT_DCM_SESSION_MASK_EXT_ONLY;
    default:
      return 0u;
  }
}

static uint8 Boot_Uds_DidWriteMask(uint16 did)
{
  switch (did)
  {
    case BOOT_DID_BOOT_SOFTWARE:
    case BOOT_DID_FINGERPRINT:
      return BOOT_DCM_SESSION_MASK_PROG_EXT;
    case BOOT_DID_SPARE_PART_NUMBER:
    case BOOT_DID_ECU_PART_NUMBER:
    case BOOT_DID_SERIAL_NUMBER:
    case BOOT_DID_VIN:
    case BOOT_DID_HW_VERSION:
      return BOOT_DCM_SESSION_MASK_EXT_ONLY;
    default:
      return 0u;
  }
}

void Boot_Uds_HandleDsc(void)
{
  uint8 sub;
  uint8 subNs;

  if (Cdd_TpRxLen < 2u)
  {
    Boot_Uds_SendNeg(BOOT_SID_DSC, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  sub = Cdd_TpRxBuf[1];
  subNs = (uint8)(sub & (uint8)(~BOOT_UDS_SUPPRESS_POS_RSP));

  if ((subNs != BOOT_SF_DSC_DEFAULT) &&
      (subNs != BOOT_SF_DSC_PROGRAMMING) &&
      (subNs != BOOT_SF_DSC_EXTENDED))
  {
    Boot_Uds_SendNeg(BOOT_SID_DSC, BOOT_UDS_NRC_SFNS);
    return;
  }

  if (Boot_Dcm_GetSession() != subNs)
  {
    if ((subNs == BOOT_SF_DSC_EXTENDED) &&
        (Boot_Sm_GetState() == BOOT_SM_DOWNLOADING))
    {
      Boot_Uds_SendNeg(BOOT_SID_DSC, BOOT_UDS_NRC_CNC);
      return;
    }
    Boot_Dcm_ChangeSession(subNs);
  }

  if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) != 0u)
  {
    return;
  }

  Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_DSC);
  Cdd_TpTxBuf[1] = subNs;
  Cdd_TpTxBuf[2] = (uint8)((BOOT_UDS_P2_SERVER_10MS >> 8) & 0xFFu);
  Cdd_TpTxBuf[3] = (uint8)(BOOT_UDS_P2_SERVER_10MS & 0xFFu);
  Cdd_TpTxBuf[4] = (uint8)((BOOT_UDS_P2EX_SERVER_10MS >> 8) & 0xFFu);
  Cdd_TpTxBuf[5] = (uint8)(BOOT_UDS_P2EX_SERVER_10MS & 0xFFu);
  Boot_Uds_Transmit(6u);
}

void Boot_Uds_HandleEcuReset(void)
{
  uint8 sub;
  uint8 subNs;

  if (Cdd_TpRxLen < 2u)
  {
    Boot_Uds_SendNeg(BOOT_SID_ER, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  sub = Cdd_TpRxBuf[1];
  subNs = (uint8)(sub & (uint8)(~BOOT_UDS_SUPPRESS_POS_RSP));

  /* Boot Dcm: 0x01 hardReset, 0x03 softReset */
  if ((subNs != BOOT_SF_ER_HARD) && (subNs != BOOT_SF_ER_SOFT))
  {
    Boot_Uds_SendNeg(BOOT_SID_ER, BOOT_UDS_NRC_SFNS);
    return;
  }

  if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) == 0u)
  {
    Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_ER);
    Cdd_TpTxBuf[1] = subNs;
    Boot_Uds_Transmit(2u);
    Boot_Uds_ResetHoldMs = BOOT_UDS_RESET_HOLD_MS;
  }
  else
  {
    Boot_Uds_ResetHoldMs = 0u;
  }

  /* Reset in MainFunction after 0x51 TxConfirmation (or immediately if SPRMIB). */
  Boot_Uds_ResetPending = 1u;
}

void Boot_Uds_HandleTesterPresent(void)
{
  uint8 sub;
  uint8 subNs;

  if (Cdd_TpRxLen < 2u)
  {
    Boot_Uds_SendNeg(BOOT_SID_TP, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  sub = Cdd_TpRxBuf[1];
  subNs = (uint8)(sub & (uint8)(~BOOT_UDS_SUPPRESS_POS_RSP));

  if (subNs != BOOT_SF_TP_ZERO)
  {
    Boot_Uds_SendNeg(BOOT_SID_TP, BOOT_UDS_NRC_SFNS);
    return;
  }

  if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) != 0u)
  {
    return;
  }

  Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_TP);
  Cdd_TpTxBuf[1] = BOOT_SF_TP_ZERO;
  Boot_Uds_Transmit(2u);
}

void Boot_Uds_HandleRdbi(void)
{
  uint16 did;

  if (Cdd_TpRxLen != 3u)
  {
    Boot_Uds_SendNeg(BOOT_SID_RDBI, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  did = (uint16)(((uint16)Cdd_TpRxBuf[1] << 8) | (uint16)Cdd_TpRxBuf[2]);

  if (Boot_Uds_DidSessionOk(Boot_Uds_DidReadMask(did)) != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_RDBI, BOOT_UDS_NRC_ROOR);
    return;
  }

  switch (did)
  {
    case BOOT_DID_BOOT_SOFTWARE:
      Boot_Uds_CopyToTx(did, Boot_Did_F180, BOOT_DID_F180_LEN);
      break;
    case BOOT_DID_SPARE_PART_NUMBER:
      Boot_Uds_CopyToTx(did, Boot_Did_F187, BOOT_DID_F187_LEN);
      break;
    case BOOT_DID_ECU_PART_NUMBER:
      Boot_Uds_CopyToTx(did, Boot_Did_F189, BOOT_DID_F189_LEN);
      break;
    case BOOT_DID_SERIAL_NUMBER:
      Boot_Uds_CopyToTx(did, Boot_Did_F18C, BOOT_DID_F18C_LEN);
      break;
    case BOOT_DID_VIN:
      Boot_Uds_CopyToTx(did, Boot_Did_F190, BOOT_DID_F190_LEN);
      break;
    case BOOT_DID_HW_VERSION:
      Boot_Uds_CopyToTx(did, Boot_Did_F193, BOOT_DID_F193_LEN);
      break;
    default:
      Boot_Uds_SendNeg(BOOT_SID_RDBI, BOOT_UDS_NRC_ROOR);
      break;
  }
}

void Boot_Uds_HandleWdbi(void)
{
  uint16 did;
  uint8 lenNeed;
  uint8* dst;
  uint8 i;

  if (Cdd_TpRxLen < 4u)
  {
    Boot_Uds_SendNeg(BOOT_SID_WDBI, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  did = (uint16)(((uint16)Cdd_TpRxBuf[1] << 8) | (uint16)Cdd_TpRxBuf[2]);

  if (Boot_Uds_DidSessionOk(Boot_Uds_DidWriteMask(did)) != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_WDBI, BOOT_UDS_NRC_ROOR);
    return;
  }

  switch (did)
  {
    case BOOT_DID_BOOT_SOFTWARE:
      lenNeed = BOOT_DID_F180_LEN;
      dst = Boot_Did_F180;
      break;
    case BOOT_DID_SPARE_PART_NUMBER:
      lenNeed = BOOT_DID_F187_LEN;
      dst = Boot_Did_F187;
      break;
    case BOOT_DID_ECU_PART_NUMBER:
      lenNeed = BOOT_DID_F189_LEN;
      dst = Boot_Did_F189;
      break;
    case BOOT_DID_SERIAL_NUMBER:
      lenNeed = BOOT_DID_F18C_LEN;
      dst = Boot_Did_F18C;
      break;
    case BOOT_DID_VIN:
      lenNeed = BOOT_DID_F190_LEN;
      dst = Boot_Did_F190;
      break;
    case BOOT_DID_HW_VERSION:
      lenNeed = BOOT_DID_F193_LEN;
      dst = Boot_Did_F193;
      break;
    case BOOT_DID_FINGERPRINT:
      lenNeed = BOOT_DID_F198_LEN;
      dst = Boot_Did_F198;
      break;
    default:
      Boot_Uds_SendNeg(BOOT_SID_WDBI, BOOT_UDS_NRC_ROOR);
      return;
  }

  if (Cdd_TpRxLen != (PduLengthType)(3u + lenNeed))
  {
    Boot_Uds_SendNeg(BOOT_SID_WDBI, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  for (i = 0u; i < lenNeed; i++)
  {
    dst[i] = Cdd_TpRxBuf[3u + i];
  }

  Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_WDBI);
  Cdd_TpTxBuf[1] = Cdd_TpRxBuf[1];
  Cdd_TpTxBuf[2] = Cdd_TpRxBuf[2];
  Boot_Uds_Transmit(3u);
}

void Boot_Uds_HandleSecurityAccess(void)
{
  uint8 sub;
  uint8 subNs;
  uint32 key;
  uint8 seedLen;
  uint8 keyLen;
  uint8 level;

  if (Cdd_TpRxLen < 2u)
  {
    Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  if (Boot_Uds_SaDelayMs > 0u)
  {
    Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_RTDNE);
    return;
  }

  if (Boot_Sm_AllowSecurityAccess() != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_CNC);
    return;
  }

  sub = Cdd_TpRxBuf[1];
  subNs = (uint8)(sub & (uint8)(~BOOT_UDS_SUPPRESS_POS_RSP));

  if ((subNs == BOOT_SF_SA_L1_SEED) || (subNs == BOOT_SF_SA_L3_SEED))
  {
    level = (subNs == BOOT_SF_SA_L1_SEED) ? 1u : 3u;
    seedLen = (level == 1u) ? BOOT_SA_SEED_LEN_L1 : BOOT_SA_SEED_LEN_L3;

    if (Cdd_TpRxLen != 2u)
    {
      Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_IMLOIF);
      return;
    }

    if (Boot_Sm_IsSecLevelOpen(level) == TRUE)
    {
      Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_SA);
      Cdd_TpTxBuf[1] = subNs;
      Cdd_TpTxBuf[2] = 0u;
      Cdd_TpTxBuf[3] = 0u;
      Cdd_TpTxBuf[4] = 0u;
      Cdd_TpTxBuf[5] = 0u;
      Boot_Uds_Transmit((PduLengthType)(2u + seedLen));
      return;
    }

    Boot_Uds_Seed = Boot_Uds_MakeSeed();
    Boot_Uds_SeedRequested = 1u;
    Boot_Uds_PendingSecLevel = level;

    if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) != 0u)
    {
      return;
    }

    Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_SA);
    Cdd_TpTxBuf[1] = subNs;
    Cdd_TpTxBuf[2] = (uint8)((Boot_Uds_Seed >> 24) & 0xFFu);
    Cdd_TpTxBuf[3] = (uint8)((Boot_Uds_Seed >> 16) & 0xFFu);
    Cdd_TpTxBuf[4] = (uint8)((Boot_Uds_Seed >> 8) & 0xFFu);
    Cdd_TpTxBuf[5] = (uint8)(Boot_Uds_Seed & 0xFFu);
    Boot_Uds_Transmit((PduLengthType)(2u + seedLen));
    return;
  }

  if ((subNs == BOOT_SF_SA_L1_KEY) || (subNs == BOOT_SF_SA_L3_KEY))
  {
    level = (subNs == BOOT_SF_SA_L1_KEY) ? 1u : 3u;
    keyLen = (level == 1u) ? BOOT_SA_KEY_LEN_L1 : BOOT_SA_KEY_LEN_L3;

    if (Cdd_TpRxLen != (PduLengthType)(2u + keyLen))
    {
      Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_IMLOIF);
      return;
    }
    if ((Boot_Uds_SeedRequested == 0u) || (Boot_Uds_PendingSecLevel != level))
    {
      Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_RSE);
      return;
    }

    key = (((uint32)Cdd_TpRxBuf[2] << 24) |
           ((uint32)Cdd_TpRxBuf[3] << 16) |
           ((uint32)Cdd_TpRxBuf[4] << 8) |
           (uint32)Cdd_TpRxBuf[5]);

    if (key != Boot_Uds_CalcKey(Boot_Uds_Seed))
    {
      Boot_Uds_SeedRequested = 0u;
      Boot_Uds_PendingSecLevel = 0u;
      Boot_Sm_OnSecurityLocked();
      if (Boot_Uds_SaAttempts < 0xFFu)
      {
        Boot_Uds_SaAttempts++;
      }
      if (Boot_Uds_SaAttempts >= BOOT_SA_MAX_ATTEMPTS)
      {
        Boot_Uds_SaDelayMs = BOOT_SA_DELAY_MS;
        Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_EAT);
        return;
      }
      Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_IK);
      return;
    }

    Boot_Uds_SeedRequested = 0u;
    Boot_Uds_SaAttempts = 0u;
    Boot_Sm_OnSecurityUnlockedLevel(level);
    Boot_Uds_PendingSecLevel = 0u;

    if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) != 0u)
    {
      return;
    }

    Cdd_TpTxBuf[0] = BOOT_POS(BOOT_SID_SA);
    Cdd_TpTxBuf[1] = subNs;
    Boot_Uds_Transmit(2u);
    return;
  }

  Boot_Uds_SendNeg(BOOT_SID_SA, BOOT_UDS_NRC_SFNS);
}


FUNC(BufReq_ReturnType, CDD_CODE) Cdd_StartOfReception(
  PduIdType id,
  P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info,
  PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) bufferSizePtr)
{
  (void)id;
  (void)info;

  if ((bufferSizePtr == NULL_PTR) || (TpSduLength > CDD_TP_RX_BUF_SIZE))
  {
    return BUFREQ_E_NOT_OK;
  }

  Cdd_TpRxIdx = 0u;
  Cdd_TpRxLen = TpSduLength;
  *bufferSizePtr = CDD_TP_RX_BUF_SIZE;
  return BUFREQ_OK;
}

FUNC(BufReq_ReturnType, CDD_CODE) Cdd_CopyRxData(
  PduIdType id,
  P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info,
  P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) bufferSizePtr)
{
  PduLengthType i;

  (void)id;

  if ((info == NULL_PTR) || (bufferSizePtr == NULL_PTR) || (info->SduDataPtr == NULL_PTR))
  {
    return BUFREQ_E_NOT_OK;
  }

  if ((Cdd_TpRxIdx + info->SduLength) > CDD_TP_RX_BUF_SIZE)
  {
    return BUFREQ_E_NOT_OK;
  }

  for (i = 0u; i < info->SduLength; i++)
  {
    Cdd_TpRxBuf[Cdd_TpRxIdx + i] = info->SduDataPtr[i];
  }
  Cdd_TpRxIdx += info->SduLength;
  *bufferSizePtr = (PduLengthType)(CDD_TP_RX_BUF_SIZE - Cdd_TpRxIdx);
  return BUFREQ_OK;
}

FUNC(void, CDD_CODE) Cdd_TpRxIndication(PduIdType id, Std_ReturnType result)
{
  (void)id;

  if ((result == E_OK) && (Cdd_TpRxIdx >= Cdd_TpRxLen) && (Cdd_TpRxLen > 0u))
  {
    Boot_CanRxNotify((uint8)id, Cdd_TpRxBuf[0]);
    /* Always wait for Boot_Uds_MainFunction so Transmit is not nested in CanTp. */
    Cdd_RxDeferred = 1u;
  }
}

FUNC(BufReq_ReturnType, CDD_CODE) Cdd_CopyTxData(
  PduIdType id,
  P2VAR(PduInfoType, AUTOMATIC, CDD_APPL_DATA) info,
  P2VAR(RetryInfoType, AUTOMATIC, CDD_APPL_DATA) retry,
  P2VAR(PduLengthType, AUTOMATIC, CDD_APPL_DATA) availableDataPtr)
{
  PduLengthType i;
  PduLengthType remain;

  (void)id;
  (void)retry;

  if ((info == NULL_PTR) || (availableDataPtr == NULL_PTR) || (info->SduDataPtr == NULL_PTR))
  {
    return BUFREQ_E_NOT_OK;
  }

  if (Cdd_TpTxIdx >= Cdd_TpTxLen)
  {
    *availableDataPtr = 0u;
    return BUFREQ_OK;
  }

  remain = (PduLengthType)(Cdd_TpTxLen - Cdd_TpTxIdx);
  if (info->SduLength > remain)
  {
    return BUFREQ_E_NOT_OK;
  }

  for (i = 0u; i < info->SduLength; i++)
  {
    info->SduDataPtr[i] = Cdd_TpTxBuf[Cdd_TpTxIdx + i];
  }
  Cdd_TpTxIdx += info->SduLength;
  *availableDataPtr = (PduLengthType)(Cdd_TpTxLen - Cdd_TpTxIdx);
  return BUFREQ_OK;
}

FUNC(void, CDD_CODE) Cdd_TpTxConfirmation(PduIdType id, Std_ReturnType result)
{
  (void)id;

  Cdd_TpTxBusy = 0u;
  Cdd_TpTxIdx = 0u;
  if (result != E_OK)
  {
    /* Same payload still in Cdd_TpTxBuf; MainFunction will Transmit again. */
    Cdd_TpTxRetry = 1u;
  }
  else if (Cdd_TpTxRetry == 0u)
  {
    Cdd_TpTxLen = 0u;
  }
  /* retry==1: a newer response was queued while this confirmation was pending;
   * keep Cdd_TpTxBuf / Cdd_TpTxLen for the next TryTransmit. */
}
