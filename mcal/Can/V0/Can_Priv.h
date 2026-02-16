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
 *  \file     Can_Priv.h
 *
 *  \brief    This file contains cover page for generating doxygen
 *            API documentation.
 */

/* Protection against multiple inclusion */
#ifndef CAN_PRIV_H_
#define CAN_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Can.h"
#include "CanIf_Cbk.h"

#include "Std_Types.h"

/*  Other Header Files */
#include "Can.h"
#include "Det.h"
#include "mcan.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CAN_FD_PAYLOAD_MAX_BYTES (64U)

#define CAN_MAX_CONTROLLER_SUPPORTED (4U)

#define POLLING_MASK   (0xFFFFFFFFU)
#define INTERRUPT_MASK (0U)

#define FIFTH(n)  ((((n | 0x0000FFFFU) + (0x01U)) >> 27) & 0x00000010U)
#define FOURTH(n) ((((n | 0x00FF00FFU) + (0x01U)) >> 28) & 0x00000008U)
#define THIRD(n)  ((((n | 0x0F0F0F0FU) + (0x01U)) >> 29) & 0x00000004U)
#define SECOND(n) ((((n | 0x33333333U) + (0x01U)) >> 30) & 0x00000002U)
#define FIRST(n)  ((((n | 0X55555555U) + (0x01U)) >> 31) & 0x00000001U)

#define GET_LOWER_INDEX(n) Lower_Index(((~n) | ((n) - (0x01U))))
#define Lower_Index(n)     (FIFTH(n) | FOURTH(n) | THIRD(n) | SECOND(n) | FIRST(n))

#define ONES(m, n) ((((uint32)1 << m) - (uint32)1) ^ (((uint32)1 << n) - (uint32)1))
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief Can FD controller Message RAM Configuration object structure.
 *        This structure will only be used in CAN FD controller i.e. MCAN
 */
typedef struct Can_FdMsgRAMConfigObjType_s
{
    MCAN_MsgRAMConfigParams    configParams;
    /*!< MCAN Message RAM Configuration parameters */
    MCAN_StdMsgIDFilterElement stdMsgIDFilterList[MCAN_STD_FILTER_MAX_NUM];
    /*!< Standard ID filter elements */
    MCAN_ExtMsgIDFilterElement extMsgIDFilterList[MCAN_EXT_FILTER_MAX_NUM];
    /*!< Extended ID filter elements */
    uint8                      stdFilterNum;
    /*!< Standard ID filter element number */
    uint8                      extFilterNum;
    /*!< Extended ID filter element number */
    Can_HwHandleType           txMbMapping[MCAN_TX_BUFFER_MAX_NUM];
    /*!< Mapping of HTH - HOH */
    Can_HwHandleType           txPduIdMapping[MCAN_TX_BUFFER_MAX_NUM];
    /*!< Mapping of HTH - PDUID */
    Can_HwHandleType           stdMbMapping[MCAN_STD_FILTER_MAX_NUM];
    /*!< Mapping of Standard Filter to HOH */
    Can_HwHandleType           extMbMapping[MCAN_EXT_FILTER_MAX_NUM];
    /*!< Mapping of Extended Filter to HOH */
    uint32                     txAddRequest;
    /*!< 0 - Correspoiding bit, Buffer is free
             1 - Correspoiding bit, Buffer is pending*/
    uint32                     txInterruptMask;
    /*!< 0 - Correspoiding bit, Buffer is in Polling Mode
             1 - Correspoiding bit, Buffer is in Interrupt Mode*/
    uint32                     rxLowInterruptMask;
    /*!< 0 - Correspoiding bit, Buffer is in Polling Mode
             1 - Correspoiding bit, Buffer is in Interrupt Mode*/
    uint32                     rxHighInterruptMask;
    /*!< 0 - Correspoiding bit, Buffer is in Polling Mode
             1 - Correspoiding bit, Buffer is in Interrupt Mode*/
    uint16                     txBuffNum;
    /*!< Tx number of Buffer elements */
    uint16                     txFIFONum;
    /*!< Tx number of FIFO elements */
    uint16                     rxBuffNum;
    /*!< Rx number of Buffer elements */
    uint16                     rxFIFO0Num;
    /*!< Rx number of FIFO0 elements */
    uint16                     rxFIFO1Num;
    /*!< Rx number of FIFO1 elements */
} Can_FdMsgRAMConfigObjType;

