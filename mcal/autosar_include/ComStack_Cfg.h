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
 *  \file     ComStack_Cfg.h
 *
 *  \brief    This file contains cover page for generating doxygen
 *            API documentation.
 */

#ifndef COMSTACK_CFG_H_
#define COMSTACK_CFG_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint16 PduIdType;     /*The size of this global type depends on the
                               * *maximum number of PDUs used within one
                               * software
                               *module.*/

typedef uint16 PduLengthType; /*The size of this global type depends on the
                               *maximum length of PDUs to be sent by an ECU.*/

#ifdef __cplusplus
}
#endif

#endif /*COMSTACK_TYPES_H_*/
