/* ======================================================================
 *   Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     appUtils_QSpiFlashLib.c
 *
 *  \brief    This file contains the SPI flash lib apis
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "string.h"
#include "stdlib.h"
/*LDRA_ANALYSIS*/
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Spi.h"
#include "appUtils_QSpiFlashLib.h"
#include "trace.h"

#define QSPI_READ_DEVICEID_MAX_WORDS (20U)

static void mem1cpy(void *dstAddr, void *srcAddr, uint32 length);
boolean     QSPIFlashLib_isDataRdCommand(uint32 cmd);

QspiFlashDevInfoType gQspiFlashDevInfo;

uint8           QSPIFlashLib_defaultBuf[32 * 1024];
Spi_ConfigType *gSpiConfigPtr;

static Std_ReturnType QSPIFlashLib_GetDefaultFlashDevInfo(QspiFlashLib_deviceType flashType,
                                                          QspiFlashDevInfoType *flashDevInfo, uint32 memMapReadWidth,
                                                          uint32 isAsync);
static Std_ReturnType QSPIFlashLib_SetDefaultFlashDevInfo(QspiFlashDevInfoType *flashDevInfo);
static Spi_ClkMode    PlatformGetQspiMode(void);
static void           QSPI_SpansionFlashInit(QspiFlashLib_deviceType DeviceType, uint32 isAsync);

static void QSPIFlashLib_initChCfg(Spi_ChannelConfigType *channelCfg)
{
    channelCfg->channelBufType = SPI_EB;
    channelCfg->defaultTxData  = 0;
    channelCfg->transferType   = SPI_MSB;
    channelCfg->maxBufLength   = sizeof(QSPIFlashLib_defaultBuf);
}

static void QSPIFlashLib_initSeqCfg(Spi_SeqConfigType *seqCfg, uint32 seqId, uint32 jobId,
                                    Spi_SeqEndNotifyType seqEndNotify)
{
    seqCfg->Spi_SequenceEndNotification = seqEndNotify;
    seqCfg->seqId                       = seqId;
    seqCfg->seqInterruptible            = FALSE;
    seqCfg->jobPerSeq                   = 1;
    seqCfg->jobList[0]                  = jobId;
}

static void QSPIFlashLib_initJobCfg(Spi_JobConfigType *jobCfg, uint32 jobId, Spi_JobEndNotifyType jobEndNotify)
{
    jobCfg->csPin                  = SPI_CS0;
    jobCfg->channelPerJob          = 0;
    jobCfg->hwUnitId               = SPI_UNIT_QSPI1;
    jobCfg->externalDeviceCfgId    = QSPI_EXTERNAL_DEVICE_ID;
    jobCfg->jobId                  = jobId;
    jobCfg->jobPriority            = SPI_JOB_PRIORITY_0;
    jobCfg->Spi_JobEndNotification = jobEndNotify;
}

static Std_ReturnType QSPIFlashLib_setupBuf(Spi_ChannelType channel, Spi_ChannelConfigType *channelCfg, void *data,
                                            Spi_NumberOfDataType length)
{
    volatile Spi_DataBufferType    *src;
    volatile Spi_DataBufferType    *dst;
    Std_ReturnType                  retVal;
    volatile Spi_ChannelConfigType *ChCfg;

    src   = NULL;
    dst   = NULL;
    ChCfg = (volatile Spi_ChannelConfigType *)channelCfg;

    if (ChCfg->qspiXferCmd == SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE)
    {
        src = (volatile Spi_DataBufferType *)data;
    }
    else
    {
        dst = (volatile Spi_DataBufferType *)data;
    }
    retVal = Spi_SetupEB(channel, (Spi_DataBufferType *)src, (Spi_DataBufferType *)dst, length);
    GT_assert(McalAppTrace, (retVal == E_OK));
    return retVal;
}

