/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2026 Texas Instruments Incorporated
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
 *  \file     Mcu_Xbar.c
 *
 */

/* ===========================================================================*/
/*                             Include Files                                  */
/* ===========================================================================*/

#include "Mcu_Xbar.h"
#include "Mcu_XbarOutput.h"
#include "Mcu_XbarPwm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

void MCU_xbarSelectInterruptXBarInputSource(uint32 base, uint32 out, const uint32 group_mask[MCU_INT_XBAR_NUM_GROUPS])
{
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0,
                group_mask[0U] & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G1,
                group_mask[1U] & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G2,
                group_mask[2U] & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G3,
                group_mask[3U] & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G4,
                group_mask[4U] & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G5,
                group_mask[5U] & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_MASK);
    HW_WR_REG32(base + (out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G6,
                group_mask[6U] & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_MASK);
}

void MCU_xbarSelectInterruptXBarInputSourceExtended(uint32 base, uint32 out,
                                                    const uint32 group_mask[MCU_INT_XBAR_NUM_GROUPS],
                                                    uint32 group7_mask, uint32 group8_mask, uint32 group9_mask)
{
    MCU_xbarSelectInterruptXBarInputSource(base, out, group_mask);
    HW_WR_REG32(base + (uint32)(out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + (uint32)MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G7,
                (uint32)(group7_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G7_SEL_MASK));
    HW_WR_REG32(base + (uint32)(out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + (uint32)MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G8,
                (uint32)(group8_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G8_SEL_MASK));
    HW_WR_REG32(base + (uint32)(out * MCU_CSL_CONTROLSS_INTXBAR_STEP) + (uint32)MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G9,
                (uint32)(group9_mask & MCU_CSL_CONTROLSS_INTXBAR_INTXBAR0_G9_SEL_MASK));
}

void MCU_xbarSelectInputXBarInputSource(uint32 base, uint32 out, uint32 group_select, uint32 group0_mask,
                                        uint32 group1_mask)
{
    HW_WR_REG32(
        (base + (uint32)MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL) + (uint32)(out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
        (uint32)(group_select & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL_GSEL_MASK));
    HW_WR_REG32(
        (base + (uint32)MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0) + (uint32)(out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
        group0_mask & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(
        (base + (uint32)MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1) + (uint32)(out * MCU_CSL_CONTROLSS_INPUTXBAR_STEP),
        (uint32)(group1_mask & MCU_CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1_SEL_MASK));
}

void MCU_xbarSelectGpioIntrXbarInputSource(uint32 base, uint32 out, uint32 mux_control)
{
    HW_WR_REG32(
        base + MCU_CSL_GPIO_INTR_XBAR_MUXCNTL(out),
        (MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_INT_ENABLE_MASK) | (mux_control & MCU_CSL_GPIO_INTR_XBAR_MUXCNTL_ENABLE_MASK));
}

uint32 MCU_xbarGetOutputXBarOutputSignalStatus(void)
{
    return (HW_RD_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_STATUS) &
            MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_STATUS_STS_MASK);
}

void MCU_xbarInvertOutputXBarOutputSignalBeforeLatch(uint32 invert)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGINVERT,
                invert & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGINVERT_INVERT_MASK);
}

uint32 MCU_xbarGetOutputXBarOutputSignalLatchedFlag(void)
{
    return (HW_RD_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAG));
}

void MCU_xbarClearOutputXBarOutputSignalLatchedFlag(uint32 clr)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAG_CLR, clr);
}

void MCU_xbarForceOutputXBarOutputSignalLatchedFlag(uint32 force)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGFORCE,
                force & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_FLAGFORCE_FRC_MASK);
}

void MCU_xbarSelectLatchOutputXBarOutputSignal(uint32 latchselect)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLATCH,
                latchselect & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLATCH_LATCHSEL_MASK);
}

void MCU_xbarSelectStretchedPulseOutputXBarOutputSignal(uint32 stretchselect)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTSTRETCH,
                stretchselect & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTSTRETCH_STRETCHSEL_MASK);
}

void MCU_xbarSelectStretchedPulseLengthOutputXBarOutputSignal(uint32 lengthselect)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLENGTH,
                lengthselect & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTLENGTH_LENGTHSEL_MASK);
}

void MCU_xbarInvertOutputXBarOutputSignal(uint32 invertout)
{
    HW_WR_REG32(MCU_OUTPUT_XBAR_BASE + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTINVERT,
                invertout & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR_OUTINVERT_OUTINVERT_MASK);
}

void MCU_xbarSelectOutputXBarInputSource(uint32 out, const uint32 group_mask[MCU_OUTPUT_XBAR_NUM_GROUPS])
{
    uint32 baseAddr = MCU_OUTPUT_XBAR_BASE + (out * MCU_CSL_CONTROLSS_OUTPUTXBAR_STEP);

    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0,
                group_mask[0U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G1,
                group_mask[1U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G1_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G2,
                group_mask[2U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G2_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G3,
                group_mask[3U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G3_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G4,
                group_mask[4U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G4_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G5,
                group_mask[5U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G5_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G6,
                group_mask[6U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G6_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G7,
                group_mask[7U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G7_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G8,
                group_mask[8U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G8_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G9,
                group_mask[9U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G9_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G10,
                group_mask[10U] & MCU_CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G10_SEL_MASK);
}

uint32 MCU_xbarGetPWMXBarOutputSignalStatus(void)
{
    return (HW_RD_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_STATUS) &
            MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_STATUS_STS_MASK);
}

void MCU_xbarInvertPWMXBarOutputSignalBeforeLatch(uint32 invert_mask)
{
    HW_WR_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAGINVERT,
                invert_mask & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAGINVERT_INVERT_MASK);
}

uint32 MCU_xbarGetPWMXBarOutputSignalLatchedFlag(void)
{
    return (HW_RD_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAG));
}

void MCU_xbarClearPWMXBarOutputSignalLatchedFlag(uint32 clr)
{
    HW_WR_REG32(MCU_PWM_XBAR_BASE + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR_FLAG_CLR, clr);
}

void MCU_xbarSelectPWMXBarInputSource(uint32 out, const uint32 group_mask[MCU_PWM_XBAR_NUM_GROUPS])
{
    uint32 baseAddr = MCU_PWM_XBAR_BASE + (out * MCU_CSL_CONTROLSS_PWMXBAR_STEP);

    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0,
                group_mask[0U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G1,
                group_mask[1U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G1_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G2,
                group_mask[2U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G2_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G3,
                group_mask[3U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G3_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G4,
                group_mask[4U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G4_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G5,
                group_mask[5U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G5_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G6,
                group_mask[6U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G6_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G7,
                group_mask[7U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G7_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G8,
                group_mask[8U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G8_SEL_MASK);
    HW_WR_REG32(baseAddr + MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G9,
                group_mask[9U] & MCU_CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G9_SEL_MASK);
}

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
