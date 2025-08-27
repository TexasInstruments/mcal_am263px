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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Number of channels to test
 * In this example application, there are 2 groups configured.
 * ADC Group 0 have 2 channels and Group 1 have 1 channel.
 * Here the maximum number of channels from the group is used
 */
#define ADC_APP_MAX_CHANNELS_PER_GROUP (2U)

/** \brief Default stream samples per channel to test - match this to streamNumSamples config parameter */
#define ADC_APP_DEFAULT_STREAM_SAMPLES (1U)
/** \brief Each group read buffer size in samples */
#define ADC_APP_READ_BUF_SIZE_WORD (ADC_APP_DEFAULT_STREAM_SAMPLES * ADC_APP_MAX_CHANNELS_PER_GROUP)

/** \brief Each group buffer allocation to match cache line aligned - assumes this is greater than
 *  ADC_APP_READ_BUF_SIZE_WORD */
#define ADC_APP_READ_BUF_SIZE_ALIGNED      (Mcal_CacheP_CACHELINE_ALIGNMENT)
#define ADC_APP_READ_BUF_SIZE_WORD_ALIGNED (ADC_APP_READ_BUF_SIZE_ALIGNED / sizeof(Adc_ValueGroupType))

/* Number of iteration to run test */
#define ADC_APP_LOOPCNT (3U)

/* DMA channel used for testing of ADC groups
 * This example uses 2 ADC groups and thus 2 DMA channels used
 * Group 0 - DMA Channel 0, Group 1 - DMA Channel 1
 */
#define ADC_APP_GROUP0_DMA_CH (0U)
#define ADC_APP_GROUP1_DMA_CH (1U)

/* EPWM Channel used for testing*/
#define ADC_APP_EPWM_CHANNEL (0U)

/* EPWM Period
 * PWM Clock 200MHz. PWM period is TBPRD = 25000U. Corresponds to 1 millisecond
 */
#define ADC_APP_EPWM_PERIOD (25000U)

/* Log size */
#define ADC_APP_LOG_SIZE (5U)

/* Trace mask */
#define ADC_APP_TRACE_MASK (GT_INFO1 | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct
{
    Adc_ValueGroupType dmaBuff[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];  /* Log buffer used for DMA*/
    Adc_ValueGroupType hwResult[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD]; /* Log ADC HW result*/
    Adc_StatusType     status;                                              /* Log ADC group status*/
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
static void Adc_appDmaTransferCallback(void *appData);
static void Adc_appDmaConfigure(const uint16 *destPtr, uint16 length, uint32 dmaCh, uint32 *srcAddr, sint16 srcBIdx,
                                sint16 destBIdx);
static void Adc_appEpwmConfigureTrigger(uint16 period, uint16 channel);
static void Adc_appEpwmDisableTrigger(uint16 channel);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test pass flag */
static uint32 gTestPassed = E_OK;

/* Result buffer used by DMA */
static Adc_ValueGroupType gAdcAppDmaBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD_ALIGNED]
    __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));

/* DMA channel allocated to each ADC group
 *  In this example, DMA channel 0 is allocated for Group 0 and DMA channel 1 is allocated to Group 1
 */
static uint32 gAdcAppDmaChannel[ADC_MAX_GROUP] = {ADC_APP_GROUP0_DMA_CH, ADC_APP_GROUP1_DMA_CH};

/* DMA callback counter */
static volatile uint32 gAdcAppDmaCallbackCount[ADC_MAX_GROUP];

