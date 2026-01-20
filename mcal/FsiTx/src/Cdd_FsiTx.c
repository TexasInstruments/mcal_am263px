/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Cdd_FsiTx.c *
 *  \brief    This file contains Complex Device Driver for FsiTx *
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_FsiTx.c
 *         Module:  Cdd_FsiTx
 *         Generator:  None
 *
 *  Description: This component provides services for fast serial transmission of the the data
 *through FsiTx
 *********************************************************************************************************************/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_FsiTx.h"

#if (CDD_FSI_TX_DMA_ENABLE == STD_ON)
#include "Cdd_Dma.h"
#endif

#define CDD_FSITX_START_SEC_VAR_NO_INIT_8
#include "Cdd_FsiTx_MemMap.h"
/** \brief CDD_FSI_TX ISR Index */
VAR(uint8, CDD_FSITX_VAR_CLEARED) Cdd_FsiTx_IsrIndex[CDD_FSI_TX_HW_UNIT_CNT];
#define CDD_FSITX_STOP_SEC_VAR_NO_INIT_8
#include "Cdd_FsiTx_MemMap.h"

#define CDD_FSITX_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiTx_MemMap.h"
/** \brief CDD FSI TX driver object */
VAR(Cdd_FsiTx_DriverObjType, CDD_FSITX_VAR_CLEARED) Cdd_FsiTx_DrvObj;
#define CDD_FSITX_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiTx_MemMap.h"

#define CDD_FSITX_START_SEC_VAR_INIT_16
#include "Cdd_FsiTx_MemMap.h"
/** \brief Variable to store driver status */
VAR(Cdd_FsiTx_StatusType, CDD_FSITX_VAR_CLEARED) Cdd_FsiTx_DriverStatus = CDD_FSI_TX_UNINIT;
#define CDD_FSITX_STOP_SEC_VAR_INIT_16
#include "Cdd_FsiTx_MemMap.h"
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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define CDD_FSITX_START_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"

/*  Design:
 *  Requirement(s): SITARAMCU_MCAL-___    */
/*******************************************************************************
 * Cdd_FsiTx_Init
 ******************************************************************************/
/*! \brief      This function will initialize FsiTx Driver Config structure.
 *
 *  \param[in]   Cdd_FsiTx_ConfigType Pointer to Driver Config structure.
 *  \param[out]  void
 *  \context
 ******************************************************************************/
FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_Init(P2CONST(Cdd_FsiTx_ConfigType, AUTOMATIC, CDD_FsiTx_CFG) ConfigurationPtr)
{
    uint8                       hwUnitId  = 0;
    const Cdd_FsiTx_ConfigType *ConfigPtr = (Cdd_FsiTx_ConfigType *)NULL_PTR;
    Cdd_FsiTx_HwUnitObjType    *hwObj;

#if (STD_ON == CDD_FSI_TX_VARIANT_PRE_COMPILE)
    if (ConfigPtr == NULL_PTR)
    {
        ConfigPtr = &CDD_FSI_TX_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == CDD_FsiTx_PRE_COMPILE_VARIANT) */
#if (STD_ON == CDD_FSI_TX_VARIANT_POST_BUILD)
    ConfigPtr = ConfigurationPtr;
#endif /* (STD_ON == CDD_FSI_TX_VARIANT_POST_BUILD) */
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
    if (CDD_FSI_TX_INIT == Cdd_FsiTx_DriverStatus)
    {
        CddFsiTx_ReportDetError(CDD_FSI_TX_INIT_SID, CDD_FSI_TX_E_ALREADY_INITIALIZED);
    }
    else if (ConfigPtr == NULL_PTR)
    {
        CddFsiTx_ReportDetError(CDD_FSI_TX_INIT_SID, CDD_FSI_TX_E_PARAM_POINTER);
    }
    else
#endif
    {
        CddFsiTx_resetDrvObj(&Cdd_FsiTx_DrvObj);
        /* Copy the configuration */
        (void)CddFsiTx_copyConfig(&Cdd_FsiTx_DrvObj, ConfigPtr);

        /* Init HW once all config is copied */
        for (hwUnitId = 0U; hwUnitId < Cdd_FsiTx_DrvObj.maxHwUnit; hwUnitId++)
        {
            hwObj = &(Cdd_FsiTx_DrvObj.hwUnitObj[hwUnitId]);
            (void)CddFsiTx_hwUnitInit(hwObj);
        }
#if (STD_ON == CDD_FSI_TX_NOTIFICATION_ENABLE)
        /* Initialize configured Interrupt Index. */
        for (hwUnitId = 0U; hwUnitId < Cdd_FsiTx_DrvObj.maxHwUnit; hwUnitId++)
        {
            if (hwUnitId == Cdd_FsiTx_DrvObj.hwUnitObj[hwUnitId].hwUnitCfg.hwId)
            {
                Cdd_FsiTx_IsrIndex[hwUnitId] = hwUnitId;
            }
        }
#endif
        Cdd_FsiTx_DriverStatus = CDD_FSI_TX_INIT;
    }

    return;
}

