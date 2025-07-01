/*
 *
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Cdd_FsiTx_Irq.c
 *
 *  \brief    This file contains the ISR implementation of CDD FSI TX driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_FsiTx.h"
#include "Cdd_FsiTx_Irq.h"
#include "Cdd_FsiTx_Cfg.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define CDD_FSITX_START_SEC_VAR_NO_INIT_8
#include "Cdd_FsiTx_MemMap.h"
/** \brief CDD_FSI_TX ISR Index */
extern VAR(uint8, CDD_FSITX_VAR_CLEARED) Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HW_UNIT_CNT];
#define CDD_FSITX_STOP_SEC_VAR_NO_INIT_8
#include "Cdd_FsiTx_MemMap.h"
extern VAR(Cdd_FsiTx_DriverObjType, CDD_FSITX_VAR_CLEARED) Cdd_FsiTx_DrvObj;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_FSITX_START_SEC_ISR_CODE
#include "Cdd_FsiTx_MemMap.h"

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_0)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT1_IrqUnit0(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT1_IrqUnit0)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_0] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_0]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = ((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT1, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_0) */
/*******************************************************************************************************/
/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_0)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT2_IrqUnit0(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT2_IrqUnit0)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_0] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_0]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = ((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT2, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_0) */
/******************************************************************************************************/
/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_1)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT1_IrqUnit1(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT1_IrqUnit1)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_1] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_1]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = ((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT1, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_1) */
/**********************************************************************************************************/
/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_1)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT2_IrqUnit1(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT2_IrqUnit1)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_1] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_1]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = ((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT2, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_1) */
/************************************************************************************************************/
/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_2)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT1_IrqUnit2(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT1_IrqUnit2)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_2] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_2]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = (uint8)((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT1, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_2) */
/*******************************************************************************************************/
/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_2)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT2_IrqUnit2(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT2_IrqUnit2)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_2] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_2]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = ((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT2, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_2) */
/***************************************************************************************************************/

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_3)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT1_IrqUnit3(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT1_IrqUnit3)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_3] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_3]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = ((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT1, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_3) */
/****************************************************************************************************/
/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_TX_INSTANCE_3)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT1) || (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_VOID))
FUNC(void, CDD_FSI_TX_ISR_CODE)
CddFsiTx_FSIINT2_IrqUnit3(void)
#elif (CDD_FSI_TX_ISR_TYPE == CDD_FSI_TX_ISR_CAT2)
ISR(CddFsiTx_FSIINT2_IrqUnit3)
#endif
{
    Cdd_FsiTx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiTxIntFlagNum;
    uint32                   intStatusRegAddr;

    /* Check if, Index is invalid */
    if (Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_3] != CDD_FSI_TX_INVALID_INDEX)
    {
        hwUnitObj          = &Cdd_FsiTx_DrvObj.hwUnitObj[Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HWUNIT_3]];
        intStatusRegAddr   = hwUnitObj->hwUnitCfg.baseAddr | CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET;
        cddFsiTxIntFlagNum = ((HW_RD_REG16(intStatusRegAddr) & CDD_FSI_TX_INT_STATUS_MASK));
        CddFsiTx_IrqTx(hwUnitObj, CDD_FSI_TX_INT2, cddFsiTxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_TX_INSTANCE_3) */
/**********************************************************************************************************/

#define CDD_FSITX_STOP_SEC_ISR_CODE
#include "Cdd_FsiTx_MemMap.h"
/*****************************************************************************************************/
