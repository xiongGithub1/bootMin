/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                Please note, that this file contains example configuration used by the 
 *                MICROSAR BSW. This code may influence the behaviour of the MICROSAR BSW
 *                in principle. Therefore, great care must be taken to verify
 *                the correctness of the implementation.
 *
 *                The contents of the originally delivered files are only examples respectively
 *                implementation proposals. With regard to the fact that these functions
 *                are meant for demonstration purposes only, the liability of Vector Informatik
 *                shall be expressly excluded in cases of ordinary negligence, 
 *                to the extent admissible by law or statute.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  _MemMap.h
 *    Component:  -
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  This File is a template for the MemMap.h
 *                This file has to be extended with the memory section defined for all BSW modules
 *                which are used.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2007-08-01  Jk                    Initial creation
 *  01.01.00  2007-12-14  Jk                    Component specific defines filtering added
 *  01.01.02  2008-11-04  Jk                    Component specific defines filtering added
 *  01.01.03  2008-12-17  Ht                    Improve list of components  (Tp_AsrTpCan,Tp_AsrTpFr,DrvMcu,DrvIcu added)
 *  01.01.04  2009-04-27  Ht                    improve list of components  (Cp_XcpOnCanAsr, Il_AsrIpduM, If_VxFblDcm,
 *                                              If_VxFblVpm_Volvo_ab, DrvFls added)
 *  01.01.05  2009-04-24  Msr                   Renamed J1939_AsrBase as TpJ1939_AsrBase
 *  01.01.06  2009-06-03  Ht                    Improve list of components (Adc, Dio, Gpt, Pwm, Spi, Wdg, Fls, Port, Fim)
 *  01.02.00  2009-08-01  Ht                    Improve list of components (Fee_30_Inst2, Can, ...Sub)
 *                                              Support filtering for RTE
 *  01.02.01  2009-08-18  HH                    replaced C++ comment by C comment
 *  01.02.02  2009-09-02  Lo                    add external Flash driver support
 *  01.02.03  2009-09-12  Lo                    add DrvFls_Mcs12xFslftm01ExtVx
 *                        Ht                    Improve list of components (CanTrcv_30_Tja1040dio,
 *                                                Eth, EthTrcv, EthIf, SoAd, TcpIp, EthSM)
 *  01.03.00  2009-10-30  Ht                    support R8: change EthTrcv to EthTrcv_30_Canoeemu
 *                                              support EthTrcv_30_Dp83848
 *                                              change CanTrcv_30_Xdio to CanTrcv_30___Your_Trcv__
 *                                              change CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1041
 *                                              change name FrTrcv to FrTrcv_30_Tja1080dio
 *                        Lo                    add Cp_AsrXcp
 *                        Ht                    add Cp_XcpOnFrAsr
 *  01.03.01  2010-01-13  Ht                    support SysService_AsrCal
 *  01.03.02  2010-02-15  Ht                    support SysService_SswRcs_Daimler, SysService_Tls, Tp_Http, 
 *                                                      SysService_Dns, SysService_Json, DrvTrans_GenericLindioAsr
 *                        Lo                    add Diag_AsrDem for all OEMs
 *                                              rename internal variables and filter methods
 *  01.04.00  2010-03-04  Ht                    change name FrTrcv_30_Tja1080dio to FrTrcv_30_Tja1080
 *  01.04.01  2010-03-10  Ht                    support DrvTrans_GenericFrAsr, DrvTrans_As8223FrspiAsr, DrvEep and If_AsrIfEa
 *  01.04.02  2010-04-07  Lo                    change IfFee to real components and add If_AsrIfWdV85xNec01Sub
 *  01.04.03  2010-06-11  Ht                    add CanTrcv_30_Tja1043
 *                        Lo                    add Il_AsrIpduMEbBmwSub
 *  01.04.04  2010-08-24  Ht                    add CanTrcv_30_Tle62512G, DrvEep_XAt25128EAsr, Tp_AsrTpFrEbBmwSub
 *  01.05.00  2010-08-24  Ht                    support R10:
 *                                              change LinTrcv_30_Tle7259dio to LinTrcv_30_Tle7259
 *  01.05.01  2010-10-14  Ht                    add VStdLib, SysService_SswScc, SysService_IpBase, SysService_Crypto
 *  01.05.02  2010-10-20  Ht                    support comments for Package Merge Tool
 *  01.05.03  2010-11-03  Ht                    add SysService_E2eLibTttechSub, SysService_E2ePwTttechSub
 *  01.05.04  2010-11-16  Ht                    add SysService_Exi, DrvTrans_Int6400EthAsr, Cdd_AsrCdd_Fiat, Diag_AsrDem_Fiat
 *  01.05.05  2010-12-17  Ht                    add SysService_AsrSchM, DrvEep_XXStubAsr, DrvIcu_Tms570Tinhet01ExtVx
 *                                                  DrvWd_XTle4278gEAsr, DrvWd_XXStubAsr
 *  01.05.06  2011-02-17  Ht                    add DrvEed, SysService_AsrBswM
 *  01.05.07  2011-03-04  Ht                    add DrvTrans_Tja1055CandioAsr
 *                                              rename CanTrcv_30_Tja1040dio to CanTrcv_30_Tja1040
 *                                              add SysService_XmlEngine
 *  01.06.00  2011-03-15  Ht                    support ASR4.0
 *                                              add Ccl_Asr4ComM, Ccl_Asr4SmCan, Nm_Asr4NmIf, Nm_AsrNmDirOsek
 *  01.06.01  2011-04-15  Ht                    add Diag_AsrDcm_<OEM>
 *  01.06.02  2011-06-17  Ht                    correct Diag_AsrDcm_<OEM>
 *                                              add Monitoring_AsrDlt and Monitoring_GenericMeasurement
 *  01.06.03  2011-09-20  Ht                    add DrvTrans_Tja1145CanSpiAsr, DrvTrans_E52013CanspiAsr, DrvFls_XXStubAsr,
 *                                              If_AsrIfFeeV85xNec05Sub, If_AsrIfFeeV85xNec06Sub, If_AsrIfFeeV85xNec07Sub
 *                                              SysService_AsrWdMTttechSub and If_AsrIfWdTttechSub
 *  01.06.04  2011-11-22  Ht                    add If_AsrIfFeeTiSub, 
 *                                              ESCAN00054718: add Cdd_AsrCdd
 *  01.06.05  2011-12-09  Ht                    add Tp_IpV4, Tp_IpV6
 *  01.06.06  2011-12-14  Ht                    add Monitoring_RuntimeMeasurement
 *  01.06.07  2012-01-03  Ht                    add DrvI2c, SysService_Asr4BswM
 *  01.06.08  2012-01-31  Ht                    add DrvTrans_Ar7000EthAsr, DrvTrans_GenericEthmiiAsr
 *  01.06.09  2012-03-06  Ht                    add If_AsrIfFeeMb9df126Fuji01Sub, 
 *                                              Infineon_Tc1767Inf01Sub, Infineon_Tc178xInf01Sub, Infineon_Tc1797Inf01Sub, Infineon_Tc1797Inf02Sub
 *  01.06.10  2012-03-13  Ht                    add Gw_AsrPduRCfg5, Il_AsrComCfg5, Il_AsrIpduMCfg5, Cdd_AsrCddCfg5,
 *                                              Tp_Asr4TpCan, Diag_Asr4Dcm, Diag_Asr4Dem
 *  01.06.11  2012-03-20  Ht                    add Cp_AsrCcp, Cp_XcpOnTcpIpAsr
 *  01.07.00  2012-07-26  Ht                    ESCAN00059365: [AUTOSAR4, compiler warning]: Wrong define name in #undef statement causes re-definition warning
 *                                              add Nm_Asr4NmCan, Nm_Asr4NmFr, Infineon_Xc2000Inf01Sub, Ccl_Asr4ComMCfg5, SysService_Asr4BswMCfg5, SysService_Asr4EcuM, SysService_AsrRamTst,
 *                                                  Ccl_Asr4SmLin 
 *            2012-09-04  Ht                    add support for ASR specification 4.0 R3
 *  01.07.01  2012-10-23  Seu                   add SysService_XmlSecurity
 *  01.07.02  2013-01-10  Seu                   MISRA deviation comments added
 *  01.08.00  2013-03-01  Seu    ESCAN00065501  AR4-325: Add support for Post-build RAM memory section
 *            2013-04-12  Seu    ESCAN00066614  Add the deviation for violation of MISRA rule 19.6
 *  01.09.00  2013-12-10  Seu    ESCAN00072537  Add *_NOCACHE_* memory sections for variables
 *            2013-12-16  Seu                   MISRA compliance: usage of character "'" removed, typos corrected
 *  01.10.00  2016-09-27  Seu                   FEATC-317: FEAT-2002: CommonAsr__Common: Support 64 Bit Signal Types for COM according to ASR 4.2.2
 *  01.11.00  2017-07-05  Seu    ESCAN00095756  FEAT-2455: Support ASR4.2 compatible MemMap for MCALs
 *            2017-08-01  Seu    ESCAN00096129  MEMMAP_SW_MINOR_VERSION / MEM_SW_MINOR_VERSION is not correct
 *  01.12.00  2018-10-17  visdfe ESCAN00095695  Add support for Os_CoreGen7 within _MemMap.h (Include of Os_MemMap.h)
 *                               TASK-78775     Change MemMap_Common.h to Template
 *  01.13.00  2021-05-06  virmfr HALBE-3985     CommonAsr_MemMap shall include Common_MemMap generated compatibility header
 *  02.00.00  2021-06-09  visto  HALBE-4594     Create a branch for >=R27 Features
 *  02.01.00  2021-08-25  virmfr HALBE-4526     MemMap_Common.h removed
 *  02.01.01  2021-09-07  virmfr HALBE-5304     MemMapIncludesList removed
 *********************************************************************************************************************/

/* PRQA S 0841 MEMMAP_0841_TAG */ /* MD_MSR_19.6 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

 /* PRQA S 0883 1 */ /* MD_MemMap_19.15 */
#undef MEMMAP_VENDOR_ID /* PRQA S 0841 */ /* MD_MSR_19.6 */

#define MEMMAP_VENDOR_ID        (30u)

/* AUTOSAR Software Specification Version Information */


# undef MEMMAP_AR_RELEASE_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_AR_RELEASE_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_AR_RELEASE_REVISION_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

/* AUTOSAR release 4.0 R3 */
# define MEMMAP_AR_RELEASE_MAJOR_VERSION       (4u)
# define MEMMAP_AR_RELEASE_MINOR_VERSION       (0u)
# define MEMMAP_AR_RELEASE_REVISION_VERSION    (3u)

/* compatiblity to older versions */
# undef MEM_AR_RELEASE_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_AR_RELEASE_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_AR_RELEASE_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEM_AR_RELEASE_MAJOR_VERSION          MEMMAP_AR_RELEASE_MAJOR_VERSION
# define MEM_AR_RELEASE_MINOR_VERSION          MEMMAP_AR_RELEASE_MINOR_VERSION
# define MEM_AR_RELEASE_PATCH_VERSION          MEMMAP_AR_RELEASE_REVISION_VERSION


# undef MEMMAP_SW_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_SW_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEMMAP_SW_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEMMAP_SW_MAJOR_VERSION     (2u)
# define MEMMAP_SW_MINOR_VERSION     (1u)
# define MEMMAP_SW_PATCH_VERSION     (1u)

/* compatiblity to older versions */
# undef MEM_SW_MAJOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_SW_MINOR_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */
# undef MEM_SW_PATCH_VERSION /* PRQA S 0841 */ /* MD_MSR_19.6 */

# define MEM_SW_MAJOR_VERSION        MEMMAP_SW_MAJOR_VERSION 
# define MEM_SW_MINOR_VERSION        MEMMAP_SW_MINOR_VERSION 
# define MEM_SW_PATCH_VERSION        MEMMAP_SW_PATCH_VERSION 
  
#define MEMMAP_ERROR

/* Package Merger: Start Section MemMapModuleList */



/**********************************************************************************************************************
 *  CanSM START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANSM_START_SEC_CODE
# undef CANSM_START_SEC_CODE
# define START_SEC_CODE                                               /* mapped to default code section */
#endif

#ifdef CANSM_STOP_SEC_CODE
# undef CANSM_STOP_SEC_CODE
# define STOP_SEC_CODE                                                /* default code stop section */
#endif


#ifdef CANSM_START_SEC_APPL_CODE
# undef CANSM_START_SEC_APPL_CODE
# define START_SEC_CODE                                               /* mapped to default code section */
#endif

#ifdef CANSM_STOP_SEC_APPL_CODE
# undef CANSM_STOP_SEC_APPL_CODE
# define STOP_SEC_CODE                                                /* default code stop section */
#endif
 


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */


#ifdef CANSM_START_SEC_CONST_8BIT
# undef CANSM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_8BIT
# undef CANSM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST                                               /* default const stop section */
#endif

#ifdef CANSM_START_SEC_CONST_32BIT
# undef CANSM_START_SEC_CONST_32BIT
# define START_SEC_CONST_32BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_32BIT
# undef CANSM_STOP_SEC_CONST_32BIT
# define STOP_SEC_CONST
#endif


#ifdef CANSM_START_SEC_CONST_UNSPECIFIED
# undef CANSM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CANSM_STOP_SEC_CONST_UNSPECIFIED
# undef CANSM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */
#ifdef CANSM_START_SEC_CONST_FAST_8BIT
# undef CANSM_START_SEC_CONST_FAST_8BIT
# define START_SEC_CONST_FAST_8BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_FAST_8BIT
# undef CANSM_STOP_SEC_CONST_FAST_8BIT
# define STOP_SEC_CONST                                               /* default const stop section */
#endif

#ifdef CANSM_START_SEC_CONST_FAST_32BIT
# undef CANSM_START_SEC_CONST_FAST_32BIT
# define START_SEC_CONST_FAST_32BIT
#endif

#ifdef CANSM_STOP_SEC_CONST_FAST_32BIT
# undef CANSM_STOP_SEC_CONST_FAST_32BIT
# define STOP_SEC_CONST
#endif


#ifdef CANSM_START_SEC_CONST_FAST_UNSPECIFIED
# undef CANSM_START_SEC_CONST_FAST_UNSPECIFIED
# define START_SEC_CONST_FAST_UNSPECIFIED
#endif

#ifdef CANSM_STOP_SEC_CONST_FAST_UNSPECIFIED
# undef CANSM_STOP_SEC_CONST_FAST_UNSPECIFIED
# define STOP_SEC_CONST
#endif



/* Postbuild CFG CONST sections */



/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */


/* VAR NOINIT sections */

#ifdef CANSM_START_SEC_VAR_NOINIT_8BIT
# undef CANSM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif

#ifdef CANSM_STOP_SEC_VAR_NOINIT_8BIT
# undef CANSM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif


#ifdef CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#ifdef CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef CANSM_START_SEC_VAR_ZERO_INIT_8BIT
# undef CANSM_START_SEC_VAR_ZERO_INIT_8BIT
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef CANSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef CANSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif

/* VAR FAST INIT sections */

/* VAR FAST NOINIT sections */

#ifdef CANSM_START_SEC_VAR_FAST_NOINIT_8BIT
# undef CANSM_START_SEC_VAR_FAST_NOINIT_8BIT
# define START_SEC_VAR_FAST_NOINIT_8BIT
#endif

#ifdef CANSM_STOP_SEC_VAR_FAST_NOINIT_8BIT
# undef CANSM_STOP_SEC_VAR_FAST_NOINIT_8BIT
# define STOP_SEC_VAR
#endif


#ifdef CANSM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef CANSM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif

#ifdef CANSM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef CANSM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR FAST ZERO INIT sections */

#ifdef CANSM_START_SEC_VAR_FAST_ZERO_INIT_8BIT
# undef CANSM_START_SEC_VAR_FAST_ZERO_INIT_8BIT
# define START_SEC_VAR_FAST_ZERO_INIT_8BIT
#endif

#ifdef CANSM_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT
# undef CANSM_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif







/**********************************************************************************************************************
 *  CanSM END
 *********************************************************************************************************************/


/***********************************************************************************************************************
 *  LINSM START
 **********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef LINSM_START_SEC_CODE
# undef LINSM_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef LINSM_STOP_SEC_CODE
# undef LINSM_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef LINSM_START_SEC_CONST_8BIT
# undef LINSM_START_SEC_CONST_8BIT
# define START_SEC_CONST_8BIT
#endif
#ifdef LINSM_STOP_SEC_CONST_8BIT
# undef LINSM_STOP_SEC_CONST_8BIT
# define STOP_SEC_CONST
#endif

#ifdef LINSM_START_SEC_CONST_UNSPECIFIED
# undef LINSM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef LINSM_STOP_SEC_CONST_UNSPECIFIED
# undef LINSM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif


/* Postbuild CFG CONST sections */

#ifdef LINSM_START_SEC_PBCFG
# undef LINSM_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef LINSM_STOP_SEC_PBCFG
# undef LINSM_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef LINSM_START_SEC_VAR_NOINIT_8BIT
# undef LINSM_START_SEC_VAR_NOINIT_8BIT
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef LINSM_STOP_SEC_VAR_NOINIT_8BIT
# undef LINSM_STOP_SEC_VAR_NOINIT_8BIT
# define STOP_SEC_VAR
#endif

#ifdef LINSM_START_SEC_VAR_NOINIT_16BIT
# undef LINSM_START_SEC_VAR_NOINIT_16BIT
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef LINSM_STOP_SEC_VAR_NOINIT_16BIT
# undef LINSM_STOP_SEC_VAR_NOINIT_16BIT
# define STOP_SEC_VAR
#endif

#ifdef LINSM_START_SEC_VAR_NOINIT_32BIT
# undef LINSM_START_SEC_VAR_NOINIT_32BIT
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef LINSM_STOP_SEC_VAR_NOINIT_32BIT
# undef LINSM_STOP_SEC_VAR_NOINIT_32BIT
# define STOP_SEC_VAR
#endif

