/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     fsirxapp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "fsirxapp_Startup.h"
#include "sys_vim.h"
#include "Cdd_FsiRx.h"
#include "Cdd_FsiRx_Irq.h"
#include "Cdd_FsiTx_Irq.h"

/* ========================================================================== */
/*                           Structures and Enums                                 */
/* ========================================================================== */
#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Cdd_FsiRxApp_interruptConfig(void);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void        Cdd_FsiRxApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();

    /*Enable Domain clocks*/
    Cdd_FsiRxApp_platformInit();
}

void Cdd_FsiRxApp_enableRxInternalLoopback(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB);
    regVal |= (uint16)CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_INT_LOOPBACK_MASK |
              (CDD_FSI_RX_CTRL_REG_KEY << CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_KEY_SHIFT);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB, regVal);
}

void Cdd_FsiRxApp_platformInit(void)
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
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    Enable_Uart();
    return;
}

void Cdd_FsiRxApp_interruptInit(void)
{
    vimInit();
    Cdd_FsiRxApp_interruptConfig();
}
/* CDD FSI Interrupt Configuration */
static void Cdd_FsiRxApp_interruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_12;
    intCfg.handler  = CddFsiTx_FSIINT1_IrqUnit0;
    intCfg.priority = VIM_PRIORITY_14;
    vimRegisterInterrupt(&intCfg);

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_14;
    intCfg.handler  = CddFsiRx_FSIINT1_IrqUnit0;
    intCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&intCfg);

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_15;
    intCfg.handler  = CddFsiRx_FSIINT2_IrqUnit0;
    intCfg.priority = VIM_PRIORITY_13;
    vimRegisterInterrupt(&intCfg);
}

void Cdd_FsiRxApp_TriggerExtTransmission(uint32 base, uint16 value)
{
    uint16 regVal;
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_EVT_FRC_ALT1);
    regVal |= ((uint16)value);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_EVT_FRC_ALT1, regVal);
}

/* ===============================================================================================*/
/*                          Function Definitions  to Initialize the ADC Module.                   */
/* ===============================================================================================*/
