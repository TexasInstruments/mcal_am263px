/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
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
 *  \file     CddFlcApp.c
 *
 *  \brief    This file contains the FLC test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "CddFlcApp.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* HW ID to test */
#define FLC_APP_HW_ID (CDD_FLC_RL2_R5SS0_CORE0)
/* Buffer size */
#define FLC_APP_BUFFER_SIZE (4096U)
/* Number of loop to run the FLC test */
#define FLC_APP_LOOP_CNT (5U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void CddFlc_appInit(void);
static void CddFlc_appDeInit(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Test pass flag */
static uint32 gTestPassed = E_OK;

/* Source and destination buffers used by FLC module */
static uint8_t gSrcBuf[FLC_APP_BUFFER_SIZE] __attribute__((aligned(CDD_FLC_ADDR_ALIGNMENT)));
static uint8_t gDestBuf[FLC_APP_BUFFER_SIZE] __attribute__((aligned(CDD_FLC_ADDR_ALIGNMENT)));

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    Std_ReturnType           retVal;
    Cdd_Flc_HwUnitType       hwUnitId;
    Cdd_Flc_RegionId         regionId;
    Cdd_Flc_RegionConfigType regionCfg;
    Cdd_Flc_StatusType       status;
    uint32                   loopCnt;

    CddFlc_appInit();

    hwUnitId = FLC_APP_HW_ID;
    for (regionId = CDD_FLC_REGION_ID_0; regionId < CDD_FLC_REGION_ID_MAX; regionId++)
    {
        loopCnt = 0U;
        while (loopCnt < FLC_APP_LOOP_CNT)
        {
            AppUtils_printf(APP_NAME ": FLC copy for region ID: %d, Loop: %d!!!\r\n", regionId, loopCnt);

            /* Initialize buffers before every test */
            for (uint32 i = 0U; i < FLC_APP_BUFFER_SIZE; i++)
            {
                gSrcBuf[i]  = i + loopCnt + regionId; /* for getting different data for every loop */
                gDestBuf[i] = 0U;
            }

            /* Configure region */
            regionCfg.srcStartAddr  = (uint32)&gSrcBuf[0U];
            regionCfg.srcEndAddr    = (uint32)&gSrcBuf[FLC_APP_BUFFER_SIZE];
            regionCfg.destStartAddr = (uint32)&gDestBuf[0U];
            retVal                  = Cdd_Flc_ConfigureRegion(hwUnitId, regionId, &regionCfg);
            if (retVal != E_OK)
            {
                AppUtils_printf(APP_NAME ": Cdd_Flc_ConfigureRegion() API failed!!!\r\n");
                gTestPassed = retVal;
                break;
            }

            /* Enable and start the copy */
            Cdd_Flc_EnableRegion(hwUnitId, regionId, FALSE);

            /* Wait for copy to complete */
            while (1U)
            {
                if (TRUE == Cdd_Flc_IsRegionCopyDone(hwUnitId, regionId))
                {
                    break;
                }
            }

            /* Check and clear error status */
            Cdd_Flc_GetStatus(hwUnitId, &status);
            Cdd_Flc_ClearAllStatus(hwUnitId);
            if (status.copyDone != TRUE)
            {
                AppUtils_printf(APP_NAME ": Copy failed!!!\r\n");
                gTestPassed = E_NOT_OK;
            }
            if (status.wrError == TRUE)
            {
                AppUtils_printf(APP_NAME ": Write failed!!!\r\n");
                gTestPassed = E_NOT_OK;
            }
            if (status.rdError == TRUE)
            {
                AppUtils_printf(APP_NAME ": Read failed!!!\r\n");
                gTestPassed = E_NOT_OK;
            }

            /*
             * Compare data
             */
            /* Copy is via DMA. So invalidate the destination buffer */
            Mcal_CacheP_inv((uint32 *)&gDestBuf[0U], FLC_APP_BUFFER_SIZE, Mcal_CacheP_TYPE_ALL);
            if (memcmp(&gSrcBuf[0U], &gDestBuf[0U], FLC_APP_BUFFER_SIZE) != 0)
            {
                AppUtils_printf(APP_NAME ": Data compare failed!!!\r\n");
                gTestPassed = E_NOT_OK;
            }

            /* Disable the region */
            Cdd_Flc_DisableRegion(hwUnitId, regionId);

            if (gTestPassed != E_OK)
            {
                break;
            }
            loopCnt++;
        }

        if (gTestPassed != E_OK)
        {
            break;
        }
    }

    CddFlc_appDeInit();

    return 0;
}

static void CddFlc_appInit(void)
{
#if (STD_ON == CDD_FLC_VERSION_INFO_API)
    Std_VersionInfoType versioninfo;
#endif /* #if (STD_ON == CDD_FLC_VERSION_INFO_API) */

    CddFlcApp_PlatformInit();
    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\r\n");

#if (STD_ON == CDD_FLC_VERSION_INFO_API)
    /* Get and print version */
    Cdd_Flc_GetVersionInfo(&versioninfo);
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " \r\n");
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " FLC MCAL Version Info\r\n");
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " ---------------------\r\n");
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " Vendor ID           : %d\r\n", versioninfo.vendorID);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " Module ID           : %d\r\n", versioninfo.moduleID);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Major Version    : %d\r\n", versioninfo.sw_major_version);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Minor Version    : %d\r\n", versioninfo.sw_minor_version);
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " SW Patch Version    : %d\r\n", versioninfo.sw_patch_version);
    GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, " \r\n");
#endif /* #if (STD_ON == CDD_FLC_VERSION_INFO_API) */
}

static void CddFlc_appDeInit(void)
{
    GT_1trace(GT_INFO1 | GT_TraceState_Enable, GT_INFO, "\nCDD_FLC_APP: Stack Usage: %d bytes\n\r",
              AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(GT_INFO1 | GT_TraceState_Enable, GT_ERR, "CDD_FLC Stack/section corruption!!!\n\r");
    }

    if (E_OK == gTestPassed)
    {
        AppUtils_printf(APP_NAME ": Sample Application - DONE (Passed) !!!\r\n");
        AppUtils_printf(APP_NAME ": All tests have passed\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_PASS);
    }
    else
    {
        AppUtils_printf(APP_NAME ": Sample Application - DONE (Failed) !!!\r\n");
        AppUtils_logTestResult(APP_UTILS_TEST_STATUS_FAIL);
    }

    CddFlcApp_PlatformDeInit();
}

void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
