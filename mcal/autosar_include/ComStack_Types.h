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

/**
 *  \file     MemMap.h
 *
 *  \brief    This file contains cover page for generating doxygen
 *            API documentation.
 */

#ifndef COMSTACK_TYPES_H_
#define COMSTACK_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ECUC_SW_MAJOR_VERSION   1
#define ECUC_SW_MINOR_VERSION   0
#define ECUC_SW_PATCH_VERSION   0
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"        /** @req COMM820.partially */
#include "ComStack_Cfg.h"
/*LDRA_ANALYSIS*/


typedef struct {
    uint8        *SduDataPtr;   /* payload */
    PduLengthType SduLength;    /* length of SDU */
} PduInfoType;

typedef enum {
    TP_STMIN = 0,
    TP_BS,
    TP_BC
} TPParameterType;

typedef enum {
    TP_DATACONF,
    TP_DATARETRY,
    TP_CONFPENDING,
    TP_NORETRY
} TpDataStateType;

typedef struct {
    TpDataStateType TpDataState;
    PduLengthType   TxTpDataCnt;
} RetryInfoType;


/* IMPROVEMENT: remove all non-E_prefixed error enum values */
typedef enum {
    BUFREQ_OK       = 0,
    BUFREQ_NOT_OK   = 1,
    BUFREQ_E_NOT_OK = 1,
    BUFREQ_BUSY     = 2,
    BUFREQ_E_BUSY   = 2,
    BUFREQ_OVFL     = 3,
    BUFREQ_E_OVFL   = 3
} BufReq_ReturnType;

/*
 * 0x00--0x1e General return types
 * 0x1f--0x3c Error notif, CAN
 * 0x3d--0x5a Error notif, LIN
 * more
 */
typedef uint8 NotifResultType;

#define NTFRSLT_OK                     0x00
#define NTFRSLT_E_NOT_OK               0x01
#define NTFRSLT_E_TIMEOUT_A            0x02
#define NTFRSLT_E_TIMEOUT_BS           0x03
#define NTFRSLT_E_TIMEOUT_CR           0x04
#define NTFRSLT_E_WRONG_SN             0x05
#define NTFRSLT_E_INVALID_FS           0x06
#define NTFRSLT_E_UNEXP_PDU            0x07
#define NTFRSLT_E_WFT_OVRN             0x08
#define NTFRSLT_E_ABORT                0x09
#define NTFRSLT_E_NO_BUFFER            0x0A
#define NTFRSLT_E_CANCELATION_OK       0x0B
#define NTFRSLT_E_CANCELATION_NOT_OK   0x0C
#define NTFRSLT_PARAMETER_OK           0x0D
#define NTFRSLT_E_PARAMETER_NOT_OK     0x0E
#define NTFRSLT_E_RX_ON                0x0F
#define NTFRSLT_E_VALUE_NOT_OK         0x10

typedef uint8 BusTrcvErrorType;

#define BUSTRCV_NO_ERROR    0x00
#define BUSBUSTRCV_E_ERROR  0x01

#define COMSTACKTYPE_AR_MINOR_VERSION       1
#define COMSTACKTYPE_AR_MAJOR_VERSION       4
#define COMSTACKTYPE_AR_PATCH_VERSION       0

typedef uint8 NetworkHandleType;

#ifdef __cplusplus
}
#endif

#endif /*COMSTACK_TYPES_H_*/
