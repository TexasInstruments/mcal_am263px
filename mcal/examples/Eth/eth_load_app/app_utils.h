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
 *  \file     AppUtils.h
 *
 *  \brief    This file contains common utility functions used by the MCAL Eth
 *            apps.
 *
 */

#ifndef APP_UTILS_H_
#define APP_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <kernel/dpl/DebugP.h>

#include "sys_common.h"

#include "Eth.h"
#include "EthTrcv.h"
#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APPUTILS_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0U]))

#define ETHAPP_TIMEOUT_DURATION 0xFFFFFFFFU

#define ETHAPP_ETHERTYPE_IPV4    (0x0800)
#define ETHAPP_ETHERTYPE_VLAN    (0x8100)
#define ETHAPP_ETHERTYPE_PTP1588 (0x88F7)

#define ETH_APP_GENERATE_NEW_DATA 1U
#define VALIDATE_ALL_FRAME        1U

#define ETH_MASTER_SLAVE_APP_LOOP_COUNT   10
#define ETH_MASTER_SLAVE_APP_PACKET_COUNT 500

#define ETH_TRCV_IDX                   0x0
#define PHY_REGCR                      0x0D
#define PHY_ADDAR                      0x0E
#define PHY_RGMIIDCTL                  0x86
#define PHY_RGMIICTL                   0x32
#define PHY_STS                        0x11
#define PHY_TI_CR                      0x10
#define PHY_TI_CFG4                    0x31
#define IEEE_CONTROL_REG_OFFSET        0
#define IEEE_STATUS_REG_OFFSET         1
#define IEEE_AUTONEGO_ADVERTISE_REG    4
#define IEEE_1000_ADVERTISE_REG_OFFSET 9

#define IEEE_ASYMMETRIC_PAUSE_MASK 0x0800
#define IEEE_PAUSE_MASK            0x0400

#define PHY_REGCR_ADDR       0x001F
#define PHY_REGCR_DATA       0x401F
#define PHY_TI_CRVAL         0x5048
#define PHY_TI_CFG4RESVDBIT7 0x80
#define ADVERTISE_100        (ADVERTISE_100FULL | ADVERTISE_100HALF)
#define ADVERTISE_10         (ADVERTISE_10FULL | ADVERTISE_10HALF)

#define ADVERTISE_1000                   0x0300
#define IEEE_CTRL_AUTONEGOTIATE_ENABLE   0x1000
#define IEEE_STAT_AUTONEGOTIATE_COMPLETE 0x0020
#define IEEE_STAT_AUTONEGOTIATE_RESTART  0x0200
/* Advertisement control register. */
#define ADVERTISE_10HALF  0x0020 /* Try for 10mbps half-duplex  */
#define ADVERTISE_10FULL  0x0040 /* Try for 10mbps full-duplex  */
#define ADVERTISE_100HALF 0x0080 /* Try for 100mbps half-duplex */
#define ADVERTISE_100FULL 0x0100 /* Try for 100mbps full-duplex */

/* Definition wrapper for in Utils/{Dem.c,Det.c} */
#define AppUtils_printf DebugP_log

/* unified different interrupt number defined in sys_common.h of am273 to same as am263 */
#ifndef CPSW_FH_INT
#define CPSW_FH_INT MSS_CPSW_FH_INT
#endif
#ifndef CPSW_TH_INT
#define CPSW_TH_INT MSS_CPSW_TH_INT
#endif
#ifndef CPSW_TH_TRSH_INT
#ifdef CPSW_TH_THRESH_INT /* hw/am261/sys_common.h */
#define CPSW_TH_TRSH_INT CPSW_TH_THRESH_INT
#else
#define CPSW_TH_TRSH_INT MSS_CPSW_TH_TRSH_INT
#endif
#endif
#ifndef CPSW_MISC_INT
#define CPSW_MISC_INT MSS_CPSW_MISC_INT
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*!
 *  \brief  Structure to report successfully processed packet counts and parser error counts.
 */
typedef struct
{
    /*! Number of data packets successfully processed by RxIndication function */
    volatile uint32 recvPacketCnt;
    /*! Number of data packets transmitted */
    volatile uint32 txConfirmPacketCnt;
    /*! Number of parser errors encountered by the stack */
    uint32          errorCnt;
    /*! Number of packets with an unexpected ether type field */
    uint32          unexpectedEtherType;
    /*! Number of packets with zero size or bigger than the maximum allowed
        payload */
    uint32          invalidPacketSizeError;
    /*! Number of times the parser encountered an out-of-sequence packet
                          (either from packet loss or truly out of sequence) */
    uint32          outOfSequenceError;
    volatile uint32 expectedEtherType_ipv4;
    volatile uint32 expectedEtherType_vlan;
    volatile uint32 expectedEtherType_stackedvlan;
    volatile uint32 expectedEtherType_ptp;

    uint32          txBuffLenUnSufficient;
    uint32          txBuffUnderflow;
    uint32          provideTxBuffErr;
    uint32          ethTransmitErr;
    volatile uint32 ethTransmitPckCnt;
    uint32          dataMismatchCntr;
    uint32          multicastPackets;
    uint32          macFilterTestPackets;

} EthApp_Stats;

/*! \brief Structure for holding the state information of an instance */
typedef struct
{
    /*! boolean to indicate that packets/frames should be examined */
    boolean          checkPackets;
    Eth_DataType    *currFrameDataPtr;
    uint16           currFrameSize;
    uint8            currFramePhysAddr[ETH_MAC_ADDR_LEN];
    uint32           frameRcvdFlag;
    EthApp_Stats     stats;
    uint32           totalFramesSize;
    volatile uint8   runTest;
    volatile boolean txConfirmPacketFlag;
} App_State;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void           EcuM_cacheWbInv(uint8 *startAddress, uint32 byteCount);
void           EcuM_cacheInvalidate(uint8 *startAddress, uint32 byteCount);
void           AppUtils_ethPrintVersionInfo();
Std_ReturnType AppUtils_ethTrcvInit(EthTrcv_ConfigType *ethTrcvConfigPtr, uint8 trcvIdx);
void           AppUtils_ethAm263xPHYDelayConfig(Eth_ConfigType *pEthConfigPtr, uint32 phyAddr);

/* ========================================================================== */
/*                          Global variables                                  */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef APP_UTILS_H_ */
