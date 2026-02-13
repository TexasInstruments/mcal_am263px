/* ======================================================================
 *   Copyright (c) 2022 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     DmaInterruptModeApp.c
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
#include "DmaInterruptModeApp.h"
#include "DmaInterruptModeApp_Startup.h"
#include "CacheP.h"
#include "Cdd_Dma.h"

#define CDD_DMA_TEST_A_COUNT (16U)
/* Value for B count */
#define CDD_DMA_TEST_B_COUNT (4U)
/* Value for C count */
#define CDD_DMA_TEST_C_COUNT     (2U)
#define CDD_DMA_TEST_BUFFER_SIZE (CDD_DMA_TEST_A_COUNT * CDD_DMA_TEST_B_COUNT * CDD_DMA_TEST_C_COUNT)

uint32              handleId = CddDmaConf_CddDmaDriverHandler_MemoryTransfer_Interrupt;
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

static void Cdd_Dma_InterruptModeApp_mainTest(void)
{
    AppUtils_TimerInit();
    uint8             *srcPtr, *dstPtr;
    Cdd_Dma_ParamEntry paramEntry0;
    uint32             opt, status = MCAL_SystemP_SUCCESS;
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
    /* Transfer is done using A sync mode */
    opt = (CDD_EDMA_OPT_TCINTEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK);

    /*  Filling the paramEntry for param 0 */
    paramEntry0.srcPtr     = srcPtr;
    paramEntry0.destPtr    = dstPtr;
    paramEntry0.aCnt       = CDD_DMA_TEST_A_COUNT;
    paramEntry0.bCnt       = CDD_DMA_TEST_B_COUNT;
    paramEntry0.cCnt       = CDD_DMA_TEST_C_COUNT;
    paramEntry0.bCntReload = CDD_DMA_TEST_B_COUNT;
    paramEntry0.srcBIdx    = CDD_DMA_TEST_A_COUNT;
    paramEntry0.destBIdx   = CDD_DMA_TEST_A_COUNT;
    paramEntry0.srcCIdx    = CDD_DMA_TEST_A_COUNT;
    paramEntry0.destCIdx   = CDD_DMA_TEST_A_COUNT;
    paramEntry0.opt        = opt;

    Cdd_Dma_ParamSet(handleId, 0, 0, paramEntry0);
    void *appdata = (void *)&Cdd_Dma_TestDoneSem;
    /* Registering the callback */
    Cdd_Dma_CbkRegister(handleId, appdata, &Cdd_Dma_RegionIsrFxn);
    /*
     * Transfer is done in A sync mode
     * Number of triggers required are B_COUNT * C_COUNT
     */
    for (uint32 count = 0; count < (CDD_DMA_TEST_B_COUNT * CDD_DMA_TEST_C_COUNT); count++)
    {
        /* Initiate the trigger */
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
    Cdd_Dma_InterruptModeApp_Startup();

    Cdd_Dma_App_PlatformInit();

    Mcal_CacheP_init();
    Cdd_Dma_InterruptConfig();

    AppUtils_printf("DmaInterruptModeApp: Sample Application - STARTS !!!\n\r ");

    Cdd_Dma_InterruptModeApp_mainTest();
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
