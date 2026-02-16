/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2021 Texas Instruments Incorporated
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
 *  \file mcspi_v0.c
 *
 *  \brief File containing MCSPI Driver APIs implementation for version V0.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* This is needed for memset/memcpy */
#include "mcspi_v0.h"
#include <stdlib.h>
#include <string.h>
#include "sys_vim.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    void *lock;
    /**< Driver lock object */
} MCSPI_DrvObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Driver internal functions */
void        MCSPI_controllerIsr(void);
static void MCSPI_initiateLastChunkTransfer(MCSPI_Object *obj, MCSPI_ChObject *chObj, MCSPI_Transaction *transaction);
static uint32_t MCSPI_continueTxRx(MCSPI_Object *obj, MCSPI_ChObject *chObj, MCSPI_Transaction *transaction);
static int32_t  MCSPI_transferControllerPoll(MCSPI_Object *obj, MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs,
                                             MCSPI_Transaction *transaction);
static int32_t  MCSPI_transferControllerIntr(MCSPI_Object *obj, MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs,
                                             MCSPI_Transaction *transaction);
static void     MCSPI_peripheralIsr(void *args);
static uint32_t MCSPI_continuePeripheralTxRx(MCSPI_Object *obj, MCSPI_ChObject *chObj, MCSPI_Transaction *transaction);
static int32_t  MCSPI_transferPeripheralPoll(MCSPI_Object *obj, MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs,
                                             MCSPI_Transaction *transaction);
static int32_t  MCSPI_transferPeripheralIntr(MCSPI_Object *obj, MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs,
                                             MCSPI_Transaction *transaction);
static inline void MCSPI_fifoWrite(uint32_t baseAddr, MCSPI_ChObject *chObj, uint32_t transferLength);
static inline void MCSPI_fifoRead(uint32_t baseAddr, MCSPI_ChObject *chObj, uint32_t transferLength);
static void        MCSPI_configInstance(MCSPI_Config *config);
static void        MCSPI_setChConfig(MCSPI_Config *config, MCSPI_ChObject *chObj);
static int32_t     MCSPI_checkOpenParams(const MCSPI_OpenParams *openPrms);
static int32_t     MCSPI_checkChConfig(MCSPI_Object *obj, const MCSPI_ChConfig *chCfg);
static int32_t     MCSPI_checkTransaction(const MCSPI_Object *obj, MCSPI_Transaction *transaction);
static uint32_t    MCSPI_getDataWidthBitMask(uint32_t dataWidth);

/* Low level HW functions */
static void MCSPI_reset(uint32_t baseAddr);
static void MCSPI_setClkConfig(uint32_t baseAddr, uint32_t chNum, uint32_t inputClkFreq, uint32_t bitRate);
static void MCSPI_setFifoConfig(MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs, uint32_t baseAddr,
                                uint32_t numWordsTxRx);
static void MCSPI_setPeripheralFifoConfig(MCSPI_ChObject *chObj, uint32_t baseAddr, uint32_t numWordsTxRx);
static inline const uint8_t  *MCSPI_fifoWrite8(uint32_t baseAddr, uint32_t chNum, const uint8_t *bufPtr,
                                               uint32_t transferLength);
static inline const uint16_t *MCSPI_fifoWrite16(uint32_t baseAddr, uint32_t chNum, const uint16_t *bufPtr,
                                                uint32_t transferLength);
static inline const uint32_t *MCSPI_fifoWrite32(uint32_t baseAddr, uint32_t chNum, const uint32_t *bufPtr,
                                                uint32_t transferLength);
static inline uint8_t  *MCSPI_fifoRead8(uint32_t baseAddr, uint32_t chNum, uint8_t *bufPtr, uint32_t transferLength,
                                        uint32_t dataWidthBitMask);
static inline uint16_t *MCSPI_fifoRead16(uint32_t baseAddr, uint32_t chNum, uint16_t *bufPtr, uint32_t transferLength,
                                         uint32_t dataWidthBitMask);
static inline uint32_t *MCSPI_fifoRead32(uint32_t baseAddr, uint32_t chNum, uint32_t *bufPtr, uint32_t transferLength,
                                         uint32_t dataWidthBitMask);
static inline void      MCSPI_fifoWriteDefault(uint32_t baseAddr, uint32_t chNum, uint32_t defaultTxData,
                                               uint32_t transferLength);
static inline void      MCSPI_fifoReadDiscard(uint32_t baseAddr, uint32_t chNum, uint32_t transferLength);
static void             MCSPI_clearAllIrqStatus(uint32_t baseAddr);
static inline void      MCSPI_intrStatusClear(MCSPI_ChObject *chObj, uint32_t baseAddr, uint32_t intFlags);
static uint32_t         Spi_mcspiGetRxMask(uint32_t csNum);
static uint32_t         Spi_mcspiGetTxMask(uint32_t csNum);
static void             MCSPI_stop(MCSPI_Object *obj, const MCSPI_Attrs *attrs, MCSPI_ChObject *chObj, uint32_t chNum);
static void MCSPI_setChDataSize(uint32_t baseAddr, MCSPI_ChObject *chObj, uint32_t dataSize, uint32_t csDisable);

void SpiApp_interruptConfig(void);

__attribute__((target("arm"))) void Spi_IrqUnitMcspi1TxRx(void);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

MCSPI_Handle gMcspiHandle1[1];
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void MCSPI_init(void)
{
#if 1
    // int32_t         status;
    uint32_t      cnt;
    MCSPI_Object *obj;

    /* Init each driver instance object */
    for (cnt = 0U; cnt < gMcspiConfigNum; cnt++)
    {
        /* initialize object varibles */
        obj = gMcspiConfig[cnt].object;
        memset(obj, 0, sizeof(MCSPI_Object));
    }
#endif
    return;
}

MCSPI_Handle MCSPI_open(uint32_t index, const MCSPI_OpenParams *openPrms)
{
    // int32_t              status = Pmic_SystemP_SUCCESS;
    MCSPI_Handle       handle = NULL_CHECK;
    MCSPI_Config      *config = NULL_CHECK;
    MCSPI_Object      *obj    = NULL_CHECK;
    // HwiP_Params          hwiPrms;
    const MCSPI_Attrs *attrs;

    config = &gMcspiConfig[index];

    obj   = config->object;
    attrs = config->attrs;

    obj->handle = (MCSPI_Handle)config;
    memset(&obj->chObj, 0, sizeof(obj->chObj));
    obj->baseAddr = (uint32_t)(attrs->baseAddr);

    /* Configure the MCSPI instance parameters */
    MCSPI_configInstance(config);

    /* Register interrupt */
    SpiApp_interruptConfig();

    handle = (MCSPI_Handle)config;

    return (handle);
}

MCSPI_Handle MCSPI_getHandle(uint32_t index)
{
    MCSPI_Handle handle = NULL_CHECK;

    /* Check index */
    if (index < gMcspiConfigNum)
    {
        MCSPI_Object *object;

        object = gMcspiConfig[index].object;

        if (object && (TRUE == object->isOpen))
        {
            /* valid handle */
            handle = object->handle;
        }
    }

    return handle;
}

int32_t MCSPI_chConfig(MCSPI_Handle handle, const MCSPI_ChConfig *chCfg)
{
    int32_t         status = Pmic_SystemP_SUCCESS;
    MCSPI_Config   *config;
    MCSPI_Object   *obj;
    MCSPI_ChObject *chObj;

    config = (MCSPI_Config *)handle;
    obj    = config->object;

    if (Pmic_SystemP_SUCCESS == status)
    {
        chObj = &obj->chObj[chCfg->chNum];
        memcpy(&chObj->chCfg, chCfg, sizeof(MCSPI_ChConfig));
    }

    config = (MCSPI_Config *)handle;

    if (Pmic_SystemP_SUCCESS == status)
    {
        /* Configure the MCSPI channel */
        MCSPI_setChConfig(config, chObj);

        chObj->isOpen   = TRUE;
        chObj->csEnable = TRUE;
    }

    return (status);
}

int32_t MCSPI_transfer(MCSPI_Handle handle, MCSPI_Transaction *transaction)
{
    int32_t            status = Pmic_SystemP_SUCCESS;
    uint32_t           baseAddr, chNum;
    MCSPI_Config      *config;
    MCSPI_Object      *obj;
    const MCSPI_Attrs *attrs;
    MCSPI_ChObject    *chObj;

    if (Pmic_SystemP_SUCCESS == status)
    {
        config   = (MCSPI_Config *)handle;
        obj      = config->object;
        attrs    = config->attrs;
        baseAddr = obj->baseAddr;

        if (Pmic_SystemP_SUCCESS == status)
        {
            /* Reset counter and other params */
            chNum                = transaction->channel;
            chObj                = &obj->chObj[chNum];
            chObj->curTxBufPtr   = (const uint8_t *)transaction->txBuf;
            chObj->curRxBufPtr   = (uint8_t *)transaction->rxBuf;
            chObj->curTxWords    = 0U;
            chObj->curRxWords    = 0U;
            obj->currTransaction = transaction;
            transaction->status  = MCSPI_TRANSFER_STARTED;

            /* Initialize channel dataSize */
            MCSPI_setChDataSize(baseAddr, chObj, transaction->dataSize, transaction->csDisable);
            MCSPI_setFifoConfig(chObj, attrs, baseAddr, transaction->count);
            MCSPI_intrStatusClear(chObj, baseAddr, chObj->intrMask);

            // status = MCSPI_transferControllerIntr(obj, chObj, attrs, transaction);

            MCSPI_transferControllerPoll(obj, chObj, attrs, transaction);

            gMcspiHandle1[0] = handle;
        }
    }

    return (status);
}

void SpiApp_interruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_LEVEL;

    intCfg.priority = 4;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR;
    intCfg.handler  = Spi_IrqUnitMcspi1TxRx;
    vimRegisterInterrupt(&intCfg);

    return;
}

void MCSPI_controllerIsr(void)
{
    int32_t            status = Pmic_SystemP_SUCCESS;
    uint32_t           transferStatus;
    MCSPI_Config      *config;
    MCSPI_Object      *obj;
    const MCSPI_Attrs *attrs;
    MCSPI_ChObject    *chObj;
    MCSPI_Transaction *transaction;
    uint32_t           baseAddr, chNum;
    MCSPI_Handle       handle;

    handle = gMcspiHandle1[0];
    if (Pmic_SystemP_SUCCESS == status)
    {
        config = (MCSPI_Config *)handle;
        obj    = config->object;
        attrs  = config->attrs;

        transaction = obj->currTransaction;
        baseAddr    = obj->baseAddr;
        if (transaction != NULL_CHECK)
        {
            chNum          = transaction->channel;
            chObj          = &obj->chObj[chNum];
            transferStatus = MCSPI_continueTxRx(obj, chObj, transaction);
            if (MCSPI_TRANSFER_COMPLETED == transferStatus)
            {
                /* Process the transfer completion. */
                /* Stop MCSPI Channel */
                MCSPI_stop(obj, attrs, chObj, chNum);
                /* Update the driver internal status. */
                /* transfer completed */
                transaction->status = MCSPI_TRANSFER_COMPLETED;
                /* Return the actual number of words transferred */
                obj->currTransaction->count = chObj->curRxWords;
                if (MCSPI_TR_MODE_TX_ONLY == chObj->chCfg.trMode)
                {
                    obj->currTransaction->count = chObj->curTxWords;
                }
                obj->currTransaction = NULL_CHECK;
            }
            /*
             * Else the transfer is still pending.
             * Do nothing, wait for next interrupt.
             */
        }
        else
        {
            /* There is no ongoing transfer. Disable and clear all interrupts. */
            CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQENABLE, 0U);
            MCSPI_clearAllIrqStatus(baseAddr);
        }
    }
    return;
}

static void MCSPI_initiateLastChunkTransfer(MCSPI_Object *obj, MCSPI_ChObject *chObj, MCSPI_Transaction *transaction)
{
    uint32_t baseAddr, chNum;
    uint32_t reminder;
    uint32_t regVal;

    baseAddr = obj->baseAddr;
    chNum    = chObj->chCfg.chNum;

    /* Disable channel so that new settings takes effect */
    chObj->chCtrlRegVal &= (~CSL_MCSPI_CH0CTRL_EN_MASK);
    CSL_REG32_WR(baseAddr + MCSPI_CHCTRL(chNum), chObj->chCtrlRegVal);

    /* Start transferring only multiple of FIFO trigger level */
    if (MCSPI_TR_MODE_RX_ONLY != chObj->chCfg.trMode)
    {
        reminder = (transaction->count & (chObj->effTxFifoDepth - 1U));
    }
    else
    {
        reminder = (transaction->count & (chObj->effRxFifoDepth - 1U));
    }

    /* Set FIFO trigger level and word count */
    regVal = 0;
    if (chObj->chCfg.rxFifoTrigLvl != 1)
    {
        regVal |= ((((reminder << chObj->bufWidthShift) - 1U) << CSL_MCSPI_XFERLEVEL_AFL_SHIFT) &
                   CSL_MCSPI_XFERLEVEL_AFL_MASK);
    }
    if (chObj->chCfg.txFifoTrigLvl != 1)
    {
        regVal |= ((((reminder << chObj->bufWidthShift) - 1U) << CSL_MCSPI_XFERLEVEL_AEL_SHIFT) &
                   CSL_MCSPI_XFERLEVEL_AEL_MASK);
    }
    regVal |= ((reminder << CSL_MCSPI_XFERLEVEL_WCNT_SHIFT) & CSL_MCSPI_XFERLEVEL_WCNT_MASK);

    CSL_REG32_WR(baseAddr + CSL_MCSPI_XFERLEVEL, regVal);

    /* Enable channel */
    chObj->chCtrlRegVal |= CSL_MCSPI_CH0CTRL_EN_MASK;
    CSL_REG32_WR(baseAddr + MCSPI_CHCTRL(chNum), chObj->chCtrlRegVal);
}

