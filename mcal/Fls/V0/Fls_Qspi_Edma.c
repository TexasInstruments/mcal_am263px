/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Fls_Qspi_Edma.c
 *
 *  \brief    This file contains FLS MCAL driver functions for using EDMA
 *
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Fls_Qspi_Edma.h"
#if (FLS_DMA_ENABLE == STD_ON)
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define FLS_EDMA_QSPI_A_COUNT (1U)
/* Max Value for EDMA count */
#define FLS_MAX_EDMA_COUNT (31U * 1024U)
/* Value for C count */
#define FLS_EDMA_QSPI_C_COUNT (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                     Function Declarations                                  */
/* ========================================================================== */
void FLS_DmaRxIsrHandler(void *args);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

/* Requirements : MCAL-____ */
sint32 Fls_Qspi_dmaChInit(Fls_DriverObjType DrvObj)
{
    sint32 status  = MCAL_SystemP_SUCCESS;
    void  *appdata = (void *)&DrvObj;
    status         = Cdd_Dma_CbkRegister(FLS_UNIT_EDMA_HANDLER, appdata, &FLS_DmaRxIsrHandler);
    return status;
}

void FLS_edmaTransfer(uint8 *dst, uint8 *src, uint32 length, QSPI_Handle qspiHandle)
{
    Cdd_Dma_ParamEntry edmaParam0, edmaParam1;
    uint32             remaining_size, size, size_adjustment;

    /* Dma buffers and length */
    Fls_DrvObj.flsDmaLength = (((((QSPI_Config *)Fls_DrvObj.spiHandle)->object)->transaction)->count);
    Fls_DrvObj.flsDmaDstBuf = (uint8 *)(((((QSPI_Config *)Fls_DrvObj.spiHandle)->object)->transaction)->buf);
    size_adjustment         = 0U;
    /* Chaining is done here fo DMA transfer so length is divided into logical two sizes */
    size = length / FLS_MAX_EDMA_COUNT;
    /* If size is less then 2 times of FLS_MAX_EDMA_COUNT in that case just dividing the length in 2
     * equal sizes */
    if (size < 2U)
    {
        size = length / 2U;
    }
    else
    { /* In order to prevent the remaining size to become 0 below implementation is done*/
        if ((length % FLS_MAX_EDMA_COUNT) == 0U)
        {
            size = (size - 1U) * FLS_MAX_EDMA_COUNT;
        }
        else
        {
            size = size * FLS_MAX_EDMA_COUNT;
        }
    }
    // To make sure that dma_transfer length for edmaparam0 and edmaparam1 are aligned with 0x04
    if (((size) & (0x3U)) != 0U)
    {
        size_adjustment = 2U;
    }
    // size_adjustment to make size and length as multiple of 0x04
    size               = size - size_adjustment;
    remaining_size     = length - size;
    uint32 chainOption = (CDD_EDMA_OPT_ITCCHEN_MASK | CDD_EDMA_OPT_TCCHEN_MASK);
    /* edmaParam0 configuration */
    edmaParam0.srcPtr  = src;
    edmaParam0.destPtr = dst;
    if (size > FLS_MAX_EDMA_COUNT)
    {
        edmaParam0.aCnt = (uint16)FLS_MAX_EDMA_COUNT;
    }
    else
    {
        edmaParam0.aCnt = (uint16)FLS_EDMA_QSPI_A_COUNT;
    }
    edmaParam0.bCnt       = (uint16)(size / edmaParam0.aCnt);
    edmaParam0.cCnt       = (uint16)FLS_EDMA_QSPI_C_COUNT;
    edmaParam0.bCntReload = (uint16)(size / edmaParam0.aCnt);
    edmaParam0.srcBIdx    = (sint16)edmaParam0.aCnt;
    edmaParam0.destBIdx   = (sint16)edmaParam0.aCnt;
    edmaParam0.srcCIdx    = (sint16)FLS_EDMA_QSPI_A_COUNT;
    edmaParam0.destCIdx   = (sint16)FLS_EDMA_QSPI_A_COUNT;
    edmaParam0.opt        = (CDD_EDMA_OPT_SYNCDIM_MASK);
    /* edmaParam1 configuration */
    edmaParam1.srcPtr     = (void *)((uint32)(src) + size);
    edmaParam1.destPtr    = (void *)((uint32)(dst) + size);
    edmaParam1.aCnt       = (uint16)FLS_EDMA_QSPI_A_COUNT;
    edmaParam1.bCnt       = (uint16)(remaining_size / edmaParam1.aCnt);
    edmaParam1.cCnt       = (uint16)FLS_EDMA_QSPI_C_COUNT;
    edmaParam1.bCntReload = (uint16)(remaining_size / edmaParam1.aCnt);
    edmaParam1.srcBIdx    = (sint16)edmaParam1.aCnt;
    edmaParam1.destBIdx   = (sint16)edmaParam1.aCnt;
    edmaParam1.srcCIdx    = (sint16)FLS_EDMA_QSPI_A_COUNT;
    edmaParam1.destCIdx   = (sint16)FLS_EDMA_QSPI_A_COUNT;
    edmaParam1.opt        = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK);
    /* Write edmaParam0 param set for fls_read */
    Cdd_Dma_ParamSet(FLS_UNIT_EDMA_HANDLER, 0, 0, edmaParam0);
    /* Write edmaParam1 param set for fls_read */
    Cdd_Dma_ParamSet(FLS_UNIT_EDMA_HANDLER, 1, 0, edmaParam1);
    Cdd_Dma_ChainChannel(FLS_UNIT_EDMA_HANDLER, 0, 0, 1, chainOption);
    /* Set manual trigger to start QSPI transfer */
    Cdd_Dma_EnableTransferRegion(FLS_UNIT_EDMA_HANDLER, CDD_EDMA_TRIG_MODE_MANUAL);
    return;
}

void FLS_DmaRxIsrHandler(void *args)
{
    Fls_DrvObj.flsDmaStage = FLS_S_READ_DMA_DONE;
    Mcal_CacheP_inv((void *)Fls_DrvObj.flsDmaDstBuf, Fls_DrvObj.flsDmaLength, Mcal_CacheP_TYPE_ALLD);
}

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
#ifdef __cplusplus
}
#endif

#endif  // #if (FLS_DMA_ENABLE == STD_ON)
