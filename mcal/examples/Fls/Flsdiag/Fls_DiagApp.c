/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This example performs QSPI transfer test using polling mode.
 *
 * The JEDEC ID of flash is read and printed out. A block
 * of flash memory is erased by sending erase command and
 * data is  written into the flash from a prefilled buffer.
 * Then, data is read back from it and validated.
 * If the equality test is successful, the test was successful.
 */
#include "Fls_NOR_SFDP.h"
#include <string.h>
#include <stdlib.h>
#include "Fls_Qspi.h"
#include "Fls_Brd_Nor.h"
#include "Fls_Startup.h"
#include "Det.h"

#define APP_QSPI_FLASH_OFFSET (0x40000U)

#define APP_QSPI_DATA_SIZE (256)

QSPI_Handle Fls_QspiHandle[1];

/* The source buffer used for transfer */
uint8 QspiTxBuf[APP_QSPI_DATA_SIZE];
/* Read buffer MUST be cache line aligned when using DMA */
uint8 QspiRxBuf[APP_QSPI_DATA_SIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));

NorSpi_SfdpHeader       SfdpHeader;
NorSpi_SfdpParamHeader  ParamHeaders[NOR_SPI_SFDP_NPH_MAX];
NorSpi_SfdpParamHeader *BfptHeader;

NorSpi_SfdpBasicFlashParamTable      Bfpt;
NorSpi_SfdpSectorMapParamTable       Smpt;
NorSpi_SfdpSCCRParamTable            Sccr;
NorSpi_SfdpProfile1ParamTable        Xpt1;
NorSpi_Sfdp4ByteAddressingParamTable Fbapt;

NorSpi_SfdpGenericDefines NorSpiDevDefines;

void                  qspi_flash_diag_test_fill_buffers(void);
uint32                qspi_flash_diag_test_compare_buffers(void);
uint32                qspi_flash_diag_print_sfdp(QSPI_Handle handle);
void                  qspi_flash_diag_print_defines_json(NorSpi_SfdpGenericDefines *norSpiDefines);
static Std_ReturnType Fls_norReadsfdp(QSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len);
static Std_ReturnType Fls_norWritesfdp(QSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len);
static Std_ReturnType Fls_norErasesfdp(QSPI_Handle handle, uint32 offset);
uint32                QSPI_norFlashInit(QSPI_Handle handle);
void                  copytoconfig(NorSpi_SfdpGenericDefines *norSpiDefines);
void                  qspi_flash_diag(void *args);
void                  Drivers_qspiClose(void);
void                  Drivers_qspiOpen(void);

int main(void)
{
    AppUtils_defaultInit();
    FlsApp_PlatformInit();
    qspi_flash_diag(NULL_PTR);
    return 0;
}

