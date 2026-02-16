/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2024 Texas Instruments Incorporated
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

#ifndef IPC_RPMSG_H_
#define IPC_RPMSG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "mcal_hw_soc_defines.h"
#include "ipc_rpmsg_lld_queue.h"
#include "ipc_notify_v1_lld.h"
#include "ipc_rpmsg_linux_resource_table.h"

/**
 * \defgroup DRV_IPC_RPMESSAGE_MODULE  APIs for IPC RPMessage
 * \ingroup DRV_MODULE
 *
 * See \ref DRIVERS_IPC_RPMESSAGE_PAGE for more details.
 *
 * @{
 */
/**
 * \brief Users can create \ref RPMessage_EpObject with local end value in the range of 0 .. \ref
 * RPMESSAGE_MAX_LOCAL_ENDPT - 1
 *
 * This limit is put to allow fast indexing of end point object to
 * recevied messages and the value is kept small to save memory space
 */
#define RPMESSAGE_MAX_LOCAL_ENDPT (64U)

/**
 * \brief Value to indicate if vring ID is valid or NOT
 *
 * When a core does not participate in IPC RPMessage set the vring ID in
 * initParams to this value
 */
#define RPMESSAGE_VRING_ADDR_INVALID (0xFFFFFFFFU)

/**
 * \brief Returns the size needed for each VRING
 *
 * This is approximate size that is >= to actual required size.
 * Approximate size is returned to allow compile time macro for size calculation.
 * Actual required size is calculated in the internal run-time function `RPMessage_vringGetSize`.
 * However this can be ignored by end users. During initialization, a assert is used to check if
 * user provided size is >= actual required size.
 *
 * \param numBuf [in] Number of buffer in the VRING
 * \param bufSize [in] Size of each buffer, in units of bytes
 *
 * \return VRING size in bytes
 */
#define RPMESSAGE_VRING_SIZE(numBuf, bufSize) (((numBuf) * ((bufSize) + 32U)) + 32U)

/**
 * \brief Size of \ref RPMessage_EpObject
 */
#define RPMESSAGE_OBJECT_SIZE_MAX (192U)

/* max number of recevied messages that can be outstanding at various end points
 * This is a per remote core limit
 * Ideally this needs to be equal to number of buffers in vring since that
 * is the theortical max limit on outstanding recv messages.
 */
#define RPMESSAGE_MAX_LOCAL_MSG_OBJ (16U)

/*
 * End Point used to communicate control messages.
 * Primarily used to communicate available end point on a core ID
 */
#define RPMESSAGE_CTRL_ENDPOINT_ID (53U)

/* Message via IPC Notify to indicate is new message is received */
#define RPMESSAGE_MSG_VRING_NEW_FULL (0U)
/* Message via IPC Notify to indicate if free buffers are available for transmit */
#define RPMESSAGE_MSG_VRING_NEW_EMPTY (1U)

/* This is fixed in Linux side and MUST match LInux side */
#define RPMESSAGE_LINUX_MSG_SIZE (512U)

/* VRING ID for TX as used with Linux */
#define RPMESSAGE_LINUX_TX_VRING_ID (0U)

/* VRING ID for RX as used with Linux */
#define RPMESSAGE_LINUX_RX_VRING_ID (1U)

/**
 * \brief Opaque RPMessage object used with the RPMessage APIs
 */
typedef struct RPMessage_EpObject_s
{
    uintptr_t
        rsv[RPMESSAGE_OBJECT_SIZE_MAX / (uint32)sizeof(uint32)]; /**< reserved, should NOT be modified by end users */
} RPMessage_EpObject;

/**
 * \brief Callback that is invoked when a message is received from any CPU at the specified local
 * end point
 *
 * The callback can be optionally registered during \ref RPMessage_lld_construct
 *
 * \note All message contents MUST be consumed in the callback.
 *       When callback returns the message buffer is released back to the sender.
 *       If the message contents are needed for deferred processing then take a copy of the message
 * contents
 *
 * \param obj   [in] RPMessage end point object created with \ref RPMessage_lld_construct
 * \param arg  [in] Arguments specified by user during \ref RPMessage_lld_construct
 * \param data  [in] Pointer to message
 * \param dataLen [in] Length of message
 * \param remoteCoreId [in] Core ID of sender
 * \param remoteEndPt [in] End point of sender
 */
