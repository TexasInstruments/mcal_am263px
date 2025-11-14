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
 *  \file     Mcu.h
 *
 *  \brief    This file contains interface header for Mcu Driver
 *
 */

/*
 * Below are the global requirements which are met by this MCU
 * driver which can't be mapped to a particular source ID
 */
/*
 * Requirements : SWS_Mcu_00017, SWS_Mcu_00226
 *
 */

/*
 * Below are the MCU module environment requirements which can't be mapped
 * to this driver
 */
/*
 * Requirements : SWS_Mcu_00116, SWS_Mcu_00051,
 *                SWS_Mcu_00244, SWS_Mcu_00246, SWS_Mcu_00247
 */
#ifndef MCU_H_
#define MCU_H_

/**
 *  \defgroup MCU Mcu
 *  @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
/* Design: MCAL-14059 , MCAL-14058 */
#include "Mcu_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name MCU Driver Module SW Version Info
 *
 *  Defines for MCU Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define MCU_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define MCU_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation Patch Version */
#define MCU_SW_PATCH_VERSION (1U)
/** @} */

/**
 *  \name MCU Driver Module AUTOSAR Version Info
 *
 *  Defines for MCU Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by MCU Driver */
#define MCU_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by MCU Driver */
#define MCU_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by MCU Driver */
#define MCU_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/**
 *  \name MCU Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define MCU_VENDOR_ID ((uint16)44U)
/** \brief MCU Driver Module ID */
#define MCU_MODULE_ID ((uint16)101U)
/** \brief MCU Driver Instance ID */
#define MCU_INSTANCE_ID ((uint8)0U)
/** @} */

/**
 *  \name MCU Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief Mcu_Init() API Service ID */
#define MCU_SID_INIT ((uint8)0x00U)
/** \brief Mcu_InitRamSection() API Service ID */
#define MCU_SID_INIT_RAMSECTION ((uint8)0x01U)
/** \brief Mcu_InitClock() API Service ID */
#define MCU_SID_INIT_CLOCK ((uint8)0x02U)
/** \brief Mcu_DistributePllClock() API Service ID */
#define MCU_SID_DISTRIBUTE_PLL_CLOCK ((uint8)0x03U)
/** \brief Mcu_GetPllStatus() API Service ID */
#define MCU_SID_GET_PLL_STATUS ((uint8)0x04U)
/** \brief Mcu_GetResetReason() API Service ID */
#define MCU_SID_GET_RESET_REASON ((uint8)0x05U)
/** \brief Mcu_GetResetRawValue() API Service ID */
#define MCU_SID_GET_RESET_RAW_VALUE ((uint8)0x06U)
/** \brief Mcu_PerformReset() API Service ID */
#define MCU_SID_PERFORM_RESET ((uint8)0x07U)
/** \brief Mcu_SetMode() API Service ID */
#define MCU_SID_SET_MODE ((uint8)0x08U)
/** \brief Mcu_GetVersionInfo() API Service ID */
#define MCU_SID_GET_VERSION_INFO ((uint8)0x09U)
/** \brief Mcu_GetRamState() API Service ID */
#define MCU_SID_GET_RAM_STATE ((uint8)0x0AU)
/** \brief Mcu_PLLInitAll() API Service ID */
#define MCU_SID_PLL_INIT_ALL ((uint8)0x0BU)
/** \brief Mcu_RegisterReadback() API Service ID */
#define MCU_SID_REGISTER_READBACK ((uint8)0x0CU)
/** @} */

/*
 *Design: MCAL-14287,MCAL-14285, MCAL-14062, MCAL-14281, MCAL-14282, MCAL-14310
 */
/**
 *  \name MCU Error Codes
 *
 *  Error Codes returned by MCU Driver
 *  @{
 */
#ifndef MCU_E_PARAM_CONFIG
/** \brief ERROR:Mcu_init config param invalid */
#define MCU_E_PARAM_CONFIG ((uint8)0x0AU)
#endif
#ifndef MCU_E_PARAM_CLOCK
/** \brief ERROR:Mcu_InitClock clockid param invalid */
#define MCU_E_PARAM_CLOCK ((uint8)0x0BU)
#endif
#ifndef MCU_E_PARAM_MODE
/** \brief ERROR:Mcu_SetMode modeid param invalid */
#define MCU_E_PARAM_MODE ((uint8)0x0CU)
#endif
#ifndef MCU_E_PARAM_RAMSECTION
/** \brief ERROR:Mcu_InitRamSection ramSect param invalid */
#define MCU_E_PARAM_RAMSECTION ((uint8)0x0DU)
#endif
#ifndef MCU_E_PLL_NOT_LOCKED
/** \brief ERROR:PLL not locked */
#define MCU_E_PLL_NOT_LOCKED ((uint8)0x0EU)
#endif
#ifndef MCU_E_UNINIT
/** \brief ERROR:API invoked without performing Mcu_Init */
#define MCU_E_UNINIT ((uint8)0x0FU)
#endif
#ifndef MCU_E_PARAM_POINTER
/** \brief ERROR:NULL_PTR passed to MCU driver APIs */
#define MCU_E_PARAM_POINTER ((uint8)0x10U)
#endif
#ifndef MCU_E_RUNTIME_ASSERT
/** \brief ERROR:Runtime assert failure */
#define MCU_E_RUNTIME_ASSERT ((uint8)0x11U)
#endif
/** @} */
/** \brief Specifief the status of un-initialization*/
#define MCU_STATE_UNINIT ((uint8)0x00U)
/** \brief Specifief the status of un-initialization*/
#define MCU_STATE_INIT ((uint8)0x01U)
/** \brief Specifies the DSP SoC supported frequency vs Selected frequency from configuration Cfg.h
 * file Mismatch This Error is thrown when user selects more frequency for DSP core than what the
 * SoC supports. Ex: In the configuration if McuDSPDPLLClockout_HSDIV1 is selected as 550Mhz but if
 * SoC supports only 300MHz as the maximum frequency this error is thrown.
 */
