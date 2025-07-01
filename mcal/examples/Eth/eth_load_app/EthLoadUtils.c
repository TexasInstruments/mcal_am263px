/*
 *
 * Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     EthLoadUtils.c
 *
 *  \brief    This file contains Eth utils target function definitions.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include <stdlib.h>
#include <kernel/dpl/DebugP.h>
#include <kernel/dpl/ClockP.h>
#include <kernel/dpl/SemaphoreP.h>

#include "Os.h"

#include "Eth.h"
#include "Eth_Irq.h"
#include "EthIf_Cbk.h"
#include "EthTrcv.h"
#include "Eth_Cfg.h"
#include "EthLoadUtils.h"

#include "app_utils.h"
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

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static boolean EthApp_verifyTxStatus(uint32 num, boolean txConfirmation);

static inline uint32 EthUtils_rand(uint32 min, uint32 max);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
StatusType GetCounterValue(CounterType CounterID, TickRefType Value)
{
    *Value = ClockP_getTicks() * 1000U;
    return (StatusType)E_OK;
}

StatusType GetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue)
{
    TickType currVal;

    currVal = ClockP_getTicks() * 1000U;
    if (currVal < *Value)
    {
        /* Counter overflow occurred */
        currVal       = (0xFFFFFFFFu - *Value) + currVal + 1U;
        *ElapsedValue = currVal;
    }
    else
    {
        *ElapsedValue = currVal - *Value;
    }

    *Value = currVal;
    return (StatusType)E_OK;
}

