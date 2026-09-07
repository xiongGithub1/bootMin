/**********************************************************************************************************************
 * Boot_App.c — APP header, MCAL Crc_CalculateCRC32, handshake, jump
 * Add this file and Crc.c to the Tasking project if they are not compiled.
 *********************************************************************************************************************/
#include "Boot_App.h"
#include "Boot_Swap.h"
#include "Boot_OsFlashTimer.h"
#include "Crc.h"
#include "BrsHw.h"
#include "BrsHwStartup_TC2xx_TC3xx.h"
#include "FlsLoader.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "McalLib.h"

/* Linked in BrsHw.c (CPU EndInit). Prefer these over BrsHwUnlockInitInline (ltc E106). */
void Appl_UnlockEndinit(void);
void Appl_LockEndinit(void);

/* SCU CHIPID (TC3xx @ 0xF0036140), STM0 TIM0 — seed mix only, not crypto. */
#define BOOT_SCU_CHIPID                  (*(volatile uint32 *)0xF0036140u)
#define BOOT_STM0_TIM0                   (*(volatile uint32 *)0xF0001010u)

/* CPU0_FLASHCON1.MASKUECC — mask PFlash UECC traps while probing APP. */
#define BOOT_CPU0_FLASHCON1              (*(volatile uint32 *)0xF8801104u)
/* MASKUECC[17:16]=01b (Infineon/Brs); do not touch PFI0_ECCS (can re-trap). */
#define BOOT_FLASHCON1_MASKUECC          (0x00010000u)
#define BOOT_FLASHCON1_MASKUECC_BITS     (0x00030000u)
/* DMU_HF_ECCC — TRAPDIS via CPU EndInit (Vector BrsHw path; NOT Safety EndInit). */
#define BOOT_DMU_HF_ECCC                 (*(volatile uint32 *)0xF8040048u)
#define BOOT_DMU_ECCC_TRAPDIS            (0xC0000000u)

/* Fixed address inside Variables_Shared (0x70026F80..0x70026FFF); leave low 64 B for BRS. */
#if defined (BRS_COMP_TASKING)
# pragma section farbss "brsSharedVar"
#endif
volatile Boot_HandshakeType Boot_Handshake __at(0x70026FC0u);
#if defined (BRS_COMP_TASKING)
# pragma section farbss restore
#endif

typedef char Boot_HsSizeCheck[(sizeof(Boot_HandshakeType) == BOOT_HS_SIZE) ? 1 : -1];

static uint8 Boot_App_FlsInited;
static uint8 Boot_App_ComStarted;
/* Set when APP JumpToBoot armed REQUEST_BOOT; Boot must send HIS 50 02. */
static uint8 Boot_App_PendingProgPosResp;

#if (BOOT_APP_CRC_TIME_MEASURE == 1)
volatile uint32 Boot_App_CrcMeas_Ticks;
volatile uint32 Boot_App_CrcMeas_Us;
volatile uint32 Boot_App_CrcMeas_Len;
volatile uint32 Boot_App_CrcMeas_Crc;
volatile uint32 Boot_App_CrcMeas_Ok;
#endif

static volatile Boot_HandshakeType* Boot_Hs(void)
{
  return &Boot_Handshake;
}

uint32 Boot_App_Crc32Acc(uint32 crcPrev, const uint8* data, uint32 length)
{
  if ((data == NULL_PTR) || (length == 0u))
  {
    return crcPrev;
  }
  return Crc_CalculateCRC32(data, length, crcPrev, FALSE);
}

uint32 Boot_App_Crc32(const uint8* data, uint32 length)
{
  if ((data == NULL_PTR) || (length == 0u))
  {
    return 0u;
  }
  return Crc_CalculateCRC32(data, length, 0u, TRUE);
}

uint32 Boot_App_ToCached(uint32 addr)
{
  if ((addr >= 0xA0000000u) && (addr <= 0xA0FFFFFFu))
  {
    return (addr - BOOT_FLASH_CACHED_TO_HW);
  }
  return addr;
}

uint32 Boot_App_ToHw(uint32 cachedOrHw)
{
  uint32 cached = Boot_App_ToCached(cachedOrHw);
  return (cached + BOOT_FLASH_CACHED_TO_HW);
}

