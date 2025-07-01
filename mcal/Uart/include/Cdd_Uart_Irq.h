/* ===============================================================================================
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
 * ============================================================================================ */

/**
 *  \file     Cdd_Uart_Irq.h
 *
 *  \brief    This file contains ISR function declaration for Complex Device Driver
 *
 */

/**
 *  \ingroup MCAL_CDD_API
 *  @{
 */

#ifndef CDD_UART_IRQ_H_
#define CDD_UART_IRQ_H_

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/

#include "Cdd_Uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************************************
 *  GLOBAL MACROS
 ************************************************************************************************/

/**
 *  \name CDD Driver ISR category level
 *
 *  Defines for CDD UART Driver ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_UART_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CDD_UART_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CDD_UART_ISR_CAT2 (0x02U)
/* @} */

/*************************************************************************************************
 *  FUNCTION DECLARATIONS
 ************************************************************************************************/

/** \brief UART Master ISR function */
FUNC(void, CDD_UART_CODE) Cdd_Uart_ChannelIsr(uint8 ChannelID) __attribute__((target("arm")));

/** \brief UART per-instance ISR functions */
#ifdef CDD_UART_UNIT_UART0_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel0Isr(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel0Isr);
#endif
#endif

#ifdef CDD_UART_UNIT_UART1_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel1Isr(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel1Isr);
#endif
#endif

#ifdef CDD_UART_UNIT_UART2_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel2Isr(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel2Isr);
#endif
#endif

#ifdef CDD_UART_UNIT_UART3_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel3Isr(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel3Isr);
#endif
#endif

#ifdef CDD_UART_UNIT_UART4_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel4Isr(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel4Isr);
#endif
#endif

#ifdef CDD_UART_UNIT_UART5_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel5Isr(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel5Isr);
#endif
#endif

#ifdef CDD_UART_UNIT_UART_MSS_SCIA_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_ChannelIsr_MSS_SCIA(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_ChannelIsr_MSS_SCIA);
#endif
#endif

#ifdef CDD_UART_UNIT_UART_MSS_SCIB_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_ChannelIsr_MSS_SCIB(void);
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_ChannelIsr_MSS_SCIB);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
