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
 *  \file     Cpsw.h
 *
 *  \brief    This file contains the function prototypes for the device
 *            abstraction layer for CPSW subsystem. It also contains some
 *            related macro definitions and some files to be included.
 *
 *  \details  Please find the below detailed description of cpsw dal.
 */

#ifndef CPSW_H_
#define CPSW_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cpsw_Priv.h"
#include "Hw_Cpsw_Ss.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Set the MacCtrl registers.
 *
 * \param   baseAddr    Base address of the CPSW.
 * \param   regVal      Register value to be written.
 *
 * \return  None
 */
void Cpsw_setMacCtrl(uint32 baseAddr, uint8 slavePortNum, uint32 regVal);

/**
 * \brief   Set the Rx Maximum length.
 *
 * \param   baseAddr    Base address of the CPSW.
 * \param   rxMaxLen    Rx Maximum length.
 *
 * \return  None
 */
void Cpsw_setRxMaxLen(uint32 baseAddr, uint8 slavePortNum, uint32 rxMaxLen);

/**
 * \brief   Reset the CPSW
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   slavePortNum Slave MAC port number.
 *
 * \return  None
 */
void Cpsw_resetEnet(uint32 baseAddr, uint8 slavePortNum);

/**
 * \brief   Get MAC control register of the MAC port.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   slavePortNum Slave MAC port number.
 *
 * \retval  value of MAC control register.
 */
uint32 Cpsw_getMacCtrl(uint32 baseAddr, uint8 slavePortNum);

/**
 * \brief   Enables RX, TX or RX threshold interrupts of a channel.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   chNum        Channel number to be enabled.
 * \param   chIntr       Interrupts to be enabled on the given channel of core.
 *
 * \return  None
 */
void Cpsw_enableChIntr(uint32 baseAddr, uint32 chNum, Eth_CpswChIntr chIntr);

/**
 * \brief   Set the prescale value for WR.
 *
 * \details WR prescale is used for interrupt pacing.
 *          Prescale value is number of MAIN_CLK R 0x0
 *          periods in 4us.
 *
 * \param   baseAddr     Base Address of the CPSW.
 * \param   preScalarVal The prescale value.
 *
 * \return  None
 */
void Cpsw_setPrescale(uint32 baseAddr, uint32 preScalarVal);

/**
 * \brief   Enable interrupt pacing for receive/transmit channel.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   intrType     Interrupt type.
 * \param   paceVal      Maximum number of interrupts per millisecond.
 *
 * \return  None
 */
void Cpsw_enableIntrPacing(uint32 baseAddr, Eth_CpswWrInt intrType, uint32 paceVal);

/**
 * \brief   Enable miscellaneous interrupts.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   miscIntrMask Interrupts to be enabled.
 *
 * \return  None
 */
void Cpsw_enableMiscIntr(uint32 baseAddr, uint32 miscIntrMask);

/**
 * \brief   Get status of given interrupt type.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   chIntr       Channel interrupt line takes values Eth_CpswChIntr.
 *
 * \return  Interrupt status of given type.
 */
uint32 Cpsw_getChIntrStatus(uint32 baseAddr, Eth_CpswChIntr chIntr);

/**
 * \brief   Get status of given miscellaneous interrupt.
 *
 * \param   baseAddr     Base address of the CPSW.
 *
 * \return  Status of all miscellaneous interrupts.
 */
uint32 Cpsw_getMiscIntrStatus(uint32 baseAddr);

/**
 * \brief   Set MAC address of given slave MAC port.
 *
 * \param   baseAddr     Base address of the CPSW Port Module registers
 * \param   slavePortNum Slave MAC port number.
 * \param   macAddr      The 6 byte MAC address.
 *
 * \return  None
 */
void Cpsw_setPortSrcAddr(uint32 baseAddr, uint8 slavePortNum, const uint8 macAddr[6]);

/**
 * \brief   Get MAC address of given slave MAC port.
 *
 * \param   baseAddr     Base address of the CPSW Port Module registers
 * \param   slavePortNum Slave MAC port number.
 * \param   macAddr      Pointer to  6 byte MAC address.
 *
 * \retval  E_OK         If address is valid
 * \retval  E_NOT_OK     Address not valid
 */
Std_ReturnType Cpsw_getPortSrcAddr(uint32 baseAddr, uint32 slavePortNum, uint8 macAddr[6]);

/**
 * \brief   Check the access to the CPSW host.
 *
 * \param   baseAddr    Base Address of the CPSW.
 *
 * \retval  TRUE        Host access error detected.
 * \retval  FALSE       No host access error.
 */
uint32 Cpsw_checkHostErr(uint32 baseAddr);

/**
 * \brief   Disable miscellaneous interrupts.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   miscIntrMask Interrupts to be disabled.
 *
 * \return  None
 */
void Cpsw_disableMiscIntr(uint32 baseAddr, uint32 miscIntrMask);
#ifdef __cplusplus
}
#endif

#endif /* #ifndef CPSW_H_ */