static uint32_t MCSPI_continueTxRx(MCSPI_Object *obj, MCSPI_ChObject *chObj, MCSPI_Transaction *transaction)
{
    uint32_t          baseAddr, chNum, txEmptyMask, rxFullMask;
    uint32_t          retVal = MCSPI_TRANSFER_STARTED;
    volatile uint32_t irqStatus, chStat;

    baseAddr    = obj->baseAddr;
    chNum       = chObj->chCfg.chNum;
    txEmptyMask = Spi_mcspiGetTxMask(chNum);
    rxFullMask  = Spi_mcspiGetRxMask(chNum);

    irqStatus = CSL_REG32_RD(baseAddr + CSL_MCSPI_IRQSTATUS);

    if ((irqStatus & chObj->intrMask) != 0)
    {
        /* Clear the interrupts being serviced. */
        CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQSTATUS, (irqStatus & chObj->intrMask));

        /* First read the data from the Rx FIFO. */
        if ((irqStatus & rxFullMask) == rxFullMask)
        {
            /* Perform RX only when enabled */
            if (MCSPI_TR_MODE_TX_ONLY != chObj->chCfg.trMode)
            {
                uint32_t numWordsToRead = transaction->count - chObj->curRxWords;
                if (numWordsToRead > chObj->effRxFifoDepth)
                {
                    numWordsToRead = chObj->effRxFifoDepth;
                }
                /* Read data from RX FIFO. */
                MCSPI_fifoRead(baseAddr, chObj, numWordsToRead);
            }
        }
        if ((irqStatus & txEmptyMask) == txEmptyMask)
        {
            uint32_t numWordsToWrite = transaction->count - chObj->curTxWords;
            if (numWordsToWrite > chObj->effTxFifoDepth)
            {
                numWordsToWrite = chObj->effTxFifoDepth;
            }

            /* Write the data in TX FIFO.Even in RX only mode, dummy data has to
               be written to receive data from Peripheral */
            MCSPI_fifoWrite(baseAddr, chObj, numWordsToWrite);
        }
        if ((irqStatus & CSL_MCSPI_IRQSTATUS_EOW_MASK) == CSL_MCSPI_IRQSTATUS_EOW_MASK)
        {
            if (MCSPI_TR_MODE_RX_ONLY != chObj->chCfg.trMode)
            {
                if (transaction->count == chObj->curTxWords)
                {
                    do
                    {
                        /* Wait for end of transfer. */
                        chStat = CSL_REG32_RD(baseAddr + MCSPI_CHSTAT(chNum));
                    } while ((chStat & CSL_MCSPI_CH0STAT_EOT_MASK) == 0);

                    /* read the last data if any from Rx FIFO. */
                    if ((MCSPI_TR_MODE_TX_ONLY != chObj->chCfg.trMode) && (transaction->count != chObj->curRxWords))
                    {
                        /* This is a corner case. EOW is set at the end of transmission.
                         * the reception is not complete by the time we are processing EOW.
                         * Read the remaining bytes.
                         */
                        MCSPI_fifoRead(baseAddr, chObj, (transaction->count - chObj->curRxWords));
                    }
                    /* Clear all interrupts. */
                    MCSPI_intrStatusClear(chObj, baseAddr, chObj->intrMask);

                    retVal = MCSPI_TRANSFER_COMPLETED;
                }
                else
                {
                    MCSPI_initiateLastChunkTransfer(obj, chObj, transaction);
                }
            }
            else
            {
                if (transaction->count == chObj->curRxWords)
                {
                    do
                    {
                        /* Wait for end of transfer. */
                        chStat = CSL_REG32_RD(baseAddr + MCSPI_CHSTAT(chNum));
                    } while ((chStat & CSL_MCSPI_CH0STAT_EOT_MASK) == 0);
                    /* Clear all interrupts. */
                    MCSPI_intrStatusClear(chObj, baseAddr, chObj->intrMask);
                    retVal = MCSPI_TRANSFER_COMPLETED;
                }
                else
                {
                    MCSPI_initiateLastChunkTransfer(obj, chObj, transaction);
                }
            }
        }
    }

    return retVal;
}

static int32_t MCSPI_transferControllerPoll(MCSPI_Object *obj, MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs,
                                            MCSPI_Transaction *transaction)
{
    int32_t  status = Pmic_SystemP_SUCCESS;
    uint32_t baseAddr, chNum;
    uint32_t numWordsToWrite, txEmptyMask, irqStatus;

    baseAddr = obj->baseAddr;
    chNum    = chObj->chCfg.chNum;

    /* Manual CS assert */
    if (MCSPI_CH_MODE_SINGLE == attrs->chMode)
    {
        if (chObj->csEnable == TRUE)
        {
            chObj->chConfRegVal |= CSL_MCSPI_CH0CONF_FORCE_MASK;
            CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chObj->chCfg.chNum), chObj->chConfRegVal);
            chObj->csEnable = FALSE;
        }
    }

    /* Enable channel */
    chObj->chCtrlRegVal |= CSL_MCSPI_CH0CTRL_EN_MASK;
    CSL_REG32_WR(baseAddr + MCSPI_CHCTRL(chNum), chObj->chCtrlRegVal);

    /* wait for the Tx Empty bit to be set. */
    txEmptyMask = Spi_mcspiGetTxMask(chNum);
    while ((MCSPI_readChStatusReg(baseAddr, chNum) & CSL_MCSPI_CH0STAT_TXS_MASK) == 0)
    {
        /* wait for the Tx Empty Event. */
    }
    /* Initially write the full Tx FIFO */
    if (transaction->count > chObj->effTxFifoDepth)
    {
        numWordsToWrite = chObj->effTxFifoDepth;
    }
    else
    {
        numWordsToWrite = transaction->count;
    }
    /* Write the data in TX FIFO.Even in RX only mode, dummy data has to
        be written to receive data from Peripheral */
    MCSPI_fifoWrite(baseAddr, chObj, numWordsToWrite);

    if (MCSPI_TR_MODE_TX_ONLY != chObj->chCfg.trMode)
    {
        while (((transaction->count - chObj->curTxWords) != 0) || ((transaction->count - chObj->curRxWords) != 0))
        {
            /* Now keep polling the CH_STAT register, if RXs bit is set, at least 1 word is
            available. Read the data from Rx register, also write the same number of bytes in Tx
            register. In case of controller mode only when 1 word is sent out, 1 word will be
            received. */
            if ((MCSPI_readChStatusReg(baseAddr, chNum) & CSL_MCSPI_CH0STAT_RXS_MASK) != 0)
            {
                MCSPI_fifoRead(baseAddr, chObj, 1);
                if (transaction->count > chObj->curTxWords)
                {
                    MCSPI_fifoWrite(baseAddr, chObj, 1);
                }
            }
        }
    }
    else
    {
        txEmptyMask = Spi_mcspiGetTxMask(chNum);
        while ((transaction->count - chObj->curTxWords) != 0)
        {
            irqStatus = CSL_REG32_RD(baseAddr + CSL_MCSPI_IRQSTATUS);

            if ((irqStatus & chObj->intrMask) != 0)
            {
                /* Clear the interrupts being serviced. */
                CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQSTATUS, (irqStatus & chObj->intrMask));
                if ((irqStatus & txEmptyMask) == txEmptyMask)
                {
                    uint32_t numWordsToWrite = transaction->count - chObj->curTxWords;
                    if (numWordsToWrite > chObj->effTxFifoDepth)
                    {
                        numWordsToWrite = chObj->effTxFifoDepth;
                    }

                    /* Write the data in TX FIFO.Even in RX only mode, dummy data has to
                    be written to receive data from Peripheral */
                    MCSPI_fifoWrite(baseAddr, chObj, numWordsToWrite);
                }
            }
        }
        /* Wait for the last byte to be sent out. */
        while (0 == (MCSPI_readChStatusReg(baseAddr, chNum) & CSL_MCSPI_CH0STAT_TXFFE_MASK))
        {
            /* Wait fot Tx FIFO to be empty for the last set of data. */
        }
        while (0 == (MCSPI_readChStatusReg(baseAddr, chNum) & CSL_MCSPI_CH0STAT_EOT_MASK))
        {
            /* Tx FIFO Empty is triggered when last word from FIFO is written to
            internal shift register. SO wait for the end of transfer of last word.
            The EOT gets set after every word when the transfer from shift
            register is complete and is reset when the transmission starts.
            So FIFO empty check is required to make sure the data in FIFO is
            sent out then wait for EOT for the last word. */
        }
    }

    /* Stop MCSPI Channel */
    MCSPI_stop(obj, attrs, chObj, chNum);

    return (status);
}

