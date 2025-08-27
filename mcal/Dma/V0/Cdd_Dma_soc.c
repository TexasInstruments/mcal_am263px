/*
 * Copyright (C) 2024 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file   Cdd_Dma_soc.c
 *
 *  \brief  This file contains device abstraction layer APIs for the DMA device.
 *          There are APIs here to enable the DMA instance, set the required
 *          configurations for communication, transmit or receive data.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_Dma_Cfg.h"
#include "hw_types.h"
#include "Cdd_Dma.h"
#include "stddef.h"

/*********************************************************************************************************************
 * Local Type Declarations
 *********************************************************************************************************************/
typedef struct
{
    uint32 cpuID;
    /**< CPU/core ID within cluster
     *   Refer \ref CSL_ArmR5CPUID
     */
    uint32 grpId;
    /**< Group Id of the cluster
     *   Refer \ref CSL_ArmR5ClusterGroupID
     */
} Cdd_Dma_Csl_ArmR5CpuInfo;

typedef struct
{
    uint32                   tcmaSize;
    uint32                   tcmbSize;
    Cdd_Dma_Csl_ArmR5CpuInfo cpuInfo;
} Cdd_Dma_Soc_VirtToPhyMap;

#define CDD_DMA_MAP_AVAILABLE     (uint8)1U
#define CDD_DMA_MAP_NOT_AVAILABLE (uint8)0U
/*********************************************************************************************************************
 * Local Object Definitions
 *********************************************************************************************************************/
#define CDD_DMA_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Dma_MemMap.h"
Cdd_Dma_Soc_VirtToPhyMap Cdd_Dma_virtToPhymap;
#define CDD_DMA_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Dma_MemMap.h"

#define CDD_DMA_START_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"
uint8 Cdd_Dma_isMapAvailable = CDD_DMA_MAP_NOT_AVAILABLE;
#define CDD_DMA_STOP_SEC_VAR_INIT_8
#include "Cdd_Dma_MemMap.h"

/*********************************************************************************************************************
 * Local Preprocessor
 *********************************************************************************************************************/
