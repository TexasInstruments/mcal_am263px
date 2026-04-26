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

#ifndef SIPC_NOTIFY_MAILBOX_H_
#define SIPC_NOTIFY_MAILBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* this file has define's and inline function's to program the HW mailbox registers and SW queue structure */
#define MAILBOX_MAX_SW_QUEUE_STRUCT_SIZE (sizeof(SIPC_SwQueue))

/* The HW mailbox only allows to trigger a interrupt on another core,
 * the SIPC Notify needs ability to pass x byte message along with a interrupt
 *
 * Basically this mimics the functionality of HW mailbox with HW FIFO in AM243x SOC
 *
 * This needs to be in sync with the addresses being set for SW queue memory in soc/{soc}/sipc_notify_cfg.c
 *
 * The new queue has two more parameters i.e EleSize = Size of 1 queue element in words
 * Qlength = total length of this Queue */

/**
 * @brief
 * @ingroup DRV_SIPC_NOTIFY_MODULE
 *  SIPC swQ structure which holds the data pointer to a fifo Queue in HSM MBOX memory.
 */
typedef struct SIPC_SwQueue_
{
    uint32_t rdIdx;   /**<queue element will be read from this index.*/
    uint32_t wrIdx;   /**<queue element will be written to this index.*/
    uint16_t EleSize; /**<Element size in words this will be a fixed parameter */
    uint16_t Qlength; /**<total number of elements */
    uint8_t *Qfifo;   /**Pointer to the FIFO queue in HSM MBOX memory */
} SIPC_SwQueue;

#if defined(__aarch64__) || defined(__arm__)
static inline void asm_dsb_memory(void)
{
    __asm__ __volatile__(
        "dsb sy"
        "\n\t"
        :
        :
        : "memory");
}

static inline void asm_isb_memory(void)
{
    __asm__ __volatile__(
        "isb"
        "\n\t"
        :
        :
        : "memory");
}
#endif

/* Read from SW fifo within a mailbox  */
static inline int32_t SIPC_mailboxRead(SIPC_SwQueue *swQ, uint8_t *Buff)
{
    int32_t status = SystemP_FAILURE;

    /* MISRA-C:2012 Rule 13.5 - Read volatile variables once to avoid side effects in logical expressions */
    uint32_t rdIdx   = swQ->rdIdx;
    uint32_t wrIdx   = swQ->wrIdx;
    uint16_t qLength = swQ->Qlength;
    uint32_t rdIdxValid;
    uint32_t wrIdxValid;

    rdIdxValid = (rdIdx < qLength) ? 1U : 0U;
    wrIdxValid = (wrIdx < qLength) ? 1U : 0U;

    if ((rdIdxValid != 0U) && (wrIdxValid != 0U))
    {
        /* If this condition meets then it means there is something in the fifo*/
        if (rdIdx != wrIdx)
        {
            /* MISRA-C:2012 Rule 18.4, Rule 21.16 - Calculate offset without pointer arithmetic, use byte copy */
            uint32_t       offset  = (uint32_t)swQ->EleSize * rdIdx;
            uint8_t const *srcPtr  = &swQ->Qfifo[offset];
            void const    *phyAddr = SOC_phyToVirt((uint64_t)srcPtr);
            (void)memcpy((void *)Buff, phyAddr, (size_t)swQ->EleSize);

            rdIdx = (rdIdx + 1U) % swQ->Qlength;

            swQ->rdIdx = rdIdx;

            rdIdx = swQ->rdIdx; /* read back to ensure the update has reached the memory */

#if defined(__aarch64__) || defined(__arm__)
            asm_dsb_memory();
            asm_isb_memory();
#endif

            status = SystemP_SUCCESS;
        }
    }

    return status;
}

/* Write to SW fifo and trigger HW interrupt using HW mailbox */
static inline int32_t SIPC_mailboxWrite(uint32_t mailboxBaseAddr, uint32_t wrIntrBitPos, SIPC_SwQueue *swQ,
                                        uint8_t *Buff)
{
    int32_t status = SystemP_FAILURE;

    /* MISRA-C:2012 Rule 13.5 - Read volatile variables once to avoid side effects in logical expressions */
    uint32_t rdIdx   = swQ->rdIdx;
    uint32_t wrIdx   = swQ->wrIdx;
    uint16_t qLength = swQ->Qlength;
    uint32_t rdIdxValid;
    uint32_t wrIdxValid;

    rdIdxValid = (rdIdx < qLength) ? 1U : 0U;
    wrIdxValid = (wrIdx < qLength) ? 1U : 0U;

    if ((rdIdxValid != 0U) && (wrIdxValid != 0U))
    {
        if (((wrIdx + 1U) % swQ->Qlength) != rdIdx)
        {
            volatile uint32_t *addr = (uint32_t *)mailboxBaseAddr;

            /* There is some space in the FIFO */
            /* MISRA-C:2012 Rule 18.4, Rule 21.16 - Calculate offset without pointer arithmetic, use byte copy */
            uint32_t offset  = (uint32_t)swQ->EleSize * wrIdx;
            uint8_t *dstPtr  = &swQ->Qfifo[offset];
            void    *phyAddr = SOC_phyToVirt((uint64_t)dstPtr);
            (void)memcpy(phyAddr, (void const *)Buff, (size_t)swQ->EleSize);

            wrIdx = (wrIdx + 1U) % swQ->Qlength;

            swQ->wrIdx = wrIdx;

            wrIdx = swQ->wrIdx; /* read back to ensure the update has reached the memory */

#if defined(__aarch64__) || defined(__arm__)
            asm_dsb_memory();
            asm_isb_memory();
#endif

            /* Trigger interrupt to other core */
            /* MISRA-C:2012 Rule 10.8 - Ensure shift result matches target type width */
            *addr = ((uint32_t)1 << wrIntrBitPos);

            status = SystemP_SUCCESS;
        }
    }
    return status;
}

static inline void SIPC_mailboxClearAllInt(uint32_t mailboxBaseAddr)
{
    volatile uint32_t *addr = (uint32_t *)mailboxBaseAddr;
    *addr                   = 0x1111111U;
}

static inline uint32_t SIPC_mailboxGetPendingIntr(uint32_t mailboxBaseAddr)
{
    volatile uint32_t *addr = (uint32_t *)mailboxBaseAddr;

    return *addr;
}

static inline void SIPC_mailboxClearPendingIntr(uint32_t mailboxBaseAddr, uint32_t pendingIntr)
{
    volatile uint32_t *addr = (uint32_t *)mailboxBaseAddr;
    *addr                   = pendingIntr;
}

/** Maximum number of cores (matches CORE_ID_MAX from sipc_notify_cfg.h) */
#ifndef SIPC_MAX_CORES
#define SIPC_MAX_CORES (5U)
#endif

static inline uint32_t SIPC_mailboxIsPendingIntr(uint32_t pendingIntr, uint32_t coreId)
{
    extern uint32_t gSIPCCoreIntrBitPos[SIPC_MAX_CORES];

    uint32_t isPending = 0U;
    isPending          = pendingIntr & (1U << (uint32_t)gSIPCCoreIntrBitPos[coreId]);
    return isPending;
}

#ifdef __cplusplus
}
#endif

#endif /*SIPC_NOTIFY_MAILBOX_H_*/
