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
 *  \file      Fls.c
 *
 *  \brief    This file contains Fls MCAL driver
 *
 */

/* Common Design ID's */
/*
 *Design: SITARA_MCU_MCAL-4793, SITARA_MCU_MCAL-4805, SITARA_MCU_MCAL-4848, SITARA_MCU_MCAL-4768,
 *SITARA_MCU_MCAL-4800, SITARA_MCU_MCAL-4887, SITARA_MCU_MCAL-4763, SITARA_MCU_MCAL-4443,
 *SITARA_MCU_MCAL-4860, SITARA_MCU_MCAL-4779, SITARA_MCU_MCAL-4758, SITARA_MCU_MCAL-4775,
 *SITARA_MCU_MCAL-4748, SITARA_MCU_MCAL-4864, SITARA_MCU_MCAL-4795, SITARA_MCU_MCAL-4754,
 *SITARA_MCU_MCAL-4843, SITARA_MCU_MCAL-4809, SITARA_MCU_MCAL-4824, SITARA_MCU_MCAL-4856,
 *SITARA_MCU_MCAL-4790, SITARA_MCU_MCAL-4784, SITARA_MCU_MCAL-4852 Design: MCAL-10266,
 *MCAL-10271,MCAL-10272,MCAL-10277,MCAL-10287,MCAL-10304, MCAL-10309, MCAL-10356, MCAL-17662,
 *MCAL-17674, MCAL-17659, MCAL-17660, MCAL-22569
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include "Fls_Cfg.h"
#include "Fls_Cbk.h"
#include "Fls.h"
#include "Fls_Brd_Nor.h"
#include "Det.h"
#if (STD_ON == FLS_OSPI_PHY_ENABLE)
#include "Fls_Ospi_Phy.h"
#endif /* #if (STD_ON == FLS_OSPI_PHY_ENABLE) */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *Design: SITARA_MCU_MCAL-3600,SITARA_MCU_MCAL-3601
 */
/* AUTOSAR version information check has to match definition in header file */
#if ((FLS_AR_RELEASE_MAJOR_VERSION != (4U)) || (FLS_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (FLS_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Fls: AUTOSAR Version Numbers of Fls are different!!"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((FLS_SW_MAJOR_VERSION != (10U)) || (FLS_SW_MINOR_VERSION != (3U)) || (FLS_SW_PATCH_VERSION != (0U)))
#error "Fls: Software Version Numbers are inconsistent!!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
#if (STD_ON == FLS_DEV_ERROR_DETECT)
static Std_ReturnType Fls_CheckValidAddress(Fls_AddressType SourceAddress);
static Std_ReturnType Fls_DetChekWrite(Fls_AddressType TargetAddress,
                                       P2VAR(const uint8, AUTOMATIC, FLS_APPL_DATA) SourceAddressPtr,
                                       Fls_LengthType Length);
static Std_ReturnType Fls_DetCheckBlankCheck(Fls_AddressType TargetAddress, Fls_LengthType Length);
static Std_ReturnType Fls_DetCheckRead(Fls_AddressType SourceAddress,
                                       P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr, Fls_LengthType Length);
