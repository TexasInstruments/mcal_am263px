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
 *  \file     Mcu_Priv.c
 *
 */

#define MCU_PLATFORM_SOURCE (1)

/* ===========================================================================*/
/*                             Include Files                                  */
/* ===========================================================================*/
#include "Std_Types.h"
#include "Os.h"
#include "Dem.h"
#include "Mcu.h"
#include "Mcu_Xbar.h"
#include "Mcu_XbarPwm.h"
#include "Mcu_XbarOutput.h"
#include "Mcu_Priv.h"
#include "soc.h"
#include "hw_ctrl_core.h"
#if (STD_ON == MCU_DEV_ERROR_DETECT)
#include "Det.h"
#endif

#include "cslr_top_ctrl.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Port mode in MSS_CPSW_CONTROL register */
#define ETH_GMII_SEL_GMII_MODE  (0x0U)
#define ETH_GMII_SEL_RMII_MODE  (0x1U)
#define ETH_GMII_SEL_RGMII_MODE (0x2U)

#define ETH_GMII_RMII_REF_CLK_DISABLE (0x10U)
#define ETH_GMII_ID_MODE_ENABLE       (0x100U)

#define MSS_CPSW_CONTROL_REG_P1_GMII_FIELD_SHIFT (0x0U)
#define MSS_CPSW_CONTROL_REG_P1_GMII_FIELD_MASK  (0x00000117U)

#define MSS_CPSW_CONTROL_REG_P2_GMII_FIELD_SHIFT (0x10U)
#define MSS_CPSW_CONTROL_REG_P2_GMII_FIELD_MASK  (0x01170000U)

#define M_ZERO         (0U)
#define M_ONE          (1U)
#define M_TWO          (2U)
#define M_THREE        (3U)
#define M_FOUR         (4U)
#define M_FIVE         (5U)
#define M_SIX          (6U)
#define M_SEVEN        (7U)
#define M_EIGHT        (8U)
#define M_NINE         (9U)
#define M_TEN          (10U)
#define M_ELEVEN       (11U)
#define M_TWELVE       (12U)
#define M_SIXTEEN      (16U)
#define M_SEVENTEEN    (17U)
#define M_NINETEEN     (19U)
#define M_TWENTY       (20U)
#define M_TWENTY_TWO   (22U)
#define M_TWENTY_THREE (23U)
#define M_TWENTY_FOUR  (24U)
#define M_TWENTY_NINE  (29U)
#define M_THIRTY       (30U)
#define M_THIRTY_ONE   (31U)

#define M_SIXTY_FOUR       (64U)
#define M_SIXTY_FIVE       (65U)
#define M_SIXTY_SIX        (66U)
#define M_SIXTY_EIGHT      (68U)
#define M_SEVENTY_TWO      (72U)
#define M_EIGHTY           (80U)
#define M_NINTY_SIX        (96U)
#define M_ONE_NINTY_TWO    (192U)
#define M_THREE_TWENTY     (320U)
#define M_FIVE_SEVENTY_SIX (576U)
#define M_VALUE_1088       (1088U)
#define M_VALUE_2112       (2112U)
#define M_VALUE_4160       (4160U)
#define M_VALUE_8256       (8256U)
#define M_VALUE_16448      (16448U)
#define M_VALUE_32832      (32832U)
#define M_VALUE_65600      (65600U)
#define M_VALUE_131136     (131136U)
#define M_VALUE_262208     (262208U)
#define M_VALUE_524352     (524352U)
#define M_VALUE_1048640    (1048640U)
#define M_VALUE_2097216    (2097216U)
#define M_VALUE_4194368    (4194368U)
#define M_VALUE_8388672    (8388672U)
#define M_VALUE_16777280   (16777280U)
#define M_VALUE_33554496   (33554496U)
#define M_VALUE_67108928   (67108928U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if (STD_OFF == MCU_NO_PLL)
/** \brief MCU PLL status object */
extern VAR(volatile uint8, MCU_VAR_ZERO_INIT) Mcu_PllStatus;
#endif

/** \brief MCU driver object */
extern P2CONST(Mcu_ConfigType, MCU_DATA, MCU_PBCFG) Mcu_DrvObj;

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == MCU_PWM_ENABLE)
static void Mcu_setEpwmTbClk(uint32 epwmInstance, uint32 enable);
static void Mcu_setEpwmGroup(uint32 epwmInstance, uint32 group);
#endif
#if (STD_ON == MCU_ADC_ENABLE)
static inline void Mcu_enableAdcReference(uint32 adcInstance);
#endif
#if (STD_ON == MCU_ETH_ENABLE)
static void Mcu_updateGmiiField(const Mcu_EthConfigType *ethCfg);
#endif
static void Mcu_controlModuleUnlockMMR(uint32 domainId, uint32 partition);
static void Mcu_controlModuleLockMMR(uint32 domainId, uint32 partition);
static void Mcu_SetupClock_Config(uint8 idx);
static void Mcu_Timeoutevent(volatile uint32 *addr, uint32 Value, uint32 timeout);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if (STD_OFF == MCU_NO_PLL)
Mcu_PllStatusType Mcu_GetPllLockStatus(void)
{
    VAR(uint32, MCU_VAR) Reg_Val1 = 0U;
    VAR(uint32, MCU_VAR) Reg_Val2 = 0U;
    VAR(Mcu_PllStatusType, MCU_VAR) Pll_Status;

    Reg_Val1 = HW_RD_REG32(&toprcmREG->PLL_CORE_STATUS);
    Reg_Val2 = HW_RD_REG32(&toprcmREG->PLL_PER_STATUS);

    if (((Reg_Val1 & 0x400U) != 0U) && ((Reg_Val2 & 0x400U) != 0U))
    {
        Pll_Status = MCU_PLL_LOCKED;
    }
    else
    {
        Pll_Status = MCU_PLL_UNLOCKED;
    }

    return (Pll_Status);
}
#endif

#if (STD_ON == MCU_PERFORM_RESET_API)
void Mcu_PerformSoftSysReset(uint32 resetVal)
{
#ifdef MCAL_DYNAMIC_BUILD
    /* Donot reset for LDRA analysis*/
#else
    uint32 regWriteStatus = 0U;

    Mcu_controlModuleUnlockMMR(0, MCU_TOP_RCM_PARTITION0);
    regWriteStatus = regWriteReadback(&toprcmREG->WARM_RESET_REQ, M_TWO, M_ZERO, resetVal);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef MCU_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    Mcu_controlModuleLockMMR(0, MCU_TOP_RCM_PARTITION0);
#endif
    return;
}
#endif /* STD_ON == MCU_PERFORM_RESET_API */

