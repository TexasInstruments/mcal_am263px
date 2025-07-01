/*
 * Copyright (C) 2022 Texas Instruments Incorporated - www.ti.com
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Pwm_Priv.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec "
#include "Pwm_MemMap.h"*/

/* Klocwork inspected. MISRA C 2012 Rule 11.4
  Explicitly cast for register address */

static void *PwmBaseAddresses[3] = {
    (void *)SOC_EPWM1_BASE,
    (void *)SOC_EPWM2_BASE,
    (void *)SOC_EPWM3_BASE,
};

#define PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec "
#include "Pwm_MemMap.h" */

/*#define PWM_START_SEC_VAR_INIT_PTR
LDRA_INSPECTED 338 S : MISRAC_2012_D_20_1
 * "Reason - Memmap file can't have include guard. "
#include "Pwm_MemMap.h" */

#define PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"

/* reference to the current global runtime configuration */
static P2CONST(Pwm_ConfigType, PWM_VAR, PWM_PBCFG) PwmConfigPtr = (const Pwm_ConfigType *)NULL_PTR;

#define PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"
/*#define PWM_STOP_SEC_VAR_INIT_PTR
LDRA_INSPECTED 338 S : MISRAC_2012_D_20_1
 * "Reason - Memmap file can't have include guard. "
#include "Pwm_MemMap.h"*/

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define PWM_START_SEC_CODE
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections. " */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file can't have include guard. " */
#include "Pwm_MemMap.h"

PWM_Handle Init_EPWM(Pwm_ChannelType pwmAddrIdx)
{
    PWM_Handle pwmHnd = (PWM_Handle)NULL_PTR;

    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.1 */
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    /* assign the handle (PWM register address) */
    pwmHnd = (PWM_Handle)(PwmBaseAddresses[pwmAddrIdx]);
    /*Initialize the PWM registers*/
    /*LDRA_INSPECTED 45 D : MISRAC_2012_D.4.1 Reason : Pointer check already performed  */
    InitPwm((PWM_Obj *)pwmHnd);

    /*LDRA_INSPECTED 71 S : MISRAC_2012_R.18.6 Reason : Need to return the driver obj handle*/
    return (pwmHnd);
}

PWM_Handle GetPwmChannelObj(Pwm_ChannelType channel)
{
    PWM_Handle pwmHnd = (PWM_Handle)NULL_PTR;
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.1 */
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    pwmHnd = (PWM_Handle)(PwmBaseAddresses[channel]);
    /*LDRA_INSPECTED 71 S : MISRAC_2012_R.18.6 Reason : Need to return the driver address*/
    return (pwmHnd);
}

/** @fn void InitPwm(PWM_Obj *pwmHnd)
 *   @brief Initializes the eTPWM Driver
 *
 *   This function initializes the eTPWM module.
 *
 *   @note This function sets the time-base counters in up-count mode.
 *   Application can configure the module in a different mode using other functions in this
 * driver.(Sample code provided in the examples folder) In that case, application need not call
 * InitPwm function. pinmuxInit needs to be called before this function.
 *
 */
void InitPwm(PWM_Obj *pwmHnd)
{
    /* USER CODE BEGIN (1) */
    /* USER CODE END */

    /** @b initialize @b ETPWM1 */

    /** - Sets high speed time-base clock prescale bits */
    pwmHnd->TBCTL = (uint16)0U << 7U;

    /** - Sets time-base clock prescale bits */
    pwmHnd->TBCTL |= (uint16)((uint16)0U << 10U);

    /** - Mode setting for Dead Band Module
     *     -Select the input mode for Dead Band Module
     *     -Select the output mode for Dead Band Module
     *     -Select Polarity of the output PWMs
     */
    pwmHnd->DBCTL = ((uint16)((uint16)0U << 5U)     /* Source for Falling edge delay(0-PWMA, 1-PWMB) */
                     | (uint16)((uint16)0u << 4U)   /* Source for Rising edge delay(0-PWMA, 1-PWMB) */
                     | (uint16)((uint16)0U << 3U)   /* Enable/Disable EPWMxB invert       */
                     | (uint16)((uint16)0U << 2U)   /* Enable/Disable EPWMxA invert       */
                     | (uint16)((uint16)0U << 1U)   /* Enable/Disable Rising Edge Delay   */
                     | (uint16)((uint16)0U << 0U)); /* Enable/Disable Falling Edge Delay  */

    /** - Set the rising edge delay  */
    pwmHnd->DBRED = 110U;

    /** - Set the falling edge delay  */
    pwmHnd->DBFED = 110U;

    /** - Enable the chopper module for ETPWMx
     *     -Sets the One shot pulse width in a chopper modulated wave
     *     -Sets the dutycycle for the subsequent pulse train
     *     -Sets the period for the subsequent pulse train
     */
    pwmHnd->PCCTL = ((uint16)((uint16)0U << 0U)     /* Enable/Disable chopper module */
                     | (uint16)((uint16)0U << 1U)   /* One-shot Pulse Width */
                     | (uint16)((uint16)3U << 8U)   /* Chopping Clock Duty Cycle */
                     | (uint16)((uint16)0U << 5U)); /* Chopping Clock Frequency */

    /** - Set trip source enable */
    pwmHnd->TZSEL = 0x0000U    /** - Enable/Disable TZ1 as a one-shot trip source */
                    | 0x0000U  /** - Enable/Disable TZ2 as a one-shot trip source */
                    | 0x0000U  /** - Enable/Disable TZ3 as a one-shot trip source */
                    | 0x0000U  /** - Enable/Disable TZ4 as a one-shot trip source */
                    | 0x0000U  /** - Enable/Disable TZ5 as a one-shot trip source */
                    | 0x0000U  /** - Enable/Disable TZ6 as a one-shot trip source */
                    | 0x0000U  /** - Enable/Disable TZ1 as a CBC trip source      */
                    | 0x0000U  /** - Enable/Disable TZ2 as a CBC trip source      */
                    | 0x0000U  /** - Enable/Disable TZ3 as a CBC trip source      */
                    | 0x0000U  /** - Enable/Disable TZ4 as a CBC trip source      */
                    | 0x0000U  /** - Enable/Disable TZ5 as a CBC trip source      */
                    | 0x0000U; /** - Enable/Disable TZ6 as a CBC trip source      */

    /** - Set interrupt enable */
    pwmHnd->TZEINT = 0x0000U    /** - Enable/Disable Digital Comparator Output A Event 1  */
                     | 0x0000U  /** - Enable/Disable Digital Comparator Output A Event 2  */
                     | 0x0000U  /** - Enable/Disable Digital Comparator Output A Event 1  */
                     | 0x0000U  /** - Enable/Disable Digital Comparator Output A Event 2  */
                     | 0x0000U  /** - Enable/Disable one-shot interrupt generation        */
                     | 0x0000U; /** - Enable/Disable cycle-by-cycle interrupt generation  */

    /** - Sets up the event for interrupt */
    pwmHnd->ETSEL = (uint16)NO_EVENT;

    /** - Setup the frequency of the interrupt generation */
    pwmHnd->ETPS = 1U;

    /** - Sets up the ADC SOC interrupt */
    pwmHnd->ETSEL |= ((uint16)(0x0000U) |
                      (uint16)(0x0000U)
                      /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
                      /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
                      | (uint16)((uint16)DCAEVT1 << 8U)
                      /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
                      /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
                      | (uint16)((uint16)DCBEVT1 << 12U));

    /** - Sets up the ADC SOC period */
    pwmHnd->ETPS |= ((uint16)((uint16)1U << 8U) | (uint16)((uint16)1U << 12U));

    /** @b initialize @b ETPWM3 */

    /* USER CODE BEGIN (2) */
    /* USER CODE END */
}

