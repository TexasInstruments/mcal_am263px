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
 *  \file     WdgApp.c
 *
 *  \brief    This file contains the SPI test example for WdgApp
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "WdgApp.h"
#include "WdgApp_Startup.h"
#include "WdgIf_Types.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x)         (sizeof((x)) / sizeof(x[0]))
#define TIME_METRICS_ENABLED STD_OFF
#define MSS_RCM_PARTITION0   (4)
#define SOC_DOMAIN_ID_MAIN   (0)
#define WDG_CTL_DISABLED     (0x5312ACED)
#define GPT_TIMER            STD_ON
#define GPT_RTI_CHANNEL1     (0U)
#define GPT_COUNTVAL         (0X1E8480) /* 20 ms =2*10^6*/
#define WDT_MAX_SERVICE      (0X1770)   /* in ms */
#define DELAY_COUNT          (100)
#define SWITCH_DELAY         (250) /* 250 *20ms = 5 sec delay*/

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
void          WDT_Isr();
Mcu_ResetType GetResetReason();
void          SOC_controlModuleUnlockMMR(uint32 domainId, uint32 partition);
void          SOC_controlModuleLockMMR(uint32 domainId, uint32 partition);
void          Gpt_Channel_Notify5(void);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32              triggerValue;
uint32              triggerValueMode;
uint32              gTestPassed;
uint32              count        = 0;
bool                WDT_Reset    = false;
volatile uint32     gptcount     = 0;
volatile uint32     gptcountMode = 0;
bool                Timer_Done   = false;
Wdg_App_TestParams *testPrms     = NULL_PTR;

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration;
#endif

extern CONST(Gpt_ConfigType, GPT_PBCFG) Gpt_ChannelConfigSet_0;

#define WDGAPP_RTI_SYSCLK1_CLKSRCID (0)
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    gTestPassed = E_OK;
    Wdg_Startup();
    Check_McuReset();
    AppUtils_printf("WDG Test Completed !!!\r\n");
    GT_1trace(McalAppTrace, GT_INFO, "WDG Stack Usage: %d bytes\r\n", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(McalAppTrace, GT_ERR, "WDG Stack/section corruption!!!\r\n");
    }
    TimerDeinit();
    return (0);
}

void Check_McuReset()
{
    Wdg_App_TestParams *testPrms;
    Mcu_ResetType       mcu_reset_reason = MCU_RESET_UNDEFINED;
    mcu_reset_reason                     = GetResetReason();
    AppUtils_delay(4U);
    AppUtils_printf("Reset Reason %d \n\r", mcu_reset_reason);
    if (mcu_reset_reason != WDGAPP_MCU_WARM_RESET)
    {
        AppUtils_printf("LoopCount %d \n\r", WDGAPP_MCU_WARM_RESET);
        /* Application has not executed */
        *(uint32 *)WDGAPP_RAM_SECTION = 0x00000000;
        AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\r\n");
        testPrms = &Wdg_AppTestPrms[0];
        WDTApp_interruptConfig();
        Wdg_App_wdgTest(testPrms);
    }
    else
    {
        AppUtils_printf("Test Passed!! \n\r");
    }
}
#if (STD_ON == TIME_METRICS_ENABLED)
uint32 gServiceInterval = 0;
#endif

