/*
 *  Copyright (C) 2020 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef MCAL_HW_SOC_DEFINES_H_
#define MCAL_HW_SOC_DEFINES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>



#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \anchor CSL_CoreID
 * \name Core ID's of core or CPUs present on this SOC
 *
 * @{
 */
#define MCAL_CSL_CORE_ID_R5FSS0_0         (0U)
#define MCAL_CSL_CORE_ID_R5FSS0_1         (1U)
#define MCAL_CSL_CORE_ID_C66SS0           (2U)
#define MCAL_CSL_CORE_ID_MAX              (3U)
/** @} */


/***********************************************************************
 * MSS - CLOCK setting
 ***********************************************************************/
 /* Sys_vclk : 200MHz */
#define MCAL_MSS_SYS_VCLK                  200000000U
#define MCAL_R5F_CLOCK_MHZ                 400U

/**
 *  \anchor CSL_ArmR5ClusterGroupID
 *  \name R5 Cluster Group IDs
 *
 *  @{
 */
/** \brief R5 Cluster Group ID0 */
#define MCAL_CSL_ARM_R5_CLUSTER_GROUP_ID_0                 ((uint32) 0x00U)
/** @} */

/**
 *  \anchor CSL_ArmR5CPUID
 *  \name R5 Core IDs
 *
 *  @{
 */
/** \brief R5 Core ID0 */
#define MCAL_CSL_ARM_R5_CPU_ID_0                          ((uint32) 0x00U)
/** \brief R5 Core ID1 */
#define MCAL_CSL_ARM_R5_CPU_ID_1                          ((uint32) 0x01U)
/** @} */

/***********************************************************************
 * Cache line size definitions
 ***********************************************************************/
#if (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R') /* R5F */
#define MCAL_CSL_CACHE_L1P_LINESIZE     (32U)
#define MCAL_CSL_CACHE_L1D_LINESIZE     (32U)
#elif defined(_TMS320C6X) /* C66 */
#define MCAL_CSL_CACHE_L1P_LINESIZE     (32U)
#define MCAL_CSL_CACHE_L1D_LINESIZE     (64U)
#define MCAL_CSL_CACHE_L2_LINESIZE      (128U)
#endif

