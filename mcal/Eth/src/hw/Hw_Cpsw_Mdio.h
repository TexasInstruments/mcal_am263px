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
 * Hw_Cpsw_Mdio.h
 *
 * Register-level header file for MDIO
 *
 */

#ifndef HW_CPSW_MDIO_H_
#define HW_CPSW_MDIO_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Register Definitions
 ******************************************************************************/

#define MDIO_MDIO_VERSION_REG                                      (0x00000F00U)
#define MDIO_CONTROL_REG                                           (0x00000F04U)
#define MDIO_ALIVE_REG                                             (0x00000F08U)
#define MDIO_LINK_REG                                              (0x00000F0CU)
#define MDIO_LINK_INT_RAW_REG                                      (0x00000F10U)
#define MDIO_LINK_INT_MASKED_REG                                   (0x00000F14U)
#define MDIO_LINK_INT_MASK_SET_REG                                 (0x00000F18U)
#define MDIO_LINK_INT_MASK_CLEAR_REG                               (0x00000F1CU)
#define MDIO_USER_INT_RAW_REG                                      (0x00000F20U)
#define MDIO_USER_INT_MASKED_REG                                   (0x00000F24U)
#define MDIO_USER_INT_MASK_SET_REG                                 (0x00000F28U)
#define MDIO_USER_INT_MASK_CLEAR_REG                               (0x00000F2CU)
#define MDIO_MANUAL_IF_REG                                         (0x00000F30U)
#define MDIO_POLL_REG                                              (0x00000F34U)
#define MDIO_POLL_EN_REG                                           (0x00000F38U)
#define MDIO_CLAUS45_REG                                           (0x00000F3CU)
#define MDIO_USER_ADDR0_REG                                        (0x00000F40U)
#define MDIO_USER_ADDR1_REG                                        (0x00000F44U)
#define MDIO_USER_GROUP_USER_ACCESS_REG                            (0x00000F80U)
#define MDIO_USER_GROUP_USER_PHY_SEL_REG                           (0x00000F84U)
#define MDIO_USER_GROUP_USER_OFFSET                                (0x00000008U)

/*******************************************************************************
 * Field Definition Macros
 ******************************************************************************/

/* USER_ACCESS_REG */

#define MDIO_USER_GROUP_USER_ACCESS_REG_DATA_MASK                  (0x0000FFFFU)
#define MDIO_USER_GROUP_USER_ACCESS_REG_DATA_SHIFT                 (0x00000000U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_DATA_MAX                   (0x0000FFFFU)

#define MDIO_USER_GROUP_USER_ACCESS_REG_PHYADR_MASK                (0x001F0000U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_PHYADR_SHIFT               (0x00000010U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_PHYADR_MAX                 (0x0000001FU)

#define MDIO_USER_GROUP_USER_ACCESS_REG_REGADR_MASK                (0x03E00000U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_REGADR_SHIFT               (0x00000015U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_REGADR_MAX                 (0x0000001FU)

#define MDIO_USER_GROUP_USER_ACCESS_REG_ACK_MASK                   (0x20000000U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_ACK_SHIFT                  (0x0000001DU)
#define MDIO_USER_GROUP_USER_ACCESS_REG_ACK_PASS                   (0x00000001U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_ACK_FAIL                   (0x00000000U)

#define MDIO_USER_GROUP_USER_ACCESS_REG_WRITE_MASK                 (0x40000000U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_WRITE_SHIFT                (0x0000001EU)
#define MDIO_USER_GROUP_USER_ACCESS_REG_WRITE                      (0x00000001U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_READ                       (0x00000000U)

#define MDIO_USER_GROUP_USER_ACCESS_REG_GO_MASK                    (0x80000000U)
#define MDIO_USER_GROUP_USER_ACCESS_REG_GO_SHIFT                   (0x0000001FU)
#define MDIO_USER_GROUP_USER_ACCESS_REG_GO_MAX                     (0x00000001U)

/* USER_PHY_SEL_REG */

