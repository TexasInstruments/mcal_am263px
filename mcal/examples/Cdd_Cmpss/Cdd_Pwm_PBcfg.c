/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
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
 *  \file     Cdd_Pwm_PBcfg.c
 *
 *  \brief    CDD PWM PB cfg file
 *
 */

#include "Std_Types.h"
#include "Cdd_Pwm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---- Perform version checking  ----------------------------------------- */
#if ((CDD_PWM_SW_MAJOR_VERSION != (10U)) || (CDD_PWM_SW_MINOR_VERSION != (2U)))
#error "Version numbers of Cdd_Pwm_PBcfg.c and Cdd_Pwm_Cfg.h are inconsistent!"
#endif

#if ((CDD_PWM_CFG_MAJOR_VERSION != (10U)) || (CDD_PWM_CFG_MINOR_VERSION != (2U)))
#error "Version numbers of Cdd_Pwm_PBcfg.c and Cdd_Pwm_Cfg.h are inconsistent!"
#endif

extern void Cdd_Pwm_Notification_Channel(void);
extern void Cdd_Pwm_Tz_Notification_Channel(void);

#define CDD_PWM_START_SEC_CONFIG_DATA
#include "Cdd_Pwm_MemMap.h"

static CONST(struct Cdd_Pwm_timerBaseConfigType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_TimerBaseRef[CDD_PWM_TIMER_BASE_NUM_CHANNELS] = {
    [0U] = {
        .channelPwmTimerBasePeriodGlobalLoad = FALSE,
        .channelPwmEmulationMode             = CDD_PWM_EMULATION_FREE_RUN,
        .channelPwmClockDivider              = CDD_PWM_CLOCK_DIVIDER_1,
        .channelPwmHSClockDivider            = CDD_PWM_HSCLOCK_DIVIDER_1,
        .channelPwmTbPeriod                  = 65535U,
        .channelPwmTbPeriodInitValue         = 0U,
        .channelPwmCounterMode               = CDD_PWM_COUNTER_MODE_UP,
        .channelPwmEnablePhaseShift          = FALSE,
        .channelPwmEnablePhaseShiftValue     = 0U,
        .channelPwmPeriodLoadMode            = CDD_PWM_PERIOD_SHADOW_LOAD,
        .channelPwmTbprdlink                 = CDD_PWM_LINK_DISABLE,
    }};

static CONST(struct Cdd_Pwm_CompareType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_CounterCompareRef[CDD_PWM_COUNTER_NUM_CHANNELS] = {
    [0U] =
        {
            /* Compare A */
            .channelCddPwmCounterBlockA                 = CDD_PWM_CMP_A,
            .channelCddPwmCompareValueCmpA              = 16384U,
            .channelCddPwmCounterCompareGlobalLoadCmpA  = FALSE,
            .channelCddPwmCounterCompareShadowModeCmpA  = FALSE,
            .channelCddPwmCounterCompareShadowEventCmpA = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
            .channelCddPwmTbprdlinkCmpA                 = CDD_PWM_LINK_DISABLE,

            /* Compare B */
            .channelCddPwmCounterBlockB                 = CDD_PWM_CMP_B,
            .channelCddPwmCompareValueCmpB              = 32768U,
            .channelCddPwmCounterCompareGlobalLoadCmpB  = FALSE,
            .channelCddPwmCounterCompareShadowModeCmpB  = FALSE,
            .channelCddPwmCounterCompareShadowEventCmpB = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
            .channelCddPwmTbprdlinkCmpB                 = CDD_PWM_LINK_DISABLE,

            /* Compare C */
            .channelCddPwmCounterBlockC                 = CDD_PWM_CMP_C,
            .channelCddPwmCompareValueCmpC              = 1U,
            .channelCddPwmCounterCompareGlobalLoadCmpC  = FALSE,
            .channelCddPwmCounterCompareShadowModeCmpC  = FALSE,
            .channelCddPwmCounterCompareShadowEventCmpC = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
            .channelCddPwmTbprdlinkCmpC                 = CDD_PWM_LINK_DISABLE,

            /* Compare D */
            .channelCddPwmCounterBlockD                 = CDD_PWM_CMP_D,
            .channelCddPwmCompareValueCmpD              = 1U,
            .channelCddPwmCounterCompareGlobalLoadCmpD  = FALSE,
            .channelCddPwmCounterCompareShadowModeCmpD  = FALSE,
            .channelCddPwmCounterCompareShadowEventCmpD = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
            .channelCddPwmTbprdlinkCmpD                 = CDD_PWM_LINK_DISABLE,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        /* Compare A */
        .channelCddPwmCounterBlockA                 = CDD_PWM_CMP_A,
        .channelCddPwmCompareValueCmpA              = 1U,
        .channelCddPwmCounterCompareGlobalLoadCmpA  = FALSE,
        .channelCddPwmCounterCompareShadowModeCmpA  = FALSE,
        .channelCddPwmCounterCompareShadowEventCmpA = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
        .channelCddPwmTbprdlinkCmpA                 = CDD_PWM_LINK_DISABLE,

        /* Compare B */
        .channelCddPwmCounterBlockB                 = CDD_PWM_CMP_B,
        .channelCddPwmCompareValueCmpB              = 1U,
        .channelCddPwmCounterCompareGlobalLoadCmpB  = FALSE,
        .channelCddPwmCounterCompareShadowModeCmpB  = FALSE,
        .channelCddPwmCounterCompareShadowEventCmpB = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
        .channelCddPwmTbprdlinkCmpB                 = CDD_PWM_LINK_WITH_PWM_2,

        /* Compare C */
        .channelCddPwmCounterBlockC                 = CDD_PWM_CMP_C,
        .channelCddPwmCompareValueCmpC              = 1U,
        .channelCddPwmCounterCompareGlobalLoadCmpC  = FALSE,
        .channelCddPwmCounterCompareShadowModeCmpC  = FALSE,
        .channelCddPwmCounterCompareShadowEventCmpC = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
        .channelCddPwmTbprdlinkCmpC                 = CDD_PWM_LINK_DISABLE,

        /* Compare D */
        .channelCddPwmCounterBlockD                 = CDD_PWM_CMP_D,
        .channelCddPwmCompareValueCmpD              = 1U,
        .channelCddPwmCounterCompareGlobalLoadCmpD  = FALSE,
        .channelCddPwmCounterCompareShadowModeCmpD  = FALSE,
        .channelCddPwmCounterCompareShadowEventCmpD = CDD_PWM_COMP_LOAD_ON_CNTR_ZERO,
        .channelCddPwmTbprdlinkCmpD                 = CDD_PWM_LINK_DISABLE,
    }};

static CONST(struct Cdd_Pwm_TimerBaseSync_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_TimerBaseSyncRef[CDD_PWM_TIMER_BASE_SYNC_NUM_CHANNELS] = {
    [0U] =
        {
            .channelOneShotSyncOutTrigger     = CDD_PWM_OSHT_SYNC_OUT_TRIG_SYNC,
            .channelForceSync                 = FALSE,
            .channelTbprdlink                 = CDD_PWM_LINK_DISABLE,
            .channelSyncOutPulseOnSoftware    = FALSE,
            .channelSyncOutPulseOnCntrZero    = FALSE,
            .channelSyncOutPulseOnCntCmpB     = FALSE,
            .channelSyncOutPulseOnCntCmpC     = FALSE,
            .channelSyncOutPulseOnCntCmpD     = FALSE,
            .channelSyncOutPulseOnDCAEVT1SYNC = FALSE,
            .channelSyncOutPulseOnDCBEVT1SYNC = FALSE,
            .channelSyncOutPulseOnALL         = FALSE,
            .channelSyncOutPulseSource        = CDD_PWM_SYNC_IN_PULSE_SRC_DISABLE,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        .channelOneShotSyncOutTrigger     = CDD_PWM_OSHT_SYNC_OUT_TRIG_SYNC,
        .channelForceSync                 = FALSE,
        .channelTbprdlink                 = CDD_PWM_LINK_DISABLE,
        .channelSyncOutPulseOnSoftware    = FALSE,
        .channelSyncOutPulseOnCntrZero    = FALSE,
        .channelSyncOutPulseOnCntCmpB     = FALSE,
        .channelSyncOutPulseOnCntCmpC     = FALSE,
        .channelSyncOutPulseOnCntCmpD     = FALSE,
        .channelSyncOutPulseOnDCAEVT1SYNC = FALSE,
        .channelSyncOutPulseOnDCBEVT1SYNC = FALSE,
        .channelSyncOutPulseOnALL         = FALSE,
        .channelSyncOutPulseSource        = CDD_PWM_SYNC_IN_PULSE_SRC_DISABLE,
    }};

static CONST(struct Cdd_Pwm_ActionConfigType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_ActionQualifierRef[CDD_PWM_TIMER_AQ_NUM_CHANNELS] = {
    [0U] =
        {
            /* Actions for EPWMA */
            .channelPwmOutptEPWMA                             = CDD_PWM_E_A,
            .channelPwmActionGlobalLoadEPWMA                  = FALSE,
            .channelPwmActionShadowModeEPWMA                  = TRUE,
            .channelPwmActionShadowEventEPWMA                 = CDD_PWM_AQ_LOAD_ON_CNTR_ZERO,
            .channelPwmT1TriggerSourceEPWMA                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
            .channelPwmT2TriggerSourceEPWMA                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
            .channelPwmActionQualifierOneTimeSwOutputEPWMA    = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmActionQualifierContinuousSwOutputEPWMA = CDD_PWM_AQ_SW_DISABLED,
            .channelPwmAqOutputOnTimebaseZEROEPWMA            = CDD_PWM_AQ_OUTPUT_HIGH,
            .channelPwmAqOutputOnTimebasePERIODEPWMA          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnTimebaseUPCMPAEPWMA          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnTimebaseDOWNCMPAEPWMA        = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnTimebaseUPCMPBEPWMA          = CDD_PWM_AQ_OUTPUT_LOW,
            .channelPwmAqOutputOnTimebaseDOWNCMPBEPWMA        = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT1COUNTUPEPWMA               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT1COUNTDOWNEPWMA             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT2COUNTUPEPWMA               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT2COUNTDOWNEPWMA             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,

            /* Actions for EPWMB */
            .channelPwmOutptEPWMB                             = CDD_PWM_E_B,
            .channelPwmActionGlobalLoadEPWMB                  = FALSE,
            .channelPwmActionShadowModeEPWMB                  = TRUE,
            .channelPwmActionShadowEventEPWMB                 = CDD_PWM_AQ_LOAD_ON_CNTR_ZERO,
            .channelPwmT1TriggerSourceEPWMB                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
            .channelPwmT2TriggerSourceEPWMB                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
            .channelPwmActionQualifierOneTimeSwOutputEPWMB    = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmActionQualifierContinuousSwOutputEPWMB = CDD_PWM_AQ_SW_DISABLED,
            .channelPwmAqOutputOnTimebaseZEROEPWMB            = CDD_PWM_AQ_OUTPUT_LOW,
            .channelPwmAqOutputOnTimebasePERIODEPWMB          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnTimebaseUPCMPAEPWMB          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnTimebaseDOWNCMPAEPWMB        = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnTimebaseUPCMPBEPWMB          = CDD_PWM_AQ_OUTPUT_HIGH,
            .channelPwmAqOutputOnTimebaseDOWNCMPBEPWMB        = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT1COUNTUPEPWMB               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT1COUNTDOWNEPWMB             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT2COUNTUPEPWMB               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
            .channelPwmAqOutputOnT2COUNTDOWNEPWMB             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        /* Actions for EPWMA */
        .channelPwmOutptEPWMA                             = CDD_PWM_E_A,
        .channelPwmActionGlobalLoadEPWMA                  = FALSE,
        .channelPwmActionShadowModeEPWMA                  = FALSE,
        .channelPwmActionShadowEventEPWMA                 = CDD_PWM_AQ_LOAD_ON_CNTR_ZERO,
        .channelPwmT1TriggerSourceEPWMA                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
        .channelPwmT2TriggerSourceEPWMA                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
        .channelPwmActionQualifierOneTimeSwOutputEPWMA    = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmActionQualifierContinuousSwOutputEPWMA = CDD_PWM_AQ_SW_DISABLED,
        .channelPwmAqOutputOnTimebaseZEROEPWMA            = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebasePERIODEPWMA          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebaseUPCMPAEPWMA          = CDD_PWM_AQ_OUTPUT_HIGH,
        .channelPwmAqOutputOnTimebaseDOWNCMPAEPWMA        = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebaseUPCMPBEPWMA          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebaseDOWNCMPBEPWMA        = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnT1COUNTUPEPWMA               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnT1COUNTDOWNEPWMA             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnT2COUNTUPEPWMA               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnT2COUNTDOWNEPWMA             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,

        /* Actions for EPWMB */
        .channelPwmOutptEPWMB                             = CDD_PWM_E_B,
        .channelPwmActionGlobalLoadEPWMB                  = FALSE,
        .channelPwmActionShadowModeEPWMB                  = FALSE,
        .channelPwmActionShadowEventEPWMB                 = CDD_PWM_AQ_LOAD_ON_CNTR_ZERO,
        .channelPwmT1TriggerSourceEPWMB                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
        .channelPwmT2TriggerSourceEPWMB                   = CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1,
        .channelPwmActionQualifierOneTimeSwOutputEPWMB    = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmActionQualifierContinuousSwOutputEPWMB = CDD_PWM_AQ_SW_DISABLED,
        .channelPwmAqOutputOnTimebaseZEROEPWMB            = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebasePERIODEPWMB          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebaseUPCMPAEPWMB          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebaseDOWNCMPAEPWMB        = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebaseUPCMPBEPWMB          = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnTimebaseDOWNCMPBEPWMB        = CDD_PWM_AQ_OUTPUT_LOW,
        .channelPwmAqOutputOnT1COUNTUPEPWMB               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnT1COUNTDOWNEPWMB             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnT2COUNTUPEPWMB               = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
        .channelPwmAqOutputOnT2COUNTDOWNEPWMB             = CDD_PWM_AQ_OUTPUT_NO_CHANGE,
    }};

static CONST(struct Cdd_Pwm_EventConfigType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_EventTriggerRef[CDD_PWM_TIMER_EVENT_NUM_CHANNELS] = {
    [0U] =
        {
            .channelPwmForceEventValue              = FALSE,
            .channelPwmEnableEventCountInitialValue = FALSE,
            .channelPwmEventCountInitialValue       = 1U,
            .channelPwmInterruptCount               = 1U,
            .channelPwmInterruptEventSources        = CDD_PWM_INT_TBCTR_ZERO,
            .channelPwmInterruptMixedSources        = 0U,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        .channelPwmForceEventValue              = FALSE,
        .channelPwmEnableEventCountInitialValue = FALSE,
        .channelPwmEventCountInitialValue       = 1U,
        .channelPwmInterruptCount               = 1U,
        .channelPwmInterruptEventSources        = CDD_PWM_INT_TBCTR_ZERO,
        .channelPwmInterruptMixedSources        = 0U,
    }};

static CONST(struct Cdd_Pwm_AdcEventTriggerType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_AdcEventTriggerRefSoc[CDD_PWM_TIMER_ADC_EVENT_NUM_CHANNELS] = {
    [0U] =
        {
            /* SOC A Event for ADC */
            .channelPwmSocAEvent                        = FALSE,
            .channelPwmSocAForceEventValue              = FALSE,
            .channelPwmSocAEventCountInitialValueEnable = FALSE,
            .channelPwmSocAEventCountInitialValue       = 0U,
            .channelPwmSocAInterruptCount               = 0U,
            .channelPwmSocAInterruptEventSources        = CDD_PWM_SOC_DCxEVT1,
            .channelPwmSocAMixedSources                 = 0U,

            /* SOC B Event for ADC */
            .channelPwmSocBEvent                        = FALSE,
            .channelPwmSocBForceEventValue              = FALSE,
            .channelPwmSocBEventCountInitialValueEnable = FALSE,
            .channelPwmSocBEventCountInitialValue       = 0U,
            .channelPwmSocBInterruptCount               = 0U,
            .channelPwmSocBInterruptEventSources        = CDD_PWM_SOC_DCxEVT1,
            .channelPwmSocBMixedSources                 = 0U,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in
       pwm demo config */
    [1U] = {
        /* SOC A Event for ADC */
        .channelPwmSocAEvent                        = FALSE,
        .channelPwmSocAForceEventValue              = FALSE,
        .channelPwmSocAEventCountInitialValueEnable = FALSE,
        .channelPwmSocAEventCountInitialValue       = 1U,
        .channelPwmSocAInterruptCount               = 1U,
        .channelPwmSocAInterruptEventSources        = CDD_PWM_SOC_TBCTR_ZERO,
        .channelPwmSocAMixedSources                 = 0U,

        /* SOC B Event for ADC */
        .channelPwmSocBEvent                        = FALSE,
        .channelPwmSocBForceEventValue              = FALSE,
        .channelPwmSocBEventCountInitialValueEnable = FALSE,
        .channelPwmSocBEventCountInitialValue       = 1U,
        .channelPwmSocBInterruptCount               = 1U,
        .channelPwmSocBInterruptEventSources        = CDD_PWM_SOC_DCxEVT1,
        .channelPwmSocBMixedSources                 = 0U,
    }};

static CONST(struct Cdd_Pwm_TripZoneType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_TripZoneRef[CDD_PWM_TIMER_TRIP_ZONE_NUM_CHANNELS] = {
    [0U] =
        {
            .channelPwmAdvancedTripZoneAction        = FALSE,
            .channelPwmEvent                         = CDD_PWM_HIGH_STATE,
            .channelPwmTZAEvent                      = CDD_PWM_HZ_STATE,
            .channelPwmTZBEvent                      = CDD_PWM_HIGH_STATE,
            .channelPwmTZAAdvUEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmTZAAdvDEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmTZBAdvUEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmTZBAdvDEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCAEVT1Event                  = CDD_PWM_HZ_STATE,
            .channelPwmDCAEVT1AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCAEVT1AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCAEVT2Event                  = CDD_PWM_HZ_STATE,
            .channelPwmDCAEVT2AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCAEVT2AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCBEVT1Event                  = CDD_PWM_HZ_STATE,
            .channelPwmDCBEVT1AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCBEVT1AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCBEVT2Event                  = CDD_PWM_HZ_STATE,
            .channelPwmDCBEVT2AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmDCBEVT2AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
            .channelPwmOneShotTZ1                    = FALSE,
            .channelPwmOneShotTZ2                    = FALSE,
            .channelPwmOneShotTZ3                    = FALSE,
            .channelPwmOneShotTZ4                    = FALSE,
            .channelPwmOneShotTZ5                    = FALSE,
            .channelPwmOneShotTZ6                    = FALSE,
            .channelPwmOneShotDCAEVT1                = FALSE,
            .channelPwmOneShotDCBEVT1                = TRUE,
            .channelPwmCBCTZ1                        = FALSE,
            .channelPwmCBCTZ2                        = FALSE,
            .channelPwmCBCTZ3                        = FALSE,
            .channelPwmCBCTZ4                        = FALSE,
            .channelPwmCBCTZ5                        = FALSE,
            .channelPwmCBCTZ6                        = FALSE,
            .channelPwmDCAEVT2                       = FALSE,
            .channelPwmDCBEVT2                       = FALSE,
            .channelPwmTZCBCInterrupt                = TRUE,
            .channelPwmTZOneShotInterrupt            = TRUE,
            .channelPwmDCAEVT1Interrupt              = FALSE,
            .channelPwmDCAEVT2Interrupt              = FALSE,
            .channelPwmDCBEVT1Interrupt              = FALSE,
            .channelPwmDCBEVT2Interrupt              = FALSE,
            .channelPwmCycleByCycleTripZoneClearMode = CDD_PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        .channelPwmAdvancedTripZoneAction        = FALSE,
        .channelPwmEvent                         = CDD_PWM_HZ_STATE,
        .channelPwmTZAEvent                      = CDD_PWM_HZ_STATE,
        .channelPwmTZBEvent                      = CDD_PWM_HZ_STATE,
        .channelPwmTZAAdvUEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmTZAAdvDEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmTZBAdvUEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmTZBAdvDEvent                  = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCAEVT1Event                  = CDD_PWM_HZ_STATE,
        .channelPwmDCAEVT1AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCAEVT1AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCAEVT2Event                  = CDD_PWM_HZ_STATE,
        .channelPwmDCAEVT2AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCAEVT2AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCBEVT1Event                  = CDD_PWM_HZ_STATE,
        .channelPwmDCBEVT1AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCBEVT1AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCBEVT2Event                  = CDD_PWM_HZ_STATE,
        .channelPwmDCBEVT2AdvUEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmDCBEVT2AdvDEvent              = CDD_PWM_TZ_ADV_ACTION_HIGH_Z,
        .channelPwmOneShotTZ1                    = FALSE,
        .channelPwmOneShotTZ2                    = FALSE,
        .channelPwmOneShotTZ3                    = FALSE,
        .channelPwmOneShotTZ4                    = FALSE,
        .channelPwmOneShotTZ5                    = FALSE,
        .channelPwmOneShotTZ6                    = FALSE,
        .channelPwmOneShotDCAEVT1                = FALSE,
        .channelPwmOneShotDCBEVT1                = FALSE,
        .channelPwmCBCTZ1                        = FALSE,
        .channelPwmCBCTZ2                        = FALSE,
        .channelPwmCBCTZ3                        = FALSE,
        .channelPwmCBCTZ4                        = FALSE,
        .channelPwmCBCTZ5                        = FALSE,
        .channelPwmCBCTZ6                        = FALSE,
        .channelPwmDCAEVT2                       = FALSE,
        .channelPwmDCBEVT2                       = FALSE,
        .channelPwmTZCBCInterrupt                = FALSE,
        .channelPwmTZOneShotInterrupt            = FALSE,
        .channelPwmDCAEVT1Interrupt              = FALSE,
        .channelPwmDCAEVT2Interrupt              = FALSE,
        .channelPwmDCBEVT1Interrupt              = FALSE,
        .channelPwmDCBEVT2Interrupt              = FALSE,
        .channelPwmCycleByCycleTripZoneClearMode = CDD_PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO,
    }};

static CONST(struct Cdd_Pwm_DigitalCompareType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_DigitalCompareRef[CDD_PWM_DIGITAL_COMPARE_NUM_CHANNELS] = {
    [0U] = {
        .channelPwmDCAHigh                          = EPWM_DC_TRIP_TRIPIN1,
        .channelPwmDCALow                           = EPWM_DC_TRIP_TRIPIN1,
        .channelPwmDCAOutputHigh1A                  = EPWM_TZ_EVENT_DC_DISABLED,
        .channelPwmDCAOutputHigh2A                  = EPWM_TZ_EVENT_DC_DISABLED,
        .channelPwmAdcSocEventA                     = FALSE,
        .channelPwmSyncOutEventA                    = FALSE,
        .channelPwmSyncModeAEVT1                    = EPWM_DC_EVENT_INPUT_SYNCED,
        .channelPwmSignalSoureAEVT1                 = EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL,
        .channelPwmCBCLatchModeDCAEVT1              = EPWM_DC_CBC_LATCH_DISABLED,
        .channelPwmCBCLatchClearModeDCAEVT1         = EPWM_DC_CBC_LATCH_CLR_CNTR_ZERO,
        .channelPwmSyncModeAEVT2                    = EPWM_DC_EVENT_INPUT_SYNCED,
        .channelPwmSignalSoureAEVT2                 = EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL,
        .channelPwmCBCLatchModeDCAEVT2              = EPWM_DC_CBC_LATCH_DISABLED,
        .channelPwmCBCLatchClearModeDCAEVT2         = EPWM_DC_CBC_LATCH_CLR_CNTR_ZERO,
        .channelPwmDCBHigh                          = EPWM_DC_TRIP_TRIPIN4, /* CMPSSA1_CTRIPH -> PWM XBAR output 3 */
        .channelPwmDCBLow                           = EPWM_DC_TRIP_TRIPIN1,
        .channelPwmDCBOutputHigh1A                  = EPWM_TZ_EVENT_DCXH_HIGH,
        .channelPwmDCBOutputHigh2A                  = EPWM_TZ_EVENT_DC_DISABLED,
        .channelPwmAdcSocEventB                     = FALSE,
        .channelPwmSyncOutEventB                    = FALSE,
        .channelPwmSyncModeBEVT1                    = EPWM_DC_EVENT_INPUT_SYNCED,
        .channelPwmSignalSoureBEVT1                 = EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL,
        .channelPwmCBCLatchModeDCBEVT1              = EPWM_DC_CBC_LATCH_DISABLED,
        .channelPwmCBCLatchClearModeDCBEVT1         = EPWM_DC_CBC_LATCH_CLR_CNTR_ZERO,
        .channelPwmSyncModeBEVT2                    = EPWM_DC_EVENT_INPUT_SYNCED,
        .channelPwmSignalSoureBEVT2                 = EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL,
        .channelPwmCBCLatchModeDCBEVT2              = EPWM_DC_CBC_LATCH_DISABLED,
        .channelPwmCBCLatchClearModeDCBEVT2         = EPWM_DC_CBC_LATCH_CLR_CNTR_ZERO,
        .channelPwmCddPwmBlankingWindow             = TRUE,
        .channelPwmDcFilterInputEventSource         = EPWM_DC_WINDOW_SOURCE_DCBEVT1,
        .channelPwmCddPwmBlankingWindowStartEvent   = EPWM_DC_WINDOW_START_TBCTR_BLANK_PULSE_MIX,
        .channelPwmCddPwmBlankingWindowOffset       = 0,
        .channelPwmCddPwmBlankingWindowLength       = 0,
        .channelPwmCddPwmBlankingWindowMixedEvent   = EPWM_DC_TBCTR_ZERO,
        .channelPwmCddPwmDCCounterCapture           = TRUE,
        .channelPwmCddPwmDCCounterCaptureShadowMode = TRUE,
        .channelPwmCddPwmUseEdgeFilter              = TRUE,
        .channelPwmCddPwmEdgeFilterMode             = EPWM_DC_EDGEFILT_MODE_RISING,
        .channelPwmCddPwmEdgeFilterCount            = EPWM_DC_EDGEFILT_EDGECNT_0,
        .channelPwmCddPwmEdgeFilterValleyCapture    = TRUE,
        .channelPwmDelayedOutputEdgeFilter          = TRUE,
        .channelPwmEdgeFilterCounterCaptureSignal   = EPWM_VALLEY_TRIGGER_EVENT_SOFTWARE,
        .channelPwmStartValleyCaptureLogic          = TRUE,
        .channelPwmStartValleyCapture               = Events_0,
        .channelPwmStopValleyCapture                = Events_0,
        .channelPwmSoftwareValleyDelayValue         = 0,
        .channelPwmValleyDelayDivider               = EPWM_VALLEY_DELAY_MODE_SW_DELAY,
    }};

static CONST(struct Cdd_Pwm_DeadBandType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_DeadBandRef[CDD_PWM_TIMER_DEAD_BAND_NUM_CHANNELS] = {
    [0U] =
        {
            .channelDeadBandClockMode     = CDD_PWM_DB_COUNTER_CLOCK_FULL_CYCLE,
            .channelDeadBandGlobalLoad    = FALSE,
            .channelDeadBandShadowMode    = FALSE,
            .channelRedGlobalLoad         = FALSE,
            .channelRedShadowMode         = FALSE,
            .channelFedGlobalLoad         = FALSE,
            .channelFedShadowMode         = FALSE,
            .channelREDEnable             = FALSE,
            .channelFEDEnable             = FALSE,
            .channelREDDelayValue         = 0U,
            .channelFEDDelayValue         = 0U,
            .channelDeadBandSwapOutputA   = FALSE,
            .channelDeadBandSwapOutputB   = FALSE,
            .channelDeadBandDelayLoadMode = CDD_PWM_RED_LOAD_ON_CNTR_ZERO,
            .channelPwmRedDelayLoadMode   = CDD_PWM_RED_LOAD_ON_CNTR_ZERO,
            .channelPwmFedDelayLoadMode   = CDD_PWM_RED_LOAD_ON_CNTR_ZERO,
            .channelPwmRedBandPolarity    = CDD_PWM_DB_POLARITY_ACTIVE_HIGH,
            .channelPwmFedBandPolarity    = CDD_PWM_DB_POLARITY_ACTIVE_HIGH,
            .channelPwmREDDelayInput      = CDD_PWM_DB_INPUT_EPWMA,
            .channelPwmFEDDelayInput      = CDD_PWM_DB_INPUT_EPWMA,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        .channelDeadBandClockMode     = CDD_PWM_DB_COUNTER_CLOCK_FULL_CYCLE,
        .channelDeadBandGlobalLoad    = FALSE,
        .channelDeadBandShadowMode    = FALSE,
        .channelRedGlobalLoad         = FALSE,
        .channelRedShadowMode         = FALSE,
        .channelFedGlobalLoad         = FALSE,
        .channelFedShadowMode         = FALSE,
        .channelREDEnable             = FALSE,
        .channelFEDEnable             = FALSE,
        .channelREDDelayValue         = 1U,
        .channelFEDDelayValue         = 1U,
        .channelDeadBandSwapOutputA   = FALSE,
        .channelDeadBandSwapOutputB   = FALSE,
        .channelDeadBandDelayLoadMode = CDD_PWM_RED_LOAD_ON_CNTR_ZERO,
        .channelPwmRedDelayLoadMode   = CDD_PWM_RED_LOAD_ON_CNTR_ZERO,
        .channelPwmFedDelayLoadMode   = CDD_PWM_RED_LOAD_ON_CNTR_ZERO,
        .channelPwmRedBandPolarity    = CDD_PWM_DB_POLARITY_ACTIVE_HIGH,
        .channelPwmFedBandPolarity    = CDD_PWM_DB_POLARITY_ACTIVE_HIGH,
        .channelPwmREDDelayInput      = CDD_PWM_DB_INPUT_EPWMA,
        .channelPwmFEDDelayInput      = CDD_PWM_DB_INPUT_EPWMA,
    }};

static CONST(struct Cdd_Pwm_ChopperType_s,
             CDD_PWM_CONFIG_DATA) Cdd_Pwm_ChopperRef[CDD_PWM_TIMER_CHOPPER_NUM_CHANNELS] = {
    [0U] =
        {
            .channelChopperEnable          = FALSE,
            .channelChopperDuty            = 0U,
            .channelChopperFreqency        = 0U,
            .channelChopperFirstPulseWidth = 0U,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        .channelChopperEnable          = FALSE,
        .channelChopperDuty            = 0U,
        .channelChopperFreqency        = 0U,
        .channelChopperFirstPulseWidth = 0U,
    }};

static CONST(struct Cdd_Pwm_HrPwmType_s, CDD_PWM_CONFIG_DATA) Cdd_Pwm_HrPwmRef[CDD_PWM_TIMER_HRPWM_NUM_CHANNELS] = {
    [0U] =
        {
            .channelHrPwmEnable              = TRUE,
            .channelAutoHRMStepScalingEnable = TRUE,
            .channelHrCtrlModeEPWMA          = HRPWM_MEP_DUTY_PERIOD_CTRL,
            .channelHrCtrlModeEPWMB          = HRPWM_MEP_DUTY_PERIOD_CTRL,

            /* PWM Duty, Period and Phase control */
            .channelHrSelEdgeModeEPWMA     = HRPWM_MEP_CTRL_DISABLE,
            .channelHrCmpHRPWMA            = 0U,
            .channelHrShadowActiveLoadPwmA = HRPWM_LOAD_ON_CNTR_ZERO,

            .channelHrSelEdgeModeEPWMB     = HRPWM_MEP_CTRL_DISABLE,
            .channelHrCmpHRPWMB            = 0U,
            .channelHrShadowActiveLoadPwmB = HRPWM_LOAD_ON_CNTR_ZERO,

            .channelHrPeriodCtrlEnable = TRUE,
            .channelHrPeriod           = 0U,

            .channelHrPhaseCtrlEnable = TRUE,
            .channelHrPhase           = 0U,
            .channelPwmSyncSelect     = HRPWM_PWMSYNC_SOURCE_ZERO,

            /* PWM Deadband Control */
            .channelHrDeadbandEdgeMode      = HRPWM_DB_MEP_CTRL_DISABLE,
            .channelHrRisEdgeDelay          = 0U,
            .channelHrDbRisShadowActiveLoad = HRPWM_LOAD_ON_CNTR_ZERO,

            .channelHrFalEdgeDelay          = 0U,
            .channelHrDbFalShadowActiveLoad = HRPWM_LOAD_ON_CNTR_ZERO,

            .channelHrSwapOutputCtrl = TRUE,
            .channelHrOutputCtrl     = HRPWM_OUTPUT_ON_B_NORMAL,
        },
    /* Not used in CMPSS application - initialized just to make the size same as what is used in pwm
       demo config */
    [1U] = {
        .channelHrPwmEnable              = TRUE,
        .channelAutoHRMStepScalingEnable = TRUE,
        .channelHrCtrlModeEPWMA          = HRPWM_MEP_DUTY_PERIOD_CTRL,
        .channelHrCtrlModeEPWMB          = HRPWM_MEP_DUTY_PERIOD_CTRL,

        /* PWM Duty, Period and Phase control */
        .channelHrSelEdgeModeEPWMA     = HRPWM_MEP_CTRL_DISABLE,
        .channelHrCmpHRPWMA            = 0U,
        .channelHrShadowActiveLoadPwmA = HRPWM_LOAD_ON_CNTR_ZERO,

        .channelHrSelEdgeModeEPWMB     = HRPWM_MEP_CTRL_DISABLE,
        .channelHrCmpHRPWMB            = 0U,
        .channelHrShadowActiveLoadPwmB = HRPWM_LOAD_ON_CNTR_ZERO,

        .channelHrPeriodCtrlEnable = TRUE,
        .channelHrPeriod           = 0U,

        .channelHrPhaseCtrlEnable = TRUE,
        .channelHrPhase           = 0U,
        .channelPwmSyncSelect     = HRPWM_PWMSYNC_SOURCE_ZERO,

        /* PWM Deadband Control */
        .channelHrDeadbandEdgeMode      = HRPWM_DB_MEP_CTRL_DISABLE,
        .channelHrRisEdgeDelay          = 0U,
        .channelHrDbRisShadowActiveLoad = HRPWM_LOAD_ON_CNTR_ZERO,

        .channelHrFalEdgeDelay          = 0U,
        .channelHrDbFalShadowActiveLoad = HRPWM_LOAD_ON_CNTR_ZERO,

        .channelHrSwapOutputCtrl = TRUE,
        .channelHrOutputCtrl     = HRPWM_OUTPUT_ON_B_NORMAL,
    }};

/* Cdd_Pwm Channel Configuration parameters */
CONST(Cdd_Pwm_ConfigType, CDD_PWM_CONFIG_DATA)
Cdd_Pwm_Config = {.chCfg = {[0U] =
                                {
                                    .notificationHandler    = (Cdd_Pwm_NotifyFuncType)Cdd_Pwm_Notification_Channel,
                                    .notificationTzHandler  = (Cdd_Pwm_TzNotifyFuncType)Cdd_Pwm_Tz_Notification_Channel,
                                    .baseaddr               = 0x50000000U,
                                    .channelID              = 0U,
                                    .channelHwID            = CDD_PWM_G0_CHANNEL_0,
                                    .outputCh               = CDD_PWM_OUTPUT_CH_A,
                                    .polarity               = CDD_PWM_HIGH,
                                    .channelTimerBase       = &Cdd_Pwm_TimerBaseRef[0U],
                                    .channelCounterCompare  = &Cdd_Pwm_CounterCompareRef[0U],
                                    .channelTimerBaseSync   = &Cdd_Pwm_TimerBaseSyncRef[0U],
                                    .channelActionQualifier = &Cdd_Pwm_ActionQualifierRef[0U],
                                    .channelEventTrigger    = &Cdd_Pwm_EventTriggerRef[0U],
                                    .channelAdcEventTrigger = &Cdd_Pwm_AdcEventTriggerRefSoc[0U],
                                    .channelTripZone        = &Cdd_Pwm_TripZoneRef[0U],
                                    .channelDigitalCompare  = &Cdd_Pwm_DigitalCompareRef[0U],
                                    .channelDeadBand        = &Cdd_Pwm_DeadBandRef[0U],
                                    .channelChopper         = &Cdd_Pwm_ChopperRef[0U],
                                    .channelHrPwm           = &Cdd_Pwm_HrPwmRef[0U],
                                },
                            /* Not used in CMPSS application - initialized just to make the size same as what is used in
                               pwm demo config */
                            [1U] = {
                                .notificationHandler    = (Cdd_Pwm_NotifyFuncType)NULL_PTR,
                                .notificationTzHandler  = (Cdd_Pwm_TzNotifyFuncType)NULL_PTR,
                                .baseaddr               = 0x50001000U,
                                .channelID              = 1U,
                                .channelHwID            = CDD_PWM_G0_CHANNEL_1,
                                .outputCh               = CDD_PWM_OUTPUT_CH_A,
                                .polarity               = CDD_PWM_HIGH,
                                .channelTimerBase       = &Cdd_Pwm_TimerBaseRef[0U],
                                .channelCounterCompare  = &Cdd_Pwm_CounterCompareRef[0U],
                                .channelTimerBaseSync   = &Cdd_Pwm_TimerBaseSyncRef[0U],
                                .channelActionQualifier = &Cdd_Pwm_ActionQualifierRef[0U],
                                .channelEventTrigger    = &Cdd_Pwm_EventTriggerRef[0U],
                                .channelAdcEventTrigger = &Cdd_Pwm_AdcEventTriggerRefSoc[0U],
                                .channelTripZone        = &Cdd_Pwm_TripZoneRef[0U],
                                .channelDigitalCompare  = &Cdd_Pwm_DigitalCompareRef[0U],
                                .channelDeadBand        = &Cdd_Pwm_DeadBandRef[0U],
                                .channelChopper         = &Cdd_Pwm_ChopperRef[0U],
                                .channelHrPwm           = &Cdd_Pwm_HrPwmRef[0U],
                            }}};

#ifdef __cplusplus
}
#endif

#define CDD_PWM_STOP_SEC_CONFIG_DATA
#include "Cdd_Pwm_MemMap.h"