/** @fn void Pwm_SetCLKDIV(PWM_Obj *etpwm, uint32 clkdiv)
 *   @brief Sets prescale value of timebase counter
 *
 *   @param etpwm     The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param clkdiv    These bits determine the time-base clock prescale value
 *
 *   This function sets the Time-base Clock Prescale Bits of timebase counter
 */
void Pwm_SetCLKDIV(PWM_Obj *etpwm, uint32 clkdiv)
{
    HW_SET_FIELD16(etpwm->TBCTL, PWM_TBCTL_CLKDIV, clkdiv);
}

/** @fn void Pwm_SetHSPCLKDIV(PWM_Obj *etpwm, uint32 clkdiv)
 *   @brief Sets prescale value of timebase counter
 *
 *   @param etpwm     The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param hsclkdiv  These bits determine the time-base clock prescale value
 *
 *   This function sets the High Speed Time-base Clock Prescale Bits of timebase counter
 */
void Pwm_SetHSPCLKDIV(PWM_Obj *etpwm, uint32 hspclkdiv)
{
    HW_SET_FIELD16(etpwm->TBCTL, PWM_TBCTL_HSPCLKDIV, hspclkdiv);
}

/** @fn void Pwm_SetTimebasePeriod(PWM_Obj *etpwm, uint16 period)
 *   @brief Sets period of timebase counter
 *
 *   @param etpwm     The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param period    16-bit Time-base period
 *
 *   This function sets period of timebase counter
 */
void Pwm_SetTimebasePeriod(PWM_Obj *etpwm, uint16 period)
{
    etpwm->TBPRD = period;
}

/** @fn uint16 Pwm_GetTimebasePeriod(PWM_Obj *etpwm, uint16 period)
 *   @brief Sets period of timebase counter
 *
 *   @param etpwm     The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param period    16-bit Time-base period
 *
 *   This function sets period of timebase counter
 */
uint16 Pwm_GetTimebasePeriod(const PWM_Obj *etpwm)
{
    return (etpwm->TBPRD);
}

/** @fn void PWM_SetCmpA(PWM_Obj *etpwm, uint16 value)
 *   @brief Set the Compare A value
 *
 *   @param etpwm     The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param value     16-bit Compare A value
 *
 *   This function sets the compare A value
 */
void PWM_SetCmpA(PWM_Obj *etpwm, uint16 value)
{
    etpwm->CMPA  = value;
    etpwm->rsvd3 = value;
}

/** @fn void PWM_EnableCmpAShadowMode(PWM_Obj *etpwm, PWM_ShadowMode_e shdwmode)
 *   @brief Enable shadow mode for Compare A register
 *
 *   @param etpwm     The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param shdwmode  Load From Shadow Select Mode
 *                     - ShadowMode_Shadow       : Load on CTR = Zero
 *                     - ShadowMode_Immediate     : Load on CTR = 1
 *
 *   This function enables shadow mode for Compare A register
 */
void PWM_EnableCmpAShadowMode(PWM_Obj *etpwm, PWM_ShadowMode_e shdwmode)
{
    etpwm->CMPCTL &= (uint16) ~(uint16)0x0013U;
    etpwm->CMPCTL |= (uint16)shdwmode;
}

void PWM_SetLoadModeCmpA(PWM_Obj *etpwm, const etpwmLoadMode_t loadMode)
{
    /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    etpwm->CMPCTL &= (uint16) ~(uint16)PWM_CMPCTL_LOADAMODE_BITS;

    etpwm->CMPCTL |= (uint16)loadMode;

    return;
}

