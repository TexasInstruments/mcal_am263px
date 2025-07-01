/* ======================================================================
 *   Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file     CddCmpssApp.c
 *
 *  \brief    This file contains the CMPSS test example
 *
 * This example enables the CMPSS High comparator and feeds the
 * asynchronous output to GPIO and EPWM.
 *
 * This example enables the CMPSSA1 COMPH comparator and feeds the asynchronous
 * CTRIPOUTH signal to the XBAROUT0 pin and CTRIPH to EPWM0B.
 *
 * CMPSS is configured to generate trip signals to trip the EPWM signals.
 * CMPIN1P is used to give positive input and internal DAC is configured
 * to provide the negative input. Internal DAC is configured to provide a
 * signal at VDD/2. An EPWM signal is generated at EPWM0B and is configured
 * to be tripped by CTRIPH. This is done via PWM XBAR output 3 configuration.
 *
 * \note When no input is provided, the analog input is not fixed and hence
 * the result is not deterministic. Most cases it is seen that the CMPSS trips
 * the PWM when no input is provided
 *
 * When a low input(VSS) is provided to CMPIN1P,
 *     - Trip signal(XBAROUT0) output is low
 *     - EPWM0B gives a PWM signal
 *
 * When a high input(higher than VDD/2) is provided to CMPIN1P,
 *     - Trip signal(XBAROUT0) output turns high
 *     - EPWM0B gets tripped and outputs as high
 *
 * External Connections \n
 *  - Give input on CMPIN1P (ControlCard HSEC Pin 15)
 *    - AM263x and AM263Px
 *      - For low input (no trip), connect J6 Pin 9 (0v/GND) to HSEC pin 15
 *      - For high input (trips pwm), connect J6 Pin 10 (3.3v/VCC) to HSEC pin 15
 *    - AM261x
 *      - For low input (no trip), connect any (0v/GND) pin to HSEC pin 15
 *      - For high input (trips pwm), connect any (3.3v/VCC) to HSEC pin 15
 *
 *  - Outputs can be observed on
 *    - XBAROUT0 (SOC pin QSPI0_CSN1. USER_LED1 on ControlCard)
 *    - EPWM0B (ControlCard HSEC pin 51) using an oscilloscope
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "CddCmpssApp.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void CddCmpss_appInit(void);
static void CddCmpss_appDeInit(void);
static void CddCmpss_appConfigCmpss(void);
static void CddCmpss_appConfigPwm(void);
static void CddCmpss_appConfigIntr(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test pass flag */
static uint32          gTestPassed = E_OK;
/* Callback notification flags */
volatile static uint32 gCddPwmAppNotifyCnt   = 0U;
volatile static uint32 gCddPwmAppTzNotifyCnt = 0U;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint16  cmpssStatus;
    uint32  xbarStatus;
    boolean pwmStatus;
    uint32  output_group_mask[MCU_OUTPUT_XBAR_NUM_GROUPS];

    CddCmpss_appInit();

    CddCmpss_appConfigXbar();
    CddCmpss_appConfigCmpss();
    CddCmpss_appConfigPwm();
    CddCmpss_appConfigIntr();

    /* Wait for PWM to trip */
    while (1U)
    {
        if (gCddPwmAppTzNotifyCnt != 0U)
        {
            AppUtils_printf(APP_NAME ": PWM tripped!!!\r\n");
            break;
        }
    }

    /* Check PWM status */
    pwmStatus = Cdd_Pwm_TzGetEventStatus(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_OST);
    if (pwmStatus == TRUE)
    {
        AppUtils_printf(APP_NAME ": PWM one-shot trip event status set!!!\r\n");
    }
    else
    {
        AppUtils_printf(APP_NAME ": PWM one-shot trip event status not set. Failed!!!\r\n");
        gTestPassed = E_NOT_OK;
    }
    pwmStatus = Cdd_Pwm_TzGetEventStatus(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_INT);
    if (pwmStatus == TRUE)
    {
        AppUtils_printf(APP_NAME ": PWM latched trip interrupt status set!!!\r\n");
    }
    else
    {
        AppUtils_printf(APP_NAME ": PWM latched trip interrupt status not set. Failed!!!\r\n");
        gTestPassed = E_NOT_OK;
    }

    /* Check CMPSS status */
    cmpssStatus = Cdd_Cmpss_GetStatus(CMPSS_APP_CMPSS_HW_ID);
    if (((cmpssStatus & CDD_CMPSS_STS_HI_FILTOUT) == CDD_CMPSS_STS_HI_FILTOUT) &&
        ((cmpssStatus & CDD_CMPSS_STS_LO_FILTOUT) == CDD_CMPSS_STS_LO_FILTOUT))
    {
        AppUtils_printf(APP_NAME ": CMPSS HI and LO filter out status set!!!\r\n");
    }
    else
    {
        /* Note: this is a not a failure as this is current status and can potentially
         * change based on current input provided compared to when the PWM was tripped.
         * So don't fail the testcase */
        AppUtils_printf(APP_NAME ": CMPSS HI and LO filter out status not set!!!\r\n");
    }
    if (((cmpssStatus & CDD_CMPSS_STS_HI_LATCHFILTOUT) == CDD_CMPSS_STS_HI_LATCHFILTOUT) &&
        ((cmpssStatus & CDD_CMPSS_STS_LO_LATCHFILTOUT) == CDD_CMPSS_STS_LO_LATCHFILTOUT))
    {
        AppUtils_printf(APP_NAME ": CMPSS HI and LO latched filter out status set!!!\r\n");
    }
    else
    {
        AppUtils_printf(APP_NAME ": CMPSS HI and LO latched filter out status not set. Failed!!!\r\n");
        gTestPassed = E_NOT_OK;
    }

    /* Check output XBAR status */
    xbarStatus = MCU_xbarGetOutputXBarOutputSignalStatus();
    if (xbarStatus & (1U << CMPSS_APP_OUTPUT_XBAR_OUT))
    {
        AppUtils_printf(APP_NAME ": Output XBAR status set!!!\r\n");
    }
    else
    {
        /* Note: this is a not a failure as this is current status and can potentially
         * change based on current input provided compared to when the PWM was tripped.
         * So don't fail the testcase */
        AppUtils_printf(APP_NAME ": Output XBAR status not set!!!\r\n");
    }
    xbarStatus = MCU_xbarGetOutputXBarOutputSignalLatchedFlag();
    if (xbarStatus & (1U << CMPSS_APP_OUTPUT_XBAR_OUT))
    {
        AppUtils_printf(APP_NAME ": Output XBAR latched status set!!!\r\n");
    }
    else
    {
        AppUtils_printf(APP_NAME ": Output XBAR latched status not set. Failed!!!\r\n");
        gTestPassed = E_NOT_OK;
    }

    /* Disable CMPSS and clear all status */
    Cdd_Cmpss_DisableModule(CMPSS_APP_CMPSS_HW_ID);
    Cdd_Cmpss_ClearFilterLatchHigh(CMPSS_APP_CMPSS_HW_ID);
    Cdd_Cmpss_ClearFilterLatchLow(CMPSS_APP_CMPSS_HW_ID);

    /* Disable Output XBAR and clear all status */
    for (uint32 i = 0U; i < MCU_OUTPUT_XBAR_NUM_GROUPS; i++)
    {
        output_group_mask[i] = MCU_OUTPUT_XBAR_GROUP_MASK_NONE;
    }
    MCU_xbarSelectOutputXBarInputSource(CMPSS_APP_OUTPUT_XBAR_OUT, output_group_mask);
    MCU_xbarClearOutputXBarOutputSignalLatchedFlag(1U << CMPSS_APP_OUTPUT_XBAR_OUT);

    /* Disable PWM and clear all status */
    Cdd_Pwm_TzIntrDisable(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_EVENT_ONE_SHOT);
    Cdd_Pwm_DisableNotification(CMPSS_APP_PWM_CH_ID);
    Cdd_Pwm_StopChannelCounter(CMPSS_APP_PWM_CH_ID);
    Cdd_Pwm_TzEventStatusClear(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_CBC, 0xFFFFU);
    Cdd_Pwm_TzEventStatusClear(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_OST, 0xFFFFU);
    Cdd_Pwm_TzEventStatusClear(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_INT, 0xFFFFU);

    CddCmpss_appDeInit();

    return 0;
}

void Cdd_Pwm_Notification_Channel(void)
{
    gCddPwmAppNotifyCnt++;
}

void Cdd_Pwm_Tz_Notification_Channel(void)
{
    gCddPwmAppTzNotifyCnt++;
}

static void CddCmpss_appConfigCmpss(void)
{
    uint16                   samplePrescale, sampleWindow, threshold;
    Cdd_Cmpss_RampConfigType rampCfg;

    /* Sets the configuration for the high and low comparator */
    Cdd_Cmpss_ConfigHighComparator(CMPSS_APP_CMPSS_HW_ID, CDD_CMPSS_INSRC_DAC);
    Cdd_Cmpss_ConfigLowComparator(CMPSS_APP_CMPSS_HW_ID, CDD_CMPSS_INSRC_PIN_INL);

    /* Sets the configuration for the internal comparator DACs */
    Cdd_Cmpss_ConfigDAC(CMPSS_APP_CMPSS_HW_ID, CDD_CMPSS_DACVAL_SYSCLK | CDD_CMPSS_DACREF_VDDA | CDD_CMPSS_DACSRC_SHDW);

    /* Configures the digital filter of the high and low comparator */
    samplePrescale = 0U;
    sampleWindow   = 1U;
    threshold      = 1U;
    Cdd_Cmpss_ConfigFilterHigh(CMPSS_APP_CMPSS_HW_ID, samplePrescale, sampleWindow, threshold);
    Cdd_Cmpss_ConfigFilterLow(CMPSS_APP_CMPSS_HW_ID, samplePrescale, sampleWindow, threshold);

    /* Sets the output signal configuration for the high and low comparator */
    Cdd_Cmpss_ConfigOutputsHigh(CMPSS_APP_CMPSS_HW_ID, CDD_CMPSS_TRIPOUT_ASYNC_COMP | CDD_CMPSS_TRIP_ASYNC_COMP);
    Cdd_Cmpss_ConfigOutputsLow(CMPSS_APP_CMPSS_HW_ID, CDD_CMPSS_TRIPOUT_ASYNC_COMP | CDD_CMPSS_TRIP_ASYNC_COMP);

    /* Sets the comparator hysteresis settings */
    Cdd_Cmpss_SetComparatorHighHysteresis(CMPSS_APP_CMPSS_HW_ID, 0U);
    Cdd_Cmpss_SetComparatorLowHysteresis(CMPSS_APP_CMPSS_HW_ID, 0U);

    /* Configures the comparator subsystem's ramp generator */
    rampCfg.MaxRampVal     = 0U;
    rampCfg.DecrementVal   = 0U;
    rampCfg.DelayVal       = 0U;
    rampCfg.PwmSyncSrc     = CMPSS_APP_CMPSS_RAMP_SRC;
    rampCfg.UseRampValShdw = true;
    Cdd_Cmpss_ConfigRamp(CMPSS_APP_CMPSS_HW_ID, &rampCfg);

    /* Sets the value of the internal DAC of the high and low comparator */
    Cdd_Cmpss_SetDACValueHigh(CMPSS_APP_CMPSS_HW_ID, CMPSS_APP_CMPSS_DAC_HIGH_VAL);
    Cdd_Cmpss_SetDACValueLow(CMPSS_APP_CMPSS_HW_ID, CMPSS_APP_CMPSS_DAC_LOW_VAL);

    /* Sets the ePWM module blanking signal that holds trip in reset */
    Cdd_Cmpss_ConfigBlanking(CMPSS_APP_CMPSS_HW_ID, CMPSS_APP_CMPSS_BLANK_SRC);
    /* Disables an ePWM blanking signal from holding trip in reset */
    Cdd_Cmpss_DisableBlanking(CMPSS_APP_CMPSS_HW_ID);

    /* Disables diode emulation mode */
    Cdd_Cmpss_DisableDEmode(CMPSS_APP_CMPSS_HW_ID);
    /* Configures whether or not the digital filter latches are reset by PWMSYNC */
    Cdd_Cmpss_ConfigLatchOnPWMSYNC(CMPSS_APP_CMPSS_HW_ID, false, false);

    /* Enables the CMPSS module */
    Cdd_Cmpss_EnableModule(CMPSS_APP_CMPSS_HW_ID);

    /* Delay for CMPSS DAC to power up */
    AppUtils_delay(1U);
}

static void CddCmpss_appConfigPwm(void)
{
    Cdd_Pwm_Init(&CddPwmConfigSet_0);

    /* Clear all status */
    Cdd_Pwm_TzEventStatusClear(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_CBC, 0xFFFFU);
    Cdd_Pwm_TzEventStatusClear(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_OST, 0xFFFFU);
    Cdd_Pwm_TzEventStatusClear(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_STS_FLG_INT, 0xFFFFU);

    /* Enable the One Shot Trip events */
    Cdd_Pwm_TzIntrEnable(CMPSS_APP_PWM_CH_ID, CDD_PWM_TZ_EVENT_ONE_SHOT);
}

static void CddCmpss_appConfigIntr(void)
{
    Vim_IntCfg intCfg;

    vimInit();

    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_5;
    intCfg.handler  = Cdd_Pwm_G0_Ch0Isr;
    intCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&intCfg);

    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_6;
    intCfg.handler  = Cdd_Pwm_G0_TzCh0Isr;
    intCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&intCfg);
}

static void CddCmpss_appInit(void)
{
#if (STD_ON == CDD_CMPSS_VERSION_INFO_API)
    Std_VersionInfoType versioninfo;
#endif /* #if (STD_ON == CDD_CMPSS_VERSION_INFO_API) */

    CddCmpss_appPlatformInit();
    AppUtils_printf(APP_NAME ": Asynchronous trip - STARTS !!!\r\n");

#if (STD_ON == CDD_CMPSS_VERSION_INFO_API)
    /* Get and print version */
    Cdd_Cmpss_GetVersionInfo(&versioninfo);
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " \r\n");
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " CMPSS MCAL Version Info\r\n");
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " ---------------------\r\n");
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " \r\n");
#endif /* #if (STD_ON == CDD_CMPSS_VERSION_INFO_API) */
}

static void CddCmpss_appDeInit(void)
{
    Cdd_Pwm_DeInit();

    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, "\nCDD_CMPSS_APP: Stack Usage: %d bytes\n\r",
              AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, "CDD_CMPSS Stack/section corruption!!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        AppUtils_printf(APP_NAME ": Asynchronous trip - DONE (Passed) !!!\r\n");
        AppUtils_printf(APP_NAME ": All tests have passed\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
    }
    else
    {
        AppUtils_printf(APP_NAME ": Asynchronous trip - DONE (Failed) !!!\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_FAIL);
    }

    CddCmpss_appPlatformDeInit();
}

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0(void)
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

void SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
