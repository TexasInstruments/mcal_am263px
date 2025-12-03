/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * any redistribution and use of any object code compiled from the source code
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
 *  \file     Fls.h
 *
 *  \brief    This file contains interface header for Fls MCAL driver
 *
 */

#ifndef FLS_H_
#define FLS_H_

/**
 *  \defgroup FLS Fls
 *  @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Os.h"
#include "Fls_Cfg.h"
#include "Fls_Irq.h"
#include "Fls_Cbk.h"
#include "MemIf_Types.h"
#include <SchM_Fls.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \name FLS Driver ISR category level
 *
 *  Defines for FLS Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define FLS_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define FLS_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define FLS_ISR_CAT2 (0x02U)
/** @} */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name FLS Driver Module SW Version Info
 *
 *  Defines for FLS Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define FLS_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define FLS_SW_MINOR_VERSION (3U)
/** \brief Driver Implementation Patch Version */
#define FLS_SW_PATCH_VERSION (0U)
/** @} */

/**
 *  \name FLS Driver Module AUTOSAR Version Info
 *
 *  Defines for FLS Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by FLS Driver */
#define FLS_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by FLS Driver */
#define FLS_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by FLS Driver */
#define FLS_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/**
 *  \name FLS Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define FLS_VENDOR_ID ((uint16)44U)
/** \brief FLS Driver Module ID */
#define FLS_MODULE_ID ((uint16)92U)
/** \brief FLS Driver Instance ID */
#define FLS_INSTANCE_ID ((uint8)0U)
/** @} */

/** \brief FLS Address type */
#define FLS_BASE_ADDRESS_REQ ((uint8)0U)

/* Requirements : MCAL-4214, MCAL-4213, MCAL-4216 */
/** \brief FLS Address type */
typedef uint32 Fls_AddressType;
/** \brief FLS Length type */
typedef uint32 Fls_LengthType;

/**
 *  \name FLS Error Codes
 *
 *  Error codes returned by FLS functions
 *  @{
 */
/* Design :  DES_FLS_006  */
/* Requirements : MCAL-4192, MCAL-4198, MCAL-4200,
 *                MCAL-4199, MCAL-4197, MCAL-4196
 *                MCAL-4190, MCAL-4191, MCAL-4190
 */
#ifndef FLS_E_PARAM_CONFIG
/** \brief API service called with wrong parameter */
#define FLS_E_PARAM_CONFIG ((uint8)0x01U)
#endif
#ifndef FLS_E_PARAM_ADDRESS
/** \brief API service called with wrong parameter */
#define FLS_E_PARAM_ADDRESS ((uint8)0x02U)
#endif
#ifndef FLS_E_PARAM_LENGTH
/** \brief API service called with wrong parameter */
#define FLS_E_PARAM_LENGTH ((uint8)0x03U)
#endif
#ifndef FLS_E_PARAM_DATA
/** \brief API service called with wrong parameter */
#define FLS_E_PARAM_DATA ((uint8)0x04U)
#endif
#ifndef FLS_E_UNINIT
/** \brief API service used without module initiali-zation */
#define FLS_E_UNINIT ((uint8)0x05U)
#endif
#ifndef FLS_E_BUSY
/** \brief APIs called when module is busy */
#define FLS_E_BUSY ((uint8)0x06U)
#endif
#ifndef FLS_E_PARAM_POINTER
/** \brief APIs called with a Null Pointer */
#define FLS_E_PARAM_POINTER ((uint8)0x0AU)
#endif
#ifndef FLS_E_VERIFY_ERASE_FAILED
/** \brief APIs service Erase Verification (BlankCheck) failed */
#define FLS_E_VERIFY_ERASE_FAILED ((uint8)0x07U)
#endif
#ifndef FLS_E_VERIFY_WRITE_FAILED
/** \brief APIs serice Write Verification (Compare) failed */
#define FLS_E_VERIFY_WRITE_FAILED ((uint8)0x08U)
#endif
#ifndef FLS_E_TIMEOUT
/** \brief APIs Timeout Exceeded*/
#define FLS_E_TIMEOUT ((uint8)0x09U)
/** \brief APIs MEMMAP/INTERRUPT OFF but DMA ON*/
#define FLS_E_MEMAP_INTERRUPT_OFF_DMA_ON ((uint8)0x0BU)
#endif

/*TRANSIENT FAULTS WITH HW*/
#ifndef FLS_E_ERASE_FAILED
/** \brief Flash Erase Failed in HW*/
#define FLS_E_ERASE_FAILED ((uint8)0x01U)
#endif
#ifndef FLS_E_WRITE_FAILED
/** \brief Flash Write Failed in HW*/
#define FLS_E_WRITE_FAILED ((uint8)0x02U)
#endif
#ifndef FLS_E_READ_FAILED
/** \brief Flash Read Failed in HW */
#define FLS_E_READ_FAILED ((uint8)0x03U)
#endif
#ifndef FLS_E_COMPARE_FAILED
/** \brief Flash Compare Failediin HW */
#define FLS_E_COMPARE_FAILED ((uint8)0x04U)
#endif
#ifndef FLS_E_UNEXPECTED_FLASH_ID
/** \brief Expected HW ID not matched */
#define FLS_E_UNEXPECTED_FLASH_ID ((uint8)0x05U)
#endif
/** @} */

/**
 *  \name FLS Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief FLS_Init() API Service ID */
#define FLS_SID_INIT ((uint8)0x00U)
/** \brief FLS_Erase() API Service ID */
#define FLS_SID_ERASE ((uint8)0x01U)
/** \brief FLS_Write() API Service ID */
#define FLS_SID_WRITE ((uint8)0x02U)
/** \brief FLS_Cancel() API Service ID */
#define FLS_SID_CANCEL ((uint8)0x03U)
/** \brief FLS_GetStatus() API Service ID */
#define FLS_SID_GET_STATUS ((uint8)0x04U)
/** \brief Fls_GetJobResult() API Service ID */
#define FLS_SID_GET_JOB_RESULT ((uint8)0x05U)
/** \brief FLS_Read() API Service ID */
#define FLS_SID_READ ((uint8)0x07U)
/** \brief FLS_Compare() API Service ID */
#define FLS_SID_COMPARE ((uint8)0x08U)
/** \brief FLS_SetMode() API Service ID */
#define FLS_SID_SET_MODE ((uint8)0x09U)
/** \brief Fls_GetVersionInfo() API Service ID */
#define FLS_SID_GET_VERSION_INFO ((uint8)0x10U)
/** \brief FLS_BlankCheck() API Service ID */
#define FLS_SID_BLANK_CHECK ((uint8)0x0AU)
/** \brief FLS_MainFunction() API Service ID */
#define FLS_SID_MAIN_FUNCTION ((uint8)0x06U)
/** \brief Fls_RegisterReadback() API Service ID */
#define FLS_SID_REGISTERREADBACK ((uint8)0x0BU)
/** \brief Fls_SetEraseType() API Service ID */
#define FLS_SID_SET_ERASE_TYPE ((uint8)0x0CU)

/** @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief FLS Module Flashable Sectors and pages
 */

typedef struct
{
    /** \brief Number of total Sectors in the Flash Device */
    Fls_LengthType  numberOfSectors;
    /** \brief Page size of the Flash Device */
    Fls_LengthType  sectorPageSize;
    /** \brief Size of each sector in the Flash Device */
    Fls_LengthType  sectorSize;
    /** \brief Start address of first sector of the Flash Device */
    Fls_AddressType sectorStartaddress;
} Fls_SectorType;

/**
 *  \brief FLS Module Configuration Structure
 */

typedef struct Fls_ConfigType_s
{
    /** \brief Mapped to the job end notification routine provided by some upper layer
     *      module, typically the Fee module. */
    Fls_JobEndNotifyType   Fls_JobEndNotification;
    /** \brief Mapped to the job error notification routine provided by some upper layer
     *      module, typically the Fee module. */
    Fls_JobErrorNotifyType Fls_JobErrorNotification;
    /** \brief The maximum number of bytes to read or compare in one cycle of the
     *      flash driver's job processing function in normal mode. */
    uint32                 maxReadNormalMode;
    /** \brief The maximum number of bytes to write in one cycle of the
     *      flash driver's job processing function in normal mode. */
    uint32                 maxWriteNormalMode;
    /** \brief Sector List*/
    Fls_SectorType         sectorList[FLS_NUMBER_OF_SECTOR_CFG];
    /** \brief To select the FLS baudrate Divider value */
    uint32                 flsBaudRateDiv;
    /** \brief Set Flash Protocol*/
    uint32                 Fls_Mode;
} Fls_ConfigType;

/**
 *  \brief FLS external flash erase configuration items
 */

typedef struct
{
    /** \brief Erase block size*/
    Fls_LengthType blockSize;
    /** \brief Erase sector size*/
    Fls_LengthType sectorSize;
    /** \brief Block erase command for 3 byte addressing mode*/
    uint8          cmdBlockErase3B;
    /** \brief Block erase command for 4 byte addressing mode*/
    uint8          cmdBlockErase4B;
    /** \brief Sector erase command for 3 byte addressing mode*/
    uint8          cmdSectorErase3B;
    /** \brief Sector erase command for 4 byte addressing mode*/
    uint8          cmdSectorErase4B;
} Fls_EraseConfig;

/**
 *  \brief FLS external flash device informations
 */
typedef struct
{
    /** \brief Command to read device information*/
    uint8 cmd;
    /** \brief Number of bytes required to read device information*/
    uint8 numBytes;
    /** \brief Number of dummy bytes for 4 line*/
    uint8 dummy4;
    /** \brief Number of dummy bytes for 8 line*/
    uint8 dummy8;
} Fls_ReadIdConfig;

/**
 *  \brief FLS external flash protocol specific configuration parameters
 */
typedef struct
{
    /** \brief Config using addressed register enable/diable*/
    uint8  isAddrReg;
    /** \brief Command to read config register*/
    uint8  cmdRegRd;
    /** \brief Command to write config register*/
    uint8  cmdRegWr;
    /** \brief Address to config register*/
    uint32 cfgReg;
    /** \brief Number of register bit shifts*/
    uint16 shift;
    /** \brief Mask to config register*/
    uint16 mask;
    /** \brief Data to be written*/
    uint8  cfgRegBitP;
} Fls_RegEnConfig;

/**
 *  \brief FLS external flash protocol specific commands
 */
typedef struct
{
    /** \brief Protocol specific read command*/
    uint8           cmdRd;
    /** \brief Protocol specific write command*/
    uint8           cmdWr;
    /** \brief Protocol specific clock mode command*/
    uint8           modeClksCmd;
    /** \brief Protocol specific clock mode read command*/
    uint8           modeClksRd;
    /** \brief Protocol specific dummy clock command*/
    uint16          dummyClksCmd;
    /** \brief Protocol specific dummy clock read command*/
    uint16          dummyClksRd;
    /** \brief Protocol enable type*/
    uint8           enableType;
    /** \brief Protocol specific enable sequence*/
    uint8           enableSeq;
    /** \brief Protocol specific configuration list*/
    Fls_RegEnConfig protoCfg;
    /** \brief Protocol specific dummy cycles related configuration list*/
    Fls_RegEnConfig dummyCfg;
    /** \brief Protocol specific STR/DTR configuration list*/
    Fls_RegEnConfig strDtrCfg;
} Fls_ProtoEnableConfig;

/**
 *  \brief FLS external flash generic parameters
 */
