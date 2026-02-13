/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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

#include <stdio.h>
#include "AppPimc.h"

/* MCSPI Driver handles */
MCSPI_Handle gMcspiHandle[CONFIG_MCSPI_NUM_INSTANCES];

/* MCSPI Driver Open Parameters */
MCSPI_OpenParams gMcspiOpenParams[CONFIG_MCSPI_NUM_INSTANCES] = {
    {
        .transferMode        = MCSPI_TRANSFER_MODE_BLOCKING,
        .transferTimeout     = Pmic_SystemP_WAIT_FOREVER,
        .transferCallbackFxn = NULL_PTR,
        .msMode              = MCSPI_MS_MODE_CONTROLLER,
        .mcspiDmaIndex       = -1,
    },
};
/* MCSPI Driver Channel Configurations */
MCSPI_ChConfig gConfigMcspi0ChCfg[CONFIG_MCSPI0_NUM_CH] = {
    {
        .chNum            = MCSPI_CHANNEL_0,
        .frameFormat      = MCSPI_FF_POL0_PHA0,
        .bitRate          = 1000000,
        .csPolarity       = MCSPI_CS_POL_LOW,
        .trMode           = MCSPI_TR_MODE_TX_RX,
        .inputSelect      = MCSPI_IS_D1,
        .dpe0             = MCSPI_DPE_ENABLE,
        .dpe1             = MCSPI_DPE_DISABLE,
        .slvCsSelect      = MCSPI_SLV_CS_SELECT_0,
        .startBitEnable   = FALSE,
        .startBitPolarity = MCSPI_SB_POL_LOW,
        .csIdleTime       = MCSPI_TCS0_0_CLK,
        .defaultTxData    = 0x0U,
        .txFifoTrigLvl    = 16U,
        .rxFifoTrigLvl    = 16U,
    },
};

/* MCSPI atrributes */
static MCSPI_Attrs gMcspiAttrs[CONFIG_MCSPI_NUM_INSTANCES] = {
    {
        .baseAddr     = CSL_MCSPI1_U_BASE,
        .inputClkFreq = 50000000U,
        .intrNum      = CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR,
        .operMode     = MCSPI_OPER_MODE_POLLED,
        .intrPriority = 4U,
        .chMode       = MCSPI_CH_MODE_SINGLE,
        .pinMode      = MCSPI_PINMODE_4PIN,
        .initDelay    = MCSPI_INITDLY_0,
    },
};
/* MCSPI objects - initialized by the driver */
static MCSPI_Object gMcspiObjects[CONFIG_MCSPI_NUM_INSTANCES];
/* MCSPI driver configuration */
MCSPI_Config        gMcspiConfig[CONFIG_MCSPI_NUM_INSTANCES] = {
    {
        &gMcspiAttrs[CONFIG_MCSPI0],
        &gMcspiObjects[CONFIG_MCSPI0],
    },
};

uint32_t gMcspiConfigNum = CONFIG_MCSPI_NUM_INSTANCES;

/*
 * This is an empty project provided for all cores present in the device.
 * User can use this project to start their application by adding more SysConfig modules.
 *
 * This application does driver and board init and just prints the pass string on the console.
 * In case of the main core, the print is redirected to the UART console.
 * For all other cores, CCS prints are used.
 */

#define APP_MCSPI_MSGSIZE (1U)
uint32_t gMcspiTxBuffer[APP_MCSPI_MSGSIZE];
uint32_t gMcspiRxBuffer[APP_MCSPI_MSGSIZE];

/* Sub address command as per tps653860xx datasheet */
#define CRC_POLY  (0x107U)
#define CRC_LEN   (9U)
#define CMD_SHIFT (24U)
#define RW_SHIFT  (16U)
#define DAT_SHIFT (8U)
#define CRC_SHIFT (0U)

#define CMD_DEVICE_ID (0x00)
#define CMD_REV_ID    (0x01)
#define CMD_RD_EN     (0x10)
#define CMD_WR_EN     (0x00)

#define CMD_REG_UNLOCK (0x03)
#define CMD_REG_STATUS (0x09)

#define CMD_LDO2_CFG 0x1F
#define CMD_LDO3_CFG 0x20
#define CMD_LDO4_CFG 0x21
#define CMD_LDO_CTRL 0x26

#define DAT_REG_UNLOCK_1 (0x98)
#define DAT_REG_UNLOCK_2 (0xB8)

#define DAT_LDO2_CFG (0x93)
#define DAT_LDO3_CFG (0x94)
#define DAT_LDO4_CFG (0x90)
#define DAT_LDO_CTRL (0x55)

#define PMIC_MCSPI_MSGSIZE (1U)

void    Drivers_mcspiOpen(void);
int32_t PMIC_mcspiWriteRegister(MCSPI_Handle handle, MCSPI_Transaction *spiTransaction, uint8_t cmd, uint8_t data);
int32_t PMIC_mcspiReadRegister(MCSPI_Handle handle, MCSPI_Transaction *spiTransaction, uint8_t cmd, uint8_t *data);
int32_t PMIC_tps653860xxConfigure(void);
uint8_t PMIC_calcCRC8(char cmd, char rdwr, char dat);
uint8_t CalcCRC8(char cmd, char rdwr, char dat);

