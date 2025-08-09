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
 *  \file   Fls_OSPI.c
 *
 *  \brief  OSPI  specific driver APIs implementation.
 *
 *   This file contains the driver APIs for OSPI controller.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include "Fls_Ospi.h"
#include "Fls_Brd_Nor.h"
#include "hal_stdtypes.h"
#include <mcal_hw_soc_baseaddress.h>
#if (FLS_DMA_ENABLE == STD_ON)
#include "Fls_Ospi_Edma.h"
#endif

#define FLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/** \brief Driver object */
OSPI_Object Fls_OspiObjects[OSPI_NUM_INSTANCES];

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define FLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/* OSPI driver configuration */

OSPI_Config Fls_OspiConfig[1] = {{&Fls_OspiObjects[0]}};

#define FLS_STOP_SEC_VAR_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define FLS_START_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"
/**
 *  \Function Name: Fls_Ospi_TransactionInit
 *
 *   Function to initialize the OSPI_Transaction structure
 *
 */
void Fls_Ospi_TransactionInit(OSPI_Transaction *trans)
{
    trans->count           = 0U;
    trans->buf             = NULL;
    trans->addrOffset      = 0U;
    trans->transferTimeout = (uint32)-1;
    trans->status          = OSPI_TRANSFER_STARTED;
}
/**
 *  \Function Name: Fls_Ospi_ExecCmd
 *
 *   This function executes the read and write command operation
 *
 */
static uint32 Fls_Ospi_ExecCmd(void)
{
    uint32 retry    = OSPI_READ_WRITE_TIMEOUT;
    uint32 retVal   = 0U;
    uint32 idleFlag = 0U;

    while (idleFlag == 0U)
    {
        idleFlag = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_IDLE_FLD);
    }

    /* Start to execute flash read/write command */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_CMD_EXEC_FLD, 1);

    while (retry != 0U)
    {
        /* Check the command execution status
         * If the execution is complete, this bit field will be zero
         */
        uint32 execCompleteFlag = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG,
                                                OSPI_FLASH_CMD_CTRL_REG_CMD_EXEC_STATUS_FLD);

        if (execCompleteFlag == 0U)
        {
            break;
        }
        uint32 delay = OSPI_CHECK_IDLE_DELAY;
        while (delay != 0U)
        {
            delay--;
        };
        retry--;
    }

    if (retry == 0U)
    {
        retVal = -1;
    }

    idleFlag = 0U;
    while (idleFlag == 0U)
    {
        idleFlag = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_IDLE_FLD);
    }

    return (retVal);
}
/**
 *  \Function Name: Fls_Ospi_ReadCmd
 *
 *   Function to send specific commands and receive related data from flash
 *
 */
Std_ReturnType Fls_Ospi_ReadCmd(OSPI_Handle handle, OSPI_ReadCmdParams *rdParams)
{
    Std_ReturnType retVal  = E_OK;
    OSPI_Config   *pHandle = (OSPI_Config *)handle;
    OSPI_Object   *obj     = pHandle->object;
    uint8         *pBuf    = (uint8 *)rdParams->rxDataBuf;
    uint32         rxLen   = rdParams->rxDataLen;

    /* Clear flash command control register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, 0U);

    /* Set command opcode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_CMD_OPCODE_FLD,
                  rdParams->cmd);

    /* Enable read data in command control register */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_ENB_READ_DATA_FLD, TRUE);

    /* Set number of read data bytes */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_NUM_RD_DATA_BYTES_FLD,
                  rxLen - 1U);

    /* Set dummyCycles for the command */
    if (rdParams->dummyBits != OSPI_CMD_INVALID_DUMMY)
    {
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_NUM_DUMMY_CYCLES_FLD,
                      rdParams->dummyBits);
    }
    else
    {
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_NUM_DUMMY_CYCLES_FLD,
                      obj->cmdDummyCycles);
    }

    uint32 dualOpCode =
        HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_DUAL_BYTE_OPCODE_EN_FLD);

    if (dualOpCode == 1U)
    {
        uint8 cmdExt = OSPI_CMD_INVALID_OPCODE;
        /* Get the extended opcode type for read and Write */
        if (fls_config_sfdp->cmdExtType == OSPI_CMD_EXT_TYPE_REPEAT)
        {
            cmdExt = rdParams->cmd;
        }
        else
        {
            if (fls_config_sfdp->cmdExtType == OSPI_CMD_EXT_TYPE_INVERSE)
            {
                cmdExt = ~(rdParams->cmd);
            }
        }

        /* Set extended STIG opcode */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_OPCODE_EXT_LOWER_REG,
                      OSPI_OPCODE_EXT_LOWER_REG_EXT_STIG_OPCODE_FLD, cmdExt);
    }
    else
    {
        /* do nothing */
    }

    if ((rdParams->cmdAddr != OSPI_CMD_INVALID_ADDR) && (rdParams->numAddrBytes > 0U))
    {
        /* Enable Command address in command control register */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_ENB_COMD_ADDR_FLD,
                      TRUE);

        /* Set number of address bytes */
        HW_WR_FIELD32((uint32)FLS_OSPI_CTRL_BASE_ADDR + (uint32)OSPI_FLASH_CMD_CTRL_REG,
                      (uint32)OSPI_FLASH_CMD_CTRL_REG_NUM_ADDR_BYTES_FLD, (uint32)(rdParams->numAddrBytes - 1U));

        /* Update the flash cmd address register */
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_ADDR_REG, rdParams->cmdAddr);
    }

    if (Fls_Ospi_ExecCmd() == 0U)
    {
        uint32 regVal = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_RD_DATA_LOWER_REG);
        uint32 rdLen  = (rxLen > 4U) ? 4U : rxLen;
        (void)memcpy((void *)pBuf, (void *)(&regVal), rdLen);
        pBuf += rdLen;

        if (rxLen > 4U)
        {
            regVal = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_RD_DATA_UPPER_REG);
            rdLen  = rxLen - rdLen;
            (void)memcpy((void *)pBuf, (void *)(&regVal), rdLen);
        }
    }

    return retVal;
}

#if (FLS_DMA_ENABLE == STD_ON)
void Fls_Ospi_Dma_Read(OSPI_Handle handle, OSPI_Transaction *trans)
{
    uint32    dmaOffset;
    uint32    nonAlignedBytes;
    uint8    *pDmaDst = (uint8 *)NULL_PTR;
    uint8    *pDmaSrc = (uint8 *)NULL_PTR;
    uintptr_t temp_addr;
    uint32    dmaLen;

    /* Destination address */
    uint8 *pDst = (uint8 *)NULL_PTR;
    /* Source address */
    uint8 *pSrc = (uint8 *)NULL_PTR;
    /* Transaction length */
    uint32 count = 0;

    if (handle != NULL_PTR)
    {
        OSPI_Transaction *transaction = trans;

        /* Enable Direct Access Mode */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 1);
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0x04000000);

        temp_addr = (FLS_BASE_ADDRESS + (uintptr_t)transaction->addrOffset);
        pSrc      = (uint8 *)(temp_addr);
        pDst      = (uint8 *)transaction->buf;
        count     = transaction->count;

        if (Fls_DrvObj.flsEdmaReadEnabled == TRUE)
        {
            /* Check if the ospi memory address is 4 byte aligned. */
            dmaOffset       = (transaction->addrOffset + 0x3U) & (~0x3U);
            nonAlignedBytes = dmaOffset - transaction->addrOffset;
            pDmaDst         = (uint8 *)(pDst + nonAlignedBytes);
            pDmaSrc         = (uint8 *)(pSrc + nonAlignedBytes);
            dmaLen          = count - nonAlignedBytes;
            /* Do the normal memory to memory transfer of nonAligned bytes at the start. */
            while (nonAlignedBytes != (uint32)0U)
            {
                *pDst = *pSrc;
                pDst++;
                pSrc++;
                nonAlignedBytes--;
            }

            if (dmaLen != (uint32)0U)
            {
                /* calculate the nonAligned bytes at the end */
                nonAlignedBytes = dmaLen - ((dmaLen) & (~0x3U));

                /* Get the previous multiple of 4 of dmaLen as edma transfer can only be done with
                 * length in multiple of 4*/
                dmaLen = (dmaLen) & (~0x3U);
                /* Do the normal memory to memory transfer of nonAligned bytes at the end. */
                pDst = pDst + dmaLen;
                pSrc = pSrc + dmaLen;
                while (nonAlignedBytes != (uint32)0U)
                {
                    *pDst = *pSrc;
                    pDst++;
                    pSrc++;
                    nonAlignedBytes--;
                }
                if (dmaLen != (uint32)0U)
                {
                    Fls_DrvObj.flsDmaStage = FLS_S_READ_DMA_WAIT_STAGE;
                    FLS_edmaTransfer(pDmaDst, pDmaSrc, dmaLen, handle);
                }
                else
                {
                    // dma is not triggered for lengths lesser than 4 bytes
                    Fls_DrvObj.flsDmaStage = FLS_S_READ_DMA_DONE;
                }
            }
        }
        else
        {
            while ((count) != (uint32)0U)
            {
                *pDst = *pSrc;
                pDst++;
                pSrc++;
                count--;
            }
        }
    }
}
#endif

/**
 *  \Function Name: Fls_Ospi_readDirect
 *
 *   Function to read from flash in DAC mode
 *
 */
Std_ReturnType Fls_Ospi_readDirect(OSPI_Handle handle, OSPI_Transaction *trans)
{
#if (FLS_DMA_ENABLE == STD_ON)
    Fls_Ospi_Dma_Read(handle, trans); /*for DMA*/
    return E_OK;
#else

    (void)handle;
    Std_ReturnType retVal = E_OK;

    uint8 *pSrc;
    uint8 *pDst;
    uint32 addrOffset;
    uint32 i, size, remainSize;

    addrOffset = trans->addrOffset;
    pDst       = (uint8 *)trans->buf;

    /* Enable Direct Access Mode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 1);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0x04000000);

    pSrc = (uint8 *)(FLS_BASE_ADDRESS + addrOffset);

    remainSize = (uint32)trans->count & 3U;
    size       = (uint32)trans->count - remainSize;
    /* Transfer the data in 32-bit size */
    for (i = 0U; i < size; i += 4U)
    {
        HW_WR_REG32(pDst + i, HW_RD_REG32(pSrc + i));
    }
    /* Transfer the remaining data in 8-bit size */
    for (i = 0; i < remainSize; i++)
    {
        HW_WR_REG32(pDst + size + i, HW_RD_REG8(pSrc + size + i));
    }
    return retVal;

#endif
}
/**
 *  \Function Name: Fls_Ospi_readIndirect
 *
 *   Function to read from flash in INDAC mode
 *
 */
Std_ReturnType Fls_Ospi_readIndirect(OSPI_Handle handle, OSPI_Transaction *trans)
{
    OSPI_Config   *pHandle = (OSPI_Config *)handle;
    OSPI_Object   *obj     = pHandle->object;
    Std_ReturnType retVal  = E_OK;
    uint8         *pDst;
    uint32         addrOffset;
    uint32         remainingSize;
    uint32         readFlag  = 0U;
    uint32         sramLevel = 0, readBytes = 0;

    uint32 retry = OSPI_READ_WRITE_TIMEOUT;
    uint32 delay = OSPI_CHECK_IDLE_DELAY;

    addrOffset = trans->addrOffset;
    pDst       = (uint8 *)trans->buf;

    /* Disable DAC Mode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 0U);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0);

    /* Config the Indirect Read Transfer Start Address Register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_START_REG, addrOffset);

    /* Set the Indirect Write Transfer Start Address Register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_NUM_BYTES_REG, trans->count);

    /* Reset watermark register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_WATERMARK_REG, 0);

    /* Set the Indirect Write Transfer Watermark Register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_WATERMARK_REG, OSPI_SRAM_WARERMARK_RD_LVL);

    /* Start the indirect read transfer */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_CTRL_REG,
                  OSPI_INDIRECT_READ_XFER_CTRL_REG_START_FLD, 1);
    if (OSPI_TRANSFER_MODE_POLLING == obj->transferMode)
    {
        remainingSize = trans->count;

        while (remainingSize > 0U)
        {
            /* Read SRAM level*/
            while (retry != 0U)
            {
                sramLevel = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_SRAM_FILL_REG) &
                            OSPI_SRAM_FILL_REG_SRAM_FILL_INDAC_READ_FLD_MASK;
                if (sramLevel != 0U)
                {
                    break;
                }
                delay = OSPI_CHECK_IDLE_DELAY;
                while (delay != 0U)
                {
                    delay--;
                };
                retry--;
            }
            if (retry == 0U)
            {
                /* SRAM FIFO has no data, failure */
                readFlag      = 1U;
                retVal        = E_NOT_OK;
                trans->status = OSPI_TRANSFER_FAILED;
                break;
            }

            readBytes = sramLevel * OSPI_FIFO_WIDTH;
            readBytes = (readBytes > remainingSize) ? remainingSize : readBytes;

            /* Read data from FIFO */
            uint32  temp;
            uint32  remainingFIFO;
            uint32 *destPtr = (uint32 *)pDst;

            for (remainingFIFO = readBytes; remainingFIFO >= OSPI_FIFO_WIDTH; remainingFIFO -= OSPI_FIFO_WIDTH)
            {
                *destPtr = HW_RD_REG32((uintptr_t)FLS_BASE_ADDRESS);
                destPtr++;
            }

            if (remainingFIFO > 0U)
            {
                temp = HW_RD_REG32((uintptr_t)FLS_BASE_ADDRESS);
                (void)memcpy(destPtr, &temp, remainingFIFO);
            }
            pDst          += readBytes;
            remainingSize -= readBytes;
        }

        /* Wait for completion of INDAC Read */
        retry         = OSPI_READ_WRITE_TIMEOUT;
        uint32 regVal = 0U;

        while (retry != 0U)
        {
            regVal = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_CTRL_REG,
                                   OSPI_INDIRECT_READ_XFER_CTRL_REG_IND_OPS_DONE_STATUS_FLD);
            if (regVal == 1U)
            {
                break;
            }
            delay = OSPI_CHECK_IDLE_DELAY;
            while (delay != 0U)
            {
                delay--;
            };
            retry--;
        }

        if (retry != 0U)
        {
            /* Clear indirect completion status */
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_CTRL_REG,
                          OSPI_INDIRECT_READ_XFER_CTRL_REG_IND_OPS_DONE_STATUS_FLD, 1);
        }
        else
        {
            if (readFlag == 0U)
            {
                readFlag      = 1U;
                retVal        = E_NOT_OK;
                trans->status = OSPI_TRANSFER_FAILED;
            }
        }
    }

    return retVal;
}
/**
 *  \Function Name: Fls_Ospi_WriteCmd
 *
 *   Function to send specific commands and related data to flash
 *
 */
Std_ReturnType Fls_Ospi_WriteCmd(OSPI_Handle handle, OSPI_WriteCmdParams *wrParams)
{
    (void)handle;
    Std_ReturnType retVal = E_OK;
    uint8         *txBuf  = (uint8 *)wrParams->txDataBuf;
    uint32         txLen  = wrParams->txDataLen;

    /* Clear the flash command control register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, 0U);

    /* Set command opcode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_CMD_OPCODE_FLD,
                  wrParams->cmd);

    /* Set command address if needed */
    if (wrParams->cmdAddr != OSPI_CMD_INVALID_ADDR)
    {
        /* Enable Command address in command control register */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_ENB_COMD_ADDR_FLD,
                      TRUE);

        /* Set number of address bytes */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_NUM_ADDR_BYTES_FLD,
                      wrParams->numAddrBytes - (uint8)1U);

        /* Update the flash cmd address register */
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_ADDR_REG, wrParams->cmdAddr);
    }
    else
    {
        /* do nothing */
    }

    uint32 dualOpCode =
        HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_DUAL_BYTE_OPCODE_EN_FLD);

    if (dualOpCode == 1U)
    {
        uint8 cmdExt = OSPI_CMD_INVALID_OPCODE;
        /* Get the extended opcode type for read and Write */
        if (fls_config_sfdp->cmdExtType == OSPI_CMD_EXT_TYPE_REPEAT)
        {
            cmdExt = wrParams->cmd;
        }
        else
        {
            if (fls_config_sfdp->cmdExtType == OSPI_CMD_EXT_TYPE_INVERSE)
            {
                cmdExt = ~(wrParams->cmd);
            }
        }
        /* Set extended STIG opcode */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_OPCODE_EXT_LOWER_REG,
                      OSPI_OPCODE_EXT_LOWER_REG_EXT_STIG_OPCODE_FLD, cmdExt);
    }
    else
    {
        /* do nothing */
    }

    if (txLen != 0U)
    {
        uint32 wrLen  = 0;
        uint32 wrData = 0;

        /* Enable write data in command control register */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_ENB_WRITE_DATA_FLD,
                      TRUE);

        /* Set number of data bytes to write */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_NUM_WR_DATA_BYTES_FLD,
                      txLen - 1U);

        wrLen = txLen > 4U ? 4U : txLen;
        (void)memcpy((void *)&wrData, (void *)txBuf, wrLen);
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_WR_DATA_LOWER_REG, wrData);

        if (txLen > 4U)
        {
            txBuf += wrLen;
            wrLen  = txLen - wrLen;
            (void)memcpy((void *)&wrData, (void *)txBuf, wrLen);
            HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_WR_DATA_UPPER_REG, wrData);
        }
    }
    else
    {
        /* do nothing */
    }
    retVal = Fls_Ospi_ExecCmd();

    return retVal;
}
/**
 *  \Function Name: Fls_Ospi_writeDirect
 *
 *   Function to write to flash in DAC mode
 *
 */
Std_ReturnType Fls_Ospi_writeDirect(OSPI_Handle handle, OSPI_Transaction *trans)
{
    Std_ReturnType retVal = E_OK;
    uint8         *pSrc;
    uint8         *pDst;
    uint32         addrOffset, remainSize, size, i;
    uint32         wrWord;
    uint8          wrByte;

    addrOffset = trans->addrOffset;
    pSrc       = (uint8 *)trans->buf;

    /* Enable Direct Access Mode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 1);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0x04000000);

    pDst       = (uint8 *)(FLS_BASE_ADDRESS + addrOffset);
    remainSize = (uint32)trans->count & 3U;
    size       = (uint32)trans->count - remainSize;
    /* Transfer the data in 32-bit size */
    for (i = 0U; i < size; i += 4U)
    {
        wrWord = HW_RD_REG32(pSrc + i);
        HW_WR_REG32(pDst + i, wrWord);
        retVal = Nor_OspiWaitDAC(handle, fls_config_sfdp->wrrwriteTimeout);
    }
    if (retVal == E_OK)
    {
        /* Transfer the remaining data in 8-bit size */
        for (i = 0; i < remainSize; i++)
        {
            wrByte = HW_RD_REG8(pSrc + size + i);
            HW_WR_REG8(pDst + size + i, wrByte);
            retVal = Nor_OspiWaitDAC(handle, fls_config_sfdp->wrrwriteTimeout);
        }
    }
    return retVal;
}
/**
 *  \Function Name: Fls_Ospi_writeIndirect
 *
 *   Function to write to flash in INDAC mode
 *
 */
Std_ReturnType Fls_Ospi_writeIndirect(OSPI_Handle handle, OSPI_Transaction *trans)
{
    Std_ReturnType retVal = E_OK;
    uint8         *pSrc;
    uint32         remainingSize, sramLevel, wrBytes, wrFlag = 0;

    uint32       retry   = OSPI_REG_RETRY;
    OSPI_Config *pHandle = (OSPI_Config *)handle;
    OSPI_Object *obj     = pHandle->object;
    pSrc                 = (uint8 *)trans->buf;

    /* Disable DAC Mode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 0U);

    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0);

    /* Set write address in indirect mode */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_START_REG, trans->addrOffset);

    /* Set the Indirect Write Transfer Start Address Register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_REG, trans->count);

    /* Reset watermark register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_WATERMARK_REG, 0);

    /* Set the Indirect Write Transfer Watermark Register */
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_WATERMARK_REG, OSPI_SRAM_WATERMARK_WR_LVL);

    /* Start the indirect write transfer */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_CTRL_REG,
                  OSPI_INDIRECT_WRITE_XFER_CTRL_REG_START_FLD, 1);

    if (OSPI_TRANSFER_MODE_POLLING == obj->transferMode)
    {
        remainingSize = trans->count;
        while (remainingSize > 0U)
        {
            /* Write SRAM level*/
            while (retry != 0U)
            {
                sramLevel = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_SRAM_FILL_REG) >>
                            OSPI_SRAM_FILL_REG_SRAM_FILL_INDAC_WRITE_FLD_SHIFT;
                if (sramLevel <= OSPI_SRAM_WATERMARK_WR_LVL)
                {
                    break;
                }
                uint32 delay = OSPI_POLL_IDLE_DELAY;
                while (delay != 0U)
                {
                    delay--;
                };
                retry--;
            }

            if (retry == 0U)
            {
                wrFlag = 1U;
                retVal = E_NOT_OK;
                break;
            }

            wrBytes = (OSPI_SRAM_PARTITION_WR - sramLevel) * OSPI_FIFO_WIDTH;
            wrBytes = (wrBytes > remainingSize) ? remainingSize : wrBytes;

            /* Write data to FIFO */
            uint32  temp = 0;
            uint32  remainingFIFO;
            uint32 *srcPtr = (uint32 *)pSrc;

            for (remainingFIFO = wrBytes; remainingFIFO >= OSPI_FIFO_WIDTH; remainingFIFO -= OSPI_FIFO_WIDTH)
            {
                HW_WR_REG32((uintptr_t)FLS_BASE_ADDRESS, *srcPtr);
                srcPtr++;
            }
            if (remainingFIFO > 0U)
            {
                /* dangling bytes */
                (void)memcpy(&temp, srcPtr, remainingFIFO);
                HW_WR_REG32((uintptr_t)FLS_BASE_ADDRESS, temp);
            }
            pSrc          += wrBytes;
            remainingSize -= wrBytes;
        }

        /* Wait for completion of INDAC Write */
        retry         = OSPI_READ_WRITE_TIMEOUT;
        uint32 regVal = 0U;

        /* Check flash indirect write controller status */
        while (retry != 0U)
        {
            regVal = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_CTRL_REG,
                                   OSPI_INDIRECT_WRITE_XFER_CTRL_REG_IND_OPS_DONE_STATUS_FLD);
            if (regVal == (uint32)1U)
            {
                break;
            }
            uint32 delay = OSPI_CHECK_IDLE_DELAY;
            while (delay != 0U)
            {
                delay--;
            };
            retry--;
        }

        if (retry != 0U)
        {
            /* Clear indirect completion status */
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_CTRL_REG,
                          OSPI_INDIRECT_WRITE_XFER_CTRL_REG_IND_OPS_DONE_STATUS_FLD, 1);
        }
        else
        {
            if (wrFlag == 0U)
            {
                wrFlag        = 1U;
                trans->status = OSPI_TRANSFER_FAILED;
                /* Cancel the indirect write */
                HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_CTRL_REG,
                              OSPI_INDIRECT_WRITE_XFER_CTRL_REG_CANCEL_FLD, 1);
                retVal = E_NOT_OK;
            }
        }
    }
    return retVal;
}
/**
 *  \Function Name: Fls_Ospi_Open
 *
 *  Function to open a OSPI peripheral specified by the OSPI handle.
 *
 */
OSPI_Handle Fls_Ospi_Open(void)
{
    /*Fls_Ospi Hardware Initialisation*/
    OSPI_Object *obj;
    obj = Fls_OspiConfig[0].object;
    (void)memset(obj, 0, sizeof(OSPI_Object));
    obj->isOpen = FALSE;

    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    OSPI_Handle    handle = NULL_PTR;
    OSPI_Config   *config = (OSPI_Config *)NULL_PTR;

    config = &Fls_OspiConfig[0];

    if (E_OK == retVal)
    {
        if (TRUE == obj->isOpen)
        {
            /* Handle already opened */
            retVal = E_NOT_OK;
        }
        else
        {
            obj->handle = (OSPI_Handle)config;
            /* Program OSPI instance according the user config */
            retVal = Fls_Ospi_ProgramInstance(config);
        }
    }
    if (E_OK == retVal)
    {
        obj->isOpen = TRUE;
        handle      = (OSPI_Handle)config;
    }
    else
    {
        if (NULL_PTR != config)
        {
            Fls_Ospi_Close((OSPI_Handle)config);
        }
    }

    return handle;
}
/**
 *  \Function Name: Fls_Ospi_Close
 *
 *   Function to close a OSPI peripheral specified by the OSPI handle.
 *
 */
void Fls_Ospi_Close(OSPI_Handle handle)
{
    if (handle != NULL_PTR)
    {
        OSPI_Object *obj = ((OSPI_Config *)handle)->object;
        /* Disable interrupts by read-modify-write to IRQ mask register */
        /* Disable Interrupt*/
        uint32       regVal  = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_MASK_REG);
        regVal              &= ~(OSPI_INTR_MASK_ALL);
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_MASK_REG, regVal);

        obj->isOpen = FALSE;
    }
    return;
}
/**
 *  \Function Name: Fls_Ospi_ProgramInstance
 *
 *   Function configure OSPI Parameter such as OSPI pin and baudrate
 *
 */
static Std_ReturnType Fls_Ospi_ProgramInstance(OSPI_Config *config)
{
    Std_ReturnType retVal            = E_OK;
    OSPI_Handle    handle            = (OSPI_Handle)config;
    OSPI_Object   *obj               = ((OSPI_Config *)handle)->object;
    uint32         regVal            = 0U;
    uint8          addrnumBytesInput = 0U;

    /* Reset Enable the Flash */
    retVal = Nor_OspiCmdWrite(handle, OSPI_NOR_CMD_RSTEN, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    /*Reset the Flash*/
    retVal = Nor_OspiCmdWrite(handle, OSPI_NOR_CMD_RST, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    /* Optimal programming setup */
    /* Disable DAC */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 0);
    /* Disable DTR */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENABLE_DTR_PROTOCOL_FLD, 0);
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG, OSPI_DEV_INSTR_RD_CONFIG_REG_DDR_EN_FLD, 0);
    /* Disable XIP */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENTER_XIP_MODE_FLD, 0);
    /* Disable OSPI Controller */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_SPI_FLD, 0);
    /* Wait until Serial Interface and OSPI pipeline is IDLE. */
    /* Wait Idle*/
    uint32 retry      = 0U;
    uint32 timeOutVal = OSPI_READ_WRITE_TIMEOUT;

    while (timeOutVal != 0U)
    {
        if (HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_IDLE_FLD) != 0U)
        {
            retry++;
            if (retry == 3U)
            {
                retVal = E_OK;
                break;
            }
        }
        else
        {
            retry = 0U;
        }
        uint32 delay = OSPI_CHECK_IDLE_DELAY;
        while (delay != 0U)
        {
            delay--;
        };
        timeOutVal--;
    }

    if (retVal != E_OK)
    {
        Fls_Ospi_Close(handle);
        retVal = E_NOT_OK;
    }

    if (E_OK == retVal)
    {
        /* User config */
        if (FLS_USE_INTERRUPTS == STD_ON)
        {
            obj->transferMode = OSPI_TRANSFER_MODE_CALLBACK;
            /* When callback is supported, add logic */
        }
        else
        {
            obj->transferMode = OSPI_TRANSFER_MODE_POLLING;
        }
        /* Chip Select */
        regVal            = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG);
        uint32 chipSelect = (uint32)OSPI_CHIP_SELECT(Fls_DrvObj.chipSelect);
        uint32 decSelect  = Fls_DrvObj.decChipSelect;

        regVal &= ~(OSPI_CONFIG_REG_PERIPH_SEL_DEC_FLD_MASK | OSPI_CONFIG_REG_PERIPH_CS_LINES_FLD_MASK);
        regVal |= (decSelect << OSPI_CONFIG_REG_PERIPH_SEL_DEC_FLD_SHIFT) |
                  (chipSelect << OSPI_CONFIG_REG_PERIPH_CS_LINES_FLD_SHIFT);
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, regVal);

        /* Frame format */
        regVal  = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG);
        regVal &= ~(OSPI_CONFIG_REG_SEL_CLK_PHASE_FLD_MASK | OSPI_CONFIG_REG_SEL_CLK_POL_FLD_MASK);
        regVal |= (Fls_DrvObj.frmFmt);
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, regVal);

        /* Disable the adapted loop-back clock circuit */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_BYPASS_FLD, 1);
        /* Delay Setup */
        uint32 delays[4] = {10, 10, 10, 10};
        uint32 devDelay =
            ((delays[0] << OSPI_DEV_DELAY_REG_D_INIT_FLD_SHIFT) | (delays[1] << OSPI_DEV_DELAY_REG_D_AFTER_FLD_SHIFT) |
             (delays[2] << OSPI_DEV_DELAY_REG_D_BTWN_FLD_SHIFT) | (delays[3] << OSPI_DEV_DELAY_REG_D_NSS_FLD_SHIFT));
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_DELAY_REG, devDelay);

        if (Fls_DrvObj.baudRateDiv != 0U)
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_MSTR_BAUD_DIV_FLD,
                          OSPI_BAUD_RATE_DIVISOR(Fls_DrvObj.baudRateDiv));
        }
        else
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_MSTR_BAUD_DIV_FLD,
                          OSPI_BAUD_RATE_DIVISOR_DEFAULT);
        }

        /* Disable PHY pipeline mode */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PIPELINE_PHY_FLD, FALSE);

        /* Disable PHY mode by default. This will be later enabled from flash driver */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PHY_MODE_ENABLE_FLD, FALSE);

        /* Set indirect trigger address register */
        if (FLS_OSPI_DAC_ENABLE == STD_ON)
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 1);
            HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0x4000000);
        }
        else
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 0);
            HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0);
        }

        /* Disable write completion auto polling */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_WRITE_COMPLETION_CTRL_REG,
                      OSPI_WRITE_COMPLETION_CTRL_REG_DISABLE_POLLING_FLD, 1);
        /* Set and invalid opcode in the WRITE_COMPLETION_CTRL_REG due to IP limitation */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_WRITE_COMPLETION_CTRL_REG,
                      OSPI_WRITE_COMPLETION_CTRL_REG_OPCODE_FLD, OSPI_CMD_INVALID_OPCODE);
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_WRITE_COMPLETION_CTRL_REG,
                      OSPI_WRITE_COMPLETION_CTRL_REG_POLL_COUNT_FLD, 3U);

        /* Disable dual byte opcode. If OSPI boot mode was used, ROM would have set this. This can
         * cause 1s mode applications to fail */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_DUAL_BYTE_OPCODE_EN_FLD, FALSE);

        /* Set SRAM partition configuration */
        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_SRAM_PARTITION_CFG_REG, OSPI_SRAM_PARTITION_DEFAULT);

        /* Disable and clear the interrupts */
        Fls_IntClearDisable();

        /* Enable OSPI Controller */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_SPI_FLD, 1);

        /*Config Reset Pin*/
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_RESET_CFG_FLD, TRUE);
        /* Set device size and addressing bytes */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                      OSPI_DEV_SIZE_CONFIG_REG_BYTES_PER_DEVICE_PAGE_FLD, fls_config_sfdp->pageSize);
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                      OSPI_DEV_SIZE_CONFIG_REG_BYTES_PER_SUBSECTOR_FLD,
                      OSPI_utilLog2(fls_config_sfdp->eraseCfg.blockSize));

        /* Set current protocol as 1s1s1s */
        obj->currentprotocol          = FLS_OSPI_RX_1S_1S_1S;
        addrnumBytesInput             = fls_config_sfdp->addrnumBytes;
        fls_config_sfdp->addrnumBytes = 3;
        /* Now configure the flash for the 1s_1s_1s protocol */
        retVal = Fls_Ospi_setProtocol(handle, FLS_OSPI_RX_1S_1S_1S);

#ifdef AM263PX_SIP_PACKAGE
        Fls_setResetPinMode(FLS_RESET_PIN_STATE_HIGH);
        Fls_setResetPinMode(FLS_RESET_PIN_STATE_LOW);
#endif
        /* Now configure the flash for the selected protocol */
        retVal               = Fls_Ospi_setProtocol(handle, Fls_DrvObj.Fls_Mode);
        obj->currentprotocol = Fls_DrvObj.Fls_Mode;

        fls_config_sfdp->addrnumBytes = addrnumBytesInput;
        /* Set address bytes to 3 */
        if (Fls_DrvObj.Fls_Mode == (uint32)FLS_OSPI_RX_1S_1S_1S)
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                          OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, 2);
        }
        else
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                          OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, fls_config_sfdp->addrnumBytes - 1U);
        }
        /* Set opcodes in OSPI controller */
        Fls_Ospi_setXferOpCodes(handle, fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].cmdRd,
                                fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].cmdWr);

        /* Set Mode Clocks and Dummy Clocks in Controller and Flash Memory */
        retVal = Fls_Ospi_SetModeDummy(handle);

        /* Set RD Capture Delay by reading ID */
        uint32 readDataCapDelay = 4U;
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD,
                      readDataCapDelay);

        retVal = Nor_OspiReadId(handle);

        while ((retVal != E_OK) && (readDataCapDelay > 0U))
        {
            readDataCapDelay--;
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD,
                          readDataCapDelay);
            retVal = Nor_OspiReadId(handle);
        }
    }
    return retVal;
}

static uint32 OSPI_utilLog2(uint32 num)
{
    /* LUT based bit scan method using deBruijn(2, 5) sequence to avoid the loop */
    uint32 ret  = 0U;
    uint32 temp = num;

    if (num != 0U)
    {
        /* Assume num is not power of 2, fill 1's after the most significant 1 */
        temp |= (temp >> 1U);
        temp |= (temp >> 2U);
        temp |= (temp >> 4U);
        temp |= (temp >> 8U);
        temp |= (temp >> 16U);

        /* 0x07C4ACDD is a modified deBruijn sequence */
        ret = (uint32)gTable[(uint32)((temp * 0x07C4ACDD) >> 27U)];
    }

    return ret;
}
/**
 *  \Function Name: Nor_OspiSetAddressBytes
 *
 *  This function set up addressing mode according to flash support
 *
 */