void qspi_flash_diag(void *args)
{
    Std_ReturnType status = E_OK;
    uint32         offset;

    Drivers_qspiOpen();

    AppUtils_printf("[QSPI Flash Diagnostic Test] Starting ...\r\n");

    /* Get QSPI Handle*/
    QSPI_Handle qspiHandle = NULL_PTR;
    uint32      instance   = CONFIG_QSPI0;
    if (instance < CONFIG_QSPI_NUM_INSTANCES)
    {
        QSPI_Object *obj;
        obj = Fls_QspiConfig[instance].object;

        if (obj && (TRUE == obj->isOpen))
        {
            qspiHandle = obj->handle;
        }
    }

    qspi_flash_diag_test_fill_buffers();

    /* Zero init the dev defines struct */
    memset(&NorSpiDevDefines, 0, sizeof(NorSpiDevDefines));

    QSPI_norFlashInit(qspiHandle);

#ifdef AM263X_PLATFORM
    Fls_DrvObj.flsBaudRateDiv = 1;
    status                    = Fls_Qspi_SetPreScaler(qspiHandle, Fls_DrvObj.flsBaudRateDiv);
#else
    Fls_DrvObj.flsBaudRateDiv = 0;
#endif
    Fls_DrvObj.Fls_Mode                         = 1;
    Fls_DrvObj.sectorList[0].sectorStartaddress = FLS_BASE_ADDRESS;

    /* Read ID */
    status = Nor_QspiReadId(qspiHandle);

    if (E_OK == status)
    {
        NorSpiDevDefines.manfId   = Fls_Config_SFDP_Ptr->manfId;
        NorSpiDevDefines.deviceId = Fls_Config_SFDP_Ptr->deviceId;

        AppUtils_printf("[QSPI Flash Diagnostic Test] Flash Manufacturer ID : 0x%X\r\n", NorSpiDevDefines.manfId);
        AppUtils_printf("[QSPI Flash Diagnostic Test] Flash Device ID       : 0x%X\r\n", NorSpiDevDefines.deviceId);
    }
    /* Fill buffers with known data,
     * find block number from offset,
     * erase block, write the data, read back from a specific offset
     * and finally compare the results.
     */
    offset = APP_QSPI_FLASH_OFFSET;

    if (E_OK == status)
    {
        qspi_flash_diag_test_fill_buffers();
        AppUtils_printf("[QSPI Flash Diagnostic Test] Executing Flash Erase on first block...\r\n");
        status = Fls_norErasesfdp(qspiHandle, offset);
        if (status == E_OK)
        {
            AppUtils_printf("[QSPI Flash Diagnostic Test] Done !!!\r\n");
        }
        else
        {
            AppUtils_printf("[QSPI Flash Diagnostic Test] Erase failed !!!\r\n");
        }
        AppUtils_printf("[QSPI Flash Diagnostic Test] Done !!!\r\n");
        AppUtils_printf("[QSPI Flash Diagnostic Test] Performing Write-Read Test...\r\n");
        status = Fls_norWritesfdp(qspiHandle, offset, QspiTxBuf, APP_QSPI_DATA_SIZE);
        if (status == E_OK)
        {
            status = Fls_norReadsfdp(qspiHandle, offset, QspiRxBuf, APP_QSPI_DATA_SIZE);
            if (status == E_OK)
            {
                status |= qspi_flash_diag_test_compare_buffers();
            }
            else
            {
                AppUtils_printf("[QSPI Flash Diagnostic Test] Read Failed!\r\n");
            }
        }
        else
        {
            AppUtils_printf("[QSPI Flash Diagnostic Test] Write Failed!\r\n");
        }

        if (E_OK == status)
        {
            AppUtils_printf("[QSPI Flash Diagnostic Test] Write-Read Test Passed!\r\n");
        }
    }

    if (E_OK == status)
    {
        /* Read the SFDP table and print flash details */
        status = qspi_flash_diag_print_sfdp(qspiHandle);
    }

    if (E_OK == status)
    {
        AppUtils_printf("All tests have passed!!\r\n");
    }
    else
    {
        AppUtils_printf("Some tests have failed!!\r\n");
    }
    Drivers_qspiClose();
}

void qspi_flash_diag_test_fill_buffers(void)
{
    uint32 i;

    for (i = 0U; i < APP_QSPI_DATA_SIZE; i++)
    {
        QspiTxBuf[i] = i;
        QspiRxBuf[i] = 0U;
    }
}

uint32 qspi_flash_diag_test_compare_buffers(void)
{
    Std_ReturnType status = E_OK;
    uint32         i;

    for (i = 0U; i < APP_QSPI_DATA_SIZE; i++)
    {
        if (QspiTxBuf[i] != QspiRxBuf[i])
        {
            status = E_NOT_OK;
            AppUtils_printf("QSPI read data mismatch !!!\r\n");
            break;
        }
    }
    return status;
}

