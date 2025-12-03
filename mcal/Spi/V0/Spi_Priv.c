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
 *  \file     Spi_Priv.c
 *
 *  \brief    This file contains SPI MCAL driver internal functions
 *
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#include "Spi.h"
#include "Spi_Dbg.h"
#include "Spi_Priv.h"
#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */
/*                           Macros & Typedefs                      */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                         Structures and Enums                     */
/* ================================================================ */

/** \brief SPI Channel PC Configuration struct declaration */
extern const struct Spi_ChannelConfigType_PC_s Spi_ChannelConfig_PC[SPI_MAX_CHANNELS];

/** \brief SPI Job PC Configuration struct declaration */
extern const struct Spi_JobConfigType_PC_s Spi_JobConfig_PC[SPI_MAX_JOBS];

/** \brief SPI Sequence PC Configuration struct declaration */
extern const struct Spi_SeqConfigType_PC_s Spi_SeqConfig_PC[SPI_MAX_SEQ];
/* ================================================================ */
/*                 Internal Function Declarations                   */
/* ================================================================ */
static void Spi_processJobCompletion(Spi_JobObjType *jobObj, Spi_HwUnitObjType *hwUnitObj, Spi_JobResultType jobResult);

static Std_ReturnType Spi_queueJobs(Spi_SeqObjType *seqObj);
static void           Spi_scheduleJob(Spi_JobObjType *jobObj);
static void           Spi_scheduleAllJobsSyncTransmit(Spi_SeqObjType *seqObj);

static void           Spi_checkAndSetDrvState(void);
static Std_ReturnType Spi_startSeqCheck(const Spi_SeqObjType *seqObj);
#if (STD_ON == SPI_DEV_ERROR_DETECT)
static Std_ReturnType Spi_checkChConfig(const Spi_ConfigType *cfgPtr);
static Std_ReturnType Spi_checkJobConfig(const Spi_ConfigType *cfgPtr);
static Std_ReturnType Spi_checkSeqConfig(const Spi_ConfigType *cfgPtr);
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */

#if (STD_ON == SPI_JOB_LOG)
static void Spi_logJob(const Spi_JobObjType *jobObj, const Spi_HwUnitObjType *hwUnitObj);
#endif /* #if (STD_ON == SPI_JOB_LOG) */

static void Spi_startSeqAsync_conditions(void);
static void Spi_cancelSequence_conditions(Spi_SeqObjType *seqObj);
static void Spi_copyConfig_MaxSeq(Spi_DriverObjType *drvObj, const Spi_ConfigType *cfgPtr);
/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

#if (STD_ON == SPI_JOB_LOG)
#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"
/** \brief SPI job log object */
VAR(Spi_JobLogType, SPI_VAR_CLEARED) Spi_JobLogObj;
#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"
#endif /* #if (STD_ON == SPI_JOB_LOG) */

/* ================================================================ */
/*                          Function Definitions                    */
/* ================================================================ */

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

void Spi_hwUnitInit(Spi_HwUnitObjType *hwUnitObj)
{
    hwUnitObj->baseAddr = Spi_getHwUnitBaseAddr(hwUnitObj->hwUnitCfg.hwUnitId);

    Spi_utilsInitLinkList(&hwUnitObj->jobList);

    /* Init the HW instance */
    Spi_mcspiInit(hwUnitObj);

    /* copy dma mode flag */
    hwUnitObj->enableDmaMode = hwUnitObj->hwUnitCfg.enableDmaMode;

#if (STD_ON == SPI_DMA_ENABLE)

    /* Copy DMA Tx and Rx Handle IDs */
    hwUnitObj->dmaTxHandlerID = hwUnitObj->hwUnitCfg.dmaTxHandlerID;
    hwUnitObj->dmaRxHandlerID = hwUnitObj->hwUnitCfg.dmaRxHandlerID;

    if (TRUE == hwUnitObj->enableDmaMode)
    {
        Spi_TxRxMode txrxMode = SPI_TX_RX_MODE_TX_ONLY;
        for (uint8 idx = 0; idx < Spi_DrvObj.maxJobs; idx++)
        {
            if ((Spi_DrvObj.jobObj[idx].hwUnitObj->baseAddr == hwUnitObj->baseAddr) &&
                (Spi_DrvObj.jobObj[idx].extDevCfg->mcspi.txRxMode == SPI_TX_RX_MODE_BOTH))
            {
                txrxMode = SPI_TX_RX_MODE_BOTH;
                break;
            }
        }

        /* Configure SPI DMA with initialization of all channels */
        if (Spi_dmaChInit(&Spi_DrvObj, hwUnitObj, txrxMode) == MCAL_SystemP_SUCCESS)
        {
            /* Check if DMA Enabled HwUnit reaches bounds and increment */
            if (Spi_DrvObj.dmaEnableHwIndx++ == SPI_MAX_HW_DMA_UNIT)
            {
#if (STD_ON == SPI_DEV_ERROR_DETECT)
                Spi_reportDetError(SPI_SID_INIT, SPI_E_PARAM_CHANNEL);
#endif
            }
        }
    }
#endif /* #if (STD_ON == SPI_DMA_ENABLE) */
}

void Spi_hwUnitDeInit(Spi_HwUnitObjType *hwUnitObj)
{
    /* De-Init the HW instance */
    Spi_mcspiDeInit(hwUnitObj);

    /* Free Job head and tail pointer link */
    Spi_utilsDeInitLinkList(&hwUnitObj->jobList);
}

Std_ReturnType Spi_startSeqAsync(Spi_SeqObjType *seqObj)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

    /* Queue the jobs in this sequence */
    retVal = Spi_queueJobs(seqObj);

    if (((Std_ReturnType)E_OK) == retVal)
    {
        /* Check all the hardware queue and consume any pending job if
         * the hardware is free */
        Spi_startSeqAsync_conditions();
    }

    SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();

    return (retVal);
}

static void Spi_startSeqAsync_conditions(void)
{
    Spi_UtilsNode     *headNodeObj = (Spi_UtilsNode *)NULL_PTR;
    Spi_JobObjType    *jobObj      = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType *hwUnitObj   = (Spi_HwUnitObjType *)NULL_PTR;
    uint8              index       = 0U;

    for (index = 0U; index < Spi_DrvObj.maxHwUnit; index++)
    {
        hwUnitObj = &Spi_DrvObj.hwUnitObj[index];
        if (SPI_HW_UNIT_OK == hwUnitObj->hwUnitResult)
        {
            /* Check if we have any job pending in the queue */
            headNodeObj = Spi_utilsGetHeadNode(&hwUnitObj->jobList);
            if (headNodeObj != NULL_PTR)
            {
                /* Some job pending - schedule it */
                jobObj = (Spi_JobObjType *)headNodeObj->params.data;
                Spi_utilsUnLinkNodePri((&(hwUnitObj->jobList)), headNodeObj);
                hwUnitObj->curJobObj    = jobObj;
                hwUnitObj->hwUnitResult = SPI_HW_UNIT_PENDING;
                Spi_scheduleJob(jobObj);
            }
        }
    }
}

Std_ReturnType Spi_startSeqSync(Spi_SeqObjType *seqObj)
{
    Std_ReturnType       retVal             = ((Std_ReturnType)E_OK);
    Spi_SeqEndNotifyType seqEndNotification = (Spi_SeqEndNotifyType)NULL_PTR;

#if (STD_ON == SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT)
    /* Check for start sequence error - needed only for concurrent
     * support on as there is no chance of jobs in pending when this
     *     is off */
    retVal = Spi_startSeqCheck(seqObj);
    /* Accept concurrent Spi_SyncTransmit(), only if the sequences to
     * be transmitted use different bus */
    if (((Std_ReturnType)E_OK) == retVal)
    {
        uint32             index;
        Spi_JobObjType    *jobObj;
        Spi_HwUnitObjType *hwUnitObj;
        Spi_JobType        jobId;

        /* Check if the HW unit is free for all the jobs in this
         * sequence. If not reject the submission */
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

    if (((Std_ReturnType)E_OK) != retVal)
    {
        Spi_reportDetRuntimeError(SPI_SID_SYNC_TRANSMIT, SPI_E_SEQ_PENDING);
    }
    else
#endif /* #if (STD_ON == SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT) */
    {
        /* Set the states */
        seqObj->seqResult      = SPI_SEQ_PENDING;
        seqObj->numJobsPending = seqObj->seqCfg.jobPerSeq;
        Spi_DrvStatus          = SPI_BUSY;

        /* Schedule all the jobs one after another in case of Sync
         *  transfer */
        Spi_scheduleAllJobsSyncTransmit(seqObj);

        /* check if any job has previously failed or cancelled
         * and hence the sequence result is already set. So
         * don't overwrite the sequence status with OK for the
         * subsequent job */
        if (seqObj->seqResult == SPI_SEQ_PENDING)
        {
            seqObj->seqResult = SPI_SEQ_OK;
        }

#ifdef SPI_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
#endif

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

void Spi_cancelSequence(Spi_SeqObjType *seqObj)
{
    Spi_SeqEndNotifyType seqEndNotification = (Spi_SeqEndNotifyType)NULL_PTR;
    SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();

    /* only a pending sequence can be cancelled */
    if (SPI_SEQ_PENDING == seqObj->seqResult)
    {
        /* Cancel the sequence */
        seqObj->seqResult = SPI_SEQ_CANCELLED;

        /* Check all the jobs in the sequence and remove them if they
         * are not already started. If they are started allow the job
         * to complete in the normal way and do the clean-up in the
         * ISR context */
        Spi_cancelSequence_conditions(seqObj);

        /* If all jobs of the sequence are removed, then notify
         * sequence end callback */
        if ((0U == seqObj->numJobsPending) && (NULL_PTR != (void *)seqObj->seqCfg.Spi_SequenceEndNotification))
        {
            seqEndNotification = seqObj->seqCfg.Spi_SequenceEndNotification;
            seqEndNotification();
        }
    }

    SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
}

static void Spi_cancelSequence_conditions(Spi_SeqObjType *seqObj)
{
    uint32               jobIndex           = 0U;
    Spi_JobType          jobId              = 0U;
    Spi_JobObjType      *jobObj             = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType   *hwUnitObj          = (Spi_HwUnitObjType *)NULL_PTR;
    Spi_JobEndNotifyType jobEndNotification = (Spi_JobEndNotifyType)NULL_PTR;

    for (jobIndex = 0U; jobIndex < seqObj->seqCfg.jobPerSeq; jobIndex++)
    {
        jobId     = seqObj->seqCfg.jobList[jobIndex];
        jobObj    = &Spi_DrvObj.jobObj[jobId];
        hwUnitObj = jobObj->hwUnitObj;
        if (jobObj->jobResult == SPI_JOB_QUEUED)
        {
            /* Job is not active, remove from HW job queue */
            Spi_utilsUnLinkNodePri(&hwUnitObj->jobList, &jobObj->nodeObj);
            jobObj->seqObj->numJobsPending--;
            jobObj->jobResult = SPI_JOB_OK;
            /* Notify Job end */
            if (NULL_PTR != (void *)jobObj->jobCfg.Spi_JobEndNotification)
            {
                jobEndNotification = jobObj->jobCfg.Spi_JobEndNotification;
                jobEndNotification();
            }
        }
    }
}

#endif /* #if (STD_ON == SPI_CANCEL_API) */

void Spi_processEvents(Spi_HwUnitObjType *hwUnitObj)
{
    Spi_ChannelType     chId      = 0U;
    Spi_ChannelObjType *chObj     = (Spi_ChannelObjType *)NULL_PTR;
    Spi_JobObjType     *jobObj    = (Spi_JobObjType *)NULL_PTR;
    Spi_JobResultType   jobResult = SPI_JOB_OK;

    if (NULL_PTR != hwUnitObj)
    {
        /* Get the current job/sequence */
        jobObj = hwUnitObj->curJobObj;
        if (jobObj == NULL_PTR)
        {
            /* Incase of McSPI, RX interrupt could happen after WCNT
             * interrupt Hence this interrupt could happen after all the
             * data is read and states moved. So don't report DET error.*/
            Spi_mcspiClearAllIrqStatus(hwUnitObj->baseAddr);
        }
        else
        {
            chId = jobObj->jobCfg.channelList[jobObj->curChIdx];
            /* Each port is considered as one controller */
            chObj     = Spi_getCurrChannelObj(chId);
            jobResult = Spi_mcspiContinueTxRx(hwUnitObj, jobObj, chObj);

            if (SPI_JOB_PENDING != jobResult)
            {
                /*
                 * Channel completed or failed!!
                 *
                 * Caution: Since there is no channel status macro, we are
                 * reusing the job status macros. Also this can be
                 * directly used to assign to job status
                 */
                Spi_processChCompletion(hwUnitObj, jobResult);
            }
            /* Else Job is still pending. Do nothing, wait for next
             * interrupt */
        }
    }
}

/**
 *  \brief Returns the the HW object for the corresponding HW unit ID
 */

Spi_HwUnitObjType *Spi_getHwUnitObj(Spi_HWUnitType HWUnit)
{
    uint32             hwUnitIdx      = 0U;
    uint32             hwUnitCfgFound = (uint32)FALSE;
    Spi_DriverObjType *drvObj         = &Spi_DrvObj;
    Spi_HwUnitObjType *hwUnitObj      = (Spi_HwUnitObjType *)NULL_PTR;

    /* HW unit ID may not be the index, so search
     * for matching HW unit */
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

    return (hwUnitObj);
}

void Spi_resetDrvObj(Spi_DriverObjType *drvObj)
{
    uint32 index = 0U;
#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
    uint32 ibIndex = 0U;
#endif

    for (index = 0U; index < SPI_MAX_CHANNELS; index++)
    {
        drvObj->channelObj[index].txBufPtr = (const Spi_DataBufferType *)NULL_PTR;
        drvObj->channelObj[index].rxBufPtr = (Spi_DataBufferType *)NULL_PTR;
        ;
        drvObj->channelObj[index].numWordsTxRx     = 0U;
        drvObj->channelObj[index].curTxBufPtr      = (const Spi_DataBufferType *)NULL_PTR;
        drvObj->channelObj[index].curRxBufPtr      = (uint8 *)NULL_PTR;
        drvObj->channelObj[index].curTxWords       = 0U;
        drvObj->channelObj[index].curRxWords       = 0U;
        drvObj->channelObj[index].bufWidth         = 4U;
        drvObj->channelObj[index].effTxFifoDepth   = 1U;
        drvObj->channelObj[index].dataWidthBitMask = 0xFFFFFFFFU;
#if ((SPI_CHANNELBUFFERS == SPI_IB) || (SPI_CHANNELBUFFERS == SPI_IB_EB))
        for (ibIndex = 0U; ibIndex < SPI_IB_MAX_LENGTH; ibIndex++)
        {
            drvObj->channelObj[index].txIb[ibIndex] = 0U;
            drvObj->channelObj[index].rxIb[ibIndex] = 0U;
        }
#endif
    }
    for (index = 0U; index < SPI_MAX_JOBS; index++)
    {
        drvObj->jobObj[index].jobResult     = SPI_JOB_OK;
        drvObj->jobObj[index].seqObj        = (Spi_SeqObjType *)NULL_PTR;
        drvObj->jobObj[index].curChIdx      = 0U;
        drvObj->jobObj[index].txFifoTrigLvl = 0U;
        drvObj->jobObj[index].rxFifoTrigLvl = 0U;
#if (SPI_DMA_ENABLE == STD_ON)
        drvObj->jobObj[index].dmaChIdx = 0U;
#endif
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
    }
    drvObj->isAsynInProgress = (uint32)FALSE;
    drvObj->maxChannels      = 0U;
    drvObj->maxJobs          = 0U;
    drvObj->maxSeq           = 0U;
    drvObj->maxHwUnit        = 0U;

#if (STD_ON == SPI_DMA_ENABLE)
    drvObj->dmaEnableHwIndx = 0U;
#endif

#if ((SPI_SCALEABILITY == SPI_LEVEL_0) || (SPI_SCALEABILITY == SPI_LEVEL_2))
    drvObj->asyncMode = SPI_POLLING_MODE;
#endif
#if (SPI_SCALEABILITY == SPI_LEVEL_1)
    drvObj->asyncMode = SPI_INTERRUPT_MODE;
#endif

#if (STD_ON == SPI_JOB_LOG)
    (void)memset(&Spi_JobLogObj, 0, sizeof(Spi_JobLogObj));
#endif /* #if (STD_ON == SPI_JOB_LOG) */
}

#if (STD_ON == SPI_DEV_ERROR_DETECT)
Std_ReturnType Spi_checkConfig(const Spi_ConfigType *cfgPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

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
    uint32              index  = 0U;
    Spi_JobObjType     *jobObj = (Spi_JobObjType *)NULL_PTR;
    Spi_ChannelObjType *chObj  = (Spi_ChannelObjType *)NULL_PTR;
    drvObj->maxChannels        = cfgPtr->maxChannels;
    drvObj->maxJobs            = cfgPtr->maxJobs;
    drvObj->maxSeq             = cfgPtr->maxSeq;
    drvObj->maxHwUnit          = cfgPtr->maxHwUnit;
    drvObj->maxExtDevCfg       = cfgPtr->maxExtDevCfg;
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
        chObj = &drvObj->channelObj[index];
        (void)memcpy(&chObj->chCfg, &cfgPtr->channelCfg[index], sizeof(Spi_ChannelConfigType));
        if (chObj->chCfg.dataWidth < 9U)
        {
            chObj->bufWidth        = 1U;
            chObj->chCfg.dataWidth = 8U;
        }
        else if (chObj->chCfg.dataWidth < 17U)
        {
            chObj->bufWidth        = 2U;
            chObj->chCfg.dataWidth = 16U;
        }
        else
        {
            chObj->bufWidth        = 4U;
            chObj->chCfg.dataWidth = 32U;
        }
        /* Incase of IB, the numWordsTxRx is same as maxBufLength */
        if (SPI_IB == chObj->chCfg.channelBufType)
        {
            chObj->numWordsTxRx = chObj->chCfg.maxBufLength;
        }
        /* Calculate data width mask depending on SPI word size */
        chObj->dataWidthBitMask = Spi_getDataWidthBitMask(chObj->chCfg.dataWidth);
    }
    for (index = 0U; index < cfgPtr->maxJobs; index++)
    {
        jobObj = &drvObj->jobObj[index];
        (void)memcpy(&jobObj->jobCfg, &cfgPtr->jobCfg[index], sizeof(Spi_JobConfigType));
        (void)memcpy(&jobObj->jobCfg_PC, &Spi_JobConfig_PC[index], sizeof(Spi_JobConfigType_PC));
        jobObj->hwUnitObj = Spi_getHwUnitObj(jobObj->jobCfg.hwUnitId);
        jobObj->extDevCfg = &drvObj->extDevCfg[jobObj->jobCfg_PC.externalDeviceCfgId];
    }

    Spi_copyConfig_MaxSeq(drvObj, cfgPtr);
}

static void Spi_copyConfig_MaxSeq(Spi_DriverObjType *drvObj, const Spi_ConfigType *cfgPtr)
{
    uint32 index = 0;

    for (index = 0U; index < cfgPtr->maxSeq; index++)
    {
        (void)memcpy(&drvObj->seqObj[index].seqCfg, &cfgPtr->seqCfg[index], sizeof(Spi_SeqConfigType));
        drvObj->seqObj[index].seqCfg_PC.seqId = Spi_SeqConfig_PC[index].seqId;
    }
}

uint32 Spi_getHwUnitBaseAddr(Spi_HWUnitType hwUnitId)
{
    return (Spi_HwUnitBaseAddr[hwUnitId]);
}

uint32 Spi_getDataWidthBitMask(uint32 dataWidth)
{
    uint32 index, fifoBitMask = 0x0U;
    uint32 tmpVar = 0U;

    for (index = 0U; index < dataWidth; index++)
    {
        tmpVar       = ((uint32)1U << index);
        fifoBitMask |= tmpVar;
    }

    return (fifoBitMask);
}

void Spi_processChCompletion(Spi_HwUnitObjType *hwUnitObj, Spi_JobResultType jobResult)
{
    Spi_ChannelType     chId   = 0U;
    Spi_ChannelObjType *chObj  = (Spi_ChannelObjType *)NULL_PTR;
    Spi_JobObjType     *jobObj = (Spi_JobObjType *)NULL_PTR;

    jobObj = hwUnitObj->curJobObj;

    /* Channel completed */
    jobObj->curChIdx++;
    if (jobObj->curChIdx == jobObj->jobCfg.channelPerJob)
    {
        /*
         * Job completed
         */

        /* Stop the hardware */
        if (hwUnitObj->enableDmaMode != (boolean)TRUE)
        {
            Spi_mcspiStop(hwUnitObj, jobObj);
        }
#if (STD_ON == SPI_DMA_ENABLE)
        else
        {
            Spi_dmaStop(jobObj, hwUnitObj->baseAddr, hwUnitObj->curJobObj->jobCfg_PC.csPin,
                        MCSPI_MODULCTRL_SINGLE_SINGLE);
        }
        jobObj->dmaChIdx = 0;
#endif
        Spi_processJobCompletion(jobObj, hwUnitObj, jobResult);
    }
    else
    {
        /* Start the next channel */
        chId  = jobObj->jobCfg.channelList[jobObj->curChIdx];
        chObj = Spi_getCurrChannelObj(chId);
        Spi_mcspiConfigCh(hwUnitObj, jobObj, chObj);
        if (hwUnitObj->enableDmaMode != (boolean)TRUE)
        {
            Spi_mcspiReStart(hwUnitObj, jobObj);
        }
#if (STD_ON == SPI_DMA_ENABLE)
        else
        {
            /* Transfer from next channel with DMA */
            Spi_dmaTransfer(hwUnitObj, jobObj, chObj, chObj->numWordsTxRx);
        }
#endif
    }
}

static void Spi_processJobCompletion(Spi_JobObjType *jobObj, Spi_HwUnitObjType *hwUnitObj, Spi_JobResultType jobResult)
{
    Spi_UtilsNode       *headNodeObj        = (Spi_UtilsNode *)NULL_PTR;
    Spi_SeqObjType      *seqObj             = (Spi_SeqObjType *)NULL_PTR;
    Spi_SeqEndNotifyType seqEndNotification = (Spi_SeqEndNotifyType)NULL_PTR;
    Spi_JobEndNotifyType jobEndNotification = (Spi_JobEndNotifyType)NULL_PTR;

    seqObj               = jobObj->seqObj;
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
    }

#ifdef SPI_E_HARDWARE_ERROR
    (void)Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
#endif

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

static Std_ReturnType Spi_queueJobs(Spi_SeqObjType *seqObj)
{
    uint32             index       = 0U;
    uint8              currSeqId   = 0U;
    Std_ReturnType     retVal      = (Std_ReturnType)E_OK;
    Spi_JobType        jobId       = 0U;
    Spi_JobObjType    *jobObj      = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType *hwUnitObj   = (Spi_HwUnitObjType *)NULL_PTR;
    Spi_UtilsParams    utilsParams = {0};

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

            /* Get current sequence ID which is in progress for this
             * HW unit */
            if (hwUnitObj->curJobObj == NULL_PTR)
            {
                /* No sequence in progress. Give invalid ID */
                currSeqId = SPI_MAX_SEQ;
            }
            else
            {
                currSeqId = hwUnitObj->curJobObj->seqObj->seqCfg_PC.seqId;
            }

            /* Queue the job to the hardware queue */
            jobObj->seqObj               = seqObj;
            jobObj->jobResult            = SPI_JOB_QUEUED;
            utilsParams.data             = jobObj;
            utilsParams.priority         = (uint32)jobObj->jobCfg.jobPriority;
            utilsParams.seqId            = seqObj->seqCfg_PC.seqId;
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

static void Spi_scheduleJob(Spi_JobObjType *jobObj)
{
    uint32              isIntrMode = 0U;
    Spi_ChannelType     chId       = 0U;
    Spi_ChannelObjType *chObj      = (Spi_ChannelObjType *)NULL_PTR;
    Spi_HwUnitObjType  *hwUnitObj  = (Spi_HwUnitObjType *)NULL_PTR;

    hwUnitObj = jobObj->hwUnitObj;

    if (hwUnitObj->enableDmaMode == (boolean)TRUE)
    {
        isIntrMode = (uint32)FALSE;
    }
    else
    {
        if (SPI_POLLING_MODE == Spi_DrvObj.asyncMode)
        {
            isIntrMode = (uint32)FALSE;
        }
        else
        {
            isIntrMode = (uint32)TRUE;
        }
    }
    /* Set the states */
    jobObj->jobResult = SPI_JOB_PENDING;
    jobObj->curChIdx  = 0U;

    /* Log the job */
#if (STD_ON == SPI_JOB_LOG)
    Spi_logJob(jobObj, hwUnitObj);
#endif /* #if (STD_ON == SPI_JOB_LOG) */

    /* Configure the hardware if previously configured job ID is
     * different */
    if (hwUnitObj->curConfiguredJobId != jobObj->jobCfg_PC.jobId)
    {
        Spi_mcspiConfigJob(hwUnitObj, jobObj);
        hwUnitObj->curConfiguredJobId = jobObj->jobCfg_PC.jobId;
    }

    /* Start the first channel */
    chId  = jobObj->jobCfg.channelList[jobObj->curChIdx];
    chObj = Spi_getCurrChannelObj(chId);
    Spi_mcspiConfigCh(hwUnitObj, jobObj, chObj);

    if (hwUnitObj->enableDmaMode != (boolean)TRUE)
    {
        Spi_mcspiStart(hwUnitObj, jobObj, isIntrMode);
    }
#if (STD_ON == SPI_DMA_ENABLE)
    else
    {
        Spi_dmaTransfer(hwUnitObj, jobObj, chObj, chObj->numWordsTxRx);
    }
#endif
}

static void Spi_scheduleAllJobsSyncTransmit(Spi_SeqObjType *seqObj)
{
    uint32               index              = 0U;
    Spi_JobObjType      *jobObj             = (Spi_JobObjType *)NULL_PTR;
    Spi_HwUnitObjType   *hwUnitObj          = (Spi_HwUnitObjType *)NULL_PTR;
    Spi_JobType          jobId              = 0U;
    Spi_JobResultType    jobResult          = SPI_JOB_OK;
    Spi_JobEndNotifyType jobEndNotification = (Spi_JobEndNotifyType)NULL_PTR;

    /* Set state of all jobs in sequence to queued */
    for (index = 0U; index < seqObj->seqCfg.jobPerSeq; index++)
    {
        jobId  = seqObj->seqCfg.jobList[index];
        jobObj = &Spi_DrvObj.jobObj[jobId];
        /* Queue the job to the hardware queue */
        jobObj->seqObj = seqObj;
        /* Set the states */
        jobObj->jobResult = SPI_JOB_QUEUED;
    }

    for (index = 0U; index < seqObj->seqCfg.jobPerSeq; index++)
    {
        jobId  = seqObj->seqCfg.jobList[index];
        jobObj = &Spi_DrvObj.jobObj[jobId];
        /* Queue the job to the hardware queue */
        jobObj->seqObj = seqObj;
        /* Set the states */
        jobObj->jobResult = SPI_JOB_PENDING;
        jobObj->curChIdx  = 0U;
        hwUnitObj         = jobObj->hwUnitObj;

#if (STD_ON == SPI_JOB_LOG)
        /* Log the job */
        Spi_logJob(jobObj, hwUnitObj);
#endif /* #if (STD_ON == SPI_JOB_LOG) */

        hwUnitObj->curJobObj    = jobObj;
        hwUnitObj->hwUnitResult = SPI_HW_UNIT_PENDING;

        /* Configure the hardware if previously configured job ID is
         * different */
        if (hwUnitObj->curConfiguredJobId != jobObj->jobCfg_PC.jobId)
        {
            Spi_mcspiConfigJob(hwUnitObj, jobObj);
            hwUnitObj->curConfiguredJobId = jobObj->jobCfg_PC.jobId;
        }

        jobResult = Spi_mcspiXferJob((const Spi_HwUnitObjType *)hwUnitObj, jobObj);

        hwUnitObj->curJobObj    = (Spi_JobObjType *)NULL_PTR;
        hwUnitObj->hwUnitResult = SPI_HW_UNIT_OK;

        seqObj->numJobsPending--;
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

static void Spi_checkAndSetDrvState(void)
{
    uint32 hwUnitIdx = 0U;

    /* Since check is done across HW unit, all interrupts
     * are disabled */
    uint32 isSomeHwBusy = (uint32)FALSE;
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
        if (Spi_ChannelConfig_PC[index].channelId >= cfgPtr->maxChannels)
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
        /* ID is used as index, can't exceed array size */
        if ((Spi_JobConfig_PC[index].jobId >= cfgPtr->maxJobs) || (cfgPtr->jobCfg[index].channelPerJob == 0U) ||
            (cfgPtr->jobCfg[index].channelPerJob > SPI_MAX_CHANNELS_PER_JOB) ||
            (Spi_JobConfig_PC[index].externalDeviceCfgId >= cfgPtr->maxExtDevCfg))
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
        if ((Spi_SeqConfig_PC[index].seqId >= cfgPtr->maxSeq) || (cfgPtr->seqCfg[index].jobPerSeq == 0U) ||
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

    logEntry = &Spi_JobLogObj.logEntry[Spi_JobLogObj.logIndex];

    logEntry->timeStamp = 0U;
    logEntry->jobId     = jobObj->jobCfg_PC.jobId;
    logEntry->seqId     = jobObj->seqObj->seqCfg_PC.seqId;
    logEntry->hwUnitId  = hwUnitObj->hwUnitCfg.hwUnitId;

    /* Move to next entry */
    Spi_JobLogObj.logIndex++;
    Spi_JobLogObj.totalLog++;
    if (Spi_JobLogObj.logIndex >= SPI_MAX_JOB_LOG)
    {
        Spi_JobLogObj.logIndex = 0U;
    }
}

#endif /* #if (STD_ON == SPI_JOB_LOG) */

/* This API is to get address of current SPI Channel object */
Spi_ChannelObjPtrType Spi_getCurrChannelObj(Spi_ChannelType chId)
{
    return (&Spi_DrvObj.channelObj[chId]);
}

#if (STD_ON == SPI_REGISTER_READBACK_API)
FUNC(Std_ReturnType, SPI_CODE)
Spi_HWRegisterReadback(Spi_HWUnitType HWUnit, P2VAR(Spi_RegisterReadbackType, AUTOMATIC, SPI_APPL_DATA) RegRbPtr)
{
    Spi_HwUnitObjType *hwUnitObj = NULL_PTR;
    Std_ReturnType     retVal    = ((Std_ReturnType)E_OK);
    (void)memset(RegRbPtr, 0, sizeof(Spi_RegisterReadbackType));

    /* HW unit ID may not be the index, so search for
                                                 matching HW unit */
    hwUnitObj = Spi_getHwUnitObj(HWUnit);
    if (NULL_PTR != hwUnitObj)
    {
        Spi_mcspiRegReadback(hwUnitObj, RegRbPtr);
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return (retVal);
}
#endif /* #if (STD_ON == SPI_REGISTER_READBACK_API) */

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"
#ifdef __cplusplus
}
#endif
