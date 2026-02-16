/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2024 Texas Instruments Incorporated
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
 *  \file     Spi_Irq.c
 *
 *  \brief    This file contains the ISR implementation of SPI MCAL
 *    driver
 *
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */
#include "Spi.h"
#include "Spi_Irq.h"
#include "Spi_Priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */
/*                           Macros & Typedefs                      */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                         Structures and Enums                     */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                 Internal Function Declarations                   */
/* ================================================================ */

/* None */

/* ================================================================ */
/*                            Global Variables                      */
/* ================================================================ */

extern volatile Spi_StatusType Spi_DrvStatus;

/* ================================================================ */
/*                          Function Definitions                    */
/* ================================================================ */

#define SPI_START_SEC_ISR_CODE
#include "Spi_MemMap.h"

MCAL_INTERRUPT_ATTRIBUTE
FUNC(void, SPI_CODE_FAST) Spi_IntISR_McspiTxRx(Spi_HWUnitType Spi_HwUnit)

{
    Spi_HwUnitObjType *hwUnitObj;
    uint32             baseAddr;

    if (SPI_UNINIT == Spi_DrvStatus)
    {
        /* Should not come here. Only possible case is MCU registers
         * ISR and stray/old interrupts are pending for channel */
        baseAddr = Spi_getHwUnitBaseAddr(Spi_HwUnit);
        Spi_mcspiDisableAllIntr(baseAddr);
        Spi_mcspiClearAllIrqStatus(baseAddr);
    }
    else
    {
        hwUnitObj = Spi_getHwUnitObj(Spi_HwUnit);
        Spi_processEvents(hwUnitObj);
    }
}
/**
 *  \brief SPI Hwunit ISR
 */

/** \brief SPI MCSPI0 ISR */
#if defined(SPI_UNIT_MCSPI0_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi0TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi0TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI0);
}

#endif

/** \brief SPI MCSPI1 ISR */
#if defined(SPI_UNIT_MCSPI1_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi1TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi1TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI1);
}

#endif

/** \brief SPI MCSPI2 ISR */
#if defined(SPI_UNIT_MCSPI2_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi2TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi2TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI2);
}
#endif

/** \brief SPI MCSPI3 ISR */
#if defined(SPI_UNIT_MCSPI3_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi3TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi3TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI3);
}
#endif

/** \brief SPI MCSPI4 ISR */
#if defined(SPI_UNIT_MCSPI4_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi4TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi4TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI4);
}
#endif

/** \brief SPI MCSPI5 ISR */
#if defined(SPI_UNIT_MCSPI5_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi5TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi5TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI5);
}
#endif

/** \brief SPI MCSPI6 ISR */
#if defined(SPI_UNIT_MCSPI6_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi6TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi6TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI6);
}
#endif

/** \brief SPI MCSPI7 ISR */
#if defined(SPI_UNIT_MCSPI7_ACTIVE)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi7TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi7TxRx)
#endif
{
    Spi_IntISR_McspiTxRx(SPI_UNIT_MCSPI7);
}
#endif

#define SPI_STOP_SEC_ISR_CODE
#include "Spi_MemMap.h"
#ifdef __cplusplus
}
#endif