uint32 qspi_flash_diag_print_sfdp(QSPI_Handle handle)
{
    Std_ReturnType status = E_OK;
    uint32         ptp    = 0xFFFFFFFFU;

    /* Read the SFDP header */
    status = Nor_QspiReadSfdp(handle, NOR_SPI_SFDP_HEADER_START_OFFSET, (void *)&SfdpHeader, sizeof(NorSpi_SfdpHeader));

    BfptHeader = &SfdpHeader.firstParamHeader;

    /* Check if the signature is read correctly */
    if (SfdpHeader.sfdpHeader.signature != NOR_SPI_SFDP_SIGNATURE)
    {
        AppUtils_printf(
            "[QSPI Flash Diagnostic Test] Error in reading SFDP Table or SFDP not supported by "
            "Flash !!!\r\n");
    }
    else
    {
        /* Print SFDP basic information */
        AppUtils_printf("[QSPI Flash Diagnostic Test] SFDP Information : \r\n");
        AppUtils_printf("================================================\r\n");
        AppUtils_printf("                      SFDP                      \r\n");
        AppUtils_printf("================================================\r\n");

        AppUtils_printf("SFDP Major Revision                       : 0x%X\r\n", SfdpHeader.sfdpHeader.majorRev);
        AppUtils_printf("SFDP Minor Revision                       : 0x%X\r\n", SfdpHeader.sfdpHeader.minorRev);
        AppUtils_printf("Number of Parameter Headers in this Table : %u\r\n\r\n",
                        SfdpHeader.sfdpHeader.numParamHeaders + 1);

        /* First parameter header is already read, read the rest of parameter headers if they exist
         */
        uint32 nph = SfdpHeader.sfdpHeader.numParamHeaders;
        uint32 i;

        if (nph > 0)
        {
            status = Nor_QspiReadSfdp(handle, NOR_SPI_SFDP_SECOND_PARAM_HEADER_OFFSET, (void *)&ParamHeaders,
                                      nph * sizeof(NorSpi_SfdpParamHeader));
        }

        if (status == E_OK)
        {
            /* Print the types of parameter tables present */
            AppUtils_printf("Types of Additional Parameter Tables in this flash\r\n");
            AppUtils_printf("---------------------------------------------------\r\n");

            for (i = 0; i < nph; i++)
            {
                NorSpi_SfdpParamHeader *paramHeader = &ParamHeaders[i];

                uint32 paramID = (uint32)((uint32)(paramHeader->paramIdMsb << 8U) | (uint32)(paramHeader->paramIdLsb));

                if (paramID != NOR_SPI_SFDP_BASIC_PARAM_TABLE_ID)
                {
                    char *paramName = NorSpi_Sfdp_getParameterTableName(paramID);

                    if (paramName == NULL_PTR)
                    {
                        AppUtils_printf("Unsupported Parameter Table type!!! - 0x%X\r\n", paramID);
                    }
                    else
                    {
                        AppUtils_printf("%s\r\n", paramName);
                    }
                }
                else
                {
                    /* Update the Bfpt pointer to the latest version */
                    if ((paramHeader->paramTableMajorRev == NOR_SPI_SFDP_JESD216_MAJOR) &&
                        ((paramHeader->paramTableMinorRev > BfptHeader->paramTableMinorRev) ||
                         ((paramHeader->paramTableMinorRev > BfptHeader->paramTableMinorRev) &&
                          (paramHeader->paramTableLength > BfptHeader->paramTableLength))))
                    {
                        BfptHeader = paramHeader;
                    }
                }
            }
        }

        /* Read the Basic Flash Parameter Table (BFPT) */
        ptp = NorSpi_Sfdp_getPtp(BfptHeader);

        status = Nor_QspiReadSfdp(handle, ptp, (void *)&Bfpt, BfptHeader->paramTableLength * sizeof(uint32));

        /* Parse BFPT */
        if (status == E_OK)
        {
            status = NorSpi_Sfdp_parseBfpt(&Bfpt, &NorSpiDevDefines, BfptHeader->paramTableLength);
        }

        /* Parse other parameter tables */
        for (i = 0; i < nph; i++)
        {
            NorSpi_SfdpParamHeader *paramHeader = &ParamHeaders[i];

            uint32 paramID = (uint32)((uint32)(paramHeader->paramIdMsb << 8U) | (uint32)(paramHeader->paramIdLsb));

            ptp = NorSpi_Sfdp_getPtp(paramHeader);

            switch (paramID)
            {
                case NOR_SPI_SFDP_PROFILE_TABLE_ID:
                    status =
                        Nor_QspiReadSfdp(handle, ptp, (void *)&Xpt1, paramHeader->paramTableLength * sizeof(uint32));
                    status = NorSpi_Sfdp_parseXpt1(&Xpt1, &NorSpiDevDefines, paramHeader->paramTableLength);
                    break;

                case NOR_SPI_SFDP_4BYTE_ADDR_INSTR_TABLE_ID:
                    status =
                        Nor_QspiReadSfdp(handle, ptp, (void *)&Fbapt, paramHeader->paramTableLength * sizeof(uint32));
                    status = NorSpi_Sfdp_parse4bait(&Fbapt, &NorSpiDevDefines, paramHeader->paramTableLength);
                    break;

                case NOR_SPI_SFDP_SECTOR_MAP_TABLE_ID:
                    status =
                        Nor_QspiReadSfdp(handle, ptp, (void *)&Smpt, paramHeader->paramTableLength * sizeof(uint32));
                    status = NorSpi_Sfdp_parseSmpt(&Smpt, &NorSpiDevDefines, paramHeader->paramTableLength);
                    break;

                case NOR_SPI_SFDP_SCCR_TABLE_ID:
                    status =
                        Nor_QspiReadSfdp(handle, ptp, (void *)&Sccr, paramHeader->paramTableLength * sizeof(uint32));
                    status = NorSpi_Sfdp_parseSccr(&Sccr, &NorSpiDevDefines, paramHeader->paramTableLength);
                    break;

                default:
                    /* Parsing not yet supported */
                    AppUtils_printf("\r\n");
                    char *paramName = NorSpi_Sfdp_getParameterTableName(paramID);
                    if (paramName != NULL_PTR)
                    {
                        AppUtils_printf("Parsing of %s table not yet supported. \r\n", paramName);
                    }
                    break;
            }
        }

        /* Print the final config */
        if (status == E_OK)
        {
            qspi_flash_diag_print_defines_json(&NorSpiDevDefines);
        }
    }

    return status;
}

