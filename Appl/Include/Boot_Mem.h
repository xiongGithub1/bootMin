/**********************************************************************************************************************
 * Boot_Mem.h — Production PFlash layout (cached CPU view 0x8xxx)
 *
 *   0x80000000 ─┬─ BMHD + Startup + Boot code     128 KB  NEVER erase/write
 *   0x8001FFFF ─┘
 *   0x80020000 ─┬─ APP header (32 B) + APP image
 *   0x801FFFFF ─┘
 *
 * FlsLoader hardware view = cached + 0x20000000 (0xAxxx).
 * last364 must link from BOOT_FLASH_APP_START and must not emit BMHD.
 *********************************************************************************************************************/
#ifndef BOOT_MEM_H
#define BOOT_MEM_H

#include "Std_Types.h"

#ifndef BOOT_FLASH_BOOT_START
# define BOOT_FLASH_BOOT_START           (0x80000000u)
#endif
#ifndef BOOT_FLASH_BOOT_END
# define BOOT_FLASH_BOOT_END             (0x8001FFFFu)
#endif
#ifndef BOOT_FLASH_APP_START
# define BOOT_FLASH_APP_START            (0x80020000u)
#endif
#ifndef BOOT_FLASH_APP_END
# define BOOT_FLASH_APP_END              (0x801FFFFFu)
#endif

#define BOOT_FLASH_BOOT_SIZE             ((BOOT_FLASH_BOOT_END - BOOT_FLASH_BOOT_START) + 1u)
#define BOOT_FLASH_APP_SIZE              ((BOOT_FLASH_APP_END - BOOT_FLASH_APP_START) + 1u)
#define BOOT_FLASH_CACHED_TO_HW          (0x20000000u)

#define BOOT_FLASH_SECTOR_SIZE           (0x4000u) /* 16 KB PFlash sector */
#define BOOT_FLASH_WRITE_ALIGN           (32u)
#define BOOT_APP_HDR_SIZE                (32u)

#if (BOOT_FLASH_BOOT_SIZE != 0x20000u)
# error "Boot partition must be 128 KB (0x80000000..0x8001FFFF)"
#endif
#if (BOOT_FLASH_APP_START != (BOOT_FLASH_BOOT_END + 1u))
# error "APP must start immediately after Boot"
#endif

/* APP image header at BOOT_FLASH_APP_START. CRC covers [base, base+length)
 * with crc32 field treated as 0 while computing. */
#define BOOT_APP_HDR_MAGIC               (0xA5C3B007u)

typedef struct
{
  uint32 magic;
  uint32 entry;
  uint32 length;
  uint32 crc32;
  uint32 version;
  uint32 intVec;    /* APP interrupt vector table base (BIV); 0 = no check */
  uint32 trapVec;   /* APP trap vector table base (BTV); 0 = no check */
  uint32 reserved2;
} Boot_AppHdrType;

/*
 * Shared no-init RAM (DSPR0), same layout in Boot and last364:
 *   DSPR_Core0        0x70000000  size 159616
 *   Variables_Shared  0x70026F80  size 128
 *     handshake @     0x70026FC0  size 64
 *   StartupStack      0x70027000 ..
 * Soft reset keeps this; APP writes REQUEST_BOOT then resets; Boot stays in FBL.
 */
#define BOOT_HS_BASE                     (0x70026FC0u)
#define BOOT_HS_SIZE                     (64u)
#define BOOT_HS_MAGIC                    (0xB007B007u)
#define BOOT_HS_CMD_NONE                 (0u)
#define BOOT_HS_CMD_REQUEST_BOOT         (1u)

typedef struct
{
  uint32 magic;
  uint32 cmd;
  uint32 reserved[14]; /* 64 bytes total */
} Boot_HandshakeType;

#ifndef BOOT_APP_JUMP_ENABLE
# define BOOT_APP_JUMP_ENABLE            (1u)
#endif
/* 1 = program BIV/BTV from header before jump (only if entry skips APP startup).
 * 0 = entry is brsStartupEntry; APP startup programs vectors (recommended). */
#ifndef BOOT_APP_JUMP_PROGRAM_VECTORS
# define BOOT_APP_JUMP_PROGRAM_VECTORS   (0u)
#endif

#endif /* BOOT_MEM_H */