Std_ReturnType Nor_OspiSetAddressBytes(OSPI_Handle handle)
{
    Std_ReturnType retVal = E_OK;

    switch (fls_config_sfdp->addrByteSupport)
    {
        case 0:
            /* Only 3 byte addressing supported, nothing to do with flash. Set OSPI driver */
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                          OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, 2);
            break;

        case 1:
            /* Both 3 and 4 byte addressing supported. Configure flash to switch to
             * 4 byte addressing if that's selected
             * */
            if (fls_config_sfdp->addrnumBytes == (uint8)4U)
            {
                (void)Nor_OspiSet4ByteAddrMode(handle);
                HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                              OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, 3);
            }
            else
            {
                HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                              OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, 2);
            }
            break;

        case 2:
            /* Only 4 byte addressing supported. Configure flash to switch to 4 byte
             * addressing
             * */
            (void)Nor_OspiSet4ByteAddrMode(handle);
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                          OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, 3);

            break;

        default:
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG,
                          OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, 2);

            break;
    }

    return retVal;
}

/**
 *  \Function Name: Fls_OspiSet3ByteAddress
 *
 *  This function set up addressing mode to 3 byte.
 *
 */
Std_ReturnType Fls_OspiSet3ByteAddress(void)
{
    Std_ReturnType retVal = E_OK;

    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG, OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD, 2);
    fls_config_sfdp->addrnumBytes = 3;

    return retVal;
}

/**
 *  \Function Name: Fls_OspiSetResetPinMode
 *
 *  This function Updates Reset Pin value.
 *
 */
Std_ReturnType Fls_OspiSetResetPinMode(Fls_ResetPinMode pinMode)
{
    Std_ReturnType retVal = E_OK;

    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR, OSPI_CONFIG_REG_RESET_PIN_FLD, pinMode);

    return retVal;
}

/**
 *  \Function Name: Fls_Ospi_setProtocol
 *
 *   This function sets the protocol for single/quad/octal read/write
 *   according to user config
 *
 */
Std_ReturnType Fls_Ospi_setProtocol(OSPI_Handle handle, uint32 protocol)
{
    Std_ReturnType retVal = E_OK;
    uint32         cmd, data, addr, dtr;
    dtr = 0;

    switch (protocol)
    {
        case FLS_OSPI_RX_1S_1S_1S:
            /*Set cmd, address, data and dtr*/
            cmd  = 0;
            addr = 0;
            data = 0;
            Fls_Ospi_setXferOpCodes(handle, fls_config_sfdp->protos[FLS_OSPI_RX_1S_1S_1S].cmdRd,
                                    fls_config_sfdp->protos[FLS_OSPI_RX_1S_1S_1S].cmdWr);
            break;

        case FLS_OSPI_RX_1S_1S_2S:
            /*Set cmd, address, data and dtr*/
            cmd  = 0;
            addr = 0;
            data = 1;
            break;

        case FLS_OSPI_RX_1S_1S_4S:
            /* Set Quad Enable Bit. Set commands, mode and dummy cycle if needed */
            /*Set cmd, address, data and dtr*/
            cmd  = 0;
            addr = 0;
            data = 2;
            /* Set QE bit */
            retVal += Nor_OspiSetQeBit(handle, fls_config_sfdp->protos[FLS_OSPI_RX_1S_1S_4S].enableType);
            break;

        case FLS_OSPI_RX_1S_1S_8S:
            /* Set Octal Enable Bit. Set commands, mode and dummy cycle if needed */
            /*Set cmd, address, data and dtr*/
            cmd  = 0;
            addr = 0;
            data = 3;
            /* Set OE bit */
            retVal += Nor_OspiSetOeBit(handle, fls_config_sfdp->protos[FLS_OSPI_RX_1S_1S_8S].enableType);
            break;

        case FLS_OSPI_RX_4S_4S_4S:
            /* Set Quad Enable Bit. Set 444 mode. Set commands, mode and dummy cycle if needed.
             * In case of DTR, enable that too*/
            /*Set cmd, address, data and dtr*/
            cmd  = 2;
            addr = 2;
            data = 2;
            /* Set QE bit */
            retVal += Nor_OspiSetQeBit(handle, fls_config_sfdp->protos[FLS_OSPI_RX_4S_4S_4S].enableType);
            /* Set 444 mode */
            retVal += Fls_set444mode(handle, fls_config_sfdp->protos[FLS_OSPI_RX_4S_4S_4S].enableSeq);
            break;
        case FLS_OSPI_RX_4S_4D_4D:
            /* Set Quad Enable Bit. Set 444 mode. Set commands, mode and dummy cycle if needed.
             * In case of DTR, enable that too*/
            /*Set cmd, address, data and dtr*/
            cmd  = 2;
            addr = 2;
            data = 2;
            dtr  = 1;
            /* Set QE bit */
            retVal += Nor_OspiSetQeBit(handle, fls_config_sfdp->protos[FLS_OSPI_RX_4S_4D_4D].enableType);
            /* Set 444 mode */
            retVal += Fls_set444mode(handle, fls_config_sfdp->protos[FLS_OSPI_RX_4S_4D_4D].enableSeq);
            break;

        case FLS_OSPI_RX_8S_8S_8S:
            /* Set Octal Enable Bit. Set 888 mode. Set commands, mode and dummy cycle if needed */
            /*Set cmd, address, data and dtr*/
            cmd  = 3;
            addr = 3;
            data = 3;
            /* Set OE bit */
            retVal = Nor_OspiSetOeBit(handle, fls_config_sfdp->protos[FLS_OSPI_RX_8S_8S_8S].enableType);
            /* Set 888 mode */
            retVal += Fls_set888mode(handle, fls_config_sfdp->protos[FLS_OSPI_RX_8S_8S_8S].enableSeq);
            break;

        case FLS_OSPI_RX_8D_8D_8D:
            /* Set Octal Enable Bit. Set 888 mode. Set commands, mode and dummy cycle if needed */
            /*Set cmd, address, data and dtr*/
            cmd  = 3;
            addr = 3;
            data = 3;
            dtr  = 1;
            /* Set OE bit */
            retVal = Nor_OspiSetOeBit(handle, fls_config_sfdp->protos[FLS_OSPI_RX_8D_8D_8D].enableType);
            /* Set 888 mode */
            retVal += Fls_set888mode(handle, fls_config_sfdp->protos[FLS_OSPI_RX_8D_8D_8D].enableSeq);
            break;

        default:
            /*Set cmd, address, data and dtr*/
            cmd  = 0;
            addr = 0;
            data = 0;
            Fls_Ospi_setXferOpCodes(handle, fls_config_sfdp->protos[FLS_OSPI_RX_1S_1S_1S].cmdRd,
                                    fls_config_sfdp->protos[FLS_OSPI_RX_1S_1S_1S].cmdWr);
            break;
    }
    Fls_Ospi_SetProtocolCmds(handle, cmd, addr, data, dtr);

    return retVal;
}
/**
 *  \Function Name: Fls_Ospi_SetProtocolCmds
 *
 *   This function sets the command, data and address lines for the
 *   configured protocol
 *
 */
void Fls_Ospi_SetProtocolCmds(OSPI_Handle handle, uint32 cmd, uint32 addr, uint32 data, uint32 dtr)
{
    (void)handle;
    /* Transfer lines for Read */
    /* Set transfer lines for sending command */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG, OSPI_DEV_INSTR_RD_CONFIG_REG_INSTR_TYPE_FLD,
                  cmd);
    /* Set transfer lines for sending address */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                  OSPI_DEV_INSTR_RD_CONFIG_REG_ADDR_XFER_TYPE_STD_MODE_FLD, addr);
    /* Set transfer lines for sending data */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                  OSPI_DEV_INSTR_RD_CONFIG_REG_DATA_XFER_TYPE_EXT_MODE_FLD, data);

    /* Transfer lines for Write */
    /* Set transfer lines for sending address */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_WR_CONFIG_REG,
                  OSPI_DEV_INSTR_WR_CONFIG_REG_ADDR_XFER_TYPE_STD_MODE_FLD, addr);
    /* Set transfer lines for sending data */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_WR_CONFIG_REG,
                  OSPI_DEV_INSTR_WR_CONFIG_REG_DATA_XFER_TYPE_EXT_MODE_FLD, data);

    if (dtr != 0U)
    {
        if ((cmd == 3U) && (data == 3U) && (addr == 3U))
        {
            /* Enable DDR Mode */
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENABLE_DTR_PROTOCOL_FLD, TRUE);
            /* Enable dual byte opcode */
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_DUAL_BYTE_OPCODE_EN_FLD, TRUE);
        }
        if ((cmd == 2U) && (data == 2U) && (addr == 2U))
        {
            /* Enable DDR EN commands */
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                          OSPI_DEV_INSTR_RD_CONFIG_REG_DDR_EN_FLD, 1);
        }
    }
}
/**
 *  \Function Name: Fls_Ospi_setXferOpCodes
 *
 *   This function set the transfer code for read and write
 *
 */
void Fls_Ospi_setXferOpCodes(OSPI_Handle handle, uint8 readCmd, uint8 pageProgCmd)
{
    if (handle != NULL)
    {
        uint8 cmdExtRead  = OSPI_CMD_INVALID_OPCODE;
        uint8 cmdExtWrite = OSPI_CMD_INVALID_OPCODE;

        /* Get the extended opcode type for read and Write */
        if (fls_config_sfdp->cmdExtType == OSPI_CMD_EXT_TYPE_REPEAT)
        {
            cmdExtRead  = readCmd;
            cmdExtWrite = pageProgCmd;
        }
        else if (fls_config_sfdp->cmdExtType == OSPI_CMD_EXT_TYPE_INVERSE)
        {
            cmdExtRead  = ~readCmd;
            cmdExtWrite = ~pageProgCmd;
        }
        else
        {
            if (fls_config_sfdp->cmdExtType == OSPI_CMD_EXT_TYPE_NONE)
            {
                cmdExtRead  = OSPI_CMD_INVALID_OPCODE;
                cmdExtWrite = OSPI_CMD_INVALID_OPCODE;
            }
        }
        /* Set opcode for read */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                      OSPI_DEV_INSTR_RD_CONFIG_REG_RD_OPCODE_NON_XIP_FLD, readCmd);

        if (cmdExtRead != OSPI_CMD_INVALID_OPCODE)
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_OPCODE_EXT_LOWER_REG,
                          OSPI_OPCODE_EXT_LOWER_REG_EXT_READ_OPCODE_FLD, cmdExtRead);
        }

        /* Set opcode for write */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_WR_CONFIG_REG,
                      OSPI_DEV_INSTR_WR_CONFIG_REG_WR_OPCODE_FLD, pageProgCmd);

        if (cmdExtWrite != OSPI_CMD_INVALID_OPCODE)
        {
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_OPCODE_EXT_LOWER_REG,
                          OSPI_OPCODE_EXT_LOWER_REG_EXT_WRITE_OPCODE_FLD, cmdExtWrite);
        }
    }
    else
    {
        /* do nothing */
    }
}
/**
 *  \Function Name: Fls_Ospi_SetModeDummy
 *
 *   Function to set mode cmd and dummy cycles
 *
 */
Std_ReturnType Fls_Ospi_SetModeDummy(OSPI_Handle handle)
{
    OSPI_Config   *pHandle = (OSPI_Config *)handle;
    OSPI_Object   *obj     = pHandle->object;
    Std_ReturnType retVal  = E_OK;

    if (fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].modeClksCmd != 0U)
    {
        /* Enable mode bits transmission while sending CMDs*/
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_ENB_MODE_BIT_FLD, 1);
    }
    if (fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].modeClksRd != 0)
    {
        /* Set mode bits in the mode bit field of OSPI config register*/
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_MODE_BIT_CONFIG_REG, OSPI_MODE_BIT_CONFIG_REG_MODE_FLD,
                      (uint8)fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].modeClksRd);
        /* Enable mode bits transmission while reading*/
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                      OSPI_DEV_INSTR_RD_CONFIG_REG_MODE_BIT_ENABLE_FLD, 1);
    }
    /* Set appropriate dummy cycles for flash read*/

    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                  OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD,
                  fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyClksRd);
    obj->rdDummyCycles = fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyClksRd;
    /* Set appropriate dummy cycles to be used while sending STIG commands to flash*/

    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_FLASH_CMD_CTRL_REG, OSPI_FLASH_CMD_CTRL_REG_NUM_DUMMY_CYCLES_FLD,
                  fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyClksCmd);

    obj->cmdDummyCycles = fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyClksCmd;

    if ((fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyClksCmd != 0U) ||
        (fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyClksRd != 0U))
    {
        retVal = Ospi_SetRegCfg(handle, &(fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].dummyCfg));

        if (retVal == E_OK)
        {
            retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        }
    }

    return retVal;
}
/**
 *  \Function Name: Fls_hwi
 *
 *  This function check the Hardware interrupt status register. if interrupt is
 *  occured then perform the corresponding operation and this function call is
 *  in Fls_Irq.c file.
 *
 */
void Fls_hwi(void)
{
#if (STD_ON == FLS_USE_INTERRUPTS)
    Std_ReturnType  retVal = E_OK;
    uint32          intrStatus;
    volatile uint32 retry;
    uint32          sramLevel = 0, rdBytes = 0, wrBytes = 0;
    uint32          len         = Fls_DrvObj.length;
    uint32         *destPtr     = (uint32 *)Fls_DrvObj.ramAddr;
    uint8          *Compare_Buf = Fls_DrvObj.compareAddr;
    uint8          *Read_Buf    = Fls_DrvObj.ramAddr;

    /* Read the interrupt status register */
    intrStatus = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_STATUS_REG);

    if (Fls_DrvObj.jobResultType == MEMIF_JOB_PENDING)
    {
        switch (Fls_DrvObj.jobType)
        {
            case FLS_JOB_COMPARE:
            case FLS_JOB_BLANKCHECK:
            case FLS_JOB_READ:
                /* Indirect read operation */
                if ((intrStatus & OSPI_INTR_MASK_IND_XFER) != 0U)
                {
                    if (Fls_DrvObj.length != 0U)
                    {
                        sramLevel = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_SRAM_FILL_REG) &
                                    OSPI_SRAM_FILL_REG_SRAM_FILL_INDAC_READ_FLD_MASK;
                        if (sramLevel == 0U)
                        {
                            retVal = E_NOT_OK;
                        }
                        if (retVal == E_OK)
                        {
                            rdBytes = sramLevel * OSPI_FIFO_WIDTH;
                            rdBytes = (rdBytes > (uint32)Fls_DrvObj.length) ? (uint32)Fls_DrvObj.length : rdBytes;

                            /* Read data from FIFO */
                            uint32 temp;
                            uint32 remaining;
                            if (Fls_DrvObj.jobType == FLS_JOB_READ)
                            {
                                destPtr = (uint32 *)Fls_DrvObj.ramAddr;
                            }
                            else
                            {
                                destPtr = (uint32 *)Fls_DrvObj.compareAddr;
                            }

                            for (remaining = rdBytes; remaining >= OSPI_FIFO_WIDTH; remaining -= OSPI_FIFO_WIDTH)
                            {
                                *destPtr = HW_RD_REG32((uintptr_t)FLS_BASE_ADDRESS);
                                destPtr++;
                            }
                            if (remaining > 0U)
                            {
                                temp = HW_RD_REG32((uintptr_t)FLS_BASE_ADDRESS);
                                memcpy(destPtr, &temp, remaining);
                            }
                            Fls_DrvObj.ramAddr += rdBytes;
                            if (Fls_DrvObj.jobType == FLS_JOB_COMPARE || Fls_DrvObj.jobType == FLS_JOB_BLANKCHECK)
                            {
                                Fls_DrvObj.compareAddr += rdBytes;
                                Fls_DrvObj.transferred += rdBytes;
                            }
                            Fls_DrvObj.length    -= rdBytes;
                            Fls_DrvObj.flashAddr += rdBytes;
                        }
                    }

                    if (retVal == E_OK)
                    {
                        intrStatus = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_STATUS_REG);

                        if ((Fls_DrvObj.length == 0U) ||
                            ((intrStatus & OSPI_IRQ_STATUS_REG_INDIRECT_OP_DONE_FLD_MASK) != 0U))
                        {
                            /* Clear indirect read operation complete status */
                            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_CTRL_REG,
                                          OSPI_INDIRECT_READ_XFER_CTRL_REG_IND_OPS_DONE_STATUS_FLD, 1);

                            /* clear the interrupts */
                            HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_STATUS_REG, intrStatus);

                            if (Fls_DrvObj.length != 0U)
                            {
                                /* Config the Indirect Read Transfer Start Address Register */
                                HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_START_REG,
                                            Fls_DrvObj.flashAddr);

                                if (Fls_DrvObj.length > 256U)
                                {
                                    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_NUM_BYTES_REG, 256U);
                                }
                                else
                                {
                                    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_NUM_BYTES_REG,
                                                Fls_DrvObj.length);
                                }
                                /* Start the indirect read transfer */
                                HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_READ_XFER_CTRL_REG,
                                              OSPI_INDIRECT_READ_XFER_CTRL_REG_START_FLD, 1);
                            }
                        }
                    }

                    if ((Fls_DrvObj.jobType == FLS_JOB_COMPARE) && (retVal == E_OK))
                    {
                        uint32 idx   = 0U;
                        uint32 match = TRUE;
                        len          = len - Fls_DrvObj.length;
                        for (idx = (uint32)0; ((idx < len) && (match != FALSE)); idx++)
                        {
                            if (*Compare_Buf != *Read_Buf)
                            {
                                match                    = FALSE;
                                Fls_DrvObj.jobResultType = MEMIF_JOB_FAILED;
                                Fls_DrvObj.status        = MEMIF_IDLE;
                                Fls_DrvObj.jobType       = FLS_JOB_NONE;
                                Fls_DrvObj.transferred   = 0U;
                                Fls_DrvObj.Fls_JobErrorNotification();
                                break;
                            }
                            Compare_Buf++;
                            Read_Buf++;
                        }
                    }
                    if ((Fls_DrvObj.jobType == FLS_JOB_BLANKCHECK) && (retVal == E_OK))
                    {
                        uint32 idx   = 0U;
                        uint32 match = TRUE;
                        len          = len - Fls_DrvObj.length;
                        for (idx = (uint32)0; ((idx < len) && (match != FALSE)); idx++)
                        {
                            if (*Compare_Buf != 0xFF)
                            {
                                match                    = FALSE;
                                Fls_DrvObj.jobResultType = MEMIF_JOB_FAILED;
                                Fls_DrvObj.status        = MEMIF_IDLE;
                                Fls_DrvObj.jobType       = FLS_JOB_NONE;
                                Fls_DrvObj.transferred   = 0U;
                                Fls_DrvObj.Fls_JobErrorNotification();
                                break;
                            }
                            Compare_Buf++;
                        }
                    }
                }

                if (((Fls_LengthType)0U == Fls_DrvObj.length) && (retVal == E_OK))
                {
                    Fls_IntClearDisable();
                    Fls_DrvObj.jobResultType = MEMIF_JOB_OK;
                    Fls_DrvObj.status        = MEMIF_IDLE;
                    Fls_DrvObj.jobType       = FLS_JOB_NONE;
                    Fls_DrvObj.transferred   = 0U;
                    Fls_DrvObj.Fls_JobEndNotification();
                }
                break;

            case FLS_JOB_WRITE:
                /* Indirect write operation */
                if ((intrStatus & OSPI_INTR_MASK_IND_XFER) != 0U)
                {
                    if (Fls_DrvObj.length != 0U)
                    {
                        sramLevel =
                            OSPI_SRAM_PARTITION_WR - (HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_SRAM_FILL_REG) >>
                                                      OSPI_SRAM_FILL_REG_SRAM_FILL_INDAC_WRITE_FLD_SHIFT);

                        wrBytes = sramLevel * OSPI_FIFO_WIDTH;
                        wrBytes = (wrBytes > Fls_DrvObj.length) ? Fls_DrvObj.length : wrBytes;

                        /* Write data to FIFO */
                        uint32  temp;
                        uint32  remaining;
                        uint32 *srcPtr = (uint32 *)Fls_DrvObj.ramAddr;

                        for (remaining = wrBytes; remaining >= OSPI_FIFO_WIDTH; remaining -= OSPI_FIFO_WIDTH)
                        {
                            HW_WR_REG32((uintptr_t)FLS_BASE_ADDRESS, *srcPtr);
                            srcPtr++;
                        }
                        if (remaining > 0U)
                        {
                            /* dangling bytes */
                            memcpy(&temp, srcPtr, remaining);
                            HW_WR_REG32((uintptr_t)FLS_BASE_ADDRESS, temp);
                        }
                        Fls_DrvObj.ramAddr   += wrBytes;
                        Fls_DrvObj.length    -= wrBytes;
                        Fls_DrvObj.flashAddr += wrBytes;
                    }

                    retry = OSPI_READ_WRITE_TIMEOUT;
                    /* Check flash indirect write controller status */
                    while (retry != 0U)
                    {
                        retry--;
                    }

                    intrStatus = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_STATUS_REG);

                    if ((Fls_DrvObj.length == 0U) ||
                        ((intrStatus & OSPI_IRQ_STATUS_REG_INDIRECT_OP_DONE_FLD_MASK) != 0U))
                    {
                        /* Clear indirect write operation complete status */
                        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_CTRL_REG,
                                      OSPI_INDIRECT_WRITE_XFER_CTRL_REG_IND_OPS_DONE_STATUS_FLD, 1);

                        /* clear the interrupts */
                        HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_STATUS_REG, intrStatus);

                        if (Fls_DrvObj.length != 0U)
                        {
                            /* Set the Indirect Write Transfer Start Address Register */
                            HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_START_REG,
                                        Fls_DrvObj.flashAddr);

                            /* Set the Indirect Write Transfer length */
                            if (Fls_DrvObj.length > 256U)
                            {
                                HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_REG, 256U);
                            }
                            else
                            {
                                HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_NUM_BYTES_REG,
                                            Fls_DrvObj.length);
                            }
                            /* Start the indirect write transfer */
                            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_INDIRECT_WRITE_XFER_CTRL_REG,
                                          OSPI_INDIRECT_WRITE_XFER_CTRL_REG_START_FLD, 1);
                        }
                    }
                }
                if ((Fls_LengthType)0U == Fls_DrvObj.length)
                {
                    Fls_IntClearDisable();
                    Fls_DrvObj.jobResultType = MEMIF_JOB_OK;
                    Fls_DrvObj.status        = MEMIF_IDLE;
                    Fls_DrvObj.jobType       = FLS_JOB_NONE;
                    Fls_DrvObj.transferred   = 0U;
                    Fls_DrvObj.Fls_JobEndNotification();
                }
                break;

            default:
                break;
        }
    }
