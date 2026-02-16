/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
#define CDD_CMPSS_CFG_PATCH_VERSION     (3U)
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
