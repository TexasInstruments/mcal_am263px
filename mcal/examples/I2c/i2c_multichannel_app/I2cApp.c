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
 *  \file     I2cApp.c
 *
 *  \brief    This file contains the I2C multi-channel test example.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "I2cApp.h"

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

static void I2c_appTest(void);
static void I2c_appInit(void);
static void I2c_appDeInit(void);
static void I2c_appInterruptConfig(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test pass flag */
static uint32 gTestPassed = E_OK;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    I2c_appInit();
    I2c_appTest();
    I2c_appDeInit();

    return 0;
}

static void I2c_appTest(void)
{
    return;
}

static void I2c_appInit(void)
{
    Std_VersionInfoType versioninfo;

    I2c_appPlatformInit();
    I2c_appInterruptConfig();
    AppUtils_printf(APP_NAME ": STARTS !!!\r\n");

    Cdd_I2c_Init(NULL_PTR);
    /* Get and print version */
    Cdd_I2c_GetVersionInfo(&versioninfo);
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " \r\n");
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " I2C MCAL Version Info\r\n");
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " ---------------------\r\n");
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " \r\n");

    return;
}

static void I2c_appDeInit(void)
{
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, APP_NAME ": Stack Usage: %d bytes\n\r",
              AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": Stack/section corruption!!!\n\r");
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

    Cdd_I2c_DeInit();
    I2c_appPlatformDeInit();

    return;
}

static void I2c_appInterruptConfig(void)
{
    Vim_IntCfg intCfg;

    vimInit();
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;
    /* I2C0 interrupt */
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
    intCfg.intNum = I2C0_INT;
#endif
#if defined(AM261X_PLATFORM)
    intCfg.intNum = I2C0_IRQ;
#endif
    intCfg.handler  = &Cdd_I2c_HwUnit0_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);

#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
    /* I2C2 interrupt */
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = I2C2_INT;
    intCfg.handler  = &Cdd_I2c_HwUnit2_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
#endif
}

void I2c_Seq0_Complete(void)
{
    return;
}

void I2c_Seq1_Complete(void)
{
    return;
}

void I2c_Seq2_Complete(void)
{
    return;
}

void I2c_Seq3_Complete(void)
{
    return;
}

void I2c_Seq0_Fail(uint8 Error_Code)
{
    return;
}

void I2c_Seq1_Fail(uint8 Error_Code)
{
    return;
}

void I2c_Seq2_Fail(uint8 Error_Code)
{
    return;
}

void I2c_Seq3_Fail(uint8 Error_Code)
{
    return;
}

void SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
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
