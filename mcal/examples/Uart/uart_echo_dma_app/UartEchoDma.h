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
 *  \file     UartEchoDma.h
 *
 *  \brief    UART Echo DMA App example header file
 */

#ifndef UART_ECHO_DMA_H_
#define UART_ECHO_DMA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "sys_vim.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "UART_ECHO_DMA_APP"

#define CDD_UART_APP_BUFFERSIZE (200U)

#define CDD_UART_APP_RECEIVE_BUFFERSIZE (8U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

void Apps_switch_to_system_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef UART_ECHO_DMA_H_ */
