/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     EthTrcv.c
 *
 *  \brief    This file contains ETH TRANCEIVER MCAL driver
 *
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/

#include "SchM_EthTrcv.h"
#include "EthTrcv.h"
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
#include "Det.h"
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
#include "Dem.h"
#include "Std_Types.h"
#include "hw_types.h"
#include "EthTrcv_Priv.h"
#include "EthTrcv_Types.h"
#include "EthIf_Cbk.h"

/*******************************************************************************
 *  VERSION CHECK
 ******************************************************************************/
/* AUTOSAR version information check has to match definition in header file */
/* SourceId :  */
/* DesignId :  */
/* Requirements : SWS_EthTrcv_00006 */

#if ((ETHTRCV_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (ETHTRCV_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (ETHTRCV_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "ETHTRCV: AUTOSAR Version Numbers of ETHTRCV are different"
#endif /* #if ((ETHTRCV_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (ETHTRCV_AR_RELEASE_MINOR_VERSION \
          != (0x03U)) || (ETHTRCV_AR_RELEASE_REVISION_VERSION != (0x01U))) */

#if ((ETHTRCV_SW_MAJOR_VERSION != (10U)) || (ETHTRCV_SW_MINOR_VERSION != (3U)))
#error "Vendor specific version numbers of EthTrcv.c and EthTrcv.h are inconsistent"
#endif /* #if ((ETHTRCV_SW_MAJOR_VERSION != (10U)) || (ETHTRCV_SW_MINOR_VERSION != (3U))) */

#if ((ETHTRCV_CFG_MAJOR_VERSION != (10U)) || (ETHTRCV_CFG_MINOR_VERSION != (3U)))
#error "Version numbers of EthTrcv.c and EthTrcv_Cfg.h are inconsistent!"
#endif /* #if ((ETHTRCV_CFG_MAJOR_VERSION != (10U)) || (ETHTRCV_CFG_MINOR_VERSION != (3U))) */

/*******************************************************************************
 *  STATIC CHECKS
 ******************************************************************************/

/*******************************************************************************
 *  TYPE DEFINITIONS
 ******************************************************************************/
typedef EthTrcv_CtrlObjType *EthTrcv_CtrlObjPtrType;

/*******************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 ******************************************************************************/
#if (STD_ON == ETHTRCV_STARTAUTONEGOTIATION_API)
static inline EthTrcv_CtrlObjPtrType EthTrcv_getCurrCtrlObj(uint8 trcvIdx);
#endif /*#if (STD_ON == ETHTRCV_STARTAUTONEGOTIATION_API) */

/*******************************************************************************
 *  CONSTANT MACRO DEFINITION
 ******************************************************************************/

/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *  LOCAL DATA DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *  GLOBAL DATA DEFINITIONS
 ******************************************************************************/

#define ETHTRCV_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthTrcv_MemMap.h"

/** \brief ETHTRCV Driver Object */
VAR(volatile EthTrcv_StateType, ETH_VAR_ZERO_INIT) EthTrcv_DrvStatus = ETHTRCV_STATE_UNINIT;

#define ETHTRCV_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthTrcv_MemMap.h"

#define ETHTRCV_START_SEC_VAR_INIT_32
#include "EthTrcv_MemMap.h"

/** \brief ETHTRCV Read Command Status */
VAR(volatile uint32, ETHTRCV_VAR_ZERO_INIT) EthTrcv_MdioRdCmdComplete = (uint32)FALSE;

/** \brief ETHTRCV Write Command Status */
VAR(volatile uint32, ETHTRCV_VAR_ZERO_INIT) EthTrcv_MdioWrCmdComplete = (uint32)FALSE;

extern uint32 EthTrcv_ControllerModeChangeFlag[ETHTRCV_MAX_CONTROLLER];

#define ETHTRCV_STOP_SEC_VAR_INIT_32
#include "EthTrcv_MemMap.h"

#define ETHTRCV_START_SEC_VAR_NO_INIT_16
#include "EthTrcv_MemMap.h"

/** \brief ETHTRCV Mdio Read value status */
VAR(volatile uint16, ETHTRCV_VAR_ZERO_INIT) EthTrcv_MdioRdVal;

