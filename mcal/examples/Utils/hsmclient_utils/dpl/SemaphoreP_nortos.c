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

#include <string.h>
#include <HwiP.h>
// #include <kernel/dpl/ClockP.h>
#include <SemaphoreP.h>
#include "Compiler.h"

/**
 * \brief Semaphore type
 */
typedef enum SemaphoreP_Type_
{
    SemaphoreP_TYPE_BINARY,   /**< Binary semaphore */
    SemaphoreP_TYPE_COUNTING, /**< Counting semaphore */
    SemaphoreP_TYPE_MUTEX     /**< Mutual exclusion semaphore */
} SemaphoreP_Type;

/**
 * \brief Parameters passed during \ref SemaphoreP_construct
 */
typedef struct SemaphoreP_Params_
{
    uint32_t type;      /**< see \ref SemaphoreP_Type */
    uint32_t initCount; /**< initial value of the semaphore. \n
        Only valid for \ref SemaphoreP_TYPE_COUNTING and \ref SemaphoreP_TYPE_BINARY. \n
        MUST be 0 or 1 for \ref SemaphoreP_TYPE_BINARY \n
        Ignored for \ref SemaphoreP_TYPE_MUTEX */
    uint32_t maxCount;  /**< max value the semaphore can take. \n
         Only valid for \ref SemaphoreP_TYPE_COUNTING. \n
         MUST be >= SemaphoreP_Params.initCount \n
         Ignored for \ref SemaphoreP_TYPE_MUTEX and \ref SemaphoreP_TYPE_BINARY
         */

} SemaphoreP_Params;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void SemaphoreP_Params_init(SemaphoreP_Params *params);

int32_t SemaphoreP_construct(SemaphoreP_Object *pSemaphore, SemaphoreP_Params *params);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SemaphoreP_Params_init(SemaphoreP_Params *params)
{
    params->type      = (uint32_t)SemaphoreP_TYPE_BINARY;
    params->initCount = 0;
    params->maxCount  = 1;
}

int32_t SemaphoreP_construct(SemaphoreP_Object *pSemaphore, SemaphoreP_Params *params)
{
    int32_t status = SystemP_FAILURE;

    if (pSemaphore != NULL_PTR)
    {
        status = SystemP_SUCCESS;
    }

    if (status == SystemP_SUCCESS)
    {
        pSemaphore->type      = params->type;
        pSemaphore->count     = params->initCount;
        pSemaphore->maxCount  = params->maxCount;
        pSemaphore->nestCount = 0;
    }
    return SystemP_SUCCESS;
}

int32_t SemaphoreP_constructBinary(SemaphoreP_Object *pSemaphore, uint32_t initCount)
{
    SemaphoreP_Params params;

    SemaphoreP_Params_init(&params);
    params.type      = (uint32_t)SemaphoreP_TYPE_BINARY;
    params.initCount = (initCount & 0x1U);
    params.maxCount  = 1;

    return (SemaphoreP_construct(pSemaphore, &params));
}

int32_t SemaphoreP_constructCounting(SemaphoreP_Object *pSemaphore, uint32_t initCount, uint32_t maxCount)
{
    uint32_t          initialCount = initCount;
    uint32_t          maximumCount = maxCount;
    SemaphoreP_Params params;

    SemaphoreP_Params_init(&params);
    params.type = (uint32_t)SemaphoreP_TYPE_COUNTING;
    if (maximumCount == 0U)
    {
        maximumCount = 1;
    }
    if (initialCount > maxCount)
    {
        initialCount = maxCount;
    }
    params.initCount = initialCount;
    params.maxCount  = maximumCount;

    return (SemaphoreP_construct(pSemaphore, &params));
}

int32_t SemaphoreP_constructMutex(SemaphoreP_Object *pSemaphore)
{
    SemaphoreP_Params params;

    SemaphoreP_Params_init(&params);
    params.type      = (uint32_t)SemaphoreP_TYPE_MUTEX;
    params.initCount = 1;
    params.maxCount  = 1;

    return (SemaphoreP_construct(pSemaphore, &params));
}

void SemaphoreP_destruct(SemaphoreP_Object *pSemaphore)
{
    /* nothing to do */
}

int32_t SemaphoreP_pend(SemaphoreP_Object *pSemaphore, uint32_t timeout)
{
    // ClockP_Params      clockParams;
    // ClockP_Object      clockObj;
    uintptr_t key;
    int32_t   status = SystemP_FAILURE;

    if (pSemaphore != NULL_PTR)
    {
        status = SystemP_SUCCESS;
        // ClockP_Params_init(&clockParams);
        // clockParams.timeout = timeout;
        // (void)ClockP_construct(&clockObj, &clockParams);
        // if ((timeout != 0U) && (timeout !=(uint32_t)SystemP_WAIT_FOREVER)) {
        //     ClockP_start(&clockObj);
        // }
        key = HwiP_disable();
        while ((pSemaphore->count == 0U) && (pSemaphore->nestCount == 0U) && (timeout == SystemP_WAIT_FOREVER))
        {
            HwiP_restore(key);
            key = HwiP_disable();
        }
        if (pSemaphore->count > 0U)
        {
            (pSemaphore->count) = (pSemaphore->count) - 1U;
            if (pSemaphore->type == (uint32_t)SemaphoreP_TYPE_MUTEX)
            {
                pSemaphore->nestCount = pSemaphore->nestCount + 1U;
            }
            status = SystemP_SUCCESS;
        }
        else
        {
            if (pSemaphore->type == (uint32_t)SemaphoreP_TYPE_MUTEX)
            {
                pSemaphore->nestCount = pSemaphore->nestCount + 1U;
                status                = SystemP_SUCCESS;
            }
            else
            {
                status = SystemP_TIMEOUT;
            }
        }
        HwiP_restore(key);
        // ClockP_destruct(&clockObj);
    }

    return status;
}

void SemaphoreP_post(SemaphoreP_Object *pSemaphore)
{
    if (pSemaphore != NULL_PTR)
    {
        uintptr_t key;
        key = HwiP_disable();
        if (pSemaphore->count < pSemaphore->maxCount)
        {
            if (pSemaphore->type == (uint32_t)SemaphoreP_TYPE_MUTEX)
            {
                if (pSemaphore->nestCount > 0U)
                {
                    pSemaphore->nestCount = pSemaphore->nestCount - 1U;
                }
            }
            if (pSemaphore->nestCount == 0U)
            {
                pSemaphore->count = pSemaphore->count + 1U;
            }
        }
        HwiP_restore(key);
    }

    return;
}
