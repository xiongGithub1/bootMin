/**********************************************************************************************************************
 * Boot_FlashProg.c — RequestDownload / TransferData / TransferExit / RoutineControl
 * Sequence gated by Boot_Uds_Sm; flash ops via FlsLoader (APP only).
 * RID/SID from Boot_Uds_Sid.h (aligned with autosarTc364_Boot Dcm_Lcfg).
 *********************************************************************************************************************/
#include "Boot_FlashProg.h"
#include "FlsLoader.h"
#include "FlsLdr_ExclArea.h"
#include "Boot_PFlashSmoke.h"
#include "Boot_Uds.h"
#include "Boot_Uds_Sm.h"
#include "Boot_App.h"
#include "Boot_Swap.h"
#include "Std_Types.h"

/* Logical APP/Boot window (UDS) → FlsLoader HW address (inactive bank when SWAP on). */
static uint32 Boot_FlashProg_ToProgHw(uint32 logicalCachedOrHw)
{
#if (BOOT_SWAP_PROGRAM_INACTIVE == 1)
  uint32 cfg = Boot_Swap_GetAddrCfg();

  if ((cfg == BOOT_SWAP_ADDRCFG_A) || (cfg == BOOT_SWAP_ADDRCFG_B))
  {
    return Boot_Swap_LogicalToInactiveHw(logicalCachedOrHw);
  }
#endif
  return Boot_App_ToHw(logicalCachedOrHw);
}

#define BOOT_POS_RD                  BOOT_POS(BOOT_SID_RD)
#define BOOT_POS_TD                  BOOT_POS(BOOT_SID_TD)
#define BOOT_POS_RTE                 BOOT_POS(BOOT_SID_RTE)
#define BOOT_POS_RC                  BOOT_POS(BOOT_SID_RC)

static uint32 Boot_DlAddr;
static uint32 Boot_DlHwAddr;
static uint32 Boot_DlSize;
static uint32 Boot_DlReceived;
static uint8  Boot_DlNextBsc;
static uint32 Boot_DlCrcOpen;
static uint32 Boot_LastAddr;
static uint32 Boot_LastSize;
static uint32 Boot_LastCrc;

static uint32 Boot_BeToU32(const uint8* p)
{
  return (((uint32)p[0] << 24) | ((uint32)p[1] << 16) | ((uint32)p[2] << 8) | (uint32)p[3]);
}

static boolean Boot_IsAppRange(uint32 start, uint32 length)
{
  return Boot_App_IsRangeInApp(start, length);
}

static uint8 Boot_NrcForProgGate(void)
{
  Boot_SmStateType st = Boot_Sm_GetState();

  if ((st == BOOT_SM_DEFAULT) || (st == BOOT_SM_EXTENDED))
  {
    return BOOT_UDS_NRC_CNC;
  }
  if (st == BOOT_SM_PROG)
  {
    return BOOT_UDS_NRC_SAD;
  }
  return BOOT_UDS_NRC_CNC;
}

void Boot_FlashProg_Init(void)
{
  Boot_DlAddr = 0u;
  Boot_DlHwAddr = 0u;
  Boot_DlSize = 0u;
  Boot_DlReceived = 0u;
  Boot_DlNextBsc = 1u;
  Boot_DlCrcOpen = 0u;
}

void Boot_FlashProg_OnSessionChange(uint8 session)
{
  (void)session;
  Boot_FlashProg_Init();
}

