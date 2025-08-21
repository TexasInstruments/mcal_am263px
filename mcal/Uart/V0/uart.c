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
 *  \file   UART.c
 *
 *  \brief  This file contains the implementation of UART driver
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <Cdd_Uart.h>
#include <uart_dma.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define UART_FIFO_CONFIG_TXGRA     ((uint32)0xFU << 26)
#define UART_FIFO_CONFIG_RXGRA     ((uint32)0xFU << 22)
#define UART_FIFO_CONFIG_TXTRIG    ((uint32)0xFFU << 14)
#define UART_FIFO_CONFIG_RXTRIG    ((uint32)0xFFU << 6)
#define UART_FIFO_CONFIG_TXCLR     ((uint32)0x1U << 5)
#define UART_FIFO_CONFIG_RXCLR     ((uint32)0x1U << 4)
#define UART_FIFO_CONFIG_DMAENPATH ((uint32)0x1U << 3)
#define UART_FIFO_CONFIG_DMAMODE   ((uint32)0x7U << 0)

#define UART_TRIG_LVL_GRANULARITY_4 ((uint32)0x0000U)
#define UART_TRIG_LVL_GRANULARITY_1 ((uint32)0x0001U)

#define UART_DMA_EN_PATH_FCR (UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_0)
#define UART_DMA_EN_PATH_SCR (UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_1)

#define UART_INT2_RX_EMPTY (UART_IER2_EN_RXFIFO_EMPTY_MASK)
#define UART_INT2_TX_EMPTY (UART_IER2_EN_TXFIFO_EMPTY_MASK)

#define UART_DMA_MODE_0_ENABLE (UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_0)
#define UART_DMA_MODE_1_ENABLE (UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_1)
#define UART_DMA_MODE_2_ENABLE (UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_2)
#define UART_DMA_MODE_3_ENABLE (UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_3)

#define UART_MIR_OVERSAMPLING_RATE_41 ((uint32)41U)
#define UART_MIR_OVERSAMPLING_RATE_42 ((uint32)42U)

#define UART_BREAK_COND_DISABLE       (UART_LCR_BREAK_EN_BREAK_EN_VALUE_0 << UART_LCR_BREAK_EN_SHIFT)
#define UART_BREAK_COND_ENABLE        (UART_LCR_BREAK_EN_BREAK_EN_VALUE_1 << UART_LCR_BREAK_EN_SHIFT)
#define UART_NO_HARDWARE_FLOW_CONTROL (UART_EFR_HW_NO_FLOW_CONTROL_VALUE)
#define UART_RTS_ENABLE               (UART_EFR_HW_ENABLE_RTS_VALUE)
#define UART_CTS_ENABLE               (UART_EFR_HW_ENALE_CTS_VALUE)
#define UART_RTS_CTS_ENABLE           (UART_EFR_HW_ENABLE_RTS_CTS_FLOW_CONTROL_VALUE)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void          UART_resetModule(uint32 baseAddr);
static void          UART_writeDataPolling(CddUart_Handle hUart);
static uint32        UART_fifoWrite(CddUart_Handle hUart, const uint8 *buffer, uint32 writeSizeRemaining);
static void          Uart_Cdd_readTransErrorStatus(CddUart_Handle hUart, uint32 lineStatus);
/* Low level HW functions */
static uint32        UART_enhanFuncEnable(uint32 baseAddr);
static void          UART_regConfModeRestore(uint32 baseAddr, uint32 lcrRegValue);
static void          UART_modemControlReset(uint32 baseAddr);
static void          UART_moduleReset(uint32 baseAddr);
static uint32        UART_subConfigTCRTLRModeEn(uint32 baseAddr);
static void          UART_enhanFuncBitValRestore(uint32 baseAddr, uint32 enhanFnBitVal);
static uint32        UART_divisorLatchWrite(uint32 baseAddr, uint32 divisorValue);
static void          UART_fifoRegisterWrite(uint32 baseAddr, uint32 fcrValue);
static void          UART_tcrTlrBitValRestore(uint32 baseAddr, uint32 tcrTlrBitVal);
static uint32        UART_fifoConfig(uint32 baseAddr, uint32 fifoConfig);
static inline uint32 UART_divideRoundCloset(uint32 divident, uint32 divisor);
static void          UART_lineCharConfig(uint32 baseAddr, uint32 wLenStbFlag, uint32 parityFlag);
static void          UART_divisorLatchDisable(uint32 baseAddr);
static void          UART_breakCtl(uint32 baseAddr, uint32 breakState);
static void          UART_hardwareFlowCtrlOptSet(uint32 baseAddr, uint32 hwFlowCtrl);
static void          UART_flowCtrlTrigLvlConfig(uint32 baseAddr, uint32 rtsHaltFlag, uint32 rtsStartFlag);
static uint32        UART_getRxError(uint32 baseAddr);
static sint32        UART_readInterrupt(CddUart_Handle handle, CddUart_Transaction *trans);
static boolean       UART_statusIsDataReady(CddUart_Handle handle);
static uint32        UART_fifoRead(CddUart_Handle handle, uint8 *buffer, uint32 readSizeRemaining);
static void          UART_readDataPolling(CddUart_Handle handle);
static sint32        UART_readPolling(CddUart_Handle handle, CddUart_Transaction *trans);
static uint32        Cdd_Uart_getRxFifoTrigBitVal(uint32 rxTrig);
static uint32        Cdd_Uart_getTxFifoTrigBitVal(uint32 txTrig);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_UART_START_SEC_CODE
#include "Cdd_Uart_MemMap.h"

static uint32 Cdd_Uart_getRxFifoTrigBitVal(uint32 rxTrig)
{
    uint32 bitValue = 0U;
    if (CDD_UART_TRIGGER_LEVEL_8 == rxTrig)
    {
        bitValue = 0U;
    }
    else if (CDD_UART_TRIGGER_LEVEL_16 == rxTrig)
    {
        bitValue = 1U;
    }
    else if (CDD_UART_TRIGGER_LEVEL_56 == rxTrig)
    {
        bitValue = 2U;
    }
    else
    {
        bitValue = 3U;
    }

    return bitValue;
}

static uint32 Cdd_Uart_getTxFifoTrigBitVal(uint32 txTrig)
{
    uint32 bitValue = 0U;
    if (CDD_UART_TRIGGER_LEVEL_8 == txTrig)
    {
        bitValue = 0U;
    }
    else if (CDD_UART_TRIGGER_LEVEL_16 == txTrig)
    {
        bitValue = 1U;
    }
    else if (CDD_UART_TRIGGER_LEVEL_32 == txTrig)
    {
        bitValue = 2U;
    }
    else
    {
        bitValue = 3U;
    }

    return bitValue;
}

static uint32 UART_FIFO_CONFIG_CLR(uint32 txClr, uint32 rxClr, uint32 dmaEnPath, uint32 dmaMode)
{
    return (((uint32)(txClr & 0x1U) << (uint32)5U) | ((uint32)(rxClr & 0x1U) << (uint32)4U) |
            ((uint32)(dmaEnPath & 0x1U) << (uint32)3U) | ((uint32)(dmaMode & 0x7U)));
}

static uint32 UART_FIFO_CONFIG_NOCLR(uint32 txGra, uint32 rxGra, uint32 txTrig, uint32 rxTrig)
{
    return (((uint32)(txGra & 0xFU) << (uint32)26U) | ((uint32)(rxGra & 0xFU) << (uint32)22U) |
            ((uint32)(txTrig & 0xFFU) << (uint32)14U) | ((uint32)(rxTrig & 0xFFU) << (uint32)6U));
}

static inline uint32 UART_readData(CddUart_Handle hUart, uint32 size)
{
    uint8           readIn = 0;
    uint32          readSuccess;
    uint32          rdSize    = size;
    volatile uint32 tempCount = UART_TRANSMITEMPTY_TRIALCOUNT;
    if (UART_TRANSMITEMPTY_TRIALCOUNT > 8U)
    {
        tempCount = UART_TRANSMITEMPTY_TRIALCOUNT / 8U;
    }

    readSuccess = UART_getChar(hUart->baseAddr, &readIn);

    /* Receive chars until empty or done. */
    while ((rdSize != (uint32)0U) && (readSuccess != FALSE))
    {
        *(uint8 *)hUart->readBuf = readIn;
        hUart->readBuf           = (uint8 *)hUart->readBuf + 1U;
        hUart->readCount++;
        rdSize--;

        /* If read returnMode is UART_RETURN_FULL, avoids missing input character
         * of next read
         */
        if (rdSize != (uint32)0U)
        {
            readSuccess = UART_getChar(hUart->baseAddr, &readIn);
        }
        if (tempCount <= 0U)
        {
            /* timeout occured */
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }

    return (rdSize);
}

static inline uint32 UART_writeData(CddUart_Handle hUart, uint32 writeSizeRemaining)
{
    uint32             numBytesToTransfer, numBytesToTransferred;
    CddUart_InitHandle hUartInit = hUart->hUartInit;

    /* In interrupt mode write only threshold level of data with FIFO enabled */
    numBytesToTransfer = writeSizeRemaining;
    if (numBytesToTransfer >= hUartInit->txTrigLvl)
    {
        numBytesToTransfer = hUartInit->txTrigLvl;
    }

    numBytesToTransferred = numBytesToTransfer;
    /* Send characters until FIFO threshold level or done. */
    while (numBytesToTransfer != (uint32)0U)
    {
        UART_putChar(hUart->baseAddr, *(const uint8 *)hUart->writeBuf);
        hUart->writeBuf = (const uint8 *)hUart->writeBuf + 1U;

        numBytesToTransfer--;
        hUart->writeCount++;
    }

    return (writeSizeRemaining - numBytesToTransferred);
}

static inline void UART_putChar(uint32 baseAddr, uint8 byteTx)
{
    /* Write the byte to the Transmit Holding Register(or TX FIFO). */
    HW_WR_REG32(baseAddr + UART_THR, (uint32)byteTx);
}

static inline uint32 UART_getChar(uint32 baseAddr, uint8 *pChar)
{
    uint32 lcrRegValue = 0U;
    uint32 retVal      = FALSE;

    /* Preserving the current value of LCR. */
    lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);

    /* Switching to Register Operational Mode of operation. */
    HW_WR_REG32(baseAddr + UART_LCR, HW_RD_REG32(baseAddr + UART_LCR) & 0x7FU);

    /* Checking if the RX FIFO(or RHR) has atleast one byte of data. */
    if ((uint32)UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 != (HW_RD_REG32(baseAddr + UART_LSR) & UART_LSR_RX_FIFO_E_MASK))
    {
        uint32 tempRetVal = HW_RD_REG32(baseAddr + UART_RHR);
        *pChar            = (uint8)tempRetVal;
        retVal            = TRUE;
    }

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return retVal;
}

static inline void UART_intrEnable(uint32 baseAddr, uint32 intrFlag)
{
    uint32 enhanFnBitVal = 0U;
    uint32 lcrRegValue   = 0U;

    /* Switch to mode B only when the upper 4 bits of IER needs to be changed */
    if ((intrFlag & 0xF0U) > (uint32)0U)
    {
        /* Preserving the current value of LCR. */
        lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);
        /* Switching to Register Configuration Mode B. */
        HW_WR_REG32(baseAddr + UART_LCR, UART_REG_CONFIG_MODE_B & 0xFFU);

        /* Collecting the current value of EFR[4] and later setting it. */
        enhanFnBitVal = HW_RD_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN);

        HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

        /* Restoring the value of LCR. */
        HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

        /* Preserving the current value of LCR. */
        lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);

        /* Switching to Register Operational Mode of operation. */
        HW_WR_REG32(baseAddr + UART_LCR, HW_RD_REG32(baseAddr + UART_LCR) & 0x7FU);

        /*
        ** It is suggested that the System Interrupts for UART in the
        ** Interrupt Controller are enabled after enabling the peripheral
        ** interrupts of the UART using this API. If done otherwise, there
        ** is a risk of LCR value not getting restored and illicit characters
        ** transmitted or received from/to the UART. The situation is explained
        ** below.
        ** The scene is that the system interrupt for UART is already enabled
        ** and the current API is invoked. On enabling the interrupts
        ** corresponding to IER[7:4] bits below, if any of those interrupt
        ** conditions already existed, there is a possibility that the control
        ** goes to Interrupt Service Routine (ISR) without executing the
        ** remaining statements in this API. Executing the remaining statements
        ** is critical in that the LCR value is restored in them.
        ** However, there seems to be no risk in this API for enabling
        ** interrupts corresponding to IER[3:0] because it is done at the end
        ** and no statements follow that.
        */

        /************* ATOMIC STATEMENTS START *************************/

        /* Programming the bits IER[7:4]. */
        HW_WR_REG32(baseAddr + UART_IER, intrFlag & 0xF0U);

        /* Restoring the value of LCR. */
        HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

        /* Preserving the current value of LCR. */
        lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);
        /* Switching to Register Configuration Mode B. */
        HW_WR_REG32(baseAddr + UART_LCR, UART_REG_CONFIG_MODE_B & 0xFFU);

        /* Restoring the value of EFR[4] to its original value. */
        HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

        /* Restoring the value of LCR. */
        HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

        /************** ATOMIC STATEMENTS END *************************/
    }

    /* Programming the bits IER[3:0]. */
    HW_WR_REG32(baseAddr + UART_IER, HW_RD_REG32(baseAddr + UART_IER) | (intrFlag & 0x0FU));
}

static inline void UART_intrDisable(uint32 baseAddr, uint32 intrFlag)
{
    uint32 enhanFnBitVal;
    uint32 lcrRegValue;

    /* Switch to mode B only when the upper 4 bits of IER needs to be changed */
    if ((intrFlag & 0xF0U) > (uint32)0U)
    {
        /* Preserving the current value of LCR. */
        lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);
        /* Switching to Register Configuration Mode B. */
        HW_WR_REG32(baseAddr + UART_LCR, UART_REG_CONFIG_MODE_B & 0xFFU);

        /* Collecting the current value of EFR[4] and later setting it. */
        enhanFnBitVal = HW_RD_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN);

        HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

        /* Restoring the value of LCR. */
        HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
    }

    /* Preserving the current value of LCR. */
    lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);

    /* Switching to Register Operational Mode of operation. */
    HW_WR_REG32(baseAddr + UART_LCR, HW_RD_REG32(baseAddr + UART_LCR) & 0x7FU);

    HW_WR_REG32(baseAddr + UART_IER, HW_RD_REG32(baseAddr + UART_IER) & ~(intrFlag & 0xFFU));

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switch to mode B only when the upper 4 bits of IER needs to be changed */
    if ((intrFlag & 0xF0U) > (uint32)0U)
    {
        /* Preserving the current value of LCR. */
        lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);
        /* Switching to Register Configuration Mode B. */
        HW_WR_REG32(baseAddr + UART_LCR, UART_REG_CONFIG_MODE_B & 0xFFU);

        /* Restoring the value of EFR[4] to its original value. */
        HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

        /* Restoring the value of LCR. */
        HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
    }
}

static inline void UART_intr2Disable(uint32 baseAddr, uint32 intrFlag)
{
    HW_WR_REG32(baseAddr + UART_IER2, HW_RD_REG32(baseAddr + UART_IER2) & ~(intrFlag & 0x3U));
}

static inline uint32 UART_getIntrIdentityStatus(uint32 baseAddr)
{
    uint32 lcrRegValue = 0U;
    uint32 retVal      = 0U;

    /* Preserving the current value of LCR. */
    lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);

    /* Switching to Register Operational Mode of operation. */
    HW_WR_REG32(baseAddr + UART_LCR, HW_RD_REG32(baseAddr + UART_LCR) & 0x7FU);

    retVal = HW_RD_REG32(baseAddr + UART_IIR) & UART_IIR_IT_TYPE_MASK;

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return retVal;
}

uint32 UART_checkCharsAvailInFifo(uint32 baseAddr)
{
    uint32 lcrRegValue = 0;
    uint32 retVal      = FALSE;

    /* Preserving the current value of LCR. */
    lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);

    /* Switching to Register Operational Mode of operation. */
    HW_WR_REG32(baseAddr + UART_LCR, HW_RD_REG32(baseAddr + UART_LCR) & 0x7FU);

    /* Checking if the Transmitter FIFO and Transmitter Shift Register are empty. */
    uint32  hwRdReg       = HW_RD_REG32(baseAddr + UART_LSR);
    uint32  uartLsrTxMask = (UART_LSR_TX_SR_E_MASK | UART_LSR_TX_FIFO_E_MASK);
    boolean maskVal       = FALSE;
    if (uartLsrTxMask == (hwRdReg & uartLsrTxMask))
    {
        maskVal = TRUE;
    }
    if (maskVal == TRUE)
    {
        retVal = (uint32)TRUE;
    }

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return retVal;
}

uint32 UART_readLineStatus(uint32 baseAddr)
{
    uint32 lcrRegValue = 0U;
    uint32 retVal      = 0U;

    /* Preserving the current value of LCR. */
    lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);

    /* Switching to Register Operational Mode of operation. */
    HW_WR_REG32(baseAddr + UART_LCR, HW_RD_REG32(baseAddr + UART_LCR) & 0x7FU);

    retVal = HW_RD_REG32(baseAddr + UART_LSR);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return retVal;
}

