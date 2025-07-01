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
 *  \file     EthApp_Startup.c
 *
 *  \brief    This file contains the Eth platform intialisations which required for example
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/

/* Include Files */
#include "Eth.h"
#include "EthTrcv.h"
#include "Eth_Irq.h"
#include "EthApp_Startup.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "hw_types.h"
#include "sys_vim.h"

static void EthApp_PlatformInit();
static void EthApp_InterruptConfig(void);

static void EthApp_PlatformInit()
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

    /* Init Eth clock follow mcu_plus_sdk */
    SOC_rcmConfigEthMacIf();

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT))*/

#if (STD_ON == PORT_SET_PIN_MODE_API)
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;
    /*Set up the pinmux for UART tx*/
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);
    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);
#endif /*    #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);

    return;
}

/* =========================Function separator========================= */

static void EthApp_InterruptConfig(void)
{
    Vim_IntCfg Eth_IntCfg;

    vimInit();

    Eth_IntCfg.map  = VIM_INTTYPE_IRQ;
    Eth_IntCfg.type = VIM_INTTRIGTYPE_PULSE;

#if (STD_ON == ETH_ENABLE_RX_INTERRUPT)
    Eth_IntCfg.intNum   = MSS_CPSW_TH_INT;
    Eth_IntCfg.handler  = Eth_RxIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /* (STD_ON == ETH_ENABLE_RX_INTERRUPT)*/

#if (STD_ON == ETH_ENABLE_TX_INTERRUPT)
    Eth_IntCfg.intNum   = MSS_CPSW_FH_INT;
    Eth_IntCfg.handler  = Eth_TxIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /*(STD_ON == ETH_ENABLE_TX_INTERRUPT)*/

#if (STD_ON == ETH_ENABLE_RX_INTERRUPT)
    Eth_IntCfg.intNum   = MSS_CPSW_TH_TRSH_INT;
    Eth_IntCfg.handler  = Eth_RxThreshIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /*(STD_ON == ETH_ENABLE_RX_INTERRUPT)*/

#if (ETH_USR_MDIO_INTERRUPT == STD_ON) || (ETH_STATS_INTERRUPT == STD_ON)
    Eth_IntCfg.intNum   = MSS_CPSW_MISC_INT;
    Eth_IntCfg.handler  = Eth_MiscIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /* (ETH_USR_MDIO_INTERRUPT == STD_ON) ||(ETH_STATS_INTERRUPT == STD_ON) */
}

/* =========================Function separator========================= */

void EthApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    EthApp_PlatformInit();
    AppUtils_TimerInit();
    EthApp_InterruptConfig();
}

/* =========================Function separator========================= */

void EthApp_TrcvInit()
{
#if (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)
    AppUtils_ethTrcvInit((EthTrcv_ConfigType *)NULL_PTR);
#else
    AppUtils_ethTrcvInit(&EthTrcvConfigSet_EthTrcvConfig_0);
#endif /* (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)*/
}

#ifdef __cplusplus
}
#endif
