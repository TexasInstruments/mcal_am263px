/*
 *
 * Copyright (C) 2023-2024 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     EthUtils_Target.c
 *
 *  \brief    This file contains Eth ultils target function definitions.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>

#include "Os.h"

#include "Eth.h"
#include "Eth_Irq.h"
#include "EthIf_Cbk.h"
#include "EthTrcv.h"
#include "Eth_Cfg.h"
#include "EthUtils.h"
#include "EthUtils_Target.h"

#include "app_utils.h"
#include "app_utilsEth.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Global Variable Definitions                        */
/* ========================================================================== */

extern EthUtilsApp_State gEthUtilsApp;
extern volatile uint16   EthTrcv_MdioRdVal;

/* ========================================================================== */
/*                         Internel Variable Definitions                      */
/* ========================================================================== */
/* ========================================================================== */
/*                         Local Variable                                     */
/* ========================================================================== */
/* Broadcast MAC address */
static uint8 BcastAddr[ETH_HW_ADDR_LEN] = {0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static boolean EthApp_verifyTxStatus(uint32 num, boolean txConfirmation);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
Std_ReturnType EthApp_deinit(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;

    /* Set controller to down mode */
    retVal = Eth_SetControllerMode(ctrlIdx, ETH_MODE_DOWN);

    if (E_OK != retVal)
    {
        EthUtils_printf("deinit: failed to set the controller to down mode\r\n");
    }

    return retVal;
}

BufReq_ReturnType EthApp_provideTxBuffer(uint8 ctrlIdx, uint8 priority, Eth_BufIdxType *bufIdxPtr, uint8 **bufPtr,
                                         uint16 *lenBytePtr)
{
    BufReq_ReturnType bufStatus = BUFREQ_E_NOT_OK;
    boolean           retry     = FALSE;

    /* Request one buffer, retry if not available */
    do
    {
        bufStatus = Eth_ProvideTxBuffer(ctrlIdx, priority, bufIdxPtr, bufPtr, lenBytePtr);

        if (BUFREQ_E_BUSY == bufStatus)
        {
            /* Temporarily no buffer available. As per spec, it's up to the
             * requester to retry request for a certain time */
            retry = TRUE;

            if (gEthUtilsApp.txIrqDisable)
            {
                /* Free TX packets are recycled during Eth_TxConfirmation(),
                 * which would normally be called periodically by EthIf, but since
                 * we don't have an actual EthIf implemented in this test app,
                 * we just call it here to let descriptor recycling happen. */
                Eth_TxConfirmation(ctrlIdx);
            }
        }
        else
        {
            retry = FALSE;
        }
    } while (retry == TRUE);

    return bufStatus;
}

boolean EthApp_transmit(uint8 ctrlIdx, uint32 num, uint16 len, boolean txConfirmation, boolean vlan, uint8 priority,
                        uint8 *dstAddr)
{
    Eth_FrameType     frameType;
    Eth_BufIdxType    bufIdx;
    BufReq_ReturnType bufStatus;
    uint16            grantedLen = len;
    uint8            *bufPtr;
    uint32            retryCnt;
    uint32            i;
    sint32            fillStatus;
    boolean           randomBufLen;
    boolean           status = PASS;
    Std_ReturnType    retVal = TRUE;

    randomBufLen = (len == 0U) ? TRUE : FALSE;

    /* Reset test counters */
    gEthUtilsApp.stats.txPktCnt     = 0U;
    gEthUtilsApp.stats.txConfPktCnt = 0U;
    gEthUtilsApp.stats.txBufLenErr  = 0U;
    gEthUtilsApp.stats.txBufProvErr = 0U;
    gEthUtilsApp.stats.txPktErr     = 0U;
    gEthUtilsApp.stats.detErr       = 0U;
    gEthUtilsApp.stats.demErr       = 0U;

    /* Transmit the requested number of buffers */
    for (i = 0U; i < num; i++)
    {
        if (randomBufLen)
        {
            grantedLen = EthUtils_rand(ETH_TEST_BUF_LEN_MIN, ETH_TEST_BUF_LEN_MAX);
        }
        else
        {
            grantedLen = len;
        }

        if (vlan)
        {
            grantedLen += ETH_VLAN_TAG_LEN;
        }

        /* Request TX buffer */
        bufStatus = EthApp_provideTxBuffer(ctrlIdx, priority, &bufIdx, &bufPtr, &grantedLen);
        if (BUFREQ_E_OVFL == bufStatus)
        {
            EthUtils_printf("transmit: failed to get exact size (req=%d got=%d)\r\n", len, grantedLen);
            gEthUtilsApp.stats.txBufLenErr++;
            status = FAIL;
        }
        else if (BUFREQ_E_NOT_OK == bufStatus)
        {
            EthUtils_printf("transmit: failed to get buffer\r\n");
            gEthUtilsApp.stats.txBufProvErr++;
            status = FAIL;
        }
        else if (bufPtr == NULL_PTR)
        {
            EthUtils_printf("transmit: invalid buffer pointer\r\n");
            gEthUtilsApp.stats.txBufProvErr++;
            status = FAIL;
        }

        /* Exit test if error is too critical */
        if (FAIL == status)
        {
            break;
        }

        /* Fill buffer with test pattern */
        if (vlan)
        {
            frameType  = ETHERTYPE_VLAN_TAG;
            fillStatus = EthUtils_fillVlanPayload((VlanDataFramePayload *)bufPtr, i % ETH_TEST_NUM_TYPES, grantedLen,
                                                  ETH_TEST_VLAN_PCP, ETH_TEST_VLAN_VID, ETHERTYPE_EXPERIMENTAL1);
        }
        else
        {
            frameType  = ETHERTYPE_EXPERIMENTAL1;
            fillStatus = EthUtils_fillPayload((DataFramePayload *)bufPtr, i % ETH_TEST_NUM_TYPES, grantedLen);
        }

        if (ETH_TEST_PKT_SOK != fillStatus)
        {
            EthUtils_printf("transmit: failed to fill test packet\r\n");
            status = FAIL;
            break;
        }

        /* Transmit the packet */
        retryCnt = txConfirmation ? 0U : ETHAPP_TRANSMIT_RETRY_COUNT;
        do
        {
            retVal = Eth_Transmit(ctrlIdx, bufIdx, frameType, txConfirmation, grantedLen, dstAddr);
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
            EthUtils_printf("transmit: failed to transmit buffer with idx %d\r\n", (sint32)bufIdx);
            gEthUtilsApp.stats.txPktErr++;
        }
        else
        {
            gEthUtilsApp.stats.txPktCnt++;
        }

        if (gEthUtilsApp.txIrqDisable)
        {
            Eth_TxConfirmation(ctrlIdx);
        }
    }

    /* Add delay before send stop command to make sure host can get CMD STOP */
    EthApp_delay(100U);

    if (TRUE == gEthUtilsApp.sendMultipleStopCmd)
    {
        /* Send STOP cmd 10x to prevent lost,
         * receiver app will handle flushing the extra STOP cmd */
        for (i = 0U; i < ETH_TEST_ITER_S_COUNT; i++)
        {
            EthApp_sendCmd(ctrlIdx, CTRL_FRAME_CMD_STOP);
        }
    }
    else
    {
        /* Send STOP cmd */
        EthApp_sendCmd(ctrlIdx, CTRL_FRAME_CMD_STOP);
    }

    /* If no error on Tx API, check Tx Stats */
    if (PASS == status)
    {
        status = EthApp_verifyTxStatus(num, txConfirmation);
    }

    return status;
}

void EthApp_send(uint8 ctrlIdx, EthFrame *frame, uint16 len, uint8 priority)
{
    Eth_FrameType     frameType = frame->hdr.etherType;
    Eth_BufIdxType    bufIdx;
    BufReq_ReturnType bufStatus;
    boolean           txConfirmation = FALSE;
    uint8            *bufPtr;
    Std_ReturnType    retVal;

    bufStatus = EthApp_provideTxBuffer(ctrlIdx, priority, &bufIdx, &bufPtr, &len);

    if (BUFREQ_OK == bufStatus)
    {
        memcpy(bufPtr, frame->payload, len);
        retVal = Eth_Transmit(ctrlIdx, bufIdx, frameType, txConfirmation, len, frame->hdr.dstMac);
        if (E_OK != retVal)
        {
            EthUtils_printf("send: failed to send buffer\r\n");
        }
    }
    else
    {
        EthUtils_printf("send: failed to get TX buffer: %d\r\n", (int)bufStatus);
    }

    if (gEthUtilsApp.txIrqDisable)
    {
        Eth_TxConfirmation(ctrlIdx);
    }
}

void EthApp_sendCmd(uint8 ctrlIdx, uint8 cmd)
{
    CtrlFramePayload *control;
    Eth_FrameType     frameType = ETHERTYPE_EXP_CONTROL;
    Eth_BufIdxType    bufIdx;
    BufReq_ReturnType bufStatus;
    boolean           txConfirmation = FALSE;
    uint16            len            = sizeof(CtrlFramePayload);
    uint8            *bufPtr;
    Std_ReturnType    retVal;

    bufStatus = EthApp_provideTxBuffer(ctrlIdx, ETH_DEFAULT_TX_PRIORITY, &bufIdx, &bufPtr, &len);
    if (BUFREQ_OK == bufStatus)
    {
        control      = (CtrlFramePayload *)bufPtr;
        control->cmd = cmd;
        retVal       = Eth_Transmit(ctrlIdx, bufIdx, frameType, txConfirmation, len, BcastAddr);
        if (E_OK != retVal)
        {
            EthUtils_printf("sendCmd: failed to send STOP cmd\r\n");
        }
    }
    else
    {
        EthUtils_printf("sendCmd: failed to get TX buffer: %d\r\n", (int)bufStatus);
    }

    if (gEthUtilsApp.txIrqDisable)
    {
        Eth_TxConfirmation(ctrlIdx);
    }
}

boolean EthApp_receive(uint8 ctrlIdx, uint32 num)
{
    boolean forever;
    boolean status = PASS;

    /* Reset test counters */
    gEthUtilsApp.stats.rxPktCnt       = 0U;
    gEthUtilsApp.stats.rxPtpPktCnt    = 0U;
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

    forever = (num == 0U) ? TRUE : FALSE;

    gEthUtilsApp.runTest = TRUE;

    /* Wait for Rx frames */
    while (gEthUtilsApp.runTest)
    {
        if (gEthUtilsApp.rxIrqDisable)
        {
            EthApp_receiveAllFifo(ctrlIdx);
        }
        if (!forever && (gEthUtilsApp.stats.rxPktIndCnt >= num))
        {
            break;
        }
    }

    if ((gEthUtilsApp.stats.rxPktIndCnt != gEthUtilsApp.stats.rxPktCnt) || (gEthUtilsApp.stats.rxEtherTypeErr > 0U) ||
        (gEthUtilsApp.stats.rxPayloadErr > 0U) || (gEthUtilsApp.stats.rxCtrlIdxErr > 0U) ||
        (gEthUtilsApp.stats.detErr > 0U) || (gEthUtilsApp.stats.demErr > 0U))
    {
        status = FAIL;
    }

    if ((FAIL == status) || (TRUE == gEthUtilsApp.verbose))
    {
        EthUtils_printf("Receive Test Results:\r\n");
        EthUtils_printf("  Status:                %s\r\n", status ? "Pass" : "Fail");
        EthUtils_printf("  Requested:             %d\r\n", num);
        EthUtils_printf("  Received:              %d\r\n", gEthUtilsApp.stats.rxPktCnt);
        EthUtils_printf("  Indicated:             %d\r\n", gEthUtilsApp.stats.rxPktIndCnt);
        EthUtils_printf("  Experimental 1:        %d\r\n", gEthUtilsApp.stats.rxExp1PktCnt);
        EthUtils_printf("  Experimental 2:        %d\r\n", gEthUtilsApp.stats.rxExp2PktCnt);
        EthUtils_printf("  VLAN tagged:           %d\r\n", gEthUtilsApp.stats.rxVlanPktCnt);
        EthUtils_printf("  Not received:          %d\r\n", gEthUtilsApp.stats.rxPktNotRecv);
        EthUtils_printf("  EtherType errors:      %d\r\n", gEthUtilsApp.stats.rxEtherTypeErr);
        EthUtils_printf("  Payload errors:        %d\r\n", gEthUtilsApp.stats.rxPayloadErr);
        EthUtils_printf("  Controller idx errors: %d\r\n", gEthUtilsApp.stats.rxCtrlIdxErr);
        EthUtils_printf("  DEM errors:            %d\r\n", gEthUtilsApp.stats.demErr);
        EthUtils_printf("  DET errors:            %d\r\n", gEthUtilsApp.stats.detErr);
        EthUtils_printf("\r\n");
    }

    return status;
}

boolean EthApp_waitForHost(void)
{
    boolean status     = FAIL;
    int     retryCount = 100;

    /* Emulate TCP's Initial Handshake to make sure both side's interface is
     * up and running.
     *  [DUT]      [HOST]
     *    |--- READY->|
     *    |<-- SACK --|
     *    |--- ACK -->|
     */
    EthUtils_printf("Waiting for Host..\r\n");
    gEthUtilsApp.hostUp = FALSE;

    do
    {
        /* Send command indicating that eth interface is up and ready to
         * received the acknowledgment command */
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_READY);
        if (gEthUtilsApp.rxIrqDisable)
        {
            EthApp_receiveAllFifo(gEthUtilsApp.ctrlIdx);
        }

        if (!(retryCount % 10) && !gEthUtilsApp.hostUp)
        {
            EthUtils_printf("No Response from Host, remaining retry = %u\r\n", retryCount);
        }
        EthApp_delay(1000u);
        retryCount--;
    } while (!gEthUtilsApp.hostUp && retryCount > 0);

    /* Send command to indicating that we received the acknowledgement
     * we're ready to start the test stage */
    if (gEthUtilsApp.hostUp)
    {
        EthUtils_printf("Host App detected! Sending Read ACK CMD...\r\n");
        EthApp_sendCmd(gEthUtilsApp.ctrlIdx, CTRL_FRAME_CMD_READY_ACK);
        status = PASS;
    }
    else
    {
        EthUtils_printf("ERROR: NO Host App detected after 100 retries!\r\n");
    }

    return status;
}

