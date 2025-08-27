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

/*!
 *  @file       trace.h
 *
 *  @brief      Kernel Trace enabling/disabling/application interface.
 *
 *              This will have the definitions for kernel side traces
 *              statements and also details of variable traces
 *              supported in existing implementation.
 *
 *  @date       09-02-2009
 *
 *  @internal   09-02-2009, Harshit Srivastava, Revision 0001:
 *              [1] Original version. Inspired from CE trace.
 *              07-04-2009, Mugdha Kamoolkar, Revision 0002:
 *              [1] Implemented trace.
 *              09-04-2009, Mugdha Kamoolkar, Revision 0003:
 *              [1] Updated non enter-leave trace to only print given format.
 *              15-04-2009, Mugdha Kamoolkar, Revision 0004:
 *              [1] Moved to outside knl to make generic.
 *              15-07-2009, Sivaraj R, Revision 0005:
 *              [1] Modified for VPS driver.
 *              11-07-2015, Sivaraj R, Revision 0006:
 *              [1] Modified for MCAL driver.
 */

#ifndef TRACE_H_
#define TRACE_H_

#include "app_utils.h"

#if defined(USE_STD_ASSERT)
#include "assert.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  @def    GT_TRACESTATE_MASK
 *  @brief  Trace state mask
 */
#define GT_TRACESTATE_MASK (0x0000000FU)

/*!
 *  @def    GT_TRACESTATE_SHIFT
 *  @brief  Bit shift for trace state
 */
#define GT_TRACESTATE_SHIFT (0U)

/*!
 *  @def    GT_TRACEENTER_MASK
 *  @brief  Trace enter mask
 */
#define GT_TRACEENTER_MASK (0x000000F0U)

/*!
 *  @def    GT_TRACEENTER_SHIFT
 *  @brief  Bit shift for trace enter
 */
#define GT_TRACEENTER_SHIFT (4U)

/*!
 *  @def    GT_TRACESETFAILURE_MASK
 *  @brief  Trace Set Failure Reason mask
 */
#define GT_TRACESETFAILURE_MASK (0x00000F00U)

/*!
 *  @def    GT_TRACESETFAILURE_SHIFT
 *  @brief  Bit shift for trace Set Failure Reason
 */
#define GT_TRACESETFAILURE_SHIFT (8U)

/*!
 *  @def    GT_TRACECLASS_MASK
 *  @brief  GT class mask
 */
#define GT_TRACECLASS_MASK (0x000F0000U)

/*!
 *  @def    GT_TRACECLASS_SHIFT
 *  @brief  Bit shift for GT class mask
 */
#define GT_TRACECLASS_SHIFT (16U)

/*!
 *  @brief  Default Mask to use with GT_assert
 */
#define GT_DEFAULT_MASK (GT_ERR | GT_TraceState_Enable)

/** \brief Log enable for example application. */
#define McalAppTrace (GT_INFO | GT_TraceState_Enable)

/*!
 *  @brief   Enumerates the types of states of trace (enable/disable)
 */
typedef enum
{
    GT_TraceState_Disable = 0x00000000U,
    /*!< Disable trace */
    GT_TraceState_Enable = 0x00000001U,
    /*!< Enable trace */
    GT_TraceState_EndValue = 0x00000002U
    /*!< End delimiter indicating start of invalid
     *values for this enum */
} GT_TraceState;

/*!
 *  @brief   Enumerates the states of enter/leave trace (enable/disable)
 */
typedef enum
{
    GT_TraceEnter_Disable = 0x00000000U,
    /*!< Disable GT_ENTER trace prints */
    GT_TraceEnter_Enable = 0x00000010U,
    /*!< Enable GT_ENTER trace prints */
    GT_TraceEnter_EndValue = 0x00000020U
    /*!< End delimiter indicating start of invalid
     *values for this enum */
} GT_TraceEnter;

/*!
 *  @brief   Enumerates the states of SetFailureReason trace (enable/disable)
 */
typedef enum
{
    GT_TraceSetFailure_Disable = 0x00000000U,
    /*!< Disable Set Failure trace prints */
    GT_TraceSetFailure_Enable = 0x00000100U,
    /*!< Enable Set Failure trace prints */
    GT_TraceSetFailure_EndValue = 0x00000200U
    /*!< End delimiter indicating start of invalid
     *values for this enum */
} GT_TraceSetFailure;

/*!
 *  @brief   Enumerates the types of trace classes
 */
typedef enum
{
    GT_ERR = 0x00010000U,
    /*!< Class 1 trace: Used for errors/warnings */
    GT_CRIT = 0x00020000U,
    /*!< Class 2 trace: Used for critical information */
    GT_INFO = 0x00030000U,
    /*!< Class 3 trace: Used for additional information */
    GT_INFO1 = 0x00040000U,
    /*!< Class 4 trace: Used for additional information (sub level 1) */
    GT_DEBUG = 0x00050000U,
    /*!< Class 5 trace: Used for block level information */
    GT_ENTER = 0x00060000U,
    /*!< Indicates a function entry class of trace */
    GT_LEAVE = 0x00070000U
    /*!< Indicates a function leave class of trace */
} GT_TraceClass;