/*******************************************************************************
 * CddFsiTx_GetStatus
 ******************************************************************************/
/*! \brief      Get the Current status of Fsi Tx Driver
 *  \param[in]  void
 *  \param[out]  void
 *******************************************************************************/
FUNC(Cdd_FsiTx_StatusType, CDD_FSITX_CODE)
CddFsiTx_GetStatus(void)
{
    return (Cdd_FsiTx_DriverStatus);
}

/******************************************************************************/
/*******************************************************************************
 * Cdd_FsiTx_DeInit
 ******************************************************************************/
/*! \brief      Deinitializes all the hw uibts of FsiTx driver.
 *  \param[in]  void
 *  \param[out]  void
 *  \context
 ******************************************************************************/

#if (STD_ON == CDD_FSI_TX_DEINIT_API)
FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_DeInit(void)
{
    uint8 hwUnitId;
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
    if (Cdd_FsiTx_DriverStatus == CDD_FSI_TX_UNINIT)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_DEINIT_SID, CDD_FSI_TX_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT) */
    {
        /* Deinit the hardware modules */
        for (hwUnitId = 0U; hwUnitId < Cdd_FsiTx_DrvObj.maxHwUnit; hwUnitId++)
        {
            (void)CddFsiTx_hwUnitDeInit(&Cdd_FsiTx_DrvObj.hwUnitObj[hwUnitId]);
        }
        CddFsiTx_resetDrvObj(&Cdd_FsiTx_DrvObj);
        Cdd_FsiTx_DriverStatus = CDD_FSI_TX_UNINIT;
    }

    return;
}
#endif /*(STD_ON == CDD_FSI_TX_DEINIT_API)*/

/*******************************************************************************
 * Cdd_FsiTx_Reset
 ******************************************************************************/
/*! \brief      Reset the Transmitter Driver.
 *  \param[in]  ResetModule - the module instance on which reset has to be performed.
 *              it can be Master Core Reset, Clock Reset or Ping Counter Reset
 *              hwUnitId: The Tx HwUnit Instance which needs to be reset
 *  \param[out]  void
 *  \context
 ******************************************************************************/

#if (STD_ON == CDD_FSI_TX_RESET_API)
FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_Reset(Cdd_FsiTx_HWUnitType HwUnitId, VAR(Cdd_FsiTx_ResetSubModuleType, AUTOMATIC) ResetModule)
{
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
    if (Cdd_FsiTx_DriverStatus == CDD_FSI_TX_UNINIT)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_RESET_SID, CDD_FSI_TX_E_UNINIT);
    }
#endif
    (void)CddFsiTx_ResetTxSubModules(&Cdd_FsiTx_DrvObj.hwUnitObj[HwUnitId], ResetModule);
    (void)CddFsiTx_ClearResetTxSubModules(&Cdd_FsiTx_DrvObj.hwUnitObj[HwUnitId], ResetModule);
}
#endif /*CDD_FSI_TX_RESET_API*/

/*******************************************************************************
 * Cdd_FsiTx_Ping
 ******************************************************************************/
/*! \brief      Transmits Ping frame based on the mode of trigger.
 *  \param[in]  HwUnitId: The Tx HwUnit Instance which transmits data
 *  \param[out]  void
 ******************************************************************************/

#if (STD_ON == CDD_FSI_TX_PING_API)
FUNC(Std_ReturnType, CDD_FSITX_CODE)
Cdd_FsiTx_Ping(Cdd_FsiTx_HWUnitType HwUnitId)
{
    uint8                    retVal = E_OK;
    Cdd_FsiTx_HwUnitObjType *hwObj;
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
    if (CDD_FSI_TX_UNINIT == Cdd_FsiTx_DriverStatus)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_PING_SID, CDD_FSI_TX_E_UNINIT);
        retVal = E_NOT_OK;
    }
    else
    {
        if (HwUnitId >= CDD_FSI_TX_HW_UNIT_CNT)
        {
            (void)CddFsiTx_ReportDetError(CDD_FSI_TX_PING_SID, CDD_FSI_TX_E_PARAM_VALUE);
            retVal = E_NOT_OK;
        }
    }

#endif
#if (STD_ON == CDD_FSI_TX_PRE_COMPILE_VARIANT)
    const Cdd_FsiTx_ConfigType *ConfigPtr = NULL_PTR;
    if (ConfigPtr == NULL_PTR)
    {
        ConfigPtr = &CDD_FSI_TX_INIT_CONFIG_PC;
    }
#endif

    hwObj   = &(Cdd_FsiTx_DrvObj.hwUnitObj[HwUnitId]);
    retVal |= CddFsiTx_PingTransmit(hwObj);
    if (retVal != E_OK)
    {
        CddFsiTx_ReportRuntimeError(CDD_FSI_TX_PING_SID, CDD_FSI_TX_E_INVALID_EVENT);
    }
    return retVal;
}
#endif /* if (STD_ON == CDD_FSI_TX_PING_API) */

/*******************************************************************************
 * Cdd_FsiTx_BufferLoad
 ******************************************************************************/
/*! \brief      Load the data from Source Buffer to Transmit Buffer.
 *  \param[in]  HwUnitId : The Tx HwUnit Instance which transmits data
 *  \param[in]  SrcBufferPtr: Source Buffer from data to be copied.
 *  \param[in]  Cdd_FsiTx_userData: User Data sent from application for each frame.
 *  \param[in]  TxDataLength: Number of words to be copied for transmission.
 *
 *  \param[out] void
 ******************************************************************************/
#if (STD_ON == CDD_FSI_TX_BUFFER_LOAD_API)
FUNC(Std_ReturnType, CDD_FSITX_CODE)
Cdd_FsiTx_BufferLoad(Cdd_FsiTx_HWUnitType HwUnitId,
                     P2VAR(Cdd_FsiTx_DataBufferType, AUTOMATIC, CDD_FSI_TX_APPL_DATA) SrcBufferPtr,
                     Cdd_FsiTx_DataType Cdd_FsiTx_userData, Cdd_FsiTx_BufferLengthType TxDataLength)
{
    Std_ReturnType            BufferStatus = E_NOT_OK;
    Cdd_FsiTx_DataBufferType *srcbuffer    = NULL;

#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
    if (CDD_FSI_TX_UNINIT == Cdd_FsiTx_DriverStatus)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_BUFFER_LOAD_SID, CDD_FSI_TX_E_UNINIT);
    }
    else if (CDD_FSI_TX_BUSY == Cdd_FsiTx_DriverStatus)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_BUFFER_LOAD_SID, CDD_FSI_TX_E_BUSY);
    }
    else if (NULL_PTR == SrcBufferPtr)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_BUFFER_LOAD_SID, CDD_FSI_TX_E_PARAM_POINTER);
    }
    else
#endif
    {
        srcbuffer = SrcBufferPtr;
        Cdd_FsiTx_HwUnitObjType *hwObj;
        hwObj        = &(Cdd_FsiTx_DrvObj.hwUnitObj[HwUnitId]);
        BufferStatus = CddFsiTx_BufferLoad(hwObj, srcbuffer, Cdd_FsiTx_userData, (uint32)TxDataLength);
        if (BufferStatus != E_OK)
        {
            CddFsiTx_ReportRuntimeError(CDD_FSI_TX_BUFFER_LOAD_SID, CDD_FSI_TX_E_INVALID_EVENT);
        }
    }

    return BufferStatus;
}
#endif /* (STD_ON == CDD_FSI_TX_BUFFER_LOAD_API) */

/*******************************************************************************
 * Cdd_FsiTx_Transmit
 ******************************************************************************/
/*! \brief      Transmits Data frame based on the mode of trigger.
 *  \param[in]  HwUnitId : The Tx HwUnit Instance which transmits data
 *  \param[in]  Cdd_FsiTx_userData: User Data sent from application for each frame.
 *  \param[in]  TxDataLength: Number of words to be copied for transmission.
 *  \param[out] void
 ******************************************************************************/

#if (STD_ON == CDD_FSI_TX_TRANSMIT_API)
FUNC(Std_ReturnType, CDD_FSITX_CODE)
Cdd_FsiTx_Transmit(Cdd_FsiTx_HWUnitType HwUnitId, Cdd_FsiTx_UserDataType userData,
                   Cdd_FsiTx_DataLengthType TxDataLength)
{
    Std_ReturnType           retVal = E_NOT_OK;
    Cdd_FsiTx_HwUnitObjType *hwObj;
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
    if (HwUnitId >= Cdd_FsiTx_DrvObj.maxHwUnit)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_TRANSMIT_SID, CDD_FSI_TX_E_PARAM_VALUE);
    }
#endif
    SchM_Enter_Cdd_FsiTx_FSI_TX_EXCLUSIVE_AREA_0();
    {
        hwObj  = &(Cdd_FsiTx_DrvObj.hwUnitObj[HwUnitId]);
        retVal = CddFsiTx_Transmit(hwObj, userData, TxDataLength);
    }

    SchM_Exit_Cdd_FsiTx_FSI_TX_EXCLUSIVE_AREA_0();

    if (retVal != E_OK)
    {
        CddFsiTx_ReportRuntimeError(CDD_FSI_TX_TRANSMIT_SID, CDD_FSI_TX_E_INVALID_EVENT);
    }
    return retVal;
}
#endif /*(STD_ON == CDD_FSI_TX_TRANSMIT_API)*/

/*******************************************************************************
 * Cdd_FsiTx_GetVersionInfo
 ******************************************************************************/
/*! \brief      The GetVersion Info API gives the version info details..
 *  \param[in]  VersionInfoPtr:Pointer to the buffer which contains version info details
 *  \param[out] void
 ******************************************************************************/
#if (STD_ON == CDD_FSI_TX_GET_VERSION_INFO)
FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_FSI_TX_APPL_DATA) VersionInfoPtr)
{
    if (NULL_PTR == VersionInfoPtr)
    {
#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_GETVERSIONINFO_SID, CDD_FSI_TX_E_PARAM_POINTER);
#endif
    }
    else

    {
        VersionInfoPtr->vendorID         = CDD_FSI_TX_VENDOR_ID;
        VersionInfoPtr->moduleID         = CDD_FSI_TX_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)CDD_FSI_TX_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)CDD_FSI_TX_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)CDD_FSI_TX_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON == CDD_FSI_TX_VERSION_INFO_API) */

/*
 * Design:
 */
/*******************************************************************************
 * Cdd_FsiTx_MainFunction
 ******************************************************************************/
/*! \brief      The MainFunction notify the application in Polling Mode..
 *  \param[in]  None
 *  \param[out] None
 ******************************************************************************/
#if (STD_ON == CDD_FSI_TX_MAIN_FUNCTION_API)
FUNC(void, CDD_FSITX_CODE)
Cdd_FsiTx_MainFunction(void)
{
    Cdd_FsiTx_HWUnitType     hwUnitId = 0;
    Cdd_FsiTx_HwUnitObjType *hwObj;

#if (STD_ON == CDD_FSI_TX_DEV_ERROR_DETECT)
    if (hwUnitId >= Cdd_FsiTx_DrvObj.maxHwUnit)
    {
        (void)CddFsiTx_ReportDetError(CDD_FSI_TX_MAIN_FUNCTION_SID, CDD_FSI_TX_E_PARAM_VALUE);
    }
#endif
    SchM_Enter_Cdd_FsiTx_FSI_TX_EXCLUSIVE_AREA_0();

    for (hwUnitId = 0U; hwUnitId < Cdd_FsiTx_DrvObj.maxHwUnit; hwUnitId++)
    {
        hwObj = &(Cdd_FsiTx_DrvObj.hwUnitObj[hwUnitId]);

        CddFsiTx_MainFunction(hwObj);
    }
    SchM_Exit_Cdd_FsiTx_FSI_TX_EXCLUSIVE_AREA_0();

    return;
}
#endif /*(STD_ON == CDD_FSI_TX_MAIN_FUNCTION_API)*/

#define CDD_FSITX_STOP_SEC_CODE
#include "Cdd_FsiTx_MemMap.h"
