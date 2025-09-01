/* ======================================================================
 *   Copyright (c) 2023-2024 Texas Instruments Incorporated
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
 *  \file     Cdd_Ipc.c
 *
 *  \brief    This file contains Complex Device Driver for IPC
 *
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_Ipc.c
 *    Component:  Complex Device Driver
 *       Module:  IPC
 *    Generator:  None
 *
 *  Description: This component provides services for initialization and control of the IPC between
 *different core in the this Multicore SoC.
 *********************************************************************************************************************/
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_Ipc.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */

/*
 *Design:MCAL-15296
 */
#if ((CDD_IPC_AR_RELEASE_MAJOR_VERSION != (4U)) || (CDD_IPC_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (CDD_IPC_AR_RELEASE_REVISION_VERSION != (1U)))
#error "CDD: AUTOSAR Version Numbers of CDD IPC are different!!"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((CDD_IPC_SW_MAJOR_VERSION != (10U)) || (CDD_IPC_SW_MINOR_VERSION != (2U)))
#error "CDD: Software Version Numbers are inconsistent!!"
#endif

/* Shared memory check to ensure it is within bounds */
#if (CDD_IPC_SHARED_MEMORY_SIZE > 16000)
#error "CDD IPC:Shared memory size exceeded"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
static boolean        Cdd_Ipc_DeInit_detError_Check_CoreNo(const Cdd_IpcConfigType *ConfigPtr);
static Std_ReturnType Cdd_Ipc_Notify_RegisterClient_det_check(uint32                localClientId,
                                                              IpcNotify_FxnCallback notify_msgHandler);
static boolean        Cdd_Ipc_DeInit_detErrorCheck(const Cdd_IpcConfigType *Configuration_Ptr);
static boolean        Cdd_Ipc_Init_detCheck(const Cdd_IpcConfigType *ConfigPtr);
static boolean        Cdd_Ipc_Construct_detCheck(const Cdd_IpcConfigType *ConfigPtr);
static boolean        Cdd_Ipc_Init_detErrorCheck(const Cdd_IpcConfigType *ConfigPtr);
#endif
static void        Cdd_Ipc_deInitCores(const Cdd_IpcConfigType *ConfigPtr);
static inline void Cdd_IpcRuntimeError(uint8 apiId, uint8 errorId);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/** \brief CDD IPC handles */
#define CDD_IPC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Ipc_MemMap.h"

IpcNotify_Object          CddIpc_NotifyObject;
IpcNotify_InitObject      CddIpcInit_Config;
IpcNotifyUtils_Object     CddIpc_NotifyUtilsObject;
IpcNotifyUtils_Handle     CddIpc_NotifyUtilsHandle = &CddIpc_NotifyUtilsObject;
IpcNotifyUtils_InitObject CddIpc_NotifyUtilsInitObject;

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
RPMessageLLD_Object Cdd_RPMessageObj;

RPMessage_EpObject Cdd_AckReplyMsgObject[CDD_IPC_LOCALEP_COUNT];

RPMessage_CreateParams createParams;

#endif

#define CDD_IPC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_Ipc_MemMap.h"

#define CDD_IPC_START_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Ipc_MemMap.h"

IpcNotify_Handle CddIpc_NotifyHandle = &CddIpc_NotifyObject;

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
RPMessageLLD_Handle CddIpc_RPMsgHandle = &Cdd_RPMessageObj;
#endif

extern RPMessageLLD_InitObject CddIpc_RPMessageInitObj;

/** \brief CDD IPC driver status */
static VAR(Cdd_IpcStatusType, CDD_VAR_ZERO_INIT) CddIpc_DrvStatus = CDD_IPC_UNINIT;

#define CDD_IPC_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_Ipc_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_IPC_START_SEC_CODE
#include "Cdd_Ipc_MemMap.h"

#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
/*
 *Design:MCAL-15298,MCAL-15297,MCAL-15250
 */
static inline void Cdd_IpcReportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(CDD_IPC_MODULE_ID, CDD_IPC_INSTANCE_ID, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == CDD_IPC_DEV_ERROR_DETECT) */

