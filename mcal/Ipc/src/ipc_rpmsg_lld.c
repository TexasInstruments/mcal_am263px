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

#include "ipc_rpmsg_lld_priv.h"
#include "sys_pmu.h"

static inline sint32 RPMessage_lld_init_Copy_Values(RPMessageLLD_Handle hRpMsg);
static inline sint32 RPMessage_lld_init_Enable_Core(RPMessageLLD_Handle hRpMsg);
static sint32  RPMessage_lld_init_lldInitParamsCheck(RPMessageLLD_Handle hRpMsg, RPMessageLLD_InitHandle hRpMsgInit,
                                                     sint32 status);
static sint32  RPMessage_lld_ParamsCheck(RPMessageLLD_InitHandle hRpMsgInit, sint32 value);
static boolean RPMessage_getEndPtMsg_timeoutCheck(RPMessage_Struct *epObj, sint32 *status, boolean done,
                                                  uint32 startTime, uint32 timeout);
static sint32  RPMessage_lld_recvHandlerEndPtCheck(RPMessageLLD_Handle hRpMsg, RPMessage_LocalMsg *pMsg,
                                                   uint16 localEndPt, uint8 *vringBufAddr, RPMessage_Header *header,
                                                   uint32 remoteCoreId, sint32 status, uint16 vringBufId,
                                                   uint32 timeout);
static void RPMessage_notify_Callback(RPMessageLLD_Handle hRpMsg, uint32 remoteCoreId, uint32 msgValue, uint32 timeout,
                                      uint16 rxMsgValue);
static sint32 RPMessage_lldSend_vringPutFullTxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 vringBufId,
                                                  uint16 dataLen, uint16 remoteEndPt, uint16 localEndPt, void *data,
                                                  uint32 timeout, sint32 status);
static uint32 RPMessage_getEndPtMsg_mutexResourceTryLock(RPMessage_Struct *epObj, sint32 *status, uint32 tryLoop,
                                                         uint32 startTicks, uint32 timeout);
static void   RPMessage_lld_recvdataLenCheck(RPMessage_Header *header, uint16 *dataLen);
static sint32 RPMessage_lld_recvHandlerEndPtCheck_EmptyRxBuf(RPMessageLLD_Handle hRpMsg, sint32 retVal,
                                                             uint32 remoteCoreId, uint16 vringBufId, uint32 timeout);
static sint32 RPMessage_lld_recv_statusCheck(sint32 status);
static void RPMessage_lld_recvHandlerEndPtCheck_recvNotifyCallback(RPMessageLLD_Handle hRpMsg, RPMessage_Struct *epObj);
static void RPMessage_lld_recv_Notify_Callback(RPMessageLLD_Handle hRpMsg, uint16 *remoteCoreId, uint32 timeout,
                                               uint32 isAllocPending);
#define CDD_IPC_START_SEC_CODE
#include "Cdd_Ipc_MemMap.h"

RPMessage_LocalMsg *RPMessage_allocEndPtMsg(RPMessage_Core *coreObj, uint32 remoteCoreId)
{
    RPMessage_LocalMsg *pMsg;

    SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
    pMsg = (RPMessage_LocalMsg *)RPMessage_queueGet(&coreObj->freeQ);
    if (pMsg == NULL_PTR)
    {
        coreObj->freeQAllocPending = 1U;
    }
    else
    {
        coreObj->freeQAllocPending = 0U;
    }
    SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();

    return pMsg;
}

uint32 RPMessage_freeEndPtMsg(RPMessage_Core *coreObj, uint16 remoteCoreId, RPMessage_LocalMsg *pMsg)
{
    uint32 isAllocPending;

    SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
    isAllocPending = coreObj->freeQAllocPending;
    RPMessage_queuePut(&coreObj->freeQ, &pMsg->elem);
    SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();

    return isAllocPending;
}

void RPMessage_putEndPtMsg(RPMessage_Struct *epObj, RPMessage_LocalMsg *pMsg)
{
    SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
    RPMessage_queuePut(&epObj->endPtQ, &pMsg->elem);
    SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();

    Cdd_Ipc_Mutex_resourceUnlock(&epObj->newEndPtMsgSem);
}

