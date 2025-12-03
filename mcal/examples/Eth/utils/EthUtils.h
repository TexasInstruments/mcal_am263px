/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     EthUtils.h
 *
 *  \brief    This file contains the function prototypes of miscellaneous
 *            Ethernet utilities.
 */

#ifndef ETHUTILS_H_
#define ETHUTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Std_Types.h>
#include "app_utils.h"

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/** \brief EthApp test round number */
#define ETH_APP_TEST_ROUND 1U

/** \brief Pass status */
#define PASS true

/** \brief Fail status */
#define FAIL false

/** \brief Print wrapper */
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM) || defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM) || \
    defined(AM261X_PLATFORM)
#include "app_utils.h"
#define EthUtils_printf(args...) AppUtils_printf(args)
#else
#define EthUtils_printf(args...) printf(args)
#endif

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

/** \brief IPV4  Protocol Identifier  */
#define ETHERTYPE_IPV4 (0x0800U)

/** \brief IPV4  Protocol Identifier  */
#define ETHERTYPE_IPV6 (0x86DDU)

/** \brief MAC address length in bytes */
#define ETH_HW_ADDR_LEN (6U)

/** \brief Total bytes in header */
#define ETH_HDR_LEN (14U)

/** \brief Max octets in payload */
#define ETH_PAYLOAD_LEN (1500U)

/** \brief Max octets in payload */
#define ETH_CHECKSUM_PAYLOAD_LEN (1500U)

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

typedef struct
{
    uint16_t proto;
    uint16_t checkSumPos;
    uint16_t validCheckSum;
    uint16_t length;
    uint8_t *payload;
} Eth_ChecksumTestType;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static inline bool EthFrame_isVlanTagged(EthFrame *frame)
{
    return frame->hdr.etherType == htons(ETHERTYPE_VLAN_TAG);
}

static inline bool EthFrame_isCtrl(EthFrame *frame)
{
    return frame->hdr.etherType == htons(ETHERTYPE_EXP_CONTROL);
}

static inline bool EthFrame_isStopCmd(EthFrame *frame)
{
    CtrlFrame *ctrlFrame = (CtrlFrame *)frame;
    return EthFrame_isCtrl(frame) && (ctrlFrame->payload.cmd == CTRL_FRAME_CMD_STOP);
}

int32_t EthUtils_checkPayload(DataFramePayload *payload);

int32_t EthUtils_checkVlanPayload(VlanDataFramePayload *payload);

int32_t EthUtils_checkVlanTagAndPayload(VlanDataFramePayload *payload, uint8_t pcp, uint16_t vid, uint16_t etherType);

int32_t EthUtils_fillPayload(DataFramePayload *payload, uint16_t type, uint16_t len);

int32_t EthUtils_fillVlanPayload(VlanDataFramePayload *payload, uint16_t type, uint16_t len, uint8_t pcp, uint16_t vid,
                                 uint16_t etherType);

int32_t EthUtils_fillVlanHdr(VlanDataFramePayload *payload, uint16_t type, uint16_t len, uint8_t pcp, uint16_t vid,
                             uint16_t etherType);

int32_t EthUtils_fillPtpSyncPayload(ptpSyncPayload *payload, uint8_t src_mac[], uint16_t seqId);

void EthUtils_printFrame(EthFrame *frame, int len);

static inline uint32_t EthUtils_rand(uint32_t min, uint32_t max)
{
    return (rand() % (max - min + 1)) + min;
}

/* ========================================================================== */
/*                        Deprecated Function Declarations                    */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* ETHUTILS_H_ */
