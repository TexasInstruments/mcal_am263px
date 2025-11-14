/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     EthApp.c
 *
 *  \brief    This file contains the Eth test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdlib.h"
#include "string.h"
#include "Std_Types.h"
#include "hw_types.h"
#include "Det.h"
#include "Dem.h"
#include "Eth.h"
#include "Eth_Irq.h"
#include "Eth_GeneralTypes.h"
#include "Eth_Cfg.h"
#include "EthIf_Cbk.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "EthTrcv.h"

/* Starterware Includes */
#include "hw_ctrl_core.h"
#include "sys_vim.h"
#include "app_utils.h"
#include "trace.h"
#include "EthApp.h"
#include "EthApp_Startup.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_NAME "ETH_APP"

#define FAIL_MESSAGE AppUtils_printf("\r\nFailed in %s \n", __func__)
#define htons(a)     ((((a) >> 8) & 0xffU) + (((a) << 8) & 0xff00U))
#define htonl(a)                                                                             \
    ((((a) & 0xff000000U) >> 24) | (((a) & 0x00ff0000U) >> 8) | (((a) & 0x0000ff00U) << 8) | \
     (((a) & 0x000000ffU) << 24))

#define ntohl(a) (htonl(a))
#define ntohs(a) (htons(a))
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

typedef void (*EthExampleFxn_t)(void);
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)
static void EthApp_TimeStampTest(Eth_ConfigType *pEthConfigPtr);
#endif /* (ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)*/
#if (STD_ON == ETHAPP_FILTER_TEST)
static void EthApp_FilterTest(Eth_ConfigType *pEthConfigPtr);
#endif /*(STD_ON == ETHAPP_FILTER_TEST) */

static void           EthApp_RxTxTest(void);
static void           EthApp_ReceivePacketTest(Eth_ConfigType *pEthConfigPtr);
static void           EthApp_TransmitPacketTest(Eth_ConfigType *pEthConfigPtr);
void                  EthExample_TransmitStress(void);
void                  EthApp_printMACAddr(uint8 macAddr[]);
static Std_ReturnType EthApp_showStats(uint8 ctrlIdx);

uint32 frc;
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

App_State                   gAppObj;
volatile uint32             gTestPassed                  = E_OK;
volatile uint32             gStopTestFlag                = FALSE;
volatile uint32             gEthcontrollerModeChangeFlag = FALSE;
uint8                       gTestMacAddr[ETH_MAC_ADDR_LEN];
uint8                       MainFunc_Execution;
float32                     ExecutimeTime;
static sint32               i2        = 0U;
volatile uint32             gLoopCntr = 1U;
extern const Mcu_ConfigType Mcu_Config;
uint8                       _gDstBuff[MAX_BUFFER_SIZE] __attribute__((aligned(128), section(".bss")));

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
volatile uint32 tsyncGetTsStress                      = 0;
volatile uint32 tsyncXmitStress                       = 0;
uint32          gTimeStampEnabled[ETH_NUM_TX_BUFFERS] = {FALSE};

char *timeStampQualString[3] = {"ETH_VALID", "ETH_INVALID", "ETH_UNCERTAIN"};

char *msgTypeString[15] = {
    "CPTS_MESSAGE_SYNC",
    "CPTS_MESSAGE_DELAY_REQ",
    "CPTS_MESSAGE_PDELAY_REQ",
    "CPTS_MESSAGE_PDELAY_RESP",
    "4",
    "5",
    "6",
    "7",
    "CPTS_MESSAGE_FOLLOW_UP",
    "CPTS_MESSAGE_DELAY_RESP",
    "CPTS_MESSAGE_PDELAY_RESP_FOLLOW_UP",
    "CPTS_MESSAGE_ANNOUNCE",
    "CPTS_MESSAGE_SIGNALING",
    "CPTS_MESSAGE_MANAGEMENT",
    "CPTS_MESSAGE_INVALID",
};
#endif /* (ETH_GLOBALTIMESUPPORT_API == STD_ON)*/

char *ethRcvStatusString[3] = {
    "ETH_RECEIVED",
    "ETH_NOT_RECEIVED",
    "ETH_RECEIVED_MORE_DATA_AVAILABLE",
};

Eth_MdioConfigType gMdioCfg = {.mdioBusFreq = 22000000U, .mdioClockFreq = 200000000U};

Eth_CpdmaConfigType gCpdmaCfg = {.pacingClkFreq            = 125000000U,
                                 .rxInterruptPacingEnabled = (uint32)TRUE,
                                 .rxInterruptsPerMsec      = 2U,
                                 .txInterruptPacingEnabled = (uint32)TRUE,
                                 .txInterruptsPerMsec      = 2U,
                                 .dmaModeFlags             = 0U,
                                 .rxThreshCount            = 0x0F};

Eth_CptsConfigType gCptsCfg = {
    /* 200U MHz */
    .cptsInputFreq = 200000000UL,
    .vlanType      = ETH_CPTS_VLAN_TYPE_SINGLE_TAG,
    .msgTypeCfg    = ETH_CPTS_MESSAGE_ALL};

uint8 gUniCstAddr[ETH_MAC_ADDR_LEN]   = {0x18, 0x03, 0x73, 0xb2, 0xcc, 0x01};
uint8 gBCstMacAddr[ETH_MAC_ADDR_LEN]  = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 gPtpMcastAddr[ETH_MAC_ADDR_LEN] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E};

static VAR(uint8, AUTOMATIC) MacDest[6];
P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) gPhysAddrPtr = MacDest;

static VAR(Eth_ModeType, AUTOMATIC) Ethmode                = ETH_MODE_DOWN;
P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) gCtrlModePtr = &Ethmode;

EthExampleFxn_t EthExampleFxnTbl[] = {
    EthApp_RxTxTest,
};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** @fn void main(void)
 *   @brief Application main function
 *   @note This function is empty by default.
 *
 *   This function is called after startup.
 *   The user can use this function to implement the application.
 */
int main(void)
{
    uint32 i    = 0;
    gTestPassed = E_OK;
    AppUtils_logTestResult(APP_UTILS_TEST_STATUS_INIT);
    EthApp_Startup();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!! \n");

    for (i = 0U; i < APPUTILS_ARRAYSIZE(EthExampleFxnTbl); i++)
    {
        EthExampleFxnTbl[i]();
    }
#if (ETHAPP_STACKUSAGE_TEST == STD_ON)
    GT_1trace(McalAppTrace, GT_INFO, "\n\rETH Stack Usage: %d bytes", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(McalAppTrace, GT_ERR, "\n\rETH Stack/section corruption!!!\n");
    }
    AppUtils_printf("\n\rETH_APP: Sample Application - DONE !!!\n");
    if (E_OK == gTestPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, "\n\rETH Test Passed!!!\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, "\n\rETH Test Failed!!!\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_FAIL);
    }
#else
    GT_0trace(McalAppTrace, GT_INFO, "\n\rETH Test Passed!!!\r\n");
    AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
#endif /* (ETHAPP_STACKUSAGE_TEST == STD_ON)*/
    AppUtils_TimerDeinit();
    return gTestPassed;
}

static void EthApp_RxTxTest()
{
    Eth_ConfigType *pEthConfigPtr;
    Std_ReturnType  retVal = (Std_ReturnType)E_NOT_OK;
    uint8           i      = 0;
    memset(&gAppObj, 0U, sizeof(App_State));
    gAppObj.checkPackets = 1U;

    AppUtils_ethPrintVersionInfo();

    pEthConfigPtr = &Eth_Config;

#if (STD_OFF == ETH_VARIANT_PRE_COMPILE)
#if (ETH_ENABLE_MII_API == STD_ON)
    /* Initialize configuration */
    memcpy(&pEthConfigPtr->mdioCfg, &gMdioCfg, sizeof(Eth_MdioConfigType));
#endif /* (ETH_ENABLE_MII_API == STD_ON) */
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
    memcpy(&pEthConfigPtr->cptsCfg, &gCptsCfg, sizeof(Eth_CptsConfigType));
#endif /* (ETH_GLOBALTIMESUPPORT_API == STD_ON) */
    memcpy(&pEthConfigPtr->cpdmaCfg, &gCpdmaCfg, sizeof(Eth_CpdmaConfigType));
#endif /* (STD_OFF == ETH_VARIANT_PRE_COMPILE) */

    /* Do Eth driver initialization */
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
        AppUtils_printf(APP_NAME ": Failed in Eth_SetControllerMode \r\n");
        gTestPassed = E_NOT_OK;
    }

    /* Get Back the Controller mode  */
    retVal = Eth_GetControllerMode(pEthConfigPtr->ctrlIdx, gCtrlModePtr);
    if ((Std_ReturnType)E_OK != retVal)
    {
        AppUtils_printf(APP_NAME ": Failed in Eth_GetControllerMode \r\n");
        gTestPassed = E_NOT_OK;
    }

    /* Generate Random MAC addresses to use */
    for (i = 0U; i < ETH_MAC_ADDR_LEN; i++)
    {
        gTestMacAddr[i] = (uint8)((pEthConfigPtr->ctrlIdx * 0x10U) + i);
    }
    Eth_SetPhysAddr(pEthConfigPtr->ctrlIdx, gTestMacAddr);

    /* Get back the Mac address of the controller*/
    Eth_GetPhysAddr(pEthConfigPtr->ctrlIdx, gPhysAddrPtr);
    AppUtils_printf("\r\nMAC Port %d Address:\r\n", 01U);
    EthApp_printMACAddr(gTestMacAddr);

    /* Adding a Destination address to the filter */
    Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gBCstMacAddr, ETH_ADD_TO_FILTER);

#if (STD_ON == ETHAPP_STRESS_TEST)
    {
        uint32 tempVar = 1U;
        while (tempVar)
        {
            EthApp_ReceivePacketTest(pEthConfigPtr);

            EthApp_TransmitPacketTest(pEthConfigPtr);
        }
    }
#endif /*(STD_ON == ETHAPP_STRESS_TEST)*/

#if (STD_ON == ETHAPP_FILTER_TEST)
    AppUtils_printf("\n\r-----------------------------------------------");
    AppUtils_printf("\n\r*********** ETH FILTER TEST *******************");
    AppUtils_printf("\n\r-----------------------------------------------\n");
    EthApp_FilterTest(pEthConfigPtr);
#endif /* (STD_ON == ETHAPP_FILTER_TEST)*/

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)
    Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gPtpMcastAddr, ETH_ADD_TO_FILTER);
    EthApp_TimeStampTest(pEthConfigPtr);
#endif /* (ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)*/

    gAppObj.frameRcvdFlag = FALSE;

    EthApp_ReceivePacketTest(pEthConfigPtr);

    EthApp_TransmitPacketTest(pEthConfigPtr);

    retVal = EthApp_showStats(pEthConfigPtr->ctrlIdx);

    if (E_OK != retVal)
    {
        AppUtils_printf("main: failed to show statistics\n");
    }
}

/* =========================Function separator========================= */

static void EthApp_ReceivePacketTest(Eth_ConfigType *pEthConfigPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON != ETH_ENABLE_RX_INTERRUPT)
    Eth_RxStatusType rxStatus;
#endif /* (STD_ON != ETH_ENABLE_RX_INTERRUPT)*/

    AppUtils_printf("\r\n---------------------------------------------\r");
    AppUtils_printf("\r\n***********ETH RECEIVE  TEST*******************");
    AppUtils_printf("\r\n---------------------------------------------\r\n");

