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
 *  \file     Gpt.c
 *
 *  \brief    This file contains GPT MCAL driver
 *
 */

/* Common Design ID's */
/*
 *Design: MCAL-21113, MCAL-16286, MCAL-16281, MCAL-16261, MCAL-16263, MCAL-16262, MCAL-16260,
 *MCAL-16434, MCAL-16433, MCAL-16425, MCAL-16435, MCAL-21112, MCAL-16436, MCAL-21506, MCAL-21504,
 *MCAL-21500, MCAL-21494, MCAL-21383, MCAL-21190
 */

/*  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt.c
 *    Component:  AM263x MCAL Driver
 *       Module:  GptDriver
 *    Generator:  None
 *
 *  Description: This component provides services for initialization and control of the
 *microcontroller internal GPT unit (General Purpose Timer).
 *********************************************************************************************************************/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Gpt.h"
#include "Gpt_Irq.h"
#include "Gpt_Priv.h"
/*LDRA_NOANALYSIS*/
#include "SchM_Gpt.h"

#include "Det.h"
/*LDRA_ANALYSIS*/

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((GPT_AR_RELEASE_MAJOR_VERSION != (4U)) || (GPT_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (GPT_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Gpt: AUTOSAR Version Numbers of Gpt are different!!"
#endif

/* Software version information check has to match definition in header file */
#if ((GPT_SW_MAJOR_VERSION != (10U)) || (GPT_SW_MINOR_VERSION != (2U)))
#error "Gpt: Software Version Numbers are inconsistent!!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define GPT_START_SEC_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Gpt_MemMap.h"
volatile VAR(uint32, GPT_DATA) Gpt_DriverStatus = GPT_DRIVER_UNINITIALIZED;
#define GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Gpt_MemMap.h"

#define GPT_START_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Gpt_MemMap.h"
VAR(uint32, GPT_DATA) Gpt_IsrIndex[GPT_RTI_MAX];

/* Variable to indicate the state of the channel */
/*A Channel will be in five states - Uninitialized,Initialized, Running,Stopped,Expired*/
VAR(Gpt_ChannelStateType, GPT_DATA) Gpt_ChannelState[GPT_RTI_MAX];

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
/* Variable indicate the notification status for each channel (bit wise) */
/* 1 - Notification is enabled for the corresponding channel
 * 0 - Notification is disabled for the corresponding channel            */
static VAR(uint16, GPT_DATA) Gpt_ActiveNotifyChannels;
#endif /* (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) */

/** \brief Tracks GPT channels mapped to counters */
VAR(uint32, GPT_DATA) Gpt_ChStartTime_map[GPT_RTI_MAX];

/* Driver Object of GPT Module. */
VAR(Gpt_DriverObjType, GPT_VAR_CLEARED) Gpt_DrvObj;

/** \brief Helps map channel ids to channel configuration objects */
VAR(uint16, GPT_DATA) Gpt_ChConfig_map[GPT_RTI_MAX];

#define GPT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Gpt_MemMap.h"

#define GPT_START_SEC_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Gpt_MemMap.h"
/** \brief GPT driver object */
P2CONST(Gpt_ConfigType, GPT_DATA, GPT_PBCFG) Gpt_Config_pt = (Gpt_ConfigType *)NULL_PTR;
#define GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"

#if (STD_ON == GPT_TIME_REMAINING_API)
static FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeMaxLevel(Gpt_ChannelType channel, Gpt_ChannelMode ChannelMode,
                                                         Gpt_ValueType FreeRunningCounter, Gpt_ValueType Compare);
#endif

#if (STD_ON == GPT_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, GPT_CODE) Gpt_CheckInitDetErrors(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_CONST) pConfig);
#endif
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define GPT_START_SEC_CODE
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Gpt_MemMap.h"

#if (STD_ON == GPT_VERSION_INFO_API)
/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*
 *Design: MCAL-16446, MCAL-16445
 */
FUNC(void, GPT_CODE)
Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) VersionInfoPtr)
{
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_GET_VERSION_INFO, GPT_E_PARAM_POINTER);
    }
    else
