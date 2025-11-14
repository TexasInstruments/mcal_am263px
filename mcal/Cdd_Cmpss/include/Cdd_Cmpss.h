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
 *  \file     Cdd_Cmpss.h
 *
 *  \brief    This file contains interface header for CMPSS (Compare Sub System)
 *            module CDD MCAL driver
 *
 */

/**
 *
 * \defgroup CDD_CMPSS CMPSS API
 *  @{
 */

#ifndef CDD_CMPSS_H_
#define CDD_CMPSS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cdd_Cmpss_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name CDD_CMPSS Driver Module SW Version Info
 *
 *  Defines for CDD_CMPSS Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_CMPSS_SW_MAJOR_VERSION (1U)
/** \brief Driver Implementation Minor Version */
#define CDD_CMPSS_SW_MINOR_VERSION (0U)
/** \brief Driver Implementation Patch Version */
#define CDD_CMPSS_SW_PATCH_VERSION (2U)
/** @} */

/**
 *  \name CDD_CMPSS Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD_CMPSS Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD_CMPSS Driver*/
#define CDD_CMPSS_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor version specification implemented by CDD_CMPSS Driver*/
#define CDD_CMPSS_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by CDD_CMPSS Driver*/
#define CDD_CMPSS_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/**
 *  \name CDD CMPSS Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define CDD_CMPSS_VENDOR_ID ((uint16)44U)
/** \brief CDD CMPSS Driver Module ID */
#define CDD_CMPSS_MODULE_ID ((uint16)255U)
/** \brief CDD CMPSS Instance ID */
#define CDD_CMPSS_INSTANCE_ID ((uint8)0U)
/** @} */

/**
 *  \name CDD CMPSS Error Codes
 *
 *  Error codes returned by CDD_CMPSS functions
 *  @{
 */
/** \brief API service called will null param pointer */
#define CDD_CMPSS_E_PARAM_POINTER ((uint8)0x01U)
/** \brief API service called with illegal HW ID */
#define CDD_CMPSS_E_ILLEGAL_HW_ID ((uint8)0x02U)
/** \brief API service called invalid configuration */
#define CDD_CMPSS_E_INVALID_CONFIG ((uint8)0x03U)
/** @} */

/**
 *  \name CDD CMPSS Service Id
 *
 *  The Service Id is one of the argument to Det_ReportError function and is
 *  used to identify the source of the error
 *  @{
 */
/** \brief Cdd_Cmpss_GetVersionInfo() API Service ID */
#define CDD_CMPSS_SID_GET_VERSION_INFO ((uint8)0U)
/** \brief Cdd_Cmpss_EnableModule() API Service ID */
#define CDD_CMPSS_SID_ENABLE_MODULE ((uint8)1U)
/** \brief Cdd_Cmpss_DisableModule() API Service ID */
#define CDD_CMPSS_SID_DISABLE_MODULE ((uint8)2U)
/** \brief Cdd_Cmpss_ConfigHighComparator() API Service ID */
#define CDD_CMPSS_SID_CONFIG_HIGH_COMPARATOR ((uint8)3U)
/** \brief Cdd_Cmpss_ConfigLowComparator() API Service ID */
#define CDD_CMPSS_SID_CONFIG_LOW_COMPARATOR ((uint8)4U)
/** \brief Cdd_Cmpss_ConfigOutputsHigh() API Service ID */
#define CDD_CMPSS_SID_CONFIG_OUTPUTS_HIGH ((uint8)5U)
/** \brief Cdd_Cmpss_ConfigOutputsLow() API Service ID */
#define CDD_CMPSS_SID_CONFIG_OUTPUTS_LOW ((uint8)6U)
/** \brief Cdd_Cmpss_GetStatus() API Service ID */
#define CDD_CMPSS_SID_GET_STATUS ((uint8)7U)
/** \brief Cdd_Cmpss_ConfigDAC() API Service ID */
#define CDD_CMPSS_SID_CONFIG_DAC ((uint8)8U)
/** \brief Cdd_Cmpss_SetDACValueHigh() API Service ID */
#define CDD_CMPSS_SID_SET_DAC_VALUE_HIGH ((uint8)9U)
/** \brief Cdd_Cmpss_SetDACValueLow() API Service ID */
#define CDD_CMPSS_SID_SET_DAC_VALUE_LOW ((uint8)10U)
/** \brief Cdd_Cmpss_InitFilterHigh() API Service ID */
#define CDD_CMPSS_SID_INIT_FILTER_HIGH ((uint8)11U)
/** \brief Cdd_Cmpss_InitFilterLow() API Service ID */
#define CDD_CMPSS_SID_INIT_FILTER_LOW ((uint8)12U)
/** \brief Cdd_Cmpss_GetDACValueHigh() API Service ID */
#define CDD_CMPSS_SID_GET_DAC_VALUE_HIGH ((uint8)13U)
/** \brief Cdd_Cmpss_GetDACValueLow() API Service ID */
#define CDD_CMPSS_SID_GET_DAC_VALUE_LOW ((uint8)14U)
/** \brief Cdd_Cmpss_ClearFilterLatchHigh() API Service ID */
#define CDD_CMPSS_SID_CLEAR_FILTER_LATCH_HIGH ((uint8)15U)
/** \brief Cdd_Cmpss_ClearFilterLatchLow() API Service ID */
#define CDD_CMPSS_SID_CLEAR_FILTER_LATCH_LOW ((uint8)16U)
/** \brief Cdd_Cmpss_SetMaxRampValue() API Service ID */
#define CDD_CMPSS_SID_SET_MAX_RAMP_VALUE ((uint8)17U)
/** \brief Cdd_Cmpss_GetMaxRampValue() API Service ID */
#define CDD_CMPSS_SID_GET_MAX_RAMP_VALUE ((uint8)18U)
/** \brief Cdd_Cmpss_SetRampDecValue() API Service ID */
#define CDD_CMPSS_SID_SET_RAMP_DEC_VALUE ((uint8)19U)
/** \brief Cdd_Cmpss_GetRampDecValue() API Service ID */
#define CDD_CMPSS_SID_GET_RAMP_DEC_VALUE ((uint8)20U)
/** \brief Cdd_Cmpss_SetRampDelayValue() API Service ID */
#define CDD_CMPSS_SID_SET_RAMP_DELAY_VALUE ((uint8)21U)
/** \brief Cdd_Cmpss_GetRampDelayValue() API Service ID */
#define CDD_CMPSS_SID_GET_RAMP_DELAY_VALUE ((uint8)22U)
/** \brief Cdd_Cmpss_ConfigBlanking() API Service ID */
#define CDD_CMPSS_SID_CONFIG_BLANKING ((uint8)23U)
/** \brief Cdd_Cmpss_EnableBlanking() API Service ID */
#define CDD_CMPSS_SID_ENABLE_BLANKING ((uint8)24U)
/** \brief Cdd_Cmpss_DisableBlanking() API Service ID */
#define CDD_CMPSS_SID_DISABLE_BLANKING ((uint8)25U)
/** \brief Cdd_Cmpss_EnableDEmode() API Service ID */
#define CDD_CMPSS_SID_ENABLE_DE_MODE ((uint8)26U)
/** \brief Cdd_Cmpss_DisableDEmode() API Service ID */
#define CDD_CMPSS_SID_DISABLE_DE_MODE ((uint8)27U)
/** \brief Cdd_Cmpss_SelectDEACTIVESource() API Service ID */
#define CDD_CMPSS_SID_SELECT_DEACTIVE_SOURCE ((uint8)28U)
/** \brief Cdd_Cmpss_ConfigHighDACShadowValue2() API Service ID */
#define CDD_CMPSS_SID_CONFIG_HIGH_DAC_SHADOW_VALUE2 ((uint8)29U)
/** \brief Cdd_Cmpss_ConfigLowDACShadowValue2() API Service ID */
#define CDD_CMPSS_SID_CONFIG_LOW_DAC_SHADOW_VALUE2 ((uint8)30U)
/** \brief Cdd_Cmpss_SetComparatorHighHysteresis() API Service ID */
#define CDD_CMPSS_SID_SET_COMPARATOR_HIGH_HYSTERESIS ((uint8)31U)
/** \brief Cdd_Cmpss_SetComparatorLowHysteresis() API Service ID */
#define CDD_CMPSS_SID_SET_COMPARATOR_LOW_HYSTERESIS ((uint8)32U)
/** \brief Cdd_Cmpss_ConfigFilterHigh() API Service ID */
#define CDD_CMPSS_SID_CONFIG_FILTER_HIGH ((uint8)33U)
/** \brief Cdd_Cmpss_ConfigFilterLow() API Service ID */
#define CDD_CMPSS_SID_CONFIG_FILTER_LOW ((uint8)34U)
/** \brief Cdd_Cmpss_ConfigLatchOnPWMSYNC() API Service ID */
#define CDD_CMPSS_SID_CONFIG_LATCH_ON_PWM_SYNC ((uint8)35U)
/** \brief Cdd_Cmpss_ConfigRamp() API Service ID */
#define CDD_CMPSS_SID_CONFIG_RAMP ((uint8)36U)
/** @} */

/*
 * Values that can be passed to Cdd_Cmpss_ConfigLowComparator() and
 * Cdd_Cmpss_ConfigHighComparator() as the Config parameter.
 */
/**
 *  \name CDD CMPSS High negative input source
 *
 *  CDD CMPSS High negative input source
 *  @{
 */
