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
 *  \file     Fls_Brd_Nor_Qspi.c
 *
 *  This file contains FLS MCAL driver internal functions for Board Nor QSPI
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "string.h"
#include "Fls_Cbk.h"
#include "Fls_Brd_Nor.h"

#include "hw_types.h"
#include "Fls_Qspi_Edma.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define FLS_QSPI_NOR_SR_WIP       (1U << 0U)
#define FLS_QSPI_NOR_SR_WEL       (1U << 1U)
#define FLS_QSPI_ID_CODE_SIZE_MAX (8U)
#define FLS_BLANKCHECK_SIZE_MAX   (4096U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void           Fls_JobDoneNotification(Fls_JobType job, uint32 chunkSize);
static void           Fls_JobDoneNotification1(Fls_JobType job, uint32 chunkSize);
static void           Fls_JobErrorNotificationFxn(Fls_JobType job, Std_ReturnType retVal);
static void           Fls_JobErrorNotification1(Fls_JobType job, Std_ReturnType retVal);
static Std_ReturnType Fls_CallNorErase(uint32 chunkSize);
static uint32         Fls_setchuncksize(void);
static Std_ReturnType Fls_norOpen_sub(QSPI_Handle handle, QSPI_Object *object);
static Std_ReturnType Fls_norQspiAsyncWaitReadyBlock(Fls_InternalStateType retstatus);
static Std_ReturnType Fls_norQspiAsyncWaitReadyChip(Fls_InternalStateType retstatus);
static Std_ReturnType Fls_norQspiAsyncWaitReadysector(Fls_InternalStateType retstatus);
static void           Fls_JobNotification(Fls_JobType job, Std_ReturnType retVal, uint32 chunkSize);
static uint8          Fls_check_Memmap_Enabled_DMA(void);
static uint8          Fls_norDmaRead(void);
void                  ReportFlsError(Fls_JobType job);
static void           Flash_offsetToBlkPage(uint32 offset, uint32 *Length);
static Std_ReturnType Fls_norAsyncWrite_sub1(void);
static Std_ReturnType Fls_norOpen_sub1(void);
static Std_ReturnType Nor_cmdwr_Enable(QSPI_Handle handle);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define FLS_START_SEC_VAR_NO_INIT_8
#include "Fls_MemMap.h"

/* Compare and BlankCheck Arrays to store data to compare */
VAR(uint8, FLS_VAR_NO_INIT) Fls_BlankCheckRxDataBuf[FLS_BLANKCHECK_SIZE_MAX];
VAR(uint8, FLS_VAR_NO_INIT) Fls_CompareRxDataBuf[FLS_BLANKCHECK_SIZE_MAX];

#define FLS_STOP_SEC_VAR_NO_INIT_8
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT_8
#include "Fls_MemMap.h"
volatile VAR(uint8, FLS_VAR_INIT) FlsEraseStage = FLS_S_DEFAULT;
volatile VAR(uint8, FLS_VAR_INIT) FlsWriteStage = FLS_S_INIT_STAGE;
#define FLS_STOP_SEC_VAR_INIT_8
#include "Fls_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

/**
 *  \Function Name: Nor_QspiCmdRead
 *
 *  This function perform read operation for QSPI protocol by passing command
 *  and will get corresponding data
 *
 *
 */
Std_ReturnType Nor_QspiCmdRead(QSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 *rxBuf, uint32 rxLen)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    QSPI_CmdParams rdParams;

    if (Fls_Qspi_ParamsInit(&rdParams) == (Std_ReturnType)E_OK)
    {
        rdParams.cmd       = cmd;
        rdParams.cmdAddr   = cmdAddr;
        rdParams.rxDataBuf = rxBuf;
        rdParams.txDataBuf = NULL_PTR;
        rdParams.DataLen   = rxLen;

        if (handle != NULL_PTR)
        {
            if (Fls_Qspi_ReadCmd(handle, &rdParams) == (Std_ReturnType)E_OK)
            {
                retVal = (Std_ReturnType)E_OK;
            }
            else
            {
                retVal = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

/**
 *  \Function Name: Nor_QspiCmdWrite
 *
 *  This function perform write operation for QSPI protocol through the passing
 *  Command
 *
 */
Std_ReturnType Nor_QspiCmdWrite(QSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 *txBuf, uint32 txLen)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    QSPI_CmdParams wrParams;
    if (Fls_Qspi_ParamsInit(&wrParams) == (Std_ReturnType)E_OK)
    {
        wrParams.cmd       = cmd;
        wrParams.cmdAddr   = cmdAddr;
        wrParams.txDataBuf = txBuf;
        wrParams.rxDataBuf = NULL_PTR;
        wrParams.DataLen   = txLen;
        if (handle != NULL_PTR)
        {
            if (Fls_Qspi_WriteCmd(handle, &wrParams) == (Std_ReturnType)E_OK)
            {
                retVal = (Std_ReturnType)E_OK;
            }
            else
            {
                retVal = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    return retVal;
}

/**
 *  \Function Name: Nor_QspiWriteEnableLatched
 *
 *  This function enable the latch for write opearation.
 *
 */
Std_ReturnType Nor_QspiWriteEnableLatched(QSPI_Handle handle, uint32 timeOut)
{
    Std_ReturnType  retVal         = (Std_ReturnType)E_NOT_OK;
    uint8           stepcmd        = 0U;
    uint8           readStatus[4U] = {0U};
    uint8           cmd            = 0U;
    volatile uint32 tempCount      = timeOut * 16U;
    cmd                            = fls_config_sfdp->cmdRdsr;
    do
    {
        if (tempCount <= 0U)
        {
            stepcmd = 1U;
        }
        if (stepcmd == 0U)
        {
            retVal = Nor_QspiCmdRead(handle, cmd, FLS_QSPI_CMD_INVALID_ADDR, &readStatus[0U], 1);
            if (retVal != (Std_ReturnType)E_OK)
            {
                stepcmd = 1U;
            }
        }
        if (stepcmd == 1U)
        {
            break;
        }
        MCAL_SW_DELAY(tempCount);
    } while ((readStatus[0U] & FLS_QSPI_NOR_SR_WEL) == 0U);

    if (tempCount == (uint32)0U)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((readStatus[0U] & FLS_QSPI_NOR_SR_WEL) != (uint8)0U)
    {
        retVal = (Std_ReturnType)E_OK;
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

/**
 *  \Function Name: Nor_QspiWaitReady
 *
 *  This function will perform delay opearation for QSPI read untill
 *  will get read status.
 *
 */
Std_ReturnType Nor_QspiWaitReady(QSPI_Handle handle, uint32 timeOut)
{
    Std_ReturnType  retVal    = (Std_ReturnType)E_OK;
    volatile uint32 tempCount = timeOut;
    if (timeOut > 9U)
    {
        tempCount = timeOut / 9U;
    }
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    uint8 stepcmd        = 0U;
    uint8 readStatus[4U] = {0U};
    uint8 cmd            = 0U;

    cmd = fls_config_sfdp->cmdRdsr;

    do
    {
        if (tempCount <= 0U)
        {
            stepcmd = 1U;
        }
        if (stepcmd == 0U)
        {
            retVal = Nor_QspiCmdRead(handle, cmd, FLS_QSPI_CMD_INVALID_ADDR, &readStatus[0U], 1);
            if (retVal == (Std_ReturnType)E_NOT_OK)
            {
                stepcmd = 1U;
            }
        }
        if (stepcmd == 1U)
        {
            break;
        }
        MCAL_SW_DELAY(tempCount);
    } while ((readStatus[0U] & FLS_QSPI_NOR_SR_WIP) != (uint32)0);

    if ((readStatus[0U] & FLS_QSPI_NOR_SR_WIP) == 0U)
    {
        retVal = (Std_ReturnType)E_OK;
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

/**
 *  \Function Name: Nor_QspiAsyncWaitReady
 *
 *  This function will perform delay opearation for QSPI read untill
 *  will get read status.
 *
 */
Fls_InternalStateType Nor_QspiAsyncWaitReady(QSPI_Handle handle, uint32 timeOut)
{
    Std_ReturnType        retVal1        = E_OK;
    Fls_InternalStateType retVal         = FLS_INTERNAL_JOB_WAIT;
    uint8                 readStatus[4U] = {0U};
    uint8                 cmd            = 0U;

    cmd = fls_config_sfdp->cmdRdsr;

    retVal1 = Nor_QspiCmdRead(handle, cmd, FLS_QSPI_CMD_INVALID_ADDR, &readStatus[0U], 1);

    if (retVal1 == E_NOT_OK)
    {
        retVal = FLS_INTERNAL_JOB_FAIL;
    }
    else
    {
        /* Check for Status. */
        if ((readStatus[0U] & FLS_QSPI_NOR_SR_WIP) == (uint8)0U)
        {
            retVal = FLS_INTERNAL_JOB_DONE;
        }
    }

    return retVal;
}

/**
 *  \Function Name: Nor_QspiReadId
 *
 *  This function check the device id and manufacture id for external flash.
 *
 */
Std_ReturnType Nor_QspiReadId(QSPI_Handle handle)
{
    Std_ReturnType retVal    = (Std_ReturnType)E_OK;
    uint8          idCode[3] = {0};
    uint32         manufacturerId;
    uint32         deviceId;
    uint8          cmd = fls_config_sfdp->idCfg.cmd;

    retVal = Nor_QspiCmdRead(handle, cmd, FLS_QSPI_CMD_INVALID_ADDR, idCode, fls_config_sfdp->idCfg.numBytes);

    if (retVal == (Std_ReturnType)E_OK)
    {
        manufacturerId = (uint32)idCode[0];
        deviceId       = ((uint32)idCode[1] << 8U) | ((uint32)idCode[2]);
        if (manufacturerId != fls_config_sfdp->manfId)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else if (deviceId != fls_config_sfdp->deviceId)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            retVal = (Std_ReturnType)E_OK;
        }
    }
    return retVal;
}

/**
 *  \Function Name: Fls_norOpen
 *
 *  This function invokes Fls_QspiOpen and checks the device and manufacture id
 *
 */
Std_ReturnType Fls_norOpen(void)
{
    Std_ReturnType retVal = E_OK;
    QSPI_Handle    handle;
    QSPI_Object   *object;

    Fls_DrvObj.spiHandle = Fls_QspiOpen(0U);
    handle               = Fls_DrvObj.spiHandle;
    if (Fls_DrvObj.spiHandle == NULL_PTR)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        object = ((QSPI_Config *)handle)->object;
    }
    if (retVal == E_OK)
    {
        retVal = Fls_norOpen_sub1();
        if (retVal == E_OK)
        {
            retVal = Fls_norOpen_sub(handle, object);
        }
    }
    return (retVal);
}

static Std_ReturnType Fls_norOpen_sub(QSPI_Handle handle, QSPI_Object *object)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    switch (Fls_DrvObj.Fls_Mode)
    {
        case FLS_QSPI_RX_LINES_SINGLE:
            object->writeCmd     = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_SINGLE].cmdWr;
            object->readCmd      = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_SINGLE].cmdRd;
            object->numDummyBits = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_SINGLE].dummyClksRd;
            object->numAddrBytes = fls_config_sfdp->addrnumBytes;
            break;
        case FLS_QSPI_RX_LINES_DUAL:
            object->writeCmd     = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_DUAL].cmdWr;
            object->readCmd      = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_DUAL].cmdRd;
            object->numDummyBits = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_DUAL].dummyClksRd;
            object->numAddrBytes = fls_config_sfdp->addrnumBytes;
            break;
        case FLS_QSPI_RX_LINES_QUAD:
            object->writeCmd     = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].cmdWr;
            object->readCmd      = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].cmdRd;
            object->numDummyBits = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].dummyClksRd;
            object->numAddrBytes = fls_config_sfdp->addrnumBytes;
            retVal               = Nor_QspiSetQeBit(handle, fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].enableType);
            break;
        default:
            object->writeCmd     = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].cmdWr;
            object->readCmd      = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].cmdRd;
            object->numDummyBits = fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].dummyClksRd;
            object->numAddrBytes = fls_config_sfdp->addrnumBytes;
            retVal               = Nor_QspiSetQeBit(handle, fls_config_sfdp->protos[FLS_QSPI_RX_LINES_QUAD].enableType);
            break;
    }
    if (retVal == E_OK)
    {
        if (Nor_QspiReadId(handle) == E_OK)
        {
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

static Std_ReturnType Fls_norOpen_sub1(void)
{
    Std_ReturnType retVal = E_OK;
    uint8          cmd;
    /* Reset the Flash */
    cmd = NOR_CMD_RSTEN;
    if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmd, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0U) == E_OK)
    {
        cmd = NOR_CMD_RST;
        if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmd, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0U) == E_OK)
        {
            if (Nor_QspiWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->wrrwriteTimeout) == E_OK)
            {
                retVal = E_OK;
            }
            else
            {
                retVal = E_NOT_OK;
            }
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }
    return retVal;
}

