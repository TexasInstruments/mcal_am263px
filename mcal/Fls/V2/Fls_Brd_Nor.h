/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file     Fls_Brd_Nor_Ospi.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the FLS MCAL driver files.
 *
 */

#ifndef FLS_BRD_NOR_OSPI_H_
#define FLS_BRD_NOR_OSPI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "SchM_Fls.h"
#include "Fls_Cbk.h"
#include "Fls.h"
#include "Fls_Ospi.h"
#include "Det.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* The retVal definitions */
#define E_COMPARE_MISMATCH    (2U)
#define E_BLANKCHECK_MISMATCH (3U)

/* FLS Stage of Erase. */
#define FLS_S_DEFAULT          (0U)
#define FLS_S_INVALID_ADDRESS  (1U)
#define FLS_S_DELAY_1_STAGE    (2U)
#define FLS_S_SECTOR_CMD_STAGE (3U)
#define FLS_S_BLOCK_CMD_STAGE  (3U)
#define FLS_S_CHIP_CMD_STAGE   (3U)
#define FLS_S_DELAY_2_STAGE    (4U)

/* FLS Stage of Erase. */
#define FLS_S_INIT_STAGE (0U)
#define FLS_S_WAIT_STAGE (1U)
#define FLS_S_WRITE_DONE (2U)

/* FLS Stage of Read(for DMA). */
#define FLS_S_READ_DMA_INIT_STAGE (0U)
#define FLS_S_READ_DMA_WAIT_STAGE (1U)
#define FLS_S_READ_DMA_DONE       (2U)

#define OSPI_NOR_CMD_RSTEN (0x66U)
#define OSPI_NOR_CMD_RST   (0x99U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**< ENUM for job type names */
typedef enum
{
    FLS_JOB_NONE,
    FLS_JOB_COMPARE,
    FLS_JOB_ERASE,
    FLS_JOB_READ,
    FLS_JOB_WRITE,
    FLS_JOB_BLANKCHECK
} Fls_JobType;

/**
 * \breif FLS Driver Object, global information used by module.
 */
typedef struct
{
    uint32                 Fls_Mode;
    /* Set Flash Protocol*/
    Fls_JobEndNotifyType   Fls_JobEndNotification;
    /**<    Mapped to the job end notification routine provided by some upper layer
     *      module, typically the Fee module. */
    Fls_JobErrorNotifyType Fls_JobErrorNotification;
    /**<    Mapped to the job error notification routine provided by some upper layer
     *      module, typically the Fee module. */
    uint32                 maxReadNormalMode;
    /**<    The maximum number of bytes to read or compare in one cycle of the
     *      flash driver's job processing function in normal mode. */
    uint32                 maxWriteNormalMode;
    /**<    The maximum number of bytes to write in one cycle of the
     *      flash driver's job processing function in normal mode. */
    Fls_SectorType         sectorList[FLS_NUMBER_OF_SECTOR_CFG];
    /**<     The maximum number of bytes to write in one cycle of the flash driver's job
     *       processing function in normal mode.
     *       Using Fls Info Structure instead of this for now. */
    MemIf_StatusType       status;
    /**< Current Module Status update variable */
    MemIf_JobResultType    jobResultType;
    /**< Current Job Result update variable */
    Fls_JobType            jobType;
    /**< Current running job type */
    Fls_AddressType        flashAddr;
    /**< Flash Address for the current job */
    uint8                 *ramAddr;
    /**< Ram Address pointer for the current job */
    uint8                 *compareAddr;
    /**< Compare Address pointer for the compare job */
    Fls_LengthType         length;
    /**< Data transfer length for the current job */
    MemIf_ModeType         mode;
    /**< Module mode setup for current job - SLOW for now */
    uint32                 jobChunkSize;
    /**< Length of Data to be transfer in current call cycle */
    OSPI_Handle            spiHandle;
    /**< Handle for the SPI object that will used in OSPI Driver */
    uint32                 offset;
    /** offset to an OSPI flash device*/
    uint32                 actual;
    /** Actual size to an OSPI flash device.*/
    uint32                 postBlankCheckFlashaddr;
    /** Flash Post Blank Check Address*/
    uint32                 prevFlashaddr;
    /**Flash Previous Address*/
    Fls_LengthType         transferred;
    /**<    Select the OSPI read/write transaction Lines */
    uint32                 baudRateDiv;
    /**<    To select the FLS baudrate Divider value */
    Fls_EraseType          typeoferase;
    /**<    To select the type of erase (sector erase/ block erase/ bulk erase) */
    uint32                 chipSelect;
    /**< Ospi Chip select number */
    uint32                 decChipSelect;
    /**< Decoder Chip select number */
    uint32                 dmaEnable;
    /**< Enable DMA mode */
    uint32                 frmFmt;
    /**< Ospi Frame Format */
    boolean                flsEdmaReadEnabled;
    /**<    To give error if dma is enabled but Interrupt/Memmap mode is off */
    uint32                 flsDmaStage;
    /**<    To select the stage of dma read (not started: FLS_S_READ_DMA_INIT_STAGE/
     * ongoing:FLS_S_READ_DMA_WAIT_STAGE/ completed: FLS_S_READ_DMA_DONE) */
    boolean                flsDmaConfigError;
    /**<    Dma Transfet Length */
    volatile uint32        flsDmaLength;
    /**<    Dma Destination Bufer */
    volatile uint8        *flsDmaDstBuf;
} Fls_DriverObjType;

