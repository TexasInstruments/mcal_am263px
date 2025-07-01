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
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif

#if (STD_ON == PORT_SET_PIN_MODE_API)
    /* Set up the pinmux for UART tx */
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);
#endif /*    #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
    vimInit();

    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);

#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_InterruptConfig();
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

boolean Port_TestIntruppt(void)
{
    boolean status = E_NOT_OK;

    /** Enable the intr. for MSS_GPIO_28/RCSS_GPIO_49 pins */
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_PinEnableIntrNotification(28);

#if (STD_ON == PORT_RCSS_INTR_VERIFY)
    Port_PinEnableIntrNotification(49);
#endif /* #if (STD_ON == PORT_RCSS_INTR_VERIFY) */

#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#if (STD_ON == PORT_RCSS_INTR_VERIFY)

    /** RCSS INTR verification **/
    Dio_WriteChannel(11, STD_HIGH);
    AppUtils_printf(
        "[RCSS INTR verification] => Please provide signal from Pin1 of J24 connector to Pin16 of "
        "J7 connector using jumper wire.\n\r\n\r");
    while (Port_App_IntrFlg != PORT_INTR_TEST_PASS)
        ;
    Port_App_IntrFlg = 0;

#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_PinDisableIntrNotification(49);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */
    /** RCSS INTR verification **/

#endif /* #if (STD_ON == PORT_RCSS_INTR_VERIFY) */

    /** MSS INTR verification **/
    AppUtils_printf("[MSS INTR verification] => Press SW2 switch on board to trigger the interrupt\n\r\n\r");
    while (Port_App_IntrFlg != PORT_INTR_TEST_PASS)
        ;

    /** Disable the intr. for MSS_GPIO_28/RCSS_GPIO_49 pins */
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_PinDisableIntrNotification(28);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */
    /** MSS INTR verification **/

    if (Port_App_IntrFlg == PORT_INTR_TEST_PASS)
    {
        status = E_OK;
    }

    return status;
}

#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_InterruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_LEVEL;

    intCfg.priority = VIM_PRIORITY_12;
    intCfg.intNum   = MSS_GIO_INT0; /** MSS High Level Interrupt **/
    intCfg.handler  = Port_MssPinHighLevelIsr;
    vimRegisterInterrupt(&intCfg);

    intCfg.priority = VIM_PRIORITY_13;
    intCfg.intNum   = RCSS_GIO_INT1; /** RCSS Low Level Interrupt **/
    intCfg.handler  = Port_RcssPinLowLevelIsr;
    vimRegisterInterrupt(&intCfg);

    intCfg.priority = VIM_PRIORITY_14;
    intCfg.intNum   = MSS_GIO_INT1; /** MSS Low Level Interrupt **/
    intCfg.handler  = Port_MssPinLowLevelIsr;
    vimRegisterInterrupt(&intCfg);

    intCfg.priority = VIM_PRIORITY_15;
    intCfg.intNum   = RCSS_GIO_INT0; /** RCSS High Level Interrupt **/
    intCfg.handler  = Port_RcssPinHighLevelIsr;
    vimRegisterInterrupt(&intCfg);
}

void Port_IsrNotification0(uint8 PinNum, Port_LevelTrig Level)
{
    AppUtils_printf("Interrupt -- PinNum : %d Level : %d\n\r\n\r", PinNum, Level);

    Port_App_IntrFlg = PORT_INTR_TEST_PASS;
}

void Port_IsrNotification1(uint8 PinNum, Port_LevelTrig Level)
{
    AppUtils_printf("Interrupt -- PinNum : %d Level : %d\n\r\n\r", PinNum, Level);

    Port_App_IntrFlg = PORT_INTR_TEST_PASS;
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