#define MDIO_USER_GROUP_USER_PHY_SEL_REG_PHYADR_MON_MASK           (0x0000001FU)
#define MDIO_USER_GROUP_USER_PHY_SEL_REG_PHYADR_MON_SHIFT          (0x00000000U)
#define MDIO_USER_GROUP_USER_PHY_SEL_REG_PHYADR_MON_MAX            (0x0000001FU)

#define MDIO_USER_GROUP_USER_PHY_SEL_REG_LINKINT_ENABLE_MASK       (0x00000040U)
#define MDIO_USER_GROUP_USER_PHY_SEL_REG_LINKINT_ENABLE_SHIFT      (0x00000006U)
#define MDIO_USER_GROUP_USER_PHY_SEL_REG_LINKINT_ENABLE_MAX        (0x00000001U)

#define MDIO_USER_GROUP_USER_PHY_SEL_REG_LINKSEL_MASK              (0x00000080U)
#define MDIO_USER_GROUP_USER_PHY_SEL_REG_LINKSEL_SHIFT             (0x00000007U)
#define MDIO_USER_GROUP_USER_PHY_SEL_REG_LINKSEL_MAX               (0x00000001U)

/* MDIO_VERSION_REG */

#define MDIO_MDIO_VERSION_REG_SCHEME_MASK                          (0xC0000000U)
#define MDIO_MDIO_VERSION_REG_SCHEME_SHIFT                         (0x0000001EU)
#define MDIO_MDIO_VERSION_REG_SCHEME_MAX                           (0x00000003U)

#define MDIO_MDIO_VERSION_REG_BU_MASK                              (0x30000000U)
#define MDIO_MDIO_VERSION_REG_BU_SHIFT                             (0x0000001CU)
#define MDIO_MDIO_VERSION_REG_BU_MAX                               (0x00000003U)

#define MDIO_MDIO_VERSION_REG_MODULE_ID_MASK                       (0x0FFF0000U)
#define MDIO_MDIO_VERSION_REG_MODULE_ID_SHIFT                      (0x00000010U)
#define MDIO_MDIO_VERSION_REG_MODULE_ID_MAX                        (0x00000FFFU)

#define MDIO_MDIO_VERSION_REG_REVRTL_MASK                          (0x0000F800U)
#define MDIO_MDIO_VERSION_REG_REVRTL_SHIFT                         (0x0000000BU)
#define MDIO_MDIO_VERSION_REG_REVRTL_MAX                           (0x0000001FU)

#define MDIO_MDIO_VERSION_REG_REVMAJ_MASK                          (0x00000700U)
#define MDIO_MDIO_VERSION_REG_REVMAJ_SHIFT                         (0x00000008U)
#define MDIO_MDIO_VERSION_REG_REVMAJ_MAX                           (0x00000007U)

#define MDIO_MDIO_VERSION_REG_CUSTOM_MASK                          (0x000000C0U)
#define MDIO_MDIO_VERSION_REG_CUSTOM_SHIFT                         (0x00000006U)
#define MDIO_MDIO_VERSION_REG_CUSTOM_MAX                           (0x00000003U)

#define MDIO_MDIO_VERSION_REG_REVMIN_MASK                          (0x0000003FU)
#define MDIO_MDIO_VERSION_REG_REVMIN_SHIFT                         (0x00000000U)
#define MDIO_MDIO_VERSION_REG_REVMIN_MAX                           (0x0000003FU)

/* CONTROL_REG */

#define MDIO_CONTROL_REG_CLKDIV_MASK                               (0x0000FFFFU)
#define MDIO_CONTROL_REG_CLKDIV_SHIFT                              (0x00000000U)
#define MDIO_CONTROL_REG_CLKDIV_MAX                                (0x0000FFFFU)

#define MDIO_CONTROL_REG_INT_TEST_ENABLE_MASK                      (0x00020000U)
#define MDIO_CONTROL_REG_INT_TEST_ENABLE_SHIFT                     (0x00000011U)
#define MDIO_CONTROL_REG_INT_TEST_ENABLE_MAX                       (0x00000001U)

#define MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_MASK                  (0x00040000U)
#define MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_SHIFT                 (0x00000012U)
#define MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_MAX                   (0x00000001U)