#define CDD_DMA_CSL_MSS(reg, PER_REG_FIELD) \
    (((reg) & CDD_DMA_CSL_##PER_REG_FIELD##_MASK) >> CDD_DMA_CSL_##PER_REG_FIELD##_SHIFT)
/**
 *  \anchor CSL_ArmR5ClusterGroupID
 *  \name R5 Cluster Group IDs
 *
 *  @{
 */
/** \brief R5 Cluster Group ID0 */
#define CDD_DMA_CSL_ARM_R5_CLUSTER_GROUP_ID_0 ((uint32)0x00U)
/** \brief R5 Cluster Group ID1 */
#define CDD_DMA_CSL_ARM_R5_CLUSTER_GROUP_ID_1 ((uint32)0x01U)
/** @} */
#define CDD_DMA_CSL_ARM_R5_MPIDR_DEFAULT (0xC0000000U)

/**
 *  \anchor CSL_ArmR5CPUID
 *  \name R5 Core IDs
 *
 *  @{
 */
/** \brief R5 Core ID0 */
#define CDD_DMA_CSL_ARM_R5_CPU_ID_0 ((uint32)0x00U)
/** \brief R5 Core ID1 */
#define CDD_DMA_CSL_ARM_R5_CPU_ID_1 ((uint32)0x01U)
/** @} */

/* Base Addresss */
#define CDD_DMA_CSL_R5SS0_CORE0_TCMA_U_BASE (0x78000000UL)
#define CDD_DMA_CSL_R5SS0_CORE0_TCMB_U_BASE (0x78100000UL)
#define CDD_DMA_CSL_R5SS0_CORE1_TCMA_U_BASE (0x78200000UL)
#define CDD_DMA_CSL_R5SS0_CORE1_TCMB_U_BASE (0x78300000UL)
#define CDD_DMA_CSL_R5SS1_CORE0_TCMA_U_BASE (0x78400000UL)
#define CDD_DMA_CSL_R5SS1_CORE0_TCMB_U_BASE (0x78500000UL)
#define CDD_DMA_CSL_R5SS1_CORE1_TCMA_U_BASE (0x78600000UL)
#define CDD_DMA_CSL_R5SS1_CORE1_TCMB_U_BASE (0x78700000UL)

/* ========================================================================== */
/*                        Static Function Declaration                         */
/* ========================================================================== */
#ifdef MCAL_DYNAMIC_BUILD
uint32 Cdd_Dma_Mcal_ArmR5ReadMpidrReg(void);
#else
__attribute__((naked)) uint32 Cdd_Dma_Mcal_ArmR5ReadMpidrReg(void);
#endif
static void                      Cdd_Dma_Csl_ArmR5GetCpuID(Cdd_Dma_Csl_ArmR5CpuInfo *cpuInfo);
static uint32                    Cdd_Dma_Soc_RcmIsR5FInLockStepMode(uint32 r5fClusterGroupId);
static Cdd_Dma_Csl_Mss_CtrlRegs *Cdd_Dma_Soc_RcmGetBaseAddressMssCtrl(void);

uint64 Cdd_Dma_Soc_VirtToPhy_Internal(void *virtAddr);

static void   Cdd_Dma_virtToPhymapcheck(uint32 retVal);
static uint64 Cdd_Dma_virtToPhymap_core0TCMA(uint64 temp);
static uint64 Cdd_Dma_virtToPhymap_core0TCMB(uint64 temp);
static uint64 Cdd_Dma_virtToPhymap_core1TCMA(uint64 temp);
static uint64 Cdd_Dma_virtToPhymap_core1TCMB(uint64 temp);

#define CDD_DMA_START_SEC_CODE
#include "Cdd_Dma_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
uint64 Cdd_Dma_Soc_VirtToPhy_Internal(void *virtAddr)
{
    uintptr_t temp    = (uintptr_t)virtAddr;
    uint64    phyAddr = (uint64)temp; /* Default case */

    /* R5F overrides */
#if (__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R')
    uint32 retVal;

    if (CDD_DMA_MAP_NOT_AVAILABLE == Cdd_Dma_isMapAvailable)
    {
        /* Get Core ID Info */
        Cdd_Dma_Csl_ArmR5GetCpuID(&Cdd_Dma_virtToPhymap.cpuInfo);

        retVal = Cdd_Dma_Soc_RcmIsR5FInLockStepMode(Cdd_Dma_virtToPhymap.cpuInfo.grpId);
        /* LockStep Mode TCM Size is 64KB */

        if (Cdd_Dma_virtToPhymap.cpuInfo.grpId == (uint32)CDD_DMA_CSL_ARM_R5_CLUSTER_GROUP_ID_0)
        {
            Cdd_Dma_virtToPhymapcheck(retVal);
        }
        else if (Cdd_Dma_virtToPhymap.cpuInfo.grpId == (uint32)CDD_DMA_CSL_ARM_R5_CLUSTER_GROUP_ID_1) /* R5SS1-0 */
        {
            Cdd_Dma_virtToPhymapcheck(retVal);
        }
        else
        {
            /*Do Nothing*/
        }

        Cdd_Dma_isMapAvailable = CDD_DMA_MAP_AVAILABLE;
    }

    if (Cdd_Dma_virtToPhymap.cpuInfo.grpId == (uint32)CDD_DMA_CSL_ARM_R5_CLUSTER_GROUP_ID_0) /* R5SS0-0 */
    {
        if (Cdd_Dma_virtToPhymap.cpuInfo.cpuID == CDD_DMA_CSL_ARM_R5_CPU_ID_0)
        {
            /* TCMA R5FSS0-0 */
            phyAddr = Cdd_Dma_virtToPhymap_core0TCMA(temp);
        }
        else if (Cdd_Dma_virtToPhymap.cpuInfo.cpuID == CDD_DMA_CSL_ARM_R5_CPU_ID_1)
        {
            /* TCMA R5FSS0-1 */
            phyAddr = Cdd_Dma_virtToPhymap_core0TCMB(temp);
        }
        else
        {
            /*Do Nothing*/
        }
    }

    if (Cdd_Dma_virtToPhymap.cpuInfo.grpId == (uint32)CDD_DMA_CSL_ARM_R5_CLUSTER_GROUP_ID_1) /* R5SS1-0 */
    {
        if (Cdd_Dma_virtToPhymap.cpuInfo.cpuID == CDD_DMA_CSL_ARM_R5_CPU_ID_0)
        {
            /* TCMA R5FSS1-0 */
            phyAddr = Cdd_Dma_virtToPhymap_core1TCMA(temp);
        }
        else if (Cdd_Dma_virtToPhymap.cpuInfo.cpuID == CDD_DMA_CSL_ARM_R5_CPU_ID_1)
        {
            /* TCMA R5FSS1-1 */
            phyAddr = Cdd_Dma_virtToPhymap_core1TCMB(temp);
        }
        else
        {
            /*Do Nothing*/
        }
    }
#endif

    return (phyAddr);
}

static void Cdd_Dma_virtToPhymapcheck(uint32 retVal)
{
    uint32 value = retVal;
    if (value == TRUE)
    {
        Cdd_Dma_virtToPhymap.tcmaSize = (CDD_DMA_CSL_MSS_TCMA_RAM_SIZE * 2U);
        Cdd_Dma_virtToPhymap.tcmbSize = (CDD_DMA_CSL_MSS_TCMB_RAM_SIZE * 2U);
    }
    else
    {
        Cdd_Dma_virtToPhymap.tcmaSize = (CDD_DMA_CSL_MSS_TCMA_RAM_SIZE);
        Cdd_Dma_virtToPhymap.tcmbSize = (CDD_DMA_CSL_MSS_TCMB_RAM_SIZE);
    }
    return;
}

static uint64 Cdd_Dma_virtToPhymap_core0TCMA(uint64 temp)
{
    uint64 phyAddr = (uint64)temp;
    if ((temp < (CDD_DMA_CSL_MSS_TCMA_RAM_BASE + Cdd_Dma_virtToPhymap.tcmaSize)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMA_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS0_CORE0_TCMA_U_BASE;
    }

    /* TCMB R5FSS0-0 */
    else if ((temp >= CDD_DMA_CSL_MSS_TCMB_RAM_BASE) &&
             (temp < (CDD_DMA_CSL_MSS_TCMB_RAM_BASE + Cdd_Dma_virtToPhymap.tcmbSize)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMB_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS0_CORE0_TCMB_U_BASE;
    }
    else
    {
        /*Do Nothing*/
    }
    return phyAddr;
}

static uint64 Cdd_Dma_virtToPhymap_core0TCMB(uint64 temp)
{
    uint64 phyAddr = (uint64)temp;
    if ((temp < (CDD_DMA_CSL_MSS_TCMA_RAM_BASE + CDD_DMA_CSL_MSS_TCMA_RAM_SIZE)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMA_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS0_CORE1_TCMA_U_BASE;
    }

    /* TCMB R5FSS0-1 */
    else if ((temp >= CDD_DMA_CSL_MSS_TCMB_RAM_BASE) &&
             (temp < (CDD_DMA_CSL_MSS_TCMB_RAM_BASE + CDD_DMA_CSL_MSS_TCMB_RAM_SIZE)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMB_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS0_CORE1_TCMB_U_BASE;
    }
    else
    {
        /*Do Nothing*/
    }
    return phyAddr;
}

static uint64 Cdd_Dma_virtToPhymap_core1TCMA(uint64 temp)
{
    uint64 phyAddr = (uint64)temp;
    if ((temp < (CDD_DMA_CSL_MSS_TCMA_RAM_BASE + Cdd_Dma_virtToPhymap.tcmaSize)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMA_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS1_CORE0_TCMA_U_BASE;
    }

    /* TCMB R5FSS1-0 */
    else if ((temp >= CDD_DMA_CSL_MSS_TCMB_RAM_BASE) &&
             (temp < (CDD_DMA_CSL_MSS_TCMB_RAM_BASE + Cdd_Dma_virtToPhymap.tcmbSize)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMB_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS1_CORE0_TCMB_U_BASE;
    }
    else
    {
        /*Do Nothing*/
    }
    return phyAddr;
}

static uint64 Cdd_Dma_virtToPhymap_core1TCMB(uint64 temp)
{
    uint64 phyAddr = (uint64)temp;
    if ((temp < (CDD_DMA_CSL_MSS_TCMA_RAM_BASE + Cdd_Dma_virtToPhymap.tcmaSize)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMA_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS1_CORE0_TCMA_U_BASE;
    }

    /* TCMB R5FSS1-0 */
    else if ((temp >= CDD_DMA_CSL_MSS_TCMB_RAM_BASE) &&
             (temp < (CDD_DMA_CSL_MSS_TCMB_RAM_BASE + Cdd_Dma_virtToPhymap.tcmbSize)))
    {
        phyAddr -= CDD_DMA_CSL_MSS_TCMB_RAM_BASE;
        phyAddr += CDD_DMA_CSL_R5SS1_CORE1_TCMB_U_BASE;
    }
    else
    {
        /*Do Nothing*/
    }
    return phyAddr;
}

static void Cdd_Dma_Csl_ArmR5GetCpuID(Cdd_Dma_Csl_ArmR5CpuInfo *cpuInfo)
{
    uint32 regVal;

    if (cpuInfo != NULL_PTR)
    {
        regVal         = Cdd_Dma_Mcal_ArmR5ReadMpidrReg();
        cpuInfo->cpuID = (uint32)((regVal & CDD_DMA_CSL_R5_MPIDR_AFF0_MASK) >> CDD_DMA_CSL_R5_MPIDR_AFF0_SHIFT);
        cpuInfo->grpId = (uint32)((regVal & CDD_DMA_CSL_R5_MPIDR_AFF1_MASK) >> CDD_DMA_CSL_R5_MPIDR_AFF1_SHIFT);
    }
    return;
}

static uint32 Cdd_Dma_Soc_RcmIsR5FInLockStepMode(uint32 r5fClusterGroupId)
{
    uint32                    retVal  = FALSE;
    Cdd_Dma_Csl_Mss_CtrlRegs *mssCtrl = Cdd_Dma_Soc_RcmGetBaseAddressMssCtrl();

    if (r5fClusterGroupId == 0U)
    {
        if (CDD_DMA_CSL_MSS(mssCtrl->r5_status_reg, MSS_CTRL_R5_STATUS_REG_R5_STATUS_REG_LOCK_STEP) == 1U)
        {
            /* Lockstep Mode */
            retVal = TRUE;
        }
        else
        {
            /* Dualcore Mode */
            retVal = FALSE;
        }
    }

    return retVal;
}

static Cdd_Dma_Csl_Mss_CtrlRegs *Cdd_Dma_Soc_RcmGetBaseAddressMssCtrl(void)
{
    return (Cdd_Dma_Csl_Mss_CtrlRegs *)CDD_DMA_CSL_MSS_CTRL_U_BASE;
}

#ifdef MCAL_DYNAMIC_BUILD
uint32 Cdd_Dma_Mcal_ArmR5ReadMpidrReg(void)
{
    uint32 local = CDD_DMA_CSL_ARM_R5_MPIDR_DEFAULT;
    return local;
}
#else
__attribute__((naked)) uint32 Cdd_Dma_Mcal_ArmR5ReadMpidrReg(void)
{
    asm("dmb ");
    asm("mrc   p15, #0, r0, c0, c0, #5 ");
    asm("bx lr ");
}
#endif

#define CDD_DMA_STOP_SEC_CODE
#include "Cdd_Dma_MemMap.h"

/*********************************************************************************************************************
 *  End of File: Cdd_Dma_soc.c
 *********************************************************************************************************************/
