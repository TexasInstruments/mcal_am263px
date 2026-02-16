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

#ifndef IPC_NOTIFY_V1_MAILBOX_H_
#define IPC_NOTIFY_V1_MAILBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "sys_common.h"

/* this file has define's and inline function's to program the HW mailbox registers and SW queue
 * structure */

#define MAILBOX_MAX_MSGS_IN_SW_FIFO (4U)
#define MAILBOX_MAX_SW_QUEUE_SIZE   (32U)

/* The HW mailbox only allows to trigger a interrupt on another core,
 * the IPC Notify needs ability to pass 32b value along with a interrupt
 * This 32b value is kept a MAILBOX_MAX_MSGS_IN_FIFO deep SW queue
 *
 * Basically this mimics the functionality of HW mailbox with HW FIFO in AM243x SOC
 *
 * Note, recommend to not modify MAILBOX_MAX_MSGS_IN_SW_FIFO and MAILBOX_MAX_SW_QUEUE_SIZE
 * and IpcNotify_SwQueue struct.
 *
 * This needs to be in sync with the addresses being set for SW queue memory in
 * soc/{soc}/ipc_notify_v1_cfg.c
 */
typedef struct
{
    volatile uint32 rdIdx;
    volatile uint32 wrIdx;
    uint32          fifo[MAILBOX_MAX_MSGS_IN_SW_FIFO];

} IpcNotify_SwQueue;
/**
 * \brief Parameters for mailbox write operation
 *
 * This structure groups the parameters needed for mailbox write.
 */
typedef struct IpcNotify_MailboxWriteParams_s
{
    uint32             selfCoreId;      /**< Self core ID */
    uint32             remoteCoreId;    /**< Remote core ID */
    uint32             mailboxBaseAddr; /**< Mailbox base address */
    uint32             intrBitPos;      /**< Interrupt bit position */
    IpcNotify_SwQueue *swQ;             /**< Pointer to SW queue */
    uint32             value;           /**< Value to write */
} IpcNotify_MailboxWriteParams;

extern sint32        IpcNotify_trigInterrupt(uint32 selfCoreId, uint32 remoteCoreId, uint32 mailboxBaseAddr,
                                             uint32 intrBitPos);
extern uint32        gIpcNotifyCoreIntrBitPos[4];
static inline void   IpcNotify_mailbox_asm(void);
static inline sint32 IpcNotify_mailboxReadSwQ(IpcNotify_SwQueue *swQ, uint32 *value);

/* read from SW fifo within a mailbox  */
static inline sint32 IpcNotify_mailboxReadSwQ(IpcNotify_SwQueue *swQ, uint32 *value)
{
    sint32 status = MCAL_SystemP_FAILURE;

    uint32 rdIdx = swQ->rdIdx;
    uint32 wrIdx = swQ->wrIdx;

    if ((rdIdx < MAILBOX_MAX_MSGS_IN_SW_FIFO) && (wrIdx < MAILBOX_MAX_MSGS_IN_SW_FIFO))
    {
        if (rdIdx != wrIdx)
        {
            /* there is something in the FIFO */
            *value = swQ->fifo[rdIdx];

            rdIdx = (rdIdx + 1U) % MAILBOX_MAX_MSGS_IN_SW_FIFO;

            swQ->rdIdx = rdIdx;

            rdIdx = swQ->rdIdx;      /* read back to ensure the update has reached the memory */
            if (rdIdx == swQ->rdIdx) /*To suppress MISRA warning*/
            {
                /*Do nothing*/
            }
            IpcNotify_mailbox_asm();
            status = MCAL_SystemP_SUCCESS;
        }
    }

    return status;
}

/* write to SW fifo and trigger HW interrupt using HW mailbox */
static inline sint32 IpcNotify_mailboxWrite(const IpcNotify_MailboxWriteParams *writeParams)
{
    sint32 status = MCAL_SystemP_FAILURE;

    uint32 rdIdx = writeParams->swQ->rdIdx;
    uint32 wrIdx = writeParams->swQ->wrIdx;

    if ((rdIdx < MAILBOX_MAX_MSGS_IN_SW_FIFO) && (wrIdx < MAILBOX_MAX_MSGS_IN_SW_FIFO))
    {
        if (((wrIdx + 1U) % MAILBOX_MAX_MSGS_IN_SW_FIFO) != rdIdx)
        {
            /* there is some space in the FIFO */
            writeParams->swQ->fifo[wrIdx] = writeParams->value;

            wrIdx = (wrIdx + 1U) % MAILBOX_MAX_MSGS_IN_SW_FIFO;

            writeParams->swQ->wrIdx = wrIdx;

            wrIdx = writeParams->swQ->wrIdx;      /* read back to ensure the update has reached the memory */
            if (wrIdx == writeParams->swQ->wrIdx) /*To suppress MISRA warning*/
            {
                /*Do nothing*/
            }
            IpcNotify_mailbox_asm();

            /* trigger interrupt to other core */
            status = IpcNotify_trigInterrupt(writeParams->selfCoreId, writeParams->remoteCoreId,
                                             writeParams->mailboxBaseAddr, writeParams->intrBitPos);
        }
    }

    return status;
}

static inline void IpcNotify_mailboxClearAllInt(uint32 mailboxBaseAddr)
{
    volatile uint32 *addr = (uint32 *)mailboxBaseAddr;
    *addr                 = 0x1111111U;
}

static inline uint32 IpcNotify_mailboxGetPendingIntr(uint32 mailboxBaseAddr)
{
    volatile uint32 *addr = (uint32 *)mailboxBaseAddr;

    return *addr;
}

static inline void IpcNotify_mailboxClearPendingIntr(uint32 mailboxBaseAddr, uint32 pendingIntr)
{
    volatile uint32 *addr = (uint32 *)mailboxBaseAddr;

    *addr = pendingIntr;
}

static inline uint32 IpcNotify_mailboxIsPendingIntr(uint32 pendingIntr, uint32 coreId)
{
    uint32 isPending = 0U;
    if (coreId < MCAL_CSL_CORE_ID_MAX)
    {
        isPending = pendingIntr & (1U << gIpcNotifyCoreIntrBitPos[coreId]);
    }

    return isPending;
}

static inline void IpcNotify_mailbox_asm(void)
{
/* ensure that all instructions and memory transactions, including cache operations, are completed
 * this is required to avoid any multi-core coherency issue since shared memory is being written/accessed
 */
#if defined(__aarch64__) || defined(__arm__)
    __asm__ __volatile__(
        "dsb sy"
        "\n\t"
        :
        :
        : "memory");
    __asm__ __volatile__(
        "isb"
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

#ifdef __cplusplus
}
#endif

#endif /* IPC_NOTIFY_V1_MAILBOX_H_ */
