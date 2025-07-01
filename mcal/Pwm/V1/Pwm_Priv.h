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
 *  \file     Pwm_priv.h
 *
 ** @brief    This component provides services for initialization and control of the microcontroller
 *internal PWM unit (pulse width modulation). The PWM module generates pulses with variable pulse
 *width. It allows the selection of the duty cycle and the signal period time.
 *
 */

#ifndef PWM_PRIV_H_
#define PWM_PRIV_H_

#include "sys_common.h"

#include "Pwm.h"
#include "hw_epwm.h"
#include "soc.h"

#include "hw_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN (0) */
/* USER CODE END */
#define COUNT_UP   (1U << 13U)
#define COUNT_DOWN 0U

/* @brief Defines the location of the ZRO bits in the AQCTL register */
#define PWM_AQCTL_ZRO_BITS (uint16)((uint16)3U << 0U)

/* @brief Defines the location of the PRD bits in the AQCTL register */
#define PWM_AQCTL_PRD_BITS (3 << 2)

/* @brief Defines the location of the CAU bits in the AQCTL register */
#define PWM_AQCTL_CAU_BITS (uint16)((uint16)3U << 4U)

/* @brief Defines the location of the CAD bits in the AQCTL register */
#define PWM_AQCTL_CAD_BITS (uint16)((uint16)3U << 6U)

/* @brief Defines the location of the CBU bits in the AQCTL register */
#define PWM_AQCTL_CBU_BITS (3 << 8)

/* @brief Defines the location of the CBD bits in the AQCTL register */
#define PWM_AQCTL_CBD_BITS (3 << 10)

/* @brief Defines the location of the CSFA bits in the AQCSFRC register */
#define PWM_AQCSFRC_CSFA_BITS (uint16)((uint16)3U << 0U)

/* @brief Defines the location of the CSFB bits in the AQCSFRC register */

#define PWM_AQCSFRC_CSFB_BITS (3 << 2)

/* @brief Defines the location of the LOADAMODE bits in the CMPCTL register */

#define PWM_CMPCTL_LOADAMODE_BITS (uint16)((uint16)3U << 0U)

/* @brief Defines the location of the LOADBMODE bits in the CMPCTL register */

#define PWM_CMPCTL_LOADBMODE_BITS (3 << 2)

/* @brief Defines the location of the SHDWAMODE bits in the CMPCTL register */

#define PWM_CMPCTL_SHDWAMODE_BITS (1 << 4)

/* @brief Defines the location of the SHDWBMODE bits in the CMPCTL register */

#define PWM_CMPCTL_SHDWBMODE_BITS (1 << 6)

/* @brief Defines the location of the SHDWAFULL bits in the CMPCTL register */

#define PWM_CMPCTL_SHDWAFULL_BITS (1 << 8)

/* @brief Defines the location of the SHDWBFULL bits in the CMPCTL register */

#define PWM_CMPCTL_SHDWBFULL_BITS (1 << 9)

/* @brief Defines the location of the OUTMODE bits in the DBCTL register */
#define PWM_DBCTL_OUTMODE_BITS (3 << 0)

/* @brief Defines the location of the POLSEL bits in the DBCTL register */
#define PWM_DBCTL_POLSEL_BITS (3 << 2)

/* @brief Defines the location of the INMODE bits in the DBCTL register */
#define PWM_DBCTL_INMODE_BITS (3 << 4)

/* @brief Defines the location of the HALFCYCLE bits in the DBCTL register */
#define PWM_DBCTL_HALFCYCLE_BITS (1 << 15)

/* @brief Defines the location of the ETCR bits in the ETCLR register */
#define PWM_ETCLR_INT_BITS (1 << 0)

/* @brief Defines the location of the SOCA bits in the ETCLR register */
#define PWM_ETCLR_SOCA_BITS (1 << 2)

/* @brief Defines the location of the SOCB bits in the ETCLR register */
#define PWM_ETCLR_SOCB_BITS (1 << 3)

/* @brief Defines the location of the INTPRD bits in the ETPS register */
#define PWM_ETPS_INTPRD_BITS (3 << 0)

/* @brief Defines the location of the INTCNT bits in the ETPS register */
#define PWM_ETPS_INTCNT_BITS (3 << 2)

/* @brief Defines the location of the SOCAPRD bits in the ETPS register */
#define PWM_ETPS_SOCAPRD_BITS (3 << 8)

/* @brief Defines the location of the SOCACNT bits in the ETPS register */
#define PWM_ETPS_SOCACNT_BITS (3 << 10)

/* @brief Defines the location of the SOCBPRD bits in the ETPS register */
#define PWM_ETPS_SOCBPRD_BITS (3 << 12)

/* @brief Defines the location of the SOCBCNT bits in the ETPS register */
#define PWM_ETPS_SOCBCNT_BITS (3 << 14)

/* @brief Defines the location of the INTSEL bits in the ETSEL register */
#define PWM_ETSEL_INTSEL_BITS (uint16)((uint16)7U << 0U)

/* @brief Defines the location of the INTEN bits in the ETSEL register */
#define PWM_ETSEL_INTEN_BITS (1 << 3)

/* @brief Defines the location of the SOCASEL bits in the ETSEL register */
#define PWM_ETSEL_SOCASEL_BITS (7 << 8)

/* @brief Defines the location of the SOCAEN bits in the ETSEL register */
#define PWM_ETSEL_SOCAEN_BITS (1 << 11)

/* @brief Defines the location of the SOCBSEL bits in the ETSEL register */
#define PWM_ETSEL_SOCBSEL_BITS (7 << 12)

/* @brief Defines the location of the SOCBEN bits in the ETSEL register */
#define PWM_ETSEL_SOCBEN_BITS (1 << 15)

/* @brief Defines the location of the CHPEN bits in the PCCTL register */
#define PWM_PCCTL_CHPEN_BITS (1 << 0)

/* @brief Defines the location of the OSHTWTH bits in the PCCTL register */
#define PWM_PCCTL_OSHTWTH_BITS (15 << 1)

/* @brief Defines the location of the CHPFREQ bits in the PCCTL register */
#define PWM_PCCTL_CHPFREQ_BITS (7 << 5)

/* @brief Defines the location of the CHPDUTY bits in the PCCTL register */
#define PWM_PCCTL_CHPDUTY_BITS (7 << 8)

/* @brief Defines the location of the CTRMODE bits in the TBCTL register */
#define PWM_TBCTL_CTRMODE_BITS (3 << 0)

/* @brief Defines the location of the PHSEN bits in the TBCTL register */
#define PWM_TBCTL_PHSEN_BITS (1 << 2)

/* @brief Defines the location of the PRDLD bits in the TBCTL register */
#define PWM_TBCTL_PRDLD_BITS (1 << 3)

/* @brief Defines the location of the SYNCOSEL bits in the TBCTL register */
#define PWM_TBCTL_SYNCOSEL_BITS (3 << 4)

/* @brief Defines the location of the SWFSYNC bits in the TBCTL register */
#define PWM_TBCTL_SWFSYNC_BITS (1 << 6)

/* @brief Defines the location of the HSPCLKDIV bits in the TBCTL register */
#define PWM_TBCTL_HSPCLKDIV_BITS (7 << 7)

/* @brief Defines the location of the CLKDIV bits in the TBCTL register */
#define PWM_TBCTL_CLKDIV_BITS (7 << 10)

/* @brief Defines the location of the HSPCLKDIV bits in the TBCTL register */
#define PWM_TBCTL_HSPCLKDIV_SHIFT ((uint16)7U)
#define PWM_TBCTL_HSPCLKDIV_MASK  ((uint16)7U << (uint16)7U)

/* @brief Defines the location of the CLKDIV bits in the TBCTL register */
#define PWM_TBCTL_CLKDIV_SHIFT ((uint16)10U)
#define PWM_TBCTL_CLKDIV_MASK  ((uint16)7U << (uint16)10U)

/* @brief Defines the location of the PHSDIR bits in the TBCTL register */
#define PWM_TBCTL_PHSDIR_BITS (1 << 13)

