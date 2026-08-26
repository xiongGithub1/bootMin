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
 *            Module: MemMap
 *           Program: MSR_Vector_SLP4
 *          Customer: China Lithium Battery Technology Co., Ltd.
 *       Expiry Date: 2025-08-26
 *  Ordered Derivat.: SAK-TC387QP-160F300S AE
 *    License Scope : The usage is restricted to CBD2200508_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanIf_MemMap.h
 *   Generation Time: 2026-08-19 14:28:25
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

#ifndef MICROSAR_DISABLE_MEMMAP

/**********************************************************************************************************************
 *  PRE USER CONFIG FILE
 *********************************************************************************************************************/

/* User Config File Start */

/* User Config File End */

/**********************************************************************************************************************
 *  MEMMAP SECTIONS
 *********************************************************************************************************************/

#define MEMMAP_ERROR

#if defined CANIF_START_SEC_CODE
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CODE is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CODE_OPEN

/* Generation of pragmas is not possible as neither a start/stop pragma nor a valid vLinkGen logical group reference is given. */

# undef CANIF_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CODE
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CODE is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CODE_OPEN
#  error Using CANIF_STOP_SEC_CODE is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Generation of pragmas is not possible as neither a start/stop pragma nor a valid vLinkGen logical group reference is given. */

# undef CANIF_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_APPL_CODE
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_APPL_CODE is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_APPL_CODE_OPEN

/* Generation of pragmas is not possible as neither a start/stop pragma nor a valid vLinkGen logical group reference is given. */

# undef CANIF_START_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_APPL_CODE
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_APPL_CODE is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_APPL_CODE_OPEN
#  error Using CANIF_STOP_SEC_APPL_CODE is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_APPL_CODE_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Generation of pragmas is not possible as neither a start/stop pragma nor a valid vLinkGen logical group reference is given. */

# undef CANIF_STOP_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_PBCFG
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_PBCFG is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_PBCFG_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_PBCFG_CONST/MSR_PBCFG_CONST */
# pragma section farrom "MSR_PBCFG_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_PBCFG
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_PBCFG is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_PBCFG_OPEN
#  error Using CANIF_STOP_SEC_PBCFG is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_PBCFG_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_PBCFG_CONST/MSR_PBCFG_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_8BIT_OPEN
#  error Using CANIF_STOP_SEC_CONST_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_16BIT_OPEN
#  error Using CANIF_STOP_SEC_CONST_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_32BIT_OPEN
#  error Using CANIF_STOP_SEC_CONST_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_CONST_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_FAST_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_FAST_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_FAST_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_FAST_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_FAST_8BIT_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_FAST_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_FAST_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_FAST_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_FAST_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_FAST_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_FAST_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_FAST_16BIT_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_FAST_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_FAST_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_FAST_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_FAST_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_FAST_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_FAST_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_FAST_32BIT_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_FAST_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_FAST_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_CONST_FAST_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_CONST_FAST_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_CONST_FAST_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom "MSR_CONST" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_CONST_FAST_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_CONST_FAST_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_CONST_FAST_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_CONST_FAST_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_CONST/MSR_CONST */
# pragma section farrom restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_CONST_FAST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_PBCFG
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_PBCFG is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_PBCFG_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_PBCFG_VAR/MSR_PBCFG_VAR */
# pragma section farnoclear "MSR_PBCFG_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_PBCFG_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_PBCFG_VAR" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_PBCFG
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_PBCFG is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_PBCFG_OPEN
#  error Using CANIF_STOP_SEC_VAR_PBCFG is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_PBCFG_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_PBCFG_VAR/MSR_PBCFG_VAR */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_PBCFG /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_NOINIT_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_NOINIT_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_NOINIT_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_NOINIT_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_NOINIT_8BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_NOINIT_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_NOINIT_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_NOINIT_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_NOINIT_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_NOINIT_16BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_NOINIT_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_NOINIT_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_NOINIT_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_NOINIT_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_NOINIT_32BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_NOINIT_64BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_NOINIT_64BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_NOINIT_64BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_NOINIT_64BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_NOINIT_64BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_64BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_NOINIT_64BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_64BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_NOINIT_64BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_NOINIT_64BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_NOINIT_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_NOINIT_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_INIT_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_INIT_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_INIT_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_INIT_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_INIT_8BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_INIT_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_INIT_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_INIT_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_INIT_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_INIT_16BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_INIT_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_INIT_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_INIT_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_INIT_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_INIT_32BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_INIT_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_INIT_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_INIT_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_INIT_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_ZERO_INIT_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_ZERO_INIT_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_ZERO_INIT_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_ZERO_INIT_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_ZERO_INIT_8BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_ZERO_INIT_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_ZERO_INIT_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_ZERO_INIT_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_ZERO_INIT_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_ZERO_INIT_16BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_ZERO_INIT_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_ZERO_INIT_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_ZERO_INIT_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_ZERO_INIT_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_ZERO_INIT_32BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_ZERO_INIT_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_ZERO_INIT_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_NOINIT_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_NOINIT_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_NOINIT_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_NOINIT_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_NOINIT_8BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_NOINIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_NOINIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_NOINIT_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_NOINIT_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_NOINIT_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_NOINIT_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_NOINIT_16BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_NOINIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_NOINIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_NOINIT_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_NOINIT_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_NOINIT_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_NOINIT_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_NOINIT_32BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_NOINIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_NOINIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_NOINIT_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_NOINIT_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_NOINIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_NO_INIT/MSR_VAR_NO_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_INIT_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_INIT_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_INIT_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_INIT_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_INIT_8BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_INIT_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_INIT_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_INIT_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_INIT_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_INIT_16BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_INIT_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_INIT_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_INIT_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_INIT_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_INIT_32BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_INIT_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_INIT_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_INIT_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_NO_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_INIT_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_INIT/MSR_VAR_INIT */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_ZERO_INIT_8BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_8BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_ZERO_INIT_8BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_ZERO_INIT_8BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_ZERO_INIT_8BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_ZERO_INIT_16BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_16BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_ZERO_INIT_16BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_ZERO_INIT_16BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_ZERO_INIT_16BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_ZERO_INIT_32BIT
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_32BIT is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_ZERO_INIT_32BIT_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_ZERO_INIT_32BIT_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_ZERO_INIT_32BIT_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

