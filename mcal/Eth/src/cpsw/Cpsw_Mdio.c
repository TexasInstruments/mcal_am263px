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
 *  \file   Cpsw_Mdio.c
 *
 *  \brief  This file contains the device abstraction layer API implementation
 *          corresponding to Management Data Input Output (MDIO).
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cpsw_Hw.h"
#include "Eth_Cfg.h"
#if (ETH_ENABLE_MII_API == STD_ON)
#include "EthTrcv.h"
#endif
#include "Eth_Priv.h"
#include "Cpsw_Mdio.h"
#include "Dem.h"
#include "Os.h"
#include "sys_common.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#if (STD_ON == ETH_MDIO_OPMODE_MANUAL)
/* MDIO Clause22 Bit definitions */
/* Preamble length (32 bits) */
#define CPSW_MDIO_PRE32_LEN (32U)

/* Start (2 bits) and Opcode (2 bits) field length */
#define CPSW_MDIO_ST_OP_LEN (4U)

/* PHY address field length (5 bits) */
#define CPSW_MDIO_PA5_LEN (5U)

/* REGADR (5 bits). PHY register address field length */
#define CPSW_MDIO_RA5_LEN (5U)

/* Turn-around field length (2 bits) */
#define CPSW_MDIO_TA_LEN (2U)

/* Data field length (16 bits) */
#define CPSW_MDIO_D16_LEN (16U)

/* Standard MDIO Functions for Clause22 (aka Article 22)
 *  i.e. Function = ST + OpCode
 *  Where:
 *   - ST (2 bits), Start of Frame (01 for Clause22)
 *   - OpCode (2 bits),
 *     - 01 for WRITE Operation
 *     - 10 for READ Operation
 */
/* MDIO Write Function for Clause22 */
#define CPSW_MDIO_WRITE_FUNC 0x05U

/* MDIO Read Function for Clause22 */
#define CPSW_MDIO_READ_FUNC 0x06U

/* Standard MDIO turn-around bits for Clause-22 (aka Article 22)
 *   - 10 for WRITE Operation
 */
/* MDIO Write Function for Clause22 */
#define CPSW_MDIO_TA_BITS 0x02U

/* MDIO Preamble Bits for Clause22 */
#define CPSW_MDIO_PRE32_BITS 0xFFFFFFFFU

/* Invalid Data Value to be set when Read Operation Failed */
#define CPSW_MDIO_INV_DATA_VAL (0xFFFFU)

#endif
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
#if (STD_ON == ETH_MDIO_OPMODE_MANUAL)
/* Write MDIO manual interface register.
 *
 * \return None
 */
static inline void CpswMdio_setManualIf(uint32 baseAddr, uint32 val);

/* Read MDIO manual interface register */
static inline uint32 CpswMdio_getManualIf(uint32 baseAddr);

/* Read MDIO PIN Register Value */
static inline uint32 CpswMdio_readMdi(uint32 baseAddr);

/* Clear Poll Enable Mask */
static inline void CpswMdio_clearPollEnableMask(uint32 baseAddr);

/* Enable MDIO Manual Mode */
static void CpswMdio_enableManualMode(uint32 baseAddr);

/* Toggle MDC Clock for Reg Read/Write */
static void CpswMdio_swToggleMdclk(uint32 baseAddr, uint32 *manualIf);

/* Sends MDIO field value */
static void CpswMdio_swFieldSend(uint32 baseAddr, uint32 len, uint32 val, uint32 *manualIf);

/* Receives MDIO field value (up to 16 bits) */
static uint16 CpswMdio_swFieldRecv(uint32 baseAddr, uint32 len, uint32 *manualIf);

/* MDIO Manual Phy Reg Read (Clause 22) */
static Std_ReturnType CpswMdio_manualPhyRegRead22(uint32 baseAddr, uint32 phyAddr, uint32 regNum, uint16 *val);

/* MDIO Manual Phy Reg Write (Clause 22) */
static void CpswMdio_manualPhyRegWrite22(uint32 baseAddr, uint32 phyAddr, uint32 regNum, uint16 val);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ETH_START_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

