/*
 * Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file   uart.c
 *
 *  \brief  This file contains the implementation of UART driver functions
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <hw_types.h>
#include <uart_dma.h>
#include "SchM_Cdd_Uart.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Timeout in ms used for TX FIFO empty at the time of delete. Three
 *  seconds is more than sufficient to transfer 64 bytes (FIFO size) at the
 *  lowest baud rate of 2400.
 */
#define UART_TRANSMITEMPTY_TRIALCOUNT (6000U)

#define UARTSCI_TIMING_MODE_SYNC  ((uint32)0U)
#define UARTSCI_TIMING_MODE_ASYNC ((uint32)1U)

#define UARTSCI_CLOCK_MODE_EXTERNAL ((uint32)0U)
#define UARTSCI_CLOCK_MODE_INTERNAL ((uint32)1U)

#define UARTSCI_COMM_MODE_IDLE    ((uint32)0U)
#define UARTSCI_COMM_MODE_ADDRESS ((uint32)1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* Driver internal functions */

#if (STD_ON == CDD_UART_DMA_ENABLE)
static boolean UART_writeCancelDmaNoCB(CddUart_Handle hUart);
static boolean UART_readCancelDmaNoCB(CddUart_Handle hUart);
#endif
static sint32 UART_writePolling(CddUart_Handle hUart, CddUart_Transaction *trans);
static sint32 UART_writeInterrupt(CddUart_Handle hUart, CddUart_Transaction *trans);

static sint32 UART_readPolling(CddUart_Handle hUart, CddUart_Transaction *trans);
static sint32 UART_readInterrupt(CddUart_Handle hUart);

static void   UART_configInstance(CddUart_Handle hUart);
static sint32 UART_checkTransaction(CddUart_Transaction *trans);

/* Low level HW functions */
static inline void   UART_txChar(CddUart_Handle hUart);
static inline void   UART_rxChar(CddUart_Handle hUart);
static inline uint32 UART_isTxRdy(const MCAL_CSL_sciRegs *pSCIRegs);
static inline uint32 UART_isRxRdy(const MCAL_CSL_sciRegs *pSCIRegs);
static inline void   UART_txIntrEnable(MCAL_CSL_sciRegs *pSCIRegs);
static inline void   UART_rxIntrEnable(MCAL_CSL_sciRegs *pSCIRegs);
static inline void   UART_txIntrDisable(const MCAL_CSL_sciRegs *pSCIRegs);
static inline void   UART_rxIntrDisable(const MCAL_CSL_sciRegs *pSCIRegs);
static inline uint32 UART_isTxIntrEnabled(const MCAL_CSL_sciRegs *pSCIRegs);
static inline uint32 UART_isRxIntrEnabled(const MCAL_CSL_sciRegs *pSCIRegs);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_UART_START_SEC_CODE
#include "Cdd_Uart_MemMap.h"

sint32 Uart_Cdd_init(CddUart_Handle hUart)
{
    sint32             status = MCAL_SystemP_SUCCESS;
    CddUart_InitHandle hUartInit;

    if ((hUart == NULL_PTR) || (hUart->hUartInit == NULL_PTR))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }
    else
    {
        if (hUart->state != MCAL_STATE_RESET)
        {
            status = MCAL_SystemP_INVALID_STATE;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        hUart->state = MCAL_STATE_BUSY;
        hUartInit    = hUart->hUartInit;

        /* All of MCAL_LLD_PARAMS_CHECKs combined */
        if ((hUart->baseAddr == (uint32)0U) || (hUartInit->inputClkFreq == (uint32)0U) ||
            (hUartInit->baudRate == (uint32)0U) || (!(IS_DATA_LENGTH_VALID(hUartInit->dataLength))) ||
            (!(IS_STOP_BITS_VALID(hUartInit->stopBits))) || (!(IS_PARITY_TYPE_VALID(hUartInit->parityType))))
        {
            status = MCAL_SystemP_INVALID_PARAM;
        }
        else
        {
            /* Configure the UART instance parameters */
            UART_configInstance(hUart);

#if (STD_ON == CDD_UART_DMA_ENABLE)
            if (CDD_UART_MODE_DMA == hUart->hUartInit->transferMode)
            {
                status = Uart_Cdd_dmaInit(hUart);
            }
#endif

            if (NULL_PTR != hUart->pSCIRegs)
            {
                /* Start the SCI */
                HW_SET_FIELD32(hUart->pSCIRegs->SCIGCR1, MCAL_CSL_SCI_SCIGCR1_SW_NRESET, 1U);
            }

            if (MCAL_SystemP_SUCCESS == status)
            {
                hUart->state = MCAL_STATE_READY;
            }
        }
    }

    if (MCAL_SystemP_SUCCESS != status)
    {
        /* Free-up resources in case of error */
        (void)Uart_Cdd_deInit(hUart);
    }

    return (status);
}

