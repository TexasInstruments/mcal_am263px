/*********************************************************************************************************************
 *  COPYRIGHT
 *  ------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright 2022 Texas Instruments Inc.  All rights reserved.
 *
 *  \endverbatim
 *  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *  File:       Lin.c
 *  Project:    AM263x MCAL
 *  Module:     Lin Driver
 *  Generator:  None
 *
 *  Description:  This file contains interface for Lin Drv functions
 *
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "EcuM_Cbk.h"
#include "Lin.h"
#include "SchM_Lin.h"

#if (STD_ON == LIN_DEV_ERROR_DETECT)
#include "Det.h"
#endif

/*********************************************************************************************************************
 * Other Header Files
 *********************************************************************************************************************/
#include "Lin_Priv.h"

/*********************************************************************************************************************
 * Version Check (if required)
 *********************************************************************************************************************/
/*
 * AUTOSAR version information check has to match definition in header file
 */
#if ((LIN_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (LIN_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (LIN_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "LIN: AUTOSAR Version Numbers of LIN are different"
#endif

/*
 * Vendor specific version information is BCD coded
 */
#if ((LIN_SW_MAJOR_VERSION != (10U)) || (LIN_SW_MINOR_VERSION != (1U)))
#error "Version numbers of Lin.c and Lin.h are inconsistent!"
#endif

#if ((LIN_CFG_MAJOR_VERSION != (10U)) || (LIN_CFG_MINOR_VERSION != (1U)))
#error "Version numbers of Lin.c and Lin_Cfg.h are inconsistent!"
#endif

/* Common Design ID's */
/*
 * Design: MCAL-15875, MCAL-15873, MCAL-15889
 */
/*********************************************************************************************************************
 * Local Preprocessor #define Constants
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Preprocessor #define Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Type Declarations
 *********************************************************************************************************************/
typedef enum Lin_ModuleStateTag
{
    LIN_UNINIT,
    LIN_INIT
} Lin_ModuleStateType;

/*********************************************************************************************************************
 * Exported Object Definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Internal Function Declarations
 *********************************************************************************************************************/
static FUNC(Std_ReturnType, LIN_CODE) Lin_CheckWakeupInternal(uint8 Channel);
static FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupProcess(uint8 Channel);
static FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupInternalProcess(uint8 Channel);
static FUNC(void, LIN_CODE) Lin_InitInternal(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) Lin_ConfigPtr);
static FUNC(Std_ReturnType, LIN_CODE)
    Lin_SendFrameDetCheck(uint8 Channel, P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) PduInfoPtr);
static FUNC(Lin_StatusType, LIN_CODE)
    Lin_GetStatusInternal(uint8   Channel, P2VAR(uint8 *, AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr,
                          uint32 *lin_cnt_base_addr);

#if (STD_ON == LIN_REGISTER_READBACK_API)
static FUNC(Std_ReturnType, LIN_CODE)
    Lin_RegReadback_Deterror(uint8 Channel, P2VAR(Lin_RegisterReadbackType, AUTOMATIC, LIN_APPL_DATA) RegRbPtr);
#endif
/*********************************************************************************************************************
 * Local Object Definitions
 *********************************************************************************************************************/
#define LIN_START_SEC_VAR_INIT_UNSPECIFIED
#include "Lin_MemMap.h"
/*
 * Global Init Done flag
 */
static Lin_ModuleStateType   Lin_Module_State = LIN_UNINIT;
static const Lin_ConfigType *Lin_Config_Ptr   = (Lin_ConfigType *)NULL_PTR;
#define LIN_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Lin_MemMap.h"

#define LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Lin_MemMap.h"
static Lin_ChannelStatusType Lin_Channel_Status[LIN_MAX_CHANNEL];
#define LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Lin_MemMap.h"

/*********************************************************************************************************************
 *  Local Function Prototypes
 *********************************************************************************************************************/
#define LIN_START_SEC_CODE
#include "Lin_MemMap.h"

/*********************************************************************************************************************
 *  Local Inline Function Definitions and Function-Like Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  External Functions Definition
 *********************************************************************************************************************/

#if (STD_ON == LIN_GET_VERSION_INFO_API)
/*
 * Design: MCAL-15810, MCAL-15878, MCAL-15819, MCAL-15808, MCAL-15809
 */
FUNC(void, LIN_CODE)
Lin_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (STD_ON == LIN_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GET_VERSION_INFO, LIN_E_PARAM_POINTER);
    }
    else
