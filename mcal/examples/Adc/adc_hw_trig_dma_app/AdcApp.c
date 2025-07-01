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
 *  \brief    This file contains the ADC HW trigger DMA test example
 *
 *  This example configures the ADC in HW trigger and one-shot mode. And then
 *  configures the DMA to capture the ADC result in a buffer periodically
 *  by linking two EDMA params in a circular linked-list mode.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "AdcApp.h"
#include "Epwm_Platform.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Number of channels to test */
#define ADC_APP_NUM_CHANNEL (1U)

/** \brief Default stream samples per channel to test - match this to streamNumSamples config parameter */
#define ADC_APP_DEFAULT_STREAM_SAMPLES (1U)
/** \brief Each group read buffer size in samples */
#define ADC_APP_READ_BUF_SIZE_WORD (ADC_APP_DEFAULT_STREAM_SAMPLES * ADC_APP_NUM_CHANNEL)

/* Number of iteration to run test */
#define ADC_APP_LOOPCNT (10U)

/* DMA group and channel used for testing */
#define ADC_APP_DMA_CHANNEL (0U)
#define ADC_APP_GROUP_ID    (0U)

/* EPWM used for testing */
#define ADC_APP_EPWM_BASE_ADDR (0x50000000U)

/* Log size */
#define ADC_APP_LOG_SIZE (10U)

/* Trace mask */
#define ADC_APP_TRACE_MASK (GT_INFO1 | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct
{
    Adc_ValueGroupType dmaBuff;  /* Log buffer used for DMA*/
    Adc_ValueGroupType hwResult; /* Log ADC HW result*/
    Adc_StatusType     status;   /* Log ADC group status*/
} Adc_AppLog_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void Adc_appTest(void);
static void Adc_appInit(void);
static void Adc_appDeInit(void);
static void Adc_appInterruptConfig(void);
static void Adc_appPrintResult(uint32 loopcnt);
static void Adc_appPrintStatus(uint32 grpIdx, Adc_StatusType status);
static void Adc_appEpwmEnable(uint32 baseAddr);
static void Adc_appDisableTrigger(uint32 baseAddr);
static void Adc_appDmaTransferCallback(void *appData);
static void Adc_appDmaConfigure(const uint16 *destPtr, uint16 length, uint32 dmaCh, uint32 srcAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test pass flag */
static uint32 gTestPassed = E_OK;

/* Setup result buffer passed to driver - otherwise Adc_EnableHardwareTrigger will return error */
static Adc_ValueGroupType gAdcAppSetupBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];
/* Result buffer used by DMA */
static Adc_ValueGroupType gAdcAppDmaBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];

/* DMA callback counter */
static volatile uint32 gAdcAppDmaCallbackCount = 0;

/* Application log */
Adc_AppLog_t gAdcAppLog[ADC_APP_LOG_SIZE];

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
    uint32         dmaDataAddr;

    /* Setup all groups */
    for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        /* Check group status - it should be idle */
        status = Adc_GetGroupStatus(grpIdx);
        Adc_appPrintStatus(grpIdx, status);
        GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");

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
        /* Reset buffers and perform a cache write back */
        memset((void *)&gAdcAppDmaBuffer, 0U, sizeof(gAdcAppDmaBuffer));
        Mcal_CacheP_wb((void *)&gAdcAppDmaBuffer, sizeof(gAdcAppDmaBuffer), Mcal_CacheP_TYPE_ALL);
        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            Adc_EnableGroupNotification(grpIdx);
        }

        /* Enable hardware trigger */
        Adc_EnableHardwareTrigger(ADC_APP_GROUP_ID);
        /* Enable continue to interrupt mode */
        Adc_SetInterruptContinuousMode(ADC_APP_GROUP_ID);

        /* Configure DMA channel */
        dmaDataAddr = Adc_GetReadResultBaseAddress(ADC_APP_GROUP_ID);
        Adc_appDmaConfigure(&gAdcAppDmaBuffer[0U][0U], ADC_APP_NUM_CHANNEL * 2U, ADC_APP_DMA_CHANNEL, dmaDataAddr);

        /* Configure EPWM for ADC trigger */
        Adc_appEpwmEnable(ADC_APP_EPWM_BASE_ADDR);
        EPWM_setTimeBaseCounterMode(ADC_APP_EPWM_BASE_ADDR, EPWM_COUNTER_MODE_UP);

        /* FIXME: Enable EPWM TBCLK SYNC in CONTROLSS_CTRL to start EPWM. Replace with proper macros/APIs */
        *((volatile uint32 *)(0x502F0000 + 0x1008)) = 0x01234567;
        *((volatile uint32 *)(0x502F0000 + 0x100C)) = 0xFEDCBA8;
        *((volatile uint32 *)(0x502F0000 + 0x0010)) = 0x00000001;

        Adc_appPrintResult(loopcnt);

        /* Disable hardware trigger for Group 0*/
        Adc_appDisableTrigger(ADC_APP_EPWM_BASE_ADDR);
        Adc_DisableHardwareTrigger(ADC_APP_GROUP_ID);

        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            Adc_DisableGroupNotification(grpIdx);
        }
    }

    if (testPassed != E_OK)
    {
        gTestPassed = E_NOT_OK;
    }

    return;
}

