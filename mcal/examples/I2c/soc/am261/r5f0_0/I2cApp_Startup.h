/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Protection against multiple inclusion */
#ifndef I2CAPP_STARTUP_H_
#define I2CAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "app_utils.h"
#include "sys_common.h"
#include "hw_types.h"
#include "sys_vim.h"
#include "Cdd_I2c_Irq.h"
#include "Mcu.h"
#include "Cdd_I2c.h"
#include "EcuM_Cbk.h"
#include "Port.h"

#if (STD_OFF == CDD_I2C_POLLING_MODE)
#include "Cdd_I2c_Irq.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "I2cApp"

/*EEPROM start address*/
#define EEPROM_START_ADDRESS (0x00U)

/*EEPROM start message length*/
#define EEPROM_START_MESSAGE_LENGTH (0x01U)

#define EEPROM_MEM_ADDRESS (0x00U)

#define EEPROM_ADDR_SIZE (2U)

/* ========================================================================== */
/*                           Global variables                                 */
/* ========================================================================== */

/* Global pointer pointing to NULL to be passed as argument in Cdd_I2c_Init */
extern Cdd_I2c_ConfigPtrType I2cConfigSet;

/* MCU configuration for I2C application */
extern Mcu_ClockConfigType gI2cAppMcuClockConfig[];

extern volatile boolean rxDoneEeprom;

extern uint8 txBufferEeprom[32];
extern uint8 txBufferEepromStart[2];
extern uint8 rxBufferEeprom[26];

#if (STD_OFF == MCU_NO_PLL)
extern CONST(Mcu_ConfigType, MCU_PBCFG) McuModuleConfiguration;
#endif

/* ========================================================================== */
/*                           Function Declarations                            */
/* ========================================================================== */
void           Cdd_I2cApp_Startup(void);
void           Cdd_I2c_InterruptConfig(void);
void           Cdd_I2c_App_PlatformInit(void);
Std_ReturnType I2c_Buffer_Setup(void);
Std_ReturnType I2cExample_ExternalTest_Data_Write_To_Slaves(Std_ReturnType BufferSetupReturnValue);
Std_ReturnType I2cExample_ExternalTest_Eeprom_address_pointer_reset(Std_ReturnType BufferSetupReturnValue);
Std_ReturnType I2cExample_ExternalTest_Receive_Data(void);

#if (STD_ON == CDD_I2C_VERSION_INFO_API)
void Print_I2c_Version_Info(Std_VersionInfoType* versionInfoPtr);
#endif

#if (STD_ON == CDD_I2C_VERSION_INFO_API)
void Print_I2c_Version_Info(Std_VersionInfoType* versionInfoPtr);
#endif

#endif
