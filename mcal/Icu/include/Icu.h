/*
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     Icu.h
 *
 *  \brief    This file contains interface header for ICU MCAL driver
 *              to be used by other AUTOSAR MCAL Layers
 *
 */

/*
 * Below are the global requirements which are met by this PWM
 * driver which can't be mapped to a particular source ID
 */
/* DesignId : DES_ICU_002*/
/* Requirements : MCAL-4569, MCAL-4570, MCAL-4571, MCAL-4572, MCAL-4573,
 *  MCAL-4574, MCAL-4575, MCAL-4576, MCAL-4577, MCAL-4578, MCAL-4579
 */

/*
 * Below are the PWM module's environment requirements which can't be mapped
 * to this driver
 */
/* DesignId : DES_ICU_003, DES_ICU_004*/
/*
 * Requirements : MCAL-4534, MCAL-4535, MCAL-4536, MCAL-4538, MCAL-4539,
 * MCAL-4541, MCAL-4542, MCAL-4544, MCAL-4545, MCAL-4546, MCAL-4547, MCAL-4549,
 * MCAL-4550, MCAL-4552, MCAL-4553, MCAL-4554, MCAL-4555, MCAL-4557, MCAL-4558,
 * MCAL-4559, MCAL-4560, MCAL-4561, MCAL-4562, MCAL-4563, MCAL-4566, MCAL-4567,
 * MCAL-5168, MCAL-5169, MCAL-5170
 */

#ifndef ICU_H_
#define ICU_H_

/**
 * \defgroup ICU Icu API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* Design : DES_ICU_002 */
/* Requirements : MCAL-4585, MCAL-4586 MCAL-4569, MCAL-4570, MCAL-4571, MCAL-4572,
            MCAL-4573, MCAL-4574, MCAL-4575, MCAL-4576, MCAL-4577, MCAL-4578, MCAL-4579*/
#include "Std_Types.h"
#include "hw_icu.h"
#include "EcuM_Cbk.h"
#include "Icu_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name ICU Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define ICU_VENDOR_ID ((uint16)44U)
/** \brief ICU Driver Module ID */
#define ICU_MODULE_ID ((uint16)122U)
/** \brief ICU Driver Instance ID */
#define ICU_INSTANCE_ID ((uint8)0U)

/**   @} */

/**
 *  \name ICU Driver Module SW Version Info
 *
 *  Defines for ICU Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define ICU_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define ICU_SW_MINOR_VERSION (1U)
/** \brief Driver Implementation Patch Version */
#define ICU_SW_PATCH_VERSION (0U)
/**   @} */

/**
 *  \name ICU Driver Module AUTOSAR Version Info
 *
 *  Defines for ICU Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by ICU Driver */
#define ICU_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by ICU Driver */
#define ICU_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by ICU Driver */
#define ICU_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */
/**
 *  \name ICU ISR category level
 *
 *  Defines for ICU Driver ISR category level
 *  @{
 */
/** \brief void ISR type */
#define ICU_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define ICU_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define ICU_ISR_CAT2 (0x02U)
/**   @} */

