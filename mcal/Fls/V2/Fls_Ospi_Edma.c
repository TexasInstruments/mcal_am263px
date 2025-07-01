/* ======================================================================
 *   Copyright (C) 2023-24 Texas Instruments Incorporated
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
 *  \file     Fls_Ospi_Edma.c
 *
 *  \brief    This file contains FLS MCAL driver functions for using EDMA
 *
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Fls_Ospi_Edma.h"
#if (FLS_DMA_ENABLE == STD_ON)
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define FLS_EDMA_OSPI_A_COUNT (1U)
/* Max Value for EDMA count */
#define FLS_MAX_EDMA_COUNT (31U * 1024U)
/* Value for C count */
#define FLS_EDMA_OSPI_C_COUNT (1U)

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
sint32 Fls_Ospi_dmaChInit(Fls_DriverObjType Fls_DrvObj)
{
    sint32 status  = MCAL_SystemP_SUCCESS;
    void  *appdata = (void *)&Fls_DrvObj;
    status         = Cdd_Dma_CbkRegister(FLS_UNIT_EDMA_HANDLER, appdata, &FLS_DmaRxIsrHandler);
    return status;
}

void FLS_edmaTransfer(uint8 *dst, uint8 *src, uint32 length, OSPI_Handle ospiHandle)
{
    Cdd_Dma_ParamEntry edmaParam0, edmaParam1;
    uint32             remaining_size, size, size_adjustment;

    /* Dma buffers and length */
    Fls_DrvObj.flsDmaLength = (((((OSPI_Config *)Fls_DrvObj.spiHandle)->object)->transaction)->count);
    Fls_DrvObj.flsDmaDstBuf = (uint8 *)(((((OSPI_Config *)Fls_DrvObj.spiHandle)->object)->transaction)->buf);
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
        edmaParam0.aCnt = (uint16)FLS_EDMA_OSPI_A_COUNT;
    }
    edmaParam0.bCnt       = (uint16)(size / edmaParam0.aCnt);
    edmaParam0.cCnt       = (uint16)FLS_EDMA_OSPI_C_COUNT;
    edmaParam0.bCntReload = (uint16)(size / edmaParam0.aCnt);
    edmaParam0.srcBIdx    = (sint16)edmaParam0.aCnt;
    edmaParam0.destBIdx   = (sint16)edmaParam0.aCnt;
    edmaParam0.srcCIdx    = (sint16)FLS_EDMA_OSPI_A_COUNT;
    edmaParam0.destCIdx   = (sint16)FLS_EDMA_OSPI_A_COUNT;
    edmaParam0.opt        = (CDD_EDMA_OPT_SYNCDIM_MASK);
    /* edmaParam1 configuration */
    edmaParam1.srcPtr     = (void *)((uint32)(src) + size);
    edmaParam1.destPtr    = (void *)((uint32)(dst) + size);
    edmaParam1.aCnt       = (uint16)FLS_EDMA_OSPI_A_COUNT;
    edmaParam1.bCnt       = (uint16)(remaining_size / edmaParam1.aCnt);
    edmaParam1.cCnt       = (uint16)FLS_EDMA_OSPI_C_COUNT;
    edmaParam1.bCntReload = (uint16)(remaining_size / edmaParam1.aCnt);
    edmaParam1.srcBIdx    = (sint16)edmaParam1.aCnt;
    edmaParam1.destBIdx   = (sint16)edmaParam1.aCnt;
    edmaParam1.srcCIdx    = (sint16)FLS_EDMA_OSPI_A_COUNT;
    edmaParam1.destCIdx   = (sint16)FLS_EDMA_OSPI_A_COUNT;
    edmaParam1.opt        = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK);
    /* Write edmaParam0 param set for fls_read */
    Cdd_Dma_ParamSet(FLS_UNIT_EDMA_HANDLER, 0, 0, edmaParam0);
    /* Write edmaParam1 param set for fls_read */
    Cdd_Dma_ParamSet(FLS_UNIT_EDMA_HANDLER, 1, 0, edmaParam1);
    Cdd_Dma_ChainChannel(FLS_UNIT_EDMA_HANDLER, 0, 0, 1, chainOption);
    /* Set manual trigger to start OSPI transfer */
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
