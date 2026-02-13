/*
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
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
 * BUT NOT LIMITED TO, PRCDD_PWMREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Cdd_Pwm.c
 *
 *    This component provides services for initialization and control of
 *    the CDD_PWM unit (pulse width modulation).
 *    The CDD_PWM driver allows comparing and acting automatically
 *    when the value of a counter matches a defined threshold.
 *
 */

/* Common Design ID's */
/*
 *Design: MCAL-23870, MCAL-23871, MCAL-23872, MCAL-23873
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Pwm.h"
#include "SchM_Cdd_Pwm.h"
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "Cdd_Pwm_Irq.h"
#include "Cdd_Pwm_Priv.h"
#include "Cdd_Pwm_Cfg.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((CDD_PWM_AR_RELEASE_MAJOR_VERSION != (4U)) || (CDD_PWM_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (CDD_PWM_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Cdd_Pwm: AUTOSAR Version Numbers of Cdd_Pwm are different!!"
#endif

/* AUTOSAR SW version information check has to match definition in header file */
#if ((CDD_PWM_SW_MAJOR_VERSION != (10U)) || (CDD_PWM_SW_MINOR_VERSION != (2U)) || (CDD_PWM_SW_PATCH_VERSION != (0U)))
#error "Cdd_Pwm: Software Version Numbers are inconsistent!!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void Cdd_Pwm_InitIsr(const Cdd_Pwm_ConfigType *CfgPtr);
static void Cdd_Pwm_StartChannel(Cdd_Pwm_ChannelType ChannelNumber);
static void Cdd_Pwm_StartNotification(Cdd_Pwm_ChannelType ChannelParameter, Cdd_Pwm_InterruptType EdgeInterruptSource);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define CDD_PWM_START_SEC_VAR_INIT_8
#include "Cdd_Pwm_MemMap.h"
/** \brief Cdd_Pwm driver init status */
volatile VAR(uint8, CDD_PWM_VAR_INIT) Cdd_Pwm_DrvStatus = CDD_PWM_STATUS_UNINIT;
#define CDD_PWM_STOP_SEC_VAR_INIT_8
#include "Cdd_Pwm_MemMap.h"

#define CDD_PWM_START_SEC_VAR_NO_INIT_16
#include "Cdd_Pwm_MemMap.h"
/** \brief Cdd_Pwm driver interrupt index. */
VAR(Cdd_Pwm_ChannelType, CDD_PWM_VAR_NO_INIT) Cdd_Pwm_IsrIndex[CDD_PWM_HW_MAX_NUM_CHANNELS];
#define CDD_PWM_STOP_SEC_VAR_NO_INIT_16
#include "Cdd_Pwm_MemMap.h"

#define CDD_PWM_START_SEC_VAR_NO_INIT_32
#include "Cdd_Pwm_MemMap.h"
/** \brief CDD_PWM SFO Calibration status for each configured channel*/
VAR(uint32, CDD_PWM_VAR_NO_INIT) Cdd_Pwm_ChannelSfoStatus[CDD_PWM_MAX_NUM_CHANNELS];
#define CDD_PWM_STOP_SEC_VAR_NO_INIT_32
#include "Cdd_Pwm_MemMap.h"

#define CDD_PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Pwm_MemMap.h"
/** \brief CDD_PWM driver object. */
VAR(Cdd_Pwm_ChObjType, CDD_PWM_VAR_NO_INIT) Cdd_Pwm_ChObj[CDD_PWM_HW_MAX_NUM_CHANNELS];
#define CDD_PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Pwm_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_PWM_START_SEC_CODE
#include "Cdd_Pwm_MemMap.h"

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_Validate_Init(uint8 Sid)
{
    Std_ReturnType returnValue = E_OK;

    if (CDD_PWM_STATUS_UNINIT == Cdd_Pwm_DrvStatus)
    {
        /*
         * Cdd_Pwm module must not be initialized.
         * Otherwise call the Det with CDD_PWM_E_UNINIT
         */
        (void)Cdd_Pwm_reportDetError(Sid, CDD_PWM_E_UNINIT);
        returnValue = E_NOT_OK;
    }

    return (returnValue);
}
#endif

/* Initializes CDD_PWM unit and sets default period and duty cycle values from
 * parameter ConfigPtr.
 */
/*
 *Design: MCAL-23326, MCAL-23327, MCAL-23328, MCAL-23329, MCAL-23330, MCAL-23331, MCAL-23332,
 *MCAL-23333, MCAL-23371, MCAL-23370
 */
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_Init(P2CONST(Cdd_Pwm_ConfigType, AUTOMATIC, CDD_PWM_PBCFG) ConfigPtr)
{
    const Cdd_Pwm_ConfigType *CfgPtr = (Cdd_Pwm_ConfigType *)NULL_PTR;

#if (STD_ON == CDD_PWM_PRE_COMPILE_VARIANT)
    if (NULL_PTR == ConfigPtr)
    {
        CfgPtr = &CDD_PWM_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == CDD_PWM_PRE_COMPILE_VARIANT) */

#if (STD_ON == CDD_PWM_POST_BUILD_VARIANT)
    if (NULL_PTR != ConfigPtr)
    {
        CfgPtr = ConfigPtr;
    }
#endif /* (STD_ON == CDD_PWM_POST_BUILD_VARIANT) */

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (NULL_PTR == CfgPtr)
    {
        /*
         * ConfigPtr must not be NULL_PTR. In case it is NULL_PTR report an error and
         * return immediately.
         */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_INIT, CDD_PWM_E_INIT_FAILED);
    }
    else if (CDD_PWM_STATUS_INIT == Cdd_Pwm_DrvStatus)
    {
        /*
         * Cdd_Pwm module must not be initialized.
         * Otherwise call the Det with CDD_PWM_E_ALREADY_INITIALIZED
         */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_INIT, CDD_PWM_E_ALREADY_INITIALIZED);
    }
    else
#endif /*(STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        Cdd_Pwm_InitIsr(CfgPtr);
        Cdd_Pwm_DrvStatus = CDD_PWM_STATUS_INIT;
    }
    return;
}
static void Cdd_Pwm_InitIsr(const Cdd_Pwm_ConfigType *CfgPtr)
{
    uint32 chIdx, chnum;
    /* Reset the ISR Index. */
    for (chnum = 0U; chnum < (CDD_PWM_HW_MAX_NUM_CHANNELS); chnum++)
    {
        Cdd_Pwm_IsrIndex[chnum] = CDD_PWM_ISR_MAX;
    }

    /*  Align the ISR Index with HW channels configured. */
    for (chnum = 0U; chnum < (CDD_PWM_HW_MAX_NUM_CHANNELS); chnum++)
    {
        for (chIdx = 0U; chIdx < (CDD_PWM_MAX_NUM_CHANNELS); chIdx++)
        {
            if (chnum == CfgPtr->chCfg[chIdx].channelHwID)
            {
                Cdd_Pwm_IsrIndex[chnum] = (uint16)chIdx;
                break;
            }
        }
    }

    /* Only initialize configured resources */
    for (chIdx = 0U; chIdx < (CDD_PWM_MAX_NUM_CHANNELS); chIdx++)
    {
        /* Reset Channel object */
        Cdd_Pwm_resetChObj(&Cdd_Pwm_ChObj[chIdx]);

        /* Copy the configuration */
        Cdd_Pwm_copyConfig(&Cdd_Pwm_ChObj[chIdx], &CfgPtr->chCfg[chIdx]);

        /* Init the HW Channel */
        Cdd_Pwm_HwUnitInit(&Cdd_Pwm_ChObj[chIdx]);

/* The function Cdd_Pwm_Init shall disable all notifications */
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
        Cdd_Pwm_ChObj[chIdx].channelNotifyActiveFlag = CDD_PWM_FALSE;
#endif

        /* Change state to CDD_PWM_STATUS_INIT */
        Cdd_Pwm_ChObj[chIdx].channelState = CDD_PWM_STATUS_INIT;
    }

    /* Initialize the ISR. */
}

/*===============================================================================================*/
/*
 * Design: MCAL-23334, MCAL-23335, MCAL-23336, MCAL-23337, MCAL-23338
 */
#if (STD_ON == CDD_PWM_DEINIT_API)
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_DeInit(void)
{
    uint32 chIdx;
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_DEINIT))
#endif
    {
        for (chIdx = 0U; chIdx < CDD_PWM_MAX_NUM_CHANNELS; chIdx++)
        {
            if (CDD_PWM_STATUS_INIT == (Cdd_Pwm_ChObj[chIdx].channelState))
            {
                Cdd_Pwm_IpDeInit_epwm(&Cdd_Pwm_ChObj[chIdx]);

                /*
                 * The function Cdd_Pwm_Deinit shall disable all interrupt
                 * notifications controlled by the CDD_PWM driver.
                 */
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
                Cdd_Pwm_ChObj[chIdx].channelNotifyActiveFlag = CDD_PWM_FALSE;
#endif
                /* Change the State to CDD_PWM_STATUS_UNINIT */
                Cdd_Pwm_ChObj[chIdx].channelState = CDD_PWM_STATUS_UNINIT;

                /* Reset driver object */
                Cdd_Pwm_resetChObj(&Cdd_Pwm_ChObj[chIdx]);
            }
        }

        /* Set driver status  to uninitialized */
        Cdd_Pwm_DrvStatus = CDD_PWM_STATUS_UNINIT;
    }
    return;
}
#endif /*(STD_ON == CDD_PWM_DEINIT_API)*/

/*===============================================================================================*/
/*
 *Design: MCAL-23382, MCAL-23374, MCAL-23373, MCAL-23375, MCAL-23372
 */
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_StopChannelCounter(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_STOPCHANNEL))
    {
        if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
        {
            /*Invalid channel */
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_STOPCHANNEL, CDD_PWM_E_PARAM_INVALID_CHANNEL);
        }
        else
        {
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
            Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
            if (CDD_PWM_STATUS_UNINIT == chObj->channelState)
            {
                (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_STOPCHANNEL, CDD_PWM_E_UNINIT);
            }
            else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
            {
                /* Critical section, block the interrupts */
                SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

                /* Stop the CDD_PWM Channel. */
                Cdd_Pwm_Stop_Private((const Cdd_Pwm_ChObjType *)chObj);

                /*  Change the Status to Running. */
                Cdd_Pwm_ChObj[ChannelNumber].channelState = CDD_PWM_STATUS_STOPPED;

                /* Critical section, enable the interrupts */
                SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
            }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        }
    }
#endif /* CDD_PWM_DEV_ERROR_DETECT */
}

/*===============================================================================================*/
/*
 *Design: MCAL-23381, MCAL-23376, MCAL-23377, MCAL-23378, MCAL-23379, MCAL-23380
 */
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_StartChannelCounter(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_STARTCHANNEL))
    {
        if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
        {
            /*Invalid channel */
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_STARTCHANNEL, CDD_PWM_E_PARAM_INVALID_CHANNEL);
        }
        else
        {
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
            Cdd_Pwm_StartChannel(ChannelNumber);
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        }
    }
#endif /* CDD_PWM_DEV_ERROR_DETECT */
}

