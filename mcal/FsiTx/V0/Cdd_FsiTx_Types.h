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
 *  \file     Cdd_FsiTx_Types.h
 *
 *  \brief    This file contains type definations of Cdd_FsiTx MCAL driver
 *
 */

#ifndef CDD_FSI_TX_TYPES_H_
#define CDD_FSI_TX_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#include "Cdd_FsiTx_Cfg.h"

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
#include "Cdd_Dma.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \brief Number of MCAL channels - in terms of CDD FSI TX HW, this represents the
 *  number of hardware steps.
 *
 */

/** \brief Numeric ID of an CDD FSI TX channel */
#define CDD_FSI_TX_NUM_CHANNEL (2U)
/** \brief Minimum value of channel ID */
#define CDD_FSI_TX_MIN_CHANNEL_ID (0U)
/** \brief Maximum value of channel ID */
#define CDD_FSI_TX_MAX_CHANNEL_ID (CDD_FSI_TX_NUM_CHANNEL - 1U)

/*
 *Design: MCAL
 */
/** \brief Numeric ID of an CDD FSI TX channel group */

typedef uint8  Cdd_FsiTx_ChannelType;
/*
 * Design: MCAL
 */
/** \brief Type for the value of the HW module Ping timer. */
typedef uint32 Cdd_FsiTx_PingTimerType;

/**
 *  \brief Specifies the ID for a CDD FSI TX Hardware microcontroller
 *  peripheral unit.
 */
typedef uint8 Cdd_FsiTx_HWUnitType;

/** \brief Typedef for the data buffer elements*/
typedef uint16 Cdd_FsiTx_DataBufferType;

/** \brief Typedef for the data  elements*/
typedef uint32 Cdd_FsiTx_DataType;
/** \brief Typedef for the data  elements*/
typedef uint8  Cdd_FsiTx_UserDataType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \addtogroup FSITX FsiTx API GUIDE Header file
 *  @{
 */

/** \brief Typedef for application notification function pointer */
typedef P2FUNC(void, CDD_FSI_TX_APPL_CODE, Cdd_FsiTx_NotifyType)(void);

/** \brief Typedef for application notification function pointer */
typedef P2FUNC(void, CDD_FSI_TX_APPL_CODE, Cdd_FsiTx_BufferNotifyType)(Cdd_FsiTx_HWUnitType hwUnitId);

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
/** \brief Typedef for group end notification function pointer */
typedef Cdd_Edma_EventCallback CddFsiTx_DmaCallBackFunctionType;
#endif

/*
 * Design: MCAL-5811
 */
/**
 *  \brief Current status of the CDD FSI TX HW Unit.
 */

typedef enum
{
    /** \brief The Tx module has not initialized yet **/
    CDD_FSI_TX_UNINIT,
    /** \brief The Tx module has initialized **/
    CDD_FSI_TX_INIT,
    /** \brief The transmission through the Tx channel hasn't started **/
    CDD_FSI_TX_IDLE,
    /** \brief The Frame transmission has been started and is still
     *   going on. */
    CDD_FSI_TX_BUSY,

} Cdd_FsiTx_StatusType;

/*
 * Design: MCAL
 */
/**
 *  \brief Type for configuring the trigger source for CDD FSI TX HW.
 */

typedef enum
{
    /** \brief Transmission is triggered by a software API call */
    CDD_FSI_TX_TRIGG_SRC_SW,
    /** \brief Transmission is triggered by external hardware trigger */
    CDD_FSI_TX_TRIGG_SRC_HW
} Cdd_FsiTx_TriggerSourceType;

/*
 * Design: MCAL
 */
/**
 *  \brief Type for configuring on which edge of the hardware trigger signal
 *  the Ping frame should be transmitted.
 */

/**
 *  \brief Type of CDD FSI_TX Data Transmit method.
 *
 */
/*
 * Design: MCAL-5843
 */
typedef enum
{
    /** \brief Transmission using Interrupt Method.**/
    CDD_FSI_TX_INTERRUPT_MODE,
    /** \brief Transmission using Polling Method.**/
    CDD_FSI_TX_POLLING_MODE,
    /** \brief Transmission using DMA Method.**/
    CDD_FSI_TX_DMA_MODE
} Cdd_FsiTx_DataTransmitType;

/**
 *  \brief Type of Clock Prescale
 *
 */
typedef enum
{
    /** \brief <CDD FSI TXCLK = (controlls clock) / 1.0 = 100/1=100 MHz */
    CDD_FSI_TX_CLK_DIV_1 = 1,
    /** \brief <CDD FSI TXCLK = (controlls clock) / 1.0 = 100/2=50 MHz */
    CDD_FSI_TX_CLK_DIV_2 = 2,
    /** \brief <CDD FSI TXCLK = (controlls clock) / 1.0 = 100/4=25 MHz */
    CDD_FSI_TX_CLK_DIV_4 = 4,
    /** \brief <CDD FSI TXCLK = (controlls clock) / 1.0 = 100/5=20 MHz */
    CDD_FSI_TX_CLK_DIV_5 = 5,
    /** \brief <CDD FSI TXCLK = (controlls clock) / 1.0 = 100/10=10 MHz */
    CDD_FSI_TX_CLK_DIV_10 = 10,
    /** \brief <CDD FSI TXCLK = (controlls clock) / 1.0 = 100/20=5 MHz */
    CDD_FSI_TX_CLK_DIV_20 = 20,

} Cdd_FsiTx_ClkPrescaleType;

/**
 *  \brief Type for configuring the number of data lines for transmission.
 *   This decides whether the transmission should happen in single data rate or double data rate.
 */
/*
 * Design: MCAL-
 */
typedef enum
{
    /** \brief Single data line for Transmission( only TXD0) **/
    CDD_FSI_TX_SINGLE_DATA_LINE,
    /** \brief Data Transmitted through both TXD0 & TXD1. (DDR) **/
    CDD_FSI_TX_DOUBLE_DATA_LINE

} Cdd_Fsi_Tx_TransmitLineType;

/**
 *  \brief Type for configuring the status of Ping frame transmission.
 *   This decides whether the Tx has sent Ping frame with tag0 , tag1 or none of them.
 */
/*
 * Design: MCAL-
 */
typedef enum
{
    /** \brief Ping frame with Tag 0 sent **/
    CDD_FSI_TX_PING_ZERO_SENT,
    /** \brief Ping frame with Tag 1 sent **/
    CDD_FSI_TX_PING_ONE_SENT,
    /** \brief No ping frame is sent **/
    CDD_FSI_TX_PING_COMPLETED,

} Cdd_FsiTx_PingTagType;

/**
 *  \brief Type for configuring data frame.
 *   This decides data packet width.
 */
/*
 * Design: MCAL-
 */
typedef enum
{
    /** \brief data ping frame **/
    CDD_FSI_TX_DATA_PING_FRAME = 0x00,
    /** \brief data frame with 1 words data packet **/
    CDD_FSI_TX_DATA_1_WORD = 0x04,
    /** \brief data frame with 2 words data packet **/
    CDD_FSI_TX_DATA_2_WORD = 0x05,
    /** \brief data frame with 4 words data packet **/
    CDD_FSI_TX_DATA_4_WORD = 0x06,
    /** \brief data frame with 6 words data packet **/
    CDD_FSI_TX_DATA_6_WORD = 0x07,
    /** \brief data frame with N (1-16)words data packet **/
    CDD_FSI_TX_DATA_N_WORD = 0x03

} Cdd_FsiTx_FrameType;

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
    CDD_FSI_TX_SINGLE_DATA_LANE,
    /** \brief data frame with 2 words data packet **/
    CDD_FSI_TX_DOUBLE_DATA_LANE,
} Cdd_FsiTx_DataLaneType;

