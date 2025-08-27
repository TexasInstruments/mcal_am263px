/* ======================================================================
 *   Copyright (C) 2024 Texas Instruments Incorporated
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
 *  \file     UartInterruptApp_Startup.c
 *
 *  \brief    This file contains platform-based functions for UART Interrupt Example.
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "UartInterruptApp_Startup.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CDD UART Interrupt Configuration */
void Cdd_Uart_InterruptConfiguration()
{
    vimInit();
    Vim_IntCfg interruptCfg;
    interruptCfg.map      = VIM_INTTYPE_IRQ;
    interruptCfg.type     = VIM_INTTRIGTYPE_PULSE;
    interruptCfg.priority = VIM_PRIORITY_15;
    interruptCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_UART0_IRQ;
    interruptCfg.handler  = &Cdd_Uart_Channel0Isr;
    vimRegisterInterrupt(&interruptCfg);
}

#ifdef __cplusplus
}
#endif
