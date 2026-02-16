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

#include <sipc_notify_src.h>

/*
 * global internal module state
 */
typedef struct
{
    uint32_t         selfCoreId; /* core ID on which this module is running */
    uint32_t         selfSecHostId;
    SIPC_FxnCallback callback[SIPC_CLIENT_ID_MAX];          /* user registered callback's */
    void            *callbackArgs[SIPC_CLIENT_ID_MAX];      /* arguments to user registered callback's */
    uint8_t          isCoreEnabled[MAX_SEC_CORES_WITH_HSM]; /* flags to indicate if a core is enabled for IPC */
    SIPC_InterruptConfig
            *interruptConfig;    /* interrupt config for this core,
                                  * this is a array with one element per interrupt that is setup to receive messages
                                  */
    uint32_t interruptConfigNum; /* number of interrupts to setup, i.e number of element in interruptConfig array */
    /* place holder to store the secure master core information */
    uint32_t secHostCoreId[MAX_SEC_CORES_WITH_HSM - 1];
} SIPC_Ctrl;

SIPC_Ctrl gSIPC_ctrl;

/**
 * This Api is responsible to set correct MBOX config for given secure core
 *
 * */
static inline void SIPC_setMboxConfig(SIPC_Params *params, uint32_t selfCoreId)
{
    SIPC_MailboxConfig *pMailboxConfig;
    uint8_t             secMaster;
    /* Based on secureMaster_corID populate the queues and mbox config
     * if selfcore id is hsm then write all the sec master write queues to the hsmmbox config and vice versa */
    if (selfCoreId == CORE_ID_HSM0_0)
    {
        /* Define HSM->R5 tx and R5 -> HSM rx queues */
        for (secMaster = 0; secMaster < (MAX_SEC_CORES_WITH_HSM - 1); secMaster++)
        {
            /*****************************************************************************/
            /* HSM TX queue setup                                                        */
            /*****************************************************************************/
            pMailboxConfig               = &gSIPC_HsmMboxConfig[params->secHostCoreId[secMaster]];
            pMailboxConfig->swQ          = gSIPC_QueHsmToSecureHost[secMaster];
            pMailboxConfig->swQ->wrIdx   = 0;
            pMailboxConfig->swQ->rdIdx   = 0;
            pMailboxConfig->swQ->EleSize = params->ipcQueue_eleSize_inBytes;
            pMailboxConfig->swQ->Qlength = params->ipcQueue_length;
            pMailboxConfig->swQ->Qfifo   = (uint8_t *)params->tx_SipcQueues[secMaster];

            /*****************************************************************************/
            /* HSM RX queue setup                                                        */
            /*****************************************************************************/
            pMailboxConfig               = &gSIPC_SecureHostMboxConfig[params->secHostCoreId[secMaster]];
            pMailboxConfig->swQ          = gSIPC_QueSecureHostToHsm[secMaster];
            pMailboxConfig->swQ->wrIdx   = 0;
            pMailboxConfig->swQ->rdIdx   = 0;
            pMailboxConfig->swQ->EleSize = params->ipcQueue_eleSize_inBytes;
            pMailboxConfig->swQ->Qlength = params->ipcQueue_length;
            pMailboxConfig->swQ->Qfifo   = (uint8_t *)params->rx_SipcQueues[secMaster];
        }
    }
    else
    {
        /*****************************************************************************/
        /* R5 TX queue setup                                                        */
        /*****************************************************************************/
        pMailboxConfig               = &gSIPC_SecureHostMboxConfig[selfCoreId];
        pMailboxConfig->swQ          = gSIPC_QueSecureHostToHsm[gSIPC_ctrl.selfSecHostId];
        pMailboxConfig->swQ->wrIdx   = 0;
        pMailboxConfig->swQ->rdIdx   = 0;
        pMailboxConfig->swQ->EleSize = params->ipcQueue_eleSize_inBytes;
        pMailboxConfig->swQ->Qlength = params->ipcQueue_length;
        pMailboxConfig->swQ->Qfifo =
            (uint8_t *)((uint32_t)SOC_virtToPhy((void *)params->tx_SipcQueues[CORE_INDEX_HSM]));

        /*****************************************************************************/
        /* R5 RX queue setup                                                        */
        /*****************************************************************************/
        pMailboxConfig               = &gSIPC_HsmMboxConfig[selfCoreId];
        pMailboxConfig->swQ          = gSIPC_QueHsmToSecureHost[gSIPC_ctrl.selfSecHostId];
        pMailboxConfig->swQ->wrIdx   = 0;
        pMailboxConfig->swQ->rdIdx   = 0;
        pMailboxConfig->swQ->EleSize = params->ipcQueue_eleSize_inBytes;
        pMailboxConfig->swQ->Qlength = params->ipcQueue_length;
        pMailboxConfig->swQ->Qfifo =
            (uint8_t *)((uint32_t)SOC_virtToPhy((void *)params->rx_SipcQueues[CORE_INDEX_HSM]));
    }
}