static inline uint32 EthUtils_rand(uint32 min, uint32 max)
{
    return (rand() % (max - min + 1)) + min;
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

sint32 EthUtils_fillPayload(DataFramePayload *payload, uint16 type, uint16 len)
{
    sint32 status = ETH_TEST_PKT_SOK;

    if ((len >= ETH_TEST_DATA_HDR_LEN) && (len <= ETH_PAYLOAD_LEN))
    {
        len           -= ETH_TEST_DATA_HDR_LEN;
        payload->type  = type;
        payload->len   = htons(len);
        memset(payload->data, type, len);
    }
    else
    {
        status = ETH_TEST_PKT_ESIZE;
    }

    return status;
}

sint32 EthUtils_fillVlanPayload(VlanDataFramePayload *payload, uint16 type, uint16 len, uint8 pcp, uint16 vid,
                                uint16 etherType)
{
    sint32 status = ETH_TEST_PKT_SOK;

    payload->tci       = htons((pcp << 13) | vid);
    payload->etherType = htons(etherType);

    if (len < (ETH_TEST_DATA_HDR_LEN + ETH_VLAN_TAG_LEN))
    {
        status = ETH_TEST_PKT_ESIZE;
    }

    if (ETH_TEST_PKT_SOK == status)
    {
        len    -= ETH_VLAN_TAG_LEN;
        status  = EthUtils_fillPayload(&payload->payload, type, len);
    }

    return status;
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
            DebugP_log("transmit: failed to get exact size (req=%d got=%d)\r\n", len, grantedLen);
            gEthUtilsApp.stats.txBufLenErr++;
            status = FAIL;
        }
        else if (BUFREQ_E_NOT_OK == bufStatus)
        {
            DebugP_log("transmit: failed to get buffer\r\n");
            gEthUtilsApp.stats.txBufProvErr++;
            status = FAIL;
        }
        else if (bufPtr == NULL_PTR)
        {
            DebugP_log("transmit: invalid buffer pointer\r\n");
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
            DebugP_log("transmit: failed to fill test packet\r\n");
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
                ClockP_usleep(1U);
                retryCnt--;
            }
            else
            {
                break;
            }
        } while (TRUE);

        if (E_OK != retVal)
        {
            DebugP_log("transmit: failed to transmit buffer with idx %d\r\n", (sint32)bufIdx);
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
            DebugP_log("send: failed to send buffer\r\n");
        }
    }
    else
    {
        DebugP_log("send: failed to get TX buffer: %d\r\n", (int)bufStatus);
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

    const uint8 BcastAddr[ETH_HW_ADDR_LEN] = {0xffU, 0xffU, 0xffU, 0xffU, 0xffU, 0xffU};

    bufStatus = EthApp_provideTxBuffer(ctrlIdx, ETH_DEFAULT_TX_PRIORITY, &bufIdx, &bufPtr, &len);
    if (BUFREQ_OK == bufStatus)
    {
        control      = (CtrlFramePayload *)bufPtr;
        control->cmd = cmd;
        retVal       = EthApp_Transmit(ctrlIdx, bufIdx, frameType, txConfirmation, len, BcastAddr);
        if (E_OK != retVal)
        {
            DebugP_log("sendCmd: failed to send STOP cmd\r\n");
        }
    }
    else
    {
        DebugP_log("sendCmd: failed to get TX buffer: %d\r\n", (int)bufStatus);
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
        DebugP_log("Receive Test Results:\r\n");
        DebugP_log("  Status:                %s\r\n", status ? "Pass" : "Fail");
        DebugP_log("  Requested:             %d\r\n", num);
        DebugP_log("  Received:              %d\r\n", gEthUtilsApp.stats.rxPktCnt);
        DebugP_log("  Indicated:             %d\r\n", gEthUtilsApp.stats.rxPktIndCnt);
        DebugP_log("  Experimental 1:        %d\r\n", gEthUtilsApp.stats.rxExp1PktCnt);
        DebugP_log("  Experimental 2:        %d\r\n", gEthUtilsApp.stats.rxExp2PktCnt);
        DebugP_log("  VLAN tagged:           %d\r\n", gEthUtilsApp.stats.rxVlanPktCnt);
        DebugP_log("  Not received:          %d\r\n", gEthUtilsApp.stats.rxPktNotRecv);
        DebugP_log("  EtherType errors:      %d\r\n", gEthUtilsApp.stats.rxEtherTypeErr);
        DebugP_log("  Payload errors:        %d\r\n", gEthUtilsApp.stats.rxPayloadErr);
        DebugP_log("  Controller idx errors: %d\r\n", gEthUtilsApp.stats.rxCtrlIdxErr);
        DebugP_log("  DEM errors:            %d\r\n", gEthUtilsApp.stats.demErr);
        DebugP_log("  DET errors:            %d\r\n", gEthUtilsApp.stats.detErr);
        DebugP_log("\r\n");
    }

    return status;
}

void EthApp_receiveAllFifo(uint8 ctrlIdx)
{
    Eth_RxStatusType rxStatus;
    /* Priority is not supported and app should always pass it as 0 */
    (void)Eth_Receive(ctrlIdx, 0, &rxStatus);
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

void EthApp_delay(uint32 msecs)
{
    ClockP_usleep(msecs * 1000U);
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
            DebugP_log("EthTrcv link state: %s\r\n", (linkState == ETHTRCV_LINK_STATE_ACTIVE) ? "Up" : "Down");
        }
        else
        {
            DebugP_log("Failed to get link state: %d\r\n", retVal);
        }
    }

    return retVal;
}
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */

Std_ReturnType EthApp_Transmit(uint8 ctrlIdx, Eth_BufIdxType bufIdx, Eth_FrameType frameType, boolean txConfirmation,
                               uint16 lenByte, P2CONST(uint8, AUTOMATIC, ETH_APPL_DAT) physAddrPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    retVal = Eth_Transmit(ctrlIdx, bufIdx, frameType, txConfirmation, lenByte, physAddrPtr);

    return retVal;
}

