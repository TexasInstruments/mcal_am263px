/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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

#ifndef Mcal_CacheP_H
#define Mcal_CacheP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

/**
 * \defgroup KERNEL_DPL_CACHE APIs for Cache
 * \ingroup KERNEL_DPL
 *
 * For more details and example usage, see \ref KERNEL_DPL_CACHE_PAGE
 *
 * @{
 */

/**
 * \brief  Cache line size for alignment of buffers.
 * Actual CPU defined cache line can be smaller that this value, this define
 * is a utility macro to keep application portable across different CPU's.
 */
#define Mcal_CacheP_CACHELINE_ALIGNMENT (128U)

/**
 * \brief Cache type
 */
typedef enum Mcal_CacheP_Type_
{
    Mcal_CacheP_TYPE_L1P  = (0x0001u),                                                     /**< L1 program cache */
    Mcal_CacheP_TYPE_L1D  = (0x0002u),                                                     /**< L1 data cache */
    Mcal_CacheP_TYPE_L2P  = (0x0004u),                                                     /**< L2 program cache */
    Mcal_CacheP_TYPE_L2D  = (0x0008u),                                                     /**< L2 data cache */
    Mcal_CacheP_TYPE_L1   = ((uint32)Mcal_CacheP_TYPE_L1P | (uint32)Mcal_CacheP_TYPE_L1D), /**< All L1 cache's */
    Mcal_CacheP_TYPE_L2   = ((uint32)Mcal_CacheP_TYPE_L2P | (uint32)Mcal_CacheP_TYPE_L2D), /**< All L2 cache's */
    Mcal_CacheP_TYPE_ALLP = ((uint32)Mcal_CacheP_TYPE_L1P | (uint32)Mcal_CacheP_TYPE_L2P), /**< All program cache's */
    Mcal_CacheP_TYPE_ALLD = ((uint32)Mcal_CacheP_TYPE_L1D | (uint32)Mcal_CacheP_TYPE_L2D), /**< All data cache's */
    Mcal_CacheP_TYPE_ALL  = ((uint32)Mcal_CacheP_TYPE_L1 | (uint32)Mcal_CacheP_TYPE_L2)    /**< All cache's */
} Mcal_CacheP_Type;

/**
 * \brief Cache config structure, this used by SysConfig and not to be used by end-users directly
 */
typedef struct Mcal_CacheP_Config_
{
    uint32 enable;            /**< 0: cache disabled, 1: cache enabled */
    uint32 enableForceWrThru; /**< 0: force write through disabled, 1: force write through enabled */

} Mcal_CacheP_Config;

/** \brief Externally defined Cache configuration */
extern Mcal_CacheP_Config mcal_gCacheConfig;

/**
 * \brief Cache enable
 *
 * \param type [in] cache type's to enable, refer #Mcal_CacheP_Type \n
 *                  R5: Supports Mcal_CacheP_TYPE_L1P, Mcal_CacheP_TYPE_L1D,
 *                  A53: Supports Mcal_CacheP_TYPE_L1P , Mcal_CacheP_TYPE_L2P, Mcal_CacheP_TYPE_L1D
 * and Mcal_CacheP_TYPE_L2D, C66x: Not used assumes Mcal_CacheP_TYPE_ALL, M4: Not supported
 */
void Mcal_CacheP_enable(uint32 type);

/**
 * \brief Cache disable
 *
 * \param type [in] cache type's to disable, refer #Mcal_CacheP_Type \n
 *                  R5: Supports Mcal_CacheP_TYPE_L1P, Mcal_CacheP_TYPE_L1D,
 *                  A53: Supports Mcal_CacheP_TYPE_L1P , Mcal_CacheP_TYPE_L2P, Mcal_CacheP_TYPE_L1D
 * and Mcal_CacheP_TYPE_L2D, C66x: Not used assumes Mcal_CacheP_TYPE_ALL, M4: Not supported
 */
void Mcal_CacheP_disable(uint32 type);

/**
 * \brief Get cache enabled bits
 *
 * \return cache type's that are enabled
 */
uint32 Mcal_CacheP_getEnabled(void);