#ifdef LINSM_START_SEC_VAR_NOINIT_64BIT
# undef LINSM_START_SEC_VAR_NOINIT_64BIT
# define START_SEC_VAR_NOINIT_64BIT
#endif
#ifdef LINSM_STOP_SEC_VAR_NOINIT_64BIT
# undef LINSM_STOP_SEC_VAR_NOINIT_64BIT
# define STOP_SEC_VAR
#endif

#ifdef LINSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef LINSM_START_SEC_VAR_NOINIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef LINSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef LINSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef LINSM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef LINSM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef LINSM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef LINSM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

#ifdef LINSM_START_SEC_VAR_ZERO_INIT_8BIT
# undef LINSM_START_SEC_VAR_ZERO_INIT_8BIT
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef LINSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef LINSM_STOP_SEC_VAR_ZERO_INIT_8BIT
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  LINSM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  XCP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined(XCP_START_SEC_CODE)
# undef XCP_START_SEC_CODE      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE         /* mapped to default code section */
#endif
#if defined(XCP_STOP_SEC_CODE)
# undef XCP_STOP_SEC_CODE       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE          /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(XCP_START_SEC_CONST_8BIT)
# undef XCP_START_SEC_CONST_8BIT  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT     /* mapped to default const 8bit section */
#endif
#if defined(XCP_STOP_SEC_CONST_8BIT)
# undef XCP_STOP_SEC_CONST_8BIT   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST           /* default const stop section */
#endif

#if defined(XCP_START_SEC_CONST_16BIT)
# undef XCP_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#if defined(XCP_STOP_SEC_CONST_16BIT)
# undef XCP_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(XCP_START_SEC_CONST_32BIT)
# undef XCP_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#if defined(XCP_STOP_SEC_CONST_32BIT)
# undef XCP_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(XCP_START_SEC_CONST_UNSPECIFIED)
# undef XCP_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(XCP_STOP_SEC_CONST_UNSPECIFIED)
# undef XCP_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* Postbuild CFG CONST sections */

#if defined(XCP_START_SEC_PBCFG)
# undef XCP_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#if defined(XCP_STOP_SEC_PBCFG)
# undef XCP_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#if defined(XCP_START_SEC_VAR_INIT_8BIT)
# undef XCP_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT      /* mapped to default var init 8bit section */
#endif
#if defined(XCP_STOP_SEC_VAR_INIT_8BIT)
# undef XCP_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                /* default var stop section */
#endif

#if defined(XCP_START_SEC_VAR_INIT_16BIT)
# undef XCP_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#if defined(XCP_STOP_SEC_VAR_INIT_16BIT)
# undef XCP_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_INIT_32BIT)
# undef XCP_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#if defined(XCP_STOP_SEC_VAR_INIT_32BIT)
# undef XCP_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_INIT_UNSPECIFIED)
# undef XCP_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#if defined(XCP_STOP_SEC_VAR_INIT_UNSPECIFIED)
# undef XCP_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#if defined(XCP_START_SEC_VAR_NOINIT_8BIT)
# undef XCP_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOINIT_8BIT)
# undef XCP_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOINIT_16BIT)
# undef XCP_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOINIT_16BIT)
# undef XCP_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOINIT_32BIT)
# undef XCP_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOINIT_32BIT)
# undef XCP_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef XCP_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(XCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef XCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* ESCAN00065501 */
#if defined(XCP_START_SEC_VAR_PBCFG)
# undef XCP_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#if defined(XCP_STOP_SEC_VAR_PBCFG)
# undef XCP_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#if defined(XCP_START_SEC_VAR_ZERO_INIT_8BIT)
# undef XCP_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(XCP_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef XCP_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_ZERO_INIT_16BIT)
# undef XCP_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#if defined(XCP_STOP_SEC_VAR_ZERO_INIT_16BIT)
# undef XCP_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_ZERO_INIT_32BIT)
# undef XCP_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#if defined(XCP_STOP_SEC_VAR_ZERO_INIT_32BIT)
# undef XCP_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef XCP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(XCP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef XCP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOCACHE INIT sections */

#if defined(XCP_START_SEC_VAR_NOCACHE_INIT_8BIT)
# undef XCP_START_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_8BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_INIT_8BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_INIT_16BIT)
# undef XCP_START_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_16BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_INIT_16BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_INIT_32BIT)
# undef XCP_START_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_32BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_INIT_32BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef XCP_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef XCP_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE NOINIT sections */

#if defined(XCP_START_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef XCP_START_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_8BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef XCP_START_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_16BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef XCP_START_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_32BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef XCP_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef XCP_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE ZERO INIT sections */

#if defined(XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef XCP_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
#endif
#if defined(XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef XCP_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR Safe sections */
#if defined (XCP_START_SEC_VAR_INIT_UNSPECIFIED_SAFE)
# undef XCP_START_SEC_VAR_INIT_UNSPECIFIED_SAFE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#if defined (XCP_STOP_SEC_VAR_INIT_UNSPECIFIED_SAFE)
# undef XCP_STOP_SEC_VAR_INIT_UNSPECIFIED_SAFE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  XCP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANXCP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANXCP_START_SEC_CODE
  #undef CANXCP_START_SEC_CODE                      /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CODE                            /* mapped to default code section */
#endif

#ifdef CANXCP_STOP_SEC_CODE
  #undef CANXCP_STOP_SEC_CODE                       /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CODE                             /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANXCP_START_SEC_CONST_8BIT
  #undef CANXCP_START_SEC_CONST_8BIT                /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CONST_8BIT                      /* mapped to const 8 bit section */
#endif

#ifdef CANXCP_STOP_SEC_CONST_8BIT
  #undef CANXCP_STOP_SEC_CONST_8BIT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CONST                            /* default const stop section */
#endif

#ifdef CANXCP_START_SEC_CONST_UNSPECIFIED
  #undef CANXCP_START_SEC_CONST_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CONST_UNSPECIFIED               /* mapped to const unspecified bit section */
#endif

#ifdef CANXCP_STOP_SEC_CONST_UNSPECIFIED
  #undef CANXCP_STOP_SEC_CONST_UNSPECIFIED          /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


/* Post build config unspecified */

#ifdef CANXCP_START_SEC_PBCFG_ROOT
  #undef CANXCP_START_SEC_PBCFG_ROOT                /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_PBCFG_ROOT
  #undef CANXCP_STOP_SEC_PBCFG_ROOT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


#ifdef CANXCP_START_SEC_PBCFG
  #undef CANXCP_START_SEC_PBCFG                     /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CONST_PBCFG                     /* mapped to const unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_PBCFG
  #undef CANXCP_STOP_SEC_PBCFG                      /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CONST                            /* default const stop section */
#endif


/*******  VAR sections  **********************************************************************************************/

#ifdef CANXCP_START_SEC_VAR_INIT_8BIT
  #undef CANXCP_START_SEC_VAR_INIT_8BIT             /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_VAR_INIT_8BIT                   /* mapped to uninitialized RAM 8bit section */
#endif

#ifdef CANXCP_STOP_SEC_VAR_INIT_8BIT
  #undef CANXCP_STOP_SEC_VAR_INIT_8BIT              /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_VAR                              /* default RAM stop section */
#endif


#ifdef CANXCP_START_SEC_VAR_NOINIT_8BIT
  #undef CANXCP_START_SEC_VAR_NOINIT_8BIT           /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_VAR_NOINIT_8BIT                 /* mapped to uninitialized RAM 8bit section */
#endif

#ifdef CANXCP_STOP_SEC_VAR_NOINIT_8BIT
  #undef CANXCP_STOP_SEC_VAR_NOINIT_8BIT            /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_VAR                              /* default RAM stop section */
#endif


#ifdef CANXCP_START_SEC_VAR_NOINIT_UNSPECIFIED
  #undef CANXCP_START_SEC_VAR_NOINIT_UNSPECIFIED    /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_VAR_NOINIT_UNSPECIFIED          /* mapped to uninitialized RAM unspecified section */
#endif

#ifdef CANXCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #undef CANXCP_STOP_SEC_VAR_NOINIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_VAR                              /* default RAM stop section */
#endif


#ifdef CANXCP_START_SEC_VAR_INIT_UNSPECIFIED_SAFE 
    #undef CANXCP_START_SEC_VAR_INIT_UNSPECIFIED_SAFE /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef CANXCP_STOP_SEC_VAR_INIT_UNSPECIFIED_SAFE 
    #undef CANXCP_STOP_SEC_VAR_INIT_UNSPECIFIED_SAFE /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  CANXCP END
 *********************************************************************************************************************/

/** DEM **********************************************************************/
/*---------------------START-MODULE-SPECIFIC-START-SECTIONS------------------*/

                                                            /* code sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_START_SEC_CODE)
# undef DEM_START_SEC_CODE                                                     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif

#if defined (DEM_START_SEC_CALLOUT_CODE)
# undef DEM_START_SEC_CALLOUT_CODE                                             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif

#if defined (DEM_START_SEC_CODE_LIB)
# undef DEM_START_SEC_CODE_LIB                                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif

                                               /* uninitialized RAM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_START_SEC_VAR_NOINIT_8BIT)
# undef DEM_START_SEC_VAR_NOINIT_8BIT                                          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined (DEM_START_SEC_VAR_NOINIT_16BIT)
# undef DEM_START_SEC_VAR_NOINIT_16BIT                                         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined (DEM_START_SEC_VAR_NOINIT_32BIT)
# undef DEM_START_SEC_VAR_NOINIT_32BIT                                         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#if defined (DEM_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef DEM_START_SEC_VAR_NOINIT_UNSPECIFIED                                   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_VAR_UNCACHED_UNSPECIFIED)
# undef DEM_START_SEC_VAR_UNCACHED_UNSPECIFIED                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_VAR_NOINIT_UNSPECIFIED_SAT0)
# undef DEM_START_SEC_VAR_NOINIT_UNSPECIFIED_SAT0                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_VAR_NOINIT_UNSPECIFIED_SAT1)
# undef DEM_START_SEC_VAR_NOINIT_UNSPECIFIED_SAT1                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED)
# undef DEM_START_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED                        /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
                                                 /* initialized RAM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_START_SEC_VAR_INIT_8BIT)
# undef DEM_START_SEC_VAR_INIT_8BIT                                            /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT
#endif
#if defined (DEM_START_SEC_VAR_INIT_32BIT)
# undef DEM_START_SEC_VAR_INIT_32BIT                                           /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#if defined (DEM_START_SEC_VAR_INIT_8BIT_RESTRICTED)
# undef DEM_START_SEC_VAR_INIT_8BIT_RESTRICTED                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT
#endif

                                              /* post-buildable RAM sections */
/*---------------------------------------------------------------------------*/
#if defined (DEM_START_SEC_VAR_PBCFG)
# undef DEM_START_SEC_VAR_PBCFG                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif


                                                          /* NV RAM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_START_SEC_VAR_SAVED_ZONE0_8BIT)
# undef DEM_START_SEC_VAR_SAVED_ZONE0_8BIT                                     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif

#if defined (DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED)
# undef DEM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_CONST_SAVED_RECOVERY_ZONE0)
# undef DEM_START_SEC_CONST_SAVED_RECOVERY_ZONE0                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif

                                                             /* ROM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_START_SEC_CONST_8BIT)
# undef DEM_START_SEC_CONST_8BIT                                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT
#endif
#if defined (DEM_START_SEC_CONST_16BIT)
# undef DEM_START_SEC_CONST_16BIT                                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#if defined (DEM_START_SEC_CONST_32BIT)
# undef DEM_START_SEC_CONST_32BIT                                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#if defined (DEM_START_SEC_CONST_UNSPECIFIED)
# undef DEM_START_SEC_CONST_UNSPECIFIED                                        /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_CONFIG_DATA_UNSPECIFIED)
# undef DEM_START_SEC_CONFIG_DATA_UNSPECIFIED                                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_PBCFG_ROOT)
# undef DEM_START_SEC_PBCFG_ROOT                                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif

#if defined (DEM_START_SEC_CALIB_UNSPECIFIED)
# undef DEM_START_SEC_CALIB_UNSPECIFIED                                        /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif

#if defined (DEM_START_SEC_CALIB_8BIT)
# undef DEM_START_SEC_CALIB_8BIT                                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT
#endif

#if defined (DEM_START_SEC_PBCFG)
# undef DEM_START_SEC_PBCFG                                                    /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif



/*---------------------STOP-MODULE-SPECIFIC-START-SECTIONS-------------------*/

/*---------------------START-MODULE-SPECIFIC-STOP-SECTIONS-------------------*/


                                                            /* code sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_STOP_SEC_CODE)
# undef DEM_STOP_SEC_CODE                                                      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif

#if defined (DEM_STOP_SEC_CALLOUT_CODE)
# undef DEM_STOP_SEC_CALLOUT_CODE                                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif

#if defined (DEM_STOP_SEC_CODE_LIB)
# undef DEM_STOP_SEC_CODE_LIB                                                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif

                                               /* uninitialized RAM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_STOP_SEC_VAR_NOINIT_8BIT)
# undef DEM_STOP_SEC_VAR_NOINIT_8BIT                                           /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_NOINIT_16BIT)
# undef DEM_STOP_SEC_VAR_NOINIT_16BIT                                          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_NOINIT_32BIT)
# undef DEM_STOP_SEC_VAR_NOINIT_32BIT                                          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED                                    /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_UNCACHED_UNSPECIFIED)
# undef DEM_STOP_SEC_VAR_UNCACHED_UNSPECIFIED                                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_SAT0)
# undef DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_SAT0                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_SAT1)
# undef DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_SAT1                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED)
# undef DEM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED                         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

                                                 /* initialized RAM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_STOP_SEC_VAR_INIT_8BIT)
# undef DEM_STOP_SEC_VAR_INIT_8BIT                                             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif
#if defined (DEM_STOP_SEC_VAR_INIT_32BIT)
# undef DEM_STOP_SEC_VAR_INIT_32BIT                                            /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_INIT_8BIT_RESTRICTED)
# undef DEM_STOP_SEC_VAR_INIT_8BIT_RESTRICTED                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif
                                              /* post-buildable RAM sections */
/*---------------------------------------------------------------------------*/
#if defined (DEM_STOP_SEC_VAR_PBCFG)
# undef DEM_STOP_SEC_VAR_PBCFG                                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

                                                          /* NV RAM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED)
# undef DEM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_VAR_SAVED_ZONE0_8BIT)
# undef DEM_STOP_SEC_VAR_SAVED_ZONE0_8BIT                                      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined (DEM_STOP_SEC_CONST_SAVED_RECOVERY_ZONE0)
# undef DEM_STOP_SEC_CONST_SAVED_RECOVERY_ZONE0                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

                                                             /* ROM sections */
/*---------------------------------------------------------------------------*/

#if defined (DEM_STOP_SEC_CONST_8BIT)
# undef DEM_STOP_SEC_CONST_8BIT                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CONST_16BIT)
# undef DEM_STOP_SEC_CONST_16BIT                                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CONST_32BIT)
# undef DEM_STOP_SEC_CONST_32BIT                                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CONST_UNSPECIFIED)
# undef DEM_STOP_SEC_CONST_UNSPECIFIED                                         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined (DEM_STOP_SEC_PBCFG_ROOT)
# undef DEM_STOP_SEC_PBCFG_ROOT                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined (DEM_STOP_SEC_CALIB_UNSPECIFIED)
# undef DEM_STOP_SEC_CALIB_UNSPECIFIED                                         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif
#if defined (DEM_STOP_SEC_CALIB_8BIT)
# undef DEM_STOP_SEC_CALIB_8BIT                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined (DEM_STOP_SEC_PBCFG)
# undef DEM_STOP_SEC_PBCFG                                                     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

//#include "Dem_MemMap.h"

/*---------------------STOP-MODULE-SPECIFIC-STOP-SECTIONS--------------------*/
/** End of DEM ***************************************************************/



/**********************************************************************************************************************
 *  J1939DCM START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef J1939DCM_START_SEC_CODE
# undef J1939DCM_START_SEC_CODE                                                                                                                      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE      /* mapped to default code section */
#endif
#ifdef J1939DCM_STOP_SEC_CODE
# undef J1939DCM_STOP_SEC_CODE                                                                                                                       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE      /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/*! CONST sections */

#ifdef J1939DCM_START_SEC_CONST_8BIT
# undef J1939DCM_START_SEC_CONST_8BIT                                                                                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT      /* mapped to default const 8bit section */
#endif
#ifdef J1939DCM_STOP_SEC_CONST_8BIT
# undef J1939DCM_STOP_SEC_CONST_8BIT                                                                                                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST           /* default const stop section */
#endif

#ifdef J1939DCM_START_SEC_CONST_16BIT
# undef J1939DCM_START_SEC_CONST_16BIT                                                                                                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#ifdef J1939DCM_STOP_SEC_CONST_16BIT
# undef J1939DCM_STOP_SEC_CONST_16BIT                                                                                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef J1939DCM_START_SEC_CONST_32BIT
# undef J1939DCM_START_SEC_CONST_32BIT                                                                                                               /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#ifdef J1939DCM_STOP_SEC_CONST_32BIT
# undef J1939DCM_STOP_SEC_CONST_32BIT                                                                                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef J1939DCM_START_SEC_CONST_UNSPECIFIED
# undef J1939DCM_START_SEC_CONST_UNSPECIFIED                                                                                                         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef J1939DCM_STOP_SEC_CONST_UNSPECIFIED
# undef J1939DCM_STOP_SEC_CONST_UNSPECIFIED                                                                                                          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*! Postbuild CFG CONST sections */

#ifdef J1939DCM_START_SEC_PBCFG
# undef J1939DCM_START_SEC_PBCFG                                                                                                                     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef J1939DCM_STOP_SEC_PBCFG
# undef J1939DCM_STOP_SEC_PBCFG                                                                                                                      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef J1939DCM_START_SEC_PBCFG_ROOT
# undef J1939DCM_START_SEC_PBCFG_ROOT                                                                                                                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef J1939DCM_STOP_SEC_PBCFG_ROOT
# undef J1939DCM_STOP_SEC_PBCFG_ROOT                                                                                                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/*! VAR INIT sections */

