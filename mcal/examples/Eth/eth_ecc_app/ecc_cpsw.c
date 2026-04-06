/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2026 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>

#include <kernel/dpl/DebugP.h>
#include "sdlexample.h"
#include "sdl_ecc_soc.h"

#include "Eth_Cfg.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CPSW_CPPI_P0_CONTROL_REG                    (0x00021004U)
#define CPSW_CPPI_P0_CONTROL_REG_TX_ECC_ERR_EN_MASK (0x00004000U)
#define CPSW_CPPI_P0_CONTROL_REG_RX_ECC_ERR_EN_MASK (0x00008000U)
void setMacPortEcc(void)
{
    volatile uint32_t reg = 0U;
    reg                   = SDL_REG32_RD(SOC_MSS_CPSW_BASE + CPSW_CPPI_P0_CONTROL_REG);

    reg |= CPSW_CPPI_P0_CONTROL_REG_TX_ECC_ERR_EN_MASK;
    reg |= CPSW_CPPI_P0_CONTROL_REG_RX_ECC_ERR_EN_MASK;

    SDL_REG32_WR(SOC_MSS_CPSW_BASE + CPSW_CPPI_P0_CONTROL_REG, reg);
}

void clearMacPortEcc(void)
{
    volatile uint32_t reg = 0U;
    reg                   = SDL_REG32_RD(SOC_MSS_CPSW_BASE + CPSW_CPPI_P0_CONTROL_REG);

    reg &= ~CPSW_CPPI_P0_CONTROL_REG_TX_ECC_ERR_EN_MASK;
    reg &= ~CPSW_CPPI_P0_CONTROL_REG_RX_ECC_ERR_EN_MASK;

    SDL_REG32_WR(SOC_MSS_CPSW_BASE + CPSW_CPPI_P0_CONTROL_REG, reg);
}

void clear_cpsw_ecc_injection(SDL_ECC_MemSubType EccSubType)
{
    /* Clear any pending error injection */
    uint32_t          regValue    = 0x0;
    SDL_ecc_aggrRegs *eccAggrRegs = (SDL_ecc_aggrRegs *)SDL_CPSW0_ECC_U_BASE;  // base address of ECC aggregator

    /* Read the current register contents */
    SDL_ecc_aggrReadEccRamCtrlReg(eccAggrRegs, EccSubType, &regValue);

    /* Clear ERROR_ONCE, FORCE_N_ROW, FORCE_DED, and FORCE_SEC */
    regValue &= ((uint32_t)(~(SDL_ECC_RAM_CTRL_ERROR_ONCE_MASK | SDL_ECC_RAM_CTRL_FORCE_N_ROW_MASK |
                              SDL_ECC_RAM_CTRL_FORCE_DED_MASK | SDL_ECC_RAM_CTRL_FORCE_SEC_MASK)));

    /* Write back the updated value */
    SDL_ecc_aggrWriteEccRamCtrlReg(eccAggrRegs, EccSubType, regValue);
}

void ecc_cpsw_clearESM(void)
{
    SDL_ECC_MemType     eccmemtype;
    SDL_Ecc_AggrIntrSrc eccIntrSrc;
    SDL_ECC_ErrorInfo_t eccErrorInfo;

    SDL_ECC_getESMErrorInfo(sdlstats.esm.esmInst, sdlstats.esm.intSrc, &eccmemtype, &eccIntrSrc);
    SDL_ECC_getErrorInfo(eccmemtype, eccIntrSrc, &eccErrorInfo);

    sdlstats.ecc.eccMemtype   = eccmemtype;
    sdlstats.ecc.eccIntrSrc   = eccIntrSrc;
    sdlstats.ecc.eccErrorInfo = eccErrorInfo;

    if (eccErrorInfo.injectBitErrCnt != 0)
    {
        SDL_ECC_clearNIntrPending(eccmemtype, eccErrorInfo.memSubType, eccIntrSrc, SDL_ECC_AGGR_ERROR_SUBTYPE_INJECT,
                                  eccErrorInfo.injectBitErrCnt);
    }
    else
    {
        SDL_ECC_clearNIntrPending(eccmemtype, eccErrorInfo.memSubType, eccIntrSrc, SDL_ECC_AGGR_ERROR_SUBTYPE_NORMAL,
                                  eccErrorInfo.bitErrCnt);
    }

    SDL_ECC_ackIntr(eccmemtype, eccIntrSrc);

    clear_cpsw_ecc_injection(eccErrorInfo.memSubType);

    clearMacPortEcc();
}

uint32_t popcount32(uint32_t v)
{
    uint32_t c;

    c  = ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    c += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
    c += ((v >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;

    return c;
}

int32_t runECC2Bit_RAMInjectTest(bool isRx)
{
    SDL_ECC_InjectErrorConfig_t injectErrorConfig;
    SDL_ECC_InjectErrorType     errorType;
    SDL_ErrType_t               result;
    int32_t                     status = 0;
    SDL_ECC_MemSubType          EccSubType;

    uint32_t injectEccBitMask = 1 << 5;

    setMacPortEcc();

    /* Note the address is relative to start of ram */
    injectErrorConfig.pErrMem     = (uint32_t *)(0x0u);
    injectErrorConfig.flipBitMask = injectEccBitMask;
    injectErrorConfig.chkGrp      = 0x0;

    if (isRx == TRUE)
    {
        EccSubType = SDL_CPSW3GCSS_ECC_AGGR_CPSW_3GC_CORE_ECC_ECC_CTRL2_ECC_RAM_ID;
    }
    else
    {
        EccSubType = SDL_CPSW3GCSS_ECC_AGGR_CPSW_3GC_CORE_ECC_ECC_CTRL1_ECC_RAM_ID;
    }
    errorType = (popcount32(injectErrorConfig.flipBitMask) > 1) ? SDL_INJECT_ECC_ERROR_FORCING_2BIT_ONCE
                                                                : SDL_INJECT_ECC_ERROR_FORCING_1BIT_ONCE;

    result = SDL_ECC_injectError(SDL_CPSW3GCSS_ECC_AGGR, EccSubType, errorType, &injectErrorConfig);
    if (result != SDL_PASS)
    {
        status = -1;
    }

    return status;
}
