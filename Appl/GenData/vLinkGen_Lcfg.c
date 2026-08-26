/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: vLinkGen
 *           Program: MSR_Vector_SLP4
 *          Customer: China Lithium Battery Technology Co., Ltd.
 *       Expiry Date: 2025-08-26
 *  Ordered Derivat.: SAK-TC387QP-160F300S AE
 *    License Scope : The usage is restricted to CBD2200508_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: vLinkGen_Lcfg.c
 *   Generation Time: 2026-08-20 16:34:00
 *           Project: last364 - Version 1.0
 *          Delivery: CBD2200508_D00
 *      Tool Version: DaVinci Configurator Classic (beta) 5.25.37 SP2
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 ! BETA VERSION                                                                                                       !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 ! This version of DaVinci Configurator Classic and/or the related Basic Software Package is BETA software.               !
 ! BETA Software is basically operable, but not sufficiently tested, verified and/or qualified for use in series      !
 ! production and/or in vehicles operating on public or non-public roads.                                             !
 ! In particular, without limitation, BETA Software may cause unpredictable ECU behavior, may not provide all         !
 ! functions necessary for use in series production and/or may not comply with quality requirements which are         !
 ! necessary according to the state of the art. BETA Software must not be used in series production.                  !
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  EXAMPLE CODE ONLY
 *  -------------------------------------------------------------------------------------------------------------------
 *  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
 *  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
 *  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
 *  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
 *  according to the state of the art before their use.
 *********************************************************************************************************************/

