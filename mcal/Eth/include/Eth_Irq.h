/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *  \file     Eth_Irq.h
 *
 *  \brief    This file contains ISR function declaration for ETH MCAL driver
 *
 */

/**
 *  \ingroup MCAL_ETH_API
 *  @{
 */

#ifndef ETH_IRQ_H_
#define ETH_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#if (ETH_ISR_TYPE == ETH_ISR_CAT2)
#include "Os.h"
#endif
#include "sys_common.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name ETH Driver ISR SW Version Info
 *
 *  Defines for ETH Driver ISR version used for compatibility checks
 *  @{
 */
/** \brief Driver ISR Implementation Major Version */
#define ETH_IRQ_MAJOR_VERSION (10U)
/** \brief Driver ISR Implementation Minor Version */
#define ETH_IRQ_MINOR_VERSION (0U)
/** \brief Driver ISR Implementation Patch Version */
#define ETH_IRQ_PATCH_VERSION (0U)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief ISR for frame reception interrupts of the indexed controller
 *
 *  \verbatim
 *  Service name      : Eth_RxIrqHdlr_0
 *  Syntax            : void Eth_RxIrqHdlr_0(void)
 *  Service ID[hex]   : 0x10
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant.
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Handles frame reception interrupts of the indexed
 *                      controller
 *  \endverbatim
 */
#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
FUNC(void, ETH_CODE_ISR) Eth_RxIrqHdlr_0(void);
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_RxIrqHdlr_0);
#endif

/**
 *  \brief ISR for frame transmission interrupts of the indexed controller
 *
 *  \verbatim
 *  Service name      : Eth_TxIrqHdlr_0
 *  Syntax            : void Eth_TxIrqHdlr_0(void)
 *  Service ID[hex]   : 0x11
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant.
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Handles frame transmission interrupts of the indexed
 *                      controller
 *  \endverbatim
 */

#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
FUNC(void, ETH_CODE_ISR) Eth_TxIrqHdlr_0(void);
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_TxIrqHdlr_0);
#endif

/**
 *  \brief ISR for misc. interrupts of the indexed controller
 *
 *  \verbatim
 *  Service name      : Eth_MiscIrqHdlr_0
 *  Syntax            : void Eth_MiscIrqHdlr_0(void)
 *  Service ID[hex]   : NA
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant.
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Handles misc. interrupts of the indexed
 *                      controller
 *  \endverbatim
 */
#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
FUNC(void, ETH_CODE_ISR) Eth_MiscIrqHdlr_0(void);
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_MiscIrqHdlr_0);
#endif

/**
 *  \brief ISR for Receive threshold interrupts of the indexed controller
 *
 *  \verbatim
 *  Service name      : Eth_RxThreshIrqHdlr_0
 *  Syntax            : void Eth_RxThreshIrqHdlr_0(void)
 *  Service ID[hex]   : NA
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant.
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Handles receive threshold interrupts of the indexed
 *                      controller
 *  \endverbatim
 */
#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
void Eth_RxThreshIrqHdlr_0(void);
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_RxThreshIrqHdlr_0);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ETH_IRQ_H_ */

/* @} */
