/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 * This example performs OSPI transfer test using polling mode.
 *
 * The JEDEC ID of flash is read and printed out. A block
 * of flash memory is erased by sending erase command and
 * data is  written into the flash from a prefilled buffer.
 * Then, data is read back from it and validated.
 * If the equality test is successful, the test was successful.
 */
#include "Fls_NOR_SFDP.h"
#include "Fls_Nor_config.h"
#include <string.h>
#include <stdlib.h>
#include "Fls_Ospi.h"
#include "Fls_Brd_Nor.h"
#include "Fls_Startup.h"
#include "Det.h"
// OSPI_Object Fls_OspiObjects[1];
// OSPI_Config Fls_OspiConfig[1];

extern FlashConfigSfdp *fls_config_sfdp;

/* The source buffer used for transfer */
uint8 OspiTxBuf[APP_OSPI_DATA_SIZE];
/* Read buffer MUST be cache line aligned when using DMA */
uint8 OspiRxBuf[APP_OSPI_DATA_SIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));

NorSpi_SfdpHeader       SfdpHeader;
NorSpi_SfdpParamHeader  ParamHeaders[NOR_SPI_SFDP_NPH_MAX];
NorSpi_SfdpParamHeader *BfptHeader;

NorSpi_SfdpBasicFlashParamTable      Bfpt;
NorSpi_SfdpSectorMapParamTable       Smpt;
NorSpi_SfdpSCCRParamTable            Sccr;
NorSpi_SfdpProfile1ParamTable        Xpt1;
NorSpi_Sfdp4ByteAddressingParamTable Fbapt;

NorSpi_SfdpGenericDefines NorSpiDevDefines;

void                  ospi_flash_diag_test_fill_buffers(void);
uint32                ospi_flash_diag_test_compare_buffers(void);
uint32                ospi_flash_diag_print_sfdp(OSPI_Handle handle);
void                  ospi_flash_diag_print_defines_json(NorSpi_SfdpGenericDefines *norSpiDefines);
static Std_ReturnType Fls_norReadsfdp(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len);
static Std_ReturnType Fls_norWritesfdp(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len);
uint32                OSPI_norFlashInit(OSPI_Handle handle);
void                  ospi_flash_diag(void *args);

int main(void)
{
    AppUtils_defaultInit();
    FlsApp_PlatformInit();
    Flash_readsfdp_init();
    ospi_flash_diag(NULL_PTR);
    return 0;
}

void ospi_flash_diag(void *args)
{
    Std_ReturnType status = E_OK;
    uint32         offset;

    AppUtils_printf("[OSPI Flash Diagnostic Test] Starting ...\r\n");

    /* Get OSPI Handle*/
    OSPI_Handle ospiHandle                      = NULL_PTR;
    Fls_DrvObj.chipSelect                       = OSPI_CS0;
    Fls_DrvObj.decChipSelect                    = OSPI_DECODER_SELECT4;
    Fls_DrvObj.frmFmt                           = OSPI_FF_POL0_PHA0;
    Fls_DrvObj.baudRateDiv                      = 2;
    Fls_DrvObj.Fls_Mode                         = FLASH_CFG_PROTO_1S_1S_1S;
    Fls_DrvObj.sectorList[0].sectorStartaddress = FLS_BASE_ADDRESS;
    ospiHandle                                  = Fls_Ospi_Open();

    /* Zero init the dev defines struct */
    memset(&NorSpiDevDefines, 0, sizeof(NorSpiDevDefines));

    /* Initialize the flash device in 1s1s1s mode */
    status = Fls_set111mode(ospiHandle, 0x03, 0x02, 0xD8);

    /* Read ID */
    status = Nor_OspiReadId(ospiHandle);

    if (E_OK == status)
    {
        NorSpiDevDefines.manfId   = fls_config_sfdp->manfId;
        NorSpiDevDefines.deviceId = fls_config_sfdp->deviceId;

        AppUtils_printf("[OSPI Flash Diagnostic Test] Flash Manufacturer ID : 0x%X\r\n", NorSpiDevDefines.manfId);
        AppUtils_printf("[OSPI Flash Diagnostic Test] Flash Device ID       : 0x%X\r\n", NorSpiDevDefines.deviceId);
    }
    /* Fill buffers with known data,
     * find block number from offset,
     * erase block, write the data, read back from a specific offset
     * and finally compare the results.
     */

    if (E_OK == status)
    {
        offset = APP_OSPI_FLASH_OFFSET;
        ospi_flash_diag_test_fill_buffers();
        AppUtils_printf("[OSPI Flash Diagnostic Test] Executing Flash Erase on first block...\r\n");
        status = Fls_norBlockErase(ospiHandle, offset);

        if (status == E_OK)
        {
            AppUtils_printf("[OSPI Flash Diagnostic Test] Done !!!\r\n");
        }
        else
        {
            AppUtils_printf("[OSPI Flash Diagnostic Test] Erase Failed !!!\r\n");
        }
        AppUtils_printf("[OSPI Flash Diagnostic Test] Performing Write-Read Test...\r\n");

        status = Nor_OspiWrite(ospiHandle, offset, OspiTxBuf, APP_OSPI_DATA_SIZE);
        if (E_OK == status)
        {
            status = Nor_OspiRead(ospiHandle, offset, OspiRxBuf, APP_OSPI_DATA_SIZE);
        }

        status |= ospi_flash_diag_test_compare_buffers();

        if (E_OK == status)
        {
            AppUtils_printf("[OSPI Flash Diagnostic Test] Write-Read Test Passed!\r\n");
        }
    }

    if (E_OK == status)
    {
        /* Read the SFDP table and print flash details */
        status = ospi_flash_diag_print_sfdp(ospiHandle);
    }

    if (E_OK == status)
    {
        AppUtils_printf("All tests have passed!!\r\n");
    }
    else
    {
        AppUtils_printf("Some tests have failed!!\r\n");
    }
}

