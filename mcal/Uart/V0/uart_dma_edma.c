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
#include <Cdd_Dma.h>
#include <Cdd_Dma_Priv.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Transmit EDMA channel event queue number                           */
#define CDD_EDMA_UART_TX_EVT_QUEUE_NO (0U)
/** \brief Receive EDMA channel event queue number                            */
#define CDD_EDMA_UART_RX_EVT_QUEUE_NO (1U)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_UART_START_SEC_CODE
#include "Cdd_Uart_MemMap.h"

sint32 Uart_Cdd_dmaInit(CddUart_Handle hUart)
{
    sint32  status = MCAL_SystemP_FAILURE;
    boolean isEdmaInterruptEnabled;

    isEdmaInterruptEnabled =
        (boolean)(((uint32)TRUE == Cdd_Dma_Config.CddDmaDriverHandler[hUart->dmaTxHandleId]->edmaConfig.intrEnable) &&
                  ((uint32)TRUE == Cdd_Dma_Config.CddDmaDriverHandler[hUart->dmaRxHandleId]->edmaConfig.intrEnable));

    if ((boolean)TRUE == (boolean)isEdmaInterruptEnabled)
    {
        /* Register RX interrupt */
        if ((uint32)E_OK == Cdd_Dma_CbkRegister(hUart->dmaRxHandleId, (void *)hUart, UART_edmaIsrRx))
        {
            status = MCAL_SystemP_SUCCESS;
        }

        if (MCAL_SystemP_SUCCESS == status)
        {
            /* Register TX interrupt */
            if ((uint32)E_OK != Cdd_Dma_CbkRegister(hUart->dmaTxHandleId, (void *)hUart, UART_edmaIsrTx))
            {
                status = MCAL_SystemP_FAILURE;
            }
        }
    }
    return status;
}

sint32 Uart_Cdd_dmaDeInit(CddUart_Handle hUart)
{
    sint32  status = MCAL_SystemP_FAILURE;
    boolean isEdmaInterruptEnabled =
        (boolean)(((uint32)TRUE == Cdd_Dma_Config.CddDmaDriverHandler[hUart->dmaTxHandleId]->edmaConfig.intrEnable) &&
                  ((uint32)TRUE == Cdd_Dma_Config.CddDmaDriverHandler[hUart->dmaRxHandleId]->edmaConfig.intrEnable));

    if ((boolean)TRUE == isEdmaInterruptEnabled)
    {
        /* Unregister RX interrupt */
        Cdd_Dma_CbkUnregister(hUart->dmaRxHandleId);

        /* Unregister TX interrupt */
        Cdd_Dma_CbkUnregister(hUart->dmaTxHandleId);

        status = MCAL_SystemP_SUCCESS;
    }

    return status;
}

sint32 Uart_Cdd_dmaWrite(CddUart_Handle hUart, const CddUart_Transaction *transaction)
{
    sint32             status       = MCAL_SystemP_SUCCESS;
    uint32             channelIndex = 0U;
    uint32             paramTx = 0U, paramDummy = 1U;
    uint32             isEdmaEventPending = FALSE;
    Cdd_Dma_ParamEntry edmaTxParam, edmaDummyParam;

    /* Transmit param set configuration */
    edmaTxParam.srcPtr     = (void *)transaction->buf;
    edmaTxParam.destPtr    = (uint8 *)hUart->baseAddr + UART_THR;
    edmaTxParam.aCnt       = (uint16)1U;
    edmaTxParam.bCnt       = (uint16)(transaction->count);
    edmaTxParam.cCnt       = (uint16)1U;
    edmaTxParam.bCntReload = (uint16)edmaTxParam.bCnt;
    edmaTxParam.srcBIdx    = (sint16)edmaTxParam.aCnt;
    edmaTxParam.destBIdx   = (sint16)0;
    edmaTxParam.srcCIdx    = (sint16)0;
    edmaTxParam.destCIdx   = (sint16)0;
    edmaTxParam.opt        = (CDD_EDMA_OPT_TCINTEN_MASK);

    /* Write Tx param set */
    Cdd_Dma_ParamSet(hUart->dmaTxHandleId, channelIndex, paramTx, edmaTxParam);

    /* Dummy param set configuration */
    edmaDummyParam.aCnt       = (uint16)1U;
    edmaDummyParam.bCnt       = (uint16)0U;
    edmaDummyParam.cCnt       = (uint16)0U;
    edmaDummyParam.bCntReload = (uint16)0U;
    edmaDummyParam.srcBIdx    = (sint16)0;
    edmaDummyParam.destBIdx   = (sint16)0;
    edmaDummyParam.srcCIdx    = (sint16)0;
    edmaDummyParam.destCIdx   = (sint16)0;
    edmaDummyParam.opt        = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_STATIC_MASK);

    /* Write Tx Dummy param set */
    Cdd_Dma_ParamSet(hUart->dmaTxHandleId, channelIndex, paramDummy, edmaDummyParam);

    /* Link Dummy param ID */
    Cdd_Dma_LinkChannel(hUart->dmaTxHandleId, paramTx, paramDummy);

    /* Workaround: In case of DMA mode, the UART IP generates the
     * next EDMA event as soon as the FIFO gets emptied or when there are
     * TX threshold level bytes free in FIFO. In the EDMA ISR,
     * the DMA mode is disabled and EDMA channel is disabled.
     * There is a race condition between software (CPU) disabling the DMA
     * mode and the UART IP generating the DMA event to EDMA.
     *
     * In cases when the software is slower (multi-tasking systems or
     * in heavily CPU loaded systems or for lower FIFO trigger levels),
     * the UART IP DMA event gets generated before the CPU could disable
     * the DMA event generation.
     *
     * When this happens, since the EDMA channel is enabled, the EDMA will
     * acknowledge the EDMA event but it doesn't have proper param set to
     * do the actual transfer to the UART FIFO. Hence the event gets lost
     * and the UART IP doesn't generate the next EDMA event unless the FIFO
     * is written. This becomes a deadlock!!
     *
     * To break the dead lock, first we need to identify whether this had
     * happened by checking the UART FIFO level and the EDMA channel status.
     * As per UART IP, in DMA mode, when ever the FIFO is empty or has TX
     * threshold amount of free space it should have raised an DMA event.
     * Hence we check if the UART FIFO has room and see if the event is
     * latched in the EDMA register.
     * So if FIFO is empty and event is not latched, then we are in a
     * deadlock.
     *
     * To recover from the deadlock, we do a manual trigger for the first
     * time and the rest of the transfer is taken care automatically
     * by further UART events.
     */

    if (CDD_EDMA_lld_readEventStatusRegion(Cdd_Dma_Config.CddDmaDriverHandler[hUart->dmaTxHandleId]->baseAddr,
                                           Cdd_Dma_Config.CddDmaDriverHandler[hUart->dmaTxHandleId]->edmaConfig.tcc) ==
        TRUE)
    {
        isEdmaEventPending = TRUE;
    }

    /* Check for FIFO empty and EDMA Event Pending */
    if ((UART_checkCharsAvailInFifo(hUart->baseAddr) == TRUE) && (isEdmaEventPending == FALSE))
    {
        /* Set manual trigger to start UART TX transfer */
        if ((boolean)FALSE == Cdd_Dma_EnableTransferRegion(hUart->dmaTxHandleId, CDD_EDMA_TRIG_MODE_MANUAL))
        {
            status = MCAL_SystemP_FAILURE;
        }
    }
    else
    {
        /* Set event trigger to start UART TX transfer */
        if ((boolean)FALSE == Cdd_Dma_EnableTransferRegion(hUart->dmaTxHandleId, CDD_EDMA_TRIG_MODE_EVENT))
        {
            status = MCAL_SystemP_FAILURE;
        }
    }

    return status;
}

