/* ======================================================================
 *   Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file     Cdd_I2c.c
 *
 *  \brief    The I2C driver provides APIs to configure the I2C module
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_I2c_Priv.h"
#include "Cdd_I2c_Hw.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((CDD_I2C_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (CDD_I2C_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (CDD_I2C_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "AUTOSAR Version of I2C is incorrect"
#endif

/* vendor specific version information check */
#if ((CDD_I2C_SW_MAJOR_VERSION != (11U)) || (CDD_I2C_SW_MINOR_VERSION != (0U)))
#error "Version numbers of Cdd_I2c.c and Cdd_I2c.h are not matching!"
#endif
#if ((CDD_I2C_CFG_MAJOR_VERSION != (11U)) || (CDD_I2C_CFG_MINOR_VERSION != (0U)))
#error "Version numbers of Cdd_I2c.c and Cdd_I2c_Cfg.h are not matching!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static Std_ReturnType Cdd_I2c_SetupEBParamCheck(uint8 apiId, Cdd_I2c_ChannelType chId,
                                                Cdd_I2c_DataConstPtrType txDataBufferPtr,
                                                Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length);
#endif

/* ========================================================================== */
/*                        Local Object Definitions                            */
/* ========================================================================== */

#define CDD_I2C_START_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"
/* Driver Status */
Cdd_I2c_ComponentStatusType Cdd_I2c_DrvState = CDD_I2C_UNINIT;
#define CDD_I2C_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"

#define CDD_I2C_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"
/* Driver Object */
Cdd_I2c_DriverObjType Cdd_I2c_DrvObj;
#define CDD_I2C_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_I2c_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"

FUNC(void, CDD_I2C_CODE) Cdd_I2c_Init(const Cdd_I2c_ConfigType *configPtr)
{
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (NULL_PTR != configPtr)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_INIT, CDD_I2C_E_PARAM_CONFIG);
    }
    else if (CDD_I2C_UNINIT != Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_INIT, CDD_I2C_E_ALREADY_INITIALIZED);
    }
    else
#endif
    {
        /* Only pre-compile variant supported */
        const Cdd_I2c_ConfigType *localConfigPtr = &Cdd_I2c_Config;
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
        Std_ReturnType retVal;

        retVal = Cdd_I2c_checkConfig(localConfigPtr);
        if (E_OK == retVal)
#endif
        {
            Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;

            Cdd_I2c_resetDrvObj(drvObj);
            Cdd_I2c_copyConfig(drvObj, localConfigPtr);

            /* Init HW once all config is copied */
            for (uint32 hwIdx = 0U; hwIdx < CDD_I2C_MAX_HW_UNIT; hwIdx++)
            {
                Cdd_I2c_HwUnitObjType          *hwUnitObj = &drvObj->hwUnitObj[hwIdx];
                const Cdd_I2c_HwUnitConfigType *hwUnitCfg = hwUnitObj->hwUnitCfg;
                Cdd_I2c_hwInit(hwUnitObj->baseAddr, hwUnitCfg->baudRate, hwUnitCfg->hwUnitFrequency, hwUnitCfg->sysClk,
                               hwUnitCfg->ownAddress);
            }
            Cdd_I2c_DrvState = CDD_I2C_IDLE;
        }
    }

    return;
}

FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_DeInit(void)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_DEINIT, CDD_I2C_E_UNINIT);
        retVal = E_NOT_OK;
    }
    else
#endif
    {
        Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;

        for (uint32 hwIdx = 0U; hwIdx < CDD_I2C_MAX_HW_UNIT; hwIdx++)
        {
            Cdd_I2c_HwUnitObjType *hwUnitObj = &drvObj->hwUnitObj[hwIdx];
            Cdd_I2c_hwDeInit(hwUnitObj->baseAddr);
        }
        Cdd_I2c_DrvState = CDD_I2C_UNINIT;
    }

    return retVal;
}

#if (STD_ON == CDD_I2C_VERSION_INFO_API)
FUNC(void, CDD_I2C_CODE) Cdd_I2c_GetVersionInfo(Std_VersionInfoType *versionInfo)
{
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (NULL_PTR == versionInfo)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_GET_VERSION_INFO,
                              CDD_I2C_E_PARAM_VINFO_PTR);
    }
    else
#endif
    {
        versionInfo->vendorID         = CDD_I2C_VENDOR_ID;
        versionInfo->moduleID         = CDD_I2C_MODULE_ID;
        versionInfo->sw_major_version = (uint8)CDD_I2C_SW_MAJOR_VERSION;
        versionInfo->sw_minor_version = (uint8)CDD_I2C_SW_MINOR_VERSION;
        versionInfo->sw_patch_version = (uint8)CDD_I2C_SW_PATCH_VERSION;
    }

    return;
}
#endif

FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_SetupEB(Cdd_I2c_ChannelType chId, Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                Cdd_I2c_DataLengthType length)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    retVal = Cdd_I2c_SetupEBParamCheck(CDD_I2C_SID_SETUP_EB, chId, txDataBufferPtr, rxDataBufferPtr, length);
    if (E_OK == retVal)
#endif
    {
        Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;
        Cdd_I2c_ChObjType     *chObj  = &drvObj->chObj[chId];

        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();

        chObj->txBufPtr = txDataBufferPtr;
        chObj->rxBufPtr = rxDataBufferPtr;
        chObj->length   = length;
        /* Restore device address from user configuration */
        chObj->deviceAddress = chObj->chCfg->deviceAddress;
        chObj->addressScheme = chObj->chCfg->addressScheme;

        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
    }

    return retVal;
}

FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_SetupEBDynamic(Cdd_I2c_ChannelType chId, Cdd_I2c_AddressType deviceAddress,
                       Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                       Cdd_I2c_DataLengthType length)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    retVal = Cdd_I2c_SetupEBParamCheck(CDD_I2C_SID_SETUP_EB_DYNAMIC, chId, txDataBufferPtr, rxDataBufferPtr, length);
    if ((E_OK == retVal) && (deviceAddress > CDD_I2C_ADDRESS_10_BIT_MAX))
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_SETUP_EB_DYNAMIC,
                              CDD_I2C_E_PARAM_ADDRESS);
        retVal = E_NOT_OK;
    }
    if (E_OK == retVal)
#endif
    {
        Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;
        Cdd_I2c_ChObjType     *chObj  = &drvObj->chObj[chId];

        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();

        chObj->txBufPtr      = txDataBufferPtr;
        chObj->rxBufPtr      = rxDataBufferPtr;
        chObj->length        = length;
        chObj->deviceAddress = deviceAddress;
        /* The API doesn't provide parameter for addressing mode, so derive based on address */
        if (deviceAddress > CDD_I2C_ADDRESS_7_BIT_MAX)
        {
            chObj->addressScheme = CDD_I2C_10_BIT_ADDRESS;
        }
        else
        {
            chObj->addressScheme = CDD_I2C_7_BIT_ADDRESS;
        }

        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
    }

    return retVal;
}

FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_AsyncTransmit(Cdd_I2c_SequenceType sequenceId)
{
    Std_ReturnType retVal = E_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_ASYNC_TRANSMIT, CDD_I2C_E_UNINIT);
    }
    else if (sequenceId >= CDD_I2C_MAX_SEQ)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_ASYNC_TRANSMIT,
                              CDD_I2C_E_PARAM_SEQUENCE);
    }
    else
#endif
    {
        Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;
        Cdd_I2c_SeqObjType    *seqObj = &drvObj->seqObj[sequenceId];

        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();

        /* Pending sequence cannot be queued again */
        if ((CDD_I2C_SEQ_PENDING == seqObj->seqResult) || (CDD_I2C_SEQ_QUEUED == seqObj->seqResult))
        {
            (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_ASYNC_TRANSMIT,
                                  CDD_I2C_E_SEQ_BUSY);
        }
        else
        {
            /* Call the start sequence API */
            retVal = Cdd_I2c_startSeqAsync(drvObj, seqObj);
            if (E_OK != retVal)
            {
                (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_ASYNC_TRANSMIT,
                                      CDD_I2C_E_SEQ_BUSY);
            }
        }

        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
    }

    return retVal;
}

#if (STD_ON == CDD_I2C_CANCEL_API)
FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_Cancel(Cdd_I2c_SequenceType sequenceId)
{
    Std_ReturnType retVal = E_NOT_OK;

    // TODO
    return retVal;
}
#endif

FUNC(void, CDD_I2C_CODE) Cdd_I2c_MainFunction(void)
{
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_MAIN_FUNCTION, CDD_I2C_E_UNINIT);
    }
    else
#endif
    {
#if (STD_ON == CDD_I2C_POLLING_MODE)
        Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;
        Cdd_I2c_HwUnitObjType *hwUnitObj;

        SchM_Enter_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();

        /* Check all hardware units for any pending sequence */
        for (uint32 hwUnitIdx = 0U; hwUnitIdx < drvObj->maxHwUnit; hwUnitIdx++)
        {
            hwUnitObj = &drvObj->hwUnitObj[hwUnitIdx];
            if (NULL_PTR != hwUnitObj->curChObj)
            {
                Cdd_I2c_processEvents(drvObj, hwUnitObj);
            }
        }

        SchM_Exit_Cdd_I2c_I2C_EXCLUSIVE_AREA_0();
#endif
    }

    return;
}

#if (STD_ON == CDD_I2C_POLLING_MODE)
FUNC(void, CDD_I2C_CODE) Cdd_I2c_PollingModeProcessing(void)
{
    /* This API is deprecated and provide only for backward compatibility.
     * Call main handling fxn which does the job */
    Cdd_I2c_MainFunction();
    return;
}
#endif

FUNC(Cdd_I2c_SequenceResultType, CDD_I2C_CODE) Cdd_I2c_GetSequenceResult(Cdd_I2c_SequenceType sequenceId)
{
    Cdd_I2c_SequenceResultType seqResult = CDD_I2C_SEQ_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_GET_SEQUENCE_RESULT,
                              CDD_I2C_E_UNINIT);
    }
    else if (sequenceId >= CDD_I2C_MAX_SEQ)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_GET_SEQUENCE_RESULT,
                              CDD_I2C_E_PARAM_SEQUENCE);
    }
    else
#endif
    {
        Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;
        Cdd_I2c_SeqObjType    *seqObj = &drvObj->seqObj[sequenceId];

        seqResult = seqObj->seqResult;
    }

    return seqResult;
}

FUNC(Cdd_I2c_ChannelResultType, CDD_I2C_CODE) Cdd_I2c_GetResult(Cdd_I2c_ChannelType chId)
{
    Cdd_I2c_ChannelResultType chResult = CDD_I2C_CH_RESULT_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_GET_RESULT, CDD_I2C_E_UNINIT);
    }
    else if (chId >= CDD_I2C_MAX_CH)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_GET_RESULT, CDD_I2C_E_PARAM_CHANNEL);
    }
    else
#endif
    {
        Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;
        Cdd_I2c_ChObjType     *chObj  = &drvObj->chObj[chId];

        chResult = chObj->chResult;
    }

    return chResult;
}

#if (STD_ON == CDD_I2C_GET_STATUS_API)
FUNC(Cdd_I2c_ComponentStatusType, CDD_I2C_CODE) Cdd_I2c_GetStatus(void)
{
    return Cdd_I2c_DrvState;
}
#endif

#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
/**
 * \brief This service reads the key I2C registers and returns their value
 *
 * Service ID[hex] - CDD_I2C_SID_REGISTERREADBACK
 * Sync/Async - Synchronous
 * Reentrancy - Reentrant
 *
 * \return Std_ReturnType - E_OK: Success, E_NOT_OK: Request rejected
 */
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_RegisterReadback(uint8 hwUnitId, Cdd_I2c_RegisterReadbackType *regRbPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
    if (CDD_I2C_UNINIT == Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_REGISTERREADBACK, CDD_I2C_E_UNINIT);
    }
    else if (hwUnitId >= CDD_I2C_HW_UNIT_MAX)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, CDD_I2C_SID_REGISTERREADBACK,
                              CDD_I2C_E_PARAM_HWUNIT);
    }
    else
#endif
    {
        uint32 baseAddr;

        baseAddr = Cdd_I2c_getHwUnitBaseAddr(hwUnitId);
        Cdd_I2c_hwRegReadback(baseAddr, regRbPtr);
        retVal = E_OK;
    }

    return retVal;
}
#endif

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
static Std_ReturnType Cdd_I2c_SetupEBParamCheck(uint8 apiId, Cdd_I2c_ChannelType chId,
                                                Cdd_I2c_DataConstPtrType txDataBufferPtr,
                                                Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length)
{
    Std_ReturnType         retVal = E_OK;
    Cdd_I2c_DriverObjType *drvObj = &Cdd_I2c_DrvObj;

    if (CDD_I2C_UNINIT == Cdd_I2c_DrvState)
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, apiId, CDD_I2C_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((E_OK == retVal) && (chId >= CDD_I2C_MAX_CH))
    {
        (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, apiId, CDD_I2C_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((E_OK == retVal) && (CDD_I2C_WRITE == drvObj->chObj[chId].chCfg->direction))
    {
        if (NULL_PTR == txDataBufferPtr)
        {
            (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, apiId, CDD_I2C_E_PARAM_TRANS_BUFFER);
            retVal = E_NOT_OK;
        }

        if (NULL_PTR != rxDataBufferPtr)
        {
            (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, apiId, CDD_I2C_E_PARAM_DIRECTION);
            retVal = E_NOT_OK;
        }
    }

    if ((E_OK == retVal) && (drvObj->chObj[chId].chCfg->direction == CDD_I2C_READ))
    {
        if (NULL_PTR == rxDataBufferPtr)
        {
            (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, apiId, CDD_I2C_E_PARAM_TRANS_BUFFER);
            retVal = E_NOT_OK;
        }

        if (NULL_PTR != txDataBufferPtr)
        {
            (void)Det_ReportError(CDD_I2C_MODULE_ID, CDD_I2C_INSTANCE_ID, apiId, CDD_I2C_E_PARAM_DIRECTION);
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}
#endif

#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
