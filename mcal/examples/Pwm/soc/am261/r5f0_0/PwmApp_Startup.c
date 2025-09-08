/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     PwmApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "sys_common.h"
#include "PwmApp.h"
#include "PwmApp_Startup.h"
#include "sys_vim.h"
#include "Pwm_Irq.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**< Flag used for Demo status */
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
volatile uint32 Pwm_App_NotifyCnt = 0;
#endif

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) Mcu_Config;
#endif

volatile uint32 Pwm_NotifyRecvFlag              = 0xFFFF;
uint8           Pwm_Valid_WakeupSrcDetectedFlag = (uint8)FALSE;

Mcu_ClockConfigType Pwm_Mcu_ClkConfig[] = {
    [0] =
        {
            .Mcu_InitCfg       = TRUE,
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_SYSCLK,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0U  // Source = Sysclk ie 200MHz, so (200/(0+1) = 200MHz with 200MHz clk)
        },
    [1] = {
        .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_SCI0,
        .Mcu_ClockSourceId = MCU_CLKSRC_3,
        .Mcu_ClockDiv      = 3,
        .Mcu_InitCfg       = TRUE,
    }};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static inline void EPWM_PWMconfigureSignal1(uint32 base);
static inline void SOC_xbarSelectInterruptXBarInputSource(uint32 base, uint8 out, uint32 group0_mask,
                                                          uint32 group1_mask, uint32 group2_mask, uint32 group3_mask,
                                                          uint32 group4_mask, uint32 group5_mask, uint32 group6_mask);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void               PwmApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();
    /*	initializing interrupt	*/
    Pwm_App_InterruptInit();
    /*	timer initialization	*/
}
void Pwm_App_InterruptInit(void)
{
    vimInit();
    Pwm_App_InterruptConfig(0);
}
void Pwm_App_InterruptConfig(uint32 channelId)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_0;
    intCfg.handler  = Pwm_Ch9Isr;
    intCfg.priority = 15;
    vimRegisterInterrupt(&intCfg);
}

void Pwm_App_InterruptDisable(uint32 channelId)
{
    switch (channelId)
    {
        case 0:
            vimDisableInterrupt(MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_0);
            break;
        case 1:
            vimDisableInterrupt(MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_1);
            break;
    }
#ifdef PWMTIMER_QT
    AppUtils_delay(2U);
#else
    AppUtils_delay(20U);
#endif
    return;
}

void Pwm_App_PlatformInit(void)
{
    AppUtils_TimerInit();

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&Mcu_Config);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&Port_Config);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    Enable_Uart();
    AppUtils_TimerDeinit();
    return;
}

void Example_Pwminit(void)
{
    AppUtils_TimerInit();
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
    const Pwm_ConfigType *pCfgPtr = &Pwm_Config;
    Pwm_Init(pCfgPtr);
    AppUtils_delay(1000U);
}

uint32 Example_PwmCalperiod(uint32 inputfreq)
{
    uint32                period;
    uint32                clkSrc;
    const Pwm_ConfigType *pConfgPtr = &Pwm_Config;
    /* 50% duty cycle */
    /* Counter Direction set is - UPDOWN Mode to generate a symmetric PWM
     * PRD = (TBCLK/PWM_FREQ) / 2
     * TBCLK = (SYSCLK / (HSPCLKDIV x CLKDIV) , PWM_FREQ = 1 / TPWM
     * SYSCLK - System Clock(PWM_SYS_CLOCK)
     * HSPCLKDIV and CLKDIV are Prescalers to calculate Time base clock
     * Please refer PWM User guide for more details
     * Make sure period changed should use same prescalers used in init */
    clkSrc = pConfgPtr->chCfg[0].instanceClkHz;
    period = (clkSrc / (4U * 1U));     /* Prescalers */
    period = (period / inputfreq) / 2; /* UPDOWN Mode  */

    return period;
}

void Example_PwmTest_EHPWM(void)
{
#if defined TEST_EHRPWM
    uint32 period;
    uint32 clkSrc;
    uint32 inputduty;
    uint32 inputfreq;

#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
    AppUtils_printf(" \n");
    AppUtils_printf(APP_NAME ": Changing Frequency from 1kHz to 1.25MHz and Duty Cycle to 40.5%%\n\r");

    inputfreq = 1250000U;
    /* 50% duty cycle */
    /* Counter Direction set is - UPDOWN Mode to generate a symmetric PWM
     * PRD = (TBCLK/PWM_FREQ) / 2
     * TBCLK = (SYSCLK / (HSPCLKDIV x CLKDIV) , PWM_FREQ = 1 / TPWM
     * SYSCLK - System Clock(PWM_SYS_CLOCK)
     * HSPCLKDIV and CLKDIV are Prescalers to calculate Time base clock
     * Please refer PWM User guide for more details
     * Make sure period changed should use same prescalers used in init */
    clkSrc = pCfgPtr->chCfg[0].instanceClkHz;
    period = (clkSrc / (4U * 1U)); /* Prescalers */
    period = (period / inputfreq); /* UPDOWN Mode  */

    AppUtils_printf(APP_NAME ": period is set to %d\n\r", period);
    inputduty = period / 2;
    Pwm_SetPeriodAndDuty(PWM_CHANNEL_0, period, inputduty);
#endif /*PWM_SET_PERIOD_AND_DUTY_API */
    AppUtils_printf(APP_NAME ": This app again waits for 30 seconds please probe\n\r");

    AppUtils_delay(30000);

    AppUtils_printf("PWM Test Passed for configuration!!\n\r");
    AppUtils_printf("PWM Test Completed !!!\n\r");

    AppUtils_printf("PWM Test Completed !!!\n\r");
#endif /* TEST_EHRPWM */
}

void PwmApp_Stop(void)
{
    AppUtils_TimerDeinit();
}

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
void Pwm_Notification_Channel1(void)
{
    Pwm_App_NotifyCnt++;
}

void Pwm_Notification_Channel2(void)
{
    Pwm_App_NotifyCnt++;
}

void Pwm_Notification_Channel3(void)
{
    Pwm_App_NotifyCnt++;
}

void Pwm_Notification_Channel4(void)
{
    Pwm_App_NotifyCnt++;
}
#endif /*#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)*/

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
void Pwm_Example_DisableNotification(void)
{
    if (Pwm_App_NotifyCnt >= 1000)
    {
        AppUtils_printf(APP_NAME ": Chek Isr count 1: %u \n\r", Pwm_App_NotifyCnt);
        Pwm_DisableNotification(PWM_CHANNEL);
    }
    else
    {
        /*do nothing*/
    }
}
#endif /*#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)*/