/**
 *  \Function Name: Fls_hwUnitInit
 *
 *  This function initialize Hardware
 *
 */
Std_ReturnType Fls_hwUnitInit(void)
{
    Std_ReturnType retVal;
    QSPI_Handle    handle = NULL_PTR;

    (void)Fls_QspiHwInit();

    retVal = Fls_norOpen();

    handle = Fls_DrvObj.spiHandle;

    if (handle != NULL_PTR)
    {
        if (retVal != (Std_ReturnType)E_NOT_OK)
        {
            retVal = (Std_ReturnType)E_OK;
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

#if (FLS_DMA_ENABLE == STD_ON)
    if (retVal == E_OK)
    {
        retVal = Fls_Qspi_dmaChInit(Fls_DrvObj);
    }
#endif
    return retVal;
}

/**
 *  \Function Name: ReportFlsError
 *
 *  This function invoke Det_ReportTransientFault.this will report DET.
 *
 *
 */
void ReportFlsError(Fls_JobType job)
{
    switch (job)
    {
        case FLS_JOB_COMPARE:
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_COMPARE_FAILED);
            break;
        case FLS_JOB_ERASE:
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_ERASE_FAILED);
            break;
        case FLS_JOB_READ:
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_READ_FAILED);
            break;
        case FLS_JOB_WRITE:
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_WRITE_FAILED);
            break;
        default:
            break;
    }
    Fls_DrvObj.jobResultType = MEMIF_JOB_FAILED;
    Fls_DrvObj.status        = MEMIF_IDLE;
}

/**
 *  \Function Name: processJobs
 *
 *  This function invoke
 * Fls_norCompare,Fls_norBlockErase,Fls_norSectorErase,Fls_norChipErase,Fls_norRead,Fls_norWrite and
 * Fls_norBlankCheck function. it will perform any one function based on jobtype
 *
 *
 */
void processJobs(Fls_JobType job)
{
    uint32         chunkSize = 0;
    Std_ReturnType retVal    = E_NOT_OK;
#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
    Fls_AddressType prevFlashaddr;
    prevFlashaddr                  = 0;
    uint32 norblankmaxchunkSize    = FLS_BLANKCHECK_SIZE_MAX;
    uint32 postBlankCheckFlashaddr = 0;
#endif
    /*Get the MIN of two*/
    Fls_DrvObj.flsEdmaReadEnabled = FALSE;
    chunkSize                     = Fls_setchuncksize();

    SchM_Enter_Fls_FLS_EXCLUSIVE_AREA_0();

    switch (job)
    {
        case FLS_JOB_COMPARE:
            retVal = Fls_norCompare(chunkSize);
            break;
        case FLS_JOB_ERASE:

#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
            Fls_DrvObj.prevFlashaddr           = Fls_DrvObj.flashAddr;
            prevFlashaddr                      = Fls_DrvObj.prevFlashaddr;
            Fls_DrvObj.postBlankCheckFlashaddr = prevFlashaddr + chunkSize;
            postBlankCheckFlashaddr            = Fls_DrvObj.postBlankCheckFlashaddr;
#endif

            retVal = Fls_CallNorErase(chunkSize);

#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
            if ((FlsEraseStage == FLS_S_DEFAULT) && (retVal == E_OK))
            {
                while (prevFlashaddr < postBlankCheckFlashaddr) /* to allow Fls_norBlankCheck to work for larger
                                                                   chunksize (>4KB) */
                {
                    Fls_DrvObj.flashAddr = prevFlashaddr;
                    retVal               = Fls_norBlankCheck(norblankmaxchunkSize);
                    prevFlashaddr        = prevFlashaddr + norblankmaxchunkSize;
                }
                Fls_DrvObj.flashAddr = postBlankCheckFlashaddr;
            }
#endif
            break;
        case FLS_JOB_READ:
#if (FLS_DMA_ENABLE == STD_ON)
            retVal    = Fls_norDmaRead();
            chunkSize = Fls_DrvObj.length;
#else
            if (Fls_DrvObj.flsDmaStage == FLS_S_READ_DMA_INIT_STAGE)
            {
                retVal = Fls_norRead(chunkSize);
            }
#endif
            break;
        case FLS_JOB_WRITE:

#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
            if ((FlsWriteStage == FLS_S_WRITE_DONE) && (Fls_norBlankCheck(chunkSize) != E_OK))
            {
                break;
            }
#endif

            retVal = Fls_norAsyncWrite(chunkSize);

#if (STD_ON == FLS_WRITE_VERIFICATION_ENABLED)
            if ((FlsWriteStage == FLS_S_WRITE_DONE) && (retVal == E_OK))
            {
                retVal = Fls_norCompare(chunkSize);
            }
            else
            {
                /* Do Nothing */
            }

#endif
            break;

        case FLS_JOB_BLANKCHECK:
            retVal = Fls_norBlankCheck(chunkSize);
            break;

        default:
            retVal = E_NOT_OK;
            break;
    }
    Fls_JobNotification(job, retVal, chunkSize);

    SchM_Exit_Fls_FLS_EXCLUSIVE_AREA_0();

    return;
}

static uint8 Fls_norDmaRead(void)
{
    Std_ReturnType retVal    = E_OK;
    uint32         chunkSize = 0;
    chunkSize                = Fls_DrvObj.length;
    retVal                   = Fls_DrvObj.flsDmaConfigError;
    if (retVal == E_OK)
    {
        Fls_DrvObj.flsEdmaReadEnabled = TRUE;
        if (Fls_DrvObj.flsDmaStage == FLS_S_READ_DMA_INIT_STAGE)
        {
            retVal = Fls_norRead(chunkSize);
        }
    }
    return retVal;
}

static void Fls_JobNotification(Fls_JobType job, Std_ReturnType retVal, uint32 chunkSize)
{
    if (retVal == E_OK)
    {
        Fls_JobDoneNotification1(job, chunkSize);
    }
    else /*if retval == E_NOT_OK or E_COMPARE_MISMATCH*/
    {
        Fls_JobErrorNotificationFxn(job, retVal);
    }
}

static uint8 Fls_check_Memmap_Enabled_DMA(void)
{
    uint8 retVal = E_OK;
#if ((STD_OFF == FLS_MEM_MAP_MODE) && (STD_ON == FLS_DMA_ENABLE))
    retVal = FLS_E_MEMAP_INTERRUPT_OFF_DMA_ON;
#endif
    return retVal;
}
static uint32 Fls_setchuncksize(void)
{
    uint32 chunkSize = 0;
    if (Fls_DrvObj.length < Fls_DrvObj.jobChunkSize)
    {
        chunkSize = Fls_DrvObj.length;
    }
    else
    {
        chunkSize = Fls_DrvObj.jobChunkSize;
    }
    return chunkSize;
}

static Std_ReturnType Fls_CallNorErase(uint32 chunkSize)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (FlsEraseStage == FLS_S_DEFAULT)
    {
        FlsEraseStage = FLS_S_INVALID_ADDRESS;
    }
    if (Fls_DrvObj.typeoferase == FLS_SECTOR_ERASE)
    {
        retVal = Fls_norAsyncSectorErase(chunkSize);
    }
    else if (Fls_DrvObj.typeoferase == FLS_BLOCK_ERASE)
    {
        retVal = Fls_norAsyncBlockErase(chunkSize);
    }
    else
    {
        retVal = Fls_norAsyncChipErase();
    }
    return retVal;
}
static void Fls_JobDoneNotification1(Fls_JobType job, uint32 chunkSize)
{
    switch (job)
    {
        case FLS_JOB_WRITE:
            if (FLS_S_WRITE_DONE == FlsWriteStage)
            {
                Fls_JobDoneNotification(job, chunkSize);
            }
            break;
        case FLS_JOB_ERASE:
            if (FLS_S_DEFAULT == FlsEraseStage)
            {
                Fls_JobDoneNotification(job, chunkSize);
            }
            break;
        case FLS_JOB_COMPARE:
            Fls_JobDoneNotification(job, chunkSize);
            break;
        case FLS_JOB_READ:
#if (FLS_DMA_ENABLE == STD_ON)
            if ((Fls_DrvObj.flsDmaStage == FLS_S_READ_DMA_DONE) || (Fls_DrvObj.flsEdmaReadEnabled == FALSE))
            {
                Fls_JobDoneNotification(job, chunkSize);
            }
#else
            Fls_JobDoneNotification(job, chunkSize);
#endif

            break;
        case FLS_JOB_BLANKCHECK:
            Fls_JobDoneNotification(job, chunkSize);
            break;
        default:
            break;
    }
}
static void Fls_JobDoneNotification(Fls_JobType job, uint32 chunkSize)
{
    uint32 Fls_len     = 0;
    Fls_DrvObj.ramAddr = &Fls_DrvObj.ramAddr[chunkSize];
    if (job != FLS_JOB_ERASE)
    {
        Fls_DrvObj.flashAddr += chunkSize;
    }
#if (STD_OFF == FLS_TIMEOUT_SUPERVISION_ENABLED)
    if (job == FLS_JOB_ERASE)
    {
        Fls_DrvObj.flashAddr += chunkSize;
    }
#endif
    Fls_DrvObj.flsDmaStage  = FLS_S_READ_DMA_INIT_STAGE;
    Fls_DrvObj.length      -= chunkSize;
    Fls_DrvObj.transferred += chunkSize;
    FlsWriteStage           = FLS_S_INIT_STAGE;

    if (0U == Fls_DrvObj.length)
    {
        Fls_DrvObj.jobResultType = MEMIF_JOB_OK;
        Fls_DrvObj.status        = MEMIF_IDLE;
        Fls_DrvObj.jobType       = FLS_JOB_NONE;
        Fls_DrvObj.transferred   = Fls_len;
        if (Fls_DrvObj.Fls_JobEndNotification != NULL_PTR)
        {
            Fls_DrvObj.Fls_JobEndNotification();
        }
    }
}

static void Fls_JobErrorNotificationFxn(Fls_JobType job, Std_ReturnType retVal)
{
    if (E_BLANKCHECK_MISMATCH == retVal)
    {
        Fls_JobErrorNotification1(job, retVal);
    }
    else if (E_COMPARE_MISMATCH == retVal)
    {
        Fls_JobErrorNotification1(job, retVal);
    }
    else if (FLS_E_MEMAP_INTERRUPT_OFF_DMA_ON == retVal)
    {
        Fls_JobErrorNotification1(job, retVal);
    }
    else /*if retVal == E_NOT_OK*/
    {
        /*Hardware/driver internal error occured*/
        ReportFlsError(job);
        if (Fls_DrvObj.Fls_JobErrorNotification != NULL_PTR)
        {
            Fls_DrvObj.Fls_JobErrorNotification();
        }
#if (STD_ON == FLS_USE_INTERRUPTS)
        /* disable and clear the interrupts */
        Fls_QspiIntDisable((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
        Fls_QspiIntClear((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
#endif
    }
}

static void Fls_JobErrorNotification1(Fls_JobType job, Std_ReturnType retVal)
{
    uint32 Fls_len         = 0;
    Fls_DrvObj.status      = MEMIF_IDLE;
    Fls_DrvObj.jobType     = FLS_JOB_NONE;
    Fls_DrvObj.transferred = Fls_len;
    Fls_DrvObj.flsDmaStage = FLS_S_READ_DMA_INIT_STAGE;
    if (FLS_JOB_BLANKCHECK == job)
    {
        Fls_DrvObj.jobResultType = MEMIF_BLOCK_INCONSISTENT;
#if (STD_OFF == FLS_USE_INTERRUPTS)
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION, FLS_E_VERIFY_ERASE_FAILED);
#else
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK, FLS_E_VERIFY_ERASE_FAILED);
#endif
    }
    else if (FLS_JOB_ERASE == job)
    {
#if (STD_OFF == FLS_USE_INTERRUPTS)
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION, FLS_E_VERIFY_ERASE_FAILED);
#else
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK, FLS_E_VERIFY_ERASE_FAILED);
#endif
    }
    else /*if (FLS_JOB_COMPARE == job)*/
    {
        Fls_DrvObj.jobResultType = MEMIF_BLOCK_INCONSISTENT;
#if ((STD_OFF == FLS_MEM_MAP_MODE) && (STD_ON == FLS_DMA_ENABLE))
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_MEMAP_INTERRUPT_OFF_DMA_ON);
#elif (STD_OFF == FLS_USE_INTERRUPTS)
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION, FLS_E_VERIFY_WRITE_FAILED);
#else
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_VERIFY_WRITE_FAILED);
#endif
    }
    if (Fls_DrvObj.Fls_JobErrorNotification != NULL_PTR)
    {
        Fls_DrvObj.Fls_JobErrorNotification();
    }
