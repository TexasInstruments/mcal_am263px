/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2025 Texas Instruments Incorporated
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

/*
 * Hw_Cpsw_Cpts.h
 *
 * Register-level header file for CPSW_CPTS
 */

#ifndef HW_CPSW_CPTS_H_
#define HW_CPSW_CPTS_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
* Register Definitions
*******************************************************************************/

#define CPSW_CPTS_IDVER_REG                                      (0x0003D000U)
#define CPSW_CPTS_CONTROL_REG                                    (0x0003D004U)
#define CPSW_CPTS_RFTCLK_SEL_REG                                 (0x0003D008U)
#define CPSW_CPTS_TS_PUSH_REG                                    (0x0003D00CU)
#define CPSW_CPTS_TS_LOAD_VAL_REG                                (0x0003D010U)
#define CPSW_CPTS_TS_LOAD_EN_REG                                 (0x0003D014U)
#define CPSW_CPTS_TS_COMP_VAL_REG                                (0x0003D018U)
#define CPSW_CPTS_TS_COMP_LEN_REG                                (0x0003D01CU)
#define CPSW_CPTS_INTSTAT_RAW_REG                                (0x0003D020U)
#define CPSW_CPTS_INTSTAT_MASKED_REG                             (0x0003D024U)
#define CPSW_CPTS_INT_ENABLE_REG                                 (0x0003D028U)
#define CPSW_CPTS_TS_COMP_NUDGE_REG                              (0x0003D02CU)
#define CPSW_CPTS_EVENT_POP_REG                                  (0x0003D030U)
#define CPSW_CPTS_EVENT_0_REG                                    (0x0003D034U)
#define CPSW_CPTS_EVENT_1_REG                                    (0x0003D038U)
#define CPSW_CPTS_EVENT_2_REG                                    (0x0003D03CU)
#define CPSW_CPTS_EVENT_3_REG                                    (0x0003D040U)
#define CPSW_CPTS_TS_LOAD_HIGH_VAL_REG                           (0x0003D044U)
#define CPSW_CPTS_TS_COMP_HIGH_VAL_REG                           (0x0003D048U)
#define CPSW_CPTS_TS_ADD_VAL_REG                                 (0x0003D04CU)
#define CPSW_CPTS_TS_PPM_LOW_VAL_REG                             (0x0003D050U)
#define CPSW_CPTS_TS_PPM_HIGH_VAL_REG                            (0x0003D054U)
#define CPSW_CPTS_TS_NUDGE_VAL_REG                               (0x0003D058U)
#define CPSW_CPTS_TS_GENF_COMP_LOW_REG(TS_GENF)                  (0x0003D0E0U+((TS_GENF)*0x20U))
#define CPSW_CPTS_TS_GENF_COMP_HIGH_REG(TS_GENF)                 (0x0003D0E4U+((TS_GENF)*0x20U))
#define CPSW_CPTS_TS_GENF_CONTROL_REG(TS_GENF)                   (0x0003D0E8U+((TS_GENF)*0x20U))
#define CPSW_CPTS_TS_GENF_LENGTH_REG(TS_GENF)                    (0x0003D0ECU+((TS_GENF)*0x20U))
#define CPSW_CPTS_TS_GENF_PPM_LOW_REG(TS_GENF)                   (0x0003D0F0U+((TS_GENF)*0x20U))
#define CPSW_CPTS_TS_GENF_PPM_HIGH_REG(TS_GENF)                  (0x0003D0F4U+((TS_GENF)*0x20U))
#define CPSW_CPTS_TS_GENF_NUDGE_REG(TS_GENF)                     (0x0003D0F8U+((TS_GENF)*0x20U))
#define CPSW_CPTS_TS_ESTF_COMP_LOW_REG                           (0x0003D200U)
#define CPSW_CPTS_TS_ESTF_COMP_HIGH_REG                          (0x0003D204U)
#define CPSW_CPTS_TS_ESTF_CONTROL_REG                            (0x0003D208U)
#define CPSW_CPTS_TS_ESTF_LENGTH_REG                             (0x0003D20CU)
#define CPSW_CPTS_TS_ESTF_PPM_LOW_REG                            (0x0003D210U)
#define CPSW_CPTS_TS_ESTF_PPM_HIGH_REG                           (0x0003D214U)
#define CPSW_CPTS_TS_ESTF_NUDGE_REG                              (0x0003D218U)


