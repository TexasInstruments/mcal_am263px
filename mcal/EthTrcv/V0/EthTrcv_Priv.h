/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     EthTrcv_Priv.h
 *
 *  \brief    This file contains ETH TRANCEIVER MCAL driver API prototype
 *            declarations and type definitions.
 *
 */

#ifndef ETHTRCV_PRIV_H_
#define ETHTRCV_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "EthTrcv_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ETHTRCV_BMC                           (0x00U)
#define ETHTRCV_BMS                           (0x01U)
#define ETHTRCV_ID1                           (0x02U)
#define ETHTRCV_ID2                           (0x03U)
#define ETHTRCV_AUTO_NEG_ADV                  (0x04U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY (0x05U)
#define ETHTRCV_AUTO_NEG_EXPANSION            (0x06U)
#define ETHTRCV_AUTO_NEG_NEXT_PAGE_TX         (0x07U)
#define ETHTRCV_LINK_PARTNER_NEXT_PAGE        (0x08U)
#define ETHTRCV_GENCFG1                       (0x09U)
#define ETHTRCV_STS1                          (0x0AU)
#define ETHTRCV_EXTENDED_REGCR                (0x0DU)
#define ETHTRCV_EXTENDED_ADDACR               (0x0EU)
#define ETHTRCV_EXTENDED_STS                  (0x0FU)
#define ETHTRCV_PHYCR                         (0x10U)
#define ETHTRCV_PHYSTS                        (0x11U)
#define ETHTRCV_MICR                          (0x12U)
#define ETHTRCV_LOOPBACK_CTRL2                (0x13U)
#define ETHTRCV_RX_ERR_CNT                    (0x14U)
#define ETHTRCV_MI_CTRL                       (0x15U)
#define ETHTRCV_CFG                           (0x16U)
#define ETHTRCV_CTRL                          (0x17U)
#define ETHTRCV_INTR_MASK                     (0x18U)
#define ETHTRCV_INTR_STS                      (0x19U)
#define ETHTRCV_STS                           (0x1AU)
#define ETHTRCV_RXFCFG                        (0x0134U)
#define ETHTRCV_RXFSTS                        (0x0135U)

#define ETHTRCV_LED_CTRL(n)      (0x1BU + ((n) * 0x1U))
#define ETHTRCV_DIAGNOSTICS_CTRL (0x1EU)
#define ETHTRCV_DIAGNOSTICS_STS  (0x1FU)

#define ETHTRCV_OP_MODE_DECODE (0x1DFU)

/****************************************************************************************************
 * Field Definition Macros
 ****************************************************************************************************/

#define ETHTRCV_BMC_SPEED_MASK  (0x2040U)
#define ETHTRCV_BMC_SPEED_SHIFT (6U)
#define ETHTRCV_BMC_SPEED_10    (0x00U)
#define ETHTRCV_BMC_SPEED_100   (0x80U)
#define ETHTRCV_BMC_SPEED_1000  (0x01U)

#define ETHTRCV_PHYSTS_SPEED_MASK  (0xC000U)
#define ETHTRCV_PHYSTS_SPEED_SHIFT 14U
#define ETHTRCV_PHYSTS_SPEED_10    (0x00U)
#define ETHTRCV_PHYSTS_SPEED_100   (0x01U)
#define ETHTRCV_PHYSTS_SPEED_1000  (0x02U)

#define ETHTRCV_BMC_COLLISON_TEST_MASK    (0x0080U)
#define ETHTRCV_BMC_COLLISON_TEST_SHIFT   (7U)
#define ETHTRCV_BMC_COLLISON_TEST_ENABLE  (1U)
#define ETHTRCV_BMC_COLLISON_TEST_DISABLE (0U)

#define ETHTRCV_BMC_DUPLEX_MODE_MASK  (0x100U)
#define ETHTRCV_BMC_DUPLEX_MODE_SHIFT (8U)
#define ETHTRCV_BMC_DUPLEX_MODE_FULL  (1U)
#define ETHTRCV_BMC_DUPLEX_MODE_HALF  (0U)

#define ETHTRCV_PHYSTS_DUPLEX_MODE_MASK  (0x2000U)
#define ETHTRCV_PHYSTS_DUPLEX_MODE_SHIFT (13U)
#define ETHTRCV_PHYSTS_DUPLEX_MODE_FULL  (1U)
#define ETHTRCV_PHYSTS_DUPLEX_MODE_HALF  (0U)

