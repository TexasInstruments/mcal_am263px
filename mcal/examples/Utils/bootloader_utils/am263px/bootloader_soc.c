/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2021-2024 Texas Instruments Incorporated
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

#include <string.h>
#include <bootloader.h>
#include <bootloader_priv.h>
#include <bootloader_soc.h>
#include <mcal_hw_soc_baseaddress.h>
// #include <security_common/drivers/hsmclient/hsmclient.h>

#define BOOTLOADER_R5SS_FREQ_200MHz (1U)

// extern SecureBoot_Stream_t mcal_hw_soc_baseaddress.h[];
// extern HsmClient_t gHSMClient ;

uint32_t gStreamId = 0;

Bootloader_resMemSections gResMemSection = {
    .numSections            = 1,
    .memSection[0].memStart = 0x70002000,
    .memSection[0].memEnd   = 0x70040000,
};

Bootloader_CoreBootInfo gCoreBootInfo[] = {
    {
        .defaultClockHz = (uint32_t)(400 * 1000000),
        .coreName       = "r5f0-0",
    },

    {
        .defaultClockHz = (uint32_t)(400 * 1000000),
        .coreName       = "r5f0-1",
    },
    {
        .defaultClockHz = (uint32_t)(400 * 1000000),
        .coreName       = "r5f1-0",
    },

    {
        .defaultClockHz = (uint32_t)(400 * 1000000),
        .coreName       = "r5f1-1",
    },
};

/* list the R5F cluster where this bootloader runs, this is fixed to R5FSS0-0, R5FSS0-1 in this SOC */
uint32_t gBootloaderSelfCpuList[] = {
    MCAL_CSL_CORE_ID_R5FSS0_0,
    BOOTLOADER_INVALID_ID,
};

Bootloader_CoreAddrTranslateInfo gAddrTranslateInfo[] = {
    /* MCAL_CSL_CORE_ID_R5FSS0_0 */
    {
        .numRegions = 2,
        .addrRegionInfo =
            {
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMA_RAM_BASE,
                    .socAddr      = (uint32_t)CSL_MSS_TCMA_RAM_BASE,
                    .regionSize   = CSL_MSS_TCMA_RAM_SIZE * 2U,
                },
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMB_RAM_BASE,
                    .socAddr      = (uint32_t)CSL_MSS_TCMB_RAM_BASE,
                    .regionSize   = CSL_MSS_TCMB_RAM_SIZE * 2U,
                },
            },
    },

    /* MCAL_CSL_CORE_ID_R5FSS0_1 */
    {
        .numRegions = 2,
        .addrRegionInfo =
            {
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMA_RAM_BASE,
                    .socAddr      = (uint32_t)CSL_MSS_TCMA_RAM_BASE + CSL_MSS_TCMA_RAM_SIZE,
                    .regionSize   = (uint32_t)CSL_MSS_TCMA_RAM_SIZE,
                },
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMB_RAM_BASE,
                    .socAddr      = (uint32_t)CSL_MSS_TCMB_RAM_BASE + CSL_MSS_TCMB_RAM_SIZE,
                    .regionSize   = (uint32_t)CSL_MSS_TCMB_RAM_SIZE,
                },
            },
    },

    /* MCAL_CSL_CORE_ID_R5FSS1_0 */
    {
        .numRegions = 2,
        .addrRegionInfo =
            {
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMA_RAM_BASE,
                    .socAddr      = (uint32_t)MCAL_CSL_R5SS1_CORE0_TCMA_U_BASE,
                    .regionSize   = (uint32_t)CSL_MSS_TCMA_RAM_SIZE * 2U,
                },
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMB_RAM_BASE,
                    .socAddr      = (uint32_t)MCAL_CSL_R5SS1_CORE0_TCMB_U_BASE,
                    .regionSize   = (uint32_t)CSL_MSS_TCMB_RAM_SIZE * 2U,
                },
            },
    },

    /* MCAL_CSL_CORE_ID_R5FSS1_1 */
    {
        .numRegions = 2,
        .addrRegionInfo =
            {
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMA_RAM_BASE,
                    .socAddr      = (uint32_t)MCAL_CSL_R5SS1_CORE1_TCMA_U_BASE,
                    .regionSize   = (uint32_t)CSL_MSS_TCMA_RAM_SIZE,
                },
                {
                    .cpuLocalAddr = (uint32_t)CSL_MSS_TCMB_RAM_BASE,
                    .socAddr      = (uint32_t)MCAL_CSL_R5SS1_CORE1_TCMB_U_BASE,
                    .regionSize   = (uint32_t)CSL_MSS_TCMB_RAM_SIZE,
                },
            },
    },
};

