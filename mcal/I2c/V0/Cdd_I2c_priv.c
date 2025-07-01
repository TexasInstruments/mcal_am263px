/*
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free,
 * non-exclusive license under copyrights and patents it now or hereafter owns or
 * controls to make, have made, use, import, offer to sell and sell ("Utilize")
 * this software subject to the terms herein.With respect to the foregoing patent
 * license, such license is granted solely to the extent that any such patent is
 * necessary to Utilize the software alone. The patent license shall not apply to
 * any combinations which include this software, other than combinations with
 * devices manufactured by or for TI ("TI Devices"). No hardware patent is
 * licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this
 * license (including the above copyright notice and the disclaimer and
 * (if applicable) source code license limitations below) in the documentation
 * and/or other materials provided with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted
 * provided that the following conditions are met:
 *
 * *  No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * * any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution
 * of the source code are permitted provided that the following conditions are
 * met:
 *
 * * any redistribution and use of the source code, including any resulting
 * derivative works, are licensed by TI for use only with TI Devices.
 *
 * * any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI
 * Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its
 * suppliers
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
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED  OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Cdd_I2c_priv.c
 *
 *  \brief    This file contains the internal function implementations of the CDD I2C driver
 *
 *
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#include "Cdd_I2c.h"
#include "Cdd_I2c_Cfg.h"
#include "Cdd_I2c_priv.h"
#include "Cdd_I2c_hw_reg.h"
#include "hw_types.h"
#include "Os.h"

/* ================================================================ */
/*                      Function Declarations                       */
/* ================================================================ */

#if (STD_OFF == CDD_I2C_POLLING_MODE)
static Std_ReturnType Cdd_I2c_Isr_Handler_check_sequenceIDchannelID(uint8 HwUnit, uint8 *ChannelId, uint8 *SequenceId);
static Std_ReturnType Cdd_I2c_Isr_Handlersequencecheck(uint8 HwUnit, uint8 *pDataReceiveBuffer,
                                                       uint32 *pDataReceiveBufferIndex, uint32 IsrStatus);
static void Cdd_I2c_Isr_Handlersequencecheck_channelread(uint8 ChannelId, uint8 SequenceId, uint8 *pDataReceiveBuffer,
                                                         uint32 *pDataReceiveBufferIndex);
static void Cdd_I2c_Isr_Handlersequencecheck_lastchannel(uint8 ChannelId, uint8 SequenceId);
static Std_ReturnType Cdd_I2c_Isr_Handler_checkerrors(uint8 HwUnit);
static void Cdd_I2c_Isr_Handler_datashift(uint8 HwUnit, uint8 *pDataReceiveBuffer, uint32 *pDataReceiveBufferIndex,
                                          uint16 *pDataBufferLength);
static Std_ReturnType Cdd_I2c_Isr_Handler_datawrite(uint8 HwUnit);
static void           Cdd_I2c_Isr_Handler_channelUpdate(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId);
#endif /* (STD_OFF == CDD_I2C_POLLING_MODE) */

#if (STD_ON == CDD_I2C_POLLING_MODE)
static void Cdd_I2c_Polling_Mode_Receive_BusBusyCheck(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId, uint32 Timeout);
static void Cdd_I2c_Polling_Mode_Receive_ReadStatusRegister(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId);
static void Cdd_I2c_PollingModeProcessingFromQueue_channelupdate(uint8 SequenceId);
#endif /* (STD_ON == CDD_I2C_POLLING_MODE) */

/* ================================================================ */
/*                          Global variables                        */
/* ================================================================ */

#define CDD_I2C_START_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"
static uint8 QueueCounter = 0;
#define CDD_I2C_STOP_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"

#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"

/* ================================================================ */
/*                          Function Definitions                    */
/* ================================================================ */

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
void Cdd_I2cReportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, apiId, errorId);
    return;
}
#endif

uint8 Cdd_I2c_Timeout(uint32 TimeoutPrevious, uint32 TimeoutPeriod)
{
    uint32 TimeoutPresent = 0;
    uint8  status         = 0;
    /*Get current time ticks value*/
    (void)GetCounterValue(CDD_I2C_OS_COUNTER_ID, &TimeoutPresent);
    if ((TimeoutPresent - TimeoutPrevious) >= TimeoutPeriod)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

void Cdd_I2c_Setup_HW_Unit_Clk(uint8 HwInstance, uint32 BaudRate, uint32 Cdd_I2cHwUnitFrequency, uint32 SysClk)
{
    uint8  PreScalerI2cModule = 0;
    uint16 VariableDifference = 0;
    uint16 Divisor            = 0;
    uint32 InternalClk;
    uint32 OutputClk;

    /* Determine internal clock frequency and output clock based on BaudRate */
    switch (BaudRate)
    {
        case 100000u:
            InternalClk = 4000000u;
            OutputClk   = 100000u;
            break;
        case 400000u:
            InternalClk = 8000000u;
            OutputClk   = 400000u;
            break;
        default:
            InternalClk = 4000000u;
            OutputClk   = 100000u;
            break;
    }

    /* Calculate prescaler */
    PreScalerI2cModule = (uint8)((SysClk / InternalClk) - 1u);
    HW_WR_REG8((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICPSC), PreScalerI2cModule);

    /* Determine VariableDifference based on prescaler */
    if (PreScalerI2cModule == 0u)
    {
        VariableDifference = 7u;
    }
    else if (PreScalerI2cModule == 1u)
    {
        VariableDifference = 6u;
    }
    else
    {
        VariableDifference = 5u;
    }

    /* Calculate divisor */
    Divisor = InternalClk / OutputClk;
    if (Divisor % 2u == 0u)
    {
        Divisor = Divisor / 2u;
        HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICCLKL), (Divisor - VariableDifference));
        HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICCLKH), (Divisor - VariableDifference));
    }
    else
    {
        HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICCLKL), ((Divisor / 2u) - VariableDifference));
        HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICCLKH), ((Divisor / 2u) - VariableDifference) + 1u);
    }
}

