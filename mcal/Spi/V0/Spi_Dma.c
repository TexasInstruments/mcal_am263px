/* ======================================================================
 *   Copyright (C) 2023-2024 Texas Instruments Incorporated
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
 *  \file     Spi_Dma.c
 *
 *  \brief    This file contains SPI MCAL driver functions for using EDMA
 *            with MCSPI peripheral
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Spi_Cfg.h"
#include "Spi.h"
#include "Spi_Priv.h"

#if (SPI_DMA_ENABLE == STD_ON)

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"
#include "lldr_mcspi.h"
#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Transmit EDMA channel event queue number                           */
#define MCAL_EDMA_MCSPI_TX_EVT_QUEUE_NO (0U)
/** \brief Receive EDMA channel event queue number                            */
#define MCAL_EDMA_MCSPI_RX_EVT_QUEUE_NO (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                     Function Declarations                                  */
/* ========================================================================== */

void          Spi_DmaTxIsrHandler(void *args);
void          Spi_DmaRxIsrHandler(void *args);
static void   Spi_dmaTxIsrHandler_StatusCheck(const Spi_HwUnitObjType *hwUnitObj);
static sint32 Spi_dmaChInit_status(Spi_HwUnitObjType *hwUnitObj, Spi_TxRxMode txRxMode);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

/* Requirements : MCAL-____ */
sint32 Spi_dmaChInit(Spi_DriverObjType *drvObj, Spi_HwUnitObjType *hwUnitObj, Spi_TxRxMode txRxMode)
{
    sint32 status = MCAL_SystemP_FAILURE;
    if (drvObj != NULL_PTR)
    {
        status = Spi_dmaChInit_status(hwUnitObj, txRxMode);
    }

    return (status);
}

static sint32 Spi_dmaChInit_status(Spi_HwUnitObjType *hwUnitObj, Spi_TxRxMode txRxMode)
{
    sint32  status = MCAL_SystemP_SUCCESS;
    boolean isEdmaInterruptEnabled;

    /* Can be checked if interrupt is enabled */
    if ((Cdd_Dma_Config.CddDmaDriverHandler[hwUnitObj->dmaTxHandlerID]->edmaConfig.intrEnable == TRUE) &&
        (Cdd_Dma_Config.CddDmaDriverHandler[hwUnitObj->dmaRxHandlerID]->edmaConfig.intrEnable == TRUE))
    {
        isEdmaInterruptEnabled = TRUE;
    }
    else
    {
        isEdmaInterruptEnabled = FALSE;
    }

    if (isEdmaInterruptEnabled == TRUE)
    {
        if ((SPI_TX_RX_MODE_BOTH == txRxMode) || (SPI_TX_RX_MODE_TX_ONLY == txRxMode))
        {
            /* Register TX interrupt */
            status += (sint32)Cdd_Dma_CbkRegister(hwUnitObj->dmaTxHandlerID, (void *)hwUnitObj, Spi_DmaTxIsrHandler);
        }

        if ((SPI_TX_RX_MODE_BOTH == txRxMode))
        {
            /* Register RX interrupt */
            status += (sint32)Cdd_Dma_CbkRegister(hwUnitObj->dmaRxHandlerID, (void *)hwUnitObj, Spi_DmaRxIsrHandler);
        }
    }
    else
    {
        status = MCAL_SystemP_FAILURE;
    }
    return (status);
}