void qspi_flash_diag_print_defines_json(NorSpi_SfdpGenericDefines *norSpiDefines)
{
    if (norSpiDefines != NULL_PTR)
    {
        AppUtils_printf("\r\n");

        AppUtils_printf("{\r\n");
        AppUtils_printf("\r\n");
        AppUtils_printf("\t\"flashSize\": \"%d\",\r\n", norSpiDefines->flashSize);
        AppUtils_printf("\t\"flashPageSize\": \"%d\",\r\n", norSpiDefines->pageSize);
        AppUtils_printf("\t\"flashManfId\": \"0x%02X\",\r\n", norSpiDefines->manfId);
        AppUtils_printf("\t\"flashDeviceId\": \"0x%04X\",\r\n", norSpiDefines->deviceId);
        AppUtils_printf("\t\"flashBlockSize\": \"%d\",\r\n", norSpiDefines->eraseCfg.blockSize);
        AppUtils_printf("\t\"flashSectorSize\": \"%d\",\r\n", norSpiDefines->eraseCfg.sectorSize);
        AppUtils_printf("\t\"cmdBlockErase3B\": \"0x%02X\",\r\n", norSpiDefines->eraseCfg.cmdBlockErase3B);
        AppUtils_printf("\t\"cmdBlockErase4B\": \"0x%02X\",\r\n", norSpiDefines->eraseCfg.cmdBlockErase4B);
        AppUtils_printf("\t\"cmdSectorErase3B\": \"0x%02X\",\r\n", norSpiDefines->eraseCfg.cmdSectorErase3B);
        AppUtils_printf("\t\"cmdSectorErase4B\": \"0x%02X\",\r\n", norSpiDefines->eraseCfg.cmdSectorErase4B);
        AppUtils_printf("\t\"protos\": {\r\n");

        FlashCfg_ProtoEnConfig *pCfg = &norSpiDefines->protos[FLASH_CFG_PROTO_1S_1S_1S];
        AppUtils_printf("\t\t\"p111\": {\r\n");
        AppUtils_printf("\t\t\t\"isDtr\": %s,\r\n", pCfg->isDtr ? "true" : "false");
        AppUtils_printf("\t\t\t\"cmdRd\": \"0x%02X\",\r\n", pCfg->cmdRd);
        AppUtils_printf("\t\t\t\"cmdWr\": \"0x%02X\",\r\n", pCfg->cmdWr);
        AppUtils_printf("\t\t\t\"modeClksCmd\": %d,\r\n", pCfg->modeClksCmd);
        AppUtils_printf("\t\t\t\"modeClksRd\": %d,\r\n", pCfg->modeClksRd);
        AppUtils_printf("\t\t\t\"dummyClksCmd\": %d,\r\n", pCfg->dummyClksCmd);
        AppUtils_printf("\t\t\t\"dummyClksRd\": %d,\r\n", pCfg->dummyClksRd);
        AppUtils_printf("\t\t\t\"enableType\": \"%d\",\r\n", pCfg->enableType);
        AppUtils_printf("\t\t\t\"enableSeq\": \"0x%02X\",\r\n", pCfg->enableSeq);
        AppUtils_printf("\t\t\t\"dummyCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\t\"protoCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\t\"strDtrCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t},\r\n");

        pCfg = &norSpiDefines->protos[FLASH_CFG_PROTO_1S_1S_2S];
        AppUtils_printf("\t\t\"p112\": {\r\n");
        AppUtils_printf("\t\t\t\"isDtr\": %s,\r\n", pCfg->isDtr ? "true" : "false");
        AppUtils_printf("\t\t\t\"cmdRd\": \"0x%02X\",\r\n", pCfg->cmdRd);
        AppUtils_printf("\t\t\t\"cmdWr\": \"0x%02X\",\r\n", pCfg->cmdWr);
        AppUtils_printf("\t\t\t\"modeClksCmd\": %d,\r\n", pCfg->modeClksCmd);
        AppUtils_printf("\t\t\t\"modeClksRd\": %d,\r\n", pCfg->modeClksRd);
        AppUtils_printf("\t\t\t\"dummyClksCmd\": %d,\r\n", pCfg->dummyClksCmd);
        AppUtils_printf("\t\t\t\"dummyClksRd\": %d,\r\n", pCfg->dummyClksRd);
        AppUtils_printf("\t\t\t\"enableType\": \"%d\",\r\n", pCfg->enableType);
        AppUtils_printf("\t\t\t\"enableSeq\": \"0x%02X\",\r\n", pCfg->enableSeq);
        AppUtils_printf("\t\t\t\"dummyCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\t\"protoCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\t\"strDtrCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t},\r\n");

        pCfg = &norSpiDefines->protos[FLASH_CFG_PROTO_1S_1S_4S];
        AppUtils_printf("\t\t\"p114\": {\r\n");
        AppUtils_printf("\t\t\t\"isDtr\": %s,\r\n", pCfg->isDtr ? "true" : "false");
        AppUtils_printf("\t\t\t\"cmdRd\": \"0x%02X\",\r\n", pCfg->cmdRd);
        AppUtils_printf("\t\t\t\"cmdWr\": \"0x%02X\",\r\n", pCfg->cmdWr);
        AppUtils_printf("\t\t\t\"modeClksCmd\": %d,\r\n", pCfg->modeClksCmd);
        AppUtils_printf("\t\t\t\"modeClksRd\": %d,\r\n", pCfg->modeClksRd);
        AppUtils_printf("\t\t\t\"dummyClksCmd\": %d,\r\n", pCfg->dummyClksCmd);
        AppUtils_printf("\t\t\t\"dummyClksRd\": %d,\r\n", pCfg->dummyClksRd);
        AppUtils_printf("\t\t\t\"enableType\": \"%d\",\r\n", pCfg->enableType);
        AppUtils_printf("\t\t\t\"enableSeq\": \"0x%02X\",\r\n", pCfg->enableSeq);
        AppUtils_printf("\t\t\t\"dummyCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\t\"protoCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\t\"strDtrCfg\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t},\r\n");

        /* Don't print the data for other protocols */
        AppUtils_printf("\t\t\"p118\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\"p444s\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\"p444d\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\"p888s\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\"p888d\": NULL_PTR,\r\n");
        AppUtils_printf("\t\t\"pCustom\": NULL_PTR\r\n");

        AppUtils_printf("\t},\r\n");
        AppUtils_printf("\t\"addrByteSupport\": \"%d\",\r\n", norSpiDefines->addrByteSupport);
        AppUtils_printf("\t\"fourByteAddrEnSeq\": \"0x%02X\",\r\n", norSpiDefines->fourByteAddrEnSeq);
        AppUtils_printf("\t\"resetType\": \"0x%02X\",\r\n", norSpiDefines->rstType);
        AppUtils_printf("\t\"cmdWren\": \"0x%02X\",\r\n", norSpiDefines->cmdWren);
        AppUtils_printf("\t\"cmdRdsr\": \"0x%02X\",\r\n", norSpiDefines->cmdRdsr);
        AppUtils_printf("\t\"srWip\": %d,\r\n", norSpiDefines->srWip);
        AppUtils_printf("\t\"srWel\": %d,\r\n", norSpiDefines->srWel);
        AppUtils_printf("\t\"cmdChipErase\": \"0x%02X\",\r\n", norSpiDefines->cmdChipErase);
        AppUtils_printf("\t\"flashDeviceBusyTimeout\": %d,\r\n", norSpiDefines->flashBusyTimeout);
        AppUtils_printf("\t\"flashPageProgTimeout\": %d\r\n", norSpiDefines->flashWriteTimeout);
        AppUtils_printf("}\r\n\r\n");
    }
}