void Cdd_I2c_Set_Own_Address(uint8 HwInstance, uint16 address)
{
    /**
     * Writes address passed as parameter to the register,
     * Will add check to see if address is 10 bit or 7 bit
     * When driver supports SOC to function as slave
     */
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICOAR), address);
}

void Cdd_I2c_Clear_interrupts(uint8 HwInstance, uint16 InterruptMask)
{
    /**
     * Writes mask value to clear any
     * existing interrupts to the register
     */
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICSTR), InterruptMask);
}

void Cdd_I2c_Disable_interrupts(uint8 HwInstance, uint16 InterruptMask)
{
    /**
     * Writes mask value to disable all I2C
     * related interrupts to the register
     */
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), InterruptMask);
}

void Cdd_I2c_Enable_master(uint8 HwInstance)
{
    /**
     * Writes mask value to set SOC in master mode, free run
     * and bring I2c out of reset
     */
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR),
                (CDD_I2C_MASTER_MODE | CDD_I2C_FREE_RUN | CDD_I2C_OUT_OF_RESET));
}

void Cdd_I2c_queue_init(Cdd_I2c_Queue_obj *pQueue)
{
    /**
     * Function initialises
     * sequenceId = 255
     * pNext = NULL
     * for all queue locations
     */
    uint8 i = 0;

    for (i = 0; i < CDD_I2C_MAX_QUEUE_SIZE; i++)
    {
        (pQueue + i)->sequenceId = 255;
        (pQueue + i)->pNext      = (struct Cdd_I2c_Queue_obj_ *)NULL_PTR;
    }
}

void Cdd_I2c_Disable_master(uint8 HwInstance)
{
    /**
     * Puts I2c in reset mode
     */
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR), ~(CDD_I2C_OUT_OF_RESET));
}

void Cdd_I2c_Set_Slave_Addressing_mode(uint8 HwInstance, uint8 SlaveAddressScheme)
{
    uint16 regVal = 0;
    /**
     * Writes the give SlaveAddressScheme either 0 or 1 to the
     * MDR registers XA bit
     */
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICMDR_XA, SlaveAddressScheme);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR), regVal);
}

void Cdd_I2c_Set_Slave_Address(uint8 HwInstance, Cdd_I2c_AddressType SlaveAddress)
{
    /**
     * Writes the given 16 bit slave device address in the register
     */
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICSAR), SlaveAddress);
}

void Cdd_I2c_Enable_interrupts(uint8 HwInstance)
{
    uint16 regVal = 0;

    /**
     * All configurator selected interrupts will be enabled here
     * All bits in the IMR register will be manipulated
     */

#if (STD_ON == CDD_I2C_ARBITRATION_LOSS)
    /*Enable arbitration loss interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_AL, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#elif (STD_OFF == CDD_I2C_ARBITRATION_LOSS)
    /*Disable arbitration loss interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_AL, 0);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#endif

#if (STD_ON == CDD_I2C_TREAT_NACK_AS_ERROR)
    /*Enable NACK interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_NACK, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#elif (STD_OFF == CDD_I2C_TREAT_NACK_AS_ERROR)
    /*Disable NACK interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_NACK, 0);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#endif

    /*Disable Register access ready interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ARDY, 0);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);

#if (STD_ON == CDD_I2C_POLLING_MODE)
    /*Disable Receive data ready interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICRRDY, 0);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#elif (STD_OFF == CDD_I2C_POLLING_MODE)
    /*Enable Receive data ready interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICRRDY, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#endif

#if (STD_ON == CDD_I2C_POLLING_MODE)
    /*Disable Transmit Data ready interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICXRDY, 0);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#elif (STD_OFF == CDD_I2C_POLLING_MODE)
    /*Enable Transmit Data ready interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICXRDY, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
#endif

    /*Enable stop condition interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_SCD, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);

    /*Disable Address as Slave interrupt*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_AAS, 0);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICIMR), regVal);
}

void Cdd_I2c_Set_Master_Receive_Mode(uint8 HwInstance)
{
    uint16 regVal = 0;

    /**
     * Set Master in receive mode
     */
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICMDR_TRX, 0);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR), regVal);
}

void Cdd_I2c_Set_Master_Transmit_Mode(uint8 HwInstance)
{
    uint16 regVal = 0;

    /**
     * Set Master in transmit mode
     */
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICMDR_TRX, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR), regVal);
}

