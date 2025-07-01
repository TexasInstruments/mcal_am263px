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
 *  \file     Adc_Priv.c
 *
 *  \brief    This file contains ADC MCAL driver internal functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Adc_Cfg.h"
#include "Adc_Temp.h"
#include "Adc.h"
#include "Adc_Priv.h"
#include <string.h>
#include "hw_types.h"
#include "Adc_Platform.h"

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void           Adc_scheduleGroup(Adc_GroupObjType *groupObj);
static Std_ReturnType Adc_startGroupCheckStatus(const Adc_GroupObjType *groupObj);

#if (STD_ON == ADC_DEV_ERROR_DETECT)
static Std_ReturnType Adc_checkGroupCfgRangeParameters(const Adc_GroupConfigType *groupCfg);
static void           Adc_checkChannelParams(const Adc_ChannelConfigType *chCfg);
static Std_ReturnType Adc_checkGroupParameters(const Adc_GroupConfigType *groupCfg, const Adc_ConfigType *cfgPtr);
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/*LDRA_INSPECTED 61 X MR:5.1 Reason : "Based on Autosar Memory Map strategy" */
#define ADC_START_SEC_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S MR:19.1 Reason : "Based on Autosar Memory Map strategy" */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Adc_MemMap.h"
/*! \brief
 * GPADC Param Lut
 * ConfigValue, {ParamValue, CollectSamples, SkipSamples, ChirpBreak, Reserved}, time(10MHz clock)
 */
#if defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM)
Adc_CfgAndParamValuesType Adc_ConfigParamLuTab[ADC_NUM_HW_CHANNEL] = {
    /*! UnBuffConfigVal, BuffConfigVal, ParamVal,         Settling time */
    {0x400U, 0x2U, 0x0000FF7CU, 4080U},           /* #0 Adc_Meas_Ext_Ch1 */
    {0x800U, 0x4U, 0x0000FF7CU, 4080U},           /* #1 Adc_Meas_Ext_Ch2 */
    {0x1000U, 0x8U, 0x0000FF7CU, 4080U},          /* #2 Adc_Meas_Ext_Ch3 */
    {0x2000U, 0x10U, 0x0000FF7CU, 4080U},         /* #3 Adc_Meas_Ext_Ch4 */
    {0x4000U, 0x10000U, 0x0000FF7CU, 4080U},      /* #4 Adc_Meas_Ext_Ch5 */
    {0x8000U, 0x200000U, 0x0000FF7CU, 4080U},     /* #5 Adc_Meas_Ext_Ch6 */
    {0x1000000U, 0x400000U, 0x0000FF7CU, 4080U},  /* #6 Adc_Meas_Ext_Ch7 */
    {0x2000000U, 0x800000U, 0x0000FF7CU, 4080U},  /* #7 Adc_Meas_Ext_Ch8 */
    {0x8000000U, 0x4000000U, 0x0000FF7CU, 4080U}, /* #8 Adc_Meas_Ext_Ch9 */
    {0x40000U, 0x40000U, 0x0000FF7CU, 4080U},     /* #9  Adc_Dig_DSP_Temp_Sensor */
    {0x80000U, 0x80000U, 0x0000FF7CU, 4080U},     /* #10 Adc_Dig_HWA_Temp_Sensor */
    {0x100000U, 0x100000U, 0x0000FF7CU, 4080U},   /* #11 Adc_Dig_HSM_Temp_Sensor */
};
#else
Adc_CfgAndParamValuesType Adc_ConfigParamLuTab[ADC_NUM_HW_CHANNEL] = {
    /*! UnBuffConfigVal, BuffConfigVal, ParamVal,         Settling time */
    {0x400U, 0x2U, 0x0000FF02U, 4080U},           /* #0 Adc_Meas_Ext_Ch1 */
    {0x800U, 0x4U, 0x0000FF02U, 4080U},           /* #1 Adc_Meas_Ext_Ch2 */
    {0x1000U, 0x8U, 0x0000FF02U, 4080U},          /* #2 Adc_Meas_Ext_Ch3 */
    {0x2000U, 0x10U, 0x0000FF02U, 4080U},         /* #3 Adc_Meas_Ext_Ch4 */
    {0x4000U, 0x10000U, 0x0000FF02U, 4080U},      /* #4 Adc_Meas_Ext_Ch5 */
    {0x8000U, 0x200000U, 0x0000FF02U, 4080U},     /* #5 Adc_Meas_Ext_Ch6 */
    {0x1000000U, 0x400000U, 0x0000FF02U, 4080U},  /* #6 Adc_Meas_Ext_Ch7 */
    {0x2000000U, 0x800000U, 0x0000FF02U, 4080U},  /* #7 Adc_Meas_Ext_Ch8 */
    {0x8000000U, 0x4000000U, 0x0000FF02U, 4080U}, /* #8 Adc_Meas_Ext_Ch9 */
    {0x40000U, 0x40000U, 0x0000FF02U, 4080U},     /* #9  Adc_Dig_DSP_Temp_Sensor */
    {0x80000U, 0x80000U, 0x0000FF02U, 4080U},     /* #10 Adc_Dig_HWA_Temp_Sensor */
    {0x100000U, 0x100000U, 0x0000FF02U, 4080U},   /* #11 Adc_Dig_HSM_Temp_Sensor */
};
#endif
/*LDRA_INSPECTED 61 X MR:5.1 Reason : "Based on Autosar Memory Map strategy" */
#define ADC_STOP_SEC_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S MR:19.1 Reason : "Based on Autosar Memory Map strategy" */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Adc_MemMap.h"

extern VAR(Adc_DriverObjType, ADC_VAR_CLEARED) Adc_DrvObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"

/* Requirements : */
/*LDRA_INSPECTED 65 D : MISRAC_2012_R.2.2 */
/* "Reason - Tool is not able to interpret pointers" */
/*LDRA_INSPECTED 120 D 1 : MISRAC_2012_R.8.13 */
/* "Reason - modified by the called function" */
void Adc_hwUnitInit(Adc_HwUnitObjType *hwUnitObj)
{
    Adc_utilsInitLinkList(&hwUnitObj->groupList);

    return;
}

/* Requirements : SWS_Adc_00111 */
/*LDRA_INSPECTED 65 D : MISRAC_2012_R.2.2 */
/* "Reason - Tool is not able to interpret pointers" */
/*LDRA_INSPECTED 120 D 1 : MISRAC_2012_R.8.13 */
/* "Reason - modified by the called function" */
void Adc_hwUnitDeInit(Adc_HwUnitObjType *hwUnitObj)
{
    Adc_utilsDeInitLinkList(&hwUnitObj->groupList);

    return;
}

/*
 * Design: MCAL-14843, MCAL-14844, MCAL-14845, MCAL-14846, MCAL-14847, MCAL-14848, MCAL-14849,
 * MCAL-14850, MCAL-14851, MCAL-14852, MCAL-14853, MCAL-14854, MCAL-14855, MCAL-14857, MCAL-14858,
 * MCAL-14859, MCAL-14860, MCAL-14835, MCAL-14834, MCAL-15353
 */
/* Requirements : SWS_Adc_00310, SWS_Adc_00311, SWS_Adc_00332, SWS_Adc_00335,
 *                SWS_Adc_00346, SWS_Adc_00348, SWS_Adc_00436, SWS_Adc_00315,
 *                SWS_Adc_00333, SWS_Adc_00340 */
Std_ReturnType Adc_startGroup(Adc_GroupObjType *groupObj)
{
    Std_ReturnType        retVal = (Std_ReturnType)E_OK;
    Adc_HwUnitObjType    *hwUnitObj;
    Adc_GroupObjType     *curGroupObj;
    Adc_GroupPriorityType effPriority;

    retVal                    = Adc_startGroupCheckStatus(groupObj);
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    if (((Std_ReturnType)E_OK) == retVal)
    {
        hwUnitObj = groupObj->hwUnitObj;

        /* Check if we have any group already going on in hardware */
        /*LDRA_INSPECTED 45 D: MISRA-C:2012 D.4.1
         * "Reason - Configurator checks ensure bound
         *  checks to ensure no invalid array access" */
        if (NULL_PTR == hwUnitObj->curGroupObj)
        {
            /* HW is free, schedule this group */
            hwUnitObj->curGroupObj = groupObj;
            groupObj->groupStatus  = ADC_BUSY;
            Adc_scheduleGroup(groupObj);
            Avoid_nesting_flag = 1U;
        }
/*LDRA_INSPECTED 139 S: MISRAC_2012_14.3
 * "Reason - In case we have a configurable macro in an if
 * condition and expression is invariant */
#if (STD_OFF == ADC_ENABLE_QUEUING)
        if (Avoid_nesting_flag == 0U)
        {
            /* Queuing is disabled - return error */
            retVal             = (Std_ReturnType)E_NOT_OK;
            Avoid_nesting_flag = 1U;
        }
#endif
        if (Avoid_nesting_flag == 0U)
        {
            if (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION)
            {
                /* Use priority only when enabled */
                effPriority = groupObj->groupCfg.groupPriority;
            }
            else
            {
                /* Use same priority so that request are processed on first
                 * come first serve basis */
                effPriority = 0U;
            }

            /* Check if this group's priority is more than current group's
             * priority */
            curGroupObj = hwUnitObj->curGroupObj;
            if (effPriority > curGroupObj->groupCfg.groupPriority)
            {
                /*
                 * This is high priority group. Stop the current group,
                 * push back to the group queue and schedule the new group
                 */

                curGroupObj->isPaused = (uint32)TRUE;
                curGroupObj->isQueued = (uint32)TRUE;
                Adc_utilsLinkNodePri(&hwUnitObj->groupList, &curGroupObj->nodeObj, curGroupObj,
                                     curGroupObj->groupCfg.groupPriority, curGroupObj->isPaused);

                /* schedule the new group */
                groupObj->groupStatus  = ADC_BUSY;
                hwUnitObj->curGroupObj = groupObj;
            }
            else
            {
                /* Some high priority group already on-going - queue this to
                 * hardware queue */
                groupObj->groupStatus = ADC_BUSY;
                groupObj->isQueued    = (uint32)TRUE;
                Adc_utilsLinkNodePri(&hwUnitObj->groupList, &groupObj->nodeObj, groupObj, effPriority, FALSE);
            }
        }
    }

    return (retVal);
}

/* Requirements : SWS_Adc_00351, SWS_Adc_00426, SWS_Adc_00427, SWS_Adc_00428 */
static Std_ReturnType Adc_startGroupCheckStatus(const Adc_GroupObjType *groupObj)
{
    Std_ReturnType retVal;

    if (ADC_IDLE != groupObj->groupStatus)
    {
        /* Group is already in progress - return error */
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        retVal = (Std_ReturnType)E_OK;
    }

    return retVal;
}

/* Requirements : SWS_Adc_00385, SWS_Adc_00155, SWS_Adc_00360,
 *                SWS_Adc_00437 */
void Adc_stopGroup(Adc_GroupObjType *groupObj, boolean SwHw)
{
    Adc_HwUnitObjType *hwUnitObj;

    hwUnitObj = groupObj->hwUnitObj;

    /* Check if on-going conversion is same as this group */
    /*LDRA_INSPECTED 45 D: MISRA-C:2012 D.4.1
     * "Reason - Configurator checks ensure bound
     *  checks to ensure no invalid array access" */
    if (groupObj == hwUnitObj->curGroupObj)
    {
        hwUnitObj->curGroupObj = (Adc_GroupObjType *)NULL_PTR;

        /* Check and schedule any pending groups for this HW */
        Adc_checkAndSchedule(hwUnitObj);
    }
    else
    {
        /* Just remove request from the hardware queue */
        Adc_utilsUnLinkNodePri(&hwUnitObj->groupList, &groupObj->nodeObj);
        groupObj->isQueued = (uint32)FALSE;
    }

    if (SwHw == TRUE)
    {
        /*Do nothing added for Klockwork issue*/
    }

    /* Disable group notification */
    groupObj->isNotifyOn = (uint32)FALSE;
    /* Set status to IDLE */
    groupObj->groupStatus = ADC_IDLE;

    return;
}

/**
 *  \brief Returns the the HW object for the corresponding HW unit ID
 */
Adc_HwUnitObjType *Adc_getHwUnitObj(Adc_HWUnitType HWUnit)
{
    uint32             hwUnitIdx;
    /*LDRA_INSPECTED 94 S : MISRAC_2012_R.11.1
     * "Reason - Pointer typecast required here since same element is
     * required to hold different types" */
    /*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4
     * "Reason - Pointer typecast required here since same element is
     * required to hold different types" */
    Adc_HwUnitObjType *hwObj  = (Adc_HwUnitObjType *)NULL_PTR;
    Adc_DriverObjType *drvObj = &Adc_DrvObj;

    /* HW unit ID may not be the index, so search for matching HW unit */
    for (hwUnitIdx = 0U; hwUnitIdx < drvObj->maxHwUnit; hwUnitIdx++)
    {
        if (drvObj->hwUnitObj[hwUnitIdx].hwUnitCfg.hwUnitId == HWUnit)
        {
            /*LDRA_INSPECTED 128 D: MISRA-C:2012 D.4.14
             * "Reason - drvObj cannot be NULL here as
             *  as it is ensured by DET error check before calling this func */
            hwObj = &drvObj->hwUnitObj[hwUnitIdx];
            break; /* Match found */
        }
    }

    /*LDRA_INSPECTED 71 S : MISRAC_2012_R.11.4
     * "Reason - Returned HW Obj is not local type */
    return (hwObj);
}

/* Requirements : SWS_Adc_00077, SWS_Adc_00307, SWS_Adc_00221 */
void Adc_resetDrvObj(Adc_DriverObjType *drvObj)
{
    uint32         hwUnitIdx, grpIdx;
    Adc_UtilsNode *nodeObj;
    uint32         chIdx;

    for (grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        drvObj->groupObj[grpIdx].groupStatus        = ADC_IDLE;
        drvObj->groupObj[grpIdx].isExplicitStopMode = (uint32)FALSE;
        drvObj->groupObj[grpIdx].isNotifyOn         = (uint32)FALSE;
        drvObj->groupObj[grpIdx].isPaused           = (uint32)FALSE;
        drvObj->groupObj[grpIdx].isQueued           = (uint32)FALSE;
        drvObj->groupObj[grpIdx].resultBufPtr       = (Adc_ValueGroupType *)NULL_PTR;

        nodeObj = &drvObj->groupObj[grpIdx].nodeObj;
        Adc_utilsInitNodeObject(nodeObj);
    }
    for (hwUnitIdx = 0U; hwUnitIdx < ADC_MAX_HW_UNIT; hwUnitIdx++)
    {
        drvObj->hwUnitObj[hwUnitIdx].curGroupObj = (Adc_GroupObjType *)NULL_PTR;
    }
    for (chIdx = 0U; chIdx < ADC_NUM_CHANNEL; ++chIdx)
    {
        drvObj->channelObj[chIdx].channelConfig.hwChannelId        = 0xFFU;
        drvObj->channelObj[chIdx].channelConfig.settlingTime       = 0U;
        drvObj->channelObj[chIdx].channelConfig.isConfigured       = FALSE;
        drvObj->channelObj[chIdx].channelConfig.channelConfigValue = 0U;
        drvObj->channelObj[chIdx].channelConfig.channelParamValue  = 0U;
        drvObj->channelObj[chIdx].channelConfig.skipSamples        = 0U;
        drvObj->channelObj[chIdx].channelConfig.collectSamples     = 0U;
        drvObj->channelObj[chIdx].channelConfig.useLuTable         = FALSE;
        drvObj->channelObj[chIdx].channelConfig.isBufferedMode     = FALSE;
    }
    drvObj->maxGroup   = 0U;
    drvObj->maxHwUnit  = 0U;
    drvObj->maxChannel = 0U;

    return;
}