#define ETHTRCV_STOP_SEC_VAR_NO_INIT_16
#include "EthTrcv_MemMap.h"

#define ETHTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EthTrcv_MemMap.h"
/** \brief Ethernet TRANCEIVER driver object */
/** \brief The default configuration will be set in EthTrcv_Init function */
VAR(EthTrcv_DrvObject, ETHTRCV_VAR_ZERO_INIT) EthTrcv_DrvObj;

#define ETHTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EthTrcv_MemMap.h"

/*******************************************************************************
 *  LOCAL FUNCTION DEFINITIONS
 ******************************************************************************/
#define ETHTRCV_START_SEC_CODE
#include "EthTrcv_MemMap.h"

/*******************************************************************************
 *  API DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * EthTrcv_Init
 ******************************************************************************/
/** \brief      This function initializes the Ethernet Transceiver Driver
 *
 *  \param[in]  CfgPtr - Points to the implementation specific structure
 *
 *  \param[out] None
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_00029, SWS_EthTrcv_00030, SWS_EthTrcv_00032,
 *                SWS_EthTrcv_00033, SWS_EthTrcv_00040, SWS_EthTrcv_00115
 */
FUNC(void, ETHTRCV_CODE) EthTrcv_Init(P2CONST(EthTrcv_ConfigType, AUTOMATIC, ETHTRCV_PBCFG) CfgPtr)
{
    /* Config pointer initialised with NULL_PTR */
    const EthTrcv_ConfigType *ConfigPtr = (EthTrcv_ConfigType *)NULL_PTR;
    uint8                     TrcvIdx   = 0;
    Std_ReturnType            retVal    = (Std_ReturnType)E_OK;
    uint32                    ctrlIdx   = 0U;

#if (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT)
    if (NULL_PTR == CfgPtr)
    {
        /* Assigning module configuration to Config pointer incase of Pre Compile variant */
        ConfigPtr = &ETHTRCV_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == ETHTRCV_PRE_COMPILE_VARIANT) */

#if (STD_ON == ETHTRCV_POST_BUILD_VARIANT || STD_ON == ETHTRCV_LINK_TIME_VARIANT)
    if (NULL_PTR != CfgPtr)
    {
        /* Assigning passed module configuration to Config pointer incase of Post Build variant */
        ConfigPtr = CfgPtr;
    }
#endif /* (STD_ON == ETHTRCV_POST_BUILD_VARIANT || STD_ON == ETHTRCV_LINK_TIME_VARIANT) */

#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (NULL_PTR == ConfigPtr)
    {
        /* EthTrcv Config pointer is NOT valid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_INIT_ID, ETHTRCV_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        for (ctrlIdx = 0U; ctrlIdx < ETHTRCV_MAX_CONTROLLER; ctrlIdx++)
        {
            TrcvIdx = ConfigPtr->pController[ctrlIdx]->trcvIdx;

#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
            if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
            {
                /* EthTrcv TrcvIdx is not valid */
                (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_INIT_ID, ETHTRCV_E_INV_TRCV_IDX);
                retVal = (Std_ReturnType)E_NOT_OK;
            }
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
        }
    }
    if (((Std_ReturnType)E_NOT_OK) != retVal)
    {
        if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
        {
            /* Reset driver object */
            EthTrcv_resetDrvObj(&EthTrcv_DrvObj);
            for (ctrlIdx = 0U; ctrlIdx < ETHTRCV_MAX_CONTROLLER; ctrlIdx++)
            {
                TrcvIdx = ConfigPtr->pController[ctrlIdx]->trcvIdx;

                /* Initialize driver & copy configuration into driver object */
                EthTrcv_DrvObj.ethTrcvCtrlObj[ctrlIdx].ctrlMode = ETHTRCV_MODE_DOWN;
                /* Copy controller config */
                EthTrcv_DrvObj.ethTrcvCtrlObj[ctrlIdx].trcvIdx = TrcvIdx;
                /* Copy port configuration into driver object */
                (void)(void)memcpy(&EthTrcv_DrvObj.ethTrcvCtrlObj[ctrlIdx].ethTrcvCfg, ConfigPtr->pController[ctrlIdx],
                                   sizeof(EthTrcv_ControllerConfigType));
                retVal = EthTrcv_Initilization(ctrlIdx);
            }
            if (((Std_ReturnType)E_NOT_OK) != retVal)
            {
                /* Change driver state to initialized */
                EthTrcv_DrvStatus = ETHTRCV_STATE_INIT;
            }
        }
        else
        {
            for (ctrlIdx = 0U; ctrlIdx < ETHTRCV_MAX_CONTROLLER; ctrlIdx++)
            {
                /* Driver already initialized, just copy configuration Controller index */
                EthTrcv_DrvObj.ethTrcvCtrlObj[ctrlIdx].trcvIdx  = ConfigPtr->pController[ctrlIdx]->trcvIdx;
                EthTrcv_DrvObj.ethTrcvCtrlObj[ctrlIdx].ctrlMode = ETHTRCV_MODE_DOWN;

                /* Copy port configuration into driver object */
                (void)memcpy(&EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx].ethTrcvCfg, ConfigPtr->pController[ctrlIdx],
                             sizeof(EthTrcv_ControllerConfigType));
            }
        }
    }
}

/*******************************************************************************
 * EthTrcv_GetVersionInfo
 ******************************************************************************/
/** \brief      This function will return the version for this module
 *
 *  \param[in]  None
 *
 *  \param[out] Std_VersionInfoType VersionInfoPtr - the structure that will
 *              contain version info after function call.
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/* Requirements : SWS_EthTrcv_00082, SWS_EthTrcv_00093 */

#if (STD_ON == ETHTRCV_VERSION_INFO_API)
FUNC(void, ETHTRCV_CODE)
EthTrcv_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ETHTRCV_APPL_DATA) VersionInfoPtr)
{
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (VersionInfoPtr == NULL_PTR)
    {
        /* EthTrcv Config pointer is NOT valid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_VERSION_ID, ETHTRCV_E_PARAM_POINTER);
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        /* Adding Version details to the pointer */
        VersionInfoPtr->vendorID         = (uint16)ETHTRCV_VENDOR_ID;
        VersionInfoPtr->moduleID         = (uint16)ETHTRCV_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)ETHTRCV_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)ETHTRCV_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)ETHTRCV_SW_PATCH_VERSION;
    }
}
#endif /* #if (STD_ON == ETHTRCV_VERSION_INFO_API) */

/*******************************************************************************
 * EthTrcv_SetTransceiverMode
 ******************************************************************************/
/** \brief      This function Enables/disables the indexed transceiver
 *
 *  \param[in]  uint8 TrcvIdx
 *              EthTrcv_ModeType CtrlMode
 *
 *  \param[out] None
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_00042, SWS_EthTrcv_00043, SWS_EthTrcv_00044
 *                SWS_EthTrcv_00045, SWS_EthTrcv_00046, SWS_EthTrcv_00094
 *                SWS_EthTrcv_00104, SWS_EthTrcv_00047
 */
#if (STD_ON == ETHTRCV_SETTRANSCEIVERMODE_API)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_SetTransceiverMode(uint8 TrcvIdx, EthTrcv_ModeType CtrlMode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in Uninitialised State */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETTRCVMODE_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* EthTrcv TrcvIdx is not valid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETTRCVMODE_ID, ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        if (CtrlMode == EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx].ctrlMode)
        {
            retVal = (Std_ReturnType)E_OK;
        }
        else
        {
            retVal = EthTrcv_SetTransceiverCtrlMode(TrcvIdx, CtrlMode);
        }
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_SETTRANSCEIVERMODE_API) */

/*******************************************************************************
 * EthTrcv_GetTransceiverMode
 ******************************************************************************/
/** \brief      This function obtains the state of the indexed transceiver
 *
 *  \param[in]  uint8 TrcvIdx
 *
 *  \param[out] EthTrcv_ModeType* TrcvModePtr
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_00048, SWS_EthTrcv_00049, SWS_EthTrcv_00050
 *                SWS_EthTrcv_00051, SWS_EthTrcv_00052, SWS_EthTrcv_00053
 *                SWS_EthTrcv_00054
 */
#if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetTransceiverMode(uint8 TrcvIdx, EthTrcv_ModeType *TrcvModePtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETTRCVMODE_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* EthTrcv TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETTRCVMODE_ID, ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == TrcvModePtr)
    {
        /* EthTrcv Config Pointer is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETTRCVMODE_ID, ETHTRCV_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        /* Assigning configuration cntrl mode to pointer */
        *TrcvModePtr = EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx].ctrlMode;
        retVal       = (Std_ReturnType)E_OK;
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API) */

/*******************************************************************************
 * EthTrcv_StartAutoNegotiation
 ******************************************************************************/
/** \brief      This function restarts the negotiation of the transmission
 *              parameters used by the indexed transceiver
 *
 *  \param[in]  uint8 TrcvIdx
 *
 *  \param[out] None
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_00055, SWS_EthTrcv_00056, SWS_EthTrcv_00057
 *                SWS_EthTrcv_00058, SWS_EthTrcv_00059, SWS_EthTrcv_00060
 *                SWS_EthTrcv_00088
 */
#if (STD_ON == ETHTRCV_STARTAUTONEGOTIATION_API)
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_StartAutoNegotiation(uint8 TrcvIdx)
{
    Std_ReturnType                retVal      = (Std_ReturnType)E_NOT_OK;
    EthTrcv_ControllerConfigType *pEthTrcvCfg = (EthTrcv_ControllerConfigType *)NULL_PTR;
    EthTrcv_CtrlObjType          *pEthTrcvObj = (EthTrcv_CtrlObjType *)NULL_PTR;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SRTAUTONEGOTIA_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* EthTrcv TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SRTAUTONEGOTIA_ID,
                              ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        pEthTrcvCfg = &(EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx].ethTrcvCfg);
        pEthTrcvObj = (EthTrcv_CtrlObjType *)EthTrcv_getCurrCtrlObj(TrcvIdx);
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
        /* Checking advertiseCapab for 1000 half NULL or not */
        if (0U != (pEthTrcvCfg->advertiseCapab & (uint32)ETHERNET_ADV_CAPAB_1000_HALF))
        {
            pEthTrcvCfg->advertiseCapab &= ~((uint32)ETHERNET_ADV_CAPAB_1000_HALF);
        }
#endif /* #if (STD_ON == ETHTRCV_1000MBPS_MACRO) */
        if (0U != pEthTrcvCfg->advertiseCapab)
        {
            /* Auto negotiate and get the speed and duplex parameters.
             *  "Reason - pEthTrcvObj cannot be NULL here
             *  as it is ensured by DET error check before calling this func */
            retVal = EthTrcv_configAndStartAutoNegotiation(pEthTrcvObj);
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_STARTAUTONEGOTIATION_API) */

/*******************************************************************************
 * EthTrcv_GetLinkState
 ******************************************************************************/
/** \brief This function Obtains the link state used by the indexed transceiver
 *
 *  \param[in]  uint8 TrcvIdx
 *
 *  \param[out] EthTrcv_LinkStateType* LinkStatePtr
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_00061, SWS_EthTrcv_00062, SWS_EthTrcv_00063
 *                SWS_EthTrcv_00064, SWS_EthTrcv_00065, SWS_EthTrcv_00066
 *                SWS_EthTrcv_00067
 */

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetLinkState(uint8 TrcvIdx, EthTrcv_LinkStateType *LinkStatePtr)
{
    Std_ReturnType retVal       = (Std_ReturnType)E_OK;
    uint32         linkUpStatus = FALSE;

#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETLNKSTATE_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* EthTrcv TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETLNKSTATE_ID, ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == LinkStatePtr)
    {
        /* EthTrcv Config Pointer is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETLNKSTATE_ID, ETHTRCV_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        /* Calling getLinkSatus function */
        linkUpStatus = EthTrcv_getLinkStatus(EthTrcv_DrvObj.ctrlIdx, TrcvIdx);
        if (((uint32)TRUE) == linkUpStatus)
        {
            /* if linkupstatus true then assigning link status as ACTIVE */
            *LinkStatePtr = ETHTRCV_LINK_STATE_ACTIVE;
        }
        else
        {
            /* if linkupstatus false then assigning link status as DOWN */
            *LinkStatePtr = ETHTRCV_LINK_STATE_DOWN;
        }
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETLINKSTATE_API) */

/*******************************************************************************
 * EthTrcv_GetBaudRate
 ******************************************************************************/
/** \brief      This function Obtains the baud rate used by the indexed transceiver
 *
 *  \param[in]  uint8 TrcvIdx
 *
 *  \param[out] EthTrcv_BaudRateType* BaudRatePtr
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_00068, SWS_EthTrcv_00069, SWS_EthTrcv_00070
 *                SWS_EthTrcv_00071, SWS_EthTrcv_00072, SWS_EthTrcv_00073
 *                SWS_EthTrcv_00074, SWS_EthTrcv_00089
 */

#if (STD_ON == ETHTRCV_GETBAUDRATE_API)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetBaudRate(uint8 TrcvIdx, EthTrcv_BaudRateType *BaudRatePtr)
{
    Std_ReturnType       retVal      = (Std_ReturnType)E_OK;
    uint32               baudRate    = 0u;
    uint16               data        = 0u;
    EthTrcv_CtrlObjType *pEthTrcvObj = (EthTrcv_CtrlObjType *)NULL_PTR;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETBAUD_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* EthTrcv TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETBAUD_ID, ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == BaudRatePtr)
    {
        /* EthTrcv Config Pointer is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETBAUD_ID, ETHTRCV_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        pEthTrcvObj = &(EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx]);
        if ((Std_ReturnType)E_OK ==
            EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, ETHTRCV_PHYSTS, &data))
        {
            /* By calling HW_GET_FIELD, getting speeds */
            baudRate = HW_GET_FIELD(data, ETHTRCV_PHYSTS_SPEED);
            switch (baudRate)
            {
                /* For baudRate 10mbps */
                case ETHTRCV_PHYSTS_SPEED_10:
                    *BaudRatePtr = ETHTRCV_BAUD_RATE_10MBIT;
                    retVal       = (Std_ReturnType)E_OK;
                    break;
                /* For baudRate 100mbps */
                case ETHTRCV_PHYSTS_SPEED_100:
                    *BaudRatePtr = ETHTRCV_BAUD_RATE_100MBIT;
                    retVal       = (Std_ReturnType)E_OK;
                    break;
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
                /* For baudRate 1000mbps */
                case ETHTRCV_PHYSTS_SPEED_1000:
                    *BaudRatePtr = ETHTRCV_BAUD_RATE_1000MBIT;
                    retVal       = (Std_ReturnType)E_OK;
                    break;
#endif /* #if (STD_ON == ETHTRCV_1000MBPS_MACRO) */
                default:
                    retVal = (Std_ReturnType)E_NOT_OK;
                    break;
            }
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETBAUDRATE_API) */

/*******************************************************************************
 * EthTrcv_GetDuplexMode
 ******************************************************************************/
/** \brief This function Obtains the duplex mode used by the indexed transceiver
 *
 *  \param[in]  uint8 TrcvIdx
 *
 *  \param[out] EthTrcv_DuplexModeType* DuplexModePtr
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_00075, SWS_EthTrcv_00076, SWS_EthTrcv_00077
 *                SWS_EthTrcv_00078, SWS_EthTrcv_00079, SWS_EthTrcv_00080
 *                SWS_EthTrcv_00081, SWS_EthTrcv_00090
 */
#if (STD_ON == ETHTRCV_GETDUPLEXMODE_API)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetDuplexMode(uint8 TrcvIdx, EthTrcv_DuplexModeType *DuplexModePtr)
{
    Std_ReturnType       retVal = (Std_ReturnType)E_OK;
    uint32               duplexMode;
    uint16               data        = 0u;
    EthTrcv_CtrlObjType *pEthTrcvObj = (EthTrcv_CtrlObjType *)NULL_PTR;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETDPLXMODE_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* EthTrcv TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETDPLXMODE_ID, ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == DuplexModePtr)
    {
        /* EthTrcv Config Pointer is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETDPLXMODE_ID, ETHTRCV_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        pEthTrcvObj = &(EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx]);
        if ((Std_ReturnType)E_OK ==
            EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, ETHTRCV_PHYSTS, &data))
        {
            /* Getting duplex mode status and storing in varaible */
            duplexMode = HW_GET_FIELD(data, ETHTRCV_PHYSTS_DUPLEX_MODE);
            /* Half Duplex mode */
            if (ETHTRCV_BMC_DUPLEX_MODE_HALF == duplexMode)
            {
                *DuplexModePtr = ETHTRCV_DUPLEX_MODE_HALF;
                retVal         = (Std_ReturnType)E_OK;
            }
            else
            /* Full Duplex mode */
            {
                *DuplexModePtr = ETHTRCV_DUPLEX_MODE_FULL;
                retVal         = (Std_ReturnType)E_OK;
            }
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETDUPLEXMODE_API) */

/*******************************************************************************
 * Callback notifications
 ******************************************************************************/
/*******************************************************************************
 * EthTrcv_ReadMiiIndication
 ******************************************************************************/
/** \brief      This function is callback function from Eth driver indicating
 *              transceiver read is complete.
 *  \param[in]  uint8 CtrlIdx
 *              uint8 TrcvIdx
 *              uint8 RegId
 *              uint8 RegVal
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/* Requirements : SWS_EthTrcv_00108 */

FUNC(void, ETHTRCV_CODE)
EthTrcv_ReadMiiIndication(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
    EthTrcv_MdioRdVal         = RegVal;
    EthTrcv_MdioRdCmdComplete = (uint32)TRUE;
}

/*******************************************************************************
 * EthTrcv_WriteMiiIndication
 ******************************************************************************/
/** \brief      This function is callback function from Eth driver indicating
 * transceiver write is .
 *          complete
 *  \param[in]  uint8 CtrlIdx
 *              uint8 TrcvIdx
 *              uint8 RegId
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/* Requirements : SWS_EthTrcv_00109 */
FUNC(void, ETHTRCV_CODE) EthTrcv_WriteMiiIndication(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegId)
{
    EthTrcv_MdioWrCmdComplete = (uint32)TRUE;
}

/*******************************************************************************
 * Scheduled function
 ******************************************************************************/

/*******************************************************************************
 * EthTrcv_MainFunction
 ******************************************************************************/
/** \brief      This function is used for polling state changes and wakeup
 *              reasons.
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/* Requirements : SWS_EthTrcv_00106, SWS_EthTrcv_00107, SWS_EthTrcv_00142 */
FUNC(void, ETHTRCV_CODE) EthTrcv_MainFunction(void)
{
#if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API)
    Std_ReturnType   retVal = E_OK;
    EthTrcv_ModeType ctrlMode;
    uint8            trcvIdx = 0u;
    uint32           tempVal = 0u;
#endif /* #if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API) */

#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_MAINFCT_WRITE_ID, ETHTRCV_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
#if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API)
        for (trcvIdx = 0U; trcvIdx < ETHTRCV_MAX_CONTROLLER; trcvIdx++)
        {
            tempVal = EthTrcv_ControllerModeChangeFlag[trcvIdx];
            if (((uint32)TRUE) == tempVal)
            {
                /* storing transceiver mode status */
                retVal = EthTrcv_GetTransceiverMode(trcvIdx, &ctrlMode);
                if (((Std_ReturnType)E_OK) == retVal)
                {
                    EthIf_TrcvModeIndication(trcvIdx, ctrlMode);
                    EthTrcv_ControllerModeChangeFlag[trcvIdx] = (uint32)FALSE;
                }
            }
            else
            {
                /* do nothing */
            }
        }
#endif /* #if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API) */
    }
}

/*******************************************************************************
 * EthTrcv_SetPhyLoopbackMode
 ******************************************************************************/
/** \brief      This function activates a given loopback mode for the indexed Transceiver.
 *
 *  \param[in]  uint8 TrcvIdx
 *              EthTrcv_PhyTestModeType Mode
 *
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_91005, SWS_EthTrcv_00149
 */

FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_SetPhyLoopbackMode(uint8 TrcvIdx, EthTrcv_PhyLoopbackModeType Mode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYLOOPBCKMODE_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYLOOPBCKMODE_ID,
                              ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if ((Mode != ETHTRCV_PHYLOOPBACK_NONE) && (Mode != ETHTRCV_PHYLOOPBACK_INTERNAL) &&
             (Mode != ETHTRCV_PHYLOOPBACK_EXTERNAL))
    {
        /* Mode is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYLOOPBCKMODE_ID,
                              ETHTRCV_E_NOT_SUPPORTED);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        retVal = EthTrcv_ConfigSetPhyLoopbackMode(TrcvIdx, Mode);
    }
    return retVal;
}

#if (STD_ON == ETHTRCV_SETPHYTXMODE_API)
/*******************************************************************************
 * EthTrcv_SetPhyTxMode
 ******************************************************************************/
/** \brief      This function activates a given transmission mode for the indexed Transceiver.
 *
 *  \param[in]  uint8 TrcvIdx
 *              EthTrcv_PhyTxModeType Mode
 *
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_91007, SWS_EthTrcv_00148
 */

FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyTxMode(uint8 TrcvIdx, EthTrcv_PhyTxModeType Mode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYTXMODE_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYTXMODE_ID, ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if ((Mode != ETHTRCV_PHYTXMODE_NORMAL) && (Mode != ETHTRCV_PHYTXMODE_SCRAMBLER_OFF))
    {
        /* Mode is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYTXMODE_ID, ETHTRCV_E_NOT_SUPPORTED);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        retVal = EthTrcvSettingStatusPhyTxMode(TrcvIdx, Mode);
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_SETPHYTXMODE_API) */

#if (STD_ON == ETHTRCV_GETCABLEDIAGNOSTICSRESULT_API)
/*******************************************************************************
 * EthTrcv_GetCableDiagnosticsResult
 ******************************************************************************/
/** \brief      This function retrieves the cable diagnostics result of a given transceiver
 *
 *  \param[in]  uint8 TrcvIdx
 *              EthTrcv_CableDiagResultType* ResultPtr
 *
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_91009
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetCableDiagnosticsResult(uint8 TrcvIdx, EthTrcv_CableDiagResultType *ResultPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETCBLDIAGNSTICRSLT_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETCBLDIAGNSTICRSLT_ID,
                              ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == ResultPtr)
    {
        /* API is being called with invalid param */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETCBLDIAGNSTICRSLT_ID,
                              ETHTRCV_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        retVal = EthTrcv_ReadCableDiagResult(TrcvIdx, ResultPtr);
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETCABLEDIAGNOSTICSRESULT_API) */

#if (STD_ON == ETHTRCV_GETPHYIDENTIFIER_API)
/*******************************************************************************
 * EthTrcv_GetPhyIdentifier
 ******************************************************************************/
/** \brief  This function will obtain the PHY identifier of the Ethernet
 *          Transceiver according to IEEE 802.3-2015 chapter 22.2.4.3.1 PHY
 *          Identifier.
 *
 *  \param[in]  uint8 TrcvIdx
 *              uint32* OrgUniqueIdPtr
 *              uint8* ModelNrPtr
 *              uint8* RevisionNrPtr
 *
 *  \param[out] uint32* OrgUniqueIdPtr
 *              uint8* ModelNrPtr
 *              uint8* RevisionNrPtr
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_91010
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetPhyIdentifier(uint8 TrcvIdx, uint32 *OrgUniqueIdPtr, uint8 *ModelNrPtr, uint8 *RevisionNrPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETPHYIDENTIFIER_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETPHYIDENTIFIER_ID,
                              ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if ((NULL_PTR == OrgUniqueIdPtr) || (NULL_PTR == ModelNrPtr) || (NULL_PTR == RevisionNrPtr))
    {
        /* API is being called with invalid param */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_GETPHYIDENTIFIER_ID,
                              ETHTRCV_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        retVal = EthTrcv_GetPhyIdentifierRead(TrcvIdx, OrgUniqueIdPtr, ModelNrPtr, RevisionNrPtr);
    }
    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETPHYIDENTIFIER_API) */

#if (STD_ON == ETHTRCV_SETPHYTESTMODE_API)
/*******************************************************************************
 * EthTrcv_SetPhyTxMode
 ******************************************************************************/
/** \brief      This function activates a given transmission mode for the indexed Transceiver.
 *
 *  \param[in]  uint8 TrcvIdx
 *              EthTrcv_PhyTxModeType Mode
 *
 *
 *  \context    App
 ******************************************************************************/
/* SourceId :  */
/* DesignId :  */
/*
 * Requirements : SWS_EthTrcv_91003, SWS_EthTrcv_00147
 *
 *
 */

FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_SetPhyTestMode(uint8 TrcvIdx, EthTrcv_PhyTestModeType Mode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
    if (ETHTRCV_STATE_INIT != EthTrcv_DrvStatus)
    {
        /* EthTrcv is in uninitialised state */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYTESTMODE_ID, ETHTRCV_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (TrcvIdx >= ETHTRCV_MAX_CONTROLLER)
    {
        /* TrcvIdx is invalid */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYTESTMODE_ID,
                              ETHTRCV_E_INV_TRCV_IDX);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if ((Mode != ETHTRCV_PHYTESTMODE_NONE) && (Mode != ETHTRCV_PHYTESTMODE_2) && (Mode != ETHTRCV_PHYTESTMODE_3) &&
             (Mode != ETHTRCV_PHYTESTMODE_4))
    {
        /* Api is called with invalid mode */
        (void)Det_ReportError(ETHTRCV_MODULE_ID, ETHTRCV_INSTANCE_ID, ETHTRCV_SETPHYTESTMODE_ID,
                              ETHTRCV_E_NOT_SUPPORTED);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
    {
        retVal = EthTrcv_HwSetPhyTestMode(TrcvIdx, Mode);
    }
    return retVal;
}
#endif /*#if (STD_ON == ETHTRCV_SETPHYTESTMODE_API) */

#if (STD_ON == ETHTRCV_STARTAUTONEGOTIATION_API)
static inline EthTrcv_CtrlObjPtrType EthTrcv_getCurrCtrlObj(uint8 trcvIdx)
{
    return (&EthTrcv_DrvObj.ethTrcvCtrlObj[trcvIdx]);
}
#endif /* #if (STD_ON == ETHTRCV_STARTAUTONEGOTIATION_API) */

#if (ETHTRCV_WAKEUPSUPPORT_API != ETHTRCV_WAKEUP_NOT_SUPPORTED)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_SetTransceiverWakeupMode(uint8 TrcvIdx, EthTrcv_WakeupModeType TrcvWakeupMode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    return retVal;
}
#endif /* #if (ETHTRCV_WAKEUPSUPPORT_API != ETHTRCV_WAKEUP_NOT_SUPPORTED) */

#if (ETHTRCV_GETTRANSCEIVERWAKEUPMODE_API == STD_ON)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetTransceiverWakeupMode(uint8 TrcvIdx, EthTrcv_WakeupModeType *TrcvWakeupModePtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    return retVal;
}
#endif /* #if (ETHTRCV_GETTRANSCEIVERWAKEUPMODE_API == STD_ON) */

#if (ETHTRCV_GETPHYSIGNALQUALITY_API == STD_ON)
FUNC(Std_ReturnType, ETHTRCV_CODE)
EthTrcv_GetPhySignalQuality(uint8 TrcvIdx, uint32 *SignalQualityPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    return retVal;
}
#endif /* #if (ETHTRCV_GETPHYSIGNALQUALITY_API == STD_ON) */

#if (ETHTRCV_WAKEUPSUPPORT_API != ETHTRCV_WAKEUP_NOT_SUPPORTED)
FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_CheckWakeup(uint8 TrcvIdx)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    return retVal;
}
#endif /* #if (ETHTRCV_WAKEUPSUPPORT_API != ETHTRCV_WAKEUP_NOT_SUPPORTED) */

#define ETHTRCV_STOP_SEC_CODE
#include "EthTrcv_MemMap.h"
