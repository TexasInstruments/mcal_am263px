/* ======================================================================
 *   Copyright (C) 2024 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     CddPwmApp.c
 *
 *  \brief    This file contains the CDD PWM Trip zone feature test example
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
static uint32   Cdd_Pwm_App_mainTest(void);
uint32          CddPwmTestCalperiod(uint32 inputfreq, uint32 dutyCycle);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32          gTestPassed              = E_OK;
uint32          Cdd_Pwm_App_NotifyCnt    = 0U;
volatile uint32 Cdd_Pwm_App_Tz_NotifyCnt = 0U;

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
    uint32 testPassed = E_OK;

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
    uint32                       inputfreq;
    Cdd_Pwm_ChannelType          channelNumber;
    Cdd_Pwm_channelParametertype ChParameter_test;
#endif

#if (CDD_PWM_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
#endif /* #if (CDD_PWM_VERSION_INFO_API == STD_ON) */

    Cdd_Pwm_App_Tz_interruptConfig();
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
    AppUtils_printf(" Keep the GPIO 122 to High State. \r\n\r");
#if (STD_ON == CDD_PWM_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - CDD_PWM PreCompile variant being used !!!\n\r");
    Cdd_Pwm_Init(NULL_PTR);
#else
    AppUtils_printf(APP_NAME ": Variant - CDD_PWM PostBuild variant being used !!!\n\r");
    Cdd_Pwm_Init(&Cdd_Pwm_Config);
#endif
    AppUtils_delay(1000);
    AppUtils_printf(" PWM Signal is generated with default configured parameters. \r\n\r");

#if (STD_ON == CDD_PWM_TRIP_ZONE)
    /* Clear the Status.  */
    /* Trip Zone 3 signal is used. */
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_CBC, 0);
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_CBC, 1);
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_CBC, 2);
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_OST, 0);
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_OST, 1);
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_OST, 2);
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_INT, CDD_PWM_TZ_EVENT_ONE_SHOT);
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_INT, CDD_PWM_TZ_EVENT_CYCLE_BY_CYCLE);

    /* Enable the One Shot Trip events */
    Cdd_Pwm_TzIntrEnable(0, CDD_PWM_TZ_EVENT_ONE_SHOT);
#endif /*#if (STD_ON == CDD_PWM_TRIP_ZONE)*/

    /* Observe the PWM Signal . */
    Cdd_Pwm_App_Tz_NotifyCnt = 0;
    AppUtils_printf(" Wait for sometime and Change the GPIO 122 to Low State from High State. \r\n\r");
    while (1)
    {
        /* Wait for sometime. */
        AppUtils_delay(4000);

        /* Change the GPIO 122 to Low State after sometime. */
        if (Cdd_Pwm_App_Tz_NotifyCnt != 0)
        {
            AppUtils_printf("\r\n\n\rTrip zone signal occurred \r\n\n\r");

            /* Change the GPIO 122 to HIGH State at this stage. */
            /* PWM Signal should be restored after changing to HIGH state */
            break;
        }
    }

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

    /* Enable the CBC Trip events */
    Cdd_Pwm_TzEventStatusClear(0, CDD_PWM_TZ_STS_FLG_INT, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST | EPWM_TZ_FLAG_CBC));
    Cdd_Pwm_TzIntrEnable(0, CDD_PWM_TZ_EVENT_CYCLE_BY_CYCLE);

    /* Observe the PWM Signal . */
    Cdd_Pwm_App_Tz_NotifyCnt = 0;
    AppUtils_printf(" Wait for sometime and Change the GPIO 122 to Low State from High State. \r\n\r");
    while (1)
    {
        /* Wait for sometime. */
        AppUtils_delay(4000);

        /* Change the GPIO 122 to Low State after sometime. */
        if (Cdd_Pwm_App_Tz_NotifyCnt != 0)
        {
            /* Change the GPIO 122 to HIGH State at this stage. */
            /* PWM Signal should be restored after changing to HIGH state */

            AppUtils_printf("\r\n\n\rTrip zone signal occurred \r\n\n\r");

            break;
        }
    }

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
    /* Duty Cycle - 50%, Frequency - 10K */
    channelNumber                  = 0U;
    ChParameter_test.ChannelNumber = channelNumber;
    ChParameter_test.DutyCycle     = 0x8000;
    ChParameter_test.Phase         = 0U;
    ChParameter_test.Output        = CDD_PWM_OUTPUT_CH_BOTH_A_AND_B;
    inputfreq                      = 1000U;
    AppUtils_printf(" PWM Signal is generated with below parameters on Channel A and B Pins. \r\n\r");
    ChParameter_test.Period = CddPwmTestCalperiod(inputfreq, ChParameter_test.DutyCycle);
    Cdd_Pwm_SetPeriodDutyPhase(ChParameter_test);
#endif

    /* Wait for Settle down */
    AppUtils_delay(1000);

#if (STD_ON == CDD_PWM_DEINIT_API)
    Cdd_Pwm_DeInit();
#endif

#if (STD_ON == CDD_PWM_DEINIT_API)
    Cdd_Pwm_App_TimerDeinit();
#endif

    return testPassed;
}

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
void Cdd_Pwm_Notification_Channel(void)
{
    Cdd_Pwm_App_NotifyCnt++;
}
#endif /*#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

void Cdd_Pwm_Tz_Notification_Channel(void)
{
    Cdd_Pwm_App_Tz_NotifyCnt++;
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
