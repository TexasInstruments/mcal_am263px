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
 *  \file     DioApp_Startup.c
 *
 *  \brief    This file contains the DIO test example Hw Dependent functions.
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "DioApp_Startup.h"

static void Dio_Example_PlatformInit();

#ifdef __cplusplus
extern "C" {
#endif

void DioApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();
    Dio_Example_PlatformInit();
}

static void Dio_Example_PlatformInit()
{
#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&Mcu_Config);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&Port_Config);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    Enable_Uart();

    return;
}
#ifdef __cplusplus
}
#endif
