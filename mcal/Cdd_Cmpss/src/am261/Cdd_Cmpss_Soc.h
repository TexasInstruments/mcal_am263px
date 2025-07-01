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
 *  \file     Cdd_Cmpss_Soc.h
 *
 *  \brief    This file contains SOC specific macros and defines for CDD CMPSS
 *
 */

#ifndef CDD_CMPSS_SOC_H_
#define CDD_CMPSS_SOC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "cslr_cmpssa.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Check if max user configuration is correct for the SOC */
#if (CDD_CMPSS_MAX > 9U)
#error "This SOC supports only up to 9 instances of CMPSS"
#endif

/**
 *  \name CMPSS base address
 *
 *  Base address of different HW units present in the SOC
 *  @{
 */
/** \brief CMPSSA0 base address */
#define CSL_CONTROLSS_CMPSSA0_U_BASE (0x50200000U)
/** \brief CMPSSA1 base address */
#define CSL_CONTROLSS_CMPSSA1_U_BASE (0x50201000U)
/** \brief CMPSSA2 base address */
#define CSL_CONTROLSS_CMPSSA2_U_BASE (0x50202000U)
/** \brief CMPSSA3 base address */
#define CSL_CONTROLSS_CMPSSA3_U_BASE (0x50203000U)
/** \brief CMPSSA4 base address */
#define CSL_CONTROLSS_CMPSSA4_U_BASE (0x50204000U)
/** \brief CMPSSA5 base address */
#define CSL_CONTROLSS_CMPSSA5_U_BASE (0x50205000U)
/** \brief CMPSSA6 base address */
#define CSL_CONTROLSS_CMPSSA6_U_BASE (0x50206000U)
/** \brief CMPSSA7 base address */
#define CSL_CONTROLSS_CMPSSA7_U_BASE (0x50207000U)
/** \brief CMPSSA8 base address */
#define CSL_CONTROLSS_CMPSSA8_U_BASE (0x50208000U)
/** @} */

/** \brief Base address array for all modules present in the device */
#define CDD_CMPSS_BASEADDR_ARRAY                                                                  \
    CSL_CONTROLSS_CMPSSA0_U_BASE, CSL_CONTROLSS_CMPSSA1_U_BASE, CSL_CONTROLSS_CMPSSA2_U_BASE,     \
        CSL_CONTROLSS_CMPSSA3_U_BASE, CSL_CONTROLSS_CMPSSA4_U_BASE, CSL_CONTROLSS_CMPSSA5_U_BASE, \
        CSL_CONTROLSS_CMPSSA6_U_BASE, CSL_CONTROLSS_CMPSSA7_U_BASE, CSL_CONTROLSS_CMPSSA8_U_BASE,

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

#endif /* CDD_CMPSS_SOC_H_ */