sint32 Uart_Cdd_deInit(CddUart_Handle hUart)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    if (NULL_PTR != hUart)
    {
        hUart->state = MCAL_STATE_BUSY;

        /* Update current tick value to perform timeout operation */

        /* Flush TX FIFO */
        (void)Uart_Cdd_flushTxFifo(hUart);

        /* Disable UART and interrupts. */
        HW_WR_REG32(&hUart->pSCIRegs->SCICLEARINT, 0xFFFFFFFFU);

#if (STD_ON == CDD_UART_DMA_ENABLE)
        if (CDD_UART_MODE_DMA == hUart->hUartInit->transferMode)
        {
            status = Uart_Cdd_dmaDeInit(hUart);
        }
#endif

        hUart->state = MCAL_STATE_RESET;
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    return status;
}

sint32 Uart_Cdd_writeEx(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        /* Check if any transaction is in progress */
        if (NULL_PTR != hUart->writeTrans)
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_INUSE;
            status        = MCAL_SystemP_FAILURE;
        }
        else
        {
            /* Initialize transaction params */
            hUart->writeTrans          = trans;
            hUart->writeBuf            = trans->buf;
            hUart->writeTrans->timeout = trans->timeout;
            hUart->writeCount          = 0U;
            hUart->writeSizeRemaining  = trans->count;
        }

        SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* Polled mode */
            status       = UART_writePolling(hUart, trans);
            hUart->state = MCAL_STATE_READY;
        }
    }

    return (status);
}

sint32 Uart_Cdd_writeIntrEx(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        /* Check if any transaction is in progress */
        if (NULL_PTR != hUart->writeTrans)
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_INUSE;
            status        = MCAL_SystemP_FAILURE;
        }
        else
        {
            /* Initialize transaction params */
            hUart->writeTrans          = trans;
            hUart->writeBuf            = trans->buf;
            hUart->writeTrans->timeout = trans->timeout;
            hUart->writeCount          = 0U;
            hUart->writeSizeRemaining  = trans->count;
        }

        SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* Interrupt mode */
            status       = UART_writeInterrupt(hUart, trans);
            hUart->state = MCAL_STATE_READY;
        }
    }

    return (status);
}

#if (STD_ON == CDD_UART_DMA_ENABLE)
sint32 Uart_Cdd_writeDmaEx(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        /* Check if any transaction is in progress */
        if (NULL_PTR != hUart->writeTrans)
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_INUSE;
            status        = MCAL_SystemP_FAILURE;
        }
        else
        {
            /* Initialize transaction params */
            hUart->writeTrans          = trans;
            hUart->writeBuf            = trans->buf;
            hUart->writeTrans->timeout = trans->timeout;
            hUart->writeCount          = 0U;
            hUart->writeSizeRemaining  = trans->count;
        }

        SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* DMA mode */
            status       = Uart_Cdd_dmaWrite(hUart, trans);
            hUart->state = MCAL_STATE_READY;
        }
    }

    return (status);
}
#endif

sint32 Uart_Cdd_readEx(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_FAILURE;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        /* Check if any transaction is in progress */
        if (NULL_PTR != hUart->readTrans)
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_INUSE;
            status        = MCAL_SystemP_FAILURE;
        }
        else
        {
            /* Initialize transaction params */
            hUart->readTrans          = trans;
            hUart->readBuf            = trans->buf;
            hUart->readSizeRemaining  = trans->count;
            hUart->readTrans->timeout = trans->timeout;
            hUart->readCount          = 0U;
            hUart->rxTimeoutCnt       = 0U;
            hUart->readErrorCnt       = 0U;
        }

        SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* Polled mode */
            status       = UART_readPolling(hUart, trans);
            hUart->state = MCAL_STATE_READY;
        }
    }

    return (status);
}

