/*
 * Copyright (C) 2024 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file   Cdd_Dma_Priv.c
 *
 *  \brief  This file contains device abstraction layer APIs for the EDMA device.
 *          There are APIs here to enable the EDMA instance, set the required
 *          configurations for communication, transmit or receive data.
 */

/* ========================================================================== */
/*                             Include Files(standard and others)             */
/* ========================================================================== */

#include "Cdd_Dma_Priv.h"
#include "Cdd_Dma.h"
#include "Mcal_Libs_Utils.h"

/* ========================================================================== */
/*                        Static Function Declaration                         */
/* ========================================================================== */

static sint32 CDD_EDMA_lld_initialize(Cdd_Dma_Handler *hEdma);
static sint32 CDD_EDMA_lld_deinitialize(Cdd_Dma_Handler *hEdma);
static void   CDD_EDMA_lld_initializeCheckChannel(uint32 channel, uint32 baseAddr, uint32 regionId);
static void   CDD_EDMA_lld_initializeCheckTcc(uint32 tcc, uint32 baseAddr, uint32 regionId);
static void   CDD_EDMA_TransferCompletion_MasterIsr_loop(uint8 i);
static void   Cdd_Edma_lld_chainingConfig(Cdd_Dma_Handler *hEdma, uint32 handleId);
/* ========================================================================== */
/*                        Local Type Declaration                         */
/* ========================================================================== */
extern uint8  Cdd_Dma_Reg_Callback[CDD_DMA_MAX_HANDLER];
extern uint64 Cdd_Dma_Soc_VirtToPhy_Internal(void *virtAddr);
#define CDD_DMA_START_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"
uint8 Cdd_Dma_TccUsed[CDD_EDMA_NUM_DMACH] = {0};
#define CDD_DMA_STOP_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"

#define CDD_DMA_START_SEC_VAR_INIT_32
#include "Cdd_Dma_MemMap.h"
uint32 Cdd_Dma_TccHandlerMapping[CDD_EDMA_NUM_DMACH] = {0};
#define CDD_DMA_STOP_SEC_VAR_INIT_32
#include "Cdd_Dma_MemMap.h"

#define CDD_DMA_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Dma_MemMap.h"
void                  *Cdd_Dma_AppDataList[CDD_EDMA_NUM_DMACH];
Cdd_Edma_EventCallback Cdd_Dma_CallBackList[CDD_EDMA_NUM_DMACH];
#define CDD_DMA_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Dma_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CDD_DMA_START_SEC_CODE
#include "Cdd_Dma_MemMap.h"

static sint32 CDD_EDMA_lld_initialize(Cdd_Dma_Handler *hEdma)
{
    sint32                     retVal = MCAL_SystemP_SUCCESS;
    CDD_EDMACCEDMACCPaRAMEntry paramSet;
    uint32                     count = 0;
    uint32                     ch    = 0;
    uint32                     qnumValue;
    uint32                     regionId;
    uint32                     queNum;
    uint32                     tcc;
    uint32                     channel;
    uint32                     maxparam;
    uint32                     param;
    uint32                     baseAddr     = hEdma->baseAddr;
    Cdd_Dma_InitHandleType     hEdmaInit    = hEdma->edmaConfig;
    Cdd_Dma_InitHandleType    *hEdmaInitPtr = &hEdmaInit;
    Cdd_Dma_ResourceObject     ownResource  = hEdmaInit.ownResource;

    if (hEdmaInitPtr == NULL_PTR)
    {
        retVal = MCAL_SystemP_FAILURE;
    }
    else
    {
        regionId = hEdmaInit.regionId;
        queNum   = hEdmaInit.queNum;
        tcc      = hEdmaInit.tcc;
        for (ch = 0; ch < ownResource.maxChannel; ch++)
        {
            channel = ownResource.channelGroup[ch]->channelId;
            /* Clear the Event miss Registers                                     */
            CDD_EDMA_lld_initializeCheckChannel(channel, baseAddr, regionId);
            /* Disable and clear DMA events for all own dma channels */
            CDD_EDMA_lld_disableDmaEvtRegion(baseAddr, regionId, channel);
            CDD_EDMA_lld_clrEvtRegion(baseAddr, regionId, channel);
            CDD_EDMA_lld_clrMissEvtRegion(baseAddr, regionId, channel);
            /* Disable the interrupt for the channel to transfer in polling mode */
            if (hEdmaInit.intrEnable != TRUE)
            {
                CDD_EDMA_lld_disableEvtIntrRegion(baseAddr, regionId, channel);
            }
            if (CDD_EDMA_CHMAPEXIST != 0U)
            {
                HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DCHMAPN(channel), channel << CDD_EDMA_MAPPING_SHIFT);
            }
            /* Initialize the DMA Queue Number Registers                            */
            qnumValue  = HW_RD_REG32(baseAddr + (CDD_EDMA_TPCC_DMAQNUMN((channel >> CDD_EDMA_QUEUE_SHIFT))));
            qnumValue &= CDD_EDMACC_DMAQNUM_CLR(channel);
            qnumValue |= CDD_EDMACC_DMAQNUM_SET(channel, queNum);
            HW_WR_REG32(baseAddr + (CDD_EDMA_TPCC_DMAQNUMN((channel >> CDD_EDMA_QUEUE_SHIFT))), qnumValue);
        }
        /* Clear CCERR register.                                               */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_CCERRCLR, CDD_EDMA_SET_ALL_BITS);
        /* Disable and clear channel interrupts for all own dma channels */
        CDD_EDMA_lld_disableEvtIntrRegion(baseAddr, regionId, tcc);
        CDD_EDMA_lld_clrIntrRegion(baseAddr, regionId, tcc);
        /* Enable the own TCCs also for the region in DRAE and DRAEH register */
        CDD_EDMA_lld_initializeCheckTcc(tcc, baseAddr, regionId);
        CDD_EDMA_lld_ccParamEntry_Init(&paramSet);
        /* cleanup Params, note h/w reset state is all 0s, must be done after
        disabling/clearning channel events */

        for (ch = 0; ch < ownResource.maxChannel; ch++)
        {
            maxparam = ownResource.channelGroup[ch]->maxParam;
            for (count = 0; count < maxparam; count++)
            {
                param = ownResource.channelGroup[ch]->paramGroup[count]->paramId;
                CDD_EDMA_lld_setPaRAM(baseAddr, param, &paramSet);
            }
        }
        for (ch = 0; ch < ownResource.maxChannel; ch++)
        {
            channel  = ownResource.channelGroup[ch]->channelId;
            maxparam = ownResource.channelGroup[ch]->maxParam;
            for (count = 0; count < maxparam; count++)
            {
                Cdd_Dma_ChannelConfigType chConfig;
                param            = ownResource.channelGroup[ch]->paramGroup[count]->paramId;
                chConfig.chType  = CDD_EDMA_CHANNEL_TYPE_DMA;
                chConfig.chNum   = channel;
                chConfig.tccNum  = tcc;
                chConfig.paramId = param;
                chConfig.evtQNum = queNum;
                CDD_EDMA_lld_configureChannelRegion(baseAddr, regionId, &chConfig);
                break;
            }
            break;
        }
    }

    return retVal;
}

