/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2024-2025 Texas Instruments Incorporated
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
 *  \file     Hw_Cpsw.h
 *
 *  \brief    This file contains the function prototypes for the device
 *            abstraction layer for CPSW subsystem. It also contains some
 *            related macro definitions and some files to be included.
 *
 *  \details  Please find the below detailed description of cpsw dal.
 */

#ifndef HW_CPSW_H_
#define HW_CPSW_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Register Definitions
 ******************************************************************************/
#define CPSW_CPSW_ID_VER_REG                                     (0x00020000U)
#define CPSW_CONTROL_REG                                         (0x00020004U)
#define CPSW_EM_CONTROL_REG                                      (0x00020010U)
#define CPSW_STAT_PORT_EN_REG                                    (0x00020014U)
#define CPSW_PTYPE_REG                                           (0x00020018U)
#define CPSW_SOFT_IDLE_REG                                       (0x0002001CU)
#define CPSW_THRU_RATE_REG                                       (0x00020020U)
#define CPSW_GAP_THRESH_REG                                      (0x00020024U)
#define CPSW_TX_START_WDS_REG                                    (0x00020028U)
#define CPSW_EEE_PRESCALE_REG                                    (0x0002002CU)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG                           (0x00020030U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG                           (0x00020034U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG                           (0x00020038U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG                           (0x0002003CU)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG                           (0x00020040U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG                           (0x00020044U)
#define CPSW_VLAN_LTYPE_REG                                      (0x00020050U)
#define CPSW_EST_TS_DOMAIN_REG                                   (0x00020054U)
#define CPSW_TX_PRI0_MAXLEN_REG                                  (0x00020100U)
#define CPSW_TX_PRI1_MAXLEN_REG                                  (0x00020104U)
#define CPSW_TX_PRI2_MAXLEN_REG                                  (0x00020108U)
#define CPSW_TX_PRI3_MAXLEN_REG                                  (0x0002010CU)
#define CPSW_TX_PRI4_MAXLEN_REG                                  (0x00020110U)
#define CPSW_TX_PRI5_MAXLEN_REG                                  (0x00020114U)
#define CPSW_TX_PRI6_MAXLEN_REG                                  (0x00020118U)
#define CPSW_TX_PRI7_MAXLEN_REG                                  (0x0002011CU)
#define CPSW_EST_FETCH_LOC(FETCH_LOC)                    (0x00032000U+((FETCH_LOC)*0x4U))


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* FETCH_LOC */

#define CPSW_EST_FETCH_LOC_LOC_MASK                              (0x003FFFFFU)
#define CPSW_EST_FETCH_LOC_LOC_SHIFT                             (0x00000000U)
#define CPSW_EST_FETCH_LOC_LOC_MAX                               (0x003FFFFFU)

/* CPSW_ID_VER_REG */

#define CPSW_CPSW_ID_VER_REG_MINOR_VER_MASK                      (0x0000003FU)
#define CPSW_CPSW_ID_VER_REG_MINOR_VER_SHIFT                     (0x00000000U)
#define CPSW_CPSW_ID_VER_REG_MINOR_VER_MAX                       (0x0000003FU)

#define CPSW_CPSW_ID_VER_REG_CUSTOM_VER_MASK                     (0x000000C0U)
#define CPSW_CPSW_ID_VER_REG_CUSTOM_VER_SHIFT                    (0x00000006U)
#define CPSW_CPSW_ID_VER_REG_CUSTOM_VER_MAX                      (0x00000003U)

#define CPSW_CPSW_ID_VER_REG_MAJOR_VER_MASK                      (0x00000700U)
#define CPSW_CPSW_ID_VER_REG_MAJOR_VER_SHIFT                     (0x00000008U)
#define CPSW_CPSW_ID_VER_REG_MAJOR_VER_MAX                       (0x00000007U)

#define CPSW_CPSW_ID_VER_REG_RTL_VER_MASK                        (0x0000F800U)
#define CPSW_CPSW_ID_VER_REG_RTL_VER_SHIFT                       (0x0000000BU)
#define CPSW_CPSW_ID_VER_REG_RTL_VER_MAX                         (0x0000001FU)

#define CPSW_CPSW_ID_VER_REG_IDENT_MASK                          (0xFFFF0000U)
#define CPSW_CPSW_ID_VER_REG_IDENT_SHIFT                         (0x00000010U)
#define CPSW_CPSW_ID_VER_REG_IDENT_MAX                           (0x0000FFFFU)

