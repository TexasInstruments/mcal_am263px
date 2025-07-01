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
 *  \file     QSpiFlashApp.c
 *
 *  \brief    This file contains the SPI test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "QSpiFlashApp_Startup.h"
#include "QSpiFlashApp.h"

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void QSpiFlashApp_platformInit(void);
static void QSpiFlashApp_interruptConfig(void);
static void QSpiFlashAppDma_interruptConfig(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern uint8 gQspiApp_srcBuff1[QSPI_APP_FLASH_BLOCK_SIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration_0;
#endif
#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration;
#endif
#define MCAL_CSL_MSS_INTR_MSS_TPCC_A_INTAGG 67

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void QSpiFlashApp_Startup(void)
{
    QSpiFlashApp_platformInit();
    QSpiFlashAppDma_interruptConfig();
    QSpiFlashApp_interruptConfig();
}

static void QSpiFlashApp_platformInit(void)
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

    Mcu_InitRamSection(0);

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
}

static void QSpiFlashApp_interruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.priority = VIM_PRIORITY_6;
    intCfg.intNum   = MSS_QSPI_INT;
    intCfg.handler  = Spi_IrqUnit0TxRxQspi;
    vimRegisterInterrupt(&intCfg);
    return;
}

static void QSpiFlashAppDma_interruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_LEVEL;
    intCfg.priority = VIM_PRIORITY_7;
    intCfg.intNum   = MCAL_CSL_MSS_INTR_MSS_TPCC_A_INTAGG;
    intCfg.handler  = &CDD_EDMA_lld_transferCompletionMasterIsrFxn;
    vimRegisterInterrupt(&intCfg);
    return;
}