/**
 *  \name ICU Service IDs
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief Icu_Init() API Service ID */
#define ICU_INIT_ID ((uint8)0x00U)
/** \brief Icu_DeInit() API Service ID */
#define ICU_DEINIT_ID ((uint8)0x01U)
/** \brief Icu_SetMode() API Service ID */
#define ICU_SETMODE_ID ((uint8)0x02U)
/** \brief Icu_SetActivationCondition() API Service ID */
#define ICU_SETACTIVATIONCONDITION_ID ((uint8)0x05U)
/** \brief Icu_DisableNotification() API Service ID */
#define ICU_DISABLENOTIFICATION_ID ((uint8)0x06U)
/** \brief Icu_EnableNotification() API Service ID */
#define ICU_ENABLENOTIFICATION_ID ((uint8)0x07U)
/** \brief Icu_GetInputState() API Service ID */
#define ICU_GETINPUTSTATE_ID ((uint8)0x08U)
/** \brief Icu_StartTimestamp() API Service ID */
#define ICU_STARTTIMESTAMP_ID ((uint8)0x09U)
/** \brief Icu_StopTimestamp() API Service ID */
#define ICU_STOPTIMESTAMP_ID ((uint8)0x0AU)
/** \brief Icu_GetTimeStampIndex() API Service ID */
#define ICU_GETTIMESTAMPINDEX_ID ((uint8)0x0BU)
/** \brief Icu_ResetEdgeCount() API Service ID */
#define ICU_RESETEDGECOUNT_ID ((uint8)0x0CU)
/** \brief Icu_EnableEdgeCount() API Service ID */
#define ICU_ENABLEEDGECOUNT_ID ((uint8)0x0DU)
/** \brief Icu_EnableEdgeDetection() API Service ID */
#define ICU_ENABLEEDGEDETECTION_ID ((uint8)0x16U)
/** \brief Icu_DisableEdgeDetection() API Service ID */
#define ICU_DISABLEEDGEDETECTION_ID ((uint8)0x17U)
/** \brief Icu_DisableEdgeCount() API Service ID */
#define ICU_DISABLEEDGECOUNT_ID ((uint8)0x0EU)
/** \brief Icu_GetEdgeNumbers() API Service ID */
#define ICU_GETEDGENUMBERS_ID ((uint8)0x0FU)
/** \brief Icu_StartSignalMeasurement() API Service ID */
#define ICU_STARTSIGNALMEASUREMENT_ID ((uint8)0x13U)
/** \brief Icu_StopSignalMeasurement() API Service ID */
#define ICU_STOPSIGNALMEASUREMENT_ID ((uint8)0x14U)
/** \brief Icu_GetTimeElapsed() API Service ID */
#define ICU_GETTIMEELAPSED_ID ((uint8)0x10U)
/** \brief Icu_GetDutyCycleValues() API Service ID */
#define ICU_GETDUTYCYCLEVALUES_ID ((uint8)0x11U)
/** \brief Icu_GetVersionInfo() API Service ID */
#define ICU_GETVERSIONINFO_ID ((uint8)0x12U)
/** \brief Icu_RegisterReadback() API Service ID */
#define ICU_REGISTERREADBACK_ID ((uint8)0x15U)
/**   @} */

/**
 *  \name ICU Error Codes
 *
 *  Error codes returned by ICU functions
 *  @{
 */
/* Design : DES_ICU_005 */
/* Requirements : MCAL-4585, MCAL-4586 */
/** \brief API service called with invalid pointer */
#define ICU_E_PARAM_POINTER ((uint8)0x0AU)

/** \brief API service called with invalid channel identifier
 *  or channel not configured
 */
#define ICU_E_PARAM_CHANNEL ((uint8)0x0BU)
/** \brief API service calleed with an invalid or not feasible activation */
#define ICU_E_PARAM_ACTIVATION ((uint8)0x0CU)
/** \brief Init Function Failed */
#define ICU_E_INIT_FAILED ((uint8)0x0DU)
/** \brief API service used with invalid Buffer size */
#define ICU_E_PARAM_BUFFER_SIZE ((uint8)0x0EU)
/** \brief API service called with invalid mode */
#define ICU_E_PARAM_MODE ((uint8)0x0FU)
/** \brief API service calleed without module initialisation */
#define ICU_E_UNINIT ((uint8)0x14U)
/** \brief Icu_StopTimestamp called on channel not started or already stopped */
#define ICU_E_NOT_STARTED ((uint8)0x16U)
/** \brief API service called while a running operation */
#define ICU_E_BUSY_OPERATION ((uint8)0x16U)
/** \brief API service Icu_Init called when module already initialized */
#define ICU_E_ALREADY_INITIALIZED ((uint8)0x17U)
/** \brief API service called when notify interval is invalid */
#define ICU_E_PARAM_NOTIFY_INTERVAL ((uint8)0x18U)
/** \brief API service Icu_GetVersionInfo called and parameter is invalid */
#define ICU_E_PARAM_VINFO ((uint8)0x19U)
/**   @} */

/**
 *  \name ICU Driver State Values
 *
 *  The ICU Driver State Values
 *  @{
 */
/* Design : DES_ICU_001 */
/* Requirements : MCAL-4591 */
/** \brief ICU driver Status uninitialized */
#define ICU_STATUS_UNINIT ((uint8)(0U))
/** \brief ICU driver Status Initialized */
#define ICU_STATUS_INIT ((uint8)(1U))
/**   @} */

/**
 *  \name Macros to define Rising and Falling edge config for capture registers
 *@{
 */
/** \brief Capture regsiter configuration for FALLING edge  */
#define ICU_FALLING ((uint8)(1U))
/** \brief Capture regsiter configuration for RISING edge  */
#define ICU_RISING ((uint8)(0U))
/**   @} */
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**  \brief This type defines a range of mode type */