sint32 Uart_Cdd_dmaRead(CddUart_Handle hUart, const CddUart_Transaction *transaction)
{
    sint32             status       = MCAL_SystemP_SUCCESS;
    uint32             channelIndex = CddUartConf_CddUartChannelConfiguration_CddUartChannel_0;
    uint32             paramRx      = 0;
    Cdd_Dma_ParamEntry edmaRxParam;

    /* Receive param set configuration */
    edmaRxParam.srcPtr     = (uint8 *)hUart->baseAddr + UART_RHR;
    edmaRxParam.destPtr    = (void *)transaction->buf;
    edmaRxParam.aCnt       = (uint16)1U;
    edmaRxParam.bCnt       = (uint16)(transaction->count);
    edmaRxParam.cCnt       = (uint16)1U;
    edmaRxParam.bCntReload = (uint16)edmaRxParam.bCnt;
    edmaRxParam.srcBIdx    = (sint16)0;
    edmaRxParam.destBIdx   = (sint16)edmaRxParam.aCnt;
    edmaRxParam.srcCIdx    = (sint16)0;
    edmaRxParam.destCIdx   = (sint16)0;
    edmaRxParam.opt        = (CDD_EDMA_OPT_TCINTEN_MASK);

    /* Write Rx param set */
    Cdd_Dma_ParamSet(hUart->dmaRxHandleId, channelIndex, paramRx, edmaRxParam);

    /* Set event trigger to start UART RX transfer */
    if ((boolean)FALSE == Cdd_Dma_EnableTransferRegion(hUart->dmaRxHandleId, CDD_EDMA_TRIG_MODE_EVENT))
    {
        status = MCAL_SystemP_FAILURE;
    }

    return status;
}

void UART_edmaIsrTx(void *args)
{
    CddUart_Handle hUart;
    uint32         lineStatus;

    /* Check parameters */
    if (NULL_PTR != args)
    {
        hUart = (CddUart_Handle)args;
        /* Make sure data is sent out from FIFO and shift register */
        do
        {
            lineStatus = UART_readLineStatus(hUart->baseAddr);
        } while ((uint32)(UART_LSR_TX_FIFO_E_MASK | UART_LSR_TX_SR_E_MASK) !=
                 (lineStatus & (uint32)(UART_LSR_TX_FIFO_E_MASK | UART_LSR_TX_SR_E_MASK)));
        hUart->writeTrans->status = UART_TRANSFER_STATUS_SUCCESS;
        hUart->writeTrans         = (CddUart_Transaction *)NULL_PTR;
        hUart->writeSizeRemaining = 0;
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
        hUart->readSizeRemaining = 0;
        Uart_Cdd_readCompleteCallback(hUart);
    }

    return;
}

#define CDD_UART_STOP_SEC_CODE
#include "Cdd_Uart_MemMap.h"

#endif
