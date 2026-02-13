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
 *  \file     CDD_FSI_RX_Platform.c
 *  \brief    This file contains CDD FSI_RX  driver internal functions
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_FsiRx_Platform.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
extern VAR(CddFsiRx_DriverObjType, CDD_FSIRX_VAR_CLEARED) Cdd_FsiRx_DrvObj;
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CDD_FSIRX_START_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"

FUNC(void, CDD_FSIRX_CODE) CddFsiRx_resetRxModule(uint32 base)
{
    uint16 regVal;
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB);
    regVal |= (uint16)CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_CORE_RST_MASK |
              (CDD_FSI_RX_CTRL_REG_KEY << CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_KEY_SHIFT);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB, regVal);
    return;
}
/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_clearRxModuleReset(uint32 base)
{
    uint16 regVal;
    regVal = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB);
    regVal = (regVal & (uint16)(~CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_CORE_RST_MASK)) |
             (CDD_FSI_RX_CTRL_REG_KEY << CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB_KEY_SHIFT);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_MASTER_CTRL_ALTB, regVal);
    return;
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSIRX_CODE)
CddFsiRx_clearAllRxEvents(uint32 base)
{
    Std_ReturnType retVal = E_OK;
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_EVT_CLR_ALT1, CDD_FSI_RX_EVTMASK);
    return (retVal);
}

/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_clearRxEvents(uint32 base, uint16 evtflags)
{
    uint16 flags = evtflags & CDD_FSI_RX_EVTMASK;
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_EVT_CLR_ALT1, flags);
    return;
}
/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_clearPingWdgEvent(uint32 base, uint16 evtflags)
{
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL, 0x0001);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_EVT_CLR_ALT1, evtflags);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL, 0x0000);

    return;
}
/**********************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_enableRxDMAEvent(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL);
    regVal |= CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL_DMA_EVT_EN_MASK;
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL, regVal);

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableRxDMAEvent(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL_DMA_EVT_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL, regVal);

    return;
}

/******************************************************************************/

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_dataReceive(uint8 hwUnitId, uint32 base, volatile Cdd_FsiRx_DataBufferType *databuffer, uint8 length,
                     uint8 bufOffset)
{
    uint32           baseAddr   = base;
    uint8            dataLength = length;
    volatile uint16 *pSrc16     = (volatile uint16 *)NULL_PTR;
    uint8            wordLength = 0;
    uint8            offset     = bufOffset;
    uint32           regBase    = (uint32)CSL_CDD_FSI_RX_CFG_RX_BUF_BASE((uint32)offset);
    pSrc16                      = (volatile uint16 *)(base + regBase);
    wordLength                  = CddFsiRx_getRxWordLength(baseAddr, (CddFsiRx_DataLengthType)dataLength);
    volatile Cdd_FsiRx_DataBufferType *localDatabuffer = databuffer;

    while (wordLength > 0U)
    {
        *localDatabuffer = *pSrc16;
        pSrc16++;
        localDatabuffer++;
        offset++;
        /*Check for BufferPtr Offset*/
        if (offset > (CDD_FSI_RX_MAX_VALUE_BUF_PTR_OFF))
        {
            offset = 0U;
            pSrc16 = (volatile uint16 *)(base + (uint32)CSL_CDD_FSI_RX_CFG_RX_BUF_BASE((uint32)offset));
        }
        wordLength--;

        Cdd_FsiRx_DrvObj.CddFsiRxDataFrameReceivedNotificationPtr(hwUnitId);
    }
    /*After data reception the offset of of Rx Buffer Pointer will be at a location which equals
    to the number of words received.  So the bufferpointer is forced to 0 again for next reception*/
    CddFsiRx_ForceRxBufferPtr(baseAddr, 0);
    return;
}
/******************************************************************************/
FUNC(uint8, CDD_FSIRX_CODE)
CddFsiRx_getRxWordLength(uint32 base, CddFsiRx_DataLengthType length)
{
    (void)base;
    uint8 WordLength = 0;
    switch (length)
    {
        case CDD_FSI_RX_DATA_1_WORD_LENGTH:
            WordLength = (uint8)1U;
            break;
        case CDD_FSI_RX_DATA_2_WORD_LENGTH:
            WordLength = (uint8)2U;
            break;
        case CDD_FSI_RX_DATA_3_WORD_LENGTH:
            WordLength = (uint8)3U;
            break;
        case CDD_FSI_RX_DATA_4_WORD_LENGTH:
            WordLength = (uint8)4U;
            break;
        case CDD_FSI_RX_DATA_5_WORD_LENGTH:
            WordLength = (uint8)5U;
            break;
        case CDD_FSI_RX_DATA_6_WORD_LENGTH:
            WordLength = (uint8)6U;
            break;
        case CDD_FSI_RX_DATA_7_WORD_LENGTH:
            WordLength = (uint8)7U;
            break;
        case CDD_FSI_RX_DATA_8_WORD_LENGTH:
            WordLength = (uint8)8U;
            break;
        case CDD_FSI_RX_DATA_9_WORD_LENGTH:
            WordLength = (uint8)9U;
            break;
        case CDD_FSI_RX_DATA_10_WORD_LENGTH:
            WordLength = (uint8)10U;
            break;
        case CDD_FSI_RX_DATA_11_WORD_LENGTH:
            WordLength = (uint8)11U;
            break;
        case CDD_FSI_RX_DATA_12_WORD_LENGTH:
            WordLength = (uint8)12U;
            break;
        case CDD_FSI_RX_DATA_13_WORD_LENGTH:
            WordLength = (uint8)13U;
            break;
        case CDD_FSI_RX_DATA_14_WORD_LENGTH:
            WordLength = (uint8)14U;
            break;
        case CDD_FSI_RX_DATA_15_WORD_LENGTH:
            WordLength = (uint8)15U;
            break;
        case CDD_FSI_RX_DATA_16_WORD_LENGTH:
            WordLength = (uint8)16U;
            break;
        default:
            /*Do nothing*/
            break;
    }
    return (WordLength);
}
/******************************************************************************/