#if (ETH_ENABLE_RX_INTERRUPT != STD_ON)
    AppUtils_printf("\r\nUsing Eth Receive in polling mode.\r\n");
#endif /*(STD_ON != ETH_ENABLE_RX_INTERRUPT)*/

    AppUtils_printf("\r\nWaiting to receive %d packets from CANoe/PC packet player\r\n", ETHAPP_NUM_RECEIVE_PACKET);
    gAppObj.stats.recvPacketCnt = 0U;
    while (gAppObj.stats.recvPacketCnt < ETHAPP_NUM_RECEIVE_PACKET)
    {
/* Wait for Rx packets */
#if (ETH_ENABLE_RX_INTERRUPT != STD_ON)
        do
        {
            Eth_Receive(pEthConfigPtr->ctrlIdx, 0, &rxStatus);
#if DEBUG
            AppUtils_printf("\r\n\tEth_Receive = [%s] \r\n", ethRcvStatusString[rxStatus]);
#endif /*DEBUG*/
        } while (ETH_RECEIVED_MORE_DATA_AVAILABLE == rxStatus);
#endif /*(ETH_ENABLE_RX_INTERRUPT != STD_ON)*/
    }

    if ((Std_ReturnType)E_NOT_OK == retVal)
    {
        gTestPassed = E_NOT_OK;
    }
    else
    {
        /*
         * Wait for 1U second for clearing all pending receive
         * transfers if any.
         */
        AppUtils_delay(1000U);

        if (gAppObj.checkPackets)
        {
            AppUtils_printf("\r\nReceive packet statistics:");
            AppUtils_printf("\r\n EXPECTEDETHERTYPE_IPV4 (0x%x) = %d ", ETHAPP_ETHERTYPE_IPV4,
                            gAppObj.stats.expectedEtherType_ipv4);
            AppUtils_printf("\r\n EXPECTEDETHERTYPE_VLAN (0x%x) = %d", ETHAPP_ETHERTYPE_VLAN,
                            gAppObj.stats.expectedEtherType_vlan);
            AppUtils_printf("\r\n UNEXPECTEDETHERTYPE = %d", gAppObj.stats.unexpectedEtherType++);
            AppUtils_printf("\r\n");
        }
    }

    if ((Std_ReturnType)E_OK != retVal)
    {
        gTestPassed = E_NOT_OK;
    }
}

/* =========================Function separator========================= */

static void EthApp_TransmitPacketTest(Eth_ConfigType *pEthConfigPtr)
{
    AppUtils_printf("\r\n-----------------------------------------------");
    AppUtils_printf("\r\n***********ETH TRANSMIT TEST*******************");
    AppUtils_printf("\r\n-----------------------------------------------\r\n");

    gAppObj.stats.ethTransmitPckCnt = 0U;

    gAppObj.stats.txBuffUnderflow = gAppObj.stats.txConfirmPacketCnt = 0U;

    AppUtils_printf("\r\nTransmitting %d packets, ", ETHAPP_NUM_TRANSMIT_PACKET);
    AppUtils_printf("\r\nExpect CANoe / PC Wireshark to receive %d packets..", ETHAPP_NUM_TRANSMIT_PACKET);

    EthExample_TransmitStress();

    AppUtils_delay(1000U);
    AppUtils_printf("\r\nStats: Sent=%d,\r\n", gAppObj.stats.ethTransmitPckCnt);
    /* for first iteration we disable txConfirmation, so we check only (ETH_APP_LOOP_COUNT - 1) for
     * TxConfirmation count  */
    if ((gAppObj.stats.ethTransmitPckCnt != ETHAPP_NUM_TRANSMIT_PACKET))
    {
        AppUtils_printf("\r\nTx error, sent only %d packets [of %d] \r\n", gAppObj.stats.ethTransmitPckCnt,
                        ETHAPP_NUM_TRANSMIT_PACKET);
    }
    else
    {
        AppUtils_printf("\r\nTransmitted %d packets \r\n", gAppObj.stats.ethTransmitPckCnt);
    }
}

/* =========================Function separator========================= */