void PWM_SetActionQualZeroPwmA(PWM_Obj *etpwm, const etpwmActionQual_t actionQual, uint16 pol)
{
    /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    etpwm->AQCTLA &= (uint16) ~(uint16)PWM_AQCTL_ZRO_BITS;

    etpwm->AQCTLA |= (uint16)actionQual;

    /* Force output once, thereby getting the correct initial state */
    etpwm->AQSFRC &= (uint16)0xFFFC;
    etpwm->AQSFRC |= pol;
    /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    etpwm->AQCSFRC &= (uint16) ~(uint16)PWM_AQCSFRC_CSFA_BITS;

    return;
}
void PWM_SetActionQualCntUpCmpAPwmA(PWM_Obj *etpwm, const etpwmActionQual_t actionQual)
{
    /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    etpwm->AQCTLA &= (uint16) ~(uint16)PWM_AQCTL_CAU_BITS;
    etpwm->AQCTLA |= ((uint16)actionQual << 4U);

    return;
}

void PWM_SetActionQualCntDownCmpAPwmA(PWM_Obj *etpwm, const etpwmActionQual_t actionQual)
{
    /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    etpwm->AQCTLA &= (uint16) ~(uint16)PWM_AQCTL_CAD_BITS;
    etpwm->AQCTLA |= ((uint16)actionQual << 6U);

    return;
}

void PWM_SetActionQualContSWForce_PwmA(PWM_Obj *etpwm, const ActionQualContSWForce_e actionQualContSWForce)
{
    /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    etpwm->AQCSFRC &= (uint16) ~(uint16)PWM_AQCSFRC_CSFA_BITS;

    etpwm->AQCSFRC |= (uint16)actionQualContSWForce;

    return;
}

#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
uint16 PWM_GetActionQualContSWForce_PwmA(const PWM_Obj *etpwm)
{
    return (etpwm->AQCSFRC);
}
#endif

/** @fn void PWM_EnableInterrupt(PWM_Obj *etpwm, etpwmEventSrc_t eventsource, etpwmEventPeriod_t
 * eventperiod)
 *   @brief Enable ePWM Interrupt
 *
 *   @param etpwm        The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param eventsource  EPWMx_INT Selection Options
 *                         - CTR_ZERO      : Event CTR = Zero
 *                         - CTR_PRD       : Event CTR = PRD
 *                         - CTR_ZERO_PRD  : Event CTR = Zero or CTR = PRD
 *                         - CTR_UP_CMPA   : Event CTR = CMPA when the timer is incrementing
 *                         - CTR_D0WM_CMPA : Event CTR = CMPA when the timer is decrementing
 *                         - CTR_UP_CMPB   : Event CTR = CMPB when the timer is incrementing
 *                         - CTR_D0WM_CMPB : Event CTR = CMPB when the timer is decrementing
 *   @param eventperiod  EPWMx_INT Period Select
 *                         - EventPeriod_FirstEvent  : Generate interrupt on the first event
 *                         - EventPeriod_SecondEvent : Generate interrupt on the second event
 *                         - EventPeriod_ThirdEvent  : Generate interrupt on the third event
 *
 *   This function enables EPWMx_INT generation
 */
void PWM_EnableInterrupt(PWM_Obj *etpwm, etpwmEventSrc_t eventsource, etpwmEventPeriod_t eventperiod)
{
    etpwm->ETSEL &= 0xFFF0U;
    etpwm->ETSEL |= (uint16)((uint16)1U << 3U) | (uint16)((uint16)eventsource << 0U);

    etpwm->ETPS &= 0xFFF0U;
    etpwm->ETPS |= (uint16)((uint16)eventperiod << 0U);
}

void PWM_SetIntMode(PWM_Obj *etpwm, const etpwmEventSrc_t intMode)
{
    /*LDRA_INSPECTED 50 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    /*LDRA_INSPECTED 93 S : MISRAC_2012_R.10.1 Reason : Driver object typecast*/
    etpwm->ETSEL &= (uint16) ~(uint16)PWM_ETSEL_INTSEL_BITS;

    etpwm->ETSEL |= (uint16)intMode;

    return;
}

/** @fn void PWM_DisableInt(PWM_Handle *etpwm)
 *   @brief Disable ePWM Interrupt
 *
 *   @param etpwm        The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *
 *   This function disables EPWMx_INT generation
 */
void PWM_DisableInt(PWM_Obj *etpwm)
{
    etpwm->ETSEL &= (uint16)0xFFF0U;
}

/** @fn void PWM_ClearEventFlag(PWM_Obj *etpwm, etpwmEvent_t events)
 *   @brief Clear event status flag
 *
 *   @param etpwm The pulse width modulation (ETPWM) object handle (etpwmREG1..3)
 *   @param events status flag (flags can be ORed)
 *                  - Event_Interrupt
 *                  - Event_SOCA
 *                  - Event_SOCB
 *
 *   This function clears the event status flags
 */
void PWM_ClearEventFlag(PWM_Obj *etpwm, etpwmEvent_t events)
{
    /*LDRA_INSPECTED 433 S : MISRAC_2012_R.10.1 Reason : LDRA tool issue*/
    etpwm->ETCLR = (uint16)events;
}

#if (STD_ON == PWM_SAFETI_API)

