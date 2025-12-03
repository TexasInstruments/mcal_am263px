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
 *  \file     Adc_Priv.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the ADC MCAL driver files.
 *
 */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "SchM_Adc.h"
#include "Adc_Utils.h"
#include "Adc_Platform.h"
#include "Adc_Types.h"
#include "Det.h"
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define ADC_MAX_HW_CHANNEL_QUQUE 0x0F
#define ADC_MAX_SOC              0x10U
#define ADC_INVALID_HW_INT       0x5
#define ADC_INVALID_INDEX        ((uint8)0xFF)

/* Macros for ADC ISR. */
#define ADC_INTERRUPT_12_REGISTER_OFFSET ((uint32)0x000E)
#define ADC_INTERRUPT_34_REGISTER_OFFSET ((uint32)0x0010)
#define ADC_INTERRUPT_13_REGISTER_MASK   ((uint32)0x000F)
#define ADC_INTERRUPT_24_REGISTER_MASK   ((uint32)0x0F00)
#define ADC_INTERRUPT_SHIFT_VALUE        ((uint8)0x8U)

/** \brief Pre-declaration for HW unit object */
typedef struct Adc_HwUnitObjType_t Adc_HwUnitObjType;

/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief ADC Channel object structure.
 */
typedef struct
{
    Adc_ValueGroupType     *chResultBufPtr;
    /**< Result buffer pointer - fixed for a channel */
    Adc_ValueGroupType     *curResultBufPtr;
    /**< Current result buffer pointer */
    Adc_StreamNumSampleType curNumSamples;
    /**< Current number of samples read */
} Adc_ChannelObjType;

/**
 *  \brief ADC Group object structure.
 */
typedef struct
{
    Adc_GroupConfigType groupCfg;
    /**< ADC group config passed during init */

    Adc_StatusType            groupStatus;
    /**< ADC group result/status */
    uint16                    groupInterruptSrc;
    /**< Group Interrupt Source. */
    uint32                    isExplicitStopMode;
    /**< Determines whether the group stops implicitly or has to be stopped
     *   by the user */
    uint32                    isNotifyOn;
    /**< Flag to enable or disable group notify function */
    uint32                    isPaused;
    /**< Flag to indicate whether the group was paused when a higher
     *   priority group is scheculed */
    uint32                    isQueued;
    /**< Flag to indicate whether the group was queued */
    const Adc_ValueGroupType *resultBufPtr;
    /**< Result buffer pointer - fixed for a group */
    Adc_HwUnitObjType        *hwUnitObj;
    /**< ADC HW unit object as ID and array index may not be same.
     *   This is used for easy de-referencing */

    Adc_UtilsNode nodeObj;
    /**< Node object used for node memory to be used in link list */

    uint32             validSampleCount;
    /**< Number of valid samples - incremented after conversion of all
     *   channels in the group */
    uint32             curCh;
    /**< Current channel to read and store the converted value */
    uint16             socAssigned;
    /**< Starting SOC Ptr assigned to group*/
    uint16             lastSocAssigned;
    /**< Last SOC Ptr assigned to group*/
    /**< Starting SOC Ptr assigned to group*/
    Adc_ChannelObjType chObj[ADC_NUM_CHANNEL];
    /**< Channel specific parameters */
} Adc_GroupObjType;

/**
 *  \brief ADC Hardware unit object structure.
 */
struct Adc_HwUnitObjType_t
{
    Adc_HwUnitConfigType hwUnitCfg;
    /**< ADC HW unit config passed during init */
    uint32               baseAddr;
    /**< ADC base Address. */
    uint32               resultBaseAddr;
    /**< ADC result registers base. */
    Adc_UtilsLinkListObj groupList;
    /**< Group link list per hardware */
    uint16               socHwPtr;
    /**< Soc HW Pointer. */
    uint16               numHwGroupsQue;
    /**< Interrupt assignment. */
    uint16               swGroupSchduled;
    /**< SW Group Schuled flag indicator. */
    Adc_GroupObjType    *curGroupObj;
    /**< When hardware is busy, this points to the current group that is in
     *   progress. When hardware is idle, this will be NULL */
};

/**
 *  \brief ADC driver object structure.
 */
typedef struct
{
    uint8 adcHwUnit;
    /**<  HW Unit Number*/
    uint8 adcHwSocGroup[ADC_MAX_SOC];
    /**< SOC Number */
} Adc_HwSocObjType;

/**
 *  \brief ADC driver object structure.
 */
typedef struct
{
    uint8             maxGroup;
    /**< Maximum number of group
     *   Should not be more than ADC_MAX_GROUP */
    uint8             maxHwUnit;
    /**< Maximum number of HW unit
     *   Should not be more than ADC_MAX_HW_UNIT */
    Adc_GroupObjType  groupObj[ADC_MAX_GROUP];
    /**< ADC group objects */
    Adc_HwUnitObjType hwUnitObj[ADC_MAX_HW_UNIT];
    /**< ADC hw unit objects */
} Adc_DriverObjType;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
/** \brief ADC driver object */
extern VAR(Adc_DriverObjType, ADC_VAR_CLEARED) Adc_DrvObj;
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

/* ========================================================================== */ /* ==========================================================================
                                                                                  */
/*                          Function Declarations                             */
/* ========================================================================== */

void Adc_hwUnitInit(Adc_HwUnitObjType *hwUnitObj);
void Adc_hwUnitDeInit(Adc_HwUnitObjType *hwUnitObj);

Std_ReturnType Adc_startGroup(Adc_GroupObjType *groupObj);
void           Adc_stopGroup(Adc_GroupObjType *groupObj, boolean SwHw);

void Adc_IrqTxRx(Adc_HwUnitObjType *hwUnitObj, uint16 InterruptNum, uint8 Soc);

Adc_HwUnitObjType *Adc_getHwUnitObj(Adc_HWUnitType HWUnit);
void               Adc_resetDrvObj(Adc_DriverObjType *drvObj);
void               Adc_copyConfig(Adc_DriverObjType *drvObj, const Adc_ConfigType *cfgPtr);
uint32             Adc_checkHwUnitObj(const Adc_ConfigType *cfgPtr);
void               Adc_dmaInit(const Adc_ConfigType *cfgPtr);
#if (STD_ON == ADC_DEV_ERROR_DETECT)
void Adc_reportDetError(uint8 apiId, uint8 errorId);
#endif /* #if (STD_ON == ADC_DEV_ERROR_DETECT) */
void                    Adc_reportDetRuntimeError(uint8 apiId, uint8 errorId);
void                    Adc_groupPolling(Adc_GroupObjType *groupObj);
void                    Adc_getChannelMuxParams(Adc_DriverObjType *drvObj);
void                    Adc_performHwInit(void);
void                    Adc_performHwDeInit(void);
void                    Adc_FillDataBufferPtr(Adc_ValueGroupType *DataBufferPtr, Adc_GroupObjType *groupObj);
Adc_StreamNumSampleType Adc_GetStreamLastPointerinternal(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr);
Std_ReturnType          Adc_getStreamPtrCheckDetError(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr);
void                    Adc_checkChannelParams(const Adc_ChannelConfigType *chCfg);

Std_ReturnType Adc_groupConversionDoneHandler(void);

boolean AdcDma_ModuleChannelConfigure(const uint16 *table, uint16 table_size, uint32 dma_ch, uint32 srceaddr);

#if (STD_ON == ADC_REGISTER_READBACK_API)
FUNC(void, ADC_CODE)
Adc_HWRegisterReadback(P2VAR(Adc_RegisterReadbackType, AUTOMATIC, ADC_APPL_DATA) RegRbPtr,
                       Adc_HwUnitObjType *hwUnitObj);
#endif /*STD_ON == ADC_REGISTER_READBACK_API*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ADC_PRIV_H_ */
