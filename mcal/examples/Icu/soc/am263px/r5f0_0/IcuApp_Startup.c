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
 *  \file     IcuApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "IcuApp_Startup.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                              Macros & Typedefs                             */
/* ========================================================================== */
#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

/*	None	*/

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void IcuApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    /*	timer initialization	*/
    AppUtils_TimerInit();
}

void Icu_InterruptConfig(void)
{
    vimInit();
    Vim_IntCfg intCfg;
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.priority = VIM_PRIORITY_15;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_22;  // using for intrxbar_22
    intCfg.handler  = Icu_ch0Notify;
    vimRegisterInterrupt(&intCfg);
}

/*
 This is required by ecap to hit the ISR
*/
static void SOC_xbarSelectInterruptXBarInputSource(uint32 base, uint8 out, uint32 group0_mask, uint32 group1_mask,
                                                   uint32 group2_mask, uint32 group3_mask, uint32 group4_mask,
                                                   uint32 group5_mask, uint32 group6_mask)
{
    // TBD: 32 bit field required?
    HW_WR_REG32(base + out * CSL_CONTROLSS_INTXBAR_STEP + CSL_CONTROLSS_INTXBAR_INTXBAR0_G0,
                group0_mask & CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(base + out * CSL_CONTROLSS_INTXBAR_STEP + CSL_CONTROLSS_INTXBAR_INTXBAR0_G1,
                group1_mask & CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_MASK);
    HW_WR_REG32(base + out * CSL_CONTROLSS_INTXBAR_STEP + CSL_CONTROLSS_INTXBAR_INTXBAR0_G2,
                group2_mask & CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_MASK);
    HW_WR_REG32(base + out * CSL_CONTROLSS_INTXBAR_STEP + CSL_CONTROLSS_INTXBAR_INTXBAR0_G3,
                group3_mask & CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_MASK);
    HW_WR_REG32(base + out * CSL_CONTROLSS_INTXBAR_STEP + CSL_CONTROLSS_INTXBAR_INTXBAR0_G4,
                group4_mask & CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_MASK);
    HW_WR_REG32(base + out * CSL_CONTROLSS_INTXBAR_STEP + CSL_CONTROLSS_INTXBAR_INTXBAR0_G5,
                group5_mask & CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_MASK);
    HW_WR_REG32(base + out * CSL_CONTROLSS_INTXBAR_STEP + CSL_CONTROLSS_INTXBAR_INTXBAR0_G6,
                group6_mask & CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_MASK);
}

static void SOC_controlModuleLockMMR(uint32 domainId, uint32 partition)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    if (partition == CONTROLSS_CTRL_PARTITION0)
    {
        /*Lock CONTROLSS_CTRL*/
        baseAddr = (uint32)CSL_CONTROLSS_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, TEST_KICK_LOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, TEST_KICK_LOCK_VAL); /* KICK 1 */
    }

    return;
}

static void SOC_controlModuleUnlockMMR(uint32 domainId, uint32 partition)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    if (partition == CONTROLSS_CTRL_PARTITION0)
    {
        /*Unlock CONTROLSS_CTRL*/
        baseAddr = (uint32)CSL_CONTROLSS_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, TEST_KICK0_UNLOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, TEST_KICK1_UNLOCK_VAL); /* KICK 1 */
    }

    return;
}

