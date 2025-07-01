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
 *  \file     Icu_Irq.h
 *
 *  \brief    This file contains ISR function declaration for ICU MCAL driver
 *
 */

/**
 *  \ingroup MCAL_ICU_API
 *  \defgroup MCAL_ICU_IRQ ICU Driver Interrupt Handlers
 *
 *  This file defines the interrupt handlers for all instance of timer/channels
 *  @{
 */

#ifndef ICU_IRQ_H_
#define ICU_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* Design : DES_ICU_006 */
/* Requirements : MCAL-3508 */
#include "Icu.h"
#include "sys_common.h"
#if (ICU_ISR_TYPE == ICU_ISR_CAT2)
#include "Os.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         GLOBAL VARIABLES                                   */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief ICU ISR
 */
FUNC(void, ICU_CODE_FAST) Icu_IntISR_Fun(Icu_ChannelType Icu_Channel);

#if defined(ICU_CHANNEL_0_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch0Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch0Notify);
#endif
#endif

#if defined(ICU_CHANNEL_1_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch1Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch1Notify);
#endif
#endif

#if defined(ICU_CHANNEL_2_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch2Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch2Notify);
#endif
#endif

#if defined(ICU_CHANNEL_3_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch3Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch3Notify);
#endif
#endif

#if defined(ICU_CHANNEL_4_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch4Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch4Notify);
#endif
#endif

#if defined(ICU_CHANNEL_5_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch5Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch5Notify);
#endif
#endif

#if defined(ICU_CHANNEL_6_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch6Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch6Notify);
#endif
#endif

#if defined(ICU_CHANNEL_7_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch7Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch7Notify);
#endif
#endif

#if defined(ICU_CHANNEL_8_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch8Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch8Notify);
#endif
#endif

#if defined(ICU_CHANNEL_9_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch9Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch9Notify);
#endif
#endif

#if defined(ICU_CHANNEL_10_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch10Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch10Notify);
#endif
#endif

#if defined(ICU_CHANNEL_11_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch11Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch11Notify);
#endif
#endif

#if defined(ICU_CHANNEL_12_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch12Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch12Notify);
#endif
#endif

#if defined(ICU_CHANNEL_13_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch13Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch13Notify);
#endif
#endif

#if defined(ICU_CHANNEL_14_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch14Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch14Notify);
#endif
#endif

#if defined(ICU_CHANNEL_15_ACTIVE)
#if ((ICU_ISR_TYPE == ICU_ISR_CAT1) || (ICU_ISR_TYPE == ICU_ISR_VOID))
void Icu_ch15Notify(void);
#elif (ICU_ISR_TYPE == ICU_ISR_CAT2)
ISR(Icu_ch15Notify);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ICU_IRQ_H_ */

/* @} */
