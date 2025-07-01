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
 *  \file     FlsApp_Startup.c
 *
 *  \brief    This file contains the Eth platform intialisations which required for example
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Det.h"
#include "Dem.h"
#include "Fls.h"
#include "Fls_Irq.h"
#include "Fls_Brd_Nor.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"
/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "trace.h"
#include "FlsApp_Startup.h"

/* Starterware Includes */
#include "sys_vim.h"
#include "app_utils.h"
#include "soc.h"

#include "hw_ctrl_core.h"
#include "FlsApp_Startup.h"

static void FlsApp_InterruptConfig(void);
static void FlsApp_PlatformInit(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define FLSEXAMPLE_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))
uint32 gTestPassed;

sint32 TestState = TRUE;

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration_0;
#endif

Mcu_RamSectionConfigType Mcu_RamConfig[] = {[0] = {.Mcu_RamSectionBaseAddress = (uint8 *)&TestState,
                                                   .Mcu_RamDefaultValue       = 0x00,
                                                   .Mcu_RamSectionBytes       = sizeof(TestState)}};

Mcu_ClockConfigType Mcu_ClkConfig[] = {[0] =
                                           {
                                               .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_QSPI,
                                               .Mcu_ClockSourceId = MCU_CLKSRC_4,
                                               .Mcu_ClockDiv      = 4,
                                               .Mcu_InitCfg       = TRUE,
                                           },
                                       [1] = {
                                           .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_SCIA,
                                           .Mcu_ClockSourceId = MCU_CLKSRC_2,
                                           .Mcu_ClockDiv      = 0,
                                           .Mcu_InitCfg       = TRUE,
                                       }};
Mcu_ConfigType      Mcu_Config      = {.Mcu_ResetMode           = MCU_PERFORM_RESET_MODE_WARM,
                                       .Mcu_ConfigRamSection    = &Mcu_RamConfig[0],
                                       .Mcu_NumberOfRamSectors  = FLSEXAMPLE_ARRAYSIZE(Mcu_RamConfig),
                                       .Mcu_ClockConfig         = (Mcu_ClockConfigPtrType)&Mcu_ClkConfig,
                                       .Mcu_NumberOfClockConfig = FLSEXAMPLE_ARRAYSIZE(Mcu_ClkConfig)};

static void FlsApp_PlatformInit()
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif

#if (STD_ON == PORT_SET_PIN_MODE_API)
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;
    /* Set up the pinmux for UART tx */
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);
#endif /*    #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
    vimInit();

    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);

    AppUtils_TimerInit();
}

/* =========================Function separator========================= */

static void FlsApp_InterruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    vimInit();
    intCfg.priority = VIM_PRIORITY_4;
    intCfg.intNum   = 35U;
    intCfg.handler  = Fls_Hdlr;
    vimRegisterInterrupt(&intCfg);
}

/* =========================Function separator========================= */
void FlsApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    FlsApp_PlatformInit();
    AppUtils_TimerInit();
    FlsApp_InterruptConfig();
}

#ifdef __cplusplus
}
#endif
