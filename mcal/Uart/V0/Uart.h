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

#ifndef UART_V0_LLD_H_
#define UART_V0_LLD_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************************************
 * Register Definitions
 ****************************************************************************************************/
#define UART_RHR              ((uint32)0x0U)
#define UART_THR              ((uint32)0x0U)
#define UART_IER              ((uint32)0x4U)
#define UART_IIR              ((uint32)0x8U)
#define UART_FCR              ((uint32)0x8U)
#define UART_LCR              ((uint32)0xcU)
#define UART_MCR              ((uint32)0x10U)
#define UART_LSR              ((uint32)0x14U)
#define UART_MSR              ((uint32)0x18U)
#define UART_SPR              ((uint32)0x1cU)
#define UART_MDR1             ((uint32)0x20U)
#define UART_MDR2             ((uint32)0x24U)
#define UART_SFLSR            ((uint32)0x28U)
#define UART_TXFLL            ((uint32)0x28U)
#define UART_RESUME           ((uint32)0x2cU)
#define UART_TXFLH            ((uint32)0x2cU)
#define UART_SFREGL           ((uint32)0x30U)
#define UART_RXFLL            ((uint32)0x30U)
#define UART_SFREGH           ((uint32)0x34U)
#define UART_RXFLH            ((uint32)0x34U)
#define UART_BLR              ((uint32)0x38U)
#define UART_ACREG            ((uint32)0x3cU)
#define UART_SCR              ((uint32)0x40U)
#define UART_SSR              ((uint32)0x44U)
#define UART_EBLR             ((uint32)0x48U)
#define UART_MVR              ((uint32)0x50U)
#define UART_SYSC             ((uint32)0x54U)
#define UART_SYSS             ((uint32)0x58U)
#define UART_WER              ((uint32)0x5cU)
#define UART_CFPS             ((uint32)0x60U)
#define UART_RXFIFO_LVL       ((uint32)0x64U)
#define UART_TXFIFO_LVL       ((uint32)0x68U)
#define UART_IER2             ((uint32)0x6cU)
#define UART_ISR2             ((uint32)0x70U)
#define UART_FREQ_SEL         ((uint32)0x74U)
#define UART_ABAUD_1ST_CHAR   ((uint32)0x78U)
#define UART_BAUD_2ND_CHAR    ((uint32)0x7cU)
#define UART_MDR3             ((uint32)0x80U)
#define UART_TX_DMA_THRESHOLD ((uint32)0x84U)
#define UART_DLL              ((uint32)0x0U)
#define UART_IER_IRDA         ((uint32)0x4U)
#define UART_IER_CIR          ((uint32)0x4U)
#define UART_DLH              ((uint32)0x4U)
#define UART_IIR_IRDA         ((uint32)0x8U)
#define UART_IIR_CIR          ((uint32)0x8U)
#define UART_EFR              ((uint32)0x8U)
#define UART_XON1_ADDR1       ((uint32)0x10U)
#define UART_LSR_IRDA         ((uint32)0x14U)
#define UART_LSR_CIR          ((uint32)0x14U)
#define UART_XON2_ADDR2       ((uint32)0x14U)
#define UART_XOFF1            ((uint32)0x18U)
#define UART_TCR              ((uint32)0x18U)
#define UART_XOFF2            ((uint32)0x1cU)
#define UART_TLR              ((uint32)0x1cU)
#define UART_UASR             ((uint32)0x38U)

/* ========================================================================== */
/*                             Field Definition Macros                        */
/* ========================================================================== */

#define UART_RHR_RHR_SHIFT ((uint32)0U)
#define UART_RHR_RHR_MASK  ((uint32)0x000000ffU)

#define UART_RHR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_RHR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_THR_THR_SHIFT ((uint32)0U)
#define UART_THR_THR_MASK  ((uint32)0x000000ffU)

#define UART_THR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_THR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_IER_RHR_IT_SHIFT          ((uint32)0U)
#define UART_IER_RHR_IT_MASK           ((uint32)0x00000001U)
#define UART_IER_RHR_IT_RHR_IT_VALUE_1 ((uint32)1U)
#define UART_IER_RHR_IT_RHR_IT_VALUE_0 ((uint32)0U)

#define UART_IER_THR_IT_SHIFT          ((uint32)1U)
#define UART_IER_THR_IT_MASK           ((uint32)0x00000002U)
#define UART_IER_THR_IT_THR_IT_VALUE_1 ((uint32)1U)
#define UART_IER_THR_IT_THR_IT_VALUE_0 ((uint32)0U)

#define UART_IER_LINE_STS_IT_SHIFT                 ((uint32)2U)
#define UART_IER_LINE_STS_IT_MASK                  ((uint32)0x00000004U)
#define UART_IER_LINE_STS_IT_LINE_STS_IT_U_VALUE_1 ((uint32)1U)
#define UART_IER_LINE_STS_IT_LINE_STS_IT_U_VALUE_0 ((uint32)0U)

#define UART_IER_MODEM_STS_IT_SHIFT                ((uint32)3U)
#define UART_IER_MODEM_STS_IT_MASK                 ((uint32)0x00000008U)
#define UART_IER_MODEM_STS_IT_MODEM_STS_IT_VALUE_1 ((uint32)1U)
#define UART_IER_MODEM_STS_IT_MODEM_STS_IT_VALUE_0 ((uint32)0U)

#define UART_IER_SLEEP_MODE_SHIFT              ((uint32)4U)
#define UART_IER_SLEEP_MODE_MASK               ((uint32)0x00000010U)
#define UART_IER_SLEEP_MODE_SLEEP_MODE_VALUE_1 ((uint32)1U)
#define UART_IER_SLEEP_MODE_SLEEP_MODE_VALUE_0 ((uint32)0U)

#define UART_IER_XOFF_IT_SHIFT           ((uint32)5U)
#define UART_IER_XOFF_IT_MASK            ((uint32)0x00000020U)
#define UART_IER_XOFF_IT_XOFF_IT_VALUE_1 ((uint32)1U)
#define UART_IER_XOFF_IT_XOFF_IT_VALUE_0 ((uint32)0U)

#define UART_IER_RTS_IT_SHIFT          ((uint32)6U)
#define UART_IER_RTS_IT_MASK           ((uint32)0x00000040U)
#define UART_IER_RTS_IT_RTS_IT_VALUE_1 ((uint32)1U)
#define UART_IER_RTS_IT_RTS_IT_VALUE_0 ((uint32)0U)

#define UART_IER_CTS_IT_SHIFT          ((uint32)7U)
#define UART_IER_CTS_IT_MASK           ((uint32)0x00000080U)
#define UART_IER_CTS_IT_CTS_IT_VALUE_1 ((uint32)1U)
#define UART_IER_CTS_IT_CTS_IT_VALUE_0 ((uint32)0U)

#define UART_IER_RESERVED_SHIFT ((uint32)8U)
#define UART_IER_RESERVED_MASK  ((uint32)0xffffff00U)

#define UART_IIR_IT_PENDING_SHIFT              ((uint32)0U)
#define UART_IIR_IT_PENDING_MASK               ((uint32)0x00000001U)
#define UART_IIR_IT_PENDING_IT_PENDING_VALUE_0 ((uint32)0U)
#define UART_IIR_IT_PENDING_IT_PENDING_VALUE_1 ((uint32)1U)

#define UART_IIR_IT_TYPE_SHIFT            ((uint32)1U)
#define UART_IIR_IT_TYPE_MASK             ((uint32)0x0000003eU)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_8  ((uint32)8U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_6  ((uint32)6U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_3  ((uint32)3U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_10 ((uint32)16U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_2  ((uint32)2U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_1  ((uint32)1U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_0  ((uint32)0U)

#define UART_IIR_FCR_MIRROR_SHIFT ((uint32)6U)
#define UART_IIR_FCR_MIRROR_MASK  ((uint32)0x000000c0U)

#define UART_IIR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_IIR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_FCR_FIFO_EN_SHIFT           ((uint32)0U)
#define UART_FCR_FIFO_EN_MASK            ((uint32)0x00000001U)
#define UART_FCR_FIFO_EN_FIFO_EN_VALUE_1 ((uint32)1U)
#define UART_FCR_FIFO_EN_FIFO_EN_VALUE_0 ((uint32)0U)

#define UART_FCR_RX_FIFO_CLEAR_SHIFT                 ((uint32)1U)
#define UART_FCR_RX_FIFO_CLEAR_MASK                  ((uint32)0x00000002U)
#define UART_FCR_RX_FIFO_CLEAR_RX_FIFO_CLEAR_VALUE_1 ((uint32)1U)
#define UART_FCR_RX_FIFO_CLEAR_RX_FIFO_CLEAR_VALUE_0 ((uint32)0U)

#define UART_FCR_TX_FIFO_CLEAR_SHIFT                 ((uint32)2U)
#define UART_FCR_TX_FIFO_CLEAR_MASK                  ((uint32)0x00000004U)
#define UART_FCR_TX_FIFO_CLEAR_TX_FIFO_CLEAR_VALUE_1 ((uint32)1U)
#define UART_FCR_TX_FIFO_CLEAR_TX_FIFO_CLEAR_VALUE_0 ((uint32)0U)

#define UART_FCR_DMA_MODE_SHIFT            ((uint32)3U)
#define UART_FCR_DMA_MODE_MASK             ((uint32)0x00000008U)
#define UART_FCR_DMA_MODE_DMA_MODE_VALUE_1 ((uint32)1U)
#define UART_FCR_DMA_MODE_DMA_MODE_VALUE_0 ((uint32)0U)

#define UART_FCR_TX_FIFO_TRIG_SHIFT ((uint32)4U)
#define UART_FCR_TX_FIFO_TRIG_MASK  ((uint32)0x00000030U)

#define UART_FCR_RX_FIFO_TRIG_SHIFT ((uint32)6U)
#define UART_FCR_RX_FIFO_TRIG_MASK  ((uint32)0x000000c0U)

#define UART_FCR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_FCR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_LCR_CHAR_LENGTH_SHIFT               ((uint32)0U)
#define UART_LCR_CHAR_LENGTH_MASK                ((uint32)0x00000003U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_3 (uint32)((uint32)3U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_2 (uint32)((uint32)2U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_1 (uint32)((uint32)1U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_0 (uint32)((uint32)0U)

#define UART_LCR_NB_STOP_SHIFT           ((uint32)2U)
#define UART_LCR_NB_STOP_MASK            ((uint32)0x00000004U)
#define UART_LCR_NB_STOP_NB_STOP_VALUE_1 (uint32)((uint32)1U)
#define UART_LCR_NB_STOP_NB_STOP_VALUE_0 (uint32)((uint32)0U)

