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
 *  \file     Fls_Brd_Nor_Ospi.c
 *
 *  This file contains FLS MCAL driver internal functions for Board Nor OSPI
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include "string.h"
#include "Fls_Cbk.h"
#include "hw_types.h"
#include "Fls_Ospi.h"
#include "Fls_Nor_config.h"
#include "Fls_Brd_Nor.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define FLASH_OSPI_JEDEC_ID_SIZE_MAX (8U)
#define FLS_BLANKCHECK_SIZE_MAX      (4096U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define FLS_START_SEC_VAR_NO_INIT_8
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/* Compare and BlankCheck Arrays to store data to compare */
VAR(uint8, FLS_VAR_NO_INIT) Fls_BlankCheckRxDataBuf[FLS_BLANKCHECK_SIZE_MAX];
VAR(uint8, FLS_VAR_NO_INIT) Fls_CompareRxDataBuf[FLS_BLANKCHECK_SIZE_MAX];

#define FLS_STOP_SEC_VAR_NO_INIT_8
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT_8
#include "Fls_MemMap.h"
volatile VAR(uint8, FLS_VAR_INIT) Fls_EraseStage = FLS_S_DEFAULT;
volatile VAR(uint8, FLS_VAR_INIT) Fls_WriteStage = FLS_S_INIT_STAGE;
#define FLS_STOP_SEC_VAR_INIT_8
#include "Fls_MemMap.h"
#include "Fls_Ospi_Edma.h"

static void Fls_JobNotification(Fls_JobType job, Std_ReturnType retVal, uint32 chunkSize);
static void Fls_JobDoneNotification1(Fls_JobType job, uint32 chunkSize);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define FLS_START_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/**
 *  \Function Name: Nor_OspiCmdWrite
 *
 *  This function perform write operation for OSPI protocol through the passing
 *  Command
 *
 */
Std_ReturnType Nor_OspiCmdWrite(OSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 numAddrBytes, uint8 *txBuf,
                                uint32 txLen)
{
    Std_ReturnType      retVal = (Std_ReturnType)E_OK;
    OSPI_WriteCmdParams wrParams;

    wrParams.cmd          = cmd;
    wrParams.cmdAddr      = cmdAddr;
    wrParams.numAddrBytes = numAddrBytes;
    wrParams.txDataBuf    = txBuf;
    wrParams.txDataLen    = txLen;

    retVal = Fls_Ospi_WriteCmd(handle, &wrParams);

    return retVal;
}
/**
 *  \Function Name: Nor_OspiCmdRead
 *
 *  This function perform read operation for OSPI protocol by passing command
 *  and will get corresponding data
 *
 *
 */
Std_ReturnType Nor_OspiCmdRead(OSPI_Handle handle, uint8 cmd, uint32 cmdAddr, uint8 numAddrBytes, uint8 dummyBits,
                               uint8 *rxBuf, uint32 rxLen)
{
    Std_ReturnType     retVal = (Std_ReturnType)E_OK;
    OSPI_ReadCmdParams rdParams;

    rdParams.cmd          = cmd;
    rdParams.cmdAddr      = cmdAddr;
    rdParams.numAddrBytes = numAddrBytes;
    rdParams.rxDataBuf    = rxBuf;
    rdParams.rxDataLen    = (uint16)rxLen;
    rdParams.dummyBits    = dummyBits;

    retVal = Fls_Ospi_ReadCmd(handle, &rdParams);

    return retVal;
}
/**
 *  \Function Name: Nor_OspiWaitDAC
 *
 *  This function executes delay for DAC mode
 *
 *
 */
Std_ReturnType Nor_OspiWaitDAC(OSPI_Handle handle, uint32 timeOut)
{
    Std_ReturnType retVal = E_NOT_OK;
    /* OSPI read command can potentially read a word of 4 bytes. So allocate that
     * big buffer even for a 1 byte read */
    uint8          rdstatus[4U] = {0};
    uint32         timeOutVal   = timeOut;

    rdstatus[0U] = 0xFFU;
    while (timeOutVal != 0U)
    {
        retVal = Nor_OspiCmdRead(handle, fls_config_sfdp->cmdRdsr, OSPI_CMD_INVALID_ADDR, 3, 8, &rdstatus[0U], 2);
        if ((retVal == E_OK) && ((rdstatus[0U] & 1U) == 0U))
        {
            retVal = E_OK;
            break;
        }
        timeOutVal--;
        volatile uint32 i = OSPI_CHECK_IDLE_DELAY;
        while (i > 0U)
        {
            i = i - 1U;
        }
    }
    return retVal;
}
/**
 *  \Function Name: Nor_OspiWaitReady
 *
 *  This function will perform delay opearation for OSPI read untill
 *  will get read status.
 *
 */
Std_ReturnType Nor_OspiWaitReady(OSPI_Handle handle, uint32 timeOut)
{
    OSPI_Object   *obj          = ((OSPI_Config *)handle)->object;
    Std_ReturnType retVal       = E_OK;
    uint32         localtimeOut = timeOut;

    uint8  readStatus[2]  = {0};
    uint8  numAddrBytes   = OSPI_CMD_INVALID_OPCODE;
    uint32 cmdAddr        = OSPI_CMD_INVALID_ADDR;
    uint8  cmd            = fls_config_sfdp->cmdRdsr;
    uint32 bitMask        = (uint32)fls_config_sfdp->srWip;
    uint8  numBytesToRead = 1;
    uint8  dummyBits      = 0;

    /* Do RDSR based on xspi WIP status */
    if ((fls_config_sfdp->xspiWipRdCmd != 0x00U) && (obj->currentprotocol == (uint32)FLS_OSPI_RX_8D_8D_8D))
    {
        /* Check XSPI WIP configuration */
        cmd            = fls_config_sfdp->xspiWipRdCmd;
        cmdAddr        = fls_config_sfdp->xspiWipReg;
        numAddrBytes   = fls_config_sfdp->addrnumBytes;
        bitMask        = fls_config_sfdp->xspiWipBit;
        numBytesToRead = 2; /* Can't read odd bytes in Octal DDR mode */
        dummyBits      = (uint8)fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyClksCmd;
    }

    while (localtimeOut > 0U)
    {
        retVal = Nor_OspiCmdRead(handle, cmd, cmdAddr, numAddrBytes, dummyBits, readStatus, numBytesToRead);
        if ((retVal == (Std_ReturnType)E_OK) && ((readStatus[0] & (uint8)bitMask) == 0U))
        {
            break;
        }
        localtimeOut--;
    }

    if ((readStatus[0] & (uint8)bitMask) == (uint8)0U)
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
 *  \Function Name: Nor_OspiReadId
 *
 *  This function check the device id and manufacture id for external flash.
 *
 */
Std_ReturnType Nor_OspiReadId(OSPI_Handle handle)
{
    OSPI_Config   *pHandle = (OSPI_Config *)handle;
    OSPI_Object   *obj     = pHandle->object;
    Std_ReturnType retVal  = (Std_ReturnType)E_OK;

    uint8  idCode[3]    = {0};
    uint32 cmdAddr      = OSPI_CMD_INVALID_ADDR;
    uint8  dummyBits    = 0;
    uint32 idNumBytes   = 3;
    uint8  numAddrBytes = 0;

    if (obj->currentprotocol == (uint32)FLS_OSPI_RX_8D_8D_8D)
    {
        dummyBits  = fls_config_sfdp->idCfg.dummy8;
        cmdAddr    = 0U;
        idNumBytes = 4; /* Can't read odd bytes in octal DDR */
    }

    retVal = Nor_OspiCmdRead(handle, fls_config_sfdp->idCfg.cmd, cmdAddr, numAddrBytes, dummyBits, idCode, idNumBytes);

    /* Verify ID with filled data */
    if (retVal == (Std_ReturnType)E_OK)
    {
        uint32 manfID, devID;

        manfID = (uint32)idCode[0];
        devID  = ((uint32)idCode[1] << 8) | ((uint32)idCode[2]);
        if ((manfID != fls_config_sfdp->manfId) || (devID != fls_config_sfdp->deviceId))
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return retVal;
}
/**
 *  \Function Name: Nor_OspiRead
 *
 *   This function read flash memory
 *
 */
Std_ReturnType Nor_OspiRead(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len)
{
    Std_ReturnType retVal = E_OK;
    if (handle == NULL_PTR)
    {
        retVal = E_NOT_OK;
    }
    /* Validate address input */
    if ((offset + len) > (fls_config_sfdp->flashSize))
    {
        retVal = E_NOT_OK;
    }
    if (retVal == E_OK)
    {
        OSPI_Transaction transaction;

        Fls_Ospi_TransactionInit(&transaction);
        transaction.addrOffset = offset;
        transaction.buf        = (void *)buf;
        transaction.count      = len;
        if (FLS_OSPI_DAC_ENABLE == STD_ON)
        {
            retVal = Fls_Ospi_readDirect(handle, &transaction);
        }
        else
        {
            retVal = Fls_Ospi_readIndirect(handle, &transaction);
        }
    }

    return retVal;
}
/**
 *  \Function Name: Nor_OspiWrite
 *
 *   This function Write to flash
 *
 */
Std_ReturnType Nor_OspiWrite(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len)
{
    Std_ReturnType retVal      = E_OK;
    uint32         localoffset = offset;
    if (handle == NULL_PTR)
    {
        retVal = E_NOT_OK;
    }
    /* Validate address input */
    if ((localoffset + len) > (fls_config_sfdp->flashSize))
    {
        retVal = E_NOT_OK;
    }
    /* Check if the offset is aligned to page */
    if (0U != (localoffset % fls_config_sfdp->pageSize))
    {
        retVal = E_NOT_OK;
    }
    boolean isFlsWriteInitStage = FALSE;
    if (Fls_WriteStage == FLS_S_INIT_STAGE)
    {
        isFlsWriteInitStage = TRUE;
    }
    if ((E_OK == retVal) && (isFlsWriteInitStage == TRUE))
    {
        uint32           pageSize, chunkLen, actual;
        OSPI_Transaction transaction;

        pageSize = fls_config_sfdp->pageSize;
        chunkLen = pageSize;

        for (actual = 0; actual < len; actual += chunkLen)
        {
            retVal = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

            if (retVal == E_OK)
            {
                retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
            }

            if (retVal == E_OK)
            {
                /* Send Page Program command */
                if ((len - actual) < (pageSize))
                {
                    chunkLen = (len - actual);
                }
                else
                {
                    chunkLen = pageSize;
                }

                Fls_Ospi_TransactionInit(&transaction);
                transaction.addrOffset = localoffset;
                transaction.buf        = (void *)(buf + actual);
                transaction.count      = chunkLen;
                if (FLS_OSPI_DAC_ENABLE == STD_ON)
                {
                    retVal = Fls_Ospi_writeDirect(handle, &transaction);
                }
                else
                {
                    retVal = Fls_Ospi_writeIndirect(handle, &transaction);
                }
            }

            if (retVal == E_OK)
            {
                retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashWriteTimeout);
            }

            if (retVal == E_OK)
            {
                localoffset += chunkLen;
            }
            else
            {
                break;
            }
        }
#if (FLS_USE_INTERRUPTS == STD_OFF)
        if (retVal == E_OK)
        {
            Fls_WriteStage = FLS_S_WRITE_DONE;
        }
#endif
    }

    return retVal;
}
/**
 *  \Function Name: Fls_norBlockErase
 *
 *   This function erase memory at a given blocknumber
 *
 */
Std_ReturnType Fls_norBlockErase(OSPI_Handle handle, uint32 offset)
{
    Std_ReturnType retVal = E_OK;
    uint32         blkNum;
    blkNum = offset / fls_config_sfdp->eraseCfg.blockSize;

    uint8  cmd     = OSPI_CMD_INVALID_OPCODE;
    uint32 cmdAddr = OSPI_CMD_INVALID_ADDR;

    cmdAddr = blkNum * fls_config_sfdp->eraseCfg.blockSize;
    if (fls_config_sfdp->addrnumBytes == (uint8)3U)
    {
        cmd = fls_config_sfdp->eraseCfg.cmdBlockErase3B;
    }
    else
    {
        cmd = fls_config_sfdp->eraseCfg.cmdBlockErase4B;
    }
    if (handle == NULL_PTR)
    {
        retVal = E_NOT_OK;
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiCmdWrite(handle, cmd, cmdAddr, fls_config_sfdp->addrnumBytes, NULL, 0);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
    }

    return retVal;
}
/**
 *  \Function Name: Fls_norSectorErase
 *
 *   Function to perform sector erase in the flash
 *
 */
Std_ReturnType Fls_norSectorErase(OSPI_Handle handle, uint32 offset)
{
    Std_ReturnType retVal = E_OK;
    uint32         sectorNum;
    sectorNum      = offset / fls_config_sfdp->eraseCfg.sectorSize;
    uint8  cmd     = OSPI_CMD_INVALID_OPCODE;
    uint32 cmdAddr = OSPI_CMD_INVALID_ADDR;
    cmdAddr        = sectorNum * fls_config_sfdp->eraseCfg.sectorSize;
    if (fls_config_sfdp->addrnumBytes == (uint8)3U)
    {
        cmd = fls_config_sfdp->eraseCfg.cmdSectorErase3B;
    }
    else
    {
        cmd = fls_config_sfdp->eraseCfg.cmdSectorErase4B;
    }
    if (handle == NULL_PTR)
    {
        retVal = E_NOT_OK;
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiCmdWrite(handle, cmd, cmdAddr, fls_config_sfdp->addrnumBytes, NULL, 0);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
    }

    return retVal;
}
/**
 *  \Function Name: Fls_norChipErase
 *
 *   Function to perform chip erase in the flash
 *
 */
Std_ReturnType Fls_norChipErase(OSPI_Handle handle, uint32 offset)
{
    (void)offset;
    Std_ReturnType retVal  = E_OK;
    uint8          cmd     = fls_config_sfdp->cmdChipErase;
    uint32         cmdAddr = OSPI_CMD_INVALID_ADDR;
    if (handle == NULL_PTR)
    {
        retVal = E_NOT_OK;
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiCmdWrite(handle, cmd, cmdAddr, fls_config_sfdp->addrnumBytes, NULL, 0);
    }
    if (E_OK == retVal)
    {
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->chipEraseTimeout);
    }

    return retVal;
}
/**
 *  \Function Name: Nor_OspiSetQeBit
 *
 *   Function to set Quad Enable bit
 *
 */
