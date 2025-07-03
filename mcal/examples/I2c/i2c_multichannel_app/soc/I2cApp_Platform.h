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
/*Temperature result registers*/
#define TMP10X_RESULT_REG (0x0000U)

/*EEPROM start address*/
#define EEPROM_START_ADDRESS (0x00U)

/*EEPROM start message length*/
#define EEPROM_START_MESSAGE_LENGTH (0x01U)

#define EEPROM_MEM_ADDRESS (0x00U)

#define EEPROM_ADDR_SIZE (2U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void           I2c_appPlatformInit(void);
void           I2c_appPlatformDeInit(void);
Std_ReturnType I2c_Buffer_Setup(void);
Std_ReturnType I2cExample_ExternalTest_Data_Write_To_Slaves(Std_ReturnType BufferSetupReturnValue);
Std_ReturnType I2cExample_ExternalTest_Eeprom_address_pointer_reset(Std_ReturnType BufferSetupReturnValue);
Std_ReturnType I2cExample_ExternalTest_Receive_Data(void);
#ifdef __cplusplus
}
#endif

#endif /* #ifndef I2C_APP_PLATFORM_H_ */