static inline void GT_assertLocal(uint32 enableMask, uint32 condition, char *str, char *fileName, sint32 lineNum);

#define GT_assert(x, y) (GT_assertLocal((uint32)(x), (uint32)(y), (char *)#y, (char *)__FILE__, (sint32)__LINE__))

static inline void GT_assertLocal(uint32 enableMask, uint32 condition, char *str, char *fileName, sint32 lineNum)
{
#if defined(ASSERT_ENABLE)
    if ((!(condition)) != 0)
    {
        AppUtils_printf(" Assertion @ Line: %d in %s: %s : failed !!!\n", lineNum, fileName, str);
#if defined(USE_STD_ASSERT)
        assert((!(condition)) != 0);
#else
        while (TRUE)
        {
            AppUtils_delay((uint32)10U);
        }
#endif /* #if defined(USE_STD_ASSERT) */
    }
#endif /* if defined(ASSERT_ENABLE) */

    return;
}

#if defined(TRACE_ENABLE)

/* Function to report the vps failure and log the trace. */
void GT_failureReasonSet(sint32 enableMask, char *func, char *fileName, sint32 lineNum, uint32 status, char *msg);
#define GT_setFailureReason(maskType, classType, func, status, msg) \
    (GT_failureReasonSet((maskType), (char *)(func), (char *)__FILE__, (sint32)__LINE__, (status), (char *)(msg)))

#else /* if defined (TRACE_ENABLE) */

#define GT_setFailureReason(maskType, classType, func, status, msg) \
    do                                                              \
    {                                                               \
        if (maskType)                                               \
        {                                                           \
        }                                                           \
        if (classType)                                              \
        {                                                           \
        }                                                           \
        if (status)                                                 \
        {                                                           \
        }                                                           \
        if ((uint32)(msg))                                          \
        {                                                           \
        }                                                           \
    } while (FALSE)

#endif /* if defined (TRACE_ENABLE) */

/* Log the trace with zero parameters and information string. */
void GT_trace0(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString);

/* Function to log the trace with one additional parameter */
void GT_trace1(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0);

/* Function to log the trace with two additional parameters */
void GT_trace2(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1);

/* Function to log the trace with three parameters. */
void GT_trace3(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2);

/* Function to log the trace with four parameters. */
void GT_trace4(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3);

/* Function to log the trace with five parameters. */
void GT_trace5(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3, uint32 param4);

/* Function to log the trace with six parameters. */
void GT_trace6(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5);

/* Function to log the trace with seven parameters. */
void GT_trace7(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6);

#if defined(TRACE_ENABLE)

#define GT_0trace(maskType, classType, infoString) \
    (GT_trace0((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString)))

#define GT_1trace(maskType, classType, infoString, param0) \
    (GT_trace1((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString), (uint32)(param0)))

#define GT_2trace(maskType, classType, infoString, param0, param1)                                                  \
    (GT_trace2((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString), (uint32)(param0), \
               (uint32)(param1)))

#define GT_3trace(maskType, classType, infoString, param0, param1, param2)                                          \
    (GT_trace3((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString), (uint32)(param0), \
               (uint32)(param1), (uint32)(param2)))

#define GT_4trace(maskType, classType, infoString, param0, param1, param2, param3)                                  \
    (GT_trace4((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString), (uint32)(param0), \
               (uint32)(param1), (uint32)(param2), (uint32)(param3)))

#define GT_5trace(maskType, classType, infoString, param0, param1, param2, param3, param4)                          \
    (GT_trace5((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString), (uint32)(param0), \
               (uint32)(param1), (uint32)(param2), (uint32)(param3), (uint32)(param4)))

#define GT_6trace(maskType, classType, infoString, param0, param1, param2, param3, param4, param5)                  \
    (GT_trace6((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString), (uint32)(param0), \
               (uint32)(param1), (uint32)(param2), (uint32)(param3), (uint32)(param4), (uint32)(param5)))

#define GT_7trace(maskType, classType, infoString, param0, param1, param2, param3, param4, param5, param6)          \
    (GT_trace7((maskType), (classType), (char *)__FILE__, (sint32)__LINE__, (char *)(infoString), (uint32)(param0), \
               (uint32)(param1), (uint32)(param2), (uint32)(param3), (uint32)(param4), (uint32)(param5),            \
               (uint32)(param6)))

#else /* if defined (TRACE_ENABLE) */

#define GT_0trace(maskType, classType, infoString)
#define GT_1trace(maskType, classType, infoString, param0)
#define GT_2trace(maskType, classType, infoString, param0, param1)
#define GT_3trace(maskType, classType, infoString, param0, param1, param2)
#define GT_4trace(maskType, classType, infoString, param0, param1, param2, param3)
#define GT_5trace(maskType, classType, infoString, param0, param1, param2, param3, param4)
#define GT_6trace(maskType, classType, infoString, param0, param1, param2, param3, param4, param5)
#define GT_7trace(maskType, classType, infoString, param0, param1, param2, param3, param4, param5, param6)

#endif /* if defined (TRACE_ENABLE) */

#ifdef __cplusplus
}
#endif

#endif /* ifndef TRACE_H_ */
