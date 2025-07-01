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
 *  \file     Pwm_Irq.h
 *
 *  \brief    This component provides services for initialization and control of the microcontroller
 * internal PWM unit (pulse width modulation). The PWM module generates pulses with variable pulse
 * width. It allows the selection of the duty cycle and the signal period time.
 *
 */

/*DesignId : PWM_DesignId_004 */
/*Requirements  :  : SWS_Pwm_70075 */
/*Design  :  : AUTORADAR_MCAL-1638 */
/* ---- Protection against multiple inclusion
 * ----------------------------------------------------------------------*/
#ifndef PWM_IRQ_H
#define PWM_IRQ_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/* Requirements :SWS_Pwm_70075,  */
/* Design :AUTORADAR_MCAL-1638 */
#include "Pwm.h"
#include "sys_common.h"
#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)

#if (PWM_ISR_TYPE == PWM_ISR_CAT1)
/** \brief PWM channel 1 ISR */
void Pwm_Ch1Notify(void);
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch1Notify);
#elif (PWM_ISR_TYPE == PWM_ISR_VOID)
/** \brief PWM channel 1 ISR */
void Pwm_Ch1Notify(void);
#endif

#if (PWM_ISR_TYPE == PWM_ISR_CAT1)
/** \brief PWM channel 2 ISR */
void Pwm_Ch2Notify(void);
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch2Notify);
#elif (PWM_ISR_TYPE == PWM_ISR_VOID)
/** \brief PWM channel 2 ISR */
void Pwm_Ch2Notify(void);
#endif

#if (PWM_ISR_TYPE == PWM_ISR_CAT1)
/** \brief PWM channel 3 ISR */
void Pwm_Ch3Notify(void);
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch3Notify);
#elif (PWM_ISR_TYPE == PWM_ISR_VOID)
/** \brief PWM channel 3 ISR */
void Pwm_Ch3Notify(void);
#endif

/** \brief PWM Notification function */
extern FUNC(void, PWM_CODE) Pwm_ChannelNotificationISR(Pwm_ChannelType Channel);

#endif

#ifdef __cplusplus
}
#endif
#endif /*PWM_IRQ_H*/
/**********************************************************************************************************************
 *  END OF FILE: Pwm_Irq.h
 *********************************************************************************************************************/
