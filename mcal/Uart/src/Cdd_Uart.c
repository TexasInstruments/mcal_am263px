/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Cdd_Uart.c
 *
 *  \brief    This file contains Complex Device Driver for UART
 *
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_Uart.c
 *    Component:  AM263X Complex Device Driver
 *       Module:  UART
 *    Generator:  None
 *
 *  Description: This component provides services for initStatus and control of the UART between
 *different core in the this Multicore SoC.
 *********************************************************************************************************************/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_Uart.h"
#include "Cdd_Uart_Priv.h"
#if (CDD_UART_DMA_ENABLE == STD_ON)
#include "Cdd_Dma.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((CDD_UART_AR_RELEASE_MAJOR_VERSION != (4U)) || (CDD_UART_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (CDD_UART_AR_RELEASE_REVISION_VERSION != (1U)))
#error "CDD UART: AUTOSAR Version Numbers of CDD UART are different!!"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((CDD_UART_SW_MAJOR_VERSION != (10U)) || (CDD_UART_SW_MINOR_VERSION != (2U)))
#error "CDD UART: Software Version Numbers are inconsistent!!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define CDD_UART_START_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Uart_MemMap.h"
/** \brief CDD UART driver status */
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
static VAR(Cdd_Uart_StatusType, CDD_VAR_ZERO_INIT) CddUart_DriverStatus = CDD_UART_UNINIT;
#endif
#define CDD_UART_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Uart_MemMap.h"

#define CDD_UART_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Uart_MemMap.h"
/** \brief Transaction objects for read and write */
CddUart_Transaction     CddUart_readTransaction[CDD_UART_NUM_CHANNELS], CddUart_writeTransaction[CDD_UART_NUM_CHANNELS];
/** \brief CDD UART Notification callback functions */
Cdd_Uart_NotifCallbacks CddUart_NotificationCallbacks[CDD_UART_NUM_CHANNELS];
/** \brief CDD UART Init objects */
CddUart_InitObject      CddUart_InitObjects[CDD_UART_NUM_CHANNELS];
/** \brief CDD UART channel handles */
CddUart_Object          CddUart_ChannelObjects[CDD_UART_NUM_CHANNELS];
#define CDD_UART_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Uart_MemMap.h"

/* ========================================================================== */
/*                       Internal Function Definitions                        */
/* ========================================================================== */

#define CDD_UART_START_SEC_CODE
#include "Cdd_Uart_MemMap.h"

#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
static inline void CddUart_ReportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(CDD_UART_MODULE_ID, CDD_UART_INSTANCE_ID, apiId, errorId);
}

static Std_ReturnType Cdd_Uart_TransferParamsDetCheck(uint8 APIServiceID, uint8 ChannelID,
                                                      P2CONST(void, AUTOMATIC, CDD_UART_APPL_DATA) ParameterPointer,
                                                      uint32 Count)
{
    Std_ReturnType status = (Std_ReturnType)E_OK;
    if (CDD_UART_UNINIT == CddUart_DriverStatus)
    {
        CddUart_ReportDetError(APIServiceID, CDD_UART_E_UNINIT);
        status = (Std_ReturnType)E_NOT_OK;
    }
    if (((Std_ReturnType)E_OK == status) && (ChannelID >= CDD_UART_NUM_CHANNELS))
    {
        CddUart_ReportDetError(APIServiceID, CDD_UART_E_INVALID_CHANNEL);
        status = (Std_ReturnType)E_NOT_OK;
    }
    if (((Std_ReturnType)E_OK == status) && (NULL_PTR == ParameterPointer))
    {
        CddUart_ReportDetError(APIServiceID, CDD_UART_E_PARAM_POINTER);
        status = (Std_ReturnType)E_NOT_OK;
    }
    if (((Std_ReturnType)E_OK == status) && ((uint32)0U == Count))
    {
        CddUart_ReportDetError(APIServiceID, CDD_UART_E_PARAM_VALUE);
        status = (Std_ReturnType)E_NOT_OK;
    }

    return status;
}

