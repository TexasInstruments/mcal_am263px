/*
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *  \file     Eth_Priv.c
 *
 *  \brief    This file contains ETH MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "string.h"
#include "Cpsw_Hw.h"
#include "Dem.h"
#include "Os.h"
#include "hw_ctrl_core.h"
#include "Eth.h"
#include "SchM_Eth.h"
#include "Eth_Irq.h"
#include "EthIf_Cbk.h"
#include "Cpsw.h"
#include "Cpsw_Ale.h"
#include "Cpsw_Cpdma.h"
#include "Eth_Priv.h"
#include "Cpsw_Priv.h"
#include "Cpsw_Mdio.h"
#include "Cpsw_Stats.h"
#include "Cpsw_Cpts.h"
#include "Cpsw_Port.h"
#include "Eth_Helpers.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Declaration for Port Obj pointer type */
typedef Eth_PortObject *Eth_PortObjectPtrType;

/* Default frame type for receive and transmit */
#define ETH_FRAME_DEFAULT_TYPE (0x0800U)

/* VLAN ID ZERO - no VLAN */
#define ETH_NOVLAN_ID (0U)

/* Host port id
 * Note - This is fixed, dont change */
#define ETH_HOST_PORT_ID (0U)

#define ntohs(a) ((((a) >> 8) & 0xffU) + (((a) << 8) & 0xff00U))
#define htons(a) (ntohs(a))

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
/* CPSW Checksum offload Encap Info length */
#define ENET_CPDMA_ENCAPINFO_CHECKSUM_INFO_LEN (4U)

#define ENETDMA_RXCSUMINFO_CHKSUM_ADD_SHIFT (0U)
#define ENETDMA_RXCSUMINFO_CHKSUM_ADD_MASK  (0x0000FFFFU)

#define ENETDMA_RXCSUMINFO_CHKSUM_ERR_SHIFT (16U)
#define ENETDMA_RXCSUMINFO_CHKSUM_ERR_MASK  (0x00010000U)

#define ENETDMA_RXCSUMINFO_FRAGMENT_SHIFT (17U)
#define ENETDMA_RXCSUMINFO_FRAGMENT_MASK  (0x00020000U)

#define ENETDMA_RXCSUMINFO_TCP_UDP_N_SHIFT (18U)
#define ENETDMA_RXCSUMINFO_TCP_UDP_N_MASK  (0x00040000U)

#define ENETDMA_RXCSUMINFO_IPV6_VALID_SHIFT (19U)
#define ENETDMA_RXCSUMINFO_IPV6_VALID_MASK  (0x00080000U)

#define ENETDMA_RXCSUMINFO_IPV4_VALID_SHIFT (20U)
#define ENETDMA_RXCSUMINFO_IPV4_VALID_MASK  (0x00100000U)

#define ENETDMA_TXCSUMINFO_CHKSUM_BYTECNT_SHIFT (0U)
#define ENETDMA_TXCSUMINFO_CHKSUM_BYTECNT_MASK  (0x00003FFFU)

#define ENETDMA_TXCSUMINFO_CHKSUM_INV_SHIFT (15U)
#define ENETDMA_TXCSUMINFO_CHKSUM_INV_MASK  (0x00008000U)

#define ENETDMA_TXCSUMINFO_CHKSUM_STARTBYTE_SHIFT (16U)
#define ENETDMA_TXCSUMINFO_CHKSUM_STARTBYTE_MASK  (0x00FF0000U)

#define ENETDMA_TXCSUMINFO_CHKSUM_RESULT_SHIFT (24U)
#define ENETDMA_TXCSUMINFO_CHKSUM_RESULT_MASK  (0xFF000000U)

/* Internet Protocol Version 4 (IPv4)   */
#define ETH_P_IP (0x0800U)
/* Internet Protocol Version 6 (IPv6)   */
#define ETH_P_IPV6 (0x86DDU)
/* 802.1Q VLAN Extended Header          */
#define ETH_P_8021Q (0x8100U)

/* User Datagram Protocol (UDP)         */
#define IPPROTO_UDP (17U)
/* Transmission Control Protocol (TCP)  */
#define IPPROTO_TCP (6U)

/* Size of 802.1Q VLAN Extended Header  */
#define SIZEOF_VLAN_HDR (4U)

/* IPv6 Header Length */
#define IPV6_HDR_LEN (40U)
#endif /* CHECKSUM_OFFLOAD */
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
/* Eth VLAN Frame Header */
typedef struct
{
    uint8  dstMac[ETH_MAC_ADDR_LEN];
    /**< Destination MAC address */
    uint8  srcMac[ETH_MAC_ADDR_LEN];
    /**< Source MAC address */
    uint16 tpid;
    /**< Tag Protocol Identifier */
    uint16 tci;
    /**< Tag Control Information */
    uint16 etherType;
    /**< EtherType field */
} __attribute__((packed)) Eth_vlanFrameHdr;

/* IPv4 Header */
typedef struct
{
    uint8  v_hl;
    /**< IP version and Header Length */
    uint8  tos;
    /**< Type Of Service */
    uint16 len;
    /**< Total Length */
    uint16 id;
    /**< Identification */
    uint16 offset;
    /**< Flags + Fragment offset field */
    uint8  ttl;
    /**< Time to live */
    uint8  protocol;
    /**< Protocol */
    uint16 checksum;
    /**< IP Header Checksum */
    uint32 src_addr;
    /**< Source address */
    uint32 dst_addr;
    /**< Destination address */
} __attribute__((packed)) Eth_Ip4Hdr;

/* IPv6 Header */
typedef struct
{
    uint32 v_tc_fl;
    /**< IP version + Traffic Class + Flow Label */
    uint16 pay_len;
    /**< Payload Length */
    uint8  next_hdr;
    /**< Next Header */
    uint8  hop_limit;
    /**< Hop Limit */
    uint32 src_addr[4];
    /**< Source address */
    uint32 dst_addr[4];
    /**< Destination address */
} __attribute__((packed)) Eth_Ip6Hdr;

/* UDP Header */
typedef struct
{
    uint16 src_port;
    /**< UDP Source Port */
    uint16 dst_port;
    /**< UDP Destination Port */
    uint16 len;
    /**< Length (Header + Payload) */
    uint16 checksum;
    /**< UDP Frame Checksum of IP Header + UDP Header + Payload */
} __attribute__((packed)) Eth_UdpHdr;

/* TCP Header */
typedef struct
{
    uint16 src_port;
    /**< TCP Source Port */
    uint16 dst_port;
    /**< TCP Destination Port */
    uint32 seq_num;
    /**< Sequence Number */
    uint32 ack_num;
    /**< Acknowledgment number */
    uint16 hl_flags;
    /**< TCP Header Lengh + Flags */
    uint16 window_size;
    /**< Window Size */
    uint16 checksum;
    /**< TCP Frame Checksum of IP Header + TCP Header + Payload */
    uint16 urgent_pointer;
    /**< Urgent Pointer */
} __attribute__((packed)) Eth_TcpHdr;
#endif /* CHECKSUM_OFFLOAD */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Eth_updateMacControlVal(const Eth_MacConfigType *pMACConfig, uint32 *pMacControlVal);

static void EthRxChTearDown(uint32 chNum);

static void EthRxProcessPacket(uint8 ctrlIdx, const Eth_CpdmaRxBuffDescType *pCurrRxBuffDesc);

static void Eth_configureSwitch(const uint8 macAddr[6]);

static Std_ReturnType Eth_allowReception(uint8 currPort, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

static void Eth_enableControllerToTransmitAndReceiveBuffers(const Eth_CpdmaConfigType *pCpdmaConfig);

static inline Eth_PortObjectPtrType Eth_getCurrPortObj(void);

static void Eth_HwcheckCtrlrErrors1(const Eth_StatsType *pStatistics);

static void Eth_MacControlEnable(uint32 *macControlVal, const Eth_MacConfigType *pMACConfig, uint8 portNum);

static void Eth_CpdmaTxChTearDownAck(uint32 baseAddr, uint32 chNum);

static void Eth_CpdmaRxChTearDownAck(uint32 baseAddr, uint32 chNum);

static void EthTxBuffProcess(uint8 ctrlIdx, Eth_TxBufObjType *pBufObj);

static void EthRxBuffDescEnqueue(Eth_CpdmaRxBuffDescQueue *pRxDescRing, Eth_CpdmaRxBuffDescType *pNewTail);

static uint32 EthCheckNullMACAddr(const uint8 macAddr[ETH_MAC_ADDR_LEN]);

static void Eth_freeTxBuffers(Eth_TxBufObjType *bufObjArray, uint32 numBuffers);

static BufReq_ReturnType Eth_HwProvideTxBufferIdx(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr,
                                                  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) * BufPtr,
                                                  P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr);

static void EthResetDrvObj(Eth_DrvObject *pEthDrvObj);

static void EthCpswInstInit(uint32 portNum);

static void Eth_macSetConfig(uint8 portNum, const Eth_MacConfigType *pMACConfig);

static void EthTxBuffDescInit(uint8 ctrlIdx, Eth_CpdmaTxBuffDescQueue *pRing, uint32 numBuffDesc, uint32 startAddr);

static void EthRxBuffDescInit(uint8 ctrlIdx, Eth_CpdmaRxBuffDescQueue *pRing, uint32 numBuffDesc, uint32 startAddr);

static void EthRxBuffDescRxStatus(const Eth_CpdmaRxBuffDescType *pCurrRxBuffDesc, Eth_RxStatusType *rxStatus);

static Eth_RxStatusType EthRxBuffDescProcessSingle(uint8 ctrlIdx, uint32 chNum);

static boolean Eth_isBcastMacAddr(const uint8 *addr);

static boolean Eth_isMcastMacAddr(const uint8 *addr);

static boolean Eth_isUcastMacAddr(const uint8 *addr);

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
static uint16        Eth_genPseudoCheckSumIPv4(uint8 *ipPktStart, uint16 ipPktPayLen);
static uint16        Eth_genPseudoCheckSumIPv6(uint8 *ipPktStart, uint16 ipPktPayLen);
static uint32        Eth_setPseudoCheckSum(Eth_FrameHeaderType *pEthPkt, Eth_FrameType frameType);
static inline uint8 *Eth_getIpPktStart(uint8 *frameBuffer);
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
/** \brief Ethernet driver object */
VAR(Eth_DrvObject, ETH_VAR_ZERO_INIT) Eth_DrvObj;
#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

/* Design     : SITARA_MCU_MCAL-2239 */
#define ETH_START_SEC_VAR_NO_INIT_8

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
static uint8 Eth_TxPacketMemoryPool[ETH_MAX_FRAME_LEN * ETH_NUM_TX_BUFFERS];

static uint8 Eth_RxPacketMemoryPool[ETH_MAX_FRAME_LEN * ETH_NUM_RX_BUFFERS];
#define ETH_STOP_SEC_VAR_NO_INIT_8

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

uint8 Eth_RxDescMem[ETH_NUM_RX_BUFFERS * sizeof(Eth_CpdmaRxBuffDescType)]
    __attribute__((aligned(128), section(".bss.ENET_CPPI_DESC")));
uint8 Eth_TxDescMem[ETH_NUM_TX_BUFFERS * sizeof(Eth_CpdmaTxBuffDescType)]
    __attribute__((aligned(128), section(".bss.ENET_CPPI_DESC")));

#define ETH_START_SEC_VAR_INIT_32

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
static boolean Eth_CpdmaRxChTornFlag = FALSE;
static boolean Eth_CpdmaTxChTornFlag = FALSE;
#define ETH_STOP_SEC_VAR_INIT_32

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

#define ETH_START_SEC_CONST_8

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
static const uint8 Eth_BcastAddr[ETH_MAC_ADDR_LEN] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

static const uint8 Eth_PtpMcastAddr[ETH_MAC_ADDR_LEN] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E};
#define ETH_STOP_SEC_CONST_8

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_8

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
volatile uint8 Eth_ControllerModeChangeFlag = (uint8)FALSE;
#define ETH_STOP_SEC_VAR_INIT_8

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define ETH_START_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

