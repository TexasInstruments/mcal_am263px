/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
#define LIN_CFG_MINOR_VERSION    (3U) //!< Lin configuration Minor Version.
#define LIN_CFG_PATCH_VERSION    (1U) //!< Lin configuration Patch Version.
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


/** \brief LIN ID used to transmit a header instead of a wakeup signal. 
 *   The hardware enters an undefined state when a standard wakeup signal is transmitted. 
 *   To mitigate this limitation, an unused header frame is utilized as the wakeup signal, which 
 *   conforms to the LIN 2.1 specification **/
#define LIN_WAKEUP_ID                    (0x3FU)

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


#define LIN_WAKEUP_SOURCE_0               (EcuM_WakeupSourceType)(0x00000020U)




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
/** \brief Interrupt line number */
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
   /** \brief LIN loopback disabled */
   LIN_LOOPBACK_DISABLED,
   /** \brief LIN loopback internal */
   LIN_LOOPBACK_INTERNAL,
   /** \brief LIN loopback external */
   LIN_LOOPBACK_EXTERNAL
} Lin_LoopbackModeType;

//*****************************************************************************
//
//! Lin Controller Configuration definition
//
//*****************************************************************************
typedef struct Lin_ControllerTag
{
   /** \brief Pointer to LinReg structure */
   uint32 CntrAddr;
   /** \brief Interrupt Line to be selected     */
   Lin_InterruptLineNum IntrLineNum;
   /** \brief Loopback Mode for this controller    */
   Lin_LoopbackModeType LoopbackMode;
} Lin_ControllerType;

//*****************************************************************************
//
//! Lin Controller BaudRate Configuration
//
//*****************************************************************************
typedef struct Lin_BaudrateConfigTag
{
   /** \brief Baud rate value */
   uint32 BaudRate;
   /** \brief Prescaler */
   uint32 Prescalar;
   /** \brief Fractional divider */
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
    uint32      Scigcr0;
    /**< IP revision identifier */
    uint32      Scigcr1;
    uint32      Scigcr2;
    /**< Control Register */

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
