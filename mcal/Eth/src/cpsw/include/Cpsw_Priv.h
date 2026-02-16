/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *  \file     Cpsw_Priv.h
 *
 *  \brief    This file contains the generic ethernet definitions
 *
 */
#ifndef CPSW_PRIV_H_
#define CPSW_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"

#include "Eth_Types.h"
#include "Cpsw_Cpts.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/*---------------------------------------------------------------------------*\
 |                           Macros/Defines for MAC switch                     |
 \*---------------------------------------------------------------------------*/
#define MAC_CONFIG_MODEFLG_CHPRIORITY 0x00001U
/**< Use Tx channel priority                                                */
#define MAC_CONFIG_MODEFLG_MACLOOPBACK 0x00002U
/**< MAC internal loopback                                                  */
#define MAC_CONFIG_MODEFLG_RXCRC 0x00004U
/**< Include CRC in RX frames                                               */
#define MAC_CONFIG_MODEFLG_TXCRC 0x00008U
/**< Tx frames include CRC                                                  */
#define MAC_CONFIG_MODEFLG_PASSERROR 0x00010U
/**< Pass error frames                                                      */
#define MAC_CONFIG_MODEFLG_PASSCONTROL 0x00020U
/**< Pass control frames                                                    */
#define MAC_CONFIG_MODEFLG_PASSALL 0x00040U
/**< pass all frames                                                        */
#define MAC_CONFIG_MODEFLG_RXQOS 0x00080U
/**< Enable QOS at receive side                                             */
#define MAC_CONFIG_MODEFLG_RXNOCHAIN 0x00100U
/**< Select no buffer chaining                                              */
#define MAC_CONFIG_MODEFLG_RXOFFLENBLOCK 0x00200U
/**< Enable offset/length blocking                                          */
#define MAC_CONFIG_MODEFLG_RXOWNERSHIP 0x00400U
/**< Use ownership bit as 1                                                 */
#define MAC_CONFIG_MODEFLG_RXFIFOFLOWCNTL 0x00800U
/**< Enable rx fifo flow control                                            */
#define MAC_CONFIG_MODEFLG_CMDIDLE 0x01000U
/**< Enable IDLE command                                                    */
#define MAC_CONFIG_MODEFLG_TXSHORTGAPEN 0x02000U
/**< Enable tx short gap                                                    */
#define MAC_CONFIG_MODEFLG_TXPACE 0x04000U
/**< Enable tx pacing                                                       */
#define MAC_CONFIG_MODEFLG_TXFLOWCNTL 0x08000U
/**< Enable tx flow control                                                 */
#define MAC_CONFIG_MODEFLG_RXBUFFERFLOWCNTL 0x10000U
/**< Enable rx buffer flow control                                          */

/*---------------------------------------------------------------------------*\
 |                           Macros/Defines for CPDMA                          |
 \*---------------------------------------------------------------------------*/