#define MDIO_CONTROL_REG_FAULT_MASK                                (0x00080000U)
#define MDIO_CONTROL_REG_FAULT_SHIFT                               (0x00000013U)
#define MDIO_CONTROL_REG_FAULT_MAX                                 (0x00000001U)

#define MDIO_CONTROL_REG_PREAMBLE_MASK                             (0x00100000U)
#define MDIO_CONTROL_REG_PREAMBLE_SHIFT                            (0x00000014U)
#define MDIO_CONTROL_REG_PREAMBLE_MAX                              (0x00000001U)

#define MDIO_CONTROL_REG_HIGHEST_USER_CHANNEL_MASK                 (0x1F000000U)
#define MDIO_CONTROL_REG_HIGHEST_USER_CHANNEL_SHIFT                (0x00000018U)
#define MDIO_CONTROL_REG_HIGHEST_USER_CHANNEL_MAX                  (0x0000001FU)

#define MDIO_CONTROL_REG_ENABLE_MASK                               (0x40000000U)
#define MDIO_CONTROL_REG_ENABLE_SHIFT                              (0x0000001EU)
#define MDIO_CONTROL_REG_ENABLE_MAX                                (0x00000001U)

#define MDIO_CONTROL_REG_IDLE_MASK                                 (0x80000000U)
#define MDIO_CONTROL_REG_IDLE_SHIFT                                (0x0000001FU)
#define MDIO_CONTROL_REG_IDLE_MAX                                  (0x00000001U)

/* ALIVE_REG */

#define MDIO_ALIVE_REG_ALIVE_MASK                                  (0xFFFFFFFFU)
#define MDIO_ALIVE_REG_ALIVE_SHIFT                                 (0x00000000U)
#define MDIO_ALIVE_REG_ALIVE_MAX                                   (0xFFFFFFFFU)

/* LINK_REG */

#define MDIO_LINK_REG_LINK_MASK                                    (0xFFFFFFFFU)
#define MDIO_LINK_REG_LINK_SHIFT                                   (0x00000000U)
#define MDIO_LINK_REG_LINK_MAX                                     (0xFFFFFFFFU)

/* LINK_INT_RAW_REG */

#define MDIO_LINK_INT_RAW_REG_LINKINTRAW_MASK                      (0x00000003U)
#define MDIO_LINK_INT_RAW_REG_LINKINTRAW_SHIFT                     (0x00000000U)
#define MDIO_LINK_INT_RAW_REG_LINKINTRAW_MAX                       (0x00000003U)

/* LINK_INT_MASKED_REG */

#define MDIO_LINK_INT_MASKED_REG_LINKINTMASKED_MASK                (0x00000003U)
#define MDIO_LINK_INT_MASKED_REG_LINKINTMASKED_SHIFT               (0x00000000U)
#define MDIO_LINK_INT_MASKED_REG_LINKINTMASKED_MAX                 (0x00000003U)

/* LINK_INT_MASK_SET_REG */

#define MDIO_LINK_INT_MASK_SET_REG_LINKINTMASKSET_MASK             (0x00000001U)
#define MDIO_LINK_INT_MASK_SET_REG_LINKINTMASKSET_SHIFT            (0x00000000U)
#define MDIO_LINK_INT_MASK_SET_REG_LINKINTMASKSET_MAX              (0x00000001U)

/* LINK_INT_MASK_CLEAR_REG */

#define MDIO_LINK_INT_MASK_CLEAR_REG_LINKINTMASKCLR_MASK           (0x00000001U)
#define MDIO_LINK_INT_MASK_CLEAR_REG_LINKINTMASKCLR_SHIFT          (0x00000000U)
#define MDIO_LINK_INT_MASK_CLEAR_REG_LINKINTMASKCLR_MAX            (0x00000001U)

/* USER_INT_RAW_REG */

#define MDIO_USER_INT_RAW_REG_USERINTRAW_MASK                      (0x00000003U)
#define MDIO_USER_INT_RAW_REG_USERINTRAW_SHIFT                     (0x00000000U)
#define MDIO_USER_INT_RAW_REG_USERINTRAW_MAX                       (0x00000003U)

/* USER_INT_MASKED_REG */