/* This api will get the mboxaddr, intrbitpos , and swQ of remote sec core to which the msg will be sent */
static inline void SIPC_getWriteMailbox(uint32_t remoteSecCoreId, uint32_t *mailboxBaseAddr, uint32_t *intrBitPos,
                                        SIPC_SwQueue **swQ)
{
    SIPC_MailboxConfig *pMailboxConfig;
    /* If it is HSM */
    if ((gSIPC_ctrl.selfCoreId == CORE_ID_HSM0_0) && (remoteSecCoreId < 2))
    {
        /* Read the necessary fields */
        pMailboxConfig   = &gSIPC_HsmMboxConfig[gSIPC_ctrl.secHostCoreId[remoteSecCoreId]];
        *mailboxBaseAddr = pMailboxConfig->writeDoneMailboxBaseAddr;
        *intrBitPos      = pMailboxConfig->wrIntrBitPos;
        *swQ             = pMailboxConfig->swQ;
    }
    else
    {
        /* Read from the mbox config of R5 -> hsm */
        pMailboxConfig   = &gSIPC_SecureHostMboxConfig[gSIPC_ctrl.selfCoreId];
        *mailboxBaseAddr = pMailboxConfig->writeDoneMailboxBaseAddr;
        *intrBitPos      = pMailboxConfig->wrIntrBitPos;
        *swQ             = pMailboxConfig->swQ;
    }
}
/* Get the read mailbox address */
static inline void SIPC_getReadMailbox(uint32_t *mailboxBaseAddr)
{
    SIPC_MailboxConfig *pMailboxConfig;

    if (gSIPC_ctrl.selfCoreId < CORE_ID_MAX)
    {
        /* If current core is HSM */
        if (gSIPC_ctrl.selfCoreId == CORE_ID_HSM0_0)
        {
            pMailboxConfig   = &gSIPC_HsmMboxConfig[0];
            *mailboxBaseAddr = pMailboxConfig->readReqMailboxBaseAddr;
        }
        else
        {
            pMailboxConfig   = &gSIPC_SecureHostMboxConfig[gSIPC_ctrl.selfCoreId];
            *mailboxBaseAddr = pMailboxConfig->readReqMailboxBaseAddr;
        }
    }
    else
    {
        *mailboxBaseAddr = 0;
    }
}

/* Get the read mailbox address */
static inline void SIPC_getReadMailboxClear(uint32_t *mailboxBaseAddr)
{
    SIPC_MailboxConfig *pMailboxConfig;

    if (gSIPC_ctrl.selfCoreId < CORE_ID_MAX)
    {
        /* If current core is HSM */
        if (gSIPC_ctrl.selfCoreId == CORE_ID_HSM0_0)
        {
            pMailboxConfig   = &gSIPC_HsmMboxConfig[0];
            *mailboxBaseAddr = pMailboxConfig->readReqMailboxClrBaseAddr;
        }
        else
        {
            pMailboxConfig   = &gSIPC_SecureHostMboxConfig[gSIPC_ctrl.selfCoreId];
            *mailboxBaseAddr = pMailboxConfig->readReqMailboxClrBaseAddr;
        }
    }
    else
    {
        *mailboxBaseAddr = 0;
    }
}