typedef enum
{
    /** \brief Normal Mode */
    ICU_MODE_NORMAL,
    /** \brief Sleep Mode */
    ICU_MODE_SLEEP
} Icu_ModeType;

/**  \brief This type defines a input state of ICU driver */

typedef enum
{
    /** \brief Module is in active state */
    ICU_ACTIVE,
    /** \brief Module is in idle state */
    ICU_IDLE
} Icu_InputStateType;

/** \brief This type defines Activation range */

typedef enum
{
    /** \brief Rising Edge Activation type*/
    ICU_RISING_EDGE,
    /** \brief Falling Edge Activation type*/
    ICU_FALLING_EDGE,
    /** \brief Both Edge Activation type*/
    ICU_BOTH_EDGES
} Icu_ActivationType;

/** \brief This type defines Input XBAR */
typedef enum
{
    /** \brief XBAR 0 */
    INPUT_XBAR_0 = 202,
    /** \brief XBAR 1 */
    INPUT_XBAR_1,
    /** \brief XBAR 2 */
    INPUT_XBAR_2,
    /** \brief XBAR 3 */
    INPUT_XBAR_3,
    /** \brief XBAR 4 */
    INPUT_XBAR_4,
    /** \brief XBAR 5 */
    INPUT_XBAR_5,
    /** \brief XBAR 6 */
    INPUT_XBAR_6,
    /** \brief XBAR 7 */
    INPUT_XBAR_7,
    /** \brief XBAR 8 */
    INPUT_XBAR_8,
    /** \brief XBAR 9 */
    INPUT_XBAR_9,
    /** \brief XBAR 10 */
    INPUT_XBAR_10,
    /** \brief XBAR 11 */
    INPUT_XBAR_11,
    /** \brief XBAR 12 */
    INPUT_XBAR_12,
    /** \brief XBAR 13 */
    INPUT_XBAR_13,
    /** \brief XBAR 14 */
    INPUT_XBAR_14,
    /** \brief XBAR 15 */
    INPUT_XBAR_15,
    /** \brief XBAR 16 */
    INPUT_XBAR_16,
    /** \brief XBAR 17 */
    INPUT_XBAR_17,
    /** \brief XBAR 18 */
    INPUT_XBAR_18,
    /** \brief XBAR 19 */
    INPUT_XBAR_19,
    /** \brief XBAR 20 */
    INPUT_XBAR_20,
    /** \brief XBAR 21 */
    INPUT_XBAR_21,
    /** \brief XBAR 22 */
    INPUT_XBAR_22,
    /** \brief XBAR 23 */
    INPUT_XBAR_23,
    /** \brief XBAR 24 */
    INPUT_XBAR_24,
    /** \brief XBAR 25 */
    INPUT_XBAR_25,
    /** \brief XBAR 26 */
    INPUT_XBAR_26,
    /** \brief XBAR 27 */
    INPUT_XBAR_27,
    /** \brief XBAR 28 */
    INPUT_XBAR_28,
    /** \brief XBAR 29 */
    INPUT_XBAR_29,
    /** \brief XBAR 30 */
    INPUT_XBAR_30,
    /** \brief XBAR 31 */
    INPUT_XBAR_31
} Icu_XbarSelect;

/** \brief This type defines ECAP selection */
typedef enum
{
    ECAP_CEVT1_INT       = CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK,
    ECAP_CEVT2_INT       = CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK,
    ECAP_CEVT3_INT       = CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK,
    ECAP_CEVT4_INT       = CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK,
    ECAP_CEVT1_CEVT2_INT = CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK,
    ECAP_CEVT1_CEVT3_INT = CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK,
    ECAP_CEVT1_CEVT4_INT = CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK,
    ECAP_CEVT2_CEVT3_INT = CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK,
    ECAP_CEVT2_CEVT4_INT = CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK,
    ECAP_CEVT3_CEVT4_INT = CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK,
    ECAP_CEVT1_CEVT2_CEVT3_INT =
        CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK,
    ECAP_CEVT1_CEVT2_CEVT4_INT =
        CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK,
    ECAP_CEVT1_CEVT3_CEVT4_INT =
        CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK,
    ECAP_CEVT2_CEVT3_CEVT4_INT =
        CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK,
    ECAP_INT_ALLCAPS = CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK |
                       CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK | CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK
} Icu_IntrCapSelect;

