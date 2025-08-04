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
 *  \file   Cdd_Pwm_Priv.c
 *
 *  \brief  This file contains the Internal APIs for CDD_PWM.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Pwm.h"
#include "Cdd_Pwm_Priv.h"
#include "hw_epwm.h"

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
static uint16 Cdd_Pwm_DutyValue(uint32 compareValue, uint32 period, EPWM_TimeBaseCountMode tbCtrMode);

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
static void Cdd_Pmw_FallingEdgeHighPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh);
static void Cdd_Pmw_FallingEdgeLowPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh);
static void Cdd_Pmw_RisingEdgeHighPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh);
static void Cdd_Pmw_RisingEdgeLowPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh);
static void Cdd_Pmw_BothEdges(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh);
#endif
static void Cdd_Pwm_CounterCmpA(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr);
static void Cdd_Pwm_CounterCmpB(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr);
static void Cdd_Pwm_CounterCmpC(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr);
static void Cdd_Pwm_CounterCmpD(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr);
static void Cdd_Pwm_otherPinAction(const Cdd_Pwm_ChObjType *pChannelConfig, uint32 baseAddr,
                                   EPWM_ActionQualifierSWOutput swTrigAction);
static void Cdd_Pwm_TogglePinAction(const Cdd_Pwm_ChObjType *pChannelConfig, uint32 baseAddr,
                                    EPWM_ActionQualifierSWOutput *swTrigAction);
static void Cdd_Pwm_PwmDCEvent(const Cdd_Pwm_tripZoneType *tripZoneParameter, uint32 epwmbaseadrr);
static void Cdd_Pwm_PwmOneShotTzEvent(const Cdd_Pwm_tripZoneType *tripZoneParameter, uint32 epwmbaseadrr);
static void Cdd_Pwm_PwmCBCTzEvent(const Cdd_Pwm_tripZoneType *tripZoneParameter, uint32 epwmbaseadrr);
static void Cdd_Pwm_PwmSyncOutPulseCntCmp(uint32 baseAddr, Cdd_Pwm_ChannelType ChannelNumber);
static void Cdd_Pwm_PwmHRConfig(uint32 ChannelNumber, Cdd_Pwm_OutputChType outputCh, uint32 base);
static void Cdd_Pwm_GenerateSignal(Cdd_Pwm_channelParametertype ChannelParameter, uint32 period,
                                   Cdd_Pwm_OutputChType outputCh, uint32 baseAddr, Cdd_Pwm_ChObjType *local_ChObj,
                                   const Cdd_Pwm_ChObjType *chObj);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define CDD_PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Pwm_MemMap.h"
/** \brief CDD_PWM driver object. */
extern VAR(Cdd_Pwm_ChObjType, CDD_PWM_VAR_NO_INIT) Cdd_Pwm_ChObj[CDD_PWM_MAX_NUM_CHANNELS];

#define CDD_PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Pwm_MemMap.h"

#define CDD_PWM_START_SEC_VAR_NO_INIT_32
#include "Cdd_Pwm_MemMap.h"

/** \brief CDD_PWM SFO Calibration status for each configured channel*/
extern VAR(uint32, CDD_PWM_VAR_NO_INIT) Cdd_Pwm_ChannelSfoStatus[CDD_PWM_MAX_NUM_CHANNELS];

#define CDD_PWM_STOP_SEC_VAR_NO_INIT_32
#include "Cdd_Pwm_MemMap.h"
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_PWM_START_SEC_CODE
#include "Cdd_Pwm_MemMap.h"
static uint16 Cdd_Pwm_DutyValue(uint32 compareValue, uint32 period, EPWM_TimeBaseCountMode tbCtrMode)
{
    float32 duty_cycle_percent;
    float64 duty_cycle_period;
    float64 dutyintvalue;
    uint16  duty_Value;

    /* Calculation for high resolution */
    duty_cycle_percent = ((float32)(((float32)(compareValue)) / (float32)CDD_PWM_CFG_DUTYCYCLE_MAX));
    duty_cycle_period  = (float64)((float64)duty_cycle_percent * ((float64)period + 1.0f));

    /* Provide Value based on COUNTER mode */
    if (tbCtrMode == EPWM_COUNTER_MODE_UP)
    {
        dutyintvalue = (duty_cycle_period);
    }
    else if (tbCtrMode == EPWM_COUNTER_MODE_DOWN)
    {
        dutyintvalue = (((float64)period + 1.0f) - ((float64)duty_cycle_period));
    }
    else
    {
        dutyintvalue = ((((float64)period + 1.0f) - ((float64)duty_cycle_period)) - ((float64)(0.5f)));
    }

    duty_Value = (uint16)dutyintvalue;

    return (duty_Value);
}

void Cdd_Pwm_resetChObj(Cdd_Pwm_ChObjType *chObj)
{
    /* Reset All the Struture elements. */
    chObj->idleState         = CDD_PWM_LOW;
    chObj->channelForcedIdle = FALSE;
    chObj->baseaddr          = 0;
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    chObj->notificationHandler     = (Cdd_Pwm_NotifyFuncType)NULL_PTR;
    chObj->channelNotifyActiveFlag = (uint32)FALSE;
#endif
    chObj->channelState          = CDD_PWM_STATUS_UNINIT;
    chObj->notificationTzHandler = (Cdd_Pwm_TzNotifyFuncType)NULL_PTR;
}

void Cdd_Pwm_copyConfig(Cdd_Pwm_ChObjType *chObj, const Cdd_Pwm_ChannelConfigType *chCfg)
{
    /* Init channelForcedIdle var default to FALSE */
    chObj->channelNotifyActiveFlag = (boolean)FALSE;
    chObj->channelState            = CDD_PWM_STATUS_INIT;
    chObj->baseaddr                = chCfg->baseaddr;
    chObj->outputCh                = chCfg->outputCh;
    chObj->polarity                = chCfg->polarity;
    chObj->channelID               = chCfg->channelID;
    chObj->channelHwID             = chCfg->channelHwID;
    chObj->idleState               = chCfg->polarity;
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
    chObj->notificationHandler = chCfg->notificationHandler;
#endif
    chObj->notificationTzHandler = chCfg->notificationTzHandler;

    /* Copying the Config stucture to Channel Object*/
    (void)memcpy(&chObj->channelTimerBase, chCfg->channelTimerBase, sizeof(Cdd_Pwm_timerBaseConfigType));
    (void)memcpy(&chObj->channelCounterCompare, chCfg->channelCounterCompare, sizeof(Cdd_Pwm_compareType));

#if (STD_ON == CDD_PWM_BASE_CLK_SYNC)
    (void)memcpy(&chObj->channelTimerBaseSync, chCfg->channelTimerBaseSync, sizeof(Cdd_Pwm_timerBaseSyncType));
#endif

#if (STD_ON == CDD_PWM_ACTION_QUALIFIER)
    (void)memcpy(&chObj->channelActionQualifier, chCfg->channelActionQualifier, sizeof(Cdd_Pwm_actionConfigType));
#endif

#if (STD_ON == CDD_PWM_EVENT_TRIGGER)
    (void)memcpy(&chObj->channelEventTrigger, chCfg->channelEventTrigger, sizeof(Cdd_Pwm_eventConfigType));
#endif

#if (STD_ON == CDD_PWM_ADC_ENABLE_DISABLE_API)
    (void)memcpy(&chObj->channelAdcEventTrigger, chCfg->channelAdcEventTrigger, sizeof(Cdd_Pwm_adcEventTriggerType));
#endif

#if (STD_ON == CDD_PWM_TRIP_ZONE)
    (void)memcpy(&chObj->channelTripZone, chCfg->channelTripZone, sizeof(Cdd_Pwm_tripZoneType));
#endif

#if (STD_ON == CDD_PWM_DIGITALCOMPARE)
    (void)memcpy(&chObj->channelDigitalCompare, chCfg->channelDigitalCompare, sizeof(Cdd_Pwm_DigitalCompareType));
#endif

#if (STD_ON == CDD_PWM_DEAD_BAND)
    (void)memcpy(&chObj->channelDeadBand, chCfg->channelDeadBand, sizeof(Cdd_Pwm_deadBandType));
#endif

#if (STD_ON == CDD_PWM_CHOPPER)
    (void)memcpy(&chObj->channelChopper, chCfg->channelChopper, sizeof(Cdd_Pwm_chopperType));
#endif

#if (STD_ON == CDD_PWM_HR_SET_HRPWM_API)
    (void)memcpy(&chObj->channelHrPwm, chCfg->channelHrPwm, sizeof(Cdd_Pwm_hrPwmType));
#endif
}

