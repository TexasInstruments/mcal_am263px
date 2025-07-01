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
 *   \file Adc_Platform.c
 *
 *   \brief The file implements the Platform specific GPADC Driver Configurations
 */

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************
 */
#include "Std_Types.h"
#include "hw_types.h"
#include "hw_ctrl_core.h"
#include "hal_stdtypes.h"
#include "hw_adc.h"
#include "Adc_Cfg.h"
#include "Adc_Platform.h"
/******************************************************************************
 * GLOBAL VARIABLES/DATA-TYPES DEFINITIONS
 ******************************************************************************
 */
#define GPADC_CLK_DIVIDER_VAL (0x131313U)

#define GPADC_CLK_GATING_OFF (0U)
#define GPADC_CLK_GATING_ON  (1U)

#define CLK_TMUX_ESD_CTRL_DISABLE (0U)
#define CLK_TMUX_ESD_CTRL_ENABLE  (1U)

#define ANA_TEST_DISABLE (0U)
#define ANA_TEST_ENABLE  (1U)

#define ANALOGTEST_TMUX_ESD_CTRL_DISABLE (0U)
#define ANALOGTEST_TMUX_ESD_CTRL_ENABLE  (1U)

#define ADC_REF_BUF_DISABLE (0U)
#define ADC_REF_BUF_ENABLE  (1U)

/* 0b001 = Reference from Top Refsys
 */
#define ADC_REF_SEL_TOP_REFSYS (1U)
/* 0b010 = Reference from RX Refsys
 */
#define ADC_REF_SEL_RX_REFSYS (2U)
/* 0b100 = Reference from External Test Pin
 */
#define ADC_REF_SEL_EXT_TEST_PIN (4U)

#define ADC_START_CONV_DISABLE (0U)
#define ADC_START_CONV_ENABLE  (1U)

#define ADC_INP_BUF_DISABLE (0U)
#define ADC_INP_BUF_ENABLE  (1U)

#define ADC_DISABLE            (0U)
#define ADC_ENABLE             (1U)
#define ADC_ASSERT_RESET       (1U)
#define ADC_DEASSERT_RESET     (0U)
#define ADC_FSM_ASSERT_RESET   (0x7U)
#define ADC_FSM_DEASSERT_RESET (0U)

/*
 *  GPADC MODES
 */
#define ADC_MODE_DISABLE (0U)
#define ADC_MODE_IFM     (1U)
#define ADC_MODE_CTM     (2U)

#define ADC_DEBUG_MODE_ENABLE (1U)

extern VAR(Adc_DriverObjType, ADC_VAR_CLEARED) Adc_DrvObj;

#define ADC_START_SEC_VAR_INIT_32
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

static volatile VAR(uint32, ADC_VAR) groupChannelCount = 0U;

#define ADC_STOP_SEC_VAR_INIT_32
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static Std_ReturnType Adc_notifyGroupDone(Adc_HwUnitObjType *hwUnitObj);

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

void Adc_hwDriverInit(void)
{
    uint8  divider;
    uint32 profRamAdd;
    uint32 regVal;

    /*
     * Source sysclk 200MHz
     * Configure sys clock divider as 0x000 in multibit which is 200/1
     */
    regVal = HW_RD_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_CLK_DIV_VAL_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, MSS_GPADC_CLK_DIV_VAL_CLKDIVR, GPADC_CLK_DIVIDER_VAL);
    HW_WR_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_CLK_DIV_VAL_ADDR_OFFSET, regVal);

    /*
     * writing '111' will gate clock for MSS GPADC
     */
    regVal = HW_RD_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_CLK_GATE_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, MSS_GPADC_CLK_GATE_GATED, GPADC_CLK_GATING_OFF);
    HW_WR_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_CLK_GATE_ADDR_OFFSET, regVal);

    /*
     * Configure the clock divider for GPADC Module
     * GPADC Clock = 10MHz = source_clock/Divider
     * source_clock can be 200 or xtal clock
     */
    divider = (20U);
    regVal  = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG8_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG8_GPADC_CLK_DIV, divider);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG8_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG1_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG1_GPADC_INIT, 1U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG1_ADDR_OFFSET, regVal);

    /* Disable FSM Bypass */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG1_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG1_GPADC_FSM_BYPASS, 0U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG1_ADDR_OFFSET, regVal);

    /* Enable the GPADC FSM clock */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG0_GPADC_FSM_CLK_ENABLE, 1U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET, regVal);

    /* Enable the GPADC clock */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG8_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG8_GPADC_CLK_ENABLE, 1U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG8_ADDR_OFFSET, regVal);

    /* Write the Mode of operation */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG0_DCBIST_MODE, ADC_MODE_DISABLE);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET, regVal);

    /* Write config value for IFM Mode */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG2_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG2_CONFIG_VALUE_IFM, 0U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG2_ADDR_OFFSET, regVal);

    /* Write param and samples values for IFM Mode */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG3_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG3_PARAM_IFM, 0U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG3_ADDR_OFFSET, regVal);

    /* Write Packet RAM Base address for CTM Mode */
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG4_ADDR_OFFSET, 0U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG5_ADDR_OFFSET, 0U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG6_ADDR_OFFSET, 0U);

    /*!
     * Profile 15 Instruction Ram address update with M_GPADC_MON_INSTR_RAM_ST_IND for monitoring
     */
    profRamAdd = ((uint32)M_GPADC_MON_INSTR_RAM_ST_IND << 24U) & 0xFF000000U;
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG7_ADDR_OFFSET, profRamAdd);
}