#ifdef J1939DCM_START_SEC_VAR_INIT_8BIT
# undef J1939DCM_START_SEC_VAR_INIT_8BIT                                                                                                             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT      /* mapped to default var init 8bit section */
#endif
#ifdef J1939DCM_STOP_SEC_VAR_INIT_8BIT
# undef J1939DCM_STOP_SEC_VAR_INIT_8BIT                                                                                                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                /* default var stop section */
#endif

#ifdef J1939DCM_START_SEC_VAR_INIT_16BIT
# undef J1939DCM_START_SEC_VAR_INIT_16BIT                                                                                                            /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#ifdef J1939DCM_STOP_SEC_VAR_INIT_16BIT
# undef J1939DCM_STOP_SEC_VAR_INIT_16BIT                                                                                                             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef J1939DCM_START_SEC_VAR_INIT_32BIT
# undef J1939DCM_START_SEC_VAR_INIT_32BIT                                                                                                            /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#ifdef J1939DCM_STOP_SEC_VAR_INIT_32BIT
# undef J1939DCM_STOP_SEC_VAR_INIT_32BIT                                                                                                             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef J1939DCM_START_SEC_VAR_INIT_UNSPECIFIED
# undef J1939DCM_START_SEC_VAR_INIT_UNSPECIFIED                                                                                                      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef J1939DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef J1939DCM_STOP_SEC_VAR_INIT_UNSPECIFIED                                                                                                       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/*! VAR NOINIT sections */

#ifdef J1939DCM_START_SEC_VAR_NOINIT_8BIT
# undef J1939DCM_START_SEC_VAR_NOINIT_8BIT                                                                                                           /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef J1939DCM_STOP_SEC_VAR_NOINIT_8BIT
# undef J1939DCM_STOP_SEC_VAR_NOINIT_8BIT                                                                                                            /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef J1939DCM_START_SEC_VAR_NOINIT_16BIT
# undef J1939DCM_START_SEC_VAR_NOINIT_16BIT                                                                                                          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef J1939DCM_STOP_SEC_VAR_NOINIT_16BIT
# undef J1939DCM_STOP_SEC_VAR_NOINIT_16BIT                                                                                                           /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef J1939DCM_START_SEC_VAR_NOINIT_32BIT
# undef J1939DCM_START_SEC_VAR_NOINIT_32BIT                                                                                                          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef J1939DCM_STOP_SEC_VAR_NOINIT_32BIT
# undef J1939DCM_STOP_SEC_VAR_NOINIT_32BIT                                                                                                           /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef J1939DCM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef J1939DCM_START_SEC_VAR_NOINIT_UNSPECIFIED                                                                                                    /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef J1939DCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef J1939DCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED                                                                                                     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/*! ESCAN00065501 */
#ifdef J1939DCM_START_SEC_VAR_PBCFG
# undef J1939DCM_START_SEC_VAR_PBCFG                                                                                                                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#ifdef J1939DCM_STOP_SEC_VAR_PBCFG
# undef J1939DCM_STOP_SEC_VAR_PBCFG                                                                                                                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif



/**********************************************************************************************************************
 *  J1939DCM END
 *********************************************************************************************************************/

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/*        STARTSINGLE_OF_MULTIPLE_COMMENT      */


/**********************************************************************************************************************
 *  Can START  DRVCAN_MPC5700MCANASR
 *********************************************************************************************************************/

#if defined (CAN_REMAP_PB_SECTIONS)        /* PRQA S 0883 */ /* Appears only while testing */
/* for none PB variants the code will be mapped to standard sections, so the generated and static code can ignore the variant handling */
# if defined (CAN_START_SEC_PBCFG)
#  undef CAN_START_SEC_PBCFG                /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_START_SEC_CONST_UNSPECIFIED
# endif
# if defined (CAN_STOP_SEC_PBCFG)
#  undef CAN_STOP_SEC_PBCFG                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_STOP_SEC_CONST_UNSPECIFIED
# endif

# if defined (CAN_START_SEC_VAR_PBCFG)
#  undef CAN_START_SEC_VAR_PBCFG            /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
# endif
# if defined (CAN_STOP_SEC_VAR_PBCFG)
#  undef CAN_STOP_SEC_VAR_PBCFG             /* PRQA S 0841 */ /* MD_MSR_19.6 */
#  define CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# endif
#endif

/*******  CODE sections **********************************************************************************************/

#ifdef CAN_START_SEC_CODE                             /* CAN code */
# undef CAN_START_SEC_CODE                              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_CODE
# undef CAN_STOP_SEC_CODE                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

#ifdef CAN_START_SEC_STATIC_CODE                      /* CAN static code */
# undef CAN_START_SEC_STATIC_CODE                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_STATIC_CODE
# undef CAN_STOP_SEC_STATIC_CODE                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

#ifdef CAN_START_SEC_CODE_APPL                        /* Appl code (generic precopy)*/
# undef CAN_START_SEC_CODE_APPL                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                               /* mapped to default code section */
#endif
#ifdef CAN_STOP_SEC_CODE_APPL
# undef CAN_STOP_SEC_CODE_APPL                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CAN_START_SEC_CONST_8BIT                       /* Const 8bit */
# undef CAN_START_SEC_CONST_8BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                         /* mapped to default const 8bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_8BIT
# undef CAN_STOP_SEC_CONST_8BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_16BIT                      /* Const 16bit */
# undef CAN_START_SEC_CONST_16BIT                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_16BIT                        /* mapped to default const 16bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_16BIT
# undef CAN_STOP_SEC_CONST_16BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_32BIT                      /* Const 32bit */
# undef CAN_START_SEC_CONST_32BIT                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT                        /* mapped to default const 32bit section */
#endif
#ifdef CAN_STOP_SEC_CONST_32BIT
# undef CAN_STOP_SEC_CONST_32BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_CONST_UNSPECIFIED                /* Const unspecified */
# undef CAN_START_SEC_CONST_UNSPECIFIED                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED                  /* mapped to default const unspec section */
#endif
#ifdef CAN_STOP_SEC_CONST_UNSPECIFIED
# undef CAN_STOP_SEC_CONST_UNSPECIFIED                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */
/* unused */

/* Postbuild CFG CONST sections */

/* Root table for postbuild data (not relevant for CFG5 AutoSar4.0.3) */
#ifdef CAN_START_SEC_PBCFG_ROOT                       /* Generated Postbuild Root Table */
# undef CAN_START_SEC_PBCFG_ROOT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                        /* mapped to default const postbuild section */
#endif
#ifdef CAN_STOP_SEC_PBCFG_ROOT
# undef CAN_STOP_SEC_PBCFG_ROOT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef CAN_START_SEC_PBCFG                            /* Generated Postbuild */
# undef CAN_START_SEC_PBCFG                             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                        /* mapped to default const postbuild section */
#endif
#ifdef CAN_STOP_SEC_PBCFG
# undef CAN_STOP_SEC_PBCFG                              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef CAN_START_SEC_VAR_INIT_UNSPECIFIED             /* init RAM*/
# undef CAN_START_SEC_VAR_INIT_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED               /* mapped to default init var section */
#endif
#ifdef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef CAN_START_SEC_VAR_NOINIT_UNSPECIFIED           /* uninit RAM*/
# undef CAN_START_SEC_VAR_NOINIT_UNSPECIFIED            /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#ifdef CAN_START_SEC_VAR_NOINIT_8BIT                  /* uninit 8bit RAM*/
# undef CAN_START_SEC_VAR_NOINIT_8BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_NOINIT_8BIT
# undef CAN_STOP_SEC_VAR_NOINIT_8BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#ifdef CAN_START_SEC_VAR_NOINIT_16BIT                  /* uninit 16bit RAM*/
# undef CAN_START_SEC_VAR_NOINIT_16BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_NOINIT_16BIT
# undef CAN_STOP_SEC_VAR_NOINIT_16BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#ifdef CAN_START_SEC_VAR_NOINIT_32BIT                  /* uninit 32bit RAM*/
# undef CAN_START_SEC_VAR_NOINIT_32BIT                 /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_NOINIT_32BIT
# undef CAN_STOP_SEC_VAR_NOINIT_32BIT                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif



/* VAR PBCFG sections */

#ifdef CAN_START_SEC_VAR_PBCFG           /* Generated Postbuild RAM*/
# undef CAN_START_SEC_VAR_PBCFG            /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_PBCFG             /* mapped to default uninit var section */
#endif
#ifdef CAN_STOP_SEC_VAR_PBCFG
# undef CAN_STOP_SEC_VAR_PBCFG             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */
/* unused */


/* VAR FAST INIT sections */
/* unused */


/* VAR FAST NOINIT sections */
/* unused */

/* VAR FAST ZERO INIT sections */
/* unused */



/**********************************************************************************************************************
 *  Can END    DRVCAN_MPC5700MCANASR
 *********************************************************************************************************************/

/*  STOPSINGLE_OF_MULTIPLE_COMMENT  */
/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_TricoreMcanAsr Erzeugungsgangnummer: 766 */



/**********************************************************************************************************************
 *  EEP_30_XXSPI01 START
 *********************************************************************************************************************/

/******** CODE sections **********************************************************************************************/

#ifdef EEP_30_XXSPI01_START_SEC_CODE
# undef EEP_30_XXSPI01_START_SEC_CODE /* PRQA S 841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif
#ifdef EEP_30_XXSPI01_STOP_SEC_CODE
# undef EEP_30_XXSPI01_STOP_SEC_CODE /* PRQA S 841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif

/*******  CONST sections  ********************************************************************************************/

#ifdef EEP_30_XXSPI01_START_SEC_CONST_32
# undef EEP_30_XXSPI01_START_SEC_CONST_32 /* PRQA S 841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32
#endif
#ifdef EEP_30_XXSPI01_STOP_SEC_CONST_32
# undef EEP_30_XXSPI01_STOP_SEC_CONST_32 /* PRQA S 841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef EEP_30_XXSPI01_START_SEC_CONST_UNSPECIFIED
# undef EEP_30_XXSPI01_START_SEC_CONST_UNSPECIFIED /* PRQA S 841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef EEP_30_XXSPI01_STOP_SEC_CONST_UNSPECIFIED
# undef EEP_30_XXSPI01_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef EEP_30_XXSPI01_START_SEC_PBCFG_ROOT
# undef EEP_30_XXSPI01_START_SEC_PBCFG_ROOT /* PRQA S 841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef EEP_30_XXSPI01_STOP_SEC_PBCFG_ROOT
# undef EEP_30_XXSPI01_STOP_SEC_PBCFG_ROOT /* PRQA S 841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef EEP_30_XXSPI01_INST2_START_SEC_PBCFG_ROOT
# undef EEP_30_XXSPI01_INST2_START_SEC_PBCFG_ROOT /* PRQA S 841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef EEP_30_XXSPI01_INST2_STOP_SEC_PBCFG_ROOT
# undef EEP_30_XXSPI01_INST2_STOP_SEC_PBCFG_ROOT /* PRQA S 841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

#ifdef EEP_30_XXSPI01_START_SEC_VAR_NO_INIT_UNSPECIFIED
# undef EEP_30_XXSPI01_START_SEC_VAR_NO_INIT_UNSPECIFIED /* PRQA S 841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef EEP_30_XXSPI01_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# undef EEP_30_XXSPI01_STOP_SEC_VAR_NO_INIT_UNSPECIFIED /* PRQA S 841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef EEP_30_XXSPI01_START_SEC_VAR_INIT_UNSPECIFIED
# undef EEP_30_XXSPI01_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef EEP_30_XXSPI01_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef EEP_30_XXSPI01_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  EEP_30_XXSPI01 END
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**        \file  Lin_MemMap.inc
 *        \brief  AUTOSAR LIN Driver
 *
 *      \details  AUTOSAR LIN Driver for all target systems
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  LIN START
 **********************************************************************************************************************/

/*******  CODE sections ***********************************************************************************************/
/* PRQA S 0883 514 */ /* MD_LIN_TESTSUITE_WORKAROUND */
#if defined(LIN_START_SEC_CODE)
# undef LIN_START_SEC_CODE      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE                                               /* mapped to default code section */
#endif
#if defined(LIN_STOP_SEC_CODE)
# undef LIN_STOP_SEC_CODE       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE                                                /* default code stop section */
#endif

#if defined(LIN_START_SEC_CODE_FAST)
# undef LIN_START_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE_FAST                                          /* mapped to default fast code section */
#endif
#if defined(LIN_STOP_SEC_CODE_FAST)
# undef LIN_STOP_SEC_CODE_FAST  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE                                                /* default code stop section */
#endif

#if defined(LIN_START_SEC_CODE_ISR)
# undef LIN_START_SEC_CODE_ISR  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE_ISR                                           /* mapped to default ISR code section */
#endif
#if defined(LIN_STOP_SEC_CODE_ISR)
# undef LIN_STOP_SEC_CODE_ISR   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE                                                /* default code stop section */
#endif

#ifdef LIN_START_SEC_CODE_APPL
# undef LIN_START_SEC_CODE_APPL /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE                                               /* mapped to default code section */
#endif
#ifdef LIN_STOP_SEC_CODE_APPL
# undef LIN_STOP_SEC_CODE_APPL /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE                                                /* default code stop section */
#endif


/*******  CONST sections  *********************************************************************************************/

/* CONST sections */

#if defined(LIN_START_SEC_CONST_8BIT)
# undef LIN_START_SEC_CONST_8BIT  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT                                         /* mapped to default const 8bit section */
#endif
#if defined(LIN_STOP_SEC_CONST_8BIT)
# undef LIN_STOP_SEC_CONST_8BIT   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                                               /* default const stop section */
#endif

#if defined(LIN_START_SEC_CONST_16BIT)
# undef LIN_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#if defined(LIN_STOP_SEC_CONST_16BIT)
# undef LIN_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(LIN_START_SEC_CONST_32BIT)
# undef LIN_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#if defined(LIN_STOP_SEC_CONST_32BIT)
# undef LIN_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(LIN_START_SEC_CONST_UNSPECIFIED)
# undef LIN_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_CONST_UNSPECIFIED)
# undef LIN_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */

#if defined(LIN_START_SEC_FAST_CONST_8BIT)
# undef LIN_START_SEC_FAST_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_8BIT
#endif
#if defined(LIN_STOP_SEC_FAST_CONST_8BIT)
# undef LIN_STOP_SEC_FAST_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(LIN_START_SEC_FAST_CONST_16BIT)
# undef LIN_START_SEC_FAST_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_16BIT
#endif
#if defined(LIN_STOP_SEC_FAST_CONST_16BIT)
# undef LIN_STOP_SEC_FAST_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(LIN_START_SEC_FAST_CONST_32BIT)
# undef LIN_START_SEC_FAST_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_32BIT
#endif
#if defined(LIN_STOP_SEC_FAST_CONST_32BIT)
# undef LIN_STOP_SEC_FAST_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(LIN_START_SEC_FAST_CONST_UNSPECIFIED)
# undef LIN_START_SEC_FAST_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_FAST_CONST_UNSPECIFIED)
# undef LIN_STOP_SEC_FAST_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* Postbuild CFG CONST sections */

/* NOTE: ASR3.x till ASR4.0.1 only. Root table for postbuild data */
#if defined(LIN_START_SEC_PBCFG_ROOT)
# undef LIN_START_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#if defined(LIN_STOP_SEC_PBCFG_ROOT)
# undef LIN_STOP_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/* ESCAN00065501 */
/* NOTE: ASR4.0.3 (CFG5) only. The origin root table for postbuild data. Relevant only for EcuM. */
#if defined(LIN_START_SEC_PBCFG_GLOBALROOT)
# undef LIN_START_SEC_PBCFG_GLOBALROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_PBCFG_GLOBALROOT
#endif
#if defined(LIN_STOP_SEC_PBCFG_GLOBALROOT)
# undef LIN_STOP_SEC_PBCFG_GLOBALROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(LIN_START_SEC_PBCFG)
# undef LIN_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#if defined(LIN_STOP_SEC_PBCFG)
# undef LIN_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  ***********************************************************************************************/

/* VAR INIT sections */

#if defined(LIN_START_SEC_VAR_INIT_8BIT)
# undef LIN_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT                                      /* mapped to default var init 8bit section */
#endif
#if defined(LIN_STOP_SEC_VAR_INIT_8BIT)
# undef LIN_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                                                 /* default var stop section */
#endif

#if defined(LIN_START_SEC_VAR_INIT_16BIT)
# undef LIN_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_INIT_16BIT)
# undef LIN_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_INIT_32BIT)
# undef LIN_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_INIT_32BIT)
# undef LIN_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_INIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_INIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#if defined(LIN_START_SEC_VAR_NOINIT_8BIT)
# undef LIN_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOINIT_8BIT)
# undef LIN_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOINIT_16BIT)
# undef LIN_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOINIT_16BIT)
# undef LIN_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOINIT_32BIT)
# undef LIN_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOINIT_32BIT)
# undef LIN_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* ESCAN00065501 */
#if defined(LIN_START_SEC_VAR_PBCFG)
# undef LIN_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#if defined(LIN_STOP_SEC_VAR_PBCFG)
# undef LIN_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#if defined(LIN_START_SEC_VAR_ZERO_INIT_8BIT)
# undef LIN_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef LIN_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_ZERO_INIT_16BIT)
# undef LIN_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_ZERO_INIT_16BIT)
# undef LIN_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_ZERO_INIT_32BIT)
# undef LIN_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_ZERO_INIT_32BIT)
# undef LIN_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */

#if defined(LIN_START_SEC_VAR_FAST_INIT_8BIT)
# undef LIN_START_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_INIT_8BIT)
# undef LIN_STOP_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_INIT_16BIT)
# undef LIN_START_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_INIT_16BIT)
# undef LIN_STOP_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_INIT_32BIT)
# undef LIN_START_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_INIT_32BIT)
# undef LIN_STOP_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST NOINIT sections */

#if defined(LIN_START_SEC_VAR_FAST_NOINIT_8BIT)
# undef LIN_START_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_NOINIT_8BIT)
# undef LIN_STOP_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_NOINIT_16BIT)
# undef LIN_START_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_NOINIT_16BIT)
# undef LIN_STOP_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_NOINIT_32BIT)
# undef LIN_START_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_NOINIT_32BIT)
# undef LIN_STOP_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR FAST ZERO INIT sections */

