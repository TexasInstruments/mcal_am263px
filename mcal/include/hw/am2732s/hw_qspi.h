/* ======================================================================
 *   Copyright (c) 2022 Texas Instruments Incorporated
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

#ifndef HW_QSPI_H_
#define HW_QSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*This is a false error report in LDRA for 61 X "Identifier match in
  * 31 characters ". Adding LDRA no analysis for this part of the
  * code to improve the readability  */
  /*LDRA_NOANALYSIS*/
/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define QSPI_PID                        (0x0U)
#define QSPI_SYSCONFIG                  (0x10U)
#define QSPI_INTR_STATUS_RAW_SET        (0x20U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR  (0x24U)
#define QSPI_INTR_ENABLE_SET_REG        (0x28U)
#define QSPI_INTR_ENABLE_CLEAR_REG      (0x2cU)
#define QSPI_INTC_EOI_REG               (0x30U)
#define QSPI_SPI_CLOCK_CNTRL_REG        (0x40U)
#define QSPI_SPI_DC_REG                 (0x44U)
#define QSPI_SPI_CMD_REG                (0x48U)
#define QSPI_SPI_STATUS_REG             (0x4cU)
#define QSPI_SPI_DATA_REG               (0x50U)
#define QSPI_SPI_SETUP0_REG             (0x54U)
#define QSPI_SPI_SETUP1_REG             (0x58U)
#define QSPI_SPI_SETUP2_REG             (0x5cU)
#define QSPI_SPI_SETUP3_REG             (0x60U)
#define QSPI_SPI_SWITCH_REG             (0x64U)
#define QSPI_SPI_DATA_REG_1             (0x68U)
#define QSPI_SPI_DATA_REG_2             (0x6cU)
#define QSPI_SPI_DATA_REG_3             (0x70U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define QSPI_PID_REVISION_SHIFT                             (0U)
#define QSPI_PID_REVISION_MASK                              (0xffffffffU)

#define QSPI_SYSCONFIG_RSVD_1_SHIFT                         (0U)
#define QSPI_SYSCONFIG_RSVD_1_MASK                          (0x00000003U)

#define QSPI_SYSCONFIG_IDLE_MODE_SHIFT                      (2U)
#define QSPI_SYSCONFIG_IDLE_MODE_MASK                       (0x0000000cU)
#define QSPI_SYSCONFIG_IDLE_MODE_FORCE_IDLE                  (0U)
#define QSPI_SYSCONFIG_IDLE_MODE_NO_IDLE                     (1U)
#define QSPI_SYSCONFIG_IDLE_MODE_SMART_IDLE                  (2U)
#define QSPI_SYSCONFIG_IDLE_MODE_SMART_IDLE_WAKEUP_CAPABLE   (3U)

#define QSPI_SYSCONFIG_RSVD_3_SHIFT                         (4U)
#define QSPI_SYSCONFIG_RSVD_3_MASK                          (0x00000030U)

#define QSPI_SYSCONFIG_RSVD_2_SHIFT                         (6U)
#define QSPI_SYSCONFIG_RSVD_2_MASK                          (0xffffffc0U)

#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_SHIFT             (0U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_MASK              (0x00000001U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_READ_INACTIVE      (0U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_READ_ACTIVE        (1U)

#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_SHIFT             (1U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_MASK              (0x00000002U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_READ_INACTIVE      (0U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_READ_ACTIVE        (1U)

#define QSPI_INTR_STATUS_RAW_SET_RSVD_SHIFT                 (2U)
#define QSPI_INTR_STATUS_RAW_SET_RSVD_MASK                  (0xfffffffcU)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_SHIFT       (0U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_MASK        (0x00000001U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_INACTIVE     (0U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_ACTIVE       (1U)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_SHIFT       (1U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_MASK        (0x00000002U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_INACTIVE     (0U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_ACTIVE       (1U)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_SHIFT           (2U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_MASK            (0xfffffffcU)

#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_SHIFT         (0U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK          (0x00000001U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_INACTIVE       (0U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_ACTIVE         (1U)

