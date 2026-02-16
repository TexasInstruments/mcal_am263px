/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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

/**
 *  \file     McuApp.c
 *
 *  \brief    This file contains the Mcu test example
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "assert.h"
/*LDRA_NOANALYSIS*/
#include "string.h"
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
/*LDRA_ANALYSIS*/
#include "Mcu.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "trace.h"
#include "esm.h"
#include "app_utils.h"
#include "McuApp_Startup.h"
#define APP_PERFORMANCE_MODE STD_OFF
#define APP_NAME             "Mcu_App"
uint8 MainFunc_Execution;
#if (STD_ON == APP_PERFORMANCE_MODE)
static void McuExample_PerformanceTest();
#endif
void   Stop_Timer(uint8 Api_Id);
void   Start_Timer(void);
uint32 Performance_Result[10];
#ifdef __cplusplus
extern "C" {
#endif

/** @fn void main(void)
 *   @brief Application main function
 *   @note This function is empty by default.
 *
 *   This function is called after startup.
 *   The user can use this function to implement the application.
 */

Std_VersionInfoType VersionInfo;
sint32              TestState = TRUE;

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
sint32 main(void)
{
    uint8 referenceArray[20];

    start_timer();

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&Mcu_Config);
#endif
    McuApp_Startup();
#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&Port_Config);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/
    McuApp_PlatformInit();

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n\r");

#else
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");

#endif
    AppUtils_printf("\n\rMcuApp: Sample Application - STARTS !!!\n\r");
#if (STD_ON == MCU_GET_VERSION_INFO_API)
    Mcu_GetVersionInfo(&VersionInfo);
    AppUtils_printf("Mcu Driver version info:%d.%d.%d\n\r", VersionInfo.sw_major_version, VersionInfo.sw_minor_version,
                    VersionInfo.sw_patch_version);
    AppUtils_printf("Mcu Driver Module/Driver:%d.%d \n\r", VersionInfo.moduleID, VersionInfo.vendorID);
#endif

    my_memset((uint8 *)MCU_RAM_INIT_ADDRESS, 0, 20);
    my_memset(referenceArray, 0xBE, 20);

#if (STD_ON == APP_PERFORMANCE_MODE)
    McuExample_PerformanceTest();
#endif

#if (STD_ON == MCU_INIT_RAM_API)
    Mcu_InitRamSection(0);
#endif

    if (memcmp((uint8 *)MCU_RAM_INIT_ADDRESS, &referenceArray[0], 20) != 0)
    {
        GT_0trace(McalAppTrace, GT_INFO, "RAM section is not initialized properly");
        AppUtils_printf("MCU Test Failed!!!\n\r");
        TestState = FALSE;
    }
    else
    {
        GT_0trace(McalAppTrace, GT_INFO, "RAM section is initialized properly\n\r");
        /* check the wakeup cause */
        if (Mcu_GetResetReason() == MCU_POWER_ON_RESET)
        {
            GT_0trace(McalAppTrace, GT_INFO, "Wake up from Power ON\n\r");
            AppUtils_printf("All tests have passed!!!\n\r");
        }
        else
        {
            GT_0trace(McalAppTrace, GT_INFO, " Wake up from Soft Reset\n\r");
            AppUtils_printf("All tests have passed!!!\n\r");
        }
    }
    GT_1trace(McalAppTrace, GT_INFO, "MCU Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        GT_0trace(McalAppTrace, GT_ERR, "MCU Stack/section corruption!!!\n\r");
    }
    return TestState;
}

void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    MainFunc_Execution = 1;
}

#ifdef __cplusplus
}
#endif