static Std_ReturnType Cdd_Uart_InitDetCheck(P2CONST(Cdd_Uart_CfgType, AUTOMATIC, CDD_UART_APPL_DATA)
                                                ConfigurationPointer)
{
    Std_ReturnType status = (Std_ReturnType)E_NOT_OK;
    if (CDD_UART_UNINIT != CddUart_DriverStatus)
    {
        CddUart_ReportDetError(CDD_UART_INIT_SERVICE_ID, CDD_UART_E_ALREADY_INITIALIZED);
    }
    else if (ConfigurationPointer == NULL_PTR)
    {
        CddUart_ReportDetError(CDD_UART_INIT_SERVICE_ID, CDD_UART_E_PARAM_POINTER);
    }
    else
    {
        status = (Std_ReturnType)E_OK;
    }

    return status;
}

#endif /* (STD_ON == CDD_UART_DEV_ERROR_DETECT) */

#define CDD_UART_STOP_SEC_CODE
#include "Cdd_Uart_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_UART_START_SEC_CODE
#include "Cdd_Uart_MemMap.h"

/*
 * Design : MCAL-22636
 */
#if (STD_ON == CDD_UART_VERSION_INFO_API)
FUNC(void, CDD_UART_CODE)
Cdd_Uart_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_UART_APPL_DATA) VersionInfoPtr)
{
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        CddUart_ReportDetError(CDD_UART_GETVERSIONINFO_SERVICE_ID, CDD_UART_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON == CDD_UART_DEV_ERROR_DETECT) */
    {
        VersionInfoPtr->vendorID         = (uint16)CDD_UART_VENDOR_ID;
        VersionInfoPtr->moduleID         = (uint16)CDD_UART_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)CDD_UART_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)CDD_UART_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)CDD_UART_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON == CDD_UART_VERSION_INFO_API) */

/*
 * Design: MCAL-22671
 */
