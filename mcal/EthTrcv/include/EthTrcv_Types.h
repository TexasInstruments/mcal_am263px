
/* ======================================================================
 *   Copyright (C) 2021 Texas Instruments Incorporated
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
 *  \file     EthTrcv_Types.h
 *
 *  \brief    This file contains interface header for ETHTRCV MCAL driver
 *
 */

#ifndef ETHTRCV_TYPES_H_
#define ETHTRCV_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Eth_GeneralTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Ethernet Transceiver wakeup support macro.
 *         SWS Item: ECUC_EthTrcv_00030.
 */
/* Requirements : SWS_EthTrcv_00110 */
/**
 *  \brief Interrupt based wake up for ETH TRCV
 */
#define ETHTRCV_WAKEUP_BY_INTERRUPT (0x0U)
/**
 *  \brief Polling based wake up for ETH TRCV
 */
#define ETHTRCV_WAKEUP_BY_POLLING (0x1U)
/**
 *  \brief Wake up for ETH TRCV not supported
 */
#define ETHTRCV_WAKEUP_NOT_SUPPORTED (0x2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief Transceiver state enum
 */
/* Requirements : SWS_EthTrcv_00101 */
typedef enum
{
    ETHTRCV_STATE_UNINIT,
    ETHTRCV_STATE_INIT
} EthTrcv_StateType;

/**
 *  \brief Transceiver wake-up reason type enum
 */
/* Requirements : SWS_EthTrcv_00114 */
typedef enum
{
    ETHTRCV_WUR_NONE,
    ETHTRCV_WUR_GENERAL,
    ETHTRCV_WUR_BUS,
    ETHTRCV_WUR_INTERNAL,
    ETHTRCV_WUR_RESET,
    ETHTRCV_WUR_POWER_ON,
    ETHTRCV_WUR_PIN,
    ETHTRCV_WUR_SYSERR
} EthTrcv_WakeupReasonType;

typedef enum
{
    ETHTRCV_WUR_MAGIC,
    ETHTRCV_WUR_PATTERN,
    ETHTRCV_WUR_BROADCAST,
    ETHTRCV_WUR_UNICAST
} EthTrcv_WakeupReasonType1;

/** \brief Enumerates Advertisement configurations. */
typedef enum
{
    ETHERNET_ADV_CAPAB_10_HALF = 0x1U, /* (0x1U << 0x0U) */
    /**< 10 Mbps half operation. */
    ETHERNET_ADV_CAPAB_10_FULL = 0x2U, /* (0x1U << 0x1U) */
    /**< 10 Mbps full operation. */
    ETHERNET_ADV_CAPAB_100_HALF = 0x4U, /* (0x1U << 0x2U) */
    /**< 100 Mbps half operation. */
    ETHERNET_ADV_CAPAB_100_FULL = 0x8U, /* (0x1U << 0x3U) */
    /**< 100 Mbps full operation. */
    ETHERNET_ADV_CAPAB_1000_HALF = 0x10U, /* (0x1U << 0x4U) */
    /**< 1000 Mbps half operation. */
    ETHERNET_ADV_CAPAB_1000_FULL = 0x20U, /* (0x1U << 0x5U) */
    /**< 1000 Mbps full operation. */
} EthTrcv_AdvCapabType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ETHTRCV_TYPES_H_ */
