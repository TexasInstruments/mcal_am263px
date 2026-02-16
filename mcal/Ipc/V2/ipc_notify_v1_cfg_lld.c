/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2018-2023 Texas Instruments Incorporated
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

#include "ipc_notify_v1_lld.h"
#include "ipc_notify_v1_cfg_lld.h"
#include "mcal_hw_soc_defines.h"

#define CDD_IPC_START_SEC_VAR_INIT_32
#include "Cdd_Ipc_MemMap.h"

/* shift to apply in mailbox addr to get to core specific status */
uint32 gIpcNotifyCoreIntrBitPos[]                         = {R5FSS0_0_MBOX_PROC_BIT_POS, R5FSS0_1_MBOX_PROC_BIT_POS};
uint32 gIpcNotifyInterruptConfigNum_r5fss0_0              = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM;
uint32 gIpcNotifyInterruptConfigNum_r5fss0_1              = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM;
uint32 gIpcNotifyInterruptConfigNum[MCAL_CSL_CORE_ID_MAX] = {
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM,
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM,
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
    },
};

/* Interrupt config for R5FSS0-0 */

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM] = {{
    .intNum   = R5FSS0_0_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS0-0 */
    .eventId  = 0U,                          /* not used */
    .numCores = 1U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_1,
            0,
        },
    .clearIntOnInit = 0,
}};

/* Interrupt config for R5FSS0-1 */

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss0_1[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM] = {{
    .intNum   = R5FSS0_1_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS0-1 */
    .eventId  = 0U,                          /* not used */
    .numCores = 1U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_0,
            0,
        },
    .clearIntOnInit = 0,
}};

IpcNotify_InterruptConfig* gIpcNotifyInterruptConfig[MCAL_CSL_CORE_ID_MAX] = {
    gIpcNotifyInterruptConfig_r5fss0_0,
    gIpcNotifyInterruptConfig_r5fss0_1,
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
     * and verifying the interrupt is triggered at receving Processor
     */
    for (loopCounter = 0U; loopCounter < IPC_NOTIFY_WAIT_CYCLES; loopCounter += 1U)
    {
        ;
    }
    return;
}

#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
