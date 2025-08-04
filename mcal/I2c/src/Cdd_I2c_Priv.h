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
 *  \file     Cdd_I2c_Priv.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the I2C MCAL driver files.
 *
 */

#ifndef CDD_I2C_PRIV_H_
#define CDD_I2C_PRIV_H_

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "SchM_Cdd_I2c.h"
#include "Cdd_I2c.h"
#include "Cdd_I2c_Utils.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */
/*                               Macros                             */
/* ================================================================ */

/** \brief Maximum possible 10 bit address */
#define CDD_I2C_ADDRESS_10_BIT_MAX (1023U)
/** \brief Maximum possible 7 bit address */
#define CDD_I2C_ADDRESS_7_BIT_MAX (127U)

/* ================================================================ */
/*                         Structures and Enums                     */
/* ================================================================ */

/** \brief Pre-declaration for HW unit object */
typedef struct Cdd_I2c_HwUnitObjType_t Cdd_I2c_HwUnitObjType;

/**
 *  \brief I2C Sequence object structure.
 */
typedef struct
{
    const Cdd_I2c_SequenceConfigType *seqCfg;
    /**< I2C sequence config passed during init */
    Cdd_I2c_SequenceType              sequenceId;
    /**< I2C sequence ID. This is used for easy de-referencing */
    Cdd_I2c_HwUnitObjType            *hwUnitObj;
    /**< I2C HW unit object as ID and array index may not be same.
     *   This is used for easy de-referencing */
    Cdd_I2c_SequenceResultType        seqResult;
    /**< I2C sequence result/status */
    uint8                             seqErrorCode;
    /**< I2C sequence error code */
    uint32                            numChsPending;
    /**< Number of chs still pending. Used for notifying sequence end */
} Cdd_I2c_SeqObjType;

/**
 *  \brief I2C Channel object structure.
 */
typedef struct
{
    const Cdd_I2c_ChConfigType *chCfg;
    /**< I2C ch config passed during init */
    Cdd_I2c_ChannelType         chId;
    /**< I2C channel ID. This is used for easy de-referencing */
    Cdd_I2c_SeqObjType         *seqObj;
    /**< I2C sequence object pointer to which the ch belongs.
     *   This is used for easy de-referencing */
    Cdd_I2c_HwUnitObjType      *hwUnitObj;
    /**< I2C HW unit object as ID and array index may not be same.
     *   This is used for easy de-referencing */
    Cdd_I2c_UtilsNode           nodeObj;
    /**< Node object used for node memory to be used in link list */
    Cdd_I2c_DataConstPtrType    txBufPtr;
    /**< TX buffer pointer given by user. This should be persistent */
    Cdd_I2c_DataPtrType         rxBufPtr;
    /**< RX buffer pointer given by user. This should be persistent */
    Cdd_I2c_DataLengthType      length;
    /** \brief The address of a target device which is accessed by the Controller */
    Cdd_I2c_AddressType         deviceAddress;
    /** \brief 7-bit or 10-bit addressing */
    uint8                       addressScheme;
    /**< Number of words to transfer given by user */
    Cdd_I2c_ChannelResultType   chResult;
    /**< I2C channel result/status */
    Cdd_I2c_ChannelResultType   chErrorCode;
    /**< I2C channel error - temp variable to store intermediate errors and
     *   passed to channel result at channel completion */
    Cdd_I2c_DataConstPtrType    curTxBufPtr;
    /**< Current TX buffer pointer */
    Cdd_I2c_DataPtrType         curRxBufPtr;
    /**< Current RX buffer pointer */
    Cdd_I2c_DataLengthType      curLength;
    /**< Number of words transferred */
    boolean                     isStopRequired;
    /**< Flag to indicate whether to perform stop at end of channel transfer */
    boolean                     doBusyCheck;
    /**< Flag to indicate whether to perform bus busy check at start of channel transfer */
} Cdd_I2c_ChObjType;

/**
 *  \brief I2C Hardware unit object structure.
 */
struct Cdd_I2c_HwUnitObjType_t
{
    const Cdd_I2c_HwUnitConfigType *hwUnitCfg;
    /**< I2C HW unit config passed during init */
    uint32                          baseAddr;
    /**< Base address of the hardware */
    Cdd_I2c_UtilsLinkListObj        llobj;
    /**< Ch link list per hardware */
    Cdd_I2c_ChObjType              *curChObj;
    /**< When hardware is busy, this points to the current ch that
     *   is in progress. When hardware is idle, this will be NULL */
    Cdd_I2c_HwUnitStatusType        hwUnitStatus;
    /**< SPI HW unit result/status */
};

/**
 *  \brief I2C driver object structure.
 */
typedef struct
{
    uint8                 maxCh;
    /**< Maximum number of channels */
    uint8                 maxSeq;
    /**< Maximum number of sequences */
    uint8                 maxHwUnit;
    /**< Maximum number of HW unit */
    Cdd_I2c_ChObjType     chObj[CDD_I2C_MAX_CH];
    /**< I2C ch objects */
    Cdd_I2c_SeqObjType    seqObj[CDD_I2C_MAX_SEQ];
    /**< I2C sequence objects */
    Cdd_I2c_HwUnitObjType hwUnitObj[CDD_I2C_MAX_HW_UNIT];
    /**< I2C hw unit objects */
} Cdd_I2c_DriverObjType;

/* ================================================================ */
/*                          Function Declarations                   */
/* ================================================================ */

Std_ReturnType Cdd_I2c_startSeqAsync(Cdd_I2c_DriverObjType *drvObj, Cdd_I2c_SeqObjType *seqObj);

#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
Std_ReturnType Cdd_I2c_checkConfig(const Cdd_I2c_ConfigType *configPtr);
#endif
void Cdd_I2c_resetDrvObj(Cdd_I2c_DriverObjType *drvObj);
void Cdd_I2c_copyConfig(Cdd_I2c_DriverObjType *drvObj, const Cdd_I2c_ConfigType *configPtr);

void Cdd_I2c_processIsr(Cdd_I2c_HwUnitType hwUnitId);
void Cdd_I2c_processEvents(Cdd_I2c_DriverObjType *drvObj, Cdd_I2c_HwUnitObjType *hwUnitObj);

uint32                 Cdd_I2c_getHwUnitBaseAddr(Cdd_I2c_HwUnitType hwUnitId);
Cdd_I2c_HwUnitObjType *Cdd_I2c_getHwUnitObj(Cdd_I2c_DriverObjType *drvObj, Cdd_I2c_HwUnitType hwUnitId);

/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

extern Cdd_I2c_ComponentStatusType Cdd_I2c_DrvState;
extern Cdd_I2c_DriverObjType       Cdd_I2c_DrvObj;

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_I2C_PRIV_H_ */
