/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     MibspiApp.c
 *
 *  \brief    This file contains the SPI test example for MibSPI
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/

#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"

#include "MibspiApp.h"
#include "MibspiApp_Startup.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0U]))

/* UART read timeout in msec */
#define SPI_APP_UART_TIMEOUT_MSEC (10000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static uint32 SpiApp_mibspiLoopbackTest(const Spi_ConfigType *spiConfig);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32 gTestPassed = E_OK;

uint32          gMibspiTxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD];
uint32          gMibspiRxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD];
volatile uint32 gMibspiJobDone[SPI_MAX_JOBS], gMibspiSeqDone[SPI_MAX_SEQ];

#define SPI_APP_NUM_CLK_LIST (sizeof(gClkDividerTestList) / sizeof(gClkDividerTestList[0U]))
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    gTestPassed                  = E_OK;
    const Spi_ConfigType *cfgPtr = &SpiDriver_0;

    MibspiApp_Startup();

    gTestPassed = SpiApp_mibspiLoopbackTest(cfgPtr);

    if (E_OK == gTestPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, "All tests have passed\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, " MibSPI Test Failed!!!\n\r");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_FAIL);
    }
    while (1)
        ;

    return (0U);
}

static uint32 SpiApp_mibspiLoopbackTest(const Spi_ConfigType *spiConfig)
{
    uint32              index, chIndex;
    uint32              testPassed = E_OK, matching;
    uint8              *tempTxPtr, *tempRxPtr;
    uint32              byteLength[SPI_MAX_CHANNELS];
    uint32              xferLength[SPI_MAX_CHANNELS];
    Std_ReturnType      retVal;
    Spi_StatusType      status;
    Spi_SeqResultType   seqResult;
    Spi_JobResultType   jobResult;
    Spi_ChannelType     chId;
    Spi_SequenceType    seqId;
    Spi_JobType         jobId;
    Spi_DataBufferType *srcDataBuf, *destDataBuf;
#if (SPI_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
#endif /* #if (SPI_VERSION_INFO_API == STD_ON) */
#if ((SPI_SCALEABILITY == SPI_CFG_LEVEL_1) || (SPI_SCALEABILITY == SPI_CFG_LEVEL_2))
    uint32 isPending;
#endif

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\n\r");

#if (STD_ON == SPI_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n\r");
    Spi_Init((const Spi_ConfigType *)NULL_PTR);
#elif (STD_ON == SPI_VARIANT_POST_BUILD)
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
    Spi_Init(spiConfig);
#elif (STD_ON == SPI_LINK_TIME_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Link Time being used !!!\n\r");
    Spi_Init(spiConfig);
#endif

    /* Print test case information */
    AppUtils_printf(APP_NAME ": CH %d: JOBS %d: SEQ %d: HWUNIT %d: !!!\n\r", spiConfig->maxChannels, spiConfig->maxJobs,
                    spiConfig->maxSeq, spiConfig->maxHwUnit);
    SpiApp_interruptConfig();

#if (STD_ON == SPI_SET_LOOPBACK_MODE_API)
    for (index = 0U; index < spiConfig->maxHwUnit; index++)
    {
        Std_ReturnType retVal;
        boolean        lpbkEnable;

        GT_assert(McalAppTrace, (index < SPI_MAX_HW_UNIT));

        /* Skip for QSPI unit */
        if (spiConfig->hwUnitCfg[index].hwUnitId != SPI_UNIT_QSPI1)
        {
            lpbkEnable = TRUE;
            if (spiConfig->extDevCfg[0U].mibspi.txRxMode == SPI_TX_RX_MODE_TX_ONLY)
            {
                /* Disable loopback for TX only mode */
                lpbkEnable = FALSE;
            }
            retVal = Spi_SetLoopbackMode(spiConfig->hwUnitCfg[index].hwUnitId, lpbkEnable);
            if (retVal != E_OK)
            {
                testPassed = E_NOT_OK;
                GT_0trace(McalAppTrace, GT_ERR, "SPI Set Loopback Mode Failed!!\n\r");
            }
        }
    }
#endif /* #if (STD_ON == SPI_SET_LOOPBACK_MODE_API) */

#if (SPI_VERSION_INFO_API == STD_ON)
    /* Get and print version */
    Spi_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n\r");
    AppUtils_printf("SPI MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf("Vendor ID           : %d\n\r", versioninfo.vendorID);
    AppUtils_printf("Module ID           : %d\n\r", versioninfo.moduleID);
    AppUtils_printf("SW Major Version    : %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf("SW Minor Version    : %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf("SW Patch Version    : %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n\r");
#endif /* #if (SPI_VERSION_INFO_API == STD_ON) */

    /* SPI driver should be free now - check */
    status = Spi_GetStatus();
    if (status != SPI_IDLE)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf("SPI driver is not IDLE!!\n\r");
    }

#if (SPI_HW_STATUS_API == STD_ON)
    /* SPI HW unit should be free now - check */
    for (index = 0U; index < spiConfig->maxHwUnit; index++)
    {
        status = Spi_GetHWUnitStatus(spiConfig->hwUnitCfg[index].hwUnitId);
        if (status != SPI_IDLE)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf("SPI HW %d is not IDLE!!\n\r", spiConfig->hwUnitCfg[index].hwUnitId);
        }
    }
#endif /* #if (SPI_HW_STATUS_API == STD_ON) */

#if (SPI_SCALEABILITY == SPI_CFG_LEVEL_2)
    /* Set Async mode */
    retVal = Spi_SetAsyncMode(SPI_APP_DEFAULT_ASYNC_MODE);

    if (retVal != E_OK)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf("SPI Set Async Mode Failed!!\n\r");
    }
#endif /* #if (SPI_SCALEABILITY == SPI_CFG_LEVEL_2) */

    /* Init test params */
    for (chIndex = 0U; chIndex < SPI_MAX_CHANNELS; chIndex++)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr = (uint8 *)&gMibspiTxBuffer[chIndex][0U];
        tempRxPtr = (uint8 *)&gMibspiRxBuffer[chIndex][0U];
        uint8 i;
        if (chIndex == 0)
        {
            i = 0xaU;
        }
        else
        {
            i = 0x0U;
        }

        for (index = 0U; index < (RX_TX_BUF_SIZE_WORD * 4U); index++)
        {
            *tempTxPtr++ = (uint8)(index + i);
            *tempRxPtr++ = 0U;
        }

        if (spiConfig->channelCfg[chIndex].dataWidth == (uint8)SPI_APP_RX_TX_LENGTH_RAMP_UP)
        {
            xferLength[chIndex] = 1U;
        }
        else if (spiConfig->channelCfg[chIndex].dataWidth == (uint8)SPI_APP_RX_TX_LENGTH_RAMP_DOWN)
        {
            xferLength[chIndex] = SPI_APP_RAMP_LOOP_COUNT;
        }
        else
        {
            xferLength[chIndex] = spiConfig->channelCfg[chIndex].dataWidth;
        }
    }

    for (chIndex = 0U; chIndex < spiConfig->maxChannels; chIndex++)
    {
        /* Memset RX buffer for every run */
        if (spiConfig->channelCfg[chIndex].dataWidth <= 8U)
        {
            byteLength[chIndex] = xferLength[chIndex];
        }
        else if (spiConfig->channelCfg[chIndex].dataWidth <= 16U)
        {
            byteLength[chIndex] = xferLength[chIndex] * 2U;
        }
        else
        {
            byteLength[chIndex] = xferLength[chIndex] * 4U;
        }
        tempRxPtr = (uint8 *)&gMibspiRxBuffer[chIndex][0U];
        for (index = 0U; index < xferLength[chIndex]; index++)
        {
            *tempRxPtr++ = 0U;
        }

        /* Setup EB for TX/RX */
        srcDataBuf  = (Spi_DataBufferType *)&gMibspiTxBuffer[chIndex][0U];
        destDataBuf = (Spi_DataBufferType *)&gMibspiRxBuffer[chIndex][0U];
        chId        = spiConfig->channelCfg[chIndex].channelId;
        retVal      = Spi_SetupEB(chId, srcDataBuf, destDataBuf, xferLength[chIndex]);
        if (retVal != E_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf("SPI Setup EB Failed!! %d\n\r", byteLength[chIndex]);
        }
    }

    /* Reset flags */
    for (index = 0U; index < SPI_MAX_JOBS; index++)
    {
        gMibspiJobDone[index] = FALSE;
    }
    for (index = 0U; index < SPI_MAX_SEQ; index++)
    {
        gMibspiSeqDone[index] = FALSE;
    }

#if ((SPI_SCALEABILITY == SPI_CFG_LEVEL_1) || (SPI_SCALEABILITY == SPI_CFG_LEVEL_2))

    for (index = 0U; index < spiConfig->maxSeq; index++)
    {
        /* Start the TX/RX */
        seqId  = spiConfig->seqCfg[index].seqId;
        retVal = Spi_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf("SPI Async transmit Failed!!\n\r");
        }
    }

    if (SPI_INTERRUPT_MODE == SPI_APP_DEFAULT_ASYNC_MODE)
    {
        /* Wait for TX/RX to get over */
        while (1U)
        {
            isPending = FALSE;
            for (index = 0U; index < spiConfig->maxSeq; index++)
            {
                if (gMibspiSeqDone[index] == FALSE)
                {
                    isPending = TRUE;
                    break;
                }
            }
            for (index = 0U; index < spiConfig->maxJobs; index++)
            {
                if (gMibspiJobDone[index] == FALSE)
                {
                    isPending = TRUE;
                    break;
                }
            }
            if (FALSE == isPending)
            {
                break;
            }
        }
    }
    else
    {
        while (1U)
        {
            Spi_MainFunction_Handling();

            isPending = FALSE;
            for (index = 0U; index < spiConfig->maxSeq; index++)
            {
                seqResult = Spi_GetSequenceResult(index);
                if (seqResult != SPI_SEQ_OK)
                {
                    isPending = TRUE;
                    break;
                }
            }
            for (index = 0U; index < spiConfig->maxJobs; index++)
            {
                jobResult = Spi_GetJobResult(index);
                if (jobResult != SPI_JOB_OK)
                {
                    isPending = TRUE;
                    break;
                }
            }

            /* All jobs/sequences completed */
            if (FALSE == isPending)
            {
                break;
            }
        }
    }

#endif

#if ((SPI_SCALEABILITY == SPI_CFG_LEVEL_0) || (SPI_SCALEABILITY == SPI_CFG_LEVEL_2))
    if (FALSE == SPI_APP_DEFAULT_ASYNC_MODE)
    {
        for (index = 0U; index < spiConfig->maxSeq; index++)
        {
            /* Start the TX/RX */
            seqId  = spiConfig->seqCfg[index].seqId;
            retVal = Spi_SyncTransmit(seqId);
            if (retVal != E_OK)
            {
                testPassed = E_NOT_OK;
                AppUtils_printf("SPI Sync transmit Failed!!\n\r");
            }
        }
    }
