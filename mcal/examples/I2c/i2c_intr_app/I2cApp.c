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
 *  \file     I2cApp.c
 *
 *  \brief    This file contains the I2C multi-channel test example.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "I2cApp.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * Temperature sensor related params
 */
#if (STD_ON == I2C_APP_TMP_PRESENT)
/* Temperature sensor register offset */
#define I2C_APP_TMP_REG_MANUFACTURER_ID (0xFEU)
#define I2C_APP_TMP_REG_DEVICE_ID       (0xFFU)

/* Temperature sensor expected values */
#define I2C_APP_TMP_REG_MANUFACTURER_ID_EXPECTED (0x55U)
#define I2C_APP_TMP_REG_DEVICE_ID_EXPECTED       (0x12U)

/* Write buffer size - one word for writing register offset */
#define I2C_APP_TMP_WR_BUF_SIZE (1U)
/* Read buffer size - entire 256 byte register space */
#define I2C_APP_TMP_RD_BUF_SIZE (256U)
#endif

/* Trace mask */
#define I2C_APP_TRACE_MASK (GT_INFO1 | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == I2C_APP_EEPROM_PRESENT)
static Std_ReturnType I2c_appEepromTest(void);
static Std_ReturnType I2c_appEepromRead(uint32 offset, uint8 *pRdBuf, uint16 size);
static Std_ReturnType I2c_appEepromPageWrite(uint32 offset, const uint8 *pWrBuf, uint16 size);
#endif
#if (STD_ON == I2C_APP_TMP_PRESENT)
static boolean        I2c_appTempSensorIsValidOffset(uint16 offset);
static Std_ReturnType I2c_appTempSensorTest(void);
#endif

Std_ReturnType I2c_write(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf, uint16 size);
Std_ReturnType I2c_read(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pRdBuf, uint16 size);
Std_ReturnType I2c_writeRead(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                             uint8 *pRdBuf, uint16 wrSize, uint16 rdSize);
Std_ReturnType I2c_writeReadRestart(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                                    uint8 *pRdBuf, uint16 wrSize, uint16 rdSize);

static void I2c_appTest(void);
static void I2c_appInit(void);
static void I2c_appDeInit(void);
#if (STD_OFF == CDD_I2C_POLLING_MODE)
static void I2c_appInterruptConfig(void);
#endif
static void I2c_appSequenceErrorReport(uint8 errorCode);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile boolean gI2cAppSeqDone    = FALSE;
static volatile uint8   gI2cAppSeqErrCode = CDD_I2C_E_NO_ERROR;

/* Test pass flag */
static uint32 gTestPassed = E_OK;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    I2c_appInit();
    I2c_appTest();
    I2c_appDeInit();

    return 0;
}

static void I2c_appTest(void)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == I2C_APP_EEPROM_PRESENT)
    /* EEPROM test */
    retVal = I2c_appEepromTest();
    if (E_OK != retVal)
    {
        gTestPassed = retVal;
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " I2C EEPROM Test Failed!!\n\r");
    }
#endif
#if (STD_ON == I2C_APP_TMP_PRESENT)
    /* Temperature sensor test */
    retVal = I2c_appTempSensorTest();
    if (E_OK != retVal)
    {
        gTestPassed = retVal;
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " I2C Temp Sensor Test Failed!!\n\r");
    }
#endif

    return;
}

#if (STD_ON == I2C_APP_EEPROM_PRESENT)
static Std_ReturnType I2c_appEepromTest(void)
{
    Std_ReturnType retVal = E_OK;
    uint32         offset;
    /* static so that buffers don't go to stack */
    static uint8   txBuf[I2C_APP_EEPROM_PAGE_SIZE];
    static uint8   rxBuf[I2C_APP_EEPROM_PAGE_SIZE];
    uint16         size = I2C_APP_EEPROM_PAGE_SIZE;

    /* Read and print first page */
    memset(&rxBuf[0U], 0xDEU, I2C_APP_EEPROM_PAGE_SIZE);
    retVal = I2c_appEepromRead(0U, &rxBuf[0U], I2C_APP_EEPROM_PAGE_SIZE);
    if (retVal == E_OK)
    {
        /* Print board info */
        for (uint32 index = 0U; index < I2C_APP_EEPROM_BOARD_INFO_SIZE; index++)
        {
            AppUtils_printf(APP_NAME ": EEPROM Data 0x%0.4X: 0x%0.2X\n\r", index, rxBuf[index]);
        }
    }

    if (retVal == E_OK)
    {
        /* Write and verify a page except first which has the board revision data */
        uint16 page = 1U;
        AppUtils_printf(APP_NAME ": EEPROM Program and verify page: %d ...\n\r", page);

        /* Reset buffers */
        offset = page * I2C_APP_EEPROM_PAGE_SIZE;
        for (uint16 index = 0U; index < I2C_APP_EEPROM_PAGE_SIZE; index++)
        {
            txBuf[index] = (uint8)index;
        }
        memset(&rxBuf[0U], 0xDEU, size);

        /* Perform page write */
        retVal = I2c_appEepromPageWrite(offset, &txBuf[0U], size);
        if (retVal != E_OK)
        {
            GT_1trace(I2C_APP_TRACE_MASK, GT_ERR, " EEPROM Program failed for %d page!!!\n\r", page);
        }

        /* Wait for programming to complete - otherwise reads will be NACK'd */
        AppUtils_delay(I2C_APP_EEPROM_PROG_TIME_MS);

        /* Read data */
        retVal += I2c_appEepromRead(offset, &rxBuf[0U], size);
        if (retVal != E_OK)
        {
            GT_1trace(I2C_APP_TRACE_MASK, GT_ERR, " EEPROM Read failed for %d page!!!\n\r", page);
        }

        /* Verify data */
        if (memcmp(&rxBuf[0U], &txBuf[0U], size))
        {
            GT_1trace(I2C_APP_TRACE_MASK, GT_ERR, " EEPROM Data Mismatch!! Page: %d\n\r", page);
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}

static Std_ReturnType I2c_appEepromRead(uint32 offset, uint8 *pRdBuf, uint16 size)
{
    Std_ReturnType      retVal = E_OK;
    Cdd_I2c_AddressType deviceAddress;
    uint8               txBuf[I2C_APP_EEPROM_ADDR_SIZE];

    deviceAddress = I2C_APP_EEPROM_ADDRESS;
    if (offset >= (64U * 1024U))
    {
        /* Use next device address, if offset is more than 16-bit */
        deviceAddress++;
    }
    txBuf[0U] = (uint8)(offset >> 8U);
    txBuf[1U] = (uint8)offset;
    retVal =
        I2c_writeReadRestart(I2C_APP_EEPROM_HW_UNIT, deviceAddress, &txBuf[0U], pRdBuf, I2C_APP_EEPROM_ADDR_SIZE, size);

    return retVal;
}

static Std_ReturnType I2c_appEepromPageWrite(uint32 offset, const uint8 *pWrBuf, uint16 size)
{
    Std_ReturnType      retVal = E_OK;
    Cdd_I2c_AddressType deviceAddress;
    static uint8        txBuf[I2C_APP_EEPROM_ADDR_SIZE + I2C_APP_EEPROM_PAGE_SIZE];

    if (size > I2C_APP_EEPROM_PAGE_SIZE)
    {
        GT_1trace(I2C_APP_TRACE_MASK, GT_ERR, " EEPROM Invalid page size to program: %d ...\n\r", size);
        retVal = E_NOT_OK;
    }

    if (retVal == E_OK)
    {
        deviceAddress = I2C_APP_EEPROM_ADDRESS;
        if (offset >= (64U * 1024U))
        {
            /* Use next device address, if offset is more than 16-bit */
            deviceAddress++;
        }
        txBuf[0U] = (uint8)(offset >> 8U);
        txBuf[1U] = (uint8)offset;
        memcpy(&txBuf[I2C_APP_EEPROM_ADDR_SIZE], pWrBuf, size);
        retVal = I2c_write(I2C_APP_EEPROM_HW_UNIT, deviceAddress, &txBuf[0U], I2C_APP_EEPROM_ADDR_SIZE + size);
    }

    return retVal;
}
#endif

#if (STD_ON == I2C_APP_TMP_PRESENT)
/* All offsets of temp sensor is not valid for read/write.
 * For invalid offsets, the temp sensor NACKs any operation */
static boolean I2c_appTempSensorIsValidOffset(uint16 offset)
{
    boolean isValid = FALSE;

    if ((offset >= 0x00U) && (offset <= 0x08U))
    {
        isValid = TRUE;
    }
    if ((offset >= 0x10U) && (offset <= 0x1AU))
    {
        isValid = TRUE;
    }
    if ((offset >= 0x20U) && (offset <= 0x22U))
    {
        isValid = TRUE;
    }
    if ((offset >= 0x30U) && (offset <= 0x37U))
    {
        isValid = TRUE;
    }
    if ((offset >= 0xFEU) && (offset <= 0xFFU))
    {
        isValid = TRUE;
    }

    return isValid;
}

static Std_ReturnType I2c_appTempSensorTest(void)
{
    Std_ReturnType retVal = E_OK;
    /* static so that buffers don't go to stack */
    static uint8   txBuf[I2C_APP_TMP_WR_BUF_SIZE];
    static uint8   rxBuf[I2C_APP_TMP_RD_BUF_SIZE];

    /* Test with individual read and write API */
    AppUtils_printf(APP_NAME ": Temperature sensor separate write and read test ...\n\r");
    /* Read all the register and store */
    for (uint16 offset = 0U; offset < I2C_APP_TMP_RD_BUF_SIZE; offset++)
    {
        txBuf[0U]     = (uint8)offset;
        rxBuf[offset] = 0xDEU;
        if (I2c_appTempSensorIsValidOffset(offset) == TRUE)
        {
            retVal += I2c_write(I2C_APP_TMP_HW_UNIT, I2C_APP_TMP_ADDRESS, &txBuf[0U], 1U);
            retVal += I2c_read(I2C_APP_TMP_HW_UNIT, I2C_APP_TMP_ADDRESS, &rxBuf[offset], 1U);
        }
    }

    /* Check correctness of data for every iteration */
    if (rxBuf[I2C_APP_TMP_REG_MANUFACTURER_ID] != I2C_APP_TMP_REG_MANUFACTURER_ID_EXPECTED)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Temperature sensor manufacturer ID mismatch!!\n\r");
        retVal = E_NOT_OK;
    }
    if (rxBuf[I2C_APP_TMP_REG_DEVICE_ID] != I2C_APP_TMP_REG_DEVICE_ID_EXPECTED)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Temperature sensor device ID mismatch!!\n\r");
        retVal = E_NOT_OK;
    }

    /* Test with write+read API with restart */
    AppUtils_printf(APP_NAME ": Temperature sensor write+read with restart test ...\n\r");
    /* Read all the register and store */
    for (uint16 offset = 0U; offset < I2C_APP_TMP_RD_BUF_SIZE; offset++)
    {
        txBuf[0U]     = (uint8)offset;
        rxBuf[offset] = 0xDEU;
        if (I2c_appTempSensorIsValidOffset(offset) == TRUE)
        {
            retVal +=
                I2c_writeReadRestart(I2C_APP_TMP_HW_UNIT, I2C_APP_TMP_ADDRESS, &txBuf[0U], &rxBuf[offset], 1U, 1U);
        }
    }

    /* Check correctness of data for every iteration */
    if (rxBuf[I2C_APP_TMP_REG_MANUFACTURER_ID] != I2C_APP_TMP_REG_MANUFACTURER_ID_EXPECTED)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Temperature sensor manufacturer ID mismatch!!\n\r");
        retVal = E_NOT_OK;
    }
    if (rxBuf[I2C_APP_TMP_REG_DEVICE_ID] != I2C_APP_TMP_REG_DEVICE_ID_EXPECTED)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Temperature sensor device ID mismatch!!\n\r");
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif

Std_ReturnType I2c_write(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf, uint16 size)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        wrChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId  = I2C_APP_SEQ_ID_HW_UNIT_0_WR;
    wrChId = I2C_APP_CH_ID_HW_UNIT_0_WR;
    if (hwUnitId == CDD_I2C_HW_UNIT_2)
    {
        /* Assumes HW UNIT 1 is not present. Otherwise need to do += (2 * x) */
        seqId  += I2C_APP_NUM_SEQ_PER_HW_UNIT;
        wrChId += I2C_APP_NUM_CH_PER_HW_UNIT;
    }

    /* Dynamically setup the slave address */
    retVal = Cdd_I2c_SetupEBDynamic(wrChId, deviceAddress, pWrBuf, NULL_PTR, size);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, APP_NAME ": I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        gI2cAppSeqDone    = FALSE;
        gI2cAppSeqErrCode = CDD_I2C_E_NO_ERROR;
        retVal            = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
        }
        else
        {
            /* Wait for completion */
            while (1U)
            {
#if (STD_ON == CDD_I2C_POLLING_MODE)
                /* Needed only for polled mode transfers */
                Cdd_I2c_MainFunction();
#endif

                /* Check if sequence is complete */
                seqResult = Cdd_I2c_GetSequenceResult(seqId);
                if (!((seqResult == CDD_I2C_SEQ_PENDING) || (seqResult == CDD_I2C_SEQ_QUEUED)))
                {
                    break;
                }
            }

            if (seqResult != CDD_I2C_SEQ_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (gI2cAppSeqDone != TRUE)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }
            if (gI2cAppSeqErrCode != CDD_I2C_E_NO_ERROR)
            {
                I2c_appSequenceErrorReport(gI2cAppSeqErrCode);
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(wrChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

Std_ReturnType I2c_read(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pRdBuf, uint16 size)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        rdChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId  = I2C_APP_SEQ_ID_HW_UNIT_0_RD;
    rdChId = I2C_APP_CH_ID_HW_UNIT_0_RD;
    if (hwUnitId == CDD_I2C_HW_UNIT_2)
    {
        /* Assumes HW UNIT 1 is not present. Otherwise need to do += (2 * x) */
        seqId  += I2C_APP_NUM_SEQ_PER_HW_UNIT;
        rdChId += I2C_APP_NUM_CH_PER_HW_UNIT;
    }

    /* Dynamically setup the slave address */
    retVal = Cdd_I2c_SetupEBDynamic(rdChId, deviceAddress, NULL_PTR, pRdBuf, size);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, APP_NAME ": I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        gI2cAppSeqDone    = FALSE;
        gI2cAppSeqErrCode = CDD_I2C_E_NO_ERROR;
        retVal            = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
        }
        else
        {
            /* Wait for completion */
            while (1U)
            {
#if (STD_ON == CDD_I2C_POLLING_MODE)
                /* Needed only for polled mode transfers */
                Cdd_I2c_MainFunction();
#endif

                /* Check if sequence is complete */
                seqResult = Cdd_I2c_GetSequenceResult(seqId);
                if (!((seqResult == CDD_I2C_SEQ_PENDING) || (seqResult == CDD_I2C_SEQ_QUEUED)))
                {
                    break;
                }
            }

            if (seqResult != CDD_I2C_SEQ_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (gI2cAppSeqDone != TRUE)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }
            if (gI2cAppSeqErrCode != CDD_I2C_E_NO_ERROR)
            {
                I2c_appSequenceErrorReport(gI2cAppSeqErrCode);
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(rdChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

Std_ReturnType I2c_writeRead(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                             uint8 *pRdBuf, uint16 wrSize, uint16 rdSize)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        wrChId, rdChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId  = I2C_APP_SEQ_ID_HW_UNIT_0_WR_RD;
    wrChId = I2C_APP_CH_ID_HW_UNIT_0_WR_RD_WR;
    rdChId = I2C_APP_CH_ID_HW_UNIT_0_WR_RD_RD;
    if (hwUnitId == CDD_I2C_HW_UNIT_2)
    {
        /* Assumes HW UNIT 1 is not present. Otherwise need to do += (2 * x) */
        seqId  += I2C_APP_NUM_SEQ_PER_HW_UNIT;
        wrChId += I2C_APP_NUM_CH_PER_HW_UNIT;
        rdChId += I2C_APP_NUM_CH_PER_HW_UNIT;
    }

    /* Dynamically setup the slave address */
    retVal += Cdd_I2c_SetupEBDynamic(wrChId, deviceAddress, pWrBuf, NULL_PTR, wrSize);
    retVal  = Cdd_I2c_SetupEBDynamic(rdChId, deviceAddress, NULL_PTR, pRdBuf, rdSize);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, APP_NAME ": I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        gI2cAppSeqDone    = FALSE;
        gI2cAppSeqErrCode = CDD_I2C_E_NO_ERROR;
        retVal            = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
        }
        else
        {
            /* Wait for completion */
            while (1U)
            {
#if (STD_ON == CDD_I2C_POLLING_MODE)
                /* Needed only for polled mode transfers */
                Cdd_I2c_MainFunction();
#endif

                /* Check if sequence is complete */
                seqResult = Cdd_I2c_GetSequenceResult(seqId);
                if (!((seqResult == CDD_I2C_SEQ_PENDING) || (seqResult == CDD_I2C_SEQ_QUEUED)))
                {
                    break;
                }
            }

            if (seqResult != CDD_I2C_SEQ_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (gI2cAppSeqDone != TRUE)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }
            if (gI2cAppSeqErrCode != CDD_I2C_E_NO_ERROR)
            {
                I2c_appSequenceErrorReport(gI2cAppSeqErrCode);
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(wrChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Write Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
            chResult = Cdd_I2c_GetResult(rdChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Read Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

Std_ReturnType I2c_writeReadRestart(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                                    uint8 *pRdBuf, uint16 wrSize, uint16 rdSize)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        wrChId, rdChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId  = I2C_APP_SEQ_ID_HW_UNIT_0_WR_RD_RESTART;
    wrChId = I2C_APP_CH_ID_HW_UNIT_0_WR_RD_WR_RESTART;
    rdChId = I2C_APP_CH_ID_HW_UNIT_0_WR_RD_RD_RESTART;
    if (hwUnitId == CDD_I2C_HW_UNIT_2)
    {
        /* Assumes HW UNIT 1 is not present. Otherwise need to do += (2 * x) */
        seqId  += I2C_APP_NUM_SEQ_PER_HW_UNIT;
        wrChId += I2C_APP_NUM_CH_PER_HW_UNIT;
        rdChId += I2C_APP_NUM_CH_PER_HW_UNIT;
    }

    /* Dynamically setup the slave address */
    retVal += Cdd_I2c_SetupEBDynamic(wrChId, deviceAddress, pWrBuf, NULL_PTR, wrSize);
    retVal  = Cdd_I2c_SetupEBDynamic(rdChId, deviceAddress, NULL_PTR, pRdBuf, rdSize);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, APP_NAME ": I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        gI2cAppSeqDone    = FALSE;
        gI2cAppSeqErrCode = CDD_I2C_E_NO_ERROR;
        retVal            = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
        }
        else
        {
            /* Wait for completion */
            while (1U)
            {
#if (STD_ON == CDD_I2C_POLLING_MODE)
                /* Needed only for polled mode transfers */
                Cdd_I2c_MainFunction();
#endif

                /* Check if sequence is complete */
                seqResult = Cdd_I2c_GetSequenceResult(seqId);
                if (!((seqResult == CDD_I2C_SEQ_PENDING) || (seqResult == CDD_I2C_SEQ_QUEUED)))
                {
                    break;
                }
            }

            if (seqResult != CDD_I2C_SEQ_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (gI2cAppSeqDone != TRUE)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }
            if (gI2cAppSeqErrCode != CDD_I2C_E_NO_ERROR)
            {
                I2c_appSequenceErrorReport(gI2cAppSeqErrCode);
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(wrChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Write Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
            chResult = Cdd_I2c_GetResult(rdChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Read Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

void I2c_appSeqComplete(void)
{
    gI2cAppSeqDone = TRUE;
}

void I2c_appSeqFail(uint8 errorCode)
{
    gI2cAppSeqErrCode = errorCode;
}

static void I2c_appInit(void)
{
    Std_VersionInfoType versioninfo;

    I2c_appPlatformInit();
#if (STD_OFF == CDD_I2C_POLLING_MODE)
    I2c_appInterruptConfig();
#endif

    AppUtils_printf(APP_NAME ": STARTS !!!\r\n");

    Cdd_I2c_Init(NULL_PTR);

    /*Get I2c Version information*/
    Cdd_I2c_GetVersionInfo(&versioninfo);
    GT_0trace(I2C_APP_TRACE_MASK, GT_INFO, " \r\n");
    GT_0trace(I2C_APP_TRACE_MASK, GT_INFO, " I2C MCAL Version Info\r\n");
    GT_0trace(I2C_APP_TRACE_MASK, GT_INFO, " ---------------------\r\n");
    GT_1trace(I2C_APP_TRACE_MASK, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(I2C_APP_TRACE_MASK, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(I2C_APP_TRACE_MASK, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(I2C_APP_TRACE_MASK, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(I2C_APP_TRACE_MASK, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(I2C_APP_TRACE_MASK, GT_INFO, " \r\n");

    return;
}

static void I2c_appDeInit(void)
{
    GT_1trace(I2C_APP_TRACE_MASK, GT_INFO, APP_NAME ": Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, APP_NAME ": Stack/section corruption!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        AppUtils_printf(APP_NAME ": DONE (Passed) !!\r\n");
        AppUtils_printf(APP_NAME ": All tests have passed\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
    }
    else
    {
        AppUtils_printf(APP_NAME ": DONE (Failed) !!\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_FAIL);
    }

    Cdd_I2c_DeInit();
    I2c_appPlatformDeInit();

    return;
}

#if (STD_OFF == CDD_I2C_POLLING_MODE)
static void I2c_appInterruptConfig(void)
{
    Vim_IntCfg intCfg;

    vimInit();
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

#if defined(CDD_I2C_HW_UNIT_0_ACTIVE)
    /* I2C0 interrupt */
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
    intCfg.intNum = I2C0_INT;
#endif
#if defined(AM261X_PLATFORM)
    intCfg.intNum = I2C0_IRQ;
#endif
    intCfg.handler  = &Cdd_I2c_HwUnit0_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
#endif

#if defined(CDD_I2C_HW_UNIT_2_ACTIVE)
    /* I2C2 interrupt */
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
    intCfg.intNum = I2C2_INT;
#endif
#if defined(AM261X_PLATFORM)
    intCfg.intNum = I2C2_IRQ;
#endif
    intCfg.handler  = &Cdd_I2c_HwUnit2_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
#endif

    return;
}
#endif

static void I2c_appSequenceErrorReport(uint8 errorCode)
{
    if (CDD_I2C_E_ARBITRATION_FAILURE == errorCode)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Arbitration lost!!\n\r");
    }
    else if (CDD_I2C_E_NACK_RECEIVED == errorCode)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " No Acknowledgement!!\n\r");
    }
    else if (CDD_I2C_E_BUS_FAILURE == errorCode)
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Bus failure!!\n\r");
    }
    else
    {
        GT_0trace(I2C_APP_TRACE_MASK, GT_ERR, " Unknown error!!\n\r");
    }

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

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0(void)
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
