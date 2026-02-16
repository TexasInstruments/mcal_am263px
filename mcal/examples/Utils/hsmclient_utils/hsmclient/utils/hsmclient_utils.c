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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <hsmclient.h>
#include "hsmclient_utils.h"

/* ========================================================================== */
/*                             Constant Declaration                           */
/* ========================================================================== */

static const char soc_type_arr[NUM_SOC_TYPE][8] = {
    "AM263x", "AM263p", "AM273x", "AWR294x", "F29H85x", "AM261X",
};

/* ========================================================================== */
/*                             Static Function Declaration                    */
/* ========================================================================== */

/**
 * \brief Parse SOC Type
 *
 * \param soc_type SOC Type from version struct.
 * \param parsedVer Pointer to parsed string.
 *
 */
static void HsmClient_getSocType(uint8_t soc_type, char* parsedVer);

/**
 * \brief Parse Device Type
 *
 * \param device_type Device Type from version struct.
 * \param parsedVer Pointer to parsed string.
 *
 */
static void HsmClient_getDeviceType(uint8_t device_type, char* parsedVer);

/**
 * \brief Parse Binary Type
 *
 * \param hsm_type Binary Type from version struct.
 * \param parsedVer Pointer to parsed string.
 *
 */
static void HsmClient_getHSMType(uint8_t hsm_type, char* parsedVer);

/**
 * \brief Parse Binary Type
 *
 * \param bin_type Binary Type from version struct.
 * \param parsedVer Pointer to parsed string.
 *
 */
static void HsmClient_getBinType(uint8_t bin_type, char* parsedVer);

/**
 * \brief Integer to alphanumberic conversion.
 *
 * \param value Number to convert to string.
 * \param str Pointer to buffer large enough to hold number.
 * \param base Base to convert number to.
 *
 * \returns Pointer to str.
 */
static uint8_t* lib_itoa(uint32_t value, uint8_t* str, uint32_t base);

/* ========================================================================== */
/*                             Static Function Definition                     */
/* ========================================================================== */

static uint8_t* lib_itoa(uint32_t value, uint8_t* str, uint32_t base)
{
    uint32_t idx = 0;
    uint32_t val;
    uint32_t i;

    if (value == 0U)
    {
        str[0] = (uint8_t)'0';
        idx++;
    }

    while (value > 0U)
    {
        val = value % base;
        if (val < 10U)
        {
            str[idx] = (uint8_t)(val + '0');
        }
        else
        {
            str[idx] = (uint8_t)((val - 10U) + 'A');
        }

        idx++;
        value /= base;
    }

    str[idx] = (uint8_t)'\0';

    if (idx > 1U)
    {
        /* Get length of string - NULL terminator*/
        idx--;

        /* Reverse the string as we converted from low digit to high */
        for (i = 0U; i <= idx / 2U; i++)
        {
            val          = str[idx - i];
            str[idx - i] = str[i];
            str[i]       = (uint8_t)val;
        }
    }

    return str;
}

static void HsmClient_getSocType(uint8_t soc_type, char* parsedVer)
{
    strcpy(parsedVer, "\r\n[Soc Type]          = ");
    strcat(parsedVer, soc_type_arr[soc_type - 1]);
}

static void HsmClient_getDeviceType(uint8_t device_type, char* parsedVer)
{
    strcat(parsedVer, "\r\n[Device Type]       = ");
    switch (device_type)
    {
        case DEVICE_TYPE_HS_FS:
            strcat(parsedVer, "HS-FS");
            break;
        case DEVICE_TYPE_HS_SE:
            strcat(parsedVer, "HS-SE");
            break;
        default:
            break;
    }
}

static void HsmClient_getHSMType(uint8_t hsm_type, char* parsedVer)
{
    strcat(parsedVer, "\r\n[HSM Type]          = ");
    switch (hsm_type)
    {
        case HSM_V1:
            strcat(parsedVer, "HSM_V1");
            break;
        default:
            break;
    }
}

static void HsmClient_getBinType(uint8_t bin_type, char* parsedVer)
{
    strcat(parsedVer, "\r\n[Bin Type]          = ");
    switch (bin_type)
    {
        case BIN_TYPE_STANDARD:
            strcat(parsedVer, "STANDARD");
            break;
        case BIN_TYPE_CUSTOM:
            strcat(parsedVer, "CUSTOM");
            break;
        case BIN_TYPE_OTPKW:
            strcat(parsedVer, "OTPKW");
            break;
        default:
            break;
    }
}

/* ========================================================================== */
/*                            Function Definition                             */
/* ========================================================================== */

int32_t HsmClient_parseVersion(HsmVer_t* tifsMcuVer, char* parsedVer)
{
    int32_t status = SystemP_FAILURE;

    HsmClient_getSocType(tifsMcuVer->VerStruct.SocType, parsedVer);
    HsmClient_getDeviceType(tifsMcuVer->VerStruct.DevType, parsedVer);
    HsmClient_getHSMType(tifsMcuVer->VerStruct.HsmType, parsedVer);
    HsmClient_getBinType(tifsMcuVer->VerStruct.BinType, parsedVer);
    if (tifsMcuVer->VerStruct.BinType == BIN_TYPE_OTPKW)
    {
        strcat(parsedVer, "\r\n[OTP-KW Version]    = ");
    }
    else
    {
        strcat(parsedVer, "\r\n[TIFS-MCU Version]  = ");
    }
    lib_itoa(tifsMcuVer->VerStruct.MajorVer, (uint8_t*)&parsedVer[strlen(parsedVer)], 10);
    parsedVer[strlen(parsedVer)] = '.';
    lib_itoa(tifsMcuVer->VerStruct.MinorVer, (uint8_t*)&parsedVer[strlen(parsedVer)], 10);
    parsedVer[strlen(parsedVer)] = '.';
    lib_itoa(tifsMcuVer->VerStruct.PatchVer, (uint8_t*)&parsedVer[strlen(parsedVer)], 10);
    parsedVer[strlen(parsedVer)] = '\0';
    status                       = SystemP_SUCCESS;

    return status;
}