void EthExample_TransmitStress()
{
    BufReq_ReturnType bufStatus = BUFREQ_NOT_OK;
    uint8            *bufPtr;
    uint16            i;
    Eth_BufIdxType    bufIdx;
    uint16            lenByte;
    volatile uint32   packetCnt;
    Std_ReturnType    retVal = (Std_ReturnType)E_NOT_OK;
    boolean           txConfirmation;
    Eth_FrameType     frameType = 0x0800; /* ICMP IP packet */
    Eth_ConfigType   *pEthConfigPtr;
    static uint32     maxTxPacketSizeTestDone = FALSE;

    lenByte = ETH_DATA_LEN;

    pEthConfigPtr = &Eth_Config;

    packetCnt = 0;
    while (packetCnt < ETHAPP_NUM_TRANSMIT_PACKET)
    {
        txConfirmation = TRUE;

        if (!maxTxPacketSizeTestDone)
        {
            /* Do maximum ethernet Tx packet test only once */
            lenByte = 1600U;
        }

    requestbuffer:
        gTestPassed = E_OK;
        bufStatus   = Eth_ProvideTxBuffer(pEthConfigPtr->ctrlIdx, 0, &bufIdx, &bufPtr, &lenByte);
        if (BUFREQ_OK != bufStatus)
        {
            if (BUFREQ_E_OVFL == bufStatus)
            {
                /* Length approved less than asked */
                gTestPassed = E_NOT_OK;
                gAppObj.stats.txBuffLenUnSufficient++;

                /* As per SWS_Eth_00079 if a buffer requested with Eth_ProvideTxBuffer
                 * is larger than the available buffer length, the buffer shall not be
                 * locked but return the available length and BUFREQ_E_OVFL. */
                AppUtils_printf("\r\nMax Tx Packet Size Test passed \r\n");

                /* we change packet length and request again */
                lenByte = ETH_DATA_LEN;
                /* Set max packet test done flag */
                maxTxPacketSizeTestDone = TRUE;

                goto requestbuffer;
            }
            else
            {
                gAppObj.stats.txBuffUnderflow++;
                /* No free buffer */
                gTestPassed = E_NOT_OK;
#if (STD_OFF == ETHAPP_TRAFFIC_SHAPING_TEST)
                AppUtils_delay(100U);
#endif
                /* Try again */
                goto requestbuffer;
            }
        }

        if (E_OK == gTestPassed)
        {
#if (1U == ENABLE_VLAN_TAG)
            uint32 pcp       = 5U;
            uint32 vlanId    = 1024U;
            uint32 tpId      = 0x8100;
            uint32 etherType = 0x0800;

            frameType = tpId;
            /* Fill data into buffer provided by driver */
            *(uint32 *)(bufPtr) = htonl((pcp << 29) | (1 << 28) | (vlanId << 16) | etherType);
#endif /* 1U == ENABLE_VLAN_TAG*/

            /* Fill data into buffer provided by driver */
            for (i = 0U; i <= lenByte; i++)
            {
                bufPtr[i] = i;
            }

            gAppObj.txConfirmPacketFlag = FALSE;

            retVal = Eth_Transmit(pEthConfigPtr->ctrlIdx, bufIdx, frameType, txConfirmation, lenByte, gBCstMacAddr);
            if ((Std_ReturnType)E_NOT_OK == retVal)
            {
                gTestPassed = E_NOT_OK;
                gAppObj.stats.ethTransmitErr++;
            }
            else
            {
                while (gAppObj.txConfirmPacketFlag == FALSE)
                {
                    /*wait till tx packet confirmed */
                }
                gAppObj.stats.ethTransmitPckCnt++;
            }
        }
        else
        {
            gAppObj.stats.provideTxBuffErr++;
        }
        packetCnt++;
    }
}

/* =========================Function separator========================= */
void EthIf_CtrlModeIndication(uint8 ControllerId, Eth_ModeType ControllerMode)
{
    AppUtils_printf("\r\nETH_APP: EthIf_CtrlModeIndication: Eth Controller mode change - %20s ",
                    (ControllerMode == ETH_MODE_ACTIVE) ? "ETH_MODE_ACTIVE" : "ETH_MODE_DOWN");

    gEthcontrollerModeChangeFlag = TRUE;
    MainFunc_Execution           = 3U;
}

/* =========================Function separator========================= */
void EthIf_TrcvModeIndication(uint8 CtrlIdx, EthTrcv_ModeType TrcvMode)
{
    if (ETHTRCV_MODE_ACTIVE == TrcvMode)
    {
        AppUtils_printf("\rETH_APP:EthTRCV Controller Up\n");
    }
    else
    {
        AppUtils_printf("\rETH_APP:EthTRCV Controller Down\n");
    }
    MainFunc_Execution = 2U;
}

/* =========================Function separator========================= */
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    gTestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (Std_ReturnType)E_OK;
}

/* =========================Function separator========================= */

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */
void EthApp_printMACAddr(uint8 macAddr[])
{
    AppUtils_printf("\n\r%02x:%02x:%02x:%02x:%02x:%02x\r\n", macAddr[0U], macAddr[1U], macAddr[2U], macAddr[3U],
                    macAddr[4U], macAddr[5U]);
}

/* =========================Function separator========================= */

