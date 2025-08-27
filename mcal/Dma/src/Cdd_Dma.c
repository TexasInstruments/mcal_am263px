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
 *  \file   CDD_Dma.c
 *
 *  \brief  This file contains device abstraction layer APIs for the DMA device.
 *          There are APIs here to enable the DMA instance, set the required
 *          configurations for communication, transmit or receive data.
 */

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/
#include "Cdd_Dma_Cfg.h"
#include "hw_types.h"
#include "Cdd_Dma.h"
#include "stddef.h"
#include "SchM_Cdd_Dma.h"

/* ========================================================================== */
/*                        Local Type Declaration                         */
/* ========================================================================== */
#define CDD_DMA_START_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"
uint8          Cdd_Dma_Reg_Callback[CDD_DMA_MAX_HANDLER]       = {0};
volatile uint8 Cdd_Dma_handleAlreadyInUse[CDD_DMA_MAX_HANDLER] = {0};
#define CDD_DMA_STOP_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"

/*********************************************************************************************************************
 * Local Object Definitions
 *********************************************************************************************************************/
#define CDD_DMA_START_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Dma_MemMap.h"
Cdd_Dma_ConfigType *Cdd_Dma_HandlerList = (Cdd_Dma_ConfigType *)NULL_PTR;
#define CDD_DMA_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Dma_MemMap.h"

#define CDD_DMA_START_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"
/* Global Init Done flag */
static boolean Cdd_Dma_InitDone = FALSE;
#define CDD_DMA_STOP_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"

#define CDD_DMA_START_SEC_VAR_INIT_32
#include "Cdd_Dma_MemMap.h"
uint32 Cdd_Dma_ChainingTcc[CDD_EDMA_NUM_DMACH][CDD_EDMA_NUM_DMACH] = {{0}};
#define CDD_DMA_STOP_SEC_VAR_INIT_32
#include "Cdd_Dma_MemMap.h"

static void           Cdd_Dma_ParamSet_ConfigValues(uint32 handleId, uint32 channelIdx, uint32 paramIndex,
                                                    Cdd_Dma_ParamEntry paramEntry);
static Std_ReturnType Cdd_Edma_lld_intrRegister(uint32 handleId, void *appdata, Cdd_Edma_EventCallback callback);
static boolean        Cdd_Edma_lld_transferRegion(uint32 handleId, uint32 trigMode);
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
static boolean Cdd_Dma_GetParamDetCheck(uint32 handleId, uint32 channelIdx, uint32 paramIndex);
static boolean Cdd_Dma_GetParam_detErrorCheck(uint32 handleId, uint32 channelIdx, uint32 paramIndex);
static boolean Cdd_Dma_ParamSet_MaxparamDetcheck(uint32 maxParamCheck, uint32 paramIndex);
static boolean Cdd_Dma_ChainChannel_paramDetCheck(uint32 channelIdx0, uint32 channelIdx1, uint32 maxChannelCheck,
                                                  Cdd_Dma_InitHandleType hEdmaInitCheck, uint32 paramIndex0);
#endif

#define CDD_DMA_START_SEC_CODE
#include "Cdd_Dma_MemMap.h"
/*********************************************************************************************************************
 *  External Functions Definition
 *********************************************************************************************************************/
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
static inline void Cdd_Dma_ReportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(CDD_DMA_MODULE_ID, CDD_DMA_INSTANCE_ID, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == CDD_DMA_DEV_ERROR_DETECT) */

/*
 *Design:MCAL-19816,MCAL-19817,MCAL-19818,MCAL-19819,MCAL-19638,MCAL-19627,MCAL-18914,MCAL-18915,MCAL-18916,MCAL-18917,MCAL-18918,MCAL-18919,MCAL-18921,MCAL-18922,MCAL-18923,MCAL-18924,MCAL-18925,MCAL-18926,MCAL-18928
 *
 */