#define ETHTRCV_BMC_RESTART_AUTONEG_MASK    (0x0200U)
#define ETHTRCV_BMC_RESTART_AUTONEG_SHIFT   (9U)
#define ETHTRCV_BMC_RESTART_AUTONEG_ENABLE  (1U)
#define ETHTRCV_BMC_RESTART_AUTONEG_DISABLE (0U)

#define ETHTRCV_BMC_ISOLATE_MASK    (0x0400U)
#define ETHTRCV_BMC_ISOLATE_SHIFT   (10U)
#define ETHTRCV_BMC_ISOLATE_ENABLE  (1U)
#define ETHTRCV_BMC_ISOLATE_DISABLE (0U)

#define ETHTRCV_BMC_PWR_DWN_MASK    (0x0800U)
#define ETHTRCV_BMC_PWR_DWN_SHIFT   (11U)
#define ETHTRCV_BMC_PWR_DWN_ENABLE  (1U)
#define ETHTRCV_BMC_PWR_DWN_DISABLE (0U)

#define ETHTRCV_BMC_AUTONEG_ENABLE_MASK  (0x1000U)
#define ETHTRCV_BMC_AUTONEG_ENABLE_SHIFT (12U)
#define ETHTRCV_BMC_AUTONEG_ENABLE       (1U)
#define ETHTRCV_BMC_AUTONEG_DISABLE      (0U)

#define ETHTRCV_BMC_LOOPBACK_MASK    (0x4000U)
#define ETHTRCV_BMC_LOOPBACK_SHIFT   (14U)
#define ETHTRCV_BMC_LOOPBACK_ENABLE  (1U)
#define ETHTRCV_BMC_LOOPBACK_DISABLE (0U)

#define ETHTRCV_BMC_RESET_MASK    (0x8000U)
#define ETHTRCV_BMC_RESET_SHIFT   (15U)
#define ETHTRCV_BMC_RESET_ENABLE  (1U)
#define ETHTRCV_BMC_RESET_DISABLE (0U)

#define ETHTRCV_BMS_EXTENDED_CAPABILITY_MASK    (0x0001U)
#define ETHTRCV_BMS_EXTENDED_CAPABILITY_SHIFT   (0U)
#define ETHTRCV_BMS_EXTENDED_CAPABILITY_ENABLE  (1U)
#define ETHTRCV_BMS_EXTENDED_CAPABILITY_DISABLE (0U)

#define ETHTRCV_BMS_JABBER_MASK         (0x0002U)
#define ETHTRCV_BMS_JABBER_SHIFT        (1U)
#define ETHTRCV_BMS_JABBER_DETECTED     (1U)
#define ETHTRCV_BMS_JABBER_NOT_DETECTED (0U)

#define ETHTRCV_BMS_LINKS_STS_MASK  (0x0004U)
#define ETHTRCV_BMS_LINKS_STS_SHIFT (2U)
#define ETHTRCV_BMS_LINKS_STS_UP    (1U)
#define ETHTRCV_BMS_LINKS_STS_DWN   (0U)

#define ETHTRCV_BMS_AUTONEG_ABILITY_MASK        (0x0008U)
#define ETHTRCV_BMS_AUTONEG_ABILITY_SHIFT       (3U)
#define ETHTRCV_BMS_AUTONEG_ABILITY_CAPABLE     (1U)
#define ETHTRCV_BMS_AUTONEG_ABILITY_NOT_CAPABLE (0U)

#define ETHTRCV_BMS_REMOTE_FAULT_MASK         (0x0010U)
#define ETHTRCV_BMS_REMOTE_FAULT_SHIFT        (4U)
#define ETHTRCV_BMS_REMOTE_FAULT_DETECTED     (1U)
#define ETHTRCV_BMS_REMOTE_FAULT_NOT_DETECTED (0U)

#define ETHTRCV_BMS_AUTONEG_PROCESS_MASK         (0x0020U)
#define ETHTRCV_BMS_AUTONEG_PROCESS_SHIFT        (5U)
#define ETHTRCV_BMS_AUTONEG_PROCESS_COMPLETE     (1U)
#define ETHTRCV_BMS_AUTONEG_PROCESS_NOT_COMPLETE (0U)

#define ETHTRCV_BMS_MF_PREAMBLE_SUPRESS_MASK         (0x0040U)
#define ETHTRCV_BMS_MF_PREAMBLE_SUPRESS_SHIFT        (6U)
#define ETHTRCV_BMS_MF_PREAMBLE_SUPRESS_ACCEPTED     (1U)
#define ETHTRCV_BMS_MF_PREAMBLE_SUPRESS_NOT_ACCEPTED (0U)