#if (STD_ON == CDD_IPC_VERSION_INFO_API)
/*
 *Design:MCAL-15319,MCAL-15318
 */
FUNC(void, CDD_IPC_CODE)
Cdd_Ipc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_IPC_APPL_DATA) VersionInfoPtr)
{
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        Cdd_IpcReportDetError(CDD_IPC_GETVERSIONINFO_SERVICE_ID, CDD_IPC_E_PARAM_POINTER);
    }
    else
#endif /* #if (STD_ON == CDD_IPC_DEV_ERROR_DETECT) */
    {
        VersionInfoPtr->vendorID         = CDD_IPC_VENDOR_ID;
        VersionInfoPtr->moduleID         = CDD_IPC_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)CDD_IPC_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)CDD_IPC_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)CDD_IPC_SW_PATCH_VERSION;
    }

    return;
}
#endif /* #if (STD_ON == CDD_IPC_VERSION_INFO_API) */

/*
 *Design:MCAL-15289,MCAL-15306,MCAL-15308,MCAL-15309,MCAL-15307
 */
FUNC(void, CDD_IPC_CODE) Cdd_Ipc_Init(P2CONST(Cdd_IpcConfigType, AUTOMATIC, CDD_IPC_CFG) ConfigPtr)
{
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    boolean exitCondition = FALSE;
    exitCondition         = Cdd_Ipc_Init_detErrorCheck(ConfigPtr);
    if (TRUE == exitCondition)
    {
        if (ConfigPtr->Cdd_Ipc_numCores < CDD_IPC_CORE_ID_MAX)
        {
            exitCondition = Cdd_Ipc_Init_detCheck(ConfigPtr);
        }
        else
        {
            /*nothing to do*/
        }
    }

    if (TRUE == exitCondition)
#endif
    {
        sint32 initStatus = (sint32)CDD_IPC_UNINIT;
#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON && CDD_IPC_SAFEIPC_ENABLE == STD_OFF)
        Cdd_Ipc_VringMemAllocation();
#endif
#if (CDD_IPC_SAFEIPC_ENABLE == STD_ON)
        IpcNotify_MailboxConfig *pMailboxConfig;
        pMailboxConfig = IpcNotifyCfg_getMailboxConfig(0, 0);
        Cdd_Ipc_SafeIpcMemoryAllocation(pMailboxConfig);
#endif
        CddIpcInit_Config.selfCoreId          = ConfigPtr->Cdd_Ipc_SelfCoreId;
        CddIpcInit_Config.numCores            = ConfigPtr->Cdd_Ipc_numCores;
        CddIpcInit_Config.Cdd_Ipc_CrcHookFunc = ConfigPtr->Cdd_Ipc_CrcHookFunc;
        for (uint32 core = 0; core < ConfigPtr->Cdd_Ipc_numCores; core++)
        {
            CddIpcInit_Config.coreIdList[core] = ConfigPtr->Cdd_Ipc_coreIdList[core];
        }

        CddIpc_NotifyHandle->hIpcNotifyInit           = &CddIpcInit_Config;
        CddIpc_NotifyUtilsInitObject.hIpcNotify       = CddIpc_NotifyHandle;
        CddIpc_NotifyUtilsHandle->hIpcNotifyUtilsInit = &CddIpc_NotifyUtilsInitObject;

        initStatus = IpcNotify_lld_init(CddIpc_NotifyHandle);
        initStatus = IpcNotifyUtils_lld_init(CddIpc_NotifyUtilsHandle);

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON) /* Initialize the RpMsg API's only if it is enabled */
        CddIpc_RPMsgHandle->hRpMsgInit = &CddIpc_RPMessageInitObj;
        initStatus                     = RPMessage_lld_init(CddIpc_RPMsgHandle);
#endif

        if ((E_OK) == (uint32)initStatus)
        {
            CddIpc_DrvStatus = CDD_IPC_IDLE;
        }

        else
        {
            Cdd_IpcRuntimeError(CDD_IPC_INIT_SERVICE_ID, CDD_IPC_E_INIT_FAILED);
        }
    }
    return;
}

