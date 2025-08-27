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
 *  \file       trace.c
 *
 *  \brief      Trace implementation.
 *
 *              This abstracts and implements the definitions for
 *              user side traces statements and also details
 *              of variable traces supported in existing
 *              implementation.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "trace.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief      Function to log the trace with zero parameters and just
 *              information string.
 *  \param      mask type of traces.
 *  \param      classType One of three classes where this trace need
 *              to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 */
void GT_trace0(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with one additional parameter
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param The additional parameter which needs to be logged.
 */
void GT_trace1(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString, param0);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString, param0);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with two additional parameters
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 */
void GT_trace2(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString, param0, param1);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString, param0, param1);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with three parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 */
void GT_trace3(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString, param0, param1, param2);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString, param0, param1, param2);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with four parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 */
void GT_trace4(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with five parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 *  \param      param4 The fifth parameter which needs to be logged.
 */
void GT_trace5(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3, uint32 param4)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3, param4);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3, param4);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with six parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 *  \param      param4 The fifth parameter which needs to be logged.
 *  \param      param5 The sixth parameter which needs to be logged.
 */
void GT_trace6(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3, param4, param5);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3, param4, param5);
            }
        }
    }
}

/**
 *  \brief      Function to log the trace with seven parameters.
 *  \param      mask type of traces
 *  \param      classType One of three classes where this trace
 *              need to be enabed.
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      The debug string.
 *  \param      param0 The first parameter which needs to be logged.
 *  \param      param1 The second parameter which needs to be logged.
 *  \param      param2 The third parameter which needs to be logged.
 *  \param      param3 The fourth parameter which needs to be logged.
 *  \param      param4 The fifth parameter which needs to be logged.
 *  \param      param5 The sixth parameter which needs to be logged.
 *  \param      param6 The sixth parameter which needs to be logged.
 */
void GT_trace7(uint32 maskType, GT_TraceClass classType, char *fileName, sint32 lineNum, const char *infoString,
               uint32 param0, uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6)
{
    /* Check if trace is enabled. */
    if (((maskType & GT_TRACESTATE_MASK) >> GT_TRACESTATE_SHIFT) == GT_TraceState_Enable)
    {
        if ((classType == GT_ENTER) || (classType == GT_LEAVE))
        {
            if ((maskType & GT_TRACEENTER_MASK) == GT_TraceEnter_Enable)
            {
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3, param4, param5, param6);
            }
        }
        else
        {
            /* Check if specified class is enabled. */
            if ((maskType & GT_TRACECLASS_MASK) >= classType)
            {
                /* Print if specified class is greater than or equal to class
                 * for this specific print.
                 */
                if (!((classType == GT_INFO) || (classType == GT_INFO1)))
                {
                    AppUtils_printf("%s @ Line %d: ", fileName, lineNum);
                }
                AppUtils_printf((const char *)infoString, param0, param1, param2, param3, param4, param5, param6);
            }
        }
    }
}

/**
 *  \brief      Function to report the vps failure and log the trace. This
 *              is mostly the fatal error and system can not recover without
 *              module restart.
 *  \param      mask        Indicates whether SetFailure is enabled.
 *  \param      func        Name of the function where this oc.cured
 *  \param      fileName    Where the condition has occured.
 *  \param      lineNum     Line number of the current file where this failure
 *                          has occured.
 *  \param      status      What was the code we got/set for this failure
 *  \param      msg         Any additional information which can be useful for
 *                          deciphering the error condition.
 */
void GT_failureReasonSet(sint32 enableMask, char *func, char *fileName, sint32 lineNum, uint32 status, char *msg)
{
    if ((((uint32)enableMask & GT_TRACESETFAILURE_MASK) >> GT_TRACESETFAILURE_SHIFT) == GT_TraceState_Enable)
    {
        AppUtils_printf("*** %s: %s\tError [0x%x] at Line no: %d in file %s\n", func, msg, status, lineNum, fileName);
    }
}
