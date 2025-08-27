/*
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PRCDD_PWMREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Cdd_Pwm.h
 *
 *  \brief    This file contains interface header for CDD_PWM MCAL driver
 *
 */

#ifndef CDD_PWM_H
#define CDD_PWM_H

/**
 * \defgroup CDD_PWM Epwm API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Pwm_Types.h"
#include "Cdd_Pwm_Cfg.h"
#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \name CDD_PWM Driver Module SW Version Info
 *
 *  Defines for CDD_PWM Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_PWM_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define CDD_PWM_SW_MINOR_VERSION (1U)
/** \brief Driver Implementation Patch Version */
#define CDD_PWM_SW_PATCH_VERSION (0U)
/**   @} */

/**
 *  \name CDD_PWM Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD_PWM Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD_PWM Driver */
#define CDD_PWM_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by CDD_PWM Driver */
#define CDD_PWM_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by CDD_PWM Driver */
#define CDD_PWM_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/** \brief Instance ID of this CDD_PWM driver. */
#define CDD_PWM_INDEX ((uint8)0U)

/** \brief InValid Base Address.*/
#define CDD_PWM_INVALID_BASE_ADDR ((uint8)0U)

/**
 *  \name CDD_PWM Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define CDD_PWM_VENDOR_ID ((uint16)44U)
/** \brief CDD_PWM Driver Module ID */
#define CDD_PWM_MODULE_ID ((uint16)255U)
/** \brief CDD_PWM Driver Instance ID */
#define CDD_PWM_INSTANCE_ID (CDD_PWM_INDEX)
/**   @} */

/**
 *  \name CDD_PWM Error Codes
 *
 *  Error codes returned by CDD_PWM functions
 *  @{
 */

#ifndef CDD_PWM_E_UNINIT
/** \brief API service used without module initialization */
#define CDD_PWM_E_UNINIT ((uint8)(0x02U))
#endif

#ifndef CDD_PWM_E_INIT_FAILED
/** \brief API Cdd_Pwm_Init service called with wrong parameter. */
#define CDD_PWM_E_INIT_FAILED ((uint8)(0x0BU))
#endif

#ifndef CDD_PWM_E_PARAM_INVALID_CHANNEL
/** \brief API service used with an invalid channel Identifier */
#define CDD_PWM_E_PARAM_INVALID_CHANNEL ((uint8)(0x03U))
#endif

#ifndef CDD_PWM_E_PARAM_INVALID_STATE
/** \brief API Cdd_Pwm_SetPinState() called with an invalid pin state or
           when the channel is in the RUNNING state.. */
#define CDD_PWM_E_PARAM_INVALID_STATE ((uint8)(0x04U))
#endif

#ifndef CDD_PWM_E_PARAM_INVALID_ACTION
/** \brief API Cdd_Pwm_SetPinAction() called with an invalid pin action. */
#define CDD_PWM_E_PARAM_INVALID_ACTION ((uint8)(0x05U))
#endif

#ifndef CDD_PWM_E_NO_VALID_NOTIF
/** \brief Usage of Cdd_Pwm_DisableNotification() or Cdd_Pwm_EnableNotification() on a channel
           where a NULL pointer is configured as the notification function. */
#define CDD_PWM_E_NO_VALID_NOTIF ((uint8)(0x06U))
#endif

#ifndef CDD_PWM_E_ALREADY_INITIALIZED
/** \brief API Cdd_Pwm_Init() called while the CDD_PWM driver has already been initialized */
#define CDD_PWM_E_ALREADY_INITIALIZED ((uint8)(0x07U))
#endif

#ifndef CDD_PWM_E_PARAM_POINTER
/** \brief API Cdd_Pwm_GetVersionInfo() is called with a NULL parameter. */
#define CDD_PWM_E_PARAM_POINTER ((uint8)(0x08U))
#endif

#ifndef CDD_PWM_E_BUSY
/** \brief API Cdd_Pwm_StartChannel() called on a channel that is in state RUNNING. */
#define CDD_PWM_E_BUSY ((uint8)(0x09U))
#endif

#ifndef CDD_PWM_E_PARAM_NO_PIN
/** \brief Cdd_Pwm_SetPinState() or Cdd_Pwm_SetPinAction() called for a channel that doesn’t
 *          have an associated output pin. */
#define CDD_PWM_E_PARAM_NO_PIN ((uint8)(0x0AU))
#endif

#ifndef CDD_PWM_E_PARAM_INVALID_VALUE
/** \brief Cdd_Pwm_SetAbsoluteThreshold() or Cdd_Pwm_SetRelativeThreshold() called for with a
 * compare match parameter greater than maximum supported counter value for a given channel */
#define CDD_PWM_E_PARAM_INVALID_VALUE ((uint8)(0x1AU))
#endif

#ifndef CDD_PWM_E_PARAM_CHANNEL
/** \brief Invalid Channel parameter  */
#define CDD_PWM_E_PARAM_CHANNEL ((uint8)(0x1BU))
#endif
/**   @} */
/**
 *  \name CDD_PWM Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief CDD_PWM driver service ID for Initialization API */
