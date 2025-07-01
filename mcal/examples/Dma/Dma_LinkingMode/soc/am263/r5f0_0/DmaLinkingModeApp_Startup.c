/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     DmaLinkingModeApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "DmaLinkingModeApp_Startup.h"
#include "Cdd_Dma_Cfg.h"
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                              Macros & Typedefs                             */
/* ========================================================================== */
#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

/*	None	*/

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Cdd_Dma_LinkingModeApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    /*	timer initialization	*/
    AppUtils_TimerInit();
}

void Cdd_Dma_InterruptConfig(void)
{
    vimInit();
    Vim_IntCfg intCfg;
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.priority = VIM_PRIORITY_15;
    intCfg.intNum   = MCAL_MSS_INTR_MSS_TPCC_A_INTAGG;
    intCfg.handler  = &CDD_EDMA_lld_transferCompletionMasterIsrFxn;
    vimRegisterInterrupt(&intCfg);
}

void Uart_Delay(uint32 Delay)
{
    for (Delay = 0; Delay < 5000; Delay++)
    {
        ;
    }
}

void Cdd_Dma_App_PlatformInit(void)
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 uart_tx_pin;
#endif /*(STD_ON == PORT_SET_PIN_MODE_API)*/
#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
    uint16 uart_rx_pin;
#endif /* ((STD_ON == PORT_SET_PIN_MODE_API) || ( STD_ON == PORT_SET_PIN_DIRECTION_API ))*/

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

#if (STD_ON == PORT_SET_PIN_MODE_API)
    uart_tx_pin = 13;
#endif /*(STD_ON == PORT_SET_PIN_MODE_API)*/
#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
    uart_rx_pin = 14;
#endif /* ((STD_ON == PORT_SET_PIN_MODE_API) || ( STD_ON == PORT_SET_PIN_DIRECTION_API ))*/

#if (STD_ON == PORT_SET_PIN_MODE_API)
    /* Set up the pinmux for UART tx */
    Port_SetPinMode(uart_tx_pin, PORT_PIN_MODE_LIN0);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(uart_rx_pin, PORT_PIN_MODE_LIN0);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(uart_rx_pin, PORT_PIN_IN);
#endif /*#if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/

    Enable_Uart();

    /* Delay for UART to settle up */
    Uart_Delay(5000);
}
