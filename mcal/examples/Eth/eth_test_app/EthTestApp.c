/* ======================================================================
 *   Copyright (C) 2023-2024 Texas Instruments Incorporated
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
#include "Os.h"

/* Starterware Includes */
#include "hw_ctrl_core.h"
#include "sys_vim.h"
#include "app_utils.h"
#include "trace.h"
#include "EthTestApp.h"
#include "EthApp_Startup.h"

#include "EthUtils_Target.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_NAME "ETH_APP"

#define FAIL_MESSAGE AppUtils_printf("\r\nFailed in %s \n", __func__)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void EthApp_printMACAddr(uint8 macAddr[]);

/* Test cases */

/**
 * \brief Test basic frame reception
 *
 * Basic DUT frame reception test.  The target side performs these operations:
 * - Send START command
 * - Receive frames until the STOP is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0001(void);

/**
 * \brief Test basic frame transmission
 *
 * Basic DUT frame transmission test.  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged frames without confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0002(void);

/**
 * \brief Test external loopback
 *
 * External loopback test.  The target side sends frames to the host, the host
 * receives the frames and sends them back to the target.  The following operations
 * are performed on the target side:
 * - Send START command
 * - Send and receive ETH_TEST_ITER_M_COUNT frames, for each of them:
 *   o A different payload is set
 *   o EtherType and payload are verified on the received frame
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0003(void);

/**
 * \brief Test default filter operation
 *
 * Test the operation of the default DUT's filter configuration (only frames with
 * DUT's MAC address are accepted, all others are rejected).  The target side
 * performs these operations:
 * - Send START command
 * - Receive frames until the STOP is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT / 2 as
 * only one half of the total frames sent by the host have the DUT's MAC address.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0004(void);

#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)
/**
 * \brief Test different filter configurations
 *
 * Test the different modes of the DUT's filter configuration.  The target side performs
 * these operations:
 * - Send START command
 * - Part 1
 *   o Filter is reset to accept only frames with DUT's MAC address
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be rejected
 *     - Expected to receive ETH_TEST_ITER_M_COUNT / 2 frames
 * - Part 2
 *   o A second unicast MAC address is added to the DUT's filter
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is second valid MAC address. It should be accepted
 *     - Expected to receive ETH_TEST_ITER_M_COUNT frames
 * - Part 3
 *   o A multicast address is added to the DUT's filter
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is multicast address. It should be accepted
 *     - Expected to receive ETH_TEST_ITER_M_COUNT frames
 * - Part 4
 *   o The multicast address is removed from the DUT's filter
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is multicast address. It should be rejected
 *     - Expected to receive ETH_TEST_ITER_M_COUNT / 2 frames
 * - Part 5
 *   o The filter is opened up (promiscuous mode)
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be accepted
 *     - Expected to receive ETH_TEST_ITER_M_COUNT frames
 * - Part 6
 *   o The filter is reset back to accept only DUT's unicast address
 *   o Receive frames until STOP is detected
 *     - Frame 1: Source MAC address is DUT's. It should be accepted
 *     - Frame 2: Source MAC address is not DUT's. It should be rejected
 *     - Expected to receive ETH_TEST_ITER_M_COUNT / 2 frames
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0005(void);
#endif /* (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API) */

/**
 * \brief Test frame transmission with confirmation
 *
 * DUT frame transmission test with TX confirmation.  The target side performs
 * these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged frames with confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0006(void);

/**
 * \brief Test frame transmission of VLAN tagged frames
 *
 * DUT frame transmission test of VLAN tagged frames.  The target side performs
 * these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT VLAN tagged frames with confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0007(void);

/**
 * \brief Test frame transmission of different lengths
 *
 * DUT frame transmission test of different frame lengths, including short frames
 * (less than 64 octets).  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_S_COUNT frames for lengths starting at 10 octets in
 *   increments of 10 octets until 1500 octets.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0008(void);

/**
 * \brief Test VLAN tagged frame reception
 *
 * DUT VLAN tagged frame reception test.  The target side performs these operations:
 * - Send START command
 * - Receive frames until the STOP is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0009(void);

/**
 * \brief Test controller mode change
 *
 * Controller mode change test.  The target performs the following operations:
 * - Send START command
 * - Run ETH_TEST_ITER_S_COUNT iterations of:
 *   o Set controller mode to DOWN state
 *   o Set controller mode to ACTIVE state
 *   o Transmit frames (run test 0002)
 *   o Receive frames (run test 0001)
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0010(void);

/**
 * \brief Test multicast frame transmission
 *
 * Multicast frame transmission test.  The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged multicast frames without
 *   confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0011(void);

/**
 * \brief Test basic frame reception for checksum hw offload
 *
 * Basic DUT frame reception test.  The target side performs these operations:
 * - Send START command
 * - Receive frames until the STOP is detected
 *
 * The number of frames expected to be received is ETH_TEST_ITER_M_COUNT.
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0012(void);

/**
 * \brief Test basic frame transmission for checksum hw offload
 *
 * Basic DUT frame transmission test for checksum validation.
 * The target side performs these operations:
 * - Send START command
 * - Transmit ETH_TEST_ITER_M_COUNT non-VLAN tagged frames without confirmation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0013(void);

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

/**
 * \brief Measure DUT transmit throughput
 *
 * Measure DUT transmit throughput for multiple frame size. The target
 * performs the following operations:
 * - with each frame size and frame number call EthApp_test_0010
 *   to calculate throughput for that frame szie
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0110(void);

/**
 * \brief Measure DUT receive throughput
 *
 * Measure DUT receive throughput.
 * . The target performs the following operations:
 * - Get the initial timestamp corresponding to the first frame received
 * - Receive frames until the STOP is detected and get the final timestamp
 * - Compute the receive throughput from the number of received frames and the
 *   time difference between the two captured timestamps
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0101(void);

/**
 * \brief Test internal loopback
 *
 * Internal loopback test (MAC).
 * - Send and receive ETH_TEST_ITER_M_COUNT frames, for each of them:
 *   o A different payload is set
 *   o EtherType and payload are verified on the received frame
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0200(void);

/* Egress timestamp test */
boolean EthApp_test_0300(void);

/* Ingress timestamp test */
boolean EthApp_test_0301(void);

/* Get current time test */
boolean EthApp_test_0302(void);

#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
/* Traffic shaping test */
boolean EthApp_test_0400(void);
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
/**
 * \brief Test MDIO Operation
 *
 * Stress testing of MDIO Read Operation
 *
 * \return PASS or FAIL  Test result
 */
boolean EthApp_test_0500(void);
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */

/* Tx QOS test */
boolean EthApp_test_0610(void);

/* Rx QOS test */
boolean EthApp_test_0611(void);

/* Tx IRQ pacing test */
boolean EthApp_test_0201(void);

/* Rx IRQ pacing test */
boolean EthApp_test_0202(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint8 gBCstMacAddr[ETH_MAC_ADDR_LEN]  = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8 gPtpMcastAddr[ETH_MAC_ADDR_LEN] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E};

/* Broadcast MAC address */
static uint8 BcastAddr[ETH_HW_ADDR_LEN] = {0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU};

#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)
static uint8 TargetMcastAddr[ETH_HW_ADDR_LEN] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U};
#endif

/* Null MAC address */
static uint8 NullAddr[ETH_HW_ADDR_LEN] = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

/* Unicast MAC address */
static uint8 UcastAddr[ETH_HW_ADDR_LEN] = {0x0aU, 0x0bU, 0x0cU, 0x0dU, 0x0eU, 0x0fU};

/* Multicast MAC address */
static uint8 McastAddr[ETH_HW_ADDR_LEN] = {0x01U, 0x00U, 0x5eU, 0x0dU, 0x0eU, 0x0fU};

/* Transmit Multicast MAC address */
static uint8 TxMcastAddr[ETH_HW_ADDR_LEN] = {0x33U, 0x33U, 0x00U, 0x00U, 0x00U, 0x01U};

static VAR(uint8, AUTOMATIC) MacDest[6];
P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) gPhysAddrPtr = MacDest;

static VAR(Eth_ModeType, AUTOMATIC) Ethmode                = ETH_MODE_DOWN;
P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) gCtrlModePtr = &Ethmode;

static TestFunc testFuncs[] = {
    &EthApp_test_0001, &EthApp_test_0002, &EthApp_test_0003, &EthApp_test_0004,
#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
    &EthApp_test_0400,
#endif
#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)
    &EthApp_test_0005,
#endif
    &EthApp_test_0006, &EthApp_test_0007, &EthApp_test_0008, &EthApp_test_0009, &EthApp_test_0010, &EthApp_test_0011,
#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) && (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
    &EthApp_test_0012, &EthApp_test_0013,
#endif
    &EthApp_test_0300, &EthApp_test_0301, &EthApp_test_0302, &EthApp_test_0110, &EthApp_test_0101, &EthApp_test_0201,
    &EthApp_test_0202,
/* host independent test case */
#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
    &EthApp_test_0500,
#endif
};

/* Eth application state */
EthUtilsApp_State gEthUtilsApp;