void EthApp_receiveAllFifo(uint8 ctrlIdx)
{
    Eth_RxStatusType rxStatus;
    /* Priority is not supported and app should always pass it as 0 */
    Eth_Receive(ctrlIdx, 0, &rxStatus);
}

void EthApp_transmitFlush(uint8 ctrlIdx)
{
    uint16 pktIdx = 0u;

    for (pktIdx = 0u; pktIdx < ETH_NUM_TX_BUFFERS; ++pktIdx)
    {
        EthApp_delay(2u);

        if (gEthUtilsApp.txIrqDisable)
        {
            Eth_TxConfirmation(ctrlIdx);
        }
    }
}

void EthApp_flushRecvQueue(uint8 ctrlIdx)
{
    Eth_RxStatusType rxStatus;
    uint32           pktIdx;

    for (pktIdx = 0; pktIdx < ETH_NUM_RX_BUFFERS; ++pktIdx)
    {
        EthApp_delay(2);

        if (gEthUtilsApp.rxIrqDisable)
        {
            (void)Eth_Receive(ctrlIdx, 0, &rxStatus);
        }
    }
}

void EthApp_notifyCmdRecv(uint8 ctrlIdx)
{
    TickType startCount = 0U, tempCount = 0U, elapsedCount = 0U;
    gEthUtilsApp.ackRecv = FALSE;

    (void)GetCounterValue(ETH_OS_COUNTER_ID, &startCount);
    tempCount = startCount;

    /* Notify Host that we've received the Stop Command */
    EthApp_sendCmd(ctrlIdx, CTRL_FRAME_CMD_RECV_SYN_ACK);

    /* Wait for Host to acknowledge our SYN ACK */
    while (!gEthUtilsApp.ackRecv)
    {
        if (gEthUtilsApp.rxIrqDisable)
        {
            EthApp_receiveAllFifo(ctrlIdx);
        }

        (void)GetElapsedValue(ETH_OS_COUNTER_ID, &tempCount, &elapsedCount);
        tempCount = startCount;
        if (elapsedCount >= (TickType)(100u * OS_TIME_SCALE_VALUE)) /* retry notify every 100 ms */
        {
            (void)GetCounterValue(ETH_OS_COUNTER_ID, &startCount);
            tempCount = startCount;

            /* Notify Host that we've received the Stop Command */
            EthApp_sendCmd(ctrlIdx, CTRL_FRAME_CMD_RECV_SYN_ACK);
        }
    }
}

