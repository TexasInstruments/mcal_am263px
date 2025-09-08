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
 *  \file   Pwm_Priv.c
 *
 *  \brief  This file contains the Internal APIs for PWM.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Pwm_Priv.h"
#include "hw_epwm.h"
#include "sys_common.h"
#include "mcal_hw_soc_baseaddress.h"

#if (STD_ON == PWM_SFO_SUPPORT_ENABLE)
#include "Pwm_Sfo.h"
#endif

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#define PWM_START_SEC_VAR_NO_INIT_32
#include "Pwm_MemMap.h"
VAR(sint32, PWM_VAR_NO_INIT) Pwm_MEP_ScaleFactor;
#define PWM_STOP_SEC_VAR_NO_INIT_32
#include "Pwm_MemMap.h"

static void Pwm_ConfigHR_epwm_Internal(uint32 outputCh, uint32 baseAddr, float32 Duty, float32 highRes_regVal);
static void Pwm_ConfigHR_epwm_Internal1(uint32 outputCh, uint32 baseAddr, float32 Duty, float32 highRes_regVal);
static void Pwm_EnableNotification_epwm_FallingEdge(uint32 outputCh, uint32 baseAddr, Pwm_OutputStateType polarity);
static void Pwm_EnableNotification_epwm_RisingEdge(uint32 outputCh, uint32 baseAddr, Pwm_OutputStateType polarity);
static void Pwm_EnableNotification_epwm_BothEdges(uint32 outputCh, uint32 baseAddr);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"
/** \brief Pwm driver interrupt status flag*/
volatile VAR(Pwm_OutputStateType, PWM_VAR_NO_INIT) Pwm_Intrflag[PWM_MAX_NUM_CHANNELS];
/** \brief PWM driver object. */
VAR(Pwm_ChObjType, PWM_VAR_NO_INIT) Pwm_ChObj[PWM_MAX_NUM_CHANNELS];
VAR(uint16, PWM_VAR_NO_INIT) Pwm_IsrIndex[PWM_HW_MAX_NUM_CHANNELS];
#define PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"

#define PWM_START_SEC_VAR_INIT_32
#include "Pwm_MemMap.h"

VAR(uint32, PWM_VAR_INIT) Pwm_gOttoCal_base = (uint32)MCAL_CSL_CONTROLSS_OTTOCAL0_U_BASE;

#define PWM_STOP_SEC_VAR_INIT_32
#include "Pwm_MemMap.h"
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define PWM_START_SEC_CODE
#include "Pwm_MemMap.h"

FUNC(void, PWM_CODE) Pwm_ResetChObj(Pwm_ChObjType *chObj)
{
    chObj->chCfg_PC.channelId = (Pwm_ChannelType)0U;
#ifdef PWM_USE_EPWM
    chObj->chCfg_PC.outputCh = 0U;
#endif /*PWM_USE_EPWM*/
    chObj->chCfg.instanceClkHz = 0U;
    chObj->chCfg.dutyCycle     = 0U;
    chObj->chCfg.hwPeriod      = 0U;
    chObj->chCfg.polarity      = PWM_LOW;
    chObj->chCfg.idleState     = PWM_LOW;
    chObj->chCfg.channelClass  = PWM_FIXED_PERIOD;
    chObj->chCfg.prescale      = 0U;
#ifdef PWM_USE_EPWM
    chObj->chCfg.hsPrescale = 0U;
    chObj->chCfg.enableHR   = FALSE;
#endif /*PWM_USE_EPWM*/
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
    chObj->chCfg.notificationHandler = (Pwm_NotifyFuncType)NULL_PTR;
    chObj->channelNotifyActiveFlag   = (uint32)FALSE;
#endif
    chObj->baseAddr     = 0U;
    chObj->channelState = PWM_STATUS_UNINIT;
    return;
}

FUNC(void, PWM_CODE)
Pwm_CopyConfig(Pwm_ChObjType *chObj, const Pwm_ChannelConfigType *chCfg, const Pwm_ChannelConfigType_PC *chCfg_pc)
{
    /* Copying the Config stucture to Channel Object*/
    (void)memcpy(&chObj->chCfg, &chCfg[0U], sizeof(Pwm_ChannelConfigType));

    /*Copying the pre-compile config structure to Channel Object */
    chObj->chCfg_PC.channelId = chCfg_pc->channelId;
#ifdef PWM_USE_EPWM
    chObj->chCfg_PC.outputCh = chCfg_pc->outputCh;
#endif /*PWM_USE_EPWM*/

    /* Store base address of all the configured channels */
    chObj->baseAddr = chCfg[0U].baseaddr;
    /* Init channelForcedIdle var default to FALSE */
    chObj->channelForcedIdle = (boolean)FALSE;
    chObj->channelState      = PWM_STATUS_INIT;
    return;
}

FUNC(void, PWM_CODE) Pwm_SetIdleState(const Pwm_ChObjType *chObj)
{
    const Pwm_ChannelConfigType    *pChannelConfig   = &chObj->chCfg;
    const Pwm_ChannelConfigType_PC *channelConfig_PC = &chObj->chCfg_PC;

    uint32                       baseAddr;
    EPWM_ActionQualifierSWOutput swTrigAction;
    baseAddr = chObj->baseAddr;

    if (PWM_HIGH == pChannelConfig->idleState)
    {
        swTrigAction = EPWM_AQ_SW_OUTPUT_HIGH;
    }
    else
    {
        swTrigAction = EPWM_AQ_SW_OUTPUT_LOW;
    }

    /* Program AQCSFRC Active Register Reload From Shadow Options */
    EPWM_setActionQualifierContSWForceShadowMode(baseAddr, EPWM_AQ_SW_IMMEDIATE_LOAD);

    /* Enable both outputs epwmxA and epwmxB which is same configuration
     * if channelConfig_PC->outputCh == PWM_OUTPUT_CH_BOTH_A_AND_B */
    if (((uint32)PWM_OUTPUT_CH_A == channelConfig_PC->outputCh) ||
        ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == channelConfig_PC->outputCh))
    {
        /* Continuous software forced output on A */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_A, swTrigAction);
    }

    if (((uint32)PWM_OUTPUT_CH_B == channelConfig_PC->outputCh) ||
        ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == channelConfig_PC->outputCh))
    {
        /* Continuous software forced output on B */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_B, swTrigAction);
    }
}