boolean UART_writeCancelNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;

    UART_intrDisable(hUart->baseAddr, UART_INTR_THR);

    /* Disable interrupts to avoid writing data while changing state. */
    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();

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
boolean UART_writeCancelDmaNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;
    UART_intrDisable(hUart->baseAddr, UART_INTR_THR);

    /* Disable interrupts to avoid writing data while changing state. */
    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();

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
            hUart->writeTrans->count = 0;
        }
        else
        {
            hUart->writeCount = 0;
        }
    }

    SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();

    return (retVal);
}
#endif

boolean UART_readCancelNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;

    UART_intrDisable(hUart->baseAddr, UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);

    /* Disable interrupts to avoid reading data while changing state. */
    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
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
boolean UART_readCancelDmaNoCB(CddUart_Handle hUart)
{
    boolean retVal = (boolean)TRUE;

    UART_intrDisable(hUart->baseAddr, UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);

    /* Disable interrupts to avoid reading data while changing state. */
    SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    if (hUart->readSizeRemaining == (uint32)0U)
    {
        retVal = (boolean)FALSE;
    }
    else
    {
/* Disable DMA RX channel */
#if (STD_ON == CDD_UART_DMA_ENABLE)
        (void)Cdd_Dma_DisableTransferRegion(hUart->dmaRxHandleId, CDD_EDMA_TRIG_MODE_EVENT);
#else
        retVal = (boolean)FALSE;
#endif
        if (hUart->readTrans != NULL_PTR)
        {
            hUart->readTrans->count = 0;
        }
        else
        {
            hUart->readCount = 0;
        }
    }

    SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0();
    return (retVal);
}
#endif

void UART_configInstance(CddUart_Handle hUart)
{
    uint32             baseAddr;
    uint32             regVal, divisorVal, wLenStbFlag, parityFlag;
    CddUart_InitHandle hUartInit;

    baseAddr  = hUart->baseAddr;
    hUartInit = hUart->hUartInit;

    /* Reset module */
    UART_resetModule(baseAddr);

    /* Set up the TX and RX FIFO Trigger levels. */
    if (CDD_UART_MODE_DMA == hUartInit->transferMode)
    {
        regVal = UART_FIFO_CONFIG_NOCLR(UART_TRIG_LVL_GRANULARITY_1, UART_TRIG_LVL_GRANULARITY_1, hUartInit->txTrigLvl,
                                        hUartInit->rxTrigLvl) |
                 UART_FIFO_CONFIG_CLR(1U, 1U, UART_DMA_EN_PATH_FCR, UART_DMA_MODE_1_ENABLE);
    }
    else
    {
        regVal = UART_FIFO_CONFIG_NOCLR(hUartInit->txTrigLvl, hUartInit->rxTrigLvl, hUartInit->txTrigLvl,
                                        hUartInit->rxTrigLvl) |
                 UART_FIFO_CONFIG_CLR(1U, 1U, UART_DMA_EN_PATH_FCR, UART_DMA_MODE_0_ENABLE);
    }

    /* Configuring the FIFO settings. */
    (void)UART_fifoConfig(baseAddr, regVal);

    /* Computing the Divisor Value for params.baudRate */
    divisorVal = UART_divisorValCompute(hUartInit->inputClkFreq, hUartInit->baudRate, hUartInit->operMode);
    /* Configuring the Baud Rate settings. */
    (void)UART_divisorLatchWrite(baseAddr, divisorVal);

    /* Switching to Configuration Mode B. */
    (void)UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics */
    wLenStbFlag  = (hUartInit->dataLength << UART_LCR_CHAR_LENGTH_SHIFT);
    wLenStbFlag |= (hUartInit->stopBits << UART_LCR_NB_STOP_SHIFT);
    parityFlag   = (hUartInit->parityType << UART_LCR_PARITY_EN_SHIFT);
    UART_lineCharConfig(baseAddr, wLenStbFlag, parityFlag);

    /* Disable write access to Divisor Latches. */
    UART_divisorLatchDisable(baseAddr);

    /* Disabling Break Control. */
    UART_breakCtl(baseAddr, UART_BREAK_COND_DISABLE);

    /* Set UART operating mode */
    (void)UART_operatingModeSelect(baseAddr, hUartInit->operMode);

    if (hUartInit->hwFlowControl == (uint32)TRUE)
    {
        /* In case of HW flow control, the programmer must ensure that the
        trigger level to halt transmission is greater than or equal to the
        RX FIFO trigger level
        i.e., (hUartInit->hwFlowControlThr >= hUartInit->rxTrigLvl)  */
        UART_flowCtrlTrigLvlConfig(baseAddr, hUartInit->hwFlowControlThr, hUartInit->rxTrigLvl);
    }
    else
    {
        UART_hardwareFlowCtrlOptSet(baseAddr, UART_NO_HARDWARE_FLOW_CONTROL);
    }

    return;
}

static void UART_resetModule(uint32 baseAddr)
{
    /* Switch to mode B to access EFR */
    /* Set the ENHANCEDEN Bit Field to Enable access to the MCR & IER reg
     * Setting the EFR[4] bit to 1 */
    (void)UART_enhanFuncEnable(baseAddr);
    /* Force LCR[6] to zero, to avoid UART breaks and LCR[7] to zero to access
     * MCR reg */
    UART_regConfModeRestore(baseAddr, 0x00U);
    /* RESET MCR Reg */
    UART_modemControlReset(baseAddr);

    /* Disable all interrupts */
    UART_intrDisable(baseAddr, 0xFFU);
    UART_intr2Disable(baseAddr, UART_INT2_TX_EMPTY);

    /* Put the module in Disable State */
    (void)UART_operatingModeSelect(baseAddr, UART_OPER_MODE_DISABLED);

    /* Reset Uart and setup hardware params */
    UART_moduleReset(baseAddr);

    return;
}

static sint32 UART_checkTransaction(CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    if (0U == trans->count)
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

static uint32 UART_enhanFuncEnable(uint32 baseAddr)
{
    uint32 enhanFnBitVal;
    uint32 lcrRegValue;

    /* Enabling Configuration Mode B of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of ENHANCEDEN bit of EFR. */
    enhanFnBitVal = HW_RD_REG32(baseAddr + UART_EFR) & UART_EFR_ENHANCED_EN_MASK;

    /* Setting the ENHANCEDEN bit in EFR register. */
    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Programming LCR with the collected value. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return enhanFnBitVal;
}

static void UART_regConfModeRestore(uint32 baseAddr, uint32 lcrRegValue)
{
    /* Programming the Line Control Register(LCR). */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
}

static void UART_modemControlReset(uint32 baseAddr)
{
    uint32 mcrResetVal = 0U;
    /* Resetting bits of MCR. */
    HW_WR_REG32(baseAddr + UART_MCR, mcrResetVal);
}

uint32 UART_operatingModeSelect(uint32 baseAddr, uint32 modeFlag)
{
    uint32 operMode;

    operMode = HW_RD_REG32(baseAddr + UART_MDR1) & UART_MDR1_MODE_SELECT_MASK;

    /* Programming the MODESELECT field in MDR1. */
    HW_WR_FIELD32(baseAddr + UART_MDR1, UART_MDR1_MODE_SELECT, modeFlag >> UART_MDR1_MODE_SELECT_SHIFT);

    return operMode;
}

static void UART_moduleReset(uint32 baseAddr)
{
    /* Performing Software Reset of the module. */
    HW_WR_FIELD32(baseAddr + UART_SYSC, UART_SYSC_SOFTRESET, UART_SYSC_SOFTRESET_SOFTRESET_VALUE_1);

    /* Wait until the process of Module Reset is complete. */
    while (0U == HW_RD_FIELD32(baseAddr + UART_SYSS, UART_SYSS_RESETDONE))
    {
        /* Do nothing - Busy wait */
    }
}

static uint32 UART_subConfigTCRTLRModeEn(uint32 baseAddr)
{
    uint32 enhanFnBitVal;
    uint32 tcrTlrValue;
    uint32 lcrRegValue;

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of EFR[4] and later setting it. */
    enhanFnBitVal = HW_RD_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN);

    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode A. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_A);

    /* Collecting the bit value of MCR[6]. */
    tcrTlrValue = HW_RD_REG32(baseAddr + UART_MCR) & UART_MCR_TCR_TLR_MASK;

    /* Setting the TCRTLR bit in Modem Control Register(MCR). */
    HW_WR_FIELD32(baseAddr + UART_MCR, UART_MCR_TCR_TLR, UART_MCR_TCR_TLR_TCR_TLR_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4] to its original value. */
    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return tcrTlrValue;
}

