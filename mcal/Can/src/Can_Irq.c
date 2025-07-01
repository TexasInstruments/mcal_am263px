/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Can.h"

#if (CAN_ISR_TYPE == CAN_ISR_CAT2)
#include "Os.h"
#endif

/* ========================================================================== */
/*                          ISR Definitions                                   */
/* ========================================================================== */

#define CAN_START_SEC_ISR_CODE
#include "Can_MemMap.h"
#if defined(CAN_CONTROLLER_MCAN0)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
void Can_0_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_0_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_0_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_0_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_0_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_0_Int1ISR_Fun();
}
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN1)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_1_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_1_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_1_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_1_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_1_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_1_Int1ISR_Fun();
}

#endif
#endif

#if defined(CAN_CONTROLLER_MCAN2)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
void Can_2_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_2_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_2_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_2_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_2_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_2_Int1ISR_Fun();
}

#endif
#endif

#if defined(CAN_CONTROLLER_MCAN3)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
void Can_3_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_3_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_3_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_3_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_3_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_3_Int1ISR_Fun();
}

#endif
#endif

#if defined(CAN_CONTROLLER_MCAN4)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
void Can_4_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_4_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_4_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_4_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_4_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_4_Int1ISR_Fun();
}

#endif
#endif

#if defined(CAN_CONTROLLER_MCAN5)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
void Can_5_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_5_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_5_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_5_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_5_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_5_Int1ISR_Fun();
}

#endif
#endif

#if defined(CAN_CONTROLLER_MCAN6)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
void Can_6_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_6_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_6_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_6_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_6_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_6_Int1ISR_Fun();
}

#endif
#endif

#if defined(CAN_CONTROLLER_MCAN7)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
void Can_7_Int0ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_7_Int0ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_7_Int0ISR_Fun();
}

#if (STD_ON == CAN_ECC_ENABLE)
MCAL_INTERRUPT_ATTRIBUTE
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
/* Design :CAN_DesignId_005*/
/* CODE_STATE word allignment needed for R5  */
void Can_7_Int1ISR(void)
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_7_Int1ISR)
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
{
    Can_7_Int1ISR_Fun();
}

#endif
#endif

#define CAN_STOP_SEC_ISR_CODE
#include "Can_MemMap.h"

/*******************************************************************************
 *  End of File: Can_Irq.c
 ******************************************************************************/