#endif
}
/**
 *  \Function Name: Fls_OspiIntEnable
 *
 *   This function is used to enable word or frame complete interrupt
 *
 */
void Fls_OspiIntEnable(void)
{
    uint32 regVal  = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_MASK_REG);
    regVal        |= (OSPI_INTR_MASK_ALL);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_MASK_REG, regVal);
}
/**
 *  \Function Name: Fls_IntClearDisable
 *
 *   This function is used to disable and clear Interrupt Register.
 *
 */
void Fls_IntClearDisable(void)
{
    /* Disable Interrupt*/
    uint32 regVal  = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_MASK_REG);
    regVal        &= ~(OSPI_INTR_MASK_ALL);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_MASK_REG, regVal);
    /* Clear Interrupt*/
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IRQ_STATUS_REG, OSPI_INTR_MASK_ALL);
}

void Fls_Interrupt_Enable(void)
{
    processJobs(Fls_DrvObj.jobType);
}
/**
 *  \Function Name: Fls_set888mode
 *
 *   This function is used to set register read and write commands for 888 mode.
 *
 */
Std_ReturnType Fls_set888mode(OSPI_Handle handle, uint8 seq)
{
    OSPI_Config   *pHandle = (OSPI_Config *)handle;
    OSPI_Object   *obj     = pHandle->object;
    Std_ReturnType retVal  = E_OK;

    if ((seq & (1 << 1)) != 0U)
    {
        retVal = Nor_OspiCmdWrite(handle, 0xE8, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
        if (Fls_DrvObj.Fls_Mode == (uint32)FLS_OSPI_RX_8D_8D_8D)
        {
            Fls_Ospi_SetProtocolCmds(handle, 3, 3, 3, 1);
        }
        else
        {
            Fls_Ospi_SetProtocolCmds(handle, 3, 3, 3, 0);
        }
        obj->currentprotocol = Fls_DrvObj.Fls_Mode;
        if (retVal == E_OK)
        {
            retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        }
    }
    if ((seq & (1 << 2)) != 0U)
    {
        retVal = Nor_OspiCmdWrite(handle, fls_config_sfdp->cmdWren, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
        if (retVal == E_OK)
        {
            retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        }
        retVal = Nor_OspiCmdWrite(handle, 0x72, 0, 0, NULL, 0);
        if (Fls_DrvObj.Fls_Mode == (uint32)FLS_OSPI_RX_8D_8D_8D)
        {
            Fls_Ospi_SetProtocolCmds(handle, 3, 3, 3, 1);
        }
        else
        {
            Fls_Ospi_SetProtocolCmds(handle, 3, 3, 3, 0);
        }
        obj->currentprotocol = Fls_DrvObj.Fls_Mode;
        if (retVal == E_OK)
        {
            retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        }
    }

    /* Check for register addressed 8-8-8 mode */
    Flash_RegEnConfig *octCfg = &(fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].protoCfg);
    Flash_RegEnConfig *dCfg   = &(fls_config_sfdp->protos[Fls_DrvObj.Fls_Mode].strDtrCfg);

    if (octCfg->isAddrReg && dCfg->isAddrReg && (dCfg->cfgReg == octCfg->cfgReg))
    {
        /* Do both the configs together */
        uint8 reg = 0U;
        retVal    = Nor_OspiRegRead(handle, octCfg->cmdRegRd, octCfg->cfgReg, &reg);
        if (E_OK == retVal)
        {
            /* Octal DDR is special. Check if it is already enabled */
            if ((((reg >> octCfg->shift) & 0x01) == (uint8)1U) && (((reg >> dCfg->shift) & 0x01) == (uint8)1U))
            {
                /* Already 8D */
            }
            else
            {
                /* Clear the config bits in the register  */
                reg &= ~(uint8)(octCfg->mask | dCfg->mask);
                /* Bitwise OR the bit pattern for setting the dummyCycle selected */
                reg |= (octCfg->cfgRegBitP << octCfg->shift);
                if (Fls_DrvObj.Fls_Mode == (uint32)FLS_OSPI_RX_8D_8D_8D)
                {
                    reg |= (dCfg->cfgRegBitP << dCfg->shift);
                }
                retVal += Nor_OspiRegWrite(handle, octCfg->cmdRegWr, octCfg->cfgReg, reg);
            }
        }
        if (Fls_DrvObj.Fls_Mode == (uint32)FLS_OSPI_RX_8D_8D_8D)
        {
            Fls_Ospi_SetProtocolCmds(handle, 3, 3, 3, 1);
        }
        else
        {
            Fls_Ospi_SetProtocolCmds(handle, 3, 3, 3, 0);
        }
    }
    else
    {
        (void)Ospi_SetRegCfg(handle, octCfg);
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
        (void)Ospi_SetRegCfg(handle, dCfg);
        if (Fls_DrvObj.Fls_Mode == (uint32)FLS_OSPI_RX_8D_8D_8D)
        {
            obj->currentprotocol = Fls_DrvObj.Fls_Mode;
        }
        retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);
    }
    if (retVal == E_OK)
    {
        obj->currentprotocol = Fls_DrvObj.Fls_Mode;
    }

    return retVal;
}
/**
 *  \Function Name: Fls_set444mode
 *
 *   This function is used to set register read and write commands for 444 mode.
 *
 */