#define MCU_INCORRECT_DSP_FREQ_SEL ((uint8)0x02U)

/**
 *  \name MCU Reset Modes
 *
 *  Reset mode enum which can be used in Mcu_PerformReset()
 *  @{
 */
/** \brief Initiate SW WARM RESET sequence */
#define MCU_PERFORM_RESET_MODE_WARM (0U)

/** \brief Reset Reason Error Mask */
#define MCU_ERRORRST_MASK ((Mcu_RawResetType)0xFFFF0000U)

/** \brief Reset Reason  */
#define RESETREASON_NRESET 0x0U
/** @} */
/**
 *  \name MCU RCM modules mode ID defines
 *
 *  PRCM modules ids defines are used tp enable specific modules
 *  @{
 */
/** \brief ModuleId for First */
#define MCU_RCM_MODULE_ID_FIRST (0U)
/** \brief ModuleId for DCAN */
#define MCU_RCM_MODULE_ID_DCAN (0U)
/** \brief ModuleId for MIBSPI1 */
#define MCU_RCM_MODULE_ID_MIBSPI1 (1U)
/** \brief ModuleId for MIBSPI2 */
#define MCU_RCM_MODULE_ID_MIBSPI2 (2U)
/** \brief ModuleId for QSPI */
#define MCU_RCM_MODULE_ID_QSPI (3U)
/** \brief ModuleId for GPIOA */
#define MCU_RCM_MODULE_ID_GPIOA (4U)
/** \brief ModuleId for Watchdog */
#define MCU_RCM_MODULE_ID_WDTIMER (5U)
/** \brief ModuleId for UART */
#define MCU_RCM_MODULE_ID_UART (6U)
/** \brief ModuleId for GPTIMER */
#define MCU_RCM_MODULE_ID_GPTIMER (7U)
/** \brief ModuleId for Last */
#define MCU_RCM_MODULE_ID_LAST (MCU_RCM_MODULE_ID_GPTIMER)
/** @} */

/* Design: MCAL-14426,MCAL-14425 */
/**
 *  \brief This type specifies the identification (ID) for a ClockType
 *  status used by Mcu_InitClock()
 */
typedef uint8 Mcu_ClockType;

/* Design: MCAL-14423, MCAL-14422 */
/**
 *  \brief This type specifies the identification (ID) for a RAW MCU reset
 *  status returned by Mcu_GetResetRawValue()
 */
typedef uint32 Mcu_RawResetType;

/* Design : MCAL-14419,MCAL-14418 */
/**
 *  \brief This type specifies the identification (ID) for a RAM section used
 *  in Mcu_InitRamSection()
 */
typedef uint8 Mcu_RamSectionType;

/* Design : MCAL-14421,MCAL-14420 */
/**
 *  \brief This type specifies the identification (ID) for a MCU mode used
 *  in Mcu_SetMode()
 */
typedef uint8 Mcu_ModeType;

/* Design: MCAL-14427, MCAL-14428 */
/**
 *  \enum Mcu_PllStatusType
 *  \brief  This is a status value returned by the function Mcu_GetPllStatus()
 *  of the MCU module.
 */
typedef enum
{
    /** \brief PLL locked */
    MCU_PLL_LOCKED = 0,
    /** \brief PLL unlocked */
    MCU_PLL_UNLOCKED,
    /** \brief PLL status undefined */
    MCU_PLL_STATUS_UNDEFINED
} Mcu_PllStatusType;

/* Requirements : SWS_Mcu_00256 */
/**
 *  \enum Mcu_RamStateType
 *  \brief  Enumeration of ranstate queried by Mcu_GetRamState()
 */
typedef enum
{
    /** \brief RAM state invalid */
    MCU_RAMSTATE_INVALID,
    /** \brief RAM state valid */
    MCU_RAMSTATE_VALID
} Mcu_RamStateType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief This service initializes the MCU driver
 *
 * Service ID[hex]   : 0x0
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] ConfigPtr - Pointer to MCU driver configuration set.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, MCU_CODE) Mcu_Init(P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_PBCFG) ConfigPtr);