Std_ReturnType Nor_OspiSetQeBit(OSPI_Handle handle, uint8 qeType)
{
    Std_ReturnType retVal = E_OK;
    /* OSPI read command can potentially read a word of 4 bytes. So allocate that
     * big buffer even for a 1 byte read */
    uint8          sr1[4U] = {0}, sr2[4U] = {0}, bitPos = 0;
    uint32         bFlashRegWr = 0U;

    if (E_OK == retVal)
    {
        switch (qeType)
        {
            case 0:
                /* No QE bit, detects 1-1-4 based on instruction */
                break;

            case 1:
            case 4:
            case 5:
                /* QE is bit 1 of SR2 */
                bitPos  = (uint8)(1U << 1U);
                retVal  = Nor_OspiCmdRead(handle, fls_config_sfdp->cmdRdsr, OSPI_CMD_INVALID_ADDR,
                                          fls_config_sfdp->addrnumBytes, OSPI_CMD_INVALID_DUMMY, &sr1[0U], 1);
                retVal += Nor_OspiCmdRead(handle, fls_config_sfdp->cmdRdsr2, OSPI_CMD_INVALID_ADDR,
                                          fls_config_sfdp->addrnumBytes, OSPI_CMD_INVALID_DUMMY, &sr2[0U], 1);

                if ((sr2[0U] & bitPos) != (uint8)0U)
                {
                    /* QE bit already set */
                }
                else
                {
                    /* OSPI read command can potentially read a word of 4 bytes. So allocate that
                     * big buffer even for a 1 byte read */
                    uint16 sr[4U]  = {0};
                    sr2[0U]       |= bitPos;
                    sr[0U]         = (uint16)(((uint16)sr2[0U] << 8) | (uint16)sr1[0U]);

                    retVal = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
                    if (retVal == E_OK)
                    {
                        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
                    }

                    retVal      += Nor_OspiCmdWrite(handle, 0x01, OSPI_CMD_INVALID_ADDR, fls_config_sfdp->addrnumBytes,
                                                    (uint8 *)&sr[0U], 2);
                    bFlashRegWr  = 1U;
                }
                break;
            case 2:
                /* QE is bit 6 of SR1 */
                sr1[0U] = 0;
                bitPos  = (uint8)(1U << 6U);
                retVal  = Nor_OspiCmdRead(handle, fls_config_sfdp->cmdRdsr, OSPI_CMD_INVALID_ADDR,
                                          fls_config_sfdp->addrnumBytes, OSPI_CMD_INVALID_DUMMY, &sr1[0U], 1);

                if ((sr1[0U] & bitPos) != (uint8)0U)
                {
                    /* QE is already set */
                }
                else
                {
                    sr1[0U] |= bitPos;
                    retVal   = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
                    if (retVal == E_OK)
                    {
                        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
                    }
                    retVal      += Nor_OspiCmdWrite(handle, 0x01, OSPI_CMD_INVALID_ADDR, fls_config_sfdp->addrnumBytes,
                                                    &sr1[0U], 1);
                    bFlashRegWr  = 1U;
                }
                break;
            case 3:
                /* QE is bit 7 of SR2 */
                sr2[0U] = 0;
                bitPos  = (uint8)(1U << 7U);
                retVal  = Nor_OspiCmdRead(handle, 0x3F, OSPI_CMD_INVALID_ADDR, fls_config_sfdp->addrnumBytes,
                                          OSPI_CMD_INVALID_DUMMY, &sr2[0U], 1);

                if ((sr2[0U] & bitPos) != (uint8)0U)
                {
                    /* QE is already set */
                }
                else
                {
                    sr2[0U] |= bitPos;
                    retVal   = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
                    if (retVal == E_OK)
                    {
                        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
                    }
                    retVal      += Nor_OspiCmdWrite(handle, 0x3E, OSPI_CMD_INVALID_ADDR, fls_config_sfdp->addrnumBytes,
                                                    &sr2[0U], 1);
                    bFlashRegWr  = 1U;
                }
                break;
            case 6:
                /* QE is bit 1 of SR2, using different command */
                bitPos = (uint8)(1U << 1U);
                retVal = Nor_OspiCmdRead(handle, fls_config_sfdp->cmdRdsr2, OSPI_CMD_INVALID_ADDR,
                                         fls_config_sfdp->addrnumBytes, OSPI_CMD_INVALID_DUMMY, &sr2[0U], 1);

                if ((sr2[0U] & bitPos) != (uint8)0U)
                {
                    /* QE bit already set */
                }
                else
                {
                    sr2[0U] |= bitPos;
                    retVal   = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
                    if (retVal == E_OK)
                    {
                        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
                    }
                    retVal      += Nor_OspiCmdWrite(handle, 0x31, OSPI_CMD_INVALID_ADDR, fls_config_sfdp->addrnumBytes,
                                                    &sr2[0U], 1);
                    bFlashRegWr  = 1U;
                }
                break;
            default:
                break;
        }
        if ((retVal == E_OK) && (1U == bFlashRegWr))
        {
            retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        }
    }
    return retVal;
}
/**
 *  \Function Name: Nor_OspiSetOeBit
 *
 *   Function to set Octal Enable bit
 *
 */
