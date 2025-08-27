/*
 *
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Adc.c
 *
 *  \brief    This file contains ADC MCAL driver
 *
 */

/* Common Design ID's */
/*
*Design: MCAL-14837, MCAL-21530,MCAL-14856, MCAL-14672, MCAL-14434, MCAL-14627, MCAL-14630

*/
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "Adc.h"
#include "Adc_Priv.h"
#include "Adc_Platform.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* AUTOSAR version information check has to match definition in header file */
#if ((ADC_AR_RELEASE_MAJOR_VERSION != (4U)) || (ADC_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (ADC_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Adc: AUTOSAR Version Numbers of Adc are different!!"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((ADC_SW_MAJOR_VERSION != (10U)) || (ADC_SW_MINOR_VERSION != (1U)))
#error "Adc: Software Version Numbers are inconsistent!!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void Adc_EnableHardwareTrigger_startDet(Adc_GroupObjType *groupObj);

static void Adc_EnableHardwareTrigger_detCheck(Adc_GroupObjType *groupObj);

static void Adc_StartGroupConversion_DetCheck(Std_ReturnType retVal);

static boolean Adc_DeInit_StatusChk(const Adc_GroupObjType *groupObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define ADC_START_SEC_VAR_INIT_32
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

/** \brief ADC driver init status */
static volatile VAR(uint32, ADC_VAR_CLEARED) Adc_DrvIsInit = (uint32)ADC_FALSE;
#define ADC_STOP_SEC_VAR_INIT_32
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"
/** \brief ADC driver object */
VAR(Adc_DriverObjType, ADC_VAR_CLEARED) Adc_DrvObj;
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ADC_START_SEC_CODE
/*LDRA_INSPECTED 338 S: MISRAC_2012_20.1
 * "Reason - This is the format to use for specifying memory sections." */
/*LDRA_INSPECTED 243 S: MISRAC_2012_D4.10
 * "Reason - This is required here for specifying memory sections." */
#include "Adc_MemMap.h"

/*
 *Design: MCAL-15321, MCAL-14655, MCAL-14656, MCAL-14657, MCAL-14659, MCAL-14660, MCAL-14661,
 *MCAL-14662, MCAL-14663, MCAL-14863, MCAL-14867, MCAL-14871, MCAL-14872, MCAL-14873
 */
/*LDRA_INSPECTED 61 D : MISRAC_2012_R.8.8
 * "Reason - This is external API and cannot be static" */
FUNC(void, ADC_CODE) Adc_Init(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_PBCFG) CfgPtr)
{
    uint8 hwUnitIdx;
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/
#endif
    /*LDRA_INSPECTED 104 D: MISRA-C:2012 D.4.8
     * "Reason - Tool Issue - ConfigPtr pointer
     *  is dereferenced in this function" */
    const Adc_ConfigType *ConfigPtr = (Adc_ConfigType *)NULL_PTR;
    Adc_HwUnitObjType    *hwObj;

#if (STD_ON == ADC_VARIANT_PRE_COMPILE)
    ConfigPtr = &ADC_INIT_CONFIG_PC;
#endif /* (STD_ON == ADC_PRE_COMPILE_VARIANT) */

#if (STD_ON == ADC_VARIANT_POST_BUILD)
    ConfigPtr = CfgPtr;
#endif /* (STD_ON == ADC_VARIANT_POST_BUILD) */

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) != Adc_DrvIsInit) /* To check whether ADC driver is initialised*/
    {
        Adc_reportDetError(ADC_SID_INIT, ADC_E_ALREADY_INITIALIZED); /*Report DET if ADC driver is already initialised*/
        Avoid_nesting_flag = 1U;
    }
#if (STD_ON == ADC_VARIANT_PRE_COMPILE)
    if ((Avoid_nesting_flag == 0U) && (NULL_PTR != CfgPtr))
#elif (STD_ON == ADC_VARIANT_POST_BUILD)
    if ((Avoid_nesting_flag == 0U) && (NULL_PTR == CfgPtr))
#endif /* (STD_ON == ADC_VARIANT_PRE_COMPILE) */
    {
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_POINTER); /* Report DET if CfgPtr is not NULL in precompile
                                                                  or NULL in post build*/
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) &&
        ((ConfigPtr->maxGroup >= (ADC_MAX_GROUP + 1U)) || (ConfigPtr->maxHwUnit >= (ADC_MAX_HW_UNIT + 1U))))
    {
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG); /*Report DET if ConfigPtr has parameter values which
                                                                 exceeds max values*/
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (((uint32)ADC_TRUE) != Adc_checkHwUnitObj(ConfigPtr)))
    {
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG); /* Report DET if HwUnitId exceeds max
                                                                 hw value and hwunit not found*/
        Avoid_nesting_flag = 1U;
    }
    if (Avoid_nesting_flag == 0U)
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        /*LDRA_INSPECTED 72 D: MISRA-C:2012 R.13.2
         * "Reason - There is no side effect in this expression */
        Adc_resetDrvObj(&Adc_DrvObj);

        /* Copy the configuration */
        /*LDRA_INSPECTED 128 D: MISRA-C:2012 D.4.14
         * "Reason - Adc_DrvObj cannot be NULL here as
         *  as it is ensured by DET error check before calling this func */
        Adc_copyConfig(&Adc_DrvObj, ConfigPtr);

        Adc_getChannelMuxParams(&Adc_DrvObj);
        /* Init HW once all config is copied */
        for (hwUnitIdx = 0U; hwUnitIdx < ConfigPtr->maxHwUnit; hwUnitIdx++)
        {
            /*LDRA_INSPECTED 128 D: MISRA-C:2012 D.4.14
             * "Reason - Adc_DrvObj cannot be NULL here as
             *  as it is ensured by DET error check before calling this func */
            hwObj = &(Adc_DrvObj.hwUnitObj[hwUnitIdx]);
            Adc_hwUnitInit(hwObj);
        }
        Adc_performHwInit();
        /* Initialize driver status and object */
        Adc_DrvIsInit = (uint32)ADC_TRUE;
    }

    return;
}

#if (STD_ON == ADC_DEINIT_API)
/*
 * Design: MCAL-15323, MCAL-14664, MCAL-14665, MCAL-14667, MCAL-14668, MCAL-14669, MCAL-14670,
 * MCAL-14863
 */
/*LDRA_INSPECTED 61 D : MISRAC_2012_R.8.8
 * "Reason - This is external APIs " */
FUNC(void, ADC_CODE) Adc_DeInit(void)
{
    uint8  hwUnitIdx;
    uint32 isError = (uint32)ADC_FALSE;
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    uint8             grpIdx;
    Adc_GroupObjType *groupObj;
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_DEINIT, ADC_E_UNINIT); /* Report DET if Driver is already uninitialised*/
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();
#if (STD_ON == ADC_DEV_ERROR_DETECT)
        for (grpIdx = 0U; grpIdx < Adc_DrvObj.maxGroup; grpIdx++)
        {
            groupObj = &Adc_DrvObj.groupObj[grpIdx];
            isError  = Adc_DeInit_StatusChk(groupObj);

            if (((uint32)ADC_TRUE) == isError)
            {
                Adc_reportDetRuntimeError(ADC_SID_DEINIT,
                                          ADC_E_BUSY); /* Report DET is uninit API is called when the driver is busy*/
            }
        }
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

        if (((uint32)ADC_FALSE) == isError)
        {
            Adc_DrvIsInit = (uint32)ADC_FALSE;
            /* Deinit the hardware modules */
            for (hwUnitIdx = 0U; hwUnitIdx < Adc_DrvObj.maxHwUnit; hwUnitIdx++)
            {
                Adc_hwUnitDeInit(&Adc_DrvObj.hwUnitObj[hwUnitIdx]);
            }
            /*LDRA_INSPECTED 72 D: MISRA-C:2012 R.13.2
             * "Reason - There is no side effect in this expression */
            Adc_resetDrvObj(&Adc_DrvObj);
        }
        Adc_performHwDeInit();
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }

    return;
}
#endif /* #if (STD_ON == ADC_DEINIT_API) */

/* Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue */
static boolean Adc_DeInit_StatusChk(const Adc_GroupObjType *groupObj)
{
    boolean isError = ADC_FALSE;
    if ((ADC_BUSY == groupObj->groupStatus) || (ADC_COMPLETED == groupObj->groupStatus))
    {
        /* These states indicate, that the group is still converting */
        isError = ADC_TRUE;
    }
    else if (ADC_STREAM_COMPLETED == groupObj->groupStatus)
    {
        /* Check if this group has to be stopped explicitly */
        if (ADC_TRUE == groupObj->isExplicitStopMode)
        {
            /* Group has to be stopped explicitly. State
             * ADC_STREAM_COMPLETED means, that group is still
             * converting */
            isError = ADC_TRUE;
        }
    }
    else
    {
        /* This group is not converting: continue */
    }
    return (isError);
}

/*
 * Design: MCAL-15322, MCAL-14673, MCAL-14674, MCAL-14675, MCAL-14676, MCAL-14677, MCAL-14678,
 * MCAL-14679, MCAL-14869
 */
/*LDRA_INSPECTED 61 D : MISRAC_2012_R.8.8
 * "Reason - These are interface API's " */
FUNC(Std_ReturnType, ADC_CODE)
Adc_SetupResultBuffer(Adc_GroupType Group, const Adc_ValueGroupType *DataBufferPtr)
{
    Std_ReturnType    retVal = (Std_ReturnType)E_OK;
    Adc_GroupObjType *groupObj;
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/
#endif

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_SETUP_RESULT_BUFFER,
                           ADC_E_UNINIT); /* Report DET if driver not initialised to set result buffer*/
        retVal             = (Std_ReturnType)E_NOT_OK;
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (Group >= Adc_DrvObj.maxGroup))
    {
        Adc_reportDetError(ADC_SID_SETUP_RESULT_BUFFER,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
        retVal             = (Std_ReturnType)E_NOT_OK;
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (NULL_PTR == DataBufferPtr))
    {
        Adc_reportDetError(ADC_SID_SETUP_RESULT_BUFFER,
                           ADC_E_PARAM_POINTER); /* Report DET if databuffer pointer is NULL */
        retVal             = (Std_ReturnType)E_NOT_OK;
        Avoid_nesting_flag = 1U;
    }
    if (Avoid_nesting_flag == 0U)
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

        /* Check group status */
        if (ADC_IDLE != groupObj->groupStatus)
        {
            Adc_reportDetRuntimeError(ADC_SID_SETUP_RESULT_BUFFER,
                                      ADC_E_BUSY); /* Report Runtime DET if driver is busy when user
                                                      tries to set result buffer*/
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            groupObj->resultBufPtr = DataBufferPtr;
        }

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}

/*
 * Design: MCAL-15324, MCAL-14680, MCAL-14681, MCAL-14682, MCAL-14683, MCAL-14684, MCAL-14685,
 * MCAL-14686, MCAL-14687, MCAL-14688, MCAL-14689, MCAL-14870
 */
FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus(Adc_GroupType Group)
{
    Adc_StatusType    groupStatus = ADC_IDLE;
    Adc_GroupObjType *groupObj    = (Adc_GroupObjType *)NULL_PTR;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_GET_GROUP_STATUS,
                           ADC_E_UNINIT); /* Report DET if getgroupstatus called without initialising driver*/
    }
    else if (Group >= Adc_DrvObj.maxGroup)
    {
        Adc_reportDetError(ADC_SID_GET_GROUP_STATUS,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

        groupStatus = groupObj->groupStatus;

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }

    return (groupStatus);
}

/*
 * Design: MCAL-14690, MCAL-15325, MCAL-14691, MCAL-14692, MCAL-14693, MCAL-14694, MCAL-14695,
 * MCAL-14696, MCAL-14697, MCAL-14698, MCAL-14699, MCAL-14700
 */
FUNC(Adc_StreamNumSampleType, ADC_CODE)
Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr)
{
    Adc_StreamNumSampleType numSamples = 0U;
    Std_ReturnType          retVal     = (Std_ReturnType)E_OK;

    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if ((((uint32)ADC_TRUE)) == Adc_DrvIsInit)
    {
#endif
        retVal = Adc_getStreamPtrCheckDetError(Group, PtrToSamplePtr);
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    }
    else
    {
        if (NULL_PTR != PtrToSamplePtr)
        {
            *PtrToSamplePtr = (Adc_ValueGroupType *)NULL_PTR;
        }
        retVal = (Std_ReturnType)E_NOT_OK;
        /* Report DET if driver not initialised before calling Adc_getStreamPtrCheckDetError */
        Adc_reportDetError(ADC_SID_GET_STREAM_LAST_POINTER, ADC_E_UNINIT);
    }
#endif

    if (((Std_ReturnType)E_OK) == retVal)
    {
        numSamples = Adc_GetStreamLastPointerinternal(Group, PtrToSamplePtr);
    }

    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();

    return (numSamples);
}

#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
/*
 * Design: MCAL-15326, MCAL-14701, MCAL-14702, MCAL-14703, MCAL-14704, MCAL-14705, MCAL-14706,
 * MCAL-14707, MCAL-14708, MCAL-14709, MCAL-14710, MCAL-14711, MCAL-14712, MCAL-14713, MCAL-14714,
 * MCAL-14715
 */
FUNC(void, ADC_CODE) Adc_StartGroupConversion(Adc_GroupType Group)
{
    Std_ReturnType    retVal;
    Adc_GroupObjType *groupObj;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_START_GROUP_CONVERSION, ADC_E_UNINIT); /* Report DET if driver not initialised before
                                                                             calling Adc_StartGroupConversion */
    }
    else if (Group >= Adc_DrvObj.maxGroup)
    {
        Adc_reportDetError(ADC_SID_START_GROUP_CONVERSION,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

#if (STD_ON == ADC_DEV_ERROR_DETECT)
        if (NULL_PTR == groupObj->resultBufPtr)
        {
            Adc_reportDetError(ADC_SID_START_GROUP_CONVERSION,
                               ADC_E_BUFFER_UNINIT); /* Report DET if result buffer is NULL when
                                                        Adc_EnableHardwareTrigger is called*/
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (ADC_TRIGG_SRC_HW == groupObj->groupCfg.triggSrc))
        {
            Adc_reportDetError(ADC_SID_START_GROUP_CONVERSION,
                               ADC_E_WRONG_TRIGG_SRC); /* Report DET if trigger source is wrong*/
            Avoid_nesting_flag = 1U;
        }
        if (Avoid_nesting_flag == 0U)
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        {
            /* Call the start group API */
            retVal = Adc_startGroup(groupObj);
            Adc_StartGroupConversion_DetCheck(retVal);
        }

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();

        (void)Adc_groupConversionDoneHandler();
    }

    return;
}

/* Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue */
static void Adc_StartGroupConversion_DetCheck(Std_ReturnType retVal)
{
    if (((Std_ReturnType)E_NOT_OK) == retVal)
    {
        Adc_reportDetRuntimeError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
    }
}

/*
 * Design: MCAL-15327, MCAL-14716, MCAL-14717, MCAL-14718, MCAL-14719, MCAL-14720, MCAL-14721,
 * MCAL-14722, MCAL-14723, MCAL-14724, MCAL-14725, MCAL-14726, MCAL-14727, MCAL-14865, MCAL-14866
 */
FUNC(void, ADC_CODE) Adc_StopGroupConversion(Adc_GroupType Group)
{
    Adc_GroupObjType *groupObj;
    Std_ReturnType    retVal = (Std_ReturnType)E_OK;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_STOP_GROUP_CONVERSION, ADC_E_UNINIT); /* Report DET if driver not initialised before
                                                                            calling Adc_StopGroupConversion */
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (Group >= Adc_DrvObj.maxGroup))
    {
        Adc_reportDetError(ADC_SID_STOP_GROUP_CONVERSION,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
        Avoid_nesting_flag = 1U;
    }
    if (Avoid_nesting_flag == 0U)
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

#if (STD_ON == ADC_DEV_ERROR_DETECT)
        if (ADC_TRIGG_SRC_HW == groupObj->groupCfg.triggSrc)
        {
            Adc_reportDetError(ADC_SID_STOP_GROUP_CONVERSION,
                               ADC_E_WRONG_TRIGG_SRC); /* Report DET if trigger source is wrong*/
            retVal = (Std_ReturnType)E_NOT_OK;
        }
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        if (retVal == (Std_ReturnType)E_OK)
        {
            if (ADC_IDLE == groupObj->groupStatus)
            {
                Adc_reportDetRuntimeError(ADC_SID_STOP_GROUP_CONVERSION,
                                          ADC_E_IDLE); /*Report DET if required group to stop
                                                          conversion is already idle */
            }
            else
            {
                /* Call the stop group API */
                Adc_stopGroup(groupObj, ADC_TRUE);
            }
        }

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }

    return;
}
#endif /* #if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) */