/** @fn void etpwm1GetConfigValue(etpwm_config_reg_t *config_reg, config_value_type_t type)
 *   @brief Get the initial or current values of the configuration registers
 *
 *   @param[in] *RegRbPtr: pointer to the struct to which the initial or current
 *                           value of the configuration registers need to be stored
 *   @param[in] type:    whether initial or current value of the configuration registers need to be
 * stored
 *                       - InitialValue: initial value of the configuration registers will be stored
 *                                       in the struct pointed by RegRbPtr
 *                       - CurrentValue: initial value of the configuration registers will be stored
 *                                       in the struct pointed by RegRbPtr
 *   @param[in] Channel : Channel number
 *
 *   This function will copy the initial or current value (depending on the parameter 'type')
 *   of the configuration registers to the struct pointed by RegRbPtr
 *
 */
void Pwm_HwRegisterReadback(Pwm_RegisterReadbackType *RegRbPtr, Pwm_ChannelType Channel)
{
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.1 */
    /*LDRA_INSPECTED 94 S : MISRAC_2012_R.11.1 Reason : Casting done for getting driver object*/
    /*LDRA_INSPECTED 554 S : MISRAC_2012_R.11.2 Reason : Casting done for getting driver object*/
    PWM_Obj *etpwmREG1     = (PWM_Obj *)GetPwmChannelObj(Channel);
    RegRbPtr->CONFIG_TBCTL = etpwmREG1->TBCTL;
    RegRbPtr->CONFIG_TBPHS = etpwmREG1->TBPHS;
}
#endif

void Pwm_EnIntr(uint8 channel)
{
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    PWM_EnableInterrupt((PWM_Obj *)PwmHandles[channel], NO_EVENT, EventPeriod_FirstEvent);
}

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
void PWM_NotifySetIntMode(Pwm_ChannelType Channel, Pwm_EdgeNotificationType Notification)
{
    Pwm_OutputStateType polarity;
    /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
     * "Reason - Pointer cannot NULL . NULL_PTR Check done in init " */
    polarity = PwmConfigPtr->ChannelConfig_at[Channel].settings.Polarity_t;
    switch (Notification)
    {
        case PWM_FALLING_EDGE:
            if (polarity == PWM_HIGH)
            {
                /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here
                 */
                PWM_SetIntMode((PWM_Obj *)PwmHandles[Channel], CTR_UP_CMPA);
            }
            else
            {
                /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here
                 */
                PWM_SetIntMode((PWM_Obj *)PwmHandles[Channel], CTR_ZERO);
            }
            break;
        case PWM_RISING_EDGE:
            if (polarity == PWM_HIGH)
            {
                /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here
                 */
                PWM_SetIntMode((PWM_Obj *)PwmHandles[Channel], CTR_ZERO);
            }
            else
            {
                /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here
                 */
                PWM_SetIntMode((PWM_Obj *)PwmHandles[Channel], CTR_UP_CMPA);
            }
            break;
        default:
            /*Do nothing*/
            break;
    }
}
#endif

FUNC(void, PWM_CODE) Pwm_SystemInit(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) CfgPtr)
{
    uint32 pwmClockHz = 0;
    PwmConfigPtr      = CfgPtr;
    pwmClockHz        = PwmConfigPtr->pwmClkHz;
    uint32 clkDiv     = 1U;
    uint32 hspclkDiv  = 1U;
    uint8  idx;
    uint32 hwPeriod    = 0;
    uint32 Dutycycle_t = 0;

    /*Requirements : SWS_Pwm_00007, SWS_Pwm_00062*/
    for (idx = 0; idx < PwmConfigPtr->NumberOfChannels_u8; idx++)
    {
        /*Requirements :SWS_Pwm_10009*/
        Pwm_ChannelType hwChannel = PwmConfigPtr->ChannelConfig_at[idx].channel;
        PwmHandles[hwChannel]     = Init_EPWM(hwChannel);

        /*Requirements : SWS_Pwm_10009, SWS_Pwm_20009, SWS_Pwm_30009*/
        channelConfigMap[hwChannel] = (uint32)idx; /*to use in interrupt handler/channel class*/

        /* TBCLK = SYSCLK / (hsPrescale x prescale) */
        if ((PwmConfigPtr->ChannelConfig_at[idx].hsPrescale) == (uint32)0U)
        {
            hspclkDiv = (uint32)1U;
        }
        else
        {
            hspclkDiv = ((uint32)2U * (PwmConfigPtr->ChannelConfig_at[idx].hsPrescale));
        }
        clkDiv     = (uint32)1U << (PwmConfigPtr->ChannelConfig_at[idx].prescale);
        pwmClockHz = pwmClockHz / ((uint32)hspclkDiv * (uint32)clkDiv);

        hwPeriod = pwmClockHz / PwmConfigPtr->ChannelConfig_at[idx].settings.frequency_t;
        /*LDRA_INSPECTED 332 S : MISRAC_2012_R.10.8 Reason :LDRA tool not able to analyse*/
        Dutycycle_t = (uint32)(((uint32)hwPeriod * PwmConfigPtr->ChannelConfig_at[idx].settings.Dutycycle_t) >> 15U);

        Pwm_SetCLKDIV((PWM_Obj *)PwmHandles[hwChannel], PwmConfigPtr->ChannelConfig_at[idx].prescale);

        Pwm_SetHSPCLKDIV((PWM_Obj *)PwmHandles[hwChannel], PwmConfigPtr->ChannelConfig_at[idx].hsPrescale);

        Pwm_SetPrdCmpAcq(hwChannel, hwPeriod, Dutycycle_t, idx);

        uint16 configDuty = PwmConfigPtr->ChannelConfig_at[idx].settings.Dutycycle_t;
        /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
         * "Reason - Pointer cannot NULL . NULL_PTR Check done  " */
        Pwm_HandleDutyBoundry(configDuty, hwChannel, idx);

        /*
         * For updates at the end of period, leave default shadowing of CMPA on,
         * and write to the real register on period clock event.
         * For unbuffered updates, disable shadowing of the CMPA register.
         */
#if (PWM_DUTYCYCLE_UPDATED_ENDPERIOD == STD_ON)
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_EnableCmpAShadowMode((PWM_Obj *)PwmHandles[hwChannel], ShadowMode_Shadow);
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetLoadModeCmpA((PWM_Obj *)PwmHandles[hwChannel], LoadMode_CtrEqZero);
#else
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_EnableCmpAShadowMode((PWM_Obj *)PwmHandles[hwChannel], ShadowMode_Immediate);
#endif
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        /*Requirements : SWS_Pwm_00052 */
        Pwm_DrvStatus = PWM_STATUS_INIT;
#endif
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        {
            Pwm_DisableNotification(hwChannel);
        }
#endif
    }
}

