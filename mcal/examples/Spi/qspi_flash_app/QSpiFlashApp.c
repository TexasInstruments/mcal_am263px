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
 *  \file     QSpiFlashApp.c
 *
 *  \brief    This file contains the SPI test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
#include "Os.h"

#include "QSpiFlashApp.h"
#include "appUtils_QSpiFlashLib.h"
#include "Cdd_Dma_Cfg.h"
#include "Cdd_Dma.h"
#include "QSpiFlashApp_Startup.h"

Mcal_CacheP_Config gCacheConfig = {
    .enable            = 1,
    .enableForceWrThru = 0,
};

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void QSpiFlashApp_qspiSFITest(QSpiFlashApp_Obj *appObj, QSpiFlashApp_TestParams *testPrms);

static uint32 QSpiFlashApp_getTestId(QSpiFlashApp_Obj *appObj);
static void   QSpiFlashApp_printRunTime(const QSpiFlashApp_TestParams *testPrms);
static void   QSpiFlashApp_QSpiSeqEndNotification(void);
static void   QSpiFlashApp_QSpiJobEndNotification(void);

#if (SPI_JOB_LOG == STD_ON)
static void QSpiFlashApp_printJobLog(const QSpiFlashApp_TestParams *testPrms);
#endif /* #if (SPI_JOB_LOG == STD_ON) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint32 gTestPassed = E_OK;
volatile uint8  gQspiApp_dstBuff1[QSPI_APP_FLASH_BLOCK_SIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));

volatile uint8  gQspiApp_srcBuff1[QSPI_APP_FLASH_BLOCK_SIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));
volatile uint32 gQspiJobDone[SPI_MAX_JOBS], gQspiSeqDone[SPI_MAX_SEQ];

/* Test application object */
QSpiFlashApp_Obj gQSpiFlashAppObj;

CONST(Spi_RegisterPtrType, SPI_CONST)
Spi_HWUnit_at[] = {
    (Spi_RegisterPtrType)SPI_REGISTER_BASE_0,
    (Spi_RegisterPtrType)SPI_REGISTER_BASE_1,
};

CONST(Spi_RamBufferPtrType, SPI_CONST)
Spi_RamUnit_at[] = {
    (Spi_RamBufferPtrType)SPI_RAM_BASE_0,
    (Spi_RamBufferPtrType)SPI_RAM_BASE_1,
};

CONST(Spi_HWUnitPropertyType, SPI_CONST)
Spi_UnitProperty_at[] = {
    {1U, 0U},
    {1U, 1U},
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32                   testId;
    QSpiFlashApp_Obj        *appObj = &gQSpiFlashAppObj;
    QSpiFlashApp_TestParams *testPrms;

    gTestPassed = E_OK;
    Mcal_CacheP_init();
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    vimInit();
    QSpiFlashApp_Startup();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\n\r");

#ifdef QSPI_FLASH_QT
    appObj->enableAutoRun = (uint32)TRUE;
#else
    appObj->enableAutoRun = (uint32)FALSE;
#endif

    /* Get the TestId */
    while (1U)
    {
        /* Get the TestId */
        testId = QSpiFlashApp_getTestId(appObj);
        if (testId < SPI_APP_NUM_TESTS)
        {
            testPrms         = &gQSpiFlashAppTestPrms[testId];
            testPrms->testId = testId;
            AppUtils_printf("Running test : %d: %s\n\r", testId, gQSpiFlashAppTestPrms[testId].testDescStr);
            QSpiFlashApp_qspiSFITest(appObj, testPrms);
        }
        else
        {
            /* Exit */
            break;
        }
    }

    if (E_OK == gTestPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, "All tests have passed\n");
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, " QSPI Test Failed!!!\n\r");
    }
    while (1)
        ;
    return (0U);
}

static boolean QSpiFlashApp_qspiGetResult(QSpiFlashApp_Obj *appObj, const QSpiFlashApp_TestParams *testPrms)
{
    Spi_StatusType    status;
    uint32            index;
    uint32            testPassed = E_OK;
    Spi_SequenceType  seqId;
    Spi_JobType       jobId;
    Spi_SeqResultType seqResult;
    Spi_JobResultType jobResult;

    /* SPI driver should be free now - check */
    status = Spi_GetStatus();
    if (status != SPI_IDLE)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf("SPI driver is not IDLE!!\n\r");
        return testPassed;
    }
    for (index = 0U; index < testPrms->spiConfig.maxSeq; index++)
    {
        seqId     = testPrms->spiConfig.seqCfg[index].seqId;
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
            break;
        }
    }
    if (index < testPrms->spiConfig.maxSeq)
    {
        return testPassed;
    }
    for (index = 0U; index < testPrms->spiConfig.maxJobs; index++)
    {
        jobId     = testPrms->spiConfig.jobCfg[index].jobId;
        jobResult = Spi_GetJobResult(jobId);
        if (jobResult != SPI_JOB_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf("SPI Job is not OK!!\n\r");
            break;
        }
    }
    return (testPassed == E_OK);
}

static boolean QSpiFlashApp_qspiQuickTest(QSpiFlashApp_Obj *appObj, const QSpiFlashApp_TestParams *testPrms)
{
    volatile uint32 dstAddr, srcOffsetAddr;
    volatile uint32 srcAddr, dstOffsetAddr;
    volatile uint32 length;
    uint32          i;
    uint8          *patternOrg = (uint8 *)(gQspiApp_srcBuff1);
    uint8          *patternAddr;
    uint8          *patternRead = (uint8 *)(gQspiApp_dstBuff1);
    uint32         *srctest, *dsttest;
    uint32          offset_addr = 0x10000; /* 64KB offset */
    boolean         testPassed  = TRUE;

    /* Erase the first block */
    QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
    AppUtils_printf("\nErasing QSPI Flash Block\n\r");
    QSPIFlashLib_FlashBlockErase((offset_addr / QSPIFLASH_SECTORSIZE), QSPI_IS_ASYNC);

    AppUtils_printf("\nErase Complete\n\r");

    AppUtils_printf("\nWriting test pattern to flash.. \n\r");
    length      = QSPI_APP_READ_LENGTH; /* in words */
    patternAddr = patternOrg;
    for (i = 0U; i < (length * 4U); i++)
    {
        *patternAddr++ = i + 8U;
    }

    /* Write data from DDR location to flash at offset address  */
    srcAddr       = (uint32)patternOrg;
    dstOffsetAddr = offset_addr;
    while (length > 64U)
    {
        QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
        QSPIFlashLib_WriteCfgMode(dstOffsetAddr, srcAddr, 64U, QSPI_IS_ASYNC);
        /* 64U words -- 64U*4U= 256U bytes */
        length        -= 64U;
        dstOffsetAddr += 256U;
        srcAddr       += 256U;
    }
    if (length > 0U)
    {
        QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
        QSPIFlashLib_WriteCfgMode(dstOffsetAddr, srcAddr, length, QSPI_IS_ASYNC);
    }
    AppUtils_printf("\nWrite flash Completed\n\r");

    AppUtils_printf("\nReading the flash data..\n\r");

    /* Read From 0x10 words from offset address 0x100 Memory mapped
     *mode*/
    dstAddr       = (uint32)patternRead;
    srcOffsetAddr = offset_addr;
    length        = QSPI_APP_READ_LENGTH;

    if (testPrms->rdWrDataType == QSPI_RDWR_DATA_TYPE_CFG_MODE)
    {
        while (length > 64U)
        {
            QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, 64U, QSPI_IS_ASYNC);
            /* 64U words -- 64U*4U= 256U bytes */
            length        -= 64U;
            dstAddr       += 256U;
            srcOffsetAddr += 256U;
        }
        if (length > 0U)
        {
            QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, length, QSPI_IS_ASYNC);
        }
    }
    else
    {
        /* Memory mapped read can be performed without any restriction on size so
         * perform in single access */
        /* length is in SPI words */
        QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, length, QSPI_IS_ASYNC);
    }
    if (FALSE == testPrms->disableDataCheck)
    {
        srctest = (uint32 *)(gQspiApp_srcBuff1);
        dsttest = (uint32 *)(gQspiApp_dstBuff1);
        /* Check RX buffer against TX buffer */

        for (i = 0U; i < (length); i++)
        {
            volatile uint32 dataval = *dsttest;
            if (testPrms->rdWrDataType != QSPI_RDWR_DATA_TYPE_CFG_MODE)
            {
                dataval = (((dataval & 0xFF) << 24) | ((dataval & 0xFF00) << 8) | ((dataval & 0xFF0000) >> 8) |
                           ((dataval & 0xFF000000) >> 24));
            }
            if (*srctest != dataval)
            {
                AppUtils_printf("\n Data Read write error at flash location - %x", (i * 4U));
                break;
            }
            srctest++;
            dsttest++;
        }
        if (i == length)
        {
            AppUtils_printf("\nData Read Write Test Passed.\n\r");
            testPassed = TRUE;
        }
        else
        {
            testPassed = FALSE;
        }
    }
    AppUtils_printf("\nQuick Flash Test Complete.\n\r");
    return testPassed;
} /* end test case 1U*/

