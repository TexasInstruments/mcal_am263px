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

/* Protection against multiple inclusion */
#ifndef PWMAPP_STARTUP_H_
#define PWMAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "sys_common.h"
#include "hal_stdtypes.h"
#include "Pwm_Irq.h"
#include "Pwm_Priv.h"
#include "EcuM_Cbk.h"
#include "Pwm_Cfg.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"
#include "Os.h"
#include "trace.h"
#include "sys_common.h"
#include "sys_vim.h"
#include "assert.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME      "PWM_APP"
#define PWM_CHANNEL_1 0U
#define PWM_CHANNEL_2 1U
#define PWM_CHANNEL_3 2U
#define PWM_CHANNEL   (PWM_CHANNEL_1)

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
extern volatile uint32 Pwm_App_NotifyCnt;
#endif
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void   PwmApp_Startup(void);
void   Pwm_InterruptConfig(void);
void   Pwm_InterruptDisable(void);
void   Pwm_AppGetTestOption(void);
void   Pwm_PrintCurrentConfig(Pwm_ChannelType channel);
void   Pwm_App_PlatformInit(void);
void   Example_Pwminit(void);
void   PwmApp_Stop(void);
uint32 Example_PwmCalperiod(uint32 inputfreq);
#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
void Pwm_Notification_Channel1(void);
void Pwm_Notification_Channel2(void);
void Pwm_Notification_Channel3(void);
// void Pwm_Notification_Channel4(void);
void Pwm_Example_DisableNotification(void);
#endif

#endif