Std_ReturnType Spi_dmaTransfer(const Spi_HwUnitObjType *HwUnitObj, Spi_JobObjType *jobObj, Spi_ChannelObjPtrType chObj,
                               uint16 Count)
{
    Std_ReturnType     status         = (Std_ReturnType)E_OK;
    uint32             dmaTxCh        = 0U;
    uint32             dmaRxCh        = 0U;
    uint32             paramTx        = 0U;
    uint32             paramRx        = 0U;
    uint32             paramDummy     = 1U;
    Cdd_Dma_ParamEntry edmaTxParam    = {0};
    Cdd_Dma_ParamEntry edmaRxParam    = {0};
    Cdd_Dma_ParamEntry edmaDummyParam = {0};

    if ((SPI_TX_RX_MODE_BOTH == jobObj->extDevCfg->mcspi.txRxMode))
    {
        /* Receive param set configuration */
        edmaRxParam.srcPtr     = (uint8 *)HwUnitObj->baseAddr + MCSPI_CHRX(jobObj->jobCfg_PC.csPin);
        edmaRxParam.destPtr    = (void *)chObj->curRxBufPtr;
        edmaRxParam.aCnt       = (uint16)(((uint16)1U) << ((uint16)(((uint16)chObj->bufWidth) / ((uint16)2U))));
        edmaRxParam.bCnt       = Count;
        edmaRxParam.cCnt       = (uint16)1U;
        edmaRxParam.bCntReload = (uint16)edmaRxParam.bCnt;
        edmaRxParam.srcBIdx    = (sint16)0U;
        edmaRxParam.destBIdx   = (sint16)edmaRxParam.aCnt;
        edmaRxParam.srcCIdx    = (sint16)0U;
        edmaRxParam.destCIdx   = (sint16)0U;
        edmaRxParam.opt        = CDD_EDMA_OPT_TCINTEN_MASK;

        /* Write Rx param set */
        Cdd_Dma_ParamSet(HwUnitObj->dmaRxHandlerID, dmaRxCh, paramRx, edmaRxParam);

        /* Set event trigger to start McSPI RX transfer */
        if ((boolean)FALSE == Cdd_Dma_EnableTransferRegion(HwUnitObj->dmaRxHandlerID, CDD_EDMA_TRIG_MODE_EVENT))
        {
            status = (Std_ReturnType)E_NOT_OK;
        }
    }

    if ((SPI_TX_RX_MODE_BOTH == jobObj->extDevCfg->mcspi.txRxMode) ||
        (SPI_TX_RX_MODE_TX_ONLY == jobObj->extDevCfg->mcspi.txRxMode))
    {
        /* Transmit param set configuration */
        edmaTxParam.srcPtr     = (void *)chObj->curTxBufPtr;
        edmaTxParam.destPtr    = (uint8 *)HwUnitObj->baseAddr + MCSPI_CHTX(jobObj->jobCfg_PC.csPin);
        edmaTxParam.aCnt       = (uint16)(((uint16)1U) << ((uint16)(((uint16)chObj->bufWidth) / ((uint16)2U))));
        edmaTxParam.bCnt       = Count;
        edmaTxParam.cCnt       = (uint16)1U;
        edmaTxParam.bCntReload = (uint16)edmaTxParam.bCnt;
        edmaTxParam.srcBIdx    = (sint16)edmaTxParam.aCnt;
        edmaTxParam.destBIdx   = (sint16)0U;
        edmaTxParam.srcCIdx    = (sint16)0U;
        edmaTxParam.destCIdx   = (sint16)0U;
        edmaTxParam.opt        = CDD_EDMA_OPT_TCINTEN_MASK;

        /* Write Tx param set */
        Cdd_Dma_ParamSet(HwUnitObj->dmaTxHandlerID, dmaTxCh, paramTx, edmaTxParam);

        /* Dummy param set configuration */
        edmaDummyParam.aCnt = (uint16)1U;

        /* Write Tx dummy param set */
        Cdd_Dma_ParamSet(HwUnitObj->dmaTxHandlerID, dmaTxCh, paramDummy, edmaDummyParam);

        /* Link dummy param ID */
        Cdd_Dma_LinkChannel(HwUnitObj->dmaTxHandlerID, paramTx, paramDummy);

        /* Set event trigger to start McSPI TX transfer */
        if ((boolean)FALSE == Cdd_Dma_EnableTransferRegion(HwUnitObj->dmaTxHandlerID, CDD_EDMA_TRIG_MODE_EVENT))
        {
            status = (Std_ReturnType)E_NOT_OK;
        }
    }

    /* Initiate Transfer */
    if ((Std_ReturnType)E_OK == status)
    {
        MCSPI_dmaStart(jobObj, HwUnitObj->baseAddr, MCSPI_MODULCTRL_SINGLE_SINGLE);
    }

    return (status);
}

Std_ReturnType Spi_dmaStop(Spi_JobObjType *jobObj, uint32 baseAddr, uint32 chNum, uint8 chMode)
{
    Std_ReturnType status = E_OK;

    /* Manual CS de-assert */
    if (MCSPI_MODULCTRL_SINGLE_SINGLE == chMode)
    {
        HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_FORCE, CSL_MCSPI_CH0CONF_FORCE_DEASSERT);
    }

    /* Disable channel */
    HW_WR_FIELD32((baseAddr + MCSPI_CHCTRL(chNum)), CSL_MCSPI_CH0CTRL_EN, CSL_MCSPI_CH0CTRL_EN_NACT);

    if (SPI_TX_RX_MODE_BOTH == jobObj->extDevCfg->mcspi.txRxMode)
    {
        /* Disable DMA */
        HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_DMAW, CSL_MCSPI_CH0CONF_DMAW_DISABLED);
        HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_DMAR, CSL_MCSPI_CH0CONF_DMAR_DISABLED);
    }
    else if (SPI_TX_RX_MODE_TX_ONLY == jobObj->extDevCfg->mcspi.txRxMode)
    {
        HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_DMAW, CSL_MCSPI_CH0CONF_DMAW_DISABLED);
    }
    else
    {
        /* condition check */
    }

    return (status);
}

