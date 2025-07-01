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

#include <ipc_rpmsg_lld_priv.h>
#include <Cdd_Ipc.h>

/* NOTE:
 * For RTOS to RTOS IPC RPMessage
 *   - AVAIL in vring = EMPTY in ipc rpmsg implementation
 *   - USED in vring = FULL  in ipc rpmsg implementation
 *
 * For Linux to RTOS IPC RPMessage
 * - When doing TX from RTOS
 *   - AVAIL in vring = EMPTY in ipc rpmsg implementation
 *   - USED in vring = FULL  in ipc rpmsg implementation
 * - When doing RX from RTOS
 *   - AVAIL in vring = FULL in ipc rpmsg implementation
 *   - USED in vring = EMTPY  in ipc rpmsg implementation
 *
 * RPMessage_isLinuxCore is used in Rx APIs to switch the meaning when
 * receiving messages from core ID which runs Linux
 */

#define VRING_USED_F_NO_NOTIFY (1U)
static inline void RPMessage_vringPutFullTxBuf_asm(void);
static boolean     RPMessage_vringGetEmptyTxBufTimeOut(sint32 *status, boolean done, uint32 startTime, uint32 tryLoop,
                                                       uint32 timeout);
static uint32 RPMessage_vringGetEmptyTxBuf_mutexResourceTryLock(sint32 *status, RPMessage_Core *coreObj, uint32 tryLoop,
                                                                uint32 startTicks, uint32 startTime, uint32 timeout);
#define CDD_IPC_START_SEC_CODE
#include "Cdd_Ipc_MemMap.h"

sint32 RPMessage_vringGetEmptyTxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 *vringBufId, uint32 timeout)
{
    RPMessage_Core  *coreObj  = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj = &coreObj->vringTxObj;
    uint32           startTicks, startTime;
    uint16           head;
    sint32           status  = MCAL_SystemP_TIMEOUT;
    boolean          done    = FALSE;
    uint32           tryLoop = 0U;
    startTime                = Cdd_Ipc_Clock_getTicks();
    do
    {
        /* There's nothing available */
        if (vringObj->lastAvailIdx == vringObj->avail->idx)
        {
            /* We need to know about added buffers */
            vringObj->used->flags &= (uint16)~VRING_USED_F_NO_NOTIFY;
            sint32 *statusValue    = &status;
            startTicks             = Cdd_Ipc_Clock_getTicks();
            tryLoop = RPMessage_vringGetEmptyTxBuf_mutexResourceTryLock(statusValue, coreObj, tryLoop, startTicks,
                                                                        startTime, timeout);
            sint32 *statusLocal = &status;
            done                = RPMessage_vringGetEmptyTxBufTimeOut(statusLocal, done, startTime, tryLoop, timeout);
        }
        else
        {
            head = vringObj->avail->ring[vringObj->lastAvailIdx % vringObj->vringNumBuf];
            vringObj->lastAvailIdx++;

            *vringBufId = head;
            done        = TRUE;
            status      = MCAL_SystemP_SUCCESS;
        }
    } while (done == FALSE);

    return status;
}

void RPMessage_vringPutFullTxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 vringBufId, uint16 dataLen,
                                 uint32 timeout)
{
    RPMessage_Core         *coreObj  = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring        *vringObj = &coreObj->vringTxObj;
    struct vring_used_elem *used;
    uint32                  txMsgValue = RPMESSAGE_MSG_VRING_NEW_FULL;

    if ((RPMessage_isLinuxCore(hRpMsg, remoteCoreId)) != 0U)
    {
        /* for linux we need to send the TX VRING ID in the mailbox message */
        txMsgValue = RPMESSAGE_LINUX_TX_VRING_ID;
    }

    used      = &vringObj->used->ring[vringObj->used->idx % vringObj->vringNumBuf];
    used->id  = vringBufId;
    used->len = dataLen;
    vringObj->used->idx++;
    RPMessage_vringPutFullTxBuf_asm();
    IpcNotify_lld_sendMsg(hRpMsg->hRpMsgInit->hIpcNotify, remoteCoreId, IPC_NOTIFY_CLIENT_ID_RPMSG, txMsgValue,
                          1 /* wait for message to be posted */, timeout);
}

void RPMessage_vringCheckEmptyTxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId)
{
    RPMessage_Core  *coreObj       = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj      = &coreObj->vringTxObj;
    uint32           isNewEmptyBuf = 1U;

    if (vringObj->lastAvailIdx == vringObj->avail->idx)
    {
        isNewEmptyBuf = 0U;
    }

    if (isNewEmptyBuf != 0U)
    {
        Cdd_Ipc_Mutex_resourceUnlock(&coreObj->newEmptyVringBufSem);
    }
}

uint8 *RPMessage_vringGetTxBufAddr(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 vringBufId)
{
    RPMessage_Core  *coreObj  = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj = &coreObj->vringTxObj;

    return (uint8 *)vringObj->desc[vringBufId].addr;
}