void AdcApp_Group0EndNotification(void)
{
    /* We never get this as we are using DMA to read the data */
    return;
}

static void Adc_appInit(void)
{
    Std_VersionInfoType versioninfo;

    Adc_appPlatformInit();
    Cdd_Dma_Init(NULL_PTR);
    Adc_Init(&AdcConfigSet);
    Adc_appInterruptConfig();
    Cdd_Dma_CbkRegister(ADC_APP_DMA_CHANNEL, NULL_PTR, &Adc_appDmaTransferCallback);

    AppUtils_printf(APP_NAME ": STARTS !!!\r\n");

    /* ADC - Get and print version */
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

    /* DMA - Get and print version */
    Cdd_Dma_GetVersionInfo(&versioninfo);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " DMA MCAL Version Info\r\n");
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " ---------------------\r\n");
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");

    /* Print ADC Config */
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " AdcConfigSet\r\n");
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " ------------\r\n");
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "  maxGroup     : %d\r\n", AdcConfigSet.maxGroup);
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "  maxHwUnit    : %d\r\n", AdcConfigSet.maxHwUnit);
    for (uint8_t grpIdx = 0; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        const Adc_GroupConfigType *grpCfg;

        grpCfg = &AdcConfigSet.groupCfg[grpIdx];
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "  Group %d                       \r\n", grpIdx);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   groupId                   : %d\r\n", grpCfg->groupId);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   groupPriority             : %d\r\n", grpCfg->groupPriority);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   hwUnitId                  : %d\r\n", grpCfg->hwUnitId);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   Adc_GroupEndNotification  : 0x%08x\r\n",
                  grpCfg->Adc_GroupEndNotification);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   streamNumSamples          : %d\r\n", grpCfg->streamNumSamples);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   resolution                : %d\r\n", grpCfg->resolution);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   convMode                  : %d\r\n", grpCfg->convMode);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   triggSrc                  : %d\r\n", grpCfg->triggSrc);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   accessMode                : %d\r\n", grpCfg->accessMode);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   streamBufMode             : %d\r\n", grpCfg->streamBufMode);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   hwTrigSignal              : %d\r\n", grpCfg->hwTrigSignal);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   hwTrigTimer               : %d\r\n", grpCfg->hwTrigTimer);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   groupReplacement          : %d\r\n", grpCfg->groupReplacement);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   groupChannelMask          : 0x%08x\r\n", grpCfg->groupChannelMask);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   groupDataAccessMode       : %d\r\n", grpCfg->groupDataAccessMode);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   numChannels               : %d\r\n", grpCfg->numChannels);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   groupDmaChannelId         : %d\r\n", grpCfg->groupDmaChannelId);
        for (uint8_t chIdx = 0; chIdx < grpCfg->numChannels; chIdx++)
        {
            GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "    channelConfig %d   \r\n", chIdx);
            GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "     hwChannelId   : %d\r\n",
                      grpCfg->channelConfig[chIdx].hwChannelId);
            GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "     samplewindow  : %d\r\n",
                      grpCfg->channelConfig[chIdx].samplewindow);
        }
    }
    for (uint8_t hwUnitIdx = 0; hwUnitIdx < ADC_MAX_HW_UNIT; hwUnitIdx++)
    {
        const Adc_HwUnitConfigType *hwUnitCfg;

        hwUnitCfg = &AdcConfigSet.hwUnitCfg[hwUnitIdx];
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "  HW Unit %d           \r\n", hwUnitIdx);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   hwUnitId    : %d\r\n", hwUnitCfg->hwUnitId);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   baseAddr    : 0x%08x\r\n", hwUnitCfg->baseAddr);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   prescale    : %d\r\n", hwUnitCfg->prescale);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "   resolution  : %d\r\n", hwUnitCfg->resolution);
    }
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " ------------\r\n");

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
    Cdd_Dma_DeInit();
    Adc_appPlatformDeInit();

    return;
}

