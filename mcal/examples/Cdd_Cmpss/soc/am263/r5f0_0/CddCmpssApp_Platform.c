/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
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
 *  \file     CddCmpssApp_Platform.c
 *
 *  \brief    This file contains the platform configurations.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <CddCmpssApp.h>
#include <CddCmpssApp_Platform.h>

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

void CddCmpss_appPlatformInit(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();

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
}

void CddCmpss_appPlatformDeInit(void)
{ /* Nothing to do */
}

void CddCmpss_appConfigXbar(void)
{
    uint32 pwm_group_mask[MCU_PWM_XBAR_NUM_GROUPS];
    uint32 output_group_mask[MCU_OUTPUT_XBAR_NUM_GROUPS];

    /* Init all masks with none flag */
    for (uint32 i = 0U; i < MCU_PWM_XBAR_NUM_GROUPS; i++)
    {
        pwm_group_mask[i] = MCU_PWM_XBAR_GROUP_MASK_NONE;
    }
    for (uint32 i = 0U; i < MCU_OUTPUT_XBAR_NUM_GROUPS; i++)
    {
        output_group_mask[i] = MCU_OUTPUT_XBAR_GROUP_MASK_NONE;
    }

    /* EPWM XBAR - Config first and then select the mux */
    pwm_group_mask[0U] = CMPSS_APP_PWM_XBAR_GROUP0_MASK;
    MCU_xbarInvertPWMXBarOutputSignalBeforeLatch(0U);
    MCU_xbarSelectPWMXBarInputSource(CMPSS_APP_PWM_XBAR_OUT, pwm_group_mask);

    /* OUTPUT XBAR - Config first and then select the mux */
    output_group_mask[6U] = CMPSS_APP_OUTPUT_XBAR_GROUP6_MASK;
    MCU_xbarInvertOutputXBarOutputSignalBeforeLatch(0U);
    MCU_xbarInvertOutputXBarOutputSignal(0U);
    MCU_xbarSelectLatchOutputXBarOutputSignal(0U);
    MCU_xbarSelectStretchedPulseOutputXBarOutputSignal(0U);
    MCU_xbarSelectStretchedPulseLengthOutputXBarOutputSignal(0U);
    MCU_xbarSelectOutputXBarInputSource(CMPSS_APP_OUTPUT_XBAR_OUT, output_group_mask);
}
