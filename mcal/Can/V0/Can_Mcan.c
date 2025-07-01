/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include "Can_Priv.h"
#include "EcuM_Cbk.h"
#include "Can_Cfg.h"
#include "SchM_Can.h"
#include "soc.h"
#include "mcan.h"
#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
#include "hw_types.h"
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"
#include "hw_mcanss.h"

/*******************************************************************************
 *  LOCAL DATA DEFINITIONS
 ******************************************************************************/

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name Default Configuration params values
 *
 *  Defines for MCAN Controller default Configuration params
 *  @{
 */
/** \brief  Transmit pause enable */
#define MCAN_TRANSMIT_PAUSE_ENABLE (MCAN_CCCR_TXP_DISABLE)
/** \brief  Edge Filtering during Bus Integration */
#define MCAN_EFBI (MCAN_CCCR_EFBI_DISABLE)
/** \brief  Protocol Exception Handling Enable */
#define MCAN_PROT_EXP_HANDLING_ENABLE (MCAN_CCCR_PXHD_DISABLE)
/** \brief  Emulation Enable */
#define MCAN_EMU_ENABLE (MCAN_MCANSS_CTRL_EMUEN_DISABLE)
/** \brief  Emulation Fast Ack */
#define MCAN_EMU_FAST_ACK (MCAN_MCANSS_CTRL_EMUFACK_DISABLE)
/** \brief  Clock Stop Fast Ack */
#define MCAN_CLK_STOP_FAST_ACK (MCAN_MCANSS_CTRL_CLKFACK_DISABLE)
/** \brief  Start value of the Message RAM Watchdog Counter */
#define MCAN_WDC_PRELOAD (MCAN_RWD_WDC_DISABLE)
/** \brief  Transmitter Delay Compensation Filter Window Length */
#define MCAN_TRCV_DELAY_COMP_WIN (0U)
/** \brief  MCAN Extension ID mask*/
#define APP_MCAN_EXT_ID_AND_MASK (0x1FFFFFFFU)

/**
 *  \name Elements Size
 *
 *  Defines for MCAN Message RAM Elements Size in Words
 *  @{
 */
/** \brief  Standard ID Filter Element Size */
#define MCAN_MSG_RAM_STD_ELEM_SIZE (1U)
/** \brief  Extended ID Filter Element Size */
#define MCAN_MSG_RAM_EXT_ELEM_SIZE (2U)
/** \brief  Tx/Rx Mailbox Size */
#define MCAN_MSG_RAM_TX_RX_ELEM_SIZE (18U)

#define XTD_MSGID_MASK  ((uint32)0x1fffffffU)
#define STD_MSGID_MASK  ((uint32)0x7ffU)
#define STD_MSGID_SHIFT (18U)
#define MSGID_FD_SHIFT  (30U)
#define CAN_ID_STD      (0x0U)
#define CAN_ID_XTD      (0x1U)
#define CAN_ID_MIXED    (0x2U)

#define CAN_MSG_ID_TYPE_STD      ((uint32)0x0U)
#define CAN_MSG_ID_TYPE_EXT      ((uint32)0x80000000U)
#define CAN_MSG_TYPE_MASK        ((uint32)0x40000000U)
#define CAN_MSG_TYPE_CLASSIC_CAN ((uint32)0x0U)
#define CAN_MSG_TYPE_CAN_FD      ((uint32)0x40000000U)

/**
 *  \name Default Interrupt Enable Mask
 *
 *  Defines for MCAN Controller default Interrupt Mask
 *  NOTE: User can change this mask
 *  @{
 */

#define MCAN_INTR_MASK                                                                                               \
    ((uint32)MCAN_INTR_SRC_RX_FIFO1_NEW_MSG | (uint32)MCAN_INTR_SRC_TRANS_CANCEL_FINISH |                            \
     (uint32)MCAN_INTR_SRC_TIMEOUT | (uint32)MCAN_INTR_SRC_BUS_OFF_STATUS | (uint32)MCAN_INTR_SRC_PROTOCOL_ERR_ARB | \
     (uint32)MCAN_INTR_SRC_PROTOCOL_ERR_DATA | (uint32)MCAN_INTR_SRC_RX_FIFO0_NEW_MSG |                              \
     (uint32)MCAN_INTR_SRC_RX_FIFO0_MSG_LOST | (uint32)MCAN_INTR_SRC_TRANS_COMPLETE |                                \
     (uint32)MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG | (uint32)MCAN_INTR_SRC_BUS_OFF_STATUS)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void Can_mcanInit(MCAN_InitParams *initParams, const Can_ControllerType *canControllerCfg,
                         const Can_ControllerType_PC *canControllerCfg_PC);

void Can_mcanConfig(const Can_ControllerObjType *canController, uint32 baseAddr);

void Can_mcanSetUpController(uint32 baseAddr);

void Can_mcanMsgRAMConfigInit(Can_FdMsgRAMConfigObjType *canFDMsgRamConfig);

void Can_mcanSetUpMSGRAM(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                         Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt);

void Can_mcanSetUpTxMailbox(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                            Can_ControllerObjType *canControllerCfg, Can_MailboxObjTxType *canTxMessageObj,
                            uint32 htrh);

static void Can_mcanSetUpRxMailbox(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                   uint32 htrh);

static void Can_mcanSetUpRxMailboxBuf(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                      uint32 htrh, uint32 hwFilterIdx);

static void Can_mcanSetUpRxMailboxStdIdFifo(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                            uint32 htrh, uint32 hwFilterIdx);

static void Can_mcanSetUpRxMailboxExtIdFifo(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                            uint32 htrh, uint32 hwFilterIdx);

void Can_mcanMsgRAMConfig(uint32 baseAddr, Can_FdMsgRAMConfigObjType *canFDMsgRamConfig);

void Can_mcanInitInterrupt(Can_ControllerObjType *controllerObj);

static void Can_mcanCancelPendMsg(uint32 baseAddr);

static void Can_WaitInternal(uint32 baseAddr, uint32 bitPos, uint32 bitIndex);

static void Can_mcanSetId(const Can_PduType *PduInfo, const Can_MailboxType *mailboxCfg, MCAN_TxBufElement *elem);

static inline uint32 Can_mcanGetID(const uint32 idType, const uint32 CanId);
static void          Can_mcanRamInitDone(uint32 baseAddr);

static void Can_MailboxInitialize(Can_ControllerObjType *canController, Can_MailboxObjTxType *canTxMessageObj,
                                  const Can_MailboxType *mailboxCfg);

static void Can_GetFilterMask(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg, uint32 htrh,
                              uint32 hwFilterIdx);

static void Can_CheckCsStarted(Can_ControllerObjType *canController, uint32 baseAddr);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define CAN_START_SEC_VAR_INIT_8
#include "Can_MemMap.h"

static const uint8 Can_McanDataSize[16] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U};

#define CAN_STOP_SEC_VAR_INIT_8
#include "Can_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"

/*******************************************************************************
 * Can_mcanRamInitDone
 ******************************************************************************/
/*! \brief      Checks the initialization of Message RAM done or not.
 *
 *  \param[in]  uint32 baseAddr -  Base Address of controller
 *
 ******************************************************************************/
static void Can_mcanRamInitDone(uint32 baseAddr)
{
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 9U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 9U;
    }
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    /* Wait for FSM to to come out of reset */
    while (MCAN_isMemInitDone(baseAddr) != (uint32)TRUE)
    {
        /* Below API can change start time, so use temp variable */
        if (tempCount <= 0U)
        {
            /* timeout */
#ifdef CAN_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
}

void Can_hwUnitConfig(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                      Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt)
{
    uint32                       baseAddr;
    const Can_ControllerType    *canControllerCfg;
    const Can_ControllerType_PC *canControllerCfg_PC;
    MCAN_InitParams              initParams;

    canControllerCfg    = &canController->canControllerConfig;
    canControllerCfg_PC = &canController->canControllerConfig_PC;

    baseAddr = canControllerCfg_PC->CntrAddr;

    /* Checks the initialization of Message RAM */
    Can_mcanRamInitDone(baseAddr);

    /* Set Up Can Controller */
    Can_mcanSetUpController(baseAddr);

    /* Initialize Init params */
    Can_mcanInit(&initParams, canControllerCfg, canControllerCfg_PC);

    /* Configure MCAN */
    Can_mcanConfig(canController, baseAddr);

    /* Perform the initialization of Message RAM and the mailboxes */
    Can_mcanSetUpMSGRAM(canController, canMailbox, canTxMessageObj, maxMbCnt);

    /* Interrupt is enabled as per the configuration */
    Can_mcanInitInterrupt(canController);
#if (STD_ON == CAN_ECC_ENABLE)
    /* Enable ECC Interrupt */
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_SEC, (uint32)TRUE);
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_DED, (uint32)TRUE);
#endif
}

Std_ReturnType Can_mcanStart(Can_ControllerObjType *controllerObj)
{
    Std_ReturnType      retVal    = E_NOT_OK;
    MCAN_ProtocolStatus errStatus = {0};
    uint32              baseAddr;
    volatile uint32     tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }

    baseAddr = controllerObj->canControllerConfig_PC.CntrAddr;
    /* Put MCAN in operational mode */
    MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_NORMAL);

    {
        /* Wait for FSM to to come out of reset */
        while (((uint32)(MCAN_OPERATION_MODE_NORMAL)) != MCAN_getOpMode(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
#ifdef CAN_E_HARDWARE_ERROR
                /* timeout */
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }

    controllerObj->canState = CAN_CS_STARTED;
    CanIf_ControllerModeIndication(controllerObj->canControllerConfig_PC.ControllerId, CAN_CS_STARTED);
    retVal = E_OK;
    /* Check if there is a busoff */
    MCAN_getProtocolStatus(baseAddr, &errStatus);
    if ((uint32)MCAN_PSR_BO_BUS_OFF == errStatus.busOffStatus)
    {
        /* BusOff Recovery sequence has started */
        controllerObj->canBusOffRecoveryStatus = (boolean)TRUE;
    }
    return retVal;
}

static void Can_mcanCancelPendMsg(uint32 baseAddr)
{
    uint32 txBufPendStatus, bitIndex;

    /* Cancel all pending messages */
    txBufPendStatus = MCAN_getTxBufReqPend(baseAddr);
    for (bitIndex = 0U; bitIndex < 32U; bitIndex++)
    {
        /* For each bit set call cancel request */
        uint32 bitPos = (uint32)1U << bitIndex;
        if (bitPos == (txBufPendStatus & bitPos))
        {
            Can_WaitInternal(baseAddr, bitPos, bitIndex);
        }
    }
}

static void Can_WaitInternal(uint32 baseAddr, uint32 bitPos, uint32 bitIndex)
{
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }
    /* Clear pending Tx request */
    (void)MCAN_txBufCancellationReq(baseAddr, bitIndex);

    {
        /* Wait for FSM to come out of reset */
        while ((MCAN_txBufCancellationStatus(baseAddr) & bitPos) != bitPos)
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
#ifdef CAN_E_HARDWARE_ERROR
                /* timeout */
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }
}
Std_ReturnType Can_mcanStop(Can_ControllerObjType *controllerObj, Can_MailboxObjType *canMailbox,
                            Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt)
{
    Std_ReturnType         retVal = E_NOT_OK;
    uint32                 baseAddr;
    const Can_MailboxType *mailboxCfg;
    baseAddr                                      = controllerObj->canControllerConfig_PC.CntrAddr;
    controllerObj->canFDMsgRamConfig.txAddRequest = 0U;
    uint32          htrh;
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }
    /* cancel pending messages */
    Can_mcanCancelPendMsg(baseAddr);
    /* Initialize Can_MailboxObjTxType params according to configured mailboxes */
    for (htrh = 0U; htrh < maxMbCnt; htrh++)
    {
        mailboxCfg = &canMailbox[htrh].mailBoxConfig;

        if ((CAN_MAILBOX_DIRECTION_TX == mailboxCfg->MBDir) &&
            (mailboxCfg->Controller->ControllerId == controllerObj->canControllerConfig_PC.ControllerId))
        {
            canTxMessageObj[mailboxCfg->HwHandle].freeHwObjectCount = mailboxCfg->CanHwObjectCount;
        }
    }
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_SW_INIT);
    {
        /* Wait for FSM to to come out of reset */
        while (((uint32)MCAN_OPERATION_MODE_SW_INIT) != MCAN_getOpMode(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
#ifdef CAN_E_HARDWARE_ERROR
                /* timeout */
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }

    controllerObj->canState = CAN_CS_STOPPED;
    CanIf_ControllerModeIndication(controllerObj->canControllerConfig_PC.ControllerId, CAN_CS_STOPPED);
    retVal                                 = E_OK;
    controllerObj->canBusOffRecoveryStatus = (boolean)FALSE;

    return retVal;
}

Std_ReturnType Can_mcanSleep(Can_ControllerObjType *controllerObj)
{
    boolean         timeOut = (boolean)FALSE;
    Std_ReturnType  retVal  = E_NOT_OK;
    uint32          baseAddr;
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }
    baseAddr = controllerObj->canControllerConfig_PC.CntrAddr;
    /* Local Power down */
    MCAN_addClockStopRequest(baseAddr, (uint32)TRUE);
    {
        /* Wait for FSM to to come out of reset */
        while ((uint32)MCAN_CCCR_CSA_ACK != MCAN_getClkStopAck(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
                /* timeout */
                timeOut = (boolean)TRUE;
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }
    if (timeOut == (boolean)TRUE)
    {
#ifdef CAN_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    controllerObj->canState = CAN_CS_SLEEP;
    CanIf_ControllerModeIndication(controllerObj->canControllerConfig_PC.ControllerId, CAN_CS_SLEEP);
    retVal                                 = E_OK;
    controllerObj->canBusOffRecoveryStatus = (boolean)FALSE;

    return retVal;
}

Std_ReturnType Can_mcanTestLoopBackModeEnable(uint32 baseAddr, uint8 mode)
{
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_SW_INIT);

    {
        /* Wait for FSM to to come out of reset */
        while (((uint32)MCAN_OPERATION_MODE_SW_INIT) != MCAN_getOpMode(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
#ifdef CAN_E_HARDWARE_ERROR
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }
    if (0U == mode)
    {
        /* Enable Digital Loopback */
        MCAN_lpbkModeEnable(baseAddr, (uint32)MCAN_LPBK_MODE_INTERNAL, (uint32)TRUE);
    }
    else
    {
        /* Enable Analog Loopback */
        MCAN_lpbkModeEnable(baseAddr, (uint32)MCAN_LPBK_MODE_EXTERNAL, (uint32)TRUE);
    }
    tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }
    /* Put MCAN in normal mode of operation */
    MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_NORMAL);
    {
        /* Wait for FSM to to come out of reset */
        while (((uint32)MCAN_OPERATION_MODE_NORMAL) != MCAN_getOpMode(baseAddr))
        {
            /* Below API can change start time, so use temp variable */

            if (tempCount <= 0U)
            {
#ifdef CAN_E_HARDWARE_ERROR
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }
    return (Std_ReturnType)(E_OK);
}

Std_ReturnType Can_mcanTestLoopBackModeDisable(uint32 baseAddr, uint8 mode)
{
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }
    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_SW_INIT);

    {
        /* Wait for FSM to to come out of reset */
        while ((uint32)MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
#ifdef CAN_E_HARDWARE_ERROR
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }
    if (0U == mode)
    {
        /* Enable Digital Loopback */
        MCAN_lpbkModeEnable(baseAddr, (uint32)MCAN_LPBK_MODE_INTERNAL, (uint32)FALSE);
    }
    else
    {
        /* Enable Analog Loopback */
        MCAN_lpbkModeEnable(baseAddr, (uint32)MCAN_LPBK_MODE_EXTERNAL, (uint32)FALSE);
    }
    tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }
    /* Put MCAN in normal mode of operation */
    MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_NORMAL);
    {
        /* Wait for FSM to to come out of reset */
        while (((uint32)(MCAN_OPERATION_MODE_NORMAL)) != MCAN_getOpMode(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
#ifdef CAN_E_HARDWARE_ERROR
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }
    return (Std_ReturnType)(E_OK);
}

void Can_mcanCancelledMessagesReset(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                                    Can_MailboxObjTxType *canTxMessageObj)
{
    uint32                     txStatus = 0U, idx, hth, baseAddr;
    const Can_MailboxType     *mailboxCfg;
    Can_HwHandleType           HwHandle;
    Can_FdMsgRAMConfigObjType *canFDMsgRamConfig;
    canFDMsgRamConfig = &canController->canFDMsgRamConfig;

    baseAddr = canController->canControllerConfig_PC.CntrAddr;

    txStatus  = MCAN_txBufCancellationStatus(baseAddr);
    txStatus &= canFDMsgRamConfig->txAddRequest;
    /* Only 32 Tx Mailboxes are supported by hw */
    while (txStatus != CAN_ZERO)
    {
        idx                              = GET_LOWER_INDEX(txStatus);
        txStatus                        ^= (uint32)1 << idx;
        canFDMsgRamConfig->txAddRequest ^= (uint32)1 << idx;

        hth        = canController->canFDMsgRamConfig.txMbMapping[idx];
        mailboxCfg = &canMailbox[hth].mailBoxConfig;
        HwHandle   = mailboxCfg->HwHandle;
        if (CAN_MAILBOX_DIRECTION_TX == mailboxCfg->MBDir)
        {
            canTxMessageObj[HwHandle].freeHwObjectCount++;
        }
    }
}

uint32 Can_writeGetFreeMsgObj(Can_ControllerObjType *canController, Can_MailboxObjTxType *canTxMessageObj)
{
    uint32                     messageBox = 0, rangeOnes = 0, rangeFreeBuffers = 0;
    Can_FdMsgRAMConfigObjType *canFDMsgRamConfig;
    canFDMsgRamConfig = &canController->canFDMsgRamConfig;
    rangeOnes         = ONES(canTxMessageObj->higherBuffIdx, canTxMessageObj->lowerBuffIdx);

    rangeFreeBuffers = rangeOnes & (~(canFDMsgRamConfig->txAddRequest));
    messageBox       = GET_LOWER_INDEX(rangeFreeBuffers);
    return messageBox;
}

Std_ReturnType Can_mcanWriteTxMailbox(const Can_MailboxType *mailboxCfg, Can_ControllerObjType *controllerObj,
                                      uint32 messageBox, const Can_PduType *pduInfo)
{
    uint32            loopCnt, baseAddr;
    uint32            memType;
    uint32            canMessageBox;
    MCAN_TxBufElement elem   = {0};
    PduLengthType     length = 0;
    Std_ReturnType    status = E_OK;
#if (CAN_TRIGGER_TRANSMIT_ENABLE == STD_ON)
    PduInfoType *PduInfoPtr = NULL;
#endif

    baseAddr = mailboxCfg->Controller->CntrAddr;
    /* Frame Tx message element */
    elem.rtr = 0U;
    elem.esi = 0U;
    if (CAN_MSG_TYPE_CLASSIC_CAN == (pduInfo->id & CAN_MSG_TYPE_MASK))
    {
        elem.brs = 0U;
        elem.fdf = 0U;
    }
    else
    {
        elem.brs = 1U;
        elem.fdf = 1U;
    }
    elem.efc = 0U;
    elem.mm  = 0U;
    Can_mcanSetId(pduInfo, mailboxCfg, &elem);
#if (CAN_TRIGGER_TRANSMIT_ENABLE == STD_ON)
    if (mailboxCfg->CanTriggerTransmitEnable == TRUE && pduInfo->sdu == NULL)
    {
        status = CanIf_TriggerTransmit(pduInfo->id, PduInfoPtr);
        if (status == E_OK)
        {
            length    = PduInfoPtr->SduLength;
            elem.data = PduInfoPtr->SduDataPtr;
        }
    }
    else
#endif
    {
        /* Copy payload into message element */
        elem.data = pduInfo->sdu;
        length    = pduInfo->length;
    }
    if (status == E_OK)
    {
        if (length < (PduLengthType)9)
        {
            elem.data_length = length;
        }
        else if (length < (PduLengthType)25)
        {
            elem.data_length = 0x07U + (((uint32)length - (0x01U)) >> (0x02U));
        }
        else
        {
            elem.data_length = (uint32)12 + (((uint32)length - (0x01U)) >> (0x04U));
        }
        /* Add padding value to unused to data in payload */
        loopCnt = (uint32)length;
        for (; loopCnt < Can_McanDataSize[elem.data_length]; loopCnt++)
        {
            elem.data[loopCnt] = mailboxCfg->CanFdPaddingValue;
        }
        memType       = (uint32)MCAN_MEM_TYPE_BUF;
        canMessageBox = MCAN_writeMsgRam(baseAddr, memType, messageBox, &elem);
        controllerObj->canFDMsgRamConfig.txPduIdMapping[canMessageBox]  = (Can_HwHandleType)(pduInfo->swPduHandle);
        controllerObj->canFDMsgRamConfig.txAddRequest                  |= (uint32)1 << canMessageBox;
        (void)MCAN_txBufAddReq(baseAddr, canMessageBox);
    }
    return status;
}

/*******************************************************************************
 * Can_mcanGetProtocolStatus
 ******************************************************************************/
/*! \brief      This function will check the Protocol Status register to get
                the error status.
 *
 *  \param[in]  Can_ControllerObjType controller -  The controller for which
 *              the error status is checked.
 *
 *  \param[out] Returns the Can_ErrorStateType errorState
 *  \context
 *****************************************************************************/
Can_ErrorStateType Can_mcanGetProtocolStatus(const Can_ControllerObjType *canController)
{
    uint32              baseAddr;
    MCAN_ProtocolStatus errStatus = {0};
    Can_ErrorStateType  errorState;
    baseAddr = canController->canControllerConfig_PC.CntrAddr;

    /* Check Protocol Staus Register */
    MCAN_getProtocolStatus(baseAddr, &errStatus);
    if (1U == errStatus.busOffStatus)
    {
        errorState = CAN_ERRORSTATE_BUSOFF;
    }
    else if (1U == errStatus.errPassive)
    {
        errorState = CAN_ERRORSTATE_PASSIVE;
    }
    else
    {
        errorState = CAN_ERRORSTATE_ACTIVE;
    }

    return errorState;
}

/* ========================================================================== */
/*                 Internal Functions                                         */
/* ========================================================================== */

static void Can_mcanInit(MCAN_InitParams *initParams, const Can_ControllerType *canControllerCfg,
                         const Can_ControllerType_PC *canControllerCfg_PC)
{
    uint32 baseAddr;

    baseAddr = canControllerCfg_PC->CntrAddr;
    /* Initialize MCAN Init params */
    initParams->fdMode    = (uint32)MCAN_CCCR_FDOE_ENABLE;
    initParams->brsEnable = (uint32)MCAN_CCCR_BRSE_ENABLE;
    if ((boolean)TRUE == canControllerCfg->DefaultBaud->BaudFdRateConfig.BrsSwitch)
    {
        initParams->brsEnable = (uint32)MCAN_CCCR_BRSE_ENABLE;
    }
    else
    {
        initParams->brsEnable = (uint32)MCAN_CCCR_BRSE_DISABLE;
    }
    if ((boolean)TRUE == canControllerCfg_PC->DisableAutoRetransmission)
    {
        initParams->darEnable = (uint32)MCAN_CCCR_DAR_ENABLE;
    }
    else
    {
        initParams->darEnable = (uint32)MCAN_CCCR_DAR_DISABLE;
    }

    initParams->wkupReqEnable  = (uint32)MCAN_MCANSS_CTRL_WAKEUPREQEN_DISABLE;
    initParams->autoWkupEnable = (uint32)MCAN_MCANSS_CTRL_AUTOWAKEUP_DISABLE;

    initParams->txpEnable       = (uint32)MCAN_TRANSMIT_PAUSE_ENABLE;
    initParams->efbi            = (uint32)MCAN_EFBI;
    initParams->pxhddisable     = (uint32)0U;
    initParams->emulationEnable = (uint32)MCAN_EMU_ENABLE;
    initParams->emulationFAck   = (uint32)MCAN_EMU_FAST_ACK;
    initParams->clkStopFAck     = (uint32)MCAN_CLK_STOP_FAST_ACK;
    initParams->wdcPreload      = (uint32)MCAN_WDC_PRELOAD;
    MCAN_init(baseAddr, initParams);
}

void Can_mcanConfig(const Can_ControllerObjType *canController, uint32 baseAddr)
{
    MCAN_ConfigParams            mConfParams;
    MCAN_ECCConfigParams         eccConfigParams;
    MCAN_RxNewDataStatus         newDataStatus;
    const Can_ControllerType_PC *canControllerCfg_PC;

    canControllerCfg_PC = &canController->canControllerConfig_PC;

    /* Initialize Configuration parameters */
    mConfParams.monEnable         = 0U;
    mConfParams.asmEnable         = 0U;
    mConfParams.tsPrescalar       = 0U;
    mConfParams.tsSelect          = 0U;
    mConfParams.timeoutSelect     = 0U;
    mConfParams.timeoutPreload    = 0U;
    mConfParams.timeoutCntEnable  = 0U;
    mConfParams.filterConfig.rrfe = 0x1U;
    mConfParams.filterConfig.rrfs = 0x1U;
    mConfParams.filterConfig.anfe = 0x3U;
    mConfParams.filterConfig.anfs = 0x3U;
    (void)MCAN_config(baseAddr, &mConfParams);
    /* Configure ECC */
#if (STD_ON == CAN_ECC_ENABLE)
    eccConfigParams.enable        = (uint32)MCAN_ECC_AGGR_CONTROL_ECC_ENABLE_ENABLE;
    eccConfigParams.enableChk     = (uint32)MCAN_ECC_AGGR_CONTROL_ECC_CHECK_ENABLE;
    eccConfigParams.enableRdModWr = (uint32)MCAN_ECC_AGGR_CONTROL_ENABLE_RMW_ENABLE;
    MCAN_eccConfig(baseAddr, &eccConfigParams);
#else
    eccConfigParams.enable        = (uint32)MCAN_ECC_AGGR_CONTROL_ECC_ENABLE_DISABLE;
    eccConfigParams.enableChk     = (uint32)MCAN_ECC_AGGR_CONTROL_ECC_CHECK_DISABLE;
    eccConfigParams.enableRdModWr = (uint32)MCAN_ECC_AGGR_CONTROL_ENABLE_RMW_DISABLE;
    MCAN_eccConfig(baseAddr, &eccConfigParams);
#endif
    /* Clear all pending error flags and status */
    MCAN_clearIntrStatus(baseAddr, MCAN_INTR_MASK);
    newDataStatus.statusLow  = MCAN_NDAT1_CLEAR;
    newDataStatus.statusHigh = MCAN_NDAT2_CLEAR;
    MCAN_clearNewDataStatus(baseAddr, &newDataStatus);
    /* Configure Baud rate */
    Can_mcanSetBaudrate(canControllerCfg_PC, canController->canControllerConfig.DefaultBaud);

    /* Set Extended ID Mask */
    (void)MCAN_setExtIDAndMask(baseAddr, APP_MCAN_EXT_ID_AND_MASK);
}

void Can_mcanInitInterrupt(Can_ControllerObjType *controllerObj)
{
    uint32                    *canInterruptMask;
    uint32                     baseAddr;
    Can_FdMsgRAMConfigObjType *canFDMsgRamConfig;
    Can_ControllerType_PC     *canControllerCfg_PC;

    canControllerCfg_PC = &controllerObj->canControllerConfig_PC;
    baseAddr            = canControllerCfg_PC->CntrAddr;
    canFDMsgRamConfig   = &controllerObj->canFDMsgRamConfig;
    canInterruptMask    = &controllerObj->canInterruptMask;

    /* Enable TX Interrupt when it is configured */
    if ((canFDMsgRamConfig->txInterruptMask) != CAN_ZERO)
    {
        *canInterruptMask |= MCAN_IR_TC_MASK;
    }

    /* Enable RX Interrupt for Buffers when it is configured */
    if ((canFDMsgRamConfig->rxLowInterruptMask != CAN_ZERO) || (canFDMsgRamConfig->rxHighInterruptMask != CAN_ZERO))
    {
        *canInterruptMask |= MCAN_IR_DRX_MASK;
    }

    /* Enable RX Interrupt for FIFO new message and message lost
            when it is configured */
    if ((canFDMsgRamConfig->rxFIFO0Num) != CAN_ZERO)
    {
        *canInterruptMask |= MCAN_IR_RF0N_MASK;
        *canInterruptMask |= MCAN_IR_RF0L_MASK;
    }

    /* Enable RX Interrupt for FIFO message lost for FIFO polling messages */
    if ((canFDMsgRamConfig->rxFIFO1Num) != CAN_ZERO)
    {
        *canInterruptMask |= MCAN_IR_RF1L_MASK;
    }

    if ((canControllerCfg_PC->BusOffProcessingInterrupt) != CAN_ZERO)
    {
        *canInterruptMask |= MCAN_IR_BO_MASK;
    }

    if ((*canInterruptMask) != CAN_ZERO)
    {
        MCAN_enableIntr(baseAddr, *canInterruptMask, (uint32)TRUE);
        MCAN_selectIntrLine(baseAddr, *canInterruptMask);
        MCAN_enableIntrLine(baseAddr, (uint32)MCAN_INTR_LINE_NUM_0, (uint32)TRUE);
    }
}

void Can_mcanMsgRAMConfigInit(Can_FdMsgRAMConfigObjType *canFDMsgRamConfig)
{
    uint32 loopCnt                  = 0U;
    canFDMsgRamConfig->stdFilterNum = (uint8)0U;
    canFDMsgRamConfig->extFilterNum = (uint8)0U;

    /* Initialize Message RAM configuration parameters */
    canFDMsgRamConfig->configParams.flssa                = 0U;
    canFDMsgRamConfig->configParams.lss                  = 0U;
    canFDMsgRamConfig->configParams.flesa                = 0U;
    canFDMsgRamConfig->configParams.lse                  = 0U;
    canFDMsgRamConfig->configParams.txStartAddr          = 0U;
    canFDMsgRamConfig->configParams.txBufNum             = 0U;
    canFDMsgRamConfig->configParams.txFIFOSize           = 0U;
    canFDMsgRamConfig->configParams.txBufMode            = 1U;
    canFDMsgRamConfig->configParams.txBufElemSize        = (uint32)MCAN_ELEM_SIZE_64BYTES;
    canFDMsgRamConfig->configParams.txEventFIFOStartAddr = 0U;
    canFDMsgRamConfig->configParams.txEventFIFOSize      = 0U;
    canFDMsgRamConfig->configParams.txEventFIFOWaterMark = 0U;
    canFDMsgRamConfig->configParams.rxFIFO0startAddr     = 0U;
    canFDMsgRamConfig->configParams.rxFIFO0size          = 0U;
    canFDMsgRamConfig->configParams.rxFIFO0waterMark     = 0U;
    canFDMsgRamConfig->configParams.rxFIFO0OpMode        = 0U;
    canFDMsgRamConfig->configParams.rxFIFO1startAddr     = 0U;
    canFDMsgRamConfig->configParams.rxFIFO1size          = 0U;
    canFDMsgRamConfig->configParams.rxFIFO1waterMark     = 0U;
    canFDMsgRamConfig->configParams.rxFIFO1OpMode        = 0U;
    canFDMsgRamConfig->configParams.rxBufStartAddr       = 0U;
    canFDMsgRamConfig->configParams.rxBufElemSize        = (uint32)MCAN_ELEM_SIZE_64BYTES;
    canFDMsgRamConfig->configParams.rxFIFO0ElemSize      = (uint32)MCAN_ELEM_SIZE_64BYTES;
    canFDMsgRamConfig->configParams.rxFIFO1ElemSize      = (uint32)MCAN_ELEM_SIZE_64BYTES;

    canFDMsgRamConfig->txAddRequest        = (uint32)0U;
    canFDMsgRamConfig->txInterruptMask     = (uint32)0U;
    canFDMsgRamConfig->rxLowInterruptMask  = (uint32)0U;
    canFDMsgRamConfig->rxHighInterruptMask = (uint32)0U;

    canFDMsgRamConfig->txBuffNum  = (uint16)0U;
    canFDMsgRamConfig->txFIFONum  = (uint16)0U;
    canFDMsgRamConfig->rxBuffNum  = (uint16)0U;
    canFDMsgRamConfig->rxFIFO0Num = (uint16)0U;
    canFDMsgRamConfig->rxFIFO1Num = (uint16)0U;

    for (loopCnt = 0U; loopCnt < MCAN_STD_FILTER_MAX_NUM; loopCnt++)
    {
        canFDMsgRamConfig->stdMsgIDFilterList[loopCnt].sfid1 = 0U;
        canFDMsgRamConfig->stdMsgIDFilterList[loopCnt].sfid2 = 0U;
        canFDMsgRamConfig->stdMsgIDFilterList[loopCnt].sfec  = 0U;
        canFDMsgRamConfig->stdMsgIDFilterList[loopCnt].sft   = 0x3U;
        canFDMsgRamConfig->stdMbMapping[loopCnt]             = 0xFFU;
    }
    for (loopCnt = 0U; loopCnt < MCAN_EXT_FILTER_MAX_NUM; loopCnt++)
    {
        canFDMsgRamConfig->extMsgIDFilterList[loopCnt].efid1 = 0U;
        canFDMsgRamConfig->extMsgIDFilterList[loopCnt].efid2 = 0U;
        canFDMsgRamConfig->extMsgIDFilterList[loopCnt].efec  = 0U;
        canFDMsgRamConfig->extMsgIDFilterList[loopCnt].eft   = 0x3U;
        canFDMsgRamConfig->extMbMapping[loopCnt]             = 0xFFU;
    }
    for (loopCnt = 0U; loopCnt < MCAN_TX_BUFFER_MAX_NUM; loopCnt++)
    {
        canFDMsgRamConfig->txMbMapping[loopCnt]    = 0xFFU;
        canFDMsgRamConfig->txPduIdMapping[loopCnt] = 0xFFU;
    }
}

void Can_mcanSetUpController(uint32 baseAddr)
{
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 9U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 9U;
    }
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    StatusType status = E_OK;

    /* reset MCAN Module */
    MCAN_reset(baseAddr);
    if (((StatusType)E_OK) == status)
    {
        /* Wait for FSM to to come out of reset */
        while ((uint32)TRUE == MCAN_isInReset(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
                /* Dynamic coverage for the below DEM event is not covered.
                 * Since it is hardware dependent.
                 */

                /* timeout */
#ifdef CAN_E_HARDWARE_ERROR
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                status = E_NOT_OK;
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }

    /* Put MCAN in SW initialization mode */
    MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_SW_INIT);

    if (((StatusType)E_OK) == status)
    {
        tempCount = CAN_TIMEOUT_DURATION;
        if (CAN_TIMEOUT_DURATION > 9U)
        {
            tempCount = CAN_TIMEOUT_DURATION / 9U;
        }
        /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
        /* Wait for FSM to to come out of reset */
        while ((uint32)MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(baseAddr))
        {
            /* Below API can change start time, so use temp variable */
            if (tempCount <= 0U)
            {
                /* Dynamic coverage for the below DEM event is not covered.
                 * Since it is hardware dependent.
                 */

                /* timeout */
#ifdef CAN_E_HARDWARE_ERROR
                (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
                break;
            }
            MCAL_SW_DELAY(tempCount);
        }
    }
}

static void Can_mcanSetUpMbxList(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                                 uint32 maxMbCnt)
{
    uint32                     htrh;
    uint8                      controller;
    const Can_MailboxType     *mailboxCfg;
    const Can_MailboxObjType  *mailBoxCfgList;
    Can_FdMsgRAMConfigObjType *msgRamConfig;

    controller     = canController->canControllerConfig_PC.ControllerId;
    msgRamConfig   = &canController->canFDMsgRamConfig;
    mailBoxCfgList = &canMailbox[0U];
    /* Initialize Message RAM params according to configured mailboxes */
    for (htrh = 0U; htrh < maxMbCnt; htrh++)
    {
        mailboxCfg = &mailBoxCfgList[htrh].mailBoxConfig;
        if ((mailboxCfg->Controller->ControllerId == controller) && (CAN_MAILBOX_DIRECTION_TX == mailboxCfg->MBDir) &&
            (mailboxCfg->CanHwObjectCount == 1U))
        {
            msgRamConfig->txBuffNum += (uint16)1U;
        }
    }
}

void Can_mcanSetUpMSGRAM(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                         Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt)
{
    uint32                     htrh, baseAddr;
    uint8                      controller;
    const Can_MailboxType     *mailboxCfg;
    const Can_MailboxObjType  *mailBoxCfgList;
    Can_FdMsgRAMConfigObjType *msgRamConfig;

    controller     = canController->canControllerConfig_PC.ControllerId;
    mailBoxCfgList = &canMailbox[0U];
    baseAddr       = canController->canControllerConfig_PC.CntrAddr;
    msgRamConfig   = &canController->canFDMsgRamConfig;
    Can_mcanMsgRAMConfigInit(msgRamConfig);
    Can_mcanSetUpMbxList(canController, canMailbox, maxMbCnt);
    /* Initialize Message RAM params according to configured mailboxes */
    for (htrh = 0U; htrh < maxMbCnt; htrh++)
    {
        mailboxCfg = &mailBoxCfgList[htrh].mailBoxConfig;
        if (mailboxCfg->Controller->ControllerId == controller)
        {
            if (CAN_MAILBOX_DIRECTION_RX == mailboxCfg->MBDir)
            {
                Can_mcanSetUpRxMailbox(msgRamConfig, mailboxCfg, htrh);
            }
            if (CAN_MAILBOX_DIRECTION_TX == mailboxCfg->MBDir)
            {
                Can_mcanSetUpTxMailbox(msgRamConfig, mailboxCfg, canController, canTxMessageObj, htrh);
            }
        }
    }
    msgRamConfig->configParams.lss = (uint32)msgRamConfig->stdFilterNum;
    msgRamConfig->configParams.lse = (uint32)msgRamConfig->extFilterNum;

    /* Transmission Interrupt Enabled for Respective Buffers */
    MCAN_txBufTransIntrEnable(baseAddr, msgRamConfig->txInterruptMask);

    /* Configure Message RAM sections:
     * STD/EXT filters, Tx Buffers/FIFO and Rx Buffers/FIFO */
    Can_mcanMsgRAMConfig(baseAddr, msgRamConfig);
}

void Can_mcanSetUpTxMailbox(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                            Can_ControllerObjType *canController, Can_MailboxObjTxType *canTxMessageObj, uint32 htrh)
{
    uint16                 hth = mailboxCfg->HwHandle;
    Can_ControllerType_PC *canControllerCfg_PC;
    canControllerCfg_PC = &canController->canControllerConfig_PC;
    if (mailboxCfg->CanHwObjectCount == 1U)
    {
        uint8 txBuff                      = (uint8)(msgRamConfig->configParams.txBufNum);
        msgRamConfig->txMbMapping[txBuff] = (Can_HwHandleType)htrh;
        /* Prepare Transmission Interrupt Enable Mask */
        if ((canControllerCfg_PC->TxProcessingType == CAN_TX_RX_PROCESSING_INTERRUPT) ||
            ((canControllerCfg_PC->TxProcessingType == CAN_TX_RX_PROCESSING_MIXED) &&
             (mailboxCfg->CanHardwareObjectUsesPolling == (boolean)FALSE)))
        {
            msgRamConfig->txInterruptMask |= ((uint32)1 << (uint32)txBuff);
        }
        canTxMessageObj[hth].lowerBuffIdx    = (uint8)(msgRamConfig->configParams.txBufNum);
        msgRamConfig->configParams.txBufNum += 0x01U;
        canTxMessageObj[hth].higherBuffIdx   = (uint8)(msgRamConfig->configParams.txBufNum);
    }
    else
    {
        uint8 loopCnt;
        uint8 temp                          = (uint8)(msgRamConfig->txBuffNum + msgRamConfig->txFIFONum);
        canTxMessageObj[hth].lowerBuffIdx   = temp;
        msgRamConfig->txFIFONum            += mailboxCfg->CanHwObjectCount;
        canTxMessageObj[hth].higherBuffIdx  = (uint8)(msgRamConfig->txBuffNum + msgRamConfig->txFIFONum);
        for (loopCnt = temp; loopCnt < canTxMessageObj[hth].higherBuffIdx; loopCnt++)
        {
            msgRamConfig->txMbMapping[loopCnt] = (Can_HwHandleType)htrh;
            /* Prepare Transmission Interrupt Enable Mask */
            if ((canControllerCfg_PC->TxProcessingType == CAN_TX_RX_PROCESSING_INTERRUPT) ||
                ((canControllerCfg_PC->TxProcessingType == CAN_TX_RX_PROCESSING_MIXED) &&
                 (mailboxCfg->CanHardwareObjectUsesPolling == (boolean)FALSE)))
            {
                msgRamConfig->txInterruptMask |= ((uint32)1 << (uint32)loopCnt);
            }
        }
        msgRamConfig->configParams.txFIFOSize += (uint32)mailboxCfg->CanHwObjectCount;
    }
}

static void Can_mcanSetUpRxMailbox(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                   uint32 htrh)
{
    uint32                 hwFilterIdx;
    Can_TxRxProcessingType rxProcessingType;

    rxProcessingType = mailboxCfg->Controller->RxProcessingType;

    for (hwFilterIdx = 0U; hwFilterIdx < mailboxCfg->HwFilterCnt; hwFilterIdx++)
    {
        Can_GetFilterMask(msgRamConfig, mailboxCfg, htrh, hwFilterIdx);
    }

    if (mailboxCfg->CanHwObjectCount == 1U)
    {
        if ((rxProcessingType == CAN_TX_RX_PROCESSING_INTERRUPT) ||
            ((rxProcessingType == CAN_TX_RX_PROCESSING_MIXED) &&
             (mailboxCfg->CanHardwareObjectUsesPolling == (boolean)FALSE)))
        {
            if (msgRamConfig->rxBuffNum < (uint16)32)
            {
                msgRamConfig->rxLowInterruptMask |= (uint32)1 << (uint32)(msgRamConfig->rxBuffNum);
            }
            else
            {
                msgRamConfig->rxHighInterruptMask |= (uint32)1 << (msgRamConfig->rxBuffNum - (uint16)32);
            }
        }
        msgRamConfig->rxBuffNum += 1U;
    }
    else
    {
        if ((rxProcessingType == CAN_TX_RX_PROCESSING_INTERRUPT) ||
            ((rxProcessingType == CAN_TX_RX_PROCESSING_MIXED) &&
             (mailboxCfg->CanHardwareObjectUsesPolling == (boolean)FALSE)))
        {
            msgRamConfig->rxFIFO0Num += 1U;
        }
        else
        {
            msgRamConfig->rxFIFO1Num += 1U;
        }
    }
}

static void Can_GetFilterMask(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg, uint32 htrh,
                              uint32 hwFilterIdx)
{
    if (mailboxCfg->CanHwObjectCount > 1U)
    {
        /* Get Filter Mask for HRH - STD */
        if (CAN_ID_STD == mailboxCfg->MBIdType)
        {
            Can_mcanSetUpRxMailboxStdIdFifo(msgRamConfig, mailboxCfg, htrh, hwFilterIdx);
        }
        /* Get Filter Mask for HRH - EXT */
        else if (CAN_ID_XTD == mailboxCfg->MBIdType)
        {
            Can_mcanSetUpRxMailboxExtIdFifo(msgRamConfig, mailboxCfg, htrh, hwFilterIdx);
        }
        /* Get Filter Mask for HRH (+1 for STD and XTD both in
           case of MIXED) */
        else
        {
            Can_mcanSetUpRxMailboxStdIdFifo(msgRamConfig, mailboxCfg, htrh, hwFilterIdx);
            Can_mcanSetUpRxMailboxExtIdFifo(msgRamConfig, mailboxCfg, htrh, hwFilterIdx);
        }
        /* Set Mailbox entry */
    }
    else
    {
        Can_mcanSetUpRxMailboxBuf(msgRamConfig, mailboxCfg, htrh, hwFilterIdx);
    }
}

static void Can_mcanSetUpRxMailboxStdIdFifo(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                            uint32 htrh, uint32 hwFilterIdx)
{
    Can_HwFilterType      *pHwFilter;
    Can_TxRxProcessingType rxProcessingType;
    uint32                 tmpIdValue;
    uint32                 tmpFilterMask;
    uint8                  idx = 0U;

    rxProcessingType = mailboxCfg->Controller->RxProcessingType;
    pHwFilter        = mailboxCfg->HwFilterList[hwFilterIdx];
    tmpIdValue       = pHwFilter->IDValue;
    tmpFilterMask    = pHwFilter->Mask;

    idx                                         = msgRamConfig->stdFilterNum;
    msgRamConfig->stdMsgIDFilterList[idx].sfid1 = (tmpIdValue & STD_MSGID_MASK);
    if (mailboxCfg->CanHandleType == (uint8)CAN_FULL)
    {
        msgRamConfig->stdMsgIDFilterList[idx].sfid2 = (tmpIdValue & STD_MSGID_MASK);
        msgRamConfig->stdMsgIDFilterList[idx].sft   = 0x0U;
    }
    /* Dynamic coverage for the below "else" statement
     * is not covered. Since can handle type FULL is tested.
     */
    else
    {
        msgRamConfig->stdMsgIDFilterList[idx].sfid2 = (tmpFilterMask & STD_MSGID_MASK);
        msgRamConfig->stdMsgIDFilterList[idx].sft   = 0x2U;
    }

    if ((rxProcessingType == CAN_TX_RX_PROCESSING_INTERRUPT) ||
        ((rxProcessingType == CAN_TX_RX_PROCESSING_MIXED) &&
         (mailboxCfg->CanHardwareObjectUsesPolling == (boolean)FALSE)))
    {
        msgRamConfig->stdMsgIDFilterList[idx].sfec  = 0x1U;
        msgRamConfig->configParams.rxFIFO0size     += (uint32)mailboxCfg->CanHwObjectCount;
    }
    else
    {
        msgRamConfig->stdMsgIDFilterList[idx].sfec  = 0x2U;
        msgRamConfig->configParams.rxFIFO1size     += (uint32)mailboxCfg->CanHwObjectCount;
    }
    msgRamConfig->stdMbMapping[idx] = (Can_HwHandleType)htrh;
    msgRamConfig->stdFilterNum++;
}

static void Can_mcanSetUpRxMailboxExtIdFifo(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                            uint32 htrh, uint32 hwFilterIdx)
{
    Can_HwFilterType      *pHwFilter;
    Can_TxRxProcessingType rxProcessingType;
    uint32                 tmpIdValue;
    uint32                 tmpFilterMask;
    uint8                  idx = 0U;

    rxProcessingType = mailboxCfg->Controller->RxProcessingType;
    pHwFilter        = mailboxCfg->HwFilterList[hwFilterIdx];
    tmpIdValue       = pHwFilter->IDValue;
    tmpFilterMask    = pHwFilter->Mask;

    idx                                         = msgRamConfig->extFilterNum;
    msgRamConfig->extMsgIDFilterList[idx].efid1 = (tmpIdValue & XTD_MSGID_MASK);

    if (mailboxCfg->CanHandleType == (uint8)CAN_FULL)
    {
        msgRamConfig->extMsgIDFilterList[idx].efid2 = (tmpIdValue & XTD_MSGID_MASK);
        msgRamConfig->extMsgIDFilterList[idx].eft   = 0x0U;
    }
    else
    {
        msgRamConfig->extMsgIDFilterList[idx].efid2 = (tmpFilterMask & XTD_MSGID_MASK);
        msgRamConfig->extMsgIDFilterList[idx].eft   = 0x2U;
    }

    if ((rxProcessingType == CAN_TX_RX_PROCESSING_INTERRUPT) ||
        ((rxProcessingType == CAN_TX_RX_PROCESSING_MIXED) &&
         (mailboxCfg->CanHardwareObjectUsesPolling == (boolean)FALSE)))
    {
        msgRamConfig->extMsgIDFilterList[idx].efec  = 0x1U;
        msgRamConfig->configParams.rxFIFO0size     += (uint32)mailboxCfg->CanHwObjectCount;
    }
    else
    {
        msgRamConfig->extMsgIDFilterList[idx].efec  = 0x2U;
        msgRamConfig->configParams.rxFIFO1size     += (uint32)mailboxCfg->CanHwObjectCount;
    }
    msgRamConfig->extMbMapping[idx] = (Can_HwHandleType)htrh;
    msgRamConfig->extFilterNum++;
}

static void Can_mcanSetUpRxMailboxBuf(Can_FdMsgRAMConfigObjType *msgRamConfig, const Can_MailboxType *mailboxCfg,
                                      uint32 htrh, uint32 hwFilterIdx)
{
    uint32            tmpIdValue;
    uint8             idx = 0U;
    Can_HwFilterType *pHwFilter;

    pHwFilter  = mailboxCfg->HwFilterList[hwFilterIdx];
    tmpIdValue = pHwFilter->IDValue;

    /* Get Filter Mask for HRH - STD */
    if (CAN_ID_STD == mailboxCfg->MBIdType)
    {
        idx                                         = msgRamConfig->stdFilterNum;
        msgRamConfig->stdMsgIDFilterList[idx].sfid1 = (tmpIdValue & STD_MSGID_MASK);
        msgRamConfig->stdMsgIDFilterList[idx].sfid2 = (uint32)msgRamConfig->rxBuffNum;
        msgRamConfig->stdMsgIDFilterList[idx].sfec  = 0x7U;
        msgRamConfig->stdMsgIDFilterList[idx].sft   = 0x0U;
        msgRamConfig->stdMbMapping[idx]             = (Can_HwHandleType)htrh;
        msgRamConfig->stdFilterNum++;
    }
    /* Get Filter Mask for HRH - EXT */
    else if (CAN_ID_XTD == mailboxCfg->MBIdType)
    {
        idx                                         = msgRamConfig->extFilterNum;
        msgRamConfig->extMsgIDFilterList[idx].efid1 = (tmpIdValue & XTD_MSGID_MASK);
        msgRamConfig->extMsgIDFilterList[idx].efid2 = (uint32)msgRamConfig->rxBuffNum;
        msgRamConfig->extMsgIDFilterList[idx].efec  = 0x7U;
        msgRamConfig->extMsgIDFilterList[idx].eft   = 0x0U;
        msgRamConfig->extMbMapping[idx]             = (Can_HwHandleType)htrh;
        msgRamConfig->extFilterNum++;
    }
    /* Get Filter Mask for HRH
     (+1 for STD and XTD both in case of MIXED) */
    else
    {
        idx                                         = msgRamConfig->stdFilterNum;
        msgRamConfig->stdMsgIDFilterList[idx].sfid1 = (tmpIdValue & STD_MSGID_MASK);
        msgRamConfig->stdMsgIDFilterList[idx].sfid2 = (uint32)msgRamConfig->rxBuffNum;
        msgRamConfig->stdMsgIDFilterList[idx].sfec  = 0x7U;
        msgRamConfig->stdMsgIDFilterList[idx].sft   = 0x0U;
        msgRamConfig->stdMbMapping[idx]             = (Can_HwHandleType)htrh;
        msgRamConfig->stdFilterNum++;

        idx                                         = msgRamConfig->extFilterNum;
        msgRamConfig->extMsgIDFilterList[idx].efid1 = (tmpIdValue & XTD_MSGID_MASK);
        msgRamConfig->extMsgIDFilterList[idx].efid2 = (uint32)msgRamConfig->rxBuffNum;
        msgRamConfig->extMsgIDFilterList[idx].efec  = 0x7U;
        msgRamConfig->extMsgIDFilterList[idx].eft   = 0x0U;
        msgRamConfig->extMbMapping[idx]             = (Can_HwHandleType)htrh;
        msgRamConfig->extFilterNum++;
    }
}

void Can_mcanMsgRAMConfig(uint32 baseAddr, Can_FdMsgRAMConfigObjType *canFDMsgRamConfig)
{
    uint32 startAddr, loopCnt, txMbNum;

    txMbNum = ((uint32)canFDMsgRamConfig->txBuffNum + (uint32)canFDMsgRamConfig->txFIFONum);
    if ((MCAN_TX_BUFFER_MAX_NUM >= txMbNum) &&
        (MCAN_RX_FIFO_0_MAX_NUM >= canFDMsgRamConfig->configParams.rxFIFO0size) &&
        (MCAN_RX_FIFO_1_MAX_NUM >= canFDMsgRamConfig->configParams.rxFIFO1size) &&
        (MCAN_RX_BUFFER_MAX_NUM >= canFDMsgRamConfig->rxBuffNum))
    {
        /* Calculate start address for Message RAM sections */
        startAddr                             = 0U;
        canFDMsgRamConfig->configParams.flssa = 0U;
        startAddr +=
            (uint32)(((uint32)canFDMsgRamConfig->stdFilterNum + (uint32)1U) * (uint32)MCAN_MSG_RAM_STD_ELEM_SIZE * 4U);
        canFDMsgRamConfig->configParams.flesa = startAddr;
        startAddr +=
            (uint32)(((uint32)canFDMsgRamConfig->extFilterNum + (uint32)1U) * (uint32)MCAN_MSG_RAM_EXT_ELEM_SIZE * 4U);
        canFDMsgRamConfig->configParams.txStartAddr = startAddr;
        startAddr += (uint32)(((uint32)canFDMsgRamConfig->configParams.txBufNum + (uint32)1U) *
                              (uint32)MCAN_MSG_RAM_TX_RX_ELEM_SIZE * 4U);
        startAddr += (uint32)(((uint32)canFDMsgRamConfig->configParams.txFIFOSize + (uint32)1U) *
                              (uint32)MCAN_MSG_RAM_TX_RX_ELEM_SIZE * 4U);
        canFDMsgRamConfig->configParams.rxFIFO0startAddr = startAddr;
        startAddr += (uint32)((canFDMsgRamConfig->configParams.rxFIFO0size + 1U) * MCAN_MSG_RAM_TX_RX_ELEM_SIZE * 4U);
        canFDMsgRamConfig->configParams.rxFIFO1startAddr = startAddr;
        startAddr += (uint32)(((uint32)canFDMsgRamConfig->configParams.rxFIFO1size + (uint32)1U) *
                              ((uint32)MCAN_MSG_RAM_TX_RX_ELEM_SIZE * (uint32)4U));
        canFDMsgRamConfig->configParams.rxBufStartAddr = startAddr;

        /* Configure Message RAM */
        (void)MCAN_msgRAMConfig(baseAddr, &canFDMsgRamConfig->configParams);

        /* Configure Standard ID filters */
        for (loopCnt = 0U; loopCnt < (uint32)canFDMsgRamConfig->stdFilterNum; loopCnt++)
        {
            MCAN_addStdMsgIDFilter(baseAddr, loopCnt, &canFDMsgRamConfig->stdMsgIDFilterList[loopCnt]);
        }
        /* Configure Extended ID filters */
        for (loopCnt = 0U; loopCnt < (uint32)canFDMsgRamConfig->extFilterNum; loopCnt++)
        {
            MCAN_addExtMsgIDFilter(baseAddr, loopCnt, &canFDMsgRamConfig->extMsgIDFilterList[loopCnt]);
        }
    }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    else
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_INIT_ID,
                              (uint8)CAN_E_PARAM_HANDLE);
    }
#endif
}

static void Can_mcanSetId(const Can_PduType *PduInfo, const Can_MailboxType *mailboxCfg, MCAN_TxBufElement *elem)
{
    uint32 id;
    uint32 idType = CAN_ID_STD;
    uint32 status = (uint32)E_OK;

    switch (mailboxCfg->MBIdType)
    {
        case CAN_ID_STD:
        {
            idType = CAN_ID_STD;
            break;
        }

        case CAN_ID_XTD:
        {
            idType = CAN_ID_XTD;
            break;
        }

        case CAN_ID_MIXED:
        {
            /*Mixed ID */
            if ((PduInfo->id & CAN_MSG_ID_TYPE_EXT) == (CAN_MSG_ID_TYPE_EXT))
            {
                idType = CAN_ID_XTD;
            }
            else
            {
                idType = CAN_ID_STD;
            }
            break;
        }

        default:
        {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_WRITE_ID,
                                  (uint8)CAN_E_PARAM_CONTROLLER);
#endif
            status = (uint32)E_NOT_OK;
            break;
        }
    }

    if (((uint32)E_OK) == status)
    {
        id        = Can_mcanGetID(idType, PduInfo->id);
        elem->xtd = idType;
        elem->id  = id;
    }
}

static inline uint32 Can_mcanGetID(const uint32 idType, const uint32 CanId)
{
    uint32 id;

    if (idType == CAN_ID_STD)
    {
        /* Standard ID*/
        id = (CanId & STD_MSGID_MASK) << STD_MSGID_SHIFT;
    }
    else
    {
        /* Extended ID*/
        id = CanId & XTD_MSGID_MASK;
    }
    return id;
}

void Can_mcanSetBaudrate(const Can_ControllerType_PC *canControllerCfg_PC, const Can_BaudConfigType *setBaud)
{
    MCAN_BitTimingParams configParams;
    uint8                tmpVal;
    sint32               status;
    uint32               timeQuanta;
    uint32               baseAddr;

    baseAddr                       = canControllerCfg_PC->CntrAddr;
    configParams.nomRatePrescalar  = ((uint32)setBaud->BrpValue);
    configParams.nomRatePrescalar -= 1U;

    /* Setup bit timing */
    tmpVal                         = (setBaud->Pseg1 + setBaud->PropSeg) - 1U;
    configParams.nomTimeSeg1       = (uint32)tmpVal;
    configParams.nomTimeSeg2       = (uint32)((uint32)setBaud->Pseg2 - 1U);
    configParams.nomSynchJumpWidth = (uint32)((uint32)setBaud->Sjw - 1U);
    tmpVal                         = (setBaud->BaudFdRateConfig.Pseg1 + setBaud->BaudFdRateConfig.PropSeg) - 1U;
    configParams.dataTimeSeg1      = (uint32)tmpVal;

    configParams.dataTimeSeg2       = (uint32)setBaud->BaudFdRateConfig.Pseg2 - 1U;
    configParams.dataSynchJumpWidth = (uint32)setBaud->BaudFdRateConfig.Sjw - 1U;
    configParams.dataRatePrescalar  = (uint32)setBaud->BaudFdRateConfig.BrpValue - 1U;
    configParams.brsEnable          = setBaud->BaudFdRateConfig.BrsSwitch;
    if (0U != setBaud->BaudFdRateConfig.TrcvCompDelay)
    {
        timeQuanta                  = (uint32)setBaud->BaudFdRateConfig.TrcvCompDelay;
        configParams.tdcEnable      = (uint32)MCAN_DBTP_TDC_ENABLE;
        configParams.tdcConfig.tdco = timeQuanta;
        configParams.tdcConfig.tdcf = (uint32)MCAN_TRCV_DELAY_COMP_WIN;
    }
    else
    {
        configParams.tdcEnable      = (uint32)MCAN_DBTP_TDC_DISABLE;
        configParams.tdcConfig.tdco = (uint32)setBaud->BaudFdRateConfig.TrcvCompDelay;
        configParams.tdcConfig.tdcf = (uint32)MCAN_TRCV_DELAY_COMP_WIN;
    }
    status = MCAN_setBitTime(baseAddr, &configParams);
    if (STW_SOK == status)
    {
        /* Bit timings config successful */
    }
    else
    {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETBAUDRATE_ID,
                              (uint8)CAN_E_PARAM_BAUDRATE);
#endif
    }
}

