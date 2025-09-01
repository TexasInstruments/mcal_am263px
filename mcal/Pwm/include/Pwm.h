/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Pwm.h
 *
 *  \brief    This file contains interface header for PWM MCAL driver
 *
 */

/*
 * Below are the global requirements which are met by this PWM
 * driver which can't be mapped to a particular source ID
 */

/*
 * Below are the PWM module's environment requirements which can't be mapped
 * to this driver
 */
#ifndef PWM_H
#define PWM_H

/**
 *  \defgroup PWM Pwm
 *  @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*
 *Design: MCAL-13121
 */
#include "Pwm_Cfg.h"
#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *Design:
 *MCAL-13202,MCAL-13132,MCAL-13134,MCAL-13135,MCAL-13136,MCAL-13131,MCAL-13149,MCAL-13138,MCAL-13139,MCAL-13140,MCAL-13141,MCAL-13142
 */

/**
 *  \name PWM Driver Module SW Version Info
 *
 *  Defines for PWM Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define PWM_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define PWM_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation Patch Version */
#define PWM_SW_PATCH_VERSION (0U)
/** @} */

/**
 *  \name PWM Driver Module AUTOSAR Version Info
 *
 *  Defines for PWM Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by PWM Driver */
#define PWM_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by PWM Driver */
#define PWM_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by PWM Driver */
#define PWM_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/**
 *  \name PWM Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define PWM_VENDOR_ID ((uint16)44U)
/** \brief PWM Driver Module ID */
#define PWM_MODULE_ID ((uint16)121U)
/** \brief PWM Driver Instance ID */
#define PWM_INSTANCE_ID (PWM_INDEX)
/** @} */

/**
 *  \name PWM Error Codes
 *
 *  Error codes returned by PWM functions
 *  @{
 */

/** \brief PWM driver configuration parameter error */
#ifndef PWM_E_INIT_FAILED
#define PWM_E_INIT_FAILED ((uint8)(0x10U))
#endif

/** \brief PWM driver Not initialized error */
#ifndef PWM_E_UNINIT
#define PWM_E_UNINIT ((uint8)(0x11U))
#endif

/** \brief PWM driver Invalid param */
#ifndef PWM_E_PARAM_CHANNEL
#define PWM_E_PARAM_CHANNEL ((uint8)(0x12U))
#endif

/** \brief PWM driver Fixed period channel */
#ifndef PWM_E_PERIOD_UNCHANGEABLE
#define PWM_E_PERIOD_UNCHANGEABLE ((uint8)(0x13U))
#endif

/** \brief PWM driver Already initialized */
#ifndef PWM_E_ALREADY_INITIALIZED
#define PWM_E_ALREADY_INITIALIZED ((uint8)(0x14U))
#endif

/** \brief PWM driver pointer parameter error */
#ifndef PWM_E_PARAM_POINTER
#define PWM_E_PARAM_POINTER ((uint8)(0x15U))
#endif

/** \brief RunTime Error: API Pwm_SetPowerState is called
 *        while the PWM module is still in use */
#ifndef PWM_E_NOT_DISENGAGED
#define PWM_E_NOT_DISENGAGED ((uint8)(0x16U))
#endif
/** @} */

/**
 *  \name PWM Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief PWM driver service ID for Initialization API */
#define PWM_SID_INIT ((uint8)(0x0U))
/** \brief PWM driver service ID for De-Initialization API */
#define PWM_SID_DEINIT ((uint8)(0x1U))
/** \brief PWM driver service ID for set duty cycle API */
#define PWM_SID_SET_DUTY_CYCLE ((uint8)(0x2U))
/** \brief PWM driver service ID for set duty cycle and period API */
#define PWM_SID_SET_PERIOD_AND_DUTY ((uint8)(0x3U))
/** \brief PWM driver service ID for set output state to idle API */
#define PWM_SID_SET_OUTPUT_TO_IDLE ((uint8)(0x4U))
/** \brief PWM driver service ID for get output state API */
#define PWM_SID_GET_OUTPUT_STATE ((uint8)(0x5U))
/** \brief PWM driver service ID for disable notification API */
#define PWM_SID_DISABLE_NOTIFICATION ((uint8)(0x6U))
/** \brief PWM driver service ID for Enable notification API */
#define PWM_SID_ENABLE_NOTIFICATION ((uint8)(0x7U))
/** \brief PWM driver service ID for Get version info API */
#define PWM_SID_GET_VERSION_INFO ((uint8)(0x8U))
/** \brief PWM driver service ID for Critical register read back API */
#define PWM_SID_REGISTER_READBACK ((uint8)(0xDU))
/** @} */

/**
 *  \name PWM Driver State Values
 *
 *  The PWM Driver State Values
 *  @{
 */
/** \brief PWM driver Status uninitialized */
#define PWM_STATUS_UNINIT ((uint8)(0U))
/** \brief PWM driver Status Initialized */
#define PWM_STATUS_INIT ((uint8)(1U))

/** @} */

/* Req MCAL-3534 states that PWM module shall comply below duty cycle scheme
 *  - 0x0000 means 0%.
 *  - 0x8000 means 100%.
 *    0x8000 gives the highest resolution while allowing 100% duty cycle
 *    to be represented with a 16 bit value
 */
/** \brief 16 bit value representing 100% of a period value */
#define PWM_DUTY_100_PERCENT (0x8000U)

