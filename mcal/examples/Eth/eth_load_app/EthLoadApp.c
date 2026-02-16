/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file     EthLoadApp.c
 *
 *  \brief    This file contains the Eth load test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FreeRTOS.h>
#include <task.h>

#include <kernel/dpl/HwiP.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/SemaphoreP.h>
#include <kernel/dpl/TaskP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/TimerP.h>
#include <kernel/freertos/dpl/common/ClockP_freertos_priv.h>

#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

#include "Eth.h"
#include "Eth_Irq.h"

#include "app_utils.h"
#include "EthApp_Startup.h"

#include "EthLoadUtils.h"
#include "os_wrapper.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ETHAPP_TASK_HIGH_PRI (configMAX_PRIORITIES - 1U)

#define ETHAPP_TASK_DEFAULT_PRI (configMAX_PRIORITIES - 10U)

#define ETHAPP_TASK_DEFAULT_STACK_SIZE (8192U)

#define ETHAPP_TEST_SIZE_MEASURE (5U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef struct EthApp_TaskCfgType_s
{
    const char   *name;
    uint8         priority;
    uint32        stackSize;
    uint8        *stackMem;
    void         *handle;
    TaskP_FxnMain entry;
} EthApp_TaskCfgType;

typedef enum EthApp_TestType_e
{
    ETHAPP_TEST_TX  = 0u,
    ETHAPP_TEST_RX  = 1u,
    ETHAPP_TEST_NUM = 2u,
} EthApp_TestType;

typedef struct EthApp_TestResultType_s
{
    uint32 cpuload;
    uint32 irqLoad;
    uint32 pps;
    uint32 mbps;
} EthApp_TestResultType;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief Measure DUT transmit throughput
 *
 * Measure DUT transmit throughput over "frames" frames with frame size is "size"
 * . The target performs the following operations:
 * - Get the initial timestamp corresponding to the first frame received
 * - Receive frames until the STOP is detected and get the final timestamp
 * - Compute the transmit throughput from the number of received frames and the
 *   time difference between the two captured timestamps
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0100(uint32 frames, uint32 size);

/* Rx task main function, to polling RX data if RX IRQ is disabled */
#if (STD_OFF == ETH_ENABLE_RX_INTERRUPT)
void EthApp_rxTask(void *args1);
#endif

/* Test task main function */
void EthApp_testTask(void *args1);

/* Monitor task main function */
void EthApp_monTask(void *args1);

/* Init task main function */
void EthApp_initTask(void *args1);

void EthApp_printMACAddr(uint8 macAddr[]);

static void EthApp_interruptConfigCustom(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Eth application state */
EthUtilsApp_State gEthUtilsApp;

volatile boolean isRunning = TRUE;
/* TaskP_load doesn't account for interrupt process time, use timer counter to get load with
 * interrupt */
uint64           totalIrqClock = 0;
uint64           totalTxClock  = 0;

static SemaphoreP_Object gInitDoneSem;  /* Eth init done flag */
static SemaphoreP_Object gStartTestSem; /* Flag to start test */
static SemaphoreP_Object gStatsSem;     /* Flag to print test status */
static SemaphoreP_Object gBucketSem;    /* TX buffer processed interrupt flag */
static SemaphoreP_Object gTestDoneSem;  /* RX test done flag */

#if (STD_OFF == ETH_ENABLE_RX_INTERRUPT)
volatile uint32          rxPollingTime = 50u;
static SemaphoreP_Object gRxSem;
StackType_t              gMainRxTaskStack[ETHAPP_TASK_DEFAULT_STACK_SIZE] __attribute__((aligned(32)));
#endif
StackType_t gMainTestTaskStack[ETHAPP_TASK_DEFAULT_STACK_SIZE] __attribute__((aligned(32)));
StackType_t gMainMonTaskStack[ETHAPP_TASK_DEFAULT_STACK_SIZE] __attribute__((aligned(32)));
StackType_t gMainInitTaskStack[ETHAPP_TASK_DEFAULT_STACK_SIZE] __attribute__((aligned(32)));

EthApp_TaskCfgType EthApp_taskCfg[] = {
    /* First item must be test task to get correct cpu load */
    {"TEST", ETHAPP_TASK_DEFAULT_PRI - 2, ETHAPP_TASK_DEFAULT_STACK_SIZE, (uint8 *)gMainTestTaskStack, NULL_PTR,
     &EthApp_testTask},
#if (STD_OFF == ETH_ENABLE_RX_INTERRUPT)
    {"RX", ETHAPP_TASK_DEFAULT_PRI - 1, ETHAPP_TASK_DEFAULT_STACK_SIZE, (uint8 *)gMainRxTaskStack, NULL_PTR,
     &EthApp_rxTask},
#endif
    {"MON", ETHAPP_TASK_DEFAULT_PRI, ETHAPP_TASK_DEFAULT_STACK_SIZE, (uint8 *)gMainMonTaskStack, NULL_PTR,
     &EthApp_monTask},
    {"INIT", ETHAPP_TASK_HIGH_PRI, /* need to be highest */
     ETHAPP_TASK_DEFAULT_STACK_SIZE, (uint8 *)gMainInitTaskStack, NULL_PTR, &EthApp_initTask}};

/* Test measurement data */
uint16 gTxPktSizeMesure[] = {1500u, 512u, 256u, 128u, 64u};
uint32 gTxIteratorNum[]   = {640000u, 1280000u, 1280000u, 1280000u, 1280000u};
uint32 gTxNumTest         = sizeof(gTxPktSizeMesure) / sizeof(uint16);

uint16 gRxPktSizeMesure[] = {1500u, 512u, 256u, 128u, 64u};
uint32 gRxIteratorNum[]   = {640000u, 1280000u, 2560000u, 3072000u, 2560000u};
uint32 gRxNumTest         = sizeof(gRxPktSizeMesure) / sizeof(uint16);

TickType_t gStartTestTick = 0u;
TickType_t gEndTestTick   = 0u;

EthApp_TestType gTestType  = ETHAPP_TEST_TX;
uint16          gTxTestIdx = 0u;
uint16          gRxTestIdx = 0u;

EthApp_TestResultType gTxTestResult[ETHAPP_TEST_SIZE_MEASURE];
EthApp_TestResultType gRxTestResult[ETHAPP_TEST_SIZE_MEASURE];

EthTrcv_BaudRateType gTestSpeed = ETHTRCV_BAUD_RATE_1000MBIT; /* default is 1Gpbs */

volatile sint32 gBucketCount;

uintptr_t hwi_irq_state;

/* OS interrupt object */
HwiP_Object hwiObj_TxIrq;
HwiP_Object hwiObj_RxIrq;
HwiP_Object hwiObj_RxThreshIrq;
HwiP_Object hwiObj_MiscIrq;

/* Broadcast MAC address */
const uint8 BcastAddr[ETH_HW_ADDR_LEN] = {0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static uint64 EthApp_getCurrentTaskClock(void)
{
    uint64 ts = 0U;
    uint32 timerCount;
    uint64 ticks1;
    uint64 ticks2;

    do
    {
        ticks1     = gClockCtrl.ticks;
        timerCount = ClockP_getTimerCount(gClockCtrl.timerBaseAddr);
        ticks2     = gClockCtrl.ticks;
    } while (ticks1 != ticks2); /* loop reading to timerCount synced with gClockCtrl.ticks*/

    /* Get the current time in clock count */
    ts  = (ticks2 * (uint64)(MAX_TIMER_COUNT_VALUE - gClockCtrl.timerReloadCount));
    ts += (uint64)(timerCount - gClockCtrl.timerReloadCount);

    return (ts);
}

static uint64 EthApp_getElapsedTaskClock(uint64 startClock)
{
    return EthApp_getCurrentTaskClock() - startClock;
}

static uint32 EthApp_getClockCount(void)
{
    return TimerP_getCount(gClockConfig.timerBaseAddr);
}

static uint32 EthApp_getElapsedClock(uint32 startClock)
{
    uint32 elapsedClock = 0;
    uint32 endClock     = EthApp_getClockCount();

    if (endClock >= startClock)
    {
        elapsedClock = endClock - startClock;
    }
    else /* overflow. timerP count from start to MAX_TIMER_COUNT_VALUE then from reload to end */
    {
        elapsedClock  = MAX_TIMER_COUNT_VALUE - startClock;
        elapsedClock += endClock - gClockCtrl.timerReloadCount;
    }

    return elapsedClock;
}

uint32 EthApp_getLoadWithClock(uint64 timeClock)
{
    uint64 time           = 0;
    uint32 timeLoad       = 0;
    uint32 testDurationMs = gEndTestTick - gStartTestTick;

    time = timeClock * gClockConfig.timerInputPreScaler;

    /* test duration unit is millisecond, convert time to 0.01 millisecond to get percent later */
    time = time / (gClockConfig.timerInputClkHz / 100000u);

    timeLoad = time / testDurationMs;

    if (timeLoad > 100)
    {
        timeLoad = 100;
    }

    return timeLoad;
}

/* Reduce test packet number by speed */
static inline uint8 EthApp_GetScaleValue(void)
{
    uint8 scale = 1;
    switch (gTestSpeed)
    {
        case ETHTRCV_BAUD_RATE_10MBIT:
            scale = 20u;
            break;
        case ETHTRCV_BAUD_RATE_100MBIT:
            scale = 5u;
            break;
        case ETHTRCV_BAUD_RATE_1000MBIT:
            scale = 1u;
            break;
        default:
            break;
    }

    return scale;
}

static void EthApp_TxIrqHdlr_0_wrapper(void *arg)
{
    uint32 start;

    /* Get start irq time then process */
    start = EthApp_getClockCount();

    Eth_TxIrqHdlr_0();

    /* accumulate irq process time */
    totalIrqClock += EthApp_getElapsedClock(start);

    SemaphoreP_post(&gBucketSem);
}

#if (STD_ON == ETH_ENABLE_RX_INTERRUPT)
static void EthApp_RxIrqHdlr_0_wrapper(void *arg)
{
    uint32 start;

    /* Get start irq time then process */
    start = EthApp_getClockCount();

    Eth_RxIrqHdlr_0();

    /* accumulate irq process time */
    totalIrqClock += EthApp_getElapsedClock(start);
}

static void EthApp_RxThreshIrqHdlr_0_wrapper(void *arg)
{
    uint32 start;

    /* Get start irq time then process */
    start = EthApp_getClockCount();

    Eth_RxThreshIrqHdlr_0();

    /* accumulate irq process time */
    totalIrqClock += EthApp_getElapsedClock(start);
}
#endif /* STD_ON == ETH_ENABLE_RX_INTERRUPT */

static void EthApp_interruptConfigCustom(void)
{
    int32_t     status = SystemP_SUCCESS;
    HwiP_Params hwiPrms;

/* Register interrupt */
#if (STD_ON == ETH_ENABLE_TX_INTERRUPT)
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CPSW_FH_INT;
    hwiPrms.callback = (void *)&EthApp_TxIrqHdlr_0_wrapper;
    hwiPrms.isPulse  = 1;
    hwiPrms.priority = 3u;
    status           = HwiP_construct(&hwiObj_TxIrq, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);
#endif

#if (STD_ON == ETH_ENABLE_RX_INTERRUPT)
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CPSW_TH_INT;
    hwiPrms.callback = (void *)&EthApp_RxIrqHdlr_0_wrapper;
    hwiPrms.isPulse  = 1;
    hwiPrms.priority = 3u;
    status           = HwiP_construct(&hwiObj_RxIrq, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);

    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CPSW_TH_TRSH_INT;
    hwiPrms.callback = (void *)&EthApp_RxThreshIrqHdlr_0_wrapper;
    hwiPrms.isPulse  = 1;
    hwiPrms.priority = 3u;
    status           = HwiP_construct(&hwiObj_RxThreshIrq, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);
#endif

#if (STD_ON == ETH_USR_MDIO_INTERRUPT)
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = CPSW_MISC_INT;
    hwiPrms.callback = (void *)&Eth_MiscIrqHdlr_0;
    hwiPrms.isPulse  = 1;
    hwiPrms.priority = 3u;
    status           = HwiP_construct(&hwiObj_MiscIrq, &hwiPrms);
    DebugP_assert(status == SystemP_SUCCESS);
#endif
}

boolean EthApp_test_0100(uint32 frames, uint32 size)
{
    Eth_BufIdxType    bufIdx;
    boolean           txConfirmation = TRUE;
    uint8            *bufPtr;
    uint16            len       = size;
    uint8             priority  = 0U;
    BufReq_ReturnType bufStatus = BUFREQ_E_NOT_OK;
    uint64            start;
    TickType_t        currentTick = 0U;
    uint32            irqPerMs    = 0U;

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);
    vTaskDelay(100); /* Add delay to make sure host received STOP command */

    /* Most of TX process start from here until suspend */
    start = EthApp_getCurrentTaskClock();

    /* Request and transmit one buffer, polling semaphore from TX IRQ if not available */
    while (frames > 0)
    {
        bufStatus = Eth_ProvideTxBuffer(gEthUtilsApp.ctrlIdx, priority, &bufIdx, &bufPtr, &len);

        if (BUFREQ_OK == bufStatus)
        {
            (void)Eth_Transmit(gEthUtilsApp.ctrlIdx, bufIdx, (Eth_FrameType)ETHERTYPE_EXPERIMENTAL3, txConfirmation,
                               len, BcastAddr);
            frames--;
        }
        else
        {
            /* Check if irq reach threshold then keep polling Eth_ProvideTxBuffer
               to send faster, this will increase CPU load */
            if (irqPerMs < Eth_Config.cpdmaCfg.txInterruptsPerMsec)
            {
                /* accumulate irq process time before polling IRQ */
                totalTxClock += EthApp_getElapsedTaskClock(start);
                SemaphoreP_pend(&gBucketSem, SystemP_WAIT_FOREVER);
                irqPerMs++;
                currentTick = xTaskGetTickCount();

                /* resume TX process */
                start = EthApp_getCurrentTaskClock();
            }
            else
            {
                /* FreeRTOS with Tick duration = 1ms, reset irqPerMs every Tick change */
                if (currentTick != xTaskGetTickCount())
                {
                    irqPerMs = 0;
                }
                else
                {
                    /* keep polling Eth_ProvideTxBuffer */
                }
            }
        }
    };

    /* accumulate last TX process time */
    totalTxClock += EthApp_getElapsedTaskClock(start);

    /* Last TX buffer filled, get end test time here to exclude delay to send multi STOP command */
    vTaskDelay(100);
    gEndTestTick = xTaskGetTickCount();

    /* Send multiple STOP cmd to make sure host can receive STOP command */
    for (start = 0; start < 10u; start++)
    {
        vTaskDelay(100);
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_STOP);
    }
    return PASS;
}

void EthApp_receiveTput(uint32 frames, uint16 pktLen, uint32 *pps, uint32 *mbps)
{
    float32 elapsed;
    uint32  framesOk;
    uint64  byteCnt;

    elapsed = (float32)(gEndTestTick - gStartTestTick) / 1000;

    framesOk = gEthUtilsApp.stats.rxExp3PktCnt;
    byteCnt  = gEthUtilsApp.stats.rxExp3BytesCnt;

    /* Compute elapsed time, packets per second and Mbps */
    *pps  = (uint32)framesOk / elapsed;
    *mbps = (uint32)((byteCnt * 8) / (elapsed * 1000000));
}

void EthApp_transmitTput(uint32 frames, uint16 pktLen, uint32 *pps, uint32 *mbps)
{
    float32 elapsed;
    uint32  framesOk;
    uint64  byteCnt;

    elapsed = (float32)(gEndTestTick - gStartTestTick) / 1000;

    framesOk = gEthUtilsApp.stats.txConfPktCnt;
    byteCnt  = (uint64)(gEthUtilsApp.stats.txConfPktCnt * (pktLen + 14u));

    /* Compute elapsed time, packets per second and Mbps */
    *pps  = (uint32)framesOk / elapsed;
    *mbps = (uint32)((byteCnt * 8) / (elapsed * 1000000));
}

void EthApp_monShowStats()
{
    if (gTestType == ETHAPP_TEST_TX)
    {
        gTxTestResult[gTxTestIdx].irqLoad = EthApp_getLoadWithClock(totalIrqClock);
        // gTxTestResult[gTxTestIdx].cpuload = OsUtils_getCpuload(EthApp_taskCfg[0u].handle) +
        // gTxTestResult[gTxTestIdx].irqLoad; gTxTestResult[gTxTestIdx].cpuload =
        // TaskP_loadGetTotalCpuLoad()/100 + gRxTestResult[gRxTestIdx].irqLoad;
        gTxTestResult[gTxTestIdx].cpuload = EthApp_getLoadWithClock(totalIrqClock + totalTxClock);
        EthApp_transmitTput(gTxIteratorNum[gTxTestIdx] / EthApp_GetScaleValue(), gTxPktSizeMesure[gTxTestIdx],
                            &gTxTestResult[gTxTestIdx].pps, &gTxTestResult[gTxTestIdx].mbps);

        DebugP_log("Tx throughput test size %4d Done in %2ds load %d (irqLoad %d)\r\n", gTxPktSizeMesure[gTxTestIdx],
                   (gEndTestTick - gStartTestTick) / 1000, gTxTestResult[gTxTestIdx].cpuload,
                   gTxTestResult[gTxTestIdx].irqLoad);
    }
    else
    {
        gRxTestResult[gRxTestIdx].irqLoad = EthApp_getLoadWithClock(totalIrqClock);
        /* most RX process in IRQ, TaskP_loadGetTotalCpuLoad() will return 0*/
        gRxTestResult[gRxTestIdx].cpuload = gRxTestResult[gRxTestIdx].irqLoad;
        EthApp_receiveTput(gRxIteratorNum[gRxTestIdx] / EthApp_GetScaleValue(), gRxPktSizeMesure[gRxTestIdx],
                           &gRxTestResult[gRxTestIdx].pps, &gRxTestResult[gRxTestIdx].mbps);

        DebugP_log("Rx throughput test size %4d Done in %2ds load %d (irqLoad %d)\r\n", gRxPktSizeMesure[gRxTestIdx],
                   (gEndTestTick - gStartTestTick) / 1000, gRxTestResult[gRxTestIdx].cpuload,
                   gRxTestResult[gRxTestIdx].irqLoad);
    }
}

void EthApp_TestFunc(uint8 testType, uint8 testId)
{
    gTestType = (EthApp_TestType)testType;

    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_READY);
    vTaskDelay(100); /* Add delay to make sure host received READY command */

    gStartTestTick = xTaskGetTickCount();
    totalIrqClock  = 0;
    totalTxClock   = 0;

    if (gTestType == ETHAPP_TEST_TX)
    {
        gEthUtilsApp.runTest            = TRUE;
        gEthUtilsApp.stats.txConfPktCnt = 0u;
        gTxTestIdx                      = testId;
        (void)EthApp_test_0100(gTxIteratorNum[gTxTestIdx] / EthApp_GetScaleValue(), gTxPktSizeMesure[gTxTestIdx]);
    }
    else
    {
        // gEthUtilsApp.runTest = TRUE;
        gEthUtilsApp.stats.rxPktCnt       = 0u;
        gEthUtilsApp.stats.rxExp3PktCnt   = 0u;
        gEthUtilsApp.stats.rxExp3BytesCnt = 0u;
        gRxTestIdx                        = testId;

        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);
        /* Host load app send multiple stop packet, wait a small time before update runTest flag */
        vTaskDelay(1000);
        gEthUtilsApp.runTest = TRUE;

        /* wait rx test done */
        SemaphoreP_pend(gEthUtilsApp.testDoneNotifySem, SystemP_WAIT_FOREVER);
        /* Get RX end test time */
        gEndTestTick = xTaskGetTickCount();
    }

    SemaphoreP_post(&gStatsSem);
}