/**
 * \brief Can controller object strucuture.
 */
typedef struct Can_ControllerObjType_s
{
    boolean canBusOffRecoveryStatus;
    /*!< Bus off recovery status */

    uint8                     canInterruptCounter;
    /*!< Total number of interrupts for this controller */
    uint32                    canInterruptMask;
    /*!< Interrupt Masking for the controller */
    uint16                    canBaud;
    /*!< Set BRP value */
    uint8                     canSduPtr[CAN_FD_PAYLOAD_MAX_BYTES];
    /*!< SDU pointer */
    Can_ControllerType        canControllerConfig;
    /**< Can Controller */
    Can_ControllerType_PC     canControllerConfig_PC;
    /**< Can Controller Pre-Compile Configuration */
    uint32                    maxBaudConfigID;
    /**< Max Baud Config Index in BaudRateConfigList */
    Can_ControllerStateType   canState;
    /**< State of Can */
    Can_HwType                mailboxCfg;
    /**< Structure which includes HOH, CAN Controller ID and specific CanId */
    PduInfoType               pduInfo;
    /**< Structure which includes pointer to the SDU and it's length */
    Can_FdMsgRAMConfigObjType canFDMsgRamConfig;
    /*!< MCAN Message RAM configuration parameters */

} Can_ControllerObjType;

/**
 * \brief Can HWObject to Mailbox mapping type
 */
typedef uint32 Can_MbHTRHMapping_Type;

/**
 * \brief Can Mailbox TX type strucuture.
 */
typedef struct Can_MailboxObjTxType_s
{
    uint16 freeHwObjectCount;
    /**< Mailbox Config Info */
    uint8  lowerBuffIdx;
    /**< Lower Buffer Idx */
    uint8  higherBuffIdx;
    /**< Higher Buffer Idx */
} Can_MailboxObjTxType;

/**
 * \brief Can Mailbox type strucuture.
 */
typedef struct Can_MailboxObjType_s
{
    Can_MailboxType    mailBoxConfig;
    /**< Mailbox Config Info */
    Can_MailboxType_PC mailBoxConfig_PC;
    /**< Mailbox Config Info Pre-Compile Configuration */
} Can_MailboxObjType;

/**
 * \brief Can Driver object type strucuture.
 */
typedef struct Can_DriverObjType_s
{
    Can_ControllerObjType canController[CAN_NUM_CONTROLLER];
    /**< List of enabled Controllers */
    Can_MailboxObjType    canMailbox[CAN_NUM_MAILBOXES];
    /**< MB array for all controllers */
    uint8                 canMaxControllerCount;
    /**< MaxCount of Controller in Controller List */
    uint32                maxMbCnt;
    /**< MaxMbCount in MB list in all controller */
    uint32                controllerIDMap[CAN_MAX_CONTROLLER];
    /**< CAN Controller ID mapping */
    Can_MailboxObjTxType  canTxMessageObj[CAN_NUM_TX_MAILBOXES];
    /**< Can Mailbox TX type array of Number of TX Mailboxes. */
} Can_DriverObjType;

extern uint8 Can_DrvState;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

FUNC(void, CAN_CODE)
Can_hwUnitConfig(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                 Can_MailboxObjTxType *canTxMessageObj, uint32 MaxMbCnt);

Std_ReturnType Can_hwUnitStart(Can_ControllerObjType *controllerObj);

Std_ReturnType Can_hwUnitStop(Can_ControllerObjType *controllerObj, Can_MailboxObjType *canMailbox,
                              Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt);

Std_ReturnType Can_hwUnitSleep(Can_ControllerObjType *controllerObj);
void           Can_mcanWkUp(Can_ControllerObjType *controllerObj);