static void MCSPI_dmaStart(Spi_JobObjType *jobObj, uint32 baseAddr, uint8 chMode)
{
    uint32 chNum = jobObj->jobCfg_PC.csPin;

    if (jobObj->dmaChIdx == 0U)
    {
        jobObj->dmaChIdx++;
        /* Enable DMA */
        if (SPI_TX_RX_MODE_BOTH == jobObj->extDevCfg->mcspi.txRxMode)
        {
            HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_DMAR, CSL_MCSPI_CH0CONF_DMAR_ENABLED);
            HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_DMAW, CSL_MCSPI_CH0CONF_DMAW_ENABLED);
        }
        else if (SPI_TX_RX_MODE_TX_ONLY == jobObj->extDevCfg->mcspi.txRxMode)
        {
            HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_DMAW, CSL_MCSPI_CH0CONF_DMAW_ENABLED);
        }
        else
        {
            /* condition check */
        }

        /* Manual CS assert */
        if (MCSPI_MODULCTRL_SINGLE_SINGLE == chMode)
        {
            HW_WR_FIELD32((baseAddr + MCSPI_CHCONF(chNum)), CSL_MCSPI_CH0CONF_FORCE, CSL_MCSPI_CH0CONF_FORCE_ASSERT);
        }

        /* Enable channel */
        HW_WR_FIELD32((baseAddr + MCSPI_CHCTRL(chNum)), CSL_MCSPI_CH0CTRL_EN, CSL_MCSPI_CH0CTRL_EN_ACT);

        /** Note: Once the channel is enabled, DMA will trigger its transfer. */
    }
    else
    {
        /* Disable and re-enable channel for the next DMA transfer */
        HW_WR_FIELD32((baseAddr + MCSPI_CHCTRL(chNum)), CSL_MCSPI_CH0CTRL_EN, CSL_MCSPI_CH0CTRL_EN_NACT);
        HW_WR_FIELD32((baseAddr + MCSPI_CHCTRL(chNum)), CSL_MCSPI_CH0CTRL_EN, CSL_MCSPI_CH0CTRL_EN_ACT);
    }
}

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"

#define SPI_START_SEC_ISR_CODE
#include "Spi_MemMap.h"

void Spi_DmaTxIsrHandler(void *args)
{
    Spi_HwUnitObjType *hwUnitObj = (Spi_HwUnitObjType *)args;
    if ((NULL_PTR != hwUnitObj) && (NULL_PTR != hwUnitObj->curJobObj) &&
        (hwUnitObj->curJobObj->extDevCfg->mcspi.txRxMode == SPI_TX_RX_MODE_TX_ONLY))
    {
        Spi_dmaTxIsrHandler_StatusCheck(hwUnitObj);

        /* This channel transfer is complete */
        hwUnitObj->curJobObj->jobResult = SPI_JOB_OK;
        Spi_processChCompletion(hwUnitObj, SPI_JOB_OK);
    }
}

static void Spi_dmaTxIsrHandler_StatusCheck(const Spi_HwUnitObjType *hwUnitObj)
{
    volatile uint32 chStat    = 0U;
    uint32          chNum     = 0U;
    volatile uint32 tempCount = SPI_MAX_TIMEOUT_DURATION;
    if (SPI_MAX_TIMEOUT_DURATION > 8U)
    {
        tempCount = SPI_MAX_TIMEOUT_DURATION / 8U;
    }

    chNum = (uint32)hwUnitObj->curJobObj->jobCfg_PC.csPin;
    do
    {
        if (tempCount <= 0U)
        {
#ifdef SPI_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(tempCount);
        chStat = HW_RD_REG32(hwUnitObj->baseAddr + MCSPI_CHSTAT(chNum));
    } while ((chStat & CSL_MCSPI_CH0STAT_EOT_MASK) == 0U);
    /* no timeout */
}

void Spi_DmaRxIsrHandler(void *args)
{
    Spi_HwUnitObjType *hwUnitObj = (Spi_HwUnitObjType *)NULL_PTR;

    if (args != NULL_PTR)
    {
        hwUnitObj = (Spi_HwUnitObjType *)args;
        if ((NULL_PTR != hwUnitObj) && (NULL_PTR != hwUnitObj->curJobObj) &&
            (hwUnitObj->curJobObj->extDevCfg->mcspi.txRxMode != SPI_TX_RX_MODE_TX_ONLY))
        {
            /* This channel transfer is complete */
            hwUnitObj->curJobObj->jobResult = SPI_JOB_OK;
            Spi_processChCompletion(hwUnitObj, SPI_JOB_OK);
        }
    }
}

#define SPI_STOP_SEC_ISR_CODE
#include "Spi_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* SPI_DMA_ENABLE == STD_ON */
