/*
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
 *
 * All rights reserved not granted here in.
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
 *  \file     Cdd_Pwm_Types.h
 *
 *  \brief    This file contains interface header for CDD_PWM MCAL driver
 *
 */

#ifndef CDD_PWM_TYPES_H
#define CDD_PWM_TYPES_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Pwm_Cfg.h"
#define CDD_PWM_START_SEC_CODE
#include "Cdd_Pwm_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#include "hw_epwm.h"  /* Map the static inline functions in this file as well */
#define CDD_PWM_STOP_SEC_CODE
#include "Cdd_Pwm_MemMap.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CDD_PWM_FALSE ((uint8)(0x0U))
#define CDD_PWM_TRUE  ((uint8)(0x1U))

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/******************************************************************************

 Values that can be passed to EPWM_setCounterCompareShadowLoadMode() as the
 \e loadMode parameter.

*******************************************************************************/
#define CDD_PWM_COMP_LOAD_ON_CNTR_ZERO        EPWM_COMP_LOAD_ON_CNTR_ZERO
#define CDD_PWM_COMP_LOAD_ON_CNTR_PERIOD      EPWM_COMP_LOAD_ON_CNTR_PERIOD
#define CDD_PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD
#define CDD_PWM_COMP_LOAD_FREEZE              EPWM_COMP_LOAD_FREEZE

/******************************************************************************
 Time Base Module
 Values that can be passed to EPWM_setEmulationMode() as the
 \e emulationMode parameter.
******************************************************************************/
#define CDD_PWM_EMULATION_STOP_AFTER_NEXT_TB    EPWM_EMULATION_STOP_AFTER_NEXT_TB
#define CDD_PWM_EMULATION_STOP_AFTER_FULL_CYCLE EPWM_EMULATION_STOP_AFTER_FULL_CYCLE
#define CDD_PWM_EMULATION_FREE_RUN              EPWM_EMULATION_FREE_RUN

/******************************************************************************

 Values that can be passed to EPWM_setClockPrescaler() as the
 \e prescaler parameter.

*******************************************************************************/
#define CDD_PWM_CLOCK_DIVIDER_1   EPWM_CLOCK_DIVIDER_1
#define CDD_PWM_CLOCK_DIVIDER_2   EPWM_CLOCK_DIVIDER_2
#define CDD_PWM_CLOCK_DIVIDER_4   EPWM_CLOCK_DIVIDER_4
#define CDD_PWM_CLOCK_DIVIDER_8   EPWM_CLOCK_DIVIDER_8
#define CDD_PWM_CLOCK_DIVIDER_16  EPWM_CLOCK_DIVIDER_16
#define CDD_PWM_CLOCK_DIVIDER_32  EPWM_CLOCK_DIVIDER_32
#define CDD_PWM_CLOCK_DIVIDER_128 EPWM_CLOCK_DIVIDER_128

/******************************************************************************

 Values that can be passed to EPWM_setClockPrescaler() as the
 \e highSpeedPrescaler parameter.

*******************************************************************************/
#define CDD_PWM_HSCLOCK_DIVIDER_1  EPWM_HSCLOCK_DIVIDER_1
#define CDD_PWM_HSCLOCK_DIVIDER_2  EPWM_HSCLOCK_DIVIDER_2
#define CDD_PWM_HSCLOCK_DIVIDER_4  EPWM_HSCLOCK_DIVIDER_4
#define CDD_PWM_HSCLOCK_DIVIDER_6  EPWM_HSCLOCK_DIVIDER_6
#define CDD_PWM_HSCLOCK_DIVIDER_8  EPWM_HSCLOCK_DIVIDER_8
#define CDD_PWM_HSCLOCK_DIVIDER_10 EPWM_HSCLOCK_DIVIDER_10
#define CDD_PWM_HSCLOCK_DIVIDER_12 EPWM_HSCLOCK_DIVIDER_12
#define CDD_PWM_HSCLOCK_DIVIDER_14 EPWM_HSCLOCK_DIVIDER_14

/******************************************************************************

 Values that can be passed to EPWM_setSyncInPulseSource() as the \e mode
 parameter.

*******************************************************************************/
#define CDD_PWM_SYNC_IN_PULSE_SRC_DISABLE                    EPWM_SYNC_IN_PULSE_SRC_DISABLE
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM0              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM0
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM3              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM3
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM5              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM5
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM6              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM6
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM7              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM7
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM9              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM9
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM10             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM10
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM11             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM11
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM12             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM12
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM13             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM13
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM14             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM14
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM15             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM15
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM16             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM16
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM17             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM17
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM18             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM18
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM19             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM19
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM20             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM20
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM21             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM21
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM22             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM22
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM23             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM23
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM24             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM24
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM25             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM25
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM26             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM26
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM27             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM27
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM28             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM28
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM29             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM29
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM30             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM30
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM31             EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM31
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP0              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP0
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP2              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP2
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP3              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP3
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP4              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP4
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP5              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP5
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP6              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP6
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP7              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP7
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP8              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP8
#define CDD_PWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP9              EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP9
#define CDD_PWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT4             EPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT4
#define CDD_PWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT20            EPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT20
#define CDD_PWM_SYNC_IN_PULSE_SRC_C2K_TIMESYNC_XBAR_PWM_OUT0 EPWM_SYNC_IN_PULSE_SRC_C2K_TIMESYNC_XBAR_PWM_OUT0
#define CDD_PWM_SYNC_IN_PULSE_SRC_C2K_TIMESYNC_XBAR_PWM_OUT1 EPWM_SYNC_IN_PULSE_SRC_C2K_TIMESYNC_XBAR_PWM_OUT1
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG0            EPWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG0
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG1            EPWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG1
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG2            EPWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG2
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG3            EPWM_SYNC_IN_PULSE_SRC_FSIRX0_RX_TRIG3
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG0            EPWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG0
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG1            EPWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG1
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG2            EPWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG2
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG3            EPWM_SYNC_IN_PULSE_SRC_FSIRX1_RX_TRIG3
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG0            EPWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG0
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG1            EPWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG1
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG2            EPWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG2
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG3            EPWM_SYNC_IN_PULSE_SRC_FSIRX2_RX_TRIG3
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG0            EPWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG0
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG1            EPWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG1
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG2            EPWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG2
#define CDD_PWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG3            EPWM_SYNC_IN_PULSE_SRC_FSIRX3_RX_TRIG3

/******************************************************************************

 Values that can be passed to EPWM_setOneShotSyncOutTrigger() as the
 \e trigger parameter.

*******************************************************************************/
#define CDD_PWM_OSHT_SYNC_OUT_TRIG_SYNC   EPWM_OSHT_SYNC_OUT_TRIG_SYNC
#define CDD_PWM_OSHT_SYNC_OUT_TRIG_RELOAD EPWM_OSHT_SYNC_OUT_TRIG_RELOAD

/******************************************************************************

 Values that can be passed to EPWM_setPeriodLoadMode()  as the
 \e loadMode parameter.

*******************************************************************************/
#define CDD_PWM_PERIOD_SHADOW_LOAD EPWM_PERIOD_SHADOW_LOAD
#define CDD_PWM_PERIOD_DIRECT_LOAD EPWM_PERIOD_DIRECT_LOAD

/******************************************************************************

! Values that can be passed to EPWM_setTimeBaseCounterMode() as the
 \e counterMode parameter.

*******************************************************************************/
#define CDD_PWM_COUNTER_MODE_UP          EPWM_COUNTER_MODE_UP
#define CDD_PWM_COUNTER_MODE_DOWN        EPWM_COUNTER_MODE_DOWN
#define CDD_PWM_COUNTER_MODE_UP_DOWN     EPWM_COUNTER_MODE_UP_DOWN
#define CDD_PWM_COUNTER_MODE_STOP_FREEZE EPWM_COUNTER_MODE_STOP_FREEZE

/******************************************************************************

 Values that can be passed to EPWM_setupEPWMLinks() as the \e epwmLink
 parameter.

*******************************************************************************/
#define CDD_PWM_LINK_WITH_PWM_0  EPWM_LINK_WITH_EPWM_0
#define CDD_PWM_LINK_WITH_PWM_1  EPWM_LINK_WITH_EPWM_1
#define CDD_PWM_LINK_WITH_PWM_2  EPWM_LINK_WITH_EPWM_2
#define CDD_PWM_LINK_WITH_PWM_3  EPWM_LINK_WITH_EPWM_3
#define CDD_PWM_LINK_WITH_PWM_4  EPWM_LINK_WITH_EPWM_4
#define CDD_PWM_LINK_WITH_PWM_5  EPWM_LINK_WITH_EPWM_5
#define CDD_PWM_LINK_WITH_PWM_6  EPWM_LINK_WITH_EPWM_6
#define CDD_PWM_LINK_WITH_PWM_7  EPWM_LINK_WITH_EPWM_7
#define CDD_PWM_LINK_WITH_PWM_8  EPWM_LINK_WITH_EPWM_8
#define CDD_PWM_LINK_WITH_PWM_9  EPWM_LINK_WITH_EPWM_9
#define CDD_PWM_LINK_WITH_PWM_10 EPWM_LINK_WITH_EPWM_10
#define CDD_PWM_LINK_WITH_PWM_11 EPWM_LINK_WITH_EPWM_11
#define CDD_PWM_LINK_WITH_PWM_12 EPWM_LINK_WITH_EPWM_12
#define CDD_PWM_LINK_WITH_PWM_13 EPWM_LINK_WITH_EPWM_13
#define CDD_PWM_LINK_WITH_PWM_14 EPWM_LINK_WITH_EPWM_14
#define CDD_PWM_LINK_WITH_PWM_15 EPWM_LINK_WITH_EPWM_15
#define CDD_PWM_LINK_WITH_PWM_16 EPWM_LINK_WITH_EPWM_16
#define CDD_PWM_LINK_WITH_PWM_17 EPWM_LINK_WITH_EPWM_17
#define CDD_PWM_LINK_WITH_PWM_18 EPWM_LINK_WITH_EPWM_18
#define CDD_PWM_LINK_WITH_PWM_19 EPWM_LINK_WITH_EPWM_19
#define CDD_PWM_LINK_WITH_PWM_20 EPWM_LINK_WITH_EPWM_20
#define CDD_PWM_LINK_WITH_PWM_21 EPWM_LINK_WITH_EPWM_21
#define CDD_PWM_LINK_WITH_PWM_22 EPWM_LINK_WITH_EPWM_22
#define CDD_PWM_LINK_WITH_PWM_23 EPWM_LINK_WITH_EPWM_23
#define CDD_PWM_LINK_WITH_PWM_24 EPWM_LINK_WITH_EPWM_24
#define CDD_PWM_LINK_WITH_PWM_25 EPWM_LINK_WITH_EPWM_25
#define CDD_PWM_LINK_WITH_PWM_26 EPWM_LINK_WITH_EPWM_26
#define CDD_PWM_LINK_WITH_PWM_27 EPWM_LINK_WITH_EPWM_27
#define CDD_PWM_LINK_WITH_PWM_28 EPWM_LINK_WITH_EPWM_28
#define CDD_PWM_LINK_WITH_PWM_29 EPWM_LINK_WITH_EPWM_29
#define CDD_PWM_LINK_WITH_PWM_30 EPWM_LINK_WITH_EPWM_30
#define CDD_PWM_LINK_WITH_PWM_31 EPWM_LINK_WITH_EPWM_31
#define CDD_PWM_LINK_DISABLE     EPWM_LINK_DISABLE

/******************************************************************************

 Values that can be passed to EPWM_setCounterCompareShadowLoadMode() as the
 \e loadMode parameter.

*******************************************************************************/
#define CDD_PWM_COMP_LOAD_ON_CNTR_ZERO             EPWM_COMP_LOAD_ON_CNTR_ZERO
#define CDD_PWM_COMP_LOAD_ON_CNTR_PERIOD           EPWM_COMP_LOAD_ON_CNTR_PERIOD
#define CDD_PWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD      EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD
#define CDD_PWM_COMP_LOAD_FREEZE                   EPWM_COMP_LOAD_FREEZE
#define CDD_PWM_COMP_LOAD_ON_SYNC_CNTR_ZERO        EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO
#define CDD_PWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD      EPWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD
#define CDD_PWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD      EPWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD
#define CDD_PWM_COMP_LOAD_ON_SYNC_CNTR_ZERO_PERIOD EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO_PERIOD

/******************************************************************************

 Values that can be passed to EPWM_setActionQualifierShadowLoadMode() as the
 \e loadMode parameter.

*******************************************************************************/
#define CDD_PWM_AQ_LOAD_ON_CNTR_ZERO             EPWM_AQ_LOAD_ON_CNTR_ZERO
#define CDD_PWM_AQ_LOAD_ON_CNTR_PERIOD           EPWM_AQ_LOAD_ON_CNTR_PERIOD
#define CDD_PWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD      EPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD
#define CDD_PWM_AQ_LOAD_FREEZE                   EPWM_AQ_LOAD_FREEZE
#define CDD_PWM_AQ_LOAD_ON_SYNC_CNTR_ZERO        EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO
#define CDD_PWM_AQ_LOAD_ON_SYNC_CNTR_PERIOD      EPWM_AQ_LOAD_ON_SYNC_CNTR_PERIOD
#define CDD_PWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD

/******************************************************************************

 Values that can be passed to EPWM_setActionQualifierT1TriggerSource() and
 EPWM_setActionQualifierT2TriggerSource() as the \e trigger parameter.

*******************************************************************************/
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_1       EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCA_2       EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_2
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCB_1       EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_1
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DCB_2       EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_2
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_TZ_1        EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_1
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_TZ_2        EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_2
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_TZ_3        EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_3
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN EPWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN
#define CDD_PWM_AQ_TRIGGER_EVENT_TRIG_DC_EVTFILT  EPWM_AQ_TRIGGER_EVENT_TRIG_DC_EVTFILT

/******************************************************************************

 Values that can be passed to EPWM_setActionQualifierSWAction(),
 EPWM_setActionQualifierAction() as the \e outPut parameter.

*******************************************************************************/
#define CDD_PWM_AQ_OUTPUT_NO_CHANGE EPWM_AQ_OUTPUT_NO_CHANGE
#define CDD_PWM_AQ_OUTPUT_LOW       EPWM_AQ_OUTPUT_LOW
#define CDD_PWM_AQ_OUTPUT_HIGH      EPWM_AQ_OUTPUT_HIGH
#define CDD_PWM_AQ_OUTPUT_TOGGLE    EPWM_AQ_OUTPUT_TOGGLE

/******************************************************************************

 Values that can be passed to EPWM_setActionQualifierContSWForceAction()
 as the \e outPut parameter.

*******************************************************************************/
#define CDD_PWM_AQ_SW_DISABLED    EPWM_AQ_SW_DISABLED
#define CDD_PWM_AQ_SW_OUTPUT_LOW  EPWM_AQ_SW_OUTPUT_LOW
#define CDD_PWM_AQ_SW_OUTPUT_HIGH EPWM_AQ_SW_OUTPUT_HIGH

/******************************************************************************

 Values that can be passed to EPWM_setDeadBandDelayPolarity() as the
 \e polarity parameter.

*******************************************************************************/
#define CDD_PWM_DB_POLARITY_ACTIVE_HIGH EPWM_DB_POLARITY_ACTIVE_HIGH
#define CDD_PWM_DB_POLARITY_ACTIVE_LOW  EPWM_DB_POLARITY_ACTIVE_LOW

/******************************************************************************

 Values that can be passed to EPWM_setRisingEdgeDeadBandDelayInput(),
 EPWM_setFallingEdgeDeadBandDelayInput() as the input parameter.

*******************************************************************************/
/*! Input signal is ePWMA*/
#define CDD_PWM_DB_INPUT_EPWMA EPWM_DB_INPUT_EPWMA
/*! Input signal is ePWMB*/
#define CDD_PWM_DB_INPUT_EPWMB EPWM_DB_INPUT_EPWMB
/*! Input signal is the output of Rising Edge delay*/
#define CDD_PWM_DB_INPUT_DB_RED EPWM_DB_INPUT_DB_RED

/******************************************************************************

 Values that can be passed to EPWM_setDeadBandControlShadowLoadMode() as
 the \e loadMode parameter.

*******************************************************************************/
#define CDD_PWM_DB_LOAD_ON_CNTR_ZERO        EPWM_DB_LOAD_ON_CNTR_ZERO
#define CDD_PWM_DB_LOAD_ON_CNTR_PERIOD      EPWM_DB_LOAD_ON_CNTR_PERIOD
#define CDD_PWM_DB_LOAD_ON_CNTR_ZERO_PERIOD EPWM_DB_LOAD_ON_CNTR_ZERO_PERIOD
#define CDD_PWM_DB_LOAD_FREEZE              EPWM_DB_LOAD_FREEZE

/******************************************************************************

 Values that can be passed to EPWM_setRisingEdgeDelayCountShadowLoadMode()
 as the \e loadMode parameter.

*******************************************************************************/
#define CDD_PWM_RED_LOAD_ON_CNTR_ZERO        EPWM_RED_LOAD_ON_CNTR_ZERO
#define CDD_PWM_RED_LOAD_ON_CNTR_PERIOD      EPWM_RED_LOAD_ON_CNTR_PERIOD
#define CDD_PWM_RED_LOAD_ON_CNTR_ZERO_PERIOD EPWM_RED_LOAD_ON_CNTR_ZERO_PERIOD
#define CDD_PWM_RED_LOAD_FREEZE              EPWM_RED_LOAD_FREEZE

/******************************************************************************

 Values that can be passed to EPWM_setFallingEdgeDelayCountShadowLoadMode()
 as the \e loadMode parameter.

*******************************************************************************/
#define CDD_PWM_FED_LOAD_ON_CNTR_ZERO        EPWM_FED_LOAD_ON_CNTR_ZERO
#define CDD_PWM_FED_LOAD_ON_CNTR_PERIOD      EPWM_FED_LOAD_ON_CNTR_PERIOD
#define CDD_PWM_FED_LOAD_ON_CNTR_ZERO_PERIOD EPWM_FED_LOAD_ON_CNTR_ZERO_PERIOD
#define CDD_PWM_FED_LOAD_FREEZE              EPWM_FED_LOAD_FREEZE

/******************************************************************************

 Values that can be passed to EPWM_setDeadBandCounterClock() as the
 \e clockMode parameter.

*******************************************************************************/
#define CDD_PWM_DB_COUNTER_CLOCK_FULL_CYCLE EPWM_DB_COUNTER_CLOCK_FULL_CYCLE
#define CDD_PWM_DB_COUNTER_CLOCK_HALF_CYCLE EPWM_DB_COUNTER_CLOCK_HALF_CYCLE

/******************************************************************************

 Values that can be passed to EPWM_setTripZoneAdvDigitalCompareActionA(),
 EPWM_setTripZoneAdvDigitalCompareActionB(), EPWM_setTripZoneAdvAction()
 as the \e tzAdvDCAction parameter.

*******************************************************************************/
#define CDD_PWM_TZ_ADV_ACTION_HIGH_Z  EPWM_TZ_ADV_ACTION_HIGH_Z
#define CDD_PWM_TZ_ADV_ACTION_HIGH    EPWM_TZ_ADV_ACTION_HIGH
#define CDD_PWM_TZ_ADV_ACTION_LOW     EPWM_TZ_ADV_ACTION_LOW
#define CDD_PWM_TZ_ADV_ACTION_TOGGLE  EPWM_TZ_ADV_ACTION_TOGGLE
#define CDD_PWM_TZ_ADV_ACTION_DISABLE EPWM_TZ_ADV_ACTION_DISABLE

/******************************************************************************

 Values that can be passed to EPWM_selectCycleByCycleTripZoneClearEvent() as
 the \e clearMode parameter.

*******************************************************************************/
#define CDD_PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO         EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO
#define CDD_PWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD       EPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD
#define CDD_PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIODE PWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD

/******************************************************************************

 Values that can be passed to EPWM_setInterruptSource() as the
 interruptSource parameter.

*******************************************************************************/
/*! Time-base counter equal to zero*/
#define CDD_PWM_INT_TBCTR_ZERO (EPWM_INT_TBCTR_ZERO)
/*! Time-base counter equal to period*/
#define CDD_PWM_INT_TBCTR_PERIOD (EPWM_INT_TBCTR_PERIOD)
/*! Time-base counter based on mix events*/
#define CDD_PWM_INT_TBCTR_ETINTMIX (EPWM_INT_TBCTR_ETINTMIX)
/*! time-base counter equal to CMPA when the timer is incrementing*/
#define CDD_PWM_INT_TBCTR_U_CMPA (EPWM_INT_TBCTR_U_CMPA)
/*! time-base counter equal to CMPC when the timer is incrementing*/
#define CDD_PWM_INT_TBCTR_U_CMPC (EPWM_INT_TBCTR_U_CMPC)
/*! time-base counter equal to CMPA when the timer is decrementing*/
#define CDD_PWM_INT_TBCTR_D_CMPA (EPWM_INT_TBCTR_D_CMPA)
/*! time-base counter equal to CMPC when the timer is decrementing*/
#define CDD_PWM_INT_TBCTR_D_CMPC (EPWM_INT_TBCTR_D_CMPC)
/*! time-base counter equal to CMPB when the timer is incrementing*/
#define CDD_PWM_INT_TBCTR_U_CMPB (EPWM_INT_TBCTR_U_CMPB)
/*! time-base counter equal to CMPD when the timer is incrementing*/
#define CDD_PWM_INT_TBCTR_U_CMPD (EPWM_INT_TBCTR_U_CMPD)
/*! time-base counter equal to CMPB when the timer is decrementing*/
#define CDD_PWM_INT_TBCTR_D_CMPB (EPWM_INT_TBCTR_D_CMPB)
/*! time-base counter equal to CMPD when the timer is decrementing*/
#define CDD_PWM_INT_TBCTR_D_CMPD (EPWM_INT_TBCTR_D_CMPD)

/******************************************************************************

 Values that can be passed to EPWM_setInterruptSource() and
 EPWM_setADCTriggerSource() as the mixedSource parameter.

*******************************************************************************/
#define CDD_PWM_INT_MIX_TBCTR_ZERO   (EPWM_INT_MIX_TBCTR_ZERO)
#define CDD_PWM_INT_MIX_TBCTR_PERIOD (EPWM_INT_MIX_TBCTR_PERIOD)
#define CDD_PWM_INT_MIX_TBCTR_U_CMPA (EPWM_INT_MIX_TBCTR_U_CMPA)
#define CDD_PWM_INT_MIX_TBCTR_D_CMPA (EPWM_INT_MIX_TBCTR_D_CMPA)
#define CDD_PWM_INT_MIX_TBCTR_U_CMPB (EPWM_INT_MIX_TBCTR_U_CMPB)
#define CDD_PWM_INT_MIX_TBCTR_D_CMPB (EPWM_INT_MIX_TBCTR_D_CMPB)
#define CDD_PWM_INT_MIX_TBCTR_U_CMPC (EPWM_INT_MIX_TBCTR_U_CMPC)
#define CDD_PWM_INT_MIX_TBCTR_D_CMPC (EPWM_INT_MIX_TBCTR_D_CMPC)
#define CDD_PWM_INT_MIX_TBCTR_U_CMPD (EPWM_INT_MIX_TBCTR_U_CMPD)
#define CDD_PWM_INT_MIX_TBCTR_D_CMPD (EPWM_INT_MIX_TBCTR_D_CMPD)
#define CDD_PWM_INT_MIX_DCAEVT1      (EPWM_INT_MIX_DCAEVT1)

/******************************************************************************

! Values that can be passed to EPWM_enableADCTrigger(),
! EPWM_disableADCTrigger(),EPWM_setADCTriggerSource(),
! EPWM_setADCTriggerEventPrescale(),EPWM_getADCTriggerFlagStatus(),
! EPWM_clearADCTriggerFlag(),EPWM_enableADCTriggerEventCountInit(),
! EPWM_disableADCTriggerEventCountInit(),EPWM_forceADCTriggerEventCountInit()
! EPWM_setADCTriggerEventCountInitValue(),EPWM_getADCTriggerEventCount(),
! EPWM_forceADCTrigger() as the \e adcSOCType parameter

*******************************************************************************/
#define CDD_PWM_SOC_A EPWM_SOC_A
#define CDD_PWM_SOC_B EPWM_SOC_B
/*
 *Design: MCAL-23810
 */
typedef EPWM_ADCStartOfConversionType CDD_PWM_ADCStartOfConversionType;

/******************************************************************************

 Values that can be passed to EPWM_setADCTriggerSource() as the
 \e socSource parameter.

*******************************************************************************/
#define CDD_PWM_SOC_DCxEVT1           EPWM_SOC_DCxEVT1
#define CDD_PWM_SOC_TBCTR_ZERO        EPWM_SOC_TBCTR_ZERO
#define CDD_PWM_SOC_TBCTR_PERIOD      EPWM_SOC_TBCTR_PERIOD
#define CDD_PWM_SOC_TBCTR_MIXED_EVENT EPWM_SOC_TBCTR_MIXED_EVENT
#define CDD_PWM_SOC_TBCTR_U_CMPA      EPWM_SOC_TBCTR_U_CMPA
#define CDD_PWM_SOC_TBCTR_U_CMPC      EPWM_SOC_TBCTR_U_CMPC
#define CDD_PWM_SOC_TBCTR_D_CMPA      EPWM_SOC_TBCTR_D_CMPA
#define CDD_PWM_SOC_TBCTR_D_CMPC      EPWM_SOC_TBCTR_D_CMPC
#define CDD_PWM_SOC_TBCTR_U_CMPB      EPWM_SOC_TBCTR_U_CMPB
#define CDD_PWM_SOC_TBCTR_U_CMPD      EPWM_SOC_TBCTR_U_CMPD
#define CDD_PWM_SOC_TBCTR_D_CMPB      EPWM_SOC_TBCTR_D_CMPB
#define CDD_PWM_SOC_TBCTR_D_CMPD      EPWM_SOC_TBCTR_D_CMPD

/******************************************************************************

 Values that can be passed to EPWM_setTripZoneAction() as the
 \e tzAction parameter.

*******************************************************************************/
#define CDD_PWM_HZ_STATE      EPWM_TZ_ACTION_HIGH_Z
#define CDD_PWM_HIGH_STATE    EPWM_TZ_ACTION_HIGH
#define CDD_PWM_LOW_STATE     EPWM_TZ_ACTION_LOW
#define CDD_PWM_DISABLE_STATE EPWM_TZ_ACTION_DISABLE

/**
 *  \anchor CDD_PWM_TbCounterDir_t
 *  \name EPWM Tb Counter Direction
 *  @{
 */
/** \brief Types of Time base counter direction modes. */
/*
 *Design: MCAL-23811
 */
