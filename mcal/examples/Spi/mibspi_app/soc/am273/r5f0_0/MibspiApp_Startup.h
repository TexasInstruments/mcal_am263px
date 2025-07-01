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
 *  \file     mcspiApp_Startup.h
 *
 *  \brief    This file contains the McSPI test example Hw Dependent
 *             functions declartions.
 */
#ifdef __cplusplus
extern "C" {
#endif

/* Starterware Includes */
#include "string.h"
/*LDRA_ANALYSIS*/
#include "Spi_Cfg.h"
#include "Spi.h"
#include "Spi_Priv.h"
#include "Spi_Dbg.h"
/* Starterware Includes */
#include "app_utils.h"
#include "trace.h"
#include "sys_vim.h"
#include "SchM_Spi.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"

#include "hw_Mibspi.h"
#include "Spi_Irq.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \brief Clock divider used for interruptible sequence testing. The SPI clock
 *  should be lower so that the second sequence gets scheduled. Otherwise
 *  the CPU will fully execute the first sequence in ISR as the McSPI data rate
 *  is faster than the code execution.
 */
#define SPI_APP_INTR_SEQ_DIVIDER (47U)

/** \brief Default ASYNC/SYNC Transmit flag - TRUE: Async, FALSE: Sync */
#define SPI_APP_DEFAULT_ASYNC_SYNC (TRUE)

/** \brief Default ASYNC mode - interrupt or polled */
#define SPI_APP_DEFAULT_ASYNC_MODE (SPI_INTERRUPT_MODE)

/** \brief RX/TX transfer length used for ramp-up test */
#define SPI_APP_RX_TX_LENGTH_RAMP_UP (0xFFFFU)
/** \brief RX/TX transfer length used for ramp-down test */
#define SPI_APP_RX_TX_LENGTH_RAMP_DOWN (0xFFFEU)
/** \brief Ramp test loop count. */
#define SPI_APP_RAMP_LOOP_COUNT (100U)
/** \brief Clock ramp test clock divider */
#define SPI_APP_RAMP_DIVIDER (0xFFFFFFFFU)

/* ========================================================================== */
/*                  Function Declarations                                     */
/* ========================================================================== */
void MibspiApp_Startup(void);
void SpiApp_interruptConfig(void);

#ifdef __cplusplus
}
#endif
