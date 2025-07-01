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
 *  \file     appUtils_QSpiFlashLib.h
 *
 *  \brief    QSPI flash apis header file
 *
 */

#ifndef QSPI_FLASH_LIB_H_
#define QSPI_FLASH_LIB_H_

/*_______________________________ Include Files ______________________________*/

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Spi.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/*____________________________ Exported Definitions __________________________*/
/* Defines for all possible configuration IDs. */
#define QSPI_CONFIGID_CLOCKSPEED (0)
#define QSPI_CONFIGID_READCMD    (1)

#define QSPI_EXTERNAL_DEVICE_ID (0)

/*______________________________ Exported Types ______________________________*/

/* ========================================================================== */
/** qspi_DeviceType_e are the values for QSPI device type used for
 * configurations
 *
 *  @param    DEVICE_TYPE_QSPI4                Quad Fast read at 48 MHz
 *  @param    DEVICE_TYPE_QSPI1                Normal read at 12 MHz
 *
 */
typedef enum
{
    DEVICE_TYPE_QSPI4 = 0x01U,
    DEVICE_TYPE_QSPI1 = 0x02U,
    /* Spansion flash device type enum values are kept same as
     * default device types for compatibility */
    DEVICE_TYPE_SPANSION_QSPI4 = 0x01U,
    DEVICE_TYPE_SPANSION_QSPI1 = 0x02U,
    DEVICE_TYPE_MICRON_QSPI4   = 0x11U,
    DEVICE_TYPE_MICRON_QSPI1   = 0x12U,
    DEVICE_TYPE_CUSTOM         = 0xF0U
} QspiFlashLib_deviceType;

typedef void (*QSPI_flashInitFunPtr)(QspiFlashLib_deviceType DeviceType, uint32 isAsync);

/* ========================================================================== */
/** qspi_ClockFreq_e are the values for selecting flash clock frequency
 *
 *  @param    QSPI_SCLK_FREQ_40MHz            Select 40 MHz clock
 *  @param    QSPI_SCLK_FREQ_50MHz            Select 50 MHz clock
 *
 */
typedef enum
{
    QSPI_SCLK_FREQ_40MHz = 0x4U
} QspiFlashLib_freqType;

/* ========================================================================== */
/** qspi_ReadCommand_e are the values of QSPI commands
 *
 *  @param    QSPI_CMD_READ            Normal Read command
 *  @param    QSPI_CMD_RDSR
 *  @param    QSPI_CMD_WREN            Write enable command
 *  @param    QSPI_CMD_WRREG           Write register command
 *  @param    QSPI_CMD_WRITE           Normal write command
 *  @param    QSPI_CMD_FAST_READ       Fast read command
 *  @param    QSPI_CMD_FAST_DREAD      Fast dual read command
 *  @param    QSPI_CMD_FAST_QREAD      Fast quad read command
 *  @param    QSPI_CMD_MFGID           Read manufacturer Id command
 *  @param    QSPI_CMD_BLKERASE        Block Erase command
 *  @param    QSPI_CMD_PAGEERASE       Page Erase command
 *  @param    QSPI_CMD_FULLERASE       Full Flash Erase command
 *
 */
/* QSPI READ CMD */
typedef enum
{
    QSPI_CMD_READ_24       = 0x03,
    QSPI_CMD_READ          = 0x13,
    QSPI_CMD_RDSR          = 0x05,
    QSPI_CMD_RDSR2         = 0x07,
    QSPI_CMD_RDCR          = 0x35,
    QSPI_CMD_WREN          = 0x06,
    QSPI_CMD_WRREG         = 0x01,
    QSPI_CMD_WRITE_24      = 0x02,
    QSPI_CMD_WRITE         = 0x12,
    QSPI_CMD_FAST_READ_24  = 0x0B,
    QSPI_CMD_FAST_READ     = 0x0C,
    QSPI_CMD_FAST_DREAD_24 = 0x3B,
    QSPI_CMD_FAST_DREAD    = 0x3C,
    QSPI_CMD_FAST_QREAD_24 = 0x6B,
    QSPI_CMD_FAST_QREAD    = 0x6C,
    QSPI_CMD_MFGID         = 0x90,
    QSPI_CMD_MFGID_AR      = 0x9F,
    QSPI_CMD_BLKERASE_24   = 0xD8,
    QSPI_CMD_BLKERASE      = 0xDC,
    QSPI_CMD_PAGEERASE     = 0x20,
    QSPI_CMD_FULLERASE     = 0x60,

    /* Micron flash commands */
    QSPI_CMD_MICRON_READ_24     = 0x03,
    QSPI_CMD_MICRON_RDSR        = 0x05,
    QSPI_CMD_MICRON_QREAD_24    = 0x6B,
    QSPI_CMD_MICRON_WRITE_24    = 0x02,
    QSPI_CMD_MICRON_MFGID       = 0x9E,
    QSPI_CMD_MICRON_WREN        = 0x06,
    QSPI_CMD_MICRON_BLKERASE_24 = 0xD8,
    QSPI_CMD_MICRON_FULLERASE   = 0xC7
} QspiFlashLib_ReadCommandType;

/* QSPI CR WLEN : 128 bits is not supported for tda3xx platform*/
typedef enum
{
    QSPI_CR_WLEN_1_BIT    = 0x0,  /* 1 bit   */
    QSPI_CR_WLEN_8_BITS   = 0x7,  /* 8 bits  */
    QSPI_CR_WLEN_16_BITS  = 0xF,  /* 16 bits */
    QSPI_CR_WLEN_24_BITS  = 0x17, /* 24 bits */
    QSPI_CR_WLEN_32_BITS  = 0x1F, /* 32 bits */
    QSPI_CR_WLEN_128_BITS = 0x7F  /* 128 bits*/
} QspiFlashLink_CrWlenType;

/* QSPI CR FLEN  */
typedef enum
{
    QSPI_CR_FLEN_1_WORD = 0x0, /* 1 word  */
    QSPI_CR_FLEN_2_WORDS,      /* 2 words */
    QSPI_CR_FLEN_3_WORDS,      /* 3 words */
    QSPI_CR_FLEN_4_WORDS,      /* 4 words */
    QSPI_CR_FLEN_5_WORDS,      /* 5 words */
    QSPI_CR_FLEN_6_WORDS,      /* 6 words */
    QSPI_CR_FLEN_7_WORDS,      /* 7 words */
    QSPI_CR_FLEN_8_WORDS       /* 8 words */
} QspiFlashLib_CrFrameLenType;

/** Values of qspi_ClockFreq_e are combination of input clock select value and
 *  Clock devide value.
 *
 *  @def    QSPI_CLKSWITCH_MASK            - Mask value to get input clock value
 *  @def    QSPI_CLKDIVIDER_MASK           - Mask value to get clock devide
 *                                           value
 *
 */
#define QSPI_CLKSWITCH_MASK  0xF0U
#define QSPI_CLKDIVIDER_MASK 0x0FU

/* Configuration descriptor type. */
typedef struct
{
    uint32 ConfigId;
    uint32 Value;
} QspiFlashLib_ConfigDescType;

typedef struct
{
    uint32                numCmdBits;
    uint32                cmd;
    uint32                numCmdDummyBits;
    uint32                numAddrBits;
    uint32                addr;
    uint32                numAddrDummyBits;
    Spi_QspiChXferCmdType dataType;
    uint32                numPerDataWordbits;
    uint32                numDataWords;
    uint32                seqId;
} QspiFlashLib_FlashCmdType;