static boolean QSpiFlashApp_qspiFullTest(QSpiFlashApp_Obj *appObj, const QSpiFlashApp_TestParams *testPrms)
{
    volatile uint32  dstAddr, srcOffsetAddr;
    volatile uint32  srcAddr, dstOffsetAddr;
    volatile uint32  length;
    volatile uint32  i, k, sectorIdx, totalsector;
    volatile uint8  *patternOrg = (uint8 *)(gQspiApp_srcBuff1);
    volatile uint8  *patternAddr;
    volatile uint8  *patternRead = (uint8 *)(gQspiApp_dstBuff1);
    volatile uint32 *srctest, *dsttest;
    uint32           offset_addr = 0x10000; /* 64kB offset */
    boolean          testPassed  = TRUE;
    uint32           flash_size;
    uint32           buf_size;

    /* Erase the entire flash */
    AppUtils_printf("\nErasing entire QSPI Flash..This takes 50U-60U seconds\n\r");
    sectorIdx   = (offset_addr / QSPIFLASH_SECTORSIZE);
    totalsector = (QSPI_APP_FLASH_SIZE / QSPIFLASH_SECTORSIZE);
    while (sectorIdx < totalsector)
    {
        /* WriteEnable should be called every time before erase */
        QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
        QSPIFlashLib_FlashBlockErase(sectorIdx, QSPI_IS_ASYNC);
        sectorIdx++;
    }
    AppUtils_printf("\nErase Completed\n\r");

    /* If 128Mbit size of flash is 16MB and if 512Mbit size of flash is
     * 32MB */
    length      = QSPI_APP_READ_LENGTH; /* in words */
    patternAddr = patternOrg;
    for (i = 0U; i < (length * 4); i++)
    {
        *patternAddr++ = i + 8U;
    }

    flash_size = QSPI_APP_FLASH_SIZE - offset_addr;
    buf_size   = QSPI_APP_FLASH_BLOCK_SIZE;
    k          = (offset_addr / QSPIFLASH_SECTORSIZE);
    while (flash_size != 0U)
    {
        /* Write data from DDR location to flash at offset address  */
        srcAddr       = (uint32)patternOrg;
        dstOffsetAddr = offset_addr;
        if (flash_size > QSPI_APP_READ_LENGTH)
        {
            length = QSPI_APP_READ_LENGTH;
        }
        else
        {
            length = flash_size;
        }

        while (length > 64U)
        {
            QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
            QSPIFlashLib_WriteCfgMode(dstOffsetAddr, srcAddr, 64U, QSPI_IS_ASYNC);
            /* 64U words -- 64U*4U= 256U bytes */
            length        -= 64U;
            dstOffsetAddr += 256U;
            srcAddr       += 256U;
        }
        if (length > 0U)
        {
            QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
            QSPIFlashLib_WriteCfgMode(dstOffsetAddr, srcAddr, length, QSPI_IS_ASYNC);
        }
        /* Read From 0x10 words from offset address 0x100 Memory mapped
         *mode*/
        dstAddr       = (uint32)patternRead;
        srcOffsetAddr = offset_addr;
        if (flash_size > QSPI_APP_READ_LENGTH)
        {
            length = QSPI_APP_READ_LENGTH;
        }
        else
        {
            length = flash_size;
        }

        if (testPrms->rdWrDataType == QSPI_RDWR_DATA_TYPE_CFG_MODE)
        {
            while (length > 64U)
            {
                QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, 64U, QSPI_IS_ASYNC);
                /* 64U words -- 64U*4U= 256U bytes */
                length        -= 64U;
                dstAddr       += 256U;
                srcOffsetAddr += 256U;
            }
            if (length > 0U)
            {
                QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, length, QSPI_IS_ASYNC);
            }
        }
        else
        {
            /* Memory mapped read can be performed without any restriction on size so
             * perform in single access */
            /* length is in SPI words */

            Mcal_CacheP_wb((uint32 *)dstAddr, length, Mcal_CacheP_TYPE_ALL);
            if (length > 0U)
            {
                QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, length, QSPI_IS_ASYNC);
            }
            Mcal_CacheP_inv((uint32 *)dstAddr, length, Mcal_CacheP_TYPE_ALL);
        }
        length = QSPI_APP_READ_LENGTH;
        if (FALSE == testPrms->disableDataCheck)
        {
            srctest = (uint32 *)(gQspiApp_srcBuff1);
            dsttest = (uint32 *)(gQspiApp_dstBuff1);
            for (i = 0U; i < (length / 4); i++)
            {
                volatile uint32 dataval = *dsttest;
                if (testPrms->rdWrDataType != QSPI_RDWR_DATA_TYPE_CFG_MODE)
                {
                    dataval = (((dataval & 0xFF) << 24) | ((dataval & 0xFF00) << 8) | ((dataval & 0xFF0000) >> 8) |
                               ((dataval & 0xFF000000) >> 24));
                }
                if (*srctest != dataval)
                {
                    AppUtils_printf(
                        "\nData Read write error at flash location"
                        " - %x",
                        ((i * 4U) + offset_addr));
                    testPassed = FALSE;
                    break;
                }
                srctest++;
                dsttest++;
            }
            if (testPassed == FALSE)
            {
                AppUtils_printf("\nError testing block num: %d", k);
                break;
            }
            if ((k % 20U) == 0U)
            {
                /* Print Success Msg only once in 20U times not to clutter
                 * uart console, still letting user know test is in progress
                 **/
                AppUtils_printf("\nTesting Completed till block no: %d\n\r", k);
            }
        }
        k++;
        offset_addr += buf_size;
        flash_size  -= buf_size;
    }

    AppUtils_printf("\nEntire Flash Test Complete\n\r");
    offset_addr = 0x0;
    return testPassed;
}

