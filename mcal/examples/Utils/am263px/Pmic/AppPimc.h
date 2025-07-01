/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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
#include "mcspi_v0.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MCSPI Instance Macros */
#define CONFIG_MCSPI0                      (0U)
#define CONFIG_MCSPI_NUM_INSTANCES         (1U)
#define CONFIG_MCSPI_NUM_DMA_INSTANCES     (0U)
#define CONFIG_MCSPI0_NUM_CH               (1U)
#define CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR 79
#define CSL_MCSPI1_U_BASE                  (0x52201000ul)

int32_t pmic_test(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ADC_APP_H_ */