Std_ReturnType Nor_OspiSetOeBit(OSPI_Handle handle, uint8 oeType)
{
    Std_ReturnType retVal = E_OK;
    /* OSPI read command can potentially read a word of 4 bytes. So allocate that
     * big buffer even for a 1 byte read */
    uint8          sr2[4U] = {0}, bitPos = 0;

    /* oeType 0 means no config, and all other values other 1 are reserved for now */
    switch (oeType)
    {
        case 0:
            /* No octal enable bit */
            break;
        case 1:
            /* Octal enable is the bit 3 of SR2 */
            bitPos = (uint8)(1U << 3U);
            retVal = Nor_OspiCmdRead(handle, 0x65, OSPI_CMD_INVALID_ADDR, 2, 1, &sr2[0U], 1);

            if ((sr2[0U] & bitPos) != (uint8)0U)
            {
                /* QE is already set */
            }
            else
            {
                sr2[0U] |= bitPos;
                retVal   = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
                if (retVal == E_OK)
                {
                    retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
                }
                retVal +=
                    Nor_OspiCmdWrite(handle, 0x3E, OSPI_CMD_INVALID_ADDR, fls_config_sfdp->addrnumBytes, &sr2[0U], 1);
            }
            break;
        default:
            break;
    }
    return retVal;
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
            retVal = Nor_OspiRead(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr, Fls_DrvObj.ramAddr, chunkSize);
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
        Fls_ErrorNotification(job, retVal);
    }
}

