/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2021 Texas Instruments Incorporated
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

#include <bootloader.h>
#include <bootloader_fls.h>
#include "Fls.h"

static int32_t  Flash_imgOpen(void *args, Bootloader_Params *params);
static int32_t  Flash_imgRead(void *dst, uint32_t len, void *args);
static uint32_t Flash_imgGetCurOffset(void *args);
static void     Flash_imgSeek(uint32_t location, void *args);
static void     Flash_imgClose(void *handle, void *args);
static int32_t  Flash_imgDacModeToggle(void *args);

extern Fls_ConfigSfdp *fls_config_sfdp;

Bootloader_Fxns gBootloaderFlashFxns = {
    .imgOpenFxn   = Flash_imgOpen,
    .imgReadFxn   = Flash_imgRead,
    .imgOffsetFxn = Flash_imgGetCurOffset,
    .imgSeekFxn   = Flash_imgSeek,
    .imgCloseFxn  = Flash_imgClose,
    .imgCustomFxn = Flash_imgDacModeToggle,
};

volatile uint32 Fls_JobDoneSuccess;
volatile uint32 Fls_JobDoneError;
Std_ReturnType  retVal = E_OK;

static void main_handling()
{
    AppUtils_printf(APP_NAME ": Job Processing in Progress.\n\r");
    while (1U)
    {
        Fls_MainFunction();
        if (Fls_JobDoneSuccess == 1U)
        {
            AppUtils_printf(APP_NAME ": Job Ends: SUCCESS\n\r");
            retVal = E_OK;
            break;
        }
        if (Fls_JobDoneError == 1U)
        {
            AppUtils_printf(APP_NAME ": Job Ends: Error\n\r");
            retVal = E_NOT_OK;
            break;
        }
    }

    Fls_JobDoneSuccess = 0U;
    Fls_JobDoneError   = 0U;
    return;
}

static void main_handling_intr()
{
    AppUtils_printf(APP_NAME ": Job Processing in Progress.\n\r");
    while (1U)
    {
        if (Fls_JobDoneSuccess == 1U)
        {
            AppUtils_printf(APP_NAME ": Job Ends: SUCCESS\n\r");
            retVal = E_OK;
            break;
        }
        if (Fls_JobDoneError == 1U)
        {
            AppUtils_printf(APP_NAME ": Job Ends: Error\n\r");
            retVal = E_NOT_OK;
            break;
        }
    }

    Fls_JobDoneSuccess = 0U;
    Fls_JobDoneError   = 0U;
    return;
}

void Fee_JobEndNotification(void)
{
    Fls_JobDoneSuccess = 1U;
}

void Fee_JobErrorNotification(void)
{
    Fls_JobDoneError = 1U;
}

static int32_t Flash_imgOpen(void *args, Bootloader_Params *params)
{
    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)args;
    flashArgs->curOffset            = flashArgs->appImageOffset;
    return SystemP_SUCCESS;
}

static int32_t Flash_imgRead(void *dst, uint32_t len, void *args)
{
    Std_ReturnType        job_accepted = E_OK;
    Bootloader_FlashArgs *flashArgs    = (Bootloader_FlashArgs *)args;
    // Flash_Handle handle = Flash_getHandle(flashArgs->flashIndex);
    // Flash_Attrs *attrs = Flash_getAttrs(flashArgs->flashIndex);

    if (flashArgs->curOffset + len < Fls_Config_SFDP_Ptr->flashSize)
    {
        while (1U)
        {
            job_accepted = Fls_Read(flashArgs->curOffset, (uint8_t *)dst, len);
            if (E_OK == job_accepted)
            {
                break;
            }
        }
#if (STD_OFF == FLS_USE_INTERRUPTS)
        main_handling();
#else
        main_handling_intr();
#endif
        Mcal_CacheP_wb(dst, len, Mcal_CacheP_TYPE_ALL);
        flashArgs->curOffset += len;
    }

    return SystemP_SUCCESS;
}

static uint32_t Flash_imgGetCurOffset(void *args)
{
    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)args;
    return flashArgs->curOffset;
}

static void Flash_imgSeek(uint32_t location, void *args)
{
    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)args;
    flashArgs->curOffset            = flashArgs->appImageOffset + location;
    return;
}

static void Flash_imgClose(void *handle, void *args)
{
    return;
}

static int32_t Flash_imgDacModeToggle(void *args)
{
    int32_t status = SystemP_FAILURE;

    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)args;

    /* Get Flash handle */
    // Flash_Handle flashHandle = Flash_getHandle(flashArgs->flashIndex);

    if (TRUE == flashArgs->enableDacMode)
    {
        /* Enable DAC Mode */
        // status = Flash_enableDacMode(flashHandle);
    }
    else
    {
        /* Disable DAC Mode */
        // status = Flash_disableDacMode(flashHandle);
    }

    return status;
}