#define ETHTRCV_BMS_EXTENDED_STS_MASK    (0x0100U)
#define ETHTRCV_BMS_EXTENDED_STS_SHIFT   (8U)
#define ETHTRCV_BMS_EXTENDED_STS_ENABLE  (1U)
#define ETHTRCV_BMS_EXTENDED_STS_DISABLE (0U)

#define ETHTRCV_BMS_100_T2_HALF_MASK        (0x0200U)
#define ETHTRCV_BMS_100_T2_HALF_SHIFT       (9U)
#define ETHTRCV_BMS_100_T2_HALF_CAPABLE     (1U)
#define ETHTRCV_BMS_100_T2_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_BMS_100_T2_FULL_MASK        (0x0400U)
#define ETHTRCV_BMS_100_T2_FULL_SHIFT       (10U)
#define ETHTRCV_BMS_100_T2_FULL_CAPABLE     (1U)
#define ETHTRCV_BMS_100_T2_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_BMS_10_T_HALF_MASK        (0x0800U)
#define ETHTRCV_BMS_10_T_HALF_SHIFT       (11U)
#define ETHTRCV_BMS_10_T_HALF_CAPABLE     (1U)
#define ETHTRCV_BMS_10_T_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_BMS_10_T_FULL_MASK        (0x1000U)
#define ETHTRCV_BMS_10_T_FULL_SHIFT       (12U)
#define ETHTRCV_BMS_10_T_FULL_CAPABLE     (1U)
#define ETHTRCV_BMS_10_T_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_BMS_100_X_HALF_MASK        (0x2000U)
#define ETHTRCV_BMS_100_X_HALF_SHIFT       (13U)
#define ETHTRCV_BMS_100_X_HALF_CAPABLE     (1U)
#define ETHTRCV_BMS_100_X_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_BMS_100_X_FULL_MASK        (0x4000U)
#define ETHTRCV_BMS_100_X_FULL_SHIFT       (14U)
#define ETHTRCV_BMS_100_X_FULL_CAPABLE     (1U)
#define ETHTRCV_BMS_100_X_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_BMS_100_T4_MASK        (0x8000U)
#define ETHTRCV_BMS_100_T4_SHIFT       (15U)
#define ETHTRCV_BMS_100_T4_CAPABLE     (1U)
#define ETHTRCV_BMS_100_T4_NOT_CAPABLE (0U)

#define ETHTRCV_ID1_OUI_3_18_MASK  (0xFFFFU)
#define ETHTRCV_ID1_OUI_3_18_SHIFT (0U)

#define ETHTRCV_ID2_OUI_19_24_MASK  (0xFC00U)
#define ETHTRCV_ID2_OUI_19_24_SHIFT (10U)
#define ETHTRCV_ID2_MODEL_NUM_MASK  (0x03F0U)
#define ETHTRCV_ID2_MODEL_NUM_SHIFT (4U)
#define ETHTRCV_ID2_REV_NUM_MASK    (0x000FU)
#define ETHTRCV_ID2_REV_NUM_SHIFT   (0U)

#define ETHTRCV_AUTO_NEG_ADV_SEL_MASK  (0x001FU)
#define ETHTRCV_AUTO_NEG_ADV_SEL_SHIFT (0U)

