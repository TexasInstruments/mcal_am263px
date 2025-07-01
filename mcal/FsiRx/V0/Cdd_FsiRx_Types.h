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
 *  \file     Cdd_FsiRx_Types.h
 *
 *  \brief    This file contains type definations of Cdd_FsiRx  driver
 *
 */

#ifndef CDD_FSI_RX_TYPES_H_
#define CDD_FSI_RX_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#include "Cdd_FsiRx_Cfg.h"

#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)
#include "Cdd_Dma.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  Number of MCAL channels - in terms of CDD FSI RX HW, this represents the
 *  number of hardware steps.
 *
 */

/** \brief Numeric ID of an CDD FSI RX channel */
#define CDD_FSI_RX_NUM_CHANNEL (2U)
/** \brief Minimum value of channel ID */
#define CDD_FSI_RX_MIN_CHANNEL_ID (0U)
/** \brief Maximum value of channel ID */
#define CDD_FSI_RX_MAX_CHANNEL_ID (CDD_FSI_RX_NUM_CHANNEL - 1U)

#define CDD_FSI_RX_SIZEOF_WORD (2U)
#define CDD_FSI_RX_SIZEOF_BYTE (1U)
#define CDD_FSI_RX_PARAM0      ((uint8)0U)
#define CDD_FSI_RX_CHANNEL0    ((uint8)0U)
#define CDD_FSI_RX_DMA_C_COUNT (1U)

/**
 *  \addtogroup FSIRX FsiRx API GUIDE Header file
 *  @{
 */
/*
 *Design: MCAL
 */
/** \brief Numeric ID of an CDD FSI RX channel group */

typedef uint8  CddFsiRx_ChannelType;
/*
 * Design: MCAL
 */
/** \brief Type for the value of the HW module Ping Watchdog timer. */
typedef uint32 CddFsiRx_PingWdgTimerType;
/*
 * Design: MCAL
 */
/** \brief Type for the value of the HW module Frame Watchdog timer. */
typedef uint32 CddFsiRx_FrameWdgTimerType;

/**
 *  \brief Specifies the ID for a CDD FSI RX Hardware microcontroller
 *  peripheral unit.
 */
typedef uint8 Cdd_FsiRx_HWUnitType;

/** \brief Typedef for the data buffer elements*/
typedef uint16 Cdd_FsiRx_DataBufferType;
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Typedef for application notification function pointer */
typedef P2FUNC(void, CDD_FSI_RX_APPL_CODE, CddFsiRx_NotifyType)(void);

/** \brief Typedef for application notification function pointer */
typedef P2FUNC(void, CDD_FSI_RX_APPL_CODE, Cdd_FsiRx_BufferNotifyType)(Cdd_FsiRx_HWUnitType hwUnitId);

/** \brief Typedef for application notification function pointer */
typedef P2FUNC(void, CDD_FSI_RX_APPL_CODE,
               Cdd_FsiRx_DataBufferNotifyType)(Cdd_FsiRx_HWUnitType               hwUnitId,
                                               volatile Cdd_FsiRx_DataBufferType *databuffer);

#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)
/** \brief Typedef for group end notification function pointer */
typedef Cdd_Edma_EventCallback CddFsiRx_DmaCallBackFunctionType;

#endif

/*
 * Design: MCAL-5811
 */
/**
 *  \brief Current status of the CDD FSI RX HW Unit.
 */

typedef enum
{
    /** \brief The Rx module has not initialized yet **/
    CDD_FSI_RX_UNINIT,
    /** \brief  The Rx module has initialized **/
    CDD_FSI_RX_INIT,
    /** \brief  The Reception through the Rx channel hasn't started **/
    CDD_FSI_RX_IDLE,
    /** \brief The Frame reception has been started and is still
     *   going on. */
    CDD_FSI_RX_BUSY,
    /** \brief The current reception has been completed **/
    CDD_FSI_RX_COMPLETED

} CddFsiRx_StatusType;

/*
 * Design: MCAL-5843
 */
/**
 *  \brief Reception Method.
 */
typedef enum
{
    /** \brief  Reception using Polling Method.**/
    CDD_FSI_RX_POLLING_MODE,
    /** \brief  Reception using DMA Method.**/
    CDD_FSI_RX_DMA_MODE,
    /** \brief  Reception using Interrupt Method.**/
    CDD_FSI_RX_INTERRUPT_MODE
} Cdd_FsiRx_DataReceiveType;

/**
 *  \brief Type for configuring the number of data lines for reception.
 *   This decides whether the reception should happen in single data rate or double data rate.
 */
/*
 * Design: MCAL-
 */
/**
 *  \brief Type for configuring data frame.
 *   This decides data packet width.
 */
/*
 * Design: MCAL-
 */
typedef enum
{
    /** \brief data frame with 1 words data packet **/
    CDD_FSI_RX_SINGLE_DATA_LANE,
    /** \brief data frame with 2 words data packet **/
    CDD_FSI_RX_DOUBLE_DATA_LANE

} CddFsiRxDataLaneType;

