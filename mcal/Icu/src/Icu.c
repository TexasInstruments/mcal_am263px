/*
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file      Icu.c
 *
 *  \brief    This file contains ICU MCAL driver
 *
 */

/* Common Design ID's */
/*
 *Design: MCAL-12507, MCAL-12066, MCAL-12508, MCAL-15696, MCAL-15698, MCAL-15699, MCAL-12073,
 *MCAL-12069, MCAL-12071, MCAL-12590, MCAL-12072, MCAL-12060, MCAL-12070, MCAL-12064, MCAL-12061,
 *MCAL-12068, MCAL-12055, MCAL-12587, MCAL-12056, MCAL-12058, MCAL-13873, MCAL-12074, MCAL-12054,
 *MCAL-12059, MCAL-12057,MCAL-12063,MCAL-12589, MCAL-12062, MCAL-12067, MCAL-12588
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include "SchM_Icu.h"
#include "EcuM_Cbk.h"
#include "Icu.h"
#if (STD_ON == ICU_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "Icu_Irq.h"
#include "Icu_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((ICU_AR_RELEASE_MAJOR_VERSION != (4U)) || (ICU_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (ICU_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Icu: AUTOSAR Version Numbers of Icu are different!!"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if ((ICU_SW_MAJOR_VERSION != (10U)) || (ICU_SW_MINOR_VERSION != (2U)) || (ICU_SW_PATCH_VERSION != (0U)))
#error "Icu: Software Version Numbers are inconsistent!!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkInitErrors(const Icu_ConfigType* IcuConfigPtr);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

static FUNC(void, ICU_CODE) Icu_CheckInit_Internal(uint32 chNum, const Icu_ConfigType* IcuConfigPtr);

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE)
    Icu_checkSetActivationConditionErrors(Icu_ChannelType Channel, Icu_ActivationType Activation);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkGetInputStateErrors(Icu_ChannelType Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE)
    Icu_checkStartTimestampErrors(Icu_ChannelType Channel, Icu_ValueType* BufferPtr, uint16 BufferSize);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkStopTimestampErrors(Icu_ChannelType Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkGetTimestampIndexErrors(Icu_ChannelType Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkStopSignalMeasurementErrors(Icu_ChannelType Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkGetTimeElapsedErrors(Icu_ChannelType Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE)
    Icu_checkGetDutyCycleValuesErrors(Icu_ChannelType Channel, Icu_DutyCycleType* DutyCycleValues);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define ICU_START_SEC_VAR_INIT_8
#include "Icu_MemMap.h"
/** \brief Icu driver init status */
volatile VAR(uint8, ICU_VAR_INIT) Icu_DrvStatus = ICU_STATUS_UNINIT;

#define ICU_STOP_SEC_VAR_INIT_8
#include "Icu_MemMap.h"

#define ICU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"
/** \brief ICU driver object. */
VAR(Icu_ChObjType, ICU_VAR_NO_INIT) Icu_ChObj[ICU_MAX_NUM_CHANNELS];
/* Icu_ChObj is not static storage class, as this requires to be accessed by
    debug interface provided.  */
#define ICU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ICU_START_SEC_CODE
#include "Icu_MemMap.h"

/*
 *Design:
 *MCAL-12077,MCAL-12078,MCAL-12079,MCAL-12080,MCAL-12081,MCAL-12082,MCAL-12083,MCAL-12084,MCAL-12085,MCAL-12086,MCAL-12087,MCAL-12088,MCAL-12089,MCAL-12090,MCAL-12091,MCAL-12092
 */
FUNC(void, ICU_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_PBCFG) ConfigPtr)
{
    uint32 chNum;
    uint32 maxCh;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
    const Icu_ConfigType* IcuConfigPtr    = ConfigPtr;
#if (STD_ON == ICU_PRE_COMPILE_VARIANT)
    IcuConfigPtr = &ICU_INIT_CONFIG_PC;
#endif

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkInitErrors(IcuConfigPtr);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        maxCh = (uint32)IcuConfigPtr->icuMaxChannel;

        for (chNum = 0U; chNum < maxCh; chNum++)
        {
#if (STD_ON == ICU_DEV_ERROR_DETECT)
            if (((&IcuConfigSet_PC)->chCfg[chNum].channelId) > (uint32)ICU_MAX_NUM_CHANNELS)
            {
                /*Invalid channel */
                (void)Icu_reportDetError(ICU_INIT_ID, ICU_E_PARAM_CHANNEL);
            }
            else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
            {
                Icu_CheckInit_Internal(chNum, IcuConfigPtr);
            }
        }

#if (STD_ON == ICU_DEV_ERROR_DETECT)
        Icu_DrvStatus = ICU_STATUS_INIT;
#endif
    }

    return;
}

/*
 *Design: MCAL-12093, MCAL-12094, MCAL-12132, MCAL-12133, MCAL-12134, MCAL-12135, MCAL-12136,
 *MCAL-12137, MCAL-12138, MCAL-12139
 */
#if (STD_ON == ICU_DE_INIT_API)
FUNC(void, ICU_CODE) Icu_DeInit(void)
{
    uint32 chIdx;
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_DEINIT_ID, ICU_E_UNINIT);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        Icu_DrvStatus = ICU_STATUS_UNINIT;

        for (chIdx = 0; chIdx < ICU_MAX_NUM_CHANNELS; chIdx++)
        {
            /*Check if any channel is running. If yes, cannot call Deinit*/
            if (FALSE == Icu_ChObj[chIdx].IsRunning)
            {
                /*Disable and Clear Interrupts*/
                ICU_ECAP_intrDisable(Icu_ChObj[chIdx].baseAddr, ECAP_INT_ALL);
                ICU_ECAP_intrStatusClear(Icu_ChObj[chIdx].baseAddr, ECAP_INT_ALL);

                /* Disable CAP1-CAP4 register loads */
                ICU_ECAP_captureLoadingDisable(Icu_ChObj[chIdx].baseAddr);

                Icu_ResetChObj(&Icu_ChObj[chIdx]);
            }
        }
    }
    return;
}
#endif /*ICU_DE_INIT_API*/

/*
 *Design: MCAL-12176, MCAL-12177, MCAL-12178, MCAL-12179
 */
FUNC(void, ICU_CODE) Icu_DisableNotification(Icu_ChannelType Channel)
{
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_DISABLENOTIFICATION_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_DISABLENOTIFICATION_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        Icu_ChObj[Channel].NotificationEnabled = FALSE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
        /* Disable the notification on the given channel */
    }
}

/*
 *Design: MCAL-12180, MCAL-12181, MCAL-12182, MCAL-12183
 */
FUNC(void, ICU_CODE) Icu_EnableNotification(Icu_ChannelType Channel)
{
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_ENABLENOTIFICATION_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_ENABLENOTIFICATION_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        Icu_ChObj[Channel].NotificationEnabled = TRUE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
        /* Enables the notification on the given channel */
    }
    return;
}
/*
 *Design: MCAL-12170, MCAL-12171, MCAL-12172, MCAL-12173, MCAL-12174, MCAL-12175
 */
FUNC(void, ICU_CODE)
Icu_SetActivationCondition(Icu_ChannelType Channel, Icu_ActivationType Activation)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkSetActivationConditionErrors(Channel, Activation);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        Icu_ChObj[Channel].activation_edge = Activation;

#if ((ICU_EDGE_DETECT_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON))
        Icu_ChObj[Channel].InputState = ICU_IDLE;
#endif
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }

    return;
}

#if (STD_ON == ICU_GET_INPUT_STATE_API)

/*
 *Design: MCAL-12184, MCAL-12185, MCAL-12186, MCAL-12187, MCAL-12188, MCAL-12189, MCAL-12190,
 *MCAL-12191, MCAL-12192, MCAL-12193, MCAL-12194, MCAL-12195
 */
