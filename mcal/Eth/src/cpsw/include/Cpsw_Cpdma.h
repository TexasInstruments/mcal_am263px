/*
 *
 * Copyright (c) 2024-2025 Texas Instruments Incorporated
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
 *  \file       Cpsw_Cpdma.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              contains some abstraction layer for CPDMA module of CPSW
 *              subsystem.
 */

#ifndef CPSW_CPDMA_H_
#define CPSW_CPDMA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

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
 * \brief   This API resets the CPDMA module.
 *
 * \param   baseAddr Base address of the CPDMA.
 */
void CpswCpdma_reset(uint32 baseAddr);

/**
 * \brief   This API enables the CPDMA Statistics interrupt.
 *
 * \param   baseAddr     Base address of the CPSW.
 */
void CpswCpdma_enableStatIntr(uint32 baseAddr);

/**
 * \brief   This API enables the CPDMA Host Error interrupt.
 *
 * \param   baseAddr     Base address of the CPSW.
 */
void CpswCpdma_enableHostErrIntr(uint32 baseAddr);

/**
 * \brief   This API disables the CPDMA Statistics interrupt.
 *
 * \param   baseAddr     Base address of the CPSW.
 */
void CpswCpdma_disableStatIntr(uint32 baseAddr);

/**
 * \brief   This API enables the transfer interrupt for given channel.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   chIntr       Interrupt configuration mask of DMA interrupt takes
 *                       values #Eth_CpswChIntr.
 */
void CpswCpdma_enableChIntr(uint32 baseAddr, uint32 chNum, Eth_CpswChIntr chIntr);

/**
 * \brief   This API disables the transfer interrupt for given channel.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   chIntr       Interrupt configuration mask of DMA interrupt takes
 *                       values #Eth_CpswChIntr.
 */
void CpswCpdma_disableChIntr(uint32 baseAddr, uint32 chNum, Eth_CpswChIntr chIntr);
/**
 * \brief   This API writes the interrupt line number to End Of Interrupt
 *          Vector.
 *
 * \param   baseAddr      Base Address of the CPDMA module registers.
 * \param   intrLine      Type of interrupt to acknowledge to the CPDMA from
 *                        interrupt lines #Eth_CpswWrIntrLine.
 */
void CpswCpdma_writeEoiVector(uint32 baseAddr, Eth_CpswWrIntrLine intrLine);

/**
 * \brief   This API enables TX transfer.
 *
 * Enables TX transfers, any write to hardware descriptor of a channel will
 * start transfer.
 *
 * \param   baseAddr Base Address of the CPSW.
 */
void CpswCpdma_enableTxCh(uint32 baseAddr);

/**
 * \brief   This API disables TX transfer.
 *
 * \param   baseAddr Base Address of the CPSW.
 */
void CpswCpdma_disableTxCh(uint32 baseAddr);

/**
 * \brief   Tear-down TX channel.
 *
 * This API will teardown CPDMA TX channel. CPDMA teardown is used for
 * gracefully shutting down CPDMA channel transfers. When a teardown
 * command is issued to an enabled receive channel the following will
 * occur
 *
 * 1. Any current frame in reception will complete normally.
 * 2. The teardown_complete bit will be set in the next buffer descriptor
 *    in the chain (if there is one).
 * 3. The channel head descriptor pointer will be cleared to 0.
 * 4. A receive interrupt for the channel will be issued to the host.
 *
 * \param   baseAddr      Base Address of the CPSW.
 * \param   chNum         Channel number to be torn.
 */
void CpswCpdma_teardownTxCh(uint32 baseAddr, uint32 chNum);

/**
 * \brief   Write TX Head Descriptor Pointer.
 *
 * Writes TX HDP register. If transfer is enabled, write to the transfer
 * HDP will immediately start transfer.
 * The data will be taken from the buffer pointer of the transfer buffer
 * descriptor written to the transfer HDP.
 *
 * \param   baseAddr Base Address of the CPSW.
 * \param   descHdr  Global address of the transfer buffer descriptor.
 * \param   chNum    Channel Number.
 */
void CpswCpdma_writeTxChHdp(uint32 baseAddr, uint32 descHdr, uint32 chNum);

