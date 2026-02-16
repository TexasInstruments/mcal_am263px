/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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

#include <sipc_notify_cfg.h>
#include <sipc_notify_src.h>
// #include <drivers/hw_include/am263px/cslr_soc.h>

/* Dedicated hsm mailbox memories address and size */
#define HSM_MBOX_MEM      (0x44000000)
#define HSM_MBOX_MEM_SIZE ((2U * 1024U) - 4)

/* SIPC_SwQueue structure should be stored in a particular shared memory section
 * In this section we define such Queues and store it at the bottom of our shared Mbox memory so that
 * Both R5 and M4 cores can access this data structure .
 * Each of the SwQueue instance will point to a corresponding Queue memory location in HSM_MBOX_MEM area
 */
#define CORE0_TO_HSM0_0_SW_QUEUE \
    (SIPC_SwQueue *)(HSM_MBOX_MEM + HSM_MBOX_MEM_SIZE - MAILBOX_MAX_SW_QUEUE_STRUCT_SIZE * 4)
#define HSM0_0_TO_CORE0_SW_QUEUE \
    (SIPC_SwQueue *)(HSM_MBOX_MEM + HSM_MBOX_MEM_SIZE - MAILBOX_MAX_SW_QUEUE_STRUCT_SIZE * 3)
#define CORE1_TO_HSM0_0_SW_QUEUE \
    (SIPC_SwQueue *)(HSM_MBOX_MEM + HSM_MBOX_MEM_SIZE - MAILBOX_MAX_SW_QUEUE_STRUCT_SIZE * 2)
#define HSM0_0_TO_CORE1_SW_QUEUE \
    (SIPC_SwQueue *)(HSM_MBOX_MEM + HSM_MBOX_MEM_SIZE - MAILBOX_MAX_SW_QUEUE_STRUCT_SIZE * 1)

/* For AM263Px SBL runs on R50 core so one of the secure master has to be R50 by default
 * Default second secure master is R51 */
uint8_t       gCore_Ids[MAX_SEC_CORES_WITH_HSM] = {CORE_ID_R5FSS0_0, CORE_ID_R5FSS0_1, CORE_ID_HSM0_0};
/* Pointer to the Queues R5 -> HSM indexed by Sec master core Id */
SIPC_SwQueue *gSIPC_QueSecureHostToHsm[MAX_SEC_CORES_WITH_HSM - 1] = {CORE0_TO_HSM0_0_SW_QUEUE,
                                                                      CORE1_TO_HSM0_0_SW_QUEUE};

/* Pointer to the Queues HSM -> R5 indexed by Sec master core Id */
SIPC_SwQueue *gSIPC_QueHsmToSecureHost[MAX_SEC_CORES_WITH_HSM - 1] = {HSM0_0_TO_CORE0_SW_QUEUE,
                                                                      HSM0_0_TO_CORE1_SW_QUEUE};

/* Mailbox queues will be dynamically created at runtime via sysconfig similarly as Rpmessage queues are made
 * Pre-defined mailbox config to send message from R5 to HSM
 * based on which core is configured as secure master the swQ data structure will be populated */
SIPC_MailboxConfig gSIPC_SecureHostMboxConfig[CORE_ID_MAX - 1] = {
    {
        /* with HSM0_0 */
        .writeDoneMailboxBaseAddr  = R5FSS0_0_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = R5FSS0_0_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = R5FSS0_0_MBOX_READ_DONE,
        .wrIntrBitPos              = HSM0_0_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = HSM0_0_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,
    },

    {
        /* with HSM0_0 */
        .writeDoneMailboxBaseAddr  = R5FSS0_1_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = R5FSS0_1_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = R5FSS0_1_MBOX_READ_DONE,
        .wrIntrBitPos              = HSM0_0_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = HSM0_0_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,
    },
    {
        /* with HSM0_0 */
        .writeDoneMailboxBaseAddr  = R5FSS1_0_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = R5FSS1_0_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = R5FSS1_0_MBOX_READ_DONE,
        .wrIntrBitPos              = HSM0_0_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = HSM0_0_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,
    },
    {
        /* with HSM0_0 */
        .writeDoneMailboxBaseAddr  = R5FSS1_1_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = R5FSS1_1_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = R5FSS1_1_MBOX_READ_DONE,
        .wrIntrBitPos              = HSM0_0_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = HSM0_0_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,
    },
};

/* Pre-defined mailbox config to send message from R5 to HSM
 * based on which core is configured as secure master the swQ data structure will be populated */