#define CDD_PWM_SID_INIT ((uint8)(0x0U))
/** \brief CDD_PWM driver service ID for De-Initialization API */
#define CDD_PWM_SID_DEINIT ((uint8)(0x1U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_StartChannel API */
#define CDD_PWM_SID_STARTCHANNEL ((uint8)(0x2U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_StopChannel API */
#define CDD_PWM_SID_STOPCHANNEL ((uint8)(0x3U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_SetPinState API */
#define CDD_PWM_SID_GETCOUNTER_STATUS ((uint8)(0x4U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_SetPinAction API */
#define CDD_PWM_SID_SET_PIN_ACTION ((uint8)(0x5U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_GetCounter API */
#define CDD_PWM_SID_GETCOUNTER ((uint8)(0x6U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_SetAbsoluteThreshold API */
#define CDD_PWM_SID_SET_ABSOLUTE_THRESHOLD ((uint8)(0x7U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_SetRelativeThreshold API */
#define CDD_PWM_SID_SET_RELATIVE_THRESHOLD ((uint8)(0x8U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_DisableNotification API */
#define CDD_PWM_SID_DISABLE_NOTIFICATION ((uint8)(0x9U))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_EnableNotification API */
#define CDD_PWM_SID_ENABLE_NOTIFICATION ((uint8)(0xAU))
/** \brief CDD_PWM driver service ID for Cdd_Pwm_GetVersionInfo API */
#define CDD_PWM_SID_GET_VERSION_INFO ((uint8)(0xBU))
/** \brief CDD_PWM driver service ID for Critical register read back API */
#define CDD_PWM_SID_REGISTER_READBACK ((uint8)(0xDU))
/** \brief CDD_PWM driver service ID for set duty cycle and period API */
#define CDD_PWM_SID_SET_PERIOD_AND_DUTY ((uint8)(0xEU))
/** \brief CDD_PWM driver service ID for get output state API */
#define CDD_PWM_SID_SET_OUTPUT_TO_IDLE ((uint8)(0xFU))
/** \brief CDD_PWM driver service ID for configuration of DeadBand module */
#define CDD_PWM_SID_CONFIGURE_DEADBAND ((uint8)(0x10U))
/** \brief CDD_PWM driver service ID to bypass DeadBand module */
#define CDD_PWM_SID_BYPASS_DEADBAND ((uint8)(0x11U))
/** \brief CDD_PWM driver service ID for configuration of Chopper module */
#define CDD_PWM_SID_CONFIGURE_CHOPPER ((uint8)(0x12U))
/** \brief CDD_PWM driver service ID to enable Chopper module */
#define CDD_PWM_SID_ENABLE_CHOPPER ((uint8)(0x13U))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_ClearCounterStatus*/
#define CDD_PWM_SID_CLEAR_COUNTER_STATUS ((uint8)(0x15U))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_EtIntrStatus*/
#define CDD_PWM_SID_INTR_STATUS ((uint8)(0x16U))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_EtIntrClear*/
#define CDD_PWM_SID_INTR_CLEAR_STATUS ((uint8)(0x17U))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_EtGetEventCount*/
#define CDD_PWM_SID_GET_EVENT_COUNT ((uint8)(0x18U))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_SetAdcTrigger*/
#define CDD_PWM_SID_SET_ADC_TRIGGER ((uint8)(0x19U))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_SyncEnable*/
#define CDD_PWM_SID_SYNC_ENABLE ((uint8)(0x2AU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_SyncDisable*/
#define CDD_PWM_SID_SYNC_DISABLE ((uint8)(0x2BU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_CounterComparatorCfg*/
#define CDD_PWM_SID_COUNTER_CMP_CFG ((uint8)(0x2CU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_TzTripEventEnable*/
#define CDD_PWM_SID_TZ_EVENT_ENABLE ((uint8)(0x1BU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_TzTripEventDisable*/
#define CDD_PWM_SID_TZ_EVENT_DISABLE ((uint8)(0x1CU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_TzIntrEnable*/
#define CDD_PWM_SID_TZ_INTR_ENABLE ((uint8)(0x1DU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_TzIntrDisable*/
#define CDD_PWM_SID_TZ_INTR_DISABLE ((uint8)(0x1EU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_TzGetEventStatus*/
#define CDD_PWM_SID_TZ_GET_EVENT_STATUS ((uint8)(0x1FU))
/** \brief CDD_PWM driver service ID to Cdd_Pwm_TzEventStatusClear*/
#define CDD_PWM_SID_TZ_EVENT_STATUS_CLEAR ((uint8)(0x20U))
/** \brief CDD_PWM driver service ID to enable HRPWM module */
#define CDD_PWM_SID_HR_SET_HRPWM_API ((uint8)(0x21U))
/** \brief CDD_PWM driver service ID to enable HRPWM SFO calibration */
#define CDD_PWM_SID_HR_SFO_CAL_API ((uint8)(0x22U))
/** \brief CDD_PWM driver service ID to check HRPWM SFO Cal. Status */
#define CDD_PWM_SID_HR_SFO_STATUS_API ((uint8)(0x23U))