static int32_t MCSPI_transferControllerIntr(MCSPI_Object *obj, MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs,
                                            MCSPI_Transaction *transaction)
{
    int32_t  status = Pmic_SystemP_SUCCESS;
    uint32_t baseAddr, chNum;

    baseAddr = obj->baseAddr;
    chNum    = chObj->chCfg.chNum;

    CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQENABLE, chObj->intrMask);

    /* Manual CS assert */
    if (MCSPI_CH_MODE_SINGLE == attrs->chMode)
    {
        if (chObj->csEnable == TRUE)
        {
            chObj->chConfRegVal |= CSL_MCSPI_CH0CONF_FORCE_MASK;
            CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chObj->chCfg.chNum), chObj->chConfRegVal);
            chObj->csEnable = FALSE;
        }
    }

    /* Enable channel */
    chObj->chCtrlRegVal |= CSL_MCSPI_CH0CTRL_EN_MASK;
    CSL_REG32_WR(baseAddr + MCSPI_CHCTRL(chNum), chObj->chCtrlRegVal);

    /*
     * Note: Once the channel is enabled, we will get the TX almost empty
     *       interrupt. No data transfer is required here!!
     */
    return (status);
}

static uint32_t MCSPI_continuePeripheralTxRx(MCSPI_Object *obj, MCSPI_ChObject *chObj, MCSPI_Transaction *transaction)
{
    uint32_t          baseAddr, chNum, chStat;
    uint32_t          retVal = MCSPI_TRANSFER_STARTED;
    volatile uint32_t irqStatus;

    baseAddr = obj->baseAddr;
    chNum    = chObj->chCfg.chNum;

    irqStatus = CSL_REG32_RD(baseAddr + CSL_MCSPI_IRQSTATUS);

    if ((irqStatus & chObj->intrMask) != 0)
    {
        /* Clear the interrupts being serviced. */
        CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQSTATUS, (irqStatus & chObj->intrMask));

        /* First read the data from the Rx FIFO. */
        if (irqStatus & (CSL_MCSPI_IRQSTATUS_RX0_FULL_MASK << (4 * chNum)))
        {
            /* Perform RX only when enabled */
            if (MCSPI_TR_MODE_TX_ONLY != chObj->chCfg.trMode)
            {
                uint32_t numWordsToRead = transaction->count - chObj->curRxWords;
                if (numWordsToRead > chObj->effRxFifoDepth)
                {
                    numWordsToRead = chObj->effRxFifoDepth;
                }
                /* Read data from RX FIFO. */
                MCSPI_fifoRead(baseAddr, chObj, numWordsToRead);
                /* Check if transfer is completed for current transaction. */
                if (transaction->count == chObj->curRxWords)
                {
                    retVal = MCSPI_TRANSFER_COMPLETED;
                }
            }
        }
        if (irqStatus & (CSL_MCSPI_IRQSTATUS_TX0_EMPTY_MASK << (4 * chNum)))
        {
            /* Perform TX only when enabled */
            if (MCSPI_TR_MODE_RX_ONLY != chObj->chCfg.trMode)
            {
                uint32_t numWordsToWrite = transaction->count - chObj->curTxWords;
                if (numWordsToWrite > chObj->effTxFifoDepth)
                {
                    numWordsToWrite = chObj->effTxFifoDepth;
                }
                /* Write the data in TX FIFO. */
                MCSPI_fifoWrite(baseAddr, chObj, numWordsToWrite);
                if (MCSPI_TR_MODE_TX_ONLY == chObj->chCfg.trMode)
                {
                    /* Check if transfer is completed for current transaction. */
                    if (transaction->count == chObj->curTxWords)
                    {
                        do
                        {
                            /* Wait for TX FIFO Empty. */
                            chStat = CSL_REG32_RD(baseAddr + MCSPI_CHSTAT(chNum));
                        } while ((chStat & CSL_MCSPI_CH0STAT_TXFFE_MASK) == 0);
                        do
                        {
                            /* Wait for end of transfer. */
                            chStat = CSL_REG32_RD(baseAddr + MCSPI_CHSTAT(chNum));
                        } while ((chStat & CSL_MCSPI_CH0STAT_EOT_MASK) == 0);
                        retVal = MCSPI_TRANSFER_COMPLETED;
                    }
                }
            }
        }
        /* Check for Rx overflow or Tx underflow.
         * Cancel the current transfer and return error. */
        if ((irqStatus & (CSL_MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK)) ||
            (irqStatus & (CSL_MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK << (4 * chNum))))
        {
            retVal = MCSPI_TRANSFER_CANCELLED;
        }
    }

    return retVal;
}

static int32_t MCSPI_transferPeripheralIntr(MCSPI_Object *obj, MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs,
                                            MCSPI_Transaction *transaction)
{
    int32_t  status = Pmic_SystemP_SUCCESS;
    uint32_t baseAddr, chNum;

    baseAddr = obj->baseAddr;
    chNum    = chObj->chCfg.chNum;

    CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQENABLE, chObj->intrMask);

    /* Enable channel */
    chObj->chCtrlRegVal |= CSL_MCSPI_CH0CTRL_EN_MASK;
    CSL_REG32_WR(baseAddr + MCSPI_CHCTRL(chNum), chObj->chCtrlRegVal);

    /*
     * Note: Once the channel is enabled, we will get the TX almost empty
     *       interrupt. No data transfer is required here!!
     */

    return (status);
}

static inline void MCSPI_fifoWrite(uint32_t baseAddr, MCSPI_ChObject *chObj, uint32_t transferLength)
{
    uint32_t chNum;

    chNum = chObj->chCfg.chNum;
    if (NULL_CHECK != chObj->curTxBufPtr)
    {
        if (0U == chObj->bufWidthShift)
        {
            chObj->curTxBufPtr = MCSPI_fifoWrite8(baseAddr, chNum, chObj->curTxBufPtr, transferLength);
        }
        else if (1U == chObj->bufWidthShift)
        {
            chObj->curTxBufPtr = (const uint8_t *)MCSPI_fifoWrite16(
                baseAddr, chNum, (const uint16_t *)chObj->curTxBufPtr, transferLength);
        }
        else
        {
            chObj->curTxBufPtr = (const uint8_t *)MCSPI_fifoWrite32(
                baseAddr, chNum, (const uint32_t *)chObj->curTxBufPtr, transferLength);
        }
    }
    else
    {
        /* NULL_CHECK TX pointer provided. Use default data */
        MCSPI_fifoWriteDefault(baseAddr, chNum, chObj->chCfg.defaultTxData, transferLength);
    }
    chObj->curTxWords += transferLength;

    return;
}

static inline void MCSPI_fifoRead(uint32_t baseAddr, MCSPI_ChObject *chObj, uint32_t transferLength)
{
    uint32_t chNum;

    chNum = chObj->chCfg.chNum;
    if (NULL_CHECK != chObj->curRxBufPtr)
    {
        if (0U == chObj->bufWidthShift)
        {
            chObj->curRxBufPtr =
                MCSPI_fifoRead8(baseAddr, chNum, chObj->curRxBufPtr, transferLength, chObj->dataWidthBitMask);
        }
        else if (1U == chObj->bufWidthShift)
        {
            chObj->curRxBufPtr = (uint8_t *)MCSPI_fifoRead16(baseAddr, chNum, (uint16_t *)chObj->curRxBufPtr,
                                                             transferLength, chObj->dataWidthBitMask);
        }
        else
        {
            chObj->curRxBufPtr = (uint8_t *)MCSPI_fifoRead32(baseAddr, chNum, (uint32_t *)chObj->curRxBufPtr,
                                                             transferLength, chObj->dataWidthBitMask);
        }
    }
    else
    {
        /* NULL_CHECK RX pointer provided. Read and discard data */
        MCSPI_fifoReadDiscard(baseAddr, chNum, transferLength);
    }
    chObj->curRxWords += transferLength;

    return;
}