#endif
    {
        VersionInfoPtr->vendorID         = GPT_VENDOR_ID;
        VersionInfoPtr->moduleID         = GPT_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)GPT_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)GPT_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)GPT_SW_PATCH_VERSION;
    }

    return;
}
#endif /*(STD_ON == GPT_VERSION_INFO_API)*/

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA tool error " */
/*
 *Design: MCAL-21497, MCAL-16516, MCAL-16521, MCAL-16518, MCAL-16520, MCAL-16507, MCAL-16508,
 *MCAL-16509, MCAL-16510, MCAL-16511, MCAL-16514, MCAL-16512, MCAL-16513
 */

FUNC(void, GPT_CODE) Gpt_Init(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_CONST) configPtr)
{
    Std_ReturnType retVal = E_OK;
#if (STD_ON == GPT_PRE_COMPILE_VARIANT)
    if (NULL_PTR == configPtr)
    {
        Gpt_Config_pt = &GPT_INIT_CONFIG_PC;
    }
#endif
#if (STD_ON == GPT_POST_BUILD_VARIANT)
    if (NULL_PTR != configPtr)
    {
        Gpt_Config_pt = configPtr;
    }
#endif
    /* configPtr must not be NULL. In case it is NULL report an error and
     * return immediately.*/
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    retVal = Gpt_CheckInitDetErrors(Gpt_Config_pt);
#endif
    if (retVal == E_OK)
    {
        /* Reset the Channel notifications*/
#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
        Gpt_ActiveNotifyChannels = 0U;
#endif /* (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) */

        /* SWS_Gpt_00068: Only initialize configured resources, that means, only
         * timers listed in the channel configuration structure.
         */

        Gpt_ChConfig_map[0U] = (uint16)GPT_RTI_MAX;
        retVal               = Gpt_copyConfig(&Gpt_DrvObj, Gpt_Config_pt);

        if (retVal == E_OK)
        {
            Gpt_ConfigHwChannel(&Gpt_DrvObj, GPT_INITIALIZED);
        }

        if (retVal == E_OK)
        {
            Gpt_DriverStatus = GPT_DRIVER_INITIALIZED;
        }
    }
}

/*Gpt_Init*/

#if (STD_ON == GPT_DEINIT_API)

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA tool error " */
/*
 *Design: MCAL-16527, MCAL-16533, MCAL-16532, MCAL-16531, MCAL-16525, MCAL-16530, MCAL-16524,
 *MCAL-16528, MCAL-16529, MCAL-16419
 */

FUNC(void, GPT_CODE) Gpt_DeInit(void)
{
    Gpt_ChannelType ChannelIdx; /*Configured Channel Index*/
    Gpt_ChannelType Gpt_Channel;
    boolean         Dev_Error_Flag = FALSE;

    /* check if the driver has been successfully initialized. if the driver
     * has not been initialized, report an error and return immediately.
     */
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    if (Gpt_DriverStatus != GPT_DRIVER_INITIALIZED)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_DEINIT, GPT_E_UNINIT);
        Dev_Error_Flag = TRUE;
    }
#endif
    /*Return from the Api if Dev_Error_Flag is TRUE */
    if (Dev_Error_Flag == FALSE)
    {
        /* Check if any channel is in "Running" state,If true report error and
         *  return from the function*/
        for (ChannelIdx = 0U; ChannelIdx < Gpt_DrvObj.ChannelCount; ChannelIdx++)
        {
            Gpt_Channel = Gpt_DrvObj.gChannelConfig_pt[ChannelIdx].ChannelId;
            if (GPT_RUNNING == Gpt_ChannelState[Gpt_Channel])
            {
                /* At least one of the channels is active */
                (void)Det_ReportRuntimeError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_DEINIT, GPT_E_BUSY);
                Dev_Error_Flag = TRUE;
                break;
            }
        }
    }
    /* -------------------- DeInit Loop ----------------------------------------*/
    /*
     * SWS_Gpt_00234: If any timer channel is in state "running", the
     * function shall raise the error GPT_E_BUSY.
     */
    if (Dev_Error_Flag == FALSE)
    {
        /* Reset the GPT channel. */
        Gpt_ConfigHwChannel(&Gpt_DrvObj, GPT_UNINITIALIZED);

        /* Reset the driver object. */
        Gpt_resetDrvObj(&Gpt_DrvObj);

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)
        Gpt_ActiveNotifyChannels = 0U; /* Reset the notification attributes */
