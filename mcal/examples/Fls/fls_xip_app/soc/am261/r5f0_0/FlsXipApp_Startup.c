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
#include "FlsXipApp_Startup.h"

/* Starterware Includes */
#include "sys_vim.h"
#include "app_utils.h"
#include "soc.h"

#include "hw_ctrl_core.h"
#include "FlsXipApp_Startup.h"
#include "sys_pmu.h"

static void FlsApp_InterruptConfig(void);
static void FlsApp_PlatformInit(void);
#if (STD_ON == FLS_DMA_ENABLE)
static void FlashAppDma_interruptConfig(void);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define FLSEXAMPLE_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))
uint32 gTestPassed;

sint32 TestState = TRUE;

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) Mcu_Config;
#endif

static void FlsApp_PlatformInit()
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

/* =========================Function separator========================= */

static void FlsApp_InterruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    vimInit();
    intCfg.priority = VIM_PRIORITY_4;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_OSPI0_INT;
    intCfg.handler  = Fls_Hdlr;
    vimRegisterInterrupt(&intCfg);
}

#if (STD_ON == FLS_DMA_ENABLE)
static void FlashAppDma_interruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.priority = VIM_PRIORITY_7;
    intCfg.intNum   = MCAL_MSS_INTR_MSS_TPCC_A_INTAGG;
    intCfg.handler  = &CDD_EDMA_lld_transferCompletionMasterIsrFxn;
    vimRegisterInterrupt(&intCfg);
    return;
}
#endif  //(STD_ON == FLS_DMA_ENABLE)

/* =========================Function separator========================= */
void FlsApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    FlsApp_PlatformInit();
    AppUtils_TimerInit();
    Mcal_pmuInit();
    FlsApp_InterruptConfig();
#if (STD_ON == FLS_DMA_ENABLE)
    FlashAppDma_interruptConfig();
#endif  //(STD_ON == FLS_DMA_ENABLE)
}

#ifdef __cplusplus
}
#endif