boolean Boot_App_IsRangeInApp(uint32 start, uint32 length)
{
  uint32 cached;
  uint32 end;

  if (length == 0u)
  {
    return FALSE;
  }
  cached = Boot_App_ToCached(start);
  end = cached + length - 1u;
  if (end < cached)
  {
    return FALSE;
  }
  if ((cached < BOOT_FLASH_APP_START) || (end > BOOT_FLASH_APP_END))
  {
    return FALSE;
  }
  if (end <= BOOT_FLASH_BOOT_END)
  {
    return FALSE;
  }
  return TRUE;
}

static const Boot_AppHdrType* Boot_App_Hdr(void)
{
  return (const Boot_AppHdrType *)BOOT_FLASH_APP_START;
}

/* Disable PFlash UECC trap before probing APP.
 * Match Vector BrsHwDisableEccErrorReporting intent:
 * FLASHCON1.MASKUECC (Mcal CPU-EndInit) + DMU_HF_ECCC.TRAPDIS (Appl CPU-EndInit).
 * Do not call BrsHwUnlockInitInline from this TU — Tasking may emit an external
 * ref (ltc E106). Appl_UnlockEndinit is the linked equivalent in BrsHw.c.
 * Do NOT use Mcal Safety EndInit for DMU (traps in Boot_Init). */
static void Boot_App_MaskPfUeecc(void)
{
  uint32 v;

  v = (BOOT_CPU0_FLASHCON1 & ~BOOT_FLASHCON1_MASKUECC_BITS) | BOOT_FLASHCON1_MASKUECC;
  Mcal_WriteCpuEndInitProtReg((volatile void *)0xF8801104u, v);

  Appl_UnlockEndinit();
  BOOT_CPU0_FLASHCON1 = BOOT_FLASHCON1_MASKUECC;
  BOOT_DMU_HF_ECCC = BOOT_DMU_ECCC_TRAPDIS;
  Appl_LockEndinit();
#if defined (BRS_COMP_TASKING)
  __dsync();
  __isync();
#endif
}

void Boot_App_MaskUeeccForProbe(void)
{
  Boot_App_MaskPfUeecc();
}

static boolean Boot_App_IsPfUeeccMasked(void)
{
  return (((BOOT_CPU0_FLASHCON1 & BOOT_FLASHCON1_MASKUECC_BITS) != 0u) ? TRUE : FALSE);
}

static boolean Boot_App_IsVectorOk(uint32 vec, uint32 align)
{
  uint32 cached;

  if (vec == 0u)
  {
    return TRUE; /* optional field empty */
  }
  cached = Boot_App_ToCached(vec);
  if ((cached % align) != 0u)
  {
    return FALSE;
  }
  if (Boot_App_IsRangeInApp(cached, 4u) != TRUE)
  {
    return FALSE;
  }
  return TRUE;
}