void CDD_EDMA_lld_ccParamEntry_Init(CDD_EDMACCEDMACCPaRAMEntry *paramEntry)
{
    if (paramEntry != NULL_PTR)
    {
        /* Initialize all PaRAM entries as 0 */
        paramEntry->opt        = 0;
        paramEntry->srcAddr    = 0;
        paramEntry->aCnt       = 0;
        paramEntry->bCnt       = 0;
        paramEntry->destAddr   = 0;
        paramEntry->srcBIdx    = 0;
        paramEntry->destBIdx   = 0;
        paramEntry->linkAddr   = 0;
        paramEntry->bCntReload = 0;
        paramEntry->srcCIdx    = 0;
        paramEntry->destCIdx   = 0;
        paramEntry->cCnt       = 0;
        paramEntry->reserved   = 0;
    }
    else
    {
        /* Do Nothing */
    }
}

void CDD_EDMA_lld_enableChInShadowRegRegion(uint32 baseAddr, uint32 regionId, uint32 chType, uint32 chNum)
{
    uint32 draeValue;
    /* Allocate the DMA/QDMA channel */
    if (CDD_EDMA_CHANNEL_TYPE_DMA == chType)
    {
        /* FOR TYPE EDMA*/
        if (chNum < 32U)
        {
            draeValue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId));
            /* Enable the DMA channel in the DRAE registers */
            draeValue |= (uint32)0x01U << chNum;
            HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId), draeValue);
        }
        else
        {
            draeValue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId));

            /* Enable the DMA channel in the DRAEH registers */
            draeValue |= (uint32)0x01U << (chNum - 32U);
            HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId), draeValue);
        }
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void CDD_EDMA_lld_disableChInShadowRegRegion(uint32 baseAddr, uint32 regionId, uint32 chType, uint32 chNum)
{
    uint32 draeValue;
    /* Allocate the DMA/QDMA channel */
    if (CDD_EDMA_CHANNEL_TYPE_DMA == chType)
    {
        /* FOR TYPE EDMA*/
        if (chNum < 32U)
        {
            draeValue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId));
            /* Enable the DMA channel in the DRAE registers */
            draeValue &= ~((uint32)0x01U << chNum);
            HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId), draeValue);
        }
        else
        {
            draeValue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId));
            /* Enable the DMA channel in the DRAEH registers */
            draeValue &= ~((uint32)0x01U << (chNum - 32U));
            HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId), draeValue);
        }
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void CDD_EDMA_lld_channelToParamMap(uint32 baseAddr, uint32 channel, uint32 paramSet)

{
    if (CDD_EDMA_CHMAPEXIST != 0U)
    {
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DCHMAPN(channel), paramSet << CDD_EDMA_MAPPING_SHIFT);
    }
}

