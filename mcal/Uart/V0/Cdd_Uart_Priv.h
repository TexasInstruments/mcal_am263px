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
    /* UART Module Version Register */
    uint32 MVR;
    /* UART System Configuration Register */
    uint32 SYSC;
    /* UART System Status Register */
    uint32 SYSS;
    /* Interrupt Enable Register for UART, CIR, IrDA modes */
    uint32 IER;
} CddUart_RegisterReadbackType;
#endif

/** \brief CDD UART channel handles */
extern CddUart_Object CddUart_ChannelObjects[CDD_UART_NUM_CHANNELS];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Function for mapping Configuration parameters to UART Handle. */
FUNC(void, CDD_UART_CODE)
Cdd_Uart_Object_Configuration_Mapping(CddUart_Handle CddUartHandle,
                                      P2CONST(Cdd_Uart_ConfigType, AUTOMATIC, CDD_UART_CFG) ChannelCfgPtr);

/** \brief Function to get the index of the Channel ID */
uint32 Cdd_Uart_GetChannelIndex(uint8 hUart_Channel_ID);

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