sint32 Uart_Cdd_readIntrEx(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_FAILURE;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        /* Check if any transaction is in progress */
        if (NULL_PTR != hUart->readTrans)
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_INUSE;
            status        = MCAL_SystemP_FAILURE;
        }
        else
        {
            /* Initialize transaction params */
            hUart->readTrans          = trans;
            hUart->readBuf            = trans->buf;
            hUart->readSizeRemaining  = trans->count;
            hUart->readTrans->timeout = trans->timeout;
            hUart->readCount          = 0U;
            hUart->rxTimeoutCnt       = 0U;
            hUart->readErrorCnt       = 0U;
        }

        SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* Interrupt mode */
            status       = UART_readInterrupt(hUart);
            hUart->state = MCAL_STATE_READY;
        }
    }

    return (status);
}

#if (STD_ON == CDD_UART_DMA_ENABLE)
sint32 Uart_Cdd_readDmaEx(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_FAILURE;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        /* Check if any transaction is in progress */
        if (NULL_PTR != hUart->readTrans)
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_INUSE;
            status        = MCAL_SystemP_FAILURE;
        }
        else
        {
            /* Initialize transaction params */
            hUart->readTrans          = trans;
            hUart->readBuf            = trans->buf;
            hUart->readSizeRemaining  = trans->count;
            hUart->readTrans->timeout = trans->timeout;
            hUart->readCount          = 0U;
            hUart->rxTimeoutCnt       = 0U;
            hUart->readErrorCnt       = 0U;
        }

        SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* DMA mode */
            status       = Uart_Cdd_dmaRead(hUart, trans);
            hUart->state = MCAL_STATE_READY;
        }
    }

    return (status);
}
#endif

sint32 Uart_Cdd_writeCancel(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (UART_writeCancelNoCB(hUart) == (boolean)TRUE)
        {
            hUart->writeTrans->status = UART_TRANSFER_STATUS_CANCELLED;
            hUart->state              = MCAL_STATE_READY;
            hUart->writeTrans         = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_writeCompleteCallback(hUart);
        }
        else
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_OTH;
            status        = MCAL_SystemP_FAILURE;
        }
    }

    return (status);
}

#if (STD_ON == CDD_UART_DMA_ENABLE)
sint32 Uart_Cdd_writeCancelDma(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (UART_writeCancelDmaNoCB(hUart) == (boolean)TRUE)
        {
            hUart->writeTrans->status = UART_TRANSFER_STATUS_CANCELLED;
            hUart->state              = MCAL_STATE_READY;
            hUart->writeTrans         = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_writeCompleteCallback(hUart);
        }
        else
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_OTH;
            status        = MCAL_SystemP_FAILURE;
        }
    }

    return (status);
}
#endif

sint32 Uart_Cdd_readCancel(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (UART_readCancelNoCB(hUart) == (boolean)TRUE)
        {
            hUart->readTrans->status = UART_TRANSFER_STATUS_CANCELLED;
            hUart->state             = MCAL_STATE_READY;
            hUart->readTrans         = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_readCompleteCallback(hUart);
        }
        else
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_OTH;
            status        = MCAL_SystemP_FAILURE;
        }
    }

    return (status);
}

