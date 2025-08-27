/*
 *
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Adc.h
 *
 *  \brief    This file contains interface header for ADC MCAL driver
 *
 */

/*
 * Below are the global design requirements which are met by this ADC
 * driver which can't be mapped to a particular source ID
 */
/*
 * Design: MCAL-5723,MCAL-5861
 */

/*
 * Below are the ADC's module environment design requirements which can't
 * be mapped to this driver
 */
/*
 * Design: MCAL-5805,MCAL-5708,MCAL-5739,MCAL-5748
 */

/*
 * Note: MCAL-5700,MCAL-5834 are prerequisites which are done by SBL/GEL files.
 */

#ifndef ADC_H_
#define ADC_H_

/**
 * \defgroup ADC Adc API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Adc_Cfg.h"
#include "Adc_Priv.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Version Checks                                  */
/* ========================================================================== */

/**
 *  \name ADC Driver Module SW Version Info
 *
 *  Defines for ADC Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define ADC_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define ADC_SW_MINOR_VERSION (1U)
/** \brief Driver Implementation Patch Version */
#define ADC_SW_PATCH_VERSION (1U)
/**   @} */

/**
 *  \name ADC Driver Module AUTOSAR Version Info
 *
 *  Defines for ADC Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by ADC Driver */
#define ADC_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by ADC Driver */
#define ADC_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by ADC Driver */
#define ADC_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/**
 *  \name ADC Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define ADC_VENDOR_ID ((uint16)44U)
/** \brief ADC Driver Module ID */
#define ADC_MODULE_ID ((uint16)123U)
/** \brief ADC Driver Instance ID */
#define ADC_INSTANCE_ID ((uint8)0U)
/**   @} */

/**
 *  \name Boolean Macros for ADC module
 *  @{
 */
/** \brief Boolean Macros for ADC module */
#define ADC_TRUE (TRUE)
/** \brief Boolean Macros for ADC module */
#define ADC_FALSE (FALSE)
/**   @} */

/**
 *  \name ADC Driver ISR category level
 *
 *  Defines for ADC Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define ADC_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define ADC_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define ADC_ISR_CAT2 (0x02U)
/**   @} */

/**
 *  \name ADC Error Codes
 *
 *  Error codes returned by ADC functions
 *  @{
 */
/*
 *Design:  MCAL-14433
 */
#ifndef ADC_E_UNINIT
/** \brief API service used without module initialization */
#define ADC_E_UNINIT ((uint8)0x0AU)
#endif
#ifndef ADC_E_BUSY
/** \brief API service called during ongoing process */
#define ADC_E_BUSY ((uint8)0x0BU)
#endif
#ifndef ADC_E_IDLE
/** \brief API service called while no conversion is ongoing. */
#define ADC_E_IDLE ((uint8)0x0CU)
#endif
#ifndef ADC_E_ALREADY_INITIALIZED
/**
 *  \brief API Adc_Init service called while the ADC driver has already been
 *  initialized
 */
#define ADC_E_ALREADY_INITIALIZED ((uint8)0x0DU)
#endif
#ifndef ADC_E_PARAM_CONFIG
/** \brief API service called with incorrect configuration parameter. */
#define ADC_E_PARAM_CONFIG ((uint8)0x0EU)
#endif
#ifndef ADC_E_PARAM_POINTER
/** \brief API servcie called with invalid data buffer pointer. */
#define ADC_E_PARAM_POINTER ((uint8)0x14U)
#endif
#ifndef ADC_E_PARAM_GROUP
/** \brief API servcie called with invalid group ID. */
#define ADC_E_PARAM_GROUP ((uint8)0x15U)
#endif
#ifndef ADC_E_WRONG_CONV_MODE
/**
 *  \brief API service called on a group with conversion mode configured as
 *  continuous.
 */
#define ADC_E_WRONG_CONV_MODE ((uint8)0x16U)
#endif
#ifndef ADC_E_WRONG_TRIGG_SRC
/** \brief API servcie called for group with wrong trigger source */
#define ADC_E_WRONG_TRIGG_SRC ((uint8)0x17U)
#endif
#ifndef ADC_E_NOTIF_CAPABILITY
/**
 *  \brief Enable/disable notification function for a group whose configuration
 *  set has no notification available.
 */
