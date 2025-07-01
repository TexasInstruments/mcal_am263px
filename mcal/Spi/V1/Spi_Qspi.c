/* ======================================================================
 *   Copyright (c) 2023-2024 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     Spi_Qspi.c
 *
 *  \brief    This file contains SPI MCAL driver functions for the QSPI
 *            peripheral
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Spi_Priv.h"

#include "Dem.h"
#include "Os.h"
#include "soc.h"

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

#include "hw_types.h"
#include "hw_ctrl_core.h"
#include "Os.h"

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
#include "Spi_Qspi.h"
#include "hw_qspi.h"
#include "Cdd_Dma_Priv.h"
#include "Cdd_Dma.h"
#include "Cdd_Dma_Cfg.h"
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Spi_qspiCmdCheck(Spi_JobObjType *jobObj, Spi_ChannelObjType *chObj, Spi_HwUnitObjType *const hwUnitObj);

static void Spi_qspiChModeCheck(Spi_JobObjType *jobObj, Spi_ChannelObjType *chObj, Spi_HwUnitObjType *const hwUnitObj);

static void Spi_qspiWaitIdle(uint32 baseAddr);
static void Spi_qspiSetClockControl(uint32 baseAddr, uint32 lv_clkDivider);
static void Spi_qspiSetDeviceControl(const Spi_QspiExternalDeviceConfigType *extDevCfg, uint32 baseAddr, uint32 csNum);

static void Spi_qspiSetCommandReg(uint32 baseAddr, uint32 cmd);
static void Spi_qspiWriteData(uint32 baseAddr, Spi_ChannelObjType *chObj);

static void Spi_qspiReadData(uint32 baseAddr, Spi_ChannelObjType *chObj);

static void Spi_qspiReadDataAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift);

static boolean Spi_qspiIsWriteCmd(Spi_QspiChXferCmdType xferCmd);

static boolean Spi_qspiIsReadCmd(Spi_QspiChXferCmdType xferCmd);

static Std_ReturnType Spi_qspiSendCmd(uint32 baseAddr, const Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                      uint32 curChId);

static Std_ReturnType Spi_qspiSendCmdAsync(uint32 baseAddr, Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                           uint32 curChId);

static uint16 Spi_qspiGetCmdFrameLength(const Spi_JobObjType *jobObj, const Spi_ChannelObjType chList[],
                                        uint32 startChId);

static Std_ReturnType Spi_qspiXferCmd(uint32 baseAddr, const Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                      uint32 curChId);

static Std_ReturnType Spi_qspiXferCmdAsync(uint32 baseAddr, Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                           uint32 curChId);

static Std_ReturnType Spi_qspiXferAddr(uint32 baseAddr, Spi_ChannelObjType *chObj);

static Std_ReturnType Spi_qspiXferAddrAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift);

static Std_ReturnType Spi_qspiXferDummy(uint32 baseAddr, Spi_ChannelObjType *chObj);

static Std_ReturnType Spi_qspiXferData(uint32 baseAddr, Spi_ChannelObjType *chObj);

static Std_ReturnType Spi_qspiXferDummyAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift);

static Std_ReturnType Spi_qspiXferDataAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift);

static void Spi_qspiXferDataMemMapped(uint32 baseAddr, Spi_ChannelObjType *const chObj, uint32 addrOffset);

#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)
static void Spi_qspiXferDataMemMappedDma(void *dst, void *src, uint16 length);
static void Spi_qspiTxCompletionStatus(uint32 Spi_QspiHandle);
#endif
static Spi_JobResultType Spi_qspiXferJobMemMapped(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                  Spi_ChannelObjType chList[]);

#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)
static Spi_JobResultType Spi_qspiXferJobMemMappedDma(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                     Spi_ChannelObjType chList[]);
#endif

static Spi_JobResultType Spi_qspiXferJobNonMemMapped(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                     Spi_ChannelObjType chList[]);

static Spi_JobResultType Spi_qspiXferJobNonMemMappedAsync(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                          Spi_ChannelObjType chList[]);

static uint32 Spi_qspiGetChTxData(Spi_ChannelObjType *chObj);
static uint32 Spi_qspiGetChTxDataAsync(Spi_ChannelObjType *chObj, uint32 shift);
static void   QSPI_edmaIsrFxn(void);
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define EDMA_QSPI_A_COUNT (1U)
/* Max Value for EDMA count */
#define MAX_EDMA_COUNT (31U * 1024U)
/* Value for C count */
#define EDMA_QSPI_C_COUNT (1U)

#define SPI_START_SEC_VAR_INIT_8
#include "Spi_MemMap.h"
volatile boolean Spi_Qspi_IsEdmaInterruptEnabled = FALSE;
#define SPI_STOP_SEC_VAR_INIT_8
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_INIT_32
#include "Spi_MemMap.h"
#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)
uint32 Spi_Qspi_Handle = SPI_UNIT_QSPI1_DMA_HANDLER;
#endif
#define SPI_STOP_SEC_VAR_INIT_32
#include "Spi_MemMap.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

/* ========================================================================== */
/*                          Static function declaration                       */
/* ========================================================================== */

static void Spi_qspiWaitIdle(uint32 baseAddr)
{
    volatile uint32 tempCount = SPI_MAX_TIMEOUT_DURATION;
    if (SPI_MAX_TIMEOUT_DURATION > 9U)
    {
        /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
        tempCount = SPI_MAX_TIMEOUT_DURATION / 9U;
    }
    while ((HW_RD_REG32(baseAddr + QSPI_SPI_STATUS_REG) & QSPI_SPI_STATUS_REG_BUSY_MASK) ==
           QSPI_SPI_STATUS_REG_BUSY_BUSY)
    {
        if (tempCount <= 0U)
        {
#ifdef SPI_E_HARDWARE_ERROR
            /* timeout */
            Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
}

static void Spi_qspiSetClockControl(uint32 baseAddr, uint32 lv_clkDivider)
{
    /* wait for the QSPI to be idle */
    Spi_qspiWaitIdle(baseAddr);

    /* turn off QSPI data clock */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
                  QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF);

    /* clear QSPI clock divider*/
    HW_WR_FIELD32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG, QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV, 0U);

    /* update QSPI clock divider*/
    HW_WR_FIELD32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG, QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV, lv_clkDivider);

    /* enable QSPI data clock */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_CLOCK_CNTRL_REG, QSPI_SPI_CLOCK_CNTRL_REG_CLKEN,
                  QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON);

    return;
}

