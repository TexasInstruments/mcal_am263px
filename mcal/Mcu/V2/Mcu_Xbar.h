/*
 * Copyright (C) 2023 Texas Instruments Incorporated
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

#ifndef MCU_XBAR_H_
#define MCU_XBAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "Std_Types.h"
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

/* Register Macros */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0       (0x00000100U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G1       (0x00000104U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G2       (0x00000108U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G3       (0x0000010CU)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G4       (0x00000110U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G5       (0x00000114U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G6       (0x00000118U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G7       (0x0000011CU)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G8       (0x00000120U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G9       (0x00000124U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR1_G0       (0x00000140U)
#define MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL (0x00000100U)
#define MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0   (0x00000104U)
#define MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1   (0x00000108U)
#define MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR1_GSEL (0x00000140U)

/* INTXBAR0_G0 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_MASK (0xFFFFFFFFU)
/* INTXBAR0_G1 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_MASK (0xFFFFFFFFU)
/* INTXBAR0_G2 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_MASK (0x01FFFFFFU)
/* INTXBAR0_G3 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_MASK (0x0000FFFFU)
/* INTXBAR0_G4 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_MASK (0x000003FFU)
/* INTXBAR0_G5 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_MASK (0x000003FFU)
/* INTXBAR0_G6 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_MASK (0x00000007U)
/* INTXBAR0_G7 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G7_SEL_MASK (0x000003FFU)
/* INTXBAR0_G8 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G8_SEL_MASK (0x000FFFFFU)
/* INTXBAR0_G9 */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G9_SEL_MASK (0x000FFFFFU)

/* INPUTXBAR0_GSEL */
#define MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL_GSEL_MASK (0x00000001U)
/* INPUTXBAR0_G0 */
#define MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0_SEL_MASK (0x000000FFU)
/* INPUTXBAR0_G1 */
#define MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1_SEL_MASK (0x0000001FU)

#define MCU_CSL_CONTROLSS_INTXBAR_STEP (MCU_CSL_CONTROLSS_INTXBAR_INTXBAR1_G0 - MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0)
#define MCU_CSL_CONTROLSS_INPUTXBAR_STEP \
    (MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR1_GSEL - MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL)

/* Global addresses in unified address space */
#define MCU_CSL_CONTROLSS_INTXBAR_U_BASE   (0x502D5000UL)
#define MCU_CSL_CONTROLSS_INPUTXBAR_U_BASE (0x502D0000UL)

/* GPIO_XBAR_INTR Macros */
#define MCU_CSL_GPIO_INTR_XBAR_U_BASE                  (0x52E02000UL)
#define MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_INT_ENABLE_MASK (0x00010000U)
#define MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_ENABLE_MASK     (0x000000FFU)
#define MCU_CSL_GPIO_INTR_XBAR_MUXCNTL(MUXCNTL)        (0x00000004U + ((MUXCNTL) * 0x4U))

/* List of interrupt crossbar sources
 */
#define MCU_INTRXBAR0_OUT_0  0
#define MCU_INTRXBAR0_OUT_1  1
#define MCU_INTRXBAR0_OUT_2  2
#define MCU_INTRXBAR0_OUT_3  3
#define MCU_INTRXBAR0_OUT_4  4
#define MCU_INTRXBAR0_OUT_5  5
#define MCU_INTRXBAR0_OUT_6  6
#define MCU_INTRXBAR0_OUT_7  7
#define MCU_INTRXBAR0_OUT_8  8
#define MCU_INTRXBAR0_OUT_9  9
#define MCU_INTRXBAR0_OUT_10 10
#define MCU_INTRXBAR0_OUT_11 11
#define MCU_INTRXBAR0_OUT_12 12
#define MCU_INTRXBAR0_OUT_13 13
#define MCU_INTRXBAR0_OUT_14 14
#define MCU_INTRXBAR0_OUT_15 15
#define MCU_INTRXBAR0_OUT_16 16
#define MCU_INTRXBAR0_OUT_17 17
#define MCU_INTRXBAR0_OUT_18 18
#define MCU_INTRXBAR0_OUT_19 19
#define MCU_INTRXBAR0_OUT_20 20
#define MCU_INTRXBAR0_OUT_21 21
#define MCU_INTRXBAR0_OUT_22 22
#define MCU_INTRXBAR0_OUT_23 23
#define MCU_INTRXBAR0_OUT_24 24
#define MCU_INTRXBAR0_OUT_25 25
#define MCU_INTRXBAR0_OUT_26 26
#define MCU_INTRXBAR0_OUT_27 27
#define MCU_INTRXBAR0_OUT_28 28
#define MCU_INTRXBAR0_OUT_29 29
#define MCU_INTRXBAR0_OUT_30 30
#define MCU_INTRXBAR0_OUT_31 31

/* List of input crossbar sources
 */
#define MCU_INPUT_XBAR0_OUT_0  0
#define MCU_INPUT_XBAR0_OUT_1  1
#define MCU_INPUT_XBAR0_OUT_2  2
#define MCU_INPUT_XBAR0_OUT_3  3
#define MCU_INPUT_XBAR0_OUT_4  4
#define MCU_INPUT_XBAR0_OUT_5  5
#define MCU_INPUT_XBAR0_OUT_6  6
#define MCU_INPUT_XBAR0_OUT_7  7
#define MCU_INPUT_XBAR0_OUT_8  8
#define MCU_INPUT_XBAR0_OUT_9  9
#define MCU_INPUT_XBAR0_OUT_10 10
#define MCU_INPUT_XBAR0_OUT_11 11
#define MCU_INPUT_XBAR0_OUT_12 12
#define MCU_INPUT_XBAR0_OUT_13 13
#define MCU_INPUT_XBAR0_OUT_14 14
#define MCU_INPUT_XBAR0_OUT_15 15
#define MCU_INPUT_XBAR0_OUT_16 16
#define MCU_INPUT_XBAR0_OUT_17 17
#define MCU_INPUT_XBAR0_OUT_18 18
#define MCU_INPUT_XBAR0_OUT_19 19
#define MCU_INPUT_XBAR0_OUT_20 20
#define MCU_INPUT_XBAR0_OUT_21 21
#define MCU_INPUT_XBAR0_OUT_22 22
#define MCU_INPUT_XBAR0_OUT_23 23
#define MCU_INPUT_XBAR0_OUT_24 24
#define MCU_INPUT_XBAR0_OUT_25 25
#define MCU_INPUT_XBAR0_OUT_26 26
#define MCU_INPUT_XBAR0_OUT_27 27
#define MCU_INPUT_XBAR0_OUT_28 28
#define MCU_INPUT_XBAR0_OUT_29 29
#define MCU_INPUT_XBAR0_OUT_30 30
#define MCU_INPUT_XBAR0_OUT_31 31

/**************************************************************************
    Mcu Interrupt XBAR INPUT Macros
**************************************************************************/

#define MCU_INT_XBAR_EPWM0_INT       (0x00000001)
#define MCU_INT_XBAR_EPWM1_INT       (0x00000002)
#define MCU_INT_XBAR_EPWM2_INT       (0x00000004)
#define MCU_INT_XBAR_EPWM3_INT       (0x00000008)
#define MCU_INT_XBAR_EPWM4_INT       (0x00000010)
#define MCU_INT_XBAR_EPWM5_INT       (0x00000020)
#define MCU_INT_XBAR_EPWM6_INT       (0x00000040)
#define MCU_INT_XBAR_EPWM7_INT       (0x00000080)
#define MCU_INT_XBAR_EPWM8_INT       (0x00000100)
#define MCU_INT_XBAR_EPWM9_INT       (0x00000200)
#define MCU_INT_XBAR_EPWM10_INT      (0x00000400)
#define MCU_INT_XBAR_EPWM11_INT      (0x00000800)
#define MCU_INT_XBAR_EPWM12_INT      (0x00001000)
#define MCU_INT_XBAR_EPWM13_INT      (0x00002000)
#define MCU_INT_XBAR_EPWM14_INT      (0x00004000)
#define MCU_INT_XBAR_EPWM15_INT      (0x00008000)
#define MCU_INT_XBAR_EPWM16_INT      (0x00010000)
#define MCU_INT_XBAR_EPWM17_INT      (0x00020000)
#define MCU_INT_XBAR_EPWM18_INT      (0x00040000)
#define MCU_INT_XBAR_EPWM19_INT      (0x00080000)
#define MCU_INT_XBAR_EPWM20_INT      (0x00100000)
#define MCU_INT_XBAR_EPWM21_INT      (0x00200000)
#define MCU_INT_XBAR_EPWM22_INT      (0x00400000)
#define MCU_INT_XBAR_EPWM23_INT      (0x00800000)
#define MCU_INT_XBAR_EPWM24_INT      (0x01000000)
#define MCU_INT_XBAR_EPWM25_INT      (0x02000000)
#define MCU_INT_XBAR_EPWM26_INT      (0x04000000)
#define MCU_INT_XBAR_EPWM27_INT      (0x08000000)
#define MCU_INT_XBAR_EPWM28_INT      (0x10000000)
#define MCU_INT_XBAR_EPWM29_INT      (0x20000000)
#define MCU_INT_XBAR_EPWM30_INT      (0x40000000)
#define MCU_INT_XBAR_EPWM31_INT      (0x80000000)
#define MCU_INT_XBAR_EPWM0_TZINT     (0x00000001)
#define MCU_INT_XBAR_EPWM1_TZINT     (0x00000002)
#define MCU_INT_XBAR_EPWM2_TZINT     (0x00000004)
#define MCU_INT_XBAR_EPWM3_TZINT     (0x00000008)
#define MCU_INT_XBAR_EPWM4_TZINT     (0x00000010)
#define MCU_INT_XBAR_EPWM5_TZINT     (0x00000020)
#define MCU_INT_XBAR_EPWM6_TZINT     (0x00000040)
#define MCU_INT_XBAR_EPWM7_TZINT     (0x00000080)
#define MCU_INT_XBAR_EPWM8_TZINT     (0x00000100)
#define MCU_INT_XBAR_EPWM9_TZINT     (0x00000200)
#define MCU_INT_XBAR_EPWM10_TZINT    (0x00000400)
#define MCU_INT_XBAR_EPWM11_TZINT    (0x00000800)
#define MCU_INT_XBAR_EPWM12_TZINT    (0x00001000)
#define MCU_INT_XBAR_EPWM13_TZINT    (0x00002000)
#define MCU_INT_XBAR_EPWM14_TZINT    (0x00004000)
#define MCU_INT_XBAR_EPWM15_TZINT    (0x00008000)
#define MCU_INT_XBAR_EPWM16_TZINT    (0x00010000)
#define MCU_INT_XBAR_EPWM17_TZINT    (0x00020000)
#define MCU_INT_XBAR_EPWM18_TZINT    (0x00040000)
#define MCU_INT_XBAR_EPWM19_TZINT    (0x00080000)
#define MCU_INT_XBAR_EPWM20_TZINT    (0x00100000)
#define MCU_INT_XBAR_EPWM21_TZINT    (0x00200000)
#define MCU_INT_XBAR_EPWM22_TZINT    (0x00400000)
#define MCU_INT_XBAR_EPWM23_TZINT    (0x00800000)
#define MCU_INT_XBAR_EPWM24_TZINT    (0x01000000)
#define MCU_INT_XBAR_EPWM25_TZINT    (0x02000000)
#define MCU_INT_XBAR_EPWM26_TZINT    (0x04000000)
#define MCU_INT_XBAR_EPWM27_TZINT    (0x08000000)
#define MCU_INT_XBAR_EPWM28_TZINT    (0x10000000)
#define MCU_INT_XBAR_EPWM29_TZINT    (0x20000000)
#define MCU_INT_XBAR_EPWM30_TZINT    (0x40000000)
#define MCU_INT_XBAR_EPWM31_TZINT    (0x80000000)
#define MCU_INT_XBAR_ADC0_INT1       (0x00000001)
#define MCU_INT_XBAR_ADC0_INT2       (0x00000002)
#define MCU_INT_XBAR_ADC0_INT3       (0x00000004)
#define MCU_INT_XBAR_ADC0_INT4       (0x00000008)
#define MCU_INT_XBAR_ADC0_EVTINT     (0x00000010)
#define MCU_INT_XBAR_ADC1_INT1       (0x00000020)
#define MCU_INT_XBAR_ADC1_INT2       (0x00000040)
#define MCU_INT_XBAR_ADC1_INT3       (0x00000080)
#define MCU_INT_XBAR_ADC1_INT4       (0x00000100)
#define MCU_INT_XBAR_ADC1_EVTINT     (0x00000200)
#define MCU_INT_XBAR_ADC2_INT1       (0x00000400)
#define MCU_INT_XBAR_ADC2_INT2       (0x00000800)
#define MCU_INT_XBAR_ADC2_INT3       (0x00001000)
#define MCU_INT_XBAR_ADC2_INT4       (0x00002000)
#define MCU_INT_XBAR_ADC2_EVTINT     (0x00004000)
#define MCU_INT_XBAR_ADC3_INT1       (0x00008000)
#define MCU_INT_XBAR_ADC3_INT2       (0x00010000)
#define MCU_INT_XBAR_ADC3_INT3       (0x00020000)
#define MCU_INT_XBAR_ADC3_INT4       (0x00040000)
#define MCU_INT_XBAR_ADC3_EVTINT     (0x00080000)
#define MCU_INT_XBAR_ADC4_INT1       (0x00100000)
#define MCU_INT_XBAR_ADC4_INT2       (0x00200000)
#define MCU_INT_XBAR_ADC4_INT3       (0x00400000)
#define MCU_INT_XBAR_ADC4_INT4       (0x00800000)
#define MCU_INT_XBAR_ADC4_EVTINT     (0x01000000)
#define MCU_INT_XBAR_FSIRX0_INT1N    (0x00000001)
#define MCU_INT_XBAR_FSIRX0_INT2N    (0x00000002)
#define MCU_INT_XBAR_FSIRX1_INT1N    (0x00000004)
#define MCU_INT_XBAR_FSIRX1_INT2N    (0x00000008)
#define MCU_INT_XBAR_FSIRX2_INT1N    (0x00000010)
#define MCU_INT_XBAR_FSIRX2_INT2N    (0x00000020)
#define MCU_INT_XBAR_FSIRX3_INT1N    (0x00000040)
#define MCU_INT_XBAR_FSIRX3_INT2N    (0x00000080)
#define MCU_INT_XBAR_FSITX0_INT1N    (0x00000100)
#define MCU_INT_XBAR_FSITX0_INT2N    (0x00000200)
#define MCU_INT_XBAR_FSITX1_INT1N    (0x00000400)
#define MCU_INT_XBAR_FSITX1_INT2N    (0x00000800)
#define MCU_INT_XBAR_FSITX2_INT1N    (0x00001000)
#define MCU_INT_XBAR_FSITX2_INT2N    (0x00002000)
#define MCU_INT_XBAR_FSITX3_INT1N    (0x00004000)
#define MCU_INT_XBAR_FSITX3_INT2N    (0x00008000)
#define MCU_INT_XBAR_SD0_ERR         (0x00000001)
#define MCU_INT_XBAR_SD0_FILT0_DRINT (0x00000002)
#define MCU_INT_XBAR_SD0_FILT1_DRINT (0x00000004)
#define MCU_INT_XBAR_SD0_FILT2_DRINT (0x00000008)
#define MCU_INT_XBAR_SD0_FILT3_DRINT (0x00000010)
#define MCU_INT_XBAR_SD1_ERR         (0x00000020)
#define MCU_INT_XBAR_SD1_FILT0_DRINT (0x00000040)
#define MCU_INT_XBAR_SD1_FILT1_DRINT (0x00000080)
#define MCU_INT_XBAR_SD1_FILT2_DRINT (0x00000100)
#define MCU_INT_XBAR_SD1_FILT3_DRINT (0x00000200)
#define MCU_INT_XBAR_ECAP0_INT       (0x00000001)
#define MCU_INT_XBAR_ECAP1_INT       (0x00000002)
#define MCU_INT_XBAR_ECAP2_INT       (0x00000004)
#define MCU_INT_XBAR_ECAP3_INT       (0x00000008)
#define MCU_INT_XBAR_ECAP4_INT       (0x00000010)
#define MCU_INT_XBAR_ECAP5_INT       (0x00000020)
#define MCU_INT_XBAR_ECAP6_INT       (0x00000040)
#define MCU_INT_XBAR_ECAP7_INT       (0x00000080)
#define MCU_INT_XBAR_ECAP8_INT       (0x00000100)
#define MCU_INT_XBAR_ECAP9_INT       (0x00000200)
#define MCU_INT_XBAR_ECAP10_INT      (0x00000400)
#define MCU_INT_XBAR_ECAP11_INT      (0x00000800)
#define MCU_INT_XBAR_ECAP12_INT      (0x00001000)
#define MCU_INT_XBAR_ECAP13_INT      (0x00002000)
#define MCU_INT_XBAR_ECAP14_INT      (0x00004000)
#define MCU_INT_XBAR_ECAP15_INT      (0x00008000)
#define MCU_INT_XBAR_EQEP0_INT       (0x00000001)
#define MCU_INT_XBAR_EQEP1_INT       (0x00000002)
#define MCU_INT_XBAR_EQEP2_INT       (0x00000004)
/* Group 7 */
#define MCU_INT_XBAR_ADC_R0_INT1   (0x00000001)
#define MCU_INT_XBAR_ADC_R0_INT2   (0x00000002)
#define MCU_INT_XBAR_ADC_R0_INT3   (0x00000004)
#define MCU_INT_XBAR_ADC_R0_INT4   (0x00000008)
#define MCU_INT_XBAR_ADC_R0_EVTINT (0x00000010)
#define MCU_INT_XBAR_ADC_R1_INT1   (0x00000020)
#define MCU_INT_XBAR_ADC_R1_INT2   (0x00000040)
#define MCU_INT_XBAR_ADC_R1_INT3   (0x00000080)
#define MCU_INT_XBAR_ADC_R1_INT4   (0x00000100)
#define MCU_INT_XBAR_ADC_R1_EVTINT (0x00000200)
/* Group 8 */
#define MCU_INT_XBAR_CMPSSA0_CTRIPL (0x00000001)
#define MCU_INT_XBAR_CMPSSA0_CTRIPH (0x00000002)
#define MCU_INT_XBAR_CMPSSA1_CTRIPL (0x00000004)
#define MCU_INT_XBAR_CMPSSA1_CTRIPH (0x00000008)
#define MCU_INT_XBAR_CMPSSA2_CTRIPL (0x00000010)
#define MCU_INT_XBAR_CMPSSA2_CTRIPH (0x00000020)
#define MCU_INT_XBAR_CMPSSA3_CTRIPL (0x00000040)
#define MCU_INT_XBAR_CMPSSA3_CTRIPH (0x00000080)
#define MCU_INT_XBAR_CMPSSA4_CTRIPL (0x00000100)
#define MCU_INT_XBAR_CMPSSA4_CTRIPH (0x00000200)
#define MCU_INT_XBAR_CMPSSA5_CTRIPL (0x00000400)
#define MCU_INT_XBAR_CMPSSA5_CTRIPH (0x00000800)
#define MCU_INT_XBAR_CMPSSA6_CTRIPL (0x00001000)
#define MCU_INT_XBAR_CMPSSA6_CTRIPH (0x00002000)
#define MCU_INT_XBAR_CMPSSA7_CTRIPL (0x00004000)
#define MCU_INT_XBAR_CMPSSA7_CTRIPH (0x00008000)
#define MCU_INT_XBAR_CMPSSA8_CTRIPL (0x00010000)
#define MCU_INT_XBAR_CMPSSA8_CTRIPH (0x00020000)
#define MCU_INT_XBAR_CMPSSA9_CTRIPL (0x00040000)
#define MCU_INT_XBAR_CMPSSA9_CTRIPH (0x00080000)
/* Group 9 */
#define MCU_INT_XBAR_CMPSSB0_CTRIPL (0x00000001)
#define MCU_INT_XBAR_CMPSSB0_CTRIPH (0x00000002)
#define MCU_INT_XBAR_CMPSSB1_CTRIPL (0x00000004)
#define MCU_INT_XBAR_CMPSSB1_CTRIPH (0x00000008)
#define MCU_INT_XBAR_CMPSSB2_CTRIPL (0x00000010)
#define MCU_INT_XBAR_CMPSSB2_CTRIPH (0x00000020)
#define MCU_INT_XBAR_CMPSSB3_CTRIPL (0x00000040)
#define MCU_INT_XBAR_CMPSSB3_CTRIPH (0x00000080)
#define MCU_INT_XBAR_CMPSSB4_CTRIPL (0x00000100)
#define MCU_INT_XBAR_CMPSSB4_CTRIPH (0x00000200)
#define MCU_INT_XBAR_CMPSSB5_CTRIPL (0x00000400)
#define MCU_INT_XBAR_CMPSSB5_CTRIPH (0x00000800)
#define MCU_INT_XBAR_CMPSSB6_CTRIPL (0x00001000)
#define MCU_INT_XBAR_CMPSSB6_CTRIPH (0x00002000)
#define MCU_INT_XBAR_CMPSSB7_CTRIPL (0x00004000)
#define MCU_INT_XBAR_CMPSSB7_CTRIPH (0x00008000)
#define MCU_INT_XBAR_CMPSSB8_CTRIPL (0x00010000)
#define MCU_INT_XBAR_CMPSSB8_CTRIPH (0x00020000)
#define MCU_INT_XBAR_CMPSSB9_CTRIPL (0x00040000)
#define MCU_INT_XBAR_CMPSSB9_CTRIPH (0x00080000)

/**************************************************************************
    MCU InputCrossbar INPUT Macros
**************************************************************************/

#define MCU_INPUT_XBAR_GPIO0           (0)
#define MCU_INPUT_XBAR_GPIO1           (1)
#define MCU_INPUT_XBAR_GPIO2           (2)
#define MCU_INPUT_XBAR_GPIO3           (3)
#define MCU_INPUT_XBAR_GPIO4           (4)
#define MCU_INPUT_XBAR_GPIO5           (5)
#define MCU_INPUT_XBAR_GPIO6           (6)
#define MCU_INPUT_XBAR_GPIO7           (7)
#define MCU_INPUT_XBAR_GPIO8           (8)
#define MCU_INPUT_XBAR_GPIO9           (9)
#define MCU_INPUT_XBAR_GPIO10          (10)
#define MCU_INPUT_XBAR_GPIO11          (11)
#define MCU_INPUT_XBAR_GPIO12          (12)
#define MCU_INPUT_XBAR_GPIO13          (13)
#define MCU_INPUT_XBAR_GPIO14          (14)
#define MCU_INPUT_XBAR_GPIO15          (15)
#define MCU_INPUT_XBAR_GPIO16          (16)
#define MCU_INPUT_XBAR_GPIO17          (17)
#define MCU_INPUT_XBAR_GPIO18          (18)
#define MCU_INPUT_XBAR_GPIO19          (19)
#define MCU_INPUT_XBAR_GPIO20          (20)
#define MCU_INPUT_XBAR_GPIO21          (21)
#define MCU_INPUT_XBAR_GPIO22          (22)
#define MCU_INPUT_XBAR_GPIO23          (23)
#define MCU_INPUT_XBAR_GPIO24          (24)
#define MCU_INPUT_XBAR_GPIO25          (25)
#define MCU_INPUT_XBAR_GPIO26          (26)
#define MCU_INPUT_XBAR_GPIO27          (27)
#define MCU_INPUT_XBAR_GPIO28          (28)
#define MCU_INPUT_XBAR_GPIO29          (29)
#define MCU_INPUT_XBAR_GPIO30          (30)
#define MCU_INPUT_XBAR_GPIO31          (31)
#define MCU_INPUT_XBAR_GPIO32          (32)
#define MCU_INPUT_XBAR_GPIO33          (33)
#define MCU_INPUT_XBAR_GPIO34          (34)
#define MCU_INPUT_XBAR_GPIO35          (35)
#define MCU_INPUT_XBAR_GPIO36          (36)
#define MCU_INPUT_XBAR_GPIO37          (37)
#define MCU_INPUT_XBAR_GPIO38          (38)
#define MCU_INPUT_XBAR_GPIO39          (39)
#define MCU_INPUT_XBAR_GPIO40          (40)
#define MCU_INPUT_XBAR_GPIO41          (41)
#define MCU_INPUT_XBAR_GPIO42          (42)
#define MCU_INPUT_XBAR_GPIO43          (43)
#define MCU_INPUT_XBAR_GPIO44          (44)
#define MCU_INPUT_XBAR_GPIO45          (45)
#define MCU_INPUT_XBAR_GPIO46          (46)
#define MCU_INPUT_XBAR_GPIO47          (47)
#define MCU_INPUT_XBAR_GPIO48          (48)
#define MCU_INPUT_XBAR_GPIO49          (49)
#define MCU_INPUT_XBAR_GPIO50          (50)
#define MCU_INPUT_XBAR_GPIO51          (51)
#define MCU_INPUT_XBAR_GPIO52          (52)
#define MCU_INPUT_XBAR_GPIO53          (53)
#define MCU_INPUT_XBAR_GPIO54          (54)
#define MCU_INPUT_XBAR_GPIO55          (55)
#define MCU_INPUT_XBAR_GPIO56          (56)
#define MCU_INPUT_XBAR_GPIO57          (57)
#define MCU_INPUT_XBAR_GPIO58          (58)
#define MCU_INPUT_XBAR_GPIO59          (59)
#define MCU_INPUT_XBAR_GPIO60          (60)
#define MCU_INPUT_XBAR_GPIO61          (61)
#define MCU_INPUT_XBAR_GPIO62          (62)
#define MCU_INPUT_XBAR_GPIO63          (63)
#define MCU_INPUT_XBAR_GPIO64          (64)
#define MCU_INPUT_XBAR_GPIO65          (65)
#define MCU_INPUT_XBAR_GPIO66          (66)
#define MCU_INPUT_XBAR_GPIO67          (67)
#define MCU_INPUT_XBAR_GPIO68          (68)
#define MCU_INPUT_XBAR_GPIO69          (69)
#define MCU_INPUT_XBAR_GPIO70          (70)
#define MCU_INPUT_XBAR_GPIO71          (71)
#define MCU_INPUT_XBAR_GPIO72          (72)
#define MCU_INPUT_XBAR_GPIO73          (73)
#define MCU_INPUT_XBAR_GPIO74          (74)
#define MCU_INPUT_XBAR_GPIO75          (75)
#define MCU_INPUT_XBAR_GPIO76          (76)
#define MCU_INPUT_XBAR_GPIO77          (77)
#define MCU_INPUT_XBAR_GPIO78          (78)
#define MCU_INPUT_XBAR_GPIO79          (79)
#define MCU_INPUT_XBAR_GPIO80          (80)
#define MCU_INPUT_XBAR_GPIO81          (81)
#define MCU_INPUT_XBAR_GPIO82          (82)
#define MCU_INPUT_XBAR_GPIO83          (83)
#define MCU_INPUT_XBAR_GPIO84          (84)
#define MCU_INPUT_XBAR_GPIO85          (85)
#define MCU_INPUT_XBAR_GPIO86          (86)
#define MCU_INPUT_XBAR_GPIO87          (87)
#define MCU_INPUT_XBAR_GPIO88          (88)
#define MCU_INPUT_XBAR_GPIO89          (89)
#define MCU_INPUT_XBAR_GPIO90          (90)
#define MCU_INPUT_XBAR_GPIO91          (91)
#define MCU_INPUT_XBAR_GPIO92          (92)
#define MCU_INPUT_XBAR_GPIO93          (93)
#define MCU_INPUT_XBAR_GPIO94          (94)
#define MCU_INPUT_XBAR_GPIO95          (95)
#define MCU_INPUT_XBAR_GPIO96          (96)
#define MCU_INPUT_XBAR_GPIO97          (97)
#define MCU_INPUT_XBAR_GPIO98          (98)
#define MCU_INPUT_XBAR_GPIO99          (99)
#define MCU_INPUT_XBAR_GPIO100         (100)
#define MCU_INPUT_XBAR_GPIO101         (101)
#define MCU_INPUT_XBAR_GPIO102         (102)
#define MCU_INPUT_XBAR_GPIO103         (103)
#define MCU_INPUT_XBAR_GPIO104         (104)
#define MCU_INPUT_XBAR_GPIO105         (105)
#define MCU_INPUT_XBAR_GPIO106         (106)
#define MCU_INPUT_XBAR_GPIO107         (107)
#define MCU_INPUT_XBAR_GPIO108         (108)
#define MCU_INPUT_XBAR_GPIO109         (109)
#define MCU_INPUT_XBAR_GPIO110         (110)
#define MCU_INPUT_XBAR_GPIO111         (111)
#define MCU_INPUT_XBAR_GPIO112         (112)
#define MCU_INPUT_XBAR_GPIO113         (113)
#define MCU_INPUT_XBAR_GPIO114         (114)
#define MCU_INPUT_XBAR_GPIO115         (115)
#define MCU_INPUT_XBAR_GPIO116         (116)
#define MCU_INPUT_XBAR_GPIO117         (117)
#define MCU_INPUT_XBAR_GPIO118         (118)
#define MCU_INPUT_XBAR_GPIO119         (119)
#define MCU_INPUT_XBAR_GPIO120         (120)
#define MCU_INPUT_XBAR_GPIO121         (121)
#define MCU_INPUT_XBAR_GPIO122         (122)
#define MCU_INPUT_XBAR_GPIO123         (123)
#define MCU_INPUT_XBAR_GPIO124         (124)
#define MCU_INPUT_XBAR_GPIO125         (125)
#define MCU_INPUT_XBAR_GPIO126         (126)
#define MCU_INPUT_XBAR_GPIO127         (127)
#define MCU_INPUT_XBAR_GPIO128         (128)
#define MCU_INPUT_XBAR_GPIO129         (129)
#define MCU_INPUT_XBAR_GPIO130         (130)
#define MCU_INPUT_XBAR_GPIO131         (131)
#define MCU_INPUT_XBAR_GPIO132         (132)
#define MCU_INPUT_XBAR_GPIO133         (133)
#define MCU_INPUT_XBAR_GPIO134         (134)
#define MCU_INPUT_XBAR_GPIO135         (135)
#define MCU_INPUT_XBAR_GPIO136         (136)
#define MCU_INPUT_XBAR_GPIO137         (137)
#define MCU_INPUT_XBAR_GPIO138         (138)
#define MCU_INPUT_XBAR_GPIO139         (139)
#define MCU_INPUT_XBAR_GPIO140         (140)
#define MCU_INPUT_XBAR_GPIO141         (141)
#define MCU_INPUT_XBAR_GPIO142         (142)
#define MCU_INPUT_XBAR_GPIO143         (143)
#define MCU_INPUT_XBAR_ICSSGPO0_PORT0  (0)
#define MCU_INPUT_XBAR_ICSSGPO1_PORT0  (1)
#define MCU_INPUT_XBAR_ICSSGPO2_PORT0  (2)
#define MCU_INPUT_XBAR_ICSSGPO3_PORT0  (3)
#define MCU_INPUT_XBAR_ICSSGPO4_PORT0  (4)
#define MCU_INPUT_XBAR_ICSSGPO5_PORT0  (5)
#define MCU_INPUT_XBAR_ICSSGPO6_PORT0  (6)
#define MCU_INPUT_XBAR_ICSSGPO7_PORT0  (7)
#define MCU_INPUT_XBAR_ICSSGPO8_PORT0  (8)
#define MCU_INPUT_XBAR_ICSSGPO9_PORT0  (9)
#define MCU_INPUT_XBAR_ICSSGPO10_PORT0 (10)
#define MCU_INPUT_XBAR_ICSSGPO11_PORT0 (11)
#define MCU_INPUT_XBAR_ICSSGPO12_PORT0 (12)
#define MCU_INPUT_XBAR_ICSSGPO13_PORT0 (13)
#define MCU_INPUT_XBAR_ICSSGPO14_PORT0 (14)
#define MCU_INPUT_XBAR_ICSSGPO15_PORT0 (15)
#define MCU_INPUT_XBAR_ICSSGPO0_PORT1  (16)
#define MCU_INPUT_XBAR_ICSSGPO1_PORT1  (17)
#define MCU_INPUT_XBAR_ICSSGPO2_PORT1  (18)
#define MCU_INPUT_XBAR_ICSSGPO3_PORT1  (19)
#define MCU_INPUT_XBAR_ICSSGPO4_PORT1  (20)
#define MCU_INPUT_XBAR_ICSSGPO5_PORT1  (21)
#define MCU_INPUT_XBAR_ICSSGPO6_PORT1  (22)
#define MCU_INPUT_XBAR_ICSSGPO7_PORT1  (23)
#define MCU_INPUT_XBAR_ICSSGPO8_PORT1  (24)
#define MCU_INPUT_XBAR_ICSSGPO9_PORT1  (25)
#define MCU_INPUT_XBAR_ICSSGPO10_PORT1 (26)
#define MCU_INPUT_XBAR_ICSSGPO11_PORT1 (27)
#define MCU_INPUT_XBAR_ICSSGPO12_PORT1 (28)
#define MCU_INPUT_XBAR_ICSSGPO13_PORT1 (29)
#define MCU_INPUT_XBAR_ICSSGPO14_PORT1 (30)
#define MCU_INPUT_XBAR_ICSSGPO15_PORT1 (31)

/**************************************************************************
    MCU GPIO Xbar Input Macros
**************************************************************************/
#define MCU_GPIO_0   0
#define MCU_GPIO_1   1
#define MCU_GPIO_2   2
#define MCU_GPIO_3   3
#define MCU_GPIO_4   4
#define MCU_GPIO_5   5
#define MCU_GPIO_6   6
#define MCU_GPIO_7   7
#define MCU_GPIO_8   8
#define MCU_GPIO_9   9
#define MCU_GPIO_10  10
#define MCU_GPIO_11  11
#define MCU_GPIO_12  12
#define MCU_GPIO_13  13
#define MCU_GPIO_14  14
#define MCU_GPIO_15  15
#define MCU_GPIO_16  16
#define MCU_GPIO_17  17
#define MCU_GPIO_18  18
#define MCU_GPIO_19  19
#define MCU_GPIO_20  20
#define MCU_GPIO_21  21
#define MCU_GPIO_22  22
#define MCU_GPIO_23  23
#define MCU_GPIO_24  24
#define MCU_GPIO_25  25
#define MCU_GPIO_26  26
#define MCU_GPIO_27  27
#define MCU_GPIO_28  28
#define MCU_GPIO_29  29
#define MCU_GPIO_30  30
#define MCU_GPIO_31  31
#define MCU_GPIO_32  32
#define MCU_GPIO_33  33
#define MCU_GPIO_34  34
#define MCU_GPIO_35  35
#define MCU_GPIO_36  36
#define MCU_GPIO_37  37
#define MCU_GPIO_38  38
#define MCU_GPIO_39  39
#define MCU_GPIO_40  40
#define MCU_GPIO_41  41
#define MCU_GPIO_42  42
#define MCU_GPIO_43  43
#define MCU_GPIO_44  44
#define MCU_GPIO_45  45
#define MCU_GPIO_46  46
#define MCU_GPIO_47  47
#define MCU_GPIO_48  48
#define MCU_GPIO_49  49
#define MCU_GPIO_50  50
#define MCU_GPIO_51  51
#define MCU_GPIO_52  52
#define MCU_GPIO_53  53
#define MCU_GPIO_54  54
#define MCU_GPIO_55  55
#define MCU_GPIO_56  56
#define MCU_GPIO_57  57
#define MCU_GPIO_58  58
#define MCU_GPIO_59  59
#define MCU_GPIO_60  60
#define MCU_GPIO_61  61
#define MCU_GPIO_62  62
#define MCU_GPIO_63  63
#define MCU_GPIO_64  64
#define MCU_GPIO_65  65
#define MCU_GPIO_66  66
#define MCU_GPIO_67  67
#define MCU_GPIO_68  68
#define MCU_GPIO_69  69
#define MCU_GPIO_70  70
#define MCU_GPIO_71  71
#define MCU_GPIO_72  72
#define MCU_GPIO_73  73
#define MCU_GPIO_74  74
#define MCU_GPIO_75  75
#define MCU_GPIO_76  76
#define MCU_GPIO_77  77
#define MCU_GPIO_78  78
#define MCU_GPIO_79  79
#define MCU_GPIO_80  80
#define MCU_GPIO_81  81
#define MCU_GPIO_82  82
#define MCU_GPIO_83  83
#define MCU_GPIO_84  84
#define MCU_GPIO_85  85
#define MCU_GPIO_86  86
#define MCU_GPIO_87  87
#define MCU_GPIO_88  88
#define MCU_GPIO_89  89
#define MCU_GPIO_90  90
#define MCU_GPIO_91  91
#define MCU_GPIO_92  92
#define MCU_GPIO_93  93
#define MCU_GPIO_94  94
#define MCU_GPIO_95  95
#define MCU_GPIO_96  96
#define MCU_GPIO_97  97
#define MCU_GPIO_98  98
#define MCU_GPIO_99  99
#define MCU_GPIO_100 100
#define MCU_GPIO_101 101
#define MCU_GPIO_102 102
#define MCU_GPIO_103 103
#define MCU_GPIO_104 104
#define MCU_GPIO_105 105
#define MCU_GPIO_106 106
#define MCU_GPIO_107 107
#define MCU_GPIO_108 108
#define MCU_GPIO_109 109
#define MCU_GPIO_110 110
#define MCU_GPIO_111 111
#define MCU_GPIO_112 112
#define MCU_GPIO_113 113
#define MCU_GPIO_114 114
#define MCU_GPIO_115 115
#define MCU_GPIO_116 116
#define MCU_GPIO_117 117
#define MCU_GPIO_118 118
#define MCU_GPIO_119 119
#define MCU_GPIO_120 120
#define MCU_GPIO_121 121
#define MCU_GPIO_122 122
#define MCU_GPIO_123 123
#define MCU_GPIO_124 124
#define MCU_GPIO_125 125
#define MCU_GPIO_126 126
#define MCU_GPIO_127 127
#define MCU_GPIO_128 128
#define MCU_GPIO_129 129
#define MCU_GPIO_130 130
#define MCU_GPIO_131 131
#define MCU_GPIO_132 132
#define MCU_GPIO_133 133
#define MCU_GPIO_134 134
#define MCU_GPIO_135 135
#define MCU_GPIO_136 136
#define MCU_GPIO_137 137
#define MCU_GPIO_138 138
#define MCU_GPIO_139 139

#define MCU_GPIO_0_BANK_INTR_0 144
#define MCU_GPIO_0_BANK_INTR_1 145
#define MCU_GPIO_0_BANK_INTR_2 146
#define MCU_GPIO_0_BANK_INTR_3 147
#define MCU_GPIO_0_BANK_INTR_4 148
#define MCU_GPIO_0_BANK_INTR_5 149
#define MCU_GPIO_0_BANK_INTR_6 150
#define MCU_GPIO_0_BANK_INTR_7 151
#define MCU_GPIO_0_BANK_INTR_8 152

#define MCU_GPIO_1_BANK_INTR_0 153
#define MCU_GPIO_1_BANK_INTR_1 154
#define MCU_GPIO_1_BANK_INTR_2 155
#define MCU_GPIO_1_BANK_INTR_3 156
#define MCU_GPIO_1_BANK_INTR_4 157
#define MCU_GPIO_1_BANK_INTR_5 158
#define MCU_GPIO_1_BANK_INTR_6 159
#define MCU_GPIO_1_BANK_INTR_7 160
#define MCU_GPIO_1_BANK_INTR_8 161

#define MCU_GPIO_2_BANK_INTR_0 162
#define MCU_GPIO_2_BANK_INTR_1 163
#define MCU_GPIO_2_BANK_INTR_2 164
#define MCU_GPIO_2_BANK_INTR_3 165
#define MCU_GPIO_2_BANK_INTR_4 166
#define MCU_GPIO_2_BANK_INTR_5 167
#define MCU_GPIO_2_BANK_INTR_6 168
#define MCU_GPIO_2_BANK_INTR_7 169
#define MCU_GPIO_2_BANK_INTR_8 170

#define MCU_GPIO_3_BANK_INTR_0 171
#define MCU_GPIO_3_BANK_INTR_1 172
#define MCU_GPIO_3_BANK_INTR_2 173
#define MCU_GPIO_3_BANK_INTR_3 174
#define MCU_GPIO_3_BANK_INTR_4 175
#define MCU_GPIO_3_BANK_INTR_5 176
#define MCU_GPIO_3_BANK_INTR_6 177
#define MCU_GPIO_3_BANK_INTR_7 178
#define MCU_GPIO_3_BANK_INTR_8 179

/**************************************************************************
    MCU GPIO Xbar Output Macros
**************************************************************************/
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_0 0
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_1 1
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_2 2
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_3 3

#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_0 4
#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_1 5
#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_2 6
#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_3 7

#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_0 8
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_1 9
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_2 10
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_3 11
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_4 12
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_5 13

#define MCU_GPIO_INT_XBAR_VIM_MODULE0_0 14
#define MCU_GPIO_INT_XBAR_VIM_MODULE0_1 15
#define MCU_GPIO_INT_XBAR_VIM_MODULE0_2 16
#define MCU_GPIO_INT_XBAR_VIM_MODULE0_3 17

#define MCU_GPIO_INT_XBAR_VIM_MODULE1_0 18
#define MCU_GPIO_INT_XBAR_VIM_MODULE1_1 19
#define MCU_GPIO_INT_XBAR_VIM_MODULE1_2 20
#define MCU_GPIO_INT_XBAR_VIM_MODULE1_3 21

#define MCU_GPIO_INT_XBAR_VIM_MODULE2_0 22
#define MCU_GPIO_INT_XBAR_VIM_MODULE2_1 23
#define MCU_GPIO_INT_XBAR_VIM_MODULE2_2 24
#define MCU_GPIO_INT_XBAR_VIM_MODULE2_3 25

#define MCU_GPIO_INT_XBAR_VIM_MODULE3_0 26
#define MCU_GPIO_INT_XBAR_VIM_MODULE3_1 27
#define MCU_GPIO_INT_XBAR_VIM_MODULE3_2 28
#define MCU_GPIO_INT_XBAR_VIM_MODULE3_3 29

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static inline void MCU_xbarSelectInterruptXBarInputSource(uint32 base, uint32 out, uint32 group0_mask,
                                                          uint32 group1_mask, uint32 group2_mask, uint32 group3_mask,
                                                          uint32 group4_mask, uint32 group5_mask, uint32 group6_mask);
static inline void MCU_xbarSelectInterruptXBarInputSourceExtended(uint32 base, uint32 out, uint32 group0_mask,
                                                                  uint32 group1_mask, uint32 group2_mask,
                                                                  uint32 group3_mask, uint32 group4_mask,
                                                                  uint32 group5_mask, uint32 group6_mask,
                                                                  uint32 group7_mask, uint32 group8_mask,
                                                                  uint32 group9_mask);

static inline void MCU_xbarSelectInputXBarInputSource(uint32 base, uint32 out, uint32 group_select, uint32 group0_mask,
                                                      uint32 group1_mask);

static inline void MCU_xbarSelectGpioIntrXbarInputSource(uint32 base, uint32 out, uint32 mux_control);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

/**
 * \brief Trip & Sync xbar: API to select input sources of Interrupt XBar
 *
 * \param base [in] Interrupt XBar base address
 * \param out [in] Instance of Interrupt XBar
 * \param group0_mask [in] Mask to OR inputs from group 0
 * \param group1_mask [in] Mask to OR inputs from group 1
 * \param group2_mask [in] Mask to OR inputs from group 2
 * \param group3_mask [in] Mask to OR inputs from group 3
 * \param group4_mask [in] Mask to OR inputs from group 4
 * \param group5_mask [in] Mask to OR inputs from group 5
 * \param group6_mask [in] Mask to OR inputs from group 6
 *
 */
static inline void MCU_xbarSelectInterruptXBarInputSource(uint32 base, uint32 out, uint32 group0_mask,
                                                          uint32 group1_mask, uint32 group2_mask, uint32 group3_mask,
                                                          uint32 group4_mask, uint32 group5_mask, uint32 group6_mask)
{
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0,
                group0_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G1,
                group1_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G2,
                group2_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G3,
                group3_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G4,
                group4_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G5,
                group5_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G6,
                group6_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_MASK);
}

/**
 * \brief Trip & Sync xbar: API to select input sources of Interrupt XBar
 *
 * \param base [in] Interrupt XBar base address
 * \param out [in] Instance of Interrupt XBar
 * \param group0_mask [in] Mask to OR inputs from group 0
 * \param group1_mask [in] Mask to OR inputs from group 1
 * \param group2_mask [in] Mask to OR inputs from group 2
 * \param group3_mask [in] Mask to OR inputs from group 3
 * \param group4_mask [in] Mask to OR inputs from group 4
 * \param group5_mask [in] Mask to OR inputs from group 5
 * \param group6_mask [in] Mask to OR inputs from group 6
 * \param group7_mask [in] Mask to OR inputs from group 7
 * \param group8_mask [in] Mask to OR inputs from group 8
 * \param group9_mask [in] Mask to OR inputs from group 9
 *
 */
static inline void MCU_xbarSelectInterruptXBarInputSourceExtended(uint32 base, uint32 out, uint32 group0_mask,
                                                                  uint32 group1_mask, uint32 group2_mask,
                                                                  uint32 group3_mask, uint32 group4_mask,
                                                                  uint32 group5_mask, uint32 group6_mask,
                                                                  uint32 group7_mask, uint32 group8_mask,
                                                                  uint32 group9_mask)
{
    MCU_xbarSelectInterruptXBarInputSource(base, out, group0_mask, group1_mask, group2_mask, group3_mask, group4_mask,
                                           group5_mask, group6_mask);
    HW_WR_REG32(base + (uint32)(out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + (uint32)MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G7,
                (uint32)(group7_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G7_SEL_MASK));
    HW_WR_REG32(base + (uint32)(out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + (uint32)MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G8,
                (uint32)(group8_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G8_SEL_MASK));
    HW_WR_REG32(base + (uint32)(out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + (uint32)MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G9,
                (uint32)(group9_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G9_SEL_MASK));
}

/**
 * \brief Trip & Sync xbar: API to select input source of Input XBar
 *
 * \param base [in] Input XBar base address
 * \param out [in] Instance of Input XBar
 * \param group0_muxctl [in] Mux control to select input from group 0 mux
 * \param group1_muxctl [in] Mux control to select input from group 1 mux
 * \param group_select [in] Mux control to select group 0 or 1
 *
 */
static inline void MCU_xbarSelectInputXBarInputSource(uint32 base, uint32 out, uint32 group_select, uint32 group0_mask,
                                                      uint32 group1_mask)
{
    HW_WR_REG32(
        (base + (uint32)MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL) + (uint32)(out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
        (uint32)(group_select & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL_GSEL_MASK));
    HW_WR_REG32(
        (base + (uint32)MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0) + (uint32)(out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
        group0_mask & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(
        (base + (uint32)MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1) + (uint32)(out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
        (uint32)(group1_mask & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1_SEL_MASK));
}

static inline void MCU_xbarSelectGpioIntrXbarInputSource(uint32 base, uint32 out, uint32 mux_control)
{
    HW_WR_REG32(
        base + MCU_CSL_GPIO_INTR_XBAR_MUXCNTL(out),
        (MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_INT_ENABLE_MASK) | (mux_control & MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_ENABLE_MASK));
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCU_XBAR_H_ */
