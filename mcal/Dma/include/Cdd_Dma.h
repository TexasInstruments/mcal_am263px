/*
 * Copyright (C) 2024 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CDD_DMA_H_
#define CDD_DMA_H_

/**
 *  \defgroup DMA Dma
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Dma_Priv.h"
#include "Cdd_Dma_Cfg.h"

/* ========================================================================== */
/*                            Version Checks                                  */
/* ========================================================================== */

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/**
 *  \name CDD_DMA Driver Module SW Version Info
 *
 *  Defines for CDD_DMA Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_DMA_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define CDD_DMA_SW_MINOR_VERSION (2U)
/** \brief Driver Implementation Patch Version */
#define CDD_DMA_SW_PATCH_VERSION (0U)
/** @} */

/**
 *  \name CDD_DMA Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD_DMA Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD_DMA Driver */
#define CDD_DMA_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by CDD_DMA Driver */
#define CDD_DMA_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by CDD_DMA Driver */
#define CDD_DMA_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/**
 *  \name CDD_DMA Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define CDD_DMA_VENDOR_ID ((uint16)44U)
/** \brief CDD_DMA Driver Module ID */
#define CDD_DMA_MODULE_ID ((uint16)255U)
/** \brief CDD_DMA Driver Instance ID */
#define CDD_DMA_INSTANCE_ID ((uint8)0U)
/** @} */
/**
 *  \name CDD DMA Driver ISR category level
 *
 *  Defines for CDD DMA Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_DMA_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CDD_DMA_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CDD_DMA_ISR_CAT2 (0x02U)
/** @} */
/**
 *  \name CDD DMA API Service ID
 *  @{
 */

/** \brief API Service ID for initialization */
#define CDD_DMA_INIT_SERVICE_ID 0x01U
/** \brief API Service ID for deinitialization */
#define CDD_DMA_DEINIT_SERVICE_ID 0x02U
/** \brief  API Service ID for IntrRegistration */
#define CDD_DMA_CBKREGISTER_SERVICE_ID 0x03U
/** \brief  API Service ID for ParamSet */
#define CDD_DMA_PARAMSET_SERVICE_ID 0x04U
/** \brief  API Service ID for Param linking */
#define CDD_DMA_LINKCHANNEL_SERVICE_ID 0x05U
/** \brief  API Service ID for Channel chaining */
#define CDD_DMA_CHAINCHANNEL_SERVICE_ID 0x06U
/** \brief  API Service ID for enable a trigger */
#define CDD_DMA_ENABLETRANSFERREGION_SERVICE_ID 0x07U
/** \brief  API Service ID for reading TCC  status  */
#define CDD_DMA_GETSTATUS_SERVICE_ID 0x08U
/** \brief API Service ID for get version info */
#define CDD_DMA_GETVERSIONINFO_SERVICE_ID 0x09U
/** \brief API Service ID for get INIT status */
#define Cdd_Dma_GETINITSTATUS_SERVICE_ID 0x0AU
/** \brief  API Service ID for GetParam */
#define CDD_DMA_GETPARAM_SERVICE_ID 0x0BU
/** \brief  API Service ID for disable the transfer region */
#define CDD_DMA_DISABLETRANSFERREGION_SERVICE_ID 0x0CU
/** \brief  API Service ID for Register Read Back */
#define CDD_DMA_REGISTER_READBACK_SERVICE_ID 0x0DU
/** @} */

/**
 *  \name CDD DMA Error Codes
 *  @{*
 */

/** \brief Error code indicating the DMA is uninitialized */
#define CDD_DMA_E_UNINIT 0x01U
/** \brief Error code indicating DMA already initialized */
#define CDD_DMA_E_ALREADY_INITIALIZED 0x02U
/** \brief Error code indicating Service called with wrong param */
#define CDD_DMA_E_PARAM_VALUE 0x03U
/** \brief Error code indicating invalid parameter */
#define CDD_DMA_E_PARAM_POINTER 0x04U
/** \brief Error code indicating callback is already registered */
#define CDD_DMA_E_ALREADY_REGISTERED 0X05U
/** \brief Error code indicating DMA handle already in use */
#define CDD_DMA_E_ALREADY_IN_PROGRESS 0x06U
/** @} */

/* ========================================================================== */
/*                         Structures                                         */
/* ========================================================================== */

/** \brief Param entry */
typedef struct
{
    /** \brief OPT field of PaRAM Set */
    uint32 opt;
    /** \brief Starting byte address of Source */
    void  *srcPtr;
    /** \brief Number of bytes in each Array (ACNT) */
    uint16 aCnt;
    /** \brief Number of Arrays in each Frame (BCNT) */
    uint16 bCnt;
    /** \brief Starting byte address of destination i.e. 5 LSBs should be 0. */
    void  *destPtr;
    /** \brief Index between consec. arrays of a Source Frame (SRCBIDX) */
    sint16 srcBIdx;
    /** \brief Index between consec. arrays of a Destination Frame (DSTBIDX) */
    sint16 destBIdx;
    /** \brief Reload value of the numArrInFrame (BCNT). Relevant only for A-sync transfers */
    uint16 bCntReload;
    /** \brief Index between consecutive frames of a Source Block (SRCCIDX) */
    sint16 srcCIdx;
    /** \brief Index between consecutive frames of a Dest Block (DSTCIDX) */
    sint16 destCIdx;
    /** \brief Number of Frames in a block (CCNT) */
    uint16 cCnt;
} Cdd_Dma_ParamEntry;

/* ========================================================================== */
/*                                 Exported type declaration                  */
/* ========================================================================== */

/** \brief Callback type */
typedef Cdd_Edma_EventCallback CddDma_CallBackType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Service for CDD_DMA initialization
 *
 * Service ID[hex]   : 0x01
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] configPtr - Pointer to configuration set
 * \return None
 * \retval None
 *
 *****************************************************************************/
void Cdd_Dma_Init(Cdd_Dma_ConfigType *ConfigPtr);

/** \brief Service for CDD_DMA de-initialization
 * Function to de-initialize the Cdd_Dma Module.With this call all the handler regsitered for
 *Cdd-Dma module is de-initialized.
 *
 * Service ID[hex]   : 0x02
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
void Cdd_Dma_DeInit(void);

/** \brief Service for CDD_DMA GetInitStatus. Function to provide the initialization status of the
 *Module.
 *
 * Service ID[hex]   : 0x0A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return boolean
 * \retval True or False
 *
 *****************************************************************************/
boolean Cdd_Dma_GetInitStatus(void);

/** \brief Service for CDD_DMA Callback Register. Function to register callback function for a TCC
 *
 * Service ID[hex]   : 0x03
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to register callback
 * \param[in] appdata - data associated with it
 * \param[in] callback - registered callback which will be called on interrupt
 * \return uint32
 * \retval E_OK: Status Ok
 * \retval E_NOT_OK: Status Not Ok
 *
 *****************************************************************************/
uint32 Cdd_Dma_CbkRegister(uint32 handleId, void *appdata, Cdd_Edma_EventCallback callback);

/** \brief Service for CDD_DMA Param Setting.
 * Function to Set the paramSet values with the param value associated with the channel of a
 *particular handle
 *
 * Service ID[hex]   : 0x04
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to set the param set value
 * \param[in] channelIdx - Index of the channel for that particular handle
 * \param[in] paramIndex - Index of the param for which we want to set the param values
 * \param[in] paramEntry - Structure which contains the required paramSet fields to be used for the
 *particular param value.
 * \return None
 * \retval None
 *
 *****************************************************************************/
void Cdd_Dma_ParamSet(uint32 handleId, uint32 channelIdx, uint32 paramIndex, Cdd_Dma_ParamEntry paramEntry);

