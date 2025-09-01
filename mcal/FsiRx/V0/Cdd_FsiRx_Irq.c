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
 *  \file     Cdd_FsiRx_Irq.c
 *
 *  \brief    This file contains the ISR implementation of CDD FSI RX driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_FsiRx.h"
#include "Cdd_FsiRx_Irq.h"
#include "Cdd_FsiRx_Cfg.h"
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

static Cdd_FsiRx_HwUnitObjType *CddFsiRx_GetHwUnitObj(Cdd_FsiRx_HWUnitType HwUnitId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern VAR(CddFsiRx_DriverObjType, CDD_FSIRX_VAR_CLEARED) Cdd_FsiRx_DrvObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CDD_FSIRX_START_SEC_ISR_CODE
#include "Cdd_FsiRx_MemMap.h"

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_0)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit0(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit0)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_0);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_0) */

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_0)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit0(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit0)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_0);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_0) */

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_1)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit1(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit1)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_1);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_1) */

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_1)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit1(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit1)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_1);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_1) */

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_2)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit2(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit2)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_2);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_2) */

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_2)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit2(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit2)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_2);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_2) */

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_3)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT1_IrqUnit3(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT1_IrqUnit3)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_3);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_3) */

/* Design :  */
/* Requirements : */
#if defined(CDD_FSI_RX_INSTANCE_3)
MCAL_INTERRUPT_ATTRIBUTE
#if ((CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT1) || (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_VOID))
FUNC(void, CDD_FSI_RX_ISR_CODE)
CddFsiRx_FSIINT2_IrqUnit3(void)
#elif (CDD_FSI_RX_ISR_TYPE == CDD_FSI_RX_ISR_CAT2)
ISR(CddFsiRx_FSIINT2_IrqUnit3)
#endif
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj;
    uint16                   cddFsiRxIntFlagNum;
    uint32                   RxintStatusRegAddr;

    hwUnitObj = CddFsiRx_GetHwUnitObj(CDD_FSI_RX_HWUNIT_3);
    if (hwUnitObj != NULL_PTR)
    {
        RxintStatusRegAddr = hwUnitObj->hwUnitCfg.baseAddr | CSL_CDD_FSI_RX_CFG_RX_EVT_STS_ALT1;
        cddFsiRxIntFlagNum = (HW_RD_REG16(RxintStatusRegAddr) & CDD_FSI_RX_EVTMASK);
        CddFsiRx_IrqRx(hwUnitObj, cddFsiRxIntFlagNum);
    }
}
#endif /* #if defined (CDD_FSI_RX_INSTANCE_3) */

static Cdd_FsiRx_HwUnitObjType *CddFsiRx_GetHwUnitObj(Cdd_FsiRx_HWUnitType HwUnitId)
{
    Cdd_FsiRx_HwUnitObjType *hwUnitObj = (Cdd_FsiRx_HwUnitObjType *)NULL_PTR;

    for (uint8 HwUnitIdx = 0U; HwUnitIdx < Cdd_FsiRx_DrvObj.maxHwUnit; HwUnitIdx++)
    {
        if (Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitIdx].hwUnitCfg.hwUnitId == HwUnitId)
        {
            hwUnitObj = &Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitIdx];
            break;
        }
    }

    return hwUnitObj;
}

#define CDD_FSIRX_STOP_SEC_ISR_CODE
#include "Cdd_FsiRx_MemMap.h"
