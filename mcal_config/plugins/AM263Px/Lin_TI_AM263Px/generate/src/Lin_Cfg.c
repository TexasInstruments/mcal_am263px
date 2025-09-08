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
 *  File:       Lin_Cfg.c
 *  Project:    AM263Px MCAL
 *  Module:     Lin Driver
 *  Generator:  Elektrobit Tresos
 *
 *  Description:  This file contains generated post build configuration data
 *
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/
#include "EcuM_Cbk.h"
#include "Lin.h"

/*********************************************************************************************************************
 * Other Header Files
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Version Check (if required)
 *********************************************************************************************************************/
//*****************************************************************************
//
// AUTOSAR version information check.
//
//*****************************************************************************
#if ((LIN_SW_MAJOR_VERSION != ([!"substring-before($moduleSoftwareVer,'.')"!]U)) || (LIN_SW_MINOR_VERSION != ([!"substring-before(substring-after($moduleSoftwareVer,'.'),'.')"!]U)))
  #error "Version numbers of Lin_Cfg.c and Lin.h are inconsistent!"
#endif

#if ((LIN_CFG_MAJOR_VERSION != ([!"substring-before($moduleSoftwareVer,'.')"!]U)) || (LIN_CFG_MINOR_VERSION != ([!"substring-before(substring-after($moduleSoftwareVer,'.'),'.')"!]U)))
  #error "Version numbers of Lin_Cfg.c and Lin_Cfg.h are inconsistent!"
#endif

/*********************************************************************************************************************
 * Local Preprocessor #define Constants
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Preprocessor #define Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Type Declarations
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * External Object Definitions
 *********************************************************************************************************************/
[!AUTOSPACING!]
[!IF "(as:modconf('Lin')[1]/IMPLEMENTATION_CONFIG_VARIANT = 'VariantPreCompile')"!][!VAR "LinChannelIdIndx" = "0"!]
#define  LIN_START_SEC_CONFIG_DATA
#include "Lin_MemMap.h"
CONST(Lin_ConfigType, LIN_CFG) Lin_Config =
{
   [!LOOP "as:modconf('Lin')[1]/LinGlobalConfig/LinChannel/*"!][!IF "(num:i($LinChannelIdIndx)) != LinChannelId"!][!ERROR "Lin Channel Id should start with 0, increment by 1 and continue without any gaps"!][!ENDIF!]
   .linChannelCfg[[!"@index"!]] =
   {
      .linControllerConfig =
      {
         .CntrAddr = [!IF "LinInstance='LIN_INSTANCE_0'"!]0x52400000U[!ELSEIF "LinInstance='LIN_INSTANCE_1'"!]0x52401000U[!ELSEIF "LinInstance='LIN_INSTANCE_2'"!]0x52402000U[!ELSEIF "LinInstance='LIN_INSTANCE_3'"!]0x52403000U[!ELSEIF "LinInstance='LIN_INSTANCE_4'"!]0x52404000U[!ELSE!][!ENDIF!],
         .IntrLineNum = [!"LinInterruptLineSelect"!],
         .LoopbackMode = [!"LinLoopbackMode"!]
      },
      .linBaudConfig =
      {
         .Prescalar = [!"LinBaudrateConfig/LinChannelPrescalar"!]U,
         .FractionalDivider = [!"LinBaudrateConfig/LinChannelFractionalDivider"!]U
      },
      .linWakeupSource = ([!IF "not(node:empty(LinChannelEcuMWakeupSource))"!]LIN_WAKEUP_SOURCE_[!"LinChannelId"!][!ELSE!]0[!ENDIF!]),
      .linChannelWakeupSupport = [!IF "LinChannelWakeupSupport='true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]

   }[!IF "not(node:islast())"!],[!CR!][!ELSE!][!ENDIF!][!VAR "LinChannelIdIndx" = "$LinChannelIdIndx+1"!][!ENDLOOP!]

};
#define  LIN_STOP_SEC_CONFIG_DATA
#include "Lin_MemMap.h"
[!ENDIF!][!//
/*********************************************************************************************************************
 * Local Object Definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  Local Function Prototypes
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  Local Inline Function Definitions and Function-Like Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  External Functions Definition
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  Local Functions Definition
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  End of File: Lin_Cfg.c
 *********************************************************************************************************************/