/* Initializes the DMA module. */
void Cdd_Dma_Init(Cdd_Dma_ConfigType *ConfigPtr)
{
    Cdd_Dma_ConfigType *CfgPtr = ConfigPtr;

/* Initialize the Pointer. */
#if (STD_ON == CDD_DMA_PRE_COMPILE_VARIANT)
    if (NULL_PTR == CfgPtr)
    {
        CfgPtr = (Cdd_Dma_ConfigType *)&CddDmaDriverHandler;
    }
#endif

    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_HandlerList = CfgPtr;
        Cdd_Dma_TrigXbar();
        Cdd_Dma_Xbar();
        CDD_EDMA_lld_init(Cdd_Dma_HandlerList);
        Cdd_Dma_InitDone = TRUE;
    }
    else
    {
/* Report DET */
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
        Cdd_Dma_ReportDetError(CDD_DMA_INIT_SERVICE_ID, CDD_DMA_E_ALREADY_INITIALIZED);
#endif
    }

    return;
}

/*
 *Design: MCAL-22685
 */
/* Provides the DMA Initialization status. */
boolean Cdd_Dma_GetInitStatus(void)
{
    return Cdd_Dma_InitDone;
}
/*
 *Design:MCAL-19820,MCAL-19821,MCAL-19822,MCAL-19693,MCAL-18929,MCAL-18931
 */

/* De-Initializes the DMA module. */
#if (STD_ON == CDD_DMA_DEINIT_API)
void Cdd_Dma_DeInit(void)
{
    if (TRUE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_InitDone = FALSE;
        CDD_EDMA_lld_deInit(Cdd_Dma_HandlerList);
        for (uint32 i = 0; i < (uint32)CDD_DMA_MAX_HANDLER; i++)
        {
            Cdd_Dma_Reg_Callback[i] = 0;
        }
    }
    else
    {
/* Report DET */
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
        Cdd_Dma_ReportDetError(CDD_DMA_DEINIT_SERVICE_ID, CDD_DMA_E_UNINIT);
#endif
    }

    return;
}
#endif

/*
 *Design:MCAL-19824,MCAL-19823,MCAL-19825,MCAL-19619,MCAL-18933,MCAL-18944,MCAL-22652,
 */
uint32 Cdd_Dma_CbkRegister(uint32 handleId, void *appdata, Cdd_Edma_EventCallback callback)
{
    Std_ReturnType status = E_NOT_OK;
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_CBKREGISTER_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_CBKREGISTER_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else if (Cdd_Dma_Reg_Callback[handleId] != 0U)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_CBKREGISTER_SERVICE_ID, CDD_DMA_E_ALREADY_REGISTERED);
    }
    else
#endif
    {
        status = Cdd_Edma_lld_intrRegister(handleId, appdata, callback);
    }
    return (uint32)status;
}

/*
 *Design:MCAL-19826,MCAL-19827,MCAL-19828,MCAL-19829,MCAL-22651,MCAL-18934,MCAL-18935,MCAL-18936,MCAL-18937
 */
