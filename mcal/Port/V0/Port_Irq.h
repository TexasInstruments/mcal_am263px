/* =============================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ========================================================================== */

/**
 *  \file     Port_Irq.h
 *
 *  \brief    This file contains ISR function declaration for PORT MCAL driver
 *
 */

#ifndef PORT_IRQ_H_
#define PORT_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Port.h"
#include "sys_common.h"
#if (PORT_ISR_TYPE == PORT_ISR_CAT2)
#include "Os.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         GLOBAL VARIABLES                                   */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID))

/*******************************************************************************
 *                         PORT_ISR_CAT1 BANK ISRs
 *******************************************************************************/

#if defined(PORT_GPIO_BANK_0_ACTIVE)
void Port_Bnk0Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_0_ACTIVE) **/

#if defined(PORT_GPIO_BANK_1_ACTIVE)
void Port_Bnk1Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_1_ACTIVE) **/

#if defined(PORT_GPIO_BANK_2_ACTIVE)
void Port_Bnk2Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_2_ACTIVE) **/

#if defined(PORT_GPIO_BANK_3_ACTIVE)
void Port_Bnk3Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_3_ACTIVE) **/

#if defined(PORT_GPIO_BANK_4_ACTIVE)
void Port_Bnk4Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_4_ACTIVE) **/

#if defined(PORT_GPIO_BANK_5_ACTIVE)
void Port_Bnk5Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_5_ACTIVE) **/

#if defined(PORT_GPIO_BANK_6_ACTIVE)
void Port_Bnk6Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_6_ACTIVE) **/

#if defined(PORT_GPIO_BANK_7_ACTIVE)
void Port_Bnk7Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_7_ACTIVE) **/

#if defined(PORT_GPIO_BANK_8_ACTIVE)
void Port_Bnk8Isr(void);
#endif /** #if defined(PORT_GPIO_BANK_8_ACTIVE) **/

/*******************************************************************************
 *                         PORT_ISR_CAT1 CHANNEL ISRs
 *******************************************************************************/
#if defined(PORT_GPIO_CH_0_ACTIVE)
void Port_Ch0Isr(void);
#endif /** #if defined(PORT_GPIO_CH_0_ACTIVE) **/

#if defined(PORT_GPIO_CH_1_ACTIVE)
void Port_Ch1Isr(void);
#endif /** #if defined(PORT_GPIO_CH_1_ACTIVE) **/

#if defined(PORT_GPIO_CH_2_ACTIVE)
void Port_Ch2Isr(void);
#endif /** #if defined(PORT_GPIO_CH_2_ACTIVE) **/

#if defined(PORT_GPIO_CH_3_ACTIVE)
void Port_Ch3Isr(void);
#endif /** #if defined(PORT_GPIO_CH_3_ACTIVE) **/

#if defined(PORT_GPIO_CH_4_ACTIVE)
void Port_Ch4Isr(void);
#endif /** #if defined(PORT_GPIO_CH_4_ACTIVE) **/

#if defined(PORT_GPIO_CH_5_ACTIVE)
void Port_Ch5Isr(void);
#endif /** #if defined(PORT_GPIO_CH_5_ACTIVE) **/

#if defined(PORT_GPIO_CH_6_ACTIVE)
void Port_Ch6Isr(void);
#endif /** #if defined(PORT_GPIO_CH_6_ACTIVE) **/

#if defined(PORT_GPIO_CH_7_ACTIVE)
void Port_Ch7Isr(void);
#endif /** #if defined(PORT_GPIO_CH_7_ACTIVE) **/

#if defined(PORT_GPIO_CH_8_ACTIVE)
void Port_Ch8Isr(void);
#endif /** #if defined(PORT_GPIO_CH_8_ACTIVE) **/

#if defined(PORT_GPIO_CH_9_ACTIVE)
void Port_Ch9Isr(void);
#endif /** #if defined(PORT_GPIO_CH_9_ACTIVE) **/

#if defined(PORT_GPIO_CH_10_ACTIVE)
void Port_Ch10Isr(void);
#endif /** #if defined(PORT_GPIO_CH_10_ACTIVE) **/

#if defined(PORT_GPIO_CH_11_ACTIVE)
void Port_Ch11Isr(void);
#endif /** #if defined(PORT_GPIO_CH_11_ACTIVE) **/

#if defined(PORT_GPIO_CH_12_ACTIVE)
void Port_Ch12Isr(void);
#endif /** #if defined(PORT_GPIO_CH_12_ACTIVE) **/

#if defined(PORT_GPIO_CH_13_ACTIVE)
void Port_Ch13Isr(void);
#endif /** #if defined(PORT_GPIO_CH_13_ACTIVE) **/

#if defined(PORT_GPIO_CH_14_ACTIVE)
void Port_Ch14Isr(void);
#endif /** #if defined(PORT_GPIO_CH_14_ACTIVE) **/

#if defined(PORT_GPIO_CH_15_ACTIVE)
void Port_Ch15Isr(void);
#endif /** #if defined(PORT_GPIO_CH_15_ACTIVE) **/

#if defined(PORT_GPIO_CH_16_ACTIVE)
void Port_Ch16Isr(void);
#endif /** #if defined(PORT_GPIO_CH_16_ACTIVE) **/

#if defined(PORT_GPIO_CH_17_ACTIVE)
void Port_Ch17Isr(void);
#endif /** #if defined(PORT_GPIO_CH_17_ACTIVE) **/

#if defined(PORT_GPIO_CH_18_ACTIVE)
void Port_Ch18Isr(void);
#endif /** #if defined(PORT_GPIO_CH_18_ACTIVE) **/

#if defined(PORT_GPIO_CH_19_ACTIVE)
void Port_Ch19Isr(void);
#endif /** #if defined(PORT_GPIO_CH_19_ACTIVE) **/

#if defined(PORT_GPIO_CH_20_ACTIVE)
void Port_Ch20Isr(void);
#endif /** #if defined(PORT_GPIO_CH_20_ACTIVE) **/

#if defined(PORT_GPIO_CH_21_ACTIVE)
void Port_Ch21Isr(void);
#endif /** #if defined(PORT_GPIO_CH_21_ACTIVE) **/

#if defined(PORT_GPIO_CH_22_ACTIVE)
void Port_Ch22Isr(void);
#endif /** #if defined(PORT_GPIO_CH_22_ACTIVE) **/

#if defined(PORT_GPIO_CH_23_ACTIVE)
void Port_Ch23Isr(void);
#endif /** #if defined(PORT_GPIO_CH_23_ACTIVE) **/

#if defined(PORT_GPIO_CH_24_ACTIVE)
void Port_Ch24Isr(void);
#endif /** #if defined(PORT_GPIO_CH_24_ACTIVE) **/

#if defined(PORT_GPIO_CH_25_ACTIVE)
void Port_Ch25Isr(void);
#endif /** #if defined(PORT_GPIO_CH_25_ACTIVE) **/

#if defined(PORT_GPIO_CH_26_ACTIVE)
void Port_Ch26Isr(void);
#endif /** #if defined(PORT_GPIO_CH_26_ACTIVE) **/

#if defined(PORT_GPIO_CH_27_ACTIVE)
void Port_Ch27Isr(void);
#endif /** #if defined(PORT_GPIO_CH_27_ACTIVE) **/

