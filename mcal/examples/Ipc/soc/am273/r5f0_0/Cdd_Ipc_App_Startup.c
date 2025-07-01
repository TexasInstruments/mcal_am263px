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

void Cdd_Ipc_App_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();
}

static Mcu_ClockConfigType gIpcAppMcuClockConfig[] = {
    [0] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_SCIA,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [1] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTIA,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [2] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTIB,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [3] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTIC,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [4] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_WDT,
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

/* IPC Interrupt Configuration */
void Cdd_Ipc_InterruptConfig(void)
{
    vimInit();
    Vim_IntCfg interruptCfg;
    interruptCfg.map  = VIM_INTTYPE_IRQ;
    interruptCfg.type = VIM_INTTRIGTYPE_PULSE;
#if (CDD_IPC_SAFEIPC_ENABLE == STD_ON)
    interruptCfg.intNum = 79U;
#else
    interruptCfg.intNum = 77U;
#endif
    interruptCfg.handler  = &Cdd_Ipc_Isr;
    interruptCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&interruptCfg);
}
#if (CDD_IPC_SAFEIPC_ENABLE == STD_OFF)
uint32 gRemoteCoreId[] = {
    CDD_IPC_R5FSS0_1_ID, CDD_IPC_C66x_DSP_ID, MAX /* this value indicates the end of the array */
};
#endif
#if (CDD_IPC_SAFEIPC_ENABLE == STD_ON)
uint32 gRemoteCoreId[] = {
    CDD_IPC_R5FSS0_1_ID, MAX /* this value indicates the end of the array */
};
#endif

void Cdd_Ipc_App_PlatformInit(void)
{
#if (CDD_IPC_SAFEIPC_ENABLE == STD_OFF)
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
#if (STD_OFF == MCU_NO_PLL)
    uint32 sys_clk_freq_vclk_const;

    /* MCU PLL Config */
    gIpcAppMcuConfig.Mcu_PllConfig   = McuModuleConfiguration.Mcu_PllConfig;
    gIpcAppMcuConfig.Mcu_PllSourceId = McuModuleConfiguration.Mcu_PllSourceId;
#endif
#endif

    Mcu_Init(&gIpcAppMcuConfig);
#if (CDD_IPC_SAFEIPC_ENABLE == STD_OFF)
    Port_Init(&PortConfigSet_0);
    mss_uart_tx_pin = 3;
    mss_uart_rx_pin = 4;

#if defined AWR29XXETS_PLATFORM
    mss_uart_tx_pin = 12;
    mss_uart_rx_pin = 8;
#endif
#if defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM)
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;
#endif

    /* Set up the pinmux for UART tx */
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);

#if (STD_OFF == MCU_NO_PLL)
    if (McuModuleConfiguration.Mcu_PllSourceId == MCU_CLKSRC_DPLL)
    {
        sys_clk_freq_vclk_const =
            (McuModuleConfiguration.Mcu_PllConfig[MCU_CLKSRC_DPLL].Mcu_PllClk1.MCU_PLL_HSDIV2 / (2e6)) * 30;
    }
    else
    {
        sys_clk_freq_vclk_const =
            (McuModuleConfiguration.Mcu_PllConfig[MCU_CLKSRC_APLL].Mcu_PllClk1.MCU_PLL_HSDIV0 / (2e6)) * 30;
    }
    Enable_Uart(sys_clk_freq_vclk_const);
#else
    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);
#endif
#endif

    return;
}
