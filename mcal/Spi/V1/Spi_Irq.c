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
 *  \file     Spi_Irq.c
 *
 *  \brief    This file contains the ISR implementation of SPI MCAL driver
 *
 */

#define SPI_IRQ_SOURCE 1

/********************************************************************************************
 * INCLUDES
 *******************************************************************************************/
/* SourceId : SPI_SourceId_053 */
/* DesignId : SPI_DesignId_019 */
/* Requirements : AR_SPI_SR15 */
#include "Spi_Irq.h"
#include "Spi_Priv.h"
#include "Spi_Qspi.h"

/********************************************************************************************
 *  VERSION CHECK
 *******************************************************************************************/
/* AUTOSAR version information check has to match definition in header file */
#if ((SPI_IRQ_MAJOR_VERSION != (10U)) || (SPI_IRQ_MINOR_VERSION != (1U)))
#error "Software Version Numbers of Spi_Irq.c and Spi_Irq.h are different"
#endif

/*****************************************************************************************
 *  LOCAL CONSTANT MACROS
 *****************************************************************************************/

/*****************************************************************************************
 *  LOCAL FUNCTION MACROS
 *****************************************************************************************/

/*****************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *****************************************************************************************/

/*****************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *****************************************************************************************/

/*****************************************************************************************
 *  GLOBAL DATA
 *****************************************************************************************/

/*****************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *****************************************************************************************/

/*****************************************************************************************
 *  LOCAL FUNCTIONS
 *****************************************************************************************/

/*****************************************************************************************
 *  GLOBAL FUNCTIONS
 *****************************************************************************************/
#define SPI_START_SEC_ISR_CODE
#include "Spi_MemMap.h"

#if (SPI_UNIT_MIBSPI1_ACTIVE == STD_ON)

#if (defined CLANG)
#else
#pragma CODE_STATE(Spi_IrqUnit0TxRxERR, 32)
#pragma CODE_STATE(Spi_IrqUnit0TxRx, 32)
#endif

/****************************************************************************************
 *  SPI unit 0 error handler
 ***************************************************************************************/
/*! \brief      This method is the SPI unit 0 error handler.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt error handler for SPI, active if feature is available
 ***************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit0TxRxERR(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnit0TxRxERR)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRxERR(SPI_UNIT_MIBSPI1);
    }
}

/*****************************************************************************************
 *  SPI unit 0 handler
 ****************************************************************************************/
/*! \brief      This method is the SPI unit 0 handler.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt handler for SPI
 ****************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit0TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnit0TxRx)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRx(SPI_UNIT_MIBSPI1);
    }
}
#endif

#if (SPI_UNIT_MIBSPI2_ACTIVE == STD_ON)

#if (defined CLANG)
#else
#pragma CODE_STATE(Spi_IrqUnit1TxRxERR, 32)
#pragma CODE_STATE(Spi_IrqUnit1TxRx, 32)
#endif

/*****************************************************************************************
 *  SPI unit 1 Error handler
 ****************************************************************************************/
/*! \brief      This method is the SPI unit 1 Error handler.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt error handler for SPI, active if feature is available
 ****************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit1TxRxERR(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnit1TxRxERR)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRxERR(SPI_UNIT_MIBSPI2);
    }
}

/****************************************************************************************
 *  SPI unit 1 handler
 ***************************************************************************************/
/*! \brief      This method is the SPI unit 1 handler..
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt handler for SPI
 ***************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit1TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnit1TxRx)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRx(SPI_UNIT_MIBSPI2);
    }
}
#endif
#if (SPI_UNIT_RCSS_MIBSPI1_ACTIVE == STD_ON)

#if (defined CLANG)
#else
#pragma CODE_STATE(RCSS_Spi_IrqUnit0TxRxERR, 32)
#pragma CODE_STATE(RCSS_Spi_IrqUnit0TxRx, 32)
#endif

/****************************************************************************************
 *  SPI unit 0 error handler
 ***************************************************************************************/
/*! \brief      This method is the SPI unit 0 error handler.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt error handler for SPI, active if feature is available
 ***************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit0TxRxERR(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(RCSS_Spi_IrqUnit0TxRxERR)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRxERR(RCSS_SPI_UNIT_MIBSPI1);
    }
}

/*****************************************************************************************
 *  SPI unit 0 handler
 ****************************************************************************************/
/*! \brief      This method is the SPI unit 0 handler.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt handler for SPI
 ****************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit0TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(RCSS_Spi_IrqUnit0TxRx)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRx(RCSS_SPI_UNIT_MIBSPI1);
    }
}
#endif

#if (SPI_UNIT_RCSS_MIBSPI2_ACTIVE == STD_ON)
#if (defined CLANG)
#else
#pragma CODE_STATE(RCSS_Spi_IrqUnit1TxRxERR, 32)
#pragma CODE_STATE(RCSS_Spi_IrqUnit1TxRx, 32)
#endif

/*****************************************************************************************
 *  SPI unit 1 Error handler
 ****************************************************************************************/
/*! \brief      This method is the SPI unit 1 Error handler.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt error handler for SPI, active if feature is available
 ****************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit1TxRxERR(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(RCSS_Spi_IrqUnit1TxRxERR)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRxERR(RCSS_SPI_UNIT_MIBSPI2);
    }
}
/****************************************************************************************
 *  SPI unit 1 handler
 ***************************************************************************************/
/*! \brief      This method is the SPI unit 1 handler..
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \context    Function is called from interrupt level
 *  \note       Interrupt handler for SPI
 ***************************************************************************************/
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) RCSS_Spi_IrqUnit1TxRx(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(RCSS_Spi_IrqUnit1TxRx)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRx(RCSS_SPI_UNIT_MIBSPI2);
    }
}
#endif
#if (SPI_UNIT_QSPI1_ACTIVE == STD_ON)
MCAL_INTERRUPT_ATTRIBUTE
#if ((SPI_ISR_TYPE == SPI_ISR_CAT1) || (SPI_ISR_TYPE == SPI_ISR_VOID))
FUNC(void, SPI_CODE_ISR) Spi_IrqUnit0TxRxQspi(void)
#elif (SPI_ISR_TYPE == SPI_ISR_CAT2)
ISR(Spi_IrqUnit0TxRxQspi)
#endif
{
    if (SPI_UNINIT != Spi_DrvStatus)
    {
        Spi_IrqTxRxQspi(SPI_UNIT_QSPI1);
    }
}
#endif

#define SPI_STOP_SEC_ISR_CODE
#include "Spi_MemMap.h"
