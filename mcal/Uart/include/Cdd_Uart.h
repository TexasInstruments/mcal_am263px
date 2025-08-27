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
 *  \file     Cdd_Uart.h
 *
 *  \brief    This file contains interface header for UART Complex Device Driver
 *
 */

/*  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_Uart.h
 *      Project:  Complex Device Driver
 *       Module:  CddUartDriver
 *
 *  Description:  This module implements a driver in ANSI C programming language to centralize the
 *                configuration of ports and pins which are used by more than one driver module.
 *                With this driver you can:
 *                - Configure the UART config registers
 *                - Initialize the UART configuration
 *                - Read and write data over the UART
 **************************************************************************************************/

#ifndef CDD_UART_H_
#define CDD_UART_H_

/**
 *  \defgroup UART Uart
 *  @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <sys_common.h>
#include <hw_types.h>
#include "Std_Types.h"
#include "Cdd_Uart_Cfg.h"
#include <Uart.h>
#include "Cdd_Uart_Priv.h"
#include <SchM_Cdd_Uart.h>
#if CDD_UART_DMA_ENABLE == STD_ON
#include "Cdd_Dma_Cfg.h"
#include "Cdd_Dma_Priv.h"
#include "uart_dma.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Uart FIFO Size */
#define UART_FIFO_SIZE (64U)

/**
 *  \brief Timeout in ms used for TX FIFO empty at the time of delete. Three
 *  seconds is more than sufficient to transfer 64 bytes (FIFO size) at the
 *  lowest baud rate of 2400.
 */
#define UART_TRANSMITEMPTY_TRIALCOUNT (6000U)

/**
 *  CDD UART Driver ID Info
 *
 */
/*
 * Design: MCAL-22636
 */
/**
 *  \name CDD UART Driver ID Info
 *  @{
 */
/** \brief CDD Module ID */
#define CDD_UART_MODULE_ID 255U
/** \brief Texas Instruments Vendor ID */
#define CDD_UART_VENDOR_ID 44U
/** \brief Texas Instruments Vendor ID */
#define CDD_UART_INSTANCE_ID 0U
/** @} */

/**
 *  \name CDD UART Driver Module Version Info
 *
 *  Defines for CDD Driver version used for compatibility checks
 *@{
 */
/** \brief Driver Implementation Major Version */
#define CDD_UART_SW_MAJOR_VERSION CDD_UART_MAJOR_VERSION
/** \brief Driver Implementation Minor Version */
#define CDD_UART_SW_MINOR_VERSION CDD_UART_MINOR_VERSION
/** \brief Driver Implementation patch Version */
#define CDD_UART_SW_PATCH_VERSION CDD_UART_CFG_PATCH_VERSION
/** @} */
/**
 *  \name CDD UART Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD Driver AUTOSAR version used for compatibility checks
 *@{
 */
/** \brief AUTOSAR Major version specification implemented by CDD Driver */
#define CDD_UART_AR_RELEASE_MAJOR_VERSION 4U
/** \brief AUTOSAR Minor version specification implemented by CDD Driver */
#define CDD_UART_AR_RELEASE_MINOR_VERSION 3U
/** \brief AUTOSAR Patch version specification implemented by CDD Driver */
#define CDD_UART_AR_RELEASE_REVISION_VERSION 1U
/** @} */

/**
 *  \name CDD UART API Service ID
 *@{
 */
/*
 * Design:
 * MCAL-22583,MCAL-22584,MCAL-22585,MCAL-22586,MCAL-22587,MCAL-22588,MCAL-22589,MCAL-22636,MCAL-22671
 */
/** \brief API Service ID for initialization */
#define CDD_UART_INIT_SERVICE_ID 0x01U
/** \brief API Service ID for get version info */
#define CDD_UART_GETVERSIONINFO_SERVICE_ID 0x02U
/** \brief API Service ID for Register Readback service ID */
#define CDD_UART_REGISTERREADBACK_SERVICE_ID 0x0DU
/** \brief API Service ID for read API */
#define CDD_UART_READDATA_SERVICE_ID 0x03U
/** \brief API Service ID for write API */
#define CDD_UART_WRITEDATA_SERVICE_ID 0x04U
/** \brief API Service ID for error API */
#define CDD_UART_ERROR_SERVICE_ID 0x05U
/** \brief API Service ID for cancel API */
#define CDD_UART_CANCEL_SERVICE_ID 0x06U
/** \brief API Service ID for get remaining words API */
#define CDD_UART_GETREMAININGWORDS_SERVICE_ID 0x07U
/** \brief API Service ID for read notification handler */
#define CDD_UART_READNOTIF_SERVICE_ID 0x08U
/** \brief API Service ID for write notification handler */
#define CDD_UART_WRITENOTIF_SERVICE_ID 0x09U
/** \brief API Service ID for error notification handler */
#define CDD_UART_ERRORNOTIF_SERVICE_ID 0x0AU
/** \brief API Service ID for deinitialization */
#define CDD_UART_DEINIT_SERVICE_ID 0x0BU
/** \brief API Service ID for ISR */
#define CDD_UART_INTERNAL_ISR_ID 0x0CU
/** @} */

/**
 *  \name CDD UART Error Codes
 *@{
 */
/*
 * Design: MCAL-22572
 */
/** \brief Error code indicating the UART is uninitialized */
#define CDD_UART_E_UNINIT 0x01U

/** \brief Error code indicating an invalid event */
#define CDD_UART_E_INVALID_EVENT 0x02U

/** \brief Error code indicating UART reading mode ongoing */
#define CDD_UART_E_READ_LOCKED 0x03U

/** \brief Error code indicating UART writing mode ongoing */
#define CDD_UART_E_WRITE_LOCKED 0x04U

/** \brief Error code indicating invalid parameter pointer */
#define CDD_UART_E_PARAM_POINTER 0x05U

/** \brief Error code indicating UART is already initialized */
#define CDD_UART_E_ALREADY_INITIALIZED 0x06U

/** \brief Error code indicating Service called with wrong param */
#define CDD_UART_E_PARAM_VALUE 0x07U

/** \brief Error code indicating Service called with invalid length */
#define CDD_UART_E_PARAM_LENGTH 0x08U

/** \brief Error code indicating invalid UART channel */
#define CDD_UART_E_INVALID_CHANNEL 0x09U

/** \brief Error code indicating invalid UART configuration */
#define CDD_UART_E_INVALID_CONFIG 0x0AU
/** @} */
/**
 *  UART_TXFIFO
 *  \name Values indicating the filled status of TX FIFO
 *
 *  Note: The values should not be changed since it represents the
 *        actual register configuration values used to configure the UART
 *  @{
 */

#define UART_TX_FIFO_NOT_FULL (UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_0)
#define UART_TX_FIFO_FULL     (UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_1)
/** @} */

/**
 *  UART_IntrSources
 **  \name Values related to status of Interrupt sources.
 * @{
 */

/** \brief Values pertaining to status of UART Interrupt sources. */

#define UART_INTID_MODEM_STAT             (UART_IIR_IT_TYPE_IT_TYPE_VALUE_0 << UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_TX_THRES_REACH         (UART_IIR_IT_TYPE_IT_TYPE_VALUE_1 << UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_RX_THRES_REACH         (UART_IIR_IT_TYPE_IT_TYPE_VALUE_2 << UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_RX_LINE_STAT_ERROR     (UART_IIR_IT_TYPE_IT_TYPE_VALUE_3 << UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_CHAR_TIMEOUT           (UART_IIR_IT_TYPE_IT_TYPE_VALUE_6 << UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_XOFF_SPEC_CHAR_DETECT  (UART_IIR_IT_TYPE_IT_TYPE_VALUE_8 << UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_MODEM_SIG_STATE_CHANGE (UART_IIR_IT_TYPE_IT_TYPE_VALUE_10 << UART_IIR_IT_TYPE_SHIFT)

/** \brief Values indicating the UART Interrupt pending status. */
#define UART_INTR_PENDING (0U)
/** \brief Values indicating the UART Interrupt pending status. */
#define UART_NO_INTR_PENDING (1U)
/** @} */

/**
** \name Values related to enabling/disabling of Interrupts.
* @{
*/

/** \brief Values for enabling/disabling the interrupts of UART. */

#define UART_INTR_CTS        (UART_IER_CTS_IT_MASK)
#define UART_INTR_RTS        (UART_IER_RTS_IT_MASK)
#define UART_INTR_XOFF       (UART_IER_XOFF_IT_MASK)
#define UART_INTR_SLEEPMODE  (UART_IER_SLEEP_MODE_MASK)
#define UART_INTR_MODEM_STAT (UART_IER_MODEM_STS_IT_MASK)
#define UART_INTR_LINE_STAT  (UART_IER_LINE_STS_IT_MASK)
#define UART_INTR_THR        (UART_IER_THR_IT_MASK)
#define UART_INTR_RHR_CTI    (UART_IER_RHR_IT_MASK)

#define UART_INTR2_RX_EMPTY (UART_IER2_EN_RXFIFO_EMPTY_MASK)
#define UART_INTR2_TX_EMPTY (UART_IER2_EN_TXFIFO_EMPTY_MASK)
/** @} */

/**
** \name Values related to Line Status information.
* @{
*/

/** \brief Values pertaining to UART Line Status information. */

#define UART_FIFO_PE_FE_BI_DETECTED (UART_LSR_RX_FIFO_STS_MASK)
#define UART_BREAK_DETECTED_ERROR   (UART_LSR_RX_BI_MASK)
#define UART_FRAMING_ERROR          (UART_LSR_RX_FE_MASK)
#define UART_PARITY_ERROR           (UART_LSR_RX_PE_MASK)
#define UART_OVERRUN_ERROR          (UART_LSR_RX_OE_MASK)
/** @} */

#define UART_STATE_RX_DISABLED (0x0U)
#define UART_STATE_RX_ENABLED  (0x1U)

/** \brief Macro to check if the Data length is valid */
#define IS_DATA_LENGTH_VALID(dataLength)                                                 \
    ((dataLength == CDD_UART_WORD_LENGTH_5) || (dataLength == CDD_UART_WORD_LENGTH_6) || \
     (dataLength == CDD_UART_WORD_LENGTH_7) || (dataLength == CDD_UART_WORD_LENGTH_8))

/** \brief Macro to check if the Number of stop bits is valid */
#define IS_STOP_BITS_VALID(stopBits) ((stopBits == CDD_UART_STOP_BIT_1) || (stopBits == CDD_UART_STOP_BITS_2))

/** \brief Macro to check if the Parity type is valid */
#define IS_PARITY_TYPE_VALID(parityType)                                            \
    ((parityType == CDD_UART_PARITY_NONE) || (parityType == CDD_UART_PARITY_ODD) || \
     (parityType == CDD_UART_PARITY_EVEN))

/** \brief Macro to check if the Operation mode is valid */
#define IS_OPER_MODE_VALID(operMode) \
    ((operMode == CDD_UART_16x_OPER) || (operMode == CDD_UART_16x_AUTO_OPER) || (operMode == CDD_UART_13x_OPER))

/** \brief Macro to check if the RX Trigger level is valid */
#define IS_RXTRIG_LVL_VALID(rxTrigLvl)                                                       \
    ((rxTrigLvl == CDD_UART_TRIGGER_LEVEL_1) || (rxTrigLvl == CDD_UART_TRIGGER_LEVEL_8) ||   \
     (rxTrigLvl == CDD_UART_TRIGGER_LEVEL_16) || (rxTrigLvl == CDD_UART_TRIGGER_LEVEL_56) || \
     (rxTrigLvl == CDD_UART_TRIGGER_LEVEL_60))

/** \brief Macro to check if the TX Trigger level is valid */
#define IS_TXTRIG_LVL_VALID(txTrigLvl)                                                       \
    ((txTrigLvl == CDD_UART_TRIGGER_LEVEL_1) || (txTrigLvl == CDD_UART_TRIGGER_LEVEL_8) ||   \
     (txTrigLvl == CDD_UART_TRIGGER_LEVEL_16) || (txTrigLvl == CDD_UART_TRIGGER_LEVEL_32) || \
     (txTrigLvl == CDD_UART_TRIGGER_LEVEL_56))