#if (STD_ON == CDD_UART_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CDD_UART_CODE)
Cdd_Uart_RegisterReadback(uint8 ChannelID, P2VAR(CddUart_RegisterReadbackType, AUTOMATIC, CDD_UART_CFG) RegisterSetPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    if (CDD_UART_INIT != CddUart_DriverStatus)
    {
        CddUart_ReportDetError(CDD_UART_REGISTERREADBACK_SERVICE_ID, CDD_UART_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == RegisterSetPtr)
    {
        CddUart_ReportDetError(CDD_UART_REGISTERREADBACK_SERVICE_ID, CDD_UART_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        if (ChannelID >= (uint8)CDD_UART_NUM_CHANNELS)
        {
            CddUart_ReportDetError(CDD_UART_REGISTERREADBACK_SERVICE_ID, CDD_UART_E_INVALID_CHANNEL);
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
#endif

    /* Check if return value is still OK for no DET */
    if ((Std_ReturnType)E_OK == retVal)
    {
        /* Readback IP-specific registers */
        Uart_Cdd_RegisterReadback(&CddUart_ChannelObjects[ChannelID], RegisterSetPtr);
    }

    /* Status return */
    return (retVal);
}
#endif

/*
 * Design: MCAL-22584
 *
 */
FUNC(void, CDD_UART_CODE)
Cdd_Uart_Init(P2CONST(Cdd_Uart_CfgType, AUTOMATIC, CDD_UART_CFG) ConfigurationPtr)
{
    const Cdd_Uart_CfgType* ConfigPtr = (Cdd_Uart_CfgType*)NULL_PTR;
#if (STD_ON == CDD_UART_PRE_COMPILE_VARIANT)
    if (ConfigurationPtr == NULL_PTR)
    {
        ConfigPtr = &CDD_UART_INIT_CONFIG_PC;
    }
    else
#endif /* (STD_ON == CDD_UART_PRE_COMPILE_VARIANT) */
    {
        ConfigPtr = ConfigurationPtr;
    }
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    if ((Std_ReturnType)E_OK == Cdd_Uart_InitDetCheck(ConfigPtr))
#endif
    {
        sint32 initStatus;
        for (uint8 channel = 0; channel < ConfigPtr->netChannels; ++channel)
        {
            CddUart_ChannelObjects[channel].hUartInit = &CddUart_InitObjects[channel];
            Cdd_Uart_Object_Configuration_Mapping(&CddUart_ChannelObjects[channel], &ConfigPtr->channelCfg[channel]);

            initStatus = Uart_Cdd_init(&CddUart_ChannelObjects[channel]);
            if (initStatus != MCAL_SystemP_SUCCESS)
            {
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
                CddUart_ReportDetError(CDD_UART_INIT_SERVICE_ID, CDD_UART_E_PARAM_VALUE);
#endif
            }
            else
            {
                CddUart_NotificationCallbacks[channel].uartNotificationReadHandler =
                    ConfigPtr->channelCfg[channel].uartNotificationHandlers.uartNotificationReadHandler;
                CddUart_NotificationCallbacks[channel].uartNotificationWriteHandler =
                    ConfigPtr->channelCfg[channel].uartNotificationHandlers.uartNotificationWriteHandler;
                CddUart_NotificationCallbacks[channel].uartNotificationErrorHandler =
                    ConfigPtr->channelCfg[channel].uartNotificationHandlers.uartNotificationErrorHandler;
#if (CDD_UART_DEV_ERROR_DETECT == STD_ON)
                /* Setting global UART status to INIT once initialization completes */
                CddUart_DriverStatus = CDD_UART_INIT;
#endif
            }
        }
    }
}

/*
 * Design: MCAL-22585
 */
#if (STD_ON == CDD_UART_DEINIT_API)
FUNC(void, CDD_UART_CODE) Cdd_Uart_DeInit(void)
{
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    if ((CDD_UART_UNINIT == CddUart_DriverStatus))
    {
        CddUart_ReportDetError(CDD_UART_DEINIT_SERVICE_ID, CDD_UART_E_UNINIT);
    }
    else
    {
#endif
        sint32 deInitStatus;
        for (uint8 channel = 0; channel < CDD_UART_NUM_CHANNELS; ++channel)
        {
            deInitStatus = Uart_Cdd_deInit(&CddUart_ChannelObjects[channel]);
            if (deInitStatus == MCAL_SystemP_SUCCESS)
            {
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
                /* Setting global UART status to UNINITialized on success */
                CddUart_DriverStatus = CDD_UART_UNINIT;
            }
            else
            {
                CddUart_ReportDetError(CDD_UART_DEINIT_SERVICE_ID, CDD_UART_E_INVALID_EVENT);
#endif /* #if (STD_ON == CDD_UART_DEV_ERROR_DETECT) */
            }
        }
#if (CDD_UART_DEV_ERROR_DETECT == STD_ON)
    }
#endif
}
#endif /* (STD_ON == CDD_UART_DEINIT_API) */

/*
 * Design: MCAL-22587
 */
#if (STD_ON == CDD_UART_WRITE_API)
FUNC(Std_ReturnType, CDD_UART_CODE)
Cdd_Uart_Write(uint8 ChannelID, P2VAR(CddUartDataBufferType, AUTOMATIC, CDD_UART_APPL_DATA) SrcBufferPtr, uint32 Count,
               uint32 Timeout)
{
    Std_ReturnType writeStatus = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    if (Cdd_Uart_TransferParamsDetCheck(CDD_UART_WRITEDATA_SERVICE_ID, ChannelID, SrcBufferPtr, Count) ==
        (Std_ReturnType)E_OK)
#endif
    {
        CddUart_writeTransaction[ChannelID].buf     = SrcBufferPtr;
        CddUart_writeTransaction[ChannelID].count   = Count;
        CddUart_writeTransaction[ChannelID].timeout = Timeout;
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_POLLING)
        {
            if (Uart_Cdd_writeEx(&CddUart_ChannelObjects[ChannelID], &CddUart_writeTransaction[ChannelID]) ==
                MCAL_SystemP_SUCCESS)
            {
                writeStatus = (Std_ReturnType)E_OK;
            }
        }
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_INTERRUPT)
        {
            if (Uart_Cdd_writeIntrEx(&CddUart_ChannelObjects[ChannelID], &CddUart_writeTransaction[ChannelID]) ==
                MCAL_SystemP_SUCCESS)
            {
                writeStatus = (Std_ReturnType)E_OK;
            }
        }
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_DMA)
        {
#if (CDD_UART_DMA_ENABLE == STD_ON)
            if (Uart_Cdd_writeDmaEx(&CddUart_ChannelObjects[ChannelID], &CddUart_writeTransaction[ChannelID]) ==
                MCAL_SystemP_SUCCESS)
#endif
            {
                writeStatus = (Std_ReturnType)E_OK;
            }
        }
    }

    return writeStatus;
}
#endif /* (STD_ON == CDD_UART_WRITE_API) */

/*
 * Design: MCAL-22586
 */
#if (STD_ON == CDD_UART_READ_API)
FUNC(Std_ReturnType, CDD_UART_CODE)
Cdd_Uart_Read(uint8 ChannelID, P2VAR(CddUartDataBufferType, AUTOMATIC, CDD_UART_APPL_DATA) DestBufferPtr, uint32 Count,
              uint32 Timeout)
{
    Std_ReturnType readStatus = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    if (Cdd_Uart_TransferParamsDetCheck(CDD_UART_READDATA_SERVICE_ID, ChannelID, DestBufferPtr, Count) ==
        (Std_ReturnType)E_OK)
#endif
    {
        CddUart_readTransaction[ChannelID].buf     = DestBufferPtr;
        CddUart_readTransaction[ChannelID].count   = Count;
        CddUart_readTransaction[ChannelID].timeout = Timeout;
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_POLLING)
        {
            if (Uart_Cdd_readEx(&CddUart_ChannelObjects[ChannelID], &CddUart_readTransaction[ChannelID]) ==
                MCAL_SystemP_SUCCESS)
            {
                readStatus = (Std_ReturnType)E_OK;
            }
        }
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_INTERRUPT)
        {
            if (Uart_Cdd_readIntrEx(&CddUart_ChannelObjects[ChannelID], &CddUart_readTransaction[ChannelID]) ==
                MCAL_SystemP_SUCCESS)
            {
                readStatus = (Std_ReturnType)E_OK;
            }
        }
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_DMA)
        {
#if (CDD_UART_DMA_ENABLE == STD_ON)
            if (Uart_Cdd_readDmaEx(&CddUart_ChannelObjects[ChannelID], &CddUart_readTransaction[ChannelID]) ==
                MCAL_SystemP_SUCCESS)
#endif
            {
                readStatus = (Std_ReturnType)E_OK;
            }
        }
    }

    return readStatus;
}
#endif /* (STD_ON == CDD_UART_READ_API) */

