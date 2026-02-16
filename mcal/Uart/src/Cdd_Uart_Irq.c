/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
