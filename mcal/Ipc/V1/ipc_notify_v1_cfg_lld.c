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

#define CDD_IPC_START_SEC_VAR_INIT_32
#include "Cdd_Ipc_MemMap.h"

/* shift to apply in mailbox addr to get to core specific status */
uint32 gIpcNotifyCoreIntrBitPos[] = {
    R5FSS0_0_MBOX_PROC_BIT_POS,
    R5FSS0_1_MBOX_PROC_BIT_POS,
    C66SS0_MBOX_PROC_BIT_POS,
};

uint32 gIpcNotifyInterruptConfigNum_r5fss0_0 = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM;
uint32 gIpcNotifyInterruptConfigNum_r5fss0_1 = IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM;
uint32 gIpcNotifyInterruptConfigNum_c66ss0   = IPC_NOFTIY_INTERRUPT_CONFIG_C66SS0_NUM;

uint32 gIpcNotifyInterruptConfigNum[MCAL_CSL_CORE_ID_MAX] = {
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM,
    IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM,
    IPC_NOFTIY_INTERRUPT_CONFIG_C66SS0_NUM,
};

#define CDD_IPC_STOP_SEC_VAR_INIT_32
#include "Cdd_Ipc_MemMap.h"

/* Pre-defined mailbox config to allow any CPU to send and receive messages from any CPU on this SOC
 *
 * These assignments need to be in sync with gIpcNotifyInterruptConfig* done later below,
 *
 * This is a 2D array
 * - 1st indexed by self core ID
 * - then indexed by remote core ID
 */
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
        {/* with C66SS0 */
         .writeDoneMailboxBaseAddr = R5FSS0_0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_0_MBOX_READ_REQ,
         .intrBitPos               = C66SS0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_0_TO_C66SS0_SW_QUEUE},
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
        {/* with C66SS0 */
         .writeDoneMailboxBaseAddr = R5FSS0_1_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = R5FSS0_1_MBOX_READ_REQ,
         .intrBitPos               = C66SS0_MBOX_PROC_BIT_POS,
         .swQ                      = R5FSS0_1_TO_C66SS0_SW_QUEUE},
    },
    /* C66SS0 */
    {
        {/* with R5FSS0_0 */
         .writeDoneMailboxBaseAddr = C66SS0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = C66SS0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_0_MBOX_PROC_BIT_POS,
         .swQ                      = C66SS0_TO_R5FSS0_0_SW_QUEUE},
        {/* with R5FSS0_1 */
         .writeDoneMailboxBaseAddr = C66SS0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = C66SS0_MBOX_READ_REQ,
         .intrBitPos               = R5FSS0_1_MBOX_PROC_BIT_POS,
         .swQ                      = C66SS0_TO_R5FSS0_1_SW_QUEUE},
        {/* with C66SS0 */
         .writeDoneMailboxBaseAddr = C66SS0_MBOX_WRITE_DONE,
         .readReqMailboxBaseAddr   = C66SS0_MBOX_READ_REQ,
         .intrBitPos               = C66SS0_MBOX_PROC_BIT_POS,
         .swQ                      = 0},
    },
};

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss0_0[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_0_NUM] = {{
    .intNum   = R5FSS0_0_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS0-0 */
    .eventId  = 0U,                          /* not used */
    .numCores = 2U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_1,
            MCAL_CSL_CORE_ID_C66SS0,
            0,
        },
    .clearIntOnInit = 0,
}};

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_r5fss0_1[IPC_NOFTIY_INTERRUPT_CONFIG_R5FSS0_1_NUM] = {{
    .intNum   = R5FSS0_1_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS0-1 */
    .eventId  = 0U,                          /* not used */
    .numCores = 2U,                          /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_0,
            MCAL_CSL_CORE_ID_C66SS0,
            0,
        },
    .clearIntOnInit = 0,
}};

IpcNotify_InterruptConfig gIpcNotifyInterruptConfig_c66ss0[IPC_NOFTIY_INTERRUPT_CONFIG_C66SS0_NUM] = {{
    .intNum   = C66SS0_MBOX_READ_REQ_INTR, /* interrupt line on R5FSS0-1 */
    .eventId  = 0U,                        /* not used */
    .numCores = 2U,                        /* number of cores that send messages which tied to this interrupt line */
    .coreIdList =
        {
            /* core ID's tied to this interrupt line */
            MCAL_CSL_CORE_ID_R5FSS0_0,
            MCAL_CSL_CORE_ID_R5FSS0_1,
            0,
        },
    .clearIntOnInit = 1,
}};

IpcNotify_InterruptConfig *gIpcNotifyInterruptConfig[MCAL_CSL_CORE_ID_MAX] = {
    gIpcNotifyInterruptConfig_r5fss0_0,
    gIpcNotifyInterruptConfig_r5fss0_1,
    gIpcNotifyInterruptConfig_c66ss0,
};

#define CDD_IPC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Ipc_MemMap.h"

#define CDD_IPC_START_SEC_CODE
#include "Cdd_Ipc_MemMap.h"

IpcNotify_InterruptConfig *IpcNotifyCfg_getInterruptConfig(uint32 coreId)
{
    return gIpcNotifyInterruptConfig[coreId];
}

uint32 IpcNotifyCfg_getInterruptConfigNum(uint32 coreId)
{
    return gIpcNotifyInterruptConfigNum[coreId];
}

IpcNotify_MailboxConfig *IpcNotifyCfg_getMailboxConfig(uint32 selfCoreId, uint32 remoteCoreId)
{
    return &gIpcNotifyMailboxConfig[selfCoreId][remoteCoreId];
}

#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
