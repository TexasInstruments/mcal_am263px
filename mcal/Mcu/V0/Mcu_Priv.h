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
 *  \file     Mcu_Priv.h
 *
 */

#ifndef MCU_PRIV_H_
#define MCU_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
#include "sys_common.h"
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#include "Mcu.h"
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#include "Mcal_Libs_Utils.h"
#include "hw_ctrl_core.h"
#include "sys_pmu.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MCU_SOFT_SYSRST 0x00

/*Single port memory*/
#define RL_SP_ST_M_MBOX (uint64)((uint64)1U << 21U)
#define RL_SP_ST_M_MCAN (uint64)((uint64)1U << 39U)

/*Two port memory*/
#define RL_TP_ST_M_SPIB  (uint64)((uint64)1U << 43U)
#define RL_TP_ST_M_DCAN1 (uint64)((uint64)1U << 25U)
#define RL_TP_ST_M_DCAN2 (uint64)((uint64)1U << 26U)
#define RL_TP_ST_M_DMA   (uint64)((uint64)1U << 27U)
#define RL_TP_ST_M_SPIA  (uint64)((uint64)1U << 28U)
#define RL_TP_ST_M_VIM   (uint64)((uint64)1U << 29U)
#define XTAL_CLKINP      ((uint64)25000000)

#define MCU_SYSTEM_CLK ((uint32)400000000)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct
{
    uint8         rawresetval;
    Mcu_ResetType resetReason;
} Mcu_ResetStatusMap;

typedef struct
{
    uint8                     numFields;
    const Mcu_ResetStatusMap *resetMap;
} Mcu_ResetInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if (STD_OFF == MCU_NO_PLL)
Mcu_PllStatusType Mcu_GetPllLockStatus(void);
Std_ReturnType    Mcu_PLLInitAll(const Mcu_ConfigType *Mcu_PllDrvObj);
uint32            Mcu_corePllInit(Mcu_PllClkDivType pllClk1, uint32 M);
uint32            Mcu_perPllInit(Mcu_PllClkDivType pllClk2, uint32 M);
uint32            Mcu_corePllClkout(Mcu_PllClkDivType pllClk1);
uint32            Mcu_perPllClkout(Mcu_PllClkDivType pllClk2);
uint32            Mcu_corePllHsdivStat(Mcu_PllClkDivType pllClk1);
uint32            Mcu_perPllHsdivStat(Mcu_PllClkDivType pllClk2);
uint32            Mcu_Pll_CoreHSDIV(void);
uint32            Mcu_Pll_PerHSDIV(void);
Std_ReturnType    Mcu_pllTimeoutevent(volatile const uint32 *addr);
#endif
#if (STD_ON == MCU_PERFORM_RESET_API)
void Mcu_PerformSoftSysReset(uint32 resetVal);
#endif
void             Mcu_DisableEpwmTbClk(void);
Mcu_ResetType    Mcu_GetPlatformResetReason(void);
Mcu_RawResetType Mcu_GetPlatformRawResetReason(void);
FUNC(void, MCU_CODE) Mcu_SetupClock(void);
FUNC(Std_ReturnType, MCU_CODE)
Mcu_ClockSetSource(Mcu_ClkModuleIdType moduleId, Mcu_ClkSourceIdType clkSrcId, uint32 clkDivId, boolean enable);
uint32              Mcu_getMultibitValue(uint32 clk_srcId);
Mcu_ClkSourceIdType Mcu_ClockSetSourceCR5(Mcu_ClkSourceIdType clk_srcId);
Std_ReturnType      Mcu_ClockSetSourceSYSCLK(uint32 clk_divId);
Std_ReturnType      Mcu_ClockSetSourceMCAN0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCAN1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCAN2(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCAN3(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceRTI0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceRTI1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceRTI2(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceRTI3(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceWDT0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceWDT1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceWDT2(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceWDT3(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceQSPI(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI2(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI3(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI4(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceI2C(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceSCI0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceSCI1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceSCI2(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceSCI3(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceSCI4(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceSCI5(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceCPTS(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMcuClkout0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType      Mcu_ClockSetSourceMcuClkout1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType      Mcu_ClockSetSourceMII100Clk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType      Mcu_ClockSetSourceMII10Clk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType      Mcu_ClockSetSourceRGMIClk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);

Std_ReturnType Mcu_ClockSetSourceCONTROLSS(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_SetUpDCDC_Contrl(void);

FUNC(void, MCU_CODE) Mcu_SystemInit(void);

#if (STD_ON == MCU_REGISTER_READBACK_API)
void Mcu_HWRegisterReadback(Mcu_RegisterReadbackType *RegisterReadbackPtr);
#endif /* MCU_REGISTER_READBACK_API */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCU_PRIV_H_ */
