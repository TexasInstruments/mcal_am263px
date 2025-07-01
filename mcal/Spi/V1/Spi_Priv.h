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
 *  \file     Spi_Priv.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the SPI MCAL driver files.
 *
 */

#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "SchM_Spi.h"
#include "Spi_Utils.h"
#include "hw_Mibspi.h"

#if (STD_ON == SPI_DEV_ERROR_DETECT)
#include "Det.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Pre-declaration for HW unit object */
typedef struct Spi_HwUnitObjType_t Spi_HwUnitObjType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief SPI Channel object structure.
 */

typedef struct
{
    Spi_ChannelConfigType chCfg;
    /**< SPI channel config passed during init */
    P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) txBufPtr;
    /**< TX buffer pointer given by user. This should be persistent */
    P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) rxBufPtr;
    /**< RX buffer pointer given by user. This should be persistent */
    Spi_NumberOfDataType numWordsTxRx;
    /**< Number of words to transfer */

    const uint8         *curTxBufPtr;
    /**< Current TX buffer pointer */
    uint8               *curRxBufPtr;
    /**< Current RX buffer pointer */
    Spi_NumberOfDataType curTxWords;
    /**< Number of words transmitted. We need seperate counters for TX/RX
     *   because when FIFO in enabled, TX writes happen in advance where as
     *   RX will happen on actual received data. */
    Spi_NumberOfDataType curRxWords;
    /**< Number of words received */
    uint8                bufWidth;
    /**< Width of buffer in bits - used for accessing the TX/RX buffer.
     *   When dataWidth < 9,           bufWidth = uint8
     *   When dataWidth >= 9  && < 17, bufWidth = uint16
     *   When dataWidth >= 17 && < 33, bufWidth = uint32
     */
    uint32               effTxFifoDepth;
    /**< Effective TX FIFO depth in words - depends on dataWidth */
} Spi_ChannelObjType;

/**
 *  \brief SPI Sequence object structure.
 */
typedef struct
{
    Spi_SeqConfigType seqCfg;
    /**< SPI sequence config passed during init */
    Spi_SeqResultType seqResult;
    /**< SPI sequence result/status */
    uint32            numJobsPending;
    /**< Number of jobs still pending. Used for notifying sequence end */
} Spi_SeqObjType;

/**
 *  \brief SPI Job object structure.
 */
typedef struct
{
    Spi_JobConfigType             jobCfg;
    /**< SPI job config passed during init */
    Spi_ExternalDeviceConfigType *extDevCfg;
    /**< SPI job config passed during init */
    Spi_JobResultType             jobResult;
    /**< SPI job result/status */
    Spi_HwUnitObjType            *hwUnitObj;
    /**< SPI HW unit object as ID and array index may not be same.
     *   This is used for easy de-referencing */
    Spi_SeqObjType               *seqObj;
    /**< SPI sequence object pointer to which the job belongs.
     *   This is used for easy de-referencing */
    Spi_UtilsNode                 nodeObj;
    /**< Node object used for node memory to be used in link list */
    uint32                        curChIdx;
    /**< Current channel index. Used for notifying job end */
    uint32                        txFifoTrigLvl;
    /**< TX FIFO trigger level in bytes */
    uint32                        rxFifoTrigLvl;
    /**< RX FIFO trigger level in bytes */
    boolean                       IsAdd;
    /**< Boolean for checking that we have already come accross the Address part */
    boolean                       IsData;
    /**< Boolean for checking that we have already come accross the Data part */
    boolean                       IsCmd;
    /**< Boolean for checking that we have already come accross the Command part */
    uint32                        wordNum;
    /**< Parameter to just track of the current channel on which we are */
    uint32                        pointerShifter;
    /**< Parameter to have shift for our write */
} Spi_JobObjType;

/**
 *  \brief SPI Hardware unit object structure.
 */
struct Spi_HwUnitObjType_t
{
    Spi_HwUnitConfigType hwUnitCfg;
    /**< SPI HW unit config passed during init */
    Spi_HwUnitResultType hwUnitResult;
    /**< SPI HW unit result/status */
    uint32               baseAddr;
    /**< Base address of the hardware */
    uint32               isQspiUnit;
    /**< Whether the unit is QSPI or McSPI: TRUE-QSPI, FALSE MiBSPI */
    Spi_UtilsLinkListObj jobList;
    /**< Job link list per hardware */
    Spi_JobObjType      *curJobObj;
    /**< When hardware is busy, this points to the current job that is in
     *   progress. When hardware is idle, this will be NULL */
    uint8                curConfiguredJobId;
    /**< Currently configured job ID. Used to avoid re-configuring the hardware
     *   again when the same job ID is used back to back */
    boolean              lpbkEnable;
    /**< Loopback enable/disable flag */
};

/**
 *  \brief SPI driver object structure.
 */