/* -------------------------------------------------------------------------------- */

#elif defined CANIF_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# ifdef MEMMAP_SECTION_OPEN
#  error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is not possible as a memory section has already been opened. Nesting is not supported.
# endif
# define MEMMAP_SECTION_OPEN
# define CANIF_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss "MSR_VAR_CLEARED" /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata "MSR_VAR_INIT" /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */

#elif defined CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# ifndef MEMMAP_SECTION_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is not possible as no memory section has been opened.
# endif
# undef MEMMAP_SECTION_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */
# ifndef CANIF_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN
#  error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is not possible as the corresponding memory section has not been opened.
# endif
# undef CANIF_VAR_FAST_ZERO_INIT_UNSPECIFIED_OPEN /* PRQA S 0841 */ /* MD_MSR_Undef */

/* Pragmas generated automatically. Related MemMapAddressingMode: /ActiveEcuC/MemMap/MSR_VAR_CLEARED/MSR_VAR_CLEARED */
# pragma section farnoclear restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section farbss restore /* PRQA S 3116 */ /* MD_MSR_Pragma */
# pragma section fardata restore /* PRQA S 3116 */ /* MD_MSR_Pragma */

# undef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_Undef */
# undef MEMMAP_ERROR /* PRQA S 0841 */ /* MD_MSR_Undef */
#endif

/* -------------------------------------------------------------------------------- */


/**********************************************************************************************************************
 *  MEMMAP ERROR CHECKS
 *********************************************************************************************************************/