static void Cdd_Pwm_StartChannel(Cdd_Pwm_ChannelType ChannelNumber)
{
    Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_UNINIT == chObj->channelState)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_STARTCHANNEL, CDD_PWM_E_UNINIT);
    }
    else if (Cdd_Pwm_ChObj[ChannelNumber].channelState == CDD_PWM_STATUS_RUNNING)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_STARTCHANNEL, CDD_PWM_E_BUSY);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        /* Critical section, block the interrupts */
        SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Start the CDD_PWM Channel. */
        Cdd_Pwm_Start_Private((const Cdd_Pwm_ChObjType *)chObj);

        /*  Change the Status to Running. */
        Cdd_Pwm_ChObj[ChannelNumber].channelState = CDD_PWM_STATUS_RUNNING;

        /* Critical section, enable the interrupts */
        SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
}

/*===============================================================================================*/
/*
 *Design: MCAL-23383, MCAL-23384, MCAL-23385, MCAL-23386
 */
#if (CDD_PWM_GET_COUNTER_API == STD_ON)
FUNC(Cdd_Pwm_ValueType, CDD_PWM_CODE)
Cdd_Pwm_GetCounter(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber)
{
    Cdd_Pwm_ValueType CounterValue = 0U;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_GETCOUNTER))
    {
        if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
        {
            /*Invalid channel */
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_GETCOUNTER, CDD_PWM_E_PARAM_INVALID_CHANNEL);
        }
        else
        {
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
            Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
            if (CDD_PWM_STATUS_UNINIT == chObj->channelState)
            {
                (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_GETCOUNTER, CDD_PWM_E_UNINIT);
            }
            else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
            {
                /* Critical section, block the interrupts */
                SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

                /* Get the Counter. */
                CounterValue = Cdd_Pwm_PrivGetCounter((const Cdd_Pwm_ChObjType *)chObj);

                /* Critical section, enable the interrupts */
                SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
            }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        }
    }
#endif /* CDD_PWM_DEV_ERROR_DETECT */

    /* Return counter. */
    return (CounterValue);
}
#endif /* CDD_PWM_GET_COUNTER_API */

/*===============================================================================================*/
/*
 *Design: MCAL-23391, MCAL-23387, MCAL-23388, MCAL-23389, MCAL-23390
 */
#if (CDD_PWM_SET_PIN_ACTION_API == STD_ON)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetPinAction(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber, VAR(Cdd_Pwm_PinActionType, AUTOMATIC) PinAction)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
    {
        /*Invalid channel */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_PIN_ACTION, CDD_PWM_E_PARAM_INVALID_CHANNEL);
    }
    else
    {
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
        Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        if ((CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus) && (CDD_PWM_STATUS_INIT != chObj->channelState))
        {
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_PIN_ACTION, CDD_PWM_E_UNINIT);
        }
        else if ((PinAction != CDD_PWM_SET_LOW) && (PinAction != CDD_PWM_SET_HIGH) && (PinAction != CDD_PWM_TOGGLE) &&
                 (PinAction != CDD_PWM_DISABLE))
        {
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_PIN_ACTION, CDD_PWM_E_PARAM_INVALID_ACTION);
        }
        else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
        {
            /* Critical section, block the interrupts */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Set the Pin State. */
            Cdd_Pwm_SetPinAction_Private((const Cdd_Pwm_ChObjType *)chObj, PinAction);

            /* Critical section, enable the interrupts */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif /* CDD_PWM_DEV_ERROR_DETECT */
}
#endif /* CDD_PWM_SET_PIN_ACTION_API */

/*===============================================================================================*/
/*
 *Design: MCAL-23392, MCAL-23394, MCAL-23393, MCAL-23395
 */
#if (CDD_PWM_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetAbsoluteThreshold(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                             VAR(Cdd_Pwm_ValueType, AUTOMATIC) ReferenceValue,
                             VAR(Cdd_Pwm_ValueType, AUTOMATIC) AbsoluteValue)
{
    VAR(Cdd_Pwm_ReturnType, AUTOMATIC) ret = CDD_PWM_CM_OUT_REF_INTERVAL;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_SET_ABSOLUTE_THRESHOLD))
    {
        if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
        {
            /*Invalid channel */
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_ABSOLUTE_THRESHOLD, CDD_PWM_E_PARAM_INVALID_CHANNEL);
        }
        else
        {
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
            Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
            if (CDD_PWM_STATUS_UNINIT == chObj->channelState)
            {
                (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_ABSOLUTE_THRESHOLD, CDD_PWM_E_UNINIT);
            }
            else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
            {
                /* Critical section, block the interrupts */
                SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

                ret = Cdd_Pwm_PrivSetAbsoluteThreshold((const Cdd_Pwm_ChObjType *)chObj, ReferenceValue, AbsoluteValue);

                /* Critical section, enable the interrupts */
                SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
            }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        }
    }
#endif /* CDD_PWM_DEV_ERROR_DETECT */

    return (ret);
}
#endif /* CDD_PWM_SET_ABSOLUTE_THRESHOLD_API */

/*===============================================================================================*/
/*
 *Design: MCAL-23396, MCAL-23397, MCAL-23398, MCAL-23399
 */
