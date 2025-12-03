/*
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \defgroup CDD_FSI_RX_MODULE APIs for Cdd_FsiRx
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the Cdd_FsiRx module.
 *
 *  @{
 */

#ifndef CDD_FSI_RX_PLATFORM_H_
#define CDD_FSI_RX_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#define CDD_FSIRX_START_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CDD_FSIRX_STOP_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"
#include "Cdd_FsiRx_Priv.h"
#include "Cdd_FsiRx_Reg.h"
#include "Cdd_FsiRx_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Values that can be passedas the intFlags and evtFlags parameters.
******************************************************************************/
#define FSI_RX_EVT_FRAME_DONE ((uint16)0x1U)
/** RX frame done event */
#define FSI_RX_EVT_BUF_UNDERRUN ((uint16)0x2U)
/** RX buffer underrun event */
#define FSI_RX_EVT_BUF_OVERRUN ((uint16)0x4U)
/** RX buffer overrun event */
#define FSI_RX_EVT_PING_TIMEOUT ((uint16)0x8U)
/** RX ping timeout event */
#define CDD_FSI_RX_EVTMASK      ((uint16)0x7FFF)
#define CDD_FSI_RX_CTRL_REG_KEY ((uint16)0xA5U)

#define CDD_FSI_RX_MAX_VALUE_BUF_PTR_OFF ((uint16)0xFU)

#define CDD_FSI_RX_INTERRUPT_EVENTS (uint16)0x7FFFU
/**
 * @brief Maximum value for user data field (8 bits)
 */
#define CDD_FSI_RX_MAX_VALUE_USERDATA ((uint16)0xFFU)

#define CDD_FSI_RX_DATA_WIDTH_1_LANE ((uint32)0x0U)
/**< 1 lane data width */
#define CDD_FSI_RX_DATA_WIDTH_2_LANE ((uint32)0x1U)
#define CDD_FSI_RX_INT2_CTRL_SHIFT   ((uint16)0x08U)

/* Macros for CDD_FSI_RX ISR. */
#define CDD_FSI_RX_INTERRUPT_REGISTER_OFFSET  ((uint32)0x0020)
#define CDD_FSI_RX_INT_STATUS_REGISTER_OFFSET ((uint32)0x0028)

#define CDD_FSI_RX_INT_SHIFT ((uint16)0x0016)
/* Macros for CDD_FSI_RX ISR event which uses for Ping reception confirmation*/
#define CDD_FSI_RX_RX_INT1_REGISTER_OFFSET       ((uint32)0x0038)
#define CDD_FSI_RX_RX_INT2_REGISTER_OFFSET       ((uint32)0x003A)
#define CDD_FSI_RX_RX_INT_STATUS_REGISTER_OFFSET ((uint32)0x0014)

/* Macros for CDD_FSI_RX ISR event flags. */
#define CDD_FSI_RX_PING_WDG_TIMEOUT    ((uint16)0x0001)
#define CDD_FSI_RX_FRAME_WDG_TIMEOUT   ((uint16)0x0002)
#define CDD_FSI_RX_CRC_ERROR           ((uint16)0x0004)
#define CDD_FSI_RX_FRAME_TYPE_ERROR    ((uint16)0x0008)
#define CDD_FSI_RX_EOF_ERROR           ((uint16)0x0010)
#define CDD_FSI_RX_BUFFER_OVERRUN      ((uint16)0x0020)
#define CDD_FSI_RX_FRAME_DONE          ((uint16)0x0040)
#define CDD_FSI_RX_BUFFER_UNDERRUN     ((uint16)0x0080)
#define CDD_FSI_RX_ERROR_FRAME         ((uint16)0x0100)
#define CDD_FSI_RX_PING_FRAME_RECEIVED ((uint16)0x0200)
#define CDD_FSI_RX_FRAME_OVERRUN       ((uint16)0x0400)
#define CDD_FSI_RX_DATA_FRAME_RECEIVED ((uint16)0x0800)
#define CDD_FSI_RX_PING_TAG_MATCH      ((uint16)0x1000)
#define CDD_FSI_RX_DATA_TAG_MATCH      ((uint16)0x2000)
#define CDD_FSI_RX_ERROR_TAG_MATCH     ((uint16)0x4000)
#define CDD_FSI_RX_ALL_FIELDS_CLEAR    ((uint16)0x7FFF)

#define CDD_FSI_RX_PING_TAG0     ((uint16)0x0000)
#define CDD_FSI_RX_PING_TAG1     ((uint16)0x0001)
#define CDD_FSI_RX_INVALID_INDEX ((uint8)0x0F)

#define CDD_FSI_RX_PING_WDG_TIMEOUT_SHIFT ((uint16)0U)
#define CDD_FSI_RX_PING_WDG_TIMEOUT_MASK  ((uint16)0x0001)

#define CDD_FSI_RX_FRAME_WDG_TIMEOUT_SHIFT ((uint16)1U)
#define CDD_FSI_RX_FRAME_WDG_TIMEOUT_MASK  ((uint16)0x0002)

#define CDD_FSI_RX_CRC_ERROR_SHIFT ((uint16)2U)
#define CDD_FSI_RX_CRC_ERROR_MASK  ((uint16)0x0004)

