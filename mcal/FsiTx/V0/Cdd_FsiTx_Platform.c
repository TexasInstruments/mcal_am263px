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
 *  \file     CDD_FSI_TX_Platform.c
 *
 *  \brief    This file contains FSI_TX MCAL driver internal functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Cdd_FsiTx_Platform.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CDD_FSITX_START_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"
/******************************************************************************/
/*
 * Set the configuration of the Cdd Fsi Tx module prescaler.
 */
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_setPrescaler(uint32 base, Cdd_FsiTx_ClkPrescaleType preScaleValue)
{
    HW_WR_REG16((base + (uint32)CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL),
                ((HW_RD_REG16(base + (uint32)CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL) &
                  (uint16)(~CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL_PRESCALE_VAL_MASK)) |
                 (preScaleValue << CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL_PRESCALE_VAL_SHIFT)));
    return;
}
/******************************************************************************/
/*
 * Enable the clock for Cdd Fsi Tx module.
 */
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_enableClock(uint32 base)
{
    HW_WR_REG16((base + CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL),
                (HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL) | CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL_CLK_EN_MASK));
    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_selectTxPLLClock(uint32 base, uint16 clkSel)
{
    uint16 regVal;
    {
        /* Set PLLCLK as source for clock divider */
        regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1);
        regVal &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1_SEL_PLLCLK_MASK);
        regVal  = (clkSel << CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1_SEL_PLLCLK_SHIFT);
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1, regVal);
    }

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_resetTxModule(uint32 base)
{
    uint16 regVal;
    regVal = (uint16)CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_CORE_RST_MASK |
             (CDD_FSI_TX_CTRL_REG_KEY << CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_KEY_SHIFT);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL, regVal);
    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_clearTxModuleReset(uint32 base)
{
    uint16 regVal;
    regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL);
    regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_CORE_RST_MASK)) |
             (CDD_FSI_TX_CTRL_REG_KEY << CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_KEY_SHIFT);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL, regVal);
    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_clearAllTxEvents(uint32 base)
{
    uint16 flags  = 0;
    flags        |= CDD_FSI_TX_EVTMASK;

    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_EVT_CLR, flags);
    return;
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_clearTxEvents(uint32 base, uint16 evtFlag)
{
    Std_ReturnType retVal = E_OK;
    uint16         flags  = evtFlag & (CDD_FSI_TX_EVTMASK);

    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_EVT_CLR, flags);

    return (retVal);
}

/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_enableTxDMAEvent(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL);
    regVal |= CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL_DMA_EVT_EN_MASK;
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL, regVal);

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_disableTxDMAEvent(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL_DMA_EVT_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL, regVal);

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_disableTxClock(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL_CLK_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL, regVal);

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_setPingTag(uint32 base, uint16 frameTag)
{
    {
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_TAG, (uint16)frameTag);
    }

    return;
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_setFrameType(uint32 base, uint16 frameType)
{
    Std_ReturnType retVal = E_OK;
    if (frameType > (uint16)0x000FU)
    {
        retVal = E_NOT_OK;
    }
    uint16 regVal;
    {
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL_FRAME_TYPE_MASK)) | (uint16)frameType;
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL, regVal);
    }

    return retVal;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_startTxTransmit(uint32 base)
{
    uint16 regVal;
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL);
    regVal |= CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL_START_MASK;
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL, regVal);
    return;
}
/******************************************************************************/

FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_dataBufferLoad(uint32 base, volatile P2VAR(uint16, AUTOMATIC, CDD_FSI_TX_APPL_DATA) databuffer, uint8 length)
{
    Std_ReturnType retVal       = E_OK;
    uint8          local_length = length;

    if ((databuffer == NULL_PTR) || (local_length > (CDD_FSI_TX_MAX_VALUE_BUF_PTR_OFF + (uint8)1U)))
    {
        retVal = E_NOT_OK;
    }
    else
    {
        volatile uint16 *pSrc16, *pDst16;
        uint16           offset = 0;
        pSrc16                  = (volatile uint16 *)databuffer;
        pDst16                  = (volatile uint16 *)(base + (uint32)CSL_CDD_FSI_TX_CFG_TX_BUF_BASE(offset));

        while (local_length > 0U)
        {
            *pDst16 = *pSrc16;
            pSrc16++;
            pDst16++;
            offset++;
            /*
             * Check for wrap around in case more words to be written in
             * buffer when last write happened at maximum offset in Tx buffer
             */
            if (offset > CDD_FSI_TX_MAX_VALUE_BUF_PTR_OFF)
            {
                offset = 0U;
                pDst16 = (volatile uint16 *)(base + (uint32)CSL_CDD_FSI_TX_CFG_TX_BUF_BASE(offset));
            }
            local_length--;
        }
    }
    return retVal;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_setTxFrameTag(uint32 base, uint8 frameTag)
{
    uint16 regVal;

    {
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA_FRAME_TAG_MASK)) | (uint16)frameTag;
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA, regVal);
    }

    return;
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_setTxUserDefinedData(uint32 base, uint8 userData)
{
    uint32 retVal = E_OK;
    uint16 regVal;

    /* Check the arguments */
    if (userData > CDD_FSI_TX_MAX_VALUE_USERDATA)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA_USER_DATA_MASK)) |
                 (uint16)(userData << (uint16)CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA_USER_DATA_SHIFT);
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_TAG_UDATA, regVal);
    }

    return (retVal);
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_setTxDataLane(uint32 base, uint16 DataLane)
{
    uint32 retVal = E_OK;
    uint16 regVal;

    /* Check the arguments */
    if (DataLane > CDD_FSI_TX_DATA_WIDTH_2_LANE)
    {
        retVal = E_NOT_OK;
    }
    else
    {
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1_DATA_WIDTH_MASK)) | (uint16)DataLane;
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1, regVal);
    }

    return (retVal);
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_setTxSoftwareFrameSize(uint32 base, uint16 dataLength)
{
    Std_ReturnType retVal = E_OK;
    uint16         regVal;

    /* Check the arguments */
    if ((dataLength == (uint16)0U) || (dataLength > (uint16)(CDD_FSI_TX_MAX_LEN_NWORDS_DATA + (uint16)1U)))
    {
        retVal = E_NOT_OK;
    }
    else
    {
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL_N_WORDS_MASK)) |
                 (dataLength << CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL_N_WORDS_SHIFT);
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_FRAME_CTRL, regVal);
    }
    return (retVal);
}
/******************************************************************************/
FUNC(uint8, CDD_FSITX_CODE)
CddFsiTx_getTxWordLength(uint32 base, uint16 length)
{
    (void)base;
    uint8 WordLength = 0;
    switch (length)
    {
        case CDD_FSI_TX_DATA_1_WORD_LENGTH:
            WordLength = (uint16)1U;
            break;
        case CDD_FSI_TX_DATA_2_WORD_LENGTH:
            WordLength = (uint16)2U;
            break;
        case CDD_FSI_TX_DATA_3_WORD_LENGTH:
            WordLength = (uint16)3U;
            break;
        case CDD_FSI_TX_DATA_4_WORD_LENGTH:
            WordLength = (uint16)4U;
            break;
        case CDD_FSI_TX_DATA_5_WORD_LENGTH:
            WordLength = (uint16)5U;
            break;
        case CDD_FSI_TX_DATA_6_WORD_LENGTH:
            WordLength = (uint16)6U;
            break;
        case CDD_FSI_TX_DATA_7_WORD_LENGTH:
            WordLength = (uint16)7U;
            break;
        case CDD_FSI_TX_DATA_8_WORD_LENGTH:
            WordLength = (uint16)8U;
            break;
        case CDD_FSI_TX_DATA_9_WORD_LENGTH:
            WordLength = (uint16)9U;
            break;
        case CDD_FSI_TX_DATA_10_WORD_LENGTH:
            WordLength = (uint16)10U;
            break;
        case CDD_FSI_TX_DATA_11_WORD_LENGTH:
            WordLength = (uint16)11U;
            break;
        case CDD_FSI_TX_DATA_12_WORD_LENGTH:
            WordLength = (uint16)12U;
            break;
        case CDD_FSI_TX_DATA_13_WORD_LENGTH:
            WordLength = (uint16)13U;
            break;
        case CDD_FSI_TX_DATA_14_WORD_LENGTH:
            WordLength = (uint16)14U;
            break;
        case CDD_FSI_TX_DATA_15_WORD_LENGTH:
            WordLength = (uint16)15U;
            break;
        case CDD_FSI_TX_DATA_16_WORD_LENGTH:
            WordLength = (uint16)16U;
            break;
        default:
            /*Do nothing*/
            break;
    }
    return (WordLength);
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_enableTxPingTimer(uint32 base, uint32 refValue, uint16 pingFrameTag)
{
    uint16 regVal;

    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_TAG, (uint16)pingFrameTag);
    HW_WR_REG32(base + CSL_CDD_FSI_TX_CFG_TX_PING_TO_REF, refValue);
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1);
    regVal |= CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1_TIMER_EN_MASK;
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1, regVal);
    return;
}
/******************************************************************************/

