/*********************************************************************************************************************
 *  COPYRIGHT
 *  ------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright 2023 Texas Instruments Inc.  All rights reserved.
 *
 *  \endverbatim
 *  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *  File:       Lin_Cfg.h
 *  Project:    AM263Px MCAL
 *  Module:     Lin Driver
 *  Generator:  Elektrobit Tresos
 *
 *  Description:  This file contains generated configuration data
 *
 *********************************************************************************************************************/

#ifndef LIN_CFG_H
#define LIN_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup LIN Lin
 * @{
 */

 #ifndef DOXYGEN_SHOULD_SKIP_THIS

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Other Header Files
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Version Check (if required)
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Exported Preprocessor #define Constants
 *********************************************************************************************************************/
//*****************************************************************************
//
//! \brief Lin Driver Configuration SW Version Info.
//
//*****************************************************************************
/**
 *  \name LIN Driver Configuration SW Version Info
 *
 *  Defines for LIN Driver configuration version
 *  @{
 */
#define LIN_CFG_MAJOR_VERSION    ([!"substring-before($moduleSoftwareVer,'.')"!]U) //!< Lin configuration Major Version.
#define LIN_CFG_MINOR_VERSION    ([!"substring-before(substring-after($moduleSoftwareVer,'.'),'.')"!]U) //!< Lin configuration Minor Version.
#define LIN_CFG_PATCH_VERSION    ([!"substring-after(substring-after($moduleSoftwareVer,'.'),'.')"!]U) //!< Lin configuration Patch Version.
/* @} */


//*****************************************************************************
//
//! \brief LIN Build Variant. Build Variants.(i.e Pre-compile,Post-Build or Link time)
//
//*****************************************************************************
/**
 *  \name LIN Build Variant
 *
 *  Defines for LIN Driver configuration version
 *  @{
 */
#define LIN_PRE_COMPILE_VARIANT          [!IF "as:modconf('Lin')[1]/IMPLEMENTATION_CONFIG_VARIANT = 'VariantPreCompile'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

#define LIN_POST_BUILD_VARIANT           [!IF "as:modconf('Lin')[1]/IMPLEMENTATION_CONFIG_VARIANT = 'VariantPostBuild'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* @} */
[!IF "as:modconf('Lin')[1]/IMPLEMENTATION_CONFIG_VARIANT = 'VariantPreCompile'"!]
//*****************************************************************************
//
//! \brief Pointer to Lin Config Set to be used during Pre-Compile
//
//*****************************************************************************
#define LIN_INIT_CONFIG_PC                   Lin_Config
[!ENDIF!]


/**
 *  \name Pre-Compile Switches for API Services
 *  @{
 */
//*****************************************************************************
//
//! \brief Enable/Disable DEV error detection.
//
//*****************************************************************************
#define LIN_DEV_ERROR_DETECT             [!IF "as:modconf('Lin')[1]/LinGeneral/LinDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

//*****************************************************************************
//
//! \brief Enable/Disable Lin_GetVersionInfo().
//
//*****************************************************************************
#define LIN_GET_VERSION_INFO_API         [!IF "as:modconf('Lin')[1]/LinGeneral/LinVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

//*****************************************************************************
//
//! \brief Enable/Disable LIN RegisterReadback API.
//
//*****************************************************************************
#define LIN_REGISTER_READBACK_API         [!IF "as:modconf('Lin')[1]/LinGeneral/LinEnableRegisterReadbackApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* @} */

//*****************************************************************************
//
//! \brief Lin Instance to Channel ID mapping.
//
//*****************************************************************************
[!LOOP "as:modconf('Lin')[1]/LinGlobalConfig/LinChannel/*"!][!//
#define [!"LinInstance"!]                    [!"LinChannelId"!]
[!ENDLOOP!][!//

//*****************************************************************************
//
//! \brief Lin Channel Symbolic Names.
//
//*****************************************************************************
[!LOOP "as:modconf('Lin')[1]/LinGlobalConfig/LinChannel/*"!][!//
#define LinConf_LinChannel_[!"@name"!]       [!"LinChannelId"!]
[!ENDLOOP!][!//

//*****************************************************************************
//
//! \brief Lin Channel Interrupt Line Selection.
//
//*****************************************************************************
[!LOOP "as:modconf('Lin')[1]/LinGlobalConfig/LinChannel/*"!][!//
#define [!"LinInstance"!]_[!"substring-after(LinInterruptLineSelect, 'LIN_INTERRUPT_')"!]
[!ENDLOOP!][!//

//*****************************************************************************
//
//! \brief Lin Channel ISR Type Selection.
//
//*****************************************************************************
[!LOOP "as:modconf('Lin')[1]/LinGlobalConfig/LinChannel/*"!][!//
#define [!"LinInstance"!]_ISR_TYPE           [!"LinISRType"!]
[!ENDLOOP!][!//



//*****************************************************************************
//
//! \brief Lin Channel ISR Type Selection.
//
//*****************************************************************************
[!LOOP "as:modconf('Lin')[1]/LinGlobalConfig/LinChannel/*"!]
[!IF "node:refvalid(LinChannelEcuMWakeupSource)"!]
#define LIN_WAKEUP_SOURCE_[!"LinChannelId"!]           EcuMConf_EcuMWakeupSource_[!"node:name(node:ref(LinChannelEcuMWakeupSource))"!]
[!ENDIF!]
[!ENDLOOP!]


//*****************************************************************************
//
//! \brief Max number of channels defined
//
//*****************************************************************************
#define LIN_MAX_CHANNEL                      ([!"num:i(count(as:modconf('Lin')[1]/LinGlobalConfig/LinChannel/*))"!]U)

/*********************************************************************************************************************
 * Exported Preprocessor #define Macros
 *********************************************************************************************************************/
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/*********************************************************************************************************************
 * Exported Type Declarations
 *********************************************************************************************************************/

/** \brief Interrupt Line number */
 typedef enum
{
   /** \brief Use Interrupt Line 0 */
   LIN_INTERRUPT_LINE_NUM_0 = 0x0U,
   /** \brief Use Interrupt Line 1 */
   LIN_INTERRUPT_LINE_NUM_1 = 0x1U
} Lin_InterruptLineNum;

/** \brief Loopback mode type */
typedef enum Lin_LoopbackModeTag
{
   /** \brief Loopback disabled */
   LIN_LOOPBACK_DISABLED,
   /** \brief Loopback Internal */
   LIN_LOOPBACK_INTERNAL,
   /** \brief Loopback External */
   LIN_LOOPBACK_EXTERNAL
} Lin_LoopbackModeType;

//*****************************************************************************
//
//! Lin Controller Configuration definition
//
//*****************************************************************************
typedef struct Lin_ControllerTag
{
   /** \brief Pointer to LinReg structure*/
   uint32 CntrAddr;
   /** \brief Interrupt Line to be selected    */
   Lin_InterruptLineNum IntrLineNum;
   /** \brief Loopback Mode for this controller   */
   Lin_LoopbackModeType LoopbackMode;
} Lin_ControllerType;

//*****************************************************************************
//
//! Lin Controller BaudRate Configuration
//
//*****************************************************************************
typedef struct Lin_BaudrateConfigTag
{
   /** \brief Prescaler*/
   uint32 Prescalar;
   /** \brief Fractional divider*/
   uint32 FractionalDivider;
} Lin_BaudRateConfigType;

/*********************************************************************************************************************
 * Exported Object Declarations
 *********************************************************************************************************************/
/** \brief LIN Configuration struct declaration */
extern const struct Lin_ConfigTag Lin_Config;

#if (STD_ON == LIN_REGISTER_READBACK_API)
/**
 *  \brief LIN register readback structure
 *
 */
typedef struct
{
    /*
     * Lin related registers
     */
    /** \brief IP revision identifier */
    uint32      Scigcr0;
    /** \brief Control Register */
    uint32      Scigcr1;
    /** \brief Control Register */
    uint32      Scigcr2;


} Lin_RegisterReadbackType;
#endif  /* #if (STD_ON == LIN_REGISTER_READBACK_API) */

/*********************************************************************************************************************
 *  Exported Function Prototypes
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  Exported Inline Function Definitions and Function-Like Macros
 *********************************************************************************************************************/

#ifdef __cplusplus
}
#endif

/**
* @}
*/

#endif /* LIN_CFG_H */
/*********************************************************************************************************************
 *  End of File: Lin_Cfg.h
 *********************************************************************************************************************/
