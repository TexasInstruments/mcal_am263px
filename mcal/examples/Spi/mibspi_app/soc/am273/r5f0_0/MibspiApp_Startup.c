/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     mcspiApp_Startup.c
 *
 *  \brief    This file contains the McSPI test example Hw Dependent functions.
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "MibspiApp.h"
#include "MibspiApp_Startup.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "SchM_Port.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                  Macros                                                    */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof((x)[0]))

/* ========================================================================== */
/*                  Function Declarations                                     */
/* ========================================================================== */
static void SpiApp_platformInit(void);

uint32 frc;
uint32 Performance_Result[30];
#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration;
#endif
extern uint32 gMibspiRxBuffer[SPI_MAX_CHANNELS][RX_TX_BUF_SIZE_WORD];

void MibspiApp_Startup()
{
    AppUtils_defaultInit();
    SpiApp_platformInit();
}

static void SpiApp_platformInit(void)
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif

    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;

#if (STD_ON == PORT_SET_PIN_MODE_API)
    /* Set up the pinmux for UART tx */
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
#endif

#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);
#endif

    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);

    return;
}

void SpiApp_interruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_LEVEL;

    vimInit();
    intCfg.priority = VIM_PRIORITY_6;
    intCfg.intNum   = MSS_SPIA_INT1;
    intCfg.handler  = Spi_IrqUnit0TxRx;
    vimRegisterInterrupt(&intCfg);

    intCfg.priority = VIM_PRIORITY_7;
    intCfg.intNum   = MSS_SPIB_INT1;
    intCfg.handler  = Spi_IrqUnit1TxRx;
    vimRegisterInterrupt(&intCfg);

    intCfg.priority = VIM_PRIORITY_6;
    intCfg.intNum   = RCSS_SPIA_INT1;
    intCfg.handler  = RCSS_Spi_IrqUnit0TxRx;
    vimRegisterInterrupt(&intCfg);

    intCfg.priority = VIM_PRIORITY_7;
    intCfg.intNum   = RCSS_SPIB_INT1;
    intCfg.handler  = RCSS_Spi_IrqUnit1TxRx;
    vimRegisterInterrupt(&intCfg);

    return;
}

#ifdef __cplusplus
}
#endif