typedef uint32 Cdd_Pwm_TbCounterDirType;
#define CDD_PWM_TB_COUNTER_DIR_UP (CSL_EPWM_TBCTL_CTRMODE_UP_COUNT)
/**< Up Count mode. */
#define CDD_PWM_TB_COUNTER_DIR_DOWN (CSL_EPWM_TBCTL_CTRMODE_DOWN_COUNT)
/**< Down count mode. */
#define CDD_PWM_TB_COUNTER_DIR_UP_DOWN (CSL_EPWM_TBCTL_CTRMODE_UP_DOWN_COUNT)
/**< Up down count mode. */
#define CDD_PWM_TB_COUNTER_DIR_STOP (CSL_EPWM_TBCTL_CTRMODE_STOP_FREEZE)
/**< stop-freeze counter operation (default on reset). */
/** @} */

/**
 *  \anchor CDD_PWM_ShadowRegCtrl_t
 *  \name EPWM Shadow register Control
 *  @{
 */
/** \brief Shadow register enable or disable control.
 *
 *  \details Same macros will be used to control the following shadow registers
 *           - Time Base period register
 *           - Counter Comparator A register
 *           - Counter Comparator B register
 *
 *  \note   Same macros are used for controlling all the three registers because
 *          the field values are same for all these cases.
 *          - Shadow enable  = 0x0
 *          - Shadow disable = 0x1
 *          In any case if these values changes across the above mentioned
 *          registers then separate macros need to be used.
 *          - Shadow enable macros with value 0x0
 *              - CSL_EPWM_TBCTL_PRDLD_LOAD_FROM_SHADOW,
 *              - CSL_EPWM_CMPCTL_SHDWAMODE_SHADOW,
 *              - CSL_EPWM_CMPCTL_SHDWBMODE_SHADOW
 *          - Shadow disable macros with value 0x1
 *              - CSL_EPWM_TBCTL_PRDLD_LOAD_IMMEDIATELY
 *              - CSL_EPWM_CMPCTL_SHDWAMODE_IMMEDIATE
 *              - CSL_EPWM_CMPCTL_SHDWBMODE_IMMEDIATE
 */
/*
 *Design: MCAL-23812
 */
typedef uint32 Cdd_Pwm_ShadowRegCtrlType;
#define CDD_PWM_SHADOW_REG_CTRL_ENABLE (CSL_EPWM_TBCTL_PRDLD_LOAD_FROM_SHADOW)
/**< Shadow register value will be used. */
#define CDD_PWM_SHADOW_REG_CTRL_DISABLE (CSL_EPWM_TBCTL_PRDLD_LOAD_IMMEDIATELY)
/**< Shadow register is disabled and active register value will be used. */
/** @} */

/**
 *  \anchor CDD_PWM_TbCntDirAftSync_t
 *  \name EPWM Counter directions after sync event
 *  @{
 */
/** \brief Counter directions after sync event. */
/*
 *Design: MCAL-23813
 */
typedef uint32 Cdd_Pwm_TbCntDirAftSyncType;
#define CDD_PWM_TB_CNT_DIR_AFT_SYNC_DOWN (CSL_EPWM_TBCTL_PHSDIR_COUNT_DOWN)
/**< Count down after the synchronization event. */
#define CDD_PWM_TB_CNT_DIR_AFT_SYNC_UP (CSL_EPWM_TBCTL_PHSDIR_COUNT_UP)
/**< Count up after the synchronization event. */
/** @} */

/**
 *  \anchor CDD_PWM_TbSyncOutEvt_t
 *  \name EPWM Source of Synchronization output signal
 *  @{
 */
/** \brief Source of Synchronization output signal. */
/*
 *Design: MCAL-23814
 */
typedef uint32 Cdd_Pwm_TbSyncOutEvtType;
#define CDD_PWM_TB_SYNC_OUT_EVT_SYNCIN (CSL_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC)
/**< Sync Input signal. */
#define CDD_PWM_TB_SYNC_OUT_EVT_CNT_EQ_ZERO (CSL_EPWM_TBCTL_SYNCOSEL_CTR_0)
/**< Time-base counter equal to zero. */
#define CDD_PWM_TB_SYNC_OUT_EVT_CNT_EQ_CMP_B (CSL_EPWM_TBCTL_SYNCOSEL_CTR_CPMB)
/**< Time-base counter equal to counter-compare B (TBCTR = CMPB). */
#define CDD_PWM_TB_SYNC_OUT_EVT_DISABLE (CSL_EPWM_TBCTL_SYNCOSEL_DISABLE_EPWMXSYNCO)
/**< Disable EPWMxSYNCO(Sync Output) signal. */
/** @} */

/**
 *  \anchor CDD_PWM_TbSts_t
 *  \name EPWM Flags to get the different types of time base status
 *  @{
 */
/** \brief Flags to get the different types of time base status. */
/*
 *Design: MCAL-23815
 */
typedef uint32 Cdd_Pwm_TbStsType;
#define CDD_PWM_TB_STS_CTR_MAX (CSL_EPWM_TBSTS_CTRMAX_MASK)
/**< Time-Base Counter Max Latched Status. */
#define CDD_PWM_TB_STS_SYNCI (CSL_EPWM_TBSTS_SYNCI_MASK)
/**< Input Synchronization Latched Status. */
#define CDD_PWM_TB_STS_CTR_DIR (CSL_EPWM_TBSTS_CTRDIR_MASK)
/**< Time-Base Counter Direction Status. */
/** @} */

/**
 *  \anchor CDD_PWM_TbEmuMode_t
 *  \name EPWM Emulation Mode
 *  @{
 */
/** \brief Emulation Mode. This selects the behaviour of the ePWM time-base
           counter during emulation events. */
/*
 *Design: MCAL-23816
 */
typedef uint32 Cdd_Pwm_TbEmuModeType;
#define CDD_PWM_TB_EMU_MODE_STP_AFT_NEXT_CYCLE (CSL_EPWM_TBCTL_FREE_SOFT_STOP_AFTER_NEXT_CTR)
/**< Stop after the next time-base counter increment or decrement. */
#define CDD_PWM_TB_EMU_MODE_STP_AFT_COMPLETE_CYCLE (CSL_EPWM_TBCTL_FREE_SOFT_STOP_AFTER_CYCLE)
/**< Stop after the next time-base counter increment or decrement.
     Up-count mode: stop when the time-base counter = period.
     Down-count mode: stop when the time-base counter = 0000.
     Up-down-count mode: stop when the time-base counter = 0000. */
#define CDD_PWM_TB_EMU_MODE_FREE_RUN (CSL_EPWM_TBCTL_FREE_SOFT_RUN2)
/**< Counter is in Free run. */
/** @} */

/**
 *  \anchor CDD_PWM_CcCmp_t
 *  \name EPWM Comparator type
 *  @{
 */
/** \ Counter Comparator type either A or B. */
/*
 *Design: MCAL-23817
 */
typedef uint32 CDD_PWM_CcCmpType;
#define CDD_PWM_CC_CMP_MIN (0U)
/**< Minimum value of enumeration. Used for input validation. */
#define CDD_PWM_CC_CMP_A (CDD_PWM_CC_CMP_MIN)
/**< Counter Comparator A. */
#define CDD_PWM_CC_CMP_B (1U)
/**< Counter Comparator B. */
#define CDD_PWM_CC_CMP_MAX (CSL_EPWM_CC_CMP_B)
/**< Maximum value of enumeration. Used for input validation. */
/** @} */

/**
 *  \anchor CDD_PWM_CcCmpLoadMode_t
 *  \name EPWM Counter-Comparator registers(A and B) load mode
 *  @{
 */
/** \brief   Counter-Comparator registers(A and B) load mode flags from shadow
 *           register.
 *
 *  \details Same macros will be used to control the following registers
 *           - Counter Comparator A register
 *           - Counter Comparator B register
 *
 *  \note   Same macros are used for controlling all the three registers because
 *          the field values are same for all these cases.
 *          - load when counter equals zero   = 0x0
 *          - load when counter equals period = 0x1
 *          - load when counter equals zero or period = 0x2
 *          - Do not load                     = 0x3
 *          In any case if these values changes across the above mentioned
 *          registers, then separate macros need to be used.
 *          - Load when counter equals zero macros with value 0x0
 *              - CSL_EPWM_CMPCTL_LOADAMODE_CTR_0,
 *              - CSL_EPWM_CMPCTL_LOADBMODE_CTR_0,
 *          - Load when counter equals period macros with value 0x1
 *              - CSL_EPWM_CMPCTL_LOADAMODE_CTR_PRD
 *              - CSL_EPWM_CMPCTL_LOADBMODE_CTR_PRD
 *          - Load when counter equals zero or period macros with value 0x2
 *              - CSL_EPWM_CMPCTL_LOADAMODE_CTR_0_OR_PRD
 *              - CSL_EPWM_CMPCTL_LOADBMODE_CTR_0_OR_PRD
 *          - Do not load macros with value 0x3
 *              - CSL_EPWM_CMPCTL_LOADAMODE_FREEZE
 *              - CSL_EPWM_CMPCTL_LOADBMODE_FREEZE
 */
/*
 *Design: MCAL-23818
 */
typedef uint32 CDD_PWM_CcCmpLoadModeType;
#define CDD_PWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO (CSL_EPWM_CMPCTL_LOADAMODE_CTR_0)
/**< Load on CTR = 0: Time-base counter equal to zero. */
#define CDD_PWM_CC_CMP_LOAD_MODE_CNT_EQ_PRD (CSL_EPWM_CMPCTL_LOADAMODE_CTR_PRD)
/**< Load on CTR = PRD: Time-base counter equal to period. */
#define CDD_PWM_CC_CMP_LOAD_MODE_CNT_EQ_ZERO_OR_PRD (CSL_EPWM_CMPCTL_LOADAMODE_CTR_0_OR_PRD)
/**< Load on either CTR = 0 or CTR = PRD. */
#define CDD_PWM_CC_CMP_LOAD_MODE_NO_LOAD (CSL_EPWM_CMPCTL_LOADAMODE_FREEZE)
/**< Freeze (no loads possible). */
/** @} */

/**
 *  \anchor CDD_PWM_AqAction_t
 *  \name EPWM Actions
 *  @{
 */
/** \brief   Types of Actions that Action Qualifier can take on the Output when
 *           the supported counter compare event occurs.
 *
 *  \details Same actions will be applicable for all the supported events and
 *           same actions are applicable for both A and B channel PWM outputs.
 *
 *  \note    Same macros are used for all the events and for both A and B
 *           because their field values are same.
 *           - Action Do nothing macros with value 0x0
 *              - CSL_EPWM_AQCTLx_ZRO_DISABLED
 *              - CSL_EPWM_AQCTLx_PRD_DISABLED
 *              - CSL_EPWM_AQCTLx_CAU_DISABLED
 *              - CSL_EPWM_AQCTLx_CAD_DISABLED
 *              - CSL_EPWM_AQCTLx_CBU_DISABLED
 *              - CSL_EPWM_AQCTLx_CBD_DISABLED
 *           - Action high macros with value 0x1
 *              - CSL_EPWM_AQCTLx_ZRO_CLEAR
 *              - CSL_EPWM_AQCTLx_PRD_CLEAR
 *              - CSL_EPWM_AQCTLx_CAU_CLEAR
 *              - CSL_EPWM_AQCTLx_CAD_CLEAR
 *              - CSL_EPWM_AQCTLx_CBU_CLEAR
 *              - CSL_EPWM_AQCTLx_CBD_CLEAR
 *           - Action low macros  with value 0x2
 *              - CSL_EPWM_AQCTLx_ZRO_SET
 *              - CSL_EPWM_AQCTLx_PRD_SET
 *              - CSL_EPWM_AQCTLx_CAU_SET
 *              - CSL_EPWM_AQCTLx_CAD_SET
 *              - CSL_EPWM_AQCTLx_CBU_SET
 *              - CSL_EPWM_AQCTLx_CBD_SET
 *           - Action toggle macros  with value 0x3
 *              - CSL_EPWM_AQCTLx_ZRO_TOGGLE
 *              - CSL_EPWM_AQCTLx_PRD_TOGGLE
 *              - CSL_EPWM_AQCTLx_CAU_TOGGLE
 *              - CSL_EPWM_AQCTLx_CAD_TOGGLE
 *              - CSL_EPWM_AQCTLx_CBU_TOGGLE
 *              - CSL_EPWM_AQCTLx_CBD_TOGGLE
 */
/*
 *Design: MCAL-23819
 */
typedef uint32 CDD_PWM_AqActionType;
#define CDD_PWM_AQ_ACTION_DONOTHING (CSL_EPWM_AQCTLA_ZRO_DISABLED)
/**< Do nothing (Action disabled). */
#define CDD_PWM_AQ_ACTION_LOW (CSL_EPWM_AQCTLA_ZRO_CLEAR)
/**< Clear: Force EPWMx output low. */
#define CDD_PWM_AQ_ACTION_HIGH (CSL_EPWM_AQCTLA_ZRO_SET)
/**< Set: Force EPWMx output high. */
#define EPQM_AQ_ACTION_TOLLGE    (CSL_EPWM_AQCTLA_ZRO_TOGGLE)
#define CDD_PWM_AQ_ACTION_TOLLGE (CSL_EPQM_AQ_ACTION_TOLLGE)
/**< Toggle EPWMx output: low output signal will be forced high,
         and a high signal will be forced low. */
/** @} */

/**
 *  \anchor CDD_PWM_AqSwTrigOtAction_t
 *  \name EPWM output actions
 *  @{
 */