static void QSPIFlashLib_getFlashCmdJobCfg(QspiFlashLib_FlashCmdType *flashCmd, Spi_SeqConfigType *seqCfg,
                                           Spi_JobConfigType *jobCfg, Spi_ChannelConfigType *channelCfgList,
                                           uint32 maxCh, uint32 startChId, uint32 jobId, uint32 seqId,
                                           Spi_SeqEndNotifyType seqEndNotify, Spi_JobEndNotifyType jobEndNotify,
                                           uint32 qspiEnableMemMapModeFlag)
{
    Spi_ChannelConfigType *channelCfg;
    uint32                 numCh;

    QSPIFlashLib_initSeqCfg(seqCfg, seqId, jobId, seqEndNotify);
    QSPIFlashLib_initJobCfg(jobCfg, jobId, jobEndNotify);
    AppUtils_printf("QSPIFlashLib_getFlashCmdJobCfg cmd : %x ch:%d datawidth %d\n\r", flashCmd->cmd, maxCh,
                    flashCmd->numPerDataWordbits);

    numCh = 0;
    GT_assert(McalAppTrace, (numCh < maxCh));
    channelCfg = &channelCfgList[numCh];
    QSPIFlashLib_initChCfg(channelCfg);
    channelCfg->qspiXferCmd    = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
    channelCfg->dataWidth      = flashCmd->numCmdBits;
    channelCfg->channelId      = startChId + numCh;
    channelCfg->qspiChMode     = SPI_QSPI_SFI_CHMODE_CMD;
    jobCfg->channelList[numCh] = channelCfg->channelId;

    /* Write Address Bytes */
    if (flashCmd->numAddrBits != 0)
    {
        numCh++;
        GT_assert(McalAppTrace, (numCh < maxCh));
        channelCfg = &channelCfgList[numCh];
        QSPIFlashLib_initChCfg(channelCfg);
        channelCfg->qspiXferCmd    = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        channelCfg->dataWidth      = flashCmd->numAddrBits;
        channelCfg->channelId      = startChId + numCh;
        channelCfg->qspiChMode     = SPI_QSPI_SFI_CHMODE_ADDR;
        jobCfg->channelList[numCh] = channelCfg->channelId;
    }
    /* Write dummy Bytes */
    if (flashCmd->numAddrDummyBits != 0)
    {
        numCh++;
        GT_assert(McalAppTrace, (numCh < maxCh));
        channelCfg = &channelCfgList[numCh];
        QSPIFlashLib_initChCfg(channelCfg);
        channelCfg->qspiXferCmd    = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        channelCfg->dataWidth      = flashCmd->numAddrDummyBits;
        channelCfg->channelId      = startChId + numCh;
        channelCfg->qspiChMode     = SPI_QSPI_SFI_CHMODE_DUMMY;
        jobCfg->channelList[numCh] = channelCfg->channelId;
    }
    /* Read or Write data */
    jobCfg->qspiEnableMemMapMode = (uint8)FALSE;
    if (flashCmd->numDataWords != 0)
    {
        if (1U == qspiEnableMemMapModeFlag)
        {
            if (TRUE == QSPIFlashLib_isDataRdCommand(flashCmd->cmd))
            {
                jobCfg->qspiEnableMemMapMode = (uint8)TRUE;
            }
        }
        numCh++;
        GT_assert(McalAppTrace, (numCh < maxCh));
        channelCfg = &channelCfgList[numCh];
        QSPIFlashLib_initChCfg(channelCfg);
        channelCfg->qspiXferCmd    = flashCmd->dataType;
        channelCfg->dataWidth      = flashCmd->numPerDataWordbits;
        channelCfg->channelId      = startChId + numCh;
        channelCfg->qspiChMode     = SPI_QSPI_SFI_CHMODE_DATA;
        jobCfg->channelList[numCh] = channelCfg->channelId;
    }
    numCh++;
    jobCfg->channelPerJob = numCh;
    flashCmd->seqId       = seqId;
}

static Spi_QspiMemSetupReadType getMemSetupReadType(uint32 cmdRegDataType)
{
    Spi_QspiMemSetupReadType readType;
    if (cmdRegDataType == SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE)
    {
        readType = SPI_QSPI_MEMSETUP_READTYPE_NORMAL_0;
    }
    else if (cmdRegDataType == SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_DUAL)
    {
        readType = SPI_QSPI_MEMSETUP_READTYPE_DUAL;
    }
    else if (cmdRegDataType == SPI_QSPI_SFI_CH_XFER_CMD_6PIN_RD_QUAD)
    {
        readType = SPI_QSPI_MEMSETUP_READTYPE_QUAD;
    }
    else
    {
        readType = SPI_QSPI_MEMSETUP_READTYPE_NORMAL_0;
    }
    return readType;
}

static Spi_QspiMemSetupNumAddrBytesType getNumAddrBytesFromBits(uint32 numBits)
{
    Spi_QspiMemSetupNumAddrBytesType numBytes;
    if (numBits <= 8)
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMADDR_BYTES_1;
    }
    else if (numBits <= 16)
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMADDR_BYTES_2;
    }
    else if (numBits <= 24)
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMADDR_BYTES_3;
    }
    else if (numBits <= 32)
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMADDR_BYTES_4;
    }
    else
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMADDR_BYTES_1;
    }
    return numBytes;
}

static Spi_QspiMemSetupNumDummyBytesType getNumDummyBytesFromBits(uint32 numBits)
{
    Spi_QspiMemSetupNumDummyBytesType numBytes;
    if (numBits == 8)
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMDUMMY_BYTES_1;
    }
    else if (numBits == 16)
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMDUMMY_BYTES_2;
    }
    else if (numBits == 24)
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMDUMMY_BYTES_3;
    }
    else
    {
        numBytes = SPI_QSPI_MEMSETUP_NUMDUMMY_BYTES_0;
    }
    return numBytes;
}

static void QSPIFlashLib_setMemSetupCfg(QspiFlashDevInfoType *flashDevInfo, Spi_QspiMemSetupConfigType *memSetup)
{
    /* Set Memory Map Setup registers */
    memSetup->readCmd       = flashDevInfo->readCmd.cmd;
    memSetup->numAddrBytes  = getNumAddrBytesFromBits(flashDevInfo->readCmd.numAddrBits);
    memSetup->numDummyBytes = getNumDummyBytesFromBits(flashDevInfo->readCmd.numAddrDummyBits);
    memSetup->readType      = getMemSetupReadType(flashDevInfo->readCmd.dataType);
    memSetup->writeCmd      = flashDevInfo->writeCmd.cmd;
    // memSetup->writeCmd = 0;

    if (getNumDummyBytesFromBits(flashDevInfo->readCmd.numAddrDummyBits) != SPI_QSPI_MEMSETUP_NUMDUMMY_BYTES_0)
    {
        memSetup->numDummyBits = 0;
    }
    else
    {
        memSetup->numDummyBits = flashDevInfo->readCmd.numAddrDummyBits;
    }

    memSetup->numDummyBytes = getNumDummyBytesFromBits(flashDevInfo->readCmd.numAddrDummyBits);
}

static void QSPIFlashLib_setExtDevCfg(QspiFlashDevInfoType *flashDevInfo, Spi_ExternalDeviceConfigType *extDevCfg)
{
    extDevCfg->qspi.csPolarity = SPI_LOW;
    extDevCfg->qspi.clkMode    = gQspiFlashDevInfo.qspiMode;
    extDevCfg->qspi.csIdleTime = flashDevInfo->qspiDataDelay;
    extDevCfg->qspi.clkDivider = flashDevInfo->qspifrequency & QSPI_CLKDIVIDER_MASK;
    QSPIFlashLib_setMemSetupCfg(flashDevInfo, &extDevCfg->qspi.qspiMemSetup);
}

