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
 *  \file     Mcu_Priv.h
 *
 */

#ifndef MCU_PRIV_H_
#define MCU_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/

#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#include "sys_common.h"

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#include "Mcu.h"
#include "hw_types.h"
#include "Mcal_Libs_Utils.h"
#include "hw_ctrl_core.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MCU_SOFT_SYSRST 0x00

#define MCAL_SOC_RcmXtalClkFreq_Size    (8U)
#define MCAL_SOC_RcmPllFoutClkFreq_Size (11U)

/*Single port memory*/
#define RL_SP_ST_M_MBOX (uint64)((uint64)1U << 21U)
#define RL_SP_ST_M_MCAN (uint64)((uint64)1U << 39U)

/*Two port memory*/
#define RL_TP_ST_M_SPIB (uint64)((uint64)1U << 43U)
#define RL_TP_ST_M_DMA  (uint64)((uint64)1U << 27U)
#define RL_TP_ST_M_SPIA (uint64)((uint64)1U << 28U)
#define RL_TP_ST_M_VIM  (uint64)((uint64)1U << 29U)

#define MCAL_BOOTLOADER_SOC_DSP_PART_MASK   (0x70U)
#define MCAL_BOOTLOADER_SOC_DSP_PART_450MHZ (0x00)
#define MCAL_BOOTLOADER_SOC_DSP_PART_480MHZ (0x10)
#define MCAL_BOOTLOADER_SOC_DSP_PART_500MHZ (0x20)
#define MCAL_BOOTLOADER_SOC_DSP_PART_550MHZ (0x30)
#define MCAL_BOOTLOADER_SOC_DSP_PART_600MHZ (0x40)
#define MCAL_BOOTLOADER_SOC_DSP_PART_DITHER (0x50)
#define MCAL_BOOTLOADER_SOC_DSP_PART_300MHZ (0x60)

#define MCAL_BOOTLOADER_SOC_R5_FREQ_MASK   ((uint32)1U << (uint32)21U)
#define MCAL_BOOTLOADER_SOC_R5_PART_400MHZ (0x00000000)
#define MCAL_BOOTLOADER_SOC_R5_PART_200MHZ (uint32)(1U << 21U)

#define MCAL_BOOTLOADER_SOC_EFUSE_DUAL_CORE_DIS_MASK (uint32)(1U << 14U)
#define MCAL_BOOTLOADER_SOC_VARIANT_DUAL_R5F         (0x00000000)
#define MCAL_BOOTLOADER_SOC_VARIANT_SINGLE_R5F       (uint32)(1U << 14U)

/** @brief HSDIV output enable bitmask, used with SOC_RcmPllHsDivOutConfig */
#define MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0 (1U << 0U)
/** @brief HSDIV output enable bitmask, used with SOC_RcmPllHsDivOutConfig */
#define MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1 (1U << 1U)
/** @brief HSDIV output enable bitmask, used with SOC_RcmPllHsDivOutConfig */
#define MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2 (1U << 2U)
/** @brief HSDIV output enable bitmask, used with SOC_RcmPllHsDivOutConfig */
#define MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_3 (1U << 3U)
/** @brief HSDIV output enable bitmask, used with SOC_RcmPllHsDivOutConfig */
#define MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_ALL                                       \
    (MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_0 | MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_1 | \
     MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_2 | MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_ENABLE_3)

/* @brief HSDIV output enable bitmask, used with SOC_RcmPllHsDivOutConfig */
#define MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_COUNT (4U)