FUNC(void, PWM_CODE) Pwm_HwUnitInit(Pwm_ChObjType *chObj)
{
    uint32                 baseAddr;
    Pwm_ChannelConfigType *pChannelConfig = &chObj->chCfg;
    EPWM_SignalParams      signalParams;
    float32                duty_cycle_percent;
    float32                duty_cycle_percent_int;
    float32                duty_cycle_percent_dec;
    float32                duty_cycle_period;
    uint32                 phwPeriod = 0U;

    baseAddr  = chObj->baseAddr;
    phwPeriod = pChannelConfig->hwPeriod;

    /* Initialize the EPWM module. */
    Pwm_Initialize(baseAddr);

    /* Explicit PWM clock enable must not be performed by driver.*/
    Pwm_ChannelConfigType_PC *channelConfig_PC = &chObj->chCfg_PC;

    if (pChannelConfig->enableHR == TRUE)
    {
        signalParams.tbCtrMode = EPWM_COUNTER_MODE_UP_DOWN;

        duty_cycle_percent = (float32)(((float32)(pChannelConfig->dutyCycle)) / ((float32)32768U));

        /*0x8000 is 32768, calculating percentage from hex*/
        duty_cycle_period      = duty_cycle_percent * (float32)((phwPeriod));
        duty_cycle_percent_int = (float32)((phwPeriod));
        duty_cycle_percent_dec = duty_cycle_percent_int - duty_cycle_period;

        /* Set the parameters of PWM. */
        signalParams.freqInHz = duty_cycle_percent_int;
        /* CMPA/CMPB = (100% - duty cycle) TBPRD  */
        signalParams.dutyValA = duty_cycle_percent_dec;
        signalParams.dutyValB = duty_cycle_percent_dec;

        /* Set the Polarity. */
        if (pChannelConfig->polarity == PWM_HIGH)
        {
            signalParams.invertSignalB = (boolean)0;
        }
        else
        {
            signalParams.invertSignalB = (boolean)1;
        }

        signalParams.sysClkInHz = pChannelConfig->instanceClkHz;

        signalParams.tbClkDiv   = (EPWM_ClockDivider)pChannelConfig->prescale;
        signalParams.tbHSClkDiv = (EPWM_HSClockDivider)pChannelConfig->hsPrescale;

        /* Configure PWM Signal.  */
        PWM_ConfigureSignal(baseAddr, &signalParams);

        /* Configure HR PWM.  */
        Pwm_ConfigHR_epwm(baseAddr, (float32)signalParams.sysClkInHz, (float32)(phwPeriod), duty_cycle_percent_dec,
                          (uint32)channelConfig_PC->outputCh);
    }
    else
    {
        signalParams.tbCtrMode = EPWM_COUNTER_MODE_UP_DOWN;

        /* Calculation for high resolution */
        duty_cycle_percent = (float32)(((float32)(pChannelConfig->dutyCycle)) / ((float32)32768U));

        /*0x8000 is 32768, calculating percentage from hex*/
        duty_cycle_period      = duty_cycle_percent * (float32)(pChannelConfig->hwPeriod);
        duty_cycle_percent_int = (float32)(pChannelConfig->hwPeriod);
        duty_cycle_percent_dec = duty_cycle_percent_int - duty_cycle_period;

        /* Set the parameters of PWM. */
        signalParams.freqInHz = duty_cycle_percent_int;
        signalParams.dutyValA = duty_cycle_period;
        signalParams.dutyValA = duty_cycle_percent_dec;
        signalParams.dutyValB = duty_cycle_period;
        signalParams.dutyValB = duty_cycle_percent_dec;

        /* Set the Polarity. */
        if (pChannelConfig->polarity == PWM_HIGH)
        {
            signalParams.invertSignalB = (boolean)0;
        }
        else
        {
            signalParams.invertSignalB = (boolean)1;
        }

        signalParams.sysClkInHz = pChannelConfig->instanceClkHz;

        signalParams.tbClkDiv   = (EPWM_ClockDivider)pChannelConfig->prescale;
        signalParams.tbHSClkDiv = (EPWM_HSClockDivider)pChannelConfig->hsPrescale;

        /* Configure PWM Signal.  */
        PWM_ConfigureSignal(baseAddr, &signalParams);
    }

    return;
}

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON) || (PWM_SET_DUTY_CYCLE_API == STD_ON)
FUNC(void, PWM_CODE) Pwm_SetDutyCycle_Internal(Pwm_ChObjType *chObj, uint16 DutyCycle)
{
    uint32            period;
    uint32            baseAddr, outputCh, sysClk;
    EPWM_SignalParams signalParams;
    float32           duty_cycle_percent;
    float32           duty_cycle_percent_int;
    float32           duty_cycle_percent_dec;
    float32           duty_cycle_period;

    baseAddr = chObj->baseAddr;
    outputCh = chObj->chCfg_PC.outputCh;
    sysClk   = chObj->chCfg.instanceClkHz;

    /* Reactivate channel if output was forced to idle */
    /*TI_INSPECTED 331 S: MISRAC_2012_7.2
     * "Reason - External Package errors like Compiler which are
     *  not part of MCAL cannot be fixed." */
    /*TI_INSPECTED 434 S: MISRAC_2012_10.3
     * "Reason - Tool Issue Not able to analyse boolean type" */

    /* Check for IDLE state. */
    if ((boolean)TRUE == chObj->channelForcedIdle)
    {
        /* Disable SW Forced Action qualifiers */
        baseAddr = chObj->baseAddr;
        /* Program AQCSFRC Active Register Reload From Shadow Options */
        EPWM_setActionQualifierContSWForceShadowMode(baseAddr, EPWM_AQ_SW_IMMEDIATE_LOAD);

        /* Enable both outputs epwmxA and epwmxB which is same configuration
         * if channelConfig_PC->outputCh == PWM_OUTPUT_CH_BOTH_A_AND_B */
        if (((uint32)PWM_OUTPUT_CH_A == outputCh) || ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on A */
            EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_SW_DISABLED);
        }

        if (((uint32)PWM_OUTPUT_CH_B == outputCh) || ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on B */
            EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_DISABLED);
        }

        /* Enable both outputs epwmxA and epwmxB which is same configuration
         * if channelConfig_PC->outputCh == PWM_OUTPUT_CH_BOTH_A_AND_B */
        if (((uint32)PWM_OUTPUT_CH_A == outputCh) || ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on A */
            EPWM_forceActionQualifierSWAction(baseAddr, EPWM_AQ_OUTPUT_A);
        }

        if (((uint32)PWM_OUTPUT_CH_B == outputCh) || ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on B */
            EPWM_forceActionQualifierSWAction(baseAddr, EPWM_AQ_OUTPUT_B);
        }
        chObj->channelForcedIdle = (boolean)FALSE;
    }

    /* Updating Init time dutyCycle which is used to enable notifications,
     * if the duty cycle is not 0% or 100% */
    chObj->chCfg.dutyCycle = DutyCycle;
    period                 = (uint32)EPWM_getTimeBasePeriod(baseAddr);

    if (chObj->chCfg.enableHR == TRUE)
    {
        signalParams.tbCtrMode = EPWM_COUNTER_MODE_UP_DOWN;

        /* Calculation for high resolution */
        duty_cycle_percent = (float32)(((float32)(chObj->chCfg.dutyCycle)) / ((float32)32768U));

        /*0x8000 is 32768, calculating percentage from hex*/
        duty_cycle_period      = duty_cycle_percent * (float32)(period);
        duty_cycle_percent_int = (float32)(period);
        duty_cycle_percent_dec = duty_cycle_percent_int - duty_cycle_period;

        /* Update DutyCycle */
        /* Check the Output outputCh */
        /* Set the parameters of PWM. */
        signalParams.freqInHz = period;
        /* CMPA/CMPB = (100% - duty cycle) TBPRD  */
        signalParams.dutyValA = duty_cycle_percent_dec;
        signalParams.dutyValB = duty_cycle_percent_dec;
        /* Set the Polarity. */
        if (chObj->chCfg.polarity == PWM_HIGH)
        {
            signalParams.invertSignalB = (boolean)0;
        }
        else
        {
            signalParams.invertSignalB = (boolean)1;
        }

        signalParams.sysClkInHz = sysClk;
        signalParams.tbClkDiv   = (EPWM_ClockDivider)chObj->chCfg.prescale;
        signalParams.tbHSClkDiv = (EPWM_HSClockDivider)chObj->chCfg.hsPrescale;

        /* Genearte the PWM signal. */
        PWM_ConfigureSignal(baseAddr, &signalParams);

        /* Configure HR PWM. */

        Pwm_ConfigHR_epwm(baseAddr, (float32)signalParams.sysClkInHz, signalParams.freqInHz, duty_cycle_percent_dec,
                          (uint32)outputCh);
    }
    else
    {
        signalParams.tbCtrMode = EPWM_COUNTER_MODE_UP_DOWN;

        /* Calculation for high resolution */
        duty_cycle_percent = (float32)(((float32)(chObj->chCfg.dutyCycle)) / ((float32)32768U));

        /*0x8000 is 32768, calculating percentage from hex*/
        duty_cycle_period      = duty_cycle_percent * (float32)(period);
        duty_cycle_percent_int = (float32)(period);
        duty_cycle_percent_dec = duty_cycle_percent_int - duty_cycle_period;

        /* Update DutyCycle */
        /* Check the Output outputCh */
        /* Set the parameters of PWM. */
        signalParams.freqInHz = period;
        signalParams.dutyValA = duty_cycle_percent_dec;
        signalParams.dutyValB = duty_cycle_percent_dec;
        /* Set the Polarity. */
        if (chObj->chCfg.polarity == PWM_HIGH)
        {
            signalParams.invertSignalB = (boolean)0;
        }
        else
        {
            signalParams.invertSignalB = (boolean)1;
        }

        signalParams.sysClkInHz = sysClk;
        signalParams.tbClkDiv   = (EPWM_ClockDivider)chObj->chCfg.prescale;
        signalParams.tbHSClkDiv = (EPWM_HSClockDivider)chObj->chCfg.hsPrescale;

        /* Genearte the PWM signal. */
        PWM_ConfigureSignalDutyOnly(baseAddr, &signalParams);
    }
}
#endif

