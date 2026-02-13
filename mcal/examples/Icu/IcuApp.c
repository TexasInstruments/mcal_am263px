/* ======================================================================
 *   Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     IcuApp.c
 *
 *  \brief    This file contains the Icu test example
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "assert.h"
/*LDRA_NOANALYSIS*/
#include "string.h"
#include "Det.h"
#include "Dem.h"
#include "Std_Types.h"
#include "Os.h"
/*LDRA_ANALYSIS*/
#include "EcuM_Cbk.h"
#include "Pwm_Cfg.h"
#include "Icu_Cfg.h"
#include "sys_common.h"
#include "trace.h"
#include "soc.h"
#include "Pwm_Irq.h"
#include "Icu_Irq.h"
#include "IcuApp.h"
#include "hw_icu.h"
#include "IcuApp_Startup.h"

#define ICU_CHANNEL (ICU_CHANNEL0)

#define PWM_SYS_CLOCK (200000000)

volatile boolean Icu_NotifyIntervalReached     = FALSE;
volatile boolean Icu_SignalNotificationReached = FALSE;
volatile uint32  Icu_SignalNotificationNumber  = 0U;

Std_VersionInfoType VersionInfo;
sint32              TestState      = TRUE;
sint32              notifyRecvFlag = TRUE;

/*Notification function definitions*/
void Icu_SignalNotification_Channel1(void)
{
    Icu_SignalNotificationNumber++;
}

void Icu_TimeStampNotification_Channel1(void)
{
    Icu_NotifyIntervalReached = TRUE;
}

void Pwm_Notification_Channel1(void)
{
}

void Pwm_Notification_Channel2(void)
{
}
void Pwm_Notification_Channel3(void)
{
}

void SchM_Enter_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Pwm_PWM_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