#if (STD_ON == ADC_READ_GROUP_API)
/*
 * Design: MCAL-15328, MCAL-14728, MCAL-14729, MCAL-14730, MCAL-14731, MCAL-14732, MCAL-14733,
 * MCAL-14734, MCAL-14735, MCAL-14736, MCAL-14737, MCAL-14864
 */
FUNC(Std_ReturnType, ADC_CODE) Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr)
{
    Std_ReturnType    retVal = (Std_ReturnType)E_OK;
    Adc_GroupObjType *groupObj;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_READ_GROUP,
                           ADC_E_UNINIT); /* Report DET if driver not initialised before calling Adc_ReadGroup */
        retVal             = (Std_ReturnType)E_NOT_OK;
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (Group >= Adc_DrvObj.maxGroup))
    {
        Adc_reportDetError(ADC_SID_READ_GROUP,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
        retVal             = (Std_ReturnType)E_NOT_OK;
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (NULL_PTR == DataBufferPtr))
    {
        /* Note: This error return is not mentioned in spec */
        Adc_reportDetError(ADC_SID_READ_GROUP, ADC_E_PARAM_POINTER); /* Report DET if databuffer pointer is NULL */
        retVal             = (Std_ReturnType)E_NOT_OK;
        Avoid_nesting_flag = 1U;
    }
    if (Avoid_nesting_flag == 0U)
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

        if (ADC_IDLE == groupObj->groupStatus)
        {
            Adc_reportDetRuntimeError(ADC_SID_READ_GROUP, ADC_E_IDLE); /*Report DET if required group to read is idle */
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* Check the status */
            if (ADC_BUSY == groupObj->groupStatus)
            {
                retVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                Adc_FillDataBufferPtr(DataBufferPtr, groupObj);
            }
        }

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}
#endif /* #if (STD_ON == ADC_READ_GROUP_API) */

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY_API)
/*
 * Design: MCAL-15329, MCAL-14740, MCAL-14741, MCAL-14742, MCAL-14744, MCAL-14749, MCAL-14861,
 * MCAL-14861, MCAL-15354, MCAL-15355, MCAL-15356, MCAL-15357, MCAL-15358, MCAL-15359, MCAL-15360
 */
FUNC(void, ADC_CODE) Adc_EnableGroupNotification(Adc_GroupType Group)
{
    Adc_GroupObjType *groupObj;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_ENABLE_GROUP_NOTIFICATION,
                           ADC_E_UNINIT); /* Report DET if driver not initialised before calling
                                             Adc_EnableGroupNotification */
    }
    else if (Group >= Adc_DrvObj.maxGroup)
    {
        Adc_reportDetError(ADC_SID_ENABLE_GROUP_NOTIFICATION,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

#if (STD_ON == ADC_DEV_ERROR_DETECT)
        /* Check group status */
        if ((Adc_GroupEndNotifyType)NULL_PTR == groupObj->groupCfg.Adc_GroupEndNotification)
        {
            Adc_reportDetError(ADC_SID_ENABLE_GROUP_NOTIFICATION,
                               ADC_E_NOTIF_CAPABILITY); /* Report DET if Adc_GroupEndNotification is NULL*/
        }
        else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        {
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

            groupObj->isNotifyOn = (uint32)ADC_TRUE;

            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
        }
    }

    return;
}

/*
 * Design: MCAL-15330, MCAL-14752, MCAL-14753, MCAL-14754, MCAL-14755, MCAL-14756
 */
FUNC(void, ADC_CODE) Adc_DisableGroupNotification(Adc_GroupType Group)
{
    Adc_GroupObjType *groupObj;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_DISABLE_GROUP_NOTIFICATION,
                           ADC_E_UNINIT); /* Report DET if driver not initialised before calling
                                             Adc_DisableGroupNotification */
    }
    else if (Group >= Adc_DrvObj.maxGroup)
    {
        Adc_reportDetError(ADC_SID_DISABLE_GROUP_NOTIFICATION,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

#if (STD_ON == ADC_DEV_ERROR_DETECT)
        /* Check group status */
        if ((Adc_GroupEndNotifyType)NULL_PTR == groupObj->groupCfg.Adc_GroupEndNotification)
        {
            Adc_reportDetError(ADC_SID_DISABLE_GROUP_NOTIFICATION,
                               ADC_E_NOTIF_CAPABILITY); /* Report DET if Adc_GroupEndNotification is NULL*/
        }
        else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        {
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

            groupObj->isNotifyOn = (uint32)ADC_FALSE;

            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
        }
    }

    return;
}
#endif /* #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY_API) */

#if (STD_ON == ADC_VERSION_INFO_API)
/*
 * Design: MCAL-15331, MCAL-14757, MCAL-14863
 */
FUNC(void, ADC_CODE)
Adc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ADC_APPL_DATA) versioninfo)
{
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        Adc_reportDetError(ADC_SID_GET_VERSION_INFO, ADC_E_PARAM_POINTER); /* Report DET if versioninfo is NULL */
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        versioninfo->vendorID         = ADC_VENDOR_ID;
        versioninfo->moduleID         = ADC_MODULE_ID;
        versioninfo->sw_major_version = (uint8)ADC_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)ADC_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)ADC_SW_PATCH_VERSION;
    }

    return;
}
#endif /* #if (STD_ON == ADC_VERSION_INFO_API) */

#if (ADC_HW_TRIGGER_API == STD_ON)
static void Adc_EnableHardwareTrigger_startDet(Adc_GroupObjType *groupObj)
{
    Std_ReturnType retVal = E_OK;
    /* Call the start group API */
    retVal = Adc_startGroup(groupObj);
    if (((Std_ReturnType)E_NOT_OK) == retVal)
    {
        Adc_reportDetRuntimeError(ADC_SID_ENABLE_HARDWARE_TRIGGER,
                                  ADC_E_BUSY); /* Report DET if required group is already busy*/
    }
}
static void Adc_EnableHardwareTrigger_detCheck(Adc_GroupObjType *groupObj)
{
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (NULL_PTR == groupObj->resultBufPtr)
    {
        Adc_reportDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER,
                           ADC_E_BUFFER_UNINIT); /* Report DET if result buffer is NULL when
                                                    Adc_EnableHardwareTrigger is called*/
    }
    else if (ADC_TRIGG_SRC_SW == groupObj->groupCfg.triggSrc)
    {
        Adc_reportDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER,
                           ADC_E_WRONG_TRIGG_SRC); /* Report DET if trigger source is wrong*/
    }
    else if (ADC_CONV_MODE_CONTINUOUS == groupObj->groupCfg.convMode)
    {
        Adc_reportDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER,
                           ADC_E_WRONG_CONV_MODE); /* Report DET if conversion mode is wrong*/
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        /* Call the start group API */
        Adc_EnableHardwareTrigger_startDet(groupObj);
    }
}

/*
 * Design: MCAL-15332, MCAL-14808, MCAL-14809, MCAL-14811, MCAL-14812, MCAL-14813, MCAL-14815,
 * MCAL-14816, MCAL-14817, MCAL-14818, MCAL-14819, MCAL-14820, MCAL-14821, MCAL-14822, MCAL-14823
 */
FUNC(void, ADC_CODE) Adc_EnableHardwareTrigger(VAR(Adc_GroupType, AUTOMATIC) Group)
{
    Adc_GroupObjType *groupObj;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER,
                           ADC_E_UNINIT); /* Report DET if driver not initialised before calling
                                             Adc_EnableHardwareTrigger */
    }
    else if (Group >= Adc_DrvObj.maxGroup)
    {
        Adc_reportDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

        Adc_EnableHardwareTrigger_detCheck(groupObj);

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }
}

