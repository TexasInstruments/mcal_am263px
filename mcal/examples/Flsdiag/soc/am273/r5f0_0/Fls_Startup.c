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
 *  \file     Fls_Startup.c
 *
 *  \brief    This file contains the Eth platform intialisations which required for example
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/
#include "Fls_Startup.h"

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void FlsApp_PlatformInit()
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
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
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;
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

    AppUtils_TimerInit();
}
