/*
 * Copyright (C) 2022 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \defgroup DRV_ECAP_MODULE APIs for ECAP
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the ECAP module.
 *
 *  @{
 */

/**
 *  \file v2/ecap.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for ECAP. It also contains some
 *              related macro definitions and some files to be included.
 */

#ifndef ECAP_H_
#define ECAP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "hw_icu.h"
#include "hw_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 *  \anchor Ecap_OperMode_t
 *  \name ECAP Operating Mode
 *  @{
 */
/** \brief Capture Mode */
#define ECAP_CAPTURE_MODE (0U)
/** \brief Auxiliary PWM Mode */
#define ECAP_APWM_MODE (1U)
/** @} */

/**
 *  \anchor Ecap_CaptEvt_t
 *  \name ECAP time stamp capture on event
 *  @{
 */
/** \brief Time stamp capture on event 1 */
#define ECAP_CAPTURE_EVENT_1 ((uint16)0x08U)
/** \brief Time stamp capture on event 2 */
#define ECAP_CAPTURE_EVENT_2 ((uint16)0x0cU)
/** \brief Time stamp capture on event 3 */
#define ECAP_CAPTURE_EVENT_3 ((uint16)0x10U)
/** \brief Time stamp capture on event 4 */
#define ECAP_CAPTURE_EVENT_4 ((uint16)0x14U)
/** @} */

/**
 *  \anchor Ecap_StopCaptEvt_t
 *  \name ECAP stop capture on event
 *  @{
 */
/** \brief Stop capture after event 1 */
#define ECAP_CAPTURE_EVENT1_STOP ((uint32)0x00U)
/** \brief Stop capture after event 2 */
#define ECAP_CAPTURE_EVENT2_STOP ((uint32)0x01U)
/** \brief Stop capture after event 3 */
#define ECAP_CAPTURE_EVENT3_STOP ((uint32)0x02U)
/** \brief Stop capture after event 4 */
#define ECAP_CAPTURE_EVENT4_STOP ((uint32)0x03U)
/** @} */

/**
 *  \anchor Ecap_APWMPolarityConfig_t
 *  \name ECAP APWM Output Polarity
 *  @{
 */
/** \brief Output Polarity HIGH */
#define ECAP_APWM_ACTIVE_HIGH (0U)
/** \brief Output Polarity LOW */
#define ECAP_APWM_ACTIVE_LOW (1U)
/** @} */

/**
 *  \anchor Ecap_CounterMode_t
 *  \name ECAP Counter Mode
 *  @{
 */
/** \brief Counter Mode Stop */
#define ECAP_COUNTER_STOP (0U)
/** \brief Counter Mode Free Running */
#define ECAP_COUNTER_FREE_RUNNING (1U)
/** @} */

/**
 *  \anchor Ecap_CounterSyncInMode_t
 *  \name ECAP Counter SyncIn Mode
 *  @{
 */
/** \brief Disable SyncIn option */
#define ECAP_SYNC_IN_DISABLE ((uint32)0U)
/** \brief Enable Counter to be loaded from the ECAP_CNTPHS register upon
 *  SYNCI signal */
#define ECAP_ENABLE_COUNTER ((uint32)1U)
/** @} */

/**
 *  \anchor Ecap_CounterSyncOutMode_t
 *  \name ECAP Counter SyncOut Mode
 *  @{
 */
/** \brief Select SyncIn event to be the SyncOut signal */
#define ECAP_SYNC_IN ((uint32)0x0U)
/** \brief Select PRD event to be the SyncOut signal */
#define ECAP_PRD_EQ ((uint32)0x1U)
/** \brief Disable SyncOut Signal */
#define ECAP_SYNC_OUT_DISABLE ((uint32)0x2U)
/** @} */

/**
 *  \anchor Ecap_IntrSrc_t
 *  \name ECAP Interrupt Sources
 *  @{
 */
/** \brief Capture Event 1 Interrupt Enable */
#define ECAP_CEVT1_INT (CSL_ECAP_ECEINT_ECFLG_CEVT1_MASK)
/** \brief Capture Event 2 Interrupt Enable */
#define ECAP_CEVT2_INT (CSL_ECAP_ECEINT_ECFLG_CEVT2_MASK)
/** \brief Capture Event 3 Interrupt Enable */
#define ECAP_CEVT3_INT (CSL_ECAP_ECEINT_ECFLG_CEVT3_MASK)
/** \brief Capture Event 4 Interrupt Enable */
#define ECAP_CEVT4_INT (CSL_ECAP_ECEINT_ECFLG_CEVT4_MASK)
/** \brief Counter Overflow Interrupt Enable */
#define ECAP_CNTOVF_INT (CSL_ECAP_ECEINT_ECFLG_CTROVF_MASK)
/** \brief Period Equal Interrupt Enable */
#define ECAP_PRDEQ_INT (CSL_ECAP_ECEINT_ECFLG_CTR_EQ_PRD_MASK)
/** \brief Compare Equal Interrupt Enable */
#define ECAP_CMPEQ_INT (CSL_ECAP_ECEINT_ECFLG_CTR_EQ_CMP_MASK)
/** @} */

typedef enum
{
    //! TSCTR is stopped on emulation suspension
    ECAP_EMULATION_STOP = 0x0U,
    //! TSCTR runs until 0 before stopping on emulation suspension
    ECAP_EMULATION_RUN_TO_ZERO = 0x1U,
    //! TSCTR is not affected by emulation suspension
    ECAP_EMULATION_FREE_RUN = 0x2U
} ECAP_EmulationMode;

typedef enum
{
    //! Disable Sync-in
    ECAP_SYNC_IN_PULSE_SRC_DISABLE = 0x0,
    //! Sync-in source is EPWM0 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM0 = 0x1,
    //! Sync-in source is EPWM1 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1 = 0x2,
    //! Sync-in source is EPWM2 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2 = 0x3,
    //! Sync-in source is EPWM3 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM3 = 0x4,
    //! Sync-in source is EPWM4 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4 = 0x5,
    //! Sync-in source is EPWM5 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM5 = 0x6,
    //! Sync-in source is EPWM6 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM6 = 0x7,
    //! Sync-in source is EPWM7 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM7 = 0x8,
    //! Sync-in source is EPWM8 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8 = 0x9,
    //! Sync-in source is EPWM9 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM9 = 0xA,
    //! Sync-in source is EPWM10 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM10 = 0xB,
    //! Sync-in source is EPWM11 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM11 = 0xC,
    //! Sync-in source is EPWM12 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM12 = 0xD,
    //! Sync-in source is EPWM13 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM13 = 0xE,
    //! Sync-in source is EPWM14 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM14 = 0xF,
    //! Sync-in source is EPWM15 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM15 = 0x10,
    //! Sync-in source is EPWM16 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM16 = 0x11,
    //! Sync-in source is EPWM17 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM17 = 0x12,
    //! Sync-in source is EPWM18 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM18 = 0x13,
    //! Sync-in source is EPWM19 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM19 = 0x14,
    //! Sync-in source is EPWM20 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM20 = 0x15,
    //! Sync-in source is EPWM21 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM21 = 0x16,
    //! Sync-in source is EPWM22 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM22 = 0x17,
    //! Sync-in source is EPWM23 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM23 = 0x18,
    //! Sync-in source is EPWM24 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM24 = 0x19,
    //! Sync-in source is EPWM25 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM25 = 0x1A,
    //! Sync-in source is EPWM26 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM26 = 0x1B,
    //! Sync-in source is EPWM27 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM27 = 0x1C,
    //! Sync-in source is EPWM28 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM28 = 0x1D,
    //! Sync-in source is EPWM29 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM29 = 0x1E,
    //! Sync-in source is EPWM30 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM30 = 0x1F,
    //! Sync-in source is EPWM31 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM31 = 0x20,
} ECAP_SyncInPulseSource;
/**
 *  \anchor Ecap_GlobalIntrSrcClear_t
 *  \name ECAP Global Interrupt Source
 *  @{
 */
/** \brief Global Interrupt Source Clear Flag */
#define ECAP_GLOBAL_INT (ECAP_ECFLG_INT)
/** @} */

/**
 *  \anchor Ecap_CaptureEvtPolarityConfig_t
 *  \name ECAP Capture Event Polarity
 *  @{
 */
/** \brief Capture Event Rising Edge */
#define ECAP_CAPTURE_EVENT_RISING (0U)
/** \brief Capture Event Falling Edge */
#define ECAP_CAPTURE_EVENT_FALLING (1U)
/** @} */

/**
 *  \anchor Ecap_CaptureEvtCntrRstConfig_t
 *  \name ECAP Counter Reset On Capture Event
 *  @{
 */
/** \brief No counter reset upon Capture Event */
#define ECAP_CAPTURE_EVENT_RESET_COUNTER_NO_RESET (0U)
/** \brief Counter reset upon Capture Event */
#define ECAP_CAPTURE_EVENT_RESET_COUNTER_RESET (1U)
/** @} */

/** \brief Capture input source select input is ECAPxINPU[0] */
#define ECAP_CAPTURE_INPUT_SOURCE_SELECT_0 (0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function enables capture loading.
 *
 * \param   baseAddr   It is the Memory address of the ECAP instance used.
 */
void ICU_ECAP_captureLoadingEnable(uint32 baseAddr);

/**
 * \brief   This function disables capture loading
 *
 * \param   baseAddr   It is the Memory address of the ECAP instance used.
 */
void ICU_ECAP_captureLoadingDisable(uint32 baseAddr);

/**
 * \brief   This function configures prescale value.
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   prescale  It is the value which is used to prescale the incoming
 *                    input.
 *
 *          Prescale can take any integer value between 0 to 31
 */
void ICU_ECAP_prescaleConfig(uint32 baseAddr, uint32 prescale);

/**
 * \brief   This function configures ecapture module to operate in capture
 *          mode or in APWM mode.
 *
 * \param   baseAddr    It is the Memory address of the ECAP instance used.
 * \param   modeSelect  It is the value which determines whether ecapture
 *                      module to operate in capture mode or in APWM mode.\n
 *
 *         modeSelect can take one of the following macros.
 *         - \ref Ecap_OperMode_t.
 */
void ICU_ECAP_operatingModeSelect(uint32 baseAddr, uint32 modeSelect);

/**
 * \brief   This function returns time-stamp for a given capture event.
 *
 * \param   baseAddr    It is the Memory address of the ECAP instance used.
 * \param   capEvtFlag  It is the value which determines for which capture event
 *                      time-stam has to returned.
 *
 *         capEvtFlag can take one of the following macros.
 *         - \ref Ecap_CaptEvt_t.
 *
 * \return  Returns the time-stamp for given capure event.
 */
uint32 ICU_ECAP_timeStampRead(uint32 baseAddr, uint32 capEvtFlag);

/**
 * \brief   This function configures Capture Event polarity.
 *
 * \param   baseAddr    It is the Memory address of the ECAP instance used.
 * \param   capEvt1pol  It determines whether Capture Event1 has to be generated
 *                      on rising edge or falling edge of pulse.
 *
 * \param   capEvt2pol  It determines whether Capture Event2 has to be generated
 *                      on rising edge or falling edge of pulse.
 *
 * \param   capEvt3pol  It determines whether Capture Event3 has to be generated
 *                      on rising edge or falling edge of pulse.
 *
 * \param   capEvt4pol  It determines whether Capture Event4 has to be generated
 *                      on rising edge or falling edge of pulse.
 *
 *          capEvtpol variables can take one of the following macros.
 *          - \ref Ecap_CaptureEvtPolarityConfig_t.
 */
void ICU_ECAP_captureEvtPolarityConfig(uint32 baseAddr, uint32 capEvt1pol, uint32 capEvt2pol, uint32 capEvt3pol,
                                       uint32 capEvt4pol);

/**
 * \brief   This function enables reset of the counters upon Capture Events.
 *
 * \param   baseAddr     It is the Memory address of the ECAP instance used.
 * \param   counterRst1  It determines whether counter has to be reset upon
 *                       Capture Event1.
 *
 * \param   counterRst2  It determines whether counter has to be reset upon
 *                       Capture Event2.
 *
 * \param   counterRst3  It determines whether counter has to be reset upon
 *                       Capture Event3.
 *
 * \param   counterRst4  It determines whether counter has to be reset upon
 *                       Capture Event4.
 *
 *          counterRst variables can take one of the following macros.
 *          - \ref Ecap_CaptureEvtCntrRstConfig_t.
 */
void ICU_ECAP_captureEvtCntrRstConfig(uint32 baseAddr, uint32 counterRst1, uint32 counterRst2, uint32 counterRst3,
                                      uint32 counterRst4);

/**
 * \brief   This function configures ECAP to Continuous mode.
 *
 * This API is valid only if ECAP is configured to Capture Mode.It has
 * no significance when ECAP is configured in APWM mode.
 *
 * \param   baseAddr   It is the Memory address of the ECAP instance used.
 */
void ICU_ECAP_continousModeConfig(uint32 baseAddr);

/**
 * \brief   This function configures counter to stop or free running
 *          based on its input argument flag.
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   flag      It is the value which determine counter to be configured
 *                    to stop or free running.\n
 *
 *          flag can take one of the following macros.
 *          - \ref Ecap_CounterMode_t.
 */
void ICU_ECAP_counterControl(uint32 baseAddr, uint32 flag);

/**
 * \brief   This function configures Sync-In and Sync-Out.
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   syncIn    It is the value which determines whether to disable
 *                    syncIn or to enable counter to be loaded from
 *                    CNTPHS register upon a SYNCI signal.\n
 *
 *          syncIn can take one of the following macros.
 *          - \ref Ecap_CounterSyncInMode_t.
 *
 * \param   syncOut   It is the value which select type of syncOut signal
 *                    (i.e select syncIn event to be the Sync-Out signal,
 *                         select PRD_eq event to be Sync-Out signal).\n
 *
 *          syncOut can take one of the following macros.
 *          - \ref Ecap_CounterSyncInMode_t.
 */
void ICU_ECAP_syncInOutSelect(uint32 baseAddr, uint32 syncIn, uint32 syncOut);

/**
 * \brief   This function clears global interrupt and enables the generation of
 *          interrupts if any of the event interrupt are enabled and
 *          corresponding event interrupt flag is set.
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 */
void ICU_ECAP_globalIntrClear(uint32 baseAddr);

/**
 * \brief   This function enables the specified interrupts
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   flag      It is the value which specifies the interrupts to
 *                    be enabled.\n
 *
 *          flag can take one of the following macros.
 *          - \ref Ecap_IntrSrc_t.
 */
void ICU_ECAP_intrEnable(uint32 baseAddr, uint32 flag);

/**
 * \brief   This function disables the specified interrupts
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   flag      It is the value which specifies the interrupts to
 *                    be disabled.\n
 *
 *          flag can take one of the following macros.
 *          - \ref Ecap_IntrSrc_t.
 */
void ICU_ECAP_intrDisable(uint32 baseAddr, uint32 flag);

/**
 * \brief   This function returns the status specified interrupts
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   flag      It is the value which specifies the status of interrupts
 *                    to be returned.\n
 *
 *          flag can take one of the following macros.
 *          - \ref Ecap_IntrSrc_t.
 *
 * \returns Status of the specified interrupts.
 *
 */
uint32 ICU_ECAP_getIntrStatus(uint32 baseAddr, uint32 flag);

/**
 * \brief   This function clears of the status specified interrupts
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   flag      It is the value which specifies the status of interrupts
 *                    to be cleared.\n
 *
 *          flag can take one of the following macros.
 *          - \ref Ecap_IntrSrc_t.
 */
void ICU_ECAP_intrStatusClear(uint32 baseAddr, uint32 flag);

/**
 * \brief   This function configures the capture input source select bits
 *
 * \param   baseAddr  It is the Memory address of the ECAP instance used.
 * \param   srcSelect Capture input select
 *                    0x0 capture input is ECAPxINPUT[0]
 *                    0x1 capture input is ECAPxINPUT[1]
 *                    0x7F  capture input is ECAPxINPUT[127]
 */
void ICU_ECAP_captureInputSourceSelect(uint32 baseAddr, uint8 srcSelect);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ECAP_V2_H_ */

/** @} */