Mcu_ResetType Mcu_GetPlatformResetReason(void)
{
    VAR(uint32, MCU_VAR) Reset_Read        = 0U;
    VAR(Mcu_ResetType, MCU_VAR) Reset_Type = MCU_RESET_UNDEFINED;
    Reset_Read                             = Mcu_GetPlatformRawResetReason();

    switch (Reset_Read)
    {
        case M_ZERO:
        {
            Reset_Type = MCU_RESET_CLEAR;
            break;
        }
        case M_SIXTY_FIVE:
        {
            Reset_Type = MCU_POWER_ON_RESET;
            break;
        }
        case M_SIXTY_SIX:
        {
            Reset_Type = MCU_WARM_RESET_WDT0;
            break;
        }
        case M_SIXTY_EIGHT:
        {
            Reset_Type = MCU_WARM_RESET_WDT1;
            break;
        }
        case M_NINTY_SIX:
        {
            Reset_Type = MCU_WARM_RESET;
            break;
        }
        case M_SIXTY_FOUR:
        {
            Reset_Type = MCU_EXT_PAD_RESET;
            break;
        }
        case M_ONE_NINTY_TWO:
        {
            Reset_Type = MCU_HSM_WDT_RESET;
            break;
        }
        case M_THREE_TWENTY:
        {
            Reset_Type = MCU_DEBUGGER_RESET;
            break;
        }
        case M_FIVE_SEVENTY_SIX:
        {
            Reset_Type = MCU_WARM_RESET_TEMP0;
            break;
        }
        case M_VALUE_1088:
        {
            Reset_Type = MCU_WARM_RESET_TEMP1;
            break;
        }
        case M_VALUE_2112:
        {
            Reset_Type = MCU_WARM_RESET_VMON1_oV;
            break;
        }
        case M_VALUE_4160:
        {
            Reset_Type = MCU_WARM_RESET_VMON2_oV;
            break;
        }
        case M_VALUE_8256:
        {
            Reset_Type = MCU_WARM_RESET_VMON3_oV;
            break;
        }
        case M_VALUE_16448:
        {
            Reset_Type = MCU_WARM_RESET_VMON5_oV;
            break;
        }
        case M_VALUE_32832:
        {
            Reset_Type = MCU_WARM_RESET_VMON0_uV;
            break;
        }
        case M_VALUE_65600:
        {
            Reset_Type = MCU_WARM_RESET_VMON1_uV;
            break;
        }
        case M_VALUE_131136:
        {
            Reset_Type = MCU_WARM_RESET_VMON2_uV;
            break;
        }
        case M_VALUE_262208:
        {
            Reset_Type = MCU_WARM_RESET_VMON3_uV;
            break;
        }
        case M_VALUE_524352:
        {
            Reset_Type = MCU_WARM_RESET_VMON5_uV;
            break;
        }
        case M_VALUE_1048640:
        {
            Reset_Type = MCU_WARM_RESET_VMON7_uV;
            break;
        }
        case M_VALUE_2097216:
        {
            Reset_Type = MCU_WARM_RESET_VMON8_uV;
            break;
        }
        case M_VALUE_4194368:
        {
            Reset_Type = MCU_WARM_RESET_SYS_CLK_LOSS;
            break;
        }
        case M_VALUE_8388672:
        {
            Reset_Type = MCU_WARM_RESET_ESM_INTERRUPT;
            break;
        }
        case M_VALUE_16777280:
        {
            Reset_Type = MCU_WARM_RESET_ESM_WDG_INTERRUPT;
            break;
        }
        case M_VALUE_33554496:
        {
            Reset_Type = MCU_WARM_RESET_ESM_ERR_INTERRUPT;
            break;
        }
        case M_VALUE_67108928:
        {
            Reset_Type = MCU_POWER_ON_RESET_ASSERT_SW;
            break;
        }
        default:
            Reset_Type = MCU_RESET_UNDEFINED;
            break;
    }

    return Reset_Type;
}

Mcu_RawResetType Mcu_GetPlatformRawResetReason(void)
{
    VAR(Mcu_RawResetType, MCU_VAR) rawResetReason = 0U;

    Mcu_controlModuleUnlockMMR(0, MCU_TOP_RCM_PARTITION0);
    /* Get reset reason, stored in WARM_RST_CAUSE by startup code */
    rawResetReason = (Mcu_RawResetType)toprcmREG->WARM_RST_CAUSE;

    HW_SET_FIELD32(toprcmREG->WARM_RST_CAUSE_CLR, TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR, 0x7);

    Mcu_controlModuleLockMMR(0, MCU_TOP_RCM_PARTITION0);

    return rawResetReason;
}

FUNC(void, MCU_CODE) Mcu_SystemInit(void)
{
    Mcal_Libs_Utils_unlockMMR(); /* Invoking API to unlock MMR registers */

#if (STD_OFF == MCU_NO_PLL)
    if (Mcu_PllStatus != MCU_STATE_INIT) /* Checking whether PLL is already initialised or not */
    {
        if (Mcu_PLLInitAll(Mcu_DrvObj) == E_OK) /* Invoking PLL init API */
        {
            Mcu_PllStatus = MCU_STATE_INIT; /* Updating PLL status object as initialized */
        }
    }
#endif

    Mcu_SetupClock(); /* Invoking API to do clock initialization for different modules */
    Mcal_pmuInit();

#if (STD_ON == MCU_PWM_ENABLE)
    uint8 pwm_instance;
    for (pwm_instance = 0U; pwm_instance < MCU_PWM_CHANNEL; pwm_instance++)
    {
        Mcu_setEpwmTbClk(Mcu_DrvObj->Mcu_Pwmconfig[pwm_instance].Mcu_PwmChannelId, TRUE);
        Mcu_setEpwmGroup(Mcu_DrvObj->Mcu_Pwmconfig[pwm_instance].Mcu_PwmChannelId,
                         Mcu_DrvObj->Mcu_Pwmconfig[pwm_instance].Mcu_PwmGroupId);
    }
#endif
#if (STD_ON == MCU_ADC_ENABLE)
    uint8 adc_instance;
    for (adc_instance = 0U; adc_instance < MCU_ADC_HWUNIT; adc_instance++)
    {
        Mcu_enableAdcReference(Mcu_DrvObj->Mcu_AdcConfig[adc_instance].Mcu_AdcHWUniId);
    }
#endif
#if (STD_ON == MCU_ETH_ENABLE)
    Mcu_updateGmiiField(Mcu_DrvObj->Mcu_EthConfig);
#endif
#if (STD_ON == MCU_INTRCROSSBAR_ENABLE)
    Mcu_IntXbar();
#endif

#if (STD_ON == MCU_INPUT_CROSSBAR_ENABLE)
    Mcu_InputXbar();
#endif

    /* Configure GPIO xbar pins */
    Mcu_GpioXbarConfig();
    Mcal_Libs_Utils_lockMMR();
}

