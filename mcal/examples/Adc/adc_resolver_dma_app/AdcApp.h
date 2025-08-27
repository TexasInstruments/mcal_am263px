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
 *  \file     AdcApp.h
 *
 *  \brief    ADC example header file
 *
 */
#ifndef ADC_APP_H_
#define ADC_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "string.h"
#include "Det.h"
#include "Adc.h"
#include "Adc_Irq.h"
#include "SchM_Adc.h"
#include "Mcu.h"
#include "Mcu_Xbar.h"
#include "SchM_Mcu.h"
#include "Port.h"
#include "SchM_Port.h"
#include "Cdd_Dma.h"
#include "Cdd_Dma_Irq.h"
#include "CacheP.h"
#include "app_utils.h"
#include "trace.h"
#include "sys_vim.h"
#include "AdcApp_Platform.h"
#include "cslr_resolver.h"
#include "mcal_hw_soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "ADC_RESOLVER_DMA_APP"

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

#endif /* #ifndef ADC_APP_H_ */