/* Requirements : SWS_Adc_00091 */
void Adc_copyConfig(Adc_DriverObjType *drvObj, const Adc_ConfigType *cfgPtr)
{
    uint32                       hwUnitIdx, grpIdx;
    const Adc_HwUnitConfigType  *hwCfg;
    Adc_GroupObjType            *groupObj;
    Adc_ChannelObjType          *chObj;
    const Adc_GroupConfigType   *groupCfg;
    uint32                       chIdx;
    const Adc_ChannelConfigType *chCfg;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    Std_ReturnType retVal;
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

    drvObj->maxGroup   = cfgPtr->maxGroup;
    drvObj->maxHwUnit  = cfgPtr->maxHwUnit;
    drvObj->maxChannel = cfgPtr->maxChannel;

    for (hwUnitIdx = 0U; hwUnitIdx < cfgPtr->maxHwUnit; hwUnitIdx++)
    {
        hwCfg = &cfgPtr->hwUnitCfg[hwUnitIdx];
        {
            /* Copy configuration */
            (void)memcpy(&drvObj->hwUnitObj[hwUnitIdx].hwUnitCfg, hwCfg, sizeof(Adc_HwUnitConfigType));
        }
    }

    for (grpIdx = 0U; grpIdx < cfgPtr->maxGroup; grpIdx++)
    {
        groupCfg = &cfgPtr->groupCfg[grpIdx];
        groupObj = &drvObj->groupObj[grpIdx];
#if (STD_ON == ADC_DEV_ERROR_DETECT)
        retVal = Adc_checkGroupParameters(groupCfg, cfgPtr);
        if (((Std_ReturnType)E_OK) == retVal)
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        {
            /* Copy configuration */
            (void)memcpy(&groupObj->groupCfg, groupCfg, sizeof(Adc_GroupConfigType));

            /* Store HW object pointer for easy reference */
            /*LDRA_INSPECTED 91 D : MISRAC_2012_R.17.7
             * "Reason - groupObj->hwUnitObj is not a local variable
             * and scope is global i.e used outside this function/file " */
            groupObj->hwUnitObj = Adc_getHwUnitObj(groupCfg->hwUnitId);

            /* This condition will always hold true for this driver
             * as only one shot conversion mode is supported */
            groupObj->isExplicitStopMode = (uint32)FALSE;
        }
    }

    /* Check channel configuration */
    for (chIdx = 0U; chIdx < cfgPtr->maxChannel; chIdx++)
    {
        chCfg = &cfgPtr->channelConfig[chIdx];
#if (STD_ON == ADC_DEV_ERROR_DETECT)
        Adc_checkChannelParams(chCfg);
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        chObj = &drvObj->channelObj[cfgPtr->channelConfig[chIdx].hwChannelId];

        /* Copy configuration */
        (void)memcpy(&chObj->channelConfig, chCfg, sizeof(Adc_ChannelConfigType));
    }

    return;
}

