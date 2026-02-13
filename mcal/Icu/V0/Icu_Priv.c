/*
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file   Icu_Priv.c
 *
 *  \brief  This file contains the Internal APIs for ICU.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Icu_Priv.h"
#include "string.h"
#include "Icu_Cfg.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
#if (STD_ON == ICU_TIMESTAMP_API)
static FUNC(void, ICU_CODE) ICU_Timestamp_ISRProcess(Icu_ChannelType Channel);
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"

void ICU_ECAP_selectECAPInput(uint32 base, Icu_XbarSelect input)
{
    HW_WR_REG16(base + CSL_ECAP_ECCTL0,
                ((HW_RD_REG16(base + CSL_ECAP_ECCTL0) & ~CSL_ECAP_ECCTL0_INPUTSEL_MASK) | (uint16)input));
}

void Icu_ResetChObj(Icu_ChObjType *chObj)
{
#if (ICU_TIMESTAMP_API == STD_ON)
    chObj->NextTimeStampIndexPtr = (Icu_ValueType *)NULL_PTR;
    chObj->NextTimeStampIndex    = 0U;
    chObj->TimeStampBufferSize   = 0U;
    chObj->NotifyInterval        = 0U;
    chObj->NotificationCounter   = 0U;
    chObj->IsActive              = FALSE;
#endif
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
    chObj->cap1                 = 0U;
    chObj->cap2                 = 0U;
    chObj->cap3                 = 0U;
    chObj->cap4                 = 0U;
    chObj->HighTime             = 0U;
    chObj->LowTime              = 0U;
    chObj->Period               = 0U;
    chObj->DutyCycle.ActiveTime = (Icu_ValueType)0U;
    chObj->DutyCycle.PeriodTime = (Icu_ValueType)0U;
    chObj->PeriodAcquired       = FALSE;
    chObj->DutyAcquired         = FALSE;
#endif
    chObj->InputState = (Icu_InputStateType)ICU_IDLE;
#if (ICU_EDGE_COUNT_API == STD_ON)
    chObj->EdgeCounter = (Icu_EdgeNumberType)0U;
#endif
    chObj->activation_edge                 = ICU_BOTH_EDGES;
    chObj->IsRunning                       = FALSE;
    chObj->NotificationEnabled             = FALSE;
    chObj->baseAddr                        = 0U;
    chObj->prescaler                       = 0U;
    chObj->chCfg.defaultStartEdge          = ICU_BOTH_EDGES;
    chObj->chCfg.xbarSelect                = INPUT_XBAR_0;
    chObj->chCfg.intrcapSelect             = ECAP_INT_ALLCAPS;
    chObj->chCfg.measurementMode           = ICU_MODE_SIGNAL_MEASUREMENT;
    chObj->chCfg.signalMeasurementProperty = ICU_PERIOD_TIME;
    chObj->chCfg.notificationHandler       = (Icu_NotifyFuncType)NULL_PTR;
    chObj->chCfg.bufferType                = ICU_LINEAR_BUFFER;
    chObj->chCfg.instanceClkMHz            = 0U;
    chObj->chCfg.prescaler                 = 0U;
    chObj->chCfg_PC.channelId              = 0U;
    return;
}

void Icu_CopyConfig(Icu_ChObjType *chObj, const Icu_ChannelConfigType *chCfg, const Icu_ChannelConfigType_PC *chCfg_pc)
{
    Icu_ChannelType channelNumber;
    /* Copying the Config stucture to Channel Object*/
    (void)memcpy(&chObj->chCfg, &chCfg[0U], sizeof(Icu_ChannelConfigType));

    /*Copying the pre-compile config structure to Channel Object */
    chObj->chCfg_PC.channelId = chCfg_pc->channelId;
    chObj->activation_edge    = chCfg->defaultStartEdge;
    channelNumber             = chObj->chCfg_PC.channelId;
    chObj->prescaler          = (Icu_ChannelPrescalerType)chCfg->prescaler;
    /* Store base address of all the configured channels */
    chObj->baseAddr = Icu_GetBaseAddr(channelNumber);
    return;
}

