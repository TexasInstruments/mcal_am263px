/*
 *  Copyright (C) 2023-24 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "ioexp_tca6416_6424.h"
#include "hw_types.h"
#include "Mcu.h"
#include "Cdd_I2c.h"
#include "Fls.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PIN_STATE_HIGH (1U)
#define PIN_STATE_LOW  (0U)

#define IO_MUX_OSPI_RST_SEL_PORT_LINE (0U)  // PORT 0, PIN 0    -> ioIndex : 0*8 + 0 = 0

#define EEPROM_OFFSET_READ_PCB_REV   (0x0022U)
#define EEPROM_READ_PCB_REV_DATA_LEN (0x2U)
#define SIP_FLASH_CFG_VALUE          (0x55)
#ifndef AM263PX_C_PACKAGE
/* PORT 0, PIN 4         -> ioIndex : 0*8 + 4 = 4*/
#define IO_MUX_MCAN_SEL (4U)
/* PORT 2, PIN 1         -> ioIndex : 2*8 + 1 = 17 */
#define IO_MUX_MCAN_STB (17U)
/* MCAN_SEL PIN OUTPUT   -> 0 */
#else
#define IO_MUX_MCAN_STB (10U) /* PORT 1, PIN 2         -> ioIndex : 1*8 + 2 = 10 */
/* MCAN_STB PIN OUTPUT   -> 0 */
#endif

#define TCA6416_IO_MUX_MCAN_STB_PORT_LINE_STATE (TCA6416_OUT_STATE_LOW)
#define TCA6416_REG_OUTPUT_PORT_0               (0x02U)
#define TCA6416_REG_CONFIG_PORT_0               (0x06U)

/**
 *  \anchor TCA6416_Mode
 *  \name IO pin mode - Input or Output
 *  @{
 */
/** \brief Configure IO pin as input */
#define TCA6416_MODE_INPUT (0U)
/** \brief Configure IO pin as output */
#define TCA6416_MODE_OUTPUT (1U)
/** @} */

/**
 *  \anchor TCA6416_OutState
 *  \name IO pin output state - HIGH or LOW
 *  @{
 */
/** \brief Configure IO pin output as LOW */
#define TCA6416_OUT_STATE_LOW (0U)
/** \brief Configure IO pin output as HIGH */
#define TCA6416_OUT_STATE_HIGH (1U)
/** @} */

#define TCA6424_IO_MUX_MCAN_SEL_PORT_LINE_STATE (TCA6424_OUT_STATE_LOW)
/* MCAN_STB PIN OUTPUT   -> 1 */
#define TCA6424_IO_MUX_MCAN_STB_PORT_LINE_STATE (TCA6424_OUT_STATE_HIGH)
#define TCA6424_REG_OUTPUT_PORT_0               (0x04U)
#define TCA6424_REG_CONFIG_PORT_0               (0x0CU)
/**
 *  \anchor TCA6424_Mode
 *  \name IO pin mode - Input or Output
 *  @{
 */
/** \brief Configure IO pin as input */
#define TCA6424_MODE_INPUT (0U)
/** \brief Configure IO pin as output */
#define TCA6424_MODE_OUTPUT (1U)
/** @} */

/**
 *  \anchor TCA6424_OutState
 *  \name IO pin output state - HIGH or LOW
 *  @{
 */
/** \brief Configure IO pin output as LOW */
#define TCA6424_OUT_STATE_LOW (0U)
/** \brief Configure IO pin output as HIGH */
#define TCA6424_OUT_STATE_HIGH (1U)
/** @} */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

volatile boolean rxDoneIomux  = FALSE;
volatile boolean rxDoneEeprom = FALSE;

/*Buffer to store transmission data for IOMUX*/
uint8 txBufferIomux[2];
/*Buffer to store reception data for IOMUX*/
uint8 rxBufferIomux[2];
/*Buffer to store transmission data for Eeprom*/
uint8 txBufferEeprom[2];
/*Buffer to store reception data for Eeprom*/
uint8 boardVerEeprom[2];
// Cdd_I2c_ConfigPtrType I2cConfigSet = NULL_PTR;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32 TCA6416_setOutput(uint32 ioIndex, uint32 state)
{
    uint32 status = E_OK;
    uint32 port, portPin, numIo = 24;
    /* Validate input IO number */
    if (ioIndex >= numIo)
    {
        status = E_NOT_OK;
    }

    if (status == E_OK)
    {
        /* Each port contains 8 IOs */
        port    = ioIndex >> 3U;   /* /8 gives port */
        portPin = ioIndex & 0x07U; /* %8 gives pin within port */

        txBufferIomux[0] = TCA6416_REG_OUTPUT_PORT_0 + port;
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_1);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;

        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
            ;
        /*Read data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
        {
        }
        while (TRUE != rxDoneIomux)
        {
            /*Wait till above sequence is completed*/
        }

        if (TCA6416_OUT_STATE_HIGH == state)
        {
            txBufferIomux[1] = rxBufferIomux[0] | (0x01 << portPin);
        }
        else
        {
            txBufferIomux[1] = (rxBufferIomux[0]) & (~(0x01 << portPin));
        }
        txBufferIomux[0] = TCA6416_REG_OUTPUT_PORT_0 + port;

        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_2);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
    }

    return (status);
}

