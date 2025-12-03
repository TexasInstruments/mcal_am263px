/* ======================================================================
 *   Copyright (C) 2023-2024 Texas Instruments Incorporated
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
 *  \file     Spi.c
 *
 *  \brief    This file contains SPI MCAL driver
 *
 */

/* =============================================================== */
/*                             Include Files                       */
/* =============================================================== */

#include "Spi.h"
#include "Spi_Priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */
/*                           Macros & Typedefs                      */
/* ================================================================ */

/* AUTOSAR version information check has to match definition
                                                     in header file */
#if ((SPI_AR_RELEASE_MAJOR_VERSION != (4U)) || (SPI_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (SPI_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Spi: AUTOSAR Version Numbers of Spi are different!!"
#endif

/* Driver version information check has to match definition
                                                     in header file */
#if ((SPI_SW_MAJOR_VERSION != (10U)) || (SPI_SW_MINOR_VERSION != (2U)) || (SPI_SW_PATCH_VERSION != (0U)))
#error "Spi: Software Version Numbers are inconsistent!!"
#endif

/* ================================================================ */
/*                         Structures and Enums                     */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                 Internal Function Declarations                   */
/* ================================================================ */
/*  */
#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
#if (STD_ON == SPI_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, SPI_CODE)
    Spi_writeIBDetErrCheck(Spi_ChannelType Channel,
                           P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr);

#endif /* (STD_ON == SPI_DEV_ERROR_DETECT) */
#endif /* (SPI_CHANNELBUFFERS == SPI_IB) || \
                                  (SPI_CHANNELBUFFERS == SPI_IB_EB) */
static void           Spi_readIB_tempBuf_update(Spi_ChannelObjType *chObj, Spi_DataBufferType *DataBufferPointer);
static void           Spi_writeIB_tempBuf_update(Spi_ChannelObjType *chObj, const Spi_DataBufferType *DataBufferPtr);
static Std_ReturnType Spi_asyncTransmit_Start(Spi_SequenceType Sequence, Std_ReturnType *retVal);
#if (STD_OFF == SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT)
static Std_ReturnType Spi_syncTransmit_GetResult(Std_ReturnType *retVal);
#endif
#if (STD_ON == SPI_DEV_ERROR_DETECT)
static uint8 SPI_init_CheckDetError(const Spi_ConfigType *ConfigPtr);
#endif

/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

#define SPI_START_SEC_VAR_INIT_UNSPECIFIED
#include "Spi_MemMap.h"
/** \brief SPI driver status */
/* Requirements : SWS_Spi_00373,SWS_Spi_00061,SWS_Spi_00011,SWS_Spi_00345 */
volatile VAR(Spi_StatusType, SPI_VAR_CLEARED) Spi_DrvStatus = SPI_UNINIT;
#define SPI_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"
/** \brief SPI driver object */
VAR(Spi_DriverObjType, SPI_VAR_CLEARED) Spi_DrvObj;
#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

/* ================================================================ */
/*                          Function Definitions                    */
/* ================================================================ */

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

/*
 *Design: MCAL-14448, MCAL-14447, MCAL-14446, MCAL-14445, MCAL-14444, MCAL-14443, MCAL-14442,
 *MCAL-14049, MCAL-14050, MCAL-14051, MCAL-15082
 */
/* Requirements : SWS_Spi_00175,SWS_Spi_00298,SWS_Spi_00299,SWS_Spi_00013,
 *                 SWS_Spi_00240,SWS_Spi_00241,SWS_Spi_00246,
 *                  SWS_Spi_00004,SWS_Spi_00237,SWS_Spi_00238,
 *                 SWS_Spi_00031,SWS_Spi_00032,SWS_Spi_00143,SWS_Spi_00288,
 *                  SWS_Spi_00233,SWS_Spi_00235,SWS_Spi_00999,
 */
