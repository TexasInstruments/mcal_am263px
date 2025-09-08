/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     fsirxpp.c
 *
 *  \brief    This file contains the FsiRx  test example
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_NOANALYSIS*/
#include "string.h"
/*LDRA_ANALYSIS*/
#include "assert.h"
#include "SchM_Port.h"
#include "Det.h"
#include "Dem.h"

#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port_Cfg.h"
#include "Port.h"
#if CDD_FSI_RX_DMA_ENABLE == STD_ON
#include "Cdd_Dma.h"
#endif
#include "fsirxapp.h"
#include "fsirxapp_Startup.h"
#include "Cdd_FsiTx_Cfg.h"
#include "Cdd_FsiTx.h"
#include "Cdd_FsiTx_Irq.h"
#include "Cdd_FsiRx_Cfg.h"
#include "Cdd_FsiRx.h"
#include "Cdd_FsiRx_Irq.h"

#include "app_utils.h"
#include "sys_common.h"

#include "trace.h"
#include "sys_vim.h"

/* For PRCM base addresses */
#include "soc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Macros to Enable CDD FSI Application Test  */
#define CDD_FSI_APPL_TEST STD_ON
#define ARRAYSIZE(x)      (sizeof((x)) / sizeof((x)[0]))
/*Cdd_FsiTx_StatusType Cdd_FsiTx_DriverStatus;*/
uint32 gTestPassed = E_OK;
uint32 testPassed  = E_OK;
extern volatile VAR(Cdd_FsiTx_PingTagType, CDD_VAR_PING) Cdd_FsiTx_PingStatus;
volatile uint8 Cdd_Fsi_isDataReceived = E_NOT_OK;
volatile uint8 Cdd_Fsi_isDataSent     = E_NOT_OK;

Std_ReturnType Cdd_Fsi_bufferstatus   = E_NOT_OK;
Std_ReturnType Cdd_Fsi_transmitstatus = E_NOT_OK;
Std_ReturnType Cdd_Fsi_receivestatus  = E_NOT_OK;
Std_ReturnType Cdd_Fsi_PingStatus     = E_NOT_OK;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef void (*CddFsiAppFxn_t)(void);

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static void Cdd_FsiRxApp_mainTest(void);
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

uint16 SrcPtr[80] = {
    0xAAAA, 0xBBBB, 0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF, 0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777,
    0x8888, 0x9999, 0x1122, /*First 16 words*/
    0x3344, 0x5566, 0x7788, 0x99AA, 0x1234, 0x5678, 0x9ABC, 0xDEF1, 0x2345, 0x6789, 0xABCD, 0xEF12, 0x3456,
    0x789A, 0xBCDE, 0xF123, 0x4567, 0x89AB, 0xCDEF, 0x1122, 0x3344, 0x5566, 0x7788, 0x99AA, 0x1234, 0x5678,
    0x9ABC, 0xDEF1, 0x2345, 0x6789, 0xABCD, 0xEF12, 0x3456, 0x789A, 0xBCDE, 0xF123, 0x4567, 0x89AB, 0xCDEF,
    0x1122, 0x3344, 0x5566, 0x7788, 0x99AA, 0x1234, 0x5678, 0x9ABC, 0xDEF1, 0x2345, 0x6789, 0xABCD, 0xEF12,
    0x3456, 0x789A, 0xBCDE, 0xF123, 0x4567, 0x89AB, 0xCDEF, 0x1122, 0x3344, 0x5566, 0x7788, 0x99AA,
};
uint16         DstBffr[80];
volatile uint8 Cdd_FsiTx_userdata = 0x3F;
uint8          Cdd_Fsi_txCount, Cdd_Fsi_rxCount = 0;
#if (CDD_FSI_TX_VARIANT_POST_COMPILE == STD_ON)
extern const Cdd_FsiTx_ConfigType *Cdd_FsiTx_ConfigPtr;
#endif
#if (CDD_FSI_RX_VARIANT_POST_COMPILE == STD_ON)
extern const Cdd_FsiRx_ConfigType *Cdd_FsiRx_ConfigPtr;
#endif
VAR(uint32, CDD_FSIRX_APPL_DATA)
Cdd_Fsi_rxbase;
volatile uint8 Cdd_Fsi_array_index = 0;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) Mcu_Config;
#endif

CddFsiAppFxn_t CddFsiAppFxnTbl[] = {&Cdd_FsiRxApp_mainTest};

void Cdd_FsiRxApp_ResetNotification(Cdd_FsiRx_HWUnitType hwUnitId)
{
    AppUtils_printf(CDD_FSI_APP_NAME ": Rx and Tx drivers have to undergo reset\n\r");
}
void Cdd_FsiRxApp_OverrunNotification(Cdd_FsiTx_HWUnitType hwUnitId)
{
    AppUtils_printf(CDD_FSI_APP_NAME ": A buffer over run occured in Rx Buffer and there is no data to read\n\r");
}

void Cdd_FsiTxApp_Notification(Cdd_FsiTx_HWUnitType hwUnitId)
{
    Cdd_Fsi_isDataSent = E_OK;
}

void Cdd_FsiTxApp_OverRunNotification(Cdd_FsiTx_HWUnitType hwUnitId)
{
    AppUtils_printf(CDD_FSI_APP_NAME ": A buffer over run occured in Tx Buffer and there is no data to read\n\r");
    AppUtils_printf(CDD_FSI_APP_NAME ": Rx and Tx drivers have to undergo reset\n\r");
}

void Cdd_FsiTxApp_UnderRunNotification(Cdd_FsiTx_HWUnitType hwUnitId)
{
    AppUtils_printf(CDD_FSI_APP_NAME ": A buffer under run occured in Tx Buffer and there is no data to read\n\r");
    AppUtils_printf(CDD_FSI_APP_NAME ": Rx and Tx drivers have to undergo reset\n\r");
}

void Cdd_FsiRxApp_UnderrunNotification(Cdd_FsiRx_HWUnitType hwUnitId)
{
    AppUtils_printf(CDD_FSI_APP_NAME ": A buffer under run occured in Rx Buffer and there is no data to read\n\r");
}

void Cdd_FsiRxApp_PingReceivedNotification(Cdd_FsiRx_HWUnitType hwUnitId)
{
    if (Cdd_FsiTx_PingStatus == CDD_FSI_TX_PING_TAG0)
    {
        Cdd_FsiTx_Ping(hwUnitId);
    }
    else if (Cdd_FsiTx_PingStatus == CDD_FSI_TX_PING_TAG1)
    {
        Cdd_FsiTx_PingStatus = CDD_FSI_TX_PING_COMPLETED;
    }
}

void Cdd_FsiRxApp_dataReceivedNotification(Cdd_FsiRx_HWUnitType hwUnitId)
{
    Cdd_Fsi_isDataReceived = E_OK;
}

/* Entry point of example */
int main(void)
{
    uint8 index = 0;
    Cdd_FsiRxApp_Startup();
    /* Initilize the timer. */
    AppUtils_TimerInit();
    AppUtils_printf(CDD_FSI_APP_NAME "\n\r: Sample Application - STARTS !!!\n\r");
    for (index = 0U; index < ARRAYSIZE(CddFsiAppFxnTbl); index++)
    {
        CddFsiAppFxnTbl[index]();
    }

    GT_1trace(McalAppTrace, GT_INFO, " FSI Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(McalAppTrace, GT_ERR, " FSI Stack/section corruption!!!\n\r");
    }
    AppUtils_TimerDeinit();

    if (E_OK == gTestPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, "All tests have passed\n");
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, "Some tests have failed\n");
    }

    AppUtils_printf(CDD_FSI_APP_NAME ": Sample Application - Completed. !!!\n\r");

    return (0);
}

