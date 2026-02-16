/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     CDD_FSI_RX_Priv.c
 *
 *  \brief    This file contains CDD_FSI_RX MCAL driver internal functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_FsiRx_Cfg.h"
#include "Cdd_FsiRx.h"
#include "Cdd_FsiRx_Priv.h"
#include "Cdd_FsiRx_Irq.h"
#if (CDD_FSI_RX_DMA_ENABLE == STD_ON)
#include "Cdd_Dma.h"
#endif
#include "Os.h"

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static FUNC(void, CDD_FSIRX_CODE) CddFsiRx_delayWait(uint32 delay);

#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)
static void           CddFsiRx_IrqDmaRx(void *hwUnitObj);
static Std_ReturnType CddFsiRxDma_ModuleChannelConfigure(Cdd_FsiRx_HwUnitObjType           *hwUnitObj,
                                                         volatile Cdd_FsiRx_DataBufferType *buffrPtr, uint16 table_size,
                                                         uint16 *rx_databuffer, uint8 bCnt, uint8 cCnt, uint32 mode);
#endif /* #if (STD_ON == CDD_FSI_RX_DMA_ENABLE) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define CDD_FSIRX_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiRx_MemMap.h"
VAR(CddFsiRx_DriverObjType, CDD_FSIRX_VAR_CLEARED) Cdd_FsiRx_DrvObj;
#define CDD_FSIRX_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiRx_MemMap.h"

#define CDD_FSIRX_START_SEC_VAR_INIT_16
#include "Cdd_FsiRx_MemMap.h"
/** \brief variable to store Tag and user data */
VAR(uint16, CDD_FSIRX_VAR_CLEARED) Cdd_FsiRx_TagAndUserData = 0U;
#define CDD_FSIRX_STOP_SEC_VAR_INIT_16
#include "Cdd_FsiRx_MemMap.h"

#define CDD_FSIRX_START_SEC_VAR_NO_INIT_16
#include "Cdd_FsiRx_MemMap.h"
/** \brief variable to store Ping Tag RECEIVED */
volatile VAR(uint16, CDD_FSIRX_VAR_CLEARED) Cdd_FsiRx_PingTag;
#define CDD_FSIRX_STOP_SEC_VAR_NO_INIT_16
#include "Cdd_FsiRx_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_FSIRX_START_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"

/*
 * Design:
 */
void CddFsiRx_hwUnitInit(const Cdd_FsiRx_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr;
    /* Assign base address */
    baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    CddFsiRx_resetRxModule(baseAddr);
    CddFsiRx_clearRxModuleReset(baseAddr);
    CddFsiRx_delayWait(10U);

    {
        (void)CddFsiRx_setRxDataWidth(baseAddr, CDD_FSI_RX_SINGLE_DATA_LANE);
    }
#if (STD_OFF == CDD_FSI_RX_MAIN_FUNCTION_API)
    if (hwUnitObj->hwUnitCfg.receptionMode == CDD_FSI_RX_INTERRUPT_MODE)
    {
        (void)CddFsiRx_disableInterrupt(baseAddr, (uint8)CDD_FSI_RX_INT_TYPE);
        (void)CddFsiRx_clearAllRxEvents(baseAddr);
    }
#endif
    /* Set the rx buffer pointer to initial index to receive data from first position*/
    CddFsiRx_ForceRxBufferPtr(baseAddr, 0U);
    CddFsiRx_enableRxPingWatchdogTimer(baseAddr, hwUnitObj->hwUnitCfg.pingWdgTriggerTimeout);
    CddFsiRx_delayWait(10U);
    CddFsiRx_enableRxFrameWatchdogTimer(baseAddr, hwUnitObj->hwUnitCfg.frameWdgTriggerTimeout);
    CddFsiRx_delayWait(10U);
#if (STD_OFF == CDD_FSI_RX_MAIN_FUNCTION_API)
    if (hwUnitObj->hwUnitCfg.receptionMode == CDD_FSI_RX_INTERRUPT_MODE)
    {
        (void)CddFsiRx_enableInterrupt(baseAddr, (uint8)CDD_FSI_RX_INT_TYPE);
    }
#endif

    return;
}
/********************************************************************************************************/
/*
 * Design:
 */
