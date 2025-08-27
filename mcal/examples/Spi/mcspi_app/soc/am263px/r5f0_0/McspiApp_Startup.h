/* ======================================================================
 *   Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     mcspiApp_Startup.h
 *
 *  \brief    This file contains the McSPI test example Hw Dependent
 *             functions declartions.
 */
#ifdef __cplusplus
extern "C" {
#endif
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"

/*LDRA_ANALYSIS*/
#include "hw_types.h"

/* Starterware Includes */
#include "app_utils.h"
#include "trace.h"
#include "sys_vim.h"
// #include "McspiApp.h"

#include "hw_mcspi.h"
#include "Spi_Irq.h"
#include "Cdd_Dma_Irq.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0U]))

/* UART read timeout in msec */
#define SPI_APP_UART_TIMEOUT_MSEC (10000U)
#define APP_PERFORMANCE_MODE      STD_OFF

void Stop_Timer(uint8 Api_Id);
void Start_Timer(void);
void McspiApp_Startup(void);
void SpiApp_interruptConfig(void);
void SpiApp_platformInit(void);

#ifdef __cplusplus
}
#endif