FUNC(void, CDD_FSITX_CODE)
CddFsiTx_sendFlushSequence(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL);
    regVal |= (uint16)CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_FLUSH_MASK |
              (CDD_FSI_TX_CTRL_REG_KEY << (uint16)CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_KEY_SHIFT);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL, regVal);

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_stopFlushSequence(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_FLUSH_MASK);
    regVal |= CDD_FSI_TX_CTRL_REG_KEY << (uint16)CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL_KEY_SHIFT;
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_MASTER_CTRL, regVal);

    return;
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_enableHwTrigger(uint32 base, uint16 frameTriggInput)
{
    uint32 retVal = E_OK;
    uint16 regVal = 0;

    {
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_HI_ALT1);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_HI_ALT1_EXT_TRIG_SEL_MASK)) |
                 (frameTriggInput << CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_HI_ALT1_EXT_TRIG_SEL_SHIFT);
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_HI_ALT1, regVal);
    }

    return (retVal);
}
/******************************************************************************/
FUNC(Std_ReturnType, CDD_FSITX_CODE)
CddFsiTx_enableInterrupt(uint32 base, uint8 intTxNum)
{
    Std_ReturnType retVal = E_OK;
    uint16         regVal = 0;
    /* Check the arguments */
    regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_INT_CTRL);

#if (STD_ON == CDD_FSI_TX_BUFFER_OVERRUN_INTERRUPT)
    if (intTxNum == (uint8)CDD_FSI_TX_INT1)
    {
        regVal |= FSI_TX_EVT_BUF_UNDERRUN;
    }
    else
    {
        regVal |= FSI_TX_EVT_BUF_UNDERRUN << CDD_FSI_TX_INT2_CTRL_SHIFT;
    }
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_INT_CTRL, regVal);
#endif /*CDD_FSI_TX_BUFFER_OVERRUN_INTERRUPT*/

#if (STD_ON == CDD_FSI_TX_BUFFER_UNDERRUN_INTERRUPT)
    if (intTxNum == (uint8)CDD_FSI_TX_INT1)
    {
        regVal |= FSI_TX_EVT_BUF_OVERRUN;
    }
    else
    {
        regVal |= FSI_TX_EVT_BUF_OVERRUN << CDD_FSI_TX_INT2_CTRL_SHIFT;
    }
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_INT_CTRL, regVal);
#endif /*CDD_FSI_TX_BUFFER_UNDERRUN_INTERRUPT*/

#if (STD_ON == CDD_FSI_TX_PING_TIMEOUT_INTERRUPT)
    if (intTxNum == (uint8)CDD_FSI_TX_INT1)
    {
        regVal |= FSI_TX_EVT_PING_TIMEOUT;
    }
    else
    {
        regVal |= FSI_TX_EVT_PING_TIMEOUT << CDD_FSI_TX_INT2_CTRL_SHIFT;
    }
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_INT_CTRL, regVal);
#endif /*CDD_FSI_TX_PING_TIMEOUT_INTERRUPT*/