void CDD_EDMA_lld_mapChToEvtQ(uint32 baseAddr, uint32 chType, uint32 chNum, uint32 evtQNum)
{
    uint32 qnumValue;
    if (CDD_EDMA_CHANNEL_TYPE_DMA == chType)
    {
        /* Associate DMA Channel to Event Queue                             */
        qnumValue  = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DMAQNUMN(chNum >> CDD_EDMA_QUEUE_SHIFT));
        qnumValue &= CDD_EDMACC_DMAQNUM_CLR(chNum);
        qnumValue |= CDD_EDMACC_DMAQNUM_SET(chNum, evtQNum);
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DMAQNUMN(chNum >> 3U), qnumValue);
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void CDD_EDMA_lld_unmapChToEvtQ(uint32 baseAddr, uint32 chType, uint32 chNum)
{
    uint32 qnumValue;
    if (CDD_EDMA_CHANNEL_TYPE_DMA == chType)
    {
        /* Unmap DMA Channel to Event Queue                                */
        qnumValue  = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DMAQNUMN(chNum >> 3U));
        qnumValue &= CDD_EDMACC_DMAQNUM_CLR(chNum);
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DMAQNUMN(chNum >> 3U), qnumValue);
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void CDD_EDMA_lld_mapQdmaChToPaRAM(uint32 baseAddr, uint32 chNum, const uint32 *paRAMId)
{
    uint32 qchmapValue;
    /* Map Parameter RAM Set Number for specified channelId             */
    qchmapValue  = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_QCHMAPN(chNum));
    qchmapValue &= CDD_EDMACC_QCHMAP_PAENTRY_CLR;
    qchmapValue |= (uint32)CDD_EDMACC_QCHMAP_PAENTRY_SET(*paRAMId);
    HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_QCHMAPN(chNum), qchmapValue);
}

void CDD_EDMA_lld_clrMissEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum)
{
    if (chNum < 32U)
    {
        /*clear SECR to clean any previous NULL_PTR request */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_SECR_RN(regionId), (uint32)0x01U << chNum);

        /*clear EMCR to clean any previous NULL_PTR request */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EMCR, (uint32)0x01U << chNum);
    }
    else
    {
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_SECRH_RN(regionId), (uint32)0x01U << (chNum - 32U));
        /*clear EMCRH to clean any previous NULL_PTR request */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EMCRH, (uint32)0x01U << (chNum - 32U));
    }
}

void CDD_EDMA_lld_clrCCErr(uint32 baseAddr, uint32 flags)
{
    /* (CCERRCLR) - clear channel controller error register */
    HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_CCERRCLR, flags);
}

void CDD_EDMA_lld_setEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum)
{
    if (chNum < 32U)
    {
        /* (ESR) - set corresponding bit to set a event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_ESR_RN(regionId), (uint32)0x01U << chNum);
    }
    else
    {
        /* (ESRH) - set corresponding bit to set a event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_ESRH_RN(regionId), (uint32)0x01U << (chNum - 32U));
    }
}

void CDD_EDMA_lld_clrEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum)
{
    if (chNum < 32U)
    {
        /* (ECR) - set corresponding bit to clear a event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_ECR_RN(regionId), (uint32)0x01U << chNum);
    }
    else
    {
        /* (ECRH) - set corresponding bit to clear a event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_ECRH_RN(regionId), (uint32)0x01U << (chNum - 32U));
    }
}

void CDD_EDMA_lld_enableDmaEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum)
{
    if (chNum < 32U)
    {
        /* (EESR) - set corresponding bit to enable DMA event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EESR_RN(regionId), (uint32)0x01U << chNum);
    }
    else
    {
        /* (EESRH) - set corresponding bit to enable DMA event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EESRH_RN(regionId), (uint32)0x01U << (chNum - 32U));
    }
}

void CDD_EDMA_lld_disableDmaEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum)
{
    if (chNum < 32U)
    {
        /* (EECR) - set corresponding bit to disable event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EECR_RN(regionId), (uint32)0x01U << chNum);
    }
    else
    {
        /* (EECRH) - set corresponding bit to disable event */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EECRH_RN(regionId), (uint32)0x01U << (chNum - 32U));
    }
}

uint32 CDD_EDMA_lld_getIntrStatusRegion(uint32 baseAddr, uint32 regionId)
{
    uint32 intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_IPR_RN(regionId));

    return intrStatusVal;
}

uint32 CDD_EDMA_lld_intrStatusHighGetRegion(uint32 baseAddr, uint32 regionId)
{
    uint32 intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_IPRH_RN(regionId));

    return intrStatusVal;
}

uint32 CDD_EDMA_lld_readIntrStatusRegion(uint32 baseAddr, uint32 regionId, uint32 tccNum)
{
    uint32 intrStatus = 0;

    if (tccNum < 32U)
    {
        if ((CDD_EDMA_lld_getIntrStatusRegion(baseAddr, regionId) & (0x1U << tccNum)) == (0x1U << tccNum))
        {
            intrStatus = 1;
        }
    }
    else
    {
        if ((CDD_EDMA_lld_intrStatusHighGetRegion(baseAddr, regionId) & (0x1U << (tccNum - 32U))) ==
            (0x1U << (tccNum - 32U)))
        {
            intrStatus = 1;
        }
    }
    return intrStatus;
}

uint32 CDD_EDMA_lld_getEventStatus(uint32 baseAddr)
{
    uint32 intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_ER);

    return intrStatusVal;
}

uint32 CDD_EDMA_lld_getEventStatusHigh(uint32 baseAddr)
{
    uint32 intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_ERH);

    return intrStatusVal;
}

uint32 CDD_EDMA_lld_readEventStatusRegion(uint32 baseAddr, uint32 chNum)
{
    uint32 eventStatus = 0;

    if (chNum < 32U)
    {
        if ((CDD_EDMA_lld_getEventStatus(baseAddr) & (0x1U << chNum)) == (0x1U << chNum))
        {
            eventStatus = 1;
        }
    }
    else
    {
        if ((CDD_EDMA_lld_getEventStatusHigh(baseAddr) & (0x1U << (chNum - 32U))) == (0x1U << (chNum - 32U)))
        {
            eventStatus = 1;
        }
    }
    return eventStatus;
}

