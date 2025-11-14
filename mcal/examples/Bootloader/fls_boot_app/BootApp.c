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
 *  \file     BootApp.c
 *
 *  \brief    This file contains the MCAL Bootloader
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
#if defined(AM263PX_PLATFORM)
#include "app_utilsI2c.h"
#endif

#include "bootloader.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))

/* This macro should be (1) if sector erase application is needed to run */
#define SECTOR_ERASE (1)
/* This macro should be (1) if block erase application is needed to run */
#define BLOCK_ERASE (0)
/* This macro should be (1) if bulk/chip erase application is needed to run */
#define CHIP_ERASE (0)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

void          FlsApp_Startup(void);
void          main_handling(void);
uint8         fls_sampleapp(void);
uint32        Fls_TestPassed;
uint16        test_forloop = 0;
uint32        Data_Size_Test;
uint32        Data_Value;
uint32        numOfSectorsOrBlocks;
uint32        CfgSectorOrBlockSize;
uint32        numofseccfg;
uint32        offset;
uint32        Total_datasize;
uint32        type_of_erase;
extern uint32 sector_or_blocksize;

/* BOOTLOADER Instance Macros */
#define CONFIG_BOOTLOADER0              (0U)
#define CONFIG_BOOTLOADER_NUM_INSTANCES (1U)
#define CONFIG_FLASH0                   (0U)

/* Bootloader boot media specific arguments */
Bootloader_FlashArgs gBootloader0Args = {
    .flashIndex     = CONFIG_FLASH0,
    .curOffset      = 0,
    .appImageOffset = 0x000C0000,
};

/* Configuration option for lockstep or standalone */
Bootloader_socCoreOpModeConfig operatingMode = {
    BOOTLOADER_OPMODE_LOCKSTEP,
    BOOTLOADER_OPMODE_LOCKSTEP,
};

/* Bootloader driver configuration */
Bootloader_Config gBootloaderConfig[CONFIG_BOOTLOADER_NUM_INSTANCES] = {
    {
        &gBootloaderFlashFxns,
        &gBootloader0Args,
        BOOTLOADER_MEDIA_FLASH,
        0,
        0,
        NULL,

        .socCoreOpMode       = (void *)&operatingMode,
        .isAppimageSigned    = FALSE,
        .disableAppImageAuth = FALSE,
        .initICSSCores       = FALSE,
        0,
    },
};

uint32_t gBootloaderConfigNum = CONFIG_BOOTLOADER_NUM_INSTANCES;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define FLSEXAMPLE_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))
#define DATA_SIZE_TEST          64 * 1024

#if (STD_ON == FLS_VERSION_INFO_API)
Std_VersionInfoType VersionInfo;
#endif

/* Buffer containing the known data that needs to be written to flash */
uint8 txBuf_test[DATA_SIZE_TEST] = {0};
/* Buffer containing the received data */
uint8 rxBuf_test[DATA_SIZE_TEST] = {0};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    FlsApp_Startup();
#if defined(AM263PX_PLATFORM)
#if defined AM263PX_R_PACKAGE || defined AM263PX_C_PACKAGE
    I2c_utilsInterruptConfig();
    Cdd_I2c_Init(NULL_PTR);
    board_flash_reset();
#endif  // #if defined AM263PX_R_PACKAGE || defined AM263PX_C_PACKAGE
#endif  // if defined(AM263PX_PLATFORM)

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
    Fls_Init(&Fls_Config);
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

    Bootloader_BootImageInfo bootImageInfo;
    Bootloader_Params        bootParams;
    Bootloader_Handle        bootHandle;

    Bootloader_Params_init(&bootParams);
    Bootloader_BootImageInfo_init(&bootImageInfo);

    bootHandle = Bootloader_open(CONFIG_BOOTLOADER0, &bootParams);

    if (bootHandle != NULL)
    {
        status = Bootloader_parseAndLoadMultiCoreELF(bootHandle, &bootImageInfo);
        if (status == SystemP_SUCCESS)
        {
            AppUtils_printf(APP_NAME ": Parsing OK!!\n\r");
        }
        else
        {
            AppUtils_printf(APP_NAME ": Parsing Failed!!\n\r");
            status = SystemP_SUCCESS;
        }

        /* Run CPUs */
        if (status == SystemP_SUCCESS && (TRUE == Bootloader_isCorePresent(bootHandle, MCAL_CSL_CORE_ID_R5FSS1_1)))
        {
            status = Bootloader_runCpu(bootHandle, &bootImageInfo.cpuInfo[MCAL_CSL_CORE_ID_R5FSS1_1]);
        }
        if (status == SystemP_SUCCESS && (TRUE == Bootloader_isCorePresent(bootHandle, MCAL_CSL_CORE_ID_R5FSS1_0)))
        {
            status = Bootloader_runCpu(bootHandle, &bootImageInfo.cpuInfo[MCAL_CSL_CORE_ID_R5FSS1_0]);
        }
        if (status == SystemP_SUCCESS && (TRUE == Bootloader_isCorePresent(bootHandle, MCAL_CSL_CORE_ID_R5FSS0_1)))
        {
            status = Bootloader_runCpu(bootHandle, &bootImageInfo.cpuInfo[MCAL_CSL_CORE_ID_R5FSS0_1]);
        }
        if (status == SystemP_SUCCESS)
        {
            AppUtils_printf(APP_NAME "Image loading done, switching to application ...\r\n");
            status = Bootloader_runSelfCpu(bootHandle, &bootImageInfo);
        }
        /* it should not return here, if it does, then there was some error */
        Bootloader_close(bootHandle);
    }

    AppUtils_TimerDeinit();
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
