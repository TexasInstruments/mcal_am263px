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
 *  \file     Cdd_Ipc_notify_app.c
 *
 *  \brief    This file contains the IPC R50 test app for IPC Notify
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
/*LDRA_ANALYSIS*/
#include "sys_vim.h"
#include "Cdd_Ipc_Cfg.h"
#include "Cdd_Ipc.h"
#include "Cdd_Ipc_Irq.h"
#include "Cdd_Ipc_app.h"
#include "Cdd_Ipc_App_Startup.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

uint32 gMsgEchoCount = 1000000;

uint32 msgValue;

uint16 gClientId = 4;
uint32 i, numRemoteCores = 0;

extern uint32 gRemoteCoreId[MAX];

volatile uint32 gIpcTransferMutex[MAX] = {CDD_IPC_LOCK, CDD_IPC_LOCK, CDD_IPC_LOCK, CDD_IPC_LOCK};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void Cdd_Ipc_notify_MsgHandler(void* ipcNotifyHandle, uint32 Cdd_Ipc_remoteCoreId, uint16 Cdd_Ipc_remoteClientId,
                               uint32 Cdd_Ipc_msgValue, uint32 timeout, sint32 crc, void* args)
{
    /* increment msgValue and send it back until gMsgEchoCount iterations are done */
    if (Cdd_Ipc_msgValue != (gMsgEchoCount - 1U))
    {
        /* send new message to remote core, that echod our message */
        Cdd_Ipc_msgValue++;
#if (STD_ON == CDD_IPC_WRITE_API)
        Cdd_Ipc_Notify_Write(Cdd_Ipc_remoteCoreId, gClientId, Cdd_Ipc_msgValue, 1);
#endif
    }
    else
    {
        /**
         * There is one semaphore for each core ID, so post the semaphore for the remote core that
         * has finished all message exchange iterations. Please note this is just a pseudo
         * implementation of the semaphores/mutexes using global variables
         */
        gIpcTransferMutex[Cdd_Ipc_remoteCoreId] = CDD_IPC_UNLOCK;
    }
}

/* Entry point of example */
int main(void)
{
    Cdd_Ipc_App_Startup();

    Cdd_Ipc_App_PlatformInit();

    Cdd_Ipc_Init(&CddIpcDriver_0);

    Cdd_Ipc_Notify_RegisterClient(gClientId, Cdd_Ipc_notify_MsgHandler, NULL_PTR);

    AppUtils_printf(APP_NAME ": Sample IPC Application started!\r\n");

    /* Interrupt Configuration (Registering Interrupt to R5 core, ISR) */
    /* Do this after Cdd_Ipc_Init is done because ISR can get triggerred due to SyncAll from Other
    core and lead to data abort due to Un-initialized IPC handles*/
    Cdd_Ipc_InterruptConfig();

    Cdd_Ipc_Notify_Sync_All();
    AppUtils_printf(APP_NAME ": Sync All Completed\r\n");

    AppUtils_printf(APP_NAME ": Message exchange started by main core \r\n");

    for (i = 0; gRemoteCoreId[i] != MAX; i++)
    {
/* send message's to all participating core's, wait for message to be put in HW FIFO */
#if (STD_ON == CDD_IPC_WRITE_API)
        msgValue = 0;
        Cdd_Ipc_Notify_Write(gRemoteCoreId[i], gClientId, msgValue, 1);
#endif
    }

    /* wait for all messages to be echo'ed back */
    numRemoteCores = 0;
    for (i = 0; gRemoteCoreId[i] != MAX; i++)
    {
        while (CDD_IPC_LOCK == gIpcTransferMutex[gRemoteCoreId[i]])
            ;
        numRemoteCores++;
    }

    AppUtils_printf(APP_NAME ": All echoed messages received by main core from %d remote cores !!!\r\n",
                    numRemoteCores);
    AppUtils_printf(APP_NAME ": Messages sent to each core = %d \r\n", gMsgEchoCount);
    AppUtils_printf(APP_NAME ": Number of remote cores = %d \r\n", numRemoteCores);
    AppUtils_printf("All tests have passed\n\r");
    Cdd_Ipc_Notify_UnregisterClient(gClientId);

#if (STD_ON == CDD_IPC_DEINIT_API)
    Cdd_Ipc_DeInit(&CddIpcDriver_0);
#endif

    AppUtils_TimerDeinit();

    return (0);
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

void SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

void SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0(void)
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