void Can_mcanDisableInterrupts(Can_ControllerObjType *controllerObj)
{
    uint8  InterruptCounter;
    uint32 baseAddr;

    InterruptCounter = controllerObj->canInterruptCounter;
    baseAddr         = controllerObj->canControllerConfig_PC.CntrAddr;
#if (STD_ON == CAN_ECC_ENABLE)
    /* Disable ECC Interrupt */
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_SEC, (uint32)FALSE);
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_DED, (uint32)FALSE);
#endif
    /* Disable Interrupt Sources as well as Interrupt Line */
    // MCAN_enableIntr(baseAddr, canInterruptMask, (uint32)FALSE);
    MCAN_enableIntrLine(baseAddr, (uint32)MCAN_INTR_LINE_NUM_0, (uint32)FALSE);
    controllerObj->canInterruptCounter = InterruptCounter + 1U;
}

void Can_mcanEnableInterrupts(Can_ControllerObjType *canController)
{
    uint8  InterruptCounter;
    uint32 baseAddr;

    InterruptCounter = canController->canInterruptCounter;
    baseAddr         = canController->canControllerConfig_PC.CntrAddr;
#if (STD_ON == CAN_ECC_ENABLE)
    /* Enable ECC Interrupt */
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_SEC, (uint32)TRUE);
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_DED, (uint32)TRUE);
#endif

    if (InterruptCounter != 0U)
    {
        canController->canInterruptCounter = InterruptCounter - 1U;
        InterruptCounter                   = canController->canInterruptCounter;
        if (InterruptCounter == 0U)
        {
            /* Enable Interrupt Sources as well as Interrupt Line */
            // MCAN_enableIntr(baseAddr, canInterruptMask, (uint32)TRUE);
            MCAN_enableIntrLine(baseAddr, (uint32)MCAN_INTR_LINE_NUM_0, (uint32)TRUE);

        } /*End of if (InterruptCounter == 0U)*/
    }
}

