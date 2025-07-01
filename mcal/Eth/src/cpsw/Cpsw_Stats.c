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
 *   \file  Cpsw_Stats.c
 *
 *   \brief CPSW Statistics gathering and processing functionality
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "string.h"
#include "Std_Types.h"
#include "Cpsw_Hw.h"
#include "SchM_Eth.h"
#include "Cpsw_Priv.h"
#include "Cpsw.h"
#include "Cpsw_Stats.h"
#include "Cpsw_Cpdma.h"

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

/* Clear statistics from statistics structure */
static void CpswStats_clear(uint32 baseAddr, Eth_StatsObj *pStatsObj, uint8 portNum);

/* This API enables/disables the CPSW statistics for the given port */
static void CpswStats_enable(uint32 baseAddr, uint32 portNum, uint32 enableStats);

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
void CpswStats_init(uint32 baseAddr, Eth_StatsObj *pStatsObj, uint8 portIdx)
{
    /* Zero init the Eth_StatsObj structure */
    (void)memset((void *)&(pStatsObj->stats), 0, sizeof(pStatsObj->stats));
    if ((uint32)1U == pStatsObj->enableStatistics)
    {
        /* Enable statistics gathering for each port */
        CpswStats_enable(baseAddr, (uint32)0U, (uint32)TRUE);
        CpswStats_enable(baseAddr, (uint32)portIdx, (uint32)TRUE);
#if (ETH_STATS_INTERRUPT == STD_ON)
        /* Enable the STATS interrupt by setting the mask bit */
        CpswCpdma_enableStatIntr(baseAddr);

        /* Enable the STATS interrupt */
        Cpsw_enableMiscIntr(baseAddr, (uint32)CPSW_SS_MISC_STATUS_REG_STAT_PEND_MASK);
#endif /* ETH_STATS_INTERRUPT == STD_ON */
    }
}

void CpswStats_deinit(uint32 baseAddr, Eth_StatsObj *pStatsObj, uint8 portIdx)
{
    CpswStats_clear(baseAddr, pStatsObj, portIdx);

    CpswStats_enable(baseAddr, (uint32)0, (uint32)FALSE);
    CpswStats_enable(baseAddr, (uint32)portIdx, (uint32)FALSE);

#if (ETH_STATS_INTERRUPT == STD_ON)
    /* Disable the STATS interrupt by setting the mask bit */
    CpswCpdma_disableStatIntr(baseAddr);

    /* Disable the STATS interrupt in the wrapper module */
    Cpsw_disableMiscIntr(baseAddr, (uint32)CPSW_SS_MISC_STATUS_REG_STAT_PEND_MASK);
#endif /* ETH_STATS_INTERRUPT == STD_ON */
}

void CpswStats_update(uint32 baseAddr, Eth_StatsObj *pStatsObj)
{
    uint32 *pStatAddr = (uint32 *)(&pStatsObj->stats);
    uint32  statsAddr = 0U, endAddr = 0U, statval = 0U;

    uint32 macPort = Eth_GetMacPortNum();

    statsAddr = (baseAddr + CPSW_STAT_1_RXGOODFRAMES + CPSW_STAT_OFFSET(macPort));
    endAddr   = (baseAddr + CPSW_STAT_1_TX_MEMORY_PROTECT_ERROR + CPSW_STAT_OFFSET(macPort));

    /* Read the entire stats block of MAC ports then clear */
    while (statsAddr <= endAddr)
    {
        statval = HW_RD_REG32(statsAddr);
        HW_WR_REG32(statsAddr, statval);

        *pStatAddr += statval;

        pStatAddr++;
        statsAddr += 4U; /* 4 bytes address increment */
    }
}

void CpswStats_clearHostPortStats(uint32 baseAddr)
{
    volatile uint32 *pStatRegs = (uint32 *)NULL_PTR;
    uint32           statsAddr = 0U, statval = 0U;

    statsAddr = (baseAddr + CPSW_STAT_0_RXGOODFRAMES);
    pStatRegs = (volatile uint32 *)statsAddr;

    /* Read the entire stats block of MAC ports then clear */
    while ((uint32)pStatRegs <= (uint32)(baseAddr + CPSW_STAT_0_TX_MEMORY_PROTECT_ERROR))
    {
        statval    = *pStatRegs;
        *pStatRegs = statval;

        pStatRegs++;
    }
}

static void CpswStats_clear(uint32 baseAddr, Eth_StatsObj *pStatsObj, uint8 portNum)
{
    volatile uint32 *pStatRegs = (uint32 *)NULL_PTR;
    uint32          *pStatAddr = (uint32 *)NULL_PTR;
    uint32           statsAddr = 0U;

    statsAddr = (baseAddr + CPSW_STAT_0_RXGOODFRAMES);
    pStatRegs = (volatile uint32 *)(statsAddr);
    /* Clear PORT 0 Stats */
    while ((uint32)pStatRegs <= (uint32)(baseAddr + CPSW_STAT_0_TX_MEMORY_PROTECT_ERROR))
    {
        /* Write to decrement to zero */
        *pStatRegs = 0xFFFFFFFFU;
        pStatRegs++;
    }

    /* Clear PORT 1 Stats */
    statsAddr = (baseAddr + CPSW_STAT_1_RXGOODFRAMES + CPSW_STAT_OFFSET(portNum));
    pStatRegs = (volatile uint32 *)(statsAddr);
    pStatAddr = (uint32 *)((void *)(&pStatsObj->stats));

    while ((uint32)pStatRegs <= (uint32)(baseAddr + CPSW_STAT_1_TX_MEMORY_PROTECT_ERROR + CPSW_STAT_OFFSET(portNum)))
    {
        /* Write to decrement to zero */
        *pStatRegs = 0xFFFFFFFFU;
        /* Clear the software accumulation structure */
        *pStatAddr = (uint32)0U;

        pStatRegs++;
        pStatAddr++;
    }
}

static void CpswStats_enable(uint32 baseAddr, uint32 portNum, uint32 enableStats)
{
    uint32 regVal = 0U;

    regVal = CPSW_RD_REG(STAT_PORT_EN);

    if ((uint32)TRUE == enableStats)
    {
        regVal |= ((uint32)1U << portNum);
    }
    else
    {
        regVal &= ~((uint32)1U << portNum);
    }

    CPSW_WR_REG(STAT_PORT_EN, regVal);
}

void CpswStats_getStats(uint32 baseAddr, Eth_StatsObj *pStatsObj, Eth_StatsType *pStatistics)
{
    /* Update the stats */
    CpswStats_update(baseAddr, pStatsObj);

    /* Copy the updated stats to the application */
    (void)memcpy(pStatistics, &pStatsObj->stats, sizeof(Eth_StatsType));
}

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
