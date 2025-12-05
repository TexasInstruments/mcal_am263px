/* ======================================================================
 *   Copyright (C) 2023-2024 Texas Instruments Incorporated
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
 *  \file     Spi.h
 *
 *  \brief    This file contains interface header for SPI MCAL driver
 *
 */

/* Design : SPI_DesignId_001, SPI_DesignId_002, SPI_DesignId_005,
 *          SPI_DesignId_006, SPI_DesignId_024, SPI_DesignId_008 */
/*
 * Below are the global requirements which are met by this SPI handler
 * driver which can't be mapped to a particular source ID
 */

/*
 * Below are the SPI's module environment requirements which can't be mapped
 * to this driver.
 */
/* Design : SPI_DesignId_023 */

#ifndef SPI_H_
#define SPI_H_

/**
 * \defgroup SPI Spi API GUIDE Header file
 * @{
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */
/*
 *Design: MCAL-14055, MCAL-14057
 */
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Spi_Cfg.h"
#include "sys_common.h"
#if (SPI_DMA_ENABLE == STD_ON)
#include "Cdd_Dma_Priv.h"
#include "Cdd_Dma.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */
/*                           Macros & Typedefs                      */
/* ================================================================ */

/**
 *  \name SPI Driver Module SW Version Info
 *
 *  Defines for SPI Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define SPI_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define SPI_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation Patch Version */
#define SPI_SW_PATCH_VERSION (1U)
/**   @} */

/**
 *  \name SPI Driver Module AUTOSAR Version Info
 *
 *  Defines for SPI Driver AUTOSAR version used for compatibility
 *   checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by
 *   SPI Driver */
#define SPI_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by
 *   SPI Driver */
#define SPI_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by
 *   SPI Driver */
#define SPI_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/**
 *  \name SPI Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define SPI_VENDOR_ID ((uint16)44U)
/** \brief SPI Driver Module ID */
#define SPI_MODULE_ID ((uint16)83U)
/** \brief SPI Driver Instance ID */
#define SPI_INSTANCE_ID ((uint8)0U)
/**   @} */

/**
 *  \name SPI Buffer Macro
 *  @{
 */

/** \brief SPI IB  */
#define SPI_IB_ALIGNMENGT (0x03U)
/**   @} */

/**
 *  \name SPI Buffer Definition
 *  @{
 */
/** \brief Buffer definitions IB - internal buffers */
#define SPI_IB (0U)
/** \brief Buffer definitions EB - external buffers. Only this
 *   is supported */
#define SPI_EB (1U)
/** \brief Buffer definitions IB/EB - internal/external buffers */
#define SPI_IB_EB (2U)
/**   @} */

/**
 *  \name SPI Driver ISR category level
 *
 *  Defines for SPI Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define SPI_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define SPI_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define SPI_ISR_CAT2 (0x02U)
/**   @} */

/**
 *  \name SPI Error Codes
 *
 *  Error codes returned by SPI functions
 *  @{
 */
/*
 *Design: MCAL-14089, MCAL-14079, MCAL-14080, MCAL-14081, MCAL-14082, MCAL-14083, MCAL-14085,
 *MCAL-14086,  MCAL-14087, MCAL-14091, MCAL-14074, MCAL-14073, MCAL-14067, MCAL-14071, MCAL-14070,
 *MCAL-14068, MCAL-14064, MCAL-14072, MCAL-14066, MCAL-14069
 */
#ifndef SPI_E_PARAM_CHANNEL
/** \brief API service called with wrong parameter */
#define SPI_E_PARAM_CHANNEL ((uint8)0x0AU)
#endif
#ifndef SPI_E_PARAM_JOB
/** \brief API service called with wrong parameter */
#define SPI_E_PARAM_JOB ((uint8)0x0BU)
#endif
#ifndef SPI_E_PARAM_SEQ
/** \brief API service called with wrong parameter */
#define SPI_E_PARAM_SEQ ((uint8)0x0CU)
#endif
#ifndef SPI_E_PARAM_LENGTH
/** \brief API service called with wrong parameter */
#define SPI_E_PARAM_LENGTH ((uint8)0x0DU)
#endif
#ifndef SPI_E_PARAM_UNIT
/** \brief API service called with wrong parameter */
#define SPI_E_PARAM_UNIT ((uint8)0x0EU)
#endif
#ifndef SPI_E_PARAM_POINTER
/** \brief APIs called with a Null Pointer */
#define SPI_E_PARAM_POINTER ((uint8)0x10U)
#endif
#ifndef SPI_E_UNINIT
/** \brief API service used without module initiali-zation */
#define SPI_E_UNINIT ((uint8)0x1AU)
#endif
#ifndef SPI_E_SEQ_PENDING
/** \brief Services called in a wrong sequence */
#define SPI_E_SEQ_PENDING ((uint8)0x2AU)
#endif
#ifndef SPI_E_SEQ_IN_PROCESS
/** \brief Synchronous transmission service called at wrong time */
#define SPI_E_SEQ_IN_PROCESS ((uint8)0x3AU)
#endif
#ifndef SPI_E_ALREADY_INITIALIZED
/**
 *  \brief API Spi_Init service called while the SPI driver has
 *   already been initialized
 */