FUNC(uint32, ICU_CODE) Icu_GetBaseAddr(Icu_ChannelType ChannelNumber)
{
    uint32 baseAddr;

#if (ICU_DEV_ERROR_DETECT == STD_ON)
    if (ChannelNumber >= (uint32)ICU_MAX_NUM_CHANNELS)
    {
        (void)Icu_reportDetError(ICU_INIT_ID, ICU_E_PARAM_CHANNEL);
        baseAddr = 0U;
    }
    else
#endif
    {
        baseAddr = Icu_HwUnitBaseAddr[ChannelNumber];
    }
    return (baseAddr);
}

void Icu_HwUnitInit(Icu_ChObjType *chObj)
{
    uint32 baseAddr;
    baseAddr = chObj->baseAddr;
    /*Disable and Clear Interrupts*/
    ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
    ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);

    /* Disable CAP1-CAP4 register loads */
    ICU_ECAP_captureLoadingDisable(baseAddr);

    /* Configure eCAP
     *    Enable capture mode.
     *    Continous, stop capture at event 4.
     *    Set polarity based on default start edge configuration.
     *    Set capture in time difference mode.
     *    Enable eCAP module.
     */

    ICU_ECAP_counterControl(baseAddr, ECAP_COUNTER_STOP);
    ICU_ECAP_operatingModeSelect(baseAddr, ECAP_CAPTURE_MODE);

    /*Configure initial parameters:*/
    ICU_ECAP_continousModeConfig(baseAddr);
    ICU_ECAP_prescaleConfig(baseAddr, chObj->prescaler);

    if (chObj->activation_edge == ICU_RISING_EDGE)
    {
        ICU_ECAP_captureEvtPolarityConfig(baseAddr, ICU_RISING, ICU_RISING, ICU_RISING, ICU_RISING);
    }
    else if (chObj->activation_edge == ICU_FALLING_EDGE)
    {
        ICU_ECAP_captureEvtPolarityConfig(baseAddr, ICU_FALLING, ICU_FALLING, ICU_FALLING, ICU_FALLING);
    }
    else if (chObj->activation_edge == ICU_BOTH_EDGES)
    {
        ICU_ECAP_captureEvtPolarityConfig(baseAddr, ICU_FALLING, ICU_RISING, ICU_FALLING, ICU_RISING);
    }
    else
    {
        /*MISRA-C*/
    }

    ICU_ECAP_captureEvtCntrRstConfig(baseAddr, 1, 1, 1, 1); /*Delta Mode*/
    ICU_ECAP_selectECAPInput(baseAddr, chObj->chCfg.xbarSelect);

    ICU_ECAP_syncInOutSelect(baseAddr, ECAP_ENABLE_COUNTER, ECAP_SYNC_IN);  // changed 2nd para
    ICU_ECAP_setEmulationMode(baseAddr, ECAP_EMULATION_STOP);
    ICU_ECAP_setSyncInPulseSource(baseAddr, ECAP_SYNC_IN_PULSE_SRC_DISABLE);
    ICU_ECAP_counterControl(baseAddr, ECAP_COUNTER_FREE_RUNNING);
    ICU_ECAP_captureLoadingEnable(baseAddr);
}

void Icu_ConfigEcap(uint32 baseAddr, Icu_ActivationType activation, Icu_CounterRstType cntRst, boolean interruptEnable,
                    Icu_IntrCapSelect capture)
{
    ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
    ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);
    ECAP_clearGlobalInterrupt(baseAddr);

    /* Disable CAP1-CAP4 register loads */
    ICU_ECAP_captureLoadingDisable(baseAddr);
    ICU_ECAP_cap1Reset(baseAddr);
    ICU_ECAP_cap2Reset(baseAddr);
    ICU_ECAP_cap3Reset(baseAddr);
    ICU_ECAP_cap4Reset(baseAddr);

    ICU_ECAP_counterControl(baseAddr, ECAP_COUNTER_STOP);
    ICU_ECAP_operatingModeSelect(baseAddr, ECAP_CAPTURE_MODE);
    ICU_ECAP_continousModeConfig(baseAddr);
    if (activation == ICU_RISING_EDGE)
    {
        ICU_ECAP_captureEvtPolarityConfig(baseAddr, ICU_RISING, ICU_RISING, ICU_RISING, ICU_RISING);
    }
    else if (activation == ICU_FALLING_EDGE)
    {
        ICU_ECAP_captureEvtPolarityConfig(baseAddr, ICU_FALLING, ICU_FALLING, ICU_FALLING, ICU_FALLING);
    }
    else if (activation == ICU_BOTH_EDGES)
    {
        ICU_ECAP_captureEvtPolarityConfig(baseAddr, ICU_FALLING, ICU_RISING, ICU_FALLING, ICU_RISING);
    }
    else
    {
        /*MISRA-C*/
    }

    if (cntRst == ICU_ABSOLUTE_MODE)
    {
        ICU_ECAP_captureEvtCntrRstConfig(baseAddr, 0, 0, 0, 0); /*using absolute mode*/
    }
    else if (cntRst == ICU_DELTA_MODE)
    {
        ICU_ECAP_captureEvtCntrRstConfig(baseAddr, 1, 1, 1, 1); /*using delta mode*/
    }
    else
    {
        /*MISRA-C*/
    }

    ICU_ECAP_syncInOutSelect(baseAddr, ECAP_ENABLE_COUNTER, ECAP_SYNC_IN);
    ICU_ECAP_setEmulationMode(baseAddr, ECAP_EMULATION_STOP);
    ICU_ECAP_setSyncInPulseSource(baseAddr, ECAP_SYNC_IN_PULSE_SRC_DISABLE);
    ICU_ECAP_counterControl(baseAddr, ECAP_COUNTER_FREE_RUNNING);

    /* Enable CAP1-CAP4 register loads */
    ICU_ECAP_captureLoadingEnable(baseAddr);
    if (interruptEnable != (uint32)0U)
    {
        uint16 cap = (uint16)capture;
        ICU_ECAP_intrEnable(baseAddr, cap);
    }
}

#if (STD_ON == ICU_TIMESTAMP_API)

void Icu_TimeStamp_Init(Icu_ChannelType Channel, Icu_ValueType *StartPtr, uint16 Size, uint16 NotifyInterval)
{
    Icu_ChObj[Channel].NextTimeStampIndexPtr = StartPtr;
    Icu_ChObj[Channel].TimeStampBufferSize   = Size;
    Icu_ChObj[Channel].NextTimeStampIndex    = 0U;
    Icu_ChObj[Channel].NotifyInterval        = NotifyInterval;
    Icu_ChObj[Channel].NotificationCounter   = 0U;
}

void Icu_TimeStamp_Clear(Icu_ChannelType Channel)
{
    Icu_ChObj[Channel].NextTimeStampIndexPtr = (Icu_ValueType *)NULL_PTR;
    Icu_ChObj[Channel].TimeStampBufferSize   = 0U;
    Icu_ChObj[Channel].NextTimeStampIndex    = 0U;
    Icu_ChObj[Channel].NotifyInterval        = 0U;
    Icu_ChObj[Channel].NotificationCounter   = 0U;
}

#endif /*ICU_TIMESTAMP_API*/

#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)

/*Reset Signal measurement runtime struct*/
void Icu_SignalMeasurement_Init(Icu_ChannelType Channel)
{
    Icu_ChObj[Channel].cap1                 = 0U;
    Icu_ChObj[Channel].cap2                 = 0U;
    Icu_ChObj[Channel].cap3                 = 0U;
    Icu_ChObj[Channel].cap4                 = 0U;
    Icu_ChObj[Channel].HighTime             = 0U;
    Icu_ChObj[Channel].LowTime              = 0U;
    Icu_ChObj[Channel].Period               = 0U;
    Icu_ChObj[Channel].DutyCycle.PeriodTime = 0U;
    Icu_ChObj[Channel].DutyCycle.ActiveTime = 0U;
    Icu_ChObj[Channel].DutyAcquired         = FALSE;
    Icu_ChObj[Channel].PeriodAcquired       = FALSE;
}

#endif

#if (STD_ON == ICU_DEV_ERROR_DETECT)
void Icu_reportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(ICU_MODULE_ID, ICU_INSTANCE_ID, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == ICU_DEV_ERROR_DETECT) */

void Icu_reportDetRuntimeError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportRuntimeError(ICU_MODULE_ID, ICU_INSTANCE_ID, apiId, errorId);
    return;
}

#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"

#define ICU_START_SEC_ISR_CODE
/*TI_INSPECTED 338 S : MISRAC_2012_D_20_1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Icu_MemMap.h"

#if (STD_ON == ICU_TIMESTAMP_API)

FUNC(void, ICU_CODE) Icu_Timestamp_ISR(Icu_ChannelType Channel)
{
    uint32 baseAddr;
    baseAddr = Icu_ChObj[Channel].baseAddr;

    /*BufferPtr null check*/
    if (Icu_ChObj[Channel].NextTimeStampIndexPtr != NULL_PTR)
    {
        ICU_Timestamp_ISRProcess(Channel);
    }

    /* Enable all global interrupts*/
    ICU_ECAP_globalIntrClear(baseAddr);

    Icu_ChObj[Channel].NextTimeStampIndex++;

    /*Handling for end of buffer*/
    if ((Icu_ChObj[Channel].NextTimeStampIndex >= Icu_ChObj[Channel].TimeStampBufferSize) &&
        (Icu_ChObj[Channel].NextTimeStampIndexPtr != NULL_PTR))
    {
        switch (Icu_ChObj[Channel].chCfg.bufferType)
        {
            case ICU_LINEAR_BUFFER:
                /*Stop capturing values and disable interrupts */

                /*Stop capturing timestamps, but take the NextTimeStampIndex value*/

                ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
                Icu_ChObj[Channel].IsRunning = FALSE;
                break;
            case ICU_CIRCULAR_BUFFER:
                /*Next timestamp writes over the first item, and continous capturing timestamps. */
                Icu_ChObj[Channel].NextTimeStampIndex = 0;
                break;
            default:
                break;
        }
    }

    return;
}
#endif

#if (STD_ON == ICU_TIMESTAMP_API)
static FUNC(void, ICU_CODE) ICU_Timestamp_ISRProcess(Icu_ChannelType Channel)
{
    uint32 baseAddr;
    baseAddr = Icu_ChObj[Channel].baseAddr;
    uint32 timestampRead;
    uint32 avoidNesting_Flag = E_NOT_OK;

    /*Check which capregister called the interrupt*/
    if (ICU_ECAP_getIntrStatus(baseAddr, ECAP_CEVT1_INT) != 0U)
    {
        /*interrupt occured at CAP1, get the current timestamp from CAP1*/
        timestampRead = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_1);
        Icu_ChObj[Channel].NextTimeStampIndexPtr[Icu_ChObj[Channel].NextTimeStampIndex] = (uint16)timestampRead;
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_CEVT1_INT);
        avoidNesting_Flag = E_OK;
    }
    if ((ICU_ECAP_getIntrStatus(baseAddr, ECAP_CEVT2_INT) != 0U) && (avoidNesting_Flag != (uint32)E_OK))
    {
        /*interrupt occured at CAP1, get the current timestamp from CAP1*/
        timestampRead = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_2);
        Icu_ChObj[Channel].NextTimeStampIndexPtr[Icu_ChObj[Channel].NextTimeStampIndex] = (uint16)timestampRead;
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_CEVT2_INT);
        avoidNesting_Flag = E_OK;
    }
    if ((ICU_ECAP_getIntrStatus(baseAddr, ECAP_CEVT3_INT) != 0U) && (avoidNesting_Flag != (uint32)E_OK))
    {
        /*interrupt occured at CAP1, get the current timestamp from CAP1*/
        timestampRead = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_3);
        Icu_ChObj[Channel].NextTimeStampIndexPtr[Icu_ChObj[Channel].NextTimeStampIndex] = (uint16)timestampRead;
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_CEVT3_INT);
        avoidNesting_Flag = E_OK;
    }
    if ((ICU_ECAP_getIntrStatus(baseAddr, ECAP_CEVT4_INT) != 0U) && (avoidNesting_Flag != (uint32)E_OK))
    {
        /*interrupt occured at CAP1, get the current timestamp from CAP1*/
        timestampRead = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_4);
        Icu_ChObj[Channel].NextTimeStampIndexPtr[Icu_ChObj[Channel].NextTimeStampIndex] = (uint16)timestampRead;
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_CEVT4_INT);
        avoidNesting_Flag = E_OK;
    }
    else
    {
        /* no other values possible*/
    }
}
#endif
/*******************************************************************************
 *   Function Name : Icu_ChannelISR
 ******************************************************************************/