#define MCAL_SOC_RCM_CORE_ADPLL_DEFAULT_VALUE       (0x9U)
#define MCAL_SOC_RCM_DSP_ADPLL_DEFAULT_VALUE        (0x9U)
#define MCAL_SOC_RCM_PER_ADPLL_DEFAULT_VALUE        (0x9U)
#define MCAL_SOC_RCM_PLL_SYS_CLK_FREQUENCY_HZ       (200000000U)
#define MCAL_SOC_RCM_PLL_HSDIV_CLKOUT2_FREQUENCY_HZ (400000000U)
#define MCAL_SOC_RCM_XTAL_CLK_40MHZ                 (40000000U)
#define MCAL_SOC_RCM_XTAL_CLK_50MHZ                 (50000000U)
#define MCAL_SOC_RCM_XTAL_CLK_49p152MHZ             (49152000U)
#define MCAL_SOC_RCM_XTAL_CLK_45p1584MHZ            (45158400U)
#define MCAL_SOC_RCM_XTAL_CLK_20MHZ                 (20000000U)
#define MCAL_SOC_RCM_XTAL_CLK_25MHZ                 (25000000U)
#define MCAL_SOC_RCM_XTAL_CLK_24p576MHZ             (24576000U)
#define MCAL_SOC_RCM_XTAL_CLK_22p5792MHZ            (22579200U)

#define MCAL_BOOTLOADER_SOC_CLK_FREQ_400MHZ (uint32)(400 * 1000000)
#define MCAL_BOOTLOADER_SOC_CLK_FREQ_200MHZ (uint32)(200 * 1000000)
#define MCAL_BOOTLOADER_SOC_CLK_FREQ_450MHZ (uint32)(450 * 1000000)
#define MCAL_BOOTLOADER_SOC_CLK_FREQ_550MHZ (uint32)(550 * 1000000)
#define MCAL_BOOTLOADER_SOC_CLK_FREQ_300MHZ (uint32)(300 * 1000000)
#define MCAL_BOOTLOADER_SOC_CLK_FREQ_600MHZ (uint32)(600 * 1000000)

#define MCAL_SOC_RCM_FREQ_HZ2MHZ(hz)     ((hz) / (1000000U))
#define MCAL_SOC_RCM_FREQ_MHZ2HZ(mhz)    ((mhz) * (1000000U))
#define MCAL_SOC_RCM_FREQ_MHZ2HZ_FL(mhz) (float32)((mhz) * (float32)(1000000U))
#define MCAL_SOC_RCM_UTILS_ARRAYSIZE(x)  (sizeof(x) / sizeof(x[0]))
#define MCAL_SOC_RCM_FREQ_1GHZ           (1000 * 1000 * 1000)
#define MCAL_SOC_RCM_FREQ_550MHZ         (uint32)(550 * 1000 * 1000)

#define MCAL_SOC_RCM_XTAL_FREQ_SCALE_START_BIT          (25U)
#define MCAL_SOC_RCM_XTAL_FREQ_SCALE_END_BIT            (25U)
#define MCAL_SOC_RCM_COREADPLLTRIMCONFIG_START_BIT      (0U)
#define MCAL_SOC_RCM_COREADPLLTRIMCONFIG_END_BIT        (11U)
#define MCAL_SOC_RCM_DSPADPLLTRIMCONFIG_START_BIT       (12U)
#define MCAL_SOC_RCM_DSPADPLLTRIMCONFIG_END_BIT         (23U)
#define MCAL_SOC_RCM_PERADPLLTRIMCONFIG_START_BIT       (0U)
#define MCAL_SOC_RCM_PERADPLLTRIMCONFIG_END_BIT         (11U)
#define MCAL_SOC_RCM_COREADPLLTRIMVALIDCONFIG_START_BIT (12U)
#define MCAL_SOC_RCM_COREADPLLTRIMVALIDCONFIG_END_BIT   (12U)
#define MCAL_SOC_RCM_DSPADPLLTRIMVALIDCONFIG_START_BIT  (13U)
#define MCAL_SOC_RCM_DSPADPLLTRIMVALIDCONFIG_END_BIT    (13U)
#define MCAL_SOC_RCM_PERADPLLTRIMVALIDCONFIG_START_BIT  (14U)
#define MCAL_SOC_RCM_PERADPLLTRIMVALIDCONFIG_END_BIT    (14U)

