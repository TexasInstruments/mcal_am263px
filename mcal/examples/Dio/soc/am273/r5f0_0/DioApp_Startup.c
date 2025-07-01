/* ======================================================================
 *   Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     DioApp_Startup.c
 *
 *  \brief    This file contains the DIO test example Hw Dependent functions.
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "DioApp_Startup.h"

static void Dio_Example_PlatformInit();

#ifdef __cplusplus
extern "C" {
#endif

void DioApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();
    Dio_Example_PlatformInit();
}

static void Dio_Example_PlatformInit()
{
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif
    Port_Init(&PortConfigSet_0);

    /* Set up the pinmux for UART tx */
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);

    vimInit();

    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);
}

#ifdef __cplusplus
}
#endif