/**
 *  \brief This type defines Value type
 */
typedef uint16 Icu_ValueType;

/**
 *  \brief This type defines Duty Cycle struct
 */
typedef struct
{
    /** \brief Active time of Signal*/
    Icu_ValueType ActiveTime;
    /** \brief Period time of Signal*/
    Icu_ValueType PeriodTime;
} Icu_DutyCycleType;

/**
 *  \brief This type defines return value Icu_GetTimeStampIndex
 */
typedef uint32 Icu_IndexType;

/**
 *  \brief This type defines return value of Icu-Icu_GetEdgeNumbers
 */
typedef uint32 Icu_EdgeNumberType;

/**
 *  \brief This type defines available measurement modes
 */
typedef enum
{
    /** \brief Signal Edge Detect Mode*/
    ICU_MODE_SIGNAL_EDGE_DETECT,
    /** \brief Signal measurement Mode*/
    ICU_MODE_SIGNAL_MEASUREMENT,
    /** \brief Signal Timestamp Mode*/
    ICU_MODE_TIMESTAMP,
    /** \brief Signal Edge counter Mode*/
    ICU_MODE_EDGE_COUNTER
} Icu_MeasurementModeType;

/**
 *  \brief This type defines Signal Measurement Property range
 */
typedef enum
{
    /** \brief Signal Low time*/
    ICU_LOW_TIME,
    /** \brief Signal High time*/
    ICU_HIGH_TIME,
    /** \brief Signal Period time*/
    ICU_PERIOD_TIME,
    /** \brief Signal Duty Cycle time*/
    ICU_DUTY_CYCLE
} Icu_SignalMeasurementPropertyType;

/**
 *  \brief This type defines TimeStamp Property range
 */
typedef enum
{
    /** \brief Linear Buffer to be used in Timestamp*/
    ICU_LINEAR_BUFFER,
    /** \brief Circular Buffer to be used in Timestamp*/
    ICU_CIRCULAR_BUFFER
} Icu_TimestampBufferType;

/** \brief  Notification callback function pointer  */
typedef void (*Icu_NotifyFuncType)(void);

/**
 *  \brief This type defines Channel type
 */
typedef uint8 Icu_ChannelType;

/**
 *  \brief This type defines Prescaler type
 */
typedef uint8 Icu_ChannelPrescalerType;

/**
 *  \brief ICU Channel Config Structure of Pre-Compile only
 */
typedef struct
{
    /** \brief Channel ID of ICU Channel in use */
    Icu_ChannelType channelId;
} Icu_ChannelConfigType_PC;

/**
 *  \brief ICU Config Structure of Pre-Compile only
 */
typedef struct Icu_ConfigType_PC_s
{
    /** \brief Channel configurations */
    Icu_ChannelConfigType_PC chCfg[ICU_MAX_NUM_CHANNELS];
} Icu_ConfigType_PC;

/**
 *  \brief ICU Channel Config Structure
 */
typedef struct
{
    /** \brief Default activation edge to be used by ICU module */
    Icu_ActivationType                defaultStartEdge;
    /**  \brief xbar to used for input  */
    Icu_XbarSelect                    xbarSelect;
    /**  \brief capture event for interupt enable**/
    Icu_IntrCapSelect                 intrcapSelect;
    /** \brief Measurement Mode to be used */
    Icu_MeasurementModeType           measurementMode;
    /** \brief Signal Measurmenet property to be used if mode choosen */
    Icu_SignalMeasurementPropertyType signalMeasurementProperty;
    /** \brief Notification handler for notifications */
    Icu_NotifyFuncType                notificationHandler;
    /** \brief Buffer Type for Timestamp API mode */
    Icu_TimestampBufferType           bufferType;
    /** \brief Clk src for ICU module in MHz */
    uint32                            instanceClkMHz;
    /** \brief Prescaler value to be used for ICU  module */
    uint32                            prescaler;
} Icu_ChannelConfigType;

/**
 *  \brief ICU Config Structure
 */
typedef struct Icu_ConfigType_s
{
    /** \brief Number of ICU Channel being configured*/
    Icu_ChannelType       icuMaxChannel;
    /** \brief Channel configurations */
    Icu_ChannelConfigType chCfg[ICU_MAX_NUM_CHANNELS];
} Icu_ConfigType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Service for ICU initialization.
 *
 *
 * Initializes internal variables and the ECAP unit of the micro controller.
 * The function can be called on task level.
 *
 *
 * Service ID[hex] - 0x00
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] CfgPtr Pointer to configuration
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_PBCFG) ConfigPtr);

