/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     I2cExample.c
 *
 *  \brief    This file contains the I2c test example
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
/*LDRA_ANALYSIS*/
#include "Cdd_I2c_Cfg.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "hw_types.h"
#include "esm.h"
#include "sys_vim.h"
#include "app_utils.h"
#include "trace.h"
#include "Cdd_I2c.h"
#include <string.h>
#include "I2cApp_Startup.h"

Std_ReturnType testPassed = E_NOT_OK;

int main(void)
{
    Std_ReturnType BufferSetupReturnValue = E_OK;

#if (STD_ON == CDD_I2C_VERSION_INFO_API)
    Std_VersionInfoType  VersionInformation;
    Std_VersionInfoType *pVersionInformation = &VersionInformation;
#endif

    Cdd_I2cApp_Startup();

    Cdd_I2c_App_PlatformInit();

#if (STD_OFF == CDD_I2C_POLLING_MODE)
    Cdd_I2c_InterruptConfig();
#endif

    start_timer();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\n\r");
    AppUtils_printf(APP_NAME
                    ": gI2cAppMcuClockConfig[0].Mcu_ClockSourceId = %d "
                    "gI2cAppMcuClockConfig[0].Mcu_ClockDiv = %d  :\n\r",
                    gI2cAppMcuClockConfig[0].Mcu_ClockSourceId, gI2cAppMcuClockConfig[0].Mcu_ClockDiv);

#if (STD_ON == CDD_I2C_VERSION_INFO_API)
    /*Get I2c Version information*/
    Cdd_I2c_GetVersionInfo(pVersionInformation);
    Print_I2c_Version_Info(pVersionInformation);
#endif

    /* Do I2c Init */
    Cdd_I2c_Init(I2cConfigSet);
    /*Set up channels*/
    BufferSetupReturnValue = I2c_Buffer_Setup();
    /*Write data to Temperature sensor and EEPROM*/
    testPassed = I2cExample_ExternalTest_Data_Write_To_Slaves(BufferSetupReturnValue);
    /*Write dummy data to EEPROM to reset address pointer*/
    testPassed |= I2cExample_ExternalTest_Eeprom_address_pointer_reset(BufferSetupReturnValue);
    /*Receive and process data*/
    testPassed |= I2cExample_ExternalTest_Receive_Data();

    if (E_OK == testPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, "All tests have passed\n\r");
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, " I2C Test Failed!!!\n\r");
    }

    /*Stop the timer*/
    stop_timer();
    /*De-initialize I2c module*/
    Cdd_I2c_DeInit();

    return (0);
}

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

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    testPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return E_OK;
}

#ifdef __cplusplus
}
#endif