void Can_mcanProcessBusOff(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                           Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt)
{
    const Can_MailboxType *mailboxCfg;
    uint32                 htrh;
    uint32                 initStatus, baseAddr;
    MCAN_ProtocolStatus    protStatus = {0};

    baseAddr   = canController->canControllerConfig_PC.CntrAddr;
    initStatus = MCAN_getOpMode(baseAddr);
    MCAN_getProtocolStatus(baseAddr, &protStatus);
    if ((MCAN_PSR_BO_BUS_OFF == protStatus.busOffStatus) && (MCAN_CCCR_INIT_MODE_INIT == initStatus))
    {
        /* Check if recovery has already started */
        if (canController->canBusOffRecoveryStatus != (boolean)TRUE)
        {
            canController->canFDMsgRamConfig.txAddRequest = 0U;
            Can_mcanCancelPendMsg(baseAddr);
            /* Initialize Can_MailboxObjTxType params according to configured mailboxes */
            for (htrh = 0U; htrh < maxMbCnt; htrh++)
            {
                mailboxCfg = &canMailbox[htrh].mailBoxConfig;
                Can_MailboxInitialize(canController, canTxMessageObj, mailboxCfg);
            }
            /* BusOff Recovery sequence has not started */
            canController->canState = CAN_CS_STOPPED;
            /*Call the bus off indication function*/
            CanIf_ControllerBusOff(canController->canControllerConfig_PC.ControllerId);
        }
    }
}
static void Can_MailboxInitialize(Can_ControllerObjType *canController, Can_MailboxObjTxType *canTxMessageObj,
                                  const Can_MailboxType *mailboxCfg)
{
    if ((CAN_MAILBOX_DIRECTION_TX == mailboxCfg->MBDir) &&
        (mailboxCfg->Controller->ControllerId == canController->canControllerConfig_PC.ControllerId))
    {
        canTxMessageObj[mailboxCfg->HwHandle].freeHwObjectCount = mailboxCfg->CanHwObjectCount;
    }
}
void Can_mcan_ModeProcess(Can_ControllerObjType *canController)
{
    uint32                  baseAddr;
    Can_ControllerStateType controller_state;

    controller_state = canController->canState;
    baseAddr         = canController->canControllerConfig_PC.CntrAddr;
    switch (controller_state)
    {
        case CAN_CS_STARTED:
        {
            Can_CheckCsStarted(canController, baseAddr);
            CanIf_ControllerModeIndication((uint8)canController->canControllerConfig_PC.ControllerId,
                                           (Can_ControllerStateType)CAN_CS_STARTED);
            break;
        }

        case CAN_CS_STOPPED:
        {
            if ((uint32)MCAN_OPERATION_MODE_SW_INIT == MCAN_getOpMode(baseAddr))
            {
                CanIf_ControllerModeIndication(canController->canControllerConfig_PC.ControllerId, CAN_CS_STOPPED);
            }
            break;
        }

        case CAN_CS_SLEEP:
        {
            if (MCAN_CCCR_CSA_ACK == (MCAN_getClkStopAck(baseAddr) & (uint32)MCAN_CCCR_CSA_ACK))
            {
                CanIf_ControllerModeIndication(canController->canControllerConfig_PC.ControllerId, CAN_CS_SLEEP);
            }
            break;
        }

        default:
        {
            break;
        }
    } /*End of Switch*/
}

