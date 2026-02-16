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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "hw_types.h"

#include <kernel/dpl/ClockP.h>

#include "EthTrcv.h"
#include "app_utils.h"
#include "McalUtils.h"
#include "EthApp_Startup.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                         Internal Function Declarations                     */
/* ========================================================================== */
static void I2C_Write(uint32 cmd, uint32 reg);
static void I2C_Read(uint32 cmd, uint32 *reg);
void        I2C();

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static CONST(Mcu_EthConfigType, MCU_PBCFG) Mcu_EthConfiguration[MCU_ETH_PORTS] = {
    [0] = {
        .macNum            = 1U,
        .rmiiClkOutDisable = 1U,
        .idModeEnable      = 0U,
        .macConnectionType = MCU_ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND,
    }};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static void I2C_Write(uint32 cmd, uint32 reg)
{
    uint32 count, temp = 0;
    count = 2;
    HW_WR_REG32(0x52502014, count);  /* Count */
    HW_WR_REG32(0x52502024, 0x4620); /* Start Write */
    HW_WR_REG32(0x52502024, 0x6620); /* Start Write */
    ClockP_usleep(10000U);
    HW_WR_REG32(0x52502020, cmd); /* Data Command */
    while (temp == 0)
    {
        temp = HW_RD_REG32(0x52502008);
        temp = (temp >> 4) & 0x01;
    }
    HW_WR_REG32(0x52502020, reg);    /* Data */
    HW_WR_REG32(0x52502024, 0x4E20); /* Stop I2C */
}

static void I2C_Read(uint32 cmd, uint32 *reg)
{
    uint32 count;
    count = 1;
    HW_WR_REG32(0x52502014, count);  /* Count */
    HW_WR_REG32(0x52502024, 0x4620); /* Start Write */
    HW_WR_REG32(0x52502024, 0x6620); /* Start Write */
    ClockP_usleep(10000U);
    HW_WR_REG32(0x52502020, cmd); /* Data Command */
    count = 1;
    HW_WR_REG32(0x52502014, count);  /* Count */
    HW_WR_REG32(0x52502024, 0x4420); /* Start Read */
    HW_WR_REG32(0x52502024, 0x6420); /* Start Read */
    ClockP_usleep(10000U);
    *reg = HW_RD_REG32(0x52502018);  /* Read */
    HW_WR_REG32(0x52502024, 0x4A20); /* Stop I2C */
}

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

void EthApp_Startup()
{
    I2C();

    Mcu_updateGmiiField(Mcu_EthConfiguration);
}

void EthApp_TrcvInit()
{
    Eth_ConfigType *pEthConfigPtr;
    pEthConfigPtr = &Eth_Config;

    AppUtils_ethAm263xPHYDelayConfig(pEthConfigPtr, 0);

#if (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)
    AppUtils_ethTrcvInit((EthTrcv_ConfigType *)NULL_PTR, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#else
    AppUtils_ethTrcvInit(&EthTrcv_Config, EthTrcvConf_EthTrcvConfig_EthTrcvIdx_0);
#endif /* (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)*/
}

#ifdef __cplusplus
}
#endif
