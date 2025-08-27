/* ======================================================================
 *   Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     McspiApp.c
 *
 *  \brief    This file contains the SPI test example for McSPI
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

/*LDRA_ANALYSIS*/
#include "Spi_Cfg.h"
#include "Spi.h"
#include "Spi_Dbg.h"
#include "SchM_Spi.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "SchM_Port.h"
#include "McspiApp.h"
#include "McspiApp_Startup.h"
#if (STD_ON == SPI_DMA_ENABLE)
#include "CacheP.h"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32 SpiApp_TestPassed = E_OK;

/* SPI External Buffers for Tx and Rx */
#if (STD_OFF == SPI_DMA_ENABLE)
uint8 gMcspiTxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD];
uint8 gMcspiRxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD];
#else
uint8 gMcspiTxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));
uint8 gMcspiRxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));
#endif

#if (STD_ON == APP_PERFORMANCE_MODE)
static void MCSPIExample_PerformanceTest();
#endif
volatile uint32 SpiApp_McspiJobDone[SPI_MAX_JOBS + 1], SpiApp_McspiSeqDone[SPI_MAX_SEQ + 1];

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration;
#endif

/** \brief SPI Channel PC Configuration struct declaration */
extern const struct Spi_ChannelConfigType_PC_s Spi_ChannelConfig_PC[SPI_MAX_CHANNELS];

/** \brief SPI Job PC Configuration struct declaration */
extern const struct Spi_JobConfigType_PC_s Spi_JobConfig_PC[SPI_MAX_JOBS];

/** \brief SPI Sequence PC Configuration struct declaration */
extern const struct Spi_SeqConfigType_PC_s Spi_SeqConfig_PC[SPI_MAX_SEQ];

static void SpiApp_platformDeinit(void);

#define SPI_APP_NUM_CLK_LIST (sizeof(gClkDividerTestList) / sizeof(gClkDividerTestList[0U]))
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32                index, chIndex, isPending;
    uint32                testPassed = E_OK, matching;
    uint8                *tempTxPtr, *tempRxPtr;
    uint32                byteLength[SPI_MAX_CHANNELS] = {0U};
    uint32                xferLength[SPI_MAX_CHANNELS] = {0U};
    Std_ReturnType        retVal;
    Spi_StatusType        status;
    Spi_SeqResultType     seqResult;
    Spi_JobResultType     jobResult;
    Spi_ChannelType       chId;
    Spi_SequenceType      seqId;
    Spi_JobType           jobId;
    const Spi_ConfigType *cfgPtr = &SpiDriver;
    Std_VersionInfoType   versioninfo;

    McspiApp_Startup();
    SpiApp_platformInit();
#if (SPI_DMA_ENABLE == STD_ON)
    Cdd_Dma_Init(NULL_PTR);
#endif

#if (STD_ON == SPI_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n\r");
    Spi_Init((const Spi_ConfigType *)NULL_PTR);
#elif (STD_ON == SPI_VARIANT_POST_BUILD)
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
    Spi_Init(cfgPtr);
#elif (STD_ON == SPI_LINK_TIME_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Link Time being used !!!\n\r");
    Spi_Init(cfgPtr);
#endif

    AppUtils_printf(APP_NAME "\n\r: Sample Application - STARTS !!!\n\r");

