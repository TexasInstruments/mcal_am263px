/**
 *  \file     Cdd_Ipc_rpmsg_app.c
 *
 *  \brief    This file contains the IPC R50 test app for RpMsg
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
/*LDRA_ANALYSIS*/
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "app_utils.h"
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

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

#define MAX_MSG_SIZE (64U)

uint32 msgValue;
uint32 gMsgEchoCount = 100000U;
uint32 msg, i, numRemoteCores = 0U;
uint16 gRemoteServiceEndPt = 13U;

uint16 remoteCoreId, remoteCoreEndPt, msgSize;

char msgBuf[MAX_MSG_SIZE];

extern uint32 gRemoteCoreId[];

volatile uint32 gIpcTransferMutex[MAX] = {CDD_IPC_LOCK, CDD_IPC_LOCK, CDD_IPC_LOCK, CDD_IPC_LOCK};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* RpMsg Callback Implementation */
/* When a RpMsg arrives, this function is invoked along with all the data in the VRING buffer*/
#if (STD_ON == CDD_IPC_RPMSG_CALLBACK_ENABLE)
void Callback(void *handle, RPMessage_EpObject *epObj, void *args, void *data, uint16 dataLen, sint32 crcStatus,
              uint16 remoteCoreId, uint16 remoteEndPt)
{
    /*Convert the void data-type of the "data" variable passed by driver callback to integer to find
     * the messages transmitted  */
    msg = strtol((char *)data, NULL, 10);
    if (msg != (gMsgEchoCount - 1))
    {
        /* If the number of messages to be sent are less than the 1,00,000 messages increment the
         * message count, construct a new packet and echo it back to same core*/
        msg++;
        snprintf(msgBuf, MAX_MSG_SIZE - 1, "%d", msg);
        msgBuf[MAX_MSG_SIZE - 1] = 0;
        msgSize                  = strlen(data) + 1; /* count the terminating char as well */
/* Sending Data from local End point ID 0 i.e., 12 as per Configuration*/
#if (STD_ON == CDD_IPC_RPMSG_ENABLE_API)
        Cdd_Ipc_RpMsg_SendMsg(msgBuf, msgSize, remoteCoreId, remoteEndPt,
                              CddIpcConf_CddIpclocalEndPt_CddIpcEndPtConfig_0, CDD_IPC_TIMEOUT);
#endif
    }
    else
    {
        /**
         * There is one semaphore for each core ID, so post the semaphore for the remote core that
         * has finished all message exchange iterations. Please note this is just a pseudo
         * implementation of the semaphores/mutexes using global variables
         */
        gIpcTransferMutex[remoteCoreId] = CDD_IPC_UNLOCK;
    }
}
#endif

/* Notify Callback Implementaion */
/* In this mode, when a rpmsg comes the below function is invoked and an explicit rpmsg Read must be
issued to read the data from VRING. That is the only difference between callback and notify
callback.*/
#if (STD_ON == CDD_IPC_RPMSG_NOTIFY_CALLBACK_ENABLE)
void Notify_callback(void *handle, Cdd_Ipc_RPMessage_EpObject *obj, void *args)
{
    msgSize = sizeof(msgBuf);
#if (STD_ON == CDD_IPC_RPMSG_ENABLE_API)
    Cdd_Ipc_RpMsg_RecvMsg(msgBuf, &msgSize, CddIpcConf_CddIpclocalEndPt_CddIpcEndPtConfig_0, &remoteCoreId,
                          &remoteCoreEndPt, CDD_IPC_TIMEOUT);
#endif
    msg = strtol((char *)msgBuf, NULL, 10);

    if (msg != (gMsgEchoCount - 1))
    {
        msg++;
        snprintf(msgBuf, MAX_MSG_SIZE - 1, "%d", msg);
        msgBuf[MAX_MSG_SIZE - 1] = 0;
        msgSize                  = strlen(msgBuf) + 1; /* count the terminating char as well */
/* Sending Data from local End point ID 0 i.e., 12 as per Configuration*/
#if (STD_ON == CDD_IPC_RPMSG_ENABLE_API)
        Cdd_Ipc_RpMsg_SendMsg(msgBuf, msgSize, remoteCoreId, remoteCoreEndPt,
                              CddIpcConf_CddIpclocalEndPt_CddIpcEndPtConfig_0, CDD_IPC_TIMEOUT);
#endif
    }
    else
    {
        /**
         * There is one semaphore for each core ID, so post the semaphore for the remote core that
         * has finished all message exchange iterations. Please note this is just a pseudo
         * implementation of the semaphores/mutexes using global variables
         */
        gIpcTransferMutex[remoteCoreId] = CDD_IPC_UNLOCK;
    }
}
#endif