#if defined(LIN_START_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef LIN_START_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef LIN_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef LIN_START_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef LIN_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef LIN_START_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef LIN_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE INIT sections */

#if defined(LIN_START_SEC_VAR_NOCACHE_INIT_8BIT)
# undef LIN_START_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_INIT_8BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_INIT_16BIT)
# undef LIN_START_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_INIT_16BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_INIT_32BIT)
# undef LIN_START_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_INIT_32BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE NOINIT sections */

#if defined(LIN_START_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef LIN_START_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef LIN_START_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef LIN_START_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE ZERO INIT sections */

#if defined(LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef LIN_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
#endif
#if defined(LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef LIN_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/***********************************************************************************************************************
 *  LIN END
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  SBC START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef SBC_30_FS6500_START_SEC_CODE
  #undef SBC_30_FS6500_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CODE      /* mapped to default code section */
#endif
#ifdef SBC_30_FS6500_STOP_SEC_CODE
  #undef SBC_30_FS6500_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CODE      /* default code stop section */
#endif

#ifdef SBC_30_FS6500_START_SEC_CODE_FAST
  #undef SBC_30_FS6500_START_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CODE_FAST      /* mapped to default fast code section */
#endif
#ifdef SBC_30_FS6500_STOP_SEC_CODE_FAST
  #undef SBC_30_FS6500_STOP_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CODE           /* default code stop section */
#endif

#ifdef SBC_30_FS6500_START_SEC_CODE_ISR
  #undef SBC_30_FS6500_START_SEC_CODE_ISR /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CODE_ISR      /* mapped to default ISR code section */
#endif
#ifdef SBC_30_FS6500_STOP_SEC_CODE_ISR
  #undef SBC_30_FS6500_STOP_SEC_CODE_ISR /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CODE          /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef SBC_30_FS6500_START_SEC_CONST_8BIT
# undef SBC_30_FS6500_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT      /* mapped to default const 8bit section */
#endif
#ifdef SBC_30_FS6500_STOP_SEC_CONST_8BIT
# undef SBC_30_FS6500_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST           /* default const stop section */
#endif

#ifdef SBC_30_FS6500_START_SEC_CONST_16BIT
# undef SBC_30_FS6500_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_CONST_16BIT
# undef SBC_30_FS6500_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef SBC_30_FS6500_START_SEC_CONST_32BIT
# undef SBC_30_FS6500_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_CONST_32BIT
# undef SBC_30_FS6500_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef SBC_30_FS6500_START_SEC_CONST_UNSPECIFIED /* COV_SBC_UNUSED_MEM_SEC */
# undef SBC_30_FS6500_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_CONST_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */

#ifdef SBC_30_FS6500_START_SEC_FAST_CONST_8BIT
# undef SBC_30_FS6500_START_SEC_FAST_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_FAST_CONST_8BIT
# undef SBC_30_FS6500_STOP_SEC_FAST_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef SBC_30_FS6500_START_SEC_FAST_CONST_16BIT
# undef SBC_30_FS6500_START_SEC_FAST_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_FAST_CONST_16BIT
# undef SBC_30_FS6500_STOP_SEC_FAST_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef SBC_30_FS6500_START_SEC_FAST_CONST_32BIT
# undef SBC_30_FS6500_START_SEC_FAST_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_FAST_CONST_32BIT
# undef SBC_30_FS6500_STOP_SEC_FAST_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef SBC_30_FS6500_START_SEC_FAST_CONST_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_FAST_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_FAST_CONST_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_FAST_CONST_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_FAST_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* Postbuild CFG CONST sections */

/* NOTE: ASR3.x till ASR4.0.1 only. Root table for postbuild data */
#ifdef SBC_30_FS6500_START_SEC_PBCFG_ROOT
# undef SBC_30_FS6500_START_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef SBC_30_FS6500_STOP_SEC_PBCFG_ROOT
# undef SBC_30_FS6500_STOP_SEC_PBCFG_ROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/* ESCAN00065501 */
/* NOTE: ASR4.0.3 (CFG5) only. The origin root table for postbuild data. Relevant only for EcuM. */
#ifdef SBC_30_FS6500_START_SEC_PBCFG_GLOBALROOT
# undef SBC_30_FS6500_START_SEC_PBCFG_GLOBALROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_PBCFG_GLOBALROOT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_PBCFG_GLOBALROOT
# undef SBC_30_FS6500_STOP_SEC_PBCFG_GLOBALROOT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef SBC_30_FS6500_START_SEC_PBCFG
# undef SBC_30_FS6500_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef SBC_30_FS6500_STOP_SEC_PBCFG
# undef SBC_30_FS6500_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_INIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT      /* mapped to default var init 8bit section */
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_INIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                /* default var stop section */
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_INIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_INIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_INIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_INIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_INIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_NOINIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOINIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOINIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOINIT_SAFE
# undef SBC_30_FS6500_START_SEC_VAR_NOINIT_SAFE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_SAFE
# undef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_SAFE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* ESCAN00065501 */
#ifdef SBC_30_FS6500_START_SEC_VAR_PBCFG
# undef SBC_30_FS6500_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_PBCFG
# undef SBC_30_FS6500_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST NOINIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR FAST ZERO INIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE INIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE NOINIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE ZERO INIT sections */

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
# undef SBC_30_FS6500_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
#endif
#ifdef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
# undef SBC_30_FS6500_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  SBC END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CANTRCV_30_SBC START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined(CANTRCV_30_SBC_START_SEC_CODE) /* PRQA S 0883 */ /* Appears only while testing */
# undef CANTRCV_30_SBC_START_SEC_CODE      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE         /* mapped to default code section */
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_CODE)
# undef CANTRCV_30_SBC_STOP_SEC_CODE       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE          /* default code stop section */
#endif

#if defined(CANTRCV_30_SBC_START_SEC_CODE_FAST)
# undef CANTRCV_30_SBC_START_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE_FAST    /* mapped to default fast code section */
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_CODE_FAST)
# undef CANTRCV_30_SBC_STOP_SEC_CODE_FAST  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE          /* default code stop section */
#endif

#if defined(CANTRCV_30_SBC_START_SEC_CODE_ISR)
# undef CANTRCV_30_SBC_START_SEC_CODE_ISR  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE_ISR     /* mapped to default ISR code section */
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_CODE_ISR)
# undef CANTRCV_30_SBC_STOP_SEC_CODE_ISR   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE          /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(CANTRCV_30_SBC_START_SEC_CONST_8BIT)
# undef CANTRCV_30_SBC_START_SEC_CONST_8BIT  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT     /* mapped to default const 8bit section */
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_CONST_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_CONST_8BIT   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST           /* default const stop section */
#endif

#if defined(CANTRCV_30_SBC_START_SEC_CONST_16BIT)
# undef CANTRCV_30_SBC_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_CONST_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_SBC_START_SEC_CONST_32BIT)
# undef CANTRCV_30_SBC_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_CONST_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_SBC_START_SEC_CONST_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_CONST_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */

#if defined(CANTRCV_30_SBC_START_SEC_FAST_CONST_8BIT)
# undef CANTRCV_30_SBC_START_SEC_FAST_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_FAST_CONST_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_FAST_CONST_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_FAST_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_SBC_START_SEC_FAST_CONST_16BIT)
# undef CANTRCV_30_SBC_START_SEC_FAST_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_FAST_CONST_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_FAST_CONST_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_FAST_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_SBC_START_SEC_FAST_CONST_32BIT)
# undef CANTRCV_30_SBC_START_SEC_FAST_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_FAST_CONST_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_FAST_CONST_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_FAST_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_SBC_START_SEC_FAST_CONST_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_FAST_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_FAST_CONST_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_FAST_CONST_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_FAST_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/* Postbuild CFG CONST sections */

#if defined(CANTRCV_30_SBC_START_SEC_PBCFG)
# undef CANTRCV_30_SBC_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_PBCFG)
# undef CANTRCV_30_SBC_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_INIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_8BIT      /* mapped to default var init 8bit section */
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_INIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                /* default var stop section */
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_INIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_INIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_INIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_INIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOINIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOINIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOINIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* ESCAN00065501 */
#if defined(CANTRCV_30_SBC_START_SEC_VAR_PBCFG)
# undef CANTRCV_30_SBC_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_PBCFG
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_PBCFG)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_INIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_INIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_INIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR FAST NOINIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR FAST ZERO INIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE INIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_INIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_INIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_INIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE NOINIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE ZERO INIT sections */

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_SBC_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  CANTRCV_30_SBC END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LIN TRANSCEIVER SBC DRIVER START
 *********************************************************************************************************************/
/*******  CODE sections **********************************************************************************************/

#if defined(LINTRCV_30_SBC_START_SEC_CODE)
# undef LINTRCV_30_SBC_START_SEC_CODE      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif
#if defined(LINTRCV_30_SBC_STOP_SEC_CODE)
# undef LINTRCV_30_SBC_STOP_SEC_CODE       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(LINTRCV_30_SBC_START_SEC_CONST_8BIT)
# undef LINTRCV_30_SBC_START_SEC_CONST_8BIT  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT
#endif
#if defined(LINTRCV_30_SBC_STOP_SEC_CONST_8BIT)
# undef LINTRCV_30_SBC_STOP_SEC_CONST_8BIT   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#if defined(LINTRCV_30_SBC_START_SEC_CONST_32BIT)
# undef LINTRCV_30_SBC_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_32BIT
#endif
#if defined(LINTRCV_30_SBC_STOP_SEC_CONST_32BIT)
# undef LINTRCV_30_SBC_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


#if defined(LINTRCV_30_SBC_START_SEC_CONST_UNSPECIFIED)
# undef LINTRCV_30_SBC_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(LINTRCV_30_SBC_STOP_SEC_CONST_UNSPECIFIED)
# undef LINTRCV_30_SBC_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#if defined(LINTRCV_30_SBC_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef LINTRCV_30_SBC_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(LINTRCV_30_SBC_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef LINTRCV_30_SBC_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#if defined(LINTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_8BIT)
# undef LINTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(LINTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef LINTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined(LINTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef LINTRCV_30_SBC_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(LINTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef LINTRCV_30_SBC_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  LIN TRANSCEIVER SBC DRIVER END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANTRCV_30_TJA1040 START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined(CANTRCV_30_TJA1040_START_SEC_CODE)
# undef CANTRCV_30_TJA1040_START_SEC_CODE      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE         /* mapped to default code section */
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CODE)
# undef CANTRCV_30_TJA1040_STOP_SEC_CODE       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE          /* default code stop section */
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CODE_FAST)
# undef CANTRCV_30_TJA1040_START_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE_FAST    /* mapped to default fast code section */
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CODE_FAST)
# undef CANTRCV_30_TJA1040_STOP_SEC_CODE_FAST  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE          /* default code stop section */
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CODE_ISR)
# undef CANTRCV_30_TJA1040_START_SEC_CODE_ISR  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE_ISR     /* mapped to default ISR code section */
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CODE_ISR)
# undef CANTRCV_30_TJA1040_STOP_SEC_CODE_ISR   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE          /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_8BIT  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT     /* mapped to default const 8bit section */
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_8BIT   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST           /* default const stop section */
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_FAST_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_FAST_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_FAST_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_CONST_FAST_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* Postbuild CFG CONST sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_PBCFG)
# undef CANTRCV_30_TJA1040_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_PBCFG)
# undef CANTRCV_30_TJA1040_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_INIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT      /* mapped to default var init 8bit section */
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                /* default var stop section */
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_INIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_INIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* ESCAN00065501 */
#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_PBCFG)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_PBCFG)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST NOINIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR FAST ZERO INIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE INIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE NOINIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE ZERO INIT sections */

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1040_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  CANTRCV_30_TJA1040 END
 *********************************************************************************************************************/ /* PRQA S 0883 */ /* Appears only while testing */

/**********************************************************************************************************************
 *  CANTRCV_30_TJA1145 START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined(CANTRCV_30_TJA1145_START_SEC_CODE)
# undef CANTRCV_30_TJA1145_START_SEC_CODE      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE         /* mapped to default code section */
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CODE)
# undef CANTRCV_30_TJA1145_STOP_SEC_CODE       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE          /* default code stop section */
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CODE_FAST)
# undef CANTRCV_30_TJA1145_START_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE_FAST    /* mapped to default fast code section */
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CODE_FAST)
# undef CANTRCV_30_TJA1145_STOP_SEC_CODE_FAST  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE          /* default code stop section */
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CODE_ISR)
# undef CANTRCV_30_TJA1145_START_SEC_CODE_ISR  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE_ISR     /* mapped to default ISR code section */
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CODE_ISR)
# undef CANTRCV_30_TJA1145_STOP_SEC_CODE_ISR   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE          /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_8BIT  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT     /* mapped to default const 8bit section */
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_8BIT   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST           /* default const stop section */
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_FAST_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_FAST_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_FAST_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_CONST_FAST_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_FAST_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* Postbuild CFG CONST sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_PBCFG)
# undef CANTRCV_30_TJA1145_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_PBCFG)
# undef CANTRCV_30_TJA1145_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_INIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT      /* mapped to default var init 8bit section */
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                /* default var stop section */
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_INIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_INIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* ESCAN00065501 */
#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_PBCFG)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_PBCFG)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST NOINIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR FAST ZERO INIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE INIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE NOINIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR NOCACHE ZERO INIT sections */

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
#endif
#if defined(CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED)
# undef CANTRCV_30_TJA1145_STOP_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  CANTRCV_30_TJA1145 END
 *********************************************************************************************************************/ /* PRQA S 0883 */ /* Appears only while testing */

/**********************************************************************************************************************
 *  LIN TRANSCEIVER TLE7259 DRIVER START
 *********************************************************************************************************************/
/*******  CODE sections **********************************************************************************************/

#if defined(LINTRCV_30_TLE7259_START_SEC_CODE)
# undef LINTRCV_30_TLE7259_START_SEC_CODE      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif
#if defined(LINTRCV_30_TLE7259_STOP_SEC_CODE)
# undef LINTRCV_30_TLE7259_STOP_SEC_CODE       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(LINTRCV_30_TLE7259_START_SEC_CONST_8BIT)
# undef LINTRCV_30_TLE7259_START_SEC_CONST_8BIT  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT
#endif
#if defined(LINTRCV_30_TLE7259_STOP_SEC_CONST_8BIT)
# undef LINTRCV_30_TLE7259_STOP_SEC_CONST_8BIT   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(LINTRCV_30_TLE7259_START_SEC_CONST_32BIT)
# undef LINTRCV_30_TLE7259_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#if defined(LINTRCV_30_TLE7259_STOP_SEC_CONST_32BIT)
# undef LINTRCV_30_TLE7259_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


#if defined(LINTRCV_30_TLE7259_START_SEC_CONST_UNSPECIFIED)
# undef LINTRCV_30_TLE7259_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(LINTRCV_30_TLE7259_STOP_SEC_CONST_UNSPECIFIED)
# undef LINTRCV_30_TLE7259_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#if defined(LINTRCV_30_TLE7259_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef LINTRCV_30_TLE7259_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(LINTRCV_30_TLE7259_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef LINTRCV_30_TLE7259_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#if defined(LINTRCV_30_TLE7259_START_SEC_VAR_ZERO_INIT_8BIT)
# undef LINTRCV_30_TLE7259_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(LINTRCV_30_TLE7259_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef LINTRCV_30_TLE7259_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(LINTRCV_30_TLE7259_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef LINTRCV_30_TLE7259_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(LINTRCV_30_TLE7259_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef LINTRCV_30_TLE7259_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* PRQA S 0883 4 */ /* MD_LINTRCV_0883 */
/**********************************************************************************************************************
 *  LIN TRANSCEIVER TLE7259 DRIVER END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  WDG_30_SBC START
 *********************************************************************************************************************/
 
/******** CODE sections **********************************************************************************************/
#ifdef WDG_30_SBC_START_SEC_CODE                      
    #undef WDG_30_SBC_START_SEC_CODE	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CODE
#endif
#ifdef WDG_30_SBC_STOP_SEC_CODE
    #undef WDG_30_SBC_STOP_SEC_CODE	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CODE
#endif

/*******  CONST sections  ********************************************************************************************/
#ifdef WDG_30_SBC_START_SEC_CONST_UNSPECIFIED
    #undef WDG_30_SBC_START_SEC_CONST_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef WDG_30_SBC_STOP_SEC_CONST_UNSPECIFIED
    #undef WDG_30_SBC_STOP_SEC_CONST_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_CONST
#endif
#ifdef WDG_30_SBC_START_SEC_PBCFG_ROOT
	#undef WDG_30_SBC_START_SEC_PBCFG_ROOT	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
	#define START_SEC_CONST_PBCFG
#endif
#ifdef WDG_30_SBC_STOP_SEC_PBCFG_ROOT
	#undef WDG_30_SBC_STOP_SEC_PBCFG_ROOT	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
	#define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/
#ifdef WDG_30_SBC_START_SEC_VAR_INIT_8       /* Init variables */
    #undef WDG_30_SBC_START_SEC_VAR_INIT_8	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_INIT_8
#endif
#ifdef WDG_30_SBC_STOP_SEC_VAR_INIT_8
    #undef WDG_30_SBC_STOP_SEC_VAR_INIT_8	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR
#endif	
#ifdef WDG_30_SBC_START_SEC_VAR_CLEARED_8    /* Cleared variables */
    #undef WDG_30_SBC_START_SEC_VAR_CLEARED_8	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_CLEARED_8
#endif
#ifdef WDG_30_SBC_STOP_SEC_VAR_CLEARED_8
    #undef WDG_30_SBC_STOP_SEC_VAR_CLEARED_8	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR
#endif

#ifdef WDG_30_SBC_START_SEC_VAR_CLEARED_32
    #undef WDG_30_SBC_START_SEC_VAR_CLEARED_32	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_CLEARED_32
#endif
#ifdef WDG_30_SBC_STOP_SEC_VAR_CLEARED_32
    #undef WDG_30_SBC_STOP_SEC_VAR_CLEARED_32	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR
#endif