#if (STD_ON == PWM_DEINIT_API)
FUNC(void, PWM_CODE) Pwm_IpDeInit_epwm(const Pwm_ChObjType *chObj)
{
    uint32 baseAddr = chObj->baseAddr;

    /* Set registers to default value */
    Pwm_HwSetDefReg_epwm(baseAddr);

    Pwm_SetIdleState(chObj);

    /* Disable all Notifications */
    EPWM_disableInterrupt(chObj->baseAddr);
    EPWM_clearEventTriggerInterruptFlag(chObj->baseAddr);

    /* Explicit PWM clock disable must not be performed by driver.
     * Refer TRM for more details */
    return;
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
/*******************************************************************************
 *   Function Name : Pwm_ChannelNotificationISR
 ******************************************************************************/
/*! \Description: Interrupt Subroutine for Notification
 *
 *  \context    Function is called from interrupt level
 ******************************************************************************/
FUNC(void, PWM_CODE) Pwm_ChannelNotificationISR_epwm(Pwm_ChannelType ChannelNumber)
{
    /*TI_INSPECTED 93 S : MISRAC_2012_R.11.1
     * "Reason - Pointer typecast required here to match
     *           destination data type" */
    /*TI_INSPECTED 95 S : MISRAC_2012_R.11.4
     * "Reason - Pointer typecast required here since same element is
     * required to hold different types" */
    /*TI_INSPECTED 606 S : MISRAC_2012_R.11.1
     * "Reason - Pointer typecast required here to match
     *           destination data type" */
    Pwm_NotifyFuncType pwmNotification = (Pwm_NotifyFuncType)NULL_PTR;
    Pwm_ChObjType     *chObj           = &Pwm_ChObj[ChannelNumber];
    EPWM_clearEventTriggerInterruptFlag(chObj->baseAddr);
    if (NULL_PTR != chObj)
    {
        if ((chObj->chCfg.dutyCycle != PWM_DUTY_0_PERCENT) && (chObj->chCfg.dutyCycle != PWM_DUTY_100_PERCENT))
        {
            /* Call Notification */
            if ((Pwm_NotifyFuncType)NULL_PTR != chObj->chCfg.notificationHandler)
            {
                pwmNotification = chObj->chCfg.notificationHandler;
                pwmNotification();
            }
        }
    }
}

#endif /*(STD_ON == PWM_NOTIFICATION_SUPPORTED)*/

#if (STD_ON == PWM_REGISTER_READBACK_API)
FUNC(void, PWM_CODE)
Pwm_IpRegisterReadback_epwm(uint32 baseAddr, Pwm_RegisterReadbackType *RegRbPtr)
{
    RegRbPtr->pwmTbCtl1 = HW_RD_REG16(baseAddr + PWM_EPWM_TBCTL);
    RegRbPtr->pwmTbCtl2 = HW_RD_REG16(baseAddr + PWM_EPWM_TBCTL2);
    RegRbPtr->pwmTbPhs  = HW_RD_REG16(baseAddr + PWM_EPWM_TBPHS);
    RegRbPtr->pwmTbCnt  = HW_RD_REG16(baseAddr + PWM_EPWM_TBCTR);
}
#endif /*PWM_REGISTER_READBACK_API*/

#if (STD_ON == PWM_DEV_ERROR_DETECT)
FUNC(void, PWM_CODE) Pwm_reportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == PWM_DEV_ERROR_DETECT) */

FUNC(void, PWM_CODE)
Pwm_EnableNotification_epwm(Pwm_ChObjType *chObj, const Pwm_ChannelConfigType_PC *channelConfig_PC)
{
    Pwm_OutputStateType polarity;

    /* Design : DES_PWM_018 */
    /* Requirements : MCAL-2056 */
    /* Requirements : MCAL-3598, MCAL-3634*/
    EPWM_clearEventTriggerInterruptFlag(chObj->baseAddr);
    EPWM_enableInterrupt(chObj->baseAddr);
    /* Enable notification only if the duty cycle is not 0% or 100% */
    if ((chObj->chCfg.dutyCycle == PWM_DUTY_0_PERCENT) || (chObj->chCfg.dutyCycle == PWM_DUTY_100_PERCENT))
    {
        /* Generate interrupt when count equal to zero,
         * but do not enable rising/falling edge notification as it is
         * meaningless if duty cycle is 0% or 100% */
        EPWM_setInterruptSource(chObj->baseAddr, EPWM_INT_TBCTR_ZERO, EPWM_INT_TBCTR_ZERO);
    }
    else
    {
        polarity = chObj->chCfg.polarity;
        switch (chObj->Notification)
        {
            case PWM_FALLING_EDGE:
                Pwm_EnableNotification_epwm_FallingEdge(channelConfig_PC->outputCh, chObj->baseAddr, polarity);
                break;
            case PWM_RISING_EDGE:
                Pwm_EnableNotification_epwm_RisingEdge(channelConfig_PC->outputCh, chObj->baseAddr, polarity);
                break;
            case PWM_BOTH_EDGES:
                /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here
                 */
                Pwm_EnableNotification_epwm_BothEdges(channelConfig_PC->outputCh, chObj->baseAddr);
                break;
            default:
                /*Do nothing*/
                break;
        }
    }

    EPWM_setInterruptEventCount(chObj->baseAddr, PWM_EVENT_COUNT);
    EPWM_disableInterruptEventCountInit(chObj->baseAddr);
    EPWM_setInterruptEventCountInitValue(chObj->baseAddr, 0);

    /* Requirements : MCAL-3597*/
    chObj->channelNotifyActiveFlag = (uint32)TRUE;
}

static void Pwm_EnableNotification_epwm_FallingEdge(uint32 outputCh, uint32 baseAddr, Pwm_OutputStateType polarity)
{
    if (polarity == PWM_HIGH)
    {
        if ((uint32)PWM_OUTPUT_CH_A == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPA, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPB, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAD_CBD);
        }
    }
    else
    {
        if ((uint32)PWM_OUTPUT_CH_A == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPA, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPB, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAU_CBU);
        }
    }
}

static void Pwm_EnableNotification_epwm_RisingEdge(uint32 outputCh, uint32 baseAddr, Pwm_OutputStateType polarity)
{
    if (polarity == PWM_HIGH)
    {
        if ((uint32)PWM_OUTPUT_CH_A == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPA, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPB, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAU_CBU);
        }
    }
    else
    {
        if ((uint32)PWM_OUTPUT_CH_A == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPA, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPB, EPWM_INT_TBCTR_ZERO);
        }

        if ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
        {
            EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAD_CBD);
        }
    }
}

static void Pwm_EnableNotification_epwm_BothEdges(uint32 outputCh, uint32 baseAddr)
{
    if ((uint32)PWM_OUTPUT_CH_A == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, 0x000CU);
    }

    if ((uint32)PWM_OUTPUT_CH_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, 0x0020U);
    }

    if ((uint32)PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, 0x003CU);
    }
}

FUNC(void, PWM_CODE) Pwm_setTimeBasePeriod_epwm(uint32 baseAddr, uint32 hwPeriod)
{
    EPWM_setTimeBasePeriod(baseAddr, (uint16)hwPeriod);
}

FUNC(void, PWM_CODE) Pwm_disableInterrupt_epwm(uint32 baseAddr)
{
    EPWM_clearEventTriggerInterruptFlag(baseAddr);
    EPWM_disableInterrupt(baseAddr);
}