typedef struct
{
    QspiFlashLib_deviceType   flashType;
    uint32                    numDatalines;
    Spi_ClkMode               qspiMode;
    uint32                    qspiCs;
    Spi_DataDelayType         qspiDataDelay;
    QspiFlashLib_freqType     qspifrequency;
    QspiFlashLib_FlashCmdType idCmd;
    QspiFlashLib_FlashCmdType readCmd;
    QspiFlashLib_FlashCmdType writeCmd;
    QspiFlashLib_FlashCmdType sectorEraseCmd;
    QspiFlashLib_FlashCmdType fullEraseCmd;
    QspiFlashLib_FlashCmdType flashStatusCmd;
    QspiFlashLib_FlashCmdType writeEnableCmd;
    QspiFlashLib_FlashCmdType flashCfgReadCmd;
    QspiFlashLib_FlashCmdType flashCfgWriteCmd;
    QSPI_flashInitFunPtr      qspiFlashInitFxn;
} QspiFlashDevInfoType;
extern QspiFlashDevInfoType gQspiFlashDevInfo;
#define QSPIFLASH_SECTORSIZE (4U * 1024U)

/** \brief Generate 1010 pattern data to analyze of CRO */
#define SPI_TEST_WAVEFORM_ANALYSIS (1U)
extern volatile uint32 gQspiJobDone[SPI_MAX_JOBS], gQspiSeqDone[SPI_MAX_SEQ];

Std_ReturnType QSPIFlashLib_executeCmd(QspiFlashLib_FlashCmdType flashCmd, uint32 *data, uint32 isAsync);

uint32 QSPIFlashLib_Initialize(QspiFlashLib_deviceType DeviceType, Spi_ConfigType *spiCfg,
                               Spi_SeqEndNotifyType seqEndNotify, Spi_JobEndNotifyType jobEndNotify,
                               uint32 qspiEnableMemMapModeFlag, uint32 memMapReadWidth, uint32 isAsync);

uint32 QSPIFlashLib_ReadSectors(void *dstAddr, const void *srcOffsetAddr, uint32 length);

uint32 QSPIFlashLib_Configure(uint32 ConfigId, uint32 ConfigValue);

uint32 QSPIFlashLib_WriteSectors(uint32 srcAddr, uint32 dstOffsetAddr, uint32 length);

uint32 QSPIFlashLib_WriteSectorsNonBlocking(uint32 srcAddr, uint32 dstOffsetAddr, uint32 length);

void QSPIFlashLib_WriteCfgMode(uint32 dstOffsetAddr, uint32 srcAddr, uint32 length, uint32 isAsync);

void QSPIFlashLib_WriteCfgModeNonBlocking(uint32 dstOffsetAddr, uint32 srcAddr, uint32 length, uint32 isAsync);

uint32 QSPIFlashLib_GetDeviceId(uint32 isAsync);

uint32 QSPIFlashLib_GetDeviceIdExtended(uint32 numSpiWords, uint32 *data, uint32 isAsync);

void QSPIFlashLib_ReadCfgMode(uint32 dstAddr, uint32 srcOffsetAddr, uint32 length, uint32 isAsync);
void QSPIFlashLib_ReadMemMode(uint32 dstAddr, uint32 srcOffsetAddr, uint32 length);
void QSPIFlashLib_WriteMemMode(uint32 dstOffsetAddr, uint32 srcAddr, uint32 length);

void QSPIFlashLib_MemMapReadCfgMode(uint32 dstAddr, uint32 srcOffsetAddr, uint32 length);

uint32 QSPIFlashLib_ReadMID(void);

uint32 QSPIFlashLib_FlashStatus(uint32 isAsync);

void QSPIFlashLib_WriteEnable(uint32 isAsync);

void QSPIFlashLib_QuadEnable(uint32 isAsync);

void QSPIFlashLib_QuadEnableNonBlocking(uint32 isAsync);

void QSPIFlashLib_FlashBlockErase(uint32 blkNo, uint32 isAsync);

void QSPIFlashLib_FlashBlockEraseNonBlocking(uint32 blkNo, uint32 isAsync);

void QSPIFlashLib_FlashFullErase(uint32 isAsync);

void QSPIFlashLib_FlashFullEraseNonBlocking(uint32 isAsync);

void                  QSPIFlashLib_seek(uint32 *srcAddr, uint32 location);
QspiFlashLib_freqType QSPIFlashLib_GetQspiFreq(QspiFlashLib_deviceType flashType);

void AppUtils_generateData(uint8 *srcAddr, uint32 length, uint32 chdataWidth);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* QSPI_FLASH_LIB_H_ */
