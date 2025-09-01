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
 *  \file     Pwm.c
 *
 *  \brief    This file includes services for initialization and control of the
 *            PWM unit (pulse width modulation).
 *            The PWM module generates pulses with variable pulse width.It
 *            allows the selection of the duty cycle and the signal period time.
 *
 */

/* Common Design ID's */
/*
 *Design: MCAL-13120,MCAL-13125,MCAL-19512,MCAL-13127
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*
 *Design: MCAL-13122
 */
#include "Pwm.h"
#include "SchM_Pwm.h"
#if (STD_ON == PWM_DEV_ERROR_DETECT)
#include "Det.h"
#endif

#include "Pwm_Irq.h"
#include "Pwm_Priv.h"

/* There are static inline functions in hw_types.h file. Map them as well */
#include "hw_types.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((PWM_AR_RELEASE_MAJOR_VERSION != (4U)) || (PWM_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (PWM_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Pwm: AUTOSAR Version Numbers of Pwm are different!!"
#endif

/* AUTOSAR SW version information check has to match definition in header file */
#if ((PWM_SW_MAJOR_VERSION != (10U)) || (PWM_SW_MINOR_VERSION != (2U)) || (PWM_SW_PATCH_VERSION != (0U)))
#error "Pwm: Software Version Numbers are inconsistent!!"
#endif

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

#define PWM_START_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"
/** \brief Pwm driver init status */
volatile VAR(uint8, PWM_VAR_INIT) Pwm_DrvStatus = PWM_STATUS_UNINIT;
#define PWM_STOP_SEC_VAR_INIT_8
#include "Pwm_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define PWM_START_SEC_CODE
#include "Pwm_MemMap.h"

/* Initializes PWM unit and sets default period and duty cycle values from
 * parameter ConfigPtr.
 */

/*
 *Design:
 *MCAL-13154,MCAL-13155,MCAL-13156,MCAL-13157,MCAL-13158,MCAL-13159,MCAL-13160,MCAL-13161,MCAL-13162,MCAL-13163,MCAL-13164
 */

FUNC(void, PWM_CODE) Pwm_Init(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) CfgPtr)
{
    Std_ReturnType        ret_val   = E_OK;
    const Pwm_ConfigType *ConfigPtr = (Pwm_ConfigType *)NULL_PTR;

#if (STD_ON == PWM_PRE_COMPILE_VARIANT)
    /* Check if, Config parameter is NULL */
    if (NULL_PTR == CfgPtr)
    {
        ConfigPtr = &PWM_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == PWM_PRE_COMPILE_VARIANT) */

#if (STD_ON == PWM_VARIANT_POST_BUILD)
    /* Check if, Config parameter is not NULL */
    if (NULL_PTR != CfgPtr)
    {
        /* Assigning passed module configuration to Config pointer incase of Post Build variant */
        ConfigPtr = CfgPtr;
    }
#endif

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_Init_Deterror(ConfigPtr);
#endif /*(STD_ON == PWM_DEV_ERROR_DETECT) */

    if (ret_val == E_OK)
    {
        /* Init the PWM Peripheral. */
        Pwm_SystemInit(ConfigPtr);

#if (STD_ON == PWM_DEV_ERROR_DETECT)
        /* Change the Status. */
        Pwm_DrvStatus = PWM_STATUS_INIT;
#endif
    }
    else
    {
        /* do nothing */
    }
    return;
}

/*
 *Design: MCAL-13165,MCAL-13166,MCAL-13167,MCAL-13168,MCAL-13169,MCAL-13170
 */
#if (STD_ON == PWM_DEINIT_API)
FUNC(void, PWM_CODE) Pwm_DeInit(void)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_Deinit_Deterror();
#endif

    /* Check for DET Error */
    if (ret_val == E_OK)
    {
        Pwm_SystemDeInit();
    }
    else
    {
        /*do nothing*/
    }

    return;
}
#endif /*(STD_ON == PWM_DEINIT_API)*/

/*
 *Design:
 *MCAL-13172,MCAL-13173,MCAL-13174,MCAL-13175,MCAL-13176,MCAL-13177,MCAL-13178,MCAL-13179,MCAL-13143,MCAL-13144
 */
#if (STD_ON == PWM_SET_DUTY_CYCLE_API)
/*  Sets parameter DutyCycle as new duty cycle for channel ChannelNumber.
 *  DutyCycle is a percentage of the period with 0x8000 being equivalent
 *  to 100%.
 */
FUNC(void, PWM_CODE) Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_SetDutyCycle_Deterror(ChannelNumber, DutyCycle);
#endif

    /* Check for DET Error */
    if (ret_val == E_OK)
    {
        /* Enter Critical Section. */
        SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Change the duty cycle. */
        Pwm_SystemSetDutyCycle_Internal(ChannelNumber, DutyCycle);

        /* Exit Critical Section. */
        SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
    else
    {
        /*do nothing */
    }

    return;
}

#endif /*(STD_ON == PWM_SET_DUTY_CYCLE_API)*/

/*
 *Design: MCAL-13180,MCAL-13181,MCAL-19532,MCAL-13182,MCAL-13183,MCAL-13184,MCAL-13185,MCAL-13186
 */
#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
/*  Sets DutyCycle and Period of ChannelNumber. DutyCycle is a percentage of
 *  the period with 0x8000 being equivalent to 100%. */
FUNC(void, PWM_CODE)
Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_SetPeriodAndDuty_Deterror(ChannelNumber, DutyCycle);
#endif /* (STD_ON == PWM_DEV_ERROR_DETECT) */

    if (ret_val == E_OK)
    {
        /* Enter Critical Section. */
        SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Period passed here is in unit ticks */
        Pwm_SystemSetPeriodAndDuty(ChannelNumber, Period, DutyCycle);

        /* Exit Critical Section. */
        SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
    else
    {
        /*do nothing */
    }
    return;
}
#endif /*(STD_ON == PWM_SET_PERIOD_AND_DUTY_API)*/

/*
 *Design: MCAL-13187,MCAL-13188,MCAL-13189,MCAL-13190,MCAL-19533,MCAL-19534,MCAL-19535
 */
#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
/* Sets output state immediately to idle level. */
FUNC(void, PWM_CODE) Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_SetOutputToIdle_Deterror(ChannelNumber);
#endif /* (STD_ON == PWM_DEV_ERROR_DETECT) */

    /* Check for DET Error. */
    if (ret_val == E_OK)
    {
        /* Enter Critical Section. */
        SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Set output to idle state */
        Pwm_SystemSetOutputToIdle(ChannelNumber);

        /* Exit Critical Section. */
        SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
    else
    {
        /*do nothing */
    }
}
#endif /*(STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)*/

/*
 *Design: MCAL-13191,MCAL-13192,MCAL-13193,MCAL-13194,MCAL-13205,MCAL-19566,MCAL-13207
 */
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
/* Disables notification for channel ChannelNumber. */
FUNC(void, PWM_CODE) Pwm_DisableNotification(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_DisableNotify_Deterror(ChannelNumber);
#endif /* (STD_ON == PWM_DEV_ERROR_DETECT) */

    /* Check for DET error. */
    if (ret_val == E_OK)
    {
        /* Enter Critical Section. */
        SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Disable the Notification. */
        Pwm_SystemDisableNotification(ChannelNumber);

        /* Exit Critical Section. */
        SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
    else
    {
        /*do nothing */
    }
}
#endif /* #if (STD_ON == PWM_NOTIFICATION_SUPPORTED)*/

/*
 *Design: MCAL-13195,MCAL-13196,MCAL-13197,MCAL-13198,MCAL-13199,MCAL-13203,MCAL-13204,MCAL-13206
 */
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
/* Enables notification for Channel. */
FUNC(void, PWM_CODE)
Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_EnableNotify_Deterror(ChannelNumber);
#endif /* #if (STD_ON == PWM_DEV_ERROR_DETECT)*/

    /* Check for DET error. */
    if (ret_val == E_OK)
    {
        /* Enter Critical Section. */
        SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Enable the Notification. */
        Pwm_SystemEnableNotification(ChannelNumber, Notification);

        /* Exit Critical Section. */
        SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
    else
    {
        /*do nothing */
    }
    return;
}
#endif

/*
 *Design: MCAL-13619,MCAL-13620,MCAL-19536,MCAL-19537,MCAL-13621
 */
#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
/* Returns the output state of Channel, if supported. */
FUNC(Pwm_OutputStateType, PWM_CODE) Pwm_GetOutputState(Pwm_ChannelType ChannelNumber)
{
    Pwm_OutputStateType Output_Level = PWM_LOW;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    Std_ReturnType ret_val = E_OK;
#endif

/* check driver state */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_GetOutputstate_Deterror(ChannelNumber);
#endif

    /* Check for DET error. */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (ret_val == E_OK)
#endif
    {
        Output_Level = Pwm_SystemGetOutputState(ChannelNumber);
    }

    /* Return the Value. */
    return Output_Level;
}
#endif

/*
 *Design: MCAL-21284,MCAL-21285,MCAL-21286
 */
#if (STD_ON == PWM_REGISTER_READBACK_API) || (STD_ON == PWM_SAFETI_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_RegisterReadback(Pwm_ChannelType PwmChannel, P2VAR(Pwm_RegisterReadbackType, AUTOMATIC, PWM_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    /* HW unit ID is the index, so search for matching HW unit */

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    retVal = Pwm_HwRegReadback_Deterror(PwmChannel, RegRbPtr);
#endif

    /* Check if return value is correct. */
    if (retVal == E_OK)
    {
        /* Readback the register. */
        Pwm_HwRegisterReadback(RegRbPtr, PwmChannel);
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    /* Return the Value. */
    return (retVal);
}
#endif

/*
 *Design: MCAL-13200
 */
#if (STD_ON == PWM_VERSION_INFO_API)
FUNC(void, PWM_CODE)
Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA) VersionInfoPtr)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    ret_val = Pwm_GetVersionInfo_Deterror(VersionInfoPtr);
#endif

    /* Check for DET error. */
    if (ret_val == E_OK)
    {
        VersionInfoPtr->vendorID         = PWM_VENDOR_ID;
        VersionInfoPtr->moduleID         = PWM_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)PWM_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)PWM_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)PWM_SW_PATCH_VERSION;
    }
    else
    {
        /*do nothing */
    }

    return;
}
#endif /* PWM_VERSION_INFO_API*/

#define PWM_STOP_SEC_CODE
#include "Pwm_MemMap.h"
