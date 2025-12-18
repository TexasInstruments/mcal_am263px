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
 *  \file     app_utilsI2c.c
 *
 *  \brief    This file contains the I2C utiliy APIs to make it easy for any app
 *            to use I2C read/write operation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "app_utilsI2c.h"
#include "SchM_Cdd_I2c.h"
#include "app_utils.h"
#include "trace.h"
#include "sys_vim.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Trace mask */
#define I2C_UTILS_TRACE_MASK (GT_INFO1 | GT_TraceState_Enable)

/* I2C ISR numbers */
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
#define I2C_UTILS_HW_UNIT_0_INT (I2C0_INT)
#define I2C_UTILS_HW_UNIT_1_INT (I2C1_INT)
#define I2C_UTILS_HW_UNIT_2_INT (I2C2_INT)
#define I2C_UTILS_HW_UNIT_3_INT (I2C3_INT)
#endif
#if defined(AM261X_PLATFORM)
#define I2C_UTILS_HW_UNIT_0_INT (I2C0_IRQ)
#define I2C_UTILS_HW_UNIT_1_INT (I2C1_IRQ)
#define I2C_UTILS_HW_UNIT_2_INT (I2C2_IRQ)
#endif

/*
 * Sequence and channel IDs
 * Each HW unit has four sequences and 6 channels
 *      Seq 0: 1 WR only channel
 *      Seq 1: 1 RD only channel
 *      Seq 2: 1 WR channel and 1 RD channel with STOP in between
 *      Seq 4: 1 WR channel and 1 RD channel with NOSTOP in between (RESTART mode)
 */
