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
 *  \file     FlsApp.c
 *
 *  \brief    This file contains the FLS test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Det.h"
#include "Fls.h"
#include "Fls_Irq.h"
#include "Fls_Brd_Nor.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Port_Cfg.h"
#include "Port.h"
/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "trace.h"
#include "FlsApp_Startup.h"
#include "CacheP.h"

/* Starterware Includes */
#include "sys_vim.h"
#include "app_utils.h"
#include "soc.h"
#include "hw_ctrl_core.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))
#define APP_NAME     "FLS_APP"
#define SECTOR_ERASE                                                                             \
    (1)                 /* This macro should be (1) if sector erase application is needed to run \
                         */
#define BLOCK_ERASE (0) /* This macro should be (1) if block erase application is needed to run */
#define CHIP_ERASE  (0) /* This macro should be (1) if bulk/chip erase application is needed to run */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void            FlsApp_Startup(void);
void            main_handling(void);
void            main_handling_intr(void);
uint8           fls_sampleapp(void);
uint8           fls_sampleapp_configinput(void);
uint32          Fls_TestPassed;
volatile uint32 Fls_JobDoneSuccess;
volatile uint32 Fls_JobDoneError;
uint16          test_forloop = 0;
uint32          Data_Size_Test;
uint32          Data_Value;
uint32          numOfSectorsOrBlocks;
uint32          CfgSectorOrBlockSize;
uint32          numofseccfg;
uint32          offset;
uint32          Total_datasize;
uint32          type_of_erase;
extern uint32   sector_or_blocksize;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define FLSEXAMPLE_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))
#define DATA_SIZE_TEST          64 * 1024

extern FlashConfigSfdp *fls_config_sfdp;
#if (STD_ON == FLS_VERSION_INFO_API)
Std_VersionInfoType VersionInfo;
#endif

Std_ReturnType retVal = E_OK;
/* Buffer containing the known data that needs to be written to flash */
uint8          txBuf_test[DATA_SIZE_TEST] = {0};
/* Buffer containing the received data */
uint8          rxBuf_test[DATA_SIZE_TEST] = {0};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    FlsApp_Startup();
#if defined(AM263PX_PLATFORM)
#if defined AM263PX_R_PACKAGE || defined AM263PX_C_PACKAGE
#if (STD_OFF == CDD_I2C_POLLING_MODE)
    Cdd_I2c_InterruptConfig();
#endif  // #if(STD_OFF == CDD_I2C_POLLING_MODE)
    Cdd_I2c_Init(NULL_PTR);
    board_flash_reset();
#endif                        // #if defined AM263PX_R_PACKAGE || defined AM263PX_C_PACKAGE
#endif                        // if defined(AM263PX_PLATFORM)
    Flash_sfdpParams_init();  // initialise sfdp parameters

    if (SECTOR_ERASE == 1)
    {
        offset              = 0x000000U;
        Data_Value          = 0xAA;
        Data_Size_Test      = fls_config_sfdp->eraseCfg.sectorSize;
        type_of_erase       = FLS_SECTOR_ERASE;
        sector_or_blocksize = Fls_SetEraseType(FLS_SECTOR_ERASE);
        fls_sampleapp_configinput();
    }
    if (BLOCK_ERASE == 1)
    {
        offset              = 0x000000U;
        Data_Value          = 0xBB;
        Data_Size_Test      = fls_config_sfdp->eraseCfg.blockSize;
        type_of_erase       = FLS_BLOCK_ERASE;
        sector_or_blocksize = Fls_SetEraseType(FLS_BLOCK_ERASE);
        fls_sampleapp_configinput();
    }
    if (CHIP_ERASE == 1)
    {
        offset              = 0x000000U;
        Data_Value          = 0xCC;
        Data_Size_Test      = fls_config_sfdp->flashSize;
        type_of_erase       = FLS_CHIP_ERASE;
        sector_or_blocksize = Fls_SetEraseType(FLS_CHIP_ERASE);
        fls_sampleapp_configinput();
    }
    AppUtils_TimerDeinit();
    return (0);
}