void Wdg_App_wdgTest(const Wdg_App_TestParams *testPrms)
{
    uint32         maxServiceInterval;
    uint32         preloadVal;
    uint32         Gpt_Count     = 0;
    uint32         Gpt_CountMode = 0;
    Wdg_WindowSize windowSize;
    uint32         RTI_Clock = 0;
    uint32         preload   = 0;

    uint32          preloadValMode;
    Wdg_WindowSize  windowSizeMode;
    uint32          maxServiceIntervalMode;
    Gpt_ChannelType ChannelId     = GPT_RTI_CHANNEL5;
    Gpt_ChannelType ChannelIdMode = GPT_RTI_CHANNEL6;
#if (STD_ON == TIME_METRICS_ENABLED)
    uint32 startTime;
    uint32 triggerTime;
#endif

#if (WDG_GET_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
    /* Get and print version */
    Wdg_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \r\n");
    AppUtils_printf("WDG MCAL Version Info\r\n");
    AppUtils_printf("---------------------\r\n");
    AppUtils_printf("Vendor ID           : %d\r\n", versioninfo.vendorID);
    AppUtils_printf("Module ID           : %d\r\n", versioninfo.moduleID);
    AppUtils_printf("SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    AppUtils_printf("SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    AppUtils_printf("SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    AppUtils_printf(" \r\n");
#endif /* #if (WDG_CFG_VERSION_INFO_API == STD_ON) */

    AppUtils_printf("Starting WDG test  !!!\r\n");

    AppUtils_printf("Service Count %d\r\n", testPrms->numServiceCount);

    AppUtils_printf("Service Interval %d milliseconds\r\n", testPrms->serviceInterval);

    triggerValue = ((testPrms->numServiceCount) * (testPrms->serviceInterval));
    AppUtils_printf("Trigger Value = %d milliseconds\r\n", triggerValue);
    triggerValueMode = ((testPrms->numServiceCount) * (testPrms->serviceIntervalMode));

    /* check if the service interval is valid or not */

    if (testPrms->wdgConfig->defaultMode == WDGIF_FAST_MODE)
    {
        preloadVal = testPrms->wdgConfig->fastModeCfg.preloadValue;
        windowSize = testPrms->wdgConfig->fastModeCfg.windowSize;
    }
    else
    {
        preloadVal = testPrms->wdgConfig->slowModeCfg.preloadValue;
        windowSize = testPrms->wdgConfig->slowModeCfg.windowSize;
    }

    if (testPrms->setMode == WDGIF_FAST_MODE)
    {
        preloadValMode = testPrms->wdgConfig->fastModeCfg.preloadValue;
        windowSizeMode = testPrms->wdgConfig->fastModeCfg.windowSize;
    }
    else
    {
        preloadValMode = testPrms->wdgConfig->slowModeCfg.preloadValue;
        windowSizeMode = testPrms->wdgConfig->slowModeCfg.windowSize;
    }

    /* The expiration time of the DWD Down Counter can be determined with following equation:*/
    /* texp= ((RTI_DWDPRLD + 1) x (2^13) )/ RTI_FCLK */
    /* calculate the maximum service interval */
    /* texp in seconds */
    maxServiceInterval = (preloadVal + 1) * 8192;
    maxServiceInterval = maxServiceInterval / (WDG_RTI_FREQUENCY * 1000);

    maxServiceIntervalMode = (preloadValMode + 1) * 8192;
    maxServiceIntervalMode = maxServiceIntervalMode / (WDG_RTI_FREQUENCY * 1000);
    switch (windowSize)
    {
        case WDG_WINDOW_SIZE_100_PERCENT:
            maxServiceInterval = maxServiceInterval / 1;
            break;
        case WDG_WINDOW_SIZE_50_PERCENT:
            maxServiceInterval = maxServiceInterval / 2;
            break;
        case WDG_WINDOW_SIZE_25_PERCENT:
            maxServiceInterval = maxServiceInterval / 4;
            break;
        case WDG_WINDOW_SIZE_12_5_PERCENT:
            maxServiceInterval = maxServiceInterval / 8;
            break;
        case WDG_WINDOW_SIZE_6_25_PERCENT:
            maxServiceInterval = maxServiceInterval / 16;
            break;
        default:
            maxServiceInterval = maxServiceInterval / 32;
            break;
    }
    AppUtils_printf("Maximum Service Interval %d milliseconds\r\n", maxServiceInterval);

    if (testPrms->serviceInterval >= maxServiceInterval)
    {
        AppUtils_printf("service interval should not be greater than maximum interval\n\r");
        AppUtils_printf("Test Failed!!\n\r");
        return;
    }
    else if (triggerValue < maxServiceInterval)
    {
        AppUtils_printf("triggerValue should not be less than maximum interval\n\r");
        AppUtils_printf("Test Failed!!\n\r");
        return;
    }
    switch (windowSizeMode)
    {
        case WDG_WINDOW_SIZE_100_PERCENT:
            maxServiceIntervalMode = maxServiceInterval / 1;
            break;
        case WDG_WINDOW_SIZE_50_PERCENT:
            maxServiceIntervalMode = maxServiceInterval / 2;
            break;
        case WDG_WINDOW_SIZE_25_PERCENT:
            maxServiceIntervalMode = maxServiceInterval / 4;
            break;
        case WDG_WINDOW_SIZE_12_5_PERCENT:
            maxServiceIntervalMode = maxServiceInterval / 8;
            break;
        case WDG_WINDOW_SIZE_6_25_PERCENT:
            maxServiceIntervalMode = maxServiceInterval / 16;
            break;
        default:
            maxServiceIntervalMode = maxServiceInterval / 32;
            break;
    }
    AppUtils_printf("Initializing channels\n\r");
    RTI_Clock     = Gpt_ChannelConfigSet_0.ChannelConfig_pt[0].GptChannelClksrcRef;
    preload       = Gpt_ChannelConfigSet_0.ChannelConfig_pt[0].GptChannelTickFrequency;
    Gpt_Count     = (RTI_Clock * 1000 * testPrms->serviceInterval) / (preload + 1);
    Gpt_CountMode = (RTI_Clock * 1000 * testPrms->serviceIntervalMode) / (preload + 1);
    Gpt_Init(&Gpt_ChannelConfigSet_0);
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
    Gpt_EnableNotification(ChannelId);
    Gpt_EnableNotification(ChannelIdMode);
#endif

#if (STD_ON == WDG_VARIANT_PRE_COMPILE)
    AppUtils_printf("Precompile variant is being used .. \n\r");
    Wdg_Init((const Wdg_ConfigType *)NULL_PTR);
#elif (STD_ON == WDG_VARIANT_POST_BUILD)
    AppUtils_printf("Post-Build variant is being used .. \n\r");
    Wdg_Init(testPrms->wdgConfig);
#else
    AppUtils_printf("Link-Time variant is being used .. \n\r");
    Wdg_Init(testPrms->wdgConfig);
#endif

    if (gTestPassed == E_NOT_OK)
    {
        AppUtils_printf("Error in WatchDog Initialization\n\r");
        AppUtils_printf("Test Failed!!\n\r");
        return;
    }

    Gpt_StartTimer(ChannelId, Gpt_Count + 100);
    Wdg_SetTriggerCondition(triggerValue - maxServiceInterval);
    while (1)
    {
        if (gptcount >= SWITCH_DELAY)
        {
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
            Gpt_DisableNotification(ChannelId);
#endif
            Gpt_StopTimer(ChannelId);
            gptcount = 0;
            Wdg_SetMode(testPrms->setMode);
            AppUtils_printf("Wdg SetMode to  %x !! \n\r", testPrms->setMode);
            AppUtils_printf("Service Interval changed to %d milliseconds\r\n", testPrms->serviceIntervalMode);
            Gpt_StartTimer(ChannelIdMode, Gpt_CountMode + 100);
            Wdg_SetTriggerCondition(triggerValueMode - maxServiceIntervalMode);
        }
        if (gptcountMode >= DELAY_COUNT)
        {
            AppUtils_printf("Wdg SetMode Test Passed!! \n\r");
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
            Gpt_DisableNotification(ChannelIdMode);
#endif
            Gpt_StopTimer(ChannelIdMode);
            gptcountMode = 0;
/* Deinit current configuration */
#if (STD_ON == GPT_DEINIT_API)
            Gpt_DeInit();
#endif
        }
    }
}

uint8 Intc_status;

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_0(void)
{
    __asm(" CPSID I");
}

void SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_0(void)
{
    __asm(" CPSIE I");
}

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    __asm(" CPSID I");
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    __asm(" CPSIE I");
}

void SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SOC_controlModuleUnlockMMR(uint32 domainId, uint32 partition)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;

    if (partition == CONTROLSS_CTRL_PARTITION0)
    {
        /*Unlock CONTROLSS_CTRL*/
        baseAddr = (uint32)CSL_CONTROLSS_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, TEST_KICK0_UNLOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, TEST_KICK1_UNLOCK_VAL); /* KICK 1 */
    }

    return;
}