#if defined(PORT_GPIO_CH_28_ACTIVE)
void Port_Ch28Isr(void);
#endif /** #if defined(PORT_GPIO_CH_28_ACTIVE) **/

#if defined(PORT_GPIO_CH_29_ACTIVE)
void Port_Ch29Isr(void);
#endif /** #if defined(PORT_GPIO_CH_29_ACTIVE) **/

#if defined(PORT_GPIO_CH_30_ACTIVE)
void Port_Ch30Isr(void);
#endif /** #if defined(PORT_GPIO_CH_30_ACTIVE) **/

#if defined(PORT_GPIO_CH_31_ACTIVE)
void Port_Ch31Isr(void);
#endif /** #if defined(PORT_GPIO_CH_31_ACTIVE) **/

#if defined(PORT_GPIO_CH_32_ACTIVE)
void Port_Ch32Isr(void);
#endif /** #if defined(PORT_GPIO_CH_32_ACTIVE) **/

#if defined(PORT_GPIO_CH_33_ACTIVE)
void Port_Ch33Isr(void);
#endif /** #if defined(PORT_GPIO_CH_33_ACTIVE) **/

#if defined(PORT_GPIO_CH_34_ACTIVE)
void Port_Ch34Isr(void);
#endif /** #if defined(PORT_GPIO_CH_34_ACTIVE) **/

#if defined(PORT_GPIO_CH_35_ACTIVE)
void Port_Ch35Isr(void);
#endif /** #if defined(PORT_GPIO_CH_35_ACTIVE) **/

#if defined(PORT_GPIO_CH_36_ACTIVE)
void Port_Ch36Isr(void);
#endif /** #if defined(PORT_GPIO_CH_36_ACTIVE) **/

#if defined(PORT_GPIO_CH_37_ACTIVE)
void Port_Ch37Isr(void);
#endif /** #if defined(PORT_GPIO_CH_37_ACTIVE) **/

#if defined(PORT_GPIO_CH_38_ACTIVE)
void Port_Ch38Isr(void);
#endif /** #if defined(PORT_GPIO_CH_38_ACTIVE) **/

#if defined(PORT_GPIO_CH_39_ACTIVE)
void Port_Ch39Isr(void);
#endif /** #if defined(PORT_GPIO_CH_39_ACTIVE) **/

#if defined(PORT_GPIO_CH_40_ACTIVE)
void Port_Ch40Isr(void);
#endif /** #if defined(PORT_GPIO_CH_40_ACTIVE) **/

#if defined(PORT_GPIO_CH_41_ACTIVE)
void Port_Ch41Isr(void);
#endif /** #if defined(PORT_GPIO_CH_41_ACTIVE) **/

#if defined(PORT_GPIO_CH_42_ACTIVE)
void Port_Ch42Isr(void);
#endif /** #if defined(PORT_GPIO_CH_42_ACTIVE) **/

#if defined(PORT_GPIO_CH_43_ACTIVE)
void Port_Ch43Isr(void);
#endif /** #if defined(PORT_GPIO_CH_43_ACTIVE) **/

#if defined(PORT_GPIO_CH_44_ACTIVE)
void Port_Ch44Isr(void);
#endif /** #if defined(PORT_GPIO_CH_44_ACTIVE) **/

#if defined(PORT_GPIO_CH_45_ACTIVE)
void Port_Ch45Isr(void);
#endif /** #if defined(PORT_GPIO_CH_45_ACTIVE) **/

#if defined(PORT_GPIO_CH_46_ACTIVE)
void Port_Ch46Isr(void);
#endif /** #if defined(PORT_GPIO_CH_46_ACTIVE) **/

#if defined(PORT_GPIO_CH_47_ACTIVE)
void Port_Ch47Isr(void);
#endif /** #if defined(PORT_GPIO_CH_47_ACTIVE) **/

#if defined(PORT_GPIO_CH_48_ACTIVE)
void Port_Ch48Isr(void);
#endif /** #if defined(PORT_GPIO_CH_48_ACTIVE) **/

#if defined(PORT_GPIO_CH_49_ACTIVE)
void Port_Ch49Isr(void);
#endif /** #if defined(PORT_GPIO_CH_49_ACTIVE) **/

#if defined(PORT_GPIO_CH_50_ACTIVE)
void Port_Ch50Isr(void);
#endif /** #if defined(PORT_GPIO_CH_50_ACTIVE) **/

#if defined(PORT_GPIO_CH_51_ACTIVE)
void Port_Ch51Isr(void);
#endif /** #if defined(PORT_GPIO_CH_51_ACTIVE) **/

#if defined(PORT_GPIO_CH_52_ACTIVE)
void Port_Ch52Isr(void);
#endif /** #if defined(PORT_GPIO_CH_52_ACTIVE) **/

#if defined(PORT_GPIO_CH_53_ACTIVE)
void Port_Ch53Isr(void);
#endif /** #if defined(PORT_GPIO_CH_53_ACTIVE) **/

#if defined(PORT_GPIO_CH_54_ACTIVE)
void Port_Ch54Isr(void);
#endif /** #if defined(PORT_GPIO_CH_54_ACTIVE) **/

#if defined(PORT_GPIO_CH_55_ACTIVE)
void Port_Ch55Isr(void);
#endif /** #if defined(PORT_GPIO_CH_55_ACTIVE) **/

#if defined(PORT_GPIO_CH_56_ACTIVE)
void Port_Ch56Isr(void);
#endif /** #if defined(PORT_GPIO_CH_56_ACTIVE) **/

#if defined(PORT_GPIO_CH_57_ACTIVE)
void Port_Ch57Isr(void);
#endif /** #if defined(PORT_GPIO_CH_57_ACTIVE) **/

#if defined(PORT_GPIO_CH_58_ACTIVE)
void Port_Ch58Isr(void);
#endif /** #if defined(PORT_GPIO_CH_58_ACTIVE) **/

#if defined(PORT_GPIO_CH_59_ACTIVE)
void Port_Ch59Isr(void);
#endif /** #if defined(PORT_GPIO_CH_59_ACTIVE) **/

#if defined(PORT_GPIO_CH_60_ACTIVE)
void Port_Ch60Isr(void);
#endif /** #if defined(PORT_GPIO_CH_60_ACTIVE) **/

#if defined(PORT_GPIO_CH_61_ACTIVE)
void Port_Ch61Isr(void);
#endif /** #if defined(PORT_GPIO_CH_61_ACTIVE) **/

#if defined(PORT_GPIO_CH_62_ACTIVE)
void Port_Ch62Isr(void);
#endif /** #if defined(PORT_GPIO_CH_62_ACTIVE) **/

#if defined(PORT_GPIO_CH_63_ACTIVE)
void Port_Ch63Isr(void);
#endif /** #if defined(PORT_GPIO_CH_63_ACTIVE) **/

#if defined(PORT_GPIO_CH_64_ACTIVE)
void Port_Ch64Isr(void);
#endif /** #if defined(PORT_GPIO_CH_64_ACTIVE) **/

#if defined(PORT_GPIO_CH_65_ACTIVE)
void Port_Ch65Isr(void);
#endif /** #if defined(PORT_GPIO_CH_65_ACTIVE) **/