void EthApp_TestFuncAll()
{
    uint8 testType;
    uint8 testId;
    for (testType = 0u; testType < ETHAPP_TEST_NUM; ++testType)
    {
#if (STD_OFF == ETH_ENABLE_RX_INTERRUPT)
        if (testType == ETHAPP_TEST_RX)
        {
            rxPollingTime = 1u;
            SemaphoreP_post(&gRxSem);
            vTaskDelay(100);
        }
#endif

        for (testId = 0u; testId < ETHAPP_TEST_SIZE_MEASURE; ++testId)
        {
            SemaphoreP_pend(&gStartTestSem, SystemP_WAIT_FOREVER);

            EthApp_TestFunc(testType, testId);
        }
    }
}

void EthApp_testTask(void *args1)
{
    SemaphoreP_pend(&gInitDoneSem, SystemP_WAIT_FOREVER);

    EthApp_TestFuncAll();

    isRunning = FALSE;
    SemaphoreP_post(&gStatsSem);

    vTaskDelay(portMAX_DELAY);
    vTaskDelete(NULL_PTR);
    (void)args1;
}

#if (STD_OFF == ETH_ENABLE_RX_INTERRUPT)
void EthApp_rxTask(void *args1)
{
    Eth_RxStatusType rxStatus = ETH_NOT_RECEIVED;
    for (;;)
    {
        SemaphoreP_pend(&gRxSem, rxPollingTime);
        if (isRunning == FALSE)
        {
            break;
        }
        rxStatus = ETH_RECEIVED_MORE_DATA_AVAILABLE;
        while (rxStatus == ETH_RECEIVED_MORE_DATA_AVAILABLE)
        {
            Eth_Receive(0u, 0u, &rxStatus);
        }
    }

    vTaskDelay(portMAX_DELAY);
    vTaskDelete(NULL_PTR);
    (void)args1;
}
#endif

void EthApp_monTask(void *args1)
{
    uint8 idx;

    for (;;)
    {
        SemaphoreP_pend(&gStatsSem, SystemP_WAIT_FOREVER);
        if (isRunning == FALSE)
        {
            break;
        }
        EthApp_monShowStats();

        SemaphoreP_post(&gStartTestSem);
    }

    /* Show test result */
    DebugP_log("Performance result - %s link\r\n",
               (gTestSpeed == 0U) ? "10Mbps" : ((gTestSpeed == 1U) ? "100Mbps" : "1Gbps"));
    DebugP_log("----------------------------------------------------------------------\r\n");
    DebugP_log("|Pkt Size | TX throughput(Mbps) | TX packet rate(Pps) | Cpu load(%%) |\r\n");
    DebugP_log("---------------------------------------------------------------------\r\n");

    for (idx = 0u; idx < ETHAPP_TEST_SIZE_MEASURE; ++idx)
    {
        DebugP_log("|%8d |%20d |%20d |%12d |\r\n", gTxPktSizeMesure[idx], gTxTestResult[idx].mbps,
                   gTxTestResult[idx].pps, gTxTestResult[idx].cpuload);
        DebugP_log("---------------------------------------------------------------------\r\n");
    }

    DebugP_log("----------------------------------------------------------------------\r\n");
    DebugP_log("|Pkt Size | RX throughput(Mbps) | RX packet rate(Pps) | Cpu load(%%) |\r\n");
    DebugP_log("---------------------------------------------------------------------\r\n");

    for (idx = 0u; idx < ETHAPP_TEST_SIZE_MEASURE; ++idx)
    {
        DebugP_log("|%8d |%20d |%20d |%12d |\r\n", gRxPktSizeMesure[idx], gRxTestResult[idx].mbps,
                   gRxTestResult[idx].pps, gRxTestResult[idx].cpuload);
        DebugP_log("---------------------------------------------------------------------\r\n");
    }

    vTaskDelay(portMAX_DELAY);
    vTaskDelete(NULL_PTR);
    (void)args1;
}

