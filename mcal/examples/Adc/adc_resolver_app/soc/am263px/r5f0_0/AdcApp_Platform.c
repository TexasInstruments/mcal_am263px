/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
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
 *  \file     AdcApp_Platform.c
 *
 *  \brief    This file contains the platform configurations.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <AdcApp.h>
#include <AdcApp_Platform.h>
#include "Cdd_I2c.h"
#include "Cdd_I2c_Irq.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* TCA6424 Register Offsets */
#define TCA6424_REG_INPUT_PORT_0   (0x00U)
#define TCA6424_REG_INPUT_PORT_1   (0x01U)
#define TCA6424_REG_INPUT_PORT_2   (0x02U)
#define TCA6424_REG_OUTPUT_PORT_0  (0x04U)
#define TCA6424_REG_OUTPUT_PORT_1  (0x05U)
#define TCA6424_REG_OUTPUT_PORT_2  (0x06U)
#define TCA6424_REG_POL_INV_PORT_0 (0x08U)
#define TCA6424_REG_POL_INV_PORT_1 (0x09U)
#define TCA6424_REG_POL_INV_PORT_2 (0x0AU)
#define TCA6424_REG_CONFIG_PORT_0  (0x0CU)
#define TCA6424_REG_CONFIG_PORT_1  (0x0DU)
#define TCA6424_REG_CONFIG_PORT_2  (0x0EU)

/* TCA6416 Register Offsets */
#define TCA6416_REG_INPUT_PORT_0   (0x00U)
#define TCA6416_REG_INPUT_PORT_1   (0x01U)
#define TCA6416_REG_OUTPUT_PORT_0  (0x02U)
#define TCA6416_REG_OUTPUT_PORT_1  (0x03U)
#define TCA6416_REG_POL_INV_PORT_0 (0x04U)
#define TCA6416_REG_POL_INV_PORT_1 (0x05U)
#define TCA6416_REG_CONFIG_PORT_0  (0x06U)
#define TCA6416_REG_CONFIG_PORT_1  (0x07U)

/* I2C board parameters based on generated configuration */
#define ADC_APP_I2C_IO_MUX_WR_SEQ (CddI2cConf_CddI2cSequence_CddI2cSequence_0)
#define ADC_APP_I2C_IO_MUX_RD_SEQ (CddI2cConf_CddI2cSequence_CddI2cSequence_1)
#define ADC_APP_I2C_IO_MUX_WR_CH  (CddI2cConf_CddI2cChannel_CddI2cChannel_0)
#define ADC_APP_I2C_IO_MUX_RD_CH  (CddI2cConf_CddI2cChannel_CddI2cChannel_1)
#define ADC_APP_I2C_EEPROM_WR_SEQ (CddI2cConf_CddI2cSequence_CddI2cSequence_2)
#define ADC_APP_I2C_EEPROM_RD_SEQ (CddI2cConf_CddI2cSequence_CddI2cSequence_3)
#define ADC_APP_I2C_EEPROM_WR_CH  (CddI2cConf_CddI2cChannel_CddI2cChannel_2)
#define ADC_APP_I2C_EEPROM_RD_CH  (CddI2cConf_CddI2cChannel_CddI2cChannel_3)

/* Slave address for IO Expander TCA6416 available in E1 version board*/
#define TCA6416_SLAVE_ADDRESS (32U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

extern void           Pmic_Enable(void);
static boolean        Adc_appIsIoMuxTCA6424(void);
static Std_ReturnType Adc_appI2cWrite(Cdd_I2c_SequenceType wrSeqId, Cdd_I2c_ChannelType wrChId, uint8 *pWrBuf,
                                      uint16 size, boolean boardVerE1);
static Std_ReturnType Adc_appI2cRead(Cdd_I2c_SequenceType rdSeqId, Cdd_I2c_ChannelType rdChId, uint8 *pRdBuf,
                                     uint16 size);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Adc_appPlatformInit(void)
{
    Vim_IntCfg intCfg;

    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();

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

    vimInit();
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;
    /* I2C0 interrupt */
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = I2C0_INT;
    intCfg.handler  = &Cdd_I2c_HwUnit0_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
    /* I2C2 interrupt */
    intCfg.map      = VIM_INTTYPE_IRQ;
    intCfg.type     = VIM_INTTRIGTYPE_PULSE;
    intCfg.intNum   = I2C2_INT;
    intCfg.handler  = &Cdd_I2c_HwUnit2_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);

    Enable_Uart();
    Cdd_I2c_Init(NULL_PTR);

    /* Set up Pmic for Adc AM263P CC Board*/
    Pmic_Enable();

    return;
}