#define CPSW_CPDMA_WRD0_NDP_MASK               (0xFFFFFFFFU)
#define CPSW_CPDMA_WRD0_NDP_SHIFT              (0U)
#define CPSW_CPDMA_WRD1_BUFF_PTR_MASK          (0xFFFFFFFFU)
#define CPSW_CPDMA_WRD1_BUFF_PTR_SHIFT         (0U)
#define CPSW_CPDMA_WRD3_SOP_MASK               (0x80000000U)
#define CPSW_CPDMA_WRD3_SOP_SHIFT              (31U)
#define CPSW_CPDMA_WRD3_SOP_ENABLE             (1U)
#define CPSW_CPDMA_WRD3_SOP_DISABLE            (0U)
#define CPSW_CPDMA_WRD3_EOP_MASK               (0x40000000U)
#define CPSW_CPDMA_WRD3_EOP_SHIFT              (30U)
#define CPSW_CPDMA_WRD3_EOP_ENABLE             (1U)
#define CPSW_CPDMA_WRD3_EOP_DISABLE            (0U)
#define CPSW_CPDMA_WRD3_OWN_MASK               (0x20000000U)
#define CPSW_CPDMA_WRD3_OWN_SHIFT              (29U)
#define CPSW_CPDMA_WRD3_OWN_ENABLE             (1U)
#define CPSW_CPDMA_WRD3_OWN_DISABLE            (0U)
#define CPSW_CPDMA_WRD3_EOQ_MASK               (0x10000000U)
#define CPSW_CPDMA_WRD3_EOQ_SHIFT              (28U)
#define CPSW_CPDMA_WRD3_EOQ_ENABLE             (1U)
#define CPSW_CPDMA_WRD3_EOQ_DISABLE            (0U)
#define CPSW_CPDMA_WRD3_TEAR_DWN_COMP_MASK     (0x08000000U)
#define CPSW_CPDMA_WRD3_TEAR_DWN_COMP_SHIFT    (27U)
#define CPSW_CPDMA_WRD3_TEAR_DWN_COMP_COMPLETE (1U)
#define CPSW_CPDMA_WRD3_PASS_CRC_MASK          (0x04000000U)
#define CPSW_CPDMA_WRD3_PASS_CRC_SHIFT         (26U)
#define CPSW_CPDMA_WRD3_TO_PORT_EN_MASK        (0x00100000U)
#define CPSW_CPDMA_WRD3_TO_PORT_EN_SHIFT       (20U)
#define CPSW_CPDMA_WRD3_TO_PORT_MASK           (0x000F0000U)
#define CPSW_CPDMA_WRD3_TO_PORT_SHIFT          (16U)
#define CPSW_CPDMA_WRD3_HOST_EVENT_MASK        (0x00008000U)
#define CPSW_CPDMA_WRD3_HOST_EVENT_SHIFT       (15U)
#define CPSW_CPDMA_WRD3_HOST_EVENT_ENABLE      (1U)
#define CPSW_CPDMA_WRD3_CHKSUM_ENCAP_MASK      (0x00004000U)
#define CPSW_CPDMA_WRD3_CHKSUM_ENCAP_SHIFT     (14U)
#define CPSW_CPDMA_WRD3_CHKSUM_ENCAP_ENABLE    (1U)
#define CPSW_CPDMA_WRD3_PKT_LEN_MASK           (0x000007FFU)
#define CPSW_CPDMA_WRD3_PKT_LEN_SHIFT          (0U)

/** \brief Multicast MAC address upper byte mask. */
#define CPSW_CPDMA_RX_WRD2_BUFF_LEN_MASK       (0x000007FFU)
#define CPSW_CPDMA_RX_WRD2_BUFF_LEN_SHIFT      (0U)
#define CPSW_CPDMA_RX_WRD2_BUFF_OFF_MASK       (0x07FF0000U)
#define CPSW_CPDMA_RX_WRD2_BUFF_OFF_SHIFT      (16U)
#define CPSW_CPDMA_RX_WRD3_CHKSUM_ENCAP_MASK   (0x00001000U)
#define CPSW_CPDMA_RX_WRD3_CHKSUM_ENCAP_SHIFT  (12U)
#define CPSW_CPDMA_RX_WRD3_CHKSUM_ENCAP_ENABLE (1U)
#define CPSW_CPDMA_RX_WRD3_FROM_PORT_MASK      (0x00070000U)
#define CPSW_CPDMA_RX_WRD3_FROM_PORT_SHIFT     (16U)
#define CPSW_CPDMA_RX_WRD3_VLAN_ENCAP_MASK     (0x00080000U)
#define CPSW_CPDMA_RX_WRD3_VLAN_ENCAP_SHIFT    (19U)
#define CPSW_CPDMA_RX_WRD3_PKT_ERR_MASK        (0x00300000U)
#define CPSW_CPDMA_RX_WRD3_PKT_ERR_SHIFT       (20U)
#define CPSW_CPDMA_RX_WRD3_OVERRUN_MASK        (0x00400000U)
#define CPSW_CPDMA_RX_WRD3_OVERRUN_SHIFT       (22U)
#define CPSW_CPDMA_RX_WRD3_MAC_CTRL_MASK       (0x00800000U)
#define CPSW_CPDMA_RX_WRD3_MAC_CTRL_SHIFT      (23U)
#define CPSW_CPDMA_RX_WRD3_SHORT_MASK          (0x01000000U)
#define CPSW_CPDMA_RX_WRD3_SHORT_SHIFT         (24U)
#define CPSW_CPDMA_RX_WRD3_LONG_MASK           (0x02000000U)
#define CPSW_CPDMA_RX_WRD3_LONG_SHIFT          (25U)