Std_ReturnType CddFsiRx_hwUnitDeInit(const Cdd_FsiRx_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr;
    uint8  retVal = E_OK;
    baseAddr      = hwUnitObj->hwUnitCfg.baseAddr;
    CddFsiRx_disableRxPingWatchdogTimer(baseAddr);
    CddFsiRx_disableRxFrameWatchdogTimer(baseAddr);
    retVal = CddFsiRx_clearAllRxEvents(baseAddr);
#if (STD_OFF == CDD_FSI_RX_MAIN_FUNCTION_API)
    if (hwUnitObj->hwUnitCfg.receptionMode == CDD_FSI_RX_INTERRUPT_MODE)
    {
        CddFsiRx_disableInterrupt(baseAddr, (uint8)CDD_FSI_RX_INT_TYPE);
    }
#endif
#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)
    CddFsiRx_disableRxDMAEvent(baseAddr);
#endif
    return retVal;
}
/*****************************************************************************************************/
/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
void CddFsiRx_copyConfig(CddFsiRx_DriverObjType *drvObj, const Cdd_FsiRx_ConfigType *cfgPtr)
{
    uint8                            hwUnitId;
    const CddFsiRx_HwUnitConfigType *hwCfg;
    Cdd_FsiRx_HwUnitObjType         *hwObj;

    drvObj->maxHwUnit                                = cfgPtr->maxHwUnit;
    drvObj->CddFsiRxResetNotificationPtr             = cfgPtr->cddFsiRxResetNotification;
    drvObj->CddFsiRxOverRunNotificationPtr           = cfgPtr->cddFsiRxOverRunNotification;
    drvObj->CddFsiRxUnderRunNotificationPtr          = cfgPtr->cddFsiRxUnderRunNotification;
    drvObj->CddFsiRxPingFrameReceivedNotificationPtr = cfgPtr->cddFsiRxPingFrameReceivedNotification;
    drvObj->CddFsiRxDataFrameReceivedNotificationPtr = cfgPtr->cddFsiRxDataFrameReceivedNotification;
#if (CDD_FSI_RX_DMA_ENABLE == STD_ON)
    drvObj->CddFsiRxDmaNotificationPtr = cfgPtr->cddFsiRxDmaNotification;

#endif

    for (hwUnitId = 0U; hwUnitId < cfgPtr->maxHwUnit; hwUnitId++)
    {
        hwCfg = &cfgPtr->hwUnitCfg[hwUnitId];
        /* Copy configuration */
        (void)memcpy(&drvObj->hwUnitObj[hwUnitId].hwUnitCfg, hwCfg, sizeof(CddFsiRx_HwUnitConfigType));
        hwObj                     = &drvObj->hwUnitObj[hwUnitId];
        hwObj->hwUnitCfg.baseAddr = hwCfg->baseAddr;
#if (CDD_FSI_RX_DMA_ENABLE == STD_ON)
        Cdd_Dma_CbkRegister(hwObj->hwUnitCfg.edmaRxInstance, (void *)hwObj, &CddFsiRx_IrqDmaRx);
#endif
    }
    return;
}
/********************************************************************************************************/
/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
void CddFsiRx_Receive(Cdd_FsiRx_HwUnitObjType *hwUnitObj)
{
    /* Assign base address */

    if (CDD_FSI_RX_DMA_MODE == hwUnitObj->hwUnitCfg.receptionMode)
    {
#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)

        CddFsiRx_DMAdataReceive(hwUnitObj);
#endif
    }
#if (STD_OFF == CDD_FSI_RX_DMA_ENABLE)
    uint32 baseAddr;
    baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    if (CDD_FSI_RX_POLLING_MODE == hwUnitObj->hwUnitCfg.receptionMode)
    {
        uint16 eventStatus = (HW_RD_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1));
        if ((eventStatus & CDD_FSI_RX_DATA_FRAME_RECEIVED_MASK) != 0U)
        {
            CddFsiRx_dataReceive(hwUnitObj->hwUnitCfg.hwId, baseAddr, hwUnitObj->rxBuffer, hwUnitObj->rxDataWidth,
                                 CDD_FSI_RX_BUFF_OFFSET);
        }
    }
    if (CDD_FSI_RX_INTERRUPT_MODE == hwUnitObj->hwUnitCfg.receptionMode)
    {
        CddFsiRx_dataReceive(hwUnitObj->hwUnitCfg.hwId, baseAddr, hwUnitObj->rxBuffer, hwUnitObj->rxDataWidth,
                             CDD_FSI_RX_BUFF_OFFSET);
    }
#endif
    return;
}

/*********************************************************************************************************/
/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */

void CddFsiRx_IrqRx(Cdd_FsiRx_HwUnitObjType *hwUnitObj, uint16 flag)
{
    uint32 baseAddr;
    baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    if (((flag & CDD_FSI_RX_DATA_FRAME_RECEIVED_MASK) >> CDD_FSI_RX_DATA_FRAME_RECEIVED_SHIFT) == 1U)
    {
        CddFsiRx_Receive(hwUnitObj);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_DATA_FRAME_RECEIVED);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_FRAME_DONE);
    }
    if (((flag & CDD_FSI_RX_PING_FRAME_RECEIVED_MASK) >> CDD_FSI_RX_PING_FRAME_RECEIVED_SHIFT) == 1U)
    {
        Cdd_FsiRx_PingTag = CddFsiRx_getRxPingTag(baseAddr);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_PING_FRAME_RECEIVED);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_FRAME_DONE);
    }
    if (((flag & CDD_FSI_RX_BUFFER_UNDERRUN_MASK) >> CDD_FSI_RX_BUFFER_UNDERRUN_SHIFT) == 1U)
    {
/*call DEM Error*/
#ifdef CDD_FSI_RX_E_BUFFER_UNDERRUN_ERROR
        (void)Dem_SetEventStatus(CDD_FSI_RX_E_BUFFER_UNDERRUN_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        Cdd_FsiRx_DrvObj.CddFsiRxUnderRunNotificationPtr(hwUnitObj->hwUnitCfg.hwUnitId);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_BUFFER_UNDERRUN);
    }
    if (((flag & CDD_FSI_RX_BUFFER_OVERRUN_MASK) >> CDD_FSI_RX_BUFFER_OVERRUN_SHIFT) == 1U)
    {
/*call DEM Error*/
#ifdef CDD_FSI_RX_E_BUFFER_OVERRUN_ERROR
        (void)Dem_SetEventStatus(CDD_FSI_RX_E_BUFFER_OVERRUN_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        Cdd_FsiRx_DrvObj.CddFsiRxOverRunNotificationPtr(hwUnitObj->hwUnitCfg.hwUnitId);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_BUFFER_OVERRUN);
    }
    if (((flag & CDD_FSI_RX_FRAME_WDG_TIMEOUT_MASK) >> CDD_FSI_RX_FRAME_WDG_TIMEOUT_SHIFT) == 1U)
    {
        /*Call back Notification to Application to reset and reinitialize the drivers which is a
        must under this situation.*/
        Cdd_FsiRx_DrvObj.CddFsiRxResetNotificationPtr(hwUnitObj->hwUnitCfg.hwUnitId);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_FRAME_WDG_TIMEOUT);
    }
    if (((flag & CDD_FSI_RX_PING_WDG_TIMEOUT_MASK) >> CDD_FSI_RX_PING_WDG_TIMEOUT_SHIFT) == 1U)
    {
        /*Call back Notification to Application to reset and reinitialize the drivers.*/
        Cdd_FsiRx_DrvObj.CddFsiRxResetNotificationPtr(hwUnitObj->hwUnitCfg.hwUnitId);
        CddFsiRx_clearPingWdgEvent(baseAddr, CDD_FSI_RX_PING_WDG_TIMEOUT);
    }
    if (((flag & CDD_FSI_RX_CRC_ERROR_MASK) >> CDD_FSI_RX_CRC_ERROR_SHIFT) == 1U)
    {
        /*Call back Notification to Application to reset and reinitialize the drivers.*/
        Cdd_FsiRx_DrvObj.CddFsiRxResetNotificationPtr(hwUnitObj->hwUnitCfg.hwUnitId);
        CddFsiRx_clearRxEvents(baseAddr, CDD_FSI_RX_CRC_ERROR);
    }
}
/*********************************************************************************************************/
/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
void CddFsiRx_ReportDetError(uint8 moduleId, uint8 instanceId)
{
    uint8 apiId   = moduleId;
    uint8 errorId = instanceId;

    (void)Det_ReportError(CDD_FSI_RX_MODULE_ID, CDD_FSI_RX_INSTANCE_ID, apiId, errorId);
    return;
}
#endif
/***************************************************************************************************************/
void CddFsiRx_ReportRuntimeError(uint8 moduleId, uint8 instanceId)
{
    uint8 apiId   = moduleId;
    uint8 errorId = instanceId;

    (void)Det_ReportRuntimeError(CDD_FSI_RX_MODULE_ID, CDD_FSI_RX_INSTANCE_ID, apiId, errorId);
    return;
}
/**************************************************************************************************************/
/*
 * Design:
 */
