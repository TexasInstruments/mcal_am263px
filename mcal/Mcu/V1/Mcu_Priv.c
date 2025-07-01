
/* ======================================================================
 *   Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Mcu_Priv.c
 *
 */

#define MCU_PLATFORM_SOURCE (1)
#define MCU_ONE_GHZ                                                                             \
    (1000000000U) /* 1GHz macro to check inside the PLL INIT Function to program the SELFREQDCO \
                     bitfields*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
#include "Os.h"
#include "Dem.h"
/*LDRA_ANALYSIS*/
#include "Mcu.h"
#include "Mcu_Priv.h"
#include "hw_ctrl_core.h"
#include "soc.h"

#define MCU_START_SEC_CODE
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
#include "Mcu_MemMap.h"
#include "mcal_hw_soc_baseaddress.h"
#include "hw_types.h"

#define MCU_STOP_SEC_CODE
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
#include "Mcu_MemMap.h"

#if (STD_ON == MCU_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "hal_stdtypes.h"

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
static uint8 MCAL_SOC_rcmExtract8(volatile uint32 reg, uint8 msb, uint8 lsb);
#if (STD_OFF == MCU_NO_PLL)
static uint32 SOC_rcmMake8(uint8 msb, uint8 lsb, uint8 val);
static uint32 SOC_rcmMake16(uint8 msb, uint8 lsb, uint16 val);
static uint32 SOC_rcmMake32(uint8 msb, uint8 lsb, uint32 val);
static uint16 MCAL_SOC_rcmExtract16(volatile uint32 reg, uint8 msb, uint8 lsb);
static uint32 MCAL_SOC_rcmExtract32(volatile uint32 reg, uint8 msb, uint8 lsb);
static uint32 MCAL_SOC_rcmInsert8(volatile uint32 reg, uint8 msb, uint8 lsb, uint8 val);
static uint32 MCAL_SOC_rcmInsert16(volatile uint32 reg, uint8 msb, uint8 lsb, uint16 val);
static uint32 MCAL_SOC_rcmInsert32(volatile uint32 reg, uint8 msb, uint8 lsb, uint32 val);
static uint32 MCAL_SOC_rcmGetADPLLJFout(uint32 Finp, uint32 N, uint32 M, uint32 M2, uint32 FracM, uint32 div2flag);
static uint32 MCAL_SOC_rcmGetCoreFout(uint32 Finp, uint32 div2flag);
static uint8  MCAL_SOC_rcmReadXtalFreqScale(const topCtrlBASE_t *ptrTopCtrlRegs);
static uint8  MCAL_SOC_rcmReadCoreADPLLTrimValidEfuse(const topCtrlBASE_t *ptrTopCtrlRegs);
static uint8  MCAL_SOC_rcmReadDspADPLLTrimValidEfuse(const topCtrlBASE_t *ptrTopCtrlRegs);
static uint8  MCAL_SOC_rcmReadPerADPLLTrimValidEfuse(const topCtrlBASE_t *ptrTopCtrlRegs);
static uint16 MCAL_SOC_rcmReadDspADPLLTrimEfuse(const topCtrlBASE_t *ptrTopCtrlRegs);
static uint16 MCAL_SOC_rcmReadPerADPLLTrimEfuse(const topCtrlBASE_t *ptrTopCtrlRegs);
/* PLL Init Functions */
static MCAL_SOC_RcmXtalFreqId          MCAL_SOC_rcmGetXtalFrequency(void);
static uint16                          MCAL_SOC_rcmGetDspTrimVal(void);
static MCAL_SOC_RcmADPLLJConfig const *MCAL_SOC_rcmGetADPLLJConfig(uint32 Finp, MCAL_SOC_RcmPllFoutFreqId foutFreqId);
static void   MCAL_SOC_rcmProgPllDspDivider(uint32 inputClockDiv, uint8 divider, uint32 multiplier, uint32 postDivider,
                                            uint32 fracMultiplier);
static void   MCAL_SOC_rcmConfigurePllDsp(uint16 trimVal);
static uint16 MCAL_SOC_rcmGetPerTrimVal(void);
static void   MCAL_SOC_rcmCoreApllHSDivConfig(const MCAL_SOC_RcmPllHsDivOutConfig *hsDivCfg);
static void   MCAL_SOC_rcmProgPllPerDivider(uint32 inputClockDiv, uint32 divider, uint32 multiplier, uint32 postDivider,
                                            uint32 fracMultiplier);
static void   MCAL_SOC_rcmConfigurePllPer(uint16 trimVal);
static void   MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId            outFreqId,
                                       const MCAL_SOC_RcmPllHsDivOutConfig *hsDivCfg);
static void   MCAL_SOC_rcmPerPllConfig(MCAL_SOC_RcmPllFoutFreqId            outFreqId,
                                       const MCAL_SOC_RcmPllHsDivOutConfig *hsDivCfg);
#endif
static void Mcu_ClockSetSourceCR5_Condition(uint32 *Condition_check, Mcu_ClkSourceIdType clk_srcId,
                                            uint32 hsdivClkout2);
static void Mcu_ClockSetSourceCR5_hsdivClkout2(uint32 *Condition_check, Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
static void Mcu_ClockSetSourceCR5_1(void);
static void Mcu_ClockSetSourceCR5_div_3(void);
static void Mcu_Timeoutevent(volatile const uint32 *addr, uint32 Value, uint32 timeout);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#if (STD_OFF == MCU_NO_PLL)
/** \brief MCU PLL status object */
extern VAR(volatile uint8, MCU_VAR_ZERO_INIT) Mcu_PllStatus;

/* Table populated from TPR12_ADPLLJ_Settings_1p0.xlsx.
 * Each entry corresponds to tab in the excel sheet
 */
static const MCAL_SOC_RcmADPLLJConfig Mcu_SocRcmADPLLJConfigTbl[] = {
    /*DSP_1100_40MHz*/
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 1100U,
        .M2    = 1U,
        .M     = 550U,
        .FracM = 0U,
    },
    /*DSP_1650_40MHz*/
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 1650U,
        .M2    = 1U,
        .M     = 1650U,
        .FracM = 0U,
    },
    /* DSP_900_40MHz  */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 900U,
        .M2    = 1U,
        .M     = 900U,
        .FracM = 0U,
    },
    /* CORE_DSP_800_40MHz */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 800U,
        .FracM = 0U,
    },
    /* CORE_DSP_800_40MHz */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 400U,
        .FracM = 0U,
    },
    /* CORE_DSP_2000_40MHz */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 2000U,
        .FracM = 0U,
    },
    /* CORE_DSP_2000_40MHz */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 1000U,
        .FracM = 0U,
    },
    /* CORE_PER_1728_40MHz */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 1728U,
        .M2    = 1U,
        .M     = 1728U,
        .FracM = 0U,
    },
    /* DSP_900_40MHz  */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 900U,
        .M2    = 1U,
        .M     = 450U,
        .FracM = 0U,
    },
    /* DSP_1800_40MHz  */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 900U,
        .FracM = 0U,
    },
    /* PER_1920_40MHz  */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 1920U,
        .M2    = 1U,
        .M     = 960U,
        .FracM = 0U,
    },
    /* CORE_DSP_800_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 400U,
        .FracM = 0U,
    },
    /* CORE_DSP_2000_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 1000U,
        .FracM = 0U,
    },
    /* DSP_1800_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 900U,
        .FracM = 0U,
    },
    /* PER_1920_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 1920U,
        .M2    = 1U,
        .M     = 960U,
        .FracM = 0U,
    },
    /* CORE_800_49152  */
    {
        .Finp  = 49U,
        .N     = 23U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 390U,
        .FracM = 163840U,
    },
    /* CORE_2000_49152  */
    {
        .Finp  = 49U,
        .N     = 21U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 895U,
        .FracM = 47787U,
    },
    /* DSP_1800_49152  */
    {
        .Finp  = 49U,
        .N     = 20U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 769U,
        .FracM = 11264U,
    },
    /* DSP_1728_49152  */
    {
        .Finp  = 49U,
        .N     = 19U,
        .Fout  = 1728U,
        .M2    = 1U,
        .M     = 703U,
        .FracM = 32768U,
    },
    /* PER_1966p08_49152  */
    {
        .Finp  = 49U,
        .N     = 19U,
        .Fout  = 1966U,
        .M2    = 1U,
        .M     = 800U,
        .FracM = 209715200U,
    },
    /* CORE_800_451584  */
    {
        .Finp  = 45U,
        .N     = 20U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 372U,
        .FracM = 6242U,
    },
    /* CORE_2000_451584  */
    {
        .Finp  = 45U,
        .N     = 20U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 930U,
        .FracM = 15604U,
    },
    /* DSP_1800_451584  */
    {
        .Finp  = 45U,
        .N     = 20U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 837U,
        .FracM = 14043U,
    },
    /* DSP_1728_451584  */
    {
        .Finp  = 45U,
        .N     = 18U,
        .Fout  = 1728U,
        .M2    = 1U,
        .M     = 727U,
        .FracM = 10700U,
    },
    /* PER_1806p336_451584  */
    {
        .Finp  = 45U,
        .N     = 18U,
        .Fout  = 1806U,
        .M2    = 1U,
        .M     = 760U,
        .FracM = 0U,
    },
    /* PER_1699_40MHz  */
    {
        .Finp  = 40U,
        .N     = 16U,
        .Fout  = 1699U,
        .M2    = 1U,
        .M     = 722U,
        .FracM = 44032U,
    },
};

static const MCAL_SOC_RcmXtalInfo Mcu_SocRcmXtalInfo[MCAL_SOC_RcmXtalClkFreq_Size] = {
    [MCAL_SOC_RcmXtalFreqId_CLK_40MHZ] = {.Finp = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_40MHZ), .div2flag = 0},
    [MCAL_SOC_RcmXtalFreqId_CLK_50MHZ] = {.Finp = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_50MHZ), .div2flag = 0},
    [MCAL_SOC_RcmXtalFreqId_CLK_49p152MHZ]  = {.Finp     = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_49p152MHZ),
                                               .div2flag = 0},
    [MCAL_SOC_RcmXtalFreqId_CLK_45p1584MHZ] = {.Finp     = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_45p1584MHZ),
                                               .div2flag = 0},
    [MCAL_SOC_RcmXtalFreqId_CLK_20MHZ] = {.Finp = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_40MHZ), .div2flag = 1},
    [MCAL_SOC_RcmXtalFreqId_CLK_25MHZ] = {.Finp = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_50MHZ), .div2flag = 1},
    [MCAL_SOC_RcmXtalFreqId_CLK_24p576MHZ]  = {.Finp     = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_49p152MHZ),
                                               .div2flag = 1},
    [MCAL_SOC_RcmXtalFreqId_CLK_22p5792MHZ] = {.Finp     = MCAL_SOC_RCM_FREQ_HZ2MHZ(MCAL_SOC_RCM_XTAL_CLK_50MHZ),
                                               .div2flag = 1},
};

static const uint32 Mcu_SocRcmPllFreqId2FOutMap[MCAL_SOC_RcmPllFoutClkFreq_Size] = {
    [MCAL_SOC_RcmPllFoutFreqId_CLK_1100MHZ] = 1100U,     [MCAL_SOC_RcmPllFoutFreqId_CLK_1650MHZ] = 1650U,
    [MCAL_SOC_RcmPllFoutFreqId_CLK_800MHZ] = 800U,       [MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ] = 900U,
    [MCAL_SOC_RcmPllFoutFreqId_CLK_2000MHZ] = 2000U,     [MCAL_SOC_RcmPllFoutFreqId_CLK_1800MHZ] = 1800U,
    [MCAL_SOC_RcmPllFoutFreqId_CLK_1920MHZ] = 1920U,     [MCAL_SOC_RcmPllFoutFreqId_CLK_1699p21875MHZ] = 1699U,
    [MCAL_SOC_RcmPllFoutFreqId_CLK_1728MHZ] = 1728U,     [MCAL_SOC_RcmPllFoutFreqId_CLK_1966p08MHZ] = 1966U,
    [MCAL_SOC_RcmPllFoutFreqId_CLK_1806p336MHZ] = 1806U,
};
#endif

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"
/** \brief MCU driver object */
extern P2CONST(Mcu_ConfigType, MCU_DATA, MCU_PBCFG) Mcu_DrvObj;

#define MCU_START_SEC_CODE
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Mcu_MemMap.h"

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Mcu_controlModuleUnlockMMR(uint32 domainId);
static void Mcu_controlModuleLockMMR(uint32 domainId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if (STD_OFF == MCU_NO_PLL)
Mcu_PllStatusType Mcu_GetPllLockStatus(void)
{
    uint32            oeRegVal1 = 0U;
    uint32            oeRegVal2 = 0U;
    uint32            oeRegVal3 = 0U;
    Mcu_PllStatusType pllStatus;

    oeRegVal1 = HW_RD_REG32(&toprcmREG->PLL_CORE_STATUS);
    oeRegVal2 = HW_RD_REG32(&toprcmREG->PLL_DSP_STATUS);
    oeRegVal3 = HW_RD_REG32(&toprcmREG->PLL_PER_STATUS);

    if (((oeRegVal1 & (uint32)0x400U) != 0U) && ((oeRegVal2 & (uint32)0x400U) != 0U) &&
        ((oeRegVal3 & (uint32)0x400U) != 0U))
    {
        pllStatus = MCU_PLL_LOCKED;
    }
    else
    {
        pllStatus = MCU_PLL_UNLOCKED;
    }

    return (pllStatus);
}
#endif

#if (STD_ON == MCU_PERFORM_RESET_API)
/*LDRA_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is updating  MCU register "
 **/
void Mcu_PerformSoftSysReset(uint32 resetVal)
{
#ifdef MCAL_DYNAMIC_BUILD
    /* Donot reset for LDRA analysis*/
#else
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    uint32 regWriteStatus = 0U;

    Mcu_controlModuleUnlockMMR(MCU_DOMAIN_ID_MSS_TOP_RCM);
    regWriteStatus = regWriteReadback(&toprcmREG->WARM_RESET_CONFIG, M_TEN, M_EIGHT, resetVal);
    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef MCU_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    Mcu_controlModuleLockMMR(MCU_DOMAIN_ID_MSS_TOP_RCM);
#endif
    return;
}
#endif /* STD_ON == MCU_PERFORM_RESET_API */

Mcu_ResetType Mcu_GetPlatformResetReason(void)
{
    uint32        resetRead = 0U;
    Mcu_ResetType resetType = MCU_RESET_UNDEFINED;

    resetRead = Mcu_GetPlatformRawResetReason();

    switch (resetRead)
    {
        case M_ZERO:
        {
            resetType = MCU_RESET_CLEAR;
            break;
        }
        case M_NINE:
        {
            resetType = MCU_POWER_ON_RESET;
            break;
        }
        case M_TEN:
        {
            resetType = MCU_WARM_RESET_WDT;
            break;
        }
        case M_TWELVE:
        {
            resetType = MCU_WARM_RESET;
            break;
        }
        case M_EIGHT:
        {
            resetType = MCU_EXT_PAD_RESET;
            break;
        }
        case M_TWENTY_FOUR:
        {
            resetType = MCU_HSM_WDT_RESET;
            break;
        }
        default:
            resetType = MCU_RESET_UNDEFINED;
            break;
    }

    return resetType;
}

Mcu_RawResetType Mcu_GetPlatformRawResetReason(void)
{
    Mcu_RawResetType rawResetReason = 0U;

    Mcu_controlModuleUnlockMMR(MCU_DOMAIN_ID_MSS_TOP_RCM);

    /* Get reset reason, stored in SPARE_RW0 by startup code */
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */

    rawResetReason = (Mcu_RawResetType)toprcmREG->SYS_RST_CAUSE;

    HW_SET_FIELD32(toprcmREG->SYS_RST_CAUSE_CLR, MSS_TOPRCM_SYS_RST_CAUSE_CLR_SYS_RST_CAUSE_CLR_CLEAR, 0x1);

    Mcu_controlModuleLockMMR(MCU_DOMAIN_ID_MSS_TOP_RCM);

    return rawResetReason;
}

FUNC(void, MCU_CODE) Mcu_SystemInit(void)
{
    Mcal_Libs_Utils_unlockMMR();

#if (STD_OFF == MCU_NO_PLL)
    if (Mcu_PllStatus != MCU_STATE_INIT) /* Checking whether PLL is already initialised or not */
    {
        /* Invoking PLL init API */
        if (Mcu_PLLInitAll(Mcu_DrvObj) == E_OK)
        {
            Mcu_PllStatus = MCU_STATE_INIT; /* Updating PLL status object as initialized */
        }
    }
#endif

    Mcu_SetupClock();
    Mcal_Libs_Utils_lockMMR();
}

/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
       Reason : LDRA tool issue */
FUNC(void, MCU_CODE) Mcu_SetupClock(void)
{
    uint8  idx;
    uint32 Avoid_nested_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    /* Config Clock */
    for (idx = 0U; idx < Mcu_DrvObj->Mcu_NumberOfClockConfig; idx++)
    {
        Avoid_nested_flag = 0U;
        if (Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_InitCfg == (boolean)TRUE)
        {
            Std_ReturnType status = E_NOT_OK;
            if (MCU_CLKSRC_MAX > Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockSourceId)
            {
                status            = Mcu_ClockSetSource(Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockModuleId,
                                                       Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockSourceId,
                                                       Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_ClockDiv,
                                                       Mcu_DrvObj->Mcu_ClockConfig[idx].Mcu_InitCfg);
                Avoid_nested_flag = 1U;
            }
            if ((Avoid_nested_flag == 1U) && (status != ((Std_ReturnType)E_OK)))
            {
#if (STD_ON == MCU_DEV_ERROR_DETECT)
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT, MCU_E_PARAM_CONFIG);
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            }

            if (Avoid_nested_flag == 0U)
            {
#if (STD_ON == MCU_DEV_ERROR_DETECT)
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_INIT, MCU_E_PARAM_CONFIG);
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            }
        }
    }
    return;
}

uint32 Mcu_getMultibitValue(uint32 clk_srcId)
{
    uint32 multibitValue = 0;

    multibitValue = (clk_srcId << 8) | (clk_srcId << 4) | (clk_srcId);

    return multibitValue;
}

