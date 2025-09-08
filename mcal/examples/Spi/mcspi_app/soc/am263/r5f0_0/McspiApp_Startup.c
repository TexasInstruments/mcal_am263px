/* ======================================================================
 *   Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     mcspiApp_Startup.c
 *
 *  \brief    This file contains the McSPI test example Hw Dependent functions.
 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* Include Files */
#include "McspiApp_Startup.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32 frc;
uint32 Performance_Result[30];
void   SpiApp_platformInit(void)
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 uart_tx_pin, uart_rx_pin;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&Mcu_Config);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&Port_Config);
#endif /*#if (STD_ON == PORT_PRE_COMPILE_VARIANT)*/

#if (STD_ON == PORT_SET_PIN_MODE_API)
    uart_tx_pin = 13;
    uart_rx_pin = 14;

    /* Set up the pinmux for UART tx */
    Port_SetPinMode(uart_tx_pin, PORT_PIN_MODE_LIN0);

    /* Set up the pinmux for UART rx */
    Port_SetPinMode(uart_rx_pin, PORT_PIN_MODE_LIN0);
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/
#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    Port_SetPinDirection(uart_rx_pin, PORT_PIN_IN);
#endif /*    #if ( STD_ON == PORT_SET_PIN_DIRECTION_API )*/
    Enable_Uart();

    return;
}

void McspiApp_Startup()
{
#ifdef DIAB
    AppUtils_defaultInitDiab();
#else
    AppUtils_defaultInit();
#endif
    AppUtils_sectionInit();
}

void SpiApp_interruptConfig(void)
{
    Vim_IntCfg intCfg;
    intCfg.map  = VIM_INTTYPE_IRQ;
    intCfg.type = VIM_INTTRIGTYPE_LEVEL;
#if defined(SPI_UNIT_MCSPI0_ACTIVE)
    vimInit();
    intCfg.priority = VIM_PRIORITY_6;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI0_INTR;
    intCfg.handler  = Spi_IrqUnitMcspi0TxRx;
    vimRegisterInterrupt(&intCfg);
#endif
#if defined(SPI_UNIT_MCSPI1_ACTIVE)
    intCfg.priority = VIM_PRIORITY_7;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR;
    intCfg.handler  = Spi_IrqUnitMcspi1TxRx;
    vimRegisterInterrupt(&intCfg);
#endif
#if defined(SPI_UNIT_MCSPI2_ACTIVE)
    intCfg.priority = VIM_PRIORITY_8;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI2_INTR;
    intCfg.handler  = Spi_IrqUnitMcspi2TxRx;
    vimRegisterInterrupt(&intCfg);
#endif
#if defined(SPI_UNIT_MCSPI3_ACTIVE)
    intCfg.priority = VIM_PRIORITY_9;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI3_INTR;
    intCfg.handler  = Spi_IrqUnitMcspi3TxRx;
    vimRegisterInterrupt(&intCfg);
#endif
#if defined(SPI_UNIT_MCSPI4_ACTIVE)
    intCfg.priority = VIM_PRIORITY_10;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI4_INTR;
    intCfg.handler  = Spi_IrqUnitMcspi4TxRx;
    vimRegisterInterrupt(&intCfg);
#endif
#if (STD_ON == SPI_DMA_ENABLE)
    intCfg.priority = VIM_PRIORITY_11;
    intCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTAGGR;
    intCfg.handler  = CDD_EDMA_lld_transferCompletionMasterIsrFxn;
    vimRegisterInterrupt(&intCfg);
#endif
    return;
}

void Start_Timer(void)
{
    HW_WR_REG32(0x52180000, 0x00000000);  // GCTRL
    HW_WR_REG32(0x52180008, 0x00000000);  // Capture Control
    HW_WR_REG32(0x5218000C, 0x00000000);  // COMP CTRL
    HW_WR_REG32(0x52180010, 0x00000000);  // FRC0
    HW_WR_REG32(0x52180014, 0x00000000);  // UP Counter
    HW_WR_REG32(0x52180018, 0x00000001);  // Compare Up Counter
    HW_WR_REG32(0x52180084, 0x00070F0F);  // Clear Interrupt
    HW_WR_REG32(0x52180000, 0x00000001);  // GCTRL Start Timer
}

void Stop_Timer(uint8 Api_Id)
{
    HW_WR_REG32(0x52180000, 0x00000000);  // GCTRL Stop Timer
    frc                        = HW_RD_REG32(0x52180010);
    Performance_Result[Api_Id] = frc;
}
