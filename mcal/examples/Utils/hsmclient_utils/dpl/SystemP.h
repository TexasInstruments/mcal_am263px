/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2018-2021 Texas Instruments Incorporated
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

#ifndef SYSTEMP_H
#define SYSTEMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
// #include <kernel/dpl/DebugP.h>

/**
 * \defgroup KERNEL_DPL_SYSTEM  APIs for system level define's and function's
 * \ingroup KERNEL_DPL
 *
 * @{
 */

/** @name Return status
 */
/**@{*/
/**
 * \brief Return status when the API execution was successful
 */
#define SystemP_SUCCESS ((int32_t)0)

/**
 * \brief Return status when the API execution was not successful due to a failure
 */
#define SystemP_FAILURE ((int32_t)-1)

/**
 * \brief Return status when the API execution was not successful due to a time out
 */
#define SystemP_TIMEOUT ((int32_t)-2)

/**@}*/

/** @name Timeout values
 *  @anchor SystemP_Timeout
 */
/**@{*/

/**
 * \brief Value to use when needing a timeout of zero or NO timeout, return immediately on resource not available.
 */
#define SystemP_NO_WAIT ((uint32_t)0)

/**
 * \brief Value to use when needing a timeout of infinity or wait forver until resource is available
 */
#define SystemP_WAIT_FOREVER ((uint32_t)-1)
/**@}*/

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEMP_H */

/**
 * \defgroup KERNEL_DPL APIs for Driver Porting Layer
 *
 * This module contains APIs which are used by the drivers to make them agnostic of the underlying OS and CPU
 * architecture.
 */

/**
 * \defgroup DRV_MODULE APIs for SOC Specific Device Drivers
 *
 * This module contains APIs for device drivers for various peripherals supported in this SDK
 */

/**
 * \cond !SOC_AM62X && !SOC_AM65X
 */
/**
 * \defgroup BOARD_MODULE APIs for Board Specific Device Drivers
 *
 * This module contains APIs for device drivers for various peripherals supported on the EVM or board supported by this
 * SOC
 */

/**
 * \defgroup SECURITY_MODULE APIs for Security Drivers
 *
 * This module contains APIs which are used by the Security drivers.
 */

/**
 * \defgroup TSN_UNIBASE_MODULE APIs for Unibase Binding
 *
 * This module contains APIs which are used by the Unibase Binding.
 */

/**
 * \defgroup TSN_COMBASE_MODULE APIs for combase Binding
 *
 * This module contains APIs which are used by the combase Binding.
 */

/**
 * \defgroup TSN_GPTP APIs for TSN GPTP
 *
 * This module contains APIs which are used by gptp module.
 */

/**
 * \defgroup EnetLLD_network APIs for Enet LLD network
 *
 * This module contains APIs which are used by the Enet LLD network driver.
 */

/**
 * \defgroup SDL_MODULE APIs for SDL Module
 *
 * This module contains APIs which are used by the SDL Module.
 */

/**
 * \defgroup SDL_IP_MODULE APIs for SDL IP Module
 *
 * This module contains APIs which are used by the SDL IP Module.
 */

/**
 * \endcond
 */