/** \brief Actions to be taken on the output, when Software triggered one time
 *         events will occur.
 *
 *  \details Same macros will be used for both A and B channel outputs because
 *           the bit field values are same.
 *
 *  \note    The following are the similar macros,
 *           - Do nothing macros with value 0x0
 *              - CSL_EPWM_AQSFRC_ACTSFA_DISABLED
 *              - CSL_EPWM_AQSFRC_ACTSFB_DISABLED
 *           - Action low macros with value 0x1
 *              - CSL_EPWM_AQSFRC_ACTSFA_CLEAR
 *              - CSL_EPWM_AQSFRC_ACTSFB_CLEAR
 *           - Action high macros with value 0x2
 *              - CSL_EPWM_AQSFRC_ACTSFA_SET
 *              - CSL_EPWM_AQSFRC_ACTSFB_SET
 *           - Action toggle macros with value 0x3
 *              - CSL_EPWM_AQSFRC_ACTSFA_TOGGLE
 *              - CSL_EPWM_AQSFRC_ACTSFB_TOGGLE
 */
/*
 *Design: MCAL-23820
 */
typedef uint32 CDD_PWM_AqSwTrigOtActionType;
#define CDD_PWM_AQ_SW_TRIG_OT_ACTION_DONOTHING (CSL_EPWM_AQSFRC_ACTSFA_DISABLED)
/**< Do nothing (Action disabled). */
#define CDD_PWM_AQ_SW_TRIG_OT_ACTION_LOW (CSL_EPWM_AQSFRC_ACTSFA_CLEAR)
/**< Clear: Output Low. */
#define CDD_PWM_AQ_SW_TRIG_OT_ACTION_HIGH (CSL_EPWM_AQSFRC_ACTSFA_SET)
/**< Set: Output high. */
#define CDD_PWM_AQ_SW_TRIG_OT_ACTION_TOGGLE (CSL_EPWM_AQSFRC_ACTSFA_TOGGLE)
/**< Toggle output. */
/** @} */

/**
 *  \anchor CDD_PWM_AqSwTrigContAction_t
 *  \name EPWM Continuous software forced actions
 *  @{
 */
/** \brief Types of Continuous software forced actions on output.
 *
 *  \details Same macros will be used for configuration of both A and B PWM
 *           outputs, because bit field values for both A and B are same.
 *
 *  \note    The following are the similar macros,
 *           - Do nothing macros with value 0x0
 *              - CSL_EPWM_AQCSFRC_CSFA_DISABLED
 *              - CSL_EPWM_AQCSFRC_CSFB_DISABLED
 *           - Action low macros with value 0x1
 *              - CSL_EPWM_AQCSFRC_CSFA_LOW_OUTPUT
 *              - CSL_EPWM_AQCSFRC_CSFB_LOW_OUTPUT
 *           - Action high macros with value 0x2
 *              - CSL_EPWM_AQCSFRC_CSFA_HIGH_OUTPUT
 *              - CSL_EPWM_AQCSFRC_CSFB_HIGH_OUTPUT
 *           - Action toggle macros with value 0x3
 *              - CSL_EPWM_AQCSFRC_CSFA_NO_EFFECT
 *              - CSL_EPWM_AQCSFRC_CSFB_NO_EFFECT
 */
/*
 *Design: MCAL-23821
 */
typedef uint32 CDD_PWM_AqSwTrigContActionType;
#define CDD_PWM_AQ_SW_TRIG_CONT_ACTION_NOEFFECT (CSL_EPWM_AQCSFRC_CSFA_DISABLED)
/**< Forcing disabled, that is, has no effect. */
#define CDD_PWM_AQ_SW_TRIG_CONT_ACTION_LOW (CSL_EPWM_AQCSFRC_CSFA_LOW_OUTPUT)
/**< Forces a continuous low on output A. */
#define CDD_PWM_AQ_SW_TRIG_CONT_ACTION_HIGH (CSL_EPWM_AQCSFRC_CSFA_HIGH_OUTPUT)
/**< Forces a continuous high on output A. */
#define CDD_PWM_AQ_SW_TRIG_CONT_ACTION_SW_DISBALED (CSL_EPWM_AQCSFRC_CSFA_NO_EFFECT)
/**< Software forcing is disabled and has no effect. */
/** @} */

/**
 *  \anchor CDD_PWM_AqCsfrcRegReload_t
 *  \name EPWM Software Force Active Register Reload
 *  @{
 */
/** \brief Action Qualifier Software Force Active Register Reload From
          Shadow Options. */
/*
 *Design: MCAL-23822
 */
typedef uint32 CDD_PWM_AqCsfrcRegReloadType;
#define CDD_PWM_AQ_CSFRC_REG_RELOAD_CNT_EQ_ZRO (CSL_EPWM_AQSFRC_RLDCSF_CTR_0)
/**< Load on event counter equals zero. */
#define CDD_PWM_AQ_CSFRC_REG_RELOAD_CNT_EQ_PRD (CSL_EPWM_AQSFRC_RLDCSF_CTR_PERIOD)
/**< Load on event counter equals period. */
#define CDD_PWM_AQ_CSFRC_REG_RELOAD_CNT_EQ_ZRO_OR_PRD (CSL_EPWM_AQSFRC_RLDCSF_CTR_0_OR_PERIOD)
/**< Load on event counter equals zero or counter equals period. */
#define CDD_PWM_AQ_CSFRC_REG_RELOAD_IMMEDIATE (CSL_EPWM_AQSFRC_RLDCSF_IMMEDIATE)
/**< Load immediately. */
/** @} */

/**
 *  \anchor CDD_PWM_DbInMode_t
 *  \name EPWM Dead Band Input Mode Control
 *  @{
 */
/** \brief Dead Band Input Mode Control. This allows you to select the
           input source to the falling-edge and rising-edge delay. */
/*
 *Design: MCAL-23823
 */
typedef uint32 CDD_PWM_DbInModeType;
#define CDD_PWM_DB_IN_MODE_A_RED_A_FED (CSL_EPWM_DBCTL_IN_MODE_SRC_ARED_AFED)
/**< EPWMxA In (from the action-qualifier) is the source for both
         falling-edge and rising-edge delay. */
#define CDD_PWM_DB_IN_MODE_B_RED_A_FED (CSL_EPWM_DBCTL_IN_MODE_SRC_BRED_AFED)
/**< EPWMxB In (from the action-qualifier) is the source for
         rising-edge delayed signal. EPWMxA In (from the action-qualifier) is
         the source for falling-edge delayed signal. */
#define CDD_PWM_DB_IN_MODE_A_RED_B_FED (CSL_EPWM_DBCTL_IN_MODE_SRC_ARED_BFED)
/**< EPWMxA In (from the action-qualifier) is the source for rising-edge
         delayed signal. EPWMxB In (from the action-qualifier) is the source for
         falling-edge delayed signal. */
#define CDD_PWM_DB_IN_MODE_B_RED_B_FED (CSL_EPWM_DBCTL_IN_MODE_SRC_BRED_BFED)
/**< EPWMxB In (from the action-qualifier) is the source for both
         rising-edge delay and falling-edge delayed signal. */
/** @} */

/**
 *  \anchor CDD_PWM_DbPolSel_t
 *  \name EPWM Polarity Select Control
 *  @{
 */
/** \brief Polarity Select Control. This allows you to selectively invert one
           of the delayed signals before it is sent out of the dead-band
           sub-module. */
/*
 *Design: MCAL-23824
 */
typedef uint32 CDD_PWM_DbPolSelType;
#define CDD_PWM_DB_POL_SEL_ACTV_HIGH (CSL_EPWM_DBCTL_POLSEL_ACTIVE_HIGH)
/**< Neither EPWMxA nor EPWMxB is inverted (default). */
#define CDD_PWM_DB_POL_SEL_ACTV_LOW_COMPLEMENTARY (CSL_EPWM_DBCTL_POLSEL_ACTIVE_LOW_COMPLEMENTARY)
/**< EPWMxA is inverted. */
#define CDD_PWM_DB_POL_SEL_ACTV_HIGH_COMPLEMENTARY (CSL_EPWM_DBCTL_POLSEL_ACTIVE_HIGH_COMPLEMENTARY)
/**< EPWMxB is inverted. */
#define CDD_PWM_DB_POL_SEL_ACTV_LOW (CSL_EPWM_DBCTL_POLSEL_ACTIVE_LOW)
/**< Both EPWMxA and EPWMxB are inverted. */
/** @} */

/**
 *  \anchor CDD_PWM_DbOutMode_t
 *  \name EPWM Dead-band Output Mode Control
 *  @{
 */
/** \brief Dead-band Output Mode Control. This allows you to selectively enable
           or bypass the dead-band generation for the falling-edge and
           rising-edge delay. */
/*
 *Design: MCAL-23825
 */
typedef uint32 CDD_PWM_DbOutModeType;
#define CDD_PWM_DB_OUT_MODE_BYPASS (CSL_EPWM_DBCTL_OUT_MODE_DISABLED)
/**< Dead-band generation is bypassed for both output signals. In this mode,
         both the EPWMxA and EPWMxB output signals from the action-qualifier are
         passed directly to the PWM-chopper sub-module. */
#define CDD_PWM_DB_OUT_MODE_NO_RED_B_FED (CSL_EPWM_DBCTL_OUT_MODE_DISABLE_RISING_EDGE)
/**< Disable rising-edge delay. The EPWMxA signal from the action-qualifier
         is passed straight through to the EPWMxA input of the PWM-chopper
         sub-module. The falling-edge delayed signal is seen on output EPWMxB */
#define CDD_PWM_DB_OUT_MODE_A_RED_NO_FED (CSL_EPWM_DBCTL_OUT_MODE_DISABLE_FALLING_EDGE)
/**< Disable falling-edge delay. The EPWMxB signal from the action-qualifier
         is passed straight through to the EPWMxB input of the PWM-chopper
         sub-module. The rising-edge delayed signal is seen on output EPWMxA. */
#define CDD_PWM_DB_OUT_MODE_A_RED_B_FED (CSL_EPWM_DBCTL_OUT_MODE_ENABLED)
/**< Dead-band is fully enabled for both rising-edge delay on output EPWMxA
         and falling-edge delay on output EPWMxB. */
/** @} */

/**
 *  \anchor CDD_PWM_ChpDutyCycle_t
 *  \name EPWM Chopping Clock Duty Cycle
 *  @{
 */
/** \brief Chopping Clock Duty Cycle values. */
/*
 *Design: MCAL-23826
 */
typedef uint32 CDD_PWM_ChpDutyCycleType;
#define CDD_PWM_CHP_DUTY_CYCLE_PERC_12PNT5 (CSL_EPWM_PCCTL_CHPDUTY_DUTY_12_5)
/**< Duty cycle 1/8 (12.5%). */
#define CDD_PWM_CHP_DUTY_CYCLE_PERC_25 (CSL_EPWM_PCCTL_CHPDUTY_DUTY_25)
/**< Duty cycle 2/8 (25%). */
#define CDD_PWM_CHP_DUTY_CYCLE_PERC_37PNT5 (CSL_EPWM_PCCTL_CHPDUTY_DUTY_37_5)
/**< Duty cycle 3/8 (37.5%). */
#define CDD_PWM_CHP_DUTY_CYCLE_PERC_50_PER (CSL_EPWM_PCCTL_CHPDUTY_DUTY_50)
/**< Duty cycle 4/8 (50%). */
#define CDD_PWM_CHP_DUTY_CYCLE_PERC_62PNT5 (CSL_EPWM_PCCTL_CHPDUTY_DUTY_62_5)
/**< Duty cycle 5/8 (62.5%). */
#define CDD_PWM_CHP_DUTY_CYCLE_PERC_75 (CSL_EPWM_PCCTL_CHPDUTY_DUTY_75)
/**< Duty cycle 6/8 (75%). */
#define CDD_PWM_CHP_DUTY_CYCLE_PERC_87PNT5 (CSL_EPWM_PCCTL_CHPDUTY_DUTY_87_5)
/**< Duty cycle 7/8 (87.5%). */
/** @} */

/**
 *  \anchor CDD_PWM_ChpClkFreq_t
 *  \name EPWM Chopping Clock Frequency
 *  @{
 */
/** \brief Chopping Clock Frequency values . */
/*
 *Design: MCAL-23827
 */
typedef uint32 CDD_PWM_ChpClkFreqType;
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_1 (CSL_EPWM_PCCTL_CHPFREQ_DIV_1)
/**< Divide by 1 (no prescale). */
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_2 (CSL_EPWM_PCCTL_CHPFREQ_DIV_2)
/**< Divide by 2. */
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_3 (CSL_EPWM_PCCTL_CHPFREQ_DIV_3)
/**< Divide by 3. */
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_4 (CSL_EPWM_PCCTL_CHPFREQ_DIV_4)
/**< Divide by 4. */
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_5 (CSL_EPWM_PCCTL_CHPFREQ_DIV_5)
/**< Divide by 5. */
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_6 (CSL_EPWM_PCCTL_CHPFREQ_DIV_6)
/**< Divide by 6. */
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_7 (CSL_EPWM_PCCTL_CHPFREQ_DIV_7)
/**< Divide by 7. */
#define CDD_PWM_CHP_CLK_FREQ_DIV_BY_8 (CSL_EPWM_PCCTL_CHPFREQ_DIV_8)
/**< Divide by 8. */
/** @} */

/**
 *  \anchor CDD_PWM_ChpOshtWidth_t
 *  \name EPWM One-Shot Pulse Width
 *  @{
 */
/** \brief One-Shot Pulse Width values. */
/*
 *Design: MCAL-23828
 */
