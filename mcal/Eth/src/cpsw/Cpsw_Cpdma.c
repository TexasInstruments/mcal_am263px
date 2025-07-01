/*
 *
 * Copyright (c) 2024-2025 Texas Instruments Incorporated
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
 *  \file   Cpsw_Cpdma.c
 *
 *  \brief  This file contains the device abstraction layer API implementation
 *          corresponding to CPDMA module of CPSW subsystem.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cpsw_Priv.h"
#include "Cpsw_Cpdma.h"
#include "Cpsw_Hw.h"
#include "Cpsw.h"
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

FUNC(void, ETH_CODE) CpswCpdma_reset(uint32 baseAddr)
{
    volatile uint32 tempCount = ETH_TIMEOUT_DURATION;

    /* Reset the CPDMA */
    CPDMA_WR_FIELD(SOFT_RESET, SOFT_RESET, 1U);
    while (1U == CPDMA_RD_FIELD(SOFT_RESET, SOFT_RESET))
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

void CpswCpdma_enableStatIntr(uint32 baseAddr)
{
    uint32 regVal = 0U;

    regVal  = CPDMA_RD_REG(INTSTAT_SET);
    regVal |= ((uint32)1U << (uint32)CPSW_STAT_INT);
    CPDMA_WR_REG(INTSTAT_SET, regVal);
}

void CpswCpdma_enableHostErrIntr(uint32 baseAddr)
{
    uint32 regVal = 0U;

    regVal  = CPDMA_RD_REG(INTSTAT_SET);
    regVal |= ((uint32)1U << (uint32)CPSW_HOST_ERR_INT);
    CPDMA_WR_REG(INTSTAT_SET, regVal);
}

void CpswCpdma_disableStatIntr(uint32 baseAddr)
{
    uint32 regVal = 0U;

    regVal = ((uint32)1U << (uint32)CPSW_STAT_INT);
    CPDMA_WR_REG(INTSTAT_CLR, regVal);
}

void CpswCpdma_enableChIntr(uint32 baseAddr, uint32 chNum, Eth_CpswChIntr chIntr)
{
    uint32 regVal = 0U;

    if (CPSW_CH_INTR_RX == chIntr)
    {
        regVal  = CPDMA_RD_REG(TH_INTSTAT_SET);
        regVal |= ((uint32)1U << chNum);
        CPDMA_WR_REG(TH_INTSTAT_SET, regVal);
    }
    else if (CPSW_CH_INTR_RX_THR == chIntr)
    {
        regVal  = CPDMA_RD_REG(TH_INTSTAT_SET);
        regVal |= ((uint32)1U << (chNum + (uint32)0x8U));
        CPDMA_WR_REG(TH_INTSTAT_SET, regVal);
    }
    else /* if (CPSW_CH_INTR_TX == chIntr) */
    {
        regVal  = CPDMA_RD_REG(FH_INTSTAT_MASKED_SET);
        regVal |= ((uint32)1U << chNum);
        CPDMA_WR_REG(FH_INTSTAT_MASKED_SET, regVal);
    }
}

void CpswCpdma_disableChIntr(uint32 baseAddr, uint32 chNum, Eth_CpswChIntr chIntr)
{
    uint32 regVal = 0U;

    if (CPSW_CH_INTR_RX == chIntr)
    {
        regVal = ((uint32)1U << chNum);
        CPDMA_WR_REG(TH_INTSTAT_CLR, regVal);
    }
    else if (CPSW_CH_INTR_RX_THR == chIntr)
    {
        regVal = ((uint32)1U << (chNum + (uint32)0x8U));
        CPDMA_WR_REG(TH_INTSTAT_CLR, regVal);
    }
    else /* if (CPSW_CH_INTR_TX == chIntr) */
    {
        regVal = ((uint32)1U << chNum);
        CPDMA_WR_REG(FH_INTSTAT_MASKED_CLR, regVal);
    }
}

void CpswCpdma_writeEoiVector(uint32 baseAddr, Eth_CpswWrIntrLine intrLine)
{
    if (CPSW_WR_INTR_LINE_RX == intrLine)
    {
        CPDMA_WR_FIELD(EOI_VECTOR, EOI_VECTOR_DMA, 0x01U);
    }
    else if (CPSW_WR_INTR_LINE_RX_THR == intrLine)
    {
        CPDMA_WR_FIELD(EOI_VECTOR, EOI_VECTOR_DMA, 0x00U);
    }
    else if (CPSW_WR_INTR_LINE_TX == intrLine)
    {
        CPDMA_WR_FIELD(EOI_VECTOR, EOI_VECTOR_DMA, 0x02U);
    }
    else /* CPSW_WR_INTR_LINE_MISC == intrLine */
    {
        CPDMA_WR_FIELD(EOI_VECTOR, EOI_VECTOR_DMA, 0x03U);
    }
}

void CpswCpdma_enableTxCh(uint32 baseAddr)
{
    CPDMA_WR_FIELD(FH_CONTROL, FH_CONTROL_EN, 1U);
}

void CpswCpdma_disableTxCh(uint32 baseAddr)
{
    CPDMA_WR_FIELD(FH_CONTROL, FH_CONTROL_EN, 0U);
}

void CpswCpdma_teardownTxCh(uint32 baseAddr, uint32 chNum)
{
    CPDMA_WR_FIELD(FH_TEARDOWN, FH_TEARDOWN_TDN_CH, chNum);
}

void CpswCpdma_writeTxChHdp(uint32 baseAddr, uint32 descHdr, uint32 chNum)
{
    CPDMA_WR_CH_REG(FH_HDP, chNum, descHdr);
}

void CpswCpdma_writeTxChCp(uint32 baseAddr, uint32 chNum, uint32 comPtr)
{
    CPDMA_WR_CH_REG(FH_CP, chNum, comPtr);
}

uint32 CpswCpdma_readTxChCp(uint32 baseAddr, uint32 chNum)
{
    uint32 val;

    val = CPDMA_RD_CH_REG(FH_CP, chNum);

    return val;
}

void CpswCpdma_enableRxCh(uint32 baseAddr)
{
    CPDMA_WR_FIELD(TH_CONTROL, TH_CONTROL_EN, 1U);
}

void CpswCpdma_disableRxCh(uint32 baseAddr)
{
    CPDMA_WR_FIELD(TH_CONTROL, TH_CONTROL_EN, 0U);
}

void CpswCpdma_teardownRxCh(uint32 baseAddr, uint32 chNum)
{
    CPDMA_WR_FIELD(TH_TEARDOWN, TH_TEARDOWN_TDN_CH, chNum);
}

void CpswCpdma_writeRxChHdp(uint32 baseAddr, uint32 descHdr, uint32 chNum)
{
    CPDMA_WR_CH_REG(TH_HDP, chNum, descHdr);
}

void CpswCpdma_writeRxChCp(uint32 baseAddr, uint32 chNum, uint32 comPtr)
{
    CPDMA_WR_CH_REG(TH_CP, chNum, comPtr);
}

uint32 CpswCpdma_readRxChCp(uint32 baseAddr, uint32 chNum)
{
    uint32 val;

    val = CPDMA_RD_CH_REG(TH_CP, chNum);

    return val;
}

void CpswCpdma_setRxChFreeBufCnt(uint32 baseAddr, uint32 chNum, uint32 numFreeBuf)
{
    CPDMA_WR_CH_REG(TH_FREEBUFFER, chNum, numFreeBuf);
}

void CpswCpdma_setRxChThresh(uint32 baseAddr, uint32 chNum, uint32 thresh)
{
    CPDMA_WR_CH_REG(TH_PENDTHRESH, chNum, thresh);
}

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
