/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
// TODO: ENabling temp sensor in AM261x board needs PMIC LDO programming. Enable after this is done
#define I2C_APP_TMP_PRESENT      (STD_OFF)
#define I2C_APP_TMP_HW_UNIT      (CDD_I2C_HW_UNIT_MAX)
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