/* CDD PWM ADC SOC */
static Cdd_Pwm_AdcSocType gAdcAppPwmAdcSocConfig;

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
    uint32         dmaDataAddr[ADC_MAX_GROUP];

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

        /* Reset buffers and perform a cache write back */
        memset(&gAdcAppDmaBuffer[grpIdx][0U], 0U, (sizeof(Adc_ValueGroupType) * ADC_APP_READ_BUF_SIZE_WORD));
        Mcal_CacheP_wb((void *)&gAdcAppDmaBuffer[grpIdx][0U], ADC_APP_READ_BUF_SIZE_ALIGNED, Mcal_CacheP_TYPE_ALL);
        retVal = Adc_SetupResultBuffer(grpIdx, &gAdcAppDmaBuffer[grpIdx][0U]);
        if (retVal != E_OK)
        {
            testPassed = E_NOT_OK;
            GT_1trace(ADC_APP_TRACE_MASK, GT_ERR, " ADC Group %d setup buffer failed!!\r\n", grpIdx);
        }
    }

    for (uint32 loopcnt = 0U; loopcnt < ADC_APP_LOOPCNT; loopcnt++)
    {
        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            /* Enable hardware trigger */
            Adc_EnableHardwareTrigger(grpIdx);
            /* Enable continue to interrupt mode */
            Adc_SetInterruptContinuousMode(grpIdx);

            /* Configure DMA channel */
            dmaDataAddr[grpIdx] = Adc_GetReadResultBaseAddress(grpIdx);
        }

        /* DMA configuration for ADC group 0 */
        /* For Group 0, 2 channels used in this example. So, srcBIdx and destBIdx shall be set to 2 to read after every
         * 2 bytes of result to move to the next consecutive result register. Also DMA update the destination buffer at
         * gAdcAppDmaBuffer[0][0] */
        Adc_appDmaConfigure(&gAdcAppDmaBuffer[0U][0U], AdcConfigSet.groupCfg[0].numChannels * 2U, gAdcAppDmaChannel[0],
                            &dmaDataAddr[0], 2, 2);

        /* DMA configuration for ADC group 1 */
        /* For Group 1, Only 1 channel used. So, srcBIdx and destBIdx shall be set to 1
         * Also DMA update the destination buffer at gAdcAppDmaBuffer[1][0]*/
        Adc_appDmaConfigure(&gAdcAppDmaBuffer[1U][0U], AdcConfigSet.groupCfg[1].numChannels * 2U, gAdcAppDmaChannel[1],
                            &dmaDataAddr[1], 1, 1);

        /* EPWM Configuration to start the time base counter and trigger ADC SOC*/
        Adc_appEpwmConfigureTrigger(ADC_APP_EPWM_PERIOD, ADC_APP_EPWM_CHANNEL);

        Adc_appPrintResult(loopcnt);

        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            Adc_DisableHardwareTrigger(grpIdx);
        }
        Adc_appEpwmDisableTrigger(ADC_APP_EPWM_CHANNEL);
    }

    if (testPassed != E_OK)
    {
        gTestPassed = E_NOT_OK;
    }

    return;
}