static void SOC_setEpwmTbClk(uint32 epwmInstance, uint32 enable)
{
    if (epwmInstance < CSL_ETPWM_PER_CNT)
    {
        /* Time base clock enable register belongs to partition 1 of the CTRL MMR */

        /* Unlock CONTROLSS_CTRL registers */
        SOC_controlModuleUnlockMMR(0, CONTROLSS_CTRL_PARTITION0);

        if (TRUE == enable)
        {
            /* Enable Time base clock in CTRL MMR */
            HW_WR_REG32(CSL_CONTROLSS_CTRL_U_BASE + CSL_CONTROLSS_CTRL_EPWM_CLKSYNC,
                        ((HW_RD_REG32(CSL_CONTROLSS_CTRL_U_BASE + CSL_CONTROLSS_CTRL_EPWM_CLKSYNC) &
                          CSL_CONTROLSS_CTRL_EPWM_CLKSYNC_BIT_MASK) |
                         (1 << epwmInstance)));
        }
        else
        {
            /* Disable Time base clock in CTRL MMR */
            HW_WR_REG32(CSL_CONTROLSS_CTRL_U_BASE + CSL_CONTROLSS_CTRL_EPWM_CLKSYNC,
                        ((HW_RD_REG32(CSL_CONTROLSS_CTRL_U_BASE + CSL_CONTROLSS_CTRL_EPWM_CLKSYNC) &
                          CSL_CONTROLSS_CTRL_EPWM_CLKSYNC_BIT_MASK) &
                         ~(1 << epwmInstance)));
        }

        /* Lock CONTROLSS_CTRL registers */
        SOC_controlModuleLockMMR(0, CONTROLSS_CTRL_PARTITION0);
    }
}

static void SOC_setEpwmGroup(uint32 epwmInstance, uint32 group)
{
    uint32 baseAddr = CSL_CONTROLSS_CTRL_U_BASE + CSL_CONTROLSS_CTRL_EPWM_STATICXBAR_SEL0;
    uint32 mask, shift;

    /* Unlock CONTROLSS_CTRL registers */
    SOC_controlModuleUnlockMMR(0, CONTROLSS_CTRL_PARTITION0);

    /* Choose the correct base address depending on which ePWM instance is selected*/
    if (epwmInstance > 15)
    {
        baseAddr     = baseAddr + 0x4;
        epwmInstance = epwmInstance - 16;
    }

    shift = (epwmInstance << 1);
    /* Create the mask to be written to register */
    mask = (0x3 << shift);

    /* Configure the group for the ePWM instance */
    HW_WR_REG32(baseAddr, ((HW_RD_REG32(baseAddr) & ~mask) | (group << shift)));

    /* Lock CONTROLSS_CTRL registers */
    SOC_controlModuleLockMMR(0, CONTROLSS_CTRL_PARTITION0);
}

void SOC_xbarSelectInputXBarInputSource(uint32 base, uint8 out, uint8 group_select, uint8 group0_muxctl,
                                        uint8 group1_muxctl)
{
    HW_WR_REG32(base + CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL + (out * CSL_CONTROLSS_INPUTXBAR_STEP),
                group_select & CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL_GSEL_MASK);
    HW_WR_REG32(base + CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0 + (out * CSL_CONTROLSS_INPUTXBAR_STEP),
                group0_muxctl & CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G0_SEL_MASK);
    HW_WR_REG32(base + CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1 + (out * CSL_CONTROLSS_INPUTXBAR_STEP),
                group1_muxctl & CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_G1_SEL_MASK);
}

void Uart_Delay(uint32 Delay)
{
    for (Delay = 0; Delay < 5000; Delay++)
    {
        ;
    }
}

void Icu_App_Pwm_Init(void)
{
    Pwm_Init(&Pwm_Config);
}

void Icu_App_PlatformInit(void)
{
#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&Mcu_Config);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&Port_Config);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    SOC_setEpwmTbClk(9, TRUE);
    SOC_setEpwmGroup(9, 0);

    Enable_Uart();

    /* Delay for UART to settle up */
    Uart_Delay(5000);

    SOC_xbarSelectInputXBarInputSource(CSL_CONTROLSS_INPUTXBAR_U_BASE, 0, 0, INPUT_XBAR_GPIO61, 0);
    SOC_xbarSelectInterruptXBarInputSource(CSL_CONTROLSS_INTXBAR_U_BASE, 22, 0, 0, 0, 0, 0, (INT_XBAR_ECAP0_INT), 0);
}
