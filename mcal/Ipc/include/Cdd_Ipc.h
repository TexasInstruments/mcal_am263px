/* ======================================================================
 *   Copyright (c) 2023-2024 Texas Instruments Incorporated
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
 *  \file     Cdd_Ipc.h
 *
 *  \brief    This file contains interface header for IPC Complex Device Driver
 *
 */

/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_Ipc.h
 *      Project:  Complex Device Driver
 *       Module:  CddIpcDriver
 *
 *  Description:  This module implements a driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                With this driver you can:
 *                - Configure the IPC config registers
 *                - Initialize the IPC configuration
 *                - Read and write data over the IPC
 **************************************************************************************************/

#ifndef CDD_IPC_H_
#define CDD_IPC_H_

/**
 * \defgroup CDD_IPC IPC API GUIDE Header file
 * @{
 */

/**  \brief Selecting IPC Version based on target platform (AM263X corresponding to V0) */
#define IP_VERSION_IPC_V0

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "ipc_notify_lld_utils.h"
#include "ipc_notify_v1_lld.h"
#include "ipc_notify_v1_cfg_lld.h"
#include "ipc_rpmsg_lld.h"
#include "SchM_Cdd_Ipc.h"
#include "Cdd_Ipc_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief IPC Lock */
#define CDD_IPC_LOCK 1U
/** \brief IPC Unlock */
#define CDD_IPC_UNLOCK 0U

/** \brief Mutex Arm Lock */
#define CDD_IPC_MUTEX_ARM_LOCKED 1U
/** \brief Mutex Arm Unlock */
#define CDD_IPC_MUTEX_ARM_UNLOCKED 0U

/**
 *  \name CDD IPC Driver ID Info
 * @{
 */

/** \brief CDD Module ID */
#define CDD_IPC_MODULE_ID 255U
/** \brief Texas Instruments Vendor ID */
#define CDD_IPC_VENDOR_ID 44U
/** \brief Texas Instruments Vendor ID */
#define CDD_IPC_INSTANCE_ID 0U
/**   @} */

/**
 *  \name CDD IPC Driver Module Version Info
 *
 *  Defines for CDD Driver version used for compatibility checks
 * @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_IPC_SW_MAJOR_VERSION 10U
/** \brief Driver Implementation Minor Version */
#define CDD_IPC_SW_MINOR_VERSION 1U
/** \brief Driver Implementation patch Version */
#define CDD_IPC_SW_PATCH_VERSION 0U
/**   @} */
/**
 *  \name CDD IPC Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD Driver AUTOSAR version used for compatibility checks
 * @{
 */

/** \brief AUTOSAR Major version specification implemented by CDD Driver */
#define CDD_IPC_AR_RELEASE_MAJOR_VERSION 4U
/** \brief AUTOSAR Minor version specification implemented by CDD Driver */
#define CDD_IPC_AR_RELEASE_MINOR_VERSION 3U
/** \brief AUTOSAR Patch version specification implemented by CDD Driver */
#define CDD_IPC_AR_RELEASE_REVISION_VERSION 1U
/**   @} */
/**
 *  \name CDD Driver ISR category level
 *  Requirements: SITARAMCU_MCAL-___
 *  Defines for CDD IPC Driver ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_IPC_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CDD_IPC_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CDD_IPC_ISR_CAT2 (0x02U)
/**   @} */

/**
 *  \name CDD IPC API Service ID
 * @{
 */

/** \brief API Service ID for initialization */
#define CDD_IPC_INIT_SERVICE_ID 0x01U
/** \brief API Service ID for get version info */
#define CDD_IPC_GETVERSIONINFO_SERVICE_ID 0x02U
/** \brief API Service ID for read API */
#define CDD_IPC_READDATA_SERVICE_ID 0x03U
/** \brief API Service ID for write API */
#define CDD_IPC_WRITEDATA_SERVICE_ID 0x04U
/** \brief API Service ID for error API */
#define CDD_IPC_ERROR_SERVICE_ID 0x05U
/** \brief API Service ID for read cancel API */
#define CDD_IPC_RPMSG_READ_SERVICE_ID 0x06U
/** \brief API Service ID for write cancel API */
#define CDD_IPC_RPMSG_WRITE_SERVICE_ID 0x07U
/** \brief API Service ID for get remaining bytes API */
#define CDD_IPC_NOTIFY_REGISTER_CLIENT_SERVICE_ID 0x08U
/** \brief API Service ID for get remaining read bytes API */
#define CDD_IPC_CONSTRUCT_SERVICE_ID 0x09U
/** \brief API Service ID for read notification han dler */
#define CDD_IPC_READNOTIF_SERVICE_ID 0x0AU
/** \brief API Service ID for write notification handler */
#define CDD_IPC_WRITENOTIF_SERVICE_ID 0x0BU
/** \brief API Service ID for error notification handler */
#define CDD_IPC_ERRORNOTIF_SERVICE_ID 0x0CU
/** \brief API Service ID for deinitialization */
#define CDD_IPC_DEINIT_SERVICE_ID 0x0DU
/** \brief API Service ID for ISR */
#define CDD_IPC_INTERNAL_ISR_ID 0x0EU
/** \brief API Service ID for get remaining bytes API */
#define CDD_IPC_NOTIFY_UNREGISTER_CLIENT_SERVICE_ID 0x0FU
/** \brief API Service ID for Destructing the RpMsg Endpoint Obj */
#define CDD_IPC_DESTRUCT_SERVICE_ID 0x10U
/** \brief API Service ID for Destructing the RpMsg Endpoint Obj */
#define CDD_IPC_NOTIFY_SYNCALL_SERVICE_ID 0x11U
/**   @} */

