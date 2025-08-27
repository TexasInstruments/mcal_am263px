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
 *  \file     WdgApp.h
 *
 *  \brief    WDG example header file
 *
 */
#ifndef WDG_APP_H_
#define WDG_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "string.h"
#include "Det.h"
#include "Wdg.h"
#include "SchM_Wdg.h"
#include "Mcu.h"
#include "Mcu_Xbar.h"
#include "SchM_Mcu.h"
#include "Port.h"
#include "SchM_Port.h"
#include "app_utils.h"
#include "trace.h"
#include "sys_vim.h"
#include "WdgApp_Platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "WDG_SKIP_RESET_APP"

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

#endif /* #ifndef WDG_APP_H_ */