void Cdd_Epwm_DeInitialize(uint32 epwmbaseadrr)
{
    /* Time Base */
    EPWM_setEmulationMode(epwmbaseadrr, EPWM_EMULATION_FREE_RUN);
    EPWM_setClockPrescaler(epwmbaseadrr, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(epwmbaseadrr, 0);
    EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_TBPRD_TBPRDHR);
    EPWM_setPeriodLoadMode(epwmbaseadrr, EPWM_PERIOD_SHADOW_LOAD);
    EPWM_setTimeBaseCounter(epwmbaseadrr, 0);
    EPWM_setTimeBaseCounterMode(epwmbaseadrr, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setCountModeAfterSync(epwmbaseadrr, EPWM_COUNT_MODE_DOWN_AFTER_SYNC);
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

    /* Events */
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN);

    /* Trip Zone */
    EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZB_D, EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZB_U, EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZA_D, EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZA_U, EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D,
                                             EPWM_TZ_ADV_ACTION_HIGH_Z);
    EPWM_disableTripZoneAdvAction(epwmbaseadrr);
    EPWM_enableTripZoneSignals(epwmbaseadrr, 0);
    EPWM_enableTripZoneSignals(epwmbaseadrr, 0);
    EPWM_selectCycleByCycleTripZoneClearEvent(epwmbaseadrr, EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO);
    EPWM_enableTripZoneInterrupt(epwmbaseadrr, 0);

    /* Deadband */
    EPWM_disableDeadBandControlShadowLoadMode(epwmbaseadrr);
    EPWM_setDeadBandControlShadowLoadMode(epwmbaseadrr, EPWM_DB_LOAD_ON_CNTR_ZERO);
    EPWM_setRisingEdgeDeadBandDelayInput(epwmbaseadrr, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(epwmbaseadrr, EPWM_DB_INPUT_EPWMA);
    EPWM_setDeadBandDelayPolarity(epwmbaseadrr, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(epwmbaseadrr, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayMode(epwmbaseadrr, EPWM_DB_RED, FALSE);
    EPWM_setDeadBandDelayMode(epwmbaseadrr, EPWM_DB_FED, FALSE);
    EPWM_setDeadBandOutputSwapMode(epwmbaseadrr, EPWM_DB_OUTPUT_A, FALSE);
    EPWM_setDeadBandOutputSwapMode(epwmbaseadrr, EPWM_DB_OUTPUT_B, FALSE);

    EPWM_disableRisingEdgeDelayCountShadowLoadMode(epwmbaseadrr);
    EPWM_setRisingEdgeDelayCountShadowLoadMode(epwmbaseadrr, EPWM_RED_LOAD_ON_CNTR_ZERO);
    EPWM_setRisingEdgeDelayCount(epwmbaseadrr, 0);

    EPWM_disableFallingEdgeDelayCountShadowLoadMode(epwmbaseadrr);
    EPWM_setFallingEdgeDelayCountShadowLoadMode(epwmbaseadrr, EPWM_FED_LOAD_ON_CNTR_ZERO);
    EPWM_setFallingEdgeDelayCount(epwmbaseadrr, 0);
    EPWM_setDeadBandCounterClock(epwmbaseadrr, EPWM_DB_COUNTER_CLOCK_FULL_CYCLE);

    /* Chopper */
    EPWM_disableChopper(epwmbaseadrr);
    EPWM_setChopperDutyCycle(epwmbaseadrr, 0);
    EPWM_setChopperFreq(epwmbaseadrr, 0);
    EPWM_setChopperFirstPulseWidth(epwmbaseadrr, 0);

    /* Event Trigger */
    EPWM_disableInterrupt(epwmbaseadrr);
    EPWM_setInterruptSource(epwmbaseadrr, EPWM_INT_TBCTR_ZERO, EPWM_INT_TBCTR_ZERO);
    EPWM_setInterruptEventCount(epwmbaseadrr, 0);
    EPWM_disableInterruptEventCountInit(epwmbaseadrr);
    EPWM_setInterruptEventCountInitValue(epwmbaseadrr, 0);

    EPWM_disableADCTrigger(epwmbaseadrr, EPWM_SOC_A);
    EPWM_setADCTriggerSource(epwmbaseadrr, EPWM_SOC_A, EPWM_SOC_DCxEVT1, EPWM_SOC_DCxEVT1);
    EPWM_setADCTriggerEventPrescale(epwmbaseadrr, EPWM_SOC_A, 0);
    EPWM_disableADCTriggerEventCountInit(epwmbaseadrr, EPWM_SOC_A);
    EPWM_setADCTriggerEventCountInitValue(epwmbaseadrr, EPWM_SOC_A, 0);

    EPWM_disableADCTrigger(epwmbaseadrr, EPWM_SOC_B);
    EPWM_setADCTriggerSource(epwmbaseadrr, EPWM_SOC_B, EPWM_SOC_DCxEVT1, EPWM_SOC_DCxEVT1);
    EPWM_setADCTriggerEventPrescale(epwmbaseadrr, EPWM_SOC_B, 0);
    EPWM_disableADCTriggerEventCountInit(epwmbaseadrr, EPWM_SOC_B);
    EPWM_setADCTriggerEventCountInitValue(epwmbaseadrr, EPWM_SOC_B, 0);

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
}

uint32 Cdd_Pwm_getBaseAddr(Cdd_Pwm_ChannelType ChannelNumber, uint32 Id)
{
    uint32 baseAddr;
    uint32 Chanl = ChannelNumber;

#if (CDD_PWM_DEV_ERROR_DETECT == STD_ON)
    if ((ChannelNumber >= (uint32)CDD_PWM_MAX_NUM_CHANNELS) && (Id != CDD_PWM_VALID_ID))
    {
        (void)Cdd_Pwm_reportDetError(Id, CDD_PWM_E_PARAM_INVALID_CHANNEL);
        baseAddr = CDD_PWM_INVALID_BASE_ADDR;
    }
    else
#endif
    {
        baseAddr = Cdd_Pwm_ChObj[Chanl].baseaddr;
    }
    return (baseAddr);
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HwUnitInit(Cdd_Pwm_ChObjType *chObj)
{
    /* Init the PWM module. */
    Cdd_Pwm_setTimerBase(chObj->channelID);

#if (STD_ON == CDD_PWM_BASE_CLK_SYNC)
    Cdd_Pwm_setTimerBaseSync(chObj->channelID);
#endif

    Cdd_Pwm_CounterCompare(chObj->channelID);

#if (STD_ON == CDD_PWM_ACTION_QUALIFIER)
    Cdd_Pwm_ActionQualifier(chObj->channelID);
#endif

#if (STD_ON == CDD_PWM_EVENT_TRIGGER)
    Cdd_Pwm_EventTrigger(chObj->channelID);
#endif

#if (STD_ON == CDD_PWM_ADC_ENABLE_DISABLE_API)
    Cdd_Pwm_AdcEventTrigger(chObj->channelID);
#endif

#if (STD_ON == CDD_PWM_TRIP_ZONE)
    Cdd_Pwm_TripZone(chObj->channelID);
#endif
#if (STD_ON == CDD_PWM_DIGITALCOMPARE)
    Cdd_Pwm_DigitalCompare(chObj->channelID);
#endif

#if (STD_ON == CDD_PWM_CHOPPER)
    Cdd_Pwm_Chopper(chObj->channelID);
#endif

#if (STD_ON == CDD_PWM_DEAD_BAND)
    Cdd_Pwm_DeadBand(chObj->channelID);
#endif

/* Initialize SFO status */
#if (STD_ON == CDD_PWM_HR_SFO_STATUS_API)
    Cdd_Pwm_InitSfoCalStatus();
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_STATUS_API) */

    return;
}

/* Initialize SFO status */
#if (STD_ON == CDD_PWM_HR_SFO_STATUS_API)
void Cdd_Pwm_InitSfoCalStatus(void)
{
    uint32 idx = 0U;

    for (idx = 0; idx < CDD_PWM_MAX_NUM_CHANNELS; idx++)
    {
        Cdd_Pwm_ChannelSfoStatus[idx] = CDD_PWM_SFO_INCOMPLETE;
    }
}
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_STATUS_API) */

#if (STD_ON == CDD_PWM_DEINIT_API)
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_IpDeInit_epwm(const Cdd_Pwm_ChObjType *chObj)
{
    uint32 baseadddr = 0U;

    baseadddr = Cdd_Pwm_getBaseAddr(chObj->channelID, CDD_PWM_VALID_ID);

    /* Initialize the CDD_PWM module. */
    if ((baseadddr >= 0x50000000UL) && (baseadddr <= 0x500DF000UL))
    {
        Cdd_Epwm_DeInitialize(baseadddr);
    }
}
#endif

void Cdd_Pwm_setTimerBase(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 baseAddr;

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_timerBaseConfigType *timerBaseParamter = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBase;

    /* Time Base */
    EPWM_setEmulationMode(baseAddr, timerBaseParamter->channelPwmEmulationMode);
    EPWM_setClockPrescaler(baseAddr, timerBaseParamter->channelPwmClockDivider,
                           timerBaseParamter->channelPwmHSClockDivider);
    EPWM_setTimeBasePeriod(baseAddr, timerBaseParamter->channelPwmTbPeriod);

    if (TRUE == timerBaseParamter->channelPwmEnablePhaseShift)
    {
        EPWM_enableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_TBPRD_TBPRDHR);
    }
    else
    {
        EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_TBPRD_TBPRDHR);
    }

    EPWM_setPeriodLoadMode(baseAddr, timerBaseParamter->channelPwmPeriodLoadMode);

    EPWM_setTimeBaseCounterMode(baseAddr, timerBaseParamter->channelPwmCounterMode);

    if (TRUE == timerBaseParamter->channelPwmEnablePhaseShift)
    {
        EPWM_enablePhaseShiftLoad(baseAddr);
        EPWM_setPhaseShift(baseAddr, timerBaseParamter->channelPwmEnablePhaseShiftValue);
    }

    if (timerBaseParamter->channelPwmTbprdlink != CDD_PWM_LINK_DISABLE)
    {
        EPWM_setupEPWMLinks(baseAddr, timerBaseParamter->channelPwmTbprdlink, EPWM_LINK_TBPRD);
    }
}

void Cdd_Pwm_setTimerBaseSync(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 baseAddr;

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_timerBaseSyncType *TimerBaseSyncParamter = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBaseSync;

    /* Timer Base Sync*/
    EPWM_setOneShotSyncOutTrigger(baseAddr, TimerBaseSyncParamter->channelOneShotSyncOutTrigger);

    EPWM_setSyncInPulseSource(baseAddr, TimerBaseSyncParamter->channelSyncOutPulseSource);

    if (TimerBaseSyncParamter->channelForceSync == TRUE)
    {
        EPWM_forceSyncPulse(baseAddr);
    }

    if (TimerBaseSyncParamter->channelSyncOutPulseOnALL == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_ALL);
    }

    if (TimerBaseSyncParamter->channelSyncOutPulseOnCntCmpB == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_B);
    }

    if (TimerBaseSyncParamter->channelSyncOutPulseOnCntCmpC == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_C);
    }

    if (TimerBaseSyncParamter->channelSyncOutPulseOnCntCmpD == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_D);
    }

    if (TimerBaseSyncParamter->channelSyncOutPulseOnCntrZero == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);
    }

    Cdd_Pwm_PwmSyncOutPulseCntCmp(baseAddr, ChannelNumber);
}

static void Cdd_Pwm_PwmSyncOutPulseCntCmp(uint32 baseAddr, Cdd_Pwm_ChannelType ChannelNumber)
{
    Cdd_Pwm_timerBaseSyncType *TimerBaseSyncParamter = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBaseSync;
    if (TimerBaseSyncParamter->channelSyncOutPulseOnDCAEVT1SYNC == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_DCA_EVT1_SYNC);
    }

    if (TimerBaseSyncParamter->channelSyncOutPulseOnDCBEVT1SYNC == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_DCB_EVT1_SYNC);
    }

    if (TimerBaseSyncParamter->channelSyncOutPulseOnSoftware == TRUE)
    {
        EPWM_enableSyncOutPulseSource(baseAddr, EPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    }
}

void Cdd_Pwm_CounterCompare(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 baseAddr;

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    if (baseAddr != CDD_PWM_INVALID_BASE_ADDR)
    {
        Cdd_Pwm_CounterCmpA(ChannelNumber, baseAddr);
        Cdd_Pwm_CounterCmpB(ChannelNumber, baseAddr);
        Cdd_Pwm_CounterCmpC(ChannelNumber, baseAddr);
        Cdd_Pwm_CounterCmpD(ChannelNumber, baseAddr);
    }
}
static void Cdd_Pwm_CounterCmpA(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr)
{
    uint16 DutyValue;

    Cdd_Pwm_compareType         *counterCompareParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelCounterCompare;
    Cdd_Pwm_timerBaseConfigType *timerBaseParamter       = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBase;

    DutyValue = Cdd_Pwm_DutyValue(counterCompareParameter->channelCddPwmCompareValueCmpA,
                                  timerBaseParamter->channelPwmTbPeriod, timerBaseParamter->channelPwmCounterMode);

    /* Counter Compare A */
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_A, (((uint16)(DutyValue)) - 1U));

    if (counterCompareParameter->channelCddPwmCompareValueCmpA == FALSE)
    {
        EPWM_disableCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_A);
        EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    }
    else
    {
        EPWM_setCounterCompareShadowLoadMode(
            baseAddr, EPWM_COUNTER_COMPARE_A,
            (EPWM_CounterCompareLoadMode)counterCompareParameter->channelCddPwmCounterCompareShadowModeCmpA);
    }

    if (counterCompareParameter->channelCddPwmCounterCompareGlobalLoadCmpA == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPA_CMPAHR);
    }
    else
    {
        EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPA_CMPAHR);
    }

    if (counterCompareParameter->channelCddPwmTbprdlinkCmpA != CDD_PWM_LINK_DISABLE)
    {
        EPWM_setupEPWMLinks(baseAddr, counterCompareParameter->channelCddPwmTbprdlinkCmpA, EPWM_LINK_COMP_A);
    }
}

static void Cdd_Pwm_CounterCmpB(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr)
{
    uint16                       DutyValue;
    Cdd_Pwm_compareType         *counterCompareParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelCounterCompare;
    Cdd_Pwm_timerBaseConfigType *timerBaseParamter       = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBase;
    DutyValue = Cdd_Pwm_DutyValue(counterCompareParameter->channelCddPwmCompareValueCmpB,
                                  timerBaseParamter->channelPwmTbPeriod, timerBaseParamter->channelPwmCounterMode);

    /* Counter Compare B */
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_B, (((uint16)(DutyValue)) - 1U));

    if (counterCompareParameter->channelCddPwmCompareValueCmpB == FALSE)
    {
        EPWM_disableCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_B);
        EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    }
    else
    {
        EPWM_setCounterCompareShadowLoadMode(
            baseAddr, EPWM_COUNTER_COMPARE_B,
            (EPWM_CounterCompareLoadMode)counterCompareParameter->channelCddPwmCounterCompareShadowModeCmpB);
    }

    if (counterCompareParameter->channelCddPwmCounterCompareGlobalLoadCmpB == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPB_CMPBHR);
    }
    else
    {
        EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPB_CMPBHR);
    }

    if (counterCompareParameter->channelCddPwmTbprdlinkCmpB != CDD_PWM_LINK_DISABLE)
    {
        EPWM_setupEPWMLinks(baseAddr, counterCompareParameter->channelCddPwmTbprdlinkCmpB, EPWM_LINK_COMP_B);
    }
}

