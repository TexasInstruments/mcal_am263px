/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     Cdd_FsiTx.h
 *  \brief    This file contains interface header for FsiTx Complex Device Driver
 */
/************************************************************************************************/
/*  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_FsiTx.h
 *      Project:  Complex Device Driver
 *       Module:  Cdd_FsiTx
 *  Description:  This module implements a driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                With this driver you can:
 *                - Configure the FsiTx config registers
 *                - Initialize the FsiTx configuration
 *                - Copy Data from Source Buffer to Internal Transmit Buffer
 *                - Transmit data over the FsiTx
 **************************************************************************************************/

/* Design:  SITARAMCU_MCAL-___, SITARAMCU_MCAL-___, SITARAMCU_MCAL-___ */
#ifndef CDD_FSI_TX_H_
#define CDD_FSI_TX_H_

/**
 * \defgroup CDD_FSITX FsiTx API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sys_common.h"
#include "hw_types.h"
#include "Std_Types.h"
#include "Cdd_FsiTx_Priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name CDD FsiTx Driver ID Info
 *  @{
 */
/** \brief CDD Module ID */
#define CDD_FSI_TX_MODULE_ID ((uint16)255U)
/** \brief Texas Instruments Vendor ID */
#define CDD_FSI_TX_VENDOR_ID ((uint16)44U)
/** \brief Texas Instruments Vendor ID */
#define CDD_FSI_TX_INSTANCE_ID ((uint8)0U)
/**   @} */

/**
 *  \name CDD FsiTx Driver Module Version Info
 *
 *  Defines for CDD Driver version used for compatibility checks
 * @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_FSI_TX_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define CDD_FSI_TX_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation patch Version */
#define CDD_FSI_TX_SW_PATCH_VERSION (0U)
/**   @} */
/**
 *  \name CDD FsiTx Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD Driver AUTOSAR version used for compatibility checks
 * @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD Driver */
#define CDD_FSI_TX_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor version specification implemented by CDD Driver */
#define CDD_FSI_TX_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by CDD Driver */
#define CDD_FSI_TX_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/**
 *  \name CDD FsiTx API Service ID
 * @{
 */
/* Requirements:  SITARAMCU_MCAL-___ */
/* Design: SITARAMCU_MCAL-___ */
/** \brief API Service ID for initialization */
#define CDD_FSI_TX_INIT_SID 0x01U
/** \brief API Service ID for get version info */
#define CDD_FSI_TX_GETVERSIONINFO_SID 0x02U
/** \brief API Service ID for Ping API */
#define CDD_FSI_TX_PING_SID 0x03U
/** \brief API Service ID for Buffer Load API */
#define CDD_FSI_TX_BUFFER_LOAD_SID 0x04U
/** \brief API Service ID for Transmit API */
#define CDD_FSI_TX_TRANSMIT_SID 0x05U
/** \brief API Service ID for Tx mainfunction API */
#define CDD_FSI_TX_MAIN_FUNCTION_SID 0x06U
/** \brief API Service ID deinit API */
#define CDD_FSI_TX_DEINIT_SID 0x07U
/** \brief API Service ID for reset driver API */
#define CDD_FSI_TX_RESET_SID 0x08U
/**   @} */
/**
 *  \name CDD FsiTx Error Codes
 * @{
 */
/** \brief Error code indicating the FsiTx is uninitialized */
#define CDD_FSI_TX_E_UNINIT 0x01U
/** \brief Error code indicating an invalid event */
#define CDD_FSI_TX_E_INVALID_EVENT 0x02U
/** \brief Error code indicating invalid parameter pointer */
#define CDD_FSI_TX_E_PARAM_POINTER 0x03U
/** \brief Error code indicating FsiTx is already initialized */
#define CDD_FSI_TX_E_ALREADY_INITIALIZED 0x04U
/** \brief Error code indicating Service called with wrong param */
#define CDD_FSI_TX_E_PARAM_VALUE 0x05U
/** \brief Error code indicating Service called with invalid length */
#define CDD_FSI_TX_E_PARAM_LENGTH 0x06U
/** \brief Error code indicating invalid FsiTx channel */
#define CDD_FSI_TX_E_INVALID_HWUNIT 0x07U
/** \brief Error code indicating invalid FsiTx configuration */
#define CDD_FSI_TX_E_INVALID_CONFIG 0x08U
/** \brief Error code indicating  FsiTx is busy */
#define CDD_FSI_TX_E_BUSY 0x09U
/**   @} */

/** \brief Minimum value of delay */
#define CDD_FSI_TX_MIN_OPEN_DELAY (0x00U)
/** \brief Maximum value of delay */
#define CDD_FSI_TX_MAX_OPEN_DELAY (0x3FFFFU)

/**
 *  \name CDD_FSI_TX Driver ISR category level
 *  Defines for CDD_FSI_TX Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_FSI_TX_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CDD_FSI_TX_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CDD_FSI_TX_ISR_CAT2 (0x02U)
/**   @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Service for CDD_FSI_TX initialization.
 *
 *
 * Initializes the CDD_FSI_TX hardware units and driver
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

FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_Init(P2CONST(Cdd_FsiTx_ConfigType, AUTOMATIC, CDD_FsiTx_CFG) ConfigurationPtr);

#if (STD_ON == CDD_FSI_TX_DEINIT_API)
/** \brief This service de-initializes all CDD_FSI_TX HW Units
 *
 *
 * Returns all CDD_FSI_TX HW Units to a state comparable to
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
FUNC(void, CDD_FSITX_CODE) Cdd_FsiTx_DeInit(void);
#endif /* #if (STD_ON == CDD_FSI_TX_DEINIT_API) */

#if (STD_ON == CDD_FSI_TX_PING_API)
/** \brief This service transmits the Ping frame to the receiver for
 * establishing communication link.
 *
 *
 * The Ping frame with Tag 0 is transmitted initially. If the Tx is on
 * the receiver hardware side, then once Tag 0 is received and gets acknowledged,
 * Tx sends Tag1 Ping frame.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HwUnitId - Hardware Instance
 * \return Std_ReturnType
 * \retval E_OK - Ping frame transmitted successfully
 * \retval E_NOT_OK - Ping frame didn't transmit successfully
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE) Cdd_FsiTx_Ping(Cdd_FsiTx_HWUnitType HwUnitId);
#endif /* #if (STD_ON == CDD_FSI_TX_PING_API) */

#if (STD_ON == CDD_FSI_TX_BUFFER_LOAD_API)
/** \brief Copy the data to be transmitted through Tx to the Tx buffer.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HwUnitId - The Tx HwUnit Instance which transmits data
 * \param[in] SrcBufferPtr - Source Buffer from data to be copied.
 * \param[in] Cdd_FsiTx_userData - User Data sent from application for each frame.
 * \param[in] TxDataLength - Number of words to be copied for transmission.
 * \return Std_ReturnType
 * \retval Returns the bufferload status
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
Cdd_FsiTx_BufferLoad(Cdd_FsiTx_HWUnitType HwUnitId,
                     P2VAR(Cdd_FsiTx_DataBufferType, AUTOMATIC, CDD_FSI_TX_APPL_DATA) SrcBufferPtr,
                     Cdd_FsiTx_DataType Cdd_FsiTx_userData, Cdd_FsiTx_BufferLengthType TxDataLength);
#endif /* #if (STD_ON == CDD_FSI_TX_BUFFER_LOAD_API) */

#if (STD_ON == CDD_FSI_TX_GET_VERSION_INFO)
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
FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_FSI_TX_APPL_DATA) VersionInfoPtr);
#endif /* #if (STD_ON == CDD_FSI_TX_VERSION_INFO_API) */

