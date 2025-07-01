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
 *  \file     Spi_Dbg.h
 *
 *  \brief    This file contains debug variable declaration for SPI MCAL driver
 *
 */

/**
 *  \ingroup MCAL_SPI_API
 *  @{
 */

#ifndef SPI_DBG_H_
#define SPI_DBG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

#if (STD_ON == SPI_JOB_LOG)
/**
 *  \brief SPI log structure per job entry
 */
typedef struct
{
    uint32           timeStamp;
    /**< Timestamp based on 32-kHz Synchronized Timer (COUNTER_32K) at which
     *   the job is scheduled */
    uint8            jobId;
    /**< Job ID of the scheduled job */
    Spi_SequenceType seqId;
    /**< Sequence ID to which the job belongs */
    Spi_HWUnitType   hwUnitId;
    /**< HWUnit associated with the job */
} Spi_JobLogEntryType;

/**
 *  \brief SPI job log structure
 */
typedef struct
{
    uint32              logIndex;
    /**< Current log index. This -1 points to the last log entry */
    uint32              totalLog;
    /**< Total log including wrapper around */
    Spi_JobLogEntryType logEntry[SPI_MAX_JOB_LOG];
    /**< Log entries */
} Spi_JobLogType;
#endif /* #if (STD_ON == SPI_JOB_LOG) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if (STD_ON == SPI_JOB_LOG)
/** \brief SPI job log object */
extern Spi_JobLogType Spi_JobLogObj;
#endif /* #if (STD_ON == SPI_JOB_LOG) */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SPI_DBG_H_ */

/* @} */