#if (CDD_PWM_SET_RELATIVE_THRESHOLD_API == STD_ON)
FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetRelativeThreshold(VAR(Cdd_Pwm_ChannelType, AUTOMATIC) ChannelNumber,
                             VAR(Cdd_Pwm_ValueType, AUTOMATIC) RelativeValue)
{
    VAR(Cdd_Pwm_ReturnType, AUTOMATIC) ret = CDD_PWM_CM_OUT_REF_INTERVAL;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
    {
        /*Invalid channel */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_RELATIVE_THRESHOLD, CDD_PWM_E_PARAM_INVALID_CHANNEL);
    }
    else
    {
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
        Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        if ((CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus) && (CDD_PWM_STATUS_INIT != chObj->channelState))
        {
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_RELATIVE_THRESHOLD, CDD_PWM_E_UNINIT);
        }
        else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
        {
            /* Critical section, block the interrupts */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            ret = Cdd_Pwm_PrivSetReleativeThreshold((const Cdd_Pwm_ChObjType *)chObj, RelativeValue);

            /* Critical section, enable the interrupts */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif /* CDD_PWM_DEV_ERROR_DETECT */

    return ret;
}
#endif /* CDD_PWM_SET_RELATIVE_THRESHOLD_API */

/*===============================================================================================*/
/*
 *Design: MCAL-23400, MCAL-23401
 */
#if (STD_ON == CDD_PWM_COUNTER_STATUS_MODE)
FUNC(uint16, CDD_PWM_CODE) Cdd_Pwm_GetCounterStatus(Cdd_Pwm_ChannelType Channel, uint32 tbStatusMask)
{
    uint32 baseAddr;
    uint16 status = 0x00U;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_GETCOUNTER_STATUS))
#endif

    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_GETCOUNTER_STATUS);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Get the Status. */
            status = Cdd_Pwm_tbGetStatus(baseAddr, tbStatusMask);
        }
    }

    return (status);
}

/*===============================================================================================*/
/*
 *Design: MCAL-23403, MCAL-23402
 */
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_ClearCounterStatus(Cdd_Pwm_ChannelType Channel, uint32 tbStatusClrMask)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_CLEAR_COUNTER_STATUS))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_CLEAR_COUNTER_STATUS);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Critical section, block the interrupts */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Clear the Status. */
            Cdd_Pwm_tbStatusClear(baseAddr, tbStatusClrMask);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
#endif /* CDD_PWM_COUNTER_STATUS_MODE*/

/*===============================================================================================*/

/*
 *Design: MCAL-23404, MCAL-23405, MCAL-23406, MCAL-23407, MCAL-23408
 */
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
/* Disables notification for channel ChannelNumber. */
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_DisableNotification(Cdd_Pwm_ChannelType ChannelNumber)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
    {
        /*Invalid channel */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_DISABLE_NOTIFICATION, CDD_PWM_E_PARAM_INVALID_CHANNEL);
    }
    else
    {
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
        Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        if ((CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus) && (CDD_PWM_STATUS_INIT != chObj->channelState))
        {
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_DISABLE_NOTIFICATION, CDD_PWM_E_UNINIT);
        }
        else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
        {
            /* Critical section, block the interrupts */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Disable the interrupt. */
            Cdd_Pwm_DisableInterrupt(ChannelNumber);

            /* Set the notification active flag to FALSE */
            chObj->channelNotifyActiveFlag = CDD_PWM_FALSE;

            /* Critical section, enable the interrupts */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    return;
}
#endif /* #if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

/*===============================================================================================*/
/*
 *Design: MCAL-23409, MCAL-23410, MCAL-23411, MCAL-23412, MCAL-23413, MCAL-23414
 */
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
/* Enables notification for channel Channel. */
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_EnableNotification(Cdd_Pwm_ChannelType ChannelParameter, Cdd_Pwm_InterruptType EdgeInterruptSource)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    Cdd_Pwm_ChannelType ChannelNumber = ChannelParameter;
    if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
    {
        /*Invalid channel */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_ENABLE_NOTIFICATION, CDD_PWM_E_PARAM_INVALID_CHANNEL);
    }
    else
    {
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)*/
        Cdd_Pwm_StartNotification(ChannelParameter, EdgeInterruptSource);
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif
    return;
}

static void Cdd_Pwm_StartNotification(Cdd_Pwm_ChannelType ChannelParameter, Cdd_Pwm_InterruptType EdgeInterruptSource)
{
    Cdd_Pwm_ChannelType ChannelNumber = ChannelParameter;
    Cdd_Pwm_ChObjType  *chObj         = &Cdd_Pwm_ChObj[ChannelNumber];

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if ((CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus) && (CDD_PWM_STATUS_INIT != chObj->channelState))
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_ENABLE_NOTIFICATION, CDD_PWM_E_UNINIT);
    }
    else if ((Cdd_Pwm_NotifyFuncType)NULL_PTR == chObj->notificationHandler)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_ENABLE_NOTIFICATION, CDD_PWM_E_PARAM_INVALID_CHANNEL);
    }
    else
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)*/
    {
        if (CDD_PWM_STATUS_UNINIT != chObj->channelState)
        {
            /* Critical section, block the interrupts */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Enable the interrupt. */
            Cdd_Pwm_EnableInterrupt(ChannelParameter, EdgeInterruptSource);

            /* Enable the notification flag */
            chObj->channelNotifyActiveFlag = CDD_PWM_TRUE;

            /* Critical section, enable the interrupts */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
    }
}
#endif /*#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

/*
 *Design: MCAL-23416, MCAL-23417, MCAL-24107
 */
FUNC(uint16, CDD_PWM_CODE) Cdd_Pwm_EtIntrStatus(Cdd_Pwm_ChannelType Channel)
{
    uint32 baseAddr;
    uint16 status = 0U;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_INTR_STATUS))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_INTR_STATUS);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Interrupt Status. */
            status = Cdd_Pwm_etIntrStatus(baseAddr);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            status = 0x00;
        }
    }

    return (status);
}
/*
 *Design: MCAL-23419, MCAL-23418
 */
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_EtIntrClear(Cdd_Pwm_ChannelType Channel)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_INTR_CLEAR_STATUS))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_INTR_CLEAR_STATUS);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Critical section, block the interrupts */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Clear the Interrupt Flag. */
            Cdd_Pwm_etIntrClear(baseAddr);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
