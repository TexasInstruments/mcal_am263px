/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Pwm_Irq.c
 *
 *  \brief    This file contains the ISR implementation of PWM MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*
 *Design: MCAL-13124
 */
#include "Pwm_Priv.h"
#include "Pwm_Irq.h"

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
extern VAR(uint16, PWM_VAR_NO_INIT) Pwm_IsrIndex[PWM_HW_MAX_NUM_CHANNELS];
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define PWM_START_SEC_ISR_CODE
#include "Pwm_MemMap.h"

/**********************************************************************************************************************
    Function name:  Pwm_Ch0Isr
    Description: The Channel0 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch0Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch0Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50000000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[0U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch1Isr
    Description: The Channel1 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch1Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch1Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50001000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[1U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch2Isr
    Description: The Channel2 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch2Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch2Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50002000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)

        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[2U]);
#endif
    }
}
/**********************************************************************************************************************
    Function name:  Pwm_Ch3Isr
    Description: The Channel3 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch3Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch3Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50003000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[3U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch4Isr
    Description: The Channel4 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch4Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch4Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50004000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[4U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch5Isr
    Description: The Channel5 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch5Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch5Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50005000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[5U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch6Isr
    Description: The Channel6 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch6Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch6Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50006000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[6U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch7Isr
    Description: The Channel7 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch7Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch7Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50007000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[7U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch8Isr
    Description: The Channel8 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch8Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch8Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50008000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[8U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch9Isr
    Description: The Channel9 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch9Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch9Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50009000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[9U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch10Isr
    Description: The Channel10 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch10Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch10Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000A000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[10U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch11Isr
    Description: The Channel11 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch11Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch11Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000B000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[11U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch12Isr
    Description: The Channel12 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch12Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch12Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000C000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[12U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch13Isr
    Description: The Channel13 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch13Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch13Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000D000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[13U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch14Isr
    Description: The Channel14 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch14Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch14Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000E000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[14U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch15Isr
    Description: The Channel15 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch15Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch15Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000F000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[15U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch16Isr
    Description: The Channel16 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch16Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch16Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50010000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[16U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch17Isr
    Description: The Channel17 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch17Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch17Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50011000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[17U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch18Isr
    Description: The Channel18 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch18Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch18Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50012000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[18U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch19Isr
    Description: The Channel19 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch19Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch19Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50013000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[19U]);
#endif
    }
}

#if !defined(AM261X_PLATFORM)

/**********************************************************************************************************************
    Function name:  Pwm_Ch20Isr
    Description: The Channel20 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch20Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch20Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50014000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[20U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch21Isr
    Description: The Channel21 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch21Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch21Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50015000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[21U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch22Isr
    Description: The Channel22 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch22Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch22Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50016000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[22U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch23Isr
    Description: The Channel23 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch23Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch23Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50017000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[23U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch24Isr
    Description: The Channel24 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch24Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch24Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50018000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[24U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch25Isr
    Description: The Channel25 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch25Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch25Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50019000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[25U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch26Isr
    Description: The Channel26 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch26Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch26Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001A000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[26U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch27Isr
    Description: The Channel Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch27Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch27Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001B000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[27U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch28Isr
    Description: The Channel28 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch28Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch28Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001C000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[28U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch29Isr
    Description: The Channel29 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch29Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch29Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001D000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[29U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch30Isr
    Description: The Channel30 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch30Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch30Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001E000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[30U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch31Isr
    Description: The Channel31 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch31Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch31Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001F000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[31U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch32Isr
    Description: The Channel32 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch32Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch32Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50040000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[32U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch33Isr
    Description: The Channel33 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch33Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch33Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50041000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[33U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch34Isr
    Description: The Channel34 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch34Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch34Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50042000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[34U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch35Isr
    Description: The Channel35 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch35Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch35Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50043000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[35U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch36Isr
    Description: The Channel36 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch36Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch36Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50044000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[36U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch37Isr
    Description: The Channel37 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/

MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch37Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch37Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50045000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[37U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch38Isr
    Description: The Channel38 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch38Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch38Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50046000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[38U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch39Isr
    Description: The Channel39 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch39Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch39Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50047000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[39U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch40Isr
    Description: The Channel40 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch40Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch40Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50048000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[40U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch41Isr
    Description: The Channel41 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch41Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch41Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50049000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[41U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch42Isr
    Description: The Channel42 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch42Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch42Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004A000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[42U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch43Isr
    Description: The Channel43 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch43Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch43Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004B000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[43U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch44Isr
    Description: The Channel44 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch44Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch44Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004C000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[44U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch45Isr
    Description: The Channel45 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch45Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch45Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004D000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[45U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch46Isr
    Description: The Channel46 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch46Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch46Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004E000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[46U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch47Isr
    Description: The Channel47 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch47Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch47Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004F000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[47U]);
#endif
    }
}
/**********************************************************************************************************************
    Function name:  Pwm_Ch48Isr
    Description: The Channel48 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch48Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch48Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50050000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[48U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch49Isr
    Description: The Channel49 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch49Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch49Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50051000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[49U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch50Isr
    Description: The Channel50 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch50Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch50Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50052000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[50U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch51Isr
    Description: The Channel51 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch51Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch51Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50053000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[51U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch52Isr
    Description: The Channel52 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch52Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch52Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50054000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[52U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch53Isr
    Description: The Channel53 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch53Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch53Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50055000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[53U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch54Isr
    Description: The Channel54 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch54Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch54Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50056000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[54U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch55Isr
    Description: The Channel55 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch55Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch55Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50057000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[55U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch56Isr
    Description: The Channel56 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch56Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch56Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50058000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[56U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch57Isr
    Description: The Channel57 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch57Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch57Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50059000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[57U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch58Isr
    Description: The Channel58 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch58Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch58Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005A000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[58U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch59Isr
    Description: The Channel59 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch59Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch59Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005B000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[59U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch60Isr
    Description: The Channel60 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch60Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch60Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005C000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[60U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch61Isr
    Description: The Channel61 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch61Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch61Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005D000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[61U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch62Isr
    Description: The Channel62 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch62Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch62Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005E000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[62U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch63Isr
    Description: The Channel63 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch63Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch63Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005F000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[63U]);
#endif
    }
}
/**********************************************************************************************************************
    Function name:  Pwm_Ch64Isr
    Description: The Channel64 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch64Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch64Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50080000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[64U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch65Isr
    Description: The Channel65 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch65Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch65Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50081000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[65U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch66Isr
    Description: The Channel66 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch66Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch66Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50082000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[66U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch67Isr
    Description: The Channel67 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch67Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch67Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50083000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[67U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch68Isr
    Description: The Channel68 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch68Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch68Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50084000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[68U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch69Isr
    Description: The Channel69 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch69Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch69Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50085000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[69U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch70Isr
    Description: The Channel70 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch70Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch70Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50086000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[70U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch71Isr
    Description: The Channel71 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch71Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch71Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50087000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[71U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch72Isr
    Description: The Channel72 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch72Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch72Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50088000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[72U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch73Isr
    Description: The Channel73 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch73Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch73Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50089000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[73U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch74Isr
    Description: The Channel174 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch74Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch74Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008A000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[74U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch75Isr
    Description: The Channel75 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch75Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch75Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008B000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[75U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch76Isr
    Description: The Channel76 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch76Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch76Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008C000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[76U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch77Isr
    Description: The Channel77 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch77Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch77Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008D000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[77U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch78Isr
    Description: The Channel78 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch78Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch78Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008E000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[78U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch79Isr
    Description: The Channel79 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch79Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch79Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008F000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[79U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch80Isr
    Description: The Channel80 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch80Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch80Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50090000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[80U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch81Isr
    Description: The Channel81 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch81Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch81Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50091000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[81U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch82Isr
    Description: The Channel82 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch82Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch82Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50092000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[82U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch83Isr
    Description: The Channel83 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch83Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch83Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50093000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[83U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch84Isr
    Description: The Channel84 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch84Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch84Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50094000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[84U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch85Isr
    Description: The Channel85 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch85Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch85Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50095000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[85U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch86Isr
    Description: The Channel86 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch86Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch86Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50096000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[86U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch87Isr
    Description: The Channel87 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch87Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch87Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50097000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[87U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch88Isr
    Description: The Channel88 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch88Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch88Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50098000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[88U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch89Isr
    Description: The Channel89 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch89Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch89Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50099000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[89U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch90Isr
    Description: The Channel90 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch90Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch90Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009A000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[90U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch91Isr
    Description: The Channel91 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch91Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch91Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009B000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[91U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch92Isr
    Description: The Channel92 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch92Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch92Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009C000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[92U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch93Isr
    Description: The Channel93 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch93Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch93Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009D000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[93U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch94Isr
    Description: The Channel94 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch94Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch94Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009E000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[94U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch95Isr
    Description: The Channel95 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch95Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch95Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009F000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[95U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch96Isr
    Description: The Channel96 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch96Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch96Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C0000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[96U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch97Isr
    Description: The Channel97 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch97Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch97Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C1000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[97U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch98Isr
    Description: The Channel98 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch98Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch98Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C2000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[98U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch99Isr
    Description: The Channel99 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch99Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch99Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C3000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[99U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch100Isr
    Description: The Channel100 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch100Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch100Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C4000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[100U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch101Isr
    Description: The Channel101 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch101Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch101Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C5000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[101U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch102Isr
    Description: The Channel102 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch102Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch102Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C6000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[102U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch103Isr
    Description: The Channel103 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch103Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch103Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C7000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[103U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch104Isr
    Description: The Channel104 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch104Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch104Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C8000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[104U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch105Isr
    Description: The Channel105 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch105Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch105Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500C9000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[105U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch106Isr
    Description: The Channel106 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch106Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch106Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500CA000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[106U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch107Isr
    Description: The Channel107 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch107Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch107Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500CB000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[107U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch108Isr
    Description: The Channel108 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch108Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch108Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500CC000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[108U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch109Isr
    Description: The Channel109 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch109Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch109Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500CD000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[109U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch110Isr
    Description: The Channel110 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch110Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch110Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500CE000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[110U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch111Isr
    Description: The Channel111 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch111Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch111Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500CF000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[111U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch112Isr
    Description: The Channel112 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch112Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch112Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D0000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[112U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch113Isr
    Description: The Channel13 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch113Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch113Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D1000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[113U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch114Isr
    Description: The Channel114 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch114Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch114Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D2000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[114U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch115Isr
    Description: The Channel115 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch115Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch115Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D3000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[115U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch116Isr
    Description: The Channel116 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch116Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch116Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D4000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[116U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch117Isr
    Description: The Channel117 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch117Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch117Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D5000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[117U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch118Isr
    Description: The Channel118 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch118Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch118Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D6000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[118U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch119Isr
    Description: The Channel119 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch119Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch119Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D7000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[119U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch120Isr
    Description: The Channel120 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch120Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch120Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D8000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[120U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch121Isr
    Description: The Channel121 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch121Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch121Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500D9000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[121U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch122Isr
    Description: The Channel122 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch122Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch122Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500DA000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[122U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch123Isr
    Description: The Channel123 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch123Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch123Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500DB000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[123U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch124Isr
    Description: The Channel124 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch124Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch124Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500DC000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[124U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch125Isr
    Description: The Channel125 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch125Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch125Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500DD000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[125U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch126Isr
    Description: The Channel126 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch126Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch126Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500DE000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[126U]);
#endif
    }
}

/**********************************************************************************************************************
    Function name:  Pwm_Ch127Isr
    Description: The Channel127 Interrupt Subroutine calls Notification function depending on the
channel mode.
**********************************************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((PWM_ISR_TYPE == PWM_ISR_CAT1) || (PWM_ISR_TYPE == PWM_ISR_VOID))
void Pwm_Ch127Isr(void)
#elif (PWM_ISR_TYPE == PWM_ISR_CAT2)
ISR(Pwm_Ch127Isr)
#endif
{
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500DF000UL;
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Pwm_disableInterrupt_epwm(baseAddr);
    }
    else
#endif
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_ChannelNotificationISR_epwm(Pwm_IsrIndex[127U]);
#endif
    }
}

#endif

#define PWM_STOP_SEC_ISR_CODE
#include "Pwm_MemMap.h"
