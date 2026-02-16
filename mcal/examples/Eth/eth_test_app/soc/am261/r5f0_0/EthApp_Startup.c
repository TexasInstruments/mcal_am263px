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
    Eth_IntCfg.intNum   = CPSW_TH_THRESH_INT;
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
    pEthConfigPtr = &Eth_Config;
#if (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)
    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, EthTrcv_Config.pController[0]->phyAddr);
    AppUtils_ethTrcvInit((EthTrcv_ConfigType *)NULL_PTR, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#else
    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, EthTrcv_Config.pController[0]->phyAddr);
    AppUtils_ethTrcvInit(&EthTrcv_Config, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#endif /* (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)*/
}

#ifdef __cplusplus
}
#endif