static void MCSPI_configInstance(MCSPI_Config *config)
{
    uint32_t           regVal;
    uint32_t           baseAddr;
    const MCSPI_Attrs *attrs;
    MCSPI_OpenParams  *openPrms;

    attrs    = config->attrs;
    baseAddr = config->object->baseAddr;
    openPrms = &config->object->openPrms;

    /* Reset MCSPI */
    MCSPI_reset(baseAddr);

    /* Set sysconfig */
    regVal = ((CSL_MCSPI_SYSCONFIG_CLOCKACTIVITY_BOTH << CSL_MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT) |
              (CSL_MCSPI_SYSCONFIG_SIDLEMODE_NO << CSL_MCSPI_SYSCONFIG_SIDLEMODE_SHIFT) |
              (CSL_MCSPI_SYSCONFIG_ENAWAKEUP_NOWAKEUP << CSL_MCSPI_SYSCONFIG_ENAWAKEUP_SHIFT) |
              (CSL_MCSPI_SYSCONFIG_AUTOIDLE_OFF << CSL_MCSPI_SYSCONFIG_AUTOIDLE_SHIFT));
    CSL_REG32_WR(baseAddr + CSL_MCSPI_SYSCONFIG, regVal);

    /* Set module control */
    regVal = (openPrms->msMode << CSL_MCSPI_MODULCTRL_MS_SHIFT);
    /* Configure Single/Multi Channel in controller mode only */
    if (MCSPI_MS_MODE_CONTROLLER == openPrms->msMode)
    {
        regVal |= (attrs->chMode << CSL_MCSPI_MODULCTRL_SINGLE_SHIFT);
    }
    if (MCSPI_CH_MODE_SINGLE == attrs->chMode)
    {
        /* 3/4 pin mode applicable only in single channel mode.
         * For  multi-ch mode, CS is always controlled by HW during transfer */
        regVal |= (attrs->pinMode << CSL_MCSPI_MODULCTRL_PIN34_SHIFT);
        if (MCSPI_MS_MODE_CONTROLLER == openPrms->msMode)
        {
            /* Init delay applicable only for single controller mode */
            regVal |= (attrs->initDelay << CSL_MCSPI_MODULCTRL_INITDLY_SHIFT);
        }
    }
    CSL_REG32_WR(baseAddr + CSL_MCSPI_MODULCTRL, regVal);

    return;
}

static void MCSPI_setChConfig(MCSPI_Config *config, MCSPI_ChObject *chObj)
{
    uint32_t           regVal;
    uint32_t           baseAddr, chNum;
    MCSPI_ChConfig    *chCfg;
    const MCSPI_Attrs *attrs;

    attrs    = config->attrs;
    baseAddr = config->object->baseAddr;
    chNum    = chObj->chCfg.chNum;
    chCfg    = &chObj->chCfg;

    regVal = CSL_REG32_RD(baseAddr + MCSPI_CHCONF(chNum));

    /* Clear and set PHA, POL fields */
    regVal &= ~((uint32_t)CSL_MCSPI_CH0CONF_PHA_MASK | (uint32_t)CSL_MCSPI_CH3CONF_POL_MASK);
    regVal |= (chCfg->frameFormat & ((uint32_t)CSL_MCSPI_CH0CONF_PHA_MASK | (uint32_t)CSL_MCSPI_CH3CONF_POL_MASK));
    CSL_FINS(regVal, MCSPI_CH0CONF_EPOL, chCfg->csPolarity);
    CSL_FINS(regVal, MCSPI_CH0CONF_TRM, chCfg->trMode);
    CSL_FINS(regVal, MCSPI_CH0CONF_IS, chCfg->inputSelect);
    CSL_FINS(regVal, MCSPI_CH0CONF_DPE0, chCfg->dpe0);
    CSL_FINS(regVal, MCSPI_CH0CONF_DPE1, chCfg->dpe1);
    CSL_FINS(regVal, MCSPI_CH0CONF_SPIENSLV, chCfg->slvCsSelect);
    CSL_FINS(regVal, MCSPI_CH0CONF_SBE, chCfg->startBitEnable);
    CSL_FINS(regVal, MCSPI_CH0CONF_SBPOL, chCfg->startBitPolarity);
    CSL_FINS(regVal, MCSPI_CH0CONF_TCS0, chCfg->csIdleTime);

    CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chNum), regVal);

    /* Set clock dividers */
    MCSPI_setClkConfig(baseAddr, chNum, attrs->inputClkFreq, chCfg->bitRate);

    if (config->object->openPrms.msMode == MCSPI_MS_MODE_PERIPHERAL)
    {
        if (MCSPI_TR_MODE_TX_RX == chObj->chCfg.trMode)
        {
            chObj->intrMask =
                ((CSL_MCSPI_IRQSTATUS_RX0_FULL_MASK << (4 * chNum)) |
                 (CSL_MCSPI_IRQSTATUS_TX0_EMPTY_MASK << (4 * chNum)) |
                 (CSL_MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK << (4 * chNum)) | (CSL_MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK));
        }
        else if (MCSPI_TR_MODE_TX_ONLY == chObj->chCfg.trMode)
        {
            chObj->intrMask = ((CSL_MCSPI_IRQSTATUS_TX0_EMPTY_MASK << (4 * chNum)) |
                               (CSL_MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK << (4 * chNum)));
        }
        else
        {
            chObj->intrMask =
                ((CSL_MCSPI_IRQSTATUS_RX0_FULL_MASK << (4 * chNum)) | (CSL_MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK));
        }
    }
    else
    {
        if (MCSPI_TR_MODE_TX_RX == chObj->chCfg.trMode)
        {
            chObj->intrMask = ((CSL_MCSPI_IRQSTATUS_RX0_FULL_MASK << (4 * chNum)) |
                               (CSL_MCSPI_IRQSTATUS_TX0_EMPTY_MASK << (4 * chNum)) | CSL_MCSPI_IRQSTATUS_EOW_MASK);
        }
        else if (MCSPI_TR_MODE_TX_ONLY == chObj->chCfg.trMode)
        {
            chObj->intrMask = ((CSL_MCSPI_IRQSTATUS_TX0_EMPTY_MASK << (4 * chNum)) | (CSL_MCSPI_IRQSTATUS_EOW_MASK));
        }
        else
        {
            chObj->intrMask = ((CSL_MCSPI_IRQSTATUS_RX0_FULL_MASK << (4 * chNum)) |
                               (CSL_MCSPI_IRQSTATUS_TX0_EMPTY_MASK << (4 * chNum)) | (CSL_MCSPI_IRQSTATUS_EOW_MASK));
        }
    }

    /* Store Ch Conf, Ch Ctrl, Syst register values in channel object. */
    chObj->chConfRegVal = CSL_REG32_RD(baseAddr + MCSPI_CHCONF(chNum));
    chObj->chCtrlRegVal = CSL_REG32_RD(baseAddr + MCSPI_CHCTRL(chNum));
    chObj->systRegVal   = CSL_REG32_RD(baseAddr + CSL_MCSPI_SYST) & (~(CSL_MCSPI_SYST_SSB_MASK));

    return;
}

static int32_t MCSPI_checkOpenParams(const MCSPI_OpenParams *openPrms)
{
    int32_t status = Pmic_SystemP_SUCCESS;

    if ((MCSPI_TRANSFER_MODE_CALLBACK == openPrms->transferMode) && (NULL_CHECK == openPrms->transferCallbackFxn))
    {
        status = Pmic_SystemP_FAILURE;
    }

    return (status);
}

static int32_t MCSPI_checkChConfig(MCSPI_Object *obj, const MCSPI_ChConfig *chCfg)
{
    int32_t status = Pmic_SystemP_SUCCESS;

    if ((obj->openPrms.msMode == MCSPI_MS_MODE_PERIPHERAL) && (chCfg->chNum != 0))
    {
        status = Pmic_SystemP_FAILURE;
    }

    return (status);
}

