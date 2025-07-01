/*
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *  \file     Eth_Priv.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the Ethernet driver files.
 */

#ifndef ETH_PRIV_H_
#define ETH_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Eth_GeneralTypes.h"
#include "Cpsw_Priv.h"
#include "Os.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* Default TX CPDMA Channel used for reception */
#define ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM (0U)

/**
 * Default TX CPDMA Channel used for transmission
 * Note: Rate limiting can be only enabled starting with highest priority
 *       channels; in this driver we support only single channel hence we use
 *       channel 7 as default to support rate limiting
 */
#define ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM (7U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

extern volatile uint8 Eth_ControllerModeChangeFlag;

extern Eth_DrvObject Eth_DrvObj;

extern volatile VAR(Eth_StateType, ETH_VAR_ZERO_INIT) Eth_DrvStatus;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  Initialize the Ethernet Driver.
 *
 * \param  CfgPtr Pointer to driver configuration
 *
 * \return None
 */
void Eth_initHw(const Eth_ConfigType *CfgPtr);

/**
 * \brief  Enable/disable the indexed controller.
 *
 * \param  CtrlIdx        Index of Eth controller
 * \param  CtrlMode       Controller mode
 *
 * \retval E_OK           Success
 * \retval E_NOT_OK       Failure
 */
Std_ReturnType Eth_setHwControllerMode(uint8 CtrlIdx, Eth_ModeType CtrlMode);

/**
 * \brief  Set the physical source address used by the indexed controller.
 *
 * \param  CtrlIdx        Index of Eth controller
 * \param  PhysAddrPtr    Pointer to physical source address
 *
 * \return None
 */
void Eth_setHwPhysAddr(P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

/**
 * \brief  Add/remove physical source address to/from the indexed controller filter.
 *
 * \param  PhysAddrPtr    Pointer to physical filter address
 * \param  Action         ETH_ADD_TO_FILTER or ETH_REMOVE_FROM_FILTER
 *
 * \retval E_OK           Success
 * \retval E_NOT_OK       Failure
 */
Std_ReturnType Eth_HwUpdatePhysAddrFilter(P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr,
                                          Eth_FilterActionType Action);

/**
 * \brief  Provides access to a transmit buffer of the specified controller
 *
 * \param  BufIdxPtr      Pointer to index of granted TX buffer
 * \param  BufPtr         Pointer to data buffer of granted TX buffer
 * \param  LenBytePtr     Input desired buffer length and return granted buffer length
 *
 * \retval BUFREQ_OK       Success
 * \retval BUFREQ_E_NOT_OK Development error detected
 * \retval BUFREQ_E_BUSY   All buffers in use
 * \retval BUFREQ_E_OVFL   Requested buffer too large
 */
BufReq_ReturnType Eth_provideHwTxBuffer(P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr,
                                        P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) * BufPtr,
                                        P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr);

/**
 * \brief  Triggers transmission of a previously filled transmit buffer.
 *
 * \param  BufIdx          Index of the buffer resource
 * \param  FrameType       Ethernet frame type
 * \param  TxConfirmation  Flag to activate transmission confirmation
 * \param  LenByte         Data length in byte
 * \param  PhysAddrPtr     Physical target address (MAC address) in network byte order
 *
 * \retval E_OK           Success
 * \retval E_NOT_OK       Failure
 */
Std_ReturnType Eth_transmitHw(VAR(Eth_BufIdxType, AUTOMATIC) BufIdx, VAR(Eth_FrameType, AUTOMATIC) FrameType,
                              VAR(boolean, AUTOMATIC) TxConfirmation, VAR(uint16, AUTOMATIC) LenByte,
                              P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

/**
 * \brief Receive a frame from the related fifo
 *
 * \param  RxStatusPtr  Indicates whether a frame has been received
 *                      and if so, whether more frames are available
 *
 * \return None
 */
void Eth_receiveHw(P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr);

/**
 * \brief  Reads a list with drop counter values of the corresponding controller.
 *
 * \param  CounterPtr  Pointer to counter values list
 *
 * \return None
 */
void Eth_getHwCounterValues(P2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) CounterPtr);

/**
 * \brief  Return the list of RX statistics according to IETF RFC2819
 *
 *         List parameters defined in Eth_RxStatsType, maximal possible value
 *         shall denote an invalid value.
 *
 * \param  RxStats    Pointer to statistics values list
 *
 * \return None
 */
void Eth_getHwRxStats(P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats);

/**
 * \brief  Return the list of Transmission Statistics out of IETF RFC1213.
 *
 *         List parameters defined in Eth_TxStatsType, maximal possible value
 *         shall denote an invalid value.
 *
 * \param TxStats    Pointer to statistics values list
 *
 * \return None
 */
void Eth_getHwTxStats(P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats);

/**
 * \brief  Return the list of Transmission Error Counters out of IETF RFC1213 and RFC1643
 *
 *         List parameters defined in Eth_TxErrorCounterValuesType, maximal possible value
 *         shall denote an invalid value.
 *
 * \param  TxErrorCounterValues     Pointer to error counter values list
 *
 * \return None
 */
void Eth_HwGetTxErrorCounterValues(P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues);

/**
 * \brief  Get egress time stamp on a dedicated message object.
 *
 * \param  BufIdx       Index of the Eth buffer, where Application
 *                      expects egress time stamping
 * \param  timeQualPtr  Quality of HW time stamp
 * \param  timeStampPtr Pointer to output time stamp
 *
 * \return None
 */
void Eth_getHwEgressTimeStamp(VAR(Eth_BufIdxType, AUTOMATIC) BufIdx,
                              P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                              P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);

/**
 * \brief  Get ingress time stamp on a dedicated message object.
 *
 * \param  DataPtr        Pointer to the message buffer, where Application
 *                        expects ingress time stamping
 *
 * \param  timeQualPtr    Quality of HW time stamp
 * \param  timeStampPtr   Pointer to output time stamp
 *
 * \return None
 */
void Eth_getHwIngressTimeStamp(P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
                               P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                               P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);

/**
 * \brief  Check access to controller and report production error.
 *
 * \retval E_OK        No access error
 * \retval E_NOT_OK    Access error detected
 */
Std_ReturnType Eth_cpswCheckHostErr(void);

/**
 * \brief  Check for controller errors and report production error.
 *
 * \return None
 */
void Eth_checkHwCtrlErrors(void);

/**
 * \brief  Process receive packets buffer descriptors for all received packets.
 *
 * \param  ctrlIdx   The instance of CPSW interface.
 * \param  chNum     Channel number.
 *
 * \return None
 */
void Eth_processRxBuffDesc(uint8 ctrlIdx, uint32 chNum);

/**
 * \brief Process transmit packet buffer descriptor.
 *
 * \param ctrlIdx   The instance of transmit packet buffer descriptor to process
 * \param chNum     Channel number.
 *
 * \return None
 */
void Eth_processTxBuffDesc(uint8 ctrlIdx, uint32 chNum);

/**
 * \brief Process transmit teardown command.
 *
 * \param chNum     Channel number.
 *
 * \return None
 */
void Eth_processTxTearDown(uint32 chNum);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef ETH_PRIV_H_ */
