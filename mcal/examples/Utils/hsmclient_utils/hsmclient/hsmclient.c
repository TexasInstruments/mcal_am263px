/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <sipc_notify.h>
#include <SemaphoreP.h>
#include <SystemP.h>
#include <CacheP.h>
// #include <drivers/hw_include/cslr_soc.h>
#include <HwiP.h>
#include <hsmclient.h>
#include <hsmclient_msg.h>
// #include <drivers/soc.h>
#include <string.h>
// #include <kernel/dpl/DebugP.h>

// void Hsmclient_updateBootNotificationRegister(void);

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * @brief
 *        Macro calculates the cache-aligned size for a given buffer or data structure
 */
#define GET_CACHE_ALIGNED_SIZE(x) ((x + Mcal_CacheP_CACHELINE_ALIGNMENT) & ~(Mcal_CacheP_CACHELINE_ALIGNMENT - 1U))

/**
 * @brief
 *        Maximum size of the HSM client message queue
 *        For Streaming Secure Boot, the break up is as follows,
 *        1 start message (includes the certificate) +
 *        1 finish message +
 *        1 ELF Header Buffer update message + 1 PHT Buffer update message
 *        1024 ELF segment update messages (including the two note segments)
 *          - PT note for boot sequence info
 *          - PT note containing Random string for decryption verification
 */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* This variable indicates HSM Runtime load status */
volatile uint32_t gHsmrtLoadStatus = HSMRT_LOAD_NOT_REQUESTED;

/* This variable indicates Secure Boot status */
static volatile int32_t gSecureBootStatus = SystemP_SUCCESS;

/* This variable indicates whether Boot notification is received or not */
static volatile int32_t gBootNotificationReceived = SystemP_FAILURE;

static int32_t          gLastSentIndex           = -1;
static int32_t          gLastEnqueuedIndex       = -1;
static int32_t          gNum_HsmRequestSent      = 0;
static volatile int32_t gNum_HsmResponseReceived = 0;
/** Default HSM client message queue size */
#ifndef HSM_CLIENT_MSG_QUEUE_SIZE
#define HSM_CLIENT_MSG_QUEUE_SIZE (64U)
#endif

static uint32_t hsm_client_msg_queue_size = HSM_CLIENT_MSG_QUEUE_SIZE;

/* Queue used to store HSM client messages that need to be dispatched via SIPC */
extern HsmMsg_t gHsmClientMsgQueue[HSM_CLIENT_MSG_QUEUE_SIZE];

/*==========================================================================
 *                        Static Function Declarations
 *==========================================================================*/

/**
 * @brief
 *        Calculate crc16_ccit for a given data.
 * @param data data pointer
 * @param length data length
 * @return 16 bit crc calculated from given data.
 */
static uint16_t crc16_ccit(uint8_t *data, uint16_t length);

/**
 * @brief
 *      Generic send and receive message api
 * @param HsmClient client type
 * @param timeout time to wait for interrupt from HSM before throwing timeout
 *                exception.
 * @return SystemP_SUCCESS if transaction is successful else SystemP_FAILURE.
 */
static int32_t HsmClient_SendAndRecv(HsmClient_t *HsmClient, uint32_t timeout);

/**
 * @brief
 *      Generic send message api which enqueus the message in HSM client message
 *      queue and tries to send the message via SIPC.
 *      This API is non blocking in nature.
 * @param message message that needs to be sent to the HSM core.
 * @return SystemP_SUCCESS if transaction is successful else SystemP_FAILURE.
 */
static int32_t HsmClient_EnqueueAndSendMsg(HsmMsg_t hsmMessage);

/**
 * @brief
 *      Generic send message api which enqueus the message in HSM client message
 *      queue and ensures all the messages present in the queue are sent via SIPC.
 *      This API is blocking in nature.
 * @param message message that needs to be sent to the HSM core
 * @return SystemP_SUCCESS if transaction is successful else SystemP_FAILURE.
 */
static int32_t HsmClient_EnqueueAndSendMsgBlocking(HsmMsg_t hsmMessage);

/**
 * @brief
 *      Generic api which waits for all responses to be received
 * @return SystemP_SUCCESS if all responses are successful else SystemP_FAILURE.
 */
static int32_t HsmClient_waitForAllResponses(void);

/*==============================================================================*
 *                          Static Functions definition.
 *==============================================================================*/

/* CRC 16 CCIT soft implementation */
static uint16_t crc16_ccit(uint8_t *data, uint16_t length)
{
    uint8_t  x;
    uint16_t crc         = 0xFFFF;
    uint8_t *localData   = data;
    uint16_t localLength = length;

    while (localLength > 0U)
    {
        x    = ((crc >> 8) ^ (*localData));
        x   ^= (x >> 4);
        crc  = ((crc << 8) ^ ((uint16_t)((uint16_t)x << 12))) ^ ((uint16_t)((uint16_t)x << 5)) ^ ((uint16_t)x);
        localData++;
        localLength--;
    }
    return crc;
}

