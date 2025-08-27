/*********************************************************************************************************************
 *  COPYRIGHT
 *  ------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright 2022 Texas Instruments Inc.  All rights reserved.
 *
 *  \endverbatim
 *  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *  File:       Lin_Irq.c
 *  Project:    AM263x MCAL
 *  Module:     Lin Driver
 *  Generator:  None
 *
 *  Description:  This file contains Interrupt Service Routines for Lin.c.
 *
 *--------------------------------------------------------------------------------------------------------------------
 * Author:  Piyush Panditrao
 *--------------------------------------------------------------------------------------------------------------------
 * Revision History (top to bottom: first revision to last revision)
 *--------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *--------------------------------------------------------------------------------------------------------------------
 * 00.01.00       11Nov2012    Author's name        0000000000000    Initial version
 *
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/
#include "EcuM_Cbk.h"
#include "Lin.h"
#include "Os.h"

/*********************************************************************************************************************
 * Other Header Files
 *********************************************************************************************************************/
#include "Lin_Priv.h"
#include "Lin_Irq.h"
#include "sys_common.h"

/*********************************************************************************************************************
 * Version Check (if required)
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Preprocessor #define Constants
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Preprocessor #define Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Type Declarations
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Exported Object Definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Object Definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  Local Function Prototypes
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  External Functions Definition
 *********************************************************************************************************************/
#define LIN_START_SEC_ISR_CODE
#include "Lin_MemMap.h"

#if defined(LIN_INSTANCE_0_LINE_NUM_0)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_VOID)
void Lin_0_Int0ISR(void)
#elif (LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_0_Int0ISR)
#endif /* ((LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_0);
}
#endif

#if defined(LIN_INSTANCE_0_LINE_NUM_1)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_VOID)
void Lin_0_Int1ISR(void)
#elif (LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_0_Int1ISR)
#endif /* ((LIN_INSTANCE_0_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_0);
}
#endif

#if defined(LIN_INSTANCE_1_LINE_NUM_0)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_VOID)
void Lin_1_Int0ISR(void)
#elif (LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_1_Int0ISR)
#endif /* ((LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_1);
}
#endif

#if defined(LIN_INSTANCE_1_LINE_NUM_1)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_VOID)
void Lin_1_Int1ISR(void)
#elif (LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_1_Int1ISR)
#endif /* ((LIN_INSTANCE_1_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_1);
}
#endif

#if defined(LIN_INSTANCE_2_LINE_NUM_0)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_VOID)
void Lin_2_Int0ISR(void)
#elif (LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_2_Int0ISR)
#endif /* ((LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_2);
}
#endif

#if defined(LIN_INSTANCE_2_LINE_NUM_1)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_VOID)
void Lin_2_Int1ISR(void)
#elif (LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_2_Int1ISR)
#endif /* ((LIN_INSTANCE_2_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_2);
}
#endif

#if defined(LIN_INSTANCE_3_LINE_NUM_0)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_VOID)
void Lin_3_Int0ISR(void)
#elif (LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_3_Int0ISR)
#endif /* ((LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_3);
}
#endif

#if defined(LIN_INSTANCE_3_LINE_NUM_1)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_VOID)
void Lin_3_Int1ISR(void)
#elif (LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_3_Int1ISR)
#endif /* ((LIN_INSTANCE_3_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_3);
}
#endif

#if defined(LIN_INSTANCE_4_LINE_NUM_0)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_VOID)
void Lin_4_Int0ISR(void)
#elif (LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_4_Int0ISR)
#endif /* ((LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_4);
}
#endif

#if defined(LIN_INSTANCE_4_LINE_NUM_1)
MCAL_INTERRUPT_ATTRIBUTE
#if (LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_CAT1 || LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_VOID)
void Lin_4_Int1ISR(void)
#elif (LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_CAT2)
ISR(Lin_4_Int1ISR)
#endif /* ((LIN_INSTANCE_4_ISR_TYPE == LIN_ISR_CAT1).... */
{
    Lin_ProcessISR(LIN_INSTANCE_4);
}
#endif

#define LIN_STOP_SEC_ISR_CODE
#include "Lin_MemMap.h"
/*********************************************************************************************************************
 *  Local Functions Definition
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  End of File: Lin_Priv.c
 *********************************************************************************************************************/
