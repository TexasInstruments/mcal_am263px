/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \defgroup DRV_CDD_FSI_TX_MODULE APIs for Cdd_FsiTx
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the Cdd_FsiTx module.
 *
 *  @{
 */

#ifndef CDD_FSI_TX_PLATFORM_H_
#define CDD_FSI_TX_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#define CDD_FSITX_START_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CDD_FSITX_STOP_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"
#include "Cdd_FsiTx_Types.h"
#include "Cdd_FsiTx_Reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Values that can be passedas the intFlags and evtFlags parameters.
******************************************************************************/
#define FSI_TX_EVT_FRAME_DONE ((uint16)0x1U)
/** TX frame done event */
#define FSI_TX_EVT_BUF_UNDERRUN ((uint16)0x2U)
/** TX buffer underrun event */
#define FSI_TX_EVT_BUF_OVERRUN ((uint16)0x4U)
/** TX buffer overrun event */
#define FSI_TX_EVT_PING_TIMEOUT ((uint16)0x8U)
/** TX ping timeout event */
#define CDD_FSI_TX_EVTMASK ((uint16)0x000F)

#define CDD_FSI_TX_INTERRUPT_EVENTS (uint16)0x000F

#define CDD_FSI_TX_MAX_VALUE_BUF_PTR_OFF ((uint16)0xFU)
/**
 * @brief Maximum value for user data field (8 bits)
 */
#define CDD_FSI_TX_MAX_VALUE_USERDATA ((uint16)0xFFU)

#define CDD_FSI_TX_DATA_WIDTH_1_LANE ((uint32)0x0U)
/**< 1 lane data width */
#define CDD_FSI_TX_DATA_WIDTH_2_LANE    ((uint32)0x1U)
#define CDD_FSI_TX_MAX_LEN_NWORDS_DATA  ((uint16)0xFU)
#define CDD_FSI_TX_MAX_NUM_EXT_TRIGGERS ((uint16)0x42U)
#define CDD_FSI_TX_INT2_CTRL_SHIFT      ((uint16)0x08U)
#define CDD_FSI_TX_INT2_MASK            ((uint16)0x0F00)

/* Macros for CDD_FSI_TX ISR. */
#define CDD_FSI_TX_INTERRUPT_REGISTER_OFFSET  ((uint32)0x0020)
#define CDD_FSI_TX_INT_STATUS_REGISTER_OFFSET ((uint32)0x0028)
#define CDD_FSI_TX_INT1_MASK                  ((uint16)0x000F)
#define CDD_FSI_TX_INT_SHIFT                  ((uint16)0x0016)
#define CDD_FSI_TX_START_MODE                 ((uint16)0x0002U)
#define CDD_FSI_TX_SW_START_MODE              ((uint16)0x0000U)
#define CDD_FSI_TX_HW_START_MODE              ((uint16)0x0001U)
#define CDD_FSI_TX_DMA_START_MODE             ((uint16)0x0002U)

/*****************************************************************************
 *
 *! Values that can be passed to CddFsiTx_setPrescaler() as the \e clkPrescale
 *! parameter.
 *
 *****************************************************************************/

typedef enum
{
    CDD_FSI_TX_INT1 = 0, /*!< CDDFSITX1 Interrupt*/
    CDD_FSI_TX_INT2 = 1, /*!< CDDFSITX2 Interrupt*/
} CddFsiTx_McalIntNumberType;

/***********************************************************************************/
FUNC(void, CDD_FSITX_CODE) CddFsiTx_selectTxPLLClock(uint32 base, uint16 clkSel);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_resetTxModule(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_clearTxModuleReset(uint32 base);
FUNC(Std_ReturnType, CDD_FSITX_CODE) CddFsiTx_clearTxEvents(uint32 base, uint16 evtFlags);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_enableTxDMAEvent(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_disableTxDMAEvent(uint32 base);
FUNC(uint32, CDD_FSITX_CODE) CddFsiTx_sendTxFlush(uint32 base);
FUNC(uint32, CDD_FSITX_CODE) CddFsiTx_stopTxFlush(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_disableTxClock(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_setPingTag(uint32 base, uint16 frameTag);
FUNC(Std_ReturnType, CDD_FSITX_CODE) CddFsiTx_setFrameType(uint32 base, uint16 frameType);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_startTxTransmit(uint32 base);
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_dataBufferLoad(uint32 base, volatile P2VAR(uint16, AUTOMATIC, CDD_FSI_TX_APPL_DATA) databuffer, uint8 length);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_setTxFrameTag(uint32 base, uint8 frameTag);
FUNC(Std_ReturnType, CDD_FSITX_CODE) CddFsiTx_setTxUserDefinedData(uint32 base, uint8 userData);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_enableHwCRC(uint32 base);
FUNC(Std_ReturnType, CDD_FSITX_CODE) CddFsiTx_setTxDataLane(uint32 base, uint16 DataLane);
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_setTxSoftwareFrameSize(uint32 base, uint16 dataLength);
FUNC(uint16, CDD_FSITX_CODE) CddFsiTx_getTxWordLength(uint32 base, Cdd_FsiTx_DataLengthType length);
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_enableTxPingTimer(uint32 base, uint32 refValue, uint16 pingFrameTag);
FUNC(uint32, CDD_FSITX_CODE) CddFsiTx_clearTxAllEvents(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_sendFlushSequence(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_stopFlushSequence(uint32 base);
FUNC(Std_ReturnType, CDD_FSITX_CODE) CddFsiTx_enableHwTrigger(uint32 base, uint16 frameTriggInput);
FUNC(Std_ReturnType, CDD_FSITX_CODE) CddFsiTx_enableInterrupt(uint32 base, uint8 intTxNum);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_disablePingTimer(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_disableInterrupt(uint32 base, uint8 TxIntNum);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_disableDMA(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_disableClock(uint32 base);
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_setPrescaler(uint32 base, Cdd_FsiTx_ClkPrescaleType preScaleValue);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_enableClock(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_enableTxExtPingTrigger(uint32 base, uint16 extTrigSel);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_getTxBufferAddress(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_clearAllTxEvents(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_ForceTxBufferPtr(uint32 base, uint16 value);
FUNC(uint8, CDD_FSITX_CODE) CddFsiTx_getTxCurrentBufferPtr(uint32 base);
FUNC(void, CDD_FSITX_CODE) CddFsiTx_setStartMode(uint32 base, uint16 startMode);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_FSI_TX_PLATFORM_H_ */

/*******************************************************************************/
/*  End of File: Cdd_FsiTx_Platform.h*/
/******************************************************************************/