static void Fls_JobDoneNotification1(Fls_JobType job, uint32 chunkSize)
{
    switch (job)
    {
        case FLS_JOB_WRITE:
            if (FLS_S_WRITE_DONE == Fls_WriteStage)
            {
                Fls_JobDoneNotification(chunkSize, job);
            }
            break;
        case FLS_JOB_ERASE:
            if (FLS_S_DEFAULT == Fls_EraseStage)
            {
                Fls_JobDoneNotification(chunkSize, job);
            }
            break;
        case FLS_JOB_COMPARE:
            Fls_JobDoneNotification(chunkSize, job);
            break;
        case FLS_JOB_READ:
#if (FLS_DMA_ENABLE == STD_ON)
            if ((Fls_DrvObj.flsDmaStage == FLS_S_READ_DMA_DONE) || (Fls_DrvObj.flsEdmaReadEnabled == FALSE))
            {
                Fls_JobDoneNotification(chunkSize, job);
            }
#else
            Fls_JobDoneNotification(chunkSize, job);
#endif

            break;
        case FLS_JOB_BLANKCHECK:
            Fls_JobDoneNotification(chunkSize, job);
            break;
        default:
            break;
    }
}

/**
 *  \Function Name: processJobs
 *
 *  This function invoke
 * Fls_norCompare,Fls_norBlockErase,Fls_norSectorErase,Fls_norChipErase,Nor_OspiRead,Fls_norWrite
 *  and Fls_norBlankCheck function. it will perform any one function based on jobtype
 *
 *
 */
void processJobs(Fls_JobType job)
{
    uint32         chunkSize = 0;
    Std_ReturnType retVal    = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
    Fls_AddressType prevFlashaddr           = 0;
    uint32          norblankmaxchunkSize    = FLS_BLANKCHECK_SIZE_MAX;
    uint32          postBlankCheckFlashaddr = 0;
#endif
    Fls_DrvObj.flsEdmaReadEnabled = FALSE;
    /*Get the MIN of two*/
    if (Fls_DrvObj.length < Fls_DrvObj.jobChunkSize)
    {
        chunkSize = Fls_DrvObj.length;
    }
    else
    {
        chunkSize = Fls_DrvObj.jobChunkSize;
    }

    SchM_Enter_Fls_FLS_EXCLUSIVE_AREA_0();

    switch (job)
    {
        case FLS_JOB_COMPARE:
            if (FLS_USE_INTERRUPTS == STD_ON)
            {
                Fls_OspiIntEnable();
            }
            retVal = Fls_norCompare(chunkSize);
            break;
        case FLS_JOB_ERASE:
#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
            Fls_DrvObj.prevFlashaddr           = Fls_DrvObj.flashAddr;
            prevFlashaddr                      = Fls_DrvObj.prevFlashaddr;
            Fls_DrvObj.postBlankCheckFlashaddr = prevFlashaddr + chunkSize;
            postBlankCheckFlashaddr            = Fls_DrvObj.postBlankCheckFlashaddr;
#endif

            if (Fls_EraseStage == FLS_S_DEFAULT)
            {
#if (STD_OFF == FLS_USE_INTERRUPTS)
                Fls_EraseStage = FLS_S_DEFAULT;
#endif
            }

            if (chunkSize == 0U)
            {
                retVal = E_NOT_OK;
            }
            else
            {
                if (Fls_DrvObj.typeoferase == FLS_SECTOR_ERASE)
                {
                    retVal = Fls_norSectorErase(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr);
                }
                else if (Fls_DrvObj.typeoferase == FLS_BLOCK_ERASE)
                {
                    retVal = Fls_norBlockErase(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr);
                }
                else
                {
                    if (Fls_DrvObj.typeoferase == FLS_CHIP_ERASE)
                    {
                        retVal = Fls_norChipErase(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr);
                    }
                }
            }

#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
            if (Fls_EraseStage == FLS_S_DEFAULT)
            {
                if (retVal == E_OK)
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
            }
#endif
            break;
        case FLS_JOB_READ:
            if (FLS_USE_INTERRUPTS == STD_ON)
            {
                Fls_OspiIntEnable();
            }
#if (FLS_DMA_ENABLE == STD_ON)
            retVal    = Fls_norDmaRead();
            chunkSize = Fls_DrvObj.length;
#else
            retVal = Nor_OspiRead(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr, Fls_DrvObj.ramAddr, chunkSize);
#endif
            break;
        case FLS_JOB_WRITE:
            if (Fls_WriteStage == FLS_S_WRITE_DONE)
            {
#if (STD_ON == FLS_ERASE_VERIFICATION_ENABLED)
                retVal = Fls_norBlankCheck(chunkSize);
                if (retVal != E_OK)
                {
                    break;
                }
#endif
            }
            if (FLS_USE_INTERRUPTS == STD_ON)
            {
                Fls_OspiIntEnable();
            }
            retVal = Nor_OspiWrite(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr, Fls_DrvObj.ramAddr, chunkSize);
#if (STD_ON == FLS_WRITE_VERIFICATION_ENABLED)
            if (Fls_WriteStage == FLS_S_WRITE_DONE)
            {
                if (retVal == E_OK)
                {
                    retVal = Fls_norCompare(chunkSize);
                }
                else
                {
                    /* Do Nothing */
                }
            }
#endif
            break;
        case FLS_JOB_BLANKCHECK:
            if (FLS_USE_INTERRUPTS == STD_ON)
            {
                Fls_OspiIntEnable();
            }
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
/**
 *  \Function Name: Fls_JobDoneNotification
 *
 *  This function provides the job done notfication
 *
 */
void Fls_JobDoneNotification(uint32 chunkSize, Fls_JobType job)
{
    boolean isNotify = FALSE;
#if (STD_OFF == FLS_USE_INTERRUPTS)
    boolean isFlsWriteStageDone = FALSE;
    boolean isFlsEraseStage     = FALSE;

    if (Fls_WriteStage == FLS_S_WRITE_DONE)
    {
        isFlsWriteStageDone = TRUE;
    }
    if (Fls_EraseStage == FLS_S_DEFAULT)
    {
        isFlsEraseStage = TRUE;
    }
    if ((job == FLS_JOB_WRITE) && (isFlsWriteStageDone == TRUE))
    {
        isNotify = TRUE;
    }
    if ((job == FLS_JOB_ERASE) && (isFlsEraseStage == TRUE))
    {
        isNotify = TRUE;
    }
    if (job == FLS_JOB_COMPARE)
    {
        isNotify = TRUE;
    }
    if (job == FLS_JOB_READ)
    {
        isNotify = TRUE;
    }
    if (job == FLS_JOB_BLANKCHECK)
    {
        isNotify = TRUE;
    }
#endif
    if (isNotify == TRUE)
    {
        {
            Fls_DrvObj.ramAddr = &Fls_DrvObj.ramAddr[chunkSize];
            if ((job != FLS_JOB_ERASE) || ((job == FLS_JOB_ERASE) && (STD_OFF == FLS_ERASE_VERIFICATION_ENABLED)))
            {
                Fls_DrvObj.flashAddr += chunkSize;
            }
            Fls_DrvObj.flsDmaStage  = FLS_S_READ_DMA_INIT_STAGE;
            Fls_DrvObj.length      -= chunkSize;
            Fls_DrvObj.transferred += chunkSize;
            Fls_WriteStage          = FLS_S_INIT_STAGE;

            if ((Fls_LengthType)0U == Fls_DrvObj.length)
            {
                Fls_DrvObj.jobResultType = MEMIF_JOB_OK;
                Fls_DrvObj.status        = MEMIF_IDLE;
                Fls_DrvObj.jobType       = FLS_JOB_NONE;
                Fls_DrvObj.transferred   = 0U;
            }

            if (((Fls_LengthType)0U == Fls_DrvObj.length) && (Fls_DrvObj.Fls_JobEndNotification != NULL_PTR))
            {
                Fls_DrvObj.Fls_JobEndNotification();
            }
        }
    }
    return;
}
/**
 *  \Function Name: Fls_ErrorNotification
 *
 *  This function provides the error notfication
 *
 */
void Fls_ErrorNotification(Fls_JobType job, uint8 retVal)
{
    if ((E_BLANKCHECK_MISMATCH == retVal) || (E_COMPARE_MISMATCH == retVal))
    {
        Fls_DrvObj.status      = MEMIF_IDLE;
        Fls_DrvObj.jobType     = FLS_JOB_NONE;
        Fls_DrvObj.transferred = 0;
        if (FLS_JOB_BLANKCHECK == job)
        {
            Fls_DrvObj.jobResultType = MEMIF_BLOCK_INCONSISTENT;
#if (STD_OFF == FLS_USE_INTERRUPTS)
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION,
                                         FLS_E_VERIFY_ERASE_FAILED);
#else
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK,
                                         FLS_E_VERIFY_ERASE_FAILED);
#endif
        }
        else if (FLS_JOB_ERASE == job)
        {
#if (STD_OFF == FLS_USE_INTERRUPTS)
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION,
                                         FLS_E_VERIFY_ERASE_FAILED);
#else
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK,
                                         FLS_E_VERIFY_ERASE_FAILED);
#endif
        }
        else /*if (FLS_JOB_COMPARE == job)*/
        {
            Fls_DrvObj.jobResultType = MEMIF_BLOCK_INCONSISTENT;
#if (STD_OFF == FLS_USE_INTERRUPTS)
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION,
                                         FLS_E_VERIFY_WRITE_FAILED);
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
        Fls_IntClearDisable();