uint32 TCA6424_setOutput(uint32 ioIndex, uint32 state)
{
    uint32 status = E_OK;
    uint32 port, portPin, numIo = 24;
    /* Validate input IO number */
    if (ioIndex >= numIo)
    {
        status = E_NOT_OK;
    }

    if (status == E_OK)
    {
        /* Each port contains 8 IOs */
        port    = ioIndex >> 3U;   /* /8 gives port */
        portPin = ioIndex & 0x07U; /* %8 gives pin within port */

        txBufferIomux[0] = TCA6424_REG_OUTPUT_PORT_0 + port;
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_1);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;

        /* Read config register value */
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
            ;
        /*Read data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
        {
        }
        while (TRUE != rxDoneIomux)
        {
            /*Wait till above sequence is completed*/
        }

        if (TCA6424_OUT_STATE_HIGH == state)
        {
            txBufferIomux[1] = rxBufferIomux[0] | (0x01 << portPin);
        }
        else
        {
            txBufferIomux[1] = (rxBufferIomux[0]) & (~(0x01 << portPin));
        }
        txBufferIomux[0] = TCA6424_REG_OUTPUT_PORT_0 + port;

        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_2);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
    }

    return (status);
}

uint32 TCA6416_config(uint32 ioIndex, uint32 mode)
{
    uint32 status = E_OK;
    uint32 port, portPin, numIo = 24;

    /* Validate input IO number */
    if (ioIndex >= numIo)
    {
        status = E_NOT_OK;
    }

    if (status == E_OK)
    {
        /* Each port contains 8 IOs */
        port    = ioIndex >> 3U;   /* /8 gives port */
        portPin = ioIndex & 0x07U; /* %8 gives pin within port */

        /* Set config register address - needed for next read */
        txBufferIomux[0] = TCA6416_REG_CONFIG_PORT_0 + port;
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_1);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;

        /* Read config register value */
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
            ;
        /*Read data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
            ;
        while (TRUE != rxDoneIomux)
        {
            /*Wait till above sequence is completed*/
        }

        /* Set output or input mode to particular IO pin - read/modify/write */
        if (TCA6416_MODE_INPUT == mode)
        {
            txBufferIomux[1] = rxBufferIomux[0] | (0x01 << portPin);
        }
        else
        {
            txBufferIomux[1] = rxBufferIomux[0] & ~(0x01 << portPin);
        }
        txBufferIomux[0] = TCA6416_REG_CONFIG_PORT_0 + port;

        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_2);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
    }

    return (status);
}

uint32 TCA6424_config(uint32 ioIndex, uint32 mode)
{
    uint32 status = E_OK;
    uint32 port, portPin, numIo = 24;

    /* Validate input IO number */
    if (ioIndex >= numIo)
    {
        status = E_NOT_OK;
    }

    if (status == E_OK)
    {
        /* Each port contains 8 IOs */
        port    = ioIndex >> 3U;   /* /8 gives port */
        portPin = ioIndex & 0x07U; /* %8 gives pin within port */

        /* Set config register address - needed for next read */
        txBufferIomux[0] = TCA6424_REG_CONFIG_PORT_0 + port;
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_1);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_1))
            ;

        /* Read config register value */
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
            ;
        /*Read data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_0);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_0))
            ;
        while (TRUE != rxDoneIomux)
        {
            /*Wait till above sequence is completed*/
        }

        /* Set output or input mode to particular IO pin - read/modify/write */
        if (TCA6424_MODE_INPUT == mode)
        {
            txBufferIomux[1] = rxBufferIomux[0] | (0x01 << portPin);
        }
        else
        {
            txBufferIomux[1] = rxBufferIomux[0] & ~(0x01 << portPin);
        }
        txBufferIomux[0] = TCA6424_REG_CONFIG_PORT_0 + port;

        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_2);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_2))
            ;
    }

    return (status);
}