static void Adc_appInit(void)
{
    Std_VersionInfoType versioninfo;

    Adc_appPlatformInit();
    Cdd_Pwm_Init(&CddPwmConfigSet_0);
    Cdd_Dma_Init(NULL_PTR);
    Adc_Init(&AdcConfigSet);
    Adc_appInterruptConfig();
    for (uint8_t grpIdx = 0; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        Cdd_Dma_CbkRegister(gAdcAppDmaChannel[grpIdx], (void *)&AdcConfigSet.groupCfg[grpIdx].groupId,
                            &Adc_appDmaTransferCallback);
    }

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

    /* CDD PWM - Get and print version */
    Cdd_Pwm_GetVersionInfo(&versioninfo);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " CDD PWM MCAL Version Info\r\n");
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
    Cdd_Pwm_DeInit();
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
    for (uint16_t logIndex = 0U; logIndex < ADC_APP_LOG_SIZE; logIndex++)
    {
        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            grpCfg = &AdcConfigSet.groupCfg[grpIdx];

            /* Store the buffer data*/
            dmaDataAddr = Adc_GetReadResultBaseAddress(grpIdx);

            Mcal_CacheP_inv((void *)&gAdcAppDmaBuffer[grpIdx][0U], ADC_APP_READ_BUF_SIZE_ALIGNED, Mcal_CacheP_TYPE_ALL);

            for (uint8 chIdx = 0U; chIdx < grpCfg->numChannels; chIdx++)
            {
                gAdcAppLog[logIndex].dmaBuff[grpIdx][chIdx]  = gAdcAppDmaBuffer[grpIdx][chIdx];
                gAdcAppLog[logIndex].hwResult[grpIdx][chIdx] = *((volatile uint16 *)(dmaDataAddr));
                dmaDataAddr                                  = dmaDataAddr + 2; /* Move to next result address*/
                gAdcAppLog[logIndex].status                  = Adc_GetGroupStatus(grpIdx);
            }
        }
        AppUtils_delay(100); /* Capture log every 100ms */
    }

    hwUnitCfg = &AdcConfigSet.hwUnitCfg[grpCfg->hwUnitId];

    GT_2trace(ADC_APP_TRACE_MASK, GT_INFO, " HW Unit %d, Base 0x%08X:\r\n", hwUnitCfg->hwUnitId, hwUnitCfg->baseAddr);
    GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " -------------------------\r\n");

    /* Print the hardware result and dma buffer */
    for (uint16_t logIndex = 0U; logIndex < ADC_APP_LOG_SIZE; logIndex++)
    {
        GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, " [Log %d]\r\n", logIndex);
        GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n");

        for (uint32 grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
        {
            grpCfg = &AdcConfigSet.groupCfg[grpIdx];
            GT_1trace(ADC_APP_TRACE_MASK, GT_INFO, "  ADC Group %d\r\n", grpIdx);

            for (uint8 chIdx = 0; chIdx < grpCfg->numChannels; chIdx++)
            {
                GT_3trace(ADC_APP_TRACE_MASK, GT_INFO, " dmaBuff[%d][%d]: %d\t", grpIdx, chIdx,
                          gAdcAppLog[logIndex].dmaBuff[grpIdx][chIdx]);
                GT_3trace(ADC_APP_TRACE_MASK, GT_INFO, " HWResult[%d][%d]: %d\r\n", grpIdx, chIdx,
                          gAdcAppLog[logIndex].hwResult[grpIdx][chIdx]);
            }
            Adc_appPrintStatus(grpIdx, gAdcAppLog[logIndex].status);
            GT_0trace(ADC_APP_TRACE_MASK, GT_INFO, " \r\n\r\n");
        }
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

static void Adc_appDmaTransferCallback(void *appData)
{
    /* DMA callback function for the application to handle .
     * Here only 2 groups used in this example. So, check whether the appData is ADC_GROUP_ID_0 else ADC_GROUP_ID_1
     * and increment the corresponding array index value */

    uint8 groupId = *(uint8 *)appData;
    if (groupId == ADC_GROUP_ID_0)
    {
        gAdcAppDmaCallbackCount[groupId]++;
    }
    else
    {
        gAdcAppDmaCallbackCount[groupId]++;
    }

    return;
}

static void Adc_appDmaConfigure(const uint16 *destPtr, uint16 length, uint32 dmaCh, uint32 *srcAddr, sint16 srcBIdx,
                                sint16 destBIdx)
{
    Cdd_Dma_ParamEntry edmaParam;

    edmaParam.srcPtr     = (void *)(srcAddr[0]);
    edmaParam.destPtr    = (void *)(destPtr);
    edmaParam.aCnt       = (uint16)length;
    edmaParam.bCnt       = (uint16)1U;
    edmaParam.cCnt       = (uint16)1U;
    edmaParam.bCntReload = 0U;
    edmaParam.srcBIdx    = (sint16)srcBIdx;
    edmaParam.destBIdx   = (sint16)destBIdx;
    edmaParam.srcCIdx    = (sint16)0;
    edmaParam.destCIdx   = (sint16)2;
    /* Note: Static mask will result in rearming the EDMA with the same set of param config for every transfer */
    edmaParam.opt =
        (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK | CDD_EDMA_OPT_STATIC_MASK);

    Cdd_Dma_ParamSet(dmaCh, 0, 0, edmaParam);
    Cdd_Dma_EnableTransferRegion(dmaCh, CDD_EDMA_TRIG_MODE_EVENT);

    return;
}

static void Adc_appEpwmConfigureTrigger(uint16 period, uint16 channel)
{
    Cdd_Pwm_channelParametertype Cdd_Pwm_Param;

    Cdd_Pwm_Param.ChannelNumber = channel;
    Cdd_Pwm_Param.Period        = period;
    Cdd_Pwm_Param.DutyCycle     = CDD_PWM_DUTYCYCLE_MAX - 1U;
    Cdd_Pwm_Param.Phase         = 0U;
    Cdd_Pwm_Param.Output        = CDD_PWM_OUTPUT_CH_A;
    Cdd_Pwm_SetPeriodDutyPhase(Cdd_Pwm_Param);

    /* Enable and set ADC trigger source */
    gAdcAppPwmAdcSocConfig.channelEnable           = TRUE;
    gAdcAppPwmAdcSocConfig.adcSocSource            = CDD_PWM_SOC_A;
    gAdcAppPwmAdcSocConfig.adcInterruptSource      = CDD_PWM_SOC_TBCTR_ZERO;
    gAdcAppPwmAdcSocConfig.adcMixedInterruptSource = CDD_PWM_SOC_TBCTR_ZERO;
    Cdd_Pwm_SetAdcTrigger(channel, gAdcAppPwmAdcSocConfig);

    /* Start the counter */
    Cdd_Pwm_SetTimeBaseCounterMode(channel, CDD_PWM_COUNTER_MODE_UP);
}

static void Adc_appEpwmDisableTrigger(uint16 channel)
{
    /* Disable PWM adc trigger*/
    gAdcAppPwmAdcSocConfig.channelEnable = FALSE;
    Cdd_Pwm_SetAdcTrigger(channel, gAdcAppPwmAdcSocConfig);

    /* Stop the EPWM time base counter */
    Cdd_Pwm_SetTimeBaseCounterMode(channel, CDD_PWM_COUNTER_MODE_STOP_FREEZE);
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

void SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
