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
 *  \file     EthLoadUtils.h
 *
 *  \brief    This file contains Eth ultils target function.declarations.
 */

#ifndef ETH_LOAD_UTILS_H_
#define ETH_LOAD_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Eth.h"
#include "EthTrcv.h"
#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief RGMII_ID_MODE shift value in CTRLMMR_MCU_ENET_CTRL register */
#define ENET_CTRL_RGMII_ID_SHIFT (4U)

/** \brief No internal TX delay in RGMII interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_RGMII_ID_INTTXDLY ((boolean)0U)

/** \brief Internal TX delay in RGMII interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_RGMII_ID_NODELAY ((boolean)1U)

/** \brief RMII port interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_MODE_RMII (1U)

/** \brief RGMII port interface (CTRLMMR_MCU_ENET_CTRL) */
#define ENET_CTRL_MODE_RGMII (2U)

/** \brief Packet transmit retry in non-confirmation mode */
#define ETHAPP_TRANSMIT_RETRY_COUNT (2U)

/** \brief Number of CPSW Statics Block */
#define CPSW_STATS_BLOCK_ELEM_NUM (128U)

/** \brief one second in unit of nanosecond */
#define SEC_TO_NS (1000000000LL)

/** \brief converts 6 bytes seconds valud of 'Eth_TimeStampType' to uint64 seconds integer  */
#define SEC32_TO_SEC64(ts) ((((uint64)ts.secondsHi) << 32) + ((uint64)ts.seconds))

/** \brief convert 'Eth_TimeStampType' vaule to nanosecond integer */
#define TS2NSEC(ts) ((((uint64)SEC32_TO_SEC64(ts)) * SEC_TO_NS) + ((uint64)ts.nanoseconds))

/** \brief ts1-ts2 in 64-bit nanosecond unit */
#define TS_DIFF64NS(ts2, ts1) ((sint64)(TS2NSEC(ts2) - TS2NSEC(ts1)))

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
#define OS_TIME_SCALE_VALUE (1000000U)
#elif defined(SOC_AM62X) || defined(SOC_AM62AX)
#define OS_TIME_SCALE_VALUE (1U)
#elif defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM273X_PLATFORM) || \
    defined(AM2732S_PLATFORM) || defined(AM261X_PLATFORM)
#define OS_TIME_SCALE_VALUE (1000U)
#else
#error "Unsupported SoC"
#endif /* defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || \ \
          defined (SOC_J784S4) */

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
#define ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM (39U)
#define ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM (40U)
#elif defined(SOC_AM62AX)
#define ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM (29U)
#define ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM (138U)
#elif defined(SOC_AM62X)
/*
 * Note: for AM62x only 2 timer available for now.
 * The timer index 1 already use for OS counter.
 * So both Tx/Rx can only use the timer id 0.
 * User should test Rx/Tx Irq pacing seperatly
 */
#define ETH_RX_IRQ_PACING_HW_TIMER_IRQ_NUM (138U)
#define ETH_TX_IRQ_PACING_HW_TIMER_IRQ_NUM (138U)
#endif

#define ETH_DEFAULT_TX_PRIORITY (0u)

/** \brief EthApp test round number */
#define ETH_APP_TEST_ROUND 1U

/** \brief Pass status */
#define PASS true

/** \brief Fail status */
#define FAIL false

/** \brief Size of an array */
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof(x[0U]))

/** \brief Host to network byte order conversion for short integer */
#define htons(a) ((((a) & 0x00FFU) << 8) | (((a) & 0xFF00U) >> 8))

/** \brief Host to network byte order conversion for long integer */
#define htonl(a)                                                                             \
    ((((a) & 0xFF000000U) >> 24) | (((a) & 0x00FF0000U) >> 8) | (((a) & 0x0000FF00U) << 8) | \
     (((a) & 0x000000FFU) << 24))

/** \brief Network to host byte order conversion for short integer */
#define ntohl(a) htonl(a)

/** \brief Network to host byte order conversion for long integer */
#define ntohs(a) htons(a)

/** \brief Experimental EtherType used in test packets */
#define ETHERTYPE_EXPERIMENTAL1 (0x88b5U)

/** \brief Experimental EtherType used in test packets */
#define ETHERTYPE_EXPERIMENTAL2 (0x88b6U)

/** \brief Experimental EtherType used in test packets */
#define ETHERTYPE_EXPERIMENTAL3 (0x88b7U)

/** \brief Experimental EtherType used in test control packets */
#define ETHERTYPE_EXP_CONTROL (0x86aaU)

/** \brief VLAN tag's Tag Protocol Identifier (TPID) */
#define ETHERTYPE_VLAN_TAG (0x8100U)

/** \brief PTP EtherType */
#define ETHERTYPE_PTP (0x88F7U)

/** \brief MAC address length in bytes */
#define ETH_HW_ADDR_LEN (6U)

/** \brief Total bytes in header */
#define ETH_HDR_LEN (14U)

/** \brief Max octets in payload */
#define ETH_PAYLOAD_LEN (1500U)

/** \brief VLAN tag length in bytes */
#define ETH_VLAN_TAG_LEN (4U)

/** \brief Test frame's header length in bytes */
#define ETH_TEST_DATA_HDR_LEN (4U)

/** \brief Test pattern 1 */
#define ETH_TEST_TYPE_PATTERN_1 (0U)

/** \brief Test pattern 2 */
#define ETH_TEST_TYPE_PATTERN_2 (1U)

/** \brief Test pattern 3 */
#define ETH_TEST_TYPE_PATTERN_3 (2U)

/** \brief Test pattern 4 */
#define ETH_TEST_TYPE_PATTERN_4 (3U)

/** \brief Total number of pattern types */
#define ETH_TEST_NUM_TYPES (4U)

/** \brief Success */
#define ETH_TEST_PKT_SOK (0)

/** \brief Invalid pattern type */
#define ETH_TEST_PKT_ETYPE (1)

/** \brief Invalid frame size */
#define ETH_TEST_PKT_ESIZE (2)

/** \brief Invalid frame content */
#define ETH_TEST_PKT_ECONTENT (3)

/** \brief Ready command which indicates that the DUT is up and running */
#define CTRL_FRAME_CMD_READY (0x01U)

/** \brief Start command which indicates that the test can begin */
#define CTRL_FRAME_CMD_START (0x02U)

/** \brief Stop command which indicates when the host or DUT want to end the test */
#define CTRL_FRAME_CMD_STOP (0x03U)

/** \brief Reply (ACK) from Host to indicate that READY CMD was received */
#define CTRL_FRAME_CMD_READY_SYN_ACK (0x04U)

/** \brief Final ACK from DUT to indicates DUT's is up and running */
#define CTRL_FRAME_CMD_READY_ACK (0x05U)

/** \brief Reply (ACK) from DUT to indicate that CMD was received */
#define CTRL_FRAME_CMD_RECV_SYN_ACK (0x06U)

/** \brief Final ACK from Host to indicates that Host received the ACK */
#define CTRL_FRAME_CMD_RECV_ACK (0x07U)

/** \brief Large number of test iterations */
#define ETH_TEST_ITER_L_COUNT (150000U)

/** \brief Med number of test iterations */
#define ETH_TEST_ITER_M_COUNT (1000U)

/** \brief Small number of test iterations */
#define ETH_TEST_ITER_S_COUNT (10U)

/** \brief Smallest length when generating frames with random length */
#define ETH_TEST_BUF_LEN_MIN (10U)

/** \brief Largest length when generating frames with random length */
#define ETH_TEST_BUF_LEN_MAX (1500U)

/** \brief VLAN PCP */
#define ETH_TEST_VLAN_PCP (0U)

/** \brief VLAN VID */
#define ETH_TEST_VLAN_VID (1024U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef struct
{
    uint8_t  dstMac[ETH_HW_ADDR_LEN];
    uint8_t  srcMac[ETH_HW_ADDR_LEN];
    uint16_t etherType;
} __attribute__((packed)) EthFrameHeader;

typedef struct
{
    EthFrameHeader hdr;
    uint8_t        payload[ETH_PAYLOAD_LEN + ETH_VLAN_TAG_LEN];
} __attribute__((packed)) EthFrame;

typedef struct
{
    uint8_t  dstMac[ETH_HW_ADDR_LEN];
    uint8_t  srcMac[ETH_HW_ADDR_LEN];
    uint16_t tpid;
    uint16_t tci;
    uint16_t etherType;
} __attribute__((packed)) EthVlanFrameHeader;

