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
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: China Lithium Battery Technology Co., Ltd.
 *       Expiry Date: 2025-08-26
 *  Ordered Derivat.: SAK-TC387QP-160F300S AE
 *    License Scope : The usage is restricted to CBD2200508_D00
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Trace_Cfg.h
 *   Generation Time: 2026-08-19 14:28:26
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

#ifndef OS_TRACE_CFG_H
# define OS_TRACE_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether ORTI is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_ORTI                             (STD_OFF)

/*! Defines whether ORTI tracing is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_ORTI_ADDITIONAL                  (STD_OFF)

/*! Defines whether Vector timing hooks are active (STD_ON) or not (STD_OFF). */
# define OS_CFG_OSTIMINGHOOKS                    (STD_OFF)

/*! Defines whether ARTI tracing is active (STD_ON) or not (STD_OFF). */
# define OS_CFG_ARTI                             (STD_OFF)

/*! Defines whether ARTI hooks are active (STD_ON) or not (STD_OFF). */
# define OS_CFG_ARTI_HOOKS_APPLICATION           (STD_OFF)
# define OS_CFG_ARTI_HOOKS_TASK                  (STD_OFF)
# define OS_CFG_ARTI_HOOKS_CAT2ISR               (STD_OFF)
# define OS_CFG_ARTI_HOOKS_SPINLOCK              (STD_OFF)
# define OS_CFG_ARTI_HOOKS_PROTECTIONHOOK        (STD_OFF)
# define OS_CFG_ARTI_HOOKS_SERVICECALLS          (STD_OFF)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  OS_CALL_ARTI_TRACE()
 **********************************************************************************************************************/
/*! \brief This macro needs to be generated as the third parameter of macro ARTI_TRACE (currently 'Os') shall contain
 *         OS instance short name. That parameter can't be set by macro as it will be concatenated with other parameters 
 *         to the function name of the ARTI tracing function.
 */
# define OS_CALL_ARTI_TRACE(_className, osCoreId, _eventName, eventParameter)

#endif /* OS_TRACE_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Trace_Cfg.h
 *********************************************************************************************************************/