static void Spi_qspiSetDeviceControl(const Spi_QspiExternalDeviceConfigType *extDevCfg, uint32 baseAddr, uint32 csNum)
{
    uint32 regVal = 0U;
    uint32 ckp    = 0U;
    uint32 csp    = 0U;
    uint32 ckph   = 0U;

    /* Set CS polarity */
    if (SPI_LOW == extDevCfg->csPolarity)
    {
        csp = QSPI_SPI_DC_REG_CSP_ACTIVE_LOW;
    }
    else
    {
        csp = QSPI_SPI_DC_REG_CSP_ACTIVE_HIGH;
    }

    /* Set Clk mode */
    if ((SPI_CLK_MODE_0 == extDevCfg->clkMode) || (SPI_CLK_MODE_1 == extDevCfg->clkMode))
    {
        ckp = QSPI_SPI_DC_REG_CKP_DATA_INACTIVE;
        if (SPI_CLK_MODE_0 == extDevCfg->clkMode)
        {
            /* SPI mode 0 */
            ckph = QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_FALLING_EDGE;
        }
        else
        {
            /* SPI mode 1 */
            ckph = QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_RISING_EDGE;
        }
    }
    else
    {
        ckp = QSPI_SPI_DC_REG_CKP_DATA_ACTIVE;
        if (SPI_CLK_MODE_2 == extDevCfg->clkMode)
        {
            /* SPI mode 2 */
            ckph = QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_RISING_EDGE;
        }
        else
        {
            /* SPI mode 3 */
            ckph = QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_FALLING_EDGE;
        }
    }

    regVal = HW_RD_REG32(baseAddr + QSPI_SPI_DC_REG);
    if (0U == csNum)
    {
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CSP0, csp);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKP0, ckp);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKPH0, ckph);

        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_DD0, (uint32)extDevCfg->csIdleTime);
    }
    else if (1U == csNum)
    {
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKP1, ckp);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKPH1, ckph);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CSP1, csp);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_DD1, (uint32)extDevCfg->csIdleTime);
    }
    else if (2U == csNum)
    {
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKP2, ckp);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKPH2, ckph);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CSP2, csp);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_DD2, (uint32)extDevCfg->csIdleTime);
    }
    else
    {
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKP3, ckp);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CKPH3, ckph);
        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_CSP3, csp);

        HW_SET_FIELD32(regVal, QSPI_SPI_DC_REG_DD3, (uint32)extDevCfg->csIdleTime);
    }

    /* wait for the QSPI to be idle */
    Spi_qspiWaitIdle(baseAddr);
    HW_WR_REG32(baseAddr + QSPI_SPI_DC_REG, regVal);

    return;
}

static void Spi_qspiSetCommandReg(uint32 baseAddr, uint32 cmd)
{
    /* wait for the QSPI to be idle */
    Spi_qspiWaitIdle(baseAddr);
    HW_WR_REG32(baseAddr + QSPI_SPI_CMD_REG, cmd);
    Spi_qspiWaitIdle(baseAddr);

    return;
}

static void Spi_qspiWriteData(uint32 baseAddr, Spi_ChannelObjType *chObj)
{
    uint32 transData;

    transData = Spi_qspiGetChTxData(chObj);
    HW_WR_REG32(baseAddr + QSPI_SPI_DATA_REG, transData);

    return;
}

static void Spi_qspiWriteDataAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift)
{
    uint32 transData;

    transData = Spi_qspiGetChTxDataAsync(chObj, shift);
    HW_WR_REG32(baseAddr + QSPI_SPI_DATA_REG, transData);

    return;
}

static void Spi_qspiReadData(uint32 baseAddr, Spi_ChannelObjType *chObj)
{
    uint32  RxData, dataWidth;
    uint8  *tempBuf8;
    uint16 *tempBuf16;
    uint32 *tempBuf32;
    uint32  dataWidthBitMask;

    dataWidth = chObj->chCfg.dataWidth;
    /* Read the RX data */
    RxData            = HW_RD_REG32(baseAddr + QSPI_SPI_DATA_REG);
    dataWidthBitMask  = Spi_getDataWidthBitMask(dataWidth);
    RxData           &= dataWidthBitMask;

    if (dataWidth <= 8U)
    {
        tempBuf8  = (uint8 *)chObj->curRxBufPtr;
        *tempBuf8 = (uint8)RxData;
        chObj->curRxBufPtr++;
    }
    else if (dataWidth <= 16U)
    {
        tempBuf16  = (uint16 *)chObj->curRxBufPtr;
        *tempBuf16 = (uint16)RxData;
        chObj->curRxBufPtr++;
        chObj->curRxBufPtr++;
    }
    else
    {
        tempBuf32 = (uint32 *)chObj->curRxBufPtr;

        *tempBuf32 = (uint32)RxData;
        chObj->curRxBufPtr++;
        chObj->curRxBufPtr++;
        chObj->curRxBufPtr++;
        chObj->curRxBufPtr++;
    }

    return;
}

static void Spi_qspiReadDataAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift)
{
    uint32  RxData           = 0U;
    uint32  dataWidth        = 0U;
    uint8  *tempBuf8         = (uint8 *)NULL_PTR;
    uint16 *tempBuf16        = (uint16 *)NULL_PTR;
    uint32 *tempBuf32        = (uint32 *)NULL_PTR;
    uint32  dataWidthBitMask = 0U;

    dataWidth = chObj->chCfg.dataWidth;
    /* Read the RX data */
    RxData            = HW_RD_REG32(baseAddr + QSPI_SPI_DATA_REG);
    dataWidthBitMask  = Spi_getDataWidthBitMask(dataWidth);
    RxData           &= dataWidthBitMask;

    if (dataWidth <= 8U)
    {
        chObj->curRxBufPtr += shift;
        tempBuf8            = (uint8 *)chObj->curRxBufPtr;
        *tempBuf8           = (uint8)RxData;
    }
    else if (dataWidth <= 16U)
    {
        chObj->curRxBufPtr += shift;
        chObj->curRxBufPtr += shift;
        tempBuf16           = (uint16 *)chObj->curRxBufPtr;
        *tempBuf16          = (uint16)RxData;
    }
    else
    {
        chObj->curRxBufPtr += shift;
        chObj->curRxBufPtr += shift;
        chObj->curRxBufPtr += shift;
        chObj->curRxBufPtr += shift;
        /* dataWidth less than or equak to 32 */
        tempBuf32  = (uint32 *)chObj->curRxBufPtr;
        *tempBuf32 = (uint32)RxData;
    }

    return;
}

static boolean Spi_qspiIsWriteCmd(Spi_QspiChXferCmdType xferCmd)
{
    boolean retVal = TRUE;

    if ((xferCmd == SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE) || (xferCmd == SPI_QSPI_SFI_CH_XFER_CMD_3PIN_WR_SINGLE))
    {
        retVal = (boolean)TRUE;
    }
    else
    {
        retVal = (boolean)FALSE;
    }

    return (retVal);
}
static boolean Spi_qspiIsReadCmd(Spi_QspiChXferCmdType xferCmd)
{
    boolean retVal;

    if ((xferCmd == SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE) || (xferCmd == SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_DUAL) ||
        (xferCmd == SPI_QSPI_SFI_CH_XFER_CMD_3PIN_RD_SINGLE) || (xferCmd == SPI_QSPI_SFI_CH_XFER_CMD_6PIN_RD_QUAD))
    {
        retVal = (boolean)TRUE;
    }
    else
    {
        retVal = (boolean)FALSE;
    }

    return (retVal);
}

static uint16 Spi_qspiGetCmdFrameLength(const Spi_JobObjType *jobObj, const Spi_ChannelObjType chList[],
                                        uint32 startChId)
{
    uint32 idx;
    uint32 chId;
    uint16 frameLength = 0U;

    for (idx = 0U; idx < jobObj->jobCfg.channelPerJob; idx++)
    {
        if (jobObj->jobCfg.channelList[idx] == startChId)
        {
            break;
        }
    }
    idx += 1U; /* Step past cmd ch */

    for (; idx < jobObj->jobCfg.channelPerJob; idx++)
    {
        chId = jobObj->jobCfg.channelList[idx];
        if (chList[chId].chCfg.qspiChMode == SPI_QSPI_SFI_CHMODE_CMD)
        {
            /* Break frame Length calculation if another command channel
             * encountered */
            break;
        }
        frameLength += chList[chId].numWordsTxRx;
    }

    return (frameLength);
}

