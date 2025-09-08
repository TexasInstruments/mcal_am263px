/*
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     PortApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PortApp_Startup.h"
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile uint8 Port_App_IntrFlg = 0;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void PortApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
}

void Port_Example_PlatformInit()
{
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

    Enable_Uart();

#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_InterruptConfig();
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

boolean Port_TestIntruppt(void)
{
#if (STD_ON == PORT_TEST_GPIO_INTR)

    boolean status = E_NOT_OK;

#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_PinEnableIntrNotification(PORT_GPIO_CH_21);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

    AppUtils_printf("[GPIO INTR verification] => Press SW1 switch on board to trigger the interrupt \n\r\n\r");

    /* Wait till Interrupt Trigger */
    while (Port_App_IntrFlg != PORT_INTR_TEST_PASS)
        ;

    if (Port_App_IntrFlg == PORT_INTR_TEST_PASS)
    {
        status = E_OK;
    }

#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_PinDisableIntrNotification(PORT_GPIO_CH_21);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

    return status;

#else
    return E_OK;
#endif /* #if (STD_ON == PORT_TEST_GPIO_INTR) */
}

#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_InterruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    /** GPIO Bank1 Interrupt Configuration **/
    intCfg.priority = VIM_PRIORITY_12;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_14;
#if defined(PORT_GPIO_BANK_1_ACTIVE)
    intCfg.handler = Port_Bnk1Isr;
#endif /** #if defined(PORT_GPIO_BANK_1_ACTIVE) **/
    vimRegisterInterrupt(&intCfg);

    /** GPIO Bank2 Interrupt Configuration **/
    intCfg.priority = VIM_PRIORITY_12;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_15;
#if defined(PORT_GPIO_BANK_2_ACTIVE)
    intCfg.handler = Port_Bnk2Isr;
#endif /** #if defined(PORT_GPIO_BANK_2_ACTIVE) **/
    vimRegisterInterrupt(&intCfg);

    /** GPIO Ch1 Interrupt Configuration **/
    intCfg.priority = VIM_PRIORITY_12;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_16;
#if defined(PORT_GPIO_CH_1_ACTIVE)
    intCfg.handler = Port_Ch1Isr;
#endif /** #if defined(PORT_GPIO_CH_1_ACTIVE) **/
    vimRegisterInterrupt(&intCfg);

    /** GPIO Ch2 Interrupt Configuration **/
    intCfg.priority = VIM_PRIORITY_12;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_17;
#if defined(PORT_GPIO_CH_2_ACTIVE)
    intCfg.handler = Port_Ch2Isr;
#endif /** #if defined(PORT_GPIO_CH_2_ACTIVE) **/
    vimRegisterInterrupt(&intCfg);
}

void Port_IsrNotification0(uint8 PortBankNum, uint8 PortBankChNum, Port_EdgeTrig Edge)
{
    AppUtils_printf("Interrupt -- Bank Number : %d GpioChannelNum : %d  Edge : %d\n\r\n\r", PortBankNum, PortBankChNum,
                    Edge);

    if (PortBankNum == PORT_GPIO_BANK_1)
    {
        Port_App_IntrFlg = PORT_INTR_TEST_PASS;
    }
}

#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */
