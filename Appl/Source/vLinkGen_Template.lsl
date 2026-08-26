/**********************************************************************************************************************
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
 *  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
 *  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
 *  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before their use.
 *********************************************************************************************************************/


architecture TC1V1.6.2
{
  endianness
  {
    little;
  }
  space linear
  {
    id = 1;
    mau = 8;
    map (dest = bus:local_bus, size = 4G);
    copytable (align = 4, copy_unit = 1, dest = linear);
  }
  bus local_bus
  {
    mau = 8;
    width = 32;
  }
}

/**********************************************************************************************************************
 * CAUTION - DO NOT EDIT
 * -------------------------------------------------------------------------------------------------------------------
 * Never manually edit the following memory definitions in this file. Only change them in the vLinkGen configuration
 * (/MICROSAR/vLinkGen/vLinkGenMemLayout/vLinkGenMemoryRegion/vLinkGenMemoryRegionBlock) and regenerate the files.
 *********************************************************************************************************************/
derivative mpe
{
  core vtc
  {
    architecture = TC1V1.6.2;
  }
  bus local_bus
  {
    mau = 8;
    width = 32;
    map (dest = bus:vtc:local_bus, dest_offset = 0, size = 4G);
  }
  section_setup :vtc:linear
  {
    start_address (symbol = "brsStartupEntry");
  }
  memory DSPR_Core1
  {
    mau = 8;
    type = ram;
    size = 196608; /* 192 KiB */
    map (dest=bus:local_bus, dest_offset = 0x60000000, size = 196608);
  }
  memory DSPR_Core0
  {
    mau = 8;
    type = ram;
    size = 159616; /* 156 KiB */
    map (dest=bus:local_bus, dest_offset = 0x70000000, size = 159616);
  }
  memory Variables_Shared
  {
    mau = 8;
    type = ram;
    size = 128; /* 128 Byte */
    map (dest=bus:local_bus, dest_offset = 0x70026F80, size = 128);
  }
  memory StartupStack_Shared
  {
    mau = 8;
    type = ram;
    size = 36864; /* 36 KiB */
    map (dest=bus:local_bus, dest_offset = 0x70027000, size = 36864);
  }
  memory PSPR0
  {
    mau = 8;
    type = ram;
    size = 32768; /* 32 KiB */
    map (dest=bus:local_bus, dest_offset = 0x70100000, size = 32768);
  }
  memory StartupCode_FirstExecInst
  {
    mau = 8;
    type = rom;
    size = 1280; /* 1 KiB */
    map (dest=bus:local_bus, dest_offset = 0x80000000, size = 1280);
  }
  memory CoreExceptions_FirstExecInst
  {
    mau = 8;
    type = rom;
    size = 512; /* 512 Byte */
    map (dest=bus:local_bus, dest_offset = 0x80000500, size = 512);
  }
  memory PFlash0_Cached
  {
    mau = 8;
    type = rom;
    size = 127488; /* 124 KiB */
    map (dest=bus:local_bus, dest_offset = 0x80000700, size = 127488);
  }
  memory BMHD0
  {
    mau = 8;
    type = rom;
    size = 512; /* 512 Byte */
    map (dest=bus:local_bus, dest_offset = 0xAF400000, size = 512);
  }
}