FUNC(Icu_InputStateType, ICU_CODE) Icu_GetInputState(Icu_ChannelType Channel)
{
    Icu_InputStateType retState           = ICU_IDLE;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkGetInputStateErrors(Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        /* Return the current input status for the channel */
        Icu_InputStateType CurrentState = Icu_ChObj[Channel].InputState;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();

        if (CurrentState == ICU_ACTIVE)
        {
            Icu_ChObj[Channel].InputState = ICU_IDLE;
        }

        if (Icu_ChObj[Channel].chCfg.measurementMode == ICU_MODE_SIGNAL_MEASUREMENT)
        {
            /*Check if measurement is completed before returning ICU_ACTIVE*/
            if ((Icu_ChObj[Channel].IsRunning) != (uint32)0U)
            {
                Icu_ChObj[Channel].InputState = CurrentState;
                retState                      = ICU_IDLE;
            }
            else
            {
                retState = CurrentState;
            }
        }
        else
        {
            retState = CurrentState;
        }
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }

    return retState;
}
#endif /* ICU_GET_INPUT_STATE_API*/

/*
 *Design: MCAL-12256, MCAL-12257, MCAL-12258, MCAL-12259, MCAL-12260, MCAL-12261, MCAL-12262,
 *MCAL-12263
 */
#if (STD_ON == ICU_EDGE_DETECT_API)
FUNC(void, ICU_CODE) Icu_EnableEdgeDetection(Icu_ChannelType Channel)
{
    uint32 baseAddr;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_ENABLEEDGEDETECTION_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_ENABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT != Icu_ChObj[Channel].chCfg.measurementMode)
    {
        (void)Icu_reportDetError(ICU_ENABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        baseAddr = Icu_ChObj[Channel].baseAddr;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();

        Icu_ConfigEcap(baseAddr, Icu_ChObj[Channel].activation_edge, ICU_DELTA_MODE, TRUE,
                       Icu_ChObj[Channel].chCfg.intrcapSelect);
        Icu_ChObj[Channel].IsRunning = TRUE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }
}

/*
 *Design: MCAL-12264, MCAL-12265, MCAL-12266, MCAL-12267, MCAL-12268, MCAL-12269
 */
FUNC(void, ICU_CODE) Icu_DisableEdgeDetection(Icu_ChannelType Channel)
{
    uint32 baseAddr;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_DISABLEEDGEDETECTION_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_DISABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT != Icu_ChObj[Channel].chCfg.measurementMode)
    {
        (void)Icu_reportDetError(ICU_DISABLEEDGEDETECTION_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        baseAddr = Icu_ChObj[Channel].baseAddr;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        /*Disable Interrupts*/
        ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);

        /* Disable CAP1-CAP4 register loads */
        ICU_ECAP_captureLoadingDisable(baseAddr);
        Icu_ChObj[Channel].IsRunning = FALSE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }
}

#endif /*ICU_EDGE_DETECT_API*/

/*
 *Design: MCAL-12195, MCAL-12196, MCAL-12197, MCAL-12198, MCAL-12199, MCAL-12200, MCAL-12201,
 *MCAL-12202, MCAL-12203, MCAL-12204, MCAL-12205, MCAL-12206, MCAL-12207, MCAL-12208, MCAL-12209
 */
#if (STD_ON == ICU_TIMESTAMP_API)
FUNC(void, ICU_CODE)
Icu_StartTimestamp(Icu_ChannelType Channel, Icu_ValueType* BufferPtr, uint16 BufferSize, uint16 NotifyInterval)
{
    uint32 baseAddr;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkStartTimestampErrors(Channel, BufferPtr, BufferSize);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        baseAddr = Icu_ChObj[Channel].baseAddr;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();

        Icu_TimeStamp_Init(Channel, BufferPtr, BufferSize, NotifyInterval);

        Icu_ConfigEcap(baseAddr, Icu_ChObj[Channel].activation_edge, ICU_ABSOLUTE_MODE, TRUE,
                       Icu_ChObj[Channel].chCfg.intrcapSelect);

        Icu_ChObj[Channel].IsRunning = TRUE;
        Icu_ChObj[Channel].IsActive  = TRUE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }

    return;
}

