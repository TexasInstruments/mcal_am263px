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
 *  \file     EthApp.c
 *
 *  \brief    This file contains the EthApp test example header file
 *
 */

#ifndef ETHTESTAPP_H_
#define ETHTESTAPP_H_
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ETHAPP_MODULE_ID ((uint8)0x0U)

#define ETHAPP_STRESS_TEST (STD_OFF)

#define ETHAPP_MAINFUNCTION_TEST    (STD_ON)
#define ETHAPP_FILTER_TEST          (STD_ON)
#define ETHAPP_TIMESTAMP_TEST       (STD_ON)
#define ETHAPP_MIN_PACKETSIZE_TEST  (STD_ON)
#define ETHAPP_TRAFFIC_SHAPING_TEST (STD_ON)
#define ETHAPP_THROUGHPUT_TEST      (STD_OFF)
#define ETHAPP_STACKUSAGE_TEST      (STD_OFF)

#define ETHAPP_NUM_RECEIVE_PACKET   (50000U)
#define ETHAPP_NUM_TRANSMIT_PACKET  (50000U)
#define ETHAPP_NUM_TIME_SYNC_PACKET (100U)
#define ETHAPP_NUM_SET_GLB_TIME_CNT (100U)
#define ETH_APP_LOOP_COUNT          (0x1U)

#define ETHAPP_NUM_RECEIVE_PACKET_FILTER (1000U)

#define ENABLE_PACKET_CPU_COPY  (0U)
#define ENABLE_PACKET_EDMA_COPY (0U)
#define ENABLE_VLAN_TAG         (0U)

/* MAX ACOUNT */
#define MAX_ACOUNT (1500U)
/* MAX BCOUNT */
#define MAX_BCOUNT (1U)
/* MAX CCOUNT */
#define MAX_CCOUNT (1U)
/**
 * Buffers (src and dest) are needed for mem-2-mem data transfers.
 * This define is for the MAXIMUM size and hence the maximum data
 * which could be transferred using the sample test cases below.
 */
#define MAX_BUFFER_SIZE (MAX_ACOUNT * MAX_BCOUNT * MAX_CCOUNT)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8 timeSyncPacket[] = {
    /* Ethernet HEADER(commented as will be added by driver) */
    /*
     * 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // # Destination MAC
     * 0xFB, 0xB1, 0x56, 0xA9, 0xF4, 0xDF, // # Source MAC
     * 0x08, 0x00,                         // # Protocol
     */

    /* PTP packet */
    0x0, 0x2, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xf, 0xf, 0x0, 0x9, 0xa, 0x0, 0x1, 0x4, 0x1, 0x0, 0x0, 0x0, 0x0, 0x5, 0x1, 0x1, 0xd, 0xe, 0xc, 0x0, 0x0,
};

uint8 pDelayRequestPacket[] = {
    0x2, 0x0, 0xe, 0x0, 0x0, 0xb, 0x0, 0x0, 0x3, 0x0, 0x9, 0xa, 0x8, 0x0, 0x5, 0x0, 0x0, 0x2, 0x5, 0xf,
    0x0, 0x0, 0x1, 0x1, 0x0, 0x2, 0x0, 0x8, 0x2, 0x6, 0x0, 0x0, 0x0, 0xb, 0x1, 0xf, 0x1, 0xf, 0x0, 0xe,
    0x0, 0x0, 0x2, 0x2, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3, 0xf, 0xf, 0x0, 0x9, 0xa, 0x0, 0x1, 0xe, 0x8, 0x5, 0xf, 0x0, 0x0, 0x5, 0x1,
    0x1, 0x1, 0x4, 0x2, 0x9, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};

uint8 delayRequestPacket[] = {
    0x1, 0x0, 0xe, 0x0, 0x0, 0xb, 0x0, 0x0, 0x3, 0x0, 0x9, 0xa, 0x8, 0x0, 0x5, 0x0, 0x0, 0x2, 0x5, 0xf,
    0x0, 0x0, 0x1, 0x1, 0x0, 0x2, 0x0, 0x8, 0x2, 0x6, 0x0, 0x0, 0x0, 0xb, 0x1, 0xf, 0x1, 0xf, 0x0, 0xe,
    0x0, 0x0, 0x2, 0x2, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3, 0xf, 0xf, 0x0, 0x9, 0xa, 0x0, 0x1, 0xe, 0x8, 0x5, 0xf, 0x0, 0x0, 0x5, 0x1,
    0x1, 0x1, 0x4, 0x2, 0x9, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};

uint16 lengthOfTimeSyncPacket      = (sizeof(timeSyncPacket) / sizeof(timeSyncPacket[0U]));
uint16 lengthOfPdelayRequestPacket = (sizeof(pDelayRequestPacket) / sizeof(pDelayRequestPacket[0U]));
uint16 lengthOfDlayRequestPacket   = (sizeof(delayRequestPacket) / sizeof(delayRequestPacket[0U]));

extern void EthTrcvInitRGMII(uint8 CtrlIdx);

/* None */
#ifdef __cplusplus
}
#endif

#endif /* #ifndef ETHTESTAPP_H_ */

/* @} */