typedef struct
{
    EthVlanFrameHeader hdr;
    uint8_t            payload[ETH_PAYLOAD_LEN];
} __attribute__((packed)) EthVlanFrame;

typedef struct
{
    uint8_t cmd;
    union
    {
        uint8_t status;
        uint8_t payload[45];
    } data;
} __attribute__((packed)) CtrlFramePayload;

typedef struct
{
    EthFrameHeader   hdr;
    CtrlFramePayload payload;
} __attribute__((packed)) CtrlFrame;

typedef struct
{
    uint8_t  type;
    uint8_t  rsvd;
    uint16_t len;
    uint8_t  data[ETH_PAYLOAD_LEN - ETH_TEST_DATA_HDR_LEN];
} __attribute__((packed)) DataFramePayload;

typedef struct
{
    EthFrameHeader   hdr;
    DataFramePayload payload;
} __attribute__((packed)) DataFrame;

typedef struct
{
    uint16_t         tci;
    uint16_t         etherType;
    DataFramePayload payload;
} __attribute__((packed)) VlanDataFramePayload;

typedef struct
{
    EthFrameHeader       hdr;
    VlanDataFramePayload payload;
} __attribute__((packed)) VlanDataFrame;

/* PTPv2 Sync payload */
typedef struct
{
    uint8_t  messageId;
    uint8_t  version;
    uint16_t len;
    uint8_t  subDomain;
    uint8_t  rsv;
    uint16_t flag;
    uint8_t  correction[6];
    uint16_t correctionSubNs;
    uint8_t  rsv4[4];
    uint8_t  clockIdentity[8];
    uint16_t sourcePortId;
    uint16_t sequenceId;
    uint8_t  control;
    uint8_t  logPeriod;
    uint8_t  timestampSecond[6];
    uint8_t  timestampNs[4];
} __attribute__((packed)) ptpSyncPayload;

typedef boolean (*TestFunc)(void);