typedef uint32 CDD_PWM_ChpOshtWidthType;
#define CDD_PWM_CHP_OSHT_WIDTH_MIN (0U)
/**< Minimum value of enumeration. Used for input validation. */
#define CDD_PWM_CHP_OSHT_WIDTH_1XSYSOUT_BY_8 (CDD_PWM_CHP_OSHT_WIDTH_MIN)
/**< 1 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_2XSYSOUT_BY_8 (1U)
/**< 2 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_3XSYSOUT_BY_8 (2U)
/**< 3 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_4XSYSOUT_BY_8 (3U)
/**< 4 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_5XSYSOUT_BY_8 (4U)
/**< 5 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_6XSYSOUT_BY_8 (5U)
/**< 6 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_7XSYSOUT_BY_8 (6U)
/**< 7 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_8XSYSOUT_BY_8 (7U)
/**< 8 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_9XSYSOUT_BY_8 (8U)
/**< 9 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_10XSYSOUT_BY_8 (9U)
/**< 10 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_11XSYSOUT_BY_8 (10U)
/**< 11 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_12XSYSOUT_BY_8 (11U)
/**< 12 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_13XSYSOUT_BY_8 (12U)
/**< 13 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_14XSYSOUT_BY_8 (13U)
/**< 14 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_15XSYSOUT_BY_8 (14U)
/**< 15 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_16XSYSOUT_BY_8 (15U)
/**< 16 x SYSCLKOUT/8 wide. */
#define CDD_PWM_CHP_OSHT_WIDTH_MAX (CSL_EPWM_CHP_OSHT_WIDTH_16XSYSOUT_BY_8)
/**< Maximum value of enumeration. Used for input validation. */
/** @} */

/**
 *  \anchor CDD_PWM_TzTripAction_t
 *  \name EPWM output action when a trip event occurs
 *  @{
 */
/** \brief   Action to be taken on PWM output When a trip event occurs.
 *
 *  \details Same macros will be used to control both A and B outputs because
 *           the bit field values are same for A and B channels.
 *
 *  \note    The following are the similar macros
 *           - Tri state action macro with value 0x0
 *              - CSL_EPWM_TZCTL_TZA_HIGH_IMPEDANCE
 *              - CSL_EPWM_TZCTL_TZB_HIGH_IMPEDANCE
 *           - High action macro  with value 0x1
 *              - CSL_EPWM_TZCTL_TZA_HIGH_STATE
 *              - CSL_EPWM_TZCTL_TZA_HIGH_STATE
 *           - Low action macro with value 0x2
 *              - CSL_EPWM_TZCTL_TZA_LOW_STATE
 *              - CSL_EPWM_TZCTL_TZB_LOW_STATE
 *           - Do nothing action macro with value 0x3
 *              - CSL_EPWM_TZCTL_TZA_DO_NOTHING
 *              - CSL_EPWM_TZCTL_TZB_DO_NOTHING
 */
/*
 *Design: MCAL-23829
 */
typedef uint32 CDD_PWM_TzTripActionType;
#define CDD_PWM_TZ_TRIP_ACTION_TRI_STATE (CSL_EPWM_TZCTL_TZA_HIGH_IMPEDANCE)
/**< High impedance (EPWMxA = High-impedance state). */
#define CDD_PWM_TZ_TRIP_ACTION_HIGH (CSL_EPWM_TZCTL_TZA_HIGH_STATE)
/**< Force EPWMxA to a high state. */
#define CDD_PWM_TZ_TRIP_ACTION_LOW (CSL_EPWM_TZCTL_TZA_LOW_STATE)
/**< Force EPWMxA to a low state. */
#define CDD_PWM_TZ_TRIP_ACTION_DO_NOTHING (CSL_EPWM_TZCTL_TZA_DO_NOTHING)
/**< Do nothing, no action is taken on EPWMxA. */
/** @} */

/**
 *  \anchor CDD_PWM_TzEvent_t
 *  \name EPWM trip zone events
 *  @{
 */
/** \brief Type of trip zone events. */
/*
 *Design: MCAL-23830
 */
typedef uint32 CDD_PWM_TzEventType;
#define CDD_PWM_TZ_EVENT_MIN (0x0U)
/**< Minimum value of enumeration. Used for input validation. */
#define CDD_PWM_TZ_EVENT_ONE_SHOT (EPWM_TZ_INTERRUPT_OST)
/**< One shot trip zone event. */
#define CDD_PWM_TZ_EVENT_CYCLE_BY_CYCLE (EPWM_TZ_INTERRUPT_CBC)
/**< Cycle by cycle trip zone event. */
#define CDD_PWM_TZ_INTERRUPT_DCAEVT1 (EPWM_TZ_INTERRUPT_DCAEVT1)
/**< DCA event 1. */
#define CDD_PWM_TZ_INTERRUPT_DCAEVT2 (EPWM_TZ_INTERRUPT_DCAEVT2)
/**< DCA event 2. */
#define CDD_PWM_TZ_INTERRUPT_DCBEVT1 (EPWM_TZ_INTERRUPT_DCBEVT1)
/**< DCB event 1. */
#define CDD_PWM_TZ_INTERRUPT_DCBEVT2 (EPWM_TZ_INTERRUPT_DCBEVT2)
/**< DCB event 2. */
#define CDD_PWM_TZ_EVENT_MAX (CSL_EPWM_TZ_EVENT_CYCLE_BY_CYCLE)
/**< Maximum value of enumeration. Used for input validation. */
/** @} */

/******************************************************************************

 Values that can be passed to EPWM_clearCycleByCycleTripZoneFlag()
 as the tzCbcFlag parameter and returned by
 EPWM_getCycleByCycleTripZoneFlagStatus().

*******************************************************************************/
/*! CBC flag 1*/
#define CDD_PWM_TZ_CBC_FLAG_1 (0x1U)
/*! CBC flag 2*/
#define CDD_PWMTZ_CBC_FLAG_2 (0x2U)
/*! CBC flag 3*/
#define CDD_PWMTZ_CBC_FLAG_3 (0x4U)
/*! CBC flag 4*/
#define CDD_PWMTZ_CBC_FLAG_4 (0x8U)
/*! CBC flag 5*/
#define CDD_PWMTZ_CBC_FLAG_5 (0x10U)
/*! CBC flag 6*/
#define CDD_PWMTZ_CBC_FLAG_6 (0x20U)
/*! CBC flag Digital compare event A2*/
#define CDD_PWMTZ_CBC_FLAG_DCAEVT2 (0x40U)
/*! CBC flag Digital compare event B2*/
#define CDD_PWMTZ_CBC_FLAG_DCBEVT2 (0x80U)
/*! CBC flag Capture event*/
#define CDD_PWMTZ_CBC_FLAG_CAPEVT (0x100U)

/*! OST flag OST1*/
#define CDD_PWMTZ_OST_FLAG_OST1 (0x1U)
/*! OST flag OST2*/
#define CDD_PWMTZ_OST_FLAG_OST2 (0x2U)
/*! OST flag OST3*/
#define CDD_PWMTZ_OST_FLAG_OST3 (0x4U)
/*! OST flag OST4*/
#define CDD_PWMTZ_OST_FLAG_OST4 (0x8U)
/*! OST flag OST5*/
#define CDD_PWMTZ_OST_FLAG_OST5 (0x10U)
/*! OST flag OST6*/
#define CDD_PWMTZ_OST_FLAG_OST6 (0x20U)
/*! OST flag Digital compare event A1*/
#define CDD_PWMTZ_OST_FLAG_DCAEVT1 (0x40U)
/*! OST flag Digital compare event B1*/
#define CDD_PWMTZ_OST_FLAG_DCBEVT1 (0x80U)
/*! OST flag Capture Event*/
#define CDD_PWMTZ_OST_FLAG_CAPEVT (0x100U)

/*! Trip Zones Cycle By Cycle flag*/
#define CDD_PWMTZ_FLAG_CBC (0x2U)
/*! Trip Zones One Shot flag*/
#define CDD_PWMTZ_FLAG_OST (0x4U)
/*! Digital Compare A Event 1 flag*/
#define CDD_PWMTZ_FLAG_DCAEVT1 (0x8U)
/*! Digital Compare A Event 2 flag*/
#define CDD_PWMTZ_FLAG_DCAEVT2 (0x10U)
/*! Digital Compare B Event 1 flag*/
#define CDD_PWMTZ_FLAG_DCBEVT1 (0x20U)
/*! Digital Compare B Event 2 flag*/
#define CDD_PWMTZ_FLAG_DCBEVT2 (0x40U)
/*! Capture Event flag*/
#define CDD_PWMTZ_FLAG_CAPEVT (0x80U)

/**
 *  \anchor CDD_PWM_TzStsFlg_t
 *  \name EPWM Trip zone status flags
 *  @{
 */
/** \brief Trip zone status flags. */
/*
 *Design: MCAL-23831
 */
typedef uint32 CDD_PWM_TzStsFlgType;
#define CDD_PWM_TZ_STS_FLG_OST (CSL_EPWM_TZFLG_OST_MASK)
/**< Latched Status Flag for A One-Shot Trip Event.*/
#define CDD_PWM_TZ_STS_FLG_CBC (CSL_EPWM_TZFLG_CBC_MASK)
/**< Latched Status Flag for Cycle-By-Cycle Trip Event.*/
#define CDD_PWM_TZ_STS_FLG_INT (CSL_EPWM_TZFLG_INT_MASK)
/**< Latched status for Trip Interrupt .*/
/** @} */

/*******************************************************************************
 Trip Zone


 Values that can be passed to EPWM_enableTripZoneSignals() and
 EPWM_disableTripZoneSignals() as the tzSignal parameter.

*******************************************************************************/
/*! TZ1 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_CBC1 (EPWM_TZ_SIGNAL_CBC1)
/*! TZ2 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_CBC2 (EPWM_TZ_SIGNAL_CBC2)
/*! TZ3 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_CBC3 (EPWM_TZ_SIGNAL_CBC3)
/*! TZ4 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_CBC4 (EPWM_TZ_SIGNAL_CBC4)
/*! TZ5 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_CBC5 (EPWM_TZ_SIGNAL_CBC5)
/*! TZ6 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_CBC6 (EPWM_TZ_SIGNAL_CBC6)
/*! DCAEVT2 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_DCAEVT2 (EPWM_TZ_SIGNAL_DCAEVT2)
/*! DCBEVT2 Cycle By Cycle*/
#define CDD_PWM_TZ_SIGNAL_DCBEVT2 (EPWM_TZ_SIGNAL_DCBEVT2)
/*! One-shot TZ1*/
#define CDD_PWM_TZ_SIGNAL_OSHT1 (EPWM_TZ_SIGNAL_OSHT1)
/*! One-shot TZ2*/
#define CDD_PWM_TZ_SIGNAL_OSHT2 (EPWM_TZ_SIGNAL_OSHT2)
/*! One-shot TZ3*/
#define CDD_PWM_TZ_SIGNAL_OSHT3 (EPWM_TZ_SIGNAL_OSHT3)
/*! One-shot TZ4*/
#define CDD_PWM_TZ_SIGNAL_OSHT4 (EPWM_TZ_SIGNAL_OSHT4)
/*! One-shot TZ5*/
#define CDD_PWM_TZ_SIGNAL_OSHT5 (EPWM_TZ_SIGNAL_OSHT5)
/*! One-shot TZ6*/
#define CDD_PWM_TZ_SIGNAL_OSHT6 (EPWM_TZ_SIGNAL_OSHT6)
/*! One-shot DCAEVT1*/
#define CDD_PWM_TZ_SIGNAL_DCAEVT1 (EPWM_TZ_SIGNAL_DCAEVT1)
/*! One-shot DCBEVT1*/
#define CDD_PWM_TZ_SIGNAL_DCBEVT1 (EPWM_TZ_SIGNAL_DCBEVT1)
/*! One-shot Capture event*/
#define CDD_PWM_TZ_SIGNAL_DCAEVT2    (EPWM_TZ_SIGNAL_DCAEVT2)
#define CDD_PWM_TZ_SIGNAL_DCBEVT2    (EPWM_TZ_SIGNAL_DCBEVT2)
#define CDD_PWM_TZ_SIGNAL_CAPEVT_OST (EPWM_TZ_SIGNAL_CAPEVT_OST)
/*! Cycle by cycle capture event*/
#define CDD_PWM_TZ_SIGNAL_CAPEVT_CBC (EPWM_TZ_SIGNAL_CAPEVT_CBC)

/**
 *  \anchor CDD_PWM_EtIntrEvt_t
 *  \name EPWM Interrupt (EPWMx_INT) Selection Options
 *  @{
 */
/** \brief ePWM Interrupt (EPWMx_INT) Selection Options. */
/*
 *Design: MCAL-23832
 */
typedef uint32 CDD_PWM_EtIntrEvtType;
#define CDD_PWM_ET_INTR_EVT_CNT_EQ_ZRO (CSL_EPWM_ETSEL_INTSEL_CTR_0)
/**< Enable event time-base counter equal to zero. (TBCTR = 0000h).*/
#define CDD_PWM_ET_INTR_EVT_CNT_EQ_PRD (CSL_EPWM_ETSEL_INTSEL_CTR_PERIOD)
/**< Enable event time-base counter equal to period (TBCTR = TBPRD).*/
#define CDD_PWM_ET_INTR_EVT_CNT_EQ_CMPA_INC (CSL_EPWM_ETSEL_INTSEL_CTR_CMPA_INCR)
/**< Enable event time-base counter equal to CMPA when the timer is
         incrementing.*/
#define CDD_PWM_ET_INTR_EVT_CNT_EQ_CMPA_DEC (CSL_EPWM_ETSEL_INTSEL_CTR_CMPA_DECR)
/**< Enable event time-base counter equal to CMPA when the timer is
         decrementing.*/
#define CDD_PWM_ET_INTR_EVT_CNT_EQ_CMPB_INC (CSL_EPWM_ETSEL_INTSEL_CTR_CMPB_INCR)
/**< Enable event: time-base counter equal to CMPB when the timer is
         incrementing.*/
#define CDD_PWM_ET_INTR_EVT_CNT_EQ_CMPB_DEC (CSL_EPWM_ETSEL_INTSEL_CTR_CMPB_DECR)
/**< Enable event: time-base counter equal to CMPB when the timer is
         decrementing.*/
/** @} */

/**
 *  \anchor CDD_PWM_EtIntrPeriod_t
 *  \name EPWM Interrupt (EPWMx_INT) Period Select
 *  @{
 */
/** \brief ePWM Interrupt (EPWMx_INT) Period Select. These values determine how
           many selected events need to occur before an interrupt is
           generated. */
/*
 *Design: MCAL-23833
 */
typedef uint32 CDD_PWM_EtIntrPeriodType;
#define CDD_PWM_ET_INTR_PERIOD_DIS_INTR (CSL_EPWM_ETPS_INTPRD_DISABLE)
/**< Disable the interrupt event counter. No interrupt will be generated. */
#define CDD_PWM_ET_INTR_PERIOD_FIRST_EVT (CSL_EPWM_ETPS_INTPRD_GEN_FIRST_EVT)
/**< Generate an interrupt on the first event. */
#define CDD_PWM_ET_INTR_PERIOD_SECOND_EVT (CSL_EPWM_ETPS_INTPRD_GEN_SECOND_EVT)
/**< Generate an interrupt on the second event. */
#define CDD_PWM_ET_INTR_PERIOD_THIRD_EVT (CSL_EPWM_ETPS_INTPRD_GEN_THIRD_EVT)
/**< Generate an interrupt on the third event. */
/** @} */

/** \brief Mask used to check interrupt status **/
#define CDD_PWM_ETFLG_INT_MASK (CSL_EPWM_ETFLG_INT_MASK)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief      Cdd_Pwm channel type
 */
/*
 *Design: MCAL-23834
 */
typedef uint16 Cdd_Pwm_ChannelType;

/**
 * \brief      Cdd_Pwm Value type
 */
/*
 *Design: MCAL-23835
 */
typedef uint16 Cdd_Pwm_ValueType;

/**
 * \brief      Cdd_Pwm Return Type
 */
/*
 *Design: MCAL-23836
 */
typedef enum
{
    CDD_PWM_CM_IN_REF_INTERVAL = 0,
    /*!< The compare match will occur inside the current Reference Interval. */
    CDD_PWM_CM_OUT_REF_INTERVAL
    /*!< The compare match will not occur inside the current Reference Interval. */
} Cdd_Pwm_ReturnType;

/**
 * \brief      Edge Pin Action type
 */
/*
 *Design: MCAL-23837
 */
typedef enum
{
    CDD_PWM_SET_HIGH = 0,
    /*!<  The channel pin will be set HIGH upon compare match. */
    CDD_PWM_SET_LOW = 1,
    /*!<  The channel pin will be set LOW upon compare match. */
    CDD_PWM_TOGGLE = 2,
    /*!<  The channel pin will be set to the opposite of its current level HIGH upon compare match.
     */
    CDD_PWM_DISABLE = 3
    /*!<  The channel pin will remain at its current level upon compare match. */
} Cdd_Pwm_PinActionType;

/**
 * \brief      PWM StartValleyCapture Type
 *
 *!<details    This enum specifies the start event of the valley capture of  CDD_PWM driver.
 */

typedef enum
{
    Events_0 = 0U,
    Events_1,
    Events_2,
    Events_3,
    Events_4,
    Events_5,
    Events_6,
    Events_7,
    Events_8,
    Events_9,
    Events_10,
    Events_11,
    Events_12
} EPWM_StartValleyCapture;

/** \brief Period type for pwm channels.
 * Fixed periods prohibit changes to the period length with Pwm_SetPeriod( ).
 * PWM_FIXED_PERIOD_SHIFTED type is not supported due to hardware restrictions
 * of the PWM unit.
 */

/** \brief Possible edge notification  */
/*
 *Design: MCAL-23838
 */
typedef enum
{
    CDD_PWM_RISING_EDGE = 1U,
    /**< Rising edges issue notification  */
    CDD_PWM_FALLING_EDGE = 2U,
    /**< Falling edges issue notification */
    CDD_PWM_BOTH_EDGES = 3U
    /**< Both edges issue notification    */
} Cdd_Pwm_EdgeNotificationType;

/**
 * !<brief      Pin State level
 * !<details    Output state of the pin linked to an CDD_PWM channel.
 *
 * !<implements Cdd_Pwm_PinStateType_enumeration
 */
/*
 *Design: MCAL-23839
 */
typedef enum
{
    CDD_PWM_HIGH = 0,
    /** !< Cdd_Pwm Pin level is logic high */
    CDD_PWM_LOW
    /** !< Cdd_Pwm Pin level is logic low */
} Cdd_Pwm_PinStateType;

/**
 * !<brief      Cdd_Pwm Count direction
 * !<details    This enum specifies the count direction for the whole CDD_PWM driver.
 *
 */
/*
 *Design: MCAL-23840
 */
typedef enum
{
    CDD_PWM_UPCOUNTING = 0,
    /** !<Counter in UP Counting */
    CDD_PWM_DOWNCOUNTING,
    /** !<Counter in DOWN Counting. */
    CDD_PWM_UPDOWNCOUNTING,
    /** !<Counter in UP DOWN Counting. */
} Cdd_Pwm_CountDirectionType;

/** \brief EPWM outputs in a single epwm channel. */
/*
 *Design: MCAL-23841
 */
typedef enum CDD_PWM_epwmOutputCh
{
    CDD_PWM_OUTPUT_CH_A = 0U,
    /**< Output channel A. */
    CDD_PWM_OUTPUT_CH_B = 1U,
    /**< Output channel B. */
    CDD_PWM_OUTPUT_CH_BOTH_A_AND_B = 2U
    /**< Both Output channel A and B */
} Cdd_Pwm_OutputChType;

/** \brief Structure holding the TimeBase sub-module configuration parameters */
/*
 *Design: MCAL-23842
 */
typedef struct CDD_PWM_TimebaseCfg_s
{
    uint32 tbClk;
    /**< Time base clock. */
    uint32 pwmtbCounterFreqPrd;
    /**< PWM Time base counter Frequency/Period. */
    uint32 tbCntrDirection;
    /**< Time base counter direction. This can take values from the following
         enum #CDD_PWM_TbCounterDir_t. */
    uint32 enableSynchronization;
    /**< Enable synchronization inside the timebase sub-module.  This can take
         following two values TRUE or FALSE. */
    uint32 cntDirAfterSync;
    /**< Direction of the counter after the sync event is occurred.  This can
         take values from the following enum #CDD_PWM_TbCntDirAftSync_t. */
    uint32 phsCountAfterSync;

    /**< Value of the phase counter to be loaded after the sync event. */
    uint32 syncOutSrc;
    /**< Source of synchronization output signal.  This can take values from the
         following enum #CDD_PWM_TbSyncOutEvt_t. */
} Cdd_Pwm_TimebaseCfgType;

/** \brief Structure holding the Counter Comparator values. */
/*
 *Design: MCAL-23843
 */
typedef struct CDD_PWM_CounterCmpCfg_s
{
    uint32 cmpAValue;
    /**< Counter Comparator A load value. */
    uint32 cmpBValue;
    /**< Counter Comparator B load value. */
} CDD_PWM_CounterCmpCfg;

/** \brief Structure holding the Action Qualifier actions to be taken on the PWM
           output at the specific events. */
/*
 *Design: MCAL-23844
 */
typedef struct CDD_PWM_AqActionCfg_s
{
    uint32 zeroAction;
    /**< Action to be taken when counter equals zero. This can take values from
         the following enum #CDD_PWM_AqAction_t. */
    uint32 prdAction;
    /**< Action to be taken when the counter equals the period. This can take
         values from the following enum #CDD_PWM_AqAction_t. */
    uint32 cmpAUpAction;
    /**< Action to be taken when the counter equals the active CMPA register
         and the counter is incrementing.  This can take values from the
         following enum #CDD_PWM_AqAction_t. */
    uint32 cmpADownAction;
    /**< Action to be taken when the counter equals the active CMPA register
         and the counter is decrementing. This can take values from the
         following enum #CDD_PWM_AqAction_t. */
    uint32 cmpBUpAction;
    /**< Action to be taken when the counter equals the active CMPB register
         and the counter is incrementing. This can take values from the
         following enum #CDD_PWM_AqAction_t. */
    uint32 cmpBDownAction;
    /**< Action to be taken when the time-base counter equals the active CMPB
         register and the counter is decrementing. This can take values from the
         following enum #CDD_PWM_AqAction_t. */
} CDD_PWM_AqActionCfgType;

/** \brief Structure holding the dead band generation sub-module configuration
           parameters. */
/*
 *Design: MCAL-23845
 */
typedef struct CDD_PWM_DeadbandCfg_s
{
    uint32 inputMode;
    /**< Input mode control that selects the input source to the falling-edge
         and rising-edge delay. This can take values from the following
         enum #CDD_PWM_DbInMode_t. */
    uint32 outputMode;
    /**< Output mode control that selectively enable or bypass the dead-band
         generation for the falling-edge and rising-edge delay. This can take
         values from the following enum #CDD_PWM_DbOutMode_t. */
    uint32 polaritySelect;
    /**< Polarity selection control that allows selectively invert one of the
         delayed signals before it is sent out of the dead-band sub-module. This
         can take values from the following enum #CDD_PWM_DbPolSel_t. */
    uint32 risingEdgeDelay;
    /**< Rising edge delay count in cycles. */
    uint32 fallingEdgeDelay;
    /**< Falling edge delay count in cycles. */
} CDD_PWM_DeadbandCfgType;

/** \brief Structure holding the configuration parameters of Chopper
           sub-module. */
/*
 *Design: MCAL-23846
 */
typedef struct CDD_PWM_ChopperCfg_s
{
    uint32 dutyCycle;
    /**< Chopping clock duty cycle. This can take values from the following
         enum #CDD_PWM_ChpDutyCycle_t. */
    uint32 clkFrequency;
    /**< Chopping clock frequency. This can take values from the following
         enum #CDD_PWM_ChpClkFreq_t. */
    uint32 oneShotPulseWidth;
    /**< One shot pulse width: pulse width of first pulse. This can take values
         from the following enum #CDD_PWM_ChpOshtWidth_t. */
} CDD_PWM_ChopperCfgType;

/** \brief Structure holding the trip-zone sub-module configuration
           parameters. */
/*
 *Design: MCAL-23847
 */
typedef struct CDD_PWM_TripzoneCfg_s
{
    uint32 tripAction;
    /**< Action to be taken on Output when trip condition occurs. This can take
         values from the following enum #CDD_PWM_TzTripAction_t. */
    uint32 tripEvtType;
    /**< Type of trip event One Shot or Cycle by cycle. This can take values
         from the following enum #CDD_PWM_TzEvent_t. */
    uint32 tripPin;
    /**< Trip Pin number on which trip condition has to be monitored. */
    uint32 enableTripIntr;
    /**< Enable Trip Zone Interrupt. */
} CDD_PWM_TripzoneCfgType;

/** \brief Structure holding the Event Trigger Sub-Module configuration
           parameters. */

/*
 *Design: MCAL-23848
 */
typedef struct CDD_PWM_EtCfg_s
{
    uint32 intrEvtSource;
    /**< Event which is the source of the interrupt. This can take values from
         the following enum #CDD_PWM_EtIntrEvt_t. */
    uint32 intrPrd;
    /**< Interrupt period which determine how many selected events need to occur
         before an interrupt is generated. This can take values from the
         following enum #CDD_PWM_EtIntrPeriod_t. */
} CDD_PWM_EtCfgType;

/*!<   Notification callback function pointer  */
typedef void (*Cdd_Pwm_NotifyFuncType)(void);
typedef void (*Cdd_Pwm_TzNotifyFuncType)(void);

/*
 *Design: MCAL-23849
 */
/*!< Channel Structure.  */
typedef struct Cdd_Pwm_channelParametertype_s
{
    Cdd_Pwm_ChannelType  ChannelNumber;
    /*!<   PWM Channel Number.  */
    Cdd_Pwm_ValueType    Period;
    /*!<   PWM Channel Period Value.  */
    uint32               DutyCycle;
    /*!<   PWM Channel DutyCycle Value.  */
    uint16               Phase;
    /*!<   PWM Channel Phase Count Value.  */
    Cdd_Pwm_OutputChType Output;
    /*!<   PWM Channel Output . */
} Cdd_Pwm_channelParametertype;

/*!<   Timer Base of Structure.  */
/*
 *Design: MCAL-23850
 */
typedef struct Cdd_Pwm_timerBaseConfigType_s
{
    boolean                channelPwmTimerBasePeriodGlobalLoad;
    boolean                channelPwmEnablePhaseShift;
    /**< CDD_PWM timer base period . */
    EPWM_EmulationMode     channelPwmEmulationMode;
    /**< Emulation mode of timer . */
    EPWM_ClockDivider      channelPwmClockDivider;
    EPWM_HSClockDivider    channelPwmHSClockDivider;
    uint32                 channelPwmTbPeriod;
    uint32                 channelPwmTbPeriodInitValue;
    EPWM_TimeBaseCountMode channelPwmCounterMode;
    uint32                 channelPwmEnablePhaseShiftValue;
    EPWM_PeriodLoadMode    channelPwmPeriodLoadMode;
    EPWM_CurrentLink       channelPwmTbprdlink;
} Cdd_Pwm_timerBaseConfigType;

