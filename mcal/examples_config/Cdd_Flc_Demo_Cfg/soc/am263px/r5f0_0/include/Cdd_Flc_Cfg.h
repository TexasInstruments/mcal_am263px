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
 *  \file     Cdd_Flc_Cfg.h
 *
 *  \brief    This file contains pre compile configurations for the FLC
 *            Complex device driver
 *
 *  \note     The user need to edit this file to have different configuration from
 *            the current default configurations. Generation of this configuration
 *            is not provided via configurator as this module doesn't have or require
 *            init time configurations
 */

/**
 *  \defgroup CDD_FLC_CFG  Configuration
 *
 *  This files defines CDD FLC configuration structures
 *  @{
 */

#ifndef CDD_FLC_CFG_H_
#define CDD_FLC_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \name CDD FLC Driver Configuration SW Version Info
 *
 *  Defines for CDD FLC Driver configuration version
 *  @{
 */
/** \brief CDD FLC configuration Major Version */
#define CDD_FLC_CFG_MAJOR_VERSION       (1U)
/** \brief CDD FLC configuration Minor Version */
#define CDD_FLC_CFG_MINOR_VERSION       (0U)
/** \brief CDD FLC configuration Patch Version */
#define CDD_FLC_CFG_PATCH_VERSION       (2U)
/** @} */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Enable/Disable CDD FLC dev detect error */
#define CDD_FLC_DEV_ERROR_DETECT        (STD_ON)

/** \brief Version info Api macro */
#define CDD_FLC_VERSION_INFO_API        (STD_ON)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Specifies the HW identification (ID) for a FLC unit */
typedef enum
{
    CDD_FLC_RL2_R5SS0_CORE0 = 0U,         /**< FLC instance present in R5SS0 CORE0 RL2 */
    CDD_FLC_RL2_R5SS0_CORE1 = 1U,         /**< FLC instance present in R5SS0 CORE1 RL2 */
    CDD_FLC_RL2_R5SS1_CORE0 = 2U,         /**< FLC instance present in R5SS1 CORE0 RL2 */
    CDD_FLC_RL2_R5SS1_CORE1 = 3U,         /**< FLC instance present in R5SS1 CORE1 RL2 */
    CDD_FLC_RL2_MAX = 4U,                 /**< Maximum supported HW units for the SOC */
} Cdd_Flc_HwUnitType;

/** \brief FLC Region ID */
typedef enum Cdd_Flc_RegionIdTag
{
    CDD_FLC_REGION_ID_0,    /**< FLC Region 0 ID */
    CDD_FLC_REGION_ID_1,    /**< FLC Region 1 ID */
    CDD_FLC_REGION_ID_2,    /**< FLC Region 2 ID */
    CDD_FLC_REGION_ID_3,    /**< FLC Region 3 ID */
    CDD_FLC_REGION_ID_MAX,  /**< Total FLC Regions */
} Cdd_Flc_RegionId;

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

#endif  /* #ifndef CDD_FLC_CFG_H_ */

/** @} */
