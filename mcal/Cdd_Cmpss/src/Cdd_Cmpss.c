/* ======================================================================
 *   Copyright (C) 2025 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     Cdd_Cmpss.c
 *
 *  \brief    The CMPSS driver provides APIs to configure the Compare Sub System module
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Det.h"
#include "Cdd_Cmpss.h"
#include "Cdd_Cmpss_Soc.h"
#include "hw_types.h"
#include "cslr_cmpssa.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((CDD_CMPSS_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (CDD_CMPSS_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (CDD_CMPSS_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "AUTOSAR Version of CDD_CMPSS is incorrect"
#endif

/* vendor specific version information check */
#if ((CDD_CMPSS_SW_MAJOR_VERSION != (1U)) || (CDD_CMPSS_SW_MINOR_VERSION != (0U)))
#error "Version numbers of Cdd_Cmpss.c and Cdd_Cmpss.h are not matching!"
#endif
#if ((CDD_CMPSS_CFG_MAJOR_VERSION != (1U)) || (CDD_CMPSS_CFG_MINOR_VERSION != (0U)))
#error "Version numbers of Cdd_Cmpss.c and Cdd_Cmpss_Cfg.h are not matching!"
#endif

#define CDD_CMPSS_HICMP_CTL_M \
    (CSL_CMPSSA_COMPCTL_COMPHSOURCE_MASK | CSL_CMPSSA_COMPCTL_COMPHINV_MASK | CSL_CMPSSA_COMPCTL_ASYNCHEN_MASK)
#define CDD_CMPSS_LOCMP_CTL_M \
    (CSL_CMPSSA_COMPCTL_COMPLSOURCE_MASK | CSL_CMPSSA_COMPCTL_COMPLINV_MASK | CSL_CMPSSA_COMPCTL_ASYNCLEN_MASK)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
static Std_ReturnType Cdd_Cmpss_ConfigFilterHighParamCheck(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale,
                                                           uint16 SampleWindow, uint16 Threshold);
static Std_ReturnType Cdd_Cmpss_ConfigFilterLowParamCheck(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale,
                                                          uint16 SampleWindow, uint16 Threshold);
static Std_ReturnType Cdd_Cmpss_ConfigRampParamCheck(Cdd_Cmpss_HwUnitType HwUnitId, uint16 DelayVal, uint16 PwmSyncSrc);
#endif

/* ========================================================================== */
/*                        Local Object Definitions                            */
/* ========================================================================== */

/** \brief Cdd Cmpss Driver configuration */
#define CDD_CMPSS_START_SEC_CONST_UNSPECIFIED
#include "Cdd_Cmpss_MemMap.h"
static uint32 const CddCmpssBaseAddr[CDD_CMPSS_MAX] = {CDD_CMPSS_BASEADDR_ARRAY};
#define CDD_CMPSS_STOP_SEC_CONST_UNSPECIFIED
#include "Cdd_Cmpss_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_CMPSS_START_SEC_CODE
#include "Cdd_Cmpss_MemMap.h"

#if (STD_ON == CDD_CMPSS_VERSION_INFO_API)
FUNC(void, CDD_CMPSS_CODE)
Cdd_Cmpss_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_CMPSS_DATA) VersionInfo)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfo)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_GET_VERSION_INFO,
                              CDD_CMPSS_E_PARAM_POINTER);
    }
    else
#endif
    {
        VersionInfo->vendorID         = CDD_CMPSS_VENDOR_ID;
        VersionInfo->moduleID         = CDD_CMPSS_MODULE_ID;
        VersionInfo->sw_major_version = (uint8)CDD_CMPSS_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = (uint8)CDD_CMPSS_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = (uint8)CDD_CMPSS_SW_PATCH_VERSION;
    }

    return;
}
#endif

