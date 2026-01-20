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
#include "Adc.h"
#include "Adc_Dbg.h"
#include "Adc_Priv.h"
#include "Adc_Irq.h"
#include "Dem.h"
#include "Adc_RegResult.h"

#if (STD_ON == ADC_DMA_MODE)
#include "Cdd_Dma.h"
#endif

#if ((STD_ON == ADC_ERR_LOG) || (STD_ON == ADC_GROUP_LOG))
#include "Os.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Adc_scheduleGroup(Adc_GroupObjType *groupObj);
static void Adc_checkAndSchedule(Adc_HwUnitObjType *hwUnitObj);
static void Adc_procIsr(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *groupObj);
static void Adc_resetGroupObjOnResume(Adc_GroupObjType *groupObj);

static void Adc_hwConfig(const Adc_GroupObjType *groupObj, uint32 baseAddr);
static void Adc_hwStart(uint32 baseAddr);
static void Adc_hwStop(uint32 baseAddr, const Adc_GroupObjType *groupObj);
static void Adc_hwSetDefReg(uint32 baseAddr);
static void Adc_setGroupStatusPostIsr(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *groupObj, uint32 convComplete,
                                      uint32 streamComplete);
static void Adc_setGroupStatusPostIsrStopADC(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *groupObj);
static Std_ReturnType Adc_startGroupCheckStatus(const Adc_GroupObjType *groupObj);

static void           Adc_startGroup_scheduleGP(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj);
static Std_ReturnType Adc_startGroup_ErChkr(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj);
static Std_ReturnType Adc_startGroup_Internal(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj, boolean hwQue);
static Std_ReturnType Adc_startGroup_Check_HWque(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj);
#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION))
static Std_ReturnType Adc_startGroup_AssignSocInt(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj);
#endif
static void           Adc_procIsr_Internal(uint32 *convComplete, Adc_GroupObjType *groupObj, uint32 *streamComplete,
                                           Adc_ChannelObjType *chObj);
static Std_ReturnType Adc_checkAndSchedule_Internal(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *nextGroupObj);
static void           Adc_copyConfig_Internal(const Adc_GroupConfigType *groupCfg);
static boolean Adc_IrqTxRx_Internal(uint32 baseAddr, Adc_GroupObjType **groupObj, uint16 InterruptNum, uint8 adcSoc);
static void    Adc_hwConfig_check_accessMode(const Adc_GroupObjType *groupObj, uint32 baseAddr, uint16 groupMask,
                                             uint16 adcLastSoc, const Adc_GroupConfigType *groupCfg);
static void    Adc_copyConfig_ExplicitStopMode(Adc_GroupObjType *groupObj, const Adc_GroupConfigType *groupCfg);

#if (STD_ON == ADC_DEV_ERROR_DETECT)
static Std_ReturnType Adc_checkGroupCfgRangeParameters(const Adc_GroupConfigType *groupCfg);
static Std_ReturnType Adc_checkGroupParameters(const Adc_GroupConfigType *groupCfg, const Adc_ConfigType *cfgPtr);
static boolean        Adc_checkGroupParametersDet_HW(const Adc_GroupConfigType *groupCfg);
static Std_ReturnType Adc_checkGroupParametersDet_SW(const Adc_GroupConfigType *groupCfg);
static boolean        Adc_CheckPass(const Adc_GroupObjType *groupObjCurrent, const Adc_GroupObjType *groupObj);
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

#if (STD_ON == ADC_DMA_MODE)
static void Adc_IrqDmaTxRx(void *groupId);
static void AdcDma_FreeModuleChannelConfigured(uint32 dma_ch);
#endif /* #if (STD_ON == ADC_DMA_MODE) */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if (STD_ON == ADC_GROUP_LOG)
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
/** \brief ADC group log object */
VAR(Adc_GroupLogType, ADC_VAR_CLEARED) Adc_GroupLogObj;
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
#endif /* #if (STD_ON == ADC_GROUP_LOG) */

#if (STD_ON == ADC_ERR_LOG)
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
/** \brief ADC FIFO error log object */
VAR(Adc_ErrLogType, ADC_VAR_CLEARED) Adc_ErrLogObj;
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
#endif /* #if (STD_ON == ADC_ERR_LOG) */

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
/** \brief ADC ISR Index */
VAR(Adc_HwSocObjType, ADC_VAR_CLEARED) Adc_HwSocGroupMapping[ADC_HW_UNIT_CNT];
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"

void Adc_hwUnitInit(Adc_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr;

    /* Assign base address */
    hwUnitObj->baseAddr       = hwUnitObj->hwUnitCfg.baseAddr;
    hwUnitObj->resultBaseAddr = hwUnitObj->hwUnitCfg.baseAddr;

    /* Get the Result Register. */
    switch (hwUnitObj->hwUnitCfg.hwUnitId)
    {
        case 0:
            hwUnitObj->resultBaseAddr = MCAL_CONTROLSS_ADC0_RESULT;
            break;
        case 1:
            hwUnitObj->resultBaseAddr = MCAL_CONTROLSS_ADC1_RESULT;
            break;
        case 2:
            hwUnitObj->resultBaseAddr = MCAL_CONTROLSS_ADC2_RESULT;
            break;
        case 3:
            hwUnitObj->resultBaseAddr = MCAL_CONTROLSS_ADC3_RESULT;
            break;
        case 4:
            hwUnitObj->resultBaseAddr = MCAL_CONTROLSS_ADC4_RESULT;
            break;
        case 5:
            hwUnitObj->resultBaseAddr = MCAL_CONTROLSS_ADCR0_RESULT;
            break;
        case 6:
            hwUnitObj->resultBaseAddr = MCAL_CONTROLSS_ADCR1_RESULT;
            break;
        default:
            /* Do nothing*/
            break;
    }

    /*
     * Init the HW instance
     */
    baseAddr = hwUnitObj->baseAddr;

    /* Set the Prescaler for ADC HW unit. */
    ADC_setPrescaler(baseAddr, hwUnitObj->hwUnitCfg.prescale);

    /* Set the Resolution for ADC HW unit. */
    ADC_setMode(baseAddr, hwUnitObj->hwUnitCfg.resolution, ADC_MODE_SINGLE_ENDED);

    /* Disable all Interrupt */
    ADC_disableInterrupt(baseAddr, 0);
    ADC_disableInterrupt(baseAddr, 1);
    ADC_disableInterrupt(baseAddr, 2);
    ADC_disableInterrupt(baseAddr, 3);

    /* Disable continuous mode */
    ADC_disableContinuousMode(baseAddr, 0U);
    ADC_disableContinuousMode(baseAddr, 1U);
    ADC_disableContinuousMode(baseAddr, 2U);
    ADC_disableContinuousMode(baseAddr, 3U);

    /* Clear interrupt status */
    ADC_clearInterruptStatus(baseAddr, 0U);
    ADC_clearInterruptStatus(baseAddr, 1U);
    ADC_clearInterruptStatus(baseAddr, 2U);
    ADC_clearInterruptStatus(baseAddr, 3U);

    /* Clear Status Register. */
    HW_WR_REG16((baseAddr + MCAL_CSL_ADC_ADCEVTCLR), 0xFFFF);

    /*
     * Power up Analog Front End
     */
    ADC_enableConverter(baseAddr);
    Adc_utilsInitLinkList(&hwUnitObj->groupList);

    return;
}

void Adc_hwUnitDeInit(Adc_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr;
    baseAddr = hwUnitObj->baseAddr;
    /*
     * De-Init the HW instance
     */
    Adc_hwSetDefReg(baseAddr);
    Adc_utilsDeInitLinkList(&hwUnitObj->groupList);

    return;
}

/*
 * Design: MCAL-14843, MCAL-14844, MCAL-14845, MCAL-14846, MCAL-14847, MCAL-14848, MCAL-14849,
 * MCAL-14850, MCAL-14851, MCAL-14852, MCAL-14853, MCAL-14854, MCAL-14855, MCAL-14857, MCAL-14858,
 * MCAL-14859, MCAL-14860, MCAL-14835, MCAL-14834, MCAL-15353
 */
Std_ReturnType Adc_startGroup(Adc_GroupObjType *groupObj)
{
    Std_ReturnType     retVal = (Std_ReturnType)E_OK;
    Adc_HwUnitObjType *hwUnitObj;
    retVal = Adc_startGroupCheckStatus(groupObj);
    if (((Std_ReturnType)E_OK) == retVal)
    {
        hwUnitObj = groupObj->hwUnitObj;

        /* Check if we have any group already going on in hardware */
        if (NULL_PTR == hwUnitObj->curGroupObj)
        {
#if (ADC_PRIORITY_NONE == ADC_PRIORITY_IMPLEMENTATION)
            /* HW is free, schedule this group */
            Adc_startGroup_scheduleGP(groupObj, hwUnitObj);
#endif

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION))
            /* HW is free, schedule this group */
            Adc_startGroup_scheduleGP(groupObj, hwUnitObj);
#endif
        }
        else
        {
#if (ADC_ENABLE_QUEUING == STD_OFF)
            /* Queuing is disabled - return error */
            retVal = (Std_ReturnType)E_NOT_OK;
            Adc_reportDetRuntimeError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
#endif
            /* Check if, error */
            if (((Std_ReturnType)E_OK) == retVal)
            {
                retVal = Adc_startGroup_ErChkr(groupObj, hwUnitObj);
            }
        }
    }

    return (retVal);
}

static boolean Adc_CheckPass(const Adc_GroupObjType *groupObjCurrent, const Adc_GroupObjType *groupObj)
{
    boolean ret = FALSE;

    /*Check the trigger source*/
    if (groupObjCurrent->groupCfg.triggSrc == ADC_TRIGG_SRC_SW)
    {
        ret = TRUE;
    }

    /*Check the Group priorty*/
    if (groupObj->groupCfg.groupPriority > groupObjCurrent->groupCfg.groupPriority)
    {
        ret = TRUE;
    }

    return ret;
}

static void Adc_startGroup_scheduleGP(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj)
{
    hwUnitObj->curGroupObj    = groupObj;
    groupObj->lastSocAssigned = (uint16)ADC_SOC_NUMBER15;
    if (hwUnitObj->curGroupObj->groupCfg.numChannels == 1U)
    {
        groupObj->socAssigned = (uint16)(ADC_SOC_NUMBER15);
    }
    else
    {
        groupObj->socAssigned =
            (uint16)((uint16)(ADC_SOC_NUMBER15)) - (((uint16)hwUnitObj->curGroupObj->groupCfg.numChannels) - 1U);
    }
    hwUnitObj->socHwPtr         = (uint16)(((uint16)groupObj->socAssigned) - 1U);
    groupObj->groupStatus       = ADC_BUSY;
    groupObj->groupInterruptSrc = ADC_INT_NUMBER1;
#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION))
    hwUnitObj->numHwGroupsQue = (uint16)(ADC_INT_NUMBER1);
#endif
    Adc_scheduleGroup(groupObj);
}

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION))
/**
 *  \brief  Assigns SOC slots and interrupt source for group start operation
 *
 *  This function is called during Adc_startGroup_ErChkr to validate SOC (Start of Conversion)
 *  range availability, assign SOC slots based on the number of channels in the group,
 *  and assign an interrupt source to the group for hardware priority scheduling.
 *
 *  \param[in,out]  groupObj    Pointer to the group object to be configured
 *  \param[in,out]  hwUnitObj   Pointer to the hardware unit object containing SOC state
 *
 *  \return E_OK if SOC and interrupt assignment successful, E_NOT_OK if resources unavailable
 */
static Std_ReturnType Adc_startGroup_AssignSocInt(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    /* Check SOC range - verify enough SOC slots are available */
    if (((uint16)((uint16)(ADC_SOC_NUMBER15)-hwUnitObj->socHwPtr + groupObj->groupCfg.numChannels)) >
        ((uint16)(ADC_SOC_NUMBER15)))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* Assign SOC based on numChannels */
        if (groupObj->groupCfg.numChannels == 1U)
        {
            groupObj->socAssigned = hwUnitObj->socHwPtr;
        }
        else
        {
            groupObj->socAssigned =
                (uint16)(((uint16)(hwUnitObj->socHwPtr)) - ((uint16)(groupObj->groupCfg.numChannels) - (uint16)1U));
        }

        hwUnitObj->socHwPtr = (uint16)(((uint16)groupObj->socAssigned) - 1U);

        /* Check if Interrupt is Valid */
        if (hwUnitObj->numHwGroupsQue >= (uint16)ADC_INVALID_HW_INT)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            hwUnitObj->numHwGroupsQue++;
            groupObj->groupInterruptSrc = hwUnitObj->numHwGroupsQue;
        }
    }

    return retVal;
}
#endif /* #if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == \
          ADC_PRIORITY_IMPLEMENTATION)) */

static Std_ReturnType Adc_startGroup_ErChkr(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || \
     ((ADC_PRIORITY_NONE == ADC_PRIORITY_IMPLEMENTATION) && (ADC_ENABLE_QUEUING == STD_ON)))
    boolean hwQue = ADC_FALSE;
#endif

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION)) || \
    ((ADC_PRIORITY_NONE == ADC_PRIORITY_IMPLEMENTATION) && (ADC_ENABLE_QUEUING == STD_ON))
    Adc_GroupObjType *curGroupObj = (Adc_GroupObjType *)NULL_PTR;

    if (curGroupObj != NULL_PTR)
    {
        /*Do nothing, written to fix build issues*/
    }
#endif

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION))

    /* Check if this group's priority is more than current group's
     * priority */
    curGroupObj = hwUnitObj->curGroupObj;

    if (ADC_TRUE == Adc_CheckPass(curGroupObj, groupObj))
    {
        groupObj->lastSocAssigned = hwUnitObj->socHwPtr;

        /* Assign SOC slots and interrupt source for this group */
        retVal = Adc_startGroup_AssignSocInt(groupObj, hwUnitObj);

        if (retVal == E_OK)
        {
            /* Schedule the Group to HW Queue. */
            groupObj->groupStatus = ADC_BUSY;
            Adc_scheduleGroup(groupObj);
#if (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION)
            hwQue = ADC_TRUE;
#endif
        }
        else
        {
#if (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION)
            if (curGroupObj->groupCfg.triggSrc == ADC_TRIGG_SRC_SW)
            {
                /* Allow the Group to store in Software Queue. */
                hwQue = ADC_FALSE;
            }
            else
            {
                hwQue = ADC_TRUE;
            }
#endif
        }
    }
#if (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION)
    else
    {
        if (groupObj->groupCfg.triggSrc == ADC_TRIGG_SRC_SW)
        {
            /* Allow the Group to store in Software Queue. */
            hwQue = ADC_FALSE;
        }
        else
        {
            hwQue = ADC_TRUE;
        }
    }
#else
    else
    {
        /* Queuing is disabled - return error */
        retVal = (Std_ReturnType)E_NOT_OK;
    }
#endif

#endif

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || \
     ((ADC_PRIORITY_NONE == ADC_PRIORITY_IMPLEMENTATION) && (ADC_ENABLE_QUEUING == STD_ON)))
    /* Check if this group's priority is more than current group's
     * priority */

    retVal = Adc_startGroup_Internal(groupObj, hwUnitObj, hwQue);

#endif

    return (retVal);
}

static Std_ReturnType Adc_startGroup_Internal(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj, boolean hwQue)
{
    Std_ReturnType        retVal      = (Std_ReturnType)E_OK;
    Adc_GroupObjType     *curGroupObj = (Adc_GroupObjType *)NULL_PTR;
    Adc_GroupPriorityType effPriority = groupObj->groupCfg.groupPriority;
    curGroupObj                       = hwUnitObj->curGroupObj;

    if ((effPriority > curGroupObj->groupCfg.groupPriority) && (hwQue == ADC_FALSE))
    {
        /*
         * This is high priority group. Stop the current group,
         * push back to the group queue and schedule the new group
         */

        /* Check if Group is HW or SW triggered group. */
        if (groupObj->groupCfg.triggSrc == ADC_TRIGG_SRC_SW)
        {
            /* Stop current group and push back to hardware queue */
            Adc_hwStop(hwUnitObj->baseAddr, groupObj);
            curGroupObj->isPaused = (uint32)ADC_TRUE;
            curGroupObj->isQueued = (uint32)ADC_TRUE;
            Adc_utilsLinkNodePri(&hwUnitObj->groupList, &curGroupObj->nodeObj, curGroupObj,
                                 curGroupObj->groupCfg.groupPriority, curGroupObj->isPaused);
        }

        /* schedule the new group */
        groupObj->groupStatus  = ADC_BUSY;
        hwUnitObj->curGroupObj = groupObj;
#if (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION)
        /* Check if, HW Queue if filled or not. */
        retVal = Adc_startGroup_Check_HWque(groupObj, hwUnitObj);

        /* Check if there is DET Error. */
        if (retVal == E_OK)
#endif
        {
            /* Schedule the Group to HW Queue. */
            Adc_scheduleGroup(groupObj);
        }
    }
    else
    {
        /* Check if Group is HW or SW triggered group. */
        if ((groupObj->groupCfg.triggSrc == ADC_TRIGG_SRC_SW) && (hwQue == ADC_FALSE))
        {
            /* Some high priority group already on-going - queue this to
             * hardware queue */
            groupObj->groupStatus = ADC_BUSY;
            groupObj->isQueued    = (uint32)ADC_TRUE;
            Adc_utilsLinkNodePri(&hwUnitObj->groupList, &groupObj->nodeObj, groupObj, effPriority, ADC_FALSE);
        }
    }
    return (retVal);
}

static Std_ReturnType Adc_startGroup_Check_HWque(Adc_GroupObjType *groupObj, Adc_HwUnitObjType *hwUnitObj)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    if (((uint16)(((uint16)(ADC_SOC_NUMBER15)) - hwUnitObj->socHwPtr + ((uint16)groupObj->groupCfg.numChannels))) <=
        ((uint16)(ADC_SOC_NUMBER15)))
    {
        /* Assign the Queue number. */
        groupObj->lastSocAssigned = hwUnitObj->socHwPtr;
        if (groupObj->groupCfg.numChannels == 1U)
        {
            groupObj->socAssigned = hwUnitObj->socHwPtr;
        }
        else
        {
            groupObj->socAssigned =
                (uint16)(((uint16)(hwUnitObj->socHwPtr)) - ((uint16)(groupObj->groupCfg.numChannels) - (uint16)1U));
        }

        hwUnitObj->socHwPtr = (uint16)(((uint16)groupObj->socAssigned) - 1U);

        /* Check if Interrupt is Valid. */
        if (hwUnitObj->numHwGroupsQue >= (uint16)ADC_INVALID_HW_INT)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            hwUnitObj->numHwGroupsQue++;
            retVal                      = E_OK;
            groupObj->groupInterruptSrc = hwUnitObj->numHwGroupsQue;
        }
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    return (retVal);
}

void Adc_stopGroup(Adc_GroupObjType *groupObj, boolean SwHw)
{
    Adc_HwUnitObjType *hwUnitObj;

    hwUnitObj = groupObj->hwUnitObj;

    /* Check if on-going conversion is same as this group */
    if (groupObj == hwUnitObj->curGroupObj)
    {
        /* Stop ADC */
        Adc_hwStop(hwUnitObj->baseAddr, groupObj);
        hwUnitObj->curGroupObj = NULL;

        /* Check and schedule any pending groups for this HW */
        Adc_checkAndSchedule(hwUnitObj);
    }
    else
    {
        if (SwHw == ADC_TRUE)
        {
            /* Just remove request from the queue */
            Adc_utilsUnLinkNodePri(&hwUnitObj->groupList, &groupObj->nodeObj);
            groupObj->isQueued = (uint32)ADC_FALSE;
        }
    }

    /* Disable group notification */
    groupObj->isNotifyOn = (uint32)ADC_FALSE;
    /* Set status to IDLE */
    groupObj->groupStatus = ADC_IDLE;

    /* Reset the SOC pointer. */
    groupObj->socAssigned     = (uint16)ADC_INVALID_HW_SOC;
    groupObj->lastSocAssigned = (uint16)ADC_INVALID_HW_SOC;

    return;
}

#if (STD_ON == ADC_POLLING_MAINFUNCTION_API)
void Adc_groupPolling(Adc_GroupObjType *groupObj)
{
    Adc_HwUnitObjType *hwUnitObj;
    uint32             baseAddr;

    hwUnitObj = groupObj->hwUnitObj;
    baseAddr  = hwUnitObj->baseAddr;

    if ((groupObj->groupCfg.groupDataAccessMode == ADC_GROUP_POLLING_ACCESS) && (groupObj->groupStatus == ADC_BUSY))
    {
        if (ADC_FALSE == ADC_getInterruptStatus(baseAddr, groupObj->groupInterruptSrc))
        {
            /* Keep the status as busy. */
            groupObj->groupStatus = ADC_BUSY;
        }
        else
        {
            ADC_clearInterruptStatus(baseAddr, (uint16)groupObj->groupInterruptSrc);
            /* Process the Group Conversion. */
            Adc_procIsr(hwUnitObj, groupObj);
        }
    }

    return;
}
#endif /* #if (STD_ON == ADC_POLLING_MAINFUNCTION_API) */

void Adc_IrqTxRx(Adc_HwUnitObjType *hwUnitObj, uint16 InterruptNum, uint8 Soc)
{
    uint32            baseAddr;
    Adc_GroupObjType *groupObj;
    boolean           allowFlag = ADC_TRUE;

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION))
    uint8             adcSoc;
    Adc_HwSocObjType *socPtr;
#endif

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    uint8 LimitCheck;
#endif
    baseAddr = hwUnitObj->baseAddr;
    groupObj = hwUnitObj->curGroupObj;

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION))
    adcSoc   = 0;
    adcSoc   = (uint8)(Soc);
    socPtr   = &Adc_HwSocGroupMapping[hwUnitObj->hwUnitCfg.hwUnitId];
    groupObj = &Adc_DrvObj.groupObj[socPtr->adcHwSocGroup[adcSoc]];

#if (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION)
    /* Check if, Group is from SW queue */
    if (hwUnitObj->swGroupSchduled == ADC_FALSE)
#endif
    {
        allowFlag = Adc_IrqTxRx_Internal(baseAddr, &groupObj, InterruptNum, adcSoc);
    }
#if (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION)
    else
    {
        /* Get the Current Group. */
        hwUnitObj->swGroupSchduled = ADC_FALSE;
        groupObj                   = hwUnitObj->curGroupObj;
        if (allowFlag == ADC_TRUE)
        {
            /* No Actions Required. */
        }
    }
#endif

#endif

    if (NULL_PTR != groupObj)
    {
        /* Check if, Data access mode. */
        switch (groupObj->groupCfg.groupDataAccessMode)
        {
            case ADC_GROUP_DMA_ACCESS:
            case ADC_GROUP_POLLING_ACCESS:
            {
                allowFlag = ADC_FALSE;
            }
            break;

            case ADC_GROUP_INTERRUPT_ACCESS:
            {
                /* Allow for processing the Group. */
                if (groupObj->groupStatus == ADC_IDLE)
                {
                    ADC_clearInterruptStatus(baseAddr, (uint16)InterruptNum);
                    allowFlag = ADC_FALSE;
                }
            }
            break;

            default:
                /* Do nothing*/
                break;
        }
    }

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    if (ADC_TRUE == groupObj->groupCfg.grouplimitcheck)
    {
        /* Get the status of ADC Limit Values. */
        LimitCheck = (HW_RD_REG16(baseAddr + MCAL_CSL_ADC_ADCEVTSTAT));

        /* Check if, Error limits are occured or not.  */
        if ((MCAL_CSL_ADC_ADCEVTSTAT_PPB1TRIPHI_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB1TRIPHI_MASK)) ||
            (MCAL_CSL_ADC_ADCEVTSTAT_PPB1TRIPLO_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB1TRIPLO_MASK)) ||
            (MCAL_CSL_ADC_ADCEVTSTAT_PPB2TRIPHI_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB2TRIPHI_MASK)) ||
            (MCAL_CSL_ADC_ADCEVTSTAT_PPB2TRIPLO_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB2TRIPLO_MASK)) ||
            (MCAL_CSL_ADC_ADCEVTSTAT_PPB3TRIPHI_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB3TRIPHI_MASK)) ||
            (MCAL_CSL_ADC_ADCEVTSTAT_PPB3TRIPLO_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB3TRIPLO_MASK)) ||
            (MCAL_CSL_ADC_ADCEVTSTAT_PPB4TRIPHI_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB4TRIPHI_MASK)) ||
            (MCAL_CSL_ADC_ADCEVTSTAT_PPB4TRIPLO_MASK == (LimitCheck & MCAL_CSL_ADC_ADCEVTSTAT_PPB4TRIPLO_MASK)))
        {
            allowFlag = ADC_FALSE;
        }

        /* Clear Status Register. */
        HW_WR_REG16((baseAddr + MCAL_CSL_ADC_ADCEVTCLR), LimitCheck);
    }
    else
    {
        /* No Actions Required. */
    }
#endif

    /*
     * Process the group
     */
    if ((NULL_PTR != groupObj) && (allowFlag == ADC_TRUE))
    {
        /* Clear interrupts immediately before handling events. This should avoid
         * missing the same interrupts again while handling the events */
        ADC_clearInterruptStatus(baseAddr, (uint16)InterruptNum);

        /* Process the Interrupt */
        Adc_procIsr(hwUnitObj, groupObj);

        /* Check if overflow has occurred */
        if (TRUE == ADC_getInterruptOverflowStatus(baseAddr, InterruptNum))
        {
            ADC_clearInterruptOverflowStatus(baseAddr, InterruptNum);
            ADC_clearInterruptStatus(baseAddr, (uint16)InterruptNum);
        }
    }

    return;
}

static boolean Adc_IrqTxRx_Internal(uint32 baseAddr, Adc_GroupObjType **groupObj, uint16 InterruptNum, uint8 adcSoc)
{
    Adc_HwUnitObjType *grpHwUnitObj;
    boolean            allowFlag = ADC_TRUE;
    if ((adcSoc != ADC_INVALID_INDEX) && ((*groupObj)->groupInterruptSrc == InterruptNum))
    {
        grpHwUnitObj = (*groupObj)->hwUnitObj;
        if (baseAddr == grpHwUnitObj->baseAddr)
        {
            if (allowFlag == ADC_TRUE)
            {
                /* No Actions Required. */
            }
        }
        else
        {
            allowFlag = ADC_FALSE;
        }
    }
    return (allowFlag);
}

#if (STD_ON == ADC_DMA_MODE)
static void Adc_IrqDmaTxRx(void *groupId)
{
    uint32             baseAddr;
    boolean            convComplete   = ADC_FALSE;
    boolean            streamComplete = ADC_FALSE;
    uint8              adcSoc         = 0;
    Adc_HwUnitObjType *hwUnitObj      = NULL_PTR;
    Adc_GroupObjType  *groupObj       = NULL_PTR;
    uint32            *lGroupId       = (uint32 *)groupId;
    uint32             groupCount     = (uint32)lGroupId;

    groupObj  = &Adc_DrvObj.groupObj[groupCount];
    hwUnitObj = groupObj->hwUnitObj;

    if (NULL_PTR != groupObj)
    {
        baseAddr = hwUnitObj->baseAddr;
        adcSoc   = (uint8)(groupObj->lastSocAssigned);

        ADC_clearInterruptStatus(baseAddr, (uint16)groupObj->groupInterruptSrc);

        /* Check if overflow has occurred */
        if (ADC_TRUE == ADC_getInterruptOverflowStatus(baseAddr, groupObj->groupInterruptSrc))
        {
            ADC_clearInterruptOverflowStatus(baseAddr, groupObj->groupInterruptSrc);
        }

        /*
         * Process the group
         */
        if (NULL_PTR != groupObj)
        {
            /* Stop the conversion, if required. */
            convComplete   = (uint32)ADC_TRUE;
            streamComplete = (uint32)ADC_TRUE;

            /* Set Group Status and Call group end notification */
            Adc_setGroupStatusPostIsr(hwUnitObj, groupObj, convComplete, streamComplete);
        }

        /* Stop the ADCs by removing the trigger for SOC0 */
        ADC_setInterruptSOCTrigger(baseAddr, (uint16)adcSoc, ADC_INT_SOC_TRIGGER_NONE);
    }
    else
    {
        /* No Actions Required. */
    }
    return;
}
#endif

/**
 *  \brief Returns the the HW object for the corresponding HW unit ID
 */
Adc_HwUnitObjType *Adc_getHwUnitObj(Adc_HWUnitType HWUnit)
{
    Adc_HwUnitObjType *hwObj  = (Adc_HwUnitObjType *)NULL_PTR;
    Adc_DriverObjType *drvObj = &Adc_DrvObj;

    /* Get the HW unit.  */
    hwObj = &drvObj->hwUnitObj[HWUnit];

    if (hwObj == NULL_PTR)
    {
#if (STD_ON == ADC_DEV_ERROR_DETECT)
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    }

    return (hwObj);
}

void Adc_resetDrvObj(Adc_DriverObjType *drvObj)
{
    uint8          hwUnitIdx, grpIdx, socIdx;
    uint32         chIdx;
    Adc_UtilsNode *nodeObj;

    /* Initialize configured Interrupt Index. */
    for (hwUnitIdx = 0U; hwUnitIdx < ADC_HW_UNIT_CNT; hwUnitIdx++)
    {
        Adc_HwSocGroupMapping[hwUnitIdx].adcHwUnit = ADC_INVALID_INDEX;

        /* ADC SOC Init. */
        for (socIdx = 0U; socIdx < ADC_MAX_SOC; socIdx++)
        {
            Adc_HwSocGroupMapping[hwUnitIdx].adcHwSocGroup[socIdx] = ADC_INVALID_INDEX;
        }
    }

    for (grpIdx = 0U; grpIdx < ADC_MAX_GROUP; grpIdx++)
    {
        drvObj->groupObj[grpIdx].groupStatus        = ADC_IDLE;
        drvObj->groupObj[grpIdx].isExplicitStopMode = (uint32)ADC_FALSE;
        drvObj->groupObj[grpIdx].isNotifyOn         = (uint32)ADC_FALSE;
        drvObj->groupObj[grpIdx].isPaused           = (uint32)ADC_FALSE;
        drvObj->groupObj[grpIdx].isQueued           = (uint32)ADC_FALSE;
        drvObj->groupObj[grpIdx].validSampleCount   = 0U;
        drvObj->groupObj[grpIdx].curCh              = 0U;
        drvObj->groupObj[grpIdx].resultBufPtr       = NULL;
        for (chIdx = 0U; chIdx < ADC_NUM_CHANNEL; chIdx++)
        {
            drvObj->groupObj[grpIdx].chObj[chIdx].chResultBufPtr  = NULL;
            drvObj->groupObj[grpIdx].chObj[chIdx].curResultBufPtr = NULL;
            drvObj->groupObj[grpIdx].chObj[chIdx].curNumSamples   = 0U;
        }

        nodeObj = &drvObj->groupObj[grpIdx].nodeObj;
        Adc_utilsInitNodeObject(nodeObj);
    }
    for (hwUnitIdx = 0U; hwUnitIdx < ADC_MAX_HW_UNIT; hwUnitIdx++)
    {
        drvObj->hwUnitObj[hwUnitIdx].curGroupObj = NULL;
    }
    drvObj->maxGroup  = 0U;
    drvObj->maxHwUnit = 0U;

    return;
}

void Adc_copyConfig(Adc_DriverObjType *drvObj, const Adc_ConfigType *cfgPtr)
{
    uint8                       hwUnitIdx, grpIdx, hwIdx;
    const Adc_HwUnitConfigType *hwCfg;
    Adc_GroupObjType           *groupObj;
    Adc_HwUnitObjType          *hwObj;
    const Adc_GroupConfigType  *groupCfg;
    uint32                      chIdx;
#if (STD_ON == ADC_DEV_ERROR_DETECT)
    Std_ReturnType retVal;
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

    drvObj->maxGroup  = cfgPtr->maxGroup;
    drvObj->maxHwUnit = cfgPtr->maxHwUnit;
    for (hwUnitIdx = 0U; hwUnitIdx < cfgPtr->maxHwUnit; hwUnitIdx++)
    {
        hwCfg = &cfgPtr->hwUnitCfg[hwUnitIdx];

        /* Copy configuration */
        (void)memcpy(&drvObj->hwUnitObj[hwUnitIdx].hwUnitCfg, hwCfg, sizeof(Adc_HwUnitConfigType));

        /* Reset the SOC pointer to last SOC. */
        hwObj           = &drvObj->hwUnitObj[hwUnitIdx];
        hwObj->socHwPtr = (uint16)(ADC_SOC_NUMBER15);
    }

    /* Initialize configured Interrupt Index. */
    for (hwUnitIdx = 0U; hwUnitIdx < ADC_HW_UNIT_CNT; hwUnitIdx++)
    {
        for (hwIdx = 0U; hwIdx < cfgPtr->maxHwUnit; hwIdx++)
        {
            if (hwUnitIdx == Adc_DrvObj.hwUnitObj[hwIdx].hwUnitCfg.hwUnitId)
            {
                Adc_HwSocGroupMapping[hwUnitIdx].adcHwUnit = hwIdx;
            }
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
            groupObj->groupCfg.groupId                  = groupCfg->groupId;
            groupObj->groupCfg.groupPriority            = groupCfg->groupPriority;
            groupObj->groupCfg.hwUnitId                 = groupCfg->hwUnitId;
            groupObj->groupCfg.Adc_GroupEndNotification = groupCfg->Adc_GroupEndNotification;
            groupObj->groupCfg.streamNumSamples         = groupCfg->streamNumSamples;
            groupObj->groupCfg.resolution               = groupCfg->resolution;
            groupObj->groupCfg.convMode                 = groupCfg->convMode;
            groupObj->groupCfg.triggSrc                 = groupCfg->triggSrc;
            groupObj->groupCfg.accessMode               = groupCfg->accessMode;
            groupObj->groupCfg.streamBufMode            = groupCfg->streamBufMode;
            groupObj->groupCfg.hwTrigSignal             = groupCfg->hwTrigSignal;
            groupObj->groupCfg.hwTrigTimer              = groupCfg->hwTrigTimer;
            groupObj->groupCfg.groupReplacement         = groupCfg->groupReplacement;
            groupObj->groupCfg.groupChannelMask         = groupCfg->groupChannelMask;
#if (STD_ON == ADC_ENABLE_LIMIT_CHECK)
            groupObj->groupCfg.grouplimitcheck = groupCfg->grouplimitcheck;
#endif
            groupObj->groupCfg.groupDataAccessMode = groupCfg->groupDataAccessMode;

            groupObj->groupCfg.numChannels = groupCfg->numChannels;

#if (STD_ON == ADC_DMA_MODE)
            groupObj->groupCfg.groupDmaChannelId = groupCfg->groupDmaChannelId;
#endif

            for (chIdx = 0U; chIdx < groupCfg->numChannels; chIdx++)
            {
                groupObj->groupCfg.channelConfig[chIdx] = groupCfg->channelConfig[chIdx];
            }

            /* Store HW object pointer for easy reference */
            groupObj->hwUnitObj = &Adc_DrvObj.hwUnitObj[groupCfg->hwUnitId];

            /* Reset the SOC to invalid. */
            groupObj->socAssigned       = (uint16)ADC_INVALID_HW_SOC;
            groupObj->lastSocAssigned   = (uint16)ADC_INVALID_HW_SOC;
            groupObj->groupInterruptSrc = (uint16)ADC_INVALID_HW_INT;

            /* All modes except one shot software trigger and linear streaming needs to be
             * stopped explicitly */
            Adc_copyConfig_ExplicitStopMode(groupObj, groupCfg);

#if (STD_ON == ADC_DMA_MODE)
            if (groupObj->groupCfg.groupDmaChannelId != 0xFFU)
            {
                /* Register the Adc module for all Groups. */
                Cdd_Dma_CbkRegister(groupObj->groupCfg.groupDmaChannelId, (void *)((uint32)groupObj->groupCfg.groupId),
                                    &Adc_IrqDmaTxRx);
            }
#endif

#if (STD_ON == ADC_DEV_ERROR_DETECT)
            /* Check channel configuration */
            Adc_copyConfig_Internal(groupCfg);
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
        }
#if (STD_ON == ADC_DEV_ERROR_DETECT)
        else
        {
            /* No Actions Required. */
        }
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    }

    return;
}

static void Adc_copyConfig_ExplicitStopMode(Adc_GroupObjType *groupObj, const Adc_GroupConfigType *groupCfg)
{
    groupObj->isExplicitStopMode = (uint32)ADC_TRUE;
    if ((groupCfg->triggSrc == ADC_TRIGG_SRC_SW) && (ADC_CONV_MODE_ONESHOT == groupCfg->convMode))
    {
        groupObj->isExplicitStopMode = (uint32)ADC_FALSE;
    }

    if ((ADC_ACCESS_MODE_STREAMING == groupCfg->accessMode) && (ADC_STREAM_BUFFER_LINEAR == groupCfg->streamBufMode))
    {
        groupObj->isExplicitStopMode = (uint32)ADC_FALSE;
    }
}

static void Adc_copyConfig_Internal(const Adc_GroupConfigType *groupCfg)
{
    uint32                       chIdx = 0;
    const Adc_ChannelConfigType *chCfg;
    for (chIdx = 0U; chIdx < groupCfg->numChannels; chIdx++)
    {
        chCfg = &groupCfg->channelConfig[chIdx];
        Adc_checkChannelParams(chCfg);
    }
}

uint32 Adc_checkHwUnitObj(const Adc_ConfigType *cfgPtr)
{
    uint8                       hwUnitIdx = 0U;
    const Adc_HwUnitConfigType *hwCfg;
    uint32                      found = (uint32)ADC_FALSE;

    for (hwUnitIdx = 0U; hwUnitIdx < cfgPtr->maxHwUnit; hwUnitIdx++)
    {
        hwCfg = &cfgPtr->hwUnitCfg[hwUnitIdx];
        if (hwCfg->hwUnitId < ADC_MAX_HW_UNIT)
        {
            found = (uint32)ADC_TRUE;
            break; /* Match found */
        }
    }

    return (found);
}

static Std_ReturnType Adc_startGroupCheckStatus(const Adc_GroupObjType *groupObj)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    if (((uint32)ADC_TRUE) == groupObj->isExplicitStopMode)
    {
        /* For explicit stop mode, group in idle status can be started */
        if (ADC_IDLE != groupObj->groupStatus)
        {
            /* Group is already in progress - return error */
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        /* For implicit stop mode, group in idle or stream completed status
         * can be started */
        if ((ADC_IDLE != groupObj->groupStatus) && (ADC_STREAM_COMPLETED != groupObj->groupStatus))
        {
            /* Group is already in progress - return error */
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return retVal;
}

/* check channel parameters */
#if (STD_ON == ADC_DEV_ERROR_DETECT)
void Adc_checkChannelParams(const Adc_ChannelConfigType *chCfg)
{
    if (chCfg->hwChannelId > ADC_MAX_HW_CHANNEL_ID)
    {
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }
    return;
}

#endif

#if (STD_ON == ADC_DEV_ERROR_DETECT)

static Std_ReturnType Adc_checkGroupParametersDet_SW(const Adc_GroupConfigType *groupCfg)
{
    boolean ret = FALSE;

    if (groupCfg->streamNumSamples == 0U)
    {
        ret = TRUE;
    }

    /*Checking the access mode*/
    if ((ADC_ACCESS_MODE_SINGLE == groupCfg->accessMode) && (groupCfg->streamNumSamples != 1U))
    {
        ret = TRUE;
    }

    /*Checking the coversion mode*/
    if ((ADC_CONV_MODE_ONESHOT == groupCfg->convMode) && (groupCfg->accessMode != ADC_ACCESS_MODE_SINGLE))
    {
        ret = TRUE;
    }

    return ret;
}

static boolean Adc_checkGroupParametersDet_HW(const Adc_GroupConfigType *groupCfg)
{
    boolean ret = FALSE;

    if (groupCfg->streamNumSamples == 0U)
    {
        ret = TRUE;
    }

    /* Chcking the acess mode*/
    if ((ADC_ACCESS_MODE_SINGLE == groupCfg->accessMode) && (groupCfg->streamNumSamples != 1U))
    {
        ret = TRUE;
    }

    return ret;
}

static Std_ReturnType Adc_checkGroupParameters(const Adc_GroupConfigType *groupCfg, const Adc_ConfigType *cfgPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    /* ID is used as index, can't exceed array size */
    if (groupCfg->groupId >= cfgPtr->maxGroup)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }
    else if (NULL_PTR == Adc_getHwUnitObj(groupCfg->hwUnitId))
    {
        /* DET already reported by Adc_getHwUnitObj() */
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        retVal = Adc_checkGroupCfgRangeParameters(groupCfg);
    }

    /* Check if, the group is software triggered. */
    if (groupCfg->triggSrc == ADC_TRIGG_SRC_SW)
    {
        /* check group parameters */
        if (TRUE == Adc_checkGroupParametersDet_SW(groupCfg))
        {
            retVal = (Std_ReturnType)E_NOT_OK;
            Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);

            /* Dynamic MC/DC coverage for the above 'if' statement is not covered 100%
             * because MC/DC cannot be achieved for C5. The only combination to achieve
             * 100% coverage is when both C2 and C5 are either ADC_TRUE or ADC_FALSE and this
             * is not possible as the condition C2 and C5 cannot be ADC_TRUE or ADC_FALSE
             * at the same time.
             */
        }
    }
    else
    {
        /* check group parameters */
        if (TRUE == Adc_checkGroupParametersDet_HW(groupCfg))
        {
            retVal = (Std_ReturnType)E_NOT_OK;
            Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);

            /* Dynamic MC/DC coverage for the above 'if' statement is not covered 100%
             * because MC/DC cannot be achieved for C5. The only combination to achieve
             * 100% coverage is when both C2 and C5 are either ADC_TRUE or ADC_FALSE and this
             * is not possible as the condition C2 and C5 cannot be ADC_TRUE or ADC_FALSE
             * at the same time.
             */
        }
    }

    return retVal;
}

#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

#if (STD_ON == ADC_DEV_ERROR_DETECT)
static Std_ReturnType Adc_checkGroupCfgRangeParameters(const Adc_GroupConfigType *groupCfg)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    if (0U == groupCfg->numChannels)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }

    if (groupCfg->numChannels > ADC_NUM_CHANNEL)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }

    if (groupCfg->resolution != ADC_DEF_CHANNEL_RESOLUTION)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_INIT, ADC_E_PARAM_CONFIG);
    }

    return retVal;
}

#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

static void Adc_scheduleGroup(Adc_GroupObjType *groupObj)
{
    uint32              chIdx;
    Adc_HwUnitObjType  *hwUnitObj;
    Adc_ValueGroupType *tempResultBufPtr;
#if (STD_ON == ADC_GROUP_LOG)
    Adc_GroupLogEntryType *logEntry;
#endif /* #if (STD_ON == ADC_GROUP_LOG) */

    hwUnitObj = groupObj->hwUnitObj;

    /*Reset the GroupObj if it is Pasues*/
    if (((uint32)ADC_TRUE) == groupObj->isPaused)
    {
        Adc_resetGroupObjOnResume(groupObj);
    }
    else
    {
        /* Set the states for normal start */
        groupObj->validSampleCount = 0U;
        groupObj->curCh            = 0U;
        tempResultBufPtr           = (Adc_ValueGroupType *)groupObj->resultBufPtr;
        for (chIdx = 0U; chIdx < groupObj->groupCfg.numChannels; chIdx++)
        {
            groupObj->chObj[chIdx].chResultBufPtr  = tempResultBufPtr;
            groupObj->chObj[chIdx].curResultBufPtr = tempResultBufPtr;
            groupObj->chObj[chIdx].curNumSamples   = 0U;

            /* Move to next channel buffer */
            tempResultBufPtr += groupObj->groupCfg.streamNumSamples;
        }
    }
#if (STD_ON == ADC_GROUP_LOG)
    /* Log the group */
    logEntry = &Adc_GroupLogObj.logEntry[Adc_GroupLogObj.logIndex];

    logEntry->timeStamp     = 0U;
    logEntry->groupId       = groupObj->groupCfg.groupId;
    logEntry->hwUnitId      = hwUnitObj->hwUnitCfg.hwUnitId;
    logEntry->isReScheduled = groupObj->isPaused;

    /* Move to next entry */
    Adc_GroupLogObj.logIndex++;
    Adc_GroupLogObj.totalLog++;
    if (Adc_GroupLogObj.logIndex >= ADC_MAX_GROUP_LOG)
    {
        Adc_GroupLogObj.logIndex = 0U;
    }
#endif /* #if (STD_ON == ADC_GROUP_LOG) */

    groupObj->isPaused = (uint32)ADC_FALSE; /* Reset flag after log */

    /* Configure ADC steps and start conversion */
    Adc_hwConfig(groupObj, hwUnitObj->baseAddr);
    Adc_hwStart(hwUnitObj->baseAddr);

    return;
}

static void Adc_checkAndSchedule(Adc_HwUnitObjType *hwUnitObj)
{
    Adc_UtilsNode    *headNodeObj;
    Adc_GroupObjType *nextGroupObj;
    Std_ReturnType    retVal = E_OK;

    /* Check if any new group is pending */
    headNodeObj = Adc_utilsGetHeadNode(&hwUnitObj->groupList);
    if (NULL_PTR != headNodeObj)
    {
        /* Some group pending - schedule it */
        nextGroupObj = (Adc_GroupObjType *)headNodeObj->data;
        Adc_utilsUnLinkNodePri((&(hwUnitObj->groupList)), headNodeObj);
        nextGroupObj->isQueued = (uint32)ADC_FALSE;

        hwUnitObj->swGroupSchduled = ADC_TRUE;

        if (((uint16)(((uint16)(ADC_SOC_NUMBER15)) - hwUnitObj->socHwPtr + nextGroupObj->groupCfg.numChannels)) <=
            ((uint16)(ADC_SOC_NUMBER15)))
        {
            /* Assign the Queue number. */
            retVal = Adc_checkAndSchedule_Internal(hwUnitObj, nextGroupObj);
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }

        if (retVal == E_OK)
        {
            /* Schedule Group. */
            Adc_scheduleGroup(nextGroupObj);
        }
        else
        {
            /* Some high priority group already on-going - queue this to
             * hardware queue */
            nextGroupObj->groupStatus = ADC_BUSY;
            nextGroupObj->isQueued    = (uint32)ADC_TRUE;
            Adc_utilsLinkNodePri(&hwUnitObj->groupList, &nextGroupObj->nodeObj, nextGroupObj,
                                 nextGroupObj->groupCfg.groupPriority, ADC_FALSE);
        }
    }
    return;
}

static Std_ReturnType Adc_checkAndSchedule_Internal(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *nextGroupObj)
{
    Std_ReturnType retVal         = E_OK;
    nextGroupObj->lastSocAssigned = hwUnitObj->socHwPtr;
    if (nextGroupObj->groupCfg.numChannels == 1U)
    {
        nextGroupObj->socAssigned = hwUnitObj->socHwPtr;
    }
    else
    {
        nextGroupObj->socAssigned =
            (uint16)(((uint16)(hwUnitObj->socHwPtr)) - ((uint16)(nextGroupObj->groupCfg.numChannels) - (uint16)1U));
    }

    hwUnitObj->socHwPtr = (uint16)(((uint16)nextGroupObj->socAssigned) - 1U);

    /* Check if Interrupt is Valid. */
    if (hwUnitObj->numHwGroupsQue >= ((uint16)ADC_INVALID_HW_INT))
    {
        retVal = (Std_ReturnType)E_NOT_OK;

        /* Check if Group is HW or SW triggered group. */
        if (nextGroupObj->groupCfg.triggSrc == ADC_TRIGG_SRC_SW)
        {
            Adc_reportDetRuntimeError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
        }
    }
    else
    {
        hwUnitObj->numHwGroupsQue++;
        nextGroupObj->groupInterruptSrc = hwUnitObj->numHwGroupsQue;
        hwUnitObj->curGroupObj          = nextGroupObj;
    }
    return (retVal);
}

static void Adc_procIsr(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *groupObj)
{
    uint32              convComplete   = (uint32)ADC_FALSE;
    uint32              streamComplete = (uint32)ADC_FALSE;
    uint16              data, numChannels, channnelPtr;
    Adc_ChannelObjType *chObj;
    uint32              socAssigned;
    Adc_ValueGroupType *resultBufPtrCh;

#if (ADC_ALIGN_LEFT == ADC_RESULT_ALIGNMENT)
    uint16 data2, shiftResol;
#endif /* #if (ADC_ALIGN_LEFT == ADC_RESULT_ALIGNMENT) */

    socAssigned = (uint32)groupObj->socAssigned;

    /* Check the mode of Group. */
    if (groupObj->groupCfg.accessMode == ADC_ACCESS_MODE_SINGLE)
    {
        /* Get Number of channels to be stored  */
        numChannels    = (uint16)groupObj->groupCfg.numChannels;
        channnelPtr    = 0;
        resultBufPtrCh = (Adc_ValueGroupType *)groupObj->resultBufPtr;

        while (numChannels > 0U)
        {
            /* Get the Data. */
            data = (uint16)ADC_readResult(hwUnitObj->resultBaseAddr, (uint32)socAssigned);

#if (ADC_ALIGN_LEFT == ADC_RESULT_ALIGNMENT)
            shiftResol = (ADC_MAX_CHANNEL_VALUE_TYPE - groupObj->groupCfg.resolution);
            data2      = (uint16)((uint32)data << (uint32)shiftResol);
            data       = data2;
#endif /* #if (ADC_ALIGN_LEFT == ADC_RESULT_ALIGNMENT) */

            /* Get the Increment the Data ptr. */
            socAssigned++;

            /* Fill data to result buffer. */
            resultBufPtrCh[channnelPtr] = data;

            /* Point to next channel. */
            channnelPtr++;
            numChannels--;
        }

        /* Stop the conversion, if required. */
        convComplete = (uint32)ADC_TRUE;

        /* Check if group needs to stopped. */
        if ((((uint32)ADC_FALSE) == groupObj->isExplicitStopMode) || (ADC_TRIGG_SRC_HW == groupObj->groupCfg.triggSrc))
        {
            streamComplete = (uint32)ADC_TRUE;
        }
    }
    else
    {
        /* Get Number of Samples to be stored  */
        numChannels     = (uint16)groupObj->groupCfg.numChannels;
        groupObj->curCh = 0;

        /* Read all the samples. */
        while (numChannels > 0U)
        {
            data = (uint16)ADC_readResult(hwUnitObj->resultBaseAddr, (uint32)socAssigned);
            socAssigned++;

            chObj                   = &groupObj->chObj[groupObj->curCh];
            *chObj->curResultBufPtr = data;

            /* Move to next buffer pointer for the channel */
            chObj->curNumSamples++;
            chObj->curResultBufPtr++;
            if ((chObj->curResultBufPtr) >= (chObj->chResultBufPtr + (groupObj->groupCfg.streamNumSamples)))
            {
                chObj->curNumSamples   = 0U;
                chObj->curResultBufPtr = chObj->chResultBufPtr;
            }

            /* Move to next channel */
            groupObj->curCh++;
            if (groupObj->curCh >= groupObj->groupCfg.numChannels)
            {
                Adc_procIsr_Internal(&convComplete, groupObj, &streamComplete, chObj);
            }
            numChannels--;
        }
    }

    /* Set Group Status and Call group end notification */
    Adc_setGroupStatusPostIsr(hwUnitObj, groupObj, convComplete, streamComplete);

    return;
}

static void Adc_procIsr_Internal(uint32 *convComplete, Adc_GroupObjType *groupObj, uint32 *streamComplete,
                                 Adc_ChannelObjType *chObj)
{
    /* All channel conversion completed */
    groupObj->curCh = 0U;
    /* Increment valid count and limit to stream max samples */
    groupObj->validSampleCount++;
    if (groupObj->validSampleCount > ((uint32)groupObj->groupCfg.streamNumSamples))
    {
        /* This happens if app fails to read data faster than driver
         * generates */
        groupObj->validSampleCount = (uint32)groupObj->groupCfg.streamNumSamples;
    }
    /* Check if all streams are completed - check last channel pointer.
     * If it is at start then stream completed */
    *convComplete = (uint32)ADC_TRUE;
    if (chObj->curResultBufPtr == chObj->chResultBufPtr)
    {
        *streamComplete = (uint32)ADC_TRUE;
        /* Incase of one-shot/linear stream, stop conversion and
         * don't update the buffers - break from reading the FIFO and
         * storing data */
        if (((uint32)ADC_FALSE) == groupObj->isExplicitStopMode)
        {
            /*break;*/
        }
    }
}

static void Adc_setGroupStatusPostIsr(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *groupObj, uint32 convComplete,
                                      uint32 streamComplete)
{
    Adc_GroupEndNotifyType groupEndNotification = NULL;
    if (((uint32)ADC_TRUE) == convComplete)
    {
        /* Set group status */
        if (((uint32)ADC_TRUE) == streamComplete)
        {
            /* Conversion over for all channels and all streams */
            groupObj->groupStatus = ADC_STREAM_COMPLETED;
        }
        else
        {
            /* Atleast one set of conversion over for all channels */
            groupObj->groupStatus = ADC_COMPLETED;
        }

        if (groupObj->groupCfg.groupDataAccessMode != ADC_GROUP_POLLING_ACCESS)
        {
            /* Call group end notification */
            if ((((uint32)ADC_TRUE) == groupObj->isNotifyOn) &&
                ((Adc_GroupEndNotifyType)NULL_PTR != groupObj->groupCfg.Adc_GroupEndNotification))
            {
                groupEndNotification = groupObj->groupCfg.Adc_GroupEndNotification;
                groupEndNotification();

                /* Dynamic MC/DC coverage for the above 'if' statement is not covered 100%
                 * because MC/DC cannot be achieved for C2. The only combination to achieve
                 * 100% coverage is when C1 is ADC_TRUE and C2 is ADC_FALSE and this is not possible
                 * because if isNotifyOn is ADC_TRUE then groupCfg.Adc_GroupEndNotification is
                 * assigned to a callback fxn pointer.
                 */
            }
        }

        /* Stop ADC in case of one-shot/linear stream */
        if ((((uint32)ADC_TRUE) == streamComplete) && (((uint32)ADC_FALSE) == groupObj->isExplicitStopMode))
        {
            Adc_setGroupStatusPostIsrStopADC(hwUnitObj, groupObj);

#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || \
     ((ADC_PRIORITY_NONE == ADC_PRIORITY_IMPLEMENTATION) && (ADC_ENABLE_QUEUING == STD_ON)))
            /* Check and schedule any pending groups for this HW */
            Adc_checkAndSchedule(hwUnitObj);
#endif
        }

        if ((groupObj->groupCfg.triggSrc == ADC_TRIGG_SRC_HW) && (((uint32)ADC_TRUE) == groupObj->isExplicitStopMode))
        {
#if ((ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION) || \
     ((ADC_PRIORITY_NONE == ADC_PRIORITY_IMPLEMENTATION) && (ADC_ENABLE_QUEUING == STD_ON)))
            /* Check and schedule any pending groups for this HW */
            Adc_checkAndSchedule(hwUnitObj);
#endif
        }
    }
    return;
}

static void Adc_setGroupStatusPostIsrStopADC(Adc_HwUnitObjType *hwUnitObj, Adc_GroupObjType *groupObj)
{
    Adc_hwStop(hwUnitObj->baseAddr, groupObj);

    hwUnitObj->socHwPtr = (uint16)(hwUnitObj->socHwPtr + (uint16)groupObj->groupCfg.numChannels);
    if (hwUnitObj->numHwGroupsQue > 0U)
    {
        hwUnitObj->numHwGroupsQue--;
    }

    if (((uint16)ADC_INVALID_HW_SOC) <= hwUnitObj->socHwPtr)
    {
        hwUnitObj->socHwPtr = (uint16)ADC_SOC_NUMBER15;
    }
    else
    {
        /* No Actions Required. */
    }
    groupObj->socAssigned     = (uint16)ADC_INVALID_HW_SOC;
    groupObj->lastSocAssigned = (uint16)ADC_INVALID_HW_SOC;

    /* Check if Group is same as HW Unit Current Group */
    if (groupObj->groupCfg.groupId == hwUnitObj->curGroupObj->groupCfg.groupId)
    {
        hwUnitObj->curGroupObj = NULL;
    }
}

static void Adc_resetGroupObjOnResume(Adc_GroupObjType *groupObj)
{
    uint32 chIdx;

    /* When we re-start, the ADC will start conversion from 0th chan, so
     * un-do previous conversion if half-way through */
    for (chIdx = 0U; chIdx < groupObj->curCh; chIdx++)
    {
        if (groupObj->chObj[chIdx].curNumSamples > 0U)
        {
            groupObj->chObj[chIdx].curNumSamples--;
            groupObj->chObj[chIdx].curResultBufPtr--;

            /* Handle wrap around */
            if ((groupObj->chObj[chIdx].curResultBufPtr) < (groupObj->chObj[chIdx].chResultBufPtr))
            {
                /* We were at start pointer, so move to last pointer */
                groupObj->chObj[chIdx].curResultBufPtr =
                    groupObj->chObj[chIdx].chResultBufPtr + (groupObj->groupCfg.streamNumSamples - 1U);

                /* Dynamic Code coverage for this statement is not covered
                 * because curResultBufPtr cannot be less than chResultBufPtr.
                 * This 'if statement' is added as an additional safety mechanism.
                 */
            }
        }
    }

    /* Set the Current channel to 0 */
    groupObj->curCh = 0U;

    return;
}

static void Adc_hwConfig(const Adc_GroupObjType *groupObj, uint32 baseAddr)
{
    uint32                       chnlId, socInc, adcSoc;
    uint32                       threshold;
    uint16                       groupMask = 0U, adcLastSoc;
    const Adc_GroupConfigType   *groupCfg;
    const Adc_ChannelConfigType *chCfg;
    Adc_HwSocObjType            *socPtr;
    Adc_HwUnitObjType           *adchwUnitObj;
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    Adc_mcalPPBNumber_t chobj;
#endif
    adchwUnitObj = groupObj->hwUnitObj;

#if (STD_ON == ADC_DMA_MODE)
    uint32 dmaDataAddr;
#endif

    groupCfg   = &groupObj->groupCfg;
    adcSoc     = groupObj->socAssigned;
    adcLastSoc = groupObj->lastSocAssigned;
    socInc     = (uint32)adcSoc;
    socPtr     = &Adc_HwSocGroupMapping[adchwUnitObj->hwUnitCfg.hwUnitId];

#if ((ADC_PRIORITY_NONE == ADC_PRIORITY_IMPLEMENTATION) && (ADC_ENABLE_QUEUING == STD_ON))
    /* Set the Priority to SOC.*/
    ADC_setSOCPriority(baseAddr, (uint16)ADC_PRI_ALL_ROUND_ROBIN);
#endif

#if ((ADC_PRIORITY_HW == ADC_PRIORITY_IMPLEMENTATION) || (ADC_PRIORITY_HW_SW == ADC_PRIORITY_IMPLEMENTATION))
    /* Set the Priority to SOC.*/
    ADC_setSOCPriority(baseAddr, (uint16)((uint16)adcLastSoc + (uint16)1U));
#endif

    /* Number of channels to every conversion of all channels */
    threshold = groupCfg->numChannels - 1U;

    for (chnlId = 0U; chnlId <= threshold; chnlId++)
    {
        chCfg                         = &groupCfg->channelConfig[chnlId];
        socPtr->adcHwSocGroup[adcSoc] = groupCfg->groupId;

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        if (ADC_TRUE == groupObj->groupCfg.grouplimitcheck)
        {
            /* Clear the Status Register. */
            HW_WR_REG16((baseAddr + MCAL_CSL_ADC_ADCEVTCLR), 0xFFFF);

            switch ((chnlId + 1U))
            {
                case 1:
                    chobj = ADC_PPB_NUMBER1;
                    break;

                case 2:
                    chobj = ADC_PPB_NUMBER2;
                    break;

                case 3:
                    chobj = ADC_PPB_NUMBER3;
                    break;

                case 4:
                    chobj = ADC_PPB_NUMBER4;
                    break;

                default:
                    chobj = ADC_PPB_NUMBER1;
                    break;
            }

            /* Setup the PPB . */
            ADC_setupPPB(baseAddr, (Adc_mcalPPBNumber_t)(chobj), (uint16)adcSoc);

            /* Set the Channel Limits. */
            ADC_setPPBTripLimits(baseAddr, (Adc_mcalPPBNumber_t)(chobj), chCfg->highRange, chCfg->lowRange);
        }

#endif

        ADC_setupSOC(baseAddr, adcSoc, groupCfg->hwTrigTimer, chCfg->hwChannelId, chCfg->samplewindow);

        ADC_setInterruptSOCTrigger(baseAddr, (uint16)adcSoc, ADC_INT_SOC_TRIGGER_NONE);

        groupMask |= (1U << socInc);
        socInc++;
        adcSoc = socInc;
    }

    /* Check the access mode. */
    switch (groupObj->groupCfg.groupDataAccessMode)
    {
        case ADC_GROUP_INTERRUPT_ACCESS:
        case ADC_GROUP_POLLING_ACCESS:
        {
            /* Clear all previous interrupt status */
            Adc_hwConfig_check_accessMode(groupObj, baseAddr, groupMask, adcLastSoc, groupCfg);
        }
        break;

        case ADC_GROUP_DMA_ACCESS:
        {
#if (STD_ON == ADC_DMA_MODE)
            /* Clear all previous interrupt status */
            ADC_clearInterruptStatus(baseAddr, (uint16)groupObj->groupInterruptSrc);

            /* Set the ADC Group Last Channel with  Interrupt trigger.*/
            ADC_setInterruptSource(baseAddr, groupObj->groupInterruptSrc, adcLastSoc);

            /* Check if, Group conversion mode. */
            if (ADC_CONV_MODE_ONESHOT != groupCfg->convMode)
            {
                ADC_setInterruptSOCTrigger(baseAddr, (uint16)adcLastSoc, ADC_INT_SOC_TRIGGER_ADCINT1);

                ADC_enableContinuousMode(baseAddr, groupObj->groupInterruptSrc);
            }

            /* Enable required interrupts */
            ADC_enableInterrupt(baseAddr, groupObj->groupInterruptSrc);

            /* Get the Address. */
            dmaDataAddr = ADC_readResultbaseaddr(adchwUnitObj->resultBaseAddr, groupObj->socAssigned);

            /* Check if, CDD is Initialized. */
            if (ADC_TRUE == Cdd_Dma_GetInitStatus())
            {
                if (groupObj->groupCfg.groupDmaChannelId != 0xFFU)
                {
                    /* Configure ADC DMA Channel for each ADC channel.  */
                    AdcDma_ModuleChannelConfigure((const uint16 *)(groupObj->resultBufPtr),
                                                  (groupObj->groupCfg.numChannels * 2),
                                                  groupObj->groupCfg.groupDmaChannelId, dmaDataAddr);
                }
            }

            if (groupCfg->triggSrc == ADC_TRIGG_SRC_SW)
            {
                /* Start ADC */
                ADC_forceMultipleSOC(baseAddr, groupMask);
            }
#endif
        }
        break;
        default:
            /* Do nothing*/
            break;
    }

    return;
}

static void Adc_hwConfig_check_accessMode(const Adc_GroupObjType *groupObj, uint32 baseAddr, uint16 groupMask,
                                          uint16 adcLastSoc, const Adc_GroupConfigType *groupCfg)
{
    ADC_clearInterruptStatus(baseAddr, (uint16)groupObj->groupInterruptSrc);
    ADC_disableInterrupt(baseAddr, groupObj->groupInterruptSrc);
    /* Check if, Group conversion mode. */
    if (groupCfg->convMode != ADC_CONV_MODE_ONESHOT)
    {
        ADC_setInterruptSOCTrigger(baseAddr, (uint16)adcLastSoc, ADC_INT_SOC_TRIGGER_ADCINT1);
        ADC_enableContinuousMode(baseAddr, groupObj->groupInterruptSrc);
    }

    /* Enable required interrupts */
    ADC_enableInterrupt(baseAddr, groupObj->groupInterruptSrc);

    /* Set the ADC Group Last Channel with  Interrupt trigger.*/
    ADC_setInterruptSource(baseAddr, groupObj->groupInterruptSrc, adcLastSoc);

    if (groupCfg->triggSrc == ADC_TRIGG_SRC_SW)
    {
        /* Start ADC */
        ADC_forceMultipleSOC(baseAddr, groupMask);
    }
}

static void Adc_hwStart(uint32 baseAddr)
{
    /* Enable Converter. */
    return;
}

static void Adc_hwStop(uint32 baseAddr, const Adc_GroupObjType *groupObj)
{
    const Adc_GroupConfigType *groupCfg;
    uint8                      ChnlId;

    groupCfg = &groupObj->groupCfg;

    /* Disable  */
    ADC_disableInterrupt(baseAddr, groupObj->groupInterruptSrc);
    ADC_clearInterruptStatus(baseAddr, (uint16)groupObj->groupInterruptSrc);

    if (groupCfg->convMode != ADC_CONV_MODE_ONESHOT)
    {
        /* Stop ADC in continuous mode. */
        ADC_disableContinuousMode(baseAddr, groupObj->groupInterruptSrc);
    }

    for (ChnlId = 0U; ChnlId < groupCfg->numChannels; ChnlId++)
    {
        /* Check if, Group conversion mode. */
        if (groupCfg->convMode != ADC_CONV_MODE_ONESHOT)
        {
            ADC_setInterruptSOCTrigger(baseAddr, (uint16)ChnlId, ADC_INT_SOC_TRIGGER_NONE);
        }
    }

#if (STD_ON == ADC_DMA_MODE)
    Cdd_Dma_DisableTransferRegion(groupObj->groupCfg.groupDmaChannelId, CDD_EDMA_TRIG_MODE_EVENT);
#endif
    return;
}

static void Adc_hwSetDefReg(uint32 baseAddr)
{
    uint32 index;

    /* Power down analog Front End */
    ADC_disableConverter(baseAddr);

    /* Reset the Registers. */
    for (index = 0U; index <= ((uint32)0x04); index++)
    {
        ADC_disableContinuousMode(baseAddr, index);
        ADC_clearInterruptStatus(baseAddr, (uint16)index);
        ADC_clearInterruptOverflowStatus(baseAddr, (uint16)index);
    }
    return;
}

#if (STD_ON == ADC_DMA_MODE)
/* Configures the DMA Channel to particular external module register. */
boolean AdcDma_ModuleChannelConfigure(const uint16 *table, uint16 table_size, uint32 dma_ch, uint32 srceaddr)
{
    Cdd_Dma_ParamEntry edmaParam;

    edmaParam.srcPtr     = (void *)(srceaddr);
    edmaParam.destPtr    = (void *)(table);
    edmaParam.aCnt       = (uint16)(table_size);
    edmaParam.bCnt       = (uint16)1;
    edmaParam.cCnt       = (uint16)1;
    edmaParam.bCntReload = 0;
    edmaParam.srcBIdx    = (sint16)0;
    edmaParam.destBIdx   = (sint16)2;
    edmaParam.srcCIdx    = (sint16)0;
    edmaParam.destCIdx   = (sint16)2;
    edmaParam.opt        = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK);
    Cdd_Dma_ParamSet(dma_ch, 0, 0, edmaParam);
    Cdd_Dma_EnableTransferRegion(dma_ch, CDD_EDMA_TRIG_MODE_EVENT);

    return 1;
}
#endif

#if (STD_ON == ADC_DEV_ERROR_DETECT)
void Adc_reportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, apiId, errorId);
    return;
}

#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */

void Adc_reportDetRuntimeError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportRuntimeError(ADC_MODULE_ID, ADC_INSTANCE_ID, apiId, errorId);
    return;
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
    baseAddr = hwUnitObj->baseAddr;

    /*Get the Register value*/
    RegRbPtr->adcCtrl1 = HW_RD_REG16(baseAddr + MCAL_CSL_ADC_ADCCTL1);
    RegRbPtr->adcCtrl2 = HW_RD_REG16(baseAddr + MCAL_CSL_ADC_ADCCTL2);
}
#endif /*STD_ON == ADC_REGISTER_READBACK_API*/

/*Dummy internal function added for re-aerchitecture*/
void Adc_getChannelMuxParams(Adc_DriverObjType *drvObj)
{ /* do nothing */
}

/*Dummy internal function added for re-aerchitecture*/
void Adc_performHwInit(void)
{ /* do nothing */
}

/*Dummy internal function added for re-aerchitecture*/
void Adc_performHwDeInit(void)
{ /* do nothing */
}

Std_ReturnType Adc_groupConversionDoneHandler(void)
{
    /* do nothing */
    return E_OK;
}

void Adc_FillDataBufferPtr(Adc_ValueGroupType *DataBufferPtr, Adc_GroupObjType *groupObj)
{
    Adc_ChannelObjType *chObj;
    Adc_ChannelObjType *chObjLast;
    uint32              offset;
    uint32              chIdx;

    /*
     * State equals ADC_COMPLETED or ADC_STREAM_COMPLETED, so
     * results are available: start reading group
     */

    /* Use the last channel pointers to calculate last result
     * pointer as this represents a completion of a set of all
     * channels. If we use any other channel, we could be half way
     * through and might return pointer one location extra */
    chObjLast = &groupObj->chObj[groupObj->groupCfg.numChannels - 1U];

    if ((chObjLast->curResultBufPtr) <= (chObjLast->chResultBufPtr))
    {
        /* Pointer is at first element, so offset is last sample */
        offset = (uint32)groupObj->groupCfg.streamNumSamples - 1U;
    }
    else
    {
        offset = chObjLast->curResultBufPtr - chObjLast->chResultBufPtr;
        /* The next result will be written at position [n],
         * so the latest result in buffer is at [n-1] */
        offset--;
    }

    for (chIdx = 0U; chIdx < groupObj->groupCfg.numChannels; chIdx++)
    {
        chObj                = &groupObj->chObj[chIdx];
        DataBufferPtr[chIdx] = chObj->chResultBufPtr[offset];
    }

    /* Reset ValidSampleCount after read process */
    groupObj->validSampleCount = 0U;

    /* State transition after reading to buffer */
    if (ADC_COMPLETED == groupObj->groupStatus)
    {
        /* Conversion has not been finished, when the group
         * was read. State transition to ADC_BUSY */
        groupObj->groupStatus = ADC_BUSY;
    }
    else
    {
        /*
         * ADC_STREAM_COMPLETED State
         */

        /* Conversion has been finished before the group was read.
         * State transition to ADC_IDLE if the group stops
         * implicitly or to ADC_BUSY if the group has to be
         * stopped explicitly.
         */
        if (((uint32)ADC_TRUE) == groupObj->isExplicitStopMode)
        {
            /* Group has to be stopped explicitly, so conversion is
             * going on after this read. */
            groupObj->groupStatus = ADC_BUSY;
        }
        else
        {
            /* Group stops implicitly when ADC_STREAM_COMPLETED is
             * reached and the group is read. */
            groupObj->groupStatus = ADC_IDLE;
        }
    }
}

Std_ReturnType Adc_getStreamPtrCheckDetError(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr)
{
    Std_ReturnType    retVal = (Std_ReturnType)E_OK;
    Adc_GroupObjType *groupObj;
    uint8             Avoid_Nesting = 0U;

#if (STD_ON == ADC_DEV_ERROR_DETECT)
    if (Group >= Adc_DrvObj.maxGroup)
    {
        if (NULL_PTR != PtrToSamplePtr)
        {
            *PtrToSamplePtr = (Adc_ValueGroupType *)NULL_PTR;
        }
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_GET_STREAM_LAST_POINTER,
                           ADC_E_PARAM_GROUP); /* Report DET if group provided exceeds maximum groups*/
        Avoid_Nesting = 1U;
    }
    if ((NULL_PTR == PtrToSamplePtr) && (Avoid_Nesting == 0U))
    {
        /* Note: This error return is not mentioned in spec */
        retVal = (Std_ReturnType)E_NOT_OK;
        Adc_reportDetError(ADC_SID_GET_STREAM_LAST_POINTER,
                           ADC_E_PARAM_POINTER); /* Report DET if PtrToSamplePtr is NULL */
    }
    else
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
    {
        groupObj = &Adc_DrvObj.groupObj[Group];
        if (ADC_IDLE == groupObj->groupStatus)
        {
            if (PtrToSamplePtr != NULL_PTR)
            {
                *PtrToSamplePtr = (Adc_ValueGroupType *)NULL_PTR;
            }
            retVal = (Std_ReturnType)E_NOT_OK;
            Adc_reportDetRuntimeError(ADC_SID_GET_STREAM_LAST_POINTER,
                                      ADC_E_IDLE); /* Report DET if required group to get stream pointer is idle */
        }
    }

    if (Avoid_Nesting == 1U)
    {
        /* To clear the build issue */
    }

    return retVal;
}

Adc_StreamNumSampleType Adc_GetStreamLastPointerinternal(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr)
{
    Adc_ChannelObjType     *chObjLast;
    uint32                  offset;
    Adc_GroupObjType       *groupObj   = (Adc_GroupObjType *)NULL_PTR;
    Adc_StreamNumSampleType numSamples = 0;

    groupObj = &Adc_DrvObj.groupObj[Group];
    if (ADC_BUSY == groupObj->groupStatus)
    {
        *PtrToSamplePtr = (Adc_ValueGroupType *)NULL_PTR;
    }
    else
    {
        numSamples = (Adc_StreamNumSampleType)groupObj->validSampleCount;
        /* Reset ValidSampleCount after read process */
        groupObj->validSampleCount = 0U;

        /* Use the last channel pointers to calculate last result
         * pointer as this represents a completion of a set of all
         * channels. If we use any other channel, we could be half way
         * through and might return pointer one location extra */
        chObjLast = &groupObj->chObj[groupObj->groupCfg.numChannels - 1U];
        if ((chObjLast->curResultBufPtr) <= (chObjLast->chResultBufPtr))
        {
            /* Pointer is at first element, so offset is last sample */
            offset = (uint32)groupObj->groupCfg.streamNumSamples - 1U;
        }
        else
        {
            offset = chObjLast->curResultBufPtr - chObjLast->chResultBufPtr;
            /* The next result will be written at position [n],
             * so the latest result in buffer is at [n-1] */
            offset--;
        }
        /* Let PtrToSamplePtr refer to the latest element in
         * application result buffer. */
        *PtrToSamplePtr = (Adc_ValueGroupType *)&groupObj->resultBufPtr[offset];

        /* State transition after getting StreamLastPointer */
        if (ADC_COMPLETED == groupObj->groupStatus)
        {
            /* Conversion has not been finished, when the group
             * was read. State transition to ADC_BUSY */
            groupObj->groupStatus = ADC_BUSY;
        }
        else
        {
            /*
             * ADC_STREAM_COMPLETED State
             */

            /* Conversion has been finished before the group was read.
             * State transition to ADC_IDLE if the group stops
             * implicitly or to ADC_BUSY if the group has to be
             * stopped explicitly.
             */
            if (((uint32)ADC_TRUE) == groupObj->isExplicitStopMode)
            {
                /* Group has to be stopped explicitly, so conversion is
                 * going on after this read. */
                groupObj->groupStatus = ADC_BUSY;
            }
            else
            {
                /* Group stops implicitly when ADC_STREAM_COMPLETED is
                 * reached and the group is read. */
                groupObj->groupStatus = ADC_IDLE;
            }
        }
    }
    return (numSamples);
}

#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