#define ETHTRCV_AUTO_NEG_ADV_10_T_HALF_MASK        (0x0020U)
#define ETHTRCV_AUTO_NEG_ADV_10_T_HALF_SHIFT       (5U)
#define ETHTRCV_AUTO_NEG_ADV_10_T_HALF_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_ADV_10_T_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_ADV_10_T_FULL_MASK        (0x0040U)
#define ETHTRCV_AUTO_NEG_ADV_10_T_FULL_SHIFT       (6U)
#define ETHTRCV_AUTO_NEG_ADV_10_T_FULL_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_ADV_10_T_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_ADV_100_TX_HALF_MASK        (0x0080U)
#define ETHTRCV_AUTO_NEG_ADV_100_TX_HALF_SHIFT       (7U)
#define ETHTRCV_AUTO_NEG_ADV_100_TX_HALF_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_ADV_100_TX_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_ADV_100_TX_FULL_MASK        (0x0100U)
#define ETHTRCV_AUTO_NEG_ADV_100_TX_FULL_SHIFT       (8U)
#define ETHTRCV_AUTO_NEG_ADV_100_TX_FULL_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_ADV_100_TX_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_ADV_100_T4_MASK        (0x0200U)
#define ETHTRCV_AUTO_NEG_ADV_100_T4_SHIFT       (9U)
#define ETHTRCV_AUTO_NEG_ADV_100_T4_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_ADV_100_T4_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_ADV_PAUSE_MASK        (0x0400U)
#define ETHTRCV_AUTO_NEG_ADV_PAUSE_SHIFT       (10U)
#define ETHTRCV_AUTO_NEG_ADV_PAUSE_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_ADV_PAUSE_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_ADV_ASYNC_PAUSE_MASK        (0x0800U)
#define ETHTRCV_AUTO_NEG_ADV_ASYNC_PAUSE_SHIFT       (11U)
#define ETHTRCV_AUTO_NEG_ADV_ASYNC_PAUSE_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_ADV_ASYNC_PAUSE_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_ADV_REMOTE_FAULT_MASK       (0x2000U)
#define ETHTRCV_AUTO_NEG_ADV_REMOTE_FAULT_SHIFT      (13U)
#define ETHTRCV_AUTO_NEG_ADV_REMOTE_FAULT_DETECT     (1U)
#define ETHTRCV_AUTO_NEG_ADV_REMOTE_FAULT_NOT_DETECT (0U)

#define ETHTRCV_AUTO_NEG_ADV_NEXT_PAGE_MASK        (0x8000U)
#define ETHTRCV_AUTO_NEG_ADV_NEXT_PAGE_SHIFT       (15U)
#define ETHTRCV_AUTO_NEG_ADV_NEXT_PAGE_SUPPORT     (1U)
#define ETHTRCV_AUTO_NEG_ADV_NEXT_PAGE_NOT_SUPPORT (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_SEL_MASK  (0x001FU)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_SEL_SHIFT (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_HALF_MASK        (0x0020U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_HALF_SHIFT       (5U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_HALF_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_FULL_MASK        (0x0040U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_FULL_SHIFT       (6U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_FULL_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_HALF_MASK        (0x0080U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_HALF_SHIFT       (7U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_HALF_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_FULL_MASK        (0x0100U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_FULL_SHIFT       (8U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_FULL_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_T4_MASK        (0x0200U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_T4_SHIFT       (9U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_T4_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_T4_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_PAUSE_MASK        (0x0400U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_PAUSE_SHIFT       (10U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_PAUSE_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_PAUSE_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ASYNC_PAUSE_MASK        (0x0800U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ASYNC_PAUSE_SHIFT       (11U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ASYNC_PAUSE_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ASYNC_PAUSE_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_REMOTE_FAULT_MASK       (0x2000U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_REMOTE_FAULT_SHIFT      (13U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_REMOTE_FAULT_DETECT     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_REMOTE_FAULT_NOT_DETECT (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ACK_MASK         (0x4000U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ACK_SHIFT        (14U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ACK_RECEIVED     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_ACK_NOT_RECEIVED (0U)

#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_NEXT_PAGE_MASK        (0x8000U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_NEXT_PAGE_SHIFT       (15U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_NEXT_PAGE_SUPPORT     (1U)
#define ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_NEXT_PAGE_NOT_SUPPORT (0U)

#define ETHTRCV_AUTO_NEG_EXPANSION_AUTO_NEG_MASK        (0x0001U)
#define ETHTRCV_AUTO_NEG_EXPANSION_AUTO_NEG_SHIFT       (0U)
#define ETHTRCV_AUTO_NEG_EXPANSION_AUTO_NEG_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_EXPANSION_AUTO_NEG_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_EXPANSION_PAGE_MASK         (0x0002U)
#define ETHTRCV_AUTO_NEG_EXPANSION_PAGE_SHIFT        (1U)
#define ETHTRCV_AUTO_NEG_EXPANSION_PAGE_REVEIVED     (1U)
#define ETHTRCV_AUTO_NEG_EXPANSION_PAGE_NOT_REVEIVED (0U)

#define ETHTRCV_AUTO_NEG_EXPANSION_NEXT_PAGE_MASK        (0x0004U)
#define ETHTRCV_AUTO_NEG_EXPANSION_NEXT_PAGE_SHIFT       (2U)
#define ETHTRCV_AUTO_NEG_EXPANSION_NEXT_PAGE_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_EXPANSION_NEXT_PAGE_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_NEXT_PAGE_MASK        (0x0008U)
#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_NEXT_PAGE_SHIFT       (3U)
#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_NEXT_PAGE_CAPABLE     (1U)
#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_NEXT_PAGE_NOT_CAPABLE (0U)

