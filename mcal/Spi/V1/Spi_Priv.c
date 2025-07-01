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
 *  \file     Spi_Priv.c
 *
 *  \brief    This file contains SPI MCAL driver internal functions
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "string.h"
#include "Spi.h"
#include "Spi_Dbg.h"
#include "Spi_Priv.h"
#include "soc.h"

/* There are static inline functions in hw_types.h file. Map them as well */
#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

#include "hw_types.h"

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void           Spi_processChCompletion(Spi_HwUnitObjType *hwUnitObj, Spi_JobResultType jobResult);
static Std_ReturnType Spi_queueJobs(Spi_SeqObjType *seqObj);
static void           Spi_scheduleJob(Spi_JobObjType *jobObj);
static void           Spi_scheduleAllJobsSyncTransmit(Spi_SeqObjType *seqObj);

static void           Spi_checkAndSetDrvState(void);
static Std_ReturnType Spi_startSeqCheck(const Spi_SeqObjType *seqObj);
#if (STD_ON == SPI_DEV_ERROR_DETECT)
static Std_ReturnType Spi_checkChConfig(const Spi_ConfigType *cfgPtr);
static Std_ReturnType Spi_checkJobConfig(const Spi_ConfigType *cfgPtr);
static Std_ReturnType Spi_checkSeqConfig(const Spi_ConfigType *cfgPtr);
#endif /* #if (STD_ON == SPI_CFG_DEV_ERROR_DETECT) */

#if (STD_ON == SPI_JOB_LOG)

static void Spi_logJob(const Spi_JobObjType *jobObj, const Spi_HwUnitObjType *hwUnitObj);
#endif /* #if (STD_ON == SPI_JOB_LOG) */
static void Spi_setJobState(Spi_SeqObjType *seqObj, Spi_JobObjType **jobObj);

static void Spi_delayIndex(void);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (STD_ON == SPI_JOB_LOG)

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED

#include "Spi_MemMap.h"

/** \brief SPI job log object */

VAR(Spi_JobLogType, SPI_VAR_ZERO_INIT) Spi_JobLogObj;

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

#include "Spi_MemMap.h"
#endif /* #if (STD_ON == SPI_JOB_LOG) */

#define SPI_START_SEC_CONST_32

#include "Spi_MemMap.h"

static CONST(uint32, SPI_CONST) Spi_HwUnitBaseAddr[5U] = {
    SOC_MIBSPI1_BASE,      /* MIBSPI1 */
    SOC_MIBSPI2_BASE,      /* MIBSPI2 */
    SOC_QSPI_ADDRSP0_BASE, /* QSPI */
    RCSS_SOC_MIBSPI1_BASE, /*RCSS_SPI1*/
    RCSS_SOC_MIBSPI2_BASE, /*RCSS_SPI2*/
};

#define SPI_STOP_SEC_CONST_32

#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED

#include "Spi_MemMap.h"

static VAR(Spi_DlcEventType, SPI_VAR_NOINIT) Spi_DlcSetEvent_t[SPI_HW_UNIT_CNT];

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_INIT_32

#include "Spi_MemMap.h"

static VAR(uint32, SPI_VAR_INIT) Spi_Initialized = FALSE;

#define SPI_STOP_SEC_VAR_INIT_32

#include "Spi_MemMap.h"
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

void Spi_hwUnitInit(Spi_HwUnitObjType *hwUnitObj)
{
    hwUnitObj->baseAddr   = Spi_getHwUnitBaseAddr(hwUnitObj->hwUnitCfg.hwUnitId);
    hwUnitObj->isQspiUnit = (uint32)FALSE;
    if (SPI_UNIT_QSPI1 == hwUnitObj->hwUnitCfg.hwUnitId)
    {
        hwUnitObj->isQspiUnit = (uint32)TRUE;
    }
    Spi_utilsInitLinkList(&hwUnitObj->jobList);

    /* Init the HW instance */
    if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
    {
        Spi_qspiInit(hwUnitObj);
    }
    else
    {
        if (Spi_Initialized != (uint32)TRUE)
        {
            Spi_DlcInit();
            Spi_Initialized = (uint32)TRUE;
        }
    }
}

void Spi_hwUnitDeInit(Spi_HwUnitObjType *hwUnitObj)
{
    /* De-Init the HW instance */
    if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
    {
        Spi_qspiDeInit(hwUnitObj);
    }
    else
    {
        Spi_DlcClose();
        Spi_Initialized = (uint32)FALSE;
    }

    Spi_utilsDeInitLinkList(&hwUnitObj->jobList);
}
/*
 * Requirements : SWS_Spi_00116, SWS_Spi_00020
 */
Std_ReturnType Spi_startSeqAsync(Spi_SeqObjType *seqObj)
{
    uint32             index              = 0U;
    Std_ReturnType     retVal             = (Std_ReturnType)E_OK;
    Spi_UtilsNode     *headNodeObj        = (Spi_UtilsNode *)NULL_PTR;
    Spi_JobObjType    *jobObj             = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType *hwUnitObj          = (Spi_HwUnitObjType *)NULL_PTR;
    uint32             Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

    /* Queue the jobs in this sequence */
    retVal = Spi_queueJobs(seqObj);

    if (((Std_ReturnType)E_OK) == retVal)
    {
        /* Check all the hardware queue and consume any pending job if the
         * hardware is free */
        for (index = 0U; index < Spi_DrvObj.maxHwUnit; index++)
        {
            Avoid_nesting_flag = 0U;
            hwUnitObj          = &Spi_DrvObj.hwUnitObj[index];
            if (SPI_HW_UNIT_OK == hwUnitObj->hwUnitResult)
            {
                /* Check if we have any job pending in the queue */
                headNodeObj        = Spi_utilsGetHeadNode(&hwUnitObj->jobList);
                Avoid_nesting_flag = 1U;
            }
            if ((Avoid_nesting_flag == 1U) && (headNodeObj != NULL_PTR))
            {
                /* Some job pending - schedule it */
                jobObj = (Spi_JobObjType *)headNodeObj->params.data;

                Spi_utilsUnLinkNodePri((&(hwUnitObj->jobList)), headNodeObj);
                hwUnitObj->curJobObj    = jobObj;
                hwUnitObj->hwUnitResult = SPI_HW_UNIT_PENDING;
                Spi_scheduleJob(jobObj);
            }

            /*
             * Check if all hardware is free so that driver can be
             * put in idle state
             */
        }
    }

    SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();

    return (retVal);
}
/*
 * Requirements : SWS_Spi_00116, SWS_Spi_00020, SWS_Spi_00134, SWS_Spi_00136
 *                SWS_Spi_00285, SWS_Spi_00286, SWS_Spi_00114
 */
Std_ReturnType Spi_startSeqSync(Spi_SeqObjType *seqObj)
{
    Std_ReturnType       retVal             = ((Std_ReturnType)E_OK);
    Spi_SeqEndNotifyType seqEndNotification = (Spi_SeqEndNotifyType)NULL_PTR;

#if (STD_ON == SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT)
    /* Check for start sequence error - needed only for concurrent support
     * on as there is no chance of jobs in pending when this is off */
    retVal = Spi_startSeqCheck(seqObj);
    /* Accept concurrent Spi_SyncTransmit(), only if the sequences to be
     * transmitted use different bus */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        uint32             index     = 0U;
        Spi_JobObjType    *jobObj    = (Spi_JobObjType *)NULL_PTR;
        Spi_HwUnitObjType *hwUnitObj = (Spi_HwUnitObjType *)NULL_PTR;
        Spi_JobType        jobId     = 0U;

        /* Check if the HW unit is free for all the jobs in this sequence.
         * If not reject the submission */
        for (index = 0U; index < seqObj->seqCfg.jobPerSeq; index++)
        {
            jobId     = seqObj->seqCfg.jobList[index];
            jobObj    = &Spi_DrvObj.jobObj[jobId];
            hwUnitObj = jobObj->hwUnitObj;
            if (SPI_HW_UNIT_OK != hwUnitObj->hwUnitResult)
            {
                /* Reject sequence */
                retVal = (Std_ReturnType)E_NOT_OK;
                break;
            }
        }
    }

#if (STD_ON == SPI_DEV_ERROR_DETECT)
    if (((Std_ReturnType)E_OK) != retVal)
    {
        Spi_reportDetError(SPI_SID_SYNC_TRANSMIT, SPI_E_SEQ_PENDING);
    }
    else
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
#endif /* #if (STD_ON == SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT) */
    {
        /* Set the states */
        seqObj->seqResult      = SPI_SEQ_PENDING;
        seqObj->numJobsPending = seqObj->seqCfg.jobPerSeq;
        Spi_DrvStatus          = SPI_BUSY;

        /* Schedule all the jobs one after another in case of Sync transfer */
        Spi_scheduleAllJobsSyncTransmit(seqObj);

        /* check if any job has previously failed or cancelled
         * and hence the sequence result is already set. So
         * don't overwrite the sequence status with OK for the
         * subsequent job */
        if (seqObj->seqResult == SPI_SEQ_PENDING)
        {
            seqObj->seqResult = SPI_SEQ_OK;
        }
        /* Notify Sequence end - should be done after scheduling */
        seqEndNotification = seqObj->seqCfg.Spi_SequenceEndNotification;
        if (NULL_PTR != seqEndNotification)
        {
            seqEndNotification();
        }

        /*
         * Check if all hardware is free so that driver can be
         * put in idle state
         */
        Spi_checkAndSetDrvState();
    }

    return (retVal);
}
#if (STD_ON == SPI_CANCEL_API)
/*
 * Requirements : SWS_Spi_00144, SWS_Spi_00145
 */
void Spi_cancelSequence(Spi_SeqObjType *seqObj)
{
    uint32               jobIndex, jobId;
    Spi_JobObjType      *jobObj             = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType   *hwUnitObj          = (Spi_HwUnitObjType *)NULL_PTR;
    Spi_SeqEndNotifyType seqEndNotification = (Spi_SeqEndNotifyType)NULL_PTR;
    Spi_JobEndNotifyType jobEndNotification = (Spi_JobEndNotifyType)NULL_PTR;
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

    /* only a pending sequence can be cancelled */
    if (SPI_SEQ_PENDING == seqObj->seqResult)
    {
        /* Cancel the sequence */
        seqObj->seqResult = SPI_SEQ_CANCELLED;

        /* Check all the jobs in the sequence and remove them if they are not
         * already started. If they are started allow the job to complete
         * in the normal way and do the clean-up in the ISR context */
        for (jobIndex = 0U; jobIndex < seqObj->seqCfg.jobPerSeq; jobIndex++)
        {
            jobId              = (uint32)seqObj->seqCfg.jobList[jobIndex];
            jobObj             = &Spi_DrvObj.jobObj[jobId];
            hwUnitObj          = jobObj->hwUnitObj;
            Avoid_nesting_flag = 0U;
            if (jobObj->jobResult == SPI_JOB_QUEUED)
            {
                /* Job is not active, remove from HW job queue */
                Spi_utilsUnLinkNodePri(&hwUnitObj->jobList, &jobObj->nodeObj);
                jobObj->seqObj->numJobsPending--;
                jobObj->jobResult  = SPI_JOB_OK;
                Avoid_nesting_flag = 1U;
            }
            /* Notify Job end */
            if ((Avoid_nesting_flag == 1U) && (NULL_PTR != jobObj->jobCfg.Spi_JobEndNotification))
            {
                jobEndNotification = jobObj->jobCfg.Spi_JobEndNotification;
                jobEndNotification();
            }
        }

        /* If all jobs of the sequence are removed, then notify sequence end
         * callback */
        if ((0U == seqObj->numJobsPending) && (NULL_PTR != seqObj->seqCfg.Spi_SequenceEndNotification))
        {
            seqEndNotification = seqObj->seqCfg.Spi_SequenceEndNotification;
            seqEndNotification();
        }
    }

    SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
}

#endif /* #if (STD_ON == SPI_CANCEL_API) */
/*
 * Requirements : SWS_Spi_00163, SWS_Spi_00118, SWS_Spi_00119, SWS_Spi_00120,
 *                SWS_Spi_00281, SWS_Spi_00283, SWS_Spi_00088, SWS_Spi_00268,
 *                SWS_Spi_00269, SWS_Spi_00270, SWS_Spi_00254, SWS_Spi_00293,
 *                SWS_Spi_00057, SWS_Spi_00075, SWS_Spi_00264, SWS_Spi_00054,
 *                SWS_Spi_00340, SWS_Spi_00071, SWS_Spi_00341, SWS_Spi_00073
 */
void Spi_processEvents(Spi_HwUnitObjType *hwUnitObj)
{
    uint32 baseAddr = 0U;
    baseAddr        = Spi_getHwUnitBaseAddr(hwUnitObj->hwUnitCfg.hwUnitId);
    if ((HW_RD_FIELD32(baseAddr + SPI_BUF_REG, SPI_BUFRXEMPTY) == 0) &&
        (hwUnitObj->hwUnitCfg.hwUnitId != SPI_UNIT_QSPI1))
    {
        Spi_delayIndex();
        Spi_IrqTxRx(hwUnitObj->hwUnitCfg.hwUnitId);
    }
}

/**
 *  \brief Returns the the HW object for the corresponding HW unit ID
 */
/*
 * Requirements : SWS_Spi_00241, SWS_Spi_00143
 */
Spi_HwUnitObjType *Spi_getHwUnitObj(Spi_HWUnitType HWUnit)
{
    uint32             hwUnitIdx      = 0U;
    uint32             hwUnitCfgFound = (uint32)FALSE;
    Spi_DriverObjType *drvObj         = &Spi_DrvObj;
    Spi_HwUnitObjType *hwUnitObj      = (Spi_HwUnitObjType *)NULL_PTR;

    /* HW unit ID may not be the index, so search for matching HW unit */
    for (hwUnitIdx = 0U; hwUnitIdx < drvObj->maxHwUnit; hwUnitIdx++)
    {
        if (drvObj->hwUnitObj[hwUnitIdx].hwUnitCfg.hwUnitId == HWUnit)
        {
            hwUnitCfgFound = (uint32)TRUE;
            break; /* Match found */
        }
    }

    if (hwUnitCfgFound != ((uint32)TRUE))
    {
        hwUnitObj = (Spi_HwUnitObjType *)NULL_PTR;
#if (STD_ON == SPI_DEV_ERROR_DETECT)
        Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_UNIT);
#endif
    }
    else
    {
        hwUnitObj = &drvObj->hwUnitObj[hwUnitIdx];
    }

    return hwUnitObj;
}

/*
 * Requirements : SWS_Spi_00151
 */
void Spi_resetDrvObj(Spi_DriverObjType *drvObj)
{
    uint32 index = 0U;

    for (index = 0U; index < SPI_MAX_CHANNELS; index++)
    {
        drvObj->channelObj[index].txBufPtr       = (Spi_DataBufferType *)NULL_PTR;
        drvObj->channelObj[index].rxBufPtr       = (Spi_DataBufferType *)NULL_PTR;
        drvObj->channelObj[index].numWordsTxRx   = 0U;
        drvObj->channelObj[index].curTxBufPtr    = (uint8 *)NULL_PTR;
        drvObj->channelObj[index].curRxBufPtr    = (uint8 *)NULL_PTR;
        drvObj->channelObj[index].curTxWords     = 0U;
        drvObj->channelObj[index].curRxWords     = 0U;
        drvObj->channelObj[index].bufWidth       = 32U;
        drvObj->channelObj[index].effTxFifoDepth = 1U;
    }
    for (index = 0U; index < SPI_MAX_JOBS; index++)
    {
        drvObj->jobObj[index].jobResult     = SPI_JOB_OK;
        drvObj->jobObj[index].seqObj        = (Spi_SeqObjType *)NULL_PTR;
        drvObj->jobObj[index].curChIdx      = 0U;
        drvObj->jobObj[index].txFifoTrigLvl = 0U;
        drvObj->jobObj[index].rxFifoTrigLvl = 0U;
        Spi_utilsInitNodeObject(&(drvObj->jobObj[index].nodeObj));
        drvObj->jobObj[index].extDevCfg = (Spi_ExternalDeviceConfigType *)NULL_PTR;
    }
    for (index = 0U; index < SPI_MAX_SEQ; index++)
    {
        drvObj->seqObj[index].seqResult      = SPI_SEQ_OK;
        drvObj->seqObj[index].numJobsPending = 0U;
    }
    for (index = 0U; index < SPI_MAX_HW_UNIT; index++)
    {
        drvObj->hwUnitObj[index].hwUnitResult = SPI_HW_UNIT_OK;
        drvObj->hwUnitObj[index].curJobObj    = (Spi_JobObjType *)NULL_PTR;
        /* Init current job to invalid job id */
        drvObj->hwUnitObj[index].curConfiguredJobId = SPI_MAX_JOBS;
        drvObj->hwUnitObj[index].lpbkEnable         = (boolean)FALSE;
    }
    drvObj->isAsynInProgress = (uint32)FALSE;
    drvObj->asyncMode        = SPI_POLLING_MODE;
    drvObj->maxChannels      = 0U;
    drvObj->maxJobs          = 0U;
    drvObj->maxSeq           = 0U;
    drvObj->maxHwUnit        = 0U;

#if (STD_ON == SPI_JOB_LOG)
    (void)memset(&Spi_JobLogObj, 0, sizeof(Spi_JobLogObj));
#endif /* #if (STD_ON == SPI_JOB_LOG) */
}

/*
 * Requirements : SWS_Spi_00065, SWS_Spi_00003, SWS_Spi_00004, SWS_Spi_00237,
 *                SWS_Spi_00238, SWS_Spi_00031, SWS_Spi_00032
 */
#if (STD_ON == SPI_DEV_ERROR_DETECT)
Std_ReturnType Spi_checkConfig(const Spi_ConfigType *cfgPtr)
{
    Std_ReturnType retVal = E_OK;

    retVal = Spi_checkChConfig(cfgPtr);
    if (((Std_ReturnType)E_OK) == retVal)
    {
        retVal = Spi_checkJobConfig(cfgPtr);
    }
    if (((Std_ReturnType)E_OK) == retVal)
    {
        retVal = Spi_checkSeqConfig(cfgPtr);
    }

    return (retVal);
}

#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */

void Spi_copyConfig(Spi_DriverObjType *drvObj, const Spi_ConfigType *cfgPtr)
{
    uint32          index  = 0U;
    Spi_JobObjType *jobObj = (Spi_JobObjType *)NULL_PTR;

    drvObj->maxChannels  = cfgPtr->maxChannels;
    drvObj->maxJobs      = cfgPtr->maxJobs;
    drvObj->maxSeq       = cfgPtr->maxSeq;
    drvObj->maxHwUnit    = cfgPtr->maxHwUnit;
    drvObj->maxExtDevCfg = cfgPtr->maxExtDevCfg;
    drvObj->Spi_MaxDlcs  = cfgPtr->Spi_MaxDlcs;
    for (index = 0U; index < cfgPtr->maxExtDevCfg; index++)
    {
        (void)memcpy(&drvObj->extDevCfg[index], &cfgPtr->extDevCfg[index], sizeof(Spi_ExternalDeviceConfigType));
    }
    for (index = 0U; index < cfgPtr->maxHwUnit; index++)
    {
        (void)memcpy(&drvObj->hwUnitObj[index].hwUnitCfg, &cfgPtr->hwUnitCfg[index], sizeof(Spi_HwUnitConfigType));
        /* Init current job to invalid job id */
        drvObj->hwUnitObj[index].curConfiguredJobId = drvObj->maxJobs;
    }

    for (index = 0U; index < cfgPtr->maxChannels; index++)
    {
        (void)memcpy(&drvObj->channelObj[index].chCfg, &cfgPtr->channelCfg[index], sizeof(Spi_ChannelConfigType));
    }
    for (index = 0U; index < cfgPtr->maxJobs; index++)
    {
        jobObj = &drvObj->jobObj[index];
        (void)memcpy(&jobObj->jobCfg, &cfgPtr->jobCfg[index], sizeof(Spi_JobConfigType));

        jobObj->hwUnitObj = Spi_getHwUnitObj(jobObj->jobCfg.hwUnitId);

        jobObj->extDevCfg = &drvObj->extDevCfg[jobObj->jobCfg.externalDeviceCfgId];
    }
    for (index = 0U; index < cfgPtr->maxSeq; index++)
    {
        (void)memcpy(&drvObj->seqObj[index].seqCfg, &cfgPtr->seqCfg[index], sizeof(Spi_SeqConfigType));
    }
}

uint32 Spi_getHwUnitBaseAddr(Spi_HWUnitType hwUnitId)
{
    return (Spi_HwUnitBaseAddr[hwUnitId]);
}

uint32 Spi_getDataWidthBitMask(uint32 dataWidth)
{
    uint32 idx         = 0U;
    uint32 fifoBitMask = 0x0U;

    for (idx = 0U; idx < dataWidth; idx++)
    {
        fifoBitMask |= ((uint32)1U << idx);
    }

    return fifoBitMask;
}

static void Spi_processChCompletion(Spi_HwUnitObjType *hwUnitObj, Spi_JobResultType jobResult)
{
    Spi_JobObjType *jobObj;
    jobObj = hwUnitObj->curJobObj;

    /* Channel completed */
    jobObj->curChIdx++;
    if (jobObj->curChIdx == jobObj->jobCfg.channelPerJob)
    {
        /*
         * Job completed
         */
        Spi_processJobCompletion(jobObj, hwUnitObj, jobResult);
    }
    else
    {
        /* Start the next channel */

        uint16_least HW_Inst_Nr_u16; /* Instance of the SPI Hw */
        uint16_least SeqIdAt_u16;
        SeqIdAt_u16                                = jobObj->seqObj->seqCfg.seqId;
        HW_Inst_Nr_u16                             = Spi_DrvObj.hwUnitObj[SeqIdAt_u16].hwUnitCfg.hwUnitId;
        Spi_DlcSetEvent_t[HW_Inst_Nr_u16].JobID_u8 = jobObj->jobCfg.jobId;

        Spi_DlcSetEvent_t[HW_Inst_Nr_u16].Event_u8 = (uint8)SPI_DLC_EV_ASYNCTX;

        (void)Spi_DlcSetEvent(&Spi_DlcSetEvent_t[HW_Inst_Nr_u16]);
    }
}

void Spi_processJobCompletion(Spi_JobObjType *jobObj, Spi_HwUnitObjType *hwUnitObj, Spi_JobResultType jobResult)
{
    Spi_UtilsNode       *headNodeObj        = (Spi_UtilsNode *)NULL_PTR;
    Spi_SeqObjType      *seqObj             = (Spi_SeqObjType *)NULL_PTR;
    Spi_SeqEndNotifyType seqEndNotification = (Spi_SeqEndNotifyType)NULL_PTR;
    Spi_JobEndNotifyType jobEndNotification = (Spi_JobEndNotifyType)NULL_PTR;

    seqObj = jobObj->seqObj;

    hwUnitObj->curJobObj = (Spi_JobObjType *)NULL_PTR;

    seqObj->numJobsPending--;
    jobObj->jobResult  = jobResult;
    jobEndNotification = jobObj->jobCfg.Spi_JobEndNotification;

    /* Check if sequence is complete */
    if (0U == seqObj->numJobsPending)
    {
        /* check if any job has previously failed or cancelled
         * and hence the sequence result is already set. So
         * don't overwrite the sequence status with OK for the
         * subsequent job */
        if (seqObj->seqResult == SPI_SEQ_PENDING)
        {
            seqObj->seqResult = SPI_SEQ_OK;
        }

        seqEndNotification = seqObj->seqCfg.Spi_SequenceEndNotification;
    }

    /* Check if any new job is pending */
    headNodeObj = Spi_utilsGetHeadNode(&hwUnitObj->jobList);
    if (headNodeObj != NULL_PTR)
    {
        Spi_JobObjType *nextJobObj;
        /* Some job pending - schedule it */

        nextJobObj = (Spi_JobObjType *)headNodeObj->params.data;
        Spi_utilsUnLinkNodePri((&(hwUnitObj->jobList)), headNodeObj);

        hwUnitObj->curJobObj    = nextJobObj;
        hwUnitObj->hwUnitResult = SPI_HW_UNIT_PENDING;

        Spi_scheduleJob(nextJobObj);
    }
    else
    {
        /* No new job scheduled, hardware is free!! */
        hwUnitObj->hwUnitResult = SPI_HW_UNIT_OK;

        /*
         * Check if all hardware is free so that driver can be
         * put in idle state
         */
        Spi_checkAndSetDrvState();
        Spi_AsyncIntrDisable(hwUnitObj->baseAddr);
    }

    /* Notify Job end - should be done after scheduling */
    if (NULL_PTR != jobEndNotification)
    {
        jobEndNotification();
    }

    /* Notify Sequence end - should be done after scheduling */
    if (NULL_PTR != seqEndNotification)
    {
        seqEndNotification();
    }
}
/*
 * Requirements : SWS_Spi_00059, SWS_Spi_00014, SWS_Spi_00194, SWS_Spi_00081,
 *                SWS_Spi_00086, SWS_Spi_00055, SWS_Spi_00122, SWS_Spi_00123,
 *                SWS_Spi_00124, SWS_Spi_00125, SWS_Spi_00126, SWS_Spi_00127,
 *                SWS_Spi_00282
 */
static Std_ReturnType Spi_queueJobs(Spi_SeqObjType *seqObj)
{
    uint32             index       = 0U;
    uint8              currSeqId   = 0U;
    Std_ReturnType     retVal      = E_OK;
    Spi_JobType        jobId       = 0U;
    Spi_JobObjType    *jobObj      = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType *hwUnitObj   = (Spi_HwUnitObjType *)NULL_PTR;
    Spi_UtilsParams    utilsParams = (Spi_UtilsParams){0};

    /* Check for start sequence error */
    retVal = Spi_startSeqCheck(seqObj);
    if (((Std_ReturnType)E_OK) == retVal)
    {
        /* Queue all the jobs to the respective hardware queue */
        for (index = 0U; index < seqObj->seqCfg.jobPerSeq; index++)
        {
            jobId  = seqObj->seqCfg.jobList[index];
            jobObj = &Spi_DrvObj.jobObj[jobId];

            hwUnitObj = jobObj->hwUnitObj;

            /* Get current sequence ID which is in progress for this HW unit */
            if (hwUnitObj->curJobObj == NULL_PTR)
            {
                /* No sequence in progress. Give invalid ID */
                currSeqId = SPI_MAX_SEQ;
            }
            else
            {
                currSeqId = hwUnitObj->curJobObj->seqObj->seqCfg.seqId;
            }

            /* Queue the job to the hardware queue */

            jobObj->seqObj               = seqObj;
            jobObj->jobResult            = SPI_JOB_QUEUED;
            utilsParams.data             = jobObj;
            utilsParams.priority         = (uint32)jobObj->jobCfg.jobPriority;
            utilsParams.seqId            = seqObj->seqCfg.seqId;
            utilsParams.seqInterruptible = seqObj->seqCfg.seqInterruptible;
            Spi_utilsLinkNodePri(&hwUnitObj->jobList, &jobObj->nodeObj, &utilsParams, currSeqId);
        }

        /* Set the states */
        seqObj->seqResult           = SPI_SEQ_PENDING;
        seqObj->numJobsPending      = seqObj->seqCfg.jobPerSeq;
        Spi_DrvObj.isAsynInProgress = (uint32)TRUE;
        Spi_DrvStatus               = SPI_BUSY;
    }

    return (retVal);
}

/* Design : SPI_DesignId_003 */
/*
 * Requirements : SWS_Spi_00157
 */
static void Spi_scheduleJob(Spi_JobObjType *jobObj)
{
    Spi_HwUnitObjType *hwUnitObj;
    hwUnitObj = jobObj->hwUnitObj;

    /* Set the states */
    jobObj->jobResult      = SPI_JOB_PENDING;
    jobObj->curChIdx       = 0U;
    jobObj->IsCmd          = FALSE;
    jobObj->IsAdd          = FALSE;
    jobObj->IsData         = FALSE;
    jobObj->wordNum        = 0;
    jobObj->pointerShifter = 0;
    /* Log the job */
#if (STD_ON == SPI_JOB_LOG)

    Spi_logJob(jobObj, hwUnitObj);
#endif /* #if (STD_ON == SPI_JOB_LOG) */

    /* Configure the hardware if previously configured job ID is different */
    if (hwUnitObj->curConfiguredJobId != jobObj->jobCfg.jobId)
    {
        if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
        {
            Spi_qspiConfigJobAsync(hwUnitObj, jobObj);
        }
        hwUnitObj->curConfiguredJobId = jobObj->jobCfg.jobId;
    }
    if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
    {
        Spi_qspiXferJobAsync(hwUnitObj, jobObj, Spi_DrvObj.channelObj);
    }
    else
    {
        /* Start the first channel */
        /*Configure and start transmit*/
        uint16_least HW_Inst_Nr_u16; /* Instance of the SPI Hw */
        uint16_least SeqIdAt_u16;
        SeqIdAt_u16                                = jobObj->seqObj->seqCfg.seqId;
        HW_Inst_Nr_u16                             = Spi_DrvObj.hwUnitObj[SeqIdAt_u16].hwUnitCfg.hwUnitId;
        Spi_DlcSetEvent_t[HW_Inst_Nr_u16].JobID_u8 = jobObj->jobCfg.jobId;

        Spi_DlcSetEvent_t[HW_Inst_Nr_u16].Event_u8 = (uint8)SPI_DLC_EV_ASYNCTX;

        (void)Spi_DlcSetEvent(&Spi_DlcSetEvent_t[HW_Inst_Nr_u16]);
    }
}

static void Spi_scheduleAllJobsSyncTransmit(Spi_SeqObjType *seqObj)
{
    uint32               index;
    Spi_JobObjType      *jobObj = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType   *hwUnitObj;
    Spi_JobType          jobId;
    Spi_JobResultType    jobResult;
    Spi_JobEndNotifyType jobEndNotification = (Spi_JobEndNotifyType)NULL_PTR;

    Spi_setJobState(seqObj, &jobObj);

    for (index = 0U; index < seqObj->seqCfg.jobPerSeq; index++)
    {
        jobId  = seqObj->seqCfg.jobList[index];
        jobObj = &Spi_DrvObj.jobObj[jobId];
        /* Queue the job to the hardware queue */
        jobObj->seqObj = seqObj;
        /* Set the states */
        jobObj->jobResult = SPI_JOB_PENDING;

        jobObj->curChIdx = 0U;
        hwUnitObj        = jobObj->hwUnitObj;

#if (STD_ON == SPI_JOB_LOG)
        /* Log the job */
        Spi_logJob(jobObj, hwUnitObj);
#endif /* #if (STD_ON == SPI_JOB_LOG) */

        hwUnitObj->curJobObj    = jobObj;
        hwUnitObj->hwUnitResult = SPI_HW_UNIT_PENDING;

        /* Configure the hardware if previously configured job ID is
         * different */
        if (hwUnitObj->curConfiguredJobId != jobObj->jobCfg.jobId)
        {
            if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
            {
                Spi_qspiConfigJob(hwUnitObj, jobObj);
            }

            hwUnitObj->curConfiguredJobId = jobObj->jobCfg.jobId;
        }
        if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
        {
            jobResult = Spi_qspiXferJob(hwUnitObj, jobObj, Spi_DrvObj.channelObj);
        }
        else
        {
            uint16_least HW_Inst_Nr_u16; /* Instance of the SPI Hw */
            uint16_least SeqIdAt_u16;
            SeqIdAt_u16                                = jobObj->seqObj->seqCfg.seqId;
            HW_Inst_Nr_u16                             = Spi_DrvObj.hwUnitObj[SeqIdAt_u16].hwUnitCfg.hwUnitId;
            Spi_DlcSetEvent_t[HW_Inst_Nr_u16].JobID_u8 = jobObj->jobCfg.jobId;

            Spi_DlcSetEvent_t[HW_Inst_Nr_u16].Event_u8 = (uint8)SPI_DLC_EV_SYNCTX;

            jobResult = Spi_DlcSetEvent(&Spi_DlcSetEvent_t[HW_Inst_Nr_u16]);
        }

        hwUnitObj->curJobObj = (Spi_JobObjType *)NULL_PTR;

        hwUnitObj->hwUnitResult = SPI_HW_UNIT_OK;

        Spi_delayIndex();

        if (seqObj->numJobsPending > 0U)
        {
            seqObj->numJobsPending--;
        }
        jobObj->jobResult  = jobResult;
        jobEndNotification = jobObj->jobCfg.Spi_JobEndNotification;
        /* Notify Job end  */
        if (NULL_PTR != jobEndNotification)
        {
            jobEndNotification();
        }

        /* Fail the sequence if job fails */
        if (SPI_JOB_FAILED == jobResult)
        {
            seqObj->seqResult = SPI_SEQ_FAILED;
        }
    }
}

static void Spi_setJobState(Spi_SeqObjType *seqObj, Spi_JobObjType **jobObj)
{
    Spi_JobType jobId = 0U;
    uint32      index = 0U;
    /* Set state of all jobs in sequence to queued */
    for (index = 0U; index < seqObj->seqCfg.jobPerSeq; index++)
    {
        jobId   = seqObj->seqCfg.jobList[index];
        *jobObj = &Spi_DrvObj.jobObj[jobId];

        /* Queue the job to the hardware queue */

        (*jobObj)->seqObj = seqObj;
        /* Set the states */
        (*jobObj)->jobResult = SPI_JOB_QUEUED;
    }
}

static void Spi_delayIndex(void)
{
    volatile uint32 delayIndex = 0U;
    for (delayIndex = 0U; delayIndex < (uint32)50000U; (delayIndex = (delayIndex + 1U)))
    {
        /*Do nothing*/
    }
}

static void Spi_checkAndSetDrvState(void)
{
    uint32 hwUnitIdx, isSomeHwBusy = 0U;

    /* Since check is done across HW unit, all interrupts
     * are disabled */
    SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

    isSomeHwBusy = (uint32)FALSE;
    for (hwUnitIdx = 0U; hwUnitIdx < Spi_DrvObj.maxHwUnit; hwUnitIdx++)
    {
        if (Spi_DrvObj.hwUnitObj[hwUnitIdx].hwUnitResult == SPI_HW_UNIT_PENDING)
        {
            isSomeHwBusy = (uint32)TRUE;
            break;
        }
    }

    if ((((uint32)FALSE)) == isSomeHwBusy)
    {
        Spi_DrvObj.isAsynInProgress = (uint32)FALSE;
        Spi_DrvStatus               = SPI_IDLE;
    }

    SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
}

static Std_ReturnType Spi_startSeqCheck(const Spi_SeqObjType *seqObj)
{
    uint32          index  = 0U;
    Std_ReturnType  retVal = (Std_ReturnType)E_OK;
    Spi_JobObjType *jobObj = (Spi_JobObjType *)NULL_PTR;
    Spi_JobType     jobId  = 0U;

    /* check all jobs if they are allowed to be queued */
    for (index = 0U; index < seqObj->seqCfg.jobPerSeq; index++)
    {
        jobId  = seqObj->seqCfg.jobList[index];
        jobObj = &Spi_DrvObj.jobObj[jobId];
        if (SPI_JOB_PENDING == jobObj->jobResult)
        {
            /* the sequence is rejected due to common used jobs */
            retVal = (Std_ReturnType)E_NOT_OK;
            break;
        }
    }

    return (retVal);
}

#if (STD_ON == SPI_DEV_ERROR_DETECT)
static Std_ReturnType Spi_checkChConfig(const Spi_ConfigType *cfgPtr)
{
    uint32         index  = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    for (index = 0U; index < cfgPtr->maxChannels; index++)
    {
        /* ID is used as index, can't exceed array size */
        if (cfgPtr->channelCfg[index].channelId >= cfgPtr->maxChannels)
        {
            Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_CHANNEL);
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return (retVal);
}

static Std_ReturnType Spi_checkJobConfig(const Spi_ConfigType *cfgPtr)
{
    uint32         index  = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    for (index = 0U; index < cfgPtr->maxJobs; index++)
    {
        if ((cfgPtr->jobCfg[index].jobId >= cfgPtr->maxJobs) || (cfgPtr->jobCfg[index].channelPerJob == 0U) ||
            (cfgPtr->jobCfg[index].channelPerJob > SPI_MAX_CHANNELS_PER_JOB) ||
            (cfgPtr->jobCfg[index].externalDeviceCfgId >= cfgPtr->maxExtDevCfg))
        {
            Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_JOB);
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }

    return (retVal);
}

static Std_ReturnType Spi_checkSeqConfig(const Spi_ConfigType *cfgPtr)
{
    uint32         index  = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    for (index = 0U; index < cfgPtr->maxSeq; index++)
    {
        /* ID is used as index, can't exceed array size */
        if ((cfgPtr->seqCfg[index].seqId >= cfgPtr->maxSeq) || (cfgPtr->seqCfg[index].jobPerSeq == 0U) ||
            (cfgPtr->seqCfg[index].jobPerSeq > SPI_MAX_JOBS_PER_SEQ))
        {
            Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_SEQ);
            retVal = (Std_ReturnType)E_NOT_OK;
        }
    }
    return (retVal);
}

#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */

#if (STD_ON == SPI_JOB_LOG)
static void Spi_logJob(const Spi_JobObjType *jobObj, const Spi_HwUnitObjType *hwUnitObj)
{
    Spi_JobLogEntryType *logEntry = (Spi_JobLogEntryType *)NULL_PTR;

    logEntry            = &Spi_JobLogObj.logEntry[Spi_JobLogObj.logIndex];
    logEntry->timeStamp = 0U;

    logEntry->jobId = jobObj->jobCfg.jobId;

    logEntry->seqId    = jobObj->seqObj->seqCfg.seqId;
    logEntry->hwUnitId = hwUnitObj->hwUnitCfg.hwUnitId;

    /* Move to next entry */
    Spi_JobLogObj.logIndex++;
    Spi_JobLogObj.totalLog++;
    if (Spi_JobLogObj.logIndex >= SPI_MAX_JOB_LOG)
    {
        Spi_JobLogObj.logIndex = 0U;
    }
}

#endif /* #if (STD_ON == SPI_JOB_LOG) */

#if (STD_ON == SPI_REGISTER_READBACK_API)

FUNC(Std_ReturnType, SPI_CODE)
Spi_HWRegisterReadback(Spi_HWUnitType HWUnit, P2VAR(Spi_RegisterReadbackType, AUTOMATIC, SPI_APPL_DATA) RegRbPtr)
{
    Spi_HwUnitObjType *hwUnitObj = (Spi_HwUnitObjType *)NULL_PTR;
    Std_ReturnType     retVal    = ((Std_ReturnType)E_OK);

    (void)memset(RegRbPtr, 0, sizeof(Spi_RegisterReadbackType));

    /* HW unit ID may not be the index, so search for matching HW unit */
    hwUnitObj = Spi_getHwUnitObj(HWUnit);
    if (NULL_PTR != hwUnitObj)
    {
        if (((uint32)TRUE) == hwUnitObj->isQspiUnit)
        {
            Spi_qspiRegReadback(hwUnitObj, RegRbPtr);
        }
        else
        {
            Spi_DlcRegisterRdbk(HWUnit, RegRbPtr);
        }
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    return (retVal);
}
#endif /* #if (STD_ON == SPI_CFG_REGISTER_READBACK_API) */

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
