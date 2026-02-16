/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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

/**
 *  \file     Mcu.c
 *
 */
/* ---------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ---------------------------------------------------------------------------
 *         File:  Mcu.c
 *      Project:  TI Sitara MCU MCAL Drivers
 *       Module:  MCU Driver
 *
 *  Description:  The MCU driver provides services for basic microcontroller
 *                initialization,power down functionality,reset and
 *                microcontroller specific functions required by other MCAL
 *                software modules.
 *
 *
 ******************************************************************************/

#define MCU_SOURCE
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Mcu.h"
#include "SchM_Mcu.h"
#if (STD_ON == MCU_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "Dem.h"
#include "Os.h"
#include "Mcu_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((MCU_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (MCU_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (MCU_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "MCU: AUTOSAR Version Numbers of MCU are different"
#endif

/* vendor specific version information is BCD coded */
#if ((MCU_SW_MAJOR_VERSION != (10U)) || (MCU_SW_MINOR_VERSION != (2U)))
#error "Version numbers of Mcu.c and Mcu.h are inconsistent!"
#endif

#if ((MCU_CFG_MAJOR_VERSION != (10U)) || (MCU_CFG_MINOR_VERSION != (2U)))
#error "Version numbers of Mcu.c and Mcu_Cfg.h are inconsistent!"
#endif

/* Software Reset Mask */
#define MCU_PERFORM_RESET_MASK ((uint32)0x00008000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Memory mapping, done via MemMap.h Variables that are not initialized */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"
/** \brief MCU driver object */
P2CONST(Mcu_ConfigType, MCU_DATA, MCU_PBCFG) Mcu_DrvObj = (Mcu_ConfigType *)NULL_PTR;
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_INIT_8
/*TI_INSPECTED 338 S: JUSTIFICATION_14 */
#include "Mcu_MemMap.h"
/** \brief MCU driver status */
static VAR(volatile uint8, MCU_VAR_ZERO_INIT) Mcu_DrvStatus = MCU_STATE_UNINIT;
#define MCU_STOP_SEC_VAR_INIT_8
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_INIT_8
/*TI_INSPECTED 338 S: JUSTIFICATION_14 */
#include "Mcu_MemMap.h"
/** \brief MCU PLL status object */
VAR(volatile uint8, MCU_VAR_ZERO_INIT) Mcu_PllStatus = MCU_STATE_UNINIT;
#define MCU_STOP_SEC_VAR_INIT_8
#include "Mcu_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
/*
 *Design: MCAL-14379
 */
#if (STD_ON == MCU_GET_VERSION_INFO_API)
FUNC(void, MCU_CODE) Mcu_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        /* API is being called with invalid config param */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_GET_VERSION_INFO, MCU_E_PARAM_POINTER);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        versioninfo->vendorID         = (MCU_VENDOR_ID);
        versioninfo->moduleID         = (MCU_MODULE_ID);
        versioninfo->sw_major_version = (uint8)(MCU_SW_MAJOR_VERSION);
        versioninfo->sw_minor_version = (uint8)(MCU_SW_MINOR_VERSION);
        versioninfo->sw_patch_version = (uint8)(MCU_SW_PATCH_VERSION);
    }
} /* Mcu_GetVersionInfo()*/
#endif /* STD_ON == MCU_GET_VERSION_INFO_API */
/*
 *Design: MCAL-14325, MCAL-14329, MCAL-14331, MCAL-14335, MCAL-14338, MCAL-14343, MCAL-14345,
 *MCAL-22633, MCAL-14312, ,MCAL-14304
 */