#endif
    {
        versioninfo->vendorID         = (LIN_VENDOR_ID);
        versioninfo->moduleID         = (LIN_MODULE_ID);
        versioninfo->sw_major_version = (uint8)(LIN_SW_MAJOR_VERSION);
        versioninfo->sw_minor_version = (uint8)(LIN_SW_MINOR_VERSION);
        versioninfo->sw_patch_version = (uint8)(LIN_SW_PATCH_VERSION);
    }
}
#endif

/*
 * Design: MCAL-15819, MCAL-15815, MCAL-15821, MCAL-15820, MCAL-15814, MCAL-15813, MCAL-15818,
 * MCAL-15817
 */
FUNC(void, LIN_CODE)
Lin_Init(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) Config)
{
#if (STD_ON == LIN_PRE_COMPILE_VARIANT)
    Lin_Config_Ptr = &LIN_INIT_CONFIG_PC;
#endif /* (STD_ON == LIN_PRE_COMPILE_VARIANT) */

#if (STD_ON == LIN_POST_BUILD_VARIANT)
    Lin_Config_Ptr = Config;
#endif /* (STD_ON == LIN_POST_BUILD_VARIANT) */

#if (STD_ON == LIN_DEV_ERROR_DETECT)
#if (STD_ON == LIN_PRE_COMPILE_VARIANT)
    if (NULL_PTR != Config)
#elif (STD_ON == LIN_POST_BUILD_VARIANT)
    if (NULL_PTR == Config)
#endif
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_INIT, LIN_E_PARAM_POINTER);
    }
    else if (LIN_UNINIT != Lin_Module_State)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_INIT, LIN_E_STATE_TRANSITION);
    }
    else
#endif
    {
        Lin_InitInternal(Lin_Config_Ptr);
    }
}

static FUNC(void, LIN_CODE) Lin_InitInternal(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) Lin_ConfigPtr)
{
    uint8 channel_idx = (uint8)0;
    for (channel_idx = 0; channel_idx < LIN_MAX_CHANNEL; channel_idx++)
    {
        /* Init individual controller */
        Lin_HwUnitConfig(&Lin_ConfigPtr->linChannelCfg[channel_idx]);

        /* Pass pointer of Driver Configuration to be used for ISR processing*/
        Lin_SetDriverCfgPtr(Lin_ConfigPtr);

        Lin_Channel_Status[channel_idx].linChannelNetworkStatus = LIN_CHANNEL_SLEEP;
        Lin_EnterLowPowerMode(Lin_ConfigPtr->linChannelCfg[channel_idx].linControllerConfig.CntrAddr, TRUE);

        if (TRUE == Lin_ConfigPtr->linChannelCfg[channel_idx].linChannelWakeupSupport)
        {
            Lin_EnableWakeupDetection(&Lin_ConfigPtr->linChannelCfg[channel_idx], TRUE);
        }
        else
        {
            Lin_EnableWakeupDetection(&Lin_ConfigPtr->linChannelCfg[channel_idx], FALSE);
        }

        Lin_Channel_Status[channel_idx].linChannelActivityStatus = LIN_CHANNEL_IDLE;
    }

    /*
     * Set Init Done flag
     */
    Lin_Module_State = LIN_INIT;
}

/*
 * Design: MCAL-15825, MCAL-15826, MCAL-15824, MCAL-15823
 */