Std_ReturnType Mcu_ClockSetSourceCR5(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal       = E_OK;
    uint32         hsdivClkout2 = 0U, Condition_check = 0U;
    uint32         regWriteStatus = 0U;

    hsdivClkout2 = MCAL_SOC_rcmExtract8(toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT2, 4U, 0U);

    /* Errata i2387 fix: set staggered PLL config to nullify the GCM circuit glitch in case of 200
     * MHz and 400 MHz */
    if ((clk_srcId != MCU_CLKSRC_2) && (hsdivClkout2 == 1U))
    {
        Condition_check = 1U;
        /* Switch back to XTAL */
        regWriteStatus = regWriteReadback(&toprcmREG->MSS_CR5_CLK_SRC_SEL, M_ELEVEN, M_ZERO, 0U);
        Mcu_Timeoutevent(&toprcmREG->MSS_CR5_CLK_SRC_SEL, 0U, MCU_TIMEOUT_DURATION);

        regWriteStatus |= regWriteReadback(&toprcmREG->MSS_CR5_DIV_VAL, M_ELEVEN, M_ZERO, 0U);

        /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
         * i2324 */
        Mcu_Timeoutevent(&toprcmREG->MSS_CR5_DIV_VAL, 0U, MCU_TIMEOUT_DURATION);
        regWriteStatus |= regWriteReadback(&toprcmREG->SYS_CLK_DIV_VAL, M_ELEVEN, M_ZERO, 0U);

        /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
         * i2324 */
        Mcu_Timeoutevent(&toprcmREG->SYS_CLK_DIV_VAL, 0U, MCU_TIMEOUT_DURATION);

        Mcu_ClockSetSourceCR5_1();
    }
    Mcu_ClockSetSourceCR5_Condition(&Condition_check, clk_srcId, hsdivClkout2);
    Mcu_ClockSetSourceCR5_hsdivClkout2(&Condition_check, clk_srcId, clk_divId);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

static void Mcu_ClockSetSourceCR5_1(void)
{
    uint32 regWriteStatus = 0U;

    /* Suppress the glitch */
    regWriteStatus = regWriteReadback(&toprcmREG->MSS_CR5_DIV_VAL, M_ELEVEN, M_ZERO, 0x111);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->MSS_CR5_DIV_VAL, 0x111U, MCU_TIMEOUT_DURATION);

    /* R5F and SYS clocks are in the ratio 1:2 */
    regWriteStatus |= regWriteReadback(&toprcmREG->SYS_CLK_DIV_VAL, M_ELEVEN, M_ZERO, 0x111);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->SYS_CLK_DIV_VAL, 0x111U, MCU_TIMEOUT_DURATION);

    /* Switch to PLL clock */
    regWriteStatus |= regWriteReadback(&toprcmREG->MSS_CR5_CLK_SRC_SEL, M_ELEVEN, M_ZERO, 0x222U);

    Mcu_Timeoutevent(&toprcmREG->MSS_CR5_CLK_SRC_SEL, 0x222U, MCU_TIMEOUT_DURATION);

    /* Switch back to 400 MHz */
    regWriteStatus |= regWriteReadback(&toprcmREG->MSS_CR5_DIV_VAL, M_ELEVEN, M_ZERO, 0U);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->MSS_CR5_DIV_VAL, 0U, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef MCU_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
}

static void Mcu_ClockSetSourceCR5_Condition(uint32 *Condition_check, Mcu_ClkSourceIdType clk_srcId, uint32 hsdivClkout2)
{
    VAR(uint32, MCU_VAR) regWriteStatus = 0U;

    if ((*Condition_check == 0U) && (clk_srcId != MCU_CLKSRC_2) && (hsdivClkout2 == 3U))
    {
        *Condition_check = 1U;
        /* Switch back to XTAL */
        regWriteStatus = regWriteReadback(&toprcmREG->MSS_CR5_CLK_SRC_SEL, M_ELEVEN, M_ZERO, 0U);

        Mcu_Timeoutevent(&toprcmREG->MSS_CR5_CLK_SRC_SEL, 0U, MCU_TIMEOUT_DURATION);

        regWriteStatus |= regWriteReadback(&toprcmREG->MSS_CR5_DIV_VAL, M_ELEVEN, M_ZERO, 0U);

        /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
         * i2324 */
        Mcu_Timeoutevent(&toprcmREG->MSS_CR5_DIV_VAL, 0U, MCU_TIMEOUT_DURATION);

        regWriteStatus |= regWriteReadback(&toprcmREG->SYS_CLK_DIV_VAL, M_ELEVEN, M_ZERO, 0U);

        /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
         * i2324 */
        Mcu_Timeoutevent(&toprcmREG->SYS_CLK_DIV_VAL, 0U, MCU_TIMEOUT_DURATION);
        Mcu_ClockSetSourceCR5_div_3();

        if (regWriteStatus != MCAL_REGWR_E_OK)
        {
#ifdef MCU_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }
    }
}

static void Mcu_ClockSetSourceCR5_div_3(void)
{
    uint32 regWriteStatus = 0U;

    /* Suppress the glitch */
    regWriteStatus = regWriteReadback(&toprcmREG->MSS_CR5_DIV_VAL, M_ELEVEN, M_ZERO, 0x111);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->MSS_CR5_DIV_VAL, 0x111U, MCU_TIMEOUT_DURATION);
    /* R5F and SYS clocks are in the ratio 1:1 */
    regWriteStatus |= regWriteReadback(&toprcmREG->SYS_CLK_DIV_VAL, M_ELEVEN, M_ZERO, 0x0U);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->SYS_CLK_DIV_VAL, 0x0U, MCU_TIMEOUT_DURATION);
    /* Switch to PLL clock */
    regWriteStatus |= regWriteReadback(&toprcmREG->MSS_CR5_CLK_SRC_SEL, M_ELEVEN, M_ZERO, 0x222U);

    Mcu_Timeoutevent(&toprcmREG->MSS_CR5_CLK_SRC_SEL, 0x222U, MCU_TIMEOUT_DURATION);
    /* Switch back to 400 MHz */
    regWriteStatus |= regWriteReadback(&toprcmREG->MSS_CR5_DIV_VAL, M_ELEVEN, M_ZERO, 0U);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->MSS_CR5_DIV_VAL, 0U, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef MCU_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
}

