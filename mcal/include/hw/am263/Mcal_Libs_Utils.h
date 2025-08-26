/*
 * Copyright (c) 2024 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef MCAL_LIBS_UTILS_H_
#define MCAL_LIBS_UTILS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "Std_Types.h"
#include "hw_ctrl_core.h"
/**
 * \brief Cache type
 */
typedef enum Mcal_CacheP_Type_ {
    Mcal_CacheP_TYPE_L1P  = (0x0001u), /**< L1 program cache */
    Mcal_CacheP_TYPE_L1D  = (0x0002u), /**< L1 data cache */
    Mcal_CacheP_TYPE_L2P  = (0x0004u), /**< L2 program cache */
    Mcal_CacheP_TYPE_L2D  = (0x0008u), /**< L2 data cache */
    Mcal_CacheP_TYPE_L1   = ((uint32)Mcal_CacheP_TYPE_L1P | (uint32)Mcal_CacheP_TYPE_L1D), /**< All L1 cache's */
    Mcal_CacheP_TYPE_L2   = ((uint32)Mcal_CacheP_TYPE_L2P | (uint32)Mcal_CacheP_TYPE_L2D), /**< All L2 cache's */
    Mcal_CacheP_TYPE_ALLP = ((uint32)Mcal_CacheP_TYPE_L1P | (uint32)Mcal_CacheP_TYPE_L2P), /**< All program cache's */
    Mcal_CacheP_TYPE_ALLD = ((uint32)Mcal_CacheP_TYPE_L1D | (uint32)Mcal_CacheP_TYPE_L2D), /**< All data cache's */
    Mcal_CacheP_TYPE_ALL  = ((uint32)Mcal_CacheP_TYPE_L1  | (uint32)Mcal_CacheP_TYPE_L2)    /**< All cache's */
} Mcal_CacheP_Type;

void Mcal_CacheP_invL1p(uint32 blockPtr, uint32 byteCnt);
void Mcal_CacheP_invL1d(uint32 blockPtr, uint32 byteCnt);
void Mcal_CacheP_inv(void *blockPtr, uint32 byteCnt, uint32 type);

void Mcal_Libs_Utils_unlockMMR(void);
void Mcal_Libs_Utils_lockMMR(void);

void Mcal_Libs_Utils_unlockTopRcmMMR(void);
void Mcal_Libs_Utils_lockTopRcmMMR(void);

#ifdef __cplusplus
}
#endif

#endif /* MCAL_LIBS_UTILS_H_*/