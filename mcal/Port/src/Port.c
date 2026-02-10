/* =============================================================================
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
 * ========================================================================== */

/**
 *  \file     Port.c
 *
 */
/*  ----------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  File      :  Port.c
 *  Project   :  AM263 MCAL Driver
 *  Module    :  PortDriver
 *  Generator :  -
 *
 *  Description:  This module implements a driver in ANSI C programming language
 *                to centralize the configuration of ports and pins which are
 *                used by more than one driver module.
 *                With this driver you can:
 *                - Configure all port pins
 *                - Initialize the configuration
 *                - Refresh the configuration (EMC purposes)
 *                - Switch the port pin configuration during runtime*/
/*****************************************************************************/

/* Common Design ID's */
/*
 *Design:
 *MCAL-13980,MCAL-14006,MCAL-14029,MCAL-13963,MCAL-13971,MCAL-14005,MCAL-14009,MCAL-14020,MCAL-14027,MCAL-14030,MCAL-14040,MCAL-14047,MCAL-13975,MCAL-13978,MCAL-13969,MCAL-14011,MCAL-13970,MCAL-14010,MCAL-13968,MCAL-13990,MCAL-13880,MCAL-16346
 */

#define PORT_SOURCE (1)

/* ========================================================================== */
/*                          Include Files                                     */
/* ========================================================================== */
#include "Std_Types.h"
#include "Port.h"
#include "Port_Priv.h"
#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* #if (PORT_DEV_ERROR_DETECT == STD_ON) */
#include "Os.h"
#include "SchM_Port.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((PORT_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (PORT_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (PORT_AR_RELEASE_MINOR_VERSION != (0x03U)) || (PORT_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "Port: AUTOSAR Version Numbers of Port Driver are different"
#endif

/* Vendor specific version */
#if ((PORT_SW_MAJOR_VERSION != (10U)) || (PORT_SW_MINOR_VERSION != (2U)))
#error "Vendor specific version numbers of Port.c and Port.h are inconsistent"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((PORT_CFG_MAJOR_VERSION != (10U)) || (PORT_CFG_MINOR_VERSION != (2U)))
#error "Version numbers of Port.c and Port_Cfg.h are inconsistent!"
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if (STD_ON == PORT_DEV_ERROR_DETECT)
static boolean Port_ValidateSetPinMode(Port_PinModeType Mode, const Port_PinConfigType *pinConfig, uint8 *errorIdPtr);
static boolean Port_ValidateSetPinDirection(const Port_PinConfigType *pinConfig, Port_PinModeType curMode,
                                            uint8 *errorIdPtr);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */

#if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API))
static Port_PinModeType Port_GetCurrentPinMode(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padCfg);
#endif /* #if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == \
          PORT_REFRESH_PORT_DIRECTION_API))   */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
static const Port_PinConfigType *Port_MapPinIdToPinConfig(Port_PinType PinId, const Port_PinConfigType modeCfg[],
                                                          uint16 numPins);
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))   */

static void Port_InitPadList(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padList, uint16 elements);

#if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API)
static void Port_RefreshPortDirection_Internal(void);
static void Port_RefreshDioPinDirection(const Port_PinConfigType *pinConfig);
#endif
#if (STD_ON == PORT_DEV_ERROR_DETECT)
static boolean Port_ValidateSetPinMode_internal(const Port_PinConfigType *pinConfig, Port_PinModeType Mode,
                                                uint8 *errorIdPtr, uint32 idx);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define PORT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"
/** \brief PORT driver object */
VAR(Port_ConfigType, PORT_VAR_ZERO_INIT) Port_DrvObj;
#define PORT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"

#define PORT_START_SEC_VAR_INIT_UNSPECIFIED
#include "Port_MemMap.h"
#if (STD_ON == PORT_DEV_ERROR_DETECT)
/* Global Init Done flag */
static boolean Port_InitDone = FALSE;
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
#define PORT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Port_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/*
 *Design:MCAL-13961,MCAL-14016,MCAL-14015,MCAL-13981,MCAL-13985,MCAL-13979,MCAL-13966,MCAL-13960,MCAL-13962,MCAL-13993,MCAL-13965,MCAL-14012,MCAL-14013,MCAL-14018,MCAL-14031,MCAL-14028,MCAL-14032
 */
