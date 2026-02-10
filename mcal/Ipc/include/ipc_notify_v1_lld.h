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

#ifndef IPC_NOTIFY_LLD_H_
#define IPC_NOTIFY_LLD_H_

#include "Platform_Types.h"
#include "stdint.h"
#include "ipc_notify_v1_mailbox.h"
#include "sys_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup DRV_IPC_NOTIFY_LLD_MODULE  APIs for IPC Notify LLD
 * \ingroup DRV_MODULE
 *
 * See \ref DRIVERS_IPC_NOTIFY_LLD_PAGE for more details.
 *
 * @{
 */

typedef void (*IpcNotify_FxnCallback)(void *hIpcNotify, uint32 remoteCoreId, uint16 localClientId, uint32 msgValue,
                                      uint32 timeout, sint32 crcStatus, void *args);
typedef sint32 (*IpcCrcHookFxn)(uint8 *data, uint16 dataLen, uint8 crcSize, void *crc);

/**
 * \brief Maximum number of clients possible for receiving messages.
 */
#define IPC_NOTIFY_CLIENT_ID_MAX (16U)

/**
 * \brief Client ID used by rpmessage, this client ID should not be used by other users
 */
#define IPC_NOTIFY_CLIENT_ID_RPMSG (0U)

/* This shift value MUST be in sync with IPC_NOTIFY_CLIENT_ID_MAX
 * and IPC_NOTIFY_MSG_VALUE_MAX
 */
#define IPC_NOTIFY_CLIENT_ID_SHIFT (28U)

#define IPC_NOTIFY_CRC_SHIFT (20U)

/**
 * \brief Maximum value of message that can be sent and received.
 */
#define IPC_NOTIFY_MSG_VALUE_MAX (0x10000000U)

/**
 * \brief This structure describes the mailbox information to send a message from core A to core B
 */
typedef struct IpcNotify_MailboxConfig_s
{
    uint32             writeDoneMailboxBaseAddr; /**< Mailbox register address at which core will post interrupt */
    uint32             readReqMailboxBaseAddr;   /**< Mailbox register address at which core will receive
                                                    interrupt */
    uint8              intrBitPos; /**< Bit pos in the mailbox register which should be set or cleared to post or
                                      clear a interrupt to other core */
    IpcNotify_SwQueue *swQ;        /**< Infomration about the SW queue associated with this HW mailbox */

} IpcNotify_MailboxConfig;

/**
 * \brief This structure describes the information related to one interrupt that is
 *        setup for receiving mailbox messages
 *
 * One interrupt can be used to handle messages from multiple cores.
 */
typedef struct IpcNotify_InterruptConfig_s
{
    uint32 intNum;                           /**< interrupt number */
    uint32 eventId;                          /**< interrupt event ID, not used for ARM cores */
    uint8  numCores;                         /**< Number of remote cores attached to this interrupt. */
    uint8  coreIdList[MCAL_CSL_CORE_ID_MAX]; /**< List of Core ID's attached to this interrupt
                                              *
                                              *   See \ref CSL_CoreID for valid values for this field.
                                              */
    uint32 clearIntOnInit; /* 0: do not clear pending interrupts during IpcNotify_init, 1: clear pending interrupts */
    void (*callback)(void *args); /**< Callback associated with every interrupt */
} IpcNotify_InterruptConfig;

/**
 *  \brief IPC Notify driver initialization object
 */
typedef struct
{
    uint32        intrPriority;
    /** IPC Notify interrupt priority */
    uint32        selfCoreId;
    /* core ID on which this module is running */
    uint32        numCores;
    /**< Number of remote cores participating in IPC, excluding the core on
     *  which this API is called.
     */
    uint32        coreIdList[MCAL_CSL_CORE_ID_MAX];
    /**< List of Core ID's participating in IPC, excluding the core on
     *   which this API is called.
     *
     *   See \ref CSL_CoreID for valid values for this field.
     */
    IpcCrcHookFxn Cdd_Ipc_CrcHookFunc;
} IpcNotify_InitObject;

typedef IpcNotify_InitObject *IpcNotify_InitHandle;

/**
 *  \brief IPC Notify driver object
 */
typedef struct
{
    IpcNotify_FxnCallback      callback[IPC_NOTIFY_CLIENT_ID_MAX];
    /* user registered callback's */
    void                      *callbackArgs[IPC_NOTIFY_CLIENT_ID_MAX];
    /* arguments to user registered callback's */
    uint8                      isCoreEnabled[MCAL_CSL_CORE_ID_MAX];
    /* flags to indicate if a core is enabled for IPC */
    IpcNotify_InterruptConfig *interruptConfig;
    /* interrupt config for this core,
     * this is a array with one element per interrupt that is setup to receive messages
     */
    uint32                     interruptConfigNum;
    /* number of interrupts to setup, i.e number of element in interruptConfig array */

    IpcNotify_InitHandle hIpcNotifyInit;
    /**< [IN] Initialization parameters of IPC Notify instance */
} IpcNotify_Object;

typedef IpcNotify_Object *IpcNotify_Handle;

/**
 * \brief Structure to hold message parameters for IPC Notify send operations
 */
typedef struct IpcNotify_MsgParams_s
{
    uint32 remoteCoreId;
    /**< Remote core to send message to */
    uint16 remoteClientId;
    /**< Remote core client ID */
    uint32 messageValue;
    /**< Message value to send */
    uint32 waitForFifoNotFull;
    /**< 1: wait for FIFO, 0: return error if full */
    uint32 timeout;
    /**< Timeout in ticks */
} IpcNotify_MsgParams;

/**
 * \brief Initialize IPC Notify module
 *
 * This API will initialize the HW used for IPC.
 *
 * \param hIpcNotify IPC Notify LLD handle
 *
 * \return #MCAL_SystemP_SUCCESS if successful; else error on failure
 */
sint32 IpcNotify_lld_init(IpcNotify_Handle hIpcNotify);

/**
 * \brief De-initialize IPC Notify module
 *
 * This API will de-initialize the HW used for IPC.
 *
 * \param hIpcNotify IPC Notify LLD handle
 *
 * \return #MCAL_SystemP_SUCCESS if successful; else error on failure
 */
sint32 IpcNotify_lld_deInit(IpcNotify_Handle hIpcNotify);

/**
 * \brief Send message to a specific remote core and specific client ID on that remote core
 *
 * \note To reduce latency, error checks are avoided in this API.
 * Users need to make sure the client ID value is < \ref IPC_NOTIFY_CLIENT_ID_MAX
 * and message value is < \ref IPC_NOTIFY_MSG_VALUE_MAX
 *
 * \note One cannot send messages to self,
 *       i.e remoteCoreId, cannot be same as core ID of the CPU that called this API.
 *
 * \param hIpcNotify     IPC Notify LLD handle
 * \param msgParams   [in] message specific structure parameter
 *
 * \return MCAL_SystemP_SUCCESS, message sent successfully
 * \return SystemP_FAILURE, message could not be sent since HW or SW FIFO for holding the message is full.
 */
sint32 IpcNotify_lld_sendMsg(IpcNotify_Handle hIpcNotify, const IpcNotify_MsgParams *msgParams);

/**
 * \brief Register a callback to handle messages received from a specific remote core and for a specific local client ID
 *
 * \param hIpcNotify IPC Notify LLD handle
 * \param localClientId [in] Client ID to which the message has been sent
 * \param msgCallback [in] Callback to invoke, if callback is already registered, error will be returned.
 * \param args [in] User arguments, that are passed back to user when the callback is invoked
 *
 * \return MCAL_SystemP_SUCCESS, callback registered sucessfully
 * \return SystemP_FAILURE, callback registration failed, either remoteCoreId or localClientId is invalid or callback
 * already registered.
 */
sint32 IpcNotify_lld_registerClient(IpcNotify_Handle hIpcNotify, uint16 localClientId,
                                    IpcNotify_FxnCallback msgCallback, void *args);

/**
 * \brief Un-register a previously registered callback
 *
 * \param hIpcNotify IPC Notify LLD handle
 * \param localClientId [in] Client ID to which the message has been sent
 *
 * \return MCAL_SystemP_SUCCESS, callback un-registered sucessfully
 * \return SystemP_FAILURE, callback un-registration failed, either remoteCoreId or localClientId is
 * invalid
 */
sint32 IpcNotify_lld_unregisterClient(IpcNotify_Handle hIpcNotify, uint16 localClientId);

/**
 * \brief IPC Notify LLD ISR which can be registered in the application.
 *
 * \param args Argument to the ISR function.
 */
__attribute__((weak)) void IpcNotify_lld_isr(void *args);

/**
 * \brief Return current core ID
 *
 * \param hIpcNotify IPC Notify LLD handle
 *
 * \return Core ID, see \ref CSL_CoreID for valid values.
 */
uint32 IpcNotify_lld_getSelfCoreId(IpcNotify_Handle hIpcNotify);

/**
 * \brief Check if a core is enabled for IPC
 *
 * \param hIpcNotify IPC Notify LLD handle
 * \param coreId [in] Core ID, see \ref CSL_CoreID for valid values.
 *
 * \return 1: core is enabled for IPC, 0: core is not enabled for IPC
 */

uint32 Cdd_Ipc_Clock_ticksToUsec(uint32 ticks);
void   Cdd_Ipc_Clock_uSleep(uint32 usec) __attribute__((optnone));
uint32 IpcNotify_lld_isCoreEnabled(IpcNotify_Handle hIpcNotify, uint32 coreId);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* IPC_NOTIFY_H_ */