#if (STD_ON == ICU_DE_INIT_API)

/** \brief Service for ICU de-initialization.
 *
 *
 * DeInit ECAP module
 *
 *
 * Service ID[hex] - 0x01
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_DeInit(void);
#endif

/** \brief Service for setting Activation Condition
 *
 *
 * This service sets the Activation edge for channel  Type of
 * activation (if supported by hardware) ICU_RISING_EDGE,
 * ICU_FALLING_EDGE, ICU_BOTH_EDGES.
 *
 *
 * Service ID[hex] - 0x05
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \param[in] Activation - activation edge to be used by ICU module
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE)
Icu_SetActivationCondition(Icu_ChannelType Channel, Icu_ActivationType Activation);

/** \brief Service for disabling notification
 *
 *
 * This service disables the notificaiton of a channel
 *
 *
 * Service ID[hex] - 0x06
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_DisableNotification(Icu_ChannelType Channel);

/** \brief Service for enabling notification
 *
 *
 * This service enables the notificaiton of a channel
 *
 *
 * Service ID[hex] - 0x07
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_EnableNotification(Icu_ChannelType Channel);

#if (ICU_GET_INPUT_STATE_API == STD_ON)
/** \brief Service for getting the ICU input status
 *
 *
 * This service returns the status of the ICU input
 *
 *
 * Service ID[hex] - 0x08
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return Icu_InputStateType
 * \retval ICU_ACTIVE - Module is in active state
 * \retval ICU_IDLE - Module is in idle state
 *
 *****************************************************************************/
FUNC(Icu_InputStateType, ICU_CODE) Icu_GetInputState(Icu_ChannelType Channel);
#endif

#if (ICU_TIMESTAMP_API == STD_ON)
/** \brief Service for starts the captuing of timer values on the edges
 *
 *
 * This service starts the capturing of timer values on the edges
 *
 *
 * Service ID[hex] - 0x09
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel
 * \param[in] BufferSize
 * \param[in] NotifyInterval
 * \param[out] BufferPtr
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE)
Icu_StartTimestamp(Icu_ChannelType Channel, Icu_ValueType* BufferPtr, uint16 BufferSize, uint16 NotifyInterval);

/** \brief Service for stopping the timestamp measurement
 *
 *
 * This service stops timestamp measurement of the given channel.
 *
 *
 * Service ID[hex] - 0x0A
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_StopTimestamp(Icu_ChannelType Channel);

/** \brief Service for reading the timestamp index of a givem channel
 *
 *
 * This service reads the timestamp index of a given channel.
 *
 *
 * Service ID[hex] - 0x0B
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return Icu_IndexType
 * \retval timestamp index value
 *
 *****************************************************************************/
