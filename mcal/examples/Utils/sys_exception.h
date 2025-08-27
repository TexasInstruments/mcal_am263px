/** @file sys_exception.h
 *   @brief file defines the exception functions prototypes of Cortex R4 processor.
 *   @date 28.Jul.2015
 *   @version 01.00.00
 *
 */

/*
 * Copyright (C) 2023 Texas Instruments Incorporated - TI web adress www.ti.com
 *
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
