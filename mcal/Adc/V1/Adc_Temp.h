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
 *   \file  Adc_Temp.h
 *
 *   \brief
 *      This is the platform specific header file for the ADC driver
 *      which specifies the ADC register addresses and structures/ unions
 *      used in the ADC temperature sensor driver
 */

/****************************************************************************************
 * FILE INCLUSION PROTECTION
 ****************************************************************************************
 */
#ifndef ADC_TEMP_H
#define ADC_TEMP_H

/****************************************************************************************
 * INCLUDE FILES
 ****************************************************************************************
 */
#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************************
 * MACRO DEFINITIONS
 ****************************************************************************************
 */

#define EFUSE_TRIM_TEMPERATURE_CONST     523.0f
#define EFUSE_TRIM_TEMPERATURE_DIV_CONST 10.0f

#define ZERO_PT_TRIM_FIXED_TRIM_TEMP                32.0f
#define ZERO_PT_TRIM_FIXED_DIG_TEMP_SENSOR_TRIM_30C 384U
#define ZERO                                        0.0f

#define ZERO_PT_TRIM_FIXED_SLOPE -0.988f
#define ONE_PT_TRIM_FIXED_SLOPE  -1.05f

/* Klocwork  inspected.
 * MISRA.DEFINE.NOT_DISTINCT.C90.2012
 * Identifier Names
 */

#define EFUSE1_ROW_14_FUSEROM_VER_START_BIT 20U
#define EFUSE1_ROW_14_FUSEROM_VER_STOP_BIT  24U

#define EFUSE1_ROW_36_TRIM_TEMPERATURE_30C_START_BIT 15U
#define EFUSE1_ROW_36_TRIM_TEMPERATURE_30C_STOP_BIT  25U

#define EFUSE1_ROW_33_TRIM_TEMPERATURE_125C_START_BIT 0U
#define EFUSE1_ROW_33_TRIM_TEMPERATURE_125C_STOP_BIT  10U

#define EFUSE1_ROW_37_DIG_DSP_TEMP_SENSOR_TRIM0_30C_START_BIT 5U
#define EFUSE1_ROW_37_DIG_DSP_TEMP_SENSOR_TRIM0_30C_STOP_BIT  14U

#define EFUSE1_ROW_37_DIG_HWA_TEMP_SENSOR_TRIM1_30C_START_BIT 15U
#define EFUSE1_ROW_37_DIG_HWA_TEMP_SENSOR_TRIM1_30C_STOP_BIT  24U

#define EFUSE1_ROW_38_DIG_HSM_TEMP_SENSOR_TRIM2_30C_START_BIT 0U
#define EFUSE1_ROW_38_DIG_HSM_TEMP_SENSOR_TRIM2_30C_STOP_BIT  9U

#define EFUSE1_ROW_34_DIG_DSP_TEMP_SENSOR_TRIM0_125C_START_BIT 5U
#define EFUSE1_ROW_34_DIG_DSP_TEMP_SENSOR_TRIM0_125C_STOP_BIT  14U

#define EFUSE1_ROW_34_DIG_HWA_TEMP_SENSOR_TRIM1_125C_START_BIT 15U
#define EFUSE1_ROW_34_DIG_HWA_TEMP_SENSOR_TRIM1_125C_STOP_BIT  24U

#define EFUSE1_ROW_35_DIG_HSM_TEMP_SENSOR_TRIM2_125C_START_BIT 0U
#define EFUSE1_ROW_35_DIG_HSM_TEMP_SENSOR_TRIM2_125C_STOP_BIT  9U

#define EFUSE1_ROW_39_TRIM_PRECISION_TEMPERATURE_START_BIT 0U
#define EFUSE1_ROW_39_TRIM_PRECISION_TEMPERATURE_STOP_BIT  13U

/******************************************************************************
 * TYPE-DEFINE STRUCT/ENUM/UNION DEFINITIONS
 ******************************************************************************
 */

/**
 * \brief
 *  ADC Temperature Sensors List
 *
 * \details
 *  Enumeration which describes the temperature sensors available for ADC measurement
 */
typedef enum
{
    /**
     * \brief   0x0 - DIG_DSP_TEMP_SENSOR
     */
    DIG_DSP_TEMP_SENSOR = 0,
    /**
     * \brief   0x1 - DIG_HWA_TEMP_SENSOR
     */
    DIG_HWA_TEMP_SENSOR,
    /**
     * \brief   0x2 - DIG_HSM_TEMP_SENSOR
     */
    DIG_HSM_TEMP_SENSOR,

    /**
     * \brief   0x3 - MAX_TEMP_SENSORS
     */
    MAX_ADC_TEMP_SENSORS
} Adc_TempSensorSrcType;

/*! \brief
 * The Temperature sensor trim parameters structure
 */
typedef struct
{
    uint16 FuseROMVer;
    uint16 TrimPrecisionTemp;
    uint16 TrimTemp30C;
    uint16 TrimTemp125C;
    uint16 TrimIntercept30C[MAX_ADC_TEMP_SENSORS];
    uint16 TrimIntercept125C[MAX_ADC_TEMP_SENSORS];
} Adc_EfuseTempTrimType;

/*! \brief
 * The Temperature sensor trim parameters structure
 */
typedef struct
{
    float32 TrimTemp30C;
    float32 TrimTemp125C;
    uint16  TrimIntercept30C[MAX_ADC_TEMP_SENSORS];
    uint16  TrimIntercept125C[MAX_ADC_TEMP_SENSORS];
    float32 Slope[MAX_ADC_TEMP_SENSORS];
    float32 InterceptTemp;
} Adc_TempSensTrimType;

/******************************************************************************
 * EXTERN GLOBAL VARIABLES/DATA-TYPES DECLARATIONS
 ******************************************************************************
 */

/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************
 */

void Adc_InitTemp(void);
void Adc_ReadTemp(Adc_GroupType Group, uint8 numAverages, Adc_TempSensValueType* tempValuesPtr);
void Adc_ReadTempResult(Adc_GroupType Group, Adc_TempSensValueType* TempValuesPtr);

#ifdef __cplusplus
}
#endif

#endif
/*
 * END OF ADC_TEMP_H
 */
