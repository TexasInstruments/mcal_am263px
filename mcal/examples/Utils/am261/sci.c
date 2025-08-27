/** @file sciBaseAddr.c
 *   @brief SCI Driver Implementation File
 *   @date 03.Apr.2014
 *   @version 01.00.00
 *
 */

/*
 * Copyright (C) 2023 Texas Instruments Incorporated - TI web adress www.ti.com
 *
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
 *
 */

#include "sci.h"
// #include "sys_vim.h"
#include "sys_common.h"
#include "hal_stdtypes.h"

g_sciTransfer_t g_sciTransfer[2U];

/** @fn void sciAInit(void)
 *   @brief Initializes the SCIA Driver
 *
 *   This function initializes the SCI module.
 */
/* SourceId :*/
/* DesignId :*/
/* Requirements :  */
void sciAInit(void)
{
    uint32 regWrFailStatus, regVal;
    /** @b initialize @b SCI */

    /** - bring SCI out of reset */
    regWrFailStatus  = regWriteReadback(&sciAREG->GCR0, M_THIRTY_ONE, M_ZERO, 0x0U);
    regWrFailStatus |= regWriteReadback(&sciAREG->GCR0, M_THIRTY_ONE, M_ZERO, 0x1U);

    regWrFailStatus = regWriteReadback(&sciAREG->GCR2, M_THIRTY_ONE, M_ZERO, 0x0U);
    // regWrFailStatus |= regWriteReadback(&sciAREG->GCR2, M_THIRTY_ONE, M_ZERO, 0x1U);

    /** - Disable all interrupts */
    sciAREG->CLEARINT    = 0xFFFFFFFFU;
    sciAREG->CLEARINTLVL = 0xFFFFFFFFU;

    /** - global control 1 */
    regVal = (uint32)((uint32)1U << 25U)         /* enable transmit */
             | (uint32)((uint32)1U << 24U)       /* enable receive */
             | (uint32)((uint32)0U << 6U)        /* internal clock (device has no clock pin) */
             | (uint32)((uint32)1U << 5U)        /* internal clock (device has no clock pin) */
             | (uint32)((uint32)(1U - 1U) << 4U) /* number of stop bits */
             | (uint32)((uint32)0U << 3U)        /* even parity, otherwise odd */
             | (uint32)((uint32)0U << 2U)        /* enable parity */
             | (uint32)((uint32)1U << 1U);       /* asynchronous timing mode */
    regWrFailStatus |= regWriteReadback(&sciAREG->GCR1, M_THIRTY_ONE, M_ZERO, regVal);

#ifdef BYPASS_APLL_CALIB
    /** - set baudrate */
    /* Prescalar val = (Clk in Hz)/(16 *(Intended Baud + 1)) */
    regWrFailStatus |= regWriteReadback(&sciAREG->BRS, M_THIRTY_ONE, M_ZERO, 0xAU);
#else
    /** - set baudrate */
    /* baudrate , 108 = (200 *10^6)/ 16 * (115200 + 1) */
    regWrFailStatus |= regWriteReadback(&sciAREG->BRS, M_THIRTY_ONE, M_ZERO, 0x19);
#endif
    /** - transmission length */
    regWrFailStatus |= regWriteReadback(&sciAREG->FORMAT, M_THIRTY_ONE, M_ZERO, (8U - 1U));

    /** - set SCI pins functional mode */
    regVal = (uint32)((uint32)1U << 2U)    /* tx pin */
             | (uint32)((uint32)1U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciAREG->PIO0, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins default output value */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciAREG->PIO3, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins output direction */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciAREG->PIO1, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins open drain enable */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciAREG->PIO6, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins pullup/pulldown enable */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciAREG->PIO7, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins pullup/pulldown select */
    regVal = (uint32)((uint32)1U << 2U)    /* tx pin */
             | (uint32)((uint32)1U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciAREG->PIO8, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set interrupt level */
    regVal = (uint32)((uint32)0U << 26U)   /* Framing error */
             | (uint32)((uint32)0U << 25U) /* Overrun error */
             | (uint32)((uint32)0U << 24U) /* Parity error */
             | (uint32)((uint32)0U << 9U)  /* Receive */
             | (uint32)((uint32)0U << 8U)  /* Transmit */
             | (uint32)((uint32)0U << 1U)  /* Wakeup */
             | (uint32)((uint32)0U << 0U); /* Break detect */
    regWrFailStatus |= regWriteReadback(&sciAREG->SETINTLVL, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set interrupt enable */
    regVal = (uint32)((uint32)1U << 26U)                 /* Framing error */
             | (uint32)((uint32)1U << 25U)               /* Overrun error */
             | (uint32)((uint32)1U << 24U)               /* Parity error */
             | (uint32)((uint32)0U << 9U) /* Receive */  // ToDo: Change to disable Interrupt.
             | (uint32)((uint32)1U << 1U)                /* Wakeup */
             | (uint32)((uint32)1U << 0U);               /* Break detect */
    regWrFailStatus |= regWriteReadback(&sciAREG->SETINT, M_THIRTY_ONE, M_ZERO, regVal);

    /** - initialize global transfer variables */
    g_sciTransfer[0U].mode      = (uint32)1U << 8U;
    g_sciTransfer[0U].tx_length = 0U;
    g_sciTransfer[0U].rx_length = 0U;

    /** - Finaly start SCI */
    sciAREG->GCR1 |= 0x80U;

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void sciBInit(void)
 *   @brief Initializes the SCIB Driver
 *
 *   This function initializes the SCI module.
 */
/* SourceId :*/
/* DesignId :  */
/* Requirements :  */
void sciBInit(void)
{
    uint32 regWrFailStatus, regVal;
    /** @b initialize @b SCI */

    /** - bring SCI out of reset */
    regWrFailStatus  = regWriteReadback(&sciBREG->GCR0, M_THIRTY_ONE, M_ZERO, 0x0U);
    regWrFailStatus |= regWriteReadback(&sciBREG->GCR0, M_THIRTY_ONE, M_ZERO, 0x1U);

    /** - Disable all interrupts */
    sciBREG->CLEARINT    = 0xFFFFFFFFU;
    sciBREG->CLEARINTLVL = 0xFFFFFFFFU;

    /** - global control 1 */
    regVal = (uint32)((uint32)1U << 25U)         /* enable transmit */
             | (uint32)((uint32)0U << 24U)       /* enable receive */
             | (uint32)((uint32)1U << 5U)        /* internal clock (device has no clock pin) */
             | (uint32)((uint32)(1U - 1U) << 4U) /* number of stop bits */
             | (uint32)((uint32)0U << 3U)        /* even parity, otherwise odd */
             | (uint32)((uint32)0U << 2U)        /* enable parity */
             | (uint32)((uint32)1U << 1U);       /* asynchronous timing mode */
    regWrFailStatus |= regWriteReadback(&sciBREG->GCR1, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set baudrate */
#ifdef BYPASS_APLL_CALIB
    /* Prescalar val = (Clk in Hz)/(16 *(Intended Baud + 1)) */
    regWrFailStatus |= regWriteReadback(&sciBREG->BRS, M_THIRTY_ONE, M_ZERO, 0xAU);
#else
    /* baudrate , 108 = (200 *10^6)/ 16 * (115200 + 1) */
    regWrFailStatus |= regWriteReadback(&sciBREG->BRS, M_THIRTY_ONE, M_ZERO, 0x6CU);
#endif

    /** - transmission length */
    regWrFailStatus |= regWriteReadback(&sciBREG->FORMAT, M_THIRTY_ONE, M_ZERO, (8U - 1U));

    /** - set SCI pins functional mode */
    regVal = (uint32)((uint32)1U << 2U)    /* tx pin */
             | (uint32)((uint32)1U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciBREG->PIO0, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins default output value */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciBREG->PIO3, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins output direction */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciBREG->PIO1, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins open drain enable */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciBREG->PIO6, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins pullup/pulldown enable */
    regVal = (uint32)((uint32)0U << 2U)    /* tx pin */
             | (uint32)((uint32)0U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciBREG->PIO7, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set SCI pins pullup/pulldown select */
    regVal = (uint32)((uint32)1U << 2U)    /* tx pin */
             | (uint32)((uint32)1U << 1U); /* rx pin */
    regWrFailStatus |= regWriteReadback(&sciBREG->PIO8, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set interrupt level */
    regVal = (uint32)((uint32)0U << 26U)   /* Framing error */
             | (uint32)((uint32)0U << 25U) /* Overrun error */
             | (uint32)((uint32)0U << 24U) /* Parity error */
             | (uint32)((uint32)0U << 9U)  /* Receive */
             | (uint32)((uint32)0U << 8U)  /* Transmit */
             | (uint32)((uint32)0U << 1U)  /* Wakeup */
             | (uint32)((uint32)0U << 0U); /* Break detect */
    regWrFailStatus |= regWriteReadback(&sciBREG->SETINTLVL, M_THIRTY_ONE, M_ZERO, regVal);

    /** - set interrupt enable */
    regVal = (uint32)((uint32)1U << 26U)   /* Framing error */
             | (uint32)((uint32)1U << 25U) /* Overrun error */
             | (uint32)((uint32)1U << 24U) /* Parity error */
             | (uint32)((uint32)1U << 9U)  /* Receive */
             | (uint32)((uint32)1U << 1U)  /* Wakeup */
             | (uint32)((uint32)1U << 0U); /* Break detect */
    regWrFailStatus |= regWriteReadback(&sciBREG->SETINT, M_THIRTY_ONE, M_ZERO, regVal);

    /** - initialize global transfer variables */
    g_sciTransfer[1U].mode      = (uint32)1U << 8U;
    g_sciTransfer[1U].tx_length = 0U;
    g_sciTransfer[1U].rx_length = 0U;

    /** - Finaly start SCI */
    sciBREG->GCR1 |= 0x80U;

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void sciSetFunctional(sciBASE_t *sciBaseAddr, uint32 port)
 *   @brief Change functional behavior of pins at runtime.
 *   @param[in] sciBaseAddr   - sciBaseAddr module base address
 *   @param[in] port  - Value to write to PIO0 register
 *
 *   Change the value of the PCPIO0 register at runtime, this allows to
 *   dynamically change the functionality of the SCI pins between functional
 *   and GIO mode.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciSetFunctional(sciBASE_t *sciBaseAddr, uint32 port)
{
    uint32 regWrFailStatus;

    regWrFailStatus = regWriteReadback(&sciBaseAddr->PIO0, M_THIRTY_ONE, M_ZERO, port);
    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void sciSetBaudrate(sciBASE_t *sciBaseAddr, uint32 baud)
 *   @brief Change baudrate at runtime.
 *   @param[in] sciBaseAddr  - sciBaseAddr module base address
 *   @param[in] baud - baudrate in Hz
 *
 *   Change the SCI baudrate at runtime.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciSetBaudrate(sciBASE_t *sciBaseAddr, uint32 baud)
{
    uint32  regWrFailStatus;
    float64 vclk = 200.000 * 1000000.0;
    uint32  gcr1 = sciBaseAddr->GCR1;
    uint32  f    = ((gcr1 & 2U) == 2U) ? 16U : 1U;
    uint32  temp;
    float64 temp2;

    /*AR_CODE_REVIEW MR:R.6.1 Reason : "Calculations including int and float cannot be avoided" */
    /*LDRA_INSPECTED 96 S */
    temp  = (f * (baud + 1U));
    temp2 = ((vclk) / ((float64)temp));

    regWrFailStatus =
        regWriteReadback(&sciBaseAddr->BRS, M_TWENTY_THREE, M_ZERO, (uint32)((uint32)temp2 & 0x00FFFFFFU));
    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void sciSetBaudrateValue(sciBASE_t *sciBaseAddr, uint32 baud)
 *   @brief Change baudrate at runtime.
 *   @param[in] sciBaseAddr  - sciBaseAddr module base address
 *   @param[in] baud - baudrate in Hz
 *
 *   Change the SCI baudrate at runtime.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciSetBaudrateValue(sciBASE_t *sciBaseAddr, uint32 baud)
{
    uint32 regWrFailStatus;

    regWrFailStatus = regWriteReadback(&sciBaseAddr->BRS, M_TWENTY_THREE, M_ZERO, (uint32)((uint32)baud & 0x00FFFFFFU));
    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn uint32 sciIsTxReady(sciBASE_t *sciBaseAddr)
 *   @brief Check if Tx buffer empty
 *   @param[in] sciBaseAddr - sciBaseAddr module base address
 *
 *   @return The TX ready flag
 *
 *   Checks to see if the Tx buffer ready flag is set, returns
 *   0 is flags not set otherwise will return the Tx flag itself.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 sciIsTxReady(sciBASE_t *sciBaseAddr)
{
    uint32 flr = sciBaseAddr->FLR;
    return (flr & (uint32)SCI_TX_INT);
}

/** @fn void sciSendByte(sciBASE_t *sciBaseAddr, uint8 byte)
 *   @brief Send Byte
 *   @param[in] sciBaseAddr  - sciBaseAddr module base address
 *   @param[in] byte - byte to transfer
 *
 *   Sends a single byte in polling mode, will wait in the
 *   routine until the transmit buffer is empty before sending
 *   the byte.  Use sciIsTxReady to check for Tx buffer empty
 *   before calling sciSendByte to avoid waiting.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciSendByte(sciBASE_t *sciBaseAddr, uint8 byte)
{
    uint32 flr;
    /*AR_CODE_REVIEW MR:NA Reason : "Potentially infinite loop found -
     * Hardware Status check for execution sequence" */
    /*LDRA_INSPECTED 28 D */
    do
    {
        flr = sciBaseAddr->FLR;
    } while ((flr & (uint32)SCI_TX_INT) == 0U); /* Wait */

    sciBaseAddr->TD = byte;
}

/** @fn void sciSend(sciBASE_t *sciBaseAddr, uint32 length, uint8 * data)
 *   @brief Send Data
 *   @param[in] sciBaseAddr    - sciBaseAddr module base address
 *   @param[in] length - number of data words to transfer
 *   @param[in] data   - pointer to data to send
 *
 *   Send a block of data pointed to by 'data' and 'length' bytes
 *   long.  If interrupts have been enabled the data is sent using
 *   interrupt mode, otherwise polling mode is used.  In interrupt
 *   mode transmission of the first byte is started and the routine
 *   returns immediately, sciSend must not be called again until the
 *   transfer is complete, when the sciNotification callback will
 *   be called.  In polling mode, sciSend will not return  until
 *   the transfer is complete.
 *
 *   @note if data word is less than 8 bits, then the data must be left
 *         aligned in the data byte.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciSend(sciBASE_t *sciBaseAddr, uint32 length, uint8 *data)
{
    uint32 index = (sciBaseAddr == sciAREG) ? 0U : 1U;
    uint8  txdata;
    uint32 flr;

    /*AR_CODE_REVIEW MR:R.13.7 Reason : "Mode variable is configured in sciEnableNotification()" */
    /*LDRA_INSPECTED 139 S */
    if ((g_sciTransfer[index].mode & (uint32)SCI_TX_INT) != 0U)
    {
        /* we are in interrupt mode */

        g_sciTransfer[index].tx_length = length;
        /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
         * allowed in this driver" */
        /*LDRA_INSPECTED 45 D */
        g_sciTransfer[index].tx_data = data;

        /* start transmit by sending first byte */
        /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
         * allowed in this driver" */
        /*LDRA_INSPECTED 45 D */
        txdata          = *g_sciTransfer[index].tx_data;
        sciBaseAddr->TD = (uint32)(txdata);
        /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
         * allowed in this driver" */
        /*LDRA_INSPECTED 45 D */
        /*AR_CODE_REVIEW MR:R.17.1,17.4 Reason : "Pointer increment needed" */
        /*LDRA_INSPECTED 567 S */
        g_sciTransfer[index].tx_data++;
        sciBaseAddr->SETINT = (uint32)SCI_TX_INT;
    }
    else
    {
        /* send the data */
        while (length > 0U)
        {
            /*AR_CODE_REVIEW MR:NA Reason : "Potentially infinite loop found -
             * Hardware Status check for execution sequence" */
            /*LDRA_INSPECTED 28 D */
            do
            {
                flr = sciBaseAddr->FLR;
            } while ((flr & (uint32)SCI_TX_INT) == 0U); /* Wait */

            /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
             * allowed in this driver" */
            /*LDRA_INSPECTED 45 D */
            txdata          = *data;
            sciBaseAddr->TD = (uint32)(txdata);
            /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
             * allowed in this driver" */
            /*LDRA_INSPECTED 45 D */
            /*AR_CODE_REVIEW MR:R.17.1,17.4 Reason : "Pointer increment needed" */
            /*LDRA_INSPECTED 567 S */
            data++;
            length--;
        }
    }
}

/** @fn uint32 sciIsRxReady(sciBASE_t *sciBaseAddr)
 *   @brief Check if Rx buffer full
 *   @param[in] sciBaseAddr - sciBaseAddr module base address
 *
 *   @return The Rx ready flag
 *
 *   Checks to see if the Rx buffer full flag is set, returns
 *   0 is flags not set otherwise will return the Rx flag itself.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 sciIsRxReady(sciBASE_t *sciBaseAddr)
{
    uint32 flr = sciBaseAddr->FLR;
    return (flr & (uint32)SCI_RX_INT);
}

/** @fn uint32 sciIsIdleDetected(sciBASE_t *sciBaseAddr)
 *   @brief Check if Idle Period is Detected
 *   @param[in] sciBaseAddr - sciBaseAddr module base address
 *
 *   @return The Idle flag
 *
 *   Checks to see if the SCI Idle flag is set, returns 0 if idle
 *   period has been detected and SCI is ready to receive, otherwise returns the Idle flag itself.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 sciIsIdleDetected(sciBASE_t *sciBaseAddr)
{
    uint32 flr = sciBaseAddr->FLR;
    return (flr & (uint32)SCI_IDLE);
}

/** @fn uint32 sciRxError(sciBASE_t *sciBaseAddr)
 *   @brief Return Rx Error flags
 *   @param[in] sciBaseAddr - sciBaseAddr module base address
 *
 *   @return The Rx error flags
 *
 *   Returns the Rx framing, overrun and parity errors flags,
 *   also clears the error flags before returning.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 sciRxError(sciBASE_t *sciBaseAddr)
{
    uint32 sci_fe_int = (uint32)SCI_FE_INT;
    uint32 sci_oe_int = (uint32)SCI_OE_INT;
    uint32 sci_pe_int = (uint32)SCI_PE_INT;
    uint32 flr        = sciBaseAddr->FLR;

    uint32 status = (flr & (sci_fe_int | sci_oe_int | sci_pe_int));

    sciBaseAddr->FLR = (sci_fe_int | sci_oe_int | sci_pe_int);
    return status;
}

/** @fn uint32 sciReceiveByte(sciBASE_t *sciBaseAddr)
 *   @brief Receive Byte
 *   @param[in] sciBaseAddr - sciBaseAddr module base address
 *
 *   @return Received byte
 *
 *    Receives a single byte in polling mode.  If there is
 *    not a byte in the receive buffer the routine will wait
 *    until one is received.   Use sciIsRxReady to check to
 *    see if the buffer is full to avoid waiting.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 sciReceiveByte(sciBASE_t *sciBaseAddr)
{
    uint32 rd;
    uint32 flr;
    /*AR_CODE_REVIEW MR:NA Reason : "Potentially infinite loop found -
     * Hardware Status check for execution sequence" */
    /*LDRA_INSPECTED 28 D */
    do
    {
        flr = sciBaseAddr->FLR;
    } while ((flr & (uint32)SCI_RX_INT) == 0U); /* Wait */

    rd = sciBaseAddr->RD;
    return (rd & (uint32)0x000000FFU);
}

/** @fn void sciReceive(sciBASE_t *sciBaseAddr, uint32 length, uint8 * data)
 *   @brief Receive Data
 *   @param[in] sciBaseAddr    - sciBaseAddr module base address
 *   @param[in] length - number of data words to transfer
 *   @param[in] data   - pointer to data buffer to receive data
 *
 *   Receive a block of 'length' bytes long and place it into the
 *   data buffer pointed to by 'data'.  If interrupts have been
 *   enabled the data is received using interrupt mode, otherwise
 *   polling mode is used.  In interrupt mode receive is setup and
 *   the routine returns immediately, sciReceive must not be called
 *   again until the transfer is complete, when the sciNotification
 *   callback will be called.  In polling mode, sciReceive will not
 *   return  until the transfer is complete.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciReceive(sciBASE_t *sciBaseAddr, uint32 length, uint8 *data)
{
    uint32 setint = sciBaseAddr->SETINT;
    uint32 rd;
    uint32 flr;

    if ((setint & (uint32)SCI_RX_INT) == (uint32)SCI_RX_INT)
    {
        /* we are in interrupt mode */
        uint32 index = (sciBaseAddr == sciAREG) ? 0U : 1U;

        /* clear error flags */
        sciBaseAddr->FLR = ((uint32)SCI_FE_INT | (uint32)SCI_OE_INT | (uint32)SCI_PE_INT);

        g_sciTransfer[index].rx_length = length;
        /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
         * allowed in this driver" */
        /*LDRA_INSPECTED 45 D */
        g_sciTransfer[index].rx_data = data;
        rd                           = 0U;
    }
    else
    {
        while (length > 0U)
        {
            /*AR_CODE_REVIEW MR:NA Reason : "Potentially infinite loop found -
             * Hardware Status check for execution sequence" */
            /*LDRA_INSPECTED 28 D */
            do
            {
                flr = sciBaseAddr->FLR;
            } while ((flr & (uint32)SCI_RX_INT) == 0U); /* Wait */
            rd = sciBaseAddr->RD;
            /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
             * allowed in this driver" */
            /*LDRA_INSPECTED 45 D */
            *data = (uint8)(rd & 0x000000FFU);
            /*AR_CODE_REVIEW MR:R.21.1 Reason : "Valid non NULL input parameters are only
             * allowed in this driver" */
            /*LDRA_INSPECTED 45 D */
            /*AR_CODE_REVIEW MR:R.17.1,17.4 Reason : "Pointer increment needed" */
            /*LDRA_INSPECTED 567 S */
            data++;
            length--;
        }
    }
}

/** @fn void sciEnableLoopback(sciBASE_t *sciBaseAddr, loopBackType_t Loopbacktype)
 *   @brief Enable Loopback mode for self test
 *   @param[in] sciBaseAddr        - sciBaseAddr module base address
 *   @param[in] Loopbacktype  - Digital or Analog
 *
 *   This function enables the Loopback mode for self test.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciEnableLoopback(sciBASE_t *sciBaseAddr, loopBackType_t Loopbacktype)
{
    uint32 regWrFailStatus, regVal;
    /* Clear Loopback incase enabled already */
    regWrFailStatus = regWriteReadback(&sciBaseAddr->IODFTCTRL, M_THIRTY_ONE, M_ZERO, 0U);

    /* Enable Loopback either in Analog or Digital Mode */
    regVal           = (uint32)0x00000A00U | (uint32)((uint32)Loopbacktype << 1U);
    regWrFailStatus |= regWriteReadback(&sciBaseAddr->IODFTCTRL, M_THIRTY_ONE, M_ZERO, regVal);

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void sciDisableLoopback(sciBASE_t *sciBaseAddr)
 *   @brief Enable Loopback mode for self test
 *   @param[in] sciBaseAddr        - sciBaseAddr module base address
 *
 *   This function disable the Loopback mode.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciDisableLoopback(sciBASE_t *sciBaseAddr)
{
    uint32 regWrFailStatus;
    /* Disable Loopback Mode */
    regWrFailStatus = regWriteReadback(&sciBaseAddr->IODFTCTRL, M_THIRTY_ONE, M_ZERO, 0x00000500U);

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn sciEnableNotification(sciBASE_t *sciBaseAddr, uint32 flags)
 *   @brief Enable interrupts
 *   @param[in] sciBaseAddr   - sciBaseAddr module base address
 *   @param[in] flags - Interrupts to be enabled, can be ored value of:
 *                      SCI_FE_INT    - framing error,
 *                      SCI_OE_INT    - overrun error,
 *                      SCI_PE_INT    - parity error,
 *                      SCI_RX_INT    - receive buffer ready,
 *                      SCI_TX_INT    - transmit buffer ready,
 *                      SCI_WAKE_INT  - wakeup,
 *                      SCI_BREAK_INT - break detect
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciEnableNotification(sciBASE_t *sciBaseAddr, uint32 flags)
{
    uint32 index = (sciBaseAddr == sciAREG) ? 0U : 1U;

    g_sciTransfer[index].mode |= (flags & (uint32)SCI_TX_INT);
    sciBaseAddr->SETINT        = (flags & (uint32)(~(uint32)(SCI_TX_INT)));
}

/** @fn sciDisableNotification(sciBASE_t *sciBaseAddr, uint32 flags)
 *   @brief Disable interrupts
 *   @param[in] sciBaseAddr   - sciBaseAddr module base address
 *   @param[in] flags - Interrupts to be disabled, can be ored value of:
 *                      SCI_FE_INT    - framing error,
 *                      SCI_OE_INT    - overrun error,
 *                      SCI_PE_INT    - parity error,
 *                      SCI_RX_INT    - receive buffer ready,
 *                      SCI_TX_INT    - transmit buffer ready,
 *                      SCI_WAKE_INT  - wakeup,
 *                      SCI_BREAK_INT - break detect
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciDisableNotification(sciBASE_t *sciBaseAddr, uint32 flags)
{
    uint32 index = (sciBaseAddr == sciAREG) ? 0U : 1U;

    g_sciTransfer[index].mode &= (uint32)(~(flags & (uint32)SCI_TX_INT));
    sciBaseAddr->CLEARINT      = (flags & (uint32)(~(uint32)(SCI_TX_INT)));
}

/** @fn void sciGetConfigValue(sci_config_reg_t *config_reg, config_value_type_t type)
 *   @brief Get the initial or current values of the SCI configuration registers
 *
 *   @param[in] *config_reg: pointer to the struct to which the initial or current
 *                           value of the configuration registers need to be stored
 *   @param[in] type:    whether initial or current value of the configuration registers need to be
 * stored
 *                       - InitialValue: initial value of the configuration registers will be stored
 *                                       in the struct pointed by config_reg
 *                       - CurrentValue: initial value of the configuration registers will be stored
 *                                       in the struct pointed by config_reg
 *
 *   This function will copy the initial or current value (depending on the parameter 'type')
 *   of the configuration registers to the struct pointed by config_reg
 *
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void sciGetConfigValue(sciBASE_t *sciBaseAddr, sci_config_reg_t *config_reg, config_value_type_t type)
{
    // TODO make different MACRO for SCI-A/B
    if ((sciBaseAddr == sciAREG) && (type == InitialValue))
    {
        config_reg->CONFIG_GCR0      = SCI_GCR0_CONFIGVALUE;
        config_reg->CONFIG_GCR1      = SCI_GCR1_CONFIGVALUE;
        config_reg->CONFIG_SETINT    = SCI_SETINT_CONFIGVALUE;
        config_reg->CONFIG_SETINTLVL = SCI_SETINTLVL_CONFIGVALUE;
        config_reg->CONFIG_FORMAT    = SCI_FORMAT_CONFIGVALUE;
        config_reg->CONFIG_BRS       = (uint32)SCI_BRS_CONFIGVALUE;
        config_reg->CONFIG_PIO0      = SCI_PIO0_CONFIGVALUE;
        config_reg->CONFIG_PIO1      = SCI_PIO1_CONFIGVALUE;
        config_reg->CONFIG_PIO6      = SCI_PIO6_CONFIGVALUE;
        config_reg->CONFIG_PIO7      = SCI_PIO7_CONFIGVALUE;
        config_reg->CONFIG_PIO8      = SCI_PIO8_CONFIGVALUE;
    }
    else if ((sciBaseAddr == sciBREG) && (type == InitialValue))
    {
        config_reg->CONFIG_GCR0      = SCI_GCR0_CONFIGVALUE;
        config_reg->CONFIG_GCR1      = SCI_GCR1_CONFIGVALUE;
        config_reg->CONFIG_SETINT    = SCI_SETINT_CONFIGVALUE;
        config_reg->CONFIG_SETINTLVL = SCI_SETINTLVL_CONFIGVALUE;
        config_reg->CONFIG_FORMAT    = SCI_FORMAT_CONFIGVALUE;
        config_reg->CONFIG_BRS       = (uint32)SCI_BRS_CONFIGVALUE;
        config_reg->CONFIG_PIO0      = SCI_PIO0_CONFIGVALUE;
        config_reg->CONFIG_PIO1      = SCI_PIO1_CONFIGVALUE;
        config_reg->CONFIG_PIO6      = SCI_PIO6_CONFIGVALUE;
        config_reg->CONFIG_PIO7      = SCI_PIO7_CONFIGVALUE;
        config_reg->CONFIG_PIO8      = SCI_PIO8_CONFIGVALUE;
    }
    else
    {
        /*AR_CODE_REVIEW MR:R.12.2 Reason : "LDRA Tool issue" */
        /*LDRA_INSPECTED 134 S */
        config_reg->CONFIG_GCR0      = sciBaseAddr->GCR0;
        config_reg->CONFIG_GCR1      = sciBaseAddr->GCR1;
        config_reg->CONFIG_SETINT    = sciBaseAddr->SETINT;
        config_reg->CONFIG_SETINTLVL = sciBaseAddr->SETINTLVL;
        config_reg->CONFIG_FORMAT    = sciBaseAddr->FORMAT;
        config_reg->CONFIG_BRS       = sciBaseAddr->BRS;
        config_reg->CONFIG_PIO0      = sciBaseAddr->PIO0;
        config_reg->CONFIG_PIO1      = sciBaseAddr->PIO1;
        config_reg->CONFIG_PIO6      = sciBaseAddr->PIO6;
        config_reg->CONFIG_PIO7      = sciBaseAddr->PIO7;
        config_reg->CONFIG_PIO8      = sciBaseAddr->PIO8;
    }
}