/* @brief Defines the location of the FREESOFT bits in the TBCTL register */
#define PWM_TBCTL_FREESOFT_BITS (3 << 14)

/* @brief Defines the location of the INT bits in the TXCLR register */
#define PWM_TZCLR_INT_BITS (1 << 0)

/* @brief Defines the location of the CBC bits in the TXCLR register */
#define PWM_TZCLR_CBC_BITS (1 << 1)

/* @brief Defines the location of the OST bits in the TXCLR register */
#define PWM_TZCLR_OST_BITS (1 << 2)

/* @brief Defines the location of the DCAEVT1 bits in the TXCLR register */
#define PWM_TZCLR_DCAEVT1_BITS (1 << 3)

/* @brief Defines the location of the DCAEVT2 bits in the TXCLR register */
#define PWM_TZCLR_DCAEVT2_BITS (1 << 4)

/* @brief Defines the location of the DCBEVT1 bits in the TXCLR register */
#define PWM_TZCLR_DCBEVT1_BITS (1 << 5)

/* @brief Defines the location of the DCBEVT2 bits in the TXCLR register */
#define PWM_TZCLR_DCBEVT2_BITS (1 << 6)

/* @brief Defines the location of the TZA bits in the TZCTL register */
#define PWM_TZCTL_TZA_BITS (3 << 0)

/* @brief Defines the location of the  TZB bits in the TZCTL register */
#define PWM_TZCTL_TZB_BITS (3 << 2)

/* @brief Defines the location of the DCAEVT1 bits in the TZCTL register */
#define PWM_TZCTL_DCAEVT1_BITS (3 << 4)

/* @brief Defines the location of the DCAEVT2 bits in the TZCTL register */
#define PWM_TZCTL_DCAEVT2_BITS (3 << 6)

/* @brief Defines the location of the DCBEVT1 bits in the TZCTL register */
#define PWM_TZCTL_DCBEVT1_BITS (3 << 8)

/* @brief Defines the location of the DCBEVT2 bits in the TZCTL register */
#define PWM_TZCTL_DCBEVT2_BITS (3 << 10)

/* @brief Defines the location of the CBC bits in the TZFRC register */
#define PWM_TZFRC_CBC_BITS (1 << 1)

/* @brief Defines the location of the OST bits in the TZFRC register */
#define PWM_TZFRC_OST_BITS (1 << 2)

/* @brief Defines the location of the DCAEVT1 bits in the TZFRC register */
#define PWM_TZFRC_DCAEVT1_BITS (1 << 3)

/* @brief Defines the location of the DCAEVT2 bits in the TZFRC register */
#define PWM_TZFRC_DCAEVT2_BITS (1 << 4)

/* @brief Defines the location of the DCBEVT1 bits in the TZFRC register */
#define PWM_TZFRC_DCBEVT1_BITS (1 << 5)

/* @brief Defines the location of the DCBEVT2 bits in the TZFRC register */
#define PWM_TZFRC_DCBEVT2_BITS (1 << 6)

/** \brief The maximum value for Period  */
#define PWM_PERIOD_MAX (0x1ffffffU)

#define PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_D_20_1
 * "Reason - Memmap file can't have include guard. " */
#include "Pwm_MemMap.h"

/*LDRA_INSPECTED 25 D : MISRAC_2012_R.8.9 Reason : bitmap for channel confiured*/
static boolean channelForcedIdle[PWM_NUMBER_OF_CHANNELS];

#define PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_D_20_1
 * "Reason - Memmap file can't have include guard. " */
#include "Pwm_MemMap.h"

#define PWM_START_SEC_VAR_NO_INIT_32
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
#include "Pwm_MemMap.h"

static uint32 channelConfigMap[PWM_NUMBER_OF_CHANNELS];

#define PWM_STOP_SEC_VAR_NO_INIT_32
/*LDRA_INSPECTED 338 S : MISRAC_2012_D_20_1
 * "Reason - Memmap file */
#include "Pwm_MemMap.h"

#ifndef PWM_E_PARAM_CONFIG
#define PWM_E_PARAM_CONFIG (0x10U)
#endif