void CpswMdio_init(uint32 baseAddr, uint32 inFreq, uint32 outFreq)
{
#if (STD_ON == ETH_MDIO_OPMODE_MANUAL)
    (void)inFreq;  /* MISRA C Compliance */
    (void)outFreq; /* MISRA C Compliance */
    /* enable mdio manual mode */
    CpswMdio_clearPollEnableMask(baseAddr);
    CpswMdio_enableManualMode(baseAddr);
#else
    uint32 clkDiv         = 0U;
    uint32 regVal1        = 0U;
    uint32 regVal2        = 0U;
    uint32 pollEnableMask = 0xFFFFFFFFU;

    if ((uint32)0U != outFreq)
    {
        clkDiv = (inFreq / outFreq);
        if (clkDiv >= 1U)
        {
            clkDiv = clkDiv - 1U;
        }
    }

    MDIO_WR_REG(POLL_EN, pollEnableMask | ((uint32)1U << 31U));

    /* Not setting MDIO_POLL_REG_STATECHANGEMODE to use Normal mode without interrupts */

    MDIO_SET_FIELD(regVal1, POLL, IPG, 1U);
    MDIO_WR_REG(POLL, regVal1);

    MDIO_SET_FIELD(regVal2, CONTROL, CLKDIV, clkDiv);
    MDIO_WR_REG(CONTROL, regVal2);
    MDIO_SET_FIELD(regVal2, CONTROL, ENABLE, 1U);
    MDIO_WR_REG(CONTROL, regVal2);
    MDIO_SET_FIELD(regVal2, CONTROL, PREAMBLE, 1U);
    MDIO_WR_REG(CONTROL, regVal2);
#endif
}

#if (STD_ON == ETH_USR_MDIO_INTERRUPT)
void CpswMdio_enableUsrIntr(uint32 baseAddr)
{
    MDIO_WR_REG(USER_INT_MASK_SET, 3U);
}

void CpswMdio_clearUsrIntr(uint32 baseAddr)
{
    MDIO_WR_REG(USER_INT_MASKED, 3U);
}
#endif

void CpswMdio_readPhyReg(uint32 baseAddr, uint8 phyAddr, uint8 regNum, uint16 *pData)
{
#if (STD_ON == ETH_MDIO_OPMODE_MANUAL)
    (void)CpswMdio_manualPhyRegRead22(baseAddr, phyAddr, regNum, pData);

#if (STD_ON == ETH_ENABLE_MII_API)
    EthTrcv_ReadMiiIndication(Eth_DrvObj.ctrlIdx, phyAddr, regNum, *pData);
#endif /* (ETH_ENABLE_MII_API == STD_ON)*/

#else
    uint32          regVal = 0U, offset = 0U;
    volatile uint32 tempCount = ETH_TIMEOUT_DURATION;

    if (phyAddr != (uint8)0U)
    {
        offset = MDIO_USER_GROUP_USER_OFFSET;
    }

    while (1U == MDIO_RD_OFFSET_FIELD(USER_GROUP_USER_ACCESS, offset, GO))
    {
        if (0U == tempCount)
        {
#ifdef ETH_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        else
        {
            tempCount = tempCount - 1U;
        }
    }

    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, GO, 1U);
    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, WRITE, 0U);
    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, PHYADR, phyAddr);
    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, REGADR, regNum);
    MDIO_WR_OFFSET_REG(USER_GROUP_USER_ACCESS, offset, regVal);

#if (STD_OFF == ETH_USR_MDIO_INTERRUPT)
    tempCount = ETH_TIMEOUT_DURATION;
    while (1U == MDIO_RD_OFFSET_FIELD(USER_GROUP_USER_ACCESS, offset, GO))
    {
        if (0U == tempCount)
        {
#ifdef ETH_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        else
        {
            tempCount = tempCount - 1U;
        }
    }

    /* Store the data if the read is acknowledged */
    if (1U == MDIO_RD_OFFSET_FIELD(USER_GROUP_USER_ACCESS, offset, ACK))
    {
        *pData = (uint16)(MDIO_RD_OFFSET_FIELD(USER_GROUP_USER_ACCESS, offset, DATA));
#if (ETH_ENABLE_MII_API == STD_ON)
        EthTrcv_ReadMiiIndication(Eth_DrvObj.ctrlIdx, phyAddr, regNum, *pData);
#endif /* (ETH_ENABLE_MII_API == STD_ON)*/
    }
#endif /* STD_OFF == ETH_USR_MDIO_INTERRUPT*/

#endif /* STD_ON == ETH_MDIO_OPMODE_MANUAL */

    return;
}

void CpswMdio_writePhyReg(uint32 baseAddr, uint8 phyAddr, uint8 regNum, uint16 wrVal)
{
#if (STD_ON == ETH_MDIO_OPMODE_MANUAL)
    CpswMdio_manualPhyRegWrite22(baseAddr, phyAddr, regNum, wrVal);

#if (ETH_ENABLE_MII_API == STD_ON)
    EthTrcv_WriteMiiIndication(Eth_DrvObj.ctrlIdx, phyAddr, regNum);
#endif /* ETH_ENABLE_MII_API == STD_ON */

#else
    uint32          regVal = 0U, offset = 0U;
    volatile uint32 tempCount = ETH_TIMEOUT_DURATION;

    if (phyAddr != (uint8)0U)
    {
        offset = MDIO_USER_GROUP_USER_OFFSET;
    }

    while (1U == MDIO_RD_OFFSET_FIELD(USER_GROUP_USER_ACCESS, offset, GO))
    {
        if (0U == tempCount)
        {
#ifdef ETH_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        else
        {
            tempCount = tempCount - 1U;
        }
    }

    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, GO, 1U);
    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, WRITE, 1U);
    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, PHYADR, phyAddr);
    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, REGADR, regNum);
    MDIO_SET_FIELD(regVal, USER_GROUP_USER_ACCESS, DATA, wrVal);
    MDIO_WR_OFFSET_REG(USER_GROUP_USER_ACCESS, offset, regVal);