static void Cdd_Pwm_CounterCmpC(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr)
{
    uint16                       DutyValue;
    Cdd_Pwm_compareType         *counterCompareParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelCounterCompare;
    Cdd_Pwm_timerBaseConfigType *timerBaseParamter       = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBase;
    DutyValue = Cdd_Pwm_DutyValue(counterCompareParameter->channelCddPwmCompareValueCmpC,
                                  timerBaseParamter->channelPwmTbPeriod, timerBaseParamter->channelPwmCounterMode);

    /* Counter Compare C */
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_C, (((uint16)(DutyValue)) - 1U));

    if (counterCompareParameter->channelCddPwmCompareValueCmpC == FALSE)
    {
        EPWM_disableCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_C);
        EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    }
    else
    {
        EPWM_setCounterCompareShadowLoadMode(
            baseAddr, EPWM_COUNTER_COMPARE_C,
            (EPWM_CounterCompareLoadMode)counterCompareParameter->channelCddPwmCounterCompareShadowModeCmpC);
    }

    if (counterCompareParameter->channelCddPwmCounterCompareGlobalLoadCmpC == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPC);
    }
    else
    {
        EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPC);
    }

    if (counterCompareParameter->channelCddPwmTbprdlinkCmpC != CDD_PWM_LINK_DISABLE)
    {
        EPWM_setupEPWMLinks(baseAddr, counterCompareParameter->channelCddPwmTbprdlinkCmpC, EPWM_LINK_COMP_C);
    }
}

static void Cdd_Pwm_CounterCmpD(Cdd_Pwm_ChannelType ChannelNumber, uint32 baseAddr)
{
    uint16                       DutyValue;
    Cdd_Pwm_compareType         *counterCompareParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelCounterCompare;
    Cdd_Pwm_timerBaseConfigType *timerBaseParamter       = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBase;
    DutyValue = Cdd_Pwm_DutyValue(counterCompareParameter->channelCddPwmCompareValueCmpD,
                                  timerBaseParamter->channelPwmTbPeriod, timerBaseParamter->channelPwmCounterMode);

    /* Counter Compare D */
    EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_D, (((uint16)(DutyValue)) - 1U));

    if (counterCompareParameter->channelCddPwmCompareValueCmpD == FALSE)
    {
        EPWM_disableCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_D);
        EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_D, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    }
    else
    {
        EPWM_setCounterCompareShadowLoadMode(
            baseAddr, EPWM_COUNTER_COMPARE_D,
            (EPWM_CounterCompareLoadMode)counterCompareParameter->channelCddPwmCounterCompareShadowModeCmpD);
    }

    if (counterCompareParameter->channelCddPwmCounterCompareGlobalLoadCmpC == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPD);
    }
    else
    {
        EPWM_disableGlobalLoadRegisters(baseAddr, EPWM_GL_REGISTER_CMPD);
    }

    if (counterCompareParameter->channelCddPwmTbprdlinkCmpD != CDD_PWM_LINK_DISABLE)
    {
        EPWM_setupEPWMLinks(baseAddr, counterCompareParameter->channelCddPwmTbprdlinkCmpD, EPWM_LINK_COMP_C);
    }
}

void Cdd_Pwm_ActionQualifier(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 epwmbaseadrr;

    epwmbaseadrr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_actionConfigType *ActionQualifierParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelActionQualifier;

    EPWM_enableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLA_AQCTLA2);

    /* Action Qualifier EPWM A */
    if (ActionQualifierParameter->channelPwmActionGlobalLoadEPWMA == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLA_AQCTLA2);
    }
    else
    {
        EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLA_AQCTLA2);
    }

    EPWM_setActionQualifierContSWForceShadowMode(
        epwmbaseadrr, (EPWM_ActionQualifierContForce)ActionQualifierParameter->channelPwmActionShadowModeEPWMA);

    if (ActionQualifierParameter->channelPwmActionShadowModeEPWMA == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLA_AQCTLA2);
        EPWM_setActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_A,
                                              ActionQualifierParameter->channelPwmActionShadowEventEPWMA);
    }
    else
    {
        EPWM_disableActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_A);
    }

    EPWM_setActionQualifierT1TriggerSource(epwmbaseadrr, ActionQualifierParameter->channelPwmT1TriggerSourceEPWMA);

    EPWM_setActionQualifierT2TriggerSource(epwmbaseadrr, ActionQualifierParameter->channelPwmT2TriggerSourceEPWMA);

    EPWM_setActionQualifierSWAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                    ActionQualifierParameter->channelPwmActionQualifierOneTimeSwOutputEPWMA);
    EPWM_setActionQualifierContSWForceAction(
        epwmbaseadrr, EPWM_AQ_OUTPUT_A, ActionQualifierParameter->channelPwmActionQualifierContinuousSwOutputEPWMA);

    /* Action Qualifier EPWM B */
    if (ActionQualifierParameter->channelPwmActionGlobalLoadEPWMB == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);
    }
    else
    {
        EPWM_disableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);
    }

    EPWM_setActionQualifierContSWForceShadowMode(
        epwmbaseadrr, (EPWM_ActionQualifierContForce)ActionQualifierParameter->channelPwmActionShadowModeEPWMB);

    if (ActionQualifierParameter->channelPwmActionShadowModeEPWMB == TRUE)
    {
        EPWM_enableGlobalLoadRegisters(epwmbaseadrr, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);
        EPWM_setActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_B,
                                              ActionQualifierParameter->channelPwmActionShadowEventEPWMB);
    }
    else
    {
        EPWM_disableActionQualifierShadowLoadMode(epwmbaseadrr, EPWM_ACTION_QUALIFIER_B);
    }

    EPWM_setActionQualifierT1TriggerSource(epwmbaseadrr, ActionQualifierParameter->channelPwmT1TriggerSourceEPWMB);

    EPWM_setActionQualifierT2TriggerSource(epwmbaseadrr, ActionQualifierParameter->channelPwmT2TriggerSourceEPWMB);

    EPWM_setActionQualifierSWAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                    ActionQualifierParameter->channelPwmActionQualifierOneTimeSwOutputEPWMB);
    EPWM_setActionQualifierContSWForceAction(
        epwmbaseadrr, EPWM_AQ_OUTPUT_B, ActionQualifierParameter->channelPwmActionQualifierContinuousSwOutputEPWMB);

    /* Event EPWM A */
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseZEROEPWMA,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebasePERIODEPWMA,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseUPCMPAEPWMA,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseDOWNCMPAEPWMA,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseUPCMPBEPWMA,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseDOWNCMPBEPWMA,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnT1COUNTUPEPWMA,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnT1COUNTDOWNEPWMA,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnT2COUNTUPEPWMA,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_A,
                                  ActionQualifierParameter->channelPwmAqOutputOnT2COUNTDOWNEPWMA,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN);

    /* Event EPWM B */
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseZEROEPWMB,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebasePERIODEPWMB,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseUPCMPAEPWMB,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseDOWNCMPAEPWMB,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseUPCMPBEPWMB,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnTimebaseDOWNCMPBEPWMB,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnT1COUNTUPEPWMB,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnT1COUNTDOWNEPWMB,
                                  EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnT2COUNTUPEPWMB,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_UP);
    EPWM_setActionQualifierAction(epwmbaseadrr, EPWM_AQ_OUTPUT_B,
                                  ActionQualifierParameter->channelPwmAqOutputOnT2COUNTDOWNEPWMB,
                                  EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN);
}

void Cdd_Pwm_TripZone(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 epwmbaseadrr;

    epwmbaseadrr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_tripZoneType *tripZoneParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelTripZone;

    /* Trip Zone */
    if (tripZoneParameter->channelPwmAdvancedTripZoneAction == TRUE)
    {
        EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZB_D,
                                  tripZoneParameter->channelPwmTZBAdvDEvent);
        EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZB_U,
                                  tripZoneParameter->channelPwmTZBAdvUEvent);
        EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZA_D,
                                  tripZoneParameter->channelPwmTZAAdvDEvent);
        EPWM_setTripZoneAdvAction(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_TZA_U,
                                  tripZoneParameter->channelPwmTZAAdvUEvent);
        EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U,
                                                 tripZoneParameter->channelPwmDCAEVT1AdvUEvent);
        EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D,
                                                 tripZoneParameter->channelPwmDCAEVT1AdvDEvent);
        EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U,
                                                 tripZoneParameter->channelPwmDCAEVT2AdvUEvent);
        EPWM_setTripZoneAdvDigitalCompareActionA(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D,
                                                 tripZoneParameter->channelPwmDCAEVT2AdvDEvent);
        EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U,
                                                 tripZoneParameter->channelPwmDCBEVT1AdvUEvent);
        EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D,
                                                 tripZoneParameter->channelPwmDCBEVT1AdvDEvent);
        EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U,
                                                 tripZoneParameter->channelPwmDCBEVT2AdvUEvent);
        EPWM_setTripZoneAdvDigitalCompareActionB(epwmbaseadrr, EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D,
                                                 tripZoneParameter->channelPwmDCBEVT2AdvDEvent);
        EPWM_enableTripZoneAdvAction(epwmbaseadrr);
    }
    else
    {
        EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_TZA, tripZoneParameter->channelPwmTZAEvent);
        EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_TZB, tripZoneParameter->channelPwmTZBEvent);
        EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCAEVT1, tripZoneParameter->channelPwmDCAEVT1Event);
        EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCAEVT2, tripZoneParameter->channelPwmDCAEVT2Event);
        EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCBEVT1, tripZoneParameter->channelPwmDCBEVT1Event);
        EPWM_setTripZoneAction(epwmbaseadrr, EPWM_TZ_ACTION_EVENT_DCBEVT2, tripZoneParameter->channelPwmDCBEVT2Event);
        EPWM_disableTripZoneAdvAction(epwmbaseadrr);
    }
    Cdd_Pwm_PwmDCEvent((const Cdd_Pwm_tripZoneType *)tripZoneParameter, epwmbaseadrr);

    Cdd_Pwm_PwmOneShotTzEvent((const Cdd_Pwm_tripZoneType *)tripZoneParameter, epwmbaseadrr);

    Cdd_Pwm_PwmCBCTzEvent((const Cdd_Pwm_tripZoneType *)tripZoneParameter, epwmbaseadrr);

    if (tripZoneParameter->channelPwmDCAEVT2 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_DCAEVT2);
    }

    if (tripZoneParameter->channelPwmDCBEVT2 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_DCBEVT2);
    }

    EPWM_selectCycleByCycleTripZoneClearEvent(epwmbaseadrr, tripZoneParameter->channelPwmCycleByCycleTripZoneClearMode);

    Cdd_Pwm_DisableTzInt(epwmbaseadrr);
}