/**
 *  \name CDD IPC Error Codes
 * @{
 */

/** \brief Error code indicating the IPC is uninitialized */
#define CDD_IPC_E_UNINIT 0x01U

/** \brief Error code indicating register client failed event */
#define CDD_IPC_E_REGISTER_CLIENT_FAILED 0x02U

/** \brief Error code indicating IPC reading mode ongoing */
#define CDD_IPC_E_INIT_FAILED 0x03U

/** \brief Error code indicating IPC writing mode ongoing */
#define CDD_IPC_E_DEINIT_FAILED 0x04U

/** \brief Error code indicating invalid parameter */
#define CDD_IPC_E_PARAM_POINTER 0x05U

/** \brief Error code indicating IPC already initialized */
#define CDD_IPC_E_ALREADY_INITIALIZED 0x06U

/** \brief Error code indicating Service called with wrong param */
#define CDD_IPC_E_PARAM_VALUE 0x07U

/** \brief Error code indicating Service called with invalid length */
#define CDD_IPC_E_PARAM_LENGTH 0x08U

/** \brief Error code indicating invalid IPC configuration */
#define CDD_IPC_E_INVALID_CHANNEL 0x09U

/** \brief Error code indicating invalid IPC configuration */
#define CDD_IPC_E_INVALID_CONFIG 0x0AU

/** \brief Error code indicating IPC Write Failed configuration */
#define CDD_IPC_E_WRITE_FAILED 0x0BU

/** \brief Error code indicating unregister client failed event */
#define CDD_IPC_E_UNREGISTER_CLIENT_FAILED 0x0CU

/** \brief Error code indicating construct failed event */
#define CDD_IPC_E_CONSTRUCT_FAILED 0x0DU

/** \brief Error code indicating RpMsg Write failed event */
#define CDD_IPC_E_RPMSG_WRITE_FAILED 0x0EU

/** \brief Error code indicating Rpmsg read failed event */
#define CDD_IPC_E_RPMSG_READ_FAILED 0x0FU

/** \brief Error code indicating destruct failed event */
#define CDD_IPC_E_DESTRUCT_FAILED 0x10U
/**   @} */
uint32 Cdd_Ipc_Mutex_resourceTryLock(uint32* lock);
void   Cdd_Ipc_Mutex_resourceUnlock(uint32* lock);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void Cdd_Ipc_notify_MsgHandler(void* ipcNotifyHandle, uint32 Cdd_Ipc_remoteCoreId, uint16 Cdd_Ipc_remoteClientId,
                               uint32 Cdd_Ipc_msgValue, uint32 timeout, sint32 crcStatus, void* args);

/** \brief Service for getting CDD version.
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[out] VersionInfoPtr - Pointer to where to store the version information
 * \return None
 * \retval None
 *
 *****************************************************************************/

#if (STD_ON == CDD_IPC_VERSION_INFO_API)
FUNC(void, CDD_CODE)
Cdd_Ipc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_Ipc_APPL_DATA) VersionInfoPtr);
#endif

