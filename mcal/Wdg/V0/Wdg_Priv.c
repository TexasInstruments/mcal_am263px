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
 *  \file     Wdg_Priv.c
 *
 */

/* ========================================================================== */
/*                         Include Files                                      */
/* ========================================================================== */
#include "soc.h"
#include "hw_ctrl_core.h"
#include "hal_stdtypes.h"
#include "Wdg_Priv.h"
#define WDG_START_SEC_CODE
#include "Wdg_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define WDG_STOP_SEC_CODE
#include "Wdg_MemMap.h"

/* ========================================================================== */
/*                         Macros & Typedefs                                  */
/* ========================================================================== */

#define WDG_DWWDPRLD_MULTIPLIER_SHIFT (13U)

/* Watchdog Triggers */
#define WDG_TRIGGER_FIRST_KEY  ((uint32)0xE51AU)
#define WDG_TRIGGER_SECOND_KEY ((uint32)0xA35CU)
#define WDG_TRIGGER_RESET_KEY  ((uint32)0x2345U)

/* Digital Watchdog Control */
#define WDG_CTL_ENABLED ((uint32)0xA98559DAU)

#define WDG_STATUS_RESET_VAL (0xFFU)

#define MSS_RCM_LOCK0_KICK0  (0x53209008U)
#define MSS_RCM_LOCK0_KICK1  (0x5320900CU)
#define RCM_KICK0_UNLOCK_VAL (0x01234567U)
#define RCM_KICK1_UNLOCK_VAL (0x0FEDCBA8U)
#define RCM_KICK0_LOCK_VAL   (0x00000000U)
#define RCM_KICK1_LOCK_VAL   (0x00000000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (WDG_DEV_ERROR_DETECT == STD_ON)
static FUNC(uint32, WDG_CODE) Wdg_getNumWdg(void);
#endif
static FUNC(void, WDG_CODE) Wdg_setPreload(uint32 baseAddr, uint32 dwwdPreloadValIn);
static FUNC(void, WDG_CODE) Wdg_setReaction(uint32 baseAddr, uint32 dwwdReaction);
static FUNC(Std_ReturnType, WDG_CODE)
    Wdg_windowConfig(uint32 baseAddr, uint32 dwwdReaction, uint32 dwwdPreloadVal, uint32 dwwdWindowSize);
static FUNC(void, WDG_CODE) Wdg_clearStatus(uint32 baseAddr, uint32 status);

static FUNC(Std_ReturnType, WDG_CODE)
    wdg_platforminit_internal(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);
static FUNC(void, WDG_CODE) Wdg_reset(void);
/* ========================================================================== */
/*                          Global Variables                                  */
/* ========================================================================== */
extern const uint32 Wdg_RTIChannelAddr[WDG_MAX_INSTANCES];
extern const uint32 Wdg_ResetChannelAddr[WDG_MAX_INSTANCES];

/** @fn void dwdInit(rtiBASE_t* rtiBaseAddr, uint16 dwdPreload)
 *   @brief Initialize DWD Expiration Period
 *   @param[in] rtidwdBaseAddr - Base address of Watchdog to be configured
 *   @param[in] dwdPreload DWD Preload value for expiration time.
 *              - Texp = (dwdPreload +1) / RTICLK
 *              - n: Divide by n + 1
 *
 *   This function can be called to set the DWD expiration
 *
 */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define WDG_START_SEC_CODE
#include "Wdg_MemMap.h"

#if (WDG_DEV_ERROR_DETECT == STD_ON)
static FUNC(uint32, WDG_CODE) Wdg_getNumWdg(void)
{
    return (WDG_MAX_INSTANCES);
}
#endif

static FUNC(void, WDG_CODE) Wdg_clearStatus(uint32 baseAddr, uint32 status)
{
    ((rtiBASE_t*)baseAddr)->WDSTATUS = status;
}

static FUNC(void, WDG_CODE) Wdg_setPreload(uint32 baseAddr, uint32 dwwdPreloadValIn)
{
    ((rtiBASE_t*)baseAddr)->DWDPRLD = dwwdPreloadValIn;
}

static FUNC(void, WDG_CODE) Wdg_setReaction(uint32 baseAddr, uint32 dwwdReaction)
{
    /* Configuring Digital Windowed Watchdog Reaction */
    ((rtiBASE_t*)baseAddr)->WWDRXNCTRL = dwwdReaction;
}

