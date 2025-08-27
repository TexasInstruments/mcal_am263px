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

#ifndef CAN_GENERALTYPES_H_
#define CAN_GENERALTYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint16 Can_HwHandleType;

/** \brief State transitions that are used by the function
 *Can_SetControllerMode. */
/*
*Design: MCAL-16873
*/
typedef enum
{
    CAN_CS_UNINIT,  /**< CAN Controller is not yet configured.
                    **/
    CAN_CS_STARTED, /**< CAN controller transition value to request state STARTED.
                 **/
    CAN_CS_STOPPED,  /**< CAN controller transition value to request state STOPPED.
                 **/
    CAN_CS_SLEEP /**< CAN controller transition value to request state SLEEP. */
} Can_ControllerStateType;

/** \brief Return values of CAN driver API. */
/* 
*Design: MCAL-17080
*/
typedef enum
{
    CAN_BUSY = 0x02U
    /**< Transmit request could not be processed because no transmit
      * object was available. */
} Can_ReturnType;

/** \brief Error states of a CAN controller. */
/* 
*Design: MCAL-17027
*/
typedef enum
{
  CAN_ERRORSTATE_ACTIVE,
  /**< The CAN controller takes fully part in communication */
  CAN_ERRORSTATE_PASSIVE,
  /**< The CAN controller takes part in communication,
    *  but does not send active error frames. */
  CAN_ERRORSTATE_BUSOFF,
  /**< The CAN controller does not take part in communication */
} Can_ErrorStateType;

typedef uint32 Can_IdType;
/*
*Design: MCAL-17125, MCAL-17044
*/
typedef struct Can_PduType_s {
    PduIdType  swPduHandle;
    /**< private data for CanIf,just save and use for callback */
    uint8      length;
    /**< Length, max 8 bytes/64 bytes for CAN FD */
    Can_IdType id;
    /**< the CAN ID, 29 or 11-bit */
    uint8     *sdu;
    /**< data ptr */
} Can_PduType;

/*Requirements: SWS_Can_00496 */
/*
*Design: MCAL-17119, MCAL-16841
*/
typedef struct
{
    Can_IdType CanId;
    /**< Standard/Extended CAN ID of CAN L-PDU */
    Can_HwHandleType Hoh;
    /**< ID of the corresponding Hardware Object Range */
    uint8 ControllerId;
    /**< Mailbox Corresponding Controller Id */
}Can_HwType;

#ifdef __cplusplus
}
#endif

#endif /* CAN_GENERALTYPES_H_ */