#if (STD_ON == CDD_UART_DMA_ENABLE)
sint32 Uart_Cdd_readCancelDma(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Check parameters */
    if ((NULL_PTR == hUart) || (NULL_PTR == trans))
    {
        status = MCAL_SystemP_INVALID_PARAM;
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (hUart->state == MCAL_STATE_READY)
        {
            status = UART_checkTransaction(trans);
        }
        else
        {
            status = MCAL_SystemP_BUSY;
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        if (UART_readCancelDmaNoCB(hUart) == (boolean)TRUE)
        {
            hUart->readTrans->status = UART_TRANSFER_STATUS_CANCELLED;
            hUart->state             = MCAL_STATE_READY;
            hUart->readTrans         = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_readCompleteCallback(hUart);
        }
        else
        {
            trans->status = UART_TRANSFER_STATUS_ERROR_OTH;
            status        = MCAL_SystemP_FAILURE;
        }
    }

    return (status);
}
#endif

sint32 Uart_Cdd_flushTxFifo(CddUart_Handle hUart)
{
    sint32          status = MCAL_SystemP_SUCCESS;
    uint32          isTxEmpty;
    uint32          timeoutElapsed = FALSE;
    volatile uint32 tempCount      = UART_TRANSMITEMPTY_TRIALCOUNT;
    if (UART_TRANSMITEMPTY_TRIALCOUNT > 8U)
    {
        tempCount = UART_TRANSMITEMPTY_TRIALCOUNT / 8U;
    }

    while ((uint32)FALSE == timeoutElapsed)
    {
        /* Get TX status */
        isTxEmpty = HW_GET_FIELD(hUart->pSCIRegs->SCIFLR, MCAL_CSL_SCI_SCIFLR_TX_EMPTY);
        if ((uint32)TRUE == isTxEmpty)
        {
            /* TX is empty */
            break;
        }

        if (tempCount <= 0U)
        {
            /* timeout occured */
            timeoutElapsed = TRUE;
            status         = MCAL_SystemP_TIMEOUT;
        }
        MCAL_SW_DELAY(tempCount);
    }

    return status;
}

boolean UART_writeCancelNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;

    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();

    /* Disable Tx interrupt */
    UART_txIntrDisable(hUart->pSCIRegs);

    /* Return if there is no write. */
    if ((hUart->writeSizeRemaining) == (uint32)0U)
    {
        retVal = (boolean)FALSE;
    }
    else
    {
        /* Reset the write buffer so we can pass it back */
        hUart->writeBuf = (const uint8 *)hUart->writeBuf - hUart->writeCount;
        if (hUart->writeTrans != NULL_PTR)
        {
            hUart->writeTrans->count = (uint32)(hUart->writeCount);
        }

        /* Set size = 0 to prevent writing and restore interrupts. */
        hUart->writeSizeRemaining = 0;
    }

    SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();

    return (retVal);
}

#if (STD_ON == CDD_UART_DMA_ENABLE)
static boolean UART_writeCancelDmaNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;

    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    /* Disable Tx interrupt */
    UART_txIntrDisable(hUart->pSCIRegs);

    /* Return if there is no write. */
    if ((hUart->writeSizeRemaining) == (uint32)0U)
    {
        retVal = (boolean)FALSE;
    }
    else
    {
        /* Disable DMA TX channel */
        (void)Cdd_Dma_DisableTransferRegion(hUart->dmaTxHandleId, CDD_EDMA_TRIG_MODE_EVENT);
        if (hUart->writeTrans != NULL_PTR)
        {
            hUart->writeTrans->count = (uint32)(hUart->writeCount);
        }

        /* Set size = 0 to prevent writing and restore interrupts. */
        hUart->writeSizeRemaining = 0;
    }

    SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    return (retVal);
}
#endif

boolean UART_readCancelNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;

    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    /* Disable Rx interrupt */
    UART_rxIntrDisable(hUart->pSCIRegs);

    if (hUart->readSizeRemaining == (uint32)0U)
    {
        retVal = (boolean)FALSE;
    }
    else
    {
        /* Reset the read buffer so we can pass it back */
        hUart->readBuf = (uint8 *)hUart->readBuf - hUart->readCount;
        if (hUart->readTrans != NULL_PTR)
        {
            hUart->readTrans->count = hUart->readCount;
        }

        /* Set size = 0 to prevent reading and restore interrupts. */
        hUart->readSizeRemaining = 0;
    }

    SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    return (retVal);
}

#if (STD_ON == CDD_UART_DMA_ENABLE)
static boolean UART_readCancelDmaNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;

    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    /* Disable Rx interrupt */
    UART_rxIntrDisable(hUart->pSCIRegs);

    if (hUart->readSizeRemaining == (uint32)0U)
    {
        retVal = (boolean)FALSE;
    }
    else
    {
        /* Disable DMA RX channel */
        (void)Cdd_Dma_DisableTransferRegion(hUart->dmaRxHandleId, CDD_EDMA_TRIG_MODE_EVENT);
        if (hUart->readTrans != NULL_PTR)
        {
            hUart->readTrans->count = hUart->readCount;
        }

        /* Set size = 0 to prevent reading and restore interrupts. */
        hUart->readSizeRemaining = 0;
    }

    SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    return (retVal);
}
#endif