section_layout mpe:vtc:linear
{
  group OS_STACKS_CORE0_VAR_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group OS_STACKS_CORE0_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_STACKS_CORE0_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_STACK_OSCORE0_ERROR_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_INIT_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_ISR_CORE_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_KERNEL_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO30_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO4294967295_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO49_VAR_NOINIT";
        select "[.]bss.OS_STACK_OSCORE0_TASK_PRIO50_VAR_NOINIT";
      }
    }
    group OS_STACKS_CORE0_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_STACKS_CORE0_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_STACKS_CORE0_VAR_NOINIT_START" = "_lc_gb_OS_STACKS_CORE0_VAR_NOINIT";
    "_OS_STACKS_CORE0_VAR_NOINIT_END" = ("_lc_gb_OS_STACKS_CORE0_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_STACKS_CORE0_VAR_NOINIT_PAD" - 1;
    "_OS_STACKS_CORE0_VAR_NOINIT_LIMIT" = "_lc_gb_OS_STACKS_CORE0_VAR_NOINIT_PAD";

    "_OS_STACKS_CORE0_VAR_ALL_START" = "_OS_STACKS_CORE0_VAR_NOINIT_START";
    "_OS_STACKS_CORE0_VAR_ALL_END" = "_OS_STACKS_CORE0_VAR_NOINIT_END";
    "_OS_STACKS_CORE0_VAR_ALL_LIMIT" = "_OS_STACKS_CORE0_VAR_NOINIT_LIMIT";
  }

  group Brs_ExcVect_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:CoreExceptions_FirstExecInst)
  {
    group Brs_ExcVect (ordered, contiguous, fill, align = 256)
    {
      section "Brs_ExcVect_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.brsExcVect";
        select "[.]rodata.brsExcVectConst";
      }
    }
    group Brs_ExcVect_PAD (align = 8)
    {
      reserved "Brs_ExcVect_PAD" (size = 16);
    }
    "_Brs_ExcVect_START" = "_lc_gb_Brs_ExcVect";
    "_Brs_ExcVect_END" = ("_lc_gb_Brs_ExcVect_PAD" == 0) ? 0 : "_lc_gb_Brs_ExcVect_PAD" - 1;
    "_Brs_ExcVect_LIMIT" = "_lc_gb_Brs_ExcVect_PAD";

    "_Brs_ExcVect_ALL_START" = "_Brs_ExcVect_START";
    "_Brs_ExcVect_ALL_END" = "_Brs_ExcVect_END";
    "_Brs_ExcVect_ALL_LIMIT" = "_Brs_ExcVect_LIMIT";
  }

  group Brs_Startup_Code_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:StartupCode_FirstExecInst)
  {
    group Brs_Startup_Code (ordered, contiguous, fill)
    {
      section "Brs_Startup_Code_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.brsStartup";
      }
    }
    "_Brs_Startup_Code_START" = "_lc_gb_Brs_Startup_Code";
    "_Brs_Startup_Code_END" = ("_lc_ge_Brs_Startup_Code" == 0) ? 0 : "_lc_ge_Brs_Startup_Code" - 1;
    "_Brs_Startup_Code_LIMIT" = "_lc_ge_Brs_Startup_Code";

    group BrsMain_Startup_Code (ordered, contiguous, fill)
    {
      section "BrsMain_Startup_Code_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.brsMainStartup";
      }
    }
    "_BrsMain_Startup_Code_START" = "_lc_gb_BrsMain_Startup_Code";
    "_BrsMain_Startup_Code_END" = ("_lc_ge_BrsMain_Startup_Code" == 0) ? 0 : "_lc_ge_BrsMain_Startup_Code" - 1;
    "_BrsMain_Startup_Code_LIMIT" = "_lc_ge_BrsMain_Startup_Code";

    "_Brs_Startup_Code_ALL_START" = "_Brs_Startup_Code_START";
    "_Brs_Startup_Code_ALL_END" = "_BrsMain_Startup_Code_END";
    "_Brs_Startup_Code_ALL_LIMIT" = "_BrsMain_Startup_Code_LIMIT";
  }

  group BMHD0_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:BMHD0)
  {
    group BMHD0 (ordered, contiguous, fill)
    {
      section "BMHD0_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.BMHD0";
      }
    }
    "_BMHD0_START" = "_lc_gb_BMHD0";
    "_BMHD0_END" = ("_lc_ge_BMHD0" == 0) ? 0 : "_lc_ge_BMHD0" - 1;
    "_BMHD0_LIMIT" = "_lc_ge_BMHD0";

    "_BMHD0_ALL_START" = "_BMHD0_START";
    "_BMHD0_ALL_END" = "_BMHD0_END";
    "_BMHD0_ALL_LIMIT" = "_BMHD0_LIMIT";
  }

  group Brs_Shared_Const_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group Brs_Shared_Const (ordered, contiguous, fill)
    {
      section "Brs_Shared_Const_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.brsSharedConst";
      }
    }
    "_Brs_Shared_Const_START" = "_lc_gb_Brs_Shared_Const";
    "_Brs_Shared_Const_END" = ("_lc_ge_Brs_Shared_Const" == 0) ? 0 : "_lc_ge_Brs_Shared_Const" - 1;
    "_Brs_Shared_Const_LIMIT" = "_lc_ge_Brs_Shared_Const";

    "_Brs_Shared_Const_ALL_START" = "_Brs_Shared_Const_START";
    "_Brs_Shared_Const_ALL_END" = "_Brs_Shared_Const_END";
    "_Brs_Shared_Const_ALL_LIMIT" = "_Brs_Shared_Const_LIMIT";
  }

  group Brs_Shared_Var_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:Variables_Shared)
  {
    group Brs_Shared_Var (ordered, contiguous, fill, align = 16)
    {
      section "Brs_Shared_Var_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.brsSharedVar";
      }
    }
    "_Brs_Shared_Var_START" = "_lc_gb_Brs_Shared_Var";
    "_Brs_Shared_Var_END" = ("_lc_ge_Brs_Shared_Var" == 0) ? 0 : "_lc_ge_Brs_Shared_Var" - 1;
    "_Brs_Shared_Var_LIMIT" = "_lc_ge_Brs_Shared_Var";

    "_Brs_Shared_Var_ALL_START" = "_Brs_Shared_Var_START";
    "_Brs_Shared_Var_ALL_END" = "_Brs_Shared_Var_END";
    "_Brs_Shared_Var_ALL_LIMIT" = "_Brs_Shared_Var_LIMIT";
  }

  group FlsLoader_WriteErase_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group FlsLoader_WriteErase_ROM (ordered, contiguous, fill, align = 4)
    {
      section "FlsLoader_WriteErase_ROM_SEC" (fill, blocksize = 1, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]text.FlsLoader_WriteErase";
        }
      }
    }
    "_FlsLoader_WriteErase_ROM_START" = "_lc_gb_FlsLoader_WriteErase_ROM";
    "_FlsLoader_WriteErase_ROM_LIMIT" = "_lc_ge_FlsLoader_WriteErase_ROM";

  }

  group FlsLoader_WriteErase_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PSPR0)
  {
    group FlsLoader_WriteErase_ALIGN (align = 4)
    {
      reserved "FlsLoader_WriteErase_ALIGN" (size = 4);
    }
    group FlsLoader_WriteErase (ordered, contiguous, fill, align = 1, copy)
    {
      /* Due to a Linker issue: 'COPY_TO_RAM' const groups cannot be created with inner output section */
      select "[.]text.FlsLoader_WriteErase";
    }
    group FlsLoader_WriteErase_PAD (align = 4)
    {
      reserved "FlsLoader_WriteErase_PAD" (size = 0);
    }
    "_FlsLoader_WriteErase_START" = "_lc_gb_FlsLoader_WriteErase";
    "_FlsLoader_WriteErase_END" = ("_lc_ge_FlsLoader_WriteErase" == 0) ? 0 : "_lc_ge_FlsLoader_WriteErase" - 1;
    "_FlsLoader_WriteErase_LIMIT" = "_lc_ge_FlsLoader_WriteErase";

    "_FlsLoader_WriteErase_ALL_START" = "_FlsLoader_WriteErase_START";
    "_FlsLoader_WriteErase_ALL_END" = "_FlsLoader_WriteErase_END";
    "_FlsLoader_WriteErase_ALL_LIMIT" = "_FlsLoader_WriteErase_LIMIT";
  }

  "__HEAP" = 8;
  "__HEAP_END" = 8;

  group MSR_CODE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group MSR_CODE (ordered, contiguous, fill)
    {
      section "MSR_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.MSR_CODE";
      }
    }
    "_MSR_CODE_START" = "_lc_gb_MSR_CODE";
    "_MSR_CODE_END" = ("_lc_ge_MSR_CODE" == 0) ? 0 : "_lc_ge_MSR_CODE" - 1;
    "_MSR_CODE_LIMIT" = "_lc_ge_MSR_CODE";

    "_MSR_CODE_ALL_START" = "_MSR_CODE_START";
    "_MSR_CODE_ALL_END" = "_MSR_CODE_END";
    "_MSR_CODE_ALL_LIMIT" = "_MSR_CODE_LIMIT";
  }

  group MSR_CONST_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group MSR_CONST (ordered, contiguous, fill)
    {
      section "MSR_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.MSR_CONST";
        select "[.]zrodata.MSR_CONST_FAST";
      }
    }
    "_MSR_CONST_START" = "_lc_gb_MSR_CONST";
    "_MSR_CONST_END" = ("_lc_ge_MSR_CONST" == 0) ? 0 : "_lc_ge_MSR_CONST" - 1;
    "_MSR_CONST_LIMIT" = "_lc_ge_MSR_CONST";

    "_MSR_CONST_ALL_START" = "_MSR_CONST_START";
    "_MSR_CONST_ALL_END" = "_MSR_CONST_END";
    "_MSR_CONST_ALL_LIMIT" = "_MSR_CONST_LIMIT";
  }

  group MSR_PBCFG_CONST_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group MSR_PBCFG_CONST (ordered, contiguous, fill)
    {
      section "MSR_PBCFG_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.MSR_PBCFG_CONST";
        select "[.]zrodata.MSR_PBCFG_CONST_FAST";
      }
    }
    "_MSR_PBCFG_CONST_START" = "_lc_gb_MSR_PBCFG_CONST";
    "_MSR_PBCFG_CONST_END" = ("_lc_ge_MSR_PBCFG_CONST" == 0) ? 0 : "_lc_ge_MSR_PBCFG_CONST" - 1;
    "_MSR_PBCFG_CONST_LIMIT" = "_lc_ge_MSR_PBCFG_CONST";

    "_MSR_PBCFG_CONST_ALL_START" = "_MSR_PBCFG_CONST_START";
    "_MSR_PBCFG_CONST_ALL_END" = "_MSR_PBCFG_CONST_END";
    "_MSR_PBCFG_CONST_ALL_LIMIT" = "_MSR_PBCFG_CONST_LIMIT";
  }

  group MSR_PBCFG_VAR_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group MSR_PBCFG_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "MSR_PBCFG_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.MSR_PBCFG_VAR";
          select "[.]zdata.MSR_PBCFG_VAR_FAST";
        }
      }
    }
    "_MSR_PBCFG_VAR_INIT_ROM_START" = "_lc_gb_MSR_PBCFG_VAR_INIT_ROM";
    "_MSR_PBCFG_VAR_INIT_ROM_LIMIT" = "_lc_ge_MSR_PBCFG_VAR_INIT_ROM";

  }

  group MSR_PBCFG_VAR_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group MSR_PBCFG_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "MSR_PBCFG_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.MSR_PBCFG_VAR";
        select "[.]zdata.MSR_PBCFG_VAR_FAST";
      }
    }
    group MSR_PBCFG_VAR_INIT_PAD (align = 4)
    {
      reserved "MSR_PBCFG_VAR_INIT_PAD" (size = 0);
    }
    "_MSR_PBCFG_VAR_INIT_START" = "_lc_gb_MSR_PBCFG_VAR_INIT";
    "_MSR_PBCFG_VAR_INIT_END" = ("_lc_ge_MSR_PBCFG_VAR_INIT" == 0) ? 0 : "_lc_ge_MSR_PBCFG_VAR_INIT" - 1;
    "_MSR_PBCFG_VAR_INIT_LIMIT" = "_lc_ge_MSR_PBCFG_VAR_INIT";

    group MSR_PBCFG_VAR_NO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "MSR_PBCFG_VAR_NO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.MSR_PBCFG_VAR_FAST_NO_INIT";
        select "[.]bss.MSR_PBCFG_VAR_NO_INIT";
      }
    }
    "_MSR_PBCFG_VAR_NO_INIT_START" = "_lc_gb_MSR_PBCFG_VAR_NO_INIT";
    "_MSR_PBCFG_VAR_NO_INIT_END" = ("_lc_ge_MSR_PBCFG_VAR_NO_INIT" == 0) ? 0 : "_lc_ge_MSR_PBCFG_VAR_NO_INIT" - 1;
    "_MSR_PBCFG_VAR_NO_INIT_LIMIT" = "_lc_ge_MSR_PBCFG_VAR_NO_INIT";

    "_MSR_PBCFG_VAR_ALL_START" = "_MSR_PBCFG_VAR_INIT_START";
    "_MSR_PBCFG_VAR_ALL_END" = "_MSR_PBCFG_VAR_NO_INIT_END";
    "_MSR_PBCFG_VAR_ALL_LIMIT" = "_MSR_PBCFG_VAR_NO_INIT_LIMIT";
  }

  group MSR_VAR_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group MSR_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "MSR_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.MSR_VAR_FAST_INIT";
          select "[.]data.MSR_VAR_INIT";
        }
      }
    }
    "_MSR_VAR_INIT_ROM_START" = "_lc_gb_MSR_VAR_INIT_ROM";
    "_MSR_VAR_INIT_ROM_LIMIT" = "_lc_ge_MSR_VAR_INIT_ROM";

  }

  group MSR_VAR_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group MSR_VAR_CLEARED (ordered, contiguous, fill, align = 16)
    {
      section "MSR_VAR_CLEARED_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.MSR_VAR_CLEARED";
        select "[.]*.MSR_VAR_FAST_CLEARED";
      }
    }
    group MSR_VAR_CLEARED_PAD (align = 4)
    {
      reserved "MSR_VAR_CLEARED_PAD" (size = 0);
    }
    "_MSR_VAR_CLEARED_START" = "_lc_gb_MSR_VAR_CLEARED";
    "_MSR_VAR_CLEARED_END" = ("_lc_ge_MSR_VAR_CLEARED" == 0) ? 0 : "_lc_ge_MSR_VAR_CLEARED" - 1;
    "_MSR_VAR_CLEARED_LIMIT" = "_lc_ge_MSR_VAR_CLEARED";

    group MSR_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "MSR_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.MSR_VAR_FAST_INIT";
        select "[.]data.MSR_VAR_INIT";
      }
    }
    group MSR_VAR_INIT_PAD (align = 4)
    {
      reserved "MSR_VAR_INIT_PAD" (size = 0);
    }
    "_MSR_VAR_INIT_START" = "_lc_gb_MSR_VAR_INIT";
    "_MSR_VAR_INIT_END" = ("_lc_ge_MSR_VAR_INIT" == 0) ? 0 : "_lc_ge_MSR_VAR_INIT" - 1;
    "_MSR_VAR_INIT_LIMIT" = "_lc_ge_MSR_VAR_INIT";

    group MSR_VAR_NO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "MSR_VAR_NO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.MSR_VAR_FAST_NO_INIT";
        select "[.]bss.MSR_VAR_NO_INIT";
      }
    }
    "_MSR_VAR_NO_INIT_START" = "_lc_gb_MSR_VAR_NO_INIT";
    "_MSR_VAR_NO_INIT_END" = ("_lc_ge_MSR_VAR_NO_INIT" == 0) ? 0 : "_lc_ge_MSR_VAR_NO_INIT" - 1;
    "_MSR_VAR_NO_INIT_LIMIT" = "_lc_ge_MSR_VAR_NO_INIT";

    "_MSR_VAR_ALL_START" = "_MSR_VAR_CLEARED_START";
    "_MSR_VAR_ALL_END" = "_MSR_VAR_NO_INIT_END";
    "_MSR_VAR_ALL_LIMIT" = "_MSR_VAR_NO_INIT_LIMIT";
  }

  group MSR_VAR_SAVED_ZONE_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group MSR_VAR_SAVED_ZONE_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "MSR_VAR_SAVED_ZONE_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.MSR_VAR_SAVED_ZONE_FAST_INIT";
          select "[.]data.MSR_VAR_SAVED_ZONE_INIT";
        }
      }
    }
    "_MSR_VAR_SAVED_ZONE_INIT_ROM_START" = "_lc_gb_MSR_VAR_SAVED_ZONE_INIT_ROM";
    "_MSR_VAR_SAVED_ZONE_INIT_ROM_LIMIT" = "_lc_ge_MSR_VAR_SAVED_ZONE_INIT_ROM";

  }

  group MSR_VAR_SAVED_ZONE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group MSR_VAR_SAVED_ZONE_INIT (ordered, contiguous, fill, align = 16)
    {
      section "MSR_VAR_SAVED_ZONE_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.MSR_VAR_SAVED_ZONE_FAST_INIT";
        select "[.]data.MSR_VAR_SAVED_ZONE_INIT";
      }
    }
    group MSR_VAR_SAVED_ZONE_INIT_PAD (align = 4)
    {
      reserved "MSR_VAR_SAVED_ZONE_INIT_PAD" (size = 0);
    }
    "_MSR_VAR_SAVED_ZONE_INIT_START" = "_lc_gb_MSR_VAR_SAVED_ZONE_INIT";
    "_MSR_VAR_SAVED_ZONE_INIT_END" = ("_lc_ge_MSR_VAR_SAVED_ZONE_INIT" == 0) ? 0 : "_lc_ge_MSR_VAR_SAVED_ZONE_INIT" - 1;
    "_MSR_VAR_SAVED_ZONE_INIT_LIMIT" = "_lc_ge_MSR_VAR_SAVED_ZONE_INIT";

    group MSR_VAR_SAVED_ZONE_NO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "MSR_VAR_SAVED_ZONE_NO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.MSR_VAR_SAVED_ZONE_FAST_NO_INIT";
        select "[.]bss.MSR_VAR_SAVED_ZONE_NO_INIT";
      }
    }
    "_MSR_VAR_SAVED_ZONE_NO_INIT_START" = "_lc_gb_MSR_VAR_SAVED_ZONE_NO_INIT";
    "_MSR_VAR_SAVED_ZONE_NO_INIT_END" = ("_lc_ge_MSR_VAR_SAVED_ZONE_NO_INIT" == 0) ? 0 : "_lc_ge_MSR_VAR_SAVED_ZONE_NO_INIT" - 1;
    "_MSR_VAR_SAVED_ZONE_NO_INIT_LIMIT" = "_lc_ge_MSR_VAR_SAVED_ZONE_NO_INIT";

    "_MSR_VAR_SAVED_ZONE_ALL_START" = "_MSR_VAR_SAVED_ZONE_INIT_START";
    "_MSR_VAR_SAVED_ZONE_ALL_END" = "_MSR_VAR_SAVED_ZONE_NO_INIT_END";
    "_MSR_VAR_SAVED_ZONE_ALL_LIMIT" = "_MSR_VAR_SAVED_ZONE_NO_INIT_LIMIT";
  }

  group OS_CODE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_CODE (ordered, contiguous, fill)
    {
      section "OS_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_CODE";
        select "[.]text.OS_OS_COREINITHOOK_CODE";
      }
    }
    group OS_CODE_PAD (align = 1)
    {
      reserved "OS_CODE_PAD" (size = 16);
    }
    "_OS_CODE_START" = "_lc_gb_OS_CODE";
    "_OS_CODE_END" = ("_lc_gb_OS_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_CODE_PAD" - 1;
    "_OS_CODE_LIMIT" = "_lc_gb_OS_CODE_PAD";

    "_OS_CODE_ALL_START" = "_OS_CODE_START";
    "_OS_CODE_ALL_END" = "_OS_CODE_END";
    "_OS_CODE_ALL_LIMIT" = "_OS_CODE_LIMIT";
  }

  group OS_CONST_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_CONST (ordered, contiguous, fill)
    {
      section "OS_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_CONST";
        select "[.]zrodata.OS_CONST_FAST";
        select "[.]rodata.OS_CORE0_CONST";
        select "[.]zrodata.OS_CORE0_CONST_FAST";
        select "[.]rodata.OS_SystemApplication_OsCore0_CONST";
        select "[.]zrodata.OS_SystemApplication_OsCore0_CONST_FAST";
      }
    }
    group OS_CONST_PAD (align = 1)
    {
      reserved "OS_CONST_PAD" (size = 16);
    }
    "_OS_CONST_START" = "_lc_gb_OS_CONST";
    "_OS_CONST_END" = ("_lc_gb_OS_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_CONST_PAD" - 1;
    "_OS_CONST_LIMIT" = "_lc_gb_OS_CONST_PAD";

    "_OS_CONST_ALL_START" = "_OS_CONST_START";
    "_OS_CONST_ALL_END" = "_OS_CONST_END";
    "_OS_CONST_ALL_LIMIT" = "_OS_CONST_LIMIT";
  }

  group OS_DATA_CORE0_VAR_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_DATA_CORE0_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_CORE0_VAR_FAST";
          select "[.]zdata.OS_CORE0_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST";
          select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE";
          select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST_SAVED_ZONE";
        }
      }
    }
    "_OS_DATA_CORE0_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_ROM";
    "_OS_DATA_CORE0_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE0_VAR_FAST_INIT_ROM";

    group OS_DATA_CORE0_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_CORE0_VAR";
          select "[.]data.OS_CORE0_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore0_VAR";
          select "[.]data.OS_SystemApplication_OsCore0_VAR_NOCACHE";
          select "[.]data.OS_SystemApplication_OsCore0_VAR_SAVED_ZONE";
        }
      }
    }
    "_OS_DATA_CORE0_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_CORE0_VAR_INIT_ROM";
    "_OS_DATA_CORE0_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_CORE0_VAR_INIT_ROM";

  }

  group OS_DATA_CORE0_VAR_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group OS_DATA_CORE0_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_CORE0_VAR_FAST";
        select "[.]zdata.OS_CORE0_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST";
        select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE";
        select "[.]zdata.OS_SystemApplication_OsCore0_VAR_FAST_SAVED_ZONE";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT";
    "_OS_DATA_CORE0_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_INIT_PAD";

    group OS_DATA_CORE0_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_CORE0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORE0_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore0_VAR_FAST_NOINIT";
        select "[.]zbss.OS_SystemApplication_OsCore0_VAR_FAST_SAVED_ZONE_NOINIT";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT";
    "_OS_DATA_CORE0_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_NOINIT_PAD";

    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT";
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_PAD";

    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss";
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_DATA_CORE0_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_CORE0_VAR";
        select "[.]data.OS_CORE0_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore0_VAR";
        select "[.]data.OS_SystemApplication_OsCore0_VAR_NOCACHE";
        select "[.]data.OS_SystemApplication_OsCore0_VAR_SAVED_ZONE";
      }
    }
    group OS_DATA_CORE0_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_INIT";
    "_OS_DATA_CORE0_VAR_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_INIT_PAD";

    group OS_DATA_CORE0_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_CORE0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORE0_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore0_VAR_NOINIT";
        select "[.]bss.OS_SystemApplication_OsCore0_VAR_SAVED_ZONE_NOINIT";
      }
    }
    group OS_DATA_CORE0_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_CORE0_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_NOINIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_NOINIT";
    "_OS_DATA_CORE0_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_NOINIT_PAD";

    group OS_DATA_CORE0_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_ZERO_INIT";
      }
    }
    group OS_DATA_CORE0_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_ZERO_INIT_START" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT";
    "_OS_DATA_CORE0_VAR_ZERO_INIT_END" = ("_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_PAD" - 1;
    "_OS_DATA_CORE0_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_PAD";

    group OS_DATA_CORE0_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_CORE0_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_SystemApplication_OsCore0_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_SystemApplication_OsCore0_VAR_ZERO_INIT_bss";
      }
    }
    group OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss";
    "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_DATA_CORE0_VAR_ZERO_INIT_bss_PAD";

    "_OS_DATA_CORE0_VAR_ALL_START" = "_OS_DATA_CORE0_VAR_FAST_INIT_START";
    "_OS_DATA_CORE0_VAR_ALL_END" = "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_END";
    "_OS_DATA_CORE0_VAR_ALL_LIMIT" = "_OS_DATA_CORE0_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_DATA_SHARED_VAR_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_DATA_SHARED_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_DATA_SHARED_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_ROM";
    "_OS_DATA_SHARED_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_SHARED_VAR_FAST_INIT_ROM";

    group OS_DATA_SHARED_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_VAR_NOCACHE";
        }
      }
    }
    "_OS_DATA_SHARED_VAR_INIT_ROM_START" = "_lc_gb_OS_DATA_SHARED_VAR_INIT_ROM";
    "_OS_DATA_SHARED_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_DATA_SHARED_VAR_INIT_ROM";

  }

  group OS_DATA_SHARED_VAR_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group OS_DATA_SHARED_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_VAR_FAST_NOCACHE";
      }
    }
    group OS_DATA_SHARED_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_SHARED_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_FAST_INIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT";
    "_OS_DATA_SHARED_VAR_FAST_INIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_INIT_PAD";

    group OS_DATA_SHARED_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_BARRIER_CORE0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_CORESTATUS_CORE0_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_PUBLIC_CORE0_VAR_FAST_NOINIT";
        select "[.]zbss.OS_VAR_FAST_NOCACHE_NOINIT";
      }
    }
    group OS_DATA_SHARED_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_SHARED_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_FAST_NOINIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT";
    "_OS_DATA_SHARED_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_FAST_NOINIT_PAD";

    group OS_DATA_SHARED_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_VAR_NOCACHE";
      }
    }
    group OS_DATA_SHARED_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_DATA_SHARED_VAR_INIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_INIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_INIT";
    "_OS_DATA_SHARED_VAR_INIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_INIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_INIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_INIT_PAD";

    group OS_DATA_SHARED_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_DATA_SHARED_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_BARRIER_CORE0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_CORESTATUS_CORE0_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_PUBLIC_CORE0_VAR_NOINIT";
        select "[.]bss.OS_VAR_NOCACHE_NOINIT";
      }
    }
    group OS_DATA_SHARED_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_DATA_SHARED_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_DATA_SHARED_VAR_NOINIT_START" = "_lc_gb_OS_DATA_SHARED_VAR_NOINIT";
    "_OS_DATA_SHARED_VAR_NOINIT_END" = ("_lc_gb_OS_DATA_SHARED_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_DATA_SHARED_VAR_NOINIT_PAD" - 1;
    "_OS_DATA_SHARED_VAR_NOINIT_LIMIT" = "_lc_gb_OS_DATA_SHARED_VAR_NOINIT_PAD";

    "_OS_DATA_SHARED_VAR_ALL_START" = "_OS_DATA_SHARED_VAR_FAST_INIT_START";
    "_OS_DATA_SHARED_VAR_ALL_END" = "_OS_DATA_SHARED_VAR_NOINIT_END";
    "_OS_DATA_SHARED_VAR_ALL_LIMIT" = "_OS_DATA_SHARED_VAR_NOINIT_LIMIT";
  }

  group OS_EXCVEC_CORE0_CODE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_EXCVEC_CORE0_CODE (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE0_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select ".text.OS_EXCVEC_CORE0_CODE";
      }
    }
    group OS_EXCVEC_CORE0_CODE_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE0_CODE_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE0_CODE_START" = "_lc_gb_OS_EXCVEC_CORE0_CODE";
    "_OS_EXCVEC_CORE0_CODE_END" = ("_lc_gb_OS_EXCVEC_CORE0_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE0_CODE_PAD" - 1;
    "_OS_EXCVEC_CORE0_CODE_LIMIT" = "_lc_gb_OS_EXCVEC_CORE0_CODE_PAD";

    "_OS_EXCVEC_CORE0_CODE_ALL_START" = "_OS_EXCVEC_CORE0_CODE_START";
    "_OS_EXCVEC_CORE0_CODE_ALL_END" = "_OS_EXCVEC_CORE0_CODE_END";
    "_OS_EXCVEC_CORE0_CODE_ALL_LIMIT" = "_OS_EXCVEC_CORE0_CODE_LIMIT";
  }

  group OS_EXCVEC_CORE0_CONST_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_EXCVEC_CORE0_CONST (ordered, contiguous, fill, align = 256)
    {
      section "OS_EXCVEC_CORE0_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select ".rodata.OS_EXCVEC_CORE0_CONST";
      }
    }
    group OS_EXCVEC_CORE0_CONST_PAD (align = 8)
    {
      reserved "OS_EXCVEC_CORE0_CONST_PAD" (size = 16);
    }
    "_OS_EXCVEC_CORE0_CONST_START" = "_lc_gb_OS_EXCVEC_CORE0_CONST";
    "_OS_EXCVEC_CORE0_CONST_END" = ("_lc_gb_OS_EXCVEC_CORE0_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_EXCVEC_CORE0_CONST_PAD" - 1;
    "_OS_EXCVEC_CORE0_CONST_LIMIT" = "_lc_gb_OS_EXCVEC_CORE0_CONST_PAD";

    "_OS_EXCVEC_CORE0_CONST_ALL_START" = "_OS_EXCVEC_CORE0_CONST_START";
    "_OS_EXCVEC_CORE0_CONST_ALL_END" = "_OS_EXCVEC_CORE0_CONST_END";
    "_OS_EXCVEC_CORE0_CONST_ALL_LIMIT" = "_OS_EXCVEC_CORE0_CONST_LIMIT";
  }

  group OS_GLOBALSHARED_CONST_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_GLOBALSHARED_CONST (ordered, contiguous, fill)
    {
      section "OS_GLOBALSHARED_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata.OS_GLOBALSHARED_CONST";
        select "[.]zrodata.OS_GLOBALSHARED_CONST_FAST";
      }
    }
    group OS_GLOBALSHARED_CONST_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_CONST_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_CONST_START" = "_lc_gb_OS_GLOBALSHARED_CONST";
    "_OS_GLOBALSHARED_CONST_END" = ("_lc_gb_OS_GLOBALSHARED_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_CONST_PAD" - 1;
    "_OS_GLOBALSHARED_CONST_LIMIT" = "_lc_gb_OS_GLOBALSHARED_CONST_PAD";

    "_OS_GLOBALSHARED_CONST_ALL_START" = "_OS_GLOBALSHARED_CONST_START";
    "_OS_GLOBALSHARED_CONST_ALL_END" = "_OS_GLOBALSHARED_CONST_END";
    "_OS_GLOBALSHARED_CONST_ALL_LIMIT" = "_OS_GLOBALSHARED_CONST_LIMIT";
  }

  group OS_GLOBALSHARED_VAR_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_GLOBALSHARED_VAR_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_GLOBALSHARED_VAR_FAST";
          select "[.]zdata.OS_GLOBALSHARED_VAR_FAST_NOCACHE";
        }
      }
    }
    "_OS_GLOBALSHARED_VAR_FAST_INIT_ROM_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_ROM";
    "_OS_GLOBALSHARED_VAR_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_GLOBALSHARED_VAR_FAST_INIT_ROM";

    group OS_GLOBALSHARED_VAR_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_GLOBALSHARED_VAR";
          select "[.]data.OS_GLOBALSHARED_VAR_NOCACHE";
        }
      }
    }
    "_OS_GLOBALSHARED_VAR_INIT_ROM_START" = "_lc_gb_OS_GLOBALSHARED_VAR_INIT_ROM";
    "_OS_GLOBALSHARED_VAR_INIT_ROM_LIMIT" = "_lc_ge_OS_GLOBALSHARED_VAR_INIT_ROM";

  }

  group OS_GLOBALSHARED_VAR_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group OS_GLOBALSHARED_VAR_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_GLOBALSHARED_VAR_FAST";
        select "[.]zdata.OS_GLOBALSHARED_VAR_FAST_NOCACHE";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT";
    "_OS_GLOBALSHARED_VAR_FAST_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_INIT_PAD";

    group OS_GLOBALSHARED_VAR_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_GLOBALSHARED_VAR_FAST_NOCACHE_NOINIT";
        select "[.]zbss.OS_GLOBALSHARED_VAR_FAST_NOINIT";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_NOINIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT";
    "_OS_GLOBALSHARED_VAR_FAST_NOINIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_NOINIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_NOINIT_PAD";

    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT";
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_ZERO_INIT";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT";
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_PAD";

    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss";
      }
    }
    group OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_START" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss";
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_PAD";

    group OS_GLOBALSHARED_VAR_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_GLOBALSHARED_VAR";
        select "[.]data.OS_GLOBALSHARED_VAR_NOCACHE";
      }
    }
    group OS_GLOBALSHARED_VAR_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_INIT";
    "_OS_GLOBALSHARED_VAR_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_INIT_PAD";

    group OS_GLOBALSHARED_VAR_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_GLOBALSHARED_VAR_NOCACHE_NOINIT";
        select "[.]bss.OS_GLOBALSHARED_VAR_NOINIT";
      }
    }
    group OS_GLOBALSHARED_VAR_NOINIT_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_VAR_NOINIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_NOINIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_NOINIT";
    "_OS_GLOBALSHARED_VAR_NOINIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_NOINIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_NOINIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_NOINIT_PAD";

    group OS_GLOBALSHARED_VAR_ZERO_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_ZERO_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT";
        select "[.]*.OS_GLOBALSHARED_VAR_ZERO_INIT";
      }
    }
    group OS_GLOBALSHARED_VAR_ZERO_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_ZERO_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT";
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_PAD";

    group OS_GLOBALSHARED_VAR_ZERO_INIT_bss (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_ZERO_INIT_bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]*.OS_GLOBALSHARED_VAR_NOCACHE_ZERO_INIT_bss";
        select "[.]*.OS_GLOBALSHARED_VAR_ZERO_INIT_bss";
      }
    }
    group OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_START" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss";
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_PAD";

    "_OS_GLOBALSHARED_VAR_ALL_START" = "_OS_GLOBALSHARED_VAR_FAST_INIT_START";
    "_OS_GLOBALSHARED_VAR_ALL_END" = "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_END";
    "_OS_GLOBALSHARED_VAR_ALL_LIMIT" = "_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_LIMIT";
  }

  group OS_GLOBALSHARED_VAR_SAVED_ZONE_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata.OS_GLOBALSHARED_VAR_FAST_SAVED_ZONE";
        }
      }
    }
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM_START" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM_LIMIT" = "_lc_ge_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM";

    group OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data.OS_GLOBALSHARED_VAR_SAVED_ZONE";
        }
      }
    }
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM_START" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM_LIMIT" = "_lc_ge_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM";

  }

  group OS_GLOBALSHARED_VAR_SAVED_ZONE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata.OS_GLOBALSHARED_VAR_FAST_SAVED_ZONE";
      }
    }
    group OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_PAD";

    group OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss.OS_GLOBALSHARED_VAR_FAST_SAVED_ZONE_NOINIT";
      }
    }
    group OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_NOINIT_PAD";

    group OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data.OS_GLOBALSHARED_VAR_SAVED_ZONE";
      }
    }
    group OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_PAD (align = 4)
    {
      reserved "OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_PAD";

    group OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT (ordered, contiguous, fill, align = 16)
    {
      section "OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss.OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT";
      }
    }
    group OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_PAD (align = 1)
    {
      reserved "OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_PAD" (size = 16);
    }
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_START" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_END" = ("_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_PAD" == 0) ? 0 : "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_PAD" - 1;
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_LIMIT" = "_lc_gb_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_PAD";

    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_ALL_START" = "_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_START";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_ALL_END" = "_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_END";
    "_OS_GLOBALSHARED_VAR_SAVED_ZONE_ALL_LIMIT" = "_OS_GLOBALSHARED_VAR_SAVED_ZONE_NOINIT_LIMIT";
  }

  group OS_INTVEC_CODE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_INTVEC_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select ".text.OS_INTVEC_CODE";
      }
    }
    group OS_INTVEC_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CODE_START" = "_lc_gb_OS_INTVEC_CODE";
    "_OS_INTVEC_CODE_END" = ("_lc_gb_OS_INTVEC_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CODE_PAD" - 1;
    "_OS_INTVEC_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CODE_PAD";

    "_OS_INTVEC_CODE_ALL_START" = "_OS_INTVEC_CODE_START";
    "_OS_INTVEC_CODE_ALL_END" = "_OS_INTVEC_CODE_END";
    "_OS_INTVEC_CODE_ALL_LIMIT" = "_OS_INTVEC_CODE_LIMIT";
  }

  group OS_INTVEC_CONST_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_INTVEC_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select ".rodata.OS_INTVEC_CONST";
      }
    }
    group OS_INTVEC_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CONST_START" = "_lc_gb_OS_INTVEC_CONST";
    "_OS_INTVEC_CONST_END" = ("_lc_gb_OS_INTVEC_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CONST_PAD" - 1;
    "_OS_INTVEC_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CONST_PAD";

    "_OS_INTVEC_CONST_ALL_START" = "_OS_INTVEC_CONST_START";
    "_OS_INTVEC_CONST_ALL_END" = "_OS_INTVEC_CONST_END";
    "_OS_INTVEC_CONST_ALL_LIMIT" = "_OS_INTVEC_CONST_LIMIT";
  }

  group OS_INTVEC_CORE0_CODE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_INTVEC_CORE0_CODE (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE0_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select ".text.OS_INTVEC_CORE0_CODE";
      }
    }
    group OS_INTVEC_CORE0_CODE_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE0_CODE_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE0_CODE_START" = "_lc_gb_OS_INTVEC_CORE0_CODE";
    "_OS_INTVEC_CORE0_CODE_END" = ("_lc_gb_OS_INTVEC_CORE0_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE0_CODE_PAD" - 1;
    "_OS_INTVEC_CORE0_CODE_LIMIT" = "_lc_gb_OS_INTVEC_CORE0_CODE_PAD";

    "_OS_INTVEC_CORE0_CODE_ALL_START" = "_OS_INTVEC_CORE0_CODE_START";
    "_OS_INTVEC_CORE0_CODE_ALL_END" = "_OS_INTVEC_CORE0_CODE_END";
    "_OS_INTVEC_CORE0_CODE_ALL_LIMIT" = "_OS_INTVEC_CORE0_CODE_LIMIT";
  }

  group OS_INTVEC_CORE0_CONST_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_INTVEC_CORE0_CONST (ordered, contiguous, fill, align = 8192)
    {
      section "OS_INTVEC_CORE0_CONST_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select ".rodata.OS_INTVEC_CORE0_CONST";
      }
    }
    group OS_INTVEC_CORE0_CONST_PAD (align = 8)
    {
      reserved "OS_INTVEC_CORE0_CONST_PAD" (size = 16);
    }
    "_OS_INTVEC_CORE0_CONST_START" = "_lc_gb_OS_INTVEC_CORE0_CONST";
    "_OS_INTVEC_CORE0_CONST_END" = ("_lc_gb_OS_INTVEC_CORE0_CONST_PAD" == 0) ? 0 : "_lc_gb_OS_INTVEC_CORE0_CONST_PAD" - 1;
    "_OS_INTVEC_CORE0_CONST_LIMIT" = "_lc_gb_OS_INTVEC_CORE0_CONST_PAD";

    "_OS_INTVEC_CORE0_CONST_ALL_START" = "_OS_INTVEC_CORE0_CONST_START";
    "_OS_INTVEC_CORE0_CONST_ALL_END" = "_OS_INTVEC_CORE0_CONST_END";
    "_OS_INTVEC_CORE0_CONST_ALL_LIMIT" = "_OS_INTVEC_CORE0_CONST_LIMIT";
  }

  group OS_USER_CODE_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group OS_USER_CODE (ordered, contiguous, fill)
    {
      section "OS_USER_CODE_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text.OS_CanIsr_0_CODE";
        select "[.]text.OS_Default_Init_Task_CODE";
        select "[.]text.OS_Default_Init_Task_Trusted_CODE";
        select "[.]text.OS_ERRORHOOK_CODE";
        select "[.]text.OS_OsTask_MainFunction_CODE";
      }
    }
    group OS_USER_CODE_PAD (align = 1)
    {
      reserved "OS_USER_CODE_PAD" (size = 16);
    }
    "_OS_USER_CODE_START" = "_lc_gb_OS_USER_CODE";
    "_OS_USER_CODE_END" = ("_lc_gb_OS_USER_CODE_PAD" == 0) ? 0 : "_lc_gb_OS_USER_CODE_PAD" - 1;
    "_OS_USER_CODE_LIMIT" = "_lc_gb_OS_USER_CODE_PAD";

    "_OS_USER_CODE_ALL_START" = "_OS_USER_CODE_START";
    "_OS_USER_CODE_ALL_END" = "_OS_USER_CODE_END";
    "_OS_USER_CODE_ALL_LIMIT" = "_OS_USER_CODE_LIMIT";
  }

  group STACK_C0_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:StartupStack_Shared)
  {
    group STACK_C0 (ordered, contiguous, fill, align = 64)
    {
      reserved "STACK_C0" (size = 36864);
    }
    group STACK_C0_PAD (align = 4)
    {
      reserved "STACK_C0_PAD" (size = 0);
    }
    "_STACK_C0_START" = "_lc_gb_STACK_C0";
    "_STACK_C0_END" = ("_lc_ge_STACK_C0" == 0) ? 0 : "_lc_ge_STACK_C0" - 1;
    "_STACK_C0_LIMIT" = "_lc_ge_STACK_C0";

    "_STACK_C0_ALL_START" = "_STACK_C0_START";
    "_STACK_C0_ALL_END" = "_STACK_C0_END";
    "_STACK_C0_ALL_LIMIT" = "_STACK_C0_LIMIT";
  }

  "StartupEntry" = "brsStartupEntry";
  "_start_tc0" = "brsStartupEntry";
  "_start_tc1" = "brsStartupEntry";
  "_start_tc2" = "brsStartupEntry";
  "_start_tc3" = "brsStartupEntry";
  "_start_tc4" = "brsStartupEntry";
  "_start_tc5" = "brsStartupEntry";

  group Const_Default_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group rodata (ordered, contiguous, fill)
    {
      section "rodata_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]rodata*";
      }
    }
    "_rodata_START" = "_lc_gb_rodata";
    "_rodata_END" = ("_lc_ge_rodata" == 0) ? 0 : "_lc_ge_rodata" - 1;
    "_rodata_LIMIT" = "_lc_ge_rodata";

    group text (ordered, contiguous, fill)
    {
      section "text_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]text*";
      }
    }
    "_text_START" = "_lc_gb_text";
    "_text_END" = ("_lc_ge_text" == 0) ? 0 : "_lc_ge_text" - 1;
    "_text_LIMIT" = "_lc_ge_text";

    group zrodata (ordered, contiguous, fill)
    {
      section "zrodata_SEC" (fill, blocksize = 2, attributes = rx)
      {
        select "[.]zrodata*";
      }
    }
    "_zrodata_START" = "_lc_gb_zrodata";
    "_zrodata_END" = ("_lc_ge_zrodata" == 0) ? 0 : "_lc_ge_zrodata" - 1;
    "_zrodata_LIMIT" = "_lc_ge_zrodata";

    "_Const_Default_ALL_START" = "_rodata_START";
    "_Const_Default_ALL_END" = "_zrodata_END";
    "_Const_Default_ALL_LIMIT" = "_zrodata_LIMIT";
  }

  group Data_Default_ROM_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:PFlash0_Cached)
  {
    group data_ROM (ordered, contiguous, fill, align = 16)
    {
      section "data_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]data*";
        }
      }
    }
    "_data_ROM_START" = "_lc_gb_data_ROM";
    "_data_ROM_LIMIT" = "_lc_ge_data_ROM";

    group zdata_ROM (ordered, contiguous, fill, align = 16)
    {
      section "zdata_ROM_SEC" (fill, blocksize = 2, attributes = rx)
      {
        group (load_addr)
        {
          select "[.]zdata*";
        }
      }
    }
    "_zdata_ROM_START" = "_lc_gb_zdata_ROM";
    "_zdata_ROM_LIMIT" = "_lc_ge_zdata_ROM";

  }

  group Data_Default_GROUP (ordered, contiguous, fill, run_addr = mem:mpe:DSPR_Core0)
  {
    group bss (ordered, contiguous, fill, align = 16)
    {
      section "bss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]bss*";
      }
    }
    group bss_PAD (align = 4)
    {
      reserved "bss_PAD" (size = 0);
    }
    "_bss_START" = "_lc_gb_bss";
    "_bss_END" = ("_lc_ge_bss" == 0) ? 0 : "_lc_ge_bss" - 1;
    "_bss_LIMIT" = "_lc_ge_bss";

    group data (ordered, contiguous, fill, align = 16)
    {
      section "data_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]data*";
      }
    }
    group data_PAD (align = 4)
    {
      reserved "data_PAD" (size = 0);
    }
    "_data_START" = "_lc_gb_data";
    "_data_END" = ("_lc_ge_data" == 0) ? 0 : "_lc_ge_data" - 1;
    "_data_LIMIT" = "_lc_ge_data";

    group zbss (ordered, contiguous, fill, align = 16)
    {
      section "zbss_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zbss*";
      }
    }
    group zbss_PAD (align = 4)
    {
      reserved "zbss_PAD" (size = 0);
    }
    "_zbss_START" = "_lc_gb_zbss";
    "_zbss_END" = ("_lc_ge_zbss" == 0) ? 0 : "_lc_ge_zbss" - 1;
    "_zbss_LIMIT" = "_lc_ge_zbss";

    group zdata (ordered, contiguous, fill, align = 16)
    {
      section "zdata_SEC" (blocksize = 2, attributes = rw)
      {
        select "[.]zdata*";
      }
    }
    group zdata_PAD (align = 4)
    {
      reserved "zdata_PAD" (size = 0);
    }
    "_zdata_START" = "_lc_gb_zdata";
    "_zdata_END" = ("_lc_ge_zdata" == 0) ? 0 : "_lc_ge_zdata" - 1;
    "_zdata_LIMIT" = "_lc_ge_zdata";

    "_Data_Default_ALL_START" = "_bss_START";
    "_Data_Default_ALL_END" = "_zdata_END";
    "_Data_Default_ALL_LIMIT" = "_zdata_LIMIT";
  }

}


