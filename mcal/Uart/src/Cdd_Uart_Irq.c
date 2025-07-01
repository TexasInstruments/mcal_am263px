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
 *  \file     Cdd_Uart_Irq.c
 *
 *  \brief    This file contains CDD UART driver IRQ functions
 *
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"
#include "Cdd_Uart.h"
#include "Cdd_Uart_Irq.h"

extern CddUart_Object CddUart_ChannelObjects[CDD_UART_NUM_CHANNELS];

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#define CDD_UART_START_SEC_ISR_CODE
#include "Cdd_Uart_MemMap.h"

/* Function name: Cdd_Uart_ChannelIsr
   Description: The Channel-specific Interrupt Subroutine calls handler function based on the
   channel input. */
MCAL_INTERRUPT_ATTRIBUTE FUNC(void, CDD_UART_CODE) Cdd_Uart_ChannelIsr(uint8 ChannelID)
{
    uint32 channelIndex = 0U;

    channelIndex = Cdd_Uart_GetChannelIndex(ChannelID);

    Uart_Cdd_masterIsr(&CddUart_ChannelObjects[channelIndex]);
}

/* Per-channel ISRs */
#ifdef CDD_UART_UNIT_UART0_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel0Isr(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel0Isr)
#endif
{
    Cdd_Uart_ChannelIsr(0U);
}
#endif

#ifdef CDD_UART_UNIT_UART1_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel1Isr(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel1Isr)
#endif
{
    Cdd_Uart_ChannelIsr(1U);
}
#endif

#ifdef CDD_UART_UNIT_UART2_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel2Isr(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel2Isr)
#endif
{
    Cdd_Uart_ChannelIsr(2U);
}
#endif

#ifdef CDD_UART_UNIT_UART3_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel3Isr(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel3Isr)
#endif
{
    Cdd_Uart_ChannelIsr(3U);
}
#endif

#ifdef CDD_UART_UNIT_UART4_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel4Isr(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel4Isr)
#endif
{
    Cdd_Uart_ChannelIsr(4U);
}
#endif

#ifdef CDD_UART_UNIT_UART5_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_Channel5Isr(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_Channel5Isr)
#endif
{
    Cdd_Uart_ChannelIsr(5U);
}
#endif

#ifdef CDD_UART_UNIT_UART_MSS_SCIA_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_ChannelIsr_MSS_SCIA(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_ChannelIsr_MSS_SCIA)
#endif
{
    Cdd_Uart_ChannelIsr(0U);
}
#endif

#ifdef CDD_UART_UNIT_UART_MSS_SCIB_ACTIVE
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT1) || (CDD_UART_ISR_TYPE == CDD_UART_ISR_VOID))
void Cdd_Uart_ChannelIsr_MSS_SCIB(void)
#elif (CDD_UART_ISR_TYPE == CDD_UART_ISR_CAT2)
ISR(Cdd_Uart_ChannelIsr_MSS_SCIB)
#endif
{
    Cdd_Uart_ChannelIsr(1U);
}
#endif

#define CDD_UART_STOP_SEC_ISR_CODE
#include "Cdd_Uart_MemMap.h"