#if (CDD_PWM_DIGITALCOMPARE == STD_ON)
void Cdd_Pwm_DigitalCompare(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 epwmbaseadrr = 0U;

    /*Get Hw Address of the channel*/
    epwmbaseadrr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_DigitalCompareType DigitalCompareParameter = Cdd_Pwm_ChObj[ChannelNumber].channelDigitalCompare;

    EPWM_setDigitalCompareFilterInput(epwmbaseadrr, DigitalCompareParameter.channelPwmDcFilterInputEventSource);
    EPWM_disableDigitalCompareBlankingWindow(epwmbaseadrr);
    EPWM_setDigitalCompareBlankingEvent(epwmbaseadrr, DigitalCompareParameter.channelPwmCddPwmBlankingWindowStartEvent,
                                        0);
    EPWM_setDigitalCompareWindowOffset(epwmbaseadrr, 0);
    EPWM_setDigitalCompareWindowLength(epwmbaseadrr, 0);
    EPWM_disableDigitalCompareWindowInverseMode(epwmbaseadrr);
    EPWM_disableDigitalCompareCounterCapture(epwmbaseadrr);
    EPWM_setDigitalCompareCounterShadowMode(epwmbaseadrr, FALSE);
    EPWM_disableDigitalCompareEdgeFilter(epwmbaseadrr);

    EPWM_setDigitalCompareEdgeFilterMode(epwmbaseadrr, DigitalCompareParameter.channelPwmCddPwmEdgeFilterMode);
    EPWM_setDigitalCompareEdgeFilterEdgeCount(epwmbaseadrr, DigitalCompareParameter.channelPwmCddPwmEdgeFilterCount);
    EPWM_disableValleyCapture(epwmbaseadrr);
    EPWM_setValleyTriggerSource(epwmbaseadrr, DigitalCompareParameter.channelPwmEdgeFilterCounterCaptureSignal);
    EPWM_setValleyTriggerEdgeCounts(epwmbaseadrr, 0, 0);
    EPWM_disableValleyHWDelay(epwmbaseadrr);
    EPWM_setValleySWDelayValue(epwmbaseadrr, 0);
    EPWM_setValleyDelayDivider(epwmbaseadrr, DigitalCompareParameter.channelPwmValleyDelayDivider);
    EPWM_enableDigitalCompareTripCombinationInput(epwmbaseadrr, 0, EPWM_DC_TYPE_DCAH);
    EPWM_selectDigitalCompareTripInput(epwmbaseadrr, DigitalCompareParameter.channelPwmDCAHigh, EPWM_DC_TYPE_DCAH);

    EPWM_enableDigitalCompareTripCombinationInput(epwmbaseadrr, 0, EPWM_DC_TYPE_DCAL);
    EPWM_selectDigitalCompareTripInput(epwmbaseadrr, DigitalCompareParameter.channelPwmDCALow, EPWM_DC_TYPE_DCAL);
    EPWM_setTripZoneDigitalCompareEventCondition(epwmbaseadrr, EPWM_TZ_DC_OUTPUT_A1,
                                                 DigitalCompareParameter.channelPwmDCAOutputHigh1A);
    EPWM_setTripZoneDigitalCompareEventCondition(epwmbaseadrr, EPWM_TZ_DC_OUTPUT_A2,
                                                 DigitalCompareParameter.channelPwmDCAOutputHigh2A);
    EPWM_disableDigitalCompareADCTrigger(epwmbaseadrr, EPWM_DC_MODULE_A);
    EPWM_setDigitalCompareEventSyncMode(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1,
                                        DigitalCompareParameter.channelPwmSyncModeAEVT1);
    EPWM_setDigitalCompareEventSource(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1,
                                      DigitalCompareParameter.channelPwmSignalSoureAEVT1);
    EPWM_setDigitalCompareEventSyncMode(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_2,
                                        DigitalCompareParameter.channelPwmSyncModeAEVT2);
    EPWM_setDigitalCompareEventSource(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_2,
                                      DigitalCompareParameter.channelPwmSignalSoureAEVT2);
    EPWM_enableDigitalCompareTripCombinationInput(epwmbaseadrr, 0, EPWM_DC_TYPE_DCBH);
    EPWM_selectDigitalCompareTripInput(epwmbaseadrr, DigitalCompareParameter.channelPwmDCBHigh, EPWM_DC_TYPE_DCBH);
    EPWM_enableDigitalCompareTripCombinationInput(epwmbaseadrr, 0, EPWM_DC_TYPE_DCBL);
    EPWM_selectDigitalCompareTripInput(epwmbaseadrr, DigitalCompareParameter.channelPwmDCBLow, EPWM_DC_TYPE_DCBL);
    EPWM_setTripZoneDigitalCompareEventCondition(epwmbaseadrr, EPWM_TZ_DC_OUTPUT_B1,
                                                 DigitalCompareParameter.channelPwmDCBOutputHigh1A);
    EPWM_setTripZoneDigitalCompareEventCondition(epwmbaseadrr, EPWM_TZ_DC_OUTPUT_B2,
                                                 DigitalCompareParameter.channelPwmDCBOutputHigh2A);
    EPWM_disableDigitalCompareADCTrigger(epwmbaseadrr, EPWM_DC_MODULE_B);
    EPWM_setDigitalCompareEventSyncMode(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1,
                                        DigitalCompareParameter.channelPwmSyncModeBEVT1);
    EPWM_setDigitalCompareEventSource(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1,
                                      DigitalCompareParameter.channelPwmSignalSoureBEVT1);
    EPWM_setDigitalCompareEventSyncMode(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_2,
                                        DigitalCompareParameter.channelPwmSyncModeBEVT1);
    EPWM_setDigitalCompareEventSource(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_2,
                                      DigitalCompareParameter.channelPwmSignalSoureBEVT2);
    EPWM_setDigitalCompareCBCLatchMode(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1,
                                       DigitalCompareParameter.channelPwmCBCLatchModeDCAEVT1);
    EPWM_selectDigitalCompareCBCLatchClearEvent(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_1,
                                                DigitalCompareParameter.channelPwmCBCLatchClearModeDCAEVT1);
    EPWM_setDigitalCompareCBCLatchMode(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_2,
                                       DigitalCompareParameter.channelPwmCBCLatchModeDCAEVT2);
    EPWM_selectDigitalCompareCBCLatchClearEvent(epwmbaseadrr, EPWM_DC_MODULE_A, EPWM_DC_EVENT_2,
                                                DigitalCompareParameter.channelPwmCBCLatchClearModeDCAEVT2);
    EPWM_setDigitalCompareCBCLatchMode(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1,
                                       DigitalCompareParameter.channelPwmCBCLatchModeDCBEVT1);
    EPWM_selectDigitalCompareCBCLatchClearEvent(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_1,
                                                DigitalCompareParameter.channelPwmCBCLatchClearModeDCBEVT1);
    EPWM_setDigitalCompareCBCLatchMode(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_2,
                                       DigitalCompareParameter.channelPwmCBCLatchModeDCBEVT2);
    EPWM_selectDigitalCompareCBCLatchClearEvent(epwmbaseadrr, EPWM_DC_MODULE_B, EPWM_DC_EVENT_2,
                                                DigitalCompareParameter.channelPwmCBCLatchClearModeDCBEVT2);
}
#endif /*#if ( CDD_PWM_DIGITALCOMPARE == STD_ON)*/

static void Cdd_Pwm_PwmDCEvent(const Cdd_Pwm_tripZoneType *tripZoneParameter, uint32 epwmbaseadrr)
{
    if (tripZoneParameter->channelPwmOneShotDCAEVT1 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_DCAEVT1);
    }

    if (tripZoneParameter->channelPwmOneShotDCBEVT1 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_DCBEVT1);
    }
}

static void Cdd_Pwm_PwmOneShotTzEvent(const Cdd_Pwm_tripZoneType *tripZoneParameter, uint32 epwmbaseadrr)
{
    if (tripZoneParameter->channelPwmOneShotTZ1 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_OSHT1);
    }

    if (tripZoneParameter->channelPwmOneShotTZ2 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_OSHT2);
    }

    if (tripZoneParameter->channelPwmOneShotTZ3 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_OSHT3);
    }

    if (tripZoneParameter->channelPwmOneShotTZ4 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_OSHT4);
    }

    if (tripZoneParameter->channelPwmOneShotTZ5 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_OSHT5);
    }

    if (tripZoneParameter->channelPwmOneShotTZ6 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_OSHT6);
    }
}
static void Cdd_Pwm_PwmCBCTzEvent(const Cdd_Pwm_tripZoneType *tripZoneParameter, uint32 epwmbaseadrr)
{
    if (tripZoneParameter->channelPwmCBCTZ1 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_CBC1);
    }

    if (tripZoneParameter->channelPwmCBCTZ2 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_CBC2);
    }

    if (tripZoneParameter->channelPwmCBCTZ3 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_CBC3);
    }

    if (tripZoneParameter->channelPwmCBCTZ4 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_CBC4);
    }

    if (tripZoneParameter->channelPwmCBCTZ5 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_CBC5);
    }

    if (tripZoneParameter->channelPwmCBCTZ6 == TRUE)
    {
        EPWM_enableTripZoneSignals(epwmbaseadrr, EPWM_TZ_SIGNAL_CBC6);
    }
}

void Cdd_Pwm_DeadBand(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 epwmbaseadrr;

    epwmbaseadrr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_deadBandType *DeadBandParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelDeadBand;

    /* Deadband */
    if (DeadBandParameter->channelDeadBandShadowMode == FALSE)
    {
        EPWM_disableDeadBandControlShadowLoadMode(epwmbaseadrr);
    }

    EPWM_setDeadBandControlShadowLoadMode(epwmbaseadrr,
                                          (EPWM_DeadBandControlLoadMode)DeadBandParameter->channelDeadBandShadowMode);
    EPWM_setRisingEdgeDeadBandDelayInput(epwmbaseadrr, DeadBandParameter->channelPwmREDDelayInput);
    EPWM_setFallingEdgeDeadBandDelayInput(epwmbaseadrr, DeadBandParameter->channelPwmFEDDelayInput);
    EPWM_setDeadBandDelayPolarity(epwmbaseadrr, EPWM_DB_RED, DeadBandParameter->channelPwmRedBandPolarity);
    EPWM_setDeadBandDelayPolarity(epwmbaseadrr, EPWM_DB_FED, DeadBandParameter->channelPwmFedBandPolarity);
    EPWM_setDeadBandDelayMode(epwmbaseadrr, EPWM_DB_RED, (DeadBandParameter->channelREDEnable));
    EPWM_setDeadBandDelayMode(epwmbaseadrr, EPWM_DB_FED, (DeadBandParameter->channelFEDEnable));
    EPWM_setDeadBandOutputSwapMode(epwmbaseadrr, EPWM_DB_OUTPUT_A, (DeadBandParameter->channelDeadBandSwapOutputA));
    EPWM_setDeadBandOutputSwapMode(epwmbaseadrr, EPWM_DB_OUTPUT_B, (DeadBandParameter->channelDeadBandSwapOutputB));

    if (DeadBandParameter->channelRedShadowMode == FALSE)
    {
        EPWM_disableRisingEdgeDelayCountShadowLoadMode(epwmbaseadrr);
    }

    EPWM_setRisingEdgeDelayCountShadowLoadMode(epwmbaseadrr,
                                               (EPWM_RisingEdgeDelayLoadMode)DeadBandParameter->channelRedShadowMode);
    EPWM_setRisingEdgeDelayCount(epwmbaseadrr, DeadBandParameter->channelREDDelayValue);
    if (DeadBandParameter->channelFedShadowMode == FALSE)
    {
        EPWM_disableFallingEdgeDelayCountShadowLoadMode(epwmbaseadrr);
    }

    EPWM_setFallingEdgeDelayCountShadowLoadMode(epwmbaseadrr,
                                                (EPWM_FallingEdgeDelayLoadMode)DeadBandParameter->channelFedShadowMode);
    EPWM_setFallingEdgeDelayCount(epwmbaseadrr, DeadBandParameter->channelFEDDelayValue);
    EPWM_setDeadBandCounterClock(epwmbaseadrr, DeadBandParameter->channelDeadBandClockMode);
}

void Cdd_Pwm_Chopper(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 epwmbaseadrr;

    epwmbaseadrr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_chopperType *chopperParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelChopper;

    /* Chopper */
    if (chopperParameter->channelChopperEnable == TRUE)
    {
        EPWM_enableChopper(epwmbaseadrr);
    }
    else
    {
        EPWM_disableChopper(epwmbaseadrr);
    }

    EPWM_setChopperDutyCycle(epwmbaseadrr, chopperParameter->channelChopperDuty);
    EPWM_setChopperFreq(epwmbaseadrr, chopperParameter->channelChopperFreqency);
    EPWM_setChopperFirstPulseWidth(epwmbaseadrr, chopperParameter->channelChopperFirstPulseWidth);
}

void Cdd_Pwm_EventTrigger(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32                   epwmbaseadrr;
    Cdd_Pwm_eventConfigType *eventtriggerParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelEventTrigger;

    epwmbaseadrr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    /* Event Trigger */
    EPWM_setInterruptSource(epwmbaseadrr, eventtriggerParameter->channelPwmInterruptEventSources,
                            eventtriggerParameter->channelPwmInterruptMixedSources);
    EPWM_setInterruptEventCount(epwmbaseadrr, eventtriggerParameter->channelPwmInterruptCount);

    if (eventtriggerParameter->channelPwmEnableEventCountInitialValue == TRUE)
    {
        EPWM_enableInterruptEventCountInit(epwmbaseadrr);
    }
    else
    {
        EPWM_disableInterruptEventCountInit(epwmbaseadrr);
    }

    EPWM_setInterruptEventCountInitValue(epwmbaseadrr, eventtriggerParameter->channelPwmEventCountInitialValue);

    if (eventtriggerParameter->channelPwmForceEventValue == TRUE)
    {
        EPWM_forceInterruptEventCountInit(epwmbaseadrr);
    }
}

