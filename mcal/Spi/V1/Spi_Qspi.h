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
 *  \file     Spi_Qspi.h
 *
 *  \brief    This file contains the common declarations and macros used across
 *            all the SPI MCAL driver files.
 *
 */
#ifndef SPI_QSPI_H_
#define SPI_QSPI_H_

#include "Cdd_Dma_Priv.h"
#include "Cdd_Dma_Cfg.h"
#include "Cdd_Dma_Irq.h"

#if (SPI_UNIT_QSPI1_DMA_ENABLE == STD_ON)
void Spi_qspiChannelConfig(void);
#endif
FUNC(void, SPI_CODE) Spi_IrqTxRxQspi(uint32 HwUnit_u32);

#endif
