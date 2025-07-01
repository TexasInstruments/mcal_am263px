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
 *  \file     Cdd_I2c.c
 *
 *  \brief    This file contains the function implementations of the CDD I2C driver
 *
 *
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#include "Cdd_I2c.h"
#include "Cdd_I2c_priv.h"
#include "Cdd_I2c_hw_reg.h"
#include "Os.h"
#include <string.h>

/* ================================================================ */
/*                            Function Declarations                 */
/* ================================================================ */

static FUNC(void, CDD_I2C_CODE) Cdd_I2c_Init_HW_Setup(void);
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2C_checkCancelErrors(Cdd_I2c_SequenceType sequenceId);
#endif /*(STD_ON == CDD_I2C_DEV_ERROR_DETECT)*/
static FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_HWCancel(Cdd_I2c_SequenceType sequenceId);
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2C_checkSetupEBErrors(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                               Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length);
#endif /*(STD_ON == CDD_I2C_DEV_ERROR_DETECT)*/
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEB_WriteHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                            Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length);
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEB_ReadHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                           Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length);
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2C_checkSetupEBDynamicErrors(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                                      Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length);
#endif /*(STD_ON == CDD_I2C_DEV_ERROR_DETECT)*/
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEBDynamic_WriteHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_AddressType address,
                                   Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                                   Cdd_I2c_DataLengthType length);
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEBDynamic_ReadHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_AddressType address,
                                  Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                                  Cdd_I2c_DataLengthType length);
static FUNC(void, CDD_I2C_CODE) Cdd_I2c_HWMainFunction(Cdd_I2c_Queue_obj *pTemp);
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2C_checkAsyncTransmitErrors(Cdd_I2c_SequenceType sequenceId);
#endif /*(STD_ON == CDD_I2C_DEV_ERROR_DETECT)*/
#if (STD_ON == CDD_I2C_POLLING_MODE)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingON_configuration(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                  Cdd_I2c_AddressType SlaveAddress, uint32 Timeout, uint32 ChannelId);
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingON(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, Cdd_I2c_AddressType SlaveAddress,
                                    uint32 Timeout);
static FUNC(void, CDD_I2C_CODE) Cdd_I2c_AsyncTransmit_PollingONBuscheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                                        uint32 Timeout, uint32 ChannelId);
static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingONDatacheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, uint32 ChannelId);
static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingONcheckchannelconfigure(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, uint32 Timeout,
                                                         uint32 ChannelId);
static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_PollingModeProcessing_channelupdate(uint8 SequenceId, uint8 ChannelId, uint8 HwUnit);
#endif
#if (STD_OFF == CDD_I2C_POLLING_MODE)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingOFF(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, Cdd_I2c_AddressType SlaveAddress,
                                     uint32 Timeout);
static FUNC(void, CDD_I2C_CODE) Cdd_I2c_AsyncTransmit_PollingOFFBuscheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                                         uint32 Timeout, uint32 ChannelId);
static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingOFFsequencecheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit);
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingOFFsequenceupdate(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                   Cdd_I2c_AddressType SlaveAddress, uint32 ChannelId);
#endif

/* ================================================================ */
/*                          Global variables                        */
/* ================================================================ */

#define CDD_I2C_START_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"
/*Driver status should be uninitialized at the begining*/
VAR(Cdd_I2c_ComponentStatusType, CDD_I2C_VAR_INIT) CddI2cDrvState = CDD_I2C_UNINIT;
VAR(Cdd_I2c_HwUnitStatus, CDD_I2C_VAR_INIT)
CddI2cHwUnitStatus[CDD_I2C_HW_UNITS_MAX] = {CDD_I2C_HW_UNIT_FREE};
#define CDD_I2C_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"

#define CDD_I2C_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"
VAR(Cdd_I2c_Sequence_Config, CDD_I2C_VAR_NO_INIT)
Cdd_I2cSequenceContainerLocal[CDD_I2C_MAXIMUM_SEQUENCE_NUMBER];
VAR(Cdd_I2c_Channel_Config, CDD_I2C_VAR_NO_INIT)
Cdd_I2cChannelContainerLocal[CDD_I2C_MAXIMUM_CHANNEL_NUMBER];
#define CDD_I2C_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"

#if (STD_OFF == CDD_I2C_POLLING_MODE)
#if defined(USED_CDD_I2C_HW_UNIT_0)
#define CDD_I2C_START_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"
uint8 DataReceiveBufferHwUnit0[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE] = {0};
#define CDD_I2C_STOP_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"

#define CDD_I2C_START_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
uint32 DataReceiveBufferIndexHwUnit0 = 0;
#define CDD_I2C_STOP_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
#endif

#if defined(USED_CDD_I2C_HW_UNIT_1)
#define CDD_I2C_START_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"
uint8 DataReceiveBufferHwUnit1[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE] = {0};
#define CDD_I2C_STOP_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"

#define CDD_I2C_START_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
uint32 DataReceiveBufferIndexHwUnit1 = 0;
#define CDD_I2C_STOP_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
#endif

#if defined(USED_CDD_I2C_HW_UNIT_2)
#define CDD_I2C_START_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"
uint8 DataReceiveBufferHwUnit2[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE] = {0};
#define CDD_I2C_STOP_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"

#define CDD_I2C_START_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
uint32 DataReceiveBufferIndexHwUnit2 = 0;
#define CDD_I2C_STOP_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
#endif

#if defined(USED_CDD_I2C_HW_UNIT_3)
#define CDD_I2C_START_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"
uint8 DataReceiveBufferHwUnit3[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE] = {0};
#define CDD_I2C_STOP_SEC_VAR_INIT_8
#include "Cdd_I2c_MemMap.h"

#define CDD_I2C_START_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
uint32 DataReceiveBufferIndexHwUnit3 = 0;
#define CDD_I2C_STOP_SEC_VAR_INIT_32
#include "Cdd_I2c_MemMap.h"
#endif

#define CDD_I2C_START_SEC_VAR_INIT_16
#include "Cdd_I2c_MemMap.h"
uint16 DataBufferLengthHwUnit[CDD_I2C_HW_UNITS_MAX] = {0};
#define CDD_I2C_STOP_SEC_VAR_INIT_16
#include "Cdd_I2c_MemMap.h"
#endif

#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"

/* ================================================================ */
/*                          Function Definitions                    */
/* ================================================================ */

/*
 *Design: MCAL-13622, MCAL-13636, MCAL-13637, MCAL-13638, MCAL-13683, MCAL-13684, MCAL-13685,
 *MCAL-13686
 */
FUNC(void, CDD_I2C_CODE) Cdd_I2c_Init(Cdd_I2c_ConfigType *configPtr)
{
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (NULL_PTR != configPtr)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_INIT, CDD_I2C_E_PARAM_CONFIG);
        /*Invalid pointer passed as argument*/
    }

    else if (CDD_I2C_UNINIT != CddI2cDrvState)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_INIT, CDD_I2C_E_ALREADY_INITIALIZED);
        /*Driver already initialized*/
    }
#endif

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    else
#endif
    {
        /*Function implemented due to Klocwork HIS Metrics issues */
        if (CDD_I2C_UNINIT == CddI2cDrvState)
        {
            Cdd_I2c_Init_HW_Setup();
        }
    }
    CddI2cDrvState = CDD_I2C_IDLE;
}

static FUNC(void, CDD_I2C_CODE) Cdd_I2c_Init_HW_Setup(void)
{
    uint8 i = 0;
    for (i = 0; i < CDD_I2C_HW_UNITS_USED; i++)
    {
        /**
         * Function call initialises I2C hardware unit
         * at frequency specified from GUI
         * and specified I2C bus frequency
         */
        Cdd_I2c_Setup_HW_Unit_Clk(
            pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance, pCddI2cInitParams->CddI2cHwCfgPtr[i].BaudRate,
            pCddI2cInitParams->CddI2cHwCfgPtr[i].HwUnitFrequency, pCddI2cInitParams->CddI2cHwCfgPtr[i].SysClk);

        /*Function call to clear all I2C related interrupts*/
        Cdd_I2c_Clear_interrupts(pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance, CDD_I2C_ALL_INTERRUPTS_CLEAR);

        /*Function call to disable all I2C related interrupts*/
        Cdd_I2c_Disable_interrupts(pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));

        /**
         * Function call to enable Cdd_I2c master, set up I2C in free run
         * and bring I2c out of reset
         */
        Cdd_I2c_Enable_master(pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance);

        /*Function call to set own address as 0x7F by default*/
        Cdd_I2c_Set_Own_Address(pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance, CDD_I2C_EXTENDED_ADDRESS_7F);
    }
    /*Copy sequence configurations into a local sequence array*/
    memcpy((void *)&Cdd_I2cSequenceContainerLocal, (void *)&Cdd_I2cSequenceContainer, sizeof(Cdd_I2cSequenceContainer));
    /*Copy channel configurations into a local channel array*/
    memcpy(&Cdd_I2cChannelContainerLocal, &Cdd_I2cChannelContainer, sizeof(Cdd_I2cChannelContainer));
    /*Function call to set all queue parameters to default value*/
    Cdd_I2c_queue_init(pCddI2cTransmissionQueue);
}

/*
 *Design: MCAL-13623, MCAL-13644, MCAL-13645, MCAL-13684
 */
FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_DeInit(void)
{
    uint8 i      = 0;
    uint8 status = 0;

    if (CDD_I2C_UNINIT != CddI2cDrvState)
    {
        for (i = 0; i < CDD_I2C_HW_UNITS_USED; i++)
        {
            /*Function call to disable all I2C related interrupts*/
            Cdd_I2c_Disable_interrupts(pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance,
                                       (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
            /*Function call to put I2C peripheral in reset mode*/
            Cdd_I2c_Disable_master(pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance);
        }
        /*Update the driver status global variable to UNINIT*/
        CddI2cDrvState = CDD_I2C_UNINIT;
        status         = (uint8)CddI2cDrvState;
    }
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    else
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_DEINIT, CDD_I2C_E_UNINIT);
        /*Driver already un-initialized*/
    }
#endif
    /*return driver state*/
    return status;
}

/*
 *Design: MCAL-13632, MCAL-13647, MCAL-13648
 */
#if (STD_ON == CDD_I2C_VERSION_INFO_API) /*STD_ON == CDD_I2C_VERSION_INFO_API*/
FUNC(void, CDD_I2C_CODE) Cdd_I2c_GetVersionInfo(Std_VersionInfoType *versionInfoPtr)
{
    if (NULL_PTR != versionInfoPtr)
    {
        versionInfoPtr->vendorID         = CDD_I2C_VENDOR_ID;
        versionInfoPtr->moduleID         = CDD_I2C_MODULE_ID;
        versionInfoPtr->sw_major_version = (uint8)CDD_I2C_SW_MAJOR_VERSION;
        versionInfoPtr->sw_minor_version = (uint8)CDD_I2C_SW_MINOR_VERSION;
        versionInfoPtr->sw_patch_version = (uint8)CDD_I2C_SW_PATCH_VERSION;
    }
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    else
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_GET_VERSION_INFO, CDD_I2C_E_PARAM_VINFO_PTR);
        /*NULL_PTR passed as argument*/
    }
#endif
}
#endif /*<STD_ON == CDD_I2C_VERSION_INFO_API>*/

/*
 *Design: MCAL-13624, MCAL-13649, MCAL-13650, MCAL-13651, MCAL-13652, MCAL-13653, MCAL-13654
 */
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_SetupEB(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length)
{
    VAR(Std_ReturnType, AUTOMATIC) status = CDD_I2C_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    status = Cdd_I2C_checkSetupEBErrors(channelId, txDataBufferPtr, rxDataBufferPtr, length);
#endif /* (STD_ON == CDD_I2C_DEV_ERROR_DETECT) */

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (((NULL_PTR != txDataBufferPtr) && (NULL_PTR == rxDataBufferPtr)) && (status == CDD_I2C_OK))
#elif (STD_OFF == CDD_I2C_DEV_ERROR_DETECT)
    if (((NULL_PTR != txDataBufferPtr) && (NULL_PTR == rxDataBufferPtr)) && (status == CDD_I2C_OK))
#endif
    {
        status = Cdd_I2c_SetupEB_WriteHW(channelId, txDataBufferPtr, rxDataBufferPtr, length);
    }
    else if (((NULL_PTR == txDataBufferPtr) && (NULL_PTR != rxDataBufferPtr)) && (status == CDD_I2C_OK))
    {
        status = Cdd_I2c_SetupEB_ReadHW(channelId, txDataBufferPtr, rxDataBufferPtr, length);
    }
    else
    {
        /*Do Nothing*/
    }
    return status;
}

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2C_checkSetupEBErrors(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                               Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length)
{
    uint8 status = CDD_I2C_OK;

    if (CDD_I2C_UNINIT == CddI2cDrvState)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB, CDD_I2C_E_UNINIT);
        /*Driver un-initialized*/
        status = CDD_I2C_NOT_OK;
    }

    if ((CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE < length) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB, CDD_I2C_E_PARAM_LENGTH);
        /*Message size exceeds maximum allowed message length*/
        status = CDD_I2C_NOT_OK;
    }

    if ((CDD_I2C_MAXIMUM_CHANNEL_NUMBER <= channelId) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB, CDD_I2C_E_PARAM_CHANNEL);
        /*Channel ID exceeds maximum number of channels configured*/
        status = CDD_I2C_NOT_OK;
    }

    if (((NULL_PTR == txDataBufferPtr) && (NULL_PTR == rxDataBufferPtr)) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB, CDD_I2C_E_PARAM_TRANS_BUFFER);
        /*Both buffers passed are NULL_PTR*/
        status = CDD_I2C_NOT_OK;
    }

    if (((NULL_PTR != txDataBufferPtr) && (NULL_PTR != rxDataBufferPtr)) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB, CDD_I2C_E_PARAM_TRANS_BUFFER);
        /*Both buffers passed are non NULL_PTR*/
        status = CDD_I2C_NOT_OK;
    }

    return status;
}
#endif /*STD_ON == CDD_I2C_DEV_ERROR_DETECT*/

static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEB_WriteHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                            Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length)
{
    uint8 status = CDD_I2C_OK;

    if (CDD_I2C_WRITE == Cdd_I2cChannelContainerLocal[channelId].Dir)
    {
        /*Copy user input to conifgurations*/
        Cdd_I2cChannelContainer[channelId].DataBufferLength = length;
        Cdd_I2cChannelContainer[channelId].DataBuffer       = txDataBufferPtr;
        /*Copy user input to local driver objects*/
        Cdd_I2cChannelContainerLocal[channelId].DataBufferLength = Cdd_I2cChannelContainer[channelId].DataBufferLength;
        Cdd_I2cChannelContainerLocal[channelId].DataBuffer       = Cdd_I2cChannelContainer[channelId].DataBuffer;
        status                                                   = CDD_I2C_OK;
    }

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    else
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB, CDD_I2C_E_PARAM_DIRECTION);
        /*Buffer direction conflicts with channel direction configured in EB*/
    }
#endif

    return status;
}

static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEB_ReadHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                           Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length)
{
    uint8 status = CDD_I2C_OK;

    if (CDD_I2C_READ == Cdd_I2cChannelContainerLocal[channelId].Dir)
    {
        /*Copy user input to conifgurations*/
        Cdd_I2cChannelContainer[channelId].DataBufferLength = length;
        Cdd_I2cChannelContainer[channelId].DataBuffer       = rxDataBufferPtr;
        /*Copy user input to local driver objects*/
        Cdd_I2cChannelContainerLocal[channelId].DataBufferLength = Cdd_I2cChannelContainer[channelId].DataBufferLength;
        Cdd_I2cChannelContainerLocal[channelId].DataBuffer       = Cdd_I2cChannelContainer[channelId].DataBuffer;
        status                                                   = CDD_I2C_OK;
    }

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    else
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB, CDD_I2C_E_PARAM_DIRECTION);
        /*Buffer direction conflicts with channel direction configured in EB*/
    }
#endif

    return status;
}

/*
 *Design: MCAL-13625, MCAL-13655, MCAL-13656, MCAL-13657, MCAL-13658, MCAL-13659, MCAL-13660,
 *MCAL-13688, MCAL-13689
 */
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_SetupEBDynamic(Cdd_I2c_ChannelType channelId, Cdd_I2c_AddressType address,
                       Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                       Cdd_I2c_DataLengthType length)
{
    VAR(Std_ReturnType, AUTOMATIC) status = CDD_I2C_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    status = Cdd_I2C_checkSetupEBDynamicErrors(channelId, txDataBufferPtr, rxDataBufferPtr, length);
#endif

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (((NULL_PTR != txDataBufferPtr) && (NULL_PTR == rxDataBufferPtr)) && (status == CDD_I2C_OK))
#elif (STD_OFF == CDD_I2C_DEV_ERROR_DETECT)
    if (((NULL_PTR != txDataBufferPtr) && (NULL_PTR == rxDataBufferPtr)) && (status == CDD_I2C_OK))
#endif
    {
        status = Cdd_I2c_SetupEBDynamic_WriteHW(channelId, address, txDataBufferPtr, rxDataBufferPtr, length);
    }
    else if (((NULL_PTR == txDataBufferPtr) && (NULL_PTR != rxDataBufferPtr)) && (status == CDD_I2C_OK))
    {
        status = Cdd_I2c_SetupEBDynamic_ReadHW(channelId, address, txDataBufferPtr, rxDataBufferPtr, length);
    }
    else
    {
        /*Do Nothing*/
    }
    return status;
}

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2C_checkSetupEBDynamicErrors(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                                      Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length)
{
    uint8 status = CDD_I2C_OK;

    if (CDD_I2C_UNINIT == CddI2cDrvState)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB_DYNAMIC, CDD_I2C_E_UNINIT);
        /*Driver un-initialized*/
        status = CDD_I2C_NOT_OK;
    }

    if ((CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE < length) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB_DYNAMIC, CDD_I2C_E_PARAM_LENGTH);
        /*Message size exceeds maximum allowed message length*/
        status = CDD_I2C_NOT_OK;
    }

    if ((CDD_I2C_MAXIMUM_CHANNEL_NUMBER <= channelId) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB_DYNAMIC, CDD_I2C_E_PARAM_CHANNEL);
        /*Channel ID exceeds maximum number of channels configured*/
        status = CDD_I2C_NOT_OK;
    }

    if (((NULL_PTR == txDataBufferPtr) && (NULL_PTR == rxDataBufferPtr)) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB_DYNAMIC, CDD_I2C_E_PARAM_TRANS_BUFFER);
        /*Both buffers passed are NULL_PTR*/
        status = CDD_I2C_NOT_OK;
    }

    if (((NULL_PTR != txDataBufferPtr) && (NULL_PTR != rxDataBufferPtr)) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB_DYNAMIC, CDD_I2C_E_PARAM_TRANS_BUFFER);
        /*Both buffers passed are non NULL_PTR*/
        status = CDD_I2C_NOT_OK;
    }

    return status;
}
#endif /*STD_ON == CDD_I2C_DEV_ERROR_DETECT*/

static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEBDynamic_WriteHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_AddressType address,
                                   Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                                   Cdd_I2c_DataLengthType length)
{
    uint8 status = CDD_I2C_OK;

    if (CDD_I2C_WRITE == Cdd_I2cChannelContainerLocal[channelId].Dir)
    {
        /*Copy user input to conifgurations*/
        Cdd_I2cChannelContainer[channelId].DataBufferLength = length;
        Cdd_I2cChannelContainer[channelId].DataBuffer       = txDataBufferPtr;
        Cdd_I2cChannelContainer[channelId].SlaveAddress     = address;
        if (Cdd_I2cChannelContainer[channelId].SlaveAddress > CDD_I2C_EXTENDED_ADDRESS_7F)
        {
            Cdd_I2cChannelContainer[channelId].SlaveAddressScheme = CDD_I2C_10_BIT_ADDRESS;
        }
        else
        {
            Cdd_I2cChannelContainer[channelId].SlaveAddressScheme = CDD_I2C_7_BIT_ADDRESS;
        }
        /*Copy user input to local driver objects*/
        Cdd_I2cChannelContainerLocal[channelId].DataBufferLength = Cdd_I2cChannelContainer[channelId].DataBufferLength;
        Cdd_I2cChannelContainerLocal[channelId].DataBuffer       = Cdd_I2cChannelContainer[channelId].DataBuffer;
        Cdd_I2cChannelContainerLocal[channelId].SlaveAddress     = Cdd_I2cChannelContainer[channelId].SlaveAddress;
        Cdd_I2cChannelContainerLocal[channelId].SlaveAddressScheme =
            Cdd_I2cChannelContainer[channelId].SlaveAddressScheme;
        status = CDD_I2C_OK;
    }

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    else
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB_DYNAMIC, CDD_I2C_E_PARAM_DIRECTION);
        /*Buffer direction conflicts with channel direction configured in EB*/
    }
#endif

    return status;
}

static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_SetupEBDynamic_ReadHW(Cdd_I2c_ChannelType channelId, Cdd_I2c_AddressType address,
                                  Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                                  Cdd_I2c_DataLengthType length)
{
    uint8 status = CDD_I2C_OK;

    if (CDD_I2C_READ == Cdd_I2cChannelContainerLocal[channelId].Dir)
    {
        /*Copy user input to conifgurations*/
        Cdd_I2cChannelContainer[channelId].DataBufferLength = length;
        Cdd_I2cChannelContainer[channelId].DataBuffer       = rxDataBufferPtr;
        Cdd_I2cChannelContainer[channelId].SlaveAddress     = address;
        if (Cdd_I2cChannelContainer[channelId].SlaveAddress > CDD_I2C_EXTENDED_ADDRESS_7F)
        {
            Cdd_I2cChannelContainer[channelId].SlaveAddressScheme = CDD_I2C_10_BIT_ADDRESS;
        }
        else
        {
            Cdd_I2cChannelContainer[channelId].SlaveAddressScheme = CDD_I2C_7_BIT_ADDRESS;
        }
        /*Copy user input to local driver objects*/
        Cdd_I2cChannelContainerLocal[channelId].DataBufferLength = Cdd_I2cChannelContainer[channelId].DataBufferLength;
        Cdd_I2cChannelContainerLocal[channelId].DataBuffer       = Cdd_I2cChannelContainer[channelId].DataBuffer;
        Cdd_I2cChannelContainerLocal[channelId].SlaveAddress     = Cdd_I2cChannelContainer[channelId].SlaveAddress;
        Cdd_I2cChannelContainerLocal[channelId].SlaveAddressScheme =
            Cdd_I2cChannelContainer[channelId].SlaveAddressScheme;
        status = CDD_I2C_OK;
    }

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    else
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_SETUP_EB_DYNAMIC, CDD_I2C_E_PARAM_DIRECTION);
        /*Buffer direction conflicts with channel direction configured in EB*/
    }