/* CONTROL_REG */

#define CPSW_CONTROL_REG_S_CN_SWITCH_MASK                        (0x00000001U)
#define CPSW_CONTROL_REG_S_CN_SWITCH_SHIFT                       (0x00000000U)
#define CPSW_CONTROL_REG_S_CN_SWITCH_MAX                         (0x00000001U)

#define CPSW_CONTROL_REG_VLAN_AWARE_MASK                         (0x00000002U)
#define CPSW_CONTROL_REG_VLAN_AWARE_SHIFT                        (0x00000001U)
#define CPSW_CONTROL_REG_VLAN_AWARE_MAX                          (0x00000001U)

#define CPSW_CONTROL_REG_P0_ENABLE_MASK                          (0x00000004U)
#define CPSW_CONTROL_REG_P0_ENABLE_SHIFT                         (0x00000002U)
#define CPSW_CONTROL_REG_P0_ENABLE_MAX                           (0x00000001U)

#define CPSW_CONTROL_REG_P0_PASS_PRI_TAGGED_MASK                 (0x00000008U)
#define CPSW_CONTROL_REG_P0_PASS_PRI_TAGGED_SHIFT                (0x00000003U)
#define CPSW_CONTROL_REG_P0_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P1_PASS_PRI_TAGGED_MASK                 (0x00000010U)
#define CPSW_CONTROL_REG_P1_PASS_PRI_TAGGED_SHIFT                (0x00000004U)
#define CPSW_CONTROL_REG_P1_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P2_PASS_PRI_TAGGED_MASK                 (0x00000020U)
#define CPSW_CONTROL_REG_P2_PASS_PRI_TAGGED_SHIFT                (0x00000005U)
#define CPSW_CONTROL_REG_P2_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P3_PASS_PRI_TAGGED_MASK                 (0x00000040U)
#define CPSW_CONTROL_REG_P3_PASS_PRI_TAGGED_SHIFT                (0x00000006U)
#define CPSW_CONTROL_REG_P3_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P4_PASS_PRI_TAGGED_MASK                 (0x00000080U)
#define CPSW_CONTROL_REG_P4_PASS_PRI_TAGGED_SHIFT                (0x00000007U)
#define CPSW_CONTROL_REG_P4_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P5_PASS_PRI_TAGGED_MASK                 (0x00000100U)
#define CPSW_CONTROL_REG_P5_PASS_PRI_TAGGED_SHIFT                (0x00000008U)
#define CPSW_CONTROL_REG_P5_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P6_PASS_PRI_TAGGED_MASK                 (0x00000200U)
#define CPSW_CONTROL_REG_P6_PASS_PRI_TAGGED_SHIFT                (0x00000009U)
#define CPSW_CONTROL_REG_P6_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P7_PASS_PRI_TAGGED_MASK                 (0x00000400U)
#define CPSW_CONTROL_REG_P7_PASS_PRI_TAGGED_SHIFT                (0x0000000AU)
#define CPSW_CONTROL_REG_P7_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P8_PASS_PRI_TAGGED_MASK                 (0x00000800U)
#define CPSW_CONTROL_REG_P8_PASS_PRI_TAGGED_SHIFT                (0x0000000BU)
#define CPSW_CONTROL_REG_P8_PASS_PRI_TAGGED_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_P0_TX_CRC_REMOVE_MASK                   (0x00002000U)
#define CPSW_CONTROL_REG_P0_TX_CRC_REMOVE_SHIFT                  (0x0000000DU)
#define CPSW_CONTROL_REG_P0_TX_CRC_REMOVE_MAX                    (0x00000001U)

#define CPSW_CONTROL_REG_P0_RX_PAD_MASK                          (0x00004000U)
#define CPSW_CONTROL_REG_P0_RX_PAD_SHIFT                         (0x0000000EU)
#define CPSW_CONTROL_REG_P0_RX_PAD_MAX                           (0x00000001U)

#define CPSW_CONTROL_REG_P0_RX_PASS_CRC_ERR_MASK                 (0x00008000U)
#define CPSW_CONTROL_REG_P0_RX_PASS_CRC_ERR_SHIFT                (0x0000000FU)
#define CPSW_CONTROL_REG_P0_RX_PASS_CRC_ERR_MAX                  (0x00000001U)

