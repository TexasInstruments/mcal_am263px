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
 *  This file contains FLS MCAL driver internal functions for Board Nor OSPI
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
    fls_config_sfdp_1.flashSize = 33554432U;
    fls_config_sfdp_1.pageSize  = 256U;
    fls_config_sfdp_1.cmdWren   = 0x06U;
    fls_config_sfdp_1.manfId    = 0x9D;
#ifdef AM263PX_SIP_PACKAGE
    fls_config_sfdp_1.deviceId = 0x5A17;
#else
    fls_config_sfdp_1.deviceId = 0x5A19;
#endif
    fls_config_sfdp_1.cmdRdsr                   = 0x05U;
    fls_config_sfdp_1.cmdRdsr2                  = 0x35U;
    fls_config_sfdp_1.addrnumBytes              = 4;
    fls_config_sfdp_1.cmdWrsr                   = 0x01U;
    fls_config_sfdp_1.flashWriteTimeout         = 400U;
    fls_config_sfdp_1.wrrwriteTimeout           = 600000U;
    fls_config_sfdp_1.eraseCfg.blockSize        = 131072U;
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
    fls_config_sfdp_1.flashSize = 33554432U;
    fls_config_sfdp_1.pageSize  = 256;
    fls_config_sfdp_1.manfId    = 0x9D;
#ifdef AM263PX_SIP_PACKAGE
    fls_config_sfdp_1.deviceId = 0x5A17;
#else
    fls_config_sfdp_1.deviceId = 0x5A19;
#endif
    fls_config_sfdp_1.numSupportedEraseTypes              = 0x00;
    fls_config_sfdp_1.cmdExtType                          = 0x00;
    fls_config_sfdp_1.byteOrder                           = 0xff;
    fls_config_sfdp_1.addrByteSupport                     = 2;
    fls_config_sfdp_1.fourByteAddrEnSeq                   = 0xA1;
    fls_config_sfdp_1.fourByteAddrDisSeq                  = 0x00;
    fls_config_sfdp_1.dtrSupport                          = 0x00;
    fls_config_sfdp_1.deviceBusyType                      = 0x00;
    fls_config_sfdp_1.rstType                             = 48;
    fls_config_sfdp_1.addrnumBytes                        = 4;
    fls_config_sfdp_1.cmdWren                             = 0x06;
    fls_config_sfdp_1.cmdRdsr                             = 0x05;
    fls_config_sfdp_1.cmdRdsr2                            = 0x35;
    fls_config_sfdp_1.cmdWrsr                             = 0x01U;
    fls_config_sfdp_1.srWip                               = 0x01;
    fls_config_sfdp_1.srWel                               = 0x02;
    fls_config_sfdp_1.cmdChipErase                        = 0xC7;
    fls_config_sfdp_1.xspiWipRdCmd                        = 0x05;
    fls_config_sfdp_1.xspiWipReg                          = 0;
    fls_config_sfdp_1.xspiWipBit                          = 1;
    fls_config_sfdp_1.flashWriteTimeout                   = 120;
    fls_config_sfdp_1.wrrwriteTimeout                     = 500000U;
    fls_config_sfdp_1.flashBusyTimeout                    = 72000000;
    fls_config_sfdp_1.chipEraseTimeout                    = 110U * 1000U * 1000U;
    fls_config_sfdp_1.flsMaxSectorErasetimeConvInUsec     = 1000U;
    fls_config_sfdp_1.flsMaxBlockErasetimeConvInUsec      = 10000U;
    fls_config_sfdp_1.flsMaxChipErasetimeConvInUsec       = 4000000U;
    fls_config_sfdp_1.flsMaxSectorReadWritetimeConvInUsec = 1000U;
    fls_config_sfdp_1.flsMaxBlockReadWritetimeConvInUsec  = 10000U;
    fls_config_sfdp_1.flsMaxChipReadWritetimeConvInUsec   = 4000000U;

    fls_config_sfdp_1.eraseCfg.blockSize        = 131072U;
    fls_config_sfdp_1.eraseCfg.sectorSize       = 4096U;
    fls_config_sfdp_1.eraseCfg.cmdBlockErase3B  = 0xD8;
    fls_config_sfdp_1.eraseCfg.cmdBlockErase4B  = 0xDC;
    fls_config_sfdp_1.eraseCfg.cmdSectorErase3B = 0x20;
    fls_config_sfdp_1.eraseCfg.cmdSectorErase4B = 0x21;

    fls_config_sfdp_1.idCfg.numBytes = 3U;
    fls_config_sfdp_1.idCfg.cmd      = 0x9FU;
    fls_config_sfdp_1.idCfg.dummy4   = 0x00;
    fls_config_sfdp_1.idCfg.dummy8   = 0x08;

    /*1S-1S-1S Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].cmdRd        = 0x03;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].modeClksCmd  = 0x00;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].modeClksRd   = 0x00;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyClksRd  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].enableType   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_1S].strDtrCfg.shift      = 0;

    /*1S-1S-2S Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].cmdRd        = 0x3B;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].modeClksCmd  = 0x00;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].modeClksRd   = 0x00;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].enableType   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_2S].strDtrCfg.shift      = 0;

    /*1S-1S-4S Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].cmdRd        = 107;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].modeClksCmd  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].modeClksRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].enableType   = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_4S].strDtrCfg.shift      = 0;

    /*1S-1S-8S Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].cmdRd        = 0x7C;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].cmdWr        = 0x84;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].modeClksCmd  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].modeClksRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].enableType   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].enableSeq    = 0x00;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].protoCfg.isAddrReg  = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].protoCfg.cfgRegBitP = 231;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].protoCfg.cmdRegRd   = 133;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].protoCfg.cmdRegWr   = 129;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].protoCfg.mask       = 255;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyCfg.isAddrReg  = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyCfg.cfgReg     = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyCfg.cfgRegBitP = 16;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyCfg.cmdRegRd   = 133;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyCfg.cmdRegWr   = 129;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyCfg.mask       = 255;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.isAddrReg  = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.cmdRegRd   = 133;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.cmdRegWr   = 129;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.mask       = 255;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_1S_1S_8S].strDtrCfg.shift      = 255;

    /*4S-4S-4S Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].cmdRd        = 107;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].modeClksCmd  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].modeClksRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].enableType   = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4S_4S].strDtrCfg.shift      = 0;

    /*4S-4D-4D Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].cmdRd        = 107;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].modeClksCmd  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].modeClksRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].enableType   = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_4S_4D_4D].strDtrCfg.shift      = 0;

    /*8S-8S-8S Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].isDtr        = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].cmdRd        = 107;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].cmdWr        = 0x02;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].modeClksCmd  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].modeClksRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyClksCmd = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyClksRd  = 8;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].enableType   = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].protoCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].protoCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].protoCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].protoCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].protoCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.isAddrReg  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.cmdRegRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.cmdRegWr   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.mask       = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8S_8S_8S].strDtrCfg.shift      = 0;

    /*8D-8D-8D Mode */
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].isDtr        = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].cmdRd        = 124;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].cmdWr        = 132;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].modeClksCmd  = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].modeClksRd   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyClksCmd = 16;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyClksRd  = 16;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].enableType   = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].enableSeq    = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].protoCfg.isAddrReg  = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].protoCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].protoCfg.cfgRegBitP = 231;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].protoCfg.cmdRegRd   = 133;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].protoCfg.cmdRegWr   = 129;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].protoCfg.mask       = 255;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].protoCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyCfg.isAddrReg  = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyCfg.cfgReg     = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyCfg.cfgRegBitP = 16;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyCfg.cmdRegRd   = 133;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyCfg.cmdRegWr   = 129;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyCfg.mask       = 255;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].dummyCfg.shift      = 0;

    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.isAddrReg  = 1;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.cfgReg     = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.cfgRegBitP = 0;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.cmdRegRd   = 133;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.cmdRegWr   = 129;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.mask       = 255;
    fls_config_sfdp_1.protos[FLS_OSPI_RX_8D_8D_8D].strDtrCfg.shift      = 255;
}

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*******************************************************************************
 *  End of File: Fls_Nor_config.c
 ******************************************************************************/
