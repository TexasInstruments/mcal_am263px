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
 *  \file     MiBspiApp.h
 *
 *  \brief    MiBSPI example header file
 *
 */

#ifndef MIBSPI_APP_H_
#define MIBSPI_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Spi_Cfg.h"
#include "Spi.h"
#include "Spi_Priv.h"
#include "Spi_Irq.h"
#include "Spi_Dbg.h"
#include "MibspiApp_Startup.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "SPI_APP"

/* Default loop count. */
#define SPI_APP_LOOP_COUNT (1U)

/* Performance loop count. */
#define SPI_APP_PERF_LOOP_COUNT (100U)

/** \brief RX/TX buffer size for allocation in words */
#define RX_TX_BUF_SIZE_WORD (32U)

/** \brief Default RX/TX transfer length in words */
#define SPI_APP_RX_TX_LENGTH (RX_TX_BUF_SIZE_WORD)

/** \brief Default clock divider - clock is 48MHz */
#define SPI_APP_DEFAULT_DIVIDER (0U)

#define APP_LOOPBACK_MODE STD_ON

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void SpiApp_MibspiJob0EndNotification(void);
void SpiApp_MibspiJob1EndNotification(void);
void SpiApp_MibspiJob2EndNotification(void);
void SpiApp_MibspiSeq0EndNotification(void);
void SpiApp_MibspiSeq1EndNotification(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MIBSPI_APP_H_ */
