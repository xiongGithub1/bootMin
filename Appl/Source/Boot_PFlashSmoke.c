/**********************************************************************************************************************
 * Boot_PFlashSmoke.c — PSPR erase + page-write (TC234-style)
 *
 * Leaf bodies must be self-contained (no calls into PFlash). Helpers are macros / inlined.
 *********************************************************************************************************************/
#include "Boot_PFlashSmoke.h"
#include "Boot_OsFlashTimer.h"
#include "Mcal_Compiler.h"

#define BOOT_SMOKE_ERASE_PSPR    (0x70102000u)
#define BOOT_SMOKE_WRITE_PSPR    (0x70102800u)
#define BOOT_SMOKE_LEAF_BYTES    (0x800u)
#define BOOT_P0BUSY              (0x4u)
#define BOOT_PFPAGE              (0x200000u)
#define BOOT_PAGE_BYTES          (32u)
#define BOOT_SECTOR_BYTES        (0x4000u)

volatile uint32 Boot_Smoke_OpResult;
volatile uint32 Boot_Smoke_ErrSr;
volatile uint32 Boot_Smoke_Status;
volatile uint32 Boot_Smoke_PsprOk;
volatile uint32 Boot_Smoke_CopyLen;
volatile uint32 Boot_Smoke_Phase;
volatile uint32 Boot_Smoke_PsprWord;
volatile uint32 Boot_Smoke_HwAddr;

typedef struct
{
  volatile uint32 *cmd_fa;
  volatile uint32 *cmd_aa50;
  volatile uint32 *cmd_aa58;
  volatile uint32 *cmd_aaa8;
  volatile uint32 *cmd_55f0;
  volatile uint32 *cmd_55f4;
  volatile uint32 *wdt;
  volatile uint32 *status;
  volatile uint32 *errsr;
  volatile uint32 *op;
  volatile uint32 *err;
  volatile uint32 *st;
  volatile uint32 *phase;
} Boot_SmokeCtx;

typedef void (*Boot_SmokeEraseFn)(uint32 hwAddr, uint32 nSec, Boot_SmokeCtx *ctx);
typedef void (*Boot_SmokeWriteFn)(uint32 hwAddr, uint32 nPages, const uint32 *data, Boot_SmokeCtx *ctx);

static Boot_SmokeCtx Boot_Smoke_Ctx;
static Boot_SmokeEraseFn Boot_Smoke_EraseFp;
static Boot_SmokeWriteFn Boot_Smoke_WriteFp;
static uint8 Boot_Smoke_Ready;

#pragma optimize 0

/* Entire body is memcpy'd to PSPR — no calls to Flash-resident code. */
static void Boot_Smoke_EraseLeaf(uint32 hwAddr, uint32 nSec, Boot_SmokeCtx *ctx)
{
  uint32 con0;
  uint32 pw;
  uint32 rel;
  uint32 v;
  uint32 spins;
  uint32 stv;
  uint32 e;

  *(ctx->phase) = 1u;
  *(ctx->op) = 0xFFu;
  *(ctx->err) = 0u;
  *(ctx->st) = 0u;

  *(ctx->cmd_fa) = 0xFAu;
  __asm("dsync");

  con0 = *(ctx->wdt);
  pw = con0 & 0x0000FFFCU;
  pw = (pw & 0x0000FF00U) | ((~(pw & 0x000000FCU)) & 0x000000FCU);
  rel = con0 & 0xFFFF0000U;
  v = rel | pw | 1u;
  *(ctx->wdt) = v;
  v &= ~0x3u;
  v |= 2u;
  *(ctx->wdt) = v;

  *(ctx->cmd_aa50) = hwAddr;
  __asm("dsync");
  *(ctx->cmd_aa58) = nSec;
  __asm("dsync");
  *(ctx->cmd_aaa8) = 0x80u;
  __asm("dsync");
  *(ctx->cmd_aaa8) = 0x50u;
  __asm("dsync");

  con0 = *(ctx->wdt);
  pw = con0 & 0x0000FFFCU;
  pw = (pw & 0x0000FF00U) | ((~(pw & 0x000000FCU)) & 0x000000FCU);
  rel = con0 & 0xFFFF0000U;
  v = rel | pw | 1u;
  *(ctx->wdt) = v;
  v &= ~0x3u;
  v |= 3u;
  *(ctx->wdt) = v;

  *(ctx->phase) = 2u;
  spins = 0u;
  do
  {
    stv = *(ctx->status);
    *(ctx->st) = stv;
    spins++;
    if (spins > 2000000000u)
    {
      *(ctx->err) = *(ctx->errsr);
      *(ctx->op) = 0xFFu;
      *(ctx->phase) = 8u;
      return;
    }
  } while ((stv & BOOT_P0BUSY) != 0u);

  *(ctx->err) = *(ctx->errsr);
  *(ctx->st) = *(ctx->status);
  e = *(ctx->err);
  if ((e & 0x1u) != 0u)
  {
    *(ctx->op) = 6u;
  }
  else if ((e & 0x2u) != 0u)
  {
    *(ctx->op) = 7u;
  }
  else if ((e & 0x3Cu) != 0u)
  {
    *(ctx->op) = 3u;
  }
  else
  {
    *(ctx->op) = 0u;
  }
  *(ctx->phase) = 9u;
}

static void Boot_Smoke_WriteLeaf(uint32 hwAddr, uint32 nPages, const uint32 *data, Boot_SmokeCtx *ctx)
{
  uint32 page;
  uint32 spins;
  uint32 stv;
  uint32 wi;
  uint32 con0;
  uint32 pw;
  uint32 rel;
  uint32 v;
  uint32 e;
  const uint32 *p;

  *(ctx->phase) = 11u;
  *(ctx->op) = 0xFFu;
  p = data;

  for (page = 0u; page < nPages; page++)
  {
    *(ctx->cmd_fa) = 0xFAu;
    __asm("dsync");

    *(ctx->cmd_fa) = 0x50u;
    __asm("dsync");

    spins = 0u;
    do
    {
      stv = *(ctx->status);
      spins++;
      if (spins > 1000000u)
      {
        *(ctx->err) = *(ctx->errsr);
        *(ctx->op) = 2u;
        *(ctx->phase) = 18u;
        return;
      }
    } while ((stv & BOOT_PFPAGE) == 0u);

    for (wi = 0u; wi < 4u; wi++)
    {
      *(ctx->cmd_55f0) = p[0];
      __asm("dsync");
      *(ctx->cmd_55f4) = p[1];
      __asm("dsync");
      p += 2u;
    }

    con0 = *(ctx->wdt);
    pw = con0 & 0x0000FFFCU;
    pw = (pw & 0x0000FF00U) | ((~(pw & 0x000000FCU)) & 0x000000FCU);
    rel = con0 & 0xFFFF0000U;
    v = rel | pw | 1u;
    *(ctx->wdt) = v;
    v &= ~0x3u;
    v |= 2u;
    *(ctx->wdt) = v;

    *(ctx->cmd_aa50) = hwAddr;
    __asm("dsync");
    *(ctx->cmd_aa58) = 0u;
    __asm("dsync");
    *(ctx->cmd_aaa8) = 0xA0u;
    __asm("dsync");
    *(ctx->cmd_aaa8) = 0xAAu;
    __asm("dsync");

    con0 = *(ctx->wdt);
    pw = con0 & 0x0000FFFCU;
    pw = (pw & 0x0000FF00U) | ((~(pw & 0x000000FCU)) & 0x000000FCU);
    rel = con0 & 0xFFFF0000U;
    v = rel | pw | 1u;
    *(ctx->wdt) = v;
    v &= ~0x3u;
    v |= 3u;
    *(ctx->wdt) = v;

    spins = 0u;
    do
    {
      stv = *(ctx->status);
      *(ctx->st) = stv;
      spins++;
      if (spins > 20000000u)
      {
        *(ctx->err) = *(ctx->errsr);
        *(ctx->op) = 0xFFu;
        *(ctx->phase) = 18u;
        return;
      }
    } while ((stv & BOOT_P0BUSY) != 0u);

    *(ctx->err) = *(ctx->errsr);
    *(ctx->st) = *(ctx->status);
    e = *(ctx->err);
    if ((e & 0x1u) != 0u)
    {
      *(ctx->op) = 6u;
      *(ctx->phase) = 19u;
      return;
    }
    if ((e & 0x2u) != 0u)
    {
      *(ctx->op) = 7u;
      *(ctx->phase) = 19u;
      return;
    }
    if ((e & 0x3Cu) != 0u)
    {
      *(ctx->op) = 3u;
      *(ctx->phase) = 19u;
      return;
    }

    hwAddr += BOOT_PAGE_BYTES;
  }

  *(ctx->op) = 0u;
  *(ctx->phase) = 29u;
}