void Cdd_I2c_Data_Count(uint8 HwInstance, uint16 DataLength)
{
    /**
     * Function call writes a 16 bit value to the register
     * Post completion of speified 2 byte data tranmssion/reception
     * stop signal is generated
     */
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICCNT), DataLength);
}

void Cdd_I2c_Start(uint8 HwInstance)
{
    uint16 regVal = 0;

    /*Set device back in master mode*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICMDR_MST, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR), regVal);
    /*Generate start condition*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICMDR_STT, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR), regVal);
}

uint16 Cdd_I2c_Isr_Check(uint8 HwInstance)
{
    volatile uint16 regVal = 0;
    /**
     * Read status register
     */
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICSTR);
    return regVal;
}

uint8 Cdd_I2c_Get_Sequence_Id(uint8 HwUnit)
{
    uint8 i      = 0;
    uint8 retVal = SEQUENCE_INITIALIZER;

    for (i = 0; i < CDD_I2C_MAXIMUM_SEQUENCE_NUMBER; i++)
    {
        if ((HwUnit == Cdd_I2cSequenceContainerLocal[i].HwInstance) &&
            (CDD_I2C_SEQ_PENDING == Cdd_I2cSequenceContainerLocal[i].SeqResult))
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

uint8 Cdd_I2c_Get_Channel_Id(uint8 HwUnit, uint8 SequenceId)
{
    uint8 i         = 0;
    uint8 ChannelId = 0;
    uint8 retVal    = CHANNEL_INITIALIZER;

    for (i = 0; ((i < Cdd_I2cSequenceContainerLocal[SequenceId].MaxChannels) && (i < CDD_I2C_MAXIMUM_CHANNEL_NUMBER));
         i++)
    {
        ChannelId = Cdd_I2cSequenceContainerLocal[SequenceId].ChannelList[i];
        if (CDD_I2C_CH_RESULT_IN_PROGRESS == Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult)
        {
            retVal = ChannelId;
        }
    }
    return retVal;
}

uint8 Cdd_I2c_Arbitration_Loss(uint8 ChannelId)
{
    Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_ARBFAIL;
    return (CDD_I2C_E_ARBITRATION_LOSS);
}

uint8 Cdd_I2c_No_Ack(uint8 ChannelId)
{
    Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_NACKFAIL;
    return (CDD_I2C_E_NACK);
}

uint8 Cdd_I2c_Shift_Register_Full(uint8 ChannelId)
{
    Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_BUSFAIL;
    return (CDD_I2C_E_RECEIVE_SHIFT_REGISTER_FULL);
}

void Cdd_I2c_Stop(uint8 HwInstance)
{
    uint16 regVal = 0;

    /*Generate stop condition*/
    regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR);
    HW_SET_FIELD16(regVal, CDD_I2C_ICMDR_STP, 1);
    HW_WR_REG16((CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICMDR), regVal);
}

void Cdd_I2c_Enqueue(uint8 sequenceId)
{
    if (QueueCounter < CDD_I2C_MAX_QUEUE_SIZE)
    {
#if (STD_OFF == CDD_I2C_PROCESS_SAME_SEQUENCE_MULTIPLE_TIMES_IN_QUEUE)
        if (CDD_I2C_SEQ_QUEUED != Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
#endif
        {
            if (QueueCounter > 0U)
            {
                (pCddI2cTransmissionQueue + QueueCounter)->sequenceId   = sequenceId;
                (pCddI2cTransmissionQueue + (QueueCounter - 1U))->pNext = (pCddI2cTransmissionQueue + QueueCounter);
                (pCddI2cTransmissionQueue + QueueCounter)->pNext        = (struct Cdd_I2c_Queue_obj_ *)NULL_PTR;
            }
            if (QueueCounter == 0U)
            {
                (pCddI2cTransmissionQueue + QueueCounter)->sequenceId = sequenceId;
                (pCddI2cTransmissionQueue + QueueCounter)->pNext      = (struct Cdd_I2c_Queue_obj_ *)NULL_PTR;
            }
            else
            {
                /*Do Nothing*/
            }
            QueueCounter++;
            Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_QUEUED;
        }
    }
    else
    {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify(CDD_I2C_E_PARAM_QUEUE_FULL);
/*Queue full error*/
#endif
#if (STD_OFF == CDD_I2C_PROCESS_SAME_SEQUENCE_MULTIPLE_TIMES_IN_QUEUE)
        if (CDD_I2C_SEQ_QUEUED != Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
#endif
        {
            QueueCounter                                          = 0;
            (pCddI2cTransmissionQueue + QueueCounter)->sequenceId = sequenceId;
            (pCddI2cTransmissionQueue + QueueCounter)->pNext      = (struct Cdd_I2c_Queue_obj_ *)NULL_PTR;
            QueueCounter++;
            Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_QUEUED;
        }
    }
}

uint8 Cdd_I2c_Read(uint8 HwInstance)
{
    /*Read data received from the I2C bus*/
    return (HW_RD_REG16(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICDRR));
}

void Cdd_I2c_Write(uint8 HwInstance, uint8 Data)
{
    /*Write data passed to the register*/
    HW_WR_REG8(CddI2cHwUnitBaseAddr[HwInstance] + CDD_I2C_ICDXR, Data);
}

#if (STD_ON == CDD_I2C_POLLING_MODE) /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/
void Cdd_I2c_Polling_Mode_Receive(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId)
{
    uint32 Timeout = 0;
    /*Disable global interrupts*/
    SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
    /*Function call to disable all interrupts*/
    Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
    /*Function call to clear all interrupts*/
    Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
    /*Function call to set the master in receive mode*/
    Cdd_I2c_Set_Master_Receive_Mode(HwUnit);
    /*Function call to set number of bytes to read/write*/
    Cdd_I2c_Data_Count(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength);
    Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_IN_PROGRESS;
    /*Get initial value for timeout period*/
    (void)GetCounterValue(CDD_I2C_OS_COUNTER_ID, &Timeout);
    /*Wait till bus is free in case of restart mode stop, as bus is released at the end of each channel in this mode*/
    if (CDD_I2C_RESTART_MODE_STOP == Cdd_I2cSequenceContainerLocal[SequenceId].RestartMode)
    {
        Cdd_I2c_Polling_Mode_Receive_BusBusyCheck(HwUnit, ChannelId, SequenceId, Timeout);
    }

    Timeout = 0;
    if (CDD_I2C_SEQ_FAILED != Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult)
    {
        /*Send start signal on the bus*/
        Cdd_I2c_Start(HwUnit);
        /*Poll and read buffer when ready*/
        Cdd_I2c_Polling_Mode_Receive_ReadStatusRegister(HwUnit, ChannelId, SequenceId);
        /*Stop in case of restart mode as CDD_I2C_RESTART_MODE_STOP*/
        if (CDD_I2C_RESTART_MODE_STOP == Cdd_I2cSequenceContainerLocal[SequenceId].RestartMode)
        {
            Cdd_I2c_Stop(HwUnit);
        }

        // If last channel of sequence, do a hard stop
        if (ChannelId == Cdd_I2cSequenceContainerLocal[SequenceId]
                             .ChannelList[Cdd_I2cSequenceContainerLocal[SequenceId].MaxChannels - 1u] &&
            (CDD_I2C_SEQ_PENDING == Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult))
        {
            /*Check if sequence complete notify function is not passed as NULL*/
            if (NULL_PTR != Cdd_I2cSequenceContainer[SequenceId].SequenceCompleteNotify)
            {
                /*Execute sequence complete notify callback function*/
                Cdd_I2cSequenceContainer[SequenceId].SequenceCompleteNotify();
            }
            else
            {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
                /*Sequence complete notify callback function passed an NULL*/
                Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
#endif
            }
            /*If restart mode is restart, then stop, else stop is done above for stop-start slave transmission mode*/
            if (CDD_I2C_RESTART_MODE_STOP != Cdd_I2cSequenceContainerLocal[SequenceId].RestartMode)
            {
                /*Stop at the end of sequence if restart mode is no-stop*/
                Cdd_I2c_Stop(HwUnit);
            }
            /*Mark the sequence as OK and free the hardware instance*/
            Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult                      = CDD_I2C_SEQ_OK;
            CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance] = CDD_I2C_HW_UNIT_FREE;
        }

        /*Function call to disable local interrupts*/
        Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
        /*Function call to clear all I2C related interrupts*/
        Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
        /*Function call to enable configurator selected interrupts*/
        Cdd_I2c_Enable_interrupts(HwUnit);
        /*Enable global interrupts*/
        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
    }

    Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult    = CDD_I2C_CH_RESULT_OK;
    Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength = Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
    Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer       = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
    CddI2cDrvState                                           = CDD_I2C_IDLE;
}

static void Cdd_I2c_Polling_Mode_Receive_BusBusyCheck(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId, uint32 Timeout)
{
    TickType Timeout_local = Timeout;
    while (CDD_I2C_BUS_BUSY == Cdd_I2cBusCheck(HwUnit))
    {
        /*Get elapsed time value*/
        if (1U == (Cdd_I2c_Timeout(Timeout_local, CDD_I2C_RESET_TIMEOUT)))
        {
            /*Call Cdd_I2c_SetHandling if bus is busy for more than specified time period*/
            Cdd_I2c_SetHandling(CddI2cArbitrationLossParam);
            Timeout_local                                         = 0;
            Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_BUSFAIL;
            Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult   = CDD_I2C_SEQ_FAILED;
            break;
        }
    }
}

static void Cdd_I2c_Polling_Mode_Receive_ReadStatusRegister(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId)
{
    uint32 IsrStatus = 0;
    while (0U != Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength)
    {
        /*Read status register*/
        IsrStatus = Cdd_I2c_Isr_Check(HwUnit);
        if ((IsrStatus & (CDD_I2C_ICSTR_AL_MASK | CDD_I2C_ICSTR_NACK_MASK | CDD_I2C_ICSTR_AD0_MASK |
                          CDD_I2C_ICSTR_RSFULL_MASK)) != 0U)
        {
            /*Function call to disable all interrupts*/
            Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
            /*Function call to send a stop signal on the I2C bus*/
            Cdd_I2c_Stop(HwUnit);
            if (NULL_PTR != Cdd_I2cSequenceContainer[SequenceId].SequenceErrorNotify)
            {
                Cdd_I2cSequenceContainer[SequenceId].SequenceErrorNotify(
                    Cdd_I2c_Error_Handler(IsrStatus, ChannelId, HwUnit));
            }
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
            else
            {
                Cdd_I2cReportDetError(CDD_I2C_SID_POLLING_MODE_PROCESSING, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
                /*Sequence error notify callback function passed as NULL_PTR*/
            }
#endif
            /*Function call to clear all interrupts*/
            Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
            Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
            Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength =
                Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
            Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
            break;
        }
        else if ((IsrStatus & CDD_I2C_ICSTR_ICRRDY_MASK) != 0U)
        {
            *(Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer) = Cdd_I2c_Read(HwUnit);
            Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer++;
            Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength--;
        }
        else
        {
            /*Do Nothing*/
        }
    }
}

#endif /*#if(STD_ON == CDD_I2C_POLLING_MODE)*/

uint8 Cdd_I2cBusCheck(uint8 HwInstance)
{
    uint16 status = 0;
    uint8  retVal = 0;

    status = Cdd_I2c_Isr_Check(HwInstance);
    if (0u != (status & CDD_I2C_ICSTR_BB_MASK))
    {
        retVal = CDD_I2C_BUS_BUSY;
    }
    if (0u == (status & CDD_I2C_ICSTR_BB_MASK))
    {
        retVal = CDD_I2C_BUS_FREE;
    }
    else
    {
        /*Do Nothing*/
    }
    return retVal;
}

uint8 Cdd_I2c_Error_Specify(uint32 ErrStatus, uint8 ChannelId)
{
    uint8 ErrorStatus = 0;

    /*Checking for Arbitration loss error*/
    if ((ErrStatus & CDD_I2C_ICSTR_AL_MASK) != (uint32)0U)
    {
        ErrorStatus = Cdd_I2c_Arbitration_Loss(ChannelId);
    }
    /*Checking for No acknowledgement error*/
    else if ((ErrStatus & CDD_I2C_ICSTR_NACK_MASK) != (uint32)0U)
    {
        ErrorStatus = Cdd_I2c_No_Ack(ChannelId);
    }
    else if ((ErrStatus & CDD_I2C_ICSTR_RSFULL_MASK) != (uint32)0U)
    {
        ErrorStatus = Cdd_I2c_Shift_Register_Full(ChannelId);
    }
    else
    {
        /*Do Nothing*/
    }
    return (ErrorStatus);
}

uint8 Cdd_I2c_Error_Handler(uint32 ErrStatus, uint8 ChannelId, uint8 HwUnit)
{
    uint8 ErrorStatus = 0;

    /*Check for all specific errors and update channel as well as sequence results*/
    ErrorStatus = Cdd_I2c_Error_Specify(ErrStatus, ChannelId);
    /*Function call to disable all interrupts*/
    Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
    /*Function call to send a stop signal on the I2C bus*/
    Cdd_I2c_Stop(HwUnit);
    /*Function call to clear all interrupts*/
    Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);

    return (ErrorStatus);
}

#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_HWRegisterReadback(uint8 HwInstance, P2VAR(Cdd_I2c_RegisterReadbackType, AUTOMATIC, CDDI2C_APPL_DATA) RegRbPtr)
{
    uint32 hwUnitObj;
    uint8  retVal = CDD_I2C_OK;

    (void)memset(RegRbPtr, 0, sizeof(Cdd_I2c_RegisterReadbackType));

    /* HW unit ID may not be the index, so search for matching HW unit */
    hwUnitObj = Cdd_I2c_getHwUnitObj(HwInstance);
    if (hwUnitObj != 0U)
    {
        Cdd_I2cRegReadback(hwUnitObj, RegRbPtr);
    }
    else
    {
        retVal = CDD_I2C_NOT_OK;
    }

    return (retVal);
}

/**
 *  \brief Returns the the HW object for the corresponding HW unit ID
 */
uint32 Cdd_I2c_getHwUnitObj(uint8 HwInstance)
{
    uint32 hwUnitIdx      = 0U;
    uint32 hwUnitCfgFound = (uint32)FALSE;
    uint32 hwUnitObj;

    /* HW unit ID may not be the index, so search
     * for matching HW unit */
    for (hwUnitIdx = 0U; hwUnitIdx < CDD_I2C_HW_UNITS_MAX; hwUnitIdx++)
    {
        if (Cdd_I2cSequenceContainerLocal[hwUnitIdx].HwInstance == HwInstance)
        {
            hwUnitCfgFound = (uint32)TRUE;
            break; /* Match found */
        }
    }

    if (hwUnitCfgFound != ((uint32)TRUE))
    {
        hwUnitObj = NULL;
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        Cdd_I2cReportDetError(CDD_I2C_SID_REGISTERREADBACK, CDD_I2C_E_PARAM_CONFIG);
#endif
    }
    else
    {
        hwUnitObj = CddI2cHwUnitBaseAddr[HwInstance];
    }

    return hwUnitObj;
}

void Cdd_I2cRegReadback(const uint32 baseaddress, Cdd_I2c_RegisterReadbackType *RegRbPtr)
{
    RegRbPtr->prescalarreg      = HW_RD_REG32(baseaddress + CDD_I2C_ICPSC);
    RegRbPtr->clkdividerlowreg  = HW_RD_REG32(baseaddress + CDD_I2C_ICCLKL);
    RegRbPtr->clkdividerhighreg = HW_RD_REG32(baseaddress + CDD_I2C_ICCLKH);
    RegRbPtr->modereg           = HW_RD_REG32(baseaddress + CDD_I2C_ICMDR);
    RegRbPtr->ownaddrreg        = HW_RD_REG32(baseaddress + CDD_I2C_ICOAR);
    return;
}
#endif /* #if (STD_ON == CDD_I2C_REGISTER_READBACK_API) */

#if (STD_ON == CDD_I2C_POLLING_MODE)
void Cdd_I2c_PollingModeProcessingFromQueue(uint8 SequenceId)
{
    if ((CDD_I2C_SEQ_FAILED != Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult) &&
        (CDD_I2C_HW_UNIT_BUSY != CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance]))
    {
        CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance] = CDD_I2C_HW_UNIT_BUSY;
        Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult                      = CDD_I2C_SEQ_PENDING;

        Cdd_I2c_PollingModeProcessingFromQueue_channelupdate(SequenceId);

        CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance] = CDD_I2C_HW_UNIT_FREE;
        if (CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult)
        {
            Cdd_I2c_Enqueue(SequenceId);
        }
    }
}

static void Cdd_I2c_PollingModeProcessingFromQueue_channelupdate(uint8 SequenceId)
{
    uint8  i            = 0;
    uint8  ChannelId    = 0;
    uint16 SlaveAddress = 0;
    uint8  HwUnit       = 0;

    for (i = 0; i < Cdd_I2cSequenceContainerLocal[SequenceId].MaxChannels; i++)
    {
        /*Find the channel ID number*/
        ChannelId = Cdd_I2cSequenceContainerLocal[SequenceId].ChannelList[i];
        if (CDD_I2C_READ == Cdd_I2cChannelContainerLocal[ChannelId].Dir)
        {
            if (CDD_I2C_CH_RESULT_IN_PROGRESS == Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult)
            {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
                Cdd_I2cSequenceContainer[SequenceId].SequenceErrorNotify(CDD_I2C_E_CHANNEL_BUSY);
/*Channel busy*/
#endif
                Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
                break;
            }
            /*Update channel result*/
            Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_IN_PROGRESS;
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
            if (NULL_PTR == Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer)
            {
                Cdd_I2cReportDetError(CDD_I2C_SID_POLLING_MODE_PROCESSING, CDD_I2C_E_PARAM_TRANS_BUFFER);
                /*Reception function called before setupEB*/
            }
#endif
            /*Find the Slave address*/
            SlaveAddress = Cdd_I2cChannelContainerLocal[ChannelId].SlaveAddress;
            /*Find HwUnit*/
            HwUnit = Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance;
            /*Function call to set the addressing mode for the slave device*/
            Cdd_I2c_Set_Slave_Addressing_mode(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId].SlaveAddressScheme);
            /*Function call to set the slave address when device in master mode*/
            Cdd_I2c_Set_Slave_Address(HwUnit, SlaveAddress);
            Cdd_I2c_Polling_Mode_Receive(HwUnit, ChannelId, SequenceId);
        }
    }
}

#endif

#if (STD_OFF == CDD_I2C_POLLING_MODE)
void Cdd_I2c_Isr_Handler(uint8 HwUnit, uint8 *pDataReceiveBuffer, uint32 *pDataReceiveBufferIndex,
                         uint16 *pDataBufferLength)
{
    uint8  status    = CDD_I2C_OK;
    uint32 IsrStatus = 0;

    /*Function call to check ISR status register*/
    IsrStatus = Cdd_I2c_Isr_Check(HwUnit);

    status = Cdd_I2c_Isr_Handlersequencecheck(HwUnit, pDataReceiveBuffer, pDataReceiveBufferIndex, IsrStatus);

    /*Check for errors on the bus*/
    if ((((IsrStatus) & (CDD_I2C_ICSTR_AL_MASK | CDD_I2C_ICSTR_NACK_MASK | CDD_I2C_ICSTR_AD0_MASK |
                         CDD_I2C_ICSTR_RSFULL_MASK)) != (uint32)0U) &&
        (status == CDD_I2C_OK))
    {
        status = Cdd_I2c_Isr_Handler_checkerrors(HwUnit);
    }
    /*Check if data has been copied from the bus into the receive shift register*/
    else if (((IsrStatus & CDD_I2C_ICSTR_ICRRDY_MASK) != (uint32)0U) && (status == CDD_I2C_OK))
    {
        Cdd_I2c_Isr_Handler_datashift(HwUnit, pDataReceiveBuffer, pDataReceiveBufferIndex, pDataBufferLength);
    }
    /*Check if data has been written on the bus*/
    else if (((IsrStatus & CDD_I2C_ICSTR_ICXRDY_MASK) != (uint32)0U) && (status == CDD_I2C_OK))
    {
        status = Cdd_I2c_Isr_Handler_datawrite(HwUnit);
    }
    else
    {
        /*Do Nothing*/
    }
    return;
}

static Std_ReturnType Cdd_I2c_Isr_Handler_check_sequenceIDchannelID(uint8 HwUnit, uint8 *ChannelId, uint8 *SequenceId)
{
    uint8 status = CDD_I2C_OK;

    /*Function call to find sequence ID*/
    *SequenceId = Cdd_I2c_Get_Sequence_Id(HwUnit);
    if (CDD_I2C_MAXIMUM_SEQUENCE_NUMBER > *SequenceId)
    {
        /*Function call to find channel ID*/
        *ChannelId = Cdd_I2c_Get_Channel_Id(HwUnit, *SequenceId);
        status     = CDD_I2C_OK;
    }
    else
    {
        status = CDD_I2C_NOT_OK;
    }
    return status;
}

static Std_ReturnType Cdd_I2c_Isr_Handlersequencecheck(uint8 HwUnit, uint8 *pDataReceiveBuffer,
                                                       uint32 *pDataReceiveBufferIndex, uint32 IsrStatus)
{
    uint8  status     = CDD_I2C_OK;
    uint16 regVal     = 0;
    uint8  ChannelId  = 0;
    uint8  SequenceId = 0;

    /*Check if a stop condition is detected*/
    if ((IsrStatus & CDD_I2C_ICSTR_SCD_MASK) != (uint32)0U)
    {
        /*Function call to find sequence ID*/
        status = Cdd_I2c_Isr_Handler_check_sequenceIDchannelID(HwUnit, &ChannelId, &SequenceId);
        if ((CDD_I2C_MAXIMUM_SEQUENCE_NUMBER <= SequenceId) || (CDD_I2C_MAXIMUM_CHANNEL_NUMBER <= ChannelId))
        {
            status = CDD_I2C_NOT_OK;
        }

        if (status == CDD_I2C_OK)
        {
            /*Check if sequence is pending and channel is to be read*/
            if ((CDD_I2C_SEQ_PENDING == Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult) &&
                (CDD_I2C_READ == Cdd_I2cChannelContainerLocal[ChannelId].Dir))
            {
                Cdd_I2c_Isr_Handlersequencecheck_channelread(ChannelId, SequenceId, pDataReceiveBuffer,
                                                             pDataReceiveBufferIndex);
            }
            else
            {
                /*Reset data buffer length to initial value*/
                Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength =
                    Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
                /*Reset data buffer pointer to start address*/
                Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
                /*Update channel result*/
                Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_OK;
                /*Check if this is the last channel of the sequence and if the sequence status is
                 * pending*/
                Cdd_I2c_Isr_Handlersequencecheck_lastchannel(ChannelId, SequenceId);
            }
            /*Function call to disable Stop interrupts*/
            regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR);
            HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_SCD, 0);
            HW_WR_REG16((CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR), regVal);
            /*Read I2C Status register*/
            regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICSTR);
            /*Set stop condition detect bit to clear interrupt*/
            HW_SET_FIELD16(regVal, CDD_I2C_ICSTR_SCD, 1);
            /*Write value to I2C status register*/
            HW_WR_REG16((CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICSTR), regVal);
        }
    }
    return status;
}

static void Cdd_I2c_Isr_Handlersequencecheck_channelread(uint8 ChannelId, uint8 SequenceId, uint8 *pDataReceiveBuffer,
                                                         uint32 *pDataReceiveBufferIndex)
{
    uint32 i = 0;
    for (i = 0; i < *pDataReceiveBufferIndex; i++)
    {
        /*Copy data from HwUnit global array to user configured array*/
        *(Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer) = *(pDataReceiveBuffer + i);
        /*Increment data buffer pointer*/
        Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer++;
        /*Decrement data buffer length*/
        Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength--;
    }
    if (0u == Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength)
    {
        /*Reset data buffer length to initial value*/
        Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength = Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
        /*Reset data buffer pointer to start address*/
        Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
        /*Update channel result*/
        Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_OK;
        /*Clear the HwUnit Global reception buffer*/
        memset(&pDataReceiveBuffer[0], 0, *pDataReceiveBufferIndex);
        /*Reset the HwUnit Global reception buffer index*/
        *pDataReceiveBufferIndex = 0;
        /*Check if this is the last channel of the sequence and if the sequence status is pending*/
        Cdd_I2c_Isr_Handlersequencecheck_lastchannel(ChannelId, SequenceId);
    }
}

static void Cdd_I2c_Isr_Handlersequencecheck_lastchannel(uint8 ChannelId, uint8 SequenceId)
{
    if ((ChannelId == Cdd_I2cSequenceContainerLocal[SequenceId]
                          .ChannelList[Cdd_I2cSequenceContainerLocal[SequenceId].MaxChannels - 1u]) &&
        (CDD_I2C_SEQ_PENDING == Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult))
    {
        /*Update sequence result*/
        Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult = CDD_I2C_SEQ_OK;
        /*Check if sequence complete notify function is not passed as NULL*/
        if (NULL_PTR != Cdd_I2cSequenceContainer[SequenceId].SequenceCompleteNotify)
        {
            /*Execute sequence complete notify callback function*/
            Cdd_I2cSequenceContainer[SequenceId].SequenceCompleteNotify();
        }
        else
        {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
            /*Sequence complete notify callback function passed an NULL*/
            Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
#endif
        }
    }
}

static Std_ReturnType Cdd_I2c_Isr_Handler_checkerrors(uint8 HwUnit)
{
    uint8 status     = CDD_I2C_OK;
    uint8 ChannelId  = 0;
    uint8 SequenceId = 0;

    status = Cdd_I2c_Isr_Handler_check_sequenceIDchannelID(HwUnit, &ChannelId, &SequenceId);
    if ((CDD_I2C_MAXIMUM_SEQUENCE_NUMBER <= SequenceId) || (CDD_I2C_MAXIMUM_CHANNEL_NUMBER <= ChannelId))
    {
        status = CDD_I2C_NOT_OK;
    }
    if (status == CDD_I2C_OK)
    {
        Cdd_I2c_Isr_Handler_channelUpdate(HwUnit, ChannelId, SequenceId);
    }
    return status;
}

static void Cdd_I2c_Isr_Handler_datashift(uint8 HwUnit, uint8 *pDataReceiveBuffer, uint32 *pDataReceiveBufferIndex,
                                          uint16 *pDataBufferLength)
{
    uint16 regVal     = 0;
    uint8  SequenceId = 0;
    uint8  ChannelId  = 0;
    if (0u != *pDataBufferLength)
    {
        /*Copy data into global receive buffer*/
        *(pDataReceiveBuffer + *pDataReceiveBufferIndex) = Cdd_I2c_Read(HwUnit);
        /*Increment global data receive buffer index*/
        *pDataReceiveBufferIndex = *pDataReceiveBufferIndex + 1u;
        /*Decrement global data count variable*/
        *pDataBufferLength = *pDataBufferLength - 1u;
    }
    if (0u == *pDataBufferLength)
    {
        SequenceId = Cdd_I2c_Get_Sequence_Id(HwUnit);
        ChannelId  = Cdd_I2c_Get_Channel_Id(HwUnit, SequenceId);
        /*Check if this is the last channel of the sequence*/
        if (ChannelId == Cdd_I2cSequenceContainerLocal[SequenceId]
                             .ChannelList[Cdd_I2cSequenceContainerLocal[SequenceId].MaxChannels - 1u])
        {
            /*Function call to send a stop signal on the bus*/
            Cdd_I2c_Stop(HwUnit);
            /*Function call to disable Receive interrupts*/
            regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR);
            HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICRRDY, 0);
            HW_WR_REG16((CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR), regVal);
        }
        else
        {
            /*Reset data buffer length to initial value*/
            Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength =
                Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
            /*Reset data buffer pointer to start address*/
            Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
            /*Update channel result*/
            Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_OK;
            /*Function call to disable Receive interrupts*/
            regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR);
            HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICRRDY, 0);
            HW_WR_REG16((CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR), regVal);
        }
    }
}

static Std_ReturnType Cdd_I2c_Isr_Handler_datawrite(uint8 HwUnit)
{
    uint8  status     = CDD_I2C_OK;
    uint8  ChannelId  = 0;
    uint8  SequenceId = 0;
    uint16 regVal     = 0;

    status = Cdd_I2c_Isr_Handler_check_sequenceIDchannelID(HwUnit, &ChannelId, &SequenceId);
    if ((CDD_I2C_MAXIMUM_SEQUENCE_NUMBER <= SequenceId) || (CDD_I2C_MAXIMUM_CHANNEL_NUMBER <= ChannelId))
    {
        status = CDD_I2C_NOT_OK;
    }

    if (status == CDD_I2C_OK)
    {
        if (0u != Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength)
        {
            /*Write data to I2c transmit register*/
            Cdd_I2c_Write(HwUnit, *(Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer));
            /*Increment data buffer pointer*/
            Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer++;
            /*Decrement data buffer length*/
            Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength--;
        }
        if (0u == Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength)
        {
            /*Check if the channel is the last channel in the sequence then send a stop*/
            if (ChannelId == Cdd_I2cSequenceContainerLocal[SequenceId]
                                 .ChannelList[Cdd_I2cSequenceContainerLocal[SequenceId].MaxChannels - 1u])
            {
                /*Function call to send a stop signal on the bus*/
                Cdd_I2c_Stop(HwUnit);
                /*Function call to disable Xmit interrupts*/
                regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR);
                HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICXRDY, 0);
                HW_WR_REG16((CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR), regVal);
            }
            else
            {
                /*Function call to disable Xmit interrupts*/
                regVal = HW_RD_REG16(CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR);
                HW_SET_FIELD16(regVal, CDD_I2C_ICIMR_ICXRDY, 0);
                HW_WR_REG16((CddI2cHwUnitBaseAddr[HwUnit] + CDD_I2C_ICIMR), regVal);
                /*Reset data buffer length to initial value*/
                Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength =
                    Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
                /*Reset data buffer pointer to start address*/
                Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
                /*Update channel result*/
                Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_OK;
            }
        }
    }
    return status;
}

static void Cdd_I2c_Isr_Handler_channelUpdate(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId)
{
    /*Update sequence status to fail*/
    Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult = CDD_I2C_SEQ_FAILED;

    if (NULL_PTR != Cdd_I2cSequenceContainer[SequenceId].SequenceErrorNotify)
    {
        /*Execute error callback function if error calback function is not null*/
        Cdd_I2cSequenceContainer[SequenceId].SequenceErrorNotify(
            Cdd_I2c_Error_Handler(Cdd_I2c_Isr_Check(HwUnit), ChannelId, HwUnit));
    }
    else
    {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        /*Sequence error notify callback function passed as NULL_PTR*/
        Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
#endif
    }
    /*Reset data buffer length to initial value*/
    Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength = Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
    /*Reset data buffer pointer to start address*/
    Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
    /*Update channel result*/
    Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_OK;
}

#endif

#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
