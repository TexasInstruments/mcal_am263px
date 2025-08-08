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
 *  \file     Cdd_I2c_Hw.c
 *
 *  \brief    This file contains the private implementation of I2C HW functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_I2c_Hw.h"
#include "hw_types.h"
#include "Cdd_I2c_hw_reg.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Interrupt enable masks */
#define CDD_I2C_HW_INTR_ENABLE_MASK_ALL                                                                       \
    ((uint16)CDD_I2C_ICIMR_AL_MASK | (uint16)CDD_I2C_ICIMR_NACK_MASK | (uint16)CDD_I2C_ICIMR_ARDY_MASK |      \
     (uint16)CDD_I2C_ICIMR_ICRRDY_MASK | (uint16)CDD_I2C_ICIMR_ICXRDY_MASK | (uint16)CDD_I2C_ICIMR_SCD_MASK | \
     (uint16)CDD_I2C_ICIMR_AAS_MASK)
#define CDD_I2C_HW_INTR_ENABLE_MASK_TX                                                                   \
    ((uint16)CDD_I2C_ICIMR_AL_MASK | (uint16)CDD_I2C_ICIMR_NACK_MASK | (uint16)CDD_I2C_ICIMR_ARDY_MASK | \
     (uint16)CDD_I2C_ICIMR_ICXRDY_MASK | (uint16)CDD_I2C_ICIMR_SCD_MASK)
#define CDD_I2C_HW_INTR_ENABLE_MASK_RX                                                                     \
    ((uint16)CDD_I2C_ICIMR_AL_MASK | (uint16)CDD_I2C_ICIMR_NACK_MASK | (uint16)CDD_I2C_ICIMR_ICRRDY_MASK | \
     (uint16)CDD_I2C_ICIMR_SCD_MASK)
/* Interrupt status masks */
#define CDD_I2C_HW_INTR_STATUS_MASK_ALL                                                                       \
    ((uint16)CDD_I2C_ICSTR_AL_MASK | (uint16)CDD_I2C_ICSTR_NACK_MASK | (uint16)CDD_I2C_ICSTR_ARDY_MASK |      \
     (uint16)CDD_I2C_ICSTR_ICRRDY_MASK | (uint16)CDD_I2C_ICSTR_ICXRDY_MASK | (uint16)CDD_I2C_ICSTR_SCD_MASK | \
     (uint16)CDD_I2C_ICSTR_AD0_MASK | (uint16)CDD_I2C_ICSTR_AAS_MASK | (uint16)CDD_I2C_ICSTR_XSMT_MASK |      \
     (uint16)CDD_I2C_ICSTR_RSFULL_MASK | (uint16)CDD_I2C_ICSTR_BB_MASK | (uint16)CDD_I2C_ICSTR_NACKSNT_MASK | \
     (uint16)CDD_I2C_ICSTR_SDIR_MASK)
#define CDD_I2C_HW_INTR_STATUS_MASK_ERR \
    ((uint16)CDD_I2C_ICSTR_AL_MASK | (uint16)CDD_I2C_ICSTR_NACK_MASK | (uint16)CDD_I2C_ICSTR_AD0_MASK)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Cdd_I2c_hwSetupClk(uint32 baseAddr, uint32 baudRate, uint32 hwUnitFrequency, uint32 sysClk);