static sint32 UART_writePolling(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32          retVal         = MCAL_SystemP_SUCCESS;
    uint32          timeoutElapsed = FALSE;
    volatile uint32 tempCount      = trans->timeout;
    if (trans->timeout > 8U)
    {
        tempCount = trans->timeout / 8U;
    }

    while ((FALSE == timeoutElapsed) && ((uint32)0U != hUart->writeSizeRemaining))
    {
        /* Transfer data */
        if (UART_isTxRdy(hUart->pSCIRegs) != (uint32)0U)
        {
            UART_txChar(hUart);
        }

        if (tempCount <= 0U)
        {
            /* timeout occured */
            timeoutElapsed = TRUE;
        }
        MCAL_SW_DELAY(tempCount);
    }

    if ((uint32)0U == hUart->writeSizeRemaining)
    {
        retVal            = MCAL_SystemP_SUCCESS;
        trans->status     = UART_TRANSFER_STATUS_SUCCESS;
        hUart->writeTrans = (CddUart_Transaction *)NULL_PTR;
    }
    else
    {
        /* Return MCAL_SystemP_TIMEOUT so that application gets whatever bytes are
         * transmitted. Set the trans status to timeout so that
         * application can handle the timeout. */
        retVal            = MCAL_SystemP_TIMEOUT;
        trans->status     = UART_TRANSFER_STATUS_TIMEOUT;
        trans->count      = hUart->writeCount;
        hUart->writeTrans = (CddUart_Transaction *)NULL_PTR;
    }

    return (retVal);
}

static sint32 UART_writeInterrupt(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /****************************************************************
     * Normal Mode: We always need to send out the first character
     * because the Transmit interrupt is only generated after the
     * first transfer from the TD to the TXSHF
     ****************************************************************/
    /* Wait for Tx Ready */
    while (UART_isTxRdy(hUart->pSCIRegs) == (uint32)0U)
    {
    }

    /* Send the first char */
    UART_txChar(hUart);

    /* Was it just one data to send? */
    if (hUart->writeSizeRemaining == (uint32)0U)
    {
        status            = MCAL_SystemP_SUCCESS;
        trans->status     = UART_TRANSFER_STATUS_SUCCESS;
        hUart->writeTrans = (CddUart_Transaction *)NULL_PTR;
        Uart_Cdd_writeCompleteCallback(hUart);
    }
    else
    {
        /* Enable Tx interrupt */
        UART_txIntrEnable(hUart->pSCIRegs);

        status = MCAL_SystemP_SUCCESS;
    }

    return status;
}

static sint32 UART_readPolling(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 retVal         = MCAL_SystemP_SUCCESS;
    uint32 timeoutElapsed = FALSE;

    volatile uint32 tempCount = trans->timeout;
    if (trans->timeout > 8U)
    {
        tempCount = trans->timeout / 8U;
    }

    while ((FALSE == timeoutElapsed) && ((uint32)0U != hUart->readSizeRemaining))
    {
        /* Read data when ready */
        if (UART_isRxRdy(hUart->pSCIRegs) != (uint32)0U)
        {
            UART_rxChar(hUart);
        }

        if (tempCount <= 0U)
        {
            /* timeout occured */
            timeoutElapsed = TRUE;
        }
        MCAL_SW_DELAY(tempCount);
    }

    if ((hUart->readSizeRemaining == (uint32)0U) && (hUart->readErrorCnt == (uint32)0U) &&
        (hUart->rxTimeoutCnt == (uint32)0U))
    {
        retVal           = MCAL_SystemP_SUCCESS;
        trans->status    = UART_TRANSFER_STATUS_SUCCESS;
        hUart->readTrans = (CddUart_Transaction *)NULL_PTR;
    }
    else
    {
        /* Return MCAL_SystemP_TIMEOUT so that application gets whatever bytes are
         * transmitted. Set the trans status to timeout so that
         * application can handle the timeout. */
        retVal           = MCAL_SystemP_TIMEOUT;
        trans->status    = UART_TRANSFER_STATUS_TIMEOUT;
        trans->count     = hUart->readCount;
        hUart->readTrans = (CddUart_Transaction *)NULL_PTR;
    }

    return (retVal);
}

static sint32 UART_readInterrupt(CddUart_Handle hUart)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    /* Enable Rx interrupt */
    UART_rxIntrEnable(hUart->pSCIRegs);

    status = MCAL_SystemP_SUCCESS;

    return status;
}