#if (SPI_VERSION_INFO_API == STD_ON)
    /* Get and print version */
    Spi_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n");
    AppUtils_printf("SPI MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf("Vendor ID           : %d\n\r", versioninfo.vendorID);
    AppUtils_printf("Module ID           : %d\n\r", versioninfo.moduleID);
    AppUtils_printf("SW Major Version    : %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf("SW Minor Version    : %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf("SW Patch Version    : %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n");
#endif /* #if (SPI_VERSION_INFO_API == STD_ON) */

#if (STD_ON == APP_PERFORMANCE_MODE)
    MCSPIExample_PerformanceTest();
#endif
    /* Print test case information */
    AppUtils_printf(APP_NAME ": CH %d: JOBS %d: SEQ %d: HWUNIT %d: NUM OF WORDS %d:!!!\n\r", cfgPtr->maxChannels,
                    cfgPtr->maxJobs, cfgPtr->maxSeq, cfgPtr->maxHwUnit, SPI_APP_RX_TX_LENGTH);
    /* Init */
    SpiApp_interruptConfig();

    /* SPI driver should be free now - check */

    status = Spi_GetStatus();
    if (status != SPI_IDLE)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf(APP_NAME ": SPI driver is not IDLE!!\n");
    }
#if (SPI_HW_STATUS_API == STD_ON)
    /* SPI HW unit should be free now - check */
    for (index = 0U; index < cfgPtr->maxHwUnit; index++)
    {
        status = Spi_GetHWUnitStatus(cfgPtr->hwUnitCfg[index].hwUnitId);
        if (status != SPI_IDLE)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf(APP_NAME ": SPI HW %d is not IDLE!!\n", cfgPtr->hwUnitCfg[index].hwUnitId);
        }
    }
#endif /* #if (SPI_HW_STATUS_API == STD_ON) */

#if (SPI_SCALEABILITY == SPI_LEVEL_2)
    /* Set Async mode */
    /** \brief Default ASYNC/SYNC Transmit flag - TRUE: Async, FALSE: Sync */
    retVal = Spi_SetAsyncMode(SPI_APP_DEFAULT_ASYNC_MODE);
    if (retVal != E_OK)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf(APP_NAME ": SPI Set Async Mode Failed!!\n");
    }
#endif /* #if (SPI_SCALEABILITY == SPI_LEVEL_2) */

    /* Init test params */
    for (chIndex = 0U; chIndex < cfgPtr->maxChannels; chIndex++)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr = (Spi_DataBufferType *)&gMcspiTxBuffer[chIndex][0U];
        tempRxPtr = (Spi_DataBufferType *)&gMcspiRxBuffer[chIndex][0U];
        for (index = 0U; index < (RX_TX_BUF_SIZE_WORD); index++)
        {
            *tempTxPtr++ = (Spi_DataBufferType)(index + 1U);
            *tempRxPtr++ = 0U;
        }
        if (cfgPtr->channelCfg[chIndex].dataWidth <= 8U)
        {
            xferLength[chIndex] = SPI_APP_RX_TX_LENGTH;
        }
        else if (cfgPtr->channelCfg[chIndex].dataWidth <= 16U)
        {
            xferLength[chIndex] = SPI_APP_RX_TX_LENGTH / 2;
        }
        else
        {
            xferLength[chIndex] = SPI_APP_RX_TX_LENGTH / 4;
        }
    }

    for (chIndex = 0U; chIndex < cfgPtr->maxChannels; chIndex++)
    {
        /* Memset RX buffer for every run */
        if (cfgPtr->channelCfg[chIndex].dataWidth <= 8U)
        {
            byteLength[chIndex] = xferLength[chIndex];
        }
        else if (cfgPtr->channelCfg[chIndex].dataWidth <= 16U)
        {
            byteLength[chIndex] = xferLength[chIndex] * 2U;
        }
        else
        {
            byteLength[chIndex] = xferLength[chIndex] * 4U;
        }
        tempRxPtr = (uint8 *)&gMcspiRxBuffer[chIndex][0U];
        for (index = 0U; index < byteLength[chIndex]; index++)
        {
            *tempRxPtr++ = 0U;
        }
        /* SetUp Buffers */
#if ((SPI_CHANNELBUFFERS == SPI_IB_EB) || (SPI_CHANNELBUFFERS == SPI_EB))
        if (SPI_EB == cfgPtr->channelCfg[chIndex].channelBufType)
        {
            Spi_DataBufferType *srcDataBuf, *destDataBuf;

            /* Setup EB for TX/RX */
            srcDataBuf  = (Spi_DataBufferType *)&gMcspiTxBuffer[chIndex][0U];
            destDataBuf = (Spi_DataBufferType *)&gMcspiRxBuffer[chIndex][0U];
            chId        = Spi_ChannelConfig_PC[chIndex].channelId;
            retVal      = Spi_SetupEB(chId, srcDataBuf, destDataBuf, xferLength[chIndex]);
            if (retVal != E_OK)
            {
                testPassed = E_NOT_OK;
                AppUtils_printf(APP_NAME ": SPI Setup EB Failed!!\n\r");
            }
        }
#endif
#if ((SPI_CHANNELBUFFERS == SPI_IB_EB) || (SPI_CHANNELBUFFERS == SPI_IB))
        if (SPI_IB == cfgPtr->channelCfg[chIndex].channelBufType)
        {
            Spi_DataBufferType *srcDataBuf;

            /* Write TX data to IB */
            srcDataBuf = (Spi_DataBufferType *)&gMcspiTxBuffer[chIndex][0U];
            chId       = Spi_ChannelConfig_PC[chIndex].channelId;
            retVal     = Spi_WriteIB(chId, srcDataBuf);
            if (retVal != E_OK)
            {
                testPassed = E_NOT_OK;
                AppUtils_printf(APP_NAME ": SPI Write IB Failed!!\n\r");
            }
        }
#endif
    }

