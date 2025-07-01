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
 *   \file Adc_Temp.c
 *
 *   \brief The file implements the Platform specific Temperature sensors
 *          readout
 */

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************
 */
#include "Adc.h"
#include "Adc_Temp.h"
#include "hw_adc.h"
#include "hw_ctrl_core.h"
#include "hw_types.h"

/******************************************************************************
 * GLOBAL VARIABLES/DATA-TYPES DEFINITIONS
 ******************************************************************************
 */

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"
static VAR(Adc_TempSensTrimType, ADC_VAR_NO_INIT) tempSensTrimSlopeValues;
static VAR(Adc_EfuseTempTrimType, ADC_VAR_NO_INIT) efuseTempTrimValues;
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

#define TS_SE_INP_BUF_EN_ENABLE    (1U)
#define TS_DIFF_INP_BUF_EN_DISABLE (0U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static uint16  Adc_EfuseExtractTrims(volatile uint32 reg, uint8 msb, uint8 lsb);
static float32 Adc_calculateTemp(uint16 adcTempCode, uint8 index);
static void    Adc_computeTempSlope(void);

/******************************************************************************
 * FUNCTION DEFINITIONS
 ******************************************************************************
 */
#define ADC_START_SEC_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

void Adc_InitTemp(void)
{
    sint16 trimTemp;
    uint32 regVal;
    regVal = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_14_ADDR_OFFSET);
    efuseTempTrimValues.FuseROMVer =
        Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_14_FUSEROM_VER_STOP_BIT, EFUSE1_ROW_14_FUSEROM_VER_START_BIT);

    regVal                                = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_39_ADDR_OFFSET);
    efuseTempTrimValues.TrimPrecisionTemp = Adc_EfuseExtractTrims(
        regVal, EFUSE1_ROW_39_TRIM_PRECISION_TEMPERATURE_STOP_BIT, EFUSE1_ROW_39_TRIM_PRECISION_TEMPERATURE_START_BIT);

    regVal   = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_36_ADDR_OFFSET);
    trimTemp = (sint16)Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_36_TRIM_TEMPERATURE_30C_STOP_BIT,
                                             EFUSE1_ROW_36_TRIM_TEMPERATURE_30C_START_BIT);

    efuseTempTrimValues.TrimTemp30C = (uint16)trimTemp;
    regVal                          = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_33_ADDR_OFFSET);
    trimTemp = (sint16)Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_33_TRIM_TEMPERATURE_125C_STOP_BIT,
                                             EFUSE1_ROW_33_TRIM_TEMPERATURE_125C_START_BIT);

    efuseTempTrimValues.TrimTemp125C = (uint16)trimTemp;

    if ((efuseTempTrimValues.FuseROMVer >= (uint16)6U) && (efuseTempTrimValues.TrimPrecisionTemp != (uint16)0U) &&
        (efuseTempTrimValues.TrimTemp30C != (uint16)0U) && (efuseTempTrimValues.TrimTemp125C != (uint16)0U))
    {
        regVal = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_37_ADDR_OFFSET);
        efuseTempTrimValues.TrimIntercept30C[DIG_DSP_TEMP_SENSOR] =
            Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_37_DIG_DSP_TEMP_SENSOR_TRIM0_30C_STOP_BIT,
                                  EFUSE1_ROW_37_DIG_DSP_TEMP_SENSOR_TRIM0_30C_START_BIT);
        regVal = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_37_ADDR_OFFSET);
        efuseTempTrimValues.TrimIntercept30C[DIG_HWA_TEMP_SENSOR] =
            Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_37_DIG_HWA_TEMP_SENSOR_TRIM1_30C_STOP_BIT,
                                  EFUSE1_ROW_37_DIG_HWA_TEMP_SENSOR_TRIM1_30C_START_BIT);
        regVal = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_38_ADDR_OFFSET);
        efuseTempTrimValues.TrimIntercept30C[DIG_HSM_TEMP_SENSOR] =
            Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_38_DIG_HSM_TEMP_SENSOR_TRIM2_30C_STOP_BIT,
                                  EFUSE1_ROW_38_DIG_HSM_TEMP_SENSOR_TRIM2_30C_START_BIT);

        regVal = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_34_ADDR_OFFSET);
        efuseTempTrimValues.TrimIntercept125C[DIG_DSP_TEMP_SENSOR] =
            Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_34_DIG_DSP_TEMP_SENSOR_TRIM0_125C_STOP_BIT,
                                  EFUSE1_ROW_34_DIG_DSP_TEMP_SENSOR_TRIM0_125C_START_BIT);
        regVal = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_34_ADDR_OFFSET);
        efuseTempTrimValues.TrimIntercept125C[DIG_HWA_TEMP_SENSOR] =
            Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_34_DIG_HWA_TEMP_SENSOR_TRIM1_125C_STOP_BIT,
                                  EFUSE1_ROW_34_DIG_HWA_TEMP_SENSOR_TRIM1_125C_START_BIT);
        regVal = HW_RD_REG32(MSS_TOP_CTRL_BASE_ADDRESS + EFUSE1_ROW_35_ADDR_OFFSET);
        efuseTempTrimValues.TrimIntercept125C[DIG_HSM_TEMP_SENSOR] =
            Adc_EfuseExtractTrims(regVal, EFUSE1_ROW_35_DIG_HSM_TEMP_SENSOR_TRIM2_125C_STOP_BIT,
                                  EFUSE1_ROW_35_DIG_HSM_TEMP_SENSOR_TRIM2_125C_START_BIT);

        tempSensTrimSlopeValues.TrimTemp30C =
            (((float32)efuseTempTrimValues.TrimTemp30C - EFUSE_TRIM_TEMPERATURE_CONST) /
             EFUSE_TRIM_TEMPERATURE_DIV_CONST);
        tempSensTrimSlopeValues.TrimTemp125C =
            (((float32)efuseTempTrimValues.TrimTemp125C - EFUSE_TRIM_TEMPERATURE_CONST) /
             EFUSE_TRIM_TEMPERATURE_DIV_CONST);

        tempSensTrimSlopeValues.TrimIntercept30C[DIG_DSP_TEMP_SENSOR] =
            efuseTempTrimValues.TrimIntercept30C[DIG_DSP_TEMP_SENSOR];
        tempSensTrimSlopeValues.TrimIntercept30C[DIG_HWA_TEMP_SENSOR] =
            efuseTempTrimValues.TrimIntercept30C[DIG_HWA_TEMP_SENSOR];
        tempSensTrimSlopeValues.TrimIntercept30C[DIG_HSM_TEMP_SENSOR] =
            efuseTempTrimValues.TrimIntercept30C[DIG_HSM_TEMP_SENSOR];

        tempSensTrimSlopeValues.TrimIntercept125C[DIG_DSP_TEMP_SENSOR] =
            efuseTempTrimValues.TrimIntercept125C[DIG_DSP_TEMP_SENSOR];
        tempSensTrimSlopeValues.TrimIntercept125C[DIG_HWA_TEMP_SENSOR] =
            efuseTempTrimValues.TrimIntercept125C[DIG_HWA_TEMP_SENSOR];
        tempSensTrimSlopeValues.TrimIntercept125C[DIG_HSM_TEMP_SENSOR] =
            efuseTempTrimValues.TrimIntercept125C[DIG_HSM_TEMP_SENSOR];

        Adc_computeTempSlope();

        tempSensTrimSlopeValues.InterceptTemp = tempSensTrimSlopeValues.TrimTemp30C;
    }
    else
    {
        tempSensTrimSlopeValues.TrimTemp30C  = ZERO;
        tempSensTrimSlopeValues.TrimTemp125C = ZERO;

        tempSensTrimSlopeValues.TrimIntercept30C[DIG_DSP_TEMP_SENSOR] =
            (uint16)ZERO_PT_TRIM_FIXED_DIG_TEMP_SENSOR_TRIM_30C;
        tempSensTrimSlopeValues.TrimIntercept30C[DIG_HWA_TEMP_SENSOR] =
            (uint16)ZERO_PT_TRIM_FIXED_DIG_TEMP_SENSOR_TRIM_30C;
        tempSensTrimSlopeValues.TrimIntercept30C[DIG_HSM_TEMP_SENSOR] =
            (uint16)ZERO_PT_TRIM_FIXED_DIG_TEMP_SENSOR_TRIM_30C;

        tempSensTrimSlopeValues.TrimIntercept125C[DIG_DSP_TEMP_SENSOR] = ZERO;
        tempSensTrimSlopeValues.TrimIntercept125C[DIG_HWA_TEMP_SENSOR] = ZERO;
        tempSensTrimSlopeValues.TrimIntercept125C[DIG_HSM_TEMP_SENSOR] = ZERO;

        tempSensTrimSlopeValues.Slope[DIG_DSP_TEMP_SENSOR] = ZERO_PT_TRIM_FIXED_SLOPE;
        tempSensTrimSlopeValues.Slope[DIG_HWA_TEMP_SENSOR] = ZERO_PT_TRIM_FIXED_SLOPE;
        tempSensTrimSlopeValues.Slope[DIG_HSM_TEMP_SENSOR] = ZERO_PT_TRIM_FIXED_SLOPE;

        tempSensTrimSlopeValues.InterceptTemp = ZERO_PT_TRIM_FIXED_TRIM_TEMP;
    }

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_TS_SE_INP_BUF_EN, TS_SE_INP_BUF_EN_ENABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_TS_DIFF_INP_BUF_EN, TS_DIFF_INP_BUF_EN_DISABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);
}

void Adc_ReadTemp(Adc_GroupType Group, uint8 NumAverages, Adc_TempSensValueType* TempValuesPtr)
{
    uint16             adcCode;
    float32            adcTempValSum[3] = {0}, tempVal;
    uint8              index, index2;
    Adc_ValueGroupType adcTempVal[ADC_NUM_CHANNEL] = {0};

    for (index = 0; index < NumAverages; index++)
    {
#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
        Adc_StartGroupConversion(Group);
#endif

        while (ADC_STREAM_COMPLETED != Adc_GetGroupStatus(Group))
        {
        }

#if (STD_ON == ADC_READ_GROUP_API)
        (void)Adc_ReadGroup(Group, &adcTempVal[0]);
#endif

        for (index2 = 0U; index2 < (uint8)MAX_ADC_TEMP_SENSORS; index2++)
        {
            adcCode               = (uint16)adcTempVal[index2];
            tempVal               = Adc_calculateTemp(adcCode, index2);
            adcTempValSum[index2] = adcTempValSum[index2] + tempVal;
        }
    }

    TempValuesPtr->DigDspTempValue = (sint16)((sint16)adcTempValSum[DIG_DSP_TEMP_SENSOR] / (sint16)NumAverages);
    TempValuesPtr->DigHwaTempValue = (sint16)((sint16)adcTempValSum[DIG_HWA_TEMP_SENSOR] / (sint16)NumAverages);
    TempValuesPtr->DigHsmTempValue = (sint16)((sint16)adcTempValSum[DIG_HSM_TEMP_SENSOR] / (sint16)NumAverages);
}

void Adc_ReadTempResult(Adc_GroupType Group, Adc_TempSensValueType* TempValuesPtr)
{
    uint16             adcCode;
    float32            adcVal[3] = {0};
    uint8              index2;
    Adc_ValueGroupType adcTempVal[ADC_NUM_CHANNEL] = {0};

#if (STD_ON == ADC_READ_GROUP_API)
    (void)Adc_ReadGroup(Group, &adcTempVal[0]);
#endif

    for (index2 = 0U; index2 < (uint8)MAX_ADC_TEMP_SENSORS; index2++)
    {
        adcCode        = (uint16)adcTempVal[index2];
        adcVal[index2] = Adc_calculateTemp(adcCode, index2);
    }

    TempValuesPtr->DigDspTempValue = (sint16)(adcVal[DIG_DSP_TEMP_SENSOR]);
    TempValuesPtr->DigHwaTempValue = (sint16)(adcVal[DIG_HWA_TEMP_SENSOR]);
    TempValuesPtr->DigHsmTempValue = (sint16)(adcVal[DIG_HSM_TEMP_SENSOR]);
}

static float32 Adc_calculateTemp(uint16 adcTempCode, uint8 index)
{
    float32 tempVal;

    tempVal = ((((float32)adcTempCode - (float32)tempSensTrimSlopeValues.TrimIntercept30C[index]) /
                tempSensTrimSlopeValues.Slope[index]) +
               tempSensTrimSlopeValues.InterceptTemp);
    return tempVal;
}

static void Adc_computeTempSlope(void)
{
    uint8 index;

    for (index = 0; index < (uint8)MAX_ADC_TEMP_SENSORS; index++)
    {
        tempSensTrimSlopeValues.Slope[index] =
            ((float32)tempSensTrimSlopeValues.TrimIntercept125C[index] -
             (float32)tempSensTrimSlopeValues.TrimIntercept30C[index]) /
            (tempSensTrimSlopeValues.TrimTemp125C - tempSensTrimSlopeValues.TrimTemp30C);
    }
}

static uint16 Adc_EfuseExtractTrims(volatile uint32 reg, uint8 msb, uint8 lsb)
{
    uint32 mask;
    uint8  bits;
    uint16 value;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    value = (uint16)((reg >> lsb) & mask);
    return value;
}

#define ADC_STOP_SEC_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

/*
 * END OF Adc_Temp.c FILE
 */