/** \brief CDD_PWM driver service ID to set Time base counter mode */
#define CDD_PWM_SID_SET_TIME_BASE_COUNTER_MODE ((uint8)(0x24U))
/** \brief CDD_PWM driver service ID to set the phase shift in runtime */
#define CDD_PWM_SID_SET_PHASE_SHIFT ((uint8)(0x25U))
/** \brief CDD_PWM driver service ID to set the period in runtime */
#define CDD_PWM_SID_SET_TIMEBASE_PERIOD ((uint8)(0x26U))
/** \brief CDD_PWM driver service ID to set the Counter Compare value in runtime */
#define CDD_PWM_SID_SET_COUNTER_COMPARE_VALUE ((uint8)(0x27U))
/** \brief CDD_PWM driver service ID to set the rising edge delay in runtime */
#define CDD_PWM_SID_SET_RISING_EDGE_DELAY_COUNT ((uint8)(0x28U))
/** \brief CDD_PWM driver service ID to set the falling edge delay in runtime */
#define CDD_PWM_SID_SET_FALLING_EDGE_DELAY_COUNT ((uint8)(0x29U))

/** \brief CDD_PWM driver service ID to set the HRPWM phase shift in runtime */
#define CDD_PWM_SID_HR_SET_PHASE_SHIFT ((uint8)(0x2AU))
/** \brief CDD_PWM driver service ID to set the HRPWM period in runtime */
#define CDD_PWM_SID_HR_SET_TIMEBASE_PERIOD ((uint8)(0x2BU))
/** \brief CDD_PWM driver service ID to set the HRPWM Counter Compare value in runtime */
#define CDD_PWM_SID_HR_SET_COUNTER_COMPARE_VALUE ((uint8)(0x2CU))
/** \brief CDD_PWM driver service ID to set the HRPWM rising edge delay in runtime */
#define CDD_PWM_SID_HR_SET_RISING_EDGE_DELAY_COUNT ((uint8)(0x2DU))
/** \brief CDD_PWM driver service ID to set the HRPWM falling edge delay in runtime */
#define CDD_PWM_SID_HR_SET_FALLING_EDGE_DELAY_COUNT ((uint8)(0x2EU))

/** \brief CDD_PWM driver service ID to set the minimum deadband delay value in runtime */
#define CDD_PWM_SID_SET_MIN_DEADBAND_DELAY ((uint8)(0x2FU))
/** \brief CDD_PWM driver service ID to set theXCMP reg value in runtime */
#define CDD_PWM_SID_SET_XCMP_REG_VALUE ((uint8)(0x30U))
/** \brief CDD_PWM driver service ID to set the HRPWM XCMP reg value in runtime */
#define CDD_PWM_SID_HR_SET_XCMP_REG_VALUE ((uint8)(0x31U))
/** \brief CDD_PWM driver service ID to set the Xminmax reg value in runtime */
#define CDD_PWM_SID_SET_XMINMAP_REG_VALUE ((uint8)(0x32U))
/** \brief CDD_PWM driver service ID to set the CMP shadow reg value in runtime */
#define CDD_PWM_SID_SET_CMP_SHADOW_REG_VALUE ((uint8)(0x33U))

/**   @} */

/**
 *  \name CDD_PWM Driver State Values
 *
 *  The CDD_PWM Driver State Values
 *  @{
 */
/** \brief CDD_PWM driver Status uninitialized */
#define CDD_PWM_STATUS_UNINIT ((uint8)(0U))
/** \brief CDD_PWM driver Status Initialized */
#define CDD_PWM_STATUS_INIT ((uint8)(1U))
/** \brief CDD_PWM driver Status stopped */
#define CDD_PWM_STATUS_STOPPED ((uint8)(2U))
/** \brief CDD_PWM driver Status running */
#define CDD_PWM_STATUS_RUNNING ((uint8)(3U))

/**   @} */

/**
 *  \name CDD PWM Driver ISR category level
 *
 *  Defines for CDD PWM Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_PWM_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CDD_PWM_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CDD_PWM_ISR_CAT2 (0x02U)
/**   @} */

/** \brief Start Memory section tag */
#define CDD_PWM_START_SEC_VAR_INIT_8
#include "Cdd_Pwm_MemMap.h"
/** \brief Pwm driver init status */
extern volatile VAR(uint8, CDD_PWM_VAR_INIT) Cdd_Pwm_DrvStatus;
/** \brief End Memory section tag */
#define CDD_PWM_STOP_SEC_VAR_INIT_8
#include "Cdd_Pwm_MemMap.h"

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*===============================================================================================
                                     FUNCTION PROTOTYPES
===============================================================================================*/
/** \brief Start Memory section tag */
#define CDD_PWM_START_SEC_CODE
#include "Cdd_Pwm_MemMap.h"

/*===============================================================================================*/

/** \brief Function Initializes CDD_PWM unit.
 *
 *
 * Cdd_Pwm_Init shall initialize all internals variables and the used PWM
 * structure of the microcontroller according to the parameters specified
 * in ConfigPtr.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ConfigPtr - Pointer to driver configuration.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_Init(P2CONST(Cdd_Pwm_ConfigType, AUTOMATIC, CDD_PWM_APPL_CONST) ConfigPtr);

/*===============================================================================================*/