void Cdd_Dma_ParamSet(uint32 handleId, uint32 channelIdx, uint32 paramIndex, Cdd_Dma_ParamEntry paramEntry)
{
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    boolean                exitCondition = FALSE;
    Cdd_Dma_Handler       *hEdmaCheck    = (Cdd_Dma_Handler *)NULL_PTR;
    Cdd_Dma_InitHandleType hEdmaInitCheck;
    uint32                 maxChannelCheck, maxParamCheck = 0U;
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_PARAMSET_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_PARAMSET_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
    {
        hEdmaCheck      = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInitCheck  = hEdmaCheck->edmaConfig;
        maxChannelCheck = hEdmaInitCheck.ownResource.maxChannel;
        if (maxChannelCheck <= channelIdx)
        {
            Cdd_Dma_ReportDetError(CDD_DMA_PARAMSET_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
        }
        else
        {
            maxParamCheck = hEdmaInitCheck.ownResource.channelGroup[channelIdx]->maxParam;
            exitCondition = Cdd_Dma_ParamSet_MaxparamDetcheck(maxParamCheck, paramIndex);
        }
    }
    if (exitCondition == TRUE)
#endif
    {
        if (Cdd_Dma_handleAlreadyInUse[handleId] != 0U)
        {
            Det_ReportRuntimeError(CDD_DMA_MODULE_ID, CDD_DMA_INSTANCE_ID, CDD_DMA_PARAMSET_SERVICE_ID,
                                   CDD_DMA_E_ALREADY_IN_PROGRESS);
        }
        else
        {
            Cdd_Dma_ParamSet_ConfigValues(handleId, channelIdx, paramIndex, paramEntry);
        }
    }
}

/*
 *Design:MCAL-19830,MCAL-19831,MCAL-19832,MCAL-19700,MCAL-18938,MCAL-22650
 */
void Cdd_Dma_LinkChannel(uint32 handleId, uint32 paramIndex0, uint32 paramIndex1)
{
    uint32                 channelIdx = 0;
    uint32                 baseAddr, param0, param1 = 0U;
    Cdd_Dma_InitHandleType hEdmaInit;
    Cdd_Dma_Handler       *hEdma;

#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    boolean                exitCondition = FALSE;
    Cdd_Dma_Handler       *hEdmaCheck;
    Cdd_Dma_InitHandleType hEdmaInitCheck;
    uint32                 maxParamCheck = 0U;
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_LINKCHANNEL_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_LINKCHANNEL_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
    {
        hEdmaCheck     = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInitCheck = hEdmaCheck->edmaConfig;
        maxParamCheck  = hEdmaInitCheck.ownResource.channelGroup[channelIdx]->maxParam;
        if ((maxParamCheck <= paramIndex0) || (maxParamCheck <= paramIndex1))
        {
            Cdd_Dma_ReportDetError(CDD_DMA_LINKCHANNEL_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
        }
        else
        {
            exitCondition = TRUE;
        }
    }
    if (exitCondition == TRUE)
#endif
    {
        hEdma     = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInit = hEdma->edmaConfig;
        baseAddr  = hEdma->baseAddr;
        param0    = hEdmaInit.ownResource.channelGroup[channelIdx]->paramGroup[paramIndex0]->paramId;
        param1    = hEdmaInit.ownResource.channelGroup[channelIdx]->paramGroup[paramIndex1]->paramId;
        CDD_EDMA_lld_linkChannel(baseAddr, param0, param1);
    }
}

/*
 *Design:MCAL-19833,MCAL-19835,MCAL-19836,MCAL-19838,MCAL-18939,MCAL-22649
 */
void Cdd_Dma_ChainChannel(uint32 handleId, uint32 channelIdx0, uint32 paramIndex0, uint32 channelIdx1, uint32 opt)
{
    Cdd_Dma_InitHandleType hEdmaInit;
    uint32                 baseAddr, channel1, param0 = 0U;
    Cdd_Dma_Handler       *hEdma;

#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    boolean                exitCondition = FALSE;
    Cdd_Dma_Handler       *hEdmaCheck;
    Cdd_Dma_InitHandleType hEdmaInitCheck;
    uint32                 maxChannelCheck = 0U;
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_CHAINCHANNEL_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_CHAINCHANNEL_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
    {
        hEdmaCheck      = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInitCheck  = hEdmaCheck->edmaConfig;
        maxChannelCheck = hEdmaInitCheck.ownResource.maxChannel;
        exitCondition =
            Cdd_Dma_ChainChannel_paramDetCheck(channelIdx0, channelIdx1, maxChannelCheck, hEdmaInitCheck, paramIndex0);
    }
    if (exitCondition == TRUE)
#endif
    {
        hEdma     = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInit = hEdma->edmaConfig;
        baseAddr  = hEdma->baseAddr;
        channel1  = hEdmaInit.ownResource.channelGroup[channelIdx1]->channelId;
        param0    = hEdmaInit.ownResource.channelGroup[channelIdx0]->paramGroup[paramIndex0]->paramId;
        CDD_EDMA_lld_chainChannel(baseAddr, param0, channel1, opt);
    }
}

/*
 *Design:MCAL-19839,MCAL-19893,MCAL-19894,MCAL-19878,MCAL-19634,MCAL-18943,MCAL-22648
 */
boolean Cdd_Dma_EnableTransferRegion(uint32 handleId, uint32 trigMode)
{
    boolean retval = FALSE;
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_ENABLETRANSFERREGION_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_ENABLETRANSFERREGION_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
#endif
    {
        retval = Cdd_Edma_lld_transferRegion(handleId, trigMode);
    }
    return retval;
}

/*
 *Design:MCAL-21483, MCAL-19895,MCAL-19896,MCAL-19647,MCAL-19644,MCAL-22647
 */
/* used in case of polling mode */
boolean Cdd_Dma_GetStatus(uint32 handleId)
{
    boolean                retval = FALSE;
    Cdd_Dma_Handler       *hEdma;
    Cdd_Dma_InitHandleType hEdmaInit;
    uint32                 baseAddr, region, tcc, maxChannel = 0U;
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_GETSTATUS_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_GETSTATUS_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
#endif
    {
        hEdma      = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInit  = hEdma->edmaConfig;
        baseAddr   = hEdma->baseAddr;
        region     = hEdmaInit.regionId;
        tcc        = hEdmaInit.tcc;
        maxChannel = hEdmaInit.ownResource.maxChannel;
        /* When multiple channels are used in case of chaining we will check for the last channel
         * involve in the chain */
        if (maxChannel > 1U)
        {
            tcc = Cdd_Dma_ChainingTcc[handleId][maxChannel - 1U];
        }
        retval = (boolean)CDD_EDMA_lld_readIntrStatusRegion(baseAddr, region, tcc);
        if (retval == TRUE)
        {
            Cdd_Dma_handleAlreadyInUse[handleId] = 0;
            CDD_EDMA_lld_clrIntrRegion(baseAddr, region, tcc);
        }
    }
    return retval;
}

/*
 *Design:MCAL-19897,MCAL-19898,MCAL-19692
 */
#if (STD_ON == CDD_DMA_VERSION_INFO_API)

void Cdd_Dma_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr)
{
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_GETVERSIONINFO_SERVICE_ID, CDD_DMA_E_PARAM_POINTER);
    }
    else