static int32_t MCSPI_checkTransaction(const MCSPI_Object *obj, MCSPI_Transaction *transaction)
{
    int32_t status = Pmic_SystemP_SUCCESS;

    if (0U == transaction->count)
    {
        /* Transfer count should be positive */
        transaction->status = MCSPI_TRANSFER_FAILED;
        status              = Pmic_SystemP_FAILURE;
    }
    else if (transaction->channel >= MCSPI_MAX_NUM_CHANNELS)
    {
        /* Invalid channel */
        transaction->status = MCSPI_TRANSFER_FAILED;
        status              = Pmic_SystemP_FAILURE;
    }
    else if ((transaction->dataSize < 4U) || (transaction->dataSize > 32U))
    {
        /* Unsupported word length or data size */
        transaction->status = MCSPI_TRANSFER_FAILED;
        status              = Pmic_SystemP_FAILURE;
    }
    else
    {
        /* Check if the channel is configured */
        if (TRUE != obj->chObj[transaction->channel].isOpen)
        {
            /* Channel not configured */
            transaction->status = MCSPI_TRANSFER_FAILED;
            status              = Pmic_SystemP_FAILURE;
        }
    }

    return (status);
}

static uint32_t MCSPI_getDataWidthBitMask(uint32_t dataWidth)
{
    uint32_t i, fifoBitMask = 0x0U;
    uint32_t tmpVar = 0U;

    for (i = 0U; i < dataWidth; i++)
    {
        tmpVar       = ((uint32_t)1U << i);
        fifoBitMask |= tmpVar;
    }

    return (fifoBitMask);
}

static void MCSPI_reset(uint32_t baseAddr)
{
    uint32_t regVal;

    /* Set the SOFTRESET field of MCSPI_SYSCONFIG register. */
    CSL_REG32_FINS(baseAddr + CSL_MCSPI_SYSCONFIG, MCSPI_SYSCONFIG_SOFTRESET, CSL_MCSPI_SYSCONFIG_SOFTRESET_ON);

    /* Stay in the loop until reset is done. */
    while (1U)
    {
        regVal = CSL_REG32_RD(baseAddr + CSL_MCSPI_SYSSTATUS);
        if ((regVal & CSL_MCSPI_SYSSTATUS_RESETDONE_MASK) == CSL_MCSPI_SYSSTATUS_RESETDONE_MASK)
        {
            break;
        }
        /* Busy wait */
    }
}

static void MCSPI_setClkConfig(uint32_t baseAddr, uint32_t chNum, uint32_t inputClkFreq, uint32_t bitRate)
{
    uint32_t fRatio;
    uint32_t clkD;
    uint32_t extClk;

    /* Calculate the value of fRatio. */
    fRatio = inputClkFreq / bitRate;
    if ((fRatio * bitRate) != inputClkFreq)
    {
        /* use a higher divider value in case the ratio
         * is fractional so that we get a lower SPI clock
         * than requested. This ensures we don't go beyond
         * recommended clock speed for the SPI peripheral */
        fRatio++;
    }

    /* If fRatio is not a power of 2, set granularity of 1 clock cycle */
    if ((uint32_t)0U != (fRatio & (fRatio - 1U)))
    {
        /* Set the clock granularity to 1 clock cycle */
        CSL_REG32_FINS(baseAddr + MCSPI_CHCONF(chNum), MCSPI_CH0CONF_CLKG, CSL_MCSPI_CH0CONF_CLKG_ONECYCLE);

        /* Calculate the ratios clkD and extClk based on fClk */
        extClk = (fRatio - 1U) >> 4U;
        clkD   = (fRatio - 1U) & (uint32_t)MCSPI_CLKD_MASK;

        /* Set the extClk field */
        CSL_REG32_FINS(baseAddr + MCSPI_CHCTRL(chNum), MCSPI_CH0CTRL_EXTCLK, extClk);
    }
    else
    {
        /* Clock granularity of power of 2 */
        CSL_REG32_FINS(baseAddr + MCSPI_CHCONF(chNum), MCSPI_CH0CONF_CLKG, CSL_MCSPI_CH0CONF_CLKG_POWERTWO);

        clkD = 0U;
        while (1U != fRatio)
        {
            fRatio >>= 1U;
            clkD++;
        }
    }

    /* Configure the clkD field */
    CSL_REG32_FINS(baseAddr + MCSPI_CHCONF(chNum), MCSPI_CH0CONF_CLKD, clkD);

    return;
}

static void MCSPI_setFifoConfig(MCSPI_ChObject *chObj, const MCSPI_Attrs *attrs, uint32_t baseAddr,
                                uint32_t numWordsTxRx)
{
    uint32_t txFifoTrigLvl, rxFifoTrigLvl;
    uint32_t regVal;
    uint32_t reminder = 0, effNumWordsTxRx;

    if (MCSPI_OPER_MODE_INTERRUPT == attrs->operMode)
    {
        /* Start transferring only multiple of FIFO trigger level */
        if (MCSPI_TR_MODE_RX_ONLY != chObj->chCfg.trMode)
        {
            reminder = (numWordsTxRx & (chObj->effTxFifoDepth - 1U));
        }
        else
        {
            reminder = (numWordsTxRx & (chObj->effRxFifoDepth - 1U));
        }

        effNumWordsTxRx = numWordsTxRx - reminder;
    }
    else
    {
        effNumWordsTxRx = numWordsTxRx;
    }

    rxFifoTrigLvl = chObj->chCfg.rxFifoTrigLvl;
    txFifoTrigLvl = chObj->chCfg.txFifoTrigLvl;

    /* Handle transfers with less than FIFO level.
     * Set FIFO trigger level and word count to be equal to the
     * reminder word. Otherwise the HW doesn't generating TX
     * empty interrupt if WCNT is less than FIFO trigger level */
    if (effNumWordsTxRx == 0U)
    {
        effNumWordsTxRx = reminder;
        if (txFifoTrigLvl != 1U)
        {
            /* Set TX level only when TX FIFO is enabled */
            txFifoTrigLvl = reminder << chObj->bufWidthShift;
        }
        if (rxFifoTrigLvl != 1U)
        {
            /* Set RX level only when RX FIFO is enabled */
            rxFifoTrigLvl = reminder << chObj->bufWidthShift;
        }
    }

    /* Set FIFO trigger level and word count.
       Setting all fields in register below, so read modify write not required. */
    regVal  = 0;
    regVal |= (((rxFifoTrigLvl - 1U) << CSL_MCSPI_XFERLEVEL_AFL_SHIFT) & CSL_MCSPI_XFERLEVEL_AFL_MASK);
    regVal |= (((txFifoTrigLvl - 1U) << CSL_MCSPI_XFERLEVEL_AEL_SHIFT) & CSL_MCSPI_XFERLEVEL_AEL_MASK);
    regVal |= ((effNumWordsTxRx << CSL_MCSPI_XFERLEVEL_WCNT_SHIFT) & CSL_MCSPI_XFERLEVEL_WCNT_MASK);
    CSL_REG32_WR(baseAddr + CSL_MCSPI_XFERLEVEL, regVal);

    /* Enable TX and RX FIFO */
    chObj->chConfRegVal &= ~(CSL_MCSPI_CH0CONF_FFEW_MASK | CSL_MCSPI_CH0CONF_FFER_MASK);
    if (MCSPI_TR_MODE_TX_RX == chObj->chCfg.trMode)
    {
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFEW_FFENABLED << CSL_MCSPI_CH0CONF_FFEW_SHIFT);
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFER_FFENABLED << CSL_MCSPI_CH0CONF_FFER_SHIFT);
    }
    else if (MCSPI_TR_MODE_TX_ONLY == chObj->chCfg.trMode)
    {
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFEW_FFENABLED << CSL_MCSPI_CH0CONF_FFEW_SHIFT);
    }
    else
    {
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFER_FFENABLED << CSL_MCSPI_CH0CONF_FFER_SHIFT);
    }
    CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chObj->chCfg.chNum), chObj->chConfRegVal);

    return;
}

static uint32_t MCSPI_getFifoTrigLvl(uint32_t numWords, uint32_t fifoDepth)
{
    uint32_t fifoTrigLvl = 1U;
    if (numWords > fifoDepth)
    {
        uint32_t i;
        for (i = fifoDepth; i > 0; i--)
        {
            if ((numWords % i) == 0)
            {
                fifoTrigLvl = i;
                break;
            }
        }
    }
    else
    {
        fifoTrigLvl = numWords;
    }
    return fifoTrigLvl;
}

static void MCSPI_setPeripheralFifoConfig(MCSPI_ChObject *chObj, uint32_t baseAddr, uint32_t numWordsTxRx)
{
    uint32_t txFifoTrigLvl, rxFifoTrigLvl;
    uint32_t regVal;

    /* Find Fifo depth to configure to be multiple of number of words to transfer. */
    chObj->effTxFifoDepth = MCSPI_getFifoTrigLvl(numWordsTxRx, chObj->chCfg.txFifoTrigLvl >> chObj->bufWidthShift);
    chObj->effRxFifoDepth = MCSPI_getFifoTrigLvl(numWordsTxRx, chObj->chCfg.rxFifoTrigLvl >> chObj->bufWidthShift);

    txFifoTrigLvl = chObj->effTxFifoDepth << chObj->bufWidthShift;
    rxFifoTrigLvl = chObj->effRxFifoDepth << chObj->bufWidthShift;

    /* Set FIFO trigger level. word count set to 0 for slve mode.
       Setting all fields in register below, so read modify write not required. */
    regVal  = 0;
    regVal |= (((rxFifoTrigLvl - 1U) << CSL_MCSPI_XFERLEVEL_AFL_SHIFT) & CSL_MCSPI_XFERLEVEL_AFL_MASK);
    regVal |= (((txFifoTrigLvl - 1U) << CSL_MCSPI_XFERLEVEL_AEL_SHIFT) & CSL_MCSPI_XFERLEVEL_AEL_MASK);
    regVal &= ~CSL_MCSPI_XFERLEVEL_WCNT_MASK;
    CSL_REG32_WR(baseAddr + CSL_MCSPI_XFERLEVEL, regVal);

    /* Enable TX and RX FIFO */
    chObj->chConfRegVal &= ~(CSL_MCSPI_CH0CONF_FFEW_MASK | CSL_MCSPI_CH0CONF_FFER_MASK);
    if (MCSPI_TR_MODE_TX_RX == chObj->chCfg.trMode)
    {
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFEW_FFENABLED << CSL_MCSPI_CH0CONF_FFEW_SHIFT);
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFER_FFENABLED << CSL_MCSPI_CH0CONF_FFER_SHIFT);
    }
    else if (MCSPI_TR_MODE_TX_ONLY == chObj->chCfg.trMode)
    {
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFEW_FFENABLED << CSL_MCSPI_CH0CONF_FFEW_SHIFT);
    }
    else
    {
        chObj->chConfRegVal |= (CSL_MCSPI_CH0CONF_FFER_FFENABLED << CSL_MCSPI_CH0CONF_FFER_SHIFT);
    }
    CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chObj->chCfg.chNum), chObj->chConfRegVal);

    return;
}

static inline const uint8_t *MCSPI_fifoWrite8(uint32_t baseAddr, uint32_t chNum, const uint8_t *bufPtr,
                                              uint32_t transferLength)
{
    uint32_t i, txData;

    /* Write the data in TX FIFO for 8-bit transfer */
    for (i = 0; i < transferLength; i++)
    {
        txData = *bufPtr++;
        CSL_REG32_WR(baseAddr + MCSPI_CHTX(chNum), txData);
    }

    return (bufPtr);
}

static inline const uint16_t *MCSPI_fifoWrite16(uint32_t baseAddr, uint32_t chNum, const uint16_t *bufPtr,
                                                uint32_t transferLength)
{
    uint32_t i, txData;

    /* Write the data in TX FIFO for 16-bit transfer */
    for (i = 0; i < transferLength; i++)
    {
        txData = *bufPtr++;
        CSL_REG32_WR(baseAddr + MCSPI_CHTX(chNum), txData);
    }

    return (bufPtr);
}

static inline const uint32_t *MCSPI_fifoWrite32(uint32_t baseAddr, uint32_t chNum, const uint32_t *bufPtr,
                                                uint32_t transferLength)
{
    uint32_t i, txData;

    /* Write the data in TX FIFO for 32-bit transfer */
    for (i = 0; i < transferLength; i++)
    {
        txData = *bufPtr++;
        CSL_REG32_WR(baseAddr + MCSPI_CHTX(chNum), txData);
    }

    return (bufPtr);
}

static inline uint8_t *MCSPI_fifoRead8(uint32_t baseAddr, uint32_t chNum, uint8_t *bufPtr, uint32_t transferLength,
                                       uint32_t dataWidthBitMask)
{
    uint32_t i, rxData;

    /* Read the data from RX FIFO for 8-bit transfer */
    for (i = 0; i < transferLength; i++)
    {
        rxData     = MCSPI_readRxDataReg(baseAddr, chNum);
        rxData    &= dataWidthBitMask; /* Clear unused bits */
        *bufPtr++  = (uint8_t)rxData;
    }

    return (bufPtr);
}

static inline uint16_t *MCSPI_fifoRead16(uint32_t baseAddr, uint32_t chNum, uint16_t *bufPtr, uint32_t transferLength,
                                         uint32_t dataWidthBitMask)
{
    uint32_t i, rxData;

    /* Read the data from RX FIFO for 16-bit transfer */
    for (i = 0; i < transferLength; i++)
    {
        rxData     = MCSPI_readRxDataReg(baseAddr, chNum);
        rxData    &= dataWidthBitMask; /* Clear unused bits */
        *bufPtr++  = (uint16_t)rxData;
    }

    return (bufPtr);
}

static inline uint32_t *MCSPI_fifoRead32(uint32_t baseAddr, uint32_t chNum, uint32_t *bufPtr, uint32_t transferLength,
                                         uint32_t dataWidthBitMask)
{
    uint32_t i, rxData;

    /* Read the data from RX FIFO for 32-bit transfer */
    for (i = 0; i < transferLength; i++)
    {
        rxData     = MCSPI_readRxDataReg(baseAddr, chNum);
        rxData    &= dataWidthBitMask; /* Clear unused bits */
        *bufPtr++  = (uint32_t)rxData;
    }

    return (bufPtr);
}

static inline void MCSPI_fifoWriteDefault(uint32_t baseAddr, uint32_t chNum, uint32_t defaultTxData,
                                          uint32_t transferLength)
{
    uint32_t i;

    /* Write default data to TX FIFO */
    for (i = 0; i < transferLength; i++)
    {
        CSL_REG32_WR(baseAddr + MCSPI_CHTX(chNum), defaultTxData);
    }

    return;
}

static inline void MCSPI_fifoReadDiscard(uint32_t baseAddr, uint32_t chNum, uint32_t transferLength)
{
    uint32_t          i;
    volatile uint32_t rxData;

    /* Read the data from RX FIFO and discard it */
    for (i = 0; i < transferLength; i++)
    {
        rxData = MCSPI_readRxDataReg(baseAddr, chNum);
        (void)rxData;
    }

    return;
}

