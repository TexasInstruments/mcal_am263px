/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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