void Adc_hwDriverDeInit(void)
{
    uint32 regVal;
    /*
     * Release Reset GPADC for digital FSM
     * Writing '111' or '0x07' will reset MSS GPADC
     */
    regVal = HW_RD_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_RST_CTRL_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, MSS_GPADC_RST_CTRL_ASSERT, ADC_FSM_ASSERT_RESET);
    HW_WR_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_RST_CTRL_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_ANA_TMUX_CTRL_LOWV_CLK_TMUX_ESD_CTRL, CLK_TMUX_ESD_CTRL_DISABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ANA_TEST_EN, ANA_TEST_DISABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_REFSYS_SPARE_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_REFSYS_SPARE_REG_LOWV_ANALOGTEST_TMUX_ESD_CTRL, ANALOGTEST_TMUX_ESD_CTRL_DISABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_REFSYS_SPARE_REG_LOWV_ADDR_OFFSET, regVal);

    /* Reset GPADC Ana */
    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_RESET, ADC_ASSERT_RESET);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    /* Disable GPADC Ana */
    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_EN, ADC_DISABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);
}

void Adc_hwResetRelease(void)
{
    uint32 regVal;
    /* Release Reset GPADC for digital FSM */
    regVal = HW_RD_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_RST_CTRL_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, MSS_GPADC_RST_CTRL_ASSERT, ADC_FSM_DEASSERT_RESET);
    HW_WR_REG32(MSS_RCM_BASE_ADDRESS + MSS_GPADC_RST_CTRL_ADDR_OFFSET, regVal);

#if defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM)
    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_ANA_TMUX_CTRL_LOWV_CLK_TMUX_ESD_CTRL, CLK_TMUX_ESD_CTRL_ENABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ANA_TEST_EN, ANA_TEST_ENABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_ANA_TMUX_CTRL_LOWV_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_REFSYS_SPARE_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_REFSYS_SPARE_REG_LOWV_ANALOGTEST_TMUX_ESD_CTRL, ANALOGTEST_TMUX_ESD_CTRL_ENABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_REFSYS_SPARE_REG_LOWV_ADDR_OFFSET, regVal);
#else
    regVal = HW_RD_REG32(AR_RFANACIO_TW_ANA_TMUX_CTRL_REG_ADDR);
    HW_SET_FIELD32(regVal, AR_RFANACIO_TW_ANA_TMUX_CTRL_CLK_TMUX_ESD_CTRL, CLK_TMUX_ESD_CTRL_ENABLE);
    HW_WR_REG32(AR_RFANACIO_TW_ANA_TMUX_CTRL_REG_ADDR, regVal);

    regVal = HW_RD_REG32(AR_RFANACIO_RX_REFSYS_TMUX_SPARE_CTRL_REG_ADDR);
    HW_SET_FIELD32(regVal, AR_RFANACIO_RX_REFSYS_TMUX_SPARE_CTRL_ANA_TEST_ESD_MUX_EN, ANA_TEST_ESD_MUX_EN);
    HW_WR_REG32(AR_RFANACIO_RX_REFSYS_TMUX_SPARE_CTRL_REG_ADDR, regVal);
