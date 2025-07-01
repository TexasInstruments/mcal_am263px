/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     AdcApp.h
 *
 *  \brief    ADC example header file
 *
 */
#ifndef ADC_APP_H_
#define ADC_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Adc_Priv.h"

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "ADC_APP"

/* Default loop count. */
#define ADC_APP_LOOP_COUNT (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief ADC application test parameters.
 *  The test case execution happens based on values of this structure
 */
typedef struct
{
    char                 *testDescStr;
    /**< Test description. */
    uint32                loopCount;
    /**< Number of iteration to run transmit. */
    uint32                printEnable;
    /**< Enable Prints. */
    const Adc_ConfigType *adcConfig;
    /**< ADC configuration */
    uint32                testId;
    /**< Test ID for print purpose. This is initialized in the code */
} AdcApp_TestParams;

/**
 *  \brief Test application data structure.
 */
typedef struct
{
    AdcApp_TestParams testPrms;
    /**< Current test parameters. */
    uint32            traceMask;
    /**< Masks for the debug prints. */
} AdcApp_Obj;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
#if (STD_ON == ADC_READ_TEMPERATURE_API)
void AdcTempTest(AdcApp_Obj *appObj, Adc_GroupType Group);
#endif
extern void AdcApp_printChannelResult(uint32 grpIdx, const Adc_GroupConfigType *grpCfg, const AdcApp_Obj *appObj);

/* ========================================================================== */
/*                           Macros related to Application.                   */
/* ========================================================================== */

/* Performance loop count. */
#define ADC_APP_PERF_LOOP_COUNT (100U)

/** \brief Maximum stream samples per channel to test */
#define ADC_APP_MAX_STREAM_SAMPLES (1000U)

/** \brief Each group buffer size in samples */
#define ADC_APP_BUF_SIZE_WORD (ADC_APP_MAX_STREAM_SAMPLES * ADC_NUM_CHANNEL)

/** \brief Default stream samples per channel to test */
#define ADC_APP_DEFAULT_STREAM_SAMPLES (4U)

/** \brief Maximum read samples per channel to store read for each cycle */
#define ADC_APP_MAX_READ_SAMPLES (ADC_APP_DEFAULT_STREAM_SAMPLES * ADC_APP_PERF_LOOP_COUNT)

/** \brief Each group read buffer size in samples */
#define ADC_APP_READ_BUF_SIZE_WORD (ADC_APP_MAX_READ_SAMPLES * ADC_NUM_CHANNEL)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ADC_APP_H_ */