#if (CDD_PWM_DEINIT_API == STD_ON)
/** \brief Function for PWM De-Initialization.
 *
 *
 * Cdd_Pwm_DeInit shall de-initialize CDD_PWM.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_DeInit(void);
#endif /*#if (CDD_PWM_DEINIT_API == STD_ON)*/

/*===============================================================================================*/
/** \brief Function to start a PWM channel.
 *
 *
 * Cdd_Pwm_StartChannelCounter shall start a PWM channel.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber - configured channel number
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_StartChannelCounter(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber);

/*===============================================================================================*/
/** \brief Function to stop a PWM channel.
 *
 *
 * Cdd_Pwm_StopChannelCounter shall stop a PWM channel.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber - configured channel number
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_StopChannelCounter(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber);

/*===============================================================================================*/

#if (CDD_PWM_SET_PIN_ACTION_API == STD_ON)
/** \brief Function to indicate the driver what shall be done automatically by
 * hardware (if supported) upon compare match.
 *
 *
 * Cdd_Pwm_SetPinAction indicate the driver what shall be done automatically
 * by hardware (if supported) upon compare match.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber - configured channel number
 * \param[in] PinAction - Actions Can be:PWM_SET_LOW, PWM_SET_HIGH, PWM_TOGGLE,
 *  PWM_DISABLE.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetPinAction(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                     VAR(Cdd_Pwm_PinActionType, AUTOMATIC) PinAction);
#endif /*#if (CDD_PWM_SET_PIN_ACTION_API == STD_ON)*/

/*===============================================================================================*/

#if (CDD_PWM_GET_COUNTER_API == STD_ON)
/** \brief Function to read the current value of the counter.
 *
 *
 * Cdd_Pwm_GetCounter read the current value of the counter.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber - configured channel number
 * \return Cdd_Pwm_ValueType
 * \retval current value of the counter
 *
 *****************************************************************************/
FUNC(Cdd_Pwm_ValueType, CDD_PWM_CODE)
Cdd_Pwm_GetCounter(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber);
#endif /*#if (CDD_PWM_GET_COUNTER_API == STD_ON)*/

#if (CDD_PWM_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/*===============================================================================================*/
/** \brief Function to set the value of the channel threshold using an absolute
 * input data.
 *
 *
 * Cdd_Pwm_SetAbsoluteThreshold  set the value of the channel threshold using an
 * absolute input data.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber
 * \param[in] ReferenceValue
 * \param[in] AbsoluteValue
 * \return Cdd_Pwm_ReturnType
 * \retval CDD_PWM_CM_IN_REF_INTERVAL - The compare match will occur inside
 * the current Reference Interval
 * \retval CDD_PWM_CM_OUT_REF_INTERVAL - The compare match will not occur inside
 * the current Reference Interval
 *
 *****************************************************************************/
FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetAbsoluteThreshold(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                             VAR(Cdd_Pwm_ValueType, AUTOMATIC) ReferenceValue,
                             VAR(Cdd_Pwm_ValueType, AUTOMATIC) AbsoluteValue);
#endif /*#if (CDD_PWM_SET_ABSOLUTE_THRESHOLD_API == STD_ON)*/

/*===============================================================================================*/

#if (CDD_PWM_SET_RELATIVE_THRESHOLD_API == STD_ON)
/** \brief Function to set the value of the channel threshold relative to the
 * current value of the counter.
 *
 *
 * Cdd_Pwm_SetRelativeThreshold set the value of the channel threshold relative
 * to the current value of the counter.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber
 * \param[in] RelativeValue
 * \return Cdd_Pwm_ReturnType
 * \retval CDD_PWM_CM_IN_REF_INTERVAL - The compare match will occur inside
 * the current Reference Interval
 * \retval CDD_PWM_CM_OUT_REF_INTERVAL - The compare match will not occur inside
 * the current Reference Interval
 *
 *****************************************************************************/
FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetRelativeThreshold(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                             VAR(Cdd_Pwm_ValueType, AUTOMATIC) RelativeValue);
#endif /*#if (CDD_PWM_SET_RELATIVE_THRESHOLD_API == STD_ON)*/

/*===============================================================================================*/

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
/** \brief Function to disable the PWM signal edge notification.
 *
 *
 * Cdd_Pwm_DisableNotification disable the PWM signal edge notification.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_DisableNotification(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber);
#endif /*#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

/*===============================================================================================*/

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
/** \brief Function  to enable the PWM signal edge notification
 * according to  notification parameter.
 *
 *
 * Cdd_Pwm_EnableNotification  to enable the PWM signal edge notification
 * according to notification parameter.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelParameter
 * \param[in] EdgeInterruptSource
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_EnableNotification(Cdd_Pwm_ChannelType ChannelParameter, Cdd_Pwm_InterruptType EdgeInterruptSource);
#endif /*#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

/*===============================================================================================*/

#if (STD_ON == CDD_PWM_VERSION_INFO_API)
/** \brief Function to return the version information of this module.
 *
 *
 * Cdd_Pwm_GetVersionInfo  returns the version information of  this module.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[out] versioninfo - Pointer to where to store the version information
 * of this module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_PWM_APPL_DATA) versioninfo);
#endif /*#if (STD_ON == CDD_PWM_VERSION_INFO_API)*/