uint32 RPMessage_vringGetTxBufLen(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 vringBufId)
{
    RPMessage_Core  *coreObj  = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj = &coreObj->vringTxObj;

    return vringObj->desc[vringBufId].len;
}

sint32 RPMessage_vringGetFullRxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 *vringBufId)
{
    RPMessage_Core  *coreObj  = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj = &coreObj->vringRxObj;
    uint16           head;
    sint32           status = MCAL_SystemP_TIMEOUT;

    if ((RPMessage_isLinuxCore(hRpMsg, remoteCoreId)) != 0U)
    {
        /* There's nothing available */
        if (vringObj->lastAvailIdx != vringObj->avail->idx)
        {
            head = vringObj->avail->ring[vringObj->lastAvailIdx % vringObj->vringNumBuf];
            vringObj->lastAvailIdx++;

            *vringBufId = head;
            status      = MCAL_SystemP_SUCCESS;
        }
        else
        {
            vringObj->used->flags &= (uint16)~VRING_USED_F_NO_NOTIFY;
        }
    }
    else
    {
        if (vringObj->lastUsedIdx != vringObj->used->idx)
        {
            head = (uint16)(vringObj->used->ring[vringObj->lastUsedIdx % vringObj->vringNumBuf].id);
            vringObj->lastUsedIdx++;

            *vringBufId = head;

            status = MCAL_SystemP_SUCCESS;
        }
    }

    return status;
}

void RPMessage_vringPutEmptyRxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 vringBufId, uint32 timeout)
{
    RPMessage_Core  *coreObj  = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj = &coreObj->vringRxObj;
    uint32           rxMsgValue;

    if ((RPMessage_isLinuxCore(hRpMsg, remoteCoreId)) != 0U)
    {
        struct vring_used_elem *used;

        used      = &vringObj->used->ring[vringObj->used->idx % vringObj->vringNumBuf];
        used->id  = vringBufId;
        used->len = vringObj->desc[vringBufId].len;
        vringObj->used->idx++;

        rxMsgValue = RPMESSAGE_LINUX_RX_VRING_ID; /* in case of linux this should be RX VRING ID */
    }
    else
    {
        uint16 avail;

        avail                        = (uint16)(vringObj->avail->idx % vringObj->vringNumBuf);
        vringObj->avail->ring[avail] = vringBufId;
        vringObj->avail->idx++;

        rxMsgValue = RPMESSAGE_MSG_VRING_NEW_EMPTY;
    }

    IpcNotify_mailbox_asm();

    IpcNotify_lld_sendMsg(hRpMsg->hRpMsgInit->hIpcNotify, remoteCoreId, IPC_NOTIFY_CLIENT_ID_RPMSG, rxMsgValue,
                          1U /* wait for message to be posted */, timeout);
}

uint32 RPMessage_vringIsFullRxBuf(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId)
{
    RPMessage_Core  *coreObj      = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj     = &coreObj->vringRxObj;
    uint32           isNewFullBuf = 1;

    if ((RPMessage_isLinuxCore(hRpMsg, remoteCoreId)) != 0U)
    {
        if (vringObj->lastAvailIdx == vringObj->avail->idx)
        {
            isNewFullBuf = 0;
        }
    }
    else
    {
        if (vringObj->lastUsedIdx == vringObj->used->idx)
        {
            isNewFullBuf = 0;
        }
    }

    return isNewFullBuf;
}

uint8 *RPMessage_vringGetRxBufAddr(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 vringBufId)
{
    RPMessage_Core  *coreObj  = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring *vringObj = &coreObj->vringRxObj;

    return (uint8 *)vringObj->desc[vringBufId].addr;
}

void RPMessage_vringResetInternal(RPMessage_Vring *vringObj, uint16 numBuf, uint16 msgSize, uintptr_t vringBaseAddr,
                                  uint32 offset_desc, uint32 offset_avail, uint32 offset_used, uint32 offset_buf,
                                  uint32 isTx)
{
    uint8 *bufAddr;
    uint16 bufId;

    /* intialize locally visible variables */
    vringObj->lastUsedIdx  = 0U;
    vringObj->lastAvailIdx = 0U;
    vringObj->vringNumBuf  = numBuf;

    /* set address to vring descriptors, avail Q, used Q, message buffers */
    vringObj->desc        = (struct vring_desc *)(vringBaseAddr + offset_desc);
    vringObj->avail       = (struct vring_avail *)(vringBaseAddr + offset_avail);
    vringObj->used        = (struct vring_used *)(vringBaseAddr + offset_used);
    vringObj->bufBaseAddr = (uint8 *)(vringBaseAddr + offset_buf);

    /* only initialize TX vring, RX vring is initialized by the remote core */
    if (isTx != 0U)
    {
        /* initialize descriptors with message buffer address and max len */
        bufAddr = vringObj->bufBaseAddr;
        for (bufId = 0U; bufId < numBuf; bufId++)
        {
            vringObj->desc[bufId].addr     = (uint32)bufAddr;
            vringObj->desc[bufId].padding  = 0U;
            vringObj->desc[bufId].len      = (uint32)msgSize;
            vringObj->desc[bufId].flags    = 0U;
            vringObj->desc[bufId].next     = 0U;
            bufAddr                       += msgSize;
        }
        /* initialize avail Q and add all buffers to avail Q */
        vringObj->avail->idx   = 0;
        vringObj->avail->flags = 0;
        for (bufId = 0; bufId < numBuf; bufId++)
        {
            vringObj->avail->ring[bufId] = bufId;
            vringObj->avail->idx++;
        }
        /* initialize used Q */
        vringObj->used->idx   = 0;
        vringObj->used->flags = 0;
        for (bufId = 0; bufId < numBuf; bufId++)
        {
            vringObj->used->ring[bufId].id  = 0;
            vringObj->used->ring[bufId].len = 0;
        }
    }
}