FUNC(Std_ReturnType, LIN_CODE)
Lin_CheckWakeup(uint8 Channel)
{
    Std_ReturnType return_value = E_NOT_OK;

#if (STD_ON == LIN_DEV_ERROR_DETECT)
    if (LIN_INIT != Lin_Module_State)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_CHECK_WAKEUP, LIN_E_UNINIT);
    }
    else if (LIN_MAX_CHANNEL <= Channel)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_CHECK_WAKEUP, LIN_E_INVALID_CHANNEL);
    }
    else
#endif
    {
        return_value = Lin_CheckWakeupInternal(Channel);
    }

    return return_value;
}

static FUNC(Std_ReturnType, LIN_CODE) Lin_CheckWakeupInternal(uint8 Channel)
{
    Std_ReturnType return_value = E_NOT_OK;
    if ((uint8)LIN_CHANNEL_SLEEP == (uint8)Lin_Channel_Status[Channel].linChannelNetworkStatus)
    {
        if (TRUE == Lin_CheckWakeupStatus(Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr))
        {
            /* Wakeup event sent to ECU Manager */
            EcuM_SetWakeupEvent(Lin_Config_Ptr->linChannelCfg[Channel].linWakeupSource);
        }
        else
        {
            /* Do Nothing */
        }
        return_value = E_OK;
    }
    return return_value;
}

/*
 * Design: MCAL-15831, MCAL-15830, MCAL-15836, MCAL-15835, MCAL-15834, MCAL-15833, MCAL-15829,
 * MCAL-15828, MCAL-15827, MCAL-15832
 */
FUNC(Std_ReturnType, LIN_CODE)
Lin_SendFrame(uint8 Channel, P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) PduInfoPtr)
{
    Std_ReturnType return_value = E_NOT_OK;
    return_value                = Lin_SendFrameDetCheck(Channel, PduInfoPtr);
    if (((Std_ReturnType)E_OK) == return_value)
    {
        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0();

        return_value = Lin_SendData(&Lin_Config_Ptr->linChannelCfg[Channel],
                                    &Lin_Channel_Status[Channel].linChannelActivityStatus, PduInfoPtr);

        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0();
    }
    return (return_value);
}

static FUNC(Std_ReturnType, LIN_CODE)
    Lin_SendFrameDetCheck(uint8 Channel, P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) PduInfoPtr)
{
    Std_ReturnType return_value = E_OK;
    if (LIN_INIT != Lin_Module_State)
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SEND_FRAME, LIN_E_UNINIT);
        return_value = E_NOT_OK;
#endif
    }
    if ((LIN_MAX_CHANNEL <= Channel) && (return_value == E_OK))
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SEND_FRAME, LIN_E_INVALID_CHANNEL);
        return_value = E_NOT_OK;
#endif
    }
    if ((NULL_PTR == PduInfoPtr) && (return_value == E_OK))
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SEND_FRAME, LIN_E_PARAM_POINTER);
        return_value = E_NOT_OK;
#endif
    }
    if ((LIN_CHANNEL_OPERATIONAL != Lin_Channel_Status[Channel].linChannelNetworkStatus) && (return_value == E_OK))
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_SEND_FRAME, LIN_E_STATE_TRANSITION);
        return_value = E_NOT_OK;
#endif
    }
    return return_value;
}

/*
 * Design: MCAL-15844, MCAL-15841, MCAL-15840, MCAL-15837, MCAL-15842, MCAL-15843, MCAL-15845,
 * MCAL-15839, MCAL-15838, MCAL-15944, MCAL-15945, MCAL-15846, MCAL-15847
 */
