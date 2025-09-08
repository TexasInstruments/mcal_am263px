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
 *  \file     LinApp.c
 *
 *  \brief    This file contains the Lin test example
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "assert.h"
/*LDRA_NOANALYSIS*/
#include "string.h"
#include "Det.h"
#include "Dem.h"
#include "Std_Types.h"
#include "Os.h"
/*LDRA_ANALYSIS*/
#include "Lin_Cfg.h"
#include "sys_common.h"
#include "trace.h"
#include "hal_stdtypes.h"
#include "soc.h"
#include "LinApp.h"
#include "LinApp_Startup.h"

/**
 *  \anchor LIN_ParityIDMasks
 *  \name   Lin Parity ID Masks
 *
 *  Note: Parity ID Masks for LIN
 *
 *  @{
 */
#define LIN_ID0 (0x1U)
#define LIN_ID1 (0x2U)
#define LIN_ID2 (0x4U)
#define LIN_ID3 (0x8U)
#define LIN_ID4 (0x10U)
#define LIN_ID5 (0x20U)
/** @} */

Std_VersionInfoType VersionInfo;
Std_ReturnType      returnValue = E_NOT_OK;
uint8               txData[8]   = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
uint8*              rxBuff;
uint8**             rxData = &rxBuff;
Lin_PduType         txPdu;
uint8               loop;
uint8               temp;
char                user_input;
boolean             test_run = TRUE;

/*Notification function definitions*/
void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    while (1)
        ;
}

static inline Lin_FramePidType Lin_GenerateParityID(Lin_FramePidType identifier)
{
    Lin_FramePidType p0, p1, parityIdentifier;

    /* Calculate parity bits and generate updated identifier */
    p0 = ((identifier & LIN_ID0) ^ ((identifier & LIN_ID1) >> 1U) ^ ((identifier & LIN_ID2) >> 2U) ^
          ((identifier & LIN_ID4) >> 4U));
    p1 = !(((identifier & LIN_ID1) >> 1U) ^ ((identifier & LIN_ID3) >> 3U) ^ ((identifier & LIN_ID4) >> 4U) ^
           ((identifier & LIN_ID5) >> 5U));
    parityIdentifier = identifier | ((p0 << 6U) | (p1 << 7U));

    return (parityIdentifier);
}

Std_ReturnType LinApp_Master_Response_Test()
{
    Std_ReturnType return_val = E_NOT_OK;

    AppUtils_printf(APP_NAME ": LinChannel_1 operating in Master Response mode \n\r");

    for (loop = 0; loop < 8; loop++)
    {
        txPdu.Pid    = Lin_GenerateParityID(7 + loop);
        txPdu.Cs     = (Lin_FrameCsModelType)(loop % 2);
        txPdu.Drc    = LIN_MASTER_RESPONSE;
        txPdu.Dl     = (loop + 1);
        txPdu.SduPtr = txData;

        return_val = Lin_SendFrame(LinConf_LinChannel_LinChannel_1, &txPdu);

        while (LIN_TX_OK != Lin_GetStatus(LinConf_LinChannel_LinChannel_1, rxData))
            ;

        AppUtils_printf(APP_NAME ": LinChannel_1 Transmission successful for %d data frame \n\r", loop);
    }

    AppUtils_printf(" \n\r");

    return return_val;
}

Std_ReturnType LinApp_Slave_Response_Test()
{
    Std_ReturnType return_val = E_NOT_OK;
    char           ip;

    AppUtils_printf(APP_NAME ": LinChannel_1 operating in Slave Response mode \n\r");

    txPdu.Pid    = Lin_GenerateParityID(0x20);
    txPdu.Cs     = LIN_ENHANCED_CS;
    txPdu.Drc    = LIN_SLAVE_RESPONSE;
    txPdu.Dl     = 8;
    txPdu.SduPtr = txData;

    return_val = Lin_SendFrame(LinConf_LinChannel_LinChannel_1, &txPdu);

    while (LIN_RX_OK != Lin_GetStatus(LinConf_LinChannel_LinChannel_1, rxData))
        ;

    AppUtils_printf(APP_NAME ": Received Data : ");

    for (loop = 0; loop < 8; loop++)
    {
        temp = rxBuff[loop];

        AppUtils_printf(" 0x%x ", temp);
    }

    AppUtils_printf(" \n\r");
    AppUtils_printf(" \n\r");

    AppUtils_printf(APP_NAME ": Does the data received match the data sent by the Slave? (y/n) \n\r");

    ip = AppUtils_getChar();

    if ('y' == ip)
    {
        AppUtils_printf(" \n\r");
        AppUtils_printf(APP_NAME ": LinChannel_1 Reception successful \n\r");

        return_val = E_OK;
    }
    else
    {
        return_val = E_NOT_OK;
    }

    return return_val;
}

