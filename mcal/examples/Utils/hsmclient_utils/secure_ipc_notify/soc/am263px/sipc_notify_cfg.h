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

#ifndef SIPC_NOTIFY_CFG_H_
#define SIPC_NOTIFY_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <bootloader_utils/am263px/soc.h>
#include "sys_vim.h"
#include <HwiP.h>
#include <CpuIdP.h>

/**
 * @brief
 * SIPC message size in bytes each element of queue will be of this size. */
#define SIPC_MSG_SIZE (13u)

/* Max number of interrupt configs possible for AM263Px */
#define INTR_CFG_NUM_MAX (1u)

/* If SIPC is compiled for R5 core then Max client ID = 32
 * Else for HSM its 2 */

/* HSM specific register addresses defined here to remove the dependency on CSL files */
#define HSM_SOC_CTRL_U_BASE                 (0x40000000U)
#define HSM_SOC_CTRL_HSM_MBOX_READ_DONE_ACK (0x00000048U)
#define HSM_SOC_CTRL_HSM_MBOX_READ_DONE     (0x0000004CU)

/* R5 Register for sending and receiving IPC interrutps
 * As write DONE interrupt line is being used by regular IPC communication we will use READ_DONE_ACK
 * register to post the interrupt to receiving core and it will read READ_DONE register to process
 * that interrupt */
#define R5FSS0_0_MBOX_READ_DONE_ACK (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_DONE_ACK)
#define R5FSS0_0_MBOX_READ_DONE     (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS0_CORE0_MBOX_READ_DONE)
#define R5FSS0_1_MBOX_READ_DONE_ACK (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_DONE_ACK)
#define R5FSS0_1_MBOX_READ_DONE     (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS0_CORE1_MBOX_READ_DONE)
#define R5FSS1_0_MBOX_READ_DONE_ACK (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS1_CORE0_MBOX_READ_DONE_ACK)
#define R5FSS1_0_MBOX_READ_DONE     (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS1_CORE0_MBOX_READ_DONE)
#define R5FSS1_1_MBOX_READ_DONE_ACK (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS1_CORE1_MBOX_READ_DONE_ACK)
#define R5FSS1_1_MBOX_READ_DONE     (MCAL_CSL_MSS_CTRL_U_BASE + CSL_MSS_CTRL_R5SS1_CORE1_MBOX_READ_DONE)

/* HSM registers for sending and receiving IPC interrupts */
#define HSM0_0_MBOX_READ_DONE_ACK (HSM_SOC_CTRL_U_BASE + HSM_SOC_CTRL_HSM_MBOX_READ_DONE_ACK)
#define HSM0_0_MBOX_READ_DONE     (HSM_SOC_CTRL_U_BASE + HSM_SOC_CTRL_HSM_MBOX_READ_DONE)

/* CPU bit positions within the HSM mailbox registers for sending interrupt
 * HSM will write the READ_DONE_ACK register to raise an interrupt to R5 core */
#define R5FSS0_0_MBOX_WRITE_PROC_BIT_POS (0U)
#define R5FSS0_1_MBOX_WRITE_PROC_BIT_POS (4U)
#define R5FSS1_0_MBOX_WRITE_PROC_BIT_POS (8U)
#define R5FSS1_1_MBOX_WRITE_PROC_BIT_POS (12U)

/* Bitshift to raise an interrupt from R5 core to HSM */
#define HSM0_0_MBOX_WRITE_PROC_BIT_POS (6U)

/* CPU bit positions within the mailbox registers for receiving interrupts */
#define R5FSS0_0_MBOX_READ_PROC_BIT_POS (0U)
#define R5FSS0_1_MBOX_READ_PROC_BIT_POS (4U)
#define R5FSS1_0_MBOX_READ_PROC_BIT_POS (8U)
#define R5FSS1_1_MBOX_READ_PROC_BIT_POS (12U)
#define HSM0_0_MBOX_READ_PROC_BIT_POS   (24U)

/* Mailbox interrupts numbers */
#define R5FSS0_0_MBOX_READ_ACK_INTR (137U)
#define R5FSS0_1_MBOX_READ_ACK_INTR (137U)
#define R5FSS1_0_MBOX_READ_ACK_INTR (137U)
#define R5FSS1_1_MBOX_READ_ACK_INTR (137U)
#define HSM0_0_MBOX_READ_ACK_INTR   (56U)

/**
 * @brief
 * Core Ids to identify different cores.
 * @ingroup DRV_SIPC_NOTIFY_MODULE
 */
typedef enum SIPC_CoreId_
{
    CORE_ID_R5FSS0_0 = 0,
    CORE_ID_R5FSS0_1,
    CORE_ID_R5FSS1_0,
    CORE_ID_R5FSS1_1,
    CORE_ID_HSM0_0,
    CORE_ID_MAX
} SIPC_coreId;

/**
 * @brief
 * Secure host Id to identify different secure hosts.
 * Max number of secure host on AM263Px is 2.
 * @ingroup DRV_SIPC_NOTIFY_MODULE
 */
typedef enum SIPC_SecCoreId_
{
    CORE_INDEX_SEC_MASTER_0 = 0,
    CORE_INDEX_SEC_MASTER_1,
    CORE_INDEX_HSM,
    MAX_SEC_CORES_WITH_HSM
} SIPC_SecCoreId;

#if defined(__ARM_ARCH_7R__)

/* If building for R5 then read selfcore ID from the Core Cluster register */
static uint32_t SIPC_readSelfCoreID(void)
{
    uint32_t         coreId;
    CSL_ArmR5CPUInfo cpuId = {0, 0};
    CSL_armR5GetCpuID(&cpuId);
    /* both cpuId and greId fields can be either 0 or 1
     * ex for R5FSS1-0 core grpId = 1 and cpu id = 0 */
    coreId = cpuId.cpuID | (cpuId.grpId) << 1;
    return coreId;
}
#define SELF_CORE_ID (SIPC_readSelfCoreID())

/**
 * @brief
 * Total number of client Ids available
 * For HSM core it is fixed to 2.
 * @ingroup DRV_SIPC_NOTIFY_MODULE
 */
#define SIPC_CLIENT_ID_MAX (5U)

#else
#define SIPC_CLIENT_ID_MAX (2U)
#define SELF_CORE_ID       (CORE_ID_HSM0_0)
#endif

/*
 *  Client ID used by HSM server's boot notify message
 */
#define SIPC_BOOT_NOTIFY_CLIENT_ID (0U)

#ifdef __cplusplus
}
#endif

#endif