/** \brief 16bit value representing 0% of a period value */
#define PWM_DUTY_0_PERCENT (0x0U)

#if (PWM_INSTANCE_ID == 0U)
#define PWM_USE_EPWM
#elif (PWM_INSTANCE_ID == 1U)
#define PWM_USE_GPT
#endif

/**
 *  \name PWM Driver ISR category level
 *
 *  Defines for PWM Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define PWM_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define PWM_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define PWM_ISR_CAT2 (0x02U)
/** @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \name Period type for pwm channels.
 * Fixed periods prohibit changes to the period length with Pwm_SetPeriod( ).
 * PWM_FIXED_PERIOD_SHIFTED type is not supported due to hardware restrictions
 * of the PWM unit.
 */

/** \brief Possible edge notification  */
typedef enum
{
    /** \brief Rising edges issue notification  */
    PWM_RISING_EDGE = 1U,
    /** \brief Falling edges issue notification */
    PWM_FALLING_EDGE = 2U,
    /** \brief Both edges issue notification    */
    PWM_BOTH_EDGES = 3U

} Pwm_EdgeNotificationType;

#define PWM_START_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"
/** \brief Pwm driver init status */
extern volatile VAR(uint8, PWM_VAR_INIT) Pwm_DrvStatus;
#define PWM_STOP_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** Possible output states of a PWM channel */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Service for PWM initialization.
 * Initializes internal variables
 * and the PWM unit of the micro controller.
 * The function can be called on task level.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x00
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] CfgPtr - Pointer to the configuration
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE) Pwm_Init(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) CfgPtr);

#if (STD_ON == PWM_DEINIT_API)

/** \brief Service for PWM de-initialization.
 * After DeInit output states should be in idle level
 * (it is configurable whether reset state is restored or
 * if channel output states are really set to idle).
 * The function can be called on task level.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x01
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE) Pwm_DeInit(void);
#endif

#if (STD_ON == PWM_SET_DUTY_CYCLE_API)

/** \brief Service for setting Duty Cycle
 *  This service sets the duty cycle for a channel
 *  if DutyCycle is 0%, set output to inverse of polarity
 *  if DutyCycle is >= 100%, set output to polarity
 *  if 0% < DutyCycle < 100%, set output accordingly
 *  The function can be called on task level.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x02
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelNumber - Channel number
 * \param[in] DutyCycle - Duty cycle
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE) Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
#endif

#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)

/** \brief Service for setting Period and Duty Cycle
 *  This service sets period and duty cycle for a channel
 *  if DutyCycle is 0%, set output to inverse of polarity
 *  if DutyCycle is >= 100%, set output to polarity
 *  if 0% < DutyCycle < 100%, set output accordingly
 *  The function can be called on task level.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x03
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelNumber - Channel number
 * \param[in] Period - Period
 * \param[in] DutyCycle - Duty cycle
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE)
Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);
#endif

#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)

/** \brief Service to set the output of a channel immediately to idle.
 *  This service sets the output of a channel
 *  immediately to idle. The idle output level
 *  is configured in driver configuration.
 *  The function can be called on task level.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x04
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelNumber - Channel number
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE) Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber);
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)

/** \brief Service to disable the Edge Notification
 *  Disables the Edge Notification
 *  This service deactivates the Edge Notification for the
 *  pwm channel specified by the ChannelNumber Parameter.
 *  The function can be called on task level.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x06
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelNumber - Channel number
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE) Pwm_DisableNotification(Pwm_ChannelType ChannelNumber);
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)

/** \brief Service to enable the Edge Notification
 *  Enables the Edge Notification
 *  This service enables the notification of the chosen
 *  edges for the Pwm channel specified by the
 *  ChannelNumber.The function can be called on task level
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x07
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelNumber - Channel number
 * \param[in] Notification - Notification
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE)
Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification);
#endif

#if (STD_ON == PWM_VERSION_INFO_API)

/** \brief This service returns the version information of this module.
 *  Returns the version information of this module.
 *  The function can be called on task level.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x08
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] versioninfo - version info
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PWM_CODE)
Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA) versioninfo);
#endif

#if (STD_ON == PWM_REGISTER_READBACK_API) || (STD_ON == PWM_SAFETI_API)

/** \brief This function reads the important registers of the hardware unit
 *         and returns the value in the structure.
 *         This API is used to check the status of critical
 *         registers which do not change during program execution.
 *
 * Service ID[hex]   : 0x0D
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelNumber - Channel number
 * \param[out] RegRbPtr - Pointer to where to store the readback
 *                       values. If this pointer is NULL, then the API
 *                       will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK: Register read back has been done successfully
 * \retval E_NOT_OK: Register read back failed
 *
 *****************************************************************************/
Std_ReturnType Pwm_RegisterReadback(Pwm_ChannelType ChannelNumber, Pwm_RegisterReadbackType *RegRbPtr);
#endif

#if (STD_ON == PWM_GET_OUTPUT_STATE_API)

/** \brief This function read the internal state of the PWM output signal.
 *
 * Service ID[hex]   : 0x05
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelNumber - Channel Number
 * \return Pwm_OutputStateType
 * \retval PWM_HIGH The PWM output state is high
 * \retval PWM_LOW The PWM output state is low
 *
 *****************************************************************************/
FUNC(Pwm_OutputStateType, PWM_CODE) Pwm_GetOutputState(Pwm_ChannelType ChannelNumber);
#endif

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef PWM_H_ */
