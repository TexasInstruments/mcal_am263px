/* ======================================================================
 *   Copyright (c) 2022 Texas Instruments Incorporated
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

/**`
 *  \file     Pwm_Irq.c
 *
 *  \brief    This component provides services for initialization and control of the microcontroller
 * internal PWM unit (pulse width modulation). The PWM module generates pulses with variable pulse
 * width. It allows the selection of the duty cycle and the signal period time.
 *
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/*
 *Design: MCAL-13124
 */
/* ---- Callback Routines Declarations ------------------------------------ */
#include "Pwm_Irq.h"
#include "Pwm.h"

/**********************************************************************************************************************
 *  MACROS
 **********************************************************************************************************************/
#define PWM_CHANNEL_1 0U
#define PWM_CHANNEL_2 1U
#define PWM_CHANNEL_3 2U
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

#define PWM_START_SEC_ISR_CODE
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Pwm_MemMap.h"

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch1Notify(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch1Notify)
#endif
{
    Pwm_GlobalReEnable();
    Pwm_ChannelNotificationISR(PWM_CHANNEL_1);
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch2Notify(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch2Notify)
#endif
{
    Pwm_GlobalReEnable();
    Pwm_ChannelNotificationISR(PWM_CHANNEL_2);
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch3Notify(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch3Notify)
#endif
{
    Pwm_GlobalReEnable();
    Pwm_ChannelNotificationISR(PWM_CHANNEL_3);
}
#endif

/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#define PWM_STOP_SEC_ISR_CODE
#include "Pwm_MemMap.h"
/**********************************************************************************************************************
 *  END OF FILE: Pwm_Irq.c
 *********************************************************************************************************************/
