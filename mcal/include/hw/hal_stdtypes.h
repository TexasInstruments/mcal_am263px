
/*
* Copyright (c) 2022 Texas Instruments Incorporated - TI web adress www.ti.com
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef HAL_STDTYPES_H
#define HAL_STDTYPES_H
/*LDRA_NOANALYSIS*/
#include <stdint.h>
#include <stdbool.h>
/*LDRA_ANALYSIS*/
/************************************************************/
/* Global Definitions                                       */
/************************************************************/
/** @def NULL
*   @brief NULL definition
*/

#ifndef NULL
/*LDRA_INSPECTED 219 S : MISRAC_2012_R_21_1 */
/*LDRA_INSPECTED 626 S : MISRAC_2012_R_20_4
 * "Reason - Custom type definition " */
/*LDRA_INSPECTED 218 S : MISRAC_2012_R_21_2 */
    #define NULL ((void *) 0U)
#endif

/*****************************************************************************/
/* Define:       NULL_PTR                                                    */
/* Description:  Void pointer to 0                                           */
/*****************************************************************************/
#ifndef NULL_PTR
    #define NULL_PTR ((void *)0x0)
#endif

/** @def TRUE
*   @brief definition for TRUE
*/
#ifndef TRUE
    #define TRUE true
#endif

/** @def FALSE
*   @brief BOOLEAN definition for FALSE
*/
#ifndef FALSE
    #define FALSE false
#endif


/*! \brief
 * Standard MACROs
 */
#define M_NULL                 (void *) 0
#define M_INVALID              (-1)
#define M_TRUE                 (uint8)(1U)
#define M_FALSE                (uint8)(0U)
#define M_LOGICAL_TRUE         (TRUE != FALSE)
#define M_LOGICAL_FALSE        (TRUE == FALSE)
#define M_SET                  (1U)
#define M_CLEAR                (0U)

#define M_ZERO                 (0U)
#define M_ONE                  (1U)
#define M_TWO                  (2U)
#define M_THREE                (3U)
#define M_FOUR                 (4U)
#define M_FIVE                 (5U)
#define M_SIX                  (6U)
#define M_SEVEN                (7U)
#define M_EIGHT                (8U)
#define M_NINE                 (9U)
#define M_TEN                  (10U)
#define M_ELEVEN               (11U)
#define M_TWELVE               (12U)
#define M_THIRTEEN             (13U)
#define M_FOURTEEN             (14U)
#define M_FIFTEEN              (15U)
#define M_SIXTEEN              (16U)
#define M_SEVENTEEN            (17U)
#define M_EIGHTEEN             (18U)
#define M_NINETEEN             (19U)
#define M_TWENTY               (20U)
#define M_TWENTY_ONE           (21U)
#define M_TWENTY_TWO           (22U)
#define M_TWENTY_THREE         (23U)
#define M_TWENTY_FOUR          (24U)
#define M_TWENTY_FIVE          (25U)
#define M_TWENTY_SIX           (26U)
#define M_TWENTY_SEVEN         (27U)
#define M_TWENTY_EIGHT         (28U)
#define M_TWENTY_NINE          (29U)
#define M_THIRTY               (30U)
#define M_THIRTY_ONE           (31U)
#define M_THIRTY_TWO           (32U)

#define M_SIXTY_FOUR           (64U)
#define M_SIXTY_FIVE           (65U)
#define M_SIXTY_SIX            (66U)
#define M_SIXTY_EIGHT          (68U)
#define M_SEVENTY_TWO          (72U)
#define M_EIGHTY               (80U)
#define M_NINTY_SIX            (96U)
#define M_NINTY_SEVEN          (97U)
#define M_HUNDRED              (100U)
#define M_ONE_TWENTY_EIGHT     (128U)
#define M_ONE_NINTY_TWO        (192U)
#define M_THREE_TWENTY         (320U)
#define M_FIVE_SEVENTY_SIX     (576U)
#define M_VALUE_1024           (1024U)
#define M_VALUE_1088           (1088U)
#define M_VALUE_2112           (2112U)
#define M_VALUE_4160           (4160U)
#define M_VALUE_8256           (8256U)
#define M_VALUE_16448          (16448U)
#define M_VALUE_32832          (32832U)
#define M_VALUE_65600          (65600U)
#define M_VALUE_131136         (131136U)
#define M_VALUE_262208         (262208U)
#define M_VALUE_524352         (524352U)
#define M_VALUE_1048640        (1048640U)
#define M_VALUE_2097216        (2097216U)
#define M_VALUE_4194368        (4194368U)
#define M_VALUE_8388672        (8388672U)
#define M_VALUE_16777280       (16777280U)
#define M_VALUE_33554496       (33554496U)
#define M_VALUE_67108928       (67108928U)

