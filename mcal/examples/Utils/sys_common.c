/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     sys_common.c
 *
 *  \brief    This file contains HW read/write functions used when dynamic
 *            analysis build is enabled. This is needed to avoid getting
 *            non-coverage for HW static inline functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "stdio.h"
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "hw_types.h"
#include "sys_common.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32 registerReadWrite_local(volatile uint32 *regAddr, uint32 endBit, uint32 startBit, uint32 wrValue)
{
    uint32 readVal  = 0U;
    uint32 wrStatus = 0U;
    uint32 maskedWrValue;

    if ((endBit == 31U) && (startBit == 0U))
    {
        /* Write */
        M_REG_WRITE32(regAddr, wrValue);

        /* Read Back */
        readVal = M_REG_READ32(regAddr);

        /* Set Status */
        wrStatus = readVal ^ wrValue;
    }
    else
    {
        /* Read Register */
        readVal = M_REG_READ32(regAddr);

        maskedWrValue =
            (readVal & (uint32)M_MASK(endBit, startBit)) | ((uint32)M_VAL_BOUND(wrValue, endBit, startBit) << startBit);

        /* Write */
        M_REG_WRITE32(regAddr, maskedWrValue);

        /* Read Back */
        readVal = (uint32)M_REG_BITS_READ32(regAddr, endBit, startBit);

        /* Set Status */
        wrStatus = readVal ^ wrValue;
    }

    return wrStatus;
}
