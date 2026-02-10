
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
#include "EthTrcv_Cfg.h"

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

/**
 *  \brief Transceiver Interface enum
 */
/* Requirements : SWS_EthTrcv_00039 */
typedef enum
{
    LIGHT_MII,
    MII,
    RGMII
} EthTrcvMiiSelection;

/**
 *  \brief Transceiver Port MAC Layer Speed enum
 */
typedef enum
{
    ETH_MAC_LAYER_SPEED_100M,
    ETH_MAC_LAYER_SPEED_10G,
    ETH_MAC_LAYER_SPEED_10M,
    ETH_MAC_LAYER_SPEED_1G
} EthTrcvPortMacLayerSpeed;

/**
 *  \brief Transceiver Connection Negotiation of
 *  EthTrcv Link enum
 */
typedef enum
{
    TRCV_CONN_NEG_AUTO,
    TRCV_CONN_NEG_MASTER,
    TRCV_CONN_NEG_SLAVE
} EthTrcvConnNeg;

/**
 *  \brief Transceiver MAC layer subtype of a switch port
 */
typedef enum
{
    REDUCED,
    REVERSED,
    SERIAL,
    STANDARD,
    UNIVERSAL_SERIAL
} EthTrcvPortMacLayerSubType;

/**
 *  \brief Transceiver MAC layer type of a switch port
 */
typedef enum
{
    TRCV_MAC_LAYER_TYPE_XGMII,
    TRCV_MAC_LAYER_TYPE_XMII,
    TRCV_MAC_LAYER_TYPE_XXGMII
} EthTrcvPortMacLayerType;

typedef enum
{
    TRCV_PHYS_LAYER_TYPE_1000BASE_T,
    TRCV_PHYS_LAYER_TYPE_1000BASE_T1,
    TRCV_PHYS_LAYER_TYPE_100BASE_T1,
    TRCV_PHYS_LAYER_TYPE_100BASE_TX
} EthTrcvPhysLayerType;

/**
 *  \brief Implementation specific structure of the post build configuration.
 */
/* Requirements : SWS_EthTrcv_00098 */
typedef struct EthTrcv_ControllerConfigType_s
{
    uint8                      ctrlIdx;
    /**< Index of the Controller */
    uint8                      trcvIdx;
    /**< Index of the transceiver */
    uint8                      phyAddr;
    /**< PHY Address. */
    EthTrcvMiiSelection        MiiSel;
    /**<MII Selection */
    uint32                     enableAutoNeg;
    /**< Phy gigabit capability. */
    EthTrcvConnNeg             connNeg;
    /**<Connection Negotiation of EthTrcv Link */
    uint32                     advertiseCapab;
    /**< Phy advertisement capability. */
    uint32                     linkPartCapab;
    /**< Link partner capability. */
    uint32                     isGigCapab;
    /**< Phy gigabit capability. */
    EthTrcv_BaudRateType       baudRate;
    /**< Phy operating speed. */
    EthTrcv_DuplexModeType     duplexMode;
    /**< Phy operating duplexMode. */
    boolean                    loopbackEnable;
    /**< Phy loopback enable- for Test purpose. */
    EthTrcvPortMacLayerSpeed   PortMacLaySpeed;
    /**<Baud Rate of MAC layer*/
    EthTrcvPortMacLayerSubType PortMacLaySubType;
    /**<MAC layer subtype of a switch port */
    EthTrcvPortMacLayerType    PortMacLayType;
    /**<MAC layer type of the ethernet transceiver */
    EthTrcvPhysLayerType       PhysLayerType;
    /**<MAC layer type of the ethernet transceiver */
} EthTrcv_ControllerConfigType;

typedef struct EthTrcv_ConfigType_s
{
    EthTrcv_ControllerConfigType *pController[ETHTRCV_MAX_CONTROLLER];
} EthTrcv_ConfigType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ETHTRCV_TYPES_H_ */
