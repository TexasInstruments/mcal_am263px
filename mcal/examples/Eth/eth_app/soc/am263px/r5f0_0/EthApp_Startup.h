/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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

/* Protection against multiple inclusion */
#ifndef ETHAPP_STARTUP_H_
#define ETHAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "app_utilsEth.h"
#include "sys_common.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define TCA6416_PORT0_INPUT_REG  0x00
#define TCA6416_PORT1_INPUT_REG  0x01
#define TCA6416_PORT0_OUTPUT_REG 0x02
#define TCA6416_PORT1_OUTPUT_REG 0x03
#define TCA6416_PORT0_DIR_REG    0x06
#define TCA6416_PORT1_DIR_REG    0x07
#define TCA6416_P(n)             (1 << (n))

#define TCA6424_PORT0_INPUT_REG  0x00
#define TCA6424_PORT1_INPUT_REG  0x01
#define TCA6424_PORT2_INPUT_REG  0x02
#define TCA6424_PORT0_OUTPUT_REG 0x04
#define TCA6424_PORT1_OUTPUT_REG 0x05
#define TCA6424_PORT2_OUTPUT_REG 0x06
#define TCA6424_PORT0_DIR_REG    0x0c
#define TCA6424_PORT1_DIR_REG    0x0d
#define TCA6424_PORT2_DIR_REG    0x0e
#define TCA6424_P(n)             (1 << (n))

// #define ETH_BOARD_REVISION_E1        (1u)

void EthApp_Startup(void);
void EthApp_TrcvInit(void);

#endif