/** \brief EPWM outputs in a single epwm channel. */
/*
 *Design: MCAL-23851
 */
typedef enum CddPwmCounterBlockCmpA_s
{
    CDD_PWM_CMP_A = 0U,
    /**< Counter A. */
} CddPwmCounterBlockCmpA;

/** \brief EPWM outputs in a single epwm channel. */
/*
 *Design: MCAL-23852
 */
typedef enum CddPwmCounterBlockCmpB_s
{
    CDD_PWM_CMP_B = 0U,
    /**< Counter B. */
} CddPwmCounterBlockCmpB;

/** \brief EPWM outputs in a single epwm channel. */
/*
 *Design: MCAL-23853
 */
typedef enum CddPwmCounterBlockCmpC_s
{
    CDD_PWM_CMP_C = 0U,
    /**< Counter C. */
} CddPwmCounterBlockCmpC;

/** \brief EPWM outputs in a single epwm channel. */
/*
 *Design: MCAL-23854
 */
typedef enum CddPwmCounterBlockCmpD_s
{
    CDD_PWM_CMP_D = 0U,
    /**< Counter D. */
} CddPwmCounterBlockCmpD;

/*!<  Counter Compare of Structure.  */
/*
 *Design: MCAL-23855
 */
typedef struct Cdd_Pwm_CompareType_s
{
    CddPwmCounterBlockCmpA      channelCddPwmCounterBlockA;
    uint32                      channelCddPwmCompareValueCmpA;
    boolean                     channelCddPwmCounterCompareGlobalLoadCmpA;
    boolean                     channelCddPwmCounterCompareShadowModeCmpA;
    EPWM_CounterCompareLoadMode channelCddPwmCounterCompareShadowEventCmpA;
    EPWM_CurrentLink            channelCddPwmTbprdlinkCmpA;

    CddPwmCounterBlockCmpB      channelCddPwmCounterBlockB;
    uint32                      channelCddPwmCompareValueCmpB;
    boolean                     channelCddPwmCounterCompareGlobalLoadCmpB;
    boolean                     channelCddPwmCounterCompareShadowModeCmpB;
    EPWM_CounterCompareLoadMode channelCddPwmCounterCompareShadowEventCmpB;
    EPWM_CurrentLink            channelCddPwmTbprdlinkCmpB;

    CddPwmCounterBlockCmpC      channelCddPwmCounterBlockC;
    uint32                      channelCddPwmCompareValueCmpC;
    boolean                     channelCddPwmCounterCompareGlobalLoadCmpC;
    boolean                     channelCddPwmCounterCompareShadowModeCmpC;
    EPWM_CounterCompareLoadMode channelCddPwmCounterCompareShadowEventCmpC;
    EPWM_CurrentLink            channelCddPwmTbprdlinkCmpC;

    CddPwmCounterBlockCmpD      channelCddPwmCounterBlockD;
    uint32                      channelCddPwmCompareValueCmpD;
    boolean                     channelCddPwmCounterCompareGlobalLoadCmpD;
    boolean                     channelCddPwmCounterCompareShadowModeCmpD;
    EPWM_CounterCompareLoadMode channelCddPwmCounterCompareShadowEventCmpD;
    EPWM_CurrentLink            channelCddPwmTbprdlinkCmpD;
} Cdd_Pwm_compareType;

/*!<   Timer Base Sync of Structure.  */
/*
 *Design: MCAL-23856
 */
typedef struct Cdd_Pwm_TimerBaseSync_s
{
    boolean                    channelForceSync;
    boolean                    channelSyncOutPulseOnSoftware;
    boolean                    channelSyncOutPulseOnCntrZero;
    boolean                    channelSyncOutPulseOnCntCmpB;
    boolean                    channelSyncOutPulseOnCntCmpC;
    boolean                    channelSyncOutPulseOnCntCmpD;
    boolean                    channelSyncOutPulseOnDCAEVT1SYNC;
    boolean                    channelSyncOutPulseOnDCBEVT1SYNC;
    EPWM_OneShotSyncOutTrigger channelOneShotSyncOutTrigger;
    EPWM_CurrentLink           channelTbprdlink;
    boolean                    channelSyncOutPulseOnALL;
    EPWM_SyncInPulseSource     channelSyncOutPulseSource;
} Cdd_Pwm_timerBaseSyncType;

#define CDD_PWM_E_A 0U
#define CDD_PWM_E_B 1U

/*!<   Action Qualifier of Structure.  */
/*
 *Design: MCAL-23857
 */
typedef struct Cdd_Pwm_ActionConfigType_s
{
    uint32                            channelPwmOutptEPWMA;
    boolean                           channelPwmActionGlobalLoadEPWMA;
    boolean                           channelPwmActionShadowModeEPWMA;
    EPWM_ActionQualifierLoadMode      channelPwmActionShadowEventEPWMA;
    EPWM_ActionQualifierTriggerSource channelPwmT1TriggerSourceEPWMA;
    EPWM_ActionQualifierTriggerSource channelPwmT2TriggerSourceEPWMA;
    EPWM_ActionQualifierOutput        channelPwmActionQualifierOneTimeSwOutputEPWMA;
    EPWM_ActionQualifierSWOutput      channelPwmActionQualifierContinuousSwOutputEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseZEROEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebasePERIODEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseUPCMPAEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseDOWNCMPAEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseUPCMPBEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseDOWNCMPBEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT1COUNTUPEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT1COUNTDOWNEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT2COUNTUPEPWMA;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT2COUNTDOWNEPWMA;

    uint32                            channelPwmOutptEPWMB;
    boolean                           channelPwmActionGlobalLoadEPWMB;
    boolean                           channelPwmActionShadowModeEPWMB;
    EPWM_ActionQualifierLoadMode      channelPwmActionShadowEventEPWMB;
    EPWM_ActionQualifierTriggerSource channelPwmT1TriggerSourceEPWMB;
    EPWM_ActionQualifierTriggerSource channelPwmT2TriggerSourceEPWMB;
    EPWM_ActionQualifierOutput        channelPwmActionQualifierOneTimeSwOutputEPWMB;
    EPWM_ActionQualifierSWOutput      channelPwmActionQualifierContinuousSwOutputEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseZEROEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebasePERIODEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseUPCMPAEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseDOWNCMPAEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseUPCMPBEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnTimebaseDOWNCMPBEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT1COUNTUPEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT1COUNTDOWNEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT2COUNTUPEPWMB;
    EPWM_ActionQualifierOutput        channelPwmAqOutputOnT2COUNTDOWNEPWMB;
} Cdd_Pwm_actionConfigType;

/*!<   CDD PWM Event Trigger of Structure.  */
/*
 *Design: MCAL-23858
 */
typedef struct Cdd_Pwm_EventConfigType_s
{
    boolean channelPwmForceEventValue;
    boolean channelPwmEnableEventCountInitialValue;
    uint16  channelPwmEventCountInitialValue;
    uint16  channelPwmInterruptCount;
    uint16  channelPwmInterruptEventSources;
    uint16  channelPwmInterruptMixedSources;
} Cdd_Pwm_eventConfigType;

/*!<   CDD PWM Adc Event Trigger of Structure.  */
/*
 *Design: MCAL-23859
 */
typedef struct Cdd_Pwm_AdcEventTriggerType_s
{
    boolean                         channelPwmSocAEvent;
    boolean                         channelPwmSocAForceEventValue;
    boolean                         channelPwmSocAEventCountInitialValueEnable;
    uint16                          channelPwmSocAEventCountInitialValue;
    uint16                          channelPwmSocAInterruptCount;
    EPWM_ADCStartOfConversionSource channelPwmSocAInterruptEventSources;
    uint16                          channelPwmSocAMixedSources;

    boolean                         channelPwmSocBEvent;
    boolean                         channelPwmSocBForceEventValue;
    boolean                         channelPwmSocBEventCountInitialValueEnable;
    uint16                          channelPwmSocBEventCountInitialValue;
    uint16                          channelPwmSocBInterruptCount;
    EPWM_ADCStartOfConversionSource channelPwmSocBInterruptEventSources;
    uint16                          channelPwmSocBMixedSources;
} Cdd_Pwm_adcEventTriggerType;

/*!<   Trip Zone of Structure.  */
/*
 *Design: MCAL-23860
 */
typedef struct Cdd_Pwm_TripZoneType_s
{
    boolean channelPwmAdvancedTripZoneAction;

    EPWM_TripZoneAction         channelPwmEvent;
    EPWM_TripZoneAction         channelPwmTZAEvent;
    EPWM_TripZoneAction         channelPwmTZBEvent;
    EPWM_TripZoneAdvancedAction channelPwmTZAAdvUEvent;
    EPWM_TripZoneAdvancedAction channelPwmTZAAdvDEvent;
    EPWM_TripZoneAdvancedAction channelPwmTZBAdvUEvent;
    EPWM_TripZoneAdvancedAction channelPwmTZBAdvDEvent;
    EPWM_TripZoneAction         channelPwmDCAEVT1Event;
    EPWM_TripZoneAdvancedAction channelPwmDCAEVT1AdvUEvent;
    EPWM_TripZoneAdvancedAction channelPwmDCAEVT1AdvDEvent;
    EPWM_TripZoneAction         channelPwmDCAEVT2Event;
    EPWM_TripZoneAdvancedAction channelPwmDCAEVT2AdvUEvent;
    EPWM_TripZoneAdvancedAction channelPwmDCAEVT2AdvDEvent;
    EPWM_TripZoneAction         channelPwmDCBEVT1Event;
    EPWM_TripZoneAdvancedAction channelPwmDCBEVT1AdvUEvent;
    EPWM_TripZoneAdvancedAction channelPwmDCBEVT1AdvDEvent;
    EPWM_TripZoneAction         channelPwmDCBEVT2Event;
    EPWM_TripZoneAdvancedAction channelPwmDCBEVT2AdvUEvent;
    EPWM_TripZoneAdvancedAction channelPwmDCBEVT2AdvDEvent;

    boolean channelPwmOneShotTZ1;
    boolean channelPwmOneShotTZ2;
    boolean channelPwmOneShotTZ3;
    boolean channelPwmOneShotTZ4;
    boolean channelPwmOneShotTZ5;
    boolean channelPwmOneShotTZ6;
    boolean channelPwmOneShotDCAEVT1;
    boolean channelPwmOneShotDCBEVT1;

    boolean channelPwmCBCTZ1;
    boolean channelPwmCBCTZ2;
    boolean channelPwmCBCTZ3;
    boolean channelPwmCBCTZ4;
    boolean channelPwmCBCTZ5;
    boolean channelPwmCBCTZ6;
    boolean channelPwmDCAEVT2;
    boolean channelPwmDCBEVT2;

    boolean channelPwmTZCBCInterrupt;
    boolean channelPwmTZOneShotInterrupt;
    boolean channelPwmDCAEVT1Interrupt;
    boolean channelPwmDCAEVT2Interrupt;
    boolean channelPwmDCBEVT1Interrupt;
    boolean channelPwmDCBEVT2Interrupt;

    EPWM_CycleByCycleTripZoneClearMode channelPwmCycleByCycleTripZoneClearMode;
} Cdd_Pwm_tripZoneType;

/*!<   Digital Compare Structure.  */
typedef struct Cdd_Pwm_DigitalCompareType_s
{
    EPWM_DigitalCompareTripInput           channelPwmDCAHigh;
    EPWM_DigitalCompareTripInput           channelPwmDCALow;
    EPWM_DigitalCompareTripInput           channelPwmDCBHigh;
    EPWM_DigitalCompareTripInput           channelPwmDCBLow;
    EPWM_TripZoneDigitalCompareOutputEvent channelPwmDCAOutputHigh1A;
    EPWM_TripZoneDigitalCompareOutputEvent channelPwmDCAOutputHigh2A;
    EPWM_TripZoneDigitalCompareOutputEvent channelPwmDCBOutputHigh1A;
    EPWM_TripZoneDigitalCompareOutputEvent channelPwmDCBOutputHigh2A;
    boolean                                channelPwmAdcSocEventA;
    boolean                                channelPwmSyncOutEventA;
    boolean                                channelPwmAdcSocEventB;
    boolean                                channelPwmSyncOutEventB;
    EPWM_DigitalCompareSyncMode            channelPwmSyncModeAEVT1;
    EPWM_DigitalCompareEventSource         channelPwmSignalSoureAEVT1;
    EPWM_DigitalCompareSyncMode            channelPwmSyncModeBEVT1;
    EPWM_DigitalCompareEventSource         channelPwmSignalSoureBEVT1;
    EPWM_DigitalCompareCBCLatchMode        channelPwmCBCLatchModeDCAEVT1;
    EPWM_DigitalCompareCBCLatchClearEvent  channelPwmCBCLatchClearModeDCAEVT1;
    EPWM_DigitalCompareCBCLatchMode        channelPwmCBCLatchModeDCBEVT1;
    EPWM_DigitalCompareCBCLatchClearEvent  channelPwmCBCLatchClearModeDCBEVT1;
    EPWM_DigitalCompareSyncMode            channelPwmSyncModeAEVT2;
    EPWM_DigitalCompareEventSource         channelPwmSignalSoureAEVT2;
    EPWM_DigitalCompareSyncMode            channelPwmSyncModeBEVT2;
    EPWM_DigitalCompareEventSource         channelPwmSignalSoureBEVT2;
    EPWM_DigitalCompareCBCLatchMode        channelPwmCBCLatchModeDCAEVT2;
    EPWM_DigitalCompareCBCLatchClearEvent  channelPwmCBCLatchClearModeDCAEVT2;
    EPWM_DigitalCompareCBCLatchMode        channelPwmCBCLatchModeDCBEVT2;
    EPWM_DigitalCompareCBCLatchClearEvent  channelPwmCBCLatchClearModeDCBEVT2;
    EPWM_DigitalCompareFilterInput         channelPwmDcFilterInputEventSource;
    boolean                                channelPwmCddPwmBlankingWindow;
    EPWM_DigitalCompareBlankingPulse       channelPwmCddPwmBlankingWindowStartEvent;
    uint16                                 channelPwmCddPwmBlankingWindowOffset;
    uint16                                 channelPwmCddPwmBlankingWindowLength;
    uint8                                  channelPwmCddPwmBlankingWindowMixedEvent;
    boolean                                channelPwmCddPwmDCCounterCapture;
    boolean                                channelPwmCddPwmDCCounterCaptureShadowMode;
    boolean                                channelPwmCddPwmUseEdgeFilter;
    EPWM_DigitalCompareEdgeFilterMode      channelPwmCddPwmEdgeFilterMode;
    EPWM_DigitalCompareEdgeFilterEdgeCount channelPwmCddPwmEdgeFilterCount;
    boolean                                channelPwmCddPwmEdgeFilterValleyCapture;
    boolean                                channelPwmDelayedOutputEdgeFilter;
    EPWM_ValleyTriggerSource               channelPwmEdgeFilterCounterCaptureSignal;
    boolean                                channelPwmStartValleyCaptureLogic;
    EPWM_StartValleyCapture                channelPwmStartValleyCapture;
    EPWM_StartValleyCapture                channelPwmStopValleyCapture;
    uint16                                 channelPwmSoftwareValleyDelayValue;
    EPWM_ValleyDelayMode                   channelPwmValleyDelayDivider;
} Cdd_Pwm_DigitalCompareType;