#endif
    }
    else /*if retVal == (Std_ReturnType) E_NOT_OK*/
    {
        /*Hardware/driver internal error occured*/
        ReportFlsError(job);
        if (Fls_DrvObj.Fls_JobErrorNotification != NULL_PTR)
        {
            Fls_DrvObj.Fls_JobErrorNotification();
        }
#if (STD_ON == FLS_USE_INTERRUPTS)
        /* disable and clear the interrupts */
        Fls_IntClearDisable();
#endif
    }

    return;
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
 *  \Function Name: Fls_norBlankCheck
 *
 *  Fls_norBlankCheck shall verify, whether a given memory area has been
 *  erased
 *
 */
uint8 Fls_norBlankCheck(uint32 actualChunkSize)
{
    uint8 retVal = (uint8)E_OK;
#if (FLS_USE_INTERRUPTS == STD_ON)
    if (Fls_DrvObj.transferred == (Fls_LengthType)0U)
    {
        Fls_DrvObj.compareAddr = Fls_BlankCheckRxDataBuf;
    }
    retVal = Nor_OspiRead(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr, (void *)Fls_DrvObj.compareAddr, actualChunkSize);
#else
    uint32 addr         = Fls_DrvObj.flashAddr;
    uint32 len          = actualChunkSize;
    uint8 *readData_buf = Fls_BlankCheckRxDataBuf;
    uint8  max_len      = sizeof(Fls_BlankCheckRxDataBuf) / sizeof(Fls_BlankCheckRxDataBuf[0]);

    if ((Fls_DrvObj.spiHandle != NULL_PTR) && (len <= max_len))
    {
        retVal = Nor_OspiRead(Fls_DrvObj.spiHandle, addr, (uint8 *)readData_buf, len);
        if ((uint8)E_OK == retVal)
        {
            if (Fls_VerifyBlankCheck_priv((const uint8 *)readData_buf, len) == TRUE)
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
#endif
    return retVal;
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
        drvObj->Fls_JobEndNotification   = (Fls_JobEndNotifyType)NULL_PTR;
        drvObj->Fls_JobErrorNotification = (Fls_JobErrorNotifyType)NULL_PTR;
        drvObj->maxReadNormalMode        = (uint32)0U;
        drvObj->maxWriteNormalMode       = (uint32)0U;
        drvObj->status                   = MEMIF_UNINIT;
        drvObj->jobResultType            = MEMIF_JOB_OK;
        drvObj->jobType                  = FLS_JOB_NONE;
        drvObj->flashAddr                = (uint32)0U;
        drvObj->ramAddr                  = (uint8 *)NULL_PTR;
        drvObj->length                   = (Fls_LengthType)0U;
        drvObj->mode                     = MEMIF_MODE_SLOW;
        drvObj->jobChunkSize             = (uint32)0U;
        drvObj->spiHandle                = NULL_PTR;
        drvObj->transferred              = (Fls_LengthType)0U;
        drvObj->baudRateDiv              = (uint32)0U;
    }
    return;
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
    if ((drvObj != NULL_PTR) && (cfgPtr != NULL_PTR))
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
        drvObj->baudRateDiv   = cfgPtr->flsBaudRateDiv;
        drvObj->Fls_Mode      = cfgPtr->Fls_Mode;
        drvObj->chipSelect    = OSPI_CS0;
        drvObj->frmFmt        = OSPI_FF_POL0_PHA0;
        drvObj->decChipSelect = OSPI_DECODER_SELECT4;
    }
    return;
}
/**
 *  \Function Name: Fls_hwUnitInit
 *
 *  This function initialize Hardware
 *
 */