#if (STD_ON == FLS_USE_INTERRUPTS)
    /* disable and clear the interrupts */
    (void)Fls_QspiIntDisable((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
    (void)Fls_QspiIntClear((QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK | QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK));
#endif
}
/**
 *  \Function Name: Fls_VerifyData_priv
 *
 *  This function included in Fls_norCompare and verify data,if any mismatch
 *  return FALSE
 *
 */
boolean Fls_VerifyData_priv(const uint8 *expData, const uint8 *rxData, uint32 length)
{
    uint32  idx           = 0U;
    uint32  match         = TRUE;
    boolean retVal        = FALSE;
    uint8  *expData_local = (uint8 *)expData;
    uint8  *rxData_local  = (uint8 *)rxData;

    for (idx = (uint32)0; ((idx < length)); idx++)
    {
        if (*expData_local != *rxData_local)
        {
            match = FALSE;
            /*Stop after first mismatch*/
            break;
        }
        expData_local++;
        rxData_local++;
    }
    if (match == TRUE)
    {
        retVal = TRUE;
    }
    return retVal;
}

/**
 *  \Function Name: Fls_norCompare
 *
 *  This function Compares flash memory, if any mismatch return E_NOT_OK
 *
 */

/**
 *  \Function Name: Fls_VerifyBlankCheck_priv
 *
 *  This function included in Fls_norBlanCheck and verify data,if any mismatch
 *  return FALSE
 *
 */
boolean Fls_VerifyBlankCheck_priv(const uint8 *rxData, uint32 length)
{
    uint32  idx          = 0U;
    uint32  match        = TRUE;
    boolean retVal       = FALSE;
    uint8   expData      = NOR_ERASED_DATA;
    uint8  *rxData_local = (uint8 *)rxData;
    while (idx < length)
    {
        if (match != 0U)
        {
            if (expData != *rxData_local)
            {
                match = FALSE;
            }
            rxData_local++;
        }
        idx++;
    }
    if (match == TRUE)
    {
        retVal = TRUE;
    }
    return retVal;
}

/**
 *  \Function Name: Fls_norCompare
 *
 *  This function Compares flash memory, if any mismatch return E_NOT_OK
 *
 */

Std_ReturnType Fls_norCompare(uint32 actualChunkSize)
{
    uint32         addr         = Fls_DrvObj.flashAddr;
    uint32         len          = actualChunkSize;
    uint8         *readData_buf = Fls_CompareRxDataBuf;
    uint8         *expData_Buf  = Fls_DrvObj.ramAddr;
    Std_ReturnType retVal       = (Std_ReturnType)E_OK;

    if (actualChunkSize > 0U)
    {
        QSPI_Transaction transaction;
        Fls_Qspi_TransactionInit(&transaction);
        transaction.addrOffset = addr;
        transaction.buf        = (void *)readData_buf;
        transaction.count      = len;
#if (FLS_MEM_MAP_MODE == (STD_ON))
        retVal = Fls_Qspi_ReadMemMapMode(Fls_DrvObj.spiHandle, &transaction);
#else
        retVal = Fls_Qspi_ReadConfigMode(Fls_DrvObj.spiHandle, &transaction);
#endif
        if ((Std_ReturnType)E_OK == retVal)
        {
            if (Fls_VerifyData_priv(expData_Buf, (const uint8 *)transaction.buf, len) == TRUE)
            {
                retVal = (Std_ReturnType)E_OK;
            }
            else
            {
                retVal = E_COMPARE_MISMATCH;
            }
        }
        else
        {
            /* No Actions Required. */
        }
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK; /* Handle is NULL*/
    }
    return retVal;
}
/**
 *  \Function Name: Fls_norBlankCheck
 *
 *  Fls_norBlankCheck shall verify, whether a given memory area has been
 *  erased
 *
 */
uint8 Fls_norBlankCheck(uint32 actualChunkSize)
{
    QSPI_Handle handle;
    uint32      addr         = Fls_DrvObj.flashAddr;
    uint32      len          = actualChunkSize;
    uint8      *readData_buf = Fls_BlankCheckRxDataBuf;
    uint8       retVal       = (uint8)E_OK;
    handle                   = Fls_DrvObj.spiHandle;

    if (handle != NULL_PTR)
    {
        QSPI_Transaction transaction;
        Fls_Qspi_TransactionInit(&transaction);
        transaction.addrOffset = addr;
        transaction.buf        = (void *)readData_buf;
        transaction.count      = len;
        retVal                 = Fls_Qspi_ReadMemMapMode(Fls_DrvObj.spiHandle, &transaction);

        if ((uint8)E_OK == retVal)
        {
            if (Fls_VerifyBlankCheck_priv((const uint8 *)transaction.buf, len) == TRUE)
            {
                retVal = (uint8)E_OK;
            }
            else
            {
                retVal = E_BLANKCHECK_MISMATCH;
            }
        }
    }
    else
    {
        retVal = (uint8)E_NOT_OK; /*Handle is NULL_PTR*/
    }
    return retVal;
}
/**
 *  \Function Name: Fls_norRead
 *
 *   This function read flash memory
 *
 */
Std_ReturnType Fls_norRead(uint32 actualChunkSize)
{
    Std_ReturnType retVal = E_OK;
    uint32         offset = Fls_DrvObj.flashAddr;
    uint8         *buf    = Fls_DrvObj.ramAddr;
    if (retVal == E_OK)
    {
        if (actualChunkSize > 0U)
        {
            QSPI_Transaction transaction;

            Fls_Qspi_TransactionInit(&transaction);
            transaction.addrOffset = offset;
            transaction.buf        = (void *)buf;
            transaction.count      = actualChunkSize;
#if (FLS_MEM_MAP_MODE == (STD_ON))
            retVal = Fls_Qspi_ReadMemMapMode(Fls_DrvObj.spiHandle, &transaction);
#else
            retVal = Fls_Qspi_ReadConfigMode(Fls_DrvObj.spiHandle, &transaction);
#endif
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    return retVal;
}

/**
 *  \Function Name: Fls_norAsyncWrite
 *
 *   This function Async Write to flash
 *
 */
Std_ReturnType Fls_norAsyncWrite(uint32 actualChunkSize)
{
    Std_ReturnType        retVal     = E_OK;
    Fls_InternalStateType readStatus = FLS_INTERNAL_JOB_WAIT;
    uint32                pageSize, chunkLen;

    pageSize = fls_config_sfdp->pageSize;
    chunkLen = pageSize;
    if (FlsWriteStage == FLS_S_INIT_STAGE)
    {
        if (actualChunkSize > 0U)
        {
            retVal = Fls_norAsyncWrite_sub1();

            if (retVal == E_OK)
            {
                Fls_norAsyncWrite_sub(actualChunkSize);
            }
            else
            {
                retVal = E_NOT_OK;
            }
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    else
    {
        readStatus = Nor_QspiAsyncWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->flashWriteTimeout);

        if (readStatus == FLS_INTERNAL_JOB_DONE)
        {
            retVal = E_OK;
            if ((actualChunkSize - Fls_DrvObj.actual) < (pageSize))
            {
                chunkLen = (actualChunkSize - Fls_DrvObj.actual);
            }
            else
            {
                chunkLen = pageSize;
            }
            Flash_offsetToBlkPage(Fls_DrvObj.offset, &chunkLen);
            Fls_DrvObj.offset += chunkLen;
            Fls_DrvObj.actual += chunkLen;
            FlsWriteStage      = FLS_S_INIT_STAGE;

            /* after writing data checking for Fls_DrvObj.actual if written data is equals to
             * actualChunkSize  making Fls_DrvObj.actual as zero    */
            if (Fls_DrvObj.actual >= actualChunkSize)
            {
                FlsWriteStage     = FLS_S_WRITE_DONE;
                Fls_DrvObj.actual = 0U;
            }
        }
        else if (readStatus == FLS_INTERNAL_JOB_FAIL)
        {
            retVal        = E_NOT_OK;
            FlsWriteStage = FLS_S_INIT_STAGE;
        }
        else
        {
            retVal = E_OK;
        }
    }

    return retVal;
}

static void Flash_offsetToBlkPage(uint32 offset, uint32 *Length)
{
    uint32 pageSize = fls_config_sfdp->pageSize;
    uint32 leftover;

    leftover = pageSize - (offset % pageSize);
    if (leftover != 0U)
    {
        if (*Length < leftover)
        {
            /*Do Nothing*/
        }
        else
        {
            *Length = leftover;
        }
    }

    return;
}

void Fls_norAsyncWrite_sub(uint32 actualChunkSize)
{
    uint32         pageSize, chunkLen;
    Std_ReturnType retVal = E_OK;
    pageSize              = fls_config_sfdp->pageSize;
    chunkLen              = pageSize;
    uint8           *buf  = Fls_DrvObj.ramAddr;
    QSPI_Transaction transaction;

    if ((actualChunkSize - Fls_DrvObj.actual) < (pageSize))
    {
        chunkLen = (actualChunkSize - Fls_DrvObj.actual);
    }
    else
    {
        chunkLen = pageSize;
    }
    Fls_Qspi_TransactionInit(&transaction);
    Flash_offsetToBlkPage(Fls_DrvObj.offset, &chunkLen);
    transaction.addrOffset = Fls_DrvObj.offset;
    transaction.buf        = (void *)(buf + Fls_DrvObj.actual);
    transaction.count      = chunkLen;
    retVal                 = Fls_Qspi_WriteConfigMode(Fls_DrvObj.spiHandle, &transaction);

    if (retVal == E_OK)
    {
        FlsWriteStage = FLS_S_WAIT_STAGE;
    }
    return;
}

static Std_ReturnType Fls_norAsyncWrite_sub1(void)
{
    Std_ReturnType retVal  = E_OK;
    uint8          cmdWren = fls_config_sfdp->cmdWren;
    retVal                 = Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmdWren, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0U);

    if (retVal == E_OK)
    {
        retVal = Nor_QspiWriteEnableLatched(Fls_DrvObj.spiHandle, fls_config_sfdp->wrrwriteTimeout);
    }
    return retVal;
}

/**
 *  \Function Name: Fls_norAsyncBlockErase
 *
 *   Function to perform sector erase in the flash
 *
 */
Std_ReturnType Fls_norAsyncBlockErase(uint32 actualChunkSize)
{
    Std_ReturnType retVal = E_OK;
    if (actualChunkSize == 0U)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        retVal = Fls_norAsyncBlockErase_sub();
    }
    return retVal;
}

Std_ReturnType Fls_norAsyncBlockErase_sub(void)
{
    Std_ReturnType        retVal    = E_OK;
    Fls_InternalStateType retstatus = FLS_INTERNAL_JOB_WAIT;
    uint8                 cmd       = fls_config_sfdp->eraseCfg.cmdBlockErase3B;
    uint32                cmdAddr   = Fls_DrvObj.flashAddr;
    uint8                 cmdWren   = fls_config_sfdp->cmdWren;
    switch (FlsEraseStage)
    {
        case FLS_S_INVALID_ADDRESS:
        {
            if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmdWren, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0U) == E_OK)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DELAY_1_STAGE;
            }
            else
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            break;
        }

        case FLS_S_DELAY_1_STAGE:
        {
            retstatus = Nor_QspiAsyncWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->wrrwriteTimeout);
            retVal    = Fls_norQspiAsyncWaitReadyBlock(retstatus);
            break;
        }

        case FLS_S_BLOCK_CMD_STAGE:
        {
            if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmd, cmdAddr, NULL, 0U) == E_OK)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DELAY_2_STAGE;
            }
            else
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            break;
        }

        case FLS_S_DELAY_2_STAGE:
        {
            retstatus = Nor_QspiAsyncWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->chipEraseTimeout);
            if (retstatus == FLS_INTERNAL_JOB_DONE)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            else if (retstatus == FLS_INTERNAL_JOB_FAIL)
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            else
            {
                /* No Actions required. */
            }
            break;
        }

        default:
            break;
    }
    return retVal;
}

