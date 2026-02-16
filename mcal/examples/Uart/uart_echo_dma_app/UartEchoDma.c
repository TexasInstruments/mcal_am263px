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
 *  \file     UartEchoDma.c
 *
 *  \brief    UART Echo DMA App example file
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "assert.h"
#include "string.h"
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "app_utils.h"
#include "UartEchoDma_Startup.h"
#include "Cdd_Uart_Irq.h"
#include "CacheP.h"
#if (STD_ON == CDD_UART_DMA_ENABLE)
#include "Cdd_Dma_Cfg.h"
#include "Cdd_Dma.h"
#endif
#include "UartEchoDma.h"
#include "sys_common.h"

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

CddUartDataBufferType CddUart_Buffer[CDD_UART_APP_BUFFERSIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));
CddUartDataBufferType CddUart_ReceiveBuffer[CDD_UART_APP_RECEIVE_BUFFERSIZE]
    __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));
volatile uint32 Uart_writeDone = 0U, Uart_readDone = 0U;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Entry point of example */
sint32 main(void)
{
    Apps_switch_to_system_mode();

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&Mcu_Config);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&Port_Config);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    /* Interrupt Configuration (Registering Interrupt to R5 core, ISR) */
    Cdd_Uart_InterruptConfiguration();

#if (STD_ON == CDD_UART_DMA_ENABLE)
    Cdd_Dma_Init(NULL_PTR); /* DMA Initialization */
#endif

    Cdd_Uart_Init(&Cdd_Uart_Config); /* UART CDD Initialization */

    /* Channel select and buffer pointers for read-write */
    void *writeBuffer = &CddUart_Buffer;
#if (STD_ON == CDD_UART_WRITE_API) || (STD_ON == CDD_UART_READ_API)
    uint8 channel = CddUartConf_CddUartChannelConfiguration_CddUartChannel_0; /* Channel Index of the
                                                                                 corresponding configuration
                                                                                 from CDD_UART Configurator */
    void *readBuffer = &CddUart_ReceiveBuffer[0];
#endif
    /* Write completion message to the terminal */
    strncpy(writeBuffer, "\rThis is Uart Echo Test in DMA Mode\r\n", CDD_UART_APP_BUFFERSIZE);
    uint32 count = strlen(writeBuffer);
    Mcal_CacheP_wb(writeBuffer, count, Mcal_CacheP_TYPE_ALL);
#if (STD_ON == CDD_UART_WRITE_API)
    assert(Cdd_Uart_Write(channel, writeBuffer, count, 0U) != (Std_ReturnType)E_NOT_OK);
    while (Uart_writeDone == 0U)
    {
    } /* Wait for write completion */
#endif

    /* Echo prompt to the terminal */
    Uart_writeDone = 0U;
    strncpy(writeBuffer, "Please input 8 characters:\r\n", CDD_UART_APP_BUFFERSIZE);
    count = strlen(writeBuffer);
    Mcal_CacheP_wb(writeBuffer, count, Mcal_CacheP_TYPE_ALL);
#if (STD_ON == CDD_UART_WRITE_API)
    assert(Cdd_Uart_Write(channel, writeBuffer, count, 0U) != (Std_ReturnType)E_NOT_OK);
    while (Uart_writeDone == 0U)
    {
    } /* Wait for write completion */
#endif

    /* Read characters */
    count = CDD_UART_APP_RECEIVE_BUFFERSIZE;
#if (STD_ON == CDD_UART_DMA_ENABLE) || (STD_ON == CDD_UART_READ_API)
    Mcal_CacheP_wbInv(readBuffer, count, Mcal_CacheP_TYPE_ALL);
    assert(Cdd_Uart_Read(channel, readBuffer, count, 0U) != (Std_ReturnType)E_NOT_OK);
    while (Uart_readDone == 0U)
    {
    } /* Wait for read completion */
#endif

    /* Echo characters read */
    Uart_writeDone = 0U;
#if (STD_ON == CDD_UART_DMA_ENABLE) || (STD_ON == CDD_UART_WRITE_API)
    Mcal_CacheP_wb(readBuffer, count, Mcal_CacheP_TYPE_ALL);
    assert(Cdd_Uart_Write(channel, readBuffer, count, 0U) != (Std_ReturnType)E_NOT_OK);
    while (Uart_writeDone == 0U)
    {
    } /* Wait for write completion */
#endif

    /* Write completion message to the terminal */
    Uart_writeDone = 0U;
    strncpy(writeBuffer, "\r\nEcho has been completed.\r\n\r\nAll tests have passed!\r\n", CDD_UART_APP_BUFFERSIZE);
    count = strlen(writeBuffer);
#if (STD_ON == CDD_UART_DMA_ENABLE)
    Mcal_CacheP_wb(writeBuffer, count, Mcal_CacheP_TYPE_ALL);
#endif
#if (STD_ON == CDD_UART_WRITE_API)
    assert(Cdd_Uart_Write(channel, writeBuffer, count, 0U) != (Std_ReturnType)E_NOT_OK);
    while (Uart_writeDone == 0U)
    {
    } /* Wait for write completion */
#endif

#if (STD_ON == CDD_UART_DEINIT_API)
    /* UART CDD Driver Deinitialization */
    Cdd_Uart_DeInit();
#endif

    /* Deinit DMA, MCU and PORT Dependencies */
#if ((STD_ON == CDD_UART_DMA_ENABLE) && (STD_ON == CDD_DMA_DEINIT_API))
    Cdd_Dma_DeInit();
#endif
    Mcu_DeInit();
    Port_DeInit();

    return 0U;
}

/* Callback functions */
void CddUart_CallbackReadNotify()
{
    Uart_readDone = 1U;
}
void CddUart_CallbackWriteNotify()
{
    Uart_writeDone = 1U;
}
void CddUart_CallbackErrorNotify()
{
}

#if (defined CLANG) || (defined DIAB)
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Cdd_Uart_UART_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Uart_UART_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void App_disable(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void App_restore(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