/*****************************************************************************

 PWM_configureSignal

******************************************************************************/
FUNC(void, PWM_CODE) PWM_ConfigureSignalDutyOnly(uint32 base, const EPWM_SignalParams *signalParams)
{
    uint16 cmpAVal = 0U, cmpBVal = 0U;

    cmpAVal = (uint16)(signalParams->dutyValA);
    cmpBVal = (uint16)(signalParams->dutyValB);

    /*
     Setup shadow register load on ZERO
    */
    EPWM_setCounterCompareShadowLoadMode(base, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(base, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    /*
     Set Compare values
    */
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_A, cmpAVal);
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B, cmpBVal);

    /*
 Set actions for ePWMxA & ePWMxB
*/
    if (signalParams->tbCtrMode == EPWM_COUNTER_MODE_UP_DOWN)
    {
        /*
         Clear PWMxA on Zero
        */
        EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

        /*
         Set PWMxA on event A, up count
        */
        EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

        /*
         Clear PWMxA on event A, down count
        */
        EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

        if (signalParams->invertSignalB == TRUE)
        {
            /*
             Set PWMxB on Zero
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

            /*
             Clear PWMxB on event B, up count
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
            /*
             Set PWMxB on event B, down count
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
        }
        else
        {
            /*
             Clear PWMxB on Zero
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

            /*
             Set PWMxB on event B, up count
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
            /*
             Clear PWMxB on event B, down count
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
        }
    }
    else
    {
        /* do nothing */
    }
}

/*****************************************************************************

 PWM_configureSignal

******************************************************************************/
FUNC(void, PWM_CODE) PWM_ConfigureSignal(uint32 base, const EPWM_SignalParams *signalParams)
{
    uint16 tbPrdVal = 0U;

    /*
     Configure Time Base counter Clock
    */
    EPWM_setClockPrescaler(base, signalParams->tbClkDiv, signalParams->tbHSClkDiv);

    /*
     Configure Time Base Counter Mode
    */
    EPWM_setTimeBaseCounterMode(base, signalParams->tbCtrMode);

    tbPrdVal = (uint16)(signalParams->freqInHz);

    /*
     Configure TBPRD value
    */
    EPWM_setTimeBasePeriod(base, tbPrdVal);

    /*
     Default Configurations.
    */
    EPWM_disablePhaseShiftLoad(base);
    EPWM_setPhaseShift(base, 0U);
    EPWM_setTimeBaseCounter(base, 0U);

    PWM_ConfigureSignalDutyOnly(base, signalParams);
}

FUNC(void, PWM_CODE)
Pwm_ConfigHR_epwm(uint32 baseAddr, float32 sysClk, float32 peroid, float32 Duty, uint32 outputCh)
{
    (void)peroid;
    uint32  Ctrladdr = 0;
    float32 abduty   = 0;
    uint32  intduty  = 0;
    float32 temp_val;
    float32 highRes_regVal;

#if (STD_ON == PWM_SFO_SUPPORT_ENABLE)
    uint32          Pwm_SFO_status = PWM_SFO_INCOMPLETE;
    volatile uint32 tempCount      = PWM_MAX_TIMEOUT_DURATION;
    if (PWM_MAX_TIMEOUT_DURATION > 9U)
    {
        /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
        tempCount = PWM_MAX_TIMEOUT_DURATION / 9U;
    }
#endif

#if (STD_OFF == PWM_SFO_SUPPORT_ENABLE)
    uint32  Pwm_MEP_step = 150U; /*150ps choosen, for 100MHZ*/
    /* TBCLK/MEP_step_size_am263x = 5ns/150ps*/
    float32 tbCLK       = ((float32)1U / sysClk);
    Pwm_MEP_ScaleFactor = tbCLK / ((float32)Pwm_MEP_step * 0.000000000001);
#endif

    intduty        = (uint32)(Duty);
    abduty         = (float32)Duty - (float32)(intduty);
    temp_val       = (float32)((abduty * ((float32)Pwm_MEP_ScaleFactor)));
    highRes_regVal = (temp_val * (float32)256U) + (float32)0.5;

    Ctrladdr = Pwm_gOttoCal_base;

    /* Enable MEP Scale Step. */
    HRPWM_setMEPStep(Ctrladdr, (uint16)Pwm_MEP_ScaleFactor);

#if (STD_ON == PWM_SFO_SUPPORT_ENABLE)
    /*

*  Calling SFO() updates the HRMSTEP register with calibrated MEP_ScaleFactor.
*  HRMSTEP must be populated with a scale factor value prior to enabling
*  high resolution period control.
*/
    while (Pwm_SFO_status == PWM_SFO_INCOMPLETE)
    {
        Pwm_SFO_status = Pwm_SFO();
        /* Below API can change start time, so use temp variable */
        if ((Pwm_SFO_status == PWM_SFO_ERROR) || (tempCount <= 0U))
        {
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
#endif

    /* Enable Period Control. */
    HRPWM_enablePeriodControl(baseAddr);
    HRPWM_enablePhaseShiftLoad(baseAddr);

    /* Set the Channel for HR PWM.  */
    Pwm_ConfigHR_epwm_Internal(outputCh, baseAddr, Duty, highRes_regVal);
    Pwm_ConfigHR_epwm_Internal1(outputCh, baseAddr, Duty, highRes_regVal);

    /* Enable Auto conversion. */
    HRPWM_enableAutoConversion(baseAddr);

    /* Call the scale factor optimizer lib function SFO()
       periodically to track for any change due to temp/voltage.
       This function generates MEP_ScaleFactor by running the
       MEP calibration module in the HRPWM logic.*/

#if (STD_ON == PWM_SFO_SUPPORT_ENABLE)
    Pwm_SFO_status = Pwm_SFO();
#endif
}

static void Pwm_ConfigHR_epwm_Internal(uint32 outputCh, uint32 baseAddr, float32 Duty, float32 highRes_regVal)
{
    if (((uint32)EPWM_HR_PWMA == outputCh) || ((uint32)EPWM_HR_PWMA_B == outputCh))
    {
        HRPWM_setCounterCompareValue(baseAddr, HRPWM_COUNTER_COMPARE_A, (uint32)Duty << 8U);
        HRPWM_setHiResCounterCompareValue(baseAddr, HRPWM_COUNTER_COMPARE_A, (uint16)(highRes_regVal));
        HRPWM_setMEPEdgeSelect(baseAddr, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
        HRPWM_setMEPControlMode(baseAddr, HRPWM_CHANNEL_A, HRPWM_MEP_DUTY_PERIOD_CTRL);
        HRPWM_setCounterCompareShadowLoadEvent(baseAddr, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    }
}

static void Pwm_ConfigHR_epwm_Internal1(uint32 outputCh, uint32 baseAddr, float32 Duty, float32 highRes_regVal)
{
    if (((uint32)EPWM_HR_PWMB == outputCh) || ((uint32)EPWM_HR_PWMA_B == outputCh))
    {
        HRPWM_setCounterCompareValue(baseAddr, HRPWM_COUNTER_COMPARE_B, (uint32)Duty << 8U);
        HRPWM_setHiResCounterCompareValue(baseAddr, HRPWM_COUNTER_COMPARE_B, (uint16)(highRes_regVal));
        HRPWM_setMEPEdgeSelect(baseAddr, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
        HRPWM_setMEPControlMode(baseAddr, HRPWM_CHANNEL_B, HRPWM_MEP_DUTY_PERIOD_CTRL);
        HRPWM_setCounterCompareShadowLoadEvent(baseAddr, HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    }
}

FUNC(void, PWM_CODE) Pwm_HwSetDefReg_epwm(uint32 baseAddr)
{
    /*
      Init all registers to default value
     */
    HW_WR_REG16((baseAddr + PWM_EPWM_TBCTL), (uint16)PWM_EPWM_TBCTL_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_TBCTL2), (uint16)PWM_EPWM_TBCTL2_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_CMPCTL), (uint16)PWM_EPWM_CMPCTL_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_CMPA), (uint16)PWM_EPWM_CMPA_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_CMPB), (uint16)PWM_EPWM_CMPB_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_AQCTLA), (uint16)PWM_EPWM_AQCTLA_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_AQCTLB), (uint16)PWM_EPWM_AQCTLB_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_AQSFRC), (uint16)PWM_EPWM_AQSFRC_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_AQCSFRC), (uint16)PWM_EPWM_AQCSFRC_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_TZSEL), (uint16)PWM_EPWM_TZSEL_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_ETPS), (uint16)PWM_EPWM_ETPS_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_EPWM_DECLR), (uint16)PWM_EPWM_DECLR_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_OTTOCAL_HRPWR), (uint16)PWM_OTTOCAL_HRPWR_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_OTTOCAL_HRCAL), (uint16)PWM_OTTOCAL_HRCAL_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_OTTOCAL_HRPRD), (uint16)PWM_OTTOCAL_HRPRD_RESETVAL);
    HW_WR_REG16((baseAddr + PWM_OTTOCAL_HRMSTEP), (uint16)PWM_OTTOCAL_HRMSTEP_RESETVAL);

    return;
}

void Pwm_Initialize(uint32 epwmbaseadrr)
{
    /* Time Base */
    EPWM_setEmulationMode(epwmbaseadrr, EPWM_EMULATION_FREE_RUN);
    EPWM_setClockPrescaler(epwmbaseadrr, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(epwmbaseadrr, 0);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_TBPRD_TBPRDHR);
    EPWM_setTimeBaseCounter(epwmbaseadrr, 0);
    EPWM_setTimeBaseCounterMode(epwmbaseadrr, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(epwmbaseadrr);
    EPWM_setPhaseShift(epwmbaseadrr, 0);
    EPWM_enableSyncOutPulseSource(epwmbaseadrr, 0);
    EPWM_setSyncInPulseSource(epwmbaseadrr, EPWM_SYNC_IN_PULSE_SRC_DISABLE);
    EPWM_setOneShotSyncOutTrigger(epwmbaseadrr, EPWM_OSHT_SYNC_OUT_TRIG_SYNC);
    EPWM_forceSyncPulse(epwmbaseadrr);

    /* Counter Compare */
    EPWM_setCounterCompareValue(epwmbaseadrr, EPWM_COUNTER_COMPARE_A, 0);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_CMPA_CMPAHR);

    EPWM_setCounterCompareShadowLoadMode(epwmbaseadrr, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(epwmbaseadrr, EPWM_COUNTER_COMPARE_B, 0);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_CMPB_CMPBHR);

    EPWM_setCounterCompareShadowLoadMode(epwmbaseadrr, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(epwmbaseadrr, EPWM_COUNTER_COMPARE_C, 0);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_CMPC);

    EPWM_setCounterCompareShadowLoadMode(epwmbaseadrr, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(epwmbaseadrr, EPWM_COUNTER_COMPARE_D, 0);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_CMPD);

    EPWM_setCounterCompareShadowLoadMode(epwmbaseadrr, EPWM_COUNTER_COMPARE_D, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    /* Action Qualifier */
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCSFRC);
    EPWM_setActionQualifierContSWForceShadowMode(epwmbaseadrr, EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLA_AQCTLA2);
    EPWM_disableActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_A);
    EPWM_setActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_A, EPWM_AQ_LOAD_ON_CNTR_ZERO);
    EPWM_setActionQualifierT1TriggerSource(epwmbaseadrr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierT2TriggerSource(epwmbaseadrr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierSWAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE);
    EPWM_setActionQualifierContSWForceAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_SW_DISABLED);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);
    EPWM_disableActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_B);
    EPWM_setActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_B, EPWM_AQ_LOAD_ON_CNTR_ZERO);
    EPWM_setActionQualifierT1TriggerSource(epwmbaseadrr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierT2TriggerSource(epwmbaseadrr, EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1);
    EPWM_setActionQualifierSWAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE);
    EPWM_setActionQualifierContSWForceAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_DISABLED);

    /* Event Trigger */
    EPWM_disableInterrupt(epwmbaseadrr);
    EPWM_setInterruptSource(epwmbaseadrr, EPWM_INT_TBCTR_ZERO, EPWM_INT_TBCTR_ZERO);
    EPWM_setInterruptEventCount(epwmbaseadrr, 0);
    EPWM_disableInterruptEventCountInit(epwmbaseadrr);
    EPWM_setInterruptEventCountInitValue(epwmbaseadrr, 0);

    /* HRPWM */
    HRPWM_disableAutoConversion(epwmbaseadrr);
    HRPWM_setMEPControlMode(epwmbaseadrr, HRPWM_CHANNEL_A, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_setMEPControlMode(epwmbaseadrr, HRPWM_CHANNEL_B, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_setHiResPhaseShift(epwmbaseadrr, 0);
    HRPWM_setSyncPulseSource(epwmbaseadrr, HRPWM_PWMSYNC_SOURCE_PERIOD);
    HRPWM_disablePhaseShiftLoad(epwmbaseadrr);
    HRPWM_setMEPEdgeSelect(epwmbaseadrr, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_DISABLE);
    HRPWM_setMEPEdgeSelect(epwmbaseadrr, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_DISABLE);
    HRPWM_setHiResCounterCompareValue(epwmbaseadrr, HRPWM_COUNTER_COMPARE_A, 1);
    HRPWM_setHiResCounterCompareValue(epwmbaseadrr, HRPWM_COUNTER_COMPARE_B, 1);
    HRPWM_setCounterCompareShadowLoadEvent(epwmbaseadrr, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO);
    HRPWM_setCounterCompareShadowLoadEvent(epwmbaseadrr, HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO);
    HRPWM_disablePeriodControl(epwmbaseadrr);
    HRPWM_setHiResTimeBasePeriod(epwmbaseadrr, 0);
    HRPWM_setDeadbandMEPEdgeSelect(epwmbaseadrr, HRPWM_DB_MEP_CTRL_DISABLE);
    HRPWM_setHiResRisingEdgeDelay(epwmbaseadrr, 0);
    HRPWM_setRisingEdgeDelayLoadMode(epwmbaseadrr, HRPWM_LOAD_ON_CNTR_ZERO);
    HRPWM_setHiResFallingEdgeDelayOnly(epwmbaseadrr, 0);
    HRPWM_setFallingEdgeDelayLoadMode(epwmbaseadrr, HRPWM_LOAD_ON_CNTR_ZERO);
    HRPWM_setOutputSwapMode(epwmbaseadrr, FALSE);
    HRPWM_setChannelBOutputPath(epwmbaseadrr, HRPWM_OUTPUT_ON_B_NORMAL);

    /* Global Load */
    EPWM_disableGlobalLoad(epwmbaseadrr);
    EPWM_setGlobalLoadTrigger(epwmbaseadrr, EPWM_GL_LOAD_PULSE_CNTR_ZERO);
    EPWM_setGlobalLoadEventPrescale(epwmbaseadrr, 0);
    EPWM_disableGlobalLoadOneShotMode(epwmbaseadrr);
}

FUNC(void, PWM_CODE) Pwm_SystemInit(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) ConfigPtr)
{
    uint32 chIdx, chnum;

    /* Only initialize configured resources */
    for (chnum = 0U; chnum < PWM_HW_MAX_NUM_CHANNELS; chnum++)
    {
        for (chIdx = 0U; chIdx < PWM_MAX_NUM_CHANNELS; chIdx++)
        {
            if (chnum == Pwm_Config_PC.chCfg[chIdx].channelHwId)
            {
                Pwm_IsrIndex[chnum] = (uint16)chIdx;
                break;
            }
            else
            {
                Pwm_IsrIndex[chnum] = PWM_ISR_MAX;
            }
        }
    }

    /* Only initialize configured resources */
    for (chnum = 0U; chnum < PWM_MAX_NUM_CHANNELS; chnum++)
    {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        if (((&Pwm_Config_PC)->chCfg[chnum].channelId) >= (uint32)PWM_HW_MAX_NUM_CHANNELS)
        {
            /*Invalid channel */
            (void)Pwm_reportDetError(PWM_SID_INIT, PWM_E_PARAM_CHANNEL);
        }
#endif
        for (chIdx = 0U; chIdx < PWM_MAX_NUM_CHANNELS; chIdx++)
        {
            if (chIdx == ((&Pwm_Config_PC)->chCfg[chnum].channelId))
            {
                /* Reset Channel object */
                Pwm_ResetChObj(&Pwm_ChObj[chIdx]);
                /* Copy the configuration */
                Pwm_CopyConfig(&Pwm_ChObj[chIdx], &ConfigPtr->chCfg[chnum], &Pwm_Config_PC.chCfg[chnum]);
                /*Set interrupt flag as per polarity : this is toggled in the
                ISR for supporting notifications*/
                Pwm_Intrflag[chIdx] = Pwm_ChObj[chIdx].chCfg.polarity;
                /* HW Channel Init */
                Pwm_HwUnitInit(&Pwm_ChObj[chIdx]);
/* The function Pwm_Init shall disable all notifications */
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
                Pwm_ChObj[chIdx].channelNotifyActiveFlag = (uint32)FALSE;
#endif
                Pwm_ChObj[chIdx].channelState = PWM_STATUS_INIT;
                break;
            }
        }
    }
}