/** \brief Input driven by internal DAC */
#define CDD_CMPSS_INSRC_DAC (0x0000U)
/** \brief Input driven by external 'INL' pin  */
#define CDD_CMPSS_INSRC_PIN (0x0001U)
/** @} */

/**
 *  \name CDD CMPSS Low positive input source
 *
 *  CDD CMPSS Low positive input source
 *  @{
 */
/** \brief Input driven by external 'INL' pin */
#define CDD_CMPSS_INSRC_PIN_INL (0x0000U)
/** \brief Input driven by external 'INH' pin */
#define CDD_CMPSS_INSRC_PIN_INH (0x0001U)
/** @} */

/**
 *  \name CDD CMPSS Extra options
 *
 *  CDD CMPSS Extra options
 *  @{
 */
/** \brief Comparator output is inverted */
#define CDD_CMPSS_INV_INVERTED (0x0002U)
/** \brief Asynch comparator output feeds into OR with latched digital filter output */
#define CDD_CMPSS_OR_ASYNC_OUT_W_FILT (0x0040U)
/** @} */

/*
 * Values that can be passed to Cdd_Cmpss_ConfigOutputsLow() and
 * Cdd_Cmpss_ConfigOutputsHigh() as the Config parameter.
 */
/**
 *  \name CDD CMPSS Signal driving CTRIPOUT
 *
 *  CDD CMPSS Signal driving CTRIPOUT
 *  @{
 */
/** \brief Asynchronous comparator output drives CTRIPOUT */
#define CDD_CMPSS_TRIPOUT_ASYNC_COMP (0x0000U)
/** \brief Synchronous comparator output drives CTRIPOUT */
#define CDD_CMPSS_TRIPOUT_SYNC_COMP (0x0010U)
/** \brief Filter output drives CTRIPOUT */
#define CDD_CMPSS_TRIPOUT_FILTER (0x0020U)
/** \brief Latched filter output drives CTRIPOUT */
#define CDD_CMPSS_TRIPOUT_LATCH (0x0030U)
/** @} */

/**
 *  \name CDD CMPSS Signal driving CTRIPOUT
 *
 *  CDD CMPSS Signal driving CTRIPOUT
 *  @{
 */
/** \brief Asynchronous comparator output drives CTRIP */
#define CDD_CMPSS_TRIP_ASYNC_COMP (0x0000U)
/** \brief Synchronous comparator output drives CTRIP */
#define CDD_CMPSS_TRIP_SYNC_COMP (0x0004U)
/** \brief Filter output drives CTRIP */
#define CDD_CMPSS_TRIP_FILTER (0x0008U)
/** \brief Latched filter output drives CTRIP */
#define CDD_CMPSS_TRIP_LATCH (0x000CU)
/** @} */

/*
 * Values that can be returned by Cdd_Cmpss_GetStatus().
 */
/**
 *  \name CDD CMPSS Signal driving CTRIPOUT
 *
 *  CDD CMPSS Signal driving CTRIPOUT
 *  @{
 */
/** \brief High digital filter output */
#define CDD_CMPSS_STS_HI_FILTOUT (0x0001U)
/** \brief Latched value of high digital filter output */
#define CDD_CMPSS_STS_HI_LATCHFILTOUT (0x0002U)
/** \brief Low digital filter output */
#define CDD_CMPSS_STS_LO_FILTOUT (0x0100U)
/** \brief Latched value of low digital filter output */
#define CDD_CMPSS_STS_LO_LATCHFILTOUT (0x0200U)
/** @} */

/*
 * Values that can be passed to Cdd_Cmpss_ConfigDAC() the Config parameter.
 */
/**
 *  \name CDD CMPSS DAC Sync
 *
 *  CDD CMPSS value loaded from shadow register in DAC mode
 *  @{
 */
/** \brief DAC value updated from SYSCLK */
#define CDD_CMPSS_DACVAL_SYSCLK (0x0000U)
/** \brief DAC value updated from PWMSYNC */
#define CDD_CMPSS_DACVAL_PWMSYNC (0x0080U)
/** @} */

/**
 *  \name CDD CMPSS DAC reference voltage
 *
 *  CDD CMPSS DAC reference voltage
 *  @{
 */
/** \brief VDDA is the voltage reference */
#define CDD_CMPSS_DACREF_VDDA (0x0000U)
/** \brief VDAC is the voltage reference */
#define CDD_CMPSS_DACREF_VDAC (0x0020U)
/** @} */

/**
 *  \name CDD CMPSS DAC value source
 *
 *  CDD CMPSS DAC value source
 *  @{
 */
