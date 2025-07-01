/*
 * Copyright (C) 2022 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include "hw_types.h"
#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

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

void ICU_ECAP_intrEnable(uint32 baseAddr, uint32 flag)
{
    uint32 temp_addr  = baseAddr + CSL_ECAP_ECEINT_ECFLG;
    uint32 value      = HW_RD_REG32(temp_addr);
    value            |= (flag);
    HW_WR_REG32(temp_addr, value);
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

void ICU_ECAP_captureInputSourceSelect(uint32 baseAddr, uint8 srcSelect)
{
    uint8  value     = 0;
    uint32 temp_addr = baseAddr + CSL_ECAP_ECCTL0;
    /* Write 0 to select the input select as ECAPxINPUT[0] */
    value = ((uint8)(srcSelect));
    HW_WR_REG16(temp_addr, value);
}

#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"