/*******************************************************************************
* Field Definition Macros
*******************************************************************************/

/* COMP_LOW_REG */

#define CPSW_CPTS_TS_GENF_COMP_LOW_REG_COMP_LOW_MASK             (0xFFFFFFFFU)
#define CPSW_CPTS_TS_GENF_COMP_LOW_REG_COMP_LOW_SHIFT            (0x00000000U)
#define CPSW_CPTS_TS_GENF_COMP_LOW_REG_COMP_LOW_MAX              (0xFFFFFFFFU)

/* COMP_HIGH_REG */

#define CPSW_CPTS_TS_GENF_COMP_HIGH_REG_COMP_HIGH_MASK           (0xFFFFFFFFU)
#define CPSW_CPTS_TS_GENF_COMP_HIGH_REG_COMP_HIGH_SHIFT          (0x00000000U)
#define CPSW_CPTS_TS_GENF_COMP_HIGH_REG_COMP_HIGH_MAX            (0xFFFFFFFFU)

/* CONTROL_REG */

#define CPSW_CPTS_TS_GENF_CONTROL_REG_PPM_DIR_MASK               (0x00000001U)
#define CPSW_CPTS_TS_GENF_CONTROL_REG_PPM_DIR_SHIFT              (0x00000000U)
#define CPSW_CPTS_TS_GENF_CONTROL_REG_PPM_DIR_MAX                (0x00000001U)

#define CPSW_CPTS_TS_GENF_CONTROL_REG_POLARITY_INV_MASK          (0x00000002U)
#define CPSW_CPTS_TS_GENF_CONTROL_REG_POLARITY_INV_SHIFT         (0x00000001U)
#define CPSW_CPTS_TS_GENF_CONTROL_REG_POLARITY_INV_MAX           (0x00000001U)

/* LENGTH_REG */

#define CPSW_CPTS_TS_GENF_LENGTH_REG_LENGTH_MASK                 (0xFFFFFFFFU)
#define CPSW_CPTS_TS_GENF_LENGTH_REG_LENGTH_SHIFT                (0x00000000U)
#define CPSW_CPTS_TS_GENF_LENGTH_REG_LENGTH_MAX                  (0xFFFFFFFFU)

/* PPM_LOW_REG */

#define CPSW_CPTS_TS_GENF_PPM_LOW_REG_PPM_LOW_MASK               (0xFFFFFFFFU)
#define CPSW_CPTS_TS_GENF_PPM_LOW_REG_PPM_LOW_SHIFT              (0x00000000U)
#define CPSW_CPTS_TS_GENF_PPM_LOW_REG_PPM_LOW_MAX                (0xFFFFFFFFU)

/* PPM_HIGH_REG */

#define CPSW_CPTS_TS_GENF_PPM_HIGH_REG_PPM_HIGH_MASK             (0x000003FFU)
#define CPSW_CPTS_TS_GENF_PPM_HIGH_REG_PPM_HIGH_SHIFT            (0x00000000U)
#define CPSW_CPTS_TS_GENF_PPM_HIGH_REG_PPM_HIGH_MAX              (0x000003FFU)

/* NUDGE_REG */

#define CPSW_CPTS_TS_GENF_NUDGE_REG_NUDGE_MASK                   (0x000000FFU)
#define CPSW_CPTS_TS_GENF_NUDGE_REG_NUDGE_SHIFT                  (0x00000000U)
#define CPSW_CPTS_TS_GENF_NUDGE_REG_NUDGE_MAX                    (0x000000FFU)

/* COMP_LOW_REG */

