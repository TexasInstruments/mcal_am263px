/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Pwm_Irq.h
 *
 *  \brief    This file contains ISR function declaration for PWM MCAL driver
 *
 */

/**
 *  \ingroup MCAL_PWM_API
 *  \defgroup MCAL_PWM_IRQ Pwm Driver Interrupt Handlers
 *
 *  This file defines the interrupt handlers for all instance of timer/channels
 *  @{
 */

#ifndef PWM_IRQ_H_
#define PWM_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Pwm.h"
#include "sys_common.h"
#if (PWM_ISR_TYPE == PWM_ISR_CAT2)
#include "Os.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

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
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch0Isr(void);
void Pwm_Ch1Isr(void);
void Pwm_Ch2Isr(void);
void Pwm_Ch3Isr(void);
void Pwm_Ch4Isr(void);
void Pwm_Ch5Isr(void);
void Pwm_Ch6Isr(void);
void Pwm_Ch7Isr(void);
void Pwm_Ch8Isr(void);
void Pwm_Ch9Isr(void);
void Pwm_Ch10Isr(void);
void Pwm_Ch11Isr(void);
void Pwm_Ch12Isr(void);
void Pwm_Ch13Isr(void);
void Pwm_Ch14Isr(void);
void Pwm_Ch15Isr(void);
void Pwm_Ch16Isr(void);
void Pwm_Ch17Isr(void);
void Pwm_Ch18Isr(void);
void Pwm_Ch19Isr(void);

#if !defined(AM261X_PLATFORM)

void Pwm_Ch20Isr(void);
void Pwm_Ch21Isr(void);
void Pwm_Ch22Isr(void);
void Pwm_Ch23Isr(void);
void Pwm_Ch24Isr(void);
void Pwm_Ch25Isr(void);
void Pwm_Ch26Isr(void);
void Pwm_Ch27Isr(void);
void Pwm_Ch28Isr(void);
void Pwm_Ch29Isr(void);
void Pwm_Ch30Isr(void);
void Pwm_Ch31Isr(void);
void Pwm_Ch32Isr(void);
void Pwm_Ch33Isr(void);
void Pwm_Ch34Isr(void);
void Pwm_Ch35Isr(void);
void Pwm_Ch36Isr(void);
void Pwm_Ch37Isr(void);
void Pwm_Ch38Isr(void);
void Pwm_Ch39Isr(void);
void Pwm_Ch40Isr(void);
void Pwm_Ch41Isr(void);
void Pwm_Ch42Isr(void);
void Pwm_Ch43Isr(void);
void Pwm_Ch44Isr(void);
void Pwm_Ch45Isr(void);
void Pwm_Ch46Isr(void);
void Pwm_Ch47Isr(void);
void Pwm_Ch48Isr(void);
void Pwm_Ch49Isr(void);
void Pwm_Ch50Isr(void);
void Pwm_Ch51Isr(void);
void Pwm_Ch52Isr(void);
void Pwm_Ch53Isr(void);
void Pwm_Ch54Isr(void);
void Pwm_Ch55Isr(void);
void Pwm_Ch56Isr(void);
void Pwm_Ch57Isr(void);
void Pwm_Ch58Isr(void);
void Pwm_Ch59Isr(void);
void Pwm_Ch60Isr(void);
void Pwm_Ch61Isr(void);
void Pwm_Ch62Isr(void);
void Pwm_Ch63Isr(void);
void Pwm_Ch64Isr(void);
void Pwm_Ch65Isr(void);
void Pwm_Ch66Isr(void);
void Pwm_Ch67Isr(void);
void Pwm_Ch68Isr(void);
void Pwm_Ch69Isr(void);
void Pwm_Ch70Isr(void);
void Pwm_Ch71Isr(void);
void Pwm_Ch72Isr(void);
void Pwm_Ch73Isr(void);
void Pwm_Ch74Isr(void);
void Pwm_Ch75Isr(void);
void Pwm_Ch76Isr(void);
void Pwm_Ch77Isr(void);
void Pwm_Ch78Isr(void);
void Pwm_Ch79Isr(void);
void Pwm_Ch80Isr(void);
void Pwm_Ch81Isr(void);
void Pwm_Ch82Isr(void);
void Pwm_Ch83Isr(void);
void Pwm_Ch84Isr(void);
void Pwm_Ch85Isr(void);
void Pwm_Ch86Isr(void);
void Pwm_Ch87Isr(void);
void Pwm_Ch88Isr(void);
void Pwm_Ch89Isr(void);
void Pwm_Ch90Isr(void);
void Pwm_Ch91Isr(void);
void Pwm_Ch92Isr(void);
void Pwm_Ch93Isr(void);
void Pwm_Ch94Isr(void);
void Pwm_Ch95Isr(void);
void Pwm_Ch96Isr(void);
void Pwm_Ch97Isr(void);
void Pwm_Ch98Isr(void);
void Pwm_Ch99Isr(void);
void Pwm_Ch100Isr(void);
void Pwm_Ch101Isr(void);
void Pwm_Ch102Isr(void);
void Pwm_Ch103Isr(void);
void Pwm_Ch104Isr(void);
void Pwm_Ch105Isr(void);
void Pwm_Ch106Isr(void);
void Pwm_Ch107Isr(void);
void Pwm_Ch108Isr(void);
void Pwm_Ch109Isr(void);
void Pwm_Ch110Isr(void);
void Pwm_Ch111Isr(void);
void Pwm_Ch112Isr(void);
void Pwm_Ch113Isr(void);
void Pwm_Ch114Isr(void);
void Pwm_Ch115Isr(void);
void Pwm_Ch116Isr(void);
void Pwm_Ch117Isr(void);
void Pwm_Ch118Isr(void);
void Pwm_Ch119Isr(void);
void Pwm_Ch120Isr(void);
void Pwm_Ch121Isr(void);
void Pwm_Ch122Isr(void);
void Pwm_Ch123Isr(void);
void Pwm_Ch124Isr(void);
void Pwm_Ch125Isr(void);
void Pwm_Ch126Isr(void);
void Pwm_Ch127Isr(void);
#endif