CSL_top_ctrlRegs *ptrTopCtrlRegs = (CSL_top_ctrlRegs *)MCAL_CSL_TOP_CTRL_U_BASE;

volatile uint32_t gR5ss0MemInitDone = FALSE, gR5ss1MemInitDone = FALSE, gR5ss1PORDone = FALSE;
volatile uint32_t gR5ss0Core1ImagePresent = FALSE, gR5ss1Core1ImagePresent = FALSE;

uint32_t Bootloader_socCpuGetClkDefault(uint32_t cpuId)
{
    uint32_t defClock = 0U;

    if (cpuId < MCAL_CSL_CORE_ID_MAX)
    {
        defClock = gCoreBootInfo[cpuId].defaultClockHz;
    }

    return defClock;
}

char *Bootloader_socGetCoreName(uint32_t cpuId)
{
    char *pName = NULL_PTR;

    if (cpuId < MCAL_CSL_CORE_ID_MAX)
    {
        pName = gCoreBootInfo[cpuId].coreName;
    }

    return pName;
}

uint64_t Bootloader_socCpuGetClock(uint32_t cpuId)
{
    int32_t  status  = SystemP_FAILURE;
    uint64_t clkRate = 0U;
    if ((cpuId == MCAL_CSL_CORE_ID_R5FSS0_0) || (cpuId == MCAL_CSL_CORE_ID_R5FSS0_1) ||
        (cpuId == MCAL_CSL_CORE_ID_R5FSS1_0) || (cpuId == MCAL_CSL_CORE_ID_R5FSS1_1))
    {
        clkRate = SOC_rcmGetR5Clock(cpuId);
    }
    if (clkRate != 0U)
    {
        status = SystemP_SUCCESS;
    }
    if (status != SystemP_SUCCESS)
    {
        AppUtils_printf(APP_NAME ":CPU clock get failed for %s\r\n", Bootloader_socGetCoreName(cpuId));
    }
    return clkRate;
}

int32_t Bootloader_socCpuRequest(uint32_t cpuId)
{
    return SystemP_SUCCESS;
}

int32_t Bootloader_socCpuRelease(uint32_t cpuId)
{
    return SystemP_SUCCESS;
}

void Bootloader_socConfigurePll(void)
{
    SOC_RcmPllHsDivOutConfig hsDivCfg;

    uint32_t r5ClkSrc_restore;

    /* Pre Requisite Sequence to relock core pll needs to be done */
    r5ClkSrc_restore = SOC_rcmCoreApllRelockPreRequisite();

    hsDivCfg.hsDivOutFreqHz[0] = (uint32_t)SOC_RCM_FREQ_MHZ2HZ(400U);
    hsDivCfg.hsDivOutFreqHz[1] = (uint32_t)SOC_RCM_FREQ_MHZ2HZ(500U);
    hsDivCfg.hsDivOutFreqHz[2] = (uint32_t)SOC_RCM_FREQ_MHZ2HZ(400U);
    hsDivCfg.hsdivOutEnMask =
        RCM_PLL_HSDIV_OUTPUT_ENABLE_0 | RCM_PLL_HSDIV_OUTPUT_ENABLE_1 | RCM_PLL_HSDIV_OUTPUT_ENABLE_2;
    SOC_rcmCoreApllConfig(RCM_PLL_FOUT_FREQID_CLK_2000MHZ, &hsDivCfg);

    hsDivCfg.hsDivOutFreqHz[0] = (uint32_t)SOC_RCM_FREQ_MHZ2HZ(160U);
    hsDivCfg.hsDivOutFreqHz[0] = (uint32_t)SOC_RCM_FREQ_MHZ2HZ(160U);
    hsDivCfg.hsDivOutFreqHz[1] = (uint32_t)SOC_RCM_FREQ_MHZ2HZ(192U);
    hsDivCfg.hsdivOutEnMask    = RCM_PLL_HSDIV_OUTPUT_ENABLE_0 | RCM_PLL_HSDIV_OUTPUT_ENABLE_1;
    SOC_rcmPerApllConfig(RCM_PLL_FOUT_FREQID_CLK_1920MHZ, &hsDivCfg);

    /* Restore R5F source clock*/
    SOC_rcmSetR5ClockSource(r5ClkSrc_restore);
}