extern volatile VAR(Eth_StateType, ETH_VAR_ZERO_INIT) Eth_DrvStatus;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    uint32         i = 0, ti = 0;
    boolean        status       = TRUE;
    boolean        globalStatus = TRUE;
    Std_ReturnType retVal       = E_OK;

    /**/

    EthApp_Startup();

    /* Print date and time */
    EthUtils_printf("---\r\nEth Application build date/time: %s, %s\r\n", __DATE__, __TIME__);

    EthUtils_printf("Eth Application Starts\r\n");

    /* Do Eth driver initialization */
    Eth_ConfigType *pEthConfigPtr;
    pEthConfigPtr = &EthConfigSet_EthCtrlConfig_0;

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
    }

    /* Get Back the Controller mode  */
    retVal = Eth_GetControllerMode(pEthConfigPtr->ctrlIdx, gCtrlModePtr);
    if ((Std_ReturnType)E_OK != retVal)
    {
        AppUtils_printf(APP_NAME ": Failed in Eth_GetControllerMode \r\n");
    }

    /* Update MAC address from config */
    Eth_SetPhysAddr(pEthConfigPtr->ctrlIdx, pEthConfigPtr->portCfg.macCfg.macAddr);

    /* Get back the Mac address of the controller*/
    Eth_GetPhysAddr(pEthConfigPtr->ctrlIdx, gEthUtilsApp.macAddr);
    AppUtils_printf("\r\nMAC Port %d Address:\r\n", pEthConfigPtr->portIdx);
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
    gEthUtilsApp.testIdx             = ARRAY_SIZE(testFuncs);

#if (ETH_ENABLE_TX_INTERRUPT == STD_OFF)
    gEthUtilsApp.txIrqDisable = TRUE;
#endif

#if (ETH_ENABLE_RX_INTERRUPT == STD_OFF)
    gEthUtilsApp.rxIrqDisable = TRUE;
#endif

#if (ETH_USR_MDIO_INTERRUPT == STD_OFF)
    gEthUtilsApp.mdioIrqDisable = TRUE;
#endif

    memset(&gEthUtilsApp.stats, 0U, sizeof(EthUtilsApp_Stats));

    AppUtils_ethPrintVersionInfo();

    /* Main test section */
    if (E_OK == retVal)
    {
        for (ti = 0u; ti < ETH_APP_TEST_ROUND; ti++)
        {
            /* DUT <-> Host Initial Handshake */
            status        = EthApp_waitForHost();
            globalStatus &= status;

            if (PASS != status)
            {
                break;
            }

            for (i = 0U; i < ARRAY_SIZE(testFuncs); i++)
            {
                if ((gEthUtilsApp.testIdx < ARRAY_SIZE(testFuncs)) && (i != gEthUtilsApp.testIdx))
                {
                    continue;
                }

                EthUtils_printf("\r\n\r\n-----------------------------------------------------------\r\n");
                memset(&gEthUtilsApp.stats, 0U, sizeof(EthApp_Stats));
                status        = testFuncs[i]();
                globalStatus &= status;
                EthUtils_printf("Test Result: %s %d\r\n", status ? "Pass" : "Fail", ti);
                EthUtils_printf("-----------------------------------------------------------\r\n");
                if (status != 1)
                {
                    break;
                }

                /* Some packet from last test pending, clear it up */
                EthApp_transmitFlush(gEthUtilsApp.ctrlIdx);
            }
            if (status != 1)
            {
                break;
            }

            EthApp_delay(2000U);
        }
    }
    EthUtils_printf("\r\n");

    /* Show statistics */
    if (E_OK == retVal)
    {
        retVal = EthApp_showStats(gEthUtilsApp.ctrlIdx);
        if (E_OK != retVal)
        {
            EthUtils_printf("main: failed to show statistics\r\n");
        }
    }

    /* Deinitialize the Ethernet controller */
    if (E_OK == retVal)
    {
        retVal = EthApp_deinit(gEthUtilsApp.ctrlIdx);
        if (E_OK != retVal)
        {
            EthUtils_printf("Failed to deinitialize: %d\r\n", retVal);
        }
    }

    EthUtils_printf("ETH Stack Usage: %d bytes\r\n", AppUtils_getStackUsage());

    EthUtils_printf("Final Tests Results: %s\r\n", (globalStatus == TRUE) ? "PASS" : "FAIL");

    if (E_OK == retVal)
    {
        EthUtils_printf("Eth Application Completed\r\n");
    }
    else
    {
        EthUtils_printf("Eth Application Failed\r\n");
    }

    return retVal;
}

boolean EthApp_test_0001(void)
{
    uint32  num = 0U;
    boolean status;

    EthUtils_printf("test_0001: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthUtilsApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0001: failed while receiving frames\r\n");
    }

    EthUtils_printf("test_0001: received %d of %d frames\r\n", gEthUtilsApp.stats.rxExp1PktCnt, ETH_TEST_ITER_M_COUNT);

    if (gEthUtilsApp.stats.rxExp1PktCnt != ETH_TEST_ITER_M_COUNT)
    {
        EthUtils_printf("test_0001: received frame count mismatch (exp=%d, got=%d)\r\n", ETH_TEST_ITER_M_COUNT,
                        gEthUtilsApp.stats.rxExp1PktCnt);
        status = FAIL;
    }

    EthUtils_printf("test_0001: END\r\n");

    return status;
}

boolean EthApp_test_0002(void)
{
    uint32  iterations     = ETH_TEST_ITER_M_COUNT;
    uint16  len            = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan           = FALSE;
    boolean status         = PASS;
    uint8   i;

    EthUtils_printf("test_0002: START\r\n");

    /* Do 2 transmit test, 1 for standard and 1 for zero mempy if enabled */
    for (i = 0; i < 2; ++i)
    {
        /* Send START cmd */
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

        /* Transmit frames */
        status |= EthApp_transmit(gEthUtilsApp.ctrlIdx, iterations, len, txConfirmation, vlan, ETH_DEFAULT_TX_PRIORITY,
                                  &BcastAddr[0U]);
    }

    EthUtils_printf("test_0002: END\r\n");

    return status;
}

boolean EthApp_test_0003(void)
{
    uint32   iterations = ETH_TEST_ITER_M_COUNT;
    uint32   i;
    sint32   fillStatus;
    uint16   len    = 1500U;
    boolean  status = TRUE;
    EthFrame frame;

    EthUtils_printf("test_0003: START\r\n");

    /* Initialize frame header */
    memcpy(frame.hdr.dstMac, BcastAddr, ETH_MAC_ADDR_LEN);
    memcpy(frame.hdr.srcMac, gEthUtilsApp.macAddr, ETH_MAC_ADDR_LEN);
    frame.hdr.etherType = ETHERTYPE_EXPERIMENTAL1;

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Send and receive frames */
    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthUtilsApp.verbose)
        {
            EthUtils_printf("test_0003: iteration %d\r\n", i);
        }

        gEthUtilsApp.saveRxFrame       = TRUE;
        gEthUtilsApp.stats.rxPktCnt    = 0U;
        gEthUtilsApp.stats.rxPktIndCnt = 0U;

        fillStatus = EthUtils_fillPayload((DataFramePayload *)frame.payload, i % ETH_TEST_NUM_TYPES, len);
        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthUtils_printf("test_0003: failed to fill test packet\r\n");
            status = FAIL;
            break;
        }

        /* Send the frame */
        EthApp_send(gEthUtilsApp.ctrlIdx, &frame, len, ETH_DEFAULT_TX_PRIORITY);

        /* Wait for Rx frames */
        while (0 == gEthUtilsApp.stats.rxPktIndCnt)
        {
            if (gEthUtilsApp.rxIrqDisable)
            {
                EthApp_receiveAllFifo(gEthUtilsApp.ctrlIdx);
            }
        }

        /* End the test if STOP cmd is detected */
        if (TRUE == EthFrame_isStopCmd(&gEthUtilsApp.rxFrame))
        {
            break;
        }

        /* Check if EtherType field matches */
        if (frame.hdr.etherType != gEthUtilsApp.rxFrame.hdr.etherType)
        {
            EthUtils_printf("test_0003: EtherType mismatch (exp=0x%04x, got=0x%04x)\r\n", frame.hdr.etherType & 0xFFFFU,
                            gEthUtilsApp.rxFrame.hdr.etherType & 0xFFFFU);
            status = FAIL;
            break;
        }

        /* Check if payload matches */
        if (0 != memcmp(&frame.payload, gEthUtilsApp.rxFrame.payload, len))
        {
            EthUtils_printf("test_0003: payload mismatch\r\n");
            status = FAIL;
            break;
        }
    }

    /* Send STOP cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    EthUtils_printf("test_0003: END\r\n");

    return status;
}

boolean EthApp_test_0004(void)
{
    uint32  num = 0U;
    boolean status;

    EthUtils_printf("test_0004: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthUtilsApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0004: failed while receiving frames\r\n");
    }

    EthUtils_printf("test_0004: received %d of %d frames\r\n", gEthUtilsApp.stats.rxExp1PktCnt,
                    ETH_TEST_ITER_M_COUNT / 2);

    if (gEthUtilsApp.stats.rxExp1PktCnt != ETH_TEST_ITER_M_COUNT / 2)
    {
        status = FAIL;
    }

    EthUtils_printf("test_0004: END\r\n");

    return status;
}
#if (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API)

boolean EthApp_test_0005(void)
{
    uint32         num       = ETH_TEST_ITER_M_COUNT;
    uint32         acceptCnt = num / 2;
    boolean        itStatus;
    boolean        status = PASS;
    Std_ReturnType retVal;

    EthUtils_printf("test_0005: START\r\n");

    /* Part 1: Reset filter and receive frames with controller's address */
    retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, NullAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthUtilsApp.stats.filterNullErr++;
    }
    /* Subscribe to spl mcast address used by host app to send mcast frames.
     * HostApp sends mcast frames with non-broadcast address so that
     * broadcast frames in network from Host PC/other machines on network
     * get routed to target test app inadvertently
     */
    if (E_OK == retVal)
    {
        retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);
    }

    gEthUtilsApp.stats.rxExp1PktCnt = 0U;
    gEthUtilsApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthUtilsApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) || (gEthUtilsApp.stats.rxExp1PktCnt != acceptCnt) || (gEthUtilsApp.stats.rxExp2PktCnt != 0U))
    {
        gEthUtilsApp.stats.filterNullRxErr++;
    }

    EthUtils_printf("test_0005:  Null: Exp1: exp %3d, got %3d\r\n", acceptCnt, gEthUtilsApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005:  Null: Exp2: exp %3d, got %3d\r\n", 0U, gEthUtilsApp.stats.rxExp2PktCnt);

    /* Part 2: Add unicast address and receive frames with that address */
    retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, UcastAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthUtilsApp.stats.filterUcastAddErr++;
    }

    gEthUtilsApp.stats.rxExp1PktCnt = 0U;
    gEthUtilsApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthUtilsApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) || (gEthUtilsApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthUtilsApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthUtilsApp.stats.filterUcastRxErr++;
    }

    EthUtils_printf("test_0005: Ucast: Exp1: exp %3d, got %3d\r\n", acceptCnt, gEthUtilsApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005: Ucast: Exp2: exp %3d, got %3d\r\n", acceptCnt, gEthUtilsApp.stats.rxExp2PktCnt);

    /* Part 3: Add multicast address and receive frames with that address */
    retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, McastAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthUtilsApp.stats.filterMcastAddErr++;
    }

    gEthUtilsApp.stats.rxExp1PktCnt = 0U;
    gEthUtilsApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthUtilsApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) || (gEthUtilsApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthUtilsApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthUtilsApp.stats.filterMcastRxErr++;
    }

    EthUtils_printf("test_0005: Mcast: Exp1: exp %3d, got %3d\r\n", acceptCnt, gEthUtilsApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005: Mcast: Exp2: exp %3d, got %3d\r\n", acceptCnt, gEthUtilsApp.stats.rxExp2PktCnt);

    /* Part 4: Remove multicast address and receive frames with that address */
    retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, McastAddr, ETH_REMOVE_FROM_FILTER);
    if (E_OK != retVal)
    {
        gEthUtilsApp.stats.filterMcastRemErr++;
    }

    gEthUtilsApp.stats.rxExp1PktCnt = 0U;
    gEthUtilsApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthUtilsApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) || (gEthUtilsApp.stats.rxExp1PktCnt != acceptCnt) || (gEthUtilsApp.stats.rxExp2PktCnt != 0U))
    {
        gEthUtilsApp.stats.filterMcastRxErr++;
    }

    EthUtils_printf("test_0005: Mcast: Exp1: exp %3d, got %3d\r\n", acceptCnt, gEthUtilsApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005: Mcast: Exp2: exp %3d, got %3d\r\n", 0U, gEthUtilsApp.stats.rxExp2PktCnt);

    /* Part 5: Add broadcast address and receive/send frames with any address */
    retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, BcastAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthUtilsApp.stats.filterBcastErr++;
    }

    gEthUtilsApp.stats.rxExp1PktCnt = 0U;
    gEthUtilsApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthUtilsApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) || (gEthUtilsApp.stats.rxExp1PktCnt != acceptCnt) ||
        (gEthUtilsApp.stats.rxExp2PktCnt != acceptCnt))
    {
        gEthUtilsApp.stats.filterBcastRxErr++;
    }

    EthUtils_printf("test_0005: Bcast: Exp1: exp %3d, got %3d\r\n", gEthUtilsApp.stats.rxExp1PktCnt, acceptCnt);
    EthUtils_printf("test_0005: Bcast: Exp2: exp %3d, got %3d\r\n", gEthUtilsApp.stats.rxExp2PktCnt, acceptCnt);

    /* Part 6: Reset filter and receive frames with controller's address */
    retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, NullAddr, ETH_ADD_TO_FILTER);
    if (E_OK != retVal)
    {
        gEthUtilsApp.stats.filterNullErr++;
    }
    /* Subscribe to spl mcast address used by host app to send mcast frames.
     * HostApp sends mcast frames with non-broadcast address so that
     * broadcast frames in network from Host PC/other machines on network
     * get routed to target test app inadvertently
     */
    if (E_OK == retVal)
    {
        retVal = Eth_UpdatePhysAddrFilter(gEthUtilsApp.ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);
    }
    if (E_OK != retVal)
    {
        gEthUtilsApp.stats.filterNullErr++;
    }

    gEthUtilsApp.stats.rxExp1PktCnt = 0U;
    gEthUtilsApp.stats.rxExp2PktCnt = 0U;
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    itStatus = EthApp_receive(gEthUtilsApp.ctrlIdx, 0U);
    if ((FAIL == itStatus) || (gEthUtilsApp.stats.rxExp1PktCnt != acceptCnt) || (gEthUtilsApp.stats.rxExp2PktCnt != 0U))
    {
        gEthUtilsApp.stats.filterNullRxErr++;
    }

    EthUtils_printf("test_0005:  Null: Exp1: exp %3d, got %3d\r\n", acceptCnt, gEthUtilsApp.stats.rxExp1PktCnt);
    EthUtils_printf("test_0005:  Null: Exp2: exp %3d, got %3d\r\n", 0U, gEthUtilsApp.stats.rxExp2PktCnt);

    /* Check error conditions */
    if ((gEthUtilsApp.stats.filterUcastAddErr > 0U) || (gEthUtilsApp.stats.filterUcastRemErr > 0U) ||
        (gEthUtilsApp.stats.filterUcastRxErr > 0U) || (gEthUtilsApp.stats.filterMcastAddErr > 0U) ||
        (gEthUtilsApp.stats.filterMcastRemErr > 0U) || (gEthUtilsApp.stats.filterMcastRxErr > 0U) ||
        (gEthUtilsApp.stats.filterBcastErr > 0U) || (gEthUtilsApp.stats.filterBcastRxErr > 0U) ||
        (gEthUtilsApp.stats.filterNullErr > 0U) || (gEthUtilsApp.stats.filterNullRxErr > 0U) ||
        (gEthUtilsApp.stats.detErr > 0U) || (gEthUtilsApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthUtilsApp.verbose))
    {
        EthUtils_printf("Filter Test Results:\r\n");
        EthUtils_printf("  Status:                %s\r\n", status ? "Pass" : "Fail");
        EthUtils_printf("  Sent from host:        %d\r\n", num);
        EthUtils_printf("  Unicast ADD errors:    %d\r\n", gEthUtilsApp.stats.filterUcastAddErr);
        EthUtils_printf("  Ucast REMOVE errors:   %d\r\n", gEthUtilsApp.stats.filterUcastRemErr);
        EthUtils_printf("  Ucast receive errors:  %d\r\n", gEthUtilsApp.stats.filterUcastRxErr);
        EthUtils_printf("  Mcast ADD errors:      %d\r\n", gEthUtilsApp.stats.filterMcastAddErr);
        EthUtils_printf("  Mcast REMOVE errors:   %d\r\n", gEthUtilsApp.stats.filterMcastRemErr);
        EthUtils_printf("  Mcast receive errors:  %d\r\n", gEthUtilsApp.stats.filterMcastRxErr);
        EthUtils_printf("  Bcast ADD errors:      %d\r\n", gEthUtilsApp.stats.filterBcastErr);
        EthUtils_printf("  Bcast receive errors:  %d\r\n", gEthUtilsApp.stats.filterBcastRxErr);
        EthUtils_printf("  Null ADD errors:       %d\r\n", gEthUtilsApp.stats.filterNullErr);
        EthUtils_printf("  Null receive errors:   %d\r\n", gEthUtilsApp.stats.filterNullRxErr);
        EthUtils_printf("  DEM errors:            %d\r\n", gEthUtilsApp.stats.demErr);
        EthUtils_printf("  DET errors:            %d\r\n", gEthUtilsApp.stats.detErr);
        EthUtils_printf("\r\n");
    }

    EthUtils_printf("test_0005: END\r\n");

    return status;
}
#endif /* (STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER_API) */

boolean EthApp_test_0006(void)
{
    uint32  iterations     = ETH_TEST_ITER_M_COUNT;
    uint16  len            = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan           = FALSE;
    boolean status;

    EthUtils_printf("test_0006: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames with txConfirmation enabled */
    status = EthApp_transmit(gEthUtilsApp.ctrlIdx, iterations, len, txConfirmation, vlan, ETH_DEFAULT_TX_PRIORITY,
                             &BcastAddr[0U]);

    EthUtils_printf("test_0006: END\r\n");

    return status;
}

boolean EthApp_test_0007(void)
{
    uint32  iterations     = ETH_TEST_ITER_M_COUNT;
    uint16  len            = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan           = TRUE;
    boolean status;

    EthUtils_printf("test_0007: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit VLAN tagged frames with txConfirmation enabled */
    status = EthApp_transmit(gEthUtilsApp.ctrlIdx, iterations, len, txConfirmation, vlan, ETH_DEFAULT_TX_PRIORITY,
                             &BcastAddr[0U]);

    EthUtils_printf("test_0007: END\r\n");

    return status;
}

boolean EthApp_test_0008(void)
{
    uint32  iterations = ETH_TEST_ITER_S_COUNT;
    uint16  len;
    boolean txConfirmation = TRUE;
    boolean vlan           = FALSE;
    boolean st;
    boolean status = PASS;

    EthUtils_printf("test_0008: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames of different lengths */
    for (len = 10U; len <= 1500U; len += 10U)
    {
        st = EthApp_transmit(gEthUtilsApp.ctrlIdx, iterations, len, txConfirmation, vlan, ETH_DEFAULT_TX_PRIORITY,
                             &BcastAddr[0U]);
        if (st == FAIL)
        {
            EthUtils_printf("test_0008: failed to transmit frames of length %u\r\n", len);
            status = FAIL;
        }

        /* Add delay per test case */
        EthApp_delay(10U);
    }

    EthUtils_printf("test_0008: END\r\n");

    return status;
}

boolean EthApp_test_0009(void)
{
    uint32  num = 0U;
    boolean status;

    EthUtils_printf("test_0009: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthUtilsApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0009: failed while receiving frames\r\n");
    }

    EthUtils_printf("test_0009: received %d of %d frames\r\n", gEthUtilsApp.stats.rxVlanPktCnt, ETH_TEST_ITER_M_COUNT);

    if (gEthUtilsApp.stats.rxVlanPktCnt != ETH_TEST_ITER_M_COUNT)
    {
        EthUtils_printf("test_0009: received frame count ` (exp=%d, got=%d)\r\n", ETH_TEST_ITER_M_COUNT,
                        gEthUtilsApp.stats.rxVlanPktCnt);
        status = FAIL;
    }

    EthUtils_printf("test_0009: END\r\n");

    return status;
}

const char *EthApp_GetCtrlModeString(Eth_ModeType ControllerMode)
{
    if (ETH_MODE_DOWN == ControllerMode)
    {
        return "DOWN";
    }
    else if (ETH_MODE_ACTIVE == ControllerMode)
    {
        return "ACTIVE";
    }
    else
    {
        return "INVALID";
    }
}

boolean EthApp_test_0010(void)
{
    uint32         iterations = ETH_TEST_ITER_S_COUNT;
    uint32         i;
    boolean        status = PASS;
    Std_ReturnType retVal;
    Eth_ModeType   CtrlMode;

    EthUtils_printf("test_0010: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthUtilsApp.verbose)
        {
            EthUtils_printf("test_0010: iteration %d\r\n", i + 1);
        }

        EthUtils_printf("Set CtrlMode DOWN\r\n");
        /* Set controller to down state */
        retVal = EthApp_SetControllerMode(gEthUtilsApp.ctrlIdx, ETH_MODE_DOWN);
        if (E_OK != retVal)
        {
            EthUtils_printf("test_0010: failed to set down mode\r\n");
            gEthUtilsApp.stats.ctrlModeErr++;
        }
        else
        {
            gEthUtilsApp.stats.ctrlModeActCnt++;
        }

        /*Get controller to down state */
        retVal = EthApp_GetControllerMode(gEthUtilsApp.ctrlIdx, &CtrlMode);
        if (E_OK != retVal)
        {
            EthUtils_printf("test_0010: failed to get control mode\r\n");
            gEthUtilsApp.stats.ctrlModeErr++;
        }
        else
        {
            EthUtils_printf("Get CtrlMode %s\r\n", EthApp_GetCtrlModeString(CtrlMode));
        }

        Eth_MainFunction();

        EthUtils_printf("Set CtrlMode ACTIVE\r\n");
        /* Set controller back to active state */
        retVal = EthApp_SetControllerMode(gEthUtilsApp.ctrlIdx, ETH_MODE_ACTIVE);
        if (E_OK != retVal)
        {
            EthUtils_printf("test_0010: failed to set active mode\r\n");
            gEthUtilsApp.stats.ctrlModeErr++;
        }
        else
        {
            gEthUtilsApp.stats.ctrlModeDownCnt++;
        }

        /*Get controller to down state */
        retVal = EthApp_GetControllerMode(gEthUtilsApp.ctrlIdx, &CtrlMode);
        if (E_OK != retVal)
        {
            EthUtils_printf("test_0010: failed to get down mode\r\n");
            gEthUtilsApp.stats.ctrlModeErr++;
        }
        else
        {
            EthUtils_printf("Get CtrlMode %s\r\n", EthApp_GetCtrlModeString(CtrlMode));
        }

        Eth_MainFunction();

        /* Check error conditions */
        if ((gEthUtilsApp.stats.ctrlModeDownCnt == 0U) || (gEthUtilsApp.stats.ctrlModeActCnt == 0U) ||
            (gEthUtilsApp.stats.ctrlModeErr > 0U) ||
            (gEthUtilsApp.stats.ctrlModeIndDownCnt != gEthUtilsApp.stats.ctrlModeDownCnt) ||
            (gEthUtilsApp.stats.ctrlModeIndActCnt != gEthUtilsApp.stats.ctrlModeActCnt) ||
            (gEthUtilsApp.stats.ctrlModeIndErr > 0U) || (gEthUtilsApp.stats.detErr > 0U) ||
            (gEthUtilsApp.stats.demErr > 0U))
        {
            status = FAIL;
        }

        if ((FAIL == status) || (TRUE == gEthUtilsApp.verbose))
        {
            EthUtils_printf("Controller Mode Test Results:\r\n");
            EthUtils_printf("  Status:                   %s\r\n", status ? "Pass" : "Fail");
            EthUtils_printf("  Requested:                %d\r\n", iterations);
            EthUtils_printf("  Changes to DOWN mode:     %d\r\n", gEthUtilsApp.stats.ctrlModeDownCnt);
            EthUtils_printf("  Changes to ACTIVE mode:   %d\r\n", gEthUtilsApp.stats.ctrlModeActCnt);
            EthUtils_printf("  Mode change errors:       %d\r\n", gEthUtilsApp.stats.ctrlModeErr);
            EthUtils_printf("  Indicated DOWN changes:   %d\r\n", gEthUtilsApp.stats.ctrlModeIndDownCnt);
            EthUtils_printf("  Indicated ACTIVE changes: %d\r\n", gEthUtilsApp.stats.ctrlModeIndActCnt);
            EthUtils_printf("  Indication errors:        %d\r\n", gEthUtilsApp.stats.ctrlModeIndErr);
            EthUtils_printf("\r\n");
        }

        if (FAIL == status)
        {
            EthUtils_printf("test_0010: failed to change controller mode\r\n");
            break;
        }

        /* Transmit frames */
        status = EthApp_test_0002();
        if (FAIL == status)
        {
            EthUtils_printf("test_0010: failed to transmit frames\r\n");
        }

        /* Receive frames */
        status = EthApp_test_0001();
        if (FAIL == status)
        {
            EthUtils_printf("test_0010: failed to receive frames\r\n");
        }
    }

    EthUtils_printf("test_0010: completed %d of %d iterations\r\n", i, iterations);
    EthUtils_printf("test_0010: END\r\n");

    return status;
}

boolean EthApp_test_0011(void)
{
    uint32  iterations     = ETH_TEST_ITER_M_COUNT;
    uint16  len            = 1500U;
    boolean txConfirmation = TRUE;
    boolean vlan           = FALSE;
    boolean status         = true;

    EthUtils_printf("test_0011: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Transmit frames */
    status = EthApp_transmit(gEthUtilsApp.ctrlIdx, iterations, len, txConfirmation, vlan, ETH_DEFAULT_TX_PRIORITY,
                             &TxMcastAddr[0U]);

    EthUtils_printf("test_0011: END\r\n");

    return status;
}

boolean EthApp_test_0012(void)
{
    uint16  expectedFrame = ETH_TEST_ITER_S_COUNT;
    uint32  num           = 0U, t;
    boolean status;

    EthUtils_printf("test_0012: START\r\n");

    gEthUtilsApp.checkSumTest = TRUE;
    for (t = 0u; t < 4u; ++t)
    {
        gEthUtilsApp.stats.rxIpChecksumCnt = 0u;
        /* Send START cmd */
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

        /* Receive frames until STOP cmd is detected */
        status = EthApp_receive(gEthUtilsApp.ctrlIdx, num);
        if (FAIL == status)
        {
            EthUtils_printf("test_0012: failed while receiving frames\r\n");
            break;
        }

        if (gEthUtilsApp.stats.rxIpChecksumCnt != expectedFrame)
        {
            EthUtils_printf("test_0012: received frame count mismatch (exp=%d, got=%d)\r\n", expectedFrame,
                            gEthUtilsApp.stats.rxIpChecksumCnt);
            status = FAIL;
        }
    }

    gEthUtilsApp.checkSumTest = FALSE;

    EthUtils_printf("test_0012: END\r\n");

    return status;
}

boolean EthApp_test_0013(void)
{
    uint32                      iterations  = ETH_TEST_ITER_S_COUNT;
    uint16                      len         = ETH_CHECKSUM_PAYLOAD_LEN;
    uint8                       vlan_enable = 0u;
    boolean                     status      = PASS;
    uint32                      i = 0U, t = 0U;
    uint8                      *bufPtr;
    Eth_BufIdxType              bufIdx;
    VlanDataFramePayload       *vlanPtr;
    Eth_FrameType               etherType = ETHERTYPE_IPV4;
    uint16                      vid       = 1000;
    uint16                      pcp       = 5;
    extern Eth_ChecksumTestType Eth_CheckSumList[4u];

    EthUtils_printf("test_0013: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    for (vlan_enable = 0; vlan_enable < 2u; vlan_enable++)
    {
        for (t = 0u; t < 4u; ++t)
        {
            len = vlan_enable ? (ETH_CHECKSUM_PAYLOAD_LEN + ETH_VLAN_TAG_LEN) : ETH_CHECKSUM_PAYLOAD_LEN;
            for (i = 0; i < iterations; ++i)
            {
                (void)EthApp_provideTxBuffer(gEthUtilsApp.ctrlIdx, ETH_DEFAULT_TX_PRIORITY, &bufIdx, &bufPtr, &len);

                if (vlan_enable == 1u)
                {
                    vlanPtr            = (VlanDataFramePayload *)bufPtr;
                    vlanPtr->tci       = htons((pcp << 13) | vid);
                    vlanPtr->etherType = htons(Eth_CheckSumList[t].proto);
                    memcpy((void *)(&vlanPtr->payload), (void *)Eth_CheckSumList[t].payload, ETH_CHECKSUM_PAYLOAD_LEN);
                    etherType = ETHERTYPE_VLAN_TAG;
                }
                else
                {
                    etherType = Eth_CheckSumList[t].proto;
                    memcpy(bufPtr, (void *)Eth_CheckSumList[t].payload, ETH_CHECKSUM_PAYLOAD_LEN);
                }

                (void)EthApp_Transmit(gEthUtilsApp.ctrlIdx, bufIdx, (Eth_FrameType)etherType, TRUE, len, BcastAddr);

                EthApp_delay(100);
            }
        }
    }

    EthUtils_printf("test_0013: END\r\n");

    return status;
}
boolean EthApp_test_0200(void)
{
    uint32   iterations = ETH_TEST_ITER_M_COUNT;
    uint32   i;
    sint32   fillStatus;
    uint16   len    = 1500U;
    boolean  status = TRUE;
    EthFrame frame;

    EthUtils_printf("test_0200: START\r\n");
    EthPsEnterLoopback(EthConfigSet_EthCtrlConfig_0.portIdx,
                       EthConfigSet_EthCtrlConfig_0.portCfg.macCfg.macConnectionType);

    /* Initialize frame header */
    memcpy(frame.hdr.dstMac, BcastAddr, ETH_MAC_ADDR_LEN);
    memcpy(frame.hdr.srcMac, gEthUtilsApp.macAddr, ETH_MAC_ADDR_LEN);
    frame.hdr.etherType = ETHERTYPE_EXPERIMENTAL1;

    /* Send and receive frames */
    for (i = 0U; i < iterations; i++)
    {
        if (TRUE == gEthUtilsApp.verbose)
        {
            EthUtils_printf("test_0200: iteration %d\r\n", i);
        }

        gEthUtilsApp.saveRxFrame       = TRUE;
        gEthUtilsApp.stats.rxPktCnt    = 0U;
        gEthUtilsApp.stats.rxPktIndCnt = 0U;

        fillStatus = EthUtils_fillPayload((DataFramePayload *)frame.payload, i % ETH_TEST_NUM_TYPES, len);
        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthUtils_printf("test_0200: failed to fill test packet\r\n");
            status = FAIL;
            break;
        }

        /* Send the frame */
        EthApp_send(gEthUtilsApp.ctrlIdx, &frame, len, ETH_DEFAULT_TX_PRIORITY);

        /* Wait for Rx frames */
        while (0 == gEthUtilsApp.stats.rxPktIndCnt)
        {
            if (gEthUtilsApp.rxIrqDisable)
            {
                EthApp_receiveAllFifo(gEthUtilsApp.ctrlIdx);
            }
        }

        /* Check if EtherType field matches */
        if (frame.hdr.etherType != gEthUtilsApp.rxFrame.hdr.etherType)
        {
            EthUtils_printf("test_0200: EtherType mismatch (exp=0x%04x, got=0x%04x)\r\n", frame.hdr.etherType & 0xFFFFU,
                            gEthUtilsApp.rxFrame.hdr.etherType & 0xFFFFU);
            status = FAIL;
            break;
        }

        /* Check if payload matches */
        if (0 != memcmp(&frame.payload, gEthUtilsApp.rxFrame.payload, len))
        {
            EthUtils_printf("test_0200: payload mismatch\r\n");
            status = FAIL;
            break;
        }
    }

    EthUtils_printf("test_0200: completed %d of %d iterations\r\n", i, iterations);
    EthUtils_printf("test_0200: END\r\n");

    return status;
}

boolean EthApp_test_0300(void)
{
    uint32  i, j, iterations = ETH_TEST_ITER_S_COUNT;
    uint32  delays_msec[ETH_TEST_ITER_S_COUNT] = {31u, 62u, 125u, 250u, 500u, 750u, 1000u, 2000u, 5000u, 1000u};
    uint16  len                                = sizeof(ptpSyncPayload);
    boolean status                             = PASS;
    BufReq_ReturnType bufStatus;
    Eth_BufIdxType    bufIdx;
    sint64            diffTs = 0;
    uint8            *bufPtr;

    EthUtils_printf("test_0300: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    gEthUtilsApp.saveTxTime = 1u;
    gEthUtilsApp.txFrameCnt = 0u;
    for (i = 0; i < iterations; ++i)
    {
        gEthUtilsApp.saveTxTimeStamp[i].seconds     = 0U;
        gEthUtilsApp.saveTxTimeStamp[i].secondsHi   = 0U;
        gEthUtilsApp.saveTxTimeStamp[i].nanoseconds = 0U;
    }

    for (i = 0; i < iterations; ++i)
    {
        bufStatus = EthApp_provideTxBuffer(gEthUtilsApp.ctrlIdx, ETH_DEFAULT_TX_PRIORITY, &bufIdx, &bufPtr, &len);

        if (BUFREQ_OK == bufStatus)
        {
            EthUtils_fillPtpSyncPayload((ptpSyncPayload *)bufPtr, gEthUtilsApp.macAddr, (uint16)i);

            EthApp_EnableEgressTimeStamp(gEthUtilsApp.ctrlIdx, bufIdx);

            (void)EthApp_Transmit(gEthUtilsApp.ctrlIdx, bufIdx, (Eth_FrameType)ETHAPP_ETHERTYPE_PTP1588, TRUE, len,
                                  gPtpMcastAddr);

            if (gEthUtilsApp.txIrqDisable)
            {
                EthApp_TxConfirmationInt(gEthUtilsApp.ctrlIdx);
            }

            if (1000U < delays_msec[i])
            {
                for (j = 0; j < (delays_msec[i] / 1000U); j++)
                {
                    EthApp_delay(1000U);
                }
                EthApp_delay((delays_msec[i] % 1000U));
            }
            else
            {
                EthApp_delay(delays_msec[i]);
            }
        }
    }

    /* Send STOP cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    for (i = 0; i < iterations; ++i)
    {
        if (i == 0)
        {
            EthUtils_printf("Egress timestamp %d Ts: %9u %2u %2u\r\n", i, gEthUtilsApp.saveTxTimeStamp[i].nanoseconds,
                            gEthUtilsApp.saveTxTimeStamp[i].seconds, gEthUtilsApp.saveTxTimeStamp[i].secondsHi);
        }
        else
        {
            diffTs = TS_DIFF64NS(gEthUtilsApp.saveTxTimeStamp[i], gEthUtilsApp.saveTxTimeStamp[i - 1]);
            EthUtils_printf("Egress timestamp %d Ts: %9u %2u %2u [Exp: %.9f Actual: %.9f]\r\n", i,
                            gEthUtilsApp.saveTxTimeStamp[i].nanoseconds, gEthUtilsApp.saveTxTimeStamp[i].seconds,
                            gEthUtilsApp.saveTxTimeStamp[i].secondsHi, ((float)delays_msec[i - 1] / 1000),
                            ((float)diffTs / SEC_TO_NS));
        }
    }

    gEthUtilsApp.saveTxTime = 0u;
    EthUtils_printf("test_0300: END\r\n");

    return status;
}

boolean EthApp_test_0301(void)
{
    uint32  delays_msec[ETH_TEST_ITER_S_COUNT] = {31u, 62u, 125u, 250u, 500u, 750u, 1000u, 2000u, 5000u, 1000u};
    uint32  num                                = 0U;
    boolean status;
    sint64  diffTs = 0;
    int     i;

    EthUtils_printf("test_0301: START\r\n");

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    gEthUtilsApp.saveRxTime = 1u;
    gEthUtilsApp.rxFrameCnt = 0u;
    for (i = 0; i < ETH_TEST_ITER_S_COUNT; ++i)
    {
        gEthUtilsApp.saveRxTimeStamp[i].seconds     = 0U;
        gEthUtilsApp.saveRxTimeStamp[i].secondsHi   = 0U;
        gEthUtilsApp.saveRxTimeStamp[i].nanoseconds = 0U;
    }

    /* Receive frames until STOP cmd is detected */
    status = EthApp_receive(gEthUtilsApp.ctrlIdx, num);
    if (FAIL == status)
    {
        EthUtils_printf("test_0301: failed while receiving frames\r\n");
    }

    EthUtils_printf("test_0301: received %d of %d frames\r\n", gEthUtilsApp.stats.rxPtpPktCnt, ETH_TEST_ITER_S_COUNT);

    if (gEthUtilsApp.stats.rxPtpPktCnt != ETH_TEST_ITER_S_COUNT)
    {
        EthUtils_printf("test_0301: received frame count mismatch (exp=%d, got=%d)\r\n", ETH_TEST_ITER_S_COUNT,
                        gEthUtilsApp.stats.rxPtpPktCnt);
        status = FAIL;
    }

    for (i = 0; i < ETH_TEST_ITER_S_COUNT; ++i)
    {
        if (i == 0)
        {
            EthUtils_printf("Ingress timestamp %d Ts: %9u %2u %2u\r\n", i, gEthUtilsApp.saveRxTimeStamp[i].nanoseconds,
                            gEthUtilsApp.saveRxTimeStamp[i].seconds, gEthUtilsApp.saveRxTimeStamp[i].secondsHi);
        }
        else
        {
            diffTs = TS_DIFF64NS(gEthUtilsApp.saveRxTimeStamp[i], gEthUtilsApp.saveRxTimeStamp[i - 1]);
            EthUtils_printf("Ingress timestamp %d Ts: %9u %2u %2u [Exp: %.9f Actual: %.9f]\r\n", i,
                            gEthUtilsApp.saveRxTimeStamp[i].nanoseconds, gEthUtilsApp.saveRxTimeStamp[i].seconds,
                            gEthUtilsApp.saveRxTimeStamp[i].secondsHi, ((float)delays_msec[i - 1] / 1000),
                            ((float)diffTs / SEC_TO_NS));
        }
    }
    gEthUtilsApp.saveRxTime = 0u;

    EthUtils_printf("test_0301: END\r\n");

    return status;
}

boolean EthApp_test_0302(void)
{
    uint32                i, iterations = ETH_TEST_ITER_S_COUNT;
    uint16                len      = 1500;
    boolean               status   = PASS;
    Eth_TimeStampQualType timeQual = ETH_INVALID;
    Eth_TimeStampType     tsVal    = {};
    EthFrame              frame;

    EthUtils_printf("test_0302: START\r\n");

    /* Initialize frame header */
    memcpy(frame.hdr.dstMac, BcastAddr, ETH_MAC_ADDR_LEN);
    memcpy(frame.hdr.srcMac, gEthUtilsApp.macAddr, ETH_MAC_ADDR_LEN);
    frame.hdr.etherType = ETHERTYPE_EXPERIMENTAL1;

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    for (i = 0; i < iterations; ++i)
    {
        (void)EthUtils_fillPayload((DataFramePayload *)frame.payload, i % ETH_TEST_NUM_TYPES, len);

        /* Send the frame */
        EthApp_send(gEthUtilsApp.ctrlIdx, &frame, len, ETH_DEFAULT_TX_PRIORITY);

        EthApp_delay(1000u);

        EthApp_GetCurrentTime(gEthUtilsApp.ctrlIdx, &timeQual, &tsVal);

        EthUtils_printf("Current timestamp %d Ts: %9u %2u %2u\r\n", timeQual, tsVal.nanoseconds, tsVal.seconds,
                        tsVal.secondsHi);
    }

    /* Send STOP cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

    EthUtils_printf("test_0302: END\r\n");

    return status;
}
boolean EthApp_test_0100(uint32 frames, uint32 size)
{
    Eth_BufIdxType    bufIdx;
    BufReq_ReturnType bufStatus;
    boolean           txConfirmation = FALSE;
    uint8            *bufPtr;
    uint32            iterations = frames;
    uint32            retryCnt;
    uint32            i;
    uint16            len = size;
    Std_ReturnType    retVal;

    EthUtils_printf("test_0100 frames %d size %d: START\r\n", frames, size);

    /* Send START cmd */
    EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

    /* Send frames */
    for (i = 0U; i < iterations; i++)
    {
        /* Request one buffer */
        bufStatus = EthApp_provideTxBuffer(gEthUtilsApp.ctrlIdx, ETH_DEFAULT_TX_PRIORITY, &bufIdx, &bufPtr, &len);

        /* Transmit it as is (only header is updated) */
        if (BUFREQ_OK == bufStatus)
        {
            retryCnt = txConfirmation ? 0U : ETHAPP_TRANSMIT_RETRY_COUNT;

            do
            {
                retVal = EthApp_Transmit(gEthUtilsApp.ctrlIdx, bufIdx, (Eth_FrameType)ETHERTYPE_EXPERIMENTAL1,
                                         txConfirmation, len, BcastAddr);
                if (E_OK == retVal)
                {
                    break;
                }

                if (retryCnt > 0U)
                {
                    EthApp_delay(1U);
                    retryCnt--;
                }
                else
                {
                    break;
                }
            } while (TRUE);

            if (E_OK != retVal)
            {
                EthUtils_printf("test_0100: failed to send buffer\r\n");
            }
            else
            {
                if (gEthUtilsApp.txIrqDisable)
                {
                    EthApp_TxConfirmationInt(gEthUtilsApp.ctrlIdx);
                }
            }
        }
        else
        {
            EthUtils_printf("test_0100: failed to get TX buffer: %d\r\n", (int)bufStatus);
        }
    }

    /* Send STOP cmd 10x to prevent lost,
     * receiver app will handle flushing the extra STOP cmd */
    for (i = 0U; i < ETH_TEST_ITER_S_COUNT; i++)
    {
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_STOP);
    }

    EthUtils_printf("test_0100: %d frames size %d\r\n", i, size);
    EthUtils_printf("test_0100: END\r\n");

    return PASS;
}

boolean EthApp_test_0110(void)
{
    uint16  txPktSizeMesure[] = {1500u, 512u, 256u, 128u, 64u};
    uint32  iterator_num[]    = {150000u, 150000u, 150000u, 150000u, 150000u};
    boolean status            = PASS;
    uint32  i;

    EthUtils_printf("test_0110: START\r\n");
    for (i = 0; i < sizeof(txPktSizeMesure) / sizeof(uint16); ++i)
    {
        (void)EthApp_test_0100(iterator_num[i], txPktSizeMesure[i]);
        EthApp_transmitFlush(gEthUtilsApp.ctrlIdx);
        EthApp_delay(2000u); /* More delay to sync with slow host */
    }

    EthUtils_printf("test_0110: DONE\r\n");
    return status;
}

#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
boolean EthApp_test_0400_Helper(uint16 type, uint8 pcp, uint16 vid, uint16 etherType)
{
    Eth_BufIdxType    bufIdx;
    BufReq_ReturnType bufStatus;
    boolean           txConfirmation = FALSE;
    uint8            *bufPtr;
    uint32            iterations = 15000;
    uint32            retryCnt;
    uint32            i;
    uint16            len    = 1500U;
    Std_ReturnType    retVal = E_NOT_OK;

    /* Send frames */
    for (i = 0U; i < iterations; i++)
    {
        /* Request one buffer */
        bufStatus = EthApp_provideTxBuffer(gEthUtilsApp.ctrlIdx, ETH_DEFAULT_TX_PRIORITY, &bufIdx, &bufPtr, &len);

        /* Transmit it as is (only header is updated) */
        if (BUFREQ_OK == bufStatus)
        {
            EthUtils_fillVlanHdr((VlanDataFramePayload *)bufPtr, type, len, pcp, vid, etherType);

            retryCnt = txConfirmation ? 0U : ETHAPP_TRANSMIT_RETRY_COUNT;

            do
            {
                retVal = EthApp_Transmit(gEthUtilsApp.ctrlIdx, bufIdx, (Eth_FrameType)ETHERTYPE_VLAN_TAG,
                                         txConfirmation, len, BcastAddr);
                if (E_OK == retVal)
                {
                    break;
                }

                if (retryCnt > 0U)
                {
                    EthApp_delay(1U);
                    retryCnt--;
                }
                else
                {
                    break;
                }
            } while (TRUE);

            if (E_OK != retVal)
            {
                EthUtils_printf("test_0400: failed to send buffer\r\n");
            }
            else
            {
                if (gEthUtilsApp.txIrqDisable)
                {
                    EthApp_TxConfirmationInt(gEthUtilsApp.ctrlIdx);
                }
            }
        }
        else
        {
            EthUtils_printf("test_0400: failed to get TX buffer: %d\r\n", (int)bufStatus);
        }
    }

    return PASS;
}

#define TEST_PRIO_NUM             (8u)
#define TEST_BANDWIDTH_PRIO_0_BPS (10000000) /*10mbps*/
#define TEST_BANDWIDTH_PRIO_1_BPS (20000000) /*20mbps*/
#define TEST_BANDWIDTH_PRIO_2_BPS (30000000) /*30mbps*/
#define TEST_BANDWIDTH_PRIO_3_BPS (40000000) /*40mbps*/
#define TEST_BANDWIDTH_PRIO_4_BPS (50000000) /*50mbps*/
#define TEST_BANDWIDTH_PRIO_5_BPS (60000000) /*60mbps*/
#define TEST_BANDWIDTH_PRIO_6_BPS (70000000) /*70mbps*/
#define TEST_BANDWIDTH_PRIO_7_BPS (80000000) /*80mbps*/

uint32 Test_RateLimit[TEST_PRIO_NUM] = {
    TEST_BANDWIDTH_PRIO_0_BPS, TEST_BANDWIDTH_PRIO_1_BPS, TEST_BANDWIDTH_PRIO_2_BPS, TEST_BANDWIDTH_PRIO_3_BPS,
    TEST_BANDWIDTH_PRIO_4_BPS, TEST_BANDWIDTH_PRIO_5_BPS, TEST_BANDWIDTH_PRIO_6_BPS, TEST_BANDWIDTH_PRIO_7_BPS,
};

boolean EthApp_test_0400(void)
{
    uint32 bandwidth;
    int    i;

    for (i = TEST_PRIO_NUM - 1; i >= 0; i--)
    {
        Eth_SetBandwidthLimit(gEthUtilsApp.ctrlIdx, TEST_PRIO_NUM - 1, Test_RateLimit[i]);

        EthUtils_printf("test_0400: START %d\r\n", i);

        /* Send START cmd */
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

        EthApp_test_0400_Helper(ETH_TEST_TYPE_PATTERN_1, TEST_PRIO_NUM - 1, ETH_TEST_VLAN_VID, ETHERTYPE_EXPERIMENTAL1);

        /* Send STOP cmd */
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_STOP);

        Eth_GetBandwidthLimit(gEthUtilsApp.ctrlIdx, TEST_PRIO_NUM - 1, &bandwidth);
        EthUtils_printf("test_0400 bandwidth %u: END\r\n", bandwidth);

        /* Flush pending rx packet */
        EthApp_flushRecvQueue(gEthUtilsApp.ctrlIdx);
    }

    Eth_SetBandwidthLimit(gEthUtilsApp.ctrlIdx, TEST_PRIO_NUM - 1, 0U);

    return PASS;
}
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

static boolean EthApp_receiveTputHelper(uint8 ctrlIdx, uint32 num)
{
    boolean status = PASS;

    /* Reset test counters */
    gEthUtilsApp.stats.rxPktCnt       = 0U;
    gEthUtilsApp.stats.rxExp3BytesCnt = 0U;
    gEthUtilsApp.stats.rxExp3PktCnt   = 0U;
    gEthUtilsApp.stats.rxExp1PktCnt   = 0U;
    gEthUtilsApp.stats.rxExp2PktCnt   = 0U;
    gEthUtilsApp.stats.rxVlanPktCnt   = 0U;
    gEthUtilsApp.stats.rxPktNotRecv   = 0U;
    gEthUtilsApp.stats.rxPktIndCnt    = 0U;
    gEthUtilsApp.stats.rxEtherTypeErr = 0U;
    gEthUtilsApp.stats.rxPayloadErr   = 0U;
    gEthUtilsApp.stats.rxCtrlIdxErr   = 0U;
    gEthUtilsApp.stats.detErr         = 0U;
    gEthUtilsApp.stats.demErr         = 0U;

    gEthUtilsApp.runTest = TRUE;

    /* Wait for Rx frames */
    while (gEthUtilsApp.runTest)
    {
        if (gEthUtilsApp.rxIrqDisable)
        {
            EthApp_receiveAllFifo(ctrlIdx);
        }
    }

    return status;
}

boolean EthApp_receiveTput(uint32 frames, uint16 pktLen)
{
    TickType t0;
    TickType elapsed_tick;
    float32  elapsed;
    float32  pps;
    float32  mbps;
    uint32   rxframes;
    uint32   rxbytecnt;

    GetCounterValue(0, &t0);

    (void)EthApp_receiveTputHelper(gEthUtilsApp.ctrlIdx, frames);

    /* Get the "end" timestamp after DUT is done sending frames */
    GetElapsedValue(0, &t0, &elapsed_tick);
    elapsed = (float32)elapsed_tick / (1000U * OS_TIME_SCALE_VALUE);

    /* Send SYN ACK to notify Host that we received the STOP cmd */
    EthApp_notifyCmdRecv(gEthUtilsApp.ctrlIdx);

    rxframes  = gEthUtilsApp.stats.rxExp3PktCnt;
    rxbytecnt = gEthUtilsApp.stats.rxExp3BytesCnt;

    /* Compute elapsed time, packets per second and Mbps */
    pps  = (float32)rxframes / elapsed;
    mbps = (float32)rxbytecnt * 8 / elapsed / 1000000;

    EthUtils_printf("receiveTput-%d: received %d frames in %.2f secs (%.2f frames/s, %.2f Mbps) Lost %d\r\n", pktLen,
                    rxframes, elapsed, pps, mbps, (frames - rxframes));
    ;

    return PASS;
}

boolean EthApp_test_0101(void)
{
    uint32  frames            = 150000;
    uint16  rxPktSizeMesure[] = {1500u, 512u, 256u, 128u, 64u};
    uint32  iterator_num[]    = {150000u, 150000u, 150000u, 300000u, 300000u};
    boolean status;
    uint32  i;

    /* set rx interupt to lower than tick irq, to get correct tick */
    /* BoardUtils_setClockPIsrPrio(0u); */

    EthUtils_printf("test_0101: START\r\n");
    for (i = 0; i < sizeof(rxPktSizeMesure) / sizeof(uint16); ++i)
    {
        frames = iterator_num[i];

        /* Send START cmd */
        EthApp_delay(1000U);
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

        /* Receive packets and measure the throughput */
        status = EthApp_receiveTput(frames, rxPktSizeMesure[i]);
        if (status == FAIL)
        {
            EthUtils_printf("test_0101: failed to get receive throughput\n");
        }

        /* Host may send multiple STOP packet, so try to clear that packet */
        EthApp_flushRecvQueue(gEthUtilsApp.ctrlIdx);
    }
    EthUtils_printf("test_0101: END\r\n");

    /* reset tick irq to orignal value */
    /* BoardUtils_setClockPIsrPrio(15u); */

    return status;
}

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
boolean EthApp_test_0500(void)
{
    Std_ReturnType retVal     = E_OK;
    uint8          trcvIdx    = EthTrcvConfigSet_EthTrcvConfig_0.trcvIdx;
    uint32         iterations = 100;
    uint32         i;

    EthUtils_printf("test_0500: START\r\n");

    for (i = 0U; i < iterations; i++)
    {
        /* Get Tranceiver Link State */
        retVal = EthApp_getTranceiverLinkState(trcvIdx);
        if (E_OK == retVal)
        {
            /* check Link State every 1 sec */
            EthApp_delay(1000U);
        }
        else
        {
            EthUtils_printf("test_0500: Read Transceiver Link State Failed\r\n");
            break;
        }
    }

    EthUtils_printf("test_0500: END\r\n");
    return (E_OK == retVal) ? PASS : FAIL;
}
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */

/* Tx IRQ pacing test */
boolean EthApp_test_0201(void)
{
    uint32          testFrames = 150000U;
    uint16          testSize   = 512U;
    /* test TX IRQ pacing value incremental */
    uint32          testTxPaceValue[] = {1U, 2U, 4U, 8U, 16U, 24U, 32U, 48U, 63U};
    uint32          testIdx           = 0U;
    boolean         status            = TRUE;
    Eth_ConfigType *pEthConfigPtr;
    Eth_BufIdxType  bufIdx;
    boolean         txConfirmation = TRUE;
    uint8          *bufPtr;
    uint32          sentFrames = 0U;
    Std_ReturnType  retVal;
    TickType        t0;
    TickType        elapsed_tick;
    TickType        elapsed_ms;
    uint32          estimateTxPace   = 0U;
    uint32          lastEstimatePace = 0U;

    EthUtils_printf("test_0201: START\r\n");
    for (testIdx = 0; testIdx < sizeof(testTxPaceValue) / sizeof(uint32); testIdx++)
    {
        EthUtils_printf("test_0201: configTxPace=%d\r\n", testTxPaceValue[testIdx]);

        /* Configure and reset testing value */
        gEthUtilsApp.testTxIrqPacing    = 1u;
        gEthUtilsApp.IrqTimestampCount  = 0u;
        gEthUtilsApp.stats.txConfPktCnt = 0U;
        gEthUtilsApp.totalIrq           = 0;

        /* Re-Init Eth driver with new TX pacing value */
        pEthConfigPtr = &EthConfigSet_EthCtrlConfig_0;
        Eth_SetControllerMode(pEthConfigPtr->ctrlIdx, ETH_MODE_DOWN);

        pEthConfigPtr->cpdmaCfg.txInterruptsPerMsec = testTxPaceValue[testIdx];
        Eth_DrvStatus                               = ETH_STATE_UNINIT;
#if (STD_ON == ETH_VARIANT_PRE_COMPILE)
        Eth_Init((const Eth_ConfigType *)NULL_PTR);
#else
        Eth_Init(pEthConfigPtr);
#endif /*STD_ON == ETH_VARIANT_PRE_COMPILE)*/

        /* Set the Controller:0 in Active mode */
        retVal = Eth_SetControllerMode(pEthConfigPtr->ctrlIdx, ETH_MODE_ACTIVE);
        if ((Std_ReturnType)E_OK != retVal)
        {
            AppUtils_printf(APP_NAME ": Failed in Eth_SetControllerMode \r\n");
        }

        /* Update MAC address from config */
        Eth_SetPhysAddr(pEthConfigPtr->ctrlIdx, pEthConfigPtr->portCfg.macCfg.macAddr);

        /* Adding a Destination address to the filter */
        Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);

        /* Send START cmd */
        EthApp_delay(1000u);
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

        /* Send frames */
        GetCounterValue(0, &t0);
        sentFrames = 0;
        do
        {
            /* If there's no free TX buffer, Eth driver will try to process packet
             * before pacing time, to test IRQ pacing feature, make sure TX buff always free */
            if (sentFrames - gEthUtilsApp.stats.txConfPktCnt < ETH_NUM_TX_BUFFERS)
            {
                EthApp_provideTxBuffer(gEthUtilsApp.ctrlIdx, ETH_DEFAULT_TX_PRIORITY, &bufIdx, &bufPtr, &testSize);

                /* Transmit it as is (only header is updated) */
                retVal = EthApp_Transmit(gEthUtilsApp.ctrlIdx, bufIdx, (Eth_FrameType)ETHERTYPE_EXPERIMENTAL1,
                                         txConfirmation, testSize, BcastAddr);
                /* Increase sent frames counter */
                sentFrames++;

                if (E_OK != retVal)
                {
                    EthUtils_printf("test_0201: failed to send buffer\r\n");
                }
            }
        } while (sentFrames < testFrames);

        /* Get the "end" timestamp after DUT is done sending frames */
        GetElapsedValue(0, &t0, &elapsed_tick);

        /* Send STOP cmd 10x to prevent lost, receiver app will handle flushing the extra STOP cmd
         */
        EthApp_delay(1000u); /* Delay to sync with slow host */
        for (sentFrames = 0U; sentFrames < ETH_TEST_ITER_S_COUNT; sentFrames++)
        {
            EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_STOP);
            EthApp_delay(20u);
        }

        EthApp_transmitFlush(gEthUtilsApp.ctrlIdx);
        EthApp_delay(1000u); /* More delay to sync with slow host */

        /* Test result */
        elapsed_ms     = elapsed_tick / OS_TIME_SCALE_VALUE;
        estimateTxPace = (gEthUtilsApp.totalIrq * OS_TIME_SCALE_VALUE) / elapsed_tick;

        EthUtils_printf("test_0201: totalIrq=%d elapsed_ms=%d estimateTxPace=%d\r\n", gEthUtilsApp.totalIrq, elapsed_ms,
                        estimateTxPace);

        /* With increasing testTxPaceValue, estimateTxPace must increase, else test failed */
        if (estimateTxPace < lastEstimatePace)
        {
            status = FALSE;
            break;
        }
        lastEstimatePace = estimateTxPace;
    }

    EthUtils_printf("test_0201: DONE\r\n");
    return status;
}

/* Rx IRQ pacing test */
boolean EthApp_test_0202(void)
{
    uint32          testFrames        = 150000U;
    uint32          testRxPaceValue[] = {1U, 2U, 4U, 8U, 16U, 24U, 32U, 48U, 63U};
    uint32_t        testIdx           = 0U;
    boolean         status            = TRUE;
    Eth_ConfigType *pEthConfigPtr;
    Std_ReturnType  retVal;
    TickType        t0;
    TickType        elapsed_tick;
    TickType        elapsed_ms;
    uint32          estimateRxPace   = 0U;
    uint32          lastEstimatePace = 0U;
    uint32          rxFrames         = 0;

    EthUtils_printf("test_0202: START\r\n");
    for (testIdx = 0; testIdx < sizeof(testRxPaceValue) / sizeof(uint32_t); testIdx++)
    {
        EthUtils_printf("test_0202: configRxPace=%d\r\n", testRxPaceValue[testIdx]);

        /* Configure and reset testing value */
        gEthUtilsApp.testRxIrqPacing   = 1u;
        gEthUtilsApp.IrqTimestampCount = 0u;
        gEthUtilsApp.totalIrq          = 0;

        /* Re-Init Eth driver with new RX pacing value */
        pEthConfigPtr = &EthConfigSet_EthCtrlConfig_0;
        Eth_SetControllerMode(pEthConfigPtr->ctrlIdx, ETH_MODE_DOWN);

        pEthConfigPtr->cpdmaCfg.rxInterruptsPerMsec = testRxPaceValue[testIdx];
        /* threshold interrupt also process RX along with pacing IRQ, set 0 to disable */
        pEthConfigPtr->cpdmaCfg.rxThreshCount = 0U;

        Eth_DrvStatus = ETH_STATE_UNINIT;
#if (STD_ON == ETH_VARIANT_PRE_COMPILE)
        Eth_Init((const Eth_ConfigType *)NULL_PTR);
#else
        Eth_Init(pEthConfigPtr);
#endif /*STD_ON == ETH_VARIANT_PRE_COMPILE)*/

        /* Set the Controller:0 in Active mode */
        retVal = Eth_SetControllerMode(pEthConfigPtr->ctrlIdx, ETH_MODE_ACTIVE);
        if ((Std_ReturnType)E_OK != retVal)
        {
            AppUtils_printf(APP_NAME ": Failed in Eth_SetControllerMode \r\n");
        }

        /* Update MAC address from config */
        Eth_SetPhysAddr(pEthConfigPtr->ctrlIdx, pEthConfigPtr->portCfg.macCfg.macAddr);

        /* Adding a Destination address to the filter */
        Eth_UpdatePhysAddrFilter(pEthConfigPtr->ctrlIdx, TargetMcastAddr, ETH_ADD_TO_FILTER);

        /* Send START cmd */
        EthApp_delay(1000u);
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_START);

        /* Receive packets and measure the throughput */
        GetCounterValue(0, &t0);
        (void)EthApp_receiveTputHelper(gEthUtilsApp.ctrlIdx, testFrames);
        GetElapsedValue(0, &t0, &elapsed_tick);

        /* Send SYN ACK to notify Host that we received the STOP cmd */
        EthApp_notifyCmdRecv(gEthUtilsApp.ctrlIdx);

        /* Host may send multiple STOP packet, so try to clear that packet */
        EthApp_flushRecvQueue(gEthUtilsApp.ctrlIdx);
        EthApp_delay(2000U);

        /* Test result */
        elapsed_ms     = elapsed_tick / OS_TIME_SCALE_VALUE;
        estimateRxPace = (gEthUtilsApp.totalIrq * OS_TIME_SCALE_VALUE) / elapsed_tick;
        rxFrames       = gEthUtilsApp.stats.rxExp3PktCnt;

        EthUtils_printf("test_0202: totalIrq=%d elapsed_ms=%d estimateRxPace=%d Lost %d\r\n", gEthUtilsApp.totalIrq,
                        elapsed_ms, estimateRxPace, testFrames - rxFrames);

        /* With increasing testRxPaceValue, estimateRxPace must increase or reach maximum */
        if (estimateRxPace < lastEstimatePace)
        {
            status = FALSE;
            break;
        }
        lastEstimatePace = estimateRxPace;
    }
    EthUtils_printf("test_0202: END\r\n");

    return status;
}

/* =========================Function separator========================= */
void EthIf_CtrlModeIndication(uint8 ControllerId, Eth_ModeType ControllerMode)
{
    EthApp_CtrlModeIndication(ControllerId, ControllerMode);
}

/* =========================Function separator========================= */
void EthIf_TrcvModeIndication(uint8 CtrlIdx, EthTrcv_ModeType TrcvMode)
{
    EthApp_TrcvModeIndication(CtrlIdx, TrcvMode);
}

/* =========================Function separator========================= */
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
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
void EthIf_RxIndication(uint8 ctrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, uint8 *PhysAddrPtr,
                        Eth_DataType *DataPtr, uint16 lenByte)
{
    EthUtilsApp_RxIndication(ctrlIdx, FrameType, IsBroadcast, PhysAddrPtr, DataPtr, lenByte);
}

void EthIf_TxConfirmation(uint8 CtrlIdx, Eth_BufIdxType bufIdx, Std_ReturnType Result)
{
    EthUtilsApp_TxConfirmation(CtrlIdx, bufIdx, Result);
}
