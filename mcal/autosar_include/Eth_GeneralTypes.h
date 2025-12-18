/* ======================================================================
 *   Copyright (C) 2022 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

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

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef ETH_GENERALTYPES_H_ */

/* @} */