/*
 * Design: MCAL-22589
 */
#if (STD_ON == CDD_UART_CANCEL_API)
FUNC(boolean, CDD_UART_CODE) Cdd_Uart_Cancel(uint8 ChannelID, CddUartDataDirectionType TransferType)
{
    boolean cancelStatus = FALSE;
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    if (Cdd_Uart_TransferParamsDetCheck(
            CDD_UART_CANCEL_SERVICE_ID, ChannelID,
            (TransferType == UART_READ_TRANSFER_TYPE)
                ? CddUart_ChannelObjects[ChannelID].readTrans
                : ((TransferType == UART_WRITE_TRANSFER_TYPE) ? CddUart_ChannelObjects[ChannelID].writeTrans
                                                              : NULL_PTR),
            1U) == (Std_ReturnType)E_OK)
#endif
    {
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_DMA)
        {
#if (CDD_UART_DMA_ENABLE == STD_ON)
            if (((TransferType == UART_WRITE_TRANSFER_TYPE)
                     ? Uart_Cdd_writeCancelDma(&CddUart_ChannelObjects[ChannelID],
                                               CddUart_ChannelObjects[ChannelID].writeTrans)
                     : Uart_Cdd_readCancelDma(&CddUart_ChannelObjects[ChannelID],
                                              CddUart_ChannelObjects[ChannelID].readTrans)) == MCAL_SystemP_SUCCESS)
            {
                cancelStatus = TRUE;
            }
#endif
        }
        else
        {
            if (((TransferType == UART_WRITE_TRANSFER_TYPE)
                     ? Uart_Cdd_writeCancel(&CddUart_ChannelObjects[ChannelID],
                                            CddUart_ChannelObjects[ChannelID].writeTrans)
                     : Uart_Cdd_readCancel(&CddUart_ChannelObjects[ChannelID],
                                           CddUart_ChannelObjects[ChannelID].readTrans)) == MCAL_SystemP_SUCCESS)
            {
                cancelStatus = TRUE;
            }
        }
    }
    return cancelStatus;
}
#endif /* (STD_ON == CDD_UART_CANCEL_API) */

/*
 * Design: MCAL-22588
 */
#if (STD_ON == CDD_UART_GETREMAININGWORDS_API)
FUNC(uint32, CDD_UART_CODE)
Cdd_Uart_GetRemainingWords(uint8 ChannelID, CddUartDataDirectionType TransferType)
{
    uint32 remainingWords = 0U;
#if (STD_ON == CDD_UART_DMA_ENABLE)
    uint32 channelIndex = 0U, paramIndex = 0U;
#endif

    Std_ReturnType status = (Std_ReturnType)E_OK;
#if (STD_ON == CDD_UART_DEV_ERROR_DETECT)
    status = (Std_ReturnType)E_NOT_OK;
    if (CDD_UART_UNINIT == CddUart_DriverStatus)
    {
        CddUart_ReportDetError(CDD_UART_GETREMAININGWORDS_SERVICE_ID, CDD_UART_E_UNINIT);
    }
    else if (ChannelID >= CDD_UART_NUM_CHANNELS)
    {
        CddUart_ReportDetError(CDD_UART_GETREMAININGWORDS_SERVICE_ID, CDD_UART_E_INVALID_CHANNEL);
    }
    else if ((TransferType != UART_WRITE_TRANSFER_TYPE) && (TransferType != UART_READ_TRANSFER_TYPE))
    {
        CddUart_ReportDetError(CDD_UART_GETREMAININGWORDS_SERVICE_ID, CDD_UART_E_PARAM_VALUE);
    }
    else
    {
        status = (Std_ReturnType)E_OK;
    }
#endif
    if ((Std_ReturnType)E_OK == status)
    {
#if (CDD_UART_DMA_ENABLE == STD_ON)
        if (CddUart_ChannelObjects[ChannelID].hUartInit->transferMode == CDD_UART_MODE_DMA)
        {
            CDD_EDMACCEDMACCPaRAMEntry currentPaRAM;
            if (TransferType == UART_WRITE_TRANSFER_TYPE)
            {
                Cdd_Dma_GetParam(CddUart_ChannelObjects[ChannelID].dmaTxHandleId, channelIndex, paramIndex,
                                 &currentPaRAM);
            }
            else
            {
                Cdd_Dma_GetParam(CddUart_ChannelObjects[ChannelID].dmaRxHandleId, channelIndex, paramIndex,
                                 &currentPaRAM);
            }
            remainingWords =
                (uint32)((uint32)currentPaRAM.aCnt * (uint32)currentPaRAM.bCnt * (uint32)currentPaRAM.cCnt);
        }
        else
#endif
        {
            if (TransferType == UART_WRITE_TRANSFER_TYPE)
            {
                remainingWords = CddUart_ChannelObjects[ChannelID].writeSizeRemaining;
            }
            else
            {
                remainingWords = CddUart_ChannelObjects[ChannelID].readSizeRemaining;
            }
        }
    }
    return remainingWords;
}
#endif /* (STD_ON == CDD_UART_GETREMAININGWORDS_API) */

/* Invoke Callback functions */
void Uart_Cdd_readCompleteCallback(CddUart_Handle hUart)
{
    uint32 channelIndex = 0U;

    if (NULL_PTR != hUart)
    {
        channelIndex = Cdd_Uart_GetChannelIndex(hUart->channelID);

        /* Invoke the notification handler function */
        (*CddUart_NotificationCallbacks[channelIndex].uartNotificationReadHandler)();
    }
}

void Uart_Cdd_writeCompleteCallback(CddUart_Handle hUart)
{
    uint32 channelIndex = 0U;

    if (NULL_PTR != hUart)
    {
        channelIndex = Cdd_Uart_GetChannelIndex(hUart->channelID);

        /* Invoke the notification handler function */
        (*CddUart_NotificationCallbacks[channelIndex].uartNotificationWriteHandler)();
    }
}

void Uart_Cdd_errorCallback(CddUart_Handle hUart)
{
    uint32 channelIndex = 0U;

    if (NULL_PTR != hUart)
    {
        channelIndex = Cdd_Uart_GetChannelIndex(hUart->channelID);

        /* Invoke the notification handler function */
        (*CddUart_NotificationCallbacks[channelIndex].uartNotificationErrorHandler)();
    }
}

#define CDD_UART_STOP_SEC_CODE
#include "Cdd_Uart_MemMap.h"
