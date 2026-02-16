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
 *  \file   Cpsw.c
 *
 *  \brief  This file contains the device abstraction layer API implementation
 *          corresponding to CPSW subsystem.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cpsw_Hw.h"
#include "Cpsw_Priv.h"
#include "Cpsw.h"
#include "Cpsw_Mdio.h"
#include "Dem.h"
#include "Os.h"
#include "sys_common.h"

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
#define ETH_START_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
FUNC(void, ETH_CODE) Cpsw_resetEnet(uint32 baseAddr, uint8 slavePortNum)
{
    volatile uint32 tempCount = ETH_TIMEOUT_DURATION;

    /* Reset the CPDMA */
    ETH_PN_WR_PORT_FIELD(MAC_SOFT_RESET, slavePortNum, SOFT_RESET, 1U);
    while (1U == ETH_PN_RD_PORT_FIELD(MAC_SOFT_RESET, slavePortNum, SOFT_RESET))
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
}

uint32 Cpsw_getMacCtrl(uint32 baseAddr, uint8 slavePortNum)
{
    return ETH_PN_RD_PORT_REG(MAC_CONTROL, slavePortNum);
}

void Cpsw_setMacCtrl(uint32 baseAddr, uint8 slavePortNum, uint32 regVal)
{
    ETH_PN_WR_PORT_REG(MAC_CONTROL, slavePortNum, regVal);
}

void Cpsw_setRxMaxLen(uint32 baseAddr, uint8 slavePortNum, uint32 rxMaxLen)
{
    ETH_PN_WR_PORT_REG(RX_MAXLEN, slavePortNum, rxMaxLen);
}

uint32 Cpsw_checkHostErr(uint32 baseAddr)
{
    volatile uint32 retVal = FALSE;
    volatile uint32 regVal = 0U;

    regVal = CPSW_RD_FIELD(CPSW_ID_VER, IDENT);
    if (regVal != Eth_GetVersionID())
    {
        retVal = (uint32)TRUE;
    }
    else
    {
        retVal = (uint32)FALSE;
    }

    return retVal;
}

void Cpsw_setPortSrcAddr(uint32 baseAddr, uint8 slavePortNum, const uint8 macAddr[6])
{
    uint32 regVal = 0U;

    if (((uint8)1U == slavePortNum) || ((uint8)2U == slavePortNum))
    {
        ETH_PN_SET_FIELD(regVal, SA_H, MACSRCADDR_47_40, macAddr[0U]);
        ETH_PN_SET_FIELD(regVal, SA_H, MACSRCADDR_39_32, macAddr[1U]);
        ETH_PN_SET_FIELD(regVal, SA_H, MACSRCADDR_31_24, macAddr[2U]);
        ETH_PN_SET_FIELD(regVal, SA_H, MACSRCADDR_23_16, macAddr[3U]);
        ETH_PN_WR_PORT_REG(SA_H, slavePortNum, regVal);

        regVal = 0;
        ETH_PN_SET_FIELD(regVal, SA_L, MACSRCADDR_15_8, macAddr[4U]);
        ETH_PN_SET_FIELD(regVal, SA_L, MACSRCADDR_7_0, macAddr[5U]);
        ETH_PN_WR_PORT_REG(SA_L, slavePortNum, regVal);
    }
    else
    {
    }

    return;
}

void Cpsw_setPrescale(uint32 baseAddr, uint32 preScalarVal)
{
    CPSW_SS_WR_FIELD(INT_CONTROL, PRESCALE, preScalarVal);
}

Std_ReturnType Cpsw_getPortSrcAddr(uint32 baseAddr, uint32 slavePortNum, uint8 macAddr[6])
{
    Std_ReturnType retVal    = (Std_ReturnType)E_NOT_OK;
    uint32         macAddrLo = 0U, macAddrHi = 0U;

    if (((uint32)1U == slavePortNum) || ((uint32)2U == slavePortNum))
    {
        macAddrHi = ETH_PN_RD_PORT_REG(SA_H, slavePortNum);
        macAddrLo = ETH_PN_RD_PORT_REG(SA_L, slavePortNum);
    }
    else
    {
        /*only two PORT */
    }

    if ((uint32)0U == macAddrHi)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        macAddr[0U] = (uint8)ETH_PN_GET_FIELD(macAddrHi, SA_H, MACSRCADDR_47_40);
        macAddr[1U] = (uint8)ETH_PN_GET_FIELD(macAddrHi, SA_H, MACSRCADDR_39_32);
        macAddr[2U] = (uint8)ETH_PN_GET_FIELD(macAddrHi, SA_H, MACSRCADDR_31_24);
        macAddr[3U] = (uint8)ETH_PN_GET_FIELD(macAddrHi, SA_H, MACSRCADDR_23_16);
        macAddr[4U] = (uint8)ETH_PN_GET_FIELD(macAddrLo, SA_L, MACSRCADDR_15_8);
        macAddr[5U] = (uint8)ETH_PN_GET_FIELD(macAddrLo, SA_L, MACSRCADDR_7_0);
        retVal      = (Std_ReturnType)E_OK;
    }

    return retVal;
}