#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_SHIFT         (1U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK          (0x00000002U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_INACTIVE       (0U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_ACTIVE         (1U)

#define QSPI_INTR_ENABLE_SET_REG_RSVD_SHIFT                 (2U)
#define QSPI_INTR_ENABLE_SET_REG_RSVD_MASK                  (0xfffffffcU)

#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_SHIFT       (0U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_MASK        (0x00000001U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_INACTIVE     (0U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_ACTIVE       (1U)

#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_SHIFT       (1U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_MASK        (0x00000002U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_INACTIVE     (0U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_ACTIVE       (1U)

#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_SHIFT               (2U)
#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_MASK                (0xfffffffcU)

#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_SHIFT             (0U)
#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_MASK              (0x0000ffffU)

#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_SHIFT                 (16U)
#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_MASK                  (0x7fff0000U)

#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_SHIFT                (31U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_MASK                 (0x80000000U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON             (1U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF            (0U)

#define QSPI_SPI_DC_REG_CKP_DATA_ACTIVE                     (1U)
#define QSPI_SPI_DC_REG_CKP_DATA_INACTIVE                   (0U)

#define QSPI_SPI_DC_REG_CSP_ACTIVE_LOW                      (0U)
#define QSPI_SPI_DC_REG_CSP_ACTIVE_HIGH                     (1U)

#define QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_FALLING_EDGE   (0U)
#define QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_RISING_EDGE    (1U)
#define QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_FALLING_EDGE   (1U)
#define QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_RISING_EDGE    (0U)

#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_0               (0U)
#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_1               (1U)
#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_2               (2U)
#define QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_3               (3U)


#define QSPI_SPI_DC_REG_CKP0_SHIFT                          (0U)
#define QSPI_SPI_DC_REG_CKP0_MASK                           (0x00000001U)

#define QSPI_SPI_DC_REG_CSP0_SHIFT                          (1U)
#define QSPI_SPI_DC_REG_CSP0_MASK                           (0x00000002U)

#define QSPI_SPI_DC_REG_CKPH0_SHIFT                         (2U)
#define QSPI_SPI_DC_REG_CKPH0_MASK                          (0x00000004U)

#define QSPI_SPI_DC_REG_DD0_SHIFT                           (3U)
#define QSPI_SPI_DC_REG_DD0_MASK                            (0x00000018U)
#define QSPI_SPI_DC_REG_RSVD_0_SHIFT                        (5U)
#define QSPI_SPI_DC_REG_RSVD_0_MASK                         (0x000000e0U)

#define QSPI_SPI_DC_REG_CKP1_SHIFT                          (8U)
#define QSPI_SPI_DC_REG_CKP1_MASK                           (0x00000100U)

#define QSPI_SPI_DC_REG_CSP1_SHIFT                          (9U)
#define QSPI_SPI_DC_REG_CSP1_MASK                           (0x00000200U)

#define QSPI_SPI_DC_REG_CKPH1_SHIFT                         (10U)
#define QSPI_SPI_DC_REG_CKPH1_MASK                          (0x00000400U)

#define QSPI_SPI_DC_REG_DD1_SHIFT                           (11U)
#define QSPI_SPI_DC_REG_DD1_MASK                            (0x00001800U)

#define QSPI_SPI_DC_REG_RSVD_1_SHIFT                        (13U)
#define QSPI_SPI_DC_REG_RSVD_1_MASK                         (0x0000e000U)

#define QSPI_SPI_DC_REG_CKP2_SHIFT                          (16U)
#define QSPI_SPI_DC_REG_CKP2_MASK                           (0x00010000U)

#define QSPI_SPI_DC_REG_CSP2_SHIFT                          (17U)
#define QSPI_SPI_DC_REG_CSP2_MASK                           (0x00020000U)

#define QSPI_SPI_DC_REG_CKPH2_SHIFT                         (18U)
#define QSPI_SPI_DC_REG_CKPH2_MASK                          (0x00040000U)

#define QSPI_SPI_DC_REG_DD2_SHIFT                           (19U)
#define QSPI_SPI_DC_REG_DD2_MASK                            (0x00180000U)

#define QSPI_SPI_DC_REG_RSVD_2_SHIFT                        (21U)
#define QSPI_SPI_DC_REG_RSVD_2_MASK                         (0x00e00000U)

#define QSPI_SPI_DC_REG_CKP3_SHIFT                          (24U)
#define QSPI_SPI_DC_REG_CKP3_MASK                           (0x01000000U)

#define QSPI_SPI_DC_REG_CSP3_SHIFT                          (25U)
#define QSPI_SPI_DC_REG_CSP3_MASK                           (0x02000000U)

#define QSPI_SPI_DC_REG_CKPH3_SHIFT                         (26U)
#define QSPI_SPI_DC_REG_CKPH3_MASK                          (0x04000000U)

#define QSPI_SPI_DC_REG_DD3_SHIFT                           (27U)
#define QSPI_SPI_DC_REG_DD3_MASK                            (0x18000000U)

#define QSPI_SPI_DC_REG_RSVD_3_SHIFT                        (29U)
#define QSPI_SPI_DC_REG_RSVD_3_MASK                         (0xe0000000U)

#define QSPI_SPI_CMD_REG_FLEN_SHIFT                         (0U)
#define QSPI_SPI_CMD_REG_FLEN_MASK                          (0x00000fffU)

#define QSPI_SPI_CMD_REG_RSVD_SHIFT                         (12U)
#define QSPI_SPI_CMD_REG_RSVD_MASK                          (0x00003000U)

#define QSPI_SPI_CMD_REG_WIRQ_SHIFT                         (14U)
#define QSPI_SPI_CMD_REG_WIRQ_MASK                          (0x00004000U)
#define QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_ENABLE          (1U)
#define QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE         (0U)

#define QSPI_SPI_CMD_REG_FIRQ_SHIFT                         (15U)
#define QSPI_SPI_CMD_REG_FIRQ_MASK                          (0x00008000U)
#define QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_ENABLE         (1U)
#define QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE        (0U)

#define QSPI_SPI_CMD_REG_CMD_SHIFT                          (16U)
#define QSPI_SPI_CMD_REG_CMD_MASK                           (0x00070000U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE            (1U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE           (2U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL              (3U)
#define QSPI_SPI_CMD_REG_CMD_THREE_PIN_READ_SINGLE           (5U)
#define QSPI_SPI_CMD_REG_CMD_THREE_PIN_WRITE_SINGLE          (6U)
#define QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD               (7U)

#define QSPI_SPI_CMD_REG_WLEN_SHIFT                         (19U)
#define QSPI_SPI_CMD_REG_WLEN_MASK                          (0x03f80000U)

#define QSPI_SPI_CMD_REG_RSVD_2_SHIFT                       (24U)
#define QSPI_SPI_CMD_REG_RSVD_2_MASK                        (0x0f000000U)

#define QSPI_SPI_CMD_REG_CSNUM_SHIFT                        (28U)
#define QSPI_SPI_CMD_REG_CSNUM_MASK                         (0x30000000U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_0                          (0U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_1                          (1U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_2                          (2U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_3                          (3U)

#define QSPI_SPI_CMD_REG_RSVD_3_SHIFT                       (30U)
#define QSPI_SPI_CMD_REG_RSVD_3_MASK                        (0xc0000000U)

#define QSPI_SPI_STATUS_REG_BUSY_SHIFT                      (0U)
#define QSPI_SPI_STATUS_REG_BUSY_MASK                       (0x00000001U)
#define QSPI_SPI_STATUS_REG_BUSY_IDLE                        (0U)
#define QSPI_SPI_STATUS_REG_BUSY_BUSY                        (1U)

#define QSPI_SPI_STATUS_REG_WC_SHIFT                        (1U)
#define QSPI_SPI_STATUS_REG_WC_MASK                         (0x00000002U)
#define QSPI_SPI_STATUS_REG_WC_WORD_TRANSFER_NOT_COMPLETE    (0U)
#define QSPI_SPI_STATUS_REG_WC_WORD_TRANSFER_COMPLETE        (1U)

