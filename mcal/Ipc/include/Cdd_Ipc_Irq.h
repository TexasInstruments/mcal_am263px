/* ======================================================================
 *   Copyright (c) 2023-2024 Texas Instruments Incorporated
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
 *  \file     CDD_Ipc_Irq.h
 *
 *  \brief    This file contains ISR function declaration for Complex Device Driver
 *
 */

/**
 *  \ingroup MCAL_CDD_API
 *  @{
 */

#ifndef CDD_IPC_IRQ_H_
#define CDD_IPC_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_Ipc.h"

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************************************************
 * INCLUDES
 ********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/** \brief IPC Master ISR functions */
#if ((CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT1) || (CDD_IPC_ISR_TYPE == CDD_IPC_ISR_VOID))
/** \brief Channel 0 interrupt service routine */
void Cdd_Ipc_Isr(void);
#elif (CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT2)
ISR(Cdd_Ipc_Isr);
#endif /* ((CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT1).... */

#ifdef __cplusplus
}
#endif

#endif
