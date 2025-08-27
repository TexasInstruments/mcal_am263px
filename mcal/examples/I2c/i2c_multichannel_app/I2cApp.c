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

/* Test loop count */
#define I2C_APP_LOOP_CNT (100U)

/* Temperature result register offset */
#define I2C_APP_TMP_REG_RESULT (0x00U)

/* Sequence and channel IDs */
#define I2C_APP_TMP_SEQ_ID   (CddI2cConf_CddI2cSequence_CddI2cSequence_0)
#define I2C_APP_TMP_WR_CH_ID (CddI2cConf_CddI2cChannel_CddI2cChannel_0)
#define I2C_APP_TMP_RD_CH_ID (CddI2cConf_CddI2cChannel_CddI2cChannel_1)

/* Buffer size */
#define I2C_APP_TMP_WR_BUF_SIZE (1U)
#define I2C_APP_TMP_RD_BUF_SIZE (2U)

/* Trace mask */
#define I2C_APP_TRACE_MASK (GT_INFO1 | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static Std_ReturnType I2c_appSetupBuffer(void);
static Std_ReturnType I2c_appDataWriteReadToSlaves(void);
static void           I2c_appSequenceErrorReport(uint8 errorCode);

static void I2c_appTest(void);
static void I2c_appInit(void);
static void I2c_appDeInit(void);

#if (STD_OFF == CDD_I2C_POLLING_MODE)
static void I2c_appInterruptConfig(void);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile boolean gI2cAppSeqDone    = FALSE;
static volatile uint8   gI2cAppSeqErrCode = CDD_I2C_E_NO_ERROR;

/*Buffer to store transmission data for temperature sensor*/
static uint8 gI2cAppTxBufTmp[I2C_APP_TMP_WR_BUF_SIZE];
/*Buffer to store reception data for temperature sensor*/
static uint8 gI2cAppRxBufTmp[I2C_APP_TMP_RD_BUF_SIZE];

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
    Std_ReturnType retVal;

    /* Set up channels */
    retVal = I2c_appSetupBuffer();
    if (retVal != E_OK)
    {
        gTestPassed = E_NOT_OK;
    }

    if (retVal == E_OK)
    {
        uint32 loopcnt = 0U;
        while (loopcnt < I2C_APP_LOOP_CNT)
        {
            /* Write data to Temperature sensor */
            gTestPassed = I2c_appDataWriteReadToSlaves();
            if (E_OK != gTestPassed)
            {
                GT_0trace(McalAppTrace, GT_ERR, " I2C Transfer to Slave Failed!!\n\r");
            }
            loopcnt++;
        }
    }

    return;
}

static Std_ReturnType I2c_appSetupBuffer(void)
{
    Std_ReturnType retVal = E_OK;

    /* Setup I2c channels */
    retVal  = Cdd_I2c_SetupEB(I2C_APP_TMP_WR_CH_ID, &gI2cAppTxBufTmp[0U], NULL_PTR, I2C_APP_TMP_WR_BUF_SIZE);
    retVal |= Cdd_I2c_SetupEB(I2C_APP_TMP_RD_CH_ID, NULL_PTR, &gI2cAppRxBufTmp[0U], I2C_APP_TMP_RD_BUF_SIZE);

    return retVal;
}

static Std_ReturnType I2c_appDataWriteReadToSlaves(void)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    /* Start transmission */
    gI2cAppSeqDone      = FALSE;
    gI2cAppSeqErrCode   = CDD_I2C_E_NO_ERROR;
    gI2cAppTxBufTmp[0U] = I2C_APP_TMP_REG_RESULT;
    retVal              = Cdd_I2c_AsyncTransmit(I2C_APP_TMP_SEQ_ID);
    if (retVal != E_OK)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
    }
    else
    {
        /* Wait for completion */
        while (1U)
        {
            Cdd_I2c_MainFunction();

            /* Check if sequence is complete */
            seqResult = Cdd_I2c_GetSequenceResult(I2C_APP_TMP_SEQ_ID);
            if (!((seqResult == CDD_I2C_SEQ_PENDING) || (seqResult == CDD_I2C_SEQ_QUEUED)))
            {
                break;
            }
        }
    }

    /* Check if sequence notify is received */
    if (gI2cAppSeqDone != TRUE)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Sequence notify not received!!\n\r");
        retVal = E_NOT_OK;
    }
    if (gI2cAppSeqErrCode != CDD_I2C_E_NO_ERROR)
    {
        I2c_appSequenceErrorReport(gI2cAppSeqErrCode);
        retVal = E_NOT_OK;
    }

    /* Check if all channel status is in complete state */
    chResult = Cdd_I2c_GetResult(I2C_APP_TMP_WR_CH_ID);
    if (chResult != CDD_I2C_CH_RESULT_OK)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Channel0 error!!\n\r");
        retVal = E_NOT_OK;
    }
    chResult = Cdd_I2c_GetResult(I2C_APP_TMP_RD_CH_ID);
    if (chResult != CDD_I2C_CH_RESULT_OK)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Channel1 error!!\n\r");
        retVal = E_NOT_OK;
    }

    if (retVal == E_OK)
    {
        sint16 temperature = (sint16)0;

        /* Create 16 bit temperature */
        temperature = ((uint16)gI2cAppRxBufTmp[0U] << 8U) | (gI2cAppRxBufTmp[1U]);

        /*
         * 4 LSBs of temperature are 0 according to datasheet
         * since temperature is stored in 12 bits. Therefore,
         * right shift by 4 places
         */
        temperature = temperature >> 4U;
        /*
         * If the 12th bit of temperature is set '1' (equivalent to 8th bit of the first byte read),
         * then we have a 2's complement negative value which needs to be sign extended
         */
        if (gI2cAppRxBufTmp[0U] & 0x80U)
        {
            temperature |= 0xF000U;
        }

        AppUtils_printf(APP_NAME ": Temperature sensor reading : %f (Celsius)\n\r", (temperature / 16.0f));
    }

    return retVal;
}

void I2c_appTemperatureDataWriteReadComplete(void)
{
    gI2cAppSeqDone = TRUE;
}

void I2c_appTemperatureDataWriteReadFail(uint8 errorCode)
{
    gI2cAppSeqErrCode = errorCode;
}

static void I2c_appSequenceErrorReport(uint8 errorCode)
{
    if (CDD_I2C_E_HW_UNIT_BUSY == errorCode)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Hardware unit busy!!\n\r");
    }
    else if (CDD_I2C_E_CHANNEL_BUSY == errorCode)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Channels busy!!\n\r");
    }
    else if (CDD_I2C_E_ARBITRATION_LOSS == errorCode)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Arbitration lost!!\n\r");
    }
    else if (CDD_I2C_E_NACK == errorCode)
    {
        GT_0trace(McalAppTrace, GT_ERR, " No Acknowledgement!!\n\r");
    }
    else if (CDD_I2C_E_RECEIVE_SHIFT_REGISTER_FULL == errorCode)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Receive shift register full!!\n\r");
    }
    else if (CDD_I2C_E_PARAM_QUEUE_FULL == errorCode)
    {
        GT_0trace(McalAppTrace, GT_ERR, " Queue full!!\n\r");
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, " Unknown error!!\n\r");
    }

    return;
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