FUNC(Std_ReturnType, CDD_FSIRX_CODE)
CddFsiRx_setRxDataWidth(uint32 base, CddFsiRxDataLaneType dataWidth)
{
    Std_ReturnType retVal = E_OK;
    uint16         regVal;

    regVal = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_OPER_CTRL);
    regVal = (regVal & (uint16)(~CSL_CDD_FSI_RX_CFG_RX_OPER_CTRL_DATA_WIDTH_MASK)) | (uint16)dataWidth;
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_OPER_CTRL, regVal);

    return (retVal);
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSIRX_CODE)
CddFsiRx_enableInterrupt(uint32 base, uint8 intRxNum)
{
    Std_ReturnType retVal = E_OK;

    /* Check the arguments */
#if (STD_ON == CDD_FSI_RX_PING_WDG_TIMEOUT_INTERRUPT)
    if (intRxNum == (uint8)CDD_FSI_RX_INT1)
    {
        uint16 regVal      = 0;
        uint32 baseAdress  = 0;
        baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal             = HW_RD_REG16(baseAdress);
        regVal            |= CDD_FSI_RX_PING_WDG_TIMEOUT;
        HW_WR_REG16(baseAdress, regVal);
    }
    /*Enable only INT2 vector*/
    else
    {
        if (intRxNum == (uint8)CDD_FSI_RX_INT2)
        {
            uint16 regVal      = 0;
            uint32 baseAdress  = 0;
            baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal             = HW_RD_REG16(baseAdress);
            regVal            |= CDD_FSI_RX_PING_WDG_TIMEOUT;
            HW_WR_REG16(baseAdress, regVal);
        }
    }
#endif /*STD_ON == CDD_FSI_RX_PING_WDG_TIMEOUT_INTERRUPT*/

#if (STD_ON == CDD_FSI_RX_FRAME_WDG_TIMEOUT_INTERRUPT)
    if (intRxNum == (uint8)CDD_FSI_RX_INT1)
    {
        uint16 regVal      = 0;
        uint32 baseAdress  = 0;
        baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal             = HW_RD_REG16(baseAdress);
        regVal            |= CDD_FSI_RX_FRAME_WDG_TIMEOUT;
        HW_WR_REG16(baseAdress, regVal);
    }
    /*Enable only INT2 vector*/
    else
    {
        if (intRxNum == (uint8)CDD_FSI_RX_INT2)
        {
            uint16 regVal      = 0;
            uint32 baseAdress  = 0;
            baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal             = HW_RD_REG16(baseAdress);
            regVal            |= CDD_FSI_RX_FRAME_WDG_TIMEOUT;
            HW_WR_REG16(baseAdress, regVal);
        }
    }
#endif /*STD_ON == CDD_FSI_RX_FRAME_WDG_TIMEOUT_INTERRUPT*/

#if (STD_ON == CDD_FSI_RX_CRC_ERROR_INTERRUPT)
    if (intRxNum == (uint8)CDD_FSI_RX_INT1)
    {
        uint16 regVal      = 0;
        uint32 baseAdress  = 0;
        baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal             = HW_RD_REG16(baseAdress);
        regVal            |= CDD_FSI_RX_CRC_ERROR;
        HW_WR_REG16(baseAdress, regVal);
    }
    /*Enable only INT2 vector*/
    else
    {
        if (intRxNum == (uint8)CDD_FSI_RX_INT2)
        {
            uint16 regVal      = 0;
            uint32 baseAdress  = 0;
            baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal             = HW_RD_REG16(baseAdress);
            regVal            |= CDD_FSI_RX_CRC_ERROR;
            HW_WR_REG16(baseAdress, regVal);
        }
    }
#endif /*STD_ON == CDD_FSI_RX_CRC_ERROR_INTERRUPT*/

#if (STD_ON == CDD_FSI_RX_BUFFER_OVERRUN_INTERRUPT)
    if (intRxNum == (uint8)CDD_FSI_RX_INT1)
    {
        uint16 regVal      = 0;
        uint32 baseAdress  = 0;
        baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal             = HW_RD_REG16(baseAdress);
        regVal            |= CDD_FSI_RX_BUFFER_OVERRUN;
        HW_WR_REG16(baseAdress, regVal);
    }
    /*Enable only INT2 vector*/
    else
    {
        if (intRxNum == (uint8)CDD_FSI_RX_INT2)
        {
            uint16 regVal      = 0;
            uint32 baseAdress  = 0;
            baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal             = HW_RD_REG16(baseAdress);
            regVal            |= CDD_FSI_RX_BUFFER_OVERRUN;
            HW_WR_REG16(baseAdress, regVal);
        }
    }
#endif /*STD_ON == CDD_FSI_RX_BUFFER_OVERRUN_INTERRUPT*/

#if (STD_ON == CDD_FSI_RX_BUFFER_UNDERRUN_INTERRUPT)
    if (intRxNum == (uint8)CDD_FSI_RX_INT1)
    {
        uint16 regVal      = 0;
        uint32 baseAdress  = 0;
        baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal             = HW_RD_REG16(baseAdress);
        regVal            |= CDD_FSI_RX_BUFFER_UNDERRUN;
        HW_WR_REG16(baseAdress, regVal);
    }
    /*Enable only INT2 vector*/
    else
    {
        if (intRxNum == (uint8)CDD_FSI_RX_INT2)
        {
            uint16 regVal      = 0;
            uint32 baseAdress  = 0;
            baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal             = HW_RD_REG16(baseAdress);
            regVal            |= CDD_FSI_RX_BUFFER_UNDERRUN;
            HW_WR_REG16(baseAdress, regVal);
        }
    }
#endif /*STD_ON == CDD_FSI_RX_BUFFER_UNDERRUN_INTERRUPT*/

#if (STD_ON == CDD_FSI_RX_PING_RECEIVED_INTERRUPT)
    if (intRxNum == (uint8)CDD_FSI_RX_INT1)
    {
        uint16 regVal      = 0;
        uint32 baseAdress  = 0;
        baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal             = HW_RD_REG16(baseAdress);
        regVal            |= CDD_FSI_RX_PING_FRAME_RECEIVED;
        HW_WR_REG16(baseAdress, regVal);
    }
    /*Enable only INT2 vector*/
    else
    {
        if (intRxNum == (uint8)CDD_FSI_RX_INT2)
        {
            uint16 regVal      = 0;
            uint32 baseAdress  = 0;
            baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal             = HW_RD_REG16(baseAdress);
            regVal            |= CDD_FSI_RX_PING_FRAME_RECEIVED;
            HW_WR_REG16(baseAdress, regVal);
        }
    }
#endif /*STD_ON == CDD_FSI_RX_PING_RECEIVED_INTERRUPT*/

#if (STD_ON == CDD_FSI_RX_DATA_RECEIVED_INTERRUPT)
    if (intRxNum == (uint8)CDD_FSI_RX_INT1)
    {
        uint16 regVal      = 0;
        uint32 baseAdress  = 0;
        baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal             = HW_RD_REG16(baseAdress);
        regVal            |= CDD_FSI_RX_DATA_FRAME_RECEIVED;
        HW_WR_REG16(baseAdress, regVal);
    }
    /*Enable only INT2 vector*/
    else
    {
        if (intRxNum == (uint8)CDD_FSI_RX_INT2)
        {
            uint16 regVal      = 0;
            uint32 baseAdress  = 0;
            baseAdress         = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal             = HW_RD_REG16(baseAdress);
            regVal            |= CDD_FSI_RX_DATA_FRAME_RECEIVED;
            HW_WR_REG16(baseAdress, regVal);
        }
    }
#endif /*STD_ON == CDD_FSI_RX_DATA_RECEIVED_INTERRUPT*/

    return (retVal);
}