/*
 *Design:MCAL-16600,MCAL-15289,MCAL-16599,MCAL-15300
 */
FUNC(void, CDD_IPC_CODE) Cdd_Ipc_Notify_Sync_All(void)
{
    (void)IpcNotifyUtils_lld_syncAll(CddIpc_NotifyUtilsHandle, (uint32)MCAL_SystemP_TIMEOUT);
}

#if (STD_ON == CDD_IPC_DEINIT_API)
/*
 *Design:MCAL-16764,MCAL-16598,MCAL-16596,MCAL-16597
 */
FUNC(void, CDD_IPC_CODE)
Cdd_Ipc_DeInit(P2CONST(Cdd_IpcConfigType, AUTOMATIC, CDD_IPC_CFG) ConfigPtr)
{
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    boolean exitCondition = FALSE;
    if ((CDD_IPC_UNINIT == CddIpc_DrvStatus))
    {
        Cdd_IpcReportDetError(CDD_IPC_DEINIT_SERVICE_ID, CDD_IPC_E_UNINIT);
    }
    else if (NULL_PTR == ConfigPtr)
    {
        Cdd_IpcReportDetError(CDD_IPC_DEINIT_SERVICE_ID, CDD_IPC_E_PARAM_POINTER);
    }
    else
    {
        exitCondition = Cdd_Ipc_DeInit_detErrorCheck(ConfigPtr);
    }

    if (TRUE == exitCondition)
#endif
    {
        Cdd_Ipc_deInitCores(ConfigPtr);
    }

    return;
}
#endif /* #if (STD_ON == CDD_IPC_DEINIT_API) */

/*
 *Design:MCAL-16603,MCAL-16605,MCAL-16601,MCAL-16604,MCAL-16763,MCAL-16602,MCAL-16765
 */
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_Notify_RegisterClient(uint32 Cdd_Ipc_localClientId, IpcNotify_FxnCallback Cdd_Ipc_notify_msgHandler,
                              P2VAR(void, AUTOMATIC, CDD_IPC_APPL_DATA) args)
{
    sint32         status = MCAL_SystemP_FAILURE;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    if (CDD_IPC_UNINIT == CddIpc_DrvStatus)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_NOTIFY_REGISTER_CLIENT_SERVICE_ID, CDD_IPC_E_UNINIT);
    }
    else
    {
        retVal = Cdd_Ipc_Notify_RegisterClient_det_check(Cdd_Ipc_localClientId, Cdd_Ipc_notify_msgHandler);
    }
    if (retVal == E_OK)
#endif
    {
        status = IpcNotify_lld_registerClient(CddIpc_NotifyHandle, (uint16)Cdd_Ipc_localClientId,
                                              Cdd_Ipc_notify_msgHandler, NULL_PTR);
        if (MCAL_SystemP_SUCCESS != status)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    return (retVal);
}

/*
 *Design:MCAL-16608,MCAL-16607,MCAL-16606,MCAL-15289
 */
FUNC(Std_ReturnType, CDD_IPC_CODE) Cdd_Ipc_Notify_UnregisterClient(uint32 Cdd_Ipc_localClientId)
{
    sint32         status = MCAL_SystemP_FAILURE;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    if (CDD_IPC_UNINIT == CddIpc_DrvStatus)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_NOTIFY_UNREGISTER_CLIENT_SERVICE_ID, CDD_IPC_E_UNINIT);
    }
    else if (Cdd_Ipc_localClientId > CDD_IPC_MAX_NOTIFY_CLIENT_ID_PER_CORE)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_NOTIFY_UNREGISTER_CLIENT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else
#endif
    {
        status = IpcNotify_lld_unregisterClient(CddIpc_NotifyHandle, (uint16)Cdd_Ipc_localClientId);
        if (MCAL_SystemP_SUCCESS != status)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    return (retVal);
}