#ifdef WDG_30_SBC_START_SEC_VAR_INIT_UNSPECIFIED
    #undef WDG_30_SBC_START_SEC_VAR_INIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef WDG_30_SBC_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef WDG_30_SBC_STOP_SEC_VAR_INIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR
#endif
	
#ifdef WDG_30_SBC_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef WDG_30_SBC_START_SEC_VAR_CLEARED_UNSPECIFIED	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_CLEARED_UNSPECIFIED
#endif
#ifdef WDG_30_SBC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef WDG_30_SBC_STOP_SEC_VAR_CLEARED_UNSPECIFIED	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR
#endif

#ifdef WDG_30_SBC_START_SEC_VAR_NOINIT_UNSPECIFIED   /* No init variables */
    #undef WDG_30_SBC_START_SEC_VAR_NOINIT_UNSPECIFIED	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef WDG_30_SBC_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef WDG_30_SBC_STOP_SEC_VAR_NOINIT_UNSPECIFIED	 /* PRQA S 0841 */ /* MD_MSR_19.6 */
    #define STOP_SEC_VAR
#endif
/**********************************************************************************************************************
 *  WDG_30_SBC END
 *********************************************************************************************************************/
 


/**********************************************************************************************************************
 *  LINIF START
 *********************************************************************************************************************/

/* Code */
#ifdef LINIF_START_SEC_CODE
# undef LINIF_START_SEC_CODE                       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef LINIF_STOP_SEC_CODE
# undef LINIF_STOP_SEC_CODE                        /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE                             /* default code stop section */
#endif

/* Const 8 bit */
#ifdef LINIF_START_SEC_CONST_8BIT
# undef LINIF_START_SEC_CONST_8BIT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT                      /* mapped to const 8 bit section */
#endif
#ifdef LINIF_STOP_SEC_CONST_8BIT
# undef LINIF_STOP_SEC_CONST_8BIT                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const 16 bit */
#ifdef LINIF_START_SEC_CONST_16BIT
# undef LINIF_START_SEC_CONST_16BIT                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT                     /* mapped to const 16 bit section */
#endif
#ifdef LINIF_STOP_SEC_CONST_16BIT
# undef LINIF_STOP_SEC_CONST_16BIT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const 32 bit */
#ifdef LINIF_START_SEC_CONST_32BIT
# undef LINIF_START_SEC_CONST_32BIT                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT                     /* mapped to const 32 bit section */
#endif
#ifdef LINIF_STOP_SEC_CONST_32BIT
# undef LINIF_STOP_SEC_CONST_32BIT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const unspecified */
#ifdef LINIF_START_SEC_CONST_UNSPECIFIED
# undef LINIF_START_SEC_CONST_UNSPECIFIED          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED               /* mapped to const unspecified section */
#endif
#ifdef LINIF_STOP_SEC_CONST_UNSPECIFIED
# undef LINIF_STOP_SEC_CONST_UNSPECIFIED           /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Post build config unspecified */
#ifdef LINIF_START_SEC_PBCFG
# undef LINIF_START_SEC_PBCFG                      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG                     /* mapped to post build section */
#endif
#ifdef LINIF_STOP_SEC_PBCFG
# undef LINIF_STOP_SEC_PBCFG                       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default post build stop section */
#endif

/* Var noinit unspecified */
#ifdef LINIF_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef LINIF_START_SEC_VAR_NOINIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED          /* mapped to uninitialized var unspecified section */
#endif
#ifdef LINIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef LINIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default var stop section */
#endif

/* Var noinit 8 bit */
#ifdef LINIF_START_SEC_VAR_NOINIT_8BIT
# undef LINIF_START_SEC_VAR_NOINIT_8BIT            /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT                 /* mapped to uninitialized var 8 bit section */
#endif
#ifdef LINIF_STOP_SEC_VAR_NOINIT_8BIT
# undef LINIF_STOP_SEC_VAR_NOINIT_8BIT             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default var stop section */
#endif

/* Var zero init 8 bit */
#ifdef LINIF_START_SEC_VAR_ZERO_INIT_8BIT
# undef LINIF_START_SEC_VAR_ZERO_INIT_8BIT         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT              /* mapped to zero initialized var unspecified section */
#endif
#ifdef LINIF_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef LINIF_STOP_SEC_VAR_ZERO_INIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default var stop section */
#endif

/* Post build config unspecified */
#ifdef LINIF_START_SEC_VAR_PBCFG
# undef LINIF_START_SEC_VAR_PBCFG                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG                       /* mapped to post build section */
#endif
#ifdef LINIF_STOP_SEC_VAR_PBCFG
# undef LINIF_STOP_SEC_VAR_PBCFG                   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default post build stop section */
#endif

/**********************************************************************************************************************
 *  LINIF END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LINTP START
 *********************************************************************************************************************/

/* Code */
#ifdef LINTP_START_SEC_CODE
# undef LINTP_START_SEC_CODE                       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef LINTP_STOP_SEC_CODE
# undef LINTP_STOP_SEC_CODE                        /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE                             /* default code stop section */
#endif

/* Const 8 bit */
#ifdef LINTP_START_SEC_CONST_8BIT
# undef LINTP_START_SEC_CONST_8BIT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT                      /* mapped to const 8 bit section */
#endif
#ifdef LINTP_STOP_SEC_CONST_8BIT
# undef LINTP_STOP_SEC_CONST_8BIT                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const 16 bit */
#ifdef LINTP_START_SEC_CONST_16BIT
# undef LINTP_START_SEC_CONST_16BIT                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT                     /* mapped to const 16 bit section */
#endif
#ifdef LINTP_STOP_SEC_CONST_16BIT
# undef LINTP_STOP_SEC_CONST_16BIT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const 32 bit */
#ifdef LINTP_START_SEC_CONST_32BIT
# undef LINTP_START_SEC_CONST_32BIT                /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT                     /* mapped to const 32 bit section */
#endif
#ifdef LINTP_STOP_SEC_CONST_32BIT
# undef LINTP_STOP_SEC_CONST_32BIT                 /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Const unspecified */
#ifdef LINTP_START_SEC_CONST_UNSPECIFIED
# undef LINTP_START_SEC_CONST_UNSPECIFIED          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED               /* mapped to const unspecified section */
#endif
#ifdef LINTP_STOP_SEC_CONST_UNSPECIFIED
# undef LINTP_STOP_SEC_CONST_UNSPECIFIED           /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default const stop section */
#endif

/* Post build config unspecified */
#ifdef LINTP_START_SEC_PBCFG
# undef LINTP_START_SEC_PBCFG                      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG                     /* mapped to post build section */
#endif
#ifdef LINTP_STOP_SEC_PBCFG
# undef LINTP_STOP_SEC_PBCFG                       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                            /* default post build stop section */
#endif

/* Var noinit unspecified */
#ifdef LINTP_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef LINTP_START_SEC_VAR_NOINIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED          /* mapped to uninitialized var unspecified section */
#endif
#ifdef LINTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef LINTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default var stop section */
#endif

/* Var noinit 8 bit */
#ifdef LINTP_START_SEC_VAR_NOINIT_8BIT
# undef LINTP_START_SEC_VAR_NOINIT_8BIT            /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT                 /* mapped to uninitialized var 8 bit section */
#endif
#ifdef LINTP_STOP_SEC_VAR_NOINIT_8BIT
# undef LINTP_STOP_SEC_VAR_NOINIT_8BIT             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default var stop section */
#endif

/* Var zero init 8 bit */
#ifdef LINTP_START_SEC_VAR_ZERO_INIT_8BIT
# undef LINTP_START_SEC_VAR_ZERO_INIT_8BIT         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT              /* mapped to zero initialized var unspecified section */
#endif
#ifdef LINTP_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef LINTP_STOP_SEC_VAR_ZERO_INIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default var stop section */
#endif

#ifdef LINTP_START_SEC_VAR_PBCFG
# undef LINTP_START_SEC_VAR_PBCFG                  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG                       /* mapped to post build section */
#endif
#ifdef LINTP_STOP_SEC_VAR_PBCFG
# undef LINTP_STOP_SEC_VAR_PBCFG                   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                              /* default post build stop section */
#endif
/**********************************************************************************************************************
 *  LINTP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  WDGIF START
 *********************************************************************************************************************/

//#include "WdgIf_MemMap.h"

/*******  CODE sections **********************************************************************************************/

#if defined WDGIF_START_SEC_CODE
# undef WDGIF_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif
#if defined WDGIF_STOP_SEC_CODE
# undef WDGIF_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

#if defined WDGIF_START_SEC_CONST_UNSPECIFIED
# undef WDGIF_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined WDGIF_STOP_SEC_CONST_UNSPECIFIED
# undef WDGIF_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#if defined WDGIF_START_SEC_VAR_INIT_8BIT
# undef WDGIF_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_8BIT
#endif
#if defined WDGIF_STOP_SEC_VAR_INIT_8BIT
# undef WDGIF_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#if defined WDGIF_START_SEC_VAR_INIT_16BIT
# undef WDGIF_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_16BIT
#endif
#if defined WDGIF_STOP_SEC_VAR_INIT_16BIT
# undef WDGIF_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/**********************************************************************************************************************
 *  WDGIF END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  If_AsrIfEa START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef EA_START_SEC_CODE
    #undef EA_START_SEC_CODE                 /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CODE
#endif
#ifdef EA_STOP_SEC_CODE
    #undef EA_STOP_SEC_CODE                 /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef EA_START_SEC_CONST_8BIT
    #undef EA_START_SEC_CONST_8BIT          /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CONST_8BIT
#endif
#ifdef EA_STOP_SEC_CONST_8BIT
    #undef EA_STOP_SEC_CONST_8BIT          /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CONST
#endif

#ifdef EA_START_SEC_CONST_UNSPECIFIED
    #undef EA_START_SEC_CONST_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef EA_STOP_SEC_CONST_UNSPECIFIED
    #undef EA_STOP_SEC_CONST_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CONST
#endif


/*******  VAR sections  ********************************************************************************************/

/* VAR NOINIT sections */

#ifdef EA_START_SEC_VAR_NOINIT_INTERNAL_READ_BUFFER
/* Non-standard MemMap section for internal read buffer, which will be forwarded to the EEPROM driver.
 * Depending on restrictions, this buffer might have to be aligned to prevent unaligned memory access exceptions. */
# undef EA_START_SEC_VAR_NOINIT_INTERNAL_READ_BUFFER /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef EA_STOP_SEC_VAR_NOINIT_INTERNAL_READ_BUFFER
# undef EA_STOP_SEC_VAR_NOINIT_INTERNAL_READ_BUFFER /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef EA_START_SEC_VAR_NOINIT_INTERNAL_WRITE_BUFFER
/* Non-standard MemMap section for internal write buffer, which will be forwarded to the EEPROM driver.
 * Depending on restrictions, this buffer might have to be aligned to prevent unaligned memory access exceptions. */
# undef EA_START_SEC_VAR_NOINIT_INTERNAL_WRITE_BUFFER /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef EA_STOP_SEC_VAR_NOINIT_INTERNAL_WRITE_BUFFER
# undef EA_STOP_SEC_VAR_NOINIT_INTERNAL_WRITE_BUFFER /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef EA_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef EA_START_SEC_VAR_NOINIT_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef EA_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef EA_STOP_SEC_VAR_NOINIT_UNSPECIFIED          /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR
#endif

/* VAR FAST sections */

#ifdef EA_START_SEC_VAR_FAST_INIT_UNSPECIFIED
    #undef EA_START_SEC_VAR_FAST_INIT_UNSPECIFIED      /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_FAST_INIT_UNSPECIFIED
#endif
#ifdef EA_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
    #undef EA_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  If_AsrIfEa END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Com START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef COM_START_SEC_CODE
# undef COM_START_SEC_CODE
# define START_SEC_CODE
#endif
#ifdef COM_STOP_SEC_CODE
# undef COM_STOP_SEC_CODE
# define STOP_SEC_CODE
#endif
/* COM application callback code section (Rte_Cbk.h)*/
#ifdef COM_START_SEC_APPL_CODE
# undef COM_START_SEC_APPL_CODE
# define START_SEC_CODE
#endif
#ifdef COM_STOP_SEC_APPL_CODE
# undef COM_STOP_SEC_APPL_CODE
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef COM_START_SEC_CONST_8
# undef COM_START_SEC_CONST_8
# define START_SEC_CONST_8
#endif
#ifdef COM_STOP_SEC_CONST_8
# undef COM_STOP_SEC_CONST_8
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_CONST_16
# undef COM_START_SEC_CONST_16
# define START_SEC_CONST_16
#endif
#ifdef COM_STOP_SEC_CONST_16
# undef COM_STOP_SEC_CONST_16
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_CONST_32
# undef COM_START_SEC_CONST_32
# define START_SEC_CONST_32
#endif
#ifdef COM_STOP_SEC_CONST_32
# undef COM_STOP_SEC_CONST_32
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_CONST_64
# undef COM_START_SEC_CONST_64
# define START_SEC_CONST_64
#endif
#ifdef COM_STOP_SEC_CONST_64
# undef COM_STOP_SEC_CONST_64
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_CONST_UNSPECIFIED
# undef COM_START_SEC_CONST_UNSPECIFIED
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_CONST_UNSPECIFIED
# undef COM_STOP_SEC_CONST_UNSPECIFIED
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_PBCFG
# undef COM_START_SEC_PBCFG
# define START_SEC_CONST_PBCFG
#endif
#ifdef COM_STOP_SEC_PBCFG
# undef COM_STOP_SEC_PBCFG
# define STOP_SEC_CONST
#endif

#ifdef COM_START_SEC_VAR_PBCFG
# undef COM_START_SEC_VAR_PBCFG
# define START_SEC_VAR_PBCFG
#endif
#ifdef COM_STOP_SEC_VAR_PBCFG
# undef COM_STOP_SEC_VAR_PBCFG
# define STOP_SEC_VAR
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef COM_START_SEC_VAR_INIT_UNSPECIFIED
# undef COM_START_SEC_VAR_INIT_UNSPECIFIED
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef COM_STOP_SEC_VAR_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_CLEARED_UNSPECIFIED
# undef COM_START_SEC_VAR_CLEARED_UNSPECIFIED
# define START_SEC_VAR_CLEARED_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# undef COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_CLEARED_8
# undef COM_START_SEC_VAR_CLEARED_8
# define START_SEC_VAR_CLEARED_8
#endif
#ifdef COM_STOP_SEC_VAR_CLEARED_8
# undef COM_STOP_SEC_VAR_CLEARED_8
# define STOP_SEC_VAR
#endif

/* VAR NO_INIT sections */

#ifdef COM_START_SEC_VAR_NO_INIT_BOOLEAN
# undef COM_START_SEC_VAR_NO_INIT_BOOLEAN
# define START_SEC_VAR_NO_INIT_8
#endif
#ifdef COM_STOP_SEC_VAR_NO_INIT_BOOLEAN
# undef COM_STOP_SEC_VAR_NO_INIT_BOOLEAN
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NO_INIT_8
# undef COM_START_SEC_VAR_NO_INIT_8
# define START_SEC_VAR_NO_INIT_8
#endif
#ifdef COM_STOP_SEC_VAR_NO_INIT_8
# undef COM_STOP_SEC_VAR_NO_INIT_8
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NO_INIT_16
# undef COM_START_SEC_VAR_NO_INIT_16
# define START_SEC_VAR_NO_INIT_16
#endif
#ifdef COM_STOP_SEC_VAR_NO_INIT_16
# undef COM_STOP_SEC_VAR_NO_INIT_16
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NO_INIT_32
# undef COM_START_SEC_VAR_NO_INIT_32
# define START_SEC_VAR_NO_INIT_32
#endif
#ifdef COM_STOP_SEC_VAR_NO_INIT_32
# undef COM_STOP_SEC_VAR_NO_INIT_32
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NO_INIT_64
# undef COM_START_SEC_VAR_NO_INIT_64
# define START_SEC_VAR_NO_INIT_64
#endif
#ifdef COM_STOP_SEC_VAR_NO_INIT_64
# undef COM_STOP_SEC_VAR_NO_INIT_64
# define STOP_SEC_VAR
#endif

#ifdef COM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# undef COM_START_SEC_VAR_NO_INIT_UNSPECIFIED
# define START_SEC_VAR_NO_INIT_UNSPECIFIED
#endif
#ifdef COM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# undef COM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */



/* VAR FAST INIT sections */



/* VAR FAST NO_INIT sections */


/* VAR FAST ZERO INIT sections */



/**********************************************************************************************************************
 *  Com END
 *********************************************************************************************************************/


/**********************************************************************************************************************
* 3rdParty_Mcal START
*********************************************************************************************************************/

#ifdef ADC_START_SEC_CODE_ASIL_B_GLOBAL
  #undef ADC_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif
#ifdef ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_CONST_ASIL_B_GLOBAL_8
  #undef ADC_START_SEC_CONST_ASIL_B_GLOBAL_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
  #undef ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef ADC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #undef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #undef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #undef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #undef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #undef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #undef ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #undef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_CODE_ASIL_B_GLOBAL
  #undef CRC_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef CRC_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef CRC_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONST_ASIL_B_GLOBAL_16
  #undef CRC_START_SEC_CONST_ASIL_B_GLOBAL_16
  #define START_SEC_CONST_16BIT
#endif

#ifdef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_16
  #undef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_16
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef CRC_START_SEC_CONST_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONST_ASIL_B_GLOBAL_8
  #undef CRC_START_SEC_CONST_ASIL_B_GLOBAL_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
  #undef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef CRC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_CORE0_32
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_CORE0_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE0_32
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE0_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_CORE1_32
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_CORE1_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE1_32
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE1_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_CORE2_32
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_CORE2_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE2_32
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE2_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_CORE3_32
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_CORE3_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE3_32
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE3_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_CORE4_32
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_CORE4_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE4_32
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE4_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_CORE5_32
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_CORE5_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE5_32
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE5_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef CRC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef CRC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef CRC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef CRC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_8
  #undef CRC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_8
  #define START_SEC_VAR_INIT_8BIT
#endif

#ifdef CRC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_8
  #undef CRC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_8
  #define STOP_SEC_VAR
#endif