void Pwm_HandleDutyBoundry(uint16 configDuty, Pwm_ChannelType hwChannel, uint8 idx)
{
    /* With duty cycle reached, we toggle, regardless of polarity */
    if (configDuty <= 0x4000U)
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualCntUpCmpAPwmA((PWM_Obj *)PwmHandles[hwChannel], ActionQual_Toggle);
    }
    else
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualCntDownCmpAPwmA((PWM_Obj *)PwmHandles[hwChannel], ActionQual_Toggle);
    }
    /* Special handling for 0% and 100% duty to prevent two conflicting events
     * from firing in the HW, so just set the output to constant high or low
     */
    if ((configDuty == 0U) || (configDuty == 0x8000U))
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualCntUpCmpAPwmA((PWM_Obj *)PwmHandles[hwChannel], ActionQual_Disabled);
        if (configDuty == 0U)
        {
            /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
            PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[hwChannel],
                                              ((PwmConfigPtr->ChannelConfig_at[idx].settings.Polarity_t) == PWM_HIGH)
                                                  ? ActionQualContSWForce_Clear
                                                  : ActionQualContSWForce_Set);
        }
        else
        {
            /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
            PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[hwChannel],
                                              ((PwmConfigPtr->ChannelConfig_at[idx].settings.Polarity_t) == PWM_HIGH)
                                                  ? ActionQualContSWForce_Set
                                                  : ActionQualContSWForce_Clear);
        }
    }
}

void Pwm_SetPrdCmpAcq(Pwm_ChannelType hwChannel, uint32 hwPeriod, uint32 Dutycycle_t, uint8 idx)
{
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    Pwm_SetTimebasePeriod((PWM_Obj *)PwmHandles[hwChannel], (uint16)(hwPeriod - 1U));
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    PWM_SetCmpA((PWM_Obj *)PwmHandles[hwChannel], (uint16)Dutycycle_t);

    if (PwmConfigPtr->ChannelConfig_at[idx].settings.Polarity_t == PWM_HIGH)
    {
        /* Up-down PWM counter implies that we set the output
         * to the configured polarity when the counter is at 0
         * Then we toggle the output when the duty cycle comparevalue is reached
         */
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualZeroPwmA((PWM_Obj *)PwmHandles[hwChannel], ActionQual_Set, (uint16)((uint16)2U << 1U));
    }
    else
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualZeroPwmA((PWM_Obj *)PwmHandles[hwChannel], ActionQual_Clear, (uint16)((uint16)1U << 1U));
    }
}

void Pwm_SetDutyCycle_Internal(Pwm_ChannelType Channel, uint16 DutyCycle)
{
    uint32 period;
    uint32 absoluteDuty;
    uint32 idx;

    idx = channelConfigMap[Channel];
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    period = (uint32)Pwm_GetTimebasePeriod((PWM_Obj *)PwmHandles[Channel]);
    /* Requirements : SWS_Pwm_00059*/
    absoluteDuty = ((uint32)(period + 1U) * DutyCycle) >> 15;
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    PWM_SetCmpA((PWM_Obj *)PwmHandles[Channel], (uint16)absoluteDuty);

    if (PwmConfigPtr->ChannelConfig_at[idx].settings.Polarity_t == PWM_HIGH)
    {
        /* Up-down PWM counter implies that we set the output
         * to the configured polarity when the counter is at 0
         * Then we toggle the output when the duty cycle compare value reached
         */
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualZeroPwmA((PWM_Obj *)PwmHandles[Channel], ActionQual_Set, (uint16)((uint16)2U << 1U));
    }
    else
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualZeroPwmA((PWM_Obj *)PwmHandles[Channel], ActionQual_Clear, (uint16)((uint16)1U << 1U));
    }
    /*Requirements : SWS_Pwm_00016*/
    /* With duty cycle reached, we toggle, regardless of polarity */
    if (DutyCycle <= 0x4000U)
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualCntUpCmpAPwmA((PWM_Obj *)PwmHandles[Channel], ActionQual_Toggle);
    }
    else
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualCntDownCmpAPwmA((PWM_Obj *)PwmHandles[Channel], ActionQual_Toggle);
    }
    /* Special handling for 0% and 100% duty to prevent two conflicting events
     * from firing in the HW, so just set the output to constant high or low
     */
    /*Requirements : SWS_Pwm_00014*/
    if ((DutyCycle == 0U) || (DutyCycle == 0x8000U))
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualCntUpCmpAPwmA((PWM_Obj *)PwmHandles[Channel], ActionQual_Disabled);
        if (DutyCycle == 0U)
        {
            /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
            PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[Channel],
                                              ((PwmConfigPtr->ChannelConfig_at[idx].settings.Polarity_t) == PWM_HIGH)
                                                  ? ActionQualContSWForce_Clear
                                                  : ActionQualContSWForce_Set);
        }
        else
        {
            /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
            PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[Channel],
                                              ((PwmConfigPtr->ChannelConfig_at[idx].settings.Polarity_t) == PWM_HIGH)
                                                  ? ActionQualContSWForce_Set
                                                  : ActionQualContSWForce_Clear);
        }
    }

    /* Requirements : SWS_Pwm_00017
     * This requirement is to update duty cycle at the end of the period. That is the
     * default behaviour of the hardware, and this setting is changed in Pwm_Init if
     * PwmDutycycleUpdatedEndperiod was turned off
     */

    /* Reactivate channel if output was forced to idle */
    /* Requirements : SWS_Pwm_20086 , SWS_Pwm_00018, SWS_Pwm_00020*/
    if ((channelForcedIdle[Channel]) == (boolean)(TRUE))
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[Channel], ActionQualContSWForce_Disabled);
        channelForcedIdle[Channel] = FALSE;
    }
}