static void QSPIFlashLib_setHwCfg(Spi_HwUnitConfigType *hwUnitCfg)
{
    hwUnitCfg->hwUnitId = SPI_UNIT_QSPI1;
}

static void QSPIFlashLib_setCfg(QspiFlashDevInfoType *flashDevInfo, Spi_ConfigType *spiCfg,
                                Spi_SeqEndNotifyType seqEndNotify, Spi_JobEndNotifyType jobEndNotify,
                                uint32 qspiEnableMemMapModeFlag)
{
    uint32 chIndex  = 0;
    uint32 jobIndex = 0;
    uint32 seqIndex = 0;

    QSPIFlashLib_setExtDevCfg(flashDevInfo, &spiCfg->extDevCfg[QSPI_EXTERNAL_DEVICE_ID]);

    QSPIFlashLib_setHwCfg(&spiCfg->hwUnitCfg[0]);
    spiCfg->maxExtDevCfg = 1;
    spiCfg->maxHwUnit    = 1;

    AppUtils_printf("QSPIFlashLib_setCfg : %d\n\r", SPI_MAX_CHANNELS - chIndex);

    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->flashStatusCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 1 */
    seqIndex++;

    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->fullEraseCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 2 */
    seqIndex++;
    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->idCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 3 */
    seqIndex++;

    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->readCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 4 */
    seqIndex++;
    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->sectorEraseCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 5 */
    seqIndex++;
    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->writeCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 6 */
    seqIndex++;
    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->writeEnableCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 7 */
    seqIndex++;
    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->flashCfgReadCmd, &spiCfg->seqCfg[seqIndex], &spiCfg->jobCfg[jobIndex],
                                   &spiCfg->channelCfg[chIndex], (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex,
                                   seqIndex, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);

    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 8 */
    seqIndex++;
    QSPIFlashLib_getFlashCmdJobCfg(&flashDevInfo->flashCfgWriteCmd, &spiCfg->seqCfg[seqIndex],
                                   &spiCfg->jobCfg[jobIndex], &spiCfg->channelCfg[chIndex],
                                   (SPI_MAX_CHANNELS - chIndex), chIndex, jobIndex, seqIndex, seqEndNotify,
                                   jobEndNotify, qspiEnableMemMapModeFlag);
    chIndex += spiCfg->jobCfg[jobIndex].channelPerJob;
    jobIndex++; /* 9 */
    seqIndex++;

    spiCfg->maxChannels = chIndex;
    spiCfg->maxJobs     = jobIndex;
    spiCfg->maxSeq      = seqIndex;
}

uint32 dummyAddressData = 0;

Std_ReturnType QSPIFlashLib_executeCmd(QspiFlashLib_FlashCmdType flashCmd, uint32 *data, uint32 isAsync)
{
    Std_ReturnType                  retVal;
    uint32                          chIndex;
    volatile Spi_ConfigType        *spiConfig;
    volatile Spi_SequenceType       sequenceId;
    volatile Spi_JobConfigType     *jobCfg;
    volatile Spi_ChannelConfigType *channelCfgList;
    volatile uint32                 Nwords;
    volatile uint32                *Info;

    spiConfig      = gSpiConfigPtr;
    sequenceId     = flashCmd.seqId;
    jobCfg         = &spiConfig->jobCfg[spiConfig->seqCfg[sequenceId].jobList[0]];
    channelCfgList = &spiConfig->channelCfg[0];
    chIndex        = 0;
    retVal         = E_OK;
    Nwords         = flashCmd.numDataWords;
    Info           = data;

    if ((Nwords != 0) && (Info == NULL))
    {
        retVal = E_NOT_OK;
    }

    if (retVal == E_OK)
    {
        if (channelCfgList[jobCfg->channelList[chIndex]].dataWidth != flashCmd.numCmdBits)
        {
            AppUtils_printf("Stay here chnlidx :%d CMD 0x%x datawidth %d numcmdbits %d\n\r", chIndex, flashCmd.cmd,
                            channelCfgList[jobCfg->channelList[chIndex]].dataWidth, flashCmd.numCmdBits);
        }
        GT_assert(McalAppTrace, channelCfgList[jobCfg->channelList[chIndex]].dataWidth == flashCmd.numCmdBits);
        retVal = QSPIFlashLib_setupBuf(channelCfgList[jobCfg->channelList[chIndex]].channelId,
                                       (Spi_ChannelConfigType *)&channelCfgList[jobCfg->channelList[chIndex]],
                                       &flashCmd.cmd, 1);
        /* Write Address Bytes */
        if (flashCmd.numAddrBits != 0)
        {
            chIndex++;
            GT_assert(McalAppTrace, channelCfgList[jobCfg->channelList[chIndex]].dataWidth == flashCmd.numAddrBits);
            QSPIFlashLib_setupBuf(channelCfgList[jobCfg->channelList[chIndex]].channelId,
                                  (Spi_ChannelConfigType *)&channelCfgList[jobCfg->channelList[chIndex]],
                                  &flashCmd.addr, 1);
        }

        /* Write dummy Bytes */
        if (flashCmd.numAddrDummyBits != 0)
        {
            chIndex++;
            GT_assert(McalAppTrace,
                      channelCfgList[jobCfg->channelList[chIndex]].dataWidth == flashCmd.numAddrDummyBits);
            dummyAddressData = 0U;
            QSPIFlashLib_setupBuf(channelCfgList[jobCfg->channelList[chIndex]].channelId,
                                  (Spi_ChannelConfigType *)&channelCfgList[jobCfg->channelList[chIndex]],
                                  &dummyAddressData, 1);
        }
        /* Read or Write data */
        if (flashCmd.numDataWords != 0)
        {
            chIndex++;
            GT_assert(McalAppTrace,
                      channelCfgList[jobCfg->channelList[chIndex]].dataWidth == flashCmd.numPerDataWordbits);
            QSPIFlashLib_setupBuf(channelCfgList[jobCfg->channelList[chIndex]].channelId,
                                  (Spi_ChannelConfigType *)&channelCfgList[jobCfg->channelList[chIndex]], data,
                                  flashCmd.numDataWords);
        }
        if (isAsync == TRUE)
        {
            retVal = Spi_AsyncTransmit(sequenceId);
            while (gQspiSeqDone[0U] != TRUE || gQspiJobDone[0U] != TRUE)
            {
            }
            gQspiSeqDone[0U] = FALSE;
            gQspiJobDone[0U] = FALSE;
        }
        else
        {
            retVal = Spi_SyncTransmit(sequenceId);
        }
    }
    return retVal;
}