/** \brief Multicast MAC address upper byte mask. */
#define CPSW_CPDMA_TX_WRD2_BUFF_LEN_MASK      (0x0000FFFFU)
#define CPSW_CPDMA_TX_WRD2_BUFF_LEN_SHIFT     (0U)
#define CPSW_CPDMA_TX_WRD2_BUFF_OFF_MASK      (0xFFFF0000U)
#define CPSW_CPDMA_TX_WRD2_BUFF_OFF_SHIFT     (16U)
#define CPSW_CPDMA_TX_WRD3_TO_PORT_MASK       (0x00030000U)
#define CPSW_CPDMA_TX_WRD3_TO_PORT_SHIFT      (16U)
#define CPSW_CPDMA_TX_WRD3_TO_PORT_EN_MASK    (0x00100000U)
#define CPSW_CPDMA_TX_WRD3_TO_PORT_EN_SHIFT   (20U)
#define CPSW_CPDMA_TX_WRD3_TO_PORT_EN_ENABLE  (1U)
#define CPSW_CPDMA_TX_WRD3_TO_PORT_EN_DISABLE (0U)

#define CPSW_CPDMA_TEAR_DWN_ACK (0xFFFFFFFCU)

/** \brief Interrupt configurations for DMA. */
#define CPSW_STAT_INT (0x00U)
/**< Statistics interrupt. */
#define CPSW_HOST_ERR_INT (0x01U)
/**< Host error interrupt interrupt. */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Enumerates interrupt configurations for channel. */
typedef enum
{
    CPSW_CH_INTR_NONE = 0x00U,
    /**< Receive threshold interrupt. */
    CPSW_CH_INTR_RX_THR = 0x01U,
    /**< Receive threshold interrupt. */
    CPSW_CH_INTR_RX = 0x02U,
    /**< Receive interrupt. */
    CPSW_CH_INTR_TX = 0x03U,
    /**< Transmit interrupt. */
} Eth_CpswChIntr;

/** \brief Enumerates interrupt types for pacing.
 *            RX_PULSE and TX_PULSE interrupts can be paced.
 *         The RX_THRESH_PULSE and MISC_PULSE interrupts are not paced
 */
typedef enum
{
    CPSW_INTR_TYPE_RX,
    /**< Receive interrupt. */
    CPSW_INTR_TYPE_TX,
    /**< Transmit interrupt. */
} Eth_CpswWrInt;

/** \brief Enumerates interrupt configurations for channel. */
typedef enum
{
    CPSW_WR_INTR_LINE_NONE = 0x0U,
    /**< None. */
    CPSW_WR_INTR_LINE_RX_THR = 0x1U,
    /**< Receive threshold interrupt. */
    CPSW_WR_INTR_LINE_RX = 0x2U,
    /**< Receive interrupt. */
    CPSW_WR_INTR_LINE_TX = 0x3U,
    /**< Transmit interrupt. */
    CPSW_WR_INTR_LINE_MISC = 0x4U,
    /**< Miscellaneous interrupt. */
} Eth_CpswWrIntrLine;

/** \brief Structure holding Eth frame header format */
typedef struct
{
    uint8  dstMacAddr[ETH_MAC_ADDR_LEN];
    /**< Destination MAC address */
    uint8  srcMacAddr[ETH_MAC_ADDR_LEN];
    /**< Source MAC address */
    uint16 h_proto;
    /**< The frame type */
} __attribute__((packed)) Eth_FrameHeaderType;

/** \brief Structure holding Eth TX frame format (header and data) and encap checksum offload */
typedef struct
{
    uint32              chksumInfo;
    /**< Encapsulated checksum */
    Eth_FrameHeaderType header;
    /**< Header */
    uint8               payload[ETH_MAX_FRAME_LEN - ETH_HLEN - 4U];
    /**< The generic data payload */
} __attribute__((packed)) Eth_TxFrameObjType;

/** \brief Structure holding Eth frame format (header and data)*/
typedef struct
{
    /**<Header */
    Eth_FrameHeaderType header;
    /**< The generic data payload */
    uint8               payload[ETH_MAX_FRAME_LEN - ETH_HLEN];
} __attribute__((packed)) Eth_RxFrameObjType;

/** \brief Enumeration for buffer states */
typedef enum
{
    ETH_BUF_STATE_FREE = 0U,
    /**< Buffer is free for allocation */
    ETH_BUF_STATE_IN_USE,
    /**< Buffer is in use */
} Eth_Buf_StateType;

/**
 *  \brief Implementation specific structures for port configuration.
 */
