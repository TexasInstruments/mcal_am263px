/* ======================================================================
 *   Copyright (C) 2022 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     Gpt.h
 *
 *  \brief    This file contains interface header for GPT MCAL driver
 *
 */

/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt.h
 *    Component:  AM263x MCAL Driver
 *       Module:  GptDriver
 *    Generator:  None
 *
 *  Description: This component provides services for initialization and control of the
 *microcontroller internal GPT unit (General Purpose Timer).
 *********************************************************************************************************************/

#ifndef GPT_H_
#define GPT_H_

/**
 * \defgroup GPT Gpt API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Gpt_Cfg.h"
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* include for Wakeup handling */
#include "EcuM_Cbk.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name GPT Driver Module SW Version Info
 *
 *  Defines for GPT Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define GPT_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define GPT_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation Patch Version */
#define GPT_SW_PATCH_VERSION (1U)
/**   @} */

/**
 *  \name GPT Driver Module AUTOSAR Version Info
 *
 *  Defines for GPT Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by GPT Driver */
#define GPT_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by GPT Driver */
#define GPT_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by GPT Driver */
#define GPT_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/**
 *  \name GPT Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define GPT_VENDOR_ID ((uint16)44U)
/** \brief GPT Driver Module ID */
#define GPT_MODULE_ID ((uint16)100U)
/** \brief GPT Driver Instance ID */
#define GPT_INSTANCE_ID ((uint8)0U)
/**   @} */
/**
 *  \name GPT Driver ISR category level
 *
 *  Defines for GPT Driver ISR ISR category level
 *  @{
 */
/** \brief GPT continuous mode index */
#define GPT_CH_ISR_MODE_CONTINUOUS (0U)
/** \brief GPT oneshot mode index */
#define GPT_CH_ISR_MODE_ONESHOT (1U)
/** \brief GPT continuous wakeup mode index */
#define GPT_CH_ISR_MODE_CONT_WAKEUP (2U)
/** \brief GPT oneshot wakeup mode index */
#define GPT_CH_ISR_MODE_ONESHOT_WAKEUP (3U)
/**   @} */

/** \brief Driver status UN INITIALIZED */
#define GPT_DRIVER_UNINITIALIZED ((uint32)0U)
/** \brief Driver status INITIALIZED */
#define GPT_DRIVER_INITIALIZED ((uint32)1U)

/** \brief Masks the higher order bits to evaluate compare block (lsb0 and lsb1) */
#define CH_COMP_MASK ((uint32)0x00000003)

/**
 *  \name GPT Error Codes
 *
 *  Error codes returned by GPT functions
 *  @{
 */
#ifndef GPT_E_UNINIT
/** \brief API service used without module initialization */
#define GPT_E_UNINIT (0x0AU)
#endif
#ifndef GPT_E_BUSY
/**
 *  \brief API service called during ongoing process (Timer is already
 *  running)
 */
#define GPT_E_BUSY (0x0BU)
#endif
#ifndef GPT_E_MODE
/** \brief API service called when driver is in wrong mode */
#define GPT_E_MODE (0x0CU)
#endif
#ifndef GPT_E_ALREADY_INITIALIZED
/** \brief API Gpt_Init is called but the module is already initialized. */
#define GPT_E_ALREADY_INITIALIZED (0x0DU)
#endif
#ifndef GPT_E_INIT_FAILED
/** \brief API Gpt_Init is called but the module is already initialized. */
#define GPT_E_INIT_FAILED (0x0EU)
#endif
#ifndef GPT_E_PARAM_CHANNEL
/** \brief API called with invalid channel. */
#define GPT_E_PARAM_CHANNEL (0x14U)
#endif
#ifndef GPT_E_PARAM_VALUE
/** \brief API servcie called with invalid start timer parameter */
#define GPT_E_PARAM_VALUE (0x15U)
#endif
#ifndef GPT_E_PARAM_POINTER
/** \brief API servcie called with invalid(Null_Ptr) data buffer pointer. */
#define GPT_E_PARAM_POINTER (0x16U)
#endif
#ifndef GPT_E_PARAM_PREDEF_TIMER
/** \brief API service called with invalid Predef Timer. */
#define GPT_E_PARAM_PREDEF_TIMER (0x17U)
#endif
#ifndef GPT_E_PARAM_MODE
/** \brief Gpt_SetMode is called with wrong mode parameter. */
#define GPT_E_PARAM_MODE (0x1FU)
#endif
#ifndef GPT_E_INVALID_ISR
/** \brief Invalid entry to ISR. */
#define GPT_E_INVALID_ISR (0x80U)
#endif
/**   @} */