/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableRxPingWatchdogTimer(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL_PING_WD_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL, regVal);

    return;
}
/******************************************************************************/

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_ForceRxBufferPtr(uint32 base, uint16 value)
{
    /* Check the arguments */

    HW_WR_REG16((base + CSL_CDD_FSI_RX_CFG_RX_BUF_PTR_LOAD), value);
}
/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableRxFrameWatchdogTimer(uint32 base)
{
    uint16 regVal;
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL_FRAME_WD_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL, regVal);
    return;
}
/******************************************************************************/

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableInterrupt(uint32 base, uint8 RxIntNum)
{
    uint16 rxflags = 0x7FFF; /*Register value to be given to Disable all the interrupt fields*/
    uint16 regVal;
    uint32 baseAddr = 0;

    if (RxIntNum == (uint8)CDD_FSI_RX_INT1)
    {
        baseAddr  = base + CSL_CDD_FSI_RX_CFG_RX_INT1_CTRL_ALT1;
        regVal    = HW_RD_REG16(baseAddr);
        regVal   &= ~rxflags;
        HW_WR_REG16(baseAddr, regVal);
    }
    else
    {
        if (RxIntNum == (uint8)CDD_FSI_RX_INT2)
        {
            baseAddr  = base + CSL_CDD_FSI_RX_CFG_RX_INT2_CTRL_ALT1;
            regVal    = HW_RD_REG16(baseAddr);
            regVal   &= ~rxflags;
            HW_WR_REG16(baseAddr, regVal);
        }
    }
}