/* Cache writeback for all channel buffers in every job using DMA Enabled HwUnit ID */
#if (STD_ON == SPI_DMA_ENABLE)
    for (index = 0; index < cfgPtr->maxJobs; index++)
    {
        if (TRUE == cfgPtr->hwUnitCfg[cfgPtr->jobCfg[index].hwUnitId].enableDmaMode)
        {
            for (chIndex = 0; chIndex < cfgPtr->jobCfg[index].channelPerJob; chIndex++)
            {
                Mcal_CacheP_wb(&gMcspiTxBuffer[cfgPtr->jobCfg[index].channelList[chIndex]], RX_TX_BUF_SIZE_WORD,
                               Mcal_CacheP_TYPE_ALLD);
            }
        }
    }
#endif

    /* Reset flags */
    for (index = 0U; index < SPI_MAX_JOBS; index++)
    {
        SpiApp_McspiJobDone[index] = FALSE;
    }

    for (index = 0U; index < SPI_MAX_SEQ; index++)
    {
        SpiApp_McspiSeqDone[index] = FALSE;
    }

#if ((SPI_SCALEABILITY == SPI_LEVEL_1) || (SPI_SCALEABILITY == SPI_LEVEL_2))
    AppUtils_printf(APP_NAME ": SPI Async transmit in progress!!\n\r");
    for (index = 0U; index < cfgPtr->maxSeq; index++)
    {
        /* Start the TX/RX */
        seqId  = Spi_SeqConfig_PC[index].seqId;
        retVal = Spi_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf(APP_NAME ": SPI Async transmit Failed!!\n\r");
        }
    }

    if (SPI_INTERRUPT_MODE == SPI_APP_DEFAULT_ASYNC_MODE)
    {
        /* Wait for TX/RX to get over */
        while (1U)
        {
            isPending = FALSE;
            for (index = 0U; index < cfgPtr->maxSeq; index++)
            {
                if (SpiApp_McspiSeqDone[index] == FALSE)
                {
                    isPending = TRUE;
                    break;
                }
            }
            for (index = 0U; index < cfgPtr->maxJobs; index++)
            {
                if (SpiApp_McspiJobDone[index] == FALSE)
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
            for (index = 0U; index < cfgPtr->maxSeq; index++)
            {
                seqResult = Spi_GetSequenceResult(index);
                if (seqResult != SPI_SEQ_OK)
                {
                    isPending = TRUE;
                    break;
                }
            }
            for (index = 0U; index < cfgPtr->maxJobs; index++)
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

#if (STD_OFF == SPI_DMA_ENABLE)
#if ((SPI_SCALEABILITY == SPI_LEVEL_0) || (SPI_SCALEABILITY == SPI_LEVEL_2))
    for (index = 0U; index < cfgPtr->maxSeq; index++)
    {
        /* Start the TX/RX */
        seqId  = Spi_SeqConfig_PC[index].seqId;
        retVal = Spi_SyncTransmit(seqId);
        if (retVal != E_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf(APP_NAME ": SPI Sync transmit Failed!!\n\r");
        }
    }
#endif
#endif

    /* SPI driver should be free now - check */
    status = Spi_GetStatus();
    if (status != SPI_IDLE)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf(APP_NAME ": SPI driver is not IDLE!!\n\r");
    }
    for (index = 0U; index < cfgPtr->maxSeq; index++)
    {
        seqId     = Spi_SeqConfig_PC[index].seqId;
        seqResult = Spi_GetSequenceResult(seqId);
        if (seqResult != SPI_SEQ_OK)
        {
            if (seqResult == SPI_SEQ_CANCELLED)
            {
                AppUtils_printf(APP_NAME ": SPI Sequence was cancelled!!\n\r");
            }
            else
            {
                testPassed = E_NOT_OK;
                AppUtils_printf(APP_NAME ": SPI Sequence is not OK!!\n\r");
            }
        }
    }

    for (index = 0U; index < cfgPtr->maxJobs; index++)
    {
        jobId     = Spi_JobConfig_PC[index].jobId;
        jobResult = Spi_GetJobResult(jobId);
        if (jobResult != SPI_JOB_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf(APP_NAME ": SPI Job is not OK!!\n\r");
        }
    }
#if (STD_ON == SPI_REGISTER_READBACK_API)
    for (index = 0U; index < cfgPtr->maxHwUnit; index++)
    {
        Spi_RegisterReadbackType RegReadback, *RegRbPtr;
        RegRbPtr = &RegReadback;
        retVal   = Spi_RegisterReadback(cfgPtr->hwUnitCfg[index].hwUnitId, RegRbPtr);
        if (retVal != E_OK)
        {
            AppUtils_printf(APP_NAME ": SPI configuration Register Readback Failed!!\n\r");
        }
        else
        {
            /* AppUtils_printf( APP_NAME
                ": SPI Hwunit %d configuration Register Readback values  \n",
                (cfgPtr->hwUnitCfg[index].hwUnitId) );
            AppUtils_printf(  APP_NAME
                ": MCSPI_HL_REV 			: 0x%x\n", RegRbPtr->mcspiHlRev);
            AppUtils_printf(  APP_NAME
                ": MCSPI_HL_HWINFO 		: 0x%x\n", RegRbPtr->mcspiHlHwInfo);
            AppUtils_printf(  APP_NAME
                ": MCSPI_HL_SYSCONFIG 		: 0x%x\n", RegRbPtr->mcspiHlSysConfig);
            AppUtils_printf(  APP_NAME
                ": MCSPI_REVISION 			: 0x%x\n", RegRbPtr->mcspiRev);
            AppUtils_printf(  APP_NAME
                ": MCSPI_SYSSTATUS 		: 0x%x\n", RegRbPtr->mcspiSysStatus);
            AppUtils_printf(  APP_NAME
                ": MCSPI_SYST 			: 0x%x\n", RegRbPtr->mcspiSyst);
            AppUtils_printf(  APP_NAME
                ": MCSPI_MODULCTRL 		: 0x%x\n", RegRbPtr->mcspiModulctrl);
            AppUtils_printf(  APP_NAME
                ": MCSPI_SYSCONFIG 		: 0x%x\n", RegRbPtr->mcspiSysConfig);
            AppUtils_printf(  APP_NAME
                ": MCSPI_CH0CONF 			: 0x%x\n", RegRbPtr->mcspiCh0config);
            AppUtils_printf(  APP_NAME
                ": MCSPI_CH1CONF 			: 0x%x\n", RegRbPtr->mcspiCh1config);
            AppUtils_printf(  APP_NAME
                ": MCSPI_CH2CONF 			: 0x%x\n", RegRbPtr->mcspiCh2config);
            AppUtils_printf(  APP_NAME
                ": MCSPI_CH3CONF 			: 0x%x\n", RegRbPtr->mcspiCh3config);
            AppUtils_printf(  APP_NAME
                ": MCSPI_IRQENABLE 		: 0x%x\n", RegRbPtr->mcspiIrqenable); */
        }
    }
#endif
#if ((SPI_CHANNELBUFFERS == SPI_IB_EB) || (SPI_CHANNELBUFFERS == SPI_IB))
    for (chIndex = 0U; chIndex < cfgPtr->maxChannels; chIndex++)
    {
        if (SPI_IB == cfgPtr->channelCfg[chIndex].channelBufType)
        {
            Spi_DataBufferType *destDataBuf;

            /* Read RX data from IB to app buffer */
            destDataBuf = (Spi_DataBufferType *)&gMcspiRxBuffer[chIndex][0U];
            chId        = Spi_ChannelConfig_PC[chIndex].channelId;
            retVal      = Spi_ReadIB(chId, destDataBuf);
            if (retVal != E_OK)
            {
                testPassed = E_NOT_OK;
                AppUtils_printf(APP_NAME ": SPI Read IB Failed!!\n\r");
            }
        }
    }
#endif

/* Cache Invalidation for all channel buffers in every job using DMA Enabled HwUnit ID */
#if (STD_ON == SPI_DMA_ENABLE)
    for (index = 0; index < cfgPtr->maxJobs; index++)
    {
        if (TRUE == cfgPtr->hwUnitCfg[cfgPtr->jobCfg[index].hwUnitId].enableDmaMode)
        {
            for (chIndex = 0; chIndex < cfgPtr->jobCfg[index].channelPerJob; chIndex++)
            {
                Mcal_CacheP_inv(&gMcspiRxBuffer[cfgPtr->jobCfg[index].channelList[chIndex]], RX_TX_BUF_SIZE_WORD,
                                Mcal_CacheP_TYPE_ALLD);
            }
        }
    }
#endif

    /* Check RX buffer against TX buffer */
    matching = TRUE;
    for (chIndex = 0U; chIndex < cfgPtr->maxChannels; chIndex++)
    {
        tempTxPtr = (Spi_DataBufferType *)&gMcspiTxBuffer[chIndex][0U];
        tempRxPtr = (Spi_DataBufferType *)&gMcspiRxBuffer[chIndex][0U];
        for (index = 0U; index < byteLength[chIndex]; index++)
        {
            if (((Spi_DataBufferType)*tempTxPtr++) != ((Spi_DataBufferType)*tempRxPtr++))
            {
                matching = FALSE;
                break;
            }
        }
    }
    if (TRUE != matching)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf(APP_NAME ": McSPI data mismatch error!!\n\r");
    }

    if (testPassed == E_OK)
    {
        for (chIndex = 0U; chIndex < cfgPtr->maxChannels; chIndex++)
        {
            xferLength[chIndex] = SPI_APP_RX_TX_LENGTH;
        }
    }

    /* DeInit */
    retVal = Spi_DeInit();
    if (testPassed == E_OK)
    {
        if (retVal != E_OK)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf(APP_NAME ": SPI Deinit Failed!!\n\r");
        }
    }

    if (testPassed == E_OK)
    {
        /* SPI driver should be uninit now - check */
        status = Spi_GetStatus();
        if (status != SPI_UNINIT)
        {
            testPassed = E_NOT_OK;
            AppUtils_printf(APP_NAME ": SPI driver is not in uninit state!!\n\r");
        }
    }

    /* Deinit DMA, PORT and MCU */
    SpiApp_platformDeinit();

    if (E_OK == testPassed)
    {
        SpiApp_TestPassed = testPassed;
        AppUtils_printf(APP_NAME ": All tests have passed\n\r");
    }
    else
    {
        SpiApp_TestPassed = testPassed;
        AppUtils_printf(APP_NAME ": SPI Loopback Test Failed!!!\n\r");
    }
    GT_1trace(McalAppTrace, GT_INFO, "SPI Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        GT_0trace(McalAppTrace, GT_ERR, "SPI Stack/section corruption!!!\n\r");
    }

    return (SpiApp_TestPassed);
}

