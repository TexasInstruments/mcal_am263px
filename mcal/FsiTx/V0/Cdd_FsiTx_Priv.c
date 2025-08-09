/*
 *
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     CDD_FSI_TX_Priv.c
 *
 *  \brief    This file contains CDD_FSI_TX MCAL driver internal functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_FsiTx_Cfg.h"
#include "Cdd_FsiTx.h"
#include "Cdd_FsiTx_Priv.h"
#include "Cdd_FsiTx_Irq.h"
#include "Dem.h"
#if (CDD_FSI_TX_DMA_ENABLE == STD_ON)
#include "Cdd_Dma.h"
#endif
#include "Os.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* =========================================================================== */
static void CddFsiTx_delayWait(uint32 delaycount);
#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
static void           CddFsiTx_IrqDmaTx(void *hwUnitObj);
static Std_ReturnType CddFsiTxDma_ModuleChannelConfigure(Cdd_FsiTx_HwUnitObjType *hwUnitObj, const uint16 *tx_buffrPtr,
                                                         uint16                    table_size,
                                                         Cdd_FsiTx_DataBufferType *srcaddr_databuffer, uint8 bCnt,
                                                         uint8 cCount, uint32 mode, const uint16 *tx_tag_udataPtr,
                                                         uint32 *tag_udata);
#endif /* #if (STD_ON == CDD_FSI_TX_DMA_ENABLE) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
#define CDD_FSITX_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiTx_MemMap.h"
/** \brief CDD_FSI_TX DMA object */
VAR(Cdd_FsiTx_HwUnitObjType, CDD_FSITX_VAR_CLEARED) * Cdd_FsiTx_DmaConfigObj;
#define CDD_FSITX_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiTx_MemMap.h"
#endif /* #if (STD_ON == CDD_FSI_TX_DMA_ENABLE) */

#define CDD_FSITX_START_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_FsiTx_MemMap.h"
/** \brief Variable which contains the driver status related to Ping frame transmission */
volatile VAR(Cdd_FsiTx_PingTagType, CDD_FSITX_VAR_CLEARED) Cdd_FsiTx_PingStatus = CDD_FSI_TX_PING_ZERO_SENT;
#define CDD_FSITX_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_FsiTx_MemMap.h"

#define CDD_FSITX_START_SEC_VAR_INIT_32
#include "Cdd_FsiTx_MemMap.h"
/** \brief Number of words to be transmitted(frame size) */
VAR(uint32, CDD_FSITX_VAR_CLEARED)
Cdd_FsiTx_wordLength = 0U;
#define CDD_FSITX_STOP_SEC_VAR_INIT_32
#include "Cdd_FsiTx_MemMap.h"

#define CDD_FSITX_START_SEC_VAR_INIT_32
#include "Cdd_FsiTx_MemMap.h"
/** \brief Frame Tag to be transmitted */
VAR(uint32, CDD_FSITX_VAR_CLEARED)
Cdd_FsiTx_frametag = 0x01U;
#define CDD_FSITX_STOP_SEC_VAR_INIT_32
#include "Cdd_FsiTx_MemMap.h"

extern VAR(Cdd_FsiTx_DriverObjType, CDD_FSITX_VAR_CLEARED) Cdd_FsiTx_DrvObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CDD_FSITX_START_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"

/*
 * Design:
 */
Std_ReturnType CddFsiTx_hwUnitInit(Cdd_FsiTx_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr = 0;
    uint32 retVal   = E_OK;
    /* Assign base address */

    baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    CddFsiTx_selectTxPLLClock(baseAddr, CSL_CDD_FSI_TX_CLK_SELECT);
    CddFsiTx_resetTxModule(baseAddr);
    /* include 5 clock pulse delay*/
    CddFsiTx_delayWait((uint32)10U * (hwUnitObj->hwUnitCfg.Prescalar));
    CddFsiTx_clearTxModuleReset(baseAddr);
    /* include 5 clock pulse delay*/
    CddFsiTx_delayWait((uint32)10U * (hwUnitObj->hwUnitCfg.Prescalar));
    CddFsiTx_setPrescaler(baseAddr, hwUnitObj->hwUnitCfg.Prescalar);
    CddFsiTx_enableClock(baseAddr);
    retVal = CddFsiTx_setTxDataLane(baseAddr, CDD_FSI_TX_SINGLE_DATA_LANE);
    CddFsiTx_setStartMode(baseAddr, CDD_FSI_TX_SW_START_MODE);

    if (retVal == E_OK)
    {
        CddFsiTx_disableInterrupt(hwUnitObj->hwUnitCfg.baseAddr, CDD_FSI_TX_INT_TYPE);
        CddFsiTx_clearAllTxEvents(baseAddr);

        if (hwUnitObj->hwUnitCfg.transmitMode == CDD_FSI_TX_INTERRUPT_MODE)
        {
            (void)CddFsiTx_enableInterrupt(baseAddr, CDD_FSI_TX_INT_TYPE);
        }

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
        Cdd_FsiTx_DmaConfigObj = hwUnitObj;
#endif
        /* The Transmit buffer pointer keeps at initial position*/
        CddFsiTx_ForceTxBufferPtr(baseAddr, 0);
        CddFsiTx_sendFlushSequence(baseAddr);
        /* include 5 clock pulse delay*/
        CddFsiTx_delayWait((uint32)10U * (hwUnitObj->hwUnitCfg.Prescalar));
        CddFsiTx_stopFlushSequence(baseAddr);
    }
    return retVal;
}

/*
 * Design:
 */
Std_ReturnType CddFsiTx_hwUnitDeInit(Cdd_FsiTx_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr;
    uint8  retVal = E_OK;
    baseAddr      = hwUnitObj->hwUnitCfg.baseAddr;
    CddFsiTx_disablePingTimer(baseAddr);
    retVal = CddFsiTx_clearTxEvents(baseAddr, CDD_FSI_TX_EVTMASK);
    if (hwUnitObj->hwUnitCfg.transmitMode == CDD_FSI_TX_INTERRUPT_MODE)
    {
        CddFsiTx_disableInterrupt(baseAddr, CDD_FSI_TX_INT_TYPE);
    }
#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
    CddFsiTx_disableTxDMAEvent(baseAddr);
#endif
    CddFsiTx_disableClock(baseAddr);
    return retVal;
}

/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
Std_ReturnType CddFsiTx_copyConfig(Cdd_FsiTx_DriverObjType *drvObj, const Cdd_FsiTx_ConfigType *cfgPtr)
{
    uint8                             hwUnitId;
    const Cdd_FsiTx_HwUnitConfigType *hwCfg;
    Cdd_FsiTx_HwUnitObjType          *hwObj;
    Std_ReturnType                    retVal = E_OK;
    drvObj->maxHwUnit                        = cfgPtr->maxHwUnit;
    drvObj->CddFsiTxNotificationPtr          = cfgPtr->cddFsiTxNotification;
    drvObj->CddFsiTxOverRunNotificationPtr   = cfgPtr->cddFsiTxOverRunNotification;
    drvObj->CddFsiTxUnderRunNotificationPtr  = cfgPtr->cddFsiTxUnderRunNotification;
#if (CDD_FSI_TX_DMA_ENABLE == STD_ON)
    drvObj->CddFsiTxDmaNotificationPtr = cfgPtr->cddFsiTxDmaNotification;
#endif
    for (hwUnitId = 0U; hwUnitId < cfgPtr->maxHwUnit; hwUnitId++)
    {
        hwCfg = &cfgPtr->hwUnitCfg[hwUnitId];
        /* Copy configuration */
        (void)memcpy(&drvObj->hwUnitObj[hwUnitId].hwUnitCfg, hwCfg, sizeof(Cdd_FsiTx_HwUnitConfigType));
        hwObj                     = &drvObj->hwUnitObj[hwUnitId];
        hwObj->hwUnitCfg.baseAddr = hwCfg->baseAddr;
#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
        hwObj->hwUnitCfg.CddFsiTxDmaInstance = hwCfg->CddFsiTxDmaInstance;
        if (hwObj->hwUnitCfg.CddFsiTxDmaInstance != 0xFFU)
        {
            Cdd_Dma_CbkRegister(hwObj->hwUnitCfg.CddFsiTxDmaInstance, (void *)hwObj, &CddFsiTx_IrqDmaTx);
        }

#endif
    }
    return retVal;
}

