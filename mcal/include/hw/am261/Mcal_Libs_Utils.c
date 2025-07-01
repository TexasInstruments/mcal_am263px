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
static void Mcal_Libs_Utils_MMR_lock(uint32 *kick0, uint32 *kick1)
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
    Mcal_Libs_Utils_MMR_lock(lock0, lock1);

    lock0 = (uint32 *)(&ctrlREG->LOCK0_KICK0);
    lock1 = (uint32 *)(&ctrlREG->LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_lock(lock0, lock1);
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
    Mcal_Libs_Utils_MMR_lock(lock0, lock1);
}