FUNC(void, MCU_CODE) Mcu_Init(P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_PBCFG) ConfigPtr)
{
    const Mcu_ConfigType *CfgPtr = (Mcu_ConfigType *)NULL_PTR; /* Config pointer initialised with NULL_PTR */
#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    if (NULL_PTR == ConfigPtr)
    {
        /* Assigning module configuration to Config pointer incase of Pre Compile variant */
        CfgPtr = &MCU_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == MCU_VARIANT_PRE_COMPILE) */
#if (STD_ON == MCU_VARIANT_POST_BUILD)
    if (NULL_PTR != ConfigPtr)
    {
        /* Assigning passed module configuration to Config pointer incase of Post Build variant */
        CfgPtr = ConfigPtr;
    }
#endif /* (STD_ON == MCU_VARIANT_POST_BUILD) */
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (NULL_PTR == CfgPtr)
    {
        /* API is being called with invalid config param */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT, MCU_E_PARAM_CONFIG);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        Mcu_DrvObj = CfgPtr;            /* Copying the configuration to driver Object */
        Mcu_SystemInit();               /* Invoking API for clock and PLL initialization */
        Mcu_DrvStatus = MCU_STATE_INIT; /* DrvStatus is updated after initialization */
    }
    return;
}
/*
 *Design: MCAL-14359, MCAL-14360, MCAL-14361, MCAL-14362, MCAL-14363
 */
#if (STD_ON == MCU_INIT_CLOCK_API)
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitClock(Mcu_ClockType ClockSetting)
{
    VAR(Std_ReturnType, MCU_VAR)
    InitClock_Return = E_NOT_OK; /* Variable to store return value of Mcu_InitClock API */
#if (STD_ON == MCU_DEV_ERROR_DETECT)

    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT_CLOCK, MCU_E_UNINIT);
    }
    else if (ClockSetting >= Mcu_DrvObj->Mcu_NumberOfClockConfig)
    {
        /* API is being called with invalid clockid param */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT_CLOCK, MCU_E_PARAM_CLOCK);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        /* Mcu_ClockSetSource will return E_OK if clock configurationis initialised successfully */
        InitClock_Return = Mcu_ClockSetSource(Mcu_DrvObj->Mcu_ClockConfig[ClockSetting].Mcu_ClockModuleId,
                                              Mcu_DrvObj->Mcu_ClockConfig[ClockSetting].Mcu_ClockSourceId,
                                              Mcu_DrvObj->Mcu_ClockConfig[ClockSetting].Mcu_ClockDiv,
                                              Mcu_DrvObj->Mcu_ClockConfig[ClockSetting].Mcu_InitCfg);
    }
    return (InitClock_Return);
} /* end of the Mcu_InitClock */
#endif /* STD_ON == MCU_INIT_CLOCK_API */

/*
 *Design: MCAL-14436, MCAL-14437, MCAL-14438, MCAL-14439, MCAL-14440, MCAL-14441, MCAL-22633
 */
#if (STD_OFF == MCU_NO_PLL)
FUNC(Std_ReturnType, MCU_CODE) Mcu_DistributePllClock(void)
{
    VAR(Std_ReturnType, MCU_VAR)
    InitClock_Return = E_OK; /* Variable to store return value of Mcu_DistributePllClock API */

#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_DISTRIBUTE_PLL_CLOCK, MCU_E_UNINIT);
        InitClock_Return = E_NOT_OK;
    }
    else
    {
        if (MCU_PLL_LOCKED != Mcu_GetPllStatus())
        {
            /* API is being called before PLL is locked */
            (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_DISTRIBUTE_PLL_CLOCK, MCU_E_PLL_NOT_LOCKED);
            InitClock_Return = E_NOT_OK;
        }
        else
        {
            if (Mcu_PllStatus != MCU_STATE_INIT) /* Checking whether PLL is already initialised or not */
            {
                (void)Mcu_PLLInitAll(Mcu_DrvObj); /* Invoking PLL init API */
                Mcu_PllStatus = MCU_STATE_INIT;   /* Updating PLL status object as initialized */
            }
        }
    }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    return (InitClock_Return);

} /*end of the Mcu_DistributePllClock()*/
#endif /* STD_OFF == MCU_NO_PLL */
/*
 *Design: MCAL-14355, MCAL-14356,MCAL-14284, MCAL-14357
 */
#if (STD_ON == MCU_INIT_RAM_API)
FUNC(Std_ReturnType, MCU_CODE) Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
    /* Variable to store return value of Mcu_InitRamSection API */
    VAR(Std_ReturnType, MCU_VAR) Init_Ram_Section_Return = (Std_ReturnType)E_NOT_OK;
    /* Local word counter */
    VAR(uint32, MCU_VAR) Mcu_RamBytes;
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT_RAMSECTION, MCU_E_UNINIT);
    }
    else if (RamSection >= Mcu_DrvObj->Mcu_NumberOfRamSectors)
    {
        /* API is being called with invalid ramsect param */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT_RAMSECTION, MCU_E_PARAM_RAMSECTION);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        /* RAM destination pointer */
        P2VAR(uint8, AUTOMATIC, MCU_APPL_DATA) Mcu_RamDestination = (uint8 *)NULL_PTR;
        /* Load the RAM Section Base address from the configuration */
        Mcu_RamDestination = Mcu_DrvObj->Mcu_ConfigRamSection[RamSection].Mcu_RamSectionBaseAddress;
        /* Load the RamSection Size */
        Mcu_RamBytes = Mcu_DrvObj->Mcu_ConfigRamSection[RamSection].Mcu_RamSectionBytes;
        while (0U < Mcu_RamBytes)
        {
            /* Initialize the RAM with selected default value */
            *Mcu_RamDestination = Mcu_DrvObj->Mcu_ConfigRamSection[RamSection].Mcu_RamDefaultValue;
            /* Point to next address*/
            Mcu_RamDestination++;
            /* Reduce Byte counter */
            Mcu_RamBytes--;
        }
        Init_Ram_Section_Return = (Std_ReturnType)E_OK;
    }

    return (Init_Ram_Section_Return);
}
#endif /* STD_ON == MCU_INIT_RAM_API */
/*
 *Design: MCAL-14364, MCAL-14365, MCAL-14366, MCAL-14367
 */
FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_GetPllStatus(void)
{
    VAR(Mcu_PllStatusType, MCU_VAR)
    Pll_Status = MCU_PLL_STATUS_UNDEFINED; /* Variable to store return value of Mcu_GetPllStatus API */
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_GET_PLL_STATUS, MCU_E_UNINIT);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
#if (STD_ON == MCU_NO_PLL)
        /* Requirements: SWS_Mcu_00206*/
        /* PLL is not enabled so the status will be undefined */
        Pll_Status = MCU_PLL_STATUS_UNDEFINED;
#else
        /* PLL is enabled ,status can be retrieved from Mcu_GetPllLockStatus */
        Pll_Status = Mcu_GetPllLockStatus();
#endif /* STD_ON == MCU_NO_PLL */
    }

    /* Requirements: SWS_Mcu_00008 */
    return (Pll_Status);
} /* end of Mcu_GetPllStatus */
/*
 *Design: MCAL-14368, MCAL-14369, MCAL-14370, MCAL-14307
 */
FUNC(Mcu_ResetType, MCU_CODE) Mcu_GetResetReason(void)
{
    VAR(Mcu_ResetType, MCU_VAR)
    Reset_Reason = MCU_RESET_UNDEFINED; /* Variable to store return value of Mcu_GetResetReason API */
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_GET_RESET_REASON, MCU_E_UNINIT);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        /* Requirements: SWS_Mcu_00005 */
        /* Mcu_GetPlatformResetReason returns valid reset types */
        Reset_Reason = Mcu_GetPlatformResetReason();
    }

    return (Reset_Reason);
} /* end of Mcu_GetResetReason() */
/*
 *Design: MCAL-14383, MCAL-14384, MCAL-14385, MCAL-14283
 */
FUNC(void, MCU_CODE) Mcu_SetMode(Mcu_ModeType McuMode)
{
    (void)McuMode;
#if (STD_ON == MCU_DEV_ERROR_DETECT)

    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_SET_MODE, MCU_E_UNINIT);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        /* Do nothing. Invalid power mode */
    }
} /*end of the Mcu_SetMode()*/
/*
 *Design: MCAL-14371, MCAL-14372, MCAL-14373
 */
FUNC(Mcu_RawResetType, MCU_CODE) Mcu_GetResetRawValue(void)
{
    VAR(Mcu_RawResetType, MCU_VAR)
    Reset_Raw_Value = MCU_ERRORRST_MASK; /* Variable to store return value of Mcu_GetResetRawValue API */
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        Reset_Raw_Value = MCU_ERRORRST_MASK;
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_GET_RESET_RAW_VALUE, MCU_E_UNINIT);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        /* Mcu_GetPlatformRawResetReason returns reset reason, stored in SPARE_RW0 by startup code
         */
        Reset_Raw_Value = Mcu_GetPlatformRawResetReason();
    }
    return (Reset_Raw_Value);
} /*end of the Mcu_ResetRawValue()*/

/* Requirements: SWS_Mcu_00209 */
/*
 *Design: MCAL-14380, MCAL-14381, MCAL-14382
 */
#if (STD_ON == MCU_GET_RAM_STATE_API)
FUNC(Mcu_RamStateType, MCU_CODE) Mcu_GetRamState(void)
{
    VAR(Mcu_RamStateType, MCU_VAR)
    GetRamState_Return = MCU_RAMSTATE_INVALID; /* Variable to store return value of Mcu_GetRamState API */
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_GET_RAM_STATE, MCU_E_UNINIT);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        GetRamState_Return = MCU_RAMSTATE_VALID;
    }
    return (GetRamState_Return);
} /*end of the Mcu_GetRamState()*/
#endif /*STD_ON == MCU_GET_RAM_STATE_API */
/*
 *Design: MCAL-14374, MCAL-14375, MCAL-14376, MCAL-14377, MCAL-14378, MCAL-14305
 */
#if (STD_ON == MCU_PERFORM_RESET_API)
FUNC(void, MCU_CODE) Mcu_PerformReset(void)
{
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PERFORM_RESET, MCU_E_UNINIT);
    }
    else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    {
        VAR(uint8, MCU_VAR) Reset_Mode;

        /* Perform a sofware reset */
        SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0();
        /* Copying resetmode (warm reset/cold reset) configured in driver configuration */
        Reset_Mode = Mcu_DrvObj->Mcu_ResetMode;
        /* Passing resetmode to perform soft reset as per resetmode */
        Mcu_PerformSoftSysReset(Reset_Mode);
        SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0();
    }
} /*end of the Mcu_PerformReset()*/
#endif /* STD_ON == MCU_PERFORM_RESET_API */

/*
 *Design: MCAL-14415, MCAL-22677
 */
#if (STD_ON == MCU_REGISTER_READBACK_API)

FUNC(Std_ReturnType, MCU_CODE)
Mcu_RegisterReadback(P2VAR(Mcu_RegisterReadbackType, AUTOMATIC, MCU_APPL_DATA) RegisterReadbackPtr)
{
    VAR(Std_ReturnType, MCU_VAR)
    RetVal = (Std_ReturnType)E_NOT_OK; /* Variable to store return value of Mcu_RegisterReadback API */

#if (STD_ON == MCU_DEV_ERROR_DETECT)
    if (Mcu_DrvStatus == MCU_STATE_UNINIT)
    {
        /* API is being called before calling Mcu_Init */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_REGISTER_READBACK, MCU_E_UNINIT);
    }
    else if (NULL_PTR == RegisterReadbackPtr)
    {
        /* API is being called with invalid ramsect param */
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_REGISTER_READBACK, MCU_E_PARAM_POINTER);
    }
    else
    {
#endif /* #if (STD_ON == MCU_DEV_ERROR_DETECT) */

        Mcu_HWRegisterReadback(RegisterReadbackPtr);
        RetVal = (Std_ReturnType)E_OK;

#if (STD_ON == MCU_DEV_ERROR_DETECT)
    }
#endif /* #if (STD_ON == MCU_DEV_ERROR_DETECT) */

    return RetVal;
}
#endif /* STD_ON == MCU_REGISTER_READBACK_API */

/*
Design: MCAL-21384
*/

FUNC(void, MCU_CODE) Mcu_DeInit(void)
{
    /*Disable PWM */
    Mcu_DisableEpwmTbClk();
    Mcu_DrvStatus = MCU_STATE_UNINIT;
}
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