FUNC(void, ETH_CODE) Eth_initHw(const Eth_ConfigType *CfgPtr)
{
    uint16                    i        = 0;
    uint8                     portIdx  = 0U;
    uint32                    currPort = 0U;
    Eth_PortObject           *portObj  = &Eth_DrvObj.portObj;
    const Eth_PortConfigType *portCfg  = &CfgPtr->portCfg;

    EthResetDrvObj(&Eth_DrvObj);
    /* store instance specific parameters */
    Eth_DrvObj.ctrlIdx            = CfgPtr->ctrlIdx;
    Eth_DrvObj.portIdx            = CfgPtr->portIdx;
    Eth_DrvObj.baseAddr           = SOC_MSS_CPSW_BASE;
    Eth_DrvObj.rxDescMemBaseAddr  = (uint32)Eth_RxDescMem;
    Eth_DrvObj.txDescMemBaseAddr  = (uint32)Eth_TxDescMem;
    Eth_DrvObj.activeMACPortCount = (uint8)1U;

    /* Copy controller configuration into driver object*/

    /* Each port is considered as one controller */
    portIdx = CfgPtr->portIdx;

    /* Reset the different modules */
    Cpsw_resetEnet(Eth_DrvObj.baseAddr, portIdx);
    CpswCpdma_reset(Eth_DrvObj.baseAddr);
    (void)memcpy(&Eth_DrvObj.ethConfig, CfgPtr, sizeof(Eth_ConfigType));

    Eth_DrvObj.enableCacheOps       = CfgPtr->enableCacheOps;
    Eth_DrvObj.cacheFlushFnPtr      = CfgPtr->cacheFlushOps;
    Eth_DrvObj.cacheInvalidateFnPtr = CfgPtr->cacheInvalidateOps;

    /* Copy port configuration into driver object */
    portObj->portNum = portIdx; /* External port starts with 1 */
    (void)memcpy(&portObj->portCfg, portCfg, sizeof(Eth_PortConfigType));

    /* Copy TX buffer information into driver object */
    for (i = 0U; i < (uint16)ETH_NUM_TX_BUFFERS; i++)
    {
        portObj->txBufObjArray[i].bufIdx         = i;
        portObj->txBufObjArray[i].payload        = (Eth_TxFrameObjType *)&Eth_TxPacketMemoryPool[i * ETH_MAX_FRAME_LEN];
        portObj->txBufObjArray[i].len            = ETH_MAX_FRAME_LEN;
        portObj->txBufObjArray[i].type           = ETH_FRAME_DEFAULT_TYPE;
        portObj->txBufObjArray[i].bufState       = ETH_BUF_STATE_FREE;
        portObj->txBufObjArray[i].txConfirmation = (boolean)FALSE;
    }

    portObj->lastTxIdx = ETH_NUM_TX_BUFFERS - 1U;

    /* Copy RX buffer information into driver object */
    for (i = 0U; i < (uint16)ETH_NUM_RX_BUFFERS; i++)
    {
        portObj->rxBufObjArray[i].bufIdx = i;
        portObj->rxBufObjArray[i].payload =
            (Eth_RxFrameObjType *)&Eth_RxPacketMemoryPool[i * (uint16)ETH_MAX_FRAME_LEN];
        portObj->rxBufObjArray[i].len = ETH_MAX_FRAME_LEN;
    }

    currPort = (uint32)Eth_DrvObj.portObj.portNum;

    /* Initialize CPSW */
    EthCpswInstInit(currPort);

#if (ETH_TRAFFIC_SHAPING_API == STD_ON)
    uint8  k         = 0U;
    uint8  queueNum  = 0U;
    uint32 idleSlope = 0U;
    for (k = ETH_PRIORITY_QUEUE_NUM; k > 0U; k--)
    {
        queueNum  = Eth_DrvObj.ethConfig.portCfg.shaperCfg[k - 1U].queueNum;
        idleSlope = Eth_DrvObj.ethConfig.portCfg.shaperCfg[k - 1U].idleSlope;
        if (queueNum < ETH_PRIORITY_QUEUE_NUM)
        {
            CpswPort_setBandwidthLimit(Eth_DrvObj.baseAddr, queueNum, Eth_DrvObj.ethConfig.cpdmaCfg.pacingClkFreq,
                                       idleSlope);
        }
    }
#endif

    /* configure switch for speed, duplex mode etc.*/
    Eth_MacConfigType *pMACConfig = &Eth_DrvObj.portObj.portCfg.macCfg;

    /* PHY found at address pMACConfig->phyAddr */
    Eth_macSetConfig(portObj->portNum, pMACConfig);

    /* write rx maxlen register, beside configured MTU, need to add pass_crc
     * and encap checksum so set to max frame size for simplicity */
    Cpsw_setRxMaxLen(Eth_DrvObj.baseAddr, portIdx, ETH_MAX_FRAME_LEN);

#if ((ETH_GETETHERSTATS_API == STD_ON) || (ETH_GET_DROPCOUNT_API == STD_ON) || \
     (ETH_GETTXERROR_COUNTERVALUES_API == STD_ON) || (ETH_GETTX_STATS_API == STD_ON))
    /* Enable statistics for port */
    Eth_DrvObj.statsObj.enableStatistics = (uint32)TRUE;
#else
    Eth_DrvObj.statsObj.enableStatistics = (uint32)FALSE;
#endif
}

/**
 * \brief Initializes driver object for the CPSW instance
 *
 * \param  instNum   Pointer to  CPSW driver object to be initialised.
 */
static void EthResetDrvObj(Eth_DrvObject *pEthDrvObj)
{
    /* Always one controller */
    pEthDrvObj->ctrlIdx  = (uint8)0x0U;
    pEthDrvObj->ctrlMode = ETH_MODE_DOWN;
    /* clear MDIO config structure */
    (void)memset(&(pEthDrvObj->ethConfig), 0, sizeof(Eth_ConfigType));

    /* clear port object structure */
    (void)memset(&(pEthDrvObj->portObj), 0, sizeof(pEthDrvObj->portObj));
    /* clear CPDMA config structure */
    (void)memset(&(pEthDrvObj->rxDescRing), 0, sizeof(pEthDrvObj->rxDescRing));
    /* clear CPDMA config structure */
    (void)memset(&(pEthDrvObj->txDescRing), 0, sizeof(pEthDrvObj->txDescRing));
    pEthDrvObj->maxTxBuffDesc = 0U;
    pEthDrvObj->maxRxBuffDesc = 0U;

    /* clear CPDMA config structure */
    (void)memset(&(pEthDrvObj->statsObj), 0, sizeof(pEthDrvObj->statsObj));

    pEthDrvObj->baseAddr           = 0U;
    pEthDrvObj->rxDescMemBaseAddr  = 0U;
    pEthDrvObj->txDescMemBaseAddr  = 0U;
    pEthDrvObj->activeMACPortCount = 0x1U;
}

/**
 * \brief Initializes the CPSW instance
 *
 * \param  instNum   The CPSW instance to be initialised
 */
static void EthCpswInstInit(uint32 portNum)
{
    uint32               maskVar      = 0U;
    Eth_CpdmaConfigType *pCpdmaConfig = &(Eth_DrvObj.ethConfig.cpdmaCfg);
#if (ETH_ENABLE_MII_API == STD_ON)
    Eth_MdioConfigType *pMdioCfg = &Eth_DrvObj.ethConfig.mdioCfg;

    /* Initialize MDIO */
    CpswMdio_init(Eth_DrvObj.baseAddr, pMdioCfg->mdioClockFreq, pMdioCfg->mdioBusFreq);
#endif /* ETH_ENABLE_MII_API == STD_ON*/

    /* Init host port */
    CpswPort_hostPortopen(Eth_DrvObj.baseAddr);
    CpswAle_enableBypass(Eth_DrvObj.baseAddr, (uint32)FALSE);

    CpswAle_init(Eth_DrvObj.baseAddr);

    /* Set the port 0 and app provided port to forward */
    CpswAle_setPortState(Eth_DrvObj.baseAddr, 0U, (uint32)CPSW_ALE_PORT_STATE_FWD);

    /* Enable ALE unknown VLAN member & registered multicast - port mask where
     *  unknown VLAN packets would be forwarded to  */
    uint32 tmpPortId, tmpCurrPort;

    tmpPortId   = ((uint32)1U << ETH_HOST_PORT_ID);
    tmpCurrPort = ((uint32)1U << portNum);

    maskVar = (tmpPortId | tmpCurrPort);

    CpswAle_setUnknownMemberList(Eth_DrvObj.baseAddr, maskVar);
    CpswAle_setUnknownRegFloodMask(Eth_DrvObj.baseAddr, maskVar);
    CpswAle_setUnknownUnregFloodMask(Eth_DrvObj.baseAddr, tmpCurrPort);

    /* Set user enabled port to forwarding state */
    CpswAle_setPortState(Eth_DrvObj.baseAddr, portNum, (uint32)CPSW_ALE_PORT_STATE_FWD);

#if (ETH_USR_MDIO_INTERRUPT == STD_ON)
    /* Enable the Misc. interrupt for MDIO events, error stats etc */
    Cpsw_enableMiscIntr(Eth_DrvObj.baseAddr, (uint32)CPSW_SS_MISC_EN_MDIO_USER);

    /* Enable the interrupt in MDIO module */
    CpswMdio_enableUsrIntr(Eth_DrvObj.baseAddr);
#endif
#if (ETH_HOST_ERROR_INTERRUPT == STD_ON)
    /* Enable the Misc. interrupt for MDIO events, error stats etc */
    Cpsw_enableMiscIntr(Eth_DrvObj.baseAddr, (uint32)CPSW_SS_MISC_EN_HOST_PEND);
#endif

    Eth_enableControllerToTransmitAndReceiveBuffers(pCpdmaConfig);

    /*
     * Currently no. of descriptors can not be more than
     * number of buffers
     */
    Eth_DrvObj.maxTxBuffDesc = (uint32)ETH_NUM_TX_BUFFERS;
    Eth_DrvObj.maxRxBuffDesc = (uint32)ETH_NUM_RX_BUFFERS;

    if (pCpdmaConfig->rxThreshCount != (uint32)0U)
    {
        /* Reset the free buffer count for this channel
         * (it is write to increment, force to rollover to zero) */
        CpswCpdma_setRxChFreeBufCnt(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, Eth_DrvObj.maxRxBuffDesc);

        /* Set the threshold for the RX_THRESH interrupt trigger */
        CpswCpdma_setRxChThresh(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, pCpdmaConfig->rxThreshCount);

        /* Enable Rx threshold interrupt in CPDMA */
        CpswCpdma_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX_THR);

        /* Enable Rx threshold interrupt in subsystem */
        Cpsw_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX_THR);
    }
}

static void Eth_macSetConfig(uint8 portNum, const Eth_MacConfigType *pMACConfig)
{
    uint32 macControlVal = 0U;

    /* If PASSCONTROL is set, enable control frames */
    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_PASSCONTROL) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(macControlVal, MAC_CONTROL, RX_CMF_EN, 1U);
    }

    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_PASSERROR) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(macControlVal, MAC_CONTROL, RX_CEF_EN, 1U);
        ETH_PN_SET_FIELD(macControlVal, MAC_CONTROL, RX_CSF_EN, 1U);
    }

    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_CMDIDLE) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(macControlVal, MAC_CONTROL, CMD_IDLE, 1U);
    }

    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_TXSHORTGAPEN) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(macControlVal, MAC_CONTROL, TX_SHORT_GAP_ENABLE, 1U);
    }

    Eth_MacControlEnable(&macControlVal, pMACConfig, portNum);
}

static void Eth_MacControlEnable(uint32 *macControlVal, const Eth_MacConfigType *pMACConfig, uint8 portNum)
{
    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_TXPACE) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(*macControlVal, MAC_CONTROL, TX_PACE, 1U);
    }

    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_TXFLOWCNTL) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(*macControlVal, MAC_CONTROL, TX_FLOW_EN, 1U);
    }

    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_RXBUFFERFLOWCNTL) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(*macControlVal, MAC_CONTROL, RX_FLOW_EN, 1U);
    }

    if ((pMACConfig->macModeFlags & (uint32)MAC_CONFIG_MODEFLG_MACLOOPBACK) != (uint32)0U)
    {
        ETH_PN_SET_FIELD(*macControlVal, MAC_CONTROL, LOOPBACK, 1U);
    }

    if (pMACConfig->macConnectionType == ETH_MAC_CONN_TYPE_RGMII_FORCE_1000)
    {
        ETH_PN_SET_FIELD(*macControlVal, MAC_CONTROL, GIG, 1U);
    }

    *macControlVal |= Cpsw_getMacCtrl(Eth_DrvObj.baseAddr, portNum);

    Cpsw_setMacCtrl(Eth_DrvObj.baseAddr, portNum, *macControlVal);

    Eth_updateMacControlVal(pMACConfig, macControlVal);

    /* Update MACCONTROL with speed/duplex/type settings */
    Cpsw_setMacCtrl(Eth_DrvObj.baseAddr, portNum, *macControlVal);
}

