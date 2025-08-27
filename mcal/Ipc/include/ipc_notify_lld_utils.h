/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef IPC_NOTIFY_LLD_UTILS_V0_H_
#define IPC_NOTIFY_LLD_UTILS_V0_H_

/**
 * \addtogroup CDD_IPC Ipc API GUIDE Header file
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#include "ipc_notify_v1_lld.h"
#include "Cdd_Ipc.h"
/**
 * \brief Client ID used for sync messages, this client ID should not be used by other users
 */
#define IPC_NOTIFY_CLIENT_ID_SYNC (1U)

/**
 *  \brief IPC Notify Utils driver initialization object
 */
typedef struct
{
    /** \brief IPC Notify driver handle */
    IpcNotify_Handle hIpcNotify;
} IpcNotifyUtils_InitObject, *IpcNotifyUtils_InitHandle;

/**
 *  \brief IPC Notify Utils driver object
 */
typedef struct
{
    /** \brief [IN] Number of sync messages pending */
    uint16                    syncMsgPend[MCAL_CSL_CORE_ID_MAX];
    /** \brief [IN] Initialization parameters of IPC Notify instance */
    IpcNotifyUtils_InitHandle hIpcNotifyUtilsInit;
} IpcNotifyUtils_Object, *IpcNotifyUtils_Handle;

/**
 * \brief Initialize IPC Notify Utils module
 *
 * This API will initialize the Utils module for IPC.
 *
 * \param[in] hIpcNotifyUtils - IPC Notify LLD utils handle
 * \return sint32
 * \retval #MCAL_SystemP_SUCCESS if successful; else error on failure
 */
sint32 IpcNotifyUtils_lld_init(IpcNotifyUtils_Handle hIpcNotifyUtils);

/**
 * \brief Send a sync message to specific core
 *
 * This API can be used to send sync message's to very specific core's
 * For most users recommend to use the more simpler IpcNotify_syncAll() API.
 *
 * \param[in] remoteCoreId - Core ID, see \ref CSL_CoreID for valid values.
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS, sync message was sent successfully, else failure
 */
sint32 IpcNotifyUtils_lld_sendSync(IpcNotifyUtils_Handle hIpcNotifyUtils, uint32 remoteCoreId);

/**
 * \brief Wait for a sync message to be received from the specified core
 *
 * This API can be used to recevice sync message from very specific core's
 * For most users recommend to use the more simpler IpcNotify_syncAll() API.
 *
 * \param[in] remoteCoreId - Core ID, see \ref CSL_CoreID for valid values.
 * \param[in] timeout - Amount of time in units of ticks to wait
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS, sync message was received successfully
 * \retval SystemP_TIMEOUT, sync message was NOT received after `timeout` ticks
 * \retval SystemP_FAILURE, invalid arguments
 */
sint32 IpcNotifyUtils_lld_waitSync(IpcNotifyUtils_Handle hIpcNotifyUtils, uint32 remoteCoreId, uint32 timeout);

/**
 * \brief Send a message to all enabled cores and wait for sync message from all enabled cores
 *
 * This API when called on all CPUs, make sure all CPUs execute upto a certain and then proceed
 * only when all other CPUs have also executed to the same point.
 *
 * This is useful esp during system init to make sure message exchange can be started only
 * after all CPUs have finished their system initialization.
 *
 * \param[in] timeout - Amount of time in units of ticks to wait for the sync
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS, all sync messages recevied successfully
 * \retval SystemP_TIMEOUT, some sync messages was NOT recevied after `timeout` ticks
 * \retval SystemP_FAILURE, invalid arguments
 */
sint32 IpcNotifyUtils_lld_syncAll(IpcNotifyUtils_Handle hIpcNotifyUtils, uint32 timeout);

void IpcNotifyUtils_lld_syncCallback(void* hIpcNotify, uint32 remoteCoreId, uint16 localClientId, uint32 msgValue,
                                     uint32 timeout, sint32 crcStatus, void* args);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /* IPC_NOTIFY_LLD_UTILS_V0_H_ */