/*
 *Design: MCAL-23420, MCAL-23421
 */
FUNC(Cdd_Pwm_ValueType, CDD_PWM_CODE) Cdd_Pwm_EtGetEventCount(Cdd_Pwm_ChannelType Channel)
{
    uint32            baseAddr;
    Cdd_Pwm_ValueType countValue = 0U;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_GET_EVENT_COUNT))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_GET_EVENT_COUNT);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            countValue = Cdd_Pwm_etGetEventCount(baseAddr);
        }
        else
        {
            countValue = 0U;
        }
    }

    return (countValue);
}

/*===============================================================================================*/
/*
 *Design: MCAL-23422, MCAL-23423
 */
#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
/*  Sets DutyCycle and Period of ChannelNumber. DutyCycle is a percentage of
 *  the period with 0x8000 being equivalent to 100%. */
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetPeriodDutyPhase(Cdd_Pwm_channelParametertype ChannelParameter)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    ret_val = Cdd_Pwm_SetPeriodAndDuty_Deterror(ChannelParameter);
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

    if (ret_val == E_OK)
    {
        /* Enter Critical Section. */
        SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Period passed here is in unit ticks */
        Cdd_Pwm_SystemSetPeriodAndDuty(ChannelParameter);

        /* Exit Critical Section. */
        SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
    else
    {
        /*do nothing */
    }
    return;
}
#endif /*(STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)*/

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetPhaseShift(Cdd_Pwm_ChannelType Channel, uint16 PhaseShiftValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_PHASE_SHIFT, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_PHASE_SHIFT);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Phase shift value is passed here */
            EPWM_setPhaseShift(baseAddr, PhaseShiftValue);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetTimeBasePeriod(Cdd_Pwm_ChannelType Channel, uint16 Period)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_TIMEBASE_PERIOD, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_TIMEBASE_PERIOD);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Period value is passed here */
            EPWM_setTimeBasePeriod(baseAddr, Period);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetCounterCompareValue(Cdd_Pwm_ChannelType Channel, EPWM_CounterCompareModule CompModule, uint16 DutyValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_COUNTER_COMPARE_VALUE, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_COUNTER_COMPARE_VALUE);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Compare module and value is passed here */
            EPWM_setCounterCompareValue(baseAddr, CompModule, DutyValue);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetRisingEdgeDelay(Cdd_Pwm_ChannelType Channel, uint16 RedCount)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_RISING_EDGE_DELAY_COUNT, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_RISING_EDGE_DELAY_COUNT);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Rising Edge Delay value is passed here */
            EPWM_setRisingEdgeDelayCount(baseAddr, RedCount);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetFallingEdgeDelay(Cdd_Pwm_ChannelType Channel, uint16 FedCount)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_FALLING_EDGE_DELAY_COUNT, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_FALLING_EDGE_DELAY_COUNT);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Falling Edge Delay value is passed here */
            EPWM_setFallingEdgeDelayCount(baseAddr, FedCount);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetMinDeadbandDelay(Cdd_Pwm_ChannelType Channel, uint32 Block, uint32 Delay)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_MIN_DEADBAND_DELAY, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_MIN_DEADBAND_DELAY);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Block and minimum deadband delay value is passed here */
            EPWM_setMinDeadBandDelay(baseAddr, Block, Delay);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetXcmpRegValue(Cdd_Pwm_ChannelType Channel, EPWM_XCMPReg XcmpReg, uint16 XcmpValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_XCMP_REG_VALUE, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_XCMP_REG_VALUE);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* XCMP reg and value is passed here */
            EPWM_setXCMPRegValue(baseAddr, XcmpReg, XcmpValue);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetXMinMaxRegValue(Cdd_Pwm_ChannelType Channel, EPWM_XMinMaxReg XminmaxReg, uint16 XcmpValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_XMINMAP_REG_VALUE, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_XMINMAP_REG_VALUE);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* MinMax value is passed here */
            EPWM_setXMINMAXRegValue(baseAddr, XminmaxReg, XcmpValue);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetCmpShadowRegValue(Cdd_Pwm_ChannelType Channel, EPWM_XCompareReg CmpReg, uint16 CmpValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_CMP_SHADOW_REG_VALUE, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_CMP_SHADOW_REG_VALUE);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* CMP shadow reg value is passed here */
            EPWM_setCMPShadowRegValue(baseAddr, CmpReg, CmpValue);
        }
    }

    return;
}

/*===============================================================================================*/
/*
 *Design: MCAL-23424, MCAL-23425
 */
#if (STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API)
/* Sets output state immediately to idle level. */
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SetOutputToIdle(Cdd_Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType ret_val = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    ret_val = Cdd_Pwm_SetOutputToIdle_Deterror(ChannelNumber);
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

    /* Check for DET Error. */
    if (ret_val == E_OK)
    {
        /* Enter Critical Section. */
        SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Set output to idle state */
        Cdd_Pwm_SystemSetOutputToIdle(ChannelNumber);

        /* Exit Critical Section. */
        SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
    }
    else
    {
        /*do nothing */
    }
}
#endif /*(STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API)*/

/*
 *Design: MCAL-23426, MCAL-23427, MCAL-23428, MCAL-23429, MCAL-23430, MCAL-23431, MCAL-24105
 */
#if (STD_ON == CDD_PWM_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_RegisterReadback(Cdd_Pwm_ChannelType Cdd_PwmChannel,
                         P2VAR(Cdd_Pwm_RegisterReadbackType, AUTOMATIC, CDD_PWM_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = ((Std_ReturnType)E_NOT_OK);

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[Cdd_PwmChannel];
    if (Cdd_PwmChannel >= (uint32)CDD_PWM_MAX_NUM_CHANNELS)
    {
        /*Invalid channel */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_REGISTER_READBACK, CDD_PWM_E_PARAM_INVALID_CHANNEL);
    }
    else if ((CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus) && (CDD_PWM_STATUS_INIT != chObj->channelState))
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_REGISTER_READBACK, CDD_PWM_E_UNINIT);
    }
    else if (NULL_PTR == RegRbPtr)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_REGISTER_READBACK, CDD_PWM_E_PARAM_POINTER);
    }
    else
#endif
    {
        (void)memset(RegRbPtr, 0, sizeof(Cdd_Pwm_RegisterReadbackType));
        Cdd_Pwm_IpRegisterReadback_epwm(Cdd_PwmChannel, RegRbPtr);
        retVal = (Std_ReturnType)E_OK;
    }
    return (retVal);
}
#endif /*(STD_ON == CDD_PWM_REGISTER_READBACK_API)*/
/*
 *Design: MCAL-23432, MCAL-23433, MCAL-23434
 */
#if (STD_ON == CDD_PWM_VERSION_INFO_API)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_PWM_APPL_DATA) VersionInfoPtr)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        Cdd_Pwm_reportDetError(CDD_PWM_SID_GET_VERSION_INFO, CDD_PWM_E_PARAM_POINTER);
    }
    else
#endif
    {
        VersionInfoPtr->vendorID         = CDD_PWM_VENDOR_ID;
        VersionInfoPtr->moduleID         = CDD_PWM_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)CDD_PWM_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)CDD_PWM_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)CDD_PWM_SW_PATCH_VERSION;
    }

    return;
}
#endif /* CDD_PWM_VERSION_INFO_API*/

/*
 *Design: MCAL-23435, MCAL-23436, MCAL-23437, MCAL-24093
 */
#if (STD_ON == CDD_PWM_HR_SET_HRPWM_API)
FUNC(void, PWM_CODE) Cdd_Pwm_HrSetPeriodDutyPhase(Cdd_Pwm_channelParametertype ChannelParameter)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (Cdd_Pwm_DrvStatus != CDD_PWM_STATUS_INIT)
    {
        /*
         * Cdd_Pwm module must be initialized.
         * Otherwise call the Det with CDD_PWM_E_UNINIT
         */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SET_HRPWM_API, CDD_PWM_E_UNINIT);
    }
    else
    {
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

        /* Enter Critical Section. */
        SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Set the Period and Duty. */
        Cdd_Pwm_HrSystemSetPeriodAndDuty(ChannelParameter);

        /* Exit Critical Section. */
        SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
}
#endif /* #if (STD_ON == CDD_PWM_HR_SET_HRPWM_API) */
/*
 *Design: MCAL-23438, MCAL-23439, MCAL-23440
 */
#if (STD_ON == CDD_PWM_HR_SFO_CAL_API)
FUNC(void, PWM_CODE) Cdd_Pwm_HrSfoCalibration(Cdd_Pwm_channelParametertype ChannelParameter)
{
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (Cdd_Pwm_DrvStatus != CDD_PWM_STATUS_INIT)
    {
        /*
         * Cdd_Pwm module must be initialized.
         * Otherwise call the Det with CDD_PWM_E_UNINIT
         */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SFO_CAL_API, CDD_PWM_E_UNINIT);
    }
    else
    {
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

        /* Enter Critical Section. */
        SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

        /* Start the Calibration. */
        Cdd_Pwm_HrSfoCalibration_Private(ChannelParameter);

        /* Exit Critical Section. */
        SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
}
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_CAL_API) */
/*
 *Design: MCAL-23441, MCAL-23443, MCAL-23444, MCAL-23445
 */