typedef void (*RPMessage_lld_recvCallback)(void *handle, RPMessage_EpObject *obj, void *arg, void *data, uint16 dataLen,
                                           sint32 crcStatus, uint16 remoteCoreId, uint16 remoteEndPt);

/**
 * \brief Callback that is invoked when a message is received from any CPU at the specified local
 * end point
 *
 * The callback can be optionally registered during \ref RPMessage_lld_construct
 *
 * \note Unlike \ref RPMessage_lld_recvCallback, this callback only notifies that there is one or
 * more messages to be read, but the message itself is not read by the driver unless \ref
 * RPMessage_lld_recv is called in this callback or later within a task.
 *
 * \note If \ref RPMessage_lld_recvCallback is set, then \ref RPMessage_lld_recvNotifyCallback
 * callback is not used.
 *
 * \param obj   [in] RPMessage end point object created with \ref RPMessage_lld_construct
 * \param arg  [in] Arguments specified by user during \ref RPMessage_lld_construct
 */
typedef void (*RPMessage_lld_recvNotifyCallback)(void *handle, RPMessage_EpObject *obj, void *arg);

/**
 * \brief Callback that is invoked when a annoucement message is received on the control end point
 *
 * The callback can be optionally registered during \ref RPMessage_lld_init
 *
 * \note All message contents MUST be consumed in the callback.
 *       When callback returns the message buffer is released back to the sender.
 *       If the message contents are needed for deferred processing then take a copy of the message
 * contents
 *
 * \param arg  [in] Arguments specified by user during \ref RPMessage_lld_init
 * \param remoteCoreId [in] Core ID of sender
 * \param remoteEndPt [in] End point of sender that has annoucned the service over the control end
 * point
 * \param remoteServiceName [in] Name of the remote service that is annoucned
 */
typedef void (*RPMessage_ControlEndPtCallback)(void *arg, uint16 remoteCoreId, uint16 remoteEndPt,
                                               const uint8 *remoteServiceName);

/* VRING structure in shared memory is as below for a VRING
   with N buffers and max msg size of X

   mesage desc [0]          (16 bytes each)
   mesage desc [1]
   ...
   mesage desc [N-1]
   avail Q flags            (2 bytes)
   avail Q current index    (2 bytes)
   avail Q element [0]      (2 bytes each)
   avail Q element [1]
   ...
   avail Q element [N-1]
   alignment padding, if any, needs 4 byte alignment atleast
   used Q flags              (2 bytes)
   used Q current index      (2 bytes)
   used Q element [0] ID     (4 bytes each)
   used Q element [0] Length (4 bytes each)
   used Q element [1] ID
   used Q element [1] Length
   ...
   used Q element [N-1] ID
   used Q element [N-1] Length
   alignment padding, if any, needs 4 byte alignment atleast
   message buffer [0]       (X bytes each)
   message buffer [1]
   ...
   message buffer [N-1]

   Total size of a VRING is
     16 * N
   + align(4 + 2 * N) to 4 bytes
   + align(4 + 8 * N) to 4 bytes
   + X * N

   When there are K CPUs participating in IPC RPMessage,
   there are total ( K * (K-1) ) VRINGs to allow TX and RX of messages
   from any CPU to any CPU

   It is recommended to keep X as a power of 2, like 64, 128, 256
   It is recommended to keep N as multiple of 2, like 2, 4, 6, 8

   In memory constrained systems, recommended values are
   X = 128, N = 8 and alignment of 4 bytes

   In this case total memory needed for VRING size when 4 CPUs are involved is,

   ( 16 * N + 4 + 2 * N + 4 + 8 * N + N * X   ) * (K * (K-1))
   ( 16 * 8 + 4 + 2 * 8 + 4 + 8 * 8 + 8 * 128 ) * (4 * (4-1))
   = 14880 bytes ~ 14.6 KB

   A simpler formula which will always be valid is below
   number of buffers * (size of buffer + 32) + number of CPUs * ( number of CPUs - 1 )

   For above example, this is
   ( 8 * ( 128 + 32 ) * 4 * (4-1) )
   = 15360 bytes = 15 KB
*/

/* buffer descriptor within vring
 * descriptor value are set once during vring init and dont change after that
 */
struct vring_desc
{
    uint32 addr;    /* Physical address of message buffer */
    uint32 padding; /* NOT USED */
    uint32 len;     /* max length of message buffer */
    uint16 flags;   /* NOT USED */
    uint16 next;    /* NOT USED */
};