typedef struct Fls_ConfigSfdp_s
{
    /** \brief External flash size*/
    uint32                flashSize;
    /** \brief External flash page size*/
    uint32                pageSize;
    /** \brief External flash manufacture ID*/
    uint8                 manfId;
    /** \brief External flash device ID*/
    uint16                deviceId;
    /** \brief Number of supported flash erase types*/
    uint8                 numSupportedEraseTypes;
    /** \brief Flash execution type*/
    uint8                 cmdExtType;
    /** \brief Flash byte order*/
    uint8                 byteOrder;
    /** \brief Flash address byte support*/
    uint8                 addrByteSupport;
    /** \brief Flash 4 byte address enable sequence*/
    uint8                 fourByteAddrEnSeq;
    /** \brief Flash 4 byte address disable sequence*/
    uint8                 fourByteAddrDisSeq;
    /** \brief External Flash dtr support*/
    uint8                 dtrSupport;
    /** \brief Flash device busy type*/
    uint8                 deviceBusyType;
    /** \brief Flash device reset type*/
    uint8                 rstType;
    /** \brief Flash device reset type*/
    uint8                 addrnumBytes;
    /** \brief Flash write enable command*/
    uint8                 cmdWren;
    /** \brief Flash read status register command*/
    uint8                 cmdRdsr;
    /** \brief Flash read status register2 command*/
    uint8                 cmdRdsr2;
    /** \brief Flash write status register command*/
    uint8                 cmdWrsr;
    /** \brief Flash WIP bit position*/
    uint8                 srWip;
    /** \brief Flash WIP bit position*/
    uint8                 srWel;
    /** \brief Flash chip erase command*/
    uint8                 cmdChipErase;
    /** \brief Flash WIP bit read command*/
    uint8                 xspiWipRdCmd;
    /** \brief Flash WIP bit status register address*/
    uint32                xspiWipReg;
    /** \brief Flash WIP bit(xSPI) bit position*/
    uint32                xspiWipBit;
    /** \brief Flash write timeout in us*/
    uint32                flashWriteTimeout;
    /** \brief Flash wrr write timeout in us*/
    uint32                wrrwriteTimeout;
    /** \brief Flash busy timeout in us*/
    uint32                flashBusyTimeout;
    /** \brief Flash chip erase timeout in us*/
    uint32                chipEraseTimeout;
    /** \brief Flash maximum sector erase time in us*/
    uint32                flsMaxSectorErasetimeConvInUsec;
    /** \brief Flash maximum block erase time in us*/
    uint32                flsMaxBlockErasetimeConvInUsec;
    /** \brief Flash maximum chip erase time in us*/
    uint32                flsMaxChipErasetimeConvInUsec;
    /** \brief Flash maximum sector read-write time in us*/
    uint32                flsMaxSectorReadWritetimeConvInUsec;
    /** \brief Flash maximum block read-write time in us*/
    uint32                flsMaxBlockReadWritetimeConvInUsec;
    /** \brief Flash maximum chip read-write time in us*/
    uint32                flsMaxChipReadWritetimeConvInUsec;
    /** \brief Flash erase configurations list*/
    Fls_EraseConfig       eraseCfg;
    /** \brief Flash device information configurations list*/
    Fls_ReadIdConfig      idCfg;
    /** \brief Flash protocol specific configurations list*/
    Fls_ProtoEnableConfig protos;
} Fls_ConfigSfdp;

/** \brief ENUM for erase type names */
typedef enum
{
    /** \brief Sector Erase */
    FLS_SECTOR_ERASE,
    /** \brief Block Erase */
    FLS_BLOCK_ERASE,
    /** \brief Chip Erase */
    FLS_CHIP_ERASE
} Fls_EraseType;

#if (STD_ON == FLS_REGISTER_READBACK_API)
/** \brief Register readback type */
typedef struct
{
    /** \brief QSPI register */
    uint32 qspireg1;

} Fls_RegisterReadbackType;
#endif /* #if (STD_ON == FLS_REGISTER_READBACK_API) */

/** \brief ENUM for Reset pin states */
typedef enum
{
    /** \brief Reset pin state low */
    FLS_RESET_PIN_STATE_LOW,
    /** \brief Reset pin state high */
    FLS_RESET_PIN_STATE_HIGH,
} Fls_ResetPinMode;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Initializes the Flash Driver.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x00
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] ConfigPtr - Pointer to flash driver configuration set
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, FLS_CODE) Fls_Init(P2CONST(Fls_ConfigType, AUTOMATIC, FLS_CONFIG_DATA) ConfigPtr);

