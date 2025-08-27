/*
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Adc_Irq.h
 *
 *  \brief    This file contains ISR function declaration for ADC MCAL driver
 *
 */

/**
 *  \ingroup MCAL_ADC_API
 *  @{
 */

#ifndef ADC_IRQ_H_
#define ADC_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Adc.h"
#include "sys_common.h"
#if (ADC_ISR_TYPE == ADC_ISR_CAT2)
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

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/** \brief ADC ISR */

#if defined(ADC_INSTANCE_0)

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT1_IrqUnit0(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT1_IrqUnit0);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT2_IrqUnit0(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT2_IrqUnit0);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT3_IrqUnit0(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT3_IrqUnit0);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT4_IrqUnit0(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT4_IrqUnit0);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#endif /* ADC_INSTANCE_0 */

#if defined(ADC_INSTANCE_1)

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT1_IrqUnit1(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT1_IrqUnit1);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT2_IrqUnit1(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT2_IrqUnit1);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT3_IrqUnit1(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT3_IrqUnit1);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT4_IrqUnit1(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT4_IrqUnit1);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#endif /* ADC_INSTANCE_1 */

#if defined(ADC_INSTANCE_2)

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT1_IrqUnit2(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT1_IrqUnit2);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT2_IrqUnit2(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT2_IrqUnit2);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT3_IrqUnit2(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT3_IrqUnit2);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT4_IrqUnit2(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT4_IrqUnit2);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#endif /* ADC_INSTANCE_2 */

#if defined(ADC_INSTANCE_3)

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT1_IrqUnit3(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT1_IrqUnit3);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT2_IrqUnit3(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT2_IrqUnit3);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT3_IrqUnit3(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT3_IrqUnit3);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT4_IrqUnit3(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT4_IrqUnit3);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#endif /* ADC_INSTANCE_3 */

#if defined(ADC_INSTANCE_4)

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT1_IrqUnit4(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT1_IrqUnit4);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT2_IrqUnit4(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT2_IrqUnit4);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT3_IrqUnit4(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT3_IrqUnit4);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT4_IrqUnit4(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT4_IrqUnit4);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#endif /* ADC_INSTANCE_4 */

#if defined(ADC_INSTANCE_5)

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT1_IrqUnit5(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT1_IrqUnit5);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT2_IrqUnit5(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT2_IrqUnit5);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT3_IrqUnit5(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT3_IrqUnit5);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT4_IrqUnit5(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT4_IrqUnit5);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#endif /* ADC_INSTANCE_5 */

#if defined(ADC_INSTANCE_6)

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT1_IrqUnit6(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT1_IrqUnit6);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT2_IrqUnit6(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT2_IrqUnit6);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT3_IrqUnit6(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT3_IrqUnit6);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
FUNC(void, ADC_ISR_CODE) Adc_ADCINT4_IrqUnit6(void);

#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_ADCINT4_IrqUnit6);
#endif /* ((ADC_ISR_TYPE == ADC_ISR_CAT1).... */

#endif /* ADC_INSTANCE_6 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ADC_IRQ_H_ */

/* @} */