FUNC(void, SPI_CODE) Spi_Init(P2CONST(Spi_ConfigType, AUTOMATIC, SPI_CONFIG_DATA) CfgPtr)
{
    uint32                index     = 0U;
    const Spi_ConfigType *ConfigPtr = (Spi_ConfigType *)NULL_PTR;

    Std_ReturnType retVal = E_OK;
#if (STD_ON == SPI_DEV_ERROR_DETECT)
    uint8 ConditionCheck = 0U;
#endif

#if (STD_ON == SPI_PRE_COMPILE_VARIANT)
    if (NULL_PTR == CfgPtr)
    {
        ConfigPtr = &SPI_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == SPI_PRE_COMPILE_VARIANT) */
#if ((STD_ON == SPI_VARIANT_POST_BUILD) || (STD_ON == SPI_LINK_TIME_VARIANT))

    if (NULL_PTR != CfgPtr)
    {
        ConfigPtr = CfgPtr;
    }
#endif /* (STD_ON == SPI_POST_BUILD_VARIANT)|| \
          (STD_ON == SPI_LINK_TIME_VARIANT) */
#if (STD_ON == SPI_DEV_ERROR_DETECT)
    ConditionCheck = SPI_init_CheckDetError(ConfigPtr);
    if ((ConditionCheck == 0U) && (ConfigPtr->maxExtDevCfg > SPI_MAX_EXT_DEV))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_JOB);
    }
    if (ConditionCheck == 0U)
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
#if (STD_ON == SPI_DEV_ERROR_DETECT)
        /* Check the configuration */
        retVal = Spi_checkConfig(ConfigPtr);
        if (((Std_ReturnType)E_OK) == retVal)
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
        {
            Spi_resetDrvObj(&Spi_DrvObj);
            Spi_copyConfig(&Spi_DrvObj, ConfigPtr);

            /* Init HW once all config is copied */
            for (index = 0U; index < ConfigPtr->maxHwUnit; index++)
            {
                Spi_hwUnitInit(&Spi_DrvObj.hwUnitObj[index]);
            }
        }
        if (E_OK == retVal)
        {
            /* Initialize driver status and object */
            Spi_DrvStatus = SPI_IDLE;
        }
    }
}

/*
 *Design: MCAL-14449, MCAL-14450, MCAL-14451, MCAL-14452, MCAL-14453, MCAL-14454, MCAL-14455,
 *MCAL-14456, MCAL-14457
 */
/*
 * Requirements :SWS_Spi_00022,SWS_Spi_00176,SWS_Spi_00303,SWS_Spi_00021,
 *                SWS_Spi_00300,SWS_Spi_00301,SWS_Spi_00302,SWS_Spi_00242,
 *                SWS_Spi_00046
 */
FUNC(Std_ReturnType, SPI_CODE) Spi_DeInit(void)
{
    uint32         index  = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        Spi_reportDetError(SPI_SID_DEINIT, SPI_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        if (SPI_BUSY == Spi_DrvStatus)
        {
            /* Do nothing */
        }
        else
        {
            Spi_DrvStatus = SPI_UNINIT;
            retVal        = ((Std_ReturnType)E_OK);
            /* Deinit the hardware modules */
            for (index = 0U; index < Spi_DrvObj.maxHwUnit; index++)
            {
                Spi_hwUnitDeInit(&Spi_DrvObj.hwUnitObj[index]);
            }
            Spi_resetDrvObj(&Spi_DrvObj);
        }
    }

    return (retVal);
}

/*
 *Design: MCAL-14458, MCAL-14459, MCAL-14460, MCAL-14461
 */
/*
 * Requirements : SWS_Spi_00181,SWS_Spi_00319,SWS_Spi_00320,SWS_Spi_00025,
 *                SWS_Spi_00259
 */
FUNC(Spi_StatusType, SPI_CODE) Spi_GetStatus(void)
{
    return (Spi_DrvStatus);
}

/*
 *Design: MCAL-14462, MCAL-14463, MCAL-14464, MCAL-14465, MCAL-14466
 */
/*
 * Requirements : SWS_Spi_00182,SWS_Spi_00322,SWS_Spi_00026,SWS_Spi_00038,
 *                SWS_Spi_00254,SWS_Spi_00350,SWS_Spi_00256,SWS_Spi_00194
 */
FUNC(Spi_JobResultType, SPI_CODE) Spi_GetJobResult(Spi_JobType Job)
{
    Spi_JobResultType jobResult = SPI_JOB_FAILED;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        Spi_reportDetError(SPI_SID_GET_JOB_RESULT, SPI_E_UNINIT);
    }
    else if (Job >= Spi_DrvObj.maxJobs)
    {
        Spi_reportDetError(SPI_SID_GET_JOB_RESULT, SPI_E_PARAM_JOB);
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        jobResult = Spi_DrvObj.jobObj[Job].jobResult;
    }

    return (jobResult);
}

/*
 *Design: MCAL-14467, MCAL-14468,MCAL-14469,MCAL-14470
 */
/*
 * Requirements : SWS_Spi_00183,SWS_Spi_00323,SWS_Spi_00324,SWS_Spi_00039,
 *                SWS_Spi_00042
 */
FUNC(Spi_SeqResultType, SPI_CODE)
Spi_GetSequenceResult(Spi_SequenceType Sequence)
{
    Spi_SeqResultType seqResult = SPI_SEQ_FAILED;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        Spi_reportDetError(SPI_SID_GET_SEQ_RESULT, SPI_E_UNINIT);
    }
    else if (Sequence >= Spi_DrvObj.maxSeq)
    {
        Spi_reportDetError(SPI_SID_GET_SEQ_RESULT, SPI_E_PARAM_SEQ);
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        seqResult = Spi_DrvObj.seqObj[Sequence].seqResult;
    }

    return (seqResult);
}

#if (STD_ON == SPI_VERSION_INFO_API)
/*
 *Design: MCAL-14577, MCAL-14578, MCAL-14083, MCAL-15083
 */
/*
 * Requirements : SWS_Spi_00184,SWS_Spi_00371
 */
FUNC(void, SPI_CODE)
Spi_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) versioninfo)
{
#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (NULL_PTR == versioninfo)
    {
        Spi_reportDetError(SPI_SID_GET_VERSION_INFO, SPI_E_PARAM_POINTER);
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        versioninfo->vendorID         = SPI_VENDOR_ID;
        versioninfo->moduleID         = SPI_MODULE_ID;
        versioninfo->sw_major_version = (uint8)SPI_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)SPI_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)SPI_SW_PATCH_VERSION;
    }
}
#endif /* #if (STD_ON == SPI_VERSION_INFO_API) */

/*
 *Design: MCAL-14471, MCAL-14472, MCAL-14473, MCAL-14474, MCAL-14475, MCAL-14476, MCAL-14228
 *
 */
#if (STD_ON == SPI_HW_STATUS_API)
/* Design :  SPI_DesignId_014 */
/*
 * Requirements : SWS_Spi_00186,SWS_Spi_00141,SWS_Spi_00142,SWS_Spi_00260,
 *                SWS_Spi_00260
 */
FUNC(Spi_StatusType, SPI_CODE) Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit)
{
    Spi_HwUnitObjType *hwUnitObj    = (Spi_HwUnitObjType *)NULL_PTR;
    Spi_StatusType     hwUnitStatus = SPI_UNINIT;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    uint8 ConditionCheck = 0U;
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_GET_HW_UNIT_STATUS, SPI_E_UNINIT);
    }
    if ((HWUnit >= SPI_HW_UNIT_CNT) && (ConditionCheck == 0U))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_GET_HW_UNIT_STATUS, SPI_E_PARAM_UNIT);
    }
    if (ConditionCheck == 0U)
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

        /* HW unit ID may not be the index, so search for
                                                   matching HW unit */
        hwUnitObj = Spi_getHwUnitObj(HWUnit);
        if (NULL_PTR != hwUnitObj)
        {
            if (SPI_HW_UNIT_OK == hwUnitObj->hwUnitResult)
            {
                hwUnitStatus = SPI_IDLE;
            }
            else
            {
                hwUnitStatus = SPI_BUSY;
            }
        }

        SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
    }

    return (hwUnitStatus);
}
#endif /* #if (STD_ON == SPI_HW_STATUS_API) */

#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
/*
 *Design: MCAL-14638, MCAL-14639, MCAL-14640, MCAL-14641, MCAL-14642, MCAL-14643, MCAL-14644,
 *MCAL-14645, MCAL-14646, MCAL-22665, MCAL-22666, MCAL-22667
 */
/*
 * Requirements :SWS_Spi_00023,SWS_Spi_00137, SWS_Spi_00177,SWS_Spi_0017,
 *                SWS_Spi_00305,SWS_Spi_00306,SWS_Spi_00307,SWS_Spi_00018,
 *                SWS_Spi_00024
 */
FUNC(Std_ReturnType, SPI_CODE)
Spi_WriteIB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr)
{
    Std_ReturnType      retVal = (Std_ReturnType)E_OK;
    Spi_ChannelObjType *chObj;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if ((Std_ReturnType)E_NOT_OK == Spi_writeIBDetErrCheck(Channel, DataBufferPtr))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

        chObj = &Spi_DrvObj.channelObj[Channel];

        Spi_writeIB_tempBuf_update(chObj, DataBufferPtr);
        SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}