void Adc_appPlatformDeInit(void)
{
    Cdd_I2c_DeInit();
    AppUtils_TimerDeinit();

    return;
}

Std_ReturnType Adc_appIoMuxSetup(void)
{
    Std_ReturnType       retVal;
    uint8                wrBuf[2U];
    Cdd_I2c_SequenceType iomuxWrSeqId;
    Cdd_I2c_ChannelType  iomuxWrChId;
    uint8                outPortOffset, configPortOffset;
    boolean              isBoardVerE1 = FALSE;

    AppUtils_printf(APP_NAME ": Configuring IO Mux on the board ...\r\n");

    /* Check which version of board and decide which IO mux is connected */
    if (Adc_appIsIoMuxTCA6424() == TRUE)
    {
        isBoardVerE1     = FALSE;
        outPortOffset    = TCA6424_REG_OUTPUT_PORT_0;
        configPortOffset = TCA6424_REG_CONFIG_PORT_0;
    }
    else
    {
        isBoardVerE1     = TRUE;
        outPortOffset    = TCA6416_REG_OUTPUT_PORT_0;
        configPortOffset = TCA6416_REG_CONFIG_PORT_0;
    }

    iomuxWrSeqId = ADC_APP_I2C_IO_MUX_WR_SEQ;
    iomuxWrChId  = ADC_APP_I2C_IO_MUX_WR_CH;
    /*
     * Port 0 - Enable/Disable settings
     * ADC3_MUX_SEL - 0 (Bit 5) and ADC4_MUX_SEL = 1 (Bit 6).
     * ADC3_MUX_SEL: ADC_R1_AIN1 and ADC_R0_AIN(0,1)
     * ADC4_MUX_SEL: ADC_R0_AIN(2,3) and ADC_R1_AIN(2,3)
     */
    wrBuf[0U] = outPortOffset;
    wrBuf[1U] = 0xDFU;
    retVal    = Adc_appI2cWrite(iomuxWrSeqId, iomuxWrChId, &wrBuf[0U], 2U, isBoardVerE1);
    if (retVal != E_OK)
    {
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Write failed!!!\n\r");
    }

    /*
     * Port 1 - Enable/Disable settings
     * ADC1_MUX_SEL - 1 (Bit 6), ADC2_MUX_SEL - 0 (Bit 7) and ADC5_MUX_SEL - 1 (Bit 0)
     * ADC1_MUX_SEL: ADC0_AIN0, ADC0_AIN1 (don't care for this app)
     * ADC2_MUX_SEL: ADC_CALx/ADC_R0_AIN(0,1)
     * ADC5_MUX_SEL: ADC_R0_AIN0 ADC_R1_AIN0
     */
    wrBuf[0U] = outPortOffset + 1U;
    wrBuf[1U] = 0x7FU;
    retVal    = Adc_appI2cWrite(iomuxWrSeqId, iomuxWrChId, &wrBuf[0U], 2U, isBoardVerE1);
    if (retVal != E_OK)
    {
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Write failed!!!\n\r");
    }

    /* Port 0 - Config */
    wrBuf[0U] = configPortOffset;
    wrBuf[1U] = 0x97U; /* Sets bits 5 and 6 to zero */
    retVal    = Adc_appI2cWrite(iomuxWrSeqId, iomuxWrChId, &wrBuf[0U], 2U, isBoardVerE1);
    if (retVal != E_OK)
    {
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Write failed!!!\n\r");
    }

    /* Port 1 - Config */
    wrBuf[0U] = configPortOffset + 1U;
    wrBuf[1U] = 0x3EU; /* Sets bits 0, 6 and 7 to zero */
    retVal    = Adc_appI2cWrite(iomuxWrSeqId, iomuxWrChId, &wrBuf[0U], 2U, isBoardVerE1);
    if (retVal != E_OK)
    {
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Write failed!!!\n\r");
    }

    return retVal;
}

static boolean Adc_appIsIoMuxTCA6424(void)
{
    boolean              result = TRUE;
    Std_ReturnType       retVal;
    uint8                wrBuf[2U], boardVer[2U];
    Cdd_I2c_SequenceType eepromWrSeqId, eepromRdSeqId;
    Cdd_I2c_ChannelType  eepromWrChId, eepromRdChId;

    eepromWrSeqId = ADC_APP_I2C_EEPROM_WR_SEQ;
    eepromWrChId  = ADC_APP_I2C_EEPROM_WR_CH;
    eepromRdSeqId = ADC_APP_I2C_EEPROM_RD_SEQ;
    eepromRdChId  = ADC_APP_I2C_EEPROM_RD_CH;

    wrBuf[0U] = 0x00U; /* 16-bit offset */
    wrBuf[1U] = 0x1AU; /* Revision offset */
    retVal    = Adc_appI2cWrite(eepromWrSeqId, eepromWrChId, &wrBuf[0U], 2U, FALSE);
    if (retVal != E_OK)
    {
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Write failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        boardVer[0U] = 0xFFU;
        boardVer[1U] = 0xFFU;
        retVal       = Adc_appI2cRead(eepromRdSeqId, eepromRdChId, &boardVer[0U], 2U);
        if (retVal != E_OK)
        {
            GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Read failed!!!\n\r");
        }
    }

    if (retVal == E_OK)
    {
        /* Default slave address of IO Expander configured -> 34U */
        if ((boardVer[0] == 'A') && (boardVer[1] == '\0'))
        {
            /* boardVer is REV A */
            AppUtils_printf(
                APP_NAME ": Detected CC version is REV A. Calling TCA6424 Drivers for io expander configurations\r\n");
            result = TRUE;
        }
        else if ((boardVer[0] == 'E') && (boardVer[1] == '1'))
        {
            /* boardVer is E1 */
            /*IO expander for E1 version board have slave address 32U.*/
            AppUtils_printf(APP_NAME
                            ": Detected CC version is E1. Calling TCA6416 Drivers for io expander configurations\r\n");
            result = FALSE;
        }
        else if ((boardVer[0] == 'E') && (boardVer[1] == '2'))
        {
            /* boardVer is E2 */
            AppUtils_printf(APP_NAME
                            ": Detected CC version is E2. Calling TCA6424 Drivers for io expander configurations\r\n");
            result = TRUE;
        }
        else
        {
            /* boardVer is invalid */
            /* Do nothing and default to latest board as latest board use TCA6424 IO Expander */
        }
    }

    return result;
}

static Std_ReturnType Adc_appI2cWrite(Cdd_I2c_SequenceType wrSeqId, Cdd_I2c_ChannelType wrChId, uint8 *pWrBuf,
                                      uint16 size, boolean boardVerE1)
{
    Std_ReturnType retVal = E_OK;

    if (boardVerE1 == TRUE)
    {
        /* Update slave address as 32U for E1 board */
        retVal = Cdd_I2c_SetupEBDynamic(wrChId, TCA6416_SLAVE_ADDRESS, pWrBuf, NULL_PTR, size);
    }
    else
    {
        /* Default slave address 34U */
        retVal = Cdd_I2c_SetupEB(wrChId, pWrBuf, NULL_PTR, size);
    }

    if (retVal != E_OK)
    {
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        Cdd_I2c_AsyncTransmit(wrSeqId);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(wrSeqId))
        {
            /* Wait for sequence to be ready */
        }
    }

    return retVal;
}

static Std_ReturnType Adc_appI2cRead(Cdd_I2c_SequenceType rdSeqId, Cdd_I2c_ChannelType rdChId, uint8 *pRdBuf,
                                     uint16 size)
{
    Std_ReturnType retVal = E_OK;

    retVal = Cdd_I2c_SetupEB(rdChId, NULL_PTR, pRdBuf, size);
    if (retVal != E_OK)
    {
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, APP_NAME ": I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        Cdd_I2c_AsyncTransmit(rdSeqId);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(rdSeqId))
        {
            /* Wait for sequence to be ready */
        }
    }

    return retVal;
}

void I2c_Seq0_Complete(void)
{
    return;
}

void I2c_Seq1_Complete(void)
{
    return;
}

void I2c_Seq2_Complete(void)
{
    return;
}

void I2c_Seq3_Complete(void)
{
    return;
}

void I2c_Seq0_Fail(uint8 Error_Code)
{
    return;
}

void I2c_Seq1_Fail(uint8 Error_Code)
{
    return;
}

void I2c_Seq2_Fail(uint8 Error_Code)
{
    return;
}

void I2c_Seq3_Fail(uint8 Error_Code)
{
    return;
}

void SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