void ospi_flash_diag_test_fill_buffers(void)
{
    uint32 i;
    for (i = 0U; i < APP_OSPI_DATA_SIZE; i++)
    {
        OspiTxBuf[i] = i;
        OspiRxBuf[i] = 0U;
    }
}

uint32 ospi_flash_diag_test_compare_buffers(void)
{
    Std_ReturnType status = E_OK;
    uint32         i;

    for (i = 0U; i < APP_OSPI_DATA_SIZE; i++)
    {
        if (OspiTxBuf[i] != OspiRxBuf[i])
        {
            status = E_NOT_OK;
            AppUtils_printf("OSPI read data mismatch !!!\r\n");
            break;
        }
    }
    return status;
}

uint32 ospi_flash_diag_print_sfdp(OSPI_Handle handle)
{
    Std_ReturnType status = E_OK;
    uint32         ptp    = 0xFFFFFFFFU;

    /* Read the SFDP header */
    status = Nor_FlsReadSfdp(handle, NOR_SPI_SFDP_HEADER_START_OFFSET, (void *)&SfdpHeader, sizeof(NorSpi_SfdpHeader));

    BfptHeader = &SfdpHeader.firstParamHeader;

    /* Check if the signature is read correctly */
    if (SfdpHeader.sfdpHeader.signature != NOR_SPI_SFDP_SIGNATURE)
    {
        AppUtils_printf(
            "[OSPI Flash Diagnostic Test] Error in reading SFDP Table or SFDP not supported by "
            "Flash !!!\r\n");
    }
    else
    {
        /* Print SFDP basic information */
        AppUtils_printf("[OSPI Flash Diagnostic Test] SFDP Information : \r\n");
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
            status = Nor_FlsReadSfdp(handle, NOR_SPI_SFDP_SECOND_PARAM_HEADER_OFFSET, (void *)&ParamHeaders,
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

        status = Nor_FlsReadSfdp(handle, ptp, (void *)&Bfpt, BfptHeader->paramTableLength * sizeof(uint32));

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
                        Nor_FlsReadSfdp(handle, ptp, (void *)&Xpt1, paramHeader->paramTableLength * sizeof(uint32));
                    status = NorSpi_Sfdp_parseXpt1(&Xpt1, &NorSpiDevDefines, paramHeader->paramTableLength);
                    break;

                case NOR_SPI_SFDP_4BYTE_ADDR_INSTR_TABLE_ID:
                    status =
                        Nor_FlsReadSfdp(handle, ptp, (void *)&Fbapt, paramHeader->paramTableLength * sizeof(uint32));
                    status = NorSpi_Sfdp_parse4bait(&Fbapt, &NorSpiDevDefines, paramHeader->paramTableLength);
                    break;

                case NOR_SPI_SFDP_SECTOR_MAP_TABLE_ID:
                    status =
                        Nor_FlsReadSfdp(handle, ptp, (void *)&Smpt, paramHeader->paramTableLength * sizeof(uint32));
                    status = NorSpi_Sfdp_parseSmpt(&Smpt, &NorSpiDevDefines, paramHeader->paramTableLength);
                    break;

                case NOR_SPI_SFDP_SCCR_TABLE_ID:
                    status =
                        Nor_FlsReadSfdp(handle, ptp, (void *)&Sccr, paramHeader->paramTableLength * sizeof(uint32));
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
            ospi_flash_diag_print_defines_json(&NorSpiDevDefines);
        }
    }

    return status;
}

void ospi_flash_diag_print_defines_json(NorSpi_SfdpGenericDefines *norSpiDefines)
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

        uint32 protos[] = {
            FLASH_CFG_PROTO_1S_1S_1S, FLASH_CFG_PROTO_1S_1S_2S, FLASH_CFG_PROTO_1S_1S_4S, FLASH_CFG_PROTO_1S_1S_8S,
            FLASH_CFG_PROTO_4S_4S_4S, FLASH_CFG_PROTO_4S_4D_4D, FLASH_CFG_PROTO_8S_8S_8S, FLASH_CFG_PROTO_8D_8D_8D,
        };

        char *protos_list[] = {
            "p111", "p112", "p114", "p118", "p444s", "p444d", "p888s", "p888d",
        };

        for (uint32 i = 0; i < 8; i++)
        {
            FlashCfg_ProtoEnConfig *pCfg = &norSpiDefines->protos[protos[i]];
            if (pCfg->cmdRd != 0)
            {
                AppUtils_printf("\t\t\"%s\": {\r\n", protos_list[i]);
                AppUtils_printf("\t\t\t\"isDtr\": %s,\r\n", pCfg->isDtr ? "true" : "false");
                AppUtils_printf("\t\t\t\"cmdRd\": \"0x%02X\",\r\n", pCfg->cmdRd);
                AppUtils_printf("\t\t\t\"cmdWr\": \"0x%02X\",\r\n", pCfg->cmdWr);
                AppUtils_printf("\t\t\t\"modeClksCmd\": %d,\r\n", pCfg->modeClksCmd);
                AppUtils_printf("\t\t\t\"modeClksRd\": %d,\r\n", pCfg->modeClksRd);
                AppUtils_printf("\t\t\t\"dummyClksCmd\": %d,\r\n", pCfg->dummyClksCmd);
                AppUtils_printf("\t\t\t\"dummyClksRd\": %d,\r\n", pCfg->dummyClksRd);
                AppUtils_printf("\t\t\t\"enableType\": \"%d\",\r\n", pCfg->enableType);
                AppUtils_printf("\t\t\t\"enableSeq\": \"0x%02X\",\r\n", pCfg->enableSeq);

                if ((protos[i] == FLASH_CFG_PROTO_4S_4S_4S) || (protos[i] == FLASH_CFG_PROTO_4S_4D_4D) ||
                    (protos[i] == FLASH_CFG_PROTO_8S_8S_8S) || (protos[i] == FLASH_CFG_PROTO_8D_8D_8D))
                {
                    AppUtils_printf("\t\t\t\"dummyCfg\": {\r\n");
                    AppUtils_printf("\t\t\t\t\"isAddrReg\": %s,\r\n", pCfg->dummyCfg.isAddrReg ? "true" : "false");
                    AppUtils_printf("\t\t\t\t\"cmdRegRd\":\"0x%02X\",\r\n", pCfg->dummyCfg.cmdRegRd);
                    AppUtils_printf("\t\t\t\t\"cmdRegWr\":\"0x%02X\",\r\n", pCfg->dummyCfg.cmdRegWr);
                    AppUtils_printf("\t\t\t\t\"cfgReg\":\"0x%08X\",\r\n", pCfg->dummyCfg.cfgReg);
                    AppUtils_printf("\t\t\t\t\"shift\":%d,\r\n", pCfg->dummyCfg.shift);
                    AppUtils_printf("\t\t\t\t\"mask\":\"0x%02X\",\r\n", pCfg->dummyCfg.mask);
                    AppUtils_printf("\t\t\t\t\"bitP\":%d\r\n", pCfg->dummyCfg.cfgRegBitP);
                    AppUtils_printf("\t\t\t},\r\n");
                    AppUtils_printf("\t\t\t\"protoCfg\": {\r\n");
                    AppUtils_printf("\t\t\t\t\"isAddrReg\": %s,\r\n", pCfg->protoCfg.isAddrReg ? "true" : "false");
                    AppUtils_printf("\t\t\t\t\"cmdRegRd\": \"0x%02X\",\r\n", pCfg->protoCfg.cmdRegRd);
                    AppUtils_printf("\t\t\t\t\"cmdRegWr\": \"0x%02X\",\r\n", pCfg->protoCfg.cmdRegWr);
                    AppUtils_printf("\t\t\t\t\"cfgReg\": \"0x%08X\",\r\n", pCfg->protoCfg.cfgReg);
                    AppUtils_printf("\t\t\t\t\"shift\": %d,\r\n", pCfg->protoCfg.shift);
                    AppUtils_printf("\t\t\t\t\"mask\": \"0x%02X\",\r\n", pCfg->protoCfg.mask);
                    AppUtils_printf("\t\t\t\t\"bitP\": %d\r\n", pCfg->protoCfg.shift);
                    AppUtils_printf("\t\t\t},\r\n");
                    AppUtils_printf("\t\t\t\"strDtrCfg\": {\r\n");
                    AppUtils_printf("\t\t\t\t\"isAddrReg\": %s,\r\n", pCfg->strDtrCfg.isAddrReg ? "true" : "false");
                    AppUtils_printf("\t\t\t\t\"cmdRegRd\": \"0x%02X\",\r\n", pCfg->strDtrCfg.cmdRegRd);
                    AppUtils_printf("\t\t\t\t\"cmdRegWr\": \"0x%02X\",\r\n", pCfg->strDtrCfg.cmdRegWr);
                    AppUtils_printf("\t\t\t\t\"cfgReg\": \"0x%08X\",\r\n", pCfg->strDtrCfg.cfgReg);
                    AppUtils_printf("\t\t\t\t\"shift\": %d,\r\n", pCfg->strDtrCfg.shift);
                    AppUtils_printf("\t\t\t\t\"mask\": \"0x%02X\",\r\n", pCfg->strDtrCfg.mask);
                    AppUtils_printf("\t\t\t\t\"bitP\": %d\r\n", pCfg->strDtrCfg.shift);
                    AppUtils_printf("\t\t\t}\r\n");
                }
                else
                {
                    AppUtils_printf("\t\t\t\"dummyCfg\": null,\r\n");
                    AppUtils_printf("\t\t\t\"protoCfg\": null,\r\n");
                    AppUtils_printf("\t\t\t\"strDtrCfg\": null\r\n");
                }
                AppUtils_printf("\t\t},\r\n");
            }
            else
            {
                AppUtils_printf("\t\t\"%s\": null,\r\n", protos_list[i]);
            }
        }

        AppUtils_printf("\t},\r\n");
        AppUtils_printf("\t\"addrByteSupport\": \"%d\",\r\n", norSpiDefines->addrByteSupport);
        AppUtils_printf("\t\"fourByteAddrEnSeq\": \"0x%02X\",\r\n", norSpiDefines->fourByteAddrEnSeq);
        AppUtils_printf("\t\"cmdExtType\": \"%s\",\r\n", norSpiDefines->cmdExtType == 0
                                                             ? "REPEAT"
                                                             : (norSpiDefines->cmdExtType == 1 ? "INVERSE" : "NONE"));
        AppUtils_printf("\t\"resetType\": \"0x%02X\",\r\n", norSpiDefines->rstType);
        AppUtils_printf("\t\"deviceBusyType\": \"%d\",\r\n", norSpiDefines->deviceBusyType);
        AppUtils_printf("\t\"cmdWren\": \"0x%02X\",\r\n", norSpiDefines->cmdWren);
        AppUtils_printf("\t\"cmdRdsr\": \"0x%02X\",\r\n", norSpiDefines->cmdRdsr);
        AppUtils_printf("\t\"srWip\":  %d,\r\n", norSpiDefines->srWip);
        AppUtils_printf("\t\"srWel\":  %d,\r\n", norSpiDefines->srWel);
        AppUtils_printf("\t\"cmdChipErase\": \"0x%02X\",\r\n", norSpiDefines->cmdChipErase);
        AppUtils_printf("\t\"rdIdSettings\": {\r\n");
        AppUtils_printf("\t\t\"cmd\": \"0x%02X\",\r\n", norSpiDefines->idCfg.cmd);
        AppUtils_printf("\t\t\"numBytes\": %d,\r\n", norSpiDefines->idCfg.numBytes);
        AppUtils_printf("\t\t\"dummy4\": %d,\r\n", norSpiDefines->idCfg.dummy4);
        AppUtils_printf("\t\t\"dummy8\": %d\r\n", norSpiDefines->idCfg.dummy8);
        AppUtils_printf("\t},\r\n");
        AppUtils_printf("\t\"xspiWipRdCmd\": \"0x%02X\",\r\n", norSpiDefines->xspiWipRdCmd);
        AppUtils_printf("\t\"xspiWipReg\": \"0x%08X\",\r\n", norSpiDefines->xspiWipReg);
        AppUtils_printf("\t\"xspiWipBit\": %d,\r\n", norSpiDefines->xspiWipBit);
        AppUtils_printf("\t\"flashDeviceBusyTimeout\": %d,\r\n", norSpiDefines->flashBusyTimeout);
        AppUtils_printf("\t\"flashPageProgTimeout\": %d\r\n", norSpiDefines->flashWriteTimeout);
        AppUtils_printf("}\r\n\r\n");
    }
}
