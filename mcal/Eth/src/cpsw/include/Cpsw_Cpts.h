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
 *   \file  Cpsw_Cpts.h
 *
 *   \brief
 *      Header file for CPTS module of CPSW subsystem.
 *
 */

#ifndef CPSW_CPTS_H_
#define CPSW_CPTS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/**
 * \brief 802.1AS Packets offsets.
 */
#define TIME_SYNC_OFFSET_PTP_SEQUENCE_ID (30U)

/**
 * \brief EtherType for the Precision Time Protocol (IEEE 1588).
 *
 * This is used by CPTS (time sync hardware) for timestamping received or
 * transmitted packets.
 */
#define CPSW_ETHTYPE_PTP1588 (0x88F7U)

/**
 * \brief Maximum number of attempts to retrieve timestamp from CPTS.
 */
#define CPSW_CPTS_RETRIEVE_TS_LOOP (512U)

/**
 * \brief Event queue size used to store TX and RX timestamps.
 *
 * Number of event buffer for each TX, RX event type. Oldest event will be
 * overwritten if upper layer doesn't retrieve buffered timestamp fast enough.
 */
#define ETH_CPTS_EVENT_CNT (16U)

/**
 * \brief CPTS event type.
 */
#define CPTS_EVENT_TIME_STAMP_PUSH          ((uint8)(0x00U))
#define CPTS_EVENT_TIME_STAMP_ROLLOVER      ((uint8)(0x01U))
#define CPTS_EVENT_TIME_STAMP_HALF_ROLLOVER ((uint8)(0x02U))
#define CPTS_EVENT_HARDWARE_TIME_STAMP_PUSH ((uint8)(0x03U))
#define CPTS_EVENT_ETHERNET_RECEIVE         ((uint8)(0x04U))
#define CPTS_EVENT_ETHERNET_TRANSMIT        ((uint8)(0x05U))
#define CPTS_EVENT_TIME_STAMP_COMPARE       ((uint8)(0x06U))
#define CPTS_EVENT_TIME_STAMP_HOST_TRANSMIT ((uint8)(0x07U))
#define CPTS_EVENT_INVALID                  ((uint8)(0xFFU))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief CPTS event structure.
 */
typedef struct
{
    uint64  timeStamp;
    /**< Timestamp value when the event occurred */
    uint8   eventType;
    /**< CPTS event type information */
    uint8   messageType;
    /**< CPTS event message type */
    uint16  sequenceId;
    /**< Sequence id of the event */
    uint16  portNumber;
    /**< MAC port number corresponding to the CPTS event */
    boolean valid;
    /**< This event is valid or invalid */
} CpswCpts_Event;

/**
 * \brief CPTS event queue structure.
 */
typedef struct
{
    uint32         idx;
    /**< Current index of free event */
    CpswCpts_Event event[ETH_CPTS_EVENT_CNT];
    /**< CPTS event queue */
} CpswCpts_EventQueue;

/**
 * \brief CPTS instance structure.
 */
typedef struct
{
    uint8               portNum;
    /**< MAC port CPTS is enabled on */
    uint32              cpswBaseAddr;
    /**< CPSW base address */
    uint32              cptsInputFreq;
    /**< CPTS timestamp counter frequency */
    CpswCpts_EventQueue rxQueue;
    /**< Queue of CPTS RX events */
    CpswCpts_EventQueue txQueue;
    /**< Queue of CPTS TX events */
    Eth_CptsConfigType  cptsCfg;
    /**< CPTS config provided by upper layer */
} CpswCpts_StateObj;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Open CPTS module.
 *
 * \param baseAddr        CPTS register base address
 * \param pCptsStateObj   CPTS instance structure
 * \param pCptsConfig     CPTS configuration
 * \param portIdx         MAC port number
 *
 * \retval E_OK           Success
 * \retval E_NOT_OK       Failure
 */
Std_ReturnType CpswCpts_init(uint32 baseAddr, CpswCpts_StateObj *pCptsStateObj, const Eth_CptsConfigType *pCptsConfig,
                             uint8 portIdx);

/**
 * \brief Close CPTS module.
 *
 * \param baseAddr        CPTS register base address
 *
 * \return None
 */
void CpswCpts_deinit(uint32 baseAddr);

/**
 * \brief CPTS event handler.
 *
 * Intended to be called in an ISR context. This is an internal driver
 * function and should not be called by an application or user.
 *
 * \param pCptsStateObj   CPTS instance structure
 *
 * \return None
 */
void CpswCpts_handleEvents(CpswCpts_StateObj *pCptsStateObj);

/**
 * \brief   Read CPTS timestamp and return time in nanoseconds.
 *
 * \param pCptsStateObj   CPTS instance structure
 * \param tsVal           Output timestamp value
 *
 * \retval E_OK           Success
 * \retval E_NOT_OK       Failure
 */
Std_ReturnType CpswCpts_readTimestamp(CpswCpts_StateObj *pCptsStateObj, uint64 *tsVal);

/**
 * \brief Get time in Eth_TimeStampType from nanoseconds.
 *
 * \param nsec            64-bit nanoseconds value
 * \param pTimestamp      Timestamp value
 *
 * \return None
 */
void CpswCpts_getSysTime(const uint64 *nsec, Eth_TimeStampType *pTimestamp);

/**
 * \brief Read CPTS Ethernet RX or TX event.
 *
 * \param pCptsStateObj   CPTS instance structure
 * \param tsVal           Output timestamp value
 * \param pEeventTemplate CPTS event queue
 *
 * \retval E_OK           Success
 * \retval E_NOT_OK       Failure
 */
Std_ReturnType CpswCpts_readEthEventTimestamp(CpswCpts_StateObj *pCptsStateObj, uint64 *tsVal,
                                              const CpswCpts_Event *pEeventTemplate);

/**
 * \brief Read CPTS event pend raw status.
 *
 * \param baseAddr        CPTS register base address
 *
 * \return Non-zero if there is CPTS PEND event. Zero otherwise.
 */
uint32 CpswCpts_getEventPendStatus(uint32 baseAddr);

#ifdef __cplusplus
}
#endif

#endif /* CPSW_CPTS_H_ */