boolean Boot_App_IsImageValid(void)
{
  const Boot_AppHdrType* hdr;
  uint32 len;
  uint32 crc;
  uint32 stored;
  uint8 tmp[BOOT_APP_HDR_SIZE];
  uint32 i;
  const uint8* flash;
  uint32 restLen;
  uint32 entry;
  uint32 magic;

  /* Mask UECC before ANY APP flash read — empty/corrupt APP (esp. after SWAP to B)
   * otherwise traps into Os_Hal_UnhandledException → Det_EndlessLoop / CoreFreeze. */
  Boot_App_MaskPfUeecc();
  if (Boot_App_IsPfUeeccMasked() != TRUE)
  {
    /* EndInit write did not stick: do not touch APP window. */
    return FALSE;
  }

  hdr = Boot_App_Hdr();
  magic = hdr->magic;
  /* Erased PFlash is 0x00 on TC3xx; also treat 0xFFFFFFFF as empty. */
  if ((magic == 0u) || (magic == 0xFFFFFFFFu) || (magic != BOOT_APP_HDR_MAGIC))
  {
    return FALSE;
  }

  len = hdr->length;
  if ((len < BOOT_APP_HDR_SIZE) || (len > BOOT_FLASH_APP_SIZE))
  {
    return FALSE;
  }
  if ((len % BOOT_FLASH_WRITE_ALIGN) != 0u)
  {
    return FALSE;
  }
  if (Boot_App_IsRangeInApp(BOOT_FLASH_APP_START, len) != TRUE)
  {
    return FALSE;
  }

  entry = Boot_App_ToCached(hdr->entry);
  if (Boot_App_IsRangeInApp(entry, 4u) != TRUE)
  {
    return FALSE;
  }
  /* No direct entry-word fetch: that is where UECC Trap hit on corrupt APP.
   * Integrity is covered by CRC below (MASKUECC already verified). */

  /* If either vector field is set, both must be valid (BTV 256 B, BIV 8 KB). */
  if ((hdr->intVec != 0u) || (hdr->trapVec != 0u))
  {
    if ((hdr->intVec == 0u) || (hdr->trapVec == 0u))
    {
      return FALSE;
    }
    if (Boot_App_IsVectorOk(hdr->intVec, 0x2000u) != TRUE)
    {
      return FALSE;
    }
    if (Boot_App_IsVectorOk(hdr->trapVec, 0x100u) != TRUE)
    {
      return FALSE;
    }
  }

  /* CRC(header with crc32=0 || payload). Prefer cached view under MASKUECC. */
  flash = (const uint8 *)BOOT_FLASH_APP_START;
  for (i = 0u; i < BOOT_APP_HDR_SIZE; i++)
  {
    tmp[i] = flash[i];
  }
  tmp[12] = 0u;
  tmp[13] = 0u;
  tmp[14] = 0u;
  tmp[15] = 0u;
  if ((Boot_App_FlsInited != 0u) || (Boot_App_ComStarted != 0u))
  {
    Boot_OsFlashTimer_Pause();
  }
#if (BOOT_APP_CRC_TIME_MEASURE == 1)
  {
    uint32 t0 = BOOT_STM0_TIM0;

    crc = Boot_App_Crc32(tmp, BOOT_APP_HDR_SIZE);
    restLen = len - BOOT_APP_HDR_SIZE;
    if (restLen > 0u)
    {
      crc = Boot_App_Crc32Acc(crc, &flash[BOOT_APP_HDR_SIZE], restLen);
    }

    Boot_App_CrcMeas_Ticks = BOOT_STM0_TIM0 - t0;
    Boot_App_CrcMeas_Us = Boot_App_CrcMeas_Ticks / 100u;
    Boot_App_CrcMeas_Len = len;
    Boot_App_CrcMeas_Crc = crc;
  }
#else
  crc = Boot_App_Crc32(tmp, BOOT_APP_HDR_SIZE);
  restLen = len - BOOT_APP_HDR_SIZE;
  if (restLen > 0u)
  {
    crc = Boot_App_Crc32Acc(crc, &flash[BOOT_APP_HDR_SIZE], restLen);
  }
#endif
  if ((Boot_App_FlsInited != 0u) || (Boot_App_ComStarted != 0u))
  {
    Boot_OsFlashTimer_Resume();
  }
  stored = hdr->crc32;
  if (crc != stored)
  {
#if (BOOT_APP_CRC_TIME_MEASURE == 1)
    Boot_App_CrcMeas_Ok = 0u;
#endif
    return FALSE;
  }
#if (BOOT_APP_CRC_TIME_MEASURE == 1)
  Boot_App_CrcMeas_Ok = 1u;
#endif
  return TRUE;
}

boolean Boot_App_IsRequestBoot(void)
{
  volatile Boot_HandshakeType* hs = Boot_Hs();

  if ((hs->magic == BOOT_HS_MAGIC) && (hs->cmd == BOOT_HS_CMD_REQUEST_BOOT))
  {
    return TRUE;
  }
  return FALSE;
}

void Boot_App_ClearRequestBoot(void)
{
  volatile Boot_HandshakeType* hs = Boot_Hs();

  hs->cmd = BOOT_HS_CMD_NONE;
  hs->magic = 0u;
}

void Boot_App_NotifyFlsInit(void)
{
  Boot_App_FlsInited = 1u;
}

void Boot_App_NotifyComStart(void)
{
  Boot_App_ComStarted = 1u;
}

