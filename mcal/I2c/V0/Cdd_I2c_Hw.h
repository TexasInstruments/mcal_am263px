/* ======================================================================
 *   Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file     Cdd_I2c_Hw.h
 *
 *  \brief    This file contains the private implementation of I2C HW functions.
 *
 */

#ifndef CDD_I2C_HW_H_
#define CDD_I2C_HW_H_

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#include "Cdd_I2c_Priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */
/*                               Macros                             */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                         Structures and Enums                     */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                          Function Declarations                   */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

void Cdd_I2c_HwInit(uint32 baseAddr, uint32 baudRate, uint32 hwUnitFrequency, uint32 sysClk,
                    Cdd_I2c_AddressType ownAddress);
void Cdd_I2c_HwDeInit(uint32 baseAddr);

Cdd_I2c_ChannelResultType Cdd_I2c_HwTxPolling(Cdd_I2c_ChObjType *chObj);
Cdd_I2c_ChannelResultType Cdd_I2c_HwTxPollingContinue(Cdd_I2c_ChObjType *chObj);
Cdd_I2c_ChannelResultType Cdd_I2c_HwRxPolling(Cdd_I2c_ChObjType *chObj);
Cdd_I2c_ChannelResultType Cdd_I2c_HwRxPollingContinue(Cdd_I2c_ChObjType *chObj);
Cdd_I2c_ChannelResultType Cdd_I2c_HwTxIntr(Cdd_I2c_ChObjType *chObj);
Cdd_I2c_ChannelResultType Cdd_I2c_HwRxIntr(Cdd_I2c_ChObjType *chObj);
Cdd_I2c_ChannelResultType Cdd_I2c_HwTxRxIntrContinue(Cdd_I2c_ChObjType *chObj);

void Cdd_I2c_HwCancelPolling(Cdd_I2c_ChObjType *chObj);
void Cdd_I2c_HwCancelIntr(Cdd_I2c_ChObjType *chObj);

void Cdd_I2c_HwDisableAllIntr(uint32 baseAddr);
void Cdd_I2c_HwClearAllStatus(uint32 baseAddr);

#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
void Cdd_I2c_HwRegReadback(uint32 baseAddr, Cdd_I2c_RegisterReadbackType *regRbPtr);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_I2C_HW_H_ */
