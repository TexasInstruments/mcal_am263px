/* ======================================================================
 *   Copyright (C) 2025 Texas Instruments Incorporated
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
 *  \file     I2cApp_Platform.h
 *
 *  \brief    I2C platform specific header file
 *
 */
#ifndef I2C_APP_PLATFORM_H_
#define I2C_APP_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Flag to indicate if various I2C slaves are present in the board */
// TODO: Restart mode not working in interrupt mode. Enable temp sensor after the fix
#define I2C_APP_TMP_PRESENT      (STD_OFF)
#define I2C_APP_TMP_HW_UNIT      (CDD_I2C_HW_UNIT_2)
#define I2C_APP_TMP_ADDRESS      (0x4CU)
#define I2C_APP_EEPROM_PRESENT   (STD_ON)
#define I2C_APP_EEPROM_HW_UNIT   (CDD_I2C_HW_UNIT_0)
#define I2C_APP_EEPROM_ADDRESS   (0x50U)
#define I2C_APP_EEPROM_SIZE      (128U * 1024U)
#define I2C_APP_EEPROM_PAGE_SIZE (256U)
#define I2C_APP_EEPROM_NUM_PAGE  (I2C_APP_EEPROM_SIZE / I2C_APP_EEPROM_PAGE_SIZE)
#define I2C_APP_EEPROM_ADDR_SIZE (2U)
/* As per spec tWR (Write Cycle Time) is 5 ms */
#define I2C_APP_EEPROM_PROG_TIME_MS    (5U)
#define I2C_APP_EEPROM_BOARD_INFO_SIZE (32U)

/*
 * Sequence and channel IDs
 * Each HW unit has four sequences and 6 channels
 *      Seq 0: 1 WR only channel
 *      Seq 1: 1 RD only channel
 *      Seq 2: 1 WR channel and 1 RD channel with STOP in between
 *      Seq 4: 1 WR channel and 1 RD channel with NOSTOP in between (RESTART mode)
 */
#define I2C_APP_NUM_SEQ_PER_HW_UNIT (4U)
#define I2C_APP_NUM_CH_PER_HW_UNIT  (6U)
/* Sequence IDs */
#define I2C_APP_SEQ_ID_HW_UNIT_0_WR            (CddI2cConf_CddI2cSequence_CddI2cSequence_0)
#define I2C_APP_SEQ_ID_HW_UNIT_0_RD            (CddI2cConf_CddI2cSequence_CddI2cSequence_1)
#define I2C_APP_SEQ_ID_HW_UNIT_0_WR_RD         (CddI2cConf_CddI2cSequence_CddI2cSequence_2)
#define I2C_APP_SEQ_ID_HW_UNIT_0_WR_RD_RESTART (CddI2cConf_CddI2cSequence_CddI2cSequence_3)
#define I2C_APP_SEQ_ID_HW_UNIT_2_WR            (CddI2cConf_CddI2cSequence_CddI2cSequence_4)
#define I2C_APP_SEQ_ID_HW_UNIT_2_RD            (CddI2cConf_CddI2cSequence_CddI2cSequence_5)
#define I2C_APP_SEQ_ID_HW_UNIT_2_WR_RD         (CddI2cConf_CddI2cSequence_CddI2cSequence_6)
#define I2C_APP_SEQ_ID_HW_UNIT_2_WR_RD_RESTART (CddI2cConf_CddI2cSequence_CddI2cSequence_7)
/* Channel IDs */
#define I2C_APP_CH_ID_HW_UNIT_0_WR               (CddI2cConf_CddI2cChannel_CddI2cChannel_0)
#define I2C_APP_CH_ID_HW_UNIT_0_RD               (CddI2cConf_CddI2cChannel_CddI2cChannel_1)
#define I2C_APP_CH_ID_HW_UNIT_0_WR_RD_WR         (CddI2cConf_CddI2cChannel_CddI2cChannel_2)
#define I2C_APP_CH_ID_HW_UNIT_0_WR_RD_RD         (CddI2cConf_CddI2cChannel_CddI2cChannel_3)
#define I2C_APP_CH_ID_HW_UNIT_0_WR_RD_WR_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_4)
#define I2C_APP_CH_ID_HW_UNIT_0_WR_RD_RD_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_5)
#define I2C_APP_CH_ID_HW_UNIT_2_WR               (CddI2cConf_CddI2cChannel_CddI2cChannel_6)
#define I2C_APP_CH_ID_HW_UNIT_2_RD               (CddI2cConf_CddI2cChannel_CddI2cChannel_7)
#define I2C_APP_CH_ID_HW_UNIT_2_WR_RD_WR         (CddI2cConf_CddI2cChannel_CddI2cChannel_8)
#define I2C_APP_CH_ID_HW_UNIT_2_WR_RD_RD         (CddI2cConf_CddI2cChannel_CddI2cChannel_9)
#define I2C_APP_CH_ID_HW_UNIT_2_WR_RD_WR_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_10)
#define I2C_APP_CH_ID_HW_UNIT_2_WR_RD_RD_RESTART (CddI2cConf_CddI2cChannel_CddI2cChannel_11)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void I2c_appPlatformInit(void);
void I2c_appPlatformDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef I2C_APP_PLATFORM_H_ */
