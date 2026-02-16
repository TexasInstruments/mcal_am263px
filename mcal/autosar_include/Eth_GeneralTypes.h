/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     Eth_GeneralTypes.h
 *
 *  \brief    This file contains general Eth type declarations.
 *
 */

/**
 *  \ingroup MCAL_ETH_API
 *  @{
 */

/*
 * Below are the global requirements which are met by this Eth
 * driver which can't be mapped to a particular source ID
 */
/* Requirements : SWS_Eth_00026, SWS_Eth_00149, SWS_EthTrcv_00096*/

#ifndef ETH_GENERALTYPES_H_
#define ETH_GENERALTYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "ComStack_Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief This type defines the Ethernet frame type used in the Ethernet
 *  frame header
 */
/* Requirements : SWS_Eth_00160 */
typedef uint16 Eth_FrameType;

/**
 *  \brief This type defines the Ethernet data type used for data
 *  transmission
 */
/* Requirements : SWS_Eth_00161 */
typedef uint32 Eth_DataType;

/** \brief Ethernet buffer identifier type */
/* Requirements : SWS_Eth_00175 */
typedef uint32 Eth_BufIdxType;



/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* [SWS_Eth_91002 */
typedef struct
{
	uint32 RxStatsDropEvents;
	uint32 RxStatsOctets;
	uint32 RxStatsPkts;
	uint32 RxStatsBroadcastPkts;
	uint32 RxStatsMulticastPkts;
	uint32 RxStatsCrcAlignErrors;
	uint32 RxStatsUndersizePkts;
	uint32 RxStatsOversizePkts;
	uint32 RxStatsFragments;
	uint32 RxStatsJabbers;
	uint32 RxStatsCollisions;
	uint32 RxStatsPkts64Octets;
	uint32 RxStatsPkts65to127Octets;
	uint32 RxStatsPkts128to255Octets;
	uint32 RxStatsPkts256to511Octets;
	uint32 RxStatsPkts512to1023Octets;
	uint32 RxStatsPkts1024to1518Octets;
	uint32 RxUnicastFrames;
}Eth_RxStatsType;

/* [SWS_Eth_91004] */
typedef struct
{
	uint32 TxDroppedNoErrorPkts;
	uint32 TxDroppedErrorPkts;
	uint32 TxDeferredTrans;
	uint32 TxSingleCollision;
	uint32 TxMultipleCollision;
	uint32 TxLateCollision;
	uint32 TxExcessiveCollison;
}Eth_TxErrorCounterValuesType;

/* [SWS_Eth_91003] */
typedef struct
{
	uint32 TxNumberOfOctets;
	uint32 TxNUcastPkts;
	uint32 TxUniCastPkts;
}Eth_TxStatsType;

/* [SWS_Eth_91007] */
typedef struct
{
	uint32 DropPktBufOverrun;
	uint32 DropPktCrc;
	uint32 UndersizePkt;
	uint32 OversizePkt;
	uint32 AlgnmtErr;
	uint32 SqeTestErr;
	uint32 DiscInbdPkt;
	uint32 ErrInbdPkt;
	uint32 DiscOtbdPkt;
	uint32 ErrOtbdPkt;
	uint32 SnglCollPkt;
	uint32 MultCollPkt;
	uint32 DfrdPkt;
	uint32 LatCollPkt;
	uint32 HwDepCtr0;
	uint32 HwDepCtr1;
	uint32 HwDepCtr2;
	uint32 HwDepCtr3;
}Eth_CounterType;


/** \brief ETH driver controller modes. */
/* Requirements : SWS_Eth_00158 */
typedef enum
{
    ETH_MODE_DOWN,
    /**< Controller disabled */
    ETH_MODE_ACTIVE
    /**< Controller enabled */
} Eth_ModeType;

/**
 *  \brief ETH driver status supervision used for development
 *  error detection.
 */
/* Requirements : SWS_Eth_00159 */
typedef enum
{
    ETH_STATE_UNINIT,
    /**< Driver is not yet configured */
    ETH_STATE_INIT,
    /**< Driver is configured */
} Eth_StateType;

/**
 *  \brief Used as out parameter in Eth_Receive() indicates whether
 *  a frame has been received and if so, whether more frames are available or
 *  frames got lost.
 */
/* Requirements : SWS_Eth_00162 */
typedef enum
{
    ETH_RECEIVED,
    /**< Ethernet frame has been received, no further frames available */
    ETH_NOT_RECEIVED,
    /**< Ethernet frame has not been received, no further frames available */
    ETH_RECEIVED_MORE_DATA_AVAILABLE
    /**< Ethernet frame has been received, more frames are available */
} Eth_RxStatusType;

/**
 *  \brief The Enumeration Type Eth_FilterActionType describes the action to
 *  be taklen for the MAC address given in *PhysAddrPtr.
 */
/* Requirements : SWS_Eth_00163 */
typedef enum
{
    ETH_ADD_TO_FILTER,
    /**< Add the MAC address to the filter, meaning allow reception */
    ETH_REMOVE_FROM_FILTER,
    /**< Remove the MAC address from the filter, meaning reception is blocked
     *   in the lower layer */
} Eth_FilterActionType;

/**
 *  \brief Quality information regarding the evaluated time stamp.
 *
 *   Note: Not supported on TDAxx MAC HW, the value is always Valid.
 */
/* Requirements : SWS_Eth_00177 */
typedef enum
{
    ETH_VALID,
    /**< Valid timestamp */
    ETH_INVALID,
    /**< Invalid timestamp */
    ETH_UNCERTAIN,
    /**< Uncertain timestamp */
} Eth_TimeStampQualType;

/**
 *  \brief Structure variable for expressing time stamps including relative
 *         & absolute calendar time.
 */
/* Requirements : SWS_Eth_00178 */
typedef struct
{
    uint32 nanoseconds;
    /**< Nanoseconds part of the time */
    uint32 seconds;
    /**< 32 bit LSB of the 48 bits Seconds part of the time */
    uint16 secondsHi;
    /**< 16 bit MSB of the 48 bits Seconds part of the time */
} Eth_TimeStampType;

/**
 *  \brief Structure variable to express time differences.
 */
/* Requirements : SWS_Eth_00179 */
typedef struct
{
    Eth_TimeStampType diff;
    /**< time difference */
    boolean sign;
    /**< Timestamp sign - Positive (True) / negative (False) time */
} Eth_TimeIntDiffType;

/**
 *  \brief Structure variable to express frequency ratios..
 */
/* Requirements : SWS_Eth_00180 */
typedef struct
{
    Eth_TimeIntDiffType IngressTimeStampDelta;
    /**< time difference (IngressTimeStampSync2 - IngressTimeStampSync1) */
    Eth_TimeIntDiffType OriginTimeStampDelta;
    /**< time difference (OriginTimeStampSync2[FUP2] - OriginTimeStampSync1[FUP1]) */
} Eth_RateRatioType;

/**
 *  \brief Transceiver board rate enum
 */
/* Requirements : SWS_EthTrcv_00102 */
typedef enum
{
    ETHTRCV_BAUD_RATE_10MBIT,
    ETHTRCV_BAUD_RATE_100MBIT,
    ETHTRCV_BAUD_RATE_1000MBIT,
} EthTrcv_BaudRateType;

/**
 *  \brief Transceiver Cable Diagnostic Results
 */
/* Requirements : SWS_EthTrcv_91008 */
typedef enum
{
    ETHTRCV_CABLEDIAG_OK,
    ETHTRCV_CABLEDIAG_ERROR,
    ETHTRCV_CABLEDIAG_SHORT,
    ETHTRCV_CABLEDIAG_OPEN
} EthTrcv_CableDiagResultType;

/**
 *  \brief Transceiver duplex mode
 */
/* Requirements : SWS_EthTrcv_00103 */
typedef enum
{
    ETHTRCV_DUPLEX_MODE_HALF,
    ETHTRCV_DUPLEX_MODE_FULL,
} EthTrcv_DuplexModeType;

/**
 *  \brief Transceiver link state enum
 */
/* Requirements : SWS_EthTrcv_00100 */
typedef enum
{
    ETHTRCV_LINK_STATE_DOWN,
    ETHTRCV_LINK_STATE_ACTIVE,
} EthTrcv_LinkStateType;

/**
 *  \brief Transceiver mode enum
 */
/* Requirements : SWS_EthTrcv_00099 */
typedef enum
{
    ETHTRCV_MODE_DOWN,
    ETHTRCV_MODE_ACTIVE,
} EthTrcv_ModeType;

/**
 *  \brief Transceiver PHY loopback modes
 */
/* Requirements : SWS_EthTrcv_91004 */
typedef enum
{
    ETHTRCV_PHYLOOPBACK_NONE,
    ETHTRCV_PHYLOOPBACK_INTERNAL,
    ETHTRCV_PHYLOOPBACK_EXTERNAL,
    ETHTRCV_PHYLOOPBACK_REMOTE
} EthTrcv_PhyLoopbackModeType;

typedef enum
{
    ETHTRCV_PHYTESTMODE_NONE,
    ETHTRCV_PHYTESTMODE_1,
    ETHTRCV_PHYTESTMODE_2,
    ETHTRCV_PHYTESTMODE_3,
    ETHTRCV_PHYTESTMODE_4,
    ETHTRCV_PHYTESTMODE_5,
} EthTrcv_PhyTestModeType;

/**
 *  \brief Transceiver PHY transmit modes
 */
/* Requirements : SWS_EthTrcv_91006 */
typedef enum
{
    ETHTRCV_PHYTXMODE_NORMAL,
    ETHTRCV_PHYTXMODE_TX_OFF,
    ETHTRCV_PHYTXMODE_SCRAMBLER_OFF
} EthTrcv_PhyTxModeType;

/**
 *  \brief Transceiver wake-up mode enum
 */
/* Requirements : SWS_EthTrcv_00113 */
typedef enum
{
    ETHTRCV_WUM_DISABLE,
    ETHTRCV_WUM_ENABLE,
    ETHTRCV_WUM_CLEAR
} EthTrcv_WakeupModeType;

/**
 *  \brief Forward declaration of EthTrcv_ConfigType
 */
/* Requirements : SWS_EthTrcv_00096 */
typedef struct EthTrcv_ConfigType_s EthTrcv_ConfigType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef ETH_GENERALTYPES_H_ */

/* @} */
