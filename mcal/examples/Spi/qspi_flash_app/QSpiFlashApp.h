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
 *  \file     QSpiFlashApp.h
 *
 *  \brief    QSPI flash example header file
 *
 */

#ifndef QSPI_FLASH_APP_H_
#define QSPI_FLASH_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "appUtils_QSpiFlashLib.h"

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "QSPI_FLASH_APP"

/* Default loop count. */
#define SPI_APP_LOOP_COUNT (1U)

/* Performance loop count. */
#define SPI_APP_PERF_LOOP_COUNT (1000U)

/** \brief Default clock divider - clock is 48MHz */
#define SPI_APP_DEFAULT_DIVIDER (0U)

/**
 *  \brief Clock divider used for interruptible sequence testing. The SPI clock
 *  should be lower so that the second sequence gets scheduled. Otherwise
 *  the CPU will fully execute the first sequence in ISR as the McSPI data rate
 *  is faster than the code execution.
 */
#define SPI_APP_INTR_SEQ_DIVIDER (47U)

typedef enum
{
    QSPI_APP_TEST_TYPE_QUICK,
    QSPI_APP_TEST_TYPE_EXTENDED,
    QSPI_APP_TEST_TYPE_CUSTOM_READ,
    QSPI_APP_TEST_TYPE_CUSTOM_WRITE
} qspiAppTestType;

typedef enum
{
    QSPI_RDWR_DATA_TYPE_CFG_MODE,
    QSPI_RDWR_DATA_TYPE_MEMMAPPED_MODE
} qspiRdWrDataType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief SPI application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    char                   *testDescStr;
    /**< Test description. */
    uint32                  loopCount;
    /**< Number of iteration to run transmit. */
    uint32                  disableDataCheck;
    /**< Disable data check - used for performance. */
    Spi_ConfigType          spiConfig;
    /**< SPI configuration */
    uint32                  testId;
    /**< Test ID for print purpose. This is initialized in the code */
    QspiFlashLib_deviceType deviceType;
    /**< Flash device type */
    qspiAppTestType         flashTestType;
    /**< Flash test type */
    qspiRdWrDataType        rdWrDataType;
    /**< Flash test type */
} QSpiFlashApp_TestParams;

/**
 *  \brief Test application data structure.
 */
typedef struct
{
    QSpiFlashApp_TestParams testPrms;
    /**< Current test parameters. */
    uint32                  enableAutoRun;
    /**< Auto-run enable flag. */
} QSpiFlashApp_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static QSpiFlashApp_TestParams gQSpiFlashAppTestPrms[] = {
    {
        .testDescStr            = (char *)"QSPI Serial Flash Test - Spansion 1 bit/Quick\n\r",
        .loopCount              = SPI_APP_LOOP_COUNT, /* loopCount */
        .disableDataCheck       = FALSE,              /* disableDataCheck */
        .spiConfig.maxExtDevCfg = 1,
        .deviceType             = DEVICE_TYPE_SPANSION_QSPI1,
        .flashTestType          = QSPI_APP_TEST_TYPE_QUICK,
        .rdWrDataType           = QSPI_RDWR_DATA_TYPE_CFG_MODE,
    },
    {
        .testDescStr            = (char *)"QSPI Serial Flash Test - Spansion 4 bit/Quick\n\r",
        .loopCount              = SPI_APP_LOOP_COUNT, /* loopCount */
        .disableDataCheck       = FALSE,              /* disableDataCheck */
        .spiConfig.maxExtDevCfg = 1,
        .deviceType             = DEVICE_TYPE_SPANSION_QSPI4,
        .flashTestType          = QSPI_APP_TEST_TYPE_QUICK,
        .rdWrDataType           = QSPI_RDWR_DATA_TYPE_CFG_MODE,
    },
    {
        .testDescStr            = (char *)"QSPI Serial Flash Test - Spansion 4 bit/Extended\n\r",
        .loopCount              = SPI_APP_LOOP_COUNT, /* loopCount */
        .disableDataCheck       = FALSE,              /* disableDataCheck */
        .spiConfig.maxExtDevCfg = 1,
        .deviceType             = DEVICE_TYPE_SPANSION_QSPI4,
        .flashTestType          = QSPI_APP_TEST_TYPE_EXTENDED,
        .rdWrDataType           = QSPI_RDWR_DATA_TYPE_CFG_MODE,
    },
    {
        .testDescStr            = (char *)"QSPI Serial Flash Test - MemMap Spansion 4 bit/Extended Write\n\r",
        .loopCount              = SPI_APP_LOOP_COUNT, /* loopCount */
        .disableDataCheck       = FALSE,              /* disableDataCheck */
        .spiConfig.maxExtDevCfg = 1,
        .deviceType             = DEVICE_TYPE_SPANSION_QSPI4,
        .flashTestType          = QSPI_APP_TEST_TYPE_CUSTOM_WRITE,
        .rdWrDataType           = QSPI_RDWR_DATA_TYPE_MEMMAPPED_MODE,
    },
    {
        .testDescStr            = (char *)"QSPI Serial Flash Test - MemMap Spansion 4 bit/Extended Read\n\r",
        .loopCount              = SPI_APP_LOOP_COUNT, /* loopCount */
        .disableDataCheck       = FALSE,              /* disableDataCheck */
        .spiConfig.maxExtDevCfg = 1,
        .deviceType             = DEVICE_TYPE_SPANSION_QSPI4,
        .flashTestType          = QSPI_APP_TEST_TYPE_CUSTOM_READ,
        .rdWrDataType           = QSPI_RDWR_DATA_TYPE_MEMMAPPED_MODE,
    },
    {
        .testDescStr            = (char *)"QSPI Serial Flash Test - Spansion 4 bit/Extended\n\r",
        .loopCount              = SPI_APP_LOOP_COUNT, /* loopCount */
        .disableDataCheck       = FALSE,              /* disableDataCheck */
        .spiConfig.maxExtDevCfg = 1,
        .deviceType             = DEVICE_TYPE_SPANSION_QSPI4,
        .flashTestType          = QSPI_APP_TEST_TYPE_EXTENDED,
        .rdWrDataType           = QSPI_RDWR_DATA_TYPE_MEMMAPPED_MODE,
    },

};

#define SPI_APP_NUM_TESTS (sizeof(gQSpiFlashAppTestPrms) / sizeof(gQSpiFlashAppTestPrms[0U]))

#ifdef __cplusplus
}
#endif

#endif /* #ifndef QSPI_FLASH_APP_H_ */