void CDD_EDMA_lld_enableEvtIntrRegion(uint32 baseAddr, uint32 regionId, uint32 chNum)
{
    if (chNum < 32U)
    {
        /*  Interrupt Enable Set Register (IESR) */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_IESR_RN(regionId), (uint32)0x01U << chNum);
    }
    else
    {
        /*  Interrupt Enable Set Register (IESRH) */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_IESRH_RN(regionId), (uint32)0x01U << (chNum - 32U));
    }
}

void CDD_EDMA_lld_disableEvtIntrRegion(uint32 baseAddr, uint32 regionId, uint32 chNum)
{
    if (chNum < 32U)
    {
        /* Interrupt Enable Clear Register (IECR) */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_IECR_RN(regionId), (uint32)0x01U << chNum);
    }
    else
    {
        /* Interrupt Enable Clear Register (IECRH) */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_IECRH_RN(regionId), (uint32)0x01U << (chNum - 32U));
    }
}

void CDD_EDMA_lld_clrIntrRegion(uint32 baseAddr, uint32 regionId, uint32 value)
{
    if (value < 32U)
    {
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_ICR_RN(regionId), (uint32)1U << value);
    }
    else
    {
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_ICRH_RN(regionId), (uint32)1U << (value - 32U));
    }
}

void CDD_EDMA_lld_getPaRAM(uint32 baseAddr, uint32 paRAMId, CDD_EDMACCEDMACCPaRAMEntry *currPaRAM)
{
    uint32  i = 0;
    uint32  sr;
    uint32 *ds = (uint32 *)currPaRAM;

    sr = baseAddr + CDD_EDMA_TPCC_OPT(paRAMId);

    for (i = 0; i < CDD_EDMACC_PARAM_ENTRY_FIELDS; i++)
    {
        *ds = HW_RD_REG32(sr);
        ds++;
        sr += (uint32)sizeof(uint32);
    }
}

void CDD_EDMA_lld_setPaRAM(uint32 baseAddr, uint32 paRAMId, const CDD_EDMACCEDMACCPaRAMEntry *newPaRAM)
{
    uint32          i  = 0;
    uint32         *sr = (uint32 *)newPaRAM;
    volatile uint32 ds;
    uint32          dsAddr = baseAddr + CDD_EDMA_TPCC_OPT(paRAMId);

    ds = (uint32)(dsAddr);

    for (i = 0; i < CDD_EDMACC_PARAM_ENTRY_FIELDS; i++)
    {
        HW_WR_REG32(ds, *sr);
        ds += (uint32)sizeof(uint32);
        sr++;
    }
}

uint32 CDD_EDMA_lld_configureChannelRegion(uint32 baseAddr, uint32 regionId, const Cdd_Dma_ChannelConfigType *chConfig)
{
    uint32 optValue;
    uint32 retVal = FALSE;
    if (((CDD_EDMA_CHANNEL_TYPE_DMA == chConfig->chType) && (chConfig->chNum < CDD_EDMA_NUM_DMACH)))
    {
        /* Enable the DMA channel in the enabled in the shadow region
         * specific register
         */
        CDD_EDMA_lld_enableChInShadowRegRegion(baseAddr, regionId, chConfig->chType, chConfig->chNum);

        CDD_EDMA_lld_mapChToEvtQ(baseAddr, chConfig->chType, chConfig->chNum, chConfig->evtQNum);

        if (CDD_EDMA_CHANNEL_TYPE_DMA == chConfig->chType)
        {
            CDD_EDMA_lld_channelToParamMap(baseAddr, chConfig->chNum, chConfig->paramId);
        }
        else
        {
            CDD_EDMA_lld_mapQdmaChToPaRAM(baseAddr, chConfig->chNum, &chConfig->paramId);
        }

        optValue  = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_OPT(chConfig->paramId));
        optValue &= CDD_EDMACC_OPT_TCC_CLR;
        optValue |= CDD_EDMACC_OPT_TCC_SET(chConfig->tccNum);
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_OPT(chConfig->paramId), optValue);

        retVal = (uint32)TRUE;
    }
    return retVal;
}

uint32 CDD_EDMA_lld_freeChannelRegion(uint32 baseAddr, uint32 regionId, uint32 chType, uint32 chNum, uint32 trigMode)
{
    uint32 retVal = FALSE;
    if ((chNum < CDD_EDMA_NUM_DMACH) && (CDD_EDMA_CHANNEL_TYPE_DMA == chType))
    {
        CDD_EDMA_lld_disableTransferRegion(baseAddr, regionId, chNum, trigMode);
        /* Disable the DMA channel in the shadow region specific register
         */
        CDD_EDMA_lld_disableChInShadowRegRegion(baseAddr, regionId, chType, chNum);

        CDD_EDMA_lld_unmapChToEvtQ(baseAddr, chType, chNum);

        retVal = (uint32)TRUE;
    }
    return retVal;
}