uint32 TCA6416_6424_Transceiver(void)
{
    uint32 status = E_OK;
#ifdef AM263PX_C_PACKAGE
    /* For MCAN_STB*/
    status += TCA6416_setOutput(IO_MUX_MCAN_STB, TCA6416_IO_MUX_MCAN_STB_PORT_LINE_STATE);
    status += TCA6416_config(IO_MUX_MCAN_STB, TCA6416_MODE_OUTPUT);
#else
    // /* For MCAN_SEL */
    status  = TCA6424_setOutput(IO_MUX_MCAN_SEL, TCA6424_IO_MUX_MCAN_SEL_PORT_LINE_STATE);
    status += TCA6424_config(IO_MUX_MCAN_SEL, TCA6424_MODE_OUTPUT);
    /* For MCAN_STB*/
    status += TCA6424_setOutput(IO_MUX_MCAN_STB, TCA6424_IO_MUX_MCAN_STB_PORT_LINE_STATE);
    status += TCA6424_config(IO_MUX_MCAN_STB, TCA6424_MODE_OUTPUT);
#endif
    if (status != E_OK)
    {
        AppUtils_printf("IOMUX setup for CAN failed \n\r");
    }
    return status;
}

uint8 I2c_Buffer_Setup(void)
{
    uint8 returnValue = E_OK;

    /* Setup I2c channels */
    /* channel0: read value, channel1: set address Iomux, Iomux channel2: write Iomux*/
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_0, NULL_PTR, &rxBufferIomux[0], 1);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_1, &txBufferIomux[0], NULL_PTR, 1);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_2, &txBufferIomux[0], NULL_PTR, 2);

#if defined AM263PX_SIP_PACKAGE || defined AM263PX_R_PACKAGE
    /* channel4: set address EEPROM, channel3: read value EEPROM */
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_3, NULL_PTR, &boardVerEeprom[0], 2);
    returnValue |= Cdd_I2c_SetupEB(CddI2cConf_CddI2cChannel_CddI2cChannel_4, &txBufferEeprom[0], NULL_PTR, 2);
#endif
    return returnValue;
}

void mcanEnableTransceiver(void)
{
    uint32 status = E_OK;

    I2c_Buffer_Setup();
#if defined AM263PX_C_PACKAGE
    status += TCA6416_6424_Transceiver();
#else
    status += EEPROM_CAT24M_read(EEPROM_OFFSET_READ_PCB_REV, EEPROM_READ_PCB_REV_DATA_LEN);
    if (status == E_OK)
    {
        if (boardVerEeprom[1] == '2' && boardVerEeprom[0] == 'E')
        {
            /* boardVer is E2 */
            status = TCA6416_6424_Transceiver();
        }
    }
    else if (boardVerEeprom[1] == '1' && boardVerEeprom[0] == 'E')
    {
        /* boardVer is E1 */
        /* MCAN Transceiver is enabled by default in E1*/
    }
    else
    {
        /* boardVer is REV A */
        status = TCA6416_6424_Transceiver();
    }
#endif
    if (status == E_OK)
    {
        AppUtils_printf("IOMUX setup for Can successful \n\r");
    }
}

uint32 TCA6416_Flash_reset(void)
{
    uint32 status = E_OK;

    status += TCA6416_config(IO_MUX_OSPI_RST_SEL_PORT_LINE, TCA6416_MODE_OUTPUT);
    status  = TCA6416_setOutput(IO_MUX_OSPI_RST_SEL_PORT_LINE, TCA6416_OUT_STATE_LOW);
    status += TCA6416_setOutput(IO_MUX_OSPI_RST_SEL_PORT_LINE, TCA6416_OUT_STATE_HIGH);

    return status;
}

uint32 TCA6424_Flash_reset(void)
{
    uint32 status = E_OK;

    status += TCA6424_config(IO_MUX_OSPI_RST_SEL_PORT_LINE, TCA6424_MODE_OUTPUT);
    status  = TCA6424_setOutput(IO_MUX_OSPI_RST_SEL_PORT_LINE, TCA6424_OUT_STATE_LOW);
    status += TCA6424_setOutput(IO_MUX_OSPI_RST_SEL_PORT_LINE, TCA6424_OUT_STATE_HIGH);

    return status;
}

#if defined AM263PX_SIP_PACKAGE || defined AM263PX_R_PACKAGE
uint32      EEPROM_CAT24M_read(uint32 offset, uint32 state)
{
    uint32 status     = E_OK;
    uint32 readOffset = offset;

    if (status == E_OK)
    {
        txBufferEeprom[0]  = (readOffset & 0xFF00U) >> 8U;
        txBufferEeprom[1U] = (readOffset & 0x00FFU);
        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_4))
            ;
        /* Start transmission */
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_4);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_4))
            ;

        /* Wait for sequence to be ready */
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_3))
            ;
        /*Read data*/
        Cdd_I2c_AsyncTransmit(CddI2cConf_CddI2cSequence_CddI2cSequence_3);
        while (CDD_I2C_SEQ_OK != Cdd_I2c_GetSequenceResult(CddI2cConf_CddI2cSequence_CddI2cSequence_3))
        {
        }
        while (TRUE != rxDoneEeprom)
        {
            /*Wait till above sequence is completed*/
        }
    }

    return (status);
}
#endif