static void Mcu_ClockSetSourceCR5_hsdivClkout2(uint32 *Condition_check, Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    uint32 clkSrcVal      = 0;
    uint32 clkDivVal      = 0;
    uint32 regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);
    if (*Condition_check == 0U)
    {
        *Condition_check = 1U;
        regWriteStatus   = regWriteReadback(&toprcmREG->MSS_CR5_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

        /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
         * i2324 */
        Mcu_Timeoutevent(&toprcmREG->MSS_CR5_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
        /* Klocwork inspected. MISRA C 2012 Rule 11.4
        Need to read the corresponding register address */
        regWriteStatus |= regWriteReadback(&toprcmREG->MSS_CR5_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

        Mcu_Timeoutevent(&toprcmREG->MSS_CR5_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

        if (regWriteStatus != MCAL_REGWR_E_OK)
        {
#ifdef MCU_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }
    }
}

Std_ReturnType Mcu_ClockSetSourceMCANA(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_MCANA_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_MCANA_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_MCANA_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_MCANA_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMCANB(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_MCANB_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_MCANB_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_MCANB_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_MCANB_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRTIA(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_RTIA_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_RTIA_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_RTIA_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_RTIA_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRTIB(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_RTIB_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_RTIB_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_RTIB_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_RTIB_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRTIC(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_RTIC_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_RTIC_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_RTIC_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_RTIC_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceWDT(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_WDT_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_WDT_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_WDT_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_WDT_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceQSPI(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_QSPI_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_QSPI_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_QSPI_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_QSPI_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSPIA(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_SPIA_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_SPIA_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_SPIA_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_SPIA_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSPIB(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_SPIB_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_SPIB_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_SPIB_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_SPIB_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceI2C(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_I2C_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_I2C_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_I2C_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_I2C_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCIA(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_SCIA_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_SCIA_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_SCIA_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_SCIA_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceSCIB(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_SCIB_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_SCIB_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_SCIB_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_SCIB_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceCPSW(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_CPSW_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_CPSW_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_CPSW_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_CPSW_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceCPTS(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_CPTS_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_CPTS_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&mssrcmREG->MSS_CPTS_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&mssrcmREG->MSS_CPTS_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceHSIClk(Mcu_ClkSourceIdType clk_srcId)
{
    /* Div value has no effect in case of HSI CLK */
    uint32         clkSrcVal      = 0;
    uint32         regWriteStatus = 0U;
    Std_ReturnType retVal         = E_OK;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&toprcmREG->HSI_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->HSI_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceCSIRXClk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&toprcmREG->CSIRX_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->CSIRX_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&toprcmREG->CSIRX_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->CSIRX_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMcuClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&toprcmREG->MCUCLKOUT_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->MCUCLKOUT_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&toprcmREG->MCUCLKOUT_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->MCUCLKOUT_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourcePmicClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&toprcmREG->PMICCLKOUT_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->PMICCLKOUT_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&toprcmREG->PMICCLKOUT_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->PMICCLKOUT_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceObsClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    Std_ReturnType retVal         = E_OK;
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&toprcmREG->OBSCLKOUT_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->OBSCLKOUT_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&toprcmREG->OBSCLKOUT_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->OBSCLKOUT_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceTRCClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    uint32         clkSrcVal      = 0;
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;
    Std_ReturnType retVal         = E_OK;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&toprcmREG->TRCCLKOUT_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&toprcmREG->TRCCLKOUT_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback(&toprcmREG->TRCCLKOUT_CLK_SRC_SEL, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent(&toprcmREG->TRCCLKOUT_CLK_SRC_SEL, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMII100Clk(uint32 clk_divId)
{
    /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;
    Std_ReturnType retVal         = E_OK;

    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_MII100_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_MII100_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceMII10Clk(uint32 clk_divId)
{
    /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;
    Std_ReturnType retVal         = E_OK;

    clkDivVal = (clk_divId << 16) | (clk_divId << 8) | (clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_MII10_CLK_DIV_VAL, M_TWENTY_THREE, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_MII10_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRGMIClk(uint32 clk_divId)
{
    /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;
    Std_ReturnType retVal         = E_OK;

    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_RGMII_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_RGMII_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceGpadcClk(uint32 clk_divId)
{
    /*Clk source is fixed to SYS_CLK*/
    uint32         clkDivVal      = 0;
    uint32         regWriteStatus = 0U;
    Std_ReturnType retVal         = E_OK;

    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback(&mssrcmREG->MSS_GPADC_CLK_DIV_VAL, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent(&mssrcmREG->MSS_GPADC_CLK_DIV_VAL, clkDivVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRCSSSPIA(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    uint32         clkSrcVal          = 0;
    uint32         clkDivVal          = 0;
    uint32         rcssSpiA_ClkSrcReg = 0x05000020;
    uint32         rcssSpiA_ClkDivReg = 0x0500005C;
    uint32         regWriteStatus     = 0U;
    Std_ReturnType retVal             = E_OK;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback((uint32 *)rcssSpiA_ClkDivReg, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent((uint32 *)rcssSpiA_ClkDivReg, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback((uint32 *)rcssSpiA_ClkSrcReg, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent((uint32 *)rcssSpiA_ClkSrcReg, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType Mcu_ClockSetSourceRCSSSPIB(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId)
{
    uint32         clkSrcVal          = 0;
    uint32         clkDivVal          = 0;
    uint32         rcssSpiB_ClkSrcReg = 0x05000024;
    uint32         rcssSpiB_ClkDivReg = 0x05000060;
    uint32         regWriteStatus     = 0U;
    Std_ReturnType retVal             = E_OK;

    clkSrcVal = Mcu_getMultibitValue((uint32)clk_srcId);
    clkDivVal = Mcu_getMultibitValue(clk_divId);

    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus = regWriteReadback((uint32 *)rcssSpiB_ClkDivReg, M_ELEVEN, M_ZERO, clkDivVal);

    /* Poll the CLKDIV and SRC_SEL register to make sure the value is synchronized. Errata Fix:
     * i2324 */
    Mcu_Timeoutevent((uint32 *)rcssSpiB_ClkDivReg, clkDivVal, MCU_TIMEOUT_DURATION);
    /* Klocwork inspected. MISRA C 2012 Rule 11.4
       Need to read the corresponding register address */
    regWriteStatus |= regWriteReadback((uint32 *)rcssSpiB_ClkSrcReg, M_ELEVEN, M_ZERO, clkSrcVal);

    Mcu_Timeoutevent((uint32 *)rcssSpiB_ClkSrcReg, clkSrcVal, MCU_TIMEOUT_DURATION);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

FUNC(Std_ReturnType, MCU_CODE)
Mcu_ClockSetSource(Mcu_ClkModuleIdType moduleId, Mcu_ClkSourceIdType clkSrcId, uint32 clkDivId, boolean enable)
{
    Std_ReturnType retVal    = E_OK;
    Std_ReturnType defRetVal = E_OK;

    switch (moduleId)
    {
        case MCU_CLKSRC_MODULE_ID_CR5:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceCR5(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCANA:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceMCANA(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCANB:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceMCANB(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RTIA:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceRTIA(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RTIB:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceRTIB(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RTIC:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceRTIC(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_WDT:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceWDT(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_QSPI:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceQSPI(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SPIA:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceSPIA(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SPIB:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceSPIB(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_I2C:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceI2C(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCIA:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceSCIA(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_SCIB:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceSCIB(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_CPSW:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceCPSW(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_CPTS:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceCPTS(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_HSI_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceHSIClk(clkSrcId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_CSIRX:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceCSIRXClk(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MCU_CLKOUT:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceMcuClkout(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_PMIC_CLKOUT:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourcePmicClkout(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_OBS_CLKOUT:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceObsClkout(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_TRC_CLKOUT:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceTRCClkout(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MII100_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                retVal = Mcu_ClockSetSourceMII100Clk(clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_MII10_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                retVal = Mcu_ClockSetSourceMII10Clk(clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RGMI_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                retVal = Mcu_ClockSetSourceRGMIClk(clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_GPADC_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                /*Clk source is fixed to DPLL_CORE_HSDIV0_CLKOUT1*/
                retVal = Mcu_ClockSetSourceGpadcClk(clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RCSSSPIA_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceRCSSSPIA(clkSrcId, clkDivId);
            }
            break;
        }
        case MCU_CLKSRC_MODULE_ID_RCSSSPIB_CLK:
        {
            if (enable == (boolean)TRUE)
            {
                retVal = Mcu_ClockSetSourceRCSSSPIB(clkSrcId, clkDivId);
            }
            break;
        }
        default:
            retVal    = (Std_ReturnType)E_NOT_OK;
            defRetVal = (Std_ReturnType)E_NOT_OK;
            break;
    }

    if ((retVal != E_OK) && (defRetVal == E_OK))
    {
#ifdef MCU_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)MCU_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

#if (STD_OFF == MCU_NO_PLL)

static uint32 SOC_rcmMake8(uint8 msb, uint8 lsb, uint8 val)
{
    uint32 mask;
    uint8  bits;
    uint32 newVal;

    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    newVal = (uint32)val & mask;

    return (newVal << lsb);
}

static uint32 SOC_rcmMake16(uint8 msb, uint8 lsb, uint16 val)
{
    uint32 mask;
    uint8  bits;
    uint32 newVal;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    newVal = (uint32)val & mask;

    return (newVal << lsb);
}

static uint32 SOC_rcmMake32(uint8 msb, uint8 lsb, uint32 val)
{
    uint32 mask;
    uint8  bits;
    uint32 newVal;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    newVal = val & mask;

    return (newVal << lsb);
}

static uint16 MCAL_SOC_rcmExtract16(volatile uint32 reg, uint8 msb, uint8 lsb)
{
    uint32 mask;
    uint8  bits;
    uint16 value;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    value = (uint16)((reg >> lsb) & mask);
    return value;
}

static uint32 MCAL_SOC_rcmExtract32(volatile uint32 reg, uint8 msb, uint8 lsb)
{
    uint32 mask;
    uint8  bits;
    uint32 value;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    value = (reg >> lsb) & mask;
    return value;
}

static uint32 MCAL_SOC_rcmInsert8(volatile uint32 reg, uint8 msb, uint8 lsb, uint8 val)
{
    uint32 mask;
    uint8  bits;
    uint32 value;
    uint32 tmp;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    value = (mask << lsb);
    tmp   = (reg & ~value);
    return (tmp | SOC_rcmMake8(msb, lsb, val));
}

static uint32 MCAL_SOC_rcmInsert16(volatile uint32 reg, uint8 msb, uint8 lsb, uint16 val)
{
    uint32 mask;
    uint8  bits;
    uint32 value;
    uint32 tmp;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    value = (mask << lsb);
    tmp   = (reg & ~value);
    return (tmp | SOC_rcmMake16(msb, lsb, val));
}

static uint32 MCAL_SOC_rcmInsert32(volatile uint32 reg, uint8 msb, uint8 lsb, uint32 val)
{
    uint32 mask;
    uint8  bits;
    uint32 value;
    uint32 tmp;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    value = (mask << lsb);
    tmp   = (reg & ~value);
    return (tmp | SOC_rcmMake32(msb, lsb, val));
}

static uint32 MCAL_SOC_rcmGetADPLLJFout(uint32 Finp, uint32 N, uint32 M, uint32 M2, uint32 FracM, uint32 div2flag)
{
    uint32 i;
    uint32 FOut;
    uint32 Nmatch;

    if (div2flag != (uint32)0)
    {
        Nmatch = ((N + (uint32)1) * (uint32)2) - (uint32)1;
    }
    else
    {
        Nmatch = N;
    }
    for (i = 0; i < MCAL_SOC_RCM_UTILS_ARRAYSIZE(Mcu_SocRcmADPLLJConfigTbl); i++)
    {
        if ((Mcu_SocRcmADPLLJConfigTbl[i].Finp == Finp) && (Mcu_SocRcmADPLLJConfigTbl[i].FracM == FracM) &&
            (Mcu_SocRcmADPLLJConfigTbl[i].M == M) && (Mcu_SocRcmADPLLJConfigTbl[i].M2 == M2) &&
            (Mcu_SocRcmADPLLJConfigTbl[i].N == Nmatch))
        {
            break;
        }
    }
    if (i < MCAL_SOC_RCM_UTILS_ARRAYSIZE(Mcu_SocRcmADPLLJConfigTbl))
    {
        FOut = MCAL_SOC_RCM_FREQ_MHZ2HZ(Mcu_SocRcmADPLLJConfigTbl[i].Fout);
    }
    else
    {
        FOut = 0;
    }
    return FOut;
}

static uint32 MCAL_SOC_rcmGetCoreFout(uint32 Finp, uint32 div2flag)
{
    uint8  pllSwitchFlag;
    uint32 FOut;

    /* read the Core PLL Lock status */
    pllSwitchFlag = MCAL_SOC_rcmExtract8(toprcmREG->PLL_CORE_STATUS, 10U, 10U);
    if (pllSwitchFlag != (uint8)0)
    {
        uint32 M, N, M2, FracM;

        N     = HW_GET_FIELD(toprcmREG->PLL_CORE_M2NDIV, MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_N);
        M2    = HW_GET_FIELD(toprcmREG->PLL_CORE_M2NDIV, MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_M2);
        M     = HW_GET_FIELD(toprcmREG->PLL_CORE_MN2DIV, MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_M);
        FracM = HW_GET_FIELD(toprcmREG->PLL_CORE_FRACDIV, MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_FRACTIONALM);
        FOut  = MCAL_SOC_rcmGetADPLLJFout(Finp, N, M, M2, FracM, div2flag);
        /*DebugP_assert(FOut != 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
        if (FOut == (uint32)0)
        {
            (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
        }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
    }
    else
    {
        uint32 ULOWCLKEN =
            HW_GET_FIELD(toprcmREG->PLL_CORE_CLKCTRL, MSS_TOPRCM_PLL_CORE_CLKCTRL_PLL_CORE_CLKCTRL_ULOWCLKEN);
        if (ULOWCLKEN == (uint32)0)
        {
            uint32 N2;

            N2   = HW_GET_FIELD(toprcmREG->PLL_CORE_MN2DIV, MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_N2);
            FOut = Finp / (N2 + (uint32)1);
        }
        else
        {
            FOut = Finp;
        }
    }
    return FOut;
}

static uint8 MCAL_SOC_rcmReadXtalFreqScale(const topCtrlBASE_t *ptrTopCtrlRegs)
{
    return (MCAL_SOC_rcmExtract8(ptrTopCtrlRegs->EFUSE1_ROW_10, MCAL_SOC_RCM_XTAL_FREQ_SCALE_END_BIT,
                                 MCAL_SOC_RCM_XTAL_FREQ_SCALE_START_BIT));
}

static uint8 MCAL_SOC_rcmReadCoreADPLLTrimValidEfuse(const topCtrlBASE_t *ptrTopCtrlRegs)
{
    return (MCAL_SOC_rcmExtract8(ptrTopCtrlRegs->EFUSE1_ROW_41, MCAL_SOC_RCM_COREADPLLTRIMVALIDCONFIG_END_BIT,
                                 MCAL_SOC_RCM_COREADPLLTRIMVALIDCONFIG_START_BIT));
}

static uint8 MCAL_SOC_rcmReadDspADPLLTrimValidEfuse(const topCtrlBASE_t *ptrTopCtrlRegs)
{
    return (MCAL_SOC_rcmExtract8(ptrTopCtrlRegs->EFUSE1_ROW_41, MCAL_SOC_RCM_DSPADPLLTRIMVALIDCONFIG_END_BIT,
                                 MCAL_SOC_RCM_DSPADPLLTRIMVALIDCONFIG_START_BIT));
}

static uint8 MCAL_SOC_rcmReadPerADPLLTrimValidEfuse(const topCtrlBASE_t *ptrTopCtrlRegs)
{
    return (MCAL_SOC_rcmExtract8(ptrTopCtrlRegs->EFUSE1_ROW_41, MCAL_SOC_RCM_PERADPLLTRIMVALIDCONFIG_END_BIT,
                                 MCAL_SOC_RCM_PERADPLLTRIMVALIDCONFIG_START_BIT));
}

static uint16 MCAL_SOC_rcmReadDspADPLLTrimEfuse(const topCtrlBASE_t *ptrTopCtrlRegs)
{
    return (MCAL_SOC_rcmExtract16(ptrTopCtrlRegs->EFUSE1_ROW_40, MCAL_SOC_RCM_DSPADPLLTRIMCONFIG_END_BIT,
                                  MCAL_SOC_RCM_DSPADPLLTRIMCONFIG_START_BIT));
}

static uint16 MCAL_SOC_rcmReadPerADPLLTrimEfuse(const topCtrlBASE_t *ptrTopCtrlRegs)
{
    return (MCAL_SOC_rcmExtract16(ptrTopCtrlRegs->EFUSE1_ROW_41, MCAL_SOC_RCM_PERADPLLTRIMCONFIG_END_BIT,
                                  MCAL_SOC_RCM_PERADPLLTRIMCONFIG_START_BIT));
}

/* PLL Init Functions */
static MCAL_SOC_RcmXtalFreqId MCAL_SOC_rcmGetXtalFrequency(void)
{
    uint32                 xtalRegVal;
    MCAL_SOC_RcmXtalFreqId freq;
    uint8                  xtalFreqScale;

    /* read the register bits corresponding to XTAL Frequency */
    xtalRegVal = MCAL_SOC_rcmExtract32(toprcmREG->ANA_REG_WU_MODE_REG_LOWV, 6U, 5U);
    /* read the register bits corresponding to XTAL Frequency Scale */
    xtalFreqScale = MCAL_SOC_rcmReadXtalFreqScale(topctrlREG);

    if (xtalFreqScale == 1U)
    {
        if (xtalRegVal == 0U)
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_20MHZ;
        }
        else if (xtalRegVal == 1U)
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_22p5792MHZ;
        }
        else if (xtalRegVal == 2U)
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_24p576MHZ;
        }
        else
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_25MHZ;
        }
    }
    else
    {
        if (xtalRegVal == 0U)
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_40MHZ;
        }
        else if (xtalRegVal == 1U)
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_45p1584MHZ;
        }
        else if (xtalRegVal == 2U)
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_49p152MHZ;
        }
        else
        {
            freq = MCAL_SOC_RcmXtalFreqId_CLK_50MHZ;
        }
    }

    return (freq);
}

static uint16 MCAL_SOC_rcmGetDspTrimVal(void)
{
    uint8  dspADPLLValid;
    uint16 dspADPLLTrimVal;

    dspADPLLValid = MCAL_SOC_rcmReadDspADPLLTrimValidEfuse(topctrlREG);

    if (dspADPLLValid == 1U)
    {
        dspADPLLTrimVal = MCAL_SOC_rcmReadDspADPLLTrimEfuse(topctrlREG);
    }
    else
    {
        dspADPLLTrimVal = (uint16)MCAL_SOC_RCM_DSP_ADPLL_DEFAULT_VALUE;
    }
    return (dspADPLLTrimVal);
}

static MCAL_SOC_RcmADPLLJConfig const *MCAL_SOC_rcmGetADPLLJConfig(uint32 Finp, MCAL_SOC_RcmPllFoutFreqId foutFreqId)
{
    uint32                          i;
    MCAL_SOC_RcmADPLLJConfig const *adplljCfg;
    uint32                          Fout;

    Fout = Mcu_SocRcmPllFreqId2FOutMap[foutFreqId];
    for (i = 0; i < MCAL_SOC_RCM_UTILS_ARRAYSIZE(Mcu_SocRcmADPLLJConfigTbl); i++)
    {
        if ((Mcu_SocRcmADPLLJConfigTbl[i].Finp == Finp) && (Mcu_SocRcmADPLLJConfigTbl[i].Fout == Fout))
        {
            break;
        }
    }
    if (i < MCAL_SOC_RCM_UTILS_ARRAYSIZE(Mcu_SocRcmADPLLJConfigTbl))
    {
        adplljCfg = &Mcu_SocRcmADPLLJConfigTbl[i];
    }
    else
    {
        adplljCfg = (MCAL_SOC_RcmADPLLJConfig const *)NULL_PTR;
    }
    return adplljCfg;
}

static void MCAL_SOC_rcmProgPllDspDivider(uint32 inputClockDiv, uint8 divider, uint32 multiplier, uint32 postDivider,
                                          uint32 fracMultiplier)
{
    volatile uint32 *ptrM2NReg, *ptrMN2Reg, *ptrFracMReg;

    ptrM2NReg   = &(toprcmREG->PLL_DSP_M2NDIV);
    ptrMN2Reg   = &(toprcmREG->PLL_DSP_MN2DIV);
    ptrFracMReg = &(toprcmREG->PLL_DSP_FRACDIV);

    /* Initialization sequence referred from ADPLLLJ_GS70_v0.8-02 */
    /* program M2 (post divider) */
    /* GEL file equivalent*/
    /* APPLJ-2 Setting*/
    /* CLOCKOUT = M/(N+1) * CLKINP * (1/M2)  =  0x708/(39+1) * 40 * (1/1) = 1.8G*/
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_M2NDIV     , 0x10027);      M2NDIV_M2[22:16] = 1 ,
     * M2NDIV_N[7:0] = 0x27*/
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_MN2DIV     , 0x10708);      MN2DIV_N2[19:16] = 1 ,
     * MN2DIV_M[11:0] = 0x708*/
    *ptrM2NReg = MCAL_SOC_rcmInsert8(*ptrM2NReg, 22U, 16U, postDivider);

    /* program N (input clock divider) */
    *ptrM2NReg = MCAL_SOC_rcmInsert8(*ptrM2NReg, 7U, 0U, inputClockDiv);

    /* program M (multiplier) */
    *ptrMN2Reg = MCAL_SOC_rcmInsert16(*ptrMN2Reg, 11U, 0U, multiplier);

    /* program N2 (divider) */
    *ptrMN2Reg = MCAL_SOC_rcmInsert8(*ptrMN2Reg, 19U, 16U, divider);

    /* program Fractional Multiplier */
    *ptrFracMReg = MCAL_SOC_rcmInsert32(*ptrFracMReg, 17U, 0U, fracMultiplier);

    if (multiplier == (uint32)1650)
    {
        *ptrFracMReg = MCAL_SOC_rcmInsert32(*ptrFracMReg, 31U, 24U, 7U);
    }
}

static void MCAL_SOC_rcmConfigurePllDsp(uint16 trimVal)
{
    volatile uint32 *ptrClkCtrl, *ptrTenable, *ptrTenableDiv, *ptrPllStatus;

    /* Core PLL settings */
    ptrClkCtrl    = &(toprcmREG->PLL_DSP_CLKCTRL);
    ptrTenable    = &(toprcmREG->PLL_DSP_TENABLE);
    ptrTenableDiv = &(toprcmREG->PLL_DSP_TENABLEDIV);
    ptrPllStatus  = &(toprcmREG->PLL_DSP_STATUS);

    /* update the Clock control setting */
    /* program CLKDCOLDOEN[29] = 1, IDLE[23] = 0, CLKDCOLDOPWDNZ[17] = 1, SELFREQDCO[12:10] = 4 */
    /* GEL file equivalent */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_CLKCTRL    , 0x29021000);   CLKDCOLDOEN[29] =
     * 1,NWELLTRIM[28:24] = 9 IDLE[23] = 0 CLKDCOLDOPWDNZ[17] = 1 SELFREQDCO[12:10] = 4*/

    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_TENABLE    , 0x1);          TENABLE    = 1 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_CLKCTRL    , 0x29021001);   +TINTZ[0]   = 1 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_TENABLE    , 0x0);          TENABLE    = 0 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_TENABLEDIV , 0x1);          TENABLEDIV = 1 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_TENABLEDIV , 0x0);          TENABLEDIV = 0 */

    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 29U, 29U, 0x1U);
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 23U, 23U, 0x0U);
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 17U, 17U, 0x1U);
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 12U, 10U, 0x4U);

    /* Write Nwell Trim Value */
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 28U, 24U, ((uint8)trimVal & 0x1FU));

    /* Soft reset Pll */
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 0U, 0U, 0x0U);

    /* TENABLE High */
    *ptrTenable = MCAL_SOC_rcmInsert8(*ptrTenable, 0U, 0U, 0x1U);

    /* out of reset Pll */
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 0U, 0U, 0x1U);

    /* TENABLE Low */
    *ptrTenable = MCAL_SOC_rcmInsert8(*ptrTenable, 0U, 0U, 0x0U);

    /* TENABLEDIV High */
    *ptrTenableDiv = MCAL_SOC_rcmInsert8(*ptrTenableDiv, 0U, 0U, 0x1U);

    /* TENABLEDIV Low */
    *ptrTenableDiv = MCAL_SOC_rcmInsert8(*ptrTenableDiv, 0U, 0U, 0x0U);

    /* wait for the Phase lock for Core/DSP PLL */
    /* GEL File equivalent*/
    /* APPLJ-2 : loop check to PLLLOCK DONE*/
    /* lock_status = HW_RD_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_STATUS); PHASELOCK[10]*/
    /* while(0x400 != (lock_status & 0x400)) {*/
    /*   lock_status = HW_RD_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_STATUS); PHASELOCK[10]*/
    /* }*/
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    volatile uint32 timeout_duration = 500U * 16U; /*Phase Lock time is 500 REFCLK cycles*/
    /* Wait for FSM to to come out of reset */
    while ((uint32)0x400U != (HW_RD_REG32(ptrPllStatus) & (uint32)0x400U))
    {
        /* Below API can change start time, so use temp variable */
        if (timeout_duration <= 0U)
        {
#ifdef MCU_E_CLOCK_FAILURE
            /* timeout */
            (void)Dem_SetEventStatus(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(timeout_duration);
        /*LDRA_INSPECTED 28 D : MISRAC_2012_R.2.1
         * "Reason - Infinite Loop has been taken care by
         * implementing timeout " */
    }
}

static uint16 MCAL_SOC_rcmGetPerTrimVal(void)
{
    uint8  perADPLLValid;
    uint16 perADPLLTrimVal;

    perADPLLValid = MCAL_SOC_rcmReadPerADPLLTrimValidEfuse(topctrlREG);

    if (perADPLLValid == 1U)
    {
        perADPLLTrimVal = MCAL_SOC_rcmReadPerADPLLTrimEfuse(topctrlREG);
    }
    else
    {
        perADPLLTrimVal = (uint16)MCAL_SOC_RCM_PER_ADPLL_DEFAULT_VALUE;
    }
    return (perADPLLTrimVal);
}

static void MCAL_SOC_rcmCoreApllHSDivConfig(const MCAL_SOC_RcmPllHsDivOutConfig *hsDivCfg)
{
    uint32                 hsDivOutRegVal;
    uint32                 Fout;
    uint32                 Finp;
    MCAL_SOC_RcmXtalFreqId clkFreqId;
    volatile uint32       *ptrFracMReg;
    volatile uint32       *ptrCoreClkCtrlReg;

    /* Core PLL settings */
    clkFreqId = MCAL_SOC_rcmGetXtalFrequency();

    Finp = Mcu_SocRcmXtalInfo[clkFreqId].Finp;
    Fout = MCAL_SOC_rcmGetCoreFout(Finp, Mcu_SocRcmXtalInfo[clkFreqId].div2flag);

    /* Derive Clocks */
    /* TPR12_Ch08_Clock_Arch_0p91 is used as reference for below settings */
    /* Set clock divider values from Core PLL*/
    /* 400Mhz */
    if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0) != (uint32)0)
    {
        /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[0]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
        if ((Fout % hsDivCfg->hsDivOutFreqHz[0]) != (uint32)0)
        {
            (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
        }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
        hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[0];
        hsDivOutRegVal--;
        toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT0 =
            MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT0, 4U, 0U, hsDivOutRegVal);
    }
    if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1) != (uint32)0)
    {
        /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[1]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
        if ((Fout % hsDivCfg->hsDivOutFreqHz[1]) != (uint32)0)
        {
            (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
        }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
        hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[1];
        hsDivOutRegVal--;
        toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT1 =
            MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT1, 4U, 0U, hsDivOutRegVal);
    }
    if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2) != (uint32)0)
    {
        /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[2]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
        if ((Fout % hsDivCfg->hsDivOutFreqHz[2]) != (uint32)0)
        {
            (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
        }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
        hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[2];
        hsDivOutRegVal--;
        toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT2 =
            MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT2, 4U, 0U, hsDivOutRegVal);
    }
    /* Core PLL output 3 not used.WIll not configure */
    /* Generate Trigger to latch these values */
    toprcmREG->PLL_CORE_HSDIVIDER = MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER, 2U, 2U, 0x1U);
    toprcmREG->PLL_CORE_HSDIVIDER = MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER, 2U, 2U, 0x0U);

    /* Ungate the clocks */
    if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0) != (uint32)0)
    {
        toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT0 =
            MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT0, 8U, 8U, 0x1U);
    }
    if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1) != (uint32)0)
    {
        toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT1 =
            MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT1, 8U, 8U, 0x1U);
    }
    if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2) != (uint32)0)
    {
        toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT2 =
            MCAL_SOC_rcmInsert8(toprcmREG->PLL_CORE_HSDIVIDER_CLKOUT2, 8U, 8U, 0x1U);
    }
    /* If the PLL lock frequency is less than 1GHz, update the sigma delta divider and DCO
     * frequency. Errata: i2389 */
    if (Fout < (uint32)MCAL_SOC_RCM_FREQ_1GHZ)
    {
        ptrFracMReg = (&toprcmREG->PLL_CORE_FRACDIV);
        /* PLL_CORE_FRACDIV_REGSD_SHIFT, PLL_CORE_FRACDIV_REGSD_MASK */
        *ptrFracMReg = MCAL_SOC_rcmInsert8(*ptrFracMReg, 31U, 24U, 0x4);

        ptrCoreClkCtrlReg = (&toprcmREG->PLL_CORE_CLKCTRL);
        /* PLL_CORE_CLKCTRL_SELFREQDCO_SHIFT, PLL_CORE_CLKCTRL_SELFREQDCO_MASK */
        *ptrCoreClkCtrlReg = MCAL_SOC_rcmInsert8(*ptrCoreClkCtrlReg, 12U, 10U, 0x2);
    }

    return;
}

static void MCAL_SOC_rcmProgPllPerDivider(uint32 inputClockDiv, uint32 divider, uint32 multiplier, uint32 postDivider,
                                          uint32 fracMultiplier)
{
    volatile uint32 *ptrM2NReg, *ptrMN2Reg, *ptrFracMReg;

    ptrM2NReg   = &(toprcmREG->PLL_PER_M2NDIV);
    ptrMN2Reg   = &(toprcmREG->PLL_PER_MN2DIV);
    ptrFracMReg = &(toprcmREG->PLL_PER_FRACDIV);

    /* Initialization sequence referred from ADPLLLJ_GS70_v0.8-02 */
    /* program M2 (post divider) */
    /* GEL file equivalent */
    /* APPLJ-3 Setting */
    /* CLOCKOUT = M/(N+1) * CLKINP * (1/M2)  =  0x6C0/(39+1) * 40 * (1/1) = 1.728G */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_M2NDIV     , 0x10027);      M2NDIV_M2[22:16] = 1 ,
     * M2NDIV_N[7:0] = 0x27 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_MN2DIV     , 0x106C0);      MN2DIV_N2[19:16] = 1 ,
     * MN2DIV_M[11:0] = 0x6C0 */
    *ptrM2NReg = MCAL_SOC_rcmInsert8(*ptrM2NReg, 22U, 16U, postDivider);

    /* program N (input clock divider) */
    *ptrM2NReg = MCAL_SOC_rcmInsert8(*ptrM2NReg, 7U, 0U, inputClockDiv);

    /* program M (multiplier) */
    *ptrMN2Reg = MCAL_SOC_rcmInsert16(*ptrMN2Reg, 11U, 0U, multiplier);

    /* program N2 (divider) */
    *ptrMN2Reg = MCAL_SOC_rcmInsert8(*ptrMN2Reg, 19U, 16U, divider);

    /* program Fractional Multiplier */
    *ptrFracMReg = MCAL_SOC_rcmInsert32(*ptrFracMReg, 17U, 0U, fracMultiplier);
}

static void MCAL_SOC_rcmConfigurePllPer(uint16 trimVal)
{
    volatile uint32 *ptrClkCtrl, *ptrTenable, *ptrTenableDiv, *ptrPllStatus;

    /* Core PLL settings */
    ptrClkCtrl    = &(toprcmREG->PLL_PER_CLKCTRL);
    ptrTenable    = &(toprcmREG->PLL_PER_TENABLE);
    ptrTenableDiv = &(toprcmREG->PLL_PER_TENABLEDIV);
    ptrPllStatus  = &(toprcmREG->PLL_PER_STATUS);

    /* update the Clock control setting */
    /* program CLKDCOLDOEN[29] = 1, IDLE[23] = 0, CLKDCOLDOPWDNZ[17] = 1, SELFREQDCO[12:10] = 4 */
    /* GEL file equivalent */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_CLKCTRL    , 0x29021000);   CLKDCOLDOEN[29] =
     * 1,NWELLTRIM[28:24] = 9 IDLE[23] = 0 CLKDCOLDOPWDNZ[17] = 1 SELFREQDCO[12:10] = 4 */

    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_TENABLE    , 0x1);           TENABLE    = 1 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_CLKCTRL    , 0x29021001);   +TINTZ[0]   = 1 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_TENABLE    , 0x0);           TENABLE    = 0 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_TENABLEDIV , 0x1);           TENABLEDIV = 1 */
    /* HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_TENABLEDIV , 0x0);           TENABLEDIV = 0 */

    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 29U, 29U, 0x1U);
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 23U, 23U, 0x0U);
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 17U, 17U, 0x1U);
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 12U, 10U, 0x4U);

    /* Write Nwell Trim Value */
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 28U, 24U, ((uint8)trimVal & 0x1FU));

    /* Soft reset Pll */
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 0U, 0U, 0x0U);

    /* TENABLE High */
    *ptrTenable = MCAL_SOC_rcmInsert8(*ptrTenable, 0U, 0U, 0x1U);

    /* out of reset Pll */
    *ptrClkCtrl = MCAL_SOC_rcmInsert8(*ptrClkCtrl, 0U, 0U, 0x1U);

    /* TENABLE Low */
    *ptrTenable = MCAL_SOC_rcmInsert8(*ptrTenable, 0U, 0U, 0x0U);

    /* TENABLEDIV High */
    *ptrTenableDiv = MCAL_SOC_rcmInsert8(*ptrTenableDiv, 0U, 0U, 0x1U);

    /* TENABLEDIV Low */
    *ptrTenableDiv = MCAL_SOC_rcmInsert8(*ptrTenableDiv, 0U, 0U, 0x0U);

    /* wait for the Phase lock for Core/DSP PLL */
    /* GEL File equivalent*/
    /* APPLJ-3 : loop check to PLLLOCK DONE*/
    /* lock_status = HW_RD_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_STATUS); PHASELOCK[10]*/
    /* while(0x400 != (lock_status & 0x400)) {*/
    /*   lock_status = HW_RD_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_STATUS); PHASELOCK[10]*/
    /* }*/
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    volatile uint32 timeout_duration = 500U * 16U; /*Phase Lock time is 500 REFCLK cycles*/
    /* Wait for FSM to to come out of reset */
    while ((uint32)0x400U != (HW_RD_REG32(ptrPllStatus) & (uint32)0x400U))
    {
        /* Below API can change start time, so use temp variable */
        if (timeout_duration <= 0U)
        {
#ifdef MCU_E_CLOCK_FAILURE
            /* timeout */
            (void)Dem_SetEventStatus(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(timeout_duration);
        /*LDRA_INSPECTED 28 D : MISRAC_2012_R.2.1
         * "Reason - Infinite Loop has been taken care by
         * implementing timeout " */
    }
}

static void MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId outFreqId, const MCAL_SOC_RcmPllHsDivOutConfig *hsDivCfg)
{
    MCAL_SOC_RcmXtalFreqId          XTALFreq;
    uint16                          dspTrimVal;
    MCAL_SOC_RcmADPLLJConfig const *adplljCfg;
    uint32                          hsDivOutRegVal;
    uint32                          Fout;

    Fout = MCAL_SOC_RCM_FREQ_MHZ2HZ(Mcu_SocRcmPllFreqId2FOutMap[outFreqId]);
    /* read the Core ADPLL trim value */
    dspTrimVal = MCAL_SOC_rcmGetDspTrimVal();

    /* read the XTAL Frequency */
    XTALFreq = MCAL_SOC_rcmGetXtalFrequency();

    /* program PLL dividers and multipliers. The value are taken from TPR12_ADPLLJ_Settings_1p0.xlsx
     */
    adplljCfg = MCAL_SOC_rcmGetADPLLJConfig(Mcu_SocRcmXtalInfo[XTALFreq].Finp, outFreqId);
    /*DebugP_assert(adplljCfg != NULL);*/
    if (adplljCfg != NULL_PTR)
    {
        if (Mcu_SocRcmXtalInfo[XTALFreq].div2flag == (uint32)0)
        {
            MCAL_SOC_rcmProgPllDspDivider(adplljCfg->N, 0U /* N2 divider for bypass */, adplljCfg->M, adplljCfg->M2,
                                          adplljCfg->FracM);
        }
        else
        {
            uint32 N;

            /*DebugP_assert(((adplljCfg->N + 1) % 2) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if (((adplljCfg->N + (uint32)1) % (uint32)2) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
            else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            {
                /* Input XTAL freq is half. Divide input divider by 2 to get same output freq */
                N = ((adplljCfg->N + (uint32)1) / (uint32)2) - (uint32)1;
                MCAL_SOC_rcmProgPllDspDivider(N, 0U /* N2 divider for bypass */, adplljCfg->M, adplljCfg->M2,
                                              adplljCfg->FracM);
            }
        }
        /* Configure and Lock Core PLL */
        MCAL_SOC_rcmConfigurePllDsp(dspTrimVal);

        /* Derive Clocks */
        /* HSDIV-2 Settings*/
        /* Core PLL settings */
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[0]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[0]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[0];
            hsDivOutRegVal--;
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT0, 0x0); CLKOUT0_DIV[4:0] =
             * 4  -- 900M/(4+1) = 225MHz*/
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT0 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT0, 4U, 0U, hsDivOutRegVal);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[1]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[1]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[1];
            hsDivOutRegVal--;
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT1, 0x3); CLKOUT1_DIV[4:0] =
             * 1  -- 900M/(1+1) = 450MHz*/
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT1 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT1, 4U, 0U, hsDivOutRegVal);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[2]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[2]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[2];
            hsDivOutRegVal--;
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT2, 0x4); CLKOUT2_DIV[4:0] =
             * 8  -- 900M/(8+1) = 100MHz */
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT2 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT2, 4U, 0U, hsDivOutRegVal);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_3) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[3]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[3]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[3];
            hsDivOutRegVal--;
            /*UnsedHW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT3, 0x109);
             * +CLKOUT3_GATE[8]  = 1*/
            /*Unsed HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT3, 0x9);
             * CLKOUT3_DIV[4:0] = 9  -- 900M/(9+1) = 90MHz unused*/
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT3 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT3, 4U, 0U, hsDivOutRegVal);
        }

        /* Generate Trigger to latch these values */
        /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER , 0x4);     HSDIVIDER[2]     = 1*/
        toprcmREG->PLL_DSP_HSDIVIDER = MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER, 2U, 2U, 0x1U);
        /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER        , 0x0);     HSDIVIDER[2]     =
         * 0*/
        toprcmREG->PLL_DSP_HSDIVIDER = MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER, 2U, 2U, 0x0U);

        /* Ungate the clocks */
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0) != (uint32)0)
        {
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT0, 0x100);  +CLKOUT0_GATE[8]
             * = 1*/
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT0 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT0, 8U, 8U, 0x1U);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1) != (uint32)0)
        {
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT1, 0x103);  +CLKOUT1_GATE[8]
             * = 1*/
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT1 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT1, 8U, 8U, 0x1U);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2) != (uint32)0)
        {
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT2, 0x104);  +CLKOUT2_GATE[8]
             * = 1*/
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT2 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT2, 8U, 8U, 0x1U);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_3) != (uint32)0)
        {
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT2, 0x104);  +CLKOUT2_GATE[8]
             * = 1*/
            toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT3 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_DSP_HSDIVIDER_CLKOUT3, 8U, 8U, 0x1U);
        }
    }
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    else
    {
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
    }
