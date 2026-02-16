/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2024 Texas Instruments Incorporated
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

#include "ipc_notify_lld_utils.h"
#include "sys_pmu.h"

static boolean IpcNotifyUtils_lld_waitSync_msgPend(IpcNotifyUtils_Handle hIpcNotifyUtils, sint32 *statusLocal,
                                                   uint32 remoteCoreId, uint32 timeout, uint32 startTicks);

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
    IpcNotify_MsgParams msgParams;

    msgParams.remoteCoreId       = remoteCoreId;
    msgParams.remoteClientId     = IPC_NOTIFY_CLIENT_ID_SYNC;
    msgParams.messageValue       = 0xFFU; /* message value is don't care */
    msgParams.waitForFifoNotFull = 1U;    /* wait for message to be put in the HwFifo */
    msgParams.timeout            = CDD_IPC_TIMEOUT;

    return IpcNotify_lld_sendMsg(hIpcNotifyUtils->hIpcNotifyUtilsInit->hIpcNotify, &msgParams);
}

sint32 IpcNotifyUtils_lld_waitSync(IpcNotifyUtils_Handle hIpcNotifyUtils, uint32 remoteCoreId, uint32 timeout)
{
    sint32  status        = MCAL_SystemP_FAILURE;
    uint32  startTicks    = 0U;
    boolean isDone        = FALSE;
    uint32  isCoreEnabled = 0U;

    isCoreEnabled = IpcNotify_lld_isCoreEnabled(hIpcNotifyUtils->hIpcNotifyUtilsInit->hIpcNotify, remoteCoreId);

    if ((remoteCoreId < MCAL_CSL_CORE_ID_MAX) && (isCoreEnabled != 0U))
    {
        Mcal_GetCycleCounterValue(&startTicks);

        while (isDone == FALSE)
        {
            isDone = IpcNotifyUtils_lld_waitSync_msgPend(hIpcNotifyUtils, &status, remoteCoreId, timeout, startTicks);
        }
    }
    else
    {
        status = MCAL_SystemP_INVALID_PARAM;
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
                                                   uint32 remoteCoreId, uint32 timeout, uint32 startTicks)
{
    uint32  elapsedTicks = 0U, tempTicks = 0U;
    boolean isDone = FALSE;

    if (hIpcNotifyUtils->syncMsgPend[remoteCoreId] == 0U)
    {
        tempTicks = startTicks;
        Mcal_GetElapsedCycleCountValue(&tempTicks, &elapsedTicks);

        if (elapsedTicks >= timeout)
        {
            *statusLocal = MCAL_SystemP_TIMEOUT;
            isDone       = TRUE;
        }
        else
        {
            /* check again after 1 tick  */
            Cdd_Ipc_Clock_uSleep(Cdd_Ipc_Clock_ticksToUsec(1U));
        }
    }
    else
    {
        SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();
        hIpcNotifyUtils->syncMsgPend[remoteCoreId]--;
        SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0();

        *statusLocal = MCAL_SystemP_SUCCESS;
        isDone       = TRUE;
    }
    return isDone;
}
#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
