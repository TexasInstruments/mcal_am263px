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

/* Protection against multiple inclusion */
#ifndef ADCAPP_STARTUP_H_
#define ADCAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "sys_common.h"
#include "AdcApp.h"
#include "Cdd_Dma_Irq.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
extern const struct Adc_ConfigType_s Adc_Config;
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void                                 AdcTempTest(AdcApp_Obj *appObj, Adc_GroupType Group);
void        AdcApp_printChannelResult(uint32 grpIdx, const Adc_GroupConfigType *grpCfg, const AdcApp_Obj *appObj);
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void        AdcApp_Startup(void);
void        AdcApp_TimerDeinit(void);
void        Adc_Print_applyvoltage(AdcApp_Obj *appObj);
extern void AdcApp_interruptConfig(void);

static AdcApp_TestParams gAdcAppTestPrms[] = {{
    (char *)"4 Groups\n"
            "CHANNEL 1  -> One-shot -> Priority - 0\n"
            "CHANNEL 1 -> One-shot -> Priority - 1\n"
            "CHANNEL 1,2,3,4  -> One-shot -> Priority - 2\n"
            "CHANNEL 1,2 -> One-shot -> Priority - 3\n",
    ADC_APP_LOOP_COUNT, /* loopCount             */
    TRUE,               /* Enable Print          */
    &Adc_Config,        /* pointer to adcConfig  */
}};

/* ========================================================================== */
/*                           Macros related to ADC Register.                  */
/* ========================================================================== */
#define CSL_TOP_CTRL_LOCK0_KICK0 (0x00001008U)
#define CSL_TOP_CTRL_LOCK0_KICK1 (0x0000100CU)

/* LOCK0_KICK0 */

#define CSL_TOP_CTRL_LOCK0_KICK0_LOCK0_KICK0_MASK     (0xFFFFFFFFU)
#define CSL_TOP_CTRL_LOCK0_KICK0_LOCK0_KICK0_SHIFT    (0x00000000U)
#define CSL_TOP_CTRL_LOCK0_KICK0_LOCK0_KICK0_RESETVAL (0x00000000U)
#define CSL_TOP_CTRL_LOCK0_KICK0_LOCK0_KICK0_MAX      (0xFFFFFFFFU)

#define CSL_TOP_CTRL_LOCK0_KICK0_RESETVAL (0x00000000U)

/* LOCK0_KICK1 */

#define CSL_TOP_CTRL_LOCK0_KICK1_LOCK0_KICK1_MASK     (0xFFFFFFFFU)
#define CSL_TOP_CTRL_LOCK0_KICK1_LOCK0_KICK1_SHIFT    (0x00000000U)
#define CSL_TOP_CTRL_LOCK0_KICK1_LOCK0_KICK1_RESETVAL (0x00000000U)
#define CSL_TOP_CTRL_LOCK0_KICK1_LOCK0_KICK1_MAX      (0xFFFFFFFFU)

#define CSL_TOP_CTRL_LOCK0_KICK1_RESETVAL (0x00000000U)

#define CSL_CONTROLSS_CTRL_U_BASE      (0x502F0000UL)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0 (0x00001008U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1 (0x0000100CU)

/* LOCK0_KICK0 */

#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_MASK     (0xFFFFFFFFU)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_MAX      (0xFFFFFFFFU)

#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_RESETVAL (0x00000000U)

/* LOCK0_KICK1 */

#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_MASK     (0xFFFFFFFFU)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_MAX      (0xFFFFFFFFU)

#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_RESETVAL (0x00000000U)

/*Control MMRs partition*/
#define MSS_CTRL_PARTITION0       (1)
#define TOP_CTRL_PARTITION0       (2)
#define CONTROLSS_CTRL_PARTITION0 (3)

/*Clock and reset MMRs partition*/
#define MSS_RCM_PARTITION0 (4)
#define TOP_RCM_PARTITION0 (5)

#define CSL_CONTROLSS_CTRL_EPWM_STATICXBAR_SEL0 (0x00000004U)
#define CSL_CONTROLSS_INTXBAR_U_BASE            (0x502D5000UL)

/* define the unlock and lock values for MSS_CTRL, TOP_CTRL, MSS_RCM, TOP_RCM*/
#define TEST_KICK_LOCK_VAL    (0x00000000U)
#define TEST_KICK0_UNLOCK_VAL (0x01234567U)
#define TEST_KICK1_UNLOCK_VAL (0x0FEDCBA8U)

/** @brief Number of ETPWM instances */

