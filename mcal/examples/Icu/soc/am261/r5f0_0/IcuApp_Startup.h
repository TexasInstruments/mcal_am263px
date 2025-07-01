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

/* Protection against multiple inclusion */
#ifndef ICUAPP_STARTUP_H_
#define ICUAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "sys_common.h"
#include "cslr_controlss_inputxbar.h"
#include "hw_types.h"
#include "sys_vim.h"
#include "Icu_Irq.h"
#include "IcuApp.h"
#include "Mcu.h"
#include "Pwm.h"
#include "Icu.h"
#include "EcuM_Cbk.h"
#include "Port.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSL_ETPWM_PER_CNT         (10U)
#define CONTROLSS_CTRL_PARTITION0 (3)

#define CSL_CONTROLSS_CTRL_U_BASE                (0x502F0000UL)
#define CSL_CONTROLSS_CTRL_EPWM_CLKSYNC          (0x00000148U)
#define CSL_CONTROLSS_CTRL_EPWM_CLKSYNC_BIT_MASK (0xFFFFFFFFU)
#define CSL_CONTROLSS_CTRL_EPWM_STATICXBAR_SEL0  (0x00000138U)

#define CSL_CONTROLSS_CTRL_LOCK0_KICK0 (0x00001008U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1 (0x0000100CU)

#define TEST_KICK_LOCK_VAL    (0x00000000U)
#define TEST_KICK0_UNLOCK_VAL (0x01234567U)
#define TEST_KICK1_UNLOCK_VAL (0x0FEDCBA8U)

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */
void IcuApp_Startup(void);
void IcuApp_interruptConfig(uint32 channelId);
void Icu_InterruptConfig(void);
void Icu_App_PlatformInit(void);
void Icu_App_Pwm_Init(void);

#endif