FUNC(void, MCU_CODE) Mcu_SetupClock(void)
{
    uint8 idx;
    /* Config Clock is done for all modules */
    for (idx = 0U; idx < Mcu_DrvObj->Mcu_NumberOfClockConfig; idx++)
    {
        if (Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_InitCfg == (boolean)TRUE)
        {
            Mcu_SetupClock_Config(idx);
        }
    }
    return;
}

static void Mcu_Timeoutevent(volatile uint32 *addr, uint32 Value, uint32 timeout)
{
    volatile uint32 tempCount = timeout;
    if (timeout > 9U)
    {
        tempCount = timeout / 9U;
    }
    /* each unit of SW_delay equals to 10 clockcycle, so divided by 10U*/
    while (M_REG_READ32(addr) != Value)
    {
        if (tempCount <= 0U)
        {
#ifdef MCU_E_CLOCK_FAILURE
            /* timeout */
            (void)Dem_SetEventStatus(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
}

#if (STD_OFF == MCU_NO_PLL)
Std_ReturnType Mcu_pllTimeoutevent(volatile const uint32 *regaddr)
{
    Std_ReturnType pll_return = E_OK;

    /* Wait for FSM to to come out of reset */
    volatile uint32 tempCount = MCU_PLL_TIMEOUT_DURATION;
    if (MCU_PLL_TIMEOUT_DURATION > 9U)
    {
        /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
        tempCount = MCU_PLL_TIMEOUT_DURATION / 9U;
    }
    /* Wait for FSM to to come out of reset */

    while (0x400U != (HW_RD_REG32(regaddr) & 0x400U))
    {
        /* Below API can change start time, so use temp variable */
        /* PHASELOCK[10] */
        if (tempCount <= 0U)
        {
#ifdef MCU_E_CLOCK_FAILURE
            /* timeout */
            (void)Dem_SetEventStatus(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
            pll_return = E_NOT_OK;
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
    return pll_return;
}
#endif

static void Mcu_SetupClock_Config(uint8 idx)
{
    if (MCU_CLKSRC_MAX > Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockSourceId)
    {
        Std_ReturnType status = E_NOT_OK;
        status                = Mcu_ClockSetSource(
            Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockModuleId, Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockSourceId,
            Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockDiv, Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_InitCfg);
        if (status != ((Std_ReturnType)E_OK))
        {
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            /* API is being called with invalid config param */
            (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT, MCU_E_PARAM_CONFIG);
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
        }
    }
    else
    {
#if (STD_ON == MCU_DEV_ERROR_DETECT)
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT, MCU_E_PARAM_CONFIG);
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    }
}

uint32 Mcu_getMultibitValue(uint32 clk_srcId)
{
    VAR(uint32, MCU_VAR) multibitValue = 0;
    multibitValue                      = (clk_srcId << 8) | (clk_srcId << 4) | (clk_srcId);
    return multibitValue;
}

Mcu_ClkSourceIdType Mcu_ClockSetSourceCR5(Mcu_ClkSourceIdType clk_srcId)
{
    VAR(uint32, MCU_VAR) clkSrcVal = 0, regWriteStatus = 0U;
    TickType            timeout_duration = 100U;
    Mcu_ClkSourceIdType multibitValue    = (Mcu_ClkSourceIdType)0;
    uint32              r5ClkSrc         = M_REG_READ32(&toprcmREG->R5SS_CLK_SRC_SEL);
    r5ClkSrc                             = ((r5ClkSrc >> 8) & (r5ClkSrc >> 4) & (r5ClkSrc));
    multibitValue                        = (Mcu_ClkSourceIdType)r5ClkSrc;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);

    regWriteStatus = regWriteReadback(&toprcmREG->R5SS_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef MCU_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    Mcu_Timeoutevent(&toprcmREG->R5SS_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    return multibitValue;
}
Std_ReturnType Mcu_ClockSetSourceSYSCLK(uint32 clk_divId)
{
    /*Clk source is pre-configured*/
    uint32 clkDivVal = 0;

    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    (void)regWriteReadback(&toprcmREG->SYS_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    return E_OK;
}

Std_ReturnType Mcu_ClockSetSourceMCAN0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_MCAN0_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCAN0_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_MCAN0_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->RCM_MCAN0_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
Std_ReturnType Mcu_ClockSetSourceMCAN1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_MCAN1_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    Mcu_Timeoutevent(&mssrcmREG->RCM_MCAN1_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_MCAN1_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->RCM_MCAN1_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRTI0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_RTI0_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI0_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_RTI0_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI0_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRTI1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_RTI1_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI1_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_RTI1_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI1_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRTI2(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_RTI2_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI2_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_RTI2_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI2_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRTI3(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_RTI3_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI3_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_RTI3_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_RTI3_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceWDT0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_WDT0_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_WDT0_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_WDT0_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_WDT0_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
Std_ReturnType Mcu_ClockSetSourceWDT1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_WDT1_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_WDT1_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_WDT1_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_WDT1_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
Std_ReturnType Mcu_ClockSetSourceOSPI0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_OSPI0_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_OSPI0_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_OSPI0_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_OSPI0_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
Std_ReturnType Mcu_ClockSetSourceOSPI1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_OSPI1_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_OSPI1_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_OSPI1_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_OSPI1_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMCSPI0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_MCSPI0_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI0_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_MCSPI0_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI0_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMCSPI1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_MCSPI1_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI1_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_MCSPI1_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI1_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMCSPI2(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_MCSPI2_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI2_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_MCSPI2_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI2_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMCSPI3(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_MCSPI3_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI3_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_MCSPI3_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_MCSPI3_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceI2C(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_I2C_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_I2C_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_I2C_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_I2C_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCI0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_LIN0_UART0_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN0_UART0_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_LIN0_UART0_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN0_UART0_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCI1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_LIN1_UART1_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN1_UART1_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_LIN1_UART1_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN1_UART1_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCI2(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_LIN2_UART2_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN2_UART2_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_LIN2_UART2_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN2_UART2_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCI3(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_LIN3_UART3_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN3_UART3_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_LIN3_UART3_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN3_UART3_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCI4(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_LIN4_UART4_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN4_UART4_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_LIN4_UART4_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN4_UART4_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCI5(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_LIN5_UART5_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN5_UART5_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_LIN5_UART5_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_LIN5_UART5_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceCPTS(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_CPTS_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_CPTS_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_CPTS_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_CPTS_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMcuClkout0(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal           = E_OK;
    uint32         regWriteStatus   = 0U;
    uint32         clkSrcVal        = 0;
    uint32         clkDivVal        = 0;
    TickType       timeout_duration = 100U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    regWriteStatus = regWriteReadback(&toprcmREG->CLKOUT0_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    Mcu_Timeoutevent(&toprcmREG->CLKOUT0_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&toprcmREG->CLKOUT0_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->CLKOUT0_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMcuClkout1(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal           = E_OK;
    uint32         regWriteStatus   = 0U;
    uint32         clkSrcVal        = 0;
    uint32         clkDivVal        = 0;
    TickType       timeout_duration = 100U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    regWriteStatus = regWriteReadback(&toprcmREG->CLKOUT1_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    Mcu_Timeoutevent(&toprcmREG->CLKOUT1_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&toprcmREG->CLKOUT1_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->CLKOUT1_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMII100Clk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
    VAR(uint32, MCU_VAR) clkDivVal  = 0;
    uint32         regWriteStatus   = 0U;
    Std_ReturnType retVal           = E_OK;
    TickType       timeout_duration = 100U;

    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_RGMII_50_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_RGMII_50_CLK_DIV_VAL, clkDivVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMII10Clk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
    VAR(uint32, MCU_VAR) clkDivVal  = 0;
    uint32         regWriteStatus   = 0U;
    Std_ReturnType retVal           = E_OK;
    TickType       timeout_duration = 100U;

    clkDivVal      = (clk_divId << 16) | (clk_divId << 8) | (clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_RGMII_5_CLK_DIV_VAL, M_TWENTY_THREE, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_RGMII_5_CLK_DIV_VAL, clkDivVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRGMIClk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
    VAR(uint32, MCU_VAR) clkDivVal  = 0;
    uint32         regWriteStatus   = 0U;
    Std_ReturnType retVal           = E_OK;
    TickType       timeout_duration = 100U;

    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_RGMII_250_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_RGMII_250_CLK_DIV_VAL, clkDivVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceCONTROLSS(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal          = E_OK;
    uint32         regWriteStatus  = 0U;
    VAR(uint32, MCU_VAR) clkSrcVal = 0;
    VAR(uint32, MCU_VAR) clkDivVal = 0;
    TickType timeout_duration      = 100U;

    clkSrcVal      = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal      = Mcu_getMultibitValue(clk_divId);
    regWriteStatus = regWriteReadback(&mssrcmREG->RCM_CONTROLSS_PLL_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_CONTROLSS_PLL_CLK_DIV_VAL, clkDivVal, timeout_duration);

    regWriteStatus |= regWriteReadback(&mssrcmREG->RCM_CONTROLSS_PLL_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);
    Mcu_Timeoutevent(&mssrcmREG->RCM_CONTROLSS_PLL_CLK_SRC_SEL, clkSrcVal, timeout_duration);

    if (regWriteStatus != (uint32)E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

FUNC(Std_ReturnType, MCU_CODE)
Mcu_ClockSetSource(Mcu_ClkModuleIdType moduleId, Mcu_ClkSourceIdType clkSrcId, uint32 clkDivId, boolean enable)
{
    VAR(Std_ReturnType, MCU_VAR) RetVal    = E_OK;
    VAR(Std_ReturnType, MCU_VAR) defRetVal = E_OK;

    switch (moduleId)
    {
        case MCU_CLKSRC_MODULE_ID_MCAN0:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_MCAN0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceMCAN0(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_MCAN0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCAN1:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_MCAN1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceMCAN1(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_MCAN1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RTI0:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_RTI0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceRTI0(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_RTI0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RTI1:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_RTI1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceRTI1(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_RTI1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RTI2:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_RTI2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceRTI2(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_RTI2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RTI3:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_RTI3_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceRTI3(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_RTI3_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_WDT0:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_WDT0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceWDT0(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_WDT0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_WDT1:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_WDT1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceWDT1(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_WDT1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_OSPI0:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_OSPI0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceOSPI0(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_OSPI0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_OSPI1:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_OSPI1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceOSPI1(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_OSPI1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCSPI0:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_MCSPI0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                         = Mcu_ClockSetSourceMCSPI0(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_MCSPI0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCSPI1:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_MCSPI1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                         = Mcu_ClockSetSourceMCSPI1(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_MCSPI1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCSPI2:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_MCSPI2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                         = Mcu_ClockSetSourceMCSPI2(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_MCSPI2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCSPI3:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_MCSPI3_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                         = Mcu_ClockSetSourceMCSPI3(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_MCSPI3_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_I2C:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_I2C0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                mssrcmREG->RCM_I2C1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                mssrcmREG->RCM_I2C2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceI2C(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_I2C0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
                mssrcmREG->RCM_I2C1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
                mssrcmREG->RCM_I2C2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCI0:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_UART0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                mssrcmREG->RCM_LIN0_CLK_GATE  = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceSCI0(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_UART0_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
                mssrcmREG->RCM_LIN0_CLK_GATE  = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCI1:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_UART1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                mssrcmREG->RCM_LIN1_CLK_GATE  = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceSCI1(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_UART1_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
                mssrcmREG->RCM_LIN1_CLK_GATE  = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCI2:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_UART2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                mssrcmREG->RCM_LIN2_CLK_GATE  = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceSCI2(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_UART2_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
                mssrcmREG->RCM_LIN2_CLK_GATE  = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCI3:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_UART3_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceSCI3(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_UART3_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCI4:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_UART4_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceSCI4(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_UART4_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCI5:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_UART5_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                        = Mcu_ClockSetSourceSCI5(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_UART5_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_CPTS:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_CPTS_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                       = Mcu_ClockSetSourceCPTS(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_CPTS_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCU_CLKOUT0:
        {
            if (enable == (boolean)TRUE)
            {
                toprcmREG->CLKOUT0_CLK_GATE = TOP_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                      = Mcu_ClockSetSourceMcuClkout0(clkSrcId, clkDivId);
            }
            else
            {
                toprcmREG->CLKOUT0_CLK_GATE = TOP_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCU_CLKOUT1:
        {
            if (enable == (boolean)TRUE)
            {
                toprcmREG->CLKOUT1_CLK_GATE = TOP_RCM_CLK_GATE_GATED_RESETVAL;
                RetVal                      = Mcu_ClockSetSourceMcuClkout1(clkSrcId, clkDivId);
            }
            else
            {
                toprcmREG->CLKOUT1_CLK_GATE = TOP_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MII100_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_RGMII_50_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                RetVal = Mcu_ClockSetSourceMII100Clk(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_RGMII_50_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MII10_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_RGMII_5_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                RetVal = Mcu_ClockSetSourceMII10Clk(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_RGMII_5_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RGMI_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_RGMII_250_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                RetVal = Mcu_ClockSetSourceRGMIClk(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_RGMII_250_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_CONTROLSS_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                mssrcmREG->RCM_CONTROLSS_PLL_CLK_GATE = MSS_RCM_CLK_GATE_GATED_RESETVAL;
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                RetVal = Mcu_ClockSetSourceCONTROLSS(clkSrcId, clkDivId);
            }
            else
            {
                mssrcmREG->RCM_CONTROLSS_PLL_CLK_GATE = MSS_RCM_CLK_GATE_GATED_MASK;
            }
            break;
        }

        default:
            RetVal    = (Std_ReturnType)E_NOT_OK;
            defRetVal = (Std_ReturnType)E_NOT_OK;
            break;
    }

    if (defRetVal == E_OK)
    {
        if ((RetVal != E_OK))
        {
#ifdef MCU_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }
    }
    return RetVal;
}

#if (STD_OFF == MCU_NO_PLL)
/* PLL Init Functions */

/**
 * \brief  Function to initialize all the PLL clocks
 */
Std_ReturnType Mcu_PLLInitAll(const Mcu_ConfigType *Mcu_PllDrvObj)
{
    uint32              regWriteStatus  = 0U;
    Std_ReturnType      init_pll_return = E_OK;
    Mcu_ClkSourceIdType r5ClkSrc_restore;
    uint32              M;

    Mcu_PllClkDivType pllClk1 = Mcu_PllDrvObj->Mcu_PllConfig[Mcu_PllDrvObj->Mcu_PllSourceId].Mcu_PllClk1;
    Mcu_PllClkDivType pllClk2 = Mcu_PllDrvObj->Mcu_PllConfig[Mcu_PllDrvObj->Mcu_PllSourceId].Mcu_PllClk2;

    /* Pre Requisite Sequence to relock core pll needs to be done */
    r5ClkSrc_restore = Mcu_ClockSetSourceCR5(MCU_CLKSRC_0);
    if (Mcu_PllDrvObj->Mcu_PllSourceId == MCU_CLKSRC_DPLL)
    {
        /* NON-ZERO => Enabled */
        if (pllClk1.MCU_PLL_CLKOUT != 0U) /* DPLL_CORE */
        {
            /* APPLJ-1 Setting
             * CLOCKOUT = M/(N+1) * CLKINP * (1/M2)
             */
            M = (uint32)((pllClk1.MCU_PLL_CLKOUT * ((pllClk1.N + (uint32)1) * pllClk1.M2)) / XTAL_CLKINP);
            /*Collect status of Core PLL registers */
            regWriteStatus |= Mcu_corePllInit(pllClk1, M);

            /*Timeout function call for MCU_E_CLOCK_FAILURE */
            init_pll_return = Mcu_pllTimeoutevent(&toprcmREG->PLL_CORE_STATUS);

            if (init_pll_return == E_OK)
            {
                /*Collect status of Core PLL CLKOUT registers */
                regWriteStatus |= Mcu_corePllClkout(pllClk1);
                /*function call for Core HSDIV settings*/
                regWriteStatus |= Mcu_Pll_CoreHSDIV();

                regWriteStatus |= Mcu_corePllHsdivStat(pllClk1);
            }
        }

        if (pllClk2.MCU_PLL_CLKOUT != 0U) /* DPLL_PER */
        {
            /* APPLJ-3 Setting
             * CLOCKOUT = M/(N+1) * CLKINP * (1/M2)
             */
            M = (uint32)((pllClk2.MCU_PLL_CLKOUT * ((pllClk2.N + (uint32)1) * pllClk2.M2)) / XTAL_CLKINP);
            /*Collect status of Per PLL registers */
            regWriteStatus |= Mcu_perPllInit(pllClk2, M);

            /*Timeout function call for MCU_E_CLOCK_FAILURE */
            init_pll_return = Mcu_pllTimeoutevent(&toprcmREG->PLL_PER_STATUS);
            if (init_pll_return == E_OK)
            {
                /*Collect status of Per PLL CLKOUT registers */
                regWriteStatus |= Mcu_perPllClkout(pllClk2);

                regWriteStatus |= Mcu_Pll_PerHSDIV();
                regWriteStatus |= Mcu_perPllHsdivStat(pllClk2);
            }
        }
    }

    /* Restore clock source to DPLL (MCU_CLKSRC_2 is DPLL_CORE_HSDIV0_CLKOUT0)*/
    (void)Mcu_ClockSetSourceCR5(r5ClkSrc_restore);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef MCU_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return init_pll_return;
}

uint32 Mcu_Pll_CoreHSDIV(void)
{
    uint32 regWriteStatus = 0U;
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER, M_TWO, M_TWO, M_ONE);  /* HSDIVIDER[2] = 1 */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER, M_TWO, M_TWO, M_ZERO); /* HSDIVIDER[2] = 0 */
    return regWriteStatus;
}
uint32 Mcu_Pll_PerHSDIV(void)
{
    uint32 regWriteStatus = 0U;
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER, M_TWO, M_TWO, M_ONE);  /* HSDIVIDER[2] = 1 */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER, M_TWO, M_TWO, M_ZERO); /* HSDIVIDER[2] = 0 */
    return regWriteStatus;
}

uint32 Mcu_corePllInit(Mcu_PllClkDivType pllClk1, uint32 M)
{
    uint32 regWriteStatus = 0;

    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_CLKCTRL, M_ZERO, M_ZERO, M_ZERO); /* Soft reset Pll */

    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_CORE_M2NDIV, M_TWENTY_TWO, M_SIXTEEN, pllClk1.M2); /* M2 - post divider */
    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_CORE_M2NDIV, M_SEVEN, M_ZERO, pllClk1.N);        /* N - input clock divider */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_MN2DIV, M_ELEVEN, M_ZERO, M); /* M - multiplier */
    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_CORE_MN2DIV, M_NINETEEN, M_SIXTEEN, M_ZERO); /* N2 - divider for by-pass */
    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_CORE_FRACDIV, M_SEVENTEEN, M_ZERO, pllClk1.FracM); /* fractional multiplier */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_FRACDIV, M_THIRTY_ONE, M_TWENTY_FOUR,
                                       pllClk1.sdDiv); /* sigma Delta divider */

    // /* program CLKDCOLDOEN[29] = 1, IDLE[23] = 0, CLKDCOLDOPWDNZ[17] = 1, SELFREQDCO[12:10] = 4
    // */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_CLKCTRL, M_TWENTY_NINE, M_TWENTY_NINE, M_ONE);
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_CLKCTRL, M_TWENTY_THREE, M_TWENTY_THREE, M_ZERO);
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_CLKCTRL, M_SEVENTEEN, M_SEVENTEEN, M_ONE);
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_CLKCTRL, M_TWELVE, M_TEN, M_FOUR);

    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_TENABLE, M_ZERO, M_ZERO, M_ONE);     /* TENABLE High */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_CLKCTRL, M_ZERO, M_ZERO, M_ONE);     /* out of reset Pll */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_TENABLE, M_ZERO, M_ZERO, M_ZERO);    /* TENABLE Low */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_TENABLEDIV, M_ZERO, M_ZERO, M_ONE);  /* TENABLEDIV High */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_TENABLEDIV, M_ZERO, M_ZERO, M_ZERO); /* TENABLEDIV Low */

    return regWriteStatus;
}

uint32 Mcu_perPllInit(Mcu_PllClkDivType pllClk2, uint32 M)
{
    uint32 regWriteStatus = 0;

    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_PER_M2NDIV, M_TWENTY_TWO, M_SIXTEEN, pllClk2.M2); /* M2 - post divider */
    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_PER_M2NDIV, M_SEVEN, M_ZERO, pllClk2.N);        /* N - input clock divider */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_MN2DIV, M_ELEVEN, M_ZERO, M); /* M - multiplier */
    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_PER_MN2DIV, M_NINETEEN, M_SIXTEEN, M_ZERO); /* N2 - divider for by-pass */
    regWriteStatus |=
        regWriteReadback(&toprcmREG->PLL_PER_FRACDIV, M_SEVENTEEN, M_ZERO, pllClk2.FracM); /* fractional multiplier */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_FRACDIV, M_THIRTY_ONE, M_TWENTY_FOUR,
                                       pllClk2.sdDiv); /* sigma Delta divider */

    /* program CLKDCOLDOEN[29] = 1, IDLE[23] = 0, CLKDCOLDOPWDNZ[17] = 1, SELFREQDCO[12:10] = 4 */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_CLKCTRL, M_TWENTY_NINE, M_TWENTY_NINE, M_ONE);
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_CLKCTRL, M_TWENTY_THREE, M_TWENTY_THREE, M_ZERO); /*Idle */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_CLKCTRL, M_SEVENTEEN, M_SEVENTEEN, M_ONE);
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_CLKCTRL, M_TWELVE, M_TEN, M_FOUR);

    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_CLKCTRL, M_ZERO, M_ZERO, M_ZERO);    /* Soft reset Pll */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_TENABLE, M_ZERO, M_ZERO, M_ONE);     /* TENABLE High */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_CLKCTRL, M_ZERO, M_ZERO, M_ONE);     /* out of reset Pll */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_TENABLE, M_ZERO, M_ZERO, M_ZERO);    /* TENABLE Low */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_TENABLEDIV, M_ZERO, M_ZERO, M_ONE);  /* TENABLEDIV High */
    regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_TENABLEDIV, M_ZERO, M_ZERO, M_ZERO); /* TENABLEDIV Low */

    return regWriteStatus;
}

uint32 Mcu_corePllClkout(Mcu_PllClkDivType pllClk1)
{
    uint32 regWriteStatus = 0;
    uint32 D;

    /* HSDIV-1 Settings
     * CLKOUT0_DIV[4:0] = D -- CLKOUT/(D+1)
     */

    if (pllClk1.MCU_PLL_HSDIV0 != 0U) /* NON-ZERO => Enabled */
    {
        D               = (uint32)(pllClk1.MCU_PLL_CLKOUT / pllClk1.MCU_PLL_HSDIV0) - (uint32)1;
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT0, M_FOUR, M_ZERO, D);
    }
    if (pllClk1.MCU_PLL_HSDIV1 != 0U)
    {
        D               = (uint32)(pllClk1.MCU_PLL_CLKOUT / (uint32)pllClk1.MCU_PLL_HSDIV1) - (uint32)1;
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT1, M_FOUR, M_ZERO, D);
    }
    if (pllClk1.MCU_PLL_HSDIV2 != 0U)
    {
        D               = (uint32)(pllClk1.MCU_PLL_CLKOUT / pllClk1.MCU_PLL_HSDIV2) - (uint32)1;
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT2, M_FOUR, M_ZERO, D);
    }
    if (pllClk1.MCU_PLL_HSDIV3 != 0U)
    {
        D               = (uint32)(pllClk1.MCU_PLL_CLKOUT / pllClk1.MCU_PLL_HSDIV3) - (uint32)1;
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT3, M_FOUR, M_ZERO, D);
    }

    return regWriteStatus;
}

uint32 Mcu_perPllClkout(Mcu_PllClkDivType pllClk2)
{
    uint32 regWriteStatus = 0;
    uint32 D;

    /* HSDIV-2 Settings
     * CLKOUT0_DIV[4:0] = D -- CLKOUT/(D+1)
     */
    if (pllClk2.MCU_PLL_HSDIV0 != 0U)
    {
        D               = (uint32)(pllClk2.MCU_PLL_CLKOUT / pllClk2.MCU_PLL_HSDIV0) - (uint32)1;
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER_CLKOUT0, M_FOUR, M_ZERO, D);
    }
    if (pllClk2.MCU_PLL_HSDIV2 != 0U)
    {
        D               = (uint32)(pllClk2.MCU_PLL_CLKOUT / pllClk2.MCU_PLL_HSDIV2) - (uint32)1;
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER_CLKOUT2, M_FOUR, M_ZERO, D);
    }
    if (pllClk2.MCU_PLL_HSDIV3 != 0U)
    {
        D               = (uint32)(pllClk2.MCU_PLL_CLKOUT / pllClk2.MCU_PLL_HSDIV3) - (uint32)1;
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER_CLKOUT3, M_FOUR, M_ZERO, D);
    }

    return regWriteStatus;
}

uint32 Mcu_corePllHsdivStat(Mcu_PllClkDivType pllClk1)
{
    uint32 regWriteStatus = 0;

    if (pllClk1.MCU_PLL_HSDIV0 != 0U)
    {
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT0, M_EIGHT, M_EIGHT,
                                           M_ONE); /* +CLKOUT0_GATE[8] = 1 */
    }
    if (pllClk1.MCU_PLL_HSDIV1 != 0U)
    {
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT1, M_EIGHT, M_EIGHT,
                                           M_ONE); /* +CLKOUT1_GATE[8] = 1 */
    }
    if (pllClk1.MCU_PLL_HSDIV2 != 0U)
    {
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT2, M_EIGHT, M_EIGHT,
                                           M_ONE); /* +CLKOUT2_GATE[8] = 1 */
    }
    if (pllClk1.MCU_PLL_HSDIV3 != 0U)
    {
        regWriteStatus |= regWriteReadback(&toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT3, M_EIGHT, M_EIGHT,
                                           M_ONE); /* +CLKOUT3_GATE[8] = 1 */
    }
    return regWriteStatus;
}

uint32 Mcu_perPllHsdivStat(Mcu_PllClkDivType pllClk2)
{
    uint32 regWriteStatus = 0;

    if (pllClk2.MCU_PLL_HSDIV0 != 0U)
    {
        regWriteStatus |=
            regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER_CLKOUT0, M_EIGHT, M_EIGHT, M_ONE); /* +CLKOUT0_GATE[8] = 1 */
    }
    if (pllClk2.MCU_PLL_HSDIV2 != 0U)
    {
        regWriteStatus |=
            regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER_CLKOUT2, M_EIGHT, M_EIGHT, M_ONE); /* +CLKOUT2_GATE[8] = 1 */
    }
    if (pllClk2.MCU_PLL_HSDIV3 != 0U)
    {
        regWriteStatus |=
            regWriteReadback(&toprcmREG->PLL_PER_HSDIVIDER_CLKOUT3, M_EIGHT, M_EIGHT, M_ONE); /* +CLKOUT3_GATE[8] = 1 */
    }
    return regWriteStatus;
}
#endif /* STD_OFF == MCU_NO_PLL */

#if (STD_ON == MCU_PWM_ENABLE)
/**
 * \brief Enable or disable ePWM time base clock from Control MMR
 *
 * \param epwmInstance [in] ePWM instance number [0 - 31]
 * \param enable       [in] TRUE to enable and FALSE to disable
 */
static void Mcu_setEpwmTbClk(uint32 epwmInstance, uint32 enable)
{
    if (epwmInstance < MCU_CSL_ETPWM_PER_CNT)
    {
        /* Time base clock enable register belongs to partition 1 of the CTRL MMR */

        /* Unlock CONTROLSS_CTRL registers */
        Mcu_controlModuleUnlockMMR(0, MCU_CONTROLSS_CTRL_PARTITION0);

        if (TRUE == enable)
        {
            /* Enable Time base clock in CTRL MMR */
            HW_WR_REG32(MCU_CSL_CONTROLSS_CTRL_U_BASE + MCU_CSL_CONTROLSS_CTRL_EPWM_CLKSYNC,
                        ((HW_RD_REG32(MCU_CSL_CONTROLSS_CTRL_U_BASE + MCU_CSL_CONTROLSS_CTRL_EPWM_CLKSYNC) &
                          MCU_CSL_CONTROLSS_CTRL_EPWM_CLKSYNC_BIT_MASK) |
                         (1U << epwmInstance)));
        }
        else
        {
            /* Disable Time base clock in CTRL MMR */
            uint32 epwmShiftInv = ~(1U << epwmInstance);
            HW_WR_REG32(MCU_CSL_CONTROLSS_CTRL_U_BASE + MCU_CSL_CONTROLSS_CTRL_EPWM_CLKSYNC,
                        ((HW_RD_REG32(MCU_CSL_CONTROLSS_CTRL_U_BASE + MCU_CSL_CONTROLSS_CTRL_EPWM_CLKSYNC) &
                          MCU_CSL_CONTROLSS_CTRL_EPWM_CLKSYNC_BIT_MASK) &
                         epwmShiftInv));
        }

        /* Lock CONTROLSS_CTRL registers */
        Mcu_controlModuleLockMMR(0, MCU_CONTROLSS_CTRL_PARTITION0);
    }
}
/**
 * \brief Configure the ePWM group
 *
 * \param epwmInstance [in] ePWM instance number [0 - 31]
 * \param group        [in] The group for this ePWM instance [0 - 3]
 */
static void Mcu_setEpwmGroup(uint32 epwmInstance, uint32 group)
{
    uint32 baseAddr = MCU_CSL_CONTROLSS_CTRL_U_BASE + MCU_CSL_CONTROLSS_CTRL_EPWM_STATICXBAR_SEL0;
    uint32 mask, shift;
    uint32 pwmInstance = epwmInstance;

    /* Unlock CONTROLSS_CTRL registers */
    Mcu_controlModuleUnlockMMR(0, MCU_CONTROLSS_CTRL_PARTITION0);

    /* Choose the correct base address depending on which ePWM instance is selected*/
    if (pwmInstance > 15U)
    {
        baseAddr    = baseAddr + 0x4U;
        pwmInstance = pwmInstance - 16U;
    }

    shift = (pwmInstance << 1);
    /* Create the mask to be written to register */
    mask = (uint32)((uint32)0x3U << shift);

    /* Configure the group for the ePWM instance */
    HW_WR_REG32(baseAddr, ((HW_RD_REG32(baseAddr) & ~mask) | (group << shift)));

    /* Lock CONTROLSS_CTRL registers */
    Mcu_controlModuleLockMMR(0, MCU_CONTROLSS_CTRL_PARTITION0);
}

#endif

void Mcu_DisableEpwmTbClk(void)
{
#if (STD_ON == MCU_PWM_ENABLE)
    uint8 pwm_instance;
    /* Disable PWM */
    for (pwm_instance = 0U; pwm_instance < MCU_PWM_CHANNEL; pwm_instance++)
    {
        Mcu_setEpwmTbClk(Mcu_DrvObj->Mcu_Pwmconfig[pwm_instance].Mcu_PwmChannelId, FALSE);
    }
#endif
}

static void Mcu_controlModuleUnlockMMR(uint32 domainId, uint32 partition)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    if (partition == MCU_TOP_CTRL_PARTITION0)
    {
        /*Unlock TOP_CTRL*/
        baseAddr = (uint32)MCU_CSL_TOP_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK0_UNLOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK1_UNLOCK_VAL); /* KICK 1 */
    }
    if (partition == MCU_TOP_RCM_PARTITION0)
    {
        /*Unlock TOP_RCM*/
        baseAddr = (uint32)MCU_CSL_TOP_RCM_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_RCM_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK0_UNLOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_RCM_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK1_UNLOCK_VAL); /* KICK 1 */
    }
    if (partition == MCU_CONTROLSS_CTRL_PARTITION0)
    {
        /*Unlock CONTROLSS_CTRL*/
        baseAddr = (uint32)MCU_CSL_CONTROLSS_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_CONTROLSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK0_UNLOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_CONTROLSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK1_UNLOCK_VAL); /* KICK 1 */
    }
#if (STD_ON == MCU_ETH_ENABLE)
    if (partition == MCU_MSS_CTRL_PARTITION0)
    {
        /*Unlock MSS_CTRL*/
        baseAddr = (uint32)MCU_CSL_MSS_CTRL_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK0_UNLOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK1_UNLOCK_VAL); /* KICK 1 */
    }
#endif
    return;
}

static void Mcu_controlModuleLockMMR(uint32 domainId, uint32 partition)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    if (partition == MCU_TOP_CTRL_PARTITION0)
    {
        /*Unlock TOP_CTRL*/
        baseAddr = (uint32)MCU_CSL_TOP_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 1 */
    }
    if (partition == MCU_TOP_RCM_PARTITION0)
    {
        /*Unlock TOP_RCM*/
        baseAddr = (uint32)MCU_CSL_TOP_RCM_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_RCM_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_TOP_RCM_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 1 */
    }
    if (partition == MCU_CONTROLSS_CTRL_PARTITION0)
    {
        /*Lock CONTROLSS_CTRL*/
        baseAddr = (uint32)MCU_CSL_CONTROLSS_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_CONTROLSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_CONTROLSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 1 */
    }
#if (STD_ON == MCU_ETH_ENABLE)
    if (partition == MCU_MSS_CTRL_PARTITION0)
    {
        /*Lock MSS_CTRL*/
        baseAddr = (uint32)MCU_CSL_MSS_CTRL_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_TEST_KICK_LOCK_VAL); /* KICK 1 */
    }
#endif
    return;
}

#if (STD_ON == MCU_ADC_ENABLE)
/* The ADC Instance is enabled here. (adcInstance can be between 0 to 4) */
static inline void Mcu_enableAdcReference(uint32 adcInstance)
{
    /* Determine the group number of the ADC and the mask to be written to compctl register */
    uint32 groupnum    = (adcInstance / 3U);
    uint32 compctlmask = 0x7;

    if (adcInstance == 2U)
    {
        compctlmask = (compctlmask << 4);
    }
    else
    {
        /*No action required*/
    }

    /* Unlock Top Control Space */
    Mcu_controlModuleUnlockMMR(0, MCU_TOP_CTRL_PARTITION0);

    /*Mask HHV before enabling reference buffer to ensure the ADC doesn't cause an MCU reset*/
    HW_WR_REG16(MCU_CSL_TOP_CTRL_U_BASE + CSL_TOP_CTRL_MASK_ANA_ISO,
                (0x7U & CSL_TOP_CTRL_MASK_ANA_ISO_MASK_ANA_ISO_MASK_MASK));
    /* Enable ADC references by writing to MMR */
    HW_WR_REG16(MCU_CSL_TOP_CTRL_U_BASE + CSL_TOP_CTRL_ADC_REFBUF0_CTRL + (groupnum * 4U), 0x7U);
    /*Unmask HHV*/
    HW_WR_REG16(MCU_CSL_TOP_CTRL_U_BASE + CSL_TOP_CTRL_MASK_ANA_ISO,
                ((~0x7U) & CSL_TOP_CTRL_MASK_ANA_ISO_MASK_ANA_ISO_MASK_MASK));

    HW_WR_REG16(MCU_CSL_TOP_CTRL_U_BASE + CSL_TOP_CTRL_ADC_REF_COMP_CTRL,
                HW_RD_REG32(MCU_CSL_TOP_CTRL_U_BASE + CSL_TOP_CTRL_ADC_REF_COMP_CTRL) | compctlmask);

    /* Lock Top Control Space */
    Mcu_controlModuleLockMMR(0, MCU_TOP_CTRL_PARTITION0);

    Mcal_pmuDelayUsec(1U, MCU_SYSTEM_CLK);
}

#endif

#if (STD_ON == MCU_ETH_ENABLE)
static void Mcu_updateGmiiField(const Mcu_EthConfigType *ethCfg)
{
    uint32 portIdx   = 0U;
    uint32 gmiiField = 0U;

    for (portIdx = 0; portIdx < MCU_ETH_PORTS; portIdx++)
    {
        /* PORT_MODE_SEL */
        switch (ethCfg[portIdx].macConnectionType)
        {
            case MCU_ETH_MAC_CONN_TYPE_MII_10_HALF:
            case MCU_ETH_MAC_CONN_TYPE_MII_10_FULL:
            case MCU_ETH_MAC_CONN_TYPE_MII_100_HALF:
            case MCU_ETH_MAC_CONN_TYPE_MII_100_FULL:
                /* MII modes */
                /* Eth mode select */
                gmiiField = ETH_GMII_SEL_GMII_MODE;
                break;

            case MCU_ETH_MAC_CONN_TYPE_RMII_10_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RMII_10_FULL:
            case MCU_ETH_MAC_CONN_TYPE_RMII_100_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RMII_100_FULL:
                /* RMII modes */
                gmiiField = ETH_GMII_SEL_RMII_MODE;
                break;

            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_10_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_10_FULL:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_100_HALF:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_100_FULL:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_FORCE_1000:
            case MCU_ETH_MAC_CONN_TYPE_RGMII_DETECT_INBAND:
                /* RGMII modes */
                gmiiField = ETH_GMII_SEL_RGMII_MODE;
                break;

            default:
                /* Wrong configuration */
                break;
        }

        /* RMII_REF_CLK_OE_N */
        if (0U != ethCfg[portIdx].rmiiClkOutDisable)
        {
            gmiiField |= ETH_GMII_RMII_REF_CLK_DISABLE;
        }

        /* ID_MODE */
        if (0U != ethCfg[portIdx].idModeEnable)
        {
            gmiiField |= ETH_GMII_ID_MODE_ENABLE;
        }

        /* Unlock MSS_CTRL */
        Mcu_controlModuleUnlockMMR(0, MCU_MSS_CTRL_PARTITION0);

        if ((uint8)1U == ethCfg[portIdx].macNum)
        {
            HW_WR_FIELD32(MCU_CSL_MSS_CTRL_BASE + MSS_CPSW_CONTROL_REG, MSS_CPSW_CONTROL_REG_P1_GMII_FIELD,
                          (gmiiField));
        }
        else if ((uint8)2U == ethCfg[portIdx].macNum)
        {
            HW_WR_FIELD32(MCU_CSL_MSS_CTRL_BASE + MSS_CPSW_CONTROL_REG, MSS_CPSW_CONTROL_REG_P2_GMII_FIELD,
                          (gmiiField));
        }
        else
        {
            /* wrong port */
        }

        /* Lock MSS_CTRL */
        Mcu_controlModuleLockMMR(0, MCU_MSS_CTRL_PARTITION0);
    }

    return;
}
#endif

#if (STD_ON == MCU_REGISTER_READBACK_API)
void Mcu_HWRegisterReadback(Mcu_RegisterReadbackType *RegisterReadbackPtr)
{
    RegisterReadbackPtr->CLKSRCSEL0 = (uint32)(mssrcmREG->RCM_RTI0_CLK_SRC_SEL);
}
#endif /* STD_ON == MCU_REGISTER_READBACK_API */

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
