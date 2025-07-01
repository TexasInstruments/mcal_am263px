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
 *  \file     WdgApp.c
 *
 *  \brief    The WDG test example to test skip force reset ON configuration.
 *
 *  This WDG application configures the watchdog in NMI mode of
 *  operation with skip force reset flag as ON. It then services the watchdog
 *  for a amount of time greater than the expiry period of the watchdog.
 *
 *  After this sets the trigger condition to 0 ms. Since the skip force reset
 *  flag is ON the watchdog won't cause system reset immediately and the
 *  application will continue to execute printing the pass/fail prints
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "WdgApp.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Trace mask */
#define WDG_APP_TRACE_MASK (GT_INFO1 | GT_TraceState_Enable)

/* WDG valid service loop - this should be greater than expiry period of WDG */
#define WDG_APP_WAIT_TIME_MS (1U)
#define WDG_APP_LOOP_CNT     (5000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void   Wdg_appTest(void);
static void   Wdg_appIsr(void);
static void   Wdg_appInit(void);
static void   Wdg_appDeInit(void);
static void   Wdg_appInterruptConfig(void);
static uint32 Wdg_appPreloadToMsec(uint32 preloadVal);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test pass flag */
static uint32 gTestPassed = E_OK;

uint32 volatile gWdgAppIntrCount = 0U;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    Wdg_appInit();
    Wdg_appTest();
    Wdg_appDeInit();

    return 0;
}

static void Wdg_appTest(void)
{
    uint32                loopcnt;
    Std_ReturnType        retVal;
    const Wdg_ConfigType *pWdgCfg = &WdgSettingsConfig;

    /* Trigger once in slow mode - we are safe to do from task context as window is 100% */
    Wdg_SetTriggerCondition(Wdg_appPreloadToMsec(pWdgCfg->slowModeCfg.preloadValue));

    /* Change to fast mode after init phase */
    retVal = Wdg_SetMode(WDGIF_FAST_MODE);
    if (retVal != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(WDG_APP_TRACE_MASK, GT_ERR, " Err: Wdg_SetMode to WDGIF_FAST_MODE failed!!\r\n");
    }

    /* Keep servicing WDG in a loop */
    GT_2trace(WDG_APP_TRACE_MASK, GT_INFO, " Servicing WDG for %d iterations of %d ms each ...\r\n", WDG_APP_LOOP_CNT,
              WDG_APP_WAIT_TIME_MS);
    loopcnt = 0U;
    while (loopcnt++ < WDG_APP_LOOP_CNT)
    {
        /* Service WDG - we are safe to do from task context as window is 100% */
        Wdg_SetTriggerCondition(Wdg_appPreloadToMsec(pWdgCfg->fastModeCfg.preloadValue));
        AppUtils_delay(WDG_APP_WAIT_TIME_MS);
    }
    GT_0trace(WDG_APP_TRACE_MASK, GT_INFO, " Serviced WDG!!\r\n");
    if (gWdgAppIntrCount != 0U)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(WDG_APP_TRACE_MASK, GT_ERR, " Err: WDG expired while servicing!!\r\n");
    }

    /* Set trigger mode to 0 timeout - this shouldn't generate system reset since we
     * have disabled this in WDG config */
    GT_0trace(WDG_APP_TRACE_MASK, GT_INFO,
              " Setting trigger condition to 0 ms and no system reset should happen ...\r\n");
    Wdg_SetTriggerCondition(0U);

    return;
}

static void Wdg_appIsr(void)
{
    gWdgAppIntrCount++;
}

static void Wdg_appInit(void)
{
    Std_VersionInfoType   versioninfo;
    const Wdg_ConfigType *pWdgCfg = &WdgSettingsConfig;

    Wdg_appPlatformInit();
    Wdg_appInterruptConfig();
    AppUtils_printf(APP_NAME ": STARTS !!!\r\n");

    /* Get and print version */
    Wdg_GetVersionInfo(&versioninfo);
    GT_0trace(WDG_APP_TRACE_MASK, GT_INFO, " \r\n");
    GT_0trace(WDG_APP_TRACE_MASK, GT_INFO, " WDG MCAL Version Info\r\n");
    GT_0trace(WDG_APP_TRACE_MASK, GT_INFO, " ---------------------\r\n");
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(WDG_APP_TRACE_MASK, GT_INFO, " \r\n");
    /* Print Wdg config info */
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " Inital Timeout      : %d ms\r\n",
              Wdg_appPreloadToMsec(pWdgCfg->initialTimeOut));
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " Fastmode Timeout    : %d ms\r\n",
              Wdg_appPreloadToMsec(pWdgCfg->fastModeCfg.preloadValue));
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, " Slowmode Timeout    : %d ms\r\n",
              Wdg_appPreloadToMsec(pWdgCfg->slowModeCfg.preloadValue));
    GT_0trace(WDG_APP_TRACE_MASK, GT_INFO, " \r\n");

    Wdg_Init(pWdgCfg);

    return;
}

static void Wdg_appDeInit(void)
{
    GT_1trace(WDG_APP_TRACE_MASK, GT_INFO, APP_NAME ": Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(WDG_APP_TRACE_MASK, GT_ERR, APP_NAME ": Err: Stack/section corruption!!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        AppUtils_printf(APP_NAME ": DONE (Passed) !!!\r\n");
        AppUtils_printf(APP_NAME ": All tests have passed\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
    }
    else
    {
        AppUtils_printf(APP_NAME ": DONE (Failed) !!!\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_FAIL);
    }

    Wdg_appPlatformDeInit();

    return;
}

static void Wdg_appInterruptConfig(void)
{
    Vim_IntCfg intCfg;

    vimInit();

    /* Register NMI generated by WDT expiration */
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = RTI_WDT0_NMI;
    intCfg.handler  = Wdg_appIsr;
    intCfg.priority = VIM_PRIORITY_10;
    vimRegisterInterrupt(&intCfg);

    return;
}

static uint32 Wdg_appPreloadToMsec(uint32 preloadVal)
{
    uint32 preloadValMsec;

    /*
     * The expiration time of the DWD Down Counter can be determined with following equation:
     *  texp= ((RTI_DWDPRLD + 1) x (2^13) ) / RTI_FCLK
     */
    preloadValMsec = (preloadVal + 1U) * 8192U;
    preloadValMsec = preloadValMsec / (WDG_RTI_FREQUENCY * 1000U);

    return preloadValMsec;
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

void SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
