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

/**
 *  \file     EthIf_Cbk.h
 *
 *  \brief    This file contains cover page for generating doxygen
 *            API documentation.
 *
 */

#ifndef ETHIF_CBK_H
#define ETHIF_CBK_H
#include "Eth_GeneralTypes.h"
#include "EthTrcv_Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

void EthIf_RxIndication(uint8         CtrlIdx,
                        Eth_FrameType FrameType,
                        boolean       IsBroadcast,
                        uint8        *PhysAddrPtr,
                        Eth_DataType *DataPtr,
                        uint16        LenByte);
void EthIf_TxConfirmation(uint8          CtrlIdx,
                          Eth_BufIdxType BufIdx,
						  Std_ReturnType Result);
void EthIf_CtrlModeIndication(uint8        CtrlIdx,
                              Eth_ModeType CtrlMode);
void EthIf_TrcvModeIndication(uint8 CtrlIdx, EthTrcv_ModeType TrcvMode);

#ifdef __cplusplus
}
#endif

#endif /* ETHIF_CBK_H end file*/