uint32 QSPI_norFlashInit(QSPI_Handle handle)
{
    uint8 cmd;

    /* Reset the Flash */
    cmd = NOR_CMD_RSTEN;
    Nor_QspiCmdWrite(handle, cmd, FLS_QSPI_CMD_INVALID_ADDR, NULL_PTR, 0);

    cmd = NOR_CMD_RST;
    Nor_QspiCmdWrite(handle, cmd, FLS_QSPI_CMD_INVALID_ADDR, NULL_PTR, 0);

    Nor_QspiWaitReady(handle, Fls_Config_SFDP_Ptr->wrrwriteTimeout);
    if (handle != NULL_PTR)
    {
        QSPI_Object *object  = ((QSPI_Config *)handle)->object;
        object->writeCmd     = NOR_PAGE_PROG;
        object->readCmd      = NOR_CMD_SINGLE_READ;
        object->numAddrBytes = 3;
        object->numDummyBits = 0;
    }
    return 0;
}

static Std_ReturnType Fls_norWritesfdp(QSPI_Handle handle, uint32 offset, uint8 *buf, uint32 actualChunkSize)
{
    Std_ReturnType retVal = E_OK;
    if (actualChunkSize > 0U)
    {
        uint32           pageSize, chunkLen, actual;
        uint8            cmdWren = Fls_Config_SFDP_Ptr->cmdWren;
        QSPI_Transaction transaction;

        pageSize = Fls_Config_SFDP_Ptr->pageSize;
        chunkLen = pageSize;

        for (actual = 0; actual < actualChunkSize; actual += chunkLen)
        {
            retVal = Nor_QspiCmdWrite(handle, cmdWren, FLS_QSPI_CMD_INVALID_ADDR, NULL_PTR, 0);

            if (retVal == E_OK)
            {
                retVal = Nor_QspiWriteEnableLatched(handle, 2 * Fls_Config_SFDP_Ptr->wrrwriteTimeout);
            }

            if (retVal == E_OK)
            {
                /* Send Page Program command */
                if ((actualChunkSize - actual) < (pageSize))
                {
                    chunkLen = (actualChunkSize - actual);
                }
                else
                {
                    chunkLen = pageSize;
                }

                Fls_Qspi_TransactionInit(&transaction);
                transaction.addrOffset = offset;
                transaction.buf        = (void *)(buf + actual);
                transaction.count      = chunkLen;
                retVal                 = Fls_Qspi_WriteConfigMode(handle, &transaction);
            }

            if (retVal == E_OK)
            {
                retVal = Nor_QspiWaitReady(handle, Fls_Config_SFDP_Ptr->flashWriteTimeout);
            }

            if (retVal == E_OK)
            {
                offset += chunkLen;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }
    return retVal;
}

static Std_ReturnType Fls_norReadsfdp(QSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len)
{
    Std_ReturnType retVal = E_OK;
    if (retVal == E_OK)
    {
        if (len > 0U)
        {
            QSPI_Transaction transaction;

            Fls_Qspi_TransactionInit(&transaction);
            transaction.addrOffset = offset;
            transaction.buf        = (void *)buf;
            transaction.count      = len;
#if (FLS_MEM_MAP_MODE == (STD_ON))
            retVal = Fls_Qspi_ReadMemMapMode(handle, &transaction);
#else
            retVal = Fls_Qspi_ReadConfigMode(handle, &transaction);
#endif
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    return retVal;
}

static Std_ReturnType Fls_norErasesfdp(QSPI_Handle handle, uint32 offset)
{
    Std_ReturnType retVal = E_OK;

    retVal = Nor_QspiWaitReady(handle, Fls_Config_SFDP_Ptr->wrrwriteTimeout);
    if (retVal == E_OK)
    {
        retVal = Nor_QspiCmdWrite(handle, Fls_Config_SFDP_Ptr->cmdWren, FLS_QSPI_CMD_INVALID_ADDR, NULL, 0);
    }
    if (retVal == E_OK)
    {
        retVal = Nor_QspiWriteEnableLatched(handle, Fls_Config_SFDP_Ptr->wrrwriteTimeout);
    }
    if (retVal == E_OK)
    {
        retVal = Nor_QspiCmdWrite(handle, Fls_Config_SFDP_Ptr->eraseCfg.cmdBlockErase3B, offset, NULL, 0);
    }
    if (retVal == E_OK)
    {
        retVal = Nor_QspiWaitReady(handle, Fls_Config_SFDP_Ptr->wrrwriteTimeout);
    }

    return retVal;
}

void Drivers_qspiOpen(void)
{
    uint32         instCnt;
    Std_ReturnType status = E_OK;

    for (instCnt = 0U; instCnt < CONFIG_QSPI_NUM_INSTANCES; instCnt++)
    {
        Fls_QspiHandle[instCnt] = NULL_PTR;
    }

    /* Open all instances */
    for (instCnt = 0U; instCnt < CONFIG_QSPI_NUM_INSTANCES; instCnt++)
    {
        if (NULL_PTR == Fls_QspiOpen(instCnt))
        {
            AppUtils_printf("QSPI open failed for instance %d !!!\r\n", instCnt);
            status = E_NOT_OK;
            break;
        }
    }

    if (E_NOT_OK == status)
    {
        Drivers_qspiClose(); /* Exit gracefully */
    }

    return;
}

void Drivers_qspiClose(void)
{
    uint32 instCnt;

    /* Close all instances that are open */
    for (instCnt = 0U; instCnt < CONFIG_QSPI_NUM_INSTANCES; instCnt++)
    {
        if (Fls_QspiHandle[instCnt] != NULL_PTR)
        {
            Fls_QspiClose(Fls_QspiHandle[instCnt]);
            Fls_QspiHandle[instCnt] = NULL_PTR;
        }
    }

    return;
}

void SchM_Enter_Fls_FLS_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Fls_FLS_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