/* Requirements : SWS_Eth_00004 */
typedef struct
{
    uint16              bufIdx;
    /**< Buffer index */
    Eth_TxFrameObjType *payload;
    /**< pointer to the actual data in the buffer */
    uint16              len;
    /**< length of this buffer */
    Eth_FrameType       type;
    /**< Eth FrameType */
    Eth_Buf_StateType   bufState;
    /**< Buffer use status */
    boolean             txConfirmation;
    /**< Callback enable/disable */
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
    boolean        enableEgressTimeStamp;
    /**< Flag to enable/disable Timestamping on Tx packet */
    CpswCpts_Event bufCptsEventInfo;
    /**< CPTS ETH TX packet event info containing messageType & sequenceId
     *   Used when event lookup is done in subsequent Eth_GetEgressTimeStamp
     *   call after Eth_EnableEgressTimeStamp */
#endif
} Eth_TxBufObjType;

typedef struct
{
    uint16              bufIdx;
    /**< Buffer index */
    Eth_RxFrameObjType *payload;
    /**< pointer to the actual data in the buffer */
    uint16              len;
    /**< length of this buffer */
} Eth_RxBufObjType;

/** \brief Rx Buffer descriptor data structure. */
typedef struct Eth_CpdmaRxBuffDesc
{
    uint32                      globalNextDescPointer;
    /**< Next descriptor pointer. */
    uint32                      globalDataBufferPointer;
    /**< Global Buffer Pointer address of current buffer desc. */
    uint32                      bufferOffsetAndLength;
    /**< Buffer length and offset. */
    uint32                      flagsAndPacketLength;
    /**< Packet length and configuration flags. */
    struct Eth_CpdmaRxBuffDesc *pNextBuffDesc;
    /**< Next buffer descriptor. */
    Eth_RxFrameObjType         *pDataBuffer;
    /**< Associated packet buffer. */
    Eth_RxBufObjType           *pBufObj;
    /**< Associated buffer descriptor */
} Eth_CpdmaRxBuffDescType;

/** \brief Tx Buffer descriptor data structure. */
typedef struct Eth_CpdmaTxBuffDesc
{
    uint32                      globalNextDescPointer;
    /**< Next descriptor pointer. */
    uint32                      globalDataBufferPointer;
    /**< Global Buffer Pointer address of current buffer desc. */
    uint32                      bufferOffsetAndLength;
    /**< Buffer length and offset. */
    uint32                      flagsAndPacketLength;
    /**< Packet length and configuration flags. */
    struct Eth_CpdmaTxBuffDesc *pNextBuffDesc;
    /**< Next buffer descriptor. */
    Eth_TxFrameObjType         *pDataBuffer;
    /**< Associated packet buffer. */
    Eth_TxBufObjType           *pBufObj;
    /**< Associated buffer descriptor */
} Eth_CpdmaTxBuffDescType;

/** \brief Hold the data used to operate on the buffer descriptor ring. */
typedef struct
{
    Eth_CpdmaRxBuffDescType *pHead;
    /**< The head of the bd chain which is having transmitting data. */
    Eth_CpdmaRxBuffDescType *pTail;
    /**< The tail of the bd chain which is having transmitting data. */
    volatile uint32          freeBuffDesc;
    /**< The number of free bd's, which can be allocated for transmission. */
} Eth_CpdmaRxBuffDescQueue;

typedef struct
{
    Eth_CpdmaTxBuffDescType *pFreeHead;
    /**< The head of the bd chain which can be allocated for transmission. */
    Eth_CpdmaTxBuffDescType *pHead;
    /**< The head of the bd chain which is having transmitting data. */
    Eth_CpdmaTxBuffDescType *pTail;
    /**< The tail of the bd chain which is having transmitting data. */
    Eth_CpdmaTxBuffDescType *pQueueHead;
    /**< The head of the bd queue which is transmitting data. */
    Eth_CpdmaTxBuffDescType *pQueueTail;
    /**< The tail of the bd queue which is transmitting data. */
    volatile uint32          freeBuffDesc;
    /**< The number of free bd's, which can be allocated for transmission. */
} Eth_CpdmaTxBuffDescQueue;

/** \brief Eth port object
 *         This structure will contain information provided by
 *         application for port.
 */
typedef struct
{
    Eth_PortConfigType portCfg;
    /**< Port configuration */
    uint8              portNum;
    /**< CPSW port number in the device*/
    Eth_RxBufObjType   rxBufObjArray[ETH_NUM_RX_BUFFERS];
    /**< Buffer object for Receive buffer ring */
    Eth_TxBufObjType   txBufObjArray[ETH_NUM_TX_BUFFERS];
    /**< Buffer object for Transmit buffer ring */
    uint32             lastTxIdx;
    /**< Last used TX buffer index */
} Eth_PortObject;