static void MCSPI_clearAllIrqStatus(uint32_t baseAddr)
{
    /* Clear all previous interrupt status */
    CSL_REG32_FINS(baseAddr + CSL_MCSPI_SYST, MCSPI_SYST_SSB, CSL_MCSPI_SYST_SSB_OFF);
    CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQSTATUS, MCSPI_IRQSTATUS_CLEAR_ALL);

    return;
}

static uint32_t Spi_mcspiGetTxMask(uint32_t csNum)
{
    uint32_t txEmptyMask;

    if ((uint32_t)MCSPI_CHANNEL_0 == csNum)
    {
        txEmptyMask = (uint32_t)CSL_MCSPI_IRQSTATUS_TX0_EMPTY_MASK;
    }
    else if ((uint32_t)MCSPI_CHANNEL_1 == csNum)
    {
        txEmptyMask = (uint32_t)CSL_MCSPI_IRQSTATUS_TX1_EMPTY_MASK;
    }
    else if ((uint32_t)MCSPI_CHANNEL_2 == csNum)
    {
        txEmptyMask = (uint32_t)CSL_MCSPI_IRQSTATUS_TX2_EMPTY_MASK;
    }
    else
    {
        txEmptyMask = (uint32_t)CSL_MCSPI_IRQSTATUS_TX3_EMPTY_MASK;
    }

    return (txEmptyMask);
}

static uint32_t Spi_mcspiGetRxMask(uint32_t csNum)
{
    uint32_t rxFullMask;

    if ((uint32_t)MCSPI_CHANNEL_0 == csNum)
    {
        rxFullMask = (uint32_t)CSL_MCSPI_IRQSTATUS_RX0_FULL_MASK;
    }
    else if ((uint32_t)MCSPI_CHANNEL_1 == csNum)
    {
        rxFullMask = (uint32_t)CSL_MCSPI_IRQSTATUS_RX1_FULL_MASK;
    }
    else if ((uint32_t)MCSPI_CHANNEL_2 == csNum)
    {
        rxFullMask = (uint32_t)CSL_MCSPI_IRQSTATUS_RX2_FULL_MASK;
    }
    else
    {
        rxFullMask = (uint32_t)CSL_MCSPI_IRQSTATUS_RX3_FULL_MASK;
    }

    return (rxFullMask);
}

static inline void MCSPI_intrStatusClear(MCSPI_ChObject *chObj, uint32_t baseAddr, uint32_t intFlags)
{
    /* Clear the SSB bit in the MCSPI_SYST register. */
    CSL_REG32_WR(baseAddr + CSL_MCSPI_SYST, chObj->systRegVal);
    /* Clear the interrupt status. */
    CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQSTATUS, intFlags);
}

static void MCSPI_stop(MCSPI_Object *obj, const MCSPI_Attrs *attrs, MCSPI_ChObject *chObj, uint32_t chNum)
{
    uint32_t regVal, baseAddr;

    baseAddr = obj->baseAddr;
    if (MCSPI_OPER_MODE_INTERRUPT == attrs->operMode)
    {
        /* Disable channel interrupts. */
        regVal  = CSL_REG32_RD(baseAddr + CSL_MCSPI_IRQENABLE);
        regVal &= ~(chObj->intrMask);
        CSL_REG32_WR(baseAddr + CSL_MCSPI_IRQENABLE, regVal);
    }
    MCSPI_intrStatusClear(chObj, baseAddr, chObj->intrMask);

    if (MCSPI_MS_MODE_CONTROLLER == obj->openPrms.msMode)
    {
        /* Manual CS de-assert */
        if (MCSPI_CH_MODE_SINGLE == attrs->chMode)
        {
            if (chObj->csDisable == TRUE)
            {
                chObj->chConfRegVal &= (~CSL_MCSPI_CH0CONF_FORCE_MASK);
                CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chObj->chCfg.chNum), chObj->chConfRegVal);
                chObj->csEnable = TRUE;
            }
        }
    }

    /* Disable channel */
    chObj->chCtrlRegVal &= (~CSL_MCSPI_CH0CTRL_EN_MASK);
    CSL_REG32_WR(baseAddr + MCSPI_CHCTRL(chNum), chObj->chCtrlRegVal);

    /* Disable TX and RX FIFO This is required so that next CS can
     * use the FIFO */
    chObj->chConfRegVal &= ~(CSL_MCSPI_CH0CONF_FFEW_MASK | CSL_MCSPI_CH0CONF_FFER_MASK);
    CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chNum), chObj->chConfRegVal);
}

static void MCSPI_setChDataSize(uint32_t baseAddr, MCSPI_ChObject *chObj, uint32_t dataSize, uint32_t csDisable)
{
    uint32_t chNum;

    chNum = chObj->chCfg.chNum;
    CSL_FINS(chObj->chConfRegVal, MCSPI_CH0CONF_WL, (dataSize - 1U));
    CSL_REG32_WR(baseAddr + MCSPI_CHCONF(chNum), chObj->chConfRegVal);

    chObj->csDisable = csDisable;
    /* Calculate buffer access width */
    chObj->bufWidthShift = MCSPI_getBufWidthShift(dataSize);

    /* Calculate data width mask depending on SPI word size */
    chObj->dataWidthBitMask = MCSPI_getDataWidthBitMask(dataSize);

    chObj->effTxFifoDepth = chObj->chCfg.txFifoTrigLvl >> chObj->bufWidthShift;
    chObj->effRxFifoDepth = chObj->chCfg.rxFifoTrigLvl >> chObj->bufWidthShift;

    return;
}

void MCSPI_close(MCSPI_Handle handle)
{
    MCSPI_Config *config;
    // MCSPI_Object   *obj;
    uint32_t      baseAddr;

    if (NULL_CHECK != handle)
    {
        config = (MCSPI_Config *)handle;
        // obj = config->object;

        baseAddr = config->object->baseAddr;
        /* Reset MCSPI */
        MCSPI_reset(baseAddr);
        vimDisableInterrupt(79);
    }

    return;
}

/* ========================================================================== */
/*                       Advanced Function Definitions                        */
/* ========================================================================== */
uint32_t MCSPI_getBaseAddr(MCSPI_Handle handle)
{
    MCSPI_Config *config;
    MCSPI_Object *obj;
    uint32_t      baseAddr;

    /* Check parameters */
    if (NULL_CHECK == handle)
    {
        baseAddr = 0U;
    }
    else
    {
        config   = (MCSPI_Config *)handle;
        obj      = config->object;
        baseAddr = obj->baseAddr;
    }

    return baseAddr;
}

int32_t MCSPI_reConfigFifo(MCSPI_Handle handle, uint32_t chNum, uint32_t numWordsRxTx)
{
    uint32_t           baseAddr;
    MCSPI_Config      *config;
    MCSPI_Object      *obj;
    MCSPI_ChObject    *chObj;
    int32_t            status = Pmic_SystemP_SUCCESS;
    const MCSPI_Attrs *attrs;

    /* Check parameters */
    if ((NULL_CHECK == handle) || (chNum >= MCSPI_MAX_NUM_CHANNELS))
    {
        status = Pmic_SystemP_FAILURE;
    }

    if (Pmic_SystemP_SUCCESS == status)
    {
        config   = (MCSPI_Config *)handle;
        obj      = config->object;
        attrs    = config->attrs;
        baseAddr = config->object->baseAddr;
        chObj    = &obj->chObj[chNum];

        /* Re-Configure word count */
        if (MCSPI_OPER_MODE_DMA != attrs->operMode)
        {
            MCSPI_setFifoConfig(chObj, attrs, baseAddr, numWordsRxTx);
        }
    }

    return status;
}

/** \brief SPI MCSPI1 ISR */
__attribute__((target("arm"))) void Spi_IrqUnitMcspi1TxRx(void)
{
    MCSPI_controllerIsr();
}