#define VLINKGEN_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "vLinkGen_Lcfg.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/* Memory region blocks to be initialized with zeros in stage Early */
const vLinkGen_MemArea vLinkGen_ZeroInit_Early_Blocks[VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Memory region blocks to be initialized with zeros in stage One */
const vLinkGen_MemArea vLinkGen_ZeroInit_One_Blocks[VLINKGEN_CFG_NUM_ZERO_INIT_ONE_BLOCKS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Memory region blocks to be initialized with zeros in stage HardReset */
const vLinkGen_MemArea vLinkGen_ZeroInit_HardReset_Blocks[VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_BLOCKS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with zeros in stage Early */
const vLinkGen_MemArea vLinkGen_ZeroInit_Early_Groups[VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with zeros in stage Zero */
const vLinkGen_MemArea vLinkGen_ZeroInit_Zero_Groups[VLINKGEN_CFG_NUM_ZERO_INIT_ZERO_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with zeros in stage One */
const vLinkGen_MemArea vLinkGen_ZeroInit_One_Groups[VLINKGEN_CFG_NUM_ZERO_INIT_ONE_GROUPS] =
{
  { /*  MSR_VAR_CLEARED  */ 
     /*  .Start  */ (uint32)_MSR_VAR_CLEARED_START, 
     /*  .End  */ (uint32)_lc_ge_MSR_VAR_CLEARED, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_CORE0_VAR_FAST_ZERO_INIT  */ 
     /*  .Start  */ (uint32)_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_CORE0_VAR_FAST_ZERO_INIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss  */ 
     /*  .Start  */ (uint32)_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_CORE0_VAR_FAST_ZERO_INIT_bss, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_CORE0_VAR_ZERO_INIT  */ 
     /*  .Start  */ (uint32)_OS_DATA_CORE0_VAR_ZERO_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_CORE0_VAR_ZERO_INIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_CORE0_VAR_ZERO_INIT_bss  */ 
     /*  .Start  */ (uint32)_OS_DATA_CORE0_VAR_ZERO_INIT_bss_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_CORE0_VAR_ZERO_INIT_bss, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_FAST_ZERO_INIT  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_FAST_ZERO_INIT_bss, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_ZERO_INIT  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_ZERO_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_ZERO_INIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_ZERO_INIT_bss  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_ZERO_INIT_bss_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_ZERO_INIT_bss, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  bss  */ 
     /*  .Start  */ (uint32)_bss_START, 
     /*  .End  */ (uint32)_lc_ge_bss, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  zbss  */ 
     /*  .Start  */ (uint32)_zbss_START, 
     /*  .End  */ (uint32)_lc_ge_zbss, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with zeros in stage Two */
const vLinkGen_MemArea vLinkGen_ZeroInit_Two_Groups[VLINKGEN_CFG_NUM_ZERO_INIT_TWO_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with zeros in stage Three */
const vLinkGen_MemArea vLinkGen_ZeroInit_Three_Groups[VLINKGEN_CFG_NUM_ZERO_INIT_THREE_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with zeros in stage HardReset */
const vLinkGen_MemArea vLinkGen_ZeroInit_HardReset_Groups[VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with concrete data in stage Zero */
const vLinkGen_RamMemArea vLinkGen_Init_Zero_Groups[VLINKGEN_CFG_NUM_INIT_ZERO_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with concrete data in stage One */
const vLinkGen_RamMemArea vLinkGen_Init_One_Groups[VLINKGEN_CFG_NUM_INIT_ONE_GROUPS] =
{
  { /*  FlsLoader_WriteErase  */ 
     /*  .Start  */ (uint32)_FlsLoader_WriteErase_START, 
     /*  .End  */ (uint32)_lc_ge_FlsLoader_WriteErase, 
     /*  .Romstart  */ (uint32)_FlsLoader_WriteErase_ROM_START, 
     /*  .Romend  */ (uint32)_FlsLoader_WriteErase_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  MSR_PBCFG_VAR_INIT  */ 
     /*  .Start  */ (uint32)_MSR_PBCFG_VAR_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_MSR_PBCFG_VAR_INIT, 
     /*  .Romstart  */ (uint32)_MSR_PBCFG_VAR_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_MSR_PBCFG_VAR_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  MSR_VAR_INIT  */ 
     /*  .Start  */ (uint32)_MSR_VAR_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_MSR_VAR_INIT, 
     /*  .Romstart  */ (uint32)_MSR_VAR_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_MSR_VAR_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  MSR_VAR_SAVED_ZONE_INIT  */ 
     /*  .Start  */ (uint32)_MSR_VAR_SAVED_ZONE_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_MSR_VAR_SAVED_ZONE_INIT, 
     /*  .Romstart  */ (uint32)_MSR_VAR_SAVED_ZONE_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_MSR_VAR_SAVED_ZONE_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_CORE0_VAR_FAST_INIT  */ 
     /*  .Start  */ (uint32)_OS_DATA_CORE0_VAR_FAST_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_CORE0_VAR_FAST_INIT, 
     /*  .Romstart  */ (uint32)_OS_DATA_CORE0_VAR_FAST_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_DATA_CORE0_VAR_FAST_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_CORE0_VAR_INIT  */ 
     /*  .Start  */ (uint32)_OS_DATA_CORE0_VAR_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_CORE0_VAR_INIT, 
     /*  .Romstart  */ (uint32)_OS_DATA_CORE0_VAR_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_DATA_CORE0_VAR_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_SHARED_VAR_FAST_INIT  */ 
     /*  .Start  */ (uint32)_OS_DATA_SHARED_VAR_FAST_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_SHARED_VAR_FAST_INIT, 
     /*  .Romstart  */ (uint32)_OS_DATA_SHARED_VAR_FAST_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_DATA_SHARED_VAR_FAST_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_DATA_SHARED_VAR_INIT  */ 
     /*  .Start  */ (uint32)_OS_DATA_SHARED_VAR_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_DATA_SHARED_VAR_INIT, 
     /*  .Romstart  */ (uint32)_OS_DATA_SHARED_VAR_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_DATA_SHARED_VAR_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_FAST_INIT  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_FAST_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_FAST_INIT, 
     /*  .Romstart  */ (uint32)_OS_GLOBALSHARED_VAR_FAST_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_GLOBALSHARED_VAR_FAST_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_INIT  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_INIT, 
     /*  .Romstart  */ (uint32)_OS_GLOBALSHARED_VAR_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_GLOBALSHARED_VAR_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT, 
     /*  .Romstart  */ (uint32)_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_GLOBALSHARED_VAR_SAVED_ZONE_FAST_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT  */ 
     /*  .Start  */ (uint32)_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_START, 
     /*  .End  */ (uint32)_lc_ge_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT, 
     /*  .Romstart  */ (uint32)_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM_START, 
     /*  .Romend  */ (uint32)_OS_GLOBALSHARED_VAR_SAVED_ZONE_INIT_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  data  */ 
     /*  .Start  */ (uint32)_data_START, 
     /*  .End  */ (uint32)_lc_ge_data, 
     /*  .Romstart  */ (uint32)_data_ROM_START, 
     /*  .Romend  */ (uint32)_data_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  { /*  zdata  */ 
     /*  .Start  */ (uint32)_zdata_START, 
     /*  .End  */ (uint32)_lc_ge_zdata, 
     /*  .Romstart  */ (uint32)_zdata_ROM_START, 
     /*  .Romend  */ (uint32)_zdata_ROM_LIMIT, 
     /*  .Core  */ 0u, 
     /*  .Alignment  */ 0u
  }, 
  {
    0u, 
    0u, 
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with concrete data in stage Two */
const vLinkGen_RamMemArea vLinkGen_Init_Two_Groups[VLINKGEN_CFG_NUM_INIT_TWO_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with concrete data in stage Three */
const vLinkGen_RamMemArea vLinkGen_Init_Three_Groups[VLINKGEN_CFG_NUM_INIT_THREE_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Section groups to be initialized with concrete data in stage HardReset */
const vLinkGen_RamMemArea vLinkGen_Init_HardReset_Groups[VLINKGEN_CFG_NUM_INIT_HARD_RESET_GROUPS] =
{
  {
    0u, 
    0u, 
    0u, 
    0u, 
    0u, 
    0u
  }
};

/* Memory region blocks to be initialized with zeros in stage Early */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_Early_BlocksSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_BLOCKS, 
  vLinkGen_ZeroInit_Early_Blocks
};

/* Memory region blocks to be initialized with zeros in stage One */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_One_BlocksSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_ONE_BLOCKS, 
  vLinkGen_ZeroInit_One_Blocks
};

/* Memory region blocks to be initialized with zeros in stage HardReset */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_HardReset_BlocksSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_BLOCKS, 
  vLinkGen_ZeroInit_HardReset_Blocks
};

/* Section groups to be initialized with zeros in stage Early */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_Early_GroupsSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_EARLY_GROUPS, 
  vLinkGen_ZeroInit_Early_Groups
};

/* Section groups to be initialized with zeros in stage Zero */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_Zero_GroupsSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_ZERO_GROUPS, 
  vLinkGen_ZeroInit_Zero_Groups
};

/* Section groups to be initialized with zeros in stage One */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_One_GroupsSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_ONE_GROUPS, 
  vLinkGen_ZeroInit_One_Groups
};

/* Section groups to be initialized with zeros in stage Two */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_Two_GroupsSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_TWO_GROUPS, 
  vLinkGen_ZeroInit_Two_Groups
};

/* Section groups to be initialized with zeros in stage Three */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_Three_GroupsSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_THREE_GROUPS, 
  vLinkGen_ZeroInit_Three_Groups
};

/* Section groups to be initialized with zeros in stage HardReset */
const vLinkGen_MemAreaSet vLinkGen_ZeroInit_HardReset_GroupsSet =
{
  VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_GROUPS, 
  vLinkGen_ZeroInit_HardReset_Groups
};

/* Section groups to be initialized with concrete data in stage Zero */
const vLinkGen_RamMemAreaSet vLinkGen_Init_Zero_GroupsSet =
{
  VLINKGEN_CFG_NUM_INIT_ZERO_GROUPS, 
  vLinkGen_Init_Zero_Groups
};

/* Section groups to be initialized with concrete data in stage One */
const vLinkGen_RamMemAreaSet vLinkGen_Init_One_GroupsSet =
{
  VLINKGEN_CFG_NUM_INIT_ONE_GROUPS, 
  vLinkGen_Init_One_Groups
};

/* Section groups to be initialized with concrete data in stage Two */
const vLinkGen_RamMemAreaSet vLinkGen_Init_Two_GroupsSet =
{
  VLINKGEN_CFG_NUM_INIT_TWO_GROUPS, 
  vLinkGen_Init_Two_Groups
};

/* Section groups to be initialized with concrete data in stage Three */
const vLinkGen_RamMemAreaSet vLinkGen_Init_Three_GroupsSet =
{
  VLINKGEN_CFG_NUM_INIT_THREE_GROUPS, 
  vLinkGen_Init_Three_Groups
};

/* Section groups to be initialized with concrete data in stage HardReset */
const vLinkGen_RamMemAreaSet vLinkGen_Init_HardReset_GroupsSet =
{
  VLINKGEN_CFG_NUM_INIT_HARD_RESET_GROUPS, 
  vLinkGen_Init_HardReset_Groups
};

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  END OF FILE: vLinkGen_Lcfg.c
 *********************************************************************************************************************/