#if (STD_ON == CDD_FSI_TX_TRANSMIT_API)
/** \brief This service returns the transmit status of this module.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HwUnitId - Hardware Instance which transmits data
 * \param[in] userData - Data to be transmitted
 * \param[in] TxDataLength - Number of data to be transmitted
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
Cdd_FsiTx_Transmit(Cdd_FsiTx_HWUnitType HwUnitId, Cdd_FsiTx_UserDataType userData,
                   Cdd_FsiTx_DataLengthType TxDataLength);
#endif /* #if (STD_ON == CDD_FSI_TX_TRANSMIT_API) */

/** \brief This service returns the current state information of the driver.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \return Cdd_FsiTx_StatusType
 * \retval CDD_FSI_TX_UNINIT - Tx module has not initialized yet
 * \retval CDD_FSI_TX_INIT - Tx module has initialized
 * \retval CDD_FSI_TX_IDLE - Transmission through the Tx channel hasn't started
 * \retval CDD_FSI_TX_BUSY - Transmission has been started and is still going on
 *
 *****************************************************************************/
FUNC(Cdd_FsiTx_StatusType, CDD_FSITX_CODE) CddFsiTx_GetStatus(void);

#if (STD_ON == CDD_FSI_TX_MAIN_FUNCTION_API)
/** \brief When transmission completes, this service notifies the Application.
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
FUNC(void, CDD_FSITX_CODE) Cdd_FsiTx_MainFunction(void);
#endif /* #if (STD_ON == CDD_FSI_TX_MAIN_FUNCTION_API) */

#if (STD_ON == CDD_FSI_TX_RESET_API)
/** \brief his service reset the TX driver.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HwUnitId
 * \param[in] ResetModule
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_Reset(Cdd_FsiTx_HWUnitType HwUnitId, VAR(Cdd_FsiTx_ResetSubModuleType, AUTOMATIC) ResetModule);
#endif /* #if (STD_ON == CDD_FSI_TX_RESET_API) */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef CDD_FSI_TX_H_ */
