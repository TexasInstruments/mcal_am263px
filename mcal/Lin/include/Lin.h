/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LIN_H
#define LIN_H

/**
 *  \defgroup LIN Lin
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/
#include "ComStack_Types.h"
#include "EcuM_Cbk.h"
#include "Lin_GeneralTypes.h"
#include "Lin_Cfg.h"
/*********************************************************************************************************************
 * Other Header Files
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Version Check (if required)
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Exported Preprocessor #define Constants
 *********************************************************************************************************************/
//*****************************************************************************
//
// Defines for LIN Driver version used for compatibility checks.
//
//*****************************************************************************

/* Common Design ID's */
/*
 * Design: MCAL-15893
 */

/**
 *  \name LIN Driver Module SW Version Info
 *
 *  Defines for LIN Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define LIN_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define LIN_SW_MINOR_VERSION (3U)
/** \brief Driver Implementation Patch Version */
#define LIN_SW_PATCH_VERSION (1U)
/** @} */
//*****************************************************************************
//
// Defines for LIN Driver AUTOSAR version used for compatibility checks.
//
//*****************************************************************************

/**
 *  \name LIN Driver Module AUTOSAR Version Info
 *
 *  Defines for LIN Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by LIN Driver */
#define LIN_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor version specification implemented by LIN Driver */
#define LIN_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by LIN Driver */
#define LIN_AR_RELEASE_REVISION_VERSION (1U)

/** @} */
//*****************************************************************************
//
// LIN Driver ID Info.
//
//*****************************************************************************

/**
 *  \name LIN Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define LIN_VENDOR_ID ((uint16)44U)
/** \brief LIN Driver Module ID */
#define LIN_MODULE_ID ((uint16)82U)
/** \brief LIN Instance ID */
#define LIN_INSTANCE_ID ((uint8)0U)
/** @} */

/**
 *  \name LIN Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief Lin_Init() */
#define LIN_SID_INIT ((uint8)0x00U)
/** \brief Lin_GetVersionInfo() */
#define LIN_SID_GET_VERSION_INFO ((uint8)0x01U)
/** \brief Lin_SendFrame() */
#define LIN_SID_SEND_FRAME ((uint8)0x04U)
/** \brief Lin_GoToSleep() */
#define LIN_SID_GOTO_SLEEP ((uint8)0x06U)
/** \brief Lin_Wakeup() */
#define LIN_SID_WAKEUP ((uint8)0x07U)
/** \brief Lin_GetStatus() */
#define LIN_SID_GET_STATUS ((uint8)0x08U)
/** \brief Lin_GoToSleepInternal() */
#define LIN_SID_GOTO_SLEEP_INTERNAL ((uint8)0x09U)
/** \brief Lin_CheckWakeup() */
#define LIN_SID_CHECK_WAKEUP ((uint8)0x0AU)
/** \brief Lin_WakeupInternal() */
#define LIN_SID_WAKEUP_INTERNAL ((uint8)0x0BU)
/** \brief Lin_RegisterReadback() */
#define LIN_SID_REGISTER_READBACK ((uint8)0x0CU)
/** \brief Lin_Deinit() */
#define LIN_SID_DEINIT ((uint8)0x0DU)
/** @} */
//*****************************************************************************
//
// LIN Error Codes returned by Driver functions.
//
//*****************************************************************************
/**
 *  \name LIN Error Codes
 *
 *  Error Codes returned by MCU Driver
 *  @{
 */
