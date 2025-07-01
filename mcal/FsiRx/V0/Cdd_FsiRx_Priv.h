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
 *  \file     Cdd_FsiRx_Priv.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the CDD FSI_RX driver files.
 *
 */

#ifndef CDD_FSI_RX_PRIV_H_
#define CDD_FSI_RX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "SchM_Cdd_FsiRx.h"
#include "Cdd_FsiRx_Platform.h"
#include "Cdd_FsiRx_Types.h"
#include "Det.h"
#if (CDD_FSI_RX_DMA_ENABLE == STD_ON)
#include "Cdd_Dma.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief Pre-declaration for HW unit object */
typedef struct Cdd_FsiRx_HwUnitObjType_t Cdd_FsiRx_HwUnitObjType;

#define CDD_FSI_RX_BUFF_OFFSET ((uint8)0x00U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 *  \brief CDD FSI RX Hardware unit object structure.
 */
struct Cdd_FsiRx_HwUnitObjType_t
{
    /**< Flag to enable or disable hw unit notify function */
    uint32                    isNotifyOn;
    /**< CDD FSI_RX HW unit config passed during init */
    CddFsiRx_HwUnitConfigType hwUnitCfg;
    /**< CDD FSI_RX HW unit buffer Pointer for each hwunit*/
    Cdd_FsiRx_DataBufferType *rxBuffer;
    /**< Number of words received in each frame*/
    uint8                     rxDataWidth;
    /**< HwUnit Object for each Rx Instance*/
    Cdd_FsiRx_HwUnitObjType  *hwunitObj;
};

typedef enum
{
    /**The master core module reset  **/
    CDD_FSI_RX_MAIN_CORE_RESET,
    /** The Rx module frame wgd counter reset.**/
    CDD_FSI_RX_FRAME_WD_CNT_RESET,
    /** Rx Ping wdg counter rest **/
    CDD_FSI_RX_PING_WD_CNT_RESET,

} Cdd_FsiRx_ResetSubModuleType;
/**
 *  \brief CDD FSI RX driver object structure.
 */
typedef struct
{
    /**< Maximum number of HW unit
     *   Should not be more than CDD_FSI_RX_MAX_NUM_HW_UNIT */
    uint8                      maxHwUnit;
    /**< callback notification fxn pointer to reset driver */
    Cdd_FsiRx_BufferNotifyType CddFsiRxResetNotificationPtr;
    /**< callback notification fxn pointer for buffer overrun */
    Cdd_FsiRx_BufferNotifyType CddFsiRxOverRunNotificationPtr;
    /**< callback notification fxn pointer for buffer underrun */
    Cdd_FsiRx_BufferNotifyType CddFsiRxUnderRunNotificationPtr;
    /**< callback notification fxn pointer for ping frame reception */
    Cdd_FsiRx_BufferNotifyType CddFsiRxPingFrameReceivedNotificationPtr;
    /**< callback notification fxn pointer for data frame reception */
    Cdd_FsiRx_BufferNotifyType CddFsiRxDataFrameReceivedNotificationPtr;
#if (CDD_FSI_RX_DMA_ENABLE == STD_ON)
    /**< callback notification fxn pointer for dma transfer */
    Cdd_FsiRx_BufferNotifyType CddFsiRxDmaNotificationPtr;
#endif
    /**< CddFsiRx hw unit objects */
    Cdd_FsiRx_HwUnitObjType hwUnitObj[CDD_FSI_RX_HW_UNIT_CNT];

} CddFsiRx_DriverObjType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void CddFsiRx_hwUnitInit(Cdd_FsiRx_HwUnitObjType *hwUnitObj);
#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
void CddFsiRx_ReportDetError(uint8 moduleId, uint8 instanceId);
#endif
void           CddFsiRx_ReportRuntimeError(uint8 moduleId, uint8 instanceId);
Std_ReturnType CddFsiRx_hwUnitDeInit(Cdd_FsiRx_HwUnitObjType *hwUnitObj);
void           CddFsiRx_resetDrvObj(CddFsiRx_DriverObjType *drvObj);
void           CddFsiRx_copyConfig(CddFsiRx_DriverObjType *drvObj, const Cdd_FsiRx_ConfigType *cfgPtr);
void           CddFsiRx_Receive(Cdd_FsiRx_HwUnitObjType *hwUnitObj);
void           CddFsiRx_IrqRx(Cdd_FsiRx_HwUnitObjType *hwUnitObj, uint16 evntflag);
Std_ReturnType CddFsiRx_ClearResetRxSubModules(Cdd_FsiRx_HwUnitObjType     *hwUnitObj,
                                               Cdd_FsiRx_ResetSubModuleType subModule);
Std_ReturnType CddFsiRx_ResetRxSubModules(Cdd_FsiRx_HwUnitObjType *hwUnitObj, Cdd_FsiRx_ResetSubModuleType SubModule);
Std_ReturnType CddFsiRx_DMAdataReceive(Cdd_FsiRx_HwUnitObjType *hwUnitObj);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_SetRxSoftwareFrameSize(uint32 base, CddFsiRx_DataLengthType dataWidth);
#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_FSI_RX_PRIV_H_ */
       /*******************************************************************************/
       /*  End of File: Cdd_FsiRx_Priv.h*/
       /******************************************************************************/
