/* ======================================================================
 *   Copyright (c) 2021 Texas Instruments Incorporated
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
 * hw_mailbox.h
 *
 * Register-level header file for AutoRadar Mailbox
 */

#ifndef HW_MAILBOX_H_
#define HW_MAILBOX_H_

#ifdef __cplusplus
extern "C" {
#endif

/*Mailbox related address */
#define CSL_MSS_CTRL_U_BASE (0x50D00000U)
#define CSL_MAILBOX_U_BASE  (0x72000000U)

#define CSL_MSS_CTRL_MAILBOXRAM_MEM_INIT_DONE   (0x00000254U)
#define CSL_MSS_CTRL_MAILBOXRAM_MEM_INIT        (0x00000250U)
#define CSL_MSS_CTRL_MAILBOXRAM_MEM_INIT_STATUS (0x00000258U)

#define CSL_MSS_CTRL_R5SS0_CORE0_MBOX_WRITE_DONE    (0x00004000U)
#define CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_REQ      (0x00004004U)
#define CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_DONE     (0x0000400CU)
#define CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_DONE_ACK (0x00004008U)

#define CSL_MSS_CTRL_R5SS0_CORE1_MBOX_WRITE_DONE    (0x00008000U)
#define CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_REQ      (0x00008004U)
#define CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_DONE     (0x0000800CU)
#define CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_DONE_ACK (0x00008008U)

#define CSL_MSS_CTRL_R5SS1_CORE0_MBOX_WRITE_DONE    (0x0000C000U)
#define CSL_MSS_CTRL_R5SS1_CORE0_MBOX_READ_REQ      (0x0000C004U)
#define CSL_MSS_CTRL_R5SS1_CORE0_MBOX_READ_DONE     (0x0000C00CU)
#define CSL_MSS_CTRL_R5SS1_CORE0_MBOX_READ_DONE_ACK (0x0000C008U)

#define CSL_MSS_CTRL_R5SS1_CORE1_MBOX_WRITE_DONE    (0x00010000U)
#define CSL_MSS_CTRL_R5SS1_CORE1_MBOX_READ_REQ      (0x00010004U)
#define CSL_MSS_CTRL_R5SS1_CORE1_MBOX_READ_DONE     (0x0001000CU)
#define CSL_MSS_CTRL_R5SS1_CORE1_MBOX_READ_DONE_ACK (0x00010008U)

#define PROC_0_MASK  (0x00000001)
#define PROC_0_SHIFT (0U)

#define PROC_1_MASK  (0x00000010)
#define PROC_1_SHIFT (4U)

#define PROC_2_MASK  (0x00000100)
#define PROC_2_SHIFT (8U)

#define PROC_3_MASK  (0x00001000)
#define PROC_3_SHIFT (12U)

#define PROC_4_MASK  (0x00010000)
#define PROC_4_SHIFT (16U)

#define PROC_5_MASK  (0x00100000)
#define PROC_5_SHIFT (20U)

#define PROC_6_MASK  (0x01000000)
#define PROC_6_SHIFT (24U)

#define PROC_7_MASK  (0x10000000)
#define PROC_7_SHIFT (28U)

#define ACK_0_MASK  (0x00000000)
#define ACK_0_SHIFT (0U)

#define ACK_1_MASK  (0x00000001)
#define ACK_1_SHIFT (1U)

#define ACK_2_MASK  (0x00000010)
#define ACK_2_SHIFT (2U)

#define ACK_3_MASK  (0x00000011)
#define ACK_3_SHIFT (3U)

#define CSL_MSS_R5FSS0_CORE0_INTR_MBOX_READ_REQ 136
/* Aggregated interrupt to MSS CR5A from other processor asking it to read */
#define CSL_MSS_R5FSS0_CORE0_INTR_MBOX_READ_ACK 137
/* Aggregated interrupt to MSS CR5A from other processor saying the reading
                                                 from their mailbox is done. */

#define CSL_CTRL_HW_SPARE_RW0  (0x00000FD0U)
#define CSL_CTRL_HW_SPARE_RW1  (0x00000FD4U)
#define CSL_DSS_MAILBOX_U_BASE (0x83100000U)
#ifndef TPR12_PLATFORM
#define CSL_RSS_MAILBOX_U_BASE (0xA4030000)
#endif
#define CSL_MSS_MBOX_U_BASE (0xC5000000U)

#define CSL_MSS_CTRL_MSS_MAILBOX_MEM_INIT          (0x00000040U)
#define CSL_MSS_CTRL_MSS_MAILBOX_MEM_INIT_DONE     (0x00000044U)
#define CSL_MSS_CTRL_MSS_MAILBOX_MEM_INIT_STATUS   (0x00000048U)
#define CSL_MSS_CTRL_MSS_CR5A_MBOX_WRITE_DONE      (0x000005FCU)
#define CSL_MSS_CTRL_MSS_CR5A_MBOX_READ_REQ        (0x00000600U)
#define CSL_MSS_CTRL_MSS_CR5A_MBOX_READ_DONE       (0x00000604U)
#define CSL_MSS_CTRL_MSS_CR5A_B_MBOX_READ_DONE_ACK (0x00000FF0U)

#define CSL_MSS_INTR_MSS_CR5A_MBOX_READ_REQ \
    77 /* Aggregated interrupt to MSS CR5A from other processor asking it to read */
#define CSL_MSS_INTR_MSS_CR5A_MBOX_READ_ACK                                                   \
    78 /* Aggregated interrupt to MSS CR5A from other processor saying the reading from their \
          mailbox is done. */

#define CSL_DSS_CTRL_U_BASE       (0x6020000U)
#define CSL_DSS_CTRL_HW_SPARE_RW0 (0x00000FD0U)
#define CSL_DSS_CTRL_HW_SPARE_RW1 (0x00000FD4U)

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif /* HW_MAILBOX_H_ */