#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
FUNC(Pwm_OutputStateType, PWM_CODE) Pwm_SystemGetOutputState(Pwm_ChannelType ChannelNumber)
{
    Pwm_OutputStateType Output_Level = PWM_LOW;

    if ((uint16)0x0U ==
        (PWM_GetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[ChannelNumber]) & (uint16)ActionQualContSWForce_Set))
    {
        Output_Level = PWM_LOW;
    }
    else
    {
        Output_Level = PWM_HIGH;
    }

    /* return the Value. */
    return Output_Level;
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
/**********************************************************************************************************************
 *   Function Name : Pwm_ChannelNotificationISR
 *********************************************************************************************************************/
/*! \Description: Interrupt Subroutine for Notification
 *
 *  \context    Function is called from interrupt level
 *********************************************************************************************************************/
/* Reason : "Reason -  Pragma is required here for functions in ISR"*/
#if (defined CLANG) || (defined DIAB)
#else
#pragma CODE_STATE(Pwm_ChannelNotificationISR, 32)
#endif
#if (defined CLANG) || (defined DIAB)
FUNC(void, PWM_CODE)
Pwm_ChannelNotificationISR(Pwm_ChannelType Channel) __attribute__((target("arm")));
#endif
FUNC(void, PWM_CODE) Pwm_ChannelNotificationISR(Pwm_ChannelType Channel)
{
    /*Get the PWM channel handle*/
    /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
     * "Reason - Pointer cannot NULL . NULL_PTR Check done in init " */
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    PWM_Obj *pwm = (PWM_Obj *)PwmHandles[Channel];

    /* Requirements : SWS_Pwm_00105, SWS_Pwm_00025*/
    /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
    "Reason - Pointer already checked before registering the handler */
    PwmConfigPtr->ChannelConfig_at[Channel].NotificationHandlers_at();

    /*Requirements : SWS_Pwm_00026 */
    PWM_ClearEventFlag(pwm, Event_Interrupt);
}
#endif /*(STD_ON == PWM_NOTIFICATION_SUPPORTED)*/

#if (STD_ON == PWM_DEINIT_API)
FUNC(void, PWM_CODE) Pwm_SystemDeInit(void)
{
    uint32              LoopCnt_u8;
    Pwm_OutputStateType idleState;
    for (LoopCnt_u8 = 0; LoopCnt_u8 < PwmConfigPtr->NumberOfChannels_u8; LoopCnt_u8++)
    {
        Pwm_ChannelType hwChannel = PwmConfigPtr->ChannelConfig_at[LoopCnt_u8].channel;
/*Requirements : SWS_Pwm_00012*/
#if PWM_NOTIFICATION_SUPPORTED == STD_ON
        Pwm_DisableNotification(hwChannel);
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_ClearEventFlag((PWM_Obj *)PwmHandles[hwChannel], Event_Interrupt);
#endif
        /* Requirements : SWS_Pwm_00021, */
        idleState = PwmConfigPtr->ChannelConfig_at[hwChannel].settings.IdleState_t;
        if (idleState == PWM_HIGH)
        {
            /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
            PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[hwChannel], ActionQualContSWForce_Set);
        }
        else
        {
            /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
            PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[hwChannel], ActionQualContSWForce_Clear);
        }

        channelForcedIdle[hwChannel] = TRUE;
    }
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*Requirements : SWS_Pwm_00010*/
    Pwm_DrvStatus = PWM_STATUS_UNINIT;
#endif
}
#endif