#define UART_LCR_PARITY_EN_SHIFT             ((uint32)3U)
#define UART_LCR_PARITY_EN_MASK              ((uint32)0x00000008U)
#define UART_LCR_PARITY_EN_PARITY_EN_VALUE_1 (uint32)((uint32)1U)
#define UART_LCR_PARITY_EN_PARITY_EN_VALUE_0 (uint32)((uint32)0U)

#define UART_LCR_PARITY_TYPE1_SHIFT                ((uint32)4U)
#define UART_LCR_PARITY_TYPE1_MASK                 ((uint32)0x00000010U)
#define UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_1 ((uint32)1U)
#define UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_0 ((uint32)0U)

#define UART_LCR_PARITY_TYPE2_SHIFT ((uint32)5U)
#define UART_LCR_PARITY_TYPE2_MASK  ((uint32)0x00000020U)

#define UART_LCR_BREAK_EN_SHIFT            ((uint32)6U)
#define UART_LCR_BREAK_EN_MASK             ((uint32)0x00000040U)
#define UART_LCR_BREAK_EN_BREAK_EN_VALUE_1 (uint32)((uint32)1U)
#define UART_LCR_BREAK_EN_BREAK_EN_VALUE_0 (uint32)((uint32)0U)

#define UART_LCR_DIV_EN_SHIFT          ((uint32)7U)
#define UART_LCR_DIV_EN_MASK           ((uint32)0x00000080U)
#define UART_LCR_DIV_EN_DIV_EN_VALUE_0 ((uint32)0U)
#define UART_LCR_DIV_EN_DIV_EN_VALUE_1 ((uint32)1U)

#define UART_LCR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_LCR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_MCR_LOOPBACK_EN_SHIFT               ((uint32)4U)
#define UART_MCR_LOOPBACK_EN_MASK                ((uint32)0x00000010U)
#define UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_1 ((uint32)1U)
#define UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_0 ((uint32)0U)

#define UART_MCR_XON_EN_SHIFT          ((uint32)5U)
#define UART_MCR_XON_EN_MASK           ((uint32)0x00000020U)
#define UART_MCR_XON_EN_XON_EN_VALUE_1 ((uint32)1U)
#define UART_MCR_XON_EN_XON_EN_VALUE_0 ((uint32)0U)

#define UART_MCR_TCR_TLR_SHIFT           ((uint32)6U)
#define UART_MCR_TCR_TLR_MASK            ((uint32)0x00000040U)
#define UART_MCR_TCR_TLR_TCR_TLR_VALUE_1 ((uint32)1U)
#define UART_MCR_TCR_TLR_TCR_TLR_VALUE_0 ((uint32)0U)

#define UART_MCR_RESERVED_SHIFT ((uint32)7U)
#define UART_MCR_RESERVED_MASK  ((uint32)0x00000080U)

#define UART_MCR_DTR_SHIFT       ((uint32)0U)
#define UART_MCR_DTR_MASK        ((uint32)0x00000001U)
#define UART_MCR_DTR_DTR_VALUE_1 ((uint32)1U)
#define UART_MCR_DTR_DTR_VALUE_0 ((uint32)0U)

#define UART_MCR_RTS_SHIFT       ((uint32)1U)
#define UART_MCR_RTS_MASK        ((uint32)0x00000002U)
#define UART_MCR_RTS_RTS_VALUE_1 ((uint32)1U)
#define UART_MCR_RTS_RTS_VALUE_0 ((uint32)0U)

#define UART_MCR_RI_STS_CH_SHIFT             ((uint32)2U)
#define UART_MCR_RI_STS_CH_MASK              ((uint32)0x00000004U)
#define UART_MCR_RI_STS_CH_RI_STS_CH_VALUE_1 ((uint32)1U)
#define UART_MCR_RI_STS_CH_RI_STS_CH_VALUE_0 ((uint32)0U)

#define UART_MCR_CD_STS_CH_SHIFT             ((uint32)3U)
#define UART_MCR_CD_STS_CH_MASK              ((uint32)0x00000008U)
#define UART_MCR_CD_STS_CH_CD_STS_CH_VALUE_1 ((uint32)1U)
#define UART_MCR_CD_STS_CH_CD_STS_CH_VALUE_0 ((uint32)0U)

#define UART_MCR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_MCR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_LSR_RX_FIFO_E_SHIFT             ((uint32)0U)
#define UART_LSR_RX_FIFO_E_MASK              ((uint32)0x00000001U)
#define UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_1 ((uint32)1U)
#define UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0 ((uint32)0U)

#define UART_LSR_RX_OE_SHIFT         ((uint32)1U)
#define UART_LSR_RX_OE_MASK          ((uint32)0x00000002U)
#define UART_LSR_RX_OE_RX_OE_VALUE_1 ((uint32)1U)
#define UART_LSR_RX_OE_RX_OE_VALUE_0 ((uint32)0U)

#define UART_LSR_RX_PE_SHIFT         ((uint32)2U)
#define UART_LSR_RX_PE_MASK          ((uint32)0x00000004U)
#define UART_LSR_RX_PE_RX_PE_VALUE_1 ((uint32)1U)
#define UART_LSR_RX_PE_RX_PE_VALUE_0 ((uint32)0U)

#define UART_LSR_RX_FE_SHIFT         ((uint32)3U)
#define UART_LSR_RX_FE_MASK          ((uint32)0x00000008U)
#define UART_LSR_RX_FE_RX_FE_VALUE_1 ((uint32)1U)
#define UART_LSR_RX_FE_RX_FE_VALUE_0 ((uint32)0U)

#define UART_LSR_RX_BI_SHIFT         ((uint32)4U)
#define UART_LSR_RX_BI_MASK          ((uint32)0x00000010U)
#define UART_LSR_RX_BI_RX_BI_VALUE_1 ((uint32)1U)
#define UART_LSR_RX_BI_RX_BI_VALUE_0 ((uint32)0U)

#define UART_LSR_TX_FIFO_E_SHIFT             ((uint32)5U)
#define UART_LSR_TX_FIFO_E_MASK              ((uint32)0x00000020U)
#define UART_LSR_TX_FIFO_E_TX_FIFO_E_VALUE_1 ((uint32)1U)
#define UART_LSR_TX_FIFO_E_TX_FIFO_E_VALUE_0 ((uint32)0U)

#define UART_LSR_TX_SR_E_SHIFT           ((uint32)6U)
#define UART_LSR_TX_SR_E_MASK            ((uint32)0x00000040U)
#define UART_LSR_TX_SR_E_TX_SR_E_VALUE_1 ((uint32)1U)
#define UART_LSR_TX_SR_E_TX_SR_E_VALUE_0 ((uint32)0U)

#define UART_LSR_RX_FIFO_STS_SHIFT               ((uint32)7U)
#define UART_LSR_RX_FIFO_STS_MASK                ((uint32)0x00000080U)
#define UART_LSR_RX_FIFO_STS_RX_FIFO_STS_VALUE_1 ((uint32)1U)
#define UART_LSR_RX_FIFO_STS_RX_FIFO_STS_VALUE_0 ((uint32)0U)

#define UART_LSR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_LSR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_MSR_CTS_STS_SHIFT           ((uint32)0U)
#define UART_MSR_CTS_STS_MASK            ((uint32)0x00000001U)
#define UART_MSR_CTS_STS_CTS_STS_VALUE_1 ((uint32)1U)

#define UART_MSR_DSR_STS_SHIFT           ((uint32)1U)
#define UART_MSR_DSR_STS_MASK            ((uint32)0x00000002U)
#define UART_MSR_DSR_STS_DSR_STS_VALUE_1 ((uint32)1U)

#define UART_MSR_RI_STS_SHIFT ((uint32)2U)
#define UART_MSR_RI_STS_MASK  ((uint32)0x00000004U)

#define UART_MSR_DCD_STS_SHIFT ((uint32)3U)
#define UART_MSR_DCD_STS_MASK  ((uint32)0x00000008U)

#define UART_MSR_NCTS_STS_SHIFT ((uint32)4U)
#define UART_MSR_NCTS_STS_MASK  ((uint32)0x00000010U)

#define UART_MSR_NDSR_STS_SHIFT ((uint32)5U)
#define UART_MSR_NDSR_STS_MASK  ((uint32)0x00000020U)

#define UART_MSR_NRI_STS_SHIFT ((uint32)6U)
#define UART_MSR_NRI_STS_MASK  ((uint32)0x00000040U)

#define UART_MSR_NCD_STS_SHIFT ((uint32)7U)
#define UART_MSR_NCD_STS_MASK  ((uint32)0x00000080U)

#define UART_MSR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_MSR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SPR_SPR_WORD_SHIFT ((uint32)0U)
#define UART_SPR_SPR_WORD_MASK  ((uint32)0x000000ffU)

#define UART_SPR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SPR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_MDR1_MODE_SELECT_SHIFT               ((uint32)0U)
#define UART_MDR1_MODE_SELECT_MASK                ((uint32)0x00000007U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_7 ((uint32)7U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_6 ((uint32)6U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_5 ((uint32)5U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_4 ((uint32)4U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_3 ((uint32)3U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_2 ((uint32)2U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_1 ((uint32)1U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_0 ((uint32)0U)

#define UART_MDR1_IR_SLEEP_SHIFT            ((uint32)3U)
#define UART_MDR1_IR_SLEEP_MASK             ((uint32)0x00000008U)
#define UART_MDR1_IR_SLEEP_IR_SLEEP_VALUE_1 ((uint32)1U)
#define UART_MDR1_IR_SLEEP_IR_SLEEP_VALUE_0 ((uint32)0U)

#define UART_MDR1_SET_TXIR_SHIFT            ((uint32)4U)
#define UART_MDR1_SET_TXIR_MASK             ((uint32)0x00000010U)
#define UART_MDR1_SET_TXIR_SET_TXIR_VALUE_1 ((uint32)1U)
#define UART_MDR1_SET_TXIR_SET_TXIR_VALUE_0 ((uint32)0U)

#define UART_MDR1_SCT_SHIFT       ((uint32)5U)
#define UART_MDR1_SCT_MASK        ((uint32)0x00000020U)
#define UART_MDR1_SCT_SCT_VALUE_1 ((uint32)1U)
#define UART_MDR1_SCT_SCT_VALUE_0 ((uint32)0U)

#define UART_MDR1_SIP_MODE_SHIFT            ((uint32)6U)
#define UART_MDR1_SIP_MODE_MASK             ((uint32)0x00000040U)
#define UART_MDR1_SIP_MODE_SIP_MODE_VALUE_1 ((uint32)1U)
#define UART_MDR1_SIP_MODE_SIP_MODE_VALUE_0 ((uint32)0U)

#define UART_MDR1_FRAME_END_MODE_SHIFT                  ((uint32)7U)
#define UART_MDR1_FRAME_END_MODE_MASK                   ((uint32)0x00000080U)
#define UART_MDR1_FRAME_END_MODE_FRAME_END_MODE_VALUE_1 ((uint32)1U)
#define UART_MDR1_FRAME_END_MODE_FRAME_END_MODE_VALUE_0 ((uint32)0U)

#define UART_MDR1_RESERVED_24_SHIFT ((uint32)8U)
#define UART_MDR1_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_MDR2_IRTX_UNDERRUN_SHIFT                 ((uint32)0U)
#define UART_MDR2_IRTX_UNDERRUN_MASK                  ((uint32)0x00000001U)
#define UART_MDR2_IRTX_UNDERRUN_IRTX_UNDERRUN_VALUE_1 ((uint32)1U)
#define UART_MDR2_IRTX_UNDERRUN_IRTX_UNDERRUN_VALUE_0 ((uint32)0U)

#define UART_MDR2_STS_FIFO_TRIG_SHIFT                 ((uint32)1U)
#define UART_MDR2_STS_FIFO_TRIG_MASK                  ((uint32)0x00000006U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_3 ((uint32)3U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_2 ((uint32)2U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_1 ((uint32)1U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_0 ((uint32)0U)

#define UART_MDR2_UART_PULSE_SHIFT              ((uint32)3U)
#define UART_MDR2_UART_PULSE_MASK               ((uint32)0x00000008U)
#define UART_MDR2_UART_PULSE_UART_PULSE_VALUE_1 ((uint32)1U)
#define UART_MDR2_UART_PULSE_UART_PULSE_VALUE_0 ((uint32)0U)

#define UART_MDR2_CIR_PULSE_MODE_SHIFT                  ((uint32)4U)
#define UART_MDR2_CIR_PULSE_MODE_MASK                   ((uint32)0x00000030U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_3 ((uint32)3U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_2 ((uint32)2U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_1 ((uint32)1U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_0 ((uint32)0U)

#define UART_MDR2_IRRXINVERT_SHIFT              ((uint32)6U)
#define UART_MDR2_IRRXINVERT_MASK               ((uint32)0x00000040U)
#define UART_MDR2_IRRXINVERT_IRRXINVERT_VALUE_1 ((uint32)1U)
#define UART_MDR2_IRRXINVERT_IRRXINVERT_VALUE_0 ((uint32)0U)

#define UART_MDR2_SET_TXIR_ALT_SHIFT                ((uint32)7U)
#define UART_MDR2_SET_TXIR_ALT_MASK                 ((uint32)0x00000080U)
#define UART_MDR2_SET_TXIR_ALT_SET_TXIR_ALT_VALUE_0 ((uint32)0U)
#define UART_MDR2_SET_TXIR_ALT_SET_TXIR_ALT_VALUE_1 ((uint32)1U)

#define UART_MDR2_RESERVED_24_SHIFT ((uint32)8U)
#define UART_MDR2_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SFLSR_RESERVED0_SHIFT ((uint32)0U)
#define UART_SFLSR_RESERVED0_MASK  ((uint32)0x00000001U)

#define UART_SFLSR_CRC_ERROR_SHIFT             ((uint32)1U)
#define UART_SFLSR_CRC_ERROR_MASK              ((uint32)0x00000002U)
#define UART_SFLSR_CRC_ERROR_CRC_ERROR_VALUE_1 ((uint32)1U)

#define UART_SFLSR_ABORT_DETECT_SHIFT                ((uint32)2U)
#define UART_SFLSR_ABORT_DETECT_MASK                 ((uint32)0x00000004U)
#define UART_SFLSR_ABORT_DETECT_ABORT_DETECT_VALUE_1 ((uint32)1U)

#define UART_SFLSR_FRAME_TOO_LONG_ERROR_SHIFT                        ((uint32)3U)
#define UART_SFLSR_FRAME_TOO_LONG_ERROR_MASK                         ((uint32)0x00000008U)
#define UART_SFLSR_FRAME_TOO_LONG_ERROR_FRAME_TOO_LONG_ERROR_VALUE_1 ((uint32)1U)

#define UART_SFLSR_OE_ERROR_SHIFT            ((uint32)4U)
#define UART_SFLSR_OE_ERROR_MASK             ((uint32)0x00000010U)
#define UART_SFLSR_OE_ERROR_OE_ERROR_VALUE_1 ((uint32)1U)

#define UART_SFLSR_RESERVED5_SHIFT ((uint32)5U)
#define UART_SFLSR_RESERVED5_MASK  ((uint32)0x000000e0U)

#define UART_SFLSR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SFLSR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_TXFLL_TXFLL_SHIFT ((uint32)0U)
#define UART_TXFLL_TXFLL_MASK  ((uint32)0x000000ffU)

#define UART_TXFLL_RESERVED_24_SHIFT ((uint32)8U)
#define UART_TXFLL_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_RESUME_RESUME_SHIFT ((uint32)0U)
#define UART_RESUME_RESUME_MASK  ((uint32)0x000000ffU)

#define UART_RESUME_RESERVED_24_SHIFT ((uint32)8U)
#define UART_RESUME_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_TXFLH_TXFLH_SHIFT ((uint32)0U)
#define UART_TXFLH_TXFLH_MASK  ((uint32)0x0000001fU)

#define UART_TXFLH_RESERVED_SHIFT ((uint32)5U)
#define UART_TXFLH_RESERVED_MASK  ((uint32)0x000000e0U)

#define UART_TXFLH_RESERVED_24_SHIFT ((uint32)8U)
#define UART_TXFLH_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SFREGL_SFREGL_SHIFT ((uint32)0U)
#define UART_SFREGL_SFREGL_MASK  ((uint32)0x000000ffU)

#define UART_SFREGL_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SFREGL_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_RXFLL_RXFLL_SHIFT ((uint32)0U)
#define UART_RXFLL_RXFLL_MASK  ((uint32)0x000000ffU)

#define UART_RXFLL_RESERVED_24_SHIFT ((uint32)8U)
#define UART_RXFLL_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SFREGH_SFREGH_SHIFT ((uint32)0U)
#define UART_SFREGH_SFREGH_MASK  ((uint32)0x0000000fU)

#define UART_SFREGH_RESERVED_SHIFT ((uint32)4U)
#define UART_SFREGH_RESERVED_MASK  ((uint32)0x000000f0U)

#define UART_SFREGH_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SFREGH_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_RXFLH_RXFLH_SHIFT ((uint32)0U)
#define UART_RXFLH_RXFLH_MASK  ((uint32)0x0000000fU)

#define UART_RXFLH_RESERVED_SHIFT ((uint32)4U)
#define UART_RXFLH_RESERVED_MASK  ((uint32)0x000000f0U)

#define UART_RXFLH_RESERVED_24_SHIFT ((uint32)8U)
#define UART_RXFLH_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_BLR_RESERVED_SHIFT ((uint32)0U)
#define UART_BLR_RESERVED_MASK  ((uint32)0x0000003fU)

#define UART_BLR_XBOF_TYPE_SHIFT             ((uint32)6U)
#define UART_BLR_XBOF_TYPE_MASK              ((uint32)0x00000040U)
#define UART_BLR_XBOF_TYPE_XBOF_TYPE_VALUE_1 ((uint32)1U)
#define UART_BLR_XBOF_TYPE_XBOF_TYPE_VALUE_0 ((uint32)0U)

#define UART_BLR_STS_FIFO_RESET_SHIFT ((uint32)7U)
#define UART_BLR_STS_FIFO_RESET_MASK  ((uint32)0x00000080U)

#define UART_BLR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_BLR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_ACREG_EOT_EN_SHIFT ((uint32)0U)
#define UART_ACREG_EOT_EN_MASK  ((uint32)0x00000001U)

#define UART_ACREG_ABORT_EN_SHIFT ((uint32)1U)
#define UART_ACREG_ABORT_EN_MASK  ((uint32)0x00000002U)

#define UART_ACREG_SCTX_EN_SHIFT ((uint32)2U)
#define UART_ACREG_SCTX_EN_MASK  ((uint32)0x00000004U)

#define UART_ACREG_SEND_SIP_SHIFT            ((uint32)3U)
#define UART_ACREG_SEND_SIP_MASK             ((uint32)0x00000008U)
#define UART_ACREG_SEND_SIP_SEND_SIP_VALUE_1 ((uint32)1U)
#define UART_ACREG_SEND_SIP_SEND_SIP_VALUE_0 ((uint32)0U)

#define UART_ACREG_DIS_TX_UNDERRUN_SHIFT                   ((uint32)4U)
#define UART_ACREG_DIS_TX_UNDERRUN_MASK                    ((uint32)0x00000010U)
#define UART_ACREG_DIS_TX_UNDERRUN_DIS_TX_UNDERRUN_VALUE_1 ((uint32)1U)
#define UART_ACREG_DIS_TX_UNDERRUN_DIS_TX_UNDERRUN_VALUE_0 ((uint32)0U)

#define UART_ACREG_DIS_IR_RX_SHIFT             ((uint32)5U)
#define UART_ACREG_DIS_IR_RX_MASK              ((uint32)0x00000020U)
#define UART_ACREG_DIS_IR_RX_DIS_IR_RX_VALUE_1 ((uint32)1U)
#define UART_ACREG_DIS_IR_RX_DIS_IR_RX_VALUE_0 ((uint32)0U)

#define UART_ACREG_SD_MOD_SHIFT          ((uint32)6U)
#define UART_ACREG_SD_MOD_MASK           ((uint32)0x00000040U)
#define UART_ACREG_SD_MOD_SD_MOD_VALUE_1 ((uint32)1U)
#define UART_ACREG_SD_MOD_SD_MOD_VALUE_0 ((uint32)0U)

#define UART_ACREG_PULSE_TYPE_SHIFT              ((uint32)7U)
#define UART_ACREG_PULSE_TYPE_MASK               ((uint32)0x00000080U)
#define UART_ACREG_PULSE_TYPE_PULSE_TYPE_VALUE_1 ((uint32)1U)
#define UART_ACREG_PULSE_TYPE_PULSE_TYPE_VALUE_0 ((uint32)0U)

#define UART_ACREG_RESERVED_24_SHIFT ((uint32)8U)
#define UART_ACREG_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SCR_DMA_MODE_CTL_SHIFT                ((uint32)0U)
#define UART_SCR_DMA_MODE_CTL_MASK                 ((uint32)0x00000001U)
#define UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_1 ((uint32)1U)
#define UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_0 ((uint32)0U)