/* avail Q */
struct vring_avail
{
    uint16 flags;   /* NOT USED */
    uint16 idx;     /* next write index within vring_avail.ring */
    uint16 ring[1]; /* buffer ID, valid values are 0 .. number of buffers - 1 */
};

/* used Q element */
struct vring_used_elem
{
    uint32 id;  /* buffer ID, valid values are 0 .. number of buffers - 1 */
    uint32 len; /* NOT USED */
};

/* used Q  */
struct vring_used
{
    uint16                 flags;   /* NOT USED */
    uint16                 idx;     /* next write index within vring_used.ring */
    struct vring_used_elem ring[1]; /* used Q elements */
};

/* header that is present in every message buffer, this space is not available for
 * users, that max message size from user point of view is
 * message buffer size - sizeof(RPMessage_Header)
 *
 * e.g, if message buffer size is 128 bytes, max message size for user is
 *      128 - 16 = 112 bytes
 */
typedef struct
{
    uint32 srcEndPt;  /* source/sender endpoint        */
    uint32 dstEndPt;  /* destination/receiver endpoint */
    uint32 srcCoreId; /* NOT USED                      */
    uint16 dataLen;   /* length of valid user data in the message buffer */
    uint16 flags;     /* NOT USED                      */
} RPMessage_Header;

/* local structure to maintain state of a given VRING,
 * holds pointers to shared memory VRING data structures
 */
typedef struct
{
    uint16              lastUsedIdx;  /* last read index into used Q */
    uint16              lastAvailIdx; /* last read index into avail Q */
    uint16              vringNumBuf;  /* number of buffer in the vring */
    struct vring_desc  *desc;         /* pointer to buffer descriptors in VRING shared memory */
    struct vring_avail *avail;        /* pointer to avail Q in VRING shared memory */
    struct vring_used  *used;         /* pointer to used Q in VRING shared memory */
    uint8              *bufBaseAddr;  /* pointer to message buffer 0 in VRING shared memory */
} RPMessage_Vring;

/* structure to hold received buffer ID and sender core ID
 *
 * An instance of this structure is put into the end point specific queue.
 * On calling rpmsg recv, an element from end point queue is extracted,
 * the vring buffer processed and the vring buffer is freed.
 *
 * This prevents a copy from vring to local end point queue
 * and also reduces the memory needed for local queing
 */
typedef struct
{
    struct RPMessage_QueueElem_s elem;         /* queue element header */
    uint16                       remoteCoreId; /* remote core that sent a message */
    uint16                       vringBufId;   /* buffer ID within VRING which holds the message */
} RPMessage_LocalMsg;

/* structure to hold state of IPC rpmsg with a remote core
 */
typedef struct
{
    uint32             newEmptyVringBufSem; /* semaphore to indicate if a empty buffer
                                             *  is available to transmit
                                             *
                                             * ONLY used during transmit
                                             */
    uint32             freeQAllocPending;   /* flag to indicate if a freeQ alloc failed
                                             * and therefore there is a pending recvied message in VRING
                                             * if this flag is set then recv message handler is invoked without
                                             * waiting for a new interrupt
                                             *
                                             * ONLY used during receive.
                                             */
    RPMessage_Queue    freeQ;               /* queue of RPMessage_LocalMsg to hold received messages until
                                             * they are processed by users
                                             *
                                             * ONLY used during receive.
                                             */
    RPMessage_LocalMsg localMsgObj[RPMESSAGE_MAX_LOCAL_MSG_OBJ]; /* RPMessage_LocalMsg messages are
                                                                  * put in the freeQ initially
                                                                  *
                                                                  * ONLY used during receive.
                                                                  */
    RPMessage_Vring    vringTxObj; /* VRING used to transmit messages to this remote core */
    RPMessage_Vring    vringRxObj; /* VRING used to receive messages from this remote core */
} RPMessage_Core;

/* structure to hold state of RPMessage end point */
typedef struct
{
    uint16                     localEndPt;       /* local end point number, MUST be < RPMESSAGE_MAX_LOCAL_ENDPT */
    RPMessage_lld_recvCallback recvCallback;     /* when not 0, received messages are handled in
                                                    callback that via RPMessage_lld_recv */
    void                      *recvCallbackArgs; /* arguments passed to the recvCallback callback */
    uint32                     doRecvUnblock;    /* flag to unblock RPMessage_lld_recv, if its blocked for every waiting
                                                    for messages and user wants to shutdown or exit */
    RPMessage_Queue            endPtQ;           /* end point specific queue to hold received messages pending for
                                                    processing at this end point */
    uint32                     newEndPtMsgSem;   /* semaphore to indicate that there messages pending endPtQ */
    RPMessage_lld_recvNotifyCallback
          recvNotifyCallback;     /* when not 0, this callback is whenever a message is received */
    void *recvNotifyCallbackArgs; /* arguments passed to the recvNotifyCallback callback */
} RPMessage_Struct;