static void Eth_updateMacControlVal(const Eth_MacConfigType *pMACConfig, uint32 *pMacControlVal)
{
    Eth_MacConnectionType macType = pMACConfig->macConnectionType;

    /*
     * We put this down here on its own since in DLB mode we have to
     * enable GMII_EN bit after enabling loop back mode. When not in
     * DLB mode, we can still do it here.
     */

    /* CTL_EN */
    if ((macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_10_HALF) || (macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_10_FULL) ||
        (macType == ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND))
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, CTL_EN, 1U);
    }
    else
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, CTL_EN, 0U);
    }

    /* GIG */
    if (macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_1000)
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, GIG, 1U);
    }
    else
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, GIG, 0U);
    }

    /* GIG_FORCE */
    if ((macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF) || (macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_100_FULL) ||
        (macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_1000))
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, GIG_FORCE, 1U);
    }
    else
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, GIG_FORCE, 0U);
    }

    /* Duplex */
    if ((macType == ETH_MAC_CONN_TYPE_MII_10_HALF) || (macType == ETH_MAC_CONN_TYPE_MII_100_HALF) ||
        (macType == ETH_MAC_CONN_TYPE_RMII_10_HALF) || (macType == ETH_MAC_CONN_TYPE_RMII_100_HALF) ||
        (macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_10_HALF) || (macType == ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF))
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, FULLDUPLEX, 0U);
    }
    else
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, FULLDUPLEX, 1U);
    }

    /* GMII_EN */
    ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, GMII_EN, 1U);

    /* IFCTL_A */
    if ((macType == ETH_MAC_CONN_TYPE_RMII_10_HALF) || (macType == ETH_MAC_CONN_TYPE_RMII_10_FULL))
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, IFCTL_A, 0U);
    }
    else if ((macType == ETH_MAC_CONN_TYPE_RMII_100_HALF) || (macType == ETH_MAC_CONN_TYPE_RMII_100_FULL))
    {
        ETH_PN_SET_FIELD(*pMacControlVal, MAC_CONTROL, IFCTL_A, 1U);
    }
    else
    {
        /* nothing */
    }

    return;
}

Std_ReturnType Eth_cpswCheckHostErr(void)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    if ((uint32)TRUE == Cpsw_checkHostErr(SOC_MSS_CPSW_BASE))
    {
        /* Requirements: SWS_Eth_00039 */

        /*
         * check access to controller and report production error
         * ETH_E_ACCESS.
         */
#ifdef ETH_E_ACCESS
        (void)Dem_SetEventStatus(ETH_E_ACCESS, DEM_EVENT_STATUS_PREFAILED);
#endif
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

/* TX channel teardown acknowledgement */
static void Eth_CpdmaTxChTearDownAck(uint32 baseAddr, uint32 chNum)
{
    volatile uint32 tempCount = ETH_TIMEOUT_DURATION;

    while (CPSW_CPDMA_TEAR_DWN_ACK != CpswCpdma_readTxChCp(baseAddr, chNum))
    {
        if (0U == tempCount)
        {
#ifdef ETH_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        else
        {
            tempCount = tempCount - 1U;
        }
    }
}

/* RX channel teardown acknowledgement */
static void Eth_CpdmaRxChTearDownAck(uint32 baseAddr, uint32 chNum)
{
    volatile uint32 tempCount = ETH_TIMEOUT_DURATION;

    while (CPSW_CPDMA_TEAR_DWN_ACK != CpswCpdma_readRxChCp(baseAddr, chNum))
    {
        if (0U == tempCount)
        {
#ifdef ETH_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        else
        {
            tempCount = tempCount - 1U;
        }
    }
}

FUNC(Std_ReturnType, ETH_CODE)
Eth_setHwControllerMode(uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
    Std_ReturnType retVal  = E_NOT_OK;
    uint32         rxChNum = ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM;
    uint32         txChNum = ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM;
    uint8          portIdx = Eth_DrvObj.portObj.portNum;

    /* Only process if input CtrlMode differs with current mode */
    if (Eth_DrvObj.ctrlMode != CtrlMode)
    {
        /*
         * Disable the Ethernet controller, reset all transmit & receive
         * buffers (i.e. ignore all pending transmission & reception
         * requests
         */
        if (ETH_MODE_DOWN == CtrlMode)
        {
            /*
             * Requirements: SWS_Eth_00137 (All pending transmit buffers
             * shall be released)
             */

            /*
             * Use channel Tear-down to clear all pending transmission and
             * reception requests.
             * Note: This is asynchronous call. Once teardown is complete it
             *       will issue interrupt with Tear-down bit set.
             */

            CpswCpdma_teardownTxCh(Eth_DrvObj.baseAddr, txChNum);
            Eth_CpdmaTxChTearDownAck(Eth_DrvObj.baseAddr, txChNum);

            CpswCpdma_teardownRxCh(Eth_DrvObj.baseAddr, rxChNum);
            Eth_CpdmaRxChTearDownAck(Eth_DrvObj.baseAddr, rxChNum);

            /*
             * SWS_Eth_00137 - All locked transmit buffers shall be released if
             * the controller is disabled via Eth_SetControllerMod
             */
            SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
            Eth_freeTxBuffers(Eth_DrvObj.portObj.txBufObjArray, ETH_NUM_TX_BUFFERS);
            Eth_DrvObj.portObj.lastTxIdx = ETH_NUM_TX_BUFFERS - 1U;

            /* Disable the transmission and reception */
            CpswCpdma_disableTxCh(Eth_DrvObj.baseAddr);
            CpswCpdma_disableRxCh(Eth_DrvObj.baseAddr);

            CpswStats_deinit(Eth_DrvObj.baseAddr, &Eth_DrvObj.statsObj, portIdx);

            CpswCpts_deinit(Eth_DrvObj.baseAddr);

            /* Set controller mode to down */
            Eth_DrvObj.ctrlMode          = ETH_MODE_DOWN;
            Eth_ControllerModeChangeFlag = TRUE;

            SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

            retVal = E_OK;
        }
        else
        {
            /*
             * Enable the Ethernet controller, enable all transmit and receive
             * buffers
             */
            SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

            EthTxBuffDescInit(CtrlIdx, &(Eth_DrvObj.txDescRing), Eth_DrvObj.maxTxBuffDesc,
                              Eth_DrvObj.txDescMemBaseAddr);

            EthRxBuffDescInit(CtrlIdx, &(Eth_DrvObj.rxDescRing), Eth_DrvObj.maxRxBuffDesc,
                              Eth_DrvObj.rxDescMemBaseAddr);

            /* Enable all transmit and receive buffers */
            CpswCpdma_writeRxChHdp(Eth_DrvObj.baseAddr, Eth_locToGlobAddr((uintptr_t)Eth_DrvObj.rxDescRing.pHead),
                                   rxChNum);

            /* Open the stats module */
            CpswStats_init(Eth_DrvObj.baseAddr, &Eth_DrvObj.statsObj, portIdx);

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
            /* Enable CPTS module */
            (void)CpswCpts_init(Eth_DrvObj.baseAddr, &Eth_DrvObj.cptsObj, &Eth_DrvObj.ethConfig.cptsCfg, portIdx);
#endif

            /* Enable the transmission and reception */
            CpswCpdma_enableTxCh(Eth_DrvObj.baseAddr);
            CpswCpdma_enableRxCh(Eth_DrvObj.baseAddr);

            /* Set controller mode to active */
            Eth_DrvObj.ctrlMode          = ETH_MODE_ACTIVE;
            Eth_ControllerModeChangeFlag = TRUE;

            SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

            retVal = E_OK;
        }
    }
    else /* if (Eth_DrvObj.ctrlMode != CtrlMode) */
    {
        /* nothing */
    }

    return retVal;
}

void Eth_setHwPhysAddr(P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
    uint8               currPort = 0U;
    Eth_PortConfigType *pPortCfg = &Eth_DrvObj.portObj.portCfg;
    /* Each port is considered as one controller */
    currPort = Eth_DrvObj.portObj.portNum;
    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
    Eth_configureSwitch(PhysAddrPtr);

    /* Copy MAC address to config structure */
    (void)memcpy(&(pPortCfg->macCfg.macAddr[0U]), PhysAddrPtr, ETH_MAC_ADDR_LEN);

    /*   Configure Mac Address  for the port */
    Cpsw_setPortSrcAddr(Eth_DrvObj.baseAddr, currPort, pPortCfg->macCfg.macAddr);

    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
}

Std_ReturnType Eth_HwUpdatePhysAddrFilter(P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr,
                                          Eth_FilterActionType Action)
{
    uint8          currPort = 0U;
    uint32         aleIdx   = 0U;
    Std_ReturnType retVal   = E_NOT_OK;
    /* Each port is considered as one controller */
    currPort = Eth_DrvObj.portObj.portNum;

    if (ETH_ADD_TO_FILTER == Action)
    {
        retVal = Eth_allowReception(currPort, PhysAddrPtr);
    }
    else
    {
        if (TRUE == Eth_isMcastMacAddr(PhysAddrPtr))
        {
            (void)CpswAle_delMulticastEntryPort(Eth_DrvObj.baseAddr, PhysAddrPtr, ETH_NOVLAN_ID, ETH_HOST_PORT_ID);

            aleIdx = CpswAle_delMulticastEntryPort(Eth_DrvObj.baseAddr, PhysAddrPtr, ETH_NOVLAN_ID, currPort);
        }
        else
        {
            aleIdx = CpswAle_delUnicastEntry(Eth_DrvObj.baseAddr, PhysAddrPtr, ETH_NOVLAN_ID, ETH_HOST_PORT_ID);
        }

        /* Check for error table entry is not free*/
        if (Eth_GetMaxAleEntry() == aleIdx)
        {
            retVal = E_NOT_OK;
        }
        else
        {
            retVal = E_OK;
        }
    }

    return (retVal);
}

static void Eth_configureSwitch(const uint8 macAddr[6])
{
    uint32 currPort                     = 0U;
    uint32 flushOldAddrFlag             = (uint32)FALSE;
    uint8  oldMacAddr[ETH_MAC_ADDR_LEN] = {0U, 0U, 0U, 0U, 0U, 0U};

    /* Each port is considered as one controller */
    currPort = (uint32)Eth_DrvObj.portObj.portNum;

    /* Check if MAC address is already set(if this is update MAC
     * operation)
     * if yes, remove old MAC addr entries from ALE
     */
    if ((Std_ReturnType)E_OK == Cpsw_getPortSrcAddr(Eth_DrvObj.baseAddr, currPort, oldMacAddr))
    {
        flushOldAddrFlag = (uint32)TRUE;
    }

    {
        uint32 portMask  = 0U;
        uint32 tmpPortId = 0U, tmpCurrPort = 0U;

        /* For normal CPSW switch mode, set multicast entry. */
        /* Set portmask for all ports */
        tmpPortId   = ((uint32)1U << ETH_HOST_PORT_ID);
        tmpCurrPort = ((uint32)1U << currPort);

        portMask = (tmpPortId | tmpCurrPort);

        (void)CpswAle_addMulticastEntry(Eth_DrvObj.baseAddr, Eth_BcastAddr, ETH_NOVLAN_ID, portMask);
        (void)CpswAle_addMulticastEntry(Eth_DrvObj.baseAddr, Eth_PtpMcastAddr, ETH_NOVLAN_ID, portMask);

        if (((uint32)TRUE) == flushOldAddrFlag)
        {
            (void)CpswAle_delUnicastEntry(Eth_DrvObj.baseAddr, oldMacAddr, ETH_NOVLAN_ID, ETH_HOST_PORT_ID);
        }

        (void)CpswAle_addUnicastEntry(Eth_DrvObj.baseAddr, macAddr, ETH_NOVLAN_ID, ETH_HOST_PORT_ID);
    }
}

static Std_ReturnType Eth_allowReception(uint8 currPort, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
    uint32         aleIdx = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    if ((uint32)TRUE == EthCheckNullMACAddr(PhysAddrPtr))
    {
        /*
         * Requirements SWS_Eth_00147
         * If the physical source address (MAC address) is set to
         * 00:00:00:00:00:00, this shall reduce the filter to the
         * controllers unique unicast MAC address and end
         * promiscuous mode if it was turned on.
         */
        /* Disable bypass mode */
        CpswAle_clearTable(Eth_DrvObj.baseAddr);
        CpswAle_enableBypass(Eth_DrvObj.baseAddr, (uint32)FALSE);

        /* Get controllers unique unicast MAC address which was set earlier by
         * Eth_SetPhysAddr */
        Eth_PortConfigType *pPortCfg = &(Eth_DrvObj.portObj.portCfg);
        /* Sets the ethernet address at the CPSW port  */
        if ((uint32)TRUE != EthCheckNullMACAddr(pPortCfg->macCfg.macAddr))
        {
            Eth_configureSwitch(pPortCfg->macCfg.macAddr);
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    /*
     * Requirements SWS_Eth_00144
     * If the physical source address (MAC address) is set to
     * FF:FF:FF:FF:FF:FF, this shall completely open the filter
     */
    else if (TRUE == Eth_isBcastMacAddr(PhysAddrPtr))
    {
        /* Clear ALE table*/
        CpswAle_clearTable(Eth_DrvObj.baseAddr);
        /* Bypass ALE to pass all data to host */
        CpswAle_enableBypass(Eth_DrvObj.baseAddr, (uint32)TRUE);
    }
    else
    {
        /* Disable bypass mode if it was enabled */
        CpswAle_enableBypass(Eth_DrvObj.baseAddr, (uint32)FALSE);

        if (FALSE == Eth_isUcastMacAddr(PhysAddrPtr))
        {
            uint32 portMask = ((1U << ETH_HOST_PORT_ID) | ((uint32)1U << (uint32)currPort));
            aleIdx          = CpswAle_addMulticastEntry(Eth_DrvObj.baseAddr, PhysAddrPtr, ETH_NOVLAN_ID, portMask);
        }
        else
        {
            aleIdx = CpswAle_addUnicastEntry(Eth_DrvObj.baseAddr, PhysAddrPtr, ETH_NOVLAN_ID, ETH_HOST_PORT_ID);
        }

        /* Check for error table entry is not free*/
        if (Eth_GetMaxAleEntry() == aleIdx)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* nothing */
        }
    }

    return retVal;
}

static uint32 EthCheckNullMACAddr(const uint8 macAddr[ETH_MAC_ADDR_LEN])
{
    uint8  i      = 0U;
    uint32 retVal = (uint32)TRUE;

    for (i = 0U; i < ETH_MAC_ADDR_LEN; i++)
    {
        if ((uint8)0U != macAddr[i])
        {
            retVal = (uint32)FALSE;
            break;
        }
    }

    return retVal;
}

static void Eth_freeTxBuffers(Eth_TxBufObjType *bufObjArray, uint32 numBuffers)
{
    uint32 i = 0U;

    for (i = 0U; i < numBuffers; i++)
    {
        bufObjArray[i].bufState = ETH_BUF_STATE_FREE;
    }
}

static void Eth_enableControllerToTransmitAndReceiveBuffers(const Eth_CpdmaConfigType *pCpdmaConfig)
{
    /*
     *  Acknowledge receive and transmit interrupts for proper interrupt
     *  pulsing
     */
    CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_RX);
    CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_TX);
    CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_RX_THR);

    /* Enable the interrupts for channel 0 and for control core 0 */
    CpswCpdma_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX);
    Cpsw_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX);
    CpswCpdma_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM, CPSW_CH_INTR_TX);
    Cpsw_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM, CPSW_CH_INTR_TX);

