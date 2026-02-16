/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     PwmApp.c
 *
 *  \brief    This file contains the PWM test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PwmApp.h"

/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "assert.h"
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
#include "SchM_Pwm.h"
#include "SchM_Port.h"
#include "Det.h"
#include "Dem.h"
/*LDRA_ANALYSIS*/
#include "PwmApp_Startup.h"
#include "sys_vim.h"
/* For PRCM base addresses */
#include "soc.h"
#include "Pwm.h"
#include "PwmApp.h"

#define PWM_ARRAYSIZE(x)     (sizeof((x)) / sizeof((x)[0]))
#define PWM_APP_PERFORM_TEST (STD_ON)
#define PWM_APP_TEST         (STD_ON)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

typedef void (*PwmAppFxn_t)(void);

PwmAppFxn_t Pwm_App_FxnTbl[] = {&Pwm_App_MainTest};

uint32 Pwm_Performance_Result[30];
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined CLANG
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif

void Pwm_App_MainTest(void)
{
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
#endif

#if (STD_ON == PWM_SET_DUTY_CYCLE_API) || (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API) || \
    (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
    uint32 inputduty;
#endif

#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
    uint32 inputfreq;
    uint32 period;
#endif /*#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)*/

    AppUtils_printf(APP_NAME ": EPWM being used with Channel # %d!!! \n\r", PWM_CHANNEL);

    Example_Pwminit();

#if (STD_ON == PWM_SET_DUTY_CYCLE_API)
    /* Duty Cycle 80% */
    AppUtils_printf(" \n");
    AppUtils_printf(APP_NAME ": Changing the Duty cycle from to 50 to 80 percent \n\r");
    inputduty = 0x6666U;
    Pwm_SetDutyCycle(PWM_CHANNEL_1, inputduty);
    AppUtils_printf(APP_NAME ": This example waits for 30 seconds Please probe\n\r");
    AppUtils_delay(1000U);
#endif

#if (STD_ON == PWM_SET_DUTY_CYCLE_API)
    /* Duty Cycle 80% */
    AppUtils_printf(" \n");
    AppUtils_printf(APP_NAME ": Changing the Duty cycle to 100 Percent \n\r");
    inputduty = 0x8000U;
    Pwm_SetDutyCycle(PWM_CHANNEL_1, inputduty);
    inputduty = 0x1625U;
    AppUtils_printf(APP_NAME ": This example waits for 10 seconds Please probe\n\r");
    AppUtils_delay(1000U);
#endif

#if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
    /* Output to Idle */
    AppUtils_printf(" \n");
    AppUtils_printf(APP_NAME ": Setting Output to Idle state \n\r");
    Pwm_SetOutputToIdle(PWM_CHANNEL_1);
    inputduty = 0x2500U;
    AppUtils_printf(APP_NAME ": This example waits for 10 seconds Please probe\n\r");
    AppUtils_delay(1000U);
#endif

#if (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
    AppUtils_printf(" \n");
    AppUtils_printf(APP_NAME ": Changing Frequency from 1kHz to 10KHz and Duty Cycle to 50%%\n\r");

    inputfreq = 10000U;
    period    = Example_PwmCalperiod(inputfreq);

    AppUtils_printf(APP_NAME ": period is set to %d\n\r", period);
    inputduty = 0x4000U;
    Pwm_SetPeriodAndDuty(PWM_CHANNEL_1, period, inputduty);
#endif /*PWM_SET_PERIOD_AND_DUTY_API */

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
    Pwm_EnableNotification(PWM_CHANNEL, PWM_FALLING_EDGE);

    AppUtils_printf(APP_NAME ": This app again waits for 30 seconds please probe\n\r");

    /* Wait for ISR count */
#if (STD_ON == PWM_SET_DUTY_CYCLE_API) || (STD_ON == PWM_SET_PERIOD_AND_DUTY_API)
    if ((inputduty == PWM_DUTY_0_PERCENT) || (inputduty == PWM_DUTY_100_PERCENT))
    {
        AppUtils_delay(1000);
    }
    else
#endif /*PWM_SET_DUTY_CYCLE_API*/
    {
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        while (Pwm_App_NotifyCnt < (inputfreq * 30U))
            ; /*Multiplied with 30 for 30 seconds run */
#endif        /*#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)*/
    }
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
    AppUtils_printf(APP_NAME ": Pwm Isr Count: %u \n\r", Pwm_App_NotifyCnt);
#endif /*#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)*/
#endif /*PWM_NOTIFICATION_SUPPORTED*/

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
    /* Disable Notifications */
    Pwm_App_NotifyCnt = 0;
    AppUtils_printf(" \n");
    AppUtils_printf(APP_NAME ": Disabling Notifications for PWM channel\n\r");
    Pwm_DisableNotification(PWM_CHANNEL);
#endif

#if defined TEST_EHRPWM
    Example_PwmTest_EHPWM();
#endif

    AppUtils_printf("PWM Test Completed !!!\n\r");
    PwmApp_Stop();
}

int main(void)
{
    uint32 i = 0;

    PwmApp_Startup();

    /*Enable Domain clocks*/
    Pwm_App_PlatformInit();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\n\r");

#if (PWM_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
    memset(&versioninfo, 0, sizeof(versioninfo));
    /* Version Info Check*/
    Pwm_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n");
    AppUtils_printf(APP_NAME ": PWM MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf(APP_NAME ": Vendor ID           : %d\n\r", versioninfo.vendorID);
    AppUtils_printf(APP_NAME ": Module ID           : %d\n\r", versioninfo.moduleID);
    AppUtils_printf(APP_NAME ": SW Major Version    : %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf(APP_NAME ": SW Minor Version    : %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf(APP_NAME ": SW Patch Version    : %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n");
#endif

#if (PWM_APP_TEST == STD_ON)
    for (i = 0U; i < PWM_ARRAYSIZE(Pwm_App_FxnTbl); i++)
    {
        Pwm_App_FxnTbl[i]();
    }
#endif

    GT_1trace(McalAppTrace, GT_INFO, " PWM Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        GT_0trace(McalAppTrace, GT_ERR, " PWM Stack/section corruption!!!\n\r");
    }
    else
    {
        AppUtils_printf("All tests have Passed !!!\n\r");
        AppUtils_printf(APP_NAME ": Sample Application - DONE !!!\n\r");
    }

    while (1)
    {
        AppUtils_delay(10000U);
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
        Pwm_Example_DisableNotification();
#endif /*#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)*/
    }
    return (0);
}

/*EoF*/