#define SPI_E_ALREADY_INITIALIZED ((uint8)0x4AU)
#endif
#ifndef SPI_E_SEQUENCE_NOT_OK
/** \brief Sequence did not complete successfully */
#define SPI_E_SEQUENCE_NOT_OK ((uint8)0x5AU)
#endif

/**   @} */

/**
 *  \name SPI Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function
 and is used to identify the source of the error
 *  @{
 */
/** \brief Spi_Init() API Service ID */
#define SPI_SID_INIT ((uint8)0x00U)
/** \brief Spi_DeInit() API Service ID */
#define SPI_SID_DEINIT ((uint8)0x01U)
/** \brief Spi_WriteIB() API Service ID */
#define SPI_SID_WRITE_IB ((uint8)0x02U)
/** \brief Spi_AsyncTransmit() API Service ID */
#define SPI_SID_ASYNC_TRANSMIT ((uint8)0x03U)
/** \brief Spi_ReadIB() API Service ID */
#define SPI_SID_READ_IB ((uint8)0x04U)
/** \brief Spi_SetupEB() API Service ID */
#define SPI_SID_SETUP_EB ((uint8)0x05U)
/** \brief Spi_GetStatus() API Service ID */
#define SPI_SID_GET_STATUS ((uint8)0x06U)
/** \brief Spi_GetJobResult() API Service ID */
#define SPI_SID_GET_JOB_RESULT ((uint8)0x07U)
/** \brief Spi_GetSequenceResult() API Service ID */
#define SPI_SID_GET_SEQ_RESULT ((uint8)0x08U)
/** \brief Spi_GetVersionInfo() API Service ID */
#define SPI_SID_GET_VERSION_INFO ((uint8)0x09U)
/** \brief Spi_SyncTransmit() API Service ID */
#define SPI_SID_SYNC_TRANSMIT ((uint8)0x0AU)
/** \brief Spi_GetHWUnitStatus() API Service ID */
#define SPI_SID_GET_HW_UNIT_STATUS ((uint8)0x0BU)
/** \brief Spi_Cancel() API Service ID */
#define SPI_SID_CANCEL ((uint8)0x0CU)
/** \brief Spi_SetAsyncMode() API Service ID */
#define SPI_SID_SET_ASYNC_MODE ((uint8)0x0DU)
/** \brief Spi_MainFunction_Handling() API Service ID */
#define SPI_SID_MAINFUNCTION_HANDLING ((uint8)0x10U)
/**   @} */

/**
 *  \brief MCSPI functional clock input in Hz.
 *   This clock is used to generate the serial clock output after
 *   the divider.
 *   Note: This is given here for reference and can't be changed.
 */
#define SPI_MCSPI_FCLK (48000000U)

/* ================================================================ */
/*                          Function Declarations                   */
/* ================================================================ */

/** \brief Service for SPI initialization.
 *
 *
 * Service ID[hex] - 0x00
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] CfgPtr - Pointer to configuration set
 * \return None
 * \retval None
 *
 *****************************************************************************/
/* SWS_Spi_00258 */
FUNC(void, SPI_CODE) Spi_Init(P2CONST(Spi_ConfigType, AUTOMATIC, SPI_CONFIG_DATA) CfgPtr);

/** \brief Service for SPI de-initialization.
 *
 *
 * Service ID[hex] - 0x01
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return Std_ReturnType
 * \retval E_OK - de-initialisation command has been accepted
 * \retval E_NOT_OK - de-initialisation command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE) Spi_DeInit(void);

/** \brief Service returns the SPI Handler/Driver software module status.
 *
 *
 * Status of register can be either SPI_UNINIT ,SPI_IDLE or SPI_BUSY
 *
 * Service ID[hex] - 0x06
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \return Spi_StatusType
 * \retval Service for SPI de-initialization
 *
 *****************************************************************************/
FUNC(Spi_StatusType, SPI_CODE) Spi_GetStatus(void);

/** \brief This service returns the last transmission result of the
 * specified Job.
 *
 *
 * Service ID[hex] - 0x07
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Job - Job ID. An invalid job ID will return an undefined result
 * \return Spi_JobResultType
 * \retval SPI_JOB_OK - last transmission of the Job has been finished successfully
 * \retval SPI_JOB_PENDING - Driver is performing a SPI Job(Busy)
 * \retval SPI_JOB_FAILED - last transmission of the Job has failed
 * \retval SPI_JOB_QUEUED - transmission for this Job has not started yet
 *
 *****************************************************************************/
