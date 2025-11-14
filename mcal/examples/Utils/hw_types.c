/* ======================================================================
 *   Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *  \file     hw_types.c
 *
 *  \brief    This file contains HW read/write functions used when dynamic
 *            analysis build is enabled. This is needed to avoid getting
 *            non-coverage for HW static inline functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdio.h"
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
#ifdef MCAL_DYNAMIC_BUILD_ETH
#include "Eth_Cfg.h"
#include "Hw_Cpsw_Ale.h"
#include "Hw_Cpsw_Cpdma.h"
#include "Hw_Cpsw_Cpts.h"
#include "Hw_Cpsw.h"
#include "Hw_Cpsw_Mdio.h"
#include "Hw_Cpsw_Port.h"
#include "Hw_Cpsw_Ss.h"
#include "Hw_Cpsw_Stats.h"
#include "../../../../mcal_test/eth_test/testLib/ethTestCovFlag.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32 HW_RD_REG32_RAW(uint32 addr)
{
    uint32 regVal = *(volatile uint32 *)addr;

#ifdef MCAL_DYNAMIC_BUILD_ETH
    static EthTestCoverageFlag lastCoverageFlag = ETH_TT_COVERAGE_FLAG_DEFAULT;

    static uint32 loop = 0U;

    if (lastCoverageFlag != gEthCoverageTestFlag)
    {
        lastCoverageFlag = gEthCoverageTestFlag;
        loop             = 0U;
    }

    /* Overwrite register read value for coverage testing */
    if ((ETH_TT_COVERAGE_FLAG_TX_TEARDOWN_ACK == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPDMA_FH_CP_REG(7U))) /* 7: TX channel number */
    {
        regVal = 0xFFFFFFFFU; /* valid CPSW_CPDMA_TEAR_DWN_ACK = 0xFFFFFFFCU */
    }

    if ((ETH_TT_COVERAGE_FLAG_RX_TEARDOWN_ACK == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPDMA_TH_CP_REG(0U))) /* 0: RX channel number */
    {
        regVal = 0xFFFFFFFFU; /* valid CPSW_CPDMA_TEAR_DWN_ACK = 0xFFFFFFFCU */
    }

    if ((ETH_TT_COVERAGE_FLAG_ETH_RECEIVE_TEARDOWN == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPDMA_TH_CP_REG(0U))) /* 0: RX channel number */
    {
        regVal = 0xFFFFFFFCU; /* valid CPSW_CPDMA_TEAR_DWN_ACK = 0xFFFFFFFCU */
    }

    if ((ETH_TT_COVERAGE_FLAG_MISC_IRQ_STAT_PEND == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_SS_MISC_STATUS_REG) && (loop < 1U))
    {
        regVal = CPSW_SS_MISC_STATUS_REG_STAT_PEND_MASK;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_MISC_IRQ_HOST_PEND == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_SS_MISC_STATUS_REG) && (loop < 1U))
    {
        regVal = CPSW_SS_MISC_STATUS_REG_HOST_PEND_MASK;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_RX_THRESH_IRQ == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_SS_TH_THRESH_PULSE_STATUS_REG) && (loop < 1U))
    {
        regVal = 0x55U;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_RX_IRQ == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_SS_TH_PULSE_STATUS_REG) && (loop < 1U))
    {
        regVal = 0x55U;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_ETH_RECEIVE_WRD3_OWN_DISABLE == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_SS_TH_PULSE_STATUS_REG))
    {
        regVal = 0x55U;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_ETH_RECEIVE_THRESH_WRD3_OWN_DISABLE == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_SS_TH_THRESH_PULSE_STATUS_REG))
    {
        regVal = 0x01U;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_ETH_RECEIVE_THRESH_WRD3_OWN_DISABLE == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPDMA_TH_CP_REG(0U))) /* 0: RX channel number */
    {
        regVal = 0xFFFFFFFFU; /* valid CPSW_CPDMA_TEAR_DWN_ACK = 0xFFFFFFFCU */
    }

    if ((ETH_TT_COVERAGE_FLAG_STAT_RXCRCERRORS == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_RXCRCERRORS))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_RXCRCERRORS == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_RXCRCERRORS + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_STAT_RX_BOTTOM_OF_FIFO_DROP == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_RX_BOTTOM_OF_FIFO_DROP))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_RX_BOTTOM_OF_FIFO_DROP == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_RX_BOTTOM_OF_FIFO_DROP + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_RXUNDERSIZEDFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_RXUNDERSIZEDFRAMES))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_RXUNDERSIZEDFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_RXUNDERSIZEDFRAMES + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_STAT_RXOVERSIZEDFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_RXOVERSIZEDFRAMES))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_RXOVERSIZEDFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_RXOVERSIZEDFRAMES + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_RXALIGNCODEERRORS == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_RXALIGNCODEERRORS))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_RXALIGNCODEERRORS == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_RXALIGNCODEERRORS + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_STAT_TXSINGLECOLLFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_TXSINGLECOLLFRAMES))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_TXSINGLECOLLFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_TXSINGLECOLLFRAMES + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_TXMULTCOLLFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_TXMULTCOLLFRAMES))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_TXMULTCOLLFRAMES == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_TXMULTCOLLFRAMES + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_STAT_TXLATECOLLISIONS == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_STAT_1_TXLATECOLLISIONS))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
    if ((ETH_TT_COVERAGE_FLAG_STAT_TXLATECOLLISIONS == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == (CPSW_STAT_1_TXLATECOLLISIONS + CPSW_STAT_OFFSET(2U))))
    {
        regVal = 0xFFFFFFFFU;
        loop++;
    }