#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_FAULT_MASK         (0x0010U)
#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_FAULT_SHIFT        (4U)
#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_FAULT_DETECTED     (1U)
#define ETHTRCV_AUTO_NEG_EXPANSION_LINK_FAULT_NOT_DETECTED (0U)

#define ETHTRCV_GENCFG1_ADV_1000_HALF_MASK        (0x0100U)
#define ETHTRCV_GENCFG1_ADV_1000_HALF_SHIFT       (8U)
#define ETHTRCV_GENCFG1_ADV_1000_HALF_CAPABLE     (1U)
#define ETHTRCV_GENCFG1_ADV_1000_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_GENCFG1_ADV_1000_FULL_MASK        (0x0200U)
#define ETHTRCV_GENCFG1_ADV_1000_FULL_SHIFT       (9U)
#define ETHTRCV_GENCFG1_ADV_1000_FULL_CAPABLE     (1U)
#define ETHTRCV_GENCFG1_ADV_1000_FULL_NOT_CAPABLE (0U)

#define ETHTRCV_GENCFG1_PORT_TYPE_MASK   (0x0400U)
#define ETHTRCV_GENCFG1_PORT_TYPE_SHIFT  (10U)
#define ETHTRCV_GENCFG1_PORT_TYPE_MULTI  (1U)
#define ETHTRCV_GENCFG1_PORT_TYPE_SINGLE (0U)

/*TDR Auto Run for Cable Diagnostics*/
#define ETHTRCV_GENCFG1_TDR_AUTO_RUN_MASK    (0x0040U)
#define ETHTRCV_GENCFG1_TDR_AUTO_RUN_SHIFT   (7U)
#define ETHTRCV_GENCFG1_TDR_AUTO_RUN_ENABLE  (1U)
#define ETHTRCV_GENCFG1_TDR_AUTO_RUN_DISABLE (0U)

#define ETHTRCV_GENCFG1_PHY_CONFIG_MASK   (0x0800U)
#define ETHTRCV_GENCFG1_PHY_CONFIG_SHIFT  (11U)
#define ETHTRCV_GENCFG1_PHY_CONFIG_MASTER (1U)
#define ETHTRCV_GENCFG1_PHY_CONFIG_SLAVE  (0U)

#define ETHTRCV_GENCFG1_PHY_CONFIG_EN_MASK   (0x1000U)
#define ETHTRCV_GENCFG1_PHY_CONFIG_EN_SHIFT  (12U)
#define ETHTRCV_GENCFG1_PHY_CONFIG_EN_MANUAL (1U)
#define ETHTRCV_GENCFG1_PHY_CONFIG_EN_AUTO   (0U)

#define ETHTRCV_STS1_LINK_1000_HALF_MASK        (0x0400U)
#define ETHTRCV_STS1_LINK_1000_HALF_SHIFT       (10U)
#define ETHTRCV_STS1_LINK_1000_HALF_CAPABLE     (1U)
#define ETHTRCV_STS1_LINK_1000_HALF_NOT_CAPABLE (0U)

#define ETHTRCV_STS1_LINK_1000_FULL_MASK        (0x0800U)
#define ETHTRCV_STS1_LINK_1000_FULL_SHIFT       (11U)
#define ETHTRCV_STS1_LINK_1000_FULL_CAPABLE     (1U)
#define ETHTRCV_STS1_LINK_1000_FULL_NOT_CAPABLE (0U)

/*PHY Identifier*/
#define ETHTRCV_PHY_ID1_OUI_MSB       (0xffffU)
#define ETHTRCV_PHY_ID2_OUI_LSB       (0xfc00U)
#define ETHTRCV_PHY_ID2_VNDR_MDL_MASK (0x01F0U)
#define ETHTRCV_PHY_ID2_MDL_REV_MASK  (0x000FU)

/*Cable Diagnostics*/
#define ETHTRCV_CAB_DIAG_CTRL_TDR_START_MASK   (0U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_START_SHIFT  (0U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_START_ENABLE (1U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_START_NORMAL (0U)

#define ETHTRCV_CAB_DIAG_CTRL_TDR_DONE_MASK          (0x0002U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_DONE_SHIFT         (1U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_DONE_COMPLETED     (1U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_DONE_NOT_COMPLETED (0U)

#define ETHTRCV_CAB_DIAG_CTRL_TDR_FAIL_MASK       (0x0004U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_FAIL_SHIFT      (2U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_FAILED          (1U)
#define ETHTRCV_CAB_DIAG_CTRL_TDR_NORMALOPERATION (0U)

/*TX PHY Mode Register Configuration*/
#define ETHTRCV_TX_CONFIG (0X43U)

#define ETHTRCV_TX_CONFIG_SCR_DIS_MASK  (0x4U)
#define ETHTRCV_TX_CONFIG_SCR_DIS_SHIFT (2U)
#define ETHTRCV_TX_CONFIG_SCR_DISABLE   (1U)
#define ETHTRCV_TX_CONFIG_SCR_NORMAL    (0U)

#define ETHTRCV_TX_CONFIG_SCR_DESCRAM_TIMEOUT_MASK  (0x780U)
#define ETHTRCV_TX_CONFIG_SCR_DESCRAM_TIMEOUT_SHIFT (7U)
#define ETHTRCV_TX_CONFIG_SCR_DESCRAM_TIMEOUT_VAlUE (15U)

#define ETHTRCV_TX_CONFIG_SCR_DESCRAM_TIMEOUT_DIS_MASK      (0x80U)
#define ETHTRCV_TX_CONFIG_SCR_DESCRAM_TIMEOUT_DIS_SHIFT     (11U)
#define ETHTRCV_TX_CONFIG_SCR_DESCRAM_TIMEOUT_DIS_PCKDIABLE (1U)
#define ETHTRCV_TX_CONFIG_SCR_DESCRAM_TIMEOUT_DIS_PCKSTOP   (0U)

/*phy loopback configuration*/

#define ETHTRCV_CFG_LOOPBACK_MODE_MASK             (0x3F)
#define ETHTRCV_CFG_LOOPBACK_MODE_SHIFT            (0U)
#define ETHTRCV_CFG_LOOPBACK_MODE_EXTERNAL         (0x10U)
#define ETHTRCV_CFG_LOOPBACK_MODE_INTERNAL_ANALOG  (0x8U)
#define ETHTRCV_CFG_LOOPBACK_MODE_INTERNAL_DIGITAL (0x4U)

/*PHY Normal operation*/
#define ETHTRCV_CFG_NORMAL_MODE_MASK      (0x4000)
#define ETHTRCV_CFG_NORMAL_MODE_SHIFT     (14U)
#define ETHTRCV_CFG_NORMAL_MODE_OPERATION (0U)

#define ETHTRCV_ID1_OUI_MSB_MASK  (0xffffU)
#define ETHTRCV_ID1_OUI_MSB_SHIFT (0U)

#define ETHTRCV_ID2_OUI_LSB_MASK  (0xFC00U)
#define ETHTRCV_ID2_OUI_LSB_SHIFT (10u)

#define ETHTRCV_ID2_MDL_MASK  (0x03f0U)
#define ETHTRCV_ID2_MDL_SHIFT (4U)

#define ETHTRCV_ID2_MDL_REV_MASK  (0xfU)
#define ETHTRCV_ID2_MDL_REV_SHIFT (0U)

#define ETHTRCV_TDR_FAIL (0x4U)
#define ETHTRCV_TDR_DONE (0x2U)
#define ETHTRCV_TDR_FAIL (0x4U)

#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
#define ETHTRCV_DISABLE_1000M_HALF_Duplex (0xFEFFU)
#endif /* #if(STD_ON == ETHTRCV_1000MBPS_MACRO) */
#define ETHTRCV_DISABLE_1000M (0xFCFFU)

#define ETHTRCV_TEST_MODE_MASK                (0xE000U)
#define ETHTRCV_TEST_MODE_SHIFT               (13U)
#define ETHTRCV_TEST_MODE_NORMAL              (0x0U)
#define ETHTRCV_TEST_MODE_JITTER_MASTER       (0x2U)
#define ETHTRCV_TEST_MODE_JITTER_SLAVE        (0x3U)
#define ETHTRCV_TEST_MODE_TRANSMIT_DISTORTION (0x4U)

#define ETHTRCV_OP_MODE_DECODE_MII_MASK     (0x20U)
#define ETHTRCV_OP_MODE_DECODE_MII_SHIFT    (5U)
#define ETHTRCV_OP_MODE_DECODE_MII_ENABLE   (1U)
#define ETHTRCV_OP_MODE_DECODE_RGMII_ENABLE (0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct
{
    EthTrcv_ControllerConfigType ethTrcvCfg;
    /**< Transceiver Config */
    EthTrcv_ModeType             ctrlMode;
    /**< Transceiver Mode */
    uint8                        trcvIdx;
    /**< PHY Address. */
} EthTrcv_CtrlObjType;