void Adc_getChannelMuxParams(Adc_DriverObjType *drvObj)
{
    uint32 skipSamples    = 0U;
    uint8  skipSamplesReg = 0U;
    uint32 chIdx;

    /* Check channel configuration */
    for (chIdx = 0U; chIdx < ADC_NUM_CHANNEL; chIdx++)
    {
        if (TRUE == drvObj->channelObj[chIdx].channelConfig.isConfigured)
        {
            if (TRUE == drvObj->channelObj[chIdx].channelConfig.isBufferedMode)
            {
                drvObj->channelObj[chIdx].channelConfig.channelConfigValue =
                    Adc_ConfigParamLuTab[chIdx].BuffConfigValue;
            }
            else
            {
                drvObj->channelObj[chIdx].channelConfig.channelConfigValue =
                    Adc_ConfigParamLuTab[chIdx].UnbuffConfigValue;
            }

            if (TRUE == drvObj->channelObj[chIdx].channelConfig.useLuTable)
            {
                drvObj->channelObj[chIdx].channelConfig.channelParamValue = Adc_ConfigParamLuTab[chIdx].ParamInfo;
                drvObj->channelObj[chIdx].channelConfig.settlingTime = (uint8)Adc_ConfigParamLuTab[chIdx].TotalTime;
            }
            else
            {
                drvObj->channelObj[chIdx].channelConfig.channelParamValue = Adc_ConfigParamLuTab[chIdx].ParamInfo;
                /* Clear number of collect samples first collect samples */
                drvObj->channelObj[chIdx].channelConfig.channelParamValue &=
                    ~(GPADC_REG_R_REG3_COLLECT_SAMPLES_IFM_MASK);
                drvObj->channelObj[chIdx].channelConfig.channelParamValue |=
                    ((uint32)drvObj->channelObj[chIdx].channelConfig.collectSamples
                     << GPADC_REG_R_REG3_COLLECT_SAMPLES_IFM_SHIFT);
                skipSamples    = drvObj->channelObj[chIdx].channelConfig.skipSamples;
                skipSamplesReg = Adc_convSkipTimeToCode(skipSamples);
                skipSamplesReg = (uint8)((uint32)skipSamplesReg & (uint32)0x7FU);
                drvObj->channelObj[chIdx].channelConfig.channelParamValue |=
                    (uint32)((uint32)skipSamplesReg << GPADC_REG_R_REG3_SKIP_SAMPLES_IFM_SHIFT);

                /* in unit of 100ns = CollectSamples*16 + SkipSamples */
                drvObj->channelObj[chIdx].channelConfig.settlingTime =
                    (drvObj->channelObj[chIdx].channelConfig.collectSamples * 16U) +
                    (uint8)drvObj->channelObj[chIdx].channelConfig.skipSamples;
            }
        }
    }
}

uint32 Adc_checkHwUnitObj(const Adc_ConfigType *cfgPtr)
{
    uint32                      hwUnitIdx = 0U;
    const Adc_HwUnitConfigType *hwCfg;
    uint32                      found = (uint32)FALSE;

    for (hwUnitIdx = 0U; hwUnitIdx < cfgPtr->maxHwUnit; hwUnitIdx++)
    {
        hwCfg = &cfgPtr->hwUnitCfg[hwUnitIdx];
        if (hwCfg->hwUnitId == ADC_UNIT_1)
        {
            found = (uint32)TRUE;
            break; /* Match found */
        }
    }
    return (found);
}

/* check channel parameters */
#if (STD_ON == ADC_DEV_ERROR_DETECT)
static void Adc_checkChannelParams(const Adc_ChannelConfigType *chCfg)
{
    if (chCfg->hwChannelId > ADC_MAX_HW_CHANNEL_ID)
    {
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }

    return;
}

#endif

#if (STD_ON == ADC_DEV_ERROR_DETECT)
static Std_ReturnType Adc_checkGroupParameters(const Adc_GroupConfigType *groupCfg, const Adc_ConfigType *cfgPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    /* ID is used as index, can't exceed array size */
    if (groupCfg->groupId >= cfgPtr->maxGroup)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }
    /* check group parameters */
    else if (ADC_CONV_MODE_ONESHOT != groupCfg->convMode)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }
    else if (NULL_PTR == Adc_getHwUnitObj(groupCfg->hwUnitId))
    {
        /* DET already reported by Adc_getHwUnitObj() */
        retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == ADC_DEV_ERROR_DETECT)
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    }
    else
    {
        retVal = Adc_checkGroupCfgRangeParameters(groupCfg);
    }

    return retVal;
}

#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

#if (STD_ON == ADC_DEV_ERROR_DETECT)
static Std_ReturnType Adc_checkGroupCfgRangeParameters(const Adc_GroupConfigType *groupCfg)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    if ((0U == groupCfg->numChannels) || (groupCfg->numChannels > ADC_NUM_CHANNEL) ||
        (groupCfg->resolution != ADC_DEF_CHANNEL_RESOLUTION))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }

    return retVal;
}

#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

/* Requirements : SWS_Adc_00280, SWS_Adc_00431, SWS_Adc_00222, SWS_Adc_00345 */
static void Adc_scheduleGroup(Adc_GroupObjType *groupObj)
{
    if (((uint32)TRUE) == groupObj->isPaused)
    {
        /* Group should already be in busy state */
        /* Set isPaused to False */
        groupObj->isPaused = (uint32)FALSE;
    }

    /* Configure ADC steps and start conversion */
    Adc_hwStart();

    return;
}

void Adc_checkAndSchedule(Adc_HwUnitObjType *hwUnitObj)
{
    Adc_UtilsNode    *headNodeObj;
    Adc_GroupObjType *nextGroupObj;

    /* Check if any new group is pending */
    headNodeObj = Adc_utilsGetHeadNode(&hwUnitObj->groupList);
    if (NULL_PTR != headNodeObj)
    {
        /* Some group pending - schedule it */
        nextGroupObj = (Adc_GroupObjType *)headNodeObj->data;
        Adc_utilsUnLinkNodePri((&(hwUnitObj->groupList)), headNodeObj);
        nextGroupObj->isQueued = (uint32)FALSE;
        hwUnitObj->curGroupObj = nextGroupObj;
        Adc_scheduleGroup(nextGroupObj);
    }

    return;
}

void Adc_performHwInit(void)
{
    Adc_hwDriverInit();

    Adc_hwResetRelease();
}

void Adc_performHwDeInit(void)
{
    Adc_hwDriverDeInit();
}

void Adc_FillDataBufferPtr(Adc_ValueGroupType *DataBufferPtr, Adc_GroupObjType *groupObj)
{
    uint32 chIdx;
    for (chIdx = 0U; chIdx < groupObj->groupCfg.numChannels; chIdx++)
    {
        DataBufferPtr[chIdx] = groupObj->resultBufPtr[chIdx];
    }
    groupObj->groupStatus = ADC_IDLE;
}

Std_ReturnType Adc_groupConversionDoneHandler(void)
{
    Adc_HwUnitObjType *hwUnitObj = Adc_getHwUnitObj(ADC_UNIT_1);

    if ((hwUnitObj != NULL_PTR) && (ADC_INTERRUPT_MODE != hwUnitObj->hwUnitCfg.hwUnitMonitorMode))
    {
        Adc_groupGpConversionDoneHandler();
    }

    return E_OK;
}

Adc_StreamNumSampleType Adc_GetStreamLastPointerinternal(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr)
{
    return 0;
    /*do nothing*/
}

Std_ReturnType Adc_getStreamPtrCheckDetError(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr)
{
    return 0;
    /*do nothing*/
}

#if (STD_ON == ADC_REGISTER_READBACK_API)
/******************************************************************************
 *  Adc_HWRegisterReadback
 ******************************************************************************/
/*! \brief      This method is Adc_HWRegisterReadback Api.
 *  \param[in]  Adc_RegisterReadbackType       RegRbPtr
 *  \param[out] none
 *  \return     E_OK, E_NOT_OK
 *  \context    Function could be called from from task level
 ******************************************************************************/
FUNC(void, ADC_CODE)
Adc_HWRegisterReadback(P2VAR(Adc_RegisterReadbackType, AUTOMATIC, ADC_APPL_DATA) RegRbPtr, Adc_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr;

    /*Get the Register base address*/
    baseAddr = MSS_GPADC_REG_BASE_ADDRESS;

    /*Get the Register value*/
    RegRbPtr->adcCtrl1 = HW_RD_REG16(baseAddr + R_REG0_ADDR_OFFSET);
    RegRbPtr->adcCtrl2 = HW_RD_REG16(baseAddr + R_REG1_ADDR_OFFSET);
}
#endif /*STD_ON == ADC_REGISTER_READBACK_API*/

void Adc_reportDetRuntimeError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportRuntimeError(ADC_MODULE_ID, ADC_INSTANCE_ID, apiId, errorId);
    return;
}

#if (STD_ON == ADC_POLLING_MAINFUNCTION_API)
void Adc_groupPolling(Adc_GroupObjType *groupObj)
{
}
#endif /* #if (STD_ON == ADC_POLLING_MAINFUNCTION_API) */

#if (STD_ON == ADC_DEV_ERROR_DETECT)
void Adc_reportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

/*LDRA_INSPECTED 580 S: MISRAC_2012_1.1
 * "Reason - LDRA is not able to analyze as there is no macro redefinition
 *  here." */
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
