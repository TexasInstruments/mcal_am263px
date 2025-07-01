/* ======================================================================
 *   Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Dio.h
 *
 *  \brief    This file contains interface header for DIO MCAL driver
 *
 */

/*  ----------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------
 *         File:  Dio.h
 *    Component:  AM263 MCAL driver
 *       Module:  DioDriver
 *    Generator:  -
 *
 *   Description: This DIO Driver provides services for
 *                reading and writing to/from
 *                        -   DIO Channels (Pins)
 *                        -   DIO Ports
 *                        -   DIO Channel Groups
 *
 *                This module works on pins and ports which are configured by the
 *                PORT driver for this purpose.
 *                For this reason there is no configuration and initialization of
 *                this port structure in the DIO Driver.
 *-----------------------------------------------------------------------------*/

/* Design:DIO_DesignId_001,DIO_DesignId_002,DIO_DesignId_003,DIO_DesignId_004 */
/*
 * Below are the global requirements which are met by this DIO
 * driver which can't be mapped to a particular source ID
 */

/*
 * Below are the DIO's module environment requirements which can't be mapped
 * to this driver.
 */

#ifndef DIO_H_
#define DIO_H_

/**
 * \defgroup DIO Dio API GUIDE Header file
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"

#include "Dio_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name DIO Driver Module SW Version Info
 *
 *  Defines for DIO Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define DIO_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define DIO_SW_MINOR_VERSION (1U)
/** \brief Driver Implementation Patch Version */
#define DIO_SW_PATCH_VERSION (0U)
/**   @} */

/**
 *  \name DIO Driver Module AUTOSAR Version Info
 *
 *  Defines for DIO Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by DIO Driver */
#define DIO_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by DIO Driver */
#define DIO_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by DIO Driver */
#define DIO_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/**
 *  \name DIO Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define DIO_VENDOR_ID ((uint16)44U)
/** \brief DIO Driver Module ID */
#define DIO_MODULE_ID ((uint16)120U)
/**   @} */

/**
 *  \name Dio Error Codes
 *
 *  Error codes returned by Driver functions
 *  @{
 */
#ifndef DIO_E_PARAM_INVALID_CHANNEL_ID
/** \brief ERROR:API service called with invalid channel ID */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (0x0AU)
#endif
#ifndef DIO_E_PARAM_INVALID_PORT_ID
/** \brief ERROR:API service called with invalid port ID */
#define DIO_E_PARAM_INVALID_PORT_ID (0x14U)
#endif
#ifndef DIO_E_PARAM_INVALID_GROUP
/** \brief ERROR:API service called with invalid channel group ID */
#define DIO_E_PARAM_INVALID_GROUP (0x1FU)
#endif
#ifndef DIO_E_PARAM_POINTER
/** \brief ERROR:Dio_GetVersionInfo() called with NULL_PTR as parameter */
#define DIO_E_PARAM_POINTER (0x20U)
#endif
/**   @} */

/**
 *  \name Dio Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and is
 *  used to identify the source of the error
 *  @{
 */
/* DIO API service identification */
/** \brief Dio_ReadChannel() */
#define DIO_SID_READ_CHANNEL (0U)
/** \brief Dio_WriteChannel() */
#define DIO_SID_WRITE_CHANNEL (1U)
/** \brief Dio_ReadPort() */
#define DIO_SID_READ_PORT (2U)
/** \brief Dio_WritePort() */
#define DIO_SID_WRITE_PORT (3U)
/** \brief Dio_ReadChannelGroup() */
#define DIO_SID_READ_CHL_GROUP (4U)
/** \brief Dio_WriteChannelGroup() */
#define DIO_SID_WRITE_CHL_GROUP (5U)
/** \brief Dio_FlipChannel() */
#define DIO_SID_FLIP_CHANNEL (7U)
/** \brief Dio_GetVersionInfo() */
#define DIO_SID_GET_VERSION_INFO (18U)
/** \brief Dio_RegisterReadback() */
#define DIO_SID_REGISTER_READBACK (19U)
/**   @} */

/** \brief To Return 0 when Improper ID is passed to Read functions */
#define DIO_RETURN_ZERO (0U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief type definition for identifying DIO channels (meaning single port
 *  pins) */

/* Requirements : SWS_Dio_00182, SWS_Dio_00015, SWS_Dio_00129 */
/*
 * Design: MCAL-19943,MCAL-19944,MCAL-19945,MCAL-19946
 */
typedef uint32 Dio_ChannelType;

/** \brief type definition for identifying ports */
/* Requirements : SWS_Dio_00183, SWS_Dio_00018, SWS_Dio_00181,  */
/*
 * Design: MCAL-19947,MCAL-19948,MCAL-19949,MCAL-19950
 */
typedef uint32 Dio_PortType;

/** \brief type definition for status*/
typedef uint8 Dio_StatusType;

/* Requirements : SWS_Dio_00186 */

/**  \brief type definition for setting port level values
 *
 *  This is a bitmask, where each bit with value '1' sets the corresponding port
 *  pin to HIGH and '0' sets the pin to LOW)
 */
/*
 * Design: MCAL-19956,MCAL-19957
 */
typedef uint32 Dio_PortLevelType;

/* Requirements : SWS_Dio_00185 */

/**  \brief type definition for setting DIO channnel level values (allowed
 *  values: STD_HIGH and STD_LOW)  */

/*
 * Design: MCAL-19954,MCAL-19955
 */
typedef uint8 Dio_LevelType;

/* Requirements : SWS_Dio_00056, SWS_Dio_00184, SWS_Dio_00021 */

/**  \brief  Type definition for identifying channel groups (meaning a set of
 *                                                          pins in one port)
 */
/*
 * Design: MCAL-19951,MCAL-19952,MCAL-19953
 */
typedef struct
{
    /** \brief port ID of a channel group */
    Dio_PortType      port;
    /** \brief bitmask where a '1' represents a pin handled by this channel group */
    Dio_PortLevelType mask;
    /** \brief shifts channel group values, so it is always "right" aligned */
    uint8             offset;
} Dio_ChannelGroupType;

/**
 *  \brief type definition for referencing channel group structures
 */
typedef P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_DATA) Dio_ChannelGroupRefType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Returns the value of the specified DIO channel.
 *
 *
 * Service ID[hex] - 0x00
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] ChannelId - ID of DIO channel
 * \return Dio_LevelType
 * \retval STD_HIGH - The physical level of the corresponding Pin is STD_HIGH
 * \retval STD_LOW - The physical level of the corresponding Pin is STD_LOW
 *
 *****************************************************************************/
FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel(Dio_ChannelType ChannelId);

/** \brief Service to set a level of a channel.
 *
 *
 * Service ID[hex] - 0x01
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] ChannelId - ID of DIO channel
 * \param[in] Level - Value to be written
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, DIO_CODE) Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/** \brief Returns the level of all channels of that port.
 *
 *
 * Service ID[hex] - 0x02
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] PortId - ID of DIO Port
 * \return Dio_PortLevelType
 * \retval Level of all channels of that port
 *
 *****************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadPort(Dio_PortType PortId);

/** \brief Service to set a value of the port.
 *
 *
 * Service ID[hex] - 0x03
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] PortId - ID of DIO Port
 * \param[in] Level - Value to be written
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, DIO_CODE) Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/** \brief This Service reads a subset of the adjoining bits of a port.
 *
 *
 * Service ID[hex] - 0x04
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] ChannelGroupIdPtr - Pointer to ChannelGroup
 * \return Dio_PortLevelType
 * \retval Level of a subset of the adjoining bits of a port
 *
 *****************************************************************************/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadChannelGroup(Dio_ChannelGroupRefType ChannelGroupIdPtr);

/** \brief Service to set a subset of the adjoining bits of a port to a
 *  specified level
 *
 *
 * Service ID[hex] - 0x05
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] ChannelGroupIdPtr - Pointer to ChannelGroup
 * \param[in] Level - Value to be written
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, DIO_CODE)
Dio_WriteChannelGroup(Dio_ChannelGroupRefType ChannelGroupIdPtr, Dio_PortLevelType Level);

#if (STD_ON == DIO_VERSION_INFO_API)
/** \brief Service to get the version information of this module
 *
 *
 * Service ID[hex] - 0x12
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[out] versioninfo - Pointer to where to store the version information of
 * this module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, DIO_CODE)
Dio_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) versioninfo);
#endif

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/** \brief Service to flip (change from 1 to 0 or from 0 to 1) the level of a
 * channel and return the level of the channel after flip
 *
 *
 * Service ID[hex] - 0x11
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] ChannelId - ID of DIO channel
 * \return Dio_LevelType
 * \retval STD_HIGH - The physical level of the corresponding Pin is STD_HIGH
 * \retval STD_LOW - The physical level of the corresponding Pin is STD_LOW
 *
 *****************************************************************************/
FUNC(Dio_LevelType, DIO_CODE) Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif

#if (STD_ON == DIO_REGISTER_READBACK_API)
/** \brief This function reads the important registers of the hardware unit
 * and returns the value in the structure.
 *
 *
 * This API is used to check the status of critical registers which do not
 * change during program execution.
 *
 * Service ID[hex] - 0x19
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[inout] RegRbPtr - Pointer to where to store the readback values.
 * If this pointer is NULL, then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK - Register read back has been done successfully
 * \retval E_NOT_OK - Register read back failed
 *****************************************************************************/
FUNC(Std_ReturnType, DIO_CODE)
Dio_RegisterReadback(P2VAR(Dio_RegisterReadbackType, AUTOMATIC, DIO_APPL_DATA) RegRbPtr);
#endif

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef DIO_H_ */
