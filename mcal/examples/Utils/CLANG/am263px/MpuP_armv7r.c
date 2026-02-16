/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2018-2023 Texas Instruments Incorporated
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

#include <stdint.h>
#include <string.h>
#include "Std_Types.h"
#include "CacheP.h"
#include "MpuP_armv7r.h"
#include "app_utils.h"

/* Max possible regions in ARMv7-R CPU */
#define MpuP_MAX_REGIONS (16u)

/* APIs defined in MpuP_armv7r_asm.s */
void   MpuP_disableAsm(void);
void   MpuP_enableAsm(void);
uint32 MpuP_isEnableAsm(void);
void   MpuP_disableBRAsm(void);
void   MpuP_enableBRAsm(void);
void   MpuP_setRegionAsm(uint32 regionId, uint32 regionBaseAddr, uint32 sizeAndEnble, uint32 regionAttrs);

static uint32 MPU_SECTION MpuP_getAttrs(MpuP_RegionAttrs *region)
{
    uint32 regionAttrs = ((uint32)(region->isExecuteNever & (uint32)0x1) << (uint32)12) |
                         ((uint32)(region->accessPerm & (uint32)0x7) << (uint32)8) |
                         ((uint32)(region->tex & (uint32)0x7) << (uint32)3) |
                         ((uint32)(region->isSharable & (uint32)0x1) << (uint32)2) |
                         ((uint32)(region->isCacheable & (uint32)0x1) << (uint32)1) |
                         ((uint32)(region->isBufferable & (uint32)0x1) << (uint32)0);

    return regionAttrs;
}

void MPU_SECTION MpuP_RegionAttrs_init(MpuP_RegionAttrs *region)
{
    region->isExecuteNever       = 0;
    region->accessPerm           = (uint8)MpuP_AP_S_RW_U_R;
    region->tex                  = 0;
    region->isSharable           = 1;
    region->isCacheable          = 0;
    region->isBufferable         = 0;
    region->isEnable             = 0;
    region->subregionDisableMask = 0;
}

/* ----------- MpuP_armv7 ----------- */
#define CONFIG_MPU_NUM_REGIONS (13u)

const MpuP_Config gMpuConfig = {
    .numRegions             = CONFIG_MPU_NUM_REGIONS,
    .enableBackgroundRegion = 0,
    .enableMpu              = 1,
};

const MpuP_RegionConfig gMpuRegionConfig[CONFIG_MPU_NUM_REGIONS] = {
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
    /* MCSPI Register Space to be Strongly Ordered */
    {
        .baseAddr = 0x52200000u,
        .size     = MpuP_RegionSize_32K,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 1,
                     .isSharable           = 1,
                     .isExecuteNever       = 0,
                     .tex                  = 0,
                     .accessPerm           = MpuP_AP_ALL_RW,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x52201000u,
        .size     = MpuP_RegionSize_32K,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 1,
                     .isSharable           = 1,
                     .isExecuteNever       = 0,
                     .tex                  = 0,
                     .accessPerm           = MpuP_AP_ALL_RW,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x70000000u,
        .size     = MpuP_RegionSize_1M,
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
        .baseAddr = 0x70100000u,
        .size     = MpuP_RegionSize_512K,
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
        .size     = MpuP_RegionSize_512K,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 1,
                     .isSharable           = 0,
                     .isExecuteNever       = 0,
                     .tex                  = 1,
                     .accessPerm           = MpuP_AP_S_RW_U_R,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x70200000u,
        .size     = MpuP_RegionSize_512K,
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
        .baseAddr = 0x70280000u,
        .size     = MpuP_RegionSize_512K,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 0,
                     .isSharable           = 0,
                     .isExecuteNever       = 0,
                     .tex                  = 1,
                     .accessPerm           = MpuP_AP_ALL_RW,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x50240000u,
        .size     = MpuP_RegionSize_1M,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 0,
                     .isSharable           = 0,
                     .isExecuteNever       = 1,
                     .tex                  = 2,
                     .accessPerm           = MpuP_AP_ALL_RW,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0x60100000u,
        .size     = MpuP_RegionSize_1M,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 1,
                     .isBufferable         = 1,
                     .isSharable           = 0,
                     .isExecuteNever       = 0,
                     .tex                  = 1,
                     .accessPerm           = MpuP_AP_ALL_RW,
                     .subregionDisableMask = 0x0u},
    },
    {
        .baseAddr = 0xCE000000u,
        .size     = MpuP_RegionSize_32M,
        .attrs    = {.isEnable             = 1,
                     .isCacheable          = 0,
                     .isBufferable         = 0,
                     .isSharable           = 1,
                     .isExecuteNever       = 0,
                     .tex                  = 0,
                     .accessPerm           = MpuP_AP_ALL_RW,
                     .subregionDisableMask = 0x0u},
    },
};

