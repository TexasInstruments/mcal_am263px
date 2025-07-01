/*
 *
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Adc_Irq.c
 *
 *  \brief    This file contains the ISR implementation of ADC MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Adc_Priv.h"
#include "Adc_Platform.h"
#include "Adc_Irq.h"

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

#define ADC_START_SEC_ISR_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

/* Design : ADC_DesignId_004 */
/* Requirements : SWS_Adc_00078 */
#if (STD_ON == ADC_UNIT_1_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((ADC_ISR_TYPE == ADC_ISR_CAT1) || (ADC_ISR_TYPE == ADC_ISR_VOID))
/* CODE_STATE word allignment needed for R5 */

/*LDRA_INSPECTED 61 D : MISRAC_2012_R.8.8
 * "Reason - These are interface API's " */
FUNC(void, ADC_CODE_ISR) Adc_IFMDoneISR(void)
#elif (ADC_ISR_TYPE == ADC_ISR_CAT2)
ISR(Adc_IFMDoneISR)
#endif
{
    Adc_HwUnitObjType *hwUnitObj;

    hwUnitObj = Adc_getHwUnitObj(ADC_UNIT_1);
    if (hwUnitObj != NULL_PTR)
    {
        Adc_IFMDoneProcessing(hwUnitObj);
    }
}
#endif /* #if (STD_ON == ADC_UNIT_1_ACTIVE) */

#define ADC_STOP_SEC_ISR_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"
