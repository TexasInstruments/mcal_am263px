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
 *  \file     Cdd_FsiRx.c
 *
 *  \brief    This file contains Complex Device Driver for FsiRx
 *
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_FsiRx.c
 *       Module:  Cdd_FsiRx
 *    Generator:  None
 *
 *  Description: This component provides services for fast seial reception  between different core
 *in the this Multicore SoC.
 *********************************************************************************************************************/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_FsiRx.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if (CDD_FSI_RX_DMA_ENABLE == STD_ON)
#include "Cdd_Dma.h"
#endif

#define CDD_FSIRX_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiRx_MemMap.h"
/** \brief CDD FSI RX driver object */
VAR(CddFsiRx_StatusType, CDD_FSIRX_VAR_CLEARED)
Cdd_FsiRx_DriverStatus;
#define CDD_FSIRX_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Cdd_FsiRx_MemMap.h"
extern VAR(CddFsiRx_DriverObjType, CDD_FSIRX_VAR_CLEARED) Cdd_FsiRx_DrvObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_FSIRX_START_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"

/*******************************************************************************
 * Cdd_FsiRx_Init
 ******************************************************************************/
/*! \brief      This function will initialize FsiRx Driver Config structure.
 *
 *  \param[in]   Cdd_FsiRx_ConfigType Pointer to Driver Config structure.
 *  \param[out]  void
 *  \context
 ******************************************************************************/

FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_Init(P2CONST(Cdd_FsiRx_ConfigType, AUTOMATIC, CDD_FsiRx_CFG) ConfigurationPtr)
{
    uint8                       HwUnitId  = 0;
    const Cdd_FsiRx_ConfigType *ConfigPtr = (Cdd_FsiRx_ConfigType *)NULL_PTR;
    Cdd_FsiRx_HwUnitObjType    *hwObj;

#if (STD_ON == CDD_FSI_RX_VARIANT_PRE_COMPILE)
    if (ConfigPtr == NULL_PTR)
    {
        ConfigPtr = &CDD_FSI_RX_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == CDD_FsiRx_PRE_COMPILE_VARIANT) */
#if (STD_ON == CDD_FSI_RX_VARIANT_POST_BUILD)
    ConfigPtr = ConfigurationPtr;
#endif /* (STD_ON == CDD_FSI_RX_VARIANT_POST_BUILD) */
#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
    if (CDD_FSI_RX_UNINIT != Cdd_FsiRx_DriverStatus)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_INIT_SID, CDD_FSI_RX_E_ALREADY_INITIALIZED);
    }
    else if (ConfigPtr == NULL_PTR)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_INIT_SID, CDD_FSI_RX_E_PARAM_POINTER);
    }
    else
#endif
    {
        CddFsiRx_resetDrvObj(&Cdd_FsiRx_DrvObj);
        /* Copy the configuration */
        CddFsiRx_copyConfig(&Cdd_FsiRx_DrvObj, ConfigPtr);

        /* Init HW once all config is copied */
        for (HwUnitId = 0U; HwUnitId < ConfigPtr->maxHwUnit; HwUnitId++)
        {
            hwObj = &(Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitId]);
            CddFsiRx_hwUnitInit(hwObj);
        }
        Cdd_FsiRx_DriverStatus = CDD_FSI_RX_INIT;
    }
}

/*******************************************************************************
 * Cdd_FsiRx_GetStatus
 ******************************************************************************/
/*! \brief      Gets the current status of the Rx driver.
 *  \param[in]  void
 *  \param[out]  void
 *  \context
 ******************************************************************************/
FUNC(CddFsiRx_StatusType, CDD_FSIRX_CODE)
CddFsiRx_GetStatus(void)
{
    return (Cdd_FsiRx_DriverStatus);
}

/*******************************************************************************
 * Cdd_FsiRx_DeInit
 ******************************************************************************/
/*! \brief      Deinitializes all the hw units of FsiRx driver.
 *
 *  \param[in]  void
 *
 *  \param[out]  void
 *
 *  \context
 ******************************************************************************/

#if (STD_ON == CDD_FSI_RX_DEINIT_API)

FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_DeInit(void)
{
    uint8 HwUnitId;

#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
    if (Cdd_FsiRx_DriverStatus == CDD_FSI_RX_UNINIT)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_DEINIT_SID, CDD_FSI_RX_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT) */
    {
        /* Deinit the hardware modules */
        for (HwUnitId = 0U; HwUnitId < Cdd_FsiRx_DrvObj.maxHwUnit; HwUnitId++)
        {
            (void)CddFsiRx_hwUnitDeInit(&Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitId]);
        }
        CddFsiRx_resetDrvObj(&Cdd_FsiRx_DrvObj);

        Cdd_FsiRx_DriverStatus = CDD_FSI_RX_UNINIT;
    }

    return;
}
#endif /*(STD_ON == CDD_FSI_RX_DEINIT_API)*/

/*******************************************************************************
 * Cdd_FsiRx_MainFunction
 ******************************************************************************/
/*! \brief      The MainFunction notify the application in Polling Mode.
 *  \param[in]  void
 *  \param[out] void
 *  \context
 ******************************************************************************/
#if (STD_ON == CDD_FSI_RX_MAIN_FUNCTION_API)
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_MainFunction(void)
{
    Cdd_FsiRx_HWUnitType     HwUnitId = 0;
    Cdd_FsiRx_HwUnitObjType *hwObj    = NULL_PTR;
    SchM_Enter_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0();

    for (HwUnitId = 0U; HwUnitId < Cdd_FsiRx_DrvObj.maxHwUnit; HwUnitId++)
    {
        hwObj = &(Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitId]);

        CddFsiRx_Receive(hwObj);
    }
    SchM_Exit_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0();

    return;
}
#endif /*(STD_ON == CDD_FSI_RX_MAIN_FUNCTION_API)*/

/*******************************************************************************
 * Cdd_FsiRx_GetVersionInfo
 ******************************************************************************/
/*! \brief      The GetVersion Info API gives the version info details..
 *  \param[in]  VersionInfoPtr : Pointer to the buffer containing version information.
 *  \param[out] void
 ******************************************************************************/
#if (STD_ON == CDD_FSI_RX_GET_VERSION_INFO)
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CDD_FsiRx_APPL_DATA) VersionInfoPtr)
{
#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_GETVERSIONINFO_SID, CDD_FSI_RX_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON == CDD_FsiRx_DEV_ERROR_DETECT) */
    {
        VersionInfoPtr->vendorID         = CDD_FSI_RX_VENDOR_ID;
        VersionInfoPtr->moduleID         = CDD_FSI_RX_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)CDD_FSI_RX_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)CDD_FSI_RX_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)CDD_FSI_RX_SW_PATCH_VERSION;
    }
}
#endif /* (STD_ON == CDD_FSI_RX_VERSION_INFO_API) */

/*******************************************************************************
 * Cdd_FsiRx_Reset
 ******************************************************************************/
/*! \brief      This API resets the Receiver when a sof reset is needed.
 *  \param[in]  HwUnitId    : HwUnit Instance to be reset.
 *  \param[in]  ResetModule : The submodule to be reset. For ex; main core, frame watchdog
 *  \param[out] void
 ******************************************************************************/

#if (STD_ON == CDD_FSI_RX_RESET_API)
FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_Reset(Cdd_FsiRx_HWUnitType HwUnitId, VAR(Cdd_FsiRx_ResetSubModuleType, AUTOMATIC) ResetModule)
{
#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
    if (Cdd_FsiRx_DriverStatus == CDD_FSI_RX_UNINIT)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_RESET_SID, CDD_FSI_RX_E_UNINIT);
    }
#endif
    (void)CddFsiRx_ResetRxSubModules(&Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitId], ResetModule);
    (void)CddFsiRx_ClearResetRxSubModules(&Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitId], ResetModule);
}
#endif /*(STD_ON == CDD_FSI_RX_RESET_API)*/

/*******************************************************************************
 * Cdd_FsiRx_setUpBuffer
 ******************************************************************************/
/*! \brief      The Cdd_FsiRx_setUpBuffer setup buffer for each instances to copy data during
 *reception. Parameters (in)     : HwUnitId : HwUnit Instance which receives data RxDataLength:
 *Number of words received in a frame Parameters (inOut)  : DataBufferPtr : Pointer to the
 *Application Buffer to which data to be copied
 ******************************************************************************/

FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_setUpBuffer(Cdd_FsiRx_HWUnitType HwUnitId,
                      P2VAR(Cdd_FsiRx_DataBufferType, AUTOMATIC, CDD_FSI_RX_APPL_DATA) DataBufferPtr,
                      CddFsiRx_DataLengthType RxDataLength)
{
    Cdd_FsiRx_HwUnitObjType *hwObj    = (Cdd_FsiRx_HwUnitObjType *)NULL_PTR;
    uint32                   baseAddr = 0;
#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
    if (Cdd_FsiRx_DriverStatus == CDD_FSI_RX_UNINIT)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_SETUP_BUFFER_SID, CDD_FSI_RX_E_UNINIT);
    }
    else if (HwUnitId >= Cdd_FsiRx_DrvObj.maxHwUnit)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_SETUP_BUFFER_SID, CDD_FSI_RX_E_PARAM_VALUE);
    }
    else if ((RxDataLength < (uint16)CDD_FSI_RX_MIN_LEN_WORDS_DATA) ||
             (RxDataLength > (uint16)(CDD_FSI_RX_MAX_LEN_WORDS_DATA)))
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_SETUP_BUFFER_SID, CDD_FSI_RX_E_PARAM_VALUE);
    }
    else
#endif
    {
        SchM_Enter_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0();

        hwObj = &Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitId];
        /*Application Buffer adress is copied to th internal hardware unit buffer so that data will
        get copied from Rx internal buffer to Application buffer directly*/
        hwObj->rxBuffer    = DataBufferPtr;
        hwObj->rxDataWidth = RxDataLength;
        baseAddr           = hwObj->hwUnitCfg.baseAddr;
        CddFsiRx_SetRxSoftwareFrameSize(baseAddr, RxDataLength);
        SchM_Exit_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0();
    }
}

/*******************************************************************************
 * Cdd_FsiRx_DmaDataReceive
 ******************************************************************************/
/*! \brief      The Cdd_FsiRx_DmaDataReceive copies data from Rx internal buffer to the application
 *buffer. Parameters (in)     : HwUnitId : HwUnit Instance which receives data
 *
 *  Parameters (inOut)  : None.
 ******************************************************************************/

FUNC(void, CDD_FSIRX_CODE)
Cdd_FsiRx_DmaDataReceive(Cdd_FsiRx_HWUnitType HwUnitId)
{
    Cdd_FsiRx_HwUnitObjType *hwObj = (Cdd_FsiRx_HwUnitObjType *)NULL_PTR;
#if (STD_ON == CDD_FSI_RX_DEV_ERROR_DETECT)
    if (Cdd_FsiRx_DriverStatus == CDD_FSI_RX_UNINIT)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_DMA_DATA_RECEIVE_SID, CDD_FSI_RX_E_UNINIT);
    }
    else if (HwUnitId >= Cdd_FsiRx_DrvObj.maxHwUnit)
    {
        CddFsiRx_ReportDetError(CDD_FSI_RX_DMA_DATA_RECEIVE_SID, CDD_FSI_RX_E_PARAM_VALUE);
    }
    else
#endif
    {
        SchM_Enter_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0();
        hwObj = &Cdd_FsiRx_DrvObj.hwUnitObj[HwUnitId];
        CddFsiRx_Receive(hwObj);
        SchM_Exit_Cdd_FsiRx_FSI_RX_EXCLUSIVE_AREA_0();
    }
}

#define CDD_FSIRX_STOP_SEC_CODE
#include "Cdd_FsiRx_MemMap.h"
