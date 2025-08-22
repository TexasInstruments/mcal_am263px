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
 *  \file     Cdd_Ipc_App_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Ipc_App_Startup.h"
#include "sys_pmu.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                              Macros                                        */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

void Uart_Delay(uint32 Delay)
{
    for (Delay = 0; Delay < 5000; Delay++)
    {
        ;
    }
}

void Cdd_Ipc_App_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();
    Mcal_pmuInit();
}

#if (STD_OFF == MCU_VARIANT_PRE_COMPILE)
static Mcu_ClockConfigType gIpcAppMcuClockConfig[] = {
    [0] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_SCI0,
            .Mcu_ClockSourceId = MCU_CLKSRC_3,
            .Mcu_ClockDiv      = 3,
            .Mcu_InitCfg       = TRUE,
        },
    [1] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTI0,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [2] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTI1,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [3] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTI2,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [4] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_WDT0,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
};

static Mcu_RamSectionConfigType gIpcAppMcuRamConfig[] = {};

static Mcu_ConfigType gIpcAppMcuConfig = {.Mcu_ResetMode           = MCU_PERFORM_RESET_MODE_WARM,
                                          .Mcu_ConfigRamSection    = &(gIpcAppMcuRamConfig[0]),
                                          .Mcu_NumberOfRamSectors  = ARRAYSIZE(gIpcAppMcuRamConfig),
                                          .Mcu_ClockConfig         = &(gIpcAppMcuClockConfig[0]),
                                          .Mcu_NumberOfClockConfig = ARRAYSIZE(gIpcAppMcuClockConfig)};

#endif /*(STD_OFF == MCU_VARIANT_PRE_COMPILE)*/

/* IPC Interrupt Configuration */
void Cdd_Ipc_InterruptConfig(void)
{
    vimInit();
    Vim_IntCfg interruptCfg;
    interruptCfg.map      = VIM_INTTYPE_IRQ;
    interruptCfg.type     = VIM_INTTRIGTYPE_PULSE;
    interruptCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_MBOX_READ_REQ;
    interruptCfg.handler  = &Cdd_Ipc_Isr;
    interruptCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&interruptCfg);
}

uint32 gRemoteCoreId[] = {
    CDD_IPC_R5FSS0_1_ID, MAX /* this value indicates the end of the array */
};

void Cdd_Ipc_App_PlatformInit(void)
{
#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&gIpcAppMcuConfig);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/
#if (CDD_IPC_SAFEIPC_ENABLE == STD_OFF)
#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    Enable_Uart();
#endif
    /* Delay for UART to settle up */
    Uart_Delay(5000);
}
