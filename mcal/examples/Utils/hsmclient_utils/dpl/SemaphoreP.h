/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2018-2021 Texas Instruments Incorporated
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

#ifndef SEMAPHOREP_H
#define SEMAPHOREP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <SystemP.h>

/**
 * \defgroup KERNEL_DPL_SEMAPHORE APIs for Semaphore
 * \ingroup KERNEL_DPL
 *
 * For more details and example usage, see \ref KERNEL_DPL_SEMAPHORE_PAGE
 *
 * @{
 */

/**
 * \brief Semaphore object for NoRTOS
 */
typedef struct SemaphoreP_Object_
{
    uint32_t          type;
    uint32_t          maxCount;
    volatile uint32_t count;
    volatile uint32_t nestCount;
} SemaphoreP_Object;

/**
 * \brief Create a mutex semaphore object
 *
 * \param obj [out] created object
 *
 * \return \ref SystemP_SUCCESS on success, \ref SystemP_FAILURE on error
 */
int32_t SemaphoreP_constructMutex(SemaphoreP_Object *obj);

/**
 * \brief Create a binary semaphore object
 *
 * \param obj [out] created object
 * \param initValue [in] Initial value of the binary semaphore, MUST be 0 or 1
 *
 * \return \ref SystemP_SUCCESS on success, \ref SystemP_FAILURE on error
 */
int32_t SemaphoreP_constructBinary(SemaphoreP_Object *obj, uint32_t initValue);

/**
 * \brief Create a counting semaphore object
 *
 * \param obj [out] created object
 * \param initValue [in] Initial value of the counting semaphore, MUST be between 0 .. maxValue
 * \param maxValue [in] Maximum value of counting semaphore
 *
 * \return \ref SystemP_SUCCESS on success, \ref SystemP_FAILURE on error
 */
int32_t SemaphoreP_constructCounting(SemaphoreP_Object *obj, uint32_t initValue, uint32_t maxValue);

/**
 * \brief Cleanup, delete, destruct a semaphore object
 *
 * \param obj [in] semaphore object
 */
void SemaphoreP_destruct(SemaphoreP_Object *obj);

/**
 * \brief Post a semaphore object or unlock a mutex
 *
 * \param obj [in] semaphore object
 */
void SemaphoreP_post(SemaphoreP_Object *obj);

/**
 * \brief Pend on a semaphore object or lock a mutex
 *
 * \param obj [in] semaphore object
 * \param timeToWaitInTicks [in] amount of time to block waiting for semaphore to be available, in units of system ticks
 * (see \ref KERNEL_DPL_CLOCK_PAGE)
 *
 * \return \ref SystemP_SUCCESS on successful acquire of the semaphore
 * \return \ref SystemP_TIMEOUT on failure to acquire the semaphore due to timeout condition
 * \return \ref SystemP_FAILURE on failure to acquire the semaphore due to other conditions
 */
int32_t SemaphoreP_pend(SemaphoreP_Object *obj, uint32_t timeToWaitInTicks);

/*!
 *  @brief  Function to return the count of a semaphore.
 *
 *  @param  obj  A SemaphoreP_Handle
 *
 *  @return The count of the semaphore
 */

int32_t SemaphoreP_getCount(SemaphoreP_Object *obj);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* SEMAPHOREP_H */