static void UART_enhanFuncBitValRestore(uint32 baseAddr, uint32 enhanFnBitVal)
{
    uint32 lcrRegValue;

    /* Enabling Configuration Mode B of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4]. */
    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal >> UART_EFR_ENHANCED_EN_SHIFT);

    /* Programming LCR with the collected value. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
}

static uint32 UART_divisorLatchWrite(uint32 baseAddr, uint32 divisorValue)
{
    volatile uint32 enhanFnBitVal;
    volatile uint32 sleepMdBitVal;
    volatile uint32 lcrRegValue;
    volatile uint32 operMode;
    uint32          divRegVal;

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of EFR[4] and later setting it. */
    enhanFnBitVal = HW_RD_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN);
    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Register Operational Mode. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_OPERATIONAL_MODE);

    /*
    ** Collecting the current value of IER[4](SLEEPMODE bit) and later
    ** clearing it.
    */
    sleepMdBitVal = HW_RD_FIELD32(baseAddr + UART_IER, UART_IER_SLEEP_MODE);

    HW_WR_FIELD32(baseAddr + UART_IER, UART_IER_SLEEP_MODE, 0U);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of Divisor Latch Registers. */
    divRegVal  = HW_RD_REG32(baseAddr + UART_DLL) & 0xFFU;
    divRegVal |= (HW_RD_REG32(baseAddr + UART_DLH) & 0x3FU) << 8;

    /* Switch the UART instance to Disabled state. */
    operMode = UART_operatingModeSelect(baseAddr, (uint32)UART_MDR1_MODE_SELECT_MASK);

    /* Writing to Divisor Latch Low(DLL) register. */
    HW_WR_REG32(baseAddr + UART_DLL, divisorValue & 0x00FFU);

    /* Writing to Divisor Latch High(DLH) register. */
    HW_WR_REG32(baseAddr + UART_DLH, (divisorValue & 0x3F00U) >> 8);

    /* Restoring the Operating Mode of UART. */
    (void)UART_operatingModeSelect(baseAddr, operMode);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Register Operational Mode. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_OPERATIONAL_MODE);

    /* Restoring the value of IER[4] to its original value. */
    HW_WR_FIELD32(baseAddr + UART_IER, UART_IER_SLEEP_MODE, sleepMdBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4] to its original value. */
    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

    /* Restoring the value of LCR Register. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return divRegVal;
}

uint32 UART_IsTxRxFifoEmpty(uint32 baseAddr)
{
    uint32 lcrRegValue = 0;
    uint32 retVal      = FALSE;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_OPERATIONAL_MODE);

    /*
    ** Checking if either TXFIFOE and RXFIFOE bits of Line Status Register(LSR)
    ** are set/unset. TXFIFOE bit is set if TX FIFO(or THR in non-FIFO mode) is
    ** empty. RXFIFOE bit is unset if the RX FIFO(or RHR in non-FIFO mode) is
    ** empty.
    */

    if (((UART_LSR_TX_FIFO_E_TX_FIFO_E_VALUE_1 << UART_LSR_TX_FIFO_E_SHIFT) |
         (UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 << UART_LSR_RX_FIFO_E_SHIFT)) ==
        (HW_RD_REG32(baseAddr + UART_LSR) & ((UART_LSR_TX_FIFO_E_TX_FIFO_E_VALUE_1 << UART_LSR_TX_FIFO_E_SHIFT) |
                                             (UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 << UART_LSR_RX_FIFO_E_SHIFT))))
    {
        retVal = (uint32)TRUE;
    }

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return retVal;
}

static void UART_fifoRegisterWrite(uint32 baseAddr, uint32 fcrValue)
{
    uint32 divLatchRegVal;
    uint32 enhanFnBitVal;
    uint32 lcrRegValue;
    uint32 isTxRxFifoEmpty = FALSE;

    /* Switching to Register Configuration Mode A of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_A);

    /* Clearing the contents of Divisor Latch Registers. */
    divLatchRegVal = UART_divisorLatchWrite(baseAddr, 0x0000U);

    /* Set the EFR[4] bit to 1. */
    enhanFnBitVal = UART_enhanFuncEnable(baseAddr);

    /* Writing the 'fcrValue' to the FCR register. */
    HW_WR_REG32(baseAddr + UART_FCR, fcrValue);

    while (isTxRxFifoEmpty == FALSE)
    {
        isTxRxFifoEmpty = UART_IsTxRxFifoEmpty(baseAddr);
    }

    /* Restoring the value of EFR[4] to its original value. */
    UART_enhanFuncBitValRestore(baseAddr, enhanFnBitVal);

    /* Programming the Divisor Latch Registers with the collected value. */
    (void)UART_divisorLatchWrite(baseAddr, divLatchRegVal);

    /* Reinstating LCR with its original value. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
}

static void UART_tcrTlrBitValRestore(uint32 baseAddr, uint32 tcrTlrBitVal)
{
    uint32 enhanFnBitVal;
    uint32 lcrRegValue;

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Collecting the current value of EFR[4] and later setting it. */
    enhanFnBitVal = HW_RD_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN);

    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Configuration Mode A of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_A);

    /* Programming MCR[6] with the corresponding bit value in 'tcrTlrBitVal'. */
    HW_WR_FIELD32(baseAddr + UART_MCR, UART_MCR_TCR_TLR, tcrTlrBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    /* Switching to Register Configuration Mode B. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Restoring the value of EFR[4] to its original value. */
    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_ENHANCED_EN, enhanFnBitVal);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
}