static void Spi_writeIB_tempBuf_update(Spi_ChannelObjType *chObj, const Spi_DataBufferType *DataBufferPtr)
{
    const uint8  *tempBuf8    = (uint8 *)NULL_PTR;
    uint8        *tempIbPtr8  = (uint8 *)NULL_PTR;
    const uint16 *tempBuf16   = (uint16 *)NULL_PTR;
    uint16       *tempIbPtr16 = (uint16 *)NULL_PTR;
    const uint32 *tempBuf32   = (uint32 *)NULL_PTR;
    uint32       *tempIbPtr32 = (uint32 *)NULL_PTR;
    uint32        index       = 0U;

    if (1U == chObj->bufWidth)
    {
        tempIbPtr8 = ((uint8 *)&chObj->txIb[0U]);
        for (index = 0U; index < chObj->chCfg.maxBufLength; index++)
        {
            if (NULL_PTR != DataBufferPtr)
            {
                tempBuf8  = (const uint8 *)DataBufferPtr;
                tempBuf8 += index;
            }
            else
            {
                tempBuf8 = ((const uint8 *)&chObj->chCfg.defaultTxData);
            }
            tempIbPtr8[index] = *tempBuf8;
        }
    }
    else if (2U == chObj->bufWidth)
    {
        tempIbPtr16 = ((uint16 *)&chObj->txIb[0U]);
        for (index = 0U; index < chObj->chCfg.maxBufLength; index++)
        {
            if (NULL_PTR != DataBufferPtr)
            {
                tempBuf16  = (const uint16 *)DataBufferPtr;
                tempBuf16 += index;
            }
            else
            {
                tempBuf16 = ((const uint16 *)&chObj->chCfg.defaultTxData);
            }
            tempIbPtr16[index] = *tempBuf16;
        }
    }
    else
    {
        tempIbPtr32 = ((uint32 *)&chObj->txIb[0U]);
        for (index = 0U; index < chObj->chCfg.maxBufLength; index++)
        {
            if (NULL_PTR != DataBufferPtr)
            {
                tempBuf32  = (const uint32 *)DataBufferPtr;
                tempBuf32 += index;
            }
            else
            {
                tempBuf32 = ((const uint32 *)&chObj->chCfg.defaultTxData);
            }
            tempIbPtr32[index] = *tempBuf32;
        }
    }
}

/*
 *Design: MCAL-14647, MCAL-14648, MCAL-14649, MCAL-14650, MCAL-14651, MCAL-14652, MCAL-14653,
 *MCAL-14654, MCAL-14646
 */
/*
 * Requirements : SWS_Spi_00179,SWS_Spi_00312,SWS_Spi_00313,SWS_Spi_00314,
 *                SWS_Spi_00315,SWS_Spi_00016,SWS_Spi_00027,SWS_Spi_00138
 */
FUNC(Std_ReturnType, SPI_CODE)
Spi_ReadIB(Spi_ChannelType Channel, P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPointer)
{
    Std_ReturnType      retVal = (Std_ReturnType)E_OK;
    Spi_ChannelObjType *chObj  = (Spi_ChannelObjType *)NULL_PTR;
#if (STD_ON == SPI_DEV_ERROR_DETECT)
    uint8 ConditionCheck = 0U;
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_READ_IB, SPI_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (((Channel >= Spi_DrvObj.maxChannels) || (Spi_DrvObj.channelObj[Channel].chCfg.channelBufType != SPI_IB)) &&
        (ConditionCheck == 0U))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_READ_IB, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (((NULL_PTR == DataBufferPointer) || (((uint32)DataBufferPointer & SPI_IB_ALIGNMENGT) != 0U)) &&
        (ConditionCheck == 0U))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_READ_IB, SPI_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (ConditionCheck == 0U)
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

        chObj = &Spi_DrvObj.channelObj[Channel];
        Spi_readIB_tempBuf_update(chObj, DataBufferPointer);

        SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}

static void Spi_readIB_tempBuf_update(Spi_ChannelObjType *chObj, Spi_DataBufferType *DataBufferPointer)
{
    uint32  index       = 0U;
    uint8  *tempBuf8    = (uint8 *)NULL_PTR;
    uint8  *tempIbPtr8  = (uint8 *)NULL_PTR;
    uint16 *tempBuf16   = (uint16 *)NULL_PTR;
    uint16 *tempIbPtr16 = (uint16 *)NULL_PTR;
    uint32 *tempBuf32   = (uint32 *)NULL_PTR;
    uint32 *tempIbPtr32 = (uint32 *)NULL_PTR;

    if (1U == chObj->bufWidth)
    {
        tempBuf8   = (uint8 *)DataBufferPointer;
        tempIbPtr8 = ((uint8 *)&chObj->rxIb[0U]);
        for (index = 0U; index < chObj->chCfg.maxBufLength; index++)
        {
            tempBuf8[index] = tempIbPtr8[index];
        }
    }
    else if ((2U == chObj->bufWidth))
    {
        tempBuf16   = (uint16 *)DataBufferPointer;
        tempIbPtr16 = ((uint16 *)&chObj->rxIb[0U]);
        for (index = 0U; index < chObj->chCfg.maxBufLength; index++)
        {
            tempBuf16[index] = tempIbPtr16[index];
        }
    }
    else
    {
        tempBuf32   = (uint32 *)DataBufferPointer;
        tempIbPtr32 = ((uint32 *)&chObj->rxIb[0U]);
        for (index = 0U; index < chObj->chCfg.maxBufLength; index++)
        {
            tempBuf32[index] = tempIbPtr32[index];
        }
    }
}
#endif /* #if SPI_IB || SPI_IB_EB */

