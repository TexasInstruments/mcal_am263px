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
 *  \file     AdcApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "AdcApp_Startup.h"
#include "AdcApp.h"
#include "sys_vim.h"
#include "Adc.h"
#include "Adc_Irq.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define LOWER_REFERENCE 0U
#define UPPER_REFERENCE 1800U

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration_0;
#endif

extern Adc_ValueGroupType Adc_AppBuffer[ADC_MAX_GROUP][ADC_APP_BUF_SIZE_WORD];
extern Adc_ValueGroupType Adc_AppReadBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void AdcApp_platformInit(void);
void AdcApp_interruptConfig(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void AdcApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_TimerInit();
    AdcApp_platformInit();
}

void AdcApp_platformInit(void)
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

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

#if (STD_ON == PORT_SET_PIN_MODE_API)
    /* Set up the pinmux for UART tx */
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);
#endif /*#if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/

    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);

    return;
}

void AdcApp_interruptConfig()
{
    vimInit();

    Vim_IntCfg Adc_IntCfg;
    Adc_IntCfg.map      = VIM_INTTYPE_IRQ;
    Adc_IntCfg.type     = VIM_INTTRIGTYPE_PULSE;
    Adc_IntCfg.intNum   = MSS_GPADC_IFM_DONE;
    Adc_IntCfg.handler  = Adc_IFMDoneISR;
    Adc_IntCfg.priority = VIM_PRIORITY_12;
    vimRegisterInterrupt(&Adc_IntCfg);

    vimEnableInterrupt(MSS_GPADC_IFM_DONE);
}

void AdcApp_TimerDeinit(void)
{
    AppUtils_TimerDeinit();
}

#if (STD_ON == ADC_READ_TEMPERATURE_API)
void AdcTempTest(AdcApp_Obj *appObj, Adc_GroupType Group)
{
    uint8                 numAverages;
    Adc_TempSensValueType tempValues;
    numAverages = 5U;
    /*Adc Init and resultbuffer are already set */
    Adc_InitTemperatureRead();

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY_API)
    Adc_DisableGroupNotification(Group);
#endif

    Adc_ReadTemperature(Group, numAverages, &tempValues);

    GT_0trace(appObj->traceMask, GT_INFO1, " \r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " Read Temp Values\r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " -------------------\r\n");

    GT_1trace(appObj->traceMask, GT_INFO1, " Temperature Values Group %d Log:\r\n", Group);
    GT_0trace(appObj->traceMask, GT_INFO1, " ----------------\r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " Sensor\t\tHW_CH\t\tTemperature\r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " ----------------------------------------------------\r\n");

    GT_1trace(appObj->traceMask, GT_INFO1, " DSP\t\tADC_IN09\t%03ddeg\r\n", tempValues.DigDspTempValue);
    GT_1trace(appObj->traceMask, GT_INFO1, " HWA\t\tADC_IN10\t%03ddeg\r\n", tempValues.DigHwaTempValue);
    GT_1trace(appObj->traceMask, GT_INFO1, " R5F\t\tADC_IN11\t%03ddeg\r\n", tempValues.DigHsmTempValue);
}
#endif

void AdcApp_printChannelResult(uint32 grpIdx, const Adc_GroupConfigType *grpCfg, const AdcApp_Obj *appObj)
{
    uint32                    chIdx;
    const Adc_ValueGroupType *tempResultPtr;
    uint32                    adcInMv;

    GT_0trace(appObj->traceMask, GT_INFO1, " Channel\tHW_CH\t\tADC Value\tVolt\r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " ----------------------------------------------------\r\n");

    for (chIdx = 0U; chIdx < grpCfg->numChannels; chIdx++)
    {
        tempResultPtr = &Adc_AppReadBuffer[grpIdx][chIdx];
        adcInMv       = ((*tempResultPtr) * (UPPER_REFERENCE - LOWER_REFERENCE)) / (1 << ADC_DEF_CHANNEL_RESOLUTION);

        GT_4trace(appObj->traceMask, GT_INFO1, " %-4d\t\tADC_IN%-3d\t0x%08x\t%04dmV\r\n", chIdx,
                  grpCfg->hwChannelID[chIdx], *tempResultPtr, adcInMv);
    }
}

void Adc_Print_applyvoltage(AdcApp_Obj *appObj)
{
    GT_0trace(appObj->traceMask, GT_INFO,
              "Apply different voltages (between 0 - 1.8 volts) to the nine ADC channels\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 1 => J7-pin19\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 2 => J7-pin21\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 3 => J7-pin23\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 4 => J7-pin25\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 5 => J7-pin27\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 6 => J7-pin29\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 7 => J7-pin31\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 8 => J7-pin33\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 9 => J7-pin35\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 10 => DSP Temp Sensor\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 11 => HWA Temp Sensor\r\n");
    GT_0trace(appObj->traceMask, GT_INFO, "CHANNEL 12 => R5F Temp Sensor\r\n");
}
