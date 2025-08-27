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
 *  \file     Cdd_FsiTx_Priv.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the CDD FSI_TX driver files.
 *
 */

#ifndef CDD_FSI_TX_PRIV_H_
#define CDD_FSI_TX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "SchM_Cdd_FsiTx.h"
#include "Cdd_FsiTx_Platform.h"
#include "Det.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Macros for CDD_FSI_TX ISR event flags. */
#define CDD_FSI_TX_FRAME_DONE      ((uint16)0x0001)
#define CDD_FSI_TX_BUFFER_UNDERRUN ((uint16)0x0002)
#define CDD_FSI_TX_BUFFER_OVERRUN  ((uint16)0x0004)
#define CDD_FSI_TX_PING_TRIGGERED  ((uint16)0x0008)

#define CDD_FSI_TX_PING_MASK  ((uint16)0x0008)
#define CDD_FSI_TX_PING_SHIFT ((uint16)3U)

#define CDD_FSI_TX_FRAME_DONE_MASK       ((uint16)0x0001)
#define CDD_FSI_TX_BUFFER_UNDERRUN_SHIFT ((uint16)0x0001)
#define CDD_FSI_TX_BUFFER_OVERRUN_SHIFT  ((uint16)0x0002)

#define CDD_FSI_TX_PING_TAG0     ((uint16)0x0000)
#define CDD_FSI_TX_PING_TAG1     ((uint16)0x0001)
#define CDD_FSI_TX_INVALID_INDEX ((uint8)0x0F)
/** \brief Pre-declaration for HW unit object */

#define CSL_CDD_FSI_TX_CLK_SELECT   ((uint16)0x0001U)
#define CDD_FSI_TX_BUFF_OFFSET      ((uint8)0x0FU)
#define CDD_FSI_TX_MAX_DMA_CHANNELS ((uint8)64U)
#define CDD_FSI_TX_WORD_SIZE        ((uint8)2U)
#define CDD_FSI_TX_BYTE_SIZE        ((uint8)1U)
#define CDD_FSI_TX_ZERO_COUNT       ((uint8)1U)
#define CDD_FSI_TX_CHANNEL0         ((uint8)0U)
#define CDD_FSI_TX_CHANNEL1         ((uint8)1U)
#define CDD_FSI_TX_PARAM0           ((uint8)0U)
#define CDD_FSI_TX_DMA_C_COUNT      ((uint8)1U)

/**
 *  \brief Number of actual HW channels - in terms of CDD_FSI_TX HW, this represents
 *  the actual channel input to the CDD_FSI_TX module.
 *  Note: This is a fixed value as per the CDD_FSI_TX module and can't be changed.
 */
#define CDD_FSI_TX_MAX_NUM_HW_INSTANCES (4U)
/** \brief Minimum value of HW channel ID */
#define CDD_FSI_TX_MIN_HW_UNIT_ID (0U)
/** \brief Maximum value of HW channel ID */
#define CDD_FSI_TX_MAX_NUM_CHANNELS (2U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/** \brief Pre-declaration for HW unit object */
typedef struct Cdd_FsiTx_HwUnitObjType_t Cdd_FsiTx_HwUnitObjType;

/**
 *  \brief CDD FSI TX Hardware unit object structure.
 */
struct Cdd_FsiTx_HwUnitObjType_t
{
    uint32                     baseAdress;
    /**< Flag to enable or disable hw unit notify function */
    uint32                     isNotifyOn;
    /**< CDD FSI_TX HW unit config passed during init */
    Cdd_FsiTx_HwUnitConfigType hwUnitCfg;
    /**< CDD FSI_TX HW unit base adress*/
    Cdd_FsiTx_HwUnitObjType   *hwunitObj;
};

typedef enum
{
    /**The master core module reset  **/
    CDD_FSI_TX_MAIN_CORE_RESET,
    /** The Tx module clock reset.**/
    CDD_FSI_TX_CLOCK_RESET,
    /** Tx Ping Time out counter rest **/
    CDD_FSI_TX_PING_TIMEOUT_CNT_RESET,

} Cdd_FsiTx_ResetSubModuleType;

/**
 *  \brief CDD FSI TX driver object structure.
 */
typedef struct
{
    /**< Maximum number of HW unit
     *   Should not be more than CDD_FSI_TX_MAX_HW_UNIT */
    uint8                      maxHwUnit;
    /**< callback notification fxn pointer */
    Cdd_FsiTx_BufferNotifyType CddFsiTxNotificationPtr;
    /**< callback notification fxn pointer for buffer overrun */
    Cdd_FsiTx_BufferNotifyType CddFsiTxOverRunNotificationPtr;
    /**< callback notification fxn pointer for buffer underrun */
    Cdd_FsiTx_BufferNotifyType CddFsiTxUnderRunNotificationPtr;
#if (CDD_FSI_TX_DMA_ENABLE == STD_ON)
    /**< callback notification fxn pointer for dma transfer */
    Cdd_FsiTx_BufferNotifyType CddFsiTxDmaNotificationPtr;
#endif
    /**< CddFsiTx hw unit objects */
    Cdd_FsiTx_HwUnitObjType hwUnitObj[CDD_FSI_TX_HW_UNIT_CNT];

} Cdd_FsiTx_DriverObjType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Std_ReturnType CddFsiTx_hwUnitInit(const Cdd_FsiTx_HwUnitObjType *hwUnitObj);
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
void CddFsiTx_ReportDetError(uint8 moduleId, uint8 instanceId);
#endif
void           CddFsiTx_ReportRuntimeError(uint8 moduleId, uint8 instanceId);
Std_ReturnType CddFsiTx_hwUnitDeInit(const Cdd_FsiTx_HwUnitObjType *hwUnitObj);
void           CddFsiTx_resetDrvObj(Cdd_FsiTx_DriverObjType *drvObj);
Std_ReturnType CddFsiTx_copyConfig(Cdd_FsiTx_DriverObjType *drvObj, const Cdd_FsiTx_ConfigType *cfgPtr);
Std_ReturnType CddFsiTx_BufferLoad(const Cdd_FsiTx_HwUnitObjType *hwUnitObj,
                                   P2VAR(uint16, AUTOMATIC, CDD_FSI_TX_APPL_DATA) databuffer, uint32 userData,
                                   uint32 txDatalength);
Std_ReturnType CddFsiTx_PingTransmit(const Cdd_FsiTx_HwUnitObjType *hwUnitObj);
Std_ReturnType CddFsiTx_Transmit(const Cdd_FsiTx_HwUnitObjType *hwUnitObj, uint8 UserData,
                                 Cdd_FsiTx_DataLengthType txDataLength);
void CddFsiTx_IrqTx(Cdd_FsiTx_HwUnitObjType *hwUnitObj, CddFsiTx_McalIntNumberType InterruptNum, uint16 EvtFlag);
Std_ReturnType CddFsiTx_DMABufferLoad(const Cdd_FsiTx_HwUnitObjType *hwUnitObj, Cdd_FsiTx_DataBufferType *databuffer,
                                      uint32 userData, uint32 TxDatalength);
void           CddFsiTx_MainFunction(Cdd_FsiTx_HwUnitObjType *hwUnitObj);
Std_ReturnType CddFsiTx_ClearResetTxSubModules(const Cdd_FsiTx_HwUnitObjType *hwUnitObj,
                                               Cdd_FsiTx_ResetSubModuleType   subModule);
Std_ReturnType CddFsiTx_ResetTxSubModules(const Cdd_FsiTx_HwUnitObjType *hwUnitObj,
                                          Cdd_FsiTx_ResetSubModuleType   SubModule);
#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_FSI_TX_PRIV_H_ */

/*******************************************************************************/
/*  End of File: Cdd_FsiTx_Priv.h*/
/******************************************************************************/
