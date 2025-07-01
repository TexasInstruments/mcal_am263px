/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     Cdd_Uart_Priv.h
 *
 *  \brief    This file contains interface header for internal functions for UART Complex Device
 * Driver
 *
 */
/**
 *  \defgroup CDD_UART Complex Device Driver
 *  This module implements a CDD driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                This driver can:
 *                - Configure the UART config registers
 *                - Read and write data over UART
 *
 *  This files defines CDD UART data structures
 *   @sa CDD_UART
 *  @{
 */
/*  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_Uart_Priv.h
 *      Project:  Complex Device Driver
 *       Module:  CddUartDriver
 *
 *  Description:  This module implements a driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                With this driver you can:
 *                - Configure the UART config registers
 *                - Initialize the UART configuration
 *                - Read and write data over the UART
 **************************************************************************************************/

#ifndef CDD_UART_PRIV_H_
#define CDD_UART_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_Uart_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief name CDD UART Driver ID Info
 */
/** \brief CDD Module ID */
#define CDD_UART_MODULE_ID 255U
/** \brief Texas Instruments Vendor ID */
#define CDD_UART_VENDOR_ID 44U
/** \brief Texas Instruments Vendor ID */
#define CDD_UART_INSTANCE_ID 0U

/**
 *  \brief Number of own resources in use for DMA Mode
 */
#define EDMA_NUM_DMACH_SOC     64
#define EDMA_NUM_PARAMSETS_SOC 256

/* ================================================================ */
/*                         Structures and Enums                     */
/* ================================================================ */

/** \brief UART registers */
#if (STD_ON == CDD_UART_REGISTER_READBACK_API)
typedef struct
{
    /* UART Global Control Register 0 */
    uint32 SCIGCR0;
    /* UART Global Control Register 1 */
    uint32 SCIGCR1;
} CddUart_RegisterReadbackType;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Function for mapping Configuration parameters to UART Handle. */
FUNC(void, CDD_UART_CODE)
Cdd_Uart_Object_Configuration_Mapping(CddUart_Handle CddUartHandle,
                                      P2CONST(Cdd_Uart_ConfigType, AUTOMATIC, CDD_UART_CFG) ChannelCfgPtr);

/** \brief UART Hardware IP instance based Register Readback Function. */
#if (STD_ON == CDD_UART_REGISTER_READBACK_API)
FUNC(void, CDD_UART_CODE)
Uart_Cdd_RegisterReadback(CddUart_Handle CddUartHandle,
                          P2VAR(CddUart_RegisterReadbackType, AUTOMATIC, CDD_UART_CFG) RegisterSetPtr);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_UART_PRIV_H_ */

/* @} */
