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
 *  \file     AdcApp.c
 *
 *  \brief    This file contains the ADC resolver test example.
 *
 *  This application configures both the ADC-R instances 0 and 1 for all 4 channels as general
 *  purpose ADC. The resolver module is disabled so that ADC can operate as
 *  general purpose ADC.
 *
 *  HW Setup:
 *      Connect the required signals to the below pins in the HSEC Control Card docking station
 *
 *          ADC_R0_AIN0 - ANA25
 *          ADC_R0_AIN1 - ANA27
 *          ADC_R0_AIN2 - ANA28
 *          ADC_R0_AIN3 - ANA30
 *
 *          ADC_R1_AIN0 - ANA31
 *          ADC_R1_AIN1 - ANA33
 *          ADC_R1_AIN2 - ANA34
 *          ADC_R1_AIN3 - ANA36
 *
 * Tips:
 *      - Signals can be connected to GND using any HSEC GND pins (expected result: 0x0000)
 *      - Signals can be connected to 3.3v using J6 pin 10 in base board (expected result: 0x0FFF)
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "AdcApp.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Default stream samples per channel to test - match this to streamNumSamples config parameter */
#define ADC_APP_DEFAULT_STREAM_SAMPLES (1U)
/** \brief Each group read buffer size in samples */
#define ADC_APP_READ_BUF_SIZE_WORD (ADC_APP_DEFAULT_STREAM_SAMPLES * ADC_NUM_CHANNEL)

/* Number of iteration to run test */
#define ADC_APP_LOOPCNT (10U)

/* Trace mask */
#define ADC_APP_TRACE_MASK (GT_INFO1 | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void Adc_appTest(void);
static void Adc_appProcIsr(uint32 grpIdx);
static void Adc_appInit(void);
static void Adc_appDeInit(void);
static void Adc_appInterruptConfig(void);
static void Adc_appPrintResult(uint32 loopcnt);
static void RDC_disableResolver(uint32 baseAddr, boolean enable);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test pass flag */
static uint32 gTestPassed = E_OK;

/* Group conversion done flag */
static volatile uint32 gAdcAppGroupDone[ADC_MAX_GROUP];

/* Setup result buffer passed to driver */
Adc_ValueGroupType gAdcAppSetupBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];

/* App buffer used to read the data back from driver */
Adc_ValueGroupType gAdcAppReadBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    Adc_appInit();
    Adc_appTest();
    Adc_appDeInit();

    return 0;
}

static void Adc_appTest(void)
{
    uint32         testPassed = E_OK;
    Adc_StatusType status;
    Std_ReturnType retVal;

    /* Setup all groups */
    for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        /* Check group status - it should be idle */
        status = Adc_GetGroupStatus(grpIdx);
        if (status != ADC_IDLE)
        {
            testPassed = E_NOT_OK;
            GT_1trace(ADC_APP_TRACE_MASK, GT_ERR, " ADC Group %d is not IDLE!!\r\n", grpIdx);
        }

        retVal = Adc_SetupResultBuffer(grpIdx, &gAdcAppSetupBuffer[grpIdx][0U]);
        if (retVal != E_OK)
        {
            testPassed = E_NOT_OK;
            GT_1trace(ADC_APP_TRACE_MASK, GT_ERR, " ADC Group %d setup buffer failed!!\r\n", grpIdx);
        }
    }

    for (uint32 loopcnt = 0U; loopcnt < ADC_APP_LOOPCNT; loopcnt++)
    {
        /* Reset buffers and flags */
        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            gAdcAppGroupDone[grpIdx] = FALSE;
            memset(&gAdcAppReadBuffer[grpIdx][0U], 0U, (sizeof(Adc_ValueGroupType) * ADC_APP_READ_BUF_SIZE_WORD));
            memset(&gAdcAppSetupBuffer[grpIdx][0U], 0U, (sizeof(Adc_ValueGroupType) * ADC_APP_READ_BUF_SIZE_WORD));
            Adc_EnableGroupNotification(grpIdx);
        }

        /* Start conversion across all groups at same time */
        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            Adc_StartGroupConversion(grpIdx);
        }

        /* Wait for all group conversion to get over */
        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            while (1U)
            {
                if (gAdcAppGroupDone[grpIdx] == TRUE)
                {
                    /* Check group status - it should be idle */
                    status = Adc_GetGroupStatus(grpIdx);
                    if (status != ADC_IDLE)
                    {
                        testPassed = E_NOT_OK;
                        GT_1trace(ADC_APP_TRACE_MASK, GT_ERR, " ADC Group %d is not IDLE!!\r\n", grpIdx);
                    }
                    break;
                }
            }
        }

        /* Disable all groups */
        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            Adc_DisableGroupNotification(grpIdx);
        }

        Adc_appPrintResult(loopcnt);
    }

    if (testPassed != E_OK)
    {
        gTestPassed = E_NOT_OK;
    }

    return;
}

void AdcApp_Group0EndNotification(void)
{
    Adc_appProcIsr(0U);
}

void AdcApp_Group1EndNotification(void)
{
    Adc_appProcIsr(1U);
}