static int32_t HsmClient_EnqueueAndSendMsg(HsmMsg_t hsmMessage)
{
    int32_t  status         = SystemP_FAILURE;
    uint8_t  localClientId  = hsmMessage.srcClientId;
    uint8_t  remoteClientId = hsmMessage.destClientId;
    HsmMsg_t localMessage   = hsmMessage;
    uint8_t  loopBreak      = 0U;

    localMessage.crcMsg = crc16_ccit((uint8_t *)&localMessage, (sizeof(HsmMsg_t) - 2U));

    if (gLastEnqueuedIndex < (((int32_t)hsm_client_msg_queue_size) - 1))
    {
        gLastEnqueuedIndex++;
        gHsmClientMsgQueue[gLastEnqueuedIndex] = localMessage;

        /* Till the boot notify is not received, simply enqueue the message */
        if (gBootNotificationReceived == SystemP_SUCCESS)
        {
            while ((gSecureBootStatus == SystemP_SUCCESS) && (gLastSentIndex < gLastEnqueuedIndex))
            {
                /*
                    Do not wait in case the SIPC software Queue is full and simply abort with error.
                    This is done in order to make this call non blocking.
                */
                status = SIPC_sendMsg(CORE_INDEX_HSM, remoteClientId, localClientId,
                                      (uint8_t *)&gHsmClientMsgQueue[gLastSentIndex + 1], ABORT_ON_FIFO_FULL);

                /* Successfully able to send the message via SIPC */
                if (status == SystemP_SUCCESS)
                {
                    gNum_HsmRequestSent++;
                    gLastSentIndex++;
                }
                /*
                    Failed to send the message because the SIPC Software FIFO is full.
                    Retry in the next call to this function or in the finish call.
                */
                else if (status == SystemP_FAILURE)
                {
                    status    = SystemP_SUCCESS;
                    loopBreak = 1U;
                }
                else
                {
                    status    = SystemP_FAILURE;
                    loopBreak = 1U;
                }

                if (loopBreak == 1U)
                {
                    break;
                }
            }
        }
        else
        {
            status = SystemP_SUCCESS;
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t HsmClient_EnqueueAndSendMsgBlocking(HsmMsg_t hsmMessage)
{
    int32_t  status         = SystemP_FAILURE;
    uint8_t  localClientId  = hsmMessage.srcClientId;
    uint8_t  remoteClientId = hsmMessage.destClientId;
    HsmMsg_t localMessage   = hsmMessage;

    localMessage.crcMsg = crc16_ccit((uint8_t *)&localMessage, (sizeof(HsmMsg_t) - 2U));

    if (gLastEnqueuedIndex < (((int32_t)hsm_client_msg_queue_size) - 1))
    {
        gLastEnqueuedIndex++;
        gHsmClientMsgQueue[gLastEnqueuedIndex] = localMessage;

        /*
            If the boot notification is not received, we wait for it indefinitely
            and once it arrives we begin sending our request packets.
        */
        status = HsmClient_checkAndWaitForBootNotification();

        if (status == SystemP_SUCCESS)
        {
            while ((gSecureBootStatus == SystemP_SUCCESS) && (gLastSentIndex < gLastEnqueuedIndex))
            {
                /*
                    In this call, we want to wait in case the SIPC software Queue is full
                    and we simply abort with error. This is done in order to make sure that
                    all the requests to HSM are sent in order.
                */
                status = SIPC_sendMsg(CORE_INDEX_HSM, remoteClientId, localClientId,
                                      (uint8_t *)&gHsmClientMsgQueue[gLastSentIndex + 1], WAIT_IF_FIFO_FULL);

                if (status == SystemP_SUCCESS)
                {
                    gNum_HsmRequestSent++;
                    gLastSentIndex++;
                }
                else
                {
                    status = SystemP_FAILURE;
                    break;
                }
            }
        }
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t HsmClient_waitForAllResponses(void)
{
    int32_t bootStatus  = gSecureBootStatus;
    int32_t numReceived = gNum_HsmResponseReceived;
    int32_t numSent     = gNum_HsmRequestSent;

    while ((bootStatus == SystemP_SUCCESS) && (numReceived < numSent))
    {
        bootStatus  = gSecureBootStatus;
        numReceived = gNum_HsmResponseReceived;
        numSent     = gNum_HsmRequestSent;
    }

    return gSecureBootStatus;
}

static int32_t HsmClient_SendAndRecv(HsmClient_t *HsmClient, uint32_t timeout)
{
    uint8_t  localClientId;
    uint8_t  remoteClientId;
    int32_t  status;
    uint16_t crcMsg;

    localClientId  = HsmClient->ReqMsg.srcClientId;
    remoteClientId = HsmClient->ReqMsg.destClientId;

    /* Add message crc. Exclude crcMsg argument of HsmMsg_t from crc calculations*/
    HsmClient->ReqMsg.crcMsg = crc16_ccit((uint8_t *)&HsmClient->ReqMsg, (sizeof(HsmMsg_t) - 2U));

    status =
        SIPC_sendMsg(CORE_INDEX_HSM, remoteClientId, localClientId, (uint8_t *)&HsmClient->ReqMsg, WAIT_IF_FIFO_FULL);
    if (status == SystemP_SUCCESS)
    {
        status = SemaphoreP_pend(&HsmClient->Semaphore, timeout);
        if (status == SystemP_FAILURE)
        {
            /* Status is already set to SystemP_FAILURE */
        }
        else if (status == SystemP_TIMEOUT)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Timeout exception \r\n");
            /* Status is already set to SystemP_TIMEOUT */
        }
        else
        {
            crcMsg = crc16_ccit((uint8_t *)&HsmClient->RespMsg, SIPC_MSG_SIZE - 2U);
            /* if the message is okay then send whatever the flag receive */
            if (crcMsg == HsmClient->RespMsg.crcMsg)
            {
                HsmClient->RespFlag = HsmClient->RespMsg.flags;
                status              = SystemP_SUCCESS;
            }
            /* corrupted message received */
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] Corrupted message received \r\n");
                HsmClient->RespFlag = HSM_FLAG_NACK;
                status              = SystemP_FAILURE;
            }
        }
    }

    return status;
}

/*==============================================================================*
 *                          Public Function definition.
 *==============================================================================*/

void HsmClient_isr(uint8_t remoteCoreId, uint8_t localClientId, uint8_t remoteClientId, uint8_t *msgValue, void *args)
{
    HsmClient_t *HsmClient = (HsmClient_t *)args;

    /* here we will just post the semaphore */
    /* copy message to client response variable */
    /* As this ISR is blocking, quickly copy the message and exit ISR */
    /* MISRA-C:2012 AMD1 Rule 21.16 - Ensure type compatibility for memcpy */
    (void)memcpy((void *)&HsmClient->RespMsg, (void const *)msgValue, SIPC_MSG_SIZE);

    /* Check if HSM response message is not related to proc_auth_boot
     * proc_auth_boot APIs use HsmClient_EnqueueAndSendMsg() or HsmClient_EnqueueAndSendMsgBlocking()
     * Others use HsmClient_SendAndRecv()
     * If true, post the semaphore to signal completion
     */
    if ((HsmClient->RespMsg.serType != (uint16_t)HSM_MSG_PROC_AUTH_BOOT_START) &&  /* Not proc_auth_boot auth start */
        (HsmClient->RespMsg.serType != (uint16_t)HSM_MSG_PROC_AUTH_BOOT_UPDATE) && /* Not proc_auth_boot auth update */
        (HsmClient->RespMsg.serType != (uint16_t)HSM_MSG_PROC_AUTH_BOOT_FINISH))   /* Not proc_auth_boot auth finish */
    {
        SemaphoreP_post(&HsmClient->Semaphore);
    }

    /*
        Analyze the received response packet.
    */
    if (HsmClient->RespMsg.serType == (uint16_t)HSM_MSG_BOOT_NOTIFY)
    {
        gBootNotificationReceived = SystemP_SUCCESS;
        gSecureBootStatus         = SystemP_SUCCESS;

        // Hsmclient_updateBootNotificationRegister();
    }
    else
    {
        if (gSecureBootStatus == SystemP_SUCCESS)
        {
            /* gNum_HsmResponseReceived must only be incremented if
             * the call is non-blocking which is valid only for PROC_AUTH
             * (START, UPDATE, FINISH).
             */
            if ((HsmClient->RespMsg.serType == (uint16_t)HSM_MSG_PROC_AUTH_BOOT_START) ||
                (HsmClient->RespMsg.serType == (uint16_t)HSM_MSG_PROC_AUTH_BOOT_UPDATE) ||
                (HsmClient->RespMsg.serType == (uint16_t)HSM_MSG_PROC_AUTH_BOOT_FINISH))
            {
                /* MISRA-C:2012 Rule 13.3 - Increment in separate statement */
                gNum_HsmResponseReceived = gNum_HsmResponseReceived + (int32_t)1;
            }
            if (HsmClient->RespMsg.flags == (uint8_t)HSM_FLAG_NACK)
            {
                gSecureBootStatus = SystemP_FAILURE;
            }
            else if (HsmClient->RespMsg.flags == (uint8_t)HSM_FLAG_ACK)
            {
                gSecureBootStatus = SystemP_SUCCESS;
            }
            else
            {
                gSecureBootStatus = SystemP_FAILURE;
            }
        }
        else
        {
            gSecureBootStatus = SystemP_FAILURE;
        }
    }
}

int32_t HsmClient_checkAndWaitForBootNotification(void)
{
    int32_t status = SystemP_FAILURE;

    if (gHsmrtLoadStatus == HSMRT_LOAD_NOT_REQUESTED)
    {
        /*
           If HSM Runtime load is not requested up till now,
           just return Success.
       */
        status = SystemP_SUCCESS;
    }
    else if (gHsmrtLoadStatus == HSMRT_LOAD_REQUESTED)
    {
        /* Only wait if HSM Runtime load is requested up till now. */
        while (gHsmrtLoadStatus == HSMRT_LOAD_REQUESTED)
        {
        }

        if (gHsmrtLoadStatus == HSMRT_LOAD_SUCCEEDED)
        {
            /* Only wait for Boot notification HSM Runtime load is successful */
            while (gBootNotificationReceived == SystemP_FAILURE)
            {
            }
            status = SystemP_SUCCESS;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }
    else if (gHsmrtLoadStatus == HSMRT_LOAD_FAILED)
    {
        status = SystemP_FAILURE;
    }
    else if (gHsmrtLoadStatus == HSMRT_LOAD_SUCCEEDED)
    {
        /* Only wait for Boot notification HSM Runtime load is successful */
        while (gBootNotificationReceived == SystemP_FAILURE)
        {
        }
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

/* return SystemP_FAILURE if clientId is greater the max or
 * A callback has been registered. already */
int32_t HsmClient_register(HsmClient_t *HsmClient, uint8_t clientId)
{
    int32_t status;

    if (HsmClient == NULL_PTR)
    {
        AppUtils_printf(" \r\n [HSM_CLIENT] HsmClient_t type error. \r\n");
        status = SystemP_FAILURE;
    }
    else
    {
        HsmClient->ClientId = clientId;

        /* register HSM_Isr and pass the pointer as args */
        status = SIPC_registerClient(clientId, HsmClient_isr, (void *)HsmClient);
        if (status == SystemP_SUCCESS)
        {
            SemaphoreP_constructBinary(&HsmClient->Semaphore, 0);
            AppUtils_printf("\r\n [HSM_CLIENT] New Client Registered with Client Id = %d\r\n ", clientId);
        }
        else
        {
            AppUtils_printf(" \r\n [HSM_CLIENT] Client already registered or Invalid ClientId\r\n");
        }
    }

    return status;
}

int32_t HsmClient_init(SIPC_Params *params)
{
    /* get the params and do SIPC init */
    int32_t  status;
    uint32_t selfCoreId;
    status = SIPC_init(params);
    /* TODO: keyrings initialization */
    if (status == SystemP_FAILURE)
    {
        selfCoreId = SIPC_getSelfCoreId();
        AppUtils_printf("[HSM_CLIENT] Secure Host initialization failed for R5F%d \r\n", selfCoreId);
    }
    return status;
}

void HsmClient_SecureBootQueueInit(uint32_t configured_hsm_client_msg_queue_size)
{
    /* Customize the size of the HSM client message queue*/
    hsm_client_msg_queue_size = configured_hsm_client_msg_queue_size;
}

/* do sipc deinit */
void HsmClient_deinit(void)
{
    SIPC_deInit();
}

void HsmClient_unregister(HsmClient_t *HsmClient, uint8_t clientId)
{
    /* unregister a client */
    SIPC_unregisterClient(clientId);
}

int32_t HsmClient_getVersion(HsmClient_t *HsmClient, HsmVer_t *hsmVer, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_VERSION;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)hsmVer, sizeof(HsmVer_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(hsmVer);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
       Write back the HsmVer struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(hsmVer, GET_CACHE_ALIGNED_SIZE(sizeof(HsmVer_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);

    if (status == SystemP_SUCCESS)
    {
        /* the hsmVer has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Get version request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), sizeof(HsmVer_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for getversion response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getUID(HsmClient_t *HsmClient, uint8_t *uid, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_UID;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)uid, HSM_UID_SIZE);

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(uid);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
       Write back the uid and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(uid, GET_CACHE_ALIGNED_SIZE(sizeof(uid)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the getUID has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Get UID request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, HSM_UID_SIZE);
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for getUID response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_openDbgFirewall(HsmClient_t *HsmClient, uint8_t *cert, uint32_t cert_size, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_OPEN_DBG_FIREWALLS;
    HsmClient->ReqMsg.args    = (void *)cert;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(cert);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
       Write back the debug cert and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] OpenDbgFirewall request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for openDbgFirewall response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_importKeyring(HsmClient_t *HsmClient, uint8_t *cert, uint32_t cert_size, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_KEYRING_IMPORT;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(cert);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
       Write back the keyring cert and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Import Keyring request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for Import Keyring response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_readOTPRow(HsmClient_t *HsmClient, NvmOtpRead_t *readRow)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_READ_OTP_ROW;
    uint64_t tempPhyAddr      = SOC_virtToPhy(readRow);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)readRow, sizeof(NvmOtpRead_t));

    /*
       Write back the EfuseRead struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(readRow, GET_CACHE_ALIGNED_SIZE(sizeof(NvmOtpRead_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Read OTP row request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(NvmOtpRead_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for read OTP Row response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_writeOTPRow(HsmClient_t *HsmClient, NvmOtpRowWrite_t *writeRow)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_WRITE_OTP_ROW;
    uint64_t tempPhyAddr      = SOC_virtToPhy(writeRow);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)writeRow, sizeof(NvmOtpRowWrite_t));

    /*
       Write back the EfuseRowWrite struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(writeRow, GET_CACHE_ALIGNED_SIZE(sizeof(NvmOtpRowWrite_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the extended otp row has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Write OTP row request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(NvmOtpRowWrite_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for Write OTP row response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_lockOTPRow(HsmClient_t *HsmClient, NvmOtpRowProt_t *protRow)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_PROT_OTP_ROW;
    uint64_t tempPhyAddr      = SOC_virtToPhy(protRow);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)protRow, sizeof(NvmOtpRowProt_t));

    /*
       Write back the EfuseRowProt struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(protRow, GET_CACHE_ALIGNED_SIZE(sizeof(NvmOtpRowProt_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the row is locked by HSM server if this
         * request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Extended OTP row protection request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(NvmOtpRowProt_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for extended OTP row protection response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getOTPRowCount(HsmClient_t *HsmClient, NvmOtpRowCount_t *rowCount)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_OTP_ROW_COUNT;
    uint64_t tempPhyAddr      = SOC_virtToPhy(rowCount);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)rowCount, sizeof(NvmOtpRowCount_t));

    /*
       Write back the EfuseRowCount struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(rowCount, GET_CACHE_ALIGNED_SIZE(sizeof(NvmOtpRowCount_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the rowCount has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Get OTP row count request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(NvmOtpRowCount_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for get OTP Row count response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getOTPRowProtection(HsmClient_t *HsmClient, NvmOtpRowProt_t *rowProt)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_OTP_ROW_PROT;
    uint64_t tempPhyAddr      = SOC_virtToPhy(rowProt);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)rowProt, sizeof(NvmOtpRowProt_t));

    /*
       Write back the EfuseRowProt struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(rowProt, GET_CACHE_ALIGNED_SIZE(sizeof(NvmOtpRowProt_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the rowProt has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Get OTP row protection request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(NvmOtpRowProt_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for get OTP Row protection response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_procAuthBoot(HsmClient_t *HsmClient, uint8_t *cert, uint32_t cert_size, uint32_t timeout)
{
    /* make the message */
    int32_t  status = SystemP_FAILURE;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_PROC_AUTH_BOOT;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(cert);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
        Write back the cert and
        invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Proc_Auth_Boot request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for Proc_Auth_Boot response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_procAuthBootStart(HsmClient_t *HsmClient, SecureBoot_Stream_t *secureBootInfo)
{
    int32_t  status = SystemP_FAILURE;
    /* Create the message object */
    HsmMsg_t startMsg;

    /*populate the send message structure */
    startMsg.destClientId = HSM_CLIENT_ID_1;
    startMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    startMsg.flags   = HSM_FLAG_AOP;
    startMsg.serType = HSM_MSG_PROC_AUTH_BOOT_START;
    startMsg.args    = (void *)secureBootInfo;

    /* Add arg crc */
    startMsg.crcArgs = crc16_ccit((uint8_t *)secureBootInfo, sizeof(SecureBoot_Stream_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t startPhyAddr = SOC_virtToPhy(secureBootInfo);
    startMsg.args         = (void *)(uint32_t *)(uintptr_t)startPhyAddr;

    /*
       Write back secure boot info object  and the data it contains
       to Shared memory invalidate the caches before passing it to HSM
    */
    Mcal_CacheP_wbInv(secureBootInfo->dataIn, GET_CACHE_ALIGNED_SIZE(secureBootInfo->dataLen), Mcal_CacheP_TYPE_ALLD);
    Mcal_CacheP_wbInv(secureBootInfo, GET_CACHE_ALIGNED_SIZE(sizeof(SecureBoot_Stream_t)), Mcal_CacheP_TYPE_ALLD);

    status = HsmClient_EnqueueAndSendMsg(startMsg);

    return status;
}

int32_t HsmClient_procAuthBootUpdate(HsmClient_t *HsmClient, SecureBoot_Stream_t *secureBootInfo)
{
    int32_t  status = SystemP_FAILURE;
    /* Create the message object */
    HsmMsg_t updateMsg;

    /*populate the send message structure */
    updateMsg.destClientId = HSM_CLIENT_ID_1;
    updateMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    updateMsg.flags   = HSM_FLAG_AOP;
    updateMsg.serType = HSM_MSG_PROC_AUTH_BOOT_UPDATE;
    updateMsg.args    = (void *)secureBootInfo;

    /* Add arg crc */
    updateMsg.crcArgs = crc16_ccit((uint8_t *)secureBootInfo, sizeof(SecureBoot_Stream_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t updatePhyAddr = SOC_virtToPhy(secureBootInfo);
    updateMsg.args         = (void *)(uint32_t *)(uintptr_t)updatePhyAddr;

    /*
       Write back secure boot info object to Shared memory
       invalidate the caches before passing it to HSM
    */
    Mcal_CacheP_wbInv(secureBootInfo, GET_CACHE_ALIGNED_SIZE(sizeof(SecureBoot_Stream_t)), Mcal_CacheP_TYPE_ALLD);

    status = HsmClient_EnqueueAndSendMsg(updateMsg);

    return status;
}

int32_t HsmClient_procAuthBootFinish(HsmClient_t *HsmClient, SecureBoot_Stream_t *secureBootInfo)
{
    int32_t  status = SystemP_FAILURE;
    /* Create the message object */
    HsmMsg_t finishMsg;

    /*populate the send message structure */
    finishMsg.destClientId = HSM_CLIENT_ID_1;
    finishMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    finishMsg.flags   = HSM_FLAG_AOP;
    finishMsg.serType = HSM_MSG_PROC_AUTH_BOOT_FINISH;
    finishMsg.args    = (void *)secureBootInfo;

    /* Add arg crc */
    finishMsg.crcArgs = crc16_ccit((uint8_t *)secureBootInfo, sizeof(SecureBoot_Stream_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t finishPhyAddr = SOC_virtToPhy(secureBootInfo);
    finishMsg.args         = (void *)(uint32_t *)(uintptr_t)finishPhyAddr;

    /*
       Write back secure boot info object to Shared memory
       invalidate the caches before passing it to HSM
    */
    Mcal_CacheP_wbInv(secureBootInfo, GET_CACHE_ALIGNED_SIZE(sizeof(SecureBoot_Stream_t)), Mcal_CacheP_TYPE_ALLD);

    status = HsmClient_EnqueueAndSendMsgBlocking(finishMsg);

    if (status == SystemP_SUCCESS)
    {
        status = HsmClient_waitForAllResponses();
    }

    return status;
}

int32_t HsmClient_setFirewall(HsmClient_t *HsmClient, FirewallReq_t *FirewallReqObj, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint16_t crcFirewallRegionArr;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_SET_FIREWALL;
    uint64_t tempPhyAddr      = SOC_virtToPhy(FirewallReqObj);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Calculates CRC of the array containing firewall regions to be configured */
    crcFirewallRegionArr              = crc16_ccit((uint8_t *)FirewallReqObj->FirewallRegionArr,
                                                   ((FirewallReqObj->regionCount) * sizeof(FirewallRegionReq_t)));
    FirewallReqObj->crcArr            = crcFirewallRegionArr;
    uint64_t firewallRegionArrPhy     = SOC_virtToPhy(FirewallReqObj->FirewallRegionArr);
    FirewallReqObj->FirewallRegionArr = (FirewallRegionReq_t *)(uint32_t *)(uintptr_t)firewallRegionArrPhy;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)FirewallReqObj, sizeof(FirewallReq_t));

    /*
       Write back the FirewallReqObj and FirewallRegionArr
    */
    Mcal_CacheP_wbInv((void *)FirewallReqObj, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallReq_t)), Mcal_CacheP_TYPE_ALL);
    Mcal_CacheP_wbInv((void *)FirewallReqObj->FirewallRegionArr,
                      GET_CACHE_ALIGNED_SIZE(((FirewallReqObj->regionCount) * sizeof(FirewallRegionReq_t))),
                      Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the firewall regions has been configured by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Set firewall request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            Mcal_CacheP_inv((void *)HsmClient->RespMsg.args, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallReq_t)),
                            Mcal_CacheP_TYPE_ALL);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(FirewallReq_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for set firewall response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_FirewallIntr(HsmClient_t *HsmClient, FirewallIntrReq_t *FirewallIntrReqObj, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_SET_FIREWALL_INTR;
    uint64_t tempPhyAddr      = SOC_virtToPhy(FirewallIntrReqObj);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)FirewallIntrReqObj, sizeof(FirewallIntrReq_t));

    /*
       Write back the FirewallIntrReq_t struct
    */
    Mcal_CacheP_wbInv((void *)FirewallIntrReqObj, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallIntrReq_t)),
                      Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the firewall interrupt request has been honored by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] firewall interrupt request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            Mcal_CacheP_inv((void *)HsmClient->RespMsg.args, GET_CACHE_ALIGNED_SIZE(sizeof(FirewallIntrReq_t)),
                            Mcal_CacheP_TYPE_ALL);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(FirewallIntrReq_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for firewall interrupt response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getDKEK(HsmClient_t *HsmClient, DKEK_t *getDKEK, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_DKEK;
    uint64_t tempPhyAddr      = SOC_virtToPhy(getDKEK);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)getDKEK, sizeof(DKEK_t));

    /*
       Write back the DKEK_t struct
    */
    Mcal_CacheP_wbInv((void *)getDKEK, GET_CACHE_ALIGNED_SIZE(sizeof(getDKEK)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Get DKEK request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(DKEK_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for get DKEK response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_keyWriter(HsmClient_t *HsmClient, KeyWriterCertHeader_t *certHeader, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_KEYWRITER_SEND_CUST_KEY_CERT;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)certHeader, sizeof(KeyWriterCertHeader_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(certHeader);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
       Write back the KwrCertHeader struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(certHeader, GET_CACHE_ALIGNED_SIZE(sizeof(KeyWriterCertHeader_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);

    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf(
                "\r\n [HSM_CLIENT] KeyWriter customer key certificate send request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(KeyWriterCertHeader_t));

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf(
                    "\r\n [HSM_CLIENT] CRC check for KeyWriter customer key certificate send response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_readSWRev(HsmClient_t *HsmClient, SWRev_t *readSWRev)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_READ_SWREV;
    uint64_t tempPhyAddr      = SOC_virtToPhy(readSWRev);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)readSWRev, sizeof(SWRev_t));

    /*
       Write back the SWRev_t struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(readSWRev, GET_CACHE_ALIGNED_SIZE(sizeof(SWRev_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Read SWRev request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(SWRev_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for read SWRev response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_writeSWRev(HsmClient_t *HsmClient, SWRev_t *writeSWRev)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_WRITE_SWREV;
    uint64_t tempPhyAddr      = SOC_virtToPhy(writeSWRev);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)tempPhyAddr;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)writeSWRev, sizeof(SWRev_t));

    /*
       Write back the SWRev_t struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(writeSWRev, GET_CACHE_ALIGNED_SIZE(sizeof(SWRev_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Write SWRev request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(SWRev_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for write SWRev response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_getRandomNum(HsmClient_t *HsmClient, RNGReq_t *getRandomNum)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_GET_RAND;
    uint64_t phyAddrRNG       = SOC_virtToPhy(getRandomNum);
    HsmClient->ReqMsg.args    = (void *)(uint32_t *)(uintptr_t)phyAddrRNG;

    uint64_t resultPtrPhy   = SOC_virtToPhy(getRandomNum->resultPtr);
    getRandomNum->resultPtr = (uint8_t *)(uint32_t *)(uintptr_t)resultPtrPhy;
    uint64_t seedValuePhy   = SOC_virtToPhy(getRandomNum->seedValue);
    getRandomNum->seedValue = (uint32_t *)(uintptr_t)seedValuePhy;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)getRandomNum, sizeof(RNGReq_t));

    /*
       Write back the RNGReq_t struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(getRandomNum, GET_CACHE_ALIGNED_SIZE(sizeof(RNGReq_t)), Mcal_CacheP_TYPE_ALL);
    Mcal_CacheP_wbInv(getRandomNum->seedValue, GET_CACHE_ALIGNED_SIZE(((getRandomNum->seedSizeInDWords) * 4U)),
                      Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the readRow has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Get Random Number request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);
            Mcal_CacheP_inv((void *)HsmClient->RespMsg.args, GET_CACHE_ALIGNED_SIZE(sizeof(RNGReq_t)),
                            Mcal_CacheP_TYPE_ALL);
            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, sizeof(RNGReq_t));

            ((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr =
                (uint8_t *)SOC_phyToVirt((uint64_t)(uintptr_t)(((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr));
            ((RNGReq_t *)HsmClient->RespMsg.args)->seedValue =
                (uint32_t *)SOC_phyToVirt((uint64_t)(uintptr_t)(((RNGReq_t *)HsmClient->RespMsg.args)->seedValue));
            Mcal_CacheP_inv((void *)((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr,
                            GET_CACHE_ALIGNED_SIZE(((uint32_t)*(((RNGReq_t *)HsmClient->RespMsg.args)->resultPtr))),
                            Mcal_CacheP_TYPE_ALL);
            Mcal_CacheP_inv((void *)((RNGReq_t *)HsmClient->RespMsg.args)->seedValue,
                            GET_CACHE_ALIGNED_SIZE(((uint32_t)*(((RNGReq_t *)HsmClient->RespMsg.args)->seedValue))),
                            Mcal_CacheP_TYPE_ALL);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for Get RandomNumber response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_firmwareUpdate_CertProcess(HsmClient_t *HsmClient, FirmwareUpdateReq_t *pFirmwareUpdateObject)
{
    int32_t  status = SystemP_SUCCESS;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /* Proceed only if no previous firmware update API calls have been made, or HsmClient_firmwareUpdate_CodeVerify API
     * is called */
    if (SystemP_SUCCESS == status)
    {
        /*populate the send message structure */
        HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
        HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

        /* Always expect acknowledgement from HSM server */
        HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
        HsmClient->ReqMsg.serType = HSM_MSG_FW_UPDATE_CERT_PROCESS;
    }
    else
    {
        /* Do nothing */
    }

    /* Proceed only if address and size check falls within bounds */
    if (SystemP_SUCCESS == status)
    {
        /* Change the certificate start address to HSM address space */
        uint64_t startAddrPhy                = SOC_virtToPhy(pFirmwareUpdateObject->pStartAddress);
        pFirmwareUpdateObject->pStartAddress = (uint8_t *)(uint32_t *)(uintptr_t)startAddrPhy;
        /* Add arg crc */
        HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)pFirmwareUpdateObject, sizeof(FirmwareUpdateReq_t));
        /* Change the Arguments Address in Physical Address */
        uint64_t phyAddrTemp   = SOC_virtToPhy(pFirmwareUpdateObject);
        HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

        /*
        Write back the HsmVer struct and
        invalidate the cache before passing it to HSM
        */
        Mcal_CacheP_wbInv(pFirmwareUpdateObject, GET_CACHE_ALIGNED_SIZE(sizeof(FirmwareUpdateReq_t)),
                          Mcal_CacheP_TYPE_ALL);
        status = HsmClient_SendAndRecv(HsmClient, timeout);

        if (status == SystemP_SUCCESS)
        {
            /* the FW update cert process request has been completed by HSM server
             * if this request has been processed correctly */
            if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
            {
                AppUtils_printf(
                    "\r\n [HSM_CLIENT] Firmware update certificate processing request NACKed by HSM server\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                /* Change the Arguments Address in Physical Address */
                uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
                uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
                HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);
                /* check the integrity of args */
                crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), 0);
                if (crcArgs == HsmClient->RespMsg.crcArgs)
                {
                    status = SystemP_SUCCESS;
                }
                else
                {
                    AppUtils_printf(
                        "\r\n [HSM_CLIENT] CRC check for firmware update certificate process response failed \r\n");
                    status = SystemP_FAILURE;
                }
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return status;
}

int32_t HsmClient_firmwareUpdate_CodeProgram(HsmClient_t *HsmClient, FirmwareUpdateReq_t *pFirmwareUpdateObject)
{
    int32_t  status = SystemP_SUCCESS;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /* Proceed only if HsmClient_firmwareUpdate_CertProcess API call has been made */
    if (SystemP_SUCCESS == status)
    {
        /*populate the send message structure */
        HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
        HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

        /* Always expect acknowledgement from HSM server */
        HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
        HsmClient->ReqMsg.serType = HSM_MSG_FW_UPDATE_CODE_PROGRAM;
    }
    else
    {
        /* Do nothing */
    }

    /* Proceed only if address and size check falls within bounds */
    if (SystemP_SUCCESS == status)
    {
        /* Change the certificate start address to HSM address space */
        uint64_t startAddrPhy                = SOC_virtToPhy(pFirmwareUpdateObject->pStartAddress);
        pFirmwareUpdateObject->pStartAddress = (uint8_t *)(uint32_t *)(uintptr_t)startAddrPhy;
        /* Add arg crc */
        HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)pFirmwareUpdateObject, sizeof(FirmwareUpdateReq_t));
        /* Change the Arguments Address in Physical Address */
        uint64_t phyAddrTemp   = SOC_virtToPhy(pFirmwareUpdateObject);
        HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

        /*
        Write back the HsmVer struct and
        invalidate the cache before passing it to HSM
        */
        Mcal_CacheP_wbInv(pFirmwareUpdateObject, GET_CACHE_ALIGNED_SIZE(sizeof(FirmwareUpdateReq_t)),
                          Mcal_CacheP_TYPE_ALL);
        status = HsmClient_SendAndRecv(HsmClient, timeout);

        if (status == SystemP_SUCCESS)
        {
            /* the FW update cert process request has been completed by HSM server
             * if this request has been processed correctly */
            if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
            {
                AppUtils_printf("\r\n [HSM_CLIENT] Firmware update code programming request NACKed by HSM server\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                /* Change the Arguments Address in Physical Address */
                uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
                uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
                HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);
                /* check the integrity of args */
                crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), 0);
                if (crcArgs == HsmClient->RespMsg.crcArgs)
                {
                    status = SystemP_SUCCESS;
                }
                else
                {
                    AppUtils_printf(
                        "\r\n [HSM_CLIENT] CRC check for firmware update code programming response failed \r\n");
                    status = SystemP_FAILURE;
                }
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return status;
}

int32_t HsmClient_firmwareUpdate_CodeVerify(HsmClient_t *HsmClient, FirmwareUpdateReq_t *pFirmwareUpdateObject)
{
    int32_t  status = SystemP_SUCCESS;
    uint16_t crcArgs;
    uint32_t timeout = SystemP_WAIT_FOREVER;

    /* Proceed only if HsmClient_firmwareUpdate_CodeProgram API call has been made */
    if (SystemP_SUCCESS == status)
    {
        /*populate the send message structure */
        HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
        HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

        /* Always expect acknowledgement from HSM server */
        HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
        HsmClient->ReqMsg.serType = HSM_MSG_FW_UPDATE_CODE_VERIFY;

        /* Address and size check */
        /* MISRA-C:2012 Rule 10.4 - Ensure type consistency in comparisons */
        if ((pFirmwareUpdateObject->pStartAddress == NULL_PTR) && (pFirmwareUpdateObject->dataLength == 0U))
        {
            status = SystemP_SUCCESS;
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    /* Proceed only if address and size check falls within bounds */
    if (SystemP_SUCCESS == status)
    {
        /* Add arg crc */
        HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)pFirmwareUpdateObject, 0);
        /* Change the Arguments Address in Physical Address */
        uint64_t phyAddrTemp   = SOC_virtToPhy(pFirmwareUpdateObject);
        HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

        /*
        Write back the HsmVer struct and
        invalidate the cache before passing it to HSM
        */
        Mcal_CacheP_wbInv(pFirmwareUpdateObject, GET_CACHE_ALIGNED_SIZE(sizeof(FirmwareUpdateReq_t)),
                          Mcal_CacheP_TYPE_ALL);
        status = HsmClient_SendAndRecv(HsmClient, timeout);

        if (SystemP_SUCCESS == status)
        {
            /* the FW update cert process request has been completed by HSM server
             * if this request has been processed correctly */
            /* MISRA-C:2012 Rule 10.4 - Ensure type consistency in comparisons */
            if ((uint8_t)HSM_FLAG_NACK == HsmClient->RespFlag)
            {
                AppUtils_printf(
                    "\r\n [HSM_CLIENT] Firmware update certificate programming request NACKed by HSM server\r\n");
                status = SystemP_FAILURE;
            }
            else
            {
                /* Change the Arguments Address in Physical Address */
                uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
                uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
                HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);
                /* check the integrity of args */
                crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), 0);
                if (crcArgs == HsmClient->RespMsg.crcArgs)
                {
                    status = SystemP_SUCCESS;
                }
                else
                {
                    AppUtils_printf(
                        "\r\n [HSM_CLIENT] CRC check for firmware update certificate programming response failed \r\n");
                    status = SystemP_FAILURE;
                }
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return status;
}
int32_t HsmClient_VerifyROTSwitchingCertificate(HsmClient_t *HsmClient, uint8_t *cert, uint32_t cert_size,
                                                uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /* populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_VERIFY_ROT_CERT;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)cert, cert_size);

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(cert);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
    Write back the RoT cert and
    invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(cert, GET_CACHE_ALIGNED_SIZE(cert_size), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (SystemP_SUCCESS == status)
    {
        /* the RoT Switch has been populated by HSM server
         * if this request has been processed correctly */
        /* MISRA-C:2012 Rule 10.4 - Ensure type consistency in comparisons */
        if ((uint8_t)HSM_FLAG_NACK == HsmClient->RespFlag)
        {
            AppUtils_printf(
                "\r\n [HSM_CLIENT] RoT Switching Certificate Verification request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0U);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf(
                    "\r\n [HSM_CLIENT] CRC check for RoT Switching Certificate Verification response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (SystemP_FAILURE == status)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_UpdateKeyRevsion(HsmClient_t *HsmClient, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /* populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_UPDATE_KEY_REV;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)NULL_PTR, 0U);

    /* Change the Arguments Address in Physical Address */
    HsmClient->ReqMsg.args = NULL_PTR;

    status = HsmClient_SendAndRecv(HsmClient, timeout);

    if (SystemP_SUCCESS == status)
    {
        /* the verifyApp has been populated by HSM server
         * if this request has been processed correctly */
        /* MISRA-C:2012 Rule 10.4 - Ensure type consistency in comparisons */
        if ((uint8_t)HSM_FLAG_NACK == HsmClient->RespFlag)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Update Key Revision request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), 0);
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for update key revision response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    else if (SystemP_FAILURE == status)
    {
        /* If failure occur due to some reason */
        status = SystemP_FAILURE;
    }
    else
    {
        /* Indicate timeout error */
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_configOTFARegions(HsmClient_t *HsmClient, OTFA_Config_t *OTFA_ConfigInfo, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_CONFIGURE_OTFA;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)OTFA_ConfigInfo, sizeof(OTFA_Config_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(OTFA_ConfigInfo);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
       Write back the OTFA_ConfigInfo struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(OTFA_ConfigInfo, GET_CACHE_ALIGNED_SIZE(sizeof(OTFA_Config_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);

    if (status == SystemP_SUCCESS)
    {
        /* the hsmVer has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Configure OTFA request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), sizeof(OTFA_Config_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for OTFA_configuration response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_readOTFARegions(HsmClient_t *HsmClient, OTFA_readRegion_t *OTFA_readRegion, uint32_t timeout)
{
    /* make the message */
    int32_t  status;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_READ_OTFA;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)OTFA_readRegion, sizeof(OTFA_readRegion_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(OTFA_readRegion);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
       Write back the OTFA_readRegion struct and
       invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(OTFA_readRegion, GET_CACHE_ALIGNED_SIZE(sizeof(OTFA_readRegion_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);

    if (status == SystemP_SUCCESS)
    {
        /* the hsmVer has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Read OTFA request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)(HsmClient->RespMsg.args), sizeof(OTFA_readRegion_t));
            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for OTFA_read response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}

int32_t HsmClient_secCfgValidate(HsmClient_t *HsmClient, SecCfgValidate_t *pSecCfgParams, uint32_t timeout)
{
    /* make the message */
    int32_t  status = SystemP_FAILURE;
    uint16_t crcArgs;

    /*populate the send message structure */
    HsmClient->ReqMsg.destClientId = HSM_CLIENT_ID_1;
    HsmClient->ReqMsg.srcClientId  = HsmClient->ClientId;

    /* Always expect acknowledgement from HSM server */
    HsmClient->ReqMsg.flags   = HSM_FLAG_AOP;
    HsmClient->ReqMsg.serType = HSM_MSG_PROC_AUTH_BOOT_SEC_CFG;

    /* Add arg crc */
    HsmClient->ReqMsg.crcArgs = crc16_ccit((uint8_t *)pSecCfgParams, sizeof(SecCfgValidate_t));

    /* Change the Arguments Address in Physical Address */
    uint64_t phyAddrTemp   = SOC_virtToPhy(pSecCfgParams);
    HsmClient->ReqMsg.args = (void *)(uint32_t *)(uintptr_t)phyAddrTemp;

    /*
        Write back the cert and
        invalidate the cache before passing it to HSM
    */
    Mcal_CacheP_wbInv(pSecCfgParams, GET_CACHE_ALIGNED_SIZE(sizeof(SecCfgValidate_t)), Mcal_CacheP_TYPE_ALL);

    status = HsmClient_SendAndRecv(HsmClient, timeout);
    if (status == SystemP_SUCCESS)
    {
        /* the OpenDbgFirewalls has been populated by HSM server
         * if this request has been processed correctly */
        if (HsmClient->RespFlag == (uint8_t)HSM_FLAG_NACK)
        {
            AppUtils_printf("\r\n [HSM_CLIENT] Sec-Cfg validation request NACKed by HSM server\r\n");
            status = SystemP_FAILURE;
        }
        else
        {
            /* Change the Arguments Address in Physical Address */
            uint32_t *tempTypedPtr  = (uint32_t *)HsmClient->RespMsg.args;
            uint64_t  tempPhyAddr   = (uint64_t)(uintptr_t)tempTypedPtr;
            HsmClient->RespMsg.args = SOC_phyToVirt(tempPhyAddr);

            /* check the integrity of args */
            crcArgs = crc16_ccit((uint8_t *)HsmClient->RespMsg.args, 0);

            if (crcArgs == HsmClient->RespMsg.crcArgs)
            {
                status = SystemP_SUCCESS;
            }
            else
            {
                AppUtils_printf("\r\n [HSM_CLIENT] CRC check for Sec-Cfg validation response failed \r\n");
                status = SystemP_FAILURE;
            }
        }
    }
    /* If failure occur due to some reason */
    else if (status == SystemP_FAILURE)
    {
        status = SystemP_FAILURE;
    }
    /* Indicate timeout error */
    else
    {
        status = SystemP_TIMEOUT;
    }
    return status;
}