/**
 *  \name GPT Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief Gpt_GetVersionInfo() API Service ID */
#define GPT_SID_GET_VERSION_INFO (0x00U)
/** \brief Gpt_Init() API Service ID */
#define GPT_SID_INIT (0x01U)
/** \brief Gpt_DeInit() API Service ID */
#define GPT_SID_DEINIT (0x02U)
/** \brief Gpt_GetTimeElapsed() API Service ID */
#define GPT_SID_GET_TIME_ELAPSED (0x03U)
/** \brief Gpt_GetTimeRemaining() API Service ID */
#define GPT_SID_GET_TIME_REMAINING (0x04U)
/** \brief Gpt_StartTimer() API Service ID */
#define GPT_SID_START_TIMER (0x05U)
/** \brief Gpt_StopTimer() API Service ID */
#define GPT_SID_STOP_TIMER (0x06U)
/** \brief Gpt_EnableNotification() API Service ID */
#define GPT_SID_ENABLE_NOTIFY (0x07U)
/** \brief Gpt_DisableNotification() API Service ID */
#define GPT_SID_DISABLE_NOTIFY (0x08U)
/** \brief Gpt_SetMode() API Service ID */
#define GPT_SID_SET_MODE (0x09U)
/** \brief Gpt_DisableWakeup() API Service ID */
#define GPT_SID_DISABLE_WAKEUP (0x0AU)
/** \brief Gpt_EnableWakeup() API Service ID */
#define GPT_SID_ENABLE_WAKEUP (0x0BU)
/** \brief Gpt_CheckWakeup() API Service ID */
#define GPT_SID_CHECK_WAKEUP (0x0CU)
/** \brief Gpt_GetPredefTimerValue() API Service ID */
#define GPT_SID_GET_PREDEFTIMERVALUE (0x0DU)
/** \brief GPT Get Hw Unit Obj API Service ID */
#define GPT_SID_GET_GETHWUNITOBJ (0x0EU)
/** \brief GPT Gpt_ConfigRegReadBack API Service ID */
#define GPT_SID_GET_CONFIG_REG_READBACK (0x0FU)
/**   @} */

/** \brief Maximum resolution for the timer */
#define MAX_RESOLUTION 0xFFFFFFFFU

/* Klocwork Inspected
 * MISRA C 2012 Dir 4.9
   Reason: Macro cannot be avoided here as sending type as an argument
 */
/** \brief Set a bit  */
#define SET(type, var, bit) (var |= (type)(((uint32)1U) << bit))
/** \brief Clear a bit  */
#define CLEAR(type, var, bit) (var &= (~((type)(((uint32)1U) << bit))))

#if (STD_ON == GPT_REGISTER_READBACK_API)

/** \brief GPT register readback structure  */

/*Type for Register readback of configuration registers*/
typedef struct GptConfigRegTag
{
    /** \brief RTI Global Control Register*/
    uint32 GPT_GCTRL;
    /** \brief RTI Timebas Control Register*/
    uint32 GPT_TBCTRL;
    /** \brief RTI Compare Control Register*/
    uint32 GPT_COMPCTRL;
    /** \brief RTI Update Compare 0 Register*/
    uint32 GPT_UDCP0;
    /** \brief RTI Update Compare 1 Register*/
    uint32 GPT_UDCP1;
    /** \brief RTI Update Compare 2 Register*/
    uint32 GPT_UDCP2;
    /** \brief RTI Update Compare 3 Register*/
    uint32 GPT_UDCP3;
} GptConfigReg;

#endif /* #if (STD_ON == GPT_REGISTER_READBACK_API) */

/*********************************************************************************************************************
 * Exported Preprocessor #define Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Exported Type Declarations
 *********************************************************************************************************************/

/*
 * Design: MCAL-16426
 */
/** \brief Type describing the Gpt channel */
typedef uint32 Gpt_ChannelType;

/*
 * Design: MCAL-16425
 */
/** \brief  Type describing the timeout value  */
typedef uint32 Gpt_ValueType;

/** \brief  Type describing the counter block to use for GPT */
typedef uint32 Gpt_CntId;

/*
 * Design: MCAL-16424
 */
/** \brief  List of process modes  */
typedef enum
{
    /** \brief GPT initialized */
    GPT_MODE_UNITIALIZED = 0U,
    /** \brief Normal operation mode of the GPT */
    GPT_MODE_NORMAL,
    /** \brief Operation for reduced power operation mode. In sleep mode only wakeup
     *  capable channels are available.*/
    GPT_MODE_SLEEP
} Gpt_ModeType;

