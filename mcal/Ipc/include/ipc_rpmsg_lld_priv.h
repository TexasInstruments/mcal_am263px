/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

static inline uint32 RPMessage_align(uint32 value, uint32 align);
/* utility function to find if core ID runs linux */
uint32               RPMessage_isLinuxCore(RPMessageLLD_Handle handle, uint16 coreId);

/* functions for VRING TX handling and initialization */
void   RPMessage_vringCheckEmptyTxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId);
sint32 RPMessage_vringGetEmptyTxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 *vringBufId,
                                    uint32 timeout);
uint8 *RPMessage_vringGetTxBufAddr(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId);
uint32 RPMessage_vringGetTxBufLen(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId);
void   RPMessage_vringPutFullTxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId, uint16 dataLen,
                                   uint32 timeout);

/* functions for VRING RX handling and initialization */
uint32 RPMessage_vringIsFullRxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId);
sint32 RPMessage_vringGetFullRxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 *vringBufId);
uint8 *RPMessage_vringGetRxBufAddr(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId);
void   RPMessage_vringPutEmptyRxBuf(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 vringBufId, uint32 timeout);

/* functions for VRING initialization and other utility functions */
void RPMessage_vringReset(RPMessageLLD_Handle handle, uint16 remoteCoreId, uint16 isTx);
void RPMessage_vringResetInternal(RPMessage_Vring(*vringObj), uint16 numBuf, uint16 msgSize, uintptr_t vringBaseAddr,
                                  uint32 offset_desc, uint32 offset_avail, uint32 offset_used, uint32 offset_buf,
                                  uint32 isTx);

/* utility function to align a value, `align` MUST be power of 2 */
static inline uint32 RPMessage_align(uint32 value, uint32 align)
{
    return (value + align - 1U) & ~(align - 1U);
}
#ifdef __cplusplus
}
#endif

#endif /* IPC_RPMSG_PRIV_H_ */