FUNC(void, PORT_CODE) Port_Init(P2CONST(Port_ConfigType, AUTOMATIC, PORT_PBCFG) ConfigPtr)
{
    const Port_ConfigType *CfgPtr = (Port_ConfigType *)NULL_PTR;

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    if (NULL_PTR == ConfigPtr)
    {
        CfgPtr = &PORT_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == PORT_PRE_COMPILE_VARIANT) */

#if (STD_ON == PORT_POST_BUILD_VARIANT)
    CfgPtr = ConfigPtr;
#endif /* (STD_ON == PORT_POST_BUILD_VARIANT) */

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Call of Errorhook if parameter refers to NULL */
    if (NULL_PTR == CfgPtr)
    {
        Port_ReportDetError(PORT_SID_INIT, PORT_E_INIT_FAILED);
    }
    else
#endif /* (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        /* Copy Config */
        (void)memcpy(&Port_DrvObj, CfgPtr, sizeof(Port_ConfigType));

        Port_DioInit();

        /* Set all registers to configured values */
        Port_InitPadList(Port_DrvObj.PinConfig_pt, Port_DrvObj.NumberOfPortPins);

#if (STD_ON == PORT_DEV_ERROR_DETECT)
        /* Set Init Done flag */
        Port_InitDone = TRUE;
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
    return;
}

#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
#if (STD_ON == PORT_DEV_ERROR_DETECT)
static boolean Port_ValidateSetPinDirection(const Port_PinConfigType *pinConfig, Port_PinModeType curMode,
                                            uint8 *errorIdPtr)
{
    boolean retVal = FALSE;

    if ((pinConfig != NULL) && (curMode != PORT_PIN_MODE_INVALID))
    {
        if (pinConfig->Port_DirectionChangeable == (boolean)TRUE)
        {
            retVal = (boolean)TRUE;
        }
        else
        {
            retVal      = (boolean)FALSE;
            *errorIdPtr = PORT_E_DIRECTION_UNCHANGEABLE;
        }
    }
    else
    {
        *errorIdPtr = PORT_E_PARAM_PIN;
        retVal      = (boolean)FALSE;
    }
    return (retVal);
}
#endif /* PORT_DEV_ERROR_DETECT */

/*
 *Design:MCAL-14034,MCAL-13977,MCAL-13986,MCAL-13995
 */

FUNC(void, PORT_CODE) Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    const Port_PinConfigType *pinConfig;
    Port_PinModeType          curMode = PORT_PIN_MODE_INVALID;
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    boolean validConfig = FALSE;
    uint8   errId;
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if module has been initialzied. */
    if ((boolean)FALSE == Port_InitDone)
    {
        /* Report error to an Errorhook function. */
        Port_ReportDetError(PORT_SID_SET_PIN_DIR, PORT_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        pinConfig = Port_MapPinIdToPinConfig(Pin, Port_DrvObj.PinConfig_pt, Port_DrvObj.NumberOfPortPins);
        if (pinConfig != NULL)
        {
            curMode = Port_GetCurrentPinMode(pinConfig);
        }
        else
        {
            curMode = PORT_PIN_MODE_INVALID;
        }
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        errId       = 0U;
        validConfig = Port_ValidateSetPinDirection(pinConfig, curMode, &errId);
        if (validConfig == (boolean)FALSE)
        {
            Port_ReportDetError(PORT_SID_SET_PIN_DIR, errId);
        }
        else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
        {
            SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0();
            Port_ConfigPadAndDioPin(pinConfig, curMode, Direction);
            SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0();
        }
    }
    return;
}
#endif /* #if (STD_ON == PORT_SET_PIN_DIRECTION_API) */

/*
 *Design:MCAL-14041,MCAL-14025,MCAL-14026, MCAL-14017
 */