int32_t Bootloader_socCpuSetClock(uint32_t cpuId, uint32_t cpuHz)
{
    int32_t status = SystemP_FAILURE;
    switch (cpuId)
    {
        case MCAL_CSL_CORE_ID_R5FSS0_0:
        case MCAL_CSL_CORE_ID_R5FSS0_1:
        case MCAL_CSL_CORE_ID_R5FSS1_0:
        case MCAL_CSL_CORE_ID_R5FSS1_1:
            status = SOC_rcmSetR5Clock(cpuHz, cpuHz / 2, cpuId);
            break;
        default:
            break;
    }
    return status;
}

int32_t Bootloader_socCpuPowerOnReset(uint32_t cpuId, void *socCoreOpMode)
{
    int32_t status = SystemP_SUCCESS;
    switch (cpuId)
    {
        case MCAL_CSL_CORE_ID_R5FSS0_0:
            if (gR5ss0Core1ImagePresent == FALSE)
            {
                /* Core 1 image is not present or not booted yet.
                   ConfigureR5 in lock step mode. */
                if (socCoreOpMode != NULL_PTR)
                {
                    Bootloader_socCoreOpModeConfig *config = (Bootloader_socCoreOpModeConfig *)socCoreOpMode;
                    /* Check for operating mode configuration as set in syscfg */
                    if (config->r5fss0_opMode == BOOTLOADER_OPMODE_LOCKSTEP)
                    {
                        SOC_rcmR5ConfigLockStep(cpuId);
                    }
                    else
                    {
                        /* ConfigureR5 in Standalone (Dual Core) mode as set in syscfg*/
                        SOC_rcmR5ConfigDualCore(MCAL_CSL_CORE_ID_R5FSS0_1);
                    }
                }
                else
                {
                    SOC_rcmR5ConfigLockStep(cpuId);
                }
            }
            break;
        case MCAL_CSL_CORE_ID_R5FSS0_1:
            /* Configure the R5 to dual core boot. Actual switch happens
               At the end of SBL execution when the core reset is done. */
            SOC_rcmR5ConfigDualCore(cpuId);
            gR5ss0Core1ImagePresent = TRUE;
            break;
        case MCAL_CSL_CORE_ID_R5FSS1_0:
            if (gR5ss1Core1ImagePresent == FALSE)
            {
                /* Core 1 image is not present or not booted yet.
                   ConfigureR5 in lock step mode. */
                if (socCoreOpMode != NULL_PTR)
                {
                    Bootloader_socCoreOpModeConfig *config = (Bootloader_socCoreOpModeConfig *)socCoreOpMode;
                    if (config->r5fss1_opMode == BOOTLOADER_OPMODE_LOCKSTEP)
                    {
                        SOC_rcmR5ConfigLockStep(cpuId);
                        (void)Bootloader_socMemInitCpu(cpuId);
                    }
                    else
                    {
                        /* ConfigureR5 in Standalone mode as set in syscfg*/
                        SOC_rcmR5ConfigDualCore(MCAL_CSL_CORE_ID_R5FSS1_1);
                        if (gR5ss1PORDone == FALSE)
                        {
                            SOC_rcmR5SS1PowerOnReset();
                            SOC_rcmR5SS1TriggerReset();
                            gR5ss1PORDone = TRUE;
                        }
                        (void)Bootloader_socMemInitCpu(MCAL_CSL_CORE_ID_R5FSS1_1);
                    }
                }
                else
                {
                    SOC_rcmR5ConfigLockStep(cpuId);
                    (void)Bootloader_socMemInitCpu(cpuId);
                }
            }
            break;
        case MCAL_CSL_CORE_ID_R5FSS1_1:
            SOC_rcmR5ConfigDualCore(cpuId);
            gR5ss1Core1ImagePresent = TRUE;
            if (gR5ss1PORDone == FALSE)
            {
                SOC_rcmR5SS1PowerOnReset();
                SOC_rcmR5SS1TriggerReset();
                gR5ss1PORDone = TRUE;
            }
            (void)Bootloader_socMemInitCpu(cpuId);
            break;
        default:
            status = SystemP_FAILURE;
            break;
    }
    return status;
}

int32_t Bootloader_socMemInitCpu(uint32_t cpuId)
{
    int32_t status = SystemP_SUCCESS;

    switch (cpuId)
    {
        case MCAL_CSL_CORE_ID_R5FSS0_0:
        case MCAL_CSL_CORE_ID_R5FSS0_1:
            if (gR5ss0MemInitDone == FALSE)
            {
                SOC_rcmStartMemInitTCMA(cpuId);
                SOC_rcmWaitMemInitTCMA(cpuId);
                SOC_rcmStartMemInitTCMB(cpuId);
                SOC_rcmWaitMemInitTCMB(cpuId);
                gR5ss0MemInitDone = TRUE;
            }
            break;
        case MCAL_CSL_CORE_ID_R5FSS1_0:
        case MCAL_CSL_CORE_ID_R5FSS1_1:
            if (gR5ss1MemInitDone == FALSE)
            {
                SOC_rcmStartMemInitTCMA(cpuId);
                SOC_rcmWaitMemInitTCMA(cpuId);
                SOC_rcmStartMemInitTCMB(cpuId);
                SOC_rcmWaitMemInitTCMB(cpuId);
                gR5ss1MemInitDone = TRUE;
            }
            break;
        default:
            break;
    }

    return status;
}

int32_t Bootloader_socCpuResetRelease(uint32_t cpuId, uintptr_t entryPoint)
{
    int32_t status = SystemP_SUCCESS;

    switch (cpuId)
    {
        case MCAL_CSL_CORE_ID_R5FSS0_1:
            SOC_rcmCoreR5FUnhalt(cpuId);
            break;
        case MCAL_CSL_CORE_ID_R5FSS1_0:
        case MCAL_CSL_CORE_ID_R5FSS1_1:
            SOC_rcmCoreR5FUnhalt(cpuId);
            break;
        default:
            break;
    }
    return status;
}

int32_t Bootloader_socCpuResetReleaseSelf(void)
{
    SOC_rcmR5SS0PowerOnReset();
    SOC_rcmR5SS0TriggerReset();

    return SystemP_SUCCESS;
}

uint32_t *Bootloader_socGetSelfCpuList(void)
{
    return &gBootloaderSelfCpuList[0];
}

uint32_t Bootloader_socTranslateSectionAddr(uint32_t cslCoreId, uint32_t addr)
{
    uint32_t outputAddr = addr;

    Bootloader_CoreAddrTranslateInfo *addrTranslateInfo = &gAddrTranslateInfo[cslCoreId];

    uint32_t i;

    for (i = 0; i < addrTranslateInfo->numRegions; i++)
    {
        uint32_t cpuLocalAddr = addrTranslateInfo->addrRegionInfo[i].cpuLocalAddr;
        uint32_t socAddr      = addrTranslateInfo->addrRegionInfo[i].socAddr;
        uint32_t regionSize   = addrTranslateInfo->addrRegionInfo[i].regionSize;

        if ((addr >= cpuLocalAddr) && (addr < cpuLocalAddr + regionSize))
        {
            uint32_t offset = addr - cpuLocalAddr;
            outputAddr      = socAddr + offset;
            break;
        }
    }

    return outputAddr;
}

void Bootloader_socInitL2MailBoxMemory(void)
{
    SOC_rcmMemInitL2Memory();
    SOC_rcmMemInitMailboxMemory();
}

Bootloader_resMemSections *Bootloader_socGetSBLMem(void)
{
    return &gResMemSection;
}

uint32_t Bootloader_socIsAuthRequired(void)
{
    uint32_t isAuthRequired = TRUE;

    if (ptrTopCtrlRegs->EFUSE_DEVICE_TYPE == BOOTLOADER_DEVTYPE_HSSE)
    {
        isAuthRequired = TRUE;
    }
    else
    {
        isAuthRequired = FALSE;
    }

    return isAuthRequired;
}

void Bootloader_socGetBootSeqOid(uint8_t *boot_seq_oid)
{
    uint8_t boot_seq[] = {0x06U, 0x09U, 0x2BU, 0x06U, 0x01U, 0x04U, 0x01U, 0x82U, 0x26U, 0x01U, 0x01U};
    (void)memcpy(boot_seq_oid, boot_seq, sizeof(boot_seq));
}

void Bootloader_socSetAutoClock(void)
{
    uint32_t eFuseFreq = (((ptrTopCtrlRegs->EFUSE1_ROW_12) & CSL_TOP_CTRL_EFUSE1_ROW_12_EFUSE1_ROW_12_R5SS_FREQ_MASK) >>
                          CSL_TOP_CTRL_EFUSE1_ROW_12_EFUSE1_ROW_12_R5SS_FREQ_SHIFT);
    if (eFuseFreq == BOOTLOADER_R5SS_FREQ_200MHz)
    {
        uint32_t cpuFreq = 200U * 1000000U, sysClkFreq = 200U * 1000000U;

        SOC_rcmsetR5SysClock(cpuFreq, sysClkFreq, MCAL_CSL_CORE_ID_R5FSS0_0);
    }
    else
    {
        (void)Bootloader_socCpuSetClock(MCAL_CSL_CORE_ID_R5FSS0_0, (uint32_t)(400U * 1000000U));
    }
}

// int32_t Bootloader_authStart(uintptr_t startAddr, uint32_t size)
// {
//     int32_t status = SystemP_FAILURE;

//     mcal_hw_soc_baseaddress.h[gStreamId].dataIn = (uint8_t *)SOC_virtToPhy((void *)startAddr);
//     mcal_hw_soc_baseaddress.h[gStreamId].dataLen = size;
//     mcal_hw_soc_baseaddress.h[gStreamId].canBeEncrypted = BOOTLOADER_APP_SEGMENT_CANNOTBE_ENCRYPTED;

//     status = HsmClient_procAuthBootStart(&gHSMClient, &mcal_hw_soc_baseaddress.h[gStreamId]);

//     gStreamId++;

//     return status;
// }

// int32_t Bootloader_authUpdate(uintptr_t startAddr, uint32_t size, uint8_t enc)
// {
// 	int32_t status = SystemP_FAILURE;

//     gSecureBootStreamArray[gStreamId].dataIn = (uint8_t *)SOC_virtToPhy((void *)startAddr);
//     gSecureBootStreamArray[gStreamId].dataLen = size;
//     gSecureBootStreamArray[gStreamId].canBeEncrypted = enc;

//     status = HsmClient_procAuthBootUpdate(&gHSMClient, &gSecureBootStreamArray[gStreamId]);

//     gStreamId++;

//     return status;
// }

// int32_t Bootloader_authFinish(void)
// {
//     int32_t status = SystemP_FAILURE;

//     gSecureBootStreamArray[gStreamId].dataIn = 0x0U;
//     gSecureBootStreamArray[gStreamId].dataLen = 0x0U;
//     gSecureBootStreamArray[gStreamId].canBeEncrypted = BOOTLOADER_APP_SEGMENT_CANNOTBE_ENCRYPTED;

//     status = HsmClient_procAuthBootFinish(&gHSMClient, &gSecureBootStreamArray[gStreamId]);

//     return status;
// }
