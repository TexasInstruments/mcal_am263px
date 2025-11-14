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
 *  \file     Cpsw_Port.c
 *
 *  \brief    This file contains the Port module related functionality.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#include "Cpsw_Hw.h"
#include "Cpsw.h"
#include "Cpsw_Port.h"
#include "Eth_Types.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*Port ratelimit divide */
#define CPSW_PORT_RATELIM_DIV (32768ULL)

/**
 *  \brief Port ratelimit max counter value
 */
#define CPSW_PORT_BANDWIDTH_CNT_MAX (0x0FFFFFFFULL)

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
/*                  Internal Function Declarations                            */
/* ========================================================================== */

/* Convert rate in bps to counter */
static uint32 CpswPort_mapBwToCnt(uint32 rateInBps, uint32 cppiClkFreqHz);

/*Convert counter to rate in bps */
static uint32 CpswPort_mapCntToBw(uint32 cntVal, uint32 cppiClkFreqHz);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CpswPort_hostPortopen(uint32 baseAddr)
{
    uint32 reg = 0U;

    /* CPSW_CONTROL_REG */
    reg = CPSW_RD_REG(CONTROL);
#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
    CPSW_SET_FIELD(reg, CONTROL, S_CN_SWITCH, 1U);
#endif
    CPSW_SET_FIELD(reg, CONTROL, VLAN_AWARE, 0U);
    CPSW_SET_FIELD(reg, CONTROL, P0_RX_PAD, 1U);
    CPSW_SET_FIELD(reg, CONTROL, P0_ENABLE, 1U);
    CPSW_WR_REG(CONTROL, reg);

    /* CPPI_P0_CONTROL_REG */
    reg = CPPI_RD_REG(P0_CONTROL);
    CPPI_SET_FIELD(reg, P0_CONTROL, TX_ECC_ERR_EN, 0U);
    CPPI_SET_FIELD(reg, P0_CONTROL, RX_ECC_ERR_EN, 0U);
    CPPI_SET_FIELD(reg, P0_CONTROL, RX_REMAP_DSCP_V6, 1U);
    CPPI_SET_FIELD(reg, P0_CONTROL, RX_REMAP_DSCP_V4, 1U);
    CPPI_SET_FIELD(reg, P0_CONTROL, DSCP_IPV6_EN, 1U);
    CPPI_SET_FIELD(reg, P0_CONTROL, DSCP_IPV4_EN, 1U);
    CPPI_SET_FIELD(reg, P0_CONTROL, RX_REMAP_VLAN, 1U);
#if ((STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP) || (STD_ON == ETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP))
    CPPI_SET_FIELD(reg, P0_CONTROL, RX_CHECKSUM_EN, 1U);
    CPPI_SET_FIELD(reg, P0_CONTROL, TX_CHECKSUM_EN, 1U);
#endif
    CPPI_WR_REG(P0_CONTROL, reg);

    /* Assign all priority to switch queue priority 0 */
    CPPI_WR_REG(P0_TX_PRI_MAP, 0);

    /* Port 0 max len, beside configured MTU, need to add pass_crc
     * and encap checksum so set to max frame size for simplicity */
    CPPI_WR_FIELD(P0_RX_MAXLEN, RX_MAXLEN, ETH_MAX_FRAME_LEN);
}

void CpswPort_setDMATXPtype(uint32 baseAddr, uint32 TXPtype)
{
    CPDMA_WR_FIELD(CONTROL, DMACTRL_TX_PTYPE, TXPtype);
}

uint8 CpswPort_setBandwidthLimit(uint32 baseAddr, uint8 priority, uint32 cppiClockFreq, uint32 bandwithLimitBitPerSec)
{
    uint8  status = E_OK;
    uint64 cir    = 0LLU;

    cir = CpswPort_mapBwToCnt(bandwithLimitBitPerSec, cppiClockFreq);

    if (cir < CPSW_PORT_BANDWIDTH_CNT_MAX)
    {
        ETH_PN_WR_PRIORITY_FIELD(PRI_CIR, (uint32)priority, PRI_CIR, cir);
        ETH_PN_WR_PRIORITY_FIELD(PRI_EIR, (uint32)priority, PRI_EIR, 0U);
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

void CpswPort_getBandwidthLimit(uint32 baseAddr, uint8 priority, uint32 cppiClockFreq,
                                uint32 *bandwithLimitBitPerSecPtr)
{
    uint32 cir = 0U;

    cir = ETH_PN_RD_PRIORITY_REG(PRI_CIR, (uint32)priority);

    *bandwithLimitBitPerSecPtr = CpswPort_mapCntToBw(cir, cppiClockFreq);
}

static uint32 CpswPort_mapBwToCnt(uint32 rateInBps, uint32 cppiClkFreqHz)
{
    uint64 tmp64 = 0ULL;

    tmp64  = (uint64)rateInBps * CPSW_PORT_RATELIM_DIV;
    tmp64 += (uint64)cppiClkFreqHz - 1ULL;
    tmp64 /= cppiClkFreqHz;

    return (uint32)tmp64;
}

static uint32 CpswPort_mapCntToBw(uint32 cntVal, uint32 cppiClkFreqHz)
{
    uint64 tmp64 = 0ULL;

    tmp64  = (uint64)cntVal * (uint64)cppiClkFreqHz;
    tmp64 /= CPSW_PORT_RATELIM_DIV;

    return (uint32)tmp64;
}