void Pmic_Enable(void)
{
    Drivers_mcspiOpen();
    PMIC_tps653860xxConfigure();
    MCSPI_close(gMcspiHandle[CONFIG_MCSPI0]);
}

void Drivers_mcspiOpen(void)
{
    uint32_t instCnt, chCnt;

    for (instCnt = 0U; instCnt < CONFIG_MCSPI_NUM_INSTANCES; instCnt++)
    {
        gMcspiHandle[instCnt] = NULL_PTR; /* Init to NULL so that we can exit gracefully */
    }

    /* Open all instances */
    for (instCnt = 0U; instCnt < CONFIG_MCSPI_NUM_INSTANCES; instCnt++)
    {
        gMcspiHandle[instCnt] = MCSPI_open(instCnt, &gMcspiOpenParams[instCnt]);
    }

    /* Channel configuration */
    for (chCnt = 0U; chCnt < CONFIG_MCSPI0_NUM_CH; chCnt++)
    {
        MCSPI_chConfig(gMcspiHandle[CONFIG_MCSPI0], &gConfigMcspi0ChCfg[chCnt]);
    }

    return;
}

int32_t PMIC_tps653860xxConfigure(void)
{
    int32_t status = Pmic_SystemP_SUCCESS;

    MCSPI_Transaction spiTransaction;
    uint8_t           data = 0;

    if (status == Pmic_SystemP_SUCCESS)
    {
        /* Setup SPI transfers*/
        MCSPI_Transaction_init(&spiTransaction);
        spiTransaction.channel = MCSPI_CHANNEL_0;
        /* number of bits/frame - this defines the buffer data type used */
        spiTransaction.dataSize = (uint32_t)32;
        /* CS will de-assert automatically after the frame completes */
        spiTransaction.csDisable = TRUE;
        /* number of frames in the transfer */
        spiTransaction.count = (uint32_t)1;
        spiTransaction.txBuf = (void *)gMcspiTxBuffer;
        spiTransaction.rxBuf = (void *)gMcspiRxBuffer;
        spiTransaction.args  = NULL_PTR;

        status = PMIC_mcspiReadRegister(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction, CMD_REV_ID, &data);

        if (status == Pmic_SystemP_SUCCESS)
        {
            status +=
                PMIC_mcspiWriteRegister(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction, CMD_REG_UNLOCK, DAT_REG_UNLOCK_1);
            status +=
                PMIC_mcspiWriteRegister(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction, CMD_REG_UNLOCK, DAT_REG_UNLOCK_2);
            status += PMIC_mcspiWriteRegister(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction, CMD_LDO2_CFG, DAT_LDO2_CFG);
            status += PMIC_mcspiWriteRegister(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction, CMD_LDO3_CFG, DAT_LDO3_CFG);
            status += PMIC_mcspiWriteRegister(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction, CMD_LDO4_CFG, DAT_LDO4_CFG);
            status += PMIC_mcspiWriteRegister(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction, CMD_LDO_CTRL, DAT_LDO_CTRL);
        }
    }

    return status;
}

int32_t PMIC_mcspiWriteRegister(MCSPI_Handle handle, MCSPI_Transaction *spiTransaction, uint8_t cmd, uint8_t data)
{
    int32_t status = Pmic_SystemP_SUCCESS;
    uint8_t crc    = 0;

    crc               = PMIC_calcCRC8(cmd, CMD_WR_EN, (char)data);
    gMcspiTxBuffer[0] = (cmd << CMD_SHIFT) | (CMD_WR_EN << RW_SHIFT) | (data << DAT_SHIFT) | crc;
    gMcspiRxBuffer[0] = 0;

    status = MCSPI_transfer(handle, spiTransaction);

    return status;
}

int32_t PMIC_mcspiReadRegister(MCSPI_Handle handle, MCSPI_Transaction *spiTransaction, uint8_t cmd, uint8_t *data)
{
    int32_t status = Pmic_SystemP_SUCCESS;
    uint8_t crc    = 0;

    crc               = PMIC_calcCRC8(cmd, CMD_RD_EN, 0);
    gMcspiTxBuffer[0] = (cmd << CMD_SHIFT) | (CMD_RD_EN << RW_SHIFT) | (0 << DAT_SHIFT) | crc;
    gMcspiRxBuffer[0] = 0;

    status = MCSPI_transfer(handle, spiTransaction);

    *data = (gMcspiRxBuffer[0] >> 8) & 0xFF;

    return status;
}

uint8_t PMIC_calcCRC8(char cmd, char rdwr, char dat)
{
    int      i = 0;
    uint8_t  crc;
    uint32_t tmp;

    tmp = ((cmd << 16) | (rdwr << 8) | dat);
    crc = 0xFF;

    /* Standard CRC-8 polynomial ,X8 + X2 + X1 + 1.,is used to calculate the
     * checksum value based on the command and data which the MCU transmits
     * to the TPS653850A-Q1 device.
     */

    for (i = 0; i < 24; i++)
    {
        long D;
        D   = (tmp & 0x800000) / 8388608;
        tmp = (tmp & 0x7FFFFF) * 2;
        D   = (D ^ (((long)crc & 0x80) / 128));
        crc = (crc & 0x7Fu) * 2u;
        D   = D * 7;
        crc = (crc ^ (unsigned char)D);
    }

    /* Return the PMIC SPI MCRC value */
    return crc;
}
