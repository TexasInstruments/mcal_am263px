/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \brief    This file contains the ADC test example
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
#include "Adc.h"
#include "Adc_Cfg.h"
#include "Adc_Irq.h"
#include "SchM_Adc.h"
#include "Mcu.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "Mcu_Cfg.h"
#include "app_utils.h"
#include "sys_common.h"

#include "sys_vim.h"
#include "AdcApp_Startup.h"
#include "AdcApp.h"
#include "trace.h"

/* For PRCM base addresses */
#include "soc.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define GROUP_TEMP_SENSORS (0)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void     AdcApp_mainTest(AdcApp_Obj *appObj, const AdcApp_TestParams *testPrms);
static void     AdcApp_procIsr(uint32 grpIdx);
static void     AdcApp_printResult(const AdcApp_TestParams *testPrms);
extern void     AdcApp_interruptConfig(void);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32          gTestPassed = E_OK;
volatile uint32 gAdcAppGroupDone[ADC_MAX_GROUP];

/**< Number of times App runs */
Adc_ValueGroupType Adc_AppBuffer[ADC_MAX_GROUP][ADC_APP_BUF_SIZE_WORD];

/**< SetUp Result Buffer passed to driver */
Adc_ValueGroupType Adc_AppReadBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];

/* Test application object */
AdcApp_Obj gAdcAppObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined CLANG

void SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
    return;
}

void SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0(void)
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
    AdcApp_Obj        *appObj = &gAdcAppObj;
    AdcApp_TestParams *testPrms;

    gTestPassed = E_OK;

    /* Setup Interrupt. */
    AdcApp_Startup();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\r\n");
    appObj->traceMask = (GT_INFO1 | GT_TraceState_Enable);
    testPrms          = &gAdcAppTestPrms[0];
    AdcApp_mainTest(appObj, testPrms);

    AppUtils_printf(APP_NAME ": Sample Application - DONE !!!\r\n");
    if (E_OK == gTestPassed)
    {
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
    }
    else
    {
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_FAIL);
    }
    AdcApp_TimerDeinit();
    return (0);
}