#define MCAL_CSL_SCI_SCIFLR_RXRDY_MASK                                 (0x00000200U)
#define MCAL_CSL_SCI_SCIFLR_TXRDY_MASK                                 (0x00000100U)
#define MCAL_CSL_SCI_SCIFLR_PE_MASK                                    (0x01000000U)
#define MCAL_CSL_SCI_SCIFLR_OE_MASK                                    (0x02000000U)
#define MCAL_CSL_SCI_SCIFLR_FE_MASK                                    (0x04000000U)
#define MCAL_CSL_SCI_SCIGCR0_RESET_MASK                                (0x00000001U)
#define MCAL_CSL_SCI_SCIGCR0_RESERVED_MASK                             (0xFFFFFFFEU)
#define MCAL_CSL_SCI_SCIGCR1_COMM_MODE_MASK                            (0x00000001U)
#define MCAL_CSL_SCI_SCIGCR1_TIMING_MODE_MASK                          (0x00000002U)
#define MCAL_CSL_SCI_SCIGCR1_PARITY_ENA_MASK                           (0x00000004U)
#define MCAL_CSL_SCI_SCIGCR1_PARITY_MASK                               (0x00000008U)
#define MCAL_CSL_SCI_SCIGCR1_STOP_MASK                                 (0x00000010U)
#define MCAL_CSL_SCI_SCIGCR1_CLOCK_MASK                                (0x00000020U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED1_MASK                            (0x00000040U)
#define MCAL_CSL_SCI_SCIGCR1_SW_NRESET_MASK                            (0x00000080U)
#define MCAL_CSL_SCI_SCIGCR1_SLEEP_MASK                                (0x00000100U)
#define MCAL_CSL_SCI_SCIGCR1_POWERDOWN_MASK                            (0x00000200U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED2_MASK                            (0x0000FC00U)
#define MCAL_CSL_SCI_SCIGCR1_LOOP_BACK_MASK                            (0x00010000U)
#define MCAL_CSL_SCI_SCIGCR1_CONT_MASK                                 (0x00020000U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED3_MASK                            (0x00FC0000U)
#define MCAL_CSL_SCI_SCIGCR1_RXENA_MASK                                (0x01000000U)
#define MCAL_CSL_SCI_SCIGCR1_TXENA_MASK                                (0x02000000U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED4_MASK                            (0xFC000000U)
#define MCAL_CSL_SCI_RESERVED1_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_SCISETINT_SET_BRKDT_INT_MASK                      (0x00000001U)
#define MCAL_CSL_SCI_SCISETINT_SET_WAKEUP_INT_MASK                     (0x00000002U)
#define MCAL_CSL_SCI_SCISETINT_RESERVED1_MASK                          (0x000000FCU)
#define MCAL_CSL_SCI_SCISETINT_SET_TX_INT_MASK                         (0x00000100U)
#define MCAL_CSL_SCI_SCISETINT_SET_RX_INT_MASK                         (0x00000200U)
#define MCAL_CSL_SCI_SCISETINT_RESERVED2_MASK                          (0x0000FC00U)
#define MCAL_CSL_SCI_SCISETINT_SET_TX_DMA_MASK                         (0x00010000U)
#define MCAL_CSL_SCI_SCISETINT_SET_RX_DMA_MASK                         (0x00020000U)
#define MCAL_CSL_SCI_SCISETINT_SET_RX_DMA_ALL_MASK                     (0x00040000U)
#define MCAL_CSL_SCI_SCISETINT_RESERVED3_MASK                          (0x00F80000U)
#define MCAL_CSL_SCI_SCISETINT_SET_PE_INT_MASK                         (0x01000000U)
#define MCAL_CSL_SCI_SCISETINT_SET_OE_INT_MASK                         (0x02000000U)
#define MCAL_CSL_SCI_SCISETINT_SET_FE_INT_MASK                         (0x04000000U)
#define MCAL_CSL_SCI_SCISETINT_RESERVED4_MASK                          (0xF8000000U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_BRKDT_INT_MASK                    (0x00000001U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_WAKEUP_INT_MASK                   (0x00000002U)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED1_MASK                        (0x000000FCU)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_TX_INT_MASK                       (0x00000100U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_RX_INT_MASK                       (0x00000200U)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED2_MASK                        (0x0000FC00U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_TX_DMA_MASK                       (0x00010000U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_RX_DMA_MASK                       (0x00020000U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_RX_DMA_ALL_MASK                   (0x00040000U)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED3_MASK                        (0x00F80000U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_PE_INT_MASK                       (0x01000000U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_OE_INT_MASK                       (0x02000000U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_FE_INT_MASK                       (0x04000000U)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED4_MASK                        (0xF8000000U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_BRKDT_INT_LVL_MASK               (0x00000001U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_WAKEUP_INT_LVL_MASK              (0x00000002U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED1_MASK                       (0x000000FCU)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_TX_INT_LVL_MASK                  (0x00000100U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_RX_INT_LVL_MASK                  (0x00000200U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED2_MASK                       (0x00007C00U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_INC_BR_INT_LVL_MASK              (0x00008000U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED3_MASK                       (0x00030000U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_RX_DMA_ALL_INT_LVL_MASK          (0x00040000U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED4_MASK                       (0x00F80000U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_PE_INT_LVL_MASK                  (0x01000000U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_OE_INT_LVL_MASK                  (0x02000000U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_FE_INT_LVL_MASK                  (0x04000000U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED5_MASK                       (0xF8000000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_BRKDT_INT_LVL_MASK             (0x00000001U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_WAKEUP_INT_LVL_MASK            (0x00000002U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED1_MASK                     (0x000000FCU)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_TX_INT_LVL_MASK                (0x00000100U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_RX_INT_LVL_MASK                (0x00000200U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED2_MASK                     (0x00007C00U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_INC_BR_INT_LVL_MASK            (0x00008000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED3_MASK                     (0x00030000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_RX_DMA_ALL_INT_LVL_MASK        (0x00040000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED4_MASK                     (0x00F80000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_PE_INT_LVL_MASK                (0x01000000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_OE_INT_LVL_MASK                (0x02000000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_FE_INT_LVL_MASK                (0x04000000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED5_MASK                     (0xF8000000U)
#define MCAL_CSL_SCI_SCIFLR_BRKDT_MASK                                 (0x00000001U)
#define MCAL_CSL_SCI_SCIFLR_WAKEUP_MASK                                (0x00000002U)
#define MCAL_CSL_SCI_SCIFLR_IDLE_MASK                                  (0x00000004U)
#define MCAL_CSL_SCI_SCIFLR_BUS_BUSY_FLAG_MASK                         (0x00000008U)
#define MCAL_CSL_SCI_SCIFLR_RESERVED1_MASK                             (0x000000F0U)
#define MCAL_CSL_SCI_SCIFLR_TXRDY_MASK                                 (0x00000100U)
#define MCAL_CSL_SCI_SCIFLR_RXRDY_MASK                                 (0x00000200U)
#define MCAL_CSL_SCI_SCIFLR_TXWAKE_MASK                                (0x00000400U)
#define MCAL_CSL_SCI_SCIFLR_TX_EMPTY_MASK                              (0x00000800U)
#define MCAL_CSL_SCI_SCIFLR_RXWAKE_MASK                                (0x00001000U)
#define MCAL_CSL_SCI_SCIFLR_RESERVED2_MASK                             (0x00FFE000U)
#define MCAL_CSL_SCI_SCIFLR_PE_MASK                                    (0x01000000U)
#define MCAL_CSL_SCI_SCIFLR_OE_MASK                                    (0x02000000U)
#define MCAL_CSL_SCI_SCIFLR_FE_MASK                                    (0x04000000U)
#define MCAL_CSL_SCI_SCIFLR_RESERVED3_MASK                             (0xF8000000U)
#define MCAL_CSL_SCI_SCIINTVECT0_INTVECT0_MASK                         (0x0000000FU)
#define MCAL_CSL_SCI_SCIINTVECT0_RESERVED_MASK                         (0xFFFFFFF0U)
#define MCAL_CSL_SCI_SCIINTVECT1_INTVECT1_MASK                         (0x0000000FU)
#define MCAL_CSL_SCI_SCIINTVECT1_RESERVED_MASK                         (0xFFFFFFF0U)
#define MCAL_CSL_SCI_SCICHAR_CHAR_MASK                                 (0x00000007U)
#define MCAL_CSL_SCI_SCICHAR_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIBAUD_BAUD_MASK                                 (0x00FFFFFFU)
#define MCAL_CSL_SCI_SCIBAUD_RESERVED_MASK                             (0xFF000000U)
#define MCAL_CSL_SCI_SCIED_ED_MASK                                     (0x000000FFU)
#define MCAL_CSL_SCI_SCIED_RESERVED_MASK                               (0xFFFFFF00U)
#define MCAL_CSL_SCI_SCIRD_RD_MASK                                     (0x000000FFU)
#define MCAL_CSL_SCI_SCIRD_RESERVED_MASK                               (0xFFFFFF00U)
#define MCAL_CSL_SCI_SCITD_TD_MASK                                     (0x000000FFU)
#define MCAL_CSL_SCI_SCITD_RESERVED_MASK                               (0xFFFFFF00U)
#define MCAL_CSL_SCI_SCIPIO0_CLK_FUNC_MASK                             (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO0_RX_FUNC_MASK                              (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO0_TX_FUNC_MASK                              (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO0_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO1_CLK_DIR_MASK                              (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO1_RX_DIR_MASK                               (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO1_TX_DIR_MASK                               (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO1_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO2_CLK_DATA_IN_MASK                          (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO2_RX_DATA_IN_MASK                           (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO2_TX_DATA_IN_MASK                           (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO2_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO3_CLK_DATA_OUT_MASK                         (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO3_RX_DATA_OUT_MASK                          (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO3_TX_DATA_OUT_MASK                          (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO3_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO4_CLK_DATA_SET_MASK                         (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO4_RX_DATA_SET_MASK                          (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO4_TX_DATA_SET_MASK                          (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO4_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO5_CLK_DATA_CLR_MASK                         (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO5_RX_DATA_CLR_MASK                          (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO5_TX_DATA_CLR_MASK                          (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO5_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO6_CLK_PDR_MASK                              (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO6_RX_PDR_MASK                               (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO6_TX_PDR_MASK                               (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO6_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO7_CLK_PD_MASK                               (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO7_RX_PD_MASK                                (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO7_TX_PD_MASK                                (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO7_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIPIO8_CLK_PSL_MASK                              (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO8_RX_PSL_MASK                               (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO8_TX_PSL_MASK                               (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO8_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_RESERVED2_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_RESERVED3_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_RESERVED4_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_RESERVED5_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_RESERVED6_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_RESERVED7_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_RESERVED8_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_RESERVED9_RESERVED_MASK                           (0xFFFFFFFFU)
#define MCAL_CSL_SCI_SCIPIO9_CLK_SL_MASK                               (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO9_RX_SL_MASK                                (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO9_TX_SL_MASK                                (0x00000004U)
#define MCAL_CSL_SCI_SCIPIO9_RESERVED_MASK                             (0xFFFFFFF8U)
#define MCAL_CSL_SCI_SCIIODCTRL_RXP_ENA_MASK                           (0x00000001U)
#define MCAL_CSL_SCI_SCIIODCTRL_LBP_ENA_MASK                           (0x00000002U)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED1_MASK                         (0x000000FCU)
#define MCAL_CSL_SCI_SCIIODCTRL_IODFTENA_MASK                          (0x00000F00U)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED2_MASK                         (0x0000F000U)
#define MCAL_CSL_SCI_SCIIODCTRL_TX_SHIFT_MASK                          (0x00070000U)
#define MCAL_CSL_SCI_SCIIODCTRL_PIN_SAMPLE_MASK_MASK                   (0x00180000U)
#define MCAL_CSL_SCI_SCIIODCTRL_PIN_SAMPLE_MASK_SHIFT                  (0x00000013U)
#define MCAL_CSL_SCI_SCIIODCTRL_PIN_SAMPLE_MASK_RESETVAL               (0x00000000U)
#define MCAL_CSL_SCI_SCIIODCTRL_PIN_SAMPLE_MASK_MAX                    (0x00000003U)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED3_MASK                         (0x00E00000U)
#define MCAL_CSL_SCI_SCIIODCTRL_BRKDT_ENA_MASK                         (0x01000000U)
#define MCAL_CSL_SCI_SCIIODCTRL_PEN_MASK                               (0x02000000U)
#define MCAL_CSL_SCI_SCIIODCTRL_FEN_MASK                               (0x04000000U)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED4_MASK                         (0xF8000000U)
#define MCAL_CSL_SCI_SCIGCR0_RESET_SHIFT                               (0x00000000U)
#define MCAL_CSL_SCI_SCIGCR0_RESERVED_SHIFT                            (0x00000001U)
#define MCAL_CSL_SCI_SCIGCR1_COMM_MODE_SHIFT                           (0x00000000U)
#define MCAL_CSL_SCI_SCIGCR1_TIMING_MODE_SHIFT                         (0x00000001U)
#define MCAL_CSL_SCI_SCIGCR1_PARITY_ENA_SHIFT                          (0x00000002U)
#define MCAL_CSL_SCI_SCIGCR1_PARITY_SHIFT                              (0x00000003U)
#define MCAL_CSL_SCI_SCIGCR1_STOP_SHIFT                                (0x00000004U)
#define MCAL_CSL_SCI_SCIGCR1_CLOCK_SHIFT                               (0x00000005U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED1_SHIFT                           (0x00000006U)
#define MCAL_CSL_SCI_SCIGCR1_SW_NRESET_SHIFT                           (0x00000007U)
#define MCAL_CSL_SCI_SCIGCR1_SLEEP_SHIFT                               (0x00000008U)
#define MCAL_CSL_SCI_SCIGCR1_POWERDOWN_SHIFT                           (0x00000009U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED2_SHIFT                           (0x0000000AU)
#define MCAL_CSL_SCI_SCIGCR1_LOOP_BACK_SHIFT                           (0x00000010U)
#define MCAL_CSL_SCI_SCIGCR1_CONT_SHIFT                                (0x00000011U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED3_SHIFT                           (0x00000012U)
#define MCAL_CSL_SCI_SCIGCR1_RXENA_SHIFT                               (0x00000018U)
#define MCAL_CSL_SCI_SCIGCR1_TXENA_SHIFT                               (0x00000019U)
#define MCAL_CSL_SCI_SCIGCR1_RESERVED4_SHIFT                           (0x0000001AU)
#define MCAL_CSL_SCI_RESERVED1_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_SCISETINT_SET_BRKDT_INT_SHIFT                     (0x00000000U)
#define MCAL_CSL_SCI_SCISETINT_SET_WAKEUP_INT_SHIFT                    (0x00000001U)
#define MCAL_CSL_SCI_SCISETINT_RESERVED1_SHIFT                         (0x00000002U)
#define MCAL_CSL_SCI_SCISETINT_SET_TX_INT_SHIFT                        (0x00000008U)
#define MCAL_CSL_SCI_SCISETINT_SET_RX_INT_SHIFT                        (0x00000009U)
#define MCAL_CSL_SCI_SCISETINT_RESERVED2_SHIFT                         (0x0000000AU)
#define MCAL_CSL_SCI_SCISETINT_SET_TX_DMA_SHIFT                        (0x00000010U)
#define MCAL_CSL_SCI_SCISETINT_SET_RX_DMA_SHIFT                        (0x00000011U)
#define MCAL_CSL_SCI_SCISETINT_SET_RX_DMA_ALL_SHIFT                    (0x00000012U)
#define MCAL_CSL_SCI_SCISETINT_RESERVED3_SHIFT                         (0x00000013U)
#define MCAL_CSL_SCI_SCISETINT_SET_PE_INT_SHIFT                        (0x00000018U)
#define MCAL_CSL_SCI_SCISETINT_SET_OE_INT_SHIFT                        (0x00000019U)
#define MCAL_CSL_SCI_SCISETINT_SET_FE_INT_SHIFT                        (0x0000001AU)
#define MCAL_CSL_SCI_SCISETINT_RESERVED4_SHIFT                         (0x0000001BU)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_BRKDT_INT_SHIFT                   (0x00000000U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_WAKEUP_INT_SHIFT                  (0x00000001U)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED1_SHIFT                       (0x00000002U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_TX_INT_SHIFT                      (0x00000008U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_RX_INT_SHIFT                      (0x00000009U)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED2_SHIFT                       (0x0000000AU)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_TX_DMA_SHIFT                      (0x00000010U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_RX_DMA_SHIFT                      (0x00000011U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_RX_DMA_ALL_SHIFT                  (0x00000012U)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED3_SHIFT                       (0x00000013U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_PE_INT_SHIFT                      (0x00000018U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_OE_INT_SHIFT                      (0x00000019U)
#define MCAL_CSL_SCI_SCICLEARINT_CLR_FE_INT_SHIFT                      (0x0000001AU)
#define MCAL_CSL_SCI_SCICLEARINT_RESERVED4_SHIFT                       (0x0000001BU)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_BRKDT_INT_LVL_SHIFT              (0x00000000U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_WAKEUP_INT_LVL_SHIFT             (0x00000001U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED1_SHIFT                      (0x00000002U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_TX_INT_LVL_SHIFT                 (0x00000008U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_RX_INT_LVL_SHIFT                 (0x00000009U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED2_SHIFT                      (0x0000000AU)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_INC_BR_INT_LVL_SHIFT             (0x0000000FU)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED3_SHIFT                      (0x00000010U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_RX_DMA_ALL_INT_LVL_SHIFT         (0x00000012U)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED4_SHIFT                      (0x00000013U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_PE_INT_LVL_SHIFT                 (0x00000018U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_OE_INT_LVL_SHIFT                 (0x00000019U)
#define MCAL_CSL_SCI_SCISETINTLVL_SET_FE_INT_LVL_SHIFT                 (0x0000001AU)
#define MCAL_CSL_SCI_SCISETINTLVL_RESERVED5_SHIFT                      (0x0000001BU)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_BRKDT_INT_LVL_SHIFT            (0x00000000U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_WAKEUP_INT_LVL_SHIFT           (0x00000001U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED1_SHIFT                    (0x00000002U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_TX_INT_LVL_SHIFT               (0x00000008U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_RX_INT_LVL_SHIFT               (0x00000009U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED2_SHIFT                    (0x0000000AU)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_INC_BR_INT_LVL_SHIFT           (0x0000000FU)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED3_SHIFT                    (0x00000010U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_RX_DMA_ALL_INT_LVL_SHIFT       (0x00000012U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED4_SHIFT                    (0x00000013U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_PE_INT_LVL_SHIFT               (0x00000018U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_OE_INT_LVL_SHIFT               (0x00000019U)
#define MCAL_CSL_SCI_SCICLEARINTLVL_CLR_FE_INT_LVL_SHIFT               (0x0000001AU)
#define MCAL_CSL_SCI_SCICLEARINTLVL_RESERVED5_SHIFT                    (0x0000001BU)
#define MCAL_CSL_SCI_SCIFLR_BRKDT_SHIFT                                (0x00000000U)
#define MCAL_CSL_SCI_SCIFLR_WAKEUP_SHIFT                               (0x00000001U)
#define MCAL_CSL_SCI_SCIFLR_IDLE_SHIFT                                 (0x00000002U)
#define MCAL_CSL_SCI_SCIFLR_BUS_BUSY_FLAG_SHIFT                        (0x00000003U)
#define MCAL_CSL_SCI_SCIFLR_RESERVED1_SHIFT                            (0x00000004U)
#define MCAL_CSL_SCI_SCIFLR_TXRDY_SHIFT                                (0x00000008U)
#define MCAL_CSL_SCI_SCIFLR_RXRDY_SHIFT                                (0x00000009U)
#define MCAL_CSL_SCI_SCIFLR_TXWAKE_SHIFT                               (0x0000000AU)
#define MCAL_CSL_SCI_SCIFLR_TX_EMPTY_SHIFT                             (0x0000000BU)
#define MCAL_CSL_SCI_SCIFLR_RXWAKE_SHIFT                               (0x0000000CU)
#define MCAL_CSL_SCI_SCIFLR_RESERVED2_SHIFT                            (0x0000000DU)
#define MCAL_CSL_SCI_SCIFLR_PE_SHIFT                                   (0x00000018U)
#define MCAL_CSL_SCI_SCIFLR_OE_SHIFT                                   (0x00000019U)
#define MCAL_CSL_SCI_SCIFLR_FE_SHIFT                                   (0x0000001AU)
#define MCAL_CSL_SCI_SCIFLR_RESERVED3_SHIFT                            (0x0000001BU)
#define MCAL_CSL_SCI_SCIINTVECT0_INTVECT0_SHIFT                        (0x00000000U)
#define MCAL_CSL_SCI_SCIINTVECT0_RESERVED_SHIFT                        (0x00000004U)
#define MCAL_CSL_SCI_SCIINTVECT1_INTVECT1_SHIFT                        (0x00000000U)
#define MCAL_CSL_SCI_SCIINTVECT1_RESERVED_SHIFT                        (0x00000004U)
#define MCAL_CSL_SCI_SCICHAR_CHAR_SHIFT                                (0x00000000U)
#define MCAL_CSL_SCI_SCICHAR_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIBAUD_BAUD_SHIFT                                (0x00000000U)
#define MCAL_CSL_SCI_SCIBAUD_RESERVED_SHIFT                            (0x00000018U)
#define MCAL_CSL_SCI_SCIED_ED_SHIFT                                    (0x00000000U)
#define MCAL_CSL_SCI_SCIED_RESERVED_SHIFT                              (0x00000008U)
#define MCAL_CSL_SCI_SCIRD_RD_SHIFT                                    (0x00000000U)
#define MCAL_CSL_SCI_SCIRD_RESERVED_SHIFT                              (0x00000008U)
#define MCAL_CSL_SCI_SCITD_TD_SHIFT                                    (0x00000000U)
#define MCAL_CSL_SCI_SCITD_RESERVED_SHIFT                              (0x00000008U)
#define MCAL_CSL_SCI_SCIPIO0_CLK_FUNC_SHIFT                            (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO0_RX_FUNC_SHIFT                             (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO0_TX_FUNC_SHIFT                             (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO0_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO1_CLK_DIR_SHIFT                             (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO1_RX_DIR_SHIFT                              (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO1_TX_DIR_SHIFT                              (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO1_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO2_CLK_DATA_IN_SHIFT                         (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO2_RX_DATA_IN_SHIFT                          (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO2_TX_DATA_IN_SHIFT                          (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO2_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO3_CLK_DATA_OUT_SHIFT                        (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO3_RX_DATA_OUT_SHIFT                         (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO3_TX_DATA_OUT_SHIFT                         (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO3_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO4_CLK_DATA_SET_SHIFT                        (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO4_RX_DATA_SET_SHIFT                         (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO4_TX_DATA_SET_SHIFT                         (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO4_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO5_CLK_DATA_CLR_SHIFT                        (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO5_RX_DATA_CLR_SHIFT                         (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO5_TX_DATA_CLR_SHIFT                         (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO5_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO6_CLK_PDR_SHIFT                             (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO6_RX_PDR_SHIFT                              (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO6_TX_PDR_SHIFT                              (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO6_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO7_CLK_PD_SHIFT                              (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO7_RX_PD_SHIFT                               (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO7_TX_PD_SHIFT                               (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO7_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIPIO8_CLK_PSL_SHIFT                             (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO8_RX_PSL_SHIFT                              (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO8_TX_PSL_SHIFT                              (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO8_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_RESERVED2_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_RESERVED3_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_RESERVED4_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_RESERVED5_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_RESERVED6_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_RESERVED7_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_RESERVED8_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_RESERVED9_RESERVED_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO9_CLK_SL_SHIFT                              (0x00000000U)
#define MCAL_CSL_SCI_SCIPIO9_RX_SL_SHIFT                               (0x00000001U)
#define MCAL_CSL_SCI_SCIPIO9_TX_SL_SHIFT                               (0x00000002U)
#define MCAL_CSL_SCI_SCIPIO9_RESERVED_SHIFT                            (0x00000003U)
#define MCAL_CSL_SCI_SCIIODCTRL_RXP_ENA_SHIFT                          (0x00000000U)
#define MCAL_CSL_SCI_SCIIODCTRL_LBP_ENA_SHIFT                          (0x00000001U)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED1_SHIFT                        (0x00000002U)
#define MCAL_CSL_SCI_SCIIODCTRL_IODFTENA_SHIFT                         (0x00000008U)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED2_SHIFT                        (0x0000000CU)
#define MCAL_CSL_SCI_SCIIODCTRL_TX_SHIFT_SHIFT                         (0x00000010U)
#define MCAL_CSL_SCI_SCIIODCTRL_PIN_SAMPLE_MASK_SHIFT                  (0x00000013U)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED3_SHIFT                        (0x00000015U)
#define MCAL_CSL_SCI_SCIIODCTRL_BRKDT_ENA_SHIFT                        (0x00000018U)
#define MCAL_CSL_SCI_SCIIODCTRL_PEN_SHIFT                              (0x00000019U)
#define MCAL_CSL_SCI_SCIIODCTRL_FEN_SHIFT                              (0x0000001AU)
#define MCAL_CSL_SCI_SCIIODCTRL_RESERVED4_SHIFT                        (0x0000001BU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef MCAL_HW_SOC_DEFINES_H_ */
