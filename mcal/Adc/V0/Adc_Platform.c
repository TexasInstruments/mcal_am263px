/*
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
