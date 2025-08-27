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
 *  \file     Fls_Nor_config.c
 *
 *  This file contains FLS MCAL driver internal functions for Board Nor QSPI
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Fls_Nor_config.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define FLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fls_MemMap.h"

FlashConfigSfdp  fls_config_sfdp_1;
FlashConfigSfdp *fls_config_sfdp = &fls_config_sfdp_1;

#define FLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

void Flash_readsfdp_init(void)
{
    fls_config_sfdp_1.flashSize                 = 16U * 1024U * 1024U;
    fls_config_sfdp_1.pageSize                  = 256U;
    fls_config_sfdp_1.cmdWren                   = 0x06U;
    fls_config_sfdp_1.manfId                    = 0x1U;
    fls_config_sfdp_1.deviceId                  = 0x2018U;
    fls_config_sfdp_1.cmdRdsr                   = 0x05U;
    fls_config_sfdp_1.cmdRdsr2                  = 0x35;
    fls_config_sfdp_1.addrnumBytes              = 3;
    fls_config_sfdp_1.cmdWrsr                   = 0x01U;
    fls_config_sfdp_1.flashWriteTimeout         = 400U;
    fls_config_sfdp_1.wrrwriteTimeout           = 600000U;
    fls_config_sfdp_1.eraseCfg.blockSize        = 64U * 1024U;
    fls_config_sfdp_1.eraseCfg.sectorSize       = 4U * 1024U;
    fls_config_sfdp_1.eraseCfg.cmdBlockErase3B  = 0xD8U;
    fls_config_sfdp_1.eraseCfg.cmdBlockErase4B  = 0xD8U;
    fls_config_sfdp_1.eraseCfg.cmdSectorErase3B = 0x20U;
    fls_config_sfdp_1.eraseCfg.cmdSectorErase4B = 0x20U;

    fls_config_sfdp_1.idCfg.cmd      = 0x9FU;
    fls_config_sfdp_1.idCfg.numBytes = 3U;
}
void Flash_sfdpParams_init(void)
{
    fls_config_sfdp_1.flashSize                           = 16U * 1024U * 1024U;
    fls_config_sfdp_1.pageSize                            = 256;
    fls_config_sfdp_1.manfId                              = 0x1U;
    fls_config_sfdp_1.deviceId                            = 0x2018U;
    fls_config_sfdp_1.numSupportedEraseTypes              = 0x00;
    fls_config_sfdp_1.cmdExtType                          = 0x02;
    fls_config_sfdp_1.byteOrder                           = 0xff;
    fls_config_sfdp_1.addrByteSupport                     = 0x00;
    fls_config_sfdp_1.fourByteAddrEnSeq                   = 0x00;
    fls_config_sfdp_1.fourByteAddrDisSeq                  = 0x00;
    fls_config_sfdp_1.dtrSupport                          = 0x00;
    fls_config_sfdp_1.deviceBusyType                      = 0x01;
    fls_config_sfdp_1.rstType                             = 0x10;
    fls_config_sfdp_1.addrnumBytes                        = 3;
    fls_config_sfdp_1.cmdWren                             = 0x06;
    fls_config_sfdp_1.cmdRdsr                             = 0x05;
    fls_config_sfdp_1.cmdRdsr2                            = 0x35;
    fls_config_sfdp_1.cmdWrsr                             = 0x01U;
    fls_config_sfdp_1.srWip                               = 0x00;
    fls_config_sfdp_1.srWel                               = 0x01;
    fls_config_sfdp_1.cmdChipErase                        = 0x60U;
    fls_config_sfdp_1.xspiWipRdCmd                        = 0x00;
    fls_config_sfdp_1.xspiWipReg                          = 0;
    fls_config_sfdp_1.xspiWipBit                          = 0;
    fls_config_sfdp_1.flashWriteTimeout                   = 400;
    fls_config_sfdp_1.wrrwriteTimeout                     = 600000U;
    fls_config_sfdp_1.flashBusyTimeout                    = 165U * 1000U * 1000U;
    fls_config_sfdp_1.chipEraseTimeout                    = 165U * 1000U * 1000U;
    fls_config_sfdp_1.flsMaxSectorErasetimeConvInUsec     = 1000U;
    fls_config_sfdp_1.flsMaxBlockErasetimeConvInUsec      = 10000U;
    fls_config_sfdp_1.flsMaxChipErasetimeConvInUsec       = 4000000U;
    fls_config_sfdp_1.flsMaxSectorReadWritetimeConvInUsec = 1000U;
    fls_config_sfdp_1.flsMaxBlockReadWritetimeConvInUsec  = 10000U;
    fls_config_sfdp_1.flsMaxChipReadWritetimeConvInUsec   = 4000000U;

    fls_config_sfdp_1.eraseCfg.blockSize        = 64U * 1024U;
    fls_config_sfdp_1.eraseCfg.sectorSize       = 4U * 1024U;
    fls_config_sfdp_1.eraseCfg.cmdBlockErase3B  = 216;
    fls_config_sfdp_1.eraseCfg.cmdBlockErase4B  = 216;
    fls_config_sfdp_1.eraseCfg.cmdSectorErase3B = 32;
    fls_config_sfdp_1.eraseCfg.cmdSectorErase4B = 32;

    fls_config_sfdp_1.idCfg.numBytes = 3U;
    fls_config_sfdp_1.idCfg.cmd      = 0x9FU;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].cmdRd        = 0x03;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].modeClksCmd  = 0x00;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].modeClksRd   = 0x00;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyClksRd  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].enableType   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_SINGLE].strDtrCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].cmdRd        = 0x3B;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].modeClksCmd  = 0x00;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].modeClksRd   = 0x00;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].enableType   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_DUAL].strDtrCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].cmdRd        = 107;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].modeClksCmd  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].modeClksRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].enableType   = 1;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_QSPI_RX_LINES_QUAD].strDtrCfg.shift      = 0;
}

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*******************************************************************************
 *  End of File: Fls_Nor_config.c
 ******************************************************************************/