#define QSPI_SPI_STATUS_REG_FC_SHIFT                        (2U)
#define QSPI_SPI_STATUS_REG_FC_MASK                         (0x00000004U)
#define QSPI_SPI_STATUS_REG_FC_FRAME_TRANSFER_NOT_COMPLETE   (0U)
#define QSPI_SPI_STATUS_REG_FC_FRAME_TRANSFER_COMPLETE       (1U)

#define QSPI_SPI_STATUS_REG_RSVD_SHIFT                      (3U)
#define QSPI_SPI_STATUS_REG_RSVD_MASK                       (0x0000fff8U)

#define QSPI_SPI_STATUS_REG_WDCNT_SHIFT                     (16U)
#define QSPI_SPI_STATUS_REG_WDCNT_MASK                      (0x0fff0000U)

#define QSPI_SPI_STATUS_REG_RSVD_2_SHIFT                    (28U)
#define QSPI_SPI_STATUS_REG_RSVD_2_MASK                     (0xf0000000U)

#define QSPI_SPI_DATA_REG_DATA_SHIFT                        (0U)
#define QSPI_SPI_DATA_REG_DATA_MASK                         (0xffffffffU)


#define QSPI_SPI_SWITCH_REG_MMPT_S_SHIFT                    (0U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_MASK                     (0x00000001U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT              (0U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT               (1U)

#define QSPI_SPI_SWITCH_REG_MM_INT_EN_SHIFT                 (1U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MASK                  (0x00000002U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MM_MODE_INTR_DISABLED   (0U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MM_MODE_INTR_ENABLED    (1U)

#define QSPI_SPI_SWITCH_REG_RSVD_SHIFT                       (2U)
#define QSPI_SPI_SWITCH_REG_RSVD_MASK                        (0xfffffffcU)

#define QSPI_SPI_SETUP_REG_RCMD_SHIFT                       (0U)
#define QSPI_SPI_SETUP_REG_RCMD_MASK                        (0x000000ffU)

#define QSPI_SPI_SETUP_REG_NUM_A_BYTES_SHIFT                (8U)
#define QSPI_SPI_SETUP_REG_NUM_A_BYTES_MASK                 (0x00000300U)
#define QSPI_SPI_SETUP_REG_NUM_A_BYTES_ONE_BYTE              (0U)
#define QSPI_SPI_SETUP_REG_NUM_A_BYTES_TWO_BYTES             (1U)
#define QSPI_SPI_SETUP_REG_NUM_A_BYTES_THREE_BYTES           (2U)
#define QSPI_SPI_SETUP_REG_NUM_A_BYTES_FOUR_BYTES            (3U)

#define QSPI_SPI_SETUP_REG_NUM_D_BYTES_SHIFT                (10U)
#define QSPI_SPI_SETUP_REG_NUM_D_BYTES_MASK                 (0x00000c00U)
#define QSPI_SPI_SETUP_REG_NUM_D_BYTES_USE_NUM_D_BITS        (0U)
#define QSPI_SPI_SETUP_REG_NUM_D_BYTES_USE_8_BITS            (1U)
#define QSPI_SPI_SETUP_REG_NUM_D_BYTES_USE_16_BITS           (2U)
#define QSPI_SPI_SETUP_REG_NUM_D_BYTES_USE_24_BITS           (3U)

#define QSPI_SPI_SETUP_REG_READ_TYPE_SHIFT                  (12U)
#define QSPI_SPI_SETUP_REG_READ_TYPE_MASK                   (0x00003000U)
#define QSPI_SPI_SETUP_REG_READ_TYPE_NORMAL_READ             (0U)
#define QSPI_SPI_SETUP_REG_READ_TYPE_DUAL_READ               (1U)
#define QSPI_SPI_SETUP_REG_READ_TYPE_NORMAL_READ_TYPE        (2U)
#define QSPI_SPI_SETUP_REG_READ_TYPE_QUAD_READ               (3U)