FUNC(Spi_JobResultType, SPI_CODE) Spi_GetJobResult(Spi_JobType Job);

/** \brief This service returns the last transmission result of the
 * specified Sequence.
 *
 *
 * Service ID[hex] - 0x08
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Sequence - Sequence ID. An invalid job ID will return an
 * undefined result
 * \return Spi_JobResultType
 * \retval SPI_SEQ_OK - last transmission of the Sequence has been finished
 * successfully
 * \retval SPI_SEQ_PENDING - Driver is performing a SPI Sequence (Busy)
 * \retval SPI_SEQ_FAILED - last transmission of the Sequence has failed
 * \retval SPI_SEQ_CANCELLED - transmission for this Sequence has been
 * canceled by user
 *
 *****************************************************************************/
FUNC(Spi_SeqResultType, SPI_CODE) Spi_GetSequenceResult(Spi_SequenceType Sequence);

#if (STD_ON == SPI_VERSION_INFO_API)
/** \brief This service returns the version information of this module.
 *
 *
 * Service ID[hex] - 0x09
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[inout] versioninfo - Pointer to where to store the version
 * information of this module
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, SPI_CODE)
Spi_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) versioninfo);
#endif /* #if (STD_ON == SPI_VERSION_INFO_API) */

#if (STD_ON == SPI_HW_STATUS_API)
/** \brief This service returns the status of the specified SPI
 * Hardware microcontroller peripheral.
 *
 *
 * Service ID[hex] - 0x0B
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[inout] HWUnit - SPI Hardware microcontroller peripheral unit ID.
 * information of this module
 * \return Spi_StatusType
 * \retval SPI_UNINIT - not initialized or not usable
 * \retval SPI_IDLE - not currently transmitting any Job
 * \retval SPI_BUSY - is performing a SPI Job (transmit)
 *
 *****************************************************************************/
FUNC(Spi_StatusType, SPI_CODE) Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit);
#endif /* #if (STD_ON == SPI_HW_STATUS_API) */

#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))

/** \brief Service for writing one or more data to an IB SPI Handler/Driver Channel
 * specified by parameter.
 *
 *
 * Service ID[hex] - 0x02
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Channel ID
 * \param[in] DataBufferPtr-Pointer to source data buffer.  If this
 * pointer is null, it is assumed that the data to be transmitted
 * is not relevant and the default transmit value of this
 * channel will be used instead.
 * \return Std_ReturnType
 * \retval E_OK - Write command has been accepted
 * \retval E_NOT_OK - Write command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE)
Spi_WriteIB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr);

/** \brief Service for reading synchronously one or more data from an IB SPI
 * SPI Handler/Driver Channel specified by parameter
 *
 *
 * Service ID[hex] - 0x04
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Channel ID
 * \param[out] DataBufferPtr-Pointer to destination data buffer.
 * \return Std_ReturnType
 * \retval E_OK - Read command has been accepted
 * \retval E_NOT_OK - Read command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE)
Spi_ReadIB(Spi_ChannelType Channel, P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPointer);
#endif /* #if SPI_IB || SPI_IB_EB */

#if ((SPI_CHANNELBUFFERS == SPI_EB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))

/** \brief Service to setup the buffers and the length of data for the
 *   EB SPI Handler/Driver Channel specified.
 *
 *
 * Service ID[hex] - 0x05
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Channel - Channel ID
 * \param[in] SrcDataBufferPtr-Pointer to source data buffer.
 * \param[in] DesDataBufferPtr-Pointer to destination data buffer.
 * \param[in] Length - Length (number of data elements) of the data to be
 * transmitted from SrcDataBufferPtr and/or  received from DesDataBufferPtr
 * Min.: 1 Max.: Max of data specified at configuration for this  channel.
 * \return Std_ReturnType
 * \retval E_OK - Setup command has been accepted
 * \retval E_NOT_OK - Setup command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE)
Spi_SetupEB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
            P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr, Spi_NumberOfDataType Length);
#endif /* #if ((SPI_CHANNELBUFFERS == SPI_EB) || \
        * (SPI_CHANNELBUFFERS == SPI_IB_EB)) */

#if ((SPI_SCALEABILITY == SPI_LEVEL_1) || (SPI_SCALEABILITY == SPI_LEVEL_2))

/** \brief Service to transmit data on the SPI bus.
 *
 *
 * Service ID[hex] - 0x03
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Sequence - Sequence ID
 * \return Std_ReturnType
 * \retval E_OK - Transmission command has been accepted
 * \retval E_NOT_OK - Transmission command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE) Spi_AsyncTransmit(Spi_SequenceType Sequence);
#endif /* #if ((SPI_SCALEABILITY == SPI_LEVEL_1) || \
        *(SPI_SCALEABILITY == SPI_LEVEL_2)) */

#if (STD_ON == SPI_CANCEL_API)
/** \brief Service cancels the specified ongoing sequence transmission.
 *
 *
 * Service ID[hex] - 0x0C
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Sequence - Sequence ID
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, SPI_CODE) Spi_Cancel(Spi_SequenceType Sequence);
#endif /* #if (STD_ON == SPI_CANCEL_API) */

#if ((SPI_SCALEABILITY == SPI_LEVEL_0) || (SPI_SCALEABILITY == SPI_LEVEL_2))

/** \brief Service to transmit data on the SPI bus.
 *
 *
 * Service ID[hex] - 0x0A
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] Sequence - Sequence ID
 * \return Std_ReturnType
 * \retval E_OK - Transmission command has been completed
 * \retval E_NOT_OK - Transmission command has not been completed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE) Spi_SyncTransmit(Spi_SequenceType Sequence);
#endif /* #if ((SPI_SCALEABILITY == SPI_LEVEL_0) || \
        *(SPI_SCALEABILITY == SPI_LEVEL_2)) */

#if (SPI_SCALEABILITY == SPI_LEVEL_2)
/** \brief Service to set the asynchronous mechanism mode for SPI
 * busses handled asynchronously.
 *
 *
 * Service ID[hex] - 0x0D
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] Mode - New mode required.
 * \return Std_ReturnType
 * \retval E_OK - Setting command has been done
 * \retval E_NOT_OK - Setting command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE) Spi_SetAsyncMode(Spi_AsyncModeType Mode);
#endif /* #if (SPI_SCALEABILITY == SPI_LEVEL_2) */

/** \brief This function polls the SPI interrupts linked to HW Units
 *   allocated to the transmission of SPI sequences to enable the
 *   evolution of transmission state machine.
 *
 *
 * Service ID[hex] - 0x10
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, SPI_CODE) Spi_MainFunction_Handling(void);

#if (STD_ON == SPI_REGISTER_READBACK_API)
/** \brief This function reads the important registers of the hardware
 *   unit and returns the value in the structure.
 *
 *
 *  This API should be called after Spi_Init is called. Otherwise this
 *  API will return E_NOT_OK.
 *
 *  This API could be used to readback the register contents after
 *  Spi_Init and then the readback value could be compared during SPI
 *  execution to check the correctness of the HW unit. Since this API
 *  is used for this purpose, the register returned are the ones which
 *  doesn't change after init based on job or channel config.
 *
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] HWUnit - SPI Hardware microcontroller peripheral unit ID.
 * If this is invalid, then the API will return E_NOT_OK.
 * \param[inout]  RegRbPtr - Pointer to where to store the readback values. If
 * If this pointer is NULL_PTR, then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK - Register read back has been done
 * \retval E_NOT_OK - Register read back failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE)
Spi_RegisterReadback(Spi_HWUnitType HWUnit, P2VAR(Spi_RegisterReadbackType, AUTOMATIC, SPI_APPL_DATA) RegRbPtr);
#endif /* #if (STD_ON == SPI_REGISTER_READBACK_API) */

#if (STD_ON == SPI_SET_LOOPBACK_MODE_API)
/** \brief This function enables or disables the internal loopback mode of
 *  SPI. Note: Only MiBSPI HW units supports this feature.
 *
 *
 *  This API should be called after Spi_Init is called. Otherwise this API will
 *  return E_NOT_OK. Also this API should not be called when the HW unit is
 *  busy.
 *
 *  This API could be used to check the integrity of the SPI module. When
 *  the loopback mode is enabled, the data transferred is received back and
 *  hence the caller can verify and compare the TX buffer with RX buffer
 *  for any HW failures.
 *
 * Service ID[hex] - None
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] HWUnit - SPI Hardware microcontroller peripheral unit ID.
 * If this is invalid, then the API will return E_NOT_OK.
 * \param[in]  LpbkEnable - Loopback enable/disable: TRUE - Enable loopback,
 * FALSE - Disable loopback
 * \return Std_ReturnType
 * \retval E_OK - Loop back mode done
 * \retval E_NOT_OK - Loop back mode failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, SPI_CODE) Spi_SetLoopbackMode(Spi_HWUnitType HWUnit, boolean LoopbkEn);
#endif /* #if (STD_ON == SPI_SET_LOOPBACK_MODE_API) */

#if (STD_ON == SPI_DEV_ERROR_DETECT)
void Spi_reportDetError(uint8 apiId, uint8 errorId);
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
void Spi_reportDetRuntimeError(uint8 apiId, uint8 errorId);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef SPI_H_ */
