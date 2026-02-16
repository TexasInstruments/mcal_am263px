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
 *  \file     Mcu_XbarOutput.h
 *
 *  \brief    This file contains interface header for Output XBAR module
 *
 */

#ifndef MCU_XBAR_OUTPUT_H_
#define MCU_XBAR_OUTPUT_H_

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
/** \brief OUTPUT XBAR Number of outputs */
#define MCU_OUTPUT_XBAR_NUM_OUTPUT (16U)
/** \brief OUTPUT XBAR Number of groups */
#define MCU_OUTPUT_XBAR_NUM_GROUPS (10U)

/*
 * OUTPUT XBAR Input Group Masks
 */
/** \brief OUTPUT XBAR none input mask - pass when nothing has to be selected for the group */
#define MCU_OUTPUT_XBAR_GROUP_MASK_NONE (0x00000000U)

/**
 *  \name MCU_OUTPUT_XBAR_GROUP0_MASKS OUTPUT XBAR Input Group0 Masks
 *
 *  Bitwise OR of this macro to be passed to group0_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_EPWM0_TRIPOUT (0x00000001U)
#define MCU_OUTPUT_XBAR_EPWM1_TRIPOUT (0x00000002U)
#define MCU_OUTPUT_XBAR_EPWM2_TRIPOUT (0x00000004U)
#define MCU_OUTPUT_XBAR_EPWM3_TRIPOUT (0x00000008U)
#define MCU_OUTPUT_XBAR_EPWM4_TRIPOUT (0x00000010U)
#define MCU_OUTPUT_XBAR_EPWM5_TRIPOUT (0x00000020U)
#define MCU_OUTPUT_XBAR_EPWM6_TRIPOUT (0x00000040U)
#define MCU_OUTPUT_XBAR_EPWM7_TRIPOUT (0x00000080U)
#define MCU_OUTPUT_XBAR_EPWM8_TRIPOUT (0x00000100U)
#define MCU_OUTPUT_XBAR_EPWM9_TRIPOUT (0x00000200U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP1_MASKS OUTPUT XBAR Input Group1 Masks
 *
 *  Bitwise OR of this macro to be passed to group1_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_EPWM0_SOCA (0x00000001U)
#define MCU_OUTPUT_XBAR_EPWM1_SOCA (0x00000002U)
#define MCU_OUTPUT_XBAR_EPWM2_SOCA (0x00000004U)
#define MCU_OUTPUT_XBAR_EPWM3_SOCA (0x00000008U)
#define MCU_OUTPUT_XBAR_EPWM4_SOCA (0x00000010U)
#define MCU_OUTPUT_XBAR_EPWM5_SOCA (0x00000020U)
#define MCU_OUTPUT_XBAR_EPWM6_SOCA (0x00000040U)
#define MCU_OUTPUT_XBAR_EPWM7_SOCA (0x00000080U)
#define MCU_OUTPUT_XBAR_EPWM8_SOCA (0x00000100U)
#define MCU_OUTPUT_XBAR_EPWM9_SOCA (0x00000200U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP2_MASKS OUTPUT XBAR Input Group2 Masks
 *
 *  Bitwise OR of this macro to be passed to group2_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_EPWM0_SOCB (0x00000001U)
#define MCU_OUTPUT_XBAR_EPWM1_SOCB (0x00000002U)
#define MCU_OUTPUT_XBAR_EPWM2_SOCB (0x00000004U)
#define MCU_OUTPUT_XBAR_EPWM3_SOCB (0x00000008U)
#define MCU_OUTPUT_XBAR_EPWM4_SOCB (0x00000010U)
#define MCU_OUTPUT_XBAR_EPWM5_SOCB (0x00000020U)
#define MCU_OUTPUT_XBAR_EPWM6_SOCB (0x00000040U)
#define MCU_OUTPUT_XBAR_EPWM7_SOCB (0x00000080U)
#define MCU_OUTPUT_XBAR_EPWM8_SOCB (0x00000100U)
#define MCU_OUTPUT_XBAR_EPWM9_SOCB (0x00000200U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP3_MASKS OUTPUT XBAR Input Group3 Masks
 *
 *  Bitwise OR of this macro to be passed to group3_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_DEL0_ACTIVE (0x00000001U)
#define MCU_OUTPUT_XBAR_DEL1_ACTIVE (0x00000002U)
#define MCU_OUTPUT_XBAR_DEL2_ACTIVE (0x00000004U)
#define MCU_OUTPUT_XBAR_DEL3_ACTIVE (0x00000008U)
#define MCU_OUTPUT_XBAR_DEL4_ACTIVE (0x00000010U)
#define MCU_OUTPUT_XBAR_DEL5_ACTIVE (0x00000020U)
#define MCU_OUTPUT_XBAR_DEL6_ACTIVE (0x00000040U)
#define MCU_OUTPUT_XBAR_DEL7_ACTIVE (0x00000080U)
#define MCU_OUTPUT_XBAR_DEL8_ACTIVE (0x00000100U)
#define MCU_OUTPUT_XBAR_DEL9_ACTIVE (0x00000200U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP4_MASKS OUTPUT XBAR Input Group4 Masks
 *
 *  Bitwise OR of this macro to be passed to group4_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_DEL0_TRIP (0x00000001U)
#define MCU_OUTPUT_XBAR_DEL1_TRIP (0x00000002U)
#define MCU_OUTPUT_XBAR_DEL2_TRIP (0x00000004U)
#define MCU_OUTPUT_XBAR_DEL3_TRIP (0x00000008U)
#define MCU_OUTPUT_XBAR_DEL4_TRIP (0x00000010U)
#define MCU_OUTPUT_XBAR_DEL5_TRIP (0x00000020U)
#define MCU_OUTPUT_XBAR_DEL6_TRIP (0x00000040U)
#define MCU_OUTPUT_XBAR_DEL7_TRIP (0x00000080U)
#define MCU_OUTPUT_XBAR_DEL8_TRIP (0x00000100U)
#define MCU_OUTPUT_XBAR_DEL9_TRIP (0x00000200U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP5_MASKS OUTPUT XBAR Input Group5 Masks
 *
 *  Bitwise OR of this macro to be passed to group5_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_SD0_FILT0_CEVT1 (0x00000001U)
#define MCU_OUTPUT_XBAR_SD0_FILT0_CEVT2 (0x00000002U)
#define MCU_OUTPUT_XBAR_SD0_FILT0_CMPHZ (0x00000004U)
#define MCU_OUTPUT_XBAR_SD0_FILT1_CEVT1 (0x00000008U)
#define MCU_OUTPUT_XBAR_SD0_FILT1_CEVT2 (0x00000010U)
#define MCU_OUTPUT_XBAR_SD0_FILT1_CMPHZ (0x00000020U)
#define MCU_OUTPUT_XBAR_SD0_FILT2_CEVT1 (0x00000040U)
#define MCU_OUTPUT_XBAR_SD0_FILT2_CEVT2 (0x00000080U)
#define MCU_OUTPUT_XBAR_SD0_FILT2_CMPHZ (0x00000100U)
#define MCU_OUTPUT_XBAR_SD0_FILT3_CEVT1 (0x00000200U)
#define MCU_OUTPUT_XBAR_SD0_FILT3_CEVT2 (0x00000400U)
#define MCU_OUTPUT_XBAR_SD0_FILT3_CMPHZ (0x00000800U)
#define MCU_OUTPUT_XBAR_SD1_FILT0_CEVT1 (0x00001000U)
#define MCU_OUTPUT_XBAR_SD1_FILT0_CEVT2 (0x00002000U)
#define MCU_OUTPUT_XBAR_SD1_FILT0_CMPHZ (0x00004000U)
#define MCU_OUTPUT_XBAR_SD1_FILT1_CEVT1 (0x00008000U)
#define MCU_OUTPUT_XBAR_SD1_FILT1_CEVT2 (0x00010000U)
#define MCU_OUTPUT_XBAR_SD1_FILT1_CMPHZ (0x00020000U)
#define MCU_OUTPUT_XBAR_SD1_FILT2_CEVT1 (0x00040000U)
#define MCU_OUTPUT_XBAR_SD1_FILT2_CEVT2 (0x00080000U)
#define MCU_OUTPUT_XBAR_SD1_FILT2_CMPHZ (0x00100000U)
#define MCU_OUTPUT_XBAR_SD1_FILT3_CEVT1 (0x00200000U)
#define MCU_OUTPUT_XBAR_SD1_FILT3_CEVT2 (0x00400000U)
#define MCU_OUTPUT_XBAR_SD1_FILT3_CMPHZ (0x00800000U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP6_MASKS OUTPUT XBAR Input Group6 Masks
 *
 *  Bitwise OR of this macro to be passed to group6_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_CMPSSA0_CTRIPL (0x00000001U)
#define MCU_OUTPUT_XBAR_CMPSSA0_CTRIPH (0x00000002U)
#define MCU_OUTPUT_XBAR_CMPSSA1_CTRIPL (0x00000004U)
#define MCU_OUTPUT_XBAR_CMPSSA1_CTRIPH (0x00000008U)
#define MCU_OUTPUT_XBAR_CMPSSA2_CTRIPL (0x00000010U)
#define MCU_OUTPUT_XBAR_CMPSSA2_CTRIPH (0x00000020U)
#define MCU_OUTPUT_XBAR_CMPSSA3_CTRIPL (0x00000040U)
#define MCU_OUTPUT_XBAR_CMPSSA3_CTRIPH (0x00000080U)
#define MCU_OUTPUT_XBAR_CMPSSA4_CTRIPL (0x00000100U)
#define MCU_OUTPUT_XBAR_CMPSSA4_CTRIPH (0x00000200U)
#define MCU_OUTPUT_XBAR_CMPSSA5_CTRIPL (0x00000400U)
#define MCU_OUTPUT_XBAR_CMPSSA5_CTRIPH (0x00000800U)
#define MCU_OUTPUT_XBAR_CMPSSA6_CTRIPL (0x00001000U)
#define MCU_OUTPUT_XBAR_CMPSSA6_CTRIPH (0x00002000U)
#define MCU_OUTPUT_XBAR_CMPSSA7_CTRIPL (0x00004000U)
#define MCU_OUTPUT_XBAR_CMPSSA7_CTRIPH (0x00008000U)
#define MCU_OUTPUT_XBAR_CMPSSA8_CTRIPL (0x00010000U)
#define MCU_OUTPUT_XBAR_CMPSSA8_CTRIPH (0x00020000U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP7_MASKS OUTPUT XBAR Input Group7 Masks
 *
 *  Bitwise OR of this macro to be passed to group7_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_ADC0_EVT1 (0x00000001U)
#define MCU_OUTPUT_XBAR_ADC0_EVT2 (0x00000002U)
#define MCU_OUTPUT_XBAR_ADC0_EVT3 (0x00000004U)
#define MCU_OUTPUT_XBAR_ADC0_EVT4 (0x00000008U)
#define MCU_OUTPUT_XBAR_ADC1_EVT1 (0x00000010U)
#define MCU_OUTPUT_XBAR_ADC1_EVT2 (0x00000020U)
#define MCU_OUTPUT_XBAR_ADC1_EVT3 (0x00000040U)
#define MCU_OUTPUT_XBAR_ADC1_EVT4 (0x00000080U)
#define MCU_OUTPUT_XBAR_ADC2_EVT1 (0x00000100U)
#define MCU_OUTPUT_XBAR_ADC2_EVT2 (0x00000200U)
#define MCU_OUTPUT_XBAR_ADC2_EVT3 (0x00000400U)
#define MCU_OUTPUT_XBAR_ADC2_EVT4 (0x00000800U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP8_MASKS OUTPUT XBAR Input Group8 Masks
 *
 *  Bitwise OR of this macro to be passed to group8_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_EPWM_SYNCOUT_XBAR0 (0x00000001U)
#define MCU_OUTPUT_XBAR_EPWM_SYNCOUT_XBAR1 (0x00000002U)
#define MCU_OUTPUT_XBAR_EPWM_SYNCOUT_XBAR2 (0x00000004U)
#define MCU_OUTPUT_XBAR_EPWM_SYNCOUT_XBAR3 (0x00000008U)
#define MCU_OUTPUT_XBAR_EQEP0_I_OUT        (0x00000010U)
#define MCU_OUTPUT_XBAR_EQEP0_S_OUT        (0x00000020U)
#define MCU_OUTPUT_XBAR_EQEP1_I_OUT        (0x00000040U)
#define MCU_OUTPUT_XBAR_EQEP1_S_OUT        (0x00000080U)
#define MCU_OUTPUT_XBAR_ECAP0_OUT          (0x00000400U)
#define MCU_OUTPUT_XBAR_ECAP1_OUT          (0x00000800U)
#define MCU_OUTPUT_XBAR_ECAP2_OUT          (0x00001000U)
#define MCU_OUTPUT_XBAR_ECAP3_OUT          (0x00002000U)
#define MCU_OUTPUT_XBAR_ECAP4_OUT          (0x00004000U)
#define MCU_OUTPUT_XBAR_ECAP5_OUT          (0x00008000U)
#define MCU_OUTPUT_XBAR_ECAP6_OUT          (0x00010000U)
#define MCU_OUTPUT_XBAR_ECAP7_OUT          (0x00020000U)
/** @} */