/** \brief Service for CDD IPC Initialization
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ConfigPtr - Pointer to configuration set
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_IPC_CODE) Cdd_Ipc_Init(P2CONST(Cdd_IpcConfigType, AUTOMATIC, CDD_IPC_CFG) ConfigPtr);

/** \brief Service for deinitializing CDD IPC
 *
 *
 * Service for deinitializing the CDD IPC and change driver state to uninitialized
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] ConfigPtr - Pointer to configuration set
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == CDD_IPC_DEINIT_API)
FUNC(void, CDD_IPC_CODE)
Cdd_Ipc_DeInit(P2CONST(Cdd_IpcConfigType, AUTOMATIC, CDD_IPC_CFG) ConfigPtr);
#endif

/** \brief Service to register a client for IPC
 *
 *
 * Service to register client at a specified client ID.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Cdd_Ipc_localClientId - Local core client ID
 * \param[in] Cdd_Ipc_notify_msgHandler - Pointer to the function that
 * handles the Ipc notify message arrives on that above client ID
 * \return Std_ReturnType
 * \retval E_OK
 * \retval E_NOT_OK
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_Notify_RegisterClient(uint32 Cdd_Ipc_localClientId, IpcNotify_FxnCallback Cdd_Ipc_notify_msgHandler,
                              P2VAR(void, AUTOMATIC, CDD_IPC_APPL_DATA) args);

/** \brief Service to write ipc notify message.
 *
 *
 * Service to Write message from the IPC instance.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Cdd_Ipc_remoteCoreId - Core ID to which you need to sent the message to
 * \param[in] Cdd_Ipc_remoteClientId - Remote client ID registered for the to send the message to
 * \param[in] Cdd_Ipc_msgValue - Message value to be sent
 * \param[in] Cdd_Ipc_waitForFifoNotFull - 1: wait for message to be inserted into HW or SW FIFO,
 *                                         0: if FIFO is full, dont send message and return with
 *error.
 * \return Std_ReturnType
 * \retval E_OK
 * \retval E_NOT_OK
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_Notify_Write(uint32 Cdd_Ipc_remoteCoreId, uint16 Cdd_Ipc_remoteClientId, uint32 Cdd_Ipc_msgValue,
                     uint32 Cdd_Ipc_waitForFifoNotFull);

/** \brief Service to un-register a client for IPC
 *
 *
 * Service to unregister client at a specified client ID.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Cdd_Ipc_localClientId - Local core client ID
 * \return Std_ReturnType
 * \retval E_OK
 * \retval E_NOT_OK
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_IPC_CODE) Cdd_Ipc_Notify_UnregisterClient(uint32 Cdd_Ipc_localClientId);

/** \brief Service for CDD Ipc RpMsg Construct.
 *
 *
 * Create a RPMessage object to receive messages at a specified end-point
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] ConfigPtr - Pointer to configuration set
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_IPC_CODE)
Cdd_Ipc_Construct(P2CONST(Cdd_IpcConfigType, AUTOMATIC, CDD_IPC_CFG) ConfigPtr);

/** \brief Service for CDD Ipc RpMsg GetLoclEndPoint.
 *
 *
 * Service to Send a message to a remote core at a specified remote end point
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] dataLen – Length of buffer
 * \param[in] data – pointer to data buffer
 * \param[in] Cdd_Ipc_remoteCoreId - Core ID to which you need to send the message to.
 * \param[in] Cdd_Ipc_remoteEndPt – Unique end point value on the remote core.
 * \param[in] timeout – Time in system ticks to block for a message receive.
 * \param[in] Cdd_Ipc_localEndPtId - localEndPt, is strictly not needed, however this is available
to the user on the remote core  * and can be used as a reply end point
 * \return Std_ReturnType
 * \retval E_OK
 * \retval E_NOT_OK
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_RpMsg_SendMsg(void* data, uint16 dataLen, uint16 Cdd_Ipc_remoteCoreId, uint16 Cdd_Ipc_remoteEndPt,
                      uint16 Cdd_Ipc_localEndPtId, uint32 timeout);

/** \brief Service for CDD Ipc RpMsg GetLoclEndPoint.
 *
 *
 * Blocking API to wait till a message is received from any CPU at the specified
 * local end point
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \param[in] dataLen – Length of buffer
 * \param[in] data – pointer to data buffer
 * \param[in] Cdd_Ipc_remoteCoreId - Core ID to which you need to send the message to.
 * \param[in] Cdd_Ipc_remoteEndPt – Pointer to Unique end point value on the remote core.
 * \param[in] timeout – Time in system ticks to block for a message receive.
 * \param[in] Cdd_Ipc_localEndPtId – localEndPt need to be passed to retrieve the endpoint message
 *object internally in the driver
 * \return Std_ReturnType
 * \retval E_OK
 * \retval E_NOT_OK
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_RpMsg_RecvMsg(void* data, uint16* dataLen, uint16 Cdd_Ipc_localEndPtId, uint16* Cdd_Ipc_remoteCoreId,
                      uint16* Cdd_Ipc_remoteEndPt, uint32 timeout);

/** \brief Service to delete a previously created RPMessage object
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_IPC_CODE) Cdd_Ipc_Destruct(uint16 Cdd_Ipc_localEndPtId);

/** \brief Service for CDD Ipc Notify SyncAll.
 *
 *
 * Service to sync all the cores that are participating the IPC.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non-Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_IPC_CODE) Cdd_Ipc_Notify_Sync_All(void);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef CDD_IPC_H_ */
