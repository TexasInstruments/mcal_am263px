/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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

#define MCU_SYSTEM_CLK ((uint32)500000000)
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
Std_ReturnType      Mcu_ClockSetSourceRTI0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceRTI1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceRTI2(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceRTI3(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceWDT0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceWDT1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceOSPI0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceOSPI1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI0(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI1(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI2(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType      Mcu_ClockSetSourceMCSPI3(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
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

FUNC(void, MCU_CODE) Mcu_SystemInit(void);

#if (STD_ON == MCU_REGISTER_READBACK_API)
void Mcu_HWRegisterReadback(Mcu_RegisterReadbackType *RegisterReadbackPtr);
#endif /* MCU_REGISTER_READBACK_API */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCU_PRIV_H_ */
