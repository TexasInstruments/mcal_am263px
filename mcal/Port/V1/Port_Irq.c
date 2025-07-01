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
 *  \file     Port_Irq.c
 *
 *  \brief    This file contains the ISR implementation of PORT MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Port_Priv.h"
#include "Port_Irq.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define PORT_START_SEC_ISR_CODE
#include "Port_MemMap.h"

/*******************************************************************************
    Function name:  Port_MssPinHighLevelIsr
    Description: ISR calls Notification function for High Level.
********************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_MssPinHighLevelIsr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_MssPinHighLevelIsr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_MssPinNotificationISR(PORT_HIGH_LEVEL);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

/*******************************************************************************
    Function name:  Port_MssPinLowLevelIsr
    Description: ISR calls Notification function for Low Level.
********************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_MssPinLowLevelIsr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_MssPinLowLevelIsr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_MssPinNotificationISR(PORT_LOW_LEVEL);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

/*******************************************************************************
    Function name:  Port_RcssPinHighLevelIsr
    Description: ISR calls Notification function for High Level.
********************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_RcssPinHighLevelIsr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_RcssPinHighLevelIsr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_RcssPinNotificationISR(PORT_HIGH_LEVEL);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

/*******************************************************************************
    Function name:  Port_RcssPinLowLevelIsr
    Description: ISR calls Notification function for Low Level.
********************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_RcssPinLowLevelIsr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_RcssPinLowLevelIsr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_RcssPinNotificationISR(PORT_LOW_LEVEL);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#define PORT_STOP_SEC_ISR_CODE
#include "Port_MemMap.h"

/*******************************************************************************
 *  END OF FILE: Port_Irq.c
 *******************************************************************************/