/*
 *Design: MCAL-12223, MCAL-12224, MCAL-12225, MCAL-12226, MCAL-12227, MCAL-12228, MCAL-12229,
 *MCAL-12230
 */
FUNC(void, ICU_CODE) Icu_StopTimestamp(Icu_ChannelType Channel)
{
    uint32 baseAddr;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkStopTimestampErrors(Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        if ((FALSE == Icu_ChObj[Channel].IsActive) && (FALSE == Icu_ChObj[Channel].IsRunning))
        {
            (void)Icu_reportDetRuntimeError(ICU_STOPTIMESTAMP_ID, ICU_E_NOT_STARTED);
        }
        else
        {
            baseAddr = Icu_ChObj[Channel].baseAddr;
            SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();

            ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
            ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);

            /* Disable CAP1-CAP4 register loads */
            ICU_ECAP_captureLoadingDisable(baseAddr);

            Icu_TimeStamp_Clear(Channel);

            Icu_ChObj[Channel].IsRunning = FALSE;
            Icu_ChObj[Channel].IsActive  = FALSE;
            SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
        }
    }
    return;
}

/*
 *Design: MCAL-12231, MCAL-12232, MCAL-12233, MCAL-12234, MCAL-12235, MCAL-12236, MCAL-12237,
 *MCAL-12238, MCAL-12239
 */
FUNC(Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex(Icu_ChannelType Channel)
{
    Icu_IndexType index                   = 0;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkGetTimestampIndexErrors(Channel);
#endif
    if (((Std_ReturnType)E_OK) == retVal)
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        if ((Icu_ChObj[Channel].IsActive) != (uint32)0U)
        {
            index = Icu_ChObj[Channel].NextTimeStampIndex;
        }
        else
        {
            /*return 0*/
        }
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }

    return index;
}

#endif /* ICU_TIMESTAMP_API*/

#if (STD_ON == ICU_EDGE_COUNT_API)

/*
 *Design: MCAL-12240, MCAL-12241, MCAL-12242, MCAL-12243, MCAL-12244, MCAL-12245
 */
FUNC(void, ICU_CODE) Icu_ResetEdgeCount(Icu_ChannelType Channel)
{
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_RESETEDGECOUNT_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_RESETEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);
    }
    else if (ICU_MODE_EDGE_COUNTER != Icu_ChObj[Channel].chCfg.measurementMode)
    {
        (void)Icu_reportDetError(ICU_RESETEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        Icu_ChObj[Channel].EdgeCounter = 0;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }
}

/*
 *Design: MCAL-12248, MCAL-12249, MCAL-12250, MCAL-12251, MCAL-12252, MCAL-12253, MCAL-12254,
 *MCAL-12255
 */
FUNC(void, ICU_CODE) Icu_EnableEdgeCount(Icu_ChannelType Channel)
{
    uint32 baseAddr;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_ENABLEEDGECOUNT_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_ENABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);
    }
    else if (ICU_MODE_EDGE_COUNTER != Icu_ChObj[Channel].chCfg.measurementMode)
    {
        (void)Icu_reportDetError(ICU_ENABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        baseAddr = Icu_ChObj[Channel].baseAddr;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();

        Icu_ConfigEcap(baseAddr, Icu_ChObj[Channel].activation_edge, ICU_DELTA_MODE, TRUE,
                       Icu_ChObj[Channel].chCfg.intrcapSelect);

        Icu_ChObj[Channel].IsRunning = TRUE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }
}

/*
 *Design: MCAL-12270, MCAL-12271, MCAL-12272, MCAL-12273, MCAL-12274, MCAL-12275
 */
