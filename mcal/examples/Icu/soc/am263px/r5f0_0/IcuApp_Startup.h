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
#define CSL_ETPWM_PER_CNT         (32U)
#define CONTROLSS_CTRL_PARTITION0 (3)

#define CSL_CONTROLSS_CTRL_U_BASE                (0x502F0000UL)
#define CSL_CONTROLSS_CTRL_EPWM_CLKSYNC          (0x00000010U)
#define CSL_CONTROLSS_CTRL_EPWM_CLKSYNC_BIT_MASK (0xFFFFFFFFU)
#define CSL_CONTROLSS_CTRL_EPWM_STATICXBAR_SEL0  (0x00000004U)

#define CSL_CONTROLSS_CTRL_LOCK0_KICK0 (0x00001008U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1 (0x0000100CU)

#define TEST_KICK_LOCK_VAL    (0x00000000U)
#define TEST_KICK0_UNLOCK_VAL (0x01234567U)
#define TEST_KICK1_UNLOCK_VAL (0x0FEDCBA8U)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G0 (0x00000100U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G1 (0x00000104U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G2 (0x00000108U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G3 (0x0000010CU)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G4 (0x00000110U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G5 (0x00000114U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G6 (0x00000118U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR1_G0 (0x00000140U)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_MASK     (0xFFFFFFFFU)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_SEL_MAX      (0xFFFFFFFFU)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G0_RESETVAL (0x00000000U)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_MASK     (0xFFFFFFFFU)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_SEL_MAX      (0xFFFFFFFFU)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G1_RESETVAL (0x00000000U)

/* INTXBAR0_G2 */

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_MASK     (0x01FFFFFFU)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_SEL_MAX      (0x01FFFFFFU)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G2_RESETVAL (0x00000000U)

/* INTXBAR0_G3 */

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_MASK     (0x0000FFFFU)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_SEL_MAX      (0x0000FFFFU)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G3_RESETVAL (0x00000000U)

/* INTXBAR0_G4 */

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_MASK     (0x000003FFU)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_SEL_MAX      (0x000003FFU)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G4_RESETVAL (0x00000000U)

/* INTXBAR0_G5 */

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_MASK     (0x000003FFU)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_SEL_MAX      (0x000003FFU)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G5_RESETVAL (0x00000000U)

/* INTXBAR0_G6 */

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_MASK     (0x00000007U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_SEL_MAX      (0x00000007U)

#define CSL_CONTROLSS_INTXBAR_INTXBAR0_G6_RESETVAL (0x00000000U)

// for inputXbar
#define CSL_CONTROLSS_INPUTXBAR_U_BASE (0x502D0000U)
#define CSL_CONTROLSS_INTXBAR_U_BASE   (0x502D5000UL)
#define INT_XBAR_ECAP0_INT             (0x00000001)
#define CSL_CONTROLSS_INPUTXBAR_STEP   (CSL_CONTROLSS_INPUTXBAR_INPUTXBAR1_GSEL - CSL_CONTROLSS_INPUTXBAR_INPUTXBAR0_GSEL)
#define CSL_CONTROLSS_PWMXBAR_STEP     (CSL_CONTROLSS_PWMXBAR_PWMXBAR1_G0 - CSL_CONTROLSS_PWMXBAR_PWMXBAR0_G0)
#define CSL_CONTROLSS_MDLXBAR_STEP     (CSL_CONTROLSS_MDLXBAR_MDLXBAR1_G0 - CSL_CONTROLSS_MDLXBAR_MDLXBAR0_G0)
#define CSL_CONTROLSS_ICLXBAR_STEP     (CSL_CONTROLSS_ICLXBAR_ICLXBAR1_G0 - CSL_CONTROLSS_ICLXBAR_ICLXBAR0_G0)
#define CSL_CONTROLSS_INTXBAR_STEP     (CSL_CONTROLSS_INTXBAR_INTXBAR1_G0 - CSL_CONTROLSS_INTXBAR_INTXBAR0_G0)
#define CSL_CONTROLSS_DMAXBAR_STEP     (CSL_CONTROLSS_DMAXBAR_DMAXBAR1_GSEL - CSL_CONTROLSS_DMAXBAR_DMAXBAR0_GSEL)
#define CSL_CONTROLSS_OUTPUTXBAR_STEP \
    (CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR1_G0 - CSL_CONTROLSS_OUTPUTXBAR_OUTPUTXBAR0_G0)
#define CSL_CONTROLSS_PWMSYNCOUTXBAR_STEP \
    (CSL_CONTROLSS_PWMSYNCOUTXBAR_PWMSYNCOUTXBAR1_G0 - CSL_CONTROLSS_PWMSYNCOUTXBAR_PWMSYNCOUTXBAR0_G0)

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */
void IcuApp_Startup(void);
void IcuApp_interruptConfig(uint32 channelId);
void Icu_InterruptConfig(void);
void Icu_App_PlatformInit(void);
void Icu_App_Pwm_Init(void);

#endif
