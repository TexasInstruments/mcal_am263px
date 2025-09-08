/* ======================================================================
 *   Copyright (C) 2022 Texas Instruments Incorporated
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
 *  \file     GptApp.c
 *
 *  \brief    This file contains the GPT test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "assert.h"
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
#include "SchM_Gpt.h"
#include "SchM_Port.h"
#include "Det.h"
#include "Dem.h"
/*LDRA_ANALYSIS*/

#include "Gpt.h"

#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"

#include "GptApp.h"
#include "GptApp_Startup.h"
#include "trace.h"

/* For PRCM base addresses */
#include "soc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof((x)[0]))
#define GptChannel_0 (0U)

#ifdef GPTTIMER_QT
#define GPTIMER_1_SECOND 0x10U
#else
/*Value of the GPT period for 1 second : 200MHz*/
#define GPTIMER_1_SECOND 0x5F5E100U
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*None*/

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void _enable_interrupt_(void);
void StartCyclecount(void);
void GptApp_platformInit(void);
void GptApp_interruptConfig(uint32 channelId);
void GptApp_interruptInit(void);
void GptApp_interruptDisable(uint32 channelId);

void Gpt_App_mainTest(void);
typedef void (*Gpt_AppFxn_t)(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const struct Gpt_ConfigType_s Gpt_Config;
volatile uint32                      Gpt_notifyRecvFlag         = 0xFFFF;
uint8                                validWakeupSrcDetectedFlag = (uint8)FALSE;

Gpt_AppFxn_t Gpt_AppFxnTbl[] = {&Gpt_App_mainTest};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined CLANG
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif

int main(void)
{
    uint32 i, gTestPassed = E_OK;
    GptApp_Startup();
    /*Enable Domain clocks*/
    GptApp_platformInit();
    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\n\r");
    for (i = 0U; i < ARRAYSIZE(Gpt_AppFxnTbl); i++)
    {
        Gpt_AppFxnTbl[i]();
    }
    AppUtils_printf(APP_NAME ": Sample Application - DONE !!!\n\r");
    GT_1trace(McalAppTrace, GT_INFO, " GPT Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(McalAppTrace, GT_ERR, " GPT Stack/section corruption!!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, " All tests have Passed!!!\n\r");
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, " GPT Test Failed!!!\n\r");
    }
    GptApp_TimeDeinit();
    return (0);
}

void Gpt_App_mainTest(void)
{
    uint32                 countVal, currCountval = 0;
    uint32                 j;
    Gpt_ChannelConfigType *pChannelCfg;
    Gpt_ChannelType        ChannelId;
    uint32                 tickFreq;

#if (GPT_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
#endif /* #if (GPT_VERSION_INFO_API == STD_ON) */

#if (GPT_VERSION_INFO_API == STD_ON)
    /* Get and print version */
    Gpt_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n\r");
    AppUtils_printf("GPT MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf("Vendor ID           : %d\n\r", versioninfo.vendorID);
    AppUtils_printf("Module ID           : %d\n\r", versioninfo.moduleID);
    AppUtils_printf("SW Major Version    : %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf("SW Minor Version    : %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf("SW Patch Version    : %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n\r");
#endif

    AppUtils_printf("----------------------------------------------------------------------------------\n\r");
    AppUtils_printf(APP_NAME ": GPTIMER Test Configuration\n\r");
    AppUtils_printf("----------------------------------------------------------------------------------\n\r");

    AppUtils_printf("Initializing channels\n\r");
#if (STD_ON == GPT_PRE_COMPILE_VARIANT)
    AppUtils_printf("Precompile variant is being used .. \n\r");
    Gpt_Init((const Gpt_ConfigType *)NULL_PTR);
#else
    AppUtils_printf("Post-Build variant is being used .. \n\r");
    Gpt_Init(&Gpt_Config);
#endif

    /* change this once debug is done */
    countVal = 1 * GPTIMER_1_SECOND;

    for (j = 0U; j < Gpt_Config.ChannelCount; j++)
    {
        /* Take each channel configuration in configuration set */
        pChannelCfg = (Gpt_ChannelConfigType *)(Gpt_Config.ChannelConfig_pt + j);
        ChannelId   = pChannelCfg->ChannelId;
        tickFreq    = pChannelCfg->GptChannelTickFrequency;
        AppUtils_printf("------------------------------------------\n\r");
        AppUtils_printf(APP_NAME ": Running GPT Test for channel %d\n\r", (ChannelId));
        AppUtils_printf("------------------------------------------\n\r");

        GptApp_interruptConfig(ChannelId);
        AppUtils_printf(APP_NAME ": Starting timer for %d s \n\r", (countVal + tickFreq * countVal) / GPTIMER_1_SECOND);
        Gpt_StartTimer(ChannelId, countVal + tickFreq * countVal);

#if (STD_ON == GPT_TIME_ELAPSED_API)
        // currCountval = Gpt_GetTimeElapsed(ChannelId);
        currCountval = Gpt_GetTimeElapsed(ChannelId);
        AppUtils_printf(APP_NAME ": Time Elapsed Value = %x\n\r", currCountval);
#endif
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
        AppUtils_printf(APP_NAME ": Enable channel notification for this channel\n\r");
        Gpt_EnableNotification(ChannelId);
#endif

        AppUtils_printf(APP_NAME ": Wait for notification(approx. %d seconds)\n\r",
                        (countVal + tickFreq * countVal) / GPTIMER_1_SECOND);
        /* Wait till you get timer notifications */
        while (ChannelId != Gpt_notifyRecvFlag)
        {
#if (STD_ON == GPT_TIME_ELAPSED_API)
            currCountval = Gpt_GetTimeElapsed(ChannelId);
/*AppUtils_printf(APP_NAME ": Time Elapsed Value = %x\n\r",
                currCountval);*/
#endif
        }
        AppUtils_printf("\n\r");
        Gpt_notifyRecvFlag = 0xFFFF;

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
        AppUtils_printf(APP_NAME ": Disable channel notification for this channel\n\r");
        Gpt_DisableNotification(ChannelId);
#endif

        AppUtils_printf(APP_NAME ": Wait till timer overflows, no notification should be received\n\r");
        /* Wait till timer overflows, you should not receive notification as
         * it is disabled */
#ifdef GPTTIMER_QT
        AppUtils_delay(1U);
#else
        AppUtils_delay(10U);
#endif
#if (STD_ON == GPT_TIME_ELAPSED_API)
        currCountval = Gpt_GetTimeElapsed(ChannelId);
        AppUtils_printf(APP_NAME ": Time Elapsed Value = 0x%x\n\r", currCountval);
#endif
#ifdef GPTTIMER_QT
        AppUtils_delay(2U);
#else
        AppUtils_delay(20U);
#endif
#if (STD_ON == GPT_TIME_REMAINING_API)
        currCountval = Gpt_GetTimeRemaining(ChannelId);
#endif
        AppUtils_printf(APP_NAME ": Time Remaining Value = 0x%x\n\r", currCountval);
        Gpt_notifyRecvFlag = 0xFFFF;
        /* Wait for 1 minute as countVal is FFF and timer tick is ~1ns(20Mhz
         * clk) it will take ~5ms to overflow */
        AppUtils_printf("Waiting for timer to overflow\n\r");
#ifdef GPTTIMER_QT
        AppUtils_delay(3U);
#else
        AppUtils_delay(1000U);
#endif
        AppUtils_printf("Overflow happened no notification received\n\r");

        AppUtils_printf(APP_NAME ": Stop timer \n\r");
        Gpt_StopTimer(ChannelId);

        GptApp_interruptDisable(ChannelId);

        AppUtils_printf("GPT Test Passed for channel =%d !!!\n\r", (ChannelId));
    }
    /* Deinit current configuration */
#if (STD_ON == GPT_DEINIT_API)
    Gpt_DeInit();
#endif
    AppUtils_printf("GPT Test Passed for configuration!!\n\r");
    AppUtils_printf("GPT Test Completed, njoy life!!!\n\r");
}

void SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void Gpt_Channel_Notify5(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 5 :)!!!\n\r");
    Gpt_notifyRecvFlag = 4U; /* Set it to channel number */
}

void Gpt_Channel_Notify6(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 6 :)!!!\n\r");
    Gpt_notifyRecvFlag = 5U; /* Set it to channel number */
}

void Gpt_Channel_Notify7(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 7 :)!!!\n\r");
    Gpt_notifyRecvFlag = 6U; /* Set it to channel number */
}

void Gpt_Channel_Notify8(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 8 :)!!!\n\r");
    Gpt_notifyRecvFlag = 7U; /* Set it to channel number */
}

void Gpt_Channel_Notify9(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 9 :)!!!\n\r");
    Gpt_notifyRecvFlag = 8U; /* Set it to channel number */
}

void Gpt_Channel_Notify10(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 10 :)!!!\n\r");
    Gpt_notifyRecvFlag = 9U; /* Set it to channel number */
}