#if (STD_ON == CDD_FSI_TX_FRAME_DONE_INTERRUPT)
    if (intTxNum == (uint8)CDD_FSI_TX_INT1)
    {
        regVal |= FSI_TX_EVT_FRAME_DONE;
    }
    else
    {
        regVal |= FSI_TX_EVT_FRAME_DONE << CDD_FSI_TX_INT2_CTRL_SHIFT;
    }
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_INT_CTRL, regVal);
#endif /*CDD_FSI_TX_FRAME_DONE_INTERRUPT*/

    return (retVal);
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_disablePingTimer(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1);
    regVal &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1_TIMER_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1, regVal);

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_disableInterrupt(uint32 base, uint8 TxIntNum)
{
    uint16 flags   = CDD_FSI_TX_INT1_MASK;
    uint16 txFlags = CDD_FSI_TX_INT2_MASK;
    uint16 regVal;
    regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_INT_CTRL);
    if (TxIntNum == (uint8)CDD_FSI_TX_INT1)
    {
        regVal &= ~flags;
    }
    else
    {
        regVal &= ~txFlags;
    }
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_INT_CTRL, regVal);
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_disableDMA(uint32 base)
{
    uint16 regVal;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL_DMA_EVT_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_DMA_CTRL, regVal);
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_disableClock(uint32 base)
{
    uint16 regVal;
    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL);
    regVal &= (uint16)(~CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL_CLK_EN_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_CLK_CTRL, regVal);
    return;
}
/******************************************************************************/

FUNC(void, CDD_FSITX_CODE)
CddFsiTx_enableTxExtPingTrigger(uint32 base, uint16 extTrigSel)
{
    uint16 regVal;
    {
        /* Select external input trigger */
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1_EXT_TRIG_SEL_MASK)) |
                 (extTrigSel << CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1_EXT_TRIG_SEL_SHIFT);
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1, regVal);

        /* Enable ping frame transmission through external trigger */
        regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1);
        regVal |= CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1_EXT_TRIG_EN_MASK;
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_PING_CTRL_ALT1, regVal);
    }

    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_enableHwCRC(uint32 base)
{
    uint16 regVal = 0;

    regVal  = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1);
    regVal &= ~(CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1_SW_CRC_MASK);
    HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1, regVal);
    return;
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_setStartMode(uint32 base, uint16 startMode)
{
    uint16 regVal;
    {
        regVal = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1);
        regVal = (regVal & (uint16)(~CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1_START_MODE_MASK)) |
                 ((uint16)startMode << CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1_START_MODE_SHIFT);
        HW_WR_REG16(base + CSL_CDD_FSI_TX_CFG_TX_OPER_CTRL_LO_ALT1, regVal);
    }
}
/******************************************************************************/
FUNC(uint8, CDD_FSITX_CODE)
CddFsiTx_getTxCurrentBufferPtr(uint32 base)
{
    uint16 regVal     = HW_RD_REG16(base + CSL_CDD_FSI_TX_CFG_TX_BUF_PTR_STS);
    uint16 pBufPtrLoc = (regVal & CSL_CDD_FSI_TX_CFG_TX_BUF_PTR_STS_CURR_BUF_PTR_MASK);
    return ((uint8)pBufPtrLoc);
}
/******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
CddFsiTx_ForceTxBufferPtr(uint32 base, uint16 value)
{
    HW_WR_REG16((base + CSL_CDD_FSI_TX_CFG_TX_BUF_PTR_LOAD), 0x0000);
    HW_WR_REG16((base + CSL_CDD_FSI_TX_CFG_TX_BUF_PTR_LOAD), value);
}
/******************************************************************************/

#define CDD_FSITX_STOP_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"
/*******************************************************************************/
/*  End of File: Cdd_FsiTx_Platform.c*/
/******************************************************************************/