#if (ETH_HOST_ERROR_INTERRUPT == STD_ON)
    /* Enable host port error interrupts */
    CpswCpdma_enableHostErrIntr(Eth_DrvObj.baseAddr);
#endif
    /* Enable CPDMA Rx and/or Tx interrupt pacing */
    if ((pCpdmaConfig->rxInterruptPacingEnabled != (uint32)0U) ||
        (pCpdmaConfig->txInterruptPacingEnabled != (uint32)0U))
    {
        /*
         * Calculate prescale count to get 4us pulse from MAIN_CLK
         */
        Cpsw_setPrescale(Eth_DrvObj.baseAddr, ((pCpdmaConfig->pacingClkFreq * (uint32)4U) / (uint32)1000000U));

        if (pCpdmaConfig->rxInterruptPacingEnabled == (uint32)TRUE)
        {
            Cpsw_enableIntrPacing(Eth_DrvObj.baseAddr, CPSW_INTR_TYPE_RX, pCpdmaConfig->rxInterruptsPerMsec);
        }

        if (pCpdmaConfig->txInterruptPacingEnabled == (uint32)TRUE)
        {
            Cpsw_enableIntrPacing(Eth_DrvObj.baseAddr, CPSW_INTR_TYPE_TX, pCpdmaConfig->txInterruptsPerMsec);
        }
    }

    return;
}

static void EthTxBuffDescInit(uint8 ctrlIdx, Eth_CpdmaTxBuffDescQueue *pRing, uint32 numBuffDesc, uint32 startAddr)
{
    Eth_CpdmaTxBuffDescType *pCurrBuffDesc   = (Eth_CpdmaTxBuffDescType *)NULL_PTR;
    Eth_CpdmaTxBuffDescType *pLastBuffDesc   = (Eth_CpdmaTxBuffDescType *)NULL_PTR;
    uint32                   numBufDescCount = 0U;
    (void)ctrlIdx; /* MISRA C Compliance - Reserved for future use */

    pRing->pFreeHead = (Eth_CpdmaTxBuffDescType *)startAddr;

    pRing->pHead      = pRing->pFreeHead;
    pRing->pQueueHead = NULL;
    pRing->pTail      = NULL;
    pRing->pQueueTail = NULL;

    pRing->freeBuffDesc = numBuffDesc;
    pCurrBuffDesc       = pRing->pFreeHead;

    if ((uint32)0U != numBuffDesc)
    {
        /* Number of buffer given to allocate are non-zero*/
        numBufDescCount = numBuffDesc;

        /* Create the tx ring of buffer descriptors */
        while ((uint32)0U != numBufDescCount)
        {
            pCurrBuffDesc->pNextBuffDesc         = pCurrBuffDesc + 0x1U;
            pCurrBuffDesc->globalNextDescPointer = Eth_locToGlobAddr((uintptr_t)(pCurrBuffDesc->pNextBuffDesc));

            pCurrBuffDesc->flagsAndPacketLength = 0U;

            pLastBuffDesc = pCurrBuffDesc;
            pCurrBuffDesc = pCurrBuffDesc->pNextBuffDesc;
            numBufDescCount--;
        }

        /* Link last desc to head to create ring */
        pLastBuffDesc->pNextBuffDesc         = pRing->pFreeHead;
        pLastBuffDesc->globalNextDescPointer = Eth_locToGlobAddr((uintptr_t)(pRing->pFreeHead));
    }
    else
    {
        /* nothing */
    }
}

static void EthRxBuffDescInit(uint8 ctrlIdx, Eth_CpdmaRxBuffDescQueue *pRing, uint32 numBuffDesc, uint32 startAddr)
{
    Eth_CpdmaRxBuffDescType *pCurrBuffDesc = (Eth_CpdmaRxBuffDescType *)NULL_PTR;
    Eth_CpdmaRxBuffDescType *pLastBuffDesc = (Eth_CpdmaRxBuffDescType *)NULL_PTR;
    Eth_RxBufObjType        *pEthBufObj    = (Eth_RxBufObjType *)NULL_PTR;
    uint32                   bufIdx        = 0;
    (void)ctrlIdx; /* MISRA C Compliance - Reserved for future use */

    pRing->pHead  = (Eth_CpdmaRxBuffDescType *)startAddr;
    pCurrBuffDesc = pRing->pHead;

    /* Init and allocate buffer desc */
    for (bufIdx = 0; bufIdx < numBuffDesc; bufIdx++)
    {
        /* Allocate and init buffer object */
        pEthBufObj = &Eth_DrvObj.portObj.rxBufObjArray[bufIdx];
        /* Init desc pointer */
        pCurrBuffDesc->pNextBuffDesc         = pCurrBuffDesc + 0x1U;
        pCurrBuffDesc->globalNextDescPointer = Eth_locToGlobAddr((uintptr_t)(pCurrBuffDesc->pNextBuffDesc));

        /* Assign RX buffer and payload to current desc */
        pCurrBuffDesc->pBufObj                 = pEthBufObj;
        pCurrBuffDesc->pDataBuffer             = pEthBufObj->payload;
        pCurrBuffDesc->globalDataBufferPointer = Eth_locToGlobAddr((uintptr_t)pEthBufObj->payload);

        /* Init desc flags */
        pCurrBuffDesc->flagsAndPacketLength  = CPSW_CPDMA_WRD3_OWN_MASK;
        pCurrBuffDesc->bufferOffsetAndLength = pCurrBuffDesc->pBufObj->len;

        /* Switch to next buffer */
        pLastBuffDesc = pCurrBuffDesc;
        pCurrBuffDesc = pCurrBuffDesc->pNextBuffDesc;
    }

    /* Init ring buffer */
    if (0U != bufIdx)
    {
        /* Link last desc to head to create ring */
        /* We are going to receive starting from the free head */
        pRing->pTail                = pLastBuffDesc;
        pRing->pTail->pNextBuffDesc = pRing->pHead;

        /*
         * Close the ring to indicate end of buffer ring, when CPSW sees
         * 0x0 as next B.D it stops receiving packets as no buffer to store
         * data.
         */
        pRing->pTail->globalNextDescPointer = 0U;

        /*Update actual buffer desc length */
        pRing->freeBuffDesc = bufIdx;
    }
    else
    {
        pRing->pHead        = (Eth_CpdmaRxBuffDescType *)NULL_PTR;
        pRing->pTail        = (Eth_CpdmaRxBuffDescType *)NULL_PTR;
        pRing->freeBuffDesc = 0;
    }
}

static BufReq_ReturnType Eth_HwProvideTxBufferIdx(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr,
                                                  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) * BufPtr,
                                                  P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr)
{
    Eth_BufIdxType      bufIdx       = 0;
    uint16              allocBuffLen = 0U;
    Eth_PortObject     *pPortObj;
    BufReq_ReturnType   retVal   = BUFREQ_OK;
    Eth_TxFrameObjType *ethFrame = (Eth_TxFrameObjType *)NULL_PTR;

    /* Each port is considered as one controller */
    pPortObj = &(Eth_DrvObj.portObj);

    /* This function is only called if having freeBuffDesc, next Tx idx is free buffer */
    bufIdx       = (pPortObj->lastTxIdx + 1U) % ETH_NUM_TX_BUFFERS;
    *BufIdxPtr   = bufIdx;
    allocBuffLen = pPortObj->txBufObjArray[bufIdx].len;

    pPortObj->lastTxIdx = bufIdx; /* store last used index */

    /* Add Ethernet header length to BufPtr and return to application */
    ethFrame                                 = pPortObj->txBufObjArray[bufIdx].payload;
    *BufPtr                                  = ethFrame->payload;
    pPortObj->txBufObjArray[bufIdx].bufState = ETH_BUF_STATE_IN_USE;

    /* Enter critical section */
    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
    /* Decrement free bds, since one is consumed */
    Eth_DrvObj.txDescRing.freeBuffDesc -= 1U;
    /* Exit critical section */
    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    if (*LenBytePtr > (uint16)(allocBuffLen - ETH_HLEN))
    {
        /*
         * [SWS_Eth_00079] If a buffer is requested with
         *  Eth_ProvideTxBuffer that is larger than the available
         *  buffer length, the buffer shall not be locked but
         *  return the available length and BUFREQ_E_OVFL.
         */

        /*
         * Buffer available is smaller than (requested + Header)
         * Subtract header length from allocated size
         */
        *LenBytePtr = (allocBuffLen - ETH_HLEN);
        retVal      = BUFREQ_E_OVFL;
    }
    else
    {
        /* nothing */
    }

    return retVal;
}

FUNC(BufReq_ReturnType, ETH_CODE)
Eth_provideHwTxBuffer(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr,
                      P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) * BufPtr,
                      P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

/* Try to process TX buffer to get free desc before TX IRQ happens */
#if (STD_ON == ETH_ENABLE_TX_INTERRUPT)
    if ((uint32)0U == Eth_DrvObj.txDescRing.freeBuffDesc)
    {
        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
        /* Below process TX will exit then re-enter exclusive with EthIf tx confirm callback,
           disable TX interrupt here to avoid race condition with process TX in IRQ handler */
        CpswCpdma_disableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM, CPSW_CH_INTR_TX);
        Eth_processTxBuffDesc(Eth_DrvObj.ctrlIdx, ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM);
        CpswCpdma_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM, CPSW_CH_INTR_TX);
        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
    }