uint32 CDD_EDMA_lld_enableTransferRegion(uint32 baseAddr, uint32 regionId, uint32 chNum, uint32 trigMode)
{
    uint32 retVal = FALSE;
    switch (trigMode)
    {
        case CDD_EDMA_TRIG_MODE_MANUAL:
            if (chNum < CDD_EDMA_NUM_DMACH)
            {
                CDD_EDMA_lld_setEvtRegion(baseAddr, regionId, chNum);
                retVal = (uint32)TRUE;
            }
            break;

        case CDD_EDMA_TRIG_MODE_EVENT:
            if (chNum < CDD_EDMA_NUM_DMACH)
            {
                /*clear SECR & EMCR to clean any previous NULL_PTR request    */
                CDD_EDMA_lld_clrMissEvtRegion(baseAddr, regionId, chNum);

                /* Set EESR to enable event                               */
                CDD_EDMA_lld_enableDmaEvtRegion(baseAddr, regionId, chNum);
                retVal = (uint32)TRUE;
            }
            break;

        default:
            retVal = (uint32)FALSE;
            break;
    }
    return retVal;
}

uint32 CDD_EDMA_lld_disableTransferRegion(uint32 baseAddr, uint32 regionId, uint32 chNum, uint32 trigMode)
{
    uint32 retVal = FALSE;
    switch (trigMode)
    {
        case CDD_EDMA_TRIG_MODE_MANUAL:
            if (chNum < CDD_EDMA_NUM_DMACH)
            {
                CDD_EDMA_lld_clrEvtRegion(baseAddr, regionId, chNum);
                retVal = (uint32)TRUE;
            }
            break;

        case CDD_EDMA_TRIG_MODE_EVENT:
            if (chNum < CDD_EDMA_NUM_DMACH)
            {
                /*clear SECR & EMCR to clean any previous NULL_PTR request    */
                CDD_EDMA_lld_clrMissEvtRegion(baseAddr, regionId, chNum);

                /* Set EESR to enable event                               */
                CDD_EDMA_lld_disableDmaEvtRegion(baseAddr, regionId, chNum);
                retVal = (uint32)TRUE;
            }
            break;

        default:
            retVal = (uint32)FALSE;
            break;
    }
    return retVal;
}

static sint32 CDD_EDMA_lld_deinitialize(Cdd_Dma_Handler *hEdma)
{
    sint32                  retVal = MCAL_SystemP_SUCCESS;
    uint32                  ch;
    uint32                  tcc;
    uint32                  channel;
    uint32                  qnumValue;
    uint32                  regionId;
    uint32                  baseAddr     = hEdma->baseAddr;
    Cdd_Dma_InitHandleType  hEdmaInit    = hEdma->edmaConfig;
    Cdd_Dma_InitHandleType *hEdmaInitPtr = &hEdmaInit;
    Cdd_Dma_ResourceObject  ownResource  = hEdmaInit.ownResource;

    if (hEdmaInitPtr == NULL_PTR)
    {
        retVal = MCAL_SystemP_FAILURE;
    }
    else
    {
        regionId = hEdmaInit.regionId;
        tcc      = hEdmaInit.tcc;
        /* Disable the DMA (0 - 62) channels in the DRAE register */
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId), CDD_EDMA_CLR_ALL_BITS);
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId), CDD_EDMA_CLR_ALL_BITS);

        CDD_EDMA_lld_clrCCErr(baseAddr, CDD_EDMACC_CLR_TCCERR);

        /* Clear the Event miss Registers                      */
        for (ch = 0; ch < ownResource.maxChannel; ch++)
        {
            channel = ownResource.channelGroup[ch]->channelId;
            /* Clear the Event miss Registers                                     */
            if (channel < 31U)
            {
                HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EMCR, ((uint32)1 << channel));
            }
            else
            {
#if CDD_EDMA_NUM_DMACH > 32
                HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EMCRH, ((uint32)1 << (channel - 32U)));
#endif
            }
            /* Deinitialize the Queue Number Registers */
            qnumValue  = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DMAQNUMN((channel >> 3U)));
            qnumValue &= CDD_EDMACC_DMAQNUM_CLR(channel);
            HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DMAQNUMN((channel >> 3U)), qnumValue);
        }
        /* Disable and clear channel interrupts for all dma channels */

        CDD_EDMA_lld_disableEvtIntrRegion(baseAddr, regionId, tcc);
        CDD_EDMA_lld_clrIntrRegion(baseAddr, regionId, tcc);

        for (ch = 0; ch < ownResource.maxChannel; ch++)
        {
            channel = ownResource.channelGroup[ch]->channelId;
            if (hEdmaInit.transferType == CDD_DMA_TRANSFER_TYPE_MEMORY_TRANSFER)
            {
                CDD_EDMA_lld_freeChannelRegion(baseAddr, regionId, CDD_EDMA_CHANNEL_TYPE_DMA, channel,
                                               CDD_EDMA_TRIG_MODE_MANUAL);
            }
            else
            {
                CDD_EDMA_lld_freeChannelRegion(baseAddr, regionId, CDD_EDMA_CHANNEL_TYPE_DMA, channel,
                                               CDD_EDMA_TRIG_MODE_EVENT);
            }
        }
    }
    return retVal;
}
void CDD_EDMA_lld_chainChannel(uint32 baseAddr, uint32 paRAMId1, uint32 chId2, uint32 chainOptions)
{
    CDD_EDMACCEDMACCPaRAMEntry *currPaRAM     = (CDD_EDMACCEDMACCPaRAMEntry *)NULL_PTR;
    uint32                      currPaRAMAddr = baseAddr + CDD_EDMA_TPCC_OPT(paRAMId1);
    uint32                      optVal;
    uint32                      optAddr;

    /* Get param set for the channel Id passed*/
    currPaRAM = (CDD_EDMACCEDMACCPaRAMEntry *)(currPaRAMAddr);

    optAddr  = (uint32)&currPaRAM->opt;
    optVal   = HW_RD_REG32((uint32)optAddr);
    optVal  &= ~(CDD_EDMA_OPT_TCCHEN_MASK | CDD_EDMA_OPT_ITCCHEN_MASK | CDD_EDMA_OPT_TCINTEN_MASK |
                CDD_EDMA_OPT_ITCINTEN_MASK);
    optVal  |= chainOptions;
    optVal  &= ~CDD_EDMA_TPCC_OPT_TCC_MASK;
    optVal  |= (chId2 << CDD_EDMA_TPCC_OPT_TCC_SHIFT) & CDD_EDMA_TPCC_OPT_TCC_MASK;
    HW_WR_REG32((uint32)optAddr, optVal);
}

