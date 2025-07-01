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
 *  \file     PwmApp_Startup.c
 *
 *  \brief    This file contains the  interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "PwmApp.h"
#include "PwmApp_Startup.h"
uint8 MainFunc_Execution;

void StartCyclecount()
{
}

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
volatile uint32 Pwm_App_NotifyCnt = 0;
#endif

#define ARRAYSIZE(x)  (sizeof((x)) / sizeof(x[0]))
#define PWM_SYS_CLOCK (200000000)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

sint32 TestState      = TRUE;
sint32 notifyRecvFlag = TRUE;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void PwmApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();

    Pwm_InterruptConfig();
}

void Pwm_InterruptConfig(void)
{
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
    uint32 index;
    vimInit();

    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    for (index = 0; index < PwmChannelConfigSet_0.NumberOfChannels_u8; index++)
    {
        if (PwmChannelConfigSet_0.ChannelConfig_at[index].channel == PWM_CHANNEL_1)
        {
            intCfg.priority = VIM_PRIORITY_11;
            intCfg.intNum   = MSS_ETPWMA_INT0;
            intCfg.handler  = Pwm_Ch1Notify;
            vimRegisterInterrupt(&intCfg);
        }
        else if (PwmChannelConfigSet_0.ChannelConfig_at[index].channel == PWM_CHANNEL_2)
        {
            intCfg.priority = VIM_PRIORITY_12;
            intCfg.intNum   = MSS_ETPWMB_INT0;
            intCfg.handler  = Pwm_Ch2Notify;
            vimRegisterInterrupt(&intCfg);
        }
        else if (PwmChannelConfigSet_0.ChannelConfig_at[index].channel == PWM_CHANNEL_3)
        {
            intCfg.priority = VIM_PRIORITY_13;
            intCfg.intNum   = MSS_ETPWMC_INT0;
            intCfg.handler  = Pwm_Ch3Notify;
            vimRegisterInterrupt(&intCfg);
        }
    }
#endif
}

void Pwm_InterruptDisable(void)
{
    uint32 index;
    for (index = 0; index < PwmChannelConfigSet_0.NumberOfChannels_u8; index++)
    {
        if (PwmChannelConfigSet_0.ChannelConfig_at[index].channel == PWM_CHANNEL_1)
        {
            vimDisableInterrupt(MSS_ETPWMA_INT0);
        }
        else if (PwmChannelConfigSet_0.ChannelConfig_at[index].channel == PWM_CHANNEL_2)
        {
            vimDisableInterrupt(MSS_ETPWMB_INT0);
        }
        else if (PwmChannelConfigSet_0.ChannelConfig_at[index].channel == PWM_CHANNEL_3)
        {
            vimDisableInterrupt(MSS_ETPWMC_INT0);
        }
    }
}

void Pwm_AppGetTestOption(void)
{
    AppUtils_printf(" \n\r");
    AppUtils_printf("PWM App Test Option\n\r");
    AppUtils_printf("a. PWM Set Duty Cycle \n\r");
    AppUtils_printf("b. PWM Set Period and Duty Cycle\n\r");
    AppUtils_printf("c. PWM Set  Output Idle\n\r");
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    AppUtils_printf("d. PWM Enable Notification\n\r");
    AppUtils_printf("e. PWM Disable Notification\n\r");
#endif
    AppUtils_printf("f. PWM Deinit\n\r");
    AppUtils_printf("x. Exit\n\r");
}
void Pwm_PrintCurrentConfig(Pwm_ChannelType channel)
{
    uint8 i = 0;
    for (i = 0; i < PwmChannelConfigSet_0.NumberOfChannels_u8; i++)
    {
        if (channel == PwmChannelConfigSet_0.ChannelConfig_at[i].channel)
        {
            /* channel found */
            AppUtils_printf("Current configuration should be :\n\r");

            AppUtils_printf("Frequency = %dHz\n\r", PwmChannelConfigSet_0.ChannelConfig_at[i].settings.frequency_t);
            AppUtils_printf("Duty Cycle = %d%c\n\r",
                            (PwmChannelConfigSet_0.ChannelConfig_at[i].settings.Dutycycle_t * 100) / 32768, 37);
            break;
        }
    }
}

void Pwm_App_PlatformInit(void)
{
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    AppUtils_TimerInit();

    /* Set up the pinmux for UART tx */
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);

    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);
}

void Example_Pwminit(void)
{
#if (PWM_VARIANT_POST_BUILD == STD_ON)
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
    const Pwm_ConfigType *pCfgPtr = &PwmChannelConfigSet_0;
    Pwm_Init(pCfgPtr);
#else
    AppUtils_printf(APP_NAME ": Variant - Precompile Variant being used !!!\n\r");
    Pwm_Init(NULL_PTR);
#endif
    AppUtils_delay(1000U);
}

uint32 Example_PwmCalperiod(uint32 inputfreq)
{
    uint16 clkDiv    = 0;
    uint16 hspclkDiv = 0;
    uint32 prescalar = 0;
    uint32 period    = 0;
    // const Pwm_ConfigType *pCfgPtr = &PwmChannelConfigSet_0;
    hspclkDiv = (uint16)2U * (PwmChannelConfigSet_0.ChannelConfig_at[PWM_CHANNEL_1].hsPrescale) +
                (uint16)(PwmChannelConfigSet_0.ChannelConfig_at[PWM_CHANNEL_1].hsPrescale == (uint16)0U);
    clkDiv    = (uint16)1U << (PwmChannelConfigSet_0.ChannelConfig_at[PWM_CHANNEL_1].prescale);
    prescalar = (uint32)hspclkDiv * clkDiv;

    period = (PwmChannelConfigSet_0.pwmClkHz / prescalar) / inputfreq;
    return period;
}

void Pwm_Notification_Channel1(void)
{
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
    Pwm_App_NotifyCnt++;
#endif
}

void Pwm_Notification_Channel2(void)
{
}

void Pwm_Notification_Channel3(void)
{
}

void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    MainFunc_Execution = 1;
}

void Pwm_Example_DisableNotification(void)
{
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
    notifyRecvFlag = 0U; /* Set it to channel number */
    if (Pwm_App_NotifyCnt > 100)
    {
        Pwm_DisableNotification(PWM_CHANNEL);
    }
    else
    {
        /*do nothing*/
    }
#endif
}

void PwmApp_Stop(void)
{
    AppUtils_TimerDeinit();
}