#endif

    return status;
}

/*
 *Design: MCAL-13626, MCAL-13663, MCAL-13664, MCAL-13665, MCAL-13666, MCAL-13667, MCAL-13709,
 *MCAL-13690, MCAL-13668, MCAL-13669, MCAL-13670, MCAL-13671, MCAL-13681, MCAL-13682, MCAL-13691
 */
FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_AsyncTransmit(Cdd_I2c_SequenceType sequenceId)
{
    /*Retun API status*/
    VAR(Std_ReturnType, AUTOMATIC) status = CDD_I2C_OK;
    /*Stores Hardware Unit being used by the sequence*/
    uint8               HwUnit = 0;
    /*Stores the slave address passed in channel container*/
    Cdd_I2c_AddressType SlaveAddress = 0;
    /*Stores timeout value*/
    uint32              Timeout = 0;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    status = Cdd_I2C_checkAsyncTransmitErrors(sequenceId);
#endif /* (STD_ON == CDD_I2C_DEV_ERROR_DETECT) */

    if (CDD_I2C_OK == status)
    {
        /*Update driver status*/
        CddI2cDrvState = CDD_I2C_BUSY;
        /*Update hardware unit in use status*/
        CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[sequenceId].HwInstance] = CDD_I2C_HW_UNIT_BUSY;
        /*Determine the HW unit used in the sequence*/
        HwUnit = Cdd_I2cSequenceContainerLocal[sequenceId].HwInstance;

#if (STD_ON == CDD_I2C_POLLING_MODE)
        status = Cdd_I2c_AsyncTransmit_PollingON(sequenceId, HwUnit, SlaveAddress, Timeout);
#endif

#if (STD_OFF == CDD_I2C_POLLING_MODE)
        status = Cdd_I2c_AsyncTransmit_PollingOFF(sequenceId, HwUnit, SlaveAddress, Timeout);

        /*Check if sequence has failed*/
        if (CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
        {
            /*Function call to queue sequence*/
            Cdd_I2c_Enqueue(sequenceId);
            /*Update API status*/
            status = CDD_I2C_NOT_OK;
        }
#endif
    }
    else
    {
        /*Do Nothing*/
    }

    /*Update driver status*/
    CddI2cDrvState = CDD_I2C_IDLE;
    /*Update hardware unit free status*/
    CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[sequenceId].HwInstance] = CDD_I2C_HW_UNIT_FREE;
    /*Return API status*/
    return status;
}

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2C_checkAsyncTransmitErrors(Cdd_I2c_SequenceType sequenceId)
{
    uint8 status = CDD_I2C_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    /*Check if driver is uninitialized*/
    if (CDD_I2C_UNINIT == CddI2cDrvState)
    {
        /*Driver un-initialized*/
        Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_UNINIT);
        /*Update sequence status*/
        Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
        /*Update API return status*/
        status = CDD_I2C_NOT_OK;
        /*Function call to queue sequence*/
        Cdd_I2c_Enqueue(sequenceId);
    }

    /*Check if sequence number is within bounds of maximum sequence configured*/
    if ((CDD_I2C_MAXIMUM_SEQUENCE_NUMBER <= sequenceId) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        /*Sequence ID out of bounds*/
        Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_SEQUENCE);
        /*Update sequence status*/
        Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
        /*Update API return status*/
        status = CDD_I2C_NOT_OK;
        /*Function call to queue sequence*/
        Cdd_I2c_Enqueue(sequenceId);
    }
#endif /*STD_ON == CDD_I2C_DEV_ERROR_DETECT*/

    /*Check if Hardware unit is busy*/
    if ((CDD_I2C_HW_UNIT_BUSY == CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[sequenceId].HwInstance]) &&
        (status == (Std_ReturnType)CDD_I2C_OK))
    {
        if (NULL_PTR != Cdd_I2cSequenceContainer[sequenceId].SequenceCompleteNotify)
        {
            Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify(CDD_I2C_E_HW_UNIT_BUSY);
            /*Report Hardware unit is busy*/
        }
        else
        {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
            /*Sequence complete notify callback function passed an NULL*/
            Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
#endif
        }
        Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
        /*Update sequence status*/
        status = CDD_I2C_NOT_OK;
        /*Function call to queue sequence*/
        Cdd_I2c_Enqueue(sequenceId);
    }
    return status;
}
#endif /*STD_ON == CDD_I2C_DEV_ERROR_DETECT*/

#if (STD_ON == CDD_I2C_POLLING_MODE)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingON(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, Cdd_I2c_AddressType SlaveAddress,
                                    uint32 Timeout)
{
    uint8               status = CDD_I2C_OK;
    uint8               i      = 0;
    Cdd_I2c_AddressType SlaveAddress_local;
    SlaveAddress_local     = SlaveAddress;
    uint32 ChannelId_local = 0;

    /*Implement polling mode transmission*/
    for (i = 0; ((i < Cdd_I2cSequenceContainerLocal[sequenceId].MaxChannels) && (status == CDD_I2C_OK)); i++)
    {
        /*Break out of loop in case sequence fails*/
        if (CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
        {
            status = CDD_I2C_NOT_OK;
        }

        if (status == CDD_I2C_OK)
        {
            /*Find the current channel ID of the sequence going transmission*/
            ChannelId_local = Cdd_I2cSequenceContainerLocal[sequenceId].ChannelList[i];
            /*Find the Slave address of the current channel*/
            SlaveAddress_local = Cdd_I2cChannelContainerLocal[ChannelId_local].SlaveAddress;
            if (NULL_PTR == Cdd_I2cChannelContainerLocal[ChannelId_local].DataBuffer)
            {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
                Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_TRANS_BUFFER);
/*Async transmit called before setupEB*/
#endif
                Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
                /*Sequence status updated to fail*/
                status = CDD_I2C_NOT_OK;
            }
            if (status == CDD_I2C_OK)
            {
                status = Cdd_I2c_AsyncTransmit_PollingON_configuration(sequenceId, HwUnit, SlaveAddress_local, Timeout,
                                                                       ChannelId_local);
                /*Check if sequence has failed*/
            }
        }
    }
    /*Check if sequence has failed*/
    if (CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
    {
        /*Reset data buffer length to initial value*/
        Cdd_I2cChannelContainerLocal[ChannelId_local].DataBufferLength =
            Cdd_I2cChannelContainer[ChannelId_local].DataBufferLength;
        /*Reset data buffer pointer to start address*/
        Cdd_I2cChannelContainerLocal[ChannelId_local].DataBuffer = Cdd_I2cChannelContainer[ChannelId_local].DataBuffer;
        /*Function call to queue sequence*/
        Cdd_I2c_Enqueue(sequenceId);
        /*Update API status*/
        status = CDD_I2C_NOT_OK;
    }
    return status;
}

static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingON_configuration(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                  Cdd_I2c_AddressType SlaveAddress, uint32 Timeout, uint32 ChannelId)
{
    Std_ReturnType status = CDD_I2C_OK;
    /*Function call to set the addressing mode for the slave device*/
    Cdd_I2c_Set_Slave_Addressing_mode(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId].SlaveAddressScheme);
    /*Function call to set the slave address when device in master mode*/
    Cdd_I2c_Set_Slave_Address(HwUnit, SlaveAddress);
    /*Check if the channel is configured for writing to I2C slave*/
    if (CDD_I2C_WRITE == Cdd_I2cChannelContainerLocal[ChannelId].Dir)
    {
        /*Update Sequence result*/
        Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_PENDING;
        /*Check if channel is already in use and do the channel task*/
        Cdd_I2c_AsyncTransmit_PollingONcheckchannelconfigure(sequenceId, HwUnit, Timeout, ChannelId);
        if ((CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult))
        {
            status = CDD_I2C_NOT_OK;
        }
    }

    return status;
}

