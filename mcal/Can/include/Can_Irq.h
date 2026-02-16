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

/**
 *  \file     Can_Irq.h
 *
 *  \brief    This file contains cover page for generating doxygen
 *            API documentation.
 */

#ifndef CAN_IRQ_H_
#define CAN_IRQ_H_
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Can.h"
#include "sys_common.h"
#include "Os.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name CAN Driver ISR category level
 *
 *  Defines for CAN Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CAN_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CAN_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CAN_ISR_CAT2 (0x02U)
/* @} */

/* ========================================================================== */
/*                           Function Prototypes                              */
/* ========================================================================== */

#if defined(CAN_CONTROLLER_MCAN0)
/**
 * \brief This function is the Interrupt frame for CAN controller 0/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_0_Int0ISR
 *  Syntax            :void Can_0_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     0/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if ((CAN_ISR_TYPE == CAN_ISR_CAT1) || (CAN_ISR_TYPE == CAN_ISR_VOID))
FUNC(void, CAN_CODE) Can_0_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_0_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 0/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_0_Int1ISR
 *  Syntax            :void Can_0_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     0/INT 1 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if ((CAN_ISR_TYPE == CAN_ISR_CAT1) || (CAN_ISR_TYPE == CAN_ISR_VOID))
FUNC(void, CAN_CODE) Can_0_Int1ISR(void);
#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_0_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif

#if defined(CAN_CONTROLLER_MCAN1)
/**
 * \brief This function is the Interrupt frame for CAN controller 1/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_1_Int0ISR
 *  Syntax            :void Can_1_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     1/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_1_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_1_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 1/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_1_Int1ISR
 *  Syntax            :void Can_1_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     1/INT 1 ECC Interrupt <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (STD_ON == CAN_ECC_ENABLE)
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_1_Int1ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_1_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN2)
/**
 * \brief This function is the Interrupt frame for CAN controller 3/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_2_Int0ISR
 *  Syntax            :void Can_2_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     3/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_2_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_2_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 3/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_2_Int1ISR
 *  Syntax            :void Can_2_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     3/INT 1 ECC Interrupt <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (STD_ON == CAN_ECC_ENABLE)
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_2_Int1ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_2_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN3)
/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_3_Int0ISR
 *  Syntax            :void Can_3_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_3_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_3_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_3_Int1ISR
 *  Syntax            :void Can_3_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 1 ECC Interrupt <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (STD_ON == CAN_ECC_ENABLE)
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_3_Int1ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_3_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN4)
/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_4_Int0ISR
 *  Syntax            :void Can_4_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_4_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_4_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_4_Int1ISR
 *  Syntax            :void Can_4_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 1 ECC Interrupt <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (STD_ON == CAN_ECC_ENABLE)
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_4_Int1ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_4_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN5)
/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_5_Int0ISR
 *  Syntax            :void Can_5_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_5_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_5_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_5_Int1ISR
 *  Syntax            :void Can_5_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 1 ECC Interrupt <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (STD_ON == CAN_ECC_ENABLE)
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_5_Int1ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_5_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN6)
/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_6_Int0ISR
 *  Syntax            :void Can_6_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_6_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_6_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_6_Int1ISR
 *  Syntax            :void Can_6_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 1 ECC Interrupt <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (STD_ON == CAN_ECC_ENABLE)
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_6_Int1ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_6_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN7)
/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 0
 *
 * \verbatim
 *
 *  Function name     :Can_7_Int0ISR
 *  Syntax            :void Can_7_Int0ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 0 <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_7_Int0ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_7_Int0ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */

/**
 * \brief This function is the Interrupt frame for CAN controller 4/INT 1
 *
 * \verbatim
 *
 *  Function name     :Can_7_Int1ISR
 *  Syntax            :void Can_7_Int1ISR( void )
 *  Service ID[hex]   :N/A
 *  Sync/Async        :Synchronous
 *  Reentrancy        :Non-Reentrant
 *  Parameters (in)   :None
 *  Parameters (inout):None
 *  Parameters (out)  :None
 *  Return value      :None
 *  Description       :This function is the Interrupt frame for CAN controller
 *                     4/INT 1 ECC Interrupt <br>
 *                     This function should be plugged into the vector table for
 *                     Category 1 ISR
 * \endverbatim
 */
#if (STD_ON == CAN_ECC_ENABLE)
#if (CAN_ISR_TYPE == CAN_ISR_CAT1 || CAN_ISR_TYPE == CAN_ISR_VOID)
FUNC(void, CAN_CODE) Can_7_Int1ISR(void);

#elif (CAN_ISR_TYPE == CAN_ISR_CAT2)
ISR(Can_7_Int1ISR);
#endif /* ((CAN_ISR_TYPE == CAN_ISR_CAT1).... */
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CAN_IRQ_H_ */

/* @} */