FUNC(Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex(Icu_ChannelType Channel);
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
/** \brief Service for resets the value of the counted edges to zero.
 *
 *
 * This service resets the value of the counted edges to zero.
 *
 *
 * Service ID[hex] - 0x0C
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_ResetEdgeCount(Icu_ChannelType Channel);

/** \brief Service enabling the counting of edges of a given channel.
 *
 *
 * This service enables the couting of edges of the given channel.
 *
 *
 * Service ID[hex] - 0x0D
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_EnableEdgeCount(Icu_ChannelType Channel);

/** \brief Service for disabling the couting of edges of the given channel
 *
 *
 * This service disables the couting of edges of a given channel.
 *
 *
 * Service ID[hex] - 0x0E
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_DisableEdgeCount(Icu_ChannelType Channel);

/** \brief Service for reading the number of counted edges
 *
 *
 * This service reads the number of counted edges.
 *
 *
 * Service ID[hex] - 0x0F
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return Icu_EdgeNumberType
 * \retval Number of counted edges
 *
 *****************************************************************************/
FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers(Icu_ChannelType Channel);
#endif

#if (ICU_EDGE_DETECT_API == STD_ON)
/** \brief Service for enabling/re-enabling the detection of edges of the given channel.
 *
 *
 * This service enables/re-enables the detection of edges of a channel.
 *
 *
 * Service ID[hex] - 0x16
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_EnableEdgeDetection(Icu_ChannelType Channel);

/** \brief Service for disabling the detection of edges of the given channel.
 *
 *
 * This service disables the detection of edges of a channel.
 *
 *
 * Service ID[hex] - 0x17
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_DisableEdgeDetection(Icu_ChannelType Channel);
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/** \brief Service for starting the measurement of signals.
 *
 *
 * This service starts the measurement of signals of a given channel.
 *
 *
 * Service ID[hex] - 0x13
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_StartSignalMeasurement(Icu_ChannelType Channel);

/** \brief Service for stopping the measurement of signals.
 *
 *
 * This service stops the measurement of signals of a given channel.
 *
 *
 * Service ID[hex] - 0x14
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_StopSignalMeasurement(Icu_ChannelType Channel);
#endif

#if (ICU_GET_TIME_ELAPSED_API == STD_ON)
/** \brief Service for reading the elasped time for the given channel
 *
 *
 * This service reads elasped time for a given channel.
 *
 *
 * Service ID[hex] - 0x10
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return Icu_ValueType
 * \retval Elapsed time for the given channel
 *
 *****************************************************************************/
FUNC(Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed(Icu_ChannelType Channel);
#endif

#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)

/** \brief Service for reading the coherent active time and period time of
 * given channel.
 *
 *
 * This service reads active time and period of given channel.
 *
 *
 * Service ID[hex] - 0x11
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \param[out] DutyCycleValues - pointer to store dutycycle
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE)
Icu_GetDutyCycleValues(Icu_ChannelType Channel, Icu_DutyCycleType* DutyCycleValues);
#endif

#if (ICU_GET_VERSION_INFO_API)
/** \brief This service returns the version information of this module.
 *
 *
 * Returns the version information of this module. The function can
 * be called on task level.
 *
 *
 * Service ID[hex] - 0x12
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[out] VersionInfoPtr - Version info.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE)
Icu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, sICU_APPL_DATA) VersionInfoPtr);

#endif

#if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
/** \brief This function checks if a wakeup capable ICU channel is the
 * source for a wakeup event and calls the ECU state manager service
 * EcuM_SetWakeupEvent in case of a valid ICU channel wakeup event.
 *
 *
 * Service ID[hex] - 0x15
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(limited according to ICU050)
 *
 * \param[in] WakeupSource - Informatin on wakeup source to be checked.
 * The associated ICU channel can be determined from configuration data
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
#endif /* if(ICU_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (ICU_DISABLEWAKEUP_API == STD_ON)
/** \brief This function disables the wakeup capability of a single ICU channel.
 *
 *
 * Service ID[hex] - 0x03
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(limited according to ICU050)
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_DisableWakeup(Icu_ChannelType Channel);
#endif /* if(ICU_DISABLEWAKEUP_API == STD_ON) */

#if (ICU_ENABLEWAKEUP_API == STD_ON)
/** \brief This function (re-)enables the wakeup capability of the given ICU channel.
 *
 *
 * Service ID[hex] - 0x04
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(limited according to ICU050)
 *
 * \param[in] Channel - Numeric identifier of the ICU channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_EnableWakeup(Icu_ChannelType Channel);
#endif /* if(ICU_ENABLEWAKEUP_API == STD_ON) */

#if (ICU_SETMODE_API == STD_ON)
/** \brief This function sets the ICU mode.
 *
 *
 * Service ID[hex] - 0x02
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Mode - ICU_MODE_NORMAL: Normal operation, all used interrupts are
 *                       enabled according to the notification requests,
 *                 ICU_MODE_SLEEP: Reduced power mode. In sleep mode only those
 *                       notifications are available which are configured as
 *                       wakeup capable.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ICU_CODE) Icu_SetMode(Icu_ModeType Mode);
#endif /* if (ICU_SETMODE_API == STD_ON) */

#if (STD_ON == ICU_REGISTER_READBACK_API)
/** \brief This function reads the important registers of the hardware unit
 * and returns the value in the structure.
 *
 *
 * This API is used to check the status of critical registers which donot
 * change during program execution.
 *
 * Service ID[hex] - 0x15
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] ChannelNumber - Numeric identifier of the ICU channel
 * \param[inout] RegRbPtr - Pointer to where to store the readback  values.
 * If this pointer is NULL, then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK - Register read back has been done successfully
 * \retval E_NOT_OK - Register read back failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, ICU_CODE)
Icu_RegisterReadback(Icu_ChannelType Channel, P2VAR(Icu_RegisterReadbackType, AUTOMATIC, ICU_APPL_DATA) RegRbPtr);
#endif

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ICU_H_ */