static boolean QSpiFlashApp_qspiCustomMMWriteTest(QSpiFlashApp_Obj *appObj, const QSpiFlashApp_TestParams *testPrms)
{
    volatile uint32  srcAddr, dstOffsetAddr;
    volatile uint32  length;
    volatile uint32  i, k, blockIdx, totalBlock;
    volatile uint8  *patternOrg = (uint8 *)(gQspiApp_srcBuff1);
    volatile uint8  *patternAddr;
    //    uint8          *patternRead = (uint8 *) (gQspiApp_dstBuff1);
    //  uint32         *srctest, *dsttest;
    volatile uint32  offset_addr = 0x10000; /* 64B offset */
    volatile boolean testPassed  = TRUE;
    volatile uint32  flash_size;
    volatile uint32  buf_size;

    /* Erase the entire flash */
    AppUtils_printf("\nErasing entire QSPI Flash..This takes 50U-60U seconds\n\r");
    blockIdx   = (offset_addr / QSPIFLASH_SECTORSIZE);
    totalBlock = (QSPI_APP_FLASH_SIZE / QSPIFLASH_SECTORSIZE);
    while (blockIdx < totalBlock)
    {
        /* WriteEnable should be called every time before erase */
        QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
        QSPIFlashLib_FlashBlockErase(blockIdx, QSPI_IS_ASYNC);
        // AppUtils_delay(10U);
        blockIdx++;
    }
    AppUtils_printf("\nErase Completed\n\r");

    /* If 128Mbit size of flash is 16MB and if 512Mbit size of flash is
     * 32MB */
    length      = QSPI_APP_READ_LENGTH; /* in words */
    patternAddr = patternOrg;
    for (i = 0U; i < (length * 4); i++)
    {
        *patternAddr++ = i + 8U;
    }

    flash_size = QSPI_APP_FLASH_SIZE - offset_addr;
    buf_size   = QSPI_APP_FLASH_BLOCK_SIZE;
    k          = (offset_addr / QSPIFLASH_SECTORSIZE);
    while (flash_size != 0U)
    {
        /* Write data from DDR location to flash at offset address  */
        srcAddr       = (uint32)patternOrg;
        dstOffsetAddr = offset_addr;
        length        = QSPI_APP_READ_LENGTH;
        while (length > 64U)
        {
            QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
            // if (testPrms->rdWrDataType == QSPI_RDWR_DATA_TYPE_CFG_MODE)
            {
                QSPIFlashLib_WriteCfgMode(dstOffsetAddr, srcAddr, 64U, QSPI_IS_ASYNC);
            }

            /* 64U words -- 64U*4U= 256U bytes */
            length        -= 64U;
            dstOffsetAddr += 256U;
            srcAddr       += 256U;
        }
        if (length > 0U)
        {
            QSPIFlashLib_WriteEnable(QSPI_IS_ASYNC);
            //  if (testPrms->rdWrDataType == QSPI_RDWR_DATA_TYPE_CFG_MODE)
            {
                QSPIFlashLib_WriteCfgMode(dstOffsetAddr, srcAddr, length, QSPI_IS_ASYNC);
            }
        }

        k++;
        offset_addr += buf_size;
        flash_size  -= buf_size;
    }

    AppUtils_printf("\nEntire Flash Test Complete\n\r");
    offset_addr = 0x0;
    return testPassed;
}

