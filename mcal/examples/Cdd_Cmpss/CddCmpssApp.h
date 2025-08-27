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
 *  \file     CddCmpssApp.h
 *
 *  \brief    CMPSS example header file
 *
 */
#ifndef CDD_CMPSS_APP_H_
#define CDD_CMPSS_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "string.h"
#include "Det.h"
#include "Cdd_Cmpss.h"
#include "Mcu.h"
#include "Mcu_XbarPwm.h"
#include "Mcu_XbarOutput.h"
#include "SchM_Mcu.h"
#include "Port.h"
#include "SchM_Port.h"
#include "Cdd_Pwm.h"
#include "Cdd_Pwm_Irq.h"
#include "SchM_Cdd_Pwm.h"
#include "app_utils.h"
#include "trace.h"
#include "sys_vim.h"
#include "CacheP.h"
#include "CddCmpssApp_Platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "CDD_CMPSS_APP"

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_CMPSS_APP_H_ */
