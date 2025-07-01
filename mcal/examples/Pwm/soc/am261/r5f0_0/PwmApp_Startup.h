/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/* Protection against multiple inclusion */
#ifndef PWMAPP_STARTUP_H_
#define PWMAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "sys_common.h"
#include "Pwm_Irq.h"
#include "Pwm_Priv.h"
#include "Pwm_Cfg.h"
#include "Mcu.h"
#include "Port.h"
#include "Os.h"
#include "trace.h"
#include "sys_common.h"
#include "sys_vim.h"
#include "assert.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_NAME "PWM_APP_EPWM"

#define CSL_CONTROLSS_CTRL_U_BASE      (0x502F0000ul)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0 (0x00001008U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1 (0x0000100CU)

/* LOCK0_KICK0 */

#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_MASK     (0xFFFFFFFFU)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_LOCK0_KICK0_MAX      (0xFFFFFFFFU)

#define CSL_CONTROLSS_CTRL_LOCK0_KICK0_RESETVAL (0x00000000U)

/* LOCK0_KICK1 */

#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_MASK     (0xFFFFFFFFU)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_SHIFT    (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_RESETVAL (0x00000000U)
#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_LOCK0_KICK1_MAX      (0xFFFFFFFFU)

#define CSL_CONTROLSS_CTRL_LOCK0_KICK1_RESETVAL (0x00000000U)

/*Control MMRs partition*/
#define MSS_CTRL_PARTITION0       (1)
#define TOP_CTRL_PARTITION0       (2)
#define CONTROLSS_CTRL_PARTITION0 (3)

/*Clock and reset MMRs partition*/
#define MSS_RCM_PARTITION0 (4)
#define TOP_RCM_PARTITION0 (5)

#define CSL_CONTROLSS_CTRL_EPWM_STATICXBAR_SEL0 (0x00000004U)
#define CSL_CONTROLSS_INTXBAR_U_BASE            (0x502D5000ul)

/* define the unlock and lock values for MSS_CTRL, TOP_CTRL, MSS_RCM, TOP_RCM*/
#define TEST_KICK_LOCK_VAL    (0x00000000U)
#define TEST_KICK0_UNLOCK_VAL (0x01234567U)
#define TEST_KICK1_UNLOCK_VAL (0x0FEDCBA8U)

/** @brief Number of ETPWM instances */
#define CSL_ETPWM_PER_CNT         (10U)
#define CONTROLSS_CTRL_PARTITION0 (3)

#define INT_XBAR_EPWM0_INT   (0x00000001)
#define INT_XBAR_EPWM1_INT   (0x00000002)
#define INT_XBAR_EPWM2_INT   (0x00000004)
#define INT_XBAR_EPWM3_INT   (0x00000008)
#define INT_XBAR_EPWM4_INT   (0x00000010)
#define INT_XBAR_EPWM5_INT   (0x00000020)
#define INT_XBAR_EPWM6_INT   (0x00000040)
#define INT_XBAR_EPWM7_INT   (0x00000080)
#define INT_XBAR_EPWM8_INT   (0x00000100)
#define INT_XBAR_EPWM9_INT   (0x00000200)
#define INT_XBAR_EPWM0_TZINT (0x00000001)
#define INT_XBAR_EPWM1_TZINT (0x00000002)
#define INT_XBAR_EPWM2_TZINT (0x00000004)
#define INT_XBAR_EPWM3_TZINT (0x00000008)
#define INT_XBAR_EPWM4_TZINT (0x00000010)
#define INT_XBAR_EPWM5_TZINT (0x00000020)
#define INT_XBAR_EPWM6_TZINT (0x00000040)
#define INT_XBAR_EPWM7_TZINT (0x00000080)
#define INT_XBAR_EPWM8_TZINT (0x00000100)
#define INT_XBAR_EPWM9_TZINT (0x00000200)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

#define PWM_CHANNEL_1 (0U)
#define PWM_CHANNEL_2 (1U)
#define PWM_CHANNEL   (PWM_CHANNEL_1)

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
extern volatile uint32 Pwm_App_NotifyCnt;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void PwmApp_Startup(void);

#if (STD_ON == PWM_NOTIFICATION_SUPPORTED)
void Pwm_Notification_Channel1(void);
void Pwm_Notification_Channel2(void);
void Pwm_Notification_Channel3(void);
void Pwm_Notification_Channel4(void);
#endif
void Pwm_App_InterruptInit(void);
void Pwm_App_InterruptConfig(uint32 channelId);
void Pwm_App_InterruptDisable(uint32 channelId);

void Pwm_App_PlatformInit(void);

static void SOC_setEpwmGroup(uint32 epwmInstance, uint32 group);
static void SOC_setEpwmTbClk(uint32 epwmInstance, uint32 enable);
static void SOC_controlModuleUnlockMMR(uint32 domainId, uint32 partition);
static void SOC_controlModuleLockMMR(uint32 domainId, uint32 partition);
void        Pwm_Example_DisableNotification(void);
uint32      Example_PwmCalperiod(uint32 inputfreq);
void        Example_Pwminit();
void        PwmApp_Stop(void);

#if defined TEST_EHRPWM
void Example_PwmTest_EHPWM(void);
#endif

#endif