#define UART_SCR_DMA_MODE_2_SHIFT              ((uint32)1U)
#define UART_SCR_DMA_MODE_2_MASK               ((uint32)0x00000006U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_3 ((uint32)3U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_2 ((uint32)2U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_1 ((uint32)1U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_0 ((uint32)0U)

#define UART_SCR_TX_EMPTY_CTL_IT_SHIFT                   ((uint32)3U)
#define UART_SCR_TX_EMPTY_CTL_IT_MASK                    ((uint32)0x00000008U)
#define UART_SCR_TX_EMPTY_CTL_IT_TX_EMPTY_CTL_IT_VALUE_1 ((uint32)1U)
#define UART_SCR_TX_EMPTY_CTL_IT_TX_EMPTY_CTL_IT_VALUE_0 ((uint32)0U)

#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_SHIFT                             ((uint32)4U)
#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_MASK                              ((uint32)0x00000010U)
#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_RX_CTS_DSR_WAKE_UP_ENABLE_VALUE_1 ((uint32)1U)
#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_RX_CTS_DSR_WAKE_UP_ENABLE_VALUE_0 ((uint32)0U)

#define UART_SCR_DSR_IT_SHIFT          ((uint32)5U)
#define UART_SCR_DSR_IT_MASK           ((uint32)0x00000020U)
#define UART_SCR_DSR_IT_DSR_IT_VALUE_1 ((uint32)1U)
#define UART_SCR_DSR_IT_DSR_IT_VALUE_0 ((uint32)0U)

#define UART_SCR_TX_TRIG_GRANU1_SHIFT                  ((uint32)6U)
#define UART_SCR_TX_TRIG_GRANU1_MASK                   ((uint32)0x00000040U)
#define UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_1 ((uint32)1U)
#define UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_0 ((uint32)0U)

#define UART_SCR_RX_TRIG_GRANU1_SHIFT                  ((uint32)7U)
#define UART_SCR_RX_TRIG_GRANU1_MASK                   ((uint32)0x00000080U)
#define UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_1 ((uint32)1U)
#define UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_0 ((uint32)0U)

#define UART_SCR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SCR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SSR_TX_FIFO_FULL_SHIFT                ((uint32)0U)
#define UART_SSR_TX_FIFO_FULL_MASK                 ((uint32)0x00000001U)
#define UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_1 ((uint32)1U)
#define UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_0 ((uint32)0U)

#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_SHIFT                          ((uint32)1U)
#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_MASK                           ((uint32)0x00000002U)
#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_RX_CTS_DSR_WAKE_UP_STS_VALUE_1 ((uint32)1U)
#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_RX_CTS_DSR_WAKE_UP_STS_VALUE_0 ((uint32)0U)

#define UART_SSR_RESERVED_SHIFT ((uint32)3U)
#define UART_SSR_RESERVED_MASK  ((uint32)0x000000f8U)

#define UART_SSR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SSR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SSR_DMA_COUNTER_RST_SHIFT                   ((uint32)2U)
#define UART_SSR_DMA_COUNTER_RST_MASK                    ((uint32)0x00000004U)
#define UART_SSR_DMA_COUNTER_RST_DMA_COUNTER_RST_VALUE_0 ((uint32)0U)
#define UART_SSR_DMA_COUNTER_RST_DMA_COUNTER_RST_VALUE_1 ((uint32)1U)

#define UART_EBLR_EBLR_SHIFT ((uint32)0U)
#define UART_EBLR_EBLR_MASK  ((uint32)0x000000ffU)

#define UART_EBLR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_EBLR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_MVR_MINOR_SHIFT ((uint32)0U)
#define UART_MVR_MINOR_MASK  ((uint32)0x0000003fU)

#define UART_MVR_CUSTOM_SHIFT ((uint32)6U)
#define UART_MVR_CUSTOM_MASK  ((uint32)0x000000c0U)

#define UART_MVR_MAJOR_SHIFT ((uint32)8U)
#define UART_MVR_MAJOR_MASK  ((uint32)0x00000700U)

#define UART_MVR_RTL_SHIFT ((uint32)11U)
#define UART_MVR_RTL_MASK  ((uint32)0x0000f800U)

#define UART_MVR_FUNC_SHIFT ((uint32)16U)
#define UART_MVR_FUNC_MASK  ((uint32)0x0fff0000U)

#define UART_MVR_RESERVED_SHIFT ((uint32)28U)
#define UART_MVR_RESERVED_MASK  ((uint32)0x30000000U)

#define UART_MVR_SCHEME_SHIFT ((uint32)30U)
#define UART_MVR_SCHEME_MASK  ((uint32)0xc0000000U)

#define UART_SYSC_AUTOIDLE_SHIFT            ((uint32)0U)
#define UART_SYSC_AUTOIDLE_MASK             ((uint32)0x00000001U)
#define UART_SYSC_AUTOIDLE_AUTOIDLE_VALUE_1 ((uint32)1U)
#define UART_SYSC_AUTOIDLE_AUTOIDLE_VALUE_0 ((uint32)0U)

#define UART_SYSC_SOFTRESET_SHIFT             ((uint32)1U)
#define UART_SYSC_SOFTRESET_MASK              ((uint32)0x00000002U)
#define UART_SYSC_SOFTRESET_SOFTRESET_VALUE_1 ((uint32)1U)
#define UART_SYSC_SOFTRESET_SOFTRESET_VALUE_0 ((uint32)0U)

#define UART_SYSC_ENAWAKEUP_SHIFT             ((uint32)2U)
#define UART_SYSC_ENAWAKEUP_MASK              ((uint32)0x00000004U)
#define UART_SYSC_ENAWAKEUP_ENAWAKEUP_VALUE_1 ((uint32)1U)
#define UART_SYSC_ENAWAKEUP_ENAWAKEUP_VALUE_0 ((uint32)0U)

#define UART_SYSC_IDLEMODE_SHIFT            ((uint32)3U)
#define UART_SYSC_IDLEMODE_MASK             ((uint32)0x00000018U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_3 ((uint32)3U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_2 ((uint32)2U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_1 ((uint32)1U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_0 ((uint32)0U)

#define UART_SYSC_RESERVED_SHIFT ((uint32)5U)
#define UART_SYSC_RESERVED_MASK  ((uint32)0x000000e0U)

#define UART_SYSC_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SYSC_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_SYSS_RESETDONE_SHIFT             ((uint32)0U)
#define UART_SYSS_RESETDONE_MASK              ((uint32)0x00000001U)
#define UART_SYSS_RESETDONE_RESETDONE_VALUE_1 ((uint32)1U)
#define UART_SYSS_RESETDONE_RESETDONE_VALUE_0 ((uint32)0U)

#define UART_SYSS_RESERVED_SHIFT ((uint32)1U)
#define UART_SYSS_RESERVED_MASK  ((uint32)0x000000feU)

#define UART_SYSS_RESERVED_24_SHIFT ((uint32)8U)
#define UART_SYSS_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_WER_EVENT_0_CTS_ACTIVITY_SHIFT                        ((uint32)0U)
#define UART_WER_EVENT_0_CTS_ACTIVITY_MASK                         ((uint32)0x00000001U)
#define UART_WER_EVENT_0_CTS_ACTIVITY_EVENT_0_CTS_ACTIVITY_VALUE_1 ((uint32)1U)
#define UART_WER_EVENT_0_CTS_ACTIVITY_EVENT_0_CTS_ACTIVITY_VALUE_0 ((uint32)0U)

#define UART_WER_EVENT_1_DSR_ACTIVITY_SHIFT                        ((uint32)1U)
#define UART_WER_EVENT_1_DSR_ACTIVITY_MASK                         ((uint32)0x00000002U)
#define UART_WER_EVENT_1_DSR_ACTIVITY_EVENT_1_DSR_ACTIVITY_VALUE_1 ((uint32)1U)
#define UART_WER_EVENT_1_DSR_ACTIVITY_EVENT_1_DSR_ACTIVITY_VALUE_0 ((uint32)0U)

#define UART_WER_EVENT_2_RI_ACTIVITY_SHIFT                       ((uint32)2U)
#define UART_WER_EVENT_2_RI_ACTIVITY_MASK                        ((uint32)0x00000004U)
#define UART_WER_EVENT_2_RI_ACTIVITY_EVENT_2_RI_ACTIVITY_VALUE_1 ((uint32)1U)
#define UART_WER_EVENT_2_RI_ACTIVITY_EVENT_2_RI_ACTIVITY_VALUE_0 ((uint32)0U)

#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_SHIFT                           ((uint32)3U)
#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_MASK                            ((uint32)0x00000008U)
#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_EVENT_3_DCD_CD_ACTIVITY_VALUE_1 ((uint32)1U)
#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_EVENT_3_DCD_CD_ACTIVITY_VALUE_0 ((uint32)0U)

#define UART_WER_EVENT_4_RX_ACTIVITY_SHIFT                       ((uint32)4U)
#define UART_WER_EVENT_4_RX_ACTIVITY_MASK                        ((uint32)0x00000010U)
#define UART_WER_EVENT_4_RX_ACTIVITY_EVENT_4_RX_ACTIVITY_VALUE_1 ((uint32)1U)
#define UART_WER_EVENT_4_RX_ACTIVITY_EVENT_4_RX_ACTIVITY_VALUE_0 ((uint32)0U)

#define UART_WER_EVENT_5_RHR_INTERRUPT_SHIFT                         ((uint32)5U)
#define UART_WER_EVENT_5_RHR_INTERRUPT_MASK                          ((uint32)0x00000020U)
#define UART_WER_EVENT_5_RHR_INTERRUPT_EVENT_5_RHR_INTERRUPT_VALUE_1 ((uint32)1U)
#define UART_WER_EVENT_5_RHR_INTERRUPT_EVENT_5_RHR_INTERRUPT_VALUE_0 ((uint32)0U)

#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_SHIFT                                          ((uint32)6U)
#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_MASK                                           ((uint32)0x00000040U)
#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_VALUE_1 ((uint32)1U)
#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_VALUE_0 ((uint32)0U)

#define UART_WER_EVENT_7_TX_WAKEUP_EN_SHIFT                        ((uint32)7U)
#define UART_WER_EVENT_7_TX_WAKEUP_EN_MASK                         ((uint32)0x00000080U)
#define UART_WER_EVENT_7_TX_WAKEUP_EN_EVENT_7_TX_WAKEUP_EN_VALUE_0 ((uint32)0U)
#define UART_WER_EVENT_7_TX_WAKEUP_EN_EVENT_7_TX_WAKEUP_EN_VALUE_1 ((uint32)1U)

#define UART_WER_RESERVED_24_SHIFT ((uint32)8U)
#define UART_WER_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_CFPS_CFPS_SHIFT ((uint32)0U)
#define UART_CFPS_CFPS_MASK  ((uint32)0x000000ffU)