#if (STD_ON == APP_PERFORMANCE_MODE)
static void MCSPIExample_PerformanceTest()
{
    char                  option;
    boolean               quit_opt = 0;
    uint32                cntr_cnt;  //,mask = 0x00000000U;
    const Spi_ConfigType *Spi_ConfigPtr;
    Std_VersionInfoType   Spi_Version;
    Spi_DataBufferType   *srcDataBuf;
    Spi_DataBufferType   *destDataBuf;
    Spi_ConfigPtr = &SpiDriver;

    Start_Timer();
    Spi_GetVersionInfo(&Spi_Version);
    Stop_Timer(0);

    Start_Timer();
    Spi_Init(Spi_ConfigPtr);
    Stop_Timer(1);

    Start_Timer();
    Spi_GetJobResult(0U);
    Stop_Timer(2);

    Start_Timer();
    Spi_GetSequenceResult(0U);
    Stop_Timer(3);

    Start_Timer();
    Spi_GetHWUnitStatus(0U);
    Stop_Timer(4);

    srcDataBuf  = (Spi_DataBufferType *)&gMcspiTxBuffer[0][0U];
    destDataBuf = (Spi_DataBufferType *)&gMcspiRxBuffer[0][0U];

    Start_Timer();
    Spi_SetupEB(0, srcDataBuf, destDataBuf, 25);
    Stop_Timer(5);

    Start_Timer();
    Spi_WriteIB(3, srcDataBuf);
    Stop_Timer(6);

    Start_Timer();
    Spi_AsyncTransmit(0);
    Stop_Timer(7);

    Start_Timer();
    Spi_ReadIB(3, destDataBuf);
    Stop_Timer(8);

    Start_Timer();
    Spi_Cancel(0);
    Stop_Timer(10);

    Start_Timer();
    Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    Stop_Timer(11);

    Start_Timer();
    Spi_MainFunction_Handling();
    Stop_Timer(12);

    Start_Timer();
    Spi_DeInit();
    Stop_Timer(13);
}