#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
FUNC(void, PWM_CODE) Pwm_SystemSetOutputToIdle(Pwm_ChannelType ChannelNumber)
{
    Pwm_OutputStateType idleState;
    idleState = PwmConfigPtr->ChannelConfig_at[ChannelNumber].settings.IdleState_t;
    if (idleState == PWM_HIGH)
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[ChannelNumber], ActionQualContSWForce_Set);
    }
    else
    {
        /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
        PWM_SetActionQualContSWForce_PwmA((PWM_Obj *)PwmHandles[ChannelNumber], ActionQualContSWForce_Clear);
    }

    channelForcedIdle[ChannelNumber] = TRUE;
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(void, PWM_CODE)
Pwm_SystemEnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification)
{
    /*Requirements : SWS_Pwm_00081, */
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    PWM_ClearEventFlag((PWM_Obj *)PwmHandles[ChannelNumber], Event_Interrupt);
    /*Requirements : SWS_Pwm_00024*/
    Pwm_EnIntr((uint8)ChannelNumber);

    /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
     * "Reason - Pointer cannot NULL . NULL_PTR Check done in init " */
    PWM_NotifySetIntMode(ChannelNumber, Notification);
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(void, PWM_CODE) Pwm_SystemDisableNotification(Pwm_ChannelType ChannelNumber)
{
    PWM_Handle pwmHnd = (PWM_Handle)NULL_PTR;
    /*Requirements : SWS_Pwm_00023*/
    pwmHnd = GetPwmChannelObj(ChannelNumber);
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    /*LDRA_INSPECTED 45 D : MISRAC_2012_D.4.1 "Reason - Pointer check is already done */
    PWM_DisableInt((PWM_Obj *)pwmHnd);
}
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
FUNC(void, PWM_CODE)
Pwm_SystemSetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle)
{
    /*Requirements :SWS_Pwm_00076, SWS_Pwm_00041,  */
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4 "Reason - Pointer typecast required here */
    Pwm_SetTimebasePeriod((PWM_Obj *)PwmHandles[ChannelNumber], (uint16)(Period - 1U));

    Pwm_EnIntr((uint8)ChannelNumber);

    /* @req SWS_Pwm_00150 */
    if (Period == 0U)
    {
        /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
         * "Reason - Pointer cannot NULL . NULL_PTR Check done in init " */
        Pwm_SetDutyCycle_Internal(ChannelNumber, 0);
    }
    else
    {
        /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
         * "Reason - Pointer cannot NULL . NULL_PTR Check done in init " */
        Pwm_SetDutyCycle_Internal(ChannelNumber, DutyCycle);
    }
}
#endif

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
FUNC(void, PWM_CODE)
Pwm_SystemSetDutyCycle_Internal(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    /*Requirements : SWS_Pwm_00013*/
    /*LDRA_INSPECTED 128 D : MISRAC_2012_D.4.1
     * "Reason - Pointer cannot NULL . NULL_PTR Check done at init " */
    Pwm_SetDutyCycle_Internal(ChannelNumber, DutyCycle);
}
#endif

#if (STD_ON == PWM_SET_DUTY_CYCLE_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_SetDutyCycle_Deterror(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    Std_ReturnType returnval = E_OK;

#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* check if the pwm driver has been initialized. if it is not, report
         * error PWM_E_UNINIT and return immediately.
         */
        (void)Pwm_Errorhook(PWM_SID_SET_DUTY_CYCLE, PWM_E_UNINIT);
        returnval = E_NOT_OK;
    }
    else if (PwmConfigPtr->NumberOfChannels_u8 <= (uint8)ChannelNumber)
    {
        /* check if channel number is valid. if it is not, report error
         * PWM_E_PARAM_CHANNEL and return immediately
         */
        (void)Pwm_Errorhook(PWM_SID_SET_DUTY_CYCLE, PWM_E_PARAM_CHANNEL);
        returnval = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }
#endif /* ( STD_ON == PWM_DEV_ERROR_DETECT ) */
    return returnval;
}
#endif

#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_GetOutputstate_Deterror(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;
    /* check driver state */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* driver has not been initialized --> report an error
         */
        (void)Pwm_Errorhook(PWM_SID_GET_OUTPUT_STATE, PWM_E_UNINIT);
        returnval = E_NOT_OK;
    }
    else if (PwmConfigPtr->NumberOfChannels_u8 <= (uint8)ChannelNumber)
    {
        /* channel number is not valid --> report an error
         */
        (void)Pwm_Errorhook(PWM_SID_GET_OUTPUT_STATE, PWM_E_PARAM_CHANNEL);
        returnval = E_NOT_OK;
    } /* if ( Pwm_HWChannelNumber_u8 <= ChannelNumber ) */
    else
    {
        /* do nothing */
    }
#endif /* #if ( STD_ON == PWM_DEV_ERROR_DETECT ) */
    return returnval;
}
#endif

#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_SetOutputToIdle_Deterror(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* check if the pwm driver has been initialized. if it is not, report
         * error PWM_E_UNINIT and return immediately.
         */
        (void)Pwm_Errorhook(PWM_SID_SET_OUTPUT_TO_IDLE, PWM_E_UNINIT);
        returnval = E_NOT_OK;
    }
    else if (PwmConfigPtr->NumberOfChannels_u8 <= (uint8)ChannelNumber)
    {
        /* check if channel number is valid. if it is not, report error
         * PWM_E_PARAM_CHANNEL and return immediately
         */
        (void)Pwm_Errorhook(PWM_SID_SET_OUTPUT_TO_IDLE, PWM_E_PARAM_CHANNEL);
        returnval = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }
#endif /* ( STD_ON == PWM_DEV_ERROR_DETECT ) */
    return returnval;
}
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(Std_ReturnType, PWM_CODE) Pwm_EnableNotify_Deterror(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* check if the pwm driver has been initialized. if it is not, report
         * error PWM_E_UNINIT and return immediately.
         */
        (void)Pwm_Errorhook(PWM_SID_ENABLE_NOTIFICATION, PWM_E_UNINIT);
        returnval = E_NOT_OK;
    }
    else if (PwmConfigPtr->NumberOfChannels_u8 <= (uint8)ChannelNumber)
    {
        (void)Pwm_Errorhook(PWM_SID_ENABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL);
        returnval = E_NOT_OK;
    }
    else if (PwmConfigPtr->ChannelConfig_at[ChannelNumber].NotificationHandlers_at == NULL_PTR)
    {
        (void)Pwm_Errorhook(PWM_SID_ENABLE_NOTIFICATION, PWM_E_NOTIFY_NULL);
        returnval = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }
#endif /* #if (STD_ON == PWM_DEV_ERROR_DETECT)*/
    return returnval;
}