uint32 MPU_SECTION MpuP_isEnable(void)
{
    return MpuP_isEnableAsm();
}

void MPU_SECTION MpuP_setRegion(uint32 regionNum, void *addr, uint32 size, MpuP_RegionAttrs *attrs)
{
    uint32 baseAddress, sizeAndEnable, regionAttrs;
    uint32 enabled;
    uint32 value = size;

    assert(regionNum < MpuP_MAX_REGIONS);

    /* size 5b field */
    value = (value & (uint32)0x1F);

    /* If N is the value in size field, the region size is 2N+1 bytes. */
    sizeAndEnable = ((uint32)(attrs->subregionDisableMask & (uint32)0xFF) << (uint32)8) |
                    ((uint32)(value & (uint32)0x1F) << (uint32)1) |
                    ((uint32)(attrs->isEnable & (uint32)0x1) << (uint32)0);

    /* align base address to region size */
    baseAddress = ((uint32)addr & ~((1U << ((uint64)value + 1U)) - 1U));

    /* get region attribute mask */
    regionAttrs = MpuP_getAttrs(attrs);

    enabled = MpuP_isEnable();

    /* disable the MPU (if already disabled, does nothing) */
    MpuP_disable();

    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();

    MpuP_setRegionAsm(regionNum, baseAddress, sizeAndEnable, regionAttrs);

    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();

    if (enabled != 0U)
    {
        MpuP_enable();
    }
}

void MPU_SECTION MpuP_enable(void)
{
    if (MpuP_isEnable() == 0U)
    {
        uint32 type;

        AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
        /* get the current enabled bits */
        type = Mcal_CacheP_getEnabled();

        assert((type & Mcal_CacheP_TYPE_ALL) == 0);

        MpuP_enableAsm();

        __asm__ __volatile__(
            " dsb"
            "\n\t"
            :
            :
            : "memory");
        __asm__ __volatile__(
            " isb"
            "\n\t"
            :
            :
            : "memory");

        AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
    }
}

void MPU_SECTION MpuP_disable(void)
{
    if (MpuP_isEnable() != 0U)
    {
        uint32 type;

        AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();

        /* get the current enabled bits */
        type = Mcal_CacheP_getEnabled();

        /* disable all enabled caches */
        Mcal_CacheP_disable(type);

        __asm__ __volatile__(
            " dsb"
            "\n\t"
            :
            :
            : "memory");

        MpuP_disableAsm();

        /* set cache back to initial settings */
        Mcal_CacheP_enable(type);

        AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
    }
}

void MPU_SECTION MpuP_init(void)
{
    uint32 i;

    if (MpuP_isEnable() != 0U)
    {
        MpuP_disable();
    }

    MpuP_disableBRAsm();

    assert(gMpuConfig.numRegions < MpuP_MAX_REGIONS);

    /*
     * Initialize MPU regions
     */
    for (i = 0; i < gMpuConfig.numRegions; i++)
    {
        MpuP_setRegion(i, (void *)gMpuRegionConfig[i].baseAddr, gMpuRegionConfig[i].size,
                       (MpuP_RegionAttrs *)&gMpuRegionConfig[i].attrs);
    }

    if (gMpuConfig.enableBackgroundRegion != 0U)
    {
        MpuP_enableBRAsm();
    }

    if (gMpuConfig.enableMpu != 0U)
    {
        MpuP_enable();
    }
}