/* PLL_DSP_TENABLE */

#define MSS_TOPRCM_PLL_DSP_TENABLE_PLL_DSP_TENABLE_TENABLE_MASK     (0x00000001U)
#define MSS_TOPRCM_PLL_DSP_TENABLE_PLL_DSP_TENABLE_TENABLE_SHIFT    (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_TENABLE_PLL_DSP_TENABLE_TENABLE_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_TENABLE_PLL_DSP_TENABLE_TENABLE_MAX      (0x00000001U)

#define MSS_TOPRCM_PLL_DSP_TENABLE_RESETVAL (0x00000000U)

/* PLL_DSP_TENABLEDIV */

#define MSS_TOPRCM_PLL_DSP_TENABLEDIV_PLL_DSP_TENABLEDIV_TENABLEDIV_MASK     (0x00000001U)
#define MSS_TOPRCM_PLL_DSP_TENABLEDIV_PLL_DSP_TENABLEDIV_TENABLEDIV_SHIFT    (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_TENABLEDIV_PLL_DSP_TENABLEDIV_TENABLEDIV_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_TENABLEDIV_PLL_DSP_TENABLEDIV_TENABLEDIV_MAX      (0x00000001U)

#define MSS_TOPRCM_PLL_DSP_TENABLEDIV_RESETVAL (0x00000000U)

/* PLL_CORE_M2NDIV */

#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_N_MASK     (0x000000FFU)
#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_N_SHIFT    (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_N_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_N_MAX      (0x000000FFU)

#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_M2_MASK     (0x007F0000U)
#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_M2_SHIFT    (0x00000010U)
#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_M2_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_M2_MAX      (0x0000007FU)

#define MSS_TOPRCM_PLL_CORE_M2NDIV_RESETVAL (0x00000000U)

/* PLL_CORE_MN2DIV */

#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_M_MASK     (0x00000FFFU)
#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_M_SHIFT    (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_M_RESETVAL (0x00000174U)
#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_M_MAX      (0x00000FFFU)

#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_N2_MASK     (0x000F0000U)
#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_N2_SHIFT    (0x00000010U)
#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_N2_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_N2_MAX      (0x0000000FU)

#define MSS_TOPRCM_PLL_CORE_MN2DIV_RESETVAL (0x00000174U)

/* PLL_CORE_FRACDIV */

#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_FRACTIONALM_MASK     (0x0003FFFFU)
#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_FRACTIONALM_SHIFT    (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_FRACTIONALM_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_FRACTIONALM_MAX      (0x0003FFFFU)

#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_REGSD_MASK     (0xFF000000U)
#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_REGSD_SHIFT    (0x00000018U)
#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_REGSD_RESETVAL (0x00000008U)
#define MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_REGSD_MAX      (0x000000FFU)

#define MSS_TOPRCM_PLL_CORE_FRACDIV_RESETVAL (0x08000000U)

/* PLL_DSP_M2NDIV */

#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_N_MASK     (0x000000FFU)
#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_N_SHIFT    (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_N_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_N_MAX      (0x000000FFU)

#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_M2_MASK     (0x007F0000U)
#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_M2_SHIFT    (0x00000010U)
#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_M2_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_M2NDIV_PLL_DSP_M2NDIV_M2_MAX      (0x0000007FU)

#define MSS_TOPRCM_PLL_DSP_M2NDIV_RESETVAL (0x00000000U)

/* PLL_DSP_MN2DIV */

#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_M_MASK     (0x00000FFFU)
#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_M_SHIFT    (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_M_RESETVAL (0x00000174U)
#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_M_MAX      (0x00000FFFU)

#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_N2_MASK     (0x000F0000U)
#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_N2_SHIFT    (0x00000010U)
#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_N2_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_MN2DIV_PLL_DSP_MN2DIV_N2_MAX      (0x0000000FU)

#define MSS_TOPRCM_PLL_DSP_MN2DIV_RESETVAL (0x00000174U)

