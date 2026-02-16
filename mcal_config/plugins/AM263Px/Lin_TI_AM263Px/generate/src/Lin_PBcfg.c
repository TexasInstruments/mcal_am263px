/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
  #error "Version numbers of Lin_PBcfg.c and Lin.h are inconsistent!"
#endif

#if ((LIN_CFG_MAJOR_VERSION != ([!"substring-before($moduleSoftwareVer,'.')"!]U)) || (LIN_CFG_MINOR_VERSION != ([!"substring-before(substring-after($moduleSoftwareVer,'.'),'.')"!]U)))
  #error "Version numbers of Lin_PBcfg.c and Lin_Cfg.h are inconsistent!"
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
[!IF "(as:modconf('Lin')[1]/IMPLEMENTATION_CONFIG_VARIANT = 'VariantPostBuild')"!][!VAR "LinChannelIdIndx" = "0"!]
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
         .BaudRate = [!"LinChannelBaudRate"!]U,
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
 *  End of File: Lin_PBcfg.c
 *********************************************************************************************************************/