static Std_ReturnType Fls_norQspiAsyncWaitReadyBlock(Fls_InternalStateType retstatus)
{
    Std_ReturnType retVal = E_OK;
    if (retstatus == FLS_INTERNAL_JOB_DONE)
    {
        retVal        = E_OK;
        FlsEraseStage = FLS_S_BLOCK_CMD_STAGE;
    }
    else if (retstatus == FLS_INTERNAL_JOB_FAIL)
    {
        retVal        = E_NOT_OK;
        FlsEraseStage = FLS_S_DEFAULT;
    }
    else
    {
        /* No Actions required. */
    }
    return retVal;
}
/**
 *  \Function Name: Fls_copyConfig
 *
 *   Configuration parameters are copying to drvObj,
 *   this function included with Fls_init
 *
 */
void Fls_copyConfig(Fls_DriverObjType *drvObj, const Fls_ConfigType *cfgPtr)
{
    uint8 sectorcfg_index = 0;
    if (drvObj != NULL_PTR)
    {
        if (cfgPtr != NULL_PTR)
        {
            drvObj->Fls_JobEndNotification   = cfgPtr->Fls_JobEndNotification;
            drvObj->Fls_JobErrorNotification = cfgPtr->Fls_JobErrorNotification;
            drvObj->maxReadNormalMode        = cfgPtr->maxReadNormalMode;
            drvObj->maxWriteNormalMode       = cfgPtr->maxWriteNormalMode;
            while (sectorcfg_index < FLS_NUMBER_OF_SECTOR_CFG)
            {
                drvObj->sectorList[sectorcfg_index] = cfgPtr->sectorList[sectorcfg_index];
                sectorcfg_index++;
            }
            drvObj->flsBaudRateDiv = cfgPtr->flsBaudRateDiv;
            drvObj->Fls_Mode       = cfgPtr->Fls_Mode;
        }
    }
    return;
}
/**
 *  \Function Name: Fls_resetDrvObj
 *
 *   All Driver parameter's reseting during initialize time.
 *
 */