static void Can_CheckCsStarted(Can_ControllerObjType *canController, uint32 baseAddr)
{
    MCAN_ProtocolStatus protStatus = {0};

    /* If BusOff recovery sequence has started, check if CAN
     * controller is started. If Not
     * restart CAN controller */
    if (canController->canBusOffRecoveryStatus == (boolean)TRUE)
    {
        if (canController->canControllerConfig_PC.CntrActive == (boolean)TRUE)
        {
            /* Restart CAN controller */
            MCAN_setOpMode(baseAddr, (uint32)MCAN_OPERATION_MODE_NORMAL);
            MCAN_getProtocolStatus(baseAddr, &protStatus);
            if (MCAN_PSR_BO_BUS_OFF == protStatus.busOffStatus)
            {
                /* Busoff recovery has completed */
                canController->canBusOffRecoveryStatus = (boolean)FALSE;
            }
        }
    }
}

void Can_mcanReadRxBuff(Can_ControllerObjType *controllerObj, uint32 Interrupt_Mask)
{
    uint32                     canIdentifier = 0U, rxStatus = 0U, idx, Pos, baseAddr;
    uint16                     hrh    = 0U;
    boolean                    retVal = TRUE;
    uint8                      CanDataLength;
    uint8                      i;
    MCAN_RxNewDataStatus       newDataStatus = {0};
    MCAN_RxBufElement          elem          = {0};
    Can_FdMsgRAMConfigObjType *canFDMsgRamConfig;
    canFDMsgRamConfig = &controllerObj->canFDMsgRamConfig;

    baseAddr = controllerObj->canControllerConfig_PC.CntrAddr;
    MCAN_getNewDataStatus(baseAddr, &newDataStatus);
    /* Scan newData Register (32 bits x 2 Registers) and
     * read appropriate mailbox if any message is received */
    newDataStatus.statusLow  &= (canFDMsgRamConfig->rxLowInterruptMask ^ Interrupt_Mask);
    newDataStatus.statusHigh &= (canFDMsgRamConfig->rxHighInterruptMask ^ Interrupt_Mask);
    /* Two iterations are required for RX Lower 32 messages and RX Higher 32
            messages interrupts */
    for (i = 0; i < (uint8)2; i++)
    {
        if (i == 0U)
        {
            rxStatus = newDataStatus.statusLow;
            Pos      = 0U;
        }
        else
        {
            rxStatus = newDataStatus.statusHigh;
            Pos      = 32U;
        }
        while (rxStatus != CAN_ZERO)
        {
            idx        = GET_LOWER_INDEX(rxStatus);
            rxStatus  ^= (uint32)1 << idx;
            idx       += Pos;
            elem.data  = controllerObj->canSduPtr;
            MCAN_readMsgRam(baseAddr, MCAN_MEM_TYPE_BUF, idx, MCAN_RX_FIFO_NUM_0, &elem);

            CanDataLength = Can_McanDataSize[elem.data_length];
            if (1U == elem.xtd)
            {
                /* Received frame with Extended ID - set MSB to '1' */
                canIdentifier = (uint32)(elem.id | CAN_MSG_ID_TYPE_EXT);
                hrh           = canFDMsgRamConfig->extMbMapping[elem.fidx];
            }
            else
            {
                /* Received frame with Standard ID */
                canIdentifier = (uint32)((elem.id >> STD_MSGID_SHIFT) & STD_MSGID_MASK);
                hrh           = canFDMsgRamConfig->stdMbMapping[elem.fidx];
            }
            controllerObj->mailboxCfg.Hoh          = hrh;
            canIdentifier                          = (uint32)(canIdentifier | (elem.fdf << MSGID_FD_SHIFT));
            controllerObj->mailboxCfg.CanId        = canIdentifier;
            controllerObj->mailboxCfg.ControllerId = controllerObj->canControllerConfig_PC.ControllerId;

            /* Copy SDU data */
            controllerObj->pduInfo.SduDataPtr = controllerObj->canSduPtr;
            controllerObj->pduInfo.SduLength  = (uint16)CanDataLength;
#ifdef CAN_LPDU_CALLOUT
            retVal = CAN_LPDU_CALLOUT(hrh, canIdentifier, CanDataLength, controllerObj->canSduPtr);
#endif
            /* Call Receive indication */
            if (retVal == TRUE)
            {
                CanIf_RxIndication(&controllerObj->mailboxCfg, &controllerObj->pduInfo);
            }
        }
    }
    MCAN_clearNewDataStatus(baseAddr, &newDataStatus);
}

