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
 * \file     Cdd_I2c_Irq.h
 *
 * \brief    This file contains ISR function declaration for CDD_I2C MCAL
 *
 */

#ifndef CDD_I2C_IRQ_H_
#define CDD_I2C_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_I2c.h"
#include "Os.h"

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

#if (STD_OFF == CDD_I2C_POLLING_MODE)

#if defined(CDD_I2C_HW_UNIT_0_ACTIVE)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit0_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit0_ISR);
#endif
#endif

#if defined(CDD_I2C_HW_UNIT_1_ACTIVE)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit1_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit1_ISR);
#endif
#endif

#if defined(CDD_I2C_HW_UNIT_2_ACTIVE)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit2_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit2_ISR);
#endif
#endif

#if defined(CDD_I2C_HW_UNIT_3_ACTIVE)
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit3_ISR(void);
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit3_ISR);
#endif
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif
