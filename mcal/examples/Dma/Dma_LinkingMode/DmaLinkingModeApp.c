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
 *  \file     DmaLinkingModeApp.c
 *
 *  \brief    This file contains the Dma test example
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "assert.h"

#include "string.h"
#include "Det.h"
#include "Dem.h"
#include "Std_Types.h"
#include "Os.h"

#include "EcuM_Cbk.h"
#include "sys_common.h"
#include "trace.h"
#include "soc.h"
#include "DmaLinkingModeApp.h"
#include "DmaLinkingModeApp_Startup.h"
#include "CacheP.h"
#include "Cdd_Dma.h"

#define CDD_DMA_TEST_A_COUNT (16U)
/* Value for B count */
#define CDD_DMA_TEST_B_COUNT (4U)
/* Value for C count */
#define CDD_DMA_TEST_C_COUNT     (2U)
#define CDD_DMA_TEST_BUFFER_SIZE (CDD_DMA_TEST_A_COUNT * CDD_DMA_TEST_B_COUNT * CDD_DMA_TEST_C_COUNT)

uint32              handleId = CddDmaConf_CddDmaDriverHandler_MemoryTransfer_Linking;
Std_VersionInfoType VersionInfo;
volatile uint32     Cdd_Dma_TestDoneSem = 1;
/* The source buffer used for transfer */
static uint8 Cdd_Dma_TestSrcBuff[CDD_DMA_TEST_BUFFER_SIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));
/* The destination buffer used for transfer */
static uint8 Cdd_Dma_TestDstBuff[CDD_DMA_TEST_BUFFER_SIZE] __attribute__((aligned(Mcal_CacheP_CACHELINE_ALIGNMENT)));
/* Callback registered for the transmission */
static void  Cdd_Dma_RegionIsrFxn(void *args);

void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

