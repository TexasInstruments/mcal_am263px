/*********************************************************************************************************************
 *  COPYRIGHT
 *  ------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright 2022 Texas Instruments Inc.  All rights reserved.
 *
 *  \endverbatim
 *  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *  File:       Lin_Priv.h
 *  Project:    AM263x MCAL
 *  Module:     Lin Driver
 *  Generator:  None
 *
 *  Description:  This file contains interface header for Port private functions
 *
 *--------------------------------------------------------------------------------------------------------------------
 * Author:  Piyush Panditrao
 *--------------------------------------------------------------------------------------------------------------------
 * Revision History (top to bottom: first revision to last revision)
 *--------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *--------------------------------------------------------------------------------------------------------------------
 * 00.01.00       11Nov2012    Author's name        0000000000000    Initial version
 *
 *********************************************************************************************************************/
#ifndef LIN_PRIV_H
#define LIN_PRIV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Other Header Files
 *********************************************************************************************************************/
#include "hw_types.h"
#include "cslr_lin.h"
/*********************************************************************************************************************
 * Version Check (if required)
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Exported Preprocessor #define Constants
 *********************************************************************************************************************/
/* Lin Interrupt Flag Parameters */
#define LIN_INT_WAKEUP  (0x00000002U) /* Wakeup */
#define LIN_INT_TO      (0x00000010U) /* Time out */
#define LIN_INT_TOAWUS  (0x00000040U) /* Time out after wakeup signal */
#define LIN_INT_TOA3WUS (0x00000080U) /* Time out after 3 wakeup signals */
#define LIN_INT_TX      (0x00000100U) /* Transmit buffer ready */
#define LIN_INT_RX      (0x00000200U) /* Receive buffer ready */
#define LIN_INT_ID      (0x00002000U) /* Received matching identifier */
#define LIN_INT_PE      (0x01000000U) /* Parity error */
#define LIN_INT_OE      (0x02000000U) /* Overrun error */
#define LIN_INT_FE      (0x04000000U) /* Framing error */
#define LIN_INT_NRE     (0x08000000U) /* No response error */
#define LIN_INT_ISFE    (0x10000000U) /* Inconsistent sync field error */
#define LIN_INT_CE      (0x20000000U) /* Checksum error */
#define LIN_INT_PBE     (0x40000000U) /* Physical bus error */
#define LIN_INT_BE      (0x80000000U) /* Bit error */
#define LIN_INT_ALL     (0xFF0023D2U) /* All interrupts */
/*********************************************************************************************************************
 * Exported Preprocessor #define Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Exported Type Declarations
 *********************************************************************************************************************/
typedef enum Lin_ChannelActivityStatusTag
{
    LIN_CHANNEL_IDLE,
    LIN_CHANNEL_TX_STARTED,
    LIN_CHANNEL_RX_STARTED,
} Lin_ChannelActivityStatusType;

typedef enum Lin_ChannelNetworkStatusTag
{
    LIN_CHANNEL_OPERATIONAL,
    LIN_CHANNEL_SLEEP_PENDING,
    LIN_CHANNEL_SLEEP
} Lin_ChannelNetworkStatusType;

typedef struct Lin_ChannelStatusTag
{
    Lin_ChannelActivityStatusType linChannelActivityStatus;
    Lin_ChannelNetworkStatusType  linChannelNetworkStatus;
} Lin_ChannelStatusType;

/*********************************************************************************************************************
 * Exported Object Declarations
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  Exported Function Prototypes
 *********************************************************************************************************************/