void EcuM_SetWakeupEvent(EcuM_WakeupSourceType WakeupRef)
{
    /* This function will be called after call to EthTrcv_CheckWakeup.
     * EthTrcv_CheckWakeup will call this function if wakeup source passed to it is
     * valid source */
    AppUtils_printf(APP_NAME ": EthTrcv Test Wakeup event set for wakeupSource =%d :)!!!\n\r", WakeupRef);
}

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
void EthExample_SendTimeStampPacket(uint8 *pPacketPtr, uint16 lenByte)
{
    BufReq_ReturnType bufStatus = BUFREQ_NOT_OK;
    uint8            *bufPtr;
    Eth_BufIdxType    bufIdx;
    Std_ReturnType    retVal = (Std_ReturnType)E_NOT_OK;
    boolean           txConfirmation;
    Eth_FrameType     frameType = ETHAPP_ETHERTYPE_PTP1588;
    Eth_ConfigType   *pEthConfigPtr;

    pEthConfigPtr = &Eth_Config;

requestbuffer:
    gTestPassed = E_OK;
    bufStatus   = Eth_ProvideTxBuffer(pEthConfigPtr->ctrlIdx, 0, &bufIdx, &bufPtr, &lenByte);
    if (BUFREQ_OK != bufStatus)
    {
        if (BUFREQ_E_OVFL == bufStatus)
        {
            /* Length approved less than asked */
            gTestPassed = E_NOT_OK;
            gAppObj.stats.txBuffLenUnSufficient++;
        }
        else
        {
            gAppObj.stats.txBuffUnderflow++;
            /* No free buffer */
            gTestPassed = E_NOT_OK;
            /*AppUtils_delay(100U);*/
            /* Try again */
            goto requestbuffer;
        }
    }

    if (E_OK == gTestPassed)
    {
        memcpy(bufPtr, pPacketPtr, lenByte);

        /* set no. of transmitted packets to zero */
        gAppObj.stats.txConfirmPacketCnt = 0U;
        txConfirmation                   = TRUE;
        gTimeStampEnabled[bufIdx]        = TRUE;

        Eth_EnableEgressTimeStamp(pEthConfigPtr->ctrlIdx, bufIdx);

        gAppObj.txConfirmPacketFlag = FALSE;
        retVal = Eth_Transmit(pEthConfigPtr->ctrlIdx, bufIdx, frameType, txConfirmation, lenByte, gPtpMcastAddr);

        while (gAppObj.txConfirmPacketFlag == FALSE)
        {
            /*wait till tx packet confirmed */
        }
    }

    if ((Std_ReturnType)E_NOT_OK == retVal)
    {
        gTestPassed = E_NOT_OK;
        gAppObj.stats.ethTransmitErr++;
    }
    else
    {
        gAppObj.stats.ethTransmitPckCnt++;
        AppUtils_delay(10U);
    }

    return;
}
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON)*/

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
void EthApp_printSysTime(Eth_TimeStampType *ts)
{
    AppUtils_printf("[%2u .%4u sec. %10u ns]", ts->secondsHi, ts->seconds, ts->nanoseconds);
}
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON)*/

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
/** \brief Macros for time conversions */
#define NSEC_PER_SEC               (1000000000U)
#define TIME_SYNC_SECONDSHIGH_MASK (0x0000FFFF00000000ULL)
#define TIME_SYNC_SECONDS_MASK     (0xFFFFFFFFU)
void EthApp_getdiffTimePeriod(Eth_TimeStampType prev, Eth_TimeStampType curr)
{
    uint64            prevSec48bit, currSec48bit;
    uint64            temp64bit, deltaSec48bit;
    Eth_TimeStampType diff;

    temp64bit    = curr.secondsHi;
    currSec48bit = (uint64)(temp64bit << 32U) + (uint64)curr.seconds;

    temp64bit    = prev.secondsHi;
    prevSec48bit = (uint64)(temp64bit << 32U) + (uint64)prev.seconds;

    if (curr.nanoseconds < prev.nanoseconds)
    {
        curr.nanoseconds += NSEC_PER_SEC;
        currSec48bit--;
    }

    deltaSec48bit    = currSec48bit - prevSec48bit;
    diff.nanoseconds = curr.nanoseconds - prev.nanoseconds;

    diff.secondsHi = (uint16)((deltaSec48bit & TIME_SYNC_SECONDSHIGH_MASK) >> 32U);
    diff.seconds   = (uint32)(deltaSec48bit & TIME_SYNC_SECONDS_MASK);

    AppUtils_printf("\tTimeSync_Diff: ");
    EthApp_printSysTime(&diff);
}
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON)*/

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
void EthApp_TimeStampGetTime(Eth_ConfigType *pEthConfigPtr)
{
    Std_ReturnType        retVal;
    Eth_TimeStampType     timeStamp     = {0, 0, 0};
    Eth_TimeStampType     prevTimestamp = {0, 0, 0};
    Eth_TimeStampQualType timeQual;
    uint32                i;
    uint32                startTime = 0U, elapsedTime = 0U;

    /* ###----####---###---###*/
    AppUtils_printf("\r\n\tGet global time after delay upto 1000ms (loop=50)\n");
    memset(&timeStamp, 0U, sizeof(Eth_TimeStampType));
    for (i = 0; i < 50; i++)
    {
        startTime = AppUtils_getCurTimeInMsec();
        AppUtils_delay(1000);
        retVal = Eth_GetCurrentTime(pEthConfigPtr->ctrlIdx, &timeQual, &timeStamp);
        if (E_NOT_OK != retVal)
        {
            AppUtils_printf("\r\n\tCurr_Time: ");
            EthApp_printSysTime(&timeStamp);
            EthApp_getdiffTimePeriod(prevTimestamp, timeStamp);
            memcpy(&prevTimestamp, &timeStamp, sizeof(Eth_TimeStampType));
        }
        else
        {
            FAIL_MESSAGE;
        }
        elapsedTime = AppUtils_getElapsedTimeInMsec(startTime);
        AppUtils_printf("(32K Cntr Diff %3d)", elapsedTime);
    }

    AppUtils_printf("\r\n");

    memset(&prevTimestamp, 0U, sizeof(Eth_TimeStampType));
    while (tsyncGetTsStress)
    {
        uint32 delay = rand();
        retVal       = Eth_GetCurrentTime(pEthConfigPtr->ctrlIdx, &timeQual, &timeStamp);
        if (E_NOT_OK != retVal)
        {
            AppUtils_printf("\r\n\tCurr_Time: ");
            EthApp_printSysTime(&timeStamp);
            AppUtils_printf("\r\n\t Delay = %d", delay);
            AppUtils_delay(delay);
            AppUtils_printf("(Time diff %f)", (timeStamp.seconds - (float32)delay / (float32)1000));
            memcpy(&prevTimestamp, &timeStamp, sizeof(Eth_TimeStampType));
        }
        else
        {
            FAIL_MESSAGE;
        }
    }
}
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON)*/

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)
void EthApp_TimeStampTest(Eth_ConfigType *pEthConfigPtr)
{
    uint32 egressPckCnt = 0;

    AppUtils_printf("\n\r-----------------------------------------------");
    AppUtils_printf("\n\r***********Time Stamping Test*******************");
    AppUtils_printf("\n\r-----------------------------------------------\n");

    EthApp_TimeStampGetTime(pEthConfigPtr);

    AppUtils_printf("\n\n\r Time Sync Packet Egress Test ");
    AppUtils_printf("\n\r--------------------------------");

    while ((egressPckCnt < ETHAPP_NUM_TIME_SYNC_PACKET) || tsyncXmitStress)
    {
        EthExample_SendTimeStampPacket(&timeSyncPacket[0], lengthOfTimeSyncPacket);
        EthExample_SendTimeStampPacket(&pDelayRequestPacket[0], lengthOfPdelayRequestPacket);
        egressPckCnt++;
    }
    AppUtils_delay(1000U);
    AppUtils_printf("\n\r\n Time Sync Packet Ingress Test ");
    AppUtils_printf("\r\n---------------------------------");
    AppUtils_printf("\r\n Send timestamp (0x88F7) packets (%d) from PC \n", ETHAPP_NUM_TIME_SYNC_PACKET);

    /* Ingress time stamp is taken in EthIf_RxIndication function */
    while (gAppObj.stats.expectedEtherType_ptp < ETHAPP_NUM_TIME_SYNC_PACKET)
        ;

    AppUtils_printf("\r\n ----------------------------\n");
    AppUtils_printf("\r\n Time Stamping Test Completed \n");
    AppUtils_printf("\r\n ----------------------------\n");
}

