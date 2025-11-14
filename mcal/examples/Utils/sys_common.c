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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

typedef volatile uint32 REG32;
#define M_REG_WRITE32(w_addr, w_data) (*((REG32 *)((w_addr)))) = ((uint32)((w_data)))
#define M_REG_READ32(w_addr)          (*((REG32 *)((w_addr))))

/*! \brief
 * Generates a pattern of ones between end bit and start bit
 * M_ONES(7,4) will give 0x000000F0
 */
#define M_ONES(c_ebit, c_sbit) (((1U << (((c_ebit) - (c_sbit)) + 1U)) - 1U) << (c_sbit))

/*! \brief
 * Generates a pattern of zeros between end bit and start bit
 * M_MASK(7,4) will give 0xFFFFFF0F
 */
#define M_MASK(c_ebit, c_sbit) (~(M_ONES((c_ebit), (c_sbit))))

/*! \brief
 * Bounds the value before writing to register
 * M_VAL_BOUND(0x1F, 7, 4) will remove the extra bit resulting in 0xF
 * TODO: Generate a warning if extra bit found
 */
#define M_VAL_BOUND(val, c_ebit, c_sbit) ((M_ONES((c_ebit), (c_sbit)) >> (c_sbit)) & (uint32)(val))

/*! \brief
 * 32 bit register field read - bit fields input
 */
#define M_REG_BITS_READ32(w_addr, c_ebit, c_sbit) \
    (((M_REG_READ32((w_addr))) & (M_ONES((c_ebit), (c_sbit)))) >> (c_sbit))

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