FUNC(Std_ReturnType, LIN_CODE)
Lin_GoToSleep(uint8 Channel)
{
    Std_ReturnType return_value = E_NOT_OK;

    if (LIN_INIT != Lin_Module_State)
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GOTO_SLEEP, LIN_E_UNINIT);
#endif
    }
    else if (LIN_MAX_CHANNEL <= Channel)
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GOTO_SLEEP, LIN_E_INVALID_CHANNEL);
#endif
    }
    else
    {
        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0();

        Lin_Channel_Status[Channel].linChannelNetworkStatus = LIN_CHANNEL_SLEEP_PENDING;

        if (TRUE == Lin_Config_Ptr->linChannelCfg[Channel].linChannelWakeupSupport)
        {
            Lin_EnableWakeupDetection(&Lin_Config_Ptr->linChannelCfg[Channel], TRUE);
        }
        else
        {
            Lin_EnableWakeupDetection(&Lin_Config_Ptr->linChannelCfg[Channel], FALSE);
        }

        /* TODO: Send goto-sleep command on bus? */
        Lin_EnterLowPowerMode(Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr, TRUE);
        Lin_AbortTransmission(Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr);

        return_value = E_OK;

        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0();
    }

    return return_value;
}

/*
 * Design: MCAL-15850, MCAL-15851, MCAL-15849, MCAL-15848, MCAL-15846, MCAL-15847
 */
FUNC(Std_ReturnType, LIN_CODE)
Lin_GoToSleepInternal(uint8 Channel)
{
    Std_ReturnType return_value = E_NOT_OK;

    if (LIN_INIT != Lin_Module_State)
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GOTO_SLEEP_INTERNAL, LIN_E_UNINIT);
#endif
    }
    else if (LIN_MAX_CHANNEL <= Channel)
    {
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GOTO_SLEEP_INTERNAL, LIN_E_INVALID_CHANNEL);
#endif
    }
    else
    {
        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0();

        Lin_Channel_Status[Channel].linChannelNetworkStatus = LIN_CHANNEL_SLEEP;

        if (TRUE == Lin_Config_Ptr->linChannelCfg[Channel].linChannelWakeupSupport)
        {
            Lin_EnableWakeupDetection(&Lin_Config_Ptr->linChannelCfg[Channel], TRUE);
        }
        else
        {
            Lin_EnableWakeupDetection(&Lin_Config_Ptr->linChannelCfg[Channel], FALSE);
        }

        Lin_EnterLowPowerMode(Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr, TRUE);

        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0();

        return_value = E_OK;
    }

    return return_value;
}

/*
 * Design: MCAL-15852, MCAL-15855, MCAL-15854, MCAL-15853
 */
FUNC(Std_ReturnType, LIN_CODE)
Lin_Wakeup(uint8 Channel)
{
    Std_ReturnType return_value = E_NOT_OK;

#if (STD_ON == LIN_DEV_ERROR_DETECT)
    if (LIN_INIT != Lin_Module_State)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUP, LIN_E_UNINIT);
    }
    else if (LIN_MAX_CHANNEL <= Channel)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUP, LIN_E_INVALID_CHANNEL);
    }
    else if (LIN_CHANNEL_SLEEP != Lin_Channel_Status[Channel].linChannelNetworkStatus)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUP, LIN_E_STATE_TRANSITION);
    }
    else
#endif
    {
        return_value = Lin_WakeupProcess(Channel);
    }

    return return_value;
}

static FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupProcess(uint8 Channel)
{
    Std_ReturnType ret_value = E_NOT_OK;
    if ((uint8)LIN_CHANNEL_SLEEP == (uint8)Lin_Channel_Status[Channel].linChannelNetworkStatus)
    {
        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0();

        Lin_SendWakeupSignal(Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr);
        Lin_EnterLowPowerMode(Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr, FALSE);
        Lin_Channel_Status[Channel].linChannelNetworkStatus = LIN_CHANNEL_OPERATIONAL;

        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0();

        ret_value = E_OK;
    }
    else
    {
        /* Do Nothing */
    }
    return (ret_value);
}

/*
 * Design: MCAL-15858, MCAL-15859, MCAL-15860, MCAL-15857, MCAL-15856
 */