#endif

    /* Make sure to get empty buffer to fit data and header */

    /*
     * check if transmit buffer descriptor is available for this buffer
     * request. As no. of buffers can be more than more than no. of bd's we
     * may encounter a case where buffer is available but not buffer
     * descriptor.
     */

    if ((uint32)0U == Eth_DrvObj.txDescRing.freeBuffDesc)
    {
        retVal = BUFREQ_E_BUSY;
    }
    else
    {
        retVal = Eth_HwProvideTxBufferIdx(BufIdxPtr, BufPtr, LenBytePtr);
    }

    return retVal;
}

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
static uint16 Eth_genPseudoCheckSumIPv4(uint8 *ipPktStart, uint16 ipPktPayLen)
{
    Eth_Ip4Hdr *pIp4Hdr = (Eth_Ip4Hdr *)ipPktStart;
    uint32      sum =
        ((pIp4Hdr->src_addr & 0XFFFFU) + ((pIp4Hdr->src_addr >> 16U) & 0XFFFFU) + (pIp4Hdr->dst_addr & 0XFFFFU) +
         ((pIp4Hdr->dst_addr >> 16U) & 0XFFFFU) + (htons((uint16)(pIp4Hdr->protocol))) + (htons(ipPktPayLen)));

    /* Split the 32-bit sum into two 16-bit num and add them up
     * until the sum is reduced to 16bits */
    while (sum >> 16U)
    {
        sum = (sum & 0XFFFFU) + (sum >> 16U);
    }

    return (uint16) ~(sum & 0XFFFFU);
}

static uint16 Eth_genPseudoCheckSumIPv6(uint8 *ipPktStart, uint16 ipPktPayLen)
{
    Eth_Ip6Hdr *pIp6Hdr = (Eth_Ip6Hdr *)ipPktStart;
    uint32      sum     = 0U;
    uint32      idx     = 0U;

    for (idx = 0U; idx < 4U; idx++)
    {
        sum += ((pIp6Hdr->src_addr[idx] & 0XFFFFU) + ((pIp6Hdr->src_addr[idx] >> 16U) & 0XFFFFU) +
                (pIp6Hdr->dst_addr[idx] & 0XFFFFUL) + ((pIp6Hdr->dst_addr[idx] >> 16U) & 0XFFFFU));
    }
    sum += ((htons((uint16)(pIp6Hdr->next_hdr))) + (htons(ipPktPayLen)));

    /* Split the 32-bit sum into two 16-bit num and add them up
     * until the sum is reduced to 16bits */
    while (sum >> 16U)
    {
        sum = (sum & 0XFFFFU) + (sum >> 16U);
    }

    return (uint16) ~(sum & 0XFFFFUL);
}
static uint32 Eth_setPseudoCheckSum(Eth_FrameHeaderType *pEthPkt, Eth_FrameType frameType)
{
    uint32 chksumInfo = 0U;
    uint8 *ipPktStart = Eth_getIpPktStart((uint8 *)pEthPkt);
    uint16 (*pseudo_chksum)(uint8 *, uint16);
    Eth_UdpHdr *pUdpHdr     = (Eth_UdpHdr *)NULL_PTR;
    Eth_TcpHdr *pTcpHdr     = (Eth_TcpHdr *)NULL_PTR;
    uint8       ipPktHdrLen = 0U;
    uint8       protocol    = 0U;

    uint16 ipPktPayloadLen       = 0U;
    uint8  csumCoverageStartByte = 0U;
    uint8  csumResultByte        = 0U;

    if (ETH_P_IPV6 == frameType)
    {
        ipPktHdrLen     = IPV6_HDR_LEN;
        ipPktPayloadLen = htons(((Eth_Ip6Hdr *)ipPktStart)->pay_len);
        pseudo_chksum   = &Eth_genPseudoCheckSumIPv6;
        protocol        = ((Eth_Ip6Hdr *)ipPktStart)->next_hdr;
    }
    else
    {
        ipPktHdrLen     = ((((Eth_Ip4Hdr *)ipPktStart)->v_hl & 0x0FU) << 2U);
        ipPktPayloadLen = htons(((Eth_Ip4Hdr *)ipPktStart)->len) - ipPktHdrLen;
        pseudo_chksum   = &Eth_genPseudoCheckSumIPv4;
        protocol        = ((Eth_Ip4Hdr *)ipPktStart)->protocol;
    }

#if (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP)
    if (IPPROTO_TCP == protocol)
    {
        pTcpHdr               = (Eth_TcpHdr *)(ipPktStart + ipPktHdrLen);
        csumCoverageStartByte = (uint8 *)pTcpHdr - (uint8 *)pEthPkt + 1U;
        csumResultByte        = (uint8 *)(&(pTcpHdr->checksum)) - (uint8 *)pEthPkt + 1U;
        pTcpHdr->checksum     = ~(pseudo_chksum(ipPktStart, ipPktPayloadLen));

        /* Update encap checksum info value */
        chksumInfo  = ipPktPayloadLen << ENETDMA_TXCSUMINFO_CHKSUM_BYTECNT_SHIFT;
        chksumInfo += csumCoverageStartByte << ENETDMA_TXCSUMINFO_CHKSUM_STARTBYTE_SHIFT;
        chksumInfo += csumResultByte << ENETDMA_TXCSUMINFO_CHKSUM_RESULT_SHIFT;
    }
#endif

#if (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP)
    if (IPPROTO_UDP == protocol)
    {
        pUdpHdr               = (Eth_UdpHdr *)(ipPktStart + ipPktHdrLen);
        csumCoverageStartByte = (uint8 *)pUdpHdr - (uint8 *)pEthPkt + 1U;
        csumResultByte        = (uint8 *)(&(pUdpHdr->checksum)) - (uint8 *)pEthPkt + 1U;
        pUdpHdr->checksum     = ~(pseudo_chksum(ipPktStart, ipPktPayloadLen));

        /* Update encap checksum info value */
        chksumInfo  = ipPktPayloadLen << ENETDMA_TXCSUMINFO_CHKSUM_BYTECNT_SHIFT;
        chksumInfo += csumCoverageStartByte << ENETDMA_TXCSUMINFO_CHKSUM_STARTBYTE_SHIFT;
        chksumInfo += csumResultByte << ENETDMA_TXCSUMINFO_CHKSUM_RESULT_SHIFT;
        chksumInfo += 1U << ENETDMA_TXCSUMINFO_CHKSUM_INV_SHIFT;
    }
#endif

    return chksumInfo;
}

static inline uint8 *Eth_getIpPktStart(uint8 *frameBuffer)
{
    Eth_FrameHeaderType *header = (Eth_FrameHeaderType *)frameBuffer;
    const uint32         ipPacketStartOffset =
        (header->h_proto == htons(ETH_P_8021Q)) ? (ETH_HLEN + SIZEOF_VLAN_HDR) : (ETH_HLEN);

    return &frameBuffer[ipPacketStartOffset];
}
#endif /* CHECKSUM_OFFLOAD */

FUNC(Std_ReturnType, ETH_CODE)
Eth_transmitHw(VAR(Eth_BufIdxType, AUTOMATIC) BufIdx, VAR(Eth_FrameType, AUTOMATIC) FrameType,
               VAR(boolean, AUTOMATIC) TxConfirmation, VAR(uint16, AUTOMATIC) LenByte,
               P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
    Std_ReturnType      retVal   = E_OK;
    Eth_PortObject     *pPortObj = (Eth_PortObject *)NULL_PTR;
    Eth_PortConfigType *pPortCfg = (Eth_PortConfigType *)NULL_PTR;
    uint32              totalLen = 0U;

    /* Each port is considered as one controller */
    pPortObj = &(Eth_DrvObj.portObj);
    pPortCfg = &pPortObj->portCfg;

    if (ETH_BUF_STATE_FREE == pPortObj->txBufObjArray[BufIdx].bufState)
    {
        /*
         * Buffer is not allocated through call to Eth_ProvideTxBuffer or
         * already qued for transmit.
         */
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        Eth_TxFrameObjType       *pDataBuffer;
        Eth_CpdmaTxBuffDescType  *pXmitTxBuffDesc;
        Eth_TxBufObjType         *pTempBufObj = &(pPortObj->txBufObjArray[BufIdx]);
        Eth_CpdmaTxBuffDescQueue *pTxDescRing = &(Eth_DrvObj.txDescRing);

        /* Take packet from Tx Buffer ring using BufIdx */
        pDataBuffer = pTempBufObj->payload;
        totalLen    = (uint32)LenByte + ETH_HLEN;

        /*
         * Make sure the driver does not transmit packet less than min. as per the
         * Ethernet standards.
         */
        if (totalLen < ETH_ZLEN)
        {
            uint32 remLenInBytes = (ETH_ZLEN - totalLen);
            /* Zero pad the packet data to at least 60 known bytes */

            (void)memset(((void *)(&(pDataBuffer->payload[LenByte]))), 0, (size_t)remLenInBytes);
            /* With Ethernet FCS, total transmitted size will be the minimum 64 bytes */
            totalLen = ETH_ZLEN;
        }

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
        if ((boolean)TRUE == pTempBufObj->enableEgressTimeStamp)
        {
            uint8  msgtype;
            uint16 seqid;

            msgtype  = pDataBuffer->payload[0];
            seqid    = pDataBuffer->payload[TIME_SYNC_OFFSET_PTP_SEQUENCE_ID + 1U];
            seqid    = seqid << 8U;
            seqid   += pDataBuffer->payload[TIME_SYNC_OFFSET_PTP_SEQUENCE_ID];

            pTempBufObj->bufCptsEventInfo.messageType = (uint8)(msgtype & (uint8)0xFU);
            pTempBufObj->bufCptsEventInfo.sequenceId  = ntohs(seqid);
        }

        pTempBufObj->type = FrameType;
#endif
        /* set application callback flag */
        pTempBufObj->txConfirmation = TxConfirmation;

        (void)memcpy(pDataBuffer->header.srcMacAddr, &(pPortCfg->macCfg.macAddr[0U]), ETH_MAC_ADDR_LEN);
        (void)memcpy(pDataBuffer->header.dstMacAddr, PhysAddrPtr, ETH_MAC_ADDR_LEN);
        pDataBuffer->header.h_proto =
            ((FrameType & (Eth_FrameType)0xFFU) << 8U) | ((FrameType & (Eth_FrameType)0xFF00U) >> 8U);

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
        uint32 chksumInfo = 0U;

        /* For VLAN Tagged packet, get the payload ethertype */
        if (ETH_P_8021Q == FrameType)
        {
            FrameType = ntohs(((Eth_vlanFrameHdr *)&(pDataBuffer->header))->etherType);
        }

        /* HW Checksum Offload is only supported on IP frames */
        if (ETH_P_IP == FrameType || ETH_P_IPV6 == FrameType)
        {
            chksumInfo = Eth_setPseudoCheckSum(&(pDataBuffer->header), FrameType);
        }

        /* Append checksum info and increase packet length */
        if (0U != chksumInfo)
        {
            pDataBuffer->chksumInfo = chksumInfo;
            totalLen                = totalLen + ENET_CPDMA_ENCAPINFO_CHECKSUM_INFO_LEN;
        }
#endif
        /* Flush buffers */
        if ((Eth_DrvObj.enableCacheOps == (uint32)TRUE) && (Eth_DrvObj.cacheFlushFnPtr != (Eth_CacheFlushType)NULL))
        {
            /* Double cast to avoid MISRA-C:2004 11.4 */
            Eth_DrvObj.cacheFlushFnPtr((uint8 *)((void *)pDataBuffer), totalLen);
        }

        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

        /* Get the buffer descriptor which is free to transmit */
        pXmitTxBuffDesc = pTxDescRing->pFreeHead;

        /* Only one TX frame length = 1536 will fit into 11 bit packet
         * each desc will have both SOP and EOP flag */
        pXmitTxBuffDesc->flagsAndPacketLength =
            totalLen | CPSW_CPDMA_WRD3_OWN_MASK | CPSW_CPDMA_WRD3_SOP_MASK | CPSW_CPDMA_WRD3_EOP_MASK;
#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
        if (0U != chksumInfo) /* Encap checksum at start of CPDMA data buffer */
        {
            pXmitTxBuffDesc->flagsAndPacketLength |= CPSW_CPDMA_WRD3_CHKSUM_ENCAP_MASK;
            pXmitTxBuffDesc->globalDataBufferPointer = (uint32)Eth_locToGlobAddr((uintptr_t)&(pDataBuffer->chksumInfo));
        }
        else /* no checksum encap, start of CPDMA databuffer is Eth frame */
#endif
        {
            pXmitTxBuffDesc->globalDataBufferPointer = (uint32)Eth_locToGlobAddr((uintptr_t)&(pDataBuffer->header));
        }
        /* Initialize the buffer pointer and length */
        pXmitTxBuffDesc->pDataBuffer           = pDataBuffer;
        pXmitTxBuffDesc->bufferOffsetAndLength = totalLen;

        /* Update Transmit ring head */
        pTxDescRing->pFreeHead = pXmitTxBuffDesc->pNextBuffDesc;

        /* Tail describes last packet transferred */
        pTxDescRing->pTail = pXmitTxBuffDesc;

        /* Copy buffer information into TX buffer descriptors */
        pXmitTxBuffDesc->pBufObj = pTempBufObj;

        /* if all previous TX done or not yet started then start DMA with single pXmitTxBuffDesc */
        if (pTxDescRing->pQueueHead == NULL)
        {
            pTxDescRing->pQueueHead = pTxDescRing->pHead;
            pTxDescRing->pQueueTail = pTxDescRing->pTail;
            pTxDescRing->pHead      = pTxDescRing->pFreeHead;
            pTxDescRing->pTail      = NULL;

            /* start new queue DMA */
            pTxDescRing->pQueueTail->globalNextDescPointer = 0;
            CpswCpdma_writeTxChHdp(Eth_DrvObj.baseAddr, Eth_locToGlobAddr((uintptr_t)pTxDescRing->pQueueHead),
                                   ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM);
        }
        else
        {
            /* nothing */
        }

        if (((boolean)FALSE) == pTempBufObj->txConfirmation)
        {
            /*
             * Requirements: SWS_Eth_00089 (If TxConfirmation is false, the
             * function shall release the buffer resource).
             */
            pTempBufObj->bufState = ETH_BUF_STATE_FREE;
        }

        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}

FUNC(void, ETH_CODE)
Eth_receiveHw(P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr)
{
    uint32 rxIntFlags = 0U, threshIntFlags = 0U;
    uint32 channelNum = 0U, channelMask = 0U;
    *RxStatusPtr = ETH_NOT_RECEIVED;

    rxIntFlags = Cpsw_getChIntrStatus(Eth_DrvObj.baseAddr, CPSW_CH_INTR_RX);

    threshIntFlags = Cpsw_getChIntrStatus(Eth_DrvObj.baseAddr, CPSW_CH_INTR_RX_THR);

    rxIntFlags |= threshIntFlags;

    /* Look for receive interrupts from across all CPDMA Rx Channels */
    while ((uint32)0U != rxIntFlags)
    {
        channelMask = (uint32)0x1U << channelNum;

        if ((uint32)0U != (uint32)(rxIntFlags & channelMask))
        {
            SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

            *RxStatusPtr = EthRxBuffDescProcessSingle(Eth_DrvObj.ctrlIdx, channelNum);
            SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
        }

        /* Clear the channel flag for the channel just handled */
        rxIntFlags &= ~channelMask;
        channelNum++;
    }

    if (ETH_NOT_RECEIVED != *RxStatusPtr)
    {
        if ((uint32)0U != threshIntFlags)
        {
            /* All outstanding RX_THRESH interrupts were handled */
            CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_RX_THR);
        }

        /* Write the EOI register */
        CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_RX);
    }

    return;
}

