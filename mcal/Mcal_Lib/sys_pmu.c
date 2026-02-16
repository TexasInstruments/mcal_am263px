/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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

#include "sys_pmu.h"

/* NOTE: CycleCounterP_getCount32 is implmented in sys_pmu_asm.asm */

#define PmuP_CYCLE_COUNTER_ENABLE_CLOCK_DIV64 0
#define MCAL_CYCLE_COUNTER_MAX_COUNT          (0xFFFFFFFFU)

#if PmuP_CYCLE_COUNTER_ENABLE_CLOCK_DIV64
#define PmuP_SETUP_COUNTER_DIVIDER_VAL      (64ULL)
#define PmuP_SETUP_FLAG_CYCLE_COUNTER_DIV64 (1u << 3u)

#else
#define PmuP_SETUP_COUNTER_DIVIDER_VAL      (1ULL)
#define PmuP_SETUP_FLAG_CYCLE_COUNTER_DIV64 (0u)

#endif

#define PmuP_SETUP_FLAG_CYCLE_COUNTER_RESET (1u << 2u)
#define PmuP_SETUP_FLAG_EVENT_COUNTER_RESET (1u << 1u)
#define PmuP_SETUP_FLAG_ENABLE_ALL_COUNTERS (1u << 0u)

#define PmuP_COUNTER_MASK_CYCLE_COUNTER ((uint32)1 << (uint32)31)
#define PmuP_COUNTER_MASK_ALL_COUNTERS  (0xFFFFFFFFu)
#define PmuP_SEC_TO_NANOSEC             (1000000000ULL)

void   PmuP_enableCounters(uint32 counterMask);
void   PmuP_disableCounters(uint32 counterMask);
void   PmuP_clearOverflowStatus(uint32 counterMask);
void   PmuP_setup(uint32 setupFlags);
uint32 CycleCounterP_getCount32();
uint32 PmuP_getOverflowStatus();

#define MCAL_LIB_START_SEC_CODE
#include "Mcal_Lib_MemMap.h"

void Mcal_pmuDelayUsec(volatile uint32 delayUsec, uint32 sysclkHz)
{
    uint32 startVal, currVal, elapsed;
    uint32 sysclkMHz   = (sysclkHz / 1000000UL);
    uint32 totalCycles = (delayUsec * sysclkMHz);
    uint32 maxCount    = 0xFFFFFFFF;

    Mcal_GetCycleCounterValue(&startVal);
    do
    {
        Mcal_GetCycleCounterValue(&currVal);
        if (currVal >= startVal)
        {
            elapsed = currVal - startVal;
        }
        else
        {
            elapsed = (maxCount - startVal) + currVal;
        }
    } while (elapsed < totalCycles);
}

void Mcal_pmuDelayMsec(volatile uint32 delayMsec, uint32 sysclkHz)
{
    Mcal_pmuDelayUsec(delayMsec * 1000U, sysclkHz);
}

void Mcal_pmuInit(void)
{
    Mcal_pmuResetCounters();
}

void Mcal_pmuEnableCountersGlobal(void)
{
    uint32 Counter_Mask = 7U;
    PmuP_enableCounters(Counter_Mask);
}

void Mcal_pmuDisableCountersGlobal(void)
{
    uint32 Counter_Mask = 7U;
    PmuP_disableCounters(Counter_Mask);
}

void Mcal_pmuResetCounters(void)
{
    uint32 setupFlags = 0;

    setupFlags |= PmuP_SETUP_FLAG_CYCLE_COUNTER_RESET;
    setupFlags |= PmuP_SETUP_FLAG_EVENT_COUNTER_RESET;
    setupFlags |= PmuP_SETUP_FLAG_ENABLE_ALL_COUNTERS;
    setupFlags |= PmuP_SETUP_FLAG_CYCLE_COUNTER_DIV64;

    PmuP_disableCounters(PmuP_COUNTER_MASK_ALL_COUNTERS);     /* disable all counters */
    PmuP_clearOverflowStatus(PmuP_COUNTER_MASK_ALL_COUNTERS); /* clear all overflow flags */
    PmuP_setup(setupFlags);                                   /* setup counters */
    PmuP_enableCounters(PmuP_COUNTER_MASK_CYCLE_COUNTER);     /* enable cycle counter only */
}

uint32 Mcal_CycleCounterP_getCount32(void)
{
    return CycleCounterP_getCount32();
}

uint32 Mcal_pmuGetOverflow(void)
{
    uint32 overflow_Status = 0;
    overflow_Status        = PmuP_getOverflowStatus();
    return overflow_Status;
}

void Mcal_GetCycleCounterValue(uint32 *Value)
{
    *Value = Mcal_CycleCounterP_getCount32();
}

void Mcal_GetElapsedCycleCountValue(uint32 *Value, uint32 *ElapsedValue)
{
    uint32 currVal;

    currVal = Mcal_CycleCounterP_getCount32();
    if (currVal < *Value)
    {
        /* Counter overflow occurred */
        currVal       = (MCAL_CYCLE_COUNTER_MAX_COUNT - *Value) + currVal + 1U;
        *ElapsedValue = currVal;
    }
    else
    {
        *ElapsedValue = currVal - *Value;
    }
    *Value = currVal;
}

#define MCAL_LIB_STOP_SEC_CODE
#include "Mcal_Lib_MemMap.h"
