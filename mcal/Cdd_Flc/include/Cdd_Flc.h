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
 *  \file     Cdd_Flc.h
 *
 *  \brief    This file contains interface header for OptiFlash FLC (Fast Local Copy)
 *            module CDD MCAL driver
 *
 */

/**
 *
 * \defgroup CDD_FLC OptiFlash FLC (Fast Local Copy) API
 *  @{
 */

#ifndef CDD_FLC_H_
#define CDD_FLC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cdd_Flc_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name CDD_FLC Driver Module SW Version Info
 *
 *  Defines for CDD_FLC Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_FLC_SW_MAJOR_VERSION (1U)
/** \brief Driver Implementation Minor Version */
#define CDD_FLC_SW_MINOR_VERSION (0U)
/** \brief Driver Implementation Patch Version */
#define CDD_FLC_SW_PATCH_VERSION (3U)
/** @} */

/**
 *  \name CDD_FLC Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD_FLC Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD_FLC Driver*/
#define CDD_FLC_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor version specification implemented by CDD_FLC Driver*/
#define CDD_FLC_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by CDD_FLC Driver*/
#define CDD_FLC_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/**
 *  \name CDD FLC Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define CDD_FLC_VENDOR_ID ((uint16)44U)
/** \brief CDD FLC Driver Module ID */
#define CDD_FLC_MODULE_ID ((uint16)255U)
/** \brief CDD FLC Instance ID */
#define CDD_FLC_INSTANCE_ID ((uint8)0U)
/** @} */

/**
 *  \name CDD FLC Error Codes
 *
 *  Error codes returned by CDD_FLC functions
 *  @{
 */
/** \brief API service called will null param pointer */
#define CDD_FLC_E_PARAM_POINTER ((uint8)0x01U)
/** \brief API service called with illegal HW ID */
#define CDD_FLC_E_ILLEGAL_HW_ID ((uint8)0x02U)
/** \brief API service called with illegal region ID */
#define CDD_FLC_E_ILLEGAL_REGION_ID ((uint8)0x03U)
/** \brief API service called with unaligned address */
#define CDD_FLC_E_UNALIGNED_ADDRESS ((uint8)0x04U)
/** @} */

/**
 *  \name CDD FLC Service Id
 *
 *  The Service Id is one of the argument to Det_ReportError function and is
 *  used to identify the source of the error
 *  @{
 */
/** \brief Cdd_Flc_GetVersionInfo() API Service ID */
#define CDD_FLC_SID_GET_VERSION_INFO ((uint8)0x00U)
/** \brief Cdd_Flc_ConfigureRegion() API Service ID */
#define CDD_FLC_SID_CONFIGURE_REGION ((uint8)0x01U)
/** \brief Cdd_Flc_EnableRegion() API Service ID */
#define CDD_FLC_SID_ENABLE_REGION ((uint8)0x02U)
/** \brief Cdd_Flc_IsRegionCopyDone() API Service ID */
#define CDD_FLC_SID_IS_REGION_COPY_DONE ((uint8)0x03U)
/** \brief Cdd_Flc_DisableRegion() API Service ID */
#define CDD_FLC_SID_DISABLE_REGION ((uint8)0x04U)
/** \brief Cdd_Flc_GetStatus() API Service ID */
#define CDD_FLC_SID_GET_STATUS ((uint8)0x05U)
/** \brief Cdd_Flc_ClearAllStatus() API Service ID */
#define CDD_FLC_SID_CLEAR_ALL_STATUS ((uint8)0x06U)
/** @} */

/** \brief Source and destination addresses should be aligned to this */
#define CDD_FLC_ADDR_ALIGNMENT ((uint32)(4U * 1024U))
/** \brief Source and destination address alignment mask */
#define CDD_FLC_ADDR_ALIGNMENT_MSK ((uint32)(CDD_FLC_ADDR_ALIGNMENT - 1U))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief FLC Region Config type */
typedef struct Cdd_Flc_RegionConfigTypeTag
{
    /**
     *  \brief Source start address. Data at this address is copied.
     *  This address should be aligned to 4KB boundary
     */
    uint32 srcStartAddr;
    /**
     *  \brief Source end address, upto this address data is copied.
     *  This address should be aligned to 4KB boundary.
     *  \note Data at this address is not copied. So this should be set to
     *  (srcStartAddr + length) and not (srcStartAddr + length - 1)
     */
    uint32 srcEndAddr;
    /**
     *  \brief Destination start address, this address is also written.
     *  This address should be aligned to 4KB boundary
     */
    uint32 destStartAddr;
} Cdd_Flc_RegionConfigType;

/**
 *   \brief FLC Status.
 *
 *  \note These status are common for all regions. Use region specific API like
 *        Cdd_Flc_IsRegionCopyDone() to check for region specific status
 */
typedef struct Cdd_Flc_StatusTypeTag
{
    /** \brief FLC has completed the copy to the FLC range */
    boolean copyDone;
    /**
     *  \brief Indicates a write error from FLC range has occurred and the FLC is
     *  logically disabled if this is set
     */
    boolean wrError;
    /**
     *  \brief Indicates a read error from FLC range has occurred and the FLC is
     *  logically disabled if this is set
     */
    uint32  rdError;
} Cdd_Flc_StatusType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == CDD_FLC_VERSION_INFO_API)
/**
 * \brief Service that returns the version information of the module.
 *
 * \param[in] VersionInfo Pointer to where to store the version information of this module
 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_FLC_DATA) VersionInfo);
#endif

/**
 * \brief Service to configure a FLC region
 *
 * \note If the requested region is already in enabled state, the API returns E_NOT_OK.
 *       It is expected that the caller first calls Cdd_Flc_DisableRegion() API before calling
 *       this API in this scenario.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_FLC_HW_UNIT_MAX
 * \param[in] RegionId Region ID to configure. This param should be less than CDD_FLC_REGION_ID_MAX
 * \param[in] RegionCfgPtr Pointer to the region configuration parameter. This should not be NULL.
 *
 * \return If the configuration is successful, returns E_OK else returns E_NOT_OK
 */
FUNC(Std_ReturnType, CDD_FLC_CODE)
Cdd_Flc_ConfigureRegion(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId,
                        P2CONST(Cdd_Flc_RegionConfigType, AUTOMATIC, CDD_FLC_DATA) RegionCfgPtr);

/**
 * \brief Service to enable and start the FLC copy from source to destination
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_FLC_HW_UNIT_MAX
 * \param[in] RegionId Region ID to start. This param should be less than CDD_FLC_REGION_ID_MAX
 * \param[in] EnableWithoutCopy Set this to TRUE when the region has to be enabled without a copy
 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_EnableRegion(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId,
                     VAR(boolean, AUTOMATIC) EnableWithoutCopy);

/**
 * \brief Service to check if the initiated FLC copy is completed
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_FLC_HW_UNIT_MAX
 * \param[in] RegionId Region ID to check. This param should be less than CDD_FLC_REGION_ID_MAX
 *
 * \return TRUE if copy is completed. FALSE otherwise.
 */
FUNC(boolean, CDD_FLC_CODE)
Cdd_Flc_IsRegionCopyDone(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId);

/**
 * \brief Service to disable the FLC region
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_FLC_HW_UNIT_MAX
 * \param[in] RegionId Region ID to start. This param should be less than CDD_FLC_REGION_ID_MAX
 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_DisableRegion(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId);

/**
 * \brief Service to get the status of the FLC
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_FLC_HW_UNIT_MAX
 * \param[in] StatusPtr Pointer to where to store the FLC status
 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_GetStatus(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId,
                  P2VAR(Cdd_Flc_StatusType, CDD_FLC_DATA, AUTOMATIC) StatusPtr);

/**
 * \brief Service to clear all status of the FLC
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_FLC_HW_UNIT_MAX
 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_ClearAllStatus(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId);

#ifdef __cplusplus
}
#endif

#endif /* CDD_FLC_H_ */

/** @} */
