/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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

#include "Adc_Platform.h"

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
/*****************************************************************************
 *
 * ADC_setMode
 *
 ******************************************************************************/
FUNC(void, ADC_CODE)
ADC_setMode(uint32 base, Adc_mcalResolution_t resolution, Adc_mcalSignalMode_t signalMode)
{
    /*
     * Apply the resolution and signalMode to the specified ADC.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCCTL2,
                ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCCTL2) &
                  ~(MCAL_CSL_ADC_ADCCTL2_RESOLUTION_MASK | MCAL_CSL_ADC_ADCCTL2_SIGNALMODE_MASK))) |
                    (((uint16)resolution << (uint16)MCAL_CSL_ADC_ADCCTL2_RESOLUTION_SHIFT) |
                     ((uint16)signalMode << (uint16)MCAL_CSL_ADC_ADCCTL2_SIGNALMODE_SHIFT)));
}

/*****************************************************************************
 *
 * ADC_setPPBTripLimits
 *
 ******************************************************************************/
FUNC(void, ADC_CODE)
ADC_setPPBTripLimits(uint32 base, Adc_mcalPPBNumber_t ppbNumber, sint32 tripHiLimit, sint32 tripLoLimit)
{
    uint32 ppbHiOffset;
    uint32 ppbLoOffset;

    /*
     * Check the arguments.
     */

    /*
     * Get the offset to the appropriate trip limit registers.
     */
    ppbHiOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1TRIPHI;
    ppbLoOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1TRIPLO;

    /*
     * Set the trip high limit.
     */
    HW_WR_REG32(base + ppbHiOffset, ((HW_RD_REG32(base + ppbHiOffset) & ~MCAL_ADC_ADCPPBTRIP_MASK) |
                                     ((uint32)tripHiLimit & MCAL_ADC_ADCPPBTRIP_MASK)));

    /*
     * Set the trip low limit.
     */
    HW_WR_REG32(base + ppbLoOffset, ((HW_RD_REG32(base + ppbLoOffset) & ~MCAL_ADC_ADCPPBTRIP_MASK) |
                                     ((uint32)tripLoLimit & MCAL_ADC_ADCPPBTRIP_MASK)));
}

#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