#endif
    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_REF_BUF_EN, ADC_REF_BUF_ENABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    /* Reset GPADC Ana */
    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_RESET, ADC_ASSERT_RESET);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    /* Enable GPADC Ana */
    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_EN, ADC_ENABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    /* Release GPADC Reset Ana */
    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_RESET, ADC_DEASSERT_RESET);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_REF_SEL_2_0, ADC_REF_SEL_TOP_REFSYS);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_START_CONV, ADC_START_CONV_ENABLE);
    HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);

    /* One time Setup of the mode of operation to IFM */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG0_DCBIST_MODE, ADC_MODE_IFM);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET, regVal);

    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG0_GPADC_DEBUG_MODE_ENABLE, ADC_DEBUG_MODE_ENABLE);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG0_ADDR_OFFSET, regVal);
}

void Adc_hwStart(void)
{
    uint8               channelIndex = 0;
    Adc_ResultType      gpAdcResult;
    Adc_GroupDefType    hwChannelId;
    uint8               numSamples;
    Adc_HwUnitObjType  *hwUnitObj = Adc_getHwUnitObj(ADC_UNIT_1);
    Adc_GroupObjType   *groupObj;
    uint32              Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/
    Adc_ValueGroupType *resultBufPtrCh;

    groupChannelCount = 0;
    if (hwUnitObj != NULL)
    {
        groupObj = hwUnitObj->curGroupObj;
    }

    if ((hwUnitObj != NULL) && (ADC_INTERRUPT_MODE == hwUnitObj->hwUnitCfg.hwUnitMonitorMode))
    {
        hwChannelId = groupObj->groupCfg.hwChannelID[groupChannelCount];

        /* Call the GPADC function to convert the param from ana to dig */
        Adc_convert(hwChannelId);
        Avoid_nesting_flag = 1U;
    }
    if ((hwUnitObj != NULL) && (Avoid_nesting_flag == 0U))
    {
        /* Max Check for the GPADC supported measurement list */
        for (channelIndex = 0; channelIndex < groupObj->groupCfg.numChannels; channelIndex++)
        {
            hwChannelId = groupObj->groupCfg.hwChannelID[channelIndex];

            if (TRUE == Adc_DrvObj.channelObj[hwChannelId].channelConfig.isConfigured)
            {
                /* Call the GPADC function to convert the param from ana to dig */
                Adc_convert(hwChannelId);

                numSamples = (uint8)((Adc_DrvObj.channelObj[hwChannelId].channelConfig.channelParamValue &
                                      GPADC_REG_R_REG3_COLLECT_SAMPLES_IFM_MASK) >>
                                     8U);

                /* Get the GPADC conversion results */
                Adc_readSamplingResult(numSamples, &gpAdcResult);

                resultBufPtrCh               = (Adc_ValueGroupType *)groupObj->resultBufPtr;
                resultBufPtrCh[channelIndex] = (uint32)gpAdcResult.Avg;
            }
        }
    }

    return;
}

void Adc_channelCfgIfm(uint32 cfgVal, uint32 paramVal)
{
    uint32 regVal;
    /* Write 32 bit Dynamic value to config reg */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG2_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG2_CONFIG_VALUE_IFM, cfgVal);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG2_ADDR_OFFSET, regVal);

    /* Write Param Value, Collect Samples , Skip Samples */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG3_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG3_PARAM_IFM, paramVal);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG3_ADDR_OFFSET, regVal);

    return;
}

void Adc_swTrigger(void)
{
    Adc_HwUnitObjType *hwUnitObj = Adc_getHwUnitObj(ADC_UNIT_1);
    uint32             regVal;
    volatile uint32    tempCount = ADC_TIMEOUT_DURATION;
    if (ADC_TIMEOUT_DURATION > 8U)
    {
        tempCount = ADC_TIMEOUT_DURATION / 8U;
    }

    /* Trigger the ADC Conversion in IFM mode */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG1_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG1_GPADC_TRIGGER, 1U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG1_ADDR_OFFSET, regVal);

    if ((hwUnitObj != NULL) && (ADC_POLLING_MODE == hwUnitObj->hwUnitCfg.hwUnitMonitorMode))
    {
        /* Wait for GPADC conversion to complete */
        do
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            /*LDRA_INSPECTED 488 S : MISRAC_2012_R.10.3
             *Reason : cannot be outside 32bit range*/
            {
                break;
            }
            MCAL_SW_DELAY(tempCount);
            /* Compute the PMU count delta */
            regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG17_ADDR_OFFSET);
        } while (1U != (0x01U & HW_GET_FIELD(regVal, GPADC_REG_R_REG17_GPADC_IFM_DONE_STATUS)));

        regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG17_ADDR_OFFSET);
        if (1U != (0x01U & HW_GET_FIELD(regVal, GPADC_REG_R_REG17_GPADC_IFM_DONE_STATUS)))
        {
#ifdef ADC_E_HARDWARE_ERROR
            Dem_SetEventStatus(ADC_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }

        /* Clear the IFM status bit */
        regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG18_ADDR_OFFSET);
        HW_SET_FIELD32(regVal, GPADC_REG_R_REG18_GPADC_IFM_DONE_CLR, 1U);
        HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG18_ADDR_OFFSET, regVal);
    }

    return;
}

