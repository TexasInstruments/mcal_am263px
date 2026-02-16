/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2024 Texas Instruments Incorporated
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

#ifndef IPC_RPMSG_PRIV_H_
#define IPC_RPMSG_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "string.h"
#include "Cdd_Ipc.h"
#include "ipc_rpmsg_lld.h"

/**
 * \brief Parameters for VRING reset operation
 *
 * This structure groups the offset parameters needed for VRING reset
 */
typedef struct
{
    uint16    numBuf;        /**< Number of buffers in VRING */
    uint16    msgSize;       /**< Size of each message */
    uintptr_t vringBaseAddr; /**< Base address of VRING */
    uint32    offset_desc;   /**< Offset to descriptors */
    uint32    offset_avail;  /**< Offset to avail queue */
    uint32    offset_used;   /**< Offset to used queue */
    uint32    offset_buf;    /**< Offset to message buffers */
    uint32    isTx;          /**< 1 if TX ring, 0 if RX ring */
} RPMessage_VringResetParams;

static inline uint32 RPMessage_align(uint32 value, uint32 align);
/* utility function to find if core ID runs linux */
uint32               RPMessage_isLinuxCore(RPMessageLLD_Handle handle, uint16 coreId);

/* functions for VRING TX handling and initialization */
void   RPMessage_vringCheckEmptyTxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId);
sint32 RPMessage_vringGetEmptyTxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 *vringBufId,
                                    uint32 timeout);
uint8 *RPMessage_vringGetTxBufAddr(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId);
uint32 RPMessage_vringGetTxBufLen(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId);
sint32 RPMessage_vringPutFullTxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId, uint16 dataLen,
                                   uint32 timeout);

/* functions for VRING RX handling and initialization */
uint32 RPMessage_vringIsFullRxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId);
sint32 RPMessage_vringGetFullRxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 *vringBufId);
uint8 *RPMessage_vringGetRxBufAddr(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId);
sint32 RPMessage_vringPutEmptyRxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId, uint32 timeout);

/* functions for VRING initialization and other utility functions */
void RPMessage_vringReset(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 isTx);
void RPMessage_vringResetInternal(RPMessage_Vring *vringObj, const RPMessage_VringResetParams *resetParams);
/* utility function to align a value, `align` MUST be power of 2 */
static inline uint32 RPMessage_align(uint32 value, uint32 align)
{
    return (value + align - 1U) & ~(align - 1U);
}
#ifdef __cplusplus
}
#endif

#endif /* IPC_RPMSG_PRIV_H_ */