void CDD_EDMA_lld_linkChannel(uint32 baseAddr, uint32 paRAMId1, uint32 paRAMId2)
{
    CDD_EDMACCEDMACCPaRAMEntry *currPaRAM1;
    CDD_EDMACCEDMACCPaRAMEntry *currPaRAM2;
    uint32                      optVal1, optVal2;
    uint32                      currPaRAMAddr1 = baseAddr + CDD_EDMA_TPCC_OPT(paRAMId1);
    uint32                      currPaRAMAddr2 = baseAddr + CDD_EDMA_TPCC_OPT(paRAMId2);
    uint32                      lnkAddr;

    /* Get param set for the paRAMId1 passed*/
    currPaRAM1 = (CDD_EDMACCEDMACCPaRAMEntry *)(currPaRAMAddr1);

    /* Update the Link field with lch2 PaRAM set */
    lnkAddr = (uint32)&currPaRAM1->linkAddr;
    HW_WR_REG16(lnkAddr, (uint16)((baseAddr + CDD_EDMA_TPCC_OPT(paRAMId2)) & (uint16)0x0FFFF));

    /* Get param set for the paRAMId2 passed*/
    currPaRAM2 = (CDD_EDMACCEDMACCPaRAMEntry *)(currPaRAMAddr2);

    /*Updated TCC value of param2 with that of param1*/
    optVal1  = HW_RD_REG32((uint32)&currPaRAM1->opt);
    optVal2  = HW_RD_REG32((uint32)&currPaRAM2->opt);
    optVal2 &= ~CDD_EDMA_TPCC_OPT_TCC_MASK;
    optVal2 |= optVal1 & CDD_EDMA_TPCC_OPT_TCC_MASK;
    HW_WR_REG32((uint32)&currPaRAM2->opt, optVal2);
}

void CDD_EDMA_lld_init(Cdd_Dma_ConfigType *hEdmaList)
{
    Cdd_Dma_Handler       *hEdma;
    Cdd_Dma_InitHandleType hEdmaInit;
    sint32                 status;
    for (uint32 i = 0; i < (uint32)CDD_DMA_MAX_HANDLER; i++)
    {
        hEdma  = hEdmaList->CddDmaDriverHandler[i];
        status = MCAL_SystemP_SUCCESS;
        if (hEdma == NULL_PTR)
        {
            status = MCAL_SystemP_FAILURE;
        }
        if (MCAL_SystemP_SUCCESS == status)
        {
            hEdmaInit = hEdma->edmaConfig;

            /* Init state */
            CDD_EDMA_lld_initialize(hEdma);
            /* Global mapping of tcc with the handler */
            Cdd_Dma_TccHandlerMapping[i] = hEdmaInit.tcc;
            /* keep track of that what tcc are actaully in used , so that remaining can be used for
             * dummy*/
            Cdd_Dma_TccUsed[hEdmaInit.tcc] = 1;
            if (hEdmaInit.intrEnable == TRUE)
            {
                /* Register the master ISR. */
                /* Enable the aggregated interrupt. */
                Mcal_Libs_Utils_unlockMMR();
                HW_WR_REG32(hEdmaInit.intrAggEnableAddr, hEdmaInit.intrAggEnableMask);
                Mcal_Libs_Utils_lockMMR();
            }
        }
    }
    for (uint32 i = 0; i < (uint32)CDD_DMA_MAX_HANDLER; i++)
    {
        hEdma = hEdmaList->CddDmaDriverHandler[i];
        Cdd_Edma_lld_chainingConfig(hEdma, i);
    }
}

void CDD_EDMA_lld_deInit(Cdd_Dma_ConfigType *hEdmaList)
{
    for (uint32 i = 0; i < (uint32)CDD_DMA_MAX_HANDLER; i++)
    {
        Cdd_Dma_Handler *hEdma = hEdmaList->CddDmaDriverHandler[i];
        if ((NULL_PTR != hEdma))
        {
            CDD_EDMA_lld_deinitialize(hEdma);
            CDD_EDMA_lld_unregisterIntr(hEdma);
        }
        else
        {
            /*Do Nothing*/
        }
    }
}