#define MDIO_USER_INT_MASKED_REG_USERINTMASKED_MASK                (0x00000003U)
#define MDIO_USER_INT_MASKED_REG_USERINTMASKED_SHIFT               (0x00000000U)
#define MDIO_USER_INT_MASKED_REG_USERINTMASKED_MAX                 (0x00000003U)
#define MDIO_USER_INT_MASKED_REG_MAX                               (0x00000002U)

/* USER_INT_MASK_SET_REG */

#define MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET_MASK             (0x00000003U)
#define MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET_SHIFT            (0x00000000U)
#define MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET_MAX              (0x00000003U)

/* USER_INT_MASK_CLEAR_REG */

#define MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR_MASK           (0x00000003U)
#define MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR_SHIFT          (0x00000000U)
#define MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR_MAX            (0x00000003U)

/* MANUAL_IF_REG */

#define MDIO_MANUAL_IF_REG_MDIO_PIN_MASK                           (0x00000001U)
#define MDIO_MANUAL_IF_REG_MDIO_PIN_SHIFT                          (0x00000000U)
#define MDIO_MANUAL_IF_REG_MDIO_PIN_MAX                            (0x00000001U)

#define MDIO_MANUAL_IF_REG_MDIO_OE_MASK                            (0x00000002U)
#define MDIO_MANUAL_IF_REG_MDIO_OE_SHIFT                           (0x00000001U)
#define MDIO_MANUAL_IF_REG_MDIO_OE_MAX                             (0x00000001U)

#define MDIO_MANUAL_IF_REG_MDIO_MDCLK_O_MASK                       (0x00000004U)
#define MDIO_MANUAL_IF_REG_MDIO_MDCLK_O_SHIFT                      (0x00000002U)
#define MDIO_MANUAL_IF_REG_MDIO_MDCLK_O_MAX                        (0x00000001U)

/* POLL_REG */

#define MDIO_POLL_REG_IPG_MASK                                     (0x000000FFU)
#define MDIO_POLL_REG_IPG_SHIFT                                    (0x00000000U)
#define MDIO_POLL_REG_IPG_MAX                                      (0x000000FFU)

#define MDIO_POLL_REG_STATECHANGEMODE_MASK                         (0x40000000U)
#define MDIO_POLL_REG_STATECHANGEMODE_SHIFT                        (0x0000001EU)
#define MDIO_POLL_REG_STATECHANGEMODE_MAX                          (0x00000001U)

#define MDIO_POLL_REG_MANUALMODE_MASK                              (0x80000000U)
#define MDIO_POLL_REG_MANUALMODE_SHIFT                             (0x0000001FU)
#define MDIO_POLL_REG_MANUALMODE_MAX                               (0x00000001U)

/* POLL_EN_REG */

#define MDIO_POLL_EN_REG_POLL_EN_MASK                              (0xFFFFFFFFU)
#define MDIO_POLL_EN_REG_POLL_EN_SHIFT                             (0x00000000U)
#define MDIO_POLL_EN_REG_POLL_EN_MAX                               (0xFFFFFFFFU)

/* CLAUS45_REG */

#define MDIO_CLAUS45_REG_CLAUSE45_MASK                             (0xFFFFFFFFU)
#define MDIO_CLAUS45_REG_CLAUSE45_SHIFT                            (0x00000000U)
#define MDIO_CLAUS45_REG_CLAUSE45_MAX                              (0xFFFFFFFFU)

/* USER_ADDR0_REG */

#define MDIO_USER_ADDR0_REG_USER_ADDR0_MASK                        (0x0000FFFFU)
#define MDIO_USER_ADDR0_REG_USER_ADDR0_SHIFT                       (0x00000000U)
#define MDIO_USER_ADDR0_REG_USER_ADDR0_MAX                         (0x0000FFFFU)

/* USER_ADDR1_REG */

#define MDIO_USER_ADDR1_REG_USER_ADDR1_MASK                        (0x0000FFFFU)
#define MDIO_USER_ADDR1_REG_USER_ADDR1_SHIFT                       (0x00000000U)
#define MDIO_USER_ADDR1_REG_USER_ADDR1_MAX                         (0x0000FFFFU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CPSW_MDIO_H_ */