#if (STD_OFF == ETH_USR_MDIO_INTERRUPT)
    tempCount = ETH_TIMEOUT_DURATION;
    while (1U == MDIO_RD_OFFSET_FIELD(USER_GROUP_USER_ACCESS, offset, GO))
    {
        /* wait for command completion */
        if (0U == tempCount)
        {
            break;
        }
        else
        {
            tempCount = tempCount - 1U;
        }
    }

    if (0U == tempCount)
    {
        /* timeout */
#ifdef ETH_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    else
    {
#if (ETH_ENABLE_MII_API == STD_ON)
        EthTrcv_WriteMiiIndication(Eth_DrvObj.ctrlIdx, phyAddr, regNum);
#endif /* ETH_ENABLE_MII_API == STD_ON */
    }
#endif /* STD_OFF == ETH_USR_MDIO_INTERRUPT */
#endif /* STD_ON == ETH_MDIO_OPMODE_MANUAL */
    return;
}

#if (STD_ON == ETH_MDIO_OPMODE_MANUAL)
static inline void CpswMdio_setManualIf(uint32 baseAddr, uint32 val)
{
    MDIO_WR_REG(MANUAL_IF, val);
}

static inline uint32 CpswMdio_getManualIf(uint32 baseAddr)
{
    return MDIO_RD_REG(MANUAL_IF);
}

static inline uint32 CpswMdio_readMdi(uint32 baseAddr)
{
    return MDIO_RD_FIELD(MANUAL_IF, MDIO_PIN);
}

static inline void CpswMdio_clearPollEnableMask(uint32 baseAddr)
{
    /* Due to a hardware limitation, bit 31 must always be set */
    MDIO_WR_REG(POLL_EN, 0x80000000U);
}

static void CpswMdio_enableManualMode(uint32 baseAddr)
{
    uint32 regVal = 0U;

    /* update clock and enable field */
    regVal = MDIO_RD_REG(CONTROL);
    MDIO_SET_FIELD(regVal, CONTROL, ENABLE, 1U);
    MDIO_WR_REG(CONTROL, regVal);

    /* Enable manual mode */
    regVal = MDIO_RD_REG(POLL);
    MDIO_SET_FIELD(regVal, POLL, MANUALMODE, 1U);
    MDIO_WR_REG(POLL, regVal);
}

static void CpswMdio_swToggleMdclk(uint32 baseAddr, uint32 *manualIf)
{
    /* MDIO clock falling edge */
    MDIO_SET_FIELD(*manualIf, MANUAL_IF, MDIO_MDCLK_O, 0U);
    CpswMdio_setManualIf(baseAddr, *manualIf);

    /* MDIO clock delay on low */
    Eth_GetMdioLowDelay();

    /* MDIO clock rising edge */
    MDIO_SET_FIELD(*manualIf, MANUAL_IF, MDIO_MDCLK_O, 1U);
    CpswMdio_setManualIf(baseAddr, *manualIf);

    /* MDIO clock delay on high */
    Eth_GetMdioHighDelay();
}

static void CpswMdio_swFieldSend(uint32 baseAddr, uint32 len, uint32 val, uint32 *manualIf)
{
    uint32 mdo;
    uint32 i;

    for (i = len; i > 0U; i--)
    {
        mdo = (val >> (i - 1U)) & 1U;

        /* Drive MDIO data line at MDIO clock falling edge */
        MDIO_SET_FIELD(*manualIf, MANUAL_IF, MDIO_PIN, mdo);
        MDIO_SET_FIELD(*manualIf, MANUAL_IF, MDIO_MDCLK_O, 0U);
        CpswMdio_setManualIf(baseAddr, *manualIf);

        /* MDIO write clock delay on low */
        Eth_GetMdioLowDelay();

        /* MDIO clock rising edge */
        MDIO_SET_FIELD(*manualIf, MANUAL_IF, MDIO_MDCLK_O, 1U);
        CpswMdio_setManualIf(baseAddr, *manualIf);

        /* MDIO write clock delay on high */
        Eth_GetMdioHighDelay();
    }
}