static void IcuApp_mainTest(void)
{
    AppUtils_TimerInit();

#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
    uint16            elapsedTime = 0U;
    Icu_DutyCycleType dutyCycleApp;
    uint16            periodTimeApp, activeTimeApp = 0U;
#endif
#if (STD_ON == ICU_TIMESTAMP_API)
    Icu_ActivationType activation = ICU_RISING_EDGE;
    uint16             bufferSize = 6;
    Icu_ValueType      timestampArray[bufferSize];
#endif
#if (STD_ON == ICU_EDGE_COUNT_API)
    Icu_EdgeNumberType edgecount = 0;
#endif
#if (STD_ON == ICU_EDGE_DETECT_API)
    Icu_InputStateType inputstate;
#endif

#if (ICU_GET_VERSION_INFO_API == STD_ON)

    Std_VersionInfoType versioninfo;

    /* Version Info Check*/
    Icu_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n\r");
    AppUtils_printf(APP_NAME ": ICU MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf(APP_NAME ": Vendor ID: %d\n\r", versioninfo.vendorID);
    AppUtils_printf(APP_NAME ": Module ID: %d\n\r", versioninfo.moduleID);
    AppUtils_printf(APP_NAME ": SW Major Version: %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf(APP_NAME ": SW Minor Version: %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf(APP_NAME ": SW Patch Version: %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n\r");
#endif

/* ICU Init*/
#if (STD_ON == ICU_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n");
#else
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
#endif
    AppUtils_printf(" \n\r");

#if (STD_ON == ICU_PRE_COMPILE_VARIANT)
#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API || STD_ON == ICU_EDGE_COUNT_API || STD_ON == ICU_EDGE_DETECT_API || \
     STD_ON == ICU_TIMESTAMP_API)
    const Icu_ConfigType *pCfgPtr = &ICU_INIT_CONFIG_PC;
#endif
    Icu_Init(NULL_PTR);
#else
    const Icu_ConfigType *pCfgPtr = &Icu_Config;
    Icu_Init(pCfgPtr);
#endif

#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API || STD_ON == ICU_EDGE_COUNT_API || STD_ON == ICU_EDGE_DETECT_API || \
     STD_ON == ICU_TIMESTAMP_API)
    Icu_MeasurementModeType mode = pCfgPtr->chCfg[0].measurementMode;
#endif

#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)

    if (mode == ICU_MODE_SIGNAL_MEASUREMENT)
    {
        AppUtils_printf(APP_NAME ": Signal Measurement Mode! \n\r");
        Icu_SignalMeasurementPropertyType type = pCfgPtr->chCfg[0].signalMeasurementProperty;

        Icu_StartSignalMeasurement(ICU_CHANNEL);
        AppUtils_delay(100U);
        Icu_StopSignalMeasurement(ICU_CHANNEL);
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
        elapsedTime = Icu_GetTimeElapsed(ICU_CHANNEL);
#endif /*#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)*/
        if (type == ICU_PERIOD_TIME)
        {
            AppUtils_printf(APP_NAME ": elapsed time (Period) is  %d us\n\r", elapsedTime);
        }
        else if (type == ICU_HIGH_TIME)
        {
            AppUtils_printf(APP_NAME ": elapsed time (High Time) is  %d us\n\r", elapsedTime);
        }
        else if (type == ICU_LOW_TIME)
        {
            AppUtils_printf(APP_NAME ": elapsed time (Low Time) is  %d us\n\r", elapsedTime);
        }
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
        Icu_GetDutyCycleValues(ICU_CHANNEL, &dutyCycleApp);
#endif /*#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)*/
        activeTimeApp = dutyCycleApp.ActiveTime;
        periodTimeApp = dutyCycleApp.PeriodTime;
        AppUtils_printf(APP_NAME ": Active Time is %d \n\r", activeTimeApp);
        AppUtils_printf(APP_NAME ": Period Time is %d \n\r", periodTimeApp);
        float32 duty_value = activeTimeApp / (periodTimeApp * 1.0);
        AppUtils_printf(APP_NAME ": Duty Cycle is %f\n\r", duty_value);
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
        elapsedTime = Icu_GetTimeElapsed(ICU_CHANNEL);
#endif /*#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)*/
        AppUtils_printf(APP_NAME ": elapsed time read is  %d us\n\r", elapsedTime);

        Icu_StartSignalMeasurement(ICU_CHANNEL);
        AppUtils_delay(100U);
        Icu_StopSignalMeasurement(ICU_CHANNEL);
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
        elapsedTime = Icu_GetTimeElapsed(ICU_CHANNEL);
#endif
        if (type == ICU_PERIOD_TIME)
        {
            AppUtils_printf(APP_NAME ": elapsed time (Period) is  %d us\n\r", elapsedTime);
        }
        else if (type == ICU_HIGH_TIME)
        {
            AppUtils_printf(APP_NAME ": elapsed time (High Time) is  %d us\n\r", elapsedTime);
        }
        else if (type == ICU_LOW_TIME)
        {
            AppUtils_printf(APP_NAME ": elapsed time (Low Time) is  %d us\n\r", elapsedTime);
        }
#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
        Icu_GetDutyCycleValues(ICU_CHANNEL, &dutyCycleApp);
#endif /*#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)*/
        activeTimeApp = dutyCycleApp.ActiveTime;
        periodTimeApp = dutyCycleApp.PeriodTime;
        AppUtils_printf(APP_NAME ": Active Time is %d \n\r", activeTimeApp);
        AppUtils_printf(APP_NAME ": Period Time is %d \n\r", periodTimeApp);
        duty_value = activeTimeApp / (periodTimeApp * 1.0);
        AppUtils_printf(APP_NAME ": Duty Cycle is %f\n\r", duty_value);
    }

#endif /* ICU_SIGNAL_MEASUREMENT_API*/

#if (STD_ON == ICU_TIMESTAMP_API)

    if (mode == ICU_MODE_TIMESTAMP)
    {
        AppUtils_printf(APP_NAME ": Timestamp Mode! \n\r");

        if (activation == ICU_RISING_EDGE)
        {
            AppUtils_printf(APP_NAME ": Setting activation edge to RISING. \n\r");
        }
        else if (activation == ICU_FALLING_EDGE)
        {
            AppUtils_printf(APP_NAME ": Setting activation edge to FALLING. \n\r");
        }
        else if (activation == ICU_BOTH_EDGES)
        {
            AppUtils_printf(APP_NAME ": Setting activation edge to BOTH. \n\r");
        }

        Icu_SetActivationCondition(ICU_CHANNEL, activation);

        Icu_EnableNotification(ICU_CHANNEL);
        for (uint16 i = 0U; i < bufferSize; i++)
        {
            timestampArray[i] = 0U;
        }
        Icu_StartTimestamp(ICU_CHANNEL, &timestampArray[0], bufferSize, 6);
        AppUtils_delay(100);

        while (!Icu_NotifyIntervalReached)
        {
            AppUtils_printf(APP_NAME ": still looping in timestamp \n\r");
        }
        Icu_NotifyIntervalReached = FALSE;

        AppUtils_printf(APP_NAME ": Array value 0 is %d \n\r", timestampArray[0]);
        AppUtils_printf(APP_NAME ": Array value 1 is %d \n\r", timestampArray[1]);
        AppUtils_printf(APP_NAME ": Array value 2 is %d \n\r", timestampArray[2]);
        AppUtils_printf(APP_NAME ": Array value 3 is %d \n\r", timestampArray[3]);
        AppUtils_printf(APP_NAME ": Array value 4 is %d \n\r", timestampArray[4]);
        AppUtils_printf(APP_NAME ": Array value 5 is %d \n\r", timestampArray[5]);

        Icu_StopTimestamp(ICU_CHANNEL);
    }

#endif /* ICU_TIMESTAMP_API*/

#if (STD_ON == ICU_EDGE_COUNT_API)

    if (mode == ICU_MODE_EDGE_COUNTER)
    {
        AppUtils_printf(APP_NAME ": Edge Count Mode! \n\r");

        Icu_EnableEdgeCount(ICU_CHANNEL);
        /* Wait 1 seconds */
        AppUtils_delay(1000);
        Icu_DisableEdgeCount(ICU_CHANNEL);

        edgecount = Icu_GetEdgeNumbers(ICU_CHANNEL);
        AppUtils_printf(APP_NAME ": edgecount in 1 sec is  %d \n\r", edgecount);

        Icu_ResetEdgeCount(ICU_CHANNEL);

        edgecount = Icu_GetEdgeNumbers(ICU_CHANNEL);
        AppUtils_printf(APP_NAME ": edgecount after reset is %d \n\r", edgecount);
    }

#endif

#if (STD_ON == ICU_EDGE_DETECT_API)

    if (mode == ICU_MODE_SIGNAL_EDGE_DETECT)
    {
        AppUtils_printf(APP_NAME ": Edge Detect Mode! \n\r");

        inputstate = Icu_GetInputState(ICU_CHANNEL);
        if (inputstate == ICU_ACTIVE)
        {
            AppUtils_printf(APP_NAME ": input state is ICU_ACTIVE\n\r");
        }
        else if (inputstate == ICU_IDLE)
        {
            AppUtils_printf(APP_NAME ": input state is ICU_IDLE \n\r");
        }

        Icu_EnableNotification(ICU_CHANNEL);

        Icu_EnableEdgeDetection(ICU_CHANNEL);

        AppUtils_delay(1000);

        AppUtils_printf(APP_NAME ": SignalNotification for Double Edge Detection Reached in 1 sec: %d \n\r",
                        Icu_SignalNotificationNumber);
        Icu_SignalNotificationNumber = 0U;

        Icu_DisableEdgeDetection(ICU_CHANNEL);

        Icu_SetActivationCondition(ICU_CHANNEL, ICU_RISING_EDGE);

        Icu_EnableEdgeDetection(ICU_CHANNEL);

        AppUtils_delay(1000);

        AppUtils_printf(APP_NAME ": SignalNotification for Single Edge Detection Reached in 1 sec: %d \n\r",
                        Icu_SignalNotificationNumber);
        Icu_SignalNotificationNumber = 0U;

        Icu_DisableEdgeDetection(ICU_CHANNEL);

        inputstate = Icu_GetInputState(ICU_CHANNEL);
        if (inputstate == ICU_ACTIVE)
        {
            AppUtils_printf(APP_NAME ": input state is ICU_ACTIVE\n\r");
        }
        else if (inputstate == ICU_IDLE)
        {
            AppUtils_printf(APP_NAME ": input state is ICU_IDLE\n\r");
        }
    }

#endif

    AppUtils_printf("All tests have passed\n\r");
#if (STD_ON == ICU_DE_INIT_API)

    Icu_DeInit();

#endif

    AppUtils_TimerDeinit();
}

uint8 MainFunc_Execution;

int main(void)
{
    IcuApp_Startup();

    Icu_App_PlatformInit();

    Icu_InterruptConfig();

    Icu_App_Pwm_Init();

    AppUtils_printf("IcuApp: Sample Application - STARTS !!!\n\r ");

    IcuApp_mainTest();
    return 0;
}

#if (defined CLANG) || (defined DIAB)
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