/*
 * Design: MCAL-15333, MCAL-14758, MCAL-14759, MCAL-14760, MCAL-14766, MCAL-14767, MCAL-14768,
 * MCAL-14769, MCAL-14770, MCAL-14771, MCAL-14772, MCAL-14773, MCAL-14774
 */
FUNC(void, ADC_CODE) Adc_DisableHardwareTrigger(VAR(Adc_GroupType, AUTOMATIC) Group)
{
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    uint8 Avoid_nesting_flag = 0U;
#endif
    Adc_GroupObjType *groupObj;
    Std_ReturnType    retVal = E_OK;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        /* Report DET if driver not initialised before calling Adc_DisableHardwareTrigger */
        Adc_reportDetError(ADC_SID_DISABLE_HARDWARE_TRIGGER, ADC_E_UNINIT);
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (Group >= Adc_DrvObj.maxGroup))
    {
        /* Report DET if group provided exceeds maximum groups */
        Adc_reportDetError(ADC_SID_DISABLE_HARDWARE_TRIGGER, ADC_E_PARAM_GROUP);
        Avoid_nesting_flag = 1U;
    }
    if (Avoid_nesting_flag == 0U)
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];

        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

#if (STD_ON == ADC_DEV_ERROR_DETECT)
        if (ADC_TRIGG_SRC_SW == groupObj->groupCfg.triggSrc)
        {
            Adc_reportDetError(ADC_SID_DISABLE_HARDWARE_TRIGGER,
                               ADC_E_WRONG_TRIGG_SRC); /* Report DET if trigger source is wrong*/
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else if (ADC_CONV_MODE_CONTINUOUS == groupObj->groupCfg.convMode)
        {
            Adc_reportDetError(ADC_SID_DISABLE_HARDWARE_TRIGGER,
                               ADC_E_WRONG_CONV_MODE); /* Report DET if conversion mode is wrong*/
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /*No action required */
        }
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        if (retVal == (Std_ReturnType)E_OK)
        {
            if (ADC_IDLE == groupObj->groupStatus)
            {
                Adc_reportDetRuntimeError(ADC_SID_DISABLE_HARDWARE_TRIGGER,
                                          ADC_E_IDLE); /* Report DET if required group to disable hardware is idle */
            }
            else
            {
                /* Call the stop group API */
                Adc_stopGroup(groupObj, ADC_FALSE);
            }
        }

        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }
}
#endif /* (ADC_HW_TRIGGER_API == STD_ON) || defined(__DOXYGEN__) */

/*
 * Design: MCAL-21551
 */
#if (STD_ON == ADC_POLLING_MAINFUNCTION_API)
FUNC(void, ADC_CODE) Adc_PollingMainFunction(void)
{
    Adc_GroupObjType *groupObj;
    VAR(Adc_GroupType, AUTOMATIC) group;

    for (group = 0U; group < Adc_DrvObj.maxGroup; group++)
    {
        /* Get the Group Object. */
        groupObj = &Adc_DrvObj.groupObj[group];

        /* Enter the Critical section. */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_0();

        /* Process the Polling mode. */
        Adc_groupPolling(groupObj);

        /* Exit the Critical section. */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_0();
    }
}
#endif /* #if (STD_ON == ADC_POLLING_MAINFUNCTION_API) */

/*
 * Design: MCAL-15650, MCAL-15649, MCAL-15648
 */
#if (STD_ON == ADC_REGISTER_READBACK_API)
FUNC(Std_ReturnType, ADC_CODE)
Adc_RegisterReadback(Adc_HWUnitType HWUnit, P2VAR(Adc_RegisterReadbackType, AUTOMATIC, ADC_APPL_DATA) RegRbPtr)
{
    Adc_HwUnitObjType *hwUnitObj;
    Std_ReturnType     retVal = ((Std_ReturnType)E_OK);

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if ((uint32)ADC_FALSE == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_REGISTER_READBACK, ADC_E_UNINIT); /* Report DET if driver not initialised before
                                                                        calling Adc_RegisterReadback */
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == RegRbPtr)
    {
        Adc_reportDetError(ADC_SID_REGISTER_READBACK, ADC_E_PARAM_GROUP); /* Report DET if RegRbPtr is NULL pointer*/
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        (void)memset(RegRbPtr, 0, sizeof(Adc_RegisterReadbackType));

        /* HW unit ID may not be the index, so search for matching HW unit */
        hwUnitObj = &Adc_DrvObj.hwUnitObj[HWUnit];

        Adc_HWRegisterReadback(RegRbPtr, hwUnitObj);
    }

    return (retVal);
}
#endif /* #if (STD_ON == ADC_REGISTER_READBACK_API) */