Std_ReturnType Fls_set444mode(OSPI_Handle handle, uint8 seq)
{
    OSPI_Object   *obj      = ((OSPI_Config *)handle)->object;
    Std_ReturnType retVal   = E_OK;
    uint32         seqFound = 0U;

    if ((seq & (uint8)(1 << 0)) != 0U)
    {
        /* Issue instruction 0x38 */
        retVal   = Nor_OspiCmdWrite(handle, 0x38, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
        seqFound = 1U;
    }
    if ((seq & (uint8)(1 << 1)) != 0U)
    {
        /* Issue instruction 0x38 */
        retVal   = Nor_OspiCmdWrite(handle, 0x38, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
        seqFound = 1U;
    }
    if ((seq & (uint8)(1 << 2)) != 0U)
    {
        /* Issue instruction 0x35 */
        retVal   = Nor_OspiCmdWrite(handle, 0x35, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);
        seqFound = 1U;
    }
    if ((seq & (uint8)(1 << 3)) != 0U)
    {
        /* Read modify write of reg, set bit 6 */
        uint8 reg = 0;
        (void)Nor_OspiRegRead(handle, 0x65, 0x800003, &reg);

        if ((reg & (1 << 6)) != 0U)
        {
            /* 444 mode already set */
        }
        else
        {
            reg |= (uint8)(1 << 6);
            (void)Nor_OspiRegWrite(handle, 0x71, 0x800003, reg);
        }
        seqFound = 1U;
    }
    if ((seq & (uint8)(1 << 4)) != 0U)
    {
        /* Read modify write of reg, clear bit 7 */
        uint8 reg = 0;
        (void)Nor_OspiRegRead(handle, 0x65, OSPI_CMD_INVALID_ADDR, &reg);

        if ((reg >> 7) == 0U)
        {
            /* 444 mode already set */
        }
        else
        {
            reg &= (uint8)(~(uint8)(1U << 7));
            (void)Nor_OspiRegWrite(handle, 0x61, OSPI_CMD_INVALID_ADDR, reg);
        }
        seqFound = 1U;
    }
    if (seqFound != 0U)
    {
        if (Fls_DrvObj.Fls_Mode == FLS_OSPI_RX_4S_4D_4D)
        {
            Fls_Ospi_SetProtocolCmds(handle, 2, 2, 2, 1);
        }
        else
        {
            Fls_Ospi_SetProtocolCmds(handle, 2, 2, 2, 0);
        }
        obj->currentprotocol = Fls_DrvObj.Fls_Mode;
    }
    retVal = Nor_OspiWaitReady(handle, fls_config_sfdp->flashBusyTimeout);

    return retVal;
}
/**
 *  \Function Name: Fls_set111mode
 *
 *   This function is used to set register read and write commands for 111 mode.
 *
 */
Std_ReturnType Fls_set111mode(OSPI_Handle handle, uint8 rdCmd, uint8 wrCmd, uint8 eraseCmd)
{
    (void)eraseCmd;
    Std_ReturnType retVal = E_OK;
    uint32         regVal = 0U;

    /* Reset Enablr the Flash */
    retVal = Nor_OspiCmdWrite(handle, OSPI_NOR_CMD_RSTEN, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    /*Reset the Flash*/
    retVal = Nor_OspiCmdWrite(handle, OSPI_NOR_CMD_RST, OSPI_CMD_INVALID_ADDR, 0, NULL, 0);

    uint32 waitMicro = 500U * 1000U;
    while (waitMicro != 0)
    {
        waitMicro--;
    };

    /* Set lowest bus clock */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_MSTR_BAUD_DIV_FLD, 0xF);

    /* SDR will be enabled in flash by default, set OSPI controller to 1S-1S-1S mode */
    uint32 xferLines = 0;

    /* Set number of address bytes as 3 to support legacy flash devices also
        00 = 1 addr byte
        01 = 2 addr byte
        10 = 3 addr byte
        11 = 4 addr byte
    */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_SIZE_CONFIG_REG, OSPI_DEV_SIZE_CONFIG_REG_NUM_ADDR_BYTES_FLD,
                  0x02);

    /* Set RD and WR Config register */
    regVal = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG);
    /* Configure the Device Read Instruction Configuration Register */
    regVal &= ~((uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_INSTR_TYPE_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_RD_OPCODE_NON_XIP_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_ADDR_XFER_TYPE_STD_MODE_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_DATA_XFER_TYPE_EXT_MODE_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_DDR_EN_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD_MASK);

    regVal |= ((uint32)rdCmd << (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_RD_OPCODE_NON_XIP_FLD_SHIFT) |
              (xferLines << (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_DATA_XFER_TYPE_EXT_MODE_FLD_SHIFT) |
              (xferLines << (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_ADDR_XFER_TYPE_STD_MODE_FLD_SHIFT) |
              (xferLines << (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_INSTR_TYPE_FLD_SHIFT) |
              (uint32)(0U << (uint32)OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD_SHIFT);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG, regVal);

    regVal = HW_RD_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_WR_CONFIG_REG);

    /* Configure the Device Write Instruction Configuration Register */
    regVal &= ~((uint32)OSPI_DEV_INSTR_WR_CONFIG_REG_WR_OPCODE_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_WR_CONFIG_REG_DATA_XFER_TYPE_EXT_MODE_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_WR_CONFIG_REG_ADDR_XFER_TYPE_STD_MODE_FLD_MASK |
                (uint32)OSPI_DEV_INSTR_WR_CONFIG_REG_DUMMY_WR_CLK_CYCLES_FLD_MASK);
    regVal |= ((uint32)wrCmd << (uint32)OSPI_DEV_INSTR_WR_CONFIG_REG_WR_OPCODE_FLD_SHIFT) |
              (xferLines << (uint32)OSPI_DEV_INSTR_WR_CONFIG_REG_ADDR_XFER_TYPE_STD_MODE_FLD_SHIFT) |
              (xferLines << (uint32)OSPI_DEV_INSTR_WR_CONFIG_REG_DATA_XFER_TYPE_EXT_MODE_FLD_SHIFT);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + (uint32)OSPI_DEV_INSTR_WR_CONFIG_REG, regVal);

    /* Set read capture delay */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD, 0U);

    return retVal;
}
/**
 *  \Function Name: Nor_FlsReadSfdp
 *
 *   This function is used to read sfdp related values.
 *
 */
Std_ReturnType Nor_FlsReadSfdp(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len)
{
    Std_ReturnType retVal = E_OK;

    /* Save the current command and dummy cycles */
    uint8 cmd       = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                                    OSPI_DEV_INSTR_RD_CONFIG_REG_RD_OPCODE_NON_XIP_FLD);
    uint8 dummyClks = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                                    OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD);

    /* Set read command and dummyClks for reading sfdp table */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                  OSPI_DEV_INSTR_RD_CONFIG_REG_RD_OPCODE_NON_XIP_FLD, OSPI_NOR_CMD_RDSFDP);
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                  OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD, OSPI_NOR_SFDP_DC);

    /* Perform SFDP read */
    retVal = Nor_OspiRead(handle, offset, buf, len);

    /* Set back to old read command and dummy clocks */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                  OSPI_DEV_INSTR_RD_CONFIG_REG_RD_OPCODE_NON_XIP_FLD, cmd);
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                  OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD, dummyClks);

    return retVal;
}

#define FLS_STOP_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

/*******************************************************************************
 *  End of File: Fls_Ospi.c
 ******************************************************************************/