#endif
    {
        VersionInfoPtr->vendorID         = CDD_DMA_VENDOR_ID;
        VersionInfoPtr->moduleID         = CDD_DMA_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)CDD_DMA_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)CDD_DMA_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)CDD_DMA_SW_PATCH_VERSION;
    }

    return;
}
#endif /* CDD_DMA_GET_VERSION_INFO_API*/

/*
 *Design:MCAL-21480,MCAL-21482,MCAL-21485,MCAL-22641
 */
void Cdd_Dma_GetParam(uint32 handleId, uint32 channelIdx, uint32 paramIndex, CDD_EDMACCEDMACCPaRAMEntry *edmaParam)
{
    Cdd_Dma_InitHandleType hEdmaInit;
    uint32                 baseAddr, param = 0U;
    Cdd_Dma_Handler       *hEdma;

#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    boolean exitCondition = FALSE;
    exitCondition         = Cdd_Dma_GetParamDetCheck(handleId, channelIdx, paramIndex);
    if (exitCondition == TRUE)
#endif
    {
        hEdma     = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInit = hEdma->edmaConfig;
        baseAddr  = hEdma->baseAddr;
        param     = hEdmaInit.ownResource.channelGroup[channelIdx]->paramGroup[paramIndex]->paramId;
        CDD_EDMA_lld_getPaRAM(baseAddr, param, edmaParam);
    }
}

/*
 *Design:MCAL-21487,MCAL-21488,MCAL-19633,MCAL-22644,MCAL-22646
 */
boolean Cdd_Dma_DisableTransferRegion(uint32 handleId, uint32 trigMode)
{
    boolean                retval = FALSE;
    Cdd_Dma_Handler       *hEdma;
    Cdd_Dma_InitHandleType hEdmaInit;
    uint32                 baseAddr, region, channel = 0U;
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_DISABLETRANSFERREGION_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_DISABLETRANSFERREGION_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
#endif
    {
        hEdma     = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInit = hEdma->edmaConfig;
        baseAddr  = hEdma->baseAddr;
        region    = hEdmaInit.regionId;
        channel   = hEdmaInit.ownResource.channelGroup[0]->channelId;
        retval    = (boolean)CDD_EDMA_lld_disableTransferRegion(baseAddr, region, channel, trigMode);
        if (retval == TRUE)
        {
            Cdd_Dma_handleAlreadyInUse[handleId] = 0;
        }
    }
    return retval;
}
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
static boolean Cdd_Dma_ParamSet_MaxparamDetcheck(uint32 maxParamCheck, uint32 paramIndex)
{
    boolean exitCondition = FALSE;

    if (maxParamCheck <= paramIndex)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_PARAMSET_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
    {
        exitCondition = TRUE;
    }
    return exitCondition;
}
#endif

