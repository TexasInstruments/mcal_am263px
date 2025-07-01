/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     I2cApp_Startup.c
 *
 *  \brief    This file contains the pinmux, interrupt and clock configuration.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "I2cApp_Startup.h"
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Cdd_I2c_ConfigPtrType I2cConfigSet = NULL_PTR;

sint16 temperature = (sint16)0;

/*Buffer to store transmission data for temperature sensor*/
uint8 txBufferTemperature[1];
/*Buffer to store reception data for temperature sensor*/
uint8 rxBufferTemperature[2];

/*Buffer to store transmission data for temperature sensor*/
uint8 txBufferEeprom[14];
/*Buffer to store transmission data for temperature sensor*/
uint8 txBufferEepromStart[2];
/*Buffer to store reception data for temperature sensor*/
uint8 rxBufferEeprom[14];

volatile boolean rxDoneTemperature = FALSE;
volatile boolean rxDoneEeprom      = FALSE;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/*	None	*/

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

void Cdd_I2cApp_Startup(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    /*	timer initialization	*/
    AppUtils_TimerInit();
}

#if (STD_OFF == CDD_I2C_POLLING_MODE)
void Cdd_I2c_InterruptConfig(void)
{
    vimInit();
    Vim_IntCfg interruptCfg;
    interruptCfg.map      = VIM_INTTYPE_IRQ;
    interruptCfg.type     = VIM_INTTRIGTYPE_PULSE;
    interruptCfg.intNum   = MSS_I2C_INT;
    interruptCfg.handler  = &Cdd_I2c_HwUnit0_ISR;
    interruptCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&interruptCfg);
}
#endif

Mcu_RamSectionConfigType Mcu_RamConfig[] = {
    [0U] = {.Mcu_RamSectionBaseAddress = &txBufferTemperature[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(txBufferTemperature)},
    [1U] = {.Mcu_RamSectionBaseAddress = &rxBufferTemperature[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(rxBufferTemperature)},
    [2U] = {.Mcu_RamSectionBaseAddress = &txBufferEepromStart[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(txBufferEepromStart)},
    [3U] = {.Mcu_RamSectionBaseAddress = &txBufferEeprom[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(txBufferEeprom)},
    [4U] = {.Mcu_RamSectionBaseAddress = &rxBufferEeprom[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(rxBufferEeprom)},
};

Mcu_ClockConfigType gI2cAppMcuClockConfig[] = {
    [0] = {.Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_I2C,
#if defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM)
           .Mcu_ClockSourceId = MCU_CLKSRC_2,
           .Mcu_ClockDiv      = 0U, /* mcu clock div for 80 MhZ, with 400 MHz clock */
#else
           .Mcu_ClockSourceId = MCU_CLKSRC_2,
           .Mcu_ClockDiv      = 0U, /* 240/(2+1) = 80MHz with 240MHz clk */
#endif
           .Mcu_InitCfg = TRUE},
    [1] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTIA,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [2] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTIB,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [3] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTIC,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
};

Mcu_ConfigType Mcu_Config = {.Mcu_ResetMode           = MCU_PERFORM_RESET_MODE_WARM,
                             .Mcu_ConfigRamSection    = (Mcu_RamSectionConfigType *)Mcu_RamConfig,
                             .Mcu_NumberOfRamSectors  = I2CEXAMPLE_ARRAYSIZE(Mcu_RamConfig),
                             .Mcu_ClockConfig         = (Mcu_ClockConfigPtrType)gI2cAppMcuClockConfig,
                             .Mcu_NumberOfClockConfig = I2CEXAMPLE_ARRAYSIZE(gI2cAppMcuClockConfig)};

void Cdd_I2c_App_PlatformInit(void)
{
    uint16 mss_uart_tx_pin, mss_uart_rx_pin;

#if (STD_OFF == MCU_NO_PLL)
    uint32 sys_clk_freq_vclk_const;

    /* MCU PLL Config */
    Mcu_Config.Mcu_PllConfig   = McuModuleConfiguration.Mcu_PllConfig;
    Mcu_Config.Mcu_PllSourceId = McuModuleConfiguration.Mcu_PllSourceId;
#endif

    Mcu_Init(&Mcu_Config);
    Port_Init(&PortConfigSet_0);
    Mcu_InitRamSection(0);
    Mcu_InitRamSection(1);

    mss_uart_tx_pin = 3;
    mss_uart_rx_pin = 4;

#if defined AWR29XXETS_PLATFORM
    mss_uart_tx_pin = 12;
    mss_uart_rx_pin = 8;
#endif
#if defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM)
    mss_uart_tx_pin = 101;
    mss_uart_rx_pin = 80;
#endif

    // Set up the pinmux for UART tx
    Port_SetPinMode(mss_uart_tx_pin, PORT_PIN_MODE_MSS_UARTA);

    // Set up the pinmux for UART rx
    Port_SetPinMode(mss_uart_rx_pin, PORT_PIN_MODE_MSS_UARTA);
    Port_SetPinDirection(mss_uart_rx_pin, PORT_PIN_IN);

#if (STD_OFF == MCU_NO_PLL)
    if (McuModuleConfiguration.Mcu_PllSourceId == MCU_CLKSRC_DPLL)
    {
        sys_clk_freq_vclk_const =
            (McuModuleConfiguration.Mcu_PllConfig[MCU_CLKSRC_DPLL].Mcu_PllClk1.MCU_PLL_HSDIV2 / (2e6)) * 30;
    }
    else
    {
        sys_clk_freq_vclk_const =
            (McuModuleConfiguration.Mcu_PllConfig[MCU_CLKSRC_APLL].Mcu_PllClk1.MCU_PLL_HSDIV0 / (2e6)) * 30;
    }
    Enable_Uart(sys_clk_freq_vclk_const);
#else
    Enable_Uart(SYS_CLOCK_FREQ_SYS_VCLK);
#endif
}

Std_ReturnType I2c_Buffer_Setup(void)
{
    Std_ReturnType returnValue = E_OK;

    /* Setup I2c channels */
    returnValue  = Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_0, &txBufferTemperature[0], NULL_PTR, 1);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_1, &txBufferEeprom[0], NULL_PTR, 14);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_2, &txBufferEepromStart[0], NULL_PTR, 2);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_3, NULL_PTR, &rxBufferTemperature[0], 2);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_4, NULL_PTR, &rxBufferEeprom[0], 12);

    return returnValue;
}