/*===============================================================================================*/

#if (STD_ON == CDD_PWM_REGISTER_READBACK_API)
/** \brief Function to read the important registers of the hardware unit and
 * returns the value in the structure.
 *
 *
 * Cdd_Pwm_RegisterReadback reads the important registers of the hardware
 * unit and returns the value in the structure.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber - configured channel number
 * \param[in] RegRbPtr
 * \return Std_ReturnType
 * \retval E_OK - Register read back has been done successfully
 * \retval E_NOT_OK - Register read back failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_RegisterReadback(Cdd_Pwm_ChannelType ChannelNumber, Cdd_Pwm_RegisterReadbackType *RegRbPtr);
#endif /*#if(STD_ON == CDD_PWM_REGISTER_READBACK_API)*/

/*===============================================================================================*/
#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
/** \brief Function sets the period and the duty cycle of a PWM channel.
 *
 *
 * Cdd_Pwm_SetPeriodDutyPhase  sets the period and the duty cycle of a
 * PWM channel.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelParameter
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetPeriodDutyPhase(Cdd_Pwm_channelParametertype ChannelParameter);
#endif /*#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)*/

/*===============================================================================================*/

#if (STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API)
/** \brief Function sets the PWM output to the configured Idle state.
 *
 *
 * Cdd_Pwm_SetOutputToIdle  sets the PWM output to the configured Idle state.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber - configured channel number
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetOutputToIdle(Cdd_Pwm_ChannelType ChannelNumber);
#endif /*#if (STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API)*/

#if (STD_ON == CDD_PWM_BASE_CLK_SYNC)
/*===============================================================================================*/
/** \brief Function enables the synchronization of time base sub-module and
 * also configures the phase count value to be loaded after sync event, counter
 * direction after sync event.
 *
 *
 * Cdd_Pwm_SyncEnable  enables the synchronization of time base sub-module and
 * also configures the phase count value to be loaded after sync event, counter
 * direction after sync event.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] tbPhsValue
 * \param[in] counterDir
 * \return Std_ReturnType
 * \retval E_OK - Synchronization enabled successfully
 * \retval E_NOT_OK - Synchronization enabled failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SyncEnable(uint32 Channel, uint32 tbPhsValue, uint32 counterDir);

/*===============================================================================================*/
/** \brief Function disables the synchronization. Even if sync-in event
 * occurs the count value will not be reloaded.
 *
 *
 * Cdd_Pwm_SyncDisable  disables the synchronization. Even if sync-in event
 * occurs the count value will not be reloaded.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \return Std_ReturnType
 * \retval E_OK - Synchronization disabled successfully
 * \retval E_NOT_OK - Synchronization disabled failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_SyncDisable(uint32 Channel);
#endif /*#if (STD_ON == CDD_PWM_BASE_CLK_SYNC)*/

/*===============================================================================================*/
/** \brief Function gets the Time Base status as indicated by the tbStatusMask
 * parameter.
 *
 *
 * Cdd_Pwm_tbGetStatus  gets the Time Base status as indicated by the
 * tbStatusMask parameter.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] tbStatusMask
 * \return uint16
 * \retval
 *
 *****************************************************************************/
FUNC(uint16, CDD_PWM_CODE) Cdd_Pwm_GetCounterStatus(uint32 Channel, uint32 tbStatusMask);
/*===============================================================================================*/
/** \brief Function  clears the Time base status bits indicated by the
 * tbStatusClrMask parameter.
 *
 *
 * Cdd_Pwm_tbStatusClear clears the Time base status bits indicated by the
 * tbStatusClrMask parameter.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] tbStatusClrMask
 * \return Std_ReturnType
 * \retval E_OK - Time base status cleared successfully
 * \retval E_NOT_OK - Time base status cleared failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_ClearCounterStatus(uint32 Channel, uint32 tbStatusClrMask);

#if (STD_ON == CDD_PWM_COUNTER_COMPARE_CFG)
/*===============================================================================================*/
/** \brief Function configures the counter comparator and loads the
 * comparator value.
 *
 *
 * Cdd_Pwm_counterComparatorCfg configures the counter comparator and
 * loads the comparator value.  When Counter comparator value equals the
 * counter value, then an event is generated both in the up direction and
 * down direction.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] cmpType
 * \param[in] cmpVal
 * \param[in] shadowToActiveLoadTrigger
 * \param[in] overwriteShadow
 * \return Std_ReturnType
 * \retval E_OK - Configuration of counter comparator is successful
 * \retval E_NOT_OK - Configuration of counter comparator is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_CounterComparatorCfg(uint32 Channel, Cdd_Pwm_OutputChType cmpType, uint32 cmpVal,
                             uint32 shadowToActiveLoadTrigger, uint32 overwriteShadow);
#endif /*#if (STD_ON == CDD_PWM_COUNTER_COMPARE_CFG)*/

