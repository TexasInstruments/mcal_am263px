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
#include "ipc_notify_v1_lld.h"
#include "ipc_notify_v1_cfg_lld.h"
#include "Cdd_Ipc.h" /* Included to bring the Clock related functions. */
#include "string.h"
#include "sys_pmu.h"

extern IpcNotify_Object          CddIpc_NotifyObject;
extern IpcNotify_InitObject      CddIpcInit_Config;
extern IpcNotifyUtils_Handle     CddIpc_NotifyUtilsHandl;
extern IpcNotifyUtils_Object     CddIpc_NotifyUtilsObject;
extern IpcNotifyUtils_InitObject CddIpc_NotifyUtilsInitObject;

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
extern RPMessageLLD_Object     Cdd_RPMessageObj;
extern RPMessageLLD_InitObject CddIpc_RPMessageInitObj;
extern RPMessage_EpObject      Cdd_AckReplyMsgObject[CDD_IPC_LOCALEP_COUNT];
#endif

extern VAR(Cdd_IpcStatusType, CDD_VAR_ZERO_INIT) CddIpc_DrvStatus;
extern IpcNotify_Handle CddIpc_NotifyHandle;

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
extern RPMessageLLD_Handle CddIpc_RPMsgHandle;
#endif

static inline void IpcNotify_getWriteMailbox(uint32 selfCoreId, uint32 remoteCoreId, uint32 *mailboxBaseAddr,
                                             uint32 *intrBitPos, IpcNotify_SwQueue **swQ);
static void        IpcNotify_lld_init_clearIntOn(IpcNotify_Handle hIpcNotify, uint32 selfCoreId);
static sint32 IpcNotify_lld_sendMsg_mailboxWrite(IpcNotify_Handle hIpcNotify, const IpcNotify_MsgParams *msgParams);
static void   IpcNotify_lld_isrCrcCheck(sint32 status, uint32 value, IpcNotify_Handle hIpcNotify,
                                        IpcNotify_InterruptConfig *pInterruptConfig, uint32 core);

#define CDD_IPC_START_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
static inline void IpcNotify_getWriteMailbox(uint32 selfCoreId, uint32 remoteCoreId, uint32 *mailboxBaseAddr,
                                             uint32 *intrBitPos, IpcNotify_SwQueue **swQ)

{
    IpcNotify_MailboxConfig *pMailboxConfig;

    pMailboxConfig = IpcNotifyCfg_getMailboxConfig(selfCoreId, remoteCoreId);

    *mailboxBaseAddr = pMailboxConfig->writeDoneMailboxBaseAddr;
    *intrBitPos      = pMailboxConfig->intrBitPos;
    *swQ             = pMailboxConfig->swQ;
}

static inline void IpcNotify_getReadMailbox(uint32 selfCoreId, uint32 *mailboxBaseAddr)
{
    IpcNotify_MailboxConfig *pMailboxConfig;

    pMailboxConfig = IpcNotifyCfg_getMailboxConfig(selfCoreId, selfCoreId);

    *mailboxBaseAddr = pMailboxConfig->readReqMailboxBaseAddr;
}

static inline void IpcNotify_getReadSwQ(uint32 selfCoreId, uint32 remoteCoreId, IpcNotify_SwQueue **swQ)
{
    IpcNotify_MailboxConfig *pMailboxConfig;

    pMailboxConfig = IpcNotifyCfg_getMailboxConfig(remoteCoreId, selfCoreId);

    *swQ = pMailboxConfig->swQ;
}

sint32 IpcNotify_lld_init(IpcNotify_Handle hIpcNotify)
{
    uint32               clientId;
    sint32               status = MCAL_SystemP_SUCCESS;
    uint32               selfCoreId;
    IpcNotify_InitHandle hIpcNotifyInit;

    if ((hIpcNotify != NULL_PTR) && (hIpcNotify->hIpcNotifyInit != NULL_PTR))
    {
        hIpcNotifyInit = hIpcNotify->hIpcNotifyInit;
        selfCoreId     = hIpcNotifyInit->selfCoreId;

        MCAL_LLD_PARAMS_CHECK(selfCoreId < MCAL_CSL_CORE_ID_MAX);

        hIpcNotify->interruptConfig    = IpcNotifyCfg_getInterruptConfig(selfCoreId);
        hIpcNotify->interruptConfigNum = IpcNotifyCfg_getInterruptConfigNum(selfCoreId);

        for (clientId = 0U; clientId < IPC_NOTIFY_CLIENT_ID_MAX; clientId++)
        {
            IpcNotify_lld_unregisterClient(hIpcNotify, (uint16)clientId);
        }
        IpcNotify_lld_init_clearIntOn(hIpcNotify, selfCoreId);
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    return status;
}

sint32 IpcNotify_lld_deInit(IpcNotify_Handle hIpcNotify)
{
    uint32 clientId;
    uint32 mailboxBaseAddr;
    sint32 status = MCAL_SystemP_SUCCESS;

    if (hIpcNotify != NULL_PTR)
    {
        for (clientId = 0U; clientId < IPC_NOTIFY_CLIENT_ID_MAX; clientId++)
        {
            IpcNotify_lld_unregisterClient(hIpcNotify, (uint16)clientId);
        }

        IpcNotify_getReadMailbox(hIpcNotify->hIpcNotifyInit->selfCoreId, &mailboxBaseAddr);
        IpcNotify_mailboxClearAllInt(mailboxBaseAddr);
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    return status;
}

static uint32 IpcNotify_makeMsg(IpcNotify_Handle hIpcNotify, uint16 clientId, uint32 msgValue)
{
    uint32 msg;

#if (CDD_IPC_CRC_ENABLE == STD_ON)
    {
        uint8  crc = 0U;
        uint32 crcData;
        crcData = msgValue & (CDD_IPC_NOTIFY_CRC_MSG_VALUE_MAX - 1U);

        hIpcNotify->hIpcNotifyInit->Cdd_Ipc_CrcHookFunc(((uint8 *)(&crcData)), CDD_IPC_NOTIFY_CRC_DATASIZE,
                                                        CDD_IPC_NOTIFY_CRC_SIZE, &crc);

        msg = ((clientId & (IPC_NOTIFY_CLIENT_ID_MAX - 1U)) << IPC_NOTIFY_CLIENT_ID_SHIFT) |
              (crc << IPC_NOTIFY_CRC_SHIFT) | (msgValue & (CDD_IPC_NOTIFY_CRC_MSG_VALUE_MAX - 1U));
    }
#else
    {
        msg = ((clientId & (IPC_NOTIFY_CLIENT_ID_MAX - 1U)) << IPC_NOTIFY_CLIENT_ID_SHIFT) |
              (msgValue & (IPC_NOTIFY_MSG_VALUE_MAX - 1U));
    }
#endif
    return msg;
}

sint32 IpcNotify_lld_sendMsg(IpcNotify_Handle hIpcNotify, const IpcNotify_MsgParams *msgParams)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    if ((hIpcNotify != NULL_PTR) && (msgParams != NULL_PTR) && (msgParams->remoteCoreId < MCAL_CSL_CORE_ID_MAX) &&
        (msgParams->remoteClientId < IPC_NOTIFY_CLIENT_ID_MAX))
    {
        status = IpcNotify_lld_sendMsg_mailboxWrite(hIpcNotify, msgParams);
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    return status;
}

sint32 IpcNotify_lld_registerClient(IpcNotify_Handle hIpcNotify, uint16 localClientId,
                                    IpcNotify_FxnCallback msgCallback, void *args)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    if ((hIpcNotify != NULL_PTR) && (localClientId < IPC_NOTIFY_CLIENT_ID_MAX))
    {
        SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
        if (hIpcNotify->callback[localClientId] == NULL_PTR)
        {
            hIpcNotify->callback[localClientId]     = msgCallback;
            hIpcNotify->callbackArgs[localClientId] = args;
        }
        else
        {
            status = MCAL_SystemP_INVALID_PARAM;
        }
        SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    return status;
}

sint32 IpcNotify_lld_unregisterClient(IpcNotify_Handle hIpcNotify, uint16 localClientId)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    if ((hIpcNotify != NULL_PTR) && (localClientId < IPC_NOTIFY_CLIENT_ID_MAX))
    {
        SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
        hIpcNotify->callback[localClientId]     = (IpcNotify_FxnCallback)NULL_PTR;
        hIpcNotify->callbackArgs[localClientId] = NULL_PTR;
        SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    return status;
}

__attribute__((weak)) void IpcNotify_lld_isr(void *args)
{
    IpcNotify_InterruptConfig *pInterruptConfig;
    uint32                     mailboxBaseAddr;
    IpcNotify_SwQueue         *swQ;
    uint32                     core, value;
    sint32                     status;
    uint32                     pendingIntr;
    uint32                     selfCoreId;
    IpcNotify_Handle           hIpcNotify = (IpcNotify_Handle)args;

    selfCoreId = hIpcNotify->hIpcNotifyInit->selfCoreId;

    pInterruptConfig = hIpcNotify->interruptConfig;

    IpcNotify_getReadMailbox(selfCoreId, &mailboxBaseAddr);

    pendingIntr = IpcNotify_mailboxGetPendingIntr(mailboxBaseAddr);
    do
    {
        IpcNotify_wait();

        /* We clear pending interrupt unconditional here, and read all the SW queues later */
        IpcNotify_mailboxClearPendingIntr(mailboxBaseAddr, pendingIntr);

        for (core = 0U; core < pInterruptConfig->numCores; core++)
        {
            IpcNotify_getReadSwQ(selfCoreId, pInterruptConfig->coreIdList[core], &swQ);

            do
            {
                status = IpcNotify_mailboxReadSwQ(swQ, &value);
                IpcNotify_lld_isrCrcCheck(status, value, hIpcNotify, pInterruptConfig, core);
            } while (status == MCAL_SystemP_SUCCESS);
        }

        /* we need to keeping doing this until all status bits are 0, else we dont get new interrupt
         * at R5F */
        pendingIntr = IpcNotify_mailboxGetPendingIntr(mailboxBaseAddr);
    } while (pendingIntr != 0U);
}

uint32 IpcNotify_lld_getSelfCoreId(IpcNotify_Handle hIpcNotify)
{
    return hIpcNotify->hIpcNotifyInit->selfCoreId;
}

uint32 IpcNotify_lld_isCoreEnabled(IpcNotify_Handle hIpcNotify, uint32 coreId)
{
    uint32 isEnabled = 0U;

    if (coreId < MCAL_CSL_CORE_ID_MAX)
    {
        isEnabled = hIpcNotify->isCoreEnabled[coreId];
    }

    return isEnabled;
}

void Cdd_Ipc_Clock_uSleep(uint32 usec) __attribute__((optnone))
{
    volatile uint32 i     = 0U;
    uint32          value = usec * 400U;
    for (i = 0U; i < value;)
    {
        i = i + 1U;
    }

    /* Here 400 is the number of uSeconds per ticks*/
}

uint32 Cdd_Ipc_Clock_ticksToUsec(uint32 ticks)
{
    return (uint32)(ticks * 1000U);
}

static void IpcNotify_lld_init_clearIntOn(IpcNotify_Handle hIpcNotify, uint32 selfCoreId)
{
    uint32               core, intConfigNum;
    uint32               mailboxBaseAddr;
    IpcNotify_InitHandle hIpcNotifyInit;
    hIpcNotifyInit = hIpcNotify->hIpcNotifyInit;
    for (core = 0U; core < MCAL_CSL_CORE_ID_MAX; core++)
    {
        hIpcNotify->isCoreEnabled[core] = 0U;
    }
    /* check parameters and config and assert if invalid */
    for (core = 0U; core < hIpcNotifyInit->numCores; core++)
    {
        /* mark core as enabled for IPC */
        hIpcNotify->isCoreEnabled[hIpcNotifyInit->coreIdList[core]] = 1U;
    }
    for (intConfigNum = 0U; intConfigNum < hIpcNotify->interruptConfigNum; intConfigNum++)
    {
        IpcNotify_InterruptConfig *pInterruptConfig;

        pInterruptConfig = &hIpcNotify->interruptConfig[intConfigNum];

        IpcNotify_getReadMailbox(selfCoreId, &mailboxBaseAddr);

        if ((pInterruptConfig->clearIntOnInit) != 0U)
        {
            IpcNotify_mailboxClearAllInt(mailboxBaseAddr);
        }
    }
}

static sint32 IpcNotify_lld_sendMsg_mailboxWrite(IpcNotify_Handle hIpcNotify, const IpcNotify_MsgParams *msgParams)
{
    uint32             mailboxBaseAddr, intrBitPos;
    IpcNotify_SwQueue *swQ;
    sint32             status       = MCAL_SystemP_SUCCESS;
    uint32             elapsedTicks = 0U, startTicks = 0U, tempTicks = 0U;

    if ((hIpcNotify->isCoreEnabled[msgParams->remoteCoreId]) != 0U)
    {
        uint32 value = IpcNotify_makeMsg(hIpcNotify, msgParams->remoteClientId, msgParams->messageValue);

        IpcNotify_getWriteMailbox(hIpcNotify->hIpcNotifyInit->selfCoreId, msgParams->remoteCoreId, &mailboxBaseAddr,
                                  &intrBitPos, &swQ);

        SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();

        Mcal_GetCycleCounterValue(&startTicks);

        do
        {
            status = IpcNotify_mailboxWrite(hIpcNotify->hIpcNotifyInit->selfCoreId, msgParams->remoteCoreId,
                                            mailboxBaseAddr, intrBitPos, swQ, value);
            if ((status != MCAL_SystemP_SUCCESS) && (msgParams->waitForFifoNotFull != 0U))
            {
                SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
                SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
                tempTicks = startTicks;
                Mcal_GetElapsedCycleCountValue(&tempTicks, &elapsedTicks);
            }
        } while ((status != MCAL_SystemP_SUCCESS) && (msgParams->waitForFifoNotFull != 0U) &&
                 (elapsedTicks < msgParams->timeout));

        if ((msgParams->timeout != 0U) && (elapsedTicks >= msgParams->timeout))
        {
            status = MCAL_SystemP_TIMEOUT;
        }
        else
        {
            /*Do nothing*/
        }

        SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
    }
    else
    {
        status = MCAL_SystemP_FAILURE;
    }
    return status;
}

static void IpcNotify_lld_isrCrcCheck(sint32 status, uint32 value, IpcNotify_Handle hIpcNotify,
                                      IpcNotify_InterruptConfig *pInterruptConfig, uint32 core)
{
    uint16 clientId;
    sint32 crcStatus = MCAL_SystemP_SUCCESS;
    if (status == MCAL_SystemP_SUCCESS)
    {
        clientId = (value >> IPC_NOTIFY_CLIENT_ID_SHIFT) & (IPC_NOTIFY_CLIENT_ID_MAX - 1U);

#if (CDD_IPC_CRC_ENABLE == STD_ON)
        {
            uint8  inputCrc, calcCrc;
            uint32 crcData;
            crcData   = (value & (CDD_IPC_NOTIFY_CRC_MSG_VALUE_MAX - 1U));
            crcStatus = MCAL_SystemP_FAILURE;

            inputCrc  = (uint8)((value >> IPC_NOTIFY_CRC_SHIFT) & (CDD_IPC_NOTIFY_CRC_MAX - 1U));
            crcStatus = hIpcNotify->hIpcNotifyInit->Cdd_Ipc_CrcHookFunc(
                (uint8 *)(&crcData), CDD_IPC_NOTIFY_CRC_DATASIZE, CDD_IPC_NOTIFY_CRC_SIZE, &calcCrc);

            if ((crcStatus == MCAL_SystemP_SUCCESS) && (inputCrc == calcCrc))
            {
                crcStatus = MCAL_SystemP_SUCCESS;
            }
        }
#endif

        if (hIpcNotify->callback[clientId] != NULL_PTR)
        {
#if (CDD_IPC_CRC_ENABLE == STD_ON)
            hIpcNotify->callback[clientId](hIpcNotify, pInterruptConfig->coreIdList[core], clientId,
                                           (value & (CDD_IPC_NOTIFY_CRC_MSG_VALUE_MAX - 1U)), CDD_IPC_TIMEOUT,
                                           crcStatus, hIpcNotify->callbackArgs[clientId]);
#else
            hIpcNotify->callback[clientId](hIpcNotify, pInterruptConfig->coreIdList[core], clientId,
                                           (value & (IPC_NOTIFY_MSG_VALUE_MAX - 1U)), CDD_IPC_TIMEOUT, crcStatus,
                                           hIpcNotify->callbackArgs[clientId]);
#endif
        }
    }
}

#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
