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

#include "Mcal_Libs_Utils.h"

static void Mcu_MMR_lock(uint32 *kick0, uint32 *kick1);
static void Mcal_Libs_Utils_MMR_unlock(uint32 *kick0, uint32 *kick1);

void Mcal_CacheP_inv(void *blockPtr, uint32 byteCnt, uint32 type)
{
    if (type & Mcal_CacheP_TYPE_L1P) {
        Mcal_CacheP_invL1p((uint32)blockPtr, byteCnt);
    }
    if (((type) & ((uint32)Mcal_CacheP_TYPE_L1D))!=0U) {
        Mcal_CacheP_invL1d((uint32)blockPtr, byteCnt);
    }
}

/* MMR Unlock Functions */
static void Mcal_Libs_Utils_MMR_unlock(uint32 *kick0, uint32 *kick1)
{
    *kick0 = KICK0_UNLOCK_VAL_MCU;
    *kick1 = KICK1_UNLOCK_VAL_MCU;
}

/**
 * \brief  Unlocks MMR registers
 */
void Mcal_Libs_Utils_unlockMMR(void)
{
    uint32 *lock0;
    uint32 *lock1;

    Mcal_Libs_Utils_unlockTopRcmMMR();

    lock0 = (uint32 *)(&mssrcmREG->RCM_LOCK0_KICK0);
    lock1 = (uint32 *)(&mssrcmREG->RCM_LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_unlock(lock0, lock1);

    lock0 = (uint32 *)(&ctrlREG->LOCK0_KICK0);
    lock1 = (uint32 *)(&ctrlREG->LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_unlock(lock0, lock1);
}

/**
 * \brief  Unlocks TOP RCM MMR registers
 */
void Mcal_Libs_Utils_unlockTopRcmMMR(void)
{
    uint32 *lock0;
    uint32 *lock1;

    lock0 = (uint32 *)(&toprcmREG->LOCK0_KICK0);
    lock1 = (uint32 *)(&toprcmREG->LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_unlock(lock0, lock1);
}

/* MMR lock Functions */
static void Mcu_MMR_lock(uint32 *kick0, uint32 *kick1)
{
    *kick0 = KICK0_LOCK_VAL_MCU;
    *kick1 = KICK1_LOCK_VAL_MCU;
}

/**
 * \brief Locks MMR registers
 */
void Mcal_Libs_Utils_lockMMR(void)
{
    uint32 *lock0;
    uint32 *lock1;

    Mcal_Libs_Utils_lockTopRcmMMR();

    lock0 = (uint32 *)(&mssrcmREG->RCM_LOCK0_KICK0);
    lock1 = (uint32 *)(&mssrcmREG->RCM_LOCK0_KICK1);
    Mcu_MMR_lock(lock0, lock1);

    lock0 = (uint32 *)(&ctrlREG->LOCK0_KICK0);
    lock1 = (uint32 *)(&ctrlREG->LOCK0_KICK1);
    Mcu_MMR_lock(lock0, lock1);
}

/**
 * \brief Locks TOP RCM MMR registers
 */
void Mcal_Libs_Utils_lockTopRcmMMR(void)
{
    uint32 *lock0;
    uint32 *lock1;

    lock0 = (uint32 *)(&toprcmREG->LOCK0_KICK0);
    lock1 = (uint32 *)(&toprcmREG->LOCK0_KICK1);
    Mcu_MMR_lock(lock0, lock1);
}

/* =========================Function separator========================= */
/* FUNCTION DEF: void Mcal_CacheP_invL1p(uint32 blockPtr, uint32 byteCnt)
 *
 *       r0 - contains blockPtr
 *       r1 - contains byteCnt
 */
        asm(".global Mcal_CacheP_invL1p         ");
        asm(".type Mcal_CacheP_invL1p,%function ");
        asm(".arm                          ");
        asm(".align 2                      ");
asm("Mcal_CacheP_invL1p:");
        asm("push    {r4}                      ");
        asm("add     r1, r0, r1                "); // calculate last address
        asm("mov     r3, #32  ");
        asm("sub     r4, r3, #1                ");
        asm("bic     r0, r0, r4                ");     // align blockPtr to cache line
asm("invL1pCache_loop:");
        asm("mcr     p15, #0, r0, c7, c5, #1 ");// invalidate single entry in ICache
        asm("add     r0, r0, r3              ");// increment address by cache line size
        asm("cmp     r0, r1                  ");// compare to last address
        asm("blo     invL1pCache_loop        ");// loop if > 0
        asm("dsb                             ");// drain write buffer
        asm("isb                             ");// flush instruction pipeline
        asm("pop     {r4}                    ");
        asm("bx      lr                      ");

/* =========================Function separator========================= */

/* FUNCTION DEF: void Mcal_CacheP_invL1d(uint32 blockPtr, uint32 byteCnt)
 *
 *       r0 - contains blockPtr
 *       r1 - contains byteCnt
 */
        asm(".global Mcal_CacheP_invL1d");
        asm(".type Mcal_CacheP_invL1d,%function");
        asm(".arm");
asm("Mcal_CacheP_invL1d:");
        asm("push    {r4}");
        asm("add     r1, r0, r1");    // calculate last address
        asm("mov     r3, #32");
        asm("sub     r4, r3, #1");
        asm("bic     r0, r0, r4");         // align blockPtr to cache line
asm("invL1dCache_loop:");
        asm("mcr     p15, #0, r0, c7, c6, #1"); // writeback inv a cache line
        asm("add     r0, r0, r3");      // increment address by cache line size
        asm("cmp     r0, r1");                // compare to last address
        asm(" blo     invL1dCache_loop");             // loop if count > 0
        asm("dsb");                              // drain write buffer
        asm("pop     {r4}");
        asm("bx      lr");
