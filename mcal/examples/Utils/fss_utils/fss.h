/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
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
 *  \defgroup DRV_FSS_MODULE APIs for FSS
 *  \ingroup DRV_MODULE
 *
 * Contains API to configure Bootseg and ECCM IP.
 *
 *  @{
 */

#ifndef __FSS_H__
#define __FSS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <SystemP.h>
#include <cslr_fss.h>

/**
 * @brief Index for ECCM region 0
 *
 */
#define Region_Index_0 ((uint32_t)(0))

/**
 * @brief Index for ECCM region 1
 *
 */
#define Region_Index_1 ((uint32_t)(1))

/**
 * @brief Index for ECCM region 2
 *
 */
#define Region_Index_2 ((uint32_t)(2))

/**
 * @brief Index for ECCM region 3
 *
 */
#define Region_Index_3 ((uint32_t)(3))

typedef void *FSS_Handle;

typedef struct
{
    uint32_t size;         /**< Size of the region (in bytes, aligned to 4K) */
    uint32_t startAddress; /**< starting address (offset in bytes, aligned to 4K) */
    uint32_t regionIndex;  /**< index for this region */
} FSS_ECCRegionConfig;

typedef struct fss_config_s_t
{
    uint32_t ipBaseAddress; /**< SOC Base address for this IP */
    uint32_t extFlashSize;  /**< size of the external flash */
} FSS_Config;

/**
 * @brief Mask the address bits
 *
 * Use this function to remap external flash. Lower 12 bits cannot be masked.
 *
 * The address that will be sent to external flash will be (address & bitMask) | ((bitMask + 1) * segment)
 *
 * Suppose external flash is 32MB and it is required to map upper 16MB to address 0 so that read from address 0
 * would automatically translar to 16MB read. In this case the bitMask would be 0xffffff and segment would be 1.
 * address that would be sent to flash is (0xffffff * address) | 0x1000000
 *
 * @param handle handle to FSS instance
 * @param bitMask bit mask
 * @param segment segment
 * @return SystemP_SUCCESS on successfull execution
 */
int32_t FSS_addressBitMask(FSS_Handle handle, uint32_t bitMask, uint8_t segment);

/**
 * @brief Disable remap
 *
 * @param handle handle to FSS instance
 * @return SystemP_SUCCESS on successfull execution
 */
int32_t FSS_disableAddressRemap(FSS_Handle handle);

/**
 * @brief Map region A of flash to initial position
 *
 * @param handle handle to FSS instance
 * @return SystemP_SUCCESS on successfull execution
 */
int32_t FSS_selectRegionA(FSS_Handle handle);

/**
 * @brief Map region N of flash to initial position
 *
 * @param handle handle to FSS instance
 * @return SystemP_SUCCESS on successfull execution
 */
int32_t FSS_selectRegionB(FSS_Handle handle);

/**
 * @brief Which boot region is been selected.
 *
 * @param handle handle to FSS instance.
 * @return selected boot region.
 */
uint32_t FSS_getBootRegion(FSS_Handle handle);

/**
 * @brief Enable ECC for Flash
 *
 * This function enabled ECC for the data that is stored in flash.
 * For every 32 Bytes of data, 4 bytes of ECC is assumed.
 * Make sure the data is in flash is prepared at compile time.
 *
 */
void FSS_enableECC(void);

/**
 * @brief Disable ECC
 *
 */
void FSS_disableECC(void);

/**
 * @brief Set size of an ECCM region
 *
 * @param regionIndex region ID
 * @param size_in_bytes size of region in bytes
 */
void FSS_setECCRegionSize(uint32_t regionIndex, uint32_t size_in_bytes);

/**
 * @brief Set start address of an ECCM region
 *
 * @param regionIndex region ID
 * @param ecc_reg_start start address
 */
void FSS_setECCRegionStart(uint32_t regionIndex, uint32_t ecc_reg_start);

/**
 * @brief Configure en ECCM Region.
 *
 * @param parameter parameters for the region
 * @return int32_t
 */
int32_t FSS_configECCMRegion(FSS_ECCRegionConfig *parameter);

/**
 * @brief Configure ECCM hardware
 *
 * @param numRegion region ID
 * @param parameter region config data
 */
int32_t FSS_ConfigEccm(uint32_t numRegion, FSS_ECCRegionConfig *parameter);

#ifdef __cplusplus
}
#endif

#endif

/** @} */
