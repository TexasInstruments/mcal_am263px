/*
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Cdd_FsiRx_Irq.h
 *
 *  \brief    This file contains ISR function declaration for CDD FSI RX driver
 *
 */

/**
 *  \ingroup MCAL_CDD_FSI_RX API
 *  @{
 */

#ifndef CDD_FSI_RX_IRQ_H_
#define CDD_FSI_RX_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_FsiRx.h"
#if (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
#include "Os.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CDD_FSI_RX_INT_MASK ((uint16)0xFFFF)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/** brief CDD FSI RX ISR */

#if defined(CDD_FSI_RX_INSTANCE_0)

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit0(void);

#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit0);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit0(void);
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit0);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#endif /* CDD_FSI_RXINSTANCE_0 */

#if defined(CDD_FSI_RX_INSTANCE_1)

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit1(void);

#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit1);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit1(void);
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit1);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#endif /* CDD_FSI_RXINSTANCE_1 */

#if defined(CDD_FSI_RX_INSTANCE_2)

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit2(void);

#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit2);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit2(void);
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit2);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#endif /* CDD_FSI_RXINSTANCE_2 */

#if defined(CDD_FSI_RX_INSTANCE_3)

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit3(void);

#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit3);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit3(void);
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit3);
#endif /* ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1).... */

#endif /* CDD_FSI_RXINSTANCE_3 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_FSI_RX_IRQ_H_ */

/* @} */
