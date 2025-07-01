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
 *  \file     Cdd_Flc_Soc.h
 *
 *  \brief    This file contains SOC specific macros and defines for CDD FLC
 *
 */

#ifndef CDD_FLC_SOC_H_
#define CDD_FLC_SOC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "cslr_rl2_of.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Check if max RL2 user configuration is correct for the SOC */
#if (CDD_FLC_RL2_MAX > (0x04U))
#error "This SOC supports only up to 4 instances of RL2"
#endif

/** \brief Check if max region user configuration is correct for the SOC */
#if (CDD_FLC_REGION_ID_MAX > (0x04U))
#error "This SOC supports only up to 4 regions"
#endif

/**
 *  \name RL2 base address
 *
 *  Base address of different RL2 HW units present in the SOC
 *  @{
 */
/** \brief R5SS0 CORE0 RL2 base address */
#define CSL_RL2_REGS_R5SS0_CORE0_U_BASE (0x53212000U)
/** \brief R5SS0 CORE1 RL2 base address */
#define CSL_RL2_REGS_R5SS0_CORE1_U_BASE (0x53213000U)
/** \brief R5SS1 CORE0 RL2 base address */
#define CSL_RL2_REGS_R5SS1_CORE0_U_BASE (0x53214000U)
/** \brief R5SS1 CORE1 RL2 base address */
#define CSL_RL2_REGS_R5SS1_CORE1_U_BASE (0x53215000U)
/** @} */

/** \brief Base address array for all modules present in the device */
#define CDD_FLC_BASEADDR_ARRAY                                                                              \
    (CSL_rl2_of_Regs *)CSL_RL2_REGS_R5SS0_CORE0_U_BASE, (CSL_rl2_of_Regs *)CSL_RL2_REGS_R5SS0_CORE1_U_BASE, \
        (CSL_rl2_of_Regs *)CSL_RL2_REGS_R5SS1_CORE0_U_BASE, (CSL_rl2_of_Regs *)CSL_RL2_REGS_R5SS1_CORE1_U_BASE,

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

#endif /* CDD_FLC_SOC_H_ */