#ifndef PWM_E_NOTIFY_NULL
#define PWM_E_NOTIFY_NULL (0x22U)
#endif
#ifndef PWM_E_PARAM_PERIOD
#define PWM_E_PARAM_PERIOD (0x21U)
#endif

/* @brief Enumeration to define the pulse width modulation (PWM) shadow modes  */

typedef enum
{
    ShadowMode_Shadow = 0,
    ShadowMode_Immediate
} PWM_ShadowMode_e;

/* @brief Enumeration to select the source of Synchronization Output signal (EPWMxSYNCO)
 */
typedef enum
{
    SyncOut_EPWMxSYNCI = 0x00U, /** EPWMxSYNCI                */
    SyncOut_CtrEqZero  = 0x10U, /** CTR = zero                */
    SyncOut_CtrEqCmpB  = 0x20U, /** CTR = CMPB                */
    SyncOut_Disable    = 0x30U  /** Disable EPWMxSYNCO signal */
} etpwmSyncOut_t;

/* @brief Enumeration to define the pulse width modulation (ETPWM) counter modes
 */
typedef enum
{
    CounterMode_Up     = 0U, /** Up-count mode                  */
    Countermode_Down   = 1U, /** Down-count mode                */
    CounterMode_UpDown = 2U, /** Up-down-count mode             */
    CounterMode_Stop   = 3U  /** Stop - freeze counter operaton */
} etpwmCounterMode_t;

/* @brief Enumeration to define the pulse width modulation (ETPWM) load modes
 */
typedef enum
{
    LoadMode_CtrEqZero       = 0U, /** Load on CTR = Zero              */
    LoadMode_CtrEqPeriod     = 1U, /** Load on CTR = PRD               */
    LoadMode_CtrEqZeroPeriod = 2U, /** Load on CTR = Zero or CTR = PRD */
    LoadMode_Freeze          = 3U  /** Freeze (no loads possible)      */
} etpwmLoadMode_t;

/* @brief Enumeration to define the sources for EPWMx_INT, SOCA or SOCB
 */
typedef enum
{
    NO_EVENT      = 0U, /** Reserved                                             */
    DCAEVT1       = 0U, /** DCAEVT1.soc event                                    */
    DCBEVT1       = 0U, /** DCBEVT1.soc event                                    */
    CTR_ZERO      = 1U, /** Event CTR = Zero                                     */
    CTR_PRD       = 2U, /** Event CTR = PRD                                      */
    CTR_ZERO_PRD  = 3U, /** Event CTR = Zero or CTR = PRD                        */
    CTR_UP_CMPA   = 4U, /** Event CTR = CMPA when when the timer is incrementing */
    CTR_D0WM_CMPA = 5U, /** Event CTR = CMPA when when the timer is decrementing */
    CTR_UP_CMPB   = 6U, /** Event CTR = CMPB when when the timer is incrementing */
    CTR_D0WM_CMPB = 7U  /** Event CTR = CMPB when when the timer is decrementing */
} etpwmEventSrc_t;

/* @brief Enumeration to define the period of EPWMx_INT, SOCA or SOCB
 */
typedef enum
{
    EventPeriod_Disable     = 0U, /** Disable EPWMx_INT/SOCA/SOCB event counter              */
    EventPeriod_FirstEvent  = 1U, /** Generate EPWMx_INT/SOCA/SOCB pulse on the first event  */
    EventPeriod_SecondEvent = 2U, /** Generate EPWMx_INT/SOCA/SOCB pulse on the second event */
    EventPeriod_ThirdEvent  = 3U  /** Generate EPWMx_INT/SOCA/SOCB pulse on the third event  */
} etpwmEventPeriod_t;

/* @brief Enumeration to define the output events from ETPWMx
 */
typedef enum
{
    Event_Interrupt = 1U, /** EPWM Interrupt        */
    Event_SOCA      = 4U, /** Start Of Conversion A */
    Event_SOCB      = 8U  /** Start Of conversion B */
} etpwmEvent_t;