#endif

    return;
}

static void MCAL_SOC_rcmPerPllConfig(MCAL_SOC_RcmPllFoutFreqId outFreqId, const MCAL_SOC_RcmPllHsDivOutConfig *hsDivCfg)
{
    MCAL_SOC_RcmXtalFreqId          XTALFreq;
    uint16                          perTrimVal;
    MCAL_SOC_RcmADPLLJConfig const *adplljCfg;
    uint32                          hsDivOutRegVal;
    uint32                          Fout;

    Fout = MCAL_SOC_RCM_FREQ_MHZ2HZ(Mcu_SocRcmPllFreqId2FOutMap[outFreqId]);
    /* read the Core ADPLL trim value */
    perTrimVal = MCAL_SOC_rcmGetPerTrimVal();

    /* Core PLL settings */
    /* read the XTAL Frequency */
    XTALFreq = MCAL_SOC_rcmGetXtalFrequency();

    /* program PLL dividers and multipliers. The value are taken from TPR12_ADPLLJ_Settings_1p0.xlsx
     */
    adplljCfg = MCAL_SOC_rcmGetADPLLJConfig(Mcu_SocRcmXtalInfo[XTALFreq].Finp, outFreqId);
    /*DebugP_assert(adplljCfg != NULL);*/

    if (adplljCfg != NULL_PTR)
    {
        if (Mcu_SocRcmXtalInfo[XTALFreq].div2flag == (uint32)0)
        {
            MCAL_SOC_rcmProgPllPerDivider(adplljCfg->N, 0U, adplljCfg->M, adplljCfg->M2, adplljCfg->FracM);
        }
        else
        {
            uint32 N;

            /*DebugP_assert(((adplljCfg->N + 1) % 2) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if (((adplljCfg->N + (uint32)1) % (uint32)2) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
            else
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            {
                /* Input XTAL freq is half. Divide input divider by 2 to get same output freq */
                N = ((adplljCfg->N + (uint32)1) / (uint32)2) - (uint32)1;

                MCAL_SOC_rcmProgPllPerDivider(N, 0U, adplljCfg->M, adplljCfg->M2, adplljCfg->FracM);
            }
        }
        /* Configure and Lock Core PLL */
        MCAL_SOC_rcmConfigurePllPer(perTrimVal);

        /* Derive Clocks */
        /* TPR12_Ch08_Clock_Arch_0p91 is used as reference for below settings */
        /* Set clock divider values from PER PLL*/
        /* 1728 Mhz */
        /* HSDIV-2 Settings*/
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[0]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[0]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[0];
            hsDivOutRegVal--;
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER_CLKOUT0, 0x0); CLKOUT0_DIV[4:0] =
             * 0  -- 1.728G/(0+1) = 1.728GHz*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT0 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT0, 4U, 0U, hsDivOutRegVal);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[1]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[1]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[1];
            hsDivOutRegVal--;
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER_CLKOUT1, 0x8); CLKOUT1_DIV[4:0] =
             * 8  -- 1.728G/(8+1) = 192 MHz*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT1 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT1, 4U, 0U, hsDivOutRegVal);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[2]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[2]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[2];
            hsDivOutRegVal--;
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER_CLKOUT2, 0x11); CLKOUT2_DIV[4:0] =
             * 11  -- 1.8G/(17+1) = 96 MHz*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT2 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT2, 4U, 0U, hsDivOutRegVal);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_3) != (uint32)0)
        {
            /*DebugP_assert((Fout % hsDivCfg->hsDivOutFreqHz[3]) == 0);*/
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            if ((Fout % hsDivCfg->hsDivOutFreqHz[3]) != (uint32)0)
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            hsDivOutRegVal = Fout / hsDivCfg->hsDivOutFreqHz[3];
            hsDivOutRegVal--;
            /*Unsed HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT3, 0x9);      unused*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT3 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT3, 4U, 0U, hsDivOutRegVal);
        }
        /* Generate Trigger to latch these values */
        /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER        , 0x4);     HSDIVIDER[2]     =
         * 1*/
        toprcmREG->PLL_PER_HSDIVIDER = MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER, 2U, 2U, 0x1U);
        /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER        , 0x0);     HSDIVIDER[2]     =
         * 0*/
        toprcmREG->PLL_PER_HSDIVIDER = MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER, 2U, 2U, 0x0U);

        /* Ungate the clocks */
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0) != (uint32)0)
        {
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER_CLKOUT0, 0x100);  +CLKOUT0_GATE[8]
             * = 1*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT0 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT0, 8U, 8U, 0x1U);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1) != (uint32)0)
        {
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER_CLKOUT1, 0x108);  +CLKOUT1_GATE[8]
             * = 1*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT1 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT1, 8U, 8U, 0x1U);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2) != (uint32)0)
        {
            /*HW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_PER_HSDIVIDER_CLKOUT2, 0x111);  +CLKOUT2_GATE[8]
             * = 1*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT2 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT2, 8U, 8U, 0x1U);
        }
        if ((hsDivCfg->hsdivOutEnMask & MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_3) != (uint32)0)
        {
            /*UnusedHW_WR_REG32(CSL_MSS_TOPRCM_U_BASE+PLL_DSP_HSDIVIDER_CLKOUT3, 0x109);
             * +CLKOUT3_GATE[8]  = 1*/
            toprcmREG->PLL_PER_HSDIVIDER_CLKOUT3 =
                MCAL_SOC_rcmInsert8(toprcmREG->PLL_PER_HSDIVIDER_CLKOUT3, 8U, 8U, 0x1U);
        }
    }