/**
 *  \brief  CPSW Statistics Structure
 *
 *  The statistics structure is used to hold, in software, the
 *  hardware statistics reported by the STATS module of the CPSW Eth Port.
 */
typedef struct
{
    uint32 RXGOODFRAMES;           /* RxGoodFrames */
    uint32 RXBROADCASTFRAMES;      /* RxBroadcastFrames */
    uint32 RXMULTICASTFRAMES;      /* RxMulticastFrames */
    uint32 RXPAUSEFRAMES;          /* RxPauseFrames */
    uint32 RXCRCERRORS;            /* RxCRCErrors */
    uint32 RXALIGNCODEERRORS;      /* RxAlignCodeErrors */
    uint32 RXOVERSIZEDFRAMES;      /* RxOversizedFrames */
    uint32 RXJABBERFRAMES;         /* RxJabberFrames */
    uint32 RXUNDERSIZEDFRAMES;     /* RxUndersizedFrames */
    uint32 RXFRAGMENTS;            /* RxFragments */
    uint32 ALE_DROP;               /* ALE_Drop */
    uint32 ALE_OVERRUN_DROP;       /* ALE_Overrun_Drop */
    uint32 RXOCTETS;               /* RxOctets */
    uint32 TXGOODFRAMES;           /* TxGoodFrames */
    uint32 TXBROADCASTFRAMES;      /* TxBroadcastFrames */
    uint32 TXMULTICASTFRAMES;      /* TxMulticastFrames */
    uint32 TXPAUSEFRAMES;          /* TxPauseFrames */
    uint32 TXDEFERREDFRAMES;       /* TxDeferredFrames */
    uint32 TXCOLLISIONFRAMES;      /* TxCollisionFrames */
    uint32 TXSINGLECOLLFRAMES;     /* TxSingleCollFrames */
    uint32 TXMULTCOLLFRAMES;       /* TxMultCollFrames */
    uint32 TXEXCESSIVECOLLISIONS;  /* TxExcessiveCollisions */
    uint32 TXLATECOLLISIONS;       /* TxLateCollisions */
    uint32 RXIPGERROR;             /* RxIPGError */
    uint32 TXCARRIERSENSEERRORS;   /* TxCarrierSenseErrors */
    uint32 TXOCTETS;               /* TxOctets */
    uint32 OCTETFRAMES64;          /* OctetFrames64 */
    uint32 OCTETFRAMES65T127;      /* OctetFrames65t127 */
    uint32 OCTETFRAMES128T255;     /* OctetFrames128t255 */
    uint32 OCTETFRAMES256T511;     /* OctetFrames256t511 */
    uint32 OCTETFRAMES512T1023;    /* OctetFrames512t1023 */
    uint32 OCTETFRAMES1024TUP;     /* OctetFrames1024tUP */
    uint32 NETOCTETS;              /* NetOctets */
    uint32 RX_BOTTOM_OF_FIFO_DROP; /* Rx_Bottom_of_FIFO_Drop */
    uint32 PORTMASK_DROP;          /* Portmask_Drop */
    uint32 RX_TOP_OF_FIFO_DROP;    /* Rx_Top_of_FIFO_Drop */
    uint32 ALE_RATE_LIMIT_DROP;    /* ALE_Rate_Limit_Drop */
    uint32 ALE_VID_INGRESS_DROP;   /* ALE_VID_Ingress_Drop */
    uint32 ALE_DA_EQ_SA_DROP;      /* ALE_DA_EQ_SA_Drop */
    uint32 ALE_BLOCK_DROP;         /* ALE_Block_Drop */
    uint32 ALE_SECURE_DROP;        /* ALE_Secure_Drop */
    uint32 ALE_AUTH_DROP;          /* ALE_Auth_Drop */
    uint32 ALE_UNKN_UNI;           /* ALE_Unkn_Uni */
    uint32 ALE_UNKN_UNI_BCNT;      /* ALE_Unkn_Uni_Bcnt */
    uint32 ALE_UNKN_MLT;           /* ALE_Unkn_Mlt */
    uint32 ALE_UNKN_MLT_BCNT;      /* ALE_Unkn_Mlt_Bcnt */
    uint32 ALE_UNKN_BRD;           /* ALE_Unkn_Brd */
    uint32 ALE_UNKN_BRD_BCNT;      /* ALE_Unkn_Brd_Bcnt */
    uint32 ALE_POL_MATCH;          /* ALE_Pol_Match */
    uint32 ALE_POL_MATCH_RED;      /* ALE_Pol_Match_Red */
    uint32 ALE_POL_MATCH_YELLOW;   /* ALE_Pol_Match_Yellow */
    uint32 ALE_MULT_SA_DROP;       /* ALE_MULT_SA_DROP */
    uint32 ALE_DUAL_VLAN_DROP;     /* ALE_DUAL_VLAN_DROP */
    uint32 ALE_LEN_ERROR_DROP;     /* ALE_LEN_ERROR_DROP */
    uint32 ALE_IP_NEXT_HDR_DROP;   /* ALE_IP_NEXT_HDR_DROP */
    uint32 ALE_IPV4_FRAG_DROP;     /* ALE_IPV4_FRAG_DROP */
    uint32 Resv_1[24];
    uint32 IET_RX_ASSEMBLY_ERROR_REG; /* iet_rx_assembly_error */
    uint32 IET_RX_ASSEMBLY_OK_REG;    /* iet_rx_assembly_ok */
    uint32 IET_RX_SMD_ERROR_REG;      /* iet_rx_smd_error */
    uint32 IET_RX_FRAG_REG;           /* iet_rx_frag */
    uint32 IET_TX_HOLD_REG;           /* iet_tx_hold */
    uint32 IET_TX_FRAG_REG;           /* iet_tx_frag */
    uint32 Resv_2[9];
    uint32 TX_MEMORY_PROTECT_ERROR;         /* Tx_Memory_Protect_Error */
    uint32 ENET_PN_TX_PRI_REG[8];           /* enet_pn_tx_pri */
    uint32 ENET_PN_TX_PRI_BCNT_REG[8];      /* enet_pn_tx_pri_bcnt */
    uint32 ENET_PN_TX_PRI_DROP_REG[8];      /* enet_pn_tx_pri_drop */
    uint32 ENET_PN_TX_PRI_DROP_BCNT_REG[8]; /* enet_pn_tx_pri_drop_bcnt */
} Eth_StatsType;

