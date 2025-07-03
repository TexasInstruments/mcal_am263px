/* ======================================================================
 *   Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file     I2cApp_Platform.c
 *
 *  \brief    This file contains the platform configurations.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "I2cApp.h"
#include "I2cApp_Platform.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

sint16           temperature       = (sint16)0;
volatile boolean rxDoneTemperature = FALSE;
volatile boolean rxDoneEeprom      = FALSE;

/*Buffer to store transmission data for temperature sensor*/
uint8 txBufferTemperature[1];
/*Buffer to store reception data for temperature sensor*/
uint8 rxBufferTemperature[2];

/*Buffer to store transmission data for temperature sensor*/
uint8 txBufferEeprom[32];
/*Buffer to store transmission data for temperature sensor*/
uint8 txBufferEepromStart[2];
/*Buffer to store reception data for temperature sensor*/
uint8 rxBufferEeprom[26];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void I2c_appPlatformInit(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

    Enable_Uart();

    return;
}

Std_ReturnType I2c_Buffer_Setup(void)
{
    Std_ReturnType returnValue = E_OK;

    /* Setup I2c channels */
    returnValue  = Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_0, &txBufferTemperature[0], NULL_PTR, 1);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_1, NULL_PTR, &rxBufferTemperature[0], 2);

    return returnValue;
}

Std_ReturnType I2cExample_ExternalTest_Data_Write_To_Slaves(Std_ReturnType BufferSetupReturnValue)
{
    Std_ReturnType returnValue = BufferSetupReturnValue;

    if (E_OK == returnValue)
    {
        txBufferTemperature[0] = TMP10X_RESULT_REG;
        strcpy((char *)&txBufferEeprom[0], "  I2C read/write test passed");

        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        /*5s delay*/
        AppUtils_delay(1000);
        while (CDD_I2C_CH_RESULT_OK != Cdd_I2c_GetResult(CddI2cConf_CddI2cChannel_CddI2cChannel_0))
        {
            /* Wait for sequence to be ready */
        }
    }
    else
    {
        // Do Nothing
    }

    return returnValue;
}

Std_ReturnType I2cExample_ExternalTest_Receive_Data(void)
{
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_I2C_GET_STATUS_API) /*#if(STD_ON == CDD_I2C_GET_STATUS_API)*/
    /* Wait for transmission to be complete */
    while ((CDD_I2C_IDLE != Cdd_I2c_GetStatus()) || ((TRUE != rxDoneTemperature)))
#endif /*#if(STD_ON == CDD_I2C_GET_STATUS_API)*/
    {
/* Read I2c sequence in polling mode */
#if (STD_ON == CDD_I2C_POLLING_MODE) /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/
        Cdd_I2c_PollingModeProcessing();
#elif (STD_OFF == CDD_I2C_POLLING_MODE)
        /*Read Temperature sensor data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        while (TRUE != rxDoneTemperature)
        {
            /*Wait till the above sequence is completed*/
        }
#endif /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/

        if (CDD_I2C_CH_RESULT_OK == Cdd_I2c_GetResult(CddI2cConf_CddI2cChannel_CddI2cChannel_1))
        {
            /* Create 16 bit temperature */
            temperature = ((uint16)rxBufferTemperature[0] << 8) | (rxBufferTemperature[1]);

            /*
             * 4 LSBs of temperature are 0 according to datasheet
             * since temperature is stored in 12 bits. Therefore,
             * right shift by 4 places
             */
            temperature = temperature >> 4;
            /*
             * If the 12th bit of temperature is set '1' (equivalent to 8th bit of the first byte read),
             * then we have a 2's complement negative value which needs to be sign extended
             */
            if (rxBufferTemperature[0] & 0x80)
            {
                temperature |= 0xF000;
            }
            else
            {
                // Do Nothing
            }

            AppUtils_printf(APP_NAME ": Temperature sensor reading : %f (celcius)\n\r", (temperature / 16.0f));

            rxDoneTemperature = TRUE;

            returnValue = E_OK;
        }
        else
        {
            returnValue = E_NOT_OK;
        }
    }
    return returnValue;
}

void I2c_appPlatformDeInit(void)
{
    AppUtils_TimerDeinit();

    return;
}

void I2c_Temperature_Data_Write_Read_Complete(void)
{
    AppUtils_printf(APP_NAME ": Temperature write-read SuccessFull \n\r");
}

void I2c_Temperature_Read_Callback(void)
{
    rxDoneTemperature = TRUE;
}

void I2c_Sequence_Error_Report(uint8 Error_code)
{
    if (CDD_I2C_E_HW_UNIT_BUSY == Error_code)
    {
        AppUtils_printf(APP_NAME ": Hardware unit busy\n\r");
    }
    else if (CDD_I2C_E_CHANNEL_BUSY == Error_code)
    {
        AppUtils_printf(APP_NAME ": Channels busy\n\r");
    }
    else if (CDD_I2C_E_ARBITRATION_LOSS == Error_code)
    {
        AppUtils_printf(APP_NAME ": Arbitration lost\n\r");
    }
    else if (CDD_I2C_E_NACK == Error_code)
    {
        AppUtils_printf(APP_NAME ": No Acknowledgement\n\r");
    }
    else if (CDD_I2C_E_RECEIVE_SHIFT_REGISTER_FULL == Error_code)
    {
        AppUtils_printf(APP_NAME ": Receive shift register full\n\r");
    }
    else if (CDD_I2C_E_PARAM_QUEUE_FULL == Error_code)
    {
        AppUtils_printf(APP_NAME ": Queue full\n\r");
    }
}

void I2c_Temperature_Data_Write_Read_Fail(uint8 Error_Code)
{
    AppUtils_printf(APP_NAME ": Sequence failed while trying to write/read to temperature\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void I2c_Temperature_Read_Callback_Fail(uint8 Error_Code)
{
    AppUtils_printf(APP_NAME ": Sequence failed while trying to read data from temperature sensor\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}