static void EthRxBuffDescRxStatus(const Eth_CpdmaRxBuffDescType *pCurrRxBuffDesc, Eth_RxStatusType *rxStatus)
{
    if (CPSW_CPDMA_WRD3_OWN_DISABLE == (uint32)HW_GET_FIELD(pCurrRxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_OWN))
    {
        /**< frame received, more frames are available */
        *rxStatus = ETH_RECEIVED_MORE_DATA_AVAILABLE;
    }
    else
    {
        /**< frame received, no further frames available */
        *rxStatus = ETH_RECEIVED;
    }
}

static Eth_RxStatusType EthRxBuffDescProcessSingle(uint8 ctrlIdx, uint32 chNum)
{
    Eth_CpdmaRxBuffDescType  *pCurrRxBuffDesc = (Eth_CpdmaRxBuffDescType *)NULL_PTR;
    Eth_CpdmaRxBuffDescQueue *pRxDescRing     = &(Eth_DrvObj.rxDescRing);
    uint32                    cp              = 0U;
    Eth_RxStatusType          rxStatus        = ETH_NOT_RECEIVED;
    uint32                    endOfQueueFlag  = 0U;

    cp = CpswCpdma_readRxChCp(Eth_DrvObj.baseAddr, chNum);

    /* Only do stuff if not a teardown request for this channel */
    if (CPSW_CPDMA_TEAR_DWN_ACK != cp)
    {
        /* Get the bd which contains the earliest filled data */
        pCurrRxBuffDesc = pRxDescRing->pHead;

        /*
         * Process the receive buffer descriptors. When the DMA completes
         * reception, OWNERSHIP flag will be cleared.
         */
        if (CPSW_CPDMA_WRD3_OWN_DISABLE ==
            (uint32)HW_GET_FIELD(pCurrRxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_OWN))
        {
            EthRxProcessPacket(ctrlIdx, pCurrRxBuffDesc);

            /* Get endOfQueueFlag before update desc */
            endOfQueueFlag = HW_GET_FIELD(pCurrRxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_EOQ);

            /* Reset descriptor flag to continue RX using the same buffer */
            pCurrRxBuffDesc->flagsAndPacketLength  = CPSW_CPDMA_WRD3_OWN_MASK;
            pCurrRxBuffDesc->bufferOffsetAndLength = pCurrRxBuffDesc->pBufObj->len;

            /*
             * Check if Receive threshold is enabled if yes write one to
             * increment number of buffers available(This is a write to
             * increment field).
             */
            if ((uint32)0U != Eth_DrvObj.ethConfig.cpdmaCfg.rxThreshCount)
            {
                CpswCpdma_setRxChFreeBufCnt(Eth_DrvObj.baseAddr, chNum, 1U);
            }

            /* Append processed buff desc to pTail */
            EthRxBuffDescEnqueue(pRxDescRing, pCurrRxBuffDesc);

            /* Acknowledge latest processed descriptors */
            CpswCpdma_writeRxChCp(Eth_DrvObj.baseAddr, chNum, Eth_locToGlobAddr((uintptr_t)pCurrRxBuffDesc));

            /*
             * If PHead descriptor is NULL means receive operation has stopped due
             * to unavailability of buffers. Now that some buffers are allocated by
             * application(in case of this function called by Eth_Receive) restart
             * receive operation by writing to RX HDP.
             */
            if (0U != endOfQueueFlag)
            {
                CpswCpdma_writeRxChHdp(Eth_DrvObj.baseAddr, Eth_locToGlobAddr((uintptr_t)(pRxDescRing->pHead)), chNum);
            }
            else
            {
                /* nothing */
            }

            EthRxBuffDescRxStatus(pCurrRxBuffDesc->pNextBuffDesc, &rxStatus);
        }
        else
        {
            /**< frame not received, no further frames available */
            rxStatus = ETH_NOT_RECEIVED;
        }
    }
    else
    {
        EthRxChTearDown(chNum);
        /**< frame not received, no further frames available */
        rxStatus = ETH_NOT_RECEIVED;
    }

    return rxStatus;
}

static void EthRxProcessPacket(uint8 ctrlIdx, const Eth_CpdmaRxBuffDescType *pCurrRxBuffDesc)
{
    uint16              totLen = 0U, dataLen = 0U;
    uint8               srcMacAddr[ETH_MAC_ADDR_LEN] = {0U, 0U, 0U, 0U, 0U, 0U};
    boolean             isBroadcast                  = FALSE;
    Eth_FrameType       frameType                    = 0U;
    Eth_RxFrameObjType *pFrameBuffer                 = (Eth_RxFrameObjType *)NULL_PTR;
    uint8              *frameDataPtr                 = (uint8 *)NULL_PTR;

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
    uint32  chkSumInfo    = 0U;
    boolean isChkSumValid = TRUE;
#endif
    /* Get the total length of the packet */

    /*
     * Buffer length field is 11 bit so typecasting to uint16
     * will not lose data.
     */
    totLen = (uint16)HW_GET_FIELD(pCurrRxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_PKT_LEN);

    /* Remove FCS/CRC (4 octets) from total size as CPDMA passes CRC along
     * with data */
    totLen = totLen - (uint16)4U;

    /* Get the EthFrame which is associated with the current bd */
    pFrameBuffer = pCurrRxBuffDesc->pDataBuffer;

    if ((Eth_DrvObj.enableCacheOps == (uint32)TRUE) &&
        (Eth_DrvObj.cacheInvalidateFnPtr != (Eth_CacheInvalidateType)NULL))
    {
        Eth_DrvObj.cacheInvalidateFnPtr((uint8 *)((void *)pFrameBuffer), (uint32)totLen);
    }

    /* Process the packet */
    (void)memcpy(srcMacAddr, pFrameBuffer->header.srcMacAddr, ETH_MAC_ADDR_LEN);
    /* Fetch information like frametype, Isbroadcast from packet */
    isBroadcast = Eth_isBcastMacAddr(pFrameBuffer->header.dstMacAddr);

    frameType = ntohs((Eth_FrameType)pFrameBuffer->header.h_proto);

    frameDataPtr = pFrameBuffer->payload;
    dataLen      = totLen - ((uint16)sizeof(Eth_FrameHeaderType));
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)

    /*
     * If timestamping is enabled then we check for CPTS event each
     * received packet.
     */
    if ((uint32)0U != CpswCpts_getEventPendStatus(Eth_DrvObj.cptsObj.cpswBaseAddr))
    {
        /*
         * Pop the event into SW queue to be returned to when
         * Eth_GetIngressTimeStamp is called from EthIf_RxIndication
         */
        CpswCpts_handleEvents(&Eth_DrvObj.cptsObj);
    }
#endif

#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
    if (0U != HW_GET_FIELD(pCurrRxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_RX_WRD3_CHKSUM_ENCAP))
    {
        /* Get 4 bytes checksum info from last data packet */
        memcpy(&chkSumInfo, &frameDataPtr[dataLen], ENET_CPDMA_ENCAPINFO_CHECKSUM_INFO_LEN);

        /* Check for checksum error and raise flag for TCP/UDP packet */
        if (0U != HW_GET_FIELD(chkSumInfo, ENETDMA_RXCSUMINFO_CHKSUM_ERR))
        {
            if ((0U != HW_GET_FIELD(chkSumInfo, ENETDMA_RXCSUMINFO_IPV4_VALID)) ||
                (0U != HW_GET_FIELD(chkSumInfo, ENETDMA_RXCSUMINFO_IPV6_VALID)))
            {
                /* check TCP detected */
                if (0U != HW_GET_FIELD(chkSumInfo, ENETDMA_RXCSUMINFO_TCP_UDP_N))
                {
#if (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP)
                    isChkSumValid = FALSE;
#endif
                }
                else /* UDP detected */
                {
#if (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP)
                    isChkSumValid = FALSE;
#endif
                }
            }
        }

        /* Remove checksum info from data packet */
        dataLen = dataLen - ENET_CPDMA_ENCAPINFO_CHECKSUM_INFO_LEN;
    }

    if (TRUE == isChkSumValid)
#endif
    {
        /* Release SchM before notify upper layer */
        /* Both RX IRQ and RX Threshold IRQ handler may call EthIf_Rxindication(),
         * disable both RX IRQs here to avoid race condition */
        CpswCpdma_disableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX);
        if (Eth_DrvObj.ethConfig.cpdmaCfg.rxThreshCount != (uint32)0U)
        {
            CpswCpdma_disableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX_THR);
        }
        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
        EthIf_RxIndication(ctrlIdx, frameType, isBroadcast, &srcMacAddr[0U], (Eth_DataType *)frameDataPtr, dataLen);
        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
        CpswCpdma_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX);
        if (Eth_DrvObj.ethConfig.cpdmaCfg.rxThreshCount != (uint32)0U)
        {
            CpswCpdma_enableChIntr(Eth_DrvObj.baseAddr, ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM, CPSW_CH_INTR_RX_THR);
        }
    }
}

static void EthRxChTearDown(uint32 chNum)
{
    /* The software should acknowledge a teardown interrupt with a
     * FFFF_FFFCh Acknowledge value */
    CpswCpdma_writeRxChCp(Eth_DrvObj.baseAddr, chNum, (uint32)CPSW_CPDMA_TEAR_DWN_ACK);
    CpswCpdma_disableRxCh(Eth_DrvObj.baseAddr);

    /*
     * Set Eth controller mode to disabled if both RX and TX
     * channels are torn. Else set this channel torn flag to TRUE so
     * when TX channel is torn it can use this for disabling
     * controller.
     */
    if (TRUE == Eth_CpdmaTxChTornFlag)
    {
        Eth_ControllerModeChangeFlag = TRUE;
        Eth_CpdmaTxChTornFlag        = FALSE;
        Eth_DrvObj.ctrlMode          = ETH_MODE_DOWN;
    }
    else
    {
        Eth_CpdmaRxChTornFlag = TRUE;
    }
}

static void EthRxBuffDescEnqueue(Eth_CpdmaRxBuffDescQueue *pRxDescRing, Eth_CpdmaRxBuffDescType *pNewTail)
{
    /* Enqueue if new tail differ with current tail */
    if (pNewTail != pRxDescRing->pTail)
    {
        /* Close the ring to prevent overwriting of ethFrame data. */
        pNewTail->globalNextDescPointer = 0;

        /* restore null desc pointer */
        pRxDescRing->pTail->globalNextDescPointer = Eth_locToGlobAddr((uintptr_t)pRxDescRing->pTail->pNextBuffDesc);

        /* Update head pointers to next of last processed buffer */
        pRxDescRing->pHead = pNewTail->pNextBuffDesc;
        pRxDescRing->pTail = (Eth_CpdmaRxBuffDescType *)pNewTail;
    }
    else
    {
        /* nothing */
    }
}

void Eth_processRxBuffDesc(uint8 ctrlIdx, uint32 chNum)
{
    Eth_CpdmaRxBuffDescType  *pCurrRxBuffDesc = (Eth_CpdmaRxBuffDescType *)NULL_PTR;
    Eth_CpdmaRxBuffDescType  *pLastBuffDesc   = (Eth_CpdmaRxBuffDescType *)NULL_PTR;
    Eth_CpdmaRxBuffDescQueue *pRxDescRing     = &(Eth_DrvObj.rxDescRing);
    uint32                    cp = 0U, packetCount = 0U;
    uint32                    endOfQueueFlag = 0U;

    cp = CpswCpdma_readRxChCp(Eth_DrvObj.baseAddr, chNum);

    /* Only do stuff if not a teardown request for this channel */
    if (CPSW_CPDMA_TEAR_DWN_ACK != cp)
    {
        /* Get the bd which contains the earliest filled data */
        pCurrRxBuffDesc = pRxDescRing->pHead;

        /*
         * Process the receive buffer descriptors. When the DMA completes
         * reception, OWNERSHIP flag will be cleared.
         */
        while (CPSW_CPDMA_WRD3_OWN_DISABLE ==
               (uint32)HW_GET_FIELD(pCurrRxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_OWN))
        {
            EthRxProcessPacket(ctrlIdx, pCurrRxBuffDesc);
            /* Get endOfQueueFlag before update desc */
            endOfQueueFlag = HW_GET_FIELD(pCurrRxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_EOQ);

            /* Reset descriptor flag to continue RX using the same buffer */
            pCurrRxBuffDesc->flagsAndPacketLength  = CPSW_CPDMA_WRD3_OWN_MASK;
            pCurrRxBuffDesc->bufferOffsetAndLength = pCurrRxBuffDesc->pBufObj->len;

            /* Switch to next RX buffer */
            pLastBuffDesc   = pCurrRxBuffDesc;
            pCurrRxBuffDesc = pCurrRxBuffDesc->pNextBuffDesc;
            packetCount++;
        }

        /* Update buff desc if having processed packet */
        if ((uint32)0U != packetCount)
        {
            /*
             * Check if Receive threshold is enabled if yes write one to
             * increment number of buffers available(This is a write to
             * increment field).
             */
            if ((uint32)0U != Eth_DrvObj.ethConfig.cpdmaCfg.rxThreshCount)
            {
                CpswCpdma_setRxChFreeBufCnt(Eth_DrvObj.baseAddr, chNum, packetCount);
            }

            /* Append processed buff desc to pTail */
            EthRxBuffDescEnqueue(pRxDescRing, pLastBuffDesc);

            /* Acknowledge latest processed descriptors */
            CpswCpdma_writeRxChCp(Eth_DrvObj.baseAddr, chNum, Eth_locToGlobAddr((uintptr_t)pLastBuffDesc));

            /*
             * If PHead descriptor is NULL means receive operation has stopped due
             * to unavailability of buffers. Now that some buffers are allocated by
             * application(in case of this function called by Eth_Receive) restart
             * receive operation by writing to RX HDP.
             */
            if (0U != endOfQueueFlag)
            {
                CpswCpdma_writeRxChHdp(Eth_DrvObj.baseAddr, Eth_locToGlobAddr((uintptr_t)(pRxDescRing->pHead)), chNum);
            }
            else
            {
                /* nothing */
            }
        }
    }
    else
    {
        EthRxChTearDown(chNum);
    }
}

static void EthTxBuffProcess(uint8 ctrlIdx, Eth_TxBufObjType *pBufObj)
{
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
    uint32 loopCnt = 0U;
#endif

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)

    /*
     * If timestamping is enabled then we check CPTS event for
     * each transmitted packet.
     */
    if ((CPSW_ETHTYPE_PTP1588 == pBufObj->type) && (((boolean)TRUE) == pBufObj->enableEgressTimeStamp))
    {
        while (loopCnt < CPSW_CPTS_RETRIEVE_TS_LOOP)
        {
            if ((uint32)0U != CpswCpts_getEventPendStatus(Eth_DrvObj.cptsObj.cpswBaseAddr))
            {
                /*
                 * Pop the event into SW queue to be returned to when
                 * getEgressTimeStamp is called from EthIf_TxConfirmation
                 */
                CpswCpts_handleEvents(&Eth_DrvObj.cptsObj);
                break;
            }
            else
            {
                loopCnt++;
            }
        }
    }
    else
    {
        /* No thing */
    }
#endif
    if (((boolean)TRUE) == pBufObj->txConfirmation)
    {
        /* Release SchM before notify upper layer */
        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
        /*
         * Tx Buffer descriptor(FHOST) doesn't have any field to check transmit error, so
         * EthIf_TxConfirmation always indicates Transmit status with E_OK.
         */
        EthIf_TxConfirmation((uint8)ctrlIdx, (Eth_BufIdxType)pBufObj->bufIdx, E_OK);
        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)

        /*
         * As Eth_GetEgressTimeStamp is only called from
         * EthIf_TxConfirmation function, buffer timestamp is
         * processed by now, hence clear flag
         */
        pBufObj->enableEgressTimeStamp = (boolean)FALSE;
#endif

        /*
         *  If TxConfirmation is FALSE buffer is freed in the Eth_Transmit
         */
        pBufObj->bufState = ETH_BUF_STATE_FREE;
    }
}

void Eth_processTxBuffDesc(uint8 ctrlIdx, uint32 chNum)
{
    Eth_CpdmaTxBuffDescType  *pCurrTxBuffDesc = (Eth_CpdmaTxBuffDescType *)NULL_PTR;
    Eth_CpdmaTxBuffDescType  *pLastBuffDesc   = (Eth_CpdmaTxBuffDescType *)NULL_PTR;
    uint32                    endOfQueueFlag  = 0U;
    Eth_CpdmaTxBuffDescQueue *pTxDescRing     = &(Eth_DrvObj.txDescRing);

    if (NULL != pTxDescRing->pQueueHead) /*only check if TX in progress */
    {
        pCurrTxBuffDesc = pTxDescRing->pQueueHead;
        /* loop to process each packet in queue, queue end with pCurrTxBuffDesc->pNextBuffDesc ==
         * NULL */
        /* Skip check OWNER with SOP because all TX desc have SOP and EOP flag */
        while (CPSW_CPDMA_WRD3_OWN_ENABLE !=
               (uint32)HW_GET_FIELD(pCurrTxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_OWN))
        {
            /* Process current packet buffer */
            EthTxBuffProcess(ctrlIdx, pCurrTxBuffDesc->pBufObj);

            /* Need save endOfQueueFlag before clear */
            endOfQueueFlag = (uint32)HW_GET_FIELD(pCurrTxBuffDesc->flagsAndPacketLength, CPSW_CPDMA_WRD3_EOQ);

            /* Clear Buff desc flag and Acknowledge completion pointer */
            pCurrTxBuffDesc->flagsAndPacketLength  = 0U;
            pTxDescRing->freeBuffDesc             += 1U;

            /* If this is last b.d. transmitted, then acknowledge using this */
            pLastBuffDesc = pCurrTxBuffDesc;

            /* Check end of queue or next packet buffer */
            if (0U != endOfQueueFlag)
            {
                /* Restore global next buff desc from null */
                pCurrTxBuffDesc->globalNextDescPointer = Eth_locToGlobAddr((uintptr_t)(pCurrTxBuffDesc->pNextBuffDesc));
                pTxDescRing->pQueueHead                = NULL; /* Reset queue after DMA queue complete */
                pTxDescRing->pQueueTail                = NULL;
                break;
            }
            else
            {
                /* switch to check next bd */
                pCurrTxBuffDesc         = pCurrTxBuffDesc->pNextBuffDesc;
                pTxDescRing->pQueueHead = pCurrTxBuffDesc;
            }
        };

        /* Acknowledge CPSW and free the corresponding ethFrame */
        if (NULL_PTR != pLastBuffDesc)
        {
            CpswCpdma_writeTxChCp(Eth_DrvObj.baseAddr, chNum, (uint32)Eth_locToGlobAddr((uintptr_t)pLastBuffDesc));
        }

        /* Check to start new DMA queue */
        if ((NULL != pTxDescRing->pTail) && (0U != endOfQueueFlag))
        {
            pTxDescRing->pQueueHead = pTxDescRing->pHead;
            pTxDescRing->pQueueTail = pTxDescRing->pTail;
            pTxDescRing->pHead      = pTxDescRing->pFreeHead;
            pTxDescRing->pTail      = NULL;

            /* start new queue DMA */
            pTxDescRing->pQueueTail->globalNextDescPointer = 0U;
            CpswCpdma_writeTxChHdp(Eth_DrvObj.baseAddr, Eth_locToGlobAddr((uintptr_t)pTxDescRing->pQueueHead), chNum);
        }
    }
    else
    {
        /* nothing */
    }
}

void Eth_processTxTearDown(uint32 chNum)
{
    /* Channel teardown */
    Eth_PortObjectPtrType portObj = Eth_getCurrPortObj();

    /*
     * The software should acknowledge a teardown interrupt with a
     * FFFF_FFFCh Acknowledge value
     */
    CpswCpdma_writeTxChCp(Eth_DrvObj.baseAddr, chNum, (uint32)CPSW_CPDMA_TEAR_DWN_ACK);
    CpswCpdma_disableTxCh(Eth_DrvObj.baseAddr);

    Eth_freeTxBuffers(portObj->txBufObjArray, ETH_NUM_TX_BUFFERS);
    portObj->lastTxIdx = ETH_NUM_TX_BUFFERS - 1U;

    /*
     * Set Eth controller mode to disabled if both RX and TX
     * channels are torn. Else set this channel torn flag to TRUE so
     * when RX channel is torn it can use this for disabling
     * controller.
     */
    if ((TRUE) == Eth_CpdmaRxChTornFlag)
    {
        Eth_ControllerModeChangeFlag = TRUE;
        Eth_CpdmaRxChTornFlag        = FALSE;
        Eth_DrvObj.ctrlMode          = ETH_MODE_DOWN;
    }
    else
    {
        Eth_CpdmaTxChTornFlag = TRUE;
    }
}

/* This API is to get address of current ETH port object */
static inline Eth_PortObjectPtrType Eth_getCurrPortObj(void)
{
    return (&Eth_DrvObj.portObj);
}

FUNC(void, ETH_CODE_FAST)
Eth_getHwRxStats(P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats)
{
    Eth_StatsType ethStats = {0};

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
    CpswStats_getStats(Eth_DrvObj.baseAddr, &Eth_DrvObj.statsObj, &ethStats);
    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    /* List of RxStats*/
    RxStats->RxStatsDropEvents =
        ethStats.ALE_DROP + ethStats.ALE_OVERRUN_DROP + ethStats.PORTMASK_DROP + ethStats.RX_TOP_OF_FIFO_DROP +
        ethStats.RX_BOTTOM_OF_FIFO_DROP + ethStats.ALE_RATE_LIMIT_DROP + ethStats.ALE_VID_INGRESS_DROP +
        ethStats.ALE_DA_EQ_SA_DROP + ethStats.ALE_BLOCK_DROP + ethStats.ALE_SECURE_DROP + ethStats.ALE_AUTH_DROP;

    RxStats->RxStatsOctets            = ethStats.RXOCTETS;
    RxStats->RxStatsPkts              = ethStats.RXGOODFRAMES + ethStats.RXBROADCASTFRAMES + ethStats.RXMULTICASTFRAMES;
    RxStats->RxStatsBroadcastPkts     = ethStats.RXBROADCASTFRAMES;
    RxStats->RxStatsMulticastPkts     = ethStats.RXMULTICASTFRAMES;
    RxStats->RxStatsCrcAlignErrors    = ethStats.RXCRCERRORS + ethStats.RXALIGNCODEERRORS;
    RxStats->RxStatsUndersizePkts     = ethStats.RXUNDERSIZEDFRAMES;
    RxStats->RxStatsOversizePkts      = ethStats.RXOVERSIZEDFRAMES;
    RxStats->RxStatsFragments         = ethStats.RXFRAGMENTS;
    RxStats->RxStatsJabbers           = ethStats.RXJABBERFRAMES;
    RxStats->RxStatsCollisions        = 0xFFFFFFFFU;
    RxStats->RxStatsPkts64Octets      = 0xFFFFFFFFU;
    RxStats->RxStatsPkts65to127Octets = 0xFFFFFFFFU;
    RxStats->RxStatsPkts128to255Octets   = 0xFFFFFFFFU;
    RxStats->RxStatsPkts256to511Octets   = 0xFFFFFFFFU;
    RxStats->RxStatsPkts512to1023Octets  = 0xFFFFFFFFU;
    RxStats->RxStatsPkts1024to1518Octets = 0xFFFFFFFFU;
    RxStats->RxUnicastFrames = ethStats.RXGOODFRAMES - ethStats.RXBROADCASTFRAMES - ethStats.RXMULTICASTFRAMES;
}

