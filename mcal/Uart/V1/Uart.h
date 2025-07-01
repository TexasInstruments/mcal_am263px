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
 *  \defgroup DRV_UART_LLD_MODULE APIs for UART
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the UART.
 *
 *  @{
 */

/**
 *  \file Uart.h
 *
 *  \brief This file contains the prototype of UART driver APIs
 */

#ifndef UART_V1_LLD_H_
#define UART_V1_LLD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 *  \anchor UART_TransferStatus
 *  \name Transfer Status Code
 *
 *  Status codes that are set by the UART driver
 *
 *  @{
 */
/** \brief Transaction success */
#define UART_TRANSFER_STATUS_SUCCESS (0U)
/** \brief Time out error */
#define UART_TRANSFER_STATUS_TIMEOUT (1U)
/** \brief Break condition error */
#define UART_TRANSFER_STATUS_ERROR_BI (2U)
/** \brief Framing error */
#define UART_TRANSFER_STATUS_ERROR_FE (3U)
/** \brief Parity error */
#define UART_TRANSFER_STATUS_ERROR_PE (4U)
/** \brief Overrun error */
#define UART_TRANSFER_STATUS_ERROR_OE (5U)
/** \brief Cancelled */
#define UART_TRANSFER_STATUS_CANCELLED (6U)
/** \brief Transaction started */
#define UART_TRANSFER_STATUS_STARTED (7U)
/** \brief Read timeout error */
#define UART_TRANSFER_STATUS_READ_TIMEOUT (8U)
/** \brief UART is currently in use */
#define UART_TRANSFER_STATUS_ERROR_INUSE (9U)
/** \brief Other errors */
#define UART_TRANSFER_STATUS_ERROR_OTH (10U)
/** @} */

/**
 *  \anchor UART Transfer Mode
 *  \name Transfer Type
 *
 *  This determines the direction of data transfer as needed
 *  @{
 */
/** \brief UART Read Transfer Types */
#define UART_READ_TRANSFER_TYPE (CddUartDataDirectionType)(0U)
/** \brief UART Write Transfer Types */
#define UART_WRITE_TRANSFER_TYPE (CddUartDataDirectionType)(1U)
/** @} */

/** \brief Macro to check if the Data length is valid */
#define IS_DATA_LENGTH_VALID(dataLength)                                                 \
    ((dataLength == CDD_UART_WORD_LENGTH_5) || (dataLength == CDD_UART_WORD_LENGTH_6) || \
     (dataLength == CDD_UART_WORD_LENGTH_7) || (dataLength == CDD_UART_WORD_LENGTH_8))

/** \brief Macro to check if the Number of stop bits is valid */
#define IS_STOP_BITS_VALID(stopBits) ((stopBits == CDD_UART_STOP_BIT_1) || (stopBits == CDD_UART_STOP_BITS_2))

/** \brief Macro to check if the Parity type is valid */
#define IS_PARITY_TYPE_VALID(parityType)                                            \
    ((parityType == CDD_UART_PARITY_NONE) || (parityType == CDD_UART_PARITY_ODD) || \
     (parityType == CDD_UART_PARITY_EVEN))

/** \brief MCAL Driver states */
#define MCAL_STATE_RESET (0U)
#define MCAL_STATE_READY (1U)
#define MCAL_STATE_BUSY  (2U)
#define MCAL_STATE_ERROR (3U)

/* ========================================================================== */
/*                           Structure Declarations                           */
/* ========================================================================== */

/** \brief A handle that is used by UART with EDMA */
typedef void *CddUart_DmaHandle;

typedef struct
{
    volatile uint32 SCIGCR0;
    volatile uint32 SCIGCR1;
    volatile uint32 RESERVED1;
    volatile uint32 SCISETINT;
    volatile uint32 SCICLEARINT;
    volatile uint32 SCISETINTLVL;
    volatile uint32 SCICLEARINTLVL;
    volatile uint32 SCIFLR;
    volatile uint32 SCIINTVECT0;
    volatile uint32 SCIINTVECT1;
    volatile uint32 SCICHAR;
    volatile uint32 SCIBAUD;
    volatile uint32 SCIED;
    volatile uint32 SCIRD;
    volatile uint32 SCITD;
    volatile uint32 SCIPIO0;
    volatile uint32 SCIPIO1;
    volatile uint32 SCIPIO2;
    volatile uint32 SCIPIO3;
    volatile uint32 SCIPIO4;
    volatile uint32 SCIPIO5;
    volatile uint32 SCIPIO6;
    volatile uint32 SCIPIO7;
    volatile uint32 SCIPIO8;
    volatile uint32 RESERVED2;
    volatile uint32 RESERVED3;
    volatile uint32 RESERVED4;
    volatile uint32 RESERVED5;
    volatile uint32 RESERVED6;
    volatile uint32 RESERVED7;
    volatile uint32 RESERVED8;
    volatile uint32 RESERVED9;
    volatile uint32 SCIPIO9;
    volatile uint8  Resv_144[12];
    volatile uint32 SCIIODCTRL;
} MCAL_CSL_sciRegs;

/**
 *  \brief Data structure used with #UART_read() and #UART_write()
 */
typedef struct
{
    void  *buf;
    /**< [IN] void * to a buffer with data to be transferred .
     *   This parameter can't be NULL */
    uint32 count;
    /**< [IN/OUT] Number of bytes for this transaction.
     *  This is input incase of read/write call and on API return
     *  this represents number of bytes actually read by the API */
    uint32 timeout;
    /**< Timeout for this transaction in units of system ticks */
    uint32 status;
    /**< [OUT] \ref UART_TransferStatus code */
    void  *args;
    /**< [IN] Argument to be passed to the callback function */
} CddUart_Transaction;

/**
 *  \brief UART driver initialization object
 */
typedef struct
{
    uint32 inputClkFreq;
    /**< Module input clock frequency */
    uint32 baudRate;
    /**< Baud rate for UART */
    uint32 dataLength;
    /**< Data length for UART. Refer \ref UART_DataLength */
    uint32 stopBits;
    /**< Stop bits for UART. Refer \ref UART_StopBits */
    uint32 parityType;
    /**< Parity bit type for UART. Refer \ref UART_Parity */

    /*
     * Driver configuration
     */
    uint32 transferMode;
    /**< Transfer mode */
    uint32 intrNum;
    /**< Peripheral interrupt number */
    uint8  intrPriority;
    /**< Interrupt priority */
} CddUart_InitObject, *CddUart_InitHandle;

/**
 *  \brief UART driver object
 */
typedef struct
{
    /*
     * SOC configuration
     */
    uint8              channelID;
    /**< UART instance Channel ID */
    uint32             baseAddr;
    /**< Peripheral base address */
    CddUart_InitHandle hUartInit;
    /**< [IN] Initialization parameters of UART instance */

    /*
     * UART write variables
     */
    const void          *writeBuf;
    /**< Buffer data pointer */
    uint32               writeCount;
    /**< Number of Chars sent */
    uint32               writeSizeRemaining;
    /**< Chars remaining in buffer */
    /*
     * UART receive variables
     */
    void                *readBuf;
    /**< Buffer data pointer */
    uint32               readCount;
    /**< Number of Chars read */
    uint32               readSizeRemaining;
    /**< Chars remaining in buffer */
    uint32               rxTimeoutCnt;
    /**< Receive timeout error count */
    uint32               readErrorCnt;
    /**< Line status error count */
    /*
     * UART transaction status variables
     */
    CddUart_Transaction *readTrans;
    /**< Pointer to the current read transaction */
    CddUart_Transaction *writeTrans;
    /**< Pointer to the current write transaction */

    uint32            dmaTxHandleId;
    /**< DMA Transfer Handle ID */
    uint32            dmaRxHandleId;
    /**< DMA Receive Handle ID */
    MCAL_CSL_sciRegs *pSCIRegs;
    /**< Pointer to register overlay */
    uint8             shiftJustification;
    /**< This is the number of bits the read data needs to be shifted. This is
     *   calculated using the data length. When data of fewer than eight bits
     *   in length is received, it is left-justified in SCIRD and padded with
     *   trailing zeros. Data read from the SCIRD should be shifted by software
     *   to make the received data rightjustified. */

    /*
     * State variables
     */
    uint32 state;
    /**< Flag to indicate whether the instance is opened already */
    uint32 readTransferMutex;
    /**< Read Transfer Sync Sempahore - to signal transfer completion */
    uint32 writeTransferMutex;
    /**< Write Transfer Sync Sempahore - to signal transfer completion */
} CddUart_Object, *CddUart_Handle;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  Function to flush a TX FIFO of peripheral specified by the UART handle
 *
 *  \pre    #UART_open() has to be called first
 *
 *  \param  handle      #UART_Handle returned from #UART_open()
 *
 *  \sa     #UART_open()
 */
sint32 Uart_Cdd_flushTxFifo(CddUart_Handle handle);

/**
 *  \brief  Function to flush a TX FIFO of peripheral specified by the UART handle
 *
 *  \pre    #UART_open() has to be called first
 *
 *  \param  handle      #UART_Handle returned from #UART_open()
 *
 *  \sa     #UART_open()
 */
boolean UART_writeCancelNoCB(CddUart_Handle hUart);

/**
 *  \brief  Function to flush a TX FIFO of peripheral specified by the UART handle
 *
 *  \pre    #UART_open() has to be called first
 *
 *  \param  handle      #UART_Handle returned from #UART_open()
 *
 *  \sa     #UART_open()
 */
boolean UART_readCancelNoCB(CddUart_Handle hUart);

/* ========================================================================== */
/*                       Advanced Function Declarations                       */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Advanced Function Definitions                        */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef UART_V1_LLD_H_ */

/** @} */