/* @brief Enumeration to define the pulse width modulation (ETPWM) action qualifiers
 *
 *   @note This enum should be use to populate the struct passed as the parameter
 *   to the APIs etpwmSetActionQualPwmA and etpwmSetActionQualPwmB
 */
typedef enum
{
    ActionQual_Disabled  = 0U,     /** Do nothing (action disabled)           */
    ActionQual_Clear     = 1U,     /** Clear: force EPTWMxA/ETPWMB output low */
    ActionQual_Set       = 2U,     /** Set: force ETPWMxA/ETPWMxB output high */
    ActionQual_Toggle    = 3U,     /** Toggle EPWMxA/ETPWMxB output           */
    ForceSize_ActionQual = 0xFFFFU /** Do not use (Makes sure that etpwmActionQual_t is at least 16 bits wide)  */
} etpwmActionQual_t;

typedef enum
{
    ActionQualContSWForce_Disabled = 0,
    ActionQualContSWForce_Clear,
    ActionQualContSWForce_Set
} ActionQualContSWForce_e;

/* @brief ETPWMx Action Qualifier configuration
 */
typedef struct
{
    etpwmActionQual_t CtrEqZero_Action;
    etpwmActionQual_t CtrEqPeriod_Action;
    etpwmActionQual_t CtrEqCmpAUp_Action;
    etpwmActionQual_t CtrEqCmpADown_Action;
    etpwmActionQual_t CtrEqCmpBUp_Action;
    etpwmActionQual_t CtrEqCmpBDown_Action;
} etpwmActionQualConfig_t;

/* @brief Defines the pulse width modulation (PWM) handle */
typedef struct PWM_Obj_t *PWM_Handle;

/*#define PWM_START_SEC_VAR_INIT_PTR
LDRA_INSPECTED 338 S : MISRAC_2012_D_20_1
* "Reason - Memmap file can't have include guard. "

LDRA_INSPECTED 338 S : MISRAC_2012_D_20_1
* "Reason - Memmap file can't have include guard. "
#include "Pwm_MemMap.h"*/
static PWM_Handle PwmHandles[PWM_NUMBER_OF_CHANNELS];
/**
 *  @defgroup ePWM ePWM
 *   @brief Enhanced Pulse Width Modulator.
 *
 *  The enhanced pulse width modulator (ePWM) peripheral is a key element in controlling many of the
 * power electronic systems found in both commercial and industrial equipments. The features
 * supported by the ePWM make it especially suitable for digital motor control.
 *
 *    Related Files
 *   - HL_reg_etpwm.h
 *   - HL_etpwm.h
 *   - HL_etpwm.c
 *  @addtogroup ePWM
 *  @{
 */
PWM_Handle        Init_EPWM(Pwm_ChannelType pwmAddrIdx);
void              Pwm_SetCLKDIV(PWM_Obj *etpwm, uint32 clkdiv);
void              Pwm_SetHSPCLKDIV(PWM_Obj *etpwm, uint32 hspclkdiv);
void              PWM_SetActionQualZeroPwmA(PWM_Obj *etpwm, const etpwmActionQual_t actionQual, uint16 pol);
void              PWM_SetActionQualCntUpCmpAPwmA(PWM_Obj *etpwm, const etpwmActionQual_t actionQual);
void              PWM_SetActionQualCntDownCmpAPwmA(PWM_Obj *etpwm, const etpwmActionQual_t actionQual);
void PWM_SetActionQualContSWForce_PwmA(PWM_Obj *etpwm, const ActionQualContSWForce_e actionQualContSWForce);
void PWM_EnableCmpAShadowMode(PWM_Obj *etpwm, PWM_ShadowMode_e shdwmode);
void PWM_SetLoadModeCmpA(PWM_Obj *etpwm, const etpwmLoadMode_t loadMode);
void PWM_EnableInterrupt(PWM_Obj *etpwm, etpwmEventSrc_t eventsource, etpwmEventPeriod_t eventperiod);
void PWM_SetCmpA(PWM_Obj *etpwm, uint16 value);