FUNC(void, ICU_CODE) Icu_DisableEdgeCount(Icu_ChannelType Channel)
{
    uint32 baseAddr;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_DISABLEEDGECOUNT_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_DISABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);
    }
    else if (ICU_MODE_EDGE_COUNTER != Icu_ChObj[Channel].chCfg.measurementMode)
    {
        (void)Icu_reportDetError(ICU_DISABLEEDGECOUNT_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        baseAddr = Icu_ChObj[Channel].baseAddr;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);

        /* Disable CAP1-CAP4 register loads */
        ICU_ECAP_captureLoadingDisable(baseAddr);

        Icu_ChObj[Channel].IsRunning = FALSE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }
}

/*
 *Design: MCAL-12276, MCAL-12277, MCAL-12278, MCAL-12279, MCAL-12280, MCAL-12281, MCAL-12282
 */
FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers(Icu_ChannelType Channel)
{
    Icu_EdgeNumberType edgecount = 0;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_GETEDGENUMBERS_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_GETEDGENUMBERS_ID, ICU_E_PARAM_CHANNEL);
    }
    else if (ICU_MODE_EDGE_COUNTER != Icu_ChObj[Channel].chCfg.measurementMode)
    {
        (void)Icu_reportDetError(ICU_GETEDGENUMBERS_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        edgecount = Icu_ChObj[Channel].EdgeCounter;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }

    return edgecount;
}

#endif /*ICU_EDGE_COUNT_API*/

/*
 *Design: MCAL-12283, MCAL-12284, MCAL-12285, MCAL-12286, MCAL-12287, MCAL-12288, MCAL-12289,
 *MCAL-12290
 */
#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
FUNC(void, ICU_CODE) Icu_StartSignalMeasurement(Icu_ChannelType Channel)
{
    uint32 baseAddr;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_STARTSIGNALMEASUREMENT_ID, ICU_E_UNINIT);
    }
    else if (ICU_MAX_NUM_CHANNELS <= Channel)
    {
        (void)Icu_reportDetError(ICU_STARTSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
    }
    else if (ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChObj[Channel].chCfg.measurementMode)
    {
        (void)Icu_reportDetError(ICU_STARTSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
    }
    else
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    {
        baseAddr = Icu_ChObj[Channel].baseAddr;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();

        Icu_ChObj[Channel].InputState = ICU_IDLE;

        Icu_SignalMeasurement_Init(Channel);

        Icu_ConfigEcap(baseAddr, ICU_BOTH_EDGES, ICU_DELTA_MODE, FALSE, Icu_ChObj[Channel].chCfg.intrcapSelect);

        Icu_ChObj[Channel].IsRunning = TRUE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }

    return;
}

/*
 *Design: MCAL-12291, MCAL-12292, MCAL-12293, MCAL-12294, MCAL-12295, MCAL-12296, MCAL-12297
 */
FUNC(void, ICU_CODE) Icu_StopSignalMeasurement(Icu_ChannelType Channel)
{
    uint32        baseAddr;
    Icu_ValueType highTime, lowTime, period;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkStopSignalMeasurementErrors(Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        baseAddr = Icu_ChObj[Channel].baseAddr;
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();

        ICU_ECAP_intrDisable(baseAddr, ECAP_INT_ALL);
        ICU_ECAP_intrStatusClear(baseAddr, ECAP_INT_ALL);

        /* Disable CAP1-CAP4 register loads */
        ICU_ECAP_captureLoadingDisable(baseAddr);

        Icu_ChObj[Channel].cap1 = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_1);
        Icu_ChObj[Channel].cap2 = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_2);
        Icu_ChObj[Channel].cap3 = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_3);
        Icu_ChObj[Channel].cap4 = ICU_ECAP_timeStampRead(baseAddr, ECAP_CAPTURE_EVENT_4);

        if ((Icu_ChObj[Channel].cap1 == 0U) || (Icu_ChObj[Channel].cap2 == 0U) || (Icu_ChObj[Channel].cap3 == 0U) ||
            (Icu_ChObj[Channel].cap4 == 0U))
        {
            Icu_ChObj[Channel].DutyAcquired   = FALSE;
            Icu_ChObj[Channel].PeriodAcquired = FALSE;
        }
        else
        {
            uint32 clkFreq_Mhz = Icu_ChObj[Channel].chCfg.instanceClkMHz;

            highTime = (Icu_ValueType)(Icu_ChObj[Channel].cap3 / clkFreq_Mhz);
            lowTime  = (Icu_ValueType)(Icu_ChObj[Channel].cap2 / clkFreq_Mhz);
            period   = highTime + lowTime;

            Icu_ChObj[Channel].HighTime             = highTime;
            Icu_ChObj[Channel].LowTime              = lowTime;
            Icu_ChObj[Channel].Period               = period;
            Icu_ChObj[Channel].DutyCycle.PeriodTime = period;
            Icu_ChObj[Channel].DutyCycle.ActiveTime = highTime;
            Icu_ChObj[Channel].DutyAcquired         = TRUE;
            Icu_ChObj[Channel].PeriodAcquired       = TRUE;
        }

        Icu_ChObj[Channel].IsRunning = FALSE;
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }

    return;
}