void EthApp_delay(uint32 msecs)
{
    AppUtils_delay(msecs);
}

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
Std_ReturnType EthApp_getTranceiverLinkState(uint8 trcvIdx)
{
    Std_ReturnType retVal = E_OK;

    /* Get the link state */
    if (E_OK == retVal)
    {
        EthTrcv_LinkStateType linkState;

        retVal = EthTrcv_GetLinkState(trcvIdx, &linkState);
        if (E_OK == retVal)
        {
            EthUtils_printf("EthTrcv link state: %s\r\n", (linkState == ETHTRCV_LINK_STATE_ACTIVE) ? "Up" : "Down");
        }
        else
        {
            EthUtils_printf("Failed to get link state: %d\r\n", retVal);
        }
    }

    return retVal;
}
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */

Std_ReturnType EthApp_showStats(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_OK;
#if (STD_ON == ETH_GET_DROPCOUNT_API)
    Eth_CounterType ethCounter;
    retVal = Eth_GetCounterValues(ctrlIdx, &ethCounter);
    if (E_OK == retVal)
    {
        EthUtils_printf("----------------------------\r\n");
        EthUtils_printf("Controller %d Counters\r\n", ctrlIdx);
        EthUtils_printf("----------------------------\r\n");
        EthUtils_printf("Buffer overruns   : %d\r\n", ethCounter.DropPktBufOverrun);
        EthUtils_printf("CRC errors        : %d\r\n", ethCounter.DropPktCrc);
        EthUtils_printf("Undersize packets : %d\r\n", ethCounter.UndersizePkt);
        EthUtils_printf("Oversized packets : %d\r\n", ethCounter.OversizePkt);
        EthUtils_printf("Alignment errors  : %d\r\n", ethCounter.AlgnmtErr);
        EthUtils_printf("SQE errors        : %d\r\n", ethCounter.SqeTestErr);
        EthUtils_printf("Discarded inbound : %d\r\n", ethCounter.DiscInbdPkt);
        EthUtils_printf("Erroneous inbound : %d\r\n", ethCounter.ErrInbdPkt);
        EthUtils_printf("Discarded outbound: %d\r\n", ethCounter.DiscOtbdPkt);
        EthUtils_printf("Erroneous outbound: %d\r\n", ethCounter.ErrOtbdPkt);
        EthUtils_printf("Single collision  : %d\r\n", ethCounter.SnglCollPkt);
        EthUtils_printf("Multiple collision: %d\r\n", ethCounter.MultCollPkt);
        EthUtils_printf("Deferred transm   : %d\r\n", ethCounter.DfrdPkt);
        EthUtils_printf("Late collisions   : %d\r\n", ethCounter.LatCollPkt);
        EthUtils_printf("Excessive colls   : %d\r\n", ethCounter.HwDepCtr0);
        EthUtils_printf("Carrier loss      : %d\r\n", ethCounter.HwDepCtr1);
    }
    else
    {
        EthUtils_printf("showCountValues: failed to get counters: %d\r\n", retVal);
        gEthUtilsApp.stats.etherGetCountValuesErr++;
    }
#else
    EthUtils_printf("showCountValues: Eth_GetCounterValues() API not enabled\r\n");
    retVal = E_NOT_OK;
#endif

#if (STD_ON == ETH_GETETHERSTATS_API)
    Eth_RxStatsType rxStats;
    retVal = Eth_GetRxStats(ctrlIdx, &rxStats);
    if (E_OK == retVal)
    {
        EthUtils_printf("----------------------------\r\n");
        EthUtils_printf("Controller %d Rx Statistics\r\n", ctrlIdx);
        EthUtils_printf("----------------------------\r\n");
        EthUtils_printf("Rx Drop Events       : %d\r\n", rxStats.RxStatsDropEvents);
        EthUtils_printf("Rx Octets            : %d\r\n", rxStats.RxStatsOctets);
        EthUtils_printf("Rx Packets           : %d\r\n", rxStats.RxStatsPkts);
        EthUtils_printf("Rx Bcast Packets     : %d\r\n", rxStats.RxStatsBroadcastPkts);
        EthUtils_printf("Rx Mcast Packets     : %d\r\n", rxStats.RxStatsMulticastPkts);
        EthUtils_printf("Rx CRC/Align Errors  : %d\r\n", rxStats.RxStatsCrcAlignErrors);
        EthUtils_printf("Rx Undersized Packets: %d\r\n", rxStats.RxStatsUndersizePkts);
        EthUtils_printf("Rx Oversized Packets : %d\r\n", rxStats.RxStatsOversizePkts);
        EthUtils_printf("Rx Fragments         : %d\r\n", rxStats.RxStatsFragments);
        EthUtils_printf("Rx Jabbers           : %d\r\n", rxStats.RxStatsJabbers);
        EthUtils_printf("Rx Collisions        : %d\r\n", rxStats.RxStatsCollisions);
        EthUtils_printf("Rx 64 bytes or less Packets   : %d\r\n", rxStats.RxStatsPkts64Octets);
        EthUtils_printf("Rx 65 to 127 bytes Packets    : %d\r\n", rxStats.RxStatsPkts65to127Octets);
        EthUtils_printf("Rx 128 to 255 bytes Packets   : %d\r\n", rxStats.RxStatsPkts128to255Octets);
        EthUtils_printf("Rx 256 to 511 bytes Packets   : %d\r\n", rxStats.RxStatsPkts256to511Octets);
        EthUtils_printf("Rx 512 to 1023 bytes Packets  : %d\r\n", rxStats.RxStatsPkts512to1023Octets);
        EthUtils_printf("Rx 1024 to 1518 bytes Packets : %d\r\n", rxStats.RxStatsPkts1024to1518Octets);
        EthUtils_printf("Rx Unicast Packets            : %d\r\n", rxStats.RxUnicastFrames);
    }
    else
    {
        EthUtils_printf("getRxStats: failed to get counters: %d\r\n", retVal);
        gEthUtilsApp.stats.etherGetRxStasErr++;
    }
#else
    EthUtils_printf("getRxStats: Eth_GetRxStats() API not enabled\r\n");
    retVal = E_NOT_OK;
#endif

#if (STD_ON == ETH_GETTX_STATS_API)
    Eth_TxStatsType txStats;
    retVal = Eth_GetTxStats(ctrlIdx, &txStats);
    if (E_OK == retVal)
    {
        EthUtils_printf("----------------------------\r\n");
        EthUtils_printf("Controller %d Tx Statistics \r\n", ctrlIdx);
        EthUtils_printf("----------------------------\r\n");
        EthUtils_printf("Tx Num octets          : %d\r\n", txStats.TxNumberOfOctets);
        EthUtils_printf("Tx No Unicast Packets  : %d\r\n", txStats.TxNUcastPkts);
        EthUtils_printf("Tx Unicast Packets     : %d\r\n", txStats.TxUniCastPkts);
    }
    else
    {
        EthUtils_printf("getTxStats: failed to get TX stats: %d\r\n", retVal);
        gEthUtilsApp.stats.etherGetTxStasErr++;
    }
#else
    EthUtils_printf("getTxStats: Eth_GetTxStats() API not enabled\r\n");
    retVal = E_NOT_OK;
#endif

#if (STD_ON == ETH_GETTXERROR_COUNTERVALUES_API)
    Eth_TxErrorCounterValuesType txErrorCounterValues;
    retVal = Eth_GetTxErrorCounterValues(ctrlIdx, &txErrorCounterValues);
    if (E_OK == retVal)
    {
        EthUtils_printf("--------------------------------\r\n");
        EthUtils_printf("Controller %d Tx Error Counters \r\n", ctrlIdx);
        EthUtils_printf("--------------------------------\r\n");
        EthUtils_printf("Tx Deferred transm      : %d\r\n", txErrorCounterValues.TxDeferredTrans);
        EthUtils_printf("Tx Single collisions    : %d\r\n", txErrorCounterValues.TxSingleCollision);
        EthUtils_printf("Tx Multiple collisions  : %d\r\n", txErrorCounterValues.TxMultipleCollision);
        EthUtils_printf("Tx Late collisions      : %d\r\n", txErrorCounterValues.TxLateCollision);
        EthUtils_printf("Tx Excessive collisions : %d\r\n", txErrorCounterValues.TxExcessiveCollison);
    }
    else
    {
        EthUtils_printf("showTxErrStatsCount: failed to get counters: %d\r\n", retVal);
        gEthUtilsApp.stats.etherGetTxErrStasErr++;
    }
#else
    EthUtils_printf("showTxErrStatsCount: Eth_GetTxErrorCounterValues() API not enabled\r\n");
    retVal = E_NOT_OK;
#endif

    return retVal;
}

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
void EthApp_GetCurrentTime(uint8 ctrlIdx, Eth_TimeStampQualType *timeQualPtr, Eth_TimeStampType *tsPtr)
{
    Eth_GetCurrentTime(ctrlIdx, timeQualPtr, tsPtr);
}