void updateSlaveAddress()
{
    /* For E1 board IOexpander I2c slave address is 32U, so update it if Board is E1
     * Default configuration (E2 board) have I2c slave address as 34U
     */
    Cdd_I2cChannelContainerLocal[0].SlaveAddress = 32U;
    Cdd_I2cChannelContainerLocal[1].SlaveAddress = 32U;
    Cdd_I2cChannelContainerLocal[2].SlaveAddress = 32U;
}

void board_flash_reset(void)
{
    uint32 status = E_OK;
    // Cdd_I2c_Init(I2cConfigSet);
    I2c_Buffer_Setup();

    /* check if part type is SIP (internal flash) or non-SIP (external flash)
     * if SIP or C package, directly do flash reset using driver API irrespective of board revision, there is no IO
     * expander involved
     */
#if defined AM263PX_SIP_PACKAGE || defined AM263PX_C_PACKAGE
    status += Fls_setResetPinMode(PIN_STATE_HIGH);
    status += Fls_setResetPinMode(PIN_STATE_LOW);
#else
    status += EEPROM_CAT24M_read(EEPROM_OFFSET_READ_PCB_REV, EEPROM_READ_PCB_REV_DATA_LEN);
    if (status == E_OK)
    {
        if (boardVerEeprom[1] == '2' && boardVerEeprom[0] == 'E')
        {
            /* boardVer is E2 */
            status += TCA6424_Flash_reset();
        }
        else if (boardVerEeprom[1] == '1' && boardVerEeprom[0] == 'E')
        {
            /* boardVer is E1 */
            updateSlaveAddress();
            status += TCA6416_Flash_reset();
        }
        else
        {
            /* boardVer is REV A
             * OSPI RESET signal does not come via IO expander
             * Toggle the reset pin directly */
            Fls_setResetPinMode(PIN_STATE_HIGH);
            Fls_setResetPinMode(PIN_STATE_LOW);
        }
    }
#endif

    if (status != E_OK)
    {
        AppUtils_printf("RESET for Flash failed \n\r");
    }
}

void I2c_Eeprom_Read_Callback(void)
{
    rxDoneEeprom = TRUE;
}

void I2c_Eeprom_Address_Ptr_Reset(void)
{
    AppUtils_printf("Eeprom address reset SuccessFul \n\r");
}

void I2c_Iomux_Read_Callback(void)
{
    rxDoneIomux = TRUE;
}
void I2c_Iomux_Write_Callback(void)
{
    AppUtils_printf("Iomux write SuccessFul \n\r");
}
void I2c_Iomux_Write_Callback_Ptr(void)
{
    AppUtils_printf("Iomux address reset SuccessFul \n\r");
}

void I2c_Sequence_Error_Report(uint8 Error_code)
{
    if (CDD_I2C_E_HW_UNIT_BUSY == Error_code)
    {
        AppUtils_printf("Hardware unit busy\n\r");
    }
    else if (CDD_I2C_E_CHANNEL_BUSY == Error_code)
    {
        AppUtils_printf("Channels busy\n\r");
    }
    else if (CDD_I2C_E_ARBITRATION_LOSS == Error_code)
    {
        AppUtils_printf("Arbitration lost\n\r");
    }
    else if (CDD_I2C_E_NACK == Error_code)
    {
        AppUtils_printf("No Acknowledgement\n\r");
    }
    else if (CDD_I2C_E_RECEIVE_SHIFT_REGISTER_FULL == Error_code)
    {
        AppUtils_printf("Receive shift register full\n\r");
    }
    else if (CDD_I2C_E_PARAM_QUEUE_FULL == Error_code)
    {
        AppUtils_printf("Queue full\n\r");
    }
}

void I2c_Eeprom_Read_Callback_Fail(uint8 Error_Code)
{
    AppUtils_printf("Sequence failed while trying to read data from Eeprom\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void I2c_Eeprom_Address_Ptr_Fail(uint8 Error_Code)
{
    AppUtils_printf("Sequence failed while trying to reset Eeprom address pointer\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void I2c_Iomux_Read_Callback_Fail(uint8 Error_Code)
{
    AppUtils_printf("Sequence failed while trying to read data from IOMUX\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void I2c_Iomux_Write_Callback_Ptr_Fail(uint8 Error_Code)
{
    AppUtils_printf("Sequence failed while trying to reset Iomux address pointer\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void I2c_Iomux_Write_Callback_Fail(uint8 Error_Code)
{
    AppUtils_printf("Sequence failed while trying to write to Iomux\n\r");
    I2c_Sequence_Error_Report(Error_Code);
}

void SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
