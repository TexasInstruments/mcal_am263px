/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file uart_dma_edma.c
 *
 *  \brief File containing EDMA Driver APIs implementation for UART.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <uart_dma.h>
#if (CDD_UART_DMA_ENABLE == STD_ON)
#include <Cdd_Dma_Priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief Transmit EDMA channel event queue number                           */
#define CDD_EDMA_UART_TX_EVT_QUEUE_NO (0U)
/** \brief Receive EDMA channel event queue number                            */
#define CDD_EDMA_UART_RX_EVT_QUEUE_NO (1U)

#define UART_LCR ((uint32)0xcU)
#define UART_LSR ((uint32)0x14U)

#define UART_LSR_RX_FIFO_E_SHIFT             ((uint32)0U)
#define UART_LSR_RX_FIFO_E_MASK              ((uint32)0x00000001U)
#define UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_1 ((uint32)1U)
#define UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 ((uint32)0U)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_UART_START_SEC_CODE
#include "Cdd_Uart_MemMap.h"

sint32 Uart_Cdd_dmaInit(CddUart_Handle hUart)
{
    sint32  status = MCAL_SystemP_FAILURE;
    boolean isEdmaInterruptEnabled;

    /* Can be checked if interrupt is enabled */
    isEdmaInterruptEnabled =
        (boolean)(((uint32)TRUE ==
                   CddDmaDriverHandler.CddDmaDriverHandler[hUart->dmaTxHandleId]->edmaConfig.intrEnable) &&
                  ((uint32)TRUE ==
                   CddDmaDriverHandler.CddDmaDriverHandler[hUart->dmaRxHandleId]->edmaConfig.intrEnable));

    if ((uint32)TRUE == isEdmaInterruptEnabled)
    {
        /* Register RX Interrupt */
        if ((boolean)E_OK == Cdd_Dma_CbkRegister(hUart->dmaRxHandleId, (void *)hUart, UART_edmaIsrRx))
        {
            status = MCAL_SystemP_SUCCESS;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        /* Register TX interrupt */
        if ((boolean)E_NOT_OK == Cdd_Dma_CbkRegister(hUart->dmaTxHandleId, (void *)hUart, UART_edmaIsrTx))
        {
            status = MCAL_SystemP_FAILURE;
        }
    }
    return status;
}

sint32 Uart_Cdd_dmaDeInit(CddUart_Handle hUart)
{
    sint32  status = MCAL_SystemP_FAILURE;
    boolean isEdmaInterruptEnabled;

    /* Check if interrupt is enabled */
    isEdmaInterruptEnabled =
        (boolean)(((uint32)TRUE ==
                   CddDmaDriverHandler.CddDmaDriverHandler[hUart->dmaTxHandleId]->edmaConfig.intrEnable) &&
                  ((uint32)TRUE ==
                   CddDmaDriverHandler.CddDmaDriverHandler[hUart->dmaRxHandleId]->edmaConfig.intrEnable));

    if ((uint32)TRUE == isEdmaInterruptEnabled)
    {
        /* Unregister RX interrupt */
        Cdd_Dma_CbkUnregister(hUart->dmaRxHandleId);

        /* Unregister TX interrupt */
        Cdd_Dma_CbkUnregister(hUart->dmaTxHandleId);

        status = MCAL_SystemP_SUCCESS;
    }
    return status;
}

static inline void UART_disableRxDma(const MCAL_CSL_sciRegs *pSCIRegs)
{
    /* Disable the Rx DMA All and Rx DMA */
    HW_WR_REG32(&pSCIRegs->SCICLEARINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCICLEARINT_CLR_RX_DMA_ALL, 1U));
    HW_WR_REG32(&pSCIRegs->SCICLEARINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCICLEARINT_CLR_RX_DMA, 1U));
}

static inline void UART_enableRxDma(const MCAL_CSL_sciRegs *pSCIRegs)
{
    /* Enable the Rx DMA All and Rx DMA */
    HW_WR_REG32(&pSCIRegs->SCISETINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCISETINT_SET_RX_DMA_ALL, 1U));
    HW_WR_REG32(&pSCIRegs->SCISETINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCISETINT_SET_RX_DMA, 1U));
}

static inline void UART_disableTxDma(const MCAL_CSL_sciRegs *pSCIRegs)
{
    /* Disable the Transmit DMA */
    HW_WR_REG32(&pSCIRegs->SCICLEARINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCICLEARINT_CLR_TX_DMA, 1U));
}

static inline void UART_enableTxDma(const MCAL_CSL_sciRegs *pSCIRegs)
{
    /* Enable Transmit DMA */
    HW_WR_REG32(&pSCIRegs->SCISETINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCISETINT_SET_TX_DMA, 1U));
}

