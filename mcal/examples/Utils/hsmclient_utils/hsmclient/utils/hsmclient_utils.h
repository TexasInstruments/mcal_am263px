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

#ifndef HSM_CLIENT_UTILS_H_
#define HSM_CLIENT_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup DRV_HSMCLIENT_UTILS_MODULE APIs for HSMCLIENT_UTILS
 * \ingroup DRV_MODULE
 *
 * See \ref DRIVERS_HSMCLIENT_PAGE for more details.
 *
 * @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <stdlib.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** @brief SOC TYPE FLAG for AM263X */
#define SOC_TYPE_AM263X 0x1
/** @brief SOC TYPE FLAG for AM263p */
#define SOC_TYPE_AM263P 0x2
/** @brief SOC TYPE FLAG for AM273x */
#define SOC_TYPE_AM273X 0x3
/** @brief SOC TYPE FLAG for AWR294x */
#define SOC_TYPE_AWR294X 0x4
/** @brief SOC TYPE FLAG for F29H85x */
#define SOC_TYPE_F29H85x 0x5
/** @brief SOC TYPE FLAG for AM261x */
#define SOC_TYPE_AM261x 0x6
/** @brief Count of all supported SOC's */
#define NUM_SOC_TYPE 0x7

/** @brief Device type flag for HS-FS */
#define DEVICE_TYPE_HS_FS 0x00
/** @brief Device type flag for HS-SE */
#define DEVICE_TYPE_HS_SE 0xFF

/** @brief HSM Version flag */
#define HSM_V1 0x1

/** @brief Binary type flag for STANDARD */
#define BIN_TYPE_STANDARD 0x55
/** @brief Binary type flag for CUSTOM */
#define BIN_TYPE_CUSTOM 0xAA
/** @brief Binary type flag for OTPKW */
#define BIN_TYPE_OTPKW 0x33

typedef union HsmVer_t_ HsmVer_t;

/* ========================================================================== */
/*                             Function Declaration                           */
/* ========================================================================== */

/**
 * \brief Parses Version string.
 *
 * \param tifsMcuVer Pointer to HsmVer_t version union
 * \param parsedVer Pointer to parsed string
 *
 * \returns status returns System_SUCCESS on successful parsing,
 *			else System_FAILURE.
 */
int32_t HsmClient_parseVersion(HsmVer_t* tifsMcuVer, char* parsedVer);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HSM_CLIENT_UTILS_H_ */