#endif

// static void SpiApp_platformInit(void)
// {
// #if (STD_ON == PORT_SET_PIN_MODE_API)
//     uint16 uart_tx_pin, uart_rx_pin;
// #endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

// #if (STD_ON == MCU_VARIANT_PRE_COMPILE)
//         Mcu_Init((const Mcu_ConfigType *) NULL_PTR);
// #else
//         Mcu_Init(&McuModuleConfiguration);
// #endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

// #if (STD_ON == PORT_PRE_COMPILE_VARIANT)
//     Port_Init((const Port_ConfigType *) NULL_PTR);
// #else
//     Port_Init(&PortConfigSet_0);
// #endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

// #if (STD_ON == PORT_SET_PIN_MODE_API)
//     uart_tx_pin = 13;
//     uart_rx_pin = 14;

//     /* Set up the pinmux for UART tx */
//     Port_SetPinMode(uart_tx_pin, PORT_PIN_MODE_LIN0);

//     /* Set up the pinmux for UART rx */
//     Port_SetPinMode(uart_rx_pin, PORT_PIN_MODE_LIN0);
// #endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/
// #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )
//     Port_SetPinDirection(uart_rx_pin, PORT_PIN_IN);
// #endif /*    #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
//     Enable_Uart();

//     return;
// }