/**
 * \brief   This API will configure Lin IP instance.
 *
 * \param   linChannel      LIN channel to be addressed.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE)
Lin_HwUnitConfig(P2CONST(Lin_ChannelType, AUTOMATIC, LIN_APPL_DATA) linChannel);

/**
 * \brief   This API will copy the driver object pointer to be used while servicing ISR.
 *
 * \param   linChannel      Pointer to driver object.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE) Lin_SetDriverCfgPtr(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_DATA) drvObj);

/**
 * \brief   This API will copy data into LIN_TDx registers and start transmission.
 *
 * \param   linChannel      LIN channel to be addressed.
 * \param   linChannelActivityStatus      Pointer to current activity staus of the channel.
 * \param   pduInfoPtr     Pointer to PDU to be sent.
 *
 * \return  E_OK: Send command has been accepted.
 *          E_NOT_OK: Send command has not been accepted, development or production error occurred.
 *
 **/
FUNC(Std_ReturnType, LIN_CODE)
Lin_SendData(P2CONST(Lin_ChannelType, AUTOMATIC, LIN_APPL_DATA) linChannel,
             P2VAR(Lin_ChannelActivityStatusType, AUTOMATIC, LIN_APPL_DATA) linChannelActivityStatus,
             P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) pduInfoPtr);

/**
 * \brief   This API will copy the received data into sduPtr.
 *
 * \param   channelID      LIN channel to be addressed.
 * \param   base           Base address of Lin Instance.
 * \param   sduPtr         Pointer to Pointer to SDU to be received.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE)
Lin_GetData(uint32 channelID, uint32 base, P2VAR(uint8 *, AUTOMATIC, LIN_APPL_CONST) sduPtr);

/**
 * \brief   This API will fetch transmit status.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  Lin_StatusType.
 *
 **/
FUNC(Lin_StatusType, LIN_CODE) Lin_FetchTxStatus(uint32 base);

/**
 * \brief   This API will fetch receive status.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  Lin_StatusType.
 *
 **/
FUNC(Lin_StatusType, LIN_CODE) Lin_FetchRxStatus(uint32 base);

/**
 * \brief   This API will send wakeup signal on Lin bus.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE) Lin_SendWakeupSignal(uint32 base);

/**
 * \brief   This API will enter local low power mode for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   enable      If TRUE low power will be entered; if FALSE Lin comes out of low power mode.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE) Lin_EnterLowPowerMode(uint32 base, boolean enable);

/**
 * \brief   This API will check if Lin in woken up.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  TRUE: Lin instance has woken up.
 *          FALSE: Lin instance is still in sleep.
 *
 **/
FUNC(boolean, LIN_CODE) Lin_CheckWakeupStatus(uint32 base);

/**
 * \brief   This API will abort ongoing transmission.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE) Lin_AbortTransmission(uint32 base);

/**
 * \brief   This API will enable wakeup detection.
 *
 * \param   linChannel      LIN channel to be addressed.
 * \param   enable      If TRUE wakeup detection will be enabled; if FALSE wakeup detection will be
 *disabled.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE)
Lin_EnableWakeupDetection(P2CONST(Lin_ChannelType, AUTOMATIC, LIN_APPL_CONST) linChannel, boolean enable);

/**
 * \brief   This API will process ISR for given channel.
 *
 * \param   channelID      LIN channel to be addressed.
 *
 * \return  None.
 *
 **/
FUNC(void, LIN_CODE) Lin_ProcessISR(uint32 channelID);

#if (STD_ON == LIN_REGISTER_READBACK_API)
/*! \brief      This method is Lin_HwRegisterReadback Api.
 *  \param[inout]  RegRbPtr - Pointer to where to store the readback
 *                        values. If this pointer is NULL_PTR, then the API
 *                        will return E_NOT_OK.
 *
 *  \return     void
 **/
FUNC(void, LIN_CODE) Lin_HwRegisterReadback(uint8 Channel, Lin_RegisterReadbackType *RegRbPtr);
#endif /*#if (STD_ON == LIN_REGISTER_READBACK_API)*/
/*********************************************************************************************************************
 *  Exported Inline Function Definitions and Function-Like Macros
 *********************************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* LIN_PRIV_H */
/*********************************************************************************************************************
 *  End of File: Lin_Priv.h
 *********************************************************************************************************************/
