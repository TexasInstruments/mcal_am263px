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

/*
 * hw_mailbox.h
 *
 * Register-level header file for AutoRadar Mailbox
 */

#ifndef HW_MAILBOX_H_
#define HW_MAILBOX_H_

#ifdef __cplusplus
extern "C"
{
#endif



/*Mailbox related address */
#define CSL_MSS_CTRL_U_BASE                     (0x2120000U)
#define CSL_DSS_MAILBOX_U_BASE                  (0x83100000U)
#if !defined (AM273X_PLATFORM) || !defined (AM2732S_PLATFORM)
#define CSL_RSS_MAILBOX_U_BASE                  (0xA4030000U)
#endif
#define CSL_MSS_MBOX_U_BASE                     (0xC5000000U)


#define CSL_MSS_CTRL_MSS_MAILBOX_MEM_INIT                                      (0x00000040U)
#define CSL_MSS_CTRL_MSS_MAILBOX_MEM_INIT_DONE                                 (0x00000044U)
#define CSL_MSS_CTRL_MSS_MAILBOX_MEM_INIT_STATUS                               (0x00000048U)
#define CSL_MSS_CTRL_MSS_CR5A_MBOX_WRITE_DONE                                  (0x000005FCU)
#define CSL_MSS_CTRL_MSS_CR5A_MBOX_READ_REQ                                    (0x00000600U)
#define CSL_MSS_CTRL_MSS_CR5A_MBOX_READ_DONE                                   (0x00000604U)
#define CSL_MSS_CTRL_MSS_CR5A_B_MBOX_READ_DONE_ACK                             (0x00000FF0U)

#define CSL_MSS_INTR_MSS_CR5A_MBOX_READ_REQ           77          /* Aggregated interrupt to MSS CR5A from other processor asking it to read */
#define CSL_MSS_INTR_MSS_CR5A_MBOX_READ_ACK           78          /* Aggregated interrupt to MSS CR5A from other processor saying the reading from their mailbox is done. */

#define CSL_DSS_CTRL_U_BASE                     (0x6020000U)
#define CSL_DSS_CTRL_HW_SPARE_RW0                                              (0x00000FD0U)
#define CSL_DSS_CTRL_HW_SPARE_RW1                                              (0x00000FD4U)


/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif  /* HW_MAILBOX_H_ */