void Cdd_Cmpss_EnableModule(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_ENABLE_MODULE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Set the bit that enables the CMPSS module */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPCTL);
        regVal |= CSL_CMPSSA_COMPCTL_COMPDACE_MASK;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_DisableModule(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_DISABLE_MODULE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Clear the bit that enables the CMPSS module */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPCTL);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPCTL_COMPDACE_MASK);
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_ConfigHighComparator(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_HIGH_COMPARATOR,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the high comparator configuration to the appropriate register */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPCTL);
        regVal &= (uint16) ~((uint16)CDD_CMPSS_HICMP_CTL_M);
        regVal |= Config;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_ConfigLowComparator(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_LOW_COMPARATOR,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the low comparator configuration to the appropriate register */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPCTL);
        regVal &= (uint16) ~((uint16)CDD_CMPSS_LOCMP_CTL_M);
        regVal |= (Config << ((uint16)CSL_CMPSSA_COMPCTL_COMPLSOURCE_SHIFT));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_ConfigOutputsHigh(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_OUTPUTS_HIGH,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the high comparator output settings to the appropriate register */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPCTL);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPCTL_CTRIPOUTHSEL_MASK | (uint16)CSL_CMPSSA_COMPCTL_CTRIPHSEL_MASK);
        regVal |= Config;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_ConfigOutputsLow(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_OUTPUTS_LOW,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the low comparator output settings to the appropriate register */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPCTL);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPCTL_CTRIPOUTLSEL_MASK | (uint16)CSL_CMPSSA_COMPCTL_CTRIPLSEL_MASK);
        regVal |= (Config << ((uint16)CSL_CMPSSA_COMPCTL_COMPLSOURCE_SHIFT));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPCTL), regVal);
    }

    return;
}

uint16 Cdd_Cmpss_GetStatus(Cdd_Cmpss_HwUnitType HwUnitId)
{
    uint16 status = 0U;

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_GET_STATUS,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Return contents of the status register */
        status = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPSTS);
    }

    return status;
}

void Cdd_Cmpss_ConfigDAC(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Config)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_DAC,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the DAC configuration to the appropriate register */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL_SWLOADSEL_MASK | (uint16)CSL_CMPSSA_COMPDACCTL_SELREF_MASK |
                             (uint16)CSL_CMPSSA_COMPDACCTL_DACSOURCE_MASK);
        regVal |= Config;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_SetDACValueHigh(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_DAC_VALUE_HIGH,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else if (Value >= 4096U)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_DAC_VALUE_HIGH,
                              CDD_CMPSS_E_INVALID_CONFIG);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the DAC value to the DAC value shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_DACHVALS), Value);
    }

    return;
}

void Cdd_Cmpss_SetDACValueLow(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_DAC_VALUE_LOW,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else if (Value >= 4096U)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_DAC_VALUE_LOW,
                              CDD_CMPSS_E_INVALID_CONFIG);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the DAC value to the DAC value shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_DACLVALS), Value);
    }

    return;
}

void Cdd_Cmpss_InitFilterHigh(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_INIT_FILTER_HIGH,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Set the high comparator filter initialization bit */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_CTRIPHFILCTL);
        regVal |= (uint16)CSL_CMPSSA_CTRIPHFILCTL_FILINIT_MASK;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CTRIPHFILCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_InitFilterLow(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_INIT_FILTER_LOW,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Set the low comparator filter initialization bit */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_CTRIPLFILCTL);
        regVal |= (uint16)CSL_CMPSSA_CTRIPLFILCTL_FILINIT_MASK;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CTRIPLFILCTL), regVal);
    }

    return;
}

uint16 Cdd_Cmpss_GetDACValueHigh(Cdd_Cmpss_HwUnitType HwUnitId)
{
    uint16 regVal = 0U;

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_GET_DAC_VALUE_HIGH,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Read the DAC value from the DAC value shadow register */
        regVal = HW_RD_REG16(baseAddr + CSL_CMPSSA_DACHVALA);
    }

    return regVal;
}

uint16 Cdd_Cmpss_GetDACValueLow(Cdd_Cmpss_HwUnitType HwUnitId)
{
    uint16 regVal = 0U;

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_GET_DAC_VALUE_LOW,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Read the DAC value from the DAC value shadow register */
        regVal = HW_RD_REG16(baseAddr + CSL_CMPSSA_DACLVALA);
    }

    return regVal;
}

