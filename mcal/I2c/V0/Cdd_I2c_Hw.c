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
 *  \file     Cdd_I2c_Hw.c
 *
 *  \brief    This file contains the private implementation of I2C HW functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_I2c_Hw.h"
#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
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

static void Cdd_I2c_HwSetup(Cdd_I2c_ChObjType *chObj, boolean isIntrMode);
static void Cdd_I2c_HwSetupClk(uint32 baseAddr, uint32 baudRate, uint32 hwUnitFrequency, uint32 sysClk);

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForBusFree(Cdd_I2c_ChObjType *chObj);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForBusBusy(Cdd_I2c_ChObjType *chObj);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferTxPolling(Cdd_I2c_ChObjType *chObj);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferTxIntr(Cdd_I2c_ChObjType *chObj, uint16 intrStatus);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferRxPolling(Cdd_I2c_ChObjType *chObj);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferRxIntr(Cdd_I2c_ChObjType *chObj, uint16 intrStatus);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForAccessReady(Cdd_I2c_ChObjType *chObj);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForStop(Cdd_I2c_ChObjType *chObj);

static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForTxReady(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForRxReady(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForAccessReady(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForStop(uint32 baseAddr);
static Cdd_I2c_ChannelResultType Cdd_I2c_HwGetErrorCode(uint16 intrStatus, boolean checkStopStatus);

static void Cdd_I2c_HwSetMode(uint32 baseAddr, uint16 ctrlMask, uint16 ctrlCmds);
static void Cdd_I2c_HwReset(uint32 baseAddr);
static void Cdd_I2c_HwEnableModule(uint32 baseAddr);
static void Cdd_I2c_HwStop(uint32 baseAddr);

static void   Cdd_I2c_HwEnableIntr(uint32 baseAddr, uint16 mask);
static void   Cdd_I2c_HwDisableIntr(uint32 baseAddr, uint16 mask);
static void   Cdd_I2c_HwClearIntr(uint32 baseAddr, uint16 mask);
static uint16 Cdd_I2c_HwGetIntrStatus(uint32 baseAddr);

static void  Cdd_I2c_HwSetOwnAddress(uint32 baseAddr, uint16 ownAddress);
static void  Cdd_I2c_HwSetSlaveAddress(uint32 baseAddr, Cdd_I2c_AddressType deviceAddress);
static void  Cdd_I2c_HwSetDataCount(uint32 baseAddr, uint16 length);
static void  Cdd_I2c_HwWriteData(uint32 baseAddr, uint8 data);
static uint8 Cdd_I2c_HwReadData(uint32 baseAddr);

/* ========================================================================== */
/*                        Local Object Definitions                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"

void Cdd_I2c_HwInit(uint32 baseAddr, uint32 baudRate, uint32 hwUnitFrequency, uint32 sysClk,
                    Cdd_I2c_AddressType ownAddress)
{
    Cdd_I2c_HwReset(baseAddr);

    /* Initialises I2C hardware unit for required baudrate */
    Cdd_I2c_HwSetupClk(baseAddr, baudRate, hwUnitFrequency, sysClk);

    /* Disable/clear all interrupts and enable the module */
    Cdd_I2c_HwDisableAllIntr(baseAddr);
    Cdd_I2c_HwClearAllStatus(baseAddr);
    Cdd_I2c_HwEnableModule(baseAddr);
    Cdd_I2c_HwSetOwnAddress(baseAddr, ownAddress);

    return;
}

void Cdd_I2c_HwDeInit(uint32 baseAddr)
{
    Cdd_I2c_HwDisableAllIntr(baseAddr);
    Cdd_I2c_HwClearAllStatus(baseAddr);
    Cdd_I2c_HwReset(baseAddr);

    return;
}

Cdd_I2c_ChannelResultType Cdd_I2c_HwTxPolling(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_ChannelResultType chResult;

    /* Init variables */
    chObj->chResult = CDD_I2C_CH_RESULT_PENDING;
    if (TRUE == chObj->doBusyCheck)
    {
        /* Wait for bus to get free */
        chObj->state = CDD_I2C_STATE_WAIT_FOR_BUS_FREE;
    }
    else
    {
        /* Start with setup state directly */
        chObj->state = CDD_I2C_STATE_SETUP;
    }
    chResult = Cdd_I2c_HwTxPollingContinue(chObj);

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_HwTxPollingContinue(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_ChannelResultType chResult = chObj->chResult;

    if (CDD_I2C_STATE_WAIT_FOR_BUS_FREE == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoWaitForBusFree(chObj);
    }

    if (CDD_I2C_STATE_SETUP == chObj->state)
    {
        Cdd_I2c_HwSetup(chObj, FALSE);
        chObj->state = CDD_I2C_STATE_WAIT_FOR_BUS_BUSY;
    }

    if (CDD_I2C_STATE_WAIT_FOR_BUS_BUSY == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoWaitForBusBusy(chObj);
    }

    if (CDD_I2C_STATE_DATA_TRANSFER == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoTransferTxPolling(chObj);
    }

    if (CDD_I2C_STATE_WAIT_FOR_ACCESS_READY == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoWaitForAccessReady(chObj);
    }

    if (CDD_I2C_STATE_WAIT_FOR_STOP == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoWaitForStop(chObj);
    }

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_HwRxPolling(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_ChannelResultType chResult;

    /* Init variables */
    chObj->chResult = CDD_I2C_CH_RESULT_PENDING;
    if (TRUE == chObj->doBusyCheck)
    {
        /* Wait for bus to get free */
        chObj->state = CDD_I2C_STATE_WAIT_FOR_BUS_FREE;
    }
    else
    {
        /* Start with setup state directly */
        chObj->state = CDD_I2C_STATE_SETUP;
    }
    chResult = Cdd_I2c_HwRxPollingContinue(chObj);

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_HwRxPollingContinue(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_ChannelResultType chResult = chObj->chResult;

    if (CDD_I2C_STATE_WAIT_FOR_BUS_FREE == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoWaitForBusFree(chObj);
    }

    if (CDD_I2C_STATE_SETUP == chObj->state)
    {
        Cdd_I2c_HwSetup(chObj, FALSE);
        chObj->state = CDD_I2C_STATE_WAIT_FOR_BUS_BUSY;
    }

    if (CDD_I2C_STATE_WAIT_FOR_BUS_BUSY == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoWaitForBusBusy(chObj);
    }

    if (CDD_I2C_STATE_DATA_TRANSFER == chObj->state)
    {
        /* Read the remaining bytes */
        chResult = Cdd_I2c_HwStateDoTransferRxPolling(chObj);
    }

    if (CDD_I2C_STATE_WAIT_FOR_STOP == chObj->state)
    {
        chResult = Cdd_I2c_HwStateDoWaitForStop(chObj);
    }

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_HwTxIntr(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;

    Cdd_I2c_HwSetup(chObj, TRUE);
    chObj->state = CDD_I2C_STATE_DATA_TRANSFER;

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_HwRxIntr(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_OK;

    Cdd_I2c_HwSetup(chObj, TRUE);
    chObj->state = CDD_I2C_STATE_DATA_TRANSFER;

    return chResult;
}

Cdd_I2c_ChannelResultType Cdd_I2c_HwTxRxIntrContinue(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult  = CDD_I2C_CH_RESULT_PENDING;
    Cdd_I2c_ChannelResultType chErrorCode;
    uint16                    intrStatus;

    /* Get status */
    intrStatus = Cdd_I2c_HwGetIntrStatus(baseAddr);

    /* Check for errors */
    chErrorCode = Cdd_I2c_HwGetErrorCode(intrStatus, FALSE);
    if (chErrorCode != CDD_I2C_CH_RESULT_OK)
    {
        chObj->chErrorCode = chErrorCode;
        Cdd_I2c_HwDisableIntr(baseAddr, CDD_I2C_HW_INTR_STATUS_MASK_ERR);
        Cdd_I2c_HwClearIntr(baseAddr, CDD_I2C_HW_INTR_STATUS_MASK_ERR);

        /* NACK or AL Errors - force stop */
        chObj->state = CDD_I2C_STATE_WAIT_FOR_STOP;
        Cdd_I2c_HwStop(baseAddr);
    }
    /* Check for stop condition */
    else if ((intrStatus & CDD_I2C_ICSTR_SCD_MASK) != 0U)
    {
        /* End of transfer - disable and clear all status */
        Cdd_I2c_HwDisableAllIntr(baseAddr);
        Cdd_I2c_HwClearAllStatus(baseAddr);
        chResult     = chObj->chErrorCode;
        chObj->state = CDD_I2C_STATE_COMPLETE;
    }
    else
    {
        if (CDD_I2C_WRITE == chObj->chCfg->direction)
        {
            chResult = Cdd_I2c_HwStateDoTransferTxIntr(chObj, intrStatus);
        }
        else
        {
            chResult = Cdd_I2c_HwStateDoTransferRxIntr(chObj, intrStatus);
        }
    }

    return chResult;
}

void Cdd_I2c_HwCancelPolling(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult;

    /* Force stop only if the channel is started */
    if (chObj->state > CDD_I2C_STATE_SETUP)
    {
        // TODO: Implement timeout
        Cdd_I2c_HwStop(baseAddr);
        do
        {
            chResult = Cdd_I2c_HwStateDoWaitForStop(chObj);
        } while (chResult != CDD_I2C_CH_RESULT_OK);
    }

    return;
}

void Cdd_I2c_HwCancelIntr(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult;

    /* Force stop only if the channel is started */
    if (chObj->state > CDD_I2C_STATE_SETUP)
    {
        /* Disable and clear all interrupts and perform stop from same context */
        Cdd_I2c_HwDisableAllIntr(baseAddr);
        Cdd_I2c_HwClearAllStatus(baseAddr);

        // TODO: Implement timeout
        Cdd_I2c_HwStop(baseAddr);
        do
        {
            chResult = Cdd_I2c_HwStateDoWaitForStop(chObj);
        } while (chResult != CDD_I2C_CH_RESULT_OK);
    }

    return;
}

void Cdd_I2c_HwDisableAllIntr(uint32 baseAddr)
{
    Cdd_I2c_HwDisableIntr(baseAddr, CDD_I2C_HW_INTR_ENABLE_MASK_ALL);
}

void Cdd_I2c_HwClearAllStatus(uint32 baseAddr)
{
    Cdd_I2c_HwClearIntr(baseAddr, CDD_I2C_HW_INTR_STATUS_MASK_ALL);
}

#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
void Cdd_I2c_HwRegReadback(uint32 baseAddr, Cdd_I2c_RegisterReadbackType *regRbPtr)
{
    regRbPtr->prescalarreg      = HW_RD_REG16(baseAddr + CDD_I2C_ICPSC);
    regRbPtr->clkdividerlowreg  = HW_RD_REG16(baseAddr + CDD_I2C_ICCLKL);
    regRbPtr->clkdividerhighreg = HW_RD_REG16(baseAddr + CDD_I2C_ICCLKH);
    regRbPtr->modereg           = HW_RD_REG16(baseAddr + CDD_I2C_ICMDR);
    regRbPtr->ownaddrreg        = HW_RD_REG16(baseAddr + CDD_I2C_ICOAR);

    return;
}
#endif

static void Cdd_I2c_HwSetup(Cdd_I2c_ChObjType *chObj, boolean isIntrMode)
{
    Cdd_I2c_HwUnitObjType *hwUnitObj = chObj->hwUnitObj;
    uint32                 baseAddr  = hwUnitObj->baseAddr;
    uint16                 ctrlMask, ctrlCmds;

    Cdd_I2c_HwClearAllStatus(baseAddr);
    Cdd_I2c_HwSetSlaveAddress(baseAddr, chObj->deviceAddress);
    Cdd_I2c_HwSetDataCount(baseAddr, chObj->length);
    if (isIntrMode == TRUE)
    {
        if (CDD_I2C_WRITE == chObj->chCfg->direction)
        {
            Cdd_I2c_HwEnableIntr(baseAddr, CDD_I2C_HW_INTR_ENABLE_MASK_TX);
        }
        else
        {
            Cdd_I2c_HwEnableIntr(baseAddr, CDD_I2C_HW_INTR_ENABLE_MASK_RX);
        }
    }

    /* Master mode bit is auto cleared for every transaction - set this everytime */
    ctrlMask = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_TRX_MASK | CDD_I2C_ICMDR_RM_MASK | CDD_I2C_ICMDR_XA_MASK |
               CDD_I2C_ICMDR_STP_MASK;
    ctrlCmds = CDD_I2C_ICMDR_MST_MASK;
    if (CDD_I2C_WRITE == chObj->chCfg->direction)
    {
        ctrlCmds |= CDD_I2C_ICMDR_TRX_MASK;
    }
    if (CDD_I2C_10_BIT_ADDRESS == chObj->addressScheme)
    {
        ctrlCmds |= CDD_I2C_ICMDR_XA_MASK;
    }
    /* Start along with setting other bits */
    ctrlMask |= CDD_I2C_ICMDR_STT_MASK;
    ctrlCmds |= CDD_I2C_ICMDR_STT_MASK;

    if (CDD_I2C_WRITE == chObj->chCfg->direction)
    {
        /* Write the first data */
        Cdd_I2c_HwWriteData(baseAddr, *chObj->curTxBufPtr);
        chObj->curTxBufPtr++;
        chObj->curLength++;
    }

    /* Start */
    Cdd_I2c_HwSetMode(baseAddr, ctrlMask, ctrlCmds);

    return;
}

static void Cdd_I2c_HwSetupClk(uint32 baseAddr, uint32 baudRate, uint32 hwUnitFrequency, uint32 sysClk)
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
    hwUnitFrequencyActual  = sysClk / ((uint32)preScaler + 1U);
    divisor                = (uint16)(hwUnitFrequencyActual / baudRate);
    divisor               -= (2U * diff);
    clkh                   = divisor >> 1U;
    clkl                   = divisor - clkh;
    HW_WR_REG16(baseAddr + CDD_I2C_ICCLKH, clkh);
    HW_WR_REG16(baseAddr + CDD_I2C_ICCLKL, clkl);

    return;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForBusFree(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult  = CDD_I2C_CH_RESULT_PENDING;
    uint16                    intrStatus;

    intrStatus = Cdd_I2c_HwGetIntrStatus(baseAddr);
    /* TI_COVERAGE_GAP_START Bus busy cannot be recreated in test environment as we don't have multi-master setup */
    if ((intrStatus & CDD_I2C_ICSTR_BB_MASK) != CDD_I2C_ICSTR_BB_MASK)
    {
        /* Bus is free - Move to next state */
        chObj->state = CDD_I2C_STATE_SETUP;
    }
    /* TI_COVERAGE_GAP_STOP */

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForBusBusy(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult  = CDD_I2C_CH_RESULT_PENDING;
    uint16                    intrStatus;

    intrStatus = Cdd_I2c_HwGetIntrStatus(baseAddr);
    if ((intrStatus & CDD_I2C_ICSTR_BB_MASK) == CDD_I2C_ICSTR_BB_MASK)
    {
        /* Bus became busy - Move to next state */
        chObj->state = CDD_I2C_STATE_DATA_TRANSFER;
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferTxPolling(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult;

    chResult = Cdd_I2c_HwCheckForTxReady(baseAddr);
    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        chResult = CDD_I2C_CH_RESULT_PENDING;
        if (chObj->curLength < chObj->length)
        {
            /* Write the remaining data */
            Cdd_I2c_HwWriteData(baseAddr, *chObj->curTxBufPtr);
            chObj->curTxBufPtr++;
            chObj->curLength++;
        }
        else
        {
            chObj->state = CDD_I2C_STATE_WAIT_FOR_ACCESS_READY;
        }
    }
    else
    {
        if (CDD_I2C_CH_RESULT_PENDING != chResult)
        {
            /* NACK or AL Errors - force stop */
            chObj->chErrorCode = chResult;
            chResult           = CDD_I2C_CH_RESULT_PENDING;
            chObj->state       = CDD_I2C_STATE_WAIT_FOR_ACCESS_READY;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferTxIntr(Cdd_I2c_ChObjType *chObj, uint16 intrStatus)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult  = CDD_I2C_CH_RESULT_PENDING;

    /* Check for access ready condition */
    if ((intrStatus & CDD_I2C_ICIMR_ARDY_MASK) != 0U)
    {
        if (chObj->curLength == chObj->length)
        {
            Cdd_I2c_HwDisableIntr(baseAddr, CDD_I2C_ICIMR_ARDY_MASK);
            Cdd_I2c_HwClearIntr(baseAddr, CDD_I2C_ICSTR_ARDY_MASK);
            if (TRUE == chObj->isStopRequired)
            {
                chObj->state = CDD_I2C_STATE_WAIT_FOR_STOP;
                Cdd_I2c_HwStop(baseAddr);
            }
            else
            {
                /* End of transfer - disable and clear all status */
                Cdd_I2c_HwDisableAllIntr(baseAddr);
                Cdd_I2c_HwClearAllStatus(baseAddr);
                chResult     = CDD_I2C_CH_RESULT_OK;
                chObj->state = CDD_I2C_STATE_COMPLETE;
            }
        }
    }

    /* Check for transmit ready */
    if ((intrStatus & CDD_I2C_ICSTR_ICXRDY_MASK) != 0U)
    {
        if (chObj->curLength < chObj->length)
        {
            /* Write the remaining data */
            Cdd_I2c_HwWriteData(baseAddr, *chObj->curTxBufPtr);
            chObj->curTxBufPtr++;
            chObj->curLength++;
        }

        if (chObj->curLength == chObj->length)
        {
            Cdd_I2c_HwDisableIntr(baseAddr, CDD_I2C_ICIMR_ICXRDY_MASK);
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferRxPolling(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult  = CDD_I2C_CH_RESULT_PENDING;

    /* Read as long we have data */
    while (chObj->curLength < chObj->length)
    {
        chResult = Cdd_I2c_HwCheckForRxReady(baseAddr);
        if (CDD_I2C_CH_RESULT_OK == chResult)
        {
            chResult = CDD_I2C_CH_RESULT_PENDING;

            /* Read the data */
            *chObj->curRxBufPtr = Cdd_I2c_HwReadData(baseAddr);
            chObj->curRxBufPtr++;
            chObj->curLength++;
        }
        else
        {
            if (CDD_I2C_CH_RESULT_PENDING != chResult)
            {
                /* NACK or AL Errors - force stop */
                chObj->chErrorCode = chResult;
                chResult           = CDD_I2C_CH_RESULT_PENDING;
                chObj->state       = CDD_I2C_STATE_WAIT_FOR_STOP;
                Cdd_I2c_HwStop(baseAddr);
            }
            break;
        }
    }

    if ((chObj->chErrorCode == CDD_I2C_CH_RESULT_OK) && (chObj->curLength == chObj->length))
    {
        /* Generate stop if required */
        if (TRUE == chObj->isStopRequired)
        {
            chObj->state = CDD_I2C_STATE_WAIT_FOR_STOP;
            Cdd_I2c_HwStop(baseAddr);
        }
        else
        {
            Cdd_I2c_HwClearAllStatus(baseAddr);
            /* Use any error code that is already detected */
            chResult     = chObj->chErrorCode;
            chObj->state = CDD_I2C_STATE_COMPLETE;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoTransferRxIntr(Cdd_I2c_ChObjType *chObj, uint16 intrStatus)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult  = CDD_I2C_CH_RESULT_PENDING;

    if ((intrStatus & CDD_I2C_ICSTR_ICRRDY_MASK) != 0U)
    {
        if (chObj->curLength < chObj->length)
        {
            /* Read the data */
            *chObj->curRxBufPtr = Cdd_I2c_HwReadData(baseAddr);
            chObj->curRxBufPtr++;
            chObj->curLength++;
        }

        if (chObj->curLength == chObj->length)
        {
            Cdd_I2c_HwDisableIntr(baseAddr, CDD_I2C_ICIMR_ICRRDY_MASK);
            if (TRUE == chObj->isStopRequired)
            {
                chObj->state = CDD_I2C_STATE_WAIT_FOR_STOP;
                Cdd_I2c_HwStop(baseAddr);
            }
            else
            {
                /* End of transfer - disable and clear all status */
                Cdd_I2c_HwDisableAllIntr(baseAddr);
                Cdd_I2c_HwClearAllStatus(baseAddr);
                chResult     = CDD_I2C_CH_RESULT_OK;
                chObj->state = CDD_I2C_STATE_COMPLETE;
            }
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForAccessReady(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult;

    chResult = Cdd_I2c_HwCheckForAccessReady(baseAddr);
    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        /* Generate stop if required or in case of error */
        if ((TRUE == chObj->isStopRequired) || (chObj->chErrorCode != CDD_I2C_CH_RESULT_OK))
        {
            chResult     = CDD_I2C_CH_RESULT_PENDING;
            chObj->state = CDD_I2C_STATE_WAIT_FOR_STOP;
            Cdd_I2c_HwStop(baseAddr);
        }
        else
        {
            Cdd_I2c_HwClearAllStatus(baseAddr);
            /* Use any error code that is already detected */
            chResult     = chObj->chErrorCode;
            chObj->state = CDD_I2C_STATE_COMPLETE;
        }
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwStateDoWaitForStop(Cdd_I2c_ChObjType *chObj)
{
    Cdd_I2c_HwUnitObjType    *hwUnitObj = chObj->hwUnitObj;
    uint32                    baseAddr  = hwUnitObj->baseAddr;
    Cdd_I2c_ChannelResultType chResult;

    chResult = Cdd_I2c_HwCheckForStop(baseAddr);
    if (CDD_I2C_CH_RESULT_OK == chResult)
    {
        Cdd_I2c_HwClearAllStatus(baseAddr);
        /* Use any error code that is already detected */
        chResult     = chObj->chErrorCode;
        chObj->state = CDD_I2C_STATE_COMPLETE;
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForTxReady(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_PENDING;
    Cdd_I2c_ChannelResultType chErrorCode;
    uint16                    intrStatus;

    intrStatus = Cdd_I2c_HwGetIntrStatus(baseAddr);
    if ((intrStatus & CDD_I2C_ICSTR_ICXRDY_MASK) == CDD_I2C_ICSTR_ICXRDY_MASK)
    {
        chResult = CDD_I2C_CH_RESULT_OK;
    }
    chErrorCode = Cdd_I2c_HwGetErrorCode(intrStatus, TRUE);
    if (chErrorCode != CDD_I2C_CH_RESULT_OK)
    {
        chResult = chErrorCode;
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForRxReady(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_PENDING;
    Cdd_I2c_ChannelResultType chErrorCode;
    uint16                    intrStatus;

    intrStatus = Cdd_I2c_HwGetIntrStatus(baseAddr);
    if ((intrStatus & CDD_I2C_ICSTR_ICRRDY_MASK) == CDD_I2C_ICSTR_ICRRDY_MASK)
    {
        chResult = CDD_I2C_CH_RESULT_OK;
    }
    chErrorCode = Cdd_I2c_HwGetErrorCode(intrStatus, TRUE);
    if (chErrorCode != CDD_I2C_CH_RESULT_OK)
    {
        chResult = chErrorCode;
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForAccessReady(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_PENDING;
    uint16                    intrStatus;

    intrStatus = Cdd_I2c_HwGetIntrStatus(baseAddr);
    if ((intrStatus & CDD_I2C_ICSTR_ARDY_MASK) == CDD_I2C_ICSTR_ARDY_MASK)
    {
        chResult = CDD_I2C_CH_RESULT_OK;
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwCheckForStop(uint32 baseAddr)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_PENDING;
    uint16                    intrStatus, pinStatus;
    uint32                    matchCount = 0U;

    intrStatus = Cdd_I2c_HwGetIntrStatus(baseAddr);
    /* Also check the external SCL and SDA pins to go high (free) */
    pinStatus = HW_RD_REG16(baseAddr + CDD_I2C_ICPDIN);

    /* Check intr status - Stop set */
    if ((intrStatus & CDD_I2C_ICSTR_SCD_MASK) == CDD_I2C_ICSTR_SCD_MASK)
    {
        matchCount++;
    }
    /* Check intr status - Bus should be free */
    if ((intrStatus & CDD_I2C_ICSTR_BB_MASK) != CDD_I2C_ICSTR_BB_MASK)
    {
        matchCount++;
    }
    /* Check pin status */
    if ((pinStatus & (CDD_I2C_ICPDIN_PDIN0_MASK | CDD_I2C_ICPDIN_PDIN1_MASK)) ==
        (CDD_I2C_ICPDIN_PDIN0_MASK | CDD_I2C_ICPDIN_PDIN1_MASK))
    {
        matchCount++;
    }

    /* Wait for all condition to be true */
    if (matchCount == 3U)
    {
        chResult = CDD_I2C_CH_RESULT_OK;
    }

    return chResult;
}

static Cdd_I2c_ChannelResultType Cdd_I2c_HwGetErrorCode(uint16 intrStatus, boolean checkStopStatus)
{
    Cdd_I2c_ChannelResultType chErrorCode = CDD_I2C_CH_RESULT_OK;

    /* TI_COVERAGE_GAP_START Arbitration loss error cannot be recreated in test environment */
    if ((intrStatus & CDD_I2C_ICSTR_AL_MASK) != 0U)
    {
        chErrorCode = CDD_I2C_CH_RESULT_ARBFAIL;
    }
    /* TI_COVERAGE_GAP_STOP */
    if ((intrStatus & CDD_I2C_ICSTR_NACK_MASK) != 0U)
    {
        chErrorCode = CDD_I2C_CH_RESULT_NACKFAIL;
    }
    /* TI_COVERAGE_GAP_START Address zero error cannot be recreated in test environment */
    if ((intrStatus & CDD_I2C_ICSTR_AD0_MASK) != 0U)
    {
        chErrorCode = CDD_I2C_CH_RESULT_NOT_OK;
    }
    /* TI_COVERAGE_GAP_STOP */
    /* Check this only for polled mode as in intr mode
     * we use stop intr status for getting interrupt and handle
     * the transfer end */
    if (TRUE == checkStopStatus)
    {
        /* TI_COVERAGE_GAP_START Bus fail error cannot be recreated in test environment */
        if ((intrStatus & CDD_I2C_ICSTR_SCD_MASK) != 0U)
        {
            chErrorCode = CDD_I2C_CH_RESULT_BUSFAIL;
        }
        /* TI_COVERAGE_GAP_STOP */
    }

    return chErrorCode;
}

static void Cdd_I2c_HwSetMode(uint32 baseAddr, uint16 ctrlMask, uint16 ctrlCmds)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(baseAddr + CDD_I2C_ICMDR);
    regVal &= ~ctrlMask;
    regVal |= ctrlCmds;
    HW_WR_REG16(baseAddr + CDD_I2C_ICMDR, regVal);
}

static void Cdd_I2c_HwReset(uint32 baseAddr)
{
    Cdd_I2c_HwSetMode(baseAddr, CDD_I2C_ICMDR_IRS_MASK, 0U);
}

static void Cdd_I2c_HwEnableModule(uint32 baseAddr)
{
    uint16 regVal;

    regVal = CDD_I2C_ICMDR_MST_MASK | CDD_I2C_ICMDR_FREE_MASK | CDD_I2C_ICMDR_IRS_MASK;
    HW_WR_REG16(baseAddr + CDD_I2C_ICMDR, regVal);
}

static void Cdd_I2c_HwStop(uint32 baseAddr)
{
    Cdd_I2c_HwSetMode(baseAddr, CDD_I2C_ICMDR_STP_MASK, CDD_I2C_ICMDR_STP_MASK);
}

static void Cdd_I2c_HwEnableIntr(uint32 baseAddr, uint16 mask)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(baseAddr + CDD_I2C_ICIMR);
    regVal |= mask;
    HW_WR_REG16(baseAddr + CDD_I2C_ICIMR, regVal);
}

static void Cdd_I2c_HwDisableIntr(uint32 baseAddr, uint16 mask)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(baseAddr + CDD_I2C_ICIMR);
    regVal &= (uint16)~mask;
    HW_WR_REG16(baseAddr + CDD_I2C_ICIMR, regVal);
}

static void Cdd_I2c_HwClearIntr(uint32 baseAddr, uint16 mask)
{
    /* TODO: STR needs to read before clearing without this restart is not working */
    volatile uint16 regVal;
    regVal = HW_RD_REG16(baseAddr + CDD_I2C_ICSTR);
    (void)regVal;

    HW_WR_REG16(baseAddr + CDD_I2C_ICSTR, mask);
}

static uint16 Cdd_I2c_HwGetIntrStatus(uint32 baseAddr)
{
    return HW_RD_REG16(baseAddr + CDD_I2C_ICSTR);
}

static void Cdd_I2c_HwSetOwnAddress(uint32 baseAddr, uint16 ownAddress)
{
    HW_WR_REG16(baseAddr + CDD_I2C_ICOAR, ownAddress);
}

static void Cdd_I2c_HwSetSlaveAddress(uint32 baseAddr, Cdd_I2c_AddressType deviceAddress)
{
    HW_WR_REG16(baseAddr + CDD_I2C_ICSAR, deviceAddress);
}

static void Cdd_I2c_HwSetDataCount(uint32 baseAddr, uint16 length)
{
    HW_WR_REG16(baseAddr + CDD_I2C_ICCNT, length);
}

static void Cdd_I2c_HwWriteData(uint32 baseAddr, uint8 data)
{
    HW_WR_REG8(baseAddr + CDD_I2C_ICDXR, data);
}

static uint8 Cdd_I2c_HwReadData(uint32 baseAddr)
{
    return HW_RD_REG8(baseAddr + CDD_I2C_ICDRR);
}

#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
