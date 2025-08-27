/* ======================================================================
 *   Copyright (C) 2022 Texas Instruments Incorporated
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
 *  \file     CanApp_Startup.c
 *
 *  \brief    This file contains the Can test example
 */

/*******************************************************************************
 *  INCLUDES
 ******************************************************************************/

/* Include Files */
#include "Can.h"
#include "CanApp_Startup.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "esm.h"
#include "sys_vim.h"

#if (STD_ON == CAN_ECC_ENABLE)
/* #define CANFD_ESM_MASK          (uint64)(0x4800000000000) */
#define CANFD_ESM_MASK (uint64)(0xC000000000000)
/* #define CANFD2_ESM_MASK         (uint64)(0x000200200000) */
#define CANFD2_ESM_MASK (uint64)(0x3000000000000)
#endif

static void CanExample_PlatformInit()
{
#if (STD_ON == PORT_SET_PIN_MODE_API)
    uint16 uart_tx_pin, uart_rx_pin;
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if (STD_ON == MCU_VARIANT_PRE_COMPILE)
    Mcu_Init((const Mcu_ConfigType *)NULL_PTR);
#else
    Mcu_Init(&McuModuleConfiguration);
#endif /*(STD_ON == MCU_VARIANT_PRE_COMPILE)*/

#if (STD_ON == PORT_PRE_COMPILE_VARIANT)
    Port_Init((const Port_ConfigType *)NULL_PTR);
#else
    Port_Init(&PortConfigSet_0);
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

#if (STD_ON == CAN_ECC_ENABLE)
void esm_low_priority_handler(void)
{
#if defined(CAN_CONTROLLER_MCAN0)
    uint64 esmStatus2 = esmGetStatus(esmREG, 0, CANFD1_ESM_MASK);
    if (esmStatus2)
    {
        Can_0_Int1ISR_Fun();
        esmClearStatus(esmREG, 0, CANFD2_ESM_MASK);
    }
#endif
#if defined(CAN_CONTROLLER_MCAN1)
    uint64 esmStatus = esmGetStatus(esmREG, 0, CANFD2_ESM_MASK);
    if (esmStatus)
    {
        esmClearStatus(esmREG, 0, CANFD_ESM_MASK);
        Can_1_Int1ISR_Fun();
    }
#endif
#if defined(CAN_CONTROLLER_MCAN2)
    uint64 esmStatus = esmGetStatus(esmREG, 0, CANFD3_ESM_MASK);
    if (esmStatus)
    {
        esmClearStatus(esmREG, 0, CANFD_ESM_MASK);
        Can_2_Int1ISR_Fun();
    }
#endif
#if defined(CAN_CONTROLLER_MCAN3)
    uint64 esmStatus = esmGetStatus(esmREG, 0, CANFD4_ESM_MASK);
    if (esmStatus)
    {
        esmClearStatus(esmREG, 0, CANFD_ESM_MASK);
        Can_3_Int1ISR_Fun();
    }
#endif
}

#endif

static void CanExample_InterruptConfig(void)
{
    vimInit();
    Vim_IntCfg Can_IntCfg;
    Can_IntCfg.map    = VIM_INTTYPE_IRQ;
    Can_IntCfg.type   = VIM_INTTRIGTYPE_LEVEL;
    Can_IntCfg.intNum = MCAN0_MCAN_LVL_INT_0;

#if defined(CAN_CONTROLLER_MCAN0)
    Can_IntCfg.intNum   = MCAN0_MCAN_LVL_INT_0;
    Can_IntCfg.handler  = Can_0_Int0ISR;
    Can_IntCfg.priority = VIM_PRIORITY_3;
    vimRegisterInterrupt(&Can_IntCfg);

#if (STD_ON == CAN_ECC_ENABLE)
    Can_IntCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1;
    Can_IntCfg.handler  = esm_low_priority_handler;
    Can_IntCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&Can_IntCfg);

    esmClearStatus(esmREG, 0, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 1, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 2, 0xFFFFFFFFFFFFFFFF);

    esmSetInterruptLevel(esmREG, CANFD1_ESM_MASK, 0U);
    esmEnableInterrupt(esmREG, CANFD1_ESM_MASK);
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN1)
    Can_IntCfg.intNum   = MCAN1_MCAN_LVL_INT_0;
    Can_IntCfg.handler  = Can_1_Int0ISR;
    Can_IntCfg.priority = VIM_PRIORITY_5;
    vimRegisterInterrupt(&Can_IntCfg);

#if (STD_ON == CAN_ECC_ENABLE)
    Can_IntCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1;
    Can_IntCfg.handler  = esm_low_priority_handler;
    Can_IntCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&Can_IntCfg);

    esmClearStatus(esmREG, 0, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 1, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 2, 0xFFFFFFFFFFFFFFFF);

    esmSetInterruptLevel(esmREG, CANFD2_ESM_MASK, 0U);
    esmEnableInterrupt(esmREG, CANFD2_ESM_MASK);
#endif
#endif
#if defined(CAN_CONTROLLER_MCAN2)
    Can_IntCfg.intNum   = MCAN2_MCAN_LVL_INT_0;
    Can_IntCfg.handler  = Can_2_Int0ISR;
    Can_IntCfg.priority = VIM_PRIORITY_6;
    vimRegisterInterrupt(&Can_IntCfg);

#if (STD_ON == CAN_ECC_ENABLE)
    Can_IntCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1;
    Can_IntCfg.handler  = esm_low_priority_handler;
    Can_IntCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&Can_IntCfg);

    esmClearStatus(esmREG, 0, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 1, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 2, 0xFFFFFFFFFFFFFFFF);

    esmSetInterruptLevel(esmREG, CANFD3_ESM_MASK, 0U);
    esmEnableInterrupt(esmREG, CANFD3_ESM_MASK);
#endif
#endif
#if defined(CAN_CONTROLLER_MCAN3)
    Can_IntCfg.intNum   = MCAN3_MCAN_LVL_INT_0;
    Can_IntCfg.handler  = Can_3_Int0ISR;
    Can_IntCfg.priority = VIM_PRIORITY_7;
    vimRegisterInterrupt(&Can_IntCfg);

#if (STD_ON == CAN_ECC_ENABLE)
    Can_IntCfg.intNum   = MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1;
    Can_IntCfg.handler  = esm_low_priority_handler;
    Can_IntCfg.priority = VIM_PRIORITY_4;
    vimRegisterInterrupt(&Can_IntCfg);

    esmClearStatus(esmREG, 0, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 1, 0xFFFFFFFFFFFFFFFF);
    esmClearStatus(esmREG, 2, 0xFFFFFFFFFFFFFFFF);

    esmSetInterruptLevel(esmREG, CANFD4_ESM_MASK, 0U);
    esmEnableInterrupt(esmREG, CANFD4_ESM_MASK);
#endif
#endif
}

void CanApp_Startup()
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
#if (STD_ON == CAN_ECC_ENABLE)
    /* ESM module needs to be enabled to generate interrupt for ECC errors */
    esmInit();
#endif
    CanExample_PlatformInit();
    AppUtils_TimerInit();
    CanExample_InterruptConfig();
}

#ifdef __cplusplus
}
#endif
