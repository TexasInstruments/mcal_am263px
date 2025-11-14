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
 *  \file     Cdd_I2c_Irq.c
 *
 *  \brief    This file contains the ISR implementation of CDD_I2C MCAL
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_I2c.h"
#include "Cdd_I2c_Irq.h"
#include "Cdd_I2c_Priv.h"
#include "Cdd_I2c_Hw.h"

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

/* None */

/* ========================================================================== */
/*                        Local Object Definitions                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define CDD_I2C_START_SEC_CODE
#include "Cdd_I2c_MemMap.h"

#if defined(CDD_I2C_HW_UNIT_0_ACTIVE)
__attribute__((target("arm")))
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit0_ISR(void)
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit0_ISR)
#endif
{
    Cdd_I2c_ProcessIsr(CDD_I2C_HW_UNIT_0);
    return;
}
#endif

#if defined(CDD_I2C_HW_UNIT_1_ACTIVE)
__attribute__((target("arm")))
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit1_ISR(void)
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit1_ISR)
#endif
{
    Cdd_I2c_ProcessIsr(CDD_I2C_HW_UNIT_1);
    return;
}
#endif

#if defined(CDD_I2C_HW_UNIT_2_ACTIVE)
__attribute__((target("arm")))
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit2_ISR(void)
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit2_ISR)
#endif
{
    Cdd_I2c_ProcessIsr(CDD_I2C_HW_UNIT_2);
    return;
}
#endif

#if defined(CDD_I2C_HW_UNIT_3_ACTIVE)
__attribute__((target("arm")))
#if ((CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT1) || (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_VOID))
FUNC(void, CDD_I2C_CODE_FAST) Cdd_I2c_HwUnit3_ISR(void)
#elif (CDD_I2C_ISR_TYPE == CDD_I2C_ISR_CAT2)
ISR(Cdd_I2c_HwUnit3_ISR)
#endif
{
    Cdd_I2c_ProcessIsr(CDD_I2C_HW_UNIT_3);
    return;
}
#endif

#define CDD_I2C_STOP_SEC_CODE
#include "Cdd_I2c_MemMap.h"