#if (STD_ON == CDD_PWM_DEAD_BAND)
/*===============================================================================================*/
/** \brief Function performs the configuration of the dead band sub-module.
 *
 *
 * Cdd_Pwm_deadbandCfgperforms the configuration of the dead band sub-module.
 * This API configures the input source, output mode, polarity,
 * rising and falling edge delays.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] pCfg
 * \return Std_ReturnType
 * \retval E_OK - Configuration of dead band sub-module is successful
 * \retval E_NOT_OK - Configuration of dead band sub-module is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_DeadbandCfg(uint32 Channel, const CDD_PWM_DeadbandCfgType *pCfg);
#endif /*#if (STD_ON == CDD_PWM_DEAD_BAND)*/

/*===============================================================================================*/
/** \brief Function bypasses the Dead-band sub-module.
 *
 *
 * Cdd_Pwm_deadbandBypass bypasses the Dead-band sub-module.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \return Std_ReturnType
 * \retval E_OK - Dead-band sub-module bypass is successful
 * \retval E_NOT_OK - Dead-band sub-module bypass is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_DeadbandBypass(uint32 Channel);

#if (STD_ON == CDD_PWM_CHOPPER)
/*===============================================================================================*/
/** \brief  Performs the configuration of the chopper sub-module.
 *
 *
 * Cdd_Pwm_chopperCfg performs the configuration of the chopper sub-module.
 * This API configures chopping clock  duty cycle, chopping clock frequency and
 * pulse width of first pulse of chopping clock.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] pCfg
 * \return Std_ReturnType
 * \retval E_OK - configuration of the chopper sub-module is successful
 * \retval E_NOT_OK - configuration of the chopper sub-module is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_ChopperCfg(uint32 Channel, const CDD_PWM_ChopperCfgType *pCfg);

/*===============================================================================================*/
/** \brief  Function  controls the enabling or disabling of chopper sub-module.
 *
 *
 * Cdd_Pwm_chopperEnable controls the enabling or disabling of chopper
 * sub-module.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] enableChopper

 * \return Std_ReturnType
 * \retval E_OK - enabling or disabling of chopper sub-module is successful
 * \retval E_NOT_OK - enabling or disabling of chopper sub-module is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_ChopperEnable(uint32 Channel, uint32 enableChopper);
#endif /*#if (STD_ON == CDD_PWM_CHOPPER)*/

/*===============================================================================================*/
/** \brief  Function sets the mode of Time base counter
 *
 * This function is used to set the mode for Time base counter.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] Mode. Refer \ref counterMode parameter. Example CDD_PWM_COUNTER_MODE_UP defined in Epwm\V0\Cdd_Pwm_Types.h
 *
 * \return Std_ReturnType
 * \retval E_OK - Operation successful
 * \retval E_NOT_OK - Operation failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_SetTimeBaseCounterMode(uint32 Channel, EPWM_TimeBaseCountMode Mode);

/*========================================================================================================*/
/** \brief  Function to set the Phase shift value in runtime.
 *
 *
 * Cdd_Pwm_SetPhaseShift set the Phase shift value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] PhaseShiftValue - Phase shift value
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetPhaseShift(uint32 Channel, uint16 PhaseShiftValue);

/*========================================================================================================*/
/** \brief  Function to set the time base period in runtime.
 *
 *
 * Cdd_Pwm_SetTimeBasePeriod set the time base period in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] Period - Period
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetTimeBasePeriod(uint32 Channel, uint16 Period);

/*========================================================================================================*/
/** \brief  Function to set the Compare value in runtime.
 *
 *
 * Cdd_Pwm_SetCounterCompareValue set the Compare value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] CompModule - Compare Module. Refer \e compModule parameter
 * \param[in] DutyValue - Duty cycle value
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetCounterCompareValue(uint32 Channel, EPWM_CounterCompareModule CompModule, uint16 DutyValue);

/*========================================================================================================*/
/** \brief  Function to set the rising edge delay in runtime.
 *
 *
 * Cdd_Pwm_SetRisingEdgeDelay set the rising edge delay in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] RedCount - Rising Edge delay count
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetRisingEdgeDelay(uint32 Channel, uint16 RedCount);

/*========================================================================================================*/
/** \brief  Function to set the falling edge delay in runtime.
 *
 *
 * Cdd_Pwm_SetFallingEdgeDelay set the falling edge delay in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] FedCount - Falling Edge delay count
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetFallingEdgeDelay(uint32 Channel, uint16 FedCount);

/*========================================================================================================*/
/** \brief  Function to set the minimum deadband delay in runtime.
 *
 *
 * Cdd_Pwm_SetMinDeadbandDelay set the minimum deadband delay in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] Block - Block. Possible values EPWM_MINDB_BLOCK_A, EPWM_MINDB_BLOCK_B
 * \param[in] Delay - Delay value
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetMinDeadbandDelay(uint32 Channel, uint32 Block, uint32 Delay);

/*========================================================================================================*/
/** \brief  Function to set the XCMP register value in runtime.
 *
 *
 * Cdd_Pwm_SetXcmpRegValue set the XCMP register value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] XcmpReg - XCMP register. Refer \e xcmpReg parameter
 * \param[in] XcmpValue - XCMP Value to be passed
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetXcmpRegValue(uint32 Channel, EPWM_XCMPReg XcmpReg, uint16 XcmpValue);

/*========================================================================================================*/
/** \brief  Function to set the XMINMAX register value in runtime.
 *
 *
 * Cdd_Pwm_SetXMinMaxRegValue set the XMINMAX register value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] XminmaxReg - XMINMAX register. Refer \e xminmaxReg parameter
 * \param[in] XcmpValue - XCMP Value to be passed
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetXMinMaxRegValue(uint32 Channel, EPWM_XMinMaxReg XminmaxReg, uint16 XcmpValue);

/*========================================================================================================*/
/** \brief  Function to set the CMP shadow register value in runtime.
 *
 *
 * Cdd_Pwm_SetCmpShadowRegValue set the CMP shadow register value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] CmpReg - CMP register. Refer \e cmpReg parameter
 * \param[in] CmpValue - CMP Value to be passed
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetCmpShadowRegValue(uint32 Channel, EPWM_XCompareReg CmpReg, uint16 CmpValue);

#if (STD_ON == CDD_PWM_TRIP_ZONE)
/*===============================================================================================*/
/** \brief  Function enables the trip event.
 *
 *
 * Cdd_Pwm_tzTripEventEnable  enables the trip event.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] tzEventType
 * \return Std_ReturnType
 * \retval E_OK - enabling of trip event is successful
 * \retval E_NOT_OK - enabling of trip event is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzTripEventEnable(uint32 Channel, uint32 tzEventType);

/*===============================================================================================*/
/** \brief  Function disable the trip event. The disabled trip events will be
 * ignored.
 *
 *
 * Cdd_Pwm_tzTripEventDisable disable the trip event. The The disabled trip
 * events will be ignored.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] tzEventType
 * \return Std_ReturnType
 * \retval E_OK - disabling of trip event is successful
 * \retval E_NOT_OK - disabling of trip event is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzTripEventDisable(uint32 Channel, uint32 tzEventType);
/*===============================================================================================*/
/** \brief  Function enables the trip interrupt.
 *
 *
 * Cdd_Pwm_tzIntrEnable enables the trip interrupt. When trip event occurs
 * the sub-module can be configured to interrupt CPU.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] tzEventType
 * \return Std_ReturnType
 * \retval E_OK - enabling of trip interrupt is successful
 * \retval E_NOT_OK - enabling of trip interrupt is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzIntrEnable(uint32 Channel, uint32 tzEventType);
/*===============================================================================================*/
/** \brief  Function disables the trip interrupt.
 *
 *
 * Cdd_Pwm_tzIntrDisable disables the trip interrupt.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] tzEventType
 * \return Std_ReturnType
 * \retval E_OK - disabling of trip interrupt is successful
 * \retval E_NOT_OK - disabling of trip interrupt is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzIntrDisable(uint32 Channel, uint32 tzEventType);
/*===============================================================================================*/
/** \brief  Function returns the selected trip zone event status.
 *
 *
 * Cdd_Pwm_tzEventStatus returns the selected trip zone event status.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] eventMask
 * \return boolean
 * \retval TRUE
 * \retval FALSE
 *
 *****************************************************************************/
