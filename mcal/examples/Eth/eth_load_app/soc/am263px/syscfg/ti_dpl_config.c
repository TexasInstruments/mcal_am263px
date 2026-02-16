/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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

/*
 * Auto generated file
 */
#include <stdio.h>
#include <drivers/soc.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_dpl_config.h"
#include "ti_drivers_config.h"

/* ----------- HwiP ----------- */
HwiP_Config gHwiConfig = {
    .intcBaseAddr = 0x50F00000u,
};

/* ----------- ClockP ----------- */
#define RTI0_CLOCK_SRC_MUX_ADDR (0x53208114u)
#define RTI0_CLOCK_SRC_WUCPUCLK (0x0u)
#define RTI0_BASE_ADDR          (0x52180000u)

ClockP_Config gClockConfig = {
    .timerBaseAddr       = RTI0_BASE_ADDR,
    .timerHwiIntNum      = 84,
    .timerInputClkHz     = 25000000,
    .timerInputPreScaler = 1,
    .usecPerTick         = 1000,
    .intrPriority        = 15,
};

/* ----------- DebugP ----------- */
void putchar_(char character)
{
    /* Output to UART console */
    DebugP_uartLogWriterPutChar(character);
}

#define RODATA_CFG_SECTION __attribute__((section(".rodata.cfg")))
/* ----------- CacheP ----------- */
const CacheP_Config gCacheConfig RODATA_CFG_SECTION = {
    .enable            = 1,
    .enableForceWrThru = 0,
};

/* ----------- MpuP_armv7 ----------- */
#define CONFIG_MPU_NUM_REGIONS (5u)

const MpuP_Config gMpuConfig RODATA_CFG_SECTION = {
    .numRegions             = CONFIG_MPU_NUM_REGIONS,
    .enableBackgroundRegion = 0,
    .enableMpu              = 1,
};

const MpuP_RegionConfig gMpuRegionConfig[CONFIG_MPU_NUM_REGIONS] RODATA_CFG_SECTION = {
    {
        .baseAddr = 0x0u,
        .size     = MpuP_RegionSize_2G,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 0,
                     .isSharable           = 1,
                     .isExecuteNever       = 1,
                     .tex                  = 0,
                     .accessPerm           = MpuP_AP_S_RW_U_R,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x0u,
        .size     = MpuP_RegionSize_32K,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 1,
                     .isBufferable         = 1,
                     .isSharable           = 0,
                     .isExecuteNever       = 0,
                     .tex                  = 1,
                     .accessPerm           = MpuP_AP_S_RW_U_R,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x80000u,
        .size     = MpuP_RegionSize_32K,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 1,
                     .isBufferable         = 1,
                     .isSharable           = 0,
                     .isExecuteNever       = 0,
                     .tex                  = 1,
                     .accessPerm           = MpuP_AP_S_RW_U_R,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x70000000u,
        .size     = MpuP_RegionSize_2M,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 1,
                     .isBufferable         = 1,
                     .isSharable           = 0,
                     .isExecuteNever       = 0,
                     .tex                  = 1,
                     .accessPerm           = MpuP_AP_S_RW_U_R,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x70180000u,
        .size     = MpuP_RegionSize_16K,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 0,
                     .isSharable           = 0,
                     .isExecuteNever       = 0,
                     .tex                  = 1,
                     .accessPerm           = MpuP_AP_ALL_RW,
                     .subregionDisableMask = 0x0u},
    },
};

#define BOOT_SECTION __attribute__((section(".text.boot"), do_not_share))

/* This function is called by _c_int00 */
void BOOT_SECTION __mpu_init()
{
    MpuP_init();

    CacheP_init();
}

void Dpl_init(void)
{
    /* initialize Hwi but keep interrupts disabled */
    HwiP_init();

    /* init debug log zones early */
    /* Debug log init */
    DebugP_logZoneEnable(DebugP_LOG_ZONE_ERROR);
    DebugP_logZoneEnable(DebugP_LOG_ZONE_WARN);
    /* UART console to use for reading input */
    DebugP_uartSetDrvIndex(CONFIG_UART0);

    /* set timer clock source */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, MSS_RCM_PARTITION0);
    *(volatile uint32_t*)(RTI0_CLOCK_SRC_MUX_ADDR) = RTI0_CLOCK_SRC_WUCPUCLK;
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, MSS_RCM_PARTITION0);
    /* initialize Clock */
    ClockP_init();

    /* Enable interrupt handling */
    HwiP_enable();
}

void Dpl_deinit(void)
{
}