static void Cdd_Dma_ParamSet_ConfigValues(uint32 handleId, uint32 channelIdx, uint32 paramIndex,
                                          Cdd_Dma_ParamEntry paramEntry)
{
    Cdd_Dma_InitHandleType     hEdmaInit;
    uint32                     baseAddr, tcc, param = 0U;
    CDD_EDMACCEDMACCPaRAMEntry edmaParam;
    Cdd_Dma_Handler           *hEdma;

    hEdma     = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
    hEdmaInit = hEdma->edmaConfig;
    baseAddr  = hEdma->baseAddr;
    tcc       = hEdmaInit.tcc;
    param     = hEdmaInit.ownResource.channelGroup[channelIdx]->paramGroup[paramIndex]->paramId;
    /* Initialize TX Param Set */
    CDD_EDMA_lld_ccParamEntry_Init(&edmaParam);

    /* Transmit param set configuration */
    edmaParam.srcAddr    = (uint32)Cdd_Dma_Soc_VirtToPhy(paramEntry.srcPtr);
    edmaParam.destAddr   = (uint32)Cdd_Dma_Soc_VirtToPhy(paramEntry.destPtr);
    edmaParam.aCnt       = (uint16)paramEntry.aCnt;
    edmaParam.bCnt       = (uint16)paramEntry.bCnt;
    edmaParam.cCnt       = (uint16)paramEntry.cCnt;
    edmaParam.bCntReload = (uint16)paramEntry.bCntReload;
    edmaParam.srcBIdx    = paramEntry.srcBIdx;
    edmaParam.destBIdx   = paramEntry.destBIdx;
    edmaParam.srcCIdx    = paramEntry.srcCIdx;
    edmaParam.destCIdx   = paramEntry.destCIdx;
    edmaParam.linkAddr   = 0xFFFFU;
    edmaParam.opt        = paramEntry.opt;
    if ((channelIdx == 0U) && (paramIndex == 0U))
    {
        edmaParam.opt |= ((tcc << CDD_EDMA_OPT_TCC_SHIFT) & CDD_EDMA_OPT_TCC_MASK);
    }
    else if (channelIdx > 0U)
    {
        tcc            = Cdd_Dma_ChainingTcc[handleId][channelIdx];
        edmaParam.opt |= ((tcc << CDD_EDMA_OPT_TCC_SHIFT) & CDD_EDMA_OPT_TCC_MASK);
    }
    else
    {
        /*Do Nothing*/
    }
    CDD_EDMA_lld_setPaRAM(baseAddr, param, &edmaParam);
}