#if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API)
FUNC(void, PORT_CODE) Port_RefreshPortDirection(void)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if module has been initialized. */
    if ((boolean)FALSE == Port_InitDone)
    {
        /* Report error to an Errorhook function. */
        Port_ReportDetError(PORT_SID_REFRESH_PORT_DIR, PORT_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        Port_RefreshPortDirection_Internal();
    }
}
#endif /*(STD_ON == PORT_REFRESH_PORT_DIRECTION_API)*/

#if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API)
static void Port_RefreshDioPinDirection(const Port_PinConfigType *pinConfig)
{
    uint32 gpioPortAddr;

    gpioPortAddr = Port_GetGPIOPortAddr(pinConfig->Port_PinDioRegId);
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (PORT_DIO_INVALID_BASE_ADDR == gpioPortAddr)
    {
        Port_ReportDetError((uint8)PORT_SID_REFRESH_PORT_DIR, (uint8)PORT_E_INVALID_GPIO_PORT_ADDRESS);
    }
    else
#endif /*(STD_ON == PORT_DEV_ERROR_DETECT)*/
    {
        Port_HWConfigDioPinDirection(gpioPortAddr, pinConfig);
    }
}

static void Port_RefreshPortDirection_Internal(void)
{
    uint16                    idx = 0U;
    const Port_PinConfigType *pinConfig;
    Port_PinModeType          curMode = PORT_PIN_MODE_INVALID;

    for (idx = 0U; idx < Port_DrvObj.NumberOfPortPins; idx++)
    {
        /* Set all registers to configured values */
        pinConfig = &Port_DrvObj.PinConfig_pt[idx];
        /* If direction is not changeable,pin direction must be refreshed*/
        if (pinConfig->Port_DirectionChangeable == (boolean)FALSE)
        {
            curMode = Port_GetCurrentPinMode(pinConfig);
            if ((curMode != PORT_PIN_MODE_INVALID) && (Port_IsDioMode(curMode) == (boolean)TRUE))
            {
                Port_RefreshDioPinDirection(pinConfig);
            }
            Port_ConfigurePad(pinConfig, curMode);
        }
    }
}
#endif

#if (STD_ON == PORT_SET_PIN_MODE_API)
#if (STD_ON == PORT_DEV_ERROR_DETECT)
static boolean Port_ValidateSetPinMode(Port_PinModeType Mode, const Port_PinConfigType *pinConfig, uint8 *errorIdPtr)
{
    boolean retVal = (boolean)FALSE;
    uint32  idx    = 0U;

    if (pinConfig->Port_PinModeChangeable == (boolean)TRUE)
    {
        for (idx = 0U; (idx < pinConfig->Port_NumPortModes) && (idx < (uint32)PORT_MAX_MUXMODE); idx++)
        {
            if (pinConfig->Port_PinMode[idx].mode == Mode)
            {
                retVal = (boolean)TRUE;
                break;
            }
        }
        retVal = Port_ValidateSetPinMode_internal(pinConfig, Mode, errorIdPtr, idx);
    }
    else
    {
        retVal      = (boolean)FALSE;
        *errorIdPtr = PORT_E_MODE_UNCHANGEABLE;
    }
    return (retVal);
}
#endif /*PORT_DEV_ERROR_DETECT */

#if (STD_ON == PORT_DEV_ERROR_DETECT)
static boolean Port_ValidateSetPinMode_internal(const Port_PinConfigType *pinConfig, Port_PinModeType Mode,
                                                uint8 *errorIdPtr, uint32 idx)
{
    uint32  dioRegId = 0u;
    boolean retVal;

    retVal = (boolean)TRUE;

    if (idx > ((pinConfig->Port_NumPortModes) - 1U))
    {
        retVal      = (boolean)FALSE;
        *errorIdPtr = PORT_E_PARAM_INVALID_MODE;
    }
    else
    {
        if (Port_IsDioMode(Mode) == (boolean)TRUE)
        {
            dioRegId = Port_GetDioRegId(Mode);
            if ((pinConfig->Port_PinDioRegId != PORT_DIO_INVALID_CH_ID) && (dioRegId == pinConfig->Port_PinDioRegId))
            {
                retVal = (boolean)TRUE;
            }
            else
            {
                retVal      = (boolean)FALSE;
                *errorIdPtr = PORT_E_PARAM_INVALID_MODE;
            }
        }
    }
    return (retVal);
}
#endif /*PORT_DEV_ERROR_DETECT */

