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
 *  \file     Cdd_Pwm_Priv.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the CDD_PWM MCAL driver files.
 *
 */

#ifndef CDD_PWM_PRIV_H_
#define CDD_PWM_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Pwm_Cfg.h"
#include "Cdd_Pwm_Types.h"
#define CDD_PWM_START_SEC_CODE
#include "Cdd_Pwm_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#include "hw_epwm.h"  /* Map the static inline functions in this file as well */
#define CDD_PWM_STOP_SEC_CODE
#include "Cdd_Pwm_MemMap.h"
#include "Cdd_Pwm_Sfo.h"

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
#include "Det.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CDD_PWM_ISR_MAX     CDD_PWM_HW_MAX_NUM_CHANNELS
#define CDD_PWM_VALID_ID    0xFFU
#define CDD_PWM_EVENT_COUNT (1U)

/** \brief Max Duty Cycle. */
#define CDD_PWM_CFG_DUTYCYCLE_MAX (CDD_PWM_DUTYCYCLE_MAX)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                         GLOBAL VARIABLES                                   */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_reportDetError(uint8 apiId, uint8 errorId);
#endif /*#if (STD_ON == CDD_PWM_DEV_ERROR_DETECT)*/

void   Cdd_Pwm_resetChObj(Cdd_Pwm_ChObjType *chObj);
void   Cdd_Pwm_copyConfig(Cdd_Pwm_ChObjType *chObj, const Cdd_Pwm_ChannelConfigType *chCfg);
void   Cdd_Epwm_DeInitialize(uint32 epwmbaseadrr);
uint32 Cdd_Pwm_getBaseAddr(Cdd_Pwm_ChannelType ChannelNumber, uint32 Id);
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_HwUnitInit(Cdd_Pwm_ChObjType *chObj);

#if (STD_ON == CDD_PWM_DEINIT_API)
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_IpDeInit_epwm(const Cdd_Pwm_ChObjType *chObj);
#endif /*#if (STD_ON == CDD_PWM_DEINIT_API)*/

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_Start_Private(const Cdd_Pwm_ChObjType *chObj);
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_Stop_Private(const Cdd_Pwm_ChObjType *chObj);
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_configureChannel(uint32 base, const EPWM_SignalParams *signalParams);
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_deconfigureChannel(uint32 base);
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetPinAction_Private(const Cdd_Pwm_ChObjType *chObj, Cdd_Pwm_PinActionType PinAction);
FUNC(Cdd_Pwm_ValueType, CDD_PWM_CODE) Cdd_Pwm_PrivGetCounter(const Cdd_Pwm_ChObjType *chObj);
FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_PrivSetAbsoluteThreshold(const Cdd_Pwm_ChObjType *chObj, Cdd_Pwm_ValueType ReferenceValue,
                                 Cdd_Pwm_ValueType AbsoluteValue);
