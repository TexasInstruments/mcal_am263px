/*
 *  Copyright (C) 2023-2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ipc_notify_lld_utils.h"

static boolean IpcNotifyUtils_lld_waitSync_msgPend(IpcNotifyUtils_Handle hIpcNotifyUtils, sint32 *statusLocal,
                                                   uint32 remoteCoreId, boolean Done, uint32 timeout,
                                                   uint32 startTicks);

#define CDD_IPC_START_SEC_CODE
#include "Cdd_Ipc_MemMap.h"

sint32 IpcNotifyUtils_lld_init(IpcNotifyUtils_Handle hIpcNotifyUtils)
{
    uint32 core;
    sint32 status = MCAL_SystemP_FAILURE;

    for (core = 0; core < MCAL_CSL_CORE_ID_MAX; core++)
    {
        hIpcNotifyUtils->syncMsgPend[core] = 0;
    }

    status = IpcNotify_lld_registerClient(hIpcNotifyUtils->hIpcNotifyUtilsInit->hIpcNotify, IPC_NOTIFY_CLIENT_ID_SYNC,
                                          IpcNotifyUtils_lld_syncCallback, hIpcNotifyUtils);

    return status;
}

void IpcNotifyUtils_lld_syncCallback(void *hIpcNotify, uint32 remoteCoreId, uint16 localClientId, uint32 msgValue,
                                     uint32 timeout, sint32 crcStatus, void *args)
{
    IpcNotifyUtils_Handle hIpcNotifyUtils = (IpcNotifyUtils_Handle)args;

    if (remoteCoreId < MCAL_CSL_CORE_ID_MAX)
    {
        hIpcNotifyUtils->syncMsgPend[remoteCoreId]++;
    }
}

sint32 IpcNotifyUtils_lld_sendSync(IpcNotifyUtils_Handle hIpcNotifyUtils, uint32 remoteCoreId)
{
    return IpcNotify_lld_sendMsg(hIpcNotifyUtils->hIpcNotifyUtilsInit->hIpcNotify, remoteCoreId,
                                 IPC_NOTIFY_CLIENT_ID_SYNC, 0xFF, /* message value is dont care */
                                 1 /* wait for messahe to be put in the HwFifo */, CDD_IPC_TIMEOUT);
}

sint32 IpcNotifyUtils_lld_waitSync(IpcNotifyUtils_Handle hIpcNotifyUtils, uint32 remoteCoreId, uint32 timeout)
{
    sint32  status = MCAL_SystemP_FAILURE;
    uint32  startTicks;
    boolean isDone;
    uint32  isCoreEnabled = 0;

    isCoreEnabled = IpcNotify_lld_isCoreEnabled(hIpcNotifyUtils->hIpcNotifyUtilsInit->hIpcNotify, remoteCoreId);

    if ((remoteCoreId < MCAL_CSL_CORE_ID_MAX) && (isCoreEnabled != 0U))
    {
        startTicks          = Cdd_Ipc_Clock_getTicks();
        sint32 *statusLocal = &status;
        isDone              = FALSE;
        while (isDone == FALSE)
        {
            isDone = IpcNotifyUtils_lld_waitSync_msgPend(hIpcNotifyUtils, statusLocal, remoteCoreId, isDone, timeout,
                                                         startTicks);
        }
    }
    return status;
}

sint32 IpcNotifyUtils_lld_syncAll(IpcNotifyUtils_Handle hIpcNotifyUtils, uint32 timeout)
{
    sint32 status = MCAL_SystemP_SUCCESS;
    uint32 remoteCoreId;
    uint32 isCoreEnabled = 0U;

    for (remoteCoreId = 0U; remoteCoreId < MCAL_CSL_CORE_ID_MAX; remoteCoreId++)
    {
        isCoreEnabled = IpcNotify_lld_isCoreEnabled(hIpcNotifyUtils->hIpcNotifyUtilsInit->hIpcNotify, remoteCoreId);

        if (isCoreEnabled != 0U)
        {
            /* no need to check return status, this will always pass */
            IpcNotifyUtils_lld_sendSync(hIpcNotifyUtils, remoteCoreId);
        }
    }
    for (remoteCoreId = 0U; remoteCoreId < MCAL_CSL_CORE_ID_MAX; remoteCoreId++)
    {
        isCoreEnabled = IpcNotify_lld_isCoreEnabled(hIpcNotifyUtils->hIpcNotifyUtilsInit->hIpcNotify, remoteCoreId);

        if (isCoreEnabled != 0U)
        {
            status = IpcNotifyUtils_lld_waitSync(hIpcNotifyUtils, remoteCoreId, timeout);
            if (status != MCAL_SystemP_SUCCESS)
            {
                break;
            }
        }
    }
    return status;
}

static boolean IpcNotifyUtils_lld_waitSync_msgPend(IpcNotifyUtils_Handle hIpcNotifyUtils, sint32 *statusLocal,
                                                   uint32 remoteCoreId, boolean Done, uint32 timeout, uint32 startTicks)
{
    uint32  elapsedTicks, tempTicks;
    boolean isDone = Done;
    if (hIpcNotifyUtils->syncMsgPend[remoteCoreId] == 0U)
    {
        tempTicks = startTicks;
        GetElapsedValue(CDD_IPC_OS_COUNTER_ID, &tempTicks, &elapsedTicks);
        if (elapsedTicks >= timeout)
        {
            *statusLocal = MCAL_SystemP_TIMEOUT;
            isDone       = TRUE;
        }
        else
        {
            /* check again after 1 tick  */
            Cdd_Ipc_Clock_uSleep(Cdd_Ipc_Clock_ticksToUsec(1));
        }
    }
    else
    {
        hIpcNotifyUtils->syncMsgPend[remoteCoreId]--;

        *statusLocal = MCAL_SystemP_SUCCESS;
        isDone       = TRUE;
    }
    return isDone;
}
#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
