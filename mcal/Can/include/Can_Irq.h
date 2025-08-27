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
