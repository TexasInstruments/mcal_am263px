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
 *  \file   dthe.c
 *
 *  \brief  This file contains the implementation of Dthe driver
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "Platform_Types.h"
#include <dthe.h>
#include "Compiler.h"
// #include <drivers/hw_include/cslr.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void DTHE_init(void)
{
    return;
}

void DTHE_deinit(void)
{
    return;
}

DTHE_Handle DTHE_open(uint32_t index)
{
    DTHE_Return_t status = DTHE_RETURN_SUCCESS;
    DTHE_Handle   handle = NULL_PTR;
    DTHE_Config  *config = NULL_PTR;
    DTHE_Attrs   *attrs  = NULL_PTR;
    /* Check instance */
    if (index >= gDtheConfigNum)
    {
        status = DTHE_RETURN_FAILURE;
    }
    else
    {
        config = &gDtheConfig[index];
        // DebugP_assert(NULL_PTR != config->attrs);
        attrs = config->attrs;
        if (TRUE == attrs->isOpen)
        {
            /* Handle is already opened */
            status             = DTHE_RETURN_FAILURE;
            attrs->faultStatus = status;
        }
    }

    if (DTHE_RETURN_SUCCESS == status)
    {
        attrs->isOpen      = TRUE;
        handle             = (DTHE_Handle)config;
        attrs->faultStatus = status;
    }
    else
    {
        /* status ireturned here will be failure as the handle is not
         * instantiated when the DTHE is already open (attrs->isOpen
         * is set to TRUE)
         */
        status = DTHE_close(handle);
    }
    return (handle);
}

DTHE_Return_t DTHE_close(DTHE_Handle handle)
{
    DTHE_Return_t status = DTHE_RETURN_FAILURE;
    DTHE_Config  *config = NULL_PTR;
    DTHE_Attrs   *attrs  = NULL_PTR;
    if (handle != NULL_PTR)
    {
        config = (DTHE_Config *)handle;
        if (config->attrs->isOpen != (uint32_t)FALSE)
        {
            attrs = config->attrs;
            // DebugP_assert(NULL_PTR != attrs);
            attrs->isOpen = FALSE;
            /* To disable module */
            handle = NULL_PTR;
            status = DTHE_RETURN_SUCCESS;
        }
    }

    return (status);
}