static Std_ReturnType Fls_DetCheckCompare(Fls_AddressType SourceAddress,
                                          P2VAR(const uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
                                          Fls_LengthType Length);
static uint8          Fls_DetCheckInit(P2CONST(Fls_ConfigType, AUTOMATIC, FLS_CONFIG_DATA) CfgPtr);
#endif
static Std_ReturnType Fls_CheckSectorAlignment(Fls_AddressType SourceAddress);
static Std_ReturnType Fls_CheckPageAlignement(Fls_AddressType SourceAddress);
static Std_ReturnType Fls_CheckBlockAlignement(Fls_AddressType SourceAddress);
static void           Fls_TimeoutVerification_sub(void);
static void           Fls_TimeoutVerification(TickType startCount);
static void           Fls_MainFunction_sub(void);
static void           Fls_TimeoutCheck(StatusType status, uint32 time1, TickType elapsedCount);
static void           Fls_MainFunctioncall(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define FLS_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fls_MemMap.h"
/** \brief FLS driver object */
Fls_DriverObjType Fls_DrvObj = {.status = MEMIF_UNINIT};
#if (STD_ON == FLS_OSPI_PHY_ENABLE)
Std_ReturnType Fls_PhyStatus = (Std_ReturnType)E_NOT_OK;
#endif
#define FLS_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fls_MemMap.h"

#define FLS_START_SEC_VAR_NO_INIT_32
#include "Fls_MemMap.h"
/*Set Erase Type Parameters */
VAR(uint32, FLS_VAR_NO_INIT) sector_or_blocksize;
#define FLS_STOP_SEC_VAR_NO_INIT_32
#include "Fls_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

static void Fls_TimeoutVerification(TickType startCount)
{
    TickType   tempCount = 0U, elapsedCount = 0U;
    StatusType status;

    tempCount = startCount;

    status       = GetElapsedValue(FLS_OS_COUNTER_ID, &tempCount, &elapsedCount);
    uint32 time1 = 0U;

    switch (Fls_DrvObj.typeoferase)
    {
        case FLS_SECTOR_ERASE:
            if (Fls_DrvObj.jobType == FLS_JOB_ERASE)
            {
                time1 = Fls_Config_SFDP_Ptr->flsMaxSectorErasetimeConvInUsec;
            }
            else
            {
                time1 = Fls_Config_SFDP_Ptr->flsMaxSectorReadWritetimeConvInUsec;
            }
            Fls_TimeoutCheck(status, time1, elapsedCount);
            break;
        case FLS_BLOCK_ERASE:
            if (Fls_DrvObj.jobType == FLS_JOB_ERASE)
            {
                time1 = Fls_Config_SFDP_Ptr->flsMaxBlockErasetimeConvInUsec;
            }
            else
            {
                time1 = Fls_Config_SFDP_Ptr->flsMaxBlockReadWritetimeConvInUsec;
            }
            Fls_TimeoutCheck(status, time1, elapsedCount);
            break;
        case FLS_CHIP_ERASE:
            if (Fls_DrvObj.jobType == FLS_JOB_ERASE)
            {
                time1 = Fls_Config_SFDP_Ptr->flsMaxChipErasetimeConvInUsec;
            }
            else
            {
                time1 = Fls_Config_SFDP_Ptr->flsMaxChipReadWritetimeConvInUsec;
            }
            Fls_TimeoutCheck(status, time1, elapsedCount);
            break;
        default:
            break;
    }
}

static void Fls_TimeoutCheck(StatusType status, uint32 time1, TickType elapsedCount)
{
    if ((Std_ReturnType)E_OK == status)
    {
        if (elapsedCount > (time1 * (uint32)FLS_MAX_WRITE_TIME))
        {
            Fls_TimeoutVerification_sub();
        }
    }
    else
    {
        /* Do Nothing */
    }
}

static void Fls_TimeoutVerification_sub(void)
{
    Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION, FLS_E_TIMEOUT);
    if (Fls_DrvObj.Fls_JobErrorNotification != NULL_PTR)
    {
        Fls_DrvObj.Fls_JobErrorNotification();
    }
    else
    {
        /* Do Nothing */
    }
    Fls_DrvObj.jobResultType = MEMIF_JOB_FAILED;
    Fls_DrvObj.status        = MEMIF_IDLE;
}

/*
 *Design: MCAL-10367 MCAL-10370 MCAL-10371 MCAL-17663 MCAL-17694
 */
#if (STD_ON == FLS_DEV_ERROR_DETECT)
/**
 * Check Flash bank ranges for a valid address
 *
 */
static Std_ReturnType Fls_CheckValidAddress(Fls_AddressType SourceAddress)
{
    Std_ReturnType retVal    = (Std_ReturnType)E_NOT_OK;
    uint32         startAddr = 0U;
    if (SourceAddress >= startAddr)
    {
        if (SourceAddress <= (startAddr + Fls_Config_SFDP_Ptr->flashSize))
        {
            retVal = E_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    return retVal;
}

/*
 *Design: MCAL-17656, MCAL-17693, MCAL-17681, MCAL-17670, MCAL-17654, MCAL-17668, MCAL-17671
 */
/**
 * Checks sector alignment for a valid address
 *
 */
static Std_ReturnType Fls_CheckSectorAlignment(Fls_AddressType SourceAddress)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    if ((SourceAddress % Fls_Config_SFDP_Ptr->eraseCfg.sectorSize) == 0U)
    {
        retVal = E_OK;
    }
    return retVal;
}

/**
 * Checks block alignment for a valid address
 *
 */
static Std_ReturnType Fls_CheckBlockAlignement(Fls_AddressType SourceAddress)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    if ((SourceAddress % Fls_Config_SFDP_Ptr->eraseCfg.blockSize) == 0U)
    {
        retVal = E_OK;
    }
    return retVal;
}

/**
 * Checks page alignment for a valid address
 *
 */
static Std_ReturnType Fls_CheckPageAlignement(Fls_AddressType SourceAddress)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    if ((SourceAddress % Fls_Config_SFDP_Ptr->pageSize) == 0U)
    {
        retVal = E_OK;
    }
    return retVal;
}

#endif /*#if (STD_ON == FLS_DEV_ERROR_DETECT)*/

/**
 *  \name: Fls_Init
 *
 *  The function Fls_Init shall initialize the FLS module and all
 *	flash memory relevant registers (hardware) with parameters
 *	provided in the given configuration set
 *
 */

/*
 * Design:
 * SITARA_MCU_MCAL-3608,SITARA_MCU_MCAL-3646,SITARA_MCU_MCAL-4056,SITARA_MCU_MCAL-3649,SITARA_MCU_MCAL-3648,SITARA_MCU_MCAL-3650,SITARA_MCU_MCAL-3652,SITARA_MCU_MCAL-3671,SITARA_MCU_MCAL-3608,SITARA_MCU_MCAL-3606,SITARA_MCU_MCAL-3645
 * Design: MCAL-10228 MCAL-10175 MCAL-10205 MCAL-10280 MCAL-10170 MCAL-10338 MCAL-10246 MCAL-10244
 * MCAL-10173 MCAL-10191 MCAL-10207 MCAL-10216 MCAL-10224 MCAL-10233
 */

FUNC(void, FLS_CODE) Fls_Init(P2CONST(Fls_ConfigType, AUTOMATIC, FLS_CONFIG_DATA) ConfigPtr)
{
    const Fls_ConfigType *CfgPtr = (Fls_ConfigType *)NULL_PTR;
    Std_ReturnType        ret    = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    uint8 detFlag = 0U;
#endif
#if (STD_ON == FLS_PRE_COMPILE_VARIANT)
    if (NULL_PTR == ConfigPtr)
    {
        CfgPtr = &FLS_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == FLS_PRE_COMPILE_VARIANT) */
#if (STD_ON == FLS_POST_BUILD_VARIANT)
    if (NULL_PTR != ConfigPtr)
    {
        CfgPtr = ConfigPtr;
    }
#endif /* (STD_ON == FLS_POST_BUILD_VARIANT) */

#if (STD_ON == FLS_DEV_ERROR_DETECT)
    detFlag = Fls_DetCheckInit(CfgPtr);

    if (detFlag == 0U)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        /* Instantiate a Driver Obj to be used by module */
        Fls_resetDrvObj(&Fls_DrvObj);
        /*Copy the input config parameters to Driver Object */
        Fls_copyConfig(&Fls_DrvObj, CfgPtr);
        Fls_DrvObj.jobResultType = MEMIF_JOB_PENDING;

        ret = Fls_hwUnitInit();
#if (STD_ON == FLS_OSPI_PHY_ENABLE)
        if (ret == E_OK)
        {
            Fls_PhyStatus = Fls_Ospi_phyInit();
            if (Fls_PhyStatus != E_OK)
            {
                ret = (Std_ReturnType)E_NOT_OK;
            }
        }
#endif /* #if (STD_ON == FLS_OSPI_PHY_ENABLE) */

        /*Init the HW */
        if (ret == (Std_ReturnType)E_OK)
        {
            Fls_DrvObj.jobResultType = MEMIF_JOB_OK;
            Fls_DrvObj.status        = MEMIF_IDLE;
        }
        else
        {
            Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_UNEXPECTED_FLASH_ID);
            Fls_DrvObj.status = MEMIF_UNINIT;
        }
    }
    return;
}