/* message that is sent during annouce and received by a control end point */
#define RPMESSAGE_ANNOUNCE_SERVICENAME_LEN (32u)
typedef struct
{
    uint8  name[RPMESSAGE_ANNOUNCE_SERVICENAME_LEN]; /* service name that has annouced */
    uint32 remoteEndPt;                              /* end point at which the service is read */
    uint32 type;                                     /* NOT USED */
} RPMessage_AnnounceMsg;

/**
 * \brief Parameters passed to \ref RPMessage_lld_construct
 *
 * It is recommended to set defaults using \ref RPMessage_lld_CreateParams_init
 * and then override with user specified parameters.
 *
 * \note When `recvCallback` is enabled, \ref RPMessage_lld_recv API should not be used and
 *       will always return failure. In this case, the received message is read and made available
 * in the callback itself and the message needs to be consumed in the callback itself.
 *
 * \note When `recvNotifyCallback` is enabled, \ref RPMessage_lld_recv API still needs to used to
 * read the message. The callback just informs there are one or more messages are pending.
 */
typedef struct
{
    uint16                     localEndPt;       /**< local end point at which to listen for received mesages */
    RPMessage_lld_recvCallback recvCallback;     /**< Optional callback to invoke when a message is
                                                    received at this end point */
    void                      *recvCallbackArgs; /**< Arguments to pass to the `recvCallback` callback */
    RPMessage_lld_recvNotifyCallback
          recvNotifyCallback;     /**< Optional callback to notify user when a message is received at this
                                     end point. If `recvCallback` is set, then this callback is not used
                                   */
    void *recvNotifyCallbackArgs; /**< Arguments to pass to the `recvNotifyCallback` callback */
} RPMessage_CreateParams;

/**
 *  \brief IPC RPMessage driver initialization object
 *
 *  \note Set vringTxBaseAddr[], vringTxBaseAddr[] to RPMESSAGE_VRING_ADDR_INVALID for cores that
 *        are not needed for IPC RPMessage.
 *  \note All cores MUST set the same value for `vringSize`, `vringNumBuf`, `vringMsgSize`.
 *  \note Set `vringTxBaseAddr`, `vringRxBaseAddr`, based on source and destination cores.
 *  \note VRING memory is shared across all cores AND this memory MUST be marked
 *        as non-cached at all the cores.
 */
typedef struct
{
    uintptr_t vringTxBaseAddr[MCAL_CSL_CORE_ID_MAX]; /**< VRING address of transmit rings to each core */
    uintptr_t vringRxBaseAddr[MCAL_CSL_CORE_ID_MAX]; /**< VRING address of receive rings to each core */
    uint32    vringSize;    /**< Size of memory assigned to one VRING, use \ref RPMESSAGE_VRING_SIZE to
                               find the size needed */
    uint16    vringNumBuf;  /**< Max number of buffers in one VRING */
    uint16    vringMsgSize; /**< Size of each message in one VRING */
    const RPMessage_ResourceTable *linuxResourceTable; /**< Linux resoruce table for self core,
                                                        * when non-0 Cortex A* is assumed to run Linux.
                                                        * And VRING info  for message exchange with LInux
                                                        * is specified in the resource table
                                                        */
    uint16                         linuxCoreId;        /** ID of linux core */
    IpcNotify_Handle               hIpcNotify;         /* IPC Notify Handle to be used */
} RPMessageLLD_InitObject, *RPMessageLLD_InitHandle;

typedef struct
{
    uint16                         selfCoreId;
    /* self core ID */
    uint8                          isCoreEnable[MCAL_CSL_CORE_ID_MAX];
    /* 1: core is enabled for IPC RPMessage, else disabled */
    uint8                          isCoreInitialized[MCAL_CSL_CORE_ID_MAX];
    /* 1: core is initialized for IPC RPMessage, else not yet initialized */
    RPMessage_Core                 coreObj[MCAL_CSL_CORE_ID_MAX];
    /* remote core objects, indexed by remote core ID */
    RPMessage_Struct              *localEndPtObj[RPMESSAGE_MAX_LOCAL_ENDPT];
    /* end point objects, indexed by endpoint ID */
    RPMessage_EpObject             controlEndPtObj;
    /* object/handle of end point that receives accouncement messages */
    RPMessage_ControlEndPtCallback controlEndPtCallback;
    /* user callback to invoke when a control message is received */
    void                          *controlEndPtCallbackArgs;
    /* user callback args for control message */
    const RPMessage_ResourceTable *linuxResourceTable;
    /* resource table used with linux */
    uint16                         linuxCoreId;
    /* Core ID of core running linux */
    RPMessageLLD_InitHandle        hRpMsgInit;
    /**< [IN] Initialization parameters of IPC RPMsg instance */
    /*
     * State variables
     */
    uint32                         state;
} RPMessageLLD_Object, *RPMessageLLD_Handle;

/**
 * \brief Set default values to \ref RPMessage_CreateParams
 *
 * \param params [out] default intialized structure
 */
void RPMessage_lld_CreateParams_init(RPMessage_CreateParams *params);

/**
 * \brief Initialize RPMessage module
 *
 * \param hRpMsg IPC RPMsg LLD handle
 *
 * \return #MCAL_SystemP_SUCCESS if successful; else error on failure
 */
sint32 RPMessage_lld_init(RPMessageLLD_Handle hRpMsg);

/**
 * \brief De-Initialize RPMessage module
 *
 * \param hRpMsg IPC RPMsg LLD handle
 *
 * \return #MCAL_SystemP_SUCCESS if successful; else error on failure
 */
sint32 RPMessage_lld_deInit(RPMessageLLD_Handle hRpMsg);

/**
 * \brief Wait for linux side RPMessage to be ready
 *
 * Messages should not be sent to Linux, if enabled, until this function
 * return success.
 *
 * \note When using RPMessage between RTOS/no-RTOS cores then this API
 *       needed not be called.
 *
 * \param timeout [in] Timeout in units of system ticks
 *
 * \return MCAL_SystemP_SUCCESS, linux has initialized its side of RPMessage
 */
sint32 RPMessage_lld_waitForLinuxReady(RPMessageLLD_Handle hRpMsg, uint32 timeout);

/**
 * \brief Create a RPMessage object to receive messages at a specified end-point
 *
 * \note Each new object that is created MUST have a unique local end point.
 * \note Local end point MUST be < RPMESSAGE_MAX_LOCAL_ENDPT
 * \note User MUST choose a value and `ANY` is not supported
 * \note When callback is registered in \ref RPMessage_CreateParams, \ref RPMessage_lld_recv MUST
 * not be used.
 *
 * \param obj [out] Created object
 * \param createParams [in] parameters
 *
 * \return E_OK on success, else failure.
 */
Std_ReturnType RPMessage_lld_construct(RPMessageLLD_Handle hRpMsg, RPMessage_EpObject *obj,
                                       const RPMessage_CreateParams *createParam);

/**
 * \brief Delete a previously created RPMessage object
 *
 * \param obj [in] object
 */
void RPMessage_lld_destruct(RPMessageLLD_Handle hRpMsg, RPMessage_EpObject *obj);

/**
 * \brief Announce a local end point at which a `service` is created to a remote core
 *
 * \note Announcing end points is optional and is not used internally by IPC RPmessage in
 *       any way.
 * \note User MUST announce one by one to all remote core's of interest.
 *       There is no announce to `ALL` option
 * \note To handle announcement messages, make sure user handler is registered during
 *       \ref RPMessage_lld_init.
 * \note It is upto the end user to use the callback to signal or wait until a remote service is
 *       announced.
 *
 * \param remoteProcId [in] The remote core to annouce to.
 * \param localEndPt [in] Local end point of the service that is being announced
 * \param name  [in] Name of the service that is being announced
 *
 * \return MCAL_SystemP_SUCCESS, when the annouce message was sent, else failure
 */
/*sint32  RPMessage_lld_announce(RPMessageLLD_Handle hRpMsg, uint16 remoteProcId, uint16 localEndPt,
 * const uint8* name);*/