#if (STD_ON == CDD_PWM_HR_SFO_STATUS_API)
FUNC(uint32, PWM_CODE) Cdd_Pwm_HrSfoStatus(uint32 ChannelNumber)
{
    uint32 status = 0U;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (Cdd_Pwm_DrvStatus != CDD_PWM_STATUS_INIT)
    {
        /*
         * Cdd_Pwm module must be initialized.
         * Otherwise call the Det with CDD_PWM_E_UNINIT
         */
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SFO_STATUS_API, CDD_PWM_E_UNINIT);
    }
    else
    {
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        if (ChannelNumber >= CDD_PWM_MAX_NUM_CHANNELS)
        {
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SFO_STATUS_API, CDD_PWM_E_PARAM_INVALID_CHANNEL);
        }
        else
        {
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Get the Status. */
            status = Cdd_Pwm_ChannelSfoStatus[ChannelNumber];

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        }
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

    return (status);
}
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_STATUS_API) */

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetPhaseShift(Cdd_Pwm_ChannelType Channel, uint32 PhaseShiftValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SET_PHASE_SHIFT, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_HR_SET_PHASE_SHIFT);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Phase shift value is passed here */
            HRPWM_setPhaseShift(baseAddr, PhaseShiftValue);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetTimeBasePeriod(Cdd_Pwm_ChannelType Channel, uint16 Period)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SET_TIMEBASE_PERIOD, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_HR_SET_TIMEBASE_PERIOD);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Period value is passed here */
            HRPWM_setHiResTimeBasePeriod(baseAddr, Period);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_HrSetCounterCompareValue(Cdd_Pwm_ChannelType Channel, HRPWM_CounterCompareModule CompModule, uint32 DutyValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SET_COUNTER_COMPARE_VALUE, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_HR_SET_COUNTER_COMPARE_VALUE);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Compare module and value is passed here */
            HRPWM_setCounterCompareValue(baseAddr, CompModule, DutyValue);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetRisingEdgeDelay(Cdd_Pwm_ChannelType Channel, uint16 RedCount)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SET_RISING_EDGE_DELAY_COUNT, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_HR_SET_RISING_EDGE_DELAY_COUNT);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Rising Edge Delay value is passed here */
            HRPWM_setHiResRisingEdgeDelay(baseAddr, RedCount);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HrSetFallingEdgeDelay(Cdd_Pwm_ChannelType Channel, uint16 FedCount)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SET_FALLING_EDGE_DELAY_COUNT, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_HR_SET_FALLING_EDGE_DELAY_COUNT);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Falling Edge Delay value is passed here */
            HRPWM_setHiResFallingEdgeDelayOnly(baseAddr, FedCount);
        }
    }

    return;
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_HrSetXcmpRegValue(Cdd_Pwm_ChannelType Channel, HRPWM_XCMPReg HrXcmpReg, uint16 HrXcmpValue)
{
    uint32 baseAddr;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus)
    {
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_HR_SET_XCMP_REG_VALUE, CDD_PWM_E_UNINIT);
    }
    else
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_HR_SET_XCMP_REG_VALUE);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* XCMP reg and value is passed here */
            HRPWM_setXCMPRegValue(baseAddr, HrXcmpReg, HrXcmpValue);
        }
    }

    return;
}

/*
 *Design: MCAL-23447, MCAL-23448
 */
#if (STD_ON == CDD_PWM_ADC_ENABLE_DISABLE_API)
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_SetAdcTrigger(Cdd_Pwm_ChannelType Channel, Cdd_Pwm_AdcSocType adcSoc)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_SET_ADC_TRIGGER))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_ADC_TRIGGER);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Trigger ADC module. */
            Cdd_Pwm_EnableAdcTrigger(baseAddr, adcSoc);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
#endif /*#if (STD_ON == CDD_PWM_ADC_ENABLE_DISABLE_API)*/
/*
 *Design: MCAL-23449, MCAL-23450
 */
#if (STD_ON == CDD_PWM_BASE_CLK_SYNC)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SyncEnable(Cdd_Pwm_ChannelType Channel, uint32 tbPhsValue, uint32 counterDir)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_SYNC_ENABLE))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SYNC_ENABLE);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Enable Sync */
            Cdd_Pwm_tbSyncEnable(baseAddr, tbPhsValue, counterDir);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}

/*
 *Design: MCAL-23451, MCAL-23452
 */
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_SyncDisable(Cdd_Pwm_ChannelType Channel)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_SYNC_DISABLE))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SYNC_DISABLE);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Disable Sync. */
            Cdd_Pwm_tbSyncDisable(baseAddr);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
#endif /*#if (STD_ON == CDD_PWM_BASE_CLK_SYNC)*/
/*
 *Design: MCAL-23453, MCAL-23454
 */
#if (STD_ON == CDD_PWM_COUNTER_COMPARE_CFG)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_CounterComparatorCfg(Cdd_Pwm_ChannelType Channel, Cdd_Pwm_OutputChType cmpType, uint32 cmpVal,
                             uint32 shadowToActiveLoadTrigger, uint32 overwriteShadow)
{
    uint32         baseAddr;
    Std_ReturnType ret    = E_OK;
    boolean        status = CDD_PWM_FALSE;
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_COUNTER_CMP_CFG))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_COUNTER_CMP_CFG);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Set Comaprator Values. */
            status = (boolean)Cdd_Pwm_counterComparatorCfg(baseAddr, cmpType, cmpVal, shadowToActiveLoadTrigger,
                                                           overwriteShadow);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            if (status == CDD_PWM_FALSE)
            {
                ret = E_NOT_OK;
            }
        }
        else
        {
            ret = E_NOT_OK;
        }
    }

    return (ret);
}
#endif /*#if (STD_ON == CDD_PWM_COUNTER_COMPARE_CFG)*/
/*
 *Design: MCAL-23455, MCAL-23456, MCAL-23457, MCAL-24112
 */
#if (STD_ON == CDD_PWM_DEAD_BAND)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_DeadbandCfg(Cdd_Pwm_ChannelType Channel, const CDD_PWM_DeadbandCfgType *pCfg)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_CONFIGURE_DEADBAND))
    {
        if (pCfg == NULL_PTR)
        {
            /*Invalid Pointer */
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_CONFIGURE_DEADBAND, CDD_PWM_E_PARAM_POINTER);
            returnValue = E_NOT_OK;
        }
        else
#endif
        {
            baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_CONFIGURE_DEADBAND);

            if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
            {
                /* Enter Critical Section. */
                SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

                /* Configure Parameters. */
                Cdd_Pwm_deadbandCfg(baseAddr, pCfg);

                /* Exit Critical Section. */
                SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
            }
            else
            {
                returnValue = E_NOT_OK;
            }
        }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif
    return returnValue;
}
/*
 *Design: MCAL-23459, MCAL-23458
 */
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_DeadbandBypass(Cdd_Pwm_ChannelType Channel)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_BYPASS_DEADBAND))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_BYPASS_DEADBAND);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Disable DeadBand. */
            Cdd_Pwm_deadbandBypass(baseAddr);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
#endif /*#if (STD_ON == CDD_PWM_DEAD_BAND)*/
/*
 *Design: MCAL-23460, MCAL-23461, MCAL-23462
 */