/* Set the interrupt config of self core */
static inline void SIPC_getIntrConfig(uint32_t selfCoreId, SIPC_InterruptConfig **interruptConfig,
                                      uint32_t *interruptConfigNum, uint8_t intrCfgNum)
{
    /* Extern globals that are specific to this core */
    extern SIPC_InterruptConfig gSIPC_InterruptConfig[INTR_CFG_NUM_MAX][CORE_ID_MAX];

    *interruptConfig    = &gSIPC_InterruptConfig[intrCfgNum][selfCoreId];
    *interruptConfigNum = intrCfgNum;
}

/* Get the queue pointer to read data from core = remoteSecCoreId */
static inline void SIPC_getReadSwQ(uint32_t remoteSecCoreId, SIPC_SwQueue **swQ)
{
    SIPC_MailboxConfig *pMailboxConfig;

    if (gSIPC_ctrl.selfCoreId < CORE_ID_MAX)
    {
        /* If current core is HSM core */
        if (gSIPC_ctrl.selfCoreId == CORE_ID_HSM0_0)
        {
            /* Get remote secure master mailbox configuration */
            pMailboxConfig = &gSIPC_SecureHostMboxConfig[gSIPC_ctrl.secHostCoreId[remoteSecCoreId]];
            *swQ           = pMailboxConfig->swQ;
        }
        /* If current core is R5 */
        else
        {
            pMailboxConfig = &gSIPC_HsmMboxConfig[gSIPC_ctrl.selfCoreId];
            *swQ           = pMailboxConfig->swQ;
        }
    }
    else
    {
        *swQ = NULL_PTR;
    }
}

/* The first two bytes of any message will be empty so populate it client IDs */
static inline void SIPC_insertClientIds(uint8_t remoteClientId, uint8_t selfClientId, uint8_t *msgValue)
{
    /* Add error checking for wrong client Id in the message */
    *msgValue       = remoteClientId;
    *(msgValue + 1) = selfClientId;
}

/* Secure IPC Isr */
__attribute__((target("arm"))) void SIPC_isr(void)
{
    SIPC_InterruptConfig *pInterruptConfig = &gSIPC_ctrl.interruptConfig[gSIPC_ctrl.interruptConfigNum];
    uint32_t              mailboxBaseAddr;
    SIPC_SwQueue         *swQ;
    uint32_t              core;
    uint8_t               clientId;
    uint8_t               srcClientId;
    int32_t               status;
    uint32_t              pendingIntr;
    uint8_t               readMsgData[SIPC_MSG_SIZE];

    SIPC_getReadMailbox(&mailboxBaseAddr);

    pendingIntr = SIPC_mailboxGetPendingIntr(mailboxBaseAddr);
    do
    {
        SIPC_getReadMailboxClear(&mailboxBaseAddr);
        /* We clear pending interrupt unconditional here, and read all the SW queues later */
        SIPC_mailboxClearPendingIntr(mailboxBaseAddr, pendingIntr);

        for (core = 0; core < pInterruptConfig->numCores; core++)
        {
            /* Get the queue to read the data from also get the Qelementsize */
            SIPC_getReadSwQ(pInterruptConfig->coreIdList[core], &swQ);

            do
            {
                if (swQ == NULL_PTR)
                {
                    status = SystemP_FAILURE;
                }
                else
                {
                    /* If both rdid and wrid == 0 then status will be failure which indicates thats there
                       is nothing in the queue. */
                    status = SIPC_mailboxRead(swQ, readMsgData);
                }

                if (status == SystemP_SUCCESS)
                {
                    /* Get the client IDs */
                    clientId    = readMsgData[0];
                    srcClientId = readMsgData[1];

                    if (gSIPC_ctrl.callback[clientId] != NULL_PTR)
                    {
                        /* Pass the src client Id of message */
                        gSIPC_ctrl.callback[clientId](pInterruptConfig->coreIdList[core], clientId, srcClientId,
                                                      readMsgData, gSIPC_ctrl.callbackArgs[clientId]);
                    }
                }
            } while (status == SystemP_SUCCESS);
        }
        SIPC_getReadMailbox(&mailboxBaseAddr);
        /* We need to keeping doing this until all status bits are 0, else we dont get new interrupt */
        pendingIntr = SIPC_mailboxGetPendingIntr(mailboxBaseAddr);
    } while (pendingIntr != 0);
}
/* This api will be used to send message to a particular remoteSecCodeId and remoteClientId. */
int32_t SIPC_sendMsg(uint8_t remoteSecCoreId, uint8_t remoteClientId, uint8_t localClientId, uint8_t *msgValue,
                     SIPC_fifoFlags waitForFifoNotFull)
{
    uint32_t      oldIntState;
    uint32_t      mailboxBaseAddr, intrBitPos;
    SIPC_SwQueue *swQ;
    int32_t       status = SystemP_FAILURE;

    if ((remoteSecCoreId < MAX_SEC_CORES_WITH_HSM) && (gSIPC_ctrl.isCoreEnabled[remoteSecCoreId]))
    {
        /* Prepend src and dest client Id to msgValue */
        SIPC_insertClientIds(remoteClientId, localClientId, msgValue);

        SIPC_getWriteMailbox(remoteSecCoreId, &mailboxBaseAddr, &intrBitPos, &swQ);
        if ((mailboxBaseAddr == (uint32_t)NULL_PTR) || (swQ == NULL_PTR))
        {
            return status;
        }
        else
        {
            oldIntState = HwiP_disable();
            do
            {
                status = SIPC_mailboxWrite(mailboxBaseAddr, intrBitPos, swQ, msgValue);
                if (status != SystemP_SUCCESS && waitForFifoNotFull)
                {
                    /* Allow interrupt enable and check again */
                    HwiP_restore(oldIntState);
                    oldIntState = HwiP_disable();
                }
            } while (status != (SystemP_SUCCESS && waitForFifoNotFull));

            HwiP_restore(oldIntState);
            /* If not wait option is selected then return failure if FIFO is full */
            if (status != SystemP_SUCCESS)
            {
                status = SystemP_FAILURE;
            }
        }
    }
    return status;
}

