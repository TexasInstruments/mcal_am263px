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
 *  \file     FlsXipApp.c
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
#include "FlsXipApp_Startup.h"
#include "CacheP.h"

/* Starterware Includes */
#include "sys_vim.h"
#include "app_utils.h"
#include "soc.h"
#include "hw_ctrl_core.h"
#if defined(AM263PX_PLATFORM)
#include "app_utilsI2c.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0]))
#define APP_NAME     "FLS_XIP_APP"
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
#define APP_BUF_SIZE            (256U)

#if (STD_ON == FLS_VERSION_INFO_API)
Std_VersionInfoType VersionInfo;
#endif

Std_ReturnType retVal = E_OK;
/* Buffer containing the known data that needs to be written to flash */
uint8          txBuf_test[DATA_SIZE_TEST] = {0};
/* Buffer containing the received data */
uint8          rxBuf_test[DATA_SIZE_TEST] = {0};
uint32_t       gAppCrcBuf[APP_BUF_SIZE];
void           ospi_flash_xip_crc_test(void) __attribute__((section(".text.ospi_flash_xip_crc_test"), used));
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static const uint16_t crc16tab[APP_BUF_SIZE] __attribute__((aligned(128), section(".rodata.crc"))) = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad,
    0xe1ce, 0xf1ef, 0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 0x9339, 0x8318, 0xb37b, 0xa35a,
    0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a, 0xb54b,
    0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
    0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861,
    0x2802, 0x3823, 0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96,
    0x1a71, 0x0a50, 0x3a33, 0x2a12, 0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 0x6ca6, 0x7c87,
    0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
    0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a,
    0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1, 0x30c2, 0x20e3,
    0x5004, 0x4025, 0x7046, 0x6067, 0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 0x02b1, 0x1290,
    0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
    0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e,
    0xc71d, 0xd73c, 0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 0xd94c, 0xc96d, 0xf90e, 0xe92f,
    0x99c8, 0x89e9, 0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c,
    0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
    0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83,
    0x1ce0, 0x0cc1, 0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 0x6e17, 0x7e36, 0x4e55, 0x5e74,
    0x2e93, 0x3eb2, 0x0ed1, 0x1ef0};

uint16_t crc16_ccitt(const void *buf, int len)
{
    int32_t  counter;
    uint16_t crc = 0;
    for (counter = 0; counter < len; counter++)
    {
        crc = (crc << 8) ^ crc16tab[((crc >> 8) ^ *(char *)buf) & 0x00FF];
        buf = (char *)buf + 1;
    }

    return crc;
}

void ospi_flash_xip_crc_test(void)
{
    AppUtils_printf("Executing function from FLASH!!!\r\n");

    uint32_t i;
    for (i = 0; i < APP_BUF_SIZE; i++)
    {
        gAppCrcBuf[i] = 2 * i;
    }

    AppUtils_printf("CRC Value: %d\r\n", crc16_ccitt(gAppCrcBuf, APP_BUF_SIZE));

}

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

    if (SECTOR_ERASE == 1)
    {
        offset              = 0x000000U;
        Data_Value          = 0xAA;
        Data_Size_Test      = Fls_Config_SFDP_Ptr->eraseCfg.sectorSize;
        type_of_erase       = FLS_SECTOR_ERASE;
        sector_or_blocksize = Fls_SetEraseType(FLS_SECTOR_ERASE);
        fls_sampleapp_configinput();
    }
    if (BLOCK_ERASE == 1)
    {
        offset              = 0x000000U;
        Data_Value          = 0xBB;
        Data_Size_Test      = Fls_Config_SFDP_Ptr->eraseCfg.blockSize;
        type_of_erase       = FLS_BLOCK_ERASE;
        sector_or_blocksize = Fls_SetEraseType(FLS_BLOCK_ERASE);
        fls_sampleapp_configinput();
    }
    if (CHIP_ERASE == 1)
    {
        offset              = 0x000000U;
        Data_Value          = 0xCC;
        Data_Size_Test      = Fls_Config_SFDP_Ptr->flashSize;
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
    Fls_Init(&Fls_Config);
#endif /* #if (STD_ON == FLS_PRE_COMPILE_VARIANT) */

#if (STD_ON == FLS_VERSION_INFO_API)
    Fls_GetVersionInfo(&VersionInfo);
    AppUtils_printf("FLS MCAL version info:%d.%d.%d\n\r", VersionInfo.sw_major_version, VersionInfo.sw_minor_version,
                    VersionInfo.sw_patch_version);
    AppUtils_printf("FLS MCAL Module/Driver:%d.%d \n\r", VersionInfo.moduleID, VersionInfo.vendorID);
#endif /* #if (STD_ON == FLS_VERSION_INFO_API) */

    /* Running the XIP Functions */
    ospi_flash_xip_crc_test();

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
        offset               = Fls_Config.sectorList[numofseccfg].sectorStartaddress - FLS_BASE_ADDRESS;
        CfgSectorOrBlockSize = Fls_Config.sectorList[numofseccfg].sectorSize;
        numOfSectorsOrBlocks = Fls_Config.sectorList[numofseccfg].numberOfSectors;
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

        ospi_flash_xip_crc_test();

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
