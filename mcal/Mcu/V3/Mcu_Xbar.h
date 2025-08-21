/*
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
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
#include "hw_types.h"

/* Register Macros */
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0       (0x00000100U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G1       (0x00000104U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G2       (0x00000108U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G3       (0x0000010CU)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G4       (0x00000110U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G5       (0x00000114U)
#define MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G6       (0x00000118U)
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
#define MCU_CSL_CONTROLSS_INTXBAR_U_BASE   (0x502D5000U)
#define MCU_CSL_CONTROLSS_INPUTXBAR_U_BASE (0x502D0000U)

/* GPIO_XBAR_INTR Macros */
#define MCU_CSL_GPIO_INTR_XBAR_U_BASE                  (0x52E02000U)
#define MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_INT_ENABLE_MASK (0x00010000U)
#define MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_ENABLE_MASK     (0x000000FFU)
#define MCU_CSL_GPIO_INTR_XBAR_MUXCNTL(MUXCNTL)        (0x00000004U + ((MUXCNTL) * 0x4U))

/* List of interrupt crossbar sources
 */
#define MCU_INTRXBAR0_OUT_0  0U
#define MCU_INTRXBAR0_OUT_1  1U
#define MCU_INTRXBAR0_OUT_2  2U
#define MCU_INTRXBAR0_OUT_3  3U
#define MCU_INTRXBAR0_OUT_4  4U
#define MCU_INTRXBAR0_OUT_5  5U
#define MCU_INTRXBAR0_OUT_6  6U
#define MCU_INTRXBAR0_OUT_7  7U
#define MCU_INTRXBAR0_OUT_8  8U
#define MCU_INTRXBAR0_OUT_9  9U
#define MCU_INTRXBAR0_OUT_10 10U
#define MCU_INTRXBAR0_OUT_11 11U
#define MCU_INTRXBAR0_OUT_12 12U
#define MCU_INTRXBAR0_OUT_13 13U
#define MCU_INTRXBAR0_OUT_14 14U
#define MCU_INTRXBAR0_OUT_15 15U
#define MCU_INTRXBAR0_OUT_16 16U
#define MCU_INTRXBAR0_OUT_17 17U
#define MCU_INTRXBAR0_OUT_18 18U
#define MCU_INTRXBAR0_OUT_19 19U
#define MCU_INTRXBAR0_OUT_20 20U
#define MCU_INTRXBAR0_OUT_21 21U
#define MCU_INTRXBAR0_OUT_22 22U
#define MCU_INTRXBAR0_OUT_23 23U
#define MCU_INTRXBAR0_OUT_24 24U
#define MCU_INTRXBAR0_OUT_25 25U
#define MCU_INTRXBAR0_OUT_26 26U
#define MCU_INTRXBAR0_OUT_27 27U
#define MCU_INTRXBAR0_OUT_28 28U
#define MCU_INTRXBAR0_OUT_29 29U
#define MCU_INTRXBAR0_OUT_30 30U
#define MCU_INTRXBAR0_OUT_31 31U

/* List of input crossbar sources
 */
#define MCU_INPUT_XBAR0_OUT_0  0U
#define MCU_INPUT_XBAR0_OUT_1  1U
#define MCU_INPUT_XBAR0_OUT_2  2U
#define MCU_INPUT_XBAR0_OUT_3  3U
#define MCU_INPUT_XBAR0_OUT_4  4U
#define MCU_INPUT_XBAR0_OUT_5  5U
#define MCU_INPUT_XBAR0_OUT_6  6U
#define MCU_INPUT_XBAR0_OUT_7  7U
#define MCU_INPUT_XBAR0_OUT_8  8U
#define MCU_INPUT_XBAR0_OUT_9  9U
#define MCU_INPUT_XBAR0_OUT_10 10U
#define MCU_INPUT_XBAR0_OUT_11 11U
#define MCU_INPUT_XBAR0_OUT_12 12U
#define MCU_INPUT_XBAR0_OUT_13 13U
#define MCU_INPUT_XBAR0_OUT_14 14U
#define MCU_INPUT_XBAR0_OUT_15 15U
#define MCU_INPUT_XBAR0_OUT_16 16U
#define MCU_INPUT_XBAR0_OUT_17 17U
#define MCU_INPUT_XBAR0_OUT_18 18U
#define MCU_INPUT_XBAR0_OUT_19 19U
#define MCU_INPUT_XBAR0_OUT_20 20U
#define MCU_INPUT_XBAR0_OUT_21 21U
#define MCU_INPUT_XBAR0_OUT_22 22U
#define MCU_INPUT_XBAR0_OUT_23 23U
#define MCU_INPUT_XBAR0_OUT_24 24U
#define MCU_INPUT_XBAR0_OUT_25 25U
#define MCU_INPUT_XBAR0_OUT_26 26U
#define MCU_INPUT_XBAR0_OUT_27 27U
#define MCU_INPUT_XBAR0_OUT_28 28U
#define MCU_INPUT_XBAR0_OUT_29 29U
#define MCU_INPUT_XBAR0_OUT_30 30U
#define MCU_INPUT_XBAR0_OUT_31 31U

/**************************************************************************
    Mcu Interrupt XBAR INPUT Macros
**************************************************************************/

#define MCU_INT_XBAR_EPWM0_INT       (0x00000001U)
#define MCU_INT_XBAR_EPWM1_INT       (0x00000002U)
#define MCU_INT_XBAR_EPWM2_INT       (0x00000004U)
#define MCU_INT_XBAR_EPWM3_INT       (0x00000008U)
#define MCU_INT_XBAR_EPWM4_INT       (0x00000010U)
#define MCU_INT_XBAR_EPWM5_INT       (0x00000020U)
#define MCU_INT_XBAR_EPWM6_INT       (0x00000040U)
#define MCU_INT_XBAR_EPWM7_INT       (0x00000080U)
#define MCU_INT_XBAR_EPWM8_INT       (0x00000100U)
#define MCU_INT_XBAR_EPWM9_INT       (0x00000200U)
#define MCU_INT_XBAR_EPWM0_TZINT     (0x00000001U)
#define MCU_INT_XBAR_EPWM1_TZINT     (0x00000002U)
#define MCU_INT_XBAR_EPWM2_TZINT     (0x00000004U)
#define MCU_INT_XBAR_EPWM3_TZINT     (0x00000008U)
#define MCU_INT_XBAR_EPWM4_TZINT     (0x00000010U)
#define MCU_INT_XBAR_EPWM5_TZINT     (0x00000020U)
#define MCU_INT_XBAR_EPWM6_TZINT     (0x00000040U)
#define MCU_INT_XBAR_EPWM7_TZINT     (0x00000080U)
#define MCU_INT_XBAR_EPWM8_TZINT     (0x00000100U)
#define MCU_INT_XBAR_EPWM9_TZINT     (0x00000200U)
#define MCU_INT_XBAR_ADC0_INT1       (0x00000001U)
#define MCU_INT_XBAR_ADC0_INT2       (0x00000002U)
#define MCU_INT_XBAR_ADC0_INT3       (0x00000004U)
#define MCU_INT_XBAR_ADC0_INT4       (0x00000008U)
#define MCU_INT_XBAR_ADC0_EVTINT     (0x00000010U)
#define MCU_INT_XBAR_ADC1_INT1       (0x00000020U)
#define MCU_INT_XBAR_ADC1_INT2       (0x00000040U)
#define MCU_INT_XBAR_ADC1_INT3       (0x00000080U)
#define MCU_INT_XBAR_ADC1_INT4       (0x00000100U)
#define MCU_INT_XBAR_ADC1_EVTINT     (0x00000200U)
#define MCU_INT_XBAR_ADC2_INT1       (0x00000400U)
#define MCU_INT_XBAR_ADC2_INT2       (0x00000800U)
#define MCU_INT_XBAR_ADC2_INT3       (0x00001000U)
#define MCU_INT_XBAR_ADC2_INT4       (0x00002000U)
#define MCU_INT_XBAR_ADC2_EVTINT     (0x00004000U)
#define MCU_INT_XBAR_FSIRX0_INT1N    (0x00000001U)
#define MCU_INT_XBAR_FSIRX0_INT2N    (0x00000002U)
#define MCU_INT_XBAR_FSITX0_INT1N    (0x00000100U)
#define MCU_INT_XBAR_FSITX0_INT2N    (0x00000200U)
#define MCU_INT_XBAR_SD0_ERR         (0x00000001U)
#define MCU_INT_XBAR_SD0_FILT0_DRINT (0x00000002U)
#define MCU_INT_XBAR_SD0_FILT1_DRINT (0x00000004U)
#define MCU_INT_XBAR_SD0_FILT2_DRINT (0x00000008U)
#define MCU_INT_XBAR_SD0_FILT3_DRINT (0x00000010U)
#define MCU_INT_XBAR_ECAP0_INT       (0x00000001U)
#define MCU_INT_XBAR_ECAP1_INT       (0x00000002U)
#define MCU_INT_XBAR_ECAP2_INT       (0x00000004U)
#define MCU_INT_XBAR_ECAP3_INT       (0x00000008U)
#define MCU_INT_XBAR_ECAP4_INT       (0x00000010U)
#define MCU_INT_XBAR_ECAP5_INT       (0x00000020U)
#define MCU_INT_XBAR_ECAP6_INT       (0x00000040U)
#define MCU_INT_XBAR_ECAP7_INT       (0x00000080U)
#define MCU_INT_XBAR_EQEP0_INT       (0x00000001U)
#define MCU_INT_XBAR_EQEP1_INT       (0x00000002U)

/**************************************************************************
    MCU InputCrossbar INPUT Macros
**************************************************************************/

#define MCU_INPUT_XBAR_GPIO0           (0U)
#define MCU_INPUT_XBAR_GPIO1           (1U)
#define MCU_INPUT_XBAR_GPIO2           (2U)
#define MCU_INPUT_XBAR_GPIO3           (3U)
#define MCU_INPUT_XBAR_GPIO4           (4U)
#define MCU_INPUT_XBAR_GPIO5           (5U)
#define MCU_INPUT_XBAR_GPIO6           (6U)
#define MCU_INPUT_XBAR_GPIO7           (7U)
#define MCU_INPUT_XBAR_GPIO8           (8U)
#define MCU_INPUT_XBAR_GPIO9           (9U)
#define MCU_INPUT_XBAR_GPIO10          (10U)
#define MCU_INPUT_XBAR_GPIO11          (11U)
#define MCU_INPUT_XBAR_GPIO12          (12U)
#define MCU_INPUT_XBAR_GPIO13          (13U)
#define MCU_INPUT_XBAR_GPIO14          (14U)
#define MCU_INPUT_XBAR_GPIO15          (15U)
#define MCU_INPUT_XBAR_GPIO16          (16U)
#define MCU_INPUT_XBAR_GPIO17          (17U)
#define MCU_INPUT_XBAR_GPIO18          (18U)
#define MCU_INPUT_XBAR_GPIO19          (19U)
#define MCU_INPUT_XBAR_GPIO20          (20U)
#define MCU_INPUT_XBAR_GPIO21          (21U)
#define MCU_INPUT_XBAR_GPIO22          (22U)
#define MCU_INPUT_XBAR_GPIO23          (23U)
#define MCU_INPUT_XBAR_GPIO24          (24U)
#define MCU_INPUT_XBAR_GPIO25          (25U)
#define MCU_INPUT_XBAR_GPIO26          (26U)
#define MCU_INPUT_XBAR_GPIO27          (27U)
#define MCU_INPUT_XBAR_GPIO28          (28U)
#define MCU_INPUT_XBAR_GPIO29          (29U)
#define MCU_INPUT_XBAR_GPIO30          (30U)
#define MCU_INPUT_XBAR_GPIO31          (31U)
#define MCU_INPUT_XBAR_GPIO32          (32U)
#define MCU_INPUT_XBAR_GPIO33          (33U)
#define MCU_INPUT_XBAR_GPIO34          (34U)
#define MCU_INPUT_XBAR_GPIO35          (35U)
#define MCU_INPUT_XBAR_GPIO36          (36U)
#define MCU_INPUT_XBAR_GPIO37          (37U)
#define MCU_INPUT_XBAR_GPIO38          (38U)
#define MCU_INPUT_XBAR_GPIO39          (39U)
#define MCU_INPUT_XBAR_GPIO40          (40U)
#define MCU_INPUT_XBAR_GPIO41          (41U)
#define MCU_INPUT_XBAR_GPIO42          (42U)
#define MCU_INPUT_XBAR_GPIO43          (43U)
#define MCU_INPUT_XBAR_GPIO44          (44U)
#define MCU_INPUT_XBAR_GPIO45          (45U)
#define MCU_INPUT_XBAR_GPIO46          (46U)
#define MCU_INPUT_XBAR_GPIO47          (47U)
#define MCU_INPUT_XBAR_GPIO48          (48U)
#define MCU_INPUT_XBAR_GPIO49          (49U)
#define MCU_INPUT_XBAR_GPIO50          (50U)
#define MCU_INPUT_XBAR_GPIO51          (51U)
#define MCU_INPUT_XBAR_GPIO52          (52U)
#define MCU_INPUT_XBAR_GPIO53          (53U)
#define MCU_INPUT_XBAR_GPIO54          (54U)
#define MCU_INPUT_XBAR_GPIO55          (55U)
#define MCU_INPUT_XBAR_GPIO56          (56U)
#define MCU_INPUT_XBAR_GPIO57          (57U)
#define MCU_INPUT_XBAR_GPIO58          (58U)
#define MCU_INPUT_XBAR_GPIO59          (59U)
#define MCU_INPUT_XBAR_GPIO60          (60U)
#define MCU_INPUT_XBAR_GPIO61          (61U)
#define MCU_INPUT_XBAR_GPIO62          (62U)
#define MCU_INPUT_XBAR_GPIO63          (63U)
#define MCU_INPUT_XBAR_GPIO64          (64U)
#define MCU_INPUT_XBAR_GPIO65          (65U)
#define MCU_INPUT_XBAR_GPIO66          (66U)
#define MCU_INPUT_XBAR_GPIO67          (67U)
#define MCU_INPUT_XBAR_GPIO68          (68U)
#define MCU_INPUT_XBAR_GPIO69          (69U)
#define MCU_INPUT_XBAR_GPIO70          (70U)
#define MCU_INPUT_XBAR_GPIO71          (71U)
#define MCU_INPUT_XBAR_GPIO72          (72U)
#define MCU_INPUT_XBAR_GPIO73          (73U)
#define MCU_INPUT_XBAR_GPIO74          (74U)
#define MCU_INPUT_XBAR_GPIO75          (75U)
#define MCU_INPUT_XBAR_GPIO76          (76U)
#define MCU_INPUT_XBAR_GPIO77          (77U)
#define MCU_INPUT_XBAR_GPIO78          (78U)
#define MCU_INPUT_XBAR_GPIO79          (79U)
#define MCU_INPUT_XBAR_GPIO80          (80U)
#define MCU_INPUT_XBAR_GPIO81          (81U)
#define MCU_INPUT_XBAR_GPIO82          (82U)
#define MCU_INPUT_XBAR_GPIO83          (83U)
#define MCU_INPUT_XBAR_GPIO84          (84U)
#define MCU_INPUT_XBAR_GPIO85          (85U)
#define MCU_INPUT_XBAR_GPIO86          (86U)
#define MCU_INPUT_XBAR_GPIO87          (87U)
#define MCU_INPUT_XBAR_GPIO88          (88U)
#define MCU_INPUT_XBAR_GPIO89          (89U)
#define MCU_INPUT_XBAR_GPIO90          (90U)
#define MCU_INPUT_XBAR_GPIO91          (91U)
#define MCU_INPUT_XBAR_GPIO92          (92U)
#define MCU_INPUT_XBAR_GPIO93          (93U)
#define MCU_INPUT_XBAR_GPIO94          (94U)
#define MCU_INPUT_XBAR_GPIO95          (95U)
#define MCU_INPUT_XBAR_GPIO96          (96U)
#define MCU_INPUT_XBAR_GPIO97          (97U)
#define MCU_INPUT_XBAR_GPIO98          (98U)
#define MCU_INPUT_XBAR_GPIO99          (99U)
#define MCU_INPUT_XBAR_GPIO100         (100U)
#define MCU_INPUT_XBAR_GPIO101         (101U)
#define MCU_INPUT_XBAR_GPIO102         (102U)
#define MCU_INPUT_XBAR_GPIO103         (103U)
#define MCU_INPUT_XBAR_GPIO104         (104U)
#define MCU_INPUT_XBAR_GPIO105         (105U)
#define MCU_INPUT_XBAR_GPIO106         (106U)
#define MCU_INPUT_XBAR_GPIO107         (107U)
#define MCU_INPUT_XBAR_GPIO108         (108U)
#define MCU_INPUT_XBAR_GPIO109         (109U)
#define MCU_INPUT_XBAR_GPIO110         (110U)
#define MCU_INPUT_XBAR_GPIO111         (111U)
#define MCU_INPUT_XBAR_GPIO112         (112U)
#define MCU_INPUT_XBAR_GPIO113         (113U)
#define MCU_INPUT_XBAR_GPIO114         (114U)
#define MCU_INPUT_XBAR_GPIO115         (115U)
#define MCU_INPUT_XBAR_GPIO116         (116U)
#define MCU_INPUT_XBAR_GPIO117         (117U)
#define MCU_INPUT_XBAR_GPIO118         (118U)
#define MCU_INPUT_XBAR_GPIO119         (119U)
#define MCU_INPUT_XBAR_GPIO120         (120U)
#define MCU_INPUT_XBAR_GPIO121         (121U)
#define MCU_INPUT_XBAR_GPIO122         (122U)
#define MCU_INPUT_XBAR_GPIO123         (123U)
#define MCU_INPUT_XBAR_GPIO124         (124U)
#define MCU_INPUT_XBAR_GPIO125         (125U)
#define MCU_INPUT_XBAR_GPIO126         (126U)
#define MCU_INPUT_XBAR_GPIO127         (127U)
#define MCU_INPUT_XBAR_GPIO128         (128U)
#define MCU_INPUT_XBAR_GPIO129         (129U)
#define MCU_INPUT_XBAR_GPIO130         (130U)
#define MCU_INPUT_XBAR_GPIO131         (131U)
#define MCU_INPUT_XBAR_GPIO132         (132U)
#define MCU_INPUT_XBAR_GPIO133         (133U)
#define MCU_INPUT_XBAR_GPIO134         (134U)
#define MCU_INPUT_XBAR_GPIO135         (135U)
#define MCU_INPUT_XBAR_GPIO136         (136U)
#define MCU_INPUT_XBAR_GPIO137         (137U)
#define MCU_INPUT_XBAR_GPIO138         (138U)
#define MCU_INPUT_XBAR_GPIO139         (139U)
#define MCU_INPUT_XBAR_GPIO140         (140U)
#define MCU_INPUT_XBAR_GPIO141         (141U)
#define MCU_INPUT_XBAR_GPIO142         (142U)
#define MCU_INPUT_XBAR_GPIO143         (143U)
#define MCU_INPUT_XBAR_ICSSGPO0_PORT0  (0U)
#define MCU_INPUT_XBAR_ICSSGPO1_PORT0  (1U)
#define MCU_INPUT_XBAR_ICSSGPO2_PORT0  (2U)
#define MCU_INPUT_XBAR_ICSSGPO3_PORT0  (3U)
#define MCU_INPUT_XBAR_ICSSGPO4_PORT0  (4U)
#define MCU_INPUT_XBAR_ICSSGPO5_PORT0  (5U)
#define MCU_INPUT_XBAR_ICSSGPO6_PORT0  (6U)
#define MCU_INPUT_XBAR_ICSSGPO7_PORT0  (7U)
#define MCU_INPUT_XBAR_ICSSGPO8_PORT0  (8U)
#define MCU_INPUT_XBAR_ICSSGPO9_PORT0  (9U)
#define MCU_INPUT_XBAR_ICSSGPO10_PORT0 (10U)
#define MCU_INPUT_XBAR_ICSSGPO11_PORT0 (11U)
#define MCU_INPUT_XBAR_ICSSGPO12_PORT0 (12U)
#define MCU_INPUT_XBAR_ICSSGPO13_PORT0 (13U)
#define MCU_INPUT_XBAR_ICSSGPO14_PORT0 (14U)
#define MCU_INPUT_XBAR_ICSSGPO15_PORT0 (15U)
#define MCU_INPUT_XBAR_ICSSGPO0_PORT1  (16U)
#define MCU_INPUT_XBAR_ICSSGPO1_PORT1  (17U)
#define MCU_INPUT_XBAR_ICSSGPO2_PORT1  (18U)
#define MCU_INPUT_XBAR_ICSSGPO3_PORT1  (19U)
#define MCU_INPUT_XBAR_ICSSGPO4_PORT1  (20U)
#define MCU_INPUT_XBAR_ICSSGPO5_PORT1  (21U)
#define MCU_INPUT_XBAR_ICSSGPO6_PORT1  (22U)
#define MCU_INPUT_XBAR_ICSSGPO7_PORT1  (23U)
#define MCU_INPUT_XBAR_ICSSGPO8_PORT1  (24U)
#define MCU_INPUT_XBAR_ICSSGPO9_PORT1  (25U)
#define MCU_INPUT_XBAR_ICSSGPO10_PORT1 (26U)
#define MCU_INPUT_XBAR_ICSSGPO11_PORT1 (27U)
#define MCU_INPUT_XBAR_ICSSGPO12_PORT1 (28U)
#define MCU_INPUT_XBAR_ICSSGPO13_PORT1 (29U)
#define MCU_INPUT_XBAR_ICSSGPO14_PORT1 (30U)
#define MCU_INPUT_XBAR_ICSSGPO15_PORT1 (31U)

/**************************************************************************
    MCU GPIO Xbar Input Macros
**************************************************************************/
#define MCU_GPIO_0   0U
#define MCU_GPIO_1   1U
#define MCU_GPIO_2   2U
#define MCU_GPIO_3   3U
#define MCU_GPIO_4   4U
#define MCU_GPIO_5   5U
#define MCU_GPIO_6   6U
#define MCU_GPIO_7   7U
#define MCU_GPIO_8   8U
#define MCU_GPIO_9   9U
#define MCU_GPIO_10  10U
#define MCU_GPIO_11  11U
#define MCU_GPIO_12  12U
#define MCU_GPIO_13  13U
#define MCU_GPIO_14  14U
#define MCU_GPIO_15  15U
#define MCU_GPIO_16  16U
#define MCU_GPIO_17  17U
#define MCU_GPIO_18  18U
#define MCU_GPIO_19  19U
#define MCU_GPIO_20  20U
#define MCU_GPIO_21  21U
#define MCU_GPIO_22  22U
#define MCU_GPIO_23  23U
#define MCU_GPIO_24  24U
#define MCU_GPIO_25  25U
#define MCU_GPIO_26  26U
#define MCU_GPIO_27  27U
#define MCU_GPIO_28  28U
#define MCU_GPIO_29  29U
#define MCU_GPIO_30  30U
#define MCU_GPIO_31  31U
#define MCU_GPIO_32  32U
#define MCU_GPIO_33  33U
#define MCU_GPIO_34  34U
#define MCU_GPIO_35  35U
#define MCU_GPIO_36  36U
#define MCU_GPIO_37  37U
#define MCU_GPIO_38  38U
#define MCU_GPIO_39  39U
#define MCU_GPIO_40  40U
#define MCU_GPIO_41  41U
#define MCU_GPIO_42  42U
#define MCU_GPIO_43  43U
#define MCU_GPIO_44  44U
#define MCU_GPIO_45  45U
#define MCU_GPIO_46  46U
#define MCU_GPIO_47  47U
#define MCU_GPIO_48  48U
#define MCU_GPIO_49  49U
#define MCU_GPIO_50  50U
#define MCU_GPIO_51  51U
#define MCU_GPIO_52  52U
#define MCU_GPIO_53  53U
#define MCU_GPIO_54  54U
#define MCU_GPIO_55  55U
#define MCU_GPIO_56  56U
#define MCU_GPIO_57  57U
#define MCU_GPIO_58  58U
#define MCU_GPIO_59  59U
#define MCU_GPIO_60  60U
#define MCU_GPIO_61  61U
#define MCU_GPIO_62  62U
#define MCU_GPIO_63  63U
#define MCU_GPIO_64  64U
#define MCU_GPIO_65  65U
#define MCU_GPIO_66  66U
#define MCU_GPIO_67  67U
#define MCU_GPIO_68  68U
#define MCU_GPIO_69  69U
#define MCU_GPIO_70  70U
#define MCU_GPIO_71  71U
#define MCU_GPIO_72  72U
#define MCU_GPIO_73  73U
#define MCU_GPIO_74  74U
#define MCU_GPIO_75  75U
#define MCU_GPIO_76  76U
#define MCU_GPIO_77  77U
#define MCU_GPIO_78  78U
#define MCU_GPIO_79  79U
#define MCU_GPIO_80  80U
#define MCU_GPIO_81  81U
#define MCU_GPIO_82  82U
#define MCU_GPIO_83  83U
#define MCU_GPIO_84  84U
#define MCU_GPIO_85  85U
#define MCU_GPIO_86  86U
#define MCU_GPIO_87  87U
#define MCU_GPIO_88  88U
#define MCU_GPIO_89  89U
#define MCU_GPIO_90  90U
#define MCU_GPIO_91  91U
#define MCU_GPIO_92  92U
#define MCU_GPIO_93  93U
#define MCU_GPIO_94  94U
#define MCU_GPIO_95  95U
#define MCU_GPIO_96  96U
#define MCU_GPIO_97  97U
#define MCU_GPIO_98  98U
#define MCU_GPIO_99  99U
#define MCU_GPIO_100 100U
#define MCU_GPIO_101 101U
#define MCU_GPIO_102 102U
#define MCU_GPIO_103 103U
#define MCU_GPIO_104 104U
#define MCU_GPIO_105 105U
#define MCU_GPIO_106 106U
#define MCU_GPIO_107 107U
#define MCU_GPIO_108 108U
#define MCU_GPIO_109 109U
#define MCU_GPIO_110 110U
#define MCU_GPIO_111 111U
#define MCU_GPIO_112 112U
#define MCU_GPIO_113 113U
#define MCU_GPIO_114 114U
#define MCU_GPIO_115 115U
#define MCU_GPIO_116 116U
#define MCU_GPIO_117 117U
#define MCU_GPIO_118 118U
#define MCU_GPIO_119 119U
#define MCU_GPIO_120 120U
#define MCU_GPIO_121 121U
#define MCU_GPIO_122 122U
#define MCU_GPIO_123 123U
#define MCU_GPIO_124 124U
#define MCU_GPIO_125 125U
#define MCU_GPIO_126 126U
#define MCU_GPIO_127 127U
#define MCU_GPIO_128 128U
#define MCU_GPIO_129 129U
#define MCU_GPIO_130 130U
#define MCU_GPIO_131 131U
#define MCU_GPIO_132 132U
#define MCU_GPIO_133 133U
#define MCU_GPIO_134 134U
#define MCU_GPIO_135 135U
#define MCU_GPIO_136 136U
#define MCU_GPIO_137 137U
#define MCU_GPIO_138 138U
#define MCU_GPIO_139 139U

#define MCU_GPIO_0_BANK_INTR_0 144U
#define MCU_GPIO_0_BANK_INTR_1 145U
#define MCU_GPIO_0_BANK_INTR_2 146U
#define MCU_GPIO_0_BANK_INTR_3 147U
#define MCU_GPIO_0_BANK_INTR_4 148U
#define MCU_GPIO_0_BANK_INTR_5 149U
#define MCU_GPIO_0_BANK_INTR_6 150U
#define MCU_GPIO_0_BANK_INTR_7 151U
#define MCU_GPIO_0_BANK_INTR_8 152U

#define MCU_GPIO_1_BANK_INTR_0 153U
#define MCU_GPIO_1_BANK_INTR_1 154U
#define MCU_GPIO_1_BANK_INTR_2 155U
#define MCU_GPIO_1_BANK_INTR_3 156U
#define MCU_GPIO_1_BANK_INTR_4 157U
#define MCU_GPIO_1_BANK_INTR_5 158U
#define MCU_GPIO_1_BANK_INTR_6 159U
#define MCU_GPIO_1_BANK_INTR_7 160U
#define MCU_GPIO_1_BANK_INTR_8 161U

#define MCU_GPIO_2_BANK_INTR_0 162U
#define MCU_GPIO_2_BANK_INTR_1 163U
#define MCU_GPIO_2_BANK_INTR_2 164U
#define MCU_GPIO_2_BANK_INTR_3 165U
#define MCU_GPIO_2_BANK_INTR_4 166U
#define MCU_GPIO_2_BANK_INTR_5 167U
#define MCU_GPIO_2_BANK_INTR_6 168U
#define MCU_GPIO_2_BANK_INTR_7 169U
#define MCU_GPIO_2_BANK_INTR_8 170U

#define MCU_GPIO_3_BANK_INTR_0 171U
#define MCU_GPIO_3_BANK_INTR_1 172U
#define MCU_GPIO_3_BANK_INTR_2 173U
#define MCU_GPIO_3_BANK_INTR_3 174U
#define MCU_GPIO_3_BANK_INTR_4 175U
#define MCU_GPIO_3_BANK_INTR_5 176U
#define MCU_GPIO_3_BANK_INTR_6 177U
#define MCU_GPIO_3_BANK_INTR_7 178U
#define MCU_GPIO_3_BANK_INTR_8 179U

/**************************************************************************
    MCU GPIO Xbar Output Macros
**************************************************************************/
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_0 0U
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_1 1U
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_2 2U
#define MCU_GPIO_INT_XBAR_ICSS_XBAR_3 3U

#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_0 4U
#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_1 5U
#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_2 6U
#define MCU_GPIO_INT_XBAR_DMA_TRIG_XBAR_3 7U

#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_0 8U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_1 9U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_2 10U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_3 11U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_4 12U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_XBAR1_5 13U

#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_0 14U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_1 15U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_2 16U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_3 17U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_4 18U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_5 19U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_6 20U
#define MCU_GPIO_INT_XBAR_SOC_TIMESYNC_ICSS1_7 21U

#define MCU_GPIO_INT_XBAR_VIM_MODULE0_0 22U
#define MCU_GPIO_INT_XBAR_VIM_MODULE0_1 23U
#define MCU_GPIO_INT_XBAR_VIM_MODULE0_2 24U
#define MCU_GPIO_INT_XBAR_VIM_MODULE0_3 25U

#define MCU_GPIO_INT_XBAR_VIM_MODULE1_0 26U
#define MCU_GPIO_INT_XBAR_VIM_MODULE1_1 27U
#define MCU_GPIO_INT_XBAR_VIM_MODULE1_2 28U
#define MCU_GPIO_INT_XBAR_VIM_MODULE1_3 29U

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static inline void MCU_xbarSelectInterruptXBarInputSource(uint32 base, uint32 out, uint32 group0_mask,
                                                          uint32 group1_mask, uint32 group2_mask, uint32 group3_mask,
                                                          uint32 group4_mask, uint32 group5_mask, uint32 group6_mask);

static inline void MCU_xbarSelectInputXBarInputSource(uint32 base, uint32 out, uint32 group_select, uint32 group0_mask,
                                                      uint32 group1_mask);

static inline void MCU_xbarSelectGpioIntrXbarInputSource(uint32 base, uint32 out, uint32 mux_control);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

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
    // TBD: 32 bit field required?
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
    HW_WR_REG32(base + MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL + (out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
                group_select & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL_GSEL_MASK);
    HW_WR_REG32(base + MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0 + (out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
                group0_mask & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(base + MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1 + (out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
                group1_mask & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1_SEL_MASK);
}

static inline void MCU_xbarSelectGpioIntrXbarInputSource(uint32 base, uint32 out, uint32 mux_control)
{
    HW_WR_REG32(
        base + MCU_CSL_GPIO_INTR_XBAR_MUXCNTL(out),
        (MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_INT_ENABLE_MASK) | (mux_control & MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_ENABLE_MASK));
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCU_XBAR_H_ */
