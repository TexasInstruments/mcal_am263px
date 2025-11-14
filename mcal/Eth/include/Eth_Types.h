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
 *  \file     Eth_Types.h
 *
 *  \brief    This file contains Eth type declarations.
 */

/**
 *  \ingroup MCAL_ETH_API
 *  @{
 */

#ifndef ETH_TYPES_H_
#define ETH_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Eth_Cfg.h"
#include "Eth_GeneralTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief MAC address length in bytes. */
#define ETH_MAC_ADDR_LEN ((uint8)6U)
/** \brief Total octets in header.  */
#define ETH_HLEN ((uint16)14U)
/** \brief Min. octets in frame sans FCS */
#define ETH_ZLEN ((uint16)60U)
/** \brief Max. octets in payload   */
#define ETH_DATA_LEN ((uint16)1500U)

/*
 * Requirements : SWS_Eth_00218 The Ethernet Driver shall ensure that the base
 * addresses of all reception and transmission buffers fulfill the memory
 * alignment requirements for all AUTOSAR data types of the respective platform.
 */
#define ETH_MAX_FRAME_LEN (1536U)

/** \brief Typedef for cache flush function pointer */
typedef P2FUNC(void, ETH_APPL_CODE, Eth_CacheFlushType)(P2VAR(uint8, AUTOMATIC, ETH_APPL_DAT) BufPtr, uint32 LenByte);

/** \brief Typedef for cache invalidate function pointer */
typedef P2FUNC(void, ETH_APPL_CODE, Eth_CacheInvalidateType)(P2VAR(uint8, AUTOMATIC, ETH_APPL_DAT) BufPtr,
                                                             uint32 LenByte);

/** \brief Total priority queue number */
#define ETH_PRIORITY_QUEUE_NUM (8U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  CPTS Ethernet Message Type Enumeration
 */
typedef enum
{
    ETH_CPTS_MESSAGE_SYNC                  = (0x1U),
    ETH_CPTS_MESSAGE_DELAY_REQ             = (0x2U),
    ETH_CPTS_MESSAGE_PDELAY_REQ            = (0x4U),
    ETH_CPTS_MESSAGE_PDELAY_RESP           = (0x8U),
    ETH_CPTS_MESSAGE_FOLLOW_UP             = (0x100U),
    ETH_CPTS_MESSAGE_DELAY_RESP            = (0x200U),
    ETH_CPTS_MESSAGE_PDELAY_RESP_FOLLOW_UP = (0x400U),
    ETH_CPTS_MESSAGE_ANNOUNCE              = (0x800U),
    ETH_CPTS_MESSAGE_SIGNALING             = (0x1000U),
    ETH_CPTS_MESSAGE_MANAGEMENT            = (0x2000U),
    ETH_CPTS_MESSAGE_ALL                   = 0xFFFFU,
} Eth_CptsMessageCfg;

/**
 *  \brief Enum of VLAN usage type for CPTS packets
 */
typedef enum
{
    ETH_CPTS_VLAN_TYPE_NONE         = 0x00U,
    ETH_CPTS_VLAN_TYPE_SINGLE_TAG   = 0x01U,
    ETH_CPTS_VLAN_TYPE_STACKED_TAGS = 0x02U,
    ETH_CPTS_VLAN_TYPE_INVALID      = 0xFFFFFFFFU,
} Eth_CptsVlanType;

/**
 *  \brief CPTS Module Init Configuration Structure
 *         Configuration information for the CPTS modules provided during
 *         initialization.
 */
typedef struct
{
    uint32           cptsInputFreq;
    /**< CPTS input clock frequency in Hz Ex- 266000000UL for L3 266MHz freq. */
    Eth_CptsVlanType vlanType;
    /**<  VLAN Type */
    uint32           msgTypeCfg;
    /**<  Message types on which time stamping is enabled*/
} Eth_CptsConfigType;

/** \brief Enumerates speed configurations. */
typedef enum
{
    ETH_SPEED_10 = 0x00U,
    /**< 10 Mbps operation. */
    ETH_SPEED_100 = 0x01U,
    /**< 100 Mbps operation. */
    ETH_SPEED_1000 = 0x02U,
    /**< 1000 Mbps operation. */
} Eth_SpeedType;

/**
 *  \brief  Type/Speed/Duplex Connection Config Options
 *
 *  Connection Config Options
 *
 */
typedef enum
{
    ETH_MAC_CONN_TYPE_MII_10_HALF = 0x00U,
    /**< MAC connection type for half-duplex 10Mbps MII mode */
    ETH_MAC_CONN_TYPE_MII_10_FULL = 0x01U,
    /**< MAC connection type for full-duplex 10Mbps MII mode */
    ETH_MAC_CONN_TYPE_MII_100_HALF = 0x02U,
    /**< MAC connection type for half-duplex 100Mbps MII mode */
    ETH_MAC_CONN_TYPE_MII_100_FULL = 0x03U,
    /**< MAC connection type for full-duplex 100Mbps MII mode */
    ETH_MAC_CONN_TYPE_RMII_10_HALF = 0x04U,
    /**< MAC connection type for half-duplex 10Mbps RMII mode */
    ETH_MAC_CONN_TYPE_RMII_10_FULL = 0x05U,
    /**< MAC connection type for full-duplex 10Mbps RMII mode */
    ETH_MAC_CONN_TYPE_RMII_100_HALF = 0x06U,
    /**< MAC connection type for half-duplex 100Mbps RMII mode */
    ETH_MAC_CONN_TYPE_RMII_100_FULL = 0x07U,
    /**< MAC connection type for full-duplex 100Mbps RMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_10_HALF = 0x08U,
    /**< MAC connection type for forced half-duplex 10Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_10_FULL = 0x09U,
    /**< MAC connection type for forced full-duplex 10Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF = 0x0AU,
    /**< MAC connection type for forced half-duplex 100Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_100_FULL = 0x0BU,
    /**< MAC connection type for forced full-duplex 100Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_FORCE_1000 = 0x0CU,
    /**< MAC connection type for forced 1000Mbps RGMII mode */
    ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND = 0x0DU,
    /**< MAC connection type for RGMII inband detection mode (speed determined
     *   based on received RGMII Rx clock) */
} Eth_MacConnectionType;

/** \brief Enumerates duplicity configuration modes. */
typedef enum
{
    ETH_DUPLEX_MODE_HALF = 0x00U,
    /**< Half duplex mode. */
    ETH_DUPLEX_MODE_FULL = 0x01U,
    /**< Full duplex mode. */
} Eth_DuplexModeType;

/**
 *  \brief   CPDMA Init Configuration
 *
 *  \details Configuration information for the CPDMA provided during
 *  initialization.
 *  Note: Most of CPDMA features are not implemented. Only interrupt
 *  pacing is enabled.
 */
typedef struct
{
    uint32 pacingClkFreq;
    /**< CPDMA ICLK frequency for interrupt pacing  */
    uint32 rxInterruptPacingEnabled;
    /**< Receive interrupt pacing enable flag    */
    uint32 rxInterruptsPerMsec;
    /**< Receive interrupt pacing conf  */
    uint32 txInterruptPacingEnabled;
    /**< Transmit interrupt pacing enable flag    */
    uint32 txInterruptsPerMsec;
    /**< Transmit interrupt pacing conf  */
    /**< Register control fields for DMA Control register      */
    uint32 dmaModeFlags;
    /**< Configuation Mode Flags.  */
    uint32 rxThreshCount;

    /**< Free buffer descriptors count threshold to trigger an RX_THRESH
     *  interrupt.Set to zero for no threshold interrupt enablement
     */
} Eth_CpdmaConfigType;

/**
 *  \brief MDIO Module Init Configuration
 *         Configuration information for the MDIO modules provided during
 *         initialization.
 */
typedef struct
{
    uint32 mdioBusFreq;
    /**< Bus frequency for the MII module */
    uint32 mdioClockFreq;
    /**< Clock frequency for MDIO link */
} Eth_MdioConfigType;

/** \brief Structure holding the PHY configuration .*/
typedef struct
{
    uint32                macModeFlags;
    /**< Configuation Mode Flags */
    Eth_MacConnectionType macConnectionType;
    /**< MAC Connection Type. */
    uint8                 macAddr[ETH_MAC_ADDR_LEN];
    /**< MAC address  */
} Eth_MacConfigType;

#if (ETH_TRAFFIC_SHAPING_API == STD_ON)
/** \brief Structure holding the Egress FIFO shaper configuration .*/
typedef struct
{
    uint8  queueNum;
    /**< Priority queue number */
    uint32 idleSlope;
    /**< idleSlope for CBS for the port queue priority */
} Eth_EgressFifoShaperCfg;
#endif

/**
 *  \brief Structure for port configuration.
 */
typedef struct
{
    Eth_MacConfigType macCfg;
    /**< MAC Init Configurations */
#if (ETH_TRAFFIC_SHAPING_API == STD_ON)
    Eth_EgressFifoShaperCfg shaperCfg[ETH_PRIORITY_QUEUE_NUM];
    /**< Traffic shapping config for egress FIFO's */
#endif
} Eth_PortConfigType;

/**
 *  \brief Implementation specific structure of the Eth configuration.
 */
/* Requirements : SWS_Eth_00156 */
typedef struct Eth_ConfigType_s
{
    uint8              ctrlIdx;
    /**< CPSW controller index [Supported value 0 for port 1 ] */
    uint8              portIdx;
    /**< Port Idx >*/
    Eth_PortConfigType portCfg;
    /**< Port configuration */
#if (ETH_ENABLE_MII_API == STD_ON)
    Eth_MdioConfigType mdioCfg;
    /**< MDIO configuration */
#endif

    Eth_CpdmaConfigType cpdmaCfg;
    /**< CPDMA Init Configurations */
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
    Eth_CptsConfigType cptsCfg;
    /**< Time stamp (CPTS) Configurations */
#endif
    uint32                  enableCacheOps;
    /**< Since the Eth driver is updating (writing/reading) the packet header,
     *   if the packets are in cached region, then cache flush should be done
     *   for transmit and cache invalidate should be done for receive.
     *
     *   This flag determines whether the cache operations need to be enabled
     *   or not. If enabled, then the below two callback will be called to
     *   perform the cache operation
     */
    Eth_CacheFlushType      cacheFlushOps;
    /**< Cache flush function pointer */
    Eth_CacheInvalidateType cacheInvalidateOps;
    /**< Cache invalidate function pointer */
} Eth_ConfigType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* ETH_TYPES_H_ */

/* @} */