/**< ENUM for Internal State type names */
typedef enum
{
    FLS_INTERNAL_JOB_WAIT = 0,
    FLS_INTERNAL_JOB_FAIL,
    FLS_INTERNAL_JOB_DONE
} Fls_InternalStateType;

extern Fls_DriverObjType Fls_DrvObj;

Std_ReturnType Nor_OspiCmdWrite(OSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 numAddrBytes, uint8 *txBuf,
                                uint32 txLen);
Std_ReturnType Nor_OspiCmdRead(OSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 numAddrBytes, uint8 dummyBits,
                               uint8 *rxBuf, uint32 rxLen);
Std_ReturnType Nor_OspiWaitDAC(OSPI_Handle handle, uint32 timeOut);
Std_ReturnType Nor_OspiWaitReady(OSPI_Handle handle, uint32 timeOut);
Std_ReturnType Nor_OspiReadId(OSPI_Handle handle);
Std_ReturnType Nor_OspiRead(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len);
Std_ReturnType Nor_OspiWrite(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len);
Std_ReturnType Fls_norBlockErase(OSPI_Handle handle, uint32 blkNum);
Std_ReturnType Fls_norSectorErase(OSPI_Handle handle, uint32 sectorNum);
Std_ReturnType Fls_norChipErase(OSPI_Handle handle, uint32 offset);
Std_ReturnType Nor_OspiSetQeBit(OSPI_Handle handle, uint8 qeType);
Std_ReturnType Nor_OspiSetOeBit(OSPI_Handle handle, uint8 oeType);

void  processJobs(Fls_JobType job);
uint8 Fls_norBlankCheck(uint32 actualChunkSize);
void  Fls_resetDrvObj(Fls_DriverObjType *drvObj);
void  Fls_copyConfig(Fls_DriverObjType *drvObj, const Fls_ConfigType *cfgPtr);

Std_ReturnType Fls_hwUnitInit(void);
Std_ReturnType Nor_OspiSet4ByteAddrMode(OSPI_Handle handle);
Std_ReturnType Nor_OspiSetAddressBytes(OSPI_Handle handle);
Std_ReturnType Fls_OspiSet3ByteAddress(void);
Std_ReturnType Fls_OspiSetResetPinMode(Fls_ResetPinMode pinMode);
Std_ReturnType Ospi_SetRegCfg(OSPI_Handle handle, const Fls_RegEnConfig *rCfg);
Std_ReturnType Nor_OspiRegWrite(OSPI_Handle handle, uint8 cmd, uint32 addr, uint8 data);
Std_ReturnType Nor_OspiRegRead(OSPI_Handle handle, uint8 cmd, uint32 addr, uint8 *data);
boolean        Fls_VerifyData_priv(const uint8 *expData, const uint8 *rxData, uint32 length);

Std_ReturnType Fls_norCompare(uint32 actualChunkSize);
void           Fls_JobDoneNotification(uint32 chunkSize, Fls_JobType job);
void           Fls_ErrorNotification(Fls_JobType job, uint8 retVal);
void           ReportFlsError(Fls_JobType job);
boolean        Fls_VerifyBlankCheck_priv(const uint8 *rxData, uint32 length);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FLS_BRD_NOR_OSPI_H_ */