#if (STD_ON == CDD_IPC_WRITE_API)
/*
 *Design:MCAL-16611,MCAL-16610,MCAL-16609,MCAL-16612,MCAL-15289,MCAL-15257
 */
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_Notify_Write(uint32 Cdd_Ipc_remoteCoreId, uint16 Cdd_Ipc_remoteClientId, uint32 Cdd_Ipc_msgValue,
                     uint32 Cdd_Ipc_waitForFifoNotFull)
{
    sint32         status = MCAL_SystemP_FAILURE;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    if (CDD_IPC_UNINIT == CddIpc_DrvStatus)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_WRITEDATA_SERVICE_ID, CDD_IPC_E_UNINIT);
    }
    else if ((Cdd_Ipc_remoteCoreId > CDD_IPC_CORE_ID_MAX) ||
             (Cdd_Ipc_remoteClientId > CDD_IPC_MAX_NOTIFY_CLIENT_ID_PER_CORE) || (Cdd_Ipc_waitForFifoNotFull > 1U))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_WRITEDATA_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else
#endif
    {
        status = IpcNotify_lld_sendMsg(CddIpc_NotifyHandle, Cdd_Ipc_remoteCoreId, Cdd_Ipc_remoteClientId,
                                       Cdd_Ipc_msgValue, Cdd_Ipc_waitForFifoNotFull, (CDD_IPC_TIMEOUT));

        if (MCAL_SystemP_SUCCESS != status)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return (retVal);
}
#endif /* #if (STD_ON == CDD_IPC_WRITE_API) */

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
/*
 *Design:MCAL-16615,MCAL-16618,MCAL-16614,MCAL-16613,MCAL-16616,MCAL-15289,MCAL-16617,MCAL-15302,MCAL-15314
 */
FUNC(void, CDD_IPC_CODE)
Cdd_Ipc_Construct(P2CONST(Cdd_IpcConfigType, AUTOMATIC, CDD_IPC_CFG) ConfigPtr)
{
    Std_ReturnType status = (Std_ReturnType)E_NOT_OK;

#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    boolean exitCondition = FALSE;
    if (CDD_IPC_UNINIT == CddIpc_DrvStatus)
    {
        Cdd_IpcReportDetError(CDD_IPC_CONSTRUCT_SERVICE_ID, CDD_IPC_E_UNINIT);
    }
    else if (ConfigPtr == NULL_PTR)
    {
        Cdd_IpcReportDetError(CDD_IPC_CONSTRUCT_SERVICE_ID, CDD_IPC_E_PARAM_POINTER);
    }
    else if (CDD_IPC_LOCALEP_COUNT > 0U)
    {
        exitCondition = Cdd_Ipc_Construct_detCheck(ConfigPtr);
    }
    else
    {
        /*Nothing to do*/
    }
    if (TRUE == exitCondition)
#endif
    {
        for (uint32 core = 0U; core < CDD_IPC_LOCALEP_COUNT; core++)
        {
            RPMessage_lld_CreateParams_init(&createParams);
            createParams.localEndPt = (uint16)ConfigPtr->Cdd_Ipc_RpMsgParams[core].Cdd_Ipc_localEndPt;
#if (STD_ON == CDD_IPC_RPMSG_CALLBACK_ENABLE)
            createParams.recvCallback = (RPMessage_lld_recvCallback)(ConfigPtr->Cdd_Ipc_RpMsgParams[core].recvCallback);
            createParams.recvCallbackArgs = ConfigPtr->Cdd_Ipc_RpMsgParams[core].recvCallbackArgs;
#endif
#if (STD_ON == CDD_IPC_RPMSG_NOTIFY_CALLBACK_ENABLE)
            createParams.recvNotifyCallback =
                (RPMessage_lld_recvNotifyCallback)ConfigPtr->Cdd_Ipc_RpMsgParams[core].recvNotifyCallback;
            createParams.recvNotifyCallbackArgs = ConfigPtr->Cdd_Ipc_RpMsgParams[core].recvNotifyCallbackArgs;
#endif
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
            status = (Std_ReturnType)RPMessage_lld_construct(CddIpc_RPMsgHandle, &Cdd_AckReplyMsgObject[core],
                                                             &createParams);
#else
            status = RPMessage_lld_construct(CddIpc_RPMsgHandle, &Cdd_AckReplyMsgObject[core], &createParams);
#endif

            if (((Std_ReturnType)E_OK) != status)
            {
                Cdd_IpcRuntimeError(CDD_IPC_CONSTRUCT_SERVICE_ID, CDD_IPC_E_CONSTRUCT_FAILED);
            }
        }
    }

    return;
}