FUNC(Std_ReturnType, PWM_CODE) Pwm_DisableNotify_Deterror(Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        (void)Pwm_Errorhook(PWM_SID_DISABLE_NOTIFICATION, PWM_E_UNINIT);
        returnval = E_NOT_OK;
    }
    else if (PwmConfigPtr->NumberOfChannels_u8 <= (uint8)ChannelNumber)
    {
        (void)Pwm_Errorhook(PWM_SID_DISABLE_NOTIFICATION, PWM_E_PARAM_CHANNEL);
        returnval = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }
#endif /* ( STD_ON == PWM_DEV_ERROR_DETECT ) */
    return returnval;
}
#endif

#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_SetPeriodAndDuty_Deterror(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    Std_ReturnType returnval = E_OK;
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    uint32 idx = channelConfigMap[ChannelNumber];
#endif

    /* ################### Begin dev error checks ######################### */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* check if the pwm driver has been initialized. if it is not, report
         * error PWM_E_UNINIT and return immediately.
         */
        (void)Pwm_Errorhook(PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_UNINIT);
        returnval = E_NOT_OK;
    }
    /* Requirements : SWS_Pwm_00047*/
    if ((returnval == E_OK) && (PwmConfigPtr->NumberOfChannels_u8 <= (uint8)ChannelNumber))
    {
        /* check if channel number is valid. if it is not, report error
         * PWM_E_PARAM_CHANNEL and return immediately
         */
        (void)Pwm_Errorhook(PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_PARAM_CHANNEL);
        returnval = E_NOT_OK;
    }
    if ((returnval == E_OK) && (PwmConfigPtr->ChannelConfig_at[idx].settings.ChannelClass_t != PWM_VARIABLE_PERIOD))
    {
        /* Check if this channel is from class "Variable Period", if it is fixed,
         report error PWM_E_PERIOD_UNCHANGEABLE */
        /*Requirements : SWS_PWM_0041, SWS_Pwm_00045*/
        (void)Pwm_Errorhook(PWM_SID_SET_PERIOD_AND_DUTY, PWM_E_PERIOD_UNCHANGEABLE);
        returnval = E_NOT_OK;
    }
#endif
    return returnval;
}
#endif

#if (STD_ON == PWM_SAFETI_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_HwRegReadback_Deterror(Pwm_ChannelType ChannelNumber,
                           P2VAR(Pwm_RegisterReadbackType, AUTOMATIC, PWM_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = E_OK;
    if (ChannelNumber >= (uint32)PWM_NUMBER_OF_CHANNELS)
    {
/*Invalid channel */
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_Errorhook(PWM_SID_REGISTER_READBACK, PWM_E_PARAM_CHANNEL);
#endif
        retVal = E_NOT_OK;
    }
    else if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_Errorhook(PWM_SID_REGISTER_READBACK, PWM_E_UNINIT);
#endif
        retVal = E_NOT_OK;
    }
    else if (NULL_PTR == RegRbPtr)
    {
#if (STD_ON == PWM_DEV_ERROR_DETECT)
        (void)Pwm_Errorhook(PWM_SID_REGISTER_READBACK, PWM_E_PARAM_POINTER);
#endif
        retVal = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }
    return (retVal);
}
#endif

FUNC(Std_ReturnType, PWM_CODE)
Pwm_Init_Deterror(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) ConfigPtr)
{
    Std_ReturnType retval = E_OK;
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    const Pwm_ConfigType *Pwmconfig = ConfigPtr;
    if (NULL_PTR == Pwmconfig)
    {
        /*Requirements : SWS_Pwm_00046, SWS_Pwm_10120, SWS_Pwm_20120*/
        (void)Pwm_Errorhook(PWM_SID_INIT, PWM_E_PARAM_CONFIG);
        retval = E_NOT_OK;
    }
    else if (PWM_STATUS_INIT == Pwm_DrvStatus)
    {
        /*Requirements : SWS_Pwm_00118*/
        (void)Pwm_Errorhook(PWM_SID_INIT, PWM_E_ALREADY_INITIALIZED);
        retval = E_NOT_OK;
    }
    else
    {
        /* do nothing */
    }
#endif /* ( STD_ON == PWM_DEV_ERROR_DETECT ) */
    return retval;
}

#if (STD_ON == PWM_DEINIT_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_Deinit_Deterror(void)
{
    Std_ReturnType retval = E_OK;
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (PWM_STATUS_INIT != Pwm_DrvStatus)
    {
        /* Requirements : SWS_Pwm_00117*/
        (void)Pwm_Errorhook(PWM_SID_DEINIT, PWM_E_UNINIT);
        retval = E_NOT_OK;
    }
#endif /* ( STD_ON == PWM_DEV_ERROR_DETECT ) */
    return retval;
}
#endif

#if (STD_ON == PWM_VERSION_INFO_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_GetVersionInfo_Deterror(P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA) VersionInfoPtr)
{
    Std_ReturnType retval = E_OK;
#if (STD_ON == PWM_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        /* Call Errorhook with 'wrong parameter'. */
        (void)Pwm_Errorhook(PWM_SID_GET_VERSION_INFO, PWM_E_PARAM_POINTER);
        retval = E_NOT_OK;
    }
#endif
    return retval;
}
#endif

/* Memory mapping, done via MemMap.h: Code */
/*LDRA_INSPECTED 580 S : MISRAC_2012_R.20.4
 * "Reason - macro is undefined in other file,but LDRA is not able to analyse
 *this " */
#define PWM_STOP_SEC_CODE
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections. " */
#include "Pwm_MemMap.h"