#define CDD_FSI_RX_FRAME_TYPE_ERROR_SHIFT ((uint16)3U)
#define CDD_FSI_RX_FRAME_TYPE_ERROR_MASK  ((uint16)0x0008)

#define CDD_FSI_RX_EOF_ERROR_SHIFT ((uint16)4U)
#define CDD_FSI_RX_EOF_ERROR_MASK  ((uint16)0x0010)

#define CDD_FSI_RX_BUFFER_OVERRUN_SHIFT ((uint16)5U)
#define CDD_FSI_RX_BUFFER_OVERRUN_MASK  ((uint16)0x0020)

#define CDD_FSI_RX_FRAME_DONE_SHIFT ((uint16)6U)
#define CDD_FSI_RX_FRAME_DONE_MASK  ((uint16)0x0040)

#define CDD_FSI_RX_BUFFER_UNDERRUN_SHIFT ((uint16)7U)
#define CDD_FSI_RX_BUFFER_UNDERRUN_MASK  ((uint16)0x0080)

#define CDD_FSI_RX_ERROR_FRAME_SHIFT ((uint16)8U)
#define CDD_FSI_RX_ERROR_FRAME_MASK  ((uint16)0x0100)

#define CDD_FSI_RX_PING_FRAME_RECEIVED_SHIFT ((uint16)9U)
#define CDD_FSI_RX_PING_FRAME_RECEIVED_MASK  ((uint16)0x0200)

#define CDD_FSI_RX_FRAME_OVERRUN_SHIFT ((uint16)10U)
#define CDD_FSI_RX_FRAME_OVERRUN_MASK  ((uint16)0x0400)

#define CDD_FSI_RX_DATA_FRAME_RECEIVED_SHIFT ((uint16)11U)
#define CDD_FSI_RX_DATA_FRAME_RECEIVED_MASK  ((uint16)0x0800)

#define CDD_FSI_RX_PING_TAG_MATCH_SHIFT ((uint16)12U)
#define CDD_FSI_RX_PING_TAG_MATCH_MASK  ((uint16)0x1000)

#define CDD_FSI_RX_DATA_TAG_MATCH_SHIFT ((uint16)13U)
#define CDD_FSI_RX_DATA_TAG_MATCH_MASK  ((uint16)0x2000)

#define CDD_FSI_RX_ERROR_TAG_MATCH_SHIFT ((uint16)14U)
#define CDD_FSI_RX_ERROR_TAG_MATCH       ((uint16)0x4000)
#define CDD_FSI_RX_16_WORDS              ((uint16)16)

/*****************************************************************************
 *
 *! Values that can be passed to CddFsiRx_setPrescaler() as the \e clkPrescale
 *! parameter.
 *
 *****************************************************************************/

typedef enum
{
    CDD_FSI_RX_INT1 = 0, /*!< CDDFSIRX1 Interrupt*/
    CDD_FSI_RX_INT2 = 1, /*!< CDDFSIRX2 Interrupt*/
} CddFsiRx_mcalIntNumber_t;

/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_resetRxModule(uint32 base);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_clearRxModuleReset(uint32 base);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_clearRxEvents(uint32 base, uint16 evtflags);

FUNC(Std_ReturnType, CDD_FSIRX_CODE)
CddFsiRx_clearAllRxEvents(uint32 base);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_enableRxDMAEvent(uint32 base);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableRxDMAEvent(uint32 base);

FUNC(uint8, CDD_FSIRX_CODE)
CddFsiRx_getRxWordLength(uint32 base, CddFsiRx_DataLengthType length);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_dataReceive(uint8 hwUnitId, uint32 base, volatile Cdd_FsiRx_DataBufferType *databuffer, uint8 length,
                     uint8 bufOffset);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_setRxFrameTag(uint32 base, uint8 frameTag);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_enableRxPingWatchdogTimer(uint32 base, uint32 wdRef);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_enableRxFrameWatchdogTimer(uint32 base, uint32 wdRef);

FUNC(Std_ReturnType, CDD_FSIRX_CODE)
CddFsiRx_disableRxPingWatchdog(uint32 base);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableDMA(uint32 base);

FUNC(Std_ReturnType, CDD_FSIRX_CODE)
CddFsiRx_setRxDataWidth(uint32 base, CddFsiRxDataLaneType dataWidth);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableRxFrameWatchdogTimer(uint32 base);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableRxPingWatchdogTimer(uint32 base);

FUNC(uint16, CDD_FSIRX_CODE)
CddFsiRx_getRxPingTag(uint32 base);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_ForceRxBufferPtr(uint32 base, uint16 value);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_clearPingWdgEvent(uint32 base, uint16 evtflags);

FUNC(Std_ReturnType, CDD_FSIRX_CODE)
CddFsiRx_enableInterrupt(uint32 base, uint8 intRxNum);

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableInterrupt(uint32 base, uint8 RxIntNum);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef CDD_FSI_RX_PLATFORM_H_ */

/*******************************************************************************/
/*  End of File: Cdd_FsiRx_Platform.h*/
/******************************************************************************/