uint32 QSPIFlashLib_Initialize(QspiFlashLib_deviceType DeviceType, Spi_ConfigType *spiCfg,
                               Spi_SeqEndNotifyType seqEndNotify, Spi_JobEndNotifyType jobEndNotify,
                               uint32 qspiEnableMemMapModeFlag, uint32 memMapReadWidth, uint32 isAsync)
{
    sint32               retVal;
    QspiFlashDevInfoType localFlashDevInfo;

    gSpiConfigPtr = spiCfg;
    /* Default initialize for device type passed */
    retVal = QSPIFlashLib_GetDefaultFlashDevInfo(DeviceType, &localFlashDevInfo, memMapReadWidth, isAsync);
    if (retVal == E_OK)
    {
        QSPIFlashLib_SetDefaultFlashDevInfo(&localFlashDevInfo);
    }
    QSPIFlashLib_setCfg(&gQspiFlashDevInfo, gSpiConfigPtr, seqEndNotify, jobEndNotify, qspiEnableMemMapModeFlag);
    Spi_Init(gSpiConfigPtr);

    if (NULL != gQspiFlashDevInfo.qspiFlashInitFxn)
    {
        gQspiFlashDevInfo.qspiFlashInitFxn(DeviceType, isAsync);
    }

    return E_OK;
} /* QSPI_Initialize */

uint32 QSPIFlashLib_GetDeviceId(uint32 isAsync)
{
    uint32 deviceId[2U];
    QSPIFlashLib_GetDeviceIdExtended(2U, &deviceId[0], isAsync);
    return ((deviceId[1U] << 16U) | deviceId[0]);
}

uint32 QSPIFlashLib_GetDeviceIdExtended(uint32 numSpiWords, uint32 *data, uint32 isAsync)
{
    uint32 retval;
    uint32 deviceId[QSPI_READ_DEVICEID_MAX_WORDS] = {0};
    if (gQspiFlashDevInfo.idCmd.numDataWords > QSPI_READ_DEVICEID_MAX_WORDS)
    {
        gQspiFlashDevInfo.idCmd.numDataWords = QSPI_READ_DEVICEID_MAX_WORDS;
    }
    /* Always read full id command but return numWords */
    retval = QSPIFlashLib_executeCmd(gQspiFlashDevInfo.idCmd, &deviceId[0], isAsync);
    if (numSpiWords > QSPI_READ_DEVICEID_MAX_WORDS)
    {
        numSpiWords = QSPI_READ_DEVICEID_MAX_WORDS;
    }
    /* Copy the number of data words passed as parameter */
    mem1cpy(data, &deviceId[0], numSpiWords * 4);
    return retval;
}

void mem1cpy(void *dstAddr, void *srcAddr, uint32 length)
{
    uint32  i;
    uint32 *DAddr = (uint32 *)(dstAddr);
    uint32 *SAddr = (uint32 *)(srcAddr);
    uint8  *DAddr_byte, *SAddr_byte;

    /*Do a word read*/
    for (i = 0; i < (length / 4); i++)
    {
        *DAddr++ = *SAddr++;
    }

    /*Do a byte write*/
    if (length % 4)
    {
        DAddr_byte = (uint8 *)DAddr;
        SAddr_byte = (uint8 *)SAddr;
        for (i = 0; i < (length % 4); ++i)
        {
            *DAddr_byte++ = *SAddr_byte++;
        }
    }
}

void QSPIFlashLib_ReadCfgMode(uint32 dstAddr, uint32 srcOffsetAddr, uint32 length, uint32 isAsync)
{
    gQspiFlashDevInfo.readCmd.numDataWords = length;
    gQspiFlashDevInfo.readCmd.addr         = srcOffsetAddr;
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.readCmd, (uint32 *)dstAddr, isAsync);
    gQspiFlashDevInfo.readCmd.numDataWords = 0;
    gQspiFlashDevInfo.readCmd.addr         = 0;
    return;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPIFlashLib_WriteCfgModeNonBlocking(uint32 dstOffsetAddr, uint32 srcAddr, uint32 length, uint32 isAsync)
{
    gQspiFlashDevInfo.writeCmd.numDataWords = length;
    gQspiFlashDevInfo.writeCmd.addr         = dstOffsetAddr;
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.writeCmd, (uint32 *)srcAddr, isAsync);
    gQspiFlashDevInfo.writeCmd.numDataWords = 0;
    gQspiFlashDevInfo.writeCmd.addr         = 0;
}

void QSPIFlashLib_WriteCfgMode(uint32 dstOffsetAddr, uint32 srcAddr, uint32 length, uint32 isAsync)
{
    QSPIFlashLib_WriteCfgModeNonBlocking(dstOffsetAddr, srcAddr, length, isAsync);
    /* Wait while Flash is busy */
    while ((QSPIFlashLib_FlashStatus(isAsync) & 0x01U))
        ;
}

uint32 QSPIFlashLib_FlashStatus(uint32 isAsync)
{
    uint32 data = 0;
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.flashStatusCmd, &data, isAsync);
    return (data & 0xFFU);
}

void QSPIFlashLib_WriteEnable(uint32 isAsync)
{
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.writeEnableCmd, NULL, isAsync);

    while (((QSPIFlashLib_FlashStatus(isAsync) & 0x02U) ^ 0x02U))
        ;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPIFlashLib_QuadEnableNonBlocking(uint32 isAsync)
{
    uint32 sr1 = 0, cr = 0;

    QSPIFlashLib_WriteEnable(isAsync);

    /* Read Ststus register 1 */
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.flashStatusCmd, &sr1, isAsync);

    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.flashCfgReadCmd, &cr, isAsync);

    /* Set Configuration register 2nd bit to 1 for Quad enable */
    cr |= 0x2U;
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.flashCfgWriteCmd, &cr, isAsync);
}

void QSPIFlashLib_QuadEnable(uint32 isAsync)
{
    QSPIFlashLib_QuadEnableNonBlocking(isAsync);
    /* Wait while Flash is busy */
    while ((QSPIFlashLib_FlashStatus(isAsync) & 0x01U))
        ;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPIFlashLib_FlashBlockEraseNonBlocking(uint32 blkNo, uint32 isAsync)
{
    gQspiFlashDevInfo.sectorEraseCmd.numDataWords = 0;
    gQspiFlashDevInfo.sectorEraseCmd.addr         = blkNo * QSPIFLASH_SECTORSIZE;
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.sectorEraseCmd, NULL, isAsync);
    gQspiFlashDevInfo.sectorEraseCmd.addr = 0;
}

void QSPIFlashLib_FlashBlockErase(uint32 blkNo, uint32 isAsync)
{
    QSPIFlashLib_FlashBlockEraseNonBlocking(blkNo, isAsync);
    /* Wait while Flash is busy */
    while ((QSPIFlashLib_FlashStatus(isAsync) & 0x01U))
        ;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPIFlashLib_FlashFullEraseNonBlocking(uint32 isAsync)
{
    QSPIFlashLib_executeCmd(gQspiFlashDevInfo.fullEraseCmd, NULL, isAsync);
}

void QSPIFlashLib_FlashFullErase(uint32 isAsync)
{
    QSPIFlashLib_FlashFullEraseNonBlocking(isAsync);
    /* Wait while Flash is busy */
    while ((QSPIFlashLib_FlashStatus(isAsync) & 0x01U))
        ;
}

void QSPIFlashLib_seek(uint32 *srcAddr, uint32 location)
{
    *srcAddr = location;
}

void AppUtils_generateData(uint8 *srcAddr, uint32 length, uint32 chDataWidth)
{
    uint8  *tempTxPtr8;
    uint16 *tempTxPtr16;
    uint32 *tempTxPtr32;
    uint32  tempTxData, index;
    uint32  fifoBitMask, dataWidthIdx;

    if (chDataWidth < 8U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr8 = (uint8 *)srcAddr;
    }
    else if (chDataWidth < 16U)
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr16 = (uint16 *)srcAddr;
    }
    else
    {
        /* Init TX buffer with known data and memset RX buffer */
        tempTxPtr32 = (uint32 *)srcAddr;
    }
    fifoBitMask = 0x0U;
    for (dataWidthIdx = 0U; dataWidthIdx < chDataWidth; dataWidthIdx++)
    {
        fifoBitMask |= (1U << dataWidthIdx);
    }
    for (index = 0U; index < (length); index++)
    {
#if (0U == SPI_TEST_WAVEFORM_ANALYSIS)
        tempTxData  = rand() & 0xff;
        tempTxData |= (rand() & 0xff) << 8;
        tempTxData |= (rand() & 0xff) << 16;
        tempTxData |= (rand() & 0xff) << 24;
#else
        tempTxData = 0xAAAAAAAA; /*1010 pattern so wave toggle */
#endif
        tempTxData %= (fifoBitMask + 1); /* Add one to take care of last bit
                                          **/
        if (chDataWidth < 8U)
        {
            *tempTxPtr8++ = (uint8)(tempTxData);
        }
        else if (chDataWidth < 16U)
        {
            *tempTxPtr16++ = (uint16)(tempTxData);
        }
        else
        {
            *tempTxPtr32++ = (uint32)(tempTxData);
        }
    }
}

static Std_ReturnType QSPIFlashLib_GetDefaultFlashDevInfo(QspiFlashLib_deviceType flashType,
                                                          QspiFlashDevInfoType *flashDevInfo, uint32 memMapReadWidth,
                                                          uint32 isAsync)
{
    Std_ReturnType retVal = E_OK;
    if (NULL == flashDevInfo)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (retVal == E_OK)
    {
        flashDevInfo->flashType     = flashType;
        flashDevInfo->qspiCs        = 0U;
        flashDevInfo->qspiDataDelay = SPI_DATADELAY_0;

        /* Initialize default mode to 3 and clk frequency to 12MHz */
        flashDevInfo->qspiMode      = SPI_CLK_MODE_3;
        flashDevInfo->qspifrequency = QSPI_SCLK_FREQ_40MHz;

        /* Initialize default data lines to 1 */
        flashDevInfo->numDatalines = 1U;

        flashDevInfo->qspiFlashInitFxn = NULL;
    }
    if ((retVal == E_OK) && (flashType == DEVICE_TYPE_SPANSION_QSPI4 || flashType == DEVICE_TYPE_SPANSION_QSPI1))
    {
        /* Initialize QSPI Mode */
        flashDevInfo->qspiMode      = PlatformGetQspiMode();
        flashDevInfo->qspifrequency = QSPI_SCLK_FREQ_40MHz;

        /* Initialize QSPI clk frequency */
        if (flashType == DEVICE_TYPE_SPANSION_QSPI4)
        {
            /* Use default speed */
        }

        /* Initializing Id Cmd */
        /* memClr(flashDevInfo, sizeof(flashDevInfo)); */
        flashDevInfo->idCmd.numCmdBits         = 8;
        flashDevInfo->idCmd.cmd                = QSPI_CMD_MFGID_AR;
        flashDevInfo->idCmd.numAddrBits        = 24;
        flashDevInfo->idCmd.addr               = 0;
        flashDevInfo->idCmd.numAddrDummyBits   = 0;
        flashDevInfo->idCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE;
        flashDevInfo->idCmd.numDataWords       = 4;
        flashDevInfo->idCmd.numPerDataWordbits = 8;

        /* Initializing write Cmd */
        flashDevInfo->writeCmd.numCmdBits         = 8;
        flashDevInfo->writeCmd.cmd                = QSPI_CMD_WRITE_24;
        flashDevInfo->writeCmd.numAddrBits        = 24;
        flashDevInfo->writeCmd.addr               = 0;
        flashDevInfo->writeCmd.numAddrDummyBits   = 0;
        flashDevInfo->writeCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->writeCmd.numDataWords       = 64;   // Upto 64 words
        flashDevInfo->writeCmd.numPerDataWordbits = 32U;  // change this for
                                                          // testing

        /* Initializing sector erase Cmd */
        flashDevInfo->sectorEraseCmd.numCmdBits         = 8;
        flashDevInfo->sectorEraseCmd.cmd                = QSPI_CMD_PAGEERASE;
        flashDevInfo->sectorEraseCmd.numAddrBits        = 24;
        flashDevInfo->sectorEraseCmd.addr               = 0;
        flashDevInfo->sectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->sectorEraseCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->sectorEraseCmd.numDataWords       = 0;
        flashDevInfo->sectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing full erase Cmd */
        flashDevInfo->fullEraseCmd.numCmdBits         = 8;
        flashDevInfo->fullEraseCmd.cmd                = QSPI_CMD_FULLERASE;
        flashDevInfo->fullEraseCmd.numAddrBits        = 0;
        flashDevInfo->fullEraseCmd.addr               = 0;
        flashDevInfo->fullEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->fullEraseCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->fullEraseCmd.numDataWords       = 0;
        flashDevInfo->fullEraseCmd.numPerDataWordbits = 0;

        /* Initializing write enable Cmd */
        flashDevInfo->writeEnableCmd.numCmdBits         = 8;
        flashDevInfo->writeEnableCmd.cmd                = QSPI_CMD_WREN;
        flashDevInfo->writeEnableCmd.numAddrBits        = 0;
        flashDevInfo->writeEnableCmd.addr               = 0;
        flashDevInfo->writeEnableCmd.numAddrDummyBits   = 0;
        flashDevInfo->writeEnableCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->writeEnableCmd.numDataWords       = 0;
        flashDevInfo->writeEnableCmd.numPerDataWordbits = 0;

        /* Initializing flash status Cmd */
        flashDevInfo->flashStatusCmd.numCmdBits         = 8;
        flashDevInfo->flashStatusCmd.cmd                = QSPI_CMD_RDSR;
        flashDevInfo->flashStatusCmd.numAddrBits        = 0;
        flashDevInfo->flashStatusCmd.addr               = 0;
        flashDevInfo->flashStatusCmd.numAddrDummyBits   = 0;
        flashDevInfo->flashStatusCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE;
        flashDevInfo->flashStatusCmd.numDataWords       = 1;
        flashDevInfo->flashStatusCmd.numPerDataWordbits = 8;
        /* Initializing flash control read Cmd */
        flashDevInfo->flashCfgReadCmd.numCmdBits         = 8;
        flashDevInfo->flashCfgReadCmd.cmd                = QSPI_CMD_RDCR;
        flashDevInfo->flashCfgReadCmd.numAddrBits        = 0;
        flashDevInfo->flashCfgReadCmd.addr               = 0;
        flashDevInfo->flashCfgReadCmd.numAddrDummyBits   = 0;
        flashDevInfo->flashCfgReadCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE;
        flashDevInfo->flashCfgReadCmd.numDataWords       = 2;
        flashDevInfo->flashCfgReadCmd.numPerDataWordbits = 8;
        /* Initializing flash control write Cmd */
        flashDevInfo->flashCfgWriteCmd.numCmdBits         = 8;
        flashDevInfo->flashCfgWriteCmd.cmd                = 0x31;
        flashDevInfo->flashCfgWriteCmd.numAddrBits        = 0;
        flashDevInfo->flashCfgWriteCmd.addr               = 0;
        flashDevInfo->flashCfgWriteCmd.numAddrDummyBits   = 0;
        flashDevInfo->flashCfgWriteCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->flashCfgWriteCmd.numDataWords       = 1;
        flashDevInfo->flashCfgWriteCmd.numPerDataWordbits = 8;

        if (flashType == DEVICE_TYPE_SPANSION_QSPI1)
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits         = 8;
            flashDevInfo->readCmd.cmd                = QSPI_CMD_READ_24;
            flashDevInfo->readCmd.numAddrBits        = 24;
            flashDevInfo->readCmd.addr               = 0;
            flashDevInfo->readCmd.numAddrDummyBits   = 0;
            flashDevInfo->readCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE;
            flashDevInfo->readCmd.numDataWords       = 64;
            flashDevInfo->readCmd.numPerDataWordbits = memMapReadWidth;

            /* Initialize data lines */
            flashDevInfo->numDatalines = 1U;
        }
        else /* DEVICE_TYPE_SPANSION_QSPI4 */
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits         = 8;
            flashDevInfo->readCmd.cmd                = QSPI_CMD_FAST_QREAD_24;
            flashDevInfo->readCmd.numAddrBits        = 24;
            flashDevInfo->readCmd.addr               = 0;
            flashDevInfo->readCmd.numAddrDummyBits   = 8;
            flashDevInfo->readCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_6PIN_RD_QUAD;
            flashDevInfo->readCmd.numDataWords       = 64;
            flashDevInfo->readCmd.numPerDataWordbits = memMapReadWidth;
            /* Initialize data lines */
            flashDevInfo->numDatalines = 4U;
        }

        flashDevInfo->qspiFlashInitFxn = &QSPI_SpansionFlashInit;
    }
    if ((retVal == E_OK) && (flashType == DEVICE_TYPE_MICRON_QSPI1 || flashType == DEVICE_TYPE_MICRON_QSPI4))
    {
        /* Initializing Id Cmd */
        flashDevInfo->idCmd.numCmdBits         = 8;
        flashDevInfo->idCmd.cmd                = QSPI_CMD_MICRON_MFGID;
        flashDevInfo->idCmd.numAddrBits        = 0;
        flashDevInfo->idCmd.addr               = 0;
        flashDevInfo->idCmd.numAddrDummyBits   = 0;
        flashDevInfo->idCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE;
        flashDevInfo->idCmd.numDataWords       = 20;
        flashDevInfo->idCmd.numPerDataWordbits = 8;

        /* Initializing write Cmd */
        flashDevInfo->writeCmd.numCmdBits         = 8;
        flashDevInfo->writeCmd.cmd                = QSPI_CMD_MICRON_WRITE_24;
        flashDevInfo->writeCmd.numAddrBits        = 24;
        flashDevInfo->writeCmd.addr               = 0;
        flashDevInfo->writeCmd.numAddrDummyBits   = 0;
        flashDevInfo->writeCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->writeCmd.numDataWords       = 64;
        flashDevInfo->writeCmd.numPerDataWordbits = 32U;  // change this for
                                                          // testing

        /* Initializing sector erase Cmd */
        flashDevInfo->sectorEraseCmd.numCmdBits         = 8;
        flashDevInfo->sectorEraseCmd.cmd                = QSPI_CMD_MICRON_BLKERASE_24;
        flashDevInfo->sectorEraseCmd.numAddrBits        = 24;
        flashDevInfo->sectorEraseCmd.addr               = 0;
        flashDevInfo->sectorEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->sectorEraseCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->sectorEraseCmd.numDataWords       = 0;
        flashDevInfo->sectorEraseCmd.numPerDataWordbits = 0;

        /* Initializing full erase Cmd */
        flashDevInfo->fullEraseCmd.numCmdBits         = 8;
        flashDevInfo->fullEraseCmd.cmd                = QSPI_CMD_MICRON_FULLERASE;
        flashDevInfo->fullEraseCmd.numAddrBits        = 0;
        flashDevInfo->fullEraseCmd.addr               = 0;
        flashDevInfo->fullEraseCmd.numAddrDummyBits   = 0;
        flashDevInfo->fullEraseCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->fullEraseCmd.numDataWords       = 0;
        flashDevInfo->fullEraseCmd.numPerDataWordbits = 0;

        /* Initializing write enable Cmd */
        flashDevInfo->writeEnableCmd.numCmdBits         = 8;
        flashDevInfo->writeEnableCmd.cmd                = QSPI_CMD_MICRON_WREN;
        flashDevInfo->writeEnableCmd.numAddrBits        = 0;
        flashDevInfo->writeEnableCmd.addr               = 0;
        flashDevInfo->writeEnableCmd.numAddrDummyBits   = 0;
        flashDevInfo->writeEnableCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_WR_SINGLE;
        flashDevInfo->writeEnableCmd.numDataWords       = 0;
        flashDevInfo->writeEnableCmd.numPerDataWordbits = 0;

        /* Initializing flash status Cmd */
        flashDevInfo->flashStatusCmd.numCmdBits         = 8;
        flashDevInfo->flashStatusCmd.cmd                = QSPI_CMD_MICRON_RDSR;
        flashDevInfo->flashStatusCmd.numAddrBits        = 0;
        flashDevInfo->flashStatusCmd.addr               = 0;
        flashDevInfo->flashStatusCmd.numAddrDummyBits   = 0;
        flashDevInfo->flashStatusCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE;
        flashDevInfo->flashStatusCmd.numDataWords       = 1;
        flashDevInfo->flashStatusCmd.numPerDataWordbits = 8;

        if (flashType == DEVICE_TYPE_MICRON_QSPI1)
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits         = 8;
            flashDevInfo->readCmd.cmd                = QSPI_CMD_MICRON_READ_24;
            flashDevInfo->readCmd.numAddrBits        = 24;
            flashDevInfo->readCmd.addr               = 0;
            flashDevInfo->readCmd.numAddrDummyBits   = 0;
            flashDevInfo->readCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_4PIN_RD_SINGLE;
            flashDevInfo->readCmd.numDataWords       = 64;
            flashDevInfo->readCmd.numPerDataWordbits = 32;
        }
        else /* DEVICE_TYPE_MICRON_QSPI1 */
        {
            /* Initializing read Cmd */
            flashDevInfo->readCmd.numCmdBits         = 8;
            flashDevInfo->readCmd.cmd                = QSPI_CMD_MICRON_QREAD_24;
            flashDevInfo->readCmd.numAddrBits        = 24;
            flashDevInfo->readCmd.addr               = 0;
            flashDevInfo->readCmd.numAddrDummyBits   = 8;
            flashDevInfo->readCmd.dataType           = SPI_QSPI_SFI_CH_XFER_CMD_6PIN_RD_QUAD;
            flashDevInfo->readCmd.numDataWords       = 64;
            flashDevInfo->readCmd.numPerDataWordbits = 32;
        }
    }

    return retVal;
}

boolean QSPIFlashLib_isDataRdCommand(uint32 cmd)
{
    boolean retVal = (boolean)FALSE;

    switch (cmd)
    {
        case QSPI_CMD_READ:
        case QSPI_CMD_FAST_QREAD:
        case QSPI_CMD_MICRON_READ_24:
        case QSPI_CMD_MICRON_QREAD_24:
            retVal = (boolean)TRUE;
            break;
        default:
            break;
    }
    return retVal;
}

static Std_ReturnType saveFlashCmd(QspiFlashLib_FlashCmdType *srcCmd, QspiFlashLib_FlashCmdType *destCmd)
{
    Std_ReturnType retVal = E_OK;
    if ((srcCmd == NULL) || (destCmd == NULL))
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    if (retVal == E_OK)
    {
        destCmd->numCmdBits         = srcCmd->numCmdBits;
        destCmd->cmd                = srcCmd->cmd;
        destCmd->numCmdDummyBits    = srcCmd->numCmdDummyBits;
        destCmd->numAddrBits        = srcCmd->numAddrBits;
        destCmd->addr               = srcCmd->addr;
        destCmd->numAddrDummyBits   = srcCmd->numAddrDummyBits;
        destCmd->dataType           = srcCmd->dataType;
        destCmd->numDataWords       = srcCmd->numDataWords;
        destCmd->numPerDataWordbits = srcCmd->numPerDataWordbits;
    }
    return retVal;
}

static Std_ReturnType QSPIFlashLib_SetDefaultFlashDevInfo(QspiFlashDevInfoType *flashDevInfo)
{
    Std_ReturnType retVal = E_OK;
    if (NULL == flashDevInfo)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        gQspiFlashDevInfo.flashType     = flashDevInfo->flashType;
        gQspiFlashDevInfo.qspiMode      = flashDevInfo->qspiMode;
        gQspiFlashDevInfo.qspiCs        = flashDevInfo->qspiCs;
        gQspiFlashDevInfo.qspiDataDelay = flashDevInfo->qspiDataDelay;
        gQspiFlashDevInfo.qspifrequency = flashDevInfo->qspifrequency;

        saveFlashCmd(&flashDevInfo->idCmd, &(gQspiFlashDevInfo.idCmd));
        saveFlashCmd(&flashDevInfo->readCmd, &gQspiFlashDevInfo.readCmd);
        saveFlashCmd(&flashDevInfo->writeCmd, &gQspiFlashDevInfo.writeCmd);
        saveFlashCmd(&flashDevInfo->sectorEraseCmd, &gQspiFlashDevInfo.sectorEraseCmd);
        saveFlashCmd(&flashDevInfo->fullEraseCmd, &gQspiFlashDevInfo.fullEraseCmd);
        saveFlashCmd(&flashDevInfo->flashStatusCmd, &gQspiFlashDevInfo.flashStatusCmd);
        saveFlashCmd(&flashDevInfo->writeEnableCmd, &gQspiFlashDevInfo.writeEnableCmd);
        saveFlashCmd(&flashDevInfo->writeEnableCmd, &gQspiFlashDevInfo.writeEnableCmd);
        saveFlashCmd(&flashDevInfo->flashCfgReadCmd, &gQspiFlashDevInfo.flashCfgReadCmd);
        saveFlashCmd(&flashDevInfo->flashCfgWriteCmd, &gQspiFlashDevInfo.flashCfgWriteCmd);
        gQspiFlashDevInfo.qspiFlashInitFxn = flashDevInfo->qspiFlashInitFxn;
    }
    return retVal;
}

QspiFlashLib_freqType QSPIFlashLib_GetQspiFreq(QspiFlashLib_deviceType flashType)
{
    QspiFlashLib_freqType qspifrequency;
    Spi_ClkMode           qspiMode;

    /* Initialize QSPI Mode */
    qspiMode = PlatformGetQspiMode();

    qspifrequency = QSPI_SCLK_FREQ_40MHz; /* default speed */
    /* Initialize QSPI clk frequency */
    if (flashType == DEVICE_TYPE_SPANSION_QSPI4)
    {
        /* Use default speed */
        AppUtils_printf("QSPIFlashLib_GetQspiFreq : %d\n\r", qspiMode);
    }
    return qspifrequency;
}

static void QSPI_SpansionFlashInit(QspiFlashLib_deviceType DeviceType, uint32 isAsync)
{
    if (DeviceType == DEVICE_TYPE_SPANSION_QSPI4)
    {
        QSPIFlashLib_QuadEnable(isAsync);
    }
}

static Spi_ClkMode PlatformGetQspiMode(void)
{
    return SPI_CLK_MODE_0;
}