uint8 fls_sampleapp_configinput(void)
{
    Std_ReturnType job_accepted = E_OK;
#if (STD_ON == FLS_GET_JOB_RESULT_API)
    MemIf_JobResultType Result_type;
#endif
    AppUtils_printf("FlsApp: Sample Application - STARTS !!!\n\r");
#if (STD_ON == FLS_DMA_ENABLE)
    Cdd_Dma_Init(NULL_PTR);
#endif
#if (STD_ON == FLS_USE_INTERRUPTS)
    AppUtils_printf(APP_NAME ": Configuring Interrupt.\n\r");
#endif /* #if (STD_ON == FLS_USE_INTERRUPTS) */

#if (STD_ON == FLS_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n\r");
    Fls_Init((const Fls_ConfigType *)NULL_PTR);
#else
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
    Fls_Init(&FlsConfigSet);
#endif /* #if (STD_ON == FLS_PRE_COMPILE_VARIANT) */

#if (STD_ON == FLS_VERSION_INFO_API)
    Fls_GetVersionInfo(&VersionInfo);
    AppUtils_printf("FLS MCAL version info:%d.%d.%d\n\r", VersionInfo.sw_major_version, VersionInfo.sw_minor_version,
                    VersionInfo.sw_patch_version);
    AppUtils_printf("FLS MCAL Module/Driver:%d.%d \n\r", VersionInfo.moduleID, VersionInfo.vendorID);
#endif /* #if (STD_ON == FLS_VERSION_INFO_API) */

/* FLS driver should be free now - check */
#if (STD_ON == FLS_GET_STATUS_API)
    MemIf_StatusType status;
    status = Fls_GetStatus();
    if (status != MEMIF_IDLE)
    {
        AppUtils_printf(APP_NAME ": FLS driver is not IDLE!!\n\r");
    }
#endif /* #if ( STD_ON == FLS_GET_STATUS_API) */

    for (numofseccfg = 0; numofseccfg < FLS_NUMBER_OF_SECTOR_CFG; numofseccfg++)
    {
        offset               = FlsConfigSet.sectorList[numofseccfg].sectorStartaddress - FLS_BASE_ADDRESS;
        CfgSectorOrBlockSize = FlsConfigSet.sectorList[numofseccfg].sectorSize;
        numOfSectorsOrBlocks = FlsConfigSet.sectorList[numofseccfg].numberOfSectors;
        /* Make sure to call "Fls_SetEraseType" function with parameter as per the sectorsize
         * configuration done in sectorlist*/
        /*FLS_SECTOR_ERASE to be passed for sectorsize = 4096, FLS_BLOCK_ERASE for sectorsize =
         * 65536 and FLS_CHIP_ERASE to erase full chip at once*/
#if (STD_ON == FLS_MEM_MAP_MODE)
        if (offset >= 0x800000)
        {
            AppUtils_printf(APP_NAME
                            ":Please configure MEMMAP MODE = OFF to access address beyond 8 "
                            "MB...exiting..\n\r");
            break;
        }
#endif
        Total_datasize = numOfSectorsOrBlocks * CfgSectorOrBlockSize;

        AppUtils_printf(APP_NAME ":Executing Sector configuration number :  %d \n\r", numofseccfg + 1);
        AppUtils_printf(APP_NAME ":Number of sector/blocks to erase/read/write: %d \n\r", numOfSectorsOrBlocks);
        AppUtils_printf(APP_NAME ":Total data size: 0x%X \n\r", Total_datasize);
        AppUtils_printf(APP_NAME ":Offset is 0x%X \n\r", offset);

        volatile uint32 idx;
        volatile uint8 *txPtr_test = txBuf_test;
        volatile uint8 *rxPtr_test = rxBuf_test;

        for (idx = 0U; idx < Total_datasize; idx++)
        {
            *txPtr_test++ = idx % 255;
            *rxPtr_test++ = (uint8)0U;
        }

        AppUtils_printf(APP_NAME ": Erasing \n\r");

        while (1U)
        {
            job_accepted = Fls_Erase(offset, Total_datasize);
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

#if (STD_ON == FLS_GET_JOB_RESULT_API)
        Result_type = Fls_GetJobResult();
        if (Result_type != MEMIF_JOB_OK)
        {
            AppUtils_printf(APP_NAME ": Get Job Result Failed\n\r");
        }
#endif /*( STD_ON == FLS_GET_JOB_RESULT_API)*/

#if (STD_ON == FLS_BLANK_CHECK_API)
        AppUtils_printf(APP_NAME ": Blank Checking \n\r");
        while (1U)
        {
            job_accepted = Fls_BlankCheck(offset, Total_datasize);
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
#endif /*STD_ON == FLS_BLANK_CHECK_API*/

        AppUtils_printf(APP_NAME ": Writing \n\r");
        while (1U)
        {
            job_accepted = Fls_Write(offset, &txBuf_test[0], Total_datasize);
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

        AppUtils_printf(APP_NAME ": Reading \n\r");
#if (STD_ON == FLS_DMA_ENABLE)
        Mcal_CacheP_wb(rxBuf_test, Total_datasize, Mcal_CacheP_TYPE_ALL);
#endif
        while (1U)
        {
            job_accepted = Fls_Read(offset, &rxBuf_test[0], Total_datasize);
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

#if (STD_ON == FLS_DMA_ENABLE)
        // Mcal_CacheP_inv(rxBuf_test, Total_datasize, Mcal_CacheP_TYPE_ALL);
#endif

#if (STD_ON == FLS_COMPARE_API)
        AppUtils_printf(APP_NAME ": Write Compare \n\r");
        while (1U)
        {
            /*
            Check if the write operation was successful by comparing txBuf_test (hardcoded)
            with the actual data in flash
            */
            job_accepted = Fls_Compare(offset, &txBuf_test[0], Total_datasize);
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

        AppUtils_printf(APP_NAME ": Read Compare \n\r");
        while (1U)
        {
            /*
            Check if the read operation was successful by comparing rxBuf_test (previously read)
            with the actual data in flash
            */
            job_accepted = Fls_Compare(offset, &rxBuf_test[0], Total_datasize);
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

#endif /*STD_ON == FLS_COMPARE_API*/
#if (STD_ON == FLS_CANCEL_API)
        AppUtils_printf(APP_NAME ": \n\r");
        AppUtils_printf(APP_NAME ": Job Cancel \n\r");
        AppUtils_printf(APP_NAME ": \t 1. Writing \n\r");
        while (1U)
        {
            job_accepted = Fls_Write(offset, &txBuf_test[0], Total_datasize);
            if (E_OK == job_accepted)
            {
                break;
            }
        }
        AppUtils_printf(APP_NAME ": \t 2. Canceling \n\r");
        Fls_Cancel();
        if (Fls_JobDoneError == 1)
        {
            AppUtils_printf(APP_NAME ": Job Canceled (SUCCESS) ! \n\r");
        }
        else
        {
            AppUtils_printf(APP_NAME ": Job completed (FAILED) !! \n\r");
            while (1)
            {
            }
        }
        Fls_JobDoneError = 0;
        AppUtils_printf(APP_NAME ": \n\r");
#endif /*STD_ON == FLS_CANCEL_API*/
        AppUtils_printf(APP_NAME ": \n\r");
        AppUtils_printf(APP_NAME ": ---------- FLS Sample application Done !! ----------  \n\r");
        AppUtils_printf(APP_NAME ": \n\r");
        AppUtils_printf("All tests have passed\n\r");
    }

    return (0);
}
void SchM_Enter_Fls_FLS_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Fls_FLS_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
void SchM_Enter_Mcu_MCU_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Mcu_MCU_EXCLUSIVE_AREA_0()
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
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    Fls_TestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (E_OK);
}
Std_ReturnType Det_ReportRuntimeError(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId,
                                      VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId)
{
    Fls_TestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (E_OK);
}
Std_ReturnType Det_ReportTransientFault(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId,
                                        VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) FaultId)
{
    Fls_TestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (E_OK);
}
void Fee_JobEndNotification(void)
{
    Fls_JobDoneSuccess = 1U;
}

void Fee_JobErrorNotification(void)
{
    Fls_JobDoneError = 1U;
}
void main_handling()
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
void main_handling_intr()
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

#if (STD_ON == FLS_DMA_ENABLE)
void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
#endif