SIPC_MailboxConfig gSIPC_HsmMboxConfig[CORE_ID_MAX - 1] = {
    {
        /* MBOX config with R5FSS0-0 */
        .writeDoneMailboxBaseAddr  = HSM0_0_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = HSM0_0_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = HSM0_0_MBOX_READ_DONE,
        .wrIntrBitPos              = R5FSS0_0_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = R5FSS0_0_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,
    },
    {
        /* MBOX config with R5FSS0-1 */
        .writeDoneMailboxBaseAddr  = HSM0_0_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = HSM0_0_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = HSM0_0_MBOX_READ_DONE,
        .wrIntrBitPos              = R5FSS0_1_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = R5FSS0_1_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,

    },
    {
        /* MBOX config with R5FSS1-0 */
        .writeDoneMailboxBaseAddr  = HSM0_0_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = HSM0_0_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = HSM0_0_MBOX_READ_DONE,
        .wrIntrBitPos              = R5FSS1_0_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = R5FSS1_0_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,
    },
    {
        /* MBOX config with R5FSS1-1 */
        .writeDoneMailboxBaseAddr  = HSM0_0_MBOX_READ_DONE_ACK,
        .readReqMailboxBaseAddr    = HSM0_0_MBOX_READ_DONE,
        .readReqMailboxClrBaseAddr = HSM0_0_MBOX_READ_DONE,
        .wrIntrBitPos              = R5FSS1_1_MBOX_WRITE_PROC_BIT_POS,
        .rdIntrBitPos              = R5FSS1_1_MBOX_READ_PROC_BIT_POS,
        .swQ                       = NULL_PTR,

    },
};

/* Global data structure defining interrupt config for all the cores. */
SIPC_InterruptConfig gSIPC_InterruptConfig[INTR_CFG_NUM_MAX][CORE_ID_MAX] =
    /* interrupt config number 0 */
    {{/*interrupt config for R5FSS0_0 core */
      {
          .intNum   = R5FSS0_0_MBOX_READ_ACK_INTR, /* interrupt line on R5FSS0-0 */
          .eventId  = 0U,                          /* not used */
          .numCores = 1U, /* number of cores that send messages which tied to this interrupt line */
          .coreIdList =
              {
                  /* sec core ID's tied to this interrupt line */
                  CORE_INDEX_HSM,
              },
          .clearIntOnInit = 1,
      },
      /* Interrupt config for R5FSS0_1 Core */
      {
          .intNum   = R5FSS0_1_MBOX_READ_ACK_INTR, /* interrupt line on R5FSS0-1 */
          .eventId  = 0U,                          /* not used */
          .numCores = 1U, /* number of cores that send messages which tied to this interrupt line */
          .coreIdList =
              {
                  /* sec core ID's tied to this interrupt line */
                  CORE_INDEX_HSM,
              },
          .clearIntOnInit = 1,
      },
      /* Interrupt config for R5FSS1_0 Core */
      {
          .intNum   = R5FSS1_0_MBOX_READ_ACK_INTR, /* interrupt line on R5FSS0-1 */
          .eventId  = 0U,                          /* not used */
          .numCores = 1U, /* number of cores that send messages which tied to this interrupt line */
          .coreIdList =
              {
                  /* sec core ID's tied to this interrupt line */
                  CORE_INDEX_HSM,
              },
          .clearIntOnInit = 1,
      },
      /* Interrupt config for R5FSS1_1 Core */
      {
          .intNum   = R5FSS1_1_MBOX_READ_ACK_INTR, /* interrupt line on R5FSS0-1 */
          .eventId  = 0U,                          /* not used */
          .numCores = 1U, /* number of cores that send messages which tied to this interrupt line */
          .coreIdList =
              {
                  /* sec core ID's tied to this interrupt line */
                  CORE_INDEX_HSM,
              },
          .clearIntOnInit = 1,
      },
      /* Interrupt Config for HSM core */
      {
          .intNum   = HSM0_0_MBOX_READ_ACK_INTR, /* interrupt line on M4 */
          .eventId  = 0U,                        /* not used */
          .numCores = 2U, /* number of cores that send messages which tied to this interrupt line */
          .coreIdList =
              {
                  /* sec core ID's tied to this interrupt line */
                  CORE_INDEX_SEC_MASTER_0,
                  CORE_INDEX_SEC_MASTER_1,
              },
          .clearIntOnInit = 1,
      }}};

int32_t SIPC_Register_Isr(HwiP_Params *pHwiParams, SIPC_InterruptConfig *pInterruptConfig, SIPC_Params *params,
                          HwiP_FxnCallback callback)
{
    int32_t status = 0;

    Vim_IntCfg intCfg;
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_LEVEL;
    intCfg.priority = params->intrPriority;
    intCfg.intNum   = pInterruptConfig->intNum;
    intCfg.handler  = (void *)callback;
    vimRegisterInterrupt(&intCfg);

    return status;
}