/** \brief Type for GPT Predefined(free running) Timers */
typedef enum
{
    /** \brief GPT Predef Timer is undefined*/
    GPT_PREDEF_UNDEFINED = 0U,
    /** \brief GPT Predef Timer with tick duration 1us and range 16bit*/
    GPT_PREDEF_TIMER_1US_16BIT = 1U,
    /** \brief GPT Predef Timer with tick duration 1us and range 24bit*/
    GPT_PREDEF_TIMER_1US_24BIT = 2U,
    /** \brief GPT Predef Timer with tick duration 1us and range 32bit*/
    GPT_PREDEF_TIMER_1US_32BIT = 3U,
    /** \brief GPT Predef Timer with tick duration 100us and range 32bit*/
    GPT_PREDEF_TIMER_100US_32BIT = 4U
} Gpt_PredefTimerType;

/*
 * Design: MCAL-16444, MCAL-16439, MCAL-16441, MCAL-16443, MCAL-16440, MCAL-16442, MCAL-16438
 */
/** \brief  Notification callback function pointer  */
typedef void (*Gpt_NotifyType)(void);

/** \brief Type for specifying source clock selection  */
typedef uint32 Gpt_ClockSourceType;

/** \brief  GPT channel mode macros.  */
typedef enum
{
    /** \brief After reaching the target time, the timer continues running
     * with the value "zero" again */
    GPT_CH_MODE_CONTINUOUS = 0U,
    /** \brief After reaching the target time, the timer stops automatically
     * (timer expired).  */
    GPT_CH_MODE_ONESHOT,

    GPT_CH_MODE_CONT_WAKEUP,

    GPT_CH_MODE_ONESHOT_WAKEUP
} Gpt_ChannelMode;

/**  \brief  List of Prescale values for General purpose timer channels
 *          The timer counter is prescaled with the value 2^(PTV+1).
 *          Example: PTV = 3, counter increases value (if started) after 16
 *          functional clock periods
 *  Note: Not applicable to GPT Predef timers.
 */
typedef enum
{
    GPT_PRESCALE_UNDEFINED
} Gpt_PrescaleValueType;

/** \brief  GPT channel state
 *         GPT will be in one of this state during its lifetime.
 */
typedef enum
{
    /** \brief GPT is uninitialized */
    GPT_UNINITIALIZED = 0U,
    /** \brief GPT is initialized */
    GPT_INITIALIZED,
    /** \brief GPT is running */
    GPT_RUNNING,
    /** \brief GPT is stopped */
    GPT_STOPPED,
    /** \brief GPT is expired */
    GPT_EXPIRED
} Gpt_ChannelStateType;

/** \brief  Configuration per channel */

typedef struct
{
    /** \brief Channel Id */
    Gpt_ChannelType     ChannelId;
    /** \brief Channel mode */
    /*TI_INSPECTED 217 S : MISRAC_2012_R.4.5
     * "Reason - the variable is used in the GPT context not an issue. " */
    Gpt_ChannelMode     ChannelMode;
    /** \brief GPT Counter Block */
    Gpt_CntId           CounterBlk;
    /** \brief Specifies the tick frequency of the timer channel in Hz */
    uint32              GptChannelTickFrequency;
    /** \brief Maximum value in ticks, the timer channel is able to count. With the
     *   next tick, the timer rolls over to zero
     *   TODO: ECUC_Gpt_00332 how to implement this with current HW? */
    uint32              tickValueMax;
    /** \brief Enables wakeup capability of MCU for a channel */
    uint8               GptEnableWakeup;
    /** \brief Function pointer to callback function (for non-wakeup notification) */
    Gpt_NotifyType      Notification_pt;
    /** \brief Reference to the GptClockReferencePoint from which the channel
     *   clock is derived */
    Gpt_ClockSourceType GptChannelClksrcRef;
    /** \brief Channel wakeup source, in case the wakeup-capability is true this value
     *   is transmitted to the EcuState Manager */
    uint8               GptWakeupSourceRef;
} Gpt_ChannelConfigType;

/*
 *Design: MCAL-16427
 */
/** \brief  global configuration of the driver  */
typedef struct Gpt_ConfigType_s
{
    /** \brief  Pointer to Channel list */
    P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONST) ChannelConfig_pt;
    /** \brief  Number of channels configured  */
    uint32 ChannelCount;
} Gpt_ConfigType;

