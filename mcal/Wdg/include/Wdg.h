/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Wdg.h
 *
 *  \brief    This file contains interface header for WDG MCAL driver
 *
 */

#ifndef WDG_H_
#define WDG_H_

/**
 *  \defgroup WDG Wdg
 *  @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "WdgIf_Types.h"
#include "Wdg_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name WDG Driver Module SW Version Info
 *
 *  Defines for WDG Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define WDG_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define WDG_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation Patch Version */
#define WDG_SW_PATCH_VERSION (0U)
/** @} */

/**
 *  \name WDG Driver Module AUTOSAR Version Info
 *
 *  Defines for WDG Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by WDG Driver */
#define WDG_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by WDG Driver */
#define WDG_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by WDG Driver */
#define WDG_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/**
 *  \name WDG Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define WDG_VENDOR_ID ((uint16)44U)
/** \brief WDG Driver Module ID */
#define WDG_MODULE_ID ((uint16)102U)
/** \brief WDG Driver Instance ID */
#define WDG_INSTANCE_ID ((uint8)0U)
/** @} */

/**
 *  \name WDG Error Codes
 *
 *  Error codes returned by Driver functions
 *  @{
 */
/** \brief ERROR:Invalid driver state */
#define WDG_E_DRIVER_STATE ((uint8)0x10U)
/** \brief ERROR:Invalid mode param */
#define WDG_E_PARAM_MODE ((uint8)0x11U)
/** \brief ERROR:Invalid config param */
#define WDG_E_PARAM_CONFIG ((uint8)0x12U)
/** \brief ERROR:Invalid timeout value */
#define WDG_E_PARAM_TIMEOUT ((uint8)0x13U)
/** \brief ERROR:Invalid NULL ptr param */
#define WDG_E_PARAM_POINTER ((uint8)0x14U)
/** \brief ERROR:Invalid Configuration set selection */
#define WDG_E_INIT_FAILED ((uint8)0x15U)
/** @} */

/**
 *  \name WDG Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and is
 *  used to identify the source of the error
 *  @{
 */
/** \brief Wdg_Init() */
#define WDG_API_INIT ((uint8)0x00U)
/** \brief Wdg_SetMode() */
#define WDG_API_SET_MODE ((uint8)0x01U)
/** \brief Wdg_SetTriggerCondition() */
#define WDG_SET_TRIGGER_CONDITION ((uint8)0x03U)
/** \brief Wdg_GetVersionInfo() */
#define WDG_API_GET_VERSION_INFO ((uint8)0x04U)
/** \brief Wdg_Trigger() */
#define WDG_API_TRIGGER ((uint8)0x05U)
/** \brief Wdg_RegisterReadback() */
#define WDG_API_REGISTER_READBACK ((uint8)0x06U)
/** @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/*******************************************************************************
 * Exported Type Declarations
 ******************************************************************************/

/** \brief WDG Status enum */
typedef enum
{
    /** \brief Watchdog driver is uninitialized. State on power on before
     *   invoking Wdg_Init() */
    WDG_UNINIT,
    /** \brief Watchdog driver is in idle state. Default state when WDG
     *   timer regs are not being programmed */
    WDG_IDLE,
    /** \brief Watchdog driver is reprogramming the WD to trigger the
     *   watchdog */
    WDG_BUSY
} Wdg_StatusType;

/** \brief DWWD Reaction on violation */
typedef enum
{
    /** \brief Generate Reset */
    WDG_GENERATE_RESET = 0x00000005U,
    /** \brief Generate NMI */
    WDG_GENERATE_NMI = 0x0000000AU
} Wdg_Reaction;

/** \brief DWWD Window size */
typedef enum
{
    /** \brief Window size 100 percent */
    WDG_WINDOW_SIZE_100_PERCENT = 0x00000005U,
    /** \brief Window size 50 percent */
    WDG_WINDOW_SIZE_50_PERCENT = 0x00000050U,
    /** \brief Window size 25 percent */
    WDG_WINDOW_SIZE_25_PERCENT = 0x00000500U,
    /** \brief Window size 12_5 percent */
    WDG_WINDOW_SIZE_12_5_PERCENT = 0x00005000U,
    /** \brief Window size 6_25 percent */
    WDG_WINDOW_SIZE_6_25_PERCENT = 0x00050000U,
    /** \brief Window size 3_125 percent */
    WDG_WINDOW_SIZE_3_125_PERCENT = 0x00500000U
} Wdg_WindowSize;

/** \brief Mode info type */
typedef struct
{
    /** \brief Reaction type */
    Wdg_Reaction   reaction;
    /** \brief Window size */
    Wdg_WindowSize windowSize;
    /** \brief Preload value */
    uint32         preloadValue;
} Wdg_ModeInfoType;

/* Requirements : SWS_Wdg_00171 */
/** \brief WDG config structure */
typedef struct Wdg_ConfigType_s
{
    /** \brief Default mode */
    WdgIf_ModeType   defaultMode;
    /** \brief Instance ID */
    uint16           instanceId;
    /** \brief Initial timeout */
    uint32           initialTimeOut;
    /** \brief Fast mode config */
    Wdg_ModeInfoType fastModeCfg;
    /** \brief Slow mode config */
    Wdg_ModeInfoType slowModeCfg;
} Wdg_ConfigType;

#if (STD_ON == WDG_REGISTER_READBACK_API)
/** \brief WDG configuration register readback data structure */
typedef struct
{
    /** \brief Digital WDG control register*/
    uint32 Wdg_RtiDwdCtrl;
    /** \brief WDG Period Load register */
    uint32 Wdg_RtiDwdprld;
    /** \brief WDG status register */
    uint32 Wdg_RtiWdStatus;
    /** \brief WDG Key register */
    uint32 Wdg_RtiWdKey;
    /** \brief WDG counter register */
    uint32 Wdg_RtiDwdCntr;
    /** \brief WDG window reaction register */
    uint32 Wdg_RtiWwdRxnCtrl;
    /** \brief WDG window size controlregister */
    uint32 Wdg_RtiWwdSizeCtrl;
} Wdg_RegisterReadbackType;
#endif /* STD_ON == WDG_REGISTER_READBACK_API */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == WDG_GET_VERSION_INFO_API)
/** \brief This service returns the version information of this module
 *
 * Service ID[hex]   : 0x04U
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[out] versioninfo - Pointer to where to store the version information of this module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, WDG_CODE) Wdg_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/** \brief This service initializes the WDG driver
 *
 * Service ID[hex]   : 0x0
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] ConfigPtr - Pointer to WDG driver configuration set.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, WDG_CODE) Wdg_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);

/** \brief Switches the watchdog into the mode Mode
 *
 * Service ID[hex]   : 0x01
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * This Api resets the watchdog to update the set mode configuration.
 *
 * \param[in] Mode - One of the following statically configured modes
 *                           - WDGIF_OFF_MODE
 *                           - WDGIF_SLOW_MODE
 *                           - WDGIF_FAST_MODE
 * \return Std_ReturnType
 * \retval E_OK - Set Mode success
 * \retval E_NOT_OK - Set Mode failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, WDG_CODE) Wdg_SetMode(WdgIf_ModeType Mode);

/** \brief Sets the timeout value for the trigger counter
 *
 * Service ID[hex]   : 0x03
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] timeout - Timeout value (milliseconds) for setting the
 *                      trigger counter
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, WDG_CODE) Wdg_SetTriggerCondition(uint16 timeout);

/** \brief This function triggers the servicing of the watchdog
 *
 *
 * This function is the watchdog trigger and is invoked from WdgIsr
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, WDG_CODE) Wdg_Trigger(void);

#if (STD_ON == WDG_REGISTER_READBACK_API)
/** \brief This method is Wdg_RegisterReadback Api.
 *
 *
 * Function could be called from from task level
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] RegisterReadbackPtr - Register readback pointer
 * \return Std_ReturnType
 * \retval E_OK - Register readback success
 * \retval E_NOT_OK - Register readback failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, WDG_CODE)
Wdg_RegisterReadback(P2VAR(Wdg_RegisterReadbackType, AUTOMATIC, WDG_APPL_DATA) RegisterReadbackPtr);
#endif

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef WDG_H_ */