void CddFsiRx_resetDrvObj(CddFsiRx_DriverObjType *drvObj)
{
    uint8 hwUnitIdx = 0U;

    for (hwUnitIdx = 0U; hwUnitIdx < Cdd_FsiRx_DrvObj.maxHwUnit; hwUnitIdx++)
    {
        drvObj->hwUnitObj[hwUnitIdx].isNotifyOn = (uint32)E_NOT_OK;
    }
    drvObj->maxHwUnit = 0U;
    return;
}
/****************************************************************************************************************/
/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */

#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)
Std_ReturnType CddFsiRx_DMAdataReceive(Cdd_FsiRx_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    uint8  retVal, bufIdx = 0U;

    if (TRUE == Cdd_Dma_GetInitStatus())
    {
        if (hwUnitObj->hwUnitCfg.edmaRxInstance != 0xFFU)
        {
            /*
           * Here to configure dma some configuration values has to be sent like
           aCount,bCount.cCount. *aCount: CDD_FSI_RX_SIZEOF_BYTE - The value of this macro is 1
           which will be get multiplied by 2 inside the function CddFsiRxDma_ModuleChannelConfigure.
           So inside the function aCount will be 2 while loading into dma register. This is the size
           of bytes in each word. bCount:  CDD_FSI_TX_BUFF_SIZE_16_WORD_LENGTH -The  number of words
           to be copied from rx internal buffer cCount:  CDD_FSI_RX_DMA_C_COUNT- Number of times
           Count*bCount to be transferred. (Here it is 1 as only single iteration happens) */
            retVal = CddFsiRxDma_ModuleChannelConfigure(
                hwUnitObj, hwUnitObj->rxBuffer, CDD_FSI_RX_DATA_16_WORD_LENGTH + 1U,
                (void *)(baseAddr + CSL_CDD_FSI_RX_CFG_RX_BUF_BASE(bufIdx)), CDD_FSI_RX_SIZEOF_BYTE,
                CDD_FSI_RX_DMA_C_COUNT, CDD_EDMA_TRIG_MODE_MANUAL);
        }
        else
        {
            retVal = FALSE;
        }
    }
    else
    {
        retVal = FALSE;
    }

    return retVal;
}

#endif

#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)
/*! \brief      Configures the DMA Channel and configure register values for dma transfer.
 *
 *  \param[in]   *buffrPtr: Pointer to the internal buffer to which data has to be copied.
 *                table_size: 1
 *                *rx_databuffer:Pointer to the buffer from which data has to be copied
 *                bCnt :number of words to be copied in a dma transfer
 *                cCnt :number of dma transfers
 *                mode :mode of dma transfer(manual/event)
 *  \param[out]  void
 *  \context
 ******************************************************************************/
static Std_ReturnType CddFsiRxDma_ModuleChannelConfigure(Cdd_FsiRx_HwUnitObjType           *hwUnitObj,
                                                         volatile Cdd_FsiRx_DataBufferType *buffrPtr, uint16 table_size,
                                                         uint16 *rx_databuffer, uint8 bCnt, uint8 cCnt, uint32 mode)
{
    boolean            result = FALSE;
    Cdd_Dma_ParamEntry edmaParam0;
    uint32             handleId = hwUnitObj->hwUnitCfg.edmaRxInstance;

    /* Program Param Set */

    edmaParam0.srcPtr     = (void *)rx_databuffer;
    edmaParam0.destPtr    = (void *)(buffrPtr);
    edmaParam0.aCnt       = (uint16)(table_size * CDD_FSI_RX_SIZEOF_WORD);
    edmaParam0.bCnt       = (uint16)bCnt;
    edmaParam0.cCnt       = (uint16)cCnt;
    edmaParam0.bCntReload = 0U;
    edmaParam0.srcBIdx    = (sint16)(table_size * CDD_FSI_RX_SIZEOF_WORD);
    edmaParam0.destBIdx   = (sint16)(table_size * CDD_FSI_RX_SIZEOF_WORD);
    edmaParam0.srcCIdx    = 0U;
    edmaParam0.destCIdx   = (sint16)(table_size * bCnt * CDD_FSI_RX_SIZEOF_WORD);
    edmaParam0.opt        = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK);

    Cdd_Dma_ParamSet(handleId, CDD_FSI_RX_CHANNEL0, CDD_FSI_RX_PARAM0, edmaParam0);
    result = Cdd_Dma_EnableTransferRegion(handleId, mode);
    if (result == TRUE)
    {
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}