static void Boot_App_ShutdownForJump(void)
{
  /* Global IE off first — no Boot ISRs while tearing down. */
#if defined (BRS_COMP_TASKING)
  __disable();
#endif

  if (Boot_App_ComStarted != 0u)
  {
    (void)CanIf_SetPduMode(CanIfConf_CanIfCtrlCfg_CT_CAN00_9df8a959, CANIF_SET_OFFLINE);
    (void)CanIf_SetControllerMode(CanIfConf_CanIfCtrlCfg_CT_CAN00_9df8a959, CANIF_CS_STOPPED);
    Boot_App_ComStarted = 0u;
  }

  if (Boot_App_FlsInited != 0u)
  {
    (void)FlsLoader_DeInit();
    Boot_App_FlsInited = 0u;
  }
}

/*
 * Do not use a C call: TriCore 'call' saves upper context into CSA / PCXI.
 * APP cold-start (brsStartupEntry) expects a clean context chain like reset.
 */
static void Boot_App_Jump(uint32 entry)
{
  uint32 entryCached = Boot_App_ToCached(entry);

  Boot_App_ShutdownForJump();

#if (BOOT_APP_JUMP_PROGRAM_VECTORS == 1)
  {
    const Boot_AppHdrType* hdr = Boot_App_Hdr();
    if ((hdr->intVec != 0u) && (hdr->trapVec != 0u))
    {
      BrsHw_ExceptionTable_Init(
          (Brs_AddressOfConstType)Boot_App_ToCached(hdr->trapVec),
          (Brs_AddressOfConstType)Boot_App_ToCached(hdr->intVec));
    }
  }
#endif

  /* Cut Boot CSA link; clear RA; absolute jump (no call).
   * Tasking: mov.a needs address from data reg (E110 if "a"(uint32)). */
  BRS_MOVE_TO_CSFR(BRS_PCXI_OFFSET, 0u);
#if defined (BRS_COMP_TASKING)
  __asm("mov.a a11,#0");
  __asm("mov d15,%0" : : "d"(entryCached) : "d15");
  __asm("mov.a a15,d15");
  __asm("ji a15");
  /* Local label — do not use "j ." (ltc resolves "." as extern). */
  __asm("Boot_App_JumpDead: j Boot_App_JumpDead");
#else
  {
    void (*appEntry)(void) = (void (*)(void))entryCached;
    appEntry();
  }
  for (;;)
  {
  }
#endif
}

void Boot_App_TryStart(void)
{
#if (BOOT_APP_JUMP_ENABLE == 1)
  const Boot_AppHdrType* hdr;

  Boot_App_MaskPfUeecc();

  if (Boot_App_IsRequestBoot() == TRUE)
  {
    /* HIS JumpToBoot: APP reset without 50 02; Boot must send it after COM up. */
    Boot_App_PendingProgPosResp = 1u;
    Boot_App_ClearRequestBoot();
    return;
  }
  /* Illegal ADDRCFG: stay in Boot (do not probe/jump). */
  if (Boot_Swap_IsMappingLegal() != TRUE)
  {
    return;
  }
#if (BOOT_APP_AUTO_JUMP == 0)
  /* Boot-only lab (no APP on A/B): never read APP PFlash — avoids UECC on dirty B. */
  return;
#else
  if (Boot_App_IsPfUeeccMasked() != TRUE)
  {
    return;
  }
  if (Boot_App_IsImageValid() != TRUE)
  {
    return;
  }
  hdr = Boot_App_Hdr();
  Boot_App_Jump(hdr->entry);
#endif
#endif
}

boolean Boot_App_TakePendingProgPosResp(void)
{
  if (Boot_App_PendingProgPosResp != 0u)
  {
    Boot_App_PendingProgPosResp = 0u;
    return TRUE;
  }
  return FALSE;
}

boolean Boot_App_IsPendingProgPosResp(void)
{
  return (Boot_App_PendingProgPosResp != 0u) ? TRUE : FALSE;
}

uint32 Boot_App_MixEntropy(void)
{
  return (BOOT_STM0_TIM0 ^ BOOT_SCU_CHIPID);
}