/**
 * \brief   Write TX Completion Pointer.
 *
 * Writes TX CP register for a specific channel.
 *
 * \param   baseAddr Base Address of the CPSW.
 * \param   chNum    Channel Number.
 * \param   comPtr   Completion Pointer Value to be written.
 */
void CpswCpdma_writeTxChCp(uint32 baseAddr, uint32 chNum, uint32 comPtr);

/**
 * \brief   This API returns value of completion pointer for Tx CPDMA channel.
 *
 * \param   baseAddr       Base address of the CPSW.
 * \param   chNum          Channel number.
 * \param   regValPtr      Poiter to store value of register.
 *
 * \retval  Completion pointer value.
 */
uint32 CpswCpdma_readTxChCp(uint32 baseAddr, uint32 chNum);

/**
 * \brief   This API enables RX transfer.
 *
 * Enables RX transfers, any write to hardware descriptor of a channel will
 * start transfer.
 *
 * \param   baseAddr Base Address of the CPSW.
 */
void CpswCpdma_enableRxCh(uint32 baseAddr);

/**
 * \brief   This API disables RX transfer.
 *
 * \param   baseAddr Base Address of the CPSW.
 */
void CpswCpdma_disableRxCh(uint32 baseAddr);

/**
 * \brief   Tear-down RX channel.
 *
 * This API will teardown CPDMA RX channel. CPDMA teardown is used for
 * gracefully shutting down CPDMA channel transfers. When a teardown
 * command is issued to an enabled receive channel the following will
 * occur
 *
 * 1. Any current frame in reception will complete normally.
 * 2. The teardown_complete bit will be set in the next buffer descriptor
 *    in the chain (if there is one).
 * 3. The channel head descriptor pointer will be cleared to 0.
 * 4. A receive interrupt for the channel will be issued to the host.
 *
 * \param   baseAddr      Base Address of the CPSW.
 * \param   chNum         Channel number to be torn.
 */
void CpswCpdma_teardownRxCh(uint32 baseAddr, uint32 chNum);

/**
 * \brief   Write RX Head Descriptor Pointer.
 *
 * Writes RX HDP register. If transfer is enabled, write to the transfer
 * HDP will immediately start transfer.
 * The data will be taken from the buffer pointer of the transfer buffer
 * descriptor written to the transfer HDP.
 *
 * \param   baseAddr Base Address of the CPSW.
 * \param   descHdr  Global address of the transfer buffer descriptor.
 * \param   chNum    Channel Number.
 */
void CpswCpdma_writeRxChHdp(uint32 baseAddr, uint32 descHdr, uint32 chNum);

/**
 * \brief   Write RX Completion Pointer.
 *
 * Writes RX CP register for a specific channel.
 *
 * \param   baseAddr Base Address of the CPSW.
 * \param   chNum    Channel Number.
 * \param   comPtr   Completion Pointer Value to be written.
 */
void CpswCpdma_writeRxChCp(uint32 baseAddr, uint32 chNum, uint32 comPtr);

/**
 * \brief   Read RX Completion Pointer.
 *
 * Read RX CP register for a specific channel.
 *
 * \param   baseAddr       Base address of the CPSW.
 * \param   chNum          Channel number.
 *
 * \retval  Completion pointer value.
 */
uint32 CpswCpdma_readRxChCp(uint32 baseAddr, uint32 chNum);

/**
 * \brief   This API sets the free buffers for a specific channel.
 *
 * \param   baseAddr   Base Address of the CPSW.
 * \param   chNum      Channel Number.
 * \param   numFreeBuf Number of free buffers.
 */
void CpswCpdma_setRxChFreeBufCnt(uint32 baseAddr, uint32 chNum, uint32 numFreeBuf);

/**
 * \brief   This API sets threshold value for issuing receive threshold
 *           pending interrupts.
 *
 * \param   baseAddr   Base Address of the CPSW.
 * \param   chNum      Channel Number.
 * \param   thresh     RX threshold value.
 */
void CpswCpdma_setRxChThresh(uint32 baseAddr, uint32 chNum, uint32 thresh);

/* ========================================================================== */
/*                        Deprecated Function Declarations                    */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CPSW_ALE_H_ */