static Std_ReturnType Spi_qspiSendCmd(uint32 baseAddr, const Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                      uint32 curChId)
{
    uint32         regVal;
    uint32         intStatus;
    uint8          dataWidth;
    uint16         frameLength;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    /* switch to cfg port mode */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S, QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    frameLength = Spi_qspiGetCmdFrameLength(jobObj, chList, curChId);
    if (frameLength >= SPI_QSPI_MAX_FRAMELEN)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        regVal = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
        /* Write Command */
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_FLEN, frameLength);
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WIRQ, QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE);

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_FIRQ, QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE);
        intStatus = 0U;
        HW_SET_FIELD32(intStatus, QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR,
                       QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_ACTIVE);
        HW_WR_REG32(baseAddr + QSPI_INTR_ENABLE_CLEAR_REG, intStatus);

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, (uint32)chList[curChId].chCfg.qspiXferCmd);

        dataWidth = (uint8)(chList[curChId].chCfg.dataWidth) - 1U;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CSNUM, (uint32)jobObj->jobCfg.csPin);

        Spi_qspiWriteData(baseAddr, &chList[curChId]);
        Spi_qspiSetCommandReg(baseAddr, regVal);
    }

    return (retVal);
}

static Std_ReturnType Spi_qspiSendCmdAsync(uint32 baseAddr, Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                           uint32 curChId)
{
    uint32         regVal;
    uint32         regVal_set;
    uint8          dataWidth;
    uint16         frameLength;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    /* switch to cfg port mode */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S, QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    frameLength = Spi_qspiGetCmdFrameLength(jobObj, chList, curChId);
    if (frameLength >= SPI_QSPI_MAX_FRAMELEN)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        regVal     = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
        regVal_set = HW_RD_REG32(baseAddr + QSPI_INTR_ENABLE_SET_REG);
        /* Write Command */
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_FLEN, frameLength);
        /* Enable the interupts both word as well as frame*/
        HW_SET_FIELD32(regVal_set, QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET, QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_ACTIVE);
        HW_SET_FIELD32(regVal_set, QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET, QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_ACTIVE);
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WIRQ, QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_ENABLE);

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_FIRQ, QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_ENABLE);

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, (uint32)chList[curChId].chCfg.qspiXferCmd);

        dataWidth = (uint8)(chList[curChId].chCfg.dataWidth) - 1U;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CSNUM, (uint32)jobObj->jobCfg.csPin);

        Spi_qspiWriteData(baseAddr, &chList[curChId]);
        jobObj->curChIdx++;
        HW_WR_REG32(baseAddr + QSPI_SPI_CMD_REG, regVal);
        HW_WR_REG32(baseAddr + QSPI_INTR_ENABLE_SET_REG, regVal_set);
    }

    return (retVal);
}

