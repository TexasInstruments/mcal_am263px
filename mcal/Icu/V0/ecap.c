/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file   ecap.c
 *
 *  \brief  Low lever APIs performing hardware register writes and reads for
 *          ECAP IP version 2.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "ecap.h"
#include "Platform_Types.h"

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void ICU_ECAP_captureLoadingEnable(uint32 baseAddr)
{
    uint32 temp_addr  = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    uint32 value      = HW_RD_REG32(temp_addr);
    value            |= CSL_ECAP_ECCTL1_ECCTL2_CAPLDEN_MASK;
    HW_WR_REG32(temp_addr, value);
}

void ICU_ECAP_captureLoadingDisable(uint32 baseAddr)
{
    uint32 temp_addr  = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    uint32 value      = HW_RD_REG32(temp_addr);
    value            &= (~CSL_ECAP_ECCTL1_ECCTL2_CAPLDEN_MASK);
    HW_WR_REG32(temp_addr, value);
}

void ICU_ECAP_cap1Reset(uint32 baseAddr)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_CAP1;
    HW_WR_REG32(temp_addr, 0);
}

void ICU_ECAP_cap2Reset(uint32 baseAddr)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_CAP2;
    HW_WR_REG32(temp_addr, 0);
}

void ICU_ECAP_cap3Reset(uint32 baseAddr)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_CAP3;
    HW_WR_REG32(temp_addr, 0);
}

void ICU_ECAP_cap4Reset(uint32 baseAddr)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_CAP4;
    HW_WR_REG32(temp_addr, 0);
}

void ICU_ECAP_prescaleConfig(uint32 baseAddr, uint32 prescale)
{
    uint32 temp_addr;

    if (prescale <= CSL_ECAP_ECCTL1_ECCTL2_PRESCALE_MAX)
    {
        temp_addr = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
        HW_WR_FIELD32(temp_addr, CSL_ECAP_ECCTL1_ECCTL2_PRESCALE, prescale);
    }
}

void ICU_ECAP_operatingModeSelect(uint32 baseAddr, uint32 modeSelect)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    HW_WR_FIELD32(temp_addr, CSL_ECAP_ECCTL1_ECCTL2_CAP_APWM, modeSelect);
}

uint32 ICU_ECAP_timeStampRead(uint32 baseAddr, uint32 capEvtFlag)
{
    return (HW_RD_REG32(baseAddr + capEvtFlag));
}