#ifdef DIO_START_SEC_CODE_ASIL_B_GLOBAL
  #undef DIO_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef DIO_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef DIO_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef DIO_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef DIO_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DIO_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef DIO_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DIO_START_SEC_CONST_ASIL_B_GLOBAL_16
  #undef DIO_START_SEC_CONST_ASIL_B_GLOBAL_16
  #define START_SEC_CONST_16BIT
#endif

#ifdef DIO_STOP_SEC_CONST_ASIL_B_GLOBAL_16
  #undef DIO_STOP_SEC_CONST_ASIL_B_GLOBAL_16
  #define STOP_SEC_CONST
#endif

#ifdef DIO_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef DIO_START_SEC_CONST_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef DIO_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef DIO_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CODE_ASIL_B_GLOBAL
  #undef DMA_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef DMA_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef DMA_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE0_256
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE0_256
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_256
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_256
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE1_256
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE1_256
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_256
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_256
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE2_256
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE2_256
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_256
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_256
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE3_256
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE3_256
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_256
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_256
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE4_256
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE4_256
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_256
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_256
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE5_256
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE5_256
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_256
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_256
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef DMA_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef DMA_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef DMA_START_SEC_CONST_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef DMA_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef DMA_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE1_8
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE1_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_8
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_8
  #define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE2_8
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE2_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_8
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_8
  #define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE3_8
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE3_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_8
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_8
  #define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE4_8
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE4_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_8
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_8
  #define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE5_8
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE5_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_8
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_8
  #define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef DMA_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef DMA_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef DMA_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #define STOP_SEC_VAR
#endif

#ifdef DSADC_START_SEC_CODE_ASIL_B_LOCAL
  #undef DSADC_START_SEC_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef DSADC_STOP_SEC_CODE_ASIL_B_LOCAL
  #undef DSADC_STOP_SEC_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef DSADC_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef DSADC_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef DSADC_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef DSADC_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef DSADC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef DSADC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef DSADC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef DSADC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define STOP_SEC_VAR
#endif

#ifdef DSADC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #undef DSADC_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef DSADC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #undef DSADC_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #define STOP_SEC_VAR
#endif

#ifdef FEE_START_SEC_CODE
  #undef FEE_START_SEC_CODE
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_CODE
  #undef FEE_STOP_SEC_CODE
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_CODE_ASIL_B_GLOBAL
  #undef FEE_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef FEE_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_CODE_ASIL_B_ILLEGALNOTIF
  #undef FEE_START_SEC_CODE_ASIL_B_ILLEGALNOTIF
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_CODE_ASIL_B_ILLEGALNOTIF
  #undef FEE_STOP_SEC_CODE_ASIL_B_ILLEGALNOTIF
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_CODE_ASIL_B_JOBENDNOTIF
  #undef FEE_START_SEC_CODE_ASIL_B_JOBENDNOTIF
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_CODE_ASIL_B_JOBENDNOTIF
  #undef FEE_STOP_SEC_CODE_ASIL_B_JOBENDNOTIF
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_CODE_ASIL_B_JOBERRNOTIF
  #undef FEE_START_SEC_CODE_ASIL_B_JOBERRNOTIF
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_CODE_ASIL_B_JOBERRNOTIF
  #undef FEE_STOP_SEC_CODE_ASIL_B_JOBERRNOTIF
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef FEE_START_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #undef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_32
  #undef FEE_START_SEC_CONST_ASIL_B_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_32
  #undef FEE_STOP_SEC_CONST_ASIL_B_32
  #define STOP_SEC_CONST
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef FEE_START_SEC_CONST_ASIL_B_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #undef FEE_STOP_SEC_CONST_ASIL_B_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef FEE_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_UNSPECIFIED
  #undef FEE_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_UNSPECIFIED
  #undef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef FEE_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef FEE_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef FEE_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif
#ifdef FEE_START_SEC_CODE_ASIL_B_LOCAL
  #undef FEE_START_SEC_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_CODE_ASIL_B_LOCAL
  #undef FEE_STOP_SEC_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef FEE_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef FEE_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef FEE_START_SEC_CONST_ASIL_B_LOCAL_32
  #undef FEE_START_SEC_CONST_ASIL_B_LOCAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef FEE_STOP_SEC_CONST_ASIL_B_LOCAL_32
  #undef FEE_STOP_SEC_CONST_ASIL_B_LOCAL_32
  #define STOP_SEC_CONST
#endif

#ifdef FEE_START_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
  #undef FEE_START_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
  #undef FEE_STOP_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
  #undef FEE_START_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
  #undef FEE_STOP_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
  #undef FEE_START_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
  #undef FEE_STOP_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
  #undef FEE_START_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
  #undef FEE_STOP_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
  #undef FEE_START_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
  #undef FEE_STOP_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define STOP_SEC_VAR
#endif

#ifdef FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef FEE_START_SEC_VAR_INIT_ASIL_B_LOCAL_8
  #undef FEE_START_SEC_VAR_INIT_ASIL_B_LOCAL_8
  #define START_SEC_VAR_INIT_8BIT
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_8
  #undef FEE_STOP_SEC_VAR_INIT_ASIL_B_LOCAL_8
  #define STOP_SEC_VAR
#endif


#ifdef FLS_17_DMU_START_SEC_CODE
  #undef FLS_17_DMU_START_SEC_CODE
  #define START_SEC_CODE
#endif

#ifdef FLS_17_DMU_STOP_SEC_CODE
  #undef FLS_17_DMU_STOP_SEC_CODE
  #define STOP_SEC_CODE
#endif

#ifdef FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
  #undef FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
  #undef FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FLS_17_DMU_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef FLS_17_DMU_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef FLS_17_DMU_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef FLS_17_DMU_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define STOP_SEC_VAR
#endif

#ifdef FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef FLSLOADER_START_SEC_BUSYLOOP_CALLOUT_CODE_QM_LOCAL
  #undef FLSLOADER_START_SEC_BUSYLOOP_CALLOUT_CODE_QM_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FLSLOADER_STOP_SEC_BUSYLOOP_CALLOUT_CODE_QM_LOCAL
  #undef FLSLOADER_STOP_SEC_BUSYLOOP_CALLOUT_CODE_QM_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FLSLOADER_START_SEC_CODE_QM_LOCAL
  #undef FLSLOADER_START_SEC_CODE_QM_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FLSLOADER_STOP_SEC_CODE_QM_LOCAL
  #undef FLSLOADER_STOP_SEC_CODE_QM_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef FLSLOADER_START_SEC_CONST_QM_LOCAL_32
  #undef FLSLOADER_START_SEC_CONST_QM_LOCAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
  #undef FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
  #define STOP_SEC_CONST
#endif

#ifdef FLSLOADER_START_SEC_CONST_QM_LOCAL_8
  #undef FLSLOADER_START_SEC_CONST_QM_LOCAL_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef FLSLOADER_STOP_SEC_CONST_QM_LOCAL_8
  #undef FLSLOADER_STOP_SEC_CONST_QM_LOCAL_8
  #define STOP_SEC_CONST
#endif

#ifdef FLSLOADER_START_SEC_VAR_CLEARED_QM_LOCAL_32
  #undef FLSLOADER_START_SEC_VAR_CLEARED_QM_LOCAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef FLSLOADER_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
  #undef FLSLOADER_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
  #define STOP_SEC_VAR
#endif

#ifdef FLSLOADER_START_SEC_VAR_CLEARED_QM_LOCAL_8
  #undef FLSLOADER_START_SEC_VAR_CLEARED_QM_LOCAL_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef FLSLOADER_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
  #undef FLSLOADER_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
  #define STOP_SEC_VAR
#endif

#ifdef FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
  #undef FLSLOADER_START_SEC_WRITEERASE_CODE_QM_LOCAL
  #define START_SEC_CODE
#endif

#ifdef FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
  #undef FLSLOADER_STOP_SEC_WRITEERASE_CODE_QM_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_CODE_ASIL_B_GLOBAL
  #undef GPT_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef GPT_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define START_SEC_CODE_FAST
#endif

#ifdef GPT_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef GPT_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef GPT_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef GPT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef GPT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_CORE0_8
  #undef GPT_START_SEC_CONST_ASIL_B_CORE0_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_CORE0_8
  #undef GPT_STOP_SEC_CONST_ASIL_B_CORE0_8
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_CORE1_8
  #undef GPT_START_SEC_CONST_ASIL_B_CORE1_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_CORE1_8
  #undef GPT_STOP_SEC_CONST_ASIL_B_CORE1_8
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_CORE2_8
  #undef GPT_START_SEC_CONST_ASIL_B_CORE2_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_CORE2_8
  #undef GPT_STOP_SEC_CONST_ASIL_B_CORE2_8
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_CORE3_8
  #undef GPT_START_SEC_CONST_ASIL_B_CORE3_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_CORE3_8
  #undef GPT_STOP_SEC_CONST_ASIL_B_CORE3_8
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_CORE4_8
  #undef GPT_START_SEC_CONST_ASIL_B_CORE4_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_CORE4_8
  #undef GPT_STOP_SEC_CONST_ASIL_B_CORE4_8
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_CORE5_8
  #undef GPT_START_SEC_CONST_ASIL_B_CORE5_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_CORE5_8
  #undef GPT_STOP_SEC_CONST_ASIL_B_CORE5_8
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef GPT_START_SEC_CONST_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef GPT_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef GPT_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef GPT_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_8
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef GPT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef GPT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_CORE0_UNSPECIFIED
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE0_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_CORE1_UNSPECIFIED
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE1_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_CORE2_UNSPECIFIED
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE2_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_CORE3_UNSPECIFIED
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE3_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_CORE4_UNSPECIFIED
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE4_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_CORE5_UNSPECIFIED
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE5_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef GPT_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef GPT_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef GPT_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef GPT_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
  #undef ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef ICU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef ICU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef ICU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef ICU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE0_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE0_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE0_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE0_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE1_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE1_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE1_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE1_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE2_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE2_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE2_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE2_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE3_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE3_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE3_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE3_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE4_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE4_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE4_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE4_32
  #define STOP_SEC_VAR
#endif

#ifdef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE5_32
  #undef ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE5_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE5_32
  #undef ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE5_32
  #define STOP_SEC_VAR
#endif

#ifdef IRQ_START_SEC_CODE
  #undef IRQ_START_SEC_CODE
  #define START_SEC_CODE
#endif

#ifdef IRQ_STOP_SEC_CODE
  #undef IRQ_STOP_SEC_CODE
  #define STOP_SEC_CODE
#endif

#ifdef IRQ_START_SEC_CODE_QM_GLOBAL
  #undef IRQ_START_SEC_CODE_QM_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef IRQ_STOP_SEC_CODE_QM_GLOBAL
  #undef IRQ_STOP_SEC_CODE_QM_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef MCALLIB_START_SEC_CODE_ASIL_B_GLOBAL
  #undef MCALLIB_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef MCALLIB_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef MCALLIB_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_8
  #undef MCALLIB_START_SEC_CONST_ASIL_B_GLOBAL_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_8
  #undef MCALLIB_STOP_SEC_CONST_ASIL_B_GLOBAL_8
  #define STOP_SEC_CONST
#endif

#ifdef MCALLIB_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #pragma align 4
  #undef MCALLIB_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef MCALLIB_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #pragma align restore
  #undef MCALLIB_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef MCU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
  #undef MCU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef MCU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef MCU_17_TIMERIP_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef MCU_17_TIMERIP_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define START_SEC_CODE_FAST
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef MCU_17_TIMERIP_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  #undef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  #define START_SEC_CONST_16BIT
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  #undef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
  #define STOP_SEC_CONST
#endif

#ifdef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_8
  #undef MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_8
  #undef MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_8
  #define STOP_SEC_CONST
#endif

#ifdef MCU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MCU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MCU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef MCU_START_SEC_CODE_ASIL_B_GLOBAL
  #undef MCU_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef MCU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef MCU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef MCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef MCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef OCU_START_SEC_CODE_ASIL_B_GLOBAL
  #undef OCU_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef OCU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef OCU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef OCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef OCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_CONST_ASIL_B_GLOBAL_32
  #undef OCU_START_SEC_CONST_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef OCU_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #undef OCU_STOP_SEC_CONST_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define STOP_SEC_VAR
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define STOP_SEC_VAR
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define STOP_SEC_VAR
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define STOP_SEC_VAR
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define STOP_SEC_VAR
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define STOP_SEC_VAR
#endif

#ifdef OCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef OCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef OCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef PORT_START_SEC_CODE_ASIL_B_GLOBAL
  #undef PORT_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef PORT_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef PORT_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PORT_START_SEC_CONST_ASIL_B_GLOBAL_16
  #undef PORT_START_SEC_CONST_ASIL_B_GLOBAL_16
  #define START_SEC_CONST_16BIT
#endif

#ifdef PORT_STOP_SEC_CONST_ASIL_B_GLOBAL_16
  #undef PORT_STOP_SEC_CONST_ASIL_B_GLOBAL_16
  #define STOP_SEC_CONST
#endif

#ifdef PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef PORT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef PORT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CODE_ASIL_B_GLOBAL
  #undef PWM_17_GTMCCU6_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef PWM_17_GTMCCU6_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef PWM_17_GTMCCU6_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define START_SEC_CODE_FAST
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef PWM_17_GTMCCU6_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
  #define STOP_SEC_VAR
#endif

#ifdef PWM_17_GTMCCU6_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PWM_17_GTMCCU6_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef PWM_17_GTMCCU6_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef PWM_17_GTMCCU6_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef SMU_START_SEC_CODE_ASIL_B_GLOBAL
  #undef SMU_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef SMU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef SMU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef SMU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef SMU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef SMU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef SMU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef SMU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef SMU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_INIT_32BIT
#endif

#ifdef SMU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #undef SMU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_CODE
  #undef SPI_START_SEC_CODE
  #define START_SEC_CODE
#endif

#ifdef SPI_STOP_SEC_CODE
  #undef SPI_STOP_SEC_CODE
  #define STOP_SEC_CODE
#endif

#ifdef SPI_START_SEC_CODE_ASIL_B_GLOBAL
  #undef SPI_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef SPI_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef SPI_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE0_32
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE0_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_32
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_32
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE1_32
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE1_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_32
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_32
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE2_32
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE2_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_32
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_32
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE3_32
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE3_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_32
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_32
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE4_32
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE4_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_32
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_32
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE5_32
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_CORE5_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_32
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_32
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef SPI_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #undef SPI_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
  #define STOP_SEC_VAR
#endif

#ifdef SPI_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef SPI_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef SPI_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef UART_START_SEC_CODE
  #undef UART_START_SEC_CODE
  #define START_SEC_CODE
#endif

#ifdef UART_STOP_SEC_CODE
  #undef UART_STOP_SEC_CODE
  #define STOP_SEC_CODE
#endif

#ifdef UART_START_SEC_CODE_ASIL_B_LOCAL
  #undef UART_START_SEC_CODE_ASIL_B_LOCAL
  #define START_SEC_CODE
#endif

#ifdef UART_STOP_SEC_CODE_ASIL_B_LOCAL
  #undef UART_STOP_SEC_CODE_ASIL_B_LOCAL
  #define STOP_SEC_CODE
#endif

#ifdef UART_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef UART_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef UART_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #undef UART_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef UART_START_SEC_CONST_ASIL_B_LOCAL_32
  #undef UART_START_SEC_CONST_ASIL_B_LOCAL_32
  #define START_SEC_CONST_32BIT
#endif

#ifdef UART_STOP_SEC_CONST_ASIL_B_LOCAL_32
  #undef UART_STOP_SEC_CONST_ASIL_B_LOCAL_32
  #define STOP_SEC_CONST
#endif

#ifdef UART_START_SEC_CONST_ASIL_B_LOCAL_8
  #undef UART_START_SEC_CONST_ASIL_B_LOCAL_8
  #define START_SEC_CONST_8BIT
#endif

#ifdef UART_STOP_SEC_CONST_ASIL_B_LOCAL_8
  #undef UART_STOP_SEC_CONST_ASIL_B_LOCAL_8
  #define STOP_SEC_CONST
#endif

#ifdef UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #undef UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
  #define STOP_SEC_VAR
#endif

#ifdef UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #undef UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #define START_SEC_VAR_ZERO_INIT_8BIT
#endif

#ifdef UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #undef UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
  #define STOP_SEC_VAR
#endif

#ifdef UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #undef UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_CODE_ASIL_B_GLOBAL
  #undef WDG_17_SCU_START_SEC_CODE_ASIL_B_GLOBAL
  #define START_SEC_CODE
#endif

#ifdef WDG_17_SCU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #undef WDG_17_SCU_STOP_SEC_CODE_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef WDG_17_SCU_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef WDG_17_SCU_START_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define START_SEC_CODE_FAST
#endif

#ifdef WDG_17_SCU_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #undef WDG_17_SCU_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
  #define STOP_SEC_CODE
#endif

#ifdef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef WDG_17_SCU_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_CONST_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_CONST
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define START_SEC_VAR_ZERO_INIT_32BIT
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #undef WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
  #define STOP_SEC_VAR
#endif

#ifdef WDG_17_SCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef WDG_17_SCU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef WDG_17_SCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #undef WDG_17_SCU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_UNSPECIFIED
  #define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
* 3rdParty_Mcal END
*********************************************************************************************************************/



/**********************************************************************************************************************
 *  DBG START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef DBG_START_SEC_CODE
  #undef DBG_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CODE                            /* mapped to default code section */
#endif
#ifdef DBG_STOP_SEC_CODE
  #undef DBG_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

#ifdef DBG_START_SEC_CODE_FAST
  #undef DBG_START_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define START_SEC_CODE_FAST                       /* mapped to default fast code section */
#endif
#ifdef DBG_STOP_SEC_CODE_FAST
  #undef DBG_STOP_SEC_CODE_FAST /* PRQA S 0841 */ /* MD_MSR_Undef */
  #define STOP_SEC_CODE                             /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef DBG_START_SEC_CONST_8BIT