#define I2C_UTILS_NUM_SEQ_PER_HW_UNIT (4U)
#define I2C_UTILS_NUM_CH_PER_HW_UNIT  (6U)
/* Sequence IDs */
#define I2C_UTILS_SEQ_ID_HW_UNIT_0_WR            (CddI2cConf_CddI2cSequence_CddI2cSequence_0)
#define I2C_UTILS_SEQ_ID_HW_UNIT_0_RD            (CddI2cConf_CddI2cSequence_CddI2cSequence_1)
#define I2C_UTILS_SEQ_ID_HW_UNIT_0_WR_RD         (CddI2cConf_CddI2cSequence_CddI2cSequence_2)
#define I2C_UTILS_SEQ_ID_HW_UNIT_0_WR_RD_RESTART (CddI2cConf_CddI2cSequence_CddI2cSequence_3)
#define I2C_UTILS_SEQ_ID_HW_UNIT_1_WR            (CddI2cConf_CddI2cSequence_CddI2cSequence_4)
#define I2C_UTILS_SEQ_ID_HW_UNIT_1_RD            (CddI2cConf_CddI2cSequence_CddI2cSequence_5)
#define I2C_UTILS_SEQ_ID_HW_UNIT_1_WR_RD         (CddI2cConf_CddI2cSequence_CddI2cSequence_6)
#define I2C_UTILS_SEQ_ID_HW_UNIT_1_WR_RD_RESTART (CddI2cConf_CddI2cSequence_CddI2cSequence_7)
#define I2C_UTILS_SEQ_ID_HW_UNIT_2_WR            (CddI2cConf_CddI2cSequence_CddI2cSequence_8)
#define I2C_UTILS_SEQ_ID_HW_UNIT_2_RD            (CddI2cConf_CddI2cSequence_CddI2cSequence_9)
#define I2C_UTILS_SEQ_ID_HW_UNIT_2_WR_RD         (CddI2cConf_CddI2cSequence_CddI2cSequence_10)
#define I2C_UTILS_SEQ_ID_HW_UNIT_2_WR_RD_RESTART (CddI2cConf_CddI2cSequence_CddI2cSequence_11)
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
#define I2C_UTILS_SEQ_ID_HW_UNIT_3_WR            (CddI2cConf_CddI2cSequence_CddI2cSequence_12)
#define I2C_UTILS_SEQ_ID_HW_UNIT_3_RD            (CddI2cConf_CddI2cSequence_CddI2cSequence_13)
#define I2C_UTILS_SEQ_ID_HW_UNIT_3_WR_RD         (CddI2cConf_CddI2cSequence_CddI2cSequence_14)
#define I2C_UTILS_SEQ_ID_HW_UNIT_3_WR_RD_RESTART (CddI2cConf_CddI2cSequence_CddI2cSequence_15)
#endif
/* Channel IDs */
#define I2C_UTILS_CH_ID_HW_UNIT_0_WR               (CddI2cConf_CddI2cChannel_CddI2cChannel_0)
#define I2C_UTILS_CH_ID_HW_UNIT_0_RD               (CddI2cConf_CddI2cChannel_CddI2cChannel_1)
#define I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_WR         (CddI2cConf_CddI2cChannel_CddI2cChannel_2)
#define I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_RD         (CddI2cConf_CddI2cChannel_CddI2cChannel_3)
#define I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_WR_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_4)
#define I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_RD_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_5)
#define I2C_UTILS_CH_ID_HW_UNIT_1_WR               (CddI2cConf_CddI2cChannel_CddI2cChannel_6)
#define I2C_UTILS_CH_ID_HW_UNIT_1_RD               (CddI2cConf_CddI2cChannel_CddI2cChannel_7)
#define I2C_UTILS_CH_ID_HW_UNIT_1_WR_RD_WR         (CddI2cConf_CddI2cChannel_CddI2cChannel_8)
#define I2C_UTILS_CH_ID_HW_UNIT_1_WR_RD_RD         (CddI2cConf_CddI2cChannel_CddI2cChannel_9)
#define I2C_UTILS_CH_ID_HW_UNIT_1_WR_RD_WR_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_10)
#define I2C_UTILS_CH_ID_HW_UNIT_1_WR_RD_RD_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_11)
#define I2C_UTILS_CH_ID_HW_UNIT_2_WR               (CddI2cConf_CddI2cChannel_CddI2cChannel_12)
#define I2C_UTILS_CH_ID_HW_UNIT_2_RD               (CddI2cConf_CddI2cChannel_CddI2cChannel_13)
#define I2C_UTILS_CH_ID_HW_UNIT_2_WR_RD_WR         (CddI2cConf_CddI2cChannel_CddI2cChannel_14)
#define I2C_UTILS_CH_ID_HW_UNIT_2_WR_RD_RD         (CddI2cConf_CddI2cChannel_CddI2cChannel_15)
#define I2C_UTILS_CH_ID_HW_UNIT_2_WR_RD_WR_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_16)
#define I2C_UTILS_CH_ID_HW_UNIT_2_WR_RD_RD_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_17)
#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
#define I2C_UTILS_CH_ID_HW_UNIT_3_WR               (CddI2cConf_CddI2cChannel_CddI2cChannel_18)
#define I2C_UTILS_CH_ID_HW_UNIT_3_RD               (CddI2cConf_CddI2cChannel_CddI2cChannel_19)
#define I2C_UTILS_CH_ID_HW_UNIT_3_WR_RD_WR         (CddI2cConf_CddI2cChannel_CddI2cChannel_20)
#define I2C_UTILS_CH_ID_HW_UNIT_3_WR_RD_RD         (CddI2cConf_CddI2cChannel_CddI2cChannel_21)
#define I2C_UTILS_CH_ID_HW_UNIT_3_WR_RD_WR_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_22)
#define I2C_UTILS_CH_ID_HW_UNIT_3_WR_RD_RD_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_23)
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void           I2c_utilsResetSeqFlag(void);
static Std_ReturnType I2c_utilsCheckSeqFlag(Cdd_I2c_SequenceType seqId, uint8 expectedErrorCode);
static void           I2c_utilsSequenceErrorReport(uint8 errorCode);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile boolean gI2cUtilsSeqDone[CDD_I2C_MAX_SEQ];
static volatile uint8   gI2cUtilsSeqErrCode[CDD_I2C_MAX_SEQ];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Std_ReturnType I2c_utilsWrite(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                              uint16 size)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        wrChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId   = I2C_UTILS_SEQ_ID_HW_UNIT_0_WR;
    wrChId  = I2C_UTILS_CH_ID_HW_UNIT_0_WR;
    seqId  += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_SEQ_PER_HW_UNIT;
    wrChId += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_CH_PER_HW_UNIT;

    /* Dynamically setup the slave address */
    retVal = Cdd_I2c_SetupEBDynamic(wrChId, deviceAddress, pWrBuf, NULL_PTR, size);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        I2c_utilsResetSeqFlag();
        retVal = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
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
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (I2c_utilsCheckSeqFlag(seqId, CDD_I2C_E_NO_ERROR) != E_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(wrChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

Std_ReturnType I2c_utilsRead(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pRdBuf, uint16 size)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        rdChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId   = I2C_UTILS_SEQ_ID_HW_UNIT_0_RD;
    rdChId  = I2C_UTILS_CH_ID_HW_UNIT_0_RD;
    seqId  += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_SEQ_PER_HW_UNIT;
    rdChId += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_CH_PER_HW_UNIT;

    /* Dynamically setup the slave address */
    retVal = Cdd_I2c_SetupEBDynamic(rdChId, deviceAddress, NULL_PTR, pRdBuf, size);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        I2c_utilsResetSeqFlag();
        retVal = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
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
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (I2c_utilsCheckSeqFlag(seqId, CDD_I2C_E_NO_ERROR) != E_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(rdChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

Std_ReturnType I2c_utilsWriteRead(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                                  uint8 *pRdBuf, uint16 wrSize, uint16 rdSize)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        wrChId, rdChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId   = I2C_UTILS_SEQ_ID_HW_UNIT_0_WR_RD;
    wrChId  = I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_WR;
    rdChId  = I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_RD;
    seqId  += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_SEQ_PER_HW_UNIT;
    wrChId += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_CH_PER_HW_UNIT;
    rdChId += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_CH_PER_HW_UNIT;

    /* Dynamically setup the slave address */
    retVal += Cdd_I2c_SetupEBDynamic(wrChId, deviceAddress, pWrBuf, NULL_PTR, wrSize);
    retVal  = Cdd_I2c_SetupEBDynamic(rdChId, deviceAddress, NULL_PTR, pRdBuf, rdSize);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        I2c_utilsResetSeqFlag();
        retVal = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
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
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (I2c_utilsCheckSeqFlag(seqId, CDD_I2C_E_NO_ERROR) != E_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(wrChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Write Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
            chResult = Cdd_I2c_GetResult(rdChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Read Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

Std_ReturnType I2c_utilsWriteReadRestart(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                                         uint8 *pRdBuf, uint16 wrSize, uint16 rdSize)
{
    Std_ReturnType             retVal = E_OK;
    Cdd_I2c_SequenceType       seqId;
    Cdd_I2c_ChannelType        wrChId, rdChId;
    Cdd_I2c_ChannelResultType  chResult;
    Cdd_I2c_SequenceResultType seqResult;

    seqId   = I2C_UTILS_SEQ_ID_HW_UNIT_0_WR_RD_RESTART;
    wrChId  = I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_WR_RESTART;
    rdChId  = I2C_UTILS_CH_ID_HW_UNIT_0_WR_RD_RD_RESTART;
    seqId  += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_SEQ_PER_HW_UNIT;
    wrChId += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_CH_PER_HW_UNIT;
    rdChId += (hwUnitId - CDD_I2C_HW_UNIT_0) * I2C_UTILS_NUM_CH_PER_HW_UNIT;

    /* Dynamically setup the slave address */
    retVal += Cdd_I2c_SetupEBDynamic(wrChId, deviceAddress, pWrBuf, NULL_PTR, wrSize);
    retVal  = Cdd_I2c_SetupEBDynamic(rdChId, deviceAddress, NULL_PTR, pRdBuf, rdSize);
    if (retVal != E_OK)
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " I2C Setup EB failed!!!\n\r");
    }

    if (retVal == E_OK)
    {
        I2c_utilsResetSeqFlag();
        retVal = Cdd_I2c_AsyncTransmit(seqId);
        if (retVal != E_OK)
        {
            GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Cdd_I2c_AsyncTransmit failed!!\n\r");
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
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence error!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if sequence notify is received */
            if (I2c_utilsCheckSeqFlag(seqId, CDD_I2C_E_NO_ERROR) != E_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Sequence notify not received!!\n\r");
                retVal = E_NOT_OK;
            }

            /* Check if all channel status is in complete state */
            chResult = Cdd_I2c_GetResult(wrChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Write Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
            chResult = Cdd_I2c_GetResult(rdChId);
            if (chResult != CDD_I2C_CH_RESULT_OK)
            {
                GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Read Channel error!!\n\r");
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

void I2c_utilsInterruptConfig(void)
{
#if (STD_OFF == CDD_I2C_POLLING_MODE)
    Vim_IntCfg intCfg;

    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_PULSE;

#if defined(CDD_I2C_HW_UNIT_0_ACTIVE)
    /* I2C0 interrupt */
    intCfg.intNum   = I2C_UTILS_HW_UNIT_0_INT;
    intCfg.handler  = &Cdd_I2c_HwUnit0_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
#endif

#if defined(CDD_I2C_HW_UNIT_1_ACTIVE)
    /* I2C1 interrupt */
    intCfg.intNum   = I2C_UTILS_HW_UNIT_1_INT;
    intCfg.handler  = &Cdd_I2c_HwUnit1_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
#endif

#if defined(CDD_I2C_HW_UNIT_2_ACTIVE)
    /* I2C2 interrupt */
    intCfg.intNum   = I2C_UTILS_HW_UNIT_2_INT;
    intCfg.handler  = &Cdd_I2c_HwUnit2_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
#endif

#if defined(CDD_I2C_HW_UNIT_3_ACTIVE)
    /* I2C3 interrupt */
    intCfg.intNum   = I2C_UTILS_HW_UNIT_3_INT;
    intCfg.handler  = &Cdd_I2c_HwUnit3_ISR;
    intCfg.priority = VIM_PRIORITY_2;
    vimRegisterInterrupt(&intCfg);
#endif
#endif

    return;
}

static void I2c_utilsResetSeqFlag(void)
{
    for (uint32 seqIdx = 0U; seqIdx < CDD_I2C_MAX_SEQ; seqIdx++)
    {
        gI2cUtilsSeqDone[seqIdx]    = FALSE;
        gI2cUtilsSeqErrCode[seqIdx] = CDD_I2C_E_NO_ERROR;
    }

    return;
}

static Std_ReturnType I2c_utilsCheckSeqFlag(Cdd_I2c_SequenceType seqId, uint8 expectedErrorCode)
{
    Std_ReturnType retVal = E_OK;

    for (uint32 seqIdx = 0U; seqIdx < CDD_I2C_MAX_SEQ; seqIdx++)
    {
        if (seqIdx == seqId)
        {
            if (expectedErrorCode == CDD_I2C_E_NO_ERROR)
            {
                if (gI2cUtilsSeqDone[seqIdx] != TRUE)
                {
                    retVal = E_NOT_OK;
                }
            }
            else
            {
                if (gI2cUtilsSeqDone[seqIdx] == TRUE)
                {
                    retVal = E_NOT_OK;
                }
            }
            if (gI2cUtilsSeqErrCode[seqIdx] != expectedErrorCode)
            {
                I2c_utilsSequenceErrorReport(gI2cUtilsSeqErrCode[seqIdx]);
                retVal = E_NOT_OK;
            }
        }
        else
        {
            if (gI2cUtilsSeqDone[seqIdx] == TRUE)
            {
                retVal = E_NOT_OK;
            }
            if (gI2cUtilsSeqErrCode[seqIdx] != CDD_I2C_E_NO_ERROR)
            {
                I2c_utilsSequenceErrorReport(gI2cUtilsSeqErrCode[seqIdx]);
                retVal = E_NOT_OK;
            }
        }
    }

    return retVal;
}

static void I2c_utilsSequenceErrorReport(uint8 errorCode)
{
    if (CDD_I2C_E_ARBITRATION_FAILURE == errorCode)
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Arbitration lost!!\n\r");
    }
    else if (CDD_I2C_E_NACK_RECEIVED == errorCode)
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " No Acknowledgement!!\n\r");
    }
    else if (CDD_I2C_E_BUS_FAILURE == errorCode)
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Bus failure!!\n\r");
    }
    else
    {
        GT_0trace(I2C_UTILS_TRACE_MASK, GT_ERR, " Unknown error!!\n\r");
    }

    return;
}

__attribute__((weak)) void SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

__attribute__((weak)) void SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void I2c_utilsSeq0Complete(void)
{
    gI2cUtilsSeqDone[0U] = TRUE;
}

void I2c_utilsSeq0Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[0U] = errorCode;
}

void I2c_utilsSeq1Complete(void)
{
    gI2cUtilsSeqDone[1U] = TRUE;
}

void I2c_utilsSeq1Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[1U] = errorCode;
}

void I2c_utilsSeq2Complete(void)
{
    gI2cUtilsSeqDone[2U] = TRUE;
}

void I2c_utilsSeq2Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[2U] = errorCode;
}

void I2c_utilsSeq3Complete(void)
{
    gI2cUtilsSeqDone[3U] = TRUE;
}

void I2c_utilsSeq3Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[3U] = errorCode;
}

void I2c_utilsSeq4Complete(void)
{
    gI2cUtilsSeqDone[4U] = TRUE;
}

void I2c_utilsSeq4Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[4U] = errorCode;
}

void I2c_utilsSeq5Complete(void)
{
    gI2cUtilsSeqDone[5U] = TRUE;
}

void I2c_utilsSeq5Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[5U] = errorCode;
}