#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)*/

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
void EthApp_TimeStampGetIngressTime(uint8 ctrlIdx, Eth_DataType *DataPtr)
{
    Eth_TimeStampQualType timeQual = ETH_INVALID;
    Eth_TimeStampType     timeStamp;
    uint8                *msgtype;
    uint16               *seqid;
    uint16                messageType;

    msgtype     = (uint8 *)DataPtr;
    seqid       = (uint16 *)((uint8 *)DataPtr + 30U /* TIME_SYNC_OFFSET_PTP_SEQUENCE_ID */);
    messageType = (uint16)(*msgtype & 0xf);

    Eth_GetIngressTimeStamp(ctrlIdx, DataPtr, &timeQual, &timeStamp);

    AppUtils_printf("\r\n\tPacket Ingress MessagType-%5s, SeqID-%5d ",
                    (messageType > 15) ? "Invalid msg type" : msgTypeString[messageType], ntohs(*seqid));
    EthApp_printSysTime(&timeStamp);
    AppUtils_printf("[%11s]\n", timeStampQualString[timeQual]);
}
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON)*/

static Std_ReturnType EthApp_showStats(uint8 ctrlIdx)
{
    Std_ReturnType retVal;
#if (STD_ON == ETH_GET_DROPCOUNT_API)
    Eth_CounterType ethCounter;
    retVal = Eth_GetCounterValues(ctrlIdx, &ethCounter);
    if (E_OK == retVal)
    {
        AppUtils_printf("\r----------------------------\n");
        AppUtils_printf("\rController %d Counters\n", ctrlIdx);
        AppUtils_printf("\r----------------------------\n");
        AppUtils_printf("\rBuffer overruns   : %d\n", ethCounter.DropPktBufOverrun);
        AppUtils_printf("\rCRC errors        : %d\n", ethCounter.DropPktCrc);
        AppUtils_printf("\rUndersize packets : %d\n", ethCounter.UndersizePkt);
        AppUtils_printf("\rOversized packets : %d\n", ethCounter.OversizePkt);
        AppUtils_printf("\rAlignment errors  : %d\n", ethCounter.AlgnmtErr);
        ;
        AppUtils_printf("\rErroneous inbound : %d\n", ethCounter.ErrInbdPkt);
        AppUtils_printf("\rErroneous outbound: %d\n", ethCounter.ErrOtbdPkt);
        AppUtils_printf("\rSingle collision  : %d\n", ethCounter.SnglCollPkt);
        AppUtils_printf("\rMultiple collision: %d\n", ethCounter.MultCollPkt);
        AppUtils_printf("\rDeferred transm   : %d\n", ethCounter.DfrdPkt);
        AppUtils_printf("\rLate collisions   : %d\n", ethCounter.LatCollPkt);
        AppUtils_printf("\rExcessive colls   : %d\n", ethCounter.HwDepCtr0);
        AppUtils_printf("\rCarrier loss      : %d\n", ethCounter.HwDepCtr1);
    }
    else
    {
        AppUtils_printf("\rshowCountValues: failed to get counters: %d\n", retVal);
    }
#else
    AppUtils_printf("\rshowCountValues: Eth_GetCounterValues() API not enabled\n");
    retVal = E_NOT_OK;
#endif /*(STD_ON == ETH_GET_DROPCOUNT_API)*/

#if (STD_ON == ETH_GETETHERSTATS_API)
    Eth_RxStatsType rxStats;
    retVal = Eth_GetRxStats(ctrlIdx, &rxStats);
    if (E_OK == retVal)
    {
        AppUtils_printf("\r----------------------------\n");
        AppUtils_printf("\rController %d Rx Statistics\n", ctrlIdx);
        AppUtils_printf("\r----------------------------\n");
        AppUtils_printf("\rRx Drop Events       : %d\n", rxStats.RxStatsDropEvents);
        AppUtils_printf("\rRx Octets            : %d\n", rxStats.RxStatsOctets);
        AppUtils_printf("\rRx Packets           : %d\n", rxStats.RxStatsPkts);
        AppUtils_printf("\rRx Bcast Packets     : %d\n", rxStats.RxStatsBroadcastPkts);
        AppUtils_printf("\rRx Mcast Packets     : %d\n", rxStats.RxStatsMulticastPkts);
        AppUtils_printf("\rRx CRC/Align Errors  : %d\n", rxStats.RxStatsCrcAlignErrors);
        AppUtils_printf("\rRx Undersized Packets: %d\n", rxStats.RxStatsUndersizePkts);
        AppUtils_printf("\rRx Oversized Packets : %d\n", rxStats.RxStatsOversizePkts);
        AppUtils_printf("\rRx Fragments         : %d\n", rxStats.RxStatsFragments);
        AppUtils_printf("\rRx Jabbers           : %d\n", rxStats.RxStatsJabbers);
        AppUtils_printf("\rRx Unicast Packets            : %d\n", rxStats.RxUnicastFrames);
    }
    else
    {
        AppUtils_printf("\rgetRxStats: failed to get counters: %d\n", retVal);
    }
#else
    AppUtils_printf("getRxStats: Eth_GetRxStats() API not enabled\n");
    retVal = E_NOT_OK;
#endif /* (STD_ON == ETH_GETETHERSTATS_API)*/

#if (STD_ON == ETH_GETTX_STATS_API)
    Eth_TxStatsType txStats;
    retVal = Eth_GetTxStats(ctrlIdx, &txStats);
    if (E_OK == retVal)
    {
        AppUtils_printf("\r----------------------------\n");
        AppUtils_printf("\rController %d Tx Statistics \n", ctrlIdx);
        AppUtils_printf("\r----------------------------\n");
        AppUtils_printf("\rTx Num octets          : %d\n", txStats.TxNumberOfOctets);
        AppUtils_printf("\rTx No Unicast Packets  : %d\n", txStats.TxNUcastPkts);
        AppUtils_printf("\rTx Unicast Packets     : %d\n", txStats.TxUniCastPkts);
    }
    else
    {
        AppUtils_printf("\rgetTxStats: failed to get TX stats: %d\n", retVal);
    }
#else
    AppUtils_printf("g\retTxStats: Eth_GetTxStats() API not enabled\n");
    retVal = E_NOT_OK;
#endif /* (STD_ON == ETH_GETTX_STATS_API)*/

#if (STD_ON == ETH_GETTXERROR_COUNTERVALUES_API)
    Eth_TxErrorCounterValuesType txErrorCounterValues;
    retVal = Eth_GetTxErrorCounterValues(ctrlIdx, &txErrorCounterValues);
    if (E_OK == retVal)
    {
        AppUtils_printf("\r--------------------------------\n");
        AppUtils_printf("\rController %d Tx Error Counters \n", ctrlIdx);
        AppUtils_printf("\r--------------------------------\n");
        AppUtils_printf("\rTx Deferred transm      : %d\n", txErrorCounterValues.TxDeferredTrans);
        AppUtils_printf("\rTx Single collisions    : %d\n", txErrorCounterValues.TxSingleCollision);
        AppUtils_printf("\rTx Multiple collisions  : %d\n", txErrorCounterValues.TxMultipleCollision);
        AppUtils_printf("\rTx Late collisions      : %d\n", txErrorCounterValues.TxLateCollision);
        AppUtils_printf("\rTx Excessive collisions : %d\n", txErrorCounterValues.TxExcessiveCollison);
    }
    else
    {
        AppUtils_printf("\rshowTxErrStatsCount: failed to get counters: %d\n", retVal);
    }
#else
    AppUtils_printf("\rshowTxErrStatsCount: Eth_GetTxErrorCounterValues() API not enabled\n");
    retVal = E_NOT_OK;
#endif /*(STD_ON == ETH_GETTXERROR_COUNTERVALUES_API)*/

    return retVal;
}

