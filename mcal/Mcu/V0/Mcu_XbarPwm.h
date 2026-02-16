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
 *  \file     Mcu_XbarPwm.h
 *
 *  \brief    This file contains interface header for PWM XBAR module
 *
 */

#ifndef MCU_XBAR_PWM_H_
#define MCU_XBAR_PWM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * Interface macros
 */
/** \brief PWMXBAR Number of outputs */
#define MCU_PWM_XBAR_NUM_OUTPUT (30U)
/** \brief PWMXBAR Number of groups */
#define MCU_PWM_XBAR_NUM_GROUPS (9U)

/*
 * PWMXBAR Input Group Masks
 */
/** \brief PWMXBAR none input mask - pass when nothing has to be selected for the group */
#define MCU_PWM_XBAR_GROUP_MASK_NONE (0x00000000U)

/**
 *  \name MCU_PWM_XBAR_GROUP0_MASKS PWMXBAR Input Group0 Masks
 *
 *  Bitwise OR of this macro to be passed to group0_mask
 *  @{
 */
#define MCU_PWM_XBAR_CMPSSA0_CTRIPL (0x00000001U)
#define MCU_PWM_XBAR_CMPSSA0_CTRIPH (0x00000002U)
#define MCU_PWM_XBAR_CMPSSA1_CTRIPL (0x00000004U)
#define MCU_PWM_XBAR_CMPSSA1_CTRIPH (0x00000008U)
#define MCU_PWM_XBAR_CMPSSA2_CTRIPL (0x00000010U)
#define MCU_PWM_XBAR_CMPSSA2_CTRIPH (0x00000020U)
#define MCU_PWM_XBAR_CMPSSA3_CTRIPL (0x00000040U)
#define MCU_PWM_XBAR_CMPSSA3_CTRIPH (0x00000080U)
#define MCU_PWM_XBAR_CMPSSA4_CTRIPL (0x00000100U)
#define MCU_PWM_XBAR_CMPSSA4_CTRIPH (0x00000200U)
#define MCU_PWM_XBAR_CMPSSA5_CTRIPL (0x00000400U)
#define MCU_PWM_XBAR_CMPSSA5_CTRIPH (0x00000800U)
#define MCU_PWM_XBAR_CMPSSA6_CTRIPL (0x00001000U)
#define MCU_PWM_XBAR_CMPSSA6_CTRIPH (0x00002000U)
#define MCU_PWM_XBAR_CMPSSA7_CTRIPL (0x00004000U)
#define MCU_PWM_XBAR_CMPSSA7_CTRIPH (0x00008000U)
#define MCU_PWM_XBAR_CMPSSA8_CTRIPL (0x00010000U)
#define MCU_PWM_XBAR_CMPSSA8_CTRIPH (0x00020000U)
#define MCU_PWM_XBAR_CMPSSA9_CTRIPL (0x00040000U)
#define MCU_PWM_XBAR_CMPSSA9_CTRIPH (0x00080000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP1_MASKS PWMXBAR Input Group1 Masks
 *
 *  Bitwise OR of this macro to be passed to group1_mask
 *  @{
 */
#define MCU_PWM_XBAR_CMPSSB0_CTRIPL (0x00000001U)
#define MCU_PWM_XBAR_CMPSSB0_CTRIPH (0x00000002U)
#define MCU_PWM_XBAR_CMPSSB1_CTRIPL (0x00000004U)
#define MCU_PWM_XBAR_CMPSSB1_CTRIPH (0x00000008U)
#define MCU_PWM_XBAR_CMPSSB2_CTRIPL (0x00000010U)
#define MCU_PWM_XBAR_CMPSSB2_CTRIPH (0x00000020U)
#define MCU_PWM_XBAR_CMPSSB3_CTRIPL (0x00000040U)
#define MCU_PWM_XBAR_CMPSSB3_CTRIPH (0x00000080U)
#define MCU_PWM_XBAR_CMPSSB4_CTRIPL (0x00000100U)
#define MCU_PWM_XBAR_CMPSSB4_CTRIPH (0x00000200U)
#define MCU_PWM_XBAR_CMPSSB5_CTRIPL (0x00000400U)
#define MCU_PWM_XBAR_CMPSSB5_CTRIPH (0x00000800U)
#define MCU_PWM_XBAR_CMPSSB6_CTRIPL (0x00001000U)
#define MCU_PWM_XBAR_CMPSSB6_CTRIPH (0x00002000U)
#define MCU_PWM_XBAR_CMPSSB7_CTRIPL (0x00004000U)
#define MCU_PWM_XBAR_CMPSSB7_CTRIPH (0x00008000U)
#define MCU_PWM_XBAR_CMPSSB8_CTRIPL (0x00010000U)
#define MCU_PWM_XBAR_CMPSSB8_CTRIPH (0x00020000U)
#define MCU_PWM_XBAR_CMPSSB9_CTRIPL (0x00040000U)
#define MCU_PWM_XBAR_CMPSSB9_CTRIPH (0x00080000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP2_MASKS PWMXBAR Input Group2 Masks
 *
 *  Bitwise OR of this macro to be passed to group2_mask
 *  @{
 */
#define MCU_PWM_XBAR_SD0_FILT0_EVT1  (0x00000001U)
#define MCU_PWM_XBAR_SD0_FILT0_EVT2  (0x00000002U)
#define MCU_PWM_XBAR_SD0_FILT0_CMPHZ (0x00000004U)
#define MCU_PWM_XBAR_SD0_FILT1_EVT1  (0x00000008U)
#define MCU_PWM_XBAR_SD0_FILT1_EVT2  (0x00000010U)
#define MCU_PWM_XBAR_SD0_FILT1_CMPHZ (0x00000020U)
#define MCU_PWM_XBAR_SD0_FILT2_EVT1  (0x00000040U)
#define MCU_PWM_XBAR_SD0_FILT2_EVT2  (0x00000080U)
#define MCU_PWM_XBAR_SD0_FILT2_CMPHZ (0x00000100U)
#define MCU_PWM_XBAR_SD0_FILT3_EVT1  (0x00000200U)
#define MCU_PWM_XBAR_SD0_FILT3_EVT2  (0x00000400U)
#define MCU_PWM_XBAR_SD0_FILT3_CMPHZ (0x00000800U)
#define MCU_PWM_XBAR_SD1_FILT0_EVT1  (0x00001000U)
#define MCU_PWM_XBAR_SD1_FILT0_EVT2  (0x00002000U)
#define MCU_PWM_XBAR_SD1_FILT0_CMPHZ (0x00004000U)
#define MCU_PWM_XBAR_SD1_FILT1_EVT1  (0x00008000U)
#define MCU_PWM_XBAR_SD1_FILT1_EVT2  (0x00010000U)
#define MCU_PWM_XBAR_SD1_FILT1_CMPHZ (0x00020000U)
#define MCU_PWM_XBAR_SD1_FILT2_EVT1  (0x00040000U)
#define MCU_PWM_XBAR_SD1_FILT2_EVT2  (0x00080000U)
#define MCU_PWM_XBAR_SD1_FILT2_CMPHZ (0x00100000U)
#define MCU_PWM_XBAR_SD1_FILT3_EVT1  (0x00200000U)
#define MCU_PWM_XBAR_SD1_FILT3_EVT2  (0x00400000U)
#define MCU_PWM_XBAR_SD1_FILT3_CMPHZ (0x00800000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP3_MASKS PWMXBAR Input Group3 Masks
 *
 *  Bitwise OR of this macro to be passed to group3_mask
 *  @{
 */
#define MCU_PWM_XBAR_ADC0_EVT1 (0x00000001U)
#define MCU_PWM_XBAR_ADC0_EVT2 (0x00000002U)
#define MCU_PWM_XBAR_ADC0_EVT3 (0x00000004U)
#define MCU_PWM_XBAR_ADC0_EVT4 (0x00000008U)
#define MCU_PWM_XBAR_ADC1_EVT1 (0x00000010U)
#define MCU_PWM_XBAR_ADC1_EVT2 (0x00000020U)
#define MCU_PWM_XBAR_ADC1_EVT3 (0x00000040U)
#define MCU_PWM_XBAR_ADC1_EVT4 (0x00000080U)
#define MCU_PWM_XBAR_ADC2_EVT1 (0x00000100U)
#define MCU_PWM_XBAR_ADC2_EVT2 (0x00000200U)
#define MCU_PWM_XBAR_ADC2_EVT3 (0x00000400U)
#define MCU_PWM_XBAR_ADC2_EVT4 (0x00000800U)
#define MCU_PWM_XBAR_ADC3_EVT1 (0x00001000U)
#define MCU_PWM_XBAR_ADC3_EVT2 (0x00002000U)
#define MCU_PWM_XBAR_ADC3_EVT3 (0x00004000U)
#define MCU_PWM_XBAR_ADC3_EVT4 (0x00008000U)
#define MCU_PWM_XBAR_ADC4_EVT1 (0x00010000U)
#define MCU_PWM_XBAR_ADC4_EVT2 (0x00020000U)
#define MCU_PWM_XBAR_ADC4_EVT3 (0x00040000U)
#define MCU_PWM_XBAR_ADC4_EVT4 (0x00080000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP4_MASKS PWMXBAR Input Group4 Masks
 *
 *  Bitwise OR of this macro to be passed to group4_mask
 *  @{
 */
#define MCU_PWM_XBAR_INPUT_XBAR0  (0x00000001U)
#define MCU_PWM_XBAR_INPUT_XBAR1  (0x00000002U)
#define MCU_PWM_XBAR_INPUT_XBAR2  (0x00000004U)
#define MCU_PWM_XBAR_INPUT_XBAR3  (0x00000008U)
#define MCU_PWM_XBAR_INPUT_XBAR4  (0x00000010U)
#define MCU_PWM_XBAR_INPUT_XBAR5  (0x00000020U)
#define MCU_PWM_XBAR_INPUT_XBAR6  (0x00000040U)
#define MCU_PWM_XBAR_INPUT_XBAR7  (0x00000080U)
#define MCU_PWM_XBAR_INPUT_XBAR8  (0x00000100U)
#define MCU_PWM_XBAR_INPUT_XBAR9  (0x00000200U)
#define MCU_PWM_XBAR_INPUT_XBAR10 (0x00000400U)
#define MCU_PWM_XBAR_INPUT_XBAR11 (0x00000800U)
#define MCU_PWM_XBAR_INPUT_XBAR12 (0x00001000U)
#define MCU_PWM_XBAR_INPUT_XBAR13 (0x00002000U)
#define MCU_PWM_XBAR_INPUT_XBAR14 (0x00004000U)
#define MCU_PWM_XBAR_INPUT_XBAR15 (0x00008000U)
#define MCU_PWM_XBAR_INPUT_XBAR16 (0x00010000U)
#define MCU_PWM_XBAR_INPUT_XBAR17 (0x00020000U)
#define MCU_PWM_XBAR_INPUT_XBAR18 (0x00040000U)
#define MCU_PWM_XBAR_INPUT_XBAR19 (0x00080000U)
#define MCU_PWM_XBAR_INPUT_XBAR20 (0x00100000U)
#define MCU_PWM_XBAR_INPUT_XBAR21 (0x00200000U)
#define MCU_PWM_XBAR_INPUT_XBAR22 (0x00400000U)
#define MCU_PWM_XBAR_INPUT_XBAR23 (0x00800000U)
#define MCU_PWM_XBAR_INPUT_XBAR24 (0x01000000U)
#define MCU_PWM_XBAR_INPUT_XBAR25 (0x02000000U)
#define MCU_PWM_XBAR_INPUT_XBAR26 (0x04000000U)
#define MCU_PWM_XBAR_INPUT_XBAR27 (0x08000000U)
#define MCU_PWM_XBAR_INPUT_XBAR28 (0x10000000U)
#define MCU_PWM_XBAR_INPUT_XBAR29 (0x20000000U)
#define MCU_PWM_XBAR_INPUT_XBAR30 (0x40000000U)
#define MCU_PWM_XBAR_INPUT_XBAR31 (0x80000000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP5_MASKS PWMXBAR Input Group5 Masks
 *
 *  Bitwise OR of this macro to be passed to group5_mask
 *  @{
 */
#define MCU_PWM_XBAR_EPWM0_TRIPOUT  (0x00000001U)
#define MCU_PWM_XBAR_EPWM1_TRIPOUT  (0x00000002U)
#define MCU_PWM_XBAR_EPWM2_TRIPOUT  (0x00000004U)
#define MCU_PWM_XBAR_EPWM3_TRIPOUT  (0x00000008U)
#define MCU_PWM_XBAR_EPWM4_TRIPOUT  (0x00000010U)
#define MCU_PWM_XBAR_EPWM5_TRIPOUT  (0x00000020U)
#define MCU_PWM_XBAR_EPWM6_TRIPOUT  (0x00000040U)
#define MCU_PWM_XBAR_EPWM7_TRIPOUT  (0x00000080U)
#define MCU_PWM_XBAR_EPWM8_TRIPOUT  (0x00000100U)
#define MCU_PWM_XBAR_EPWM9_TRIPOUT  (0x00000200U)
#define MCU_PWM_XBAR_EPWM10_TRIPOUT (0x00000400U)
#define MCU_PWM_XBAR_EPWM11_TRIPOUT (0x00000800U)
#define MCU_PWM_XBAR_EPWM12_TRIPOUT (0x00001000U)
#define MCU_PWM_XBAR_EPWM13_TRIPOUT (0x00002000U)
#define MCU_PWM_XBAR_EPWM14_TRIPOUT (0x00004000U)
#define MCU_PWM_XBAR_EPWM15_TRIPOUT (0x00008000U)
#define MCU_PWM_XBAR_EPWM16_TRIPOUT (0x00010000U)
#define MCU_PWM_XBAR_EPWM17_TRIPOUT (0x00020000U)
#define MCU_PWM_XBAR_EPWM18_TRIPOUT (0x00040000U)
#define MCU_PWM_XBAR_EPWM19_TRIPOUT (0x00080000U)
#define MCU_PWM_XBAR_EPWM20_TRIPOUT (0x00100000U)
#define MCU_PWM_XBAR_EPWM21_TRIPOUT (0x00200000U)
#define MCU_PWM_XBAR_EPWM22_TRIPOUT (0x00400000U)
#define MCU_PWM_XBAR_EPWM23_TRIPOUT (0x00800000U)
#define MCU_PWM_XBAR_EPWM24_TRIPOUT (0x01000000U)
#define MCU_PWM_XBAR_EPWM25_TRIPOUT (0x02000000U)
#define MCU_PWM_XBAR_EPWM26_TRIPOUT (0x04000000U)
#define MCU_PWM_XBAR_EPWM27_TRIPOUT (0x08000000U)
#define MCU_PWM_XBAR_EPWM28_TRIPOUT (0x10000000U)
#define MCU_PWM_XBAR_EPWM29_TRIPOUT (0x20000000U)
#define MCU_PWM_XBAR_EPWM30_TRIPOUT (0x40000000U)
#define MCU_PWM_XBAR_EPWM31_TRIPOUT (0x80000000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP6_MASKS PWMXBAR Input Group6 Masks
 *
 *  Bitwise OR of this macro to be passed to group6_mask
 *  @{
 */
#define MCU_PWM_XBAR_DEL0_TRIP  (0x00000001U)
#define MCU_PWM_XBAR_DEL1_TRIP  (0x00000002U)
#define MCU_PWM_XBAR_DEL2_TRIP  (0x00000004U)
#define MCU_PWM_XBAR_DEL3_TRIP  (0x00000008U)
#define MCU_PWM_XBAR_DEL4_TRIP  (0x00000010U)
#define MCU_PWM_XBAR_DEL5_TRIP  (0x00000020U)
#define MCU_PWM_XBAR_DEL6_TRIP  (0x00000040U)
#define MCU_PWM_XBAR_DEL7_TRIP  (0x00000080U)
#define MCU_PWM_XBAR_DEL8_TRIP  (0x00000100U)
#define MCU_PWM_XBAR_DEL9_TRIP  (0x00000200U)
#define MCU_PWM_XBAR_DEL10_TRIP (0x00000400U)
#define MCU_PWM_XBAR_DEL11_TRIP (0x00000800U)
#define MCU_PWM_XBAR_DEL12_TRIP (0x00001000U)
#define MCU_PWM_XBAR_DEL13_TRIP (0x00002000U)
#define MCU_PWM_XBAR_DEL14_TRIP (0x00004000U)
#define MCU_PWM_XBAR_DEL15_TRIP (0x00008000U)
#define MCU_PWM_XBAR_DEL16_TRIP (0x00010000U)
#define MCU_PWM_XBAR_DEL17_TRIP (0x00020000U)
#define MCU_PWM_XBAR_DEL18_TRIP (0x00040000U)
#define MCU_PWM_XBAR_DEL19_TRIP (0x00080000U)
#define MCU_PWM_XBAR_DEL20_TRIP (0x00100000U)
#define MCU_PWM_XBAR_DEL21_TRIP (0x00200000U)
#define MCU_PWM_XBAR_DEL22_TRIP (0x00400000U)
#define MCU_PWM_XBAR_DEL23_TRIP (0x00800000U)
#define MCU_PWM_XBAR_DEL24_TRIP (0x01000000U)
#define MCU_PWM_XBAR_DEL25_TRIP (0x02000000U)
#define MCU_PWM_XBAR_DEL26_TRIP (0x04000000U)
#define MCU_PWM_XBAR_DEL27_TRIP (0x08000000U)
#define MCU_PWM_XBAR_DEL28_TRIP (0x10000000U)
#define MCU_PWM_XBAR_DEL29_TRIP (0x20000000U)
#define MCU_PWM_XBAR_DEL30_TRIP (0x40000000U)
#define MCU_PWM_XBAR_DEL31_TRIP (0x80000000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP7_MASKS PWMXBAR Input Group7 Masks
 *
 *  Bitwise OR of this macro to be passed to group7_mask
 *  @{
 */
#define MCU_PWM_XBAR_DEL0_ACTIVE  (0x00000001U)
#define MCU_PWM_XBAR_DEL1_ACTIVE  (0x00000002U)
#define MCU_PWM_XBAR_DEL2_ACTIVE  (0x00000004U)
#define MCU_PWM_XBAR_DEL3_ACTIVE  (0x00000008U)
#define MCU_PWM_XBAR_DEL4_ACTIVE  (0x00000010U)
#define MCU_PWM_XBAR_DEL5_ACTIVE  (0x00000020U)
#define MCU_PWM_XBAR_DEL6_ACTIVE  (0x00000040U)
#define MCU_PWM_XBAR_DEL7_ACTIVE  (0x00000080U)
#define MCU_PWM_XBAR_DEL8_ACTIVE  (0x00000100U)
#define MCU_PWM_XBAR_DEL9_ACTIVE  (0x00000200U)
#define MCU_PWM_XBAR_DEL10_ACTIVE (0x00000400U)
#define MCU_PWM_XBAR_DEL11_ACTIVE (0x00000800U)
#define MCU_PWM_XBAR_DEL12_ACTIVE (0x00001000U)
#define MCU_PWM_XBAR_DEL13_ACTIVE (0x00002000U)
#define MCU_PWM_XBAR_DEL14_ACTIVE (0x00004000U)
#define MCU_PWM_XBAR_DEL15_ACTIVE (0x00008000U)
#define MCU_PWM_XBAR_DEL16_ACTIVE (0x00010000U)
#define MCU_PWM_XBAR_DEL17_ACTIVE (0x00020000U)
#define MCU_PWM_XBAR_DEL18_ACTIVE (0x00040000U)
#define MCU_PWM_XBAR_DEL19_ACTIVE (0x00080000U)
#define MCU_PWM_XBAR_DEL20_ACTIVE (0x00100000U)
#define MCU_PWM_XBAR_DEL21_ACTIVE (0x00200000U)
#define MCU_PWM_XBAR_DEL22_ACTIVE (0x00400000U)
#define MCU_PWM_XBAR_DEL23_ACTIVE (0x00800000U)
#define MCU_PWM_XBAR_DEL24_ACTIVE (0x01000000U)
#define MCU_PWM_XBAR_DEL25_ACTIVE (0x02000000U)
#define MCU_PWM_XBAR_DEL26_ACTIVE (0x04000000U)
#define MCU_PWM_XBAR_DEL27_ACTIVE (0x08000000U)
#define MCU_PWM_XBAR_DEL28_ACTIVE (0x10000000U)
#define MCU_PWM_XBAR_DEL29_ACTIVE (0x20000000U)
#define MCU_PWM_XBAR_DEL30_ACTIVE (0x40000000U)
#define MCU_PWM_XBAR_DEL31_ACTIVE (0x80000000U)
/** @} */

/**
 *  \name MCU_PWM_XBAR_GROUP8_MASKS PWMXBAR Input Group8 Masks
 *
 *  Bitwise OR of this macro to be passed to group8_mask
 *  @{
 */
#define MCU_PWM_XBAR_EQEP0_ERR       (0x00000001U)
#define MCU_PWM_XBAR_EQEP1_ERR       (0x00000002U)
#define MCU_PWM_XBAR_EQEP2_ERR       (0x00000004U)
#define MCU_PWM_XBAR_FSIRX0_RX_TRIG0 (0x00000008U)
#define MCU_PWM_XBAR_FSIRX0_RX_TRIG1 (0x00000010U)
#define MCU_PWM_XBAR_FSIRX0_RX_TRIG2 (0x00000020U)
#define MCU_PWM_XBAR_FSIRX0_RX_TRIG3 (0x00000040U)
#define MCU_PWM_XBAR_FSIRX1_RX_TRIG0 (0x00000080U)
#define MCU_PWM_XBAR_FSIRX1_RX_TRIG1 (0x00000100U)
#define MCU_PWM_XBAR_FSIRX1_RX_TRIG2 (0x00000200U)
#define MCU_PWM_XBAR_FSIRX1_RX_TRIG3 (0x00000400U)
#define MCU_PWM_XBAR_FSIRX2_RX_TRIG0 (0x00000800U)
#define MCU_PWM_XBAR_FSIRX2_RX_TRIG1 (0x00001000U)
#define MCU_PWM_XBAR_FSIRX2_RX_TRIG2 (0x00002000U)
#define MCU_PWM_XBAR_FSIRX2_RX_TRIG3 (0x00004000U)
#define MCU_PWM_XBAR_FSIRX3_RX_TRIG0 (0x00008000U)
#define MCU_PWM_XBAR_FSIRX3_RX_TRIG1 (0x00010000U)
#define MCU_PWM_XBAR_FSIRX3_RX_TRIG2 (0x00020000U)
#define MCU_PWM_XBAR_FSIRX3_RX_TRIG3 (0x00040000U)
#define MCU_PWM_XBAR_ECAP0_TRIPOUT   (0x00080000U)
#define MCU_PWM_XBAR_ECAP1_TRIPOUT   (0x00100000U)
#define MCU_PWM_XBAR_ECAP2_TRIPOUT   (0x00200000U)
#define MCU_PWM_XBAR_ECAP3_TRIPOUT   (0x00400000U)
#define MCU_PWM_XBAR_ECAP4_TRIPOUT   (0x00800000U)
#define MCU_PWM_XBAR_ECAP5_TRIPOUT   (0x01000000U)
#define MCU_PWM_XBAR_ECAP6_TRIPOUT   (0x02000000U)
#define MCU_PWM_XBAR_ECAP7_TRIPOUT   (0x04000000U)
#define MCU_PWM_XBAR_ECAP8_TRIPOUT   (0x08000000U)
#define MCU_PWM_XBAR_ECAP9_TRIPOUT   (0x10000000U)
/** @} */

/*
 * Internally used macros - not to be used by user directly
 */
/* PWMXBAR Register base address - to be passed to base argument in all fxns */
#define MCU_PWM_XBAR_BASE (0x502D1000U)

/* PWMXBAR Register offsets */
#define MCU_CSL_CONTROLSS_PWMXBAR_PID                (0x00000000U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_STATUS     (0x00000010U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAGINVERT (0x00000014U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAG       (0x00000018U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAG_CLR   (0x0000001CU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0        (0x00000100U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G1        (0x00000104U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G2        (0x00000108U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G3        (0x0000010CU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G4        (0x00000110U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G5        (0x00000114U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G6        (0x00000118U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G7        (0x0000011CU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G8        (0x00000120U)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR1_G0        (0x00000140U)

/* PWMXBAR offset difference between group register */
#define MCU_CSL_CONTROLSS_PWMXBAR_STEP (MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR1_G0 - MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0)

/* PWMXBAR_STATUS */
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_STATUS_STS_MASK  (0x3FFFFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_STATUS_STS_SHIFT (0x00000000U)

/* PWMXBAR_FLAGINVERT */
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAGINVERT_INVERT_MASK  (0x3FFFFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAGINVERT_INVERT_SHIFT (0x00000000U)

/* PWMXBAR Group Select Masks */
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0_SEL_MASK (0x000FFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G1_SEL_MASK (0x000FFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G2_SEL_MASK (0x00FFFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G3_SEL_MASK (0x000FFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G4_SEL_MASK (0xFFFFFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G5_SEL_MASK (0xFFFFFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G6_SEL_MASK (0xFFFFFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G7_SEL_MASK (0xFFFFFFFFU)
#define MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G8_SEL_MASK (0x1FFFFFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/**
 * \brief PWM XBAR: API to read raw output signal status of all PWM XBars
 *
 * \return uint32 PWM XBar status - Bitwise OR of all xbar outputs (0 to \ref
 * MCU_PWM_XBAR_NUM_OUTPUT - 1)
 */
static inline uint32 MCU_xbarGetPWMXBarOutputSignalStatus(void)
{
    return (HW_RD_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_STATUS) &
            MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_STATUS_STS_MASK);
}

/**
 * \brief PWM XBAR: API to configure inversion of output signal status flag (latched) of PWM XBars
 *
 * \param invert_mask [in] Mask defining the PWM XBar output signal flags (latched) to be inverted.
 *                         Bitwise OR of all xbar outputs (0 to \ref MCU_PWM_XBAR_NUM_OUTPUT - 1)
 */
static inline void MCU_xbarInvertPWMXBarOutputSignalBeforeLatch(uint32 invert_mask)
{
    HW_WR_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAGINVERT,
                invert_mask & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAGINVERT_INVERT_MASK);
}

/**
 * \brief PWM XBAR: API to read latched output signal status of all PWM XBars
 *
 * \return uint32 PWM XBar latched status flags.
 *                Bitwise OR of all xbar outputs (0 to \ref MCU_PWM_XBAR_NUM_OUTPUT - 1)
 */
static inline uint32 MCU_xbarGetPWMXBarOutputSignalLatchedFlag(void)
{
    return (HW_RD_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAG));
}

/**
 * \brief PWM XBAR: API to clear output signal status flag (latched) of PWM XBars
 *
 * \param clr [in] Mask defining the PWM XBar output signal flags (latched) to be cleared.
 *                 Bitwise OR of all xbar outputs (0 to \ref MCU_PWM_XBAR_NUM_OUTPUT - 1)
 */
static inline void MCU_xbarClearPWMXBarOutputSignalLatchedFlag(uint32 clr)
{
    HW_WR_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAG_CLR, clr);
}

/**
 * \brief PWM XBAR: API to select input sources of PWM XBar
 *
 * \param out [in] PWM XBar output. Valid values 0 to \ref MCU_PWM_XBAR_NUM_OUTPUT - 1
 * \param group_mask [in] Pointer to arrray of Mask to OR inputs from group 0 to \ref
 * MCU_PWM_XBAR_NUM_GROUPS - 1. group_mask[0U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP0_MASKS
 *                   group_mask[1U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP1_MASKS
 *                   group_mask[2U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP2_MASKS
 *                   group_mask[3U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP3_MASKS
 *                   group_mask[4U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP4_MASKS
 *                   group_mask[5U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP5_MASKS
 *                   group_mask[6U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP6_MASKS
 *                   group_mask[7U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP7_MASKS
 *                   group_mask[8U]: Bitwise mask of \ref MCU_PWM_XBAR_GROUP8_MASKS
 */
static inline void MCU_xbarSelectPWMXBarInputSource(uint32 out, const uint32 group_mask[MCU_PWM_XBAR_NUM_GROUPS])
{
    uint32 baseAddr = MCU_PWM_XBAR_BASE + (out * MCU_CSL_CONTROLSS_PWMXBAR_STEP);

    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0,
                group_mask[0U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G1,
                group_mask[1U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G1_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G2,
                group_mask[2U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G2_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G3,
                group_mask[3U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G3_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G4,
                group_mask[4U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G4_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G5,
                group_mask[5U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G5_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G6,
                group_mask[6U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G6_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G7,
                group_mask[7U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G7_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G8,
                group_mask[8U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G8_SEL_MASK);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* MCU_XBAR_PWM_H_ */