#if (STD_ON == MCU_DEV_ERROR_DETECT)
    else
    {
        (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_E_PLL_NOT_LOCKED);
    }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */

    return;
}

/**
 * \brief  Function to initialize all the PLL clocks
 */
Std_ReturnType Mcu_PLLInitAll(const Mcu_ConfigType *Mcu_PllDrvObj)
{
    Std_ReturnType                init_pll_return = E_OK;
    MCAL_SOC_RcmPllHsDivOutConfig hsDivCfg;

    /* Read the E-Fuse register to know the Device type for AM273x
    and based on the frequency supported on the part the PLL code is configured */
    uint32 eFuseRow11 = M_REG_READ32(MCAL_CSL_DSP_FREQ_EFUSE_INFO_REG);

    hsDivCfg.hsdivOutEnMask = MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1 | MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2;
    /* Configure CLKOUT1 to DSS PLL Fout/2. Divider is hsDivOut + 1 so set 1 */
    uint32 r5FreqEfuse         = (eFuseRow11 & MCAL_BOOTLOADER_SOC_R5_FREQ_MASK);
    hsDivCfg.hsDivOutFreqHz[1] = MCAL_SOC_RCM_FREQ_MHZ2HZ(200U);
    if (r5FreqEfuse == (uint32)MCAL_BOOTLOADER_SOC_R5_PART_400MHZ)
    {
        hsDivCfg.hsDivOutFreqHz[2] = MCAL_SOC_RCM_FREQ_MHZ2HZ(400U);
    }
    else
    {
        hsDivCfg.hsDivOutFreqHz[2] = MCAL_SOC_RCM_FREQ_MHZ2HZ(200U);
    }
    MCAL_SOC_rcmCoreApllHSDivConfig(&hsDivCfg);

    hsDivCfg.hsdivOutEnMask = MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1;
    /* Configure CLKOUT1 to DSS PLL Fout/2. Divider is hsDivOut + 1 so set 1 */
    /* Check the DSP frequency eFUSE register to find out frequency supported by the part */

    uint32 dspFreqEfuse = (eFuseRow11 & (MCAL_BOOTLOADER_SOC_DSP_PART_MASK));

    switch (dspFreqEfuse)
    {
        case MCAL_BOOTLOADER_SOC_DSP_PART_300MHZ:
            if (McuDSPDPLLClockout_HSDIV1 == MCAL_BOOTLOADER_SOC_CLK_FREQ_300MHZ)
            {
                hsDivCfg.hsDivOutFreqHz[1] = MCAL_BOOTLOADER_SOC_CLK_FREQ_300MHZ;
                MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ, &hsDivCfg);
            }
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            else
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_INCORRECT_DSP_FREQ_SEL);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            break;

        case MCAL_BOOTLOADER_SOC_DSP_PART_550MHZ:
            if (McuDSPDPLLClockout_HSDIV1 == MCAL_BOOTLOADER_SOC_CLK_FREQ_300MHZ)
            {
                hsDivCfg.hsDivOutFreqHz[1] = MCAL_BOOTLOADER_SOC_CLK_FREQ_300MHZ;
                MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ, &hsDivCfg);
            }
            else if (McuDSPDPLLClockout_HSDIV1 == MCAL_BOOTLOADER_SOC_CLK_FREQ_450MHZ)
            {
                hsDivCfg.hsDivOutFreqHz[1] = MCAL_BOOTLOADER_SOC_CLK_FREQ_450MHZ;
                MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ, &hsDivCfg);
            }
            else if (McuDSPDPLLClockout_HSDIV1 == MCAL_BOOTLOADER_SOC_CLK_FREQ_550MHZ)
            {
                hsDivCfg.hsDivOutFreqHz[1] = MCAL_BOOTLOADER_SOC_CLK_FREQ_550MHZ;
                MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_1650MHZ, &hsDivCfg);
            }
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            else
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_INCORRECT_DSP_FREQ_SEL);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            break;

        case MCAL_BOOTLOADER_SOC_DSP_PART_450MHZ:
            if (McuDSPDPLLClockout_HSDIV1 == MCAL_BOOTLOADER_SOC_CLK_FREQ_300MHZ)
            {
                hsDivCfg.hsDivOutFreqHz[1] = MCAL_BOOTLOADER_SOC_CLK_FREQ_300MHZ;
                MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ, &hsDivCfg);
            }
            else if (McuDSPDPLLClockout_HSDIV1 == MCAL_BOOTLOADER_SOC_CLK_FREQ_450MHZ)
            {
                hsDivCfg.hsDivOutFreqHz[1] = MCAL_BOOTLOADER_SOC_CLK_FREQ_450MHZ;
                MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ, &hsDivCfg);
            }