/** \brief Ethernet test statistics (not to be confused with Ethernet statistics) */
typedef struct EthUtilsApp_Stats_s
{
    volatile uint32 txPktCnt;
    /**< Number of data transmitted packets (Eth_Transmit()) */

    volatile uint32 txConfPktCnt;
    /**< Number of confirmed transmit packets (Eth_TxConfirmation()) */

    volatile uint32 txBufLenErr;
    /**< Number of buffer requests with BUFREQ_E_OVFL error (Eth_ProvideTxBuffer()) */

    volatile uint32 txBufProvErr;
    /**< Number of buffer requests with BUFREQ_E_NOT_OK error (Eth_ProvideTxBuffer()) */

    volatile uint32 txPktErr;
    /**< Number of data transmit errors (Eth_Transmit()) */

    volatile uint32 rxPktCnt;
    /**< Number of data received packets (Eth_Receive() or EthIf_RxIndication()) */

    volatile uint32 rxPtpPktCnt;
    /**< Number of data received packets with PTP type (EthIf_RxIndication()) */

    volatile uint32 rxExp3PktCnt;
    /**< Number of data received packets with experimental 3 type (EthIf_RxIndication()) */

    volatile uint32 rxExp3BytesCnt;
    /**< Number of data received packets (Eth_Receive() or EthIf_RxIndication()) */

    volatile uint32 rxExp1PktCnt;
    /**< Number of data received packets with experimental 1 type (EthIf_RxIndication()) */

    volatile uint32 rxExp2PktCnt;
    /**< Number of data received packets with experimental 2 type (EthIf_RxIndication()) */

    volatile uint32 rxVlanPktCnt;
    /**< Number of data received packets with VLAN tag (EthIf_RxIndication()) */

    volatile uint32 rxPktNotRecv;
    /**< Number of times Eth_Receive() returned packet not received */

    volatile uint32 rxPktIndCnt;
    /**< Number of indicated receive packets (EthIf_RxIndication()) */

    volatile uint32 rxEtherTypeErr;
    /**< Number of packets with an unexpected EtherType field (EthIf_RxIndication()) */

    volatile uint32 rxPayloadErr;
    /**< Number of packets with unexpected payload (EthIf_RxIndication()) */

    volatile uint32 rxCtrlIdxErr;
    /**< Number of packets with unexpected controller index (EthIf_RxIndication()) */

    volatile uint32 rxBcastErr;
    /**< Number of packets with unexpected broadcast flag */

    volatile uint32 rxLenErr;
    /**< Number of packets with invalid buffer length */

    volatile uint32 ctrlModeActCnt;
    /**< Number of controller mode changes to ETH_MODE_ACTIVE (Eth_SetControllerMode()) */

    volatile uint32 ctrlModeDownCnt;
    /**< Number of controller mode changes to ETH_MODE_ACTIVE (Eth_SetControllerMode()) */

    volatile uint32 ctrlModeErr;
    /**< Number of controller mode changes with error (Eth_SetControllerMode()) */

    volatile uint32 ctrlModeIndActCnt;
    /**< Number of controller mode changes to ETH_MODE_ACTIVE (EthIf_CtrlModeIndication()) */

    volatile uint32 ctrlModeIndDownCnt;
    /**< Number of controller mode changes to ETH_MODE_DOWN (EthIf_CtrlModeIndication()) */

    volatile uint32 ctrlModeIndErr;
    /**< Invalid controller mode errors (EthIf_CtrlModeIndication()) */

    volatile uint32 filterUcastAddErr;
    /** Number of filter "add" action errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterUcastRemErr;
    /** Number of filter "add" action (unicast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterUcastRxErr;
    /** Number of errors while receiving unicast packets */

    volatile uint32 filterMcastAddErr;
    /** Number of filter "remove" action (multicast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterMcastRemErr;
    /** Number of filter "remove" action (multicast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterMcastRxErr;
    /** Number of errors while receiving multicast packets */

    volatile uint32 filterBcastErr;
    /** Number of filter "add" action (broadcast) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterBcastRxErr;
    /** Number of errors while receiving broadcast packets */

    volatile uint32 filterBcastTxErr;
    /** Number of errors while transmitting broadcast packets */

    volatile uint32 filterNullErr;
    /** Number of filter "add" action (null) errors (Eth_UpdatePhysAddrFilter()) */

    volatile uint32 filterNullRxErr;
    /** Number of errors while receiving unicast packets */

    volatile uint32 etherGetCountValuesErr;
    /**< Ethernet get counter values errors (Eth_GetCounterValues()) */

    volatile uint32 etherGetRxStasErr;
    /**< Ethernet get Rx statistics errors (Eth_GetRxStats()) */

    volatile uint32 etherGetTxStasErr;
    /**< Ethernet get Tx statistics errors (Eth_GetTxStats()) */

    volatile uint32 etherGetTxErrStasErr;
    /**< Ethernet get Tx error statistics errors (Eth_GetTxErrorCounterValues()) */

    volatile uint32 demErr;
    /**< DEM errors (Dem_SetEventStatus()) */

    volatile uint32 detErr;
    /**< DET errors (Det_ReportError()) */

    // volatile uint32 qosPacketCnt[ETH_PRIORITY_QUEUE_NUM];
    /**< Number of data received packets for QOS value */

    // volatile uint32 qosBytesCnt[ETH_PRIORITY_QUEUE_NUM];
    /**< Number of data received packets for QOS value */
} EthUtilsApp_Stats;

