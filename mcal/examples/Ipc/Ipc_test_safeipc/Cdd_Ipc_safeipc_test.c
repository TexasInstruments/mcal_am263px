/**
 *  \file     Cdd_Ipc_safeipc_test.c
 *
 *  \brief    This file contains the IPC R52 test app for safeipc
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
#include <stdio.h>
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

static void IpcApp_platformInit(void);

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

#define MAX_MSG_SIZE (64U)

uint16 remoteCoreId, remoteCoreEndPt, recvMsgSize;

char recvMsg[MAX_MSG_SIZE];

extern uint32 gRemoteCoreId[];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Entry point of example */
int main(void)
{
    Cdd_Ipc_App_Startup();

    Cdd_Ipc_App_PlatformInit();

    Cdd_Ipc_Init(&CddIpcDriver_0);

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
    Cdd_Ipc_Construct(&CddIpcDriver_0);
#endif

    /* Interrupt Configuration (Registering Interrupt to R5 core, ISR) */
    /* Do this after Cdd_Ipc_Init is done because ISR can get triggerred due to SyncAll from Other
    core and lead to data abort due to Un-initialized IPC handles*/
    Cdd_Ipc_InterruptConfig();

    Cdd_Ipc_Notify_Sync_All();

    while (1)
    {
        recvMsgSize = sizeof(recvMsg);
        Cdd_Ipc_RpMsg_RecvMsg(recvMsg, &recvMsgSize, CddIpcConf_CddIpclocalEndPt_CddIpcEndPtConfig_0, &remoteCoreId,
                              &remoteCoreEndPt, CDD_IPC_TIMEOUT);

        Cdd_Ipc_RpMsg_SendMsg(recvMsg, recvMsgSize, remoteCoreId, remoteCoreEndPt,
                              CddIpcConf_CddIpclocalEndPt_CddIpcEndPtConfig_0, CDD_IPC_TIMEOUT);
    }
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