# undef DBG_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT                       /* mapped to default const 8bit section */
#endif
#ifdef DBG_STOP_SEC_CONST_8BIT
# undef DBG_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                             /* default const stop section */
#endif

#ifdef DBG_START_SEC_CONST_16BIT
# undef DBG_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#ifdef DBG_STOP_SEC_CONST_16BIT
# undef DBG_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef DBG_START_SEC_CONST_32BIT
# undef DBG_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#ifdef DBG_STOP_SEC_CONST_32BIT
# undef DBG_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef DBG_START_SEC_CONST_UNSPECIFIED
# undef DBG_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef DBG_STOP_SEC_CONST_UNSPECIFIED
# undef DBG_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef DBG_START_SEC_VAR_INIT_8BIT
# undef DBG_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT                    /* mapped to default var init 8bit section */
#endif
#ifdef DBG_STOP_SEC_VAR_INIT_8BIT
# undef DBG_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR                               /* default var stop section */
#endif

#ifdef DBG_START_SEC_VAR_INIT_16BIT
# undef DBG_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#ifdef DBG_STOP_SEC_VAR_INIT_16BIT
# undef DBG_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_INIT_32BIT
# undef DBG_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#ifdef DBG_STOP_SEC_VAR_INIT_32BIT
# undef DBG_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_INIT_UNSPECIFIED
# undef DBG_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef DBG_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef DBG_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef DBG_START_SEC_VAR_NOINIT_8BIT
# undef DBG_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef DBG_STOP_SEC_VAR_NOINIT_8BIT
# undef DBG_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_NOINIT_16BIT
# undef DBG_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef DBG_STOP_SEC_VAR_NOINIT_16BIT
# undef DBG_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_NOINIT_32BIT
# undef DBG_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#ifdef DBG_STOP_SEC_VAR_NOINIT_32BIT
# undef DBG_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef DBG_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef DBG_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef DBG_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef DBG_START_SEC_VAR_ZERO_INIT_8BIT
# undef DBG_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef DBG_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef DBG_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_ZERO_INIT_16BIT
# undef DBG_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_16BIT
#endif
#ifdef DBG_STOP_SEC_VAR_ZERO_INIT_16BIT
# undef DBG_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_ZERO_INIT_32BIT
# undef DBG_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#ifdef DBG_STOP_SEC_VAR_ZERO_INIT_32BIT
# undef DBG_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DBG_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef DBG_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef DBG_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef DBG_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif



/**********************************************************************************************************************
 *  DBG END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  J1939NM START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef J1939NM_START_SEC_CODE
# undef J1939NM_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE /* mapped to default code section */
#endif
#ifdef J1939NM_STOP_SEC_CODE
# undef J1939NM_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef J1939NM_START_SEC_CONST_8BIT
# undef J1939NM_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT /* mapped to default const 8bit section */
#endif
#ifdef J1939NM_STOP_SEC_CONST_8BIT
# undef J1939NM_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST /* default const stop section */
#endif

#ifdef J1939NM_START_SEC_CONST_16BIT
# undef J1939NM_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#ifdef J1939NM_STOP_SEC_CONST_16BIT
# undef J1939NM_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef J1939NM_START_SEC_CONST_32BIT
# undef J1939NM_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#ifdef J1939NM_STOP_SEC_CONST_32BIT
# undef J1939NM_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef J1939NM_START_SEC_CONST_UNSPECIFIED
# undef J1939NM_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef J1939NM_STOP_SEC_CONST_UNSPECIFIED
# undef J1939NM_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */


/* Postbuild CFG CONST sections */

#ifdef J1939NM_START_SEC_PBCFG
# undef J1939NM_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef J1939NM_STOP_SEC_PBCFG
# undef J1939NM_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef J1939NM_START_SEC_VAR_ZERO_INIT_8BIT
# undef J1939NM_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef J1939NM_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef J1939NM_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef J1939NM_START_SEC_VAR_NOINIT_8BIT
# undef J1939NM_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef J1939NM_STOP_SEC_VAR_NOINIT_8BIT
# undef J1939NM_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef J1939NM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef J1939NM_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef J1939NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef J1939NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef J1939NM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef J1939NM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef J1939NM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef J1939NM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */


/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */


/* Postbuild CFG VAR sections */

#ifdef J1939NM_START_SEC_VAR_PBCFG
# undef J1939NM_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#ifdef J1939NM_STOP_SEC_VAR_PBCFG
# undef J1939NM_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  J1939NM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANNM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef CANNM_START_SEC_CODE
    #undef CANNM_START_SEC_CODE                         /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_CODE                              /* mapped to default code section */
#endif
#ifdef CANNM_STOP_SEC_CODE
    #undef CANNM_STOP_SEC_CODE                          /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_CODE                               /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef CANNM_START_SEC_CONST_8BIT
    #undef CANNM_START_SEC_CONST_8BIT                   /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_CONST_8BIT                        /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_8BIT
    #undef CANNM_STOP_SEC_CONST_8BIT                    /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef CANNM_START_SEC_CONST_UNSPECIFIED
    #undef CANNM_START_SEC_CONST_UNSPECIFIED            /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_CONST_UNSPECIFIED                 /* mapped to default const section */
#endif
#ifdef CANNM_STOP_SEC_CONST_UNSPECIFIED
    #undef CANNM_STOP_SEC_CONST_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/* Postbuild CFG CONST sections */

#ifdef CANNM_START_SEC_PBCFG
    #undef CANNM_START_SEC_PBCFG                        /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_CONST_PBCFG                       /* mapped to default postbuild section */
#endif
#ifdef CANNM_STOP_SEC_PBCFG
    #undef CANNM_STOP_SEC_PBCFG                         /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef CANNM_START_SEC_VAR_NOINIT_8BIT
    #undef CANNM_START_SEC_VAR_NOINIT_8BIT              /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_VAR_NOINIT_8BIT                   /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_8BIT
    #undef CANNM_STOP_SEC_VAR_NOINIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_NOINIT_16BIT
    #undef CANNM_START_SEC_VAR_NOINIT_16BIT              /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_VAR_NOINIT_16BIT                   /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_16BIT
    #undef CANNM_STOP_SEC_VAR_NOINIT_16BIT               /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_NOINIT_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED            /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR INIT sections */
#ifdef CANNM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_INIT_UNSPECIFIED         /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_VAR_INIT_UNSPECIFIED              /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_INIT_UNSPECIFIED          /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef CANNM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
    #undef CANNM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED    /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_VAR_ZERO_INIT_UNSPECIFIED         /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
    #undef CANNM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif


#ifdef CANNM_START_SEC_VAR_ZERO_INIT_8BIT
    #undef CANNM_START_SEC_VAR_ZERO_INIT_8BIT              /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_VAR_ZERO_INIT_8BIT                   /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_ZERO_INIT_8BIT
    #undef CANNM_STOP_SEC_VAR_ZERO_INIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR PBCFG sections */

#ifdef CANNM_START_SEC_VAR_PBCFG
    #undef CANNM_START_SEC_VAR_PBCFG                    /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define START_SEC_VAR_PBCFG                         /* mapped to default var section */
#endif
#ifdef CANNM_STOP_SEC_VAR_PBCFG
    #undef CANNM_STOP_SEC_VAR_PBCFG                     /* PRQA S 0841 */ /* MD_MSR_Rule20.5 */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/**********************************************************************************************************************
 *  CANNM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LINNM START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef LINNM_START_SEC_CODE
    #undef LINNM_START_SEC_CODE                         /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CODE                              /* mapped to default code section */
#endif
#ifdef LINNM_STOP_SEC_CODE
    #undef LINNM_STOP_SEC_CODE                          /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CODE                               /*default code stop section*/
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef LINNM_START_SEC_CONST_8BIT
    #undef LINNM_START_SEC_CONST_8BIT                   /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CONST_8BIT                        /* mapped to default const section */
#endif
#ifdef LINNM_STOP_SEC_CONST_8BIT
    #undef LINNM_STOP_SEC_CONST_8BIT                    /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef LINNM_START_SEC_CONST_32BIT
    #undef LINNM_START_SEC_CONST_32BIT                  /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CONST_32BIT                       /* mapped to default const section */
#endif
#ifdef LINNM_STOP_SEC_CONST_32BIT
    #undef LINNM_STOP_SEC_CONST_32BIT                   /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef LINNM_START_SEC_CONST_UNSPECIFIED
    #undef LINNM_START_SEC_CONST_UNSPECIFIED            /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CONST_UNSPECIFIED                 /* mapped to default const section */
#endif
#ifdef LINNM_STOP_SEC_CONST_UNSPECIFIED
    #undef LINNM_STOP_SEC_CONST_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/* Postbuild CFG CONST sections */

#ifdef LINNM_START_SEC_PBCFG
    #undef LINNM_START_SEC_PBCFG                        /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CONST_PBCFG                       /* mapped to default postbuild section */
#endif
#ifdef LINNM_STOP_SEC_PBCFG
    #undef LINNM_STOP_SEC_PBCFG                         /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

#ifdef LINNM_START_SEC_PBCFG_ROOT
    #undef LINNM_START_SEC_PBCFG_ROOT                   /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_CONST_PBCFG                       /* mapped to default postbuild section */
#endif
#ifdef LINNM_STOP_SEC_PBCFG_ROOT
    #undef LINNM_STOP_SEC_PBCFG_ROOT                    /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_CONST                              /* default const stop section */
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#ifdef LINNM_START_SEC_VAR_NOINIT_8BIT
    #undef LINNM_START_SEC_VAR_NOINIT_8BIT              /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_NOINIT_8BIT                   /* mapped to default var section */
#endif
#ifdef LINNM_STOP_SEC_VAR_NOINIT_8BIT
    #undef LINNM_STOP_SEC_VAR_NOINIT_8BIT               /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef LINNM_START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef LINNM_START_SEC_VAR_NOINIT_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_NOINIT_UNSPECIFIED            /* mapped to default var section */
#endif
#ifdef LINNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef LINNM_STOP_SEC_VAR_NOINIT_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR FAST NOINIT sections */

#ifdef LINNM_START_SEC_VAR_FAST_NOINIT_8BIT
    #undef LINNM_START_SEC_VAR_FAST_NOINIT_8BIT         /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_FAST_NOINIT_8BIT              /* mapped to default var section */
#endif
#ifdef LINNM_STOP_SEC_VAR_FAST_NOINIT_8BIT
    #undef LINNM_STOP_SEC_VAR_FAST_NOINIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef LINNM_START_SEC_VAR_FAST_NOINIT_16BIT
    #undef LINNM_START_SEC_VAR_FAST_NOINIT_16BIT        /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_FAST_NOINIT_16BIT             /* mapped to default var section */
#endif
#ifdef LINNM_STOP_SEC_VAR_FAST_NOINIT_16BIT
    #undef LINNM_STOP_SEC_VAR_FAST_NOINIT_16BIT         /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef LINNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef LINNM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED       /* mapped to default var section */
#endif
#ifdef LINNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef LINNM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

/* VAR FAST ZERO INIT sections */

#ifdef LINNM_START_SEC_VAR_FAST_ZERO_INIT_8BIT
    #undef LINNM_START_SEC_VAR_FAST_ZERO_INIT_8BIT      /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_FAST_ZERO_INIT_8BIT           /* mapped to default var section */
#endif
#ifdef LINNM_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT
    #undef LINNM_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT       /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR                                /* default var stop section */
#endif

#ifdef LINNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef LINNM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED       /* mapped to default var section */
#endif
#ifdef LINNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
    #undef LINNM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_Undef */
    #define STOP_SEC_VAR                                   /* default var stop section */
#endif

/**********************************************************************************************************************
 *  LINNM END
 *********************************************************************************************************************/

/** FiM **********************************************************************/

/*---------------------START-MODULE-SPECIFIC-START-SECTIONS------------------*/

/* Memory Section Group 'Constant' */

#ifdef FIM_START_SEC_CODE
# undef FIM_START_SEC_CODE                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE                                 /* mapped to default code section */
#endif

#ifdef FIM_START_SEC_CONST_8BIT
# undef FIM_START_SEC_CONST_8BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                          /* mapped to default const section */
#endif

#ifdef FIM_START_SEC_CONST_16BIT
# undef FIM_START_SEC_CONST_16BIT                        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT                          /* mapped to default const section */
#endif

#ifdef FIM_START_SEC_CONST_UNSPECIFIED
# undef FIM_START_SEC_CONST_UNSPECIFIED                  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED                   /* mapped to default const section */
#endif

#ifdef FIM_START_SEC_PBCFG
# undef FIM_START_SEC_PBCFG                              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                         /* mapped to default const section */
#endif

#ifdef FIM_START_SEC_PBCFG_ROOT
# undef FIM_START_SEC_PBCFG_ROOT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG                         /* mapped to default const section */
#endif


/* Memory Section Group 'Master' */

#ifdef FIM_START_SEC_VAR_NOINIT_16BIT
# undef FIM_START_SEC_VAR_NOINIT_16BIT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_16BIT                      /* mapped to default var section */
#endif

#ifdef FIM_START_SEC_VAR_NOINIT_32BIT
# undef FIM_START_SEC_VAR_NOINIT_32BIT                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_32BIT                      /* mapped to default var section */
#endif

#ifdef FIM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef FIM_START_SEC_VAR_NOINIT_UNSPECIFIED             /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED                /* mapped to default var section */
#endif

#ifdef FIM_START_SEC_VAR_INIT_8BIT
# undef FIM_START_SEC_VAR_INIT_8BIT                      /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_8BIT                         /* mapped to default var section */
#endif


/* Memory Section Group 'MasterSatAll' */

#ifdef FIM_START_SEC_MASTERSAT_ALL_VAR_NOINIT_32BIT
# undef FIM_START_SEC_MASTERSAT_ALL_VAR_NOINIT_32BIT     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_32BIT                      /* mapped to default var section */
#endif


/* Memory Section Group 'Restricted' */

#ifdef FIM_START_SEC_VAR_NOINIT_16BIT_RESTRICTED
# undef FIM_START_SEC_VAR_NOINIT_16BIT_RESTRICTED        /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_16BIT                      /* mapped to default var section */
#endif

#ifdef FIM_START_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED
# undef FIM_START_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED  /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED                /* mapped to default var section */
#endif

#ifdef FIM_START_SEC_VAR_INIT_8BIT_RESTRICTED
# undef FIM_START_SEC_VAR_INIT_8BIT_RESTRICTED           /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_8BIT                         /* mapped to default var section */
#endif



/*---------------------STOP-MODULE-SPECIFIC-START-SECTIONS-------------------*/

/*---------------------START-MODULE-SPECIFIC-STOP-SECTIONS-------------------*/

/* Memory Section Group 'Constant' */

#ifdef FIM_STOP_SEC_CODE
# undef FIM_STOP_SEC_CODE                                /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE                                  /* mapped to default code section */
#endif

#ifdef FIM_STOP_SEC_CONST_8BIT
# undef FIM_STOP_SEC_CONST_8BIT                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                /* mapped to default const section */
#endif

#ifdef FIM_STOP_SEC_CONST_16BIT
# undef FIM_STOP_SEC_CONST_16BIT                         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                /* mapped to default const section */
#endif

#ifdef FIM_STOP_SEC_CONST_UNSPECIFIED
# undef FIM_STOP_SEC_CONST_UNSPECIFIED                   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                /* mapped to default const section */
#endif

#ifdef FIM_STOP_SEC_PBCFG
# undef FIM_STOP_SEC_PBCFG                               /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                  /* mapped to default const section */
#endif

#ifdef FIM_STOP_SEC_PBCFG_ROOT
# undef FIM_STOP_SEC_PBCFG_ROOT                          /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST                                  /* mapped to default const section */
#endif


/* Memory Section Group 'Master' */

#ifdef FIM_STOP_SEC_VAR_NOINIT_16BIT
# undef FIM_STOP_SEC_VAR_NOINIT_16BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                    /* mapped to default var section */
#endif

#ifdef FIM_STOP_SEC_VAR_NOINIT_32BIT
# undef FIM_STOP_SEC_VAR_NOINIT_32BIT                    /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                    /* mapped to default var section */
#endif

#ifdef FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED              /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                    /* mapped to default var section */
#endif

#ifdef FIM_STOP_SEC_VAR_INIT_8BIT
# undef FIM_STOP_SEC_VAR_INIT_8BIT                       /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                    /* mapped to default var section */
#endif


/* Memory Section Group 'MasterSatAll' */

#ifdef FIM_STOP_SEC_MASTERSAT_ALL_VAR_NOINIT_32BIT
# undef FIM_STOP_SEC_MASTERSAT_ALL_VAR_NOINIT_32BIT     /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                   /* mapped to default var section */
#endif


/* Memory Section Group 'Restricted' */

#ifdef FIM_STOP_SEC_VAR_NOINIT_16BIT_RESTRICTED
# undef FIM_STOP_SEC_VAR_NOINIT_16BIT_RESTRICTED         /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                    /* mapped to default var section */
#endif

#ifdef FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED
# undef FIM_STOP_SEC_VAR_NOINIT_UNSPECIFIED_RESTRICTED   /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                    /* mapped to default var section */
#endif

#ifdef FIM_STOP_SEC_VAR_INIT_8BIT_RESTRICTED
# undef FIM_STOP_SEC_VAR_INIT_8BIT_RESTRICTED            /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR                                    /* mapped to default var section */
#endif


//#include "FiM_MemMap.h"

/*---------------------STOP-MODULE-SPECIFIC-STOP-SECTIONS--------------------*/

/** End of FiM ***************************************************************/



/**********************************************************************************************************************
 *  WDGM START
 *********************************************************************************************************************/

//#include "WdgM_OsMemMap.h"

/*******  CODE sections **********************************************************************************************/

#if defined WDGM_START_SEC_CODE
# undef WDGM_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif
#if defined WDGM_STOP_SEC_CODE
# undef WDGM_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif

#if defined(WDGM_START_SEC_APPL_CODE)
# undef WDGM_START_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif
#if defined(WDGM_STOP_SEC_APPL_CODE)
# undef WDGM_STOP_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif


/*******  CONST sections  ********************************************************************************************/

#if defined WDGM_START_SEC_CONST_8BIT
# undef WDGM_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT
#endif
#if defined WDGM_STOP_SEC_CONST_8BIT
# undef WDGM_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined WDGM_START_SEC_CONST_16BIT
# undef WDGM_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#if defined WDGM_STOP_SEC_CONST_16BIT
# undef WDGM_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined WDGM_START_SEC_CONST_32BIT
# undef WDGM_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#if defined WDGM_STOP_SEC_CONST_32BIT
# undef WDGM_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined WDGM_START_SEC_CONST_UNSPECIFIED
# undef WDGM_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined WDGM_STOP_SEC_CONST_UNSPECIFIED
# undef WDGM_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#if defined WDGM_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef WDGM_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined WDGM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef WDGM_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined WDGM_START_SEC_VAR_NOINIT_8BIT
# undef WDGM_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined WDGM_STOP_SEC_VAR_NOINIT_8BIT
# undef WDGM_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined WDGM_START_SEC_VAR_NOINIT_16BIT
# undef WDGM_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#if defined WDGM_STOP_SEC_VAR_NOINIT_16BIT
# undef WDGM_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined WDGM_START_SEC_VAR_NOINIT_32BIT
# undef WDGM_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_32BIT
#endif
#if defined WDGM_STOP_SEC_VAR_NOINIT_32BIT
# undef WDGM_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#if defined(WDGM_START_SEC_VAR_CLEARED_32BIT)
# undef WDGM_START_SEC_VAR_CLEARED_32BIT   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_32BIT
#endif
#if defined(WDGM_STOP_SEC_VAR_CLEARED_32BIT)
# undef WDGM_STOP_SEC_VAR_CLEARED_32BIT    /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR INIT sections */

#if defined WDGM_START_SEC_VAR_32BIT
# undef WDGM_START_SEC_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_32BIT
#endif
#if defined WDGM_STOP_SEC_VAR_32BIT
# undef WDGM_STOP_SEC_VAR_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* Global Shared Variables of the WdgM.
 * If a SafeContext OS is used this section will be defined by the OS.
 * If no SafeContext OS is used this section has to be mapped to a memory area where all SWCs has access
 */
/*#if defined GlobalShared_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef GlobalShared_START_SEC_VAR_NOINIT_UNSPECIFIED*/ /* PRQA S 0841 */ /* MD_MSR_Undef */
/*# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined GlobalShared_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef GlobalShared_STOP_SEC_VAR_NOINIT_UNSPECIFIED*/ /* PRQA S 0841 */ /* MD_MSR_Undef */
/*# define STOP_SEC_VAR
#endif*/
/* or the following section (depending on which OS version is used) */
/*#if defined OS_START_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED
# undef OS_START_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED*/ /* PRQA S 0841 */ /* MD_MSR_Undef */
/*# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED
# undef OS_STOP_SEC_GLOBALSHARED_VAR_NOINIT_UNSPECIFIED*/ /* PRQA S 0841 */ /* MD_MSR_Undef */
/*# define STOP_SEC_VAR
#endif*/
 
/**********************************************************************************************************************
 *  WDGM END
 *********************************************************************************************************************/

#ifdef DET_START_SEC_CODE
# undef DET_START_SEC_CODE                    /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE
#endif
#ifdef DET_STOP_SEC_CODE
# undef DET_STOP_SEC_CODE                     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif

#ifdef DET_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef DET_START_SEC_VAR_NOINIT_UNSPECIFIED  /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef DET_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef DET_STOP_SEC_VAR_NOINIT_UNSPECIFIED   /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DET_START_SEC_VAR_NOINIT_8BIT
# undef DET_START_SEC_VAR_NOINIT_8BIT         /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef DET_STOP_SEC_VAR_NOINIT_8BIT
# undef DET_STOP_SEC_VAR_NOINIT_8BIT          /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DET_START_SEC_VAR_INIT_UNSPECIFIED
# undef DET_START_SEC_VAR_INIT_UNSPECIFIED    /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif
#ifdef DET_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef DET_STOP_SEC_VAR_INIT_UNSPECIFIED     /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef DET_START_SEC_CONST_UNSPECIFIED
# undef DET_START_SEC_CONST_UNSPECIFIED       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef DET_STOP_SEC_CONST_UNSPECIFIED
# undef DET_STOP_SEC_CONST_UNSPECIFIED        /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/**********************************************************************************************************************
 *  STBM START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined(STBM_START_SEC_CODE)
# undef STBM_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE /* mapped to default code section */
#endif
#if defined(STBM_STOP_SEC_CODE)
# undef STBM_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE  /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(STBM_START_SEC_CONST_UNSPECIFIED)
# undef STBM_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(STBM_STOP_SEC_CONST_UNSPECIFIED)
# undef STBM_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(STBM_START_SEC_CONST_8BIT)
# undef STBM_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT
#endif
#if defined(STBM_STOP_SEC_CONST_8BIT)
# undef STBM_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#if defined(STBM_START_SEC_VAR_NOINIT_8BIT)
# undef STBM_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined(STBM_STOP_SEC_VAR_NOINIT_8BIT)
# undef STBM_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(STBM_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef STBM_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef STBM_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#if defined(STBM_START_SEC_VAR_ZERO_INIT_8BIT)
# undef STBM_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(STBM_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef STBM_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(STBM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef STBM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#if defined(STBM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)
# undef STBM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  STBM END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  CANTSYN START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#if defined(CANTSYN_START_SEC_CODE)
# undef CANTSYN_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE          /* mapped to default code section */
#endif
#if defined(CANTSYN_STOP_SEC_CODE)
# undef CANTSYN_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE           /* default code stop section */
#endif

/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#if defined(CANTSYN_START_SEC_CONST_UNSPECIFIED)
# undef CANTSYN_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#if defined(CANTSYN_STOP_SEC_CONST_UNSPECIFIED)
# undef CANTSYN_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#if defined(CANTSYN_START_SEC_CONST_8BIT)
# undef CANTSYN_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT
#endif
#if defined(CANTSYN_STOP_SEC_CONST_8BIT)
# undef CANTSYN_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/*******  VAR sections  **********************************************************************************************/

/* VAR NOINIT sections */

#if defined(CANTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTSYN_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#if defined(CANTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
# undef CANTSYN_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#if defined(CANTSYN_START_SEC_VAR_NOINIT_8BIT)
# undef CANTSYN_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#if defined(CANTSYN_STOP_SEC_VAR_NOINIT_8BIT)
# undef CANTSYN_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#if defined(CANTSYN_START_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTSYN_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#if defined(CANTSYN_STOP_SEC_VAR_ZERO_INIT_8BIT)
# undef CANTSYN_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  CANTSYN END
 *********************************************************************************************************************/

/* E2EPW_MemMap.inc: End-To-End Protection Wrapper Memory Mapping: */


/* Code */
/* To be used for mapping code to application block, boot block, external flash etc. */
#if defined   E2EPW_START_SEC_CODE
#undef        E2EPW_START_SEC_CODE
#define           START_SEC_CODE

#elif defined E2EPW_STOP_SEC_CODE
#undef        E2EPW_STOP_SEC_CODE
#define             STOP_SEC_CODE


/* Constants */
/* To be used for global or static constants.  */
#elif defined E2EPW_START_SEC_CONST_UNSPECIFIED
#undef        E2EPW_START_SEC_CONST_UNSPECIFIED
#define             START_SEC_CONST_UNSPECIFIED

#elif defined E2EPW_STOP_SEC_CONST_UNSPECIFIED
#undef        E2EPW_STOP_SEC_CONST_UNSPECIFIED
#define             STOP_SEC_CONST


/* Var init unspecified */
#elif defined E2EPW_START_SEC_VAR_INIT_UNSPECIFIED
#undef        E2EPW_START_SEC_VAR_INIT_UNSPECIFIED
#define             START_SEC_VAR_INIT_UNSPECIFIED

#elif defined E2EPW_STOP_SEC_VAR_INIT_UNSPECIFIED
#undef        E2EPW_STOP_SEC_VAR_INIT_UNSPECIFIED
#define             STOP_SEC_VAR


/* Var uninitialized unspecified */
/* To be used for all global or static variables that are never initialized */
#elif defined E2EPW_START_SEC_VAR_NOINIT_UNSPECIFIED
#undef        E2EPW_START_SEC_VAR_NOINIT_UNSPECIFIED
#define             START_SEC_VAR_NOINIT_UNSPECIFIED

#elif defined E2EPW_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#undef        E2EPW_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#define             STOP_SEC_VAR


/* Var zero init unspecified */
#elif defined E2EPW_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#undef        E2EPW_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#define             START_SEC_VAR_ZERO_INIT_UNSPECIFIED

#elif defined E2EPW_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#undef        E2EPW_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#define             STOP_SEC_VAR


/* Library code     */
/* To be used for code that shall go into library segments for <MSN> module. */
#elif defined E2EPW_START_SEC_CODE_LIB
#undef        E2EPW_START_SEC_CODE_LIB
#define             START_SEC_CODE

#elif defined E2EPW_STOP_SEC_CODE_LIB
#undef        E2EPW_STOP_SEC_CODE_LIB
#define             STOP_SEC_CODE

#endif

/* End of file E2EPW_MemMap.inc */


/**********************************************************************************************************************
 *  VCANCCGBT START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef VCANCCGBT_START_SEC_CODE
# undef VCANCCGBT_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE /* mapped to default code section */
#endif
#ifdef VCANCCGBT_STOP_SEC_CODE
# undef VCANCCGBT_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE /* default code stop section */
#endif

#ifdef VCANCCGBT_START_SEC_APPL_CODE
# undef VCANCCGBT_START_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE /* mapped to default code section */
#endif
#ifdef VCANCCGBT_STOP_SEC_APPL_CODE
# undef VCANCCGBT_STOP_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef VCANCCGBT_START_SEC_CONST_UNSPECIFIED
# undef VCANCCGBT_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef VCANCCGBT_STOP_SEC_CONST_UNSPECIFIED
# undef VCANCCGBT_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef VCANCCGBT_START_SEC_CONST_8BIT
# undef VCANCCGBT_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_8BIT
#endif

#ifdef VCANCCGBT_STOP_SEC_CONST_8BIT
# undef VCANCCGBT_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

#ifdef VCANCCGBT_START_SEC_CONST_16BIT
# undef VCANCCGBT_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_16BIT
#endif

#ifdef VCANCCGBT_STOP_SEC_CONST_16BIT
# undef VCANCCGBT_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/* FAST CONST sections */


/* Postbuild CFG CONST sections */

#ifdef VCANCCGBT_START_SEC_PBCFG
# undef VCANCCGBT_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_PBCFG
#endif
#ifdef VCANCCGBT_STOP_SEC_PBCFG
# undef VCANCCGBT_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */


/* VAR NOINIT sections */

#ifdef VCANCCGBT_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef VCANCCGBT_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef VCANCCGBT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef VCANCCGBT_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/* VAR ZERO INIT sections */

#ifdef VCANCCGBT_START_SEC_VAR_ZERO_INIT_8BIT
# undef VCANCCGBT_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef VCANCCGBT_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef VCANCCGBT_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

#ifdef VCANCCGBT_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef VCANCCGBT_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef VCANCCGBT_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef VCANCCGBT_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */


/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */


/* Postbuild CFG VAR sections */

#ifdef VCANCCGBT_START_SEC_VAR_PBCFG
# undef VCANCCGBT_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_PBCFG
#endif
#ifdef VCANCCGBT_STOP_SEC_VAR_PBCFG
# undef VCANCCGBT_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  VCANCCGBT END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  J1939TP START
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef J1939TP_START_SEC_CODE
# undef J1939TP_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE /* mapped to default code section */
#endif
#ifdef J1939TP_STOP_SEC_CODE
# undef J1939TP_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef J1939TP_START_SEC_CONST_8BIT
# undef J1939TP_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT /* mapped to default const 8bit section */
#endif
#ifdef J1939TP_STOP_SEC_CONST_8BIT
# undef J1939TP_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST /* default const stop section */
#endif

#ifdef J1939TP_START_SEC_CONST_16BIT
# undef J1939TP_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#ifdef J1939TP_STOP_SEC_CONST_16BIT
# undef J1939TP_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef J1939TP_START_SEC_CONST_32BIT
# undef J1939TP_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_32BIT
#endif
#ifdef J1939TP_STOP_SEC_CONST_32BIT
# undef J1939TP_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef J1939TP_START_SEC_CONST_UNSPECIFIED
# undef J1939TP_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef J1939TP_STOP_SEC_CONST_UNSPECIFIED
# undef J1939TP_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/* FAST CONST sections */


/* Postbuild CFG CONST sections */

#ifdef J1939TP_START_SEC_PBCFG
# undef J1939TP_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef J1939TP_STOP_SEC_PBCFG
# undef J1939TP_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif


/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef J1939TP_START_SEC_VAR_ZERO_INIT_8BIT
# undef J1939TP_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif
#ifdef J1939TP_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef J1939TP_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef J1939TP_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef J1939TP_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef J1939TP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef J1939TP_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef J1939TP_START_SEC_VAR_NOINIT_8BIT
# undef J1939TP_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef J1939TP_STOP_SEC_VAR_NOINIT_8BIT
# undef J1939TP_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR ZERO INIT sections */

#ifdef J1939TP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef J1939TP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif
#ifdef J1939TP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef J1939TP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR FAST INIT sections */


/* VAR FAST NOINIT sections */


/* VAR FAST ZERO INIT sections */


/* Postbuild CFG VAR sections */

#ifdef J1939TP_START_SEC_VAR_PBCFG
# undef J1939TP_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#ifdef J1939TP_STOP_SEC_VAR_PBCFG
# undef J1939TP_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 *  J1939TP END
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  CANTP START 
 *********************************************************************************************************************/

/*******  CODE sections **********************************************************************************************/

#ifdef   CANTP_START_SEC_CODE
# undef  CANTP_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE      /* mapped to default code section */
#endif
#ifdef   CANTP_STOP_SEC_CODE
# undef  CANTP_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE      /* default code stop section */
#endif


/*******  CONST sections  ********************************************************************************************/

/* CONST sections */

#ifdef   CANTP_START_SEC_CONST_UNSPECIFIED
# undef  CANTP_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_UNSPECIFIED
#endif
#ifdef   CANTP_STOP_SEC_CONST_UNSPECIFIED
# undef  CANTP_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef   CANTP_START_SEC_CONST_8BIT
# undef  CANTP_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT
#endif
#ifdef   CANTP_STOP_SEC_CONST_8BIT
# undef  CANTP_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

#ifdef   CANTP_START_SEC_CONST_16BIT
# undef  CANTP_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_16BIT
#endif
#ifdef   CANTP_STOP_SEC_CONST_16BIT
# undef  CANTP_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif

/* Postbuild CFG CONST sections */

#ifdef   CANTP_START_SEC_PBCFG
# undef  CANTP_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_PBCFG
#endif
#ifdef   CANTP_STOP_SEC_PBCFG
# undef  CANTP_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST
#endif



/*******  VAR sections  **********************************************************************************************/

/* VAR INIT sections */

#ifdef   CANTP_START_SEC_VAR_INIT_8BIT
# undef  CANTP_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_8BIT
#endif
#ifdef   CANTP_STOP_SEC_VAR_INIT_8BIT
# undef  CANTP_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef   CANTP_START_SEC_VAR_INIT_16BIT
# undef  CANTP_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_INIT_16BIT
#endif
#ifdef   CANTP_STOP_SEC_VAR_INIT_16BIT
# undef  CANTP_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif


/* VAR NOINIT sections */

#ifdef   CANTP_START_SEC_VAR_NOINIT_8BIT
# undef  CANTP_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_8BIT
#endif
#ifdef   CANTP_STOP_SEC_VAR_NOINIT_8BIT
# undef  CANTP_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef   CANTP_START_SEC_VAR_NOINIT_16BIT
# undef  CANTP_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_16BIT
#endif
#ifdef   CANTP_STOP_SEC_VAR_NOINIT_16BIT
# undef  CANTP_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef   CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef  CANTP_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif
#ifdef   CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef  CANTP_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif

#ifdef   CANTP_START_SEC_VAR_PBCFG
# undef  CANTP_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_VAR_PBCFG
#endif
#ifdef   CANTP_STOP_SEC_VAR_PBCFG
# undef  CANTP_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_VAR
#endif



/**********************************************************************************************************************
 *  CANTP END
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  VSTDLIB START
 *********************************************************************************************************************/

#if defined(VSTDLIB_START_SEC_CODE)
# undef VSTDLIB_START_SEC_CODE                             /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CODE                                    /* mapped to default code section */
#endif
#if defined(VSTDLIB_STOP_SEC_CODE)
# undef VSTDLIB_STOP_SEC_CODE                              /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CODE
#endif

#if defined(VSTDLIB_START_SEC_CONST_8BIT)
# undef VSTDLIB_START_SEC_CONST_8BIT                       /* PRQA S 0841 */ /* MD_MSR_Undef */
# define START_SEC_CONST_8BIT                              /* mapped to const 8 bit section */
#endif
#if defined(VSTDLIB_STOP_SEC_CONST_8BIT)
# undef VSTDLIB_STOP_SEC_CONST_8BIT                        /* PRQA S 0841 */ /* MD_MSR_Undef */
# define STOP_SEC_CONST                                    /* default const stop section */
#endif

/**********************************************************************************************************************
 *  VSTDLIB END
 *********************************************************************************************************************/



/* PRQA L:MEMMAP_0841_TAG */

/* contains all configured MemMap Sections -> fallback for compatibility reasons */
#include "MemMap_Compatibility.h" /* generated by module MemMap */

/* MEMMAP_ERROR is
  - still defined if MemMap_Compatibility did not contain a matching section
  - undefined, if MemMap_Compatibility handled the section define. */               
#ifdef MEMMAP_ERROR
# include "MemMap_Common.h"
#endif


/**********************************************************************************************************************
 *  END OF FILE: MemMap.h
 *********************************************************************************************************************/