static void Cdd_Dma_LinkingModeApp_mainTest(void)
{
    AppUtils_TimerInit();
    uint8             *srcPtr, *dstPtr;
    Cdd_Dma_ParamEntry paramEntry0, paramEntry1;
    uint32             opt, shift, status = MCAL_SystemP_SUCCESS;
#if (CDD_DMA_VERSION_INFO_API == STD_ON)

    Std_VersionInfoType versioninfo;

    /* Version Info Check*/
    Cdd_Dma_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n\r");
    AppUtils_printf(APP_NAME ": DMA MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf(APP_NAME ": Vendor ID: %d\n\r", versioninfo.vendorID);
    AppUtils_printf(APP_NAME ": Module ID: %d\n\r", versioninfo.moduleID);
    AppUtils_printf(APP_NAME ": SW Major Version: %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf(APP_NAME ": SW Minor Version: %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf(APP_NAME ": SW Patch Version: %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n\r");
#endif

#if (STD_ON == CDD_DMA_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n");
#endif
    AppUtils_printf(" \n\r");

#if (STD_ON == CDD_DMA_PRE_COMPILE_VARIANT)
    Cdd_Dma_Init(NULL_PTR);
#endif

    srcPtr = (uint8 *)Cdd_Dma_TestSrcBuff;
    dstPtr = (uint8 *)Cdd_Dma_TestDstBuff;
    for (uint32 count = 0; count < CDD_DMA_TEST_BUFFER_SIZE; count++)
    {
        srcPtr[count] = (uint8)count;
        dstPtr[count] = 0;
    }
    Mcal_CacheP_wb((void *)dstPtr, CDD_DMA_TEST_BUFFER_SIZE, Mcal_CacheP_TYPE_ALL);
    /* Transfer is done using AB sync mode */
    opt   = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK | CDD_EDMA_OPT_SYNCDIM_MASK);
    shift = (CDD_DMA_TEST_A_COUNT * CDD_DMA_TEST_B_COUNT * CDD_DMA_TEST_C_COUNT / 2);

    /* Filling the paramEntry for param 0  of channel0*/
    paramEntry0.srcPtr     = srcPtr;
    paramEntry0.destPtr    = dstPtr;
    paramEntry0.aCnt       = CDD_DMA_TEST_A_COUNT;
    paramEntry0.bCnt       = CDD_DMA_TEST_B_COUNT;
    paramEntry0.cCnt       = CDD_DMA_TEST_C_COUNT / 2;
    paramEntry0.bCntReload = 0;
    paramEntry0.srcBIdx    = CDD_DMA_TEST_A_COUNT;
    paramEntry0.destBIdx   = CDD_DMA_TEST_A_COUNT;
    paramEntry0.srcCIdx    = CDD_DMA_TEST_A_COUNT * CDD_DMA_TEST_B_COUNT;
    paramEntry0.destCIdx   = CDD_DMA_TEST_A_COUNT * CDD_DMA_TEST_B_COUNT;
    paramEntry0.opt        = opt;

    /* Filling the paramEntry for param 1  of channel0*/
    paramEntry1.srcPtr     = srcPtr + shift;
    paramEntry1.destPtr    = dstPtr + shift;
    paramEntry1.aCnt       = CDD_DMA_TEST_A_COUNT;
    paramEntry1.bCnt       = CDD_DMA_TEST_B_COUNT;
    paramEntry1.cCnt       = CDD_DMA_TEST_C_COUNT / 2;
    paramEntry1.bCntReload = 0;
    paramEntry1.srcBIdx    = CDD_DMA_TEST_A_COUNT;
    paramEntry1.destBIdx   = CDD_DMA_TEST_A_COUNT;
    paramEntry1.srcCIdx    = CDD_DMA_TEST_A_COUNT * CDD_DMA_TEST_B_COUNT;
    paramEntry1.destCIdx   = CDD_DMA_TEST_A_COUNT * CDD_DMA_TEST_B_COUNT;
    paramEntry1.opt        = opt;

    Cdd_Dma_ParamSet(handleId, 0, 0, paramEntry0);
    Cdd_Dma_ParamSet(handleId, 0, 1, paramEntry1);
    /* Linking the twp params */
    Cdd_Dma_LinkChannel(handleId, 0, 1);
    void *appdata = (void *)&Cdd_Dma_TestDoneSem;
    /* Registering the callback */
    Cdd_Dma_CbkRegister(handleId, appdata, &Cdd_Dma_RegionIsrFxn);
    /* Transfer is done in AB sync mode. Every enable transfer API call
     * will transfer aCnt * bCnt bymber of bytes and required cCnt (EDMA_TEST_C_COUNT/2)
     * number of triggers for param0.
     * At the end of transfer param1 will be loaded in param0 because of linking.
     * param1 is also configured in AB Sync mode and require EDMA_TEST_C_COUNT/2
     * number of triggers to complete transfer.
     */
    for (uint32 count = 0; count < CDD_DMA_TEST_C_COUNT; count++)
    {
        Cdd_Dma_EnableTransferRegion(handleId, CDD_EDMA_TRIG_MODE_MANUAL);
        while (Cdd_Dma_TestDoneSem == 1)
            ;
        Cdd_Dma_TestDoneSem = 1;
    }
    Mcal_CacheP_inv((uint32 *)dstPtr, CDD_DMA_TEST_BUFFER_SIZE, Mcal_CacheP_TYPE_ALL);

    for (uint32 count = 0; count < CDD_DMA_TEST_BUFFER_SIZE; count++)
    {
        if (srcPtr[count] != dstPtr[count])
        {
            AppUtils_printf(APP_NAME ":Sample test case fail \n\r");
            status = MCAL_SystemP_FAILURE;
            break;
        }
    }

#if (STD_ON == CDD_DMA_DEINIT_API)
    if (status != MCAL_SystemP_FAILURE)
    {
        AppUtils_printf(APP_NAME "All tests have passed\n\r");
    }
    Cdd_Dma_DeInit();
#endif

    AppUtils_TimerDeinit();
}

uint8 MainFunc_Execution;

int main(void)
{
    Cdd_Dma_LinkingModeApp_Startup();

    Cdd_Dma_App_PlatformInit();

    Mcal_CacheP_init();
    Cdd_Dma_InterruptConfig();

    AppUtils_printf("DmaLinkingModeApp: Sample Application - STARTS !!!\n\r ");

    Cdd_Dma_LinkingModeApp_mainTest();
    return 0;
}

#if (defined CLANG) || (defined DIAB)
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif

void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
static void Cdd_Dma_RegionIsrFxn(void *args)
{
    Cdd_Dma_TestDoneSem = 0;
}
