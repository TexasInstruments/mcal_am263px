/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     WdgApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "WdgApp.h"
#include "WdgApp_Startup.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
extern void                SOC_controlModuleUnlockMMR(uint32 domainId, uint32 partition);
extern void                SOC_controlModuleLockMMR(uint32 domainId, uint32 partition);
static void                Wdg_App_platformInit(void);
extern Wdg_App_TestParams *testPrms;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void                       Wdg_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();
    Wdg_App_platformInit();
}

void TimerDeinit()
{
    AppUtils_TimerDeinit();
}
MCAL_INTERRUPT_ATTRIBUTE
void WDT_Isr()
{
    HW_WR_REG32(0x52100090, WDG_CTL_DISABLED);

    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, MSS_RCM_PARTITION0);

    HW_WR_REG32(0x53208014, 0x7); /*MSS_RCM_R5SS0_RST_CAUSE_CLR-Clear bit for rst cause register*/

    HW_WR_REG32(0x53208024, 0x7000707); /* MSS_RCM_R5SS0_RST_WFICHECK*/

    HW_WR_REG32(0x53208044, 0x7000707); /*MSS_RCM_R5SS1_RST_WFICHECK*/

    HW_WR_REG32(0x5320851C, 0x7); /*MSS_RCM_R5SS1_CORE0_LRST_CTRL- Software needs to ensure the
                                     state of the Device/IP before configuring*/

    HW_WR_REG32(0x53208518, 0x7); /*MSS_RCM_R5SS0_CORE0_LRST_CTRL*/
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, MSS_RCM_PARTITION0);
}

void WDTApp_interruptConfig()
{
    vimInit();
    Vim_IntCfg intCfg;
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = RTI_WDT0_NMI;
    intCfg.handler  = WDT_Isr;
    intCfg.priority = VIM_PRIORITY_10;
    vimRegisterInterrupt(&intCfg);

    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = RTI1_INT0;
    intCfg.handler  = Gpt_Ch4Isr;
    intCfg.priority = VIM_PRIORITY_11;
    vimRegisterInterrupt(&intCfg);

    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = RTI1_INT1;
    intCfg.handler  = Gpt_Ch5Isr;
    intCfg.priority = VIM_PRIORITY_12;
    vimRegisterInterrupt(&intCfg);
}

static void Wdg_App_platformInit(void)
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 uart_tx_pin, uart_rx_pin;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

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

#if (STD_ON == PORT_SET_PIN_MODE_API)
    uart_tx_pin = 13;
    uart_rx_pin = 14;

    /* Set up the pinmux for UART tx */
    Port_SetPinMode(uart_tx_pin, PORT_PIN_MODE_LIN0);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(uart_rx_pin, PORT_PIN_MODE_LIN0);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(uart_rx_pin, PORT_PIN_IN);
#endif /*    #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
    Enable_Uart();

    return;
}

Mcu_ResetType GetResetReason()
{
    Mcu_ResetType mcu_reset_reason = MCU_RESET_UNDEFINED;
    uint32        Reset_Reason;
    if (Wdg_AppTestPrms[0].wdgConfig->fastModeCfg.reaction != WDG_GENERATE_NMI)
    {
        mcu_reset_reason = Mcu_GetResetReason();
    }
    else
    {
        Reset_Reason = HW_RD_REG32(0x53208010);
        if (Reset_Reason & 0x20)
        {
            mcu_reset_reason = MCU_WARM_RESET_WDT0;
        }
        HW_WR_REG32(0x53208014, 0x7);
    }
    return mcu_reset_reason;
}