FUNC(boolean, CDD_PWM_CODE) Cdd_Pwm_TzGetEventStatus(uint32 Channel, uint32 eventMask);
/*===============================================================================================*/
/** \brief Function clears the selected trip zone event status.
 *
 *
 * Cdd_Pwm_tzEventStatusClear clears the selected trip zone event status.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] eventMask
 * \param[in] tzFlags
 * \return Std_ReturnType
 * \retval E_OK - selected trip zone event status is cleared successfully
 * \retval E_NOT_OK - clearing of selected trip zone event status is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_TzEventStatusClear(uint32 Channel, uint32 eventMask, uint32 tzFlags);
/*===============================================================================================*/
/** \brief Function enables to generate Software forced trip condition.
 *
 *
 * Cdd_Pwm_tzTriggerSwEvent enables to generate Software forced trip condition.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] eventMask
 * \return Std_ReturnType
 * \retval E_OK -
 * \retval E_NOT_OK -
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzTriggerSwEvent(uint32 Channel, uint32 tzEventType);
#endif /*#if (STD_ON == CDD_PWM_TRIP_ZONE)*/

/*===============================================================================================*/
/** \brief Function returns the ePWM event interrupt status.
 *
 * Cdd_Pwm_etIntrStatus returns the ePWM event interrupt status.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \return uint16
 * \retval ePWM event interrupt status.
 *
 *****************************************************************************/
FUNC(uint16, CDD_PWM_CODE) Cdd_Pwm_EtIntrStatus(uint32 Channel);
/*===============================================================================================*/
/** \brief Function  clears the interrupt.
 *
 * Cdd_Pwm_etIntrClear  clears the interrupt. This will clear the interrupt
 * flag bit and enable further interrupts pulses to be generated.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \return Std_ReturnType
 * \retval E_OK - Interrupt cleared successfully
 * \retval E_NOT_OK - Interrupt cleared failed.
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_EtIntrClear(uint32 Channel);
/*===============================================================================================*/
/** \brief Function forces interrupt to be generated.
 *
 *
 * Cdd_Pwm_etIntrTrigger forces interrupt to be generated. This API is
 * used for testing purpose.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \return Std_ReturnType
 * \retval E_OK -
 * \retval E_NOT_OK -
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_EtIntrTrigger(uint32 Channel);
/*===============================================================================================*/
/** \brief Function returns the number of events occurred.
 *
 *
 * Cdd_Pwm_etGetEventCount returns the number of events occurred.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \return uint16
 * \retval number of events occurred.
 *
 *****************************************************************************/
