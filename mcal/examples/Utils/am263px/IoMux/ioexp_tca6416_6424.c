/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "ioexp_tca6416_6424.h"
#include "hw_types.h"
#include "Mcu.h"
#include "Fls.h"
#include "app_utilsI2c.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define PIN_STATE_HIGH (1U)
#define PIN_STATE_LOW  (0U)

#define IO_MUX_OSPI_RST_SEL_PORT_LINE (0U)  // PORT 0, PIN 0    -> ioIndex : 0*8 + 0 = 0

#define EEPROM_OFFSET_READ_PCB_REV   (0x1AU)
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

#define I2C_APP_EEPROM_HW_UNIT   (CDD_I2C_HW_UNIT_0)
#define I2C_APP_EEPROM_ADDRESS   (0x50U)
#define I2C_APP_IOMUX_HW_UNIT    (CDD_I2C_HW_UNIT_2)
#define I2C_APP_IOMUX_ADDRESS_E1 (0x20U)
#define I2C_APP_IOMUX_ADDRESS    (0x22U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*Buffer to store transmission data for IOMUX*/
uint8 txBufferIomux[2];
/*Buffer to store reception data for IOMUX*/
uint8 rxBufferIomux[2];
/*Buffer to store transmission data for Eeprom*/
uint8 txBufferEeprom[2];
/*Buffer to store reception data for Eeprom*/
uint8 boardVerEeprom[2];

Cdd_I2c_AddressType ioMuxDeviceAddress = I2C_APP_IOMUX_ADDRESS;

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
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 1U);
        I2c_utilsRead(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &rxBufferIomux[0], 1U);

        if (TCA6416_OUT_STATE_HIGH == state)
        {
            txBufferIomux[1] = rxBufferIomux[0] | (0x01 << portPin);
        }
        else
        {
            txBufferIomux[1] = (rxBufferIomux[0]) & (~(0x01 << portPin));
        }
        txBufferIomux[0] = TCA6416_REG_OUTPUT_PORT_0 + port;
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 2U);
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
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 1U);
        I2c_utilsRead(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &rxBufferIomux[0], 1U);

        if (TCA6424_OUT_STATE_HIGH == state)
        {
            txBufferIomux[1] = rxBufferIomux[0] | (0x01 << portPin);
        }
        else
        {
            txBufferIomux[1] = (rxBufferIomux[0]) & (~(0x01 << portPin));
        }
        txBufferIomux[0] = TCA6424_REG_OUTPUT_PORT_0 + port;
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 2U);
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
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 1U);
        I2c_utilsRead(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &rxBufferIomux[0], 1U);

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
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 2U);
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
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 1U);
        I2c_utilsRead(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &rxBufferIomux[0], 1U);

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
        I2c_utilsWrite(I2C_APP_IOMUX_HW_UNIT, ioMuxDeviceAddress, &txBufferIomux[0], 2U);
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

void mcanEnableTransceiver(void)
{
    uint32 status = E_OK;

#if defined AM263PX_C_PACKAGE
    status += TCA6416_6424_Transceiver();
#else
    status += EEPROM_CAT24M_read(EEPROM_OFFSET_READ_PCB_REV, EEPROM_READ_PCB_REV_DATA_LEN);
    if (status == E_OK)
    {
        if ((boardVerEeprom[1] == '2') && (boardVerEeprom[0] == 'E'))
        {
            /* boardVer is E2 */
            status = TCA6416_6424_Transceiver();
        }
        else if ((boardVerEeprom[1] == '1') && (boardVerEeprom[0] == 'E'))
        {
            /* boardVer is E1 */
            ioMuxDeviceAddress = I2C_APP_IOMUX_ADDRESS_E1;
            /* MCAN Transceiver is enabled by default in E1*/
        }
        else
        {
            /* boardVer is REV A */
            status = TCA6416_6424_Transceiver();
        }
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
        I2c_utilsWrite(I2C_APP_EEPROM_HW_UNIT, I2C_APP_EEPROM_ADDRESS, &txBufferEeprom[0], 2U);
        /*Read data*/
        I2c_utilsRead(I2C_APP_EEPROM_HW_UNIT, I2C_APP_EEPROM_ADDRESS, &boardVerEeprom[0], 2U);
    }

    return (status);
}
#endif

void board_flash_reset(void)
{
    uint32 status = E_OK;

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
        if ((boardVerEeprom[1] == '2') && (boardVerEeprom[0] == 'E'))
        {
            /* boardVer is E2 */
            status += TCA6424_Flash_reset();
        }
        else if ((boardVerEeprom[1] == '1') && (boardVerEeprom[0] == 'E'))
        {
            /* boardVer is E1 */
            ioMuxDeviceAddress  = I2C_APP_IOMUX_ADDRESS_E1;
            status             += TCA6416_Flash_reset();
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
