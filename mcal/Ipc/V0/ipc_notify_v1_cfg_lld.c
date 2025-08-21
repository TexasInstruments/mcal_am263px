/*
 *  Copyright (C) 2018-2023 Texas Instruments Incorporated
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
#include "mcal_hw_soc_defines.h"

#define CDD_IPC_START_SEC_VAR_INIT_32
#include "Cdd_Ipc_MemMap.h"

/* shift to apply in mailbox addr to get to core specific status */
uint32 gIpcNotifyCoreIntrBitPos[] = {R5FSS0_0_MBOX_PROC_BIT_POS, R5FSS0_1_MBOX_PROC_BIT_POS, R5FSS1_0_MBOX_PROC_BIT_POS,
                                     R5FSS1_1_MBOX_PROC_BIT_POS};
uint32 gIpcNotifyInterruptConfigNum_r5fss1_1              = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS1_1_NUM;
uint32 gIpcNotifyInterruptConfigNum_r5fss0_0              = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM;
uint32 gIpcNotifyInterruptConfigNum_r5fss0_1              = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM;
uint32 gIpcNotifyInterruptConfigNum_r5fss1_0              = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS1_0_NUM;
uint32 gIpcNotifyInterruptConfigNum[MCAL_CSL_CORE_ID_MAX] = {
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM,
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM,
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS1_0_NUM,
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS1_1_NUM,
};
#define CDD_IPC_STOP_SEC_VAR_INIT_32
#include "Cdd_Ipc_MemMap.h"

#define CDD_IPC_START_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Ipc_MemMap.h"

IpcNotify_MailboxConfig gIpcNotifyMailboxConfig[MCAL_CSL_CORE_ID_MAX][MCAL_CSL_CORE_ID_MAX] = {
    /* R5FSS0-0 */
    {
        {/* with R5FSS0_0 */
         .writeDoneMailboxBaseAddr = R5FSS0_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_0_MBOX_PROC_BIT_POS,
         .swQ                      = 0},
        {/* with R5FSS0_1 */
         .writeDoneMailboxBaseAddr = R5FSS0_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_1_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_0_TO_R5FSS0_1_SW_QUEUE},
        {/* with R5FSS1_0 */
         .writeDoneMailboxBaseAddr = R5FSS0_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_0_TO_R5FSS1_0_SW_QUEUE},
        {/* with R5FSS1_1 */
         .writeDoneMailboxBaseAddr = (uint32)R5FSS0_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_1_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_0_TO_R5FSS1_1_SW_QUEUE},
    },
    /* R5FSS0-1 */
    {
        {/* with R5FSS0_0 */
         .writeDoneMailboxBaseAddr = R5FSS0_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_1_TO_R5FSS0_0_SW_QUEUE},
        {/* with R5FSS0_1 */
         .writeDoneMailboxBaseAddr = R5FSS0_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_1_MBOX_PROC_BIT_POS,
         .swQ                      = 0},
        {/* with R5FSS1_0 */
         .writeDoneMailboxBaseAddr = R5FSS0_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_1_TO_R5FSS1_0_SW_QUEUE},
        {/* with R5FSS1_1 */
         .writeDoneMailboxBaseAddr = R5FSS0_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_1_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_1_TO_R5FSS1_1_SW_QUEUE},
    },
    /* R5FSS1-0 */
    {
        {/* with R5FSS0_0 */
         .writeDoneMailboxBaseAddr = R5FSS1_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS1_0_TO_R5FSS0_0_SW_QUEUE},
        {/* with R5FSS0_1 */
         .writeDoneMailboxBaseAddr = R5FSS1_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_1_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS1_0_TO_R5FSS0_1_SW_QUEUE},
        {/* with R5FSS1_0 */
         .writeDoneMailboxBaseAddr = R5FSS1_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_0_MBOX_PROC_BIT_POS,
         .swQ                      = 0},
        {/* with R5FSS1_1 */
         .writeDoneMailboxBaseAddr = R5FSS1_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_1_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS1_0_TO_R5FSS1_1_SW_QUEUE},
    },
    /* R5FSS1-1 */
    {
        {/* with R5FSS0_0 */
         .writeDoneMailboxBaseAddr = R5FSS1_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS1_1_TO_R5FSS0_0_SW_QUEUE},
        {/* with R5FSS0_1 */
         .writeDoneMailboxBaseAddr = R5FSS1_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_1_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS1_1_TO_R5FSS0_1_SW_QUEUE},
        {/* with R5FSS1_0 */
         .writeDoneMailboxBaseAddr = R5FSS1_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS1_1_TO_R5FSS1_0_SW_QUEUE},
        {/* with R5FSS1_1 */
         .writeDoneMailboxBaseAddr = R5FSS1_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS1_1_MBOX_READ_REQ,
         .intrBitPos               = R5FSS1_1_MBOX_PROC_BIT_POS,
         .swQ                      = 0},
    },
};