static boolean QSpiFlashApp_qspiCustomMMReadTest(QSpiFlashApp_Obj *appObj, const QSpiFlashApp_TestParams *testPrms)
{
    volatile uint32  dstAddr, srcOffsetAddr;
    volatile uint32  length;
    volatile uint32  i, k;
    uint8           *patternOrg = (uint8 *)(gQspiApp_srcBuff1);
    uint8           *patternAddr;
    uint8           *patternRead = (uint8 *)(gQspiApp_dstBuff1);
    volatile uint32 *srctest, *dsttest;
    uint32           offset_addr = 0x10000; /* 64B offset */
    boolean          testPassed  = TRUE;
    uint32           flash_size;
    uint32           buf_size;

    // memset((void *)gQspiApp_dstBuff1, 0x0, QSPI_APP_FLASH_BLOCK_SIZE);
    for (i = 0; i < QSPI_APP_FLASH_BLOCK_SIZE; i++)
    {
        gQspiApp_srcBuff1[i] = 0x0;
        gQspiApp_dstBuff1[i] = 0x0;
    }
    /* If 128Mbit size of flash is 16MB and if 512Mbit size of flash is
     * 32MB */
    length      = QSPI_APP_READ_LENGTH; /* in words */
    patternAddr = patternOrg;
    for (i = 0U; i < (length * 4); i++)
    {
        *patternAddr++ = i + 8U;
    }

    flash_size = QSPI_APP_FLASH_SIZE - offset_addr;
    buf_size   = QSPI_APP_FLASH_BLOCK_SIZE;
    k          = (offset_addr / QSPIFLASH_SECTORSIZE);
    while (flash_size != 0U)
    {
        /* Read From 0x10 words from offset address 0x100 Memory mapped
         *mode*/
        dstAddr       = (uint32)patternRead;
        srcOffsetAddr = offset_addr;
        length        = QSPI_APP_READ_LENGTH;

        if (testPrms->rdWrDataType == QSPI_RDWR_DATA_TYPE_CFG_MODE)
        {
            while (length > 64U)
            {
                QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, 64U, QSPI_IS_ASYNC);
                /* 64U words -- 64U*4U= 256U bytes */
                length        -= 64U;
                dstAddr       += 256U;
                srcOffsetAddr += 256U;
            }
            if (length > 0U)
            {
                QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, length, QSPI_IS_ASYNC);
            }
        }
        else
        {
            /* Memory mapped read can be performed without any restriction on size so
             * perform in single access */
            /* length is in SPI words */

            Mcal_CacheP_wb((uint32 *)dstAddr, length, Mcal_CacheP_TYPE_ALL);
            if (length > 0U)
            {
                QSPIFlashLib_ReadCfgMode(dstAddr, srcOffsetAddr, length, QSPI_IS_ASYNC);
            }
            Mcal_CacheP_inv((uint32 *)dstAddr, length, Mcal_CacheP_TYPE_ALL);
        }
        if (FALSE == testPrms->disableDataCheck)
        {
            srctest = (uint32 *)(gQspiApp_srcBuff1);
            dsttest = (uint32 *)(gQspiApp_dstBuff1);

            for (i = 0U; i < (length / 4); i++)
            {
                uint32 dataval = *dsttest;
                if (testPrms->rdWrDataType != QSPI_RDWR_DATA_TYPE_CFG_MODE)
                {
                    dataval = (((dataval & 0xFF) << 24) | ((dataval & 0xFF00) << 8) | ((dataval & 0xFF0000) >> 8) |
                               ((dataval & 0xFF000000) >> 24));
                }
                if (*srctest != dataval)
                {
                    AppUtils_printf(
                        "\nData Read write error at flash location"
                        " - %x",
                        ((i * 4U) + offset_addr));
                    testPassed = FALSE;
                    break;
                }
                srctest++;
                dsttest++;
            }
            if (testPassed == FALSE)
            {
                AppUtils_printf("\nError testing block num: %d", k);
                break;
            }
            if ((k % 20U) == 0U)
            {
                /* Print Success Msg only once in 20U times not to clutter
                 * uart console, still letting user know test is in progress
                 **/
                AppUtils_printf("\nTesting Completed till block no: %d\n\r", k);
            }
        }
        k++;
        offset_addr += buf_size;
        flash_size  -= buf_size;
    }

    AppUtils_printf("\nEntire Flash Test Complete\n\r");
    offset_addr = 0x0;
    return testPassed;
}