void EthLoadApp_initEth(void)
{
    Std_ReturnType retVal = E_OK;

    VAR(Eth_ModeType, AUTOMATIC) Ethmode   = ETH_MODE_DOWN;
    uint8 TargetMcastAddr[ETH_HW_ADDR_LEN] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U};

    /* Print date and time */
    DebugP_log("\r\nEth Application build date/time: %s, %s\r\n", __DATE__, __TIME__);
    // DebugP_log("Eth Application Starts\r\n");

    /* Register custom IRQ for the app */
    EthApp_interruptConfigCustom();

    /* Do Eth driver initialization */
    Eth_ConfigType *pEthConfigPtr;
    pEthConfigPtr = &Eth_Config;

#if (STD_ON == ETH_VARIANT_PRE_COMPILE)
    Eth_Init((const Eth_ConfigType *)NULL_PTR);
#else
    Eth_Init(pEthConfigPtr);
#endif /*STD_ON == ETH_VARIANT_PRE_COMPILE)*/

    /* Initialiaze the ETH Transceiver */
    EthApp_TrcvInit();

    /* Set the Controller:0 in Active mode */
    retVal = Eth_SetControllerMode(pEthConfigPtr->ctrlIdx, ETH_MODE_ACTIVE);
    if ((Std_ReturnType)E_OK != retVal)
    {
        DebugP_log("Failed in Eth_SetControllerMode\r\n");
    }

    /* Get Back the Controller mode  */
    retVal = Eth_GetControllerMode(pEthConfigPtr->ctrlIdx, &Ethmode);
    if ((Std_ReturnType)E_OK != retVal)
    {
        DebugP_log("Failed in Eth_GetControllerMode\r\n");
    }

    /* Update MAC address from config */
    Eth_SetPhysAddr(pEthConfigPtr->ctrlIdx, pEthConfigPtr->portCfg.macCfg.macAddr);

    /* Get back the Mac address of the controller*/
    Eth_GetPhysAddr(pEthConfigPtr->ctrlIdx, gEthUtilsApp.macAddr);
    // DebugP_log("\r\nMAC Port %d Address:\r\n", pEthConfigPtr->portIdx);
    EthApp_printMACAddr(gEthUtilsApp.macAddr);

    /* Adding a Destination address to the filter */
    Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);

    /* Initialize the global app structure */
    gEthUtilsApp.ctrlIdx             = pEthConfigPtr->ctrlIdx;
    gEthUtilsApp.verbose             = FALSE;
    gEthUtilsApp.veryVerbose         = FALSE;
    gEthUtilsApp.txIrqDisable        = FALSE; /* default is using TX IRQ */
    gEthUtilsApp.rxIrqDisable        = FALSE; /* default is using RX IRQ */
    gEthUtilsApp.mdioIrqDisable      = FALSE; /* default is using MDIO IRQ */
    gEthUtilsApp.sendMultipleStopCmd = FALSE;
    gEthUtilsApp.testIdx             = 0xFF;  // ARRAY_SIZE(testFuncs);

#if (STD_OFF == ETH_ENABLE_TX_INTERRUPT)
    gEthUtilsApp.txIrqDisable = TRUE;
#endif

#if (STD_OFF == ETH_ENABLE_RX_INTERRUPT)
    gEthUtilsApp.rxIrqDisable = TRUE;
#endif

#if (STD_OFF == ETH_USR_MDIO_INTERRUPT)
    gEthUtilsApp.mdioIrqDisable = TRUE;
