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
 * Hw_Cpsw_Ss.h
 *
 * Register-level header file for CPSW_SS
 *
 */

#ifndef HW_CPSW_SS_H_
#define HW_CPSW_SS_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*******************************************************************************
* Register Definitions
*******************************************************************************/

#define CPSW_SS_IDVER_REG                                          (0x00000000U)
#define CPSW_SS_SYNCE_COUNT_REG                                    (0x00000004U)
#define CPSW_SS_SYNCE_MUX_REG                                      (0x00000008U)
#define CPSW_SS_CONTROL_REG                                        (0x0000000CU)
#define CPSW_SS_INT_CONTROL_REG                                    (0x00000018U)
#define CPSW_SS_STATUS_REG                                         (0x0000001CU)
#define CPSW_SS_RGMII1_STATUS_REG                                  (0x00000030U)

/* offset from CPSW_SS_INT_EN_OFFSET - Eth_Cfg.h */
#define CPSW_SS_TH_THRESH_PULSE_EN_REG      (CPSW_SS_INT_EN_OFFSET + 0x0U)
#define CPSW_SS_TH_PULSE_EN_REG             (CPSW_SS_INT_EN_OFFSET + 0x4U)
#define CPSW_SS_FH_PULSE_EN_REG             (CPSW_SS_INT_EN_OFFSET + 0x8U)
#define CPSW_SS_MISC_EN_REG                 (CPSW_SS_INT_EN_OFFSET + 0xCU)

/* offset from CPSW_SS_INT_STATUS_OFFSET */
#define CPSW_SS_TH_THRESH_PULSE_STATUS_REG  (CPSW_SS_INT_STATUS_OFFSET + 0x0U)
#define CPSW_SS_TH_PULSE_STATUS_REG         (CPSW_SS_INT_STATUS_OFFSET + 0x4U)
#define CPSW_SS_FH_PULSE_STATUS_REG         (CPSW_SS_INT_STATUS_OFFSET + 0x8U)
#define CPSW_SS_MISC_STATUS_REG             (CPSW_SS_INT_STATUS_OFFSET + 0xCU)

/* offset from CPSW_SS_IMAX_OFFSET */
#define CPSW_SS_TH_IMAX_REG                 (CPSW_SS_IMAX_OFFSET + 0x0U)
#define CPSW_SS_FH_IMAX_REG                 (CPSW_SS_IMAX_OFFSET + 0x4U)

/*******************************************************************************
* Field Definition Macros
*******************************************************************************/

#define CPSW_SS_INT_CONTROL_REG_PRESCALE_SHIFT              (0U)
#define CPSW_SS_INT_CONTROL_REG_PRESCALE_MASK               (0x00000FFFU)

#define CPSW_SS_MISC_EN_REG_MISC_EN_SHIFT                   (0U)
#define CPSW_SS_MISC_EN_REG_MISC_EN_MASK                    (0x0000001fU)
#define CPSW_SS_MISC_EN_DED_PEND                            (0x40)
#define CPSW_SS_MISC_EN_SEC_PEND                            (0x20)
#define CPSW_SS_MISC_EN_EVT_PEND                            (0x10)
#define CPSW_SS_MISC_EN_STS_PEND                            (0x08)
#define CPSW_SS_MISC_EN_HOST_PEND                           (0x04)
#define CPSW_SS_MISC_EN_MDIO_LINK                           (0x02)
#define CPSW_SS_MISC_EN_MDIO_USER                           (0x01)

#define CPSW_SS_MISC_STATUS_REG_DED_PEND_MASK               (0x00000040U)
#define CPSW_SS_MISC_STATUS_REG_DED_PEND_SHIFT              (0x00000006U)
#define CPSW_SS_MISC_STATUS_REG_DED_PEND_RESETVAL           (0x00000000U)

#define CPSW_SS_MISC_STATUS_REG_SEC_PEND_MASK               (0x00000020U)
#define CPSW_SS_MISC_STATUS_REG_SEC_PEND_SHIFT              (0x00000005U)
#define CPSW_SS_MISC_STATUS_REG_SEC_PEND_RESETVAL           (0x00000000U)

#define CPSW_SS_MISC_STATUS_REG_EVNT_PEND_MASK              (0x00000010U)
#define CPSW_SS_MISC_STATUS_REG_EVNT_PEND_SHIFT             (0x00000004U)
#define CPSW_SS_MISC_STATUS_REG_EVNT_PEND_RESETVAL          (0x00000000U)

#define CPSW_SS_MISC_STATUS_REG_STAT_PEND_MASK              (0x00000008U)
#define CPSW_SS_MISC_STATUS_REG_STAT_PEND_SHIFT             (0x00000003U)
#define CPSW_SS_MISC_STATUS_REG_STAT_PEND_RESETVAL          (0x00000000U)

#define CPSW_SS_MISC_STATUS_REG_HOST_PEND_MASK              (0x00000004U)
#define CPSW_SS_MISC_STATUS_REG_HOST_PEND_SHIFT             (0x00000002U)
#define CPSW_SS_MISC_STATUS_REG_HOST_PEND_RESETVAL          (0x00000000U)

#define CPSW_SS_MISC_STATUS_REG_MDIO_LINKINT_MASK           (0x00000002U)
#define CPSW_SS_MISC_STATUS_REG_MDIO_LINKINT_SHIFT          (0x00000001U)
#define CPSW_SS_MISC_STATUS_REG_MDIO_LINKINT_RESETVAL       (0x00000000U)

#define CPSW_SS_MISC_STATUS_REG_MDIO_USERINT_MASK           (0x00000001U)
#define CPSW_SS_MISC_STATUS_REG_MDIO_USERINT_SHIFT          (0x00000000U)
#define CPSW_SS_MISC_STATUS_REG_MDIO_USERINT_RESETVAL       (0x00000000U)

#define CPSW_SS_TH_IMAX_REG_TH_IMAX_SHIFT                   (0U)
#define CPSW_SS_TH_IMAX_REG_TH_IMAX_MASK                    (0x0000003FU)

#define CPSW_SS_FH_IMAX_REG_FH_IMAX_SHIFT                   (0U)
#define CPSW_SS_FH_IMAX_REG_FH_IMAX_MASK                    (0x0000003FU)

#define CPSW_SS_INT_CONTROL_REG_INT_BYPASS_RX_SHIFT         (16U)
#define CPSW_SS_INT_CONTROL_REG_INT_BYPASS_RX_MASK          (0x00010000U)

#define CPSW_SS_INT_CONTROL_REG_INT_BYPASS_TX_SHIFT         (17U)
#define CPSW_SS_INT_CONTROL_REG_INT_BYPASS_TX_MASK          (0x00020000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CPSW_SS_H_ */