void Fls_resetDrvObj(Fls_DriverObjType *drvObj)
{
    if (drvObj != NULL_PTR)
    {
        drvObj->Fls_JobEndNotification   = NULL;
        drvObj->Fls_JobErrorNotification = NULL;
        drvObj->maxReadNormalMode        = NULL;
        drvObj->maxWriteNormalMode       = NULL;
        drvObj->status                   = MEMIF_UNINIT;
        drvObj->jobResultType            = MEMIF_JOB_OK;
        drvObj->jobType                  = FLS_JOB_NONE;
        drvObj->flashAddr                = NULL;
        drvObj->ramAddr                  = NULL;
        drvObj->length                   = NULL;
        drvObj->mode                     = MEMIF_MODE_SLOW;
        drvObj->jobChunkSize             = NULL;
        drvObj->spiHandle                = NULL;
        drvObj->transferred              = NULL;
        drvObj->flsBaudRateDiv           = NULL;
        drvObj->flsDmaStage              = FLS_S_READ_DMA_INIT_STAGE;
        drvObj->flsEdmaReadEnabled       = FALSE;
        drvObj->flsDmaConfigError        = Fls_check_Memmap_Enabled_DMA();
        drvObj->flsDmaLength             = 0U;
        drvObj->flsDmaDstBuf             = (uint8 *)NULL_PTR;
    }
    return;
}

/**
 *  \Function Name: Fls_norAsyncSectorErase
 *
 *   Function to perform sector erase in the flash
 *
 */
Std_ReturnType Fls_norAsyncSectorErase(uint32 actualChunkSize)
{
    Std_ReturnType retVal = E_OK;

    if (actualChunkSize == 0U)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        retVal = Fls_norAsyncSectorErase_sub();
    }
    return retVal;
}

Std_ReturnType Fls_norAsyncSectorErase_sub(void)
{
    Std_ReturnType        retVal    = E_OK;
    Fls_InternalStateType retstatus = FLS_INTERNAL_JOB_WAIT;
    uint8                 cmd       = fls_config_sfdp->eraseCfg.cmdSectorErase3B;
    uint32                cmdAddr   = Fls_DrvObj.flashAddr;
    uint8                 cmdWren   = fls_config_sfdp->cmdWren;
    switch (FlsEraseStage)
    {
        case FLS_S_INVALID_ADDRESS:
        {
            if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmdWren, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0U) == E_OK)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DELAY_1_STAGE;
            }
            else
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            break;
        }

        case FLS_S_DELAY_1_STAGE:
        {
            retstatus = Nor_QspiAsyncWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->wrrwriteTimeout);
            retVal    = Fls_norQspiAsyncWaitReadysector(retstatus);
            break;
        }

        case FLS_S_SECTOR_CMD_STAGE:
        {
            if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmd, cmdAddr, NULL, 0) == E_OK)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DELAY_2_STAGE;
            }
            else
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            break;
        }

        case FLS_S_DELAY_2_STAGE:
        {
            retstatus = Nor_QspiAsyncWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->wrrwriteTimeout);
            if (retstatus == FLS_INTERNAL_JOB_DONE)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            else if (retstatus == FLS_INTERNAL_JOB_FAIL)
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            else
            {
                /* No Actions required. */
            }
            break;
        }

        default:
            break;
    }
    return retVal;
}

static Std_ReturnType Fls_norQspiAsyncWaitReadysector(Fls_InternalStateType retstatus)
{
    Std_ReturnType retVal = E_OK;
    if (retstatus == FLS_INTERNAL_JOB_DONE)
    {
        retVal        = E_OK;
        FlsEraseStage = FLS_S_SECTOR_CMD_STAGE;
    }
    else if (retstatus == FLS_INTERNAL_JOB_FAIL)
    {
        retVal        = E_NOT_OK;
        FlsEraseStage = FLS_S_DEFAULT;
    }
    else
    {
        /* No Actions required. */
    }
    return retVal;
}

/**
 *  \Function Name: Fls_norAsyncChipErase
 *
 *   Function to perform complete flash erase on the flash chip
 *
 */
Std_ReturnType Fls_norAsyncChipErase(void)
{
    Fls_InternalStateType retstatus = FLS_INTERNAL_JOB_WAIT;
    Std_ReturnType        retVal    = E_OK;
    uint8                 cmd       = fls_config_sfdp->cmdChipErase;
    uint8                 cmdWren   = fls_config_sfdp->cmdWren;

    switch (FlsEraseStage)
    {
        case FLS_S_INVALID_ADDRESS:
        {
            if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmdWren, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0U) == E_OK)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DELAY_1_STAGE;
            }
            else
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            break;
        }

        case FLS_S_DELAY_1_STAGE:
        {
            retstatus = Nor_QspiAsyncWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->wrrwriteTimeout);
            retVal    = Fls_norQspiAsyncWaitReadyChip(retstatus);
            break;
        }

        case FLS_S_CHIP_CMD_STAGE:
        {
            if (Nor_QspiCmdWrite(Fls_DrvObj.spiHandle, cmd, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0) == E_OK)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DELAY_2_STAGE;
            }
            else
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            break;
        }

        case FLS_S_DELAY_2_STAGE:
        {
            retstatus = Nor_QspiAsyncWaitReady(Fls_DrvObj.spiHandle, fls_config_sfdp->chipEraseTimeout);
            if (retstatus == FLS_INTERNAL_JOB_DONE)
            {
                retVal        = E_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            else if (retstatus == FLS_INTERNAL_JOB_FAIL)
            {
                retVal        = E_NOT_OK;
                FlsEraseStage = FLS_S_DEFAULT;
            }
            else
            {
                /* No Actions required. */
            }
            break;
        }

        default:
            break;
    }

    return retVal;
}