#if ((SPI_CHANNELBUFFERS == SPI_EB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
/*
 *Design: MCAL-14477, MCAL-14478, MCAL-14479, MCAL-14480, MCAL-14481, MCAL-14482, MCAL-14483,
 *MCAL-14485, MCAL-14486, MCAL-14487, MCAL-14488, MCAL-14216, MCAL-14215, MCAL-14214, MCAL-22668,
 *MCAL-22669
 */
/*
 *Design: MCAL-14216, MCAL-14214, MCAL-22668, MCAL-14199, MCAL-14484
 */
/*
 * Requirements :SWS_Spi_00060,SWS_Spi_00180,SWS_Spi_00316,SWS_Spi_00317,
 *                SWS_Spi_00067,SWS_Spi_00067,SWS_Spi_00030,SWS_Spi_00037,
 *                SWS_Spi_00139,SWS_Spi_00318,SWS_Spi_00077,SWS_Spi_00078
 */
FUNC(Std_ReturnType, SPI_CODE)
Spi_SetupEB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
            P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr, Spi_NumberOfDataType Length)
{
    Std_ReturnType      retVal = (Std_ReturnType)E_OK;
    Spi_ChannelObjType *chObj  = (Spi_ChannelObjType *)NULL_PTR;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    uint8 ConditionCheck = 0U;
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_SETUP_EB, SPI_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (((Channel >= Spi_DrvObj.maxChannels) || (Spi_DrvObj.channelObj[Channel].chCfg.channelBufType != SPI_EB)) &&
        (ConditionCheck == 0U))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_SETUP_EB, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (ConditionCheck == 0U)
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

        chObj = &Spi_DrvObj.channelObj[Channel];

#if (STD_ON == SPI_DEV_ERROR_DETECT)
        /* Buffers must always be 32-bit aligned - MCAL-1364 */
        if ((((uint32)SrcDataBufferPtr & 0x03U) != 0U) || (((uint32)DesDataBufferPtr & 0x03U) != 0U))
        {
            Spi_reportDetError(SPI_SID_SETUP_EB, SPI_E_PARAM_POINTER);
            retVal = (Std_ReturnType)E_NOT_OK;
        }

        if (((Std_ReturnType)E_OK) == retVal)
        {
            /* now check length */
            if ((Length == 0U) || (Length > chObj->chCfg.maxBufLength))
            {
                Spi_reportDetError(SPI_SID_SETUP_EB, SPI_E_PARAM_LENGTH);
                retVal = (Std_ReturnType)E_NOT_OK;
            }
        }
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */

        if (((Std_ReturnType)E_OK) == retVal)
        {
            chObj->txBufPtr     = SrcDataBufferPtr;
            chObj->rxBufPtr     = DesDataBufferPtr;
            chObj->numWordsTxRx = Length;
            retVal              = ((Std_ReturnType)E_OK);
        }

        SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
    }

    return (retVal);
}
#endif /* #if ((SPI_CHANNELBUFFERS == SPI_EB) || (SPI_CHANNELBUFFERS \
        * ==SPI_IB_EB)) */

#if ((SPI_SCALEABILITY == SPI_LEVEL_1) || (SPI_SCALEABILITY == SPI_LEVEL_2))
/*
 *Design: MCAL-14489, MCAL-14490, MCAL-14491, MCAL-14492, MCAL-14493, MCAL-14494, MCAL-14495,
 *MCAL-14496, MCAL-14497, MCAL-14498, MCAL-14499, MCAL-14500, MCAL-14501, MCAL-14502, MCAL-14503,
 *MCAL-14505, MCAL-14506, MCAL-14507, MCAL-145086, MCAL-13952, MCAL-13953, MCAL-13956
 */
/*
 *Design: MCAL-14225, MCAL-14226, MCAL-14227, MCAL-14220, MCAL-14229, MCAL-14230, MCAL-14231,
 *MCAL-14232, MCAL-14233, MCAL-14234, MCAL-14226, MCAL-14227, MCAl-14228, MCAL-14229, MCAL-14232,
 *MCAL-14233, MCAL-14234,
 */
/*
 *Design: MCAL-14248, MCAL-14247, MCAL-14245, MCAL-14246, MCAL-14251, MCAL-14250, MCAL-14253,
 *MCAL-14249, MCAL-14252, MCAL-14258, MCAL-14580, MCAL-15086, MCAL-14504
 */
/*
 * Requirements :SWS_Spi_00055,SWS_Spi_00057,SWS_Spi_00133, SWS_Spi_00178,
 *               SWS_Spi_00157,SWS_Spi_00292,SWS_Spi_00293,SWS_Spi_00081,
 *               SWS_Spi_00086,SWS_Spi_00266, SWS_Spi_00311,SWS_Spi_00020
 *               SWS_Spi_00308,SWS_Spi_00310,SWS_Spi_00243
 */
FUNC(Std_ReturnType, SPI_CODE) Spi_AsyncTransmit(Spi_SequenceType Sequence)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    uint8 ConditionCheck = 0U;
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_ASYNC_TRANSMIT, SPI_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((Sequence >= Spi_DrvObj.maxSeq) && (ConditionCheck == 0U))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_ASYNC_TRANSMIT, SPI_E_PARAM_SEQ);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (ConditionCheck == 0U)
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        retVal = Spi_asyncTransmit_Start(Sequence, &retVal);
    }

    return (retVal);
}

static Std_ReturnType Spi_asyncTransmit_Start(Spi_SequenceType Sequence, Std_ReturnType *retVal)
{
    if (Spi_GetSequenceResult(Sequence) == SPI_SEQ_PENDING)
    {
        Spi_reportDetRuntimeError(SPI_SID_ASYNC_TRANSMIT, SPI_E_SEQ_PENDING);
        *retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* Call the start sequence API */
        *retVal = Spi_startSeqAsync(&(Spi_DrvObj.seqObj[Sequence]));
        if (((Std_ReturnType)E_NOT_OK) == *retVal)
        {
            Spi_reportDetRuntimeError(SPI_SID_ASYNC_TRANSMIT, SPI_E_SEQ_PENDING);
        }
    }
    return (*retVal);
}
#endif /* #if ((SPI_SCALEABILITY == SPI_LEVEL_1) || \
        *(SPI_SCALEABILITY == SPI_LEVEL_2)) */

/*
 *Design: MCAL-14508, MCAL-14509, MCAL-14510, MCAL-14511, MCAL-14512,MCAL-14513
 */
#if (STD_ON == SPI_CANCEL_API)
/*
 * Requirements : SWS_Spi_00187,SWS_Spi_00333,SWS_Spi_00334,SWS_Spi_00144,
 *                SWS_Spi_00145,SWS_Spi_00146
 */
FUNC(void, SPI_CODE) Spi_Cancel(Spi_SequenceType Sequence)
{
#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        Spi_reportDetError(SPI_SID_CANCEL, SPI_E_UNINIT);
    }
    else if (Sequence >= Spi_DrvObj.maxSeq)
    {
        Spi_reportDetError(SPI_SID_CANCEL, SPI_E_PARAM_SEQ);
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        Spi_cancelSequence(&Spi_DrvObj.seqObj[Sequence]);
    }
}
#endif /* #if (STD_ON == SPI_CANCEL_API) */

#if ((SPI_SCALEABILITY == SPI_LEVEL_0) || (SPI_SCALEABILITY == SPI_LEVEL_2))
/*
 * Requirements :SWS_Spi_00185,SWS_Spi_00327,SWS_Spi_00328,SWS_Spi_00329,
 *               SWS_Spi_00329,SWS_Spi_00036,SWS_Spi_00035, SWS_Spi_00114,
 *               SWS_Spi_00330,SWS_Spi_00134,SWS_Spi_00285,SWS_Spi_00286,
 *                SWS_Spi_00136,SWS_Spi_00135
 */
/*
 *Design: MCAL-14558, MCAL-14559, MCAL-14560, MCAL-14561, MCAL-14562, MCAL-14563, MCAL-14564,
 *MCAL-14655, MCAL-14566 , MCAL-16641, MCAL-22691, MCAL-14208, MCAL-14203, MCAL-14202, MCAL-14199,
 *MCAL-14256
 */
/*
 *Design: MCAL-14219, MCAL-14220, MCAL-14221, MCAL-14222, MCAL_14223, MCAL-14224, MCAL-14235,
 *MCAL-14326, MCAL-14327, MCAL-14328, MCAL-14237, MCAL-14238, MCAL-14244, MCAL-14257, MCAL-14254
 */
/*
 *Design: MCAL-14262, MCAL-14261, MCAL-14259, MCAL-14258, MCAL-22697,MCAL-14565
 */
FUNC(Std_ReturnType, SPI_CODE) Spi_SyncTransmit(Spi_SequenceType Sequence)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    uint8 ConditionCheck = 0U;
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_SYNC_TRANSMIT, SPI_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if ((Sequence >= Spi_DrvObj.maxSeq) && (ConditionCheck == 0U))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_SYNC_TRANSMIT, SPI_E_PARAM_SEQ);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (ConditionCheck == 0U)
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        if (Spi_GetSequenceResult(Sequence) == SPI_SEQ_PENDING)
        {
            Spi_reportDetRuntimeError(SPI_SID_SYNC_TRANSMIT, SPI_E_SEQ_PENDING);
            retVal = (Std_ReturnType)E_NOT_OK;
        }
#if (STD_OFF == SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT)
        /* Requirements : SWS_Spi_00245 */
        retVal = Spi_syncTransmit_GetResult(&retVal);
#endif

        if (((Std_ReturnType)E_OK) == retVal)
        {
            SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();
            /* Call the start sequence API */
            Spi_SeqObjType *seqObjTmp = &(Spi_DrvObj.seqObj[Sequence]);
            retVal                    = Spi_startSeqSync(seqObjTmp);

            SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
        }
    }

    return (retVal);
}

#if (STD_OFF == SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT)
static Std_ReturnType Spi_syncTransmit_GetResult(Std_ReturnType *retVal)
{
    Spi_SequenceType index = 0U;

    for (index = (Spi_SequenceType)0; index < (Spi_SequenceType)Spi_DrvObj.maxSeq; index++)
    {
        if (Spi_GetSequenceResult(index) == SPI_SEQ_PENDING)
        {
            Spi_reportDetRuntimeError(SPI_SID_SYNC_TRANSMIT, SPI_E_SEQ_IN_PROCESS);
            *retVal = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }
    return (*retVal);
}
#endif
#endif

#if (SPI_SCALEABILITY == SPI_LEVEL_2)
/*
 *Design: MCAL-14567, MCAL-14568, MCAL-14569, MCAL-14570, MCAL-14571, MCAL-14572, MCAL-14573,
 *MCAL-14574, MCAL-14575, MCAL-14255
 */
/*
 * Requirements : SWS_Spi_00188,SWS_Spi_00335,SWS_Spi_00336,SWS_Spi_00337,
 *                SWS_Spi_00172,SWS_Spi_00154,SWS_Spi_00338,SWS_Spi_00152,
 *                SWS_Spi_00171
 */
FUNC(Std_ReturnType, SPI_CODE) Spi_SetAsyncMode(Spi_AsyncModeType Mode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        /* Note: This error return is not mentioned in spec */
        Spi_reportDetError(SPI_SID_SET_ASYNC_MODE, SPI_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        if ((uint32)FALSE == Spi_DrvObj.isAsynInProgress)
        {
            Spi_DrvObj.asyncMode = Mode;
        }
        else
        {
            /* Return error incase any ASYNC transmit is in progress */
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return (retVal);
}
#endif /* #if (SPI_SCALEABILITY == SPI_LEVEL_2) */

/*
 *Design: MCAL-14576
 */
/*
 * Requirements : SWS_Spi_00151,SWS_Spi_00189 */
FUNC(void, SPI_CODE) Spi_MainFunction_Handling(void)
{
    uint32             hwUnitIdx = 0U;
    Spi_HwUnitObjType *hwUnitObj = (Spi_HwUnitObjType *)NULL_PTR;

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        /* Note: This error return is not mentioned in spec */
        Spi_reportDetError(SPI_SID_MAINFUNCTION_HANDLING, SPI_E_UNINIT);
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
    {
        /* Check all hardware units for any pending sequence */
        for (hwUnitIdx = 0U; hwUnitIdx < Spi_DrvObj.maxHwUnit; hwUnitIdx++)
        {
            hwUnitObj = &Spi_DrvObj.hwUnitObj[hwUnitIdx];
            if ((SPI_POLLING_MODE == Spi_DrvObj.asyncMode) && (NULL_PTR != hwUnitObj->curJobObj))
            {
                Spi_processEvents(hwUnitObj);
            }
        }
    }
}

#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
#if (STD_ON == SPI_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, SPI_CODE)
    Spi_writeIBDetErrCheck(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    if (SPI_UNINIT == Spi_DrvStatus)
    {
        Spi_reportDetError(SPI_SID_WRITE_IB, SPI_E_UNINIT);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if ((Channel >= Spi_DrvObj.maxChannels) || (Spi_DrvObj.channelObj[Channel].chCfg.channelBufType != SPI_IB))
    {
        Spi_reportDetError(SPI_SID_WRITE_IB, SPI_E_PARAM_CHANNEL);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else if (((uint32)DataBufferPtr & 0x03U) != 0U)
    {
        Spi_reportDetError(SPI_SID_WRITE_IB, SPI_E_PARAM_POINTER);
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* Nothing to be done here - MISRA C Fix */
    }

    return retVal;
}
#endif /* (STD_ON == SPI_DEV_ERROR_DETECT) */
#endif /* (SPI_CHANNELBUFFERS == SPI_IB) || \
                                  (SPI_CHANNELBUFFERS == SPI_IB_EB) */

#if (STD_ON == SPI_REGISTER_READBACK_API)
/*
 *Design: MCAL-14579
 */
FUNC(Std_ReturnType, SPI_CODE)
Spi_RegisterReadback(Spi_HWUnitType HWUnit, P2VAR(Spi_RegisterReadbackType, AUTOMATIC, SPI_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = ((Std_ReturnType)E_OK);

    if ((SPI_UNINIT == Spi_DrvStatus) || (NULL_PTR == RegRbPtr))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        retVal = Spi_HWRegisterReadback(HWUnit, RegRbPtr);
    }

    return (retVal);
}
#endif /* #if (STD_ON == SPI_REGISTER_READBACK_API) */

#if (STD_ON == SPI_SET_LOOPBACK_MODE_API)

FUNC(Std_ReturnType, SPI_CODE) Spi_SetLoopbackMode(Spi_HWUnitType HWUnit, boolean LoopbkEn)
{
    Spi_HwUnitObjType *hwUnitObj = (Spi_HwUnitObjType *)NULL_PTR;
    Std_ReturnType     retVal    = ((Std_ReturnType)E_OK);

    if (SPI_UNINIT == Spi_DrvStatus)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /* HW unit ID may not be the index, so search for matching HW unit */
        hwUnitObj = Spi_getHwUnitObj(HWUnit);
        if (NULL_PTR != hwUnitObj)
        {
            if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
            {
                /* Loopback mode not supported for QSPI */
                retVal = (Std_ReturnType)E_NOT_OK;
            }
            else
            {
                /* Set the flag in HW obj. This will be used when the job
                 * is configured as the loopback mode is MIBSPI channel (job)
                 * specific parameter */
                /*LDRA_INSPECTED 105 D : MISRAC_2012_R2.1
                 * "Reason - Code inspected. LDRA tool issue .
                 *Variable is used in the correct path" */
                hwUnitObj->lpbkEnable = LoopbkEn;
            }
        }
        else
        {
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return (retVal);
}
#endif /* #if (STD_ON == SPI_SET_LOOPBACK_MODE_API) */

#if (STD_ON == SPI_DEV_ERROR_DETECT)
void Spi_reportDetError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, apiId, errorId);
}

static uint8 SPI_init_CheckDetError(const Spi_ConfigType *ConfigPtr)
{
    uint8 ConditionCheck = 0U;
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_INIT, SPI_E_ALREADY_INITIALIZED);
    }
    if ((NULL_PTR == ConfigPtr) && (ConditionCheck == 0U))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_POINTER);
    }
    if ((ConditionCheck == 0U) && (ConfigPtr->maxChannels > SPI_MAX_CHANNELS))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_CHANNEL);
    }
    if ((ConditionCheck == 0U) && (ConfigPtr->maxJobs > SPI_MAX_JOBS))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_JOB);
    }
    if ((ConditionCheck == 0U) && (ConfigPtr->maxSeq > SPI_MAX_SEQ))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_SEQ);
    }
    if ((ConditionCheck == 0U) && (ConfigPtr->maxHwUnit > SPI_MAX_HW_UNIT))
    {
        ConditionCheck = 1U;
        Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_UNIT);
    }
    return (ConditionCheck);
}
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */

/*
 *Design: MCAL-14164
 */
void Spi_reportDetRuntimeError(uint8 apiId, uint8 errorId)
{
    (void)Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, apiId, errorId);
}

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
#ifdef __cplusplus
}
#endif