#pragma optimize restore

static Std_ReturnType Boot_Smoke_CopyLeaf(uint32 psprAddr, const void *srcFn)
{
  uint8 *dst;
  const uint8 *src;
  uint32 i;

  src = (const uint8 *)srcFn;
  dst = (uint8 *)psprAddr;
  for (i = 0u; i < BOOT_SMOKE_LEAF_BYTES; i++)
  {
    dst[i] = src[i];
  }
  __asm("dsync");
  __asm("isync");

  if (*(volatile uint32 *)psprAddr != *(const uint32 *)(const void *)src)
  {
    return E_NOT_OK;
  }
  return E_OK;
}

void Boot_PFlashSmoke_Init(void)
{
  Boot_Smoke_Ready = 0u;
  Boot_Smoke_PsprOk = 0u;
  Boot_Smoke_OpResult = 0u;
  Boot_Smoke_Phase = 0u;
  Boot_Smoke_EraseFp = 0;
  Boot_Smoke_WriteFp = 0;
  Boot_Smoke_CopyLen = BOOT_SMOKE_LEAF_BYTES;

  Boot_Smoke_Ctx.cmd_fa   = (volatile uint32 *)(0xAF000000u + 0x5554u);
  Boot_Smoke_Ctx.cmd_aa50 = (volatile uint32 *)(0xAF000000u + 0xAA50u);
  Boot_Smoke_Ctx.cmd_aa58 = (volatile uint32 *)(0xAF000000u + 0xAA58u);
  Boot_Smoke_Ctx.cmd_aaa8 = (volatile uint32 *)(0xAF000000u + 0xAAA8u);
  Boot_Smoke_Ctx.cmd_55f0 = (volatile uint32 *)(0xAF000000u + 0x55F0u);
  Boot_Smoke_Ctx.cmd_55f4 = (volatile uint32 *)(0xAF000000u + 0x55F4u);
  Boot_Smoke_Ctx.wdt      = (volatile uint32 *)0xF00362A8u;
  Boot_Smoke_Ctx.status   = (volatile uint32 *)0xF8040010u;
  Boot_Smoke_Ctx.errsr    = (volatile uint32 *)0xF8040034u;
  Boot_Smoke_Ctx.op       = &Boot_Smoke_OpResult;
  Boot_Smoke_Ctx.err      = &Boot_Smoke_ErrSr;
  Boot_Smoke_Ctx.st       = &Boot_Smoke_Status;
  Boot_Smoke_Ctx.phase    = &Boot_Smoke_Phase;

  if (Boot_Smoke_CopyLeaf(BOOT_SMOKE_ERASE_PSPR, (const void *)&Boot_Smoke_EraseLeaf) != E_OK)
  {
    Boot_Smoke_OpResult = 2u;
    return;
  }
  if (Boot_Smoke_CopyLeaf(BOOT_SMOKE_WRITE_PSPR, (const void *)&Boot_Smoke_WriteLeaf) != E_OK)
  {
    Boot_Smoke_OpResult = 2u;
    return;
  }

  Boot_Smoke_PsprWord = *(volatile uint32 *)BOOT_SMOKE_ERASE_PSPR;
  Boot_Smoke_EraseFp = (Boot_SmokeEraseFn)BOOT_SMOKE_ERASE_PSPR;
  Boot_Smoke_WriteFp = (Boot_SmokeWriteFn)BOOT_SMOKE_WRITE_PSPR;
  Boot_Smoke_Ready = 1u;
  Boot_Smoke_PsprOk = 1u;
}