int32_t SIPC_registerClient(uint8_t localClientId, SIPC_FxnCallback msgCallback, void *args)
{
    int32_t  status = SystemP_FAILURE;
    uint32_t oldIntState;

    if (localClientId < SIPC_CLIENT_ID_MAX)
    {
        oldIntState = HwiP_disable();
        if (gSIPC_ctrl.callback[localClientId] == NULL_PTR)
        {
            gSIPC_ctrl.callback[localClientId]     = msgCallback;
            gSIPC_ctrl.callbackArgs[localClientId] = args;
            status                                 = SystemP_SUCCESS;
        }
        HwiP_restore(oldIntState);
    }
    return status;
}

int32_t SIPC_unregisterClient(uint16_t localClientId)
{
    uint32_t oldIntState;

    oldIntState = HwiP_disable();
    if (localClientId < SIPC_CLIENT_ID_MAX)
    {
        gSIPC_ctrl.callback[localClientId]     = NULL_PTR;
        gSIPC_ctrl.callbackArgs[localClientId] = NULL_PTR;
    }
    HwiP_restore(oldIntState);

    return SystemP_SUCCESS;
}

/* Default parameters */
void SIPC_Params_init(SIPC_Params *params)
{
    uint32_t i;

    params->numCores = 0;
    /* for non registered cores.*/
    for (i = 0; i < MAX_SEC_CORES_WITH_HSM; i++)
    {
        params->coreIdList[i] = CORE_ID_MAX;
    }

    params->interruptConfig_Num = 0;
}