/*
 *Design:MCAL-15310
 */
FUNC(void, CDD_IPC_CODE) Cdd_Ipc_Destruct(uint16 Cdd_Ipc_localEndPtId)
{
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    if (CDD_IPC_UNINIT == CddIpc_DrvStatus)
    {
        Cdd_IpcReportDetError(CDD_IPC_DESTRUCT_SERVICE_ID, CDD_IPC_E_UNINIT);
    }

    else if ((Cdd_Ipc_localEndPtId >= CDD_IPC_LOCALEP_COUNT))
    {
        Cdd_IpcReportDetError(CDD_IPC_DESTRUCT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else
#endif
    {
        RPMessage_lld_destruct(CddIpc_RPMsgHandle, &Cdd_AckReplyMsgObject[Cdd_Ipc_localEndPtId]);
    }
    return;
}

/*
 *Design:MCAL-16619,MCAL-16622,MCAL-16621,MCAL-16620
 */
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_RpMsg_SendMsg(void *data, uint16 dataLen, uint16 Cdd_Ipc_remoteCoreId, uint16 Cdd_Ipc_remoteEndPt,
                      uint16 Cdd_Ipc_localEndPtId, uint32 timeout)
{
    sint32         status = MCAL_SystemP_FAILURE;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    if (CDD_IPC_UNINIT == CddIpc_DrvStatus)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_RPMSG_WRITE_SERVICE_ID, CDD_IPC_E_UNINIT);
    }
    else if ((CddIpc_RPMsgHandle == NULL_PTR) || (data == NULL_PTR) || (dataLen == 0U) ||
             (Cdd_Ipc_localEndPtId >= CDD_IPC_LOCALEP_COUNT) || (Cdd_Ipc_remoteCoreId > CDD_IPC_CORE_ID_MAX) ||
             (Cdd_Ipc_remoteEndPt > CDD_IPC_MAX_ENDPOINTS_PER_CORE))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_RPMSG_WRITE_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else
#endif
    {
        status =
            RPMessage_lld_send(CddIpc_RPMsgHandle, data, dataLen, Cdd_Ipc_remoteCoreId, Cdd_Ipc_remoteEndPt,
                               (uint16)CfgPtr->Cdd_Ipc_RpMsgParams[Cdd_Ipc_localEndPtId].Cdd_Ipc_localEndPt, timeout);

        if (MCAL_SystemP_SUCCESS != status)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return (retVal);
}

/*
 *Design:MCAL-16623,MCAL-15312,MCAL-16624
 */
FUNC(Std_ReturnType, CDD_IPC_CODE)
Cdd_Ipc_RpMsg_RecvMsg(void *data, uint16 *dataLen, uint16 Cdd_Ipc_localEndPtId, uint16 *Cdd_Ipc_remoteCoreId,
                      uint16 *Cdd_Ipc_remoteEndPt, uint32 timeout)
{
    sint32         status = MCAL_SystemP_FAILURE;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
    if (CDD_IPC_UNINIT == CddIpc_DrvStatus)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_RPMSG_READ_SERVICE_ID, CDD_IPC_E_UNINIT);
    }
    else if ((CddIpc_RPMsgHandle == NULL_PTR) || (data == NULL_PTR) || (dataLen == NULL_PTR) ||
             (Cdd_Ipc_localEndPtId >= CDD_IPC_LOCALEP_COUNT) || (Cdd_Ipc_remoteCoreId == NULL_PTR) ||
             (Cdd_Ipc_remoteEndPt == NULL_PTR))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_RPMSG_READ_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else
