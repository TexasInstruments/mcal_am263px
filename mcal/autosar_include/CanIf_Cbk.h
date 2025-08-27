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
 *  \file     CanIf_Cbk.h
 *
 *  \brief    This file contains cover page for generating doxygen
 *            API documentation.
 */

#ifndef CANIF_CBK_H
#define CANIF_CBK_H

#ifdef __cplusplus
extern "C"
{
#endif

void CanIf_ControllerBusOff(uint8 Controller);
void CanIf_RxIndication(const Can_HwType* Mailbox, 
    const PduInfoType* PduInfoPtr);
void CanIf_TxConfirmation(PduIdType CanTxPduId);
Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, 
									PduInfoType* PduInfoPtr);
void CanIf_ControllerModeIndication(uint8                    ControllerId,
                                    Can_ControllerStateType ControllerMode);
#ifdef __cplusplus
}
#endif

#endif /* CANIF_CBK_H end file*/