int32_t SIPC_init(SIPC_Params *params)
{
    uint32_t i, core, oldIntState;
    int32_t  status = SystemP_SUCCESS;
    uint32_t mailboxBaseAddr;
    uint32_t selfCoreId;
    uint8_t  assertFlag = 0;
    /* for R5 selfCoreId comes from core cluster registers
     * This is configured at compile time */
    selfCoreId        = SELF_CORE_ID;
    uint8_t secMaster = 0;

    /* check if current core who is doing sipc init is a secure host or not if not.
     * if not then return init failure */

    for (secMaster = 0; secMaster < (MAX_SEC_CORES_WITH_HSM - 1); secMaster++)
    {
        if ((selfCoreId == params->secHostCoreId[secMaster]) || (selfCoreId == CORE_ID_HSM0_0))
        {
            if (selfCoreId == CORE_ID_HSM0_0)
            {
                gSIPC_ctrl.selfSecHostId = CORE_INDEX_HSM;
            }
            else
            {
                gSIPC_ctrl.selfSecHostId = secMaster;
            }
            assertFlag = 0;

            break;
        }
        else
        {
            assertFlag = 1;
        }
    }
    /* Indicates that this core is not a secHost*/
    if (assertFlag == 1)
    {
        return SystemP_FAILURE;
    }
    else
    {
        SIPC_getIntrConfig(selfCoreId, &gSIPC_ctrl.interruptConfig, &gSIPC_ctrl.interruptConfigNum,
                           params->interruptConfig_Num);
        /* Add the selfcore iD to notifyctrl structure*/
        gSIPC_ctrl.selfCoreId                             = selfCoreId;
        gSIPC_ctrl.secHostCoreId[CORE_INDEX_SEC_MASTER_0] = params->secHostCoreId[CORE_INDEX_SEC_MASTER_0];
        gSIPC_ctrl.secHostCoreId[CORE_INDEX_SEC_MASTER_1] = params->secHostCoreId[CORE_INDEX_SEC_MASTER_1];

        /* Unregister previously registered clients. */
        for (i = 0; i < SIPC_CLIENT_ID_MAX; i++)
        {
            SIPC_unregisterClient(i);
        }
        /* Register queues pointer point to an allocated queue. & initialize mailboxconfig swQ parameters.
         * set the mailbox config based on wether a core is secure master or not */
        SIPC_setMboxConfig(params, selfCoreId);

        /* Reset some state variables */
        for (core = 0; core < MAX_SEC_CORES_WITH_HSM; core++)
        {
            gSIPC_ctrl.isCoreEnabled[core] = 0;
        }
        /* Typechecking user config params */
        if (params->numCores < MAX_SEC_CORES_WITH_HSM)
        {
            for (core = 0; core < params->numCores; core++)
            {
                if (params->coreIdList[core] < MAX_SEC_CORES_WITH_HSM)
                {
                    /* Mark core as enabled for IPC */
                    gSIPC_ctrl.isCoreEnabled[params->coreIdList[core]] = 1;
                }
                else
                {
                    return SystemP_FAILURE;
                }
            }
        }
        else
        {
            return SystemP_FAILURE;
        }
        oldIntState = HwiP_disable();

        for (i = 0; i <= gSIPC_ctrl.interruptConfigNum; i++)
        {
            HwiP_Params           hwiParams;
            SIPC_InterruptConfig *pInterruptConfig;

            pInterruptConfig = &gSIPC_ctrl.interruptConfig[i];

            /* Isr need to write this register to clear the interrupt */
            SIPC_getReadMailbox(&mailboxBaseAddr);

            if (pInterruptConfig->clearIntOnInit != 0U)
            {
                SIPC_mailboxClearAllInt(mailboxBaseAddr);
            }

            status = SIPC_Register_Isr(&hwiParams, pInterruptConfig, params, &SIPC_isr);
        }

        HwiP_restore(oldIntState);

        return status;
    }
}

void SIPC_deInit(void)
{
    uint32_t itr;
    uint32_t oldIntState;
    uint32_t mailboxBaseAddr;

    for (itr = 0; itr < SIPC_CLIENT_ID_MAX; itr++)
    {
        SIPC_unregisterClient(itr);
    }

    oldIntState = HwiP_disable();

    for (itr = 0; itr <= gSIPC_ctrl.interruptConfigNum; itr++)
    {
        SIPC_getReadMailbox(&mailboxBaseAddr);
        SIPC_mailboxClearAllInt(mailboxBaseAddr);
    }

    HwiP_restore(oldIntState);
}

uint32_t SIPC_getSelfCoreId(void)
{
    return gSIPC_ctrl.selfCoreId;
}

uint32_t SIPC_getSelfSecMasterId(void)
{
    return gSIPC_ctrl.selfSecHostId;
}

uint32_t SIPC_isCoreEnabled(uint32_t coreId)
{
    uint32_t isEnabled = 0;

    if (coreId < MAX_SEC_CORES_WITH_HSM)
    {
        isEnabled = gSIPC_ctrl.isCoreEnabled[coreId];
    }
    else
    {
        isEnabled = 0;
    }
    return isEnabled;
}