#endif
    {
        status = RPMessage_lld_recv(CddIpc_RPMsgHandle, &Cdd_AckReplyMsgObject[Cdd_Ipc_localEndPtId], data, dataLen,
                                    Cdd_Ipc_remoteCoreId, Cdd_Ipc_remoteEndPt, timeout);

        if (MCAL_SystemP_SUCCESS != status)
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return (retVal);
}
#endif /* #if (CDD_IPC_RPMSG_ENABLE_API == STD_ON) */

void Cdd_Ipc_Mutex_resourceUnlock(uint32 *lock)
{
    *lock = CDD_IPC_UNLOCK;
}

uint32 Cdd_Ipc_Mutex_resourceTryLock(uint32 *lock)
{
    uint32 status = 0U;
    if (*lock == CDD_IPC_LOCK)
    {
        status = CDD_IPC_LOCK;
    }
    else
    {
        *lock  = CDD_IPC_LOCK;
        status = CDD_IPC_UNLOCK;
    }
    return status;
}

static void Cdd_Ipc_deInitCores(const Cdd_IpcConfigType *ConfigPtr)
{
    Std_ReturnType deInitStatus  = (Std_ReturnType)E_NOT_OK;
    CddIpcInit_Config.selfCoreId = ConfigPtr->Cdd_Ipc_SelfCoreId;
    CddIpcInit_Config.numCores   = ConfigPtr->Cdd_Ipc_numCores;
    for (uint32 core = 0; core < ConfigPtr->Cdd_Ipc_numCores; core++)
    {
        CddIpcInit_Config.coreIdList[core] = ConfigPtr->Cdd_Ipc_coreIdList[core];
    }

    CddIpc_NotifyHandle->hIpcNotifyInit = &CddIpcInit_Config;

    sint32 deInitValue = IpcNotify_lld_deInit(CddIpc_NotifyHandle);
    if (deInitValue == MCAL_SystemP_SUCCESS)
    {
        deInitStatus = E_OK;
    }
    else
    {
        deInitStatus = E_NOT_OK;
    }

#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
    CddIpc_RPMsgHandle->hRpMsgInit = &CddIpc_RPMessageInitObj;
    deInitValue                    = RPMessage_lld_deInit(CddIpc_RPMsgHandle);
    if (deInitValue == MCAL_SystemP_SUCCESS)
    {
        deInitStatus = E_OK;
    }
    else
    {
        deInitStatus = E_NOT_OK;
    }
#endif

    if ((E_OK) == deInitStatus)
    {
        CddIpc_DrvStatus = CDD_IPC_UNINIT;
    }
    else
    {
        Cdd_IpcRuntimeError(CDD_IPC_DEINIT_SERVICE_ID, CDD_IPC_E_DEINIT_FAILED);
    }
}

#if (STD_ON == CDD_IPC_DEV_ERROR_DETECT)
static boolean Cdd_Ipc_DeInit_detErrorCheck(const Cdd_IpcConfigType *Configuration_Ptr)
{
    boolean                  exitCondition = FALSE;
    const Cdd_IpcConfigType *Cfg_Ptr       = (Cdd_IpcConfigType *)NULL_PTR;
    Cfg_Ptr                                = Configuration_Ptr;
    if ((Configuration_Ptr->Cdd_Ipc_SelfCoreId > CDD_IPC_CORE_ID_MAX) ||
        (Configuration_Ptr->Cdd_Ipc_numCores > CDD_IPC_CORE_ID_MAX))
    {
        Cdd_IpcReportDetError(CDD_IPC_DEINIT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else if (Configuration_Ptr->Cdd_Ipc_numCores < CDD_IPC_CORE_ID_MAX)
    {
        exitCondition = Cdd_Ipc_DeInit_detError_Check_CoreNo(Cfg_Ptr);
    }
    else
    {
        /*nothing to do*/
    }
    return exitCondition;
}

static Std_ReturnType Cdd_Ipc_Notify_RegisterClient_det_check(uint32                localClientId,
                                                              IpcNotify_FxnCallback notify_msgHandler)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    if (notify_msgHandler == NULL_PTR)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_NOTIFY_REGISTER_CLIENT_SERVICE_ID, CDD_IPC_E_PARAM_POINTER);
    }
    else if (localClientId > CDD_IPC_MAX_NOTIFY_CLIENT_ID_PER_CORE)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
        Cdd_IpcReportDetError(CDD_IPC_NOTIFY_REGISTER_CLIENT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else
    {
        /*nothing to do*/
    }
    return retVal;
}