#endif                                 /* (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API) */

        /* Reset configuration pointer */
        Gpt_Config_pt           = (Gpt_ConfigType *)NULL_PTR;
        Gpt_DriverStatus        = GPT_DRIVER_UNINITIALIZED;
        Gpt_DrvObj.ChannelCount = 0U;
    }
} /* Gpt_DeInit */
#endif /* GPT_DEINIT_API */

#if (STD_ON == GPT_TIME_ELAPSED_API)

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA tool error " */
/*
 *Design: MCAL-16539, MCAL-16534, MCAL-16535, MCAL-16536, MCAL-16537, MCAL-16540, MCAL-16541,
 *MCAL-16542, MCAL-16543, MCAL-16544
 */

FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeElapsed(Gpt_ChannelType channel)
{
    Gpt_ValueType          UpdCompare = 0U;
    Gpt_ValueType          Compare    = 0U;
    Gpt_ValueType          FreeRunningCounter;
    Gpt_ChannelMode        ChannelMode;
    Gpt_ValueType          Return_Value = 0U;
    uint32                 Gpt_rtiChAddr;
    uint16                 channelIdx;
    uint32                 exitCondition = FALSE;
    Gpt_ChannelConfigType *gptDrvChannelObj;
    if (channel < GPT_RTI_MAX)
    {
        channelIdx = Gpt_ChConfig_map[channel];
    }

    /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/
    /* Check if the driver has been successfully initialized. If the driver
     * has not been initialized, report an error and return from Api.
     */
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    if (Gpt_DriverStatus != GPT_DRIVER_INITIALIZED)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_GET_TIME_ELAPSED, GPT_E_UNINIT);
        exitCondition = TRUE;
    }
    /* Check if parameter channel is in valid range. If its value is out
     * of range report an error and return from the function.    */
    /* If any channel is not configured then default channelIdx will be GPT_RTI_MAX */
    if ((exitCondition == FALSE) && ((channel > GPT_RTI_CH_MAX) || (channelIdx >= (uint16)GPT_RTI_MAX)))
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_GET_TIME_ELAPSED, GPT_E_PARAM_CHANNEL);
        exitCondition = TRUE;
    }
#endif
    /* Check if timer is in "initialized" state, if TRUE return value = 0"*/
    /* SWS_Gpt_00295: If timer is in "initialized" state, by default return value = 0 */
    if ((exitCondition == FALSE) && (GPT_INITIALIZED != Gpt_ChannelState[channel]))
    {
        Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(channel);
        /*Read the Counter, update counter and free running counter values of the channel*/

        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address " */
        /*LDRA_INSPECTED 91 D : MISRAC_2012_R4.7
         * "Reason - Return value used  " */
        FreeRunningCounter = Gpt_GetCounter_Values((rtiBASE_t *)Gpt_rtiChAddr, channel, &UpdCompare, &Compare);

        gptDrvChannelObj = &Gpt_DrvObj.gChannelConfig_pt[channelIdx];
        ChannelMode      = (gptDrvChannelObj->ChannelMode);

        /* SWS_Gpt_00299: Return the target time if the channel is
         * expired, else return the relative difference */
        if (GPT_CH_MODE_ONESHOT == ChannelMode)
        {
            if (GPT_EXPIRED == Gpt_ChannelState[channel])
            {
                Return_Value = Mod_Difference(Compare, Gpt_ChStartTime_map[channel]);
            }
            else
            {
                Return_Value = Mod_Difference(FreeRunningCounter, Gpt_ChStartTime_map[channel]);
            }
        }
        /* Continuous Mode */
        else
        {
            /*Find the relative difference b/w Compare and Free running counter*/
            Return_Value = UpdCompare - Mod_Difference(Compare, FreeRunningCounter);
        }
    }
    return Return_Value;
} /* Gpt_GetTimeElapsed */
#endif /* (STD_ON == GPT_CFG_USE_GET_TIME_ELAPSED) */

#if (STD_ON == GPT_TIME_REMAINING_API)

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA tool error " */
/*
 *Design: MCAL-16561, MCAL-16562, MCAL-16563, MCAL-16564, MCAL-16565, MCAL-16566, MCAL-16567,
 *MCAL-16568, MCAL-16569
 */
FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeRemaining(Gpt_ChannelType channel)
{
    Gpt_ValueType          Compare       = 0U;
    Gpt_ValueType          UpdateCompare = 0U;
    Gpt_ChannelMode        ChannelMode;
    Gpt_ValueType          FreeRunningCounter;
    Gpt_ValueType          Return_Value = 0U;
    uint32                 Gpt_rtiChAddr;
    Gpt_ChannelConfigType *gptDrvChannelObj;
    if (channel > GPT_RTI_CH_MAX)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_GET_TIME_REMAINING, GPT_E_PARAM_CHANNEL);
    }
    uint16 channelIdx = Gpt_ChConfig_map[channel];

    /* Check if the driver has been successfully initialized. If the driver
     * has not been initialized, report an error and return from Api.
     */
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    if (Gpt_DriverStatus != GPT_DRIVER_INITIALIZED)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_GET_TIME_REMAINING, GPT_E_UNINIT);
    }
    /* Check if parameter channel is in valid range. If its value is out
     * of range report an error and return from the function.    */
    /* If any channel is not configured then default channelIdx will be GPT_RTI_MAX */
    else if (channelIdx >= (uint16)GPT_RTI_MAX)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_GET_TIME_REMAINING, GPT_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        /* Check if timer is in "initialized" state, if TRUE return value = 0"*/
        /* SWS_Gpt_00301: If timer is in "initialized" state, by default return value = 0. */
        if (GPT_INITIALIZED != Gpt_ChannelState[channel])
        {
            Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(channel);

            /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
             * "Reason - Cast for register address " */
            /*LDRA_INSPECTED 91 D : MISRAC_2012_R4.7
             * "Reason - Return value used  " */
            FreeRunningCounter = Gpt_GetCounter_Values((rtiBASE_t *)Gpt_rtiChAddr, channel, &UpdateCompare, &Compare);

            /*Read the channel mode from the channel configuration*/
            gptDrvChannelObj = &Gpt_DrvObj.gChannelConfig_pt[channelIdx];
            ChannelMode      = (gptDrvChannelObj->ChannelMode);
            Return_Value     = Gpt_GetTimeMaxLevel(channel, ChannelMode, FreeRunningCounter, Compare);
        }
    }
    return (Return_Value);
} /* Gpt_GetTimeRemaining */

static FUNC(Gpt_ValueType, GPT_CODE) Gpt_GetTimeMaxLevel(Gpt_ChannelType channel, Gpt_ChannelMode ChannelMode,
                                                         Gpt_ValueType FreeRunningCounter, Gpt_ValueType Compare)
{
    Gpt_ValueType Return_Value = 0U;

    if ((ChannelMode == GPT_CH_MODE_CONTINUOUS) || (GPT_EXPIRED != Gpt_ChannelState[channel]))
    {
        Return_Value = Mod_Difference(Compare, FreeRunningCounter);
    }
    else
    {
        Return_Value = 0U;
    }
    return Return_Value;
}
/* Gpt_GetTimeRemaining */