#define ADC_E_NOTIF_CAPABILITY ((uint8)0x18U)
#endif
#ifndef ADC_E_BUFFER_UNINIT
/** \brief Conversion started and result buffer pointer is not initialized. */
#define ADC_E_BUFFER_UNINIT ((uint8)0x19U)
#endif
#ifndef ADC_E_NOT_DISENGAGED
/** \brief One or more ADC group/channel not in IDLE state. */
#define ADC_E_NOT_DISENGAGED ((uint8)0x1AU)
#endif
#ifndef ADC_E_POWER_STATE_NOT_SUPPORTED
/** \brief Unsupported power state request. */
#define ADC_E_POWER_STATE_NOT_SUPPORTED ((uint8)0x1BU)
#endif
#ifndef ADC_E_TRANSITION_NOT_POSSIBLE
/** \brief Requested power state can not be reached directly. */
#define ADC_E_TRANSITION_NOT_POSSIBLE ((uint8)0x1CU)
#endif
#ifndef ADC_E_PERIPHERAL_NOT_PREPARED
/** \brief ADC not prepared for target power state. */
#define ADC_E_PERIPHERAL_NOT_PREPARED ((uint8)0x1DU)
#endif
/**   @} */
/**
 *  \name ADC Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief Adc_Init() API Service ID */
#define ADC_SID_INIT ((uint8)0x00U)
/** \brief Adc_DeInit() API Service ID */
#define ADC_SID_DEINIT ((uint8)0x01U)
/** \brief Adc_StartGroupConversion() API Service ID */
#define ADC_SID_START_GROUP_CONVERSION ((uint8)0x02U)
/** \brief Adc_StopGroupConversion() API Service ID */
#define ADC_SID_STOP_GROUP_CONVERSION ((uint8)0x03U)
/** \brief Adc_ReadGroup() API Service ID */
#define ADC_SID_READ_GROUP ((uint8)0x04U)
/** \brief Adc_EnableHardwareTrigger() API Service ID */
#define ADC_SID_ENABLE_HARDWARE_TRIGGER ((uint8)0x05U)
/** \brief Adc_DisableHardwareTrigger() API Service ID */
#define ADC_SID_DISABLE_HARDWARE_TRIGGER ((uint8)0x06U)
/** \brief Adc_EnableGroupNotification() API Service ID */
#define ADC_SID_ENABLE_GROUP_NOTIFICATION ((uint8)0x07U)
/** \brief Adc_DisableGroupNotification() API Service ID */
#define ADC_SID_DISABLE_GROUP_NOTIFICATION ((uint8)0x08U)
/** \brief Adc_GetGroupStatus() API Service ID */
#define ADC_SID_GET_GROUP_STATUS ((uint8)0x09U)
/** \brief Adc_GetVersionInfo() API Service ID */
#define ADC_SID_GET_VERSION_INFO ((uint8)0x0AU)
/** \brief Adc_GetStreamLastPointer() API Service ID */
#define ADC_SID_GET_STREAM_LAST_POINTER ((uint8)0x0BU)
/** \brief Adc_SetupResultBuffer() API Service ID */
#define ADC_SID_SETUP_RESULT_BUFFER ((uint8)0x0CU)
/** \brief Adc_SetPowerState() API Service ID */
#define ADC_SID_SET_POWER_STATE ((uint8)0x10U)
/** \brief Adc_GetCurrentPowerState() API Service ID */
#define ADC_SID_GET_CURRENT_POWER_STATE ((uint8)0x11U)
/** \brief Adc_GetTargetPowerState() API Service ID */
#define ADC_SID_GET_TARGET_POWER_STATE ((uint8)0x12U)
/** \brief Adc_PreparePowerState() API Service ID */
#define ADC_SID_PREPARE_POWER_STATE ((uint8)0x13U)
/** \brief Adc_Main_PowerTransitionManager() API Service ID */
#define ADC_SID_MAIN_POWER_TRANSITION_MANAGER ((uint8)0x14U)
/** \brief IoHwAb_AdcNotification() API Service ID */
#define ADC_SID_IOHWAB_NOTIFICATION ((uint8)0x20U)
/** \brief IoHwAb_Adc_NotifyReadyForPowerState() API Service ID */
#define ADC_SID_IOHWAB_NOTIFY_READY_FOR_POWER_STATE ((uint8)0x70U)
/** \brief IoHwAb_Adc_NotifyReadyForPowerState() API Service ID */
#define ADC_SID_READ_TEMPERATURE ((uint8)0x0DU)
/** \brief IoHwAb_Adc_NotifyReadyForPowerState() API Service ID */
#define ADC_SID_READ_TEMPERATURE_RESULT ((uint8)0x0EU)
/** \brief Adc_PollingMainFunction() API Service ID */
#define ADC_SID_POLLING_MAINFUNCTION ((uint8)0x15U)
/** \brief Adc_RegisterReadback() API Service ID */
#define ADC_SID_REGISTER_READBACK ((uint8)0x16U)
/** \brief Adc_GetReadResultBaseAddress() API Service ID */
#define ADC_SID_GET_READ_RESULT_BASE_ADDRESS ((uint8)0x17U)
/** \brief Adc_SetInterruptContinuousMode() API Service ID */
#define ADC_SID_SET_INTERRUPT_CONTINUOUS_MODE ((uint8)0x18U)

/**   @} */
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Service for ADC initialization.
 *
 *
 * Initializes the ADC hardware units and driver
 *
 * Service ID[hex] - 0x00
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] CfgPtr Pointer to configuration set in Variant PB
 * (Variant PC requires a NULL_PTR).
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_Init(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_PBCFG) CfgPtr);

#if (STD_ON == ADC_DEINIT_API)
/** \brief This service sets all ADC HW Units to a state comparable to their
 *  power on reset state
 *
 *
 * Returns all ADC HW Units to a state comparable to their power on reset state
 *
 * Service ID[hex] - 0x01
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_DeInit(void);
#endif /* #if (STD_ON == ADC_DEINIT_API) */

/** \brief This service initializes ADC driver with the group specific result
 *  buffer start address where the conversion results will be stored.
 *
 *
 * Initializes ADC driver with the group specific result buffer start address
 * where the conversion results will be stored. The application has to ensure
 * that the application buffer, where DataBufferPtr points to, can hold all
 * the conversion results of the specified group.
 * The initialization with Adc_SetupResultBuffer is required after reset,
 * before a group conversion can be started.
 *
 * Service ID[hex] - 0x0C
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \param[in] DataBufferPtr pointer to result data buffer
 * \return Std_ReturnType
 * \retval E_OK - result buffer pointer initialized correctly
 * \retval E_NOT_OK - operation failed or development error occurred
 *
 *****************************************************************************/
FUNC(Std_ReturnType, ADC_CODE)
Adc_SetupResultBuffer(Adc_GroupType Group, const Adc_ValueGroupType *DataBufferPtr);

/** \brief Returns the conversion status of the requested ADC Channel group.
 *
 *
 * Returns the conversion status of the requested ADC Channel group.
 *
 * Service ID[hex] - 0x09
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \return Adc_StatusType - Conversion status for the requested group.
 * \retval ADC_IDLE: The conversion of the specified group has not been started
 * \retval ADC_BUSY: The conversion of the specified group has been started and is still
 * going on.
 * \retval ADC_COMPLETED: The conversion of the specified group has been finished.
 * \retval ADC_STREAM_COMPLETED: The result buffer is completely filled.
 *
 *****************************************************************************/
FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus(Adc_GroupType Group);

/** \brief Returns the number of valid samples per channel, stored in the
 *  result buffer.
 *
 *
 * Returns the number of valid samples per channel, stored in the result buffer.
 * Reads a pointer, pointing to a position in the group result buffer. With the
 * pointer position, the results of all group channels of the last completed
 * conversion round can be accessed. With the pointer and the return value,
 * all valid group conversion results can be accessed (the user has to take the
 * layout of the result buffer into account).
 *
 *
 * Service ID[hex] - 0x0B
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \param[out] PtrToSamplePtr Pointer to result buffer pointer.
 * \return Adc_StreamNumSampleType
 * \retval Number of valid samples per channel
 *
 *****************************************************************************/
FUNC(Adc_StreamNumSampleType, ADC_CODE)
Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr);

#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
/** \brief Starts the conversion of all channels of the requested ADC
 *  Channel group
 *
 *
 * Starts the conversion of all channels of the requested ADC Channel group.
 *
 * Service ID[hex] - 0x02
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_StartGroupConversion(Adc_GroupType Group);

/** \brief Stops the conversion of the requested ADC Channel group
 *
 *
 * Stops the conversion of the requested ADC Channel group.
 *
 * Service ID[hex] - 0x03
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_StopGroupConversion(Adc_GroupType Group);
#endif /* #if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) */

#if (STD_ON == ADC_READ_GROUP_API)
/** \brief Reads the group conversion result of the last completed conversion
 *  round of the requested group and stores the channel values starting at
 *  the DataBufferPtr address
 *
 *
 * Reads the group conversion result of the last completed conversion round of the
 * requested group and stores the channel values starting at the DataBufferPtr
 * address. The group channel values are stored in ascending channel number order
 * (in contrast to the storage layout of the result buffer if streaming access is
 * configured).
 *
 * Service ID[hex] - 0x04
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \param[in] DataBufferPtr ADC results of all channels of the selected group
 * are stored in the data buffer addressed with the pointer
 * \return Std_ReturnType
 * \retval E_OK - results are available and written to the data buffer
 * \retval E_NOT_OK - no results are available or development error occurred
 *
 *****************************************************************************/
FUNC(Std_ReturnType, ADC_CODE)
Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr);
#endif /* #if (STD_ON == ADC_READ_GROUP_API) */

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY_API)
/** \brief Enables the notification mechanism for the requested ADC Channel
 *   group.
 *
 *
 * Enables the notification mechanism for the requested ADC Channel group.
 *
 * Service ID[hex] - 0x07
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_EnableGroupNotification(Adc_GroupType Group);

/** \brief Disables the notification mechanism for the requested ADC Channel
 *   group.
 *
 *
 * Disables the notification mechanism for the requested ADC Channel group.
 *
 * Service ID[hex] - 0x08
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_DisableGroupNotification(Adc_GroupType Group);
#endif /* #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY_API) */

#if (STD_ON == ADC_VERSION_INFO_API)
/** \brief This service returns the version information of this module.
 *
 *
 * Returns the version information of this module
 *
 * Service ID[hex] - 0x0A
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[out] versioninfo Pointer to where to store the version information of
 * this module
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE)
Adc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ADC_APPL_DATA) versioninfo);
#endif /* #if (STD_ON == ADC_VERSION_INFO_API) */

#if (STD_ON == ADC_REGISTER_READBACK_API)
/** \brief This function reads the important registers of the hardware unit
 *  and returns the value in the structure.
 *
 *
 * This API should be called after Adc_Init is called. Otherwise this API will
 * return E_NOT_OK.
 * This API could be used to readback the register contents after Adc_Init
 * and then the readback value could be compared during ADC execution to
 * check the correctness of the HW unit. Since this API is used for this
 * purpose, the register returned are the ones which doesn't change after init
 * based on conv or channel config.
 *
 * Service ID[hex] - 0x16
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HWUnit ADC Hardware microcontroller peripheral unit ID
 * If this is invalid, then the API will return E_NOT_OK.
 * \param[inout] RegRbPtr Pointer to where to store the readback values.
 * If this pointer is NULL_PTR, then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK - Register read back has been done
 * \retval E_NOT_OK - Register read back failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, ADC_CODE)
Adc_RegisterReadback(Adc_HWUnitType HWUnit, P2VAR(Adc_RegisterReadbackType, AUTOMATIC, ADC_APPL_DATA) RegRbPtr);
#endif /* #if (STD_ON == ADC_REGISTER_READBACK_API) */

#if (ADC_HW_TRIGGER_API == STD_ON)
/** \brief Enables the hardware trigger for the requested ADC Channel group.
 *
 *
 * This function will enable the HW trigger source for the requested ADC channel group.
 *
 * Service ID[hex] - 0x05
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC Channel group.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_EnableHardwareTrigger(VAR(Adc_GroupType, AUTOMATIC) Group);

/** \brief Disables the hardware trigger for the requested ADC Channel group.
 *
 *
 * This function will disable the HW trigger source for the requested ADC channel group.
 *
 * Service ID[hex] - 0x06
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC Channel group.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_DisableHardwareTrigger(VAR(Adc_GroupType, AUTOMATIC) Group);

#endif /*(ADC_HW_TRIGGER_API == STD_ON)*/

#if (STD_ON == ADC_READ_TEMPERATURE_API)
/** \brief This service initializes the efuse parameters for temperature calculation.
 * This is a non-autosar, TI defined API
 * This API is not applicable for AM263x
 *
 *
 * Initializes the Driver to read temperature sensors and do the conversion.
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_InitTemperatureRead(void);

/** \brief This service starts temperature conversion, waits for completion and
 *   reads the temperature sensors group configured as part of Adc_Init
 *   and returns the temperature values.
 *   This is a non-autosar, TI defined API.
 *   This API is not applicable for AM263x
 *
 *
 * Returns the temperature sensor values for three digital temperature sensors.
 *
 * Service ID[hex] - 0x0D
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC Channel group.
 * \param[in] NumAverages Number of samples for averaging the temp value
 * \param[in] TempValuesPtr Temperature values for three available digital sensors are
 * stored in this structure
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE)
Adc_ReadTemperature(Adc_GroupType Group, uint8 NumAverages, Adc_TempSensValueType *TempValuesPtr);

/** \brief This service reads only the results of the temperature sensors group configured as part
 *of Adc_Init, Adc_StartGroupConversion and returns the temperature values. This is a non-autosar,
 *TI defined API. This API is not applicable for AM263x
 *
 *
 * Returns the temperature sensor values for three digital temperature sensors.
 *
 * Service ID[hex] - 0x0E
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC Channel group.
 * \param[in] TempValuesPtr Temperature values for three available digital sensors are
 * stored in this structure
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE)
Adc_ReadTemperatureResult(Adc_GroupType Group, Adc_TempSensValueType *TempValuesPtr);
#endif /* #if (STD_ON == ADC_READ_TEMPERATURE_API) */

#if (STD_ON == ADC_POLLING_MAINFUNCTION_API)
/** \brief This service is used for Polling Group data.
 *
 *
 * This service is used for Polling Group data.
 *
 * Service ID[hex] - 0x15
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC Channel group.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, ADC_CODE) Adc_PollingMainFunction(void);
#endif /* #if (STD_ON == ADC_POLLING_MAINFUNCTION_API) */

/**
 * \brief Returns the HW result register base address.
 *
 * This service returns the Hardware result register address of the first channel of the ADC group.
 * Hardware result registers of consecutive channels are contiguous.
 * If there are multiple (n) channels in a group, read 'n' contiguous values from this base address
 *
 * Service ID[hex] - 0x17
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \return uint32 Result base address
 */
FUNC(uint32, ADC_CODE) Adc_GetReadResultBaseAddress(VAR(Adc_GroupType, AUTOMATIC) Group);

/**
 * \brief Sets the continue to interrupt mode of ADC
 *
 * By enabling this function, Interrupt pulses are generated whenever an EOC pulse is
 * generated irrespective of whether the flag bit is cleared or not.
 *
 * Service ID[hex] - 0x18
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Group Numeric ID of requested ADC channel group.
 * \return Std_ReturnType. E_OK - success, E_NOT_OK - operation failed
 *
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_SetInterruptContinuousMode(VAR(Adc_GroupType, AUTOMATIC) Group);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef ADC_H_ */