#endif
    return (regVal);
}

void HW_WR_REG32_RAW(uint32 addr, uint32 value)
{
    *(volatile uint32 *)addr = value;
    return;
}

uint16 HW_RD_REG16_RAW(uint32 addr)
{
    uint16 regVal = *(volatile uint16 *)addr;
    return (regVal);
}

void HW_WR_REG16_RAW(uint32 addr, uint16 value)
{
    *(volatile uint16 *)addr = value;
    return;
}

uint8 HW_RD_REG8_RAW(uint32 addr)
{
    uint8 regVal = *(volatile uint8 *)addr;
    return (regVal);
}

void HW_WR_REG8_RAW(uint32 addr, uint8 value)
{
    *(volatile uint8 *)addr = value;
    return;
}

void HW_WR_FIELD32_RAW(uint32 addr, uint32 mask, uint32 shift, uint32 value)
{
    uint32 regVal             = *(volatile uint32 *)addr;
    regVal                   &= (~mask);
    regVal                   |= (value << shift) & mask;
    *(volatile uint32 *)addr  = regVal;
    return;
}

void HW_WR_FIELD16_RAW(uint32 addr, uint16 mask, uint32 shift, uint16 value)
{
    uint32 tempVal;
    uint16 regVal             = *(volatile uint16 *)addr;
    tempVal                   = ((uint32)regVal);
    tempVal                  &= (~((uint32)mask));
    tempVal                  |= (((uint32)value) << shift) & ((uint32)mask);
    regVal                    = (uint16)tempVal;
    *(volatile uint16 *)addr  = regVal;
    return;
}

void HW_WR_FIELD8_RAW(uint32 addr, uint8 mask, uint32 shift, uint8 value)
{
    uint32 tempVal;
    uint8  regVal            = *(volatile uint8 *)addr;
    tempVal                  = ((uint32)regVal);
    tempVal                 &= (~((uint32)mask));
    tempVal                 |= (((uint32)value) << shift) & ((uint32)mask);
    regVal                   = (uint8)tempVal;
    *(volatile uint8 *)addr  = regVal;
    return;
}

uint32 HW_RD_FIELD32_RAW(uint32 addr, uint32 mask, uint32 shift)
{
    uint32 regVal = *(volatile uint32 *)addr;

#ifdef MCAL_DYNAMIC_BUILD_ETH
    static EthTestCoverageFlag lastCoverageFlag = ETH_TT_COVERAGE_FLAG_DEFAULT;
    static uint32              loop             = 0U;

    if (lastCoverageFlag != gEthCoverageTestFlag)
    {
        lastCoverageFlag = gEthCoverageTestFlag;
        loop             = 0U;
    }

    /* Overwrite register read value for coverage testing */
    if ((ETH_TT_COVERAGE_FLAG_CHECK_HOST_ERR == gEthCoverageTestFlag) && ((addr & 0x000FFFFFU) == CPSW_CPSW_ID_VER_REG))
    {
        regVal = 0xFFFFFFFFU; /* Invalid version */
    }

    if ((ETH_TT_COVERAGE_FLAG_RESET_ENET == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_ETH_PN_MAC_SOFT_RESET_REG + CPSW_PN_OFFSET(1U)))
    {
        regVal = 0xFFFFFFFFU; /* reset bit = 1 - pending */
    }

    if ((ETH_TT_COVERAGE_FLAG_RESET_ENET == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_ETH_PN_MAC_SOFT_RESET_REG + CPSW_PN_OFFSET(2U)))
    {
        regVal = 0xFFFFFFFFU; /* reset bit = 1 - pending */
    }

    if ((ETH_TT_COVERAGE_FLAG_RESET_CPDMA == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPDMA_SOFT_RESET_REG))
    {
        regVal = 0xFFFFFFFFU; /* reset bit = 1 - pending */
    }

    if ((ETH_TT_COVERAGE_FLAG_ALE_CLEAR_TABLE == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_ALE_CONTROL_REG))
    {
        regVal = 0xFFFFFFFFU; /* CLEAR_TABLE = 1 - pending */
    }

    if ((ETH_TT_COVERAGE_FLAG_TX_TEARDOWN_ACK == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPDMA_FH_CP_REG(7U))) /* 7: TX channel number */
    {
        regVal = 0xFFFFFFFFU; /* valid CPSW_CPDMA_TEAR_DWN_ACK = 0xFFFFFFFCU */
    }

    if ((ETH_TT_COVERAGE_FLAG_RX_TEARDOWN_ACK == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPDMA_TH_CP_REG(0U))) /* 0: RX channel number */
    {
        regVal = 0xFFFFFFFFU; /* valid CPSW_CPDMA_TEAR_DWN_ACK = 0xFFFFFFFCU */
    }

    if ((ETH_TT_COVERAGE_FLAG_MDIO_PHY_GO == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == MDIO_USER_GROUP_USER_ACCESS_REG) && (mask == MDIO_USER_GROUP_USER_ACCESS_REG_GO_MASK))
    {
        regVal = MDIO_USER_GROUP_USER_ACCESS_REG_GO_MASK;
    }

    if ((ETH_TT_COVERAGE_FLAG_MDIO_PHY_GO == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == MDIO_USER_GROUP_USER_ACCESS_REG + MDIO_USER_GROUP_USER_OFFSET) &&
        (mask == MDIO_USER_GROUP_USER_ACCESS_REG_GO_MASK))
    {
        regVal = MDIO_USER_GROUP_USER_ACCESS_REG_GO_MASK;
    }

    if ((ETH_TT_COVERAGE_FLAG_MDIO_PHY_ACK == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == MDIO_USER_GROUP_USER_ACCESS_REG) && (mask == MDIO_USER_GROUP_USER_ACCESS_REG_ACK_MASK))
    {
        regVal = 0U;
    }

    if ((ETH_TT_COVERAGE_FLAG_MDIO_PHY_ACK == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == MDIO_USER_GROUP_USER_ACCESS_REG + MDIO_USER_GROUP_USER_OFFSET) &&
        (mask == MDIO_USER_GROUP_USER_ACCESS_REG_ACK_MASK))
    {
        regVal = 0U;
    }

    if ((ETH_TT_COVERAGE_FLAG_MDIO_MANUAL_ACK == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == MDIO_MANUAL_IF_REG) && (mask == MDIO_MANUAL_IF_REG_MDIO_PIN_MASK))
    {
        regVal = MDIO_MANUAL_IF_REG_MDIO_PIN_MASK;
    }

    if ((ETH_TT_COVERAGE_FLAG_CPTS_PEND_NONE == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPTS_INTSTAT_RAW_REG) && (mask == CPSW_CPTS_INTSTAT_RAW_REG_TS_PEND_RAW_MASK) &&
        (loop < 50U))
    {
        regVal = 0U;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_CPTS_RETRIEVE_LOOP == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPTS_INTSTAT_RAW_REG) && (mask == CPSW_CPTS_INTSTAT_RAW_REG_TS_PEND_RAW_MASK) &&
        (loop < /*CPSW_CPTS_RETRIEVE_TS_LOOP*/ 5000U + 1U))
    {
        regVal = 0U;
        loop++;
    }

    if ((ETH_TT_COVERAGE_FLAG_CPTS_PEND_OTHER == gEthCoverageTestFlag) &&
        ((addr & 0x000FFFFFU) == CPSW_CPTS_EVENT_1_REG) && (mask == CPSW_CPTS_EVENT_1_REG_EVENT_TYPE_MASK))
    {
        regVal = (/*CPTS_EVENT_TIME_STAMP_ROLLOVER*/ 1U) << CPSW_CPTS_EVENT_1_REG_EVENT_TYPE_SHIFT;
    }

#endif

    regVal = (regVal & mask) >> shift;
    return (regVal);
}

uint16 HW_RD_FIELD16_RAW(uint32 addr, uint16 mask, uint32 shift)
{
    uint32 tempVal;
    uint16 regVal = *(volatile uint16 *)addr;
    tempVal       = (((uint32)regVal & (uint32)mask) >> shift);
    regVal        = (uint16)tempVal;
    return (regVal);
}

uint8 HW_RD_FIELD8_RAW(uint32 addr, uint8 mask, uint32 shift)
{
    uint32 tempVal;
    uint8  regVal = *(volatile uint8 *)addr;
    tempVal       = (((uint32)regVal & (uint32)mask) >> shift);
    regVal        = (uint8)tempVal;
    return (regVal);
}