static void UART_configInstance(CddUart_Handle hUart)
{
    MCAL_CSL_sciRegs  *pSCIRegs;
    uint32             regVal;
    uint32             divisionFactor = 16U;
    CddUart_InitHandle hUartInit;

    pSCIRegs        = (MCAL_CSL_sciRegs *)hUart->baseAddr;
    hUartInit       = hUart->hUartInit;
    hUart->pSCIRegs = pSCIRegs;

    /* Enable SCI by setting the RESET bit to 1 */
    HW_SET_FIELD32(pSCIRegs->SCIGCR0, MCAL_CSL_SCI_SCIGCR0_RESET, 1U);
    /* Clear the SWnRST bit to 0 before SCI is configured */
    HW_SET_FIELD32(pSCIRegs->SCIGCR1, MCAL_CSL_SCI_SCIGCR1_SW_NRESET, 0U);

    /* Disable and clear interrupts */
    HW_WR_REG32(&pSCIRegs->SCICLEARINT, 0xFFFFFFFFU);
    HW_WR_REG32(&pSCIRegs->SCICLEARINTLVL, 0xFFFFFFFFU);

    /*
     * Configure SCI
     */
    /* TX enable */
    regVal  = 0U;
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_TXENA, 1U);
    HW_SET_FIELD32(pSCIRegs->SCIPIO0, MCAL_CSL_SCI_SCIPIO0_TX_FUNC, 1U);
    /* RX enable */
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_RXENA, 1U);
    HW_SET_FIELD32(pSCIRegs->SCIPIO0, MCAL_CSL_SCI_SCIPIO0_RX_FUNC, 1U);
    /* Clock settings */
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_CLOCK, UARTSCI_CLOCK_MODE_INTERNAL);
    HW_SET_FIELD32(pSCIRegs->SCIPIO0, MCAL_CSL_SCI_SCIPIO0_CLK_FUNC, UARTSCI_CLOCK_MODE_INTERNAL);
    /* Misc modes */
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_TIMING_MODE, UARTSCI_TIMING_MODE_ASYNC);
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_COMM_MODE, UARTSCI_COMM_MODE_IDLE);
    /* Stop bit */
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_STOP, hUartInit->stopBits);
    /* Parity */
    if (hUartInit->parityType == CDD_UART_PARITY_EVEN)
    {
        regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_PARITY_ENA, 1U);
        regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_PARITY, 1U);
    }
    else if (hUartInit->parityType == CDD_UART_PARITY_ODD)
    {
        regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_PARITY_ENA, 1U);
        regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_PARITY, 0U);
    }
    else
    {
        regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCIGCR1_PARITY_ENA, 0U);
    }
    HW_WR_REG32(&pSCIRegs->SCIGCR1, regVal);
    /* Data length */
    HW_WR_REG32(&pSCIRegs->SCICHAR, MCAL_CSL_FMK(MCAL_CSL_SCI_SCICHAR_CHAR, hUartInit->dataLength));
    hUart->shiftJustification =
        (uint8)CDD_UART_WORD_LENGTH_8 - (uint8)hUartInit->dataLength; /* 8-bit: 0 shift, 7-bit: 1 shift etc... */
    /* Baud rate */
    regVal = (hUart->hUartInit->inputClkFreq / (hUartInit->baudRate * divisionFactor)) - 1U;
    HW_WR_REG32(&pSCIRegs->SCIBAUD, regVal);

    /* Enable Error Interrupts: Framing Error, Overrun Error, Parity Error */
    regVal  = 0U;
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCISETINT_SET_PE_INT, 1U);
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCISETINT_SET_OE_INT, 1U);
    regVal |= MCAL_CSL_FMK(MCAL_CSL_SCI_SCISETINT_SET_FE_INT, 1U);
    HW_WR_REG32(&pSCIRegs->SCISETINT, regVal);

    return;
}

static sint32 UART_checkTransaction(CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    if ((uint32)0U == trans->count)
    {
        /* Transfer count should be positive */
        trans->status = UART_TRANSFER_STATUS_ERROR_OTH;
        status        = MCAL_SystemP_FAILURE;
    }
    if (NULL_PTR == trans->buf)
    {
        status = MCAL_SystemP_FAILURE;
    }

    return (status);
}