/**
 *  \brief Type for configuring data frame.
 *   This decides data packet width.
 */
/*
 * Design: MCAL-
 */
typedef enum
{
    /** \brief data packet with 1 words data length **/
    CDD_FSI_RX_DATA_1_WORD_LENGTH,
    /** \brief data packet with 2 words data length **/
    CDD_FSI_RX_DATA_2_WORD_LENGTH,
    /** \brief data packet with 3 words data length **/
    CDD_FSI_RX_DATA_3_WORD_LENGTH,
    /** \brief data packet with 4 words data length **/
    CDD_FSI_RX_DATA_4_WORD_LENGTH,
    /** \brief data packet with 5 words data length **/
    CDD_FSI_RX_DATA_5_WORD_LENGTH,
    /** \brief data packet with 6 words data length **/
    CDD_FSI_RX_DATA_6_WORD_LENGTH,
    /** \brief data packet with 7 words data length **/
    CDD_FSI_RX_DATA_7_WORD_LENGTH,
    /** \brief data packet with 8 words data length **/
    CDD_FSI_RX_DATA_8_WORD_LENGTH,
    /** \brief data packet with 9 words data length **/
    CDD_FSI_RX_DATA_9_WORD_LENGTH,
    /** \brief data packet with 10 words data length **/
    CDD_FSI_RX_DATA_10_WORD_LENGTH,
    /** \brief data packet with 11 words data length **/
    CDD_FSI_RX_DATA_11_WORD_LENGTH,
    /** \brief data packet with 12 words data length **/
    CDD_FSI_RX_DATA_12_WORD_LENGTH,
    /** \brief data packet with 13 words data length **/
    CDD_FSI_RX_DATA_13_WORD_LENGTH,
    /** \brief data packet with 14 words data length **/
    CDD_FSI_RX_DATA_14_WORD_LENGTH,
    /** \brief data packet with 15 words data length **/
    CDD_FSI_RX_DATA_15_WORD_LENGTH,
    /** \brief data packet with 16 words data length **/
    CDD_FSI_RX_DATA_16_WORD_LENGTH,

} CddFsiRx_DataLengthType;
/**
 *  \brief CDD FSI RX Hw unit configuration structure.
 */
/*
 *Design:
 */
typedef struct
{
    /** \brief HWUnit associated with this  */
    Cdd_FsiRx_HWUnitType       hwId;
    /** \brief Base address  */
    uint32                     baseAddr;
    /** \brief HWUnit associated with this  */
    Cdd_FsiRx_HWUnitType       hwUnitId;
    /** \brief Flag to enable or disable callback notify function */
    uint32                     isNotifyOn;
    /** \brief Determines the frame reception mode.**/
    Cdd_FsiRx_DataReceiveType  receptionMode;
    /** \brief Timeout period of Ping Wdg Timer. */
    CddFsiRx_PingWdgTimerType  pingWdgTriggerTimeout;
    /** \brief Timeout period of Frame Wdg Timer. */
    CddFsiRx_FrameWdgTimerType frameWdgTriggerTimeout;

#if (STD_ON == CDD_FSI_RX_DMA_ENABLE)

    /** \brief DMA Channel ID for Hw Unit . */
    uint8 edmaRxInstance;

#endif

} CddFsiRx_HwUnitConfigType;

/**
 *  \brief CDD FSI RX config structure
 */
typedef struct Cdd_FsiRx_ConfigType_s
{
    /** \brief Maximum number of HW unit
     *   Should not be more than CDD_FSI_RX_MAX_NUM_HW_UNIT */
    uint8                      maxHwUnit;
    /** \brief callback notification fxn pointer to reset driver */
    Cdd_FsiRx_BufferNotifyType cddFsiRxResetNotification;
    /** \brief callback notification fxn pointer for buffer overrun */
    Cdd_FsiRx_BufferNotifyType cddFsiRxOverRunNotification;
    /** \brief callback notification fxn pointer for buffer underrun */
    Cdd_FsiRx_BufferNotifyType cddFsiRxUnderRunNotification;
    /** \brief callback notification fxn pointer for ping frame reception */
    Cdd_FsiRx_BufferNotifyType cddFsiRxPingFrameReceivedNotification;
    /** \brief callback notification fxn pointer for data frame reception */
    Cdd_FsiRx_BufferNotifyType cddFsiRxDataFrameReceivedNotification;
#if (CDD_FSI_RX_DMA_ENABLE == STD_ON)
    /** \brief callback notification fxn pointer for dma transfer */
    Cdd_FsiRx_BufferNotifyType cddFsiRxDmaNotification;
#endif
    /** \brief Fsi Rx Driver config */
    CddFsiRx_HwUnitConfigType hwUnitCfg[CDD_FSI_RX_HW_UNIT_CNT];

} Cdd_FsiRx_ConfigType;

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* #ifndef CDD_FSI_RX_TYPES_H_*/

/*******************************************************************************/
/*  End of File: Cdd_sFsiRx_Types.h*/
/******************************************************************************/
