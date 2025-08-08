/* =============================================================================
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
 * ========================================================================== */

/**
 *   \file     Port.h
 *
 *   \brief    This file contains interface header for PORT MCAL driver
 *
 */
/*  ----------------------------------------------------------------------------
.*   FILE DESCRIPTION
.*  ----------------------------------------------------------------------------
.*   File:  Port.h
.*   Project:  AM263 MCAL Driver
.*   Module:  PortDriver
.*
.*   Description:  This module implements a driver in ANSI C programming language
.*                 to centralize the configuration of ports and pins which are
.*                 used by more than one driver module.
.*                 With this driver you can:
.*                 - Configure all port pins
.*                 - Initialize the configuration
.*                 - Refresh the configuration (EMC purposes)
.*                 - Switch the port pin configuration during runtime*/
/*****************************************************************************/

#ifndef PORT_H_
#define PORT_H_

/**
 * \defgroup PORT Port API GUIDE Header file
 * @{
 */

/*
 *Design: MCAL-14044
 */

/* ========================================================================== */
/*                          Include Files                                     */
/* ========================================================================== */

#include "Std_Types.h"
#include "Port_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *   \name PORT Driver Module SW Version Info
 *
 *   Defines for PORT Driver version used for compatibility checks
 *   @{
 */
/** \brief Driver Implementation Major Version */
#define PORT_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define PORT_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation Patch Version */
#define PORT_SW_PATCH_VERSION (0U)
/**   @} */

/**
 *   \name PORT Driver Module AUTOSAR Version Info
 *
 *   Defines for PORT Driver AUTOSAR version used for compatibility checks
 *   @{
 */
/** \brief AUTOSAR Major version specification implemented by PORT Driver  */
#define PORT_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by PORT Driver */
#define PORT_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by PORT Driver  */
#define PORT_AR_RELEASE_REVISION_VERSION (1U)
/**  @} */

/**
 *   \name PORT Driver ID Info
 *   @{
 */
/** \brief Texas Instruments Vendor ID */
#define PORT_VENDOR_ID ((uint16)44U)
/** \brief PORT Driver Module ID */
#define PORT_MODULE_ID ((uint16)124U)
/** \brief PORT Driver Instance ID */
#define PORT_INSTANCE_ID (0U)
/**  @} */

/*
 *Design: MCAL-14001
 */
/**
 *   \name PORT Error Codes
 *
 *   Error codes returned by Driver functions
 *   @{
 */
#ifndef PORT_E_PARAM_PIN
/** \brief ERROR: Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN ((uint8)0x0AU)
#endif /* #ifndef PORT_E_PARAM_PIN */

#ifndef PORT_E_DIRECTION_UNCHANGEABLE
/** \brief ERROR:Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE ((uint8)0x0BU)
#endif /* #ifndef PORT_E_DIRECTION_UNCHANGEABLE */

#ifndef PORT_E_INIT_FAILED
/** \brief ERROR:Init service called with wrong parameter */
#define PORT_E_INIT_FAILED ((uint8)0x0CU)
#endif /* #ifndef PORT_E_INIT_FAILED */

#ifndef PORT_E_PARAM_INVALID_MODE
/** \brief ERROR:Invalid mode setting for PORT pin */
#define PORT_E_PARAM_INVALID_MODE ((uint8)0x0DU)
#endif /* #ifndef PORT_E_PARAM_INVALID_MODE */

#ifndef PORT_E_MODE_UNCHANGEABLE
/** \brief ERROR:PORT pin disallows mode change */
#define PORT_E_MODE_UNCHANGEABLE ((uint8)0x0EU)
#endif /* #ifndef PORT_E_MODE_UNCHANGEABLE */

#ifndef PORT_E_UNINIT
/** \brief ERROR:PORT API called without init being invoked */
#define PORT_E_UNINIT ((uint8)0x0FU)
#endif /* #ifndef PORT_E_UNINIT */

#ifndef PORT_E_PARAM_POINTER
/** \brief ERROR:API invoked with NULL_PTR */
#define PORT_E_PARAM_POINTER ((uint8)0x10U)
#endif /* #ifndef PORT_E_PARAM_POINTER */

#ifndef PORT_E_INVALID_GPIO_PORT_ADDRESS
/** \brief ERROR:API invoked with INVALID gpio port address */
#define PORT_E_INVALID_GPIO_PORT_ADDRESS ((uint8)0x11U)
#endif /* #ifndef PORT_E_INVALID_GPIO_PORT_ADDRESS */
/**   @} */

/**
 *   \name PORT Service Ids
 *
 *   The Service Id is one of the argument to Det_ReportError function and is
 *   used to identify the source of the error
 *   @{
 */
/* PORT API service identification */
/** \brief Port_Init() */
#define PORT_SID_INIT ((uint8)0x0U)
/** \brief Port_SetPinDirection() */
#define PORT_SID_SET_PIN_DIR ((uint8)0x1U)
/** \brief Port_RefreshPortDirection() */
#define PORT_SID_REFRESH_PORT_DIR ((uint8)0x2U)
/** \brief Port_GetVersionInfo() */
#define PORT_SID_GET_VERSION_INFO ((uint8)0x3U)
/** \brief Port_SetPinMode() */
#define PORT_SID_SET_PIN_MODE ((uint8)0x4U)

/** \brief Port_PinEnableIntrNotification() */
#define PORT_SID_ENABLE_INTR ((uint8)0x5U)

/** \brief Port_PinDisableIntrNotification() */
#define PORT_SID_DISABLE_INTR ((uint8)0x6U)

/** \brief Port_GetInterruptStatus() */
#define PORT_SID_GET_INTR_ST ((uint8)0x7U)

/** \brief Port_ClearInterruptStatus() */
#define PORT_SID_CLR_INTR_ST ((uint8)0x8U)

/** @} */

/**
 *   \name PORT DIO related defines
 *   @{
 */
/**
 *   \brief PORT DIO Invalid GPIO register Id
 */
#define PORT_DIO_INVALID_REG_ID (0xFFU)

/**
 *   \brief PORT DIO Invalid GPIO Channel Id
 */
#define PORT_DIO_INVALID_CH_ID (0xFFU)
/**   @} */

/** \brief Valid Port width */
#define PORT_GPIO_PORT_WIDTH (0x8U)

/**
 *  \name PORT Driver ISR category level
 *
 *  Defines for PORT Driver ISR category level
 *  @{
 */
/** \brief void ISR type */
#define PORT_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define PORT_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define PORT_ISR_CAT2 (0x02U)
/**   @} */

#if (STD_ON == PORT_SAFETI_API)
/** \brief Structure for Cfg Registers */
typedef struct
{
    uint32 configRegs[10];
} Port_ConfigRegsType;
#endif /* #if (STD_ON == PORT_SAFETI_API) */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *   \brief Enum of Dio module data direction control
 */
typedef enum
{
    /** \brief Input direction */
    PORT_DIO_DATA_DIRECTION_INPUT,
    /** \brief Output direction */
    PORT_DIO_DATA_DIRECTION_OUTPUT,
    /** \brief Default direction */
    PORT_DIO_DATA_DIRECTION_DEFAULT
} Port_DioDataDir;

/**
 *   \brief Enum of DIO module Data Input register that reflects the current state of the pins
 */
typedef enum
{
    /** \brief Input Low state */
    PORT_DIO_DATA_INPUT_LOW,
    /** \brief Input High state */
    PORT_DIO_DATA_INPUT_HIGH,
    /** \brief Input default state */
    PORT_DIO_DATA_INPUT_DEFAULT
} Port_DioDataIn;

/**
 *   \brief Enum of DIO module Data Output register that specify the output state of the
 *   pins when configured as output
 */
typedef enum
{
    /** \brief Output Low state */
    PORT_DIO_DATA_OUTPUT_LOW,
    /** \brief Output Low state */
    PORT_DIO_DATA_OUTPUT_HIGH,
    /** \brief Output Low state */
    PORT_DIO_DATA_OUTPUT_DEFAULT
} Port_DioDataOut;

/**
 *   \brief Enum of DIO module Open drain capability
 */
typedef enum
{
    /** \brief Push Pull Mode */
    PORT_DIO_PDR_PUSHPULL_MODE,
    /** \brief Open drain Mode */
    PORT_DIO_PDR_OPEN_DRAIN_MODE,
    /** \brief Default Mode */
    PORT_DIO_PDR_DEFAULT
} Port_DioOpenDrain_Mode;

/**
 *   \brief Enum of DIO module SINGLE/BOTH Edge trigger interrupt
 */
typedef enum
{
    /** \brief Single edge trigger interrupt */
    PORT_DIO_SINGLE_EDGE_INTERRUPT,
    /** \brief Both edge trigger interrupt */
    PORT_DIO_BOTH_EDGE_INTERRUPT,
    /** \brief Default interrupt */
    PORT_DIO_DEFAULT_INTERRUPT
} Port_DioIntrDET;

/**
 *   \brief Enum of DIO module Rising/Falling edge interrupt
 */
typedef enum
{
    /** \brief Falling edge interrupt */
    PORT_DIO_FALLING_EDGE_INTERRUPT,
    /** \brief Rising edge interrupt */
    PORT_DIO_RISING_EDGE_INTERRUPT,
    /** \brief Default edge interrupt */
    PORT_DIO_DEFAULT_EDGE_INTERRUPT
} Port_DioIntrPol;

/**
 *   \brief Enum of DIO module high/low level  interrupt
 */
typedef enum
{
    /** \brief Low level interrupt */
    PORT_DIO_LOW_LEVEL_INTERRUPT,
    /** \brief High level interrupt */
    PORT_DIO_HIGH_LEVEL_INTERRUPT,
    /** \brief Default level interrupt */
    PORT_DIO_DEFAULT_LEVEL_INTERRUPT
} Port_DioIntrLvl;

/**
 *   \brief Enum of DIO module idle mode configuration
 */
typedef enum
{
    /** \brief IdleMode : Do not configure IDLEMODE. Retains default
     *configuration */
    PORT_DIO_IDLEMODE_DEFAULT,
} Port_DioIdleModeType;

/**
 *   \brief Enum of DIO module Clock gating ratio for event detection
 */
typedef enum
{
    /** \brief Clock gating ratio for event detection */
    PORT_DIO_UNGATE = 0xFFFF,
} Port_DioClockGatingRatioType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Initializes the Port Driver module
 *
 *
 * Service ID[hex] - 0x00
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[in] ConfigPtr - Pointer to configuration set.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PORT_CODE) Port_Init(P2CONST(Port_ConfigType, AUTOMATIC, PORT_PBCFG) ConfigPtr);
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
/** \brief Sets the port pin direction
 *
 *
 * Service ID[hex] - 0x01
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[in] Pin - Port Pin ID number
 * \param[in] Direction - Port_SetPinDirection
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PORT_CODE) Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif /* ( STD_ON == PORT_SET_PIN_DIRECTION_API ) */

#if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API)
/** \brief Refreshes port direction
 *
 *
 * Service ID[hex] - 0x02
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PORT_CODE) Port_RefreshPortDirection(void);
#endif /*( STD_ON == PORT_REFRESH_PORT_DIRECTION_API )*/

#if (STD_ON == PORT_SET_PIN_MODE_API)
/** \brief Sets the port pin mode
 *
 *
 * Service ID[hex] - 0x04
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[in] Pin - Port Pin ID number
 * \param[in] Mode - New Port Pin mode to be set on port pin
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PORT_CODE) Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif /*( STD_ON == PORT_SET_PIN_MODE_API )*/

#if (STD_ON == PORT_VERSION_INFO_API)
/** \brief Returns the version information of this module
 *
 *
 *
 * Service ID[hex] - 0x03
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[out] versioninfo - Pointer to where to store the version information
 * of this module
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PORT_CODE)
Port_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versioninfo);
#endif /*(STD_ON == PORT_VERSION_INFO_API)*/

/** \brief This service sets the internal PORT initDone flag to FALSE so
 * that Port_Init can be invoked again. This is required for
 * negative UT test cases
 *
 *
 * This service is only used for UT testing and not for app use
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, PORT_CODE) Port_DeInit(void);

/** \brief This service returns current/initial configuration items as from
 * the GUI.
 *
 *
 * Function could be called from interrupt level or from task level,
 * Output parameter must not be NULL_PTR, TRUE/FALSE should be passed
 *  as initial parameter.
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Non Reentrant
 *
 * \param[in] initial
 * \param[out] ConfigRegPtr - pointer to store the configuration read from GUI
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == PORT_SAFETI_API)
FUNC(void, PORT_PBCODE)
Port_GetConfigRegValues(uint8 initial, P2VAR(Port_ConfigRegsType, AUTOMATIC, PORT_PBCFG) ConfigRegPtr);

#endif /* (STD_ON == PORT_SAFETI_API) */

/** \brief Enable Port Interrupt Functionality
 *
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[in] Pin - GPIO Pin Number
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_PinEnableIntrNotification(Port_PinType Pin);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

/** \brief Disable Port Interrupt Functionality
 *
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[in] Pin - GPIO Pin Number
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_PinDisableIntrNotification(Port_PinType Pin);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

/** \brief Get Interrupt Status
 *
 *
 * Read Bank Interrupt Status Register (INTSTAT)
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[in] bankIdx - GPIO Bank Number (BankA_0 to BankI_8)
 * \return uint32
 * \retval INTSTAT Register Value
 *
 *****************************************************************************/
#if (STD_ON == PORT_GET_INTR_ST_API)
uint32 Port_GetInterruptStatus(Port_PinType bankIdx);
#endif /* #if (STD_ON == PORT_GET_INTR_ST_API) */

/** \brief Clear Interrupt Status
 *
 *
 * Clear Bank Interrupt Status Register (INTSTAT)
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy  - Reentrant
 *
 * \param[in] bankIdx - GPIO Bank Number (BankA_0 to BankI_8)
 * \param[in] maskValue - Bits Mask Value
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == PORT_CLR_INTR_ST_API)
void Port_ClearInterruptStatus(Port_PinType bankIdx, uint32 maskValue);
#endif /* #if (STD_ON == PORT_CLR_INTR_ST_API) */

#ifdef __cplusplus
}
#endif /* #if (STD_ON == PORT_SAFETI_API) */

/**
 * @}
 */

#endif /* #ifndef PORT_H_ */