#define CPSW_CONTROL_REG_EEE_ENABLE_MASK                         (0x00010000U)
#define CPSW_CONTROL_REG_EEE_ENABLE_SHIFT                        (0x00000010U)
#define CPSW_CONTROL_REG_EEE_ENABLE_MAX                          (0x00000001U)

#define CPSW_CONTROL_REG_IET_ENABLE_MASK                         (0x00020000U)
#define CPSW_CONTROL_REG_IET_ENABLE_SHIFT                        (0x00000011U)
#define CPSW_CONTROL_REG_IET_ENABLE_MAX                          (0x00000001U)

#define CPSW_CONTROL_REG_EST_ENABLE_MASK                         (0x00040000U)
#define CPSW_CONTROL_REG_EST_ENABLE_SHIFT                        (0x00000012U)
#define CPSW_CONTROL_REG_EST_ENABLE_MAX                          (0x00000001U)

#define CPSW_CONTROL_REG_ECC_CRC_MODE_MASK                       (0x80000000U)
#define CPSW_CONTROL_REG_ECC_CRC_MODE_SHIFT                      (0x0000001FU)
#define CPSW_CONTROL_REG_ECC_CRC_MODE_MAX                        (0x00000001U)

/* EM_CONTROL_REG */

#define CPSW_EM_CONTROL_REG_FREE_MASK                            (0x00000001U)
#define CPSW_EM_CONTROL_REG_FREE_SHIFT                           (0x00000000U)
#define CPSW_EM_CONTROL_REG_FREE_MAX                             (0x00000001U)

#define CPSW_EM_CONTROL_REG_SOFT_MASK                            (0x00000002U)
#define CPSW_EM_CONTROL_REG_SOFT_SHIFT                           (0x00000001U)
#define CPSW_EM_CONTROL_REG_SOFT_MAX                             (0x00000001U)

/* STAT_PORT_EN_REG */

#define CPSW_STAT_PORT_EN_REG_P0_STAT_EN_MASK                    (0x00000001U)
#define CPSW_STAT_PORT_EN_REG_P0_STAT_EN_SHIFT                   (0x00000000U)
#define CPSW_STAT_PORT_EN_REG_P0_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P1_STAT_EN_MASK                    (0x00000002U)
#define CPSW_STAT_PORT_EN_REG_P1_STAT_EN_SHIFT                   (0x00000001U)
#define CPSW_STAT_PORT_EN_REG_P1_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P2_STAT_EN_MASK                    (0x00000004U)
#define CPSW_STAT_PORT_EN_REG_P2_STAT_EN_SHIFT                   (0x00000002U)
#define CPSW_STAT_PORT_EN_REG_P2_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P3_STAT_EN_MASK                    (0x00000008U)
#define CPSW_STAT_PORT_EN_REG_P3_STAT_EN_SHIFT                   (0x00000003U)
#define CPSW_STAT_PORT_EN_REG_P3_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P4_STAT_EN_MASK                    (0x00000010U)
#define CPSW_STAT_PORT_EN_REG_P4_STAT_EN_SHIFT                   (0x00000004U)
#define CPSW_STAT_PORT_EN_REG_P4_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P5_STAT_EN_MASK                    (0x00000020U)
#define CPSW_STAT_PORT_EN_REG_P5_STAT_EN_SHIFT                   (0x00000005U)
#define CPSW_STAT_PORT_EN_REG_P5_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P6_STAT_EN_MASK                    (0x00000040U)
#define CPSW_STAT_PORT_EN_REG_P6_STAT_EN_SHIFT                   (0x00000006U)
#define CPSW_STAT_PORT_EN_REG_P6_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P7_STAT_EN_MASK                    (0x00000080U)
#define CPSW_STAT_PORT_EN_REG_P7_STAT_EN_SHIFT                   (0x00000007U)
#define CPSW_STAT_PORT_EN_REG_P7_STAT_EN_MAX                     (0x00000001U)

#define CPSW_STAT_PORT_EN_REG_P8_STAT_EN_MASK                    (0x00000100U)
#define CPSW_STAT_PORT_EN_REG_P8_STAT_EN_SHIFT                   (0x00000008U)
#define CPSW_STAT_PORT_EN_REG_P8_STAT_EN_MAX                     (0x00000001U)