static Std_ReturnType Spi_qspiXferCmd(uint32 baseAddr, const Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                      uint32 curChId)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (chList[curChId].numWordsTxRx != 1U)
    {
        Spi_reportDetError(SPI_SID_SYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (Spi_qspiIsWriteCmd(chList[curChId].chCfg.qspiXferCmd) != (boolean)TRUE)
    {
        Spi_reportDetError(SPI_SID_SYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        /* Make protected access to command config */
        SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

        retVal = Spi_qspiSendCmd(baseAddr, jobObj, chList, curChId);

        /* Exit exclusive area */
        SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}

static Std_ReturnType Spi_qspiXferCmdAsync(uint32 baseAddr, Spi_JobObjType *jobObj, Spi_ChannelObjType chList[],
                                           uint32 curChId)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (chList[curChId].numWordsTxRx != 1U)
    {
        Spi_reportDetError(SPI_SID_ASYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (Spi_qspiIsWriteCmd(chList[curChId].chCfg.qspiXferCmd) != (boolean)TRUE)
    {
        Spi_reportDetError(SPI_SID_ASYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == SPI_CFG_DEV_ERROR_DETECT) */
    {
        /* Make protected access to command config */
        SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

        retVal = Spi_qspiSendCmdAsync(baseAddr, jobObj, chList, curChId);

        /* Exit exclusive area */
        SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}

static Std_ReturnType Spi_qspiXferAddr(uint32 baseAddr, Spi_ChannelObjType *chObj)
{
    uint32         regVal;
    uint32         dataWidth;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (chObj->numWordsTxRx != 1U)
    {
        Spi_reportDetError(SPI_SID_SYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd) != (boolean)TRUE)
    {
        Spi_reportDetError(SPI_SID_SYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        /* switch to cfg port mode */
        HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

        Spi_qspiWriteData(baseAddr, chObj);
        regVal = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, (uint32)chObj->chCfg.qspiXferCmd);
        dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1U;

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
        Spi_qspiSetCommandReg(baseAddr, regVal);
    }

    return (retVal);
}
static Std_ReturnType Spi_qspiXferAddrAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift)
{
    uint32         regVal;
    uint32         dataWidth;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (chObj->numWordsTxRx != 1U)
    {
        Spi_reportDetError(SPI_SID_ASYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd) != (boolean)TRUE)
    {
        Spi_reportDetError(SPI_SID_ASYNC_TRANSMIT, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == SPI_CFG_DEV_ERROR_DETECT) */
    {
        /* switch to cfg port mode */
        HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

        Spi_qspiWriteDataAsync(baseAddr, chObj, shift);
        regVal = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, (uint32)chObj->chCfg.qspiXferCmd);
        dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1U;

        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
        HW_WR_REG32(baseAddr + QSPI_SPI_CMD_REG, regVal);
    }

    return (retVal);
}

static void Spi_qspiXferDataMemMapped(uint32 baseAddr, Spi_ChannelObjType *const chObj, uint32 addrOffset)
{
    uint32  dataWidth        = 0U;
    uint32  dataWidthBitMask = 0U;
    uint16  Length           = 0U;
    uint32  idx              = 0U;
    uint32 *srcAddr32        = (uint32 *)NULL_PTR;
    uint32 *dstAddr32        = (uint32 *)NULL_PTR;
    uint16 *srcAddr16        = (uint16 *)NULL_PTR;
    uint16 *dstAddr16        = (uint16 *)NULL_PTR;
    uint8  *srcAddr8         = (uint8 *)NULL_PTR;
    uint8  *dstAddr8         = (uint8 *)NULL_PTR;
    uint8   rxData8          = 0U;
    uint16  rxData16         = 0U;
    uint32  rxData32         = 0U;

    /* Change to Memory mapped mode */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S, QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
    /* Read data from QSPI in mem mapped mode */
    srcAddr32 = (uint32 *)(SOC_QSPI_ADDRSP1_BASE + addrOffset);

    dstAddr32 = (uint32 *)chObj->rxBufPtr;
    dataWidth = (uint32)chObj->chCfg.dataWidth;
    Length    = chObj->numWordsTxRx;

    dataWidthBitMask = Spi_getDataWidthBitMask(dataWidth);
    if (dataWidth <= 16U)
    {
        if (dataWidth <= 8U)
        {
            dstAddr8 = (uint8 *)dstAddr32;
            srcAddr8 = (uint8 *)srcAddr32;
            for (idx = 0U; idx < Length; idx++)
            {
                rxData8    = *srcAddr8;
                rxData8   &= ((uint8)(dataWidthBitMask & 0xFFU));
                *dstAddr8  = rxData8;
                srcAddr8++;
                dstAddr8++;
            }
        }
        else
        {
            dstAddr16 = (uint16 *)dstAddr32;
            srcAddr16 = (uint16 *)srcAddr32;
            for (idx = 0U; idx < (Length / 2U); idx++)
            {
                rxData16    = *srcAddr16;
                rxData16   &= ((uint16)(dataWidthBitMask & 0xFFFFU));
                *dstAddr16  = rxData16;
                srcAddr16++;
                dstAddr16++;
            }
        }
    }
    else
    {
        /* DataWidth less than or equal to 32, do a word read */
        /* Read from QSPI */
        for (idx = 0U; idx < (Length / 4U); idx++)
        {
            rxData32    = *srcAddr32;
            rxData32   &= dataWidthBitMask;
            *dstAddr32  = rxData32;
            srcAddr32++;
            dstAddr32++;
        }
    }

    return;
}

#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)

static void Spi_qspiXferDataMemMappedDma(void *dst, void *src, uint16 length)
{
    Cdd_Dma_ParamEntry edmaParam0, edmaParam1;
    uint32             remaining_size, size;
    /* Chaining is done here fo DMA transfer so length is divided into logical two sizes */
    size = ((uint32)length) / MAX_EDMA_COUNT;
    /* If size is less then 2 times of MAX_EDMA_COUNT in that case just dividing the length in 2
     * equal sizes */
    if (size < 2U)
    {
        size = ((uint32)length) / 2U;
    }
    else
    { /* In order to prevent the remaining size to become 0 below implementation is done*/
        if ((length % MAX_EDMA_COUNT) == 0U)
        {
            size = (size - 1U) * MAX_EDMA_COUNT;
        }
        else
        {
            size = size * MAX_EDMA_COUNT;
        }
    }
    remaining_size     = length - size;
    uint32 chainOption = (CDD_EDMA_OPT_ITCCHEN_MASK | CDD_EDMA_OPT_TCCHEN_MASK);
    edmaParam0.srcPtr  = src;
    edmaParam0.destPtr = dst;
    if (size > MAX_EDMA_COUNT)
    {
        edmaParam0.aCnt = (uint16)MAX_EDMA_COUNT;
    }
    else
    {
        edmaParam0.aCnt = (uint16)EDMA_QSPI_A_COUNT;
    }
    edmaParam0.bCnt       = (uint16)(size / edmaParam0.aCnt);
    edmaParam0.cCnt       = (uint16)EDMA_QSPI_C_COUNT;
    edmaParam0.bCntReload = (uint16)(size / edmaParam0.aCnt);
    edmaParam0.srcBIdx    = (sint16)edmaParam0.aCnt;
    edmaParam0.destBIdx   = (sint16)edmaParam0.aCnt;
    edmaParam0.srcCIdx    = (sint16)EDMA_QSPI_A_COUNT;
    edmaParam0.destCIdx   = (sint16)EDMA_QSPI_A_COUNT;
    edmaParam0.opt        = (CDD_EDMA_OPT_SYNCDIM_MASK);

    edmaParam1.srcPtr     = (void *)((uint32)(src) + size);
    edmaParam1.destPtr    = (void *)((uint32)(dst) + size);
    edmaParam1.aCnt       = (uint16)EDMA_QSPI_A_COUNT;
    edmaParam1.bCnt       = (uint16)(remaining_size / edmaParam1.aCnt);
    edmaParam1.cCnt       = (uint16)EDMA_QSPI_C_COUNT;
    edmaParam1.bCntReload = (uint16)(remaining_size / edmaParam1.aCnt);
    edmaParam1.srcBIdx    = (sint16)edmaParam1.aCnt;
    edmaParam1.destBIdx   = (sint16)edmaParam1.aCnt;
    edmaParam1.srcCIdx    = (sint16)EDMA_QSPI_A_COUNT;
    edmaParam1.destCIdx   = (sint16)EDMA_QSPI_A_COUNT;
    edmaParam1.opt        = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK);

    Cdd_Dma_ParamSet(Spi_Qspi_Handle, 0, 0, edmaParam0);
    Cdd_Dma_ParamSet(Spi_Qspi_Handle, 1, 0, edmaParam1);
    Cdd_Dma_ChainChannel(Spi_Qspi_Handle, 0, 0, 1, chainOption);
    /* Set manual trigger to start QSPI transfer */
    Cdd_Dma_EnableTransferRegion(Spi_Qspi_Handle, CDD_EDMA_TRIG_MODE_MANUAL);

    if (Spi_Qspi_IsEdmaInterruptEnabled != (boolean)TRUE)
    {
        Spi_qspiTxCompletionStatus(Spi_Qspi_Handle);
    }
}

static void Spi_qspiTxCompletionStatus(uint32 Spi_QspiHandle)
{
    uint8 status;
    status                    = 0U;
    volatile uint32 tempCount = SPI_MAX_TIMEOUT_DURATION;
    if (SPI_MAX_TIMEOUT_DURATION > 8U)
    {
        tempCount = SPI_MAX_TIMEOUT_DURATION / 8U;
    }

    while (status == 0U)
    {
        status = Cdd_Dma_GetStatus(Spi_QspiHandle);
        if ((tempCount <= 0U) && (status == 0U))
        {
#if (SPI_E_HARDWARE_ERROR != SPI_DEM_NO_EVENT)
            /* timeout */
            Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
}
#endif

static Std_ReturnType Spi_qspiXferDummy(uint32 baseAddr, Spi_ChannelObjType *chObj)
{
    uint32         regVal      = 0U;
    uint32         idx         = 0U;
    Std_ReturnType retVal      = (Std_ReturnType)E_OK;
    uint32         dataWidth   = 0U;
    uint32         qspiXferCmd = 0U;

    /* switch to cfg port mode */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S, QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    if (Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd) == (boolean)TRUE)
    {
        for (idx = 0U; idx < chObj->numWordsTxRx; idx++)
        {
            Spi_qspiWriteData(baseAddr, chObj);
            regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
            qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
            dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
            Spi_qspiSetCommandReg(baseAddr, regVal);
        }
    }
    else
    {
        for (idx = 0U; idx < chObj->numWordsTxRx; idx++)
        {
            regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
            qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
            dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
            Spi_qspiSetCommandReg(baseAddr, regVal);
            Spi_qspiReadData(baseAddr, chObj);
        }
    }

    return (retVal);
}

static Std_ReturnType Spi_qspiXferData(uint32 baseAddr, Spi_ChannelObjType *chObj)
{
    uint32         regVal      = 0U;
    uint32         idx         = 0U;
    Std_ReturnType retVal      = (Std_ReturnType)E_OK;
    uint32         dataWidth   = 0U;
    uint32         qspiXferCmd = 0U;

    /* switch to cfg port mode */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S, QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    if (Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd) == (boolean)TRUE)
    {
        for (idx = 0U; idx < chObj->numWordsTxRx; idx++)
        {
            Spi_qspiWriteData(baseAddr, chObj);
            regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
            qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
            dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
            Spi_qspiSetCommandReg(baseAddr, regVal);
        }
    }
    else
    {
        for (idx = 0U; idx < chObj->numWordsTxRx; idx++)
        {
            regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
            qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
            dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
            HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
            Spi_qspiSetCommandReg(baseAddr, regVal);
            Spi_qspiReadData(baseAddr, chObj);
        }
    }

    return (retVal);
}

static Std_ReturnType Spi_qspiXferDummyAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift)
{
    uint32         regVal      = 0U;
    Std_ReturnType retVal      = (Std_ReturnType)E_OK;
    uint32         dataWidth   = 0U;
    uint32         qspiXferCmd = 0U;

    /* switch to cfg port mode */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S, QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    if (Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd) == (boolean)TRUE)
    {
        Spi_qspiWriteDataAsync(baseAddr, chObj, shift);
        regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
        qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
        dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
        HW_WR_REG32(baseAddr + QSPI_SPI_CMD_REG, regVal);
    }
    else
    {
        regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
        qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
        dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
        HW_WR_REG32(baseAddr + QSPI_SPI_CMD_REG, regVal);
    }

    return (retVal);
}

static Std_ReturnType Spi_qspiXferDataAsync(uint32 baseAddr, Spi_ChannelObjType *chObj, uint32 shift)
{
    uint32         regVal      = 0U;
    Std_ReturnType retVal      = (Std_ReturnType)E_OK;
    uint32         dataWidth   = 0U;
    uint32         qspiXferCmd = 0U;

    /* switch to cfg port mode */
    HW_WR_FIELD32(baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S, QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    if (Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd) == (boolean)TRUE)
    {
        Spi_qspiWriteDataAsync(baseAddr, chObj, shift);
        regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
        qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
        dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
        HW_WR_REG32(baseAddr + QSPI_SPI_CMD_REG, regVal);
    }
    else
    {
        regVal      = HW_RD_REG32(baseAddr + QSPI_SPI_CMD_REG);
        qspiXferCmd = (uint32)chObj->chCfg.qspiXferCmd;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_CMD, qspiXferCmd);
        dataWidth = (uint32)chObj->chCfg.dataWidth - (uint32)1u;
        HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, dataWidth);
        HW_WR_REG32(baseAddr + QSPI_SPI_CMD_REG, regVal);
    }

    return (retVal);
}