/** \brief  Driver object  */
typedef struct
{
    /** \brief  Driver Object to Channel list */
    Gpt_ChannelConfigType gChannelConfig_pt[GPT_RTI_MAX];
    /** \brief  Number of channels configured  */
    uint32                ChannelCount;

} Gpt_DriverObjType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == GPT_VERSION_INFO_API)
/** \brief This service returns the version information of this module.
 *
 *
 * Returns the version information of this module
 *
 * Service ID[hex] - 0x00
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[out] VersionInfoPtr - Pointer to where to store the version
 * information of this module
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE)
Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) VersionInfoPtr);
#endif /*(STD_ON == GPT_VERSION_INFO_API)*/

/** \brief This service Initializes the GPT driver.
 *
 *
 * This service initializes all the configured Gpt channels. This will set
 * the state of the each channel to"initialized", also set the Gpt
 * driver state to "Normal".
 *
 * Service ID[hex] - 0x01
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ConfigPtr - configuration structure for initializing the module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_Init(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_CONST) configPtr);

#if (STD_ON == GPT_DEINIT_API)
/** \brief This service deinitializes the GPT driver.
 *
 *
 * This service deinitializes the RTI used by Gpt driver to the power on
 * reset state. The Gpt driver state is changed to "Uninitialized" state".
 * All the channel registers are cleared to stop the timer channels.
 * API will disable all interrupt notifications, wakeup interrupts.
 *
 * Service ID[hex] - 0x02
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_DeInit(void);
#endif /*(STD_ON == GPT_DEINIT_API)*/

#if (STD_ON == GPT_TIME_ELAPSED_API)
/** \brief This service Returns the time already elapsed.
 *
 *
 * Gpt_GetTimeElapsed will return the time elapsed for channel which is
 * referenced. The user can configure the channel in two modes, One-shot
 * and Continuous mode. In one shot mode, if the timer is in stopped
 * state, the function will return time value at the moment of stopping.
 * If the timer is expired, the function will return the target time
 * configured for the channel. In Continuous Mode - The elapsed time
 * value will be the value relative to last occurrence.
 *
 * Service ID[hex] - 0x03
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - ChannelId of the Gpt channel.
 * \return Gpt_ValueType
 * \retval Elapsed timer value (in number of ticks)
 *
 *****************************************************************************/
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed(Gpt_ChannelType channel);
#endif /*(STD_ON == GPT_TIME_ELAPSED_API)*/

#if (STD_ON == GPT_TIME_REMAINING_API)
/** \brief This service returns the time remaining until the target time is
 *  reached.
 *
 *
 * Gpt_GetTimeRemaining will return the timer value remaining until the
 * target time will be reached next time. The remaining time is target
 * time minus time already elapsed. In one shot mode, if the timer is in
 * stopped state, the function will return remaining time value at the
 * moment of stopping. If the timer is expired, the function will
 * return 0.
 *
 * Service ID[hex] - 0x04
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - ChannelId of the Gpt channel.
 * \return Gpt_ValueType
 * \retval Remaining timer value (in number of ticks)
 *
 *****************************************************************************/
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining(Gpt_ChannelType channel);
#endif /*(STD_ON == GPT_CFG_CFG_TIME_REMAINING_API)*/

