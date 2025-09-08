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
 *  \file     GptApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "sys_common.h"
#include "GptApp.h"
#include "GptApp_Startup.h"
#include "sys_vim.h"
#include "Gpt_Irq.h"
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/*	None	*/

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void GptApp_TimeDeinit(void)
{
    AppUtils_TimerDeinit();
}

void GptApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    /*	initializing interrupt	*/
    GptApp_interruptInit();
    /*	timer initialization	*/
    AppUtils_TimerInit();
}

void GptApp_interruptInit(void)
{
    vimInit();
}

void GptApp_platformInit(void)
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 uart_tx_pin, uart_rx_pin;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

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

#if (STD_ON == PORT_SET_PIN_MODE_API)
    uart_tx_pin = 13;
    uart_rx_pin = 14;

    /* Set up the pinmux for UART tx */
    Port_SetPinMode(uart_tx_pin, PORT_PIN_MODE_LIN0);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(uart_rx_pin, PORT_PIN_MODE_LIN0);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(uart_rx_pin, PORT_PIN_IN);
#endif /*    #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
    Enable_Uart();

    return;
}

void GptApp_interruptConfig(uint32 channelId)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;
    if (channelId == 4)
    {
        intCfg.intNum   = RTI1_INT0;
        intCfg.priority = VIM_PRIORITY_14;
        intCfg.handler  = Gpt_Ch4Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 5)
    {
        intCfg.intNum   = RTI1_INT1;
        intCfg.priority = VIM_PRIORITY_15;
        intCfg.handler  = Gpt_Ch5Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 6)
    {
        intCfg.intNum   = RTI1_INT2;
        intCfg.priority = VIM_PRIORITY_13;
        intCfg.handler  = Gpt_Ch6Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 7)
    {
        intCfg.intNum   = RTI1_INT3;
        intCfg.priority = VIM_PRIORITY_12;
        intCfg.handler  = Gpt_Ch7Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 8)
    {
        intCfg.intNum   = RTI2_INT0;
        intCfg.priority = VIM_PRIORITY_11;
        intCfg.handler  = Gpt_Ch8Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 9)
    {
        intCfg.intNum   = RTI2_INT1;
        intCfg.priority = VIM_PRIORITY_10;
        intCfg.handler  = Gpt_Ch9Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 10)
    {
        intCfg.intNum   = RTI2_INT2;
        intCfg.priority = VIM_PRIORITY_9;
        intCfg.handler  = Gpt_Ch10Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 11)
    {
        intCfg.intNum   = RTI2_INT3;
        intCfg.priority = VIM_PRIORITY_8;
        intCfg.handler  = Gpt_Ch11Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 12)
    {
        intCfg.intNum   = RTI3_INT0;
        intCfg.priority = VIM_PRIORITY_7;
        intCfg.handler  = Gpt_Ch12Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 13)
    {
        intCfg.intNum   = RTI3_INT1;
        intCfg.priority = VIM_PRIORITY_6;
        intCfg.handler  = Gpt_Ch13Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 14)
    {
        intCfg.intNum   = RTI3_INT2;
        intCfg.priority = VIM_PRIORITY_5;
        intCfg.handler  = Gpt_Ch14Isr;
        vimRegisterInterrupt(&intCfg);
    }
    else if (channelId == 15)
    {
        intCfg.intNum   = RTI3_INT3;
        intCfg.priority = VIM_PRIORITY_4;
        intCfg.handler  = Gpt_Ch15Isr;
        vimRegisterInterrupt(&intCfg);
    }
}

void GptApp_interruptDisable(uint32 channelId)
{
    switch (channelId)
    {
        case 0:
            vimDisableInterrupt(RTI0_INT0);
            break;
        case 1:
            vimDisableInterrupt(RTI0_INT1);
            break;
        case 2:
            vimDisableInterrupt(RTI0_INT2);
            break;
        case 3:
            vimDisableInterrupt(RTI0_INT3);
            break;
        case 4:
            vimDisableInterrupt(RTI1_INT0);
            break;
        case 5:
            vimDisableInterrupt(RTI1_INT1);
            break;
        case 6:
            vimDisableInterrupt(RTI1_INT2);
            break;
        case 7:
            vimDisableInterrupt(RTI1_INT3);
            break;
        case 8:
            vimDisableInterrupt(RTI2_INT0);
            break;
        case 9:
            vimDisableInterrupt(RTI2_INT1);
            break;
        case 10:
            vimDisableInterrupt(RTI2_INT2);
            break;
        case 11:
            vimDisableInterrupt(RTI2_INT3);
            break;
        case 12:
            vimDisableInterrupt(RTI3_INT0);
            break;
        case 13:
            vimDisableInterrupt(RTI3_INT1);
            break;
        case 14:
            vimDisableInterrupt(RTI3_INT2);
            break;
        case 15:
            vimDisableInterrupt(RTI3_INT3);
            break;
    }
#ifdef GPTTIMER_QT
    AppUtils_delay(2U);
#else
    AppUtils_delay(20U);
#endif
    return;
}