void Cdd_Pwm_AdcEventTrigger(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32 baseAddr;

    Cdd_Pwm_adcEventTriggerType *channelAdcEvent = &Cdd_Pwm_ChObj[ChannelNumber].channelAdcEventTrigger;

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    if (channelAdcEvent->channelPwmSocAEvent == TRUE)
    {
        EPWM_enableADCTrigger(baseAddr, EPWM_SOC_A);
    }
    else
    {
        EPWM_disableADCTrigger(baseAddr, EPWM_SOC_A);
    }

    EPWM_setADCTriggerSource(baseAddr, EPWM_SOC_A, channelAdcEvent->channelPwmSocAInterruptEventSources,
                             channelAdcEvent->channelPwmSocAMixedSources);

    EPWM_setADCTriggerEventPrescale(baseAddr, EPWM_SOC_A, channelAdcEvent->channelPwmSocAInterruptCount);

    if (channelAdcEvent->channelPwmSocAEvent == TRUE)
    {
        EPWM_enableADCTriggerEventCountInit(baseAddr, EPWM_SOC_A);
    }
    else
    {
        EPWM_disableADCTriggerEventCountInit(baseAddr, EPWM_SOC_A);
    }

    EPWM_setADCTriggerEventCountInitValue(baseAddr, EPWM_SOC_A, channelAdcEvent->channelPwmSocAEventCountInitialValue);

    EPWM_disableADCTrigger(baseAddr, EPWM_SOC_B);

    EPWM_setADCTriggerSource(baseAddr, EPWM_SOC_B, channelAdcEvent->channelPwmSocBInterruptEventSources,
                             channelAdcEvent->channelPwmSocBMixedSources);

    EPWM_setADCTriggerEventPrescale(baseAddr, EPWM_SOC_B, channelAdcEvent->channelPwmSocBInterruptCount);

    if (channelAdcEvent->channelPwmSocAEvent == TRUE)
    {
        EPWM_enableADCTriggerEventCountInit(baseAddr, EPWM_SOC_B);
    }
    else
    {
        EPWM_disableADCTriggerEventCountInit(baseAddr, EPWM_SOC_B);
    }

    EPWM_setADCTriggerEventCountInitValue(baseAddr, EPWM_SOC_B, channelAdcEvent->channelPwmSocBEventCountInitialValue);
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_Start_Private(const Cdd_Pwm_ChObjType *chObj)
{
    /* Initialize the Channel parameter. */
    uint32            baseAddr = chObj->baseaddr;
    EPWM_SignalParams signalParams;

    /* Set the parameters of PWM. */
    signalParams.tbClkDiv   = chObj->channelTimerBase.channelPwmClockDivider;
    signalParams.tbHSClkDiv = chObj->channelTimerBase.channelPwmHSClockDivider;
    signalParams.tbCtrMode  = chObj->channelTimerBase.channelPwmCounterMode;
    signalParams.tbCtrMode  = chObj->channelTimerBase.channelPwmCounterMode;

    /* Set thec channel */
    Cdd_Pwm_configureChannel(baseAddr, &signalParams);
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_Stop_Private(const Cdd_Pwm_ChObjType *chObj)
{
    uint32 baseAddr = chObj->baseaddr;

    /* Stop the channel */
    Cdd_Pwm_deconfigureChannel(baseAddr);
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_configureChannel(uint32 base, const EPWM_SignalParams *signalParams)
{
    /*
     Configure Time Base Counter Mode
    */
    EPWM_setTimeBaseCounterMode(base, signalParams->tbCtrMode);
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_deconfigureChannel(uint32 base)
{
    /*
     Configure Time Base Counter Mode
    */
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_STOP_FREEZE);
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetPinAction_Private(const Cdd_Pwm_ChObjType *chObj, Cdd_Pwm_PinActionType PinAction)
{
    const Cdd_Pwm_ChObjType     *pChannelConfig = chObj;
    uint32                       baseAddr       = pChannelConfig->baseaddr;
    EPWM_ActionQualifierSWOutput swTrigAction;

    /* Set the action required. */
    switch (PinAction)
    {
        case CDD_PWM_DISABLE:
        {
            swTrigAction = EPWM_AQ_SW_DISABLED;
            break;
        }

        case CDD_PWM_SET_LOW:
        {
            swTrigAction = EPWM_AQ_SW_OUTPUT_LOW;
            break;
        }

        case CDD_PWM_SET_HIGH:
        {
            swTrigAction = EPWM_AQ_SW_OUTPUT_HIGH;
            break;
        }

        default:
            break;
    }

    /* Program AQCSFRC Active Register Reload From Shadow Options */
    EPWM_setActionQualifierContSWForceShadowMode(baseAddr, EPWM_AQ_SW_IMMEDIATE_LOAD);

    if (PinAction != CDD_PWM_TOGGLE)
    {
        Cdd_Pwm_otherPinAction(pChannelConfig, baseAddr, swTrigAction);
    }
    else
    {
        Cdd_Pwm_TogglePinAction(pChannelConfig, baseAddr, &swTrigAction);
    }
}

static void Cdd_Pwm_otherPinAction(const Cdd_Pwm_ChObjType *pChannelConfig, uint32 baseAddr,
                                   EPWM_ActionQualifierSWOutput swTrigAction)
{
    /* Enable both outputs epwmxA and epwmxB which is same configuration
     * if channelConfig_PC->outputCh == PWM_OUTPUT_CH_BOTH_A_AND_B */
    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == pChannelConfig->outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == pChannelConfig->outputCh))
    {
        /* Continuous software forced output on A */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_A, swTrigAction);
    }

    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == pChannelConfig->outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == pChannelConfig->outputCh))
    {
        /* Continuous software forced output on B */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_B, swTrigAction);
    }
}

static void Cdd_Pwm_TogglePinAction(const Cdd_Pwm_ChObjType *pChannelConfig, uint32 baseAddr,
                                    EPWM_ActionQualifierSWOutput *swTrigAction)
{
    uint16 actionPin;

    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == pChannelConfig->outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == pChannelConfig->outputCh))
    {
        actionPin = (uint16)EPWM_getActionQualifierContSWForceAction(baseAddr);
        actionPin = (actionPin & 0x3U);
        if ((actionPin) == 0x1U)
        {
            *swTrigAction = EPWM_AQ_SW_OUTPUT_HIGH;
        }
        else
        {
            *swTrigAction = EPWM_AQ_SW_OUTPUT_LOW;
        }

        /* Continuous software forced output on A */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_A, *swTrigAction);
    }

    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == pChannelConfig->outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == pChannelConfig->outputCh))
    {
        actionPin = (uint16)EPWM_getActionQualifierContSWForceAction(baseAddr);
        actionPin = (actionPin & 0x0CU);
        if ((actionPin & 0xFU) == 0x4U)
        {
            *swTrigAction = EPWM_AQ_SW_OUTPUT_HIGH;
        }
        else
        {
            *swTrigAction = EPWM_AQ_SW_OUTPUT_LOW;
        }

        /* Continuous software forced output on B */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_B, *swTrigAction);
    }
}

FUNC(Cdd_Pwm_ValueType, CDD_PWM_CODE) Cdd_Pwm_PrivGetCounter(const Cdd_Pwm_ChObjType *chObj)
{
    Cdd_Pwm_ValueType        pwmCounter     = 0U;
    const Cdd_Pwm_ChObjType *pChannelConfig = chObj;
    uint32                   baseAddr       = pChannelConfig->baseaddr;

    /* Get the Counter Value. */
    pwmCounter = (Cdd_Pwm_ValueType)(EPWM_getTimeBaseCounterValue(baseAddr));

    /* Return the Counter Value. */
    return (pwmCounter);
}

FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_PrivSetAbsoluteThreshold(const Cdd_Pwm_ChObjType *chObj, Cdd_Pwm_ValueType ReferenceValue,
                                 Cdd_Pwm_ValueType AbsoluteValue)
{
    /* Set the channel Values. */
    Cdd_Pwm_ValueType        ocuCounter     = 0U;
    const Cdd_Pwm_ChObjType *pChannelConfig = chObj;
    uint32                   base           = pChannelConfig->baseaddr;

    /* Variable to store the value returned by the function */
    Cdd_Pwm_ReturnType statusValue = CDD_PWM_CM_OUT_REF_INTERVAL;

    /* Set Compare values */
    EPWM_setTimeBaseCounter(base, AbsoluteValue);

    /* Get the Counter Value. */
    ocuCounter = (Cdd_Pwm_ValueType)(EPWM_getTimeBaseCounterValue(base));

    /*check if compare match will happen before counter roll-over*/
    if (ReferenceValue <= AbsoluteValue)
    {
        /*check if counter value is inside the compare match interval*/
        if ((ReferenceValue <= ocuCounter) && (ocuCounter < AbsoluteValue))
        {
            statusValue = CDD_PWM_CM_IN_REF_INTERVAL;
        }
        else
        {
            statusValue = CDD_PWM_CM_OUT_REF_INTERVAL;
        }
    }
    else
    {
        /*check if counter value is outside the compare match interval*/
        if ((ocuCounter < ReferenceValue) && (ocuCounter > AbsoluteValue))
        {
            statusValue = CDD_PWM_CM_OUT_REF_INTERVAL;
        }
        else
        {
            statusValue = CDD_PWM_CM_IN_REF_INTERVAL;
        }
    }

    return (statusValue);
}

FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_PrivSetReleativeThreshold(const Cdd_Pwm_ChObjType *chObj, Cdd_Pwm_ValueType RelativeValue)
{
    /* Set the channel Values. */
    Cdd_Pwm_ValueType        ocuPrevCounter  = 0U;
    Cdd_Pwm_ValueType        ocuAfterCounter = 0U;
    const Cdd_Pwm_ChObjType *pChannelConfig  = chObj;
    uint32                   base            = pChannelConfig->baseaddr;
    uint16                   cmpVal          = RelativeValue;

    /* Variable to store the value returned by the function */
    Cdd_Pwm_ReturnType statusValue = CDD_PWM_CM_OUT_REF_INTERVAL;

    /* Get the Counter Value. */
    ocuPrevCounter = (Cdd_Pwm_ValueType)(EPWM_getTimeBaseCounterValue(base));

    /* Set Compare values */
    cmpVal = cmpVal + ocuPrevCounter;
    EPWM_setTimeBaseCounter(base, cmpVal);

    /* Get the Counter Value. */
    ocuAfterCounter = (Cdd_Pwm_ValueType)(EPWM_getTimeBaseCounterValue(base));

    /*check if compare match will happen before counter roll-over*/
    if (ocuAfterCounter <= cmpVal)
    {
        /*check if counter value is inside the compare match interval*/
        if ((ocuPrevCounter <= ocuAfterCounter) && (ocuAfterCounter < cmpVal))
        {
            statusValue = CDD_PWM_CM_IN_REF_INTERVAL;
        }
        else
        {
            statusValue = CDD_PWM_CM_OUT_REF_INTERVAL;
        }
    }
    else
    {
        /*check if counter value is outside the compare match interval*/
        if ((ocuAfterCounter < ocuPrevCounter) && (ocuAfterCounter > cmpVal))
        {
            statusValue = CDD_PWM_CM_OUT_REF_INTERVAL;
        }
        else
        {
            statusValue = CDD_PWM_CM_IN_REF_INTERVAL;
        }
    }

    return (statusValue);
}

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetPeriodAndDuty_Deterror(Cdd_Pwm_channelParametertype ChannelParameter)
{
    Std_ReturnType    returnval = E_OK;
    Cdd_Pwm_ChObjType local_ChObj;

    if (ChannelParameter.ChannelNumber >= (uint32)CDD_PWM_MAX_NUM_CHANNELS)
    {
        /*Invalid channel */
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_PERIOD_AND_DUTY, CDD_PWM_E_PARAM_INVALID_CHANNEL);
#endif
        returnval = E_NOT_OK;
    }
    else
    {
        local_ChObj = Cdd_Pwm_ChObj[ChannelParameter.ChannelNumber];

        if ((CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus) && (CDD_PWM_STATUS_INIT != local_ChObj.channelState))
        {
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_PERIOD_AND_DUTY, CDD_PWM_E_UNINIT);
#endif
            returnval = E_NOT_OK;
        }

        if (ChannelParameter.DutyCycle > CDD_PWM_CFG_DUTYCYCLE_MAX)
        {
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_PERIOD_AND_DUTY, CDD_PWM_E_PARAM_CHANNEL);
#endif /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

            returnval = E_NOT_OK;
        }
    }
    return (returnval);
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SystemSetPeriodAndDuty(Cdd_Pwm_channelParametertype ChannelParameter)
{
    uint32                       baseAddr;
    Cdd_Pwm_channelParametertype ChannelParameter_0;

    Cdd_Pwm_ChObjType *local_ChObj = &Cdd_Pwm_ChObj[ChannelParameter.ChannelNumber];

    local_ChObj->channelTimerBase.channelPwmTbPeriod = ChannelParameter.Period;

    if (TRUE == local_ChObj->channelTimerBase.channelPwmEnablePhaseShift)
    {
        local_ChObj->channelTimerBase.channelPwmEnablePhaseShiftValue = ChannelParameter.Phase;
    }

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelParameter.ChannelNumber, CDD_PWM_VALID_ID);
    EPWM_setTimeBasePeriod(baseAddr, local_ChObj->channelTimerBase.channelPwmTbPeriod);

    if (ChannelParameter.Period == 0U)
    {
        ChannelParameter_0.ChannelNumber = ChannelParameter.ChannelNumber;
        ChannelParameter_0.DutyCycle     = 0;
        ChannelParameter_0.Phase         = 0U;
        ChannelParameter_0.Period        = 0U;
        ChannelParameter_0.Output        = ChannelParameter.Output;
        Cdd_Pwm_SetDutyCycle_Internal(ChannelParameter_0);
    }
    else
    {
        Cdd_Pwm_SetDutyCycle_Internal(ChannelParameter);
    }
}

FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetDutyCycle_Internal(Cdd_Pwm_channelParametertype ChannelParameter)
{
    uint32               period;
    uint32               baseAddr;
    Cdd_Pwm_OutputChType outputCh;
    Cdd_Pwm_ChObjType   *local_ChObj;
    Cdd_Pwm_ChObjType   *chObj = &Cdd_Pwm_ChObj[ChannelParameter.ChannelNumber];

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelParameter.ChannelNumber, CDD_PWM_VALID_ID);
    outputCh = ChannelParameter.Output;

    /* Reactivate channel if output was forced to idle */

    /* Check for IDLE state. */
    if ((boolean)TRUE == chObj->channelForcedIdle)
    {
        /* Program AQCSFRC Active Register Reload From Shadow Options */
        EPWM_setActionQualifierContSWForceShadowMode(baseAddr, EPWM_AQ_SW_IMMEDIATE_LOAD);

        /* Enable both outputs epwmxA and epwmxB which is same configuration
         * if channelConfig_PC->outputCh == PWM_OUTPUT_CH_BOTH_A_AND_B */
        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on A */
            EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_A, EPWM_AQ_SW_DISABLED);
        }

        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on B */
            EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_DISABLED);
        }

        /* Enable both outputs epwmxA and epwmxB which is same configuration
         * if channelConfig_PC->outputCh == PWM_OUTPUT_CH_BOTH_A_AND_B */
        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on A */
            EPWM_forceActionQualifierSWAction(baseAddr, EPWM_AQ_OUTPUT_A);
        }

        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            /* Continuous software forced output on B */
            EPWM_forceActionQualifierSWAction(baseAddr, EPWM_AQ_OUTPUT_B);
        }
        chObj->channelForcedIdle = (boolean)FALSE;
    }

    /* Updating Init time dutyCycle which is used to enable notifications,
     * if the duty cycle is not 0% or 100% */
    local_ChObj = &Cdd_Pwm_ChObj[ChannelParameter.ChannelNumber];

    period = (uint32)EPWM_getTimeBasePeriod(baseAddr);

    if (TRUE == local_ChObj->channelTimerBase.channelPwmEnablePhaseShift)
    {
        EPWM_setPhaseShift(baseAddr, local_ChObj->channelTimerBase.channelPwmEnablePhaseShiftValue);
    }
    Cdd_Pwm_GenerateSignal(ChannelParameter, period, outputCh, baseAddr, local_ChObj, (const Cdd_Pwm_ChObjType *)chObj);
}

static void Cdd_Pwm_GenerateSignal(Cdd_Pwm_channelParametertype ChannelParameter, uint32 period,
                                   Cdd_Pwm_OutputChType outputCh, uint32 baseAddr, Cdd_Pwm_ChObjType *local_ChObj,
                                   const Cdd_Pwm_ChObjType *chObj)
{
    EPWM_SignalParams signalParams;
    uint16            dutyintvalue;
    uint32            sysClk;

    sysClk                 = CDD_PWM_SYSTEM_CLK_FREQ;
    signalParams.tbCtrMode = local_ChObj->channelTimerBase.channelPwmCounterMode;

    /* Update DutyCycle */
    /* Check the Output outputCh */
    /* Set the parameters of PWM. */
    signalParams.freqInHz = (float32)period;
    dutyintvalue          = Cdd_Pwm_DutyValue(ChannelParameter.DutyCycle, period, signalParams.tbCtrMode);

    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
    {
        local_ChObj->channelCounterCompare.channelCddPwmCompareValueCmpA = dutyintvalue;
    }

    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
    {
        local_ChObj->channelCounterCompare.channelCddPwmCompareValueCmpB = dutyintvalue;
    }

    signalParams.dutyValA = (float32)(local_ChObj->channelCounterCompare.channelCddPwmCompareValueCmpA);
    signalParams.dutyValB = (float32)(local_ChObj->channelCounterCompare.channelCddPwmCompareValueCmpB);

    /* Set the Polarity. */
    if (chObj->polarity == CDD_PWM_HIGH)
    {
        signalParams.invertSignalB = (boolean)0;
    }
    else
    {
        signalParams.invertSignalB = (boolean)1;
    }

    signalParams.sysClkInHz = (float32)sysClk;
    signalParams.tbClkDiv   = local_ChObj->channelTimerBase.channelPwmClockDivider;
    signalParams.tbHSClkDiv = local_ChObj->channelTimerBase.channelPwmHSClockDivider;

    /* Genearte the PWM signal. */
    Cdd_Pwm_configureSignal(baseAddr, &signalParams);
}

/*****************************************************************************

 CDD_PWM_configureSignal

******************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_configureSignal(uint32 base, const EPWM_SignalParams *signalParams)
{
    uint16 tbPrdVal = 0U, cmpAVal = 0U, cmpBVal = 0U;

    /*
     Configure Time Base counter Clock
    */
    EPWM_setClockPrescaler(base, signalParams->tbClkDiv, signalParams->tbHSClkDiv);

    /*
     Configure Time Base Counter Mode
    */
    EPWM_setTimeBaseCounterMode(base, signalParams->tbCtrMode);

    tbPrdVal = (uint16)signalParams->freqInHz;
    cmpAVal  = (uint16)signalParams->dutyValA;
    cmpBVal  = (uint16)signalParams->dutyValB;

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

    /*
     Setup shadow register load on ZERO
    */
    EPWM_setCounterCompareShadowLoadMode(base, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(base, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    /*
     Set Compare values
    */
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_A, (cmpAVal - 1U));
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B, (cmpBVal - 1U));

    /*
     Set actions for ePWMxA & ePWMxB
    */
    if (signalParams->tbCtrMode == EPWM_COUNTER_MODE_UP)
    {
        /*
        Set PWMxA on Zero
        */
        EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

        /*
         Clear PWMxA on event A, up count
        */
        EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

        if (signalParams->invertSignalB == TRUE)
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
        }
        else
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
        }
    }
    else if ((signalParams->tbCtrMode == EPWM_COUNTER_MODE_DOWN))
    {
        /*
         Set PWMxA on Zero
        */
        EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

        /*
         Clear PWMxA on event A, down count
        */
        EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

        if (signalParams->invertSignalB == TRUE)
        {
            /*
             Clear PWMxB on Zero
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
            /*
             Set PWMxB on event B, down count
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
        }
        else
        {
            /*
             Set PWMxB on Zero
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
            /*
             Clear PWMxB on event B, down count
            */
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
        }
    }
    else if (signalParams->tbCtrMode == EPWM_COUNTER_MODE_UP_DOWN)
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
        /* No action required  */
    }
}
#endif

#if (STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetOutputToIdle_Deterror(Cdd_Pwm_ChannelType ChannelNumber)
{
    Std_ReturnType returnval = E_OK;

    Cdd_Pwm_ChObjType *local_ChObj = &Cdd_Pwm_ChObj[ChannelNumber];

    if (ChannelNumber >= (uint32)CDD_PWM_MAX_NUM_CHANNELS)
    {
/*Invalid channel */
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
        (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_OUTPUT_TO_IDLE, CDD_PWM_E_PARAM_INVALID_CHANNEL);
#endif
        returnval = E_NOT_OK;
    }
    else
    {
        if ((CDD_PWM_STATUS_INIT != Cdd_Pwm_DrvStatus) && (CDD_PWM_STATUS_INIT != local_ChObj->channelState))
        {
#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
            (void)Cdd_Pwm_reportDetError(CDD_PWM_SID_SET_OUTPUT_TO_IDLE, CDD_PWM_E_UNINIT);
#endif
            returnval = E_NOT_OK;
        }
    }
    /* (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */
    return (returnval);
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SystemSetOutputToIdle(Cdd_Pwm_ChannelType ChannelNumber)
{
    uint32                       baseAddr;
    EPWM_ActionQualifierSWOutput swTrigAction;
    Cdd_Pwm_OutputChType         outputCh;
    Cdd_Pwm_ChObjType           *local_ChObj = &Cdd_Pwm_ChObj[ChannelNumber];

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);
    outputCh = local_ChObj->outputCh;

    if (CDD_PWM_HIGH == local_ChObj->idleState)
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
    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
    {
        /* Continuous software forced output on A */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_A, swTrigAction);
    }

    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
    {
        /* Continuous software forced output on B */
        EPWM_setActionQualifierContSWForceAction(baseAddr, EPWM_AQ_OUTPUT_B, swTrigAction);
    }

    local_ChObj->channelForcedIdle = TRUE;
}
#endif /*(STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API) */

/*****************************************************************************

 CDD_PWM_setEmulationMode

*****************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_setEmulationMode(uint32 base, EPWM_EmulationMode emulationMode)
{
    /*
     Write to FREE_SOFT bits
    */
    HW_WR_REG16(base + PWM_EPWM_TBCTL, ((HW_RD_REG16(base + PWM_EPWM_TBCTL) & (~PWM_EPWM_TBCTL_FREE_SOFT_MASK)) |
                                        ((uint16)emulationMode << PWM_EPWM_TBCTL_FREE_SOFT_SHIFT)));
}

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_DisableInterrupt(Cdd_Pwm_ChannelType ChannelNumber)
{
    /* Get the base addr. */
    uint32 baseAddr;
    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    /* Disable Interrupt. */
    EPWM_disableInterrupt(baseAddr);
}

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_EnableInterrupt(Cdd_Pwm_ChannelType ChannelParameter, Cdd_Pwm_InterruptType EdgeInterruptSource)
{
    /* Get the base addr. */
    uint32 baseAddr;
    baseAddr = Cdd_Pwm_getBaseAddr(ChannelParameter, CDD_PWM_VALID_ID);

    Cdd_Pwm_ChObjType   *local_ChObj = &Cdd_Pwm_ChObj[ChannelParameter];
    Cdd_Pwm_PinStateType Pinstate    = local_ChObj->polarity;
    Cdd_Pwm_OutputChType outputCh    = local_ChObj->outputCh;

    /* Enable Interrupt. */
    CDD_PWM_enableInterrupt_Notification(baseAddr, outputCh, Pinstate, EdgeInterruptSource.EdgeSource);
    EPWM_clearEventTriggerInterruptFlag(baseAddr);

    if (EdgeInterruptSource.interruptSource != 0U)
    {
        EPWM_setInterruptSource(baseAddr, EdgeInterruptSource.interruptSource,
                                EdgeInterruptSource.mixedInterruptSource);
    }

    EPWM_enableInterrupt(baseAddr);
    local_ChObj->channelNotifyActiveFlag = (uint32)TRUE;
}

FUNC(void, CDD_PWM_CODE)
CDD_PWM_enableInterrupt_Notification(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh, Cdd_Pwm_PinStateType Pinstate,
                                     Cdd_Pwm_EdgeNotificationType Notification)
{
    Cdd_Pwm_PinStateType polarity = Pinstate;
    switch (Notification)
    {
        case CDD_PWM_FALLING_EDGE:
            if (polarity == CDD_PWM_HIGH)
            {
                Cdd_Pmw_FallingEdgeHighPol(baseAddr, outputCh);
            }
            else
            {
                Cdd_Pmw_FallingEdgeLowPol(baseAddr, outputCh);
            }
            break;

        case CDD_PWM_RISING_EDGE:
            if (polarity == CDD_PWM_HIGH)
            {
                Cdd_Pmw_RisingEdgeHighPol(baseAddr, outputCh);
            }
            else
            {
                Cdd_Pmw_RisingEdgeLowPol(baseAddr, outputCh);
            }
            break;

        case CDD_PWM_BOTH_EDGES:

            Cdd_Pmw_BothEdges(baseAddr, outputCh);

            break;

        default:
            /*Do nothing*/
            break;
    }
}