static FUNC(Std_ReturnType, WDG_CODE)
    Wdg_windowConfig(uint32 baseAddr, uint32 dwwdReaction, uint32 dwwdPreloadVal, uint32 dwwdWindowSize)
{
    Std_ReturnType configStatus;

    if (WDG_MAX_PRELOAD_VALUE >= dwwdPreloadVal)
    {
        /* Configure window in which watch-dog should be serviced */
        ((rtiBASE_t*)baseAddr)->WWDSIZECTRL = dwwdWindowSize;

        /* Initialize DWD Expiration Period */
        Wdg_setPreload(baseAddr, dwwdPreloadVal);
        /* Configure Digital Windowed Watchdog Reaction */
        Wdg_setReaction(baseAddr, dwwdReaction);

        configStatus = (Std_ReturnType)E_OK;
    }
    else
    {
        configStatus = (Std_ReturnType)E_NOT_OK;
    }

    return (configStatus);
}

/** @fn FUNC(void, WDG_CODE) Wdg_counterEnable(uint32 baseAddr)
 *   @brief Enable DWD
 *   @param[in] baseAddr - Base address of Watchdog to be configured
 *
 *   This function will Enable the DWD counter.
 *
 */
FUNC(void, WDG_CODE) Wdg_counterEnable(uint32 baseAddr)
{
    /* Enable DWWD by writing pre-defined value '0xA98559DA' to RTIDWDCTRL    */
    ((rtiBASE_t*)baseAddr)->DWDCTRL = WDG_CTL_ENABLED;
}

/** @fn FUNC(uint32, MCU_CODE) Wdg_getWdgBaseAddr(uint16 regNum)
 *   @brief Gets the base address of the Watchdog module instance
 *   @param[in] regNum - Watchdog Module instances
 *
 *   This function returns the base address of the Watchdog module instance.
 *
 */
FUNC(uint32, MCU_CODE) Wdg_getWdgBaseAddr(uint16 regNum)
{
    uint32 baseAddr;

    baseAddr = Wdg_RTIChannelAddr[regNum];

    return (baseAddr);
}

/** @fn FUNC(uint32, MCU_CODE) Wdg_getWdgResetAddr(uint16 regNum)
 *   @brief Gets the reset address of the Watchdog module instance
 *   @param[in] regNum - Watchdog Module instances
 *
 *   This function returns the reset address of the Watchdog module instance.
 *
 */
FUNC(uint32, WDG_CODE) Wdg_getWdgResetAddr(uint16 regNum)
{
    uint32 resetAddr;

    resetAddr = Wdg_ResetChannelAddr[regNum];

    return (resetAddr);
}

/** @fn FUNC(uint32, WDG_CODE) Wdg_getCurrentDownCounter(uint32 baseAddr)
 *   @brief Get the current DWWD Down Counter
 *   @param[in] baseAddr - Base address of Watchdog to be configured
 *   @return Current tick of selected compare
 *
 *   This function will get the current DWWD down counter value.
 *
 */
FUNC(uint32, WDG_CODE) Wdg_getCurrentDownCounter(uint32 baseAddr)
{
    return (((rtiBASE_t*)baseAddr)->DWDCNTR);
}

/** @fn FUNC(void, WDG_CODE) Wdg_generateSysReset(uint32 baseAddr)
 *   @brief Generate System Reset through DWD
 *   @param[in] baseAddr - Base address of Watchdog to be configured
 *
 *   This function can be called to generate system reset using DWD.
 *
 */

FUNC(void, WDG_CODE) Wdg_generateSysReset(uint32 baseAddr)
{
    ((rtiBASE_t*)baseAddr)->WDKEY = WDG_TRIGGER_FIRST_KEY;
    ((rtiBASE_t*)baseAddr)->WDKEY = WDG_TRIGGER_RESET_KEY;
}

/** @fn FUNC(void, WDG_CODE) Wdg_service(uint32 baseAddr)
 *   @brief Reset Digital Watchdog
 *   @param[in] baseAddr - Base address of Watchdog to be configured
 *
 *   This function can be called to reset Digital Watchdog.
 *
 */
FUNC(void, WDG_CODE) Wdg_service(uint32 baseAddr)
{
    ((rtiBASE_t*)baseAddr)->WDKEY = WDG_TRIGGER_FIRST_KEY;
    ((rtiBASE_t*)baseAddr)->WDKEY = WDG_TRIGGER_SECOND_KEY;
}

/** @fn FUNC(uint32, WDG_CODE) Wdg_getReloadValue(uint32 baseAddr)
 *   @brief Returns the Watchdog actual Reload Value
 *   @param[in] baseAddr - Base address of Watchdog to be configured
 *
 *   This function returns the value which is reloaded into the down counter.
 *
 */
FUNC(uint32, WDG_CODE) Wdg_getReloadValue(uint32 baseAddr)
{
    uint32 dwwdReloadVal;
    dwwdReloadVal = ((rtiBASE_t*)baseAddr)->DWDPRLD;
    dwwdReloadVal = (dwwdReloadVal + 1U) << WDG_DWWDPRLD_MULTIPLIER_SHIFT;
    return (dwwdReloadVal);
}

/** @fn FUNC(Std_ReturnType, WDG_CODE) Wdg_platformInit(
 *       P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
 *   @brief Initialize the Watchdog module
 *   @param[in] ConfigPtr - pointer to the Watchdog configuration
 *
 *   This function sets the Preload value, Watchdog Window size and Watchdog
 *   reaction upon Violation or Expiration.
 *
 */
FUNC(Std_ReturnType, WDG_CODE)
Wdg_platformInit(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    Std_ReturnType status;
    uint32         regWriteStatus = 0U;

#if (WDG_DEV_ERROR_DETECT == STD_ON)
    if (ConfigPtr->instanceId >= Wdg_getNumWdg())
    {
        (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_API_INIT, WDG_E_PARAM_CONFIG);
        status = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif
    {
        status = wdg_platforminit_internal(ConfigPtr);
        if ((Std_ReturnType)E_OK == status)
        {
            Mcal_Libs_Utils_unlockTopRcmMMR();
            regWriteStatus = regWriteReadback(&toprcmREG->WARM_RESET_CONFIG, M_EIGHTEEN, M_SIXTEEN, 0x7U);
            Mcal_Libs_Utils_lockTopRcmMMR();
            if (regWriteStatus != MCAL_REGWR_E_OK)
            {
#ifdef WDG_E_HARDWARE_ERROR
                (void)Dem_SetEventStatus((Dem_EventIdType)WDG_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            }
        }
        else
        {
#if (STD_ON == WDG_DEV_ERROR_DETECT)
            (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, WDG_API_INIT, WDG_E_PARAM_CONFIG);
#endif
        }
    }

    return (status);
}

static FUNC(Std_ReturnType, WDG_CODE)
    wdg_platforminit_internal(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    Std_ReturnType status = E_OK;
    uint32         baseAddr;

    if (ConfigPtr->defaultMode == WDGIF_OFF_MODE)
    {
        status = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        baseAddr = Wdg_getWdgBaseAddr(ConfigPtr->instanceId);

        /* Clear any previous violations */
        Wdg_clearStatus(baseAddr, WDG_STATUS_RESET_VAL);

        if (ConfigPtr->defaultMode == WDGIF_FAST_MODE)
        {
            status = Wdg_windowConfig(baseAddr, (uint32)ConfigPtr->fastModeCfg.reaction,
                                      ConfigPtr->fastModeCfg.preloadValue, (uint32)ConfigPtr->fastModeCfg.windowSize);
        }
        else
        {
            /* WDGIF_SLOW_MODE */
            status = Wdg_windowConfig(baseAddr, (uint32)ConfigPtr->slowModeCfg.reaction,
                                      ConfigPtr->slowModeCfg.preloadValue, (uint32)ConfigPtr->slowModeCfg.windowSize);
        }
    }

    return status;
}

#if (STD_ON == WDG_DEV_ERROR_DETECT)
void Wdg_reportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(WDG_MODULE_ID, WDG_INSTANCE_ID, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == WDG_DEV_ERROR_DETECT) */

#if (STD_ON == WDG_REGISTER_READBACK_API)
/******************************************************************************
 *  Wdg_HWRegisterReadback
 ******************************************************************************/
/*! \name      This method is Wdg_HWRegisterReadback Api.
 *  \param[in]  Wdg_RegisterReadbackType       RegisterReadbackPtr
 *  \param[out] none
 *  \return     E_OK, E_NOT_OK
 *  \context    Function could be called from from task level
 ******************************************************************************/
FUNC(void, WDG_CODE)
Wdg_HWRegisterReadback(P2VAR(Wdg_RegisterReadbackType, AUTOMATIC, WDG_APPL_DATA) RegisterReadbackPtr)
{
    RegisterReadbackPtr->Wdg_RtiDwdCtrl     = ((rtiBASE_t*)Wdg_DrvObj.baseAddr)->DWDCTRL;
    RegisterReadbackPtr->Wdg_RtiDwdprld     = ((rtiBASE_t*)Wdg_DrvObj.baseAddr)->DWDPRLD;
    RegisterReadbackPtr->Wdg_RtiWdStatus    = ((rtiBASE_t*)Wdg_DrvObj.baseAddr)->WDSTATUS;
    RegisterReadbackPtr->Wdg_RtiWdKey       = ((rtiBASE_t*)Wdg_DrvObj.baseAddr)->WDKEY;
    RegisterReadbackPtr->Wdg_RtiWwdRxnCtrl  = ((rtiBASE_t*)Wdg_DrvObj.baseAddr)->WWDRXNCTRL;
    RegisterReadbackPtr->Wdg_RtiWwdSizeCtrl = ((rtiBASE_t*)Wdg_DrvObj.baseAddr)->WWDSIZECTRL;
}
#endif /*STD_ON == WDG_REGISTER_READBACK_API*/

/** @fn FUNC(void, WDG_CODE) Wdg_reset(void)
 *   @brief Reset the Watchdog
 *
 *   This function can be called to reset Digital Watchdog to update the PRLD register.
 *
 */
static FUNC(void, WDG_CODE) Wdg_reset(void)
{
    uint32 resetAddr;

    /* get the address of WDG instance to reset */
    resetAddr = Wdg_DrvObj.WdgResetAddress;

    /* unlock to write to the MSS_RCM register */
    HW_WR_REG32(MSS_RCM_LOCK0_KICK0, RCM_KICK0_UNLOCK_VAL);
    HW_WR_REG32(MSS_RCM_LOCK0_KICK1, RCM_KICK1_UNLOCK_VAL);

    /* Reset the wdg : 3'b111 */
    HW_WR_REG32(resetAddr, 0x7);
    /* De-assert the reset: 3'b000 */
    HW_WR_REG32(resetAddr, 0x0);

    /* lock the MSS_RCM register */
    HW_WR_REG32(MSS_RCM_LOCK0_KICK0, RCM_KICK0_LOCK_VAL);
    HW_WR_REG32(MSS_RCM_LOCK0_KICK1, RCM_KICK1_LOCK_VAL);
}

/** @fn FUNC(Std_ReturnType, WDG_CODE) Wdg_SetModeConfig(VAR(WdgIf_ModeType, AUTOMATIC) Mode)
 *   @brief Set the WDG MODE
 *   \param[in]  Wdg_RegisterReadbackType       RegisterReadbackPtr
 *
 *   This function can be called to change the Wdg Mode
 *
 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_SetModeConfig(VAR(WdgIf_ModeType, AUTOMATIC) Mode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    uint32         baseAddr;

    baseAddr = Wdg_DrvObj.baseAddr;
    /* Check if requested mode type is other than configured mode type */
    if (Mode != Wdg_DrvObj.previousMode)
    {
        if (Mode == WDGIF_OFF_MODE)
        {
            /* OFF mode not supported by HW*/
            retVal = E_NOT_OK;
        }
        /* Get Requested mode type settings from configuration settings */
        else
        {
            Wdg_reset();
            if (Mode == WDGIF_FAST_MODE)
            {
                /* DWD Expiration Period */
                retVal =
                    Wdg_windowConfig(baseAddr, (uint32)Wdg_DrvObj.fastModeCfg.reaction,
                                     Wdg_DrvObj.fastModeCfg.preloadValue, (uint32)Wdg_DrvObj.fastModeCfg.windowSize);
            }
            else
            {
                /* DWD Expiration Period */
                retVal =
                    Wdg_windowConfig(baseAddr, (uint32)Wdg_DrvObj.slowModeCfg.reaction,
                                     Wdg_DrvObj.slowModeCfg.preloadValue, (uint32)Wdg_DrvObj.slowModeCfg.windowSize);
            }
            /*  Enable the WDG after changing the DWDPRLD register */
            Wdg_counterEnable(Wdg_DrvObj.baseAddr);
        }
    }
    else
    {
        retVal = (Std_ReturnType)E_OK;
    }

    return retVal;
}

#define WDG_STOP_SEC_CODE
#include "Wdg_MemMap.h"