/* Interrupt config for R5FSS0-0 */

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM] = {{
    .intNum   = R5FSS0_0_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS0-0 */
    .eventId  = 0U,                          /* not used */
    .numCores = 3U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_1,
            MCAL_CSL_CORE_ID_R5FSS1_0,
            MCAL_CSL_CORE_ID_R5FSS1_1,
            0,
        },
    .clearIntOnInit = 0,
}};

/* Interrupt config for R5FSS0-1 */

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss0_1[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM] = {{
    .intNum   = R5FSS0_1_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS0-1 */
    .eventId  = 0U,                          /* not used */
    .numCores = 3U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_0,
            MCAL_CSL_CORE_ID_R5FSS1_0,
            MCAL_CSL_CORE_ID_R5FSS1_1,
            0,
        },
    .clearIntOnInit = 0,
}};

/* Interrupt config for R5FSS1-0 */

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss1_0[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS1_0_NUM] = {{
    .intNum   = R5FSS1_0_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS1-0 */
    .eventId  = 0U,                          /* not used */
    .numCores = 3U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_0,
            MCAL_CSL_CORE_ID_R5FSS0_1,
            MCAL_CSL_CORE_ID_R5FSS1_1,
            0,
        },
    .clearIntOnInit = 0,
}};

/* Interrupt config for R5FSS1-1 */

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss1_1[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS1_1_NUM] = {{
    .intNum   = R5FSS1_1_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS1-1 */
    .eventId  = 0U,                          /* not used */
    .numCores = 3U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_0,
            MCAL_CSL_CORE_ID_R5FSS0_1,
            MCAL_CSL_CORE_ID_R5FSS1_0,
            0,
        },
    .clearIntOnInit = 0,
}};

IpcNotify_InterruptConfig* gIpcNotifyInterruptConfig[MCAL_CSL_CORE_ID_MAX] = {
    gIpcNotifyInterruptConfig_r5fss0_0,
    gIpcNotifyInterruptConfig_r5fss0_1,
    gIpcNotifyInterruptConfig_r5fss1_0,
    gIpcNotifyInterruptConfig_r5fss1_1,
};
#define CDD_IPC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Ipc_MemMap.h"

/* Pre-defined mailbox config to allow any CPU to send and receive messages from any CPU on this SOC
 *
 * These assignments need to be in sync with gIpcNotifyInterruptConfig* done later below,
 *
 * This is a 2D array
 * - 1st indexed by self core ID
 * - then indexed by remote core ID
 */

#define CDD_IPC_START_SEC_CODE
#include "Cdd_Ipc_MemMap.h"

IpcNotify_InterruptConfig* IpcNotifyCfg_getInterruptConfig(uint32 coreId)
{
    return gIpcNotifyInterruptConfig[coreId];
}

uint32 IpcNotifyCfg_getInterruptConfigNum(uint32 coreId)
{
    return gIpcNotifyInterruptConfigNum[coreId];
}

IpcNotify_MailboxConfig* IpcNotifyCfg_getMailboxConfig(uint32 selfCoreId, uint32 remoteCoreId)
{
    return &gIpcNotifyMailboxConfig[selfCoreId][remoteCoreId];
}

sint32 IpcNotify_trigInterrupt(uint32 selfCoreId, uint32 remoteCoreId, uint32 mailboxBaseAddr, uint32 intrBitPos)
{
    uint32           pendingIntr, counter = 0U;
    volatile uint32* addr   = (uint32*)mailboxBaseAddr;
    sint32           status = MCAL_SystemP_SUCCESS;

    /* Keep polling for READ_REQ register bit of Receiver */
    IpcNotify_MailboxConfig* pReceiverMailboxConfig;
    pReceiverMailboxConfig = &gIpcNotifyMailboxConfig[remoteCoreId][selfCoreId];
    do
    {
        counter++;
        /* trigger interrupt to other core */
        *addr       = ((uint32)1U << intrBitPos);
        pendingIntr = IpcNotify_mailboxGetPendingIntr(pReceiverMailboxConfig->readReqMailboxBaseAddr);
        pendingIntr = (pendingIntr >> (pReceiverMailboxConfig->intrBitPos)) &
                      (0x1U); /* Get the READ_REQ reg. value w.r.t Core bit pos. */
    } while ((pendingIntr != 1U) && (counter < IPC_NOTIFY_LOOP_COUNTER_MAX));
    if (counter >= IPC_NOTIFY_LOOP_COUNTER_MAX)
    {
        status = MCAL_SystemP_TIMEOUT;
    }

    return status;
}

void IpcNotify_wait(void)
{
    volatile uint32 loopCounter = 0U;

    /* Processor sending will trigger read request multiple times and ensure
     * that read request is reached to receiving processor. The delay implemented
     * here is not to clear the interrupt while sending processor is reading back
     * and verifying the interrupt is triggered at receiving Processor
     */
    for (loopCounter = 0U; loopCounter < IPC_NOTIFY_WAIT_CYCLES; loopCounter += 1U)
    {
        ;
    }
    return;
}

#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