void Adc_readSamplingResult(uint8 numSamples, Adc_ResultType *gpAdcResult)
{
    uint32 sumReg = 0;
    uint32 regVal;

    /* Read the Results and populate the Structure */
    if (M_NULL != gpAdcResult)
    {
        /* Read the Sum of ADC samples */
        regVal           = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG14_ADDR_OFFSET);
        sumReg           = HW_GET_FIELD(regVal, GPADC_REG_R_REG14_SUM_IFM);
        gpAdcResult->Sum = sumReg;

        /* Read the Min of ADC samples */
        regVal           = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG15_ADDR_OFFSET);
        gpAdcResult->Min = HW_GET_FIELD(regVal, GPADC_REG_R_REG15_MIN_GPADC);

        /* Read the Max of ADC samples */
        regVal           = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG15_ADDR_OFFSET);
        gpAdcResult->Max = HW_GET_FIELD(regVal, GPADC_REG_R_REG15_MAX_GPADC);

        /* Read the Avg of ADC samples */
        if ((uint8)0U != numSamples)
        {
            gpAdcResult->Avg = sumReg / (uint32)numSamples;
        }
        else
        {
            gpAdcResult->Avg = 0U;
        }
    }

    /* Write Param Value to 0 to avoid any contention */
    regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG3_ADDR_OFFSET);
    HW_SET_FIELD32(regVal, GPADC_REG_R_REG3_PARAM_IFM, 0U);
    HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG3_ADDR_OFFSET, regVal);

    return;
}

void Adc_convert(Adc_GroupDefType hwChannelId)
{
    uint32 cfgVal;
    uint32 paramVal;
    uint32 regVal;

    if (TRUE == Adc_DrvObj.channelObj[hwChannelId].channelConfig.isBufferedMode)
    {
        regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
        HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_INP_BUF_EN, ADC_INP_BUF_ENABLE);
        HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);
    }
    else
    {
        regVal = HW_RD_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET);
        HW_SET_FIELD32(regVal, ANA_REG_TW_CTRL_REG_LOWV_ADC_INP_BUF_EN, ADC_INP_BUF_DISABLE);
        HW_WR_REG32(MSS_TOPRCM_BASE_ADDRESS + ANA_REG_TW_CTRL_REG_LOWV_ADDR_OFFSET, regVal);
    }

    /* Get the Config Value from DriverObj */
    cfgVal = Adc_DrvObj.channelObj[hwChannelId].channelConfig.channelConfigValue;
    /* Get the Param Value from DriverObj */
    paramVal = Adc_DrvObj.channelObj[hwChannelId].channelConfig.channelParamValue;

    /* Configure the GPADC by writing Config reg and Param reg*/
    Adc_channelCfgIfm(cfgVal, paramVal);

    /* Trigger the GPADC for Conversion */
    Adc_swTrigger();
}

uint8 Adc_convSkipTimeToCode(uint32 skipSamples)
{
    uint32 result;
    uint8  twoPwr = 0U, skipSampProg;

    /*! find the nearest a*2^b values to program to Hw */
    result = skipSamples;
    while (result >= (uint32)16U)
    {
        twoPwr++;
        /*Invalid LDRA warning - c_twoPwr can not be zero */
        /*LDRA_INSPECTED 127 D */
        result = (skipSamples + ((uint32)1U << (twoPwr - 1U))) / ((uint32)1U << twoPwr);

        /*! Max two to the power (b) is 3 bits */
        if (twoPwr == 7U)
        {
            break;
        }
    }

    /*! Max value of a is 4 bits */
    if (result >= 16U)
    {
        result = 15U;
    }

    /*! The programming skip sample values for first parameter */
    skipSampProg = (((twoPwr & 0x07U) << 4U) | ((uint8)result & 0xFU));

    return skipSampProg;
}