void Pwm_SetTimebasePeriod(PWM_Obj *etpwm, uint16 period);
#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
uint16 PWM_GetActionQualContSWForce_PwmA(const PWM_Obj *etpwm);
#endif
PWM_Handle GetPwmChannelObj(Pwm_ChannelType channel);
void       PWM_DisableInt(PWM_Obj *etpwm);
void       PWM_ClearEventFlag(PWM_Obj *etpwm, etpwmEvent_t events);
uint16     Pwm_GetTimebasePeriod(const PWM_Obj *etpwm);
void       PWM_SetIntMode(PWM_Obj *etpwm, const etpwmEventSrc_t intMode);

void InitPwm(PWM_Obj *pwmHnd);
void Pwm_EnIntr(uint8 channel);
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
void PWM_NotifySetIntMode(Pwm_ChannelType Channel, Pwm_EdgeNotificationType Notification);
#endif
#if (STD_ON == PWM_SAFETI_API)
void Pwm_HwRegisterReadback(Pwm_RegisterReadbackType *RegRbPtr, Pwm_ChannelType Channel);
#endif
void Pwm_SetPrdCmpAcq(Pwm_ChannelType hwChannel, uint32 hwPeriod, uint32 Dutycycle_t, uint8 idx);
void Pwm_HandleDutyBoundry(uint16 configDuty, Pwm_ChannelType hwChannel, uint8 idx);
void Pwm_SetDutyCycle_Internal(Pwm_ChannelType Channel, uint16 DutyCycle);
FUNC(void, PWM_CODE) Pwm_SystemInit(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) CfgPtr);
#if (STD_ON == PWM_DEINIT_API)
FUNC(void, PWM_CODE) Pwm_SystemDeInit(void);
#endif
#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
FUNC(void, PWM_CODE) Pwm_SystemSetOutputToIdle(Pwm_ChannelType ChannelNumber);
#endif
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(void, PWM_CODE)
Pwm_SystemEnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification);
#endif
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(void, PWM_CODE) Pwm_SystemDisableNotification(Pwm_ChannelType ChannelNumber);
#endif
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
FUNC(void, PWM_CODE)
Pwm_SystemSetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);
#endif
#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
FUNC(void, PWM_CODE)
Pwm_SystemSetDutyCycle_Internal(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
#endif
#if (STD_ON == PWM_SET_DUTY_CYCLE_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_SetDutyCycle_Deterror(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
#endif
#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_SetPeriodAndDuty_Deterror(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
#endif

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
FUNC(Std_ReturnType, PWM_CODE) Pwm_EnableNotify_Deterror(Pwm_ChannelType ChannelNumber);
FUNC(Std_ReturnType, PWM_CODE) Pwm_DisableNotify_Deterror(Pwm_ChannelType ChannelNumber);
#endif
#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_SetOutputToIdle_Deterror(Pwm_ChannelType ChannelNumber);
#endif
#if (STD_ON == PWM_SAFETI_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_HwRegReadback_Deterror(Pwm_ChannelType ChannelNumber,
                           P2VAR(Pwm_RegisterReadbackType, AUTOMATIC, PWM_APPL_DATA) RegRbPtr);
#endif

#if (STD_ON == PWM_DEINIT_API)
FUNC(Std_ReturnType, PWM_CODE) Pwm_Deinit_Deterror(void);
#endif
#if (STD_ON == PWM_VERSION_INFO_API)
FUNC(Std_ReturnType, PWM_CODE)
Pwm_GetVersionInfo_Deterror(P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA) VersionInfoPtr);
#endif
FUNC(Std_ReturnType, PWM_CODE)
Pwm_Init_Deterror(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_PBCFG) ConfigPtr);
#if (STD_ON == PWM_GET_OUTPUT_STATE_API)
FUNC(Pwm_OutputStateType, PWM_CODE) Pwm_SystemGetOutputState(Pwm_ChannelType ChannelNumber);
FUNC(Std_ReturnType, PWM_CODE) Pwm_GetOutputstate_Deterror(Pwm_ChannelType ChannelNumber);
#endif

/**@}*/
#ifdef __cplusplus
}
#endif /*extern "C" */

/* USER CODE BEGIN (1) */
/* USER CODE END */

#endif /* end of _ETPWM_H_ definition */