#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
static boolean Cdd_Dma_ChainChannel_paramDetCheck(uint32 channelIdx0, uint32 channelIdx1, uint32 maxChannelCheck,
                                                  Cdd_Dma_InitHandleType hEdmaInitCheck, uint32 paramIndex0)
{
    uint32  maxParamCheck;
    boolean status = FALSE;
    if ((maxChannelCheck <= channelIdx0) || (maxChannelCheck <= channelIdx1))
    {
        Cdd_Dma_ReportDetError(CDD_DMA_CHAINCHANNEL_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
    {
        maxParamCheck = hEdmaInitCheck.ownResource.channelGroup[channelIdx0]->maxParam;
        if (maxParamCheck <= paramIndex0)
        {
            Cdd_Dma_ReportDetError(CDD_DMA_CHAINCHANNEL_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
        }
        else
        {
            status = TRUE;
        }
    }
    return status;
}
#endif

static Std_ReturnType Cdd_Edma_lld_intrRegister(uint32 handleId, void *appdata, Cdd_Edma_EventCallback callback)
{
    Std_ReturnType   retVal = E_NOT_OK;
    Cdd_Dma_Handler *hEdma;
    hEdma  = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
    retVal = CDD_EDMA_lld_registerIntr(hEdma, appdata, callback, handleId);
    if (retVal == E_OK)
    {
        Cdd_Dma_Reg_Callback[handleId] = 1;
    }
    return retVal;
}

static boolean Cdd_Edma_lld_transferRegion(uint32 handleId, uint32 trigMode)
{
    Cdd_Dma_Handler       *hEdma;
    Cdd_Dma_InitHandleType hEdmaInit;
    uint32                 baseAddr, region, channel;
    boolean                exitCondition = FALSE;
    if (Cdd_Dma_handleAlreadyInUse[handleId] != 0U)
    {
        Det_ReportRuntimeError(CDD_DMA_MODULE_ID, CDD_DMA_INSTANCE_ID, CDD_DMA_ENABLETRANSFERREGION_SERVICE_ID,
                               CDD_DMA_E_ALREADY_IN_PROGRESS);
    }
    else
    {
        hEdma                                = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        hEdmaInit                            = hEdma->edmaConfig;
        baseAddr                             = hEdma->baseAddr;
        region                               = hEdmaInit.regionId;
        channel                              = hEdmaInit.ownResource.channelGroup[0]->channelId;
        Cdd_Dma_handleAlreadyInUse[handleId] = 1;
        exitCondition = (boolean)CDD_EDMA_lld_enableTransferRegion(baseAddr, region, channel, trigMode);
        if (exitCondition == FALSE)
        {
            Cdd_Dma_handleAlreadyInUse[handleId] = 0;
        }
    }
    return exitCondition;
}

#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
static boolean Cdd_Dma_GetParamDetCheck(uint32 handleId, uint32 channelIdx, uint32 paramIndex)
{
    boolean retVal = FALSE;
    if (FALSE == Cdd_Dma_InitDone)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_GETPARAM_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if (handleId >= (uint32)CDD_DMA_MAX_HANDLER)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_GETPARAM_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
    {
        retVal = Cdd_Dma_GetParam_detErrorCheck(handleId, channelIdx, paramIndex);
    }
    return retVal;
}

static boolean Cdd_Dma_GetParam_detErrorCheck(uint32 handleId, uint32 channelIdx, uint32 paramIndex)
{
    boolean                status = FALSE;
    Cdd_Dma_Handler       *hEdmaCheck;
    Cdd_Dma_InitHandleType hEdmaInitCheck;
    uint32                 maxChannelCheck, maxParamCheck;
    hEdmaCheck      = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
    hEdmaInitCheck  = hEdmaCheck->edmaConfig;
    maxChannelCheck = hEdmaInitCheck.ownResource.maxChannel;
    if (maxChannelCheck <= channelIdx)
    {
        Cdd_Dma_ReportDetError(CDD_DMA_GETPARAM_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
    {
        maxParamCheck = hEdmaInitCheck.ownResource.channelGroup[channelIdx]->maxParam;
        if (maxParamCheck <= paramIndex)
        {
            Cdd_Dma_ReportDetError(CDD_DMA_GETPARAM_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
        }
        else
        {
            status = TRUE;
        }
    }
    return status;
}
#endif

#if (STD_ON == CDD_DMA_REGISTER_READBACK_API)
/*
 *Design:MCAL-23362,MCAL-23368
 */
Std_ReturnType Cdd_Dma_RegisterReadback(uint32 handleId, Cdd_Dma_RegisterReadbackType *RegPtr)
{
    Cdd_Dma_Handler *hEdma;
    Std_ReturnType   retVal = ((Std_ReturnType)E_OK);
    uint32           baseAddr;
#if (STD_ON == CDD_DMA_DEV_ERROR_DETECT)
    if (FALSE == Cdd_Dma_InitDone)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_Dma_ReportDetError(CDD_DMA_REGISTER_READBACK_SERVICE_ID, CDD_DMA_E_UNINIT);
    }
    else if ((handleId >= CDD_DMA_MAX_HANDLER) || (RegPtr == NULL_PTR))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_Dma_ReportDetError(CDD_DMA_REGISTER_READBACK_SERVICE_ID, CDD_DMA_E_PARAM_VALUE);
    }
    else
#endif
    {
        hEdma    = Cdd_Dma_HandlerList->CddDmaDriverHandler[handleId];
        baseAddr = hEdma->baseAddr;
        Cdd_Dma_ReadBack(RegPtr, baseAddr);
    }
    return (retVal);
}
#endif

#define CDD_DMA_STOP_SEC_CODE
#include "Cdd_Dma_MemMap.h"
/*********************************************************************************************************************
 *  End of File: Cdd_Dma.c
 *********************************************************************************************************************/
