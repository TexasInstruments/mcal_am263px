/* ======================================================================
 *   Copyright (C) 2025 Texas Instruments Incorporated
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

/**
 *  \file     CddCmpssApp_Platform.h
 *
 *  \brief    CMPSS platform specific header file
 *
 */
#ifndef CDD_CMPSS_APP_PLATFORM_H_
#define CDD_CMPSS_APP_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* PWM Channel ID */
#define CMPSS_APP_PWM_CH_ID (0U)

/* CMPSS Instance to test */
#define CMPSS_APP_CMPSS_HW_ID (CDD_CMPSS_CONTROLSS_CMPSSA1)
/* CMPSS Ramp Source - EPWM2SYNCPER */
#define CMPSS_APP_CMPSS_RAMP_SRC (1U)
/* CMPSS Blank Source - EPWM2BLANK */
#define CMPSS_APP_CMPSS_BLANK_SRC (1U)

/* CMPSS DAC High Value - VDD/2 */
#define CMPSS_APP_CMPSS_DAC_HIGH_VAL (2048U)
/* CMPSS DAC Low Value */
#define CMPSS_APP_CMPSS_DAC_LOW_VAL (0U)

/* PWM XBAR Output */
#define CMPSS_APP_PWM_XBAR_OUT (3U)
/* PWM XBAR Input Mask */
#define CMPSS_APP_PWM_XBAR_GROUP0_MASK (MCU_PWM_XBAR_CMPSSA1_CTRIPH)

/* Output XBAR Output */
#define CMPSS_APP_OUTPUT_XBAR_OUT (0U)
/* Output XBAR Input Mask */
#define CMPSS_APP_OUTPUT_XBAR_GROUP6_MASK (MCU_OUTPUT_XBAR_CMPSSA1_CTRIPH)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void CddCmpss_appPlatformInit(void);
void CddCmpss_appPlatformDeInit(void);
void CddCmpss_appConfigXbar(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_CMPSS_APP_PLATFORM_H_ */