#if defined(PORT_GPIO_CH_66_ACTIVE)
void Port_Ch66Isr(void);
#endif /** #if defined(PORT_GPIO_CH_66_ACTIVE) **/

#if defined(PORT_GPIO_CH_67_ACTIVE)
void Port_Ch67Isr(void);
#endif /** #if defined(PORT_GPIO_CH_67_ACTIVE) **/

#if defined(PORT_GPIO_CH_68_ACTIVE)
void Port_Ch68Isr(void);
#endif /** #if defined(PORT_GPIO_CH_68_ACTIVE) **/

#if defined(PORT_GPIO_CH_69_ACTIVE)
void Port_Ch69Isr(void);
#endif /** #if defined(PORT_GPIO_CH_69_ACTIVE) **/

#if defined(PORT_GPIO_CH_70_ACTIVE)
void Port_Ch70Isr(void);
#endif /** #if defined(PORT_GPIO_CH_70_ACTIVE) **/

#if defined(PORT_GPIO_CH_71_ACTIVE)
void Port_Ch71Isr(void);
#endif /** #if defined(PORT_GPIO_CH_71_ACTIVE) **/

#if defined(PORT_GPIO_CH_72_ACTIVE)
void Port_Ch72Isr(void);
#endif /** #if defined(PORT_GPIO_CH_72_ACTIVE) **/

#if defined(PORT_GPIO_CH_73_ACTIVE)
void Port_Ch73Isr(void);
#endif /** #if defined(PORT_GPIO_CH_73_ACTIVE) **/

#if defined(PORT_GPIO_CH_74_ACTIVE)
void Port_Ch74Isr(void);
#endif /** #if defined(PORT_GPIO_CH_74_ACTIVE) **/

#if defined(PORT_GPIO_CH_75_ACTIVE)
void Port_Ch75Isr(void);
#endif /** #if defined(PORT_GPIO_CH_75_ACTIVE) **/

#if defined(PORT_GPIO_CH_76_ACTIVE)
void Port_Ch76Isr(void);
#endif /** #if defined(PORT_GPIO_CH_76_ACTIVE) **/

#if defined(PORT_GPIO_CH_77_ACTIVE)
void Port_Ch77Isr(void);
#endif /** #if defined(PORT_GPIO_CH_77_ACTIVE) **/

#if defined(PORT_GPIO_CH_78_ACTIVE)
void Port_Ch78Isr(void);
#endif /** #if defined(PORT_GPIO_CH_78_ACTIVE) **/

#if defined(PORT_GPIO_CH_79_ACTIVE)
void Port_Ch79Isr(void);
#endif /** #if defined(PORT_GPIO_CH_79_ACTIVE) **/

#if defined(PORT_GPIO_CH_80_ACTIVE)
void Port_Ch80Isr(void);
#endif /** #if defined(PORT_GPIO_CH_80_ACTIVE) **/

#if defined(PORT_GPIO_CH_81_ACTIVE)
void Port_Ch81Isr(void);
#endif /** #if defined(PORT_GPIO_CH_81_ACTIVE) **/

#if defined(PORT_GPIO_CH_82_ACTIVE)
void Port_Ch82Isr(void);
#endif /** #if defined(PORT_GPIO_CH_82_ACTIVE) **/

#if defined(PORT_GPIO_CH_83_ACTIVE)
void Port_Ch83Isr(void);
#endif /** #if defined(PORT_GPIO_CH_83_ACTIVE) **/

#if defined(PORT_GPIO_CH_84_ACTIVE)
void Port_Ch84Isr(void);
#endif /** #if defined(PORT_GPIO_CH_84_ACTIVE) **/

#if defined(PORT_GPIO_CH_85_ACTIVE)
void Port_Ch85Isr(void);
#endif /** #if defined(PORT_GPIO_CH_85_ACTIVE) **/

#if defined(PORT_GPIO_CH_86_ACTIVE)
void Port_Ch86Isr(void);
#endif /** #if defined(PORT_GPIO_CH_86_ACTIVE) **/

#if defined(PORT_GPIO_CH_87_ACTIVE)
void Port_Ch87Isr(void);
#endif /** #if defined(PORT_GPIO_CH_87_ACTIVE) **/

#if defined(PORT_GPIO_CH_88_ACTIVE)
void Port_Ch88Isr(void);
#endif /** #if defined(PORT_GPIO_CH_88_ACTIVE) **/

#if defined(PORT_GPIO_CH_89_ACTIVE)
void Port_Ch89Isr(void);
#endif /** #if defined(PORT_GPIO_CH_89_ACTIVE) **/

#if defined(PORT_GPIO_CH_90_ACTIVE)
void Port_Ch90Isr(void);
#endif /** #if defined(PORT_GPIO_CH_90_ACTIVE) **/

#if defined(PORT_GPIO_CH_91_ACTIVE)
void Port_Ch91Isr(void);
#endif /** #if defined(PORT_GPIO_CH_91_ACTIVE) **/

#if defined(PORT_GPIO_CH_92_ACTIVE)
void Port_Ch92Isr(void);
#endif /** #if defined(PORT_GPIO_CH_92_ACTIVE) **/

#if defined(PORT_GPIO_CH_93_ACTIVE)
void Port_Ch93Isr(void);
#endif /** #if defined(PORT_GPIO_CH_93_ACTIVE) **/

#if defined(PORT_GPIO_CH_94_ACTIVE)
void Port_Ch94Isr(void);
#endif /** #if defined(PORT_GPIO_CH_94_ACTIVE) **/

#if defined(PORT_GPIO_CH_95_ACTIVE)
void Port_Ch95Isr(void);
#endif /** #if defined(PORT_GPIO_CH_95_ACTIVE) **/

#if defined(PORT_GPIO_CH_96_ACTIVE)
void Port_Ch96Isr(void);
#endif /** #if defined(PORT_GPIO_CH_96_ACTIVE) **/

#if defined(PORT_GPIO_CH_97_ACTIVE)
void Port_Ch97Isr(void);
#endif /** #if defined(PORT_GPIO_CH_97_ACTIVE) **/

#if defined(PORT_GPIO_CH_98_ACTIVE)
void Port_Ch98Isr(void);
#endif /** #if defined(PORT_GPIO_CH_98_ACTIVE) **/

#if defined(PORT_GPIO_CH_99_ACTIVE)
void Port_Ch99Isr(void);
#endif /** #if defined(PORT_GPIO_CH_99_ACTIVE) **/

#if defined(PORT_GPIO_CH_100_ACTIVE)
void Port_Ch100Isr(void);
#endif /** #if defined(PORT_GPIO_CH_100_ACTIVE) **/

#if defined(PORT_GPIO_CH_101_ACTIVE)
void Port_Ch101Isr(void);
#endif /** #if defined(PORT_GPIO_CH_101_ACTIVE) **/

#if defined(PORT_GPIO_CH_102_ACTIVE)
void Port_Ch102Isr(void);
#endif /** #if defined(PORT_GPIO_CH_102_ACTIVE) **/

#if defined(PORT_GPIO_CH_103_ACTIVE)
void Port_Ch103Isr(void);
#endif /** #if defined(PORT_GPIO_CH_103_ACTIVE) **/