static FUNC(void, CDD_I2C_CODE) Cdd_I2c_AsyncTransmit_PollingONBuscheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                                        uint32 Timeout, uint32 ChannelId)
{
    TickType Timeout_local = Timeout;
    while (CDD_I2C_BUS_BUSY == Cdd_I2cBusCheck(HwUnit))
    {
        /*Get elapsed time value*/
        if (1U == (Cdd_I2c_Timeout(Timeout_local, CDD_I2C_RESET_TIMEOUT)))
        {
            /*Call Cdd_I2c_SetHandling if bus is busy for more than specified time period*/
            Cdd_I2c_SetHandling(CddI2cArbitrationLossParam);
            Timeout_local = 0;
            /*Update channel status*/
            Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_BUSFAIL;
            if (NULL_PTR != Cdd_I2cSequenceContainer[sequenceId].SequenceCompleteNotify)
            {
                /*Throw timeout error*/
                Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify(CDD_I2C_E_PARAM_TIMEOUT);
            }
            else
            {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
                /*Sequence complete notify callback function passed an NULL*/
                Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
#endif
            }
            /*Update sequence status to fail*/
            Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
            break;
        }
    }
}

static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingONDatacheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, uint32 ChannelId)
{
    while (0U != Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength)
    {
        /*Check for errors*/
        if ((Cdd_I2c_Isr_Check(HwUnit) & (CDD_I2C_ICSTR_AL_MASK | CDD_I2C_ICSTR_NACK_MASK | CDD_I2C_ICSTR_AD0_MASK |
                                          CDD_I2C_ICSTR_RSFULL_MASK)) != 0U)
        {
            if (NULL_PTR != Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify)
            {
                /*Execute error callback function if error calback function is not null*/
                Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify(
                    Cdd_I2c_Error_Handler(Cdd_I2c_Isr_Check(HwUnit), (uint8)ChannelId, HwUnit));
            }
            else
            {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
                /*Sequence error notify callback function passed as NULL_PTR*/
                Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
#endif
            }
            /*Update sequence status to fail*/
            Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
            break;
        }
        else if ((Cdd_I2c_Isr_Check(HwUnit) & (CDD_I2C_ICSTR_ICXRDY_MASK)) != 0U)
        {
            /*Write data to I2c transmit register*/
            Cdd_I2c_Write(HwUnit, *(Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer));
            /*Increment data buffer pointer*/
            Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer++;
            /*Decrement data buffer length*/
            Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength--;
        }
        else
        {
            /*Do Nothing*/
        }
    }
}

static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingONcheckchannelconfigure(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, uint32 Timeout,
                                                         uint32 ChannelId)
{
    uint8    status_break_1 = CDD_I2C_OK;
    uint8    status_break_2 = CDD_I2C_OK;
    TickType Timeout_local  = Timeout;

    if (CDD_I2C_CH_RESULT_IN_PROGRESS == Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult)
    {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        /*Throw channel busy error*/
        Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify(CDD_I2C_E_CHANNEL_BUSY);
#endif
        /*Sequence status updated to fail*/
        Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
        status_break_1                                      = CDD_I2C_NOT_OK;
    }
    if (status_break_1 == CDD_I2C_OK)
    {
        /*Update channel result*/
        Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_IN_PROGRESS;
        /*Function call to set master in transmit mode*/
        Cdd_I2c_Set_Master_Transmit_Mode(HwUnit);
        /*Function call to set number of bytes to write to slave*/
        Cdd_I2c_Data_Count(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength);
        /*Disable global interrupts*/
        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
        /*Function call to disable local interrupts*/
        Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
        /*Function call to clear all I2C related interrupts*/
        Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
        /*Function call to enable configurator selected interrupts*/
        Cdd_I2c_Enable_interrupts(HwUnit);
        /*Enable global interrupts*/
        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
        /*Get initial value for timeout period*/
        (void)GetCounterValue(CDD_I2C_OS_COUNTER_ID, &Timeout_local);
        /*Check if bus is busy*/
        if (CDD_I2C_RESTART_MODE_STOP == Cdd_I2cSequenceContainerLocal[sequenceId].RestartMode)
        {
            Cdd_I2c_AsyncTransmit_PollingONBuscheck(sequenceId, HwUnit, Timeout_local, ChannelId);
        }

        /*Reset timeout variable*/
        Timeout_local = 0;
    }
    /*Check if sequence status is fail*/
    if ((CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult))
    {
        /*Disable global interrupts*/
        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
        /*Function call to disable local interrupts*/
        Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
        /*Function call to clear all I2C related interrupts*/
        Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
        /*Function call to enable configurator selected interrupts*/
        Cdd_I2c_Enable_interrupts(HwUnit);
        /*Enable global interrupts*/
        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
        /*Break out of the for loop in case sequence is failed*/
        status_break_2 = CDD_I2C_NOT_OK;
    }
    if ((status_break_1 == CDD_I2C_OK) && (status_break_2 == CDD_I2C_OK))
    {
        /*Disable global interrupts*/
        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
        /*Function call to send a start signal on the bus in interrupt mode*/
        Cdd_I2c_Start(HwUnit);
        /*Stay in loop unless all expected data is transmitted*/
        Cdd_I2c_AsyncTransmit_PollingONDatacheck(sequenceId, HwUnit, ChannelId);
        /*Check restart mode*/
        if (CDD_I2C_RESTART_MODE_STOP == Cdd_I2cSequenceContainerLocal[sequenceId].RestartMode)
        {
            /*Stop at the end of channel if restart mode is stop-start*/
            Cdd_I2c_Stop(HwUnit);
        }
        /*Function call to disable local interrupts*/
        Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
        /*Function call to clear all I2C related interrupts*/
        Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
        /*Function call to enable configurator selected interrupts*/
        Cdd_I2c_Enable_interrupts(HwUnit);
        /*Enable global interrupts*/
        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();

        /*If last channel of sequence, do a hard stop*/
        if (ChannelId == Cdd_I2cSequenceContainerLocal[sequenceId]
                             .ChannelList[Cdd_I2cSequenceContainerLocal[sequenceId].MaxChannels - 1u] &&
            (CDD_I2C_SEQ_PENDING == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult))
        {
            /*Check if sequence complete notify function is not passed as NULL*/
            if (NULL_PTR != Cdd_I2cSequenceContainer[sequenceId].SequenceCompleteNotify)
            {
                /*Execute sequence complete notify callback function*/
                Cdd_I2cSequenceContainer[sequenceId].SequenceCompleteNotify();
            }
            else
            {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
                /*Sequence complete notify callback function passed an NULL*/
                Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_NOTIFY_CALLBACK);
#endif
            }
            /*If restart mode is restart, then stop, else stop is done above for stop-start slave transmission mode*/
            if (CDD_I2C_RESTART_MODE_STOP != Cdd_I2cSequenceContainerLocal[sequenceId].RestartMode)
            {
                /*Stop at the end of channel if restart mode is stop-start*/
                Cdd_I2c_Stop(HwUnit);
            }
            /*Mark the sequence as OK and free the hardware instance*/
            Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult                      = CDD_I2C_SEQ_OK;
            CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[sequenceId].HwInstance] = CDD_I2C_HW_UNIT_FREE;
        }

        /*Update channel result*/
        Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_OK;

        /*Reset data buffer length to initial value*/
        Cdd_I2cChannelContainerLocal[ChannelId].DataBufferLength = Cdd_I2cChannelContainer[ChannelId].DataBufferLength;
        /*Reset data buffer pointer to start address*/
        Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer = Cdd_I2cChannelContainer[ChannelId].DataBuffer;
    }
}
#endif