/* =========================Function separator========================= */
void EthIf_RxIndication(uint8 ctrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, uint8 *PhysAddrPtr,
                        Eth_DataType *DataPtr, uint16 lenByte)
{
    /* This flag would be used by app to ack ping request  */
    gAppObj.frameRcvdFlag    = TRUE;
    gAppObj.currFrameDataPtr = DataPtr;
    gAppObj.currFrameSize    = lenByte;

    (void)memcpy(gAppObj.currFramePhysAddr, PhysAddrPtr, (size_t)ETH_MAC_ADDR_LEN);

    i2++;
    /* Increase Rx frame count */
    gAppObj.stats.recvPacketCnt++;

    if (gAppObj.checkPackets)
    {
        /* Save the callback configuration info to the channel structure*/
        if (FrameType == ETHAPP_ETHERTYPE_IPV4)
        {
            gAppObj.stats.expectedEtherType_ipv4++;
        }
        else if (FrameType == ETHAPP_ETHERTYPE_VLAN)
        {
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)
            uint16 *ethTypePtr = (uint16 *)DataPtr + 1;
            if (ntohs(*ethTypePtr) == ETHAPP_ETHERTYPE_PTP1588)
            {
                /* Single tagged PTP */
                gAppObj.stats.expectedEtherType_ptp++;
                EthApp_TimeStampGetIngressTime(ctrlIdx, (Eth_DataType *)((uint8 *)DataPtr + 4U));
            }
            else if (ntohs(*ethTypePtr) == ETHAPP_ETHERTYPE_VLAN)
            {
                /* Doubly tagged PTP */
                ethTypePtr = (uint16 *)DataPtr + 3;
                if (ntohs(*ethTypePtr) == ETHAPP_ETHERTYPE_PTP1588)
                {
                    /* Single tagged PTP */
                    gAppObj.stats.expectedEtherType_ptp++;
                    EthApp_TimeStampGetIngressTime(ctrlIdx, (Eth_DataType *)((uint8 *)DataPtr + 8U));
                }
                else
                {
                    gAppObj.stats.expectedEtherType_stackedvlan++;
                }
            }
            else
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON) && (ETHAPP_TIMESTAMP_TEST == STD_ON)*/
            {
                gAppObj.stats.expectedEtherType_vlan++;
            }
        }
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
        else if (FrameType == ETHAPP_ETHERTYPE_PTP1588)
        {
            gAppObj.stats.expectedEtherType_ptp++;
            EthApp_TimeStampGetIngressTime(ctrlIdx, DataPtr);
        }
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON)*/
        else
        {
            gAppObj.stats.errorCnt++;
            gAppObj.stats.unexpectedEtherType++;
        }
    }

#if (1U == ENABLE_PACKET_CPU_COPY)
    memcpy((void *)&_gDstBuff, DataPtr, lenByte);
#endif /* (1U == ENABLE_PACKET_CPU_COPY)*/

    MainFunc_Execution = 5U;
}

