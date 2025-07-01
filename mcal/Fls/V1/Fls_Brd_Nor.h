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
 *  \file     Fls_Brd_Nor.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the FLS MCAL driver files.
 *
 */

#ifndef FLS_BRD_NOR_H_
#define FLS_BRD_NOR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "SchM_Fls.h"
#include "Fls_Cbk.h"
#include "Fls.h"
#include "Fls_Qspi.h"
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

#define NOR_CMD_RSTEN        (0x66U)
#define NOR_CMD_RST          (0x99U)
#define NOR_ERASED_DATA      (0xFF)
#define FLS_MPU_MSS_QSPI_REG (0x400C0000U)
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
    Fls_LengthType         length;
    /**< Data transfer length for the current job */
    MemIf_ModeType         mode;
    /**< Module mode setup for current job - SLOW for now */
    uint32                 jobChunkSize;
    /**< Length of Data to be transfer in current call cycle */
    QSPI_Handle            spiHandle;
    /**< Handle for the SPI object that will used in QSPI Driver */
    uint32                 offset;
    /** offset to an QSPI flash device*/
    uint32                 actual;
    /** Actual size to an QSPI flash device.*/
    uint32                 postBlankCheckFlashaddr;
    /** Flash Post Blank Check Address*/
    uint32                 prevFlashaddr;
    /**Flash Previous Address*/
    Fls_LengthType         transferred;
    /**<    Select the QSPI read/write transaction Lines */
    uint32                 flsBaudRateDiv;
    /**<    To select the FLS baudrate Divider value */
    Fls_EraseType          typeoferase;
    /**<    To select the type of erase (sector erase/ block erase/ bulk erase) */
} Fls_DriverObjType;

/**< ENUM for Internal State type names */
typedef enum
{
    FLS_INTERNAL_JOB_WAIT = 0,
    FLS_INTERNAL_JOB_FAIL,
    FLS_INTERNAL_JOB_DONE
} Fls_InternalStateType;

extern Fls_DriverObjType Fls_DrvObj;

/* ========================================================================== */
/*                           Typedefs                                         */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern Std_ReturnType Fls_hwUnitInit(void);

extern void processJobs(Fls_JobType job);

extern void Fls_resetDrvObj(Fls_DriverObjType *drvObj);

extern void Fls_copyConfig(Fls_DriverObjType *drvObj, const Fls_ConfigType *cfgPtr);

#if (STD_ON == FLS_REGISTER_READBACK_API)
void Fls_Qspi_RegisterReadback(P2VAR(Fls_RegisterReadbackType, AUTOMATIC, FLS_APPL_DATA) RegRbPtr);
#endif /*STD_ON == FLS_REGISTER_READBACK_API*/

/*========================================================================= */
/*                       Static Function Definitions                          */
/* ========================================================================== */

Std_ReturnType        Nor_QspiCmdRead(QSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 *rxBuf, uint32 rxLen);
Std_ReturnType        Nor_QspiCmdWrite(QSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 *txBuf, uint32 txLen);
Std_ReturnType        Nor_QspiWriteEnableLatched(QSPI_Handle handle, uint32 timeOut);
Std_ReturnType        Nor_QspiWaitReady(QSPI_Handle handle, uint32 timeOut);
Std_ReturnType        Nor_QspiReadId(QSPI_Handle handle);
Std_ReturnType        Fls_norOpen(void);
Std_ReturnType        Fls_norAsyncBlockErase_sub(void);
Std_ReturnType        Fls_norAsyncBlockErase(uint32 actualChunkSize);
Std_ReturnType        Fls_norAsyncSectorErase(uint32 actualChunkSize);
Std_ReturnType        Fls_norAsyncSectorErase_sub(void);
Std_ReturnType        Fls_norRead(uint32 actualChunkSize);
boolean               Fls_VerifyData_priv(const uint8 *expData, const uint8 *rxData, uint32 length);
boolean               Fls_VerifyBlankCheck_priv(const uint8 *rxData, uint32 length);
Std_ReturnType        Fls_norCompare(uint32 actualChunkSize);
uint8                 Fls_norBlankCheck(uint32 actualChunkSize);
void                  ReportFlsError(Fls_JobType job);
Fls_InternalStateType Nor_QspiAsyncWaitReady(QSPI_Handle handle, uint32 timeOut);
Std_ReturnType        Fls_norAsyncWrite(uint32 actualChunkSize);
void                  Fls_norAsyncWrite_sub(uint32 actualChunkSize);
Std_ReturnType        Fls_norAsyncChipErase(void);
Std_ReturnType        Nor_QspiSetQeBit(QSPI_Handle handle, uint8 qeType);
Std_ReturnType        Nor_QspiSetQeBit_sub(QSPI_Handle handle, uint8 qeType);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FLS_BRD_NOR_H_ */
