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
 *  \file     DioApp.c
 *
 *  \brief    This file contains the DIO test example
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "assert.h"
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
#include "Det.h"
#include "EcuM_Cbk.h"
#include "DioApp_Startup.h"

#define DIO_APP_PERFORMANCE_MODE STD_ON

uint8 Dio_MainFunc_Execution;

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

#ifdef __cplusplus
}
#endif

#define DIO_EXAMPLE_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

/** @fn void main(void)
 *   @brief Application main function
 *   @note This function is empty by default.
 *
 *   This function is called after startup.
 *   The user can use this function to implement the application.
 */
#if (STD_ON == DIO_VERSION_INFO_API)
Std_VersionInfoType Dio_VersionInfo;
#endif

sint32 Dio_TestState = TRUE;

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration;
#endif

Dio_LevelType        Dio_PinLevel[64];
Dio_PortLevelType    Dio_PortLevel[4];
Dio_ChannelGroupType Dio_ChGroup[2];

Std_ReturnType Dio_ExampleTest(void)
{
    Std_ReturnType retVal = E_OK;
    uint32         i      = 0;
    Dio_LevelType  Dio_PinLevel[64];
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(GPIO_PIN_ID, PORT_PIN_OUT);
#endif /* #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
    Dio_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
    AppUtils_printf("Pin Value for channel %d : %x \n\r\n", GPIO_PIN_NUMBER, Dio_PinLevel[0]);

    if (Dio_PinLevel[0] == STD_HIGH)
    {
#if (STD_ON == DIO_FLIP_CHANNEL_API)
        Dio_FlipChannel(GPIO_PIN_NUMBER);
#endif
        AppUtils_printf("Dio_FlipChannel(channel_%d)\n\r", GPIO_PIN_NUMBER);
        Dio_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
        AppUtils_printf("Pin Value for channel %d : %x \n\r\n", GPIO_PIN_NUMBER, Dio_PinLevel[0]);
    }
    else
    {
        retVal = E_NOT_OK;
    }

    if (Dio_PinLevel[0] == STD_LOW && retVal == E_OK)
    {
#if (STD_ON == DIO_FLIP_CHANNEL_API)
        Dio_FlipChannel(GPIO_PIN_NUMBER);
#endif
        AppUtils_printf("Dio_FlipChannel(channel_%d)\n\r", GPIO_PIN_NUMBER);
        Dio_PinLevel[0] = Dio_ReadChannel(GPIO_PIN_NUMBER);
        AppUtils_printf("Pin Value for channel %d : %x \n\r\n", GPIO_PIN_NUMBER, Dio_PinLevel[0]);
    }
    else
    {
        retVal = E_NOT_OK;
    }

    Dio_WriteChannel(GPIO_PIN_NUMBER, STD_LOW);
    AppUtils_printf("Dio_WriteChannel -channel %d\n\r ", GPIO_PIN_NUMBER);

    Dio_PinLevel[2] = Dio_ReadChannel(GPIO_PIN_NUMBER);
    AppUtils_printf("Pin Value for channel : %d\n\r", Dio_PinLevel[2]);
    if (Dio_PinLevel[2] == STD_LOW && retVal == E_OK)
    {
        retVal = E_OK;
    }
    else
    {
        retVal = E_NOT_OK;
    }

    Dio_WriteChannel(GPIO_PIN_NUMBER, STD_HIGH);
    AppUtils_printf("Dio_WriteChannel - channel %d\n\r ", GPIO_PIN_NUMBER);

    Dio_PinLevel[2] = Dio_ReadChannel(GPIO_PIN_NUMBER);
    AppUtils_printf("Pin Value for channel : %d\n\r", Dio_PinLevel[2]);

    if (Dio_PinLevel[2] == STD_HIGH && retVal == E_OK)
    {
        retVal = E_OK;
    }
    else
    {
        retVal = E_NOT_OK;
    }

    Dio_PortLevel[0] = 0x00000000;
    Dio_PortLevel[1] = 0x00000001;

    Dio_WritePort(PORT_PIN_ID, Dio_PortLevel[1]);
    AppUtils_delay(50U);
    Dio_PortLevel[1] = Dio_ReadPort(PORT_PIN_ID);
    AppUtils_printf("Port Value Before Flip:%x \n\r", Dio_PortLevel[1]);
    AppUtils_delay(50U);
#if (STD_ON == DIO_FLIP_CHANNEL_API)
    Dio_FlipChannel(GPIO_PIN_NUMBER);
#endif
    AppUtils_delay(50U);
    Dio_PortLevel[1] = Dio_ReadPort(PORT_PIN_ID);
    AppUtils_delay(50U);
    AppUtils_printf("After Flip Port Value:%x \n\r", Dio_PortLevel[1]);

    Dio_PortLevel[1] = Dio_PortLevel[0] & Dio_PortLevel[1];

    if (Dio_PortLevel[1] == 0x0000000 && retVal == E_OK)
    {
        retVal = E_OK;
    }
    else
    {
        retVal = E_NOT_OK;
    }

    for (i = 0; i < 1; i++)
    {
        Dio_ChGroup[i].port   = PORT_PIN_ID;
        Dio_ChGroup[i].offset = 0;
        Dio_ChGroup[i].mask   = 0x01;
        Dio_PortLevel[i]      = 0xFF;
        Dio_WriteChannelGroup(&Dio_ChGroup[i], Dio_PortLevel[i]);
        AppUtils_delay(20U);
        Dio_PortLevel[i] = Dio_ReadChannelGroup(&Dio_ChGroup[i]);
        AppUtils_delay(20U);
        AppUtils_printf("Read channel grp Port Value:%x \n\r", Dio_PortLevel[i]);
        if ((Dio_PortLevel[i] & 0x1) == STD_HIGH && retVal == E_OK)
        {
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}
sint32 main(void)
{
    Std_ReturnType retVal = E_OK;

    DioApp_Startup();

    AppUtils_printf("DioApp: Sample Application - STARTS !!!\n\r");

#if (STD_ON == DIO_VERSION_INFO_API)
    Dio_GetVersionInfo(&Dio_VersionInfo);
    AppUtils_printf("DIO Driver version info:%d.%d.%d\n\r", Dio_VersionInfo.sw_major_version,
                    Dio_VersionInfo.sw_minor_version, Dio_VersionInfo.sw_patch_version);
    AppUtils_printf("DIO Driver Module/Driver:%d.%d \n\r", Dio_VersionInfo.moduleID, Dio_VersionInfo.vendorID);
#endif

    retVal = Dio_ExampleTest();

    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        retVal = E_NOT_OK;
        AppUtils_printf(" DIO Stack/section corruption!!!\n\r");
    }

    if (retVal == E_OK)
    {
        AppUtils_printf(" All tests have passed\n");
    }
    else
    {
        AppUtils_printf(" Some tests have failed\n");
    }

    AppUtils_TimerDeinit();
    return retVal;
}

#ifdef __cplusplus
extern "C" {
#endif

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    assert(FALSE);
    return E_OK;
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