#if defined(PORT_GPIO_CH_104_ACTIVE)
void Port_Ch104Isr(void);
#endif /** #if defined(PORT_GPIO_CH_104_ACTIVE) **/

#if defined(PORT_GPIO_CH_105_ACTIVE)
void Port_Ch105Isr(void);
#endif /** #if defined(PORT_GPIO_CH_105_ACTIVE) **/

#if defined(PORT_GPIO_CH_106_ACTIVE)
void Port_Ch106Isr(void);
#endif /** #if defined(PORT_GPIO_CH_106_ACTIVE) **/

#if defined(PORT_GPIO_CH_107_ACTIVE)
void Port_Ch107Isr(void);
#endif /** #if defined(PORT_GPIO_CH_107_ACTIVE) **/

#if defined(PORT_GPIO_CH_108_ACTIVE)
void Port_Ch108Isr(void);
#endif /** #if defined(PORT_GPIO_CH_108_ACTIVE) **/

#if defined(PORT_GPIO_CH_109_ACTIVE)
void Port_Ch109Isr(void);
#endif /** #if defined(PORT_GPIO_CH_109_ACTIVE) **/

#if defined(PORT_GPIO_CH_110_ACTIVE)
void Port_Ch110Isr(void);
#endif /** #if defined(PORT_GPIO_CH_110_ACTIVE) **/

#if defined(PORT_GPIO_CH_111_ACTIVE)
void Port_Ch111Isr(void);
#endif /** #if defined(PORT_GPIO_CH_111_ACTIVE) **/

#if defined(PORT_GPIO_CH_112_ACTIVE)
void Port_Ch112Isr(void);
#endif /** #if defined(PORT_GPIO_CH_112_ACTIVE) **/

#if defined(PORT_GPIO_CH_113_ACTIVE)
void Port_Ch113Isr(void);
#endif /** #if defined(PORT_GPIO_CH_113_ACTIVE) **/

#if defined(PORT_GPIO_CH_114_ACTIVE)
void Port_Ch114Isr(void);
#endif /** #if defined(PORT_GPIO_CH_114_ACTIVE) **/

#if defined(PORT_GPIO_CH_115_ACTIVE)
void Port_Ch115Isr(void);
#endif /** #if defined(PORT_GPIO_CH_115_ACTIVE) **/

#if defined(PORT_GPIO_CH_116_ACTIVE)
void Port_Ch116Isr(void);
#endif /** #if defined(PORT_GPIO_CH_116_ACTIVE) **/

#if defined(PORT_GPIO_CH_117_ACTIVE)
void Port_Ch117Isr(void);
#endif /** #if defined(PORT_GPIO_CH_117_ACTIVE) **/

#if defined(PORT_GPIO_CH_118_ACTIVE)
void Port_Ch118Isr(void);
#endif /** #if defined(PORT_GPIO_CH_118_ACTIVE) **/

#if defined(PORT_GPIO_CH_119_ACTIVE)
void Port_Ch119Isr(void);
#endif /** #if defined(PORT_GPIO_CH_119_ACTIVE) **/

#if defined(PORT_GPIO_CH_120_ACTIVE)
void Port_Ch120Isr(void);
#endif /** #if defined(PORT_GPIO_CH_120_ACTIVE) **/

#if defined(PORT_GPIO_CH_121_ACTIVE)
void Port_Ch121Isr(void);
#endif /** #if defined(PORT_GPIO_CH_121_ACTIVE) **/

#if defined(PORT_GPIO_CH_122_ACTIVE)
void Port_Ch122Isr(void);
#endif /** #if defined(PORT_GPIO_CH_122_ACTIVE) **/

#if defined(PORT_GPIO_CH_123_ACTIVE)
void Port_Ch123Isr(void);
#endif /** #if defined(PORT_GPIO_CH_123_ACTIVE) **/

#if defined(PORT_GPIO_CH_124_ACTIVE)
void Port_Ch124Isr(void);
#endif /** #if defined(PORT_GPIO_CH_124_ACTIVE) **/

#if defined(PORT_GPIO_CH_125_ACTIVE)
void Port_Ch125Isr(void);
#endif /** #if defined(PORT_GPIO_CH_125_ACTIVE) **/

#if defined(PORT_GPIO_CH_126_ACTIVE)
void Port_Ch126Isr(void);
#endif /** #if defined(PORT_GPIO_CH_126_ACTIVE) **/

#if defined(PORT_GPIO_CH_127_ACTIVE)
void Port_Ch127Isr(void);
#endif /** #if defined(PORT_GPIO_CH_127_ACTIVE) **/

#if defined(PORT_GPIO_CH_128_ACTIVE)
void Port_Ch128Isr(void);
#endif /** #if defined(PORT_GPIO_CH_128_ACTIVE) **/

#if defined(PORT_GPIO_CH_129_ACTIVE)
void Port_Ch129Isr(void);
#endif /** #if defined(PORT_GPIO_CH_129_ACTIVE) **/

#if defined(PORT_GPIO_CH_130_ACTIVE)
void Port_Ch130Isr(void);
#endif /** #if defined(PORT_GPIO_CH_130_ACTIVE) **/

#if defined(PORT_GPIO_CH_131_ACTIVE)
void Port_Ch131Isr(void);
#endif /** #if defined(PORT_GPIO_CH_131_ACTIVE) **/

#if defined(PORT_GPIO_CH_132_ACTIVE)
void Port_Ch132Isr(void);
#endif /** #if defined(PORT_GPIO_CH_132_ACTIVE) **/

#if defined(PORT_GPIO_CH_133_ACTIVE)
void Port_Ch133Isr(void);
#endif /** #if defined(PORT_GPIO_CH_133_ACTIVE) **/

#if defined(PORT_GPIO_CH_134_ACTIVE)
void Port_Ch134Isr(void);
#endif /** #if defined(PORT_GPIO_CH_134_ACTIVE) **/

#if defined(PORT_GPIO_CH_135_ACTIVE)
void Port_Ch135Isr(void);
#endif /** #if defined(PORT_GPIO_CH_135_ACTIVE) **/

#if defined(PORT_GPIO_CH_136_ACTIVE)
void Port_Ch136Isr(void);
#endif /** #if defined(PORT_GPIO_CH_136_ACTIVE) **/

#if defined(PORT_GPIO_CH_137_ACTIVE)
void Port_Ch137Isr(void);
#endif /** #if defined(PORT_GPIO_CH_137_ACTIVE) **/

#if defined(PORT_GPIO_CH_138_ACTIVE)
void Port_Ch138Isr(void);
#endif /** #if defined(PORT_GPIO_CH_138_ACTIVE) **/

#if defined(PORT_GPIO_CH_139_ACTIVE)
void Port_Ch139Isr(void);
#endif /** #if defined(PORT_GPIO_CH_139_ACTIVE) **/

#elif (PORT_ISR_TYPE == PORT_ISR_CAT2)

/*******************************************************************************
 *                         PORT_ISR_CAT2 BANK ISRs
 *******************************************************************************/
#if defined(PORT_GPIO_BANK_0_ACTIVE)
ISR(Port_Bnk0Isr);
#endif /** #if defined(PORT_GPIO_BANK_0_ACTIVE) **/