FUNC(Cdd_Pwm_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_PrivSetReleativeThreshold(const Cdd_Pwm_ChObjType *chObj, Cdd_Pwm_ValueType RelativeValue);

#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetPeriodAndDuty_Deterror(Cdd_Pwm_channelParametertype ChannelParameter);
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SystemSetPeriodAndDuty(Cdd_Pwm_channelParametertype ChannelParameter);
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_SetDutyCycle_Internal(Cdd_Pwm_channelParametertype ChannelParameter);
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_configureSignal(uint32 base, const EPWM_SignalParams *signalParams);
#endif /*#if (STD_ON == CDD_PWM_SET_PERIOD_DUTY_PHASE_API)*/

#if (STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API)
FUNC(Std_ReturnType, CDD_PWM_CODE)
Cdd_Pwm_SetOutputToIdle_Deterror(Cdd_Pwm_ChannelType ChannelNumber);
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_SystemSetOutputToIdle(Cdd_Pwm_ChannelType ChannelNumber);
#endif /*#if (STD_ON == CDD_PWM_SET_OUTPUT_TO_IDLE_API)*/

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_setEmulationMode(uint32 base, EPWM_EmulationMode emulationMode);

FUNC(void, CDD_PWM_CODE) Cdd_Pwm_DisableInterrupt(Cdd_Pwm_ChannelType ChannelNumber);
#if (STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_EnableInterrupt(Cdd_Pwm_ChannelType ChannelParameter, Cdd_Pwm_InterruptType EdgeInterruptSource);
FUNC(void, CDD_PWM_CODE)
CDD_PWM_enableInterrupt_Notification(uint32 baseAddr, Cdd_Pwm_OutputChType outputCh, Cdd_Pwm_PinStateType Pinstate,
                                     Cdd_Pwm_EdgeNotificationType Notification);
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_ChannelNotificationISR_epwm(Cdd_Pwm_ChannelType ChannelNumber);
#endif /*#if(STD_ON == CDD_PWM_NOTIFICATION_SUPPORTED)*/

#if (STD_ON == CDD_PWM_REGISTER_READBACK_API)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_IpRegisterReadback_epwm(uint32 ChannelNumber, Cdd_Pwm_RegisterReadbackType *RegRbPtr);
#endif /*#if (STD_ON == CDD_PWM_REGISTER_READBACK_API)*/

void   Cdd_Pwm_tbSyncEnable(uint32 baseAddr, uint32 tbPhsValue, uint32 counterDir);
void   Cdd_Pwm_tbSyncDisable(uint32 baseAddr);
void   Cdd_Pwm_tbTriggerSwSync(uint32 baseAddr);
uint16 Cdd_Pwm_tbGetStatus(uint32 baseAddr, uint32 tbStatusMask);
void   Cdd_Pwm_tbStatusClear(uint32 baseAddr, uint32 tbStatusClrMask);
uint32 Cdd_Pwm_counterComparatorCfg(uint32 baseAddr, Cdd_Pwm_OutputChType cmpType, uint32 cmpVal,
                                    uint32 enableShadowWrite, uint32 shadowToActiveLoadTrigger, uint32 overwriteShadow);
void   Cdd_Pwm_deadbandCfg(uint32 baseAddr, const CDD_PWM_DeadbandCfgType *pCfg);
void   Cdd_Pwm_deadbandBypass(uint32 baseAddr);
void   Cdd_Pwm_chopperCfg(uint32 baseAddr, const CDD_PWM_ChopperCfgType *pCfg);
void   Cdd_Pwm_chopperEnable(uint32 baseAddr, uint32 enableChopper);
void   Cdd_Pwm_tzTripEventEnable(uint32 baseAddr, uint32 tzEventType);
void   Cdd_Pwm_tzTripEventDisable(uint32 baseAddr, uint32 tzEventType);
void   Cdd_Pwm_tzIntrEnable(uint32 epwmbaseadrr, uint32 tzEventType, Cdd_Pwm_tripZoneType *tripZoneParameter);
void   Cdd_Pwm_tzIntrDisable(uint32 epwmbaseadrr, uint32 tzEventType, Cdd_Pwm_tripZoneType *tripZoneParameter);
uint16 Cdd_Pwm_tzEventStatus(uint32 baseAddr, uint32 eventMask);
void   Cdd_Pwm_tzEventStatusClear(uint32 baseAddr, uint32 eventMask, uint32 Flags);
void   Cdd_Pwm_tzTriggerSwEvent(uint32 baseAddr, uint32 tzEventType);
uint16 Cdd_Pwm_etIntrStatus(uint32 baseAddr);
void   Cdd_Pwm_etIntrClear(uint32 baseAddr);
void   Cdd_Pwm_etIntrTrigger(uint32 baseAddr);
uint16 Cdd_Pwm_etGetEventCount(uint32 baseAddr);
void   Cdd_Pwm_setTimerBase(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_setTimerBaseSync(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_CounterCompare(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_ActionQualifier(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_TripZone(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_DigitalCompare(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_DeadBand(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_Chopper(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_EventTrigger(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_AdcEventTrigger(Cdd_Pwm_ChannelType ChannelNumber);
void   Cdd_Pwm_EnableAdcTrigger(uint32 baseAddr, Cdd_Pwm_AdcSocType adcSoc);
FUNC(void, CDD_PWM_CODE) Cdd_Pwm_ChannelNotificationTzISR(Cdd_Pwm_ChannelType ChannelNumber);
void Cdd_Pwm_DisableTzInt(uint32 baseAddr);

#if (STD_ON == CDD_PWM_HR_SET_HRPWM_API)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_HrSystemSetPeriodAndDuty(Cdd_Pwm_channelParametertype ChannelParameter);
#endif /* #if (STD_ON == CDD_PWM_HR_SET_HRPWM_API) */

#if (STD_ON == CDD_PWM_HR_SFO_CAL_API)
FUNC(void, CDD_PWM_CODE)
Cdd_Pwm_HrSfoCalibration_Private(Cdd_Pwm_channelParametertype ChannelParameter);
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_CAL_API) */

/* Initialize SFO status */
#if (STD_ON == CDD_PWM_HR_SFO_STATUS_API)
void Cdd_Pwm_InitSfoCalStatus(void);
#endif /* #if (STD_ON == CDD_PWM_HR_SFO_STATUS_API) */

void Cdd_Pwm_HighResPwm(Cdd_Pwm_ChannelType ChannelNumber);
#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_PWM_PRIV_H_ */
