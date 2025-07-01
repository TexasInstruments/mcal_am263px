/* ======================================================================
 *   Copyright (c) 2022-2025 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

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