static void AdcApp_mainTest(AdcApp_Obj *appObj, const AdcApp_TestParams *testPrms)
{
    uint32         grpIdx;
    uint32         testPassed = E_OK;
    Adc_StatusType status;
    Std_ReturnType retVal;
    uint32         isPending;
    uint32         loopCount = 0U;

#if (ADC_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
#endif /* #if (ADC_VERSION_INFO_API == STD_ON) */

    memcpy(&appObj->testPrms, testPrms, sizeof(appObj->testPrms));

    /* Print test case information */
    GT_3trace(appObj->traceMask, GT_INFO, APP_NAME ": GROUPs %d: HWUNIT %d: LOOP COUNT %d:!!!\r\n",
              (appObj->testPrms.adcConfig)->maxGroup, (appObj->testPrms.adcConfig)->maxHwUnit,
              appObj->testPrms.loopCount);

    GT_0trace(appObj->traceMask, GT_INFO, " \r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "--------------------------------------\r\n");

    Adc_Print_applyvoltage(appObj);

    GT_0trace(appObj->traceMask, GT_INFO, "--------------------------------------\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, " \r\n");

/* Init */
#if (ADC_VARIANT_PRE_COMPILE == STD_ON)
    Adc_Init(NULL_PTR);
#endif

#if (ADC_VARIANT_POST_BUILD == STD_ON)
    Adc_Init(testPrms->adcConfig);
#endif

    AdcApp_interruptConfig();
    /* Do interrupt config after init to avoid interrupts at start-up when
     * reloading program in CCS */

#if (ADC_VERSION_INFO_API == STD_ON)
    /* Get and print version */
    Adc_GetVersionInfo(&versioninfo);
    GT_0trace(appObj->traceMask, GT_INFO, " \r\n");
    GT_0trace(appObj->traceMask, GT_INFO, " ADC MCAL Version Info\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, " ---------------------\r\n");
    GT_1trace(appObj->traceMask, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(appObj->traceMask, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(appObj->traceMask, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(appObj->traceMask, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(appObj->traceMask, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(appObj->traceMask, GT_INFO, " \r\n");
#endif /* #if (ADC_VERSION_INFO_API == STD_ON) */

    while (loopCount < appObj->testPrms.loopCount)
    {
        for (grpIdx = 0U; grpIdx < testPrms->adcConfig->maxGroup; grpIdx++)
        {
            memset(&Adc_AppReadBuffer[grpIdx][0], 0U, (sizeof(Adc_ValueGroupType) * ADC_NUM_CHANNEL));

            /* Check group status - it should be idle */
            status = Adc_GetGroupStatus(grpIdx);
            if (status != ADC_IDLE)
            {
                testPassed = E_NOT_OK;
                GT_1trace(appObj->traceMask, GT_ERR, " ADC Group %d is not IDLE!!\r\n", grpIdx);
            }

            /* Memset result buffer and give to driver */
            memset(&Adc_AppBuffer[grpIdx][0], 0U, (sizeof(Adc_ValueGroupType) * ADC_NUM_CHANNEL));

            retVal = Adc_SetupResultBuffer(grpIdx, &Adc_AppBuffer[grpIdx][0]);
            if (retVal != E_OK)
            {
                testPassed = E_NOT_OK;
                GT_1trace(appObj->traceMask, GT_ERR, " ADC Group %d setup buffer failed!!\r\n", grpIdx);
            }

            gAdcAppGroupDone[grpIdx] = FALSE;

#if (ADC_GRP_NOTIF_CAPABILITY_API == STD_ON)
            /* Enable notification */
            Adc_EnableGroupNotification(grpIdx);
#endif /* #if (ADC_GRP_NOTIF_CAPABILITY_API == STD_ON) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
            /* Start conversion */
            Adc_StartGroupConversion(grpIdx);
#endif /* #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (ADC_POLLING_MAINFUNCTION_API == STD_ON)
            if (Adc_Config.groupCfg[grpIdx].groupDataAccessMode == ADC_GROUP_POLLING_ACCESS)
            {
                status = Adc_GetGroupStatus(grpIdx);

                while (status == ADC_BUSY)
                {
#if (STD_ON == ADC_POLLING_MAINFUNCTION_API)
                    Adc_PollingMainFunction();
#endif
                    status = Adc_GetGroupStatus(grpIdx);
                }

                if ((status == ADC_STREAM_COMPLETED) || (status == ADC_COMPLETED))
                {
#if (ADC_READ_GROUP_API == STD_ON)
                    /* Read and store the result */
                    retVal = Adc_ReadGroup(grpIdx, &Adc_AppReadBuffer[grpIdx][0]);
                    if (retVal != E_OK)
                    {
                        gTestPassed = E_NOT_OK;
                        GT_1trace(appObj->traceMask, GT_ERR, "ADC Group %d read buffer failed!!\r\n", grpIdx);
                    }
#endif /* #if (ADC_READ_GROUP_API == STD_ON) */
                    gAdcAppGroupDone[grpIdx] = TRUE;
                }
                else
                {
                    gTestPassed = E_NOT_OK;
                    GT_1trace(appObj->traceMask, GT_ERR, "ADC Group %d is not in read state!!\r\n", grpIdx);
                }
            }
#endif
        }

        /* Wait for all group conversion to get over */
        while (1)
        {
            isPending = FALSE;
            for (grpIdx = 0U; grpIdx < testPrms->adcConfig->maxGroup; grpIdx++)
            {
#if (ADC_POLLING_MAINFUNCTION_API == STD_ON)
                if (Adc_Config.groupCfg[grpIdx].groupDataAccessMode != ADC_GROUP_POLLING_ACCESS)
#endif
                {
                    if (gAdcAppGroupDone[grpIdx] == FALSE)
                    {
                        isPending = TRUE;
                        break;
                    }
                }
            }
            if (FALSE == isPending)
            {
                break;
            }
        }

        for (grpIdx = 0U; grpIdx < testPrms->adcConfig->maxGroup; grpIdx++)
        {
            /* Note: Stop not required as read group API we are calling from
             * ISR callback will move state to idle automatically */
#if (ADC_GRP_NOTIF_CAPABILITY_API == STD_ON)
            Adc_DisableGroupNotification(grpIdx);
#endif /* #if (ADC_GRP_NOTIF_CAPABILITY_API == STD_ON) */

            /* Check group status - it should be idle */
            status = Adc_GetGroupStatus(grpIdx);
            if (status != ADC_IDLE)
            {
                testPassed = E_NOT_OK;
                GT_1trace(appObj->traceMask, GT_ERR, " ADC Group %d is not IDLE!!\r\n", grpIdx);
            }
        }

        AdcApp_printResult(testPrms);
        AppUtils_delay(100);
        loopCount++;
    }
#if (ADC_READ_TEMPERATURE_API == STD_ON)
    AdcTempTest(appObj, GROUP_TEMP_SENSORS);
#endif

#if (ADC_DEINIT_API == STD_ON)
    /* DeInit */
    Adc_DeInit();
#endif /* #if (ADC_DEINIT_API == STD_ON) */

    if (E_OK == gTestPassed)
    {
        gTestPassed = testPassed;
    }

    if (E_OK == testPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, "All tests have passed\n");
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, "Some tests have failed\n");
    }

    return;
}

void AdcApp_Group0EndNotification(void)
{
    AdcApp_procIsr(0U);
}

void AdcApp_Group1EndNotification(void)
{
    AdcApp_procIsr(1U);
}

void AdcApp_Group2EndNotification(void)
{
    AdcApp_procIsr(2U);
}

void AdcApp_Group3EndNotification(void)
{
    AdcApp_procIsr(3U);
}

static void AdcApp_procIsr(uint32 grpIdx)
{
    Adc_StatusType status;
    AdcApp_Obj    *appObj;
#if (ADC_READ_GROUP_API == STD_ON)
    Std_ReturnType retVal;
#endif /* #if (ADC_READ_GROUP_API == STD_ON) */

    appObj = &gAdcAppObj;
    /* Check group status - it should be COMPLETED state */
    status = Adc_GetGroupStatus(grpIdx);
    if (status == ADC_STREAM_COMPLETED)
    {
#if (ADC_READ_GROUP_API == STD_ON)
        /* Read and store the result */
        retVal = Adc_ReadGroup(grpIdx, &Adc_AppReadBuffer[grpIdx][0]);
        if (retVal != E_OK)
        {
            gTestPassed = E_NOT_OK;
            GT_1trace(appObj->traceMask, GT_ERR, "ADC Group %d read buffer failed!!\r\n", grpIdx);
        }
#endif /* #if (ADC_READ_GROUP_API == STD_ON) */
    }
    else
    {
        gTestPassed = E_NOT_OK;
        GT_1trace(appObj->traceMask, GT_ERR, "ADC Group %d is not in read state!!\r\n", grpIdx);
    }

    gAdcAppGroupDone[grpIdx] = TRUE;

    return;
}

static void AdcApp_printResult(const AdcApp_TestParams *testPrms)
{
    uint32                     grpIdx;
    const Adc_GroupConfigType *grpCfg;
    AdcApp_Obj                *appObj;

    appObj = &gAdcAppObj;

    GT_0trace(appObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " Read Buffer Content\r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " -------------------\r\n");
    for (grpIdx = 0U; grpIdx < testPrms->adcConfig->maxGroup; grpIdx++)
    {
        grpCfg = &testPrms->adcConfig->groupCfg[grpIdx];

        GT_1trace(appObj->traceMask, GT_INFO1, " ADC Group %d Log:\r\n", grpIdx);
        GT_0trace(appObj->traceMask, GT_INFO1, " ----------------\r\n");

        AdcApp_printChannelResult(grpIdx, grpCfg, appObj);
    }
    return;
}
