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
 *  \file     CDD_Ipc_Irq.c
 *
 *  \brief    This file contains CDD IPC driver IRQ functions
 *
 */
#define CDD_IPC_IRQ_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "Cdd_Ipc.h"
#include "Cdd_Ipc_Irq.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITIONS
 *********************************************************************************************************************/
extern IpcNotify_Object CddIpc_NotifyObject;
extern IpcNotify_Handle CddIpc_NotifyHandle;

#define CDD_IPC_START_SEC_ISR_CODE
#include "Cdd_Ipc_MemMap.h"

/* Function name: Cdd_Ipc_Isr
   Description: The Channel0 Interrupt Subroutine calls Notification function depending on the
   channel mode. */
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT1) || (CDD_IPC_ISR_TYPE == CDD_IPC_ISR_VOID))
void Cdd_Ipc_Isr(void)
#elif (CDD_IPC_ISR_TYPE == CDD_IPC_ISR_CAT2)
ISR(Cdd_Ipc_Isr)
#endif
{
    IpcNotify_lld_isr(CddIpc_NotifyHandle);
}

#define CDD_IPC_STOP_SEC_ISR_CODE
#include "Cdd_Ipc_MemMap.h"