/** \brief Eth stats object
 *         This structure will contain statistics information.
 */
typedef struct
{
    uint32        enableStatistics;
    /**< Flag to indicate if the statistics gathering is enabled or disabled. */
    Eth_StatsType stats;
    /**< Statistics Structure. */
} Eth_StatsObj;

/** \brief Eth controller driver object
 *         This structure will contain information provided by application
 *         and common information shared by ports */
typedef struct
{
    uint8                    ctrlIdx;
    /**< Controller index */
    uint8                    portIdx;
    /**< Port >*/
    Eth_ConfigType           ethConfig;
    /**< Eth driver Init Configuration */
    uint32                   enableCacheOps;
    /**< Since the Eth driver is updating (writing/reading) the packet header,
     *   if the packets are in cached region, then cache flush should be done
     *   for transmit and cache invalidate should be done for receive.
     *
     *   This flag determines whether the cache operations need to be enabled
     *   or not. If enabled, then the below two callback will be called to
     *   perform the cache operation
     */
    Eth_CacheFlushType       cacheFlushFnPtr;
    /**< Cache flush function pointer */
    Eth_CacheInvalidateType  cacheInvalidateFnPtr;
    /**< Cache invalidate function pointer */
    Eth_ModeType             ctrlMode;
    /**< CPSW instance in the device  */
    uint32                   baseAddr;
    /**< Base address */
    uint32                   rxDescMemBaseAddr;
    uint32                   txDescMemBaseAddr;
    /**< CPPI RAM Base address */
    uint8                    activeMACPortCount;
    /**< Total number active ports */
    Eth_PortObject           portObj;
    /**< Port interface */
    Eth_CpdmaRxBuffDescQueue rxDescRing;
    /**< Receive buffer descriptor queue*/
    uint32                   maxRxBuffDesc;
    /**< Maximum Rx buffer descriptors */
    Eth_CpdmaTxBuffDescQueue txDescRing;
    /**< Transmit buffer descriptor queue */
    uint32                   maxTxBuffDesc;
    /**< Maximum Tx buffer descriptors */
    Eth_StatsObj             statsObj;
    /**< Statistics object */
    CpswCpts_StateObj        cptsObj;
    /**< CPTS object */
} Eth_DrvObject;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Deprecated Function Declarations                    */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CPSW_PRIV_H_ */
