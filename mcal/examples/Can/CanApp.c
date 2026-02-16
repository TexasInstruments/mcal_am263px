/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     CanApp.c
 *
 *  \brief    This file contains the Can test example
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/

/* Include Files */
#include "string.h"
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
#include "Can.h"
#include "CanApp_Startup.h"
#include "CanIf_Cbk.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "hw_types.h"
#include "esm.h"
#include "sys_vim.h"
#include "app_utils.h"
#include "trace.h"
#if defined(AM263PX_PLATFORM)
#include "app_utilsI2c.h"
#endif

/* ========================================================================== */
/*              Internal Function Declarations                                */
/* ========================================================================== */
#if (STD_ON == CAN_REGISTER_READBACK_API)
static void CanApp_SafetyApiTest(void);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8 MainFunc_Execution;

#define APP_NAME                "CanApp"
#define CANEXAMPLE_ARRAYSIZE(x) (sizeof((x)) / sizeof(x[0U]))

extern const Can_ConfigType Can_Config;
#ifdef CAN_LPDU_CALLOUT
boolean Can_LPdu_Callout(uint8 Hrh, Can_IdType CanId, uint8 CanDataLegth, const uint8* CanSduPtr);
#endif
static volatile uint32 msgCounter1 = 0U, CanIf_TxConfirmationCount = 0U;
static volatile uint32 eccErrCnt = 0U;
Can_PduType            Pdu, Pdu1, Pdu2, Pdu3, Pdu4;
Std_VersionInfoType    VersionInfo;
uint8                  CanRxData[64U], dlc;
Can_IdType             CanIdVal;
uint32                 ExecutionTicks, eccErrType;
uint32                 gTestPassed = E_OK;
Can_PduType            Pdunit;
boolean                bCanBusOff;
uint8 data[64U] = {0xA1, 0x1A, 0xFF, 0xFF, 0xC1, 0x1C, 0xB1, 0x1B, 0xA2, 0x2A, 0xFF, 0xFF, 0xC2, 0x2C, 0xB2, 0x2B,
                   0xA3, 0x3A, 0xFF, 0xFF, 0xC3, 0x3C, 0xB3, 0x3B, 0xA4, 0x4A, 0xFF, 0xFF, 0xC4, 0x4C, 0xB4, 0x4B,
                   0xA5, 0x5A, 0xFF, 0xFF, 0xC5, 0x5C, 0xB5, 0x5B, 0xA6, 0x6A, 0xFF, 0xFF, 0xC6, 0x6C, 0xB6, 0x6B,
                   0xA7, 0x7A, 0xFF, 0xFF, 0xC7, 0x7C, 0xB7, 0x7B, 0xA8, 0x8A, 0xFF, 0xFF, 0xC8, 0x8C, 0xB8, 0x8B};
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if (STD_ON == CAN_LOOPBACK_ENABLE)
static void CanExample_LoopbackTest()
{
    uint32 cntr_cnt, mask = 0x00000000U;
    ;
    const Can_ConfigType* Can_ConfigPtr;
    Can_PduType*          PduInfo;
    uint8                 loopCnt = 0U, hth = 0U;
    Std_ReturnType        status;

    Can_ConfigPtr = &Can_Config;
    /* Message for CAN-FD(MCAN module) */
    PduInfo = &Pdu;
    /* Setting Up CAN FD Frame*/
    Pdu.id          = 0xC1 | 0x40000000U;
    Pdu.length      = 64U;
    Pdu.swPduHandle = 1U;
    Pdu.sdu         = &data[0U];

    /* Message for CAN(DCAN module) */
    /* Setting Up CAN FD Frame*/
    Pdu1.id          = 0xC1;
    Pdu1.length      = 8U;
    Pdu1.swPduHandle = 1U;
    Pdu1.sdu         = &data[0U];

    Pdu2.id          = 0xC1;
    Pdu2.length      = 8U;
    Pdu2.swPduHandle = 2U;
    Pdu2.sdu         = &data[0U];

    Pdu3.id          = 0xC1;
    Pdu3.length      = 8U;
    Pdu3.swPduHandle = 2U;
    Pdu3.sdu         = &data[0U];

    Pdu4.id          = 0xC1;
    Pdu4.length      = 8U;
    Pdu4.swPduHandle = 2U;
    Pdu4.sdu         = &data[0U];

    AppUtils_printf(APP_NAME ": CAN Loopback test \n\r");
    /* Do Can Init */
    Can_Init(Can_ConfigPtr);
    for (cntr_cnt = 0U; cntr_cnt < (Can_ConfigPtr->CanMaxControllerCount); cntr_cnt++)
    {
        /* Flush RxData */
        for (loopCnt = 0U; loopCnt < Pdu.length; loopCnt++)
        {
            CanRxData[loopCnt] = 0;
        }
        if (CAN_CONTROLLER_INSTANCE_MCAN0 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
        {
            AppUtils_printf(APP_NAME ": Can Controller: MCAN0\n\r");
            PduInfo = &Pdu;
            hth     = 0U;
            /* mask is need for checking id of received message with
             * sent message as 30th bit the of sent message will be set
             * for CAN FD frame */
            mask = 0x40000000U;
        }
        else if (CAN_CONTROLLER_INSTANCE_MCAN1 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
        {
            AppUtils_printf(APP_NAME ": Can Controller: MCAN1\n\r");
            PduInfo = &Pdu1;
            hth     = 2U;
            mask    = 0x00000000U;
        }
#if defined(CAN_CONTROLLER_MCAN2)
        else if (CAN_CONTROLLER_INSTANCE_MCAN2 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
        {
            AppUtils_printf(APP_NAME ": Can Controller: MCAN2\n\r");
            PduInfo = &Pdu2;
            hth     = 4U;
            mask    = 0x00000000U;
        }
#endif
#if defined(CAN_CONTROLLER_MCAN3)
        else if (CAN_CONTROLLER_INSTANCE_MCAN3 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
        {
            AppUtils_printf(APP_NAME ": Can Controller: MCAN3\n\r");
            PduInfo = &Pdu3;
            hth     = 6U;
            mask    = 0x00000000U;
        }
#endif
#if defined(CAN_CONTROLLER_MCAN4)
        else if (CAN_CONTROLLER_INSTANCE_MCAN4 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
        {
            AppUtils_printf(APP_NAME ": Can Controller: MCAN4\n\r");
            PduInfo = &Pdu4;
            hth     = 16U;
            mask    = 0x00000000U;
        }
#endif
        else
        {
        }
        status = Can_SetControllerMode(CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, CAN_CS_STARTED);
        if (status != E_OK)
        {
            gTestPassed = E_NOT_OK;
        }

#if (CAN_LOOPBACK_ENABLE == STD_ON)
        /* Enable loopback mode in CAN */
        Can_TestLoopBackModeEnable(CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, 0U);
#endif

        /* Do Can Write to send the data on CAN bus */
        AppUtils_printf(APP_NAME "Calling Can_Write \n\r");
        status = Can_Write(hth, PduInfo);
        if (status != E_OK)
        {
            AppUtils_printf(APP_NAME ": Error In Can_Write.\n\r");
            gTestPassed = E_NOT_OK;
        }
        AppUtils_printf(APP_NAME "Can_Write ok \n\r");

        AppUtils_delay(30U);
#if (CAN_TX_POLLING == STD_ON)
        Can_MainFunction_Write();
#endif

#if (CAN_RX_POLLING == STD_ON)
        Can_MainFunction_Read();
#endif

        if (E_OK == gTestPassed)
        {
            if (0U != eccErrCnt)
            {
                eccErrCnt   = 0U;
                gTestPassed = E_NOT_OK;
                if ((uint32)CAN_ECC_ERROR_TYPE_PARITY == eccErrType)
                {
                    AppUtils_printf(APP_NAME ": Parity Error Detected.\n\r");
                }
                else if ((uint32)CAN_ECC_ERROR_TYPE_SEC == eccErrType)
                {
                    AppUtils_printf(APP_NAME ": SEC Error Detected.\n\r");
                }
                else if ((uint32)CAN_ECC_ERROR_TYPE_DED == eccErrType)
                {
                    AppUtils_printf(APP_NAME ": DED Error Detected.\n\r");
                }
                else
                {
                }
                break;
            }
            else if ((1U == CanIf_TxConfirmationCount) && (1U == msgCounter1))
            {
                CanIf_TxConfirmationCount = 0U;
                msgCounter1               = 0U;
            }
            else
            {
                gTestPassed = E_NOT_OK;
                break;
            }
            /* Set Controller Mode for controller 0U */
            status = Can_SetControllerMode(CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, CAN_CS_STOPPED);
            if (status != E_OK)
            {
                gTestPassed = E_NOT_OK;
            }
#if (CAN_LOOPBACK_ENABLE == STD_ON)
            Can_TestLoopBackModeDisable(CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, 0U);
#endif
            if ((PduInfo->length == dlc) && (PduInfo->id == (CanIdVal | mask)))
            {
                for (loopCnt = 0U; loopCnt < PduInfo->length; loopCnt++)
                {
                    if (CanRxData[loopCnt] != data[loopCnt])
                    {
                        gTestPassed = E_NOT_OK;
                        AppUtils_printf(APP_NAME ": Transmitted and Received data miss-matched.\n\r");
                    }
                }
            }
            else
            {
                gTestPassed = E_NOT_OK;
                break;
            }
        }
        if (gTestPassed == E_OK)
        {
            AppUtils_printf(APP_NAME ": Test Passed\n\n\r");
        }
    }
}

#else
static void CanExample_ExternalTest()
{
    char                    option;
    boolean                 quit_opt = 0;
    uint32                  cntr_cnt;
    const Can_ConfigType*   Can_ConfigPtr;
    Can_PduType*            PduInfo;
    uint8                   loopCnt = 0U, hth = 0U;
    Std_ReturnType          status;
    uint8                   operationMode = 1;
    Can_ControllerStateType Controller_Satus;
#if defined(AM263PX_PLATFORM)
    I2c_utilsInterruptConfig();
    Cdd_I2c_Init(NULL_PTR);
    mcanEnableTransceiver();
#endif

#if (STD_ON == CAN_VARIANT_PRE_COMPILE)
    Can_ConfigPtr = &CAN_INIT_CONFIG_PC;
#else
    Can_ConfigPtr = &Can_Config;
#endif
    /* Message for CAN-FD(MCAN module) */
    PduInfo = &Pdu;
    /* Setting Up CAN FD Frame*/
    Pdu.id          = 0xC1 | 0x40000000U;
    Pdu.length      = 64U;
    Pdu.swPduHandle = 1U;
    Pdu.sdu         = &data[0U];

    /* Do Can Init */
    Can_Init(Can_ConfigPtr);

    AppUtils_printf(APP_NAME ": Select one of the controller\n\r");
#if defined(CAN_CONTROLLER_MCAN0)
    AppUtils_printf(APP_NAME ": d - for using MCAN controller 0 \n\r");
#endif
#if defined(CAN_CONTROLLER_MCAN1)
    AppUtils_printf(APP_NAME ": m - for using MCAN controller 1 \n\r");
#endif
#if defined(CAN_CONTROLLER_MCAN2)
    AppUtils_printf(APP_NAME ": n - for using MCAN controller 2 \n\r");
#endif
#if defined(CAN_CONTROLLER_MCAN3)
    AppUtils_printf(APP_NAME ": s - for using MCAN controller 3 \n\r");
#endif
#if defined(CAN_CONTROLLER_MCAN4)
    AppUtils_printf(APP_NAME ": f - for using MCAN controller 4 \n\r");
#endif
    option = AppUtils_getChar();
    if (option == 'd')
    {
        cntr_cnt = 0;
        AppUtils_printf(APP_NAME ":MCAN Selected - CAN_CONTROLLER_INSTANCE_MCAN0 (cntr_cnt=0) \n\r");
    }
    else if (option == 'm')
    {
        cntr_cnt = 1;
        AppUtils_printf(APP_NAME ":MCAN Selected - CAN_CONTROLLER_INSTANCE_MCAN1 (cntr_cnt=1) \n\r");
    }
    else if (option == 'n')
    {
        cntr_cnt = 2;
        AppUtils_printf(APP_NAME ":MCAN Selected - CAN_CONTROLLER_INSTANCE_MCAN2 (cntr_cnt=2) \n\r");
    }
    else if (option == 's')
    {
        AppUtils_printf(APP_NAME ":MCAN Selected - - CAN_CONTROLLER_INSTANCE_MCAN3 (cntr_cnt=3)\n\r");
        cntr_cnt = 3;
    }
    else
    {
        AppUtils_printf(APP_NAME ":MCAN Selected - - CAN_CONTROLLER_INSTANCE_MCAN4 (cntr_cnt=4)\n\r");
        cntr_cnt = 4;
    }
    /* Disable interrupts for selected controller */
    AppUtils_printf(APP_NAME ": Select one of the Mode\n\r");
    AppUtils_printf(APP_NAME ": i - for interrupt mode\n\r");
    AppUtils_printf(APP_NAME ": p - for polling mode\n\r");
    option = AppUtils_getChar();

    if (option == 'i')
    {
        AppUtils_printf(APP_NAME ":Interrupt mode selected\n\r");
        operationMode = 0;
    }
    else
    {
        AppUtils_printf(APP_NAME ":polling Mode selected\n\r");
        operationMode = 1;
    }
    /* Flush RxData */
    for (loopCnt = 0U; loopCnt < Pdu.length; loopCnt++)
    {
        CanRxData[loopCnt] = 0;
    }
    if (CAN_CONTROLLER_INSTANCE_MCAN0 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
    {
        AppUtils_printf(APP_NAME ": Can Controller: MCAN0/MCANA (cntr_cnt=0)\n\r");
        Pdu.sdu = &data[0U];
        PduInfo = &Pdu;  // this CAN controller will be CAN FD
    }
    else if (CAN_CONTROLLER_INSTANCE_MCAN1 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
    {
        AppUtils_printf(APP_NAME ": Can Controller:MCAN1/MCANB (cntr_cnt=1)  \n\r");
        Pdu.sdu = &data[0U];
        PduInfo = &Pdu;
    }
#if defined(CAN_CONTROLLER_MCAN2)
    else if (CAN_CONTROLLER_INSTANCE_MCAN2 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
    {
        AppUtils_printf(APP_NAME ": Can Controller:MCAN2 (cntr_cnt=2)  \n\r");
        Pdu.sdu = &data[0U];
        PduInfo = &Pdu;
    }
#endif
#if defined(CAN_CONTROLLER_MCAN3)
    else if (CAN_CONTROLLER_INSTANCE_MCAN3 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
    {
        AppUtils_printf(APP_NAME ": Can Controller:MCAN3 (cntr_cnt=3)  \n\r");
        Pdu.sdu = &data[0U];
        PduInfo = &Pdu;
    }
#endif
#if defined(CAN_CONTROLLER_MCAN4)
    else if (CAN_CONTROLLER_INSTANCE_MCAN4 == CanConfigSet_CanController_List_PC[cntr_cnt]->CanControllerInst)
    {
        AppUtils_printf(APP_NAME ": Can Controller:MCAN4 (cntr_cnt=4)  \n\r");
        Pdu.sdu = &data[0U];
        PduInfo = &Pdu;
    }
#endif
    else
    {
        AppUtils_printf(APP_NAME "please check the configuration\n\r");
    }
    /* Set Controller Mode for selected controller */
    status = Can_SetControllerMode(CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, CAN_CS_STARTED);

    Can_GetControllerMode(CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, &Controller_Satus);

    AppUtils_printf(APP_NAME ": Status: %d\n", Controller_Satus);
    if (status != E_OK)
    {
        gTestPassed = E_NOT_OK;
    }

    while (1)
    {
        AppUtils_printf(APP_NAME ": Enter one of the following\n\r");
        AppUtils_printf(APP_NAME ": t - to transmit data\n\r");
        AppUtils_printf(APP_NAME ": r - to receive data\n\r");
        AppUtils_printf(APP_NAME ": q - to quit the application\n\r\n\r");

        /* Decide whether to wait to receive CAN message or to send the data on CAN bus */
        option = AppUtils_getChar();

        switch (option)
        {
            case 't':
                AppUtils_printf(APP_NAME ": e - for extended format\n\r");
                AppUtils_printf(APP_NAME ": s - for standard format\n\r");
                option = AppUtils_getChar();

                if (cntr_cnt == 0)
                {
                    (operationMode == 0) ? (Pdu.id = 0xC2) : (Pdu.id = 0xC1);
                    if (option == 'e')
                    {
                        AppUtils_printf("sending message with extended ID\n\r");
                        Pdu.id |= 0x80000000U;
                    }
                    else
                    {
                        AppUtils_printf("sending message with standard ID\n\r");
                    }
                    Pdu.id |= 0x40000000U;
                    (operationMode == 0) ? (hth = 1U) : (hth = 0U);
                }
                else if (cntr_cnt == 1)
                {
                    (operationMode == 0) ? (Pdu.id = 0xC0) : (Pdu.id = 0xC1);
                    if (option == 'e')
                    {
                        AppUtils_printf("sending message with extended ID\n\r");
                        Pdu.id |= 0x80000000U;
                    }
                    else
                    {
                        AppUtils_printf("sending message with standard ID\n\r");
                    }
                    Pdu.id |= 0x40000000U;
                    (operationMode == 0) ? (hth = 3U) : (hth = 2U);
                }
                else if (cntr_cnt == 2)
                {
                    (operationMode == 0) ? (Pdu.id = 0xC0) : (Pdu.id = 0xC1);
                    if (option == 'e')
                    {
                        AppUtils_printf("sending message with extended ID\n\r");
                        Pdu.id |= 0x80000000U;
                    }
                    else
                    {
                        AppUtils_printf("sending message with standard ID\n\r");
                    }
                    Pdu.id |= 0x40000000U;
                    (operationMode == 0) ? (hth = 5U) : (hth = 4U);
                }
                else if (cntr_cnt == 3)
                {
                    (operationMode == 0) ? (Pdu.id = 0xC0) : (Pdu.id = 0xC1);
                    if (option == 'e')
                    {
                        AppUtils_printf("sending message with extended ID\n\r");
                        Pdu.id |= 0x80000000U;
                    }
                    else
                    {
                        AppUtils_printf("sending message with standard ID\n\r");
                    }
                    Pdu.id |= 0x40000000U;
                    (operationMode == 0) ? (hth = 7U) : (hth = 6U);
                }
                else if (cntr_cnt == 4)
                {
                    (operationMode == 0) ? (Pdu.id = 0xC0) : (Pdu.id = 0xC1);
                    if (option == 'e')
                    {
                        AppUtils_printf("sending message with extended ID\n\r");
                        Pdu.id |= 0x80000000U;
                    }
                    else
                    {
                        AppUtils_printf("sending message with standard ID\n\r");
                    }
                    Pdu.id |= 0x40000000U;
                    (operationMode == 0) ? (hth = 17U) : (hth = 16U);
                }
                else
                {
                    (operationMode == 0) ? (Pdu.id = 0xC0) : (Pdu.id = 0xC1);
                    if (option == 'e')
                    {
                        AppUtils_printf("sending message with extended ID\n\r");
                        Pdu.id |= 0x80000000U;
                    }
                    else
                    {
                        AppUtils_printf("sending message with standard ID\n\r");
                    }
                    Pdu.id |= 0x40000000U;
                    (operationMode == 0) ? (hth = 7U) : (hth = 6U);
                }

                status = Can_Write(hth, PduInfo);

                if (status != E_OK)
                {
                    AppUtils_printf(APP_NAME ": Error In Can_Write.\n\r");
                    gTestPassed = E_NOT_OK;
                }
                else
                {
                    if (operationMode == 0)
                    {
                        while (CanIf_TxConfirmationCount == 0)
                        {
                            if (CanConfigSet_CanController_List_PC[cntr_cnt]->BusOffProcessingInterrupt == false)
                            {
                                Can_MainFunction_BusOff();
                            }
                            if (MainFunc_Execution == 3U)
                            {
                                status = Can_SetControllerMode(
                                    CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, CAN_CS_STARTED);
                                MainFunc_Execution = 0;
                                AppUtils_printf(APP_NAME ": Bus Off Occured.\n\r");

                                break;
                            }
                        }
                    }
                    else
                    {
                        while (CanIf_TxConfirmationCount == 0)
                        {
                            /*poll Can_MainFunction_Write for TX confirmation*/

                            Can_MainFunction_Write();
                            if (CanConfigSet_CanController_List_PC[cntr_cnt]->BusOffProcessingInterrupt == false)
                            {
                                Can_MainFunction_BusOff();
                            }
                            if (MainFunc_Execution == 3U)
                            {
                                status = Can_SetControllerMode(
                                    CanConfigSet_CanController_List_PC[cntr_cnt]->ControllerId, CAN_CS_STARTED);
                                MainFunc_Execution = 0;
                                AppUtils_printf(APP_NAME ": Bus Off Occured.\n\r");

                                break;
                            }
                            AppUtils_delay(100U);
                        }
                    }
                    AppUtils_printf(APP_NAME ": Data transmitted.\n\r");
                    CanIf_TxConfirmationCount = 0;
                }
                break;

            case 'r':
                AppUtils_printf(APP_NAME ": waiting to receive data\n\r");
                if (operationMode == 1)
                {
                    while ((0U == msgCounter1))
                    {
                        Can_MainFunction_Read();
                        AppUtils_delay(100U);
                    };
                    msgCounter1 = 0U;
                    for (loopCnt = 0U; loopCnt < dlc; loopCnt++)
                    {
                        if ((loopCnt % 8) == 7)
                        {
                            /*Klockworks fix :  ABV.GENERAL*/
                            if (loopCnt < 64U)
                            {
                                AppUtils_printf("0x%x\n\r", CanRxData[loopCnt]);
                            }
                        }
                        else
                        {
                            /*Klockworks fix :  ABV.GENERAL*/
                            if (loopCnt < 64U)
                            {
                                AppUtils_printf("0x%x\t", CanRxData[loopCnt]);
                            }
                        }
                    }
                }
                else
                {
                    while ((0U == msgCounter1))
                    {
                        AppUtils_delay(100U);
                    };
                    msgCounter1 = 0U;
                    AppUtils_printf(APP_NAME ": Received Data \n\r");
                    for (loopCnt = 0U; loopCnt < dlc; loopCnt++)
                    {
                        if ((loopCnt % 8) == 7)
                        {
                            AppUtils_printf("0x%x\n\r", CanRxData[loopCnt]);
                        }
                        else
                        {
                            AppUtils_printf("0x%x\t", CanRxData[loopCnt]);
                        }
                    }
                }

                break;

            case 'q':
                quit_opt = 1;
                break;

            default:
                AppUtils_printf(APP_NAME ": Invalid Input\n\r");
                continue;
        }

        if (E_OK != gTestPassed)
        {
            AppUtils_printf(APP_NAME ": Exiting the application\n\r");
            break;
        }

        if (0U != eccErrCnt)
        {
            eccErrCnt   = 0U;
            gTestPassed = E_NOT_OK;
            if ((uint32)CAN_ECC_ERROR_TYPE_PARITY == eccErrType)
            {
                AppUtils_printf(APP_NAME ": Parity Error Detected.\n\r");
            }
            else if ((uint32)CAN_ECC_ERROR_TYPE_SEC == eccErrType)
            {
                AppUtils_printf(APP_NAME ": SEC Error Detected.\n\r");
            }
            else if ((uint32)CAN_ECC_ERROR_TYPE_DED == eccErrType)
            {
                AppUtils_printf(APP_NAME ": DED Error Detected.\n\r");
            }
            else
            {
            }
            break;
        }

        if (quit_opt == 1)
        {
            break;
        }

    }  // end of while (1)

    if (gTestPassed == E_OK)
    {
        AppUtils_printf(APP_NAME ": Test Passed\n\r");
    }
}

#endif
typedef void (*CanExampleFxn_t)(void);

CanExampleFxn_t CanExampleFxnTbl[] = {

#if (STD_ON == CAN_LOOPBACK_ENABLE)
    CanExample_LoopbackTest,
#else
    CanExample_ExternalTest
#endif
};

sint32 main(void)
{
    uint8_least i;

    gTestPassed = E_OK;

    CanApp_Startup();

    AppUtils_printf(APP_NAME ": Sample Application - STARTS !!!\n\n\r");

    for (i = 0U; i < CANEXAMPLE_ARRAYSIZE(CanExampleFxnTbl); i++)
    {
        CanExampleFxnTbl[i]();
    }

#if (STD_ON == CAN_REGISTER_READBACK_API)
    CanApp_SafetyApiTest();
#endif

    GT_1trace(McalAppTrace, GT_INFO, "\nCAN Stack Usage: %d bytes\n\r", AppUtils_getStackUsage());
    if (AppUtils_checkStackAndSectionCorruption() != E_OK)
    {
        gTestPassed = E_NOT_OK;
        GT_0trace(McalAppTrace, GT_ERR, "CAN Stack/section corruption!!!\n\r");
    }
    AppUtils_TimerDeinit();
    if (E_OK == gTestPassed)
    {
        GT_0trace(McalAppTrace, GT_INFO, "All tests have passed\n\r");
    }
    else
    {
        GT_0trace(McalAppTrace, GT_ERR, "CAN Test Failed!!!\n\r");
    }
    return (gTestPassed);
}

void CanIf_ControllerBusOff(uint8 Controller)
{
    MainFunc_Execution = 3U;
}

void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr)
{
    uint8 i;
    msgCounter1++;
    MainFunc_Execution = 5U;

    if (PduInfoPtr->SduLength > 64U)
    {
        return;
    }
    /* Copy data */
    CanIdVal = Mailbox->CanId;
    dlc      = PduInfoPtr->SduLength;
    for (i = 0U; i < PduInfoPtr->SduLength; i++)
    {
        CanRxData[i] = PduInfoPtr->SduDataPtr[i];
    }
}

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
    CanIf_TxConfirmationCount++;
    MainFunc_Execution = 4U;
}

void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
    MainFunc_Execution = 2U;
}

#if (CAN_TRIGGER_TRANSMIT_ENABLE == STD_ON)
Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
    PduInfoPtr->SduDataPtr = &data[0U];
    PduInfoPtr->SduLength  = 46U;
    return E_OK;
}
#endif

#ifdef CAN_LPDU_CALLOUT
boolean Can_LPdu_Callout(uint8 Hrh, Can_IdType CanId, uint8 CanDataLegth, const uint8* CanSduPtr)
{
    return true;
}
#endif

void EcuM_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    MainFunc_Execution = 1U;
}

uint8 Intc_status;

#ifdef __cplusplus
extern "C" {
#endif

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

void SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0()
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0()
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
    AppUtils_printf(APP_NAME "Module ID: %d \t Instance ID: %d\t ApiID: %d\t ErrorID: %d \n", ModuleId, InstanceId,
                    ApiId, ErrorId);
    return (E_OK);
}

Std_ReturnType Det_ReportRuntimeError(VAR(uint16, AUTOMATIC) ModuleId, VAR(uint8, AUTOMATIC) InstanceId,
                                      VAR(uint8, AUTOMATIC) ApiId, VAR(uint8, AUTOMATIC) ErrorId)
{
    gTestPassed = E_NOT_OK;
    GT_assert(McalAppTrace, FALSE);
    return (E_OK);
}

#if (STD_ON == CAN_REGISTER_READBACK_API)
static void CanApp_SafetyApiTest(void)
{
    uint32                   ctlr_cnt, canMaxControllerCnt;
    Std_ReturnType           status;
    const Can_ConfigType*    Can_ConfigPtr;
    Can_RegisterReadbackType Can_RegRb;

#if (STD_ON == CAN_VARIANT_PRE_COMPILE)
    Can_ConfigPtr = &CAN_INIT_CONFIG_PC;
#else
    Can_ConfigPtr = &Can_Config;
#endif

    canMaxControllerCnt = Can_ConfigPtr->CanMaxControllerCount;

    AppUtils_printf(APP_NAME ": Can_RegisterReadback test\n\r");
    for (ctlr_cnt = 0U; ctlr_cnt < canMaxControllerCnt; ctlr_cnt++)
    {
        status = Can_RegisterReadback(CanConfigSet_CanController_List_PC[ctlr_cnt]->ControllerId, &Can_RegRb);
        if (status != E_OK)
        {
            AppUtils_printf(APP_NAME ": Can_RegisterReadback Failed for MCAN%d\n\r", ctlr_cnt);
            gTestPassed = E_NOT_OK;
        }
        else
        {
            AppUtils_printf(APP_NAME ": Can_RegisterReadback Successful for MCAN%d\n\r", ctlr_cnt);
            gTestPassed = E_OK;
        }
    }
}
#endif /* #if (STD_ON == CAN_REGISTER_READBACK_API)*/

#ifdef __cplusplus
}
#endif