static Std_ReturnType Boot_Smoke_EnsureReady(void)
{
  if ((Boot_Smoke_Ready == 0u) || (Boot_Smoke_EraseFp == 0) || (Boot_Smoke_WriteFp == 0))
  {
    Boot_PFlashSmoke_Init();
  }
  if ((Boot_Smoke_Ready == 0u) || (Boot_Smoke_PsprOk == 0u))
  {
    Boot_Smoke_OpResult = 2u;
    return E_NOT_OK;
  }
  return E_OK;
}

Std_ReturnType Boot_PFlashSmoke_EraseOneSector(uint32 hwSectorAddr)
{
  return Boot_PFlashSmoke_EraseSectors(hwSectorAddr, 1u);
}

Std_ReturnType Boot_PFlashSmoke_EraseSectors(uint32 hwSectorAddr, uint32 sectorCount)
{
  if (Boot_Smoke_EnsureReady() != E_OK)
  {
    return E_NOT_OK;
  }
  if ((hwSectorAddr & (BOOT_SECTOR_BYTES - 1u)) != 0u)
  {
    Boot_Smoke_OpResult = 1u;
    return E_NOT_OK;
  }
  if ((sectorCount == 0u) || (sectorCount > 128u))
  {
    Boot_Smoke_OpResult = 1u;
    return E_NOT_OK;
  }

  /* One Erase Logical Sector Range command for all sectors (not 120x enter/exit). */
  Boot_Smoke_HwAddr = hwSectorAddr;
  Boot_Smoke_Phase = 0u;
  Boot_OsFlashTimer_Pause();
  DISABLE();
  __asm("dsync");

  Boot_Smoke_EraseFp(hwSectorAddr, sectorCount, &Boot_Smoke_Ctx);

  __asm("dsync");
  Boot_OsFlashTimer_Resume();
  ENABLE();

  return (Boot_Smoke_OpResult == 0u) ? E_OK : E_NOT_OK;
}

Std_ReturnType Boot_PFlashSmoke_Write(uint32 hwAddr, uint32 length, const uint8 *data)
{
  uint32 nPages;
  uint32 i;
  const uint32 *dataWords;
  static uint32 alignBuf[128]; /* 512 B, enough for CDD_TP_RX_BUF_SIZE payload */

  if (Boot_Smoke_EnsureReady() != E_OK)
  {
    return E_NOT_OK;
  }
  if ((data == 0) || (length == 0u))
  {
    Boot_Smoke_OpResult = 4u;
    return E_NOT_OK;
  }
  if (((hwAddr & (BOOT_PAGE_BYTES - 1u)) != 0u) || ((length & (BOOT_PAGE_BYTES - 1u)) != 0u))
  {
    Boot_Smoke_OpResult = 4u;
    return E_NOT_OK;
  }
  if (length > (uint32)sizeof(alignBuf))
  {
    Boot_Smoke_OpResult = 4u;
    return E_NOT_OK;
  }

  /* UDS payload is often at rx[2] — not word-aligned; leaf needs uint32 loads. */
  if (((uint32)data & 0x3u) != 0u)
  {
    for (i = 0u; i < length; i++)
    {
      ((uint8 *)(void *)alignBuf)[i] = data[i];
    }
    dataWords = alignBuf;
  }
  else
  {
    dataWords = (const uint32 *)(const void *)data;
  }

  nPages = length / BOOT_PAGE_BYTES;
  Boot_Smoke_HwAddr = hwAddr;
  Boot_Smoke_Phase = 10u;

  Boot_OsFlashTimer_Pause();
  DISABLE();
  __asm("dsync");

  Boot_Smoke_WriteFp(hwAddr, nPages, dataWords, &Boot_Smoke_Ctx);

  __asm("dsync");
  Boot_OsFlashTimer_Resume();
  ENABLE();

  return (Boot_Smoke_OpResult == 0u) ? E_OK : E_NOT_OK;
}