sint32 Uart_Cdd_dmaWrite(CddUart_Handle hUart, const CddUart_Transaction *transaction)
{
    sint32             status       = MCAL_SystemP_SUCCESS;
    uint32             channelIndex = 0U, paramIndex = 0U;
    Cdd_Dma_ParamEntry edmaTxParam;

    /* Disable the UART Transfer DMA mode */
    UART_disableTxDma(hUart->pSCIRegs);

    /* Transmit param set configuration */
    edmaTxParam.srcPtr     = (void *)transaction->buf;
    edmaTxParam.destPtr    = (void *)(&hUart->pSCIRegs->SCITD);
    edmaTxParam.aCnt       = (uint16)1U;
    edmaTxParam.bCnt       = (uint16)(transaction->count);
    edmaTxParam.cCnt       = (uint16)1U;
    edmaTxParam.bCntReload = (uint16)0U;
    edmaTxParam.srcBIdx    = (sint16)1;
    edmaTxParam.destBIdx   = (sint16)0;
    edmaTxParam.srcCIdx    = (sint16)0;
    edmaTxParam.destCIdx   = (sint16)0;
    edmaTxParam.opt        = CDD_EDMA_TPCC_OPT_TCINTEN_MASK;

    /* Write Tx param set */
    Cdd_Dma_ParamSet(hUart->dmaTxHandleId, channelIndex, paramIndex, edmaTxParam);

    /* Set event trigger to start UART TX transfer */
    if ((boolean)FALSE == Cdd_Dma_EnableTransferRegion(hUart->dmaTxHandleId, CDD_EDMA_TRIG_MODE_EVENT))
    {
        status = MCAL_SystemP_FAILURE;
    }
    else
    {
        /* Enable the UART to operate in Transfer DMA mode */
        UART_enableTxDma(hUart->pSCIRegs);
    }

    return status;
}

sint32 Uart_Cdd_dmaRead(CddUart_Handle hUart, const CddUart_Transaction *transaction)
{
    sint32             status       = MCAL_SystemP_SUCCESS;
    uint32             channelIndex = 0U, paramIndex = 0U;
    Cdd_Dma_ParamEntry edmaParam;

    /* Disable UART receive DMA mode */
    UART_disableRxDma(hUart->pSCIRegs);

    /* Receive param set configuration */
    edmaParam.srcPtr     = (void *)(&hUart->pSCIRegs->SCIRD);
    edmaParam.destPtr    = (void *)transaction->buf;
    edmaParam.aCnt       = (uint16)1U;
    edmaParam.bCnt       = (uint16)(transaction->count);
    edmaParam.cCnt       = (uint16)1U;
    edmaParam.bCntReload = (uint16)0U;
    edmaParam.srcBIdx    = (sint16)0;
    edmaParam.destBIdx   = (sint16)1;
    edmaParam.srcCIdx    = (sint16)0;
    edmaParam.destCIdx   = (sint16)0;
    edmaParam.opt        = CDD_EDMA_TPCC_OPT_TCINTEN_MASK;

    /* Write Rx param set */
    Cdd_Dma_ParamSet(hUart->dmaRxHandleId, channelIndex, paramIndex, edmaParam);

    /* Set event trigger to start UART RX transfer */
    if ((boolean)FALSE == Cdd_Dma_EnableTransferRegion(hUart->dmaRxHandleId, CDD_EDMA_TRIG_MODE_EVENT))
    {
        status = MCAL_SystemP_FAILURE;
    }
    else
    {
        /* Enable the UART to operate in receive DMA mode */
        UART_enableRxDma(hUart->pSCIRegs);
    }

    return status;
}

void UART_edmaIsrTx(void *args)
{
    CddUart_Handle hUart;

    /* Check parameters */
    if (NULL_PTR != args)
    {
        hUart                     = (CddUart_Handle)args;
        hUart->writeTrans->status = UART_TRANSFER_STATUS_SUCCESS;
        hUart->writeTrans         = (CddUart_Transaction *)NULL_PTR;
        Uart_Cdd_writeCompleteCallback(hUart);
    }
    return;
}

void UART_edmaIsrRx(void *args)
{
    CddUart_Handle hUart;

    /* Check parameters */
    if (NULL_PTR != args)
    {
        hUart                    = (CddUart_Handle)args;
        hUart->readTrans->status = UART_TRANSFER_STATUS_SUCCESS;
        hUart->readTrans         = (CddUart_Transaction *)NULL_PTR;
        Uart_Cdd_readCompleteCallback(hUart);
    }

    return;
}

#define CDD_UART_STOP_SEC_CODE
#include "Cdd_Uart_MemMap.h"

#endif