uint32 Cpsw_getChIntrStatus(uint32 baseAddr, Eth_CpswChIntr chIntr)
{
    uint32 regVal = 0U;

    if (CPSW_CH_INTR_RX_THR == chIntr)
    {
        regVal = CPSW_SS_RD_REG(TH_THRESH_PULSE_STATUS);
    }
    else if (CPSW_CH_INTR_RX == chIntr)
    {
        regVal = CPSW_SS_RD_REG(TH_PULSE_STATUS);
    }
    else /* if (CPSW_CH_INTR_TX == chIntr )*/
    {
        regVal = CPSW_SS_RD_REG(FH_PULSE_STATUS);
    }

    return regVal;
}

void Cpsw_enableIntrPacing(uint32 baseAddr, Eth_CpswWrInt intrType, uint32 paceVal)
{
    if (CPSW_INTR_TYPE_RX == intrType)
    {
        /* Set  maximum receive Interrupts per Millisecond*/
        CPSW_SS_WR_FIELD(TH_IMAX, TH_IMAX, paceVal);
        /* Enable pacing for Rx interrupts int control */
        CPSW_SS_WR_FIELD(INT_CONTROL, INT_BYPASS_RX, 1U);
    }

    if (CPSW_INTR_TYPE_TX == intrType)
    {
        /* Set  maximum receive Interrupts per Millisecond*/
        CPSW_SS_WR_FIELD(FH_IMAX, FH_IMAX, paceVal);
        /* Enable pacing for Tx interrupts in wrapper int control */
        CPSW_SS_WR_FIELD(INT_CONTROL, INT_BYPASS_TX, 1U);
    }

    return;
}

uint32 Cpsw_getMiscIntrStatus(uint32 baseAddr)
{
    return CPSW_SS_RD_REG(MISC_STATUS);
}

void Cpsw_enableChIntr(uint32 baseAddr, uint32 chNum, Eth_CpswChIntr chIntr)
{
    uint32 regVal = 0U;

    if (CPSW_CH_INTR_RX_THR == chIntr)
    {
        regVal  = CPSW_SS_RD_REG(TH_THRESH_PULSE_EN);
        regVal |= ((uint32)1U << chNum);
        CPSW_SS_WR_REG(TH_THRESH_PULSE_EN, regVal);
    }
    else if (CPSW_CH_INTR_RX == chIntr)
    {
        regVal  = CPSW_SS_RD_REG(TH_PULSE_EN);
        regVal |= ((uint32)1U << chNum);
        CPSW_SS_WR_REG(TH_PULSE_EN, regVal);
    }
    else /*if (CPSW_CH_INTR_TX == chIntr)*/
    {
        regVal  = CPSW_SS_RD_REG(FH_PULSE_EN);
        regVal |= ((uint32)1U << chNum);
        CPSW_SS_WR_REG(FH_PULSE_EN, regVal);
    }
}

void Cpsw_enableMiscIntr(uint32 baseAddr, uint32 miscIntrMask)
{
    uint32 regVal = 0U, regFieldVal = 0U;

    regVal       = CPSW_SS_RD_REG(MISC_EN);
    regFieldVal  = CPSW_SS_GET_FIELD(regVal, MISC_EN, MISC_EN);
    regFieldVal |= miscIntrMask;
    CPSW_SS_WR_FIELD(MISC_EN, MISC_EN, regFieldVal);
}

void Cpsw_disableMiscIntr(uint32 baseAddr, uint32 miscIntrMask)
{
    uint32 regVal = 0U, regFieldVal = 0U;

    regVal = CPSW_SS_RD_REG(MISC_EN);

    regFieldVal  = CPSW_SS_GET_FIELD(regVal, MISC_EN, MISC_EN);
    regFieldVal &= ~miscIntrMask;

    CPSW_SS_WR_FIELD(MISC_EN, MISC_EN, regFieldVal);
}

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