#if defined(PORT_GPIO_BANK_1_ACTIVE)
ISR(Port_Bnk1Isr);
#endif /** #if defined(PORT_GPIO_BANK_1_ACTIVE) **/

#if defined(PORT_GPIO_BANK_2_ACTIVE)
ISR(Port_Bnk2Isr);
#endif /** #if defined(PORT_GPIO_BANK_2_ACTIVE) **/

#if defined(PORT_GPIO_BANK_3_ACTIVE)
ISR(Port_Bnk3Isr);
#endif /** #if defined(PORT_GPIO_BANK_3_ACTIVE) **/

#if defined(PORT_GPIO_BANK_4_ACTIVE)
ISR(Port_Bnk4Isr);
#endif /** #if defined(PORT_GPIO_BANK_4_ACTIVE) **/

#if defined(PORT_GPIO_BANK_5_ACTIVE)
ISR(Port_Bnk5Isr);
#endif /** #if defined(PORT_GPIO_BANK_5_ACTIVE) **/

#if defined(PORT_GPIO_BANK_6_ACTIVE)
ISR(Port_Bnk6Isr);
#endif /** #if defined(PORT_GPIO_BANK_6_ACTIVE) **/

#if defined(PORT_GPIO_BANK_7_ACTIVE)
ISR(Port_Bnk7Isr);
#endif /** #if defined(PORT_GPIO_BANK_7_ACTIVE) **/

#if defined(PORT_GPIO_BANK_8_ACTIVE)
ISR(Port_Bnk8Isr);
#endif /** #if defined(PORT_GPIO_BANK_8_ACTIVE) **/

/*******************************************************************************
 *                         PORT_ISR_CAT2 CHANNEL ISRs
 *******************************************************************************/
#if defined(PORT_GPIO_CH_0_ACTIVE)
ISR(Port_Ch0Isr);
#endif /** #if defined(PORT_GPIO_CH_0_ACTIVE) **/

#if defined(PORT_GPIO_CH_1_ACTIVE)
ISR(Port_Ch1Isr);
#endif /** #if defined(PORT_GPIO_CH_1_ACTIVE) **/

#if defined(PORT_GPIO_CH_2_ACTIVE)
ISR(Port_Ch2Isr);
#endif /** #if defined(PORT_GPIO_CH_2_ACTIVE) **/

#if defined(PORT_GPIO_CH_3_ACTIVE)
ISR(Port_Ch3Isr);
#endif /** #if defined(PORT_GPIO_CH_3_ACTIVE) **/

#if defined(PORT_GPIO_CH_4_ACTIVE)
ISR(Port_Ch4Isr);
#endif /** #if defined(PORT_GPIO_CH_4_ACTIVE) **/

#if defined(PORT_GPIO_CH_5_ACTIVE)
ISR(Port_Ch5Isr);
#endif /** #if defined(PORT_GPIO_CH_5_ACTIVE) **/

#if defined(PORT_GPIO_CH_6_ACTIVE)
ISR(Port_Ch6Isr);
#endif /** #if defined(PORT_GPIO_CH_6_ACTIVE) **/

#if defined(PORT_GPIO_CH_7_ACTIVE)
ISR(Port_Ch7Isr);
#endif /** #if defined(PORT_GPIO_CH_7_ACTIVE) **/

#if defined(PORT_GPIO_CH_8_ACTIVE)
ISR(Port_Ch8Isr);
#endif /** #if defined(PORT_GPIO_CH_8_ACTIVE) **/

#if defined(PORT_GPIO_CH_9_ACTIVE)
ISR(Port_Ch9Isr);
#endif /** #if defined(PORT_GPIO_CH_9_ACTIVE) **/

#if defined(PORT_GPIO_CH_10_ACTIVE)
ISR(Port_Ch10Isr);
#endif /** #if defined(PORT_GPIO_CH_10_ACTIVE) **/

#if defined(PORT_GPIO_CH_11_ACTIVE)
ISR(Port_Ch11Isr);
#endif /** #if defined(PORT_GPIO_CH_11_ACTIVE) **/

#if defined(PORT_GPIO_CH_12_ACTIVE)
ISR(Port_Ch12Isr);
#endif /** #if defined(PORT_GPIO_CH_12_ACTIVE) **/

#if defined(PORT_GPIO_CH_13_ACTIVE)
ISR(Port_Ch13Isr);
#endif /** #if defined(PORT_GPIO_CH_13_ACTIVE) **/

#if defined(PORT_GPIO_CH_14_ACTIVE)
ISR(Port_Ch14Isr);
#endif /** #if defined(PORT_GPIO_CH_14_ACTIVE) **/

#if defined(PORT_GPIO_CH_15_ACTIVE)
ISR(Port_Ch15Isr);
#endif /** #if defined(PORT_GPIO_CH_15_ACTIVE) **/

#if defined(PORT_GPIO_CH_16_ACTIVE)
ISR(Port_Ch16Isr);
#endif /** #if defined(PORT_GPIO_CH_16_ACTIVE) **/

#if defined(PORT_GPIO_CH_17_ACTIVE)
ISR(Port_Ch17Isr);
#endif /** #if defined(PORT_GPIO_CH_17_ACTIVE) **/

#if defined(PORT_GPIO_CH_18_ACTIVE)
ISR(Port_Ch18Isr);
#endif /** #if defined(PORT_GPIO_CH_18_ACTIVE) **/

#if defined(PORT_GPIO_CH_19_ACTIVE)
ISR(Port_Ch19Isr);
#endif /** #if defined(PORT_GPIO_CH_19_ACTIVE) **/

#if defined(PORT_GPIO_CH_20_ACTIVE)
ISR(Port_Ch20Isr);
#endif /** #if defined(PORT_GPIO_CH_20_ACTIVE) **/

#if defined(PORT_GPIO_CH_21_ACTIVE)
ISR(Port_Ch21Isr);
#endif /** #if defined(PORT_GPIO_CH_21_ACTIVE) **/

#if defined(PORT_GPIO_CH_22_ACTIVE)
ISR(Port_Ch22Isr);
#endif /** #if defined(PORT_GPIO_CH_22_ACTIVE) **/

#if defined(PORT_GPIO_CH_23_ACTIVE)
ISR(Port_Ch23Isr);
#endif /** #if defined(PORT_GPIO_CH_23_ACTIVE) **/

#if defined(PORT_GPIO_CH_24_ACTIVE)
ISR(Port_Ch24Isr);
#endif /** #if defined(PORT_GPIO_CH_24_ACTIVE) **/

#if defined(PORT_GPIO_CH_25_ACTIVE)
ISR(Port_Ch25Isr);
#endif /** #if defined(PORT_GPIO_CH_25_ACTIVE) **/

#if defined(PORT_GPIO_CH_26_ACTIVE)
ISR(Port_Ch26Isr);
#endif /** #if defined(PORT_GPIO_CH_26_ACTIVE) **/

#if defined(PORT_GPIO_CH_27_ACTIVE)
ISR(Port_Ch27Isr);
#endif /** #if defined(PORT_GPIO_CH_27_ACTIVE) **/

#if defined(PORT_GPIO_CH_28_ACTIVE)
ISR(Port_Ch28Isr);
#endif /** #if defined(PORT_GPIO_CH_28_ACTIVE) **/