void EthApp_EnableEgressTimeStamp(uint8 ctrlIdx, Eth_BufIdxType bufIdx)
{
    Eth_EnableEgressTimeStamp(ctrlIdx, bufIdx);
}
#endif
//
Std_ReturnType EthApp_SetControllerMode(uint8 ctrlIdx, Eth_ModeType ctrlMode)
{
    Std_ReturnType retVal = E_NOT_OK;

    retVal = Eth_SetControllerMode(ctrlIdx, ctrlMode);
    return retVal;
}

Std_ReturnType EthApp_GetControllerMode(uint8 ctrlIdx, Eth_ModeType *ctrlMode)
{
    Std_ReturnType retVal = E_NOT_OK;

    retVal = Eth_GetControllerMode(ctrlIdx, ctrlMode);
    return retVal;
}

Std_ReturnType EthApp_Transmit(uint8 ctrlIdx, Eth_BufIdxType bufIdx, Eth_FrameType frameType, boolean txConfirmation,
                               uint16 lenByte, P2CONST(uint8, AUTOMATIC, ETH_APPL_DAT) physAddrPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    retVal = Eth_Transmit(ctrlIdx, bufIdx, frameType, txConfirmation, lenByte, physAddrPtr);

    return retVal;
}

void EthApp_TxConfirmationInt(uint8 ctrlIdx)
{
    Eth_TxConfirmation(ctrlIdx);
}

/* ========================================================================== */
/*                          External User function Definition                 */
/* ========================================================================== */

void EthApp_CtrlModeIndication(uint8 CtrlIdx, Eth_ModeType ControllerMode)
{
    if (ETH_MODE_DOWN == ControllerMode)
    {
        if (TRUE == gEthUtilsApp.veryVerbose)
        {
            EthUtils_printf("EthApp_CtrlModeIndication: DOWN\r\n");
        }
        gEthUtilsApp.stats.ctrlModeIndDownCnt++;
    }
    else if (ETH_MODE_ACTIVE == ControllerMode)
    {
        if (TRUE == gEthUtilsApp.veryVerbose)
        {
            EthUtils_printf("EthApp_CtrlModeIndication: ACTIVE\r\n");
        }
        gEthUtilsApp.stats.ctrlModeIndActCnt++;
    }
    else
    {
        if (TRUE == gEthUtilsApp.veryVerbose)
        {
            EthUtils_printf("EthApp_CtrlModeIndication: invalid mode\r\n");
        }
        gEthUtilsApp.stats.ctrlModeIndErr++;
    }
}

void EthApp_TrcvModeIndication(uint8 CtrlIdx, EthTrcv_ModeType TrcvMode)
{
    if (TRUE == gEthUtilsApp.veryVerbose)
    {
        EthUtils_printf("EthApp_TrcvModeIndication: %s\r\n", (ETHTRCV_MODE_ACTIVE == TrcvMode) ? "Active" : "Down");
    }
}

#ifdef ENABLE_IRQ_TIMESTAMP_LOG
#define IRQ_TIMESTAMP_LOG 1000U
uint32 irqTimestamp[IRQ_TIMESTAMP_LOG];
#endif