#define CPSW_CPTS_TS_ESTF_COMP_LOW_REG_COMP_LOW_MASK             (0xFFFFFFFFU)
#define CPSW_CPTS_TS_ESTF_COMP_LOW_REG_COMP_LOW_SHIFT            (0x00000000U)
#define CPSW_CPTS_TS_ESTF_COMP_LOW_REG_COMP_LOW_MAX              (0xFFFFFFFFU)

/* COMP_HIGH_REG */

#define CPSW_CPTS_TS_ESTF_COMP_HIGH_REG_COMP_HIGH_MASK           (0xFFFFFFFFU)
#define CPSW_CPTS_TS_ESTF_COMP_HIGH_REG_COMP_HIGH_SHIFT          (0x00000000U)
#define CPSW_CPTS_TS_ESTF_COMP_HIGH_REG_COMP_HIGH_MAX            (0xFFFFFFFFU)

/* CONTROL_REG */

#define CPSW_CPTS_TS_ESTF_CONTROL_REG_PPM_DIR_MASK               (0x00000001U)
#define CPSW_CPTS_TS_ESTF_CONTROL_REG_PPM_DIR_SHIFT              (0x00000000U)
#define CPSW_CPTS_TS_ESTF_CONTROL_REG_PPM_DIR_MAX                (0x00000001U)

#define CPSW_CPTS_TS_ESTF_CONTROL_REG_POLARITY_INV_MASK          (0x00000002U)
#define CPSW_CPTS_TS_ESTF_CONTROL_REG_POLARITY_INV_SHIFT         (0x00000001U)
#define CPSW_CPTS_TS_ESTF_CONTROL_REG_POLARITY_INV_MAX           (0x00000001U)

/* LENGTH_REG */

#define CPSW_CPTS_TS_ESTF_LENGTH_REG_LENGTH_MASK                 (0xFFFFFFFFU)
#define CPSW_CPTS_TS_ESTF_LENGTH_REG_LENGTH_SHIFT                (0x00000000U)
#define CPSW_CPTS_TS_ESTF_LENGTH_REG_LENGTH_MAX                  (0xFFFFFFFFU)

/* PPM_LOW_REG */

#define CPSW_CPTS_TS_ESTF_PPM_LOW_REG_PPM_LOW_MASK               (0xFFFFFFFFU)
#define CPSW_CPTS_TS_ESTF_PPM_LOW_REG_PPM_LOW_SHIFT              (0x00000000U)
#define CPSW_CPTS_TS_ESTF_PPM_LOW_REG_PPM_LOW_MAX                (0xFFFFFFFFU)

/* PPM_HIGH_REG */

#define CPSW_CPTS_TS_ESTF_PPM_HIGH_REG_PPM_HIGH_MASK             (0x000003FFU)
#define CPSW_CPTS_TS_ESTF_PPM_HIGH_REG_PPM_HIGH_SHIFT            (0x00000000U)
#define CPSW_CPTS_TS_ESTF_PPM_HIGH_REG_PPM_HIGH_MAX              (0x000003FFU)

/* NUDGE_REG */

#define CPSW_CPTS_TS_ESTF_NUDGE_REG_NUDGE_MASK                   (0x000000FFU)
#define CPSW_CPTS_TS_ESTF_NUDGE_REG_NUDGE_SHIFT                  (0x00000000U)
#define CPSW_CPTS_TS_ESTF_NUDGE_REG_NUDGE_MAX                    (0x000000FFU)

/* IDVER_REG */

#define CPSW_CPTS_IDVER_REG_MINOR_VER_MASK                       (0x000000FFU)
#define CPSW_CPTS_IDVER_REG_MINOR_VER_SHIFT                      (0x00000000U)
#define CPSW_CPTS_IDVER_REG_MINOR_VER_MAX                        (0x000000FFU)

#define CPSW_CPTS_IDVER_REG_MAJOR_VER_MASK                       (0x00000700U)
#define CPSW_CPTS_IDVER_REG_MAJOR_VER_SHIFT                      (0x00000008U)
#define CPSW_CPTS_IDVER_REG_MAJOR_VER_MAX                        (0x00000007U)