#ifndef LIN_E_UNINIT
/** \brief API service used without module initialization */
#define LIN_E_UNINIT ((uint8)0x00U)
#endif
#ifndef LIN_E_INVALID_CHANNEL
/** \brief API service used with an invalid or inactive channel parameter */
#define LIN_E_INVALID_CHANNEL ((uint8)0x02U)
#endif
#ifndef LIN_E_INVALID_POINTER
/** \brief API service called with invalid configuration pointer */
#define LIN_E_INVALID_POINTER ((uint8)0x03U)
#endif
#ifndef LIN_E_STATE_TRANSITION
/** \brief Invalid state transition for the current state */
#define LIN_E_STATE_TRANSITION ((uint8)0x04U)
#endif
#ifndef LIN_E_PARAM_POINTER
/** \brief API service called with a NULL pointer */
#define LIN_E_PARAM_POINTER ((uint8)0x05U)
#endif
/** @} */
/*********************************************************************************************************************
 * Exported Preprocessor #define Macros
 *********************************************************************************************************************/
/**
 *  \name LIN Driver ISR category level
 *
 *  Defines for LIN Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define LIN_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define LIN_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define LIN_ISR_CAT2 (0x02U)
/** @} */
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*********************************************************************************************************************
 * Exported Type Declarations
 *********************************************************************************************************************/
/** \brief Structure defining the channel type  */
typedef struct Lin_ChannelTag
{
    /** \brief Lin Controller Config */
    Lin_ControllerType     linControllerConfig;
    /** \brief Lin Baud Rate Config */
    Lin_BaudRateConfigType linBaudConfig;
    /** \brief Wakeup source to be set */
    EcuM_WakeupSourceType  linWakeupSource;
    /** \brief LIN channel wakeup support */
    boolean                linChannelWakeupSupport;
} Lin_ChannelType;

/*
 * Design: MCAL-15894
 */
/** \brief Structure defining the config type  */
typedef struct Lin_ConfigTag
{
    /** \brief LIN channel configuration */
    Lin_ChannelType linChannelCfg[LIN_MAX_CHANNEL];
} Lin_ConfigType;

/*********************************************************************************************************************
 * Exported Object Declarations
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  Exported Function Prototypes
 *********************************************************************************************************************/
#if (STD_ON == LIN_GET_VERSION_INFO_API)

/** \brief This function returns the version information of this module.
 *
 * Service ID[hex]   : 0x01
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[out] versioninfo - Pointer to where to store the version information of this module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, LIN_CODE) Lin_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

/** \brief This function initializes the LIN module.
 *
 * Service ID[hex]   : 0x00
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Config - Pointer to LIN driver configuration set.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, LIN_CODE) Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) Config);

/** \brief This function checks if a wakeup has occurred on the addressed LIN channel.
 *
 * Service ID[hex]   : 0x0a
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \return Std_ReturnType
 * \retval E_OK: No error has occurred during execution of the API
 * \retval E_NOT_OK: An error has occurred during execution of the API
 *
 *****************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_CheckWakeup(uint8 Channel);

/** \brief Sends a LIN header and a LIN response, if necessary. The direction of the frame response
 *          (master response, slave response, slave-to-slave communication) is provided by the
 *PduInfoPtr.
 *
 * Service ID[hex]   : 0x04
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \param[in] PduInfoPtr - Pointer to PDU containing the PID, checksum model, response type, Dl and
 *SDU data pointer.
 * \return Std_ReturnType
 * \retval E_OK: Send command has been accepted.
 * \retval E_NOT_OK: Send command has not been accepted, development or production error occurred.
 *
 *****************************************************************************/
FUNC(Std_ReturnType, LIN_CODE)
Lin_SendFrame(uint8 Channel, P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) PduInfoPtr);