/*! \Description: Interrupt Subroutine for Notification
 *
 *  \context    Function is called from interrupt level
 ******************************************************************************/
FUNC(void, ICU_CODE) Icu_ChannelISR(Icu_ChannelType Channel)
{
#if (STD_ON == ICU_TIMESTAMP_API)
    if (Icu_ChObj[Channel].chCfg.measurementMode == ICU_MODE_TIMESTAMP)
    {
        Icu_Timestamp_ISR(Channel);

        if ((++Icu_ChObj[Channel].NotificationCounter >= Icu_ChObj[Channel].NotifyInterval) &&
            (Icu_ChObj[Channel].NotificationEnabled != (uint32)0U))
        {
            /* Call configured notification function if defined */
            if (Icu_ChObj[Channel].chCfg.notificationHandler != NULL_PTR)
            {
                Icu_ChObj[Channel].chCfg.notificationHandler();
            }
        }
    }
#endif
#if (STD_ON == ICU_EDGE_COUNT_API)
    if (Icu_ChObj[Channel].chCfg.measurementMode == ICU_MODE_EDGE_COUNTER)
    {
        uint32 baseAddr;
        baseAddr = Icu_ChObj[Channel].baseAddr;

        Icu_ChObj[Channel].InputState = ICU_ACTIVE;
        Icu_ChObj[Channel].EdgeCounter++;

        /* Enable all global interrupts*/
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);
        ICU_ECAP_globalIntrClear(baseAddr);
    }
#endif
#if (STD_ON == ICU_EDGE_DETECT_API)
    if (Icu_ChObj[Channel].chCfg.measurementMode == ICU_MODE_SIGNAL_EDGE_DETECT)
    {
        uint32 baseAddr;
        baseAddr = Icu_ChObj[Channel].baseAddr;

        Icu_ChObj[Channel].InputState = ICU_ACTIVE;
        if ((Icu_ChObj[Channel].NotificationEnabled == TRUE) &&
            (Icu_ChObj[Channel].chCfg.notificationHandler != NULL_PTR))
        {
            Icu_ChObj[Channel].chCfg.notificationHandler();

            /* Enable all global interrupts*/
            ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);
            ICU_ECAP_globalIntrClear(baseAddr);
        }
        else
        {
            /*MISRA*/
        }
    }
#endif
}

#if (STD_ON == ICU_REGISTER_READBACK_API)
void Icu_HwRegisterReadback(Icu_ChannelType Channel, Icu_RegisterReadbackType *RegRbPtr)
{
    uint32         baseAddr;
    Icu_ChObjType *chObj = &Icu_ChObj[Channel];
    (void)memset(RegRbPtr, 0, sizeof(Icu_RegisterReadbackType));
    baseAddr = chObj->baseAddr;
    Icu_RegisterReadback_Ecap(baseAddr, RegRbPtr);
}
#endif

#if (STD_ON == ICU_REGISTER_READBACK_API)
void Icu_RegisterReadback_Ecap(uint32 baseAddr, Icu_RegisterReadbackType *RegRbPtr)
{
    RegRbPtr->TSCTR  = HW_RD_REG32(baseAddr + CSL_ECAP_TSCTR);
    RegRbPtr->CTRPHS = HW_RD_REG32(baseAddr + CSL_ECAP_CTRPHS);
    RegRbPtr->CAP1   = HW_RD_REG32(baseAddr + CSL_ECAP_CAP1);
    RegRbPtr->CAP2   = HW_RD_REG32(baseAddr + CSL_ECAP_CAP2);
    RegRbPtr->CAP3   = HW_RD_REG32(baseAddr + CSL_ECAP_CAP3);
    RegRbPtr->CAP4   = HW_RD_REG32(baseAddr + CSL_ECAP_CAP4);
}
#endif
#define ICU_STOP_SEC_ISR_CODE
#include "Icu_MemMap.h"