void Can_mcanReadRxFIFO(Can_ControllerObjType *controllerObj, MCAN_RxFIFONum fifoNum)
{
    uint32                     loopCnt, fillLvl, canIdentifier = 0U, baseAddr;
    uint8                      canDlc;
    boolean                    retVal = TRUE;
    Can_HwHandleType           hrh;
    MCAN_RxFIFOStatus          fifoStatus = {(MCAN_RxFIFONum)0};
    MCAN_RxBufElement          elem       = {0};
    Can_FdMsgRAMConfigObjType *canFDMsgRamConfig;
    canFDMsgRamConfig = &controllerObj->canFDMsgRamConfig;

    baseAddr       = controllerObj->canControllerConfig_PC.CntrAddr;
    fifoStatus.num = fifoNum;
    MCAN_getRxFIFOStatus(baseAddr, &fifoStatus);
    fillLvl = fifoStatus.fillLvl;
    for (loopCnt = 0U; loopCnt < fillLvl; loopCnt++)
    {
        MCAN_getRxFIFOStatus(baseAddr, &fifoStatus);

        /* Initiallise the elem's data field by the canSduPtr, now
           MCAN_readMsgRamNoCpy will directly write payload to canSduPtr */
        elem.data = controllerObj->canSduPtr;
        MCAN_readMsgRam(baseAddr, MCAN_MEM_TYPE_FIFO, fifoStatus.getIdx, fifoStatus.num, &elem);
        (void)MCAN_writeRxFIFOAck(baseAddr, fifoStatus.num, fifoStatus.getIdx);
        canDlc = Can_McanDataSize[elem.data_length];

        if (1U == elem.xtd)
        {
            /* Received frame with Extended ID - set MSB to '1' */
            canIdentifier = (uint32)(elem.id | CAN_MSG_ID_TYPE_EXT);
            hrh           = canFDMsgRamConfig->extMbMapping[elem.fidx];
        }
        else
        {
            /* Received frame with Standard ID */
            canIdentifier = (uint32)((elem.id >> STD_MSGID_SHIFT) & STD_MSGID_MASK);
            hrh           = canFDMsgRamConfig->stdMbMapping[elem.fidx];
        }
        if (1U == elem.fdf)
        {
            /* Received CAN-FD frame - set 30th bit to '1' */
            canIdentifier = (uint32)(canIdentifier | CAN_MSG_TYPE_CAN_FD);
        }

        /* Copy CanId, ControllerId */
        controllerObj->mailboxCfg.Hoh          = hrh;
        controllerObj->mailboxCfg.CanId        = canIdentifier;
        controllerObj->mailboxCfg.ControllerId = controllerObj->canControllerConfig_PC.ControllerId;

        /* Copy SDU data */
        controllerObj->pduInfo.SduDataPtr = controllerObj->canSduPtr;
        controllerObj->pduInfo.SduLength  = (uint16)canDlc;
#ifdef CAN_LPDU_CALLOUT
        retVal = CAN_LPDU_CALLOUT(hrh, canIdentifier, canDlc, controllerObj->canSduPtr);
#endif
        /* Call Receive indication */
        if (retVal == TRUE)
        {
            CanIf_RxIndication(&controllerObj->mailboxCfg, &controllerObj->pduInfo);
        }
    }
}