/**
 *  \brief Type for configuring data the interrupt vector
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
    /** \brief data packet with 1 words data length **/
    CDD_FSI_TX_DATA_1_WORD_LENGTH,
    /** \brief data packet with 2 words data length **/
    CDD_FSI_TX_DATA_2_WORD_LENGTH,
    /** \brief data packet with 3 words data length **/
    CDD_FSI_TX_DATA_3_WORD_LENGTH,
    /** \brief data packet with 4 words data length **/
    CDD_FSI_TX_DATA_4_WORD_LENGTH,
    /** \brief data packet with 5 words data length **/
    CDD_FSI_TX_DATA_5_WORD_LENGTH,
    /** \brief data packet with 6 words data length **/
    CDD_FSI_TX_DATA_6_WORD_LENGTH,
    /** \brief data packet with 7 words data length **/
    CDD_FSI_TX_DATA_7_WORD_LENGTH,
    /** \brief data packet with 8 words data length **/
    CDD_FSI_TX_DATA_8_WORD_LENGTH,
    /** \brief data packet with 9 words data length **/
    CDD_FSI_TX_DATA_9_WORD_LENGTH,
    /** \brief data packet with 10 words data length **/
    CDD_FSI_TX_DATA_10_WORD_LENGTH,
    /** \brief data packet with 11 words data length **/
    CDD_FSI_TX_DATA_11_WORD_LENGTH,
    /** \brief data packet with 12 words data length **/
    CDD_FSI_TX_DATA_12_WORD_LENGTH,
    /** \brief data packet with 13 words data length **/
    CDD_FSI_TX_DATA_13_WORD_LENGTH,
    /** \brief data packet with 14 words data length **/
    CDD_FSI_TX_DATA_14_WORD_LENGTH,
    /** \brief data packet with 15 words data length **/
    CDD_FSI_TX_DATA_15_WORD_LENGTH,
    /** \brief data packet with 16 words data length **/
    CDD_FSI_TX_DATA_16_WORD_LENGTH,

} Cdd_FsiTx_DataLengthType;

/**
 *  \brief Type for configuring Tx buffer.
 *   This decides data packet width.
 */
/*
 * Design: MCAL-
 */