Std_ReturnType I2cExample_ExternalTest_Data_Write_To_Slaves(Std_ReturnType BufferSetupReturnValue)
{
    Std_ReturnType returnValue = BufferSetupReturnValue;

    if (E_OK == returnValue)
    {
        txBufferTemperature[0] = TMP10X_RESULT_REG;
        strcpy((char *)&txBufferEeprom[0], "  Hello World");
        txBufferEeprom[0] = EEPROM_START_ADDRESS;
        txBufferEeprom[1] = EEPROM_START_ADDRESS;

        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
        {
            /* Wait for sequence to be ready */
        }
        AppUtils_delay(2000);
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        AppUtils_delay(2000);

        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
        {
            /* Wait for sequence to be ready */
        }
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_1);
        // 1s delay
        AppUtils_delay(1000);
    }
    else
    {
        // Do Nothing
    }

    return returnValue;
}

Std_ReturnType I2cExample_ExternalTest_Eeprom_address_pointer_reset(Std_ReturnType BufferSetupReturnValue)
{
    Std_ReturnType returnValue = BufferSetupReturnValue;

    if (E_OK == returnValue)
    {
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
        {
            /* Wait for sequence to be ready */
        }
        AppUtils_delay(2000);
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_2);
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
    while ((CDD_I2C_IDLE != Cdd_I2c_GetStatus()) || ((TRUE != rxDoneTemperature) && (TRUE != rxDoneEeprom)))
#endif /*#if(STD_ON == CDD_I2C_GET_STATUS_API)*/
    {
/* Wait for transmission to be complete */
/* Read I2c channel */
#if (STD_ON == CDD_I2C_POLLING_MODE) /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/
        AppUtils_delay(5000);
        Cdd_I2c_PollingModeProcessing();
        AppUtils_delay(2000);
#elif (STD_OFF == CDD_I2C_POLLING_MODE)
        AppUtils_delay(2000);
        /*Read Temperature sensor data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_3);
        /*5s delay to give time to peripheral to copy data to proper locations*/
        AppUtils_delay(2000);
        /*Read EEPROM data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_4);
#endif /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/
        AppUtils_delay(2000);
        Cdd_I2c_MainFunction();
    }

    if (CDD_I2C_SEQ_OK == Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_3))
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

        rxDoneTemperature = FALSE;

        returnValue = E_OK;
    }
    else
    {
        returnValue = E_NOT_OK;
    }

    if (CDD_I2C_SEQ_OK == Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_4))
    {
        AppUtils_printf(APP_NAME ":Message read from EEPROM Done: %s \n\r", rxBufferEeprom);

        rxDoneEeprom = FALSE;

        returnValue = E_OK;
    }
    else
    {
        returnValue = E_NOT_OK;
    }
    return returnValue;
}

void I2c_Temperature_Data_Write_Complete(void)
{
    AppUtils_printf(APP_NAME ": Temperature write SuccessFull \n\r");
}

void I2c_Eeprom_Data_Write_Complete(void)
{
    AppUtils_printf(APP_NAME ": Eeprom write successfull: %s \n\r", (txBufferEeprom + 2));
}

void I2c_Temperature_Read_Callback(void)
{
    rxDoneTemperature = TRUE;
}

void I2c_Eeprom_Read_Callback(void)
{
    rxDoneEeprom = TRUE;
}

void I2c_Eeprom_Address_Ptr_Reset(void)
{
}

#if (STD_ON == CDD_I2C_VERSION_INFO_API)
void Print_I2c_Version_Info(Std_VersionInfoType *versionInfoPtr)
{
    AppUtils_printf(APP_NAME ": Vendor ID: %u\n\r", versionInfoPtr->vendorID);
    AppUtils_printf(APP_NAME ": Module ID: %u\n\r", versionInfoPtr->moduleID);
    AppUtils_printf(APP_NAME ": SW Major version ID: %u\n\r", versionInfoPtr->sw_major_version);
    AppUtils_printf(APP_NAME ": SW Minor version ID: %u\n\r", versionInfoPtr->sw_minor_version);
    AppUtils_printf(APP_NAME ": SW Patch version ID: %u\n\r", versionInfoPtr->sw_patch_version);
}
#endif