/*
 *Design:MCAL-14004,MCAL-14023,MCAL-14003,MCAL-13991
 */

FUNC(void, PORT_CODE) Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    const Port_PinConfigType *pinConfig;
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    boolean validConfig = (boolean)FALSE;
    uint8   errId;
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Check if module has been initialzied. */
    if ((boolean)FALSE == Port_InitDone)
    {
        /* Report error to an Errorhook function. */
        Port_ReportDetError(PORT_SID_SET_PIN_MODE, PORT_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        pinConfig = Port_MapPinIdToPinConfig(Pin, Port_DrvObj.PinConfig_pt, Port_DrvObj.NumberOfPortPins);
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        errId = (uint8)0U;
        if (pinConfig == NULL_PTR)
        {
            Port_ReportDetError(PORT_SID_SET_PIN_MODE, PORT_E_PARAM_PIN);
        }
        else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
        {
#if (STD_ON == PORT_DEV_ERROR_DETECT)
            validConfig = Port_ValidateSetPinMode(Mode, pinConfig, &errId);
            if (((boolean)FALSE) == validConfig)
            {
                Port_ReportDetError(PORT_SID_SET_PIN_MODE, errId);
            }
            else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
            {
                SchM_Enter_Port_PORT_EXCLUSIVE_AREA_0();
                Port_SetPinConfigPadAndDioPin(pinConfig, Mode);
                SchM_Exit_Port_PORT_EXCLUSIVE_AREA_0();
            }
        }
    }
}
#endif /*(STD_ON == PORT_SET_PIN_MODE_API)*/

/*
 *Design: MCAL-13967,MCAL-14038
 */

#if (STD_ON == PORT_VERSION_INFO_API)
FUNC(void, PORT_CODE)
Port_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versioninfo)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /*  Check parameter for NULL_PTR.  */
    if (NULL_PTR == versioninfo)
    {
        Port_ReportDetError(PORT_SID_GET_VERSION_INFO, PORT_E_PARAM_POINTER);
    }
    else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        /* Fill the version info */
        versioninfo->vendorID         = PORT_VENDOR_ID;
        versioninfo->moduleID         = PORT_MODULE_ID;
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
    return;
}
#endif /*(STD_ON == PORT_VERSION_INFO_API)*/

/*
 *   \brief Function to program all the pad. Get called at boot-up time
 *
 *
 *   \param[in]   pad_array - List of pad to be configured at boot time
 *
 *   \return              none
 *
 */
static void Port_InitPadList(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padList, uint16 elements)
{
    uint16 idx = 0U;

    for (idx = 0U; idx < elements; ++idx)
    {
        Port_ConfigurePad(&padList[idx], padList[idx].Port_PinInitialMode);
    }
}
#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))

static const Port_PinConfigType *Port_MapPinIdToPinConfig(Port_PinType PinId, const Port_PinConfigType modeCfg[],
                                                          uint16 numPins)
{
    uint16                    idx    = 0U;
    const Port_PinConfigType *pinCfg = (Port_PinConfigType *)NULL_PTR;

    for (idx = 0U; idx < numPins; idx++)
    {
        if (modeCfg[idx].Port_PinId == PinId)
        {
            pinCfg = &modeCfg[idx];
            break;
        }
    }

    if (idx == numPins)
    {
        pinCfg = (const Port_PinConfigType *)NULL;
    }
    return pinCfg;
}
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))   */

#if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API))
static Port_PinModeType Port_GetCurrentPinMode(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padCfg)
{
    uint32           idx     = 0U;
    Port_PinModeType pinMode = PORT_PIN_MODE_INVALID;

    uint32 muxmode_val = Port_ReadMuxMode(padCfg->Port_RegOffsetAddr);

    for (idx = 0U; (idx < padCfg->Port_NumPortModes) && (idx < (uint32)PORT_MAX_MUXMODE); idx++)
    {
        if (padCfg->Port_PinMode[idx].muxmode == muxmode_val)
        {
            pinMode = padCfg->Port_PinMode[idx].mode;
            break;
        }
    }
    if (idx == padCfg->Port_NumPortModes)
    {
        pinMode = PORT_PIN_MODE_INVALID;
    }
    return pinMode;
}

#endif /* #if ((STD_ON == PORT_SET_PIN_DIRECTION_API) || (STD_ON == \
          PORT_REFRESH_PORT_DIRECTION_API)) */

/*
 *Design: MCAL-22271
 */
/**
 *   \brief API used only for UT.Not to be used by application
 */
FUNC(void, PORT_CODE) Port_DeInit(void)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    /* Reset Init Done flag */
    Port_InitDone = (boolean)FALSE;
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
}

#if (STD_ON == PORT_DEV_ERROR_DETECT)
void Port_ReportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(PORT_MODULE_ID, 0, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */

/*
 *Design: MCAL-22272, MCAL-22698
 */
#if (STD_ON == PORT_ENABLE_INTR_API)
/*
 * \brief Enable Interrupt Functionality
 *
 * Pin --> GPIO Pin Number
 *
 */
void Port_PinEnableIntrNotification(Port_PinType Pin)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (Port_InitDone == TRUE)
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        Port_EnableIntr(Pin);
    }
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    else
    {
        /*Report error if port initialization not done */
        Port_ReportDetError(PORT_SID_ENABLE_INTR, PORT_E_UNINIT);
    }
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
}
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

/*
 *Design: MCAL-22273, MCAL-22699
 */
#if (STD_ON == PORT_ENABLE_INTR_API)
/*
 * \brief Disable Interrupt Functionality
 *
 * Pin --> GPIO Pin Number
 *
 */
void Port_PinDisableIntrNotification(Port_PinType Pin)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (Port_InitDone == TRUE)
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        Port_DisableIntr(Pin);
    }

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    else
    {
        /*Report error if port initialization not done */
        Port_ReportDetError(PORT_SID_DISABLE_INTR, PORT_E_UNINIT);
    }
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
}
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

/*
 *Design: MCAL-22274, MCAL-22700
 */
#if (STD_ON == PORT_GET_INTR_ST_API)
/*
 * \brief Read bank Interrupt Status Register
 *
 * Input : bankIdx --> GPIO bank Number
 *
 * Return value : uint32 --> INTSTAT Register Value
 *
 */
uint32 Port_GetInterruptStatus(Port_PinType bankIdx)
{
    uint32 regValue = 0U;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (Port_InitDone == TRUE)
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        regValue = Port_GetStatus(bankIdx);
    }
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    else
    {
        /*Report error if port initialization not done */
        Port_ReportDetError(PORT_SID_GET_INTR_ST, PORT_E_UNINIT);
    }
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */

    return regValue;
}
#endif /* #if (STD_ON == PORT_GET_INTR_ST_API) */

/*
 *Design: MCAL-22275, MCAL-22701
 */
#if (STD_ON == PORT_CLR_INTR_ST_API)
/*
 * \brief Clear bank Interrupt Status Register
 *
 * Input : bankIdx --> GPIO bank Number
 *         maskValue --> bit mask value
 *
 */
void Port_ClearInterruptStatus(Port_PinType bankIdx, uint32 maskValue)
{
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (Port_InitDone == TRUE)
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        Port_ClearStatus(bankIdx, maskValue);
    }
#if (STD_ON == PORT_DEV_ERROR_DETECT)
    else
    {
        /*Report error if port initialization not done */
        Port_ReportDetError(PORT_SID_CLR_INTR_ST, PORT_E_UNINIT);
    }
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
}
#endif /* #if (STD_ON == PORT_CLR_INTR_ST_API) */

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"
