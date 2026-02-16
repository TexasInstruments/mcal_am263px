/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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

/**
 *  \file     Cdd_FsiRx.h
 *
 *  \brief    This file contains interface header for FsiRx Complex Device Driver
 *
 */
/*  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_FsiRx.h
 *      Project:  Complex Device Driver
 *       Module:  Cdd_FsiRx
 *
 *  Description:  This module implements a driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                With this driver you can:
 *                - Configure the FsiRx config registers
 *                - Initialize the FsiRx configuration
 *                - Receivedata over the FsiRx
 **************************************************************************************************/
#ifndef CDD_FSI_RX_H_
#define CDD_FSI_RX_H_

/**
 * \defgroup CDD_FSIRX FsiRx API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sys_common.h"
#define CDD_FSIRX_START_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CDD_FSIRX_STOP_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"
#include "Std_Types.h"
#include "Cdd_FsiRx_Priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name CDD FsiRx Driver ID Info
 *  @{
 */
/** \brief CDD Module ID */
#define CDD_FSI_RX_MODULE_ID ((uint16)255U)
/** \brief Texas Instruments Vendor ID */
#define CDD_FSI_RX_VENDOR_ID ((uint16)44U)
/** \brief Texas Instruments Vendor ID */
#define CDD_FSI_RX_INSTANCE_ID ((uint8)0U)
/**   @} */

/**
 *  \name CDD FsiRx Driver Module Version Info
 *
 *  Defines for CDD Driver version used for compatibility checks
 * @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_FSI_RX_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define CDD_FSI_RX_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation patch Version */
#define CDD_FSI_RX_SW_PATCH_VERSION (2U)
/**   @} */
/**
 *  \name CDD FsiRx Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD Driver AUTOSAR version used for compatibility checks
 * @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD Driver */
#define CDD_FSI_RX_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor version specification implemented by CDD Driver */
#define CDD_FSI_RX_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by CDD Driver */
#define CDD_FSI_RX_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/**
 *  \name CDD FsiRx API Service ID
 * @{
 */

/** \brief API Service ID for initialization */
#define CDD_FSI_RX_INIT_SID 0x01U
/** \brief API Service ID for get version info */
#define CDD_FSI_RX_GETVERSIONINFO_SID 0x02U
/** \brief API Service ID for main function API */
#define CDD_FSI_RX_MAIN_FUNCTION_SID 0x03U
/** \brief API Service ID deinit API */
#define CDD_FSI_RX_DEINIT_SID 0x04U
/** \brief API Service ID for get status API */
#define CDD_FSI_RX_GET_STATUS_SID 0x05U
/** \brief API Service ID for reset driver API */
#define CDD_FSI_RX_RESET_SID 0x06U
/** \brief API Service ID for Buffer Setup API */
#define CDD_FSI_RX_SETUP_BUFFER_SID 0x07U
/** \brief API Service ID for Cdd_FsiRx_DmaDataReceive API */
#define CDD_FSI_RX_DMA_DATA_RECEIVE_SID 0x08U
/**   @} */
/**
 *  \name CDD FsiRx Error Codes
 * @{
 */

/** \brief Error code indicating the FsiRx is uninitialized */
#define CDD_FSI_RX_E_UNINIT 0x01U

/** \brief Error code indicating an invalid event */
#define CDD_FSI_RX_E_INVALID_EVENT 0x02U

/** \brief Error code indicating invalid parameter pointer */
#define CDD_FSI_RX_E_PARAM_POINTER 0x03U

/** \brief Error code indicating FsiRx is already initialized */
#define CDD_FSI_RX_E_ALREADY_INITIALIZED 0x04U

/** \brief Error code indicating Service called with wrong param */
#define CDD_FSI_RX_E_PARAM_VALUE 0x05U

/** \brief Error code indicating Service called with invalid length */
#define CDD_FSI_RX_E_PARAM_LENGTH 0x06U
/** \brief Error code indicating invalid FsiRx channel */
#define CDD_FSI_RX_E_INVALID_CHANNEL 0x07U
/** \brief Error code indicating invalid FsiRx configuration */
#define CDD_FSI_RX_E_INVALID_CONFIG 0x08U
/** \brief Error code indicating  FsiRx is busy */
#define CDD_FSI_RX_E_BUSY 0x09U
/**   @} */
/**
 *  \name CDD_FSI_RX HW channels
 *  Number of actual HW channels - in terms of CDD_FSI_RX HW, this represents
 *  the actual channel input to the CDD_FSI_RX module.
 *  Note: This is a fixed value as per the CDD_FSI_RX module and can't be changed.
 * @{
 */
/** \brief Minimum value of HW channel ID */
#define CDD_FSI_RX_MIN_HW_UNIT_ID (0U)
/** \brief Maximum value of HW channel ID */
#define CDD_FSI_RX_MAX_HW_CHANNEL_ID (CDD_FSI_RX_MAX__HW_UNIT - 1U)

/** \brief Minimum value of delay */
#define CDD_FSI_RX_MIN_OPEN_DELAY (0x00U)
/** \brief Maximum value of delay */
#define CDD_FSI_RX_MAX_OPEN_DELAY (0x3FFFFU)
/** \brief Maximum DMA channels */
#define CDD_FSI_RX_MAX_DMA_CHANNELS ((uint8)63U)
/**   @} */
/**
 *  \name CDD_FSI_RX Driver ISR category level
 *
 *  Defines for CDD_FSI_RX Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_FSI_RX_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CDD_FSI_RX_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CDD_FSI_RX_ISR_CAT2 (0x02U)
/**   @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Service for CDD_FSI_RX initialization.
 *
 *
 * Initializes the CDD_FSI_RX hardware units and driver
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ConfigurationPtr Pointer to configuration set in Variant PB
 * (Variant PC requires a NULL_PTR).
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_Init(P2CONST(Cdd_FsiRx_ConfigType, AUTOMATIC, CDD_FsiRx_CFG) ConfigurationPtr);

#if (STD_ON == CDD_FSI_RX_DEINIT_API)
/** \brief This service de-initializes all CDD_FSI_RX HW Units
 *
 *
 * Returns all CDD_FSI_RX HW Units to a state comparable to
 * their power on reset state
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_DeInit(void);
#endif /* #if (STD_ON == CDD_FSI_RX_DEINIT_API) */

#if (STD_ON == CDD_FSI_RX_GET_VERSION_INFO)
/** \brief This service returns the version information of this module.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[out] versioninfo - Pointer to where to store the version
 * information of this module
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_FSI_RX_APPL_DATA) VersionInfoPtr);
#endif /* #if (STD_ON == CDD_FSI_RX_VERSION_INFO_API) */

#if (STD_ON == CDD_FSI_RX_MAIN_FUNCTION_API)
/** \brief The main Function used for Polling the data reception in Polling Method.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_MainFunction(void);

#endif /* #if (STD_ON == CDD_FSI_RX_MAIN_FUNCTION_API) */
       /** \brief This service gets the status of FsiRx Driver
        *
        *
        * Returns the driver status
        *
        * Sync/Async - Synchronous
        *
        * Reentrancy - Reentrant
        *
        * \return CddFsiRx_StatusType
        * \retval CDD_FSI_RX_INIT - Not Initialized
        * \retval CDD_FSI_RX_IDLE - Reception has not started
        * \retval CDD_FSI_RX_BUSY - Reception has been started and still going on
        * \retval CDD_FSI_RX_COMPLETED - Reception completed
        *
        *****************************************************************************/
FUNC(CddFsiRx_StatusType, CDD_FSIRX_CODE)
CddFsiRx_GetStatus(void);

#if (STD_ON == CDD_FSI_RX_RESET_API)
/** \brief This service reset the Rx module
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HwUnitId - HwUnit Instance
 * \param[in] ResetModule
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_Reset(Cdd_FsiRx_HWUnitType HwUnitId, VAR(Cdd_FsiRx_ResetSubModuleType, AUTOMATIC) ResetModule);
#endif /* #if (STD_ON == CDD_FSI_RX_RESET_API) */
       /** \brief This service setup the Buffer Adress to which data has to be received.
        *
        *
        * Sync/Async - Synchronous
        *
        * Reentrancy - Reentrant
        *
        * \param[in] HwUnitId - HwUnit Instance which receives data
        * \param[in] RxDataLength - Number of words received in a frame
        * \param[out] DataBufferPtr - Pointer to the Application Buffer to which
        * data to be copied
        * \return None
        * \retval None
        *
        *****************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_setUpBuffer(Cdd_FsiRx_HWUnitType HwUnitId,
                      P2VAR(Cdd_FsiRx_DataBufferType, AUTOMATIC, CDD_FSI_RX_APPL_DATA) DataBufferPtr,
                      CddFsiRx_DataLengthType RxDataLength);

/** \brief The Cdd_FsiRx_DmaDataReceive copies data from Rx internal
 * buffer to the application buffer.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HwUnitId - HwUnit Instance which copies data
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_DmaDataReceive(Cdd_FsiRx_HWUnitType HwUnitId);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef CDD_FSI_RX_H_ */