/**
 *  \name MCU_OUTPUT_XBAR_GROUP9_MASKS OUTPUT XBAR Input Group9 Masks
 *
 *  Bitwise OR of this macro to be passed to group9_mask
 *  @{
 */
#define MCU_OUTPUT_XBAR_FSIRX0_RX_TRIG0 (0x00000001U)
#define MCU_OUTPUT_XBAR_FSIRX0_RX_TRIG1 (0x00000002U)
#define MCU_OUTPUT_XBAR_FSIRX0_RX_TRIG2 (0x00000004U)
#define MCU_OUTPUT_XBAR_FSIRX0_RX_TRIG3 (0x00000008U)
#define MCU_OUTPUT_XBAR_INPUTXBAR_OUT7  (0x00010000U)
#define MCU_OUTPUT_XBAR_INPUTXBAR_OUT15 (0x00020000U)
#define MCU_OUTPUT_XBAR_INPUTXBAR_OUT23 (0x00040000U)
#define MCU_OUTPUT_XBAR_INPUTXBAR_OUT31 (0x00080000U)
#define MCU_OUTPUT_XBAR_INTXBAR_OUT7    (0x01000000U)
#define MCU_OUTPUT_XBAR_INTXBAR_OUT15   (0x02000000U)
/** @} */

/*
 * Internally used macros - not to be used by user directly
 */