#if defined(PORT_GPIO_CH_29_ACTIVE)
ISR(Port_Ch29Isr);
#endif /** #if defined(PORT_GPIO_CH_29_ACTIVE) **/

#if defined(PORT_GPIO_CH_30_ACTIVE)
ISR(Port_Ch30Isr);
#endif /** #if defined(PORT_GPIO_CH_30_ACTIVE) **/

#if defined(PORT_GPIO_CH_31_ACTIVE)
ISR(Port_Ch31Isr);
#endif /** #if defined(PORT_GPIO_CH_31_ACTIVE) **/

#if defined(PORT_GPIO_CH_32_ACTIVE)
ISR(Port_Ch32Isr);
#endif /** #if defined(PORT_GPIO_CH_32_ACTIVE) **/

#if defined(PORT_GPIO_CH_33_ACTIVE)
ISR(Port_Ch33Isr);
#endif /** #if defined(PORT_GPIO_CH_33_ACTIVE) **/

#if defined(PORT_GPIO_CH_34_ACTIVE)
ISR(Port_Ch34Isr);
#endif /** #if defined(PORT_GPIO_CH_34_ACTIVE) **/

#if defined(PORT_GPIO_CH_35_ACTIVE)
ISR(Port_Ch35Isr);
#endif /** #if defined(PORT_GPIO_CH_35_ACTIVE) **/

#if defined(PORT_GPIO_CH_36_ACTIVE)
ISR(Port_Ch36Isr);
#endif /** #if defined(PORT_GPIO_CH_36_ACTIVE) **/

#if defined(PORT_GPIO_CH_37_ACTIVE)
ISR(Port_Ch37Isr);
#endif /** #if defined(PORT_GPIO_CH_37_ACTIVE) **/

#if defined(PORT_GPIO_CH_38_ACTIVE)
ISR(Port_Ch38Isr);
#endif /** #if defined(PORT_GPIO_CH_38_ACTIVE) **/

#if defined(PORT_GPIO_CH_39_ACTIVE)
ISR(Port_Ch39Isr);
#endif /** #if defined(PORT_GPIO_CH_39_ACTIVE) **/

#if defined(PORT_GPIO_CH_40_ACTIVE)
ISR(Port_Ch40Isr);
#endif /** #if defined(PORT_GPIO_CH_40_ACTIVE) **/

#if defined(PORT_GPIO_CH_41_ACTIVE)
ISR(Port_Ch41Isr);
#endif /** #if defined(PORT_GPIO_CH_41_ACTIVE) **/

#if defined(PORT_GPIO_CH_42_ACTIVE)
ISR(Port_Ch42Isr);
#endif /** #if defined(PORT_GPIO_CH_42_ACTIVE) **/

#if defined(PORT_GPIO_CH_43_ACTIVE)
ISR(Port_Ch43Isr);
#endif /** #if defined(PORT_GPIO_CH_43_ACTIVE) **/

#if defined(PORT_GPIO_CH_44_ACTIVE)
ISR(Port_Ch44Isr);
#endif /** #if defined(PORT_GPIO_CH_44_ACTIVE) **/

#if defined(PORT_GPIO_CH_45_ACTIVE)
ISR(Port_Ch45Isr);
#endif /** #if defined(PORT_GPIO_CH_45_ACTIVE) **/

#if defined(PORT_GPIO_CH_46_ACTIVE)
ISR(Port_Ch46Isr);
#endif /** #if defined(PORT_GPIO_CH_46_ACTIVE) **/

#if defined(PORT_GPIO_CH_47_ACTIVE)
ISR(Port_Ch47Isr);
#endif /** #if defined(PORT_GPIO_CH_47_ACTIVE) **/

#if defined(PORT_GPIO_CH_48_ACTIVE)
ISR(Port_Ch48Isr);
#endif /** #if defined(PORT_GPIO_CH_48_ACTIVE) **/

#if defined(PORT_GPIO_CH_49_ACTIVE)
ISR(Port_Ch49Isr);
#endif /** #if defined(PORT_GPIO_CH_49_ACTIVE) **/

#if defined(PORT_GPIO_CH_50_ACTIVE)
ISR(Port_Ch50Isr);
#endif /** #if defined(PORT_GPIO_CH_50_ACTIVE) **/

#if defined(PORT_GPIO_CH_51_ACTIVE)
ISR(Port_Ch51Isr);
#endif /** #if defined(PORT_GPIO_CH_51_ACTIVE) **/

#if defined(PORT_GPIO_CH_52_ACTIVE)
ISR(Port_Ch52Isr);
#endif /** #if defined(PORT_GPIO_CH_52_ACTIVE) **/

#if defined(PORT_GPIO_CH_53_ACTIVE)
ISR(Port_Ch53Isr);
#endif /** #if defined(PORT_GPIO_CH_53_ACTIVE) **/

#if defined(PORT_GPIO_CH_54_ACTIVE)
ISR(Port_Ch54Isr);
#endif /** #if defined(PORT_GPIO_CH_54_ACTIVE) **/

#if defined(PORT_GPIO_CH_55_ACTIVE)
ISR(Port_Ch55Isr);
#endif /** #if defined(PORT_GPIO_CH_55_ACTIVE) **/

#if defined(PORT_GPIO_CH_56_ACTIVE)
ISR(Port_Ch56Isr);
#endif /** #if defined(PORT_GPIO_CH_56_ACTIVE) **/

#if defined(PORT_GPIO_CH_57_ACTIVE)
ISR(Port_Ch57Isr);
#endif /** #if defined(PORT_GPIO_CH_57_ACTIVE) **/

#if defined(PORT_GPIO_CH_58_ACTIVE)
ISR(Port_Ch58Isr);
#endif /** #if defined(PORT_GPIO_CH_58_ACTIVE) **/

#if defined(PORT_GPIO_CH_59_ACTIVE)
ISR(Port_Ch59Isr);
#endif /** #if defined(PORT_GPIO_CH_59_ACTIVE) **/

#if defined(PORT_GPIO_CH_60_ACTIVE)
ISR(Port_Ch60Isr);
#endif /** #if defined(PORT_GPIO_CH_60_ACTIVE) **/

#if defined(PORT_GPIO_CH_61_ACTIVE)
ISR(Port_Ch61Isr);
#endif /** #if defined(PORT_GPIO_CH_61_ACTIVE) **/

#if defined(PORT_GPIO_CH_62_ACTIVE)
ISR(Port_Ch62Isr);
#endif /** #if defined(PORT_GPIO_CH_62_ACTIVE) **/

#if defined(PORT_GPIO_CH_63_ACTIVE)
ISR(Port_Ch63Isr);
#endif /** #if defined(PORT_GPIO_CH_63_ACTIVE) **/

#if defined(PORT_GPIO_CH_64_ACTIVE)
ISR(Port_Ch64Isr);
#endif /** #if defined(PORT_GPIO_CH_64_ACTIVE) **/

#if defined(PORT_GPIO_CH_65_ACTIVE)
ISR(Port_Ch65Isr);
#endif /** #if defined(PORT_GPIO_CH_65_ACTIVE) **/