void RPMessage_vringReset(RPMessageLLD_Handle hRpMsg, uint16 remoteCoreId, uint16 isTx)
{
    RPMessage_Core         *coreObj = &hRpMsg->coreObj[remoteCoreId];
    RPMessage_Vring        *vringObj;
    uintptr_t               vringBaseAddr;
    uint32                  offset_desc, offset_avail, offset_used, offset_buf;
    uint32                  align;  // vringSize;
    uint16                  numBuf, msgSize;
    RPMessageLLD_InitHandle hRpMsgInit = hRpMsg->hRpMsgInit;

    if (isTx != 0U)
    {
        vringObj      = &coreObj->vringTxObj;
        vringBaseAddr = hRpMsgInit->vringTxBaseAddr[remoteCoreId];
    }
    else
    {
        vringObj      = &coreObj->vringRxObj;
        vringBaseAddr = hRpMsgInit->vringRxBaseAddr[remoteCoreId];
    }
    align   = sizeof(uint32);
    numBuf  = hRpMsgInit->vringNumBuf;
    msgSize = hRpMsgInit->vringMsgSize;

    /* get vring size, including descriptors, avail Q, used Q, message buffers and alignment */

    /* check if vring ID is within limits of the memory available for vring */

    /* calculate offset to vring descriptors, avail Q, used Q, message buffers
     * relative to vringBaseAddr
     */
    offset_desc  = 0U;
    offset_avail = (offset_desc + (sizeof(struct vring_desc) * numBuf));
    offset_used  = (offset_avail + RPMessage_align(((uint32)sizeof(uint16) * ((uint32)2U + (uint32)numBuf)), align));
    offset_buf =
        (offset_used) + RPMessage_align(((sizeof(uint16) * 2U) + (sizeof(struct vring_used_elem) * numBuf)), align);

    RPMessage_vringResetInternal(vringObj, numBuf, msgSize, vringBaseAddr, offset_desc, offset_avail, offset_used,
                                 offset_buf, isTx);
}

static inline void RPMessage_vringPutFullTxBuf_asm(void)
{
#if defined(__aarch64__) || defined(__arm__)
    __asm__ __volatile__(
        "dsb sy"
        "\n\t"
        :
        :
        : "memory");
    __asm__ __volatile__(
        "isb sy"
        "\n\t"
        :
        :
        : "memory");
#endif
#if defined(_TMS320C6X)
    _mfence();
    _mfence();
#endif
}

static boolean RPMessage_vringGetEmptyTxBufTimeOut(sint32 *status, boolean done, uint32 startTime, uint32 tryLoop,
                                                   uint32 timeout)
{
    uint32  endTime, tempTime;
    boolean isDone = done;
    if (*status == MCAL_SystemP_TIMEOUT)
    {
        isDone = TRUE;
    }
    if (tryLoop == 1U)
    {
        tempTime = startTime;
        GetElapsedValue(CDD_IPC_OS_COUNTER_ID, &tempTime, &endTime);
        if (endTime > timeout)
        {
            *status = MCAL_SystemP_TIMEOUT;
            isDone  = TRUE;
        }
    }
    return isDone;
}

static uint32 RPMessage_vringGetEmptyTxBuf_mutexResourceTryLock(sint32 *status, RPMessage_Core *coreObj, uint32 tryLoop,
                                                                uint32 startTicks, uint32 startTime, uint32 timeout)
{
    uint32 tempTicks, elapsedTicks;
    uint32 tryLoopLocal = tryLoop;

    do
    {
        if (Cdd_Ipc_Mutex_resourceTryLock(&coreObj->newEmptyVringBufSem) == CDD_IPC_MUTEX_ARM_UNLOCKED)
        {
            tryLoopLocal = 1U;
            *status      = MCAL_SystemP_SUCCESS;
        }
        tempTicks = startTicks;
        GetElapsedValue(CDD_IPC_OS_COUNTER_ID, &tempTicks, &elapsedTicks);
    } while ((elapsedTicks < timeout) && (tryLoopLocal == 0U));

    return tryLoopLocal;
}
#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