#if (STD_ON == MCU_INIT_RAM_API)

/** \brief This service initializes the RAM section wise
 *
 * Service ID[hex]   : 0x01
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] RamSection - Selects RAM memory section provided in configuration set
 * \return Std_ReturnType
 * \retval E_OK - command has been accepted
 * \retval E_NOT_OK - command has not been accepted e.g. due to parameter error
 *
 *****************************************************************************/
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitRamSection(Mcu_RamSectionType RamSection);
#endif /* MCU_INIT_RAM_API */

#if (STD_ON == MCU_INIT_CLOCK_API)

/** \brief This service initializes the PLL and other MCU specific clock options
 *
 * Service ID[hex]   : 0x02
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] ClockSetting - Clock setting
 * \return Std_ReturnType
 * \retval E_OK - command has been accepted
 * \retval E_NOT_OK - command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitClock(Mcu_ClockType ClockSetting);
#endif /* MCU_INIT_CLOCK_API */

#if (STD_ON == MCU_PERFORM_RESET_API)

/** \brief The service performs a microcontroller reset
 *
 *
 * This function is the watchdog trigger and is invoked from WdgIsr
 *
 * Service ID[hex]   : 0x07
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
FUNC(void, MCU_CODE) Mcu_PerformReset(void);
#endif /* MCU_PERFORM_RESET_API */

/* Requirements: SWS_Mcu_00230 */

/** \brief This service provides the lock status of the PLL.
 * This function is provided as dummy. All PLL distribution activities
 * are being performed in Mcu_Init() to improve performance
 *
 * Service ID[hex]   : 0x03
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return Std_ReturnType
 * \retval E_OK - Success
 * \retval E_NOT_OK - Failure
 *
 *****************************************************************************/
FUNC(Std_ReturnType, MCU_CODE) Mcu_DistributePllClock(void);

/* Requirements: SWS_Mcu_00230 */

/** \brief This service provides the lock status of the PLL.
 *
 * Service ID[hex]   : 0x04
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return Mcu_PllStatusType - PLL Status
 * \retval Refer enum #Mcu_PllStatusType
 *
 *****************************************************************************/
FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_GetPllStatus(void);

/** \brief The service reads the reset type from the hardware, if supported
 *
 * Service ID[hex]   : 0x05
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return Mcu_ResetType
 * \retval Refer enum #Mcu_ResetType
 *
 *****************************************************************************/
FUNC(Mcu_ResetType, MCU_CODE) Mcu_GetResetReason(void);

/** \brief The service reads the reset type from the hardware register, if supported
 *
 * Service ID[hex]   : 0x06
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return Mcu_RawResetType - Reset raw value
 * \retval Refer #Mcu_RawResetType
 *
 *****************************************************************************/
FUNC(Mcu_RawResetType, MCU_CODE) Mcu_GetResetRawValue(void);

/** \brief This service activates the MCU power modes.
 * Supported low power modes - None
 *
 * Service ID[hex]   : 0x08
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] McuMode - MCU mode
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, MCU_CODE) Mcu_SetMode(Mcu_ModeType McuMode);

#if (STD_ON == MCU_GET_RAM_STATE_API)

/** \brief This service provides the actual status of the microcontroller Ram, if supported
 *
 * Service ID[hex]   : 0x0a
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return Mcu_RamStateType - Status of the Ram Content
 * \retval Refer enum #Mcu_RamStateType
 *
 *****************************************************************************/
FUNC(Mcu_RamStateType, MCU_CODE) Mcu_GetRamState(void);
#endif /* MCU_GET_RAM_STATE_API */

#if (STD_ON == MCU_GET_VERSION_INFO_API)

/** \brief This service returns the version information of this module
 *
 * Service ID[hex]   : 0x0B
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] versioninfo - Pointer to where to store the version information of this module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, MCU_CODE)
Mcu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA) versioninfo);
#endif /* MCU_GET_VERSION_INFO_API */

/** \brief This service is only used for UT testing and not for app use
 * This service sets the internal MCU initDone flag to
 * FALSE so that Mcu_Init can be invoked again.
 * This is required for negative UT test cases
 *
 * Service ID[hex]   : 0x09
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, MCU_CODE) Mcu_DeInit(void);

/** \brief This service is to read some of the config registers
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] RegisterReadbackPtr - Pointer to Register readback data
 * \return None
 * \retval E_OK Success
 * \retval E_NOT_OK Failure
 *
 *****************************************************************************/
#if (STD_ON == MCU_REGISTER_READBACK_API)
FUNC(Std_ReturnType, MCU_CODE)
Mcu_RegisterReadback(P2VAR(Mcu_RegisterReadbackType, AUTOMATIC, MCU_APPL_DATA) RegisterReadbackPtr);
#endif /* MCU_REGISTER_READBACK_API */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef MCU_H_ */