static boolean Cdd_Ipc_DeInit_detError_Check_CoreNo(const Cdd_IpcConfigType *ConfigPtr)
{
    boolean exitCondition = FALSE;
    for (uint32 core = 0; core < ConfigPtr->Cdd_Ipc_numCores; core++)
    {
        if (ConfigPtr->Cdd_Ipc_coreIdList[core] > CDD_IPC_CORE_ID_MAX)
        {
            Cdd_IpcReportDetError(CDD_IPC_DEINIT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
        }
        else
        {
            exitCondition = TRUE;
        }
    }
    return exitCondition;
}

static boolean Cdd_Ipc_Init_detCheck(const Cdd_IpcConfigType *ConfigPtr)
{
    boolean exitCondition = FALSE;
    for (uint32 core = 0U; core < ConfigPtr->Cdd_Ipc_numCores; core++)
    {
        if (ConfigPtr->Cdd_Ipc_coreIdList[core] > CDD_IPC_CORE_ID_MAX)
        {
            Cdd_IpcReportDetError(CDD_IPC_INIT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
        }
        else
        {
            exitCondition = TRUE;
        }
    }
    return exitCondition;
}

static boolean Cdd_Ipc_Construct_detCheck(const Cdd_IpcConfigType *ConfigPtr)
{
    boolean exitCondition = FALSE;
#if (CDD_IPC_RPMSG_ENABLE_API == STD_ON)
    for (uint32 count = 0; count < CDD_IPC_LOCALEP_COUNT; count++)
    {
        uint32 localendPoint_check = ConfigPtr->Cdd_Ipc_RpMsgParams[count].Cdd_Ipc_localEndPt;
        if (localendPoint_check > CDD_IPC_MAX_ENDPOINTS_PER_CORE)
        {
            Cdd_IpcReportDetError(CDD_IPC_CONSTRUCT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
        }
        else
        {
            exitCondition = TRUE;
        }
    }
#endif
    return exitCondition;
}

static boolean Cdd_Ipc_Init_detErrorCheck(const Cdd_IpcConfigType *ConfigPtr)
{
    boolean exitCondition = FALSE;
    if (CDD_IPC_UNINIT != CddIpc_DrvStatus)
    {
        Cdd_IpcReportDetError(CDD_IPC_INIT_SERVICE_ID, CDD_IPC_E_ALREADY_INITIALIZED);
    }
    else if (NULL_PTR == ConfigPtr)
    {
        Cdd_IpcReportDetError(CDD_IPC_INIT_SERVICE_ID, CDD_IPC_E_PARAM_POINTER);
    }
    else if ((ConfigPtr->Cdd_Ipc_SelfCoreId > CDD_IPC_CORE_ID_MAX) ||
             (ConfigPtr->Cdd_Ipc_numCores > CDD_IPC_CORE_ID_MAX))
    {
        Cdd_IpcReportDetError(CDD_IPC_INIT_SERVICE_ID, CDD_IPC_E_PARAM_VALUE);
    }
    else
    {
        exitCondition = TRUE;
    }
    return exitCondition;
}
#endif /*(STD_ON == CDD_IPC_DEV_ERROR_DETECT)*/

static inline void Cdd_IpcRuntimeError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportRuntimeError(CDD_IPC_MODULE_ID, CDD_IPC_INSTANCE_ID, apiId, errorId);
    return;
}

#define CDD_IPC_STOP_SEC_CODE
#include "Cdd_Ipc_MemMap.h"