static void Adc_appProcIsr(uint32 grpIdx)
{
    Adc_StatusType status;
    Std_ReturnType retVal;

    /* Check group status - it should be COMPLETED state */
    status = Adc_GetGroupStatus(grpIdx);
    if (status == ADC_STREAM_COMPLETED)
    {
        /* Read and store the result */
        retVal = Adc_ReadGroup(grpIdx, &gAdcAppReadBuffer[grpIdx][0]);
        if (retVal != E_OK)
        {
            gTestPassed = E_NOT_OK;
        }
    }
    else
    {
        gTestPassed = E_NOT_OK;
    }

    gAdcAppGroupDone[grpIdx] = TRUE;

    return;
}

static void Adc_appInit(void)
{
    Std_ReturnType      retVal = E_OK;
    Std_VersionInfoType versioninfo;

    Adc_appPlatformInit();
    Adc_appInterruptConfig();
    AppUtils_printf(APP_NAME ": STARTS !!!\r\n");

    /* RDC should be disabled to use the ADC as general purpose ADC */
    RDC_disableResolver(MCAL_CSL_CONTROLSS_HW_RESOLVER_U_BASE, FALSE);

    Adc_Init(&Adc_Config);

    /* Get and print version */
    Adc_GetVersionInfo(&versioninfo);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " ADC MCAL Version Info\r\n");
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " ---------------------\r\n");
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");

    retVal = Adc_appIoMuxSetup();
    if (retVal != E_OK)
    {
        gTestPassed = E_NOT_OK;
    }

    return;
}

static void Adc_appDeInit(void)
{
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, APP_NAME ": Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(ADC_APP_TRACE_MASK, GT_ERR, APP_NAME ": Stack/section corruption!!!\n\r");
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

    Adc_DeInit();
    Adc_appPlatformDeInit();

    return;
}

static void Adc_appInterruptConfig(void)
{
    Vim_IntCfg intCfg;

    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    /* Use XBAR Interrupt 1 for ADC R0 */
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_1;
    intCfg.handler  = Adc_ADCINT1_IrqUnit5;
    intCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&intCfg);
    /* Configure Interrupt XBAR */
    MCU_xbarSelectInterruptXBarInputSourceExtended(MCU_CSL_CONTROLSS_INTXBAR_U_BASE, MCU_INTRXBAR0_OUT_1, 0U, 0U, 0U,
                                                   0U, 0U, 0U, 0U, MCU_INT_XBAR_ADC_R0_INT1, 0U, 0U);

    /* Use XBAR Interrupt 2 for ADC R1 */
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_2;
    intCfg.handler  = Adc_ADCINT1_IrqUnit6;
    intCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&intCfg);
    /* Configure Interrupt XBAR */
    MCU_xbarSelectInterruptXBarInputSourceExtended(MCU_CSL_CONTROLSS_INTXBAR_U_BASE, MCU_INTRXBAR0_OUT_2, 0U, 0U, 0U,
                                                   0U, 0U, 0U, 0U, MCU_INT_XBAR_ADC_R1_INT1, 0U, 0U);

    return;
}

static void Adc_appPrintResult(uint32 loopcnt)
{
    const Adc_GroupConfigType  *grpCfg;
    const Adc_HwUnitConfigType *hwUnitCfg;

    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO1, " \r\n");
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO1, " Read Buffer Content (Loop %d)\r\n", loopcnt);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO1, " ----------------------------\r\n");
    for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        grpCfg    = &Adc_Config.groupCfg[grpIdx];
        hwUnitCfg = &Adc_Config.hwUnitCfg[grpCfg->hwUnitId];

        GT_3trace(ADC_APP_TRACE_MASK, GT_INFO1, " ADC Group %d, HW Unit %d, Base 0x%08X:\r\n", grpIdx,
                  hwUnitCfg->hwUnitId, hwUnitCfg->baseAddr);
        GT_0trace(ADC_APP_TRACE_MASK, GT_INFO1, " ----------------------------------------\r\n");
        for (uint32 chIdx = 0U; chIdx < grpCfg->numChannels; chIdx++)
        {
            GT_2trace(ADC_APP_TRACE_MASK, GT_INFO1, " CH%d: 0x%08X\r\n", chIdx, gAdcAppReadBuffer[grpIdx][chIdx]);
        }
        GT_0trace(ADC_APP_TRACE_MASK, GT_INFO1, " \r\n");
    }

    return;
}

static void RDC_disableResolver(uint32 baseAddr, boolean enable)
{
    uint32 regVal;

    regVal  = HW_RD_REG32(baseAddr + CSL_RESOLVER_REGS_GLOBAL_CFG);
    regVal &= ~CSL_RESOLVER_REGS_GLOBAL_CFG_MASTER_EN_MASK;
    regVal |= ((uint32)enable << CSL_RESOLVER_REGS_GLOBAL_CFG_MASTER_EN_SHIFT);
    HW_WR_REG32(baseAddr + CSL_RESOLVER_REGS_GLOBAL_CFG, regVal);

    return;
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

void SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