/** \brief This service starts a timer channel.
 *
 *
 * Gpt_StartTimer will start the selected timer channel with defined
 * target time. If the timer channel is enabled for interrupt
 * notification, then interrupt notification will be triggered after
 * expiration of the selected timer channel. In one shot mode, if the
 * timer is expired then the channel will be stopped in interrupt
 * subroutine. The selected channel will be moved to "Running" state
 * after calling this function.
 *
 * Service ID[hex] - 0x05
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - ChannelId of the Gpt channel.
 * \param[in] value - Target time in number of ticks.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_StartTimer(Gpt_ChannelType channel, Gpt_ValueType value);

/** \brief This service stops a timer channel.
 *
 *
 * Gpt_StopTimer will stop the selected timer channel.This will clear
 * all the registers corresponding to the selected channel. The state of
 * the timer channel will be changed to "Stopped".If the channel is in
 * state "Initialized","Expired","Stopped" before calling this function,
 * the function will be left without any action.
 *
 * Service ID[hex] - 0x06
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(but not for the same timer channel)
 *
 * \param[in] Channel - Numeric identifier of the GPT channel.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_StopTimer(Gpt_ChannelType channel);

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
/** \brief This service enables the interrupt notification for a channel
 * (relevant in normal mode).
 *
 *
 * Gpt_EnableNotification will enable the interrupt notification for the
 * selected channel. The SETINT bit in RTI Set interrupt register will
 * be Set to enable the Compare interrupt. The interrupt is triggered
 * when Free running counter value matches with compare register value.
 *
 * Service ID[hex] - 0x07
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(but not for the same timer channel)
 *
 * \param[in] Channel - Numeric identifier of the GPT channel.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_EnableNotification(Gpt_ChannelType channel);
#endif /*(STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)*/

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
/** \brief This service disables the interrupt notification for a channel
 * (relevant in normal mode).
 *
 *
 * Gpt_DisableNotification will disable the compare interrupt
 * notification for the selected channel. The SETINT bit in RTI Set interrupt
 * register will be cleared to disable the Compare interrupt. The
 * interrupt is triggered when Free running counter value matches with
 * compare register value.
 *
 * Service ID[hex] - 0x08
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(but not for the same timer channel)
 *
 * \param[in] Channel - Numeric identifier of the GPT channel.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_DisableNotification(Gpt_ChannelType channel);
#endif /*(STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)*/

#if (STD_ON == GPT_REGISTER_READBACK_API)
/** \brief This function reads the important registers of the hardware unit
 *  and returns the value in the structure.
 *
 *
 *  This API should be called after Gpt_Init is called. Otherwise this API will
 *  return E_NOT_OK.
 *
 *  This API could be used to readback the register contents after Gpt_Init
 *  and then the readback value could be compared during GPT execution to
 *  check the correctness of the HW unit. Since this API is used for this
 *  purpose, the register returned are the ones which doesn't change after init
 *  based on conv or channel config.
 *
 * Service ID[hex] - 0x0F
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(but not for the same timer channel)
 *
 * \param[in] GptChannel - Numeric identifier of the GPT channel.
 * If this is invalid, then the API will return E_NOT_OK.
 * \param[inout] RegRbPtr - Pointer to where to store the readback values.
 * If this pointer is NULL_PTR, then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK - Register read back has been done
 * \retval E_NOT_OK - Register read back failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, GPT_CODE)
Gpt_ConfigRegReadBack(Gpt_ChannelType channel, GptConfigReg* GptConfigReg_pt);
#endif /* #if (STD_ON == GPT_REGISTER_READBACK_API) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/** \brief This function checks if a wakeup capable GPT channel is the
 *  source for a wakeup event and calls the ECU state manager service
 *  EcuM_SetWakeupEvent in case of a valid GPT channel wakeup event.
 *
 *
 * Service ID[hex] - 0x0C
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] WakeupSource - Information on wakeup source to be checked.
 * The associated GPT channel can be determined from configuration data.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/** \brief This service disables the wakeup interrupt of a channel
 * (relevant in sleep mode)
 *
 *
 * Service ID[hex] - 0x0A
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(but not for the same timer channel)
 *
 * \param[in] Channel - Numeric Identifier of the GPT Channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_DisableWakeup(Gpt_ChannelType Channel);
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/** \brief This Function enables the wakeup interrupt of a channel
 * (relevant in sleep mode)
 *
 *
 * Service ID[hex] - 0x0B
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant(but not for the same timer channel)
 *
 * \param[in] Channel - Numeric Identifier of the GPT Channel
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_EnableWakeup(Gpt_ChannelType Channel);
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

/** \brief This Function delivers the current value of the desired GPT Predef Timer.
 *
 *
 * Service ID[hex] - 0x0D
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] PredefTimer - GPT Predef Timer
 * \param[out] TimeValuePtr - Pointer to time value destination data in RAM
 * \return Std_ReturnType
 * \retval E_OK: no error has been detected
 * \retval E_NOT_OK: aborted due to errors
 *
 *****************************************************************************/
FUNC(Std_ReturnType, GPT_CODE)
Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr);

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/** \brief This Function sets the operation mode of the GPT.
 *
 *
 * Service ID[hex] - 0x09
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Mode -GPT_MODE_NORMAL: Normal operation mode of the GPT driver.
 * GPT_MODE_SLEEP: Sleep mode of the GPT driver (wakeup capable).
 * See also Gpt_ModeType
 * \param[out] TimeValuePtr - Pointer to time value destination data in RAM
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, GPT_CODE) Gpt_SetMode(Gpt_ModeType Mode);
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef GPT_H_ */
