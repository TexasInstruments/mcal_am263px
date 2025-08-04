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

/* Protection against multiple inclusion */
#ifndef FLSAPP_STARTUP_H_
#define FLSAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "app_utils.h"
#include "sys_common.h"

#include "app_utils.h"
#include "sys_vim.h"
#include "hw_ctrl_core.h"
#include "hw_types.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Cdd_Dma_Irq.h"

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration_0;
#endif

#include "ioexp_tca6416_6424.h"
#if (STD_OFF == CDD_I2C_POLLING_MODE)
#include "Cdd_I2c_Irq.h"
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
void        FlsApp_Startup(void);
static void FlsApp_InterruptConfig(void);
static void FlsApp_PlatformInit(void);
#if (STD_OFF == CDD_I2C_POLLING_MODE)
void Cdd_I2c_InterruptConfig(void);
#endif
#endif