static uint32 UART_fifoConfig(uint32 baseAddr, uint32 fifoConfig)
{
    uint32 enhanFnBitVal;
    uint32 tcrTlrBitVal;
    uint32 tlrValue;
    uint32 fcrValue = 0U;
    uint32 txGra    = (fifoConfig & UART_FIFO_CONFIG_TXGRA) >> 26;
    uint32 rxGra    = (fifoConfig & UART_FIFO_CONFIG_RXGRA) >> 22;
    uint32 txTrig   = (fifoConfig & UART_FIFO_CONFIG_TXTRIG) >> 14;
    uint32 rxTrig   = (fifoConfig & UART_FIFO_CONFIG_RXTRIG) >> 6;
    uint32 txClr    = (fifoConfig & UART_FIFO_CONFIG_TXCLR) >> 5;
    uint32 rxClr    = (fifoConfig & UART_FIFO_CONFIG_RXCLR) >> 4;

    uint32 dmaEnPath = (fifoConfig & UART_FIFO_CONFIG_DMAENPATH) >> 3;
    uint32 dmaMode   = (fifoConfig & UART_FIFO_CONFIG_DMAMODE);

    /* Setting the EFR[4] bit to 1. */
    enhanFnBitVal = UART_enhanFuncEnable(baseAddr);

    tcrTlrBitVal = UART_subConfigTCRTLRModeEn(baseAddr);

    /* Enable FIFO */
    fcrValue |= UART_FCR_FIFO_EN_MASK;

    if (txGra == 1U)
    {
        txGra = UART_TRIG_LVL_GRANULARITY_1;
    }
    if (rxGra == 1U)
    {
        rxGra = UART_TRIG_LVL_GRANULARITY_1;
    }

    /* Setting the Receiver FIFO trigger level. */
    if (UART_TRIG_LVL_GRANULARITY_1 != rxGra)
    {
        /* Clearing the RXTRIGGRANU1 bit in SCR. */
        HW_WR_FIELD32(baseAddr + UART_SCR, UART_SCR_RX_TRIG_GRANU1, UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_0);

        /* Clearing the RX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAddr + UART_TLR, UART_TLR_RX_FIFO_TRIG_DMA, 0U);

        fcrValue &= ~((uint32)UART_FCR_RX_FIFO_TRIG_MASK);

        /*
        ** Checking if 'rxTrig' matches with the RX Trigger level values
        ** in FCR.
        */
        if ((CDD_UART_TRIGGER_LEVEL_8 == rxTrig) || (CDD_UART_TRIGGER_LEVEL_16 == rxTrig) ||
            (CDD_UART_TRIGGER_LEVEL_56 == rxTrig) || (CDD_UART_TRIGGER_LEVEL_60 == rxTrig))
        {
            uint32 rxFifoTrig  = Cdd_Uart_getRxFifoTrigBitVal(rxTrig);
            fcrValue          |= ((rxFifoTrig << UART_FCR_RX_FIFO_TRIG_SHIFT) & UART_FCR_RX_FIFO_TRIG_MASK);
        }
        else
        {
            /* RX Trigger level will be a multiple of 4. */
            /* Programming the RX_FIFO_TRIG_DMA field of TLR register. */
            HW_WR_FIELD32(baseAddr + UART_TLR, UART_TLR_RX_FIFO_TRIG_DMA, rxTrig);
        }
    }
    else
    {
        /* 'rxTrig' now has the 6-bit RX Trigger level value. */

        rxTrig &= 0x003FU;

        /* Collecting the bits rxTrig[5:2]. */
        tlrValue = (rxTrig & 0x003CU) >> 2;

        /* Collecting the bits rxTrig[1:0] and writing to 'fcrValue'. */
        fcrValue |= (rxTrig & 0x0003U) << UART_FCR_RX_FIFO_TRIG_SHIFT;

        /* Setting the RXTRIGGRANU1 bit of SCR register. */
        HW_WR_FIELD32(baseAddr + UART_SCR, UART_SCR_RX_TRIG_GRANU1, UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_1);

        /* Programming the RX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAddr + UART_TLR, UART_TLR_RX_FIFO_TRIG_DMA, tlrValue);
    }

    /* Setting the Transmitter FIFO trigger level. */
    if (UART_TRIG_LVL_GRANULARITY_1 != txGra)
    {
        /* Clearing the TXTRIGGRANU1 bit in SCR. */
        HW_WR_FIELD32(baseAddr + UART_SCR, UART_SCR_TX_TRIG_GRANU1, UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_0);

        /* Clearing the TX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAddr + UART_TLR, UART_TLR_TX_FIFO_TRIG_DMA, 0U);

        fcrValue &= ~((uint32)UART_FCR_TX_FIFO_TRIG_MASK);

        /*
        ** Checking if 'txTrig' matches with the TX Trigger level values
        ** in FCR.
        */
        if ((CDD_UART_TRIGGER_LEVEL_8 == (txTrig)) || (CDD_UART_TRIGGER_LEVEL_16 == (txTrig)) ||
            (CDD_UART_TRIGGER_LEVEL_32 == (txTrig)) || (CDD_UART_TRIGGER_LEVEL_56 == (txTrig)))
        {
            uint32 txFifoTrig  = Cdd_Uart_getTxFifoTrigBitVal(txTrig);
            fcrValue          |= ((txFifoTrig << UART_FCR_TX_FIFO_TRIG_SHIFT) & UART_FCR_TX_FIFO_TRIG_MASK);
        }
        else
        {
            /* TX Trigger level will be a multiple of 4. */
            /* Programming the TX_FIFO_TRIG_DMA field of TLR register. */
            HW_WR_FIELD32(baseAddr + UART_TLR, UART_TLR_TX_FIFO_TRIG_DMA, txTrig);
        }
    }
    else
    {
        /* 'txTrig' now has the 6-bit TX Trigger level value. */

        txTrig &= 0x003FU;

        /* Collecting the bits txTrig[5:2]. */
        tlrValue = (txTrig & 0x003CU) >> 2;

        /* Collecting the bits txTrig[1:0] and writing to 'fcrValue'. */
        fcrValue |= (txTrig & 0x0003U) << UART_FCR_TX_FIFO_TRIG_SHIFT;

        /* Setting the TXTRIGGRANU1 bit of SCR register. */
        HW_WR_FIELD32(baseAddr + UART_SCR, UART_SCR_TX_TRIG_GRANU1, UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_1);

        /* Programming the TX_FIFO_TRIG_DMA field of TLR register. */
        HW_WR_FIELD32(baseAddr + UART_TLR, UART_TLR_TX_FIFO_TRIG_DMA, tlrValue);
    }

    if (UART_DMA_EN_PATH_FCR == dmaEnPath)
    {
        /* Configuring the UART DMA Mode through FCR register. */
        HW_WR_FIELD32(baseAddr + UART_SCR, UART_SCR_DMA_MODE_CTL, UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_0);

        dmaMode &= 0x1U;

        /* Clearing the bit corresponding to the DMA_MODE in 'fcrValue'. */
        fcrValue &= ~((uint32)UART_FCR_DMA_MODE_MASK);

        /* Setting the DMA Mode of operation. */
        fcrValue |= dmaMode << UART_FCR_DMA_MODE_SHIFT;
    }
    else
    {
        dmaMode &= 0x3U;

        /* Configuring the UART DMA Mode through SCR register. */
        HW_WR_FIELD32(baseAddr + UART_SCR, UART_SCR_DMA_MODE_CTL, UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_1);

        /* Programming the DMAMODE2 field in SCR. */
        HW_WR_FIELD32(baseAddr + UART_SCR, UART_SCR_DMA_MODE_2, dmaMode);
    }

    /* Programming the bits which clear the RX and TX FIFOs. */
    fcrValue |= rxClr << UART_FCR_RX_FIFO_CLEAR_SHIFT;
    fcrValue |= txClr << UART_FCR_TX_FIFO_CLEAR_SHIFT;

    /* Writing 'fcrValue' to the FIFO Control Register(FCR). */
    UART_fifoRegisterWrite(baseAddr, fcrValue);

    /* Restoring the value of TCRTLR bit in MCR. */
    UART_tcrTlrBitValRestore(baseAddr, tcrTlrBitVal);

    /* Restoring the value of EFR[4] to the original value. */
    UART_enhanFuncBitValRestore(baseAddr, enhanFnBitVal);

    return fcrValue;
}

static inline uint32 UART_divideRoundCloset(uint32 divident, uint32 divisor)
{
    return ((divident + (divisor / 2U)) / divisor);
}

uint32 UART_divisorValCompute(uint32 moduleClk, uint32 baudRate, uint32 modeFlag)
{
    uint32 divisorValue = 0U;
    uint32 tempModeFlag = modeFlag & UART_MDR1_MODE_SELECT_MASK;

    switch (tempModeFlag)
    {
        case CDD_UART_16x_OPER:
        case UART_OPER_MODE_SIR:
            divisorValue = UART_divideRoundCloset(moduleClk, 16U * baudRate);
            break;

        case CDD_UART_13x_OPER:
            divisorValue = UART_divideRoundCloset(moduleClk, 13U * baudRate);
            break;

        default:
            break;
    }

    return divisorValue;
}

static void UART_lineCharConfig(uint32 baseAddr, uint32 wLenStbFlag, uint32 parityFlag)
{
    uint32 lcrRegValue;

    lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);
    /* Clearing the CHAR_LENGTH and NB_STOP fields in LCR.*/
    lcrRegValue &= ~((uint32)UART_LCR_NB_STOP_MASK | (uint32)UART_LCR_CHAR_LENGTH_MASK);

    /* Programming the CHAR_LENGTH and NB_STOP fields in LCR. */
    lcrRegValue |= wLenStbFlag & (UART_LCR_NB_STOP_MASK | UART_LCR_CHAR_LENGTH_MASK);

    /* Clearing the PARITY_EN, PARITY_TYPE1 and PARITY_TYPE2 fields in LCR. */
    lcrRegValue &=
        ~((uint32)UART_LCR_PARITY_TYPE2_MASK | (uint32)UART_LCR_PARITY_TYPE1_MASK | (uint32)UART_LCR_PARITY_EN_MASK);

    /* Programming the PARITY_EN, PARITY_TYPE1 and PARITY_TYPE2 fields in LCR.*/
    lcrRegValue |= parityFlag & (UART_LCR_PARITY_TYPE2_MASK | UART_LCR_PARITY_TYPE1_MASK | UART_LCR_PARITY_EN_MASK);
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
}

static void UART_divisorLatchDisable(uint32 baseAddr)
{
    /* Disabling access to Divisor Latch registers by clearing LCR[7] bit. */
    HW_WR_FIELD32(baseAddr + UART_LCR, UART_LCR_DIV_EN, UART_LCR_DIV_EN_DIV_EN_VALUE_0);
}

static void UART_breakCtl(uint32 baseAddr, uint32 breakState)
{
    /* Programming the BREAK_EN bit in LCR. */
    HW_WR_FIELD32(baseAddr + UART_LCR, UART_LCR_BREAK_EN, breakState >> UART_LCR_BREAK_EN_SHIFT);
}

uint8 UART_fifoCharGet(uint32 baseAddr)
{
    uint32 tempRetVal = 0U;
    tempRetVal        = HW_RD_REG32(baseAddr + UART_RHR);
    return ((uint8)tempRetVal);
}