/* This function shall be called when we recieve the response from the BSS*/
void Adc_IFMDoneProcessing(const Adc_HwUnitObjType *hwUnitObj)
{
    Adc_GroupObjType   *groupObj;
    Adc_GroupDefType    hwChannelId;
    Adc_ResultType      gpAdcResult;
    uint8               numSamples;
    uint32              regVal;
    Adc_ValueGroupType *resultBufPtrCh;

    groupObj = hwUnitObj->curGroupObj;
    regVal   = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG17_ADDR_OFFSET);
    if (1U == ((uint32)0x01 & HW_GET_FIELD(regVal, GPADC_REG_R_REG17_GPADC_IFM_DONE_STATUS)))
    {
        /* Clear the interrupt */
        regVal = HW_RD_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG18_ADDR_OFFSET);
        HW_SET_FIELD32(regVal, GPADC_REG_R_REG18_GPADC_IFM_DONE_CLR, 1U);
        HW_WR_REG32(MSS_GPADC_REG_BASE_ADDRESS + R_REG18_ADDR_OFFSET, regVal);

        hwChannelId = hwUnitObj->curGroupObj->groupCfg.hwChannelID[groupChannelCount];
        numSamples  = (uint8)((Adc_DrvObj.channelObj[hwChannelId].channelConfig.channelParamValue &
                              GPADC_REG_R_REG3_COLLECT_SAMPLES_IFM_MASK) >>
                             8U);

        /* Get the GPADC conversion results */
        Adc_readSamplingResult(numSamples, &gpAdcResult);

        resultBufPtrCh                    = (Adc_ValueGroupType *)groupObj->resultBufPtr;
        resultBufPtrCh[groupChannelCount] = (uint32)gpAdcResult.Avg;

        if ((groupChannelCount + 1U) < hwUnitObj->curGroupObj->groupCfg.numChannels)
        {
            groupChannelCount = groupChannelCount + 1U;

            hwChannelId = hwUnitObj->curGroupObj->groupCfg.hwChannelID[groupChannelCount];

            Adc_convert(hwChannelId);
        }
        else
        {
            (void)Adc_groupGpConversionDoneHandler();
        }
    }
}

Std_ReturnType Adc_groupGpConversionDoneHandler(void)
{
    /* "Reason - Tool issue " */
    Adc_HwUnitObjType *hwUnitObj = Adc_getHwUnitObj(ADC_UNIT_1);
    Std_ReturnType     retVal;

    if (hwUnitObj != NULL_PTR)
    {
        /* GPADC data */
        retVal = Adc_notifyGroupDone(hwUnitObj);

        if (retVal == (Std_ReturnType)E_OK)
        {
            /* Check and schedule any pending groups for this HW */
            Adc_checkAndSchedule(hwUnitObj);
        }
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    /*LDRA_INSPECTED 91 D : MISRAC_2012_R.17.7 */
    /* "Reason - Tool issue " */
    return retVal;
}
/*Requirements : SWS_Adc_00080, SWS_Adc_00060 */
static Std_ReturnType Adc_notifyGroupDone(Adc_HwUnitObjType *hwUnitObj)
{
    Std_ReturnType         retVal               = (Std_ReturnType)E_OK;
    Adc_GroupEndNotifyType groupEndNotification = (Adc_GroupEndNotifyType)NULL;
    Adc_GroupObjType      *groupObj;

    /* Copy data into global buffer */
    groupObj = hwUnitObj->curGroupObj;
    if (groupObj != NULL_PTR)
    {
        /* Update the state of the group */
        groupObj->groupStatus = ADC_STREAM_COMPLETED;
        /* Notify the group if enabled */
        groupEndNotification = groupObj->groupCfg.Adc_GroupEndNotification;
        if ((((uint32)TRUE) == groupObj->isNotifyOn) && (NULL_PTR != groupEndNotification))
        {
            groupEndNotification();
        }
        /* No group is running until scheduler is called */
        hwUnitObj->curGroupObj = (Adc_GroupObjType *)NULL;
    }
    else
    {
        /* It's ok, the groups might have been stopped but we
               send an ACK to BSS to prevent blocking, so don't
               return an error
         */
    }

    return retVal;
}

#define ADC_STOP_SEC_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

/*
 * END OF Adc_Platform.c FILE
 */