/* PTYPE_REG */

#define CPSW_PTYPE_REG_ESC_PRI_LD_VAL_MASK                       (0x0000001FU)
#define CPSW_PTYPE_REG_ESC_PRI_LD_VAL_SHIFT                      (0x00000000U)
#define CPSW_PTYPE_REG_ESC_PRI_LD_VAL_MAX                        (0x0000001FU)

#define CPSW_PTYPE_REG_P0_PTYPE_ESC_MASK                         (0x00000100U)
#define CPSW_PTYPE_REG_P0_PTYPE_ESC_SHIFT                        (0x00000008U)
#define CPSW_PTYPE_REG_P0_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P1_PTYPE_ESC_MASK                         (0x00000200U)
#define CPSW_PTYPE_REG_P1_PTYPE_ESC_SHIFT                        (0x00000009U)
#define CPSW_PTYPE_REG_P1_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P2_PTYPE_ESC_MASK                         (0x00000400U)
#define CPSW_PTYPE_REG_P2_PTYPE_ESC_SHIFT                        (0x0000000AU)
#define CPSW_PTYPE_REG_P2_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P3_PTYPE_ESC_MASK                         (0x00000800U)
#define CPSW_PTYPE_REG_P3_PTYPE_ESC_SHIFT                        (0x0000000BU)
#define CPSW_PTYPE_REG_P3_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P4_PTYPE_ESC_MASK                         (0x00001000U)
#define CPSW_PTYPE_REG_P4_PTYPE_ESC_SHIFT                        (0x0000000CU)
#define CPSW_PTYPE_REG_P4_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P5_PTYPE_ESC_MASK                         (0x00002000U)
#define CPSW_PTYPE_REG_P5_PTYPE_ESC_SHIFT                        (0x0000000DU)
#define CPSW_PTYPE_REG_P5_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P6_PTYPE_ESC_MASK                         (0x00004000U)
#define CPSW_PTYPE_REG_P6_PTYPE_ESC_SHIFT                        (0x0000000EU)
#define CPSW_PTYPE_REG_P6_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P7_PTYPE_ESC_MASK                         (0x00008000U)
#define CPSW_PTYPE_REG_P7_PTYPE_ESC_SHIFT                        (0x0000000FU)
#define CPSW_PTYPE_REG_P7_PTYPE_ESC_MAX                          (0x00000001U)

#define CPSW_PTYPE_REG_P8_PTYPE_ESC_MASK                         (0x00010000U)
#define CPSW_PTYPE_REG_P8_PTYPE_ESC_SHIFT                        (0x00000010U)
#define CPSW_PTYPE_REG_P8_PTYPE_ESC_MAX                          (0x00000001U)

/* SOFT_IDLE_REG */

#define CPSW_SOFT_IDLE_REG_SOFT_IDLE_MASK                        (0x00000001U)
#define CPSW_SOFT_IDLE_REG_SOFT_IDLE_SHIFT                       (0x00000000U)
#define CPSW_SOFT_IDLE_REG_SOFT_IDLE_MAX                         (0x00000001U)

/* THRU_RATE_REG */

#define CPSW_THRU_RATE_REG_P0_RX_THRU_RATE_MASK                  (0x0000000FU)
#define CPSW_THRU_RATE_REG_P0_RX_THRU_RATE_SHIFT                 (0x00000000U)
#define CPSW_THRU_RATE_REG_P0_RX_THRU_RATE_MAX                   (0x0000000FU)

#define CPSW_THRU_RATE_REG_SL_RX_THRU_RATE_MASK                  (0x0000F000U)
#define CPSW_THRU_RATE_REG_SL_RX_THRU_RATE_SHIFT                 (0x0000000CU)
#define CPSW_THRU_RATE_REG_SL_RX_THRU_RATE_MAX                   (0x0000000FU)

/* GAP_THRESH_REG */

#define CPSW_GAP_THRESH_REG_GAP_THRESH_MASK                      (0x0000001FU)
#define CPSW_GAP_THRESH_REG_GAP_THRESH_SHIFT                     (0x00000000U)
#define CPSW_GAP_THRESH_REG_GAP_THRESH_MAX                       (0x0000001FU)

/* TX_START_WDS_REG */

