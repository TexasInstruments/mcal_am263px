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
 *  \file uart_dma.h
 *
 *  \brief UART DMA header file.
 */

#ifndef UART_DMA_H_
#define UART_DMA_H_

#include <Cdd_Uart.h>

#define MCAL_CSL_FMK(PER_REG_FIELD, val) (((val) << PER_REG_FIELD##_SHIFT) & PER_REG_FIELD##_MASK)

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \defgroup UART_DMA_LLD APIs for UART DMA mode
 *  \ingroup DRV_UART_LLD_MODULE
 *
 *  This module contains APIs to program and use DMA drivers available in the SoC with UART.
 *
 *  @{
 */

/**
 * \brief API to open an UART DMA channel
 *
 * This API will open a DMA Channel using the appropriate DMA driver callbacks and the registered
 * via Sysconfig
 *
 * \param hUart    [in] UART Handle
 * \param dmaHandle     [in] UART DMA Handle
 *
 * \return MCAL_SystemP_SUCCESS on success, else failure
 */
sint32 Uart_Cdd_dmaInit(CddUart_Handle hUart);

/**
 * \brief API to close an UART DMA channel
 *
 * \param hUart   [in] UART handle returned from \ref UART_open
 *
 * \return MCAL_SystemP_SUCCESS on success, else failure
 */
sint32 Uart_Cdd_dmaDeInit(CddUart_Handle hUart);

/**
 * \brief API to write data using an UART DMA channel
 *
 * \param obj           [in] Pointer to UART object
 * \param attrs         [in] Pointer to UART attributes
 * \param transaction   [in] Pointer to #CddUart_Transaction. This parameter can't be NULL
 *
 * \return MCAL_SystemP_SUCCESS on success, else failure
 */
sint32 Uart_Cdd_dmaWrite(CddUart_Handle hUart, const CddUart_Transaction *transaction);

/**
 * \brief API to read data using an UART DMA channel
 *
 * \param obj           [in] Pointer to UART object
 * \param attrs         [in] Pointer to UART attributes
 * \param transaction   [in] Pointer to #CddUart_Transaction. This parameter can't be NULL
 *
 * \return MCAL_SystemP_SUCCESS on success, else failure
 */
sint32 Uart_Cdd_dmaRead(CddUart_Handle hUart, const CddUart_Transaction *transaction);

/**
 * \brief UART DMA channel Write ISR Handler
 *
 * \param args          [in] Pointer to #CddUart_Object.
 *
 * \return MCAL_SystemP_SUCCESS on success, else failure
 */
void UART_edmaIsrTx(void *args);

/**
 * \brief UART DMA channel Read ISR Handler
 *
 * \param args          [in] Pointer to #CddUart_Object.
 *
 * \return MCAL_SystemP_SUCCESS on success, else failure
 */
void UART_edmaIsrRx(void *args);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* UART_DMA_H_ */