/**
 * \brief Cache writeback for full cache
 *
 * \param type [in] cache type's to writeback, refer #Mcal_CacheP_Type \n
 *                  R5: Supports Mcal_CacheP_TYPE_L1P, Mcal_CacheP_TYPE_L1D,
 *                  A53: Supports Mcal_CacheP_TYPE_L1P , Mcal_CacheP_TYPE_L2P, Mcal_CacheP_TYPE_L1D
 * and Mcal_CacheP_TYPE_L2D, C66x: Not used assumes Mcal_CacheP_TYPE_ALL, M4: Not supported
 */
void Mcal_CacheP_wbAll(uint32 type);

/**
 * \brief Cache writeback and invalidate for full cache
 *
 * \param type [in] cache type's to writeback and invalidate, refer #Mcal_CacheP_Type \n
 *                  R5: Supports Mcal_CacheP_TYPE_L1P, Mcal_CacheP_TYPE_L1D,
 *                  A53: Supports Mcal_CacheP_TYPE_L1P , Mcal_CacheP_TYPE_L2P, Mcal_CacheP_TYPE_L1D
 * and Mcal_CacheP_TYPE_L2D, C66x: Not used assumes Mcal_CacheP_TYPE_ALL, M4: Not supported
 */
void Mcal_CacheP_wbInvAll(uint32 type);

/**
 * \brief Cache writeback for a specified region
 *
 * \param addr [in] region address. Recommend to specify address that is cache line aligned
 * \param size [in] region size in bytes. Recommend to specify size that is multiple of cache line
 * size
 * \param type [in] cache type's to writeback, refer #Mcal_CacheP_Type \n
 *                  R5: Supports Mcal_CacheP_TYPE_L1P, Mcal_CacheP_TYPE_L1D,
 *                  A53: Supports Mcal_CacheP_TYPE_L1P , Mcal_CacheP_TYPE_L2P, Mcal_CacheP_TYPE_L1D
 * and Mcal_CacheP_TYPE_L2D, C66x: Not used assumes Mcal_CacheP_TYPE_ALL, M4: Not supported
 */
void Mcal_CacheP_wb(void *addr, uint32 size, uint32 type);

/**
 * \brief Cache invalidate for a specified region
 *
 * \param addr [in] region address. Recommend to specify address that is cache line aligned
 * \param size [in] region size in bytes. Recommend to specify size that is multiple of cache line
 * size
 * \param type [in] cache type's to invalidate, refer #Mcal_CacheP_Type \n
 *                  R5: Supports Mcal_CacheP_TYPE_L1P, Mcal_CacheP_TYPE_L1D,
 *                  A53: Supports Mcal_CacheP_TYPE_L1P , Mcal_CacheP_TYPE_L2P, Mcal_CacheP_TYPE_L1D
 * and Mcal_CacheP_TYPE_L2D, C66x: Not used assumes Mcal_CacheP_TYPE_ALL, M4: Not supported
 */
void Mcal_CacheP_inv(void *addr, uint32 size, uint32 type);
void Mcal_CacheP_invL1p(uint32 blockPtr, uint32 byteCnt);
void Mcal_CacheP_invL1d(uint32 blockPtr, uint32 byteCnt);

/**
 * \brief Cache writeback and invalidate for a specified region
 *
 * \param addr [in] region address. Recommend to specify address that is cache line aligned
 * \param size [in] region size in bytes. Recommend to specify size that is multiple of cache line
 * size
 * \param type [in] cache type's to writeback and invalidate, refer #Mcal_CacheP_Type \n
 *                  R5: Supports Mcal_CacheP_TYPE_L1P, Mcal_CacheP_TYPE_L1D,
 *                  A53: Supports Mcal_CacheP_TYPE_L1P , Mcal_CacheP_TYPE_L2P, Mcal_CacheP_TYPE_L1D
 * and Mcal_CacheP_TYPE_L2D, C66x: Not used assumes Mcal_CacheP_TYPE_ALL, M4: Not supported
 */
void Mcal_CacheP_wbInv(void *addr, uint32 size, uint32 type);

/**
 * \brief Initialize Cache sub-system, called by SysConfig, not to be called by end users
 *
 */
void Mcal_CacheP_init(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* Mcal_CacheP_H */