static void QSpiFlashApp_qspiSFITest(QSpiFlashApp_Obj *appObj, QSpiFlashApp_TestParams *testPrms)
{
    volatile uint32 index, loopCount;
    boolean         testPassed = TRUE;
    Std_ReturnType  retVal;
    Spi_StatusType  status;
    uint32          device_Id;
#if (STD_ON == MCU_INIT_CLOCK_API)

    volatile Mcu_ClockType clockSetting;
#endif /* #if (STD_ON == MCU_INIT_CLOCK_API) */
#if (SPI_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
#endif /* #if (SPI_VERSION_INFO_API == STD_ON) */

    memcpy(&appObj->testPrms, testPrms, sizeof(appObj->testPrms));
#if (STD_ON == MCU_INIT_CLOCK_API)

    clockSetting = QSPI_APP_CLKSRC_40M_CLK;
    retVal       = Mcu_InitClock(clockSetting);
    GT_assert(McalAppTrace, (retVal == E_OK));
#endif /* #if (STD_ON == MCU_INIT_CLOCK_API) */

    QSPIFlashLib_Initialize(testPrms->deviceType, &testPrms->spiConfig, QSpiFlashApp_QSpiSeqEndNotification,
                            QSpiFlashApp_QSpiJobEndNotification, testPrms->rdWrDataType, 32U, QSPI_IS_ASYNC);
    /* Print test case information */
    AppUtils_printf(APP_NAME ": CH %d: JOBS %d: SEQ %d: HWUNIT %d: LOOP COUNT %d:!!!\n\r",
                    testPrms->spiConfig.maxChannels, testPrms->spiConfig.maxJobs, testPrms->spiConfig.maxSeq,
                    testPrms->spiConfig.maxHwUnit, appObj->testPrms.loopCount);
    QSpiFlashApp_printRunTime(testPrms);

    /* Init */

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
        testPassed = FALSE;
        AppUtils_printf("SPI driver is not IDLE!!\n\r");
    }

#if (SPI_HW_STATUS_API == STD_ON)
    /* SPI HW unit should be free now - check */
    for (index = 0U; index < testPrms->spiConfig.maxHwUnit; index++)
    {
        status = Spi_GetHWUnitStatus(testPrms->spiConfig.hwUnitCfg[index].hwUnitId);
        if (status != SPI_IDLE)
        {
            testPassed = FALSE;
            AppUtils_printf("SPI HW %d is not IDLE!!\n\r", testPrms->spiConfig.hwUnitCfg[index].hwUnitId);
        }
    }