#endif

    /* SPI driver should be free now - check */
    status = Spi_GetStatus();
    if (status != SPI_IDLE)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf("SPI driver is not IDLE!!\n\r");
    }
    for (index = 0U; index < spiConfig->maxSeq; index++)
    {
        seqId     = spiConfig->seqCfg[index].seqId;
        seqResult = Spi_GetSequenceResult(seqId);
        if (seqResult != SPI_SEQ_OK)
        {
            if (seqResult == SPI_SEQ_CANCELLED)
            {
                AppUtils_printf("SPI Sequence was cancelled!!\n\r");
            }
            else
            {
                testPassed = E_NOT_OK;
                AppUtils_printf("SPI Sequence is not OK!!\n\r");
            }
        }
    }
    for (index = 0U; index < spiConfig->maxJobs; index++)
    {
        jobId     = spiConfig->jobCfg[index].jobId;
        jobResult = Spi_GetJobResult(jobId);
        if (jobResult != SPI_JOB_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf("SPI Job is not OK %d!!\n\r", jobId);
        }
    }

    /* Check RX buffer against TX buffer */

    matching = TRUE;
    for (chIndex = 0U; chIndex < spiConfig->maxChannels; chIndex++)
    {
        tempTxPtr = (uint8 *)&gMibspiTxBuffer[chIndex][0U];
        tempRxPtr = (uint8 *)&gMibspiRxBuffer[chIndex][0U];
        for (index = 0U; index < byteLength[chIndex] / 2; index++)
        {
            if (*tempTxPtr++ != *tempRxPtr++)
            {
                matching = FALSE;
            }
        }
    }
    if (TRUE != matching)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf("MibSPI data mismatch error!!\n\r");
    }

    for (chIndex = 0U; chIndex < spiConfig->maxChannels; chIndex++)
    {
        if (spiConfig->channelCfg[chIndex].dataWidth == (uint8)SPI_APP_RX_TX_LENGTH_RAMP_UP)
        {
            xferLength[chIndex]++;
            if (xferLength[chIndex] == SPI_APP_RAMP_LOOP_COUNT)
            {
                xferLength[chIndex] = 1U;
            }
        }
        else if (spiConfig->channelCfg[chIndex].dataWidth == (uint8)SPI_APP_RX_TX_LENGTH_RAMP_DOWN)
        {
            if (xferLength[chIndex] == 1U)
            {
                xferLength[chIndex] = SPI_APP_RAMP_LOOP_COUNT;
            }
            else
            {
                xferLength[chIndex]--;
            }
        }
        else
        {
            xferLength[chIndex] = spiConfig->channelCfg[chIndex].dataWidth;
        }
    }

#if (SPI_JOB_LOG == STD_ON)
    SpiApp_printJobLog(testPrms);
#endif /* #if (SPI_JOB_LOG == STD_ON) */

    /* DeInit */
    retVal = Spi_DeInit();
    if (retVal != E_OK)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf("SPI Deinit Failed!!\n\r");
    }

    /* SPI driver should be uninit now - check */
    status = Spi_GetStatus();
    if (status != SPI_UNINIT)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf("SPI driver is not in uninit state!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        gTestPassed = testPassed;
    }
    if (E_OK == gTestPassed)
    {
        AppUtils_printf("SPI Test Passed!!!\n\r");
    }
    else
    {
        AppUtils_printf("SPI Test Failed!!!\n\r");
    }

    return (gTestPassed);
}

#if (APP_LOOPBACK_MODE == STD_ON)
void SpiApp_MibspiJob0EndNotification(void)
{
    gMibspiJobDone[0U] = TRUE;

    return;
}

void SpiApp_MibspiJob1EndNotification(void)
{
    gMibspiJobDone[1U] = TRUE;

    return;
}

void SpiApp_MibspiJob2EndNotification(void)
{
    gMibspiJobDone[2U] = TRUE;

    return;
}

void SpiApp_MibspiSeq1EndNotification(void)
{
    gMibspiSeqDone[1U] = TRUE;

    return;
}

void SpiApp_MibspiSeq0EndNotification(void)
{
    gMibspiSeqDone[0U] = TRUE;

    return;
}
#endif

uint8 Intc_status;

#ifdef __cplusplus
extern "C" {
#endif

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

#ifdef __cplusplus
}
#endif

void SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0(void)
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

void App_disable(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void App_restore(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
