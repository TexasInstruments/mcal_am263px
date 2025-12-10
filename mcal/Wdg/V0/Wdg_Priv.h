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
 *  \file     Wdg_Priv.h
 *
 *  \brief    This file contains Wdg MCAL driver private include file
 */

#ifndef WDG_PRIV_H_
#define WDG_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Wdg.h"
#include "Mcal_Libs_Utils.h"
#if (WDG_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "hw_ctrl_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define WDG_UTILS_ARRAYSIZE(array) ((sizeof(array) / sizeof((array)[0])))

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief WDG driver object structure.
 */
typedef struct
{
    /**< Base address of the hardware */
    uint32           baseAddr;
    /**< Watchdog timeOutCounter value */
    uint32           timeOutCounter;
    /**< Counter refence value for trigger */
    uint32           counterRef;
    /** \brief Fast Mode settings */
    Wdg_ModeInfoType fastModeCfg;
    /** \brief Slow mode config */
    Wdg_ModeInfoType slowModeCfg;
    /** \brief Mode type value : Fast, slow or Off mode */
    WdgIf_ModeType   previousMode;
    /**< Reset address of WDTx */
    uint32           WdgResetAddress;
} Wdg_DriverObjType;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define WDG_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Wdg_MemMap.h"

extern VAR(Wdg_DriverObjType, WDG_VAR_ZERO_INIT) Wdg_DrvObj;

#define WDG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Wdg_MemMap.h"
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

FUNC(Std_ReturnType, WDG_CODE)
Wdg_platformInit(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);
FUNC(uint32, WDG_CODE) Wdg_getCurrentDownCounter(uint32 baseAddr);
FUNC(void, WDG_CODE) Wdg_counterEnable(uint32 baseAddr);
FUNC(void, WDG_CODE) Wdg_generateSysReset(uint32 baseAddr);
FUNC(void, WDG_CODE) Wdg_service(uint32 baseAddr);
FUNC(uint32, WDG_CODE) Wdg_getReloadValue(uint32 baseAddr);
FUNC(uint32, WDG_CODE) Wdg_getWdgBaseAddr(uint16 regNum);
FUNC(uint32, WDG_CODE) Wdg_getWdgResetAddr(uint16 regNum);
#if (STD_ON == WDG_DEV_ERROR_DETECT)
void Wdg_reportDetError(uint8 apiId, uint8 errorId);
#endif /* #if (STD_ON == WDG_DEV_ERROR_DETECT) */
#if defined(WDG_E_MODE_FAILED) || defined(WDG_E_DISABLE_REJECTED) || defined(WDG_E_HARDWARE_ERROR)
void Wdg_reportDemError(Dem_EventIdType eventId, Dem_EventStatusType eventStatus);
#endif
#if (STD_ON == WDG_REGISTER_READBACK_API)
FUNC(void, WDG_CODE)
Wdg_HWRegisterReadback(P2VAR(Wdg_RegisterReadbackType, AUTOMATIC, WDG_APPL_DATA) RegisterReadbackPtr);
#endif /*STD_ON == WDG_REGISTER_READBACK_API*/
/** \brief Sets the requested Mode configuration settings into Watchdog registers
 *
 * \param[in] ModeCfg pointer to the Watchdog Mode settings
 * \return Std_ReturnType
 * \retval E_OK: command has been accepted
 * \retval E_NOT_OK: command has not been accepted
 *
 *********************************************************************************************************************/
FUNC(Std_ReturnType, WDG_CODE) Wdg_SetModeConfig(VAR(WdgIf_ModeType, AUTOMATIC) Mode);

/** @fn FUNC(void, WDG_CODE) Wdg_ProcessTimeout(VAR(uint16, AUTOMATIC) wdgtimeoutMsec)
 * @brief Set the DWDPRLD register for new timeout value
 * \param[in]  uint32               wdgtimeoutMsec
 * This function can be called to set timeout value DWDPRLD register
 * \return void
 *
 */
FUNC(void, WDG_CODE) Wdg_ProcessTimeout(VAR(uint16, AUTOMATIC) wdgTimeoutMsec);

/** @fn FUNC(uint32, WDG_CODE) Wdg_getPrldValfromTimeout(VAR(uint16, AUTOMATIC) wdgtimeoutMsec)
 * @brief Set the DWDPRLD register for new timeout value
 * \param[in]  uint32               wdgtimeoutMsec
 * This function can be called to set timeout value DWDPRLD register
 * \return uint32
 * \retval Preload Counter value to be set for DWDPRLD register
 *
 */
FUNC(uint32, WDG_CODE)
Wdg_getPrldValfromTimeout(VAR(uint16, AUTOMATIC) wdgTimeoutMsec);
#ifdef __cplusplus
}
#endif

#endif /* #ifndef WDG_PRIV_H_ */