#if (STD_OFF == CDD_I2C_POLLING_MODE)
static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingOFF(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit, Cdd_I2c_AddressType SlaveAddress,
                                     uint32 Timeout)
{
    uint8               status        = CDD_I2C_OK;
    uint8               i             = 0;
    TickType            Timeout_local = Timeout;
    Cdd_I2c_AddressType SlaveAddress_local;
    SlaveAddress_local = SlaveAddress;
    /*Stores the channel ID*/
    uint32 ChannelId_local = 0;

    /*Implement interrupt mode transmission/reception*/
    for (i = 0; ((i < Cdd_I2cSequenceContainerLocal[sequenceId].MaxChannels) && (status == CDD_I2C_OK)); i++)
    {
        /*Break out of loop in case sequence fails*/
        if (CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
        {
            status = CDD_I2C_NOT_OK;
        }
        if (status == CDD_I2C_OK)
        {
            /*Update Sequence result*/
            Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_PENDING;
            /*Find the current channel ID of the sequence going transmission*/
            ChannelId_local = Cdd_I2cSequenceContainerLocal[sequenceId].ChannelList[i];
            /*Find the Slave address of the current channel*/
            SlaveAddress_local = Cdd_I2cChannelContainerLocal[ChannelId_local].SlaveAddress;
            status =
                Cdd_I2c_AsyncTransmit_PollingOFFsequenceupdate(sequenceId, HwUnit, SlaveAddress_local, ChannelId_local);
        }

        /*Check if the channel is configured for writing to I2C slave*/
        if ((CDD_I2C_WRITE == Cdd_I2cChannelContainerLocal[ChannelId_local].Dir) && (status == CDD_I2C_OK))
        {
            /*Function call to set master in transmit mode*/
            Cdd_I2c_Set_Master_Transmit_Mode(HwUnit);
            /*Function call to set number of bytes to write to slave*/
            Cdd_I2c_Data_Count(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId_local].DataBufferLength);
            /*Disable global interrupts*/
            SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
            /*Function call to disable local interrupts*/
            Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
            /*Function call to clear all I2C related interrupts*/
            Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
            /*Function call to enable configurator selected interrupts*/
            Cdd_I2c_Enable_interrupts(HwUnit);
            /*Enable global interrupts*/
            SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
            /*Get initial value for timeout period*/
            (void)GetCounterValue((CounterType)CDD_I2C_OS_COUNTER_ID, &Timeout_local);
            /*Check if bus is busy*/
            Cdd_I2c_AsyncTransmit_PollingOFFBuscheck(sequenceId, HwUnit, Timeout_local, ChannelId_local);
            /*Reset timeout variable*/
            Timeout_local = 0;
            /*Check if sequence status is fail*/
            Cdd_I2c_AsyncTransmit_PollingOFFsequencecheck(sequenceId, HwUnit);
        }
        /*Check if the channel is configured for reading from I2C slave*/
        else if ((CDD_I2C_READ == Cdd_I2cChannelContainerLocal[ChannelId_local].Dir) && (status == CDD_I2C_OK))
        {
            /*Function call to set the master in receive mode*/
            Cdd_I2c_Set_Master_Receive_Mode(HwUnit);
            /*Function call to set number of bytes to read/write*/
            Cdd_I2c_Data_Count(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId_local].DataBufferLength);
            /*Update global variable with number of bytes to read*/
            DataBufferLengthHwUnit[HwUnit] = Cdd_I2cChannelContainerLocal[ChannelId_local].DataBufferLength;
            /*Disable global interrupts*/
            SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
            /*Function call to disable local interrupts*/
            Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
            /*Function call to clear all I2C related interrupts*/
            Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
            /*Function call to enable configurator selected interrupts*/
            Cdd_I2c_Enable_interrupts(HwUnit);
            /*Enable global interrupts*/
            SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
            /*Get initial value for timeout period*/
            (void)GetCounterValue((CounterType)CDD_I2C_OS_COUNTER_ID, &Timeout_local);
            /*Check if bus is busy*/
            Cdd_I2c_AsyncTransmit_PollingOFFBuscheck(sequenceId, HwUnit, Timeout_local, ChannelId_local);
            /*Reset timeout variable*/
            Timeout_local = 0;
            /*Check if sequence status is fail*/
            Cdd_I2c_AsyncTransmit_PollingOFFsequencecheck(sequenceId, HwUnit);
        }
        else
        {
            /*Do Nothing*/
        }
    }

    return status;
}

static FUNC(void, CDD_I2C_CODE) Cdd_I2c_AsyncTransmit_PollingOFFBuscheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                                         uint32 Timeout, uint32 ChannelId)
{
    TickType Timeout_local = Timeout;
    while (CDD_I2C_BUS_BUSY == Cdd_I2cBusCheck(HwUnit))
    {
        /*Get elapsed time value*/
        if (1u == (Cdd_I2c_Timeout(Timeout_local, CDD_I2C_RESET_TIMEOUT)))
        {
            /*Call Cdd_I2c_SetHandling if bus is busy for more than specified time period*/
            Cdd_I2c_SetHandling(CddI2cArbitrationLossParam);
            Timeout_local = 0;
            /*Update channel status*/
            Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_BUSFAIL;
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
            /*Throw timeout error*/
            Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify(CDD_I2C_E_PARAM_TIMEOUT);
#endif
            /*Update sequence status to fail*/
            Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
            break;
        }
    }
}

