/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     QSpiFlashApp.h
 *
 *  \brief    QSPI flash example header file
 *
 */

#ifndef QSPI_FLASH_APP_STARTUP_H_
#define QSPI_FLASH_APP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* Starterware Includes */
#include "app_utils.h"
#include "trace.h"
#include "sys_vim.h"
#include "hw_Mibspi.h"
#include "CacheP.h"

/*LDRA_ANALYSIS*/
#include "Spi_Cfg.h"
#include "Spi.h"
#include "Spi_Dbg.h"
#include "SchM_Spi.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "SchM_Port.h"
#include "Spi_Irq.h"
#include "Spi_Priv.h"
#include "Spi_Qspi.h"
#include "Cdd_Dma_Irq.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x)         (sizeof((x)) / sizeof(x[0U]))
#define QSPI_APP_READ_LENGTH (1U * 1024U)

#define QSPI_APP_FLASH_BLOCK_SIZE (4U * QSPI_APP_READ_LENGTH)

#define QSPI_APP_FLASH_SIZE (4U * 1024U * 1024U) /* 4MB  SPANSION*/

#define QSPI_APP_CLKSRC_40M_CLK (0U)
#if defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM)
#define QSPI_APP_CLKSRC_50M_CLK (1U)
#else
#define QSPI_APP_CLKSRC_80M_CLK (1U)
#endif

/* To enable autorun */
#define QSPI_FLASH_QT 1

/* UART read timeout in msec */
#define SPI_APP_UART_TIMEOUT_MSEC (10000U)
#define QSPI_IS_ASYNC             (TRUE)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void QSpiFlashApp_Startup(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef QSPI_FLASH_APP_STARTUP_H_ */