#endif /* #if (SPI_HW_STATUS_API == STD_ON) */

    loopCount = 0U;
    while (loopCount < testPrms->loopCount)
    {
        /* Reset flags */
        for (index = 0U; index < SPI_MAX_JOBS; index++)
        {
            gQspiJobDone[index] = FALSE;
        }
        for (index = 0U; index < SPI_MAX_SEQ; index++)
        {
            gQspiSeqDone[index] = FALSE;
        }

        device_Id = QSPIFlashLib_GetDeviceId(QSPI_IS_ASYNC);

        AppUtils_printf("\nMID - %x", (device_Id & 0xFFU));
        AppUtils_printf("\nDID - %x", ((device_Id & 0xFF00U) >> 8U));

        testPassed = QSpiFlashApp_qspiGetResult(appObj, testPrms);
        GT_assert(McalAppTrace, (TRUE == testPassed));

        if (testPrms->flashTestType == QSPI_APP_TEST_TYPE_QUICK)
        {
            testPassed = QSpiFlashApp_qspiQuickTest(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
            testPassed = QSpiFlashApp_qspiGetResult(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
        }
        else if (testPrms->flashTestType == QSPI_APP_TEST_TYPE_EXTENDED)
        {
            Cdd_Dma_Init(NULL_PTR);
            Spi_qspiChannelConfig();  // for cbk register

            testPassed = QSpiFlashApp_qspiFullTest(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
            testPassed = QSpiFlashApp_qspiGetResult(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
            Cdd_Dma_DeInit();
        }
        else if (testPrms->flashTestType == QSPI_APP_TEST_TYPE_CUSTOM_READ)
        { /* just done for async mode */
            Cdd_Dma_Init(NULL_PTR);
            Spi_qspiChannelConfig();  // for cbk register

            testPassed = QSpiFlashApp_qspiCustomMMReadTest(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
            testPassed = QSpiFlashApp_qspiGetResult(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
            Cdd_Dma_DeInit();
        }
        else
        {
            testPassed = QSpiFlashApp_qspiCustomMMWriteTest(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
            testPassed = QSpiFlashApp_qspiGetResult(appObj, testPrms);
            GT_assert(McalAppTrace, (TRUE == testPassed));
        }
        loopCount++;
    }

#if (SPI_JOB_LOG == STD_ON)
    QSpiFlashApp_printJobLog(testPrms);
#endif /* #if (SPI_JOB_LOG == STD_ON) */

    /* DeInit */
    retVal = Spi_DeInit();
    if (retVal != E_OK)
    {
        testPassed = FALSE;
        AppUtils_printf("SPI Deinit Failed!!\n\r");
    }

    /* SPI driver should be uninit now - check */
    status = Spi_GetStatus();
    if (status != SPI_UNINIT)
    {
        testPassed = FALSE;
        AppUtils_printf("SPI driver is not in uninit state!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        if (testPassed == FALSE)
        {
            gTestPassed = E_NOT_OK;
        }
    }
    if (E_OK == gTestPassed)
    {
        AppUtils_printf("SPI Test Passed!!!\n\r");
    }
    else
    {
        AppUtils_printf("SPI Test Failed!!!\n\r");
    }

    return;
}

void QSpiFlashApp_QSpiSeqEndNotification(void)
{
    gQspiSeqDone[0U] = TRUE;

    return;
}

static void QSpiFlashApp_QSpiJobEndNotification(void)
{
    gQspiJobDone[0U] = TRUE;

    return;
}

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

/**
 *  \brief Return the test ID to run.
 */
static uint32 QSpiFlashApp_getTestId(QSpiFlashApp_Obj *appObj)
{
    uint32        testCnt;
    static sint32 testId = 0U;

    AppUtils_printf(" \n\r");
    AppUtils_printf("--------------------------------------\n\r");
    AppUtils_printf("Select test to run as per below table:\n\r");
    AppUtils_printf("--------------------------------------\n\r");
    AppUtils_printf(" \n\r");
    for (testCnt = 0U; testCnt < SPI_APP_NUM_TESTS; testCnt++)
    {
        AppUtils_printf("%c: %s\n\r", ('a' + testCnt), gQSpiFlashAppTestPrms[testCnt].testDescStr);
    }
    AppUtils_printf("%c: %s\n\r", ('a' + SPI_APP_NUM_TESTS), "Auto Run\n\r");
    AppUtils_printf("%c: EXIT\n\r", 'x');
    AppUtils_printf(" \n\r");
    AppUtils_printf("Enter Test to Run (Use UART1 console): \n\r");

    if (TRUE == appObj->enableAutoRun)
    {
        testId++;
        if (testId < SPI_APP_NUM_TESTS)
        {
            AppUtils_printf("%c \r \n", 'a' + testId);
        }
    }
    else
    {
        while (1U)
        {
            char option;

            {
                option = AppUtils_getChar();
            }
            AppUtils_printf("\n Option entered = %c \r \n", option);

            testId = option - 'a';

            if (testId < SPI_APP_NUM_TESTS)
            {
                break;
            }
            else if (testId == SPI_APP_NUM_TESTS)
            {
                appObj->enableAutoRun = (uint32)TRUE;
                testId                = 0U;
                break;
            }
            else if (('x' - 'a') == testId)
            {
                break;
            }
            AppUtils_printf("Invalid Test ID. Enter Again!!\n\r");
        }
    }

    return (testId);
}

/**
 *  \brief Prints the expected runtime for the testcase
 */
static void QSpiFlashApp_printRunTime(const QSpiFlashApp_TestParams *testPrms)
{
    uint32                                  seqIndex, jobIndex, chIndex, jobId, chId;
    float32                                 bitsSent, jobTime, totalTime;
    uint32                                  clkRateHz, totalTimeMs;
    const Spi_QspiExternalDeviceConfigType *extDevCfg;
    uint32                                  extDevCfgId;

    totalTime = 0U;
    for (seqIndex = 0U; seqIndex < testPrms->spiConfig.maxSeq; seqIndex++)
    {
        for (jobIndex = 0U; jobIndex < testPrms->spiConfig.seqCfg[seqIndex].jobPerSeq; jobIndex++)
        {
            jobId       = testPrms->spiConfig.seqCfg[seqIndex].jobList[jobIndex];
            jobTime     = 0U;
            extDevCfgId = testPrms->spiConfig.jobCfg[jobId].externalDeviceCfgId;
            extDevCfg   = &testPrms->spiConfig.extDevCfg[extDevCfgId].qspi;
            clkRateHz   = SPI_MIBSPI_FCLK / (extDevCfg->clkDivider + 1U);
            for (chIndex = 0U; chIndex < testPrms->spiConfig.jobCfg[jobId].channelPerJob; chIndex++)
            {
                chId      = testPrms->spiConfig.jobCfg[jobId].channelList[chIndex];
                bitsSent  = testPrms->spiConfig.channelCfg[chId].dataWidth;
                jobTime  += (bitsSent / clkRateHz);
            }
            totalTime += jobTime;
        }
    }
    totalTime *= testPrms->loopCount;

    totalTimeMs = (totalTime * 1000U);
    AppUtils_printf("Total Expected Time for Transmission (without mem compare): %dms!!\n\r", totalTimeMs);

    return;
}

#if (SPI_JOB_LOG == STD_ON)
static void QSpiFlashApp_printJobLog(const QSpiFlashApp_TestParams *testPrms)
{
    uint32               numEntries, logIndex, index;
    Spi_JobLogEntryType *logEntry;
    char                *hwUnitName[] = {"McSPI1", "McSPI2", "QSPI"};

    if (gSpiJobLogObj.totalLog >= SPI_MAX_JOB_LOG)
    {
        logIndex   = gSpiJobLogObj.logIndex;
        numEntries = SPI_MAX_JOB_LOG;
    }
    else
    {
        logIndex   = 0U;
        numEntries = gSpiJobLogObj.logIndex;
    }

    AppUtils_printf(" \n\r");
    AppUtils_printf("SPI Job Log:\n\r");
    AppUtils_printf("Index  Timestamp   Job ID(Priority)  Seq ID      HW Unit ID\n\r");
    AppUtils_printf("-----------------------------------------------------------\n\r");

    index = 1U;
    while (numEntries > 0U)
    {
        logEntry = &gSpiJobLogObj.logEntry[logIndex];
        AppUtils_printf("%-4d   0x%08x  %3d(%d)            %3d         %s\n\r", index, logEntry->timeStamp,
                        logEntry->jobId, testPrms->spiConfig.jobCfg[logEntry->jobId].jobPriority, logEntry->seqId,
                        hwUnitName[logEntry->hwUnitId]);

        logIndex++;
        if (logIndex >= SPI_MAX_JOB_LOG)
        {
            logIndex = 0U;
        }

        numEntries--;
        index++;
    }
    AppUtils_printf(" \n\r");

    return;
}

#endif /* #if (SPI_JOB_LOG == STD_ON) */