Std_ReturnType CDD_EDMA_lld_registerIntr(Cdd_Dma_Handler *hEdma, void *appdata, Cdd_Edma_EventCallback callback,
                                         uint32 handleId)
{
    Std_ReturnType         status = E_OK;
    Cdd_Dma_InitHandleType hEdmaInit;
    uint32                 tcc, maxChannel;
    if ((hEdma == NULL_PTR) || (callback == NULL_PTR))
    {
        status = E_NOT_OK;
    }
    if (status == E_OK)
    {
        hEdmaInit  = hEdma->edmaConfig;
        tcc        = hEdmaInit.tcc;
        maxChannel = hEdmaInit.ownResource.maxChannel;
        if (maxChannel > 1U)
        {
            tcc = Cdd_Dma_ChainingTcc[handleId][maxChannel - 1U];
        }
        if (hEdmaInit.intrEnable == TRUE)
        {
            SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0();
            Cdd_Dma_AppDataList[tcc]  = appdata;
            Cdd_Dma_CallBackList[tcc] = callback;
            SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0();

            /*Enable the tcc interrupt bit.*/
            CDD_EDMA_lld_enableEvtIntrRegion(hEdma->baseAddr, hEdmaInit.regionId, tcc);
        }
        else
        {
            status = E_NOT_OK;
        }
    }
    return status;
}

sint32 CDD_EDMA_lld_unregisterIntr(Cdd_Dma_Handler *hEdma)
{
    sint32                 status = MCAL_SystemP_SUCCESS;
    Cdd_Dma_InitHandleType hEdmaInit;

    if (hEdma == NULL_PTR)
    {
        status = MCAL_SystemP_FAILURE;
    }
    if (status == MCAL_SystemP_SUCCESS)
    {
        hEdmaInit = hEdma->edmaConfig;
        CDD_EDMA_lld_disableEvtIntrRegion(hEdma->baseAddr, hEdmaInit.regionId, hEdmaInit.tcc);
    }
    return status;
}

void CDD_EDMA_lld_GetTcc(uint32 handleId, uint32 channelIdx)
{
    for (uint32 i = 0; i < CDD_EDMA_NUM_DMACH; i++)
    {
        if (Cdd_Dma_TccUsed[i] == 0U)
        {
            Cdd_Dma_TccUsed[i]                        = 1;
            Cdd_Dma_ChainingTcc[handleId][channelIdx] = i;
            break;
        }
    }
}

void CDD_EDMA_lld_chainingConfigureChannelRegion(Cdd_Dma_Handler *hEdma, uint32 handleId)
{
    uint32                     baseAddr = hEdma->baseAddr, regval, param, channel, queNum;
    CDD_EDMACCEDMACCPaRAMEntry paramSet;
    Cdd_Dma_InitHandleType     hEdmaInit    = hEdma->edmaConfig;
    uint32                     region       = hEdmaInit.regionId;
    Cdd_Dma_ResourceObject     ownResources = hEdmaInit.ownResource;
    uint32                     maxChannel   = ownResources.maxChannel;
    for (uint32 chIdx = 1; chIdx < maxChannel; chIdx++)
    {
        uint32 tcc = Cdd_Dma_ChainingTcc[handleId][chIdx];
        CDD_EDMA_lld_disableEvtIntrRegion(baseAddr, region, tcc);
        CDD_EDMA_lld_clrIntrRegion(baseAddr, region, tcc);
        /* Enable the own TCCs also for the region in DRAE and DRAEH register */
        if (tcc < 32U)
        {
            regval = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(region));
            HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(region), (regval | (1U << tcc)));
        }
        else
        {
            regval = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(region));
            HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(region), (regval | (1U << (tcc % 32U))));
        }
        channel = ownResources.channelGroup[chIdx]->channelId;
        queNum  = hEdmaInit.queNum;
        param   = ownResources.channelGroup[chIdx]->paramGroup[0]->paramId;
        CDD_EDMA_lld_ccParamEntry_Init(&paramSet);
        /* cleanup Params, note h/w reset state is all 0s, must be done after
        disabling/clearning channel events */
        CDD_EDMA_lld_setPaRAM(baseAddr, param, &paramSet);
        {
            Cdd_Dma_ChannelConfigType chConfig;
            chConfig.chType  = CDD_EDMA_CHANNEL_TYPE_DMA;
            chConfig.chNum   = channel;
            chConfig.tccNum  = tcc;
            chConfig.paramId = param;
            chConfig.evtQNum = queNum;
            CDD_EDMA_lld_configureChannelRegion(baseAddr, region, &chConfig);
        }
    }
}

uint64 Cdd_Dma_Soc_VirtToPhy(void *virtAddr)
{
    uint64 phyAddr = 0; /* Default case */
    phyAddr        = Cdd_Dma_Soc_VirtToPhy_Internal(virtAddr);
    return (phyAddr);
}

void Cdd_Dma_CbkUnregister(uint32 handleId)
{
    Cdd_Dma_Reg_Callback[handleId] = 0;
}

static void CDD_EDMA_lld_initializeCheckChannel(uint32 channel, uint32 baseAddr, uint32 regionId)
{
    uint32 regvalue;
    if (channel < 31U)
    {
        regvalue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_EMCR);
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EMCR, (regvalue | (1U << channel)));

        /* Enable the own DMA (0 - 64) channels in the DRAE and DRAEH register */
        regvalue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId));
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId), (regvalue | (1U << channel)));
    }
    else
    {
#if CDD_EDMA_NUM_DMACH > 32
        regvalue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_EMCRH);
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_EMCRH, (regvalue | (1U << (channel - 32U))));
        regvalue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId));
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId), (regvalue | (1U << (channel - 32U))));
#endif
    }
}

static void CDD_EDMA_lld_initializeCheckTcc(uint32 tcc, uint32 baseAddr, uint32 regionId)
{
    uint32 regvalue;
    if (tcc < 32U)
    {
        regvalue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId));
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEM(regionId), (regvalue | (1U << tcc)));
    }
    else
    {
        regvalue = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId));
        HW_WR_REG32(baseAddr + CDD_EDMA_TPCC_DRAEHM(regionId), (regvalue | (1U << (tcc % 32U))));
    }
}