/** \brief Ethernet test state */
typedef struct EthUtilsApp_State_s
{
    uint8 ctrlIdx;
    /**< Controller index */

    uint8 macAddr[ETH_MAC_ADDR_LEN];
    /**< MAC address of the controller */

    volatile boolean runTest;
    /**< Whether test should be running or not */

    volatile boolean hostUp;
    /**< Whether or not host application eth interface is up and running */

    volatile boolean ackRecv;
    /**< Whether or not host application ack our command receive notification */

    boolean saveRxFrame;
    /**< Whether or not the received frame should be saved */

    EthFrame rxFrame;
    /**< Receive frame to copy receive data into in some tests */

    EthUtilsApp_Stats stats;
    /**< Test statistics (not to be confused with Ethernet statistics) */

    boolean verbose;
    /**< Enable verbose */

    boolean veryVerbose;
    /**< Enable very verbose logs */

    boolean saveRxTime;
    /* Enable save Rx Time flags */

    uint16 rxFrameCnt;
    /* Rx frame counter */

    Eth_TimeStampType saveRxTimeStamp[ETH_TEST_ITER_S_COUNT];
    /* Rx frame timestamp */

    boolean saveTxTime;
    /* Enable save Tx Time flags */

    uint16 txFrameCnt;
    /* Tx frame counter */

    Eth_TimeStampType saveTxTimeStamp[ETH_TEST_ITER_S_COUNT];
    /* Tx frame timestamp */

    uint8 rxIrqDisable;
    /* Disable or enable Rx irq */

    uint8 txIrqDisable;
    /* Disable or enable Tx irq */

    uint8 mdioIrqDisable;
    /* Disable or enable Mdio irq */

    uint32 useExtTxBuffer;
    /* use extent Tx buffer*/

    boolean qosTest;
    /* Enable Qos test to calculate QOS bandwidth */

    boolean sendMultipleStopCmd;
    /* enable/disable multiple tx of STOP CMD in EthApp_transmit */
    uint8   testIdx;
    /* Select specific test case */
    void   *testDoneNotifySem;
    /**< Semaphore Handle to indicate test complete */
} EthUtilsApp_State;

/** \brief Counters related typedefs */
#if defined(AUTOSAR_431)
typedef sint16 CounterType;
#else
typedef uint32 CounterType;
#endif
typedef uint32    TickType;
typedef TickType *TickRefType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void EthApp_Startup(void);

Std_ReturnType EthUtilsApp_init(uint8 ctrlIdx);
Std_ReturnType EthUtilsApp_trcvInit(const EthTrcv_ConfigType *cfg);
Std_ReturnType EthApp_deinit(uint8 ctrlIdx);

BufReq_ReturnType EthApp_provideTxBuffer(uint8 ctrlIdx, uint8 priority, Eth_BufIdxType *bufIdxPtr, uint8 **bufPtr,
                                         uint16 *lenBytePtr);

boolean EthApp_transmit(uint8 ctrlIdx, uint32 num, uint16 len, boolean txConfirmation, boolean vlan, uint8 priority,
                        uint8 *dstAddr);

void EthApp_send(uint8 ctrlIdx, EthFrame *frame, uint16 len, uint8 priority);

void EthApp_sendCmd(uint8 ctrlIdx, uint8 cmd);

boolean EthApp_receive(uint8 ctrlIdx, uint32 num);

void EthApp_transmitFlush(uint8 ctrlIdx);
void EthApp_receiveAllFifo(uint8 ctrlIdx);
void EthApp_flushRecvQueue(uint8 ctrlIdx);
void EthApp_delay(uint32 msecs);

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
Std_ReturnType EthApp_getTranceiverLinkState(uint8 trcvIdx);
#endif /* (STD_ON == ETHTRCV_GETLINKSTATE_API) */

Std_ReturnType EthApp_Transmit(uint8 ctrlIdx, Eth_BufIdxType bufIdx, Eth_FrameType frameType, boolean txConfirmation,
                               uint16 lenByte, P2CONST(uint8, AUTOMATIC, ETH_APPL_DAT) physAddrPtr);

StatusType GetCounterValue(CounterType CounterID, TickRefType Value);

StatusType GetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);
/* ========================================================================== */
/*                          User callback function Declarations               */
/* ========================================================================== */
void       EthLoadUtils_RxIndication(uint8 ctrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, uint8 *PhysAddrPtr,
                                     Eth_DataType *DataPtr, uint16 lenByte);

void EthLoadUtils_TxConfirmation(uint8 ctrlIdx, Eth_BufIdxType bufIdx, Std_ReturnType result);

Std_ReturnType Det_ReportError(uint16 moduleId, uint8 instanceId, uint8 apiId, uint8 errorId);

FUNC(Std_ReturnType, DEM_CODE)
Dem_SetEventStatus(VAR(Dem_EventIdType, AUTOMATIC) EventId, VAR(Dem_EventStatusType, AUTOMATIC) EventStatus);

Std_ReturnType EthPsEnterLoopback(uint8 PortId, Eth_MacConnectionType Speed);

#ifdef __cplusplus
}
#endif

#endif /* ETH_LOAD_UTILS_H_ */
