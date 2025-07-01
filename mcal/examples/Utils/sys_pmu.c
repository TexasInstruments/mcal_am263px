/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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

#include "sys_pmu.h"

/* NOTE: CycleCounterP_getCount32 is implmented in sys_pmu_asm.asm */

#define PmuP_CYCLE_COUNTER_ENABLE_CLOCK_DIV64 0

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