void ICU_ECAP_captureEvtPolarityConfig(uint32 baseAddr, uint32 capEvt1pol, uint32 capEvt2pol, uint32 capEvt3pol,
                                       uint32 capEvt4pol)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    uint32 value     = HW_RD_REG32(temp_addr);

    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CAP1POL_MASK;
    value |= ((capEvt1pol << CSL_ECAP_ECCTL1_ECCTL2_CAP1POL_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CAP1POL_MASK);
    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CAP2POL_MASK;
    value |= ((capEvt2pol << CSL_ECAP_ECCTL1_ECCTL2_CAP2POL_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CAP2POL_MASK);
    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CAP3POL_MASK;
    value |= ((capEvt3pol << CSL_ECAP_ECCTL1_ECCTL2_CAP3POL_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CAP3POL_MASK);
    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CAP4POL_MASK;
    value |= (uint32)((capEvt4pol << CSL_ECAP_ECCTL1_ECCTL2_CAP4POL_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CAP4POL_MASK);
    HW_WR_REG32(temp_addr, value);
}

void ICU_ECAP_captureEvtCntrRstConfig(uint32 baseAddr, uint32 counterRst1, uint32 counterRst2, uint32 counterRst3,
                                      uint32 counterRst4)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    uint32 value     = HW_RD_REG32(temp_addr);

    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CTRRST1_MASK;
    value |= (uint32)((counterRst1 << CSL_ECAP_ECCTL1_ECCTL2_CTRRST1_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CTRRST1_MASK);
    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CTRRST2_MASK;
    value |= (uint32)((counterRst2 << CSL_ECAP_ECCTL1_ECCTL2_CTRRST2_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CTRRST2_MASK);
    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CTRRST3_MASK;
    value |= (uint32)((counterRst3 << CSL_ECAP_ECCTL1_ECCTL2_CTRRST3_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CTRRST3_MASK);
    value &= ~CSL_ECAP_ECCTL1_ECCTL2_CTRRST4_MASK;
    value |= (uint32)((counterRst4 << CSL_ECAP_ECCTL1_ECCTL2_CTRRST4_SHIFT) & CSL_ECAP_ECCTL1_ECCTL2_CTRRST4_MASK);
    HW_WR_REG32(temp_addr, value);
}

void ICU_ECAP_continousModeConfig(uint32 baseAddr)
{
    uint32 temp_addr  = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    uint32 value      = HW_RD_REG32(temp_addr);
    value            &= ((~CSL_ECAP_ECCTL1_ECCTL2_CONT_ONESHT_MASK));
    HW_WR_REG32(temp_addr, value);
}

void ICU_ECAP_counterControl(uint32 baseAddr, uint32 flag)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    HW_WR_FIELD32(temp_addr, CSL_ECAP_ECCTL1_ECCTL2_TSCTRSTOP, flag);
}

void ICU_ECAP_syncInOutSelect(uint32 baseAddr, uint32 syncIn, uint32 syncOut)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECCTL1_ECCTL2;
    HW_WR_FIELD32(temp_addr, CSL_ECAP_ECCTL1_ECCTL2_SYNCI_EN, syncIn);
    HW_WR_FIELD32(temp_addr, CSL_ECAP_ECCTL1_ECCTL2_SYNCO_SEL, syncOut);
}

void ICU_ECAP_globalIntrClear(uint32 baseAddr)
{
    uint32 temp_addr  = baseAddr + CSL_ECAP_ECCLR_ECFRC;
    uint32 value      = HW_RD_REG32(temp_addr);
    value            |= ((uint32)CSL_ECAP_ECCLR_ECFRC_INT_MASK);
    HW_WR_REG32(temp_addr, value);
}

void ICU_ECAP_intrEnable(uint32 baseAddr, uint16 flag)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECEINT_ECFLG;
    HW_WR_REG16(temp_addr, (HW_RD_REG16(baseAddr + CSL_ECAP_ECEINT_ECFLG) | flag));
}

void ICU_ECAP_intrDisable(uint32 baseAddr, uint32 flag)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECEINT_ECFLG;
    uint32 value     = HW_RD_REG32(temp_addr);
    uint32 value32;
    value32 = (value & ~flag);
    HW_WR_REG32(temp_addr, value32);
}

uint32 ICU_ECAP_getIntrStatus(uint32 baseAddr, uint32 flag)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECEINT_ECFLG;
    uint32 value     = HW_RD_REG32(temp_addr);
    return (value & flag);
}

void ICU_ECAP_intrStatusClear(uint32 baseAddr, uint32 flag)
{
    uint32 temp_addr = baseAddr + CSL_ECAP_ECEINT_ECFLG;
    uint32 value     = HW_RD_REG32(temp_addr);
    temp_addr        = baseAddr + CSL_ECAP_ECCLR_ECFRC;
    value            = (value >> 16);
    HW_WR_REG16(temp_addr, (value & flag));
}

void ICU_ECAP_setEmulationMode(uint32 baseAddr, ECAP_EmulationMode mode)
{
    HW_WR_REG16(baseAddr + CSL_ECAP_ECCTL1_ECCTL2,
                ((HW_RD_REG16(baseAddr + CSL_ECAP_ECCTL1_ECCTL2) & (~CSL_ECAP_ECCTL1_FREE_SOFT_MASK)) |
                 ((uint16)mode << CSL_ECAP_ECCTL1_FREE_SOFT_SHIFT)));
}

void ICU_ECAP_selectQualPeriod(uint32 baseAddr, ECAP_QualPeriodSelect width)
{
    HW_WR_REG32(baseAddr + CSL_ECAP_ECCTL0, ((HW_RD_REG32(baseAddr + CSL_ECAP_ECCTL0) & ~CSL_ECAP_ECCTL0_QUALPRD_MASK) |
                                             ((uint32_t)width << CSL_ECAP_ECCTL0_QUALPRD_SHIFT)));
}
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"