FUNC(Std_ReturnType, LIN_CODE)
Lin_WakeupInternal(uint8 Channel)
{
    Std_ReturnType return_value = E_NOT_OK;

#if (STD_ON == LIN_DEV_ERROR_DETECT)
    if (LIN_INIT != Lin_Module_State)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUP_INTERNAL, LIN_E_UNINIT);
    }
    else if (LIN_MAX_CHANNEL <= Channel)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUP_INTERNAL, LIN_E_INVALID_CHANNEL);
    }
    else if (LIN_CHANNEL_SLEEP != Lin_Channel_Status[Channel].linChannelNetworkStatus)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_WAKEUP_INTERNAL, LIN_E_STATE_TRANSITION);
    }
    else
#endif
    {
        return_value = Lin_WakeupInternalProcess(Channel);
    }

    return return_value;
}

static FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupInternalProcess(uint8 Channel)
{
    Std_ReturnType ret_value = E_NOT_OK;
    if ((uint8)LIN_CHANNEL_SLEEP == (uint8)Lin_Channel_Status[Channel].linChannelNetworkStatus)
    {
        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0();

        Lin_EnterLowPowerMode(Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr, FALSE);
        Lin_Channel_Status[Channel].linChannelNetworkStatus = LIN_CHANNEL_OPERATIONAL;

        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0();

        ret_value = E_OK;
    }
    else
    {
        /* Do Nothing */
    }
    return (ret_value);
}

/*
 * Design: MCAL-15868, MCAL-15863, MCAL-15864, MCAL-15862, MCAL-15867, MCAL-15866, MCAL-15865,
 * MCAL-15861
 */
FUNC(Lin_StatusType, LIN_CODE)
Lin_GetStatus(uint8 Channel, P2VAR(uint8 *, AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr)
{
    uint32         condition_check    = 0U;
    uint32         channelstate_check = 0U;
    Lin_StatusType return_value       = LIN_NOT_OK;
    uint32         lin_cnt_base_addr  = (uint32)0;

    if (LIN_INIT != Lin_Module_State)
    {
        condition_check = 1U;
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GET_STATUS, LIN_E_UNINIT);
#endif
    }
    if ((LIN_MAX_CHANNEL <= Channel) && (condition_check == 0U))
    {
        condition_check = 1U;
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GET_STATUS, LIN_E_INVALID_CHANNEL);
#endif
    }
    if ((NULL_PTR == Lin_SduPtr) && (condition_check == 0U))
    {
        condition_check = 1U;
#if (STD_ON == LIN_DEV_ERROR_DETECT)
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_GET_STATUS, LIN_E_PARAM_POINTER);
#endif
    }
    if (condition_check == 0U)
    {
        condition_check   = 1U;
        lin_cnt_base_addr = Lin_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr;

        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_0();

        if (LIN_CHANNEL_OPERATIONAL == Lin_Channel_Status[Channel].linChannelNetworkStatus)
        {
            channelstate_check = 1U;
            return_value       = Lin_GetStatusInternal(Channel, Lin_SduPtr, &lin_cnt_base_addr);
        }
        if ((LIN_CHANNEL_SLEEP == Lin_Channel_Status[Channel].linChannelNetworkStatus) && (channelstate_check == 0U))
        {
            channelstate_check = 1U;
            return_value       = LIN_CH_SLEEP;
        }
        if ((LIN_CHANNEL_SLEEP_PENDING == Lin_Channel_Status[Channel].linChannelNetworkStatus) &&
            (channelstate_check == 0U))
        {
            channelstate_check                                  = 1U;
            Lin_Channel_Status[Channel].linChannelNetworkStatus = LIN_CHANNEL_SLEEP;
            return_value                                        = LIN_CH_SLEEP;
        }
        else
        {
            /* Do Nothing */
        }
        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_0();
    }
    return return_value;
}

static FUNC(Lin_StatusType, LIN_CODE)
    Lin_GetStatusInternal(uint8 Channel, P2VAR(uint8 *, AUTOMATIC, LIN_APPL_DATA) Lin_SduPtr, uint32 *lin_cnt_base_addr)
{
    Lin_StatusType return_value = LIN_NOT_OK;
    switch (Lin_Channel_Status[Channel].linChannelActivityStatus)
    {
        case LIN_CHANNEL_IDLE:
            return_value = LIN_OPERATIONAL;
            break;

        case LIN_CHANNEL_TX_STARTED:

            return_value = Lin_FetchTxStatus(*lin_cnt_base_addr);

            if (LIN_TX_OK == return_value)
            {
                Lin_Channel_Status[Channel].linChannelActivityStatus = LIN_CHANNEL_IDLE;
            }
            else if ((LIN_TX_HEADER_ERROR == return_value) || (LIN_TX_ERROR == return_value))
            {
                Lin_Channel_Status[Channel].linChannelActivityStatus = LIN_CHANNEL_IDLE;
            }
            else
            {
                /* Do Nothing */
            }
            break;

        case LIN_CHANNEL_RX_STARTED:

            return_value = Lin_FetchRxStatus(*lin_cnt_base_addr);

            if (LIN_RX_OK == return_value)
            {
                Lin_GetData(Channel, *lin_cnt_base_addr, Lin_SduPtr);
                Lin_Channel_Status[Channel].linChannelActivityStatus = LIN_CHANNEL_IDLE;
            }
            else if ((LIN_RX_NO_RESPONSE == return_value) || (LIN_RX_ERROR == return_value))
            {
                Lin_Channel_Status[Channel].linChannelActivityStatus = LIN_CHANNEL_IDLE;
            }
            else
            {
                /* Do Nothing */
            }

            break;

        default:
            /* Do Nothing */
            break;
    }
    return return_value;
}

/**
 *\brief   This function is used to readback some critical LIN registers
 *
 */
/*
 * Design: MCAL-23320, MCAL-23322
 */
#if (STD_ON == LIN_REGISTER_READBACK_API)
FUNC(Std_ReturnType, LIN_CODE)
Lin_RegisterReadback(uint8 Channel, P2VAR(Lin_RegisterReadbackType, AUTOMATIC, LIN_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == LIN_DEV_ERROR_DETECT)
    retVal = Lin_RegReadback_Deterror(Channel, RegRbPtr);
#endif

    /* Check if return value is correct. */
    if (retVal == E_OK)
    {
        /* Readback the register. */
        Lin_HwRegisterReadback(Channel, RegRbPtr);
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    /* Return the Value. */
    return (retVal);
}

/*
 * Design: MCAL-23321
 */
#if (STD_ON == LIN_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, LIN_CODE)
    Lin_RegReadback_Deterror(uint8 Channel, P2VAR(Lin_RegisterReadbackType, AUTOMATIC, LIN_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == LIN_DEV_ERROR_DETECT)
    if (Channel >= LIN_MAX_CHANNEL)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_REGISTER_READBACK, LIN_E_INVALID_CHANNEL);
        retVal = E_NOT_OK;
    }
    if (LIN_INIT != Lin_Module_State)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_REGISTER_READBACK, LIN_E_UNINIT);
        retVal = E_NOT_OK;
    }
    if (NULL_PTR == RegRbPtr)
    {
        (void)Det_ReportError(LIN_MODULE_ID, LIN_INSTANCE_ID, LIN_SID_REGISTER_READBACK, LIN_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }
#endif /* #if (STD_ON == LIN_DEV_ERROR_DETECT) */

    return retVal;
}
#endif /*#if (STD_ON == LIN_DEV_ERROR_DETECT)*/
#endif /*#if (STD_ON == LIN_REGISTER_READBACK_API)*/

/*********************************************************************************************************************
 *  Local Functions Definition
 *********************************************************************************************************************/

#define LIN_STOP_SEC_CODE
#include "Lin_MemMap.h"

/*********************************************************************************************************************
 *  End of File: Lin.c
 *********************************************************************************************************************/