#define MSS_TOPRCM_PLL_DSP_CLKCTRL_PLL_DSP_CLKCTRL_ULOWCLKEN_MASK     (0x00040000U)
#define MSS_TOPRCM_PLL_DSP_CLKCTRL_PLL_DSP_CLKCTRL_ULOWCLKEN_SHIFT    (0x00000012U)
#define MSS_TOPRCM_PLL_DSP_CLKCTRL_PLL_DSP_CLKCTRL_ULOWCLKEN_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_DSP_CLKCTRL_PLL_DSP_CLKCTRL_ULOWCLKEN_MAX      (0x00000001U)

#define MSS_TOPRCM_PLL_CORE_CLKCTRL_PLL_CORE_CLKCTRL_ULOWCLKEN_MASK     (0x00040000U)
#define MSS_TOPRCM_PLL_CORE_CLKCTRL_PLL_CORE_CLKCTRL_ULOWCLKEN_SHIFT    (0x00000012U)
#define MSS_TOPRCM_PLL_CORE_CLKCTRL_PLL_CORE_CLKCTRL_ULOWCLKEN_RESETVAL (0x00000000U)
#define MSS_TOPRCM_PLL_CORE_CLKCTRL_PLL_CORE_CLKCTRL_ULOWCLKEN_MAX      (0x00000001U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef struct MCAL_SOC_RcmXtalInfo_s
{
    uint32 Finp;
    uint32 div2flag;
} MCAL_SOC_RcmXtalInfo;

typedef struct MCAL_SOC_RcmADPLLJConfig_s
{
    uint32 N;     /* Input Clock divider/Pre-divider (N) */
    uint32 M2;    /* Post divider (M2) */
    uint32 M;     /* Multiplier integer (M) */
    uint32 FracM; /* Multiplier fractional (M) */
    uint32 Fout;  /* Output frequency of PLL */
    uint32 Finp;  /* Output frequency of PLL */
} MCAL_SOC_RcmADPLLJConfig;

typedef enum MCAL_SOC_RcmXtalFreqId_e
{
    MCAL_SOC_RcmXtalFreqId_CLK_40MHZ,
    MCAL_SOC_RcmXtalFreqId_CLK_50MHZ,
    MCAL_SOC_RcmXtalFreqId_CLK_49p152MHZ,
    MCAL_SOC_RcmXtalFreqId_CLK_45p1584MHZ,
    MCAL_SOC_RcmXtalFreqId_CLK_20MHZ,
    MCAL_SOC_RcmXtalFreqId_CLK_25MHZ,
    MCAL_SOC_RcmXtalFreqId_CLK_24p576MHZ,
    MCAL_SOC_RcmXtalFreqId_CLK_22p5792MHZ
} MCAL_SOC_RcmXtalFreqId;

/**
 * @brief PLL Fout values
 */
typedef enum MCAL_SOC_RcmPllFoutFreqId_e
{
    /**
     * @brief   Value specifying PLL Fout of 1100 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1100MHZ,
    /**
     * @brief   Value specifying PLL Fout of 1650 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1650MHZ,
    /**
     * @brief   Value specifying PLL Fout of 800 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_800MHZ,
    /**
     * @brief   Value specifying PLL Fout of 900 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_900MHZ,
    /**
     * @brief   Value specifying PLL Fout of 2000 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_2000MHZ,
    /**
     * @brief   Value specifying PLL Fout of 1800 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1800MHZ,
    /**
     * @brief   Value specifying PLL Fout of 1920 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1920MHZ,
    /**
     * @brief   Value specifying PLL Fout of 1699.21875 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1699p21875MHZ,
    /**
     * @brief   Value specifying PLL Fout of 1728 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1728MHZ,
    /**
     * @brief   Value specifying PLL Fout of 1966.08 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1966p08MHZ,
    /**
     * @brief   Value specifying PLL Fout of 1806.336 Mhz
     */
    MCAL_SOC_RcmPllFoutFreqId_CLK_1806p336MHZ,
    /**
     * @brief max value
     */
    MCAL_SOC_RcmPllFoutFreqId_MAX_VALUE = 0xFFFFFFFFu,

} MCAL_SOC_RcmPllFoutFreqId;

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