void EthIf_TxConfirmation(uint8 CtrlIdx, Eth_BufIdxType bufIdx, Std_ReturnType Result)
{
    if (E_OK == Result)
    {
        /* Increase Tx frame count */
        gAppObj.stats.txConfirmPacketCnt++;
        gAppObj.txConfirmPacketFlag = TRUE;

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
        if (gTimeStampEnabled[bufIdx] == TRUE)
        {
            Eth_TimeStampQualType timeQual = ETH_INVALID;
            Eth_TimeStampType     timeStamp;

            Eth_GetEgressTimeStamp(CtrlIdx, bufIdx, &timeQual, &timeStamp);

            AppUtils_printf("\r\n\tPacket Egress TS:");
            EthApp_printSysTime(&timeStamp);
            AppUtils_printf("[%11s]", timeStampQualString[timeQual]);

            gTimeStampEnabled[bufIdx] = FALSE;
        }
#endif /*(ETH_GLOBALTIMESUPPORT_API == STD_ON)*/
    }
    else /*if (E_NOT_OK == Result)*/
    {
        AppUtils_printf("TxConfirmation: transmission of buffer %d failed\r\n", bufIdx);
        gAppObj.stats.ethTransmitErr++;
    }

    i2++;
    MainFunc_Execution = 4U;
}

#if (STD_ON == ETHAPP_FILTER_TEST)

static void EthApp_FilterTest(Eth_ConfigType *pEthConfigPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    uint32         i;

    for (i = 0U; i < ETH_MAC_ADDR_LEN; i++)
    {
        gTestMacAddr[i] = (i + 10);
    }

    AppUtils_printf("\n\rAdding MAC Address to filter:");
    EthApp_printMACAddr(gTestMacAddr);

    retVal = Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gTestMacAddr, ETH_ADD_TO_FILTER);

    AppUtils_printf("\n\rWaiting to receive %d packets from PC packet player..\n", ETHAPP_NUM_RECEIVE_PACKET_FILTER);
    AppUtils_printf("\n\rSend packets with destination MAC address:");
    EthApp_printMACAddr(gTestMacAddr);

    while (gAppObj.stats.recvPacketCnt < ETHAPP_NUM_RECEIVE_PACKET_FILTER)
        ;
    gAppObj.stats.recvPacketCnt = 0;
    AppUtils_printf("\n\rRemoving MAC Address from filter:");
    EthApp_printMACAddr(gTestMacAddr);
    retVal += Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gTestMacAddr, ETH_REMOVE_FROM_FILTER);

    AppUtils_printf("\n\rMulticast address filter test \n");
    /* Change mac address to multicast address */
    gTestMacAddr[0] = 0x01;
    gTestMacAddr[1] = 0x00;
    gTestMacAddr[2] = 0x5E;
    AppUtils_printf("\n\r Adding multicast MAC Address to filter:");
    EthApp_printMACAddr(gTestMacAddr);
    retVal += Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gTestMacAddr, ETH_ADD_TO_FILTER);

    AppUtils_printf("\n\rWaiting to receive %d packets from PC packet player..\n", ETHAPP_NUM_RECEIVE_PACKET_FILTER);
    AppUtils_printf("\n\r Send packets with destination MAC address:");
    EthApp_printMACAddr(gTestMacAddr);

    while (gAppObj.stats.recvPacketCnt < ETHAPP_NUM_RECEIVE_PACKET_FILTER)
        ;
    gAppObj.stats.recvPacketCnt = 0u;

    AppUtils_printf("\n\r Removing MAC Address from filter:");
    EthApp_printMACAddr(gTestMacAddr);

    retVal += Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gTestMacAddr, ETH_REMOVE_FROM_FILTER);

    AppUtils_printf("\n\rOpening up filter completely (ALE bypass)\n");
    retVal += Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gBCstMacAddr, ETH_ADD_TO_FILTER);

    AppUtils_printf("\n\rWaiting to receive %d packets from PC packet player..\n", ETHAPP_NUM_RECEIVE_PACKET_FILTER);
    AppUtils_printf("\n\rSend packets with any MAC address\n");

    while (gAppObj.stats.recvPacketCnt < ETHAPP_NUM_RECEIVE_PACKET_FILTER)
        ;
    gAppObj.stats.recvPacketCnt = 0u;

    AppUtils_printf("\n\rALE Bypass Transmit Test\n");
    AppUtils_printf("\n\rTransmitting %d packets ", ETHAPP_NUM_TRANSMIT_PACKET);
    AppUtils_printf("\n\rExpect PC Wireshark to receive %d packets..", ETHAPP_NUM_TRANSMIT_PACKET);
    EthExample_TransmitStress();

    AppUtils_printf("\n\rDisabling filter bypass & adding host address back to filter \n");
    /* Send 00:00:00:00:00:00 as MAC address to reuse earlier Controller MAC address */
    for (i = 0U; i < ETH_MAC_ADDR_LEN; i++)
    {
        gTestMacAddr[i] = 0U;
    }
    retVal += Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, gTestMacAddr, ETH_ADD_TO_FILTER);

    AppUtils_printf("\n\rWaiting to receive %d packets from PC packet player..\n", ETHAPP_NUM_RECEIVE_PACKET_FILTER);
    AppUtils_printf("\n\rSend packets with Controller MAC address\n");
    while (gAppObj.stats.recvPacketCnt < ETHAPP_NUM_RECEIVE_PACKET_FILTER)
        ;
    gAppObj.stats.recvPacketCnt = 0u;

    if ((Std_ReturnType)E_OK != retVal)
    {
        FAIL_MESSAGE;
        gTestPassed = E_NOT_OK;
    }
}
#endif /* #if (STD_ON == ETHAPP_FILTER_TEST)*/