static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitOnBusBusy(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForBusBusy(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForTxReady(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForRxReady(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForAccessReady(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForStop(uint32 baseAddr);

static void Cdd_I2c_hwSetMode(uint32 baseAddr, uint16 ctrlMask, uint16 ctrlCmds);
static void Cdd_I2c_hwReset(uint32 baseAddr);
static void Cdd_I2c_hwEnableModule(uint32 baseAddr);
static void Cdd_I2c_hwStart(uint32 baseAddr);
static void Cdd_I2c_hwStop(uint32 baseAddr);

static void   Cdd_I2c_hwEnableIntr(uint32 baseAddr, uint16 mask);
static void   Cdd_I2c_hwDisableIntr(uint32 baseAddr, uint16 mask);
static void   Cdd_I2c_hwClearIntr(uint32 baseAddr, uint16 mask);
static uint16 Cdd_I2c_hwGetIntrStatus(uint32 baseAddr);

static void  Cdd_I2c_hwSetOwnAddress(uint32 baseAddr, uint16 ownAddress);
static void  Cdd_I2c_hwSetSlaveAddress(uint32 baseAddr, Cdd_I2c_AddressType deviceAddress);
static void  Cdd_I2c_hwSetDataCount(uint32 baseAddr, uint16 length);
static void  Cdd_I2c_hwWriteData(uint32 baseAddr, uint8 data);
static uint8 Cdd_I2c_hwReadData(uint32 baseAddr);

/* ========================================================================== */
/*                        Local Object Definitions                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"

void Cdd_I2c_hwInit(uint32 baseAddr, uint32 baudRate, uint32 hwUnitFrequency, uint32 sysClk,
                    Cdd_I2c_AddressType ownAddress)
{
    Cdd_I2c_hwReset(baseAddr);

    /* Initialises I2C hardware unit for required baudrate */
    Cdd_I2c_hwSetupClk(baseAddr, baudRate, hwUnitFrequency, sysClk);

    /* Disable/clear all interrupts and enable the module */
    Cdd_I2c_hwDisableAllIntr(baseAddr);
    Cdd_I2c_hwClearAllStatus(baseAddr);
    Cdd_I2c_hwEnableModule(baseAddr);
    Cdd_I2c_hwSetOwnAddress(baseAddr, ownAddress);

    return;
}

void Cdd_I2c_hwDeInit(uint32 baseAddr)
{
    Cdd_I2c_hwDisableAllIntr(baseAddr);
    Cdd_I2c_hwClearAllStatus(baseAddr);
    Cdd_I2c_hwReset(baseAddr);

    return;
}

Cdd_I2c_ChannelResultType Cdd_I2c_hwTxPolling(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    uint16                    ctrlMask, ctrlCmds;
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;

    /* Wait for bus to get free */
    if (TRUE == chObj->doBusyCheck)
    {
        chResult = Cdd_I2c_hwWaitOnBusBusy(baseAddr);
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        Cdd_I2c_hwClearAllStatus(baseAddr);
        Cdd_I2c_hwSetSlaveAddress(baseAddr, chObj->deviceAddress);
        Cdd_I2c_hwSetDataCount(baseAddr, chObj->length);

        /* Master mode bit is auto cleared for every transaction - set this everytime */
        ctrlMask = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_TRX_MASK | CDD_I2C_ICMDR_RM_MASK | CDD_I2C_ICMDR_XA_MASK |
                   CDD_I2C_ICMDR_STP_MASK;
        ctrlCmds = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_TRX_MASK;
        if (CDD_I2C_10_BIT_ADDRESS == chObj->addressScheme)
        {
            ctrlCmds |= CDD_I2C_ICMDR_XA_MASK;
        }
        Cdd_I2c_hwSetMode(baseAddr, ctrlMask, ctrlCmds);

        /* Write the first data */
        Cdd_I2c_hwWriteData(baseAddr, *chObj->curTxBufPtr);
        chObj->curTxBufPtr++;
        chObj->curLength++;

        Cdd_I2c_hwStart(baseAddr);

        /* Wait for bus busy */
        chResult = Cdd_I2c_hwWaitForBusBusy(baseAddr);
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        /* Transmit the remaining data */
        while (chObj->curLength < chObj->length)
        {
            /* Wait for TX ready */
            chResult = Cdd_I2c_hwWaitForTxReady(baseAddr);
            if (CDD_I2C_CH_RESULT_OK != chResult)
            {
                /* NACK or AL Errors - force stop */
                Cdd_I2c_hwWaitForAccessReady(baseAddr);
                Cdd_I2c_hwStop(baseAddr);
                Cdd_I2c_hwWaitForStop(baseAddr);
                Cdd_I2c_hwClearAllStatus(baseAddr);
                break;
            }

            /* Write the remaining data */
            Cdd_I2c_hwWriteData(baseAddr, *chObj->curTxBufPtr);
            chObj->curTxBufPtr++;
            chObj->curLength++;
        }
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        /* Wait for register access ready */
        chResult = Cdd_I2c_hwWaitForAccessReady(baseAddr);
        if (CDD_I2C_CH_RESULT_OK == chResult)
        {
            /* Generate stop if required */
            if (TRUE == chObj->isStopRequired)
            {
                Cdd_I2c_hwStop(baseAddr);
                chResult = Cdd_I2c_hwWaitForStop(baseAddr);
            }
        }
    }

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_hwRxPolling(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    uint16                    ctrlMask, ctrlCmds;
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;

    /* Wait for bus to get free */
    if (TRUE == chObj->doBusyCheck)
    {
        chResult = Cdd_I2c_hwWaitOnBusBusy(baseAddr);
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        Cdd_I2c_hwClearAllStatus(baseAddr);
        Cdd_I2c_hwSetSlaveAddress(baseAddr, chObj->deviceAddress);
        Cdd_I2c_hwSetDataCount(baseAddr, chObj->length);

        /* Master mode bit is auto cleared for every transaction - set this everytime */
        ctrlMask = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_TRX_MASK | CDD_I2C_ICMDR_RM_MASK | CDD_I2C_ICMDR_XA_MASK |
                   CDD_I2C_ICMDR_STP_MASK;
        ctrlCmds = CDD_I2C_ICMDR_MST_MASK; /* Read */
        if (CDD_I2C_10_BIT_ADDRESS == chObj->addressScheme)
        {
            ctrlCmds |= CDD_I2C_ICMDR_XA_MASK;
        }
        Cdd_I2c_hwSetMode(baseAddr, ctrlMask, ctrlCmds);
        Cdd_I2c_hwStart(baseAddr);

        /* Wait for bus busy */
        chResult = Cdd_I2c_hwWaitForBusBusy(baseAddr);
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        /* Read the remaining bytes */
        while (chObj->curLength < chObj->length)
        {
            /* Wait for RX ready */
            chResult = Cdd_I2c_hwWaitForRxReady(baseAddr);
            if (CDD_I2C_CH_RESULT_OK != chResult)
            {
                /* NACK or AL Errors - force stop */
                Cdd_I2c_hwStop(baseAddr);
                Cdd_I2c_hwWaitForStop(baseAddr);
                Cdd_I2c_hwClearAllStatus(baseAddr);
                break;
            }

            /* Read the data */
            *chObj->curRxBufPtr = Cdd_I2c_hwReadData(baseAddr);
            chObj->curRxBufPtr++;
            chObj->curLength++;
        }
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        /* Generate stop if required */
        if (TRUE == chObj->isStopRequired)
        {
            Cdd_I2c_hwStop(baseAddr);
            chResult = Cdd_I2c_hwWaitForStop(baseAddr);
        }
    }

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_hwTxIntr(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    uint16                    ctrlMask, ctrlCmds;
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;

    /* Wait for bus to get free - TODO: Do we need for intr mode? */
    if (TRUE == chObj->doBusyCheck)
    {
        chResult = Cdd_I2c_hwWaitOnBusBusy(baseAddr);
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        Cdd_I2c_hwClearAllStatus(baseAddr);
        Cdd_I2c_hwSetSlaveAddress(baseAddr, chObj->deviceAddress);
        Cdd_I2c_hwSetDataCount(baseAddr, chObj->length);

        /* Master mode bit is auto cleared for every transaction - set this everytime */
        ctrlMask = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_TRX_MASK | CDD_I2C_ICMDR_RM_MASK | CDD_I2C_ICMDR_XA_MASK |
                   CDD_I2C_ICMDR_STP_MASK;
        ctrlCmds = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_TRX_MASK;
        if (CDD_I2C_10_BIT_ADDRESS == chObj->addressScheme)
        {
            ctrlCmds |= CDD_I2C_ICMDR_XA_MASK;
        }
        Cdd_I2c_hwSetMode(baseAddr, ctrlMask, ctrlCmds);
        Cdd_I2c_hwEnableIntr(baseAddr, CDD_I2C_HW_INTR_ENABLE_MASK_TX);

        /* Write the first data */
        Cdd_I2c_hwWriteData(baseAddr, *chObj->curTxBufPtr);
        chObj->curTxBufPtr++;
        chObj->curLength++;

        Cdd_I2c_hwStart(baseAddr);
        chResult = CDD_I2C_CH_RESULT_PENDING;
    }

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_hwRxIntr(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    uint16                    ctrlMask, ctrlCmds;
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;

    /* Wait for bus to get free - TODO: Do we need for intr mode? */
    if (TRUE == chObj->doBusyCheck)
    {
        chResult = Cdd_I2c_hwWaitOnBusBusy(baseAddr);
    }

    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        Cdd_I2c_hwClearAllStatus(baseAddr);
        Cdd_I2c_hwSetSlaveAddress(baseAddr, chObj->deviceAddress);
        Cdd_I2c_hwSetDataCount(baseAddr, chObj->length);

        /* Master mode bit is auto cleared for every transaction - set this everytime */
        ctrlMask = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_TRX_MASK | CDD_I2C_ICMDR_RM_MASK | CDD_I2C_ICMDR_XA_MASK |
                   CDD_I2C_ICMDR_STP_MASK;
        ctrlCmds = CDD_I2C_ICMDR_MST_MASK; /* Read */
        if (CDD_I2C_10_BIT_ADDRESS == chObj->addressScheme)
        {
            ctrlCmds |= CDD_I2C_ICMDR_XA_MASK;
        }
        Cdd_I2c_hwSetMode(baseAddr, ctrlMask, ctrlCmds);
        Cdd_I2c_hwEnableIntr(baseAddr, CDD_I2C_HW_INTR_ENABLE_MASK_RX);
        Cdd_I2c_hwStart(baseAddr);
        chResult = CDD_I2C_CH_RESULT_PENDING;
    }

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_hwContinueTxRxIntr(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult  = CDD_I2C_CH_RESULT_PENDING;
    uint16                    intrStatus;

    /* Get status */
    intrStatus = Cdd_I2c_hwGetIntrStatus(baseAddr);

    /* Check for errors */
    if ((intrStatus & CDD_I2C_HW_INTR_STATUS_MASK_ERR) != 0U)
    {
        if ((intrStatus & CDD_I2C_ICSTR_AL_MASK) != 0U)
        {
            chObj->chErrorCode = CDD_I2C_CH_RESULT_ARBFAIL;
        }
        if ((intrStatus & CDD_I2C_ICSTR_NACK_MASK) != 0U)
        {
            chObj->chErrorCode = CDD_I2C_CH_RESULT_NACKFAIL;
        }
        if ((intrStatus & CDD_I2C_ICSTR_AD0_MASK) != 0U)
        {
            chObj->chErrorCode = CDD_I2C_CH_RESULT_NOT_OK;
        }
        Cdd_I2c_hwDisableIntr(baseAddr, CDD_I2C_HW_INTR_STATUS_MASK_ERR);
        Cdd_I2c_hwClearIntr(baseAddr, CDD_I2C_HW_INTR_STATUS_MASK_ERR);

        /* NACK or AL Errors - force stop */
        Cdd_I2c_hwStop(baseAddr);
    }
    /* Check for stop condition */
    else if ((intrStatus & CDD_I2C_ICSTR_SCD_MASK) != 0U)
    {
        /* End of transfer - disable and clear all status */
        Cdd_I2c_hwDisableAllIntr(baseAddr);
        Cdd_I2c_hwClearAllStatus(baseAddr);
        chResult = chObj->chErrorCode;
    }
    else
    {
        /* Check for access ready condition */
        if ((CDD_I2C_WRITE == chObj->chCfg->direction) && ((intrStatus & CDD_I2C_ICIMR_ARDY_MASK) != 0U))
        {
            if (chObj->curLength == chObj->length)
            {
                Cdd_I2c_hwDisableIntr(baseAddr, CDD_I2C_ICIMR_ARDY_MASK);
                Cdd_I2c_hwClearIntr(baseAddr, CDD_I2C_ICSTR_ARDY_MASK);
                if (TRUE == chObj->isStopRequired)
                {
                    Cdd_I2c_hwStop(baseAddr);
                }
                else
                {
                    /* End of transfer - disable and clear all status */
                    Cdd_I2c_hwDisableAllIntr(baseAddr);
                    Cdd_I2c_hwClearAllStatus(baseAddr);
                    chResult = CDD_I2C_CH_RESULT_OK;
                }
            }
        }

        /* Check for receive ready */
        if ((CDD_I2C_READ == chObj->chCfg->direction) && (intrStatus & CDD_I2C_ICSTR_ICRRDY_MASK) != 0U)
        {
            if (chObj->curLength < chObj->length)
            {
                /* Read the data */
                *chObj->curRxBufPtr = Cdd_I2c_hwReadData(baseAddr);
                chObj->curRxBufPtr++;
                chObj->curLength++;
            }

            if (chObj->curLength == chObj->length)
            {
                Cdd_I2c_hwDisableIntr(baseAddr, CDD_I2C_ICIMR_ICRRDY_MASK);
                if (TRUE == chObj->isStopRequired)
                {
                    Cdd_I2c_hwStop(baseAddr);
                }
                else
                {
                    /* End of transfer - disable and clear all status */
                    Cdd_I2c_hwDisableAllIntr(baseAddr);
                    Cdd_I2c_hwClearAllStatus(baseAddr);
                    chResult = CDD_I2C_CH_RESULT_OK;
                }
            }
        }

        /* Check for transmit ready */
        if ((CDD_I2C_WRITE == chObj->chCfg->direction) && (intrStatus & CDD_I2C_ICSTR_ICXRDY_MASK) != 0U)
        {
            if (chObj->curLength < chObj->length)
            {
                /* Write the remaining data */
                Cdd_I2c_hwWriteData(baseAddr, *chObj->curTxBufPtr);
                chObj->curTxBufPtr++;
                chObj->curLength++;
            }

            if (chObj->curLength == chObj->length)
            {
                Cdd_I2c_hwDisableIntr(baseAddr, CDD_I2C_ICIMR_ICXRDY_MASK);
            }
        }
    }

    return chResult;
}

void Cdd_I2c_hwDisableAllIntr(uint32 baseAddr)
{
    Cdd_I2c_hwDisableIntr(baseAddr, CDD_I2C_HW_INTR_ENABLE_MASK_ALL);
}

void Cdd_I2c_hwClearAllStatus(uint32 baseAddr)
{
    Cdd_I2c_hwClearIntr(baseAddr, CDD_I2C_HW_INTR_STATUS_MASK_ALL);
}

#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
void Cdd_I2c_hwRegReadback(uint32 baseAddr, Cdd_I2c_RegisterReadbackType *regRbPtr)
{
    regRbPtr->prescalarreg      = HW_RD_REG16(baseAddr + CDD_I2C_ICPSC);
    regRbPtr->clkdividerlowreg  = HW_RD_REG16(baseAddr + CDD_I2C_ICCLKL);
    regRbPtr->clkdividerhighreg = HW_RD_REG16(baseAddr + CDD_I2C_ICCLKH);
    regRbPtr->modereg           = HW_RD_REG16(baseAddr + CDD_I2C_ICMDR);
    regRbPtr->ownaddrreg        = HW_RD_REG16(baseAddr + CDD_I2C_ICOAR);

    return;
}
#endif

static void Cdd_I2c_hwSetupClk(uint32 baseAddr, uint32 baudRate, uint32 hwUnitFrequency, uint32 sysClk)
{
    uint16 preScaler;
    uint16 diff;
    uint16 divisor, clkh, clkl;
    uint32 hwUnitFrequencyActual;

    /* Calculate prescaler */
    preScaler = (uint16)((sysClk / hwUnitFrequency) - 1U);
    HW_WR_REG16(baseAddr + CDD_I2C_ICPSC, preScaler);

    /* Determine diff based on prescaler */
    if (preScaler == 0U)
    {
        diff = 7U;
    }
    else if (preScaler == 1U)
    {
        diff = 6U;
    }
    else
    {
        diff = 5U;
    }

    /* Calculate divisor - use actual module frequency after prescaler */
    hwUnitFrequencyActual  = sysClk / (preScaler + 1U);
    divisor                = (uint16)(hwUnitFrequencyActual / baudRate);
    divisor               -= (2U * diff);
    clkh                   = divisor >> 1U;
    clkl                   = divisor - clkh;
    HW_WR_REG16(baseAddr + CDD_I2C_ICCLKH, clkh);
    HW_WR_REG16(baseAddr + CDD_I2C_ICCLKL, clkl);

    return;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitOnBusBusy(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;
    uint32                    intrStatus;

    // TODO: Implement timeout
    while (TRUE)
    {
        intrStatus = Cdd_I2c_hwGetIntrStatus(baseAddr);
        if ((intrStatus & CDD_I2C_ICSTR_BB_MASK) != CDD_I2C_ICSTR_BB_MASK)
        {
            break;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForBusBusy(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;
    uint32                    intrStatus;

    // TODO: Implement timeout
    while (TRUE)
    {
        intrStatus = Cdd_I2c_hwGetIntrStatus(baseAddr);
        if ((intrStatus & CDD_I2C_ICSTR_BB_MASK) == CDD_I2C_ICSTR_BB_MASK)
        {
            break;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForTxReady(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;
    uint32                    intrStatus;

    // TODO: Implement timeout
    while (TRUE)
    {
        intrStatus = Cdd_I2c_hwGetIntrStatus(baseAddr);
        if ((intrStatus & CDD_I2C_ICSTR_ICXRDY_MASK) == CDD_I2C_ICSTR_ICXRDY_MASK)
        {
            break;
        }
        if ((intrStatus & (CDD_I2C_ICSTR_AL_MASK | CDD_I2C_ICSTR_NACK_MASK | CDD_I2C_ICSTR_SCD_MASK)) != 0U)
        {
            chResult = CDD_I2C_CH_RESULT_NOT_OK;
            if ((intrStatus & CDD_I2C_ICSTR_AL_MASK) != 0U)
            {
                chResult = CDD_I2C_CH_RESULT_ARBFAIL;
            }
            if ((intrStatus & CDD_I2C_ICSTR_NACK_MASK) != 0U)
            {
                chResult = CDD_I2C_CH_RESULT_NACKFAIL;
            }
            if ((intrStatus & CDD_I2C_ICSTR_SCD_MASK) != 0U)
            {
                chResult = CDD_I2C_CH_RESULT_BUSFAIL;
            }
            break;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForRxReady(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;
    uint32                    intrStatus;

    // TODO: Implement timeout
    while (TRUE)
    {
        intrStatus = Cdd_I2c_hwGetIntrStatus(baseAddr);
        if ((intrStatus & CDD_I2C_ICSTR_ICRRDY_MASK) == CDD_I2C_ICSTR_ICRRDY_MASK)
        {
            break;
        }
        if ((intrStatus & (CDD_I2C_ICSTR_AL_MASK | CDD_I2C_ICSTR_NACK_MASK | CDD_I2C_ICSTR_SCD_MASK)) != 0U)
        {
            chResult = CDD_I2C_CH_RESULT_NOT_OK;
            if ((intrStatus & CDD_I2C_ICSTR_AL_MASK) != 0U)
            {
                chResult = CDD_I2C_CH_RESULT_ARBFAIL;
            }
            if ((intrStatus & CDD_I2C_ICSTR_NACK_MASK) != 0U)
            {
                chResult = CDD_I2C_CH_RESULT_NACKFAIL;
            }
            if ((intrStatus & CDD_I2C_ICSTR_SCD_MASK) != 0U)
            {
                chResult = CDD_I2C_CH_RESULT_BUSFAIL;
            }
            break;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForAccessReady(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;
    uint32                    intrStatus;

    // TODO: Implement timeout
    while (TRUE)
    {
        intrStatus = Cdd_I2c_hwGetIntrStatus(baseAddr);
        if ((intrStatus & CDD_I2C_ICSTR_ARDY_MASK) == CDD_I2C_ICSTR_ARDY_MASK)
        {
            break;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_hwWaitForStop(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;
    uint32                    intrStatus;

    // TODO: Implement timeout
    while (TRUE)
    {
        intrStatus = Cdd_I2c_hwGetIntrStatus(baseAddr);
        /* Wait for both stop to complete and bus to become free */
        if (((intrStatus & CDD_I2C_ICSTR_SCD_MASK) == CDD_I2C_ICSTR_SCD_MASK) &&
            ((intrStatus & CDD_I2C_ICSTR_BB_MASK) != CDD_I2C_ICSTR_BB_MASK))
        {
            break;
        }
    }

    return chResult;
}

static void Cdd_I2c_hwSetMode(uint32 baseAddr, uint16 ctrlMask, uint16 ctrlCmds)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(baseAddr + CDD_I2C_ICMDR);
    regVal &= ~ctrlMask;
    regVal |= ctrlCmds;
    HW_WR_REG16(baseAddr + CDD_I2C_ICMDR, regVal);
}

static void Cdd_I2c_hwReset(uint32 baseAddr)
{
    Cdd_I2c_hwSetMode(baseAddr, CDD_I2C_ICMDR_IRS_MASK, 0U);
}

static void Cdd_I2c_hwEnableModule(uint32 baseAddr)
{
    uint16 regVal;

    regVal = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_FREE_MASK | CDD_I2C_ICMDR_IRS_MASK;
    HW_WR_REG16(baseAddr + CDD_I2C_ICMDR, regVal);
}

static void Cdd_I2c_hwStart(uint32 baseAddr)
{
    Cdd_I2c_hwSetMode(baseAddr, CDD_I2C_ICMDR_STT_MASK, CDD_I2C_ICMDR_STT_MASK);
}

static void Cdd_I2c_hwStop(uint32 baseAddr)
{
    Cdd_I2c_hwSetMode(baseAddr, CDD_I2C_ICMDR_STP_MASK, CDD_I2C_ICMDR_STP_MASK);
}

static void Cdd_I2c_hwEnableIntr(uint32 baseAddr, uint16 mask)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(baseAddr + CDD_I2C_ICIMR);
    regVal |= mask;
    HW_WR_REG16(baseAddr + CDD_I2C_ICIMR, regVal);
}

static void Cdd_I2c_hwDisableIntr(uint32 baseAddr, uint16 mask)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(baseAddr + CDD_I2C_ICIMR);
    regVal &= (uint16)~mask;
    HW_WR_REG16(baseAddr + CDD_I2C_ICIMR, regVal);
}

static void Cdd_I2c_hwClearIntr(uint32 baseAddr, uint16 mask)
{
    /* TODO: STR needs to read before clearing without this restart is not working */
    volatile uint16 regVal;
    regVal = HW_RD_REG16(baseAddr + CDD_I2C_ICSTR);
    (void)regVal;

    HW_WR_REG16(baseAddr + CDD_I2C_ICSTR, mask);
}

static uint16 Cdd_I2c_hwGetIntrStatus(uint32 baseAddr)
{
    return HW_RD_REG16(baseAddr + CDD_I2C_ICSTR);
}

static void Cdd_I2c_hwSetOwnAddress(uint32 baseAddr, uint16 ownAddress)
{
    HW_WR_REG16(baseAddr + CDD_I2C_ICOAR, ownAddress);
}

static void Cdd_I2c_hwSetSlaveAddress(uint32 baseAddr, Cdd_I2c_AddressType deviceAddress)
{
    HW_WR_REG16(baseAddr + CDD_I2C_ICSAR, deviceAddress);
}

static void Cdd_I2c_hwSetDataCount(uint32 baseAddr, uint16 length)
{
    HW_WR_REG16(baseAddr + CDD_I2C_ICCNT, length);
}

static void Cdd_I2c_hwWriteData(uint32 baseAddr, uint8 data)
{
    HW_WR_REG8(baseAddr + CDD_I2C_ICDXR, data);
}

static uint8 Cdd_I2c_hwReadData(uint32 baseAddr)
{
    return HW_RD_REG8(baseAddr + CDD_I2C_ICDRR);
}

#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