typedef enum
{
    /** \brief TX buffer size with 1 words data length **/
    CDD_FSI_TX_BUFF_SIZE_1_WORD_LENGTH = 0x01,
    /** \brief TX buffer size with 2 words data length **/
    CDD_FSI_TX_BUFF_SIZE_2_WORD_LENGTH,
    /** \brief TX buffer size with 3 words data length **/
    CDD_FSI_TX_BUFF_SIZE_3_WORD_LENGTH,
    /** \brief TX buffer size with 4 words data length **/
    CDD_FSI_TX_BUFF_SIZE_4_WORD_LENGTH,
    /** \brief TX buffer size with 5 words data length **/
    CDD_FSI_TX_BUFF_SIZE_5_WORD_LENGTH,
    /** \brief TX buffer size with 6 words data length **/
    CDD_FSI_TX_BUFF_SIZE_6_WORD_LENGTH,
    /** \brief TX buffer size with 7 words data length **/
    CDD_FSI_TX_BUFF_SIZE_7_WORD_LENGTH,
    /** \brief TX buffer size with 8 words data length **/
    CDD_FSI_TX_BUFF_SIZE_8_WORD_LENGTH,
    /** \brief TX buffer size with 9 words data length **/
    CDD_FSI_TX_BUFF_SIZE_9_WORD_LENGTH,
    /** \brief TX buffer size with 10 words data length **/
    CDD_FSI_TX_BUFF_SIZE_10_WORD_LENGTH,
    /** \brief TX buffer size with 11 words data length **/
    CDD_FSI_TX_BUFF_SIZE_11_WORD_LENGTH,
    /** \brief TX buffer size with 12 words data length **/
    CDD_FSI_TX_BUFF_SIZE_12_WORD_LENGTH,
    /** \brief TX buffer size with 13 words data length **/
    CDD_FSI_TX_BUFF_SIZE_13_WORD_LENGTH,
    /** \brief TX buffer size with 14 words data length **/
    CDD_FSI_TX_BUFF_SIZE_14_WORD_LENGTH,
    /** \brief TX buffer size with 15 words data length **/
    CDD_FSI_TX_BUFF_SIZE_15_WORD_LENGTH,
    /** \brief TX buffer size with 16 words data length **/
    CDD_FSI_TX_BUFF_SIZE_16_WORD_LENGTH,

} Cdd_FsiTx_BufferLengthType;

/**
 *  \brief CDD FSI TX Hw unit configuration structure.
 */
/*
 *Design:
 */
typedef struct
{
    /** \brief HWUnit associated with this  */
    Cdd_FsiTx_HWUnitType      hwId;
    /** \brief base address  */
    uint32                    baseAddr;
    /** \brief Hardware Unit  */
    Cdd_FsiTx_HWUnitType      hwUnitId;
    /** \brief Prescalar value for clock division gives to channel **/
    Cdd_FsiTx_ClkPrescaleType Prescalar;

    /** \brief Flag to enable or disable callback notify function */
    uint32                      isNotifyOn;
    /** \brief Determines the trigger source (hw or sw trigger).**/
    Cdd_FsiTx_TriggerSourceType triggSrc;
    /** \brief Determines the frame transmit mode.**/
    Cdd_FsiTx_DataTransmitType  transmitMode;
    /** \brief Timeout period of Ping Timer. */
    Cdd_FsiTx_PingTimerType     pingTriggerTimeout;
    /** \brief Source buffer. */
    uint16                     *srcbuffer;

#if (STD_ON == CDD_FSI_TX_DMA_ENABLE)
    /** \brief CDD FSI EDMA Transmittal handle ID */
    uint8 CddFsiTxDmaInstance;

#endif

} Cdd_FsiTx_HwUnitConfigType;

/**
 *  \brief CDD FSI TX config structure
 */
typedef struct Cdd_FsiTx_ConfigType_s
{
    /** \brief Maximum number of HW unit
     *   Should not be more than CDD_FSI_TX_MAX_HW_UNIT */
    uint8                      maxHwUnit;
    /** \brief callback notification fxn pointer */
    Cdd_FsiTx_BufferNotifyType cddFsiTxNotification;
    /** \brief callback notification fxn pointer for buffer overrun */
    Cdd_FsiTx_BufferNotifyType cddFsiTxOverRunNotification;
    /** \brief callback notification fxn pointer for buffer underrun */
    Cdd_FsiTx_BufferNotifyType cddFsiTxUnderRunNotification;

#if (CDD_FSI_TX_DMA_ENABLE == STD_ON)
    /** \brief callback notification fxn pointer for dma transfer */
    Cdd_FsiTx_BufferNotifyType cddFsiTxDmaNotification;
#endif
    /** \brief FSI TX config */
    Cdd_FsiTx_HwUnitConfigType hwUnitCfg[CDD_FSI_TX_HW_UNIT_CNT];

} Cdd_FsiTx_ConfigType;

#ifdef __cplusplus
}
#endif

/**
 *@}
 */
#endif /* #ifndef CDD_FSI_TX_TYPES_H_ */