static void Adc_appInterruptConfig(void)
{
    vimInit();

    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    /* Enable DMA interrupt */
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTAGGR;
    intCfg.handler  = CDD_EDMA_lld_transferCompletionMasterIsrFxn;
    intCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&intCfg);

    return;
}

static void Adc_appPrintResult(uint32 loopcnt)
{
    uint32_t                    dmaDataAddr;
    const Adc_GroupConfigType  *grpCfg;
    const Adc_HwUnitConfigType *hwUnitCfg;

    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " Read Buffer Content (Loop %d)\r\n", loopcnt);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " ----------------------------\r\n");
    for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        grpCfg    = &AdcConfigSet.groupCfg[grpIdx];
        hwUnitCfg = &AdcConfigSet.hwUnitCfg[grpCfg->hwUnitId];

        GT_3trace(ADC_APP_TRACE_MASK, GT_INFO, " ADC Group %d, HW Unit %d, Base 0x%08X:\r\n", grpIdx,
                  hwUnitCfg->hwUnitId, hwUnitCfg->baseAddr);
        GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " ----------------------------------------\r\n");
    }

    dmaDataAddr = Adc_GetReadResultBaseAddress(ADC_APP_GROUP_ID);
    for (uint16_t logIndex = 0U; logIndex < ADC_APP_LOG_SIZE; logIndex++)
    {
        Mcal_CacheP_inv((void *)gAdcAppDmaBuffer, sizeof(gAdcAppDmaBuffer), Mcal_CacheP_TYPE_ALL);

        gAdcAppLog[logIndex].dmaBuff  = gAdcAppDmaBuffer[0U][0U];
        gAdcAppLog[logIndex].hwResult = *((volatile uint16 *)(dmaDataAddr));
        gAdcAppLog[logIndex].status   = Adc_GetGroupStatus(0);

        AppUtils_delay(100); /* Capture log every 100ms */
    }

    for (uint16_t logIndex = 0U; logIndex < ADC_APP_LOG_SIZE; logIndex++)
    {
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " [Log %d] ", logIndex);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " dmaBuff: %d,", gAdcAppLog[logIndex].dmaBuff);
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " HWResult: %d,", gAdcAppLog[logIndex].hwResult);
        GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, "     ");
        Adc_appPrintStatus(0, gAdcAppLog[logIndex].status);
        GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");
    }
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");

    return;
}

static void Adc_appPrintStatus(uint32 grpIdx, Adc_StatusType status)
{
    GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " ADC Group %d Status: ", grpIdx);
    switch (status)
    {
        case ADC_IDLE:
            GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, "ADC_IDLE  !");
            break;
        case ADC_BUSY:
            GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, "ADC_BUSY !");
            break;
        case ADC_COMPLETED:
            GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, "ADC_COMPLETED !");
            break;
        case ADC_STREAM_COMPLETED:
            GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, "ADC_STREAM_COMPLETED !");
            break;
    }
}