static void Cdd_Pmw_FallingEdgeHighPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh)
{
    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPA, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPB, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAD_CBD);
    }
}

static void Cdd_Pmw_FallingEdgeLowPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh)
{
    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPA, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPB, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAU_CBU);
    }
}

static void Cdd_Pmw_RisingEdgeHighPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh)
{
    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPA, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_U_CMPB, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAU_CBU);
    }
}

static void Cdd_Pmw_RisingEdgeLowPol(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh)
{
    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPA, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_D_CMPB, EPWM_INT_TBCTR_ZERO);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, EPWM_INT_TBCTR_CAD_CBD);
    }
}

static void Cdd_Pmw_BothEdges(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh)
{
    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, 0x000C);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, 0x0020);
    }

    if ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh)
    {
        EPWM_setInterruptSource(baseAddr, EPWM_INT_TBCTR_ETINTMIX, 0x003C);
    }
}

#endif /*(STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

#if (STD_ON == CDD_PWM_REGISTER_READBACK_API)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_IpRegisterReadback_epwm(uint32 ChannelNumber, Cdd_Pwm_RegisterReadbackType *RegRbPtr)
{
    /* Get the base addr. */
    uint32 baseAddr;
    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    RegRbPtr->pwmTbCtl1 = HW_RD_REG16(baseAddr + PWM_EPWM_TBCTL);
    RegRbPtr->pwmTbCtl2 = HW_RD_REG16(baseAddr + PWM_EPWM_TBCTL2);
}
#endif /*CDD_PWM_REGISTER_READBACK_API*/

void Cdd_Pwm_EnableAdcTrigger(uint32 baseAddr, Cdd_Pwm_AdcSocType adcSoc)
{
    if (TRUE == adcSoc.channelEnable)
    {
        EPWM_enableADCTrigger(baseAddr, adcSoc.adcSocSource);
        EPWM_setADCTriggerSource(baseAddr, adcSoc.adcSocSource,
                                 (EPWM_ADCStartOfConversionSource)adcSoc.adcInterruptSource,
                                 adcSoc.adcMixedInterruptSource);
    }
    else
    {
        EPWM_disableADCTrigger(baseAddr, adcSoc.adcSocSource);
    }
}

void Cdd_Pwm_tbSyncEnable(uint32 baseAddr, uint32 tbPhsValue, uint32 counterDir)
{
    /* counter direction configuration. */
    HW_WR_FIELD16(((baseAddr + CSL_EPWM_OFFSET) + CSL_EPWM_TBCTL), CSL_EPWM_TBCTL_PHSDIR, (uint16)counterDir);

    /* phase value configuration */
    HW_WR_FIELD16(((baseAddr + CSL_EPWM_OFFSET) + CSL_EPWM_TBPHS), CSL_EPWM_TBPHS, (uint16)tbPhsValue);

    /* Enable sync: Load time base counter with phase register value. */
    HW_WR_FIELD16(((baseAddr + CSL_EPWM_OFFSET) + CSL_EPWM_TBCTL), CSL_EPWM_TBCTL_PHSEN,
                  (uint16)CSL_EPWM_TBCTL_PHSEN_LOAD);
}

void Cdd_Pwm_tbSyncDisable(uint32 baseAddr)
{
    HW_WR_FIELD16(((baseAddr + CSL_EPWM_OFFSET) + CSL_EPWM_TBCTL), CSL_EPWM_TBCTL_PHSEN,
                  (uint16)CSL_EPWM_TBCTL_PHSEN_DO_NOT_LOAD);
}
void Cdd_Pwm_tbTriggerSwSync(uint32 baseAddr)
{
    HW_WR_FIELD16(((baseAddr + CSL_EPWM_OFFSET) + CSL_EPWM_TBCTL), CSL_EPWM_TBCTL_SWFSYNC,
                  (uint16)CSL_EPWM_TBCTL_SWFSYNC_FORCE_SYNC);
}

uint16 Cdd_Pwm_tbGetStatus(uint32 baseAddr, uint32 tbStatusMask)
{
    uint16 status = 0U;

    if (tbStatusMask == CDD_PWM_TB_STS_CTR_DIR)
    {
        status = EPWM_getTimeBaseCounterDirection(baseAddr);
    }

    if (tbStatusMask == CDD_PWM_TB_STS_CTR_MAX)
    {
        status = EPWM_getTimeBaseCounterOverflowStatus(baseAddr);
    }

    if (tbStatusMask == CDD_PWM_TB_STS_SYNCI)
    {
        status = EPWM_getSyncStatus(baseAddr);
    }

    return (status);
}

void Cdd_Pwm_tbStatusClear(uint32 baseAddr, uint32 tbStatusClrMask)
{
    if (tbStatusClrMask == CDD_PWM_TB_STS_SYNCI)
    {
        EPWM_clearTimeBaseCounterOverflowEvent(baseAddr);
    }

    if (tbStatusClrMask == CDD_PWM_TB_STS_CTR_MAX)
    {
        EPWM_clearSyncEvent(baseAddr);
    }
}

uint32 Cdd_Pwm_counterComparatorCfg(uint32 baseAddr, Cdd_Pwm_OutputChType cmpType, uint32 cmpVal,
                                    uint32 enableShadowWrite, uint32 shadowToActiveLoadTrigger, uint32 overwriteShadow)
{
    uint32 status = FALSE;

    if ((CDD_PWM_OUTPUT_CH_A == cmpType) || (CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == cmpType))
    {
        if ((TRUE == overwriteShadow) ||
            (FALSE == EPWM_getCounterCompareShadowStatus(baseAddr, EPWM_COUNTER_COMPARE_A)))
        {
            EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_A, (((uint16)(cmpVal)) - 1U));

            EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_A,
                                                 (EPWM_CounterCompareLoadMode)shadowToActiveLoadTrigger);

            status = TRUE;
        }
    }
    else if ((CDD_PWM_OUTPUT_CH_B == cmpType) || (CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == cmpType))
    {
        if ((TRUE == overwriteShadow) ||
            (FALSE == EPWM_getCounterCompareShadowStatus(baseAddr, EPWM_COUNTER_COMPARE_B)))
        {
            EPWM_setCounterCompareValue(baseAddr, EPWM_COUNTER_COMPARE_A, (((uint16)(cmpVal)) - 1U));

            EPWM_setCounterCompareShadowLoadMode(baseAddr, EPWM_COUNTER_COMPARE_A,
                                                 (EPWM_CounterCompareLoadMode)shadowToActiveLoadTrigger);

            status = TRUE;
        }
    }
    else
    {
        /* This error does not happen because of check done already */
    }

    return (status);
}

void Cdd_Pwm_deadbandCfg(uint32 baseAddr, const CDD_PWM_DeadbandCfgType *pCfg)
{
    uint32 base   = baseAddr;
    uint16 regval = 0U;
    /*
     Configure the output mode
    */
    regval  = HW_RD_REG16(base + (uint32)PWM_EPWM_DBCTL);
    regval &= (uint16)(~((uint16)1U << 0U));
    regval |= ((uint16)pCfg->outputMode << 0U);
    HW_WR_REG16(base + (uint32)PWM_EPWM_DBCTL, regval);

    /*
     Configure the input source for dead-band
    */
    regval  = HW_RD_REG16(base + (uint32)PWM_EPWM_DBCTL);
    regval &= (uint16)(~((uint16)1U << 4U));
    regval |= ((uint16)pCfg->inputMode << 4U);
    HW_WR_REG16(base + (uint32)PWM_EPWM_DBCTL, regval);

    /*
     Configure the polarity selection
    */
    regval  = HW_RD_REG16(base + (uint32)PWM_EPWM_DBCTL);
    regval &= (uint16)(~((uint16)1U << 2U));
    regval |= ((uint16)pCfg->polaritySelect << 2U);
    HW_WR_REG16(base + (uint32)PWM_EPWM_DBCTL, regval);

    /* Set the RED (Rising Edge Delay) count */
    HW_WR_REG16(base + CSL_EPWM_DBRED, (uint16)pCfg->fallingEdgeDelay);

    /* Set the FED (Falling Edge Delay) count */
    HW_WR_REG16(base + CSL_EPWM_DBFED, (uint16)pCfg->risingEdgeDelay);
}

void Cdd_Pwm_deadbandBypass(uint32 baseAddr)
{
    HW_WR_FIELD16(((baseAddr + CSL_EPWM_OFFSET) + CSL_EPWM_DBCTL), CSL_EPWM_DBCTL_OUT_MODE,
                  (uint16)CSL_EPWM_DBCTL_OUT_MODE_DISABLED);
}

void Cdd_Pwm_chopperCfg(uint32 baseAddr, const CDD_PWM_ChopperCfgType *pCfg)
{
    uint32 freqDivider = pCfg->clkFrequency;

    /* Configure chopping clock frequency */
    if (freqDivider > CDD_PWM_CHP_CLK_FREQ_DIV_BY_8)
    {
        freqDivider = CDD_PWM_CHP_CLK_FREQ_DIV_BY_8;
    }
    EPWM_setChopperDutyCycle(baseAddr, pCfg->dutyCycle);
    EPWM_setChopperFreq(baseAddr, freqDivider);
    EPWM_setChopperFirstPulseWidth(baseAddr, pCfg->oneShotPulseWidth);
}

void Cdd_Pwm_chopperEnable(uint32 baseAddr, uint32 enableChopper)
{
    /* Chopper */
    if (enableChopper == TRUE)
    {
        EPWM_enableChopper(baseAddr);
    }
    else
    {
        EPWM_disableChopper(baseAddr);
    }
}

void Cdd_Pwm_tzTripEventEnable(uint32 baseAddr, uint32 tzEventType)
{
    EPWM_enableTripZoneSignals(baseAddr, tzEventType);
}

void Cdd_Pwm_tzTripEventDisable(uint32 baseAddr, uint32 tzEventType)
{
    EPWM_disableTripZoneSignals(baseAddr, tzEventType);
}

void Cdd_Pwm_tzIntrEnable(uint32 epwmbaseadrr, uint32 tzEventType, Cdd_Pwm_tripZoneType *tripZoneParameter)
{
    if ((tripZoneParameter->channelPwmTZCBCInterrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_CBC))
    {
        EPWM_enableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_CBC);
    }

    if ((tripZoneParameter->channelPwmDCAEVT1Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCAEVT1))
    {
        EPWM_enableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCAEVT1);
    }

    if ((tripZoneParameter->channelPwmDCAEVT2Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCAEVT2))
    {
        EPWM_enableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCAEVT2);
    }

    if ((tripZoneParameter->channelPwmDCBEVT1Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCBEVT1))
    {
        EPWM_enableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCBEVT1);
    }

    if ((tripZoneParameter->channelPwmDCBEVT2Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCBEVT2))
    {
        EPWM_enableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCBEVT2);
    }

    if ((tripZoneParameter->channelPwmTZOneShotInterrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_OST))
    {
        EPWM_enableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_OST);
    }
}

void Cdd_Pwm_tzIntrDisable(uint32 epwmbaseadrr, uint32 tzEventType, Cdd_Pwm_tripZoneType *tripZoneParameter)
{
    if ((tripZoneParameter->channelPwmTZCBCInterrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_CBC))
    {
        EPWM_disableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_CBC);
    }

    if ((tripZoneParameter->channelPwmDCAEVT1Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCAEVT1))
    {
        EPWM_disableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCAEVT1);
    }

    if ((tripZoneParameter->channelPwmDCAEVT2Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCAEVT2))
    {
        EPWM_disableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCAEVT2);
    }

    if ((tripZoneParameter->channelPwmDCBEVT1Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCBEVT1))
    {
        EPWM_disableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCBEVT1);
    }

    if ((tripZoneParameter->channelPwmDCBEVT2Interrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_DCBEVT2))
    {
        EPWM_disableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_DCBEVT2);
    }

    if ((tripZoneParameter->channelPwmTZOneShotInterrupt == TRUE) && (tzEventType == EPWM_TZ_INTERRUPT_OST))
    {
        EPWM_disableTripZoneInterrupt(epwmbaseadrr, EPWM_TZ_INTERRUPT_OST);
    }
}