#if defined(PORT_GPIO_CH_66_ACTIVE)
ISR(Port_Ch66Isr);
#endif /** #if defined(PORT_GPIO_CH_66_ACTIVE) **/

#if defined(PORT_GPIO_CH_67_ACTIVE)
ISR(Port_Ch67Isr);
#endif /** #if defined(PORT_GPIO_CH_67_ACTIVE) **/

#if defined(PORT_GPIO_CH_68_ACTIVE)
ISR(Port_Ch68Isr);
#endif /** #if defined(PORT_GPIO_CH_68_ACTIVE) **/

#if defined(PORT_GPIO_CH_69_ACTIVE)
ISR(Port_Ch69Isr);
#endif /** #if defined(PORT_GPIO_CH_69_ACTIVE) **/

#if defined(PORT_GPIO_CH_70_ACTIVE)
ISR(Port_Ch70Isr);
#endif /** #if defined(PORT_GPIO_CH_70_ACTIVE) **/

#if defined(PORT_GPIO_CH_71_ACTIVE)
ISR(Port_Ch71Isr);
#endif /** #if defined(PORT_GPIO_CH_71_ACTIVE) **/

#if defined(PORT_GPIO_CH_72_ACTIVE)
ISR(Port_Ch72Isr);
#endif /** #if defined(PORT_GPIO_CH_72_ACTIVE) **/

#if defined(PORT_GPIO_CH_73_ACTIVE)
ISR(Port_Ch73Isr);
#endif /** #if defined(PORT_GPIO_CH_73_ACTIVE) **/

#if defined(PORT_GPIO_CH_74_ACTIVE)
ISR(Port_Ch74Isr);
#endif /** #if defined(PORT_GPIO_CH_74_ACTIVE) **/

#if defined(PORT_GPIO_CH_75_ACTIVE)
ISR(Port_Ch75Isr);
#endif /** #if defined(PORT_GPIO_CH_75_ACTIVE) **/

#if defined(PORT_GPIO_CH_76_ACTIVE)
ISR(Port_Ch76Isr);
#endif /** #if defined(PORT_GPIO_CH_76_ACTIVE) **/

#if defined(PORT_GPIO_CH_77_ACTIVE)
ISR(Port_Ch77Isr);
#endif /** #if defined(PORT_GPIO_CH_77_ACTIVE) **/

#if defined(PORT_GPIO_CH_78_ACTIVE)
ISR(Port_Ch78Isr);
#endif /** #if defined(PORT_GPIO_CH_78_ACTIVE) **/

#if defined(PORT_GPIO_CH_79_ACTIVE)
ISR(Port_Ch79Isr);
#endif /** #if defined(PORT_GPIO_CH_79_ACTIVE) **/

#if defined(PORT_GPIO_CH_80_ACTIVE)
ISR(Port_Ch80Isr);
#endif /** #if defined(PORT_GPIO_CH_80_ACTIVE) **/

#if defined(PORT_GPIO_CH_81_ACTIVE)
ISR(Port_Ch81Isr);
#endif /** #if defined(PORT_GPIO_CH_81_ACTIVE) **/

#if defined(PORT_GPIO_CH_82_ACTIVE)
ISR(Port_Ch82Isr);
#endif /** #if defined(PORT_GPIO_CH_82_ACTIVE) **/

#if defined(PORT_GPIO_CH_83_ACTIVE)
ISR(Port_Ch83Isr);
#endif /** #if defined(PORT_GPIO_CH_83_ACTIVE) **/

#if defined(PORT_GPIO_CH_84_ACTIVE)
ISR(Port_Ch84Isr);
#endif /** #if defined(PORT_GPIO_CH_84_ACTIVE) **/

#if defined(PORT_GPIO_CH_85_ACTIVE)
ISR(Port_Ch85Isr);
#endif /** #if defined(PORT_GPIO_CH_85_ACTIVE) **/

#if defined(PORT_GPIO_CH_86_ACTIVE)
ISR(Port_Ch86Isr);
#endif /** #if defined(PORT_GPIO_CH_86_ACTIVE) **/

#if defined(PORT_GPIO_CH_87_ACTIVE)
ISR(Port_Ch87Isr);
#endif /** #if defined(PORT_GPIO_CH_87_ACTIVE) **/

#if defined(PORT_GPIO_CH_88_ACTIVE)
ISR(Port_Ch88Isr);
#endif /** #if defined(PORT_GPIO_CH_88_ACTIVE) **/

#if defined(PORT_GPIO_CH_89_ACTIVE)
ISR(Port_Ch89Isr);
#endif /** #if defined(PORT_GPIO_CH_89_ACTIVE) **/

#if defined(PORT_GPIO_CH_90_ACTIVE)
ISR(Port_Ch90Isr);
#endif /** #if defined(PORT_GPIO_CH_90_ACTIVE) **/

#if defined(PORT_GPIO_CH_91_ACTIVE)
ISR(Port_Ch91Isr);
#endif /** #if defined(PORT_GPIO_CH_91_ACTIVE) **/

#if defined(PORT_GPIO_CH_92_ACTIVE)
ISR(Port_Ch92Isr);
#endif /** #if defined(PORT_GPIO_CH_92_ACTIVE) **/

#if defined(PORT_GPIO_CH_93_ACTIVE)
ISR(Port_Ch93Isr);
#endif /** #if defined(PORT_GPIO_CH_93_ACTIVE) **/

#if defined(PORT_GPIO_CH_94_ACTIVE)
ISR(Port_Ch94Isr);
#endif /** #if defined(PORT_GPIO_CH_94_ACTIVE) **/

#if defined(PORT_GPIO_CH_95_ACTIVE)
ISR(Port_Ch95Isr);
#endif /** #if defined(PORT_GPIO_CH_95_ACTIVE) **/

#if defined(PORT_GPIO_CH_96_ACTIVE)
ISR(Port_Ch96Isr);
#endif /** #if defined(PORT_GPIO_CH_96_ACTIVE) **/

#if defined(PORT_GPIO_CH_97_ACTIVE)
ISR(Port_Ch97Isr);
#endif /** #if defined(PORT_GPIO_CH_97_ACTIVE) **/

#if defined(PORT_GPIO_CH_98_ACTIVE)
ISR(Port_Ch98Isr);
#endif /** #if defined(PORT_GPIO_CH_98_ACTIVE) **/

#if defined(PORT_GPIO_CH_99_ACTIVE)
ISR(Port_Ch99Isr);
#endif /** #if defined(PORT_GPIO_CH_99_ACTIVE) **/

#if defined(PORT_GPIO_CH_100_ACTIVE)
ISR(Port_Ch100Isr);
#endif /** #if defined(PORT_GPIO_CH_100_ACTIVE) **/

#if defined(PORT_GPIO_CH_101_ACTIVE)
ISR(Port_Ch101Isr);
#endif /** #if defined(PORT_GPIO_CH_101_ACTIVE) **/

#if defined(PORT_GPIO_CH_102_ACTIVE)
ISR(Port_Ch102Isr);
#endif /** #if defined(PORT_GPIO_CH_102_ACTIVE) **/

#if defined(PORT_GPIO_CH_103_ACTIVE)
ISR(Port_Ch103Isr);
#endif /** #if defined(PORT_GPIO_CH_103_ACTIVE) **/