#endif /* (STD_ON == GPT_CFG_USE_GET_TIME_REMAINING) */

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*
 *Design: MCAL-21508, MCAL-16570, MCAL-16571, MCAL-16572, MCAL-16573, MCAL-16574, MCAL-16575,
 *MCAL-16576, MCAL-16577, MCAL-16578
 */
FUNC(void, GPT_CODE) Gpt_StartTimer(Gpt_ChannelType channel, Gpt_ValueType value)
{
    uint16 channelIdx;
    uint32 exitCondition = FALSE; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/
    Gpt_ChannelConfigType *gptDrvChannelObj;
    if (channel < GPT_RTI_MAX)
    {
        channelIdx = Gpt_ChConfig_map[channel];
    }

    /* Check if the driver has been successfully initialized. If the driver
     * has not been initialized, report an error and return immediately.
     */
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    if (Gpt_DriverStatus != GPT_DRIVER_INITIALIZED)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_START_TIMER, GPT_E_UNINIT);
        exitCondition = TRUE;
    }
    /* Check if parameter channel is in valid range and not in Uninitialized mode. If its value is
     * out of range report an error and set flag.
     */
    if ((exitCondition == FALSE) && ((channel > GPT_RTI_CH_MAX) || (GPT_UNINITIALIZED == Gpt_ChannelState[channel])))
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_START_TIMER, GPT_E_PARAM_CHANNEL);
        exitCondition = TRUE;
    }
    /* Check if parameter value is in valid range. If "0" is specified as
     * value, report an error and set flag.
     */
    if ((exitCondition == FALSE) && ((value == 0U) || (value >= MAX_RESOLUTION)))
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_START_TIMER, GPT_E_PARAM_VALUE);
        exitCondition = TRUE;
    }
#endif
    if (exitCondition == FALSE)
    {
        /*Check if channel is running, report error GPT_E_BUSY if channel already in "Running"
         * state*/
        if (GPT_RUNNING == Gpt_ChannelState[channel])
        {
            (void)Det_ReportRuntimeError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_START_TIMER, GPT_E_BUSY);
        }
        else
        {
            /* Critical section, block the interrupts */
            SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0();

            /*Set the channel mode for notification index*/
            gptDrvChannelObj      = &Gpt_DrvObj.gChannelConfig_pt[channelIdx];
            Gpt_IsrIndex[channel] = (gptDrvChannelObj->ChannelMode);

            /*Set the register settings required to start selected channel with defined target
             * time*/
            Gpt_SetRegStartTimer(channel, value);

            /*Set the channel state to "Running"*/
            /* SWS_Gpt_00364: Set the channel state to "Running"*/
            Gpt_ChannelState[channel] = GPT_RUNNING;

            /* Critical section, restore the interrupts */
            SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0();

        } /*if (Dev_Error_Flag == FALSE)*/
    }
} /* Gpt_StartTimer */

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*
 *Design: MCAL-16579, MCAL-16580, MCAL-16581, MCAL-16582, MCAL-16583, MCAL-16584, MCAL-16585,
 *MCAL-16586
 */

FUNC(void, GPT_CODE) Gpt_StopTimer(Gpt_ChannelType channel)
{
    uint32 Gpt_rtiChAddr;
    /* Check if the driver has been successfully initialized. If the driver
     * has not been initialized, report an error and return immediately.
     */
#if (STD_ON == GPT_DEV_ERROR_DETECT)

    /* Lower 2 bits determine the compare block - (0, 1, 2, 3) */
    uint32 exitCondition = FALSE; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/
    if (Gpt_DriverStatus != GPT_DRIVER_INITIALIZED)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_STOP_TIMER, GPT_E_UNINIT);
        exitCondition = TRUE;
    }
    /* Check if parameter channel is in valid range. If its value is out
     * of range report an error and return immediately.
     */
    if ((exitCondition == FALSE) && (channel > GPT_RTI_CH_MAX))
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_STOP_TIMER, GPT_E_PARAM_CHANNEL);
        exitCondition = TRUE;
    }
    if (exitCondition == FALSE)
#endif
    {
        /*Check for Channel State, if channel is not in "Running" state
         * there will be no state change  */
        if (Gpt_ChannelState[channel] == GPT_RUNNING)
        {
            Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(channel);
            /* Critical section, block the interrupts */
            SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0();

            /* SWS_Gpt_00343: Set the channel state to "Stopped" */
            Gpt_ChannelState[channel] = GPT_STOPPED;

            /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
             * "Reason - Cast for register address " */
            /*LDRA_INSPECTED 105 D : MISRAC_2012_R2.2
             * "Reason - Code inspected LDRA tool error " */
            Gpt_RTI_StopTimer((rtiBASE_t *)Gpt_rtiChAddr, channel);

            /* Critical section, restore the interrupts */
            SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0();
        } /*if (Channel_State == GPT_RUNNING)*/
    }
} /* Gpt_StopTimer */

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*
 *Design: MCAL-16587, MCAL-16588, MCAL-16589, MCAL-16590, MCAL-16591, MCAL-16592, MCAL-16593
 */

FUNC(void, GPT_CODE) Gpt_EnableNotification(Gpt_ChannelType channel)
{
    uint32 Gpt_rtiChAddr;

    /* Check if the driver has been successfully initialized. If the driver
     * has not been initialized, report an error and return immediately.
     */
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    uint16                 channelIdx;
    Gpt_ChannelConfigType *gptDrvChannelObj;
    if (channel < GPT_RTI_MAX)
    {
        channelIdx       = Gpt_ChConfig_map[channel];
        gptDrvChannelObj = &Gpt_DrvObj.gChannelConfig_pt[channelIdx];
    }

    if (Gpt_DriverStatus != GPT_DRIVER_INITIALIZED)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_ENABLE_NOTIFY, GPT_E_UNINIT);
    }
    /* Check if parameter channel is in valid range. If its value is out
     * of range report an error and return immediately.
     */
    else if ((channel > GPT_RTI_CH_MAX) || (NULL_PTR == gptDrvChannelObj->Notification_pt))
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_ENABLE_NOTIFY, GPT_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(channel);
        /* Critical section, block the interrupts */
        SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0();

        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address " */
        /*LDRA_INSPECTED 105 D : MISRAC_2012_R2.2
         * "Reason - Code inspected LDRA tool error " */
        Gpt_RTI_EnableNotification((rtiBASE_t *)Gpt_rtiChAddr, channel);

        /* Mark the notification for this channel */
        SET(uint16, Gpt_ActiveNotifyChannels, channel);

        /* Critical section, restore the interrupts */
        SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0();
    }
} /* Gpt_EnableNotification */
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API */

#if (STD_ON == GPT_ENABLE_DISABLE_NOTIFICATION_API)

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*
 *Design: MCAL-16766, MCAL-16767, MCAL-16768, MCAL-16769, MCAL-16770, MCAL-16771, MCAL-16772
 */