/* Entry point of example */
int main(void)
{
    Cdd_Ipc_App_Startup();

    Cdd_Ipc_App_PlatformInit();

    Cdd_Ipc_Init(&Cdd_Ipc_Config);

#if (STD_ON == CDD_IPC_RPMSG_ENABLE_API)
    Cdd_Ipc_Construct(&Cdd_Ipc_Config);
#endif

    numRemoteCores = 0U;
    for (i = 0U; gRemoteCoreId[i] != MAX; i++)
    {
        numRemoteCores++;
    }

    AppUtils_printf(APP_NAME ": Sample IPC Application started!\r\n");

    /* Interrupt Configuration (Registering Interrupt to R5 core, ISR) */
    /* Do this after Cdd_Ipc_Init is done because ISR can get triggerred due to SyncAll from Other
    core and lead to data abort due to Un-initialized IPC handles*/
    Cdd_Ipc_InterruptConfig();

    Cdd_Ipc_Notify_Sync_All();
    AppUtils_printf(APP_NAME ": Sync All Completed\r\n");

    AppUtils_printf(APP_NAME ": RpMsg Message exchange started by main core \r\n");

    snprintf(msgBuf, MAX_MSG_SIZE - 1U, "%d", msg);
    msgBuf[MAX_MSG_SIZE - 1U] = 0U;
    msgSize                   = strlen(msgBuf) + 1U; /* count the terminating char as well */
    uint8 retval              = E_OK;
    /* send the same messages to all cores */
    for (i = 0; gRemoteCoreId[i] != MAX; i++)
    {
#if (STD_ON == CDD_IPC_RPMSG_ENABLE_API)
        retval = Cdd_Ipc_RpMsg_SendMsg(msgBuf, msgSize, gRemoteCoreId[i], gRemoteServiceEndPt,
                                       CddIpcConf_CddIpclocalEndPt_CddIpcEndPtConfig_0, CDD_IPC_TIMEOUT);
        if (retval != E_OK)
        {
            volatile uint32 myTmp = 1U;
            AppUtils_printf(APP_NAME ": Send message to Remote core Id %u is failed \r\n", gRemoteCoreId[i]);
            while (myTmp)
            {
                /* code */
            }
        }
#endif
    }

    /* wait for all messages to be echo'ed back */
    numRemoteCores = 0U;
    for (i = 0; gRemoteCoreId[i] != MAX; i++)
    {
        /* Once all the messages are received, respective semaphores are unblocked */
        while (CDD_IPC_LOCK == gIpcTransferMutex[gRemoteCoreId[i]])
            ;
        numRemoteCores++;
    }
    if (retval == E_OK)
    {
        AppUtils_printf(APP_NAME ": All echoed messages received by main core from %d remote cores !!!\r\n",
                        numRemoteCores);
        AppUtils_printf(APP_NAME ": Messages sent to each core = %d \r\n", gMsgEchoCount);
        AppUtils_printf(APP_NAME ": Number of remote cores = %d \r\n", numRemoteCores);
        AppUtils_printf("All tests have passed\n\r");
    }
    else
    {
        AppUtils_printf(APP_NAME ": All echoed messages not transmitted by main core from remote cores !!!\r\n");
    }
#if (STD_ON == CDD_IPC_RPMSG_ENABLE_API)
    Cdd_Ipc_Destruct(CddIpcConf_CddIpclocalEndPt_CddIpcEndPtConfig_0);
#endif

#if (STD_ON == CDD_IPC_DEINIT_API)
    Cdd_Ipc_DeInit(&Cdd_Ipc_Config);
#endif

    AppUtils_TimerDeinit();

    return (0);
}

#if (STD_OFF == CDD_IPC_RPMSG_CALLBACK_ENABLE)
void Callback(void *handle, Cdd_Ipc_RPMessage_EpObject *epObj, void *args, void *data, uint16 dataLen, sint32 crc,
              uint16 remoteCoreId, uint16 remoteEndPt)
{
    /* Callback */
}
#endif

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
