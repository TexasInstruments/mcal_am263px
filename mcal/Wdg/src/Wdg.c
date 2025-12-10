/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Wdg.c
 *
 *  \brief    This file contains implementation of the Internal Watchdog MCAL
 *            driver
 */
/*
 *Design: MCAL-15068, MCAL-15011, MCAL-15071, MCAL-15078, MCAL-15012, MCAL-15069, MCAL-15074,
 *MCAL-15077, MCAL-15025, MCAL-15032 , MCAL-15022, MCAL-14913, MCAL-14914, MCAL-14915, MCAL-14916,
 *MCAL-14917, MCAL-14918, MCAL-14919, MCAL-14920, MCAL-14921, MCAL-14922, MCAL-14923, MCAL-14924,
 *MCAL-14925, MCAL-14926, MCAL-14927, MCAL-14928, MCAL-14929, MCAL-14930, MCAL-14931, MCAL-14932,
 *MCAL-14933, MCAL-15023
 */
/* Common Design ID's */
/*
*Design:  MCAL-15021, MCAL-14934, MCAL-14935, MCAL-14936, MCAL-14937, MCAL-14938, MCAL-14939,
MCAL-15072

*/

#define WDG_SOURCE

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Wdg.h"
#include "Wdg_Cbk.h"
#include "Dem.h"
#include "Wdg_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* AUTOSAR version information check has to match definition in header file */
#if ((WDG_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (WDG_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (WDG_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "WDG: AUTOSAR Version Numbers of WDG are different"
#endif

/* vendor specific version information is BCD coded */
#if ((WDG_SW_MAJOR_VERSION != (10U)) || (WDG_SW_MINOR_VERSION != (2U)))
#error "Version numbers of Wdg.c and Wdg.h are inconsistent!"
#endif

#if ((WDG_CFG_MAJOR_VERSION != (10U)) || (WDG_CFG_MINOR_VERSION != (2U)))
#error "Version numbers of Wdg.c and Wdg_Cfg.h are inconsistent!"
#endif

#define WDG_MHZ_TO_KHZ ((uint32)1000)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Wdg_resetDrvObj(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define WDG_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Wdg_MemMap.h"
VAR(Wdg_DriverObjType, WDG_VAR_ZERO_INIT) Wdg_DrvObj;
#define WDG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Wdg_MemMap.h"

#define WDG_START_SEC_VAR_INIT_UNSPECIFIED
#include "Wdg_MemMap.h"
#if (STD_ON == WDG_DEV_ERROR_DETECT)
/** \brief WDG driver status */
volatile VAR(Wdg_StatusType, WDG_VAR_ZERO_INIT) Wdg_DrvStatus = WDG_UNINIT;
#endif
#define WDG_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Wdg_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define WDG_START_SEC_CODE
#include "Wdg_MemMap.h"
/******************************************************************************
 *  Wdg_GetVersionInfo
 ******************************************************************************/
/*
 *Design: MCAL-14964, MCAL-14965
 */
#if (STD_ON == WDG_GET_VERSION_INFO_API)

FUNC(void, WDG_CODE) Wdg_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        (void)Wdg_reportDetError(WDG_API_GET_VERSION_INFO, WDG_E_PARAM_POINTER);
    }
    else
#endif
    {
        versioninfo->vendorID         = (WDG_VENDOR_ID);
        versioninfo->moduleID         = (WDG_MODULE_ID);
        versioninfo->sw_major_version = (uint8)(WDG_SW_MAJOR_VERSION);
        versioninfo->sw_minor_version = (uint8)(WDG_SW_MINOR_VERSION);
        versioninfo->sw_patch_version = (uint8)(WDG_SW_PATCH_VERSION);
    }

    return;
}
#endif /* STD_ON == WDG_GET_VERSION_INFO_API */

/******************************************************************************
 *  Wdg_Init
 ******************************************************************************/
/*
 *Design: MCAL-14940, MCAL-14941, MCAL-14942 , MCAL-14943  , MCAL-14945 , MCAL-14946, MCAL-14947 ,
 *MCAL-15067, MCAL-15015 , MCAL-15017
 */
FUNC(void, WDG_CODE) Wdg_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    Std_ReturnType        retVal;
    const Wdg_ConfigType *Wdg_Config_pt = (Wdg_ConfigType *)NULL_PTR;

#if (STD_ON == WDG_VARIANT_PRE_COMPILE)
    if (NULL_PTR == ConfigPtr)
    {
        Wdg_Config_pt = &WDG_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == WDG_VARIANT_PRE_COMPILE) */
#if (STD_ON == WDG_VARIANT_POST_BUILD)
    if (NULL_PTR != ConfigPtr)
    {
        Wdg_Config_pt = ConfigPtr;
    }
#endif /* (STD_ON == WDG_VARIANT_POST_BUILD) */
#if (STD_ON == WDG_VARIANT_LINK_TIME)
    if (NULL_PTR != ConfigPtr)
    {
        Wdg_Config_pt = ConfigPtr;
    }
#endif /* (STD_ON == WDG_VARIANT_LINK_TIME) */
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    if (NULL_PTR == Wdg_Config_pt)
    {
        (void)Wdg_reportDetError(WDG_API_INIT, WDG_E_PARAM_POINTER);
    }
    else
#endif
    {
#if (WDG_DISABLE_ALLOWED != STD_ON)
        if (WDGIF_OFF_MODE == Wdg_Config_pt->defaultMode)
        {
#ifdef WDG_E_DISABLE_REJECTED
            Wdg_reportDemError(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_FAILED);
#endif
        }
        else
#endif
        {
            retVal = Wdg_platformInit(Wdg_Config_pt);
            if (((Std_ReturnType)E_OK) != retVal)
            {
#ifdef WDG_E_MODE_FAILED
                /* Mode not supported */
                Wdg_reportDemError(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
            }
            else
            {
#ifdef WDG_E_MODE_FAILED
                Wdg_reportDemError(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_PASSED);
#endif

                Wdg_DrvObj.baseAddr = Wdg_getWdgBaseAddr(Wdg_Config_pt->instanceId);
                /* Set Initial Trigger Timeout */
                Wdg_DrvObj.timeOutCounter = Wdg_Config_pt->initialTimeOut;
                /* Save initial watchdog counter value */
                Wdg_DrvObj.counterRef = Wdg_getCurrentDownCounter(Wdg_DrvObj.baseAddr);
                /* Save the configured Mode type & Mode configuration settings
                    to global object*/
                Wdg_DrvObj.previousMode = Wdg_Config_pt->defaultMode;
                Wdg_DrvObj.slowModeCfg  = Wdg_Config_pt->slowModeCfg;
                Wdg_DrvObj.fastModeCfg  = Wdg_Config_pt->fastModeCfg;
                /*MSS_RCM Reset Address of Wdg*/
                Wdg_DrvObj.WdgResetAddress = Wdg_getWdgResetAddr(Wdg_Config_pt->instanceId);
                /* Enable DWD */
                Wdg_counterEnable(Wdg_DrvObj.baseAddr);
#if (STD_ON == WDG_DEV_ERROR_DETECT)
                Wdg_DrvStatus = WDG_IDLE;
#endif
            }
        }
    }

    return;
}

/******************************************************************************
 *  Wdg_SetMode
 ******************************************************************************/
/*
 *Design: MCAL-14948, MCAL-14949, MCAL-14950, MCAL-14951, MCAL-14952, MCAL-14953, MCAL-14954,
 *MCAL-14955, MCAL-14956, MCAL-14957 , MCAL-15014 , MCAL-15070 , MCAL-15079
 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_SetMode(WdgIf_ModeType Mode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

#if (STD_ON == WDG_DEV_ERROR_DETECT)
    if (WDG_IDLE != Wdg_DrvStatus)
    {
        (void)Wdg_reportDetError(WDG_API_SET_MODE, WDG_E_DRIVER_STATE);
    }
    else if (Mode > WDGIF_FAST_MODE)
    {
        (void)Wdg_reportDetError(WDG_API_SET_MODE, WDG_E_PARAM_MODE);
    }
    else
#endif
    {
#if (STD_ON == WDG_DEV_ERROR_DETECT)
        /* Set driver status as busy */
        Wdg_DrvStatus = WDG_BUSY;
#endif
#if (WDG_DISABLE_ALLOWED != STD_ON)
        if (WDGIF_OFF_MODE == Mode)
        {
#ifdef WDG_E_DISABLE_REJECTED
            Wdg_reportDemError(WDG_E_DISABLE_REJECTED, DEM_EVENT_STATUS_FAILED);
#endif
        }
        else
#endif
        {
            retVal = Wdg_SetModeConfig(Mode);

            if (((Std_ReturnType)E_OK) != retVal)
            {
#if (STD_ON == WDG_DEV_ERROR_DETECT)
                (void)Wdg_reportDetError(WDG_API_SET_MODE, WDG_E_PARAM_MODE);
#endif

#ifdef WDG_E_MODE_FAILED
                /* Mode not supported */
                (void)Dem_SetEventStatus(WDG_E_MODE_FAILED, DEM_EVENT_STATUS_FAILED);
#endif
            }
            else
            {
                Wdg_DrvObj.previousMode = Mode;
            }
        }
#if (STD_ON == WDG_DEV_ERROR_DETECT)
        /* Set driver status as idle */
        Wdg_DrvStatus = WDG_IDLE;
#endif
    }

    return (retVal);
}

/******************************************************************************
 *  Wdg_SetTriggerCondition
 ******************************************************************************/
/*
 *Design: MCAL-14958, MCAL-14959, MCAL-14960, MCAL-14961, MCAL-14962, MCAL-14963 , MCAL-15027 ,
 *MCAL-15028, MCAL-15030 , MCAL-15031
 */
FUNC(void, WDG_CODE) Wdg_SetTriggerCondition(uint16 timeout)
{
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    if ((uint16)WDG_MAX_TIMEOUT < (uint16)timeout)
    {
        /* API is being called with an invalid timeout value */
        (void)Wdg_reportDetError(WDG_SET_TRIGGER_CONDITION, WDG_E_PARAM_TIMEOUT);
    }
    else
#endif
    {
        if (0U == timeout)
        {
            /* Skip force resetting the device only when this compilation flag is set to OFF */
            if (Wdg_DrvObj.timeOutCounter != 0U)
            {
                /* Update trigger condition */
                Wdg_DrvObj.timeOutCounter = timeout;
#if (STD_OFF == WDG_SKIP_FORCE_RESET)
                /* Cause a WD reset if timeout is set as 0 */
                Wdg_generateSysReset(Wdg_DrvObj.baseAddr);
#endif
            }
        }
        else
        {
            /* Update trigger condition */
            Wdg_DrvObj.timeOutCounter = timeout;
            /* Save current watchdog counter value */
            Wdg_DrvObj.counterRef = Wdg_getCurrentDownCounter(Wdg_DrvObj.baseAddr);
            Wdg_ProcessTimeout(timeout);
            Wdg_Trigger();
        }
    }

    return;
}

/******************************************************************************
 *  Wdg_Trigger
 ******************************************************************************/
/*
 *Design: MCAL-15026, MCAL-15075 , MCAL-15024 , 	MCAL-15016 , MCAL-15076
 */
FUNC(void, WDG_CODE) Wdg_Trigger(void)
{
#if (STD_ON == WDG_DEV_ERROR_DETECT)
    /* Check if driver already initialized */
    if (WDG_IDLE != Wdg_DrvStatus)
    {
        (void)Wdg_reportDetError(WDG_API_TRIGGER, WDG_E_DRIVER_STATE);
    }
    else
#endif
    {
        Wdg_resetDrvObj();

#if (STD_ON == WDG_DEV_ERROR_DETECT)
        /* Set driver status as idle */
        Wdg_DrvStatus = WDG_IDLE;
#endif
    }
}

/******************************************************************************
 *  Wdg_resetDrvObj
 ******************************************************************************/
static void Wdg_resetDrvObj(void)
{
    uint32 elapsedTime;
    /* If Timeout counter hasn't expired, continue trigger routine */
    if (0U < Wdg_DrvObj.timeOutCounter)
    {
        /* Counter reference shall not be smaller than current WDW
         * counter */
        elapsedTime = Wdg_getCurrentDownCounter(Wdg_DrvObj.baseAddr);

        if (Wdg_DrvObj.counterRef > elapsedTime)
        {
            /* Calculate elapsed time since last trigger invocation */
            elapsedTime = Wdg_DrvObj.counterRef - elapsedTime;
            /* Convert elapsed time to milliseconds */
            elapsedTime = (elapsedTime / (WDG_RTI_FREQUENCY * WDG_MHZ_TO_KHZ));
            /* Elapsed time is smaller than the last received trigger
             * condition */
            if (Wdg_DrvObj.timeOutCounter > elapsedTime)
            {
                /* Write key sequence to reload the DWD */
                Wdg_service(Wdg_DrvObj.baseAddr);
                /* Decrement Counter */
                Wdg_DrvObj.timeOutCounter = (Wdg_DrvObj.timeOutCounter - elapsedTime);
                /* update the counter reference */
                Wdg_DrvObj.counterRef = Wdg_getReloadValue(Wdg_DrvObj.baseAddr);
            }
            else
            {
                /* Elapsed time is larger than last received trigger
                 * condition, stop servicing watchdog */
                Wdg_DrvObj.timeOutCounter = 0U;
            }
        }
    }
}

#if (STD_ON == WDG_REGISTER_READBACK_API)
/******************************************************************************
 *  Wdg_RegisterReadback
 ******************************************************************************/
/*
 *Design: MCAL-14966
 */
FUNC(Std_ReturnType, WDG_CODE)
Wdg_RegisterReadback(P2VAR(Wdg_RegisterReadbackType, AUTOMATIC, WDG_APPL_DATA) RegisterReadbackPtr)
{
    Std_ReturnType register_readback_return = E_NOT_OK;

    if (NULL_PTR == RegisterReadbackPtr)
    {
        /* Do nothing. Incorrect pointer. */
    }
    else
    {
        Wdg_HWRegisterReadback(RegisterReadbackPtr);
        register_readback_return = E_OK;
    }

    return (register_readback_return);
}
#endif /*STD_ON == WDG_REGISTER_READBACK_API*/

void Wdg_reportDemError(Dem_EventIdType eventId, Dem_EventStatusType eventStatus)
{
#ifdef MCAL_DYNAMIC_BUILD
    Dem_SetEventStatus(eventId, eventStatus);
#else
#ifdef WDG_E_DISABLE_REJECTED
    if (eventId == WDG_E_DISABLE_REJECTED)
    {
        /* WDG can't be disabled */
        (void)Dem_SetEventStatus(eventId, eventStatus);
    }
#endif
#ifdef WDG_E_MODE_FAILED
    if (eventId == WDG_E_MODE_FAILED)
    {
        /* WDG can't be disabled */
        (void)Dem_SetEventStatus(eventId, eventStatus);
    }
#endif
#endif

    return;
}

#define WDG_STOP_SEC_CODE
#include "Wdg_MemMap.h"
