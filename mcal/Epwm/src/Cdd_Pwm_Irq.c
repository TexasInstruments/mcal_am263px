/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
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
 *  \file     Cdd_Pwm_Irq.c
 *
 *  \brief    This file contains the ISR implementation of CDD PWM MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Pwm_Priv.h"
#include "Cdd_Pwm_Irq.h"

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
extern VAR(Cdd_Pwm_ChannelType, CDD_PWM_VAR_NO_INIT) Cdd_Pwm_IsrIndex[CDD_PWM_HW_MAX_NUM_CHANNELS];
extern volatile VAR(uint8, CDD_PWM_VAR_INIT) Cdd_Pwm_DrvStatus;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CDD_PWM_START_SEC_ISR_CODE
#include "Cdd_Pwm_MemMap.h"

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch0Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50000000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_0);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch1Isr)
#endif
{
    uint32              baseAddr  = 0x50001000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_1);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch2Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50002000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_2);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch3Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50003000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_3);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch4Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50004000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_4);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch5Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50005000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_5);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch6Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50006000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_6);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch7Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50007000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_7);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch8Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50008000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_8);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch9Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50009000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_9);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch10Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5000a000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_10);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch11Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5000b000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_11);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch12Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5000c000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_12);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch13Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5000d000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_13);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch14Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5000e000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_14);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch15Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5000f000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_15);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch16Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50010000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_16);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch17Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50011000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_17);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch18Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50012000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_18);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch19Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50013000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_19);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch20Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50014000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_20);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch21Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50015000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_21);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch22Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50016000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_22);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch23Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50017000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_23);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch24Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50018000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_24);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch25Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50019000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_25);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch26Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5001a000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_26);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch27Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5001b000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_27);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch28Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5001c000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_28);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch29Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5001d000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_29);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch30Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5001e000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_30);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_Ch31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_Ch31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_Ch31Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5001f000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_31);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch0Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50040000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_0);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch1Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50041000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_1);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch2Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50042000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_2);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch3Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50043000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_3);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch4Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50044000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_4);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch5Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50045000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_5);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch6Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50046000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_6);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch7Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50047000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_7);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch8Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50048000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_8);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch9Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50049000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_9);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch10Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5004a000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_10);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch11Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5004b000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_11);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch12Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5004c000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_12);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch13Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5004d000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_13);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch14Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5004e000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_14);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch15Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5004f000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_15);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch16Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50050000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_16);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch17Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50051000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_17);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch18Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50052000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_18);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch19Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50053000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;

    ChannelID = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_19);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch20Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50054000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_20);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch21Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50055000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_21);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch22Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50056000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_22);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch23Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50057000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_23);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch24Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50058000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_24);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch25Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50059000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_25);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch26Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5005a000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_26);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch27Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5005b000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_27);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch28Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5005c000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_28);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch29Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5005d000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_29);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch30Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5005e000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_30);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_Ch31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_Ch31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_Ch31Isr)