Std_ReturnType LinApp_Slave_To_Slave_Test()
{
    Std_ReturnType return_val = E_NOT_OK;
    char           ip;

    AppUtils_printf(APP_NAME ": LinChannel_1 operating in Slave to Slave mode \n\r");

    txPdu.Pid    = Lin_GenerateParityID(0x30);
    txPdu.Cs     = LIN_ENHANCED_CS;
    txPdu.Drc    = LIN_SLAVE_TO_SLAVE;
    txPdu.Dl     = 4;
    txPdu.SduPtr = txData;

    return_val = Lin_SendFrame(LinConf_LinChannel_LinChannel_1, &txPdu);

    AppUtils_printf(" \n\r");

    AppUtils_printf(APP_NAME ": Did Slave to Slave communication happen? (y/n) \n\r");

    ip = AppUtils_getChar();

    if ('y' == ip)
    {
        AppUtils_printf(" \n\r");
        AppUtils_printf(APP_NAME ": LinChannel_1 Slave to Slave communication successful \n\r");

        return_val = E_OK;
    }
    else
    {
        return_val = E_NOT_OK;
    }

    return return_val;
}

static void LinApp_mainTest(void)
{
    AppUtils_TimerInit();

#if (LIN_GET_VERSION_INFO_API == STD_ON)

    Std_VersionInfoType versioninfo;

    /* Version Info Check*/
    Lin_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n\r");
    AppUtils_printf(APP_NAME ": LIN MCAL Version Info\n\r");
    AppUtils_printf("---------------------\n\r");
    AppUtils_printf(APP_NAME ": Vendor ID: %d\n\r", versioninfo.vendorID);
    AppUtils_printf(APP_NAME ": Module ID: %d\n\r", versioninfo.moduleID);
    AppUtils_printf(APP_NAME ": SW Major Version: %d\n\r", versioninfo.sw_major_version);
    AppUtils_printf(APP_NAME ": SW Minor Version: %d\n\r", versioninfo.sw_minor_version);
    AppUtils_printf(APP_NAME ": SW Patch Version: %d\n\r", versioninfo.sw_patch_version);
    AppUtils_printf(" \n\r");

#endif

/* LIN Init*/
#if (STD_ON == LIN_PRE_COMPILE_VARIANT)
    AppUtils_printf(APP_NAME ": Variant - Pre Compile being used !!!\n");
#else
    AppUtils_printf(APP_NAME ": Variant - Post Build being used !!!\n\r");
#endif
    AppUtils_printf(" \n\r");

#if (STD_ON == LIN_PRE_COMPILE_VARIANT)
    Lin_Init(NULL_PTR);
#else
    const Lin_ConfigType* pCfgPtr = &Lin_Config;
    Lin_Init(pCfgPtr);
#endif

    AppUtils_printf(APP_NAME ": Using LinChannel_1 -> LIN_INSTANCE_1 \n\r");

    AppUtils_printf(APP_NAME ": Waking LinChannel_1 from sleep \n\r");

    returnValue = Lin_WakeupInternal(LinConf_LinChannel_LinChannel_1);

    if (E_NOT_OK == returnValue)
    {
        AppUtils_printf(APP_NAME ": LinChannel_1 Wakeup Failed \n\r");
    }
    else
    {
        AppUtils_printf(APP_NAME ": LinChannel_1 Wakeup Successful \n\r");

        AppUtils_printf(" \n\r");

        while (test_run)
        {
            AppUtils_printf(APP_NAME ": Enter one of the following\n\r");
            AppUtils_printf(APP_NAME ": m - Send Master Response Lin Request\n\r");
            AppUtils_printf(APP_NAME ": s - Send Slave Response Lin Request\n\r");
            AppUtils_printf(APP_NAME ": x - Send Slave to Slave Lin Request\n\r");
            AppUtils_printf(APP_NAME ": a - Send all types Lin Request\n\r");
            AppUtils_printf(APP_NAME ": q - to quit the application\n\r\n\r");

            user_input = AppUtils_getChar();

            switch (user_input)
            {
                case 'm':
                    returnValue |= LinApp_Master_Response_Test();
                    break;

                case 's':
                    returnValue |= LinApp_Slave_Response_Test();
                    break;

                case 'x':
                    returnValue |= LinApp_Slave_To_Slave_Test();
                    break;

                case 'a':
                    returnValue |= LinApp_Master_Response_Test();
                    returnValue |= LinApp_Slave_Response_Test();
                    returnValue |= LinApp_Slave_To_Slave_Test();
                    break;

                case 'q':
                    test_run = FALSE;

                    if (E_NOT_OK == returnValue)
                    {
                        AppUtils_printf(APP_NAME ":Test case failed \n\r");
                    }
                    else
                    {
                        AppUtils_printf(APP_NAME ":All sample test case pass \n\r");
                    }
                    break;

                default:
                    break;
            }
        }
    }

    AppUtils_TimerDeinit();
}

uint8 MainFunc_Execution;

int main(void)
{
    LinApp_Startup();

    Lin_App_PlatformInit();

    Lin_InterruptConfig();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\n\r ");

    LinApp_mainTest();
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

void SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}
