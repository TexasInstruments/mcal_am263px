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
#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT))*/

    Enable_Uart();

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
    Eth_IntCfg.intNum   = CPSW_TH_INT;
    Eth_IntCfg.handler  = Eth_RxIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /* (STD_ON == ETH_ENABLE_RX_INTERRUPT)*/

#if (STD_ON == ETH_ENABLE_TX_INTERRUPT)
    Eth_IntCfg.intNum   = CPSW_FH_INT;
    Eth_IntCfg.handler  = Eth_TxIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /*(STD_ON == ETH_ENABLE_TX_INTERRUPT)*/

#if (STD_ON == ETH_ENABLE_RX_INTERRUPT)
    Eth_IntCfg.intNum   = CPSW_TH_THRESH_INT;
    Eth_IntCfg.handler  = Eth_RxThreshIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /*(STD_ON == ETH_ENABLE_RX_INTERRUPT)*/

#if (ETH_USR_MDIO_INTERRUPT == STD_ON) || (ETH_STATS_INTERRUPT == STD_ON)
    Eth_IntCfg.intNum   = CPSW_MISC_INT;
    Eth_IntCfg.handler  = Eth_MiscIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_5;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /* (ETH_USR_MDIO_INTERRUPT == STD_ON) ||(ETH_STATS_INTERRUPT == STD_ON) */
}

/* =========================Function separator========================= */

static void EthApp_UpdateRGMIIMux(void)
{
    uint16 gpio_pin = 150U;
    Port_SetPinMode(gpio_pin, PORT_PIN_MODE_GPIOEF);

    Port_SetPinDirection(gpio_pin, PORT_PIN_OUT);
}

/* =========================Function separator========================= */
void EthApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    EthApp_PlatformInit();
    AppUtils_TimerInit();
    EthApp_InterruptConfig();
    EthApp_UpdateRGMIIMux();
}

/* =========================Function separator========================= */

void EthApp_TrcvInit()
{
    Eth_ConfigType *pEthConfigPtr;
    pEthConfigPtr = &EthConfigSet_EthCtrlConfig_0;
#if (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)
    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, EthTrcvConfigSet_EthTrcvConfig_0.phyAddr);
    AppUtils_ethTrcvInit((EthTrcv_ConfigType *)NULL_PTR);
#else
    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, EthTrcvConfigSet_EthTrcvConfig_0.phyAddr);
    AppUtils_ethTrcvInit(&EthTrcvConfigSet_EthTrcvConfig_0);
#endif /* (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)*/
}

#ifdef __cplusplus
}
#endif
