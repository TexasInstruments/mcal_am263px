/*
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Icu_Irq.c
 *
 *  \brief    This file contains the ISR implementation of ICU MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Icu.h"
#include "Icu_Irq.h"
#include "Icu_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  \brief ICU ISR
 */
#define ICU_START_SEC_ISR_CODE
#include "Icu_MemMap.h"
MCAL_INTERRUPT_ATTRIBUTE
void Icu_IntISR_Fun(Icu_ChannelType Icu_Channel)
{
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    uint32 baseAddr = Icu_GetBaseAddr(Icu_Channel);
    if (ICU_STATUS_INIT != Icu_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);
    }
    else
#endif
    {
        Icu_ChannelISR(Icu_Channel);
    }
}

#if defined(ICU_CHANNEL_0_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch0Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch0Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL0);
}
#endif

#if defined(ICU_CHANNEL_1_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch1Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch1Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL1);
}
#endif

#if defined(ICU_CHANNEL_2_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch2Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch2Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL2);
}
#endif

#if defined(ICU_CHANNEL_3_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch3Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch3Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL3);
}
#endif

#if defined(ICU_CHANNEL_4_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch4Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch4Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL4);
}
#endif

#if defined(ICU_CHANNEL_5_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch5Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch5Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL5);
}
#endif

#if defined(ICU_CHANNEL_6_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch6Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch6Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL6);
}
#endif

#if defined(ICU_CHANNEL_7_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch7Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch7Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL7);
}
#endif

#if defined(ICU_CHANNEL_8_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch8Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch8Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL8);
}
#endif

#if defined(ICU_CHANNEL_9_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch9Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch9Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL9);
}
#endif

#if defined(ICU_CHANNEL_10_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch10Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch10Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL10);
}
#endif

#if defined(ICU_CHANNEL_11_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch11Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch11Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL11);
}
#endif

#if defined(ICU_CHANNEL_12_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch12Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch12Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL12);
}
#endif

#if defined(ICU_CHANNEL_13_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch13Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch13Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL13);
}
#endif

#if defined(ICU_CHANNEL_14_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch14Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch14Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL14);
}
#endif

#if defined(ICU_CHANNEL_15_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch15Notify(void)
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch15Notify)
#endif
{
    Icu_IntISR_Fun(ICU_CHANNEL15);
}
#endif

#define ICU_STOP_SEC_ISR_CODE
#include "Icu_MemMap.h"
