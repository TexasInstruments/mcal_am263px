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
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "trace.h"

#include "AppPimc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define LOWER_REFERENCE 0U
#define UPPER_REFERENCE 3300U

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Adc_ValueGroupType Adc_AppBuffer[ADC_MAX_GROUP][ADC_APP_BUF_SIZE_WORD];
extern Adc_ValueGroupType Adc_AppReadBuffer[ADC_MAX_GROUP][ADC_APP_READ_BUF_SIZE_WORD];

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) Mcu_Config;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void        AdcApp_interruptConfig(void);
static void AdcApp_PlatformInit(void);
extern void Pmic_Enable(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void AdcApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AdcApp_PlatformInit();
    AppUtils_TimerInit();
}

void AdcApp_TimerDeinit(void)
{
    AppUtils_TimerDeinit();
}

static void AdcApp_PlatformInit(void)
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

    Enable_Uart();

    /* Set up Pmic for Adc AM263P CC Board*/
    Pmic_Enable();

    return;
}

void AdcApp_interruptConfig(void)
{
    vimInit();

    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_1;
    intCfg.handler  = Adc_ADCINT1_IrqUnit1;
    intCfg.priority = VIM_PRIORITY_15;
    vimRegisterInterrupt(&intCfg);

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_2;
    intCfg.handler  = Adc_ADCINT2_IrqUnit1;
    intCfg.priority = VIM_PRIORITY_14;
    vimRegisterInterrupt(&intCfg);

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_3;
    intCfg.handler  = Adc_ADCINT3_IrqUnit1;
    intCfg.priority = VIM_PRIORITY_13;
    vimRegisterInterrupt(&intCfg);

    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_4;
    intCfg.handler  = Adc_ADCINT4_IrqUnit1;
    intCfg.priority = VIM_PRIORITY_12;
    vimRegisterInterrupt(&intCfg);

#if (STD_ON == ADC_DMA_MODE)
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTAGGR;
    intCfg.handler  = CDD_EDMA_lld_transferCompletionMasterIsrFxn;
    intCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&intCfg);
#endif

    return;
}

/* ===============================================================================================*/
/*                          Function Definitions  to Initialize the ADC Module.                   */
/* ===============================================================================================*/

#if (STD_ON == ADC_READ_TEMPERATURE_API)
void AdcTempTest(AdcApp_Obj *appObj, Adc_GroupType Group)
{ /*do nothing*/
}
#endif

void AdcApp_printChannelResult(uint32 grpIdx, const Adc_GroupConfigType *grpCfg, const AdcApp_Obj *appObj)
{
    uint32                    chIdx;
    const Adc_ValueGroupType *tempResultPtr;
    uint32                    adcInMv;

    GT_0trace(appObj->traceMask, GT_INFO1, " Channel\t\tADC Value\tVolt\r\n");
    GT_0trace(appObj->traceMask, GT_INFO1, " ----------------------------------------------------\r\n");

    for (chIdx = 0U; chIdx < grpCfg->numChannels; chIdx++)
    {
        tempResultPtr = &Adc_AppReadBuffer[grpIdx][chIdx];
        adcInMv       = ((*tempResultPtr) * (UPPER_REFERENCE - LOWER_REFERENCE)) / (1 << ADC_DEF_CHANNEL_RESOLUTION);

        GT_3trace(appObj->traceMask, GT_INFO1, " %-4d\t\t0x%08x\t%04dmV\r\n", chIdx, *tempResultPtr, adcInMv);
    }
}

void Adc_Print_applyvoltage(AdcApp_Obj *appObj)
{
    GT_0trace(appObj->traceMask, GT_INFO,
              "Apply different voltages (between 0 - 3.3 volts) to the Six ADC channels\r\n");
}