/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
Std_ReturnType CddFsiTx_PingTransmit(Cdd_FsiTx_HwUnitObjType *hwUnitObj)
{
    uint32         baseAddr;
    Std_ReturnType retVal = E_NOT_OK;
    /* Assign base address */
    baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    retVal   = CddFsiTx_setFrameType(baseAddr, CDD_FSI_TX_DATA_PING_FRAME);

    CddFsiTx_enableTxPingTimer(baseAddr, hwUnitObj->hwUnitCfg.pingTriggerTimeout, CDD_FSI_TX_PING_TAG0);

    if (retVal == E_OK)
    {
        if (Cdd_FsiTx_PingStatus != CDD_FSI_TX_PING_ZERO_SENT)
        {
            /* Set the Pingtag as Tag0 for CDD_FSI_TX HW unit. */
            CddFsiTx_setPingTag(baseAddr, CDD_FSI_TX_PING_TAG0);
            if (hwUnitObj->hwUnitCfg.triggSrc == CDD_FSI_TX_TRIGG_SRC_SW)
            {
                CddFsiTx_startTxTransmit(baseAddr);
            }
            Cdd_FsiTx_PingStatus = CDD_FSI_TX_PING_ZERO_SENT;
        }
        else
        {
            if (Cdd_FsiTx_PingStatus == CDD_FSI_TX_PING_ZERO_SENT)
            {
                CddFsiTx_setPingTag(baseAddr, CDD_FSI_TX_PING_TAG1);
                if (hwUnitObj->hwUnitCfg.triggSrc == CDD_FSI_TX_TRIGG_SRC_SW)
                {
                    CddFsiTx_startTxTransmit(baseAddr);
                }
                Cdd_FsiTx_PingStatus = CDD_FSI_TX_PING_ONE_SENT;
            }
        }
    }
    else
    {
        CddFsiTx_ReportRuntimeError(CDD_FSI_TX_INIT_SID, CDD_FSI_TX_E_INVALID_EVENT);
    }
    return retVal;
}
Std_ReturnType CddFsiTx_BufferLoad(Cdd_FsiTx_HwUnitObjType *hwUnitObj,
                                   P2VAR(uint16, AUTOMATIC, CDD_FSI_TX_APPL_DATA) databuffer, uint32 userData,
                                   uint32 txDatalength)
{
    uint32 baseAddr = 0;
    uint8  retVal   = 0;
    /* Assign base address */
    baseAddr             = hwUnitObj->hwUnitCfg.baseAddr;
    Cdd_FsiTx_wordLength = txDatalength;
    /* The Transmit buffer pointer keeps at initial position*/
    CddFsiTx_ForceTxBufferPtr(baseAddr, 0);
    if (CDD_FSI_TX_DMA_MODE == hwUnitObj->hwUnitCfg.transmitMode)
    {
#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)

        retVal = CddFsiTx_DMABufferLoad(hwUnitObj, databuffer, userData, Cdd_FsiTx_wordLength);
        if (retVal == TRUE)
        {
            retVal = E_OK;
        }
#endif /* (STD_ON == CDD_FSI_TX_DMA_ENABLE) */
    }
    else
    {
        (void)userData;
        retVal = CddFsiTx_dataBufferLoad(baseAddr, databuffer, Cdd_FsiTx_wordLength);
    }
    return (retVal);
}

/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
Std_ReturnType CddFsiTx_DMABufferLoad(Cdd_FsiTx_HwUnitObjType *hwUnitObj, Cdd_FsiTx_DataBufferType *databuffer,
                                      uint32 userData, uint32 TxDatalength)
{
    uint32         baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    Std_ReturnType retVal   = 0;
    uint8          bufIdx   = 0;
    bufIdx                  = 0;
    uint32 Data             = userData;
    Data                    = (Data << 8U) + Cdd_FsiTx_frametag;
    uint32 *dataPtr         = &Data;
    (void)CddFsiTx_setFrameType(baseAddr, CDD_FSI_TX_DATA_N_WORD);
    retVal = CddFsiTx_setTxSoftwareFrameSize(baseAddr, TxDatalength);

    if (TRUE == Cdd_Dma_GetInitStatus())
    {
        if (hwUnitObj->hwUnitCfg.CddFsiTxDmaInstance != 0xFFU)
        {
            /*
             * Here to configure dma some configuration values has to be sent like
             aCount,bCount.cCount. *aCount: CDD_FSI_TX_BYTE_SIZE - The value of this macro is 1
             which will be get multiplied by 2 inside the function
             CddFsiTxDma_ModuleChannelConfigure. So inside the function aCount will be 2 while
             loading into dma register. This is the size of bytes in each word. bCount:
             CDD_FSI_TX_DATA_16_WORD_LENGTH -The  number of words to be copied to tx internal buffer
              cCount:  CDD_FSI_TX_DMA_C_COUNT- Number of times Count*bCount to be transferred.
              (Here it is 1 as only single iteration happens)*/
            retVal = CddFsiTxDma_ModuleChannelConfigure(
                hwUnitObj, (void *)(baseAddr + CSL_CDD_FSI_TX_CFG_TX_BUF_BASE(bufIdx)), 1, databuffer, 16, 1,
                CDD_EDMA_TRIG_MODE_MANUAL, (void *)(baseAddr + CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA), dataPtr);
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

#endif

/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
Std_ReturnType CddFsiTx_Transmit(Cdd_FsiTx_HwUnitObjType *hwUnitObj, uint8 UserData,
                                 Cdd_FsiTx_DataLengthType txDataLength)
{
    uint32         baseAddr = 0;
    Std_ReturnType retVal   = E_OK;
    /* Assign base address */
    baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    (void)CddFsiTx_setFrameType(baseAddr, CDD_FSI_TX_DATA_N_WORD);
    retVal = CddFsiTx_setTxSoftwareFrameSize(baseAddr, txDataLength);
#if (STD_OFF == CDD_FSI_TX_DMA_ENABLE)
    retVal = CddFsiTx_setTxUserDefinedData(baseAddr, UserData);
    CddFsiTx_setTxFrameTag(baseAddr, Cdd_FsiTx_frametag);
#endif
    /* Check whether the trigger source is SW and initiate transmission*/
    if (hwUnitObj->hwUnitCfg.triggSrc == CDD_FSI_TX_TRIGG_SRC_SW)
    {
        CddFsiTx_startTxTransmit(baseAddr);
    }
    return (retVal);
}
/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */

void CddFsiTx_IrqTx(Cdd_FsiTx_HwUnitObjType *hwUnitObj, CddFsiTx_McalIntNumberType InterruptNum, uint16 EvtFlag)
{
    (void)InterruptNum;
    uint32 baseAddr;
    baseAddr = hwUnitObj->hwUnitCfg.baseAddr;
    {
        (void)CddFsiTx_clearTxEvents(baseAddr, CDD_FSI_TX_PING_TRIGGERED);
    }
    if ((EvtFlag & CDD_FSI_TX_FRAME_DONE_MASK) == 1U)
    {
        Cdd_FsiTx_DrvObj.CddFsiTxNotificationPtr(hwUnitObj->hwUnitCfg.hwId);
        (void)CddFsiTx_clearTxEvents(baseAddr, CDD_FSI_TX_FRAME_DONE);
    }
    if ((EvtFlag & CDD_FSI_TX_BUFFER_UNDERRUN) >> CDD_FSI_TX_BUFFER_UNDERRUN_SHIFT == 1U)
    {
        /*call DEM Error*/
#ifdef CDD_FSI_TX_E_BUFFER_UNDERRUN
        (void)Dem_SetEventStatus(CDD_FSI_TX_E_BUFFER_UNDERRUN, DEM_EVENT_STATUS_FAILED);
#endif
        Cdd_FsiTx_DrvObj.CddFsiTxUnderRunNotificationPtr(hwUnitObj->hwUnitCfg.hwId);
        (void)CddFsiTx_clearTxEvents(baseAddr, CDD_FSI_TX_BUFFER_UNDERRUN);
    }
    if ((EvtFlag & CDD_FSI_TX_BUFFER_OVERRUN) >> CDD_FSI_TX_BUFFER_OVERRUN_SHIFT == 1U)
    {
#ifdef CDD_FSI_TX_E_BUFFER_OVERRUN
        (void)Dem_SetEventStatus(CDD_FSI_TX_E_BUFFER_OVERRUN, DEM_EVENT_STATUS_FAILED);
#endif
        Cdd_FsiTx_DrvObj.CddFsiTxOverRunNotificationPtr(hwUnitObj->hwUnitCfg.hwId);
        (void)CddFsiTx_clearTxEvents(baseAddr, CDD_FSI_TX_BUFFER_OVERRUN);
    }
}

/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
void CddFsiTx_ReportDetError(uint8 moduleId, uint8 instanceId)
{
    uint8 apiId   = moduleId;
    uint8 errorId = instanceId;

    (void)Det_ReportError(CDD_FSI_TX_MODULE_ID, CDD_FSI_TX_INSTANCE_ID, apiId, errorId);
    return;
}
#endif

void CddFsiTx_ReportRuntimeError(uint8 moduleId, uint8 instanceId)
{
    uint8 apiId   = moduleId;
    uint8 errorId = instanceId;

    (void)Det_ReportRuntimeError(CDD_FSI_TX_MODULE_ID, CDD_FSI_TX_INSTANCE_ID, apiId, errorId);
    return;
}

/*
 * Design:
 */
void CddFsiTx_resetDrvObj(Cdd_FsiTx_DriverObjType *drvObj)
{
    uint8                    hwUnitIdx = 0;
    Cdd_FsiTx_HwUnitObjType *hwObj;
    for (hwUnitIdx = 0U; hwUnitIdx < (uint8)CDD_FSI_TX_HW_UNIT_CNT; hwUnitIdx++)
    {
        hwObj = &drvObj->hwUnitObj[hwUnitIdx];

        drvObj->hwUnitObj[hwUnitIdx].isNotifyOn = (uint32)E_NOT_OK;
        hwObj->hwUnitCfg.hwUnitId               = 0;
        hwObj->hwUnitCfg.triggSrc               = CDD_FSI_TX_TRIGG_SRC_SW;
        hwObj->hwUnitCfg.transmitMode           = CDD_FSI_TX_INTERRUPT_MODE;
        hwObj->hwUnitCfg.triggSrc               = CDD_FSI_TX_TRIGG_SRC_SW;
        hwObj->hwUnitCfg.pingTriggerTimeout     = 0;
#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
        hwObj->hwUnitCfg.CddFsiTxDmaInstance = 0;
#endif
    }
    drvObj->maxHwUnit = 0U;
    return;
}

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)

/*! \brief      Configures the DMA Channel and configure register values for dma transfer.
 *
 *  \param[in]   *tx_buffrPtr: Pointer to the internal buffer to which data has to be copied.
 *                table_size: 1
 *                *srcaddr_databuffer:Pointer to the buffer from which data has to be copied
 *                bCnt :number of words to be copied in a dma transfer
 *                cCnt :number of dma transfers
 *                mode :mode of dma transfer(manual/event)
 *                *tx_tag_udataPtr: pointer to the register to which  UserData and Tag stores.
 *                *tag_udata:pointer to the buffer which stores UserData and Tag
 *  \param[out]  void
 *  \context
 ******************************************************************************/
static Std_ReturnType CddFsiTxDma_ModuleChannelConfigure(Cdd_FsiTx_HwUnitObjType *hwUnitObj, const uint16 *tx_buffrPtr,
                                                         uint16                    table_size,
                                                         Cdd_FsiTx_DataBufferType *srcaddr_databuffer, uint8 bCnt,
                                                         uint8 cCount, uint32 mode, const uint16 *tx_tag_udataPtr,
                                                         uint32 *tag_udata)
{
    bool               result = FALSE;
    uint32             opt0, opt1, chainOption;
    Cdd_Dma_ParamEntry edmaParam0, edmaParam1;
    opt0 = (CDD_EDMA_OPT_SYNCDIM_MASK);
    opt1 = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK);
    /* Chain option to be used when chaining between two channels */
    chainOption     = (CDD_EDMA_OPT_ITCCHEN_MASK | CDD_EDMA_OPT_TCCHEN_MASK);
    uint32 handleId = hwUnitObj->hwUnitCfg.CddFsiTxDmaInstance;
    /* Program Param Set */
    edmaParam0.srcPtr     = (void *)(srcaddr_databuffer);
    edmaParam0.destPtr    = (void *)(tx_buffrPtr);
    edmaParam0.aCnt       = (uint16)(table_size * CDD_FSI_TX_WORD_SIZE);
    edmaParam0.bCnt       = (uint16)bCnt;
    edmaParam0.cCnt       = (uint16)cCount;
    edmaParam0.bCntReload = CDD_FSI_TX_ZERO_COUNT;
    edmaParam0.srcBIdx    = (sint16)(table_size * CDD_FSI_TX_WORD_SIZE);
    edmaParam0.destBIdx   = (sint16)(table_size * CDD_FSI_TX_WORD_SIZE);
    edmaParam0.srcCIdx    = (sint16)(table_size * bCnt * CDD_FSI_TX_WORD_SIZE);
    edmaParam0.destCIdx   = CDD_FSI_TX_ZERO_COUNT;
    edmaParam0.opt        = opt0;

    edmaParam1.srcPtr     = (void *)(tag_udata);
    edmaParam1.destPtr    = (void *)(tx_tag_udataPtr);
    edmaParam1.aCnt       = (uint16)CDD_FSI_TX_WORD_SIZE;
    edmaParam1.bCnt       = (uint16)CDD_FSI_TX_BYTE_SIZE;
    edmaParam1.cCnt       = (uint16)cCount;
    edmaParam1.bCntReload = CDD_FSI_TX_ZERO_COUNT;
    edmaParam1.srcBIdx    = CDD_FSI_TX_ZERO_COUNT;
    edmaParam1.destBIdx   = CDD_FSI_TX_ZERO_COUNT;
    edmaParam1.srcCIdx    = CDD_FSI_TX_ZERO_COUNT;
    edmaParam1.destCIdx   = CDD_FSI_TX_ZERO_COUNT;
    edmaParam1.opt        = opt1;

    Cdd_Dma_ParamSet(handleId, CDD_FSI_TX_CHANNEL0, CDD_FSI_TX_PARAM0, edmaParam0);
    Cdd_Dma_ParamSet(handleId, CDD_FSI_TX_CHANNEL1, CDD_FSI_TX_PARAM0, edmaParam1);
    Cdd_Dma_ChainChannel(handleId, CDD_FSI_TX_CHANNEL0, CDD_FSI_TX_PARAM0, CDD_FSI_TX_CHANNEL1, chainOption);
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
#endif /* #if (STD_ON == CDD_FSI_TX_DMA_ENABLE) */

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
static void CddFsiTx_IrqDmaTx(void *hwUnitObj)
{
    uint16                   hwUnitId = 0U;
    Cdd_FsiTx_HwUnitObjType *hwObj;
    hwObj    = (Cdd_FsiTx_HwUnitObjType *)hwUnitObj;
    hwUnitId = hwObj->hwUnitCfg.hwUnitId;
    Cdd_FsiTx_DrvObj.CddFsiTxDmaNotificationPtr(hwUnitId);

    return;
}
#endif /* #if (STD_ON == CDD_FSI_TX_DMA_ENABLE) */

void CddFsiTx_MainFunction(Cdd_FsiTx_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr;
    baseAddr           = hwUnitObj->hwUnitCfg.baseAddr;
    uint16 eventStatus = (HW_RD_REG16(baseAddr + CSL_CDD_FSI_TX_CFG_TX_EVT_STS));

    if ((eventStatus & CDD_FSI_TX_FRAME_DONE_MASK) == 1U)
    {
        Cdd_FsiTx_DrvObj.CddFsiTxNotificationPtr(hwUnitObj->hwUnitCfg.hwId);
        (void)CddFsiTx_clearTxEvents(baseAddr, CDD_FSI_TX_FRAME_DONE);
    }

    return;
}

Std_ReturnType CddFsiTx_ClearResetTxSubModules(Cdd_FsiTx_HwUnitObjType     *hwUnitObj,
                                               Cdd_FsiTx_ResetSubModuleType subModule)
{
    uint16 regVal;
    uint16 regBase;
    uint8  retVal   = E_OK;
    uint16 baseAddr = hwUnitObj->hwUnitCfg.baseAddr;

    switch (subModule)
    {
        /*
         * Key value must be written into controller control register and ensure
         * that FLUSH pattern is not sent while doing Tx core reset release.
         */
        case CDD_FSI_TX_MAIN_CORE_RESET:
            regVal = HW_RD_REG16(baseAddr + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL);
            regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_CORE_RST_MASK)) |
                     (CDD_FSI_TX_CTRL_REG_KEY << CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_KEY_SHIFT);
            regBase = baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL;
            HW_WR_REG16(regBase, regVal);
            break;

        case CDD_FSI_TX_CLOCK_RESET:
            regVal   = HW_RD_REG16((baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL));
            regVal  &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL_CLK_RST_MASK);
            regBase  = baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL;
            HW_WR_REG16(regBase, regVal);
            break;

        case CDD_FSI_TX_PING_TIMEOUT_CNT_RESET:
            regVal   = HW_RD_REG16((baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1));
            regVal  &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1_CNT_RST_MASK);
            regBase  = baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1;
            HW_WR_REG16(regBase, regVal);
            break;

        default:
            retVal = E_NOT_OK;
            break;
    }
    return retVal;
}
/*****************************************************/
Std_ReturnType CddFsiTx_ResetTxSubModules(Cdd_FsiTx_HwUnitObjType *hwUnitObj, Cdd_FsiTx_ResetSubModuleType SubModule)
{
    uint16 regVal;
    uint16 regBase;
    uint8  retVal   = E_OK;
    uint16 baseAddr = hwUnitObj->hwUnitCfg.baseAddr;

    switch (SubModule)
    {
            /*
             * Key value must be written into controller control register and ensure
             * that FLUSH pattern is not sent while doing Tx core reset
             */
        case CDD_FSI_TX_MAIN_CORE_RESET:
            regVal = (uint16)CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_CORE_RST_MASK |
                     (CDD_FSI_TX_CTRL_REG_KEY << CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_KEY_SHIFT);
            regBase = baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL;
            HW_WR_REG16(regBase, regVal);
            break;

        case CDD_FSI_TX_CLOCK_RESET:
            regVal   = HW_RD_REG16((baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL));
            regVal  |= CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL_CLK_RST_MASK;
            regBase  = baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL;
            HW_WR_REG16(regBase, regVal);
            break;

        case CDD_FSI_TX_PING_TIMEOUT_CNT_RESET:
            regVal   = HW_RD_REG16((baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1));
            regVal  |= CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1_CNT_RST_MASK;
            regBase  = baseAddr + (uint16)CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1;
            HW_WR_REG16(regBase, regVal);
            break;

        default:
            retVal = E_NOT_OK;
            break;
    }
    return retVal;
}

/******************************************************************************/
static void CddFsiTx_delayWait(uint32 delaycount)
{
    volatile uint32 tempCount = delaycount;
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    if (delaycount > 9U)
    {
        tempCount = delaycount / 9U;
    }
    while (tempCount <= 0U)
    {
        MCAL_SW_DELAY(tempCount);
    }
}

#define CDD_FSITX_STOP_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"
/*******************************************************************************/
/*  End of File: Cdd_FsiTx_Priv.c*/
/******************************************************************************/
