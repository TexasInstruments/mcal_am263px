/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
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

/**
 *  \file     CddPwmApp.c
 *
 *  \brief    This file contains the CDD PWM test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "assert.h"
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
#include "SchM_Port.h"
/*LDRA_ANALYSIS*/
#include "Det.h"
#include "Dem.h"
#include "SchM_Cdd_Pwm.h"
#include "Mcu.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "Mcu_Cfg.h"
#include "app_utils.h"
#include "sys_common.h"

#include "sys_vim.h"
#include "Cdd_Pwm_App_Startup.h"
#include "Cdd_Pwm_App.h"
#include "Cdd_Pwm_Cfg.h"
#include "Cdd_Pwm.h"
#include "Adc.h"
#include "Adc_Cfg.h"
#include "trace.h"

/* For PRCM base addresses */
#include "soc.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CDD_PWM_RUN_TIME   (2U) /* in secs */
#define GROUP_TEMP_SENSORS (0)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static uint32 Cdd_Pwm_App_mainTest(void);
void          AdcApp_Test(void);
uint32        CddPwmTestCalperiod(uint32 inputfreq, uint32 dutyCycle);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32        gTestPassed           = E_OK;
uint32        Cdd_Pwm_App_NotifyCnt = 0U;

extern const struct Adc_ConfigType_s Adc_Config;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined CLANG

void SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
    return;
}

void SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
    return;
}

void SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif

int main(void)
{
    gTestPassed = E_OK;

    /* Setup Interrupt. */
    Cdd_Pwm_App_Startup();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\r\n");

    gTestPassed = Cdd_Pwm_App_mainTest();

    AppUtils_printf(APP_NAME ": Sample Application - DONE !!!\r\n");

    GT_1trace(McalAppTrace, GT_INFO, " CDD Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());

    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        AppUtils_printf("CDD PWM Stack/section corruption!!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        AppUtils_printf("All tests have passed\n\r");
    }
    else
    {
        AppUtils_printf("Some tests have failed\n\r");
    }

    return (0);
}

static uint32 Cdd_Pwm_App_mainTest(void)
{
    uint32              testPassed    = E_OK;
    Cdd_Pwm_ChannelType channelNumber = 0U;

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
    uint32                       inputfreq;
    Cdd_Pwm_channelParametertype ChParameter_test;
#endif

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    Cdd_Pwm_ChannelType   ChannelParam           = 0U;
    Cdd_Pwm_InterruptType EdgeInterruptSourceAdc = {CDD_PWM_FALLING_EDGE, CDD_PWM_INT_TBCTR_D_CMPA,
                                                    CDD_PWM_INT_TBCTR_ZERO};
    Cdd_Pwm_AdcSocType    Cdd_Pwm_AdcSoc      = {TRUE, CDD_PWM_SOC_A, CDD_PWM_SOC_TBCTR_D_CMPA, CDD_PWM_SOC_TBCTR_ZERO};
    Cdd_Pwm_InterruptType EdgeInterruptSource = {CDD_PWM_FALLING_EDGE, 0, 0};
#endif

#if (CDD_PWM_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
#endif /* #if (CDD_PWM_VERSION_INFO_API == STD_ON) */

    Cdd_Pwm_App_interruptConfig();
    /* Do interrupt config after init to avoid interrupts at start-up when
     * reloading program in CCS */

#if (CDD_PWM_VERSION_INFO_API == STD_ON)
    /* Get and print version */
    Cdd_Pwm_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n\r");
    AppUtils_printf("CDD PWM MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf("Vendor ID           : %d\n\r", versioninfo.vendorID);
    AppUtils_printf("Module ID           : %d\n\r", versioninfo.moduleID);
    AppUtils_printf("SW Major Version    : %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf("SW Minor Version    : %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf("SW Patch Version    : %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n\r");
#endif /* #if (CDD_PWM_VERSION_INFO_API == STD_ON) */

    /* Init */

#if (STD_ON == CDD_PWM_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - CDD_PWM PreCompile variant being used !!!\n\r");
    Cdd_Pwm_Init(NULL_PTR);
#else
    AppUtils_printf(APP_NAME ": Variant - CDD_PWM PostBuild variant being used !!!\n\r");
    Cdd_Pwm_Init(&Cdd_Pwm_Config);
#endif

    AppUtils_delay(1000);
    AppUtils_printf(" PWM Signal is generated with default configured parameters. \r\n\r");

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
    /* Duty Cycle - 75%, Frequency - 10K */
    channelNumber                  = 0U;
    ChParameter_test.ChannelNumber = channelNumber;
    ChParameter_test.DutyCycle     = 49152;
    ChParameter_test.Phase         = 0U;
    ChParameter_test.Output        = CDD_PWM_OUTPUT_CH_BOTH_A_AND_B;
    inputfreq                      = 10000U;
    AppUtils_printf(" PWM Signal is generated with below parameters on Channel A and B Pins. \r\n\r");
    ChParameter_test.Period = CddPwmTestCalperiod(inputfreq, ChParameter_test.DutyCycle);
    Cdd_Pwm_SetPeriodDutyPhase(ChParameter_test);
#endif

    /* Wait for Settle down */
    AppUtils_delay(1000);

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
    /* Duty Cycle - 50%, Frequency - 5K */
    channelNumber                  = 0U;
    ChParameter_test.ChannelNumber = channelNumber;
    ChParameter_test.DutyCycle     = 0x8000;
    ChParameter_test.Phase         = 0U;
    ChParameter_test.Output        = CDD_PWM_OUTPUT_CH_A;
    inputfreq                      = 5000U;
    AppUtils_printf(" PWM Signal is generated with below parameters on Channel A. \r\n\r");
    ChParameter_test.Period = CddPwmTestCalperiod(inputfreq, ChParameter_test.DutyCycle);
    Cdd_Pwm_SetPeriodDutyPhase(ChParameter_test);
#endif

    /* Wait for Settle down */
    AppUtils_delay(1000);

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
    /* Duty Cycle - 25%, Frequency - 5K */
    channelNumber                  = 0U;
    ChParameter_test.ChannelNumber = channelNumber;
    ChParameter_test.DutyCycle     = 0x4000;
    ChParameter_test.Phase         = 0U;
    ChParameter_test.Output        = CDD_PWM_OUTPUT_CH_B;
    inputfreq                      = 5000U;
    AppUtils_printf(" PWM Signal is generated with below parameters on Channel B. \r\n\r");
    ChParameter_test.Period = CddPwmTestCalperiod(inputfreq, ChParameter_test.DutyCycle);
    Cdd_Pwm_SetPeriodDutyPhase(ChParameter_test);
#endif

    /* Wait for Settle down */
    AppUtils_delay(1000);

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    /* Enable Notification. */
    Cdd_Pwm_EnableNotification(ChannelParam, EdgeInterruptSourceAdc);
    Cdd_Pwm_SetAdcTrigger(ChannelParam, Cdd_Pwm_AdcSoc);
#endif /*#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

    /* ADC Test Appl Initiatied */
    AppUtils_printf(" ADC Test Application In Progress. \r\n\r");

    /* Test Adc Module. */
    AdcApp_Test();

    /* ADC Test Appl Passed. */
    AppUtils_printf(" ADC Test Application Passed. \r\n\r");

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    /* Disable the Notification. */
    Cdd_Pwm_AdcSoc.channelEnable = FALSE;
    Cdd_Pwm_DisableNotification(ChannelParam);
    Cdd_Pwm_SetAdcTrigger(ChannelParam, Cdd_Pwm_AdcSoc);
#endif

    /* Interrupt Notification Checking. */
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    /* Enable Notification. */
    Cdd_Pwm_EnableNotification(channelNumber, EdgeInterruptSource);
    AppUtils_printf(" Edge Interrupt is enable. \r\n\r");
#endif

    /* Wait for Settle down */
    AppUtils_delay(1000);

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    AppUtils_printf(" Wait till interrupt is recived. \r\n\r");
    while ((Cdd_Pwm_App_NotifyCnt) < (1000 * CDD_PWM_RUN_TIME))
    {
        /* Wait this Notification is recived */
    }
    AppUtils_printf(" Interrupts Recieved are : %d \r\n\r", Cdd_Pwm_App_NotifyCnt);
#endif

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    Cdd_Pwm_AdcSoc.channelEnable = FALSE;
    Cdd_Pwm_DisableNotification(ChannelParam);
    Cdd_Pwm_SetAdcTrigger(ChannelParam, Cdd_Pwm_AdcSoc);
#endif

#if (STD_ON == CDD_PWM_DEINIT_API)
    Cdd_Pwm_App_TimerDeinit();
#endif

#if (STD_ON == CDD_PWM_DEINIT_API)
    Cdd_Pwm_DeInit();
#endif

    return testPassed;
}

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
void Cdd_Pwm_Notification_Channel(void)
{
    Cdd_Pwm_App_NotifyCnt++;
}
#endif /*#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

void Cdd_Pwm_Tz_Notification_Channel(uint16 Status1, uint16 Status2, uint16 Status3)
{
    Cdd_Pwm_App_NotifyCnt++;
}

void AdcApp_Test(void)
{
    Adc_StatusType status;
    Adc_ConfigType CddPwmAdcConfig;
    uint16         Adc_AppBuffer[6U] = {0, 0, 0, 0, 0, 0};
    uint16         Adc_Group         = 0;

    /* Copy the Config Set of ADC */
    memcpy(&CddPwmAdcConfig, &(Adc_Config), sizeof(Adc_ConfigType));

    /* Change the ADC Trigger source to HW for Group 0 and POLLING. */
    CddPwmAdcConfig.groupCfg[Adc_Group].triggSrc            = ADC_TRIGG_SRC_HW;
    CddPwmAdcConfig.groupCfg[Adc_Group].hwTrigTimer         = ADC_TRIGGER_EPWM0_SOCA;
    CddPwmAdcConfig.groupCfg[Adc_Group].groupDataAccessMode = ADC_GROUP_POLLING_ACCESS;

    /* Initialize ADC. */
    Adc_Init(&CddPwmAdcConfig);
    Adc_SetupResultBuffer(Adc_Group, Adc_AppBuffer);
    Adc_EnableGroupNotification(Adc_Group);

    /* Enable HW Trigger Group. */
    Adc_EnableHardwareTrigger(Adc_Group);

    while (1)
    {
        Adc_PollingMainFunction();

        /* Check group status - it should be COMPLETED state */
        status = Adc_GetGroupStatus(Adc_Group);

        if ((status == ADC_STREAM_COMPLETED) || (status == ADC_COMPLETED))
        {
            /* Disable HW Trigger Group. */
            Adc_DisableHardwareTrigger(Adc_Group);
            break;
        }
    }
}

uint32 CddPwmTestCalperiod(uint32 inputfreq, uint32 dutyCycle)
{
    uint32 inputduty = 0;
    uint32 period    = 0;
    uint32 clkSrc    = 0;

    inputduty = (dutyCycle * 100) / CDD_PWM_DUTYCYCLE_MAX;
    /* Counter Direction set is - UPDOWN Mode to generate a symmetric PWM
     * PRD = (TBCLK/PWM_FREQ) / 2
     * TBCLK = (SYSCLK / (HSPCLKDIV x CLKDIV) , PWM_FREQ = 1 / TPWM
     * SYSCLK - System Clock(PWM_SYS_CLOCK)
     * HSPCLKDIV and CLKDIV are Prescalers to calculate Time base clock
     * Please refer PWM User guide for more details
     * Make sure period changed should use same prescalers used in init */
    clkSrc = CDD_PWM_SYSTEM_CLK_FREQ;
    period = (clkSrc / (4U * 1U));     /* Prescalers */
    period = (period / inputfreq) / 2; /* UPDOWN Mode  */

    /* Print test case information */
    AppUtils_printf(" : PERIOD %d : FREQUENCY %d : DUTYCYCLE in percentage %d : DUTYCYCLE in Count %d : \r\n\r", period,
                    inputfreq, inputduty, dutyCycle);
    return period;
}

void AdcApp_Group0EndNotification(void)
{
}

void AdcApp_Group1EndNotification(void)
{
}

void AdcApp_Group2EndNotification(void)
{
}

void AdcApp_Group3EndNotification(void)
{
}
