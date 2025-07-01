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

volatile boolean rxDoneEeprom = FALSE;

/*Buffer to send data to EEPROM*/
uint8 txBufferEeprom[32];
/*Buffer to reset address pointer in EEPROM*/
uint8 txBufferEepromStart[2];
/*Buffer to read data from EEPROM*/
uint8 rxBufferEeprom[26];

/* ========================================================================== */
/*                              Macros & Typedefs                             */
/* ========================================================================== */
#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

/*	None	*/

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

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
    interruptCfg.intNum   = I2C0_IRQ;
    interruptCfg.handler  = &Cdd_I2c_HwUnit0_ISR;
    interruptCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&interruptCfg);
}
#endif

void Uart_Delay(uint32 Delay)
{
    uint32 count;
    for (count = 0; count < Delay; count++)
    {
        ;
    }
}

Mcu_RamSectionConfigType Mcu_RamConfig[] = {
    [0U] = {.Mcu_RamSectionBaseAddress = &txBufferEepromStart[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(txBufferEepromStart)},
    [1U] = {.Mcu_RamSectionBaseAddress = &txBufferEeprom[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(txBufferEeprom)},
    [2U] = {.Mcu_RamSectionBaseAddress = &rxBufferEeprom[0U],
            .Mcu_RamDefaultValue       = 0x00,
            .Mcu_RamSectionBytes       = sizeof(rxBufferEeprom)},
};

Mcu_ClockConfigType gI2cAppMcuClockConfig[] = {
    [0] = {.Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_I2C,
           .Mcu_ClockSourceId = MCU_CLKSRC_3,
           .Mcu_ClockDiv      = 1U,
           .Mcu_InitCfg       = TRUE},
    [1] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_RTI0,
            .Mcu_ClockSourceId = MCU_CLKSRC_2,
            .Mcu_ClockDiv      = 0,
            .Mcu_InitCfg       = TRUE,
        },
    [2] =
        {
            .Mcu_ClockModuleId = MCU_CLKSRC_MODULE_ID_SCI0,
            .Mcu_ClockSourceId = MCU_CLKSRC_3,
            .Mcu_ClockDiv      = 3,
            .Mcu_InitCfg       = TRUE,
        },
};

Mcu_ConfigType Mcu_Config = {.Mcu_ResetMode           = MCU_PERFORM_RESET_MODE_WARM,
                             .Mcu_ConfigRamSection    = (Mcu_RamSectionConfigType *)Mcu_RamConfig,
                             .Mcu_NumberOfRamSectors  = ARRAYSIZE(Mcu_RamConfig),
                             .Mcu_ClockConfig         = (Mcu_ClockConfigPtrType)gI2cAppMcuClockConfig,
                             .Mcu_NumberOfClockConfig = ARRAYSIZE(gI2cAppMcuClockConfig)};

void Cdd_I2c_App_PlatformInit(void)
{
#if (STD_OFF == MCU_NO_PLL)
    /* MCU PLL Config */
    Mcu_Config.Mcu_PllConfig   = McuModuleConfiguration.Mcu_PllConfig;
    Mcu_Config.Mcu_PllSourceId = McuModuleConfiguration.Mcu_PllSourceId;
#endif
    Mcu_Init(&Mcu_Config);
    Port_Init(&PortConfigSet_0);

    Enable_Uart();

    /* Delay for UART to settle up */
    Uart_Delay(5000);
}

Std_ReturnType I2c_Buffer_Setup(void)
{
    Std_ReturnType returnValue = E_OK;

    /* Setup I2c channels */
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_0, &txBufferEeprom[0], NULL_PTR, 28);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_1, &txBufferEepromStart[0], NULL_PTR, 2);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_2, NULL_PTR, &rxBufferEeprom[0], 26);
    return returnValue;
}

Std_ReturnType I2cExample_ExternalTest_Data_Write_To_Slaves(Std_ReturnType BufferSetupReturnValue)
{
    Std_ReturnType returnValue = BufferSetupReturnValue;

    if (E_OK == returnValue)
    {
        strcpy((char *)&txBufferEeprom[0], "  EEPROM read/write test");
        txBufferEeprom[0] = EEPROM_MEM_ADDRESS; /* EEPROM internal address byte 1 pointer*/
        txBufferEeprom[1] = EEPROM_MEM_ADDRESS; /* EEPROM internal address byte 2 pointer*/

        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        /*1s delay*/
        AppUtils_delay(1000);

        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
        {
            /* Wait for sequence to be ready */
        }
    }
    else
    {
        /*Do Nothing*/
    }

    return returnValue;
}