sint32 RPMessage_getEndPtMsg(RPMessage_Struct *epObj, RPMessage_LocalMsg **pMsg, uint32 timeout)
{
    uint32  tryLoop    = 0U;
    sint32  status     = MCAL_SystemP_TIMEOUT;
    uint32  startTicks = 0U, startTime = 0U;
    boolean done = FALSE;

    Mcal_GetCycleCounterValue(&startTime);

    do
    {
        SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
        *pMsg = (RPMessage_LocalMsg *)RPMessage_queueGet(&epObj->endPtQ);
        SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();

        if (*pMsg == NULL_PTR)
        {
            Mcal_GetCycleCounterValue(&startTicks);

            tryLoop = RPMessage_getEndPtMsg_mutexResourceTryLock(epObj, &status, tryLoop, startTicks, timeout);
            if (tryLoop != 1U)
            {
                done = RPMessage_getEndPtMsg_timeoutCheck(epObj, &status, done, startTime, timeout);
            }
        }
        else
        {
            status = MCAL_SystemP_SUCCESS;
            done   = TRUE;
        }
    } while (done == FALSE);

    return status;
}

/* handle one new received message from vring */
void RPMessage_lld_recvHandler(RPMessageLLD_Handle hRpMsg, uint32 remoteCoreId, uint32 timeout)
{
    uint16              vringBufId = 0U;
    sint32              status     = 0;
    RPMessage_LocalMsg *pMsg;

    /* get a free message pointer to hold vring buf info
     * if no free message pointer then dont remove from vring
     */
    pMsg = RPMessage_allocEndPtMsg(&hRpMsg->coreObj[remoteCoreId], remoteCoreId);
    if (pMsg != NULL_PTR)
    {
        status = RPMessage_vringGetFullRxBuf(hRpMsg, (uint16)remoteCoreId, &vringBufId);
        if (status == MCAL_SystemP_SUCCESS)
        {
            /* message in vring, extract it and copy info to message pointer and put in end point Q
             */
            uint8            *vringBufAddr = RPMessage_vringGetRxBufAddr(hRpMsg, (uint16)remoteCoreId, vringBufId);
            RPMessage_Header *header       = (RPMessage_Header *)vringBufAddr;
            uint16            localEndPt   = (uint16)header->dstEndPt;

            status = MCAL_SystemP_FAILURE;
            status = RPMessage_lld_recvHandlerEndPtCheck(hRpMsg, pMsg, localEndPt, vringBufAddr, header, remoteCoreId,
                                                         status, vringBufId, timeout);
        }
        if (status != MCAL_SystemP_SUCCESS)
        {
            /* no message in vring or invalid vring message header or invalid endpt
             * or no object registered for local end pt, so no need handle the message pointer,
             * free it
             */
            RPMessage_freeEndPtMsg(&hRpMsg->coreObj[remoteCoreId], (uint16)remoteCoreId, pMsg);
        }
    }
}

void RPMessage_notifyCallback(void *ipcNotifyHandle, uint32 remoteCoreId, uint16 localClientId, uint32 msgValue,
                              uint32 timeout, sint32 crcStatus, void *args)
{
    if (NULL_PTR != args)
    {
        RPMessageLLD_Handle hRpMsg = (RPMessageLLD_Handle)args;

        if ((hRpMsg->isCoreEnable[remoteCoreId] != 0U) && (hRpMsg->isCoreInitialized[remoteCoreId] != 0U))
        {
            uint16 rxMsgValue = RPMESSAGE_MSG_VRING_NEW_FULL;

            RPMessage_notify_Callback(hRpMsg, remoteCoreId, msgValue, timeout, rxMsgValue);
        }
    }
}

sint32 RPMessage_lld_send(RPMessageLLD_Handle hRpMsg, void *data, uint16 dataLen, uint16 remoteCoreId,
                          uint16 remoteEndPt, uint16 localEndPt, uint32 timeout)
{
    sint32 status = MCAL_SystemP_FAILURE;

    if (hRpMsg != NULL_PTR)
    {
        if ((remoteCoreId < MCAL_CSL_CORE_ID_MAX) && (hRpMsg->isCoreEnable[remoteCoreId] != 0U) && (data != NULL_PTR) &&
            (dataLen != 0U))
        {
            uint16 vringBufId;
            status = RPMessage_vringGetEmptyTxBuf(hRpMsg, remoteCoreId, &vringBufId, timeout);
            if (status == MCAL_SystemP_SUCCESS)
            {
                status = RPMessage_lldSend_vringPutFullTxBuf(hRpMsg, remoteCoreId, vringBufId, dataLen, remoteEndPt,
                                                             localEndPt, data, timeout, status);
            }
            else
            {
                /*Do Nothing*/;
            }
        }
        else
        {
            /*Do Nothing*/;
        }
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }
    return status;
}

sint32 RPMessage_lld_recv(RPMessageLLD_Handle hRpMsg, RPMessage_EpObject *epObject, void *data, uint16 *dataLen,
                          uint16 *remoteCoreId, uint16 *remoteEndPt, uint32 timeout)
{
    sint32            status = MCAL_SystemP_FAILURE;
    RPMessage_Struct *epObj;

    if ((hRpMsg != NULL_PTR) && (epObject != NULL_PTR))
    {
        epObj = (RPMessage_Struct *)epObject;
        if ((data != NULL_PTR) && (dataLen != NULL_PTR) && (remoteCoreId != NULL_PTR) && (remoteEndPt != NULL_PTR) &&
            (epObj->recvCallback == NULL_PTR)) /* i.e non-callback mode */

        {
            RPMessage_LocalMsg *pMsg;

            status = RPMessage_getEndPtMsg(epObj, &pMsg, timeout);
            if ((status == MCAL_SystemP_SUCCESS) && (pMsg != NULL_PTR))
            {
                uint32            isAllocPending = 0U;
                uint16            vringBufId     = pMsg->vringBufId;
                uint8            *vringBufAddr   = RPMessage_vringGetRxBufAddr(hRpMsg, pMsg->remoteCoreId, vringBufId);
                RPMessage_Header *header         = (RPMessage_Header *)vringBufAddr;

                *remoteCoreId = pMsg->remoteCoreId;
                *remoteEndPt  = (uint16)header->srcEndPt;
                RPMessage_lld_recvdataLenCheck(header, dataLen);
                memcpy((void *)data, (void *)&vringBufAddr[sizeof(RPMessage_Header)], (uint32)*dataLen);
#if (CDD_IPC_CRC_ENABLE == STD_ON)
                {
                    uint16 crc;
                    status = hRpMsg->hRpMsgInit->hIpcNotify->hIpcNotifyInit->Cdd_Ipc_CrcHookFunc(
                        (uint8 *)data, *dataLen, CDD_IPC_RPMESSAGE_CRC_SIZE, &crc);

                    if (header->flags != crc)
                    {
                        status = MCAL_SystemP_FAILURE;
                    }
                }
#endif
                if (status == MCAL_SystemP_SUCCESS)
                {
                    status = RPMessage_vringPutEmptyRxBuf(hRpMsg, *remoteCoreId, vringBufId, timeout);
                    if (status == MCAL_SystemP_SUCCESS)
                    {
                        isAllocPending = RPMessage_freeEndPtMsg(&hRpMsg->coreObj[*remoteCoreId], *remoteCoreId, pMsg);
                        RPMessage_lld_recv_Notify_Callback(hRpMsg, remoteCoreId, timeout, isAllocPending);
                    }
                }
            }
            else
            {
                status = RPMessage_lld_recv_statusCheck(status);
            }
        }
        else
        {
            /*Do Nothing*/;
        }
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }
    return status;
}