/* Enum to store the DSP Core C66x frequencies to compare during MCU PLL Init All Function */
typedef enum
{
    MCU_PLL_DSP_FREQ_300MHz = 300000000,
    MCU_PLL_DSP_FREQ_450MHz = 450000000,
    MCU_PLL_DSP_FREQ_550MHz = 550000000
} Mcu_Dsp_FreqInfo;

/* Enum to map the Efuse value to meaningful frequency values */
typedef enum
{
    MCU_PLL_EFUSE_VAL_FOR_300MHz = 0x40,
    MCU_PLL_EFUSE_VAL_FOR_450MHz = 0x00,
    MCU_PLL_EFUSE_VAL_FOR_550MHz = 0x30
} Mcu_Dsp_EfuseToFreqMap;

/**
 * @brief Structure to specific PLL HS divider output frequencies
 */
typedef struct MCAL_SOC_RcmPllHsDivOutConfig_s
{
    uint32 hsdivOutEnMask;                                      /**< HS divider output enable bit mark */
    uint32 hsDivOutFreqHz[MCAL_SOC_RCM_PLL_HSDIV_OUTPUT_COUNT]; /**< HS divider output frequencies */
} MCAL_SOC_RcmPllHsDivOutConfig;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if (STD_OFF == MCU_NO_PLL)
Mcu_PllStatusType Mcu_GetPllLockStatus(void);
Std_ReturnType    Mcu_PLLInitAll(const Mcu_ConfigType *gMcuDriverObject);
#endif
#if (STD_ON == MCU_PERFORM_RESET_API)
void Mcu_PerformSoftSysReset(uint32 resetVal);
#endif
Mcu_ResetType    Mcu_GetPlatformResetReason(void);
Mcu_RawResetType Mcu_GetPlatformRawResetReason(void);
FUNC(void, MCU_CODE) Mcu_SetupClock(void);
FUNC(Std_ReturnType, MCU_CODE)
Mcu_ClockSetSource(Mcu_ClkModuleIdType moduleId, Mcu_ClkSourceIdType clkSrcId, uint32 clkDivId, boolean enable);
uint32         Mcu_getMultibitValue(uint32 clk_srcId);
Std_ReturnType Mcu_ClockSetSourceCR5(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceMCANA(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceMCANB(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceRTIA(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceRTIB(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceRTIC(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceWDT(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceQSPI(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceSPIA(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceSPIB(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceI2C(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceSCIA(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceSCIB(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceCPSW(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceCPTS(Mcu_ClkSourceIdType clk_srcId, uint32 clkDivId);
Std_ReturnType Mcu_ClockSetSourceHSIClk(Mcu_ClkSourceIdType clk_srcId);
Std_ReturnType Mcu_ClockSetSourceCSIRXClk(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceMcuClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourcePmicClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceObsClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceTRCClkout(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceMII100Clk(uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceMII10Clk(uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceRGMIClk(uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceGpadcClk(uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceRCSSSPIA(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_ClockSetSourceRCSSSPIB(Mcu_ClkSourceIdType clk_srcId, uint32 clk_divId);
Std_ReturnType Mcu_SetUpDCDC_Contrl(void);
FUNC(void, MCU_CODE) Mcu_SystemInit(void);

#if (STD_ON == MCU_REGISTER_READBACK_API)
void Mcu_HWRegisterReadback(Mcu_RegisterReadbackType *RegisterReadbackPtr);
#endif /* MCU_REGISTER_READBACK_API */

void Mcu_DisableEpwmTbClk(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef MCU_PRIV_H_ */
