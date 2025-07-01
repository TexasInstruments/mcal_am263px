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
 *   \file  Adc_Platform.h
 *
 *   \brief
 *      This is the platform specific header file for the GPADC driver
 *      which specifies the GPADC register addresses and structures/ unions
 *      used in the GPADC driver
 */

/****************************************************************************************
 * FILE INCLUSION PROTECTION
 ****************************************************************************************
 */
#ifndef DRV_GPADC_SOC_H
#define DRV_GPADC_SOC_H

/****************************************************************************************
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "Adc_Priv.h"
#include "Adc_Cfg.h"
#include "hw_adc.h"
/****************************************************************************************
 * MACRO DEFINITIONS
 ****************************************************************************************
 */

/*! \brief
 *  GPADC MON CTM INSTRUCTION RAM Index
 */
#define M_GPADC_MON_INSTR_RAM_ST_IND (224U)
#define M_GPADC_MAX_MON_INSTR_RAM    (32U)

/*! \brief
 *  Number of measurement parameters for GPADC in CTM mode
 */
#define M_MAX_CTM_GPADC_PARAMS (1U)

/*! \brief
 *  GPADC TIMEOUT
 *  Max Number of Sample collect : 256
 *  Max Time for 256 samples collection : 256 * 16/10MHz = 409.6us
 *  Add 10 % margin : 450us
 *  Add 550us for skip samples
 *  Total timeout: 1ms
 *  Timout in terms of pmu count = 1ms/5ns = 200,000
 */
#define M_GPADC_TIMEOUT_MAX (200000U)

#define AR_RFANACIO_TW_ANA_TMUX_CTRL_REG_ADDR                (0xA32013CCU)
#define AR_RFANACIO_TW_ANA_TMUX_CTRL_CLK_TMUX_ESD_CTRL_MASK  (0x40000000U)
#define AR_RFANACIO_TW_ANA_TMUX_CTRL_CLK_TMUX_ESD_CTRL_SHIFT (0x0000001EU)
#define CLK_TMUX_ESD_CTRL_ENABLE                             (1U)

#define AR_RFANACIO_RX_REFSYS_TMUX_SPARE_CTRL_REG_ADDR                  (0xA3201144U)
#define AR_RFANACIO_RX_REFSYS_TMUX_SPARE_CTRL_ANA_TEST_ESD_MUX_EN_MASK  (0x80000000U)
#define AR_RFANACIO_RX_REFSYS_TMUX_SPARE_CTRL_ANA_TEST_ESD_MUX_EN_SHIFT (0x0000001FU)
#define ANA_TEST_ESD_MUX_EN                                             (1U)

/******************************************************************************
 * TYPE-DEFINE STRUCT/ENUM/UNION DEFINITIONS
 ******************************************************************************
 */

/*! \brief
 *  Configuration Parameters for GPADC LUT in IFM mode
 *    32 bits:  ConfigValue
 *    32 bits:  ParamInfo
 */
typedef struct
{
    uint32 UnbuffConfigValue;
    uint32 BuffConfigValue;
    uint32 ParamInfo;
    uint16 TotalTime; /* in unit of 100ns = CollectSamples*16 + SkipSamples */
} Adc_CfgAndParamValuesType;

/*! \brief
 *  GPADC returning min, avg, max and sum
 */
typedef struct
{
    uint32 Avg;
    uint32 Min;
    uint32 Max;
    uint32 Sum;
} Adc_ResultType;

/******************************************************************************
 * EXTERN GLOBAL VARIABLES/DATA-TYPES DECLARATIONS
 ******************************************************************************
 */

/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************
 */

void           Adc_hwDriverInit(void);
void           Adc_hwDriverDeInit(void);
void           Adc_hwResetRelease(void);
void           Adc_hwStart(void);
void           Adc_channelCfgIfm(uint32 cfgVal, uint32 paramVal);
void           Adc_swTrigger(void);
void           Adc_readSamplingResult(uint8 c_numSamples, Adc_ResultType *gpAdcResult);
void           Adc_convert(Adc_GroupDefType hwChannelId);
uint8          Adc_convSkipTimeToCode(uint32 skipSamples);
void           Adc_IFMDoneProcessing(const Adc_HwUnitObjType *hwUnitObj);
Std_ReturnType Adc_groupGpConversionDoneHandler(void);
#endif
/*
 * END OF DRV_GPADC_SOC_H
 */
