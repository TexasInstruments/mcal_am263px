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
 *  \file     app_utilsI2c.h
 *
 *  \brief    This file contains the I2C utiliy APIs to make it easy for any app
 *            to use I2C read/write operation.
 *
 */
#ifndef I2C_APP_H_
#define I2C_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cdd_I2c.h"
#include "Cdd_I2c_Irq.h"

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

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

Std_ReturnType I2c_utilsWrite(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                              uint16 size);
Std_ReturnType I2c_utilsRead(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pRdBuf,
                             uint16 size);
Std_ReturnType I2c_utilsWriteRead(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                                  uint8 *pRdBuf, uint16 wrSize, uint16 rdSize);
Std_ReturnType I2c_utilsWriteReadRestart(Cdd_I2c_HwUnitType hwUnitId, Cdd_I2c_AddressType deviceAddress, uint8 *pWrBuf,
                                         uint8 *pRdBuf, uint16 wrSize, uint16 rdSize);
void           I2c_utilsInterruptConfig(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef I2C_APP_H_ */