/*Requirements: SWS_Can_00273 */
void Can_mcanProcessISR(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                        Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt)
{
    uint32 intrStatus, baseAddr;
    uint8  ControllerId;

    ControllerId = canController->canControllerConfig_PC.ControllerId;
    baseAddr     = canController->canControllerConfig_PC.CntrAddr;
    intrStatus   = MCAN_getIntrStatus(baseAddr);

    if ((uint32)MCAN_INTR_SRC_BUS_OFF_STATUS == (intrStatus & (uint32)MCAN_INTR_SRC_BUS_OFF_STATUS))
    {
        Can_mcanProcessBusOff(canController, canMailbox, canTxMessageObj, maxMbCnt);
    }
    if ((uint32)MCAN_INTR_SRC_RX_FIFO0_MSG_LOST == (intrStatus & (uint32)MCAN_INTR_SRC_RX_FIFO0_MSG_LOST))
    {
        (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, (uint8)ControllerId, (uint8)CAN_RXPROCESS_ID_INTERRUPT,
                                     (uint8)CAN_E_DATALOST);
    }
    if ((uint32)MCAN_INTR_SRC_RX_FIFO1_MSG_LOST == (intrStatus & (uint32)MCAN_INTR_SRC_RX_FIFO1_MSG_LOST))
    {
        (void)Det_ReportRuntimeError((uint16)CAN_MODULE_ID, (uint8)ControllerId, (uint8)CAN_RXPROCESS_ID_POLLING,
                                     (uint8)CAN_E_DATALOST);
    }
    if ((uint32)MCAN_INTR_SRC_TRANS_COMPLETE == (intrStatus & (uint32)MCAN_INTR_SRC_TRANS_COMPLETE))
    {
        Can_mcanProcessTx(canController, canMailbox, canTxMessageObj, INTERRUPT_MASK);
    }
    if (((uint32)MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG == (intrStatus & (uint32)MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)))
    {
        /* Read Messages stored in  buffers */
        Can_mcanReadRxBuff(canController, INTERRUPT_MASK);
    }
    if ((uint32)MCAN_INTR_SRC_RX_FIFO0_NEW_MSG == (intrStatus & (uint32)MCAN_INTR_SRC_RX_FIFO0_NEW_MSG))
    {
        Can_mcanReadRxFIFO(canController, MCAN_RX_FIFO_NUM_0);
    }
    MCAN_clearIntrStatus(baseAddr, intrStatus);
}

