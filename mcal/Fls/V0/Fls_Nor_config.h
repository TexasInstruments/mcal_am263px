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
 *  \file     Fls_Nor_config.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the FLS MCAL driver files.
 *
 */

#ifndef FLS_NOR_CONFIG_H_
#define FLS_NOR_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Platform_Types.h"
#include "Fls.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define FLASH_CFG_MAX_PROTO (10U)

typedef struct
{
    uint32 blockSize;
    uint32 sectorSize;
    uint8  cmdBlockErase3B;
    uint8  cmdBlockErase4B;
    uint8  cmdSectorErase3B;
    uint8  cmdSectorErase4B;
    uint8  cmdChipErase;

    uint8 rsvd[3];

} Flash_EraseConfig;

typedef struct
{
    uint8 cmd;
    uint8 numBytes;
    uint8 dummy4;
    uint8 dummy8;

} Flash_ReadIDConfig;

typedef struct
{
    uint8  isAddrReg;
    uint8  cmdRegRd;
    uint8  cmdRegWr;
    uint32 cfgReg;
    uint16 shift;
    uint16 mask;
    uint8  cfgRegBitP;

} Flash_RegEnConfig;

typedef struct
{
    uint32 protocol;
    uint16 isDtr;
    uint8  cmdRd;
    uint8  cmdWr;
    uint8  modeClksCmd;
    uint8  modeClksRd;
    uint16 dummyClksCmd;
    uint16 dummyClksRd;
    uint8  enableType;
    uint8  enableSeq;

    Flash_RegEnConfig protoCfg;
    Flash_RegEnConfig dummyCfg;
    Flash_RegEnConfig strDtrCfg;

} FlashCfg_ProtoEnableConfig;

typedef struct
{
    uint32                     flashSize;
    uint32                     pageSize;
    uint8                      manfId;
    uint16                     deviceId;
    uint8                      numSupportedEraseTypes;
    uint8                      cmdExtType;
    uint8                      byteOrder;
    uint8                      addrByteSupport;
    uint8                      fourByteAddrEnSeq;
    uint8                      fourByteAddrDisSeq;
    uint8                      dtrSupport;
    uint8                      deviceBusyType;
    Flash_EraseConfig          eraseCfg;
    uint8                      rstType;
    uint8                      addrnumBytes;
    uint8                      cmdWren;
    uint8                      cmdRdsr;
    uint8                      cmdRdsr2;
    uint8                      cmdWrsr;
    uint8                      srWip;
    uint8                      srWel;
    uint8                      cmdChipErase;
    Flash_ReadIDConfig         idCfg;
    FlashCfg_ProtoEnableConfig protos[FLASH_CFG_MAX_PROTO];
    uint8                      xspiWipRdCmd;
    uint32                     xspiWipReg;
    uint32                     xspiWipBit;
    uint32                     flashWriteTimeout;
    uint32                     wrrwriteTimeout;
    uint32                     flashBusyTimeout;
    uint32                     chipEraseTimeout;
    uint32                     flsMaxSectorErasetimeConvInUsec;
    uint32                     flsMaxBlockErasetimeConvInUsec;
    uint32                     flsMaxChipErasetimeConvInUsec;
    uint32                     flsMaxSectorReadWritetimeConvInUsec;
    uint32                     flsMaxBlockReadWritetimeConvInUsec;
    uint32                     flsMaxChipReadWritetimeConvInUsec;

} FlashConfigSfdp;

extern FlashConfigSfdp *fls_config_sfdp;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void Flash_readsfdp_init(void);

void Flash_sfdpParams_init(void);

#endif