Std_ReturnType Fls_hwUnitInit(void)
{
    Std_ReturnType retVal = E_OK;
    OSPI_Handle    handle = NULL_PTR;

    handle = Fls_Ospi_Open();

    Fls_DrvObj.spiHandle = handle;

    if ((handle != NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        retVal = (Std_ReturnType)E_OK;
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
#if (FLS_DMA_ENABLE == STD_ON)
    if (retVal == E_OK)
    {
        retVal = Fls_Ospi_dmaChInit(&Fls_DrvObj);
    }
#endif
    return retVal;
}
/**
 *  \Function Name: Nor_OspiSet4ByteAddrMode
 *
 *  This function set 4 Byte addressing mode registers
 *
 */
Std_ReturnType Nor_OspiSet4ByteAddrMode(OSPI_Handle handle)
{
    Std_ReturnType retVal = E_OK;

    if ((fls_config_sfdp->fourByteAddrEnSeq & (uint8)(1U << 0U)) != (uint8)0U)
    {
        /* Issue instruction 0xB7 without WREN */
        retVal = Nor_OspiCmdWrite(handle, 0xB7, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
    }
    if ((fls_config_sfdp->fourByteAddrEnSeq & (uint8)(1U << 1U)) != (uint8)0U)
    {
        /* Issue instruction 0xB7 with WREN */
        retVal = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
        if (retVal == E_OK)
        {
            retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        }
        retVal += Nor_OspiCmdWrite(handle, 0xB7, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
        if (retVal == E_OK)
        {
            retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        }
    }
    if ((fls_config_sfdp->fourByteAddrEnSeq & (uint8)(1U << 2U)) != (uint8)0U)
    {
        /* Extended Register read with instr 0xC8, write with instr 0xC5 to set
         * the MSByte of addr. To be taken care during read and write.
         */
    }
    if ((fls_config_sfdp->fourByteAddrEnSeq & (uint8)(1U << 3U)) != (uint8)0U)
    {
        /* Volatile bank register used to define 4 byte mode. To be taken care
         * during read and write
         */
    }
    if ((fls_config_sfdp->fourByteAddrEnSeq & (uint8)(1U << 4U)) != (uint8)0U)
    {
        /* Dedicated 4 byte address instruction set, consider 4 bytes always ON */
    }
    return retVal;
}
/**
 *  \Function Name: Ospi_SetRegCfg
 *
 *  This function configures the read and write registers
 *
 */
Std_ReturnType Ospi_SetRegCfg(OSPI_Handle handle, const Flash_RegEnConfig *rCfg)
{
    Std_ReturnType retVal = E_OK;

    /* Check if parameter is configured with addressed registers */
    if ((rCfg->cmdRegRd != 0U) || (rCfg->cmdRegWr != 0U))
    {
        uint8 cfgReg = 0;
        if (rCfg->isAddrReg == TRUE)
        {
            retVal += Nor_OspiRegRead(handle, rCfg->cmdRegRd, rCfg->cfgReg, &cfgReg);
        }
        else
        {
            retVal += Nor_OspiRegRead(handle, rCfg->cmdRegRd, OSPI_CMD_INVALID_ADDR, &cfgReg);
        }
        if (E_OK == retVal)
        {
            /* Clear the config bits in the register  */
            cfgReg &= ~(uint8)(rCfg->mask);
            /* Bitwise OR the bit pattern for setting the dummyCycle selected */
            cfgReg |= (rCfg->cfgRegBitP << rCfg->shift);
            /* There is register config, address might not be needed */
            if (rCfg->isAddrReg == TRUE)
            {
                retVal += Nor_OspiRegWrite(handle, rCfg->cmdRegWr, rCfg->cfgReg, cfgReg);
            }
            else
            {
                retVal += Nor_OspiRegWrite(handle, rCfg->cmdRegWr, OSPI_CMD_INVALID_ADDR, cfgReg);
            }
        }
    }
    else
    {
        /* Nothing to be done */
    }

    return retVal;
}
/**
 *  \Function Name: Nor_OspiRegWrite
 *
 *  This function configures the read and write registers
 *
 */
Std_ReturnType Nor_OspiRegWrite(OSPI_Handle handle, uint8 cmd, uint32 addr, uint8 data)
{
    Std_ReturnType retVal = E_OK;
    /* OSPI read command can potentially read a word of 4 bytes. So allocate that
     * big buffer even for a 1 byte write */
    uint8          regData[4U] = {0};

    regData[0U] = data;
    retVal      = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    /* Wait a finite interval after WREN */
    if (retVal == E_OK)
    {
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
    }

    if (retVal == E_OK)
    {
        retVal = Nor_OspiCmdWrite(handle, cmd, addr, fls_config_sfdp->addrnumBytes, &regData[0U], 1);
    }
    return retVal;
}
/**
 *  \Function Name: Nor_OspiRegRead
 *
 *  This function configures the read and write registers
 *
 */
Std_ReturnType Nor_OspiRegRead(OSPI_Handle handle, uint8 cmd, uint32 addr, uint8 *data)
{
    OSPI_Config   *pHandle   = (OSPI_Config *)handle;
    OSPI_Object   *obj       = pHandle->object;
    Std_ReturnType retVal    = E_OK;
    uint8          reg[2]    = {0};
    uint8          numBytes  = 1;
    uint8          dummyBits = OSPI_CMD_INVALID_DUMMY;

    if (obj->currentprotocol == (uint32)FLS_OSPI_RX_8D_8D_8D)
    {
        numBytes  = 2; /* Octal DDR can't read odd number of bytes */
        dummyBits = (uint8)fls_config_sfdp->protos[FLS_OSPI_RX_8D_8D_8D].dummyClksCmd;
    }
    retVal = Nor_OspiCmdRead(handle, cmd, addr, fls_config_sfdp->addrnumBytes, dummyBits, reg, numBytes);

    *data = reg[0];

    return retVal;
}
/**
 *  \Function Name: Fls_VerifyBlankCheck_priv
 *
 *  This function included in Fls_norBlanCheck and verify data,if any mismatch
 *  return FALSE
 *
 */
boolean Fls_VerifyBlankCheck_priv(const uint8 *rxData, uint32 length)
{
    uint32       idx          = 0U;
    uint32       match        = TRUE;
    boolean      retVal       = FALSE;
    uint8        expData      = 0xFF;
    const uint8 *rxData_local = rxData;
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
 *  \Function Name: Fls_VerifyData_priv
 *
 *  This function included in Fls_norCompare and verify data,if any mismatch
 *  return FALSE
 *
 */
boolean Fls_VerifyData_priv(const uint8 *expData, const uint8 *rxData, uint32 length)
{
    uint32       idx           = 0U;
    uint32       match         = TRUE;
    boolean      retVal        = FALSE;
    const uint8 *expData_local = expData;
    const uint8 *rxData_local  = rxData;

    for (idx = (uint32)0; ((idx < length) && (match != FALSE)); idx++)
    {
        if (*expData_local != *rxData_local)
        {
            match = FALSE;
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
Std_ReturnType Fls_norCompare(uint32 actualChunkSize)
{
    Std_ReturnType retVal = E_OK;
#if (FLS_USE_INTERRUPTS == STD_ON)
    if (Fls_DrvObj.transferred == (Fls_LengthType)0U)
    {
        Fls_DrvObj.compareAddr = Fls_CompareRxDataBuf;
    }
    retVal = Nor_OspiRead(Fls_DrvObj.spiHandle, Fls_DrvObj.flashAddr, (void *)Fls_DrvObj.compareAddr, actualChunkSize);
#else
    uint32 addr         = Fls_DrvObj.flashAddr;
    uint32 len          = actualChunkSize;
    uint8 *readData_buf = Fls_CompareRxDataBuf;
    uint8 *expData_Buf  = Fls_DrvObj.ramAddr;
    uint8  max_len      = sizeof(Fls_CompareRxDataBuf) / sizeof(Fls_CompareRxDataBuf[0]);

    if ((Fls_DrvObj.spiHandle != NULL_PTR) && (len <= max_len))
    {
        retVal = Nor_OspiRead(Fls_DrvObj.spiHandle, addr, (uint8 *)readData_buf, len);
        if ((Std_ReturnType)E_OK == retVal)
        {
            if (Fls_VerifyData_priv(expData_Buf, (const uint8 *)readData_buf, len) == TRUE)
            {
                retVal = (Std_ReturnType)E_OK;
            }
            else
            {
                retVal = E_COMPARE_MISMATCH;
            }
        }
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK; /* Handle is NULL_PTR*/
    }
#endif
    return retVal;
}

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*******************************************************************************
 *  End of File: Fls_Brd_Nor_Ospi.c
 ******************************************************************************/