#define CPSW_CPTS_IDVER_REG_RTL_VER_MASK                         (0x0000F800U)
#define CPSW_CPTS_IDVER_REG_RTL_VER_SHIFT                        (0x0000000BU)
#define CPSW_CPTS_IDVER_REG_RTL_VER_MAX                          (0x0000001FU)

#define CPSW_CPTS_IDVER_REG_TX_IDENT_MASK                        (0xFFFF0000U)
#define CPSW_CPTS_IDVER_REG_TX_IDENT_SHIFT                       (0x00000010U)
#define CPSW_CPTS_IDVER_REG_TX_IDENT_MAX                         (0x0000FFFFU)

/* CONTROL_REG */

#define CPSW_CPTS_CONTROL_REG_CPTS_EN_MASK                       (0x00000001U)
#define CPSW_CPTS_CONTROL_REG_CPTS_EN_SHIFT                      (0x00000000U)
#define CPSW_CPTS_CONTROL_REG_CPTS_EN_MAX                        (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_INT_TEST_MASK                      (0x00000002U)
#define CPSW_CPTS_CONTROL_REG_INT_TEST_SHIFT                     (0x00000001U)
#define CPSW_CPTS_CONTROL_REG_INT_TEST_MAX                       (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_TS_COMP_POLARITY_MASK              (0x00000004U)
#define CPSW_CPTS_CONTROL_REG_TS_COMP_POLARITY_SHIFT             (0x00000002U)
#define CPSW_CPTS_CONTROL_REG_TS_COMP_POLARITY_MAX               (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_TSTAMP_EN_MASK                     (0x00000008U)
#define CPSW_CPTS_CONTROL_REG_TSTAMP_EN_SHIFT                    (0x00000003U)
#define CPSW_CPTS_CONTROL_REG_TSTAMP_EN_MAX                      (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_SEQUENCE_EN_MASK                   (0x00000010U)
#define CPSW_CPTS_CONTROL_REG_SEQUENCE_EN_SHIFT                  (0x00000004U)
#define CPSW_CPTS_CONTROL_REG_SEQUENCE_EN_MAX                    (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_MODE_MASK                          (0x00000020U)
#define CPSW_CPTS_CONTROL_REG_MODE_SHIFT                         (0x00000005U)
#define CPSW_CPTS_CONTROL_REG_MODE_MAX                           (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_TS_COMP_TOG_MASK                   (0x00000040U)
#define CPSW_CPTS_CONTROL_REG_TS_COMP_TOG_SHIFT                  (0x00000006U)
#define CPSW_CPTS_CONTROL_REG_TS_COMP_TOG_MAX                    (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_TS_PPM_DIR_MASK                    (0x00000080U)
#define CPSW_CPTS_CONTROL_REG_TS_PPM_DIR_SHIFT                   (0x00000007U)
#define CPSW_CPTS_CONTROL_REG_TS_PPM_DIR_MAX                     (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW1_TS_PUSH_EN_MASK                (0x00000100U)
#define CPSW_CPTS_CONTROL_REG_HW1_TS_PUSH_EN_SHIFT               (0x00000008U)
#define CPSW_CPTS_CONTROL_REG_HW1_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW2_TS_PUSH_EN_MASK                (0x00000200U)
#define CPSW_CPTS_CONTROL_REG_HW2_TS_PUSH_EN_SHIFT               (0x00000009U)
#define CPSW_CPTS_CONTROL_REG_HW2_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW3_TS_PUSH_EN_MASK                (0x00000400U)
#define CPSW_CPTS_CONTROL_REG_HW3_TS_PUSH_EN_SHIFT               (0x0000000AU)
#define CPSW_CPTS_CONTROL_REG_HW3_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW4_TS_PUSH_EN_MASK                (0x00000800U)
#define CPSW_CPTS_CONTROL_REG_HW4_TS_PUSH_EN_SHIFT               (0x0000000BU)
#define CPSW_CPTS_CONTROL_REG_HW4_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW5_TS_PUSH_EN_MASK                (0x00001000U)
#define CPSW_CPTS_CONTROL_REG_HW5_TS_PUSH_EN_SHIFT               (0x0000000CU)
#define CPSW_CPTS_CONTROL_REG_HW5_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW6_TS_PUSH_EN_MASK                (0x00002000U)
#define CPSW_CPTS_CONTROL_REG_HW6_TS_PUSH_EN_SHIFT               (0x0000000DU)
#define CPSW_CPTS_CONTROL_REG_HW6_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW7_TS_PUSH_EN_MASK                (0x00004000U)
#define CPSW_CPTS_CONTROL_REG_HW7_TS_PUSH_EN_SHIFT               (0x0000000EU)
#define CPSW_CPTS_CONTROL_REG_HW7_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_HW8_TS_PUSH_EN_MASK                (0x00008000U)
#define CPSW_CPTS_CONTROL_REG_HW8_TS_PUSH_EN_SHIFT               (0x0000000FU)
#define CPSW_CPTS_CONTROL_REG_HW8_TS_PUSH_EN_MAX                 (0x00000001U)

