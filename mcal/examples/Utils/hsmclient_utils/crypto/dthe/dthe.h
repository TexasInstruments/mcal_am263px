/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \defgroup SECURITY_DTHE_MODULE APIs for DTHE
 *  \ingroup  SECURITY_MODULE
 *
 *  This module contains APIs to program and use the DTHE.
 *
 *  @{
 */

/**
 *  \file dthe.h
 *
 *  \brief This file contains the prototype of DTHE driver APIs
 */

#ifndef DTHE_H_
#define DTHE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <SystemP.h>
#include <cslr_dthe.h>
// #include <drivers/hw_include/cslr_soc.h>
// #include <security_common/drivers/crypto/dthe/dma/device_includes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief
 *  DTHE Driver Error code
 *
 * \details
 *  The enumeration describes all the possible return and error codes which
 *  the DTHE Driver can return
 */
typedef enum DTHE_Return_e
{
    DTHE_RETURN_SUCCESS = 0xCE50311AU, /*!< Success/pass return code */
    DTHE_RETURN_FAILURE = 0x924FC5E7U, /*!< General or unspecified failure/error */
} DTHE_Return_t;

/** \brief Handle to the DTHE driver */
typedef void *DTHE_Handle;

/** \brief DTHE attributes */
typedef struct
{
    /*
     * SOC configuration
     */
    uint32_t caBaseAddr;
    /**< Crypto Accelerator Base Adders*/
    uint32_t aesBaseAddr;
    /**< Aes Base address */
    uint32_t shaBaseAddr;
    /**< sha Base address */
    uint32_t isOpen;
    /**< Flag to indicate whether the instance is opened already */
    uint32_t faultStatus;
    /**< Flag to ascertain whether the handle was opened successfully */
} DTHE_Attrs;

/** \brief DTHE driver context */
typedef struct
{
    DTHE_Attrs *attrs;
    /**< Driver params passed during open */

    uint32_t dmaEnable;
    /**< To enable dthe with dma */
} DTHE_Config;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Externally defined driver configuration array */
extern DTHE_Config gDtheConfig[];
/** \brief Externally defined driver configuration Num */
extern uint32_t    gDtheConfigNum;

/* ========================================================================== */
/*                              Function Definitions                          */
/* ========================================================================== */
/**
 *  \brief          This function initializes the DTHE.
 */
void DTHE_init(void);

/**
 *  \brief          This function de-initializes the DTHE.
 */
void DTHE_deinit(void);

/**
 *  \brief          Function to open DTHE instance, enable DTHE engine.
 *
 *  \param  index   Index of config to use in the *DTHE_Config* array.
 *
 *  \return         A #DTHE_Handle on success or a NULL on an error.
 */
DTHE_Handle DTHE_open(uint32_t index);

/**
 *  \brief          Function to close a DTHE module specified by the DTHE handle.
 *
 *  \param  handle  #DTHE_Handle returned from #DTHE_open()
 *
 *  \return         #DTHE_RETURN_SUCCESS if requested operation completed.
 *                  #DTHE_RETURN_FAILURE if requested operation not completed.
 */
DTHE_Return_t DTHE_close(DTHE_Handle handle);

#ifdef __cplusplus
}
#endif

#endif /* DTHE_H_ */
/** @} */