void Eth_getHwCounterValues(P2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) CounterPtr)
{
    Eth_StatsType ethStats = {0};
    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
    CpswStats_getStats(Eth_DrvObj.baseAddr, &Eth_DrvObj.statsObj, &ethStats);
    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    /* List of drop counter values */
    CounterPtr->DropPktBufOverrun = ethStats.RX_BOTTOM_OF_FIFO_DROP;
    CounterPtr->DropPktCrc        = ethStats.RXCRCERRORS;
    CounterPtr->UndersizePkt      = ethStats.RXUNDERSIZEDFRAMES;
    CounterPtr->OversizePkt       = ethStats.RXOVERSIZEDFRAMES;
    CounterPtr->AlgnmtErr         = ethStats.RXALIGNCODEERRORS;
    CounterPtr->SqeTestErr        = 0xFFFFFFFFU;
    CounterPtr->DiscInbdPkt       = 0xFFFFFFFFU;
    CounterPtr->ErrInbdPkt =
        ethStats.RXALIGNCODEERRORS + ethStats.RXOVERSIZEDFRAMES + ethStats.RXUNDERSIZEDFRAMES + ethStats.RXCRCERRORS;
    CounterPtr->DiscOtbdPkt = 0xFFFFFFFFU;
    CounterPtr->ErrOtbdPkt  = ethStats.TXDEFERREDFRAMES + ethStats.TXCOLLISIONFRAMES + ethStats.TXCARRIERSENSEERRORS;
    CounterPtr->SnglCollPkt = ethStats.TXSINGLECOLLFRAMES;
    CounterPtr->MultCollPkt = ethStats.TXMULTCOLLFRAMES;
    CounterPtr->DfrdPkt     = ethStats.TXDEFERREDFRAMES;
    CounterPtr->LatCollPkt  = ethStats.TXLATECOLLISIONS;
    CounterPtr->HwDepCtr0   = ethStats.TXEXCESSIVECOLLISIONS;
    CounterPtr->HwDepCtr1   = ethStats.TXCARRIERSENSEERRORS;
    CounterPtr->HwDepCtr2   = 0xFFFFFFFFU;
    CounterPtr->HwDepCtr3   = 0xFFFFFFFFU;
}

void Eth_getHwTxStats(P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats)
{
    Eth_StatsType ethStats = {0};
    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
    CpswStats_getStats(Eth_DrvObj.baseAddr, &Eth_DrvObj.statsObj, &ethStats);
    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    /* List of TxStats*/
    TxStats->TxNumberOfOctets = ethStats.TXOCTETS;
    TxStats->TxNUcastPkts     = ethStats.TXBROADCASTFRAMES + ethStats.TXMULTICASTFRAMES;
    TxStats->TxUniCastPkts    = ethStats.TXGOODFRAMES - ethStats.TXBROADCASTFRAMES - ethStats.TXMULTICASTFRAMES;
}

void Eth_HwGetTxErrorCounterValues(P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues)
{
    Eth_StatsType ethStats = {0};
    uint32        i        = 0U;
    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();
    CpswStats_getStats(Eth_DrvObj.baseAddr, &Eth_DrvObj.statsObj, &ethStats);
    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    /* list of Transmission Error Counters */
    TxErrorCounterValues->TxDroppedNoErrorPkts = 0xFFFFFFFFU;

    /* Check drop count for all 8 priorities levels */
    for (i = 0U; i < (uint32)8U; i++)
    {
        TxErrorCounterValues->TxDroppedErrorPkts += ethStats.ENET_PN_TX_PRI_DROP_REG[i];
    }

    TxErrorCounterValues->TxDeferredTrans     = ethStats.TXDEFERREDFRAMES;
    TxErrorCounterValues->TxSingleCollision   = ethStats.TXSINGLECOLLFRAMES;
    TxErrorCounterValues->TxMultipleCollision = ethStats.TXMULTCOLLFRAMES;
    TxErrorCounterValues->TxLateCollision     = ethStats.TXLATECOLLISIONS;
    TxErrorCounterValues->TxExcessiveCollison = ethStats.TXEXCESSIVECOLLISIONS;
}

void Eth_getHwEgressTimeStamp(VAR(Eth_BufIdxType, AUTOMATIC) BufIdx,
                              P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                              P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)
{
    Std_ReturnType     retVal        = E_NOT_OK;
    uint64             nsec          = 0U;
    CpswCpts_StateObj *pCptsStateObj = &(Eth_DrvObj.cptsObj);
    CpswCpts_Event     eventTemplate;
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
    Eth_PortObject *pPortObj      = (Eth_PortObject *)NULL_PTR;
    pPortObj                      = &(Eth_DrvObj.portObj);
    Eth_TxBufObjType *pTempBufObj = &(pPortObj->txBufObjArray[BufIdx]);
#endif

    /* We set timeStampPtr to zero so if TS read fails it returns zero */
    (void)memset(timeStampPtr, 0, sizeof(Eth_TimeStampType));

    eventTemplate.eventType = CPTS_EVENT_ETHERNET_TRANSMIT;
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)

    /*
     * Taking message and sequence details from the earlier transmitted
     * buffer. This was set in Eth_Transmit call
     */
    eventTemplate.messageType = pTempBufObj->bufCptsEventInfo.messageType;
    eventTemplate.sequenceId  = pTempBufObj->bufCptsEventInfo.sequenceId;
#endif
    retVal = CpswCpts_readEthEventTimestamp(pCptsStateObj, &nsec, &eventTemplate);

    if ((Std_ReturnType)E_NOT_OK != retVal)
    {
        CpswCpts_getSysTime(&nsec, timeStampPtr);
        /* Quality information not supported, the value always Valid. */
        *timeQualPtr = ETH_VALID;
    }
    else
    {
        *timeQualPtr = ETH_INVALID;
    }
}

void Eth_getHwIngressTimeStamp(P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
                               P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                               P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)
{
    Std_ReturnType     retVal        = E_NOT_OK;
    uint64             nsec          = 0ULL;
    CpswCpts_StateObj *pCptsStateObj = &(Eth_DrvObj.cptsObj);
    CpswCpts_Event     eventTemplate = {0U};
    uint16             seqid         = 0U;
    const uint8       *dataPtr8      = (const uint8 *)DataPtr;

    /* We set timeStampPtr to zero so if TS read fails it returns zero */
    (void)memset(timeStampPtr, 0, sizeof(Eth_TimeStampType));

    seqid  = dataPtr8[TIME_SYNC_OFFSET_PTP_SEQUENCE_ID + 1U];
    seqid  = seqid << 8U;
    seqid += dataPtr8[TIME_SYNC_OFFSET_PTP_SEQUENCE_ID];

    eventTemplate.eventType = CPTS_EVENT_ETHERNET_RECEIVE;

    /* Message type is first byte of DataPtr */
    eventTemplate.messageType = dataPtr8[0] & (uint8)0xFU;
    eventTemplate.sequenceId  = ntohs(seqid);

    retVal = CpswCpts_readEthEventTimestamp(pCptsStateObj, &nsec, &eventTemplate);

    if ((Std_ReturnType)E_NOT_OK != retVal)
    {
        CpswCpts_getSysTime(&nsec, timeStampPtr);
        /* Quality information not supported, the value always Valid. */
        *timeQualPtr = ETH_VALID;
    }
    else
    {
        *timeQualPtr = ETH_INVALID;
    }
}

void Eth_checkHwCtrlErrors(void)
{
    Eth_StatsType ethStats = {0};

    (void)memset(&ethStats, 0, sizeof(ethStats));

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

    CpswStats_getStats(Eth_DrvObj.baseAddr, &Eth_DrvObj.statsObj, &ethStats);

    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    /*
     * Check for controller errors (e.g. CRC errors). If the check
     * fails the function shall raise the extended production error.
     */
    if ((uint32)0U != ethStats.RXCRCERRORS)
    {
#ifdef ETH_E_CRC
        (void)Dem_SetEventStatus(ETH_E_CRC, DEM_EVENT_STATUS_PREFAILED);
#endif
    }

    if ((uint32)0U != ethStats.RX_BOTTOM_OF_FIFO_DROP)
    {
#ifdef ETH_E_RX_FRAMES_LOST
        (void)Dem_SetEventStatus(ETH_E_RX_FRAMES_LOST, DEM_EVENT_STATUS_PREFAILED);
#endif
    }

    if ((uint32)0U != ethStats.RXUNDERSIZEDFRAMES)
    {
#ifdef ETH_E_UNDERSIZEFRAME
        (void)Dem_SetEventStatus(ETH_E_UNDERSIZEFRAME, DEM_EVENT_STATUS_PREFAILED);
#endif
    }

    if ((uint32)0U != ethStats.RXOVERSIZEDFRAMES)
    {
#ifdef ETH_E_OVERSIZEFRAME
        (void)Dem_SetEventStatus(ETH_E_OVERSIZEFRAME, DEM_EVENT_STATUS_PREFAILED);
#endif
    }

    Eth_HwcheckCtrlrErrors1(&ethStats);

    return;
}

static void Eth_HwcheckCtrlrErrors1(const Eth_StatsType *ethStats)
{
    if ((uint32)0U != ethStats->RXALIGNCODEERRORS)
    {
#ifdef ETH_E_ALIGNMENT
        (void)Dem_SetEventStatus(ETH_E_ALIGNMENT, DEM_EVENT_STATUS_PREFAILED);
#endif
    }

    if ((uint32)0U != ethStats->TXSINGLECOLLFRAMES)
    {
#ifdef ETH_E_SINGLECOLLISION
        (void)Dem_SetEventStatus(ETH_E_SINGLECOLLISION, DEM_EVENT_STATUS_PREFAILED);
#endif
    }

    if ((uint32)0U != ethStats->TXMULTCOLLFRAMES)
    {
#ifdef ETH_E_MULTIPLECOLLISION
        (void)Dem_SetEventStatus(ETH_E_MULTIPLECOLLISION, DEM_EVENT_STATUS_PREFAILED);
#endif
    }

    if ((uint32)0U != ethStats->TXLATECOLLISIONS)
    {
#ifdef ETH_E_LATECOLLISION
        (void)Dem_SetEventStatus(ETH_E_LATECOLLISION, DEM_EVENT_STATUS_PREFAILED);
#endif
    }
}

static boolean Eth_isBcastMacAddr(const uint8 *addr)
{
    uint32  i;
    boolean retVal = TRUE;

    for (i = 0U; i < ETH_MAC_ADDR_LEN; i++)
    {
        if (addr[i] != 0xFFU)
        {
            retVal = FALSE;
            break;
        }
    }

    return retVal;
}

static boolean Eth_isMcastMacAddr(const uint8 *addr)
{
    boolean retVal = FALSE;

    if (FALSE == Eth_isBcastMacAddr(addr))
    {
        /* MSbit (right most bit) of the MSB (first byte) is 1, then
         * the address is multicast, otherwise it's unicast */
        if (0U != (addr[0U] & 1U))
        {
            retVal = TRUE;
        }
    }

    return retVal;
}

static boolean Eth_isUcastMacAddr(const uint8 *addr)
{
    boolean retVal = FALSE;

    /* MSbit (right most bit) of the MSB (first byte) is 1, then
     * the address is multicast, otherwise it's unicast */
    if (0U == (addr[0U] & 1U))
    {
        retVal = TRUE;
    }

    return retVal;
}

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