FUNC(void, PWM_CODE) Pwm_SystemDeInit(void)
{
    uint32 chIdx;

    /* Set driver status  to uninitialized */
    Pwm_DrvStatus = PWM_STATUS_UNINIT;
    for (chIdx = 0U; chIdx < PWM_MAX_NUM_CHANNELS; chIdx++)
    {
        if (PWM_STATUS_INIT == (Pwm_ChObj[chIdx].channelState))
        {
#if (STD_ON == PWM_DEINIT_API)
            Pwm_IpDeInit_epwm(&Pwm_ChObj[chIdx]);
#endif
            /*
             * The function Pwm_Deinit shall disable all interrupt
             * notifications controlled by the PWM driver.
             */
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
            Pwm_ChObj[chIdx].channelNotifyActiveFlag = (uint32)FALSE;
#endif
            Pwm_ChObj[chIdx].channelState = PWM_STATUS_UNINIT;
        }
    }
    /* Reset driver object */
    Pwm_ResetChObj(&Pwm_ChObj[0U]);

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    Pwm_DrvStatus = PWM_STATUS_UNINIT;
#endif
}

FUNC(void, PWM_CODE) Pwm_SystemSetOutputToIdle(Pwm_ChannelType ChannelNumber)
{
    Pwm_ChObjType *chObj = &Pwm_ChObj[ChannelNumber];
    Pwm_SetIdleState(chObj);
    chObj->channelForcedIdle = (boolean)TRUE;
}

FUNC(void, PWM_CODE)
Pwm_SystemEnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification)
{
    Pwm_ChObjType *chObj = &Pwm_ChObj[ChannelNumber];

    chObj->Notification = Notification;

    Pwm_EnableNotification_epwm(&Pwm_ChObj[ChannelNumber], &chObj->chCfg_PC);
}
FUNC(void, PWM_CODE) Pwm_SystemDisableNotification(Pwm_ChannelType ChannelNumber)
{
    Pwm_ChObjType *chObj = &Pwm_ChObj[ChannelNumber];
    Pwm_disableInterrupt_epwm(chObj->baseAddr);
    /* Set the notification active flag to FALSE */
    chObj->channelNotifyActiveFlag = (uint32)FALSE;
}

#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
FUNC(void, PWM_CODE)
Pwm_SystemSetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle)
{
    Pwm_ChObjType *chObj  = &Pwm_ChObj[ChannelNumber];
    chObj->chCfg.hwPeriod = Period;

    Pwm_setTimeBasePeriod_epwm(chObj->baseAddr, chObj->chCfg.hwPeriod);
    if (Period == 0U)
    {
        Pwm_SetDutyCycle_Internal(chObj, (uint16)0U);
    }
    else
    {
        Pwm_SetDutyCycle_Internal(chObj, DutyCycle);
    }
}
#endif /*#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)*/

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON) || (PWM_SET_DUTY_CYCLE_API == STD_ON)
FUNC(void, PWM_CODE)
Pwm_SystemSetDutyCycle_Internal(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    Pwm_ChObjType *chObj = &Pwm_ChObj[ChannelNumber];
    Pwm_SetDutyCycle_Internal(chObj, DutyCycle);
}
#endif /*#if (PWM_SET_PERIOD_AND_DUTY_API==STD_ON) || \ \
    (PWM_SET_DUTY_CYCLE_API == STD_ON)*/

#if (STD_ON == PWM_REGISTER_READBACK_API)
void Pwm_HwRegisterReadback(Pwm_RegisterReadbackType *RegRbPtr, Pwm_ChannelType Channel)
{
    uint32         baseAddr;
    Pwm_ChObjType *chObj = &Pwm_ChObj[Channel];
    (void)memset(RegRbPtr, 0, sizeof(Pwm_RegisterReadbackType));
    baseAddr = chObj->baseAddr;
    Pwm_IpRegisterReadback_epwm(baseAddr, RegRbPtr);
}
#endif

#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_GetOutputstate_Deterror(Pwm_ChannelType ChannelNumber)
{
    /* do nothing*/
    return 0;
}
#endif

#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_SetOutputToIdle_Deterror(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;
    if (ChannelNumber >= (uint32)PWM_MAX_NUM_CHANNELS)
    {
/*Invalid channel */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_SET_OUTPUT_TO_IDLE, PWM_E_PARAM_CHANNEL);
#endif
        returnval = E_NOT_OK;
    }
    else
    {
        if (PWM_STATUS_INIT != Pwm_DrvStatus)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_SET_OUTPUT_TO_IDLE, PWM_E_UNINIT);