void I2c_utilsSeq6Complete(void)
{
    gI2cUtilsSeqDone[6U] = TRUE;
}

void I2c_utilsSeq6Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[6U] = errorCode;
}

void I2c_utilsSeq7Complete(void)
{
    gI2cUtilsSeqDone[7U] = TRUE;
}

void I2c_utilsSeq7Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[7U] = errorCode;
}

void I2c_utilsSeq8Complete(void)
{
    gI2cUtilsSeqDone[8U] = TRUE;
}

void I2c_utilsSeq8Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[8U] = errorCode;
}

void I2c_utilsSeq9Complete(void)
{
    gI2cUtilsSeqDone[9U] = TRUE;
}

void I2c_utilsSeq9Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[9U] = errorCode;
}

void I2c_utilsSeq10Complete(void)
{
    gI2cUtilsSeqDone[10U] = TRUE;
}

void I2c_utilsSeq10Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[10U] = errorCode;
}

void I2c_utilsSeq11Complete(void)
{
    gI2cUtilsSeqDone[11U] = TRUE;
}

void I2c_utilsSeq11Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[11U] = errorCode;
}

/* These platforms have 4 I2C instances */
#if defined(AM263PX_PLATFORM) || defined(AM263X_PLATFORM)
void I2c_utilsSeq12Complete(void)
{
    gI2cUtilsSeqDone[12U] = TRUE;
}

void I2c_utilsSeq12Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[12U] = errorCode;
}

void I2c_utilsSeq13Complete(void)
{
    gI2cUtilsSeqDone[13U] = TRUE;
}

void I2c_utilsSeq13Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[13U] = errorCode;
}

void I2c_utilsSeq14Complete(void)
{
    gI2cUtilsSeqDone[14U] = TRUE;
}

void I2c_utilsSeq14Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[14U] = errorCode;
}

void I2c_utilsSeq15Complete(void)
{
    gI2cUtilsSeqDone[15U] = TRUE;
}

void I2c_utilsSeq15Fail(uint8 errorCode)
{
    gI2cUtilsSeqErrCode[15U] = errorCode;
}
#endif
