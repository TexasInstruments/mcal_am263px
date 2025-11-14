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
static void I2C();
static void I2C_Write(uint32 cmd, uint32 reg);
static void I2C_Read(uint32 cmd, uint32 *reg);

static void EthApp_PlatformInit()
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
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT))*/

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
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /* (STD_ON == ETH_ENABLE_RX_INTERRUPT)*/

#if (STD_ON == ETH_ENABLE_TX_INTERRUPT)
    Eth_IntCfg.intNum   = CPSW_FH_INT;
    Eth_IntCfg.handler  = Eth_TxIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /*(STD_ON == ETH_ENABLE_TX_INTERRUPT)*/

#if (STD_ON == ETH_ENABLE_RX_INTERRUPT)
    Eth_IntCfg.intNum   = CPSW_TH_TRSH_INT;
    Eth_IntCfg.handler  = Eth_RxThreshIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /*(STD_ON == ETH_ENABLE_RX_INTERRUPT)*/

#if (ETH_USR_MDIO_INTERRUPT == STD_ON) || (ETH_STATS_INTERRUPT == STD_ON)
    Eth_IntCfg.intNum   = CPSW_MISC_INT;
    Eth_IntCfg.handler  = Eth_MiscIrqHdlr_0;
    Eth_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Eth_IntCfg);
#endif /* (ETH_USR_MDIO_INTERRUPT == STD_ON) ||(ETH_STATS_INTERRUPT == STD_ON) */
}

/* =========================Function separator========================= */

static void I2C_Write(uint32 cmd, uint32 reg)
{
    uint32 count, temp = 0;
    count = 2;
    HW_WR_REG32(0x52502014, count);  /* Count */
    HW_WR_REG32(0x52502024, 0x4620); /* Start Write */
    HW_WR_REG32(0x52502024, 0x6620); /* Start Write */
    AppUtils_delay(10);
    HW_WR_REG32(0x52502020, cmd); /* Data Command */
    while (temp == 0)
    {
        temp = HW_RD_REG32(0x52502008);
        temp = (temp >> 4) & 0x01;
    }
    HW_WR_REG32(0x52502020, reg);    /* Data */
    HW_WR_REG32(0x52502024, 0x4E20); /* Stop I2C */
}

/* =========================Function separator========================= */

static void I2C_Read(uint32 cmd, uint32 *reg)
{
    uint32 count;
    count = 1;
    HW_WR_REG32(0x52502014, count);  /* Count */
    HW_WR_REG32(0x52502024, 0x4620); /* Start Write */
    HW_WR_REG32(0x52502024, 0x6620); /* Start Write */
    AppUtils_delay(10);
    HW_WR_REG32(0x52502020, cmd); /* Data Command */
    count = 1;
    HW_WR_REG32(0x52502014, count);  /* Count */
    HW_WR_REG32(0x52502024, 0x4420); /* Start Read */
    HW_WR_REG32(0x52502024, 0x6420); /* Start Read */
    AppUtils_delay(10);
    *reg = HW_RD_REG32(0x52502018);  /* Read */
    HW_WR_REG32(0x52502024, 0x4A20); /* Stop I2C */
}

/* =========================Function separator========================= */

void I2C()
{
    uint32 reg;
    HW_WR_REG32(0x52502024, 0x0);  /* Reset */
    HW_WR_REG32(0x52502000, 0x10); /* Own Address */
    HW_WR_REG32(0x5250200C, 0x09); /* Clock Low */
    HW_WR_REG32(0x52502010, 0x09); /* Clock High */
    HW_WR_REG32(0x52502030, 0x07); /* PreScalar */
    HW_WR_REG32(0x5250201C, 0x20); /* Slave Address */

    /**
     * Setting P02-P06 as outputs
     */
    I2C_Read(TCA6416_PORT0_DIR_REG, &reg);
    reg &= ~(TCA6416_P(2) | TCA6416_P(3) | TCA6416_P(4) | TCA6416_P(5) | TCA6416_P(6));
    I2C_Write(TCA6416_PORT0_DIR_REG, reg);

    /**
     * Setting P10 and P14 as outputs
     */
    I2C_Read(TCA6416_PORT1_DIR_REG, &reg);
    reg &= ~(TCA6416_P(0) | TCA6416_P(4));
    I2C_Write(TCA6416_PORT1_DIR_REG, reg);

    /**
     * P02: ICSSM1_MUX_SEL = 0
     * P03: ICSSM2_MUX_SEL = 0
     * P04: GPIO_RGMII1_RST = 1
     * P05: GPIO_ICSSM1_RST = 1
     * P06: GPIO_ICSSM2_RST = 1
     */
    I2C_Read(TCA6416_PORT0_INPUT_REG, &reg);
    reg |= (TCA6416_P(4) | TCA6416_P(5) | TCA6416_P(6));
    reg &= ~(TCA6416_P(2) | TCA6416_P(3));
    I2C_Write(TCA6416_PORT0_OUTPUT_REG, reg);

    /**
     * P10: USER_LED1 = 1
     * P14: MDIO/MDC_MUX_SEL = 1
     */
    I2C_Read(TCA6416_PORT1_INPUT_REG, &reg);
    reg |= (TCA6416_P(0) | TCA6416_P(4));
    I2C_Write(TCA6416_PORT1_OUTPUT_REG, reg);
}

/* =========================Function separator========================= */

void EthApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    EthApp_PlatformInit();
    AppUtils_TimerInit();
    EthApp_InterruptConfig();
    I2C();
}

/* =========================Function separator========================= */

void EthApp_TrcvInit()
{
    Eth_ConfigType *pEthConfigPtr;
    pEthConfigPtr = &Eth_Config;

#if (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)
    AppUtils_ethTrcvInit((EthTrcv_ConfigType *)NULL_PTR, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#else
    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, EthTrcv_Config.pController[0]->phyAddr);
    AppUtils_ethTrcvInit(&EthTrcv_Config, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#endif /* (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)*/
}

#ifdef __cplusplus
}
#endif