#if (STD_ON == FLS_DEV_ERROR_DETECT)
static uint8 Fls_DetCheckInit(P2CONST(Fls_ConfigType, AUTOMATIC, FLS_CONFIG_DATA) CfgPtr)
{
    uint8 detFlag = 0U;
    if (MEMIF_BUSY == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_BUSY);
        detFlag++;
    }
    if ((detFlag == 0U) && (NULL_PTR == CfgPtr))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_PARAM_CONFIG);
        detFlag++;
    }
    if ((detFlag == 0U) && ((CfgPtr->maxReadNormalMode == (uint32)0U) ||
                            ((CfgPtr->maxReadNormalMode % Fls_Config_SFDP_Ptr->pageSize) != 0U)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_PARAM_CONFIG);
        detFlag++;
    }

    if ((detFlag == 0U) && ((CfgPtr->maxWriteNormalMode == (uint32)0U) ||
                            ((CfgPtr->maxWriteNormalMode % Fls_Config_SFDP_Ptr->pageSize) != 0U)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_PARAM_CONFIG);
        detFlag++;
    }
    return detFlag;
}
#endif
#if (STD_ON == FLS_DEV_ERROR_DETECT)
static Std_ReturnType Fls_CheckEraseAddressAlignment(Fls_AddressType eraseStartAddress, Fls_LengthType Length)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    if ((Length >= Fls_Config_SFDP_Ptr->eraseCfg.sectorSize) && (Length < Fls_Config_SFDP_Ptr->eraseCfg.blockSize))
    {
        if (E_NOT_OK == Fls_CheckSectorAlignment(eraseStartAddress))
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    else if (Length >= Fls_Config_SFDP_Ptr->eraseCfg.blockSize)
    {
        if (E_NOT_OK == Fls_CheckBlockAlignement(eraseStartAddress))
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    if ((retVal == (Std_ReturnType)E_OK) && (E_NOT_OK == Fls_CheckValidAddress(eraseStartAddress)))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

static Std_ReturnType Fls_CheckEraseLengthAlignment(Fls_AddressType eraseStartAddress, Fls_LengthType Length)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    if (Length == (Fls_LengthType)0U)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if ((Length >= Fls_Config_SFDP_Ptr->eraseCfg.sectorSize) && (Length < Fls_Config_SFDP_Ptr->eraseCfg.blockSize))
    {
        if (E_NOT_OK == Fls_CheckSectorAlignment(eraseStartAddress + Length))
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    else if (Length >= Fls_Config_SFDP_Ptr->eraseCfg.blockSize)
    {
        if (E_NOT_OK == Fls_CheckBlockAlignement(eraseStartAddress + (Fls_AddressType)Length))
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    if ((retVal == (Std_ReturnType)E_OK) &&
        (E_NOT_OK == Fls_CheckValidAddress(eraseStartAddress + (Fls_AddressType)Length - 1U)))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}
#endif

/**
 *  \name: Fls_Erase
 *
 *  The function Fls_Erase shall erase one or more complete flash sectors.
 *
 */

/*
 * Design:
 * SITARA_MCU_MCAL-3608,SITARA_MCU_MCAL-3607,SITARA_MCU_MCAL-3606,SITARA_MCU_MCAL-3624,SITARA_MCU_MCAL-3675,SITARA_MCU_MCAL-3674,SITARA_MCU_MCAL-3676,SITARA_MCU_MCAL-3677,SITARA_MCU_MCAL-3678,SITARA_MCU_MCAL-3679,SITARA_MCU_MCAL-3681,SITARA_MCU_MCAL-3682,SITARA_MCU_MCAL-3683,SITARA_MCU_MCAL-3684,SITARA_MCU_MCAL-3608,SITARA_MCU_MCAL-3606,SITARA_MCU_MCAL-3672
 * Design: MCAL-10202 MCAL-10374 MCAL-10331 MCAL-10194 MCAL-10334 MCAL-10249 MCAL-17672 MCAL-10248
 * Design: MCAL-10185 MCAL-10358 MCAL-10332 MCAL-10322 MCAL-10267 MCAL-10350 MCAL-10171 MCAL-10223
 * Design: MCAL-10325 MCAL-10313 MCAL-10357 MCAL-10167 MCAL-10324 MCAL-10165 MCAL-10311 MCAL-17675
 * Design: MCAL-10184 MCAL-10312 MCAL-10242 MCAL-10353 MCAL-10335 MCAL-10307 MCAL-10365
 */

FUNC(Std_ReturnType, FLS_CODE) Fls_Erase(Fls_AddressType TargetAddress, Fls_LengthType Length)
{
    Std_ReturnType  retVal            = (Std_ReturnType)E_OK;
    Fls_AddressType eraseStartAddress = TargetAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);

#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) && (MEMIF_BUSY == Fls_DrvObj.status))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_BUSY);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) && (E_NOT_OK == Fls_CheckEraseAddressAlignment(eraseStartAddress, Length)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_PARAM_ADDRESS);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) && (E_NOT_OK == Fls_CheckEraseLengthAlignment(eraseStartAddress, Length)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_PARAM_LENGTH);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    if ((retVal == (Std_ReturnType)E_OK) && (Fls_DrvObj.status == MEMIF_IDLE))
    {
        Fls_DrvObj.status        = MEMIF_BUSY;
        Fls_DrvObj.jobResultType = MEMIF_JOB_PENDING;
        Fls_DrvObj.jobType       = FLS_JOB_ERASE;

        /* [ SWS_Fls_00221 ] */
        Fls_DrvObj.flashAddr   = eraseStartAddress;
        Fls_DrvObj.ramAddr     = (uint8 *)NULL_PTR;
        Fls_DrvObj.length      = Length;
        Fls_DrvObj.transferred = (Fls_LengthType)0;

        if (Fls_DrvObj.typeoferase == FLS_SECTOR_ERASE)
        {
            Fls_DrvObj.jobChunkSize = Fls_Config_SFDP_Ptr->eraseCfg.sectorSize;
        }
        else if (Fls_DrvObj.typeoferase == FLS_BLOCK_ERASE)
        {
            Fls_DrvObj.jobChunkSize = Fls_Config_SFDP_Ptr->eraseCfg.blockSize;
        }
        else
        {
            Fls_DrvObj.jobChunkSize = Fls_Config_SFDP_Ptr->flashSize;
        }

#if (STD_ON == FLS_USE_INTERRUPTS)
        Fls_Interrupt_Enable();
#endif
    }
    else
    {
        (retVal = (Std_ReturnType)E_NOT_OK);
    }
    return retVal;
}

/**
 *  \name: Fls_Read
 *
 *  The function Fls_Read shall read from flash memory.
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3608, SITARA_MCU_MCAL-3607, SITARA_MCU_MCAL-3606
 *         SITARA_MCU_MCAL-3626, SITARA_MCU_MCAL-3688, SITARA_MCU_MCAL-3718,
 *         SITARA_MCU_MCAL-3719, SITARA_MCU_MCAL-3720, SITARA_MCU_MCAL-3721,
 *         SITARA_MCU_MCAL-3722, SITARA_MCU_MCAL-3723, SITARA_MCU_MCAL-3725,
 *         SITARA_MCU_MCAL-3726, SITARA_MCU_MCAL-3727, SITARA_MCU_MCAL-3728,
 *         SITARA_MCU_MCAL-3729, SITARA_MCU_MCAL-3730, SITARA_MCU_MCAL-3608,
 *         SITARA_MCU_MCAL-3608
 * Design: MCAL-17675 MCAL-10324 MCAL-10167 MCAL-10325 MCAL-10267 MCAL-10322 MCAL-10358 MCAL-17672
 * MCAL-10249 Design: MCAL-10194 MCAL-10349 MCAL-10234 MCAL-10201 MCAL-10283 MCAL-10220 MCAL-10372
 * MCAL-10289 MCAL-10221 Design: MCAL-10213 MCAL-10217 MCAL-10255 MCAL-10363 MCAL-10163 MCAL-10302
 * MCAL-17697 MCAL-17677 MCAL-10339 Design: MCAL-10294 MCAL-10270 MCAL-17667 MCAL-10198 MCAL-10260
 * MCAL-10200 MCAL-10299 MCAL-10251 MCAL-17673
 */
FUNC(Std_ReturnType, FLS_CODE)
Fls_Read(Fls_AddressType SourceAddress, P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr, Fls_LengthType Length)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == FLS_DEV_ERROR_DETECT)

    retVal = Fls_DetCheckRead(SourceAddress, TargetAddressPtr, Length);

    if (retVal == (Std_ReturnType)E_OK)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        if (Fls_DrvObj.status == MEMIF_IDLE)
        {
            Fls_DrvObj.status        = MEMIF_BUSY;
            Fls_DrvObj.jobResultType = MEMIF_JOB_PENDING;
            Fls_DrvObj.jobType       = FLS_JOB_READ;

            /* [SWS_Fls_00239] */
            Fls_DrvObj.flashAddr = SourceAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);
            /* MISRAC_2012_R.20.1
             * "Reason - The source address needs to stored, for functionality operation. " */
            Fls_DrvObj.ramAddr     = (uint8 *)TargetAddressPtr;
            Fls_DrvObj.length      = Length;
            Fls_DrvObj.transferred = (Fls_LengthType)0;

            Fls_DrvObj.jobChunkSize = Fls_DrvObj.maxReadNormalMode;
#if (STD_ON == FLS_USE_INTERRUPTS)
            Fls_Interrupt_Enable();
#endif
        }
        else
        {
            (retVal = (Std_ReturnType)E_NOT_OK);
        }
    }
    return retVal;
}

#if (STD_ON == FLS_DEV_ERROR_DETECT)
static Std_ReturnType Fls_DetCheckRead(Fls_AddressType SourceAddress,
                                       P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr, Fls_LengthType Length)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    Fls_AddressType ReadStartAddress = SourceAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) && (MEMIF_BUSY == Fls_DrvObj.status))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_BUSY);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) && (NULL_PTR == TargetAddressPtr))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_PARAM_DATA);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) && ((Std_ReturnType)E_NOT_OK == Fls_CheckValidAddress(ReadStartAddress)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_PARAM_ADDRESS);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) &&
        ((Length == (Fls_LengthType)0U) ||
         ((Std_ReturnType)E_NOT_OK == Fls_CheckValidAddress(ReadStartAddress + (Fls_AddressType)Length - 1U))))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_PARAM_LENGTH);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    return retVal;
}

#endif
/**
 *  \name: Fls_Write
 *
 *  The function Fls_Write shall write one or more complete flash pages to the
 *  flash device.
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3608, SITARA_MCU_MCAL-3607, SITARA_MCU_MCAL-3606
 *         SITARA_MCU_MCAL-3625, SITARA_MCU_MCAL-3688, SITARA_MCU_MCAL-3689
 *         SITARA_MCU_MCAL-3690, SITARA_MCU_MCAL-3691, SITARA_MCU_MCAL-3692
 *         SITARA_MCU_MCAL-3694, SITARA_MCU_MCAL-3695, SITARA_MCU_MCAL-3696
 *         SITARA_MCU_MCAL-3698, SITARA_MCU_MCAL-3699, SITARA_MCU_MCAL-3608
 *         SITARA_MCU_MCAL-3606
 * Design: MCAL-10289 MCAL-10194 MCAL-10249 MCAL-17672 MCAL-10358 MCAL-10322 MCAL-10267 MCAL-10325
 * Design: MCAL-10167 MCAL-10324 MCAL-17675 MCAL-10171 MCAL-10229 MCAL-10181 MCAL-10231 MCAL-10211
 * Design: MCAL-10282 MCAL-10273 MCAL-10303 MCAL-10219 MCAL-10177 MCAL-10281 MCAL-10187 MCAL-10204
 * Design: MCAL-17698 MCAL-10264 MCAL-10164 MCAL-10340 MCAL-10354 MCAL-10239 MCAL-17699
 */