#if (STD_ON == CDD_PWM_CHOPPER)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_ChopperCfg(Cdd_Pwm_ChannelType Channel, const CDD_PWM_ChopperCfgType *pCfg)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_CONFIGURE_CHOPPER))
    {
        if (pCfg == NULL_PTR)
        {
            /*Invalid Pointer */
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_CONFIGURE_CHOPPER, CDD_PWM_E_PARAM_POINTER);
            returnValue = E_NOT_OK;
        }
        else
#endif
        {
            baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_CONFIGURE_CHOPPER);

            if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
            {
                /* Enter Critical Section. */
                SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

                /* Configure Chopper. */
                Cdd_Pwm_chopperCfg(baseAddr, pCfg);

                /* Exit Critical Section. */
                SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
            }
            else
            {
                returnValue = E_NOT_OK;
            }
        }
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    }
#endif

    return (returnValue);
}
/*
 *Design: MCAL-23464, MCAL-23463
 */
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_ChopperEnable(Cdd_Pwm_ChannelType Channel, uint32 enableChopper)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_ENABLE_CHOPPER))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_ENABLE_CHOPPER);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Enable Chopper. */
            Cdd_Pwm_chopperEnable(baseAddr, enableChopper);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
#endif /*#if (STD_ON == CDD_PWM_CHOPPER)*/

FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetTimeBaseCounterMode(Cdd_Pwm_ChannelType Channel, EPWM_TimeBaseCountMode Mode)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_SET_TIME_BASE_COUNTER_MODE))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_SET_TIME_BASE_COUNTER_MODE);
        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Set Time base counter mode */
            EPWM_setTimeBaseCounterMode(baseAddr, Mode);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}

/*
 *Design: MCAL-23465, MCAL-23466
 */
#if (STD_ON == CDD_PWM_TRIP_ZONE)
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzTripEventEnable(Cdd_Pwm_ChannelType Channel, uint32 tzEventType)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_TZ_EVENT_ENABLE))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_TZ_EVENT_ENABLE);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* TripZone Enabled */
            Cdd_Pwm_tzTripEventEnable(baseAddr, tzEventType);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
/*
 *Design: MCAL-23468, MCAL-23467
 */
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzTripEventDisable(Cdd_Pwm_ChannelType Channel, uint32 tzEventType)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_TZ_EVENT_DISABLE))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_TZ_EVENT_DISABLE);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Disable Tz Event. */
            Cdd_Pwm_tzTripEventDisable(baseAddr, tzEventType);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
/*
 *Design: MCAL-23469, MCAL-23470, MCAL-24107, MCAL-24109
 */
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzIntrEnable(Cdd_Pwm_ChannelType Channel, uint32 tzEventType)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_TZ_INTR_ENABLE))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_TZ_INTR_ENABLE);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            Cdd_Pwm_tripZoneType *tripZoneParameter = &Cdd_Pwm_ChObj[Channel].channelTripZone;

            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Enable Tz Event. */
            Cdd_Pwm_tzIntrEnable(baseAddr, tzEventType, tripZoneParameter);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
/*
 *Design: MCAL-23472, MCAL-23471, MCAL-24100
 */
FUNC(Std_ReturnType, CDD_PWM_CODE) Cdd_Pwm_TzIntrDisable(Cdd_Pwm_ChannelType Channel, uint32 tzEventType)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_TZ_INTR_DISABLE))
#endif
    {
        baseAddr                                = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_TZ_INTR_DISABLE);
        Cdd_Pwm_tripZoneType *tripZoneParameter = &Cdd_Pwm_ChObj[Channel].channelTripZone;

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Tz Interrupt Disable. */
            Cdd_Pwm_tzIntrDisable(baseAddr, tzEventType, tripZoneParameter);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
/*
 *Design: MCAL-23473, MCAL-23474
 */
FUNC(boolean, CDD_PWM_CODE) Cdd_Pwm_TzGetEventStatus(Cdd_Pwm_ChannelType Channel, uint32 eventMask)
{
    uint32  baseAddr;
    uint16  status = 0U;
    boolean ret    = CDD_PWM_FALSE;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_TZ_GET_EVENT_STATUS))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_TZ_GET_EVENT_STATUS);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Enable Event Status. */
            status = Cdd_Pwm_tzEventStatus(baseAddr, eventMask);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            if (status != 0x0U)
            {
                ret = CDD_PWM_TRUE;
            }
        }
    }

    return (ret);
}
/*
 *Design: MCAL-23476, MCAL-23475
 */
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_TzEventStatusClear(Cdd_Pwm_ChannelType Channel, uint32 eventMask, uint16 tzFlags)
{
    uint32         baseAddr;
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
    if (E_OK == Cdd_Pwm_Validate_Init(CDD_PWM_SID_TZ_EVENT_STATUS_CLEAR))
#endif
    {
        baseAddr = Cdd_Pwm_getBaseAddr(Channel, CDD_PWM_SID_TZ_EVENT_STATUS_CLEAR);

        if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
        {
            /* Enter Critical Section. */
            SchM_Enter_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();

            /* Clear the Event Status. */
            Cdd_Pwm_tzEventStatusClear(baseAddr, eventMask, tzFlags);

            /* Exit Critical Section. */
            SchM_Exit_Cdd_Pwm_PWM_EXCLUSIVE_AREA_0();
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }

    return (returnValue);
}
#endif /*#if (STD_ON == CDD_PWM_TRIP_ZONE)*/

#define CDD_PWM_STOP_SEC_CODE
#include "Cdd_Pwm_MemMap.h"