void Spi_qspiInit(const Spi_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr = 0U;
    uint32 regVal   = 0U;

    baseAddr = hwUnitObj->baseAddr;
    /* Put QSPI in no-idle mode */
    HW_WR_FIELD32(baseAddr + QSPI_SYSCONFIG, QSPI_SYSCONFIG_IDLE_MODE, QSPI_SYSCONFIG_IDLE_MODE_NO_IDLE);
    /* Clear any pending interrupt status */
    Spi_qspiClearAllIrqStatus(baseAddr);
    /* Disable interrupts by default. Enable if required at runtime */
    regVal = 0U;
    HW_SET_FIELD32(regVal, QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR, QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_ACTIVE);
    HW_SET_FIELD32(regVal, QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR, QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_ACTIVE);
    /* Disable WIRQ/FIRQ QSPI interrupts */
    HW_WR_REG32(baseAddr + QSPI_INTR_ENABLE_CLEAR_REG, regVal);

    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_WLEN, 0);
    HW_SET_FIELD32(regVal, QSPI_SPI_CMD_REG_FLEN, 1);

    Spi_qspiSetCommandReg(baseAddr, regVal);
}

void Spi_qspiDeInit(const Spi_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr = 0U;
    uint32 regVal   = 0U;

    baseAddr = hwUnitObj->baseAddr;
    /* Clear any pending interrupt status */
    Spi_qspiClearAllIrqStatus(baseAddr);
    /* Disable interrupts on exit */
    regVal = 0U;
    HW_SET_FIELD32(regVal, QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR, QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_ACTIVE);
    HW_SET_FIELD32(regVal, QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR, QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_ACTIVE);
    /* Disable WIRQ/FIRQ QSPI interrupts */
    HW_WR_REG32(baseAddr + QSPI_INTR_ENABLE_CLEAR_REG, regVal);
    /* Take QSPI out of idle */
    HW_WR_FIELD32(baseAddr + QSPI_SYSCONFIG, QSPI_SYSCONFIG_IDLE_MODE, QSPI_SYSCONFIG_IDLE_MODE_SMART_IDLE);
}

void Spi_qspiConfigJob(const Spi_HwUnitObjType *hwUnitObj, const Spi_JobObjType *jobObj)
{
    uint32                            baseAddr  = 0U;
    uint32                            regVal    = 0U;
    uint32                            csNum     = 0U;
    const Spi_JobConfigType          *jobCfg    = (Spi_JobConfigType *)NULL_PTR;
    Spi_QspiExternalDeviceConfigType *extDevCfg = (Spi_QspiExternalDeviceConfigType *)NULL_PTR;
    Spi_QspiMemSetupConfigType       *memSetup  = (Spi_QspiMemSetupConfigType *)NULL_PTR;

    baseAddr  = hwUnitObj->baseAddr;
    jobCfg    = &jobObj->jobCfg;
    extDevCfg = &jobObj->extDevCfg->qspi;
    memSetup  = &extDevCfg->qspiMemSetup;

    csNum = (uint32)jobCfg->csPin;

    Spi_qspiSetDeviceControl(extDevCfg, baseAddr, csNum);

    /* Set Clock Control register */
    Spi_qspiSetClockControl(baseAddr, extDevCfg->clkDivider);

    regVal = HW_RD_REG32(baseAddr + QSPI_SPI_SETUP0_REG + (4U * csNum));

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_RCMD, memSetup->readCmd);

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_NUM_A_BYTES, memSetup->numAddrBytes);

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_NUM_D_BYTES, memSetup->numDummyBytes);

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_READ_TYPE, memSetup->readType);
    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_WCMD, memSetup->writeCmd);
    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_NUM_D_BITS, memSetup->numDummyBits);
    /* Set Memory Map Setup registers */
    HW_WR_REG32(baseAddr + QSPI_SPI_SETUP0_REG + (4U * csNum), regVal);
}

void Spi_qspiConfigJobAsync(const Spi_HwUnitObjType *hwUnitObj, const Spi_JobObjType *jobObj)
{
    uint32                            baseAddr  = 0U;
    uint32                            regVal    = 0U;
    uint32                            csNum     = 0U;
    const Spi_JobConfigType          *jobCfg    = (Spi_JobConfigType *)NULL_PTR;
    Spi_QspiExternalDeviceConfigType *extDevCfg = (Spi_QspiExternalDeviceConfigType *)NULL_PTR;
    Spi_QspiMemSetupConfigType       *memSetup  = (Spi_QspiMemSetupConfigType *)NULL_PTR;

    baseAddr  = hwUnitObj->baseAddr;
    jobCfg    = &jobObj->jobCfg;
    extDevCfg = &jobObj->extDevCfg->qspi;
    memSetup  = &extDevCfg->qspiMemSetup;

    csNum = (uint32)jobCfg->csPin;

    Spi_qspiSetDeviceControl(extDevCfg, baseAddr, csNum);

    /* Set Clock Control register */
    Spi_qspiSetClockControl(baseAddr, extDevCfg->clkDivider);

    regVal = HW_RD_REG32(baseAddr + QSPI_SPI_SETUP0_REG + (4U * csNum));

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_RCMD, memSetup->readCmd);

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_NUM_A_BYTES, memSetup->numAddrBytes);

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_NUM_D_BYTES, memSetup->numDummyBytes);

    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_READ_TYPE, memSetup->readType);
    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_WCMD, memSetup->writeCmd);
    HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_NUM_D_BITS, memSetup->numDummyBits);
    /* Set Memory Map Setup registers */
    HW_WR_REG32(baseAddr + QSPI_SPI_SETUP0_REG + (4U * csNum), regVal);
}

void Spi_AsyncIntrDisable(uint32 baseAddr)
{
    HW_WR_FIELD32(baseAddr + QSPI_INTR_ENABLE_CLEAR_REG, QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR,
                  QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_ACTIVE);
    HW_WR_FIELD32(baseAddr + QSPI_INTR_ENABLE_CLEAR_REG, QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR,
                  QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_ACTIVE);
}

void Spi_qspiConfigCh(Spi_ChannelObjType *chObj)
{
    /* Reset counter and other params */
    chObj->curTxBufPtr = chObj->txBufPtr;
    chObj->curRxBufPtr = chObj->rxBufPtr;
    chObj->curTxWords  = 0U;
    chObj->curRxWords  = 0U;
    if (chObj->chCfg.dataWidth < 9U)
    {
        chObj->bufWidth = 8U;
    }
    else if (chObj->chCfg.dataWidth < 17U)
    {
        chObj->bufWidth = 16U;
    }
    else
    {
        chObj->bufWidth = 32U;
    }
}

void Spi_qspiClearAllIrqStatus(uint32 baseAddr)
{
    uint32 regVal = 0U;

    /* Clear any pending interrupt status */
    regVal = HW_RD_REG32(baseAddr + QSPI_INTR_STATUS_ENABLED_CLEAR);
    HW_SET_FIELD32(regVal, QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA, QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_ACTIVE);
    HW_SET_FIELD32(regVal, QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA, QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_ACTIVE);
    HW_WR_REG32(baseAddr + QSPI_INTR_STATUS_ENABLED_CLEAR, regVal);
}

Spi_JobResultType Spi_qspiXferJob(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                  Spi_ChannelObjType chList[])
{
    Spi_JobResultType        jobResult = SPI_JOB_OK;
    const Spi_JobConfigType *jobCfg    = &jobObj->jobCfg;

    Spi_ChannelObjType *chObj;
    uint32              wrCmdFlag          = 0U;
    uint32              idx                = 0U;
    uint32              memMapEnableFlag   = (uint32)FALSE;
    uint32              Avoid_nesting_flag = 0U;

    if (((uint8)TRUE) == jobCfg->qspiEnableMemMapMode)
    {
        memMapEnableFlag = (uint32)TRUE;
        /* Check if data channel is configured in read mode, as write in mem
         * mapped mode is not supported we will make it config mode write
         */
        for (idx = 0U; idx < jobCfg->channelPerJob; idx++)
        {
            chObj              = &chList[jobObj->jobCfg.channelList[idx]];
            Avoid_nesting_flag = 0U;
            if (SPI_QSPI_SFI_CHMODE_DATA == chObj->chCfg.qspiChMode)
            {
                wrCmdFlag          = Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd);
                Avoid_nesting_flag = 1U;
            }
            if ((Avoid_nesting_flag == 1U) && (wrCmdFlag == (boolean)TRUE))
            {
                /*
                 * User has configured write in Memmapped mode which is not
                 * supported by IP, so doing config mode write.
                 */
                memMapEnableFlag = (uint32)FALSE;
            }
        }
    }

    if ((uint32)TRUE == memMapEnableFlag)
    {
        jobResult = Spi_qspiXferJobMemMapped(hwUnitObj, jobObj, chList);
    }
    else
    {
        jobResult = Spi_qspiXferJobNonMemMapped(hwUnitObj, jobObj, chList);
    }

    return (jobResult);
}

Spi_JobResultType Spi_qspiXferJobAsync(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                       Spi_ChannelObjType chList[])
{
    Spi_JobResultType        jobResult        = SPI_JOB_OK;
    const Spi_JobConfigType *jobCfg           = &jobObj->jobCfg;
    Spi_ChannelObjType      *chObj            = (Spi_ChannelObjType *)NULL_PTR;
    uint32                   wrCmdFlag        = 0U;
    uint32                   idx              = 0U;
    uint32                   memMapEnableFlag = (uint32)FALSE;
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    if (((uint8)TRUE) == jobCfg->qspiEnableMemMapMode)
    {
        memMapEnableFlag = (uint32)TRUE;
        /* Check if data channel is configured in read mode, as write in mem
         * mapped mode is not supported we will make it config mode write
         */
        for (idx = 0U; idx < jobCfg->channelPerJob; idx++)
        {
            chObj              = &chList[jobObj->jobCfg.channelList[idx]];
            Avoid_nesting_flag = 0U;
            if (SPI_QSPI_SFI_CHMODE_DATA == chObj->chCfg.qspiChMode)
            {
                wrCmdFlag          = Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd);
                Avoid_nesting_flag = 1U;
            }
            if ((Avoid_nesting_flag == 1U) && (wrCmdFlag == (boolean)TRUE))
            {
                /*
                 * User has configured write in Memmapped mode which is not
                 * supported by IP, so doing config mode write.
                 */
                memMapEnableFlag = (uint32)FALSE;
            }
        }
    }

    if ((uint32)TRUE == memMapEnableFlag)
    {
#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)
        jobResult = Spi_qspiXferJobMemMappedDma(hwUnitObj, jobObj, chList);
#endif
    }
    else
    {
        jobResult = Spi_qspiXferJobNonMemMappedAsync(hwUnitObj, jobObj, chList);
    }

    return (jobResult);
}

#if (STD_ON == SPI_REGISTER_READBACK_API)

void Spi_qspiRegReadback(const Spi_HwUnitObjType *hwUnitObj, Spi_RegisterReadbackType *RegRbPtr)
{
    uint32 baseAddr = 0U;

    baseAddr                = hwUnitObj->baseAddr;
    RegRbPtr->qspiPid       = HW_RD_REG32(baseAddr + QSPI_PID);
    RegRbPtr->qspiSysConfig = HW_RD_REG32(baseAddr + QSPI_SYSCONFIG);
}

#endif /* #if (STD_ON == SPI_CFG_REGISTER_READBACK_API) */