static inline void UART_txChar(CddUart_Handle hUart)
{
    uint8 txCh;

    txCh = *((const uint8 *)hUart->writeBuf);
    HW_SET_FIELD32(hUart->pSCIRegs->SCITD, MCAL_CSL_SCI_SCITD_TD, txCh);
    hUart->writeSizeRemaining--;
    hUart->writeBuf = (uint8 *)hUart->writeBuf + 1;
    hUart->writeCount++;

    return;
}

static inline void UART_rxChar(CddUart_Handle hUart)
{
    uint8 rxCh;

    rxCh                         = (uint8)HW_GET_FIELD(hUart->pSCIRegs->SCIRD, MCAL_CSL_SCI_SCIRD_RD);
    rxCh                       >>= hUart->shiftJustification;
    *((uint8 *)hUart->readBuf)   = rxCh;
    hUart->readSizeRemaining--;
    hUart->readBuf = (uint8 *)hUart->readBuf + 1;
    hUart->readCount++;

    return;
}

static inline uint32 UART_isTxRdy(const MCAL_CSL_sciRegs *pSCIRegs)
{
    return HW_GET_FIELD(pSCIRegs->SCIFLR, MCAL_CSL_SCI_SCIFLR_TXRDY);
}

static inline uint32 UART_isRxRdy(const MCAL_CSL_sciRegs *pSCIRegs)
{
    return HW_GET_FIELD(pSCIRegs->SCIFLR, MCAL_CSL_SCI_SCIFLR_RXRDY);
}

static inline void UART_txIntrEnable(MCAL_CSL_sciRegs *pSCIRegs)
{
    HW_SET_FIELD32(pSCIRegs->SCISETINT, MCAL_CSL_SCI_SCISETINT_SET_TX_INT, 1U);
}

static inline void UART_rxIntrEnable(MCAL_CSL_sciRegs *pSCIRegs)
{
    HW_SET_FIELD32(pSCIRegs->SCISETINT, MCAL_CSL_SCI_SCISETINT_SET_RX_INT, 1U);
}

static inline void UART_txIntrDisable(const MCAL_CSL_sciRegs *pSCIRegs)
{
    HW_WR_REG32(&pSCIRegs->SCICLEARINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCICLEARINT_CLR_TX_INT, 1U));
}

static inline void UART_rxIntrDisable(const MCAL_CSL_sciRegs *pSCIRegs)
{
    HW_WR_REG32(&pSCIRegs->SCICLEARINT, MCAL_CSL_FMK(MCAL_CSL_SCI_SCICLEARINT_CLR_RX_INT, 1U));
}

static inline uint32 UART_isTxIntrEnabled(const MCAL_CSL_sciRegs *pSCIRegs)
{
    return HW_GET_FIELD(pSCIRegs->SCISETINT, MCAL_CSL_SCI_SCISETINT_SET_TX_INT);
}

static inline uint32 UART_isRxIntrEnabled(const MCAL_CSL_sciRegs *pSCIRegs)
{
    return HW_GET_FIELD(pSCIRegs->SCISETINT, MCAL_CSL_SCI_SCISETINT_SET_RX_INT);
}

#define CDD_UART_STOP_SEC_CODE
#include "Cdd_Uart_MemMap.h"

#define CDD_UART_START_SEC_ISR_CODE
#include "Cdd_Uart_MemMap.h"

/* ISR Rx Interrupt Handler */
static void Uart_Cdd_RxHandler(uint32 intrStatus, CddUart_Handle hUart)
{
    /* Is there a Rx Interrupt? */
    if ((intrStatus & MCAL_CSL_SCI_SCIFLR_RXRDY_MASK) != (uint32)0U)
    {
        /* Rx Interrupt without any character to be read? */
        if (hUart->readSizeRemaining == (uint32)0U)
        {
            /* Dummy read and drop the received character */
            HW_GET_FIELD(hUart->pSCIRegs->SCIRD, MCAL_CSL_SCI_SCIRD_RD);
        }

        /* Do we have valid data buffer to place the data? */
        if (hUart->readSizeRemaining > (uint32)0U)
        {
            UART_rxChar(hUart);
        }

        /* Are we done with the read buffer? */
        if (hUart->readSizeRemaining == (uint32)0U)
        {
            /* Disable RX interrupt until we do a new read */
            UART_rxIntrDisable(hUart->pSCIRegs);

            /* Reset the read buffer so we can pass it back */
            hUart->readBuf = (uint8 *)hUart->readBuf - hUart->readCount;
            if (hUart->readTrans != NULL_PTR)
            {
                hUart->readTrans->count  = (uint32)(hUart->readCount);
                hUart->readTrans->status = UART_TRANSFER_STATUS_SUCCESS;
            }

            hUart->readTrans = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_readCompleteCallback(hUart);
        }
    }
}