static void Cdd_FsiRxApp_mainTest(void)
{
    Cdd_FsiTx_StatusType status;
    CddFsiRx_StatusType  rxstatus;

#if (CDD_FSI_TX_VARIANT_POST_BUILD == STD_ON)
    const Cdd_FsiTx_ConfigType *Cdd_FsiTx_ConfigPtr = &Cdd_FsiTx_Config;
    /*Cdd_FsiTx_ConfigPtr->hwUnitCfg->srcbuffer = &SrcPtr;*/
#endif
#if (CDD_FSI_RX_VARIANT_POST_BUILD == STD_ON)
    const Cdd_FsiRx_ConfigType *Cdd_FsiRx_ConfigPtr = &Cdd_FsiRx_Config;
    Cdd_Fsi_rxbase = Cdd_FsiRx_ConfigPtr->hwUnitCfg[CDD_FSI_RX_HWUNIT_INSTANCE_IDX].baseAddr;
#endif
#if (STD_ON == CDD_FSI_TX_DMA_MODE)
    Cdd_Dma_Init(NULL_PTR);
#endif

/* Init */
#if (CDD_FSI_RX_VARIANT_PRE_COMPILE == STD_ON)
    /* Initialize the CDD FsiRx module. */
    Cdd_Fsi_rxbase = CDD_FSI_APP_BASE;
    Cdd_FsiRx_Init(NULL_PTR);
    /* CDD FSI TX driver should be free now - check */
#endif
    /* CDD FSI TX driver should be free now - check */
#if (CDD_FSI_TX_VARIANT_PRE_COMPILE == STD_ON)
    /* Initialize the CDD FsiTx module. */
    Cdd_FsiTx_Init(NULL_PTR);
#endif

    /* CDD FSI TX driver should be free now - check */
    Cdd_FsiRxApp_enableRxInternalLoopback(Cdd_Fsi_rxbase);

#if (CDD_FSI_RX_VARIANT_POST_BUILD == STD_ON)
    /* Initialize the CDD FsiRx module. */
    Cdd_FsiRx_Init(Cdd_FsiRx_ConfigPtr);
#endif
#if (CDD_FSI_TX_VARIANT_POST_BUILD == STD_ON)
    /* Initialize the CDD FsiTx module. */
    Cdd_FsiTx_Init(Cdd_FsiTx_ConfigPtr);
#endif

    Cdd_FsiRxApp_interruptInit();
#if (CDD_FSI_TX_GET_VERSION_INFO == STD_ON)
    /* Get and print version */
    Std_VersionInfoType versioninfo;
    Cdd_FsiTx_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n");
    AppUtils_printf("Cdd Fsi Tx driver Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf("Vendor ID           : %d\n\r", versioninfo.vendorID);
    AppUtils_printf("Module ID           : %d\n\r", versioninfo.moduleID);
    AppUtils_printf("SW Major Version    : %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf("SW Minor Version    : %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf("SW Patch Version    : %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n");
#endif /* #if (CDD_FSI_TX_VERSION_INFO_API == STD_ON) */

    status   = CddFsiTx_GetStatus();
    rxstatus = CddFsiRx_GetStatus();
    if (status != CDD_FSI_TX_INIT || rxstatus != CDD_FSI_RX_INIT)
    {
        testPassed = E_NOT_OK;
        AppUtils_printf(CDD_FSI_APP_NAME ": CDD Fsi driver is not initialized!!\n\r");
    }
    else
    {
        if ((Cdd_FsiTx_Config.hwUnitCfg->transmitMode == CDD_FSI_TX_INTERRUPT_MODE) &&
            (Cdd_FsiRx_Config.hwUnitCfg->receptionMode == CDD_FSI_RX_INTERRUPT_MODE))
        {
            Cdd_Fsi_isDataReceived = E_NOT_OK;
            Cdd_Fsi_isDataSent     = E_NOT_OK;
            Cdd_Fsi_PingStatus     = Cdd_FsiTx_Ping(CDD_FSI_TX_HWUNIT_INSTANCE_IDX);
            AppUtils_printf(CDD_FSI_APP_NAME ": Ping Frame Transmission completed!!\n\r");
            for (uint8 count = 0; count < 5; count++)
            {
                Cdd_Fsi_bufferstatus =
                    Cdd_FsiTx_BufferLoad(CDD_FSI_TX_HWUNIT_INSTANCE_IDX, &SrcPtr[Cdd_Fsi_array_index],
                                         Cdd_FsiTx_userdata, CDD_FSI_TX_BUFF_SIZE_16_WORD_LENGTH);

                if (Cdd_Fsi_bufferstatus == E_OK)
                {
                    Cdd_FsiRx_setUpBuffer(CDD_FSI_RX_HWUNIT_INSTANCE_IDX, &DstBffr[0], CDD_FSI_RX_DATA_16_WORD_LENGTH);
                    AppUtils_delay(200U);
                    Cdd_Fsi_transmitstatus = Cdd_FsiTx_Transmit(CDD_FSI_TX_HWUNIT_INSTANCE_IDX, Cdd_FsiTx_userdata,
                                                                CDD_FSI_TX_DATA_16_WORD_LENGTH);

                    while (Cdd_Fsi_isDataSent == E_NOT_OK)
                    {
                        ; /* wait untill data sent*/
                    }
                    Cdd_Fsi_txCount++;
                }

                if (Cdd_Fsi_transmitstatus != E_OK)
                {
                    AppUtils_printf(CDD_FSI_APP_NAME ": Data frame transmission failed\n\r");
                    return;
                }
                else
                {
                    while (Cdd_Fsi_isDataReceived == E_NOT_OK)
                    {
                        ; /* wait untill data sent*/
                    }

                    AppUtils_printf(CDD_FSI_APP_NAME ": Frame %d reception completed!!\n\r", count + 1);
                    Cdd_Fsi_rxCount++;
                    Cdd_Fsi_array_index = Cdd_Fsi_array_index + CDD_FSI_TX_DATA_16_WORD_LENGTH + 1;
                }
            }
        }

        if (Cdd_Fsi_txCount == Cdd_Fsi_rxCount)
        {
            AppUtils_printf(CDD_FSI_APP_NAME ": All frames received!!\n\r");
            Cdd_FsiTx_DeInit();
            Cdd_FsiRx_DeInit();

            AppUtils_printf(CDD_FSI_APP_NAME ": Cdd Fsi driver de initialized!!\n\r");
        }
    }
}
#if defined CLANG
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

void SchM_Enter_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Dma_DMA_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void SchM_Enter_Cdd_FsiTx_FSI_TX_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_FsiTx_FSI_TX_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
void SchM_Enter_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

void App_disable(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void App_restore(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

/*****************************************EoF******************************************************/