static Spi_JobResultType Spi_qspiXferJobMemMapped(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                  Spi_ChannelObjType chList[])
{
    uint32                   idx       = 0U;
    Spi_JobResultType        jobResult = SPI_JOB_OK;
    uint32                   regVal, addrOffset = 0U;
    const Spi_JobConfigType *jobCfg = &jobObj->jobCfg;
    Spi_ChannelObjType      *chObj;
    uint32                   Avoid_nesting_flag = 0U;

    for (idx = 0U; idx < jobObj->jobCfg.channelPerJob; idx++)
    {
        chObj = &chList[jobObj->jobCfg.channelList[idx]];
        Spi_qspiConfigCh(chObj);

        Avoid_nesting_flag = 0U;
        if (SPI_QSPI_SFI_CHMODE_CMD == chObj->chCfg.qspiChMode)
        {
            /* Configure QSPI Mem Map set up register for memmapped
             *access */
            regVal = HW_RD_REG32(hwUnitObj->baseAddr + QSPI_SPI_SETUP0_REG + (4U * (uint32)jobCfg->csPin));
            /* Modify read write command in set up registe as
             * per command channel */
            HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_RCMD, *(chObj->txBufPtr));
            /* Set Memory Map Setup registers */
            HW_WR_REG32(hwUnitObj->baseAddr + QSPI_SPI_SETUP0_REG + (4U * (uint32)jobCfg->csPin), regVal);
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_QSPI_SFI_CHMODE_ADDR == chObj->chCfg.qspiChMode))
        {
            /*
             * In mem mapped mode, address offset is used for pointer
             * manipulation while doing data read in next job
             */
            if (0U == addrOffset)
            {
                /* Store only the first offset as the second one is dummy */
                addrOffset = Spi_qspiGetChTxData(chObj);
            }
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_QSPI_SFI_CHMODE_DUMMY == chObj->chCfg.qspiChMode))
        {
            Avoid_nesting_flag = 1U;
        }
        if (Avoid_nesting_flag == 0U) /* SPI_QSPI_SFI_CHMODE_DATA */
        {
            Spi_qspiXferDataMemMapped(hwUnitObj->baseAddr, chObj, addrOffset);
        }
        /* Channel completed */
        jobObj->curChIdx++;
    }

    return (jobResult);
}
#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)
static Spi_JobResultType Spi_qspiXferJobMemMappedDma(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                     Spi_ChannelObjType chList[])
{
    uint32 idx = 0U;

    uint32                  *srcAddr32 = (uint32 *)NULL_PTR;
    uint32                  *dstAddr32 = (uint32 *)NULL_PTR;
    uint16                   length    = 0U;
    Spi_JobResultType        jobResult = SPI_JOB_OK;
    uint32                   regVal, addrOffset = 0U;
    const Spi_JobConfigType *jobCfg = &jobObj->jobCfg;

    Spi_ChannelObjType *chObj;
    uint32              Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    for (idx = 0U; idx < jobObj->jobCfg.channelPerJob; idx++)
    {
        chObj = &chList[jobObj->jobCfg.channelList[idx]];
        Spi_qspiConfigCh(chObj);

        Avoid_nesting_flag = 0U;
        if (SPI_QSPI_SFI_CHMODE_CMD == chObj->chCfg.qspiChMode)
        {
            /* Configure QSPI Mem Map set up register for memmapped
             *access */
            regVal = HW_RD_REG32(hwUnitObj->baseAddr + QSPI_SPI_SETUP0_REG + (4U * (uint32)jobCfg->csPin));
            /* Modify read write command in set up registe as
             * per command channel */
            HW_SET_FIELD32(regVal, QSPI_SPI_SETUP_REG_RCMD, *(chObj->txBufPtr));
            /* Set Memory Map Setup registers */
            HW_WR_REG32(hwUnitObj->baseAddr + QSPI_SPI_SETUP0_REG + (4U * (uint32)jobCfg->csPin), regVal);
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_QSPI_SFI_CHMODE_ADDR == chObj->chCfg.qspiChMode))
        {
            /*
             * In mem mapped mode, address offset is used for pointer
             * manipulation while doing data read in next job
             */
            if (0U == addrOffset)
            {
                /* Store only the first offset as the second one is dummy */
                addrOffset = Spi_qspiGetChTxData(chObj);
            }
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_QSPI_SFI_CHMODE_DUMMY == chObj->chCfg.qspiChMode))
        {
            Avoid_nesting_flag = 1U;
        }
        if (Avoid_nesting_flag == 0U) /* SPI_QSPI_SFI_CHMODE_DATA */
        {
            srcAddr32 = (uint32 *)(SOC_QSPI_ADDRSP1_BASE + addrOffset);
            dstAddr32 = (uint32 *)chObj->rxBufPtr;
            length    = chObj->numWordsTxRx;
            HW_WR_FIELD32(hwUnitObj->baseAddr + QSPI_SPI_SWITCH_REG, QSPI_SPI_SWITCH_REG_MMPT_S,
                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);

            Spi_qspiXferDataMemMappedDma(dstAddr32, srcAddr32, length);
        }
        /* Channel completed */
        jobObj->curChIdx++;
    }

    return (jobResult);
}
#endif

static Spi_JobResultType Spi_qspiXferJobNonMemMapped(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                     Spi_ChannelObjType chList[])
{
    uint32            idx       = 0U;
    Spi_JobResultType jobResult = SPI_JOB_OK;
    Std_ReturnType    retVal    = 0U;

    Spi_ChannelObjType *chObj;

    for (idx = 0U; idx < jobObj->jobCfg.channelPerJob; idx++)
    {
        chObj = &chList[jobObj->jobCfg.channelList[idx]];
        Spi_qspiConfigCh(chObj);
        if (SPI_QSPI_SFI_CHMODE_CMD == chObj->chCfg.qspiChMode)
        {
            retVal = Spi_qspiXferCmd(hwUnitObj->baseAddr, (const Spi_JobObjType *)jobObj, chList,
                                     (uint32)chObj->chCfg.channelId);
        }
        else if (SPI_QSPI_SFI_CHMODE_ADDR == chObj->chCfg.qspiChMode)
        {
            retVal = Spi_qspiXferAddr(hwUnitObj->baseAddr, chObj);
        }
        else if (SPI_QSPI_SFI_CHMODE_DUMMY == chObj->chCfg.qspiChMode)
        {
            retVal = Spi_qspiXferDummy(hwUnitObj->baseAddr, chObj);
        }
        else /* SPI_QSPI_SFI_CHMODE_DATA */
        {
            retVal = Spi_qspiXferData(hwUnitObj->baseAddr, chObj);
        }

        if (((Std_ReturnType)E_OK) != retVal)
        {
            jobResult = SPI_JOB_FAILED;
            break;
        }
        /* Channel completed */
        jobObj->curChIdx++;
    }

    return (jobResult);
}

static Spi_JobResultType Spi_qspiXferJobNonMemMappedAsync(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                                          Spi_ChannelObjType chList[])
{
    uint32              idx       = 0;
    Spi_JobResultType   jobResult = SPI_JOB_OK;
    Std_ReturnType      retVal    = E_OK;
    Spi_ChannelObjType *chObj     = (Spi_ChannelObjType *)NULL_PTR;

    chObj = &chList[jobObj->jobCfg.channelList[idx]];
    Spi_qspiConfigCh(chObj);
    retVal = Spi_qspiXferCmdAsync(

        hwUnitObj->baseAddr, (Spi_JobObjType *)jobObj, chList, (uint32)chObj->chCfg.channelId);

    if (((Std_ReturnType)E_OK) != retVal)
    {
        jobResult = SPI_JOB_FAILED;
    }
    /* Channel completed */

    return (jobResult);
}

static uint32 Spi_qspiGetChTxData(Spi_ChannelObjType *chObj)
{
    uint32        dataWidth     = 0U;
    uint32        TxData        = 0U;
    const uint8  *tempBuf8      = (uint8 *)NULL_PTR;
    uint8         tempBufdata8  = 0U;
    const uint16 *tempBuf16     = (uint16 *)NULL_PTR;
    uint16        tempBufdata16 = 0U;
    const uint32 *tempBuf32     = (uint32 *)NULL_PTR;
    uint32        tempBufdata32 = 0U;

    dataWidth = chObj->chCfg.dataWidth;
    if (dataWidth <= 8U)
    {
        tempBuf8     = (const uint8 *)chObj->curTxBufPtr;
        tempBufdata8 = *tempBuf8;
        TxData       = tempBufdata8;
        chObj->curTxBufPtr++;
    }
    else if (dataWidth <= 16U)
    {
        tempBuf16     = (const uint16 *)chObj->curTxBufPtr;
        tempBufdata16 = *tempBuf16;
        TxData        = tempBufdata16;
        chObj->curTxBufPtr++;
        chObj->curTxBufPtr++;
    }
    else
    {
        /* dataWidth less than 32 */

        tempBuf32     = (const uint32 *)chObj->curTxBufPtr;
        tempBufdata32 = *tempBuf32;
        TxData        = tempBufdata32;
        chObj->curTxBufPtr++;
        chObj->curTxBufPtr++;
        chObj->curTxBufPtr++;
        chObj->curTxBufPtr++;
    }

    return (TxData);
}