/** \brief The service instructs the driver to transmit a go-to-sleep-command on the addressed LIN
 *channel.
 *
 * Service ID[hex]   : 0x06
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \return Std_ReturnType
 * \retval E_OK: Sleep command has been accepted
 * \retval E_NOT_OK: Sleep command has not been accepted, development or production error occurred
 *
 *****************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleep(uint8 Channel);

/** \brief Sets the channel state to LIN_CH_SLEEP, enables the wake-up detection and optionally sets
 *the LIN hardware unit to reduced power operation mode.
 *
 * Service ID[hex]   : 0x09
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \return Std_ReturnType
 * \retval E_OK: Command has been accepted
 * \retval E_NOT_OK: Command has not been accepted, development or production error occurred
 *
 *****************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_GoToSleepInternal(uint8 Channel);

/** \brief Generates a wake up pulse and sets the channel state to LIN_CH_OPERATIONAL.
 *
 * Service ID[hex]   : 0x07
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \return Std_ReturnType
 * \retval E_OK: Wake-up request has been accepted
 * \retval E_NOT_OK: Wake-up request has not been accepted, development or production error occurred
 *
 *****************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_Wakeup(uint8 Channel);

/** \brief Generates a wake up pulse and sets the channel state to LIN_CH_OPERATIONAL without
 *generating a wake up pulse.
 *
 * Service ID[hex]   : 0x0b
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \return Std_ReturnType
 * \retval E_OK: Wake-up request has been accepted
 * \retval E_NOT_OK: Wake-up request has not been accepted, development or production error occurred
 *
 *****************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupInternal(uint8 Channel);

/** \brief Gets the status of the LIN driver.
 *
 * Service ID[hex]   : 0x08
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \param[out] Lin_SduPtr - Pointer to point to a shadow buffer or memory mapped LIN Hardware
 *receive buffer where the current SDU is stored.
 * \return Lin_StatusType
 * \retval LIN_NOT_OK: Development or production error occurred
 * \retval LIN_TX_OK: Successful transmission
 * \retval LIN_TX_BUSY: Ongoing transmission (Header or Response)
 * \retval LIN_TX_HEADER_ERROR: Erroneous header transmission such as: Mismatch between sent and
 *read back data, Identifier parity error or Physical bus error
 * \retval LIN_TX_ERROR: Erroneous response transmission such as: Mismatch between sent and read
 *back data, Physical bus error
 * \retval LIN_RX_OK: Reception of correct response
 * \retval LIN_RX_BUSY: Ongoing reception: at least one response byte has been received, but the
 *checksum byte has not been received
 * \retval LIN_RX_ERROR: Erroneous response reception such as: Framing error, Overrun error,
 *Checksum error or Short response
 * \retval LIN_RX_NO_RESPONSE: No response byte has been received so far
 * \retval LIN_OPERATIONAL: Normal operation; the related LIN channel is woken up from the
 *LIN_CH_SLEEP and no data has been sent.
 * \retval LIN_CH_SLEEP: Sleep state operation; in this state wake-up detection from slave nodes is
 *enabled.
 *
 *****************************************************************************/
FUNC(Lin_StatusType, LIN_CODE)
Lin_GetStatus(uint8 Channel, P2VAR(uint8 *, AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr);

#if (STD_ON == LIN_REGISTER_READBACK_API)

/** \brief This function reads the important registers of the hardware unit and returns the value in
 *the structure. This API is used to check the status of critical registers which do not change
 *during program execution.
 *
 * Service ID[hex]   : 0x0C
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] Channel - LIN channel to be addressed.
 * \param[in,out] RegRbPtr - Pointer to where to store the readback values. If this pointer is NULL,
 *then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK: Register read back has been done successfully
 * \retval E_NOT_OK: Register read back failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, LIN_CODE)
Lin_RegisterReadback(uint8 Channel, P2VAR(Lin_RegisterReadbackType, AUTOMATIC, LIN_APPL_DATA) RegRbPtr);
#endif

/** \brief This function de-intializes the LIN hardware unit .
 *
 * Service ID[hex]   : 0x0D
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non - Reentrant
 *
 * \return void
 *
 *****************************************************************************/
FUNC(void, LIN_CODE) Lin_Deinit(void);
/*********************************************************************************************************************
 *  Exported Inline Function Definitions and Function-Like Macros
 *********************************************************************************************************************/

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* LIN_H */
/*********************************************************************************************************************
 *  End of File: Lin.h
 *********************************************************************************************************************/