void EthUtilsApp_RxIndication(uint8 ctrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, uint8 *PhysAddrPtr,
                              Eth_DataType *DataPtr, uint16 lenByte)
{
    uint8             pcp = ETH_TEST_VLAN_PCP;
    uint16            vid = ETH_TEST_VLAN_VID;
    CtrlFramePayload *ctrlFramePtr;
    sint32            ret;
#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
    Eth_TimeStampQualType timeQual;
    Eth_TimeStampType     tsVal;
#endif

    if (TRUE == gEthUtilsApp.veryVerbose)
    {
        EthUtils_printf("EthIf_RxIndication: len: %d, bcast: %s, EtherType: 0x%04x\r\n", lenByte,
                        IsBroadcast ? "yes" : "no", FrameType & 0xFFFFU);
    }

    /* Check that the correct controller index is being reported */
    if (ctrlIdx != gEthUtilsApp.ctrlIdx)
    {
        EthUtils_printf(
            "EthIf_RxIndication: incorrect controller index "
            "(got %d, exp %d)\r\n",
            ctrlIdx, gEthUtilsApp.ctrlIdx);
        gEthUtilsApp.stats.rxCtrlIdxErr++;
    }

    /* Validate packet content according to its EtherType */
    switch (FrameType)
    {
        case ETHERTYPE_EXP_CONTROL:
            ctrlFramePtr = (CtrlFramePayload *)DataPtr;
            switch (ctrlFramePtr->cmd)
            {
                case CTRL_FRAME_CMD_START:
                    gEthUtilsApp.runTest = TRUE;
                    break;
                case CTRL_FRAME_CMD_STOP:
                    if (gEthUtilsApp.runTest == TRUE)
                    {
                        gEthUtilsApp.runTest = FALSE;
                    }
                    break;
                case CTRL_FRAME_CMD_READY_SYN_ACK:
                    gEthUtilsApp.hostUp  = TRUE;
                    gEthUtilsApp.testIdx = ctrlFramePtr->data.payload[0];
                    break;
                case CTRL_FRAME_CMD_RECV_ACK:
                    gEthUtilsApp.ackRecv = TRUE;
                    break;
                default:
                    EthUtils_printf("EthIf_RxIndication: invalid control command: %d\r\n", ctrlFramePtr->cmd);
                    break;
            }
            gEthUtilsApp.stats.rxPktCnt++;
            break;

        case ETHERTYPE_VLAN_TAG:
            if (gEthUtilsApp.qosTest)
            {
                VlanDataFramePayload *vlanHdr = (VlanDataFramePayload *)DataPtr;
                // uint8 tci = (ntohs(vlanHdr->tci) >> 13) & 0x7;
                uint16                vlanId = ntohs(vlanHdr->tci) & 0xFFF;

                if (vlanId == ETH_TEST_VLAN_VID)
                {
                    // gEthUtilsApp.stats.qosPacketCnt[tci]++;
                    // gEthUtilsApp.stats.qosBytesCnt[tci] += lenByte;
                }
                else
                {
                    gEthUtilsApp.stats.rxPayloadErr++;
                }
            }
            else
            {
                ret =
                    EthUtils_checkVlanTagAndPayload((VlanDataFramePayload *)DataPtr, pcp, vid, ETHERTYPE_EXPERIMENTAL1);
                if (ETH_TEST_PKT_SOK != ret)
                {
                    EthUtils_printf("EthIf_RxIndication: VLAN tagged payload error: %d\r\n", ret);
                    gEthUtilsApp.stats.rxPayloadErr++;
                }
                else
                {
                    gEthUtilsApp.stats.rxPktCnt++;
                    gEthUtilsApp.stats.rxVlanPktCnt++;
                }
            }
            break;

        case ETHERTYPE_EXPERIMENTAL1:
            ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
            if (ETH_TEST_PKT_SOK != ret)
            {
                EthUtils_printf("EthIf_RxIndication: packet validation failed: %d\r\n", ret);
                gEthUtilsApp.stats.rxPayloadErr++;
            }
            else
            {
                gEthUtilsApp.stats.rxPktCnt++;
                gEthUtilsApp.stats.rxExp1PktCnt++;
            }
            break;

        case ETHERTYPE_EXPERIMENTAL2:
            ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
            if (ETH_TEST_PKT_SOK != ret)
            {
                EthUtils_printf("EthIf_RxIndication: packet validation failed: %d\r\n", ret);
                gEthUtilsApp.stats.rxPayloadErr++;
            }
            else
            {
                gEthUtilsApp.stats.rxPktCnt++;
                gEthUtilsApp.stats.rxExp2PktCnt++;
            }
            break;

        case ETHERTYPE_EXPERIMENTAL3:
        {
            gEthUtilsApp.stats.rxPktCnt++;
            gEthUtilsApp.stats.rxExp3PktCnt++;
            gEthUtilsApp.stats.rxExp3BytesCnt += (lenByte + 14u);
        }
        break;

        case ETHAPP_ETHERTYPE_PTP1588:
        {
            gEthUtilsApp.stats.rxPktCnt++;
            gEthUtilsApp.stats.rxPtpPktCnt++;
        }
        break;

        case ETHERTYPE_IPV4:
        case ETHERTYPE_IPV6: /* fall through */
            if (gEthUtilsApp.checkSumTest == TRUE)
            {
                gEthUtilsApp.stats.rxPktCnt++;
                gEthUtilsApp.stats.rxIpChecksumCnt++;
            }
            break;

        default:
            gEthUtilsApp.stats.rxEtherTypeErr++;
            break;
    }

    if (gEthUtilsApp.saveRxFrame)
    {
        if (IsBroadcast)
        {
            memset(gEthUtilsApp.rxFrame.hdr.dstMac, 0xff, ETH_MAC_ADDR_LEN);
        }
        else
        {
            memset(gEthUtilsApp.rxFrame.hdr.dstMac, 0x00U, ETH_MAC_ADDR_LEN);
        }

        memcpy(gEthUtilsApp.rxFrame.hdr.srcMac, PhysAddrPtr, ETH_MAC_ADDR_LEN);
        gEthUtilsApp.rxFrame.hdr.etherType = (uint16)FrameType;
        memcpy(gEthUtilsApp.rxFrame.payload, DataPtr, lenByte);
        gEthUtilsApp.saveRxFrame = FALSE;
    }

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
    if (gEthUtilsApp.saveRxTime)
    {
        if (FrameType == ETHAPP_ETHERTYPE_PTP1588)
        {
            Eth_GetIngressTimeStamp(ctrlIdx, DataPtr, &timeQual, &tsVal);

            if (timeQual == ETH_VALID)
            {
                gEthUtilsApp.saveRxTimeStamp[gEthUtilsApp.rxFrameCnt] = tsVal;
                gEthUtilsApp.rxFrameCnt = (gEthUtilsApp.rxFrameCnt + 1) % ETH_TEST_ITER_S_COUNT;
            }
        }
    }
#endif

    if (gEthUtilsApp.testRxIrqPacing)
    {
        static uint32 lastRxTime = 0;
        uint32        currentRxTime;

        GetCounterValue(0, &currentRxTime);
        /* It takes about 3-4 usec to process single RX packet with RX indication */
        /* If 2 consecutive confirm times differ more than 4us, they're from 2 different IRQ
         * handling */
        if (currentRxTime - lastRxTime > 4)
        {
            gEthUtilsApp.totalIrq++;
        }
#ifdef ENABLE_IRQ_TIMESTAMP_LOG
        irqTimestamp[gEthUtilsApp.IrqTimestampCount] = currentRxTime - lastRxTime;
        gEthUtilsApp.IrqTimestampCount++;
        gEthUtilsApp.IrqTimestampCount %= IRQ_TIMESTAMP_LOG;
#endif
        lastRxTime = currentRxTime;
    }
    gEthUtilsApp.stats.rxPktIndCnt++;
}

void EthUtilsApp_TxConfirmation(uint8 ctrlIdx, Eth_BufIdxType bufIdx, Std_ReturnType result)
{
#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
    Eth_TimeStampQualType timeQual;
    Eth_TimeStampType     tsVal;
#endif

    if (E_OK == result)
    {
        gEthUtilsApp.stats.txConfPktCnt++;
    }
    else if (E_NOT_OK == result)
    {
        EthUtils_printf("TxConfirmation: transmission of buffer %d failed\r\n", bufIdx);
        gEthUtilsApp.stats.txPktErr++;
    }
    else
    {
        EthUtils_printf("TxConfirmation: invalid confirmation result %d for buffer %d\r\n", result, bufIdx);
    }

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
    if (gEthUtilsApp.saveTxTime)
    {
        Eth_GetEgressTimeStamp(ctrlIdx, bufIdx, &timeQual, &tsVal);

        if (timeQual == ETH_VALID)
        {
            gEthUtilsApp.saveTxTimeStamp[gEthUtilsApp.txFrameCnt] = tsVal;
            gEthUtilsApp.txFrameCnt = (gEthUtilsApp.txFrameCnt + 1) % ETH_TEST_ITER_S_COUNT;
        }
    }
#endif

    if (gEthUtilsApp.testTxIrqPacing)
    {
        static uint32 lastTxTime = 0;
        uint32        currentTxTime;

        GetCounterValue(0, &currentTxTime);
        /* It's take about 1-2 usec to process single TX packet with TX confirmation */
        /* If 2 consecutive confirm times differ more than 2us, they're from 2 different IRQ
         * handling */
        if (currentTxTime - lastTxTime > 2)
        {
            gEthUtilsApp.totalIrq++;
        }
#ifdef ENABLE_IRQ_TIMESTAMP_LOG
        irqTimestamp[gEthUtilsApp.IrqTimestampCount] = currentTxTime - lastTxTime;
        gEthUtilsApp.IrqTimestampCount++;
        gEthUtilsApp.IrqTimestampCount %= IRQ_TIMESTAMP_LOG;
#endif
        lastTxTime = currentTxTime;
    }
}

static boolean EthApp_verifyTxStatus(uint32 num, boolean txConfirmation)
{
    boolean status    = PASS;
    uint8   retry_cnt = 5U;

    do
    {
        /* Flush any pending Tx packet */
        EthApp_transmitFlush(gEthUtilsApp.ctrlIdx);

        /* Check error conditions */
        if ((txConfirmation && (gEthUtilsApp.stats.txConfPktCnt != gEthUtilsApp.stats.txPktCnt)) ||
            (gEthUtilsApp.stats.txPktCnt < num) || (gEthUtilsApp.stats.txPktErr > 0U) ||
            (gEthUtilsApp.stats.txBufProvErr > 0U) || (gEthUtilsApp.stats.txBufLenErr > 0U) ||
            (gEthUtilsApp.stats.detErr > 0U) || (gEthUtilsApp.stats.demErr > 0U))
        {
            retry_cnt--;
            if (retry_cnt)
            {
                continue;
            }
            status = FAIL;
        }
        break;
    } while (retry_cnt > 0);

    if ((FAIL == status) || (TRUE == gEthUtilsApp.verbose))
    {
        EthUtils_printf("Transmit Test Results:\r\n");
        EthUtils_printf("  Status:                 %s\r\n", status ? "Pass" : "Fail");
        EthUtils_printf("  Requested:              %d\r\n", num);
        EthUtils_printf("  Confirmation requested: %s\r\n", txConfirmation ? "Yes" : "No");
        EthUtils_printf("  Transmitted:            %d\r\n", gEthUtilsApp.stats.txPktCnt);
        EthUtils_printf("  Confirmed:              %d\r\n", gEthUtilsApp.stats.txConfPktCnt);
        EthUtils_printf("  Buffer length errors:   %d\r\n", gEthUtilsApp.stats.txBufLenErr);
        EthUtils_printf("  Buffer request errors:  %d\r\n", gEthUtilsApp.stats.txBufProvErr);
        EthUtils_printf("  Transmission errors:    %d\r\n", gEthUtilsApp.stats.txPktErr);
        EthUtils_printf("  DEM errors:             %d\r\n", gEthUtilsApp.stats.demErr);
        EthUtils_printf("  DET errors:             %d\r\n", gEthUtilsApp.stats.detErr);
        EthUtils_printf("\r\n");
    }

    return status;
}

#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
/* Function to access Ethernet PHY MMD indirect registers. These registers
 * are access through sequence of writes through MII registers */
Std_ReturnType App_ethTrcvWriteMMDIndirect(uint8 ctrlIdx, uint8 trcvIdx, uint32 regIdx, uint16 regVal)
{
    Std_ReturnType retVal = E_OK;
#if (STD_ON == ETH_ENABLE_MII_API)
    retVal = Eth_WriteMii(ctrlIdx, trcvIdx, 0x0D, 0x001F);

    retVal += Eth_WriteMii(ctrlIdx, trcvIdx, 0x0E, regIdx);

    retVal += Eth_WriteMii(ctrlIdx, trcvIdx, 0x0D, 0x401F);

    retVal += Eth_WriteMii(ctrlIdx, trcvIdx, 0x0E, regVal);
#endif
    if (((Std_ReturnType)E_OK) != retVal)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif

/* Detecting the PHY (TI PHY) and Setting the PHY in Loop back with
 * Operating Speed of 1000Mbps with Media independent interface APIs
 */
#if (ETH_ENABLE_MII_API == STD_ON)
Std_ReturnType EthPsEnterLoopback(uint8 PortId, Eth_MacConnectionType Speed)
{
    uint32         PhyAddr = 0;
    uint8          CtrlId  = 0;
    Std_ReturnType Status  = E_NOT_OK;
    uint16         PhyReg0 = 0x8000;

    if (PortId == 1)
    {
        PhyAddr = 0;
    }
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
    else
    {
        PhyAddr = 3;
    }
#endif

    Status = Eth_WriteMii(CtrlId, PhyAddr, 0, PhyReg0);
    while ((PhyReg0 & 0x8000) >> 15 == 1)
    {
#if (STD_ON == ETH_ENABLE_MII_API)
        Status = Eth_ReadMii(CtrlId, PhyAddr, 0, &PhyReg0);
#endif
        PhyReg0 = EthTrcv_MdioRdVal;
    }
    switch (Speed)
    {
        case ETH_MAC_CONN_TYPE_RGMII_FORCE_10_HALF:
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
        case ETH_MAC_CONN_TYPE_MII_10_HALF:
#endif
            PhyReg0 = 0x0000;
            break;

        case ETH_MAC_CONN_TYPE_RGMII_FORCE_10_FULL:
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
        case ETH_MAC_CONN_TYPE_MII_10_FULL:
#endif
            PhyReg0 = 0x0100;
            break;

        case ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF:
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
        case ETH_MAC_CONN_TYPE_MII_100_HALF:
#endif
            PhyReg0 = 0x2000;
            break;

        case ETH_MAC_CONN_TYPE_RGMII_FORCE_100_FULL:
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
        case ETH_MAC_CONN_TYPE_MII_100_FULL:
#endif
            PhyReg0 = 0x2100;
            break;

#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
        case ETH_MAC_CONN_TYPE_RGMII_FORCE_1000:
            PhyReg0 = 0x0140;
            break;
#endif
        case ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND:
            PhyReg0 = 0x2100;
            break;

        default:
            return E_NOT_OK;
    }

    // #if defined(AM263X_PLATFORM)
    // AppUtils_ethAm263xPHYDelay(CtrlId, PhyAddr);
    // #endif

    PhyReg0 |= 0x4000;
    Status   = Eth_WriteMii(CtrlId, PhyAddr, 0, PhyReg0);

    Status = Eth_WriteMii(CtrlId, PhyAddr, 0x16, 0x0004);
    Status = Eth_WriteMii(CtrlId, PhyAddr, 0x10, 0x5048);

#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
    if (Speed == ETH_MAC_CONN_TYPE_RGMII_FORCE_1000)
    {
        Status = Eth_WriteMii(CtrlId, PhyAddr, 0x09, 0x1B00);
    }
    else
    {
        Status = Eth_WriteMii(CtrlId, PhyAddr, 0x09, 0x1800);
    }

#elif defined(AM273X_PLATFORM)
    Status = Eth_WriteMii(CtrlId, PhyAddr, 0x09, 0x0B00);
#endif

    Status = Eth_WriteMii(CtrlId, PhyAddr, 0xFE, 0xEF20);
    if (Status != E_OK)
    {
        return E_NOT_OK;
    }

#if (STD_ON == ETH_ENABLE_MII_API)
    Status = Eth_ReadMii(CtrlId, PhyAddr, 1, &PhyReg0);
#endif
    PhyReg0 = EthTrcv_MdioRdVal;

    if (Status != E_OK)
    {
        return E_NOT_OK;
    }
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM261X_PLATFORM)
    /*setLoopbackCfg*/
    (void)App_ethTrcvWriteMMDIndirect(CtrlId, PhyAddr, 0x00FE, 0xE720);

    /*MII*/
    if ((Speed == ETH_MAC_CONN_TYPE_MII_10_HALF) || (Speed == ETH_MAC_CONN_TYPE_MII_10_FULL) ||
        (Speed == ETH_MAC_CONN_TYPE_MII_100_HALF) || (Speed == ETH_MAC_CONN_TYPE_MII_100_FULL))
    {
        (void)App_ethTrcvWriteMMDIndirect(CtrlId, PhyAddr, 0x1DF, 0x20);
    }
#endif
    return Status;
}
#endif