#define CPSW_CPTS_CONTROL_REG_TS_SYNC_SEL_MASK                   (0xF0000000U)
#define CPSW_CPTS_CONTROL_REG_TS_SYNC_SEL_SHIFT                  (0x0000001CU)
#define CPSW_CPTS_CONTROL_REG_TS_SYNC_SEL_MAX                    (0x0000000FU)

/* RFTCLK_SEL_REG */

#define CPSW_CPTS_RFTCLK_SEL_REG_RFTCLK_SEL_MASK                 (0x0000001FU)
#define CPSW_CPTS_RFTCLK_SEL_REG_RFTCLK_SEL_SHIFT                (0x00000000U)
#define CPSW_CPTS_RFTCLK_SEL_REG_RFTCLK_SEL_MAX                  (0x0000001FU)

/* TS_PUSH_REG */

#define CPSW_CPTS_TS_PUSH_REG_TS_PUSH_MASK                       (0x00000001U)
#define CPSW_CPTS_TS_PUSH_REG_TS_PUSH_SHIFT                      (0x00000000U)
#define CPSW_CPTS_TS_PUSH_REG_TS_PUSH_MAX                        (0x00000001U)

/* TS_LOAD_VAL_REG */

#define CPSW_CPTS_TS_LOAD_VAL_REG_TS_LOAD_VAL_MASK               (0xFFFFFFFFU)
#define CPSW_CPTS_TS_LOAD_VAL_REG_TS_LOAD_VAL_SHIFT              (0x00000000U)
#define CPSW_CPTS_TS_LOAD_VAL_REG_TS_LOAD_VAL_MAX                (0xFFFFFFFFU)

/* TS_LOAD_EN_REG */

#define CPSW_CPTS_TS_LOAD_EN_REG_TS_LOAD_EN_MASK                 (0x00000001U)
#define CPSW_CPTS_TS_LOAD_EN_REG_TS_LOAD_EN_SHIFT                (0x00000000U)
#define CPSW_CPTS_TS_LOAD_EN_REG_TS_LOAD_EN_MAX                  (0x00000001U)

/* TS_COMP_VAL_REG */

#define CPSW_CPTS_TS_COMP_VAL_REG_TS_COMP_VAL_MASK               (0xFFFFFFFFU)
#define CPSW_CPTS_TS_COMP_VAL_REG_TS_COMP_VAL_SHIFT              (0x00000000U)
#define CPSW_CPTS_TS_COMP_VAL_REG_TS_COMP_VAL_MAX                (0xFFFFFFFFU)

/* TS_COMP_LEN_REG */

#define CPSW_CPTS_TS_COMP_LEN_REG_TS_COMP_LENGTH_MASK            (0xFFFFFFFFU)
#define CPSW_CPTS_TS_COMP_LEN_REG_TS_COMP_LENGTH_SHIFT           (0x00000000U)
#define CPSW_CPTS_TS_COMP_LEN_REG_TS_COMP_LENGTH_MAX             (0xFFFFFFFFU)

/* INTSTAT_RAW_REG */

#define CPSW_CPTS_INTSTAT_RAW_REG_TS_PEND_RAW_MASK               (0x00000001U)
#define CPSW_CPTS_INTSTAT_RAW_REG_TS_PEND_RAW_SHIFT              (0x00000000U)
#define CPSW_CPTS_INTSTAT_RAW_REG_TS_PEND_RAW_MAX                (0x00000001U)

/* INTSTAT_MASKED_REG */

#define CPSW_CPTS_INTSTAT_MASKED_REG_TS_PEND_MASK                (0x00000001U)
#define CPSW_CPTS_INTSTAT_MASKED_REG_TS_PEND_SHIFT               (0x00000000U)
#define CPSW_CPTS_INTSTAT_MASKED_REG_TS_PEND_MAX                 (0x00000001U)

/* INT_ENABLE_REG */

#define CPSW_CPTS_INT_ENABLE_REG_TS_PEND_EN_MASK                 (0x00000001U)
#define CPSW_CPTS_INT_ENABLE_REG_TS_PEND_EN_SHIFT                (0x00000000U)
#define CPSW_CPTS_INT_ENABLE_REG_TS_PEND_EN_MAX                  (0x00000001U)

/* TS_COMP_NUDGE_REG */

#define CPSW_CPTS_TS_COMP_NUDGE_REG_NUDGE_MASK                   (0x000000FFU)
#define CPSW_CPTS_TS_COMP_NUDGE_REG_NUDGE_SHIFT                  (0x00000000U)
#define CPSW_CPTS_TS_COMP_NUDGE_REG_NUDGE_MAX                    (0x000000FFU)

/* EVENT_POP_REG */

#define CPSW_CPTS_EVENT_POP_REG_EVENT_POP_MASK                   (0x00000001U)
#define CPSW_CPTS_EVENT_POP_REG_EVENT_POP_SHIFT                  (0x00000000U)
#define CPSW_CPTS_EVENT_POP_REG_EVENT_POP_MAX                    (0x00000001U)

/* EVENT_0_REG */

#define CPSW_CPTS_EVENT_0_REG_TIME_STAMP_MASK                    (0xFFFFFFFFU)
#define CPSW_CPTS_EVENT_0_REG_TIME_STAMP_SHIFT                   (0x00000000U)
#define CPSW_CPTS_EVENT_0_REG_TIME_STAMP_MAX                     (0xFFFFFFFFU)

/* EVENT_1_REG */

#define CPSW_CPTS_EVENT_1_REG_SEQUENCE_ID_MASK                   (0x0000FFFFU)
#define CPSW_CPTS_EVENT_1_REG_SEQUENCE_ID_SHIFT                  (0x00000000U)
#define CPSW_CPTS_EVENT_1_REG_SEQUENCE_ID_MAX                    (0x0000FFFFU)

#define CPSW_CPTS_EVENT_1_REG_MESSAGE_TYPE_MASK                  (0x000F0000U)
#define CPSW_CPTS_EVENT_1_REG_MESSAGE_TYPE_SHIFT                 (0x00000010U)
#define CPSW_CPTS_EVENT_1_REG_MESSAGE_TYPE_MAX                   (0x0000000FU)

#define CPSW_CPTS_EVENT_1_REG_EVENT_TYPE_MASK                    (0x00F00000U)
#define CPSW_CPTS_EVENT_1_REG_EVENT_TYPE_SHIFT                   (0x00000014U)
#define CPSW_CPTS_EVENT_1_REG_EVENT_TYPE_MAX                     (0x0000000FU)

#define CPSW_CPTS_EVENT_1_REG_PORT_NUMBER_MASK                   (0x1F000000U)
#define CPSW_CPTS_EVENT_1_REG_PORT_NUMBER_SHIFT                  (0x00000018U)
#define CPSW_CPTS_EVENT_1_REG_PORT_NUMBER_MAX                    (0x0000001FU)

#define CPSW_CPTS_EVENT_1_REG_PREMPT_QUEUE_MASK                  (0x20000000U)
#define CPSW_CPTS_EVENT_1_REG_PREMPT_QUEUE_SHIFT                 (0x0000001DU)
#define CPSW_CPTS_EVENT_1_REG_PREMPT_QUEUE_MAX                   (0x00000001U)

/* EVENT_2_REG */

#define CPSW_CPTS_EVENT_2_REG_DOMAIN_MASK                        (0x000000FFU)
#define CPSW_CPTS_EVENT_2_REG_DOMAIN_SHIFT                       (0x00000000U)
#define CPSW_CPTS_EVENT_2_REG_DOMAIN_MAX                         (0x000000FFU)

/* EVENT_3_REG */

#define CPSW_CPTS_EVENT_3_REG_TIME_STAMP_MASK                    (0xFFFFFFFFU)
#define CPSW_CPTS_EVENT_3_REG_TIME_STAMP_SHIFT                   (0x00000000U)
#define CPSW_CPTS_EVENT_3_REG_TIME_STAMP_MAX                     (0xFFFFFFFFU)

/* TS_LOAD_HIGH_VAL_REG */

#define CPSW_CPTS_TS_LOAD_HIGH_VAL_REG_TS_LOAD_VAL_MASK          (0xFFFFFFFFU)
#define CPSW_CPTS_TS_LOAD_HIGH_VAL_REG_TS_LOAD_VAL_SHIFT         (0x00000000U)
#define CPSW_CPTS_TS_LOAD_HIGH_VAL_REG_TS_LOAD_VAL_MAX           (0xFFFFFFFFU)

/* TS_COMP_HIGH_VAL_REG */

#define CPSW_CPTS_TS_COMP_HIGH_VAL_REG_TS_COMP_HIGH_VAL_MASK     (0xFFFFFFFFU)
#define CPSW_CPTS_TS_COMP_HIGH_VAL_REG_TS_COMP_HIGH_VAL_SHIFT    (0x00000000U)
#define CPSW_CPTS_TS_COMP_HIGH_VAL_REG_TS_COMP_HIGH_VAL_MAX      (0xFFFFFFFFU)

/* TS_ADD_VAL_REG */

#define CPSW_CPTS_TS_ADD_VAL_REG_ADD_VAL_MASK                    (0x00000007U)
#define CPSW_CPTS_TS_ADD_VAL_REG_ADD_VAL_SHIFT                   (0x00000000U)
#define CPSW_CPTS_TS_ADD_VAL_REG_ADD_VAL_MAX                     (0x00000007U)

/* TS_PPM_LOW_VAL_REG */

#define CPSW_CPTS_TS_PPM_LOW_VAL_REG_TS_PPM_LOW_VAL_MASK         (0xFFFFFFFFU)
#define CPSW_CPTS_TS_PPM_LOW_VAL_REG_TS_PPM_LOW_VAL_SHIFT        (0x00000000U)
#define CPSW_CPTS_TS_PPM_LOW_VAL_REG_TS_PPM_LOW_VAL_MAX          (0xFFFFFFFFU)

/* TS_PPM_HIGH_VAL_REG */

#define CPSW_CPTS_TS_PPM_HIGH_VAL_REG_TS_PPM_HIGH_VAL_MASK       (0x000003FFU)
#define CPSW_CPTS_TS_PPM_HIGH_VAL_REG_TS_PPM_HIGH_VAL_SHIFT      (0x00000000U)
#define CPSW_CPTS_TS_PPM_HIGH_VAL_REG_TS_PPM_HIGH_VAL_MAX        (0x000003FFU)

/* TS_NUDGE_VAL_REG */

#define CPSW_CPTS_TS_NUDGE_VAL_REG_TS_NUDGE_VAL_MASK             (0x000000FFU)
#define CPSW_CPTS_TS_NUDGE_VAL_REG_TS_NUDGE_VAL_SHIFT            (0x00000000U)
#define CPSW_CPTS_TS_NUDGE_VAL_REG_TS_NUDGE_VAL_MAX              (0x000000FFU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CPSW_CPTS_H_ */

