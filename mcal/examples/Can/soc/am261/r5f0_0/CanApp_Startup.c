/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     CanApp_Startup.c
 *
 *  \brief    This file contains the Can test example
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/

/* Include Files */
#include "Can.h"
#include "CanApp_Startup.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "esm.h"
#include "sys_vim.h"

#if (STD_ON == CAN_ECC_ENABLE)
/* #define CANFD_ESM_MASK          (uint64)(0x4800000000000) */
#define CANFD_ESM_MASK (uint64)(0xC000000000000)
/* #define CANFD2_ESM_MASK         (uint64)(0x000200200000) */
#define CANFD2_ESM_MASK (uint64)(0x3000000000000)
#endif

static void CanExample_PlatformInit()
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
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    Enable_Uart();

    return;
}

#if (STD_ON == CAN_ECC_ENABLE)
void esm_low_priority_handler(void)
{
#if defined(CAN_CONTROLLER_MCAN0)
    uint64 esmStatus2 = esmGetStatus(esmREG, 0, CANFD1_ESM_MASK);
    if (esmStatus2)
    {
        Can_0_Int1ISR_Fun();
        esmClearStatus(esmREG, 0, CANFD2_ESM_MASK);
    }
#endif
#if defined(CAN_CONTROLLER_MCAN1)
    uint64 esmStatus = esmGetStatus(esmREG, 0, CANFD2_ESM_MASK);
    if (esmStatus)
    {
        esmClearStatus(esmREG, 0, CANFD_ESM_MASK);
        Can_1_Int1ISR_Fun();
    }
#endif
}

#endif

static void CanExample_InterruptConfig(void)
{
    vimInit();
    Vim_IntCfg Can_IntCfg;
    Can_IntCfg.map    = VIM_INTTYPE_IRQ;
    Can_IntCfg.type   = VIM_INTTRIGTYPE_LEVEL;
    Can_IntCfg.intNum = MCAN0_MCAN_LVL_INT_0;

#if defined(CAN_CONTROLLER_MCAN0)
    Can_IntCfg.intNum   = MCAN0_MCAN_LVL_INT_0;
    Can_IntCfg.handler  = Can_0_Int0ISR;
    Can_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Can_IntCfg);

#if (STD_ON == CAN_ECC_ENABLE)
    Can_IntCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1;
    Can_IntCfg.handler  = esm_low_priority_handler;
    Can_IntCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&Can_IntCfg);

    esmClearStatus(esmREG, 0, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 1, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 2, 0xFFFFFFFFFFFFFFFF);

    esmSetInterruptLevel(esmREG, CANFD1_ESM_MASK, 0U);
    esmEnableInterrupt(esmREG, CANFD1_ESM_MASK);
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN1)
    Can_IntCfg.intNum   = MCAN1_MCAN_LVL_INT_0;
    Can_IntCfg.handler  = Can_1_Int0ISR;
    Can_IntCfg.priority = VIM_PRIORITY_5;
    vimRegisterInterrupt(&Can_IntCfg);

#if (STD_ON == CAN_ECC_ENABLE)
    Can_IntCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1;
    Can_IntCfg.handler  = esm_low_priority_handler;
    Can_IntCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&Can_IntCfg);

    esmClearStatus(esmREG, 0, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 1, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 2, 0xFFFFFFFFFFFFFFFF);

    esmSetInterruptLevel(esmREG, CANFD2_ESM_MASK, 0U);
    esmEnableInterrupt(esmREG, CANFD2_ESM_MASK);
#endif
#endif
}

void CanApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
#if (STD_ON == CAN_ECC_ENABLE)
    /* ESM module needs to be enabled to generate interrupt for ECC errors */
    esmInit();
#endif
    CanExample_PlatformInit();
    AppUtils_TimerInit();
    CanExample_InterruptConfig();
}

#ifdef __cplusplus
}
#endif