static uint16 CpswMdio_swFieldRecv(uint32 baseAddr, uint32 len, uint32 *manualIf)
{
    uint32 mdi;
    uint16 val;
    uint32 i;

    val = 0U;

    for (i = len; i > 0U; i--)
    {
        mdi  = CpswMdio_readMdi(baseAddr);
        val |= ((uint16)mdi & 1U) << (i - 1U);
        /* MDIO read with clock delay */
        CpswMdio_swToggleMdclk(baseAddr, manualIf);
    }

    return val;
}

/**
 * \brief MDIO Manual Phy Reg Read (Clause 22)
 */
static Std_ReturnType CpswMdio_manualPhyRegRead22(uint32 baseAddr, uint32 phyAddr, uint32 regNum, uint16 *val)
{
    Std_ReturnType retVal = E_OK;
    uint32         manualIf;
    uint32         ack;

    manualIf = CpswMdio_getManualIf(baseAddr);

    /* Disable PHY interrupt driver */
    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_MDCLK_O, 0U);
    CpswMdio_setManualIf(baseAddr, manualIf);

    /* Enable our drive capability */
    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_OE, 1U);
    CpswMdio_setManualIf(baseAddr, manualIf);

    /* Send 32-bit preamble */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_PRE32_LEN, CPSW_MDIO_PRE32_BITS, &manualIf);

    /* Issue clause 22 MII read function {0,1,1,0} */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_ST_OP_LEN, CPSW_MDIO_READ_FUNC, &manualIf);

    /* Send the device number MSB first */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_PA5_LEN, phyAddr, &manualIf);

    /* Send the register number MSB first */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_RA5_LEN, regNum, &manualIf);

    /* Send turn-around cycles */
    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_OE, 0U);
    CpswMdio_swToggleMdclk(baseAddr, &manualIf);

    /* Get PHY ack */
    ack = CpswMdio_readMdi(baseAddr);
    CpswMdio_swToggleMdclk(baseAddr, &manualIf);

    /* Read then invalidate data if no ACK */
    *val = CpswMdio_swFieldRecv(baseAddr, CPSW_MDIO_D16_LEN, &manualIf);
    if (ack == 0U) /* If acked read the data */
    {
        retVal = E_OK;
    }
    else
    {
        *val   = CPSW_MDIO_INV_DATA_VAL;
        retVal = E_NOT_OK;
    }

    /* Give time for pull-up to work */
    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_MDCLK_O, 0U);
    CpswMdio_setManualIf(baseAddr, manualIf);
    CpswMdio_setManualIf(baseAddr, manualIf);
    CpswMdio_setManualIf(baseAddr, manualIf);

    /* Re-enable PHY interrupt function */
    CpswMdio_swToggleMdclk(baseAddr, &manualIf);

    return retVal;
}

/**
 * \brief MDIO Manual Phy Reg Write (Clause 22)
 */
static void CpswMdio_manualPhyRegWrite22(uint32 baseAddr, uint32 phyAddr, uint32 regNum, uint16 val)
{
    uint32 manualIf;

    manualIf = CpswMdio_getManualIf(baseAddr);

    /* Disable PHY interrupt driver */
    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_MDCLK_O, 0U);
    CpswMdio_setManualIf(baseAddr, manualIf);

    /* Enable our drive capability */
    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_OE, 1U);
    CpswMdio_setManualIf(baseAddr, manualIf);

    /* Send 32-bit preamble */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_PRE32_LEN, CPSW_MDIO_PRE32_BITS, &manualIf);

    /* Issue clause 22 MII write function {0,1,0,1} */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_ST_OP_LEN, CPSW_MDIO_WRITE_FUNC, &manualIf);

    /* Send the device number MSB first */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_PA5_LEN, phyAddr, &manualIf);

    /* Send the register number MSB first */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_RA5_LEN, regNum, &manualIf);

    /* Send turn-around cycles */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_TA_LEN, CPSW_MDIO_TA_BITS, &manualIf);

    /* Send Register data MSB first */
    CpswMdio_swFieldSend(baseAddr, CPSW_MDIO_D16_LEN, val, &manualIf);

    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_OE, 0U);
    CpswMdio_setManualIf(baseAddr, manualIf);

    /* Give time for pull-up to work */
    MDIO_SET_FIELD(manualIf, MANUAL_IF, MDIO_MDCLK_O, 0U);
    CpswMdio_setManualIf(baseAddr, manualIf);
    CpswMdio_setManualIf(baseAddr, manualIf);
    CpswMdio_setManualIf(baseAddr, manualIf);

    /* Re-enable PHY interrupt function */
    CpswMdio_swToggleMdclk(baseAddr, &manualIf);
}
#endif /* ETH_MDIO_OPMODE_MANUAL */

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