static void Cdd_Edma_lld_chainingConfig(Cdd_Dma_Handler *hEdma, uint32 handleId)
{
    uint32               maxChannel;
    Cdd_Dma_TransferMode mode;
    if (hEdma != NULL_PTR)
    {
        mode = hEdma->edmaConfig.transferMode;
        if (mode == CDD_DMA_TRANSFER_MODE_CHAINING)
        {
            maxChannel = hEdma->edmaConfig.ownResource.maxChannel;
            for (uint32 chIdx = 1; chIdx < maxChannel; chIdx++)
            {
                CDD_EDMA_lld_GetTcc(handleId, chIdx);
            }
            CDD_EDMA_lld_chainingConfigureChannelRegion(hEdma, handleId);
        }
    }
}

#define CDD_DMA_STOP_SEC_CODE
#include "Cdd_Dma_MemMap.h"

#define CDD_DMA_START_SEC_ISR_CODE
#include "Cdd_Dma_MemMap.h"

MCAL_INTERRUPT_ATTRIBUTE
void CDD_EDMA_TransferCompletion_MasterIsr(void)
{
    for (uint8 i = 0; i < (uint8)CDD_DMA_MAX_HANDLER; i++)
    {
        CDD_EDMA_TransferCompletion_MasterIsr_loop(i);
    }
}

static void CDD_EDMA_TransferCompletion_MasterIsr_loop(uint8 i)
{
    uint32                 baseAddr, regionId, tccNum;
    uint32                 intrLow, intrHigh, maxChannel;
    Cdd_Dma_Handler       *hEdma;
    Cdd_Dma_InitHandleType hEdmaInit;
    hEdma = Cdd_Dma_HandlerList->CddDmaDriverHandler[i];
    if (hEdma != NULL_PTR)
    {
        Cdd_Dma_handleAlreadyInUse[i] = 0;
        baseAddr                      = hEdma->baseAddr;
        hEdmaInit                     = hEdma->edmaConfig;
        regionId                      = hEdmaInit.regionId;
        maxChannel                    = hEdmaInit.ownResource.maxChannel;
        intrLow                       = CDD_EDMA_lld_getIntrStatusRegion(baseAddr, regionId);
        intrHigh                      = CDD_EDMA_lld_intrStatusHighGetRegion(baseAddr, regionId);
        tccNum                        = Cdd_Dma_TccHandlerMapping[i];
        if (maxChannel == 1U)
        {
            if ((tccNum < 32U) && ((intrLow & (1U << tccNum)) != 0U))
            {
                CDD_EDMA_lld_clrIntrRegion(baseAddr, regionId, tccNum);
                intrLow &= ~(1U << tccNum);
                Cdd_Dma_CallBackList[tccNum](Cdd_Dma_AppDataList[tccNum]);
            }
            if ((tccNum >= 32U) && ((intrHigh & (1U << (tccNum - 32U))) != 0U))
            {
                CDD_EDMA_lld_clrIntrRegion(baseAddr, regionId, tccNum);
                intrHigh &= ~(1U << (tccNum - 32U));
                Cdd_Dma_CallBackList[tccNum](Cdd_Dma_AppDataList[tccNum]);
            }
        }
        if (maxChannel > 1U)
        {
            tccNum = Cdd_Dma_ChainingTcc[i][maxChannel - 1U];

            if ((tccNum < 32U) && ((intrLow & (1U << tccNum)) != 0U))
            {
                CDD_EDMA_lld_clrIntrRegion(baseAddr, regionId, tccNum);
                intrLow &= ~(1U << tccNum);
                Cdd_Dma_CallBackList[tccNum](Cdd_Dma_AppDataList[tccNum]);
            }
            if ((tccNum >= 32U) && ((intrHigh & (1U << (tccNum - 32U))) != 0U))
            {
                CDD_EDMA_lld_clrIntrRegion(baseAddr, regionId, tccNum);
                intrHigh &= ~(1U << (tccNum - 32U));
                Cdd_Dma_CallBackList[tccNum](Cdd_Dma_AppDataList[tccNum]);
            }
        }
        Mcal_Libs_Utils_unlockMMR();
        /* Clear the aggregator interrupt */
        HW_WR_REG32(hEdmaInit.intrAggStatusAddr, hEdmaInit.intrAggClearMask);
        /* re evaluate the edma interrupt. */
        HW_WR_FIELD32(baseAddr + CDD_EDMA_TPCC_IEVAL_RN(regionId), CDD_EDMA_TPCC_IEVAL_RN_EVAL, 1);
        Mcal_Libs_Utils_lockMMR();
    }
}
void Cdd_Dma_ReadBack(Cdd_Dma_RegisterReadbackType *RegRbPtr, uint32 baseAddr)
{
    (void)memset(RegRbPtr, 0, sizeof(Cdd_Dma_RegisterReadbackType));
    RegRbPtr->revisionId = HW_RD_REG32(baseAddr + CDD_EDMA_TPCC_PID);
}

#define CDD_DMA_STOP_SEC_ISR_CODE
#include "Cdd_Dma_MemMap.h"
/*********************************************************************************************************************
 *  End of File: Cdd_Dma_Priv.c
 *********************************************************************************************************************/