static void UART_hardwareFlowCtrlOptSet(uint32 baseAddr, uint32 hwFlowCtrl)
{
    uint32 lcrRegValue = 0;

    /* Switching to Configuration Mode B of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_B);

    /* Configuring the HWFLOWCONTROL field in EFR. */
    HW_WR_FIELD32(baseAddr + UART_EFR, UART_EFR_HW_FLOW_CONTROL, hwFlowCtrl);

    /* Restoring LCR with the collected value. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);
}

static void UART_flowCtrlTrigLvlConfig(uint32 baseAddr, uint32 rtsHaltFlag, uint32 rtsStartFlag)
{
    uint32 tcrValue = 0;

    tcrValue = rtsHaltFlag & UART_TCR_RX_FIFO_TRIG_HALT_MASK;

    tcrValue |= (rtsStartFlag << UART_TCR_RX_FIFO_TRIG_START_SHIFT) & UART_TCR_RX_FIFO_TRIG_START_MASK;

    /* Writing to TCR register. */
    HW_WR_REG32(baseAddr + UART_TCR, tcrValue);
}

uint32 UART_spaceAvail(uint32 baseAddr)
{
    uint32 lcrRegValue = 0;
    uint32 retVal      = FALSE;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_OPERATIONAL_MODE);

    /*
    ** Checking if either TXFIFOE or TXSRE bits of Line Status Register(LSR)
    ** are set. TXFIFOE bit is set if TX FIFO(or THR in non-FIFO mode) is
    ** empty. TXSRE is set if both the TX FIFO(or THR in non-FIFO mode) and
    ** the transmitter shift register are empty.
    */
    if ((UART_LSR_TX_SR_E_MASK | UART_LSR_TX_FIFO_E_MASK) ==
        (HW_RD_REG32(baseAddr + UART_LSR) & (UART_LSR_TX_SR_E_MASK | UART_LSR_TX_FIFO_E_MASK)))
    {
        retVal = (uint32)TRUE;
    }

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return retVal;
}

uint8 UART_readByte(CddUart_Handle hUart)
{
    uint8  readByte  = 0;
    uint32 waitCount = UART_ERROR_COUNT;
    uint32 errorVal;

    errorVal = UART_getRxError(hUart->baseAddr);
    /* Read and throw Erroneous bytes from RxFIFO */
    while ((UART_LSR_RX_FIFO_STS_MASK | UART_LSR_RX_BI_MASK | UART_LSR_RX_FE_MASK | UART_LSR_RX_PE_MASK |
            UART_LSR_RX_OE_MASK) == errorVal)
    {
        (void)UART_fifoCharGet(hUart->baseAddr);
        hUart->readErrorCnt++;
        waitCount--;

        errorVal = UART_getRxError(hUart->baseAddr);
        if ((uint32)0U == waitCount)
        {
            break;
        }
    }
    /* Read non-erroneous byte from RxFIFO */
    readByte = UART_fifoCharGet(hUart->baseAddr);

    return readByte;
}

static uint32 UART_getRxError(uint32 baseAddr)
{
    uint32 lcrRegValue = 0;
    uint32 retVal      = 0;

    /* Switching to Register Operational Mode of operation. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_OPERATIONAL_MODE);

    retVal = HW_RD_REG32(baseAddr + UART_LSR) & (UART_LSR_RX_FIFO_STS_MASK | UART_LSR_RX_BI_MASK | UART_LSR_RX_FE_MASK |
                                                 UART_LSR_RX_PE_MASK | UART_LSR_RX_OE_MASK);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return retVal;
}

uint32 UART_regConfigModeEnable(uint32 baseAddr, uint32 modeFlag)
{
    uint32 lcrRegValue;

    /* Preserving the current value of LCR. */
    lcrRegValue = HW_RD_REG32(baseAddr + UART_LCR);

    switch (modeFlag)
    {
        case UART_REG_CONFIG_MODE_A:
        case UART_REG_CONFIG_MODE_B:
            HW_WR_REG32(baseAddr + UART_LCR, modeFlag & 0xFFU);
            break;

        case UART_REG_OPERATIONAL_MODE:
            HW_WR_REG32(baseAddr + UART_LCR, HW_RD_REG32(baseAddr + UART_LCR) & 0x7FU);
            break;
        default:
            break;
    }

    return lcrRegValue;
}

sint32 UART_writeInterrupt(CddUart_Handle hUart)
{
    sint32 status = MCAL_SystemP_SUCCESS;
    uint32 baseAddr;

    baseAddr = hUart->baseAddr;

    /* Enable the transmit interrupt. */
    UART_intrEnable(baseAddr, UART_INTR_THR);

    return status;
}

sint32 UART_writePolling(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 retVal         = MCAL_SystemP_SUCCESS;
    uint32 timeoutElapsed = FALSE;
    uint32 baseAddr       = hUart->baseAddr;
    uint32 lineStatus     = 0U;

    volatile uint32 tempCount = trans->timeout;
    if (trans->timeout > 8U)
    {
        tempCount = (trans->timeout) / 8U;
    }
    hUart->writeSizeRemaining = trans->count;
    while ((FALSE == timeoutElapsed) && ((uint32)0U != hUart->writeSizeRemaining))
    {
        /* Transfer DATA */
        UART_writeDataPolling(hUart);
        if (tempCount <= 0U)
        {
            /* timeout occured */
            timeoutElapsed = TRUE;
        }
        MCAL_SW_DELAY(tempCount);
    }

    if (0U == hUart->writeSizeRemaining)
    {
        /* Make sure data is sent out from FIFO and shift register */
        tempCount = trans->timeout;
        if (trans->timeout > 8U)
        {
            tempCount = (trans->timeout) / 8U;
        }
        do
        {
            lineStatus = UART_readLineStatus(baseAddr);
            if (tempCount <= 0U)
            {
                /* timeout occured */
                break;
            }
            MCAL_SW_DELAY(tempCount);
        } while ((uint32)(UART_LSR_TX_FIFO_E_MASK | UART_LSR_TX_SR_E_MASK) !=
                 (lineStatus & (uint32)(UART_LSR_TX_FIFO_E_MASK | UART_LSR_TX_SR_E_MASK)));

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

static void UART_writeDataPolling(CddUart_Handle hUart)
{
    uint32 numBytesWritten = 0U;

    numBytesWritten = UART_fifoWrite(hUart, (const uint8 *)hUart->writeBuf, hUart->writeSizeRemaining);

    hUart->writeSizeRemaining -= numBytesWritten;
    hUart->writeBuf            = (const uint8 *)hUart->writeBuf + numBytesWritten;
    hUart->writeCount         += numBytesWritten;

    return;
}

static uint32 UART_fifoWrite(CddUart_Handle hUart, const uint8 *buffer, uint32 writeSizeRemaining)
{
    const uint8 *buf           = buffer;
    uint32       lineStatus    = 0U;
    uint32       tempChunksize = 0U;
    sint32       maxTrialCount = (sint32)UART_TRANSMITEMPTY_TRIALCOUNT;
    uint32       size = writeSizeRemaining, remainingSize = writeSizeRemaining;

    /* Load the fifo size  */
    tempChunksize = UART_FIFO_SIZE;

    /* Before we could write no of bytes, we should have
     * no of free buffers. Hence, we check for shiftregister
     * empty (ensure the FIFO is empty) to write num of bytes */
    do
    {
        lineStatus = (uint32)UART_readLineStatus(hUart->baseAddr);
        maxTrialCount--;
    } while (((uint32)(UART_LSR_TX_SR_E_MASK | UART_LSR_TX_FIFO_E_MASK) !=
              ((uint32)(UART_LSR_TX_SR_E_MASK | UART_LSR_TX_FIFO_E_MASK) & lineStatus)) &&
             ((sint32)0 < maxTrialCount));

    if (maxTrialCount > (sint32)0)
    {
        while ((tempChunksize > (uint32)0U) && (remainingSize > (uint32)0U))
        {
            /* Writing to the H/w */
            UART_putChar(hUart->baseAddr, (*buf));
            buf++;
            remainingSize--;
            tempChunksize--;
        }
    }

    /* Returns the size actually written */
    return (size - remainingSize);
}

/* ========================================================================== */
/*                       Advanced Function Definitions                        */
/* ========================================================================== */

void UART_enableLoopbackMode(uint32 baseAddr)
{
    uint32 lcrRegValue;

    /* Switching to Register Configuration Mode A. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_A);

    /* Enable Loopback Mode. */
    HW_WR_FIELD32(baseAddr + UART_MCR, UART_MCR_LOOPBACK_EN, UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_1);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return;
}

void UART_disableLoopbackMode(uint32 baseAddr)
{
    uint32 lcrRegValue;

    /* Switching to Register Configuration Mode A. */
    lcrRegValue = UART_regConfigModeEnable(baseAddr, UART_REG_CONFIG_MODE_A);

    /* Enable Loopback Mode. */
    HW_WR_FIELD32(baseAddr + UART_MCR, UART_MCR_LOOPBACK_EN, UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_0);

    /* Restoring the value of LCR. */
    HW_WR_REG32(baseAddr + UART_LCR, lcrRegValue);

    return;
}

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

        /* All of MCAL_LLD_PARAMS_CHECKs combined to reduce
         * METRICS.E.HIS_Metrics___Number_of_paths_PATH */
        if ((hUart->baseAddr == (uint32)0U) || (hUartInit->inputClkFreq == (uint32)0U) ||
            (hUartInit->baudRate == (uint32)0U) || (!(IS_DATA_LENGTH_VALID(hUartInit->dataLength))) ||
            (!(IS_STOP_BITS_VALID(hUartInit->stopBits))) || (!(IS_PARITY_TYPE_VALID(hUartInit->parityType))) ||
            (!(IS_OPER_MODE_VALID(hUartInit->operMode))) || (!(IS_RXTRIG_LVL_VALID(hUartInit->rxTrigLvl))) ||
            (!(IS_TXTRIG_LVL_VALID(hUartInit->txTrigLvl))))
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
        }
    }

    if (MCAL_SystemP_SUCCESS == status)
    {
        hUart->state = MCAL_STATE_READY;
    }
    else
    {
        /* Free-up resources in case of error */
        (void)Uart_Cdd_deInit(hUart);
    }

    return status;
}