void Gpt_Channel_Notify11(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 11 :)!!!\n\r");
    Gpt_notifyRecvFlag = 10U; /* Set it to channel number */
}

void Gpt_Channel_Notify12(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 12 :)!!!\n\r");
    Gpt_notifyRecvFlag = 11U; /* Set it to channel number */
}

void Gpt_Channel_Notify13(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 13 :)!!!\n\r");
    Gpt_notifyRecvFlag = 12U; /* Set it to channel number */
}

void Gpt_Channel_Notify14(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 14 :)!!!\n\r");
    Gpt_notifyRecvFlag = 13U; /* Set it to channel number */
}

void Gpt_Channel_Notify15(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 15 :)!!!\n\r");
    Gpt_notifyRecvFlag = 14U; /* Set it to channel number */
}

void Gpt_Channel_Notify16(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 16 :)!!!\n\r");
    Gpt_notifyRecvFlag = 15U; /* Set it to channel number */
}

void Gpt_Channel_Notify17(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 17 :)!!!\n\r");
    Gpt_notifyRecvFlag = 16U; /* Set it to channel number */
}

void Gpt_Channel_Notify18(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 18 :)!!!\n\r");
    Gpt_notifyRecvFlag = 17U; /* Set it to channel number */
}

void Gpt_Channel_Notify19(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 19 :)!!!\n\r");
    Gpt_notifyRecvFlag = 18U; /* Set it to channel number */
}
void Gpt_Channel_Notify20(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 20 :)!!!\n\r");
    Gpt_notifyRecvFlag = 19U; /* Set it to channel number */
}

void Gpt_Channel_Notify21(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 21 :)!!!\n\r");
    Gpt_notifyRecvFlag = 20U; /* Set it to channel number */
}

void Gpt_Channel_Notify22(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 22 :)!!!\n\r");
    Gpt_notifyRecvFlag = 21U; /* Set it to channel number */
}

void Gpt_Channel_Notify23(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 23 :)!!!\n\r");
    Gpt_notifyRecvFlag = 22U; /* Set it to channel number */
}

void Gpt_Channel_Notify24(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 24 :)!!!\n\r");
    Gpt_notifyRecvFlag = 23U; /* Set it to channel number */
}

void Gpt_Channel_Notify25(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 25 :)!!!\n\r");
    Gpt_notifyRecvFlag = 24U; /* Set it to channel number */
}

void Gpt_Channel_Notify26(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 26 :)!!!\n\r");
    Gpt_notifyRecvFlag = 25U; /* Set it to channel number */
}

void Gpt_Channel_Notify27(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 27 :)!!!\n\r");
    Gpt_notifyRecvFlag = 26U; /* Set it to channel number */
}

void Gpt_Channel_Notify28(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 28 :)!!!\n\r");
    Gpt_notifyRecvFlag = 27U; /* Set it to channel number */
}

void Gpt_Channel_Notify29(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 29 :)!!!\n\r");
    Gpt_notifyRecvFlag = 28U; /* Set it to channel number */
}

void Gpt_Channel_Notify30(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 5 :)!!!\n\r");
    Gpt_notifyRecvFlag = 29U; /* Set it to channel number */
}

void Gpt_Channel_Notify31(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 30 :)!!!\n\r");
    Gpt_notifyRecvFlag = 30U; /* Set it to channel number */
}

void Gpt_Channel_Notify32(void)
{
    AppUtils_printf(APP_NAME ": GPT Test Notification Receiver channel 31 :)!!!\n\r");
    Gpt_notifyRecvFlag = 31U; /* Set it to channel number */
}

#if ((STD_ON == GPT_WAKEUP_FUNCTIONALITY_API) && (STD_ON == GPT_REPORT_WAKEUP_SOURCE))
void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    AppUtils_printf(APP_NAME ": GPT Test Wakeup event received for wakeupSource =%d :)!!!\n\r", wakeupSource);
    validWakeupSrcDetectedFlag = (uint8)TRUE;
}

void EcuM_SetWakeupEvent(EcuM_WakeupSourceType chlWakeupRef)
{
    /* This function will be called after call to Gpt_CheckWakeup.
     * Gpt_CheckWakeup will call this function if wakeup source passed to it is
     * valid source */
    AppUtils_printf(APP_NAME ": GPT Test Wakeup event set for wakeupSource =%d :)!!!\n\r", chlWakeupRef);
}

#endif

/*EoF*/