FUNC(uint16, CDD_PWM_CODE) Cdd_Pwm_EtGetEventCount(uint32 Channel);

#if (STD_ON == CDD_PWM_ADC_ENABLE_DISABLE_API)
/*===============================================================================================*/
/** \brief Function Enables/Disables the ADC Trigger.
 *
 *
 * Cdd_Pwm_SetAdcTrigger enables/disables the ADC Trigger.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Channel
 * \param[in] adcSoc
 * \return Std_ReturnType
 * \retval E_OK - enabling/disabling of ADC Trigger is successful
 * \retval E_NOT_OK - enabling/disabling of ADC Trigger is failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_SetAdcTrigger(uint32 Channel, Cdd_Pwm_AdcSocType adcSoc);
#endif /*#if (STD_ON == CDD_PWM_ADC_ENABLE_DISABLE_API)*/

#if (STD_ON == CDD_PWM_HR_SET_HRPWM_API)
/*===============================================================================================*/
/** \brief Function generates High Resolution PWM Signal.
 *
 *
 * Enable the HR PWM functionality.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelParameter
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE) Cdd_Pwm_HrSetPeriodDutyPhase(Cdd_Pwm_channelParametertype ChannelParameter);
#endif /* #if (STD_ON == CDD_PWM_HR_SET_HRPWM_API) */

#if (STD_ON == CDD_PWM_HR_SFO_CAL_API)
/*===============================================================================================*/
/** \brief Function calibrate the HR PWM signal.
 *
 *
 * Cdd_Pwm_HrSfoCalibration calibrate the HR PWM signal.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelParameter
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE) Cdd_Pwm_HrSfoCalibration(Cdd_Pwm_channelParametertype ChannelParameter);
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_CAL_API) */

#if (STD_ON == CDD_PWM_HR_SFO_STATUS_API)
/*===============================================================================================*/
/** \brief Function returns the SFO calibration status.
 *
 *
 * Cdd_Pwm_HrSfoStatus Get SFO Calibration Status
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ChannelNumber - configured channel number
 * \return uint32
 * \retval 0 -- Incomplete SFO Cal.
 * \retval 1 -- Complete SFO Cal.
 * \retval 2 -- Error in SFO Cal.
 *
 *****************************************************************************/
FUNC(uint32, PWM_CODE) Cdd_Pwm_HrSfoStatus(uint32 ChannelNumber);
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_STATUS_API) */

/*========================================================================================================*/
/** \brief  Function to set the HRPWM Phase shift value in runtime.
 *
 *
 * Cdd_Pwm_HrSetPhaseShift set the HRPWM Phase shift value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] PhaseShiftValue - Phase shift value
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetPhaseShift(uint32 Channel, uint32 PhaseShiftValue);

/*========================================================================================================*/
/** \brief  Function to set the HRPWM time base period in runtime.
 *
 *
 * Cdd_Pwm_HrSetTimeBasePeriod set the HRPWM time base period in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] Period - Period
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetTimeBasePeriod(uint32 Channel, uint16 Period);

/*========================================================================================================*/
/** \brief  Function to set the HRPWM Compare value in runtime.
 *
 * Cdd_Pwm_HrSetCounterCompareValue set the HRPWM Compare value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] CompModule - Compare Module. Refer \e compModule parameter
 * \param[in] DutyValue - Duty cycle value
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_HrSetCounterCompareValue(uint32 Channel, HRPWM_CounterCompareModule CompModule, uint32 DutyValue);

/*========================================================================================================*/
/** \brief  Function to set the HRPWM rising edge delay in runtime.
 *
 *
 * Cdd_Pwm_HrSetRisingEdgeDelay set the HRPWM rising edge delay in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] RedCount - Rising Edge delay count
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetRisingEdgeDelay(uint32 Channel, uint16 RedCount);

/*========================================================================================================*/
/** \brief  Function to set the HRPWM falling edge delay in runtime.
 *
 *
 * Cdd_Pwm_HrSetFallingEdgeDelay set the HRPWM falling edge delay in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] FedCount - Falling Edge delay count
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetFallingEdgeDelay(uint32 Channel, uint16 FedCount);

/*========================================================================================================*/
/** \brief  Function to set the HRPWM XCMP register value in runtime.
 *
 *
 * Cdd_Pwm_SetHrXcmpRegValue set the HRPWM XCMP register value in runtime
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] Channel - Channel information
 * \param[in] HrXcmpReg - XCMP register. Refer \e xcmpReg parameter
 * \param[in] HrXcmpValue - XCMP Value to be passed
 *
 * \return void
 *
 *********************************************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetXcmpRegValue(uint32 Channel, HRPWM_XCMPReg HrXcmpReg, uint16 HrXcmpValue);

/** \brief End Memory section tag */
#define CDD_PWM_STOP_SEC_CODE
#include "Cdd_Pwm_MemMap.h"

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* #ifndef CDD_PWM_H_ */
