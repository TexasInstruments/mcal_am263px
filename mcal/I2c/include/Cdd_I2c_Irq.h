/*
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     Cdd_I2c_Irq.h
 *
 *  \brief    This file contains ISR function declaration for CDD I2C MCAL driver
 *
 */

#ifndef CDD_I2C_IRQ_H_
#define CDD_I2C_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_I2c.h"
#include "Os.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         GLOBAL VARIABLES                                   */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/** \brief Service for Cdd_I2c_ISR
 *  \verbatim
 *  Service name        : Cdd_I2c_ISR
 *  Syntax              : void Cdd_I2c_ISR(void)
 *  Parameters (in)     : None
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : ISR for CDD_I2C
 *  \endverbatim
 */

#if (STD_OFF == CDD_I2C_POLLING_MODE) /*#if(STD_OFF == CDD_I2C_POLLING_MODE)*/
#if defined(USED_CDD_I2C_HW_UNIT_0)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit0_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit0_ISR);
#endif /* ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2).... */
#endif /* USED_CDD_I2C_HW_UNIT_0 ...*/

#if defined(USED_CDD_I2C_HW_UNIT_1)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit1_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit1_ISR);
#endif /* ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2).... */
#endif /* USED_CDD_I2C_HW_UNIT_1 ...*/

#if defined(USED_CDD_I2C_HW_UNIT_2)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit2_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit2_ISR);
#endif /* ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2).... */
#endif /* USED_CDD_I2C_HW_UNIT_2 ...*/

#if defined(USED_CDD_I2C_HW_UNIT_3)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit3_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit3_ISR);
#endif /* ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2).... */
#endif /* USED_CDD_I2C_HW_UNIT_3 ...*/

#endif

#ifdef __cplusplus
}
#endif

#endif