#endif
{
    /*TI_INSPECTED 91 D : MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5005f000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_31);

    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch0Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50080000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_0);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch1Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50081000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_1);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch2Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50082000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_2);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch3Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50083000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_3);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch4Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50084000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_4);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch5Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50085000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_5);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch6Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50086000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_6);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch7Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50087000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_7);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch8Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50088000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_8);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch9Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50089000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_9);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch10Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5008a000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_10);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch11Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5008b000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_11);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch12Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5008c000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_12);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch13Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5008d000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_13);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch14Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5008e000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_14);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch15Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5008f000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_15);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch16Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50090000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_16);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch17Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50091000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_17);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch18Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50092000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_18);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch19Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50093000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_19);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch20Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50094000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_20);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch21Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50095000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_21);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch22Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50096000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_22);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch23Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50097000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_23);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch24Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50098000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_24);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch25Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x50099000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_25);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch26Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5009a000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_26);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch27Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5009b000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_27);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch28Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5009c000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_28);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch29Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5009d000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_29);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch30Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5009e000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_30);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_Ch31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_Ch31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_Ch31Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x5009f000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_31);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch0Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c0000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_0);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch1Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c1000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_1);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch2Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c2000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_2);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch3Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c3000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_3);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch4Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c4000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_4);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch5Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c5000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_5);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch6Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c6000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_6);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch7Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c7000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_7);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch8Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c8000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_8);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch9Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500c9000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_9);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch10Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500ca000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_10);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch11Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500cb000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_11);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch12Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500cc000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_12);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch13Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500cd000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_13);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch14Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500ce000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_14);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch15Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500cf000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_15);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch16Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d0000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_16);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch17Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d1000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_17);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch18Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d2000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_18);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch19Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d3000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_19);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch20Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d4000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_20);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch21Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d5000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_21);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch22Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d6000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_22);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch23Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d7000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_23);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch24Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d8000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_24);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch25Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500d9000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_25);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch26Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500da000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_26);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch27Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500db000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_27);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch28Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500dc000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_28);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch29Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500dd000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_29);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch30Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500de000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_30);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_Ch31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_Ch31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_Ch31Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32              baseAddr  = 0x500df000U;
    Cdd_Pwm_ChannelType ChannelID = 0U;
    ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_31);
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableInterrupt(ChannelID);
        EPWM_clearEventTriggerInterruptFlag(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh0Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50000000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_0);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh1Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50001000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_1);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh2Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50002000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_2);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh3Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50003000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_3);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh4Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50004000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_4);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh5Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50005000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_5);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh6Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50006000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_6);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh7Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50007000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_7);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh8Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50008000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_8);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh9Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50009000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_9);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh10Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000a000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_10);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh11Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000b000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_11);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh12Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000c000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_12);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh13Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000d000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_13);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh14Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000e000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_14);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh15Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5000f000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_15);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh16Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50010000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_16);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh17Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50011000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_17);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh18Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50012000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_18);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh19Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50013000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_19);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh20Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50014000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_20);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh21Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50015000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_21);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh22Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50016000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_22);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh23Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50017000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_23);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh24Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50018000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_24);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh25Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50019000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_25);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh26Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001a000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_26);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh27Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001b000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_27);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh28Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001c000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_28);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh29Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001d000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_29);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh30Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001e000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_30);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G0_TzCh31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G0_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G0_TzCh31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G0_TzCh31Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5001f000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G0, CDD_PWM_CHANNEL_31);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh0Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50040000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_0);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh1Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50041000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_1);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh2Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50042000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_2);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh3Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50043000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_3);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh4Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50044000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_4);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh5Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50045000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_5);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh6Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50046000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_6);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh7Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50047000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_7);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh8Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50048000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_8);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh9Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50049000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_9);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh10Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004a000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_10);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh11Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004b000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_11);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh12Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004c000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_12);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh13Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004d000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_13);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh14Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004e000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_14);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh15Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5004f000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_15);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh16Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50050000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_16);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh17Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50051000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_17);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh18Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50052000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_18);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh19Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50053000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_19);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh20Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50054000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_20);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh21Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50055000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_21);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh22Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50056000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_22);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh23Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50057000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_23);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh24Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50058000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_24);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh25Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50059000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_25);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh26Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005a000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_26);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh27Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005b000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_27);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh28Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005c000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_28);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh29Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005d000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_29);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh30Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005e000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_30);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G1_TzCh31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G1_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G1_TzCh31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G1_TzCh31Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5005f000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G1, CDD_PWM_CHANNEL_31);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh0Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50080000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_0);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh1Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50081000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_1);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh2Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50082000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_2);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh3Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50083000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_3);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh4Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50084000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_4);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh5Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50085000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_5);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh6Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50086000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_6);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh7Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50087000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_7);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh8Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50088000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_8);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh9Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50089000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_9);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh10Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008a000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_10);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh11Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008b000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_11);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh12Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008c000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_12);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh13Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008d000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_13);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh14Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008e000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_14);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh15Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5008f000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_15);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh16Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50090000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_16);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh17Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50091000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_17);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh18Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50092000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_18);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh19Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50093000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_19);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh20Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50094000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_20);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh21Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50095000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_21);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh22Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50096000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_22);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh23Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50097000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_23);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh24Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50098000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_24);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh25Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x50099000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_25);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh26Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009a000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_26);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh27Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009b000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_27);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh28Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009c000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_28);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh29Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009d000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_29);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh30Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009e000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_30);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G2_TzCh31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G2_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G2_TzCh31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G2_TzCh31Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x5009f000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G2, CDD_PWM_CHANNEL_31);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh0Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_0
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh0Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh0Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c0000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_0);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh1Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_1
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh1Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh1Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c1000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_1);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh2Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_2
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh2Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh2Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c2000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_2);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh3Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_3
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh3Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh3Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c3000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_3);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh4Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_4
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh4Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh4Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c4000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_4);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh5Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_5
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh5Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh5Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c5000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_5);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh6Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_6
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh6Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh6Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c6000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_6);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh7Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_7
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh7Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh7Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c7000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_7);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh8Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_8
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh8Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh8Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c8000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_8);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh9Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_9
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh9Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh9Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500c9000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_9);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh10Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_10
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh10Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh10Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500ca000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_10);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh11Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_11
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh11Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh11Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500cb000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_11);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh12Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_12
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh12Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh12Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500cc000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_12);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh13Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_13
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh13Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh13Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500cd000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_13);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh14Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_14
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh14Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh14Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500ce000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_14);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh15Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_15
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh15Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh15Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500cf000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_15);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh16Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_16
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh16Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh16Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d0000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_16);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh17Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_17
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh17Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh17Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d1000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_17);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh18Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_18
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh18Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh18Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d2000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_18);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh19Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_19
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh19Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh19Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d3000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_19);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh20Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_20
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh20Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh20Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d4000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_20);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh21Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_21
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh21Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh21Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d5000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_21);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh22Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_22
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh22Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh22Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d6000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_22);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh23Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_23
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh23Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh23Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d7000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_23);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh24Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_24
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh24Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh24Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d8000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_24);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh25Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_25
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh25Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh25Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500d9000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_25);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh26Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_26
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh26Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh26Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500da000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_26);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh27Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_27
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh27Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh27Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500db000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_27);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh28Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_28
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh28Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh28Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500dc000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_28);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh29Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_29
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh29Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh29Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500dd000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_29);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh30Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_30
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh30Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh30Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500de000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_30);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

/**********************************************************************************************************************
    Function name:  Cdd_Pwm_G3_TzCh31Isr
**********************************************************************************************************************/
#if defined CDD_PWM_G3_CHANNEL_31
#if defined(CLANG)
MCAL_INTERRUPT_ATTRIBUTE
#endif
#if ((CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT1) || (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_VOID))
void Cdd_Pwm_G3_TzCh31Isr(void)
#elif (CDD_PWM_ISR_TYPE == CDD_PWM_ISR_CAT2)
ISR(Cdd_Pwm_G3_TzCh31Isr)
#endif
{
    /* MISRAC_2012_R.17.7
     * "Reason - Tool Issue, baseAddr is used in this function only " */
    uint32 baseAddr = 0x500df000U;
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        /* Disable and Clear Interrupt */
        Cdd_Pwm_DisableTzInt(baseAddr);
    }
    else
    {
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChannelType ChannelID = 0U;
        ChannelID                     = CDD_PWM_CHANNEL_ID(CDD_PWM_CONTROLSS_G3, CDD_PWM_CHANNEL_31);
        Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_IsrIndex[ChannelID]);
#endif
    }
}
#endif

#define CDD_PWM_STOP_SEC_ISR_CODE
#include "Cdd_Pwm_MemMap.h"