static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingOFFsequencecheck(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit)
{
    uint8 status_break = CDD_I2C_OK;
    if (CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
    {
        /*Disable global interrupts*/
        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
        /*Function call to disable local interrupts*/
        Cdd_I2c_Disable_interrupts(HwUnit, (uint16) ~(CDD_I2C_ALL_INTERRUPTS));
        /*Function call to clear all I2C related interrupts*/
        Cdd_I2c_Clear_interrupts(HwUnit, CDD_I2C_ALL_INTERRUPTS_CLEAR);
        /*Function call to enable configurator selected interrupts*/
        Cdd_I2c_Enable_interrupts(HwUnit);
        /*Enable global interrupts*/
        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
        /*Break out of the for loop in case sequence is failed*/
        status_break = CDD_I2C_NOT_OK;
    }
    /*Function call to send a start signal on the bus in interrupt mode*/
    if (status_break == CDD_I2C_OK)
    {
        Cdd_I2c_Start(HwUnit);
    }
}

static FUNC(Std_ReturnType, CDD_I2C_CODE)
    Cdd_I2c_AsyncTransmit_PollingOFFsequenceupdate(Cdd_I2c_SequenceType sequenceId, uint8 HwUnit,
                                                   Cdd_I2c_AddressType SlaveAddress, uint32 ChannelId)
{
    uint8               status             = CDD_I2C_OK;
    Cdd_I2c_AddressType SlaveAddress_local = SlaveAddress;

    if (NULL_PTR == Cdd_I2cChannelContainerLocal[ChannelId].DataBuffer)
    {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        Cdd_I2cReportDetError(CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_PARAM_TRANS_BUFFER);
/*Async transmit called before setupEB*/
#endif
        Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
        /*Sequence status updated to fail*/
        status = CDD_I2C_NOT_OK;
    }
    if (status == CDD_I2C_OK)
    {
        /*Function call to set the addressing mode for the slave device*/
        Cdd_I2c_Set_Slave_Addressing_mode(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId].SlaveAddressScheme);
        /*Function call to set the slave address when device in master mode*/
        Cdd_I2c_Set_Slave_Address(HwUnit, SlaveAddress_local);
    }
    /*Check if channel is already in use*/
    if ((CDD_I2C_CH_RESULT_IN_PROGRESS == Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult) &&
        (status == CDD_I2C_OK))
    {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        /*Throw channel busy error*/
        Cdd_I2cSequenceContainer[sequenceId].SequenceErrorNotify(CDD_I2C_E_CHANNEL_BUSY);
#endif
        /*Sequence status updated to fail*/
        Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
        status                                              = CDD_I2C_NOT_OK;
    }
    if (status == CDD_I2C_OK)
    {
        /*Update channel result*/
        Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult = CDD_I2C_CH_RESULT_IN_PROGRESS;
    }

    return status;
}
#endif

/*
 *Design: MCAL-13631, MCAL-13672, MCAL-13673, MCAL-13692
 */
#if (STD_ON == CDD_I2C_CANCEL_API) /*STD_ON == CDD_I2C_CANCEL_API*/
FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_Cancel(Cdd_I2c_SequenceType sequenceId)
{
    uint8 status = CDD_I2C_OK;

#if (CDD_I2C_DEV_ERROR_DETECT == STD_ON)
    status = Cdd_I2C_checkCancelErrors(sequenceId);
#endif /* (CDD_I2C_DEV_ERROR_DETECT == STD_ON) */

    if (status == (Std_ReturnType)(CDD_I2C_OK))
    {
        status = Cdd_I2c_HWCancel(sequenceId);
    }
    else
    {
        /*Do Nothing*/
    }
    return status;
}
#endif /*STD_ON == CDD_I2C_CANCEL_API*/

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2C_checkCancelErrors(Cdd_I2c_SequenceType sequenceId)
{
    uint8 status = CDD_I2C_OK;

    if (CDD_I2C_UNINIT == CddI2cDrvState)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_CANCEL, CDD_I2C_E_UNINIT);
        /*Driver un-initialized*/
        status = CDD_I2C_NOT_OK;
    }
    if ((CDD_I2C_MAXIMUM_SEQUENCE_NUMBER <= sequenceId) && (status == (Std_ReturnType)CDD_I2C_OK))
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_CANCEL, CDD_I2C_E_PARAM_SEQUENCE);
        /*Sequence ID passed exceeds maximum sequences configured*/
        status = CDD_I2C_NOT_OK;
    }

    return status;
}
#endif /*STD_ON == CDD_I2C_DEV_ERROR_DETECT*/

static FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_HWCancel(Cdd_I2c_SequenceType sequenceId)
{
    uint8 i      = 0;
    uint8 status = CDD_I2C_OK;

    for (i = 0; i < CDD_I2C_MAX_QUEUE_SIZE; i++)
    {
        if (sequenceId == ((pCddI2cTransmissionQueue + i)->sequenceId))
        {
            if (CDD_I2C_SEQ_CANCELLED != Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult)
            {
                Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult = CDD_I2C_SEQ_CANCELLED;
                status                                              = CDD_I2C_OK;
                break;
            }
        }
    }
    return status;
}

/*
 *Design: MCAL-13629, MCAL-13674, MCAL-13675, MCAL-13693
 */
FUNC(Cdd_I2c_ChannelResultType, CDD_I2C_CODE) Cdd_I2c_GetResult(Cdd_I2c_ChannelType channelId)
{
    Cdd_I2c_ChannelResultType retval;
    retval = CDD_I2C_CH_RESULT_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == CddI2cDrvState)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_GET_RESULT, CDD_I2C_E_UNINIT);
        /*Driver un-initialized*/
    }

    else if (CDD_I2C_MAXIMUM_CHANNEL_NUMBER <= channelId)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_GET_RESULT, CDD_I2C_E_PARAM_CHANNEL);
        /*Channel ID passed exceeds maximum channels configured*/
    }

    else
#endif
    {
        retval = Cdd_I2cChannelContainerLocal[channelId].ChannelResult;
    }
    return retval;
}

/*
 *Design: MCAL-13630, MCAL-13676, MCAL-13677, MCAL-13694
 */
FUNC(Cdd_I2c_SeqResultType, CDD_I2C_CODE) Cdd_I2c_GetSequenceResult(Cdd_I2c_SequenceType sequenceId)
{
    Cdd_I2c_SeqResultType retval;
    retval = CDD_I2C_SEQ_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == CddI2cDrvState)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_GET_SEQUENCE_RESULT, CDD_I2C_E_UNINIT);
        /*Driver un-initialized*/
    }

    else if (CDD_I2C_MAXIMUM_SEQUENCE_NUMBER <= sequenceId)
    {
        Cdd_I2cReportDetError(CDD_I2C_SID_GET_SEQUENCE_RESULT, CDD_I2C_E_PARAM_SEQUENCE);
        /*Sequence ID passed exceeds maximum configured sequences*/
    }

    else
#endif
    {
        retval = Cdd_I2cSequenceContainerLocal[sequenceId].SeqResult;
    }
    return retval;
}

/*
 *Design: MCAL-13628, MCAL-13697
 */
#if (STD_ON == CDD_I2C_GET_STATUS_API) /*STD_ON == CDD_I2C_GET_STATUS_API*/
FUNC(Cdd_I2c_ComponentStatusType, CDD_I2C_CODE) Cdd_I2c_GetStatus(void)
{
    return CddI2cDrvState;
}
#endif /*STD_ON == CDD_I2C_GET_STATUS_API*/

/*
 *Design: MCAL-13634, MCAL-13695
 */
FUNC(void, CDD_I2C_CODE) Cdd_I2c_MainFunction(void)
{
    Cdd_I2c_Queue_obj *pTemp = pCddI2cTransmissionQueue;

    /*Execute below loop till next element of queue is not pointing to NULL*/
    while (NULL_PTR != pTemp)
    {
        /*Check if sequence is queued or not*/
        Cdd_I2c_HWMainFunction(pTemp);

        /*Once sequence is processed update pointer to next sequence entry*/
        pTemp = pTemp->pNext;
    }
}