void Boot_FlashProg_HandleRequestDownload(void)
{
  const uint8* rx = Boot_Uds_GetRxBuf();
  uint8* tx = Boot_Uds_GetTxBuf();
  PduLengthType len = Boot_Uds_GetRxLen();
  uint8 alfid;
  uint8 addrLen;
  uint8 sizeLen;
  uint32 addr;
  uint32 size;
  uint16 maxBlk = BOOT_UDS_MAX_BLOCK_LENGTH;

  if (Boot_Sm_AllowDownload() != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_RD, Boot_NrcForProgGate());
    return;
  }

  if (len < 3u)
  {
    Boot_Uds_SendNeg(BOOT_SID_RD, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  if (rx[1] != BOOT_RD_DATA_FORMAT_ID)
  {
    Boot_Uds_SendNeg(BOOT_SID_RD, BOOT_UDS_NRC_ROOR);
    return;
  }

  alfid = rx[2];
  addrLen = (uint8)(alfid & 0x0Fu);
  sizeLen = (uint8)((alfid >> 4) & 0x0Fu);

  if ((addrLen != 4u) || (sizeLen != 4u) || (len != (PduLengthType)(3u + addrLen + sizeLen)))
  {
    Boot_Uds_SendNeg(BOOT_SID_RD, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  addr = Boot_BeToU32(&rx[3]);
  size = Boot_BeToU32(&rx[7]);

  if (Boot_IsAppRange(addr, size) != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_RD, BOOT_UDS_NRC_ROOR);
    return;
  }

  if (((addr % BOOT_FLASH_WRITE_ALIGN) != 0u) || ((size % BOOT_FLASH_WRITE_ALIGN) != 0u))
  {
    Boot_Uds_SendNeg(BOOT_SID_RD, BOOT_UDS_NRC_ROOR);
    return;
  }

  if (Boot_Sm_OnDownloadStart() != E_OK)
  {
    Boot_Uds_SendNeg(BOOT_SID_RD, BOOT_UDS_NRC_CNC);
    return;
  }

  Boot_DlAddr = addr;
  Boot_DlHwAddr = Boot_FlashProg_ToProgHw(addr);
  Boot_DlSize = size;
  Boot_DlReceived = 0u;
  Boot_DlNextBsc = 1u;
  Boot_DlCrcOpen = 0u;
  Boot_LastSize = 0u;

  tx[0] = BOOT_POS_RD;
  tx[1] = BOOT_RD_MAXBLK_LEN_FORMAT;
  tx[2] = (uint8)((maxBlk >> 8) & 0xFFu);
  tx[3] = (uint8)(maxBlk & 0xFFu);
  Boot_Uds_Transmit(4u);
}

void Boot_FlashProg_HandleTransferData(void)
{
  const uint8* rx = Boot_Uds_GetRxBuf();
  uint8* tx = Boot_Uds_GetTxBuf();
  PduLengthType len = Boot_Uds_GetRxLen();
  uint8 bsc;
  PduLengthType dataLen;
  FlsLoader_ReturnType fr;

  if (Boot_Sm_AllowTransferData() != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_TD, BOOT_UDS_NRC_RSE);
    return;
  }

  if (len < 2u)
  {
    Boot_Uds_SendNeg(BOOT_SID_TD, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  bsc = rx[1];
  if (bsc != Boot_DlNextBsc)
  {
    Boot_Uds_SendNeg(BOOT_SID_TD, BOOT_UDS_NRC_WBSC);
    return;
  }

  dataLen = (PduLengthType)(len - 2u);
  if (dataLen == 0u)
  {
    Boot_Uds_SendNeg(BOOT_SID_TD, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  if ((Boot_DlReceived + (uint32)dataLen) > Boot_DlSize)
  {
    Boot_Uds_SendNeg(BOOT_SID_TD, BOOT_UDS_NRC_ROOR);
    return;
  }

  if (((uint32)dataLen % BOOT_FLASH_WRITE_ALIGN) != 0u)
  {
    Boot_Uds_SendNeg(BOOT_SID_TD, BOOT_UDS_NRC_ROOR);
    return;
  }

#if (BOOT_PFLASH_SMOKE_TEST == 1)
  fr = (Boot_PFlashSmoke_Write(
            (uint32)(Boot_DlHwAddr + Boot_DlReceived),
            (uint32)dataLen,
            &rx[2]) == E_OK)
           ? FLSLOADER_E_OK
           : FLSLOADER_E_NOT_OK;
#else
  fr = FlsLoader_Write(
      (FlsLoader_AddressType)(Boot_DlHwAddr + Boot_DlReceived),
      (FlsLoader_LengthType)dataLen,
      &rx[2]);
  FlsLdr_ExclArea_PfBusy_Release();
#endif

  if (fr != FLSLOADER_E_OK)
  {
    Boot_Sm_OnDownloadAbort();
    Boot_FlashProg_Init();
    Boot_Uds_SendNeg(BOOT_SID_TD, BOOT_UDS_NRC_GPF);
    return;
  }

  if (Boot_DlReceived == 0u)
  {
    Boot_DlCrcOpen = Boot_App_Crc32(&rx[2], (uint32)dataLen);
  }
  else
  {
    Boot_DlCrcOpen = Boot_App_Crc32Acc(Boot_DlCrcOpen, &rx[2], (uint32)dataLen);
  }
  Boot_DlReceived += (uint32)dataLen;
  Boot_DlNextBsc++;

  tx[0] = BOOT_POS_TD;
  tx[1] = bsc;
  Boot_Uds_Transmit(2u);
}

void Boot_FlashProg_HandleRequestTransferExit(void)
{
  uint8* tx = Boot_Uds_GetTxBuf();
  PduLengthType len = Boot_Uds_GetRxLen();

  if (Boot_Sm_AllowTransferExit() != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_RTE, BOOT_UDS_NRC_RSE);
    return;
  }

  if (len != 1u)
  {
    Boot_Uds_SendNeg(BOOT_SID_RTE, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  if (Boot_DlReceived != Boot_DlSize)
  {
    Boot_Sm_OnDownloadAbort();
    Boot_FlashProg_Init();
    Boot_Uds_SendNeg(BOOT_SID_RTE, BOOT_UDS_NRC_CNC);
    return;
  }

  if (Boot_Sm_OnTransferExitOk() != E_OK)
  {
    Boot_Uds_SendNeg(BOOT_SID_RTE, BOOT_UDS_NRC_CNC);
    return;
  }

  Boot_LastAddr = Boot_App_ToCached(Boot_DlAddr);
  Boot_LastSize = Boot_DlSize;
  Boot_LastCrc = Boot_DlCrcOpen;
  Boot_FlashProg_Init();

  tx[0] = BOOT_POS_RTE;
  Boot_Uds_Transmit(1u);
}

static void Boot_FlashProg_EraseApp(uint32 start, uint32 length)
{
  uint32 hwStart;
  uint32 sectors;
  FlsLoader_ReturnType fr;
  uint8* tx = Boot_Uds_GetTxBuf();

  if (Boot_IsAppRange(start, length) != TRUE)
  {
    Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_ROOR);
    return;
  }

  if (((start % BOOT_FLASH_SECTOR_SIZE) != 0u) || ((length % BOOT_FLASH_SECTOR_SIZE) != 0u))
  {
    Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_ROOR);
    return;
  }

  hwStart = Boot_FlashProg_ToProgHw(start);
  sectors = length / BOOT_FLASH_SECTOR_SIZE;

#if (BOOT_PFLASH_SMOKE_TEST == 1)
  /* PSPR multi-sector erase (same-bank safe). */
  fr = (Boot_PFlashSmoke_EraseSectors(hwStart, sectors) == E_OK)
           ? FLSLOADER_E_OK
           : FLSLOADER_E_NOT_OK;
#else
  /* Length = sector count; full APP ≈ 0x1E0000/0x4000 = 120. */
  fr = FlsLoader_Erase((FlsLoader_AddressType)hwStart, (FlsLoader_LengthType)sectors);
  FlsLdr_ExclArea_PfBusy_Release();
#endif
  if (fr != FLSLOADER_E_OK)
  {
    Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_GPF);
    return;
  }

  Boot_FlashProg_Init();
  Boot_LastAddr = 0u;
  Boot_LastSize = 0u;
  Boot_LastCrc = 0u;
  if (Boot_Sm_OnEraseOk() != E_OK)
  {
    Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_CNC);
    return;
  }

  tx[0] = BOOT_POS_RC;
  tx[1] = BOOT_SF_RC_START;
  tx[2] = (uint8)((BOOT_RID_ERASE_MEMORY >> 8) & 0xFFu);
  tx[3] = (uint8)(BOOT_RID_ERASE_MEMORY & 0xFFu);
  Boot_Uds_Transmit(4u);
}

void Boot_FlashProg_HandleRoutineControl(void)
{
  const uint8* rx = Boot_Uds_GetRxBuf();
  uint8* tx = Boot_Uds_GetTxBuf();
  PduLengthType len = Boot_Uds_GetRxLen();
  uint8 sub;
  uint8 subNs;
  uint16 rid;
  uint32 addr;
  uint32 size;
  uint32 hostCrc;

  if (len < 4u)
  {
    Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_IMLOIF);
    return;
  }

  sub = rx[1];
  subNs = (uint8)(sub & (uint8)(~BOOT_UDS_SUPPRESS_POS_RSP));
  rid = (uint16)(((uint16)rx[2] << 8) | (uint16)rx[3]);

  if (subNs == BOOT_SF_RC_START)
  {
    if (rid == BOOT_RID_ERASE_MEMORY)
    {
      if (Boot_Sm_AllowErase() != TRUE)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, Boot_NrcForProgGate());
        return;
      }

      if (len == 4u)
      {
        addr = BOOT_FLASH_APP_START;
        size = (BOOT_FLASH_APP_END - BOOT_FLASH_APP_START) + 1u;
        size -= (size % BOOT_FLASH_SECTOR_SIZE);
        Boot_FlashProg_EraseApp(addr, size);
        return;
      }
      if ((len == 13u) && (rx[4] == BOOT_RD_ALFID_44))
      {
        addr = Boot_BeToU32(&rx[5]);
        size = Boot_BeToU32(&rx[9]);
        Boot_FlashProg_EraseApp(addr, size);
        return;
      }
      Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_IMLOIF);
      return;
    }

    if (rid == BOOT_RID_CHECK_PROG_DEP)
    {
      /* Boot Dcm: Start + 1-byte InSignal; accept len 4 (no data) or 5 */
      if ((len != 4u) && (len != 5u))
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_IMLOIF);
        return;
      }
      if (Boot_Sm_AllowCheckDep() != TRUE)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_CNC);
        return;
      }
      if (Boot_Sm_OnCheckDepOk() != E_OK)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_CNC);
        return;
      }
      if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) != 0u)
      {
        return;
      }
      tx[0] = BOOT_POS_RC;
      tx[1] = BOOT_SF_RC_START;
      tx[2] = (uint8)((rid >> 8) & 0xFFu);
      tx[3] = (uint8)(rid & 0xFFu);
      tx[4] = 0x00u; /* routineStatusRecord: OK */
      Boot_Uds_Transmit(5u);
      return;
    }

    if (rid == BOOT_RID_CHECK_MEMORY)
    {
      /* Gate first so order tests (4-byte FF02 before 37) still get CNC. */
      if (Boot_Sm_AllowCheckDep() != TRUE)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_CNC);
        return;
      }
      /* 31 01 FF 02 + CRC32 BE (same bytes streamed in 0x36). */
      if (len != 8u)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_IMLOIF);
        return;
      }
      if (Boot_LastSize == 0u)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_CNC);
        return;
      }
      hostCrc = Boot_BeToU32(&rx[4]);
      if (hostCrc != Boot_LastCrc)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_GPF);
        return;
      }
      /* Stream CRC OK. Boot→APP jump still uses APP header crc32 in Flash. */
      if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) != 0u)
      {
        return;
      }
      tx[0] = BOOT_POS_RC;
      tx[1] = BOOT_SF_RC_START;
      tx[2] = (uint8)((rid >> 8) & 0xFFu);
      tx[3] = (uint8)(rid & 0xFFu);
      tx[4] = 0x00u; /* routineStatusRecord: OK */
      Boot_Uds_Transmit(5u);
      return;
    }

    if (rid == BOOT_RID_ACTIVATE_SWAP)
    {
      uint8 marker = BOOT_SWAP_MARKER_TOGGLE;
      Std_ReturnType sr;

      /* 31 01 FF 03 [marker] — marker optional: 0/omit=toggle, 0x55=A, 0xAA=B */
      if ((len != 4u) && (len != 5u))
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_IMLOIF);
        return;
      }
      if (Boot_Sm_AllowActivateSwap() != TRUE)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_CNC);
        return;
      }
      if (len == 5u)
      {
        marker = rx[4];
      }
      sr = Boot_Swap_Activate(marker);
      if (sr != E_OK)
      {
        Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_GPF);
        return;
      }
      if ((sub & BOOT_UDS_SUPPRESS_POS_RSP) == 0u)
      {
        tx[0] = BOOT_POS_RC;
        tx[1] = BOOT_SF_RC_START;
        tx[2] = (uint8)((rid >> 8) & 0xFFu);
        tx[3] = (uint8)(rid & 0xFFu);
        tx[4] = 0x00u;
        Boot_Uds_Transmit(5u);
      }
      /* System Reset so SSW installs new UCB_SWAP mapping. */
      Boot_Uds_RequestSoftwareReset();
      return;
    }

    Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_ROOR);
    return;
  }

  if ((subNs == BOOT_SF_RC_STOP) || (subNs == BOOT_SF_RC_REQ_RESULTS))
  {
    Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_SFNS);
    return;
  }

  Boot_Uds_SendNeg(BOOT_SID_RC, BOOT_UDS_NRC_SFNS);
}
