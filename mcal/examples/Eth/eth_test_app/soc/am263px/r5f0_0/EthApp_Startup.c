/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
#ifdef AM263PX_C_PACKAGE
    HW_WR_REG32(0x52501014, count);  /* Count */
    HW_WR_REG32(0x52501024, 0x4620); /* Start Write */
    HW_WR_REG32(0x52501024, 0x6620); /* Start Write */
    AppUtils_delay(10);
    HW_WR_REG32(0x52501020, cmd); /* Data Command */
    while (temp == 0)
    {
        temp = HW_RD_REG32(0x52501008);
        temp = (temp >> 4) & 0x01;
    }
    HW_WR_REG32(0x52501020, reg);    /* Data */
    HW_WR_REG32(0x52501024, 0x4E20); /* Stop I2C */
#else
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
#endif /* AM263PX_C_PACKAGE */
}

/* =========================Function separator========================= */

static void I2C_Read(uint32 cmd, uint32 *reg)
{
    uint32 count;
    count = 1;
#ifdef AM263PX_C_PACKAGE
    HW_WR_REG32(0x52501014, count);  /* Count */
    HW_WR_REG32(0x52501024, 0x4620); /* Start Write */
    HW_WR_REG32(0x52501024, 0x6620); /* Start Write */
    AppUtils_delay(10);
    HW_WR_REG32(0x52501020, cmd); /* Data Command */
    count = 1;
    HW_WR_REG32(0x52501014, count);  /* Count */
    HW_WR_REG32(0x52501024, 0x4420); /* Start Read */
    HW_WR_REG32(0x52501024, 0x6420); /* Start Read */
    AppUtils_delay(10);
    *reg = HW_RD_REG32(0x52501018);  /* Read */
    HW_WR_REG32(0x52501024, 0x4A20); /* Stop I2C */
#else
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
#endif /* AM263PX_C_PACKAGE */
}

/* =========================Function separator========================= */