#if (STD_ON == MCU_DEV_ERROR_DETECT)
            else
            {
                (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SID_PLL_INIT_ALL, MCU_INCORRECT_DSP_FREQ_SEL);
            }
#endif /* STD_ON == MCU_DEV_ERROR_DETECT */
            break;

        default:
            hsDivCfg.hsDivOutFreqHz[1] = MCAL_BOOTLOADER_SOC_CLK_FREQ_450MHZ;
            MCAL_SOC_rcmDspPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ, &hsDivCfg);
            break;
    }

    hsDivCfg.hsdivOutEnMask = (MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1 | MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2 |
                               MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_3);
    /* Configure CLKOUT1 to DSS PLL Fout/2. Divider is hsDivOut + 1 so set 1 */
    hsDivCfg.hsDivOutFreqHz[1] = MCAL_SOC_RCM_FREQ_MHZ2HZ(192U);
    hsDivCfg.hsDivOutFreqHz[2] = MCAL_SOC_RCM_FREQ_MHZ2HZ(96U);
    hsDivCfg.hsDivOutFreqHz[3] = MCAL_SOC_RCM_FREQ_MHZ2HZ_FL(172.8);
    MCAL_SOC_rcmPerPllConfig(MCAL_SOC_RcmPllFoutFreqId_CLK_1728MHZ, &hsDivCfg);

    return init_pll_return;
}
#endif /* STD_OFF == MCU_NO_PLL */