#define UART_CFPS_RESERVED_24_SHIFT ((uint32)8U)
#define UART_CFPS_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_RXFIFO_LVL_RXFIFO_LVL_SHIFT ((uint32)0U)
#define UART_RXFIFO_LVL_RXFIFO_LVL_MASK  ((uint32)0x000000ffU)

#define UART_RXFIFO_LVL_RESERVED24_SHIFT ((uint32)8U)
#define UART_RXFIFO_LVL_RESERVED24_MASK  ((uint32)0xffffff00U)

#define UART_TXFIFO_LVL_TXFIFO_LVL_SHIFT ((uint32)0U)
#define UART_TXFIFO_LVL_TXFIFO_LVL_MASK  ((uint32)0x000000ffU)

#define UART_TXFIFO_LVL_RESERVED24_SHIFT ((uint32)8U)
#define UART_TXFIFO_LVL_RESERVED24_MASK  ((uint32)0xffffff00U)

#define UART_IER2_EN_RXFIFO_EMPTY_SHIFT ((uint32)0U)
#define UART_IER2_EN_RXFIFO_EMPTY_MASK  ((uint32)0x00000001U)

#define UART_IER2_EN_TXFIFO_EMPTY_SHIFT ((uint32)1U)
#define UART_IER2_EN_TXFIFO_EMPTY_MASK  ((uint32)0x00000002U)

#define UART_IER2_RESERVED_SHIFT ((uint32)2U)
#define UART_IER2_RESERVED_MASK  ((uint32)0x000000fcU)

#define UART_IER2_RESERVED1_SHIFT ((uint32)8U)
#define UART_IER2_RESERVED1_MASK  ((uint32)0xffffff00U)

#define UART_ISR2_RXFIFO_EMPTY_STS_SHIFT                    ((uint32)0U)
#define UART_ISR2_RXFIFO_EMPTY_STS_MASK                     ((uint32)0x00000001U)
#define UART_ISR2_RXFIFO_EMPTY_STS_RXFIFO_EMPTY_STS_VALUE_0 ((uint32)0U)
#define UART_ISR2_RXFIFO_EMPTY_STS_RXFIFO_EMPTY_STS_VALUE_1 ((uint32)1U)

#define UART_ISR2_TXFIFO_EMPTY_STS_SHIFT                    ((uint32)1U)
#define UART_ISR2_TXFIFO_EMPTY_STS_MASK                     ((uint32)0x00000002U)
#define UART_ISR2_TXFIFO_EMPTY_STS_TXFIFO_EMPTY_STS_VALUE_0 ((uint32)0U)
#define UART_ISR2_TXFIFO_EMPTY_STS_TXFIFO_EMPTY_STS_VALUE_1 ((uint32)1U)

#define UART_ISR2_RESERVED_SHIFT ((uint32)2U)
#define UART_ISR2_RESERVED_MASK  ((uint32)0x000000fcU)

#define UART_ISR2_RESERVED1_SHIFT ((uint32)8U)
#define UART_ISR2_RESERVED1_MASK  ((uint32)0xffffff00U)

#define UART_FREQ_SEL_FREQ_SEL_SHIFT ((uint32)0U)
#define UART_FREQ_SEL_FREQ_SEL_MASK  ((uint32)0x000000ffU)

#define UART_FREQ_SEL_RESERVED2_SHIFT ((uint32)8U)
#define UART_FREQ_SEL_RESERVED2_MASK  ((uint32)0xffffff00U)

#define UART_ABAUD_1ST_CHAR_RESERVED_SHIFT ((uint32)0U)
#define UART_ABAUD_1ST_CHAR_RESERVED_MASK  ((uint32)0xffffffffU)

#define UART_BAUD_2ND_CHAR_RESERVED_SHIFT ((uint32)0U)
#define UART_BAUD_2ND_CHAR_RESERVED_MASK  ((uint32)0xffffffffU)

#define UART_MDR3_DISABLE_CIR_RX_DEMOD_SHIFT                        ((uint32)0U)
#define UART_MDR3_DISABLE_CIR_RX_DEMOD_MASK                         ((uint32)0x00000001U)
#define UART_MDR3_DISABLE_CIR_RX_DEMOD_DISABLE_CIR_RX_DEMOD_VALUE_0 ((uint32)0U)
#define UART_MDR3_DISABLE_CIR_RX_DEMOD_DISABLE_CIR_RX_DEMOD_VALUE_1 ((uint32)1U)

#define UART_MDR3_NONDEFAULT_FREQ_SHIFT ((uint32)1U)
#define UART_MDR3_NONDEFAULT_FREQ_MASK  ((uint32)0x00000002U)

#define UART_MDR3_SET_DMA_TX_THRESHOLD_SHIFT ((uint32)2U)
#define UART_MDR3_SET_DMA_TX_THRESHOLD_MASK  ((uint32)0x00000004U)

#ifdef CSL_MODIFICATION
#define UART_MDR3_RESERVED1_SHIFT ((uint32)3U)
#define UART_MDR3_RESERVED1_MASK  ((uint32)0x000000f8U)
#else
#define UART_MDR3_DIR_POL_SHIFT ((uint32)3U)
#define UART_MDR3_DIR_POL_MASK  ((uint32)0x00000008U)

#define UART_MDR3_DIR_EN_SHIFT ((uint32)4U)
#define UART_MDR3_DIR_EN_MASK  ((uint32)0x00000010U)

#define UART_MDR3_RESERVED1_SHIFT ((uint32)5U)
#define UART_MDR3_RESERVED1_MASK  ((uint32)0x000000e0U)
#endif

#define UART_MDR3_RESERVED2_SHIFT ((uint32)8U)
#define UART_MDR3_RESERVED2_MASK  ((uint32)0xffffff00U)

#define UART_TX_DMA_THRESHOLD_TX_DMA_THRESHOLD_SHIFT ((uint32)0U)
#define UART_TX_DMA_THRESHOLD_TX_DMA_THRESHOLD_MASK  ((uint32)0x0000001fU)

#define UART_TX_DMA_THRESHOLD_RESERVED_SHIFT ((uint32)5U)
#define UART_TX_DMA_THRESHOLD_RESERVED_MASK  ((uint32)0x000000e0U)

#define UART_TX_DMA_THRESHOLD_RESERVED1_SHIFT ((uint32)8U)
#define UART_TX_DMA_THRESHOLD_RESERVED1_MASK  ((uint32)0xffffff00U)

#define UART_DLL_CLOCK_LSB_SHIFT ((uint32)0U)
#define UART_DLL_CLOCK_LSB_MASK  ((uint32)0x000000ffU)

#define UART_DLL_RESERVED_SHIFT ((uint32)8U)
#define UART_DLL_RESERVED_MASK  ((uint32)0xffffff00U)

#define UART_IER_IRDA_RHR_IT_SHIFT          ((uint32)0U)
#define UART_IER_IRDA_RHR_IT_MASK           ((uint32)0x00000001U)
#define UART_IER_IRDA_RHR_IT_RHR_IT_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_RHR_IT_RHR_IT_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_THR_IT_SHIFT          ((uint32)1U)
#define UART_IER_IRDA_THR_IT_MASK           ((uint32)0x00000002U)
#define UART_IER_IRDA_THR_IT_THR_IT_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_THR_IT_THR_IT_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_LAST_RX_BYTE_IT_SHIFT                   ((uint32)2U)
#define UART_IER_IRDA_LAST_RX_BYTE_IT_MASK                    ((uint32)0x00000004U)
#define UART_IER_IRDA_LAST_RX_BYTE_IT_LAST_RX_BYTE_IT_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_LAST_RX_BYTE_IT_LAST_RX_BYTE_IT_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_RX_OVERRUN_IT_SHIFT                 ((uint32)3U)
#define UART_IER_IRDA_RX_OVERRUN_IT_MASK                  ((uint32)0x00000008U)
#define UART_IER_IRDA_RX_OVERRUN_IT_RX_OVERRUN_IT_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_RX_OVERRUN_IT_RX_OVERRUN_IT_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_STS_FIFO_TRIG_IT_SHIFT                    ((uint32)4U)
#define UART_IER_IRDA_STS_FIFO_TRIG_IT_MASK                     ((uint32)0x00000010U)
#define UART_IER_IRDA_STS_FIFO_TRIG_IT_STS_FIFO_TRIG_IT_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_STS_FIFO_TRIG_IT_STS_FIFO_TRIG_IT_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_TX_STATUS_IT_SHIFT             ((uint32)5U)
#define UART_IER_IRDA_TX_STATUS_IT_MASK              ((uint32)0x00000020U)
#define UART_IER_IRDA_TX_STATUS_IT_TX_STATUS_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_TX_STATUS_IT_TX_STATUS_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_LINE_STS_IT_SHIFT                 ((uint32)6U)
#define UART_IER_IRDA_LINE_STS_IT_MASK                  ((uint32)0x00000040U)
#define UART_IER_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_EOF_IT_SHIFT            ((uint32)7U)
#define UART_IER_IRDA_EOF_IT_MASK             ((uint32)0x00000080U)
#define UART_IER_IRDA_EOF_IT_EOF_IT_U_VALUE_1 ((uint32)1U)
#define UART_IER_IRDA_EOF_IT_EOF_IT_U_VALUE_0 ((uint32)0U)

#define UART_IER_IRDA_RESERVED_SHIFT ((uint32)8U)
#define UART_IER_IRDA_RESERVED_MASK  ((uint32)0xffffff00U)

#define UART_IER_CIR_RHR_IT_SHIFT          ((uint32)0U)
#define UART_IER_CIR_RHR_IT_MASK           ((uint32)0x00000001U)
#define UART_IER_CIR_RHR_IT_RHR_IT_VALUE_1 ((uint32)1U)
#define UART_IER_CIR_RHR_IT_RHR_IT_VALUE_0 ((uint32)0U)

#define UART_IER_CIR_THR_IT_SHIFT          ((uint32)1U)
#define UART_IER_CIR_THR_IT_MASK           ((uint32)0x00000002U)
#define UART_IER_CIR_THR_IT_THR_IT_VALUE_1 ((uint32)1U)
#define UART_IER_CIR_THR_IT_THR_IT_VALUE_0 ((uint32)0U)

#define UART_IER_CIR_RX_STOP_IT_SHIFT                ((uint32)2U)
#define UART_IER_CIR_RX_STOP_IT_MASK                 ((uint32)0x00000004U)
#define UART_IER_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_1 ((uint32)1U)
#define UART_IER_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_0 ((uint32)0U)

