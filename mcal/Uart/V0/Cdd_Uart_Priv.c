/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     Cdd_Uart_Priv.c
 *
 *  \brief    This file contains some internal functions for UART Complex Device Driver
 *
 */
/* -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_Uart_Priv.c
 *    Component:  UART Complex Device Driver
 *       Module:  UART
 *    Generator:  None
 *
 *  Description: This component provides services for initialization and control of the UART between
 *different core in the this Multicore SoC.
 *********************************************************************************************************************/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_Uart.h"
#include "Cdd_Uart_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define CDD_UART_START_SEC_VAR_NO_INIT_32
#include "Cdd_Uart_MemMap.h"
extern uint32 baseAddresses[CDD_UART_MAXIMUM_CHANNELS];
#define CDD_UART_STOP_SEC_VAR_NO_INIT_32
#include "Cdd_Uart_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_UART_START_SEC_CODE
#include "Cdd_Uart_MemMap.h"

/** \brief Configuration to UART Handle Map Function */
FUNC(void, CDD_UART_CODE)
Cdd_Uart_Object_Configuration_Mapping(CddUart_Handle CddUartHandle,
                                      P2CONST(Cdd_Uart_ConfigType, AUTOMATIC, CDD_UART_CFG) ChannelCfgPtr)
{
    CddUartHandle->channelID                 = (uint8)ChannelCfgPtr->uartHwUnitID;
    CddUartHandle->baseAddr                  = baseAddresses[ChannelCfgPtr->uartHwUnitID];
    CddUartHandle->state                     = MCAL_STATE_RESET;
    CddUartHandle->hUartInit->inputClkFreq   = ChannelCfgPtr->uartClockFrequency;
    CddUartHandle->hUartInit->baudRate       = ChannelCfgPtr->uartBaudRate;
    CddUartHandle->hUartInit->dataLength     = ChannelCfgPtr->uartWordLength;
    CddUartHandle->hUartInit->stopBits       = ChannelCfgPtr->uartStopBits;
    CddUartHandle->hUartInit->readReturnMode = ChannelCfgPtr->uartReadReturnMode;
    CddUartHandle->hUartInit->parityType     = ChannelCfgPtr->uartParity;
    CddUartHandle->hUartInit->operMode       = ChannelCfgPtr->uartOperatingMode;
    CddUartHandle->hUartInit->rxTrigLvl      = ChannelCfgPtr->uartRXTriggerLevel;
    CddUartHandle->hUartInit->txTrigLvl      = ChannelCfgPtr->uartTXTriggerLevel;
    if (ChannelCfgPtr->uartRXTriggerLevel > (uint32)CDD_UART_TRIGGER_LEVEL_1)
    {
        CddUartHandle->hUartInit->hwFlowControl = (uint32)TRUE;
    }
    else
    {
        CddUartHandle->hUartInit->hwFlowControl = (uint32)FALSE;
    }
    CddUartHandle->hUartInit->hwFlowControlThr = ChannelCfgPtr->uartHwFlowControlThreshold;
    CddUartHandle->hUartInit->transferMode     = ChannelCfgPtr->uartIOMode;
    CddUartHandle->dmaTxHandleId               = ChannelCfgPtr->edmaXbarTxHandleID;
    CddUartHandle->dmaRxHandleId               = ChannelCfgPtr->edmaXbarRxHandleID;
}

/* To get the Channel Index */
uint32 Cdd_Uart_GetChannelIndex(uint8 hUart_Channel_ID)
{
    uint32 Idx = 0U;

    for (uint32 index = 0U; index < CDD_UART_NUM_CHANNELS; index++)
    {
        if (CddUart_ChannelObjects[index].channelID == hUart_Channel_ID)
        {
            Idx = index;
            break;
        }
    }

    return Idx;
}

/** \brief UART Hardware IP instance based Register Readback Function. */
#if (STD_ON == CDD_UART_REGISTER_READBACK_API)
FUNC(void, CDD_UART_CODE)
Uart_Cdd_RegisterReadback(CddUart_Handle CddUartHandle,
                          P2VAR(CddUart_RegisterReadbackType, AUTOMATIC, CDD_UART_CFG) RegisterSetPtr)
{
    uint32 baseAddr      = CddUartHandle->baseAddr /* Should be same as baseAddresses[CddUartHandle->channelID] */;
    RegisterSetPtr->MVR  = HW_RD_REG32(baseAddr + UART_MVR);
    RegisterSetPtr->SYSC = HW_RD_REG32(baseAddr + UART_SYSC);
    RegisterSetPtr->SYSS = HW_RD_REG32(baseAddr + UART_SYSS);
    RegisterSetPtr->IER  = HW_RD_REG32(baseAddr + UART_IER);
}
#endif /* (STD_ON == CDD_UART_REGISTER_READBACK_API) */

#define CDD_UART_STOP_SEC_CODE
#include "Cdd_Uart_MemMap.h"