void Can_mcanProcessTx(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                       Can_MailboxObjTxType *canTxMessageObj, uint32 Interrupt_Mask)
{
    uint32                     txStatus = 0U, idx, hth, baseAddr;
    const Can_MailboxType     *mailboxCfg;
    PduIdType                  CanTxPduId;
    Can_HwHandleType           HwHandle;
    Can_FdMsgRAMConfigObjType *canFDMsgRamConfig;
    canFDMsgRamConfig = &canController->canFDMsgRamConfig;

    baseAddr = canController->canControllerConfig_PC.CntrAddr;

    txStatus  = MCAN_getTxBufTransmissionStatus(baseAddr);
    txStatus &= ((canFDMsgRamConfig->txInterruptMask ^ Interrupt_Mask) & canFDMsgRamConfig->txAddRequest);
    /* Only 32 Tx Mailboxes are supported by hw */
    while (txStatus != CAN_ZERO)
    {
        idx                              = GET_LOWER_INDEX(txStatus);
        txStatus                        ^= (uint32)1 << idx;
        canFDMsgRamConfig->txAddRequest ^= (uint32)1 << idx;
        hth                              = canController->canFDMsgRamConfig.txMbMapping[idx];
        CanTxPduId                       = canController->canFDMsgRamConfig.txPduIdMapping[idx];
        mailboxCfg                       = &canMailbox[hth].mailBoxConfig;
        HwHandle                         = mailboxCfg->HwHandle;
        if (CAN_MAILBOX_DIRECTION_TX == mailboxCfg->MBDir)
        {
            canTxMessageObj[HwHandle].freeHwObjectCount++;
            /* clear for next transmission. */
            CanIf_TxConfirmation(CanTxPduId);
        }
    }
}

#if (STD_ON == CAN_ECC_ENABLE)
void Can_mcanProcessECCISR(const Can_ControllerObjType *controllerObj)
{
    Can_ErrNotifyType errorNotification = NULL;
    MCAN_ECCErrStatus mcanECCErr;
    uint32            baseAddr;
    uint32            errType = (uint32)CAN_ECC_ERROR_TYPE_SEC;

    baseAddr = controllerObj->canControllerConfig_PC.CntrAddr;
    MCAN_eccGetErrorStatus(baseAddr, &mcanECCErr);
    if (1U == mcanECCErr.secErr)
    {
        MCAN_eccClearErrorStatus(baseAddr, MCAN_ECC_ERR_TYPE_SEC);
        errType = (uint32)CAN_ECC_ERROR_TYPE_SEC;
    }
    if (1U == mcanECCErr.dedErr)
    {
        MCAN_eccClearErrorStatus(baseAddr, MCAN_ECC_ERR_TYPE_DED);
        errType = (uint32)CAN_ECC_ERROR_TYPE_DED;
    }
    errorNotification = controllerObj->canControllerConfig_PC.Can_ErrorNotification;

    if (errorNotification != NULL_PTR)
    {
        errorNotification(errType);
    }
    MCAN_eccWriteEOI(baseAddr, MCAN_ECC_ERR_TYPE_SEC);
    MCAN_eccWriteEOI(baseAddr, MCAN_ECC_ERR_TYPE_DED);
}
#endif

#if (CAN_DEINIT_API == STD_ON)
void Can_mcanHwDeInit(const Can_ControllerObjType *canController)
{
    uint32 baseAddr;

    baseAddr = canController->canControllerConfig_PC.CntrAddr;
#if (STD_ON == CAN_ECC_ENABLE)
    /* Disable ECC Interrupt */
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_SEC, (uint32)FALSE);
    MCAN_eccEnableIntr(baseAddr, MCAN_ECC_ERR_TYPE_DED, (uint32)FALSE);
    /* Clear Interrupt status */
    MCAN_eccClearErrorStatus(baseAddr, MCAN_ECC_ERR_TYPE_SEC);
    MCAN_eccClearErrorStatus(baseAddr, MCAN_ECC_ERR_TYPE_DED);
#endif
    /* Disable Interrupt Sources as well as Interrupt Line */
    MCAN_enableIntr(baseAddr, MCAN_INTR_MASK, (uint32)FALSE);
    MCAN_enableIntrLine(baseAddr, (uint32)MCAN_INTR_LINE_NUM_0, (uint32)FALSE);
    /* Clear Interrupt status */
    MCAN_clearIntrStatus(baseAddr, (uint32)MCAN_INTR_MASK_ALL);
}
#endif

#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"
