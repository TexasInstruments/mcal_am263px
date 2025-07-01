/* ======================================================================
 *   Copyright (c) 2023-2024 Texas Instruments Incorporated
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
 *  \ingroup MCAL_SPI_API
 *  @{
 */

/* Design: SPI_DesignId_004 */

#ifndef SPI_IRQ_H_
#define SPI_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Spi.h"
#if (SPI_ISR_TYPE == SPI_ISR_CAT2)
#include "Os.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name SPI Driver ISR SW Version Info
 *
 *  Defines for SPI Driver ISR version used for compatibility checks
 *  @{
 */
/** \brief Driver ISR Implementation Major Version */
#define SPI_IRQ_MAJOR_VERSION (10U)
/** \brief Driver ISR Implementation Minor Version */
#define SPI_IRQ_MINOR_VERSION (1U)
/** \brief Driver ISR Implementation Patch Version */
#define SPI_IRQ_PATCH_VERSION (0U)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (SPI_UNIT_MIBSPI1_ACTIVE == STD_ON)
/* ----SPIUNIT 0 Error handler
 * ----------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI1 ISR in case of TX/RX error*/
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit0TxRxERR(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(Spi_IrqUnit0TxRxERR);
#endif

/* ----SPIUNIT 0 handler
 * ----------------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI1 ISR to receive the data*/
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit0TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(Spi_IrqUnit0TxRx);
#endif
#endif

#if (SPI_UNIT_MIBSPI2_ACTIVE == STD_ON)
/* ----SPIUNIT 1 Error handler
 * ----------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI2 ISR in case of TX/RX error*/
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit1TxRxERR(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(Spi_IrqUnit1TxRxERR);
#endif

/* ----SPIUNIT 1 handler
 * ----------------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI2 ISR to receive the data*/
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit1TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(Spi_IrqUnit1TxRx);
#endif
#endif
#if (SPI_UNIT_RCSS_MIBSPI1_ACTIVE == STD_ON)
/* ----RCSS SPIUNIT 0 Error handler
 * ----------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI1 ISR in case of TX/RX error*/
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit0TxRxERR(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(RCSS_Spi_IrqUnit0TxRxERR);
#endif

/* ----RCSS SPIUNIT 0 handler
 * ----------------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI1 ISR to receive the data*/
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit0TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(RCSS_Spi_IrqUnit0TxRx);
#endif
#endif

#if (SPI_UNIT_RCSS_MIBSPI2_ACTIVE == STD_ON)
/* ----RCSS SPIUNIT 1 Error handler
 * ----------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI2 ISR in case of TX/RX error*/
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit1TxRxERR(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(RCSS_Spi_IrqUnit1TxRxERR);
#endif

/* ----RCSS SPIUNIT 1 handler
 * ----------------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI2 ISR to receive the data*/
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit1TxRx(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(RCSS_Spi_IrqUnit1TxRx);
#endif
#endif

#if (SPI_UNIT_QSPI1_ACTIVE == STD_ON)
/* ----SPIUNIT 0 Error handler
 * ----------------------------------------------------------------------------------------*/
#if (SPI_ISR_TYPE == SPI_ISR_CAT1 || SPI_ISR_TYPE == SPI_ISR_VOID)
/** \brief SPI MIBSPI1 ISR in case of TX/RX error*/
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit0TxRxQspi(void);
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
/* Function prototype is declared by OS */
ISR(Spi_IrqUnit0TxRxQspi);
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SPI_IRQ_H_ */

/* @} */
