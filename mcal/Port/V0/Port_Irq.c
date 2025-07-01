/* =============================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define PORT_START_SEC_ISR_CODE
#include "Port_MemMap.h"

/*******************************************************************************
 *                         BANK INTERRUPT DEFINATIONS
 *******************************************************************************/

/*******************************************************************************
Function name : Port_Bnk0Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_0
********************************************************************************/
#if defined(PORT_GPIO_BANK_0_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk0Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk0Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_0);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_0_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk1Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_1
********************************************************************************/
#if defined(PORT_GPIO_BANK_1_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk1Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk1Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR((uint32)(PORT_GPIO_BANK_SUFFIX + (uint32)PORT_GPIO_BANK_1));
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_1_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk2Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_2
********************************************************************************/
#if defined(PORT_GPIO_BANK_2_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk2Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk2Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_2);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_2_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk3Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_3
********************************************************************************/
#if defined(PORT_GPIO_BANK_3_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk3Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk3Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_3);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_3_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk4Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_4
********************************************************************************/
#if defined(PORT_GPIO_BANK_4_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk4Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk4Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_4);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_4_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk5Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_5
********************************************************************************/
#if defined(PORT_GPIO_BANK_5_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk5Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk5Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_5);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_5_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk6Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_6
********************************************************************************/
#if defined(PORT_GPIO_BANK_6_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk6Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk6Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_6);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_6_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk7Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_7
********************************************************************************/
#if defined(PORT_GPIO_BANK_7_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk7Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk7Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_7);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_7_ACTIVE) **/

/*******************************************************************************
Function name : Port_Bnk8Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_BANK_8
********************************************************************************/
#if defined(PORT_GPIO_BANK_8_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Bnk8Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Bnk8Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_BANK_SUFFIX + PORT_GPIO_BANK_8);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_BANK_8_ACTIVE) **/

/*******************************************************************************
 *                         CHANNEL INTERRUPT DEFINATIONS
 *******************************************************************************/

/*******************************************************************************
Function name : Port_Ch0Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_0
********************************************************************************/
#if defined(PORT_GPIO_CH_0_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch0Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch0Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_0);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_0_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch1Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_1
********************************************************************************/
#if defined(PORT_GPIO_CH_1_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch1Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch1Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_1);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_1_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch2Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_2
********************************************************************************/
#if defined(PORT_GPIO_CH_2_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch2Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch2Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_2);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_2_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch3Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_3
********************************************************************************/
#if defined(PORT_GPIO_CH_3_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch3Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch3Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_3);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_3_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch4Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_4
********************************************************************************/
#if defined(PORT_GPIO_CH_4_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch4Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch4Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_4);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_4_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch5Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_5
********************************************************************************/
#if defined(PORT_GPIO_CH_5_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch5Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch5Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_5);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_5_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch6Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_6
********************************************************************************/
#if defined(PORT_GPIO_CH_6_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch6Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch6Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_6);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_6_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch7Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_7
********************************************************************************/
#if defined(PORT_GPIO_CH_7_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch7Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch7Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_7);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_7_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch8Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_8
********************************************************************************/
#if defined(PORT_GPIO_CH_8_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch8Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch8Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_8);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_8_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch9Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_9
********************************************************************************/
#if defined(PORT_GPIO_CH_9_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch9Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch9Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_9);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_9_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch10Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_10
********************************************************************************/
#if defined(PORT_GPIO_CH_10_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch10Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch10Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_10);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_10_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch11Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_11
********************************************************************************/
#if defined(PORT_GPIO_CH_11_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch11Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch11Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_11);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_11_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch12Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_12
********************************************************************************/
#if defined(PORT_GPIO_CH_12_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch12Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch12Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_12);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_12_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch13Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_13
********************************************************************************/
#if defined(PORT_GPIO_CH_13_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch13Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch13Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_13);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_13_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch14Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_14
********************************************************************************/
#if defined(PORT_GPIO_CH_14_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch14Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch14Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_14);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_14_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch15Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_15
********************************************************************************/
#if defined(PORT_GPIO_CH_15_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch15Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch15Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_15);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_15_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch16Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_16
********************************************************************************/
#if defined(PORT_GPIO_CH_16_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch16Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch16Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_16);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_16_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch17Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_17
********************************************************************************/
#if defined(PORT_GPIO_CH_17_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch17Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch17Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_17);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_17_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch18Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_18
********************************************************************************/
#if defined(PORT_GPIO_CH_18_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch18Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch18Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_18);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_18_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch19Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_19
********************************************************************************/
#if defined(PORT_GPIO_CH_19_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch19Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch19Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_19);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_19_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch20Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_20
********************************************************************************/
#if defined(PORT_GPIO_CH_20_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch20Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch20Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_20);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_20_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch21Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_21
********************************************************************************/
#if defined(PORT_GPIO_CH_21_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch21Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch21Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_21);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_21_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch22Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_22
********************************************************************************/
#if defined(PORT_GPIO_CH_22_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch22Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch22Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_22);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_22_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch23Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_23
********************************************************************************/
#if defined(PORT_GPIO_CH_23_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch23Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch23Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_23);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_23_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch24Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_24
********************************************************************************/
#if defined(PORT_GPIO_CH_24_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch24Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch24Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_24);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_24_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch25Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_25
********************************************************************************/
#if defined(PORT_GPIO_CH_25_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch25Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch25Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_25);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_25_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch26Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_26
********************************************************************************/
#if defined(PORT_GPIO_CH_26_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch26Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch26Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_26);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_26_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch27Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_27
********************************************************************************/
#if defined(PORT_GPIO_CH_27_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch27Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch27Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_27);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_27_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch28Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_28
********************************************************************************/
#if defined(PORT_GPIO_CH_28_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch28Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch28Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_28);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_28_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch29Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_29
********************************************************************************/
#if defined(PORT_GPIO_CH_29_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch29Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch29Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_29);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_29_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch30Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_30
********************************************************************************/
#if defined(PORT_GPIO_CH_30_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch30Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch30Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_30);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_30_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch31Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_31
********************************************************************************/
#if defined(PORT_GPIO_CH_31_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch31Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch31Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_31);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_31_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch32Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_32
********************************************************************************/
#if defined(PORT_GPIO_CH_32_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch32Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch32Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_32);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_32_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch33Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_33
********************************************************************************/
#if defined(PORT_GPIO_CH_33_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch33Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch33Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_33);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_33_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch34Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_34
********************************************************************************/
#if defined(PORT_GPIO_CH_34_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch34Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch34Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_34);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_34_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch35Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_35
********************************************************************************/
#if defined(PORT_GPIO_CH_35_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch35Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch35Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_35);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_35_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch36Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_36
********************************************************************************/
#if defined(PORT_GPIO_CH_36_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch36Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch36Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_36);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_36_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch37Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_37
********************************************************************************/
#if defined(PORT_GPIO_CH_37_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch37Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch37Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_37);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_37_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch38Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_38
********************************************************************************/
#if defined(PORT_GPIO_CH_38_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch38Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch38Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_38);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_38_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch39Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_39
********************************************************************************/
#if defined(PORT_GPIO_CH_39_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch39Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch39Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_39);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_39_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch40Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_40
********************************************************************************/
#if defined(PORT_GPIO_CH_40_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch40Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch40Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_40);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_40_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch41Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_41
********************************************************************************/
#if defined(PORT_GPIO_CH_41_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch41Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch41Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_41);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_41_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch42Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_42
********************************************************************************/
#if defined(PORT_GPIO_CH_42_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch42Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch42Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_42);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_42_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch43Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_43
********************************************************************************/
#if defined(PORT_GPIO_CH_43_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch43Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch43Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_43);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_43_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch44Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_44
********************************************************************************/
#if defined(PORT_GPIO_CH_44_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch44Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch44Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_44);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_44_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch45Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_45
********************************************************************************/
#if defined(PORT_GPIO_CH_45_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch45Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch45Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_45);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_45_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch46Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_46
********************************************************************************/
#if defined(PORT_GPIO_CH_46_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch46Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch46Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_46);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_46_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch47Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_47
********************************************************************************/
#if defined(PORT_GPIO_CH_47_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch47Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch47Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_47);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_47_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch48Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_48
********************************************************************************/
#if defined(PORT_GPIO_CH_48_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch48Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch48Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_48);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_48_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch49Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_49
********************************************************************************/
#if defined(PORT_GPIO_CH_49_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch49Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch49Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_49);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_49_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch50Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_50
********************************************************************************/
#if defined(PORT_GPIO_CH_50_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch50Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch50Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_50);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_50_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch51Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_51
********************************************************************************/
#if defined(PORT_GPIO_CH_51_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch51Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch51Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_51);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_51_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch52Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_52
********************************************************************************/
#if defined(PORT_GPIO_CH_52_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch52Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch52Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_52);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_52_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch53Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_53
********************************************************************************/
#if defined(PORT_GPIO_CH_53_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch53Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch53Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_53);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_53_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch54Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_54
********************************************************************************/
#if defined(PORT_GPIO_CH_54_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch54Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch54Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_54);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_54_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch55Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_55
********************************************************************************/
#if defined(PORT_GPIO_CH_55_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch55Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch55Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_55);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_55_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch56Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_56
********************************************************************************/
#if defined(PORT_GPIO_CH_56_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch56Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch56Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_56);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_56_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch57Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_57
********************************************************************************/
#if defined(PORT_GPIO_CH_57_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch57Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch57Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_57);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_57_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch58Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_58
********************************************************************************/
#if defined(PORT_GPIO_CH_58_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch58Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch58Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_58);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_58_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch59Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_59
********************************************************************************/
#if defined(PORT_GPIO_CH_59_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch59Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch59Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_59);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_59_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch60Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_60
********************************************************************************/
#if defined(PORT_GPIO_CH_60_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch60Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch60Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_60);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_60_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch61Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_61
********************************************************************************/
#if defined(PORT_GPIO_CH_61_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch61Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch61Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_61);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_61_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch62Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_62
********************************************************************************/
#if defined(PORT_GPIO_CH_62_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch62Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch62Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_62);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_62_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch63Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_63
********************************************************************************/
#if defined(PORT_GPIO_CH_63_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch63Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch63Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_63);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_63_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch64Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_64
********************************************************************************/
#if defined(PORT_GPIO_CH_64_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch64Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch64Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_64);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_64_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch65Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_65
********************************************************************************/
#if defined(PORT_GPIO_CH_65_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch65Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch65Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_65);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_65_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch66Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_66
********************************************************************************/
#if defined(PORT_GPIO_CH_66_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch66Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch66Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_66);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_66_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch67Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_67
********************************************************************************/
#if defined(PORT_GPIO_CH_67_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch67Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch67Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_67);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_67_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch68Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_68
********************************************************************************/
#if defined(PORT_GPIO_CH_68_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch68Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch68Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_68);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_68_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch69Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_69
********************************************************************************/
#if defined(PORT_GPIO_CH_69_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch69Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch69Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_69);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_69_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch70Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_70
********************************************************************************/
#if defined(PORT_GPIO_CH_70_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch70Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch70Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_70);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_70_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch71Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_71
********************************************************************************/
#if defined(PORT_GPIO_CH_71_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch71Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch71Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_71);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_71_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch72Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_72
********************************************************************************/
#if defined(PORT_GPIO_CH_72_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch72Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch72Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_72);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_72_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch73Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_73
********************************************************************************/
#if defined(PORT_GPIO_CH_73_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch73Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch73Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_73);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_73_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch74Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_74
********************************************************************************/
#if defined(PORT_GPIO_CH_74_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch74Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch74Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_74);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_74_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch75Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_75
********************************************************************************/
#if defined(PORT_GPIO_CH_75_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch75Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch75Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_75);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_75_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch76Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_76
********************************************************************************/
#if defined(PORT_GPIO_CH_76_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch76Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch76Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_76);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_76_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch77Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_77
********************************************************************************/
#if defined(PORT_GPIO_CH_77_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch77Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch77Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_77);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_77_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch78Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_78
********************************************************************************/
#if defined(PORT_GPIO_CH_78_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch78Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch78Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_78);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_78_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch79Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_79
********************************************************************************/
#if defined(PORT_GPIO_CH_79_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch79Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch79Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_79);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_79_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch80Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_80
********************************************************************************/
#if defined(PORT_GPIO_CH_80_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch80Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch80Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_80);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_80_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch81Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_81
********************************************************************************/
#if defined(PORT_GPIO_CH_81_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch81Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch81Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_81);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_81_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch82Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_82
********************************************************************************/
#if defined(PORT_GPIO_CH_82_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch82Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch82Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_82);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_82_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch83Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_83
********************************************************************************/
#if defined(PORT_GPIO_CH_83_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch83Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch83Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_83);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_83_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch84Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_84
********************************************************************************/
#if defined(PORT_GPIO_CH_84_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch84Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch84Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_84);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_84_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch85Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_85
********************************************************************************/
#if defined(PORT_GPIO_CH_85_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch85Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch85Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_85);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_85_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch86Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_86
********************************************************************************/
#if defined(PORT_GPIO_CH_86_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch86Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch86Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_86);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_86_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch87Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_87
********************************************************************************/
#if defined(PORT_GPIO_CH_87_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch87Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch87Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_87);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_87_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch88Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_88
********************************************************************************/
#if defined(PORT_GPIO_CH_88_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch88Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch88Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_88);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_88_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch89Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_89
********************************************************************************/
#if defined(PORT_GPIO_CH_89_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch89Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch89Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_89);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_89_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch90Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_90
********************************************************************************/
#if defined(PORT_GPIO_CH_90_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch90Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch90Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_90);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_90_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch91Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_91
********************************************************************************/
#if defined(PORT_GPIO_CH_91_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch91Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch91Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_91);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_91_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch92Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_92
********************************************************************************/
#if defined(PORT_GPIO_CH_92_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch92Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch92Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_92);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_92_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch93Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_93
********************************************************************************/
#if defined(PORT_GPIO_CH_93_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch93Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch93Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_93);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_93_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch94Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_94
********************************************************************************/
#if defined(PORT_GPIO_CH_94_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch94Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch94Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_94);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_94_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch95Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_95
********************************************************************************/
#if defined(PORT_GPIO_CH_95_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch95Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch95Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_95);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_95_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch96Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_96
********************************************************************************/
#if defined(PORT_GPIO_CH_96_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch96Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch96Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_96);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_96_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch97Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_97
********************************************************************************/
#if defined(PORT_GPIO_CH_97_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch97Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch97Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_97);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_97_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch98Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_98
********************************************************************************/
#if defined(PORT_GPIO_CH_98_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch98Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch98Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_98);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_98_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch99Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_99
********************************************************************************/
#if defined(PORT_GPIO_CH_99_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch99Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch99Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_99);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_99_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch100Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_100
********************************************************************************/
#if defined(PORT_GPIO_CH_100_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch100Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch100Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_100);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_100_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch101Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_101
********************************************************************************/
#if defined(PORT_GPIO_CH_101_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch101Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch101Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_101);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_101_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch102Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_102
********************************************************************************/
#if defined(PORT_GPIO_CH_102_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch102Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch102Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_102);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_102_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch103Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_103
********************************************************************************/
#if defined(PORT_GPIO_CH_103_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch103Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch103Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_103);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_103_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch104Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_104
********************************************************************************/
#if defined(PORT_GPIO_CH_104_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch104Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch104Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_104);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_104_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch105Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_105
********************************************************************************/
#if defined(PORT_GPIO_CH_105_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch105Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch105Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_105);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_105_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch106Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_106
********************************************************************************/
#if defined(PORT_GPIO_CH_106_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch106Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch106Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_106);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_106_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch107Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_107
********************************************************************************/
#if defined(PORT_GPIO_CH_107_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch107Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch107Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_107);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_107_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch108Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_108
********************************************************************************/
#if defined(PORT_GPIO_CH_108_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch108Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch108Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_108);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_108_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch109Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_109
********************************************************************************/
#if defined(PORT_GPIO_CH_109_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch109Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch109Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_109);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_109_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch110Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_110
********************************************************************************/
#if defined(PORT_GPIO_CH_110_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch110Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch110Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_110);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_110_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch111Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_111
********************************************************************************/
#if defined(PORT_GPIO_CH_111_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch111Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch111Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_111);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_111_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch112Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_112
********************************************************************************/
#if defined(PORT_GPIO_CH_112_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch112Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch112Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_112);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_112_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch113Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_113
********************************************************************************/
#if defined(PORT_GPIO_CH_113_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch113Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch113Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_113);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_113_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch114Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_114
********************************************************************************/
#if defined(PORT_GPIO_CH_114_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch114Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch114Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_114);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_114_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch115Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_115
********************************************************************************/
#if defined(PORT_GPIO_CH_115_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch115Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch115Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_115);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_115_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch116Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_116
********************************************************************************/
#if defined(PORT_GPIO_CH_116_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch116Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch116Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_116);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_116_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch117Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_117
********************************************************************************/
#if defined(PORT_GPIO_CH_117_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch117Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch117Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_117);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_117_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch118Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_118
********************************************************************************/
#if defined(PORT_GPIO_CH_118_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch118Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch118Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_118);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_118_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch119Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_119
********************************************************************************/
#if defined(PORT_GPIO_CH_119_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch119Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch119Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_119);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_119_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch120Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_120
********************************************************************************/
#if defined(PORT_GPIO_CH_120_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch120Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch120Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_120);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_120_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch121Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_121
********************************************************************************/
#if defined(PORT_GPIO_CH_121_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch121Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch121Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_121);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_121_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch122Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_122
********************************************************************************/
#if defined(PORT_GPIO_CH_122_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch122Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch122Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_122);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_122_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch123Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_123
********************************************************************************/
#if defined(PORT_GPIO_CH_123_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch123Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch123Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_123);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_123_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch124Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_124
********************************************************************************/
#if defined(PORT_GPIO_CH_124_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch124Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch124Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_124);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_124_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch125Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_125
********************************************************************************/
#if defined(PORT_GPIO_CH_125_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch125Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch125Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_125);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_125_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch126Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_126
********************************************************************************/
#if defined(PORT_GPIO_CH_126_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch126Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch126Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_126);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_126_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch127Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_127
********************************************************************************/
#if defined(PORT_GPIO_CH_127_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch127Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch127Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_127);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_127_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch128Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_128
********************************************************************************/
#if defined(PORT_GPIO_CH_128_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch128Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch128Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_128);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_128_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch129Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_129
********************************************************************************/
#if defined(PORT_GPIO_CH_129_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch129Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch129Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_129);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_129_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch130Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_130
********************************************************************************/
#if defined(PORT_GPIO_CH_130_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch130Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch130Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_130);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_130_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch131Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_131
********************************************************************************/
#if defined(PORT_GPIO_CH_131_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch131Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch131Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_131);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_131_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch132Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_132
********************************************************************************/
#if defined(PORT_GPIO_CH_132_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch132Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch132Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_132);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_132_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch133Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_133
********************************************************************************/
#if defined(PORT_GPIO_CH_133_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch133Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch133Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_133);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_133_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch134Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_134
********************************************************************************/
#if defined(PORT_GPIO_CH_134_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch134Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch134Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_134);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_134_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch135Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_135
********************************************************************************/
#if defined(PORT_GPIO_CH_135_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch135Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch135Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_135);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_135_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch136Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_136
********************************************************************************/
#if defined(PORT_GPIO_CH_136_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch136Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch136Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_136);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_136_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch137Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_137
********************************************************************************/
#if defined(PORT_GPIO_CH_137_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch137Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch137Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_137);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_137_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch138Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_138
********************************************************************************/
#if defined(PORT_GPIO_CH_138_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch138Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch138Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_138);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_138_ACTIVE) **/

/*******************************************************************************
Function name : Port_Ch139Isr
Description   : ISR calls Notification function if interrupt occurred on
                PORT_GPIO_CH_139
********************************************************************************/
#if defined(PORT_GPIO_CH_139_ACTIVE)

MCAL_INTERRUPT_ATTRIBUTE
#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))
void Port_Ch139Isr(void)
#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)
ISR(Port_Ch139Isr)
#endif
{
#if (STD_ON == PORT_ENABLE_INTR_API)
    Port_GpioPinNotificationISR(PORT_GPIO_CH_139);
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
}

#endif /** #if defined(PORT_GPIO_CH_138_ACTIVE) **/

#define PORT_STOP_SEC_ISR_CODE
#include "Port_MemMap.h"

/*******************************************************************************
 *  END OF FILE: Port_Irq.c
 *******************************************************************************/