sint32 Uart_Cdd_deInit(CddUart_Handle hUart)
{
    sint32 status = MCAL_SystemP_SUCCESS;

    if (NULL_PTR != hUart)
    {
        hUart->state = MCAL_STATE_BUSY;

        /* Flush TX FIFO */
        (void)Uart_Cdd_flushTxFifo(hUart);

        /* Disable UART and interrupts. */
        UART_intrDisable(hUart->baseAddr, UART_INTR_RHR_CTI | UART_INTR_THR | UART_INTR_LINE_STAT);
        UART_intr2Disable(hUart->baseAddr, UART_INT2_TX_EMPTY);
        (void)UART_operatingModeSelect(hUart->baseAddr, UART_OPER_MODE_DISABLED);

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

        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* Interrupt mode */
            status       = UART_writeInterrupt(hUart);
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
            hUart->readTrans->timeout = trans->timeout;
            hUart->readCount          = 0U;
            hUart->rxTimeoutCnt       = 0U;
            hUart->readErrorCnt       = 0U;
        }

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
            hUart->readTrans->timeout = trans->timeout;
            hUart->readCount          = 0U;
            hUart->rxTimeoutCnt       = 0U;
            hUart->readErrorCnt       = 0U;
        }

        if (MCAL_SystemP_SUCCESS == status)
        {
            hUart->state = MCAL_STATE_BUSY;
            /* Interrupt mode */
            status       = UART_readInterrupt(hUart, trans);
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
            hUart->readTrans->timeout = trans->timeout;
            hUart->readCount          = 0U;
            hUart->rxTimeoutCnt       = 0U;
            hUart->readErrorCnt       = 0U;
            hUart->readSizeRemaining  = trans->count;
        }

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
#endif /* (STD_ON == CDD_UART_DMA_ENABLE) */

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
#endif /* (STD_ON == CDD_UART_DMA_ENABLE) */