#ifdef CANIF_START_SEC_CODE
# error Using CANIF_START_SEC_CODE is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CODE
# error Using CANIF_STOP_SEC_CODE is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_APPL_CODE
# error Using CANIF_START_SEC_APPL_CODE is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_APPL_CODE
# error Using CANIF_STOP_SEC_APPL_CODE is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_PBCFG
# error Using CANIF_START_SEC_PBCFG is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_PBCFG
# error Using CANIF_STOP_SEC_PBCFG is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_8BIT
# error Using CANIF_START_SEC_CONST_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_8BIT
# error Using CANIF_STOP_SEC_CONST_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_16BIT
# error Using CANIF_START_SEC_CONST_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_16BIT
# error Using CANIF_STOP_SEC_CONST_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_32BIT
# error Using CANIF_START_SEC_CONST_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_32BIT
# error Using CANIF_STOP_SEC_CONST_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_UNSPECIFIED
# error Using CANIF_START_SEC_CONST_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_UNSPECIFIED
# error Using CANIF_STOP_SEC_CONST_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_FAST_8BIT
# error Using CANIF_START_SEC_CONST_FAST_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_FAST_8BIT
# error Using CANIF_STOP_SEC_CONST_FAST_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_FAST_16BIT
# error Using CANIF_START_SEC_CONST_FAST_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_FAST_16BIT
# error Using CANIF_STOP_SEC_CONST_FAST_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_FAST_32BIT
# error Using CANIF_START_SEC_CONST_FAST_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_FAST_32BIT
# error Using CANIF_STOP_SEC_CONST_FAST_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_CONST_FAST_UNSPECIFIED
# error Using CANIF_START_SEC_CONST_FAST_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_CONST_FAST_UNSPECIFIED
# error Using CANIF_STOP_SEC_CONST_FAST_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_PBCFG
# error Using CANIF_START_SEC_VAR_PBCFG is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_PBCFG
# error Using CANIF_STOP_SEC_VAR_PBCFG is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_NOINIT_8BIT
# error Using CANIF_START_SEC_VAR_NOINIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_NOINIT_8BIT
# error Using CANIF_STOP_SEC_VAR_NOINIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_NOINIT_16BIT
# error Using CANIF_START_SEC_VAR_NOINIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_NOINIT_16BIT
# error Using CANIF_STOP_SEC_VAR_NOINIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_NOINIT_32BIT
# error Using CANIF_START_SEC_VAR_NOINIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_NOINIT_32BIT
# error Using CANIF_STOP_SEC_VAR_NOINIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_NOINIT_64BIT
# error Using CANIF_START_SEC_VAR_NOINIT_64BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_NOINIT_64BIT
# error Using CANIF_STOP_SEC_VAR_NOINIT_64BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
# error Using CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# error Using CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_INIT_8BIT
# error Using CANIF_START_SEC_VAR_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_INIT_8BIT
# error Using CANIF_STOP_SEC_VAR_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_INIT_16BIT
# error Using CANIF_START_SEC_VAR_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_INIT_16BIT
# error Using CANIF_STOP_SEC_VAR_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_INIT_32BIT
# error Using CANIF_START_SEC_VAR_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_INIT_32BIT
# error Using CANIF_STOP_SEC_VAR_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_INIT_UNSPECIFIED
# error Using CANIF_START_SEC_VAR_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
# error Using CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_ZERO_INIT_8BIT
# error Using CANIF_START_SEC_VAR_ZERO_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_ZERO_INIT_8BIT
# error Using CANIF_STOP_SEC_VAR_ZERO_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_ZERO_INIT_16BIT
# error Using CANIF_START_SEC_VAR_ZERO_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_ZERO_INIT_16BIT
# error Using CANIF_STOP_SEC_VAR_ZERO_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_ZERO_INIT_32BIT
# error Using CANIF_START_SEC_VAR_ZERO_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_ZERO_INIT_32BIT
# error Using CANIF_STOP_SEC_VAR_ZERO_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# error Using CANIF_START_SEC_VAR_ZERO_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# error Using CANIF_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_NOINIT_8BIT
# error Using CANIF_START_SEC_VAR_FAST_NOINIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_NOINIT_8BIT
# error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_NOINIT_16BIT
# error Using CANIF_START_SEC_VAR_FAST_NOINIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_NOINIT_16BIT
# error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_NOINIT_32BIT
# error Using CANIF_START_SEC_VAR_FAST_NOINIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_NOINIT_32BIT
# error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# error Using CANIF_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# error Using CANIF_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_INIT_8BIT
# error Using CANIF_START_SEC_VAR_FAST_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_INIT_8BIT
# error Using CANIF_STOP_SEC_VAR_FAST_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_INIT_16BIT
# error Using CANIF_START_SEC_VAR_FAST_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_INIT_16BIT
# error Using CANIF_STOP_SEC_VAR_FAST_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_INIT_32BIT
# error Using CANIF_START_SEC_VAR_FAST_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_INIT_32BIT
# error Using CANIF_STOP_SEC_VAR_FAST_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_INIT_UNSPECIFIED
# error Using CANIF_START_SEC_VAR_FAST_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
# error Using CANIF_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_ZERO_INIT_8BIT
# error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT
# error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_8BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_ZERO_INIT_16BIT
# error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT
# error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_16BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_ZERO_INIT_32BIT
# error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT
# error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_32BIT is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# error Using CANIF_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif
#ifdef CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# error Using CANIF_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is not possible as multiple memory allocation keywords are defined. Include the MemMap separately for each one.
#endif

#ifdef MEMMAP_ERROR
# error No MemMap section found in CanIf_MemMap.h. Check your section define for validity.
#endif


/**********************************************************************************************************************
 *  POST USER CONFIG FILE
 *********************************************************************************************************************/

/* User Config File Start */

/* User Config File End */

#endif
/**********************************************************************************************************************
 *  END OF FILE: CanIf_MemMap.h
 *********************************************************************************************************************/

