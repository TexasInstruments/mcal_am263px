/* ========================================================================
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
 * ===================================================================== */

/**
 *  \file     PortApp.c
 *
 *  \brief    This file contains the Port test example
 */

/**************************************************************************
 *                              Include Files
 *************************************************************************/
#include "assert.h"
#include "Std_Types.h"
#include "Det.h"
#include "EcuM_Cbk.h"
#include "PortApp_Startup.h"

/**************************************************************************
 *                            Global Variables
 *************************************************************************/

uint8 Port_MainFunc_Execution;

/**************************************************************************
 *                            Function Defination
 *************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    Port_MainFunc_Execution = 1;
}
void SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_0()
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

#ifdef __cplusplus
}
#endif

Std_ReturnType Port_ExampleTest(void)
{
    Std_ReturnType retVal = E_OK;
    Dio_LevelType  Port_PinLevel[64];

    /** Test Port Interrupt Functionality **/
#if (STD_ON == PORT_ENABLE_INTR_API)

    retVal = Port_TestIntruppt();

#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

    if (retVal == E_OK)
    {
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
        Port_SetPinDirection(GPIO_PIN_ID, PORT_PIN_OUT);
#endif /* ( STD_ON == PORT_SET_PIN_DIRECTION_API ) */
        Port_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
        AppUtils_printf("Pin Value for channel %d : %x \n\r\n", GPIO_PIN_NUMBER, Port_PinLevel[0]);

        if (Port_PinLevel[0] == STD_HIGH)
        {
#if (STD_ON == DIO_FLIP_CHANNEL_API)
            Dio_FlipChannel(GPIO_PIN_NUMBER);
            AppUtils_printf("Dio_FlipChannel(channel_%d)\n\r", GPIO_PIN_NUMBER);
#endif
            Port_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
            AppUtils_printf("Pin Value for channel %d : %x \n\r\n", GPIO_PIN_NUMBER, Port_PinLevel[0]);
        }
        else
        {
            retVal = E_NOT_OK;
        }

        if ((Port_PinLevel[0] == STD_LOW) && (retVal == E_OK))
        {
#if (STD_ON == DIO_FLIP_CHANNEL_API)
            Dio_FlipChannel(GPIO_PIN_NUMBER);
#endif
            AppUtils_printf("Dio_FlipChannel(channel_%d)\n\r", GPIO_PIN_NUMBER);
            Port_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
            AppUtils_printf("Pin Value for channel %d : %x \n\r\n", GPIO_PIN_NUMBER, Port_PinLevel[0]);
        }
        else
        {
            retVal = E_NOT_OK;
        }

        if ((Port_PinLevel[0] == STD_HIGH) && (retVal == E_OK))
        {
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
            Port_SetPinDirection(GPIO_PIN_ID, PORT_PIN_IN);
#endif /* ( STD_ON == PORT_SET_PIN_DIRECTION_API ) */
            Port_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
            AppUtils_printf("Pin Value for channel %d : %x \n\r", GPIO_PIN_NUMBER, Port_PinLevel[0]);

#if (STD_ON == DIO_FLIP_CHANNEL_API)
            Dio_FlipChannel(GPIO_PIN_NUMBER);
            AppUtils_printf("Dio_FlipChannel(channel_%d)\n\r", GPIO_PIN_NUMBER);
#endif

            Port_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
            AppUtils_printf("Pin Value for channel %d : %x \n\r\n", GPIO_PIN_NUMBER, Port_PinLevel[0]);
        }
    }

    return retVal;
}

/** @fn void main(void)
 *  @brief Port Example Application Main Function
 *
 *   This function is called after startup.
 *   The user can use this function to implement the application.
 */
sint32 main(void)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == PORT_VERSION_INFO_API)
    Std_VersionInfoType Port_VersionInfo;
#endif

    PortApp_Startup();
    Port_Example_PlatformInit();

    AppUtils_printf("CLANG compiled : portApp: Sample Application - STARTS !!!\n\r");

#if (STD_ON == PORT_VERSION_INFO_API)
    Port_GetVersionInfo(&Port_VersionInfo);
    AppUtils_printf("Port Driver version info:%d.%d.%d\n\r", Port_VersionInfo.sw_major_version,
                    Port_VersionInfo.sw_minor_version, Port_VersionInfo.sw_patch_version);
    AppUtils_printf("Port Driver Module/Driver:%d.%d \n\r\n", Port_VersionInfo.moduleID, Port_VersionInfo.vendorID);
#endif

    retVal = Port_ExampleTest();

    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        retVal = E_NOT_OK;
        AppUtils_printf(" PORT Stack/section corruption!!!\n\r");
    }

    if (retVal == E_OK)
    {
        AppUtils_printf("PORT Test Passed!!!\n\r");
    }
    else
    {
        AppUtils_printf("PORT Test Failed!!!\n\r");
    }

    return retVal;
}