/*!<   Dead Band of Structure.  */
/*
 *Design: MCAL-23861
 */
typedef struct Cdd_Pwm_DeadBandType_s
{
    EPWM_DeadBandClockMode       channelDeadBandClockMode;
    boolean                      channelDeadBandGlobalLoad;
    boolean                      channelDeadBandShadowMode;
    boolean                      channelRedGlobalLoad;
    boolean                      channelRedShadowMode;
    boolean                      channelFedGlobalLoad;
    boolean                      channelFedShadowMode;
    boolean                      channelREDEnable;
    boolean                      channelFEDEnable;
    boolean                      channelDeadBandSwapOutputA;
    boolean                      channelDeadBandSwapOutputB;
    uint32                       channelREDDelayValue;
    uint32                       channelFEDDelayValue;
    EPWM_RisingEdgeDelayLoadMode channelDeadBandDelayLoadMode;
    EPWM_RisingEdgeDelayLoadMode channelPwmRedDelayLoadMode;
    EPWM_RisingEdgeDelayLoadMode channelPwmFedDelayLoadMode;
    EPWM_DeadBandPolarity        channelPwmRedBandPolarity;
    EPWM_DeadBandPolarity        channelPwmFedBandPolarity;
    uint32                       channelPwmREDDelayInput;
    uint32                       channelPwmFEDDelayInput;
} Cdd_Pwm_deadBandType;

/*!<   Chopper of Structure.  */
/*
 *Design: MCAL-23862
 */
typedef struct Cdd_Pwm_ChopperType_s
{
    boolean channelChopperEnable;
    uint8   channelChopperDuty;
    uint8   channelChopperFreqency;
    uint16  channelChopperFirstPulseWidth;
} Cdd_Pwm_chopperType;

/*!<   Structure of High Resolution PWM  */
/*
 *Design: MCAL-23863
 */
typedef struct Cdd_Pwm_HrPwmType_s
{
    boolean           channelHrPwmEnable;
    boolean           channelAutoHRMStepScalingEnable;
    HRPWM_MEPCtrlMode channelHrCtrlModeEPWMA;
    HRPWM_MEPCtrlMode channelHrCtrlModeEPWMB;

    /* HPWM  Duty , Period  and Phase control */
    HRPWM_MEPEdgeMode channelHrSelEdgeModeEPWMA;
    uint32            channelHrCmpHRPWMA;
    HRPWM_LoadMode    channelHrShadowActiveLoadPwmA;

    HRPWM_MEPEdgeMode channelHrSelEdgeModeEPWMB;
    uint32            channelHrCmpHRPWMB;
    HRPWM_LoadMode    channelHrShadowActiveLoadPwmB;

    boolean channelHrPeriodCtrlEnable;
    uint32  channelHrPeriod;

    boolean               channelHrPhaseCtrlEnable;
    uint32                channelHrPhase;
    HRPWM_SyncPulseSource channelPwmSyncSelect;

    /* HPWM  Deadband Control */
    HRPWM_MEPDeadBandEdgeMode channelHrDeadbandEdgeMode;
    uint32                    channelHrRisEdgeDelay;
    HRPWM_LoadMode            channelHrDbRisShadowActiveLoad;

    uint32         channelHrFalEdgeDelay;
    HRPWM_LoadMode channelHrDbFalShadowActiveLoad;

    boolean              channelHrSwapOutputCtrl;
    HRPWM_ChannelBOutput channelHrOutputCtrl;

} Cdd_Pwm_hrPwmType;

/*!<   ADC SOC Structure.  */
/*
 *Design: MCAL-23864
 */
typedef struct Cdd_Pwm_AdcSocType_s
{
    boolean                          channelEnable;
    /*!<   SOC Enable or Disable.  */
    CDD_PWM_ADCStartOfConversionType adcSocSource;
    /*!<   SOCA / SOCB.  */
    EPWM_ADCStartOfConversionSource  adcInterruptSource;
    /*!<   ADC Interrupt Source.  */
    uint32                           adcMixedInterruptSource;
    /*!<   ADC Mixed Interrupt Source.  */
} Cdd_Pwm_AdcSocType;

/*!<   Interrupt of Structure.  */
/*
 *Design: MCAL-23865
 */
typedef struct Cdd_Pwm_InterruptType_s
{
    Cdd_Pwm_EdgeNotificationType EdgeSource;
    /*!<   EdgeSource for PWM module.  */
    uint32                       interruptSource;
    /*!<   Interrupt Source.  */
    uint32                       mixedInterruptSource;
    /*!<   Mixed Interrupt Source.  */
} Cdd_Pwm_InterruptType;

/*
 *Design: MCAL-23866
 */
typedef struct
{
#if (CDD_PWM_NOTIFICATION_SUPPORTED == STD_ON)
    Cdd_Pwm_NotifyFuncType notificationHandler;
    /**< Notification handler. */
#endif /* (CDD_PWM_NOTIFICATION_SUPPORTED == STD_ON) */

    Cdd_Pwm_TzNotifyFuncType notificationTzHandler;
    /**< Notification handler. */

    VAR(uint32, CDD_PWM_VAR) baseaddr;
    /**< Base Address of CDD_PWM channel. */

    VAR(uint32, CDD_PWM_VAR) channelID;
    /**< CDD_PWM Channel Logical Channel ID. */

    VAR(uint32, CDD_PWM_VAR) channelHwID;
    /**< CDD_PWM Channel Physical Channel ID. */

    VAR(Cdd_Pwm_OutputChType, CDD_PWM_VAR) outputCh;
    /**< CDD_PWM Channel Physical Channel ID. */

    VAR(Cdd_Pwm_PinStateType, CDD_PWM_VAR) polarity;
    /**< CDD_PWM Pin State Channel ID. */

    P2CONST(Cdd_Pwm_timerBaseConfigType, CDD_PWM_CODE, CDD_PWM_VAR) channelTimerBase;
    /**< Timer Base Parameter refernce */

    P2CONST(Cdd_Pwm_compareType, CDD_PWM_CODE, CDD_PWM_VAR) channelCounterCompare;
    /**< Counter Compare Parameter refernce */

    P2CONST(Cdd_Pwm_timerBaseSyncType, CDD_PWM_CODE, CDD_PWM_VAR) channelTimerBaseSync;
    /**< Timer Base Parameter refernce */

    P2CONST(Cdd_Pwm_actionConfigType, CDD_PWM_CODE, CDD_PWM_VAR) channelActionQualifier;
    /**< Action Qualifier Parameter refernce */

    P2CONST(Cdd_Pwm_eventConfigType, CDD_PWM_CODE, CDD_PWM_VAR) channelEventTrigger;
    /**< Event Trigger Parameter refernce */

    P2CONST(Cdd_Pwm_adcEventTriggerType, CDD_PWM_CODE, CDD_PWM_VAR) channelAdcEventTrigger;
    /**< Adc Event Trigger Parameter refernce */

    P2CONST(Cdd_Pwm_tripZoneType, CDD_PWM_CODE, CDD_PWM_VAR) channelTripZone;
    /**< Trip Zone Parameter refernce */

    P2CONST(Cdd_Pwm_DigitalCompareType, CDD_PWM_CODE, CDD_PWM_VAR) channelDigitalCompare;
    /**< DigitalCompare Parameter refernce */

    P2CONST(Cdd_Pwm_deadBandType, CDD_PWM_CODE, CDD_PWM_VAR) channelDeadBand;
    /**< Dead Band Parameter refernce */

    P2CONST(Cdd_Pwm_chopperType, CDD_PWM_CODE, CDD_PWM_VAR) channelChopper;
    /**< Chopper Parameter refernce */

    P2CONST(Cdd_Pwm_hrPwmType, CDD_PWM_CODE, CDD_PWM_VAR) channelHrPwm;
    /**< HRPWM Parameter reference */

} Cdd_Pwm_ChannelConfigType;

/*!<  Pwm configuration structure */
/*
 *Design: MCAL-23867
 */
typedef struct Cdd_Pwm_ConfigType_s
{
    Cdd_Pwm_ChannelConfigType chCfg[CDD_PWM_MAX_NUM_CHANNELS];
    /**< Channel configurations */
} Cdd_Pwm_ConfigType;

/*!<  Pwm Channel Object structure */
/*
 *Design: MCAL-23868
 */
typedef struct
{
#if (CDD_PWM_NOTIFICATION_SUPPORTED == STD_ON)
    Cdd_Pwm_NotifyFuncType notificationHandler;
    /**< Notification handler. */
#endif /* (CDD_PWM_NOTIFICATION_SUPPORTED == STD_ON) */

    Cdd_Pwm_TzNotifyFuncType notificationTzHandler;
    /**< Notification handler. */

    VAR(uint32, CDD_PWM_VAR) baseaddr;
    /**< Base Address of CDD_PWM channel. */

    VAR(uint32, CDD_PWM_VAR) channelID;
    /**< CDD_PWM Channel Logical Channel ID. */

    VAR(uint32, CDD_PWM_VAR) channelHwID;
    /**< CDD_PWM Channel Physical Channel ID. */

    VAR(Cdd_Pwm_OutputChType, CDD_PWM_VAR) outputCh;
    /**< CDD_PWM Channel Physical Channel ID. */

    VAR(Cdd_Pwm_PinStateType, CDD_PWM_VAR) polarity;
    /**< CDD_PWM Pin State Channel ID. */

    VAR(Cdd_Pwm_timerBaseConfigType, CDD_PWM_CODE) channelTimerBase;
    /**< Timer Base Parameter refernce */

    VAR(Cdd_Pwm_compareType, CDD_PWM_CODE) channelCounterCompare;
    /**< Counter Compare Parameter refernce */

    VAR(Cdd_Pwm_timerBaseSyncType, CDD_PWM_CODE) channelTimerBaseSync;
    /**< Timer Base Parameter refernce */

    VAR(Cdd_Pwm_actionConfigType, CDD_PWM_CODE) channelActionQualifier;
    /**< Action Qualifier Parameter refernce */

    VAR(Cdd_Pwm_eventConfigType, CDD_PWM_CODE) channelEventTrigger;
    /**< Event Trigger Parameter refernce */

    VAR(Cdd_Pwm_adcEventTriggerType, CDD_PWM_CODE) channelAdcEventTrigger;
    /**< Adc Event Trigger Parameter refernce */

    VAR(Cdd_Pwm_tripZoneType, CDD_PWM_CODE) channelTripZone;
    /**< Trip Zone Parameter refernce */

    VAR(Cdd_Pwm_DigitalCompareType, CDD_PWM_CODE) channelDigitalCompare;
    /**< DigitalCompare Parameter refernce */

    VAR(Cdd_Pwm_deadBandType, CDD_PWM_CODE) channelDeadBand;
    /**< Dead Band Parameter refernce */

    VAR(Cdd_Pwm_chopperType, CDD_PWM_CODE) channelChopper;
    /**< Chopper Parameter refernce */

    VAR(Cdd_Pwm_hrPwmType, CDD_PWM_CODE) channelHrPwm;
    /**< HRPWM Parameter reference */

    boolean channelNotifyActiveFlag;
    /**< Channel Notification status */

    boolean channelForcedIdle;
    /**< Channel forced sate */

    Cdd_Pwm_PinStateType idleState;
    /**< Idle State of PWM. */

    boolean channelState;
    /**< Channel status */

} Cdd_Pwm_ChObjType;

/* @} */

#if (STD_ON == CDD_PWM_REGISTER_READBACK_API)
/**
 *  \brief PWM register readback structure
 */
/*
 *Design: MCAL-23869
 */
typedef struct
{
    /*
     * EPWM related registers
     */
    uint16 pwmTbCtl1;
    uint16 pwmTbCtl2;
    /**< Time base control register */
} Cdd_Pwm_RegisterReadbackType;

#endif /* #if (STD_ON == CDD_PWM_REGISTER_READBACK_API) */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_PWM_H_ */

/* @} */