/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_disableDMA(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL_DMA_EVT_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_DMA_CTRL, regVal);
}

/******************************************************************************/
FUNC(uint16, CDD_FSIRX_CODE)
CddFsiRx_getRxPingTag(uint32 base)
{
    uint32  regVal       = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_PING_TAG);
    uint16  PingTagValue = (uint16)((regVal & CSL_CDD_FSI_RX_CFG_RX_PING_TAG_PING_TAG_MASK) >>
                                   CSL_CDD_FSI_RX_CFG_RX_PING_TAG_PING_TAG_SHIFT);
    uint16 *PingTag      = &PingTagValue;
    return (*PingTag);
}

/******************************************************************************/

FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_enableRxPingWatchdogTimer(uint32 base, uint32 wdRef)
{
    uint16 regVal;

    HW_WR_REG32(base + CSL_CDD_FSI_RX_CFG_RX_PING_WD_REF, wdRef);
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL);
    regVal |= CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL_PING_WD_EN_MASK;
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_PING_WD_CTRL, regVal);

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSIRX_CODE)
CddFsiRx_enableRxFrameWatchdogTimer(uint32 base, uint32 wdRef)
{
    uint16 regVal;

    HW_WR_REG32(base + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_REF, wdRef);
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL);
    regVal |= CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL_FRAME_WD_EN_MASK;
    HW_WR_REG16(base + CSL_CDD_FSI_RX_CFG_RX_FRAME_WD_CTRL, regVal);

    return;
}
/******************************************************************************/
#define CDD_FSIRX_STOP_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"

/*******************************************************************************
 *  End of File: Cdd_FsiRx_Platform.c
 ******************************************************************************/