FUNC(Std_ReturnType, FLS_CODE)
Fls_Write(Fls_AddressType TargetAddress, P2VAR(const uint8, AUTOMATIC, FLS_APPL_DATA) SourceAddressPtr,
          Fls_LengthType  Length)
{
    Std_ReturnType  retVal = (Std_ReturnType)E_OK;
    /* [SWS_Fls_00226] */
    Fls_AddressType writeStartAddress = TargetAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);

#if (STD_ON == FLS_DEV_ERROR_DETECT)
    retVal = Fls_DetChekWrite(TargetAddress, SourceAddressPtr, Length);

    if (retVal == (Std_ReturnType)E_OK)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        if (Fls_DrvObj.status == MEMIF_IDLE)
        {
            Fls_DrvObj.jobResultType = MEMIF_JOB_PENDING;
            Fls_DrvObj.status        = MEMIF_BUSY;
            Fls_DrvObj.jobType       = FLS_JOB_WRITE;

            Fls_DrvObj.flashAddr   = writeStartAddress;
            Fls_DrvObj.offset      = Fls_DrvObj.flashAddr;
            Fls_DrvObj.ramAddr     = (uint8 *)SourceAddressPtr;
            Fls_DrvObj.length      = Length;
            Fls_DrvObj.transferred = (Fls_LengthType)0;

            Fls_DrvObj.jobChunkSize = Fls_DrvObj.maxWriteNormalMode;
#if (STD_ON == FLS_USE_INTERRUPTS)
            Fls_Interrupt_Enable();
#endif
        }
        else
        {
            (retVal = (Std_ReturnType)E_NOT_OK);
        }
    }
    return retVal;
};

#if (STD_ON == FLS_DEV_ERROR_DETECT)
static Std_ReturnType Fls_DetChekWrite(Fls_AddressType TargetAddress,
                                       P2VAR(const uint8, AUTOMATIC, FLS_APPL_DATA) SourceAddressPtr,
                                       Fls_LengthType Length)
{
    Std_ReturnType  retVal            = (Std_ReturnType)E_OK;
    Fls_AddressType writeStartAddress = TargetAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) && (MEMIF_BUSY == Fls_DrvObj.status))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_BUSY);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) && (NULL_PTR == SourceAddressPtr))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_DATA);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) && ((Std_ReturnType)E_NOT_OK == Fls_CheckValidAddress(writeStartAddress)))
    {
        /* [SWS_Fls_00026] */
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_ADDRESS);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) &&
        ((Length == (Fls_LengthType)0U) ||
         ((Std_ReturnType)E_NOT_OK ==
          Fls_CheckValidAddress(writeStartAddress + (Fls_AddressType)Length - (Fls_AddressType)1U))))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_LENGTH);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    if ((retVal == (Std_ReturnType)E_OK) && ((Std_ReturnType)E_NOT_OK == Fls_CheckPageAlignement(writeStartAddress)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_LENGTH);
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}
#endif

/**
 *  \name: Fls_Compare
 *
 *  The function Fls_Compare shall compare the contents of an area of flash
 *  memory with that of an application data buffer.
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3608, SITARA_MCU_MCAL-3607, SITARA_MCU_MCAL-3606
 *         SITARA_MCU_MCAL-3627, SITARA_MCU_MCAL-3732, SITARA_MCU_MCAL-3733
 *         SITARA_MCU_MCAL-3734, SITARA_MCU_MCAL-3735, SITARA_MCU_MCAL-3736
 *         SITARA_MCU_MCAL-3734, SITARA_MCU_MCAL-3735, SITARA_MCU_MCAL-3736
 *         SITARA_MCU_MCAL-3737, SITARA_MCU_MCAL-3738, SITARA_MCU_MCAL-3739
 *         SITARA_MCU_MCAL-3740, SITARA_MCU_MCAL-3741, SITARA_MCU_MCAL-3742
 *         SITARA_MCU_MCAL-3743, SITARA_MCU_MCAL-3744, SITARA_MCU_MCAL-3608
 *         SITARA_MCU_MCAL-3606, SITARA_MCU_MCAL-3607, SITARA_MCU_MCAL-3608
 * Design: MCAL-10229 MCAL-10171 MCAL-17675 MCAL-10324 MCAL-10325 MCAL-10267
 * Design: MCAL-10322 MCAL-10358 MCAL-17672 MCAL-10249 MCAL-10194 MCAL-10289
 * Design: MCAL-17667 MCAL-10339 MCAL-17697 MCAL-10234 MCAL-10197 MCAL-10360
 * Design: MCAL-10369 MCAL-10300 MCAL-10333 MCAL-10182 MCAL-10319 MCAL-17657
 * Design: MCAL-10209 MCAL-10259 MCAL-10250 MCAL-10306 MCAL-10183 MCAL-10353
 * Design: MCAL-10292 MCAL-10293 MCAL-10373 MCAL-10348 MCAL-10237 MCAL-10174
 */
#if (FLS_COMPARE_API == STD_ON)
FUNC(Std_ReturnType, FLS_CODE)
Fls_Compare(Fls_AddressType SourceAddress, P2VAR(const uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
            Fls_LengthType  Length)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    retVal = Fls_DetCheckCompare(SourceAddress, TargetAddressPtr, Length);

    if (retVal == (Std_ReturnType)E_OK)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        if (Fls_DrvObj.status == MEMIF_IDLE)
        {
            Fls_DrvObj.status        = MEMIF_BUSY;
            Fls_DrvObj.jobResultType = MEMIF_JOB_PENDING;
            Fls_DrvObj.jobType       = FLS_JOB_COMPARE;

            /* [SWS_Fls_00244] */
            Fls_DrvObj.flashAddr   = SourceAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);
            Fls_DrvObj.ramAddr     = (uint8 *)TargetAddressPtr;
            Fls_DrvObj.length      = Length;
            Fls_DrvObj.transferred = (Fls_LengthType)0;

            Fls_DrvObj.jobChunkSize = Fls_DrvObj.maxReadNormalMode;

#if (STD_ON == FLS_USE_INTERRUPTS)
            Fls_Interrupt_Enable();
#endif
        }
        else
        {
            (retVal = (Std_ReturnType)E_NOT_OK);
        }
    }
    return retVal;
}
#endif

#if (STD_ON == FLS_DEV_ERROR_DETECT)
static Std_ReturnType Fls_DetCheckCompare(Fls_AddressType SourceAddress,
                                          P2VAR(const uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
                                          Fls_LengthType Length)
{
    Std_ReturnType  retVal              = (Std_ReturnType)E_OK;
    Fls_AddressType compareStartAddress = SourceAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) && (MEMIF_BUSY == Fls_DrvObj.status))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_BUSY);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) && (NULL_PTR == TargetAddressPtr))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_PARAM_DATA);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) && (E_NOT_OK == Fls_CheckValidAddress(compareStartAddress)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_PARAM_ADDRESS);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) &&
        ((Length == (Fls_LengthType)0U) ||
         ((Std_ReturnType)E_NOT_OK == Fls_CheckValidAddress(compareStartAddress + (Fls_AddressType)Length - 1U))))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_PARAM_LENGTH);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    return retVal;
}
#endif
/**
 *  \name: Fls_BlankCheck
 *
 *  The function Fls_BlankCheck shall verify, whether a given memory area
 *  has been erased.
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3608, SITARA_MCU_MCAL-3607, SITARA_MCU_MCAL-3606
           SITARA_MCU_MCAL-3762, SITARA_MCU_MCAL-3763, SITARA_MCU_MCAL-3764
           SITARA_MCU_MCAL-3765, SITARA_MCU_MCAL-3767, SITARA_MCU_MCAL-3769
           SITARA_MCU_MCAL-3770, SITARA_MCU_MCAL-3608, SITARA_MCU_MCAL-3606
           SITARA_MCU_MCAL-3607
 * Design: MCAL-10210 MCAL-10195 MCAL-17661 MCAL-10275 MCAL-10359 MCAL-10332 MCAL-10350
 * Design: MCAL-10296 MCAL-10366 MCAL-10226 MCAL-10346 MCAL-10222
 */
#if (FLS_BLANK_CHECK_API == STD_ON)
FUNC(Std_ReturnType, FLS_CODE) Fls_BlankCheck(Fls_AddressType TargetAddress, Fls_LengthType Length)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    retVal = Fls_DetCheckBlankCheck(TargetAddress, Length);
    if (retVal == (Std_ReturnType)E_OK)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        if (Fls_DrvObj.status == MEMIF_IDLE)
        {
            Fls_DrvObj.status        = MEMIF_BUSY;
            Fls_DrvObj.jobResultType = MEMIF_JOB_PENDING;
            Fls_DrvObj.jobType       = FLS_JOB_BLANKCHECK;

            /* [SWS_Fls_00379] */
            Fls_DrvObj.flashAddr   = TargetAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);
            Fls_DrvObj.ramAddr     = (uint8 *)NULL_PTR;
            Fls_DrvObj.length      = Length;
            Fls_DrvObj.transferred = (Fls_LengthType)0;

            Fls_DrvObj.jobChunkSize = Fls_DrvObj.maxReadNormalMode;
#if (STD_ON == FLS_USE_INTERRUPTS)
            Fls_Interrupt_Enable();
#endif /* #if (STD_ON == FLS_USE_INTERRUPTS) */
        }
        else
        {
            (retVal = (Std_ReturnType)E_NOT_OK);
        }
    }
    return retVal;
}
#endif /* #if (STD_ON == FLS_BLANK_CHECK_API) */

#if (STD_ON == FLS_DEV_ERROR_DETECT)
static Std_ReturnType Fls_DetCheckBlankCheck(Fls_AddressType TargetAddress, Fls_LengthType Length)
{
    Std_ReturnType  retVal                 = (Std_ReturnType)E_OK;
    Fls_AddressType BlankCheckStartAddress = TargetAddress + (FLS_BASE_ADDRESS & FLS_BASE_ADDRESS_REQ);
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == E_OK) && (MEMIF_BUSY == Fls_DrvObj.status))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK, FLS_E_BUSY);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) && (E_NOT_OK == Fls_CheckValidAddress(BlankCheckStartAddress)))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK, FLS_E_PARAM_ADDRESS);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((retVal == (Std_ReturnType)E_OK) &&
        ((Length == 0U) || (E_NOT_OK == Fls_CheckValidAddress(BlankCheckStartAddress + Length - 1U))))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANK_CHECK, FLS_E_PARAM_LENGTH);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    return retVal;
}
#endif

/**
 *  \name: Fls_GetStatus
 *
 *  The function Fls_GetStatus shall return the FLS module state synchronously
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3710,SITARA_MCU_MCAL-3711,SITARA_MCU_MCAL-3611,SITARA_MCU_MCAL-3630
 * Design: MCAL-10321,MCAL-10352, MCAL-17658
 */
#if (STD_ON == FLS_GET_STATUS_API)
FUNC(MemIf_StatusType, FLS_CODE)
Fls_GetStatus(void)
{
    return Fls_DrvObj.status;
}
#endif /* #if (STD_ON == FLS_GET_STATUS_API) */

/**
 *  \name: Fls_GetJobResult
 *
 *  The function Fls_GetJobResult shall return the result of the
 *    last job synchronously
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3713,SITARA_MCU_MCAL-3714,SITARA_MCU_MCAL-3715,SITARA_MCU_MCAL-3716
 * MCAL-10254 MCAL-10261 MCAL-10326 MCAL-10329 MCAL-10344
 */
#if (FLS_GET_JOB_RESULT_API == STD_ON)
FUNC(MemIf_JobResultType, FLS_CODE)
Fls_GetJobResult(void)
{
    MemIf_JobResultType jobResult = MEMIF_JOB_FAILED;
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_GET_JOB_RESULT, FLS_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        jobResult = Fls_DrvObj.jobResultType;
    }
    return jobResult;
}
#endif /* #if (STD_ON == FLS_GET_JOB_RESULT_API) */

/**
 *  \name: Fls_GetVersionInfo
 *
 *  The function Returns the version information of this module.
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3756, SITARA_MCU_MCAL-3606
 * Design: MCAL-10300, MCAL-17677, MCAL-10168 MCAL-17655
 */
#if (STD_ON == FLS_VERSION_INFO_API)
FUNC(Std_ReturnType, FLS_CODE)
Fls_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA) versioninfo)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_GET_VERSION_INFO, FLS_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        versioninfo->vendorID         = FLS_VENDOR_ID;
        versioninfo->moduleID         = FLS_MODULE_ID;
        versioninfo->sw_major_version = (uint8)FLS_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)FLS_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)FLS_SW_PATCH_VERSION;
    }
    return retVal;
}
#endif /* #if (STD_ON == FLS_VERSION_INFO_API) */

/**
 *  \name: Fls_MainFunction
 *
 *  The function Fls_MainFunction shall perform the processing
 *	of the flash read, write, erase and compare jobs
 *
 */
/*
 * Design: SITARA_MCU_MCAL-3777, SITARA_MCU_MCAL-3779, SITARA_MCU_MCAL-3787
 *         SITARA_MCU_MCAL-3817, SITARA_MCU_MCAL-3818, SITARA_MCU_MCAL-3800
 *         SITARA_MCU_MCAL-3607
 * Design: MCAL-10188, MCAL-10238, MCAL-10256, MCAL-10316, MCAL-10355, MCAL-10361, MCAL-10252,
 * MCAL-10308, MCAL-10345 Design: MCAL-17678, MCAL-17676
 */
FUNC(void, FLS_CODE) Fls_MainFunction(void)
{
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN_FUNCTION, FLS_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        Fls_MainFunctioncall();
    }
}
/*
Design: MCAL-17695 MCAL-17696 MCAL-17664
*/
static void Fls_MainFunctioncall(void)
{
    if (Fls_DrvObj.jobResultType == MEMIF_JOB_PENDING)
    {
        Fls_MainFunction_sub();
    } /* if */
    else
    {
        if (Fls_DrvObj.Fls_JobEndNotification != NULL_PTR)
        {
            /* If not pending job, then return end notification */
            Fls_DrvObj.Fls_JobEndNotification();
        }
    }
}
static void Fls_MainFunction_sub(void)
{
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    TickType startCount = 0U;
#endif
    switch (Fls_DrvObj.jobType)
    {
        case FLS_JOB_COMPARE:
            processJobs(FLS_JOB_COMPARE);
            break;

        case FLS_JOB_ERASE:
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
            (void)GetCounterValue(FLS_OS_COUNTER_ID, &startCount);
#endif

            processJobs(FLS_JOB_ERASE);

#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
            /* Below API can change start time, so use temp variable */
            Fls_TimeoutVerification(startCount);
#endif
            break;
        case FLS_JOB_READ:
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
            (void)GetCounterValue(FLS_OS_COUNTER_ID, &startCount);
#endif

            processJobs(FLS_JOB_READ);

#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
            Fls_TimeoutVerification(startCount);
#endif
            break;
        case FLS_JOB_WRITE:
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
            (void)GetCounterValue(FLS_OS_COUNTER_ID, &startCount);
#endif

            processJobs(FLS_JOB_WRITE);

#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
            Fls_TimeoutVerification(startCount);
#endif
            break;
        case FLS_JOB_BLANKCHECK:
            processJobs(FLS_JOB_BLANKCHECK);
            break;
        case FLS_JOB_NONE:
            break;
        default:
            break;
    } /* switch */
}

/**
 *  \name: Fls_Cancel
 *
 *  The function Fls_Cancel shall cancel an ongoing flash read,
 *  write, erase or compare job synchronously so that directly
 *  after returning from this function a new job can be started
 *
 *  Design : MCAL-7264,MCAL-7270,MCAL-7274,MCAL-7458,MCAL-7299,
 *           MCAL-7319,MCAL-7389,MCAL-7351,MCAL-7349,MCAL-7412,
 *           MCAL-7260,MCAL-7326,MCAL-7346,MCAL-7296,
 *  Design : MCAL-10325 MCAL-10180 MCAL-10215 MCAL-10368 MCAL-10278 MCAL-10302 MCAL-10186
 *  Design : MCAL-10190 MCAL-10176 MCAL-10235 MCAL-17665
 */
#if (FLS_CANCEL_API == STD_ON)
FUNC(void, FLS_CODE) Fls_Cancel(void)
{
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (MEMIF_UNINIT == Fls_DrvObj.status)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_CANCEL, FLS_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        /* Reset internal job processing variables (like address, length and data pointer) */
        Fls_DrvObj.flashAddr   = 0U;
        Fls_DrvObj.ramAddr     = (uint8 *)NULL_PTR;
        Fls_DrvObj.length      = 0U;
        Fls_DrvObj.transferred = (Fls_LengthType)0U;

        Fls_DrvObj.status  = MEMIF_IDLE;
        Fls_DrvObj.jobType = FLS_JOB_NONE;
        if (Fls_DrvObj.jobResultType == MEMIF_JOB_PENDING)
        {
            Fls_DrvObj.jobResultType = MEMIF_JOB_CANCELED;
        }
        if (Fls_DrvObj.Fls_JobErrorNotification != NULL_PTR)
        {
            Fls_DrvObj.Fls_JobErrorNotification();
        }
    }
}
#endif

/*
 *Design: MCAL-17669 MCAL-17680 MCAL-17692
 */

/**
 *  \name: Fls_SetEraseType
 *
 *  The function Fls_SetEraseType sets the parameters like data size,
 *  data_value, erase type(sector/block/chip),typeoferase for Fls_DrvObj,
 *  which are required in application, based on the erase type parameter
 *  passed to this function while calling from Application.
 *  This function is called from application based on the macros enabled in
 *  application itself.
 *  Implementation of this function is done to allow user to select one or more
 *  erase types based on the requirement.
 */
FUNC(uint32, FLS_CODE) Fls_SetEraseType(Fls_EraseType erasetype)
{
    switch (erasetype)
    {
        case FLS_SECTOR_ERASE:
            Fls_DrvObj.typeoferase = FLS_SECTOR_ERASE;
            sector_or_blocksize    = Fls_Config_SFDP_Ptr->eraseCfg.sectorSize;
            break;
        case FLS_BLOCK_ERASE:
            Fls_DrvObj.typeoferase = FLS_BLOCK_ERASE;
            sector_or_blocksize    = Fls_Config_SFDP_Ptr->eraseCfg.blockSize;
            break;
        case FLS_CHIP_ERASE:
            Fls_DrvObj.typeoferase = FLS_CHIP_ERASE;
            sector_or_blocksize    = Fls_Config_SFDP_Ptr->flashSize;
            break;
        default:
            Fls_DrvObj.typeoferase = FLS_SECTOR_ERASE;
            sector_or_blocksize    = Fls_Config_SFDP_Ptr->eraseCfg.sectorSize;
            break;
    }
    return sector_or_blocksize;
}

#if (STD_ON == FLS_SETMODE_API)
FUNC(void, FLS_CODE) Fls_SetMode(MemIf_ModeType Mode)
{
    (void)Mode;
    return;
}
#endif

#if (STD_ON == FLS_REGISTER_READBACK_API)
FUNC(Std_ReturnType, FLS_CODE)
Fls_RegisterReadback(P2VAR(Fls_RegisterReadbackType, AUTOMATIC, FLS_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = E_OK;
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (Fls_DrvObj.status == MEMIF_UNINIT)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_REGISTERREADBACK, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (NULL_PTR == RegRbPtr)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_REGISTERREADBACK, FLS_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (retVal == E_OK)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        Fls_Qspi_RegisterReadback(RegRbPtr);
    }
    return (retVal);
}
#endif

#ifdef FLS_OSPI_CTRL_BASE_ADDR
FUNC(Std_ReturnType, FLS_CODE) Fls_Set3ByteAddressMode(void)
{
    Std_ReturnType retVal = E_NOT_OK;
    retVal                = Fls_OspiSet3ByteAddress();

    return retVal;
}
#endif

#ifdef FLS_OSPI_CTRL_BASE_ADDR
FUNC(Std_ReturnType, FLS_CODE) Fls_setResetPinMode(Fls_ResetPinMode pinMode)
{
    Std_ReturnType retVal = E_NOT_OK;
    retVal                = Fls_OspiSetResetPinMode(pinMode);

    return retVal;
}
#endif

#if (STD_ON == FLS_OSPI_PHY_ENABLE)
FUNC(Std_ReturnType, FLS_CODE) Fls_PhyEnable(void)
{
    Std_ReturnType retVal = E_OK;
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (Fls_DrvObj.status == MEMIF_UNINIT)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_REGISTERREADBACK, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (retVal == E_OK)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        if (Fls_PhyStatus == E_OK)
        {
            Fls_Ospi_phy_enable();
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}

FUNC(void, FLS_CODE) Fls_PhyDisable(void)
{
    Std_ReturnType retVal = E_OK;
#if (STD_ON == FLS_DEV_ERROR_DETECT)
    if (Fls_DrvObj.status == MEMIF_UNINIT)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_REGISTERREADBACK, FLS_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (retVal == E_OK)
#endif /* #if (STD_ON == FLS_DEV_ERROR_DETECT) */
    {
        Fls_Ospi_phy_disable();
    }
}
#endif /* #if (STD_ON == FLS_OSPI_PHY_ENABLE) */

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
