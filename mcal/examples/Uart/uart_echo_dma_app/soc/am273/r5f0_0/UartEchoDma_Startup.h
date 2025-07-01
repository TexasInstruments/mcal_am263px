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
 *  \file     UartEchoDma_Startup.h
 *
 *  \brief    This file declares platform-specific functions for
 *            UART Echo DMA example.
 */

#ifndef CDD_UART_ECHO_DMA_STARTUP_
#define CDD_UART_ECHO_DMA_STARTUP_

#include "Cdd_Uart_Irq.h"
#include "Cdd_Dma_Irq.h"
#include "UartEchoDma.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

void Cdd_Uart_InterruptConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_UART_ECHO_DMA_STARTUP_ */