Std_ReturnType I2cExample_ExternalTest_Eeprom_address_pointer_reset(Std_ReturnType BufferSetupReturnValue)
{
    Std_ReturnType returnValue = BufferSetupReturnValue;

    txBufferEepromStart[0] = EEPROM_MEM_ADDRESS; /* Address Byte 1 */
    txBufferEepromStart[1] = EEPROM_MEM_ADDRESS; /* Address Byte 2 */

    if (E_OK == returnValue)
    {
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_1);
        /*5s delay*/
        AppUtils_delay(5000);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
        {
            /* Wait for sequence to be ready */
        }
    }
    else
    {
        /*Do Nothing*/
    }

    return returnValue;
}

Std_ReturnType I2cExample_ExternalTest_Receive_Data(void)
{
    Std_ReturnType returnValue = E_OK;

#if (STD_ON == CDD_I2C_GET_STATUS_API) /*#if(STD_ON == CDD_I2C_GET_STATUS_API)*/
    /* Wait for transmission to be complete */
    while ((CDD_I2C_IDLE != Cdd_I2c_GetStatus()) || ((TRUE != rxDoneEeprom)))
#endif /*#if(STD_ON == CDD_I2C_GET_STATUS_API)*/
    {
/* Read I2c sequence in polling mode */
#if (STD_ON == CDD_I2C_POLLING_MODE) /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/
        Cdd_I2c_PollingModeProcessing();
#elif (STD_OFF == CDD_I2C_POLLING_MODE)
        /*Read EEPROM data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_2);
        while (TRUE != rxDoneEeprom)
        {
            /*Wait till above sequence is completed*/
        }
#endif /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/
        while (1)
        {
            Cdd_I2c_MainFunction();
            if ((CDD_I2C_SEQ_OK == Cdd_I2cSequenceContainerLocal[CddI2cConf_CddI2cSequence_CddI2cSequence_2].SeqResult))
            {
                break;
            }
            if ((CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[2].SeqResult) ||
                (CDD_I2C_SEQ_CANCELLED == Cdd_I2cSequenceContainerLocal[2].SeqResult))
            {
                /*Timeout occurred or transmission cancelled*/
                returnValue = E_NOT_OK;
                break;
            }
        }
    }
    if (CDD_I2C_SEQ_OK == Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
    {
        AppUtils_printf(APP_NAME ": Message read from EEPROM: %s\n\r", rxBufferEeprom);

        rxDoneEeprom = FALSE;

        returnValue = E_OK;
    }
    else
    {
        returnValue = E_NOT_OK;
    }
    return returnValue;
}

void I2c_Eeprom_Data_Write_Complete(void)
{
    /*Clear EEPROM TX buffer*/
    memset(&txBufferEeprom[0], 0, 28);
    strcpy((char *)&txBufferEeprom[0], "  EEPROM read/write test");
    AppUtils_printf(APP_NAME ": Message written to EEPROM: %s \n\r", txBufferEeprom);
    memset(&txBufferEeprom[0], 0, 28);
}

void I2c_Slave_Data_Write_Complete(void)
{
}

void I2c_Eeprom_Read_Callback(void)
{
    rxDoneEeprom = TRUE;
}

void I2c_Eeprom_Address_Ptr_Reset(void)
{
    AppUtils_printf(APP_NAME ": EEPROM address pointer reset to start read from location : %u\n\r", EEPROM_MEM_ADDRESS);
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

void I2c_Eeprom_Data_Write_Fail(uint8 Error_Code)
{
    AppUtils_printf(APP_NAME ": Sequence failed while trying to write to EEPROM\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void I2c_Eeprom_Address_Ptr_Fail(uint8 Error_Code)
{
    AppUtils_printf(APP_NAME ": Sequence failed while trying to reset EEPROM address pointer\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void I2c_Eeprom_Read_Callback_Fail(uint8 Error_Code)
{
    AppUtils_printf(APP_NAME ": Sequence failed while trying to read data from EEPROM\n\r");
    I2c_Sequence_Error_Report(Error_Code);
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