/* OUTPUT XBAR Register base address - to be passed to base argument in all fxns */
#define MCU_OUTPUT_XBAR_BASE (0x502D8000U)

/* OUTPUT XBAR Register offsets */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_PID                   (0x00000000U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_STATUS     (0x00000010U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGINVERT (0x00000014U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAG       (0x00000018U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAG_CLR   (0x0000001CU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGFORCE  (0x00000020U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLATCH   (0x00000024U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTSTRETCH (0x00000028U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLENGTH  (0x0000002CU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTINVERT  (0x00000030U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0        (0x00000100U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G1        (0x00000104U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G2        (0x00000108U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G3        (0x0000010CU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G4        (0x00000110U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G5        (0x00000114U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G6        (0x00000118U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G7        (0x0000011CU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G8        (0x00000120U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G9        (0x00000124U)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR1_G0        (0x00000140U)

/* OUTPUT XBAR offset difference between group register */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_STEP \
    (MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR1_G0 - MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0)

/* OUTPUTXBAR_STATUS */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_STATUS_STS_MASK  (0x0000FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_STATUS_STS_SHIFT (0x00000000U)

/* OUTPUTXBAR_FLAGINVERT */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGINVERT_INVERT_MASK  (0x0000FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGINVERT_INVERT_SHIFT (0x00000000U)

/* OUTPUTXBAR_FLAGFORCE */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGFORCE_FRC_MASK  (0x0000FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGFORCE_FRC_SHIFT (0x00000000U)

/* OUTPUTXBAR_OUTLATCH */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLATCH_LATCHSEL_MASK  (0x0000FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLATCH_LATCHSEL_SHIFT (0x00000000U)

/* OUTPUTXBAR_OUTSTRETCH */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTSTRETCH_STRETCHSEL_MASK  (0x0000FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTSTRETCH_STRETCHSEL_SHIFT (0x00000000U)

/* OUTPUTXBAR_OUTLENGTH */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLENGTH_LENGTHSEL_MASK  (0x0000FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLENGTH_LENGTHSEL_SHIFT (0x00000000U)

/* OUTPUTXBAR_OUTINVERT */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTINVERT_OUTINVERT_MASK  (0x0000FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTINVERT_OUTINVERT_SHIFT (0x00000000U)

/* OUTPUT XBAR Group Select Masks */
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0_SEL_MASK (0x000003FFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G1_SEL_MASK (0x000003FFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G2_SEL_MASK (0x000003FFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G3_SEL_MASK (0x000003FFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G4_SEL_MASK (0x000003FFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G5_SEL_MASK (0x00FFFFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G6_SEL_MASK (0x0003FFFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G7_SEL_MASK (0x00000FFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G8_SEL_MASK (0x0003FCFFU)
#define MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G9_SEL_MASK (0x030F000FU)

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
 * \brief Output XBAR: API to read raw output signal status of all Output XBars
 *
 * \return uint32 Output XBar status - Bitwise OR of all xbar outputs (0 to \ref
 * MCU_OUTPUT_XBAR_NUM_OUTPUT - 1)
 */
static inline uint32 MCU_xbarGetOutputXBarOutputSignalStatus(void)
{
    return (HW_RD_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_STATUS) &
            MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_STATUS_STS_MASK);
}

/**
 * \brief Output XBAR: API to configure inversion of output signal status flag (latched) of Output
 * XBars
 *
 * \param invert [in] Mask defining the Output XBar output signal flags (latched) to be inverted.
 *                    Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT - 1)
 */
static inline void MCU_xbarInvertOutputXBarOutputSignalBeforeLatch(uint32 invert)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGINVERT,
                invert & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGINVERT_INVERT_MASK);
}

/**
 * \brief Output XBAR: API to read latched output signal status of all Output XBars
 *
 * \return uint32 Output XBar latched status flags.
 *                Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT - 1)
 */
static inline uint32 MCU_xbarGetOutputXBarOutputSignalLatchedFlag(void)
{
    return (HW_RD_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAG));
}

/**
 * \brief Output XBAR: API to clear output signal status flag (latched) of Output XBars
 *
 * \param clr [in] Mask defining the Output XBar output signal flags (latched) to be cleared
 *                 Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT - 1)
 */
static inline void MCU_xbarClearOutputXBarOutputSignalLatchedFlag(uint32 clr)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAG_CLR, clr);
}

/**
 * \brief Output XBAR: API to force output signal status flag (latched) of Output XBars
 *
 * \param force [in] Mask defining the Output XBar output signal flags (latched) to be forced to
 * set. Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT - 1)
 */
static inline void MCU_xbarForceOutputXBarOutputSignalLatchedFlag(uint32 force)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGFORCE,
                force & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGFORCE_FRC_MASK);
}

/**
 * \brief Output XBAR: API to select output of Output XBars
 *
 * \param latchselect [in] Select latched / non-latched output.
 *                         Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT - 1)
 */
static inline void MCU_xbarSelectLatchOutputXBarOutputSignal(uint32 latchselect)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLATCH,
                latchselect & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLATCH_LATCHSEL_MASK);
}

/**
 * \brief Output XBAR: API to enable pulse stretching of output of Output XBars
 *
 * \param stretchselect [in] Select stretched / non-stretched output
 *                           Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT -
 * 1)
 */
static inline void MCU_xbarSelectStretchedPulseOutputXBarOutputSignal(uint32 stretchselect)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTSTRETCH,
                stretchselect & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTSTRETCH_STRETCHSEL_MASK);
}

/**
 * \brief Output XBAR: API to configure pulse streching length of output of Output XBars
 *
 * \param lengthselect [in] Configure strech length.
 *                          Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT -
 * 1)
 */
static inline void MCU_xbarSelectStretchedPulseLengthOutputXBarOutputSignal(uint32 lengthselect)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLENGTH,
                lengthselect & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLENGTH_LENGTHSEL_MASK);
}

/**
 * \brief Output XBAR: API to configure inversion of output signal of Output XBars
 *
 * \param invertout [in] Mask defining the Output XBar output signal to be inverted
 *                       Bitwise OR of all xbar outputs (0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT - 1)
 */
static inline void MCU_xbarInvertOutputXBarOutputSignal(uint32 invertout)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTINVERT,
                invertout & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTINVERT_OUTINVERT_MASK);
}

/**
 * \brief Output XBAR: API to select input sources of Output XBar
 *
 * \param out [in] Instance of Output XBar. Valid values 0 to \ref MCU_OUTPUT_XBAR_NUM_OUTPUT - 1
 * \param group_mask [in] Pointer to arrray of Mask to OR inputs from group 0 to \ref
 * MCU_OUTPUT_XBAR_NUM_GROUPS - 1. group_mask[0U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP0_MASKS
 *                   group_mask[1U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP1_MASKS
 *                   group_mask[2U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP2_MASKS
 *                   group_mask[3U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP3_MASKS
 *                   group_mask[4U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP4_MASKS
 *                   group_mask[5U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP5_MASKS
 *                   group_mask[6U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP6_MASKS
 *                   group_mask[7U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP7_MASKS
 *                   group_mask[8U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP8_MASKS
 *                   group_mask[9U]: Bitwise mask of \ref MCU_OUTPUT_XBAR_GROUP9_MASKS
 */
static inline void MCU_xbarSelectOutputXBarInputSource(uint32 out, const uint32 group_mask[MCU_OUTPUT_XBAR_NUM_GROUPS])
{
    uint32 baseAddr = MCU_OUTPUT_XBAR_BASE + (out * MCU_CSL_CONTROLSS_OUTPUTXBAR_STEP);

    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0,
                group_mask[0U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G1,
                group_mask[1U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G1_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G2,
                group_mask[2U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G2_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G3,
                group_mask[3U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G3_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G4,
                group_mask[4U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G4_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G5,
                group_mask[5U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G5_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G6,
                group_mask[6U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G6_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G7,
                group_mask[7U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G7_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G8,
                group_mask[8U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G8_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G9,
                group_mask[9U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G9_SEL_MASK);
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* MCU_XBAR_OUTPUT_H_ */
