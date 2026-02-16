/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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

#ifndef SYS_EXCEPTION_H
#define SYS_EXCEPTION_H

#include "sys_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @def STATE_RUNNING
 *   @brief Bootup sequence state identifier
 *          Used to identify the states in the
 *          bootup sequence
 */
#define STATE_RUNNING (uint32)((uint32)12U)

/** @def STATE_FAULT
 *   @brief Bootup sequence state identifier
 *          Used to identify the states in the
 *          bootup sequence
 */
#define STATE_FAULT (uint32)((uint32)13U)

/*! \brief
 * The abort handler fault status values
 */
typedef struct
{
    E_FW_FAULT_TYPE     faultType;
    uint8               rsvdBit8;
    uint16              lineNum;
    uint32              abortLR;
    uint32              prevLR;
    uint32              abortSpsr;
    uint32              abortSp;
    uint32              farAddress;
    E_DIFSR_ERR_STATUS  fsrErrStatus;
    E_ADIFSR_ERR_SOURCE fsrErrsource;
    E_DIFSR_SD          fsrAxiErrType;
    E_DFSR_RW           fsrErrAccType;
    E_ADIFSR_ERR_RECOV  fsrErrRecovType;
    uint16              rsvdBit16;
} mssDevFaultStatus_t;

/*! \brief
 *  Group1 ESM Erros Enum, All are low priority IRQ interrupt to BSS
 */
typedef enum
{
    ESM_FAULT_GROUP1  = 0x0U,
    ESM_FAULT_GROUP2  = 0x1U,
    ESM_FAULT_INVALID = 0xFFU
} ESM_FAULT_TYPE;

/*! \brief
 * The abort handler fault status values
 */
typedef struct
{
    ESM_FAULT_TYPE faultType;
    uint32         group1Errors;
    uint32         group2Errors;
} esmFaultStatus_t;

/*! \brief
 * Software service task type
 */
typedef enum
{
    SVC_SWITCH_ARM_MODE = 0x0U,
    SVC_TEST_SWI        = 0x1U,
    NUM_OF_SVC_TYPES    = 0x2U
} SVC_TYPES;

/*! \brief
 *  BSS Fault Enum
 */
typedef enum
{
    MSS_FAULT_FW      = 0x0U,
    MSS_FAULT_ESM     = 0x1U,
    MSS_FAULT_INVALID = 0xFFU
} MSS_FAULT_TYPE;

/*! \brief
 * The MSS fault status global structure
 */
typedef struct
{
    MSS_FAULT_TYPE      mssFaultType;
    mssDevFaultStatus_t s_fwFaultStatus;
    esmFaultStatus_t    s_esmFaultStatus;
} mssFaultStatus_t;

void sys_cUabort(uint32 abortLR, uint32 abortSpsr, uint32 abortSp);
void sys_cPabort(uint32 abortLR, uint32 abortSpsr, uint32 abortSp);
void sys_cDabort(uint32 abortLR, uint32 abortSpsr, uint32 abortSp);
void sys_cSwiInt(uint8 svcNum);
void mssSafeStateHandler(const mssFaultStatus_t mssFaultStatus);

#ifdef __cplusplus
}
#endif /*extern "C" */

#endif