#define QSPI_SPI_SETUP_REG_RSVD_1_SHIFT                     (14U)
#define QSPI_SPI_SETUP_REG_RSVD_1_MASK                      (0x0000c000U)

#define QSPI_SPI_SETUP_REG_WCMD_SHIFT                       (16U)
#define QSPI_SPI_SETUP_REG_WCMD_MASK                        (0x00ff0000U)

#define QSPI_SPI_SETUP_REG_RSVD_2_SHIFT                     (29U)
#define QSPI_SPI_SETUP_REG_RSVD_2_MASK                      (0xe0000000U)

#define QSPI_SPI_SETUP_REG_NUM_D_BITS_SHIFT                 (24U)
#define QSPI_SPI_SETUP_REG_NUM_D_BITS_MASK                  (0x1f000000U)

#define QSPI_SPI_DATA_REG_1_DATA_SHIFT                       (0U)
#define QSPI_SPI_DATA_REG_1_DATA_MASK                        (0xffffffffU)

#define QSPI_SPI_DATA_REG_2_DATA_SHIFT                       (0U)
#define QSPI_SPI_DATA_REG_2_DATA_MASK                        (0xffffffffU)

#define QSPI_SPI_DATA_REG_3_DATA_SHIFT                       (0U)
#define QSPI_SPI_DATA_REG_3_DATA_MASK                        (0xffffffffU)

#define QSPI_INTR_STATUS_MASK              					(0x00000003U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_FALLING_EDGE  (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_FALLING_EDGE  (0x00000001U)

#define QSPI_SPI_DC_REG_CKP0_DATA_ACTIVE                    (0x00000001U)
#define QSPI_SPI_DC_REG_CKP0_DATA_INACTIVE                  (0x00000000U)

#define QSPI_SPI_DC_REG_CSP0_ACTIVE_LOW                     (0x00000000U)
#define QSPI_SPI_DC_REG_CSP0_ACTIVE_HIGH                    (0x00000001U)

#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_0              (0x00000000U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_1              (0x00000001U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_2              (0x00000002U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_3              (0x00000003U)

#define QSPI_INTC_EOI_REG_EOI_VECTOR_MASK                   (0xFFFFFFFFU)
#define QSPI_INTC_EOI_REG_EOI_VECTOR_SHIFT                  (0U)
#define QSPI_INTC_EOI_REG_EOI_VECTOR_RESETVAL               (0x00000000U)
#define QSPI_INTC_EOI_REG_EOI_VECTOR_MAX                    (0xffffffffU)

#define QSPI_INTC_EOI_REG                                   (0x30U)

#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_MASK                (0x00000300U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_SHIFT               (8U)

#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_MASK                 (0x1F000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_SHIFT                (24U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_RESETVAL             (0x00000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_MAX                  (0x0000001fU)


#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_MASK                (0x00000C00U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_SHIFT               (10U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_RESETVAL            (0x00000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS      (0x00000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS          (0x00000001U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_16_BITS         (0x00000002U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_24_BITS         (0x00000003U)

#define QSPI_SPI_SETUP0_REG_RCMD_MASK                       (0x000000FFU)
#define QSPI_SPI_SETUP0_REG_RCMD_SHIFT                      (0U)
#define QSPI_SPI_SETUP0_REG_RCMD_RESETVAL                   (0x00000003U)
#define QSPI_SPI_SETUP0_REG_RCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP0_REG_READ_TYPE_MASK                  (0x00003000U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_SHIFT                 (12U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_RESETVAL              (0x00000000U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ           (0x00000000U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ             (0x00000001U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ_TYPE      (0x00000002U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ             (0x00000003U)

#define QSPI_QSPISYSCONFIG                                  (0x10U)
#define QSPISYSCONFIG 										(0x10U)
#define SPI_SWITCH_REG										(0x64U)
#define SPI_SETUP0_REG										(0x54U)

/*LDRA_ANALYSIS*/
#ifdef __cplusplus
}
#endif

#endif  /* _HW_QSPI_H_ */