static FUNC(void, CDD_I2C_CODE) Cdd_I2c_HWMainFunction(Cdd_I2c_Queue_obj *pTemp)
{
    volatile uint32 tempCount = CDD_I2C_QUEUE_TIMEOUT;

    static TickType Start_time = 0;
    if (CDD_I2C_QUEUE_TIMEOUT > 8U)
    {
        tempCount = CDD_I2C_QUEUE_TIMEOUT / 8U;
    }
    if (((pTemp->sequenceId) < CDD_I2C_MAXIMUM_SEQUENCE_NUMBER) &&
        (CDD_I2C_SEQ_QUEUED == Cdd_I2cSequenceContainerLocal[pTemp->sequenceId].SeqResult))
    {
        Cdd_I2c_AsyncTransmit(pTemp->sequenceId);
#if (STD_ON == CDD_I2C_POLLING_MODE)
        Cdd_I2c_PollingModeProcessingFromQueue(pTemp->sequenceId);
#endif
        /*Wait till sequence result is OK*/
    }

    if ((CDD_I2C_SEQ_OK != Cdd_I2cSequenceContainerLocal[pTemp->sequenceId].SeqResult))
    {
        if (Start_time == 0)
        {
            /*Get initial value for timeout period*/
            (void)GetCounterValue((CounterType)CDD_I2C_OS_COUNTER_ID, &Start_time);
        }
        if (1u == (Cdd_I2c_Timeout(Start_time, tempCount)))
        {
            /*Timeout occurred*/
            if (CDD_I2C_SEQ_FAILED != Cdd_I2cSequenceContainerLocal[pTemp->sequenceId].SeqResult)
            {
                Cdd_I2cSequenceContainerLocal[pTemp->sequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
            }

            Start_time        = 0;
            pTemp->sequenceId = 255;
        }
        else
        {
            /*Check the sequence*/
            if ((CDD_I2C_SEQ_OK == Cdd_I2cSequenceContainerLocal[pTemp->sequenceId].SeqResult))
            {
                /*Sequence passed. Reset the start time for next execution*/
                Start_time = 0;
            }
        }
    }
}

/*
 *Design: MCAL-13635, MCAL-13678, MCAL-13679, MCAL-13680, MCAL-13696
 */
#if (STD_ON == CDD_I2C_POLLING_MODE) /*STD_ON == CDD_I2C_POLLING_MODE*/
FUNC(void, CDD_I2C_CODE) Cdd_I2c_PollingModeProcessing(void)
{
    uint8 SequenceId = 0;
    uint8 ChannelId  = 0;
    uint8 i          = 0;
    uint8 HwUnit     = 0;

    /*Transmission/Reception for all sequences*/
    for (SequenceId = 0; SequenceId < CDD_I2C_MAXIMUM_SEQUENCE_NUMBER; SequenceId++)
    {
        if (CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult)
        {
            continue;
        }
        else if ((CDD_I2C_HW_UNIT_BUSY == CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance]))
        {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
            Cdd_I2cSequenceContainer[SequenceId].SequenceErrorNotify(CDD_I2C_E_HW_UNIT_BUSY);
/*Bus busy*/
#endif
            continue;
        }
        else
        {
            /*Do Nothing*/
        }
        /*Update driver status*/
        CddI2cDrvState = CDD_I2C_BUSY;
        /*Update hardware unit in use status*/
        CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance] = CDD_I2C_HW_UNIT_BUSY;
        HwUnit = Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance;

        for (i = 0; i < Cdd_I2cSequenceContainerLocal[SequenceId].MaxChannels; i++)
        {
            /*Find the channel ID number*/
            ChannelId = Cdd_I2cSequenceContainerLocal[SequenceId].ChannelList[i];
            if ((CDD_I2C_READ == Cdd_I2cChannelContainerLocal[ChannelId].Dir))
            {
                Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult = CDD_I2C_SEQ_PENDING;
                Cdd_I2c_PollingModeProcessing_channelupdate(SequenceId, ChannelId, HwUnit);
            }
        }
        /*Update Hardware unit status*/
        CddI2cHwUnitStatus[Cdd_I2cSequenceContainerLocal[SequenceId].HwInstance] = CDD_I2C_HW_UNIT_FREE;
        CddI2cDrvState                                                           = CDD_I2C_IDLE;
        if ((CDD_I2C_SEQ_FAILED == Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult) &&
            (CDD_I2C_READ == Cdd_I2cChannelContainerLocal[ChannelId].Dir))
        {
            Cdd_I2c_Enqueue(SequenceId);
            break;
        }
    }
}

static FUNC(void, CDD_I2C_CODE)
    Cdd_I2c_PollingModeProcessing_channelupdate(uint8 SequenceId, uint8 ChannelId, uint8 HwUnit)
{
    uint16 SlaveAddress = 0;
    uint8  status       = CDD_I2C_OK;

    /*Check if channel direction is read*/
    if (CDD_I2C_READ == Cdd_I2cChannelContainerLocal[ChannelId].Dir)
    {
        if (CDD_I2C_CH_RESULT_IN_PROGRESS == Cdd_I2cChannelContainerLocal[ChannelId].ChannelResult)
        {
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
            Cdd_I2cSequenceContainer[SequenceId].SequenceErrorNotify(CDD_I2C_E_CHANNEL_BUSY);
/*Channel busy*/
#endif
            Cdd_I2cSequenceContainerLocal[SequenceId].SeqResult = CDD_I2C_SEQ_FAILED;
            status                                              = CDD_I2C_NOT_OK;
        }
        if (status == CDD_I2C_OK)
        {
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
            /*Function call to set the addressing mode for the slave device*/
            Cdd_I2c_Set_Slave_Addressing_mode(HwUnit, Cdd_I2cChannelContainerLocal[ChannelId].SlaveAddressScheme);
            /*Function call to set the slave address when device in master mode*/
            Cdd_I2c_Set_Slave_Address(HwUnit, SlaveAddress);
            Cdd_I2c_Polling_Mode_Receive(HwUnit, ChannelId, SequenceId);
        }
    }
}
#endif /*STD_ON == CDD_I2C_POLLING_MODE*/

/*
 *Design: MCAL-13633, MCAL-13698
 */
FUNC(void, CDD_I2C_CODE) Cdd_I2c_SetHandling(Cdd_I2c_HandlingType handling)
{
    uint8 i = 0;

    if (CDD_I2C_BURST_MODE == handling)
    {
        (void)Cdd_I2c_DeInit();
    }
    if (CDD_I2C_RECURRENT_MODE == handling)
    {
        for (i = 0; i < CDD_I2C_HW_UNITS_USED; i++)
        {
            Cdd_I2c_Stop(pCddI2cInitParams->CddI2cHwCfgPtr[i].HwInstance);
            (void)Cdd_I2c_DeInit();
            Cdd_I2c_Init((Cdd_I2c_ConfigType *)NULL_PTR);
        }
    }
    else
    {
        /*Do Nothing*/
    }
}

/*
 *Design: MCAL-21350, MCAL-21351
 */
#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_RegisterReadback(uint8 HwInstance, P2VAR(Cdd_I2c_RegisterReadbackType, AUTOMATIC, CDDI2C_APPL_DATA) RegRbPtr)
{
    uint8 retVal = CDD_I2C_OK;

    if (CDD_I2C_UNINIT == CddI2cDrvState)
    {
        retVal = CDD_I2C_NOT_OK;
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        Cdd_I2cReportDetError(CDD_I2C_SID_REGISTERREADBACK, CDD_I2C_E_UNINIT);
#endif
    }
    else if (NULL_PTR == RegRbPtr)
    {
        retVal = CDD_I2C_NOT_OK;
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        Cdd_I2cReportDetError(CDD_I2C_SID_REGISTERREADBACK, CDD_I2C_E_PARAM_CONFIG);
#endif
    }
    else
    {
        retVal = Cdd_I2c_HWRegisterReadback(HwInstance, RegRbPtr);
    }

    return (retVal);
}
#endif /* #if (STD_ON == CDD_I2C_REGISTER_READBACK_API) */

#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
