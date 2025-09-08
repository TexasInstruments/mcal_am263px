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