uint16 Cdd_Pwm_tzEventStatus(uint32 baseAddr, uint32 eventMask)
{
    /* Get the status */
    uint16 status = 0U;

    if (CDD_PWM_TZ_STS_FLG_CBC == eventMask)
    {
        status = EPWM_getCycleByCycleTripZoneFlagStatus(baseAddr);
    }

    if (CDD_PWM_TZ_STS_FLG_OST == eventMask)
    {
        status = EPWM_getOneShotTripZoneFlagStatus(baseAddr);
    }

    if (CDD_PWM_TZ_STS_FLG_INT == eventMask)
    {
        status = EPWM_getTripZoneFlagStatus(baseAddr);
    }

    return (status);
}

void Cdd_Pwm_tzEventStatusClear(uint32 baseAddr, uint32 eventMask, uint32 Flags)
{
    /* Clear the events. */
    if (CDD_PWM_TZ_STS_FLG_CBC == eventMask)
    {
        EPWM_clearCycleByCycleTripZoneFlag(baseAddr, Flags);
    }

    if (CDD_PWM_TZ_STS_FLG_OST == eventMask)
    {
        EPWM_clearOneShotTripZoneFlag(baseAddr, Flags);
    }

    if (CDD_PWM_TZ_STS_FLG_INT == eventMask)
    {
        EPWM_clearTripZoneFlag(baseAddr, Flags);
    }
}

uint16 Cdd_Pwm_etIntrStatus(uint32 baseAddr)
{
    return (EPWM_getEventTriggerInterruptStatus(baseAddr));
}

void Cdd_Pwm_etIntrClear(uint32 baseAddr)
{
    EPWM_clearEventTriggerInterruptFlag(baseAddr);
}

void Cdd_Pwm_etIntrTrigger(uint32 baseAddr)
{
    EPWM_enableInterrupt(baseAddr);
}

uint16 Cdd_Pwm_etGetEventCount(uint32 baseAddr)
{
    return (EPWM_getInterruptEventCount(baseAddr));
}

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_reportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(CDD_PWM_MODULE_ID, CDD_PWM_INSTANCE_ID, apiId, errorId);
}
#endif /* #if (STD_ON == CDD_PWM_DEV_ERROR_DETECT) */

void Cdd_Pwm_DisableTzInt(uint32 baseAddr)
{
    EPWM_disableTripZoneInterrupt(baseAddr,
                                  (EPWM_TZ_INTERRUPT_CBC | EPWM_TZ_INTERRUPT_OST | EPWM_TZ_INTERRUPT_DCAEVT1 |
                                   EPWM_TZ_INTERRUPT_DCAEVT2 | EPWM_TZ_INTERRUPT_DCBEVT1 | EPWM_TZ_INTERRUPT_DCBEVT2));

    EPWM_clearCycleByCycleTripZoneFlag(
        baseAddr, (EPWM_TZ_INTERRUPT_CBC | EPWM_TZ_INTERRUPT_OST | EPWM_TZ_INTERRUPT_DCAEVT1 |
                   EPWM_TZ_INTERRUPT_DCAEVT2 | EPWM_TZ_INTERRUPT_DCBEVT1 | EPWM_TZ_INTERRUPT_DCBEVT2));
}

#if (STD_ON == CDD_PWM_HR_SET_HRPWM_API)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_HrSystemSetPeriodAndDuty(Cdd_Pwm_channelParametertype ChannelParameter)
{
    uint32               base;
    uint32               period;
    uint32               duty_percent;
    float32              duty_percent_f;
    uint32               ChannelNumber = ChannelParameter.ChannelNumber;
    Cdd_Pwm_OutputChType outputCh      = ChannelParameter.Output;

    const Cdd_Pwm_timerBaseConfigType *channelTimeBaseParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelTimerBase;
    const Cdd_Pwm_compareType *channelCounterCompareParameter   = &Cdd_Pwm_ChObj[ChannelNumber].channelCounterCompare;
    const Cdd_Pwm_actionConfigType *channelActionQualParameter  = &Cdd_Pwm_ChObj[ChannelNumber].channelActionQualifier;

    base = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_SID_HR_SET_HRPWM_API);

    if ((base >= 0x50000000UL) && (base <= 0x500DF000UL))
    {
        period = ChannelParameter.Period;

        duty_percent_f =
            (((float32)(((float32)(ChannelParameter.DutyCycle)) / (float32)CDD_PWM_CFG_DUTYCYCLE_MAX)) * (float32)100);
        duty_percent = duty_percent_f;

        /* Set-up TBCLK */
        EPWM_setTimeBasePeriod(base, period - 0x01U);
        EPWM_setPhaseShift(base, 0U);
        EPWM_setTimeBaseCounter(base, 0U);

        /* set duty 50% initially */
        /* Enable both outputs epwmxA and epwmxB which is same configuration. */
        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_A, (((period * duty_percent) / 100U) << 8U));
        }

        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_B, (((period * duty_percent) / 100U) << 8U));
        }

        /* Set up counter mode */
        EPWM_setTimeBaseCounterMode(base, channelTimeBaseParameter->channelPwmCounterMode);
        EPWM_disablePhaseShiftLoad(base);
        EPWM_setClockPrescaler(base, channelTimeBaseParameter->channelPwmClockDivider,
                               channelTimeBaseParameter->channelPwmHSClockDivider);

        /* Set up shadowing */
        /* Enable both outputs epwmxA and epwmxB which is same configuration. */
        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            EPWM_setCounterCompareShadowLoadMode(
                base, EPWM_COUNTER_COMPARE_A,
                channelCounterCompareParameter->channelCddPwmCounterCompareShadowEventCmpA);
        }

        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            EPWM_setCounterCompareShadowLoadMode(
                base, EPWM_COUNTER_COMPARE_B,
                channelCounterCompareParameter->channelCddPwmCounterCompareShadowEventCmpB);
        }

        /* Set actions channel A*/
        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseZEROEPWMA,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebasePERIODEPWMA,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseUPCMPAEPWMA,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseDOWNCMPAEPWMA,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseUPCMPBEPWMA,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseDOWNCMPBEPWMA,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
        }

        /* Set actions channel B*/
        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseZEROEPWMB,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebasePERIODEPWMB,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseUPCMPAEPWMB,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseDOWNCMPAEPWMB,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseUPCMPBEPWMB,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

            EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_B,
                                          channelActionQualParameter->channelPwmAqOutputOnTimebaseDOWNCMPBEPWMB,
                                          EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
        }

        Cdd_Pwm_PwmHRConfig(ChannelNumber, outputCh, base);
        HRPWM_enableAutoConversion(base);
        HRPWM_disablePeriodControl(base);
        HRPWM_disablePhaseShiftLoad(base);
    }
}

static void Cdd_Pwm_PwmHRConfig(uint32 ChannelNumber, Cdd_Pwm_OutputChType outputCh, uint32 base)
{
    const Cdd_Pwm_hrPwmType *channelHighResParameter = &Cdd_Pwm_ChObj[ChannelNumber].channelHrPwm;
    /* Enable both outputs epwmxA and epwmxB which is same configuration. */
    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
    {
        HRPWM_setMEPEdgeSelect(base, HRPWM_CHANNEL_A, channelHighResParameter->channelHrSelEdgeModeEPWMA);
        HRPWM_setMEPControlMode(base, HRPWM_CHANNEL_A, channelHighResParameter->channelHrCtrlModeEPWMA);
        HRPWM_setCounterCompareShadowLoadEvent(base, HRPWM_CHANNEL_A,
                                               channelHighResParameter->channelHrShadowActiveLoadPwmA);
    }

    if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
        ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
    {
        HRPWM_setMEPEdgeSelect(base, HRPWM_CHANNEL_B, channelHighResParameter->channelHrSelEdgeModeEPWMB);
        HRPWM_setMEPControlMode(base, HRPWM_CHANNEL_B, channelHighResParameter->channelHrCtrlModeEPWMB);
        HRPWM_setCounterCompareShadowLoadEvent(base, HRPWM_CHANNEL_B,
                                               channelHighResParameter->channelHrShadowActiveLoadPwmB);
    }
}
#endif /* #if (STD_ON == CDD_PWM_HR_SET_HRPWM_API) */

#if (STD_ON == CDD_PWM_HR_SFO_CAL_API)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_HrSfoCalibration_Private(Cdd_Pwm_channelParametertype ChannelParameter)
{
    float32              dutyFine;
    Cdd_Pwm_OutputChType outputCh;
    uint32               base;
    uint16               Channel_value;

    base = Cdd_Pwm_getBaseAddr(ChannelParameter.ChannelNumber, CDD_PWM_SID_HR_SFO_CAL_API);
    dutyFine =
        (((float32)(((float32)(ChannelParameter.DutyCycle)) / (float32)CDD_PWM_CFG_DUTYCYCLE_MAX)) * (float32)100);
    outputCh      = ChannelParameter.Output;
    Channel_value = ChannelParameter.Period << 8;

    if ((base >= 0x50000000UL) && (base <= 0x500DF000UL))
    {
        float32 count     = ((dutyFine * (float32)(Channel_value)) / (float32)100);
        uint32  compCount = (uint32)(count);

        /* Enable both outputs epwmxA and epwmxB which is same configuration. */
        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_A == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_A, compCount);
        }

        if (((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_B == outputCh) ||
            ((Cdd_Pwm_OutputChType)CDD_PWM_OUTPUT_CH_BOTH_A_AND_B == outputCh))
        {
            HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_B, compCount);
        }

        /* MEP calibration module continuously updates MEP_ScaleFactor */
        Cdd_Pwm_ChannelSfoStatus[ChannelParameter.ChannelNumber] = Cdd_Pwm_SFO();
    }
}
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_CAL_API) */

#define CDD_PWM_STOP_SEC_CODE
#include "Cdd_Pwm_MemMap.h"

#define CDD_PWM_START_SEC_ISR_CODE
#include "Cdd_Pwm_MemMap.h"

#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
/*******************************************************************************
 *   Function Name : Cdd_Pwm_ChannelNotificationISR
 ******************************************************************************/
/*! \Description: Interrupt Subroutine for Notification
 *
 *  \context    Function is called from interrupt level
 ******************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_ChannelType ChannelNumber)
{
    Cdd_Pwm_NotifyFuncType pwmNotification = (Cdd_Pwm_NotifyFuncType)NULL_PTR;

    /* Get the base addr. */
    uint32 baseAddr;
    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

    if (NULL_PTR != (void *)chObj)
    {
        /* Call Notification */
        if (NULL_PTR != (void *)chObj->notificationHandler)
        {
            pwmNotification = chObj->notificationHandler;
            pwmNotification();
        }
    }

    /* Clear the events. */
    EPWM_clearEventTriggerInterruptFlag(baseAddr);
}
#endif

/*******************************************************************************
 *   Function Name : Cdd_Pwm_ChannelNotificationTzISR
 ******************************************************************************/
/*! \Description: Interrupt Subroutine for Notification
 *
 *  \context    Function is called from interrupt level
 ******************************************************************************/
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_ChannelType ChannelNumber)
{
    Cdd_Pwm_TzNotifyFuncType pwmTzNotification = (Cdd_Pwm_TzNotifyFuncType)NULL_PTR;

    /* Get the base addr. */
    uint32 baseAddr;
    uint16 statusINT;
    uint16 statusCBC;

    baseAddr = Cdd_Pwm_getBaseAddr(ChannelNumber, CDD_PWM_VALID_ID);

    Cdd_Pwm_ChObjType *chObj = &Cdd_Pwm_ChObj[ChannelNumber];

    /* Get the status */
    statusCBC = EPWM_getCycleByCycleTripZoneFlagStatus(baseAddr);
    statusINT = EPWM_getTripZoneFlagStatus(baseAddr);

    if (NULL_PTR != (void *)chObj)
    {
        /* Call Notification */
        if (NULL_PTR != (void *)chObj->notificationTzHandler)
        {
            pwmTzNotification = chObj->notificationTzHandler;
            pwmTzNotification();
        }
    }

    /* Clear the events for CBC trip zone signal */
    if (statusCBC != 0U)
    {
        EPWM_clearCycleByCycleTripZoneFlag(baseAddr, statusCBC);

        if (statusINT != 0U)
        {
            /* Clear the interrupt bit for on-shot/CBC interrupt to detect the furthur interrupts on
             * trip signal */
            EPWM_clearTripZoneFlag(baseAddr, EPWM_TZ_INTERRUPT);
        }
    }
}

#define CDD_PWM_STOP_SEC_ISR_CODE
#include "Cdd_Pwm_MemMap.h"