typedef struct
{
    EthTrcv_CtrlObjType ethTrcvCtrlObj[ETHTRCV_MAX_CONTROLLER];
    /**< Controller index */
    uint8               ctrlIdx;
} EthTrcv_DrvObject;

typedef enum
{
    ETHTRCV_PHYLOOPBACK_INTERNAL_ANALOG,
    ETHTRCV_PHYLOOPBACK_INTERNAL_DIGITAL
} EthTrcv_InternalLoopBackType;

/* ===========================================================================*/
/*                         Global Variables Declarations                      */
/* ===========================================================================*/
extern VAR(EthTrcv_DrvObject, ETHTRCV_VAR_ZERO_INIT) EthTrcv_DrvObj;
extern VAR(volatile uint32, ETHTRCV_VAR_ZERO_INIT) EthTrcv_MdioRdCmdComplete;
extern VAR(volatile uint32, ETHTRCV_VAR_ZERO_INIT) EthTrcv_MdioWrCmdComplete;
extern VAR(volatile uint16, ETHTRCV_VAR_ZERO_INIT) EthTrcv_MdioRdVal;

/**************************************************************************
 *                      API function Prototypes
 **************************************************************************/
/**
 * \brief Initializes driver object of Ethernet transceiver.
 *
 * \param  instNum   Pointer to  ETHTRCV driver object to be initialised.
 */
void EthTrcv_resetDrvObj(EthTrcv_DrvObject *pEthTrcvDrvObj);

/**
 * \brief AutoNegotiates with phy for link.
 *
 * \param  pPhyConfig The interface structure for PHY configuration.
 *
 * \retval S_PASS     Link set up is successful.
 * \retval E_FAIL     Link set up is not successful.
 */
Std_ReturnType EthTrcv_configAndStartAutoNegotiation(EthTrcv_CtrlObjType *pEthTrcvObj);

/**
 * \brief  Manually configure phy.
 *
 * \param  pPhyConfig The interface structure for PHY configuration.
 *
 * \retval S_PASS     Link set up is successful.
 * \retval E_FAIL     Link set up is not successful.
 */
Std_ReturnType EthTrcv_forceConfig(const EthTrcv_CtrlObjType *pEthTrcvObj);

/**
 * \brief   Enables Loop Back mode
 *
 * \param   CtrlIdx          PHY device ID.
 * \param   trcvIdx          PHY device instance.
 * \param   enableLoopBack   Configure PHY loop back.
 *                           	TRUE  - Enable PHY loop back.
 *                           	FALSE - Disable PHY loop back.
 *
 * \retval S_PASS            Loop back configuration successful.
 * \retval E_FAIL            Loop back configuration failed.
 */
Std_ReturnType EthTrcv_enableLoopBack(uint8 CtrlIdx, uint8 trcvIdx, uint32 enableLoopBack);

/**
 * \brief   Resets the PHY
 *
 * \param   CtrlIdx     PHY device ID.
 * \param   trcvIdx     PHY device instance.
 *
 * \retval S_PASS       Reset successful.
 * \retval E_FAIL       Reset failed.
 */
Std_ReturnType EthTrcv_resetController(uint8 CtrlIdx, uint8 trcvIdx);

/**
 * \brief   Reads the link status of the PHY.
 *
 * \param   CtrlIdx  PHY device ID.
 * \param   trcvIdx  PHY device instance.
 * \param   retries  The number of retries before indicating link status.
 *
 * \retval  TRUE     Link is up.
 * \retval  FALSE    Link is down.
 *
 * \note    This reads both the basic status register of the PHY and the
 *          link register of MDIO for double check
 */
uint32 EthTrcv_getLinkStatus(uint8 CtrlIdx, uint8 trcvIdx);

/**
 * \brief   Reads a register from the the PHY
 *
 * \param	None
 *
 * \retval	None
 */
void EthTrcv_regRead_Status(void);

/**
 * \brief   Reads a register from the the PHY
 *
 * \param   CtrlIdx     PHY device ID.
 * \param   trcvIdx     PHY device instance.
 * \param   regAddr     Address of the register to be read.
 * \param   regVal      Value of the register will be read.
 *
 * \retval E_OK         PHY register read successful.
 * \retval E_NOT_OK     PHY register read failed.\
 */
Std_ReturnType EthTrcv_regRead(uint8 CtrlIdx, uint8 trcvIdx, uint8 regIdx, uint16 *RegValPtr);