typedef struct
{
    uint32                       isAsynInProgress;
    /**< Flag to indicate any async transfer is in progress */
    Spi_AsyncModeType            asyncMode;
    /**< Aysnc mode set by user */
    uint8                        maxChannels;
    /**< Maximum number of channels.
     *   Should not be more than SPI_MAX_CHANNELS */
    uint8                        maxJobs;
    /**< Maximum number of jobs
     *   Should not be more than SPI_MAX_JOBS */
    uint8                        maxSeq;
    /**< Maximum number of sequences
     *   Should not be more than SPI_MAX_SEQ */
    uint8                        maxHwUnit;
    /**< Maximum number of HW unit
     *   Should not be more than SPI_MAX_HW_UNIT */
    uint8                        maxExtDevCfg;
    /**< Maximum number of external device configurations
     *   Should not be more than SPI_MAX_EXT_DEV */
    uint8                        Spi_MaxDlcs;
    /**< Maximum number of dlc's */
    Spi_ChannelObjType           channelObj[SPI_MAX_CHANNELS];
    /**< SPI channel objects */
    Spi_JobObjType               jobObj[SPI_MAX_JOBS];
    /**< SPI job objects */
    Spi_SeqObjType               seqObj[SPI_MAX_SEQ];
    /**< SPI sequence objects */
    Spi_HwUnitObjType            hwUnitObj[SPI_MAX_HW_UNIT];
    /**< SPI hw unit objects */
    Spi_ExternalDeviceConfigType extDevCfg[SPI_MAX_EXT_DEV];
    /**< External HW device config */
} Spi_DriverObjType;

extern Spi_DriverObjType Spi_DrvObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void Spi_hwUnitInit(Spi_HwUnitObjType *hwUnitObj);
void Spi_hwUnitDeInit(Spi_HwUnitObjType *hwUnitObj);

Std_ReturnType Spi_startSeqAsync(Spi_SeqObjType *seqObj);
Std_ReturnType Spi_startSeqSync(Spi_SeqObjType *seqObj);
#if (STD_ON == SPI_CANCEL_API)
void Spi_cancelSequence(Spi_SeqObjType *seqObj);
#endif /* #if (STD_ON == SPI_CANCEL_API) */

void Spi_processEvents(Spi_HwUnitObjType *hwUnitObj);

Spi_HwUnitObjType *Spi_getHwUnitObj(Spi_HWUnitType HWUnit);
void               Spi_resetDrvObj(Spi_DriverObjType *drvObj);
#if (STD_ON == SPI_DEV_ERROR_DETECT)
Std_ReturnType Spi_checkConfig(const Spi_ConfigType *cfgPtr);
#endif /* #if (STD_ON == SPI_DEV_ERROR_DETECT) */
void   Spi_copyConfig(Spi_DriverObjType *drvObj, const Spi_ConfigType *cfgPtr);
uint32 Spi_getHwUnitBaseAddr(Spi_HWUnitType hwUnitId);
uint32 Spi_getDataWidthBitMask(uint32 dataWidth);

/* QSPI related functions */
void Spi_qspiInit(const Spi_HwUnitObjType *hwUnitObj);
void Spi_qspiDeInit(const Spi_HwUnitObjType *hwUnitObj);
void Spi_qspiConfigJob(const Spi_HwUnitObjType *hwUnitObj, const Spi_JobObjType *jobObj);
void Spi_qspiConfigJobAsync(const Spi_HwUnitObjType *hwUnitObj, const Spi_JobObjType *jobObj);
void Spi_AsyncIntrDisable(uint32 baseAddr);
void Spi_qspiConfigCh(Spi_ChannelObjType *chObj);

void              Spi_qspiClearAllIrqStatus(uint32 baseAddr);
Spi_JobResultType Spi_qspiXferJob(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                  Spi_ChannelObjType chList[]);
Spi_JobResultType Spi_qspiXferJobAsync(const Spi_HwUnitObjType *hwUnitObj, Spi_JobObjType *jobObj,
                                       Spi_ChannelObjType chList[]);

#if (STD_ON == SPI_REGISTER_READBACK_API)
FUNC(Std_ReturnType, SPI_CODE)
Spi_HWRegisterReadback(Spi_HWUnitType HWUnit, P2VAR(Spi_RegisterReadbackType, AUTOMATIC, SPI_APPL_DATA) RegRbPtr);
void Spi_qspiRegReadback(const Spi_HwUnitObjType *hwUnitObj, Spi_RegisterReadbackType *RegRbPtr);

#endif /* #if (STD_ON == SPI_REGISTER_READBACK_API) */

void Spi_processJobCompletion(Spi_JobObjType *jobObj, Spi_HwUnitObjType *hwUnitObj, Spi_JobResultType jobResult);

uint32 Spi_CheckInitDet(P2CONST(Spi_ConfigType, AUTOMATIC, SPI_PBCFG) ConfigPtr);
FUNC(void, SPI_CODE) Spi_SetValIfCSActive(Spi_RegisterPtrType MReg_pt, uint32 CSVal_u32);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

/** \brief SPI driver status */
extern volatile Spi_StatusType Spi_DrvStatus;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SPI_PRIV_H_ */
