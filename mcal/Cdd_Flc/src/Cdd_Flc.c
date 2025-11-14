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
 *  \file     Cdd_Flc.c
 *
 *  \brief    The FLC driver provides APIs to configure the OptiFlash FLC (Fast Local Copy) module
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Det.h"
#include "Cdd_Flc.h"
#include "cslr_rl2_of.h"
#include "Cdd_Flc_Soc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((CDD_FLC_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (CDD_FLC_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (CDD_FLC_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "AUTOSAR Version of CDD_FLC is incorrect"
#endif

/* vendor specific version information check */
#if ((CDD_FLC_SW_MAJOR_VERSION != (1U)) || (CDD_FLC_SW_MINOR_VERSION != (0U)))
#error "Version numbers of Cdd_Flc.c and Cdd_Flc.h are not matching!"
#endif
#if ((CDD_FLC_CFG_MAJOR_VERSION != (1U)) || (CDD_FLC_CFG_MINOR_VERSION != (0U)))
#error "Version numbers of Cdd_Flc.c and Cdd_Flc_Cfg.h are not matching!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
static Std_ReturnType Cdd_Flc_ConfigureRegionParamCheck(Cdd_Flc_HwUnitType hwUnitId, Cdd_Flc_RegionId regionId,
                                                        const Cdd_Flc_RegionConfigType *regionCfgPtr);
#endif

/* ========================================================================== */
/*                        Local Object Definitions                            */
/* ========================================================================== */

/** \brief Cdd Flc Driver configuration */
#define CDD_FLC_START_SEC_CONST_UNSPECIFIED
#include "Cdd_Flc_MemMap.h"
static CSL_rl2_of_Regs *const CddFlcBaseAddr[CDD_FLC_RL2_MAX] = {CDD_FLC_BASEADDR_ARRAY};
#define CDD_FLC_STOP_SEC_CONST_UNSPECIFIED
#include "Cdd_Flc_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_FLC_START_SEC_CODE
#include "Cdd_Flc_MemMap.h"

/* Design: MCAL-29418 */
#if (STD_ON == CDD_FLC_VERSION_INFO_API)
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_FLC_DATA) VersionInfo)
{
#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfo)
    {
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_GET_VERSION_INFO,
                              CDD_FLC_E_PARAM_POINTER);
    }
    else
#endif
    {
        VersionInfo->vendorID         = CDD_FLC_VENDOR_ID;
        VersionInfo->moduleID         = CDD_FLC_MODULE_ID;
        VersionInfo->sw_major_version = (uint8)CDD_FLC_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = (uint8)CDD_FLC_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = (uint8)CDD_FLC_SW_PATCH_VERSION;
    }

    return;
}
#endif

/* Design: MCAL-29420 */
FUNC(Std_ReturnType, CDD_FLC_CODE)
Cdd_Flc_ConfigureRegion(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId,
                        P2CONST(Cdd_Flc_RegionConfigType, AUTOMATIC, CDD_FLC_DATA) RegionCfgPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
    retVal = Cdd_Flc_ConfigureRegionParamCheck(HwUnitId, RegionId, RegionCfgPtr);
    if (retVal == E_OK)
#endif
    {
        CSL_rl2_of_Regs *regs;

        regs = CddFlcBaseAddr[HwUnitId];

        /* check if the region is in disabled state - only then configure */
        if ((regs->FLC[RegionId].CTL & CSL_RL2_OF_FLC_CTL_FENABLE_MASK) == 0U)
        {
            /* Configure the FLC region */
            regs->FLC[RegionId].LO = RegionCfgPtr->srcStartAddr;
            regs->FLC[RegionId].HI = RegionCfgPtr->srcEndAddr;
            regs->FLC[RegionId].RA = RegionCfgPtr->destStartAddr;
            retVal                 = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}

/* Design: MCAL-29416, MCAL-29419 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_EnableRegion(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId,
                     VAR(boolean, AUTOMATIC) EnableWithoutCopy)
{
#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_FLC_RL2_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_ENABLE_REGION,
                              CDD_FLC_E_ILLEGAL_HW_ID);
    }
    else if (RegionId >= CDD_FLC_REGION_ID_MAX)
    {
        /* Report DET error if the specified region ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_ENABLE_REGION,
                              CDD_FLC_E_ILLEGAL_REGION_ID);
    }
    else
#endif
    {
        uint32           ctrlVal;
        CSL_rl2_of_Regs *regs;

        regs = CddFlcBaseAddr[HwUnitId];

        /* Enable and start region copy */
        ctrlVal = CSL_RL2_OF_FLC_CTL_FENABLE_MASK;
        if (EnableWithoutCopy == TRUE)
        {
            ctrlVal |= CSL_RL2_OF_FLC_CTL_FCOPIED_MASK;
        }
        regs->FLC[RegionId].CTL = ctrlVal;
    }

    return;
}

/* Design: MCAL-29415 */
FUNC(boolean, CDD_FLC_CODE)
Cdd_Flc_IsRegionCopyDone(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId)
{
    boolean result = FALSE;

#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_FLC_RL2_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_IS_REGION_COPY_DONE,
                              CDD_FLC_E_ILLEGAL_HW_ID);
    }
    else if (RegionId >= CDD_FLC_REGION_ID_MAX)
    {
        /* Report DET error if the specified region ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_IS_REGION_COPY_DONE,
                              CDD_FLC_E_ILLEGAL_REGION_ID);
    }
    else
#endif
    {
        uint32           mask;
        CSL_rl2_of_Regs *regs;

        regs = CddFlcBaseAddr[HwUnitId];

        /* Check region status */
        mask = (uint32)1U << ((uint32)RegionId);
        if ((regs->FLC_STS & mask) != 0U)
        {
            result = TRUE;
        }
    }

    return result;
}

/* Design: MCAL-29414 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_DisableRegion(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId, VAR(Cdd_Flc_RegionId, AUTOMATIC) RegionId)
{
#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_FLC_RL2_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_DISABLE_REGION,
                              CDD_FLC_E_ILLEGAL_HW_ID);
    }
    else if (RegionId >= CDD_FLC_REGION_ID_MAX)
    {
        /* Report DET error if the specified region ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_DISABLE_REGION,
                              CDD_FLC_E_ILLEGAL_REGION_ID);
    }
    else
#endif
    {
        CSL_rl2_of_Regs *regs;

        regs = CddFlcBaseAddr[HwUnitId];

        /* Disable region */
        regs->FLC[RegionId].CTL = 0U;
    }

    return;
}

/* Design: MCAL-29413 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_GetStatus(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId,
                  P2VAR(Cdd_Flc_StatusType, CDD_FLC_DATA, AUTOMATIC) StatusPtr)
{
#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_FLC_RL2_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_GET_STATUS, CDD_FLC_E_ILLEGAL_HW_ID);
    }
    else if (NULL_PTR == StatusPtr)
    {
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_GET_STATUS, CDD_FLC_E_PARAM_POINTER);
    }
    else
#endif
    {
        uint32           status;
        CSL_rl2_of_Regs *regs;

        regs = CddFlcBaseAddr[HwUnitId];

        /* Init all status to FALSE */
        StatusPtr->copyDone = FALSE;
        StatusPtr->wrError  = FALSE;
        StatusPtr->rdError  = FALSE;

        /* Get status and set the appropriate flags */
        status = regs->IRQSTATUS_RAW;
        if ((status & CSL_RL2_OF_IRQSTATUS_RAW_FLC_DON_MASK) != 0U)
        {
            StatusPtr->copyDone = TRUE;
        }
        /* TI_COVERAGE_GAP_START FLC write error cannot be recreated in test environment */
        if ((status & CSL_RL2_OF_IRQSTATUS_RAW_FLC_WRERR_MASK) != 0U)
        {
            StatusPtr->wrError = TRUE;
        }
        /* TI_COVERAGE_GAP_STOP */
        /* TI_COVERAGE_GAP_START FLC read error cannot be recreated in test environment */
        if ((status & CSL_RL2_OF_IRQSTATUS_RAW_FLC_RDERR_MASK) != 0U)
        {
            StatusPtr->rdError = TRUE;
        }
        /* TI_COVERAGE_GAP_STOP */
    }

    return;
}

/* Design: MCAL-29412 */
FUNC(void, CDD_FLC_CODE)
Cdd_Flc_ClearAllStatus(VAR(Cdd_Flc_HwUnitType, AUTOMATIC) HwUnitId)
{
#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
    if (HwUnitId >= CDD_FLC_RL2_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_CLEAR_ALL_STATUS,
                              CDD_FLC_E_ILLEGAL_HW_ID);
    }
    else
#endif
    {
        CSL_rl2_of_Regs *regs;

        regs = CddFlcBaseAddr[HwUnitId];

        /* Clear all status - write 1 to clear and writing 0 has no effect */
        regs->IRQSTATUS_MSK = CSL_RL2_OF_IRQSTATUS_MSK_FLC_DON_MASK | CSL_RL2_OF_IRQSTATUS_MSK_FLC_WRERR_MASK |
                              CSL_RL2_OF_IRQSTATUS_MSK_FLC_RDERR_MASK;
    }

    return;
}

/* Design: MCAL-29417 */
#if (STD_ON == CDD_FLC_DEV_ERROR_DETECT)
static Std_ReturnType Cdd_Flc_ConfigureRegionParamCheck(Cdd_Flc_HwUnitType hwUnitId, Cdd_Flc_RegionId regionId,
                                                        const Cdd_Flc_RegionConfigType *regionCfgPtr)
{
    Std_ReturnType retVal = E_OK;

    if (hwUnitId >= CDD_FLC_RL2_MAX)
    {
        /* Report DET error if the specified hardware unit ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_CONFIGURE_REGION,
                              CDD_FLC_E_ILLEGAL_HW_ID);
        retVal = E_NOT_OK;
    }

    if (regionId >= CDD_FLC_REGION_ID_MAX)
    {
        /* Report DET error if the specified region ID doesn't exist */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_CONFIGURE_REGION,
                              CDD_FLC_E_ILLEGAL_REGION_ID);
        retVal = E_NOT_OK;
    }

    if (NULL_PTR == regionCfgPtr)
    {
        /* Report DET error for invalid region config pointer */
        (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_CONFIGURE_REGION,
                              CDD_FLC_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }
    else
    {
        if (((regionCfgPtr->srcStartAddr & CDD_FLC_ADDR_ALIGNMENT_MSK) != 0U) ||
            ((regionCfgPtr->srcEndAddr & CDD_FLC_ADDR_ALIGNMENT_MSK) != 0U) ||
            ((regionCfgPtr->destStartAddr & CDD_FLC_ADDR_ALIGNMENT_MSK) != 0U))
        {
            /* Report DET error if addresses are not aligned to 4 KB boundary */
            (void)Det_ReportError(CDD_FLC_MODULE_ID, CDD_FLC_INSTANCE_ID, CDD_FLC_SID_CONFIGURE_REGION,
                                  CDD_FLC_E_UNALIGNED_ADDRESS);
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}
#endif

#define CDD_FLC_STOP_SEC_CODE
#include "Cdd_Flc_MemMap.h"