Std_ReturnType RPMessage_lld_construct(RPMessageLLD_Handle hRpMsg, RPMessage_EpObject *epObject,
                                       const RPMessage_CreateParams *createParam)
{
    Std_ReturnType    status = E_NOT_OK;
    RPMessage_Struct *epObj;

    if ((hRpMsg != NULL_PTR) && (epObject != NULL_PTR) && (createParam != NULL_PTR))
    {
        epObj = (RPMessage_Struct *)epObject;

        if ((createParam->localEndPt < RPMESSAGE_MAX_LOCAL_ENDPT) &&
            (hRpMsg->localEndPtObj[createParam->localEndPt] == NULL_PTR))
        {
            epObj->localEndPt             = createParam->localEndPt;
            epObj->recvCallback           = createParam->recvCallback;
            epObj->recvCallbackArgs       = createParam->recvCallbackArgs;
            epObj->recvNotifyCallback     = createParam->recvNotifyCallback;
            epObj->recvNotifyCallbackArgs = createParam->recvNotifyCallbackArgs;
            epObj->doRecvUnblock          = 0;
            RPMessage_queueReset(&epObj->endPtQ);
            epObj->newEndPtMsgSem = CDD_IPC_MUTEX_ARM_LOCKED;

            hRpMsg->localEndPtObj[createParam->localEndPt] = epObj;

            status = E_OK;
        }
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

void RPMessage_lld_destruct(RPMessageLLD_Handle hRpMsg, RPMessage_EpObject *epObject)
{
    RPMessage_Struct *epObj = (RPMessage_Struct *)epObject;

    if ((epObj->localEndPt < RPMESSAGE_MAX_LOCAL_ENDPT) && (hRpMsg->localEndPtObj[epObj->localEndPt] != NULL_PTR))
    {
        hRpMsg->localEndPtObj[epObj->localEndPt] = (RPMessage_Struct *)NULL_PTR;

        epObj->localEndPt       = RPMESSAGE_MAX_LOCAL_ENDPT;
        epObj->recvCallback     = (RPMessage_lld_recvCallback)NULL_PTR;
        epObj->recvCallbackArgs = NULL_PTR;
        epObj->doRecvUnblock    = 0U;
        RPMessage_queueReset(&epObj->endPtQ);
    }
}

void RPMessage_lld_CreateParams_init(RPMessage_CreateParams *params)
{
    params->localEndPt             = RPMESSAGE_MAX_LOCAL_ENDPT;
    params->recvCallback           = (RPMessage_lld_recvCallback)NULL_PTR;
    params->recvCallbackArgs       = NULL_PTR;
    params->recvNotifyCallback     = (RPMessage_lld_recvNotifyCallback)NULL_PTR;
    params->recvNotifyCallbackArgs = NULL_PTR;
}

sint32 RPMessage_coreInit(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId)
{
    sint32          status  = MCAL_SystemP_SUCCESS;
    RPMessage_Core *coreObj = &hRpMsg->coreObj[remoteCoreId];
    uint16          elemId;

    coreObj->newEmptyVringBufSem = CDD_IPC_MUTEX_ARM_LOCKED;
    coreObj->freeQAllocPending   = 0U;
    RPMessage_queueReset(&coreObj->freeQ);
    for (elemId = 0U; elemId < RPMESSAGE_MAX_LOCAL_MSG_OBJ; elemId++)
    {
        RPMessage_queuePut(&coreObj->freeQ, &coreObj->localMsgObj[elemId].elem);
    }
    /* Linux VRINGs we will init later inside RPMessage_waitForLinuxReady() */
    if ((hRpMsg->isCoreEnable[remoteCoreId] != 0U) && (!(RPMessage_isLinuxCore(hRpMsg, remoteCoreId) != 0U)))
    {
        /* reset RX ring */
        RPMessage_vringReset(hRpMsg, remoteCoreId, 0U);
        /* reset TX ring */
        RPMessage_vringReset(hRpMsg, remoteCoreId, 1U);

        /* mark core data structure as initialized, now we can handle interrupts */
        hRpMsg->isCoreInitialized[remoteCoreId] = 1U;
    }
    return status;
}

void RPMessage_coreDeInit(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId)
{
    RPMessage_Core *coreObj = &hRpMsg->coreObj[remoteCoreId];

    coreObj->freeQAllocPending = 0U;
    RPMessage_queueReset(&coreObj->freeQ);
}

void RPMessage_controlEndPtHandler(void *rpMsgHandle, RPMessage_EpObject *epObj, void *arg, void *data, uint16 dataLen,
                                   sint32 crcStatus, uint16 remoteCoreId, uint16 remoteEndPt)
{
    (void)crcStatus;
    (void)epObj;
    (void)arg;
    RPMessageLLD_Handle hRpMsg = (RPMessageLLD_Handle)rpMsgHandle;

    if ((hRpMsg->controlEndPtCallback) != NULL_PTR)
    {
        /* check if message is of correct size */
        if (dataLen == sizeof(RPMessage_AnnounceMsg))
        {
            /* invoke user callback */
            RPMessage_AnnounceMsg *pMsg = (RPMessage_AnnounceMsg *)data;

            hRpMsg->controlEndPtCallback(hRpMsg->controlEndPtCallbackArgs, remoteCoreId, pMsg->remoteEndPt, pMsg->name);
        }
    }
}

uint32 RPMessage_controlEndPtInit(RPMessageLLD_Handle hRpMsg)
{
    RPMessage_CreateParams createPrms;
    uint32                 status;

    RPMessage_lld_CreateParams_init(&createPrms);
    createPrms.localEndPt   = RPMESSAGE_CTRL_ENDPOINT_ID;
    createPrms.recvCallback = RPMessage_controlEndPtHandler;
    status                  = (uint32)RPMessage_lld_construct(hRpMsg, &hRpMsg->controlEndPtObj, &createPrms);

    return status;
}

void RPMessage_controlEndPtDeInit(RPMessageLLD_Handle hRpMsg)
{
    RPMessage_lld_destruct(hRpMsg, &hRpMsg->controlEndPtObj);
}

uint32 RPMessage_isLinuxCore(RPMessageLLD_Handle hRpMsg, uint16 coreId)
{
    uint32 isLinuxCore = 0U;

    if ((coreId == hRpMsg->linuxCoreId) && (hRpMsg->linuxResourceTable))
    {
        isLinuxCore = 1U;
    }
    return isLinuxCore;
}

sint32 RPMessage_lld_init(RPMessageLLD_Handle hRpMsg)
{
    sint32                  status = MCAL_SystemP_SUCCESS;
    RPMessageLLD_InitHandle hRpMsgInit;

    if ((hRpMsg != NULL_PTR) && (hRpMsg->hRpMsgInit != NULL_PTR))
    {
        hRpMsgInit = hRpMsg->hRpMsgInit;
        status     = RPMessage_lld_init_lldInitParamsCheck(hRpMsg, hRpMsgInit, status);
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }
    return status;
}

sint32 RPMessage_lld_deInit(RPMessageLLD_Handle hRpMsg)
{
    sint32 status = MCAL_SystemP_SUCCESS;
    uint16 coreId;

    if (hRpMsg != NULL_PTR)
    {
        IpcNotify_lld_unregisterClient(hRpMsg->hRpMsgInit->hIpcNotify, IPC_NOTIFY_CLIENT_ID_RPMSG);

        RPMessage_controlEndPtDeInit(hRpMsg);

        for (coreId = 0U; coreId < MCAL_CSL_CORE_ID_MAX; coreId++)
        {
            RPMessage_coreDeInit(hRpMsg, coreId);
        }
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    return status;
}

static inline sint32 RPMessage_lld_init_Copy_Values(RPMessageLLD_Handle hRpMsg)
{
    sint32                  status = MCAL_SystemP_SUCCESS;
    uint16                  localEndPtId;
    RPMessageLLD_InitHandle hRpMsgInit;
    if ((hRpMsg != NULL_PTR) && (hRpMsg->hRpMsgInit != NULL_PTR))
    {
        hRpMsgInit                       = hRpMsg->hRpMsgInit;
        hRpMsg->selfCoreId               = (uint16)IpcNotify_lld_getSelfCoreId(hRpMsgInit->hIpcNotify);
        hRpMsg->controlEndPtCallback     = (RPMessage_ControlEndPtCallback)NULL_PTR;
        hRpMsg->controlEndPtCallbackArgs = NULL_PTR;
        hRpMsg->linuxResourceTable       = hRpMsgInit->linuxResourceTable;
        hRpMsg->linuxCoreId              = hRpMsgInit->linuxCoreId;

        for (localEndPtId = 0U; localEndPtId < RPMESSAGE_MAX_LOCAL_ENDPT; localEndPtId++)
        {
            hRpMsg->localEndPtObj[localEndPtId] = (RPMessage_Struct *)NULL_PTR;
        }

        status = RPMessage_lld_init_Enable_Core(hRpMsg);
    }
    return status;
}

static inline sint32 RPMessage_lld_init_Enable_Core(RPMessageLLD_Handle hRpMsg)
{
    uint32                  coreInit_value = 0U;
    sint32                  status         = 0;
    uint16                  coreId         = 0U;
    RPMessageLLD_InitHandle hRpMsgInit;
    hRpMsgInit = hRpMsg->hRpMsgInit;
    for (coreId = 0U; coreId < MCAL_CSL_CORE_ID_MAX; coreId++)
    {
        /* enable a core for RPMessage only when below is satisifed
         * - valid vring ID is set
         * - not self core ID
         * - IPC Notify with that core is enabled
         */
        hRpMsg->isCoreEnable[coreId]      = 0U;
        hRpMsg->isCoreInitialized[coreId] = 0U;
        if ((hRpMsgInit->vringTxBaseAddr[coreId] != RPMESSAGE_VRING_ADDR_INVALID) &&
            (hRpMsgInit->vringRxBaseAddr[coreId] != RPMESSAGE_VRING_ADDR_INVALID) && (coreId != hRpMsg->selfCoreId) &&
            ((IpcNotify_lld_isCoreEnabled(hRpMsgInit->hIpcNotify, coreId)) != 0U))

        {
            hRpMsg->isCoreEnable[coreId] = 1U;
        }
        if ((RPMessage_isLinuxCore(hRpMsg, coreId) != 0U) &&
            (IpcNotify_lld_isCoreEnabled(hRpMsgInit->hIpcNotify, coreId) != 0U))
        {
            hRpMsg->isCoreEnable[coreId] = 1U;
        }
    }
    for (coreId = 0U; coreId < MCAL_CSL_CORE_ID_MAX; coreId++)
    {
        coreInit_value |= (uint32)RPMessage_coreInit(hRpMsg, coreId);
    }

    /* create control end point */
    coreInit_value |= (uint32)RPMessage_controlEndPtInit(hRpMsg);

    coreInit_value |= (uint32)IpcNotify_lld_registerClient(hRpMsgInit->hIpcNotify, IPC_NOTIFY_CLIENT_ID_RPMSG,
                                                           RPMessage_notifyCallback, hRpMsg);
    status          = (sint32)coreInit_value;

    return status;
}

static sint32 RPMessage_lld_init_lldInitParamsCheck(RPMessageLLD_Handle hRpMsg, RPMessageLLD_InitHandle hRpMsgInit,
                                                    sint32 value)
{
    sint32 paramValue = value;
    paramValue        = RPMessage_lld_ParamsCheck(hRpMsgInit, paramValue);
    sint32 status     = paramValue;
    MCAL_LLD_PARAMS_CHECK(hRpMsgInit->vringMsgSize != 0U);
    MCAL_LLD_PARAMS_CHECK(hRpMsgInit->linuxCoreId < MCAL_CSL_CORE_ID_MAX);
    if (status == MCAL_SystemP_SUCCESS)
    {
        status = RPMessage_lld_init_Copy_Values(hRpMsg);
    }

    return status;
}

static sint32 RPMessage_lld_ParamsCheck(RPMessageLLD_InitHandle hRpMsgInit, sint32 value)
{
    sint32 status = value;
    MCAL_LLD_PARAMS_CHECK(hRpMsgInit->hIpcNotify != NULL_PTR);
    MCAL_LLD_PARAMS_CHECK(hRpMsgInit->vringSize != 0U);
    MCAL_LLD_PARAMS_CHECK(hRpMsgInit->vringNumBuf != 0U);
    return status;
}

static boolean RPMessage_getEndPtMsg_timeoutCheck(RPMessage_Struct *epObj, sint32 *status, boolean done,
                                                  uint32 startTime, uint32 timeout)
{
    uint32  tempTime, endTime;
    boolean isDone = done;

    if (*status == MCAL_SystemP_TIMEOUT)
    {
        isDone = TRUE;
    }
    if ((*status == MCAL_SystemP_SUCCESS) && (epObj->doRecvUnblock != 0U))
    {
        *status = MCAL_SystemP_TIMEOUT;
        isDone  = TRUE;
    }

    tempTime = startTime;
    Mcal_GetElapsedCycleCountValue(&tempTime, &endTime);

    if (endTime > timeout)
    {
        *status = MCAL_SystemP_TIMEOUT;
        isDone  = TRUE;
    }

    return isDone;
}

static sint32 RPMessage_lld_recvHandlerEndPtCheck(RPMessageLLD_Handle hRpMsg, RPMessage_LocalMsg *pMsg,
                                                  uint16 localEndPt, uint8 *vringBufAddr, RPMessage_Header *header,
                                                  uint32 remoteCoreId, sint32 status, uint16 vringBufId, uint32 timeout)
{
    sint32 retVal = status;
    if (localEndPt < RPMESSAGE_MAX_LOCAL_ENDPT)
    {
        RPMessage_Struct *epObj = hRpMsg->localEndPtObj[localEndPt];
        if (epObj != NULL_PTR)
        {
            if (epObj->recvCallback != NULL_PTR)
            {
                sint32 crcStatus = MCAL_SystemP_SUCCESS;
#if (CDD_IPC_CRC_ENABLE == STD_ON)
                {
                    uint16 crc;

                    crcStatus = hRpMsg->hRpMsgInit->hIpcNotify->hIpcNotifyInit->Cdd_Ipc_CrcHookFunc(
                        (uint8 *)(&vringBufAddr[sizeof(RPMessage_Header)]), header->dataLen, CDD_IPC_RPMESSAGE_CRC_SIZE,
                        &crc);

                    if (header->flags != crc)
                    {
                        crcStatus = MCAL_SystemP_FAILURE;
                    }
                }
#endif
                /* recv messages handled in callback mode */
                epObj->recvCallback(hRpMsg, (RPMessage_EpObject *)epObj, epObj->recvCallbackArgs,
                                    &vringBufAddr[sizeof(RPMessage_Header)], header->dataLen, crcStatus,
                                    (uint16)remoteCoreId, (uint16)header->srcEndPt);

                /* pMsg is not used, free it */
                RPMessage_freeEndPtMsg(&hRpMsg->coreObj[remoteCoreId], (uint16)remoteCoreId, pMsg);
                /* done using vring buf, free it */
                retVal = RPMessage_vringPutEmptyRxBuf(hRpMsg, (uint16)remoteCoreId, vringBufId, timeout);
            }
            else
            {
                /* recv messages handled in non-callback mode */
                pMsg->remoteCoreId = (uint16)remoteCoreId;
                pMsg->vringBufId   = vringBufId;
                RPMessage_putEndPtMsg(epObj, pMsg);
                retVal = MCAL_SystemP_SUCCESS;

                RPMessage_lld_recvHandlerEndPtCheck_recvNotifyCallback(hRpMsg, epObj);
            }
        }
    }
    if (retVal == MCAL_SystemP_SUCCESS)
    {
        retVal = RPMessage_lld_recvHandlerEndPtCheck_EmptyRxBuf(hRpMsg, retVal, remoteCoreId, vringBufId, timeout);
    }

    return retVal;
}

static void RPMessage_notify_Callback(RPMessageLLD_Handle hRpMsg, uint32 remoteCoreId, uint32 msgValue, uint32 timeout,
                                      uint16 rxMsgValue)
{
    uint16 rxValue = rxMsgValue;
    if ((RPMessage_isLinuxCore(hRpMsg, (uint16)remoteCoreId)) != 0U)
    {
        rxValue = RPMESSAGE_LINUX_RX_VRING_ID; /* In linux, we get RX VRING ID, which is 1 in linux */
    }
    if (msgValue == rxValue)
    { /* check full ring */
        while ((RPMessage_vringIsFullRxBuf(hRpMsg, (uint16)remoteCoreId)) == 1U)
        {
            RPMessage_lld_recvHandler(hRpMsg, remoteCoreId, timeout);
        }
    }
    else
    { /* check empty ring */

        /* check if there is any new empty buf, if yes then post semaphore to wake up any waiting
         * threads */
        RPMessage_vringCheckEmptyTxBuf(hRpMsg, (uint16)remoteCoreId);
    }
}

static sint32 RPMessage_lldSend_vringPutFullTxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 vringBufId,
                                                  uint16 dataLen, uint16 remoteEndPt, uint16 localEndPt, void *data,
                                                  uint32 timeout, sint32 status)
{
    uint16            dataLength   = dataLen;
    sint32            retVal       = status;
    uint8            *vringBufAddr = RPMessage_vringGetTxBufAddr(hRpMsg, remoteCoreId, vringBufId);
    uint16            vringBufLen  = (uint16)RPMessage_vringGetTxBufLen(hRpMsg, remoteCoreId, vringBufId);
    RPMessage_Header *header       = (RPMessage_Header *)vringBufAddr;

    if (dataLen > (vringBufLen - sizeof(RPMessage_Header)))
    {
        dataLength = vringBufLen - (uint16)sizeof(RPMessage_Header);
    }

    header->srcEndPt  = localEndPt;
    header->dstEndPt  = remoteEndPt;
    header->srcCoreId = hRpMsg->selfCoreId;
    header->flags     = 0U;
#if (CDD_IPC_CRC_ENABLE == STD_ON)
    {
        uint16 crc;
        retVal        = hRpMsg->hRpMsgInit->hIpcNotify->hIpcNotifyInit->Cdd_Ipc_CrcHookFunc((uint8 *)data, dataLen,
                                                                                            CDD_IPC_RPMESSAGE_CRC_SIZE, &crc);
        header->flags = crc;
    }
#else
    {
        header->flags = 0;
    }
#endif

    if (retVal == MCAL_SystemP_SUCCESS)
    {
        header->dataLen = dataLength;
        memcpy((void *)&vringBufAddr[sizeof(RPMessage_Header)], (void *)data, (uint32)dataLength);
        retVal = RPMessage_vringPutFullTxBuf(hRpMsg, remoteCoreId, vringBufId,
                                             dataLength + (uint16)sizeof(RPMessage_Header), timeout);
    }

    return retVal;
}

static uint32 RPMessage_getEndPtMsg_mutexResourceTryLock(RPMessage_Struct *epObj, sint32 *status, uint32 tryLoop,
                                                         uint32 startTicks, uint32 timeout)
{
    uint32 tempTicks, elapsedTicks;
    uint32 tryLoopLocal = tryLoop;
    do
    {
        if (Cdd_Ipc_Mutex_resourceTryLock(&epObj->newEndPtMsgSem) == CDD_IPC_MUTEX_ARM_UNLOCKED)
        {
            tryLoopLocal = 1U;
            *status      = MCAL_SystemP_SUCCESS;
        }
        else
        {
            tempTicks = startTicks;
            Mcal_GetElapsedCycleCountValue(&tempTicks, &elapsedTicks);
        }
    } while ((elapsedTicks < timeout) && (tryLoopLocal == 0U));

    return tryLoopLocal;
}

static void RPMessage_lld_recvdataLenCheck(RPMessage_Header *header, uint16 *dataLen)
{
    if (*dataLen < header->dataLen)
    {
        /*Do Nothing*/;
    }
    else
    {
        *dataLen = header->dataLen;
    }
}
static sint32 RPMessage_lld_recvHandlerEndPtCheck_EmptyRxBuf(RPMessageLLD_Handle hRpMsg, sint32 retVal,
                                                             uint32 remoteCoreId, uint16 vringBufId, uint32 timeout)
{
    sint32 status = MCAL_SystemP_SUCCESS;
    if (retVal != MCAL_SystemP_SUCCESS)
    {
        /* invalid vring message header or invalid endpt
         * or no object registered for local end pt, so no need handle the message pointer,
         * free it
         */
        status = RPMessage_vringPutEmptyRxBuf(hRpMsg, (uint16)remoteCoreId, vringBufId, timeout);
    }

    return status;
}

static void RPMessage_lld_recvHandlerEndPtCheck_recvNotifyCallback(RPMessageLLD_Handle hRpMsg, RPMessage_Struct *epObj)
{
    if (epObj->recvNotifyCallback != NULL_PTR)
    {
        epObj->recvNotifyCallback(hRpMsg, (RPMessage_EpObject *)epObj, epObj->recvNotifyCallbackArgs);
    }
}

static void RPMessage_lld_recv_Notify_Callback(RPMessageLLD_Handle hRpMsg, uint16 *remoteCoreId, uint32 timeout,
                                               uint32 isAllocPending)
{
    if (isAllocPending != 0U)
    { /* if any messages are pending message pointer due to free Q being empty,
       * now there will be atleast one element to handle any pending vring requests.
       * So check vring and handle pending messages if any
       */
        RPMessage_notifyCallback(hRpMsg->hRpMsgInit->hIpcNotify, *remoteCoreId, IPC_NOTIFY_CLIENT_ID_RPMSG,
                                 RPMESSAGE_MSG_VRING_NEW_FULL, timeout, MCAL_SystemP_SUCCESS, NULL_PTR);
    }
}

static sint32 RPMessage_lld_recv_statusCheck(sint32 status)
{
    if (status != MCAL_SystemP_TIMEOUT)
    {
        /*Do Nothing*/;
    }
    return status;
}

#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