/** \brief Erases flash sector(s).
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x01
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] TargetAddress - Target address in flash memory. This address offset will be added to
 *the flash memory base address.
 * \param[in] Length - Number of bytes to erase
 * \return Std_ReturnType
 * \retval E_OK: erase command has been accepted
 * \retval E_NOT_OK: erase command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, FLS_CODE) Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length);

/** \brief Writes one or more complete flash pages.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x02
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] TargetAddress - Target address in flash memory. This address offset will be added to
 *the flash memory base address.
 * \param[in] SourceAddressPtr - Pointer to source data buffer
 * \param[in] Length - Number of bytes to write
 * \return Std_ReturnType
 * \retval E_OK: write command has been accepted
 * \retval E_NOT_OK: write command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, FLS_CODE)
Fls_Write(Fls_AddressType TargetAddress, const uint8 *SourceAddressPtr, Fls_LengthType Length);

/** \brief Reads from flash memory.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x07
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] SourceAddress - Source address in flash memory. This address offset will be added to
 *the flash memory base address.
 * \param[in] TargetAddressPtr - Pointer to target data buffer
 * \param[in] Length - Number of bytes to read
 * \return Std_ReturnType
 * \retval E_OK: read command has been accepted
 * \retval E_NOT_OK: read command has not been accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, FLS_CODE)
Fls_Read(Fls_AddressType SourceAddress, uint8 *TargetAddressPtr, Fls_LengthType Length);

/** \brief Compares the contents of an area of flash memory with that of an application data buffer.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x08
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] SourceAddress - Source address in flash memory. This address offset will be added to
 *the flash memory base address.
 * \param[in] TargetAddressPtr - Pointer to target data buffer
 * \param[in] Length - Number of bytes to compare
 * \return Std_ReturnType
 * \retval E_OK: compare command has been accepted
 * \retval E_NOT_OK: compare command has not been accepted
 *
 *****************************************************************************/
#if (STD_ON == FLS_COMPARE_API)
FUNC(Std_ReturnType, FLS_CODE)
Fls_Compare(Fls_AddressType SourceAddress, const uint8 *TargetAddressPtr, Fls_LengthType Length);
#endif

/** \brief The function Fls_BlankCheck shall verify, whether a given memory area has been erased but
 *not (yet) programmed.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x0a
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] Address - Source address in flash memory. This address offset will be added to the
 *flash memory base address.
 * \param[in] Length - Number of bytes to compare
 * \return Std_ReturnType
 * \retval E_OK: BlankCheck command has been accepted
 * \retval E_NOT_OK: BlankCheck command has not been accepted
 *
 *****************************************************************************/
#if (STD_ON == FLS_BLANK_CHECK_API)
FUNC(Std_ReturnType, FLS_CODE) Fls_BlankCheck(Fls_AddressType Address, Fls_LengthType Length);
#endif

/** \brief Returns the driver state.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x04
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return MemIf_StatusType
 * \retval Returns the state
 *
 *****************************************************************************/
#if (STD_ON == FLS_GET_STATUS_API)
FUNC(MemIf_StatusType, FLS_CODE) Fls_GetStatus(void);
#endif

/** \brief This service returns the version information of this module.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x10
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in,out] versioninfo - Pointer to where to store the version information of this module
 * \return Std_ReturnType
 * \retval E_OK: command has been accepted
 * \retval E_NOT_OK: command has not been accepted
 *
 *****************************************************************************/
#if (STD_ON == FLS_VERSION_INFO_API)
FUNC(Std_ReturnType, FLS_CODE) Fls_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

/** \brief Returns the result of the last job.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x05
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return MemIf_JobResultType
 * \retval Returns the MemIf Job result type. Refer enum #MemIf_JobResultType for the values
 *
 *****************************************************************************/
#if (STD_ON == FLS_GET_JOB_RESULT_API)
FUNC(MemIf_JobResultType, FLS_CODE) Fls_GetJobResult(void);
#endif