FUNC(void, GPT_CODE) Gpt_DisableNotification(Gpt_ChannelType channel)
{
    uint32 Gpt_rtiChAddr;
    /* Check if the driver has been successfully initialized. If the driver
     * has not been initialized, report an error and return immediately.
     */
#if (STD_ON == GPT_DEV_ERROR_DETECT)
    uint16                 channelIdx;
    Gpt_ChannelConfigType *gptDrvChannelObj;
    if (channel < GPT_RTI_MAX)
    {
        channelIdx       = Gpt_ChConfig_map[channel];
        gptDrvChannelObj = &Gpt_DrvObj.gChannelConfig_pt[channelIdx];
    }
    if (Gpt_DriverStatus != GPT_DRIVER_INITIALIZED)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_DISABLE_NOTIFY, GPT_E_UNINIT);
    }
    /* Check if parameter channel is in valid range. If its value is out
     * of range report an error and return immediately.
     */
    else if ((channel > GPT_RTI_CH_MAX) || (NULL_PTR == gptDrvChannelObj->Notification_pt))
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_DISABLE_NOTIFY, GPT_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(channel);
        /* Critical section, block the interrupts */
        SchM_Enter_Gpt_GPT_EXCLUSIVE_AREA_0();
        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address " */
        /*LDRA_INSPECTED 105 D : MISRAC_2012_R2.2
         * "Reason - Code inspected LDRA tool error " */
        Gpt_RTI_DisableNotification((rtiBASE_t *)Gpt_rtiChAddr, channel);
        /* Mark the notification for this channel */
        CLEAR(uint16, Gpt_ActiveNotifyChannels, channel);
        /* Critical section, restore the interrupts */
        SchM_Exit_Gpt_GPT_EXCLUSIVE_AREA_0();
    }
}
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API */

#if (STD_ON == GPT_REGISTER_READBACK_API)

/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is external APIs " */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA tool error " */
/*
 *Design: MCAL-21532
 */

FUNC(Std_ReturnType, GPT_CODE)
Gpt_ConfigRegReadBack(Gpt_ChannelType channel, GptConfigReg *GptConfigReg_pt)
{
    VAR(Std_ReturnType, AUTOMATIC) Gpt_RetTmp;
    Gpt_ChannelType        Gpt_Channel;
    uint16                 channelIdx;
    Gpt_ChannelConfigType *gptDrvChannelObj;
    if (channel < GPT_RTI_MAX)
    {
        channelIdx       = Gpt_ChConfig_map[channel];
        gptDrvChannelObj = &Gpt_DrvObj.gChannelConfig_pt[channelIdx];
    }
    Gpt_RetTmp = (Std_ReturnType)E_NOT_OK;
    if ((NULL_PTR != GptConfigReg_pt) && (Gpt_DriverStatus == GPT_DRIVER_INITIALIZED))
    {
        Gpt_Channel = gptDrvChannelObj->ChannelId;
        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address " */
        Gpt_RegReadBack((rtiBASE_t *)Gpt_GetRTIChannelAddr(Gpt_Channel), GptConfigReg_pt);

        Gpt_RetTmp = (Std_ReturnType)E_OK;
    }
    return Gpt_RetTmp;
}
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(void, GPT_CODE) Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
    return;
}
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(void, GPT_CODE) Gpt_DisableWakeup(Gpt_ChannelType Channel)
{
    return;
}
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(void, GPT_CODE) Gpt_EnableWakeup(Gpt_ChannelType Channel)
{
    return;
}
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

FUNC(Std_ReturnType, GPT_CODE)
Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32 *TimeValuePtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    return retVal;
}

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(void, GPT_CODE) Gpt_SetMode(Gpt_ModeType Mode)
{
    return;
}
#endif /* if(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (STD_ON == GPT_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, GPT_CODE) Gpt_CheckInitDetErrors(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_CONST) pConfig)
{
    Std_ReturnType status = E_OK;

    if (NULL_PTR == pConfig)
    {
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_INIT, GPT_E_PARAM_POINTER);
        status = E_NOT_OK;
    }
    else if (Gpt_DriverStatus != GPT_DRIVER_UNINITIALIZED)
    {
        /* Gpt module must not be initalized. Otherwise call the Det with GPT_E_ALREADY_INITIALIZED
         */
        /*
         *SWS_Gpt_00307:Gpt module must not be initialized.
         * Otherwise call the Det with GPT_E_ALREADY_INITIALIZED
         */
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_INIT, GPT_E_ALREADY_INITIALIZED);
        status = E_NOT_OK;
    }
    else
    {
        /* Do Nothing*/
    }
    return status;
}
#endif /* #if (STD_ON == GPT_DEV_ERROR_DETECT) */

#define GPT_STOP_SEC_CODE
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Gpt_MemMap.h"
/* eof */
