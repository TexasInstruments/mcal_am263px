/* ======================================================================
 *   Copyright (C) 2023-2024 Texas Instruments Incorporated
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
 *  \file     Spi_Irq.h
 *
 *  \brief    This file contains ISR function declaration for SPI MCAL driver
 *
 */

/**
 *  \ingroup MCAL_SPIHANDLER_API
 *
 *  \defgroup MCAL_SPI_IRQ_API Defines Interrupt Handler for all SPI instances
 *  @{
 */

/* Design: SPI_DesignId_004 */

#ifndef SPI_IRQ_H_
#define SPI_IRQ_H_

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */
#include "Spi.h"
#include "sys_common.h"
#if (SPI_ISR_TYPE == SPI_ISR_CAT2)
#include "Os.h"
#endif

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

/* ================================================================ */
/*                          Function Declarations                   */
/* ================================================================ */

/** \brief SPI ISR */
FUNC(void, SPI_CODE_FAST) Spi_IntISR_McspiTxRx(Spi_HWUnitType Spi_HwUnit) MCAL_INTERRUPT_ATTRIBUTE;
/** \brief SPI MCSPI0 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi0TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi0TxRx);
#endif

/** \brief SPI MCSPI1 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi1TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi1TxRx);
#endif

/** \brief SPI MCSPI2 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi2TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi2TxRx);
#endif

/** \brief SPI MCSPI3 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi3TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi3TxRx);
#endif

/** \brief SPI MCSPI4 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi4TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi4TxRx);
#endif

/** \brief SPI MCSPI5 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi5TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi5TxRx);
#endif

/** \brief SPI MCSPI6 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi6TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi6TxRx);
#endif

/** \brief SPI MCSPI7 ISR */
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_FAST) Spi_IrqUnitMcspi7TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnitMcspi7TxRx);
#endif
#ifdef __cplusplus
}
#endif

#endif /* #ifndef SPI_IRQ_H_ */

/* @} */