void SOC_controlModuleLockMMR(uint32 domainId, uint32 partition)
{
    uint32           baseAddr;
    volatile uint32 *kickAddr;
    if (partition == TOP_CTRL_PARTITION0)
    {
        /*Lock TOP_CTRL*/
        baseAddr = (uint32)CSL_TOP_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + CSL_TOP_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, TEST_KICK_LOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + CSL_TOP_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, TEST_KICK_LOCK_VAL); /* KICK 1 */
    }

    if (partition == CONTROLSS_CTRL_PARTITION0)
    {
        /*Lock CONTROLSS_CTRL*/
        baseAddr = (uint32)CSL_CONTROLSS_CTRL_U_BASE;
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK0);
        HW_WR_REG32(kickAddr, TEST_KICK_LOCK_VAL); /* KICK 0 */
        kickAddr = (volatile uint32 *)(baseAddr + CSL_CONTROLSS_CTRL_LOCK0_KICK1);
        HW_WR_REG32(kickAddr, TEST_KICK_LOCK_VAL); /* KICK 1 */
    }

    return;
}

void Gpt_Channel_Notify5(void)
{
    gptcount++;

    Wdg_SetTriggerCondition(triggerValue);

    AppUtils_printf(".\r");
}

void Gpt_Channel_Notify6(void)
{
    gptcountMode++;

    Wdg_SetTriggerCondition(triggerValueMode);

    AppUtils_printf(".\r");
}

void Gpt_Channel_Notify7(void)
{
}
void Gpt_Channel_Notify8(void)
{
}
void Gpt_Channel_Notify9(void)
{
}
void Gpt_Channel_Notify10(void)
{
}
void Gpt_Channel_Notify11(void)
{
}
void Gpt_Channel_Notify12(void)
{
}
void Gpt_Channel_Notify13(void)
{
}
void Gpt_Channel_Notify14(void)
{
}
void Gpt_Channel_Notify15(void)
{
}
void Gpt_Channel_Notify16(void)
{
}
void Gpt_Channel_Notify17(void)
{
}
void Gpt_Channel_Notify18(void)
{
}
void Gpt_Channel_Notify19(void)
{
}
void Gpt_Channel_Notify20(void)
{
}
void Gpt_Channel_Notify21(void)
{
}
void Gpt_Channel_Notify22(void)
{
}
void Gpt_Channel_Notify23(void)
{
}
void Gpt_Channel_Notify24(void)
{
}
void Gpt_Channel_Notify25(void)
{
}
void Gpt_Channel_Notify26(void)
{
}
void Gpt_Channel_Notify27(void)
{
}
void Gpt_Channel_Notify28(void)
{
}
void Gpt_Channel_Notify29(void)
{
}
void Gpt_Channel_Notify30(void)
{
}
void Gpt_Channel_Notify31(void)
{
}
void Gpt_Channel_Notify32(void)
{
}