/* ========================================================================== */
/*                          External User function Definition                 */
/* ========================================================================== */
void EthLoadUtils_RxIndication(uint8 ctrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, uint8 *PhysAddrPtr,
                               Eth_DataType *DataPtr, uint16 lenByte)
{
    CtrlFramePayload *ctrlFramePtr;
    sint32            ret;

    if (TRUE == gEthUtilsApp.veryVerbose)
    {
        DebugP_log("EthIf_RxIndication: len: %d, bcast: %s, EtherType: 0x%04x\r\n", lenByte, IsBroadcast ? "yes" : "no",
                   FrameType & 0xFFFFU);
    }

    /* Check that the correct controller index is being reported */
    if (ctrlIdx != gEthUtilsApp.ctrlIdx)
    {
        DebugP_log(
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
                        SemaphoreP_post(gEthUtilsApp.testDoneNotifySem);
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
                    DebugP_log("EthIf_RxIndication: invalid control command: %d\r\n", ctrlFramePtr->cmd);
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
                // ret = EthUtils_checkVlanTagAndPayload((VlanDataFramePayload *)DataPtr,
                //                                       pcp, vid, ETHERTYPE_EXPERIMENTAL1);
                ret = ETH_TEST_PKT_SOK;
                if (ETH_TEST_PKT_SOK != ret)
                {
                    DebugP_log("EthIf_RxIndication: VLAN tagged payload error: %d\r\n", ret);
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
            // ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
            ret = ETH_TEST_PKT_SOK;
            if (ETH_TEST_PKT_SOK != ret)
            {
                DebugP_log("EthIf_RxIndication: packet validation failed: %d\r\n", ret);
                gEthUtilsApp.stats.rxPayloadErr++;
            }
            else
            {
                gEthUtilsApp.stats.rxPktCnt++;
                gEthUtilsApp.stats.rxExp1PktCnt++;
            }
            break;

        case ETHERTYPE_EXPERIMENTAL2:
            // ret = EthUtils_checkPayload((DataFramePayload *)DataPtr);
            ret = ETH_TEST_PKT_SOK;
            if (ETH_TEST_PKT_SOK != ret)
            {
                DebugP_log("EthIf_RxIndication: packet validation failed: %d\r\n", ret);
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

    gEthUtilsApp.stats.rxPktIndCnt++;
}

void EthLoadUtils_TxConfirmation(uint8 ctrlIdx, Eth_BufIdxType bufIdx, Std_ReturnType result)
{
    if (E_OK == result)
    {
        gEthUtilsApp.stats.txConfPktCnt++;
    }
    else if (E_NOT_OK == result)
    {
        DebugP_log("TxConfirmation: transmission of buffer %d failed\r\n", bufIdx);
        gEthUtilsApp.stats.txPktErr++;
    }
    else
    {
        DebugP_log("TxConfirmation: invalid confirmation result %d for buffer %d\r\n", result, bufIdx);
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
        DebugP_log("Transmit Test Results:\r\n");
        DebugP_log("  Status:                 %s\r\n", status ? "Pass" : "Fail");
        DebugP_log("  Requested:              %d\r\n", num);
        DebugP_log("  Confirmation requested: %s\r\n", txConfirmation ? "Yes" : "No");
        DebugP_log("  Transmitted:            %d\r\n", gEthUtilsApp.stats.txPktCnt);
        DebugP_log("  Confirmed:              %d\r\n", gEthUtilsApp.stats.txConfPktCnt);
        DebugP_log("  Buffer length errors:   %d\r\n", gEthUtilsApp.stats.txBufLenErr);
        DebugP_log("  Buffer request errors:  %d\r\n", gEthUtilsApp.stats.txBufProvErr);
        DebugP_log("  Transmission errors:    %d\r\n", gEthUtilsApp.stats.txPktErr);
        DebugP_log("  DEM errors:             %d\r\n", gEthUtilsApp.stats.demErr);
        DebugP_log("  DET errors:             %d\r\n", gEthUtilsApp.stats.detErr);
        DebugP_log("\r\n");
    }

    return status;
}
