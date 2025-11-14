/*
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     McalUtils.c
 *
 *  \brief    This file contains porting of required function from other MCAL modules
 *            to help Eth driver work with RTOS
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "hw_types.h"
#include "hw_ctrl_core.h"

#include "Mcu.h"
#include "Eth.h"
#include "EthTrcv.h"
#include "app_utils.h"
#include "EthApp_Startup.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Port mode in MSS_CPSW_CONTROL register */
#define ETH_GMII_SEL_GMII_MODE  (0x0U)
#define ETH_GMII_SEL_RMII_MODE  (0x1U)
#define ETH_GMII_SEL_RGMII_MODE (0x2U)

#define ETH_GMII_RMII_REF_CLK_DISABLE (0x10U)
#define ETH_GMII_ID_MODE_ENABLE       (0x100U)

#define MSS_CPSW_CONTROL_REG_P1_GMII_FIELD_SHIFT (0x0U)
#define MSS_CPSW_CONTROL_REG_P1_GMII_FIELD_MASK  (0x00000117U)

#define MSS_CPSW_CONTROL_REG_P2_GMII_FIELD_SHIFT (0x10U)
#define MSS_CPSW_CONTROL_REG_P2_GMII_FIELD_MASK  (0x01170000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                         Internal Function Declarations                     */
/* ========================================================================== */
static void Mcu_controlModuleUnlockMMR();
static void Mcu_controlModuleLockMMR();

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void Mcu_updateGmiiField(const Mcu_EthConfigType *ethCfg)
{
    uint32 portIdx   = 0U;
    uint32 gmiiField = 0U;

    for (portIdx = 0; portIdx < MCU_ETH_PORTS; portIdx++)
    {
        /* PORT_MODE_SEL */
        switch (ethCfg[portIdx].macConnectionType)
        {
            case MCU_ETH_MAC_CONN_TYPE_MII_10_HALF:
            case MCU_ETH_MAC_CONN_TYPE_MII_10_FULL:
            case MCU_ETH_MAC_CONN_TYPE_MII_100_HALF:
            case MCU_ETH_MAC_CONN_TYPE_MII_100_FULL:
                /* MII modes */
                /* Eth mode select */
                gmiiField = ETH_GMII_SEL_GMII_MODE;
                break;

            case MCU_ETH_MAC_CONN_TYPE_RMII_10_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RMII_10_FULL:
            case MCU_ETH_MAC_CONN_TYPE_RMII_100_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RMII_100_FULL:
                /* RMII modes */
                gmiiField = ETH_GMII_SEL_RMII_MODE;
                break;

            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_10_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_10_FULL:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_100_FULL:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_1000:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND:
                /* RGMII modes */
                gmiiField = ETH_GMII_SEL_RGMII_MODE;
                break;

            default:
                /* Wrong configuration */
                break;
        }

        /* RMII_REF_CLK_OE_N */
        if (0U != ethCfg[portIdx].rmiiClkOutDisable)
        {
            gmiiField |= ETH_GMII_RMII_REF_CLK_DISABLE;
        }

        /* ID_MODE */
        if (0U != ethCfg[portIdx].idModeEnable)
        {
            gmiiField |= ETH_GMII_ID_MODE_ENABLE;
        }

        /* Unlock MSS_CTRL */
        Mcu_controlModuleUnlockMMR();

        if ((uint8)1U == ethCfg[portIdx].macNum)
        {
            HW_WR_FIELD32(MCU_CSL_MSS_CTRL_BASE + MSS_CPSW_CONTROL_REG, MSS_CPSW_CONTROL_REG_P1_GMII_FIELD,
                          (gmiiField));
        }
        else if ((uint8)2U == ethCfg[portIdx].macNum)
        {
            HW_WR_FIELD32(MCU_CSL_MSS_CTRL_BASE + MSS_CPSW_CONTROL_REG, MSS_CPSW_CONTROL_REG_P2_GMII_FIELD,
                          (gmiiField));
        }
        else
        {
            /* wrong port */
        }

        /* Lock MSS_CTRL */
        Mcu_controlModuleLockMMR();
    }

    return;
}

static void Mcu_controlModuleUnlockMMR()
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    /*Unlock MSS_CTRL*/
    baseAddr = (uint32)MCU_CSL_MSS_CTRL_BASE;
    kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK0);
    HW_WR_REG32(kickAddr, MCU_TEST_KICK0_UNLOCK_VAL); /* KICK 0 */
    kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK1);
    HW_WR_REG32(kickAddr, MCU_TEST_KICK1_UNLOCK_VAL); /* KICK 1 */
}

static void Mcu_controlModuleLockMMR()
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    /*Lock MSS_CTRL*/
    baseAddr = (uint32)MCU_CSL_MSS_CTRL_BASE;
    kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK0);
    HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 0 */
    kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK1);
    HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 1 */
}