/** \brief Performs the processing of jobs.
 *
 * Mode              : Supervisor Mode (Privileged Mode)
 *
 * Service ID[hex]   : 0x06
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, FLS_CODE) Fls_MainFunction(void);

/** \brief Cancels an ongoing job.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x03
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (FLS_CANCEL_API == STD_ON)
FUNC(void, FLS_CODE) Fls_Cancel(void);
#endif

/** \brief Sets the flash driver's operation mode
 * This is a dummy API which is not supported and Added for integration purposes
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : 0x09
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Mode - MEMIF_MODE_SLOW: Slow read access / normal SPI access, MEMIF_MODE_FAST: Fast
 *read access / SPI burst access.
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == FLS_SETMODE_API)
FUNC(void, FLS_CODE) Fls_SetMode(MemIf_ModeType Mode);
#endif

/** \brief Sets the parameters for required erase type.
 * Sets the parameters required in application, based on the erase type parameter
 * passed to this function while calling from Application.
 *
 * Mode              : User Mode (Non-Privileged Mode)
 *
 * Service ID[hex]   : NA
 *
 * \param[in] erasetype - Type of erase
 * \return uint32
 * \retval Returns sector or block size
 *
 *****************************************************************************/
FUNC(uint32, FLS_CODE) Fls_SetEraseType(Fls_EraseType erasetype);

#if (STD_ON == FLS_REGISTER_READBACK_API)
/** \brief Register readback function
 *
 * Service ID[hex]   : NA
 *
 * \param[out] RegRbPtr - Register readback pointer
 * \return Std_ReturnType
 * \retval E_OK: success
 * \retval E_NOT_OK: failure
 *
 *****************************************************************************/
FUNC(Std_ReturnType, FLS_CODE)
Fls_RegisterReadback(P2VAR(Fls_RegisterReadbackType, AUTOMATIC, FLS_APPL_DATA) RegRbPtr);
#endif /*STD_ON == FLS_REGISTER_READBACK_API*/

#ifdef FLS_OSPI_CTRL_BASE_ADDR
/** \brief Sets the Flash Addressing Mode to 3 byte.
 *
 *
 * Service ID[hex]   : NA
 *
 * \return Std_ReturnType
 * \retval E_OK: success
 * \retval E_NOT_OK: failure
 *
 *****************************************************************************/
FUNC(Std_ReturnType, FLS_CODE) Fls_Set3ByteAddressMode(void);
#endif

#ifdef FLS_OSPI_CTRL_BASE_ADDR
/** \brief Updates the Flash Pin Value.
 * Use this API to Reset Flash
 * Step1: pinMode = FLS_RESET_PIN_STATE_HIGH  Step2: pinMode = FLS_RESET_PIN_STATE_LOW
 * Works for Am263Px-SIP and AM263Px- Rev A board
 *
 * Service ID[hex]   : NA
 *
 * \return Std_ReturnType
 * \retval E_OK: success
 * \retval E_NOT_OK: failure
 *
 *****************************************************************************/
FUNC(Std_ReturnType, FLS_CODE) Fls_setResetPinMode(Fls_ResetPinMode pinMode);
#endif

#if (STD_ON == FLS_OSPI_PHY_ENABLE)
/** \brief Enables phy tuning.
 * Use this API to read with phy
 * Applicable on am263px and am261 platforms
 *
 * Service ID[hex]   : NA
 *
 * \return Std_ReturnType
 * \retval E_OK: success
 * \retval E_NOT_OK: failure
 *
 *****************************************************************************/
FUNC(Std_ReturnType, FLS_CODE) Fls_PhyEnable(void);

/** \brief Disable phy tuning.
 * Use this API to diable phy
 * Applicable on am263px and am261 platforms
 *
 * Service ID[hex]   : NA
 *
 * \return Std_ReturnType
 * \retval E_OK: success
 * \retval E_NOT_OK: failure
 *
 *****************************************************************************/
FUNC(void, FLS_CODE) Fls_PhyDisable(void);
#endif /* #if (STD_ON == FLS_OSPI_PHY_ENABLE) */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef FLS_H_ */