#endif

    memset(&gEthUtilsApp.stats, 0U, sizeof(EthUtilsApp_Stats));

    retVal = EthTrcv_GetBaudRate(0, &gTestSpeed);

    DebugP_log("Link Speed %s\r\n", (gTestSpeed == 0U) ? "10Mbps" : ((gTestSpeed == 1U) ? "100Mbps" : "1Gbps"));

    gBucketCount = ETH_NUM_TX_BUFFERS;

    /* Print Eth driver version and buffer config */
    AppUtils_ethPrintVersionInfo();

    Eth_CpdmaConfigType *pCpdmaCfg = &Eth_Config.cpdmaCfg;

    DebugP_log("RX_BUF=%d TX_BUF=%d\r\n", ETH_NUM_RX_BUFFERS, ETH_NUM_TX_BUFFERS);
    DebugP_log("RxPacing Enable=%d pacePerMs=%d Threshold=%d\r\n", pCpdmaCfg->rxInterruptPacingEnabled,
               pCpdmaCfg->rxInterruptsPerMsec, pCpdmaCfg->rxThreshCount);
    DebugP_log("TxPacing Enable=%d pacePerMs=%d\r\n", pCpdmaCfg->txInterruptPacingEnabled,
               pCpdmaCfg->txInterruptsPerMsec);
}

void EthLoadApp_initOs(void)
{
    uint8 taskIdx;

#if (STD_OFF == ETH_ENABLE_RX_INTERRUPT)
    SemaphoreP_constructBinary(&gRxSem, 0);
#endif
    SemaphoreP_constructBinary(&gBucketSem, 0);
    SemaphoreP_constructBinary(&gTestDoneSem, 0);
    gEthUtilsApp.testDoneNotifySem = (void *)&gTestDoneSem;
    SemaphoreP_constructBinary(&gStatsSem, 0);
    SemaphoreP_constructBinary(&gInitDoneSem, 0);
    SemaphoreP_constructBinary(&gStartTestSem, 0);

    OsUtils_init();
    for (taskIdx = 0u; taskIdx < sizeof(EthApp_taskCfg) / sizeof(EthApp_TaskCfgType); ++taskIdx)
    {
        EthApp_taskCfg[taskIdx].handle = OsUtils_createTask(
            EthApp_taskCfg[taskIdx].name, EthApp_taskCfg[taskIdx].priority, EthApp_taskCfg[taskIdx].stackSize,
            EthApp_taskCfg[taskIdx].stackMem, EthApp_taskCfg[taskIdx].entry);
        configASSERT(EthApp_taskCfg[taskIdx].handle != NULL_PTR);
    }
}

void EthApp_initTask(void *args1)
{
    /* Open drivers to open the UART driver for console */
    Drivers_open();
    Board_driversOpen();

    EthApp_Startup();
    EthLoadApp_initEth();

    SemaphoreP_post(&gInitDoneSem);
    SemaphoreP_post(&gStartTestSem);
    // Board_driversClose();
    // Drivers_close();

    vTaskDelay(portMAX_DELAY);
    vTaskDelete(NULL_PTR);
    (void)args1;
}

int main(void)
{
    /* init SOC specific modules */
    System_init();
    Board_init();

    EthLoadApp_initOs();

    /* Start the scheduler to start the tasks executing. */
    vTaskStartScheduler();

    /* The following line should never be reached because vTaskStartScheduler()
    will only return if there was not enough FreeRTOS heap memory available to
    create the Idle and (if configured) Timer tasks.  Heap management, and
    techniques for trapping heap exhaustion, are described in the book text. */
    DebugP_assertNoLog(0);

    return 0;
}

void EthApp_printMACAddr(uint8 macAddr[])
{
    DebugP_log("\n\r%02x:%02x:%02x:%02x:%02x:%02x\r\n", macAddr[0U], macAddr[1U], macAddr[2U], macAddr[3U], macAddr[4U],
               macAddr[5U]);
}

void EthIf_CtrlModeIndication(uint8 ControllerId, Eth_ModeType ControllerMode)
{
    /* not used for load test */
}

void EthIf_TrcvModeIndication(uint8 CtrlIdx, EthTrcv_ModeType TrcvMode)
{
    /* not used for load test */
}

void EthIf_RxIndication(uint8 ctrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, uint8 *PhysAddrPtr,
                        Eth_DataType *DataPtr, uint16 lenByte)
{
    EthLoadUtils_RxIndication(ctrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, lenByte);
}

void EthIf_TxConfirmation(uint8 CtrlIdx, Eth_BufIdxType bufIdx, Std_ReturnType Result)
{
    EthLoadUtils_TxConfirmation(CtrlIdx, bufIdx, Result);
}