void I2C()
{
    uint32 reg;

#ifdef AM263PX_C_PACKAGE
    HW_WR_REG32(0x52501024, 0x0); /* Reset */
    AppUtils_delay(10);
    HW_WR_REG32(0x52501000, 0x10); /* Own Address */
    AppUtils_delay(10);
    HW_WR_REG32(0x5250100C, 0x09); /* Clock Low */
    AppUtils_delay(10);
    HW_WR_REG32(0x52501010, 0x09); /* Clock High */
    AppUtils_delay(10);
    HW_WR_REG32(0x52501030, 0x07); /* PreScalar */
    AppUtils_delay(10);
    HW_WR_REG32(0x5250101C, 0x20); /* Slave Address */
    AppUtils_delay(10);

    // RGMII1_ICSSM_MUX_SEL_GPIO105 (D17) = 0 by default

    /**
     * P02: CPSW RGMI1/ICSSM_MII1_RST_EN = 1
     * P03: CPSW RGMI2/ICSSM_MII0_RST_EN = 1
     * P04: AM263P_LED_DRIVER_EN = 0
     * P05: AM263P_LED_EN = 1
     * P07: AM263P_PRU_MUX_SEL = 0
     */
    I2C_Read(TCA6416_PORT0_INPUT_REG, &reg);
    reg |= (TCA6416_P(2) | TCA6416_P(3) | TCA6416_P(5));
    reg &= ~(TCA6416_P(4) | TCA6416_P(7));
    I2C_Write(TCA6416_PORT0_OUTPUT_REG, reg);

    /**
     * P15: AM263P_PRU/BP_MUX_EN = 1
     */
    I2C_Read(TCA6416_PORT1_INPUT_REG, &reg);
    reg |= (TCA6416_P(5));
    I2C_Write(TCA6416_PORT1_OUTPUT_REG, reg);

    /**
     * Setting P02-P05, P07 as outputs
     */
    I2C_Read(TCA6416_PORT0_DIR_REG, &reg);
    reg &= ~(TCA6416_P(2) | TCA6416_P(3) | TCA6416_P(4) | TCA6416_P(5) | TCA6416_P(7));
    I2C_Write(TCA6416_PORT0_DIR_REG, reg);

    /**
     * Setting P15 as output
     */
    I2C_Read(TCA6416_PORT1_DIR_REG, &reg);
    reg &= ~(TCA6416_P(5));
    I2C_Write(TCA6416_PORT1_DIR_REG, reg);
#else
    HW_WR_REG32(0x52502024, 0x0); /* Reset */
    AppUtils_delay(10);
    HW_WR_REG32(0x52502000, 0x10); /* Own Address */
    AppUtils_delay(10);
    HW_WR_REG32(0x5250200C, 0x09); /* Clock Low */
    AppUtils_delay(10);
    HW_WR_REG32(0x52502010, 0x09); /* Clock High */
    AppUtils_delay(10);
    HW_WR_REG32(0x52502030, 0x07); /* PreScalar */
    AppUtils_delay(10);

#if (ETH_BOARD_REVISION_E1 == 1u)
    HW_WR_REG32(0x5250201C, 0x20); /* Slave Address */
    AppUtils_delay(10);

    I2C_Read(TCA6416_PORT0_INPUT_REG, &reg);
    reg &= ~TCA6416_P(2);
    I2C_Write(TCA6416_PORT0_OUTPUT_REG, reg);

    I2C_Read(TCA6416_PORT0_INPUT_REG, &reg);
    reg &= ~TCA6416_P(3);
    I2C_Write(TCA6416_PORT0_OUTPUT_REG, reg);

    /**
     * P15: AM263P_PRU/BP_MUX_EN = 1
     */
    I2C_Read(TCA6416_PORT1_INPUT_REG, &reg);
    reg |= (TCA6416_P(4));
    I2C_Write(TCA6416_PORT1_OUTPUT_REG, reg);

    /**
     * Setting P02-P05, P07 as outputs
     */
    I2C_Read(TCA6416_PORT0_DIR_REG, &reg);
    reg &= ~(TCA6416_P(2) | TCA6416_P(3));
    I2C_Write(TCA6416_PORT0_DIR_REG, reg);

    /**
     * Setting P15 as output
     */
    I2C_Read(TCA6416_PORT1_DIR_REG, &reg);
    reg &= ~(TCA6416_P(4));
    I2C_Write(TCA6416_PORT1_DIR_REG, reg);
#else
    HW_WR_REG32(0x5250201C, 0x22); /* Slave Address */
    AppUtils_delay(10);

    /**
     * P02: ICSSM1_MUX_SEL = 0
     * P03: ICSSM2_MUX_SEL = 0
     */
    I2C_Read(TCA6424_PORT0_INPUT_REG, &reg);
    reg &= ~(TCA6424_P(2) | TCA6424_P(3));
    I2C_Write(TCA6424_PORT0_OUTPUT_REG, reg);

    /**
     * P22: MDIO/MDC_MUX_SEL1 = 1
     * P23: MDIO/MDC_MUX_SEL2 = 1
     * P24: ICSSM0_MUX_SEL = 0
     */
    I2C_Read(TCA6424_PORT2_INPUT_REG, &reg);
    reg |= (TCA6424_P(2) | TCA6424_P(3));
    reg &= ~(TCA6424_P(4));
    I2C_Write(TCA6424_PORT2_OUTPUT_REG, reg);

    /**
     * Setting P02 and P03 as outputs
     */
    I2C_Read(TCA6424_PORT0_DIR_REG, &reg);
    reg &= ~(TCA6424_P(2) | TCA6424_P(3));
    I2C_Write(TCA6424_PORT0_DIR_REG, reg);

    /**
     * Setting P22-P24 as outputs
     */
    I2C_Read(TCA6424_PORT2_DIR_REG, &reg);
    reg &= ~(TCA6424_P(2) | TCA6424_P(3) | TCA6424_P(4));
    I2C_Write(TCA6424_PORT2_DIR_REG, reg);
#endif
#endif /* AM263PX_C_PACKAGE */
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
    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, EthTrcv_Config.pController[0]->phyAddr);
    AppUtils_ethTrcvInit((EthTrcv_ConfigType *)NULL_PTR, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#else
    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, EthTrcv_Config.pController[0]->phyAddr);
    AppUtils_ethTrcvInit(&EthTrcv_Config, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#endif /* (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)*/
}