/**
 * \brief    Writes a register with the input
 *
 * \param	None
 *
 * \retval	None
 */
void EthTrcv_regWrite_Status(void);

/**
 * \brief   Writes a register with the input
 *
 * \param   CtrlIdx    PHY device ID.
 * \param   trcvIdx    PHY device instance.
 * \param   regAddr    Address of the register to be written.
 * \param   regVal     Value to be written.
 *
 * \retval E_OK        PHY register write successful.
 * \retval E_NOT_OK    PHY register write failed.
 */

Std_ReturnType EthTrcv_regWrite(uint8 CtrlIdx, uint8 trcvIdx, uint8 regIdx, uint16 regVal);

#if (STD_ON == ETHTRCV_GETPHYIDENTIFIER_API)
/**
 * \brief   Reads the physical Identification of Ethernet Transceiver
 *
 * \param   trcvIdx     		PHY device instance.
 * \param   OrgUniqueIdPtr      Organizationally Unique Identifier
 * \param   ModelNrPtr      	Model Number
 * \param   RevisionNrPtr		Model Revision Number
 *
 * \retval E_OK       PHY Identifier  read successful.
 * \retval E_NOT_OK   PHY Identifier read failed.\
 */
Std_ReturnType EthTrcv_GetPhyIdentifierRead(uint8 trcvIdx, uint32 *OrgUniqId, uint8 *MdlNmbr, uint8 *RevNmbr);
#endif /* #if (STD_ON == ETHTRCV_GETPHYIDENTIFIER_API) */

/**
 * \brief   Configures the PHY to given LoopBack Mode
 *
 * \param   trcvIdx      PHY device instance.
 * \param   ModeType     PHY device loop Back mode
 *
 * \retval E_OK           Set Loopback mode is successful.
 * \retval E_NOT_OK       Set Loopback mode is failed.\
 */

Std_ReturnType EthTrcv_ConfigSetPhyLoopbackMode(uint8 trcvIdx, EthTrcv_PhyLoopbackModeType ModeType);

#if (STD_ON == ETHTRCV_SETPHYTXMODE_API)
/**
 * \brief   Configures the PHY to given Transmission Mode
 *
 * \param   trcvIdx     PHY device instance.
 * \param   ModeVal     PHY device Transmit mode
 *
 * \retval E_OK           Set Transmission mode is successful.
 * \retval E_NOT_OK       Set Transmission mode is failed.\
 */
Std_ReturnType EthTrcvSettingStatusPhyTxMode(uint8 trcvIdx, EthTrcv_PhyTxModeType ModeVal);
#endif /* #if (STD_ON == ETHTRCV_SETPHYTXMODE_API) */

#if (STD_ON == ETHTRCV_GETCABLEDIAGNOSTICSRESULT_API)
/**
 * \brief   Reading cable Diagnostic results of Ethernet Transceiver cable
 *
 * \param   trcvIdx       PHY device instance.
 * \param   ResultVal     Cable Diagnostic results pointer
 *
 * \retval E_OK           PHY register read successful.
 * \retval E_NOT_OK       PHY register read failed.\
 */
Std_ReturnType EthTrcv_ReadCableDiagResult(uint8 TrcvIdx, EthTrcv_CableDiagResultType *ResultVal);
#endif /* #if (STD_ON == ETHTRCV_GETCABLEDIAGNOSTICSRESULT_API) */

#if (STD_ON == ETHTRCV_SETPHYTESTMODE_API)
/**
 * \brief   Activates the given test mode
 *
 * \param   trcvIdx     PHY device instance.
 * \param   ModeVal     PHY device test mode
 *
 * \retval E_OK           The request has been accepted.
 * \retval E_NOT_OK       The request has not been accepted.\
 */
Std_ReturnType EthTrcv_HwSetPhyTestMode(uint8 trcvIdx, EthTrcv_PhyTestModeType Mode);
#endif /* #if (STD_ON == ETHTRCV_SETPHYTESTMODE_API) */

Std_ReturnType EthTrcv_Initilization(uint8 TrcvIdx);

Std_ReturnType EthTrcv_ConfigInit(EthTrcv_ControllerConfigType *pEthTrcvCfg, EthTrcv_CtrlObjType *pEthTrcvObj);

Std_ReturnType EthTrcv_SetTransceiverCtrlMode(uint8 TrcvIdx, EthTrcv_ModeType CtrlMode);

#ifdef __cplusplus
}
#endif /*  #ifdef __cplusplus */
#endif /* #ifndef ETHTRCV_PRIV_H_ */