static void SpiApp_platformDeinit(void)
{
#if (STD_ON == SPI_DMA_ENABLE)
    Cdd_Dma_DeInit();
#endif
    Port_DeInit();
    Mcu_DeInit();
}

void SpiApp_McspiJob0EndNotification(void)
{
    SpiApp_McspiJobDone[0U] = TRUE;

    return;
}

void SpiApp_McspiSeq0EndNotification(void)
{
    SpiApp_McspiSeqDone[0U] = TRUE;

    return;
}

void SpiApp_McspiJob1EndNotification(void)
{
    SpiApp_McspiJobDone[1U] = TRUE;

    return;
}

void SpiApp_McspiJob2EndNotification(void)
{
    SpiApp_McspiJobDone[2U] = TRUE;

    return;
}

void SpiApp_McspiJob3EndNotification(void)
{
    SpiApp_McspiJobDone[3U] = TRUE;

    return;
}

void SpiApp_McspiSeq1EndNotification(void)
{
    SpiApp_McspiSeqDone[1U] = TRUE;

    return;
}

void SpiApp_McspiSeq2EndNotification(void)
{
    SpiApp_McspiSeqDone[2U] = TRUE;

    return;
}

void SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}
void SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

#if (defined CLANG) || (defined DIAB)
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

#if (STD_ON == SPI_DMA_ENABLE)
void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif
