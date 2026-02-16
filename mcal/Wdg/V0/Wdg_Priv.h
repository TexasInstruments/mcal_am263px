/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