void Cdd_Cmpss_ClearFilterLatchHigh(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CLEAR_FILTER_LATCH_HIGH,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Set the bit that generates a reset pulse to the digital filter latch */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPSTSCLR);
        regVal |= (uint16)CSL_CMPSSA_COMPSTSCLR_HLATCHCLR_MASK;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPSTSCLR), regVal);
    }

    return;
}

void Cdd_Cmpss_ClearFilterLatchLow(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CLEAR_FILTER_LATCH_LOW,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Set the bit that generates a reset pulse to the digital filter latch */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPSTSCLR);
        regVal |= (uint16)CSL_CMPSSA_COMPSTSCLR_LLATCHCLR_MASK;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPSTSCLR), regVal);
    }

    return;
}

void Cdd_Cmpss_SetMaxRampValue(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_MAX_RAMP_VALUE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the maximum ramp value to the shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_RAMPMAXREFS), Value);
    }

    return;
}

uint16 Cdd_Cmpss_GetMaxRampValue(Cdd_Cmpss_HwUnitType HwUnitId)
{
    uint16 regVal = 0U;

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_GET_MAX_RAMP_VALUE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Read the maximum ramp value from the register */
        regVal = HW_RD_REG16(baseAddr + CSL_CMPSSA_RAMPMAXREFA);
    }

    return regVal;
}

void Cdd_Cmpss_SetRampDecValue(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_RAMP_DEC_VALUE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the ramp decrement value to the shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_RAMPDECVALS), Value);
    }

    return;
}

uint16 Cdd_Cmpss_GetRampDecValue(Cdd_Cmpss_HwUnitType HwUnitId)
{
    uint16 regVal = 0U;

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_GET_RAMP_DEC_VALUE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Read the ramp decrement value from the register */
        regVal = HW_RD_REG16(baseAddr + CSL_CMPSSA_RAMPDECVALA);
    }

    return regVal;
}

void Cdd_Cmpss_SetRampDelayValue(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_RAMP_DELAY_VALUE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else if (Value >= 8192U)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_RAMP_DELAY_VALUE,
                              CDD_CMPSS_E_INVALID_CONFIG);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the ramp delay value to the shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_RAMPDLYS), Value);
    }

    return;
}

uint16 Cdd_Cmpss_GetRampDelayValue(Cdd_Cmpss_HwUnitType HwUnitId)
{
    uint16 regVal = 0U;

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_GET_RAMP_DELAY_VALUE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Read the ramp delay value from the register */
        regVal = HW_RD_REG16(baseAddr + CSL_CMPSSA_RAMPDLYA);
    }

    return regVal;
}

void Cdd_Cmpss_ConfigBlanking(Cdd_Cmpss_HwUnitType HwUnitId, uint16 PwmBlankSrc)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_BLANKING,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else if ((PwmBlankSrc < 1U) || (PwmBlankSrc > 32U))
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_BLANKING,
                              CDD_CMPSS_E_INVALID_CONFIG);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /*
         * Write the blank source number to the appropriate register
         */
        /* Program COMPDACCTL */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL_BLANKSOURCE_MASK);
        regVal |= (((PwmBlankSrc - 1U) & ((uint16)0xFU)) << ((uint16)CSL_CMPSSA_COMPDACCTL_BLANKSOURCE_SHIFT));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL), regVal);
        /* Program COMPDACCTL2 */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL2);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL2_BLANKSOURCEUSEL_MASK);
        regVal |= ((((PwmBlankSrc - 1U) >> ((uint16)4U)) << ((uint16)CSL_CMPSSA_COMPDACCTL2_BLANKSOURCEUSEL_SHIFT)) &
                   ((uint16)CSL_CMPSSA_COMPDACCTL2_BLANKSOURCEUSEL_MASK));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL2), regVal);
    }

    return;
}

void Cdd_Cmpss_EnableBlanking(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_ENABLE_BLANKING,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Set the bit that enables the PWMBLANK signal */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL);
        regVal |= (uint16)CSL_CMPSSA_COMPDACCTL_BLANKEN_MASK;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_DisableBlanking(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_DISABLE_BLANKING,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Clear the bit that enables the PWMBLANK signal */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL_BLANKEN_MASK);
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL), regVal);
    }

    return;
}

void Cdd_Cmpss_EnableDEmode(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_ENABLE_DE_MODE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL2);
        regVal |= (uint16)CSL_CMPSSA_COMPDACCTL2_DEENABLE_MASK;
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL2), regVal);
    }

    return;
}

void Cdd_Cmpss_DisableDEmode(Cdd_Cmpss_HwUnitType HwUnitId)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_DISABLE_DE_MODE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL2);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL2_DEENABLE_MASK);
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL2), regVal);
    }

    return;
}

void Cdd_Cmpss_SelectDEACTIVESource(Cdd_Cmpss_HwUnitType HwUnitId, uint8 DeactiveSel)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SELECT_DEACTIVE_SOURCE,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL2);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL2_DEACTIVESEL_MASK);
        regVal |= ((((uint16)DeactiveSel) << ((uint16)CSL_CMPSSA_COMPDACCTL2_DEACTIVESEL_SHIFT)) &
                   ((uint16)CSL_CMPSSA_COMPDACCTL2_DEACTIVESEL_MASK));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL2), regVal);
    }

    return;
}

void Cdd_Cmpss_ConfigHighDACShadowValue2(Cdd_Cmpss_HwUnitType HwUnitId, uint16 DacValue)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_HIGH_DAC_SHADOW_VALUE2,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        regVal = DacValue & ((uint16)CSL_CMPSSA_DACHVALS2_DACVAL_MASK);
        HW_WR_REG16((baseAddr + CSL_CMPSSA_DACHVALS2), regVal);
    }

    return;
}

void Cdd_Cmpss_ConfigLowDACShadowValue2(Cdd_Cmpss_HwUnitType HwUnitId, uint16 DacValue)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_LOW_DAC_SHADOW_VALUE2,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        regVal = DacValue & ((uint16)CSL_CMPSSA_DACLVALS2_DACVAL_MASK);
        HW_WR_REG16((baseAddr + CSL_CMPSSA_DACLVALS2), regVal);
    }

    return;
}

void Cdd_Cmpss_SetComparatorHighHysteresis(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_COMPARATOR_HIGH_HYSTERESIS,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_CONFIG1);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_CONFIG1_COMPHHYS_MASK);
        regVal |= ((Value << ((uint16)CSL_CMPSSA_CONFIG1_COMPHHYS_SHIFT)) & ((uint16)CSL_CMPSSA_CONFIG1_COMPHHYS_MASK));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CONFIG1), regVal);
    }

    return;
}

void Cdd_Cmpss_SetComparatorLowHysteresis(Cdd_Cmpss_HwUnitType HwUnitId, uint16 Value)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_SET_COMPARATOR_LOW_HYSTERESIS,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_CONFIG1);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_CONFIG1_COMPLHYS_MASK);
        regVal |= ((Value << ((uint16)CSL_CMPSSA_CONFIG1_COMPLHYS_SHIFT)) & ((uint16)CSL_CMPSSA_CONFIG1_COMPLHYS_MASK));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CONFIG1), regVal);
    }

    return;
}

void Cdd_Cmpss_ConfigFilterHigh(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale, uint16 SampleWindow,
                                uint16 Threshold)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    Std_ReturnType retVal;
    retVal = Cdd_Cmpss_ConfigFilterHighParamCheck(HwUnitId, SamplePrescale, SampleWindow, Threshold);
    if (retVal == E_OK)
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Shift the sample window and Threshold values into the correct positions
         * and write them to the appropriate register */
        regVal = HW_RD_REG16(baseAddr + CSL_CMPSSA_CTRIPHFILCTL);
        regVal &=
            (uint16) ~(((uint16)CSL_CMPSSA_CTRIPHFILCTL_SAMPWIN_MASK) | ((uint16)CSL_CMPSSA_CTRIPHFILCTL_THRESH_MASK));
        regVal |= ((SampleWindow - 1U) << ((uint16)CSL_CMPSSA_CTRIPHFILCTL_SAMPWIN_SHIFT));
        regVal |= ((Threshold - 1U) << ((uint16)CSL_CMPSSA_CTRIPHFILCTL_THRESH_SHIFT));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CTRIPHFILCTL), regVal);

        /* Set the filter sample clock prescale for the high comparator */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CTRIPHFILCLKCTL), SamplePrescale);
    }

    return;
}

void Cdd_Cmpss_ConfigFilterLow(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale, uint16 SampleWindow,
                               uint16 Threshold)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    Std_ReturnType retVal;
    retVal = Cdd_Cmpss_ConfigFilterLowParamCheck(HwUnitId, SamplePrescale, SampleWindow, Threshold);
    if (retVal == E_OK)
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Shift the sample window and Threshold values into the correct positions
         * and write them to the appropriate register */
        regVal = HW_RD_REG16(baseAddr + CSL_CMPSSA_CTRIPLFILCTL);
        regVal &=
            (uint16) ~(((uint16)CSL_CMPSSA_CTRIPLFILCTL_SAMPWIN_MASK) | ((uint16)CSL_CMPSSA_CTRIPLFILCTL_THRESH_MASK));
        regVal |= ((SampleWindow - 1U) << ((uint16)CSL_CMPSSA_CTRIPLFILCTL_SAMPWIN_SHIFT));
        regVal |= ((Threshold - 1U) << ((uint16)CSL_CMPSSA_CTRIPLFILCTL_THRESH_SHIFT));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CTRIPLFILCTL), regVal);

        /* Set the filter sample clock prescale for the low comparator */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_CTRIPLFILCLKCTL), SamplePrescale);
    }

    return;
}

void Cdd_Cmpss_ConfigLatchOnPWMSYNC(Cdd_Cmpss_HwUnitType HwUnitId, boolean HighEnable, boolean LowEnable)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_LATCH_ON_PWM_SYNC,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* If the HighEnable is true, set the bit that will enable PWMSYNC to reset
         * the high comparator digital filter latch. If not, clear the bit */
        if (HighEnable == TRUE)
        {
            regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPSTSCLR);
            regVal |= (uint16)CSL_CMPSSA_COMPSTSCLR_HSYNCCLREN_MASK;
            HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPSTSCLR), regVal);
        }
        else
        {
            regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPSTSCLR);
            regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPSTSCLR_HSYNCCLREN_MASK);
            HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPSTSCLR), regVal);
        }

        /* If the LowEnable is true, set the bit that will enable PWMSYNC to reset
         * the low comparator digital filter latch. If not, clear the bit */
        if (LowEnable == TRUE)
        {
            regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPSTSCLR);
            regVal |= (uint16)CSL_CMPSSA_COMPSTSCLR_LSYNCCLREN_MASK;
            HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPSTSCLR), regVal);
        }
        else
        {
            regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPSTSCLR);
            regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPSTSCLR_LSYNCCLREN_MASK);
            HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPSTSCLR), regVal);
        }
    }

    return;
}

void Cdd_Cmpss_ConfigRamp(Cdd_Cmpss_HwUnitType HwUnitId, const Cdd_Cmpss_RampConfigType *RampConfigPtr)
{
#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
    Std_ReturnType retVal = E_OK;
    if (NULL_PTR == RampConfigPtr)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_RAMP,
                              CDD_CMPSS_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }
    if (retVal == E_OK)
    {
        retVal = Cdd_Cmpss_ConfigRampParamCheck(HwUnitId, RampConfigPtr->DelayVal, RampConfigPtr->PwmSyncSrc);
    }
    if (retVal == E_OK)
#endif
    {
        uint32 baseAddr;
        uint16 regVal;

        baseAddr = CddCmpssBaseAddr[HwUnitId];

        /* Write the ramp generator source to the register */
        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL_RAMPSOURCE_MASK);
        regVal |= ((RampConfigPtr->PwmSyncSrc - 1U) << ((uint16)CSL_CMPSSA_COMPDACCTL_RAMPSOURCE_SHIFT));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL), regVal);

        regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL2);
        regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL2_RAMPSOURCEUSEL_MASK);
        regVal |= ((((RampConfigPtr->PwmSyncSrc - 1U) >> ((uint16)4U))
                    << ((uint16)CSL_CMPSSA_COMPDACCTL2_RAMPSOURCEUSEL_SHIFT)) &
                   ((uint16)CSL_CMPSSA_COMPDACCTL2_RAMPSOURCEUSEL_MASK));
        HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL2), regVal);

        /* Set or clear the bit that determines from where the max ramp value
         * should be loaded */
        if (RampConfigPtr->UseRampValShdw == TRUE)
        {
            regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL);
            regVal |= (uint16)CSL_CMPSSA_COMPDACCTL_RAMPLOADSEL_MASK;
            HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL), regVal);
        }
        else
        {
            regVal  = HW_RD_REG16(baseAddr + CSL_CMPSSA_COMPDACCTL);
            regVal &= (uint16) ~((uint16)CSL_CMPSSA_COMPDACCTL_RAMPLOADSEL_MASK);
            HW_WR_REG16((baseAddr + CSL_CMPSSA_COMPDACCTL), regVal);
        }

        /* Write the maximum ramp value to the shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_RAMPMAXREFS), RampConfigPtr->MaxRampVal);

        /* Write the ramp decrement value to the shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_RAMPDECVALS), RampConfigPtr->DecrementVal);

        /* Write the ramp delay value to the shadow register */
        HW_WR_REG16((baseAddr + CSL_CMPSSA_RAMPDLYS), RampConfigPtr->DelayVal);
    }

    return;
}

#if (STD_ON == CDD_CMPSS_DEV_ERROR_DETECT)
static Std_ReturnType Cdd_Cmpss_ConfigFilterHighParamCheck(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale,
                                                           uint16 SampleWindow, uint16 Threshold)
{
    Std_ReturnType retVal = E_OK;

    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_HIGH,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
        retVal = E_NOT_OK;
    }

    if (SamplePrescale >= 1024U)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_HIGH,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    if ((SampleWindow < 1U) || (SampleWindow > 32U))
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_HIGH,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    if (Threshold < 1U)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_HIGH,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    if ((retVal == E_OK) && ((Threshold - 1U) < ((SampleWindow - 1U) / 2U)))
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_HIGH,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    return retVal;
}

static Std_ReturnType Cdd_Cmpss_ConfigFilterLowParamCheck(Cdd_Cmpss_HwUnitType HwUnitId, uint16 SamplePrescale,
                                                          uint16 SampleWindow, uint16 Threshold)
{
    Std_ReturnType retVal = E_OK;

    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_LOW,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
        retVal = E_NOT_OK;
    }

    if (SamplePrescale >= 1024U)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_LOW,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    if ((SampleWindow < 1U) || (SampleWindow > 32U))
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_LOW,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    if (Threshold < 1U)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_LOW,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    if ((retVal == E_OK) && ((Threshold - 1U) < ((SampleWindow - 1U) / 2U)))
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_FILTER_LOW,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    return retVal;
}

static Std_ReturnType Cdd_Cmpss_ConfigRampParamCheck(Cdd_Cmpss_HwUnitType HwUnitId, uint16 DelayVal, uint16 PwmSyncSrc)
{
    Std_ReturnType retVal = E_OK;

    if (HwUnitId >= CDD_CMPSS_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_RAMP,
                              CDD_CMPSS_E_ILLEGAL_HW_ID);
        retVal = E_NOT_OK;
    }

    if (DelayVal > CSL_CMPSSA_RAMPDLYS_DELAY_MASK)
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_RAMP,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    if ((PwmSyncSrc < 1U) || (PwmSyncSrc > 32U))
    {
        (void)Det_ReportError(CDD_CMPSS_MODULE_ID, CDD_CMPSS_INSTANCE_ID, CDD_CMPSS_SID_CONFIG_RAMP,
                              CDD_CMPSS_E_INVALID_CONFIG);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif
