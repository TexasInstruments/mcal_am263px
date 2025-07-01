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
 *  \file     UartEchoDma_Startup.c
 *
 *  \brief    This file contains platform-based functions for UART Echo DMA Example.
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "UartEchoDma_Startup.h"

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
    interruptCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTAGGR;
#if (STD_ON == CDD_UART_DMA_ENABLE)
    interruptCfg.handler = &CDD_EDMA_lld_transferCompletionMasterIsrFxn;
    vimRegisterInterrupt(&interruptCfg);
#endif
}

#ifdef __cplusplus
}
#endif