/**
 * \brief Send a message to a remote core at a specified remote end point
 *
 * \note `dataLen` MUST be <= initParams.vringMsgSize - 16 bytes for internal header
 * \note In order for a remote core to receive the message,
 *       a end point should be created on the remote core at the same value as `remoteEndPt`
 * \note localEndPt, is strictly not needed, however this is available to the user on the remote
 * core and can be used as a reply end point. Use \ref RPMessage_getLocalEndPt to set to the
 * RPMessage object at which to listen for replies
 * \note When timeout is 0, then if a free buffer is not available to transmit, it will
 *       return will immediately SystemP_TIMEOUT. Else it will wait for specified `timeout`
 *       ticks for a free buffer to be available.
 *
 * \param data [in] Pointer to message data to send
 * \param dataLen [in] size of message data to send
 * \param remoteCoreId  [in] Remote core ID to whom the message is being sent
 * \param remoteEndPt  [in] Remote core end point ID to which the message is being sent
 * \param localEndPt [in] Local end point that is sending the message
 * \param timeout   [in] Amount of time to wait, in units of system ticks
 *
 * \return MCAL_SystemP_SUCCESS, when the send message was successful
 * \return SystemP_TIMEOUT, message not sent since free transmit buffer not available and timeout
 * happened.
 */
sint32 RPMessage_lld_send(RPMessageLLD_Handle hRpMsg, void *data, uint16 dataLen, uint16 remoteCoreId,
                          uint16 remoteEndPt, uint16 localEndPt, uint32 timeout);

/**
 * \brief Blocking API to wait till a message is received from any CPU at the specified local end
 * point
 *
 * \note Local end point is specified during \ref RPMessage_lld_construct
 * \note When callback is registered this API should not be used.
 * \note `dataLen` when passed by user contains the user message buffer size, i.e size of buffer
 * pointer to by 'data`. If received message size exceeds *dataLen then it is truncated. If received
 * message size is <= *dataLen then all received bytes are copied to `data` and *dataLen indicates
 * the size of valid bytes in `data`
 *
 * \param obj   [in] RPMessage end point object created with \ref RPMessage_lld_construct
 * \param data  [in] Pointer to received message contents
 * \param dataLen [in] Length of user message buffer, in bytes \n [out] Size of received message, in
 * bytes
 * \param remoteCoreId [out] Core ID of sender
 * \param remoteEndPt [out] End point of sender
 * \param timeout   [in] Time in system ticks to block for a message receive
 *
 * \return MCAL_SystemP_SUCCESS, new message received, all output parameters are valid
 * \return SystemP_TIMEOUT, API unblocked due to timeout and output parameters should not be used.
 */

void                RPMessage_controlEndPtDeInit(RPMessageLLD_Handle hRpMsg);
uint32              RPMessage_controlEndPtInit(RPMessageLLD_Handle hRpMsg);
uint32              RPMessage_isLinuxCore(RPMessageLLD_Handle hRpMsg, uint16 coreId);
sint32              RPMessage_coreInit(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId);
void                RPMessage_coreDeInit(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId);
void                RPMessage_putEndPtMsg(RPMessage_Struct *epObj, RPMessage_LocalMsg *pMsg);
RPMessage_LocalMsg *RPMessage_allocEndPtMsg(RPMessage_Core *coreObj, uint32 remoteCoreId);
sint32              RPMessage_getEndPtMsg(RPMessage_Struct *epObj, RPMessage_LocalMsg **pMsg, uint32 timeout);
void                RPMessage_lld_recvHandler(RPMessageLLD_Handle hRpMsg, uint32 remoteCoreId, uint32 timeout);
uint32              RPMessage_freeEndPtMsg(RPMessage_Core *coreObj, uint16 remoteCoreId, RPMessage_LocalMsg *pMsg);
void   RPMessage_notifyCallback(void *ipcNotifyHandle, uint32 remoteCoreId, uint16 localClientId, uint32 msgValue,
                                uint32 timeout, sint32 crcStatus, void *args);
sint32 RPMessage_lld_recv(RPMessageLLD_Handle hRpMsg, RPMessage_EpObject *obj, void *data, uint16 *dataLen,
                          uint16 *remoteCoreId, uint16 *remoteEndPt, uint32 timeout);
void RPMessage_controlEndPtHandler(void *rpMsgHandle, RPMessage_EpObject *epObj, void *arg, void *data, uint16 dataLen,
                                   sint32 crcStatus, uint16 remoteCoreId, uint16 remoteEndPt);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* IPC_RPMSG_H_ */