static uint32 Spi_qspiGetChTxDataAsync(Spi_ChannelObjType *chObj, uint32 shift)
{
    uint32        dataWidth     = 0U;
    uint32        TxData        = 0U;
    const uint8  *tempBuf8      = (uint8 *)NULL_PTR;
    uint8         tempBufdata8  = 0U;
    const uint16 *tempBuf16     = (uint16 *)NULL_PTR;
    uint16        tempBufdata16 = 0U;
    const uint32 *tempBuf32     = (uint32 *)NULL_PTR;
    uint32        tempBufdata32 = 0U;

    dataWidth = chObj->chCfg.dataWidth;
    if (dataWidth <= 8U)
    {
        chObj->curTxBufPtr += shift;
        tempBuf8            = (const uint8 *)chObj->curTxBufPtr;
        tempBufdata8        = *tempBuf8;
        TxData              = tempBufdata8;
    }
    else if (dataWidth <= 16U)
    {
        chObj->curTxBufPtr += shift;
        chObj->curTxBufPtr += shift;
        tempBuf16           = (const uint16 *)chObj->curTxBufPtr;
        tempBufdata16       = *tempBuf16;
        TxData              = tempBufdata16;
    }
    else
    {
        /* dataWidth less than 32 */
        chObj->curTxBufPtr += shift;
        chObj->curTxBufPtr += shift;
        chObj->curTxBufPtr += shift;
        chObj->curTxBufPtr += shift;
        tempBuf32           = (const uint32 *)chObj->curTxBufPtr;
        tempBufdata32       = *tempBuf32;
        TxData              = tempBufdata32;
    }

    return (TxData);
}

FUNC(void, SPI_CODE) Spi_IrqTxRxQspi(uint32 HwUnit_u32)
{
    Spi_HwUnitObjType  *hwUnitObj  = (Spi_HwUnitObjType *)NULL_PTR;
    Spi_JobObjType     *jobObj     = (Spi_JobObjType *)NULL_PTR;
    Spi_ChannelType     chId       = 0U;
    Spi_ChannelObjType *chObj      = (Spi_ChannelObjType *)NULL_PTR;
    uint32              framelen   = 0U;
    uint32              regVal     = 0U;
    uint32              resetValue = 0U;

    hwUnitObj = Spi_getHwUnitObj((Spi_HWUnitType)HwUnit_u32);
    if (NULL_PTR != hwUnitObj)
    {
        HW_WR_FIELD32(hwUnitObj->baseAddr + QSPI_INTR_STATUS_ENABLED_CLEAR, QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA,
                      QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_ACTIVE);
        HW_WR_FIELD32(hwUnitObj->baseAddr + QSPI_INTR_STATUS_ENABLED_CLEAR, QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA,
                      QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_ACTIVE);

        jobObj   = hwUnitObj->curJobObj;
        regVal   = HW_RD_REG32(hwUnitObj->baseAddr + QSPI_SPI_CMD_REG);
        framelen = HW_GET_FIELD(regVal, QSPI_SPI_CMD_REG_FLEN);
        /*for incrementing channel number in our job */
        if (jobObj == NULL_PTR)
        {
            Spi_AsyncIntrDisable(hwUnitObj->baseAddr);
        }
        else
        {
            jobObj->wordNum++;
            chId  = jobObj->jobCfg.channelList[jobObj->curChIdx];
            chObj = &Spi_DrvObj.channelObj[chId];
            Spi_qspiConfigCh(chObj);

            Spi_qspiCmdCheck(jobObj, chObj, hwUnitObj);

            if (jobObj->wordNum <= framelen)
            {
                Spi_qspiChModeCheck(jobObj, chObj, hwUnitObj);
            }
            else
            {
                Spi_processJobCompletion(jobObj, hwUnitObj, SPI_JOB_OK);
            }
        }
        HW_WR_REG32(hwUnitObj->baseAddr + QSPI_INTC_EOI_REG, resetValue);
    }
}

static void Spi_qspiCmdCheck(Spi_JobObjType *jobObj, Spi_ChannelObjType *chObj, Spi_HwUnitObjType *const hwUnitObj)
{
    if ((Spi_qspiIsReadCmd(chObj->chCfg.qspiXferCmd) == (boolean)TRUE) && (jobObj->wordNum > jobObj->curChIdx))
    {
        Spi_qspiReadDataAsync(hwUnitObj->baseAddr, chObj, jobObj->pointerShifter);
        jobObj->pointerShifter++;
    }
    else if ((Spi_qspiIsWriteCmd(chObj->chCfg.qspiXferCmd) == (boolean)TRUE) && (jobObj->wordNum > jobObj->curChIdx))
    {
        jobObj->pointerShifter++;
    }
    else
    {
        /*Do nothing*/
    }
}

static void Spi_qspiChModeCheck(Spi_JobObjType *jobObj, Spi_ChannelObjType *chObj, Spi_HwUnitObjType *const hwUnitObj)
{
    if (SPI_QSPI_SFI_CHMODE_ADDR == chObj->chCfg.qspiChMode)
    {
        jobObj->curChIdx++;
        Spi_qspiXferAddrAsync(hwUnitObj->baseAddr, chObj, jobObj->pointerShifter);
    }
    else if (SPI_QSPI_SFI_CHMODE_DUMMY == chObj->chCfg.qspiChMode)
    {
        jobObj->curChIdx++;
        Spi_qspiXferDummyAsync(hwUnitObj->baseAddr, chObj, jobObj->pointerShifter);
    }
    else if (SPI_QSPI_SFI_CHMODE_CMD == chObj->chCfg.qspiChMode)
    {
        if (jobObj->IsCmd == FALSE)
        {
            jobObj->IsCmd = TRUE;
            jobObj->curChIdx++;
        }

        Spi_qspiXferCmdAsync(hwUnitObj->baseAddr, (Spi_JobObjType *)jobObj, Spi_DrvObj.channelObj,
                             (uint32)chObj->chCfg.channelId);
    }
    else
    {
        Spi_qspiXferDataAsync(hwUnitObj->baseAddr, chObj, jobObj->pointerShifter);
    }
}
#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)
void Spi_qspiChannelConfig(void)
{
    uint32 status  = E_NOT_OK;
    void  *appdata = &Spi_DrvObj;

    status = Cdd_Dma_CbkRegister(Spi_Qspi_Handle, appdata, (Cdd_Edma_EventCallback)&QSPI_edmaIsrFxn);
    if (status == E_OK)
    {
        Spi_Qspi_IsEdmaInterruptEnabled = TRUE;
    }
}
#endif
static void QSPI_edmaIsrFxn(void)
{
    Spi_HwUnitObjType *hwUnitObj;
    Spi_JobObjType    *jobObj;
    hwUnitObj = Spi_getHwUnitObj((Spi_HWUnitType)SPI_UNIT_QSPI1);
    if (NULL_PTR != hwUnitObj)
    {
        jobObj = hwUnitObj->curJobObj;
        Spi_processJobCompletion(jobObj, hwUnitObj, SPI_JOB_OK);
    }
}
#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