#endif /* ICU_SIGNAL_MEASUREMENT_API*/

/*
 *Design: MCAL-12298, MCAL-12299, MCAL-12300, MCAL-12301, MCAL-12302, MCAL-12458, MCAL-12459,
 *MCAL-12460, MCAL-12461, MCAL-12462, MCAL-12463, MCAL-12464
 */
#if (STD_ON == ICU_GET_TIME_ELAPSED_API)
FUNC(Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed(Icu_ChannelType Channel)
{
    Icu_ValueType elapsedTime             = 0U;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkGetTimeElapsedErrors(Channel);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        if (Icu_ChObj[Channel].PeriodAcquired == TRUE)
        {
            switch (Icu_ChObj[Channel].chCfg.signalMeasurementProperty)
            {
                case ICU_DUTY_CYCLE:
                    elapsedTime = Icu_ChObj[Channel].Period;
                    break;
                case ICU_PERIOD_TIME:
                    elapsedTime = Icu_ChObj[Channel].Period;
                    break;
                case ICU_HIGH_TIME:
                    elapsedTime = Icu_ChObj[Channel].HighTime;
                    break;
                case ICU_LOW_TIME:
                    elapsedTime = Icu_ChObj[Channel].LowTime;
                    break;
                default:
                    elapsedTime = 0U;
                    break;
            }
            Icu_ChObj[Channel].PeriodAcquired = FALSE;
        }
        else
        {
            elapsedTime = 0U;
        }
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }
    return elapsedTime;
}

#endif

/*
 *Design: MCAL-12465, MCAL-12466, MCAL-12467, MCAL-12468, MCAL-12469, MCAL-12470, MCAL-12471,
 *MCAL-12472, MCAL-12473, MCAL-12474
 */
#if (STD_ON == ICU_GET_DUTY_CYCLE_VALUES_API)
FUNC(void, ICU_CODE)
Icu_GetDutyCycleValues(Icu_ChannelType Channel, Icu_DutyCycleType* DutyCycleValues)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    retVal = Icu_checkGetDutyCycleValuesErrors(Channel, DutyCycleValues);
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        SchM_Enter_Icu_ICU_EXCLUSIVE_AREA_0();
        if (Icu_ChObj[Channel].DutyAcquired == TRUE)
        {
            DutyCycleValues->PeriodTime = Icu_ChObj[Channel].DutyCycle.PeriodTime;
            DutyCycleValues->ActiveTime = Icu_ChObj[Channel].DutyCycle.ActiveTime;

            Icu_ChObj[Channel].DutyAcquired = FALSE;
        }
        else
        {
            DutyCycleValues->PeriodTime = 0U;
            DutyCycleValues->ActiveTime = 0U;
        }
        SchM_Exit_Icu_ICU_EXCLUSIVE_AREA_0();
    }
}

#endif

/*
 *Design: MCAL-12475, MCAL-12476
 */
#if (STD_ON == ICU_GET_VERSION_INFO_API)
FUNC(void, ICU_CODE)
Icu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_APPL_DATA) VersionInfoPtr)
{
#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        Icu_reportDetError(ICU_GETVERSIONINFO_ID, ICU_E_PARAM_VINFO);
    }
    else
#endif
    {
        VersionInfoPtr->vendorID         = ICU_VENDOR_ID;
        VersionInfoPtr->moduleID         = ICU_MODULE_ID;
        VersionInfoPtr->sw_major_version = (uint8)ICU_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)ICU_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)ICU_SW_PATCH_VERSION;
    }

    return;
}
#endif /* ICU_GET_VERSION_INFO_API*/

#if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(void, ICU_CODE) Icu_CheckWakeup(EcuM_WakeupSourceType WakeupSource)
{
    return;
}
#endif /* if(ICU_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (ICU_DISABLEWAKEUP_API == STD_ON)
FUNC(void, ICU_CODE) Icu_DisableWakeup(Icu_ChannelType Channel)
{
    return;
}
#endif /* if(ICU_DISABLEWAKEUP_API == STD_ON) */

#if (ICU_ENABLEWAKEUP_API == STD_ON)
FUNC(void, ICU_CODE) Icu_EnableWakeup(Icu_ChannelType Channel)
{
    return;
}
#endif /* if(ICU_ENABLEWAKEUP_API == STD_ON) */

#if (ICU_SETMODE_API == STD_ON)
FUNC(void, ICU_CODE) Icu_SetMode(Icu_ModeType Mode)
{
    return;
}
#endif /* if (ICU_SETMODE_API == STD_ON) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkInitErrors(const Icu_ConfigType* IcuConfigPtr)
{
    Std_ReturnType retVal = E_OK;

    if (NULL == IcuConfigPtr)
    {
        (void)Icu_reportDetError(ICU_INIT_ID, ICU_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    if ((ICU_STATUS_INIT == Icu_DrvStatus) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_INIT_ID, ICU_E_ALREADY_INITIALIZED);
        retVal = E_NOT_OK;
    }
    return retVal;
}
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

static FUNC(void, ICU_CODE) Icu_CheckInit_Internal(uint32 chNum, const Icu_ConfigType* IcuConfigPtr)
{
    uint32 chIdx;
    for (chIdx = 0; chIdx < ICU_MAX_NUM_CHANNELS; chIdx++)
    {
        if (chIdx == ((&IcuConfigSet_PC)->chCfg[chNum].channelId))
        {
            /* Reset Channel object */
            Icu_ResetChObj(&Icu_ChObj[chIdx]);
            /* Copy the configuration */
            Icu_CopyConfig(&Icu_ChObj[chIdx], &IcuConfigPtr->chCfg[chNum], &IcuConfigSet_PC.chCfg[chNum]);
            /* HW Channel Init */
            Icu_HwUnitInit(&Icu_ChObj[chIdx]);

#if (STD_ON == ICU_TIMESTAMP_API)
            Icu_ChObj[chIdx].IsActive = FALSE;
#endif
            break;
        }
    }
}

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE)
    Icu_checkSetActivationConditionErrors(Icu_ChannelType Channel, Icu_ActivationType Activation)
{
    Std_ReturnType retVal = E_OK;

    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_SETACTIVATIONCONDITION_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_SETACTIVATIONCONDITION_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_SIGNAL_MEASUREMENT == Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_SETACTIVATIONCONDITION_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }
    if ((Activation != ICU_RISING_EDGE) && (Activation != ICU_FALLING_EDGE) && (Activation != ICU_BOTH_EDGES) &&
        (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_SETACTIVATIONCONDITION_ID, ICU_E_PARAM_ACTIVATION);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)

static FUNC(Std_ReturnType, ICU_CODE) Icu_checkGetInputStateErrors(Icu_ChannelType Channel)
{
    Std_ReturnType retVal = E_OK;

    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_GETINPUTSTATE_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETINPUTSTATE_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_SIGNAL_EDGE_DETECT != Icu_ChObj[Channel].chCfg.measurementMode) &&
        (ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETINPUTSTATE_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }
    return retVal;
}
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE)
    Icu_checkStartTimestampErrors(Icu_ChannelType Channel, Icu_ValueType* BufferPtr, uint16 BufferSize)
{
    Std_ReturnType retVal = E_OK;

    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_STARTTIMESTAMP_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_TIMESTAMP != Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((NULL_PTR == BufferPtr) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    if ((0U == BufferSize) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STARTTIMESTAMP_ID, ICU_E_PARAM_BUFFER_SIZE);
        retVal = E_NOT_OK;
    }
    return retVal;
}

#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkStopTimestampErrors(Icu_ChannelType Channel)
{
    Std_ReturnType retVal = E_OK;
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_STOPTIMESTAMP_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STOPTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_TIMESTAMP != Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STOPTIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkGetTimestampIndexErrors(Icu_ChannelType Channel)
{
    Std_ReturnType retVal = E_OK;
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_GETTIMESTAMPINDEX_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETTIMESTAMPINDEX_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_TIMESTAMP != Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETTIMESTAMPINDEX_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }
    return retVal;
}
#endif

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkStopSignalMeasurementErrors(Icu_ChannelType Channel)
{
    Std_ReturnType retVal = E_OK;
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_STOPSIGNALMEASUREMENT_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STOPSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_STOPSIGNALMEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }
    return retVal;
}

#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE)
    Icu_checkGetDutyCycleValuesErrors(Icu_ChannelType Channel, Icu_DutyCycleType* DutyCycleValues)
{
    Std_ReturnType retVal = E_OK;
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_GETDUTYCYCLEVALUES_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETDUTYCYCLEVALUES_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETDUTYCYCLEVALUES_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((NULL_PTR == DutyCycleValues) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETDUTYCYCLEVALUES_ID, ICU_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }
    return retVal;
}
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

#if (STD_ON == ICU_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ICU_CODE) Icu_checkGetTimeElapsedErrors(Icu_ChannelType Channel)
{
    Std_ReturnType retVal = E_OK;
    if (ICU_STATUS_UNINIT == Icu_DrvStatus)
    {
        (void)Icu_reportDetError(ICU_GETTIMEELAPSED_ID, ICU_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ICU_MAX_NUM_CHANNELS <= Channel) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETTIMEELAPSED_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }

    if ((ICU_MODE_SIGNAL_MEASUREMENT != Icu_ChObj[Channel].chCfg.measurementMode) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Icu_reportDetError(ICU_GETTIMEELAPSED_ID, ICU_E_PARAM_CHANNEL);
        retVal = E_NOT_OK;
    }
    return retVal;
}
#endif /* (STD_ON == ICU_DEV_ERROR_DETECT) */

/*
 *Design: MCAL-20912
 */
#if (STD_ON == ICU_REGISTER_READBACK_API)
FUNC(Std_ReturnType, ICU_CODE)
Icu_RegisterReadback(Icu_ChannelType Channel, P2VAR(Icu_RegisterReadbackType, AUTOMATIC, ICU_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == ICU_DEV_ERROR_DETECT)
    if ((ICU_STATUS_UNINIT == Icu_DrvStatus))
    {
        (void)Icu_reportDetError(ICU_REGISTERREADBACK_ID, ICU_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (NULL_PTR == RegRbPtr)
    {
        (void)Icu_reportDetError(ICU_REGISTERREADBACK_ID, ICU_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /*MISRA-C*/
    }
#endif

    /* Check if return value is correct. */
    if (retVal == E_OK)
    {
        /* Readback the register. */
        Icu_HwRegisterReadback(Channel, RegRbPtr);
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    /* Return the Value. */
    return (retVal);
}
#endif

#define ICU_STOP_SEC_CODE
#include "Icu_MemMap.h"
