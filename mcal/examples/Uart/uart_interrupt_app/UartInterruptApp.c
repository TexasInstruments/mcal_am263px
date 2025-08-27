/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     UartInterruptApp.c
 *
 *  \brief    UART Interrupt App example file
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
#include "UartInterruptApp_Startup.h"
#include "Cdd_Uart_Irq.h"
#include "CacheP.h"
#if (STD_ON == CDD_UART_DMA_ENABLE)
#include "Cdd_Dma_Cfg.h"
#include "Cdd_Dma.h"
#endif
#include "UartInterruptApp.h"
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
    Mcu_Init(&McuModuleConfiguration);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    /* Interrupt Configuration (Registering Interrupt to R5 core, ISR) */
    Cdd_Uart_InterruptConfiguration();

#if (STD_ON == CDD_UART_DMA_ENABLE)
    Cdd_Dma_Init(NULL_PTR); /* DMA Initialization */
#endif

    Cdd_Uart_Init(&CddUartDriver_0); /* UART CDD Initialization */

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