/*! \brief
 * Standard Bitwise MACROs
 */
#define  M_BIT_0                (0x00000001U)
#define  M_BIT_1                (0x00000002U)
#define  M_BIT_2                (0x00000004U)
#define  M_BIT_3                (0x00000008U)
#define  M_BIT_4                (0x00000010U)
#define  M_BIT_5                (0x00000020U)
#define  M_BIT_6                (0x00000040U)
#define  M_BIT_7                (0x00000080U)
#define  M_BIT_8                (0x00000100U)
#define  M_BIT_9                (0x00000200U)
#define  M_BIT_10               (0x00000400U)
#define  M_BIT_11               (0x00000800U)
#define  M_BIT_12               (0x00001000U)
#define  M_BIT_13               (0x00002000U)
#define  M_BIT_14               (0x00004000U)
#define  M_BIT_15               (0x00008000U)
#define  M_BIT_16               (0x00010000U)
#define  M_BIT_17               (0x00020000U)
#define  M_BIT_18               (0x00040000U)
#define  M_BIT_19               (0x00080000U)
#define  M_BIT_20               (0x00100000U)
#define  M_BIT_21               (0x00200000U)
#define  M_BIT_22               (0x00400000U)
#define  M_BIT_23               (0x00800000U)
#define  M_BIT_24               (0x01000000U)
#define  M_BIT_25               (0x02000000U)
#define  M_BIT_26               (0x04000000U)
#define  M_BIT_27               (0x08000000U)
#define  M_BIT_28               (0x10000000U)
#define  M_BIT_29               (0x20000000U)
#define  M_BIT_30               (0x40000000U)
#define  M_BIT_31               (0x80000000U)

#define  M_BIT_32               (0x0000000100000000U)
#define  M_BIT_33               (0x0000000200000000U)
#define  M_BIT_34               (0x0000000400000000U)
#define  M_BIT_35               (0x0000000800000000U)
#define  M_BIT_36               (0x0000001000000000U)
#define  M_BIT_37               (0x0000002000000000U)
#define  M_BIT_38               (0x0000004000000000U)
#define  M_BIT_39               (0x0000008000000000U)
#define  M_BIT_40               (0x0000010000000000U)
#define  M_BIT_41               (0x0000020000000000U)
#define  M_BIT_42               (0x0000040000000000U)
#define  M_BIT_43               (0x0000080000000000U)
#define  M_BIT_44               (0x0000100000000000U)
#define  M_BIT_45               (0x0000200000000000U)
#define  M_BIT_46               (0x0000400000000000U)
#define  M_BIT_47               (0x0000800000000000U)
#define  M_BIT_48               (0x0001000000000000U)
#define  M_BIT_49               (0x0002000000000000U)
#define  M_BIT_50               (0x0004000000000000U)
#define  M_BIT_51               (0x0008000000000000U)
#define  M_BIT_52               (0x0010000000000000U)
#define  M_BIT_53               (0x0020000000000000U)
#define  M_BIT_54               (0x0040000000000000U)
#define  M_BIT_55               (0x0080000000000000U)
#define  M_BIT_56               (0x0100000000000000U)
#define  M_BIT_57               (0x0200000000000000U)
#define  M_BIT_58               (0x0400000000000000U)
#define  M_BIT_59               (0x0800000000000000U)
#define  M_BIT_60               (0x1000000000000000U)
#define  M_BIT_61               (0x2000000000000000U)
#define  M_BIT_62               (0x4000000000000000U)
#define  M_BIT_63               (0x8000000000000000U)

#define M_MAX_WORD_VALUE        (0xFFFFFFFFU)
#define M_MAX_HWORD_VALUE       (0xFFFFU)
#define M_MAX_BYTE_VALUE        (0xFFU)


/*! \brief
 * regWriteReadback function status macro
 */
#define   MCAL_REGWR_E_OK       0U



#endif /* HAL_STDTYPES_H */
