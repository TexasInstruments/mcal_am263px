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
 *  \file     Cdd_Cmpss_Cfg.h
 *
 *  \brief    This file contains pre compile configurations for the CMPSS
 *            Complex device driver
 *
 *  \note     The user need to edit this file to have different configuration from
 *            the current default configurations. Generation of this configuration
 *            is not provided via configurator as this module doesn't have or require
 *            init time configurations
 */

/**
 *  \defgroup CDD_CMPSS_CFG  Configuration
 *
 *  This files defines CDD CMPSS configuration structures
 *  @{
 */

#ifndef CDD_CMPSS_CFG_H_
#define CDD_CMPSS_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \name CDD CMPSS Driver Configuration SW Version Info
 *
 *  Defines for CDD CMPSS Driver configuration version
 *  @{
 */
/** \brief CDD CMPSS configuration Major Version */
#define CDD_CMPSS_CFG_MAJOR_VERSION     (1U)
/** \brief CDD CMPSS configuration Minor Version */
#define CDD_CMPSS_CFG_MINOR_VERSION     (0U)
/** \brief CDD CMPSS configuration Patch Version */
#define CDD_CMPSS_CFG_PATCH_VERSION     (1U)
/** @} */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Enable/Disable CDD CMPSS dev detect error */
#define CDD_CMPSS_DEV_ERROR_DETECT      (STD_ON)

/** \brief Version info Api macro */
#define CDD_CMPSS_VERSION_INFO_API      (STD_ON)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Specifies the HW identification (ID) for a CMPSS unit */
typedef enum
{
    CDD_CMPSS_CONTROLSS_CMPSSA0 = 0U,       /**< CMPSSA0 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA1 = 1U,       /**< CMPSSA1 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA2 = 2U,       /**< CMPSSA2 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA3 = 3U,       /**< CMPSSA3 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA4 = 4U,       /**< CMPSSA4 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA5 = 5U,       /**< CMPSSA5 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA6 = 6U,       /**< CMPSSA6 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA7 = 7U,       /**< CMPSSA7 instance */
    CDD_CMPSS_CONTROLSS_CMPSSA8 = 8U,       /**< CMPSSA8 instance */
    CDD_CMPSS_MAX = 9U,                     /**< Maximum supported HW units for the SOC */
} Cdd_Cmpss_HwUnitType;

/* ========================================================================== */
/*                      Exported Object Declarations                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CDD_CMPSS_CFG_H_ */

/** @} */