static Std_ReturnType Fls_norQspiAsyncWaitReadyChip(Fls_InternalStateType retstatus)
{
    Std_ReturnType retVal = E_OK;
    if (retstatus == FLS_INTERNAL_JOB_DONE)
    {
        retVal        = E_OK;
        FlsEraseStage = FLS_S_CHIP_CMD_STAGE;
    }
    else if (retstatus == FLS_INTERNAL_JOB_FAIL)
    {
        retVal        = E_NOT_OK;
        FlsEraseStage = FLS_S_DEFAULT;
    }
    else
    {
        /* No Actions required. */
    }
    return retVal;
}

Std_ReturnType Nor_QspiSetQeBit(QSPI_Handle handle, uint8 qeType)
{
    Std_ReturnType status = E_OK;

    if (E_OK == status)
    {
        if (qeType > (uint8)7U)
        {
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_PARAM_CONFIG);
            status = E_NOT_OK;
        }
        else
        {
            status = Nor_QspiSetQeBit_sub(handle, qeType);
        }
        if (status == E_OK)
        {
            status = Nor_QspiWaitReady(handle, fls_config_sfdp->flashWriteTimeout);
        }
    }
    return status;
}

static Std_ReturnType Nor_cmdwr_Enable(QSPI_Handle handle)
{
    Std_ReturnType status = E_OK;
    status                = Nor_QspiCmdWrite(handle, fls_config_sfdp->cmdWren, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0U);
    if (status == E_OK)
    {
        status = Nor_QspiWriteEnableLatched(Fls_DrvObj.spiHandle, fls_config_sfdp->wrrwriteTimeout);
    }
    if (status == E_OK)
    {
        status = Nor_QspiWaitReady(handle, fls_config_sfdp->wrrwriteTimeout);
    }
    return status;
}

Std_ReturnType Nor_QspiSetQeBit_sub(QSPI_Handle handle, uint8 qeType)
{
    Std_ReturnType status = E_OK;
    uint8          sr1 = 0, sr2 = 0, bitPos = 0;
    switch (qeType)
    {
        case 0:
            /* No QE bit, detects 1-1-4 based on instruction */
            break;

        case 2:
            /* QE is bit 6 of SR1 */
            sr1    = 0;
            bitPos = (uint8)1U << (uint8)6U;
            status = Nor_QspiCmdRead(handle, fls_config_sfdp->cmdRdsr, FLS_QSPI_CMD_INVALID_ADDR, &sr1, 1U);

            if ((sr1 & bitPos) != (uint8)0U)
            {
                /* QE is already set */
            }
            else
            {
                status  = Nor_cmdwr_Enable(handle);
                sr1    |= bitPos;
                status += Nor_QspiCmdWrite(handle, 0x01, FLS_QSPI_CMD_INVALID_ADDR, &sr1, 1U);
            }
            break;
        case 3:
            /* QE is bit 7 of SR2 */
            sr2    = 0;
            bitPos = (uint8)1 << (uint8)7;
            status = Nor_QspiCmdRead(handle, 0x3F, FLS_QSPI_CMD_INVALID_ADDR, (uint8 *)&sr2, 1U);

            if ((sr2 & bitPos) != (uint8)0U)
            {
                /* QE is already set */
            }
            else
            {
                status  = Nor_cmdwr_Enable(handle);
                sr2    |= bitPos;
                status += Nor_QspiCmdWrite(handle, 0x3E, FLS_QSPI_CMD_INVALID_ADDR, &sr2, 1U);
            }
            break;
        case 1:
            /* QE is bit 1 of SR2 */
        case 4:
            /* QE is bit 1 of SR2 */
        case 5:
            /* QE is bit 1 of SR2 */
            bitPos  = (uint8)1 << (uint8)1;
            status  = Nor_QspiCmdRead(handle, fls_config_sfdp->cmdRdsr, FLS_QSPI_CMD_INVALID_ADDR, &sr1, 1U);
            status += Nor_QspiCmdRead(handle, fls_config_sfdp->cmdRdsr2, FLS_QSPI_CMD_INVALID_ADDR, &sr2, 1U);

            if ((sr2 & bitPos) != (uint8)0U)
            {
                /* QE bit already set */
            }
            else
            {
                status       = Nor_cmdwr_Enable(handle);
                sr2         |= bitPos;
                uint8 sr[2]  = {sr2, sr1};

                status += Nor_QspiCmdWrite(handle, 0x01, FLS_QSPI_CMD_INVALID_ADDR, sr, 2U);
            }
            break;
        case 6:
            /* QE is bit 1 of SR2, using different command */
            bitPos = (uint8)1 << (uint8)1;
            status = Nor_QspiCmdRead(handle, fls_config_sfdp->cmdRdsr2, FLS_QSPI_CMD_INVALID_ADDR, &sr2, 1U);

            if ((sr2 & bitPos) != (uint8)0U)
            {
                /* QE bit already set */
            }
            else
            {
                status  = Nor_cmdwr_Enable(handle);
                sr2    |= bitPos;
                status += Nor_QspiCmdWrite(handle, 0x31, FLS_QSPI_CMD_INVALID_ADDR, &sr2, 1U);
            }
            break;
        default:
            break;
    }
    return status;
}

#if (STD_ON == FLS_REGISTER_READBACK_API)
void Fls_Qspi_RegisterReadback(P2VAR(Fls_RegisterReadbackType, AUTOMATIC, FLS_APPL_DATA) RegRbPtr)
{
    (void)memset(RegRbPtr, 0, sizeof(Fls_RegisterReadbackType));
    RegRbPtr->qspireg1 = HW_RD_REG32((FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ) + FLS_QSPI0_PID_REG);
}
#endif

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