/** \brief Service for CDD_DMA Linking params.
 * Function to Link the param. Often used to link different params within the channel
 *
 * Service ID[hex]   : 0x05
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to used linking
 * \param[in] paramIndex0 - Index of the param which should be linked to another param
 * \param[in] paramIndex1 - Index of the param which is supposed to be linked to the first one
 * \return None
 * \retval None
 *
 *****************************************************************************/
void Cdd_Dma_LinkChannel(uint32 handleId, uint32 paramIndex0, uint32 paramIndex1);

/** \brief Service for CDD_DMA Chaining Channels
 * Function to Chain multiple channel and can be used in transmission only with one trigger
 *
 * Service ID[hex]   : 0x06
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to used Chaining
 * \param[in] channelIdx0 - Index of the first channel which is used for Chaining
 * \param[in] paramIndex0 - Index of the param which is supposed to be linked to the first one
 * \param[in] channelIdx1 - Index of the second channel which is used for Chaining
 * \param[in] opt - Chain Option to be used while Chaining
 * \return None
 * \retval None
 *
 *****************************************************************************/
void Cdd_Dma_ChainChannel(uint32 handleId, uint32 channelIdx0, uint32 paramIndex0, uint32 channelIdx1, uint32 opt);

/** \brief Service for CDD_DMA Enable transfer region
 * Function to Enable the trigger for transmission
 *
 * Service ID[hex]   : 0x07
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to enable the transfer
 * \param[in] trigMode - Trigger mode which is used to enable the transmission
 * \return boolean
 * \retval Indicate successfully enabled transfer or not with value True or False
 *
 *****************************************************************************/
boolean Cdd_Dma_EnableTransferRegion(uint32 handleId, uint32 trigMode);

/** \brief Service for CDD_DMA Get status
 * Function to Read the status of the transfer. Used in case of polling mode
 *
 * Service ID[hex]   : 0x08
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to get the status of the TCC
 * \return boolean
 * \retval Returns status as True or False
 *
 *****************************************************************************/
boolean Cdd_Dma_GetStatus(uint32 handleId);

/** \brief Service for CDD_DMA Get version info. Function to Get Version information
 *
 * Service ID[hex]   : 0x09
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] VersionInfoPtr - pointer to the structure for which data should be stored
 * \return None
 * \retval None
 *
 *****************************************************************************/
void Cdd_Dma_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);

/** \brief Service for CDD_DMA Param Getting
 * Function to Get the paramSet values with the param value associated with the channel of a
 *particular handle
 *
 * Service ID[hex]   : 0x0B
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to get the param value
 * \param[in] channelIdx - Index of the channel for that particular handle
 * \param[in] paramIndex - Index of the param for which we want to get the param values
 * \param[in] edmaParam - EDMA Parameter RAM struct
 * \return None
 * \retval None
 *
 *****************************************************************************/
void Cdd_Dma_GetParam(uint32 handleId, uint32 channelIdx, uint32 paramIndex, CDD_EDMACCEDMACCPaRAMEntry *edmaParam);

/** \brief Service for CDD_DMA Disable transfer region. Function to Disable the trigger for
 *transmission
 *
 * Service ID[hex]   : 0x0C
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to disable the transfer
 * \param[in] trigMode - Trigger mode which is used to disable the transmission
 * \return boolean
 * \retval Indicate successfully disabled transfer or not with value as True or False
 *
 *****************************************************************************/
boolean Cdd_Dma_DisableTransferRegion(uint32 handleId, uint32 trigMode);

/** \brief This function reads the important registers of the hardware unit and returns the value in
 *the structure.
 *
 * Service ID[hex]   : 0x0D
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] handleId - Cdd_Dma handle is passed for which we want to read the register value
 * \param[in,out] RegPtr - Pointer to where to store the readback values. If this pointer is
 *NULL_PTR, then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK: Register read back has been done
 * \retval E_NOT_OK: Register read back failed
 *
 *****************************************************************************/
Std_ReturnType Cdd_Dma_RegisterReadback(uint32 handleId, Cdd_Dma_RegisterReadbackType *RegPtr);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef CDD_DMA_H_ */