#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch0Isr);
ISR(Pwm_Ch1Isr);
ISR(Pwm_Ch2Isr);
ISR(Pwm_Ch3Isr);
ISR(Pwm_Ch4Isr);
ISR(Pwm_Ch5Isr);
ISR(Pwm_Ch6Isr);
ISR(Pwm_Ch7Isr);
ISR(Pwm_Ch8Isr);
ISR(Pwm_Ch9Isr);
ISR(Pwm_Ch10Isr);
ISR(Pwm_Ch11Isr);
ISR(Pwm_Ch12Isr);
ISR(Pwm_Ch13Isr);
ISR(Pwm_Ch14Isr);
ISR(Pwm_Ch15Isr);
ISR(Pwm_Ch16Isr);
ISR(Pwm_Ch17Isr);
ISR(Pwm_Ch18Isr);
ISR(Pwm_Ch19Isr);

#if !defined(AM261X_PLATFORM)

ISR(Pwm_Ch20Isr);
ISR(Pwm_Ch21Isr);
ISR(Pwm_Ch22Isr);
ISR(Pwm_Ch23Isr);
ISR(Pwm_Ch24Isr);
ISR(Pwm_Ch25Isr);
ISR(Pwm_Ch26Isr);
ISR(Pwm_Ch27Isr);
ISR(Pwm_Ch28Isr);
ISR(Pwm_Ch29Isr);
ISR(Pwm_Ch30Isr);
ISR(Pwm_Ch31Isr);
ISR(Pwm_Ch32Isr);
ISR(Pwm_Ch33Isr);
ISR(Pwm_Ch34Isr);
ISR(Pwm_Ch35Isr);
ISR(Pwm_Ch36Isr);
ISR(Pwm_Ch37Isr);
ISR(Pwm_Ch38Isr);
ISR(Pwm_Ch39Isr);
ISR(Pwm_Ch40Isr);
ISR(Pwm_Ch41Isr);
ISR(Pwm_Ch42Isr);
ISR(Pwm_Ch43Isr);
ISR(Pwm_Ch44Isr);
ISR(Pwm_Ch45Isr);
ISR(Pwm_Ch46Isr);
ISR(Pwm_Ch47Isr);
ISR(Pwm_Ch48Isr);
ISR(Pwm_Ch49Isr);
ISR(Pwm_Ch50Isr);
ISR(Pwm_Ch51Isr);
ISR(Pwm_Ch52Isr);
ISR(Pwm_Ch53Isr);
ISR(Pwm_Ch54Isr);
ISR(Pwm_Ch55Isr);
ISR(Pwm_Ch56Isr);
ISR(Pwm_Ch57Isr);
ISR(Pwm_Ch58Isr);
ISR(Pwm_Ch59Isr);
ISR(Pwm_Ch60Isr);
ISR(Pwm_Ch61Isr);
ISR(Pwm_Ch62Isr);
ISR(Pwm_Ch63Isr);
ISR(Pwm_Ch64Isr);
ISR(Pwm_Ch65Isr);
ISR(Pwm_Ch66Isr);
ISR(Pwm_Ch67Isr);
ISR(Pwm_Ch68Isr);
ISR(Pwm_Ch69Isr);
ISR(Pwm_Ch70Isr);
ISR(Pwm_Ch71Isr);
ISR(Pwm_Ch72Isr);
ISR(Pwm_Ch73Isr);
ISR(Pwm_Ch74Isr);
ISR(Pwm_Ch75Isr);
ISR(Pwm_Ch76Isr);
ISR(Pwm_Ch77Isr);
ISR(Pwm_Ch78Isr);
ISR(Pwm_Ch79Isr);
ISR(Pwm_Ch80Isr);
ISR(Pwm_Ch81Isr);
ISR(Pwm_Ch82Isr);
ISR(Pwm_Ch83Isr);
ISR(Pwm_Ch84Isr);
ISR(Pwm_Ch85Isr);
ISR(Pwm_Ch86Isr);
ISR(Pwm_Ch87Isr);
ISR(Pwm_Ch88Isr);
ISR(Pwm_Ch89Isr);
ISR(Pwm_Ch90Isr);
ISR(Pwm_Ch91Isr);
ISR(Pwm_Ch92Isr);
ISR(Pwm_Ch93Isr);
ISR(Pwm_Ch94Isr);
ISR(Pwm_Ch95Isr);
ISR(Pwm_Ch96Isr);
ISR(Pwm_Ch97Isr);
ISR(Pwm_Ch98Isr);
ISR(Pwm_Ch99Isr);
ISR(Pwm_Ch100Isr);
ISR(Pwm_Ch101Isr);
ISR(Pwm_Ch102Isr);
ISR(Pwm_Ch103Isr);
ISR(Pwm_Ch104Isr);
ISR(Pwm_Ch105Isr);
ISR(Pwm_Ch106Isr);
ISR(Pwm_Ch107Isr);
ISR(Pwm_Ch108Isr);
ISR(Pwm_Ch109Isr);
ISR(Pwm_Ch110Isr);
ISR(Pwm_Ch111Isr);
ISR(Pwm_Ch112Isr);
ISR(Pwm_Ch113Isr);
ISR(Pwm_Ch114Isr);
ISR(Pwm_Ch115Isr);
ISR(Pwm_Ch116Isr);
ISR(Pwm_Ch117Isr);
ISR(Pwm_Ch118Isr);
ISR(Pwm_Ch119Isr);
ISR(Pwm_Ch120Isr);
ISR(Pwm_Ch121Isr);
ISR(Pwm_Ch122Isr);
ISR(Pwm_Ch123Isr);
ISR(Pwm_Ch124Isr);
ISR(Pwm_Ch125Isr);
ISR(Pwm_Ch126Isr);
ISR(Pwm_Ch127Isr);

#endif

#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PWM_IRQ_H_ */

/* @} */