static void Adc_appEpwmEnable(uint32 baseAddr)
{
    /* Time Base - EPWM Clock 200 MHz */
    EPWM_setClockPrescaler(baseAddr, EPWM_CLOCK_DIVIDER_8, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(baseAddr, 25000);

    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_TBPRD_TBPRDHR);
    EPWM_setPeriodLoadMode(baseAddr, EPWM_PERIOD_SHADOW_LOAD);
    EPWM_setTimeBaseCounter(baseAddr, 0);
    EPWM_setTimeBaseCounterMode(baseAddr, EPWM_COUNTER_MODE_STOP_FREEZE);
    EPWM_setCountModeAfterSync(baseAddr, EPWM_COUNT_MODE_DOWN_AFTER_SYNC);
    EPWM_disablePhaseShiftLoad(baseAddr);
    EPWM_setPhaseShift(baseAddr, 0);
    EPWM_enableSyncOutPulseSource(baseAddr, 0);
    EPWM_setSyncInPulseSource(baseAddr, EPWM_SYNC_IN_PULSE_SRC_DISABLE);
    EPWM_setOneShotSyncOutTrigger(baseAddr, EPWM_OSHT_SYNC_OUT_TRIG_SYNC);

    /* Counter Compare */
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_A, 12500);
    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPA_CMPAHR);

    EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_B, 0);
    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPB_CMPBHR);

    EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_C, 0);
    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPC);

    EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_D, 0);
    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPD);

    EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_D, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    /* Action Qualifier */
    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_AQCSFRC);
    EPWM_setActionQualifierContSWForceShadowMode(baseAddr, EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO);
    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_AQCTLA_AQCTLA2);
    EPWM_disableActionQualifierShadowLoadMode(baseAddr, EPWM_ACTION_QUALIFIER_A);
    EPWM_setActionQualifierShadowLoadMode(baseAddr, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);
    EPWM_setActionQualifierT1TriggerSource(baseAddr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierT2TriggerSource(baseAddr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierSWAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE);
    EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_SW_DISABLED);
    EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);
    EPWM_disableActionQualifierShadowLoadMode(baseAddr, EPWM_ACTION_QUALIFIER_B);
    EPWM_setActionQualifierShadowLoadMode(baseAddr, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);
    EPWM_setActionQualifierT1TriggerSource(baseAddr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierT2TriggerSource(baseAddr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierSWAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE);
    EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_DISABLED);

    /* Events */
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_T2_COUNT_UP);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_T2_COUNT_UP);
    EPWM_setActionQualifierAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN);

    /* Event Trigger */
    EPWM_disableInterrupt(baseAddr);
    EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ZERO, EPWM_INT_TBCTR_ZERO);
    EPWM_setInterruptEventCount(baseAddr, 0);
    EPWM_disableInterruptEventCountInit(baseAddr);
    EPWM_setInterruptEventCountInitValue(baseAddr, 0);

    EPWM_enableADCTrigger(baseAddr, EPWM_SOC_A);
    EPWM_setADCTriggerSource(baseAddr, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(baseAddr, EPWM_SOC_A, 1);
    EPWM_disableADCTriggerEventCountInit(baseAddr, EPWM_SOC_A);
    EPWM_setADCTriggerEventCountInitValue(baseAddr, EPWM_SOC_A, 0);

    EPWM_disableADCTrigger(baseAddr, EPWM_SOC_B);
    EPWM_setADCTriggerSource(baseAddr, EPWM_SOC_B, EPWM_SOC_DCxEVT1, EPWM_SOC_DCxEVT1);
    EPWM_setADCTriggerEventPrescale(baseAddr, EPWM_SOC_B, 0);
    EPWM_disableADCTriggerEventCountInit(baseAddr, EPWM_SOC_B);
    EPWM_setADCTriggerEventCountInitValue(baseAddr, EPWM_SOC_B, 0);

    /* Global Load */
    EPWM_disableGlobalLoad(baseAddr);
    EPWM_setGlobalLoadTrigger(baseAddr, EPWM_GL_LOAD_PULSE_CNTR_ZERO);
    EPWM_setGlobalLoadEventPrescale(baseAddr, 0);
    EPWM_disableGlobalLoadOneShotMode(baseAddr);

    /* EPWM Module */
    EPWM_lockRegisters(baseAddr, 0);

    return;
}

static void Adc_appDisableTrigger(uint32 baseAddr)
{
    EPWM_disableADCTrigger(baseAddr, EPWM_SOC_A);
    EPWM_disableADCTrigger(baseAddr, EPWM_SOC_B);
    EPWM_setTimeBaseCounterMode(baseAddr, EPWM_COUNTER_MODE_STOP_FREEZE);

    return;
}

static void Adc_appDmaTransferCallback(void *appData)
{
    /* DMA callback function for the application to handle */
    gAdcAppDmaCallbackCount++;

    return;
}

static void Adc_appDmaConfigure(const uint16 *destPtr, uint16 length, uint32 dmaCh, uint32 srcAddr)
{
    Cdd_Dma_ParamEntry edmaParam;

    edmaParam.srcPtr     = (void *)(srcAddr);
    edmaParam.destPtr    = (void *)(destPtr);
    edmaParam.aCnt       = (uint16)length;
    edmaParam.bCnt       = (uint16)1U;
    edmaParam.cCnt       = (uint16)1U;
    edmaParam.bCntReload = 0U;
    edmaParam.srcBIdx    = (sint16)0;
    edmaParam.destBIdx   = (sint16)0;
    edmaParam.srcCIdx    = (sint16)0;
    edmaParam.destCIdx   = (sint16)2;
    /* Note: Static mask will result in rearming the EDMA with the same set of param config for every transfer */
    edmaParam.opt =
        (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK | CDD_EDMA_OPT_STATIC_MASK);

    Cdd_Dma_ParamSet(dmaCh, 0, 0, edmaParam);
    Cdd_Dma_EnableTransferRegion(dmaCh, CDD_EDMA_TRIG_MODE_EVENT);

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

void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
