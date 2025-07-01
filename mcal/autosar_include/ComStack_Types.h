/* ======================================================================
 *   Copyright (C) 2022 Texas Instruments Incorporated
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