Std_ReturnType Can_writeTxMailbox(const Can_MailboxType *mailboxCfg, Can_ControllerObjType *controllerObj,
                                  uint32 messageBox, const Can_PduType *PduInfo);

void Can_hwUnitDisableInterrupts(Can_ControllerObjType *controllerObj);

void Can_hwUnitEnableInterrupts(Can_ControllerObjType *controllerObj);

#if (CAN_DEINIT_API == STD_ON)
void Can_hwDeInit(const Can_ControllerObjType *canController);
#endif

void Can_hwUnitTxDonePolling(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox, uint8 htrh);

void Can_MainFunction_BusOffProcess(Can_ControllerObjType *controllerObj, Can_MailboxObjType *canMailbox,
                                    Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt);

void Can_MainFunction_ModeProcess(Can_ControllerObjType *canController);

Std_ReturnType Can_hwUnitTestLoopBackModeEnable(uint32 baseAddr, uint8 mode);

Std_ReturnType Can_hwUnitTestLoopBackModeDisable(uint32 baseAddr, uint8 mode);

/* MCAN related functions */
Std_ReturnType Can_mcanStart(Can_ControllerObjType *controllerObj);

Std_ReturnType Can_mcanStop(Can_ControllerObjType *controllerObj, Can_MailboxObjType *canMailbox,
                            Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt);

Std_ReturnType Can_mcanSleep(Can_ControllerObjType *controllerObj);

Std_ReturnType Can_mcanTestLoopBackModeEnable(uint32 baseAddr, uint8 mode);

Std_ReturnType Can_mcanTestLoopBackModeDisable(uint32 baseAddr, uint8 mode);

void Can_mcanCancelledMessagesReset(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                                    Can_MailboxObjTxType *canTxMessageObj);

uint32 Can_writeGetFreeMsgObj(Can_ControllerObjType *canController, Can_MailboxObjTxType *canTxMessageObj);

Std_ReturnType Can_mcanWriteTxMailbox(const Can_MailboxType *mailboxCfg, Can_ControllerObjType *controllerObj,
                                      uint32 messageBox, const Can_PduType *pduInfo);

void Can_mcanSetBaudrate(const Can_ControllerType_PC *canControllerCfg_PC, const Can_BaudConfigType *setBaud);

void Can_mcanDisableInterrupts(Can_ControllerObjType *controllerObj);

void Can_mcanEnableInterrupts(Can_ControllerObjType *canController);

void Can_mcanProcessBusOff(Can_ControllerObjType *controllerObj, const Can_MailboxObjType *canMailbox,
                           Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt);

void Can_mcan_ModeProcess(Can_ControllerObjType *canController);

void Can_mcanReadRxBuff(Can_ControllerObjType *controllerObj, uint32 Interrupt_Mask);

void Can_mcanReadRxFIFO(Can_ControllerObjType *controllerObj, MCAN_RxFIFONum fifoNum);

void Can_mcanProcessISR(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                        Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt);

#if (STD_ON == CAN_ECC_ENABLE)
void Can_mcanProcessECCISR(const Can_ControllerObjType *controllerObj);
#endif

void Can_mcanProcessTx(Can_ControllerObjType *canController, const Can_MailboxObjType *canMailbox,
                       Can_MailboxObjTxType *canTxMessageObj, uint32 Interrupt_Mask);

void Can_mcanProcessISRRx(Can_ControllerObjType *controllerObj, const Can_MailboxObjType *canMailbox, uint32 maxMbCnt);

#if (CAN_DEINIT_API == STD_ON)
void Can_mcanHwDeInit(const Can_ControllerObjType *canController);
#endif

#if (STD_ON == CAN_REGISTER_READBACK_API)
Std_ReturnType Can_HWRegisterReadback(Can_RegisterReadbackType *RegRbPtr, uint32 baseAddr);
#endif

Can_ErrorStateType Can_mcanGetProtocolStatus(const Can_ControllerObjType *canController);

#ifdef __cplusplus
}
#endif

#endif /* CAN_PRIV_ */

/*  End of File: Can_Priv.h */