/* ISR Tx Interrupt Handler */
static void Uart_Cdd_TxHandler(uint32 intrStatus, CddUart_Handle hUart)
{
    /* Is there a Tx Interrupt? */
    if ((intrStatus & MCAL_CSL_SCI_SCIFLR_TXRDY_MASK) != (uint32)0U)
    {
        /*Is there any data which needs to be written? */
        if ((hUart->writeSizeRemaining > (uint32)0U))
        {
            UART_txChar(hUart);
        }

        /* Are we done with the write buffer? */
        if (hUart->writeSizeRemaining == (uint32)0U)
        {
            /* Disable TX interrupt until we do a new write */
            UART_txIntrDisable(hUart->pSCIRegs);

            /* Reset the write buffer so we can pass it back */
            hUart->writeBuf = (const uint8 *)hUart->writeBuf - hUart->writeCount;
            if (hUart->writeTrans != NULL_PTR)
            {
                hUart->writeTrans->count  = (uint32)(hUart->writeCount);
                hUart->writeTrans->status = UART_TRANSFER_STATUS_SUCCESS;
            }

            hUart->writeTrans = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_writeCompleteCallback(hUart);
        }
    }
}

static void Uart_masterIsr_readErrorStatus(uint32 intrStatus, CddUart_Handle hUart)
{
    if (hUart->readTrans != NULL_PTR)
    {
        hUart->readErrorCnt++;
        if ((intrStatus & MCAL_CSL_SCI_SCIFLR_OE_MASK) != (uint32)0U)
        {
            hUart->readTrans->status = UART_TRANSFER_STATUS_ERROR_OE;
        }
        if ((intrStatus & MCAL_CSL_SCI_SCIFLR_FE_MASK) != (uint32)0U)
        {
            hUart->readTrans->status = UART_TRANSFER_STATUS_ERROR_FE;
        }
        if ((intrStatus & MCAL_CSL_SCI_SCIFLR_PE_MASK) != (uint32)0U)
        {
            hUart->readTrans->status = UART_TRANSFER_STATUS_ERROR_PE;
        }
    }
}

void Uart_Cdd_masterIsr(void *args)
{
    uint32         intrStatus, regVal;
    CddUart_Handle hUart;

    if (NULL_PTR != args)
    {
        hUart = (CddUart_Handle)args;

        intrStatus = HW_RD_REG32(&hUart->pSCIRegs->SCIFLR);
        /* Handle only when Rx interrupts are enabled */
        if (UART_isRxIntrEnabled(hUart->pSCIRegs) != (uint32)0U)
        {
            Uart_Cdd_RxHandler(intrStatus, hUart);
        }

        /* Handle only when TX interrupts are enabled */
        if (UART_isTxIntrEnabled(hUart->pSCIRegs) != (uint32)0U)
        {
            Uart_Cdd_TxHandler(intrStatus, hUart);
        }

        /* Check for errors */
        if (((intrStatus & MCAL_CSL_SCI_SCIFLR_OE_MASK) > 0U) || ((intrStatus & MCAL_CSL_SCI_SCIFLR_FE_MASK) > 0U) ||
            ((intrStatus & MCAL_CSL_SCI_SCIFLR_PE_MASK) > 0U))
        {
            /* Update hUart->readTrans Error status */
            Uart_masterIsr_readErrorStatus(intrStatus, hUart);

            /* Clear ongoing read transaction pointer */
            hUart->readTrans = (CddUart_Transaction *)NULL_PTR;

            /* Error notification callback */
            Uart_Cdd_errorCallback(hUart);

            /* Clear only those errors that are set */
            regVal =
                intrStatus & (MCAL_CSL_SCI_SCIFLR_OE_MASK | MCAL_CSL_SCI_SCIFLR_FE_MASK | MCAL_CSL_SCI_SCIFLR_PE_MASK);
            HW_WR_REG32(&hUart->pSCIRegs->SCIFLR, regVal);
        }
    }

    return;
}

#define CDD_UART_STOP_SEC_ISR_CODE
#include "Cdd_Uart_MemMap.h"