#endif
            returnval = E_NOT_OK;
        }
    }
    /* (STD_ON == PWM_DEV_ERROR_DETECT) */
    return returnval;
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(Std_ReturnType, PWM_CODE) Pwm_DisableNotify_Deterror(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;
    if (ChannelNumber >= (uint32)PWM_MAX_NUM_CHANNELS)
    {
/*Invalid channel */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_DISABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL);
#endif
        returnval = E_NOT_OK;
    }
    else
    {
        if (PWM_STATUS_INIT != Pwm_DrvStatus)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_DISABLE_NOTIFICATION, PWM_E_UNINIT);
#endif
            returnval = E_NOT_OK;
        }
    }
    return returnval;
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(Std_ReturnType, PWM_CODE) Pwm_EnableNotify_Deterror(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;

    if (ChannelNumber >= (uint32)PWM_MAX_NUM_CHANNELS)
    {
/*Invalid channel */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_ENABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL);
#endif /* #if (STD_ON == PWM_DEV_ERROR_DETECT)*/
        returnval = E_NOT_OK;
    }

    else
    {
        Pwm_ChObjType *chObj = &Pwm_ChObj[ChannelNumber];
        if (PWM_STATUS_INIT != Pwm_DrvStatus)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_ENABLE_NOTIFICATION, PWM_E_UNINIT);
#endif /* #if (STD_ON == PWM_DEV_ERROR_DETECT)*/
            returnval = E_NOT_OK;
        }
        else if ((Pwm_NotifyFuncType)NULL_PTR == chObj->chCfg.notificationHandler)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_ENABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL);
#endif /* #if (STD_ON == PWM_DEV_ERROR_DETECT)*/
            returnval = E_NOT_OK;
        }
        else
        {
            /* do nothing */
        }
    }
    return returnval;
}
#endif

#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_SetPeriodAndDuty_Deterror(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    Std_ReturnType returnval = E_OK;

    if (ChannelNumber >= (uint32)PWM_MAX_NUM_CHANNELS)
    {
        /*Invalid channel */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_PARAM_CHANNEL);
#endif
        returnval = E_NOT_OK;
    }
    else
    {
        Pwm_ChObjType *chObj = &Pwm_ChObj[ChannelNumber];

        if (PWM_STATUS_INIT != Pwm_DrvStatus)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_UNINIT);
#endif
            returnval = E_NOT_OK;
        }
        if ((chObj->chCfg.channelClass != PWM_VARIABLE_PERIOD) && (returnval == (Std_ReturnType)E_OK))
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_PERIOD_UNCHANGEABLE);
#endif
            returnval = E_NOT_OK;
        }
        else if (DutyCycle > PWM_DUTYCYCLE_MAX)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_PARAM_CHANNEL);
#endif /* (STD_ON == PWM_DEV_ERROR_DETECT) */

            returnval = E_NOT_OK;
        }
        else
        {
            /* do nothing */
        }
    }
    return returnval;
}
#endif

#if (STD_ON == PWM_SET_DUTY_CYCLE_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_SetDutyCycle_Deterror(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    Std_ReturnType returnval = E_OK;

    if (ChannelNumber >= (uint32)PWM_MAX_NUM_CHANNELS)
    {
/*Invalid channel */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_SET_DUTY_CYCLE, PWM_E_PARAM_CHANNEL);
        returnval = E_NOT_OK;
#endif
    }
    else
    {
        if (PWM_STATUS_INIT != Pwm_DrvStatus)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_SET_DUTY_CYCLE, PWM_E_UNINIT);
#endif
            returnval = E_NOT_OK;
        }
        else if (DutyCycle > PWM_DUTY_100_PERCENT)
        {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
            (void)Pwm_reportDetError(PWM_SID_SET_DUTY_CYCLE, PWM_E_PARAM_CHANNEL);
#endif
            returnval = E_NOT_OK;
        }
        else
        {
            /* do nothing */
        }
    }
    return returnval;
}
#endif

#if (STD_ON == PWM_REGISTER_READBACK_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_HwRegReadback_Deterror(Pwm_ChannelType ChannelNumber,
                           P2VAR(Pwm_RegisterReadbackType, AUTOMATIC, PWM_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = E_OK;

    if (ChannelNumber >= (uint32)PWM_MAX_NUM_CHANNELS)
    {
/*Invalid channel */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_REGISTER_READBACK, PWM_E_PARAM_CHANNEL);
#endif
        retVal = E_NOT_OK;
    }
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_REGISTER_READBACK, PWM_E_UNINIT);
#endif
        retVal = E_NOT_OK;
    }
    else if (NULL_PTR == RegRbPtr)
    {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_REGISTER_READBACK, PWM_E_PARAM_POINTER);
#endif
        retVal = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }
    return retVal;
}
#endif

#if (STD_ON == PWM_DEINIT_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_Deinit_Deterror(void)
{
    Std_ReturnType returnval = E_OK;

    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
/* If the driver is not initialized, the function shall raise the error
 * PWM_E_UNINIT */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        Pwm_reportDetError(PWM_SID_DEINIT, PWM_E_UNINIT);
#endif
        returnval = E_NOT_OK;
    }

    return returnval;
}
#endif

#if (STD_ON == PWM_VERSION_INFO_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_GetVersionInfo_Deterror(P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA) VersionInfoPtr)
{
    Std_ReturnType returnval = E_OK;

    if (NULL_PTR == VersionInfoPtr)
    {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        Pwm_reportDetError(PWM_SID_GET_VERSION_INFO, PWM_E_PARAM_POINTER);
#endif
        returnval = E_NOT_OK;
    }

    return returnval;
}
#endif

FUNC(Std_ReturnType, PWM_CODE)
Pwm_Init_Deterror(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) ConfigPtr)
{
    Std_ReturnType returnval = E_OK;

    if (NULL_PTR == ConfigPtr)
    {
        /*
         * ConfigPtr must not be NULL. In case it is NULL report an error and
         * return immediately.
         */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_INIT, PWM_E_INIT_FAILED);
        returnval = E_NOT_OK;
#endif /*(STD_ON == PWM_DEV_ERROR_DETECT) */
    }

    if (PWM_STATUS_INIT == Pwm_DrvStatus)
    {
        /*
         * Pwm module must not be initialized.
         * Otherwise call the Det with PWM_E_ALREADY_INITIALIZED
         */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_reportDetError(PWM_SID_INIT, PWM_E_ALREADY_INITIALIZED);
#endif /*(STD_ON == PWM_DEV_ERROR_DETECT) */
        returnval = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }

    return returnval;
}

#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
FUNC(Pwm_OutputStateType, PWM_CODE) Pwm_SystemGetOutputState(Pwm_ChannelType ChannelNumber)
{
    /* Not Supported for AM263x. */
    return PWM_LOW;
}
#endif

#define PWM_STOP_SEC_CODE
#include "Pwm_MemMap.h"
