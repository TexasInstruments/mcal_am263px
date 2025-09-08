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
 *  \file     CddCmpssApp_Platform.c
 *
 *  \brief    This file contains the platform configurations.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <CddCmpssApp.h>
#include <CddCmpssApp_Platform.h>

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

void CddCmpss_appPlatformInit(void)
{
    AppUtils_defaultInit();
    AppUtils_sectionInit();
    AppUtils_TimerInit();

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

    Enable_Uart();
}

void CddCmpss_appPlatformDeInit(void)
{ /* Nothing to do */
}

void CddCmpss_appConfigXbar(void)
{
    uint32 pwm_group_mask[MCU_PWM_XBAR_NUM_GROUPS];
    uint32 output_group_mask[MCU_OUTPUT_XBAR_NUM_GROUPS];

    /* Init all masks with none flag */
    for (uint32 i = 0U; i < MCU_PWM_XBAR_NUM_GROUPS; i++)
    {
        pwm_group_mask[i] = MCU_PWM_XBAR_GROUP_MASK_NONE;
    }
    for (uint32 i = 0U; i < MCU_OUTPUT_XBAR_NUM_GROUPS; i++)
    {
        output_group_mask[i] = MCU_OUTPUT_XBAR_GROUP_MASK_NONE;
    }

    /* EPWM XBAR - Config first and then select the mux */
    pwm_group_mask[0U] = CMPSS_APP_PWM_XBAR_GROUP0_MASK;
    MCU_xbarInvertPWMXBarOutputSignalBeforeLatch(0U);
    MCU_xbarSelectPWMXBarInputSource(CMPSS_APP_PWM_XBAR_OUT, pwm_group_mask);

    /* OUTPUT XBAR - Config first and then select the mux */
    output_group_mask[6U] = CMPSS_APP_OUTPUT_XBAR_GROUP6_MASK;
    MCU_xbarInvertOutputXBarOutputSignalBeforeLatch(0U);
    MCU_xbarInvertOutputXBarOutputSignal(0U);
    MCU_xbarSelectLatchOutputXBarOutputSignal(0U);
    MCU_xbarSelectStretchedPulseOutputXBarOutputSignal(0U);
    MCU_xbarSelectStretchedPulseLengthOutputXBarOutputSignal(0U);
    MCU_xbarSelectOutputXBarInputSource(CMPSS_APP_OUTPUT_XBAR_OUT, output_group_mask);
}