/** \name MCAL Driver states
 * @{
 */
/** \brief MCAL state reset */
#define MCAL_STATE_RESET (0U)
/** \brief MCAL state ready */
#define MCAL_STATE_READY (1U)
/** \brief MCAL state busy */
#define MCAL_STATE_BUSY (2U)
/** \brief MCAL state error */
#define MCAL_STATE_ERROR (3U)
/** @} */
/** \brief Typedef for the data buffer elements*/
typedef uint8 CddUartDataBufferType;

/** \brief Type for defining the direction of data transfer, i.e., sending or receiving */
typedef uint8_least CddUartDataDirectionType;

/* ================================================================ */
/*                         Structures and Enums                     */
/* ================================================================ */

/** None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Design: MCAL-22636
 */

/** \brief Service for getting CDD UART version.
 *
 *
 * Service ID[hex]   : 0x02
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[out] VersionInfoPtr - Pointer to Std_VersionInfoType structure
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == CDD_UART_VERSION_INFO_API)
FUNC(void, CDD_UART_APPL_DATA)
Cdd_Uart_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_UART_APPL_DATA) VersionInfoPtr);
#endif

/*
 * Design: MCAL-22671
 */

/** \brief Service for reading HW IP registers of a CDD UART instance.
 * Service for reading data or status from the HW registers of a CDD UART instance.
 *
 * Service ID[hex]   : 0x08
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelID - Channel ID
 * \param[out] RegisterSetPtr - Pointer to CddUart_RegisterReadbackType structure with useful
 *registers for UART IP
 * \return Std_ReturnType
 * \retval E_OK: Register read back has been done successfully
 * \retval E_NOT_OK: Register read back failed
 *
 *****************************************************************************/
#if (STD_ON == CDD_UART_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CDD_UART_CODE)
Cdd_Uart_RegisterReadback(uint8 ChannelID, P2VAR(CddUart_RegisterReadbackType, AUTOMATIC, CDD_UART_CFG) RegisterSetPtr);
#endif

/*
 * Design: MCAL-22584
 */

/** \brief Service for CDD UART Initialization
 *
 *
 * Service ID[hex]   : 0x01
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[out] ConfigurationPtr - Constant Pointer to Cdd_Uart_CfgType containing configurations for
 *all channels
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_UART_CODE)
Cdd_Uart_Init(P2CONST(Cdd_Uart_CfgType, AUTOMATIC, CDD_UART_CFG) ConfigurationPtr);

/*
 * Design: MCAL-22585
 */

/** \brief Service for deinitializing CDD UART
 * Service for deinitializing the CDD UART and change driver state to uninitialized
 *
 * Service ID[hex]   : 0x03
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == CDD_UART_DEINIT_API)
FUNC(void, CDD_UART_CODE) Cdd_Uart_DeInit(void);
#endif

/*
 * Design: MCAL-22587
 */

/** \brief Service to transmit message using UART.
 * Service to write message using the UART instance.
 *
 * Service ID[hex]   : 0x04
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelID - Channel number to be used for writing data
 * \param[out] SrcBufferPtr - Pointer to source data buffer
 * \param[in] Count - Length (number of data elements) of the data to be
 *                    transmitted from SrcBufferPtr to remote endpoint
 * \param[in] Timeout - maximum duration of transmission for blocking mode.
 * \return Std_ReturnType
 * \retval E_OK: If successful.
 *         E_NOT_OK: If the write failed.
 *
 *****************************************************************************/
#if (STD_ON == CDD_UART_WRITE_API)
FUNC(Std_ReturnType, CDD_UART_CODE)
Cdd_Uart_Write(uint8 ChannelID, P2VAR(CddUartDataBufferType, AUTOMATIC, CDD_UART_APPL_DATA) SrcBufferPtr, uint32 Count,
               uint32 Timeout);
#endif

/*
 * Design: MCAL-22586
 */

/** \brief Service to read message or command from the UART.
 *
 * Service ID[hex]   : 0x05
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelID - Channel number to be used for reading data
 * \param[out] DestBufferPtr - Pointer to destination data buffer from which the data is read.
 * \param[in] Count - Length (number of data elements) of the data to be received from
 *DestBufferPtr.
 * \param[in] Timeout - maximum duration of transmission for blocking mode.
 * \return Std_ReturnType
 * \retval E_OK:  If data has been read
 *         E_NOT_OK: If the read returned an error.
 *
 *****************************************************************************/
#if (STD_ON == CDD_UART_READ_API)
FUNC(Std_ReturnType, CDD_UART_CODE)
Cdd_Uart_Read(uint8 ChannelID, P2VAR(CddUartDataBufferType, AUTOMATIC, CDD_UART_APPL_DATA) DestBufferPtr, uint32 Count,
              uint32 Timeout);
#endif

/*
 * Design: MCAL-22589
 */

/** \brief Service to cancel an ongoing transaction with UART.
 *
 * Service ID[hex]   : 0x06
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelID - Channel number
 * \param[in] TransferType - Read or Write
 * \return boolean
 * \retval Cancellation status (true for success, else false).
 *
 *****************************************************************************/
#if (STD_ON == CDD_UART_CANCEL_API)
FUNC(boolean, CDD_UART_CODE)
Cdd_Uart_Cancel(uint8 ChannelID, CddUartDataDirectionType TransferType);
#endif

/*
 * Design: MCAL-22588
 */

/** \brief Service to get remaining words to be transmitted from the UART for any ongoing
 *transaction.
 *
 * Service ID[hex]   : 0x07
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] ChannelID - Channel number with ongoing write transaction
 * \param[in] TransferType - Read or Write
 * \return uint32
 * \retval Size of the data left to be transmitted
 *
 *****************************************************************************/
#if (STD_ON == CDD_UART_GETREMAININGWORDS_API)
FUNC(uint32, CDD_UART_CODE)
Cdd_Uart_GetRemainingWords(uint8 ChannelID, CddUartDataDirectionType TransferType);
#endif

/** \brief This API Initializes the UART instance
 *
 * \param[in] hUart - Handle to the UART instance used
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_init(CddUart_Handle hUart);

/** \brief This API De-Initializes the UART instance
 *
 * \param[in] hUart - Handle to the UART instance used
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_deInit(CddUart_Handle hUart);

/** \brief This API writes data to the UART instance in Polling mode with
 *          exteded parameters.
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_writeEx(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API writes data to the UART instance in Interrupt mode with
 *          exteded parameters.
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_writeIntrEx(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API writes data to the UART instance in DMA mode with
 *          exteded parameters.
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_writeDmaEx(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API reads data to the UART instance in Polling mode with
 *          exteded parameters.
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_readEx(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API reads data to the UART instance in Interrupt mode with
 *          exteded parameters.
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_readIntrEx(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API reads data to the UART instance in DMA mode with
 *          exteded parameters.
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_readDmaEx(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API cancels current UART Write
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_writeCancel(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API cancels current UART Write in DMA mode
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_writeCancelDma(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API cancels current UART Read
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_readCancel(CddUart_Handle hUart, CddUart_Transaction *trans);

/** \brief This API cancels current UART Read in DMA mode
 *
 * \param[in] hUart - Handle to the UART instance used
 * \param[in] trans - Pointer to the transaction structure
 * \return sint32
 * \retval MCAL_SystemP_SUCCESS if successful else error on failure
 *
 *****************************************************************************/
sint32 Uart_Cdd_readCancelDma(CddUart_Handle hUart, CddUart_Transaction *trans);

/**
 * @}
 */

__attribute__((weak)) void Uart_Cdd_masterIsr(void *args);

__attribute__((weak)) void Uart_Cdd_writeCompleteCallback(CddUart_Handle hUart);

__attribute__((weak)) void Uart_Cdd_readCompleteCallback(CddUart_Handle hUart);

__attribute__((weak)) void Uart_Cdd_errorCallback(CddUart_Handle hUart);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_UART_H_ */