#if defined(PORT_GPIO_CH_104_ACTIVE)
ISR(Port_Ch104Isr);
#endif /** #if defined(PORT_GPIO_CH_104_ACTIVE) **/

#if defined(PORT_GPIO_CH_105_ACTIVE)
ISR(Port_Ch105Isr);
#endif /** #if defined(PORT_GPIO_CH_105_ACTIVE) **/

#if defined(PORT_GPIO_CH_106_ACTIVE)
ISR(Port_Ch106Isr);
#endif /** #if defined(PORT_GPIO_CH_106_ACTIVE) **/

#if defined(PORT_GPIO_CH_107_ACTIVE)
ISR(Port_Ch107Isr);
#endif /** #if defined(PORT_GPIO_CH_107_ACTIVE) **/

#if defined(PORT_GPIO_CH_108_ACTIVE)
ISR(Port_Ch108Isr);
#endif /** #if defined(PORT_GPIO_CH_108_ACTIVE) **/

#if defined(PORT_GPIO_CH_109_ACTIVE)
ISR(Port_Ch109Isr);
#endif /** #if defined(PORT_GPIO_CH_109_ACTIVE) **/

#if defined(PORT_GPIO_CH_110_ACTIVE)
ISR(Port_Ch110Isr);
#endif /** #if defined(PORT_GPIO_CH_110_ACTIVE) **/

#if defined(PORT_GPIO_CH_111_ACTIVE)
ISR(Port_Ch111Isr);
#endif /** #if defined(PORT_GPIO_CH_111_ACTIVE) **/

#if defined(PORT_GPIO_CH_112_ACTIVE)
ISR(Port_Ch112Isr);
#endif /** #if defined(PORT_GPIO_CH_112_ACTIVE) **/

#if defined(PORT_GPIO_CH_113_ACTIVE)
ISR(Port_Ch113Isr);
#endif /** #if defined(PORT_GPIO_CH_113_ACTIVE) **/

#if defined(PORT_GPIO_CH_114_ACTIVE)
ISR(Port_Ch114Isr);
#endif /** #if defined(PORT_GPIO_CH_114_ACTIVE) **/

#if defined(PORT_GPIO_CH_115_ACTIVE)
ISR(Port_Ch115Isr);
#endif /** #if defined(PORT_GPIO_CH_115_ACTIVE) **/

#if defined(PORT_GPIO_CH_116_ACTIVE)
ISR(Port_Ch116Isr);
#endif /** #if defined(PORT_GPIO_CH_116_ACTIVE) **/

#if defined(PORT_GPIO_CH_117_ACTIVE)
ISR(Port_Ch117Isr);
#endif /** #if defined(PORT_GPIO_CH_117_ACTIVE) **/

#if defined(PORT_GPIO_CH_118_ACTIVE)
ISR(Port_Ch118Isr);
#endif /** #if defined(PORT_GPIO_CH_118_ACTIVE) **/

#if defined(PORT_GPIO_CH_119_ACTIVE)
ISR(Port_Ch119Isr);
#endif /** #if defined(PORT_GPIO_CH_119_ACTIVE) **/

#if defined(PORT_GPIO_CH_120_ACTIVE)
ISR(Port_Ch120Isr);
#endif /** #if defined(PORT_GPIO_CH_120_ACTIVE) **/

#if defined(PORT_GPIO_CH_121_ACTIVE)
ISR(Port_Ch121Isr);
#endif /** #if defined(PORT_GPIO_CH_121_ACTIVE) **/

#if defined(PORT_GPIO_CH_122_ACTIVE)
ISR(Port_Ch122Isr);
#endif /** #if defined(PORT_GPIO_CH_122_ACTIVE) **/

#if defined(PORT_GPIO_CH_123_ACTIVE)
ISR(Port_Ch123Isr);
#endif /** #if defined(PORT_GPIO_CH_123_ACTIVE) **/

#if defined(PORT_GPIO_CH_124_ACTIVE)
ISR(Port_Ch124Isr);
#endif /** #if defined(PORT_GPIO_CH_124_ACTIVE) **/

#if defined(PORT_GPIO_CH_125_ACTIVE)
ISR(Port_Ch125Isr);
#endif /** #if defined(PORT_GPIO_CH_125_ACTIVE) **/

#if defined(PORT_GPIO_CH_126_ACTIVE)
ISR(Port_Ch126Isr);
#endif /** #if defined(PORT_GPIO_CH_126_ACTIVE) **/

#if defined(PORT_GPIO_CH_127_ACTIVE)
ISR(Port_Ch127Isr);
#endif /** #if defined(PORT_GPIO_CH_127_ACTIVE) **/

#if defined(PORT_GPIO_CH_128_ACTIVE)
ISR(Port_Ch128Isr);
#endif /** #if defined(PORT_GPIO_CH_128_ACTIVE) **/

#if defined(PORT_GPIO_CH_129_ACTIVE)
ISR(Port_Ch129Isr);
#endif /** #if defined(PORT_GPIO_CH_129_ACTIVE) **/

#if defined(PORT_GPIO_CH_130_ACTIVE)
ISR(Port_Ch130Isr);
#endif /** #if defined(PORT_GPIO_CH_130_ACTIVE) **/

#if defined(PORT_GPIO_CH_131_ACTIVE)
ISR(Port_Ch131Isr);
#endif /** #if defined(PORT_GPIO_CH_131_ACTIVE) **/

#if defined(PORT_GPIO_CH_132_ACTIVE)
ISR(Port_Ch132Isr);
#endif /** #if defined(PORT_GPIO_CH_132_ACTIVE) **/

#if defined(PORT_GPIO_CH_133_ACTIVE)
ISR(Port_Ch133Isr);
#endif /** #if defined(PORT_GPIO_CH_133_ACTIVE) **/

#if defined(PORT_GPIO_CH_134_ACTIVE)
ISR(Port_Ch134Isr);
#endif /** #if defined(PORT_GPIO_CH_134_ACTIVE) **/

#if defined(PORT_GPIO_CH_135_ACTIVE)
ISR(Port_Ch135Isr);
#endif /** #if defined(PORT_GPIO_CH_135_ACTIVE) **/

#if defined(PORT_GPIO_CH_136_ACTIVE)
ISR(Port_Ch136Isr);
#endif /** #if defined(PORT_GPIO_CH_136_ACTIVE) **/

#if defined(PORT_GPIO_CH_137_ACTIVE)
ISR(Port_Ch137Isr);
#endif /** #if defined(PORT_GPIO_CH_137_ACTIVE) **/

#if defined(PORT_GPIO_CH_138_ACTIVE)
ISR(Port_Ch138Isr);
#endif /** #if defined(PORT_GPIO_CH_138_ACTIVE) **/

#if defined(PORT_GPIO_CH_139_ACTIVE)
ISR(Port_Ch139Isr);
#endif /** #if defined(PORT_GPIO_CH_139_ACTIVE) **/

#endif /** #if ((PORT_ISR_TYPE == PORT_ISR_CAT1) || (PORT_ISR_TYPE == PORT_ISR_VOID)) **/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PORT_IRQ_H_ */

/*******************************************************************************
 *  END OF FILE: Port_Irq.h
 *******************************************************************************/