#endif /* #if (STD_ON == CDD_FSI_RX_DMA_ENABLE) */
/************************************************************************************************************/
#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)
static void CddFsiRx_IrqDmaRx(void *hwUnitObj)
{
    uint16                   hwUnitId = 0U;
    Cdd_FsiRx_HwUnitObjType *hwObj;
    hwObj    = (Cdd_FsiRx_HwUnitObjType *)hwUnitObj;
    hwUnitId = hwObj->hwUnitCfg.hwUnitId;
    Cdd_FsiRx_DrvObj.CddFsiRxDmaNotificationPtr(hwUnitId);
    return;
}
#endif /* #if (STD_ON == CDD_FSI_RX_DMA_ENABLE) */
/***********************************************************************************************************/

Std_ReturnType CddFsiRx_ClearResetRxSubModules(const Cdd_FsiRx_HwUnitObjType *hwUnitObj,
                                               Cdd_FsiRx_ResetSubModuleType   subModule)
{
    uint16 regVal;
    uint8  retVal   = E_OK;
    uint32 baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    switch (subModule)
    {
        /*
         * Key value must be written into controller control register and ensure
         * that FLUSH pattern is not sent while doing Rx core reset release.
         */
        case CDD_FSI_RX_MAIN_CORE_RESET:
            regVal = HW_RD_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB);
            regVal = (regVal & (uint16)(~CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_CORE_RST_MASK)) |
                     (CDD_FSI_RX_CTRL_REG_KEY << CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_KEY_SHIFT);
            HW_WR_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB, regVal);
            break;

        case CDD_FSI_RX_FRAME_WD_CNT_RESET:
            regVal  = HW_RD_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL);
            regVal &= (uint16)(~CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL_FRAME_WD_CNT_RST_MASK);
            HW_WR_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL, regVal);
            break;

        case CDD_FSI_RX_PING_WD_CNT_RESET:
            regVal  = HW_RD_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL);
            regVal &= (uint16)(~CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL_PING_WD_RST_MASK);
            HW_WR_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL, regVal);
            break;

        default:
            retVal = E_NOT_OK;
            break;
    }
    return retVal;
}
/*************************************************************************************************************/
Std_ReturnType CddFsiRx_ResetRxSubModules(const Cdd_FsiRx_HwUnitObjType *hwUnitObj,
                                          Cdd_FsiRx_ResetSubModuleType   SubModule)
{
    uint16 regVal;
    uint8  retVal   = E_OK;
    uint32 baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    switch (SubModule)
    {
        /*
         * Key value must be written into controller control register and ensure
         * that FLUSH pattern is not sent while doing Rx core reset
         */
        case CDD_FSI_RX_MAIN_CORE_RESET:
            regVal  = HW_RD_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB);
            regVal |= (uint16)CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_CORE_RST_MASK |
                      (CDD_FSI_RX_CTRL_REG_KEY << CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_KEY_SHIFT);
            HW_WR_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB, regVal);
            break;

        case CDD_FSI_RX_FRAME_WD_CNT_RESET:
            regVal  = HW_RD_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL);
            regVal |= CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL_FRAME_WD_CNT_RST_MASK;
            HW_WR_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL, regVal);
            break;

        case CDD_FSI_RX_PING_WD_CNT_RESET:
            regVal  = HW_RD_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL);
            regVal |= CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL_PING_WD_RST_MASK;
            HW_WR_REG16(baseAddr + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL, regVal);
            break;

        default:
            retVal = E_NOT_OK;
            break;
    }

    return (retVal);
}

/******************************************************************************/
static FUNC(void, CDD_FSIRX_CODE) CddFsiRx_delayWait(uint32 delay)
{
    volatile uint32 tempCount = delay;
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    if (delay > 9U)
    {
        tempCount = delay / 9U;
    }
    while (tempCount <= 0U)
    {
        MCAL_SW_DELAY(tempCount);
    }
}
/************************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_SetRxSoftwareFrameSize(uint32 base, CddFsiRx_DataLengthType dataWidth)
{
    uint32 regVal;

    regVal = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_OPER_CTRL);
    regVal = (regVal & (uint32)(~CSL_CDD_FSI_RX_CFG_RX_OPER_CTRL_N_WORDS_MASK)) |
             ((uint32)dataWidth << CSL_CDD_FSI_RX_CFG_RX_OPER_CTRL_N_WORDS_SHIFT);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_OPER_CTRL, regVal);

    return;
}
/******************************************************************************/

#define CDD_FSIRX_STOP_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"
/*******************************************************************************/
/*  End of File: Cdd_FsiRx_Priv.c*/
/******************************************************************************/