#define CONTROLSS_CTRL_PARTITION0 (3)

#define INT_XBAR_EPWM0_INT   (0x00000001)
#define INT_XBAR_EPWM1_INT   (0x00000002)
#define INT_XBAR_EPWM2_INT   (0x00000004)
#define INT_XBAR_EPWM3_INT   (0x00000008)
#define INT_XBAR_EPWM4_INT   (0x00000010)
#define INT_XBAR_EPWM5_INT   (0x00000020)
#define INT_XBAR_EPWM6_INT   (0x00000040)
#define INT_XBAR_EPWM7_INT   (0x00000080)
#define INT_XBAR_EPWM8_INT   (0x00000100)
#define INT_XBAR_EPWM9_INT   (0x00000200)
#define INT_XBAR_EPWM0_TZINT (0x00000001)
#define INT_XBAR_EPWM1_TZINT (0x00000002)
#define INT_XBAR_EPWM2_TZINT (0x00000004)
#define INT_XBAR_EPWM3_TZINT (0x00000008)
#define INT_XBAR_EPWM4_TZINT (0x00000010)
#define INT_XBAR_EPWM5_TZINT (0x00000020)
#define INT_XBAR_EPWM6_TZINT (0x00000040)
#define INT_XBAR_EPWM7_TZINT (0x00000080)
#define INT_XBAR_EPWM8_TZINT (0x00000100)
#define INT_XBAR_EPWM9_TZINT (0x00000200)

/* G2 Mask to enable ADC module. */
#define INT_XBAR_ADC0_INT1   (0x00000001)
#define INT_XBAR_ADC0_INT2   (0x00000002)
#define INT_XBAR_ADC0_INT3   (0x00000004)
#define INT_XBAR_ADC0_INT4   (0x00000008)
#define INT_XBAR_ADC0_EVTINT (0x00000010)
#define INT_XBAR_ADC1_INT1   (0x00000020)
#define INT_XBAR_ADC1_INT2   (0x00000040)
#define INT_XBAR_ADC1_INT3   (0x00000080)
#define INT_XBAR_ADC1_INT4   (0x00000100)
#define INT_XBAR_ADC1_EVTINT (0x00000200)
#define INT_XBAR_ADC2_INT1   (0x00000400)
#define INT_XBAR_ADC2_INT2   (0x00000800)
#define INT_XBAR_ADC2_INT3   (0x00001000)
#define INT_XBAR_ADC2_INT4   (0x00002000)
#define INT_XBAR_ADC2_EVTINT (0x00004000)

#define CSL_TOP_CTRL_ADC_REFBUF0_CTRL      (0x00000C00U)
#define CSL_TOP_CTRL_ADC_REFBUF1_CTRL      (0x00000C04U)
#define CSL_TOP_CTRL_U_BASE                (0x50D80000U)
#define CSL_TOP_CTRL_ADC_REF_COMP_CTRL     (0x00000C08U)
#define CSL_TOP_CTRL_ADC_REF_GOOD_STATUS   (0x00000C0CU)
#define CSL_TOP_CTRL_VMON_CTRL             (0x00000C10U)
#define CSL_TOP_CTRL_VMON_STAT             (0x00000C14U)
#define CSL_TOP_CTRL_PMU_COARSE_STAT       (0x00000C18U)
#define CSL_TOP_CTRL_MASK_VMON_ERROR_ESM_H (0x00000C20U)
#define CSL_TOP_CTRL_MASK_VMON_ERROR_ESM_L (0x00000C24U)
#define CSL_TOP_CTRL_MASK_ANA_ISO          (0x00000C30U)
#define CSL_TOP_CTRL_VMON_FILTER_CTRL      (0x00000C34U)

#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_0  146
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_1  147
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_2  148
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_3  149
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_4  150
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_5  151
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_6  152
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_7  153
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_8  154
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_9  155
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_10 156
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_11 157
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_12 158
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_13 159
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_14 160
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_15 161
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_16 162
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_17 163
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_18 164
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_19 165
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_20 166
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_21 167
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_22 168
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_23 169
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_24 170
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_25 171
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_26 172
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_27 173
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_28 174
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_29 175
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_30 176
#define ADC_CORE0_CONTROLSS_INTRXBAR0_OUT_31 177

/** \brief Default APP Loop Count */
#define ADC_APP_LOOP_CNT (5U)

/* Application Name. */
#define ADC_APP_NAME "ADC_APP"

#endif /* ADCAPP_STARTUP_H_ */