#define UART_IER_CIR_RX_OVERRUN_IT_SHIFT                   ((uint32)3U)
#define UART_IER_CIR_RX_OVERRUN_IT_MASK                    ((uint32)0x00000008U)
#define UART_IER_CIR_RX_OVERRUN_IT_RX_OVERRUN_IT_U_VALUE_1 ((uint32)1U)
#define UART_IER_CIR_RX_OVERRUN_IT_RX_OVERRUN_IT_U_VALUE_0 ((uint32)0U)

#define UART_IER_CIR_RESERVED_1_SHIFT ((uint32)4U)
#define UART_IER_CIR_RESERVED_1_MASK  ((uint32)0x00000010U)

#define UART_IER_CIR_TX_STATUS_IT_SHIFT                  ((uint32)5U)
#define UART_IER_CIR_TX_STATUS_IT_MASK                   ((uint32)0x00000020U)
#define UART_IER_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_1 ((uint32)1U)
#define UART_IER_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_0 ((uint32)0U)

#define UART_IER_CIR_RESERVED_2_SHIFT ((uint32)6U)
#define UART_IER_CIR_RESERVED_2_MASK  ((uint32)0x000000c0U)

#define UART_IER_CIR_RESERVED_3_SHIFT ((uint32)8U)
#define UART_IER_CIR_RESERVED_3_MASK  ((uint32)0xffffff00U)

#define UART_DLH_CLOCK_MSB_SHIFT ((uint32)0U)
#define UART_DLH_CLOCK_MSB_MASK  ((uint32)0x0000003fU)

#define UART_DLH_RESERVED_SHIFT ((uint32)6U)
#define UART_DLH_RESERVED_MASK  ((uint32)0xffffffc0U)

#define UART_IIR_IRDA_RHR_IT_SHIFT          ((uint32)0U)
#define UART_IIR_IRDA_RHR_IT_MASK           ((uint32)0x00000001U)
#define UART_IIR_IRDA_RHR_IT_RHR_IT_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_RHR_IT_RHR_IT_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_THR_IT_SHIFT          ((uint32)1U)
#define UART_IIR_IRDA_THR_IT_MASK           ((uint32)0x00000002U)
#define UART_IIR_IRDA_THR_IT_THR_IT_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_THR_IT_THR_IT_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_SHIFT                          ((uint32)2U)
#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_MASK                           ((uint32)0x00000004U)
#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_RX_FIFO_LAST_BYTE_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_RX_FIFO_LAST_BYTE_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_RX_OE_IT_SHIFT              ((uint32)3U)
#define UART_IIR_IRDA_RX_OE_IT_MASK               ((uint32)0x00000008U)
#define UART_IIR_IRDA_RX_OE_IT_RX_OE_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_RX_OE_IT_RX_OE_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_STS_FIFO_IT_SHIFT                 ((uint32)4U)
#define UART_IIR_IRDA_STS_FIFO_IT_MASK                  ((uint32)0x00000010U)
#define UART_IIR_IRDA_STS_FIFO_IT_STS_FIFO_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_STS_FIFO_IT_STS_FIFO_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_TX_STATUS_IT_SHIFT                  ((uint32)5U)
#define UART_IIR_IRDA_TX_STATUS_IT_MASK                   ((uint32)0x00000020U)
#define UART_IIR_IRDA_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_LINE_STS_IT_SHIFT                 ((uint32)6U)
#define UART_IIR_IRDA_LINE_STS_IT_MASK                  ((uint32)0x00000040U)
#define UART_IIR_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_EOF_IT_SHIFT            ((uint32)7U)
#define UART_IIR_IRDA_EOF_IT_MASK             ((uint32)0x00000080U)
#define UART_IIR_IRDA_EOF_IT_EOF_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_IRDA_EOF_IT_EOF_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_IRDA_RESERVED_SHIFT ((uint32)8U)
#define UART_IIR_IRDA_RESERVED_MASK  ((uint32)0xffffff00U)

#define UART_IIR_CIR_RHR_IT_SHIFT          ((uint32)0U)
#define UART_IIR_CIR_RHR_IT_MASK           ((uint32)0x00000001U)
#define UART_IIR_CIR_RHR_IT_RHR_IT_VALUE_1 ((uint32)1U)
#define UART_IIR_CIR_RHR_IT_RHR_IT_VALUE_0 ((uint32)0U)

#define UART_IIR_CIR_THR_IT_SHIFT          ((uint32)1U)
#define UART_IIR_CIR_THR_IT_MASK           ((uint32)0x00000002U)
#define UART_IIR_CIR_THR_IT_THR_IT_VALUE_1 ((uint32)1U)
#define UART_IIR_CIR_THR_IT_THR_IT_VALUE_0 ((uint32)0U)

#define UART_IIR_CIR_RX_STOP_IT_SHIFT                ((uint32)2U)
#define UART_IIR_CIR_RX_STOP_IT_MASK                 ((uint32)0x00000004U)
#define UART_IIR_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_CIR_RX_OE_IT_SHIFT              ((uint32)3U)
#define UART_IIR_CIR_RX_OE_IT_MASK               ((uint32)0x00000008U)
#define UART_IIR_CIR_RX_OE_IT_RX_OE_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_CIR_RX_OE_IT_RX_OE_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_CIR_RESERVED_1_SHIFT ((uint32)4U)
#define UART_IIR_CIR_RESERVED_1_MASK  ((uint32)0x00000010U)

#define UART_IIR_CIR_TX_STATUS_IT_SHIFT                  ((uint32)5U)
#define UART_IIR_CIR_TX_STATUS_IT_MASK                   ((uint32)0x00000020U)
#define UART_IIR_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_1 ((uint32)1U)
#define UART_IIR_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_0 ((uint32)0U)

#define UART_IIR_CIR_RESERVED_2_SHIFT ((uint32)6U)
#define UART_IIR_CIR_RESERVED_2_MASK  ((uint32)0x000000c0U)

#define UART_IIR_CIR_RESERVED_SHIFT ((uint32)8U)
#define UART_IIR_CIR_RESERVED_MASK  ((uint32)0xffffff00U)

#define UART_EFR_SW_FLOW_CONTROL_SHIFT                      ((uint32)0U)
#define UART_EFR_SW_FLOW_CONTROL_MASK                       ((uint32)0x0000000fU)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_15 ((uint32)15U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_14 ((uint32)14U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_13 ((uint32)13U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_12 ((uint32)12U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_11 ((uint32)11U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_10 ((uint32)10U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_9  ((uint32)9U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_8  ((uint32)8U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_7  ((uint32)7U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_6  ((uint32)6U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_5  ((uint32)5U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_4  ((uint32)4U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_3  ((uint32)3U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_2  ((uint32)2U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_1  ((uint32)1U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_0  ((uint32)0U)

#define UART_EFR_HW_FLOW_CONTROL_SHIFT                ((uint32)6U)
#define UART_EFR_HW_FLOW_CONTROL_MASK                 ((uint32)0x000000C0U)
#define UART_EFR_HW_NO_FLOW_CONTROL_VALUE             ((uint32)0U)
#define UART_EFR_HW_ENABLE_RTS_FLOW_CONTROL_VALUE     ((uint32)1U)
#define UART_EFR_HW_ENALE_CTS_FLOW_CONTROL_VALUE      ((uint32)2U)
#define UART_EFR_HW_ENABLE_RTS_CTS_FLOW_CONTROL_VALUE ((uint32)3U)

#define UART_EFR_ENHANCED_EN_SHIFT                 ((uint32)4U)
#define UART_EFR_ENHANCED_EN_MASK                  ((uint32)0x00000010U)
#define UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1 ((uint32)1U)
#define UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_0 ((uint32)0U)

#define UART_EFR_SPECIAL_CHAR_DETECT_SHIFT                         ((uint32)5U)
#define UART_EFR_SPECIAL_CHAR_DETECT_MASK                          ((uint32)0x00000020U)
#define UART_EFR_SPECIAL_CHAR_DETECT_SPECIAL_CHAR_DETECT_U_VALUE_1 ((uint32)1U)
#define UART_EFR_SPECIAL_CHAR_DETECT_SPECIAL_CHAR_DETECT_U_VALUE_0 ((uint32)0U)

#define UART_EFR_AUTO_RTS_EN_SHIFT                 ((uint32)6U)
#define UART_EFR_AUTO_RTS_EN_MASK                  ((uint32)0x00000040U)
#define UART_EFR_AUTO_RTS_EN_AUTO_RTS_EN_U_VALUE_1 ((uint32)1U)
#define UART_EFR_AUTO_RTS_EN_AUTO_RTS_EN_U_VALUE_0 ((uint32)0U)

#define UART_EFR_AUTO_CTS_EN_SHIFT                 ((uint32)7U)
#define UART_EFR_AUTO_CTS_EN_MASK                  ((uint32)0x00000080U)
#define UART_EFR_AUTO_CTS_EN_AUTO_CTS_EN_U_VALUE_1 ((uint32)1U)
#define UART_EFR_AUTO_CTS_EN_AUTO_CTS_EN_U_VALUE_0 ((uint32)0U)

#define UART_EFR_RESERVED_SHIFT ((uint32)8U)
#define UART_EFR_RESERVED_MASK  ((uint32)0xffffff00U)

#define UART_XON1_ADDR1_XON_WORD1_SHIFT ((uint32)0U)
#define UART_XON1_ADDR1_XON_WORD1_MASK  ((uint32)0x000000ffU)

#define UART_XON1_ADDR1_RESERVED_24_SHIFT ((uint32)8U)
#define UART_XON1_ADDR1_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_LSR_IRDA_RX_FIFO_E_SHIFT             ((uint32)0U)
#define UART_LSR_IRDA_RX_FIFO_E_MASK              ((uint32)0x00000001U)
#define UART_LSR_IRDA_RX_FIFO_E_RX_FIFO_E_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_RX_FIFO_E_RX_FIFO_E_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_STS_FIFO_E_SHIFT              ((uint32)1U)
#define UART_LSR_IRDA_STS_FIFO_E_MASK               ((uint32)0x00000002U)
#define UART_LSR_IRDA_STS_FIFO_E_STS_FIFO_E_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_STS_FIFO_E_STS_FIFO_E_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_CRC_SHIFT       ((uint32)2U)
#define UART_LSR_IRDA_CRC_MASK        ((uint32)0x00000004U)
#define UART_LSR_IRDA_CRC_CRC_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_CRC_CRC_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_ABORT_SHIFT         ((uint32)3U)
#define UART_LSR_IRDA_ABORT_MASK          ((uint32)0x00000008U)
#define UART_LSR_IRDA_ABORT_ABORT_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_ABORT_ABORT_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_FRAME_TOO_LONG_SHIFT                  ((uint32)4U)
#define UART_LSR_IRDA_FRAME_TOO_LONG_MASK                   ((uint32)0x00000010U)
#define UART_LSR_IRDA_FRAME_TOO_LONG_FRAME_TOO_LONG_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_FRAME_TOO_LONG_FRAME_TOO_LONG_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_RX_LAST_BYTE_SHIFT                ((uint32)5U)
#define UART_LSR_IRDA_RX_LAST_BYTE_MASK                 ((uint32)0x00000020U)
#define UART_LSR_IRDA_RX_LAST_BYTE_RX_LAST_BYTE_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_RX_LAST_BYTE_RX_LAST_BYTE_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_STS_FIFO_FULL_SHIFT                 ((uint32)6U)
#define UART_LSR_IRDA_STS_FIFO_FULL_MASK                  ((uint32)0x00000040U)
#define UART_LSR_IRDA_STS_FIFO_FULL_STS_FIFO_FULL_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_STS_FIFO_FULL_STS_FIFO_FULL_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_THR_EMPTY_SHIFT             ((uint32)7U)
#define UART_LSR_IRDA_THR_EMPTY_MASK              ((uint32)0x00000080U)
#define UART_LSR_IRDA_THR_EMPTY_THR_EMPTY_VALUE_1 ((uint32)1U)
#define UART_LSR_IRDA_THR_EMPTY_THR_EMPTY_VALUE_0 ((uint32)0U)

#define UART_LSR_IRDA_RESERVED_24_SHIFT ((uint32)8U)
#define UART_LSR_IRDA_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_LSR_CIR_RX_FIFO_E_SHIFT             ((uint32)0U)
#define UART_LSR_CIR_RX_FIFO_E_MASK              ((uint32)0x00000001U)
#define UART_LSR_CIR_RX_FIFO_E_RX_FIFO_E_VALUE_1 ((uint32)1U)
#define UART_LSR_CIR_RX_FIFO_E_RX_FIFO_E_VALUE_0 ((uint32)0U)

#define UART_LSR_CIR_RESERVED_SHIFT ((uint32)1U)
#define UART_LSR_CIR_RESERVED_MASK  ((uint32)0x0000001eU)

#define UART_LSR_CIR_RX_STOP_SHIFT           ((uint32)5U)
#define UART_LSR_CIR_RX_STOP_MASK            ((uint32)0x00000020U)
#define UART_LSR_CIR_RX_STOP_RX_STOP_VALUE_1 ((uint32)1U)
#define UART_LSR_CIR_RX_STOP_RX_STOP_VALUE_0 ((uint32)0U)

#define UART_LSR_CIR_RESERVED_1_SHIFT ((uint32)6U)
#define UART_LSR_CIR_RESERVED_1_MASK  ((uint32)0x00000040U)

#define UART_LSR_CIR_THR_EMPTY_SHIFT             ((uint32)7U)
#define UART_LSR_CIR_THR_EMPTY_MASK              ((uint32)0x00000080U)
#define UART_LSR_CIR_THR_EMPTY_THR_EMPTY_VALUE_1 ((uint32)1U)
#define UART_LSR_CIR_THR_EMPTY_THR_EMPTY_VALUE_0 ((uint32)0U)

#define UART_LSR_CIR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_LSR_CIR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_XON2_ADDR2_XON_WORD2_SHIFT ((uint32)0U)
#define UART_XON2_ADDR2_XON_WORD2_MASK  ((uint32)0x000000ffU)

#define UART_XON2_ADDR2_RESERVED_24_SHIFT ((uint32)8U)
#define UART_XON2_ADDR2_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_XOFF1_XOFF_WORD1_SHIFT ((uint32)0U)
#define UART_XOFF1_XOFF_WORD1_MASK  ((uint32)0x000000ffU)

#define UART_XOFF1_RESERVED_24_SHIFT ((uint32)8U)
#define UART_XOFF1_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_TCR_RX_FIFO_TRIG_HALT_SHIFT ((uint32)0U)
#define UART_TCR_RX_FIFO_TRIG_HALT_MASK  ((uint32)0x0000000fU)

#define UART_TCR_RX_FIFO_TRIG_START_SHIFT ((uint32)4U)
#define UART_TCR_RX_FIFO_TRIG_START_MASK  ((uint32)0x000000f0U)

#define UART_TCR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_TCR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_XOFF2_XOFF_WORD2_SHIFT ((uint32)0U)
#define UART_XOFF2_XOFF_WORD2_MASK  ((uint32)0x000000ffU)

#define UART_XOFF2_RESERVED_24_SHIFT ((uint32)8U)
#define UART_XOFF2_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_TLR_TX_FIFO_TRIG_DMA_SHIFT ((uint32)0U)
#define UART_TLR_TX_FIFO_TRIG_DMA_MASK  ((uint32)0x0000000fU)

#define UART_TLR_RX_FIFO_TRIG_DMA_SHIFT ((uint32)4U)
#define UART_TLR_RX_FIFO_TRIG_DMA_MASK  ((uint32)0x000000f0U)

#define UART_TLR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_TLR_RESERVED_24_MASK  ((uint32)0xffffff00U)

#define UART_UASR_SPEED_SHIFT          ((uint32)0U)
#define UART_UASR_SPEED_MASK           ((uint32)0x0000001fU)
#define UART_UASR_SPEED_SPEED_VALUE_10 ((uint32)10U)
#define UART_UASR_SPEED_SPEED_VALUE_9  ((uint32)9U)
#define UART_UASR_SPEED_SPEED_VALUE_8  ((uint32)8U)
#define UART_UASR_SPEED_SPEED_VALUE_7  ((uint32)7U)
#define UART_UASR_SPEED_SPEED_VALUE_6  ((uint32)6U)
#define UART_UASR_SPEED_SPEED_VALUE_5  ((uint32)5U)
#define UART_UASR_SPEED_SPEED_VALUE_4  ((uint32)4U)
#define UART_UASR_SPEED_SPEED_VALUE_3  ((uint32)3U)
#define UART_UASR_SPEED_SPEED_VALUE_2  ((uint32)2U)
#define UART_UASR_SPEED_SPEED_VALUE_1  ((uint32)1U)
#define UART_UASR_SPEED_SPEED_VALUE_0  ((uint32)0U)

#define UART_UASR_BIT_BY_CHAR_SHIFT                 ((uint32)5U)
#define UART_UASR_BIT_BY_CHAR_MASK                  ((uint32)0x00000020U)
#define UART_UASR_BIT_BY_CHAR_BIT_BY_CHAR_U_VALUE_1 ((uint32)1U)
#define UART_UASR_BIT_BY_CHAR_BIT_BY_CHAR_U_VALUE_0 ((uint32)0U)

#define UART_UASR_PARITY_TYPE_SHIFT                 ((uint32)6U)
#define UART_UASR_PARITY_TYPE_MASK                  ((uint32)0x000000c0U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_3 ((uint32)3U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_2 ((uint32)2U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_1 ((uint32)1U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_0 ((uint32)0U)

#define UART_UASR_RESERVED_24_SHIFT ((uint32)8U)
#define UART_UASR_RESERVED_24_MASK  ((uint32)0xffffff00U)

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

/**
** \name Values related to Register Mode Configuration.
* @{
*/

/** \brief Values to be used while switching between register
 * configuration modes. */
#define UART_REG_CONFIG_MODE_A    ((uint32)0x0080)
#define UART_REG_CONFIG_MODE_B    ((uint32)0x00BF)
#define UART_REG_OPERATIONAL_MODE ((uint32)0x007F)
/** @} */

/**
 *  \anchor UART_OperMode
 *  \name UART Operational Modes additional to configurable ones in IP
 *
 *  Note: The values should not be changed since it represents the
 *        actual register configuration values used to configure the UART
 *  @{
 */
#define UART_OPER_MODE_SIR      (1U)
#define UART_OPER_MODE_MIR      (4U)
#define UART_OPER_MODE_FIR      (5U)
#define UART_OPER_MODE_CIR      (6U)
#define UART_OPER_MODE_DISABLED (7U)
/** @} */

/** \brief Count Value to check error in the recieved byte  */
#define UART_ERROR_COUNT (0x00FFFFFFU)

/** \brief A Data Movement Architecture (DMA) handle that is used by UART for DMA mode */
typedef void *CddUart_DmaHandle;

/* ========================================================================== */
/*                           Structure Declarations                           */
/* ========================================================================== */

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
    /*
     * SOC configuration
     */
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
    uint32 readReturnMode;
    /**< Receive return mode  Refer \ref UART_ReadReturnMode */
    uint32 hwFlowControl;
    /** < Enable HW Flow Control */
    uint32 hwFlowControlThr;
    /**< Hardware flow Control threshold, greater than or equal to the
         RX FIFO trigger level \ref UART_RxTrigLvl */
    /*
     * Driver configuration
     */
    uint32 transferMode;
    /**< Transfer mode \ref UART_ConfigMode */
    uint32 intrNum;
    /**< Peripheral interrupt number */
    uint8  intrPriority;
    /**< Interrupt priority */

    /*
     * UART configuration
     */
    uint32 operMode;
    /**< Refer \ref UART_OperMode for valid values */
    uint32 rxTrigLvl;
    /**< Refer \ref UART_RxTrigLvl for valid values */
    uint32 txTrigLvl;
    /**< Refer \ref UART_TxTrigLvl for valid values */
    uint32 rxEvtNum;
    /**< DMA Event number used for UART Rx */
    uint32 txEvtNum;
    /**< DMA Event number used for UART Tx */
} CddUart_InitObject, *CddUart_InitHandle;

/**
 *  \brief UART driver object
 */
typedef struct
{
    uint8              channelID;
    /**< UART instance Channel ID */
    uint32             baseAddr;
    /**< Peripheral base address */
    CddUart_InitHandle hUartInit;
    /**< [IN] Initialization parameters of UART instance */

    /*
     * UART write variables
     */
    const void *writeBuf;
    /**< Buffer data pointer */
    uint32      writeCount;
    /**< Number of Chars sent */
    uint32      writeSizeRemaining;
    /**< Chars remaining in buffer */

    /*
     * UART receive variables
     */
    void  *readBuf;
    /**< Buffer data pointer */
    uint32 readCount;
    /**< Number of Chars read */
    uint32 readSizeRemaining;
    /**< Chars remaining in buffer */
    uint32 rxTimeoutCnt;
    /**< Receive timeout error count */
    uint32 readErrorCnt;
    /**< Line status error count */

    /*
     * UART Transaction status variables
     */
    CddUart_Transaction *readTrans;
    /**< Pointer to the current read transaction */
    CddUart_Transaction *writeTrans;
    /**< Pointer to the current write transaction */
    uint32               currIntMask;

    /*
     *  UART DMA Configuration Handle IDs
     */
    uint32 dmaTxHandleId;
    /**< DMA Transfer Handle ID */
    uint32 dmaRxHandleId;
    /**< DMA Receive Handle ID */

    /*
     * State variables
     */
    uint32 state;
    /**< Flag to indicate whether the instance is opened already */
    uint32 readTransferMutex;
    /**< Read Transfer Sync Sempahore - to signal transfer completion */
    uint32 writeTransferMutex;
    /**< Write Transfer Sync Sempahore - to signal transfer completion */

    void *args;
    /**< Pointer to be used by application to store miscellaneous data.*/
} CddUart_Object, *CddUart_Handle;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Driver internal functions */
void                 UART_configInstance(CddUart_Handle handle);
static sint32        UART_checkTransaction(CddUart_Transaction *trans);
boolean              UART_writeCancelNoCB(CddUart_Handle handle);
boolean              UART_writeCancelDmaNoCB(CddUart_Handle handle);
sint32               UART_writePolling(CddUart_Handle handle, CddUart_Transaction *trans);
sint32               UART_writeInterrupt(CddUart_Handle handle);
boolean              UART_readCancelNoCB(CddUart_Handle handle);
boolean              UART_readCancelDmaNoCB(CddUart_Handle handle);
uint32               UART_spaceAvail(uint32 baseAddr);
uint32               UART_operatingModeSelect(uint32 baseAddr, uint32 modeFlag);
static inline uint32 UART_writeData(CddUart_Handle handle, uint32 size);
static inline uint32 UART_readData(CddUart_Handle handle, uint32 size);
uint8                UART_readByte(CddUart_Handle handle);
uint8                UART_fifoCharGet(uint32 baseAddr);
uint32               UART_divisorValCompute(uint32 moduleClk, uint32 baudRate, uint32 modeFlag);
uint32               UART_regConfigModeEnable(uint32 baseAddr, uint32 modeFlag);
uint32               UART_IsTxRxFifoEmpty(uint32 baseAddr);

/* ========================================================================== */
/*                       Advanced Function Declarations                       */
/* ========================================================================== */

/**
 *  \brief  Function to enable loopback mode. This function is for internal use.
 *          Not recommended for customers to use.
 *
 *  \param  baseAddr    Memory address of the UART instance being used.
 *
 *  \sa     #UART_open
 */
void UART_enableLoopbackMode(uint32 baseAddr);

/**
 *  \brief  Function to disable loopback mode. This function is for internal use.
 *          Not recommended for customers to use.
 *
 *  \param  baseAddr    Memory address of the UART instance being used.
 *
 *  \sa     #UART_open
 */
void UART_disableLoopbackMode(uint32 baseAddr);

/**
 * \brief   This API writes a byte to the Transmitter FIFO without checking for
 *          the emptiness of the Transmitter FIFO or the Transmitter Shift
 *          Register(TSR).
 *
 * \param   baseAddr    Memory address of the UART instance being used.
 * \param   byteTx      The byte to be transmitted by the UART.
 *
 * \note    Unlike the APIs UARTCharPut() or UARTCharPutNonBlocking(), this
 *          API does not check for the emptiness of the TX FIFO or TSR. This
 *          API is ideal for use in FIFO mode of operation where the 64-byte
 *          TX FIFO has to be written with successive bytes. If transmit
 *          interrupt is enabled, it provides a mechanism to control the
 *          writes to the TX FIFO.
 *
 * \sa      #UART_open
 */
static inline void UART_putChar(uint32 baseAddr, uint8 byteTx);

/**
 * \brief    This API reads a byte from the Receiver Buffer Register
 *           (RBR). It checks once if any character is ready to be read.
 *
 * \param    baseAddr     Memory address of the UART instance being used.
 *
 * \param    pChar        Pointer to the byte variable which saves the byte
 *                        read from RBR if there is any char ready to be read
 *
 * \return   If the RX FIFO(or RHR) was found to have atleast one byte of
 *           data, then this API returns TRUE. Else it returns FALSE.
 *
 * \sa      #UART_open
 */
static inline uint32 UART_getChar(uint32 baseAddr, uint8 *pChar);

/**
 * \brief   This API enables the specified interrupts in the UART mode of
 *          operation.
 *
 * \param   baseAddr   Memory address of the UART instance being used.
 * \param   intrFlag   Bit mask value of the bits corresponding to Interrupt
 *                    Enable Register(IER). This specifies the UART interrupts
 *                    to be enabled.
 *
 *  'intrFlag' can take one or a combination of the following macros:
 *  - UART_INTR_CTS - to enable Clear-To-Send interrupt,
 *  - UART_INTR_RTS - to enable Request-To-Send interrupt,
 *  - UART_INTR_XOFF - to enable XOFF interrupt,
 *  - UART_INTR_SLEEPMODE - to enable Sleep Mode,
 *  - UART_INTR_MODEM_STAT - to enable Modem Status interrupt,
 *  - UART_INTR_LINE_STAT - to enable Line Status interrupt,
 *  - UART_INTR_THR - to enable Transmitter Holding Register Empty interrupt,
 *  - UART_INTR_RHR_CTI - to enable Receiver Data available interrupt and
 *                       Character timeout indication interrupt.
 *
 * \note    This API modifies the contents of UART Interrupt Enable Register
 *          (IER). Modifying the bits IER[7:4] requires that EFR[4] be set.
 *          This API does the needful before it accesses IER.
 *          Moreover, this API should be called when UART is operating in
 *          UART 16x Mode, UART 13x Mode or UART 16x Auto-baud mode.\n
 *
 * \sa      #UART_open
 */
static inline void UART_intrEnable(uint32 baseAddr, uint32 intrFlag);

/**
 * \brief   This API disables the specified interrupts in the UART mode of
 *          operation.
 *
 * \param   baseAddr   Memory address of the UART instance being used.
 * \param   intrFlag   Bit mask value of the bits corresponding to Interrupt
 *                    Enable Register(IER). This specifies the UART interrupts
 *                    to be disabled.
 *
 *  'intrFlag' can take one or a combination of the following macros:
 *  - UART_INTR_CTS - to disable Clear-To-Send interrupt,
 *  - UART_INTR_RTS - to disable Request-To-Send interrupt,
 *  - UART_INTR_XOFF - to disable XOFF interrupt,
 *  - UART_INTR_SLEEPMODE - to disable Sleep Mode,
 *  - UART_INTR_MODEM_STAT - to disable Modem Status interrupt,
 *  - UART_INTR_LINE_STAT - to disable Line Status interrupt,
 *  - UART_INTR_THR - to disable Transmitter Holding Register Empty interrupt,
 *  - UART_INTR_RHR_CTI - to disable Receiver Data available interrupt and
 *                       Character timeout indication interrupt.
 *
 * \note  The note section of UART_intrEnable() also applies to this API.
 *
 * \sa      #UART_open
 */
static inline void UART_intrDisable(uint32 baseAddr, uint32 intrFlag);

/**
 * \brief   This API disables the specified interrupts in the UART mode of
 *          operation  for IER2
 *
 * \param   baseAddr  Memory address of the UART instance being used.
 * \param   intrFlag   Bit mask value of the bits corresponding to Interrupt
 *                    Enable Register(IER2). This specifies the UART interrupts
 *                    to be disabled.
 *
 *  'intrFlag' can take one or a combination of the following macros:
 *  - UART_INTR2_RX_EMPTY - to enable receive FIFO empty interrupt
 *  - UART_INTR2_TX_EMPTY - to enable TX FIFO empty interrupt
 *
 * \note    This API modifies the contents of UART Interrupt Enable Register 2
 *          (IER2).
 *
 * \sa      #UART_open
 */
static inline void UART_intr2Disable(uint32 baseAddr, uint32 intrFlag);

/**
 * \brief  This API determines the UART Interrupt Status.
 *
 * \param  baseAddr   Memory address of the UART instance being used.
 *
 *
 * \return This returns one or a combination of the following macros:
 *         - UART_INTID_MODEM_STAT - indicating the occurence of a Modem Status
 *           interrupt\n
 *         - UART_INTID_TX_THRES_REACH - indicating that the TX FIFO Threshold
 *           number of bytes can be written to the TX FIFO.
 *         - UART_INTID_RX_THRES_REACH - indicating that the RX FIFO has
 *           reached its programmed Trigger Level\n
 *         - UART_INTID_RX_LINE_STAT_ERROR - indicating the occurence of a
 *           receiver Line Status error\n
 *         - UART_INTID_CHAR_TIMEOUT - indicating the occurence of a Receiver
 *           Timeout\n
 *         - UART_INTID_XOFF_SPEC_CHAR_DETECT - indicating the detection of XOFF
 *           or a Special character\n
 *         - UART_INTID_MODEM_SIG_STATE_CHANGE - indicating that atleast one of
 *           the Modem signals among CTSn, RTSn and DSRn have changed states
 *           from active(low) to inactive(high)\n
 *
 * \sa      #UART_open
 */
static inline uint32 UART_getIntrIdentityStatus(uint32 baseAddr);

/**
 * \brief  This API checks if the RX FIFO (or RHR in non-FIFO mode) has atleast
 *         one byte of data to be read.
 *
 * \param  baseAddr    Memory address of the UART instance being used.
 *
 *
 * \return  TRUE - if there is atleast one data byte present in the RX FIFO
 *          (or RHR in non-FIFO mode)\n
 *          FALSE - if there are no data bytes present in the RX FIFO(or RHR
 *           in non-FIFO mode)\n
 *
 * \sa      #UART_open
 */
uint32 UART_checkCharsAvailInFifo(uint32 baseAddr);

/**
 * \brief  This API reads the line status register value.
 *
 * \param  baseAddr     Memory address of the UART instance being used.
 *
 *
 * \return This returns the line status register value.
 *
 * \sa      #UART_open
 */
uint32 UART_readLineStatus(uint32 baseAddr);

/* ========================================================================== */
/*                             Function Declarations                          */
/* ========================================================================== */

/**
 *  \brief  Function to flush a TX FIFO of peripheral specified by the UART handle
 *
 *  \param  hUart      Handle to the UART instance used
 *
 *  \return #MCAL_SystemP_SUCCESS if successful; else error on failure
 */
sint32 Uart_Cdd_flushTxFifo(CddUart_Handle hUart);

/**
 *  \brief  Function to check various error conditions in uart
 *
 *  \param  hUart       Handle to the UART instance used
 *
 *  \return #MCAL_SystemP_SUCCESS if successful; else error on failure
 */
void UART_procLineStatusErr(CddUart_Handle hUart);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef UART_V0_LLD_H_ */

/** @} */
