/* =============================================================================
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
 * ========================================================================== */

/**
 *  \file     Port_Irq.h
 *
 *  \brief    This file contains ISR function declaration for PORT MCAL driver
 *
 */

#ifndef PORT_IRQ_H_
#define PORT_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Port.h"
#include "sys_common.h"
#if (PORT_ISR_TYPE == PORT_ISR_CAT2)
#include "Os.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         GLOBAL VARIABLES                                   */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))

void Port_MssPinHighLevelIsr(void);
void Port_MssPinLowLevelIsr(void);
void Port_RcssPinHighLevelIsr(void);
void Port_RcssPinLowLevelIsr(void);

#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)

ISR(Port_MssPinHighLevelIsr);
ISR(Port_MssPinLowLevelIsr);
ISR(Port_RcssPinHighLevelIsr);
ISR(Port_RcssPinLowLevelIsr);

#endif /* #if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID)) */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PORT_IRQ_H_ */

/*******************************************************************************
 *  END OF FILE: Port_Irq.h
 *******************************************************************************/
