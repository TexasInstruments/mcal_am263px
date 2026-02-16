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

#include "Mcal_Libs_Utils.h"

static void Mcu_MMR_lock(volatile uint32 *kick0, volatile uint32 *kick1);
static void Mcal_Libs_Utils_MMR_unlock(volatile uint32 *kick0, volatile uint32 *kick1);

#define MCAL_LIB_START_SEC_CODE
#include "Mcal_Lib_MemMap.h"

/* MMR Unlock Functions */
static void Mcal_Libs_Utils_MMR_unlock(volatile uint32 *kick0, volatile uint32 *kick1)
{
    *kick0 = KICK0_UNLOCK_VAL_MCU;
    *kick1 = KICK1_UNLOCK_VAL_MCU;
}

/**
 * \brief  Unlocks MMR registers
 */
void Mcal_Libs_Utils_unlockMMR(void)
{
    volatile uint32 *lock0;
    volatile uint32 *lock1;

    Mcal_Libs_Utils_unlockTopRcmMMR();

    lock0 = (volatile uint32 *)(&mssrcmREG->RCM_LOCK0_KICK0);
    lock1 = (volatile uint32 *)(&mssrcmREG->RCM_LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_unlock(lock0, lock1);

    lock0 = (volatile uint32 *)(&ctrlREG->LOCK0_KICK0);
    lock1 = (volatile uint32 *)(&ctrlREG->LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_unlock(lock0, lock1);
}

/**
 * \brief  Unlocks TOP RCM MMR registers
 */
void Mcal_Libs_Utils_unlockTopRcmMMR(void)
{
    volatile uint32 *lock0;
    volatile uint32 *lock1;

    lock0 = (volatile uint32 *)(&toprcmREG->LOCK0_KICK0);
    lock1 = (volatile uint32 *)(&toprcmREG->LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_unlock(lock0, lock1);
}

/* MMR lock Functions */
static void Mcal_Libs_Utils_MMR_lock(volatile uint32 *kick0, volatile uint32 *kick1)
{
    *kick0 = KICK0_LOCK_VAL_MCU;
    *kick1 = KICK1_LOCK_VAL_MCU;
}

/**
 * \brief Locks MMR registers
 */
void Mcal_Libs_Utils_lockMMR(void)
{
    volatile uint32 *lock0;
    volatile uint32 *lock1;

    Mcal_Libs_Utils_lockTopRcmMMR();

    lock0 = (volatile uint32 *)(&mssrcmREG->RCM_LOCK0_KICK0);
    lock1 = (volatile uint32 *)(&mssrcmREG->RCM_LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_lock(lock0, lock1);

    lock0 = (volatile uint32 *)(&ctrlREG->LOCK0_KICK0);
    lock1 = (volatile uint32 *)(&ctrlREG->LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_lock(lock0, lock1);
}

/**
 * \brief Locks TOP RCM MMR registers
 */
void Mcal_Libs_Utils_lockTopRcmMMR(void)
{
    volatile uint32 *lock0;
    volatile uint32 *lock1;

    lock0 = (volatile uint32 *)(&toprcmREG->LOCK0_KICK0);
    lock1 = (volatile uint32 *)(&toprcmREG->LOCK0_KICK1);
    Mcal_Libs_Utils_MMR_lock(lock0, lock1);
}

#define MCAL_LIB_STOP_SEC_CODE
#include "Mcal_Lib_MemMap.h"