#if (STD_ON == MCU_REGISTER_READBACK_API)
void Mcu_HWRegisterReadback(Mcu_RegisterReadbackType *RegisterReadbackPtr)
{
    RegisterReadbackPtr->CLKSRCSEL0 = (uint32)(mssrcmREG->MSS_RTIA_CLK_SRC_SEL);
}
#endif /* STD_ON == MCU_REGISTER_READBACK_API */

static void Mcu_controlModuleLockMMR(uint32 domainId)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    if (MCU_DOMAIN_ID_MSS_TOP_RCM == domainId)
    {
        baseAddr = MCU_CSL_MSS_TOPRCM_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_TOPRCM_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_KICK_LOCK_VAL);
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_TOPRCM_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_KICK_LOCK_VAL);
    }

    return;
}

static void Mcu_controlModuleUnlockMMR(uint32 domainId)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    if (MCU_DOMAIN_ID_MSS_TOP_RCM == domainId)
    {
        baseAddr = MCU_CSL_MSS_TOPRCM_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_TOPRCM_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, MCU_KICK0_UNLOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + MCU_CSL_MSS_TOPRCM_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, MCU_KICK1_UNLOCK_VAL); /* KICK 1 */
    }

    return;
}

static uint8 MCAL_SOC_rcmExtract8(volatile uint32 reg, uint8 msb, uint8 lsb)
{
    uint32 mask;
    uint8  bits;
    uint8  value;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32)((uint32)1U << bits);
    mask = mask - 1U;

    value = (uint8)((reg >> lsb) & mask);
    return value;
}
static void Mcu_Timeoutevent(volatile const uint32 *addr, uint32 Value, uint32 timeout)
{
    volatile uint32 tempCount = timeout;
    if (timeout > 9U)
    {
        tempCount = timeout / 9U;
    }
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    while (M_REG_READ32(addr) != Value)
    {
        /* Below API can change start time, so use temp variable */
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
void Mcu_DisableEpwmTbClk(void)
{
    /* This function is provided as dummy for AM273x since PWM dependencies are not applicable */
}

/*LDRA_INSPECTED 580 S : MISRAC_2012_R.20.4
 * "Reason - macro is undefined in other file,but LDRA is not able to analyse
 *this " */
#define MCU_STOP_SEC_CODE
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
#include "Mcu_MemMap.h"