#define CPSW_TX_START_WDS_REG_TX_START_WDS_MASK                  (0x000007FFU)
#define CPSW_TX_START_WDS_REG_TX_START_WDS_SHIFT                 (0x00000000U)
#define CPSW_TX_START_WDS_REG_TX_START_WDS_MAX                   (0x000007FFU)

/* EEE_PRESCALE_REG */

#define CPSW_EEE_PRESCALE_REG_EEE_PRESCALE_MASK                  (0x00000FFFU)
#define CPSW_EEE_PRESCALE_REG_EEE_PRESCALE_SHIFT                 (0x00000000U)
#define CPSW_EEE_PRESCALE_REG_EEE_PRESCALE_MAX                   (0x00000FFFU)

/* TX_G_OFLOW_THRESH_SET_REG */

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI0_MASK                 (0x0000000FU)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI0_SHIFT                (0x00000000U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI0_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI1_MASK                 (0x000000F0U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI1_SHIFT                (0x00000004U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI1_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI2_MASK                 (0x00000F00U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI2_SHIFT                (0x00000008U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI2_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI3_MASK                 (0x0000F000U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI3_SHIFT                (0x0000000CU)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI3_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI4_MASK                 (0x000F0000U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI4_SHIFT                (0x00000010U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI4_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI5_MASK                 (0x00F00000U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI5_SHIFT                (0x00000014U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI5_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI6_MASK                 (0x0F000000U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI6_SHIFT                (0x00000018U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI6_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI7_MASK                 (0xF0000000U)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI7_SHIFT                (0x0000001CU)
#define CPSW_TX_G_OFLOW_THRESH_SET_REG_PRI7_MAX                  (0x0000000FU)

/* TX_G_OFLOW_THRESH_CLR_REG */

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI0_MASK                 (0x0000000FU)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI0_SHIFT                (0x00000000U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI0_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI1_MASK                 (0x000000F0U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI1_SHIFT                (0x00000004U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI1_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI2_MASK                 (0x00000F00U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI2_SHIFT                (0x00000008U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI2_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI3_MASK                 (0x0000F000U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI3_SHIFT                (0x0000000CU)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI3_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI4_MASK                 (0x000F0000U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI4_SHIFT                (0x00000010U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI4_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI5_MASK                 (0x00F00000U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI5_SHIFT                (0x00000014U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI5_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI6_MASK                 (0x0F000000U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI6_SHIFT                (0x00000018U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI6_MAX                  (0x0000000FU)

#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI7_MASK                 (0xF0000000U)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI7_SHIFT                (0x0000001CU)
#define CPSW_TX_G_OFLOW_THRESH_CLR_REG_PRI7_MAX                  (0x0000000FU)

/* TX_G_BUF_THRESH_SET_L_REG */

#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI0_MASK                 (0x000000FFU)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI0_SHIFT                (0x00000000U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI0_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI1_MASK                 (0x0000FF00U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI1_SHIFT                (0x00000008U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI1_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI2_MASK                 (0x00FF0000U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI2_SHIFT                (0x00000010U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI2_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI3_MASK                 (0xFF000000U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI3_SHIFT                (0x00000018U)
#define CPSW_TX_G_BUF_THRESH_SET_L_REG_PRI3_MAX                  (0x000000FFU)

/* TX_G_BUF_THRESH_SET_H_REG */

#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI4_MASK                 (0x000000FFU)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI4_SHIFT                (0x00000000U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI4_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI5_MASK                 (0x0000FF00U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI5_SHIFT                (0x00000008U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI5_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI6_MASK                 (0x00FF0000U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI6_SHIFT                (0x00000010U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI6_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI7_MASK                 (0xFF000000U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI7_SHIFT                (0x00000018U)
#define CPSW_TX_G_BUF_THRESH_SET_H_REG_PRI7_MAX                  (0x000000FFU)

/* TX_G_BUF_THRESH_CLR_L_REG */

#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI0_MASK                 (0x000000FFU)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI0_SHIFT                (0x00000000U)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI0_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI1_MASK                 (0x0000FF00U)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI1_SHIFT                (0x00000008U)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI1_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI2_MASK                 (0x00FF0000U)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI2_SHIFT                (0x00000010U)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI2_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI3_MASK                 (0xFF000000U)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI3_SHIFT                (0x00000018U)
#define CPSW_TX_G_BUF_THRESH_CLR_L_REG_PRI3_MAX                  (0x000000FFU)

/* TX_G_BUF_THRESH_CLR_H_REG */

#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI4_MASK                 (0x000000FFU)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI4_SHIFT                (0x00000000U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI4_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI5_MASK                 (0x0000FF00U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI5_SHIFT                (0x00000008U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI5_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI6_MASK                 (0x00FF0000U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI6_SHIFT                (0x00000010U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI6_MAX                  (0x000000FFU)

#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI7_MASK                 (0xFF000000U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI7_SHIFT                (0x00000018U)
#define CPSW_TX_G_BUF_THRESH_CLR_H_REG_PRI7_MAX                  (0x000000FFU)

/* VLAN_LTYPE_REG */

#define CPSW_VLAN_LTYPE_REG_VLAN_LTYPE_INNER_MASK                (0x0000FFFFU)
#define CPSW_VLAN_LTYPE_REG_VLAN_LTYPE_INNER_SHIFT               (0x00000000U)
#define CPSW_VLAN_LTYPE_REG_VLAN_LTYPE_INNER_MAX                 (0x0000FFFFU)

#define CPSW_VLAN_LTYPE_REG_VLAN_LTYPE_OUTER_MASK                (0xFFFF0000U)
#define CPSW_VLAN_LTYPE_REG_VLAN_LTYPE_OUTER_SHIFT               (0x00000010U)
#define CPSW_VLAN_LTYPE_REG_VLAN_LTYPE_OUTER_MAX                 (0x0000FFFFU)

/* EST_TS_DOMAIN_REG */

#define CPSW_EST_TS_DOMAIN_REG_EST_TS_DOMAIN_MASK                (0x000000FFU)
#define CPSW_EST_TS_DOMAIN_REG_EST_TS_DOMAIN_SHIFT               (0x00000000U)
#define CPSW_EST_TS_DOMAIN_REG_EST_TS_DOMAIN_MAX                 (0x000000FFU)

/* TX_PRI0_MAXLEN_REG */

#define CPSW_TX_PRI0_MAXLEN_REG_TX_PRI0_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI0_MAXLEN_REG_TX_PRI0_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI0_MAXLEN_REG_TX_PRI0_MAXLEN_MAX               (0x00003FFFU)

/* TX_PRI1_MAXLEN_REG */

#define CPSW_TX_PRI1_MAXLEN_REG_TX_PRI1_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI1_MAXLEN_REG_TX_PRI1_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI1_MAXLEN_REG_TX_PRI1_MAXLEN_MAX               (0x00003FFFU)

/* TX_PRI2_MAXLEN_REG */

#define CPSW_TX_PRI2_MAXLEN_REG_TX_PRI2_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI2_MAXLEN_REG_TX_PRI2_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI2_MAXLEN_REG_TX_PRI2_MAXLEN_MAX               (0x00003FFFU)

/* TX_PRI3_MAXLEN_REG */

#define CPSW_TX_PRI3_MAXLEN_REG_TX_PRI3_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI3_MAXLEN_REG_TX_PRI3_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI3_MAXLEN_REG_TX_PRI3_MAXLEN_MAX               (0x00003FFFU)

/* TX_PRI4_MAXLEN_REG */

#define CPSW_TX_PRI4_MAXLEN_REG_TX_PRI4_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI4_MAXLEN_REG_TX_PRI4_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI4_MAXLEN_REG_TX_PRI4_MAXLEN_MAX               (0x00003FFFU)

/* TX_PRI5_MAXLEN_REG */

#define CPSW_TX_PRI5_MAXLEN_REG_TX_PRI5_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI5_MAXLEN_REG_TX_PRI5_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI5_MAXLEN_REG_TX_PRI5_MAXLEN_MAX               (0x00003FFFU)

/* TX_PRI6_MAXLEN_REG */

#define CPSW_TX_PRI6_MAXLEN_REG_TX_PRI6_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI6_MAXLEN_REG_TX_PRI6_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI6_MAXLEN_REG_TX_PRI6_MAXLEN_MAX               (0x00003FFFU)

/* TX_PRI7_MAXLEN_REG */

#define CPSW_TX_PRI7_MAXLEN_REG_TX_PRI7_MAXLEN_MASK              (0x00003FFFU)
#define CPSW_TX_PRI7_MAXLEN_REG_TX_PRI7_MAXLEN_SHIFT             (0x00000000U)
#define CPSW_TX_PRI7_MAXLEN_REG_TX_PRI7_MAXLEN_MAX               (0x00003FFFU)

/* CPSW_SS_IDVER_REG */

#define CPSW_SS_IDVER_REG_MINOR_VER_MASK                          (0x000000FFU)
#define CPSW_SS_IDVER_REG_MINOR_VER_SHIFT                         (0x00000000U)
#define CPSW_SS_IDVER_REG_MINOR_VER_MAX                           (0x000000FFU)

#define CPSW_SS_IDVER_REG_MAJOR_VER_MASK                          (0x00000700U)
#define CPSW_SS_IDVER_REG_MAJOR_VER_SHIFT                         (0x00000008U)
#define CPSW_SS_IDVER_REG_MAJOR_VER_MAX                           (0x00000007U)

#define CPSW_SS_IDVER_REG_RTL_VER_MASK                            (0x0000F800U)
#define CPSW_SS_IDVER_REG_RTL_VER_SHIFT                           (0x0000000BU)
#define CPSW_SS_IDVER_REG_RTL_VER_MAX                             (0x0000001FU)

#define CPSW_SS_IDVER_REG_IDENT_MASK                              (0xFFFF0000U)
#define CPSW_SS_IDVER_REG_IDENT_SHIFT                             (0x00000010U)
#define CPSW_SS_IDVER_REG_IDENT_MAX                               (0x0000FFFFU)

/* SYNCE_COUNT_REG */

#define SYNCE_COUNT_REG_SYNCE_CNT_MASK                            (0xFFFFFFFFU)
#define SYNCE_COUNT_REG_SYNCE_CNT_SHIFT                           (0x00000000U)
#define SYNCE_COUNT_REG_SYNCE_CNT_MAX                             (0xFFFFFFFFU)

/* SYNCE_MUX_REG */

#define SYNCE_MUX_REG_SYNCE_SEL_MASK                              (0x0000003FU)
#define SYNCE_MUX_REG_SYNCE_SEL_SHIFT                             (0x00000000U)
#define SYNCE_MUX_REG_SYNCE_SEL_MAX                               (0x0000003FU)

/* CONTROL_REG */

#define CONTROL_REG_EEE_EN_MASK                                   (0x00000001U)
#define CONTROL_REG_EEE_EN_SHIFT                                  (0x00000000U)
#define CONTROL_REG_EEE_EN_MAX                                    (0x00000001U)

#define CONTROL_REG_EEE_PHY_ONLY_MASK                             (0x00000002U)
#define CONTROL_REG_EEE_PHY_ONLY_SHIFT                            (0x00000001U)
#define CONTROL_REG_EEE_PHY_ONLY_MAX                              (0x00000001U)

/* SGMII_MODE_REG */

#define SGMII_MODE_REG_SYNCE_SEL_MASK                             (0x00000001U)
#define SGMII_MODE_REG_SYNCE_SEL_SHIFT                            (0x00000000U)
#define SGMII_MODE_REG_SYNCE_SEL_MAX                              (0x00000001U)

/* RGMII_STATUS_REG */

#define RGMII_STATUS_REG_LINK_MASK                                (0x00000001U)
#define RGMII_STATUS_REG_LINK_SHIFT                               (0x00000000U)
#define RGMII_STATUS_REG_LINK_MAX                                 (0x00000001U)

#define RGMII_STATUS_REG_SPEED_MASK                               (0x00000006U)
#define RGMII_STATUS_REG_SPEED_SHIFT                              (0x00000001U)
#define RGMII_STATUS_REG_SPEED_MAX                                (0x00000003U)

#define RGMII_STATUS_REG_FULLDUPLEX_MASK                          (0x00000008U)
#define RGMII_STATUS_REG_FULLDUPLEX_SHIFT                         (0x00000003U)
#define RGMII_STATUS_REG_FULLDUPLEX_MAX                           (0x00000001U)

/* SUBSSYSTEM_STATUS_REG */

#define SUBSSYSTEM_STATUS_REG_EEE_CLKSTOP_ACK_MASK                (0x00000001U)
#define SUBSSYSTEM_STATUS_REG_EEE_CLKSTOP_ACK_SHIFT               (0x00000000U)
#define SUBSSYSTEM_STATUS_REG_EEE_CLKSTOP_ACK_MAX                 (0x00000001U)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HW_CPSW_H_ */