sint32 Uart_Cdd_flushTxFifo(CddUart_Handle hUart)
{
    sint32          status = MCAL_SystemP_SUCCESS;
    uint32          isTxFifoEmpty;
    uint32          timeoutElapsed = FALSE;
    volatile uint32 tempCount      = UART_TRANSMITEMPTY_TRIALCOUNT;
    if (UART_TRANSMITEMPTY_TRIALCOUNT > 8U)
    {
        tempCount = UART_TRANSMITEMPTY_TRIALCOUNT / 8U;
    }

    while ((uint32)FALSE == timeoutElapsed)
    {
        /* Get TX FIFO status */
        isTxFifoEmpty = UART_spaceAvail(hUart->baseAddr);
        if ((uint32)TRUE == isTxFifoEmpty)
        {
            /* FIFO and Shift register is empty */
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

static sint32 UART_readPolling(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32          retVal         = MCAL_SystemP_SUCCESS;
    uint32          timeoutElapsed = FALSE;
    volatile uint32 tempCount      = trans->timeout;
    if (trans->timeout > 8U)
    {
        tempCount = trans->timeout / 8U;
    }
    hUart->readSizeRemaining = trans->count;
    while ((FALSE == timeoutElapsed) && ((uint32)0U != hUart->readSizeRemaining))
    {
        /* Transfer DATA */
        UART_readDataPolling(hUart);
        if (tempCount <= 0U)
        {
            /* timeout occured */
            timeoutElapsed = TRUE;
        }
        MCAL_SW_DELAY(tempCount);
    }

    if (hUart->readErrorCnt > (uint32)0U)
    {
        retVal = MCAL_SystemP_FAILURE;
        Uart_Cdd_readTransErrorStatus(hUart, UART_readLineStatus(hUart->baseAddr));
        hUart->readTrans = (CddUart_Transaction *)NULL_PTR;
    }
    else if ((hUart->readSizeRemaining == (uint32)0U) && (hUart->rxTimeoutCnt == (uint32)0U))
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

static void UART_readDataPolling(CddUart_Handle hUart)
{
    uint32 numBytesRead = 0U;

    numBytesRead = UART_fifoRead(hUart, (uint8 *)hUart->readBuf, hUart->readSizeRemaining);

    hUart->readSizeRemaining -= numBytesRead;
    hUart->readBuf            = (uint8 *)hUart->readBuf + numBytesRead;
    hUart->readCount         += numBytesRead;

    return;
}

static uint32 UART_fifoRead(CddUart_Handle hUart, uint8 *buffer, uint32 readSizeRemaining)
{
    uint32  size = readSizeRemaining, remainingSize = readSizeRemaining;
    uint8  *buf       = buffer;
    boolean isRxReady = UART_statusIsDataReady(hUart);

    while (((boolean)TRUE == isRxReady) && ((uint32)0U != remainingSize))
    {
        /* once the H/w is ready  reading from the H/w                        */
        *buf = (uint8)UART_readByte(hUart);
        buf++;
        --remainingSize;

        isRxReady = UART_statusIsDataReady(hUart);
    }

    return (size - remainingSize);
}

static void Uart_Cdd_readTransErrorStatus(CddUart_Handle hUart, uint32 lineStatus)
{
    hUart->readErrorCnt++;
    if ((lineStatus & UART_BREAK_DETECTED_ERROR) != (uint32)0U)
    {
        hUart->readTrans->status = UART_TRANSFER_STATUS_ERROR_BI;
    }
    else if ((lineStatus & UART_FRAMING_ERROR) != (uint32)0U)
    {
        hUart->readTrans->status = UART_TRANSFER_STATUS_ERROR_FE;
    }
    else if ((lineStatus & UART_PARITY_ERROR) != (uint32)0U)
    {
        hUart->readTrans->status = UART_TRANSFER_STATUS_ERROR_PE;
    }
    else
    {
        hUart->readTrans->status = UART_TRANSFER_STATUS_ERROR_OE;
    }
}

void UART_procLineStatusErr(CddUart_Handle hUart)
{
    uint32 lineStatus, iteration = 0U;

    if (NULL_PTR != hUart)
    {
        lineStatus = UART_readLineStatus(hUart->baseAddr);

        if (((lineStatus & UART_FIFO_PE_FE_BI_DETECTED) == UART_FIFO_PE_FE_BI_DETECTED) ||
            ((lineStatus & UART_OVERRUN_ERROR) == UART_OVERRUN_ERROR))
        {
            /* empty the RX FIFO which contains data with errors */
            if (hUart->readTrans != NULL_PTR)
            {
                hUart->readTrans->count = (uint32)(hUart->readCount);
            }

            /* Clearing Receive Errors(FE,BI,PE)by reading erroneous data from RX FIFO */
            /* Iteration count: Worst case = FIFO size */
            iteration = UART_FIFO_SIZE;
            do
            {
                /* Read and throw error byte */
                /* Till Line status int is pending */
                (void)UART_fifoCharGet(hUart->baseAddr);

                iteration--;

                lineStatus  = (uint32)UART_readLineStatus(hUart->baseAddr);
                lineStatus &= (UART_LSR_RX_FIFO_STS_MASK | UART_LSR_RX_BI_MASK | UART_LSR_RX_FE_MASK |
                               UART_LSR_RX_PE_MASK | UART_LSR_RX_OE_MASK | UART_LSR_RX_FIFO_E_MASK);
            } while ((lineStatus != (uint32)0U) && (iteration != (uint32)0U));

            UART_intrDisable(hUart->baseAddr, UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);

            /* Reset the read buffer and read count so we can pass it back */
            hUart->readBuf = (uint8 *)hUart->readBuf - hUart->readCount;

            /* Update hUart->readTrans error status */
            if (NULL_PTR != hUart->readTrans)
            {
                Uart_Cdd_readTransErrorStatus(hUart, lineStatus);
            }

            hUart->readTrans = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_errorCallback(hUart);
        }
    }
}

static boolean UART_statusIsDataReady(CddUart_Handle hUart)
{
    uint32  status = 0;
    boolean retVal = FALSE;

    status = (uint32)UART_readLineStatus(hUart->baseAddr);

    /* Added for error checks */
    if ((uint32)UART_LSR_RX_FIFO_STS_MASK == (status & (uint32)UART_LSR_RX_FIFO_STS_MASK))
    {
        UART_procLineStatusErr(hUart);
    }
    /* Caution: This should be under if else of error check since
     * the RX error handler clears the FIFO. Hence the status we have read
     * before this call will become stale. Hence the data will not be
     * ready in FIFO. Otherwise we will read the FIFO register which has
     * a infinite loop for data ready and the code hangs there till user
     * gives any character!! */
    else if ((uint32)UART_LSR_RX_FIFO_E_MASK == (status & (uint32)UART_LSR_RX_FIFO_E_MASK))
    {
        retVal = (boolean)TRUE;
    }
    else
    {
        /* Do nothing */
    }

    return retVal;
}

static sint32 UART_readInterrupt(CddUart_Handle hUart, CddUart_Transaction *trans)
{
    sint32 status = MCAL_SystemP_SUCCESS;
    uint32 baseAddr;

    baseAddr = hUart->baseAddr;

    /* Disable RX threshold and line status error interrupt */
    UART_intrDisable(baseAddr, UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);

    hUart->readSizeRemaining = UART_readData(hUart, trans->count);
    if (hUart->readSizeRemaining == (uint32)0U)
    {
        /* Update the actual read count */
        trans->count  = (uint32)(hUart->readCount);
        trans->status = UART_TRANSFER_STATUS_SUCCESS;

        hUart->readTrans = (CddUart_Transaction *)NULL_PTR;
        Uart_Cdd_readCompleteCallback(hUart);

        status = MCAL_SystemP_SUCCESS;
    }
    else
    {
        /* Enable Rx, read time-out and RX Line Error interrupt */
        UART_intrEnable(baseAddr, (uint32)UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);
    }

    return status;
}

#define CDD_UART_STOP_SEC_CODE
#include "Cdd_Uart_MemMap.h"

#define CDD_UART_START_SEC_ISR_CODE
#include "Cdd_Uart_MemMap.h"

static void Uart_Cdd_RxHandler(CddUart_Handle hUart)
{
    uint8 rdData;
    /* RX FIFO threshold reached */
    if (hUart->readSizeRemaining > (uint32)0U)
    {
        hUart->readSizeRemaining = UART_readData(hUart, hUart->readSizeRemaining);
        if ((hUart->readSizeRemaining == (uint32)0U) ||
            (hUart->hUartInit->readReturnMode == CDD_UART_PARTIAL_READ_RETURN))
        {
            /* transfer completed */
            UART_intrDisable(hUart->baseAddr, UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);

            /* Update the driver internal status. */
            /* Reset the read buffer so we can pass it back */
            hUart->readBuf = (uint8 *)hUart->readBuf - hUart->readCount;
            if (hUart->readTrans != NULL_PTR)
            {
                hUart->readTrans->count  = hUart->readCount;
                hUart->readTrans->status = UART_TRANSFER_STATUS_SUCCESS;
            }
            hUart->readTrans = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_readCompleteCallback(hUart);
        }
        else
        {
            /* Enable Rx interrupt again in case of CDD_UART_FULL_READ_RETURN */
            UART_intrEnable(hUart->baseAddr, (uint32)UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);
        }
    }
    else
    {
        /* Disable the receive interrupt again. */
        (void)UART_getChar(hUart->baseAddr, &rdData);
        UART_intrDisable(hUart->baseAddr, (uint32)UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);
    }
}

static void Uart_Cdd_TxHandler(CddUart_Handle hUart)
{
    uint32 lineStatus;
    /* TX FIFO threshold reached */
    if (hUart->writeSizeRemaining > (uint32)0U)
    {
        hUart->writeSizeRemaining = UART_writeData(hUart, (hUart->writeSizeRemaining));
        if ((hUart->writeSizeRemaining) == (uint32)0U)
        {
            do
            {
                lineStatus = UART_readLineStatus(hUart->baseAddr);
            } while ((uint32)(UART_LSR_TX_FIFO_E_MASK | UART_LSR_TX_SR_E_MASK) !=
                     (lineStatus & (uint32)(UART_LSR_TX_FIFO_E_MASK | UART_LSR_TX_SR_E_MASK)));

            UART_intrDisable(hUart->baseAddr, UART_INTR_THR);

            /* Reset the write buffer so we can pass it back */
            hUart->writeBuf = (const uint8 *)hUart->writeBuf - hUart->writeCount;
            if (hUart->writeTrans != NULL_PTR)
            {
                hUart->writeTrans->count  = hUart->writeCount;
                hUart->writeTrans->status = UART_TRANSFER_STATUS_SUCCESS;
            }
            hUart->writeTrans = (CddUart_Transaction *)NULL_PTR;
            Uart_Cdd_writeCompleteCallback(hUart);
        }
    }
    else
    {
        UART_intrDisable(hUart->baseAddr, UART_INTR_THR);
    }
}

static boolean Uart_Cdd_masterIsr_processInterrupt(CddUart_Handle hUart, uint32 intType)
{
    boolean retVal = TRUE;
    if ((intType & UART_INTID_RX_THRES_REACH) == UART_INTID_RX_THRES_REACH)
    {
        if ((intType & UART_INTID_RX_LINE_STAT_ERROR) == UART_INTID_RX_LINE_STAT_ERROR)
        {
            /* RX line status error */
            UART_procLineStatusErr(hUart);
        }
        else
        {
            if ((intType & UART_INTID_CHAR_TIMEOUT) == UART_INTID_CHAR_TIMEOUT)
            {
                /* Disable Interrupt first, to avoid further RX timeout */
                UART_intrDisable(hUart->baseAddr, UART_INTR_RHR_CTI | UART_INTR_LINE_STAT);
                /* RX timeout, log the RX timeout errors */
                hUart->rxTimeoutCnt++;
            }

            Uart_Cdd_RxHandler(hUart);
        }
    }
    else if ((intType & UART_INTID_TX_THRES_REACH) == UART_INTID_TX_THRES_REACH)
    {
        Uart_Cdd_TxHandler(hUart);
    }
    else
    {
        retVal = FALSE;
    }

    return retVal;
}

/*
 *  ======== UART_masterIsr ========
 *  Hwi function that processes UART interrupts.
 *
 *  In non-DMA mode, three UART interrupts are enabled:
 *    1. transmit FIFO is below the TX FIFO trigger level (THR)
 *    2. receive FIFO is above RX FIFO trigger level (RHR)
 *    3. line status rx error
 *
 *  ISR checks the three interrupts, to ensure that all
 *  the pending interrupts are handled.
 *
 *  If line status rx error is detected, ISR clears the last read error, update
 *  the actual number of bytes transferred and transfer status in readTrans and
 *  calls back to application in the callback mode or post the read semaphone
 *  in the blocking mode. ISR
 *
 *  If RHR interrupt is received, ISR calls the in-lined function readData to
 *  read the data out from the RX FIFO. When all the data are received, ISR updates
 *  the actual number of bytes transferred and transfer status in readTrans and
 *  calls back to the application in the callback mode or post the read semaphone
 *  in the blocking mode. if RX timeout is detected, ISR will log the timeout
 *  count.
 *
 *  If THR interrupt is received, ISR calls the in-lined function writeData,
 *  to write the data to the TX FIFO. After all the data are sent, TX FIFO empty
 *  interrupt is enabled, ISR will update the actual number of bytes transferred
 *  and transfer status in writeTrans and calls back to application in the
 *  callback mode or post the read semaphone in the blocking mode.
 *
 *
 *  @param(arg)         The CddUart_Handle for this Hwi.
 */
void Uart_Cdd_masterIsr(void *args)
{
    CddUart_Handle hUart = (CddUart_Handle)args;

    if (NULL_PTR != hUart)
    {
        for (;;)
        {
            if (Uart_Cdd_masterIsr_processInterrupt(hUart, UART_getIntrIdentityStatus(hUart->baseAddr)) == FALSE)
            {
                break;
            }
        } /* for (;;) */
    }
}

#define CDD_UART_STOP_SEC_ISR_CODE
#include "Cdd_Uart_MemMap.h"