FUNC(uint32, ADC_CODE) Adc_GetReadResultBaseAddress(VAR(Adc_GroupType, AUTOMATIC) Group)
{
    Adc_GroupObjType *groupObj;
    Std_ReturnType    retVal         = ((Std_ReturnType)E_OK);
    uint32            resultBaseAddr = 0U;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        /* Report DET if driver not initialised to set result buffer*/
        Adc_reportDetError(ADC_SID_GET_READ_RESULT_BASE_ADDRESS, ADC_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (Group >= Adc_DrvObj.maxGroup)
    {
        /* Report DET if group provided exceeds maximum groups*/
        Adc_reportDetError(ADC_SID_GET_READ_RESULT_BASE_ADDRESS, ADC_E_PARAM_GROUP);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    if (retVal == E_OK)
    {
        groupObj       = &Adc_DrvObj.groupObj[Group];
        resultBaseAddr = ADC_readResultbaseaddr(groupObj->hwUnitObj->resultBaseAddr, groupObj->socAssigned);
    }

    return resultBaseAddr;
}

FUNC(Std_ReturnType, ADC_CODE) Adc_SetInterruptContinuousMode(VAR(Adc_GroupType, AUTOMATIC) Group)
{
    Adc_GroupObjType *groupObj;
    Std_ReturnType    retVal = ((Std_ReturnType)E_OK);

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        /* Report DET if driver not initialised to set result buffer*/
        Adc_reportDetError(ADC_SID_SET_INTERRUPT_CONTINUOUS_MODE, ADC_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (Group >= Adc_DrvObj.maxGroup)
    {
        /* Report DET if group provided exceeds maximum groups*/
        Adc_reportDetError(ADC_SID_SET_INTERRUPT_CONTINUOUS_MODE, ADC_E_PARAM_GROUP);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    if (retVal == E_OK)
    {
        groupObj = &Adc_DrvObj.groupObj[Group];
        ADC_enableContinuousMode(groupObj->hwUnitObj->baseAddr, groupObj->groupInterruptSrc);
    }

    return (retVal);
}

#if (STD_ON == ADC_READ_TEMPERATURE_API)
/*
 * Design: MCAL-21529
 */
FUNC(void, ADC_CODE) Adc_InitTemperatureRead(void)
{
    Adc_InitTemp();
    return;
}

/*
 * Design: MCAL-21527
 */
FUNC(void, ADC_CODE)
Adc_ReadTemperature(Adc_GroupType Group, uint8 NumAverages, Adc_TempSensValueType *TempValuesPtr)
{
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_READ_TEMPERATURE, ADC_E_UNINIT); /* Report DET if driver not initialised before
                                                                       calling Adc_InitTemperatureRead */
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        Adc_ReadTemp(Group, NumAverages, TempValuesPtr);
    }
}
/**
 * @brief
 * Need to ensure the Adc_StartGroupConversion() and the corresponding wait to complete the
 * conversion is called before this Adc_ReadTemperatureResult API is called.
 */
/*
 * Design: MCAL-21528
 */
FUNC(void, ADC_CODE)
Adc_ReadTemperatureResult(Adc_GroupType Group, Adc_TempSensValueType *TempValuesPtr)
{
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (((uint32)ADC_FALSE) == Adc_DrvIsInit)
    {
        Adc_reportDetError(ADC_SID_READ_TEMPERATURE_RESULT,
                           ADC_E_UNINIT); /* Report DET if driver not initialised before calling
                                             Adc_ReadTemperatureResult */
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        Adc_ReadTempResult(Group, TempValuesPtr);
    }
}
#endif /* #if (STD_ON == ADC_READ_TEMPERATURE_API) */

#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
