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
#define LIN_CFG_MAJOR_VERSION    (10U) //!< Lin configuration Major Version.
#define LIN_CFG_MINOR_VERSION    (1U) //!< Lin configuration Minor Version.
#define LIN_CFG_PATCH_VERSION    (0U) //!< Lin configuration Patch Version.
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
#define LIN_PRE_COMPILE_VARIANT          (STD_OFF)

#define LIN_POST_BUILD_VARIANT           (STD_ON)
/* @} */



/**
 *  \name Pre-Compile Switches for API Services
 *  @{
 */
//*****************************************************************************
//
//! \brief Enable/Disable DEV error detection.
//
//*****************************************************************************
#define LIN_DEV_ERROR_DETECT             (STD_ON)

//*****************************************************************************
//
//! \brief Enable/Disable Lin_GetVersionInfo().
//
//*****************************************************************************
#define LIN_GET_VERSION_INFO_API         (STD_ON)

//*****************************************************************************
//
//! \brief Enable/Disable LIN RegisterReadback API.
//
//*****************************************************************************
#define LIN_REGISTER_READBACK_API         (STD_ON)
/* @} */

//*****************************************************************************
//
//! \brief Lin Instance to Channel ID mapping.
//
//*****************************************************************************
#define LIN_INSTANCE_1                    0

//*****************************************************************************
//
//! \brief Lin Channel Symbolic Names.
//
//*****************************************************************************
#define LinConf_LinChannel_LinChannel_1       0

//*****************************************************************************
//
//! \brief Lin Channel Interrupt Line Selection.
//
//*****************************************************************************
#define LIN_INSTANCE_1_LINE_NUM_0                  

//*****************************************************************************
//
//! \brief Lin Channel ISR Type Selection.
//
//*****************************************************************************
#define LIN_INSTANCE_1_ISR_TYPE           LIN_ISR_CAT1



//*****************************************************************************
//
//! \brief Lin Channel ISR Type Selection.
//
//*****************************************************************************


#define LIN_WAKEUP_SOURCE_0           EcuMConf_EcuMWakeupSource_LIN1




//*****************************************************************************
//
//! \brief Max number of channels defined
//
//*****************************************************************************
#define LIN_MAX_CHANNEL                      (1U)

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
extern const struct Lin_ConfigTag LinGlobalConfig;

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