/** \brief DAC value updated from shadow register */
#define CDD_CMPSS_DACSRC_SHDW (0x0000U)
/** \brief DAC value is updated from the ramp register */
#define CDD_CMPSS_DACSRC_RAMP (0x0001U)
/** @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief CMPSS Ramp Config type */
typedef struct Cdd_Cmpss_RampConfigTypeTag
{
    /** \brief Ramp maximum reference value. */
    uint16  MaxRampVal;
    /** \brief Ramp decrement value */
    uint16  DecrementVal;
    /** \brief Ramp delay value */
    uint16  DelayVal;
    /** \brief Number of the PWMSYNC source */
    uint16  PwmSyncSrc;
    /** \brief Indicates if the max ramp shadow should be used */
    boolean UseRampValShdw;
} Cdd_Cmpss_RampConfigType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == CDD_CMPSS_VERSION_INFO_API)
/**
 * \brief Service that returns the version information of the module.
 *
 * \param[in] VersionInfo Pointer to where to store the version information of this module
 */
FUNC(void, CDD_CMPSS_CODE)
Cdd_Cmpss_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_CMPSS_DATA) VersionInfo);
#endif

/**
 * \brief Enables the CMPSS module.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 */
void Cdd_Cmpss_EnableModule(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Disables the CMPSS module.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 */
void Cdd_Cmpss_DisableModule(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Sets the configuration for the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Config is the configuration of the high comparator.
 *
 * This function configures a comparator. The \e Config parameter is the
 * result of a logical OR operation between a \b CDD_CMPSS_INSRC_xxx value and if
 * desired, \b CDD_CMPSS_INV_INVERTED and \b CDD_CMPSS_OR_ASYNC_OUT_W_FILT values.
 *
 * The \b CDD_CMPSS_INSRC_xxx term can take on the following values to specify
 * the high comparator negative input source:
 * - \b CDD_CMPSS_INSRC_DAC - The internal DAC.
 * - \b CDD_CMPSS_INSRC_PIN - External 'INL' pin.
 *       This is not applicable for CMPSSBx
 *
 * \b CDD_CMPSS_INV_INVERTED may be ORed into \e Config if the comparator output
 * should be inverted.
 *
 * \b CDD_CMPSS_OR_ASYNC_OUT_W_FILT may be ORed into \e Config if the
 * asynchronous comparator output should be fed into an OR gate with the
 * latched digital filter output before it is made available for CTRIPH or
 * CTRIPOUTH.
 */
void Cdd_Cmpss_ConfigHighComparator(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config);

/**
 * \brief Sets the configuration for the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Config is the configuration of the low comparator.
 *
 * This function configures a comparator.  The \e Config parameter is the
 * result of a logical OR operation between a \b CDD_CMPSS_INSRC_xxx value and if
 * desired, \b CDD_CMPSS_INV_INVERTED and \b CDD_CMPSS_OR_ASYNC_OUT_W_FILT values.
 *
 * The \b CDD_CMPSS_INSRC_xxx term can take on the following values to specify
 * the low comparator negative input source:
 * - \b CDD_CMPSS_INSRC_PIN_INL - External 'INL' pin.
 * - \b CDD_CMPSS_INSRC_PIN_INH - External 'INH' pin.
 *       This is not applicable for CMPSSBx
 *
 * \b CDD_CMPSS_INV_INVERTED may be ORed into \e Config if the comparator output
 * should be inverted.
 *
 * \b CDD_CMPSS_OR_ASYNC_OUT_W_FILT may be ORed into \e Config if the
 * asynchronous comparator output should be fed into an OR gate with the
 * latched digital filter output before it is made available for CTRIPL or
 * CTRIPOUTL.
 */
void Cdd_Cmpss_ConfigLowComparator(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config);

/**
 * \brief Sets the output signal configuration for the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Config is the configuration of the high comparator output signals.
 *
 * This function configures a comparator's output signals CTRIP and CTRIPOUT.
 * The \e Config parameter is the result of a logical OR operation between the
 * \b CDD_CMPSS_TRIPOUT_xxx and \b CDD_CMPSS_TRIP_xxx values.
 *
 * The \b CDD_CMPSS_TRIPOUT_xxx term can take on the following values to specify
 * which signal drives CTRIPOUTH:
 * - \b CDD_CMPSS_TRIPOUT_ASYNC_COMP - The asynchronous comparator output.
 * - \b CDD_CMPSS_TRIPOUT_SYNC_COMP - The synchronous comparator output.
 * - \b CDD_CMPSS_TRIPOUT_FILTER - The output of the digital filter.
 * - \b CDD_CMPSS_TRIPOUT_LATCH - The latched output of the digital filter.
 *
 * The \b CDD_CMPSS_TRIP_xxx term can take on the following values to specify
 * which signal drives CTRIPH:
 * - \b CDD_CMPSS_TRIP_ASYNC_COMP - The asynchronous comparator output.
 * - \b CDD_CMPSS_TRIP_SYNC_COMP - The synchronous comparator output.
 * - \b CDD_CMPSS_TRIP_FILTER - The output of the digital filter.
 * - \b CDD_CMPSS_TRIP_LATCH - The latched output of the digital filter.
 */
void Cdd_Cmpss_ConfigOutputsHigh(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config);

/**
 * \brief Sets the output signal configuration for the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Config is the configuration of the low comparator output signals.
 *
 * This function configures a comparator's output signals CTRIP and CTRIPOUT.
 * The \e Config parameter is the result of a logical OR operation between the
 * \b CDD_CMPSS_TRIPOUT_xxx and \b CDD_CMPSS_TRIP_xxx values.
 *
 * The \b CDD_CMPSS_TRIPOUT_xxx term can take on the following values to specify
 * which signal drives CTRIPOUTL:
 * - \b CDD_CMPSS_TRIPOUT_ASYNC_COMP - The asynchronous comparator output.
 * - \b CDD_CMPSS_TRIPOUT_SYNC_COMP - The synchronous comparator output.
 * - \b CDD_CMPSS_TRIPOUT_FILTER - The output of the digital filter.
 * - \b CDD_CMPSS_TRIPOUT_LATCH - The latched output of the digital filter.
 *
 * The \b CDD_CMPSS_TRIP_xxx term can take on the following values to specify
 * which signal drives CTRIPL:
 * - \b CDD_CMPSS_TRIP_ASYNC_COMP - The asynchronous comparator output.
 * - \b CDD_CMPSS_TRIP_SYNC_COMP - The synchronous comparator output.
 * - \b CDD_CMPSS_TRIP_FILTER - The output of the digital filter.
 * - \b CDD_CMPSS_TRIP_LATCH - The latched output of the digital filter.
 */
void Cdd_Cmpss_ConfigOutputsLow(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config);

/**
 * \brief Gets the current comparator status.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function returns the current status for the comparator, specifically
 * the digital filter output and latched digital filter output.
 *
 * \return Returns the current interrupt status, enumerated as a bit field of
 * the following values:
 * - \b CDD_CMPSS_STS_HI_FILTOUT - High digital filter output
 * - \b CDD_CMPSS_STS_HI_LATCHFILTOUT - Latched value of high digital filter
 *   output
 * - \b CDD_CMPSS_STS_LO_FILTOUT - Low digital filter output
 * - \b CDD_CMPSS_STS_LO_LATCHFILTOUT - Latched value of low digital filter output
 */
uint16 Cdd_Cmpss_GetStatus(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Sets the configuration for the internal comparator DACs.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Config is the configuration of the internal DAC.
 *
 * This function configures the comparator's internal DAC.  The \e Config
 * parameter is the result of a logical OR operation between the
 * \b CDD_CMPSS_DACVAL_xxx, \b CDD_CMPSS_DACREF_xxx, and \b CDD_CMPSS_DACSRC_xxx.
 *
 * The \b CDD_CMPSS_DACVAL_xxx term can take on the following values to specify
 * when the DAC value is loaded from its shadow register:
 * - \b CDD_CMPSS_DACVAL_SYSCLK - Value register updated on system clock.
 * - \b CDD_CMPSS_DACVAL_PWMSYNC - Value register updated on PWM sync.
 *
 * The \b CDD_CMPSS_DACREF_xxx term can take on the following values to specify
 * which voltage supply is used as reference for the DACs:
 * - \b CDD_CMPSS_DACREF_VDDA - VDDA is the voltage reference for the DAC.
 * - \b CDD_CMPSS_DACREF_VDAC - VDAC is the voltage reference for the DAC.
 *
 * The \b CDD_CMPSS_DACSRC_xxx term can take on the following values to specify
 * the DAC value source for the high comparator's internal DAC:
 * - \b CDD_CMPSS_DACSRC_SHDW - The user-programmed DACVALS register.
 * - \b CDD_CMPSS_DACSRC_RAMP - The ramp generator RAMPSTS register
 *
 * \note The \b CDD_CMPSS_DACVAL_xxx and \b CDD_CMPSS_DACREF_xxx terms apply to
 * both the high and low comparators. \b CDD_CMPSS_DACSRC_xxx will only affect
 * the high comparator's internal DAC.
 */
void Cdd_Cmpss_ConfigDAC(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config);

/**
 * \brief Sets the value of the internal DAC of the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Value is the value actively driven by the DAC.
 *
 * This function sets the 12-bit value driven by the internal DAC of the high
 * comparator. This function will load the value into the shadow register from
 * which the actual DAC value register will be loaded. To configure which
 * event causes this shadow load to take place, use \ref Cdd_Cmpss_ConfigDAC().
 */
void Cdd_Cmpss_SetDACValueHigh(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value);

/**
 * \brief Sets the value of the internal DAC of the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Value is the value actively driven by the DAC.
 *
 * This function sets the 12-bit value driven by the internal DAC of the low
 * comparator. This function will load the value into the shadow register from
 * which the actual DAC value register will be loaded. To configure which
 * event causes this shadow load to take place, use \ref Cdd_Cmpss_ConfigDAC().
 */
void Cdd_Cmpss_SetDACValueLow(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value);

/**
 * \brief Initializes the digital filter of the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function initializes all the samples in the high comparator digital
 * filter to the filter input value.
 *
 * \note See \ref Cdd_Cmpss_ConfigFilterHigh() for the proper initialization sequence
 * to avoid glitches.
 */
void Cdd_Cmpss_InitFilterHigh(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Initializes the digital filter of the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function initializes all the samples in the low comparator digital
 * filter to the filter input value.
 *
 * \note See Cdd_Cmpss_ConfigFilterLow() for the proper initialization sequence
 * to avoid glitches.
 */
void Cdd_Cmpss_InitFilterLow(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Gets the value of the internal DAC of the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function gets the value of the internal DAC of the high comparator.
 * The value is read from the \e active register--not the shadow register to
 * which \ref Cdd_Cmpss_SetDACValueHigh() writes.
 *
 * \return Returns the value driven by the internal DAC of the high comparator.
 */
uint16 Cdd_Cmpss_GetDACValueHigh(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Gets the value of the internal DAC of the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function gets the value of the internal DAC of the low comparator.
 * The value is read from the \e active register--not the shadow register to
 * which \ref Cdd_Cmpss_SetDACValueLow() writes.
 *
 * \return Returns the value driven by the internal DAC of the low comparator.
 */
uint16 Cdd_Cmpss_GetDACValueLow(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Causes a software reset of the high comparator digital filter output latch.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function causes a software reset of the high comparator digital filter
 * output latch. It will generate a single pulse of the latch reset signal.
 */
void Cdd_Cmpss_ClearFilterLatchHigh(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Causes a software reset of the low comparator digital filter output latch.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function causes a software reset of the low comparator digital filter
 * output latch. It will generate a single pulse of the latch reset signal.
 */
void Cdd_Cmpss_ClearFilterLatchLow(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Sets the ramp generator maximum reference value.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Value the ramp maximum reference value.
 *
 * This function sets the ramp maximum reference value that will be loaded
 * into the ramp generator.
 */
void Cdd_Cmpss_SetMaxRampValue(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value);

/**
 * \brief Gets the ramp generator maximum reference value.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * \return Returns the latched ramp maximum reference value that will be
 * loaded into the ramp generator.
 */
uint16 Cdd_Cmpss_GetMaxRampValue(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Sets the ramp generator decrement value.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Value is the ramp decrement value.
 *
 * This function sets the value that is subtracted from the ramp value on
 * every system clock cycle.
 */
void Cdd_Cmpss_SetRampDecValue(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value);

/**
 * \brief Gets the ramp generator decrement value.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * \return Returns the latched ramp decrement value that is subtracted from
 * the ramp value on every system clock cycle.
 */
uint16 Cdd_Cmpss_GetRampDecValue(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Sets the ramp generator delay value.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Value is the 13-bit ramp delay value.
 *
 * This function sets the value that configures the number of system clock
 * cycles to delay the start of the ramp generator decrementer after a PWMSYNC
 * event is received. Delay value can be no greater than 8191.
 */
void Cdd_Cmpss_SetRampDelayValue(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value);

/**
 * \brief Gets the ramp generator delay value.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * \return Returns the latched ramp delay value that is subtracted from
 * the ramp value on every system clock cycle.
 */
uint16 Cdd_Cmpss_GetRampDelayValue(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Sets the ePWM module blanking signal that holds trip in reset.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] PwmBlankSrc is the number of the PWMBLANK source.
 *
 * This function configures which PWMBLANK signal from the ePWM module will
 * hold trip in reset when blanking is enabled.
 *
 * The number of the PWMBLANK signal to be used to reset the ramp generator
 * should be specified by passing it into the \e PwmBlankSrc parameter. For
 * instance, passing a 2 into \e PwmBlankSrc will select PWMBLANK2.
 */
void Cdd_Cmpss_ConfigBlanking(Cdd_Cmpss_HwUnitType HwUnitId, uint16 PwmBlankSrc);

/**
 * \brief Enables an ePWM blanking signal to hold trip in reset.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function enables a selected ePWM blanking signal to hold trip in
 * reset.
 */
void Cdd_Cmpss_EnableBlanking(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Disables an ePWM blanking signal from holding trip in reset.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function disables a selected ePWM blanking signal from holding trip in
 * reset.
 */
void Cdd_Cmpss_DisableBlanking(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Enables the CDD_CMPSS diode emulation mode
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function enables the CMPSS diode emulation mode
 */
void Cdd_Cmpss_EnableDEmode(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Disables the CDD_CMPSS diode emulation mode
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 *
 * This function disables the CMPSS diode emulation mode
 */
void Cdd_Cmpss_DisableDEmode(Cdd_Cmpss_HwUnitType HwUnitId);

/**
 * \brief Select the CDD_CMPSS diode emulation mode DEACTIVE source
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] DeactiveSel is the DEACTIVE source select
 *
 * This function selects the CMPSS diode emulation mode DEACTIVE source
 */
void Cdd_Cmpss_SelectDEACTIVESource(Cdd_Cmpss_HwUnitType HwUnitId, uint8 DeactiveSel);

/**
 * \brief Sets the shadow value 2 (used in DE mode) of the internal DAC of the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] DacValue is the value actively driven by the DAC.
 *
 * This function sets the 12-bit value driven by the internal DAC of the high
 * comparator. This function will load the value into the shadow register 2 from
 * which the actual DAC value register will be loaded in DE mode.
 */
void Cdd_Cmpss_ConfigHighDACShadowValue2(Cdd_Cmpss_HwUnitType HwUnitId, uint16 DacValue);

/**
 * \brief Sets the shadow value 2 (used in DE mode) of the internal DAC of the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] DacValue is the value actively driven by the DAC.
 *
 * This function sets the 12-bit value driven by the internal DAC of the low
 * comparator. This function will load the value into the shadow register 2 from
 * which the actual DAC value register will be loaded in DE mode.
 */
void Cdd_Cmpss_ConfigLowDACShadowValue2(Cdd_Cmpss_HwUnitType HwUnitId, uint16 DacValue);

/**
 * \brief Sets the hysteresis value of the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Value is the hysteresis value.
 *     bit[15:4]:  unused.
 *     bit[3]   :  reserved.
 *     bit[2]   :  control which comparator output value the hysteresis is applied to
 *                 0 comparator hysteresis is applied when the comparator output is 1'b1
 *                 1 comparator hysteresis is applied when the comparator output is 1'b0
 *     bit[1:0] :
 *                 00  ==>     0 LSB       ==>     0mV,
 *                 01  ==>     17.5 LSB    ==>     14mV,
 *                 10  ==>     35 LSB      ==>     28mV,
 *                 11  ==>     52.5 LSB    ==>     42mV.
 *
 * This function sets the hysteresis value of the high comparator.
 */
void Cdd_Cmpss_SetComparatorHighHysteresis(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value);

/**
 * \brief Sets the hysteresis value of the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] Value is the hysteresis value.
 *     bit[15:4]:  unused.
 *     bit[3]   :  reserved.
 *     bit[2]   :  control which comparator output value the hysteresis is applied to
 *                 0 comparator hysteresis is applied when the comparator output is 1'b1
 *                 1 comparator hysteresis is applied when the comparator output is 1'b0
 *     bit[1:0] :
 *                 00  ==>     0 LSB       ==>     0mV,
 *                 01  ==>     17.5 LSB    ==>     14mV,
 *                 10  ==>     35 LSB      ==>     28mV,
 *                 11  ==>     52.5 LSB    ==>     42mV.
 *
 * This function sets the hysteresis value of the low comparator.
 */
void Cdd_Cmpss_SetComparatorLowHysteresis(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value);

/**
 * \brief Configures the digital filter of the high comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] SamplePrescale is the number of system clock cycles between samples.
 * \param[in] SampleWindow is the number of FIFO samples to monitor.
 * \param[in] Threshold is the majority Threshold of samples to change state.
 *
 * This function configures the operation of the digital filter of the high
 * comparator.
 *
 * The \e SamplePrescale parameter specifies the number of system clock cycles
 * between samples. It is a 10-bit value so a number higher than 1023 should
 * not be passed as this parameter. The prescale used by digital filter is 1
 * more than \e SamplePrescale value. So, the input provided should be 1 less
 * than the expected prescale.
 *
 * The \e SampleWindow parameter configures the size of the window of FIFO
 * samples taken from the input that will be monitored to determine when to
 * change the filter output. This sample window may be no larger than 32
 * samples.
 *
 * The \e Threshold parameter configures the Threshold value to be used by
 * the digital filter.
 *
 * The filter output resolves to the majority value of the sample window where
 * majority is defined by the value passed into the \e Threshold parameter.
 * For proper operation, the value of \e Threshold must be greater than
 * SampleWindow / 2.
 *
 * To ensure proper operation of the filter, the following is the recommended
 * function call sequence for initialization:
 *
 * -# Configure and enable the comparator using \ref Cdd_Cmpss_ConfigHighComparator()
 *    and \ref Cdd_Cmpss_EnableModule()
 * -# Configure the digital filter using \ref Cdd_Cmpss_ConfigFilterHigh()
 * -# Initialize the sample values using \ref Cdd_Cmpss_InitFilterHigh()
 * -# Configure the module output signals CTRIP and CTRIPOUT using
 *    \ref Cdd_Cmpss_ConfigOutputsHigh()
 */
void Cdd_Cmpss_ConfigFilterHigh(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale, uint16 SampleWindow,
                                uint16 Threshold);

/**
 * \brief Configures the digital filter of the low comparator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] SamplePrescale is the number of system clock cycles between samples.
 * \param[in] SampleWindow is the number of FIFO samples to monitor.
 * \param[in] Threshold is the majority Threshold of samples to change state.
 *
 * This function configures the operation of the digital filter of the low
 * comparator.
 *
 * The \e SamplePrescale parameter specifies the number of system clock cycles
 * between samples. It is a 10-bit value so a number higher than 1023 should
 * not be passed as this parameter. The prescale used by digital filter is 1
 * more than \e SamplePrescale value. So, the input provided should be 1 less
 * than the expected prescale.
 *
 * The \e SampleWindow parameter configures the size of the window of FIFO
 * samples taken from the input that will be monitored to determine when to
 * change the filter output. This sample window may be no larger than 32
 * samples.
 *
 * The \e Threshold parameter configures the Threshold value to be used by
 * the digital filter.
 *
 * The filter output resolves to the majority value of the sample window where
 * majority is defined by the value passed into the \e Threshold parameter.
 * For proper operation, the value of \e Threshold must be greater than
 * SampleWindow / 2.
 *
 * To ensure proper operation of the filter, the following is the recommended
 * function call sequence for initialization:
 *
 * -# Configure and enable the comparator using \ref Cdd_Cmpss_ConfigLowComparator()
 *    and \ref Cdd_Cmpss_EnableModule()
 * -# Configure the digital filter using \ref Cdd_Cmpss_ConfigFilterLow()
 * -# Initialize the sample values using \ref Cdd_Cmpss_InitFilterLow()
 * -# Configure the module output signals CTRIP and CTRIPOUT using
 *    \ref Cdd_Cmpss_ConfigOutputsLow()
 */
void Cdd_Cmpss_ConfigFilterLow(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale, uint16 SampleWindow,
                               uint16 Threshold);

/**
 * \brief Configures whether or not the digital filter latches are reset by PWMSYNC
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] HighEnable indicates filter latch settings in the high comparator.
 * \param[in] LowEnable indicates filter latch settings in the low comparator.
 *
 * This function configures whether or not the digital filter latches in both
 * the high and low comparators should be reset by PWMSYNC. If the
 * \e HighEnable parameter is \b true, the PWMSYNC will be allowed to reset
 * the high comparator's digital filter latch. If it is false, the ability of
 * the PWMSYNC to reset the latch will be disabled. The \e LowEnable parameter
 * has the same effect on the low comparator's digital filter latch.
 */
void Cdd_Cmpss_ConfigLatchOnPWMSYNC(Cdd_Cmpss_HwUnitType HwUnitId, boolean HighEnable, boolean LowEnable);

/**
 * \brief Configures the comparator subsystem's ramp generator.
 *
 * \param[in] HwUnitId HW ID. This param should be less than CDD_CMPSS_HW_UNIT_MAX
 * \param[in] RampConfigPtr Pointer to the ramp configuration parameter. This should not be NULL.
 *
 * This function configures many of the main settings of the comparator
 * subsystem's ramp generator. The \e MaxRampVal parameter should be passed
 * the ramp maximum reference value that will be loaded into the ramp
 * generator. The \e DecrementVal parameter should be passed the decrement
 * value that will be subtracted from the ramp generator on each system clock
 * cycle. The \e DelayVal parameter should be passed the 13-bit number of
 * system clock cycles the ramp generator should delay before beginning to
 * decrement the ramp generator after a PWMSYNC signal is received.
 *
 * These three values may be be set individually using the
 * \ref Cdd_Cmpss_SetMaxRampValue(), \ref Cdd_Cmpss_SetRampDecValue(), and
 * \ref Cdd_Cmpss_SetRampDelayValue() APIs.
 *
 * The number of the PWMSYNC signal to be used to reset the ramp generator
 * should be specified by passing it into the \e PwmSyncSrc parameter. For
 * instance, passing a 2 into \e PwmSyncSrc will select PWMSYNC2.
 *
 * To indicate whether the ramp generator should reset with the value from the
 * ramp max reference value shadow register or with the latched ramp max
 * reference value, use the \e UseRampValShdw parameter. Passing it \b true
 * will result in the latched value being bypassed. The ramp generator will be
 * loaded right from the shadow register. A value of \b false will load the
 * ramp generator from the latched value.
 */
void Cdd_Cmpss_ConfigRamp(Cdd_Cmpss_HwUnitType HwUnitId, const Cdd_Cmpss_RampConfigType *RampConfigPtr);

#ifdef __cplusplus
}
#endif

#endif /* CDD_CMPSS_H_ */

/** @} */
