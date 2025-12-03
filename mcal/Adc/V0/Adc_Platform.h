/*
 * Copyright (C) 2022-2023 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ADC_PLATFORM_H_
#define ADC_PLATFORM_H_

/**
 * \addtogroup ADC Adc API GUIDE Header file
 * @{
 */

/*****************************************************************************
 *
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 *
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *
 *! Header Files
 *
 ******************************************************************************/
#include "Std_Types.h"
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"
#include "Adc_Reg.h"
#include "Adc_RegResult.h"
/*****************************************************************************
 *
 * Values that can be passed to ADC_enablePPBEvent(), ADC_disablePPBEvent(),
 * ADC_enablePPBEventInterrupt(), ADC_disablePPBEventInterrupt(), and
 * ADC_clearPPBEventStatus() as the intFlags and evtFlags parameters. They also
 * make up the enumerated bit field returned by ADC_getPPBEventStatus().
 *
 *****************************************************************************/
/** \brief Trip High Event */
#define ADC_EVT_TRIPHI (0x0001U)
/** \brief Trip Low Event */
#define ADC_EVT_TRIPLO (0x0002U)
/** \brief Zero Crossing Event */
#define ADC_EVT_ZERO (0x0004U)

/*****************************************************************************
 *
 * Values that can be passed to ADC_forceMultipleSOC() as socMask parameter.
 * These values can be OR'd together to trigger multiple SOCs at a time.
 *
 ******************************************************************************/
/** \brief  SW trigger ADC SOC 0 */
#define ADC_FORCE_SOC0 (0x0001U)
/** \brief  SW trigger ADC SOC 1 */
#define ADC_FORCE_SOC1 (0x0002U)
/** \brief  SW trigger ADC SOC 2 */
#define ADC_FORCE_SOC2 (0x0004U)
/** \brief  SW trigger ADC SOC 3 */
#define ADC_FORCE_SOC3 (0x0008U)
/** \brief  SW trigger ADC SOC 4 */
#define ADC_FORCE_SOC4 (0x0010U)
/** \brief  SW trigger ADC SOC 5 */
#define ADC_FORCE_SOC5 (0x0020U)
/** \brief  SW trigger ADC SOC 6 */
#define ADC_FORCE_SOC6 (0x0040U)
/** \brief  SW trigger ADC SOC 7 */
#define ADC_FORCE_SOC7 (0x0080U)
/** \brief  SW trigger ADC SOC 8 */
#define ADC_FORCE_SOC8 (0x0100U)
/** \brief  SW trigger ADC SOC 9 */
#define ADC_FORCE_SOC9 (0x0200U)
/** \brief  SW trigger ADC SOC 10 */
#define ADC_FORCE_SOC10 (0x0400U)
/** \brief  SW trigger ADC SOC 11 */
#define ADC_FORCE_SOC11 (0x0800U)
/** \brief  SW trigger ADC SOC 12 */
#define ADC_FORCE_SOC12 (0x1000U)
/** \brief  SW trigger ADC SOC 13 */
#define ADC_FORCE_SOC13 (0x2000U)
/** \brief  SW trigger ADC SOC 14 */
#define ADC_FORCE_SOC14 (0x4000U)
/** \brief  SW trigger ADC SOC 15 */
#define ADC_FORCE_SOC15 (0x8000U)

/** \brief Values that can be passed to ADC_setPrescaler() as the \e clkPrescale
 parameter. */

typedef enum
{
    /** \brief  ADCCLK = (input clock) / 1.0 */
    ADC_CLK_DIV_1_0 = 0,
    /** \brief  ADCCLK = (input clock) / 2.0 */
    ADC_CLK_DIV_2_0 = 2,
    /** \brief  ADCCLK = (input clock) / 2.5 */
    ADC_CLK_DIV_2_5 = 3,
    /** \brief  ADCCLK = (input clock) / 3.0 */
    ADC_CLK_DIV_3_0 = 4,
    /** \brief  ADCCLK = (input clock) / 3.5 */
    ADC_CLK_DIV_3_5 = 5,
    /** \brief  ADCCLK = (input clock) / 4.0 */
    ADC_CLK_DIV_4_0 = 6,
    /** \brief  ADCCLK = (input clock) / 4.5 */
    ADC_CLK_DIV_4_5 = 7,
    /** \brief  ADCCLK = (input clock) / 5.0 */
    ADC_CLK_DIV_5_0 = 8,
    /** \brief  ADCCLK = (input clock) / 5.5 */
    ADC_CLK_DIV_5_5 = 9,
    /** \brief  ADCCLK = (input clock) / 6.0 */
    ADC_CLK_DIV_6_0 = 10,
    /** \brief  ADCCLK = (input clock) / 6.5 */
    ADC_CLK_DIV_6_5 = 11,
    /** \brief  ADCCLK = (input clock) / 7.0 */
    ADC_CLK_DIV_7_0 = 12,
    /** \brief  ADCCLK = (input clock) / 7.5 */
    ADC_CLK_DIV_7_5 = 13,
    /** \brief  ADCCLK = (input clock) / 8.0 */
    ADC_CLK_DIV_8_0 = 14,
    /** \brief  ADCCLK = (input clock) / 8.5 */
    ADC_CLK_DIV_8_5 = 15
} Adc_mcalClkPrescale_t;

/** \brief Values that can be passed to ADC_setMode() as the \e resolution
 parameter. */

typedef enum
{
    /** \brief  12-bit conversion resolution */
    ADC_RESOLUTION_12BIT = 0
} Adc_mcalResolution_t;

/** \brief Values that can be passed to ADC_setMode() as the \e signalMode
 parameter. */

typedef enum
{
    /** \brief  Sample on single pin with VREFLO */
    ADC_MODE_SINGLE_ENDED = 0,
    /** \brief  Sample on pair of pins */
    ADC_MODE_DIFFERENTIAL = 1
} Adc_mcalSignalMode_t;

/** \brief Values that can be passed to ADC_setupSOC() as the \e trigger
parameter to specify the event that will trigger a conversion to start.
It is also used with ADC_setBurstModeConfig(). */

typedef enum
{
    /** \brief  Software only */
    ADC_TRIGGER_SW_ONLY = 0x00,
    /** \brief  RTI Timer 0 */
    ADC_TRIGGER_RTI0 = 0x01,
    /** \brief  RTI Timer 1 */
    ADC_TRIGGER_RTI1 = 0x02,
    /** \brief  RTI Timer 2 */
    ADC_TRIGGER_RTI2 = 0x03,
    /** \brief  RTI Timer 3 */
    ADC_TRIGGER_RTI3 = 0x04,
    /** \brief  InputXBar.Out[5] */
    ADC_TRIGGER_INPUT_XBAR_OUT5 = 0x05,
    /** \brief  ePWM0, ADCSOCA */
    ADC_TRIGGER_EPWM0_SOCA = 0x08,
    /** \brief  ePWM0, ADCSOCB */
    ADC_TRIGGER_EPWM0_SOCB = 0x09,
    /** \brief  ePWM1, ADCSOCA */
    ADC_TRIGGER_EPWM1_SOCA = 0x0A,
    /** \brief  ePWM1, ADCSOCB */
    ADC_TRIGGER_EPWM1_SOCB = 0x0B,
    /** \brief  ePWM2, ADCSOCA */
    ADC_TRIGGER_EPWM2_SOCA = 0x0C,
    /** \brief  ePWM2, ADCSOCB */
    ADC_TRIGGER_EPWM2_SOCB = 0x0D,
    /** \brief  ePWM3, ADCSOCA */
    ADC_TRIGGER_EPWM3_SOCA = 0x0E,
    /** \brief  ePWM3, ADCSOCB */
    ADC_TRIGGER_EPWM3_SOCB = 0x0F,
    /** \brief  ePWM4, ADCSOCA */
    ADC_TRIGGER_EPWM4_SOCA = 0x10,
    /** \brief  ePWM4, ADCSOCB */
    ADC_TRIGGER_EPWM4_SOCB = 0x11,
    /** \brief  ePWM5, ADCSOCA */
    ADC_TRIGGER_EPWM5_SOCA = 0x12,
    /** \brief  ePWM5, ADCSOCB */
    ADC_TRIGGER_EPWM5_SOCB = 0x13,
    /** \brief  ePWM6, ADCSOCA */
    ADC_TRIGGER_EPWM6_SOCA = 0x14,
    /** \brief  ePWM6, ADCSOCB */
    ADC_TRIGGER_EPWM6_SOCB = 0x15,
    /** \brief  ePWM7, ADCSOCA */
    ADC_TRIGGER_EPWM7_SOCA = 0x16,
    /** \brief  ePWM7, ADCSOCB */
    ADC_TRIGGER_EPWM7_SOCB = 0x17,
    /** \brief  ePWM8, ADCSOCA */
    ADC_TRIGGER_EPWM8_SOCA = 0x18,
    /** \brief  ePWM8, ADCSOCB */
    ADC_TRIGGER_EPWM8_SOCB = 0x19,
    /** \brief  ePWM9, ADCSOCA */
    ADC_TRIGGER_EPWM9_SOCA = 0x1A,
    /** \brief  ePWM9, ADCSOCB */
    ADC_TRIGGER_EPWM9_SOCB = 0x1B,
    /** \brief  ePWM10, ADCSOCA */
    ADC_TRIGGER_EPWM10_SOCA = 0x1C,
    /** \brief  ePWM10, ADCSOCB */
    ADC_TRIGGER_EPWM10_SOCB = 0x1D,
    /** \brief  ePWM11, ADCSOCA */
    ADC_TRIGGER_EPWM11_SOCA = 0x1E,
    /** \brief  ePWM11, ADCSOCB */
    ADC_TRIGGER_EPWM11_SOCB = 0x1F,
    /** \brief  ePWM12, ADCSOCA */
    ADC_TRIGGER_EPWM12_SOCA = 0x20,
    /** \brief  ePWM12, ADCSOCB */
    ADC_TRIGGER_EPWM12_SOCB = 0x21,
    /** \brief  ePWM13, ADCSOCA */
    ADC_TRIGGER_EPWM13_SOCA = 0x22,
    /** \brief  ePWM13, ADCSOCB */
    ADC_TRIGGER_EPWM13_SOCB = 0x23,
    /** \brief  ePWM14, ADCSOCA */
    ADC_TRIGGER_EPWM14_SOCA = 0x24,
    /** \brief  ePWM14, ADCSOCB */
    ADC_TRIGGER_EPWM14_SOCB = 0x25,
    /** \brief  ePWM15, ADCSOCA */
    ADC_TRIGGER_EPWM15_SOCA = 0x26,
    /** \brief  ePWM15, ADCSOCB */
    ADC_TRIGGER_EPWM15_SOCB = 0x27,
    /** \brief  ePWM16, ADCSOCA */
    ADC_TRIGGER_EPWM16_SOCA = 0x28,
    /** \brief  ePWM16, ADCSOCB */
    ADC_TRIGGER_EPWM16_SOCB = 0x29,
    /** \brief  ePWM17, ADCSOCA */
    ADC_TRIGGER_EPWM17_SOCA = 0x2A,
    /** \brief  ePWM17, ADCSOCB */
    ADC_TRIGGER_EPWM17_SOCB = 0x2B,
    /** \brief  ePWM18, ADCSOCA */
    ADC_TRIGGER_EPWM18_SOCA = 0x2C,
    /** \brief  ePWM18, ADCSOCB */
    ADC_TRIGGER_EPWM18_SOCB = 0x2D,
    /** \brief  ePWM19, ADCSOCA */
    ADC_TRIGGER_EPWM19_SOCA = 0x2E,
    /** \brief  ePWM19, ADCSOCB */
    ADC_TRIGGER_EPWM19_SOCB = 0x2F,
    /** \brief  ePWM20, ADCSOCA */
    ADC_TRIGGER_EPWM20_SOCA = 0x30,
    /** \brief  ePWM20, ADCSOCB */
    ADC_TRIGGER_EPWM20_SOCB = 0x31,
    /** \brief  ePWM21, ADCSOCA */
    ADC_TRIGGER_EPWM21_SOCA = 0x32,
    /** \brief  ePWM21, ADCSOCB */
    ADC_TRIGGER_EPWM21_SOCB = 0x33,
    /** \brief  ePWM22, ADCSOCA */
    ADC_TRIGGER_EPWM22_SOCA = 0x34,
    /** \brief  ePWM22, ADCSOCB */
    ADC_TRIGGER_EPWM22_SOCB = 0x35,
    /** \brief  ePWM23, ADCSOCA */
    ADC_TRIGGER_EPWM23_SOCA = 0x36,
    /** \brief  ePWM23, ADCSOCB */
    ADC_TRIGGER_EPWM23_SOCB = 0x37,
    /** \brief  ePWM24, ADCSOCA */
    ADC_TRIGGER_EPWM24_SOCA = 0x38,
    /** \brief  ePWM24, ADCSOCB */
    ADC_TRIGGER_EPWM24_SOCB = 0x39,
    /** \brief  ePWM25, ADCSOCA */
    ADC_TRIGGER_EPWM25_SOCA = 0x3A,
    /** \brief  ePWM25, ADCSOCB */
    ADC_TRIGGER_EPWM25_SOCB = 0x3B,
    /** \brief  ePWM26, ADCSOCA */
    ADC_TRIGGER_EPWM26_SOCA = 0x3C,
    /** \brief  ePWM26, ADCSOCB */
    ADC_TRIGGER_EPWM26_SOCB = 0x3D,
    /** \brief  ePWM27, ADCSOCA */
    ADC_TRIGGER_EPWM27_SOCA = 0x3E,
    /** \brief  ePWM27, ADCSOCB */
    ADC_TRIGGER_EPWM27_SOCB = 0x3F,
    /** \brief  ePWM28, ADCSOCA */
    ADC_TRIGGER_EPWM28_SOCA = 0x40,
    /** \brief  ePWM28, ADCSOCB */
    ADC_TRIGGER_EPWM28_SOCB = 0x41,
    /** \brief  ePWM29, ADCSOCA */
    ADC_TRIGGER_EPWM29_SOCA = 0x42,
    /** \brief  ePWM29, ADCSOCB */
    ADC_TRIGGER_EPWM29_SOCB = 0x43,
    /** \brief  ePWM30, ADCSOCA */
    ADC_TRIGGER_EPWM30_SOCA = 0x44,
    /** \brief  ePWM30, ADCSOCB */
    ADC_TRIGGER_EPWM30_SOCB = 0x45,
    /** \brief  ePWM31, ADCSOCA */
    ADC_TRIGGER_EPWM31_SOCA = 0x46,
    /** \brief  ePWM31, ADCSOCB */
    ADC_TRIGGER_EPWM31_SOCB = 0x47,
    /** \brief  ECAP0 */
    ADC_TRIGGER_ECAP0 = 0x48,
    /** \brief  ECAP1 */
    ADC_TRIGGER_ECAP1 = 0x49,
    /** \brief  ECAP2 */
    ADC_TRIGGER_ECAP2 = 0x4A,
    /** \brief  ECAP3 */
    ADC_TRIGGER_ECAP3 = 0x4B,
    /** \brief  ECAP4 */
    ADC_TRIGGER_ECAP4 = 0x4C,
    /** \brief  ECAP5 */
    ADC_TRIGGER_ECAP5 = 0x4D,
    /** \brief  ECAP6 */
    ADC_TRIGGER_ECAP6 = 0x4E,
    /** \brief  ECAP7 */
    ADC_TRIGGER_ECAP7 = 0x4F,
    /** \brief  ECAP8 */
    ADC_TRIGGER_ECAP8 = 0x50,
    /** \brief  ECAP9 */
    ADC_TRIGGER_ECAP9 = 0x51,
    /** \brief  Spare */
    ADC_TRIGGER_NONE = 0x7F
} Adc_mcalTrigger_t;

/** \brief Values that can be passed to ADC_setupSOC() as the \e channel
 parameter. This is the input pin on which the signal to be converted is
 located. */

typedef enum
{
    /** \brief  single-ended, ADCIN0 */
    ADC_CH_ADCIN0 = 0,
    /** \brief  single-ended, ADCIN1 */
    ADC_CH_ADCIN1 = 1,
    /** \brief  single-ended, ADCIN2 */
    ADC_CH_ADCIN2 = 2,
    /** \brief  single-ended, ADCIN3 */
    ADC_CH_ADCIN3 = 3,
    /** \brief  single-ended, ADCIN4 */
    ADC_CH_ADCIN4 = 4,
    /** \brief  single-ended, ADCIN5 */
    ADC_CH_ADCIN5 = 5,
    /** \brief  single-ended, CAL0 */
    ADC_CH_CAL0 = 6,
    /** \brief  single-ended, CAL1 */
    ADC_CH_CAL1 = 7,
    /** \brief  differential, ADCIN0 and ADCIN1 */
    ADC_CH_ADCIN0_ADCIN1 = 0,
    /** \brief  differential, ADCIN1 and ADCIN0 */
    ADC_CH_ADCIN1_ADCIN0 = 1,
    /** \brief  differential, ADCIN2 and ADCIN3 */
    ADC_CH_ADCIN2_ADCIN3 = 2,
    /** \brief  differential, ADCIN3 and ADCIN2 */
    ADC_CH_ADCIN3_ADCIN2 = 3,
    /** \brief  differential, ADCIN4 and ADCIN5 */
    ADC_CH_ADCIN4_ADCIN5 = 4,
    /** \brief  differential, ADCIN5 and ADCIN4 */
    ADC_CH_ADCIN5_ADCIN4 = 5,
    /** \brief  differential, CAL0 and CAL1 */
    ADC_CH_CAL0_CAL1 = 6,
} Adc_mcalChannel_t;

/** \brief Values that can be passed to ADC_setInterruptPulseMode() as the
 \e pulseMode parameter. */

typedef enum
{
    /** \brief  Occurs at the end of the acquisition window*/
    ADC_PULSE_END_OF_ACQ_WIN = 0,
    /** \brief  Occurs at the end of the conversion*/
    ADC_PULSE_END_OF_CONV = 1
} Adc_mcalPulseMode_t;

/** \brief Values that can be passed to ADC_enableInterrupt(), ADC_disableInterrupt(),
 ADC_clearInterruptStatus(), ADC_getInterruptOverflowStatus(),
 ADC_clearInterruptOverflowStatus(), ADC_setInterruptSource(),
 ADC_enableContinuousMode(), ADC_disableContinuousMode()
 and ADC_getInterruptStatus() as the \e adcIntNum parameter. */

typedef enum
{
    /** \brief  ADCINT1 Interrupt*/
    ADC_INT_NUMBER1 = 0,
    /** \brief  ADCINT2 Interrupt*/
    ADC_INT_NUMBER2 = 1,
    /** \brief  ADCINT3 Interrupt*/
    ADC_INT_NUMBER3 = 2,
    /** \brief  ADCINT4 Interrupt*/
    ADC_INT_NUMBER4 = 3
} Adc_mcalIntNumber_t;

/** \brief Values that can be passed in as the \e ppbNumber parameter for several
 functions. */

typedef enum
{
    /** \brief  Post-processing block 1*/
    ADC_PPB_NUMBER1 = 0,
    /** \brief  Post-processing block 2*/
    ADC_PPB_NUMBER2 = 1,
    /** \brief  Post-processing block 3*/
    ADC_PPB_NUMBER3 = 2,
    /** \brief  Post-processing block 4*/
    ADC_PPB_NUMBER4 = 3
} Adc_mcalPPBNumber_t;

/** \brief Values that can be passed in as the \e socNumber parameter for several
 functions. This value identifies the start-of-conversion (SOC) that a
 function is configuring or accessing. Note that in some cases (for example,
 ADC_setInterruptSource()) \e socNumber is used to refer to the
 corresponding end-of-conversion (EOC). */

typedef enum
{
    /** \brief  SOC/EOC number 0*/
    ADC_SOC_NUMBER0 = 0,
    /** \brief  SOC/EOC number 1*/
    ADC_SOC_NUMBER1 = 1,
    /** \brief  SOC/EOC number 2*/
    ADC_SOC_NUMBER2 = 2,
    /** \brief  SOC/EOC number 3*/
    ADC_SOC_NUMBER3 = 3,
    /** \brief  SOC/EOC number 4*/
    ADC_SOC_NUMBER4 = 4,
    /** \brief  SOC/EOC number 5*/
    ADC_SOC_NUMBER5 = 5,
    /** \brief  SOC/EOC number 6*/
    ADC_SOC_NUMBER6 = 6,
    /** \brief  SOC/EOC number 7*/
    ADC_SOC_NUMBER7 = 7,
    /** \brief  SOC/EOC number 8*/
    ADC_SOC_NUMBER8 = 8,
    /** \brief  SOC/EOC number 9*/
    ADC_SOC_NUMBER9 = 9,
    /** \brief  SOC/EOC number 10*/
    ADC_SOC_NUMBER10 = 10,
    /** \brief  SOC/EOC number 11*/
    ADC_SOC_NUMBER11 = 11,
    /** \brief  SOC/EOC number 12*/
    ADC_SOC_NUMBER12 = 12,
    /** \brief  SOC/EOC number 13*/
    ADC_SOC_NUMBER13 = 13,
    /** \brief  SOC/EOC number 14*/
    ADC_SOC_NUMBER14 = 14,
    /** \brief  SOC/EOC number 15*/
    ADC_SOC_NUMBER15 = 15,
    /** \brief  SOC/EOC number 16*/
    ADC_INVALID_HW_SOC = 16
} Adc_mcalSOCNumber_t;

/** \brief Values that can be passed in as the \e trigger parameter for the
 ADC_setInterruptSOCTrigger() function. */

typedef enum
{
    /** \brief  No ADCINT will trigger the SOC*/
    ADC_INT_SOC_TRIGGER_NONE = 0,
    /** \brief  ADCINT1 will trigger the SOC*/
    ADC_INT_SOC_TRIGGER_ADCINT1 = 1,
    /** \brief  ADCINT2 will trigger the SOC*/
    ADC_INT_SOC_TRIGGER_ADCINT2 = 2
} Adc_mcalIntSOCTrigger_t;

/** \brief Values that can be passed to ADC_setSOCPriority() as the \e priMode
 parameter. */

typedef enum
{
    /** \brief  Round robin mode is used for all*/
    ADC_PRI_ALL_ROUND_ROBIN = 0,
    /** \brief  SOC 0 hi pri, others in round robin*/
    ADC_PRI_SOC0_HIPRI = 1,
    /** \brief  SOC 0-1 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC1_HIPRI = 2,
    /** \brief  SOC 0-2 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC2_HIPRI = 3,
    /** \brief  SOC 0-3 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC3_HIPRI = 4,
    /** \brief  SOC 0-4 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC4_HIPRI = 5,
    /** \brief  SOC 0-5 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC5_HIPRI = 6,
    /** \brief  SOC 0-6 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC6_HIPRI = 7,
    /** \brief  SOC 0-7 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC7_HIPRI = 8,
    /** \brief  SOC 0-8 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC8_HIPRI = 9,
    /** \brief  SOC 0-9 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC9_HIPRI = 10,
    /** \brief  SOC 0-10 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC10_HIPRI = 11,
    /** \brief  SOC 0-11 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC11_HIPRI = 12,
    /** \brief  SOC 0-12 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC12_HIPRI = 13,
    /** \brief  SOC 0-13 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC13_HIPRI = 14,
    /** \brief  SOC 0-14 hi pri, others in round robin*/
    ADC_PRI_THRU_SOC14_HIPRI = 15,
    /** \brief  All priorities based on SOC number*/
    ADC_PRI_ALL_HIPRI = 16
} Adc_mcalPriorityMode_t;

/*****************************************************************************
 *
 *! Defines used by the driver
 *
 ******************************************************************************/
/** \brief   Register offset difference between 2 ADCSOCxCTL registers*/
#define MCAL_ADC_ADCSOCxCTL_STEP (MCAL_CSL_ADC_ADCSOC1CTL - MCAL_CSL_ADC_ADCSOC0CTL)
/** \brief  Register offset difference between 2 ADCINTSELxNy registers*/
#define MCAL_ADC_ADCINTSELxNy_STEP (MCAL_CSL_ADC_ADCINTSEL3N4 - MCAL_CSL_ADC_ADCINTSEL1N2)
/** \brief  Register offset difference between 2 ADCPPBxCONFIG registers*/
#define MCAL_ADC_ADCPPBx_STEP (MCAL_CSL_ADC_ADCPPB2CONFIG - MCAL_CSL_ADC_ADCPPB1CONFIG)
/** \brief  ADC PPB Trip Mask*/
#define MCAL_ADC_ADCPPBTRIP_MASK \
    ((uint32)MCAL_CSL_ADC_ADCPPB1TRIPHI_LIMITHI_MASK | (uint32)MCAL_CSL_ADC_ADCPPB1TRIPHI_HSIGN_MASK)
/** \brief  Register offset difference between 2 ADCPPBxRESULT registers*/
#define MCAL_ADC_RESULT_ADCPPBxRESULT_STEP (MCAL_CSL_ADC_RESULT_ADCPPB2RESULT - MCAL_CSL_ADC_RESULT_ADCPPB1RESULT)
/** \brief  Register offset difference between 2 ADCRESULTx registers*/
#define MCAL_ADC_RESULT_ADCRESULTx_STEP (MCAL_CSL_ADC_RESULT_ADCRESULT1 - MCAL_CSL_ADC_RESULT_ADCRESULT0)

/*****************************************************************************
 *
 * Prototypes for the APIs.
 *
 *****************************************************************************/
/** \brief Start Memory section tag */
#define ADC_START_SEC_CODE
#include "Adc_MemMap.h"

/** \brief Configures the analog-to-digital converter module prescaler.
 *
 *
 * This function configures the ADC module's ADCCLK.
 *
 * \param[in] base base address of the ADC module.
 * \param[in] clkPrescale specifies the value by which the input clock is
 * divided to make the ADCCLK. The clkPrescale value can be specified with
 * any of the following variables:
 * \b ADC_CLK_DIV_1_0, \b ADC_CLK_DIV_2_0, \b ADC_CLK_DIV_2_5, ...,
 * \b ADC_CLK_DIV_7_5, \b ADC_CLK_DIV_8_0, or \b ADC_CLK_DIV_8_5.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setPrescaler(uint32 base, Adc_mcalClkPrescale_t clkPrescale)
{
    /*
     * Set the configuration of the ADC module prescaler.
     */
    HW_WR_REG16(
        base + MCAL_CSL_ADC_ADCCTL2,
        ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCCTL2) & ~MCAL_CSL_ADC_ADCCTL2_PRESCALE_MASK) | (uint16)clkPrescale));
}

/** \brief Configures a start-of-conversion (SOC) in the ADC.
 *
 *
 * This function configures the a start-of-conversion (SOC) in the ADC module.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] socNumber - number of the start-of-conversion.
 * The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
 * from 0 to 15 specifying which SOC is to be configured on the ADC module
 * specified by \e base.
 * \param[in] trigger - the source that will cause the SOC.
 * The \e trigger specifies the event that causes the SOC such as software, a
 * timer interrupt, an ePWM event, or an ADC interrupt. It should be a value
 * in the format of \b ADC_TRIGGER_XXXX where XXXX is the event such as
 * \b ADC_TRIGGER_SW_ONLY, \b ADC_TRIGGER_EPWM1_SOCA, and so on.
 * \param[in] channel - number associated with the input signal.
 * The \e channel parameter specifies the channel to be converted. In
 * single-ended mode this is a single pin given by \b ADC_CH_ADCINx where x is
 * the number identifying the pin between 0 and 5 inclusive. In differential
 * mode, two pins are used as inputs and are passed in the \e channel
 * parameter as \b ADC_CH_ADCIN0_ADCIN1, \b ADC_CH_ADCIN2_ADCIN3, ..., or
 * \b ADC_CH_ADCIN14_ADCIN5.
 * \param[in] sampleWindow - acquisition window duration.
 * The \e sampleWindow parameter is the acquisition window duration in SYSCLK
 * cycles. It should be a value between 1 and 512 cycles inclusive. The
 * selected duration must be at least as long as one ADCCLK cycle. Also, the
 * datasheet will specify a minimum window duration requirement in
 * nanoseconds.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE)
    ADC_setupSOC(uint32 base, uint32 socNumber, Adc_mcalTrigger_t trigger, uint32 channel, uint32 sampleWindow)
{
    uint32 ctlRegAddr;

    /*
     * Check the arguments.
     */

    /*
     * Calculate address for the SOC control register.
     */
    ctlRegAddr = base + MCAL_CSL_ADC_ADCSOC0CTL + ((uint32)socNumber * MCAL_ADC_ADCSOCxCTL_STEP);

    /*
     * Set the configuration of the specified SOC.
     */
    HW_WR_REG32(ctlRegAddr, (((uint32)channel << MCAL_CSL_ADC_ADCSOC0CTL_CHSEL_SHIFT) |
                             ((uint32)trigger << MCAL_CSL_ADC_ADCSOC0CTL_TRIGSEL_SHIFT) | (sampleWindow - 1U)));
}

/** \brief Configures the interrupt SOC trigger of an SOC.
 *
 *
 * This function configures the interrupt start-of-conversion trigger in
 * the ADC module. This functionality is useful for creating continuous conversions.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] socNumber - number of the start-of-conversion.
 * The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
 * from 0 to 15 specifying which SOC is to be configured on the ADC module
 * specified by \e base.
 * \param[in] trigger - the interrupt source that will cause the SOC.
 * The \e trigger specifies the interrupt that causes a start of conversion or
 * none. It should be one of the following values.
 * - \b ADC_INT_SOC_TRIGGER_NONE
 * - \b ADC_INT_SOC_TRIGGER_ADCINT1
 * - \b ADC_INT_SOC_TRIGGER_ADCINT2
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE)
    ADC_setInterruptSOCTrigger(uint32 base, uint16 socNumber, Adc_mcalIntSOCTrigger_t trigger)
{
    uint16 shiftVal;

    /*
     * Each SOC has a 2-bit field in this register.
     */
    shiftVal = (uint16)socNumber << 1U;

    /*
     * Set the configuration of the specified SOC. Note that we're treating
     * ADCINTSOCSEL1 and ADCINTSOCSEL2 as one 32-bit register here.
     */
    HW_WR_REG32(base + MCAL_CSL_ADC_ADCINTSOCSEL1, ((HW_RD_REG32(base + MCAL_CSL_ADC_ADCINTSOCSEL1) &
                                                     ~((uint32)MCAL_CSL_ADC_ADCINTSOCSEL1_SOC0_MASK << shiftVal)) |
                                                    ((uint32)trigger << shiftVal)));
}

/** \brief Sets the timing of the end-of-conversion pulse
 *
 *
 * This function configures the end-of-conversion (EOC) pulse generated by ADC.
 * This pulse will be generated either at the end of the acquisition window
 * plus a number of SYSCLK cycles configured by ADC_setInterruptCycleOffset()
 * (pass \b ADC_PULSE_END_OF_ACQ_WIN into \e pulseMode) or at the end of the
 * voltage conversion, one cycle prior to the ADC result latching into it's
 * result register (pass \b ADC_PULSE_END_OF_CONV into \e pulseMode).
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] pulseMode - generation mode of the EOC pulse.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setInterruptPulseMode(uint32 base, Adc_mcalPulseMode_t pulseMode)
{
    /*
     * Set the position of the pulse.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCCTL1,
                ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCCTL1) & ~MCAL_CSL_ADC_ADCCTL1_INTPULSEPOS_MASK) |
                 ((uint16)pulseMode << MCAL_CSL_ADC_ADCCTL1_INTPULSEPOS_SHIFT)));
}

/** \brief Sets the timing of early interrupt generation.
 *
 *
 * This function configures cycle offset between the negative edge of a sample
 * pulse and an early interrupt pulse being generated. This number of cycles
 * is specified with the \e cycleOffset parameter.
 *
 * This function only applies when early interrupt generation is enabled. That
 * means the ADC_setInterruptPulseMode() function \e pulseMode parameter is
 * configured as \b ADC_PULSE_END_OF_ACQ_WIN.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] cycleOffset - cycles from an SOC falling edge to an early
 * interrupt pulse
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setInterruptCycleOffset(uint32 base, uint16 cycleOffset)
{
    /*
     * Set the position of the pulse.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCINTCYCLE, cycleOffset);
}

/** \brief Powers up the analog-to-digital converter core.
 *
 *
 * This function powers up the analog circuitry inside the analog core.
 *
 * \note Allow at least a 500us delay before sampling after calling this API.
 * If you enable multiple ADCs, you can delay after they all have begun
 * powering up.
 *
 * \param[in] base - base address of the ADC module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_enableConverter(uint32 base)
{
    /*
     * Set the bit that powers up the analog circuitry.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCCTL1,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCCTL1) | MCAL_CSL_ADC_ADCCTL1_ADCPWDNZ_MASK));
}

/** \brief Powers down the analog-to-digital converter module.
 *
 *
 * This function powers down the analog circuitry inside the analog core..
 *
 * \param[in] base - base address of the ADC module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_disableConverter(uint32 base)
{
    /*
     * Clear the bit that powers down the analog circuitry.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCCTL1,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCCTL1) & ~MCAL_CSL_ADC_ADCCTL1_ADCPWDNZ_MASK));
}

/** \brief Forces a SOC flag to a 1 in the analog-to-digital converter.
 *
 *
 * This function forces the SOC flag associated with the SOC specified by
 * \e socNumber. This initiates a conversion once that SOC is given
 * priority. This software trigger can be used whether or not the SOC has been
 * configured to accept some other specific trigger.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] socNumber - number of the start-of-conversion.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_forceSOC(uint32 base, Adc_mcalSOCNumber_t socNumber)
{
    /*
     * Write to the register that will force a 1 to the corresponding SOC flag
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCSOCFRC1, ((uint16)((uint16)1U << (uint16)socNumber)));
}

/** \brief Forces multiple SOC flags to 1 in the analog-to-digital converter.
 *
 *
 * This function forces the SOCFRC1 flags associated with the SOCs specified
 * by \e socMask. This initiates a conversion once the desired SOCs are given
 * priority. This software trigger can be used whether or not the SOC has been
 * configured to accept some other specific trigger.
 * Valid values for \e socMask parameter can be any of the individual
 * ADC_FORCE_SOCx values or any of their OR'd combination to trigger multiple
 * SOCs.
 *
 * \note To trigger SOC0, SOC1 and SOC2, value (ADC_FORCE_SOC0 |
 * ADC_FORCE_SOC1 | ADC_FORCE_SOC2) should be passed as socMask.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] socMask - SOCs to be forced through software
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_forceMultipleSOC(uint32 base, uint16 socMask)
{
    /*
     * Write to the register that will force a 1 to desired SOCs
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCSOCFRC1, socMask);
}

/** \brief Gets the current ADC interrupt status.
 *
 *
 * This function returns the interrupt status for the analog-to-digital
 * converter.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
 * \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express
 * which of the four interrupts of the ADC module should be cleared.
 * \return boolean
 * \retval  ADC_TRUE - if the interrupt flag for the specified interrupt number
 * is set
 * \retval  ADC_FALSE - if the interrupt flag for the specified interrupt number
 * is not set
 *
 *****************************************************************************/
static inline boolean ADC_getInterruptStatus(uint32 base, uint16 adcIntNum)
{
    /*
     * Get the specified ADC interrupt status.
     */
    return ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCINTFLG) & (1U << (uint16)adcIntNum)) != 0U);
}

/** \brief Clears ADC interrupt sources.
 *
 *
 * This function clears the specified ADC interrupt sources so that they no
 * longer assert. If not in continuous mode, this function must be called
 * before any further interrupt pulses may occur.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
 * \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express
 * which of the four interrupts of the ADC module should be cleared.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_clearInterruptStatus(uint32 base, uint16 adcIntNum)
{
    /*
     * Clear the specified interrupt.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCINTFLGCLR, ((uint16)((uint16)1U << (uint16)adcIntNum)));
}

/** \brief Gets the current ADC interrupt overflow status.
 *
 *
 * This function returns the interrupt overflow status for the
 * analog-to-digital converter. An overflow condition is generated
 * irrespective of the continuous mode.

 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
 * \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express
 * which of the four interrupts of the ADC module should be cleared.
 * \return boolean
 * \retval  ADC_TRUE - if the interrupt overflow flag for the specified interrupt
 * number is set
 * \retval  ADC_FALSE - if the interrupt overflow flag for the specified interrupt
 * number is not set
 *
 *****************************************************************************/
static inline boolean ADC_getInterruptOverflowStatus(uint32 base, uint16 adcIntNum)
{
    /*
     * Get the specified ADC interrupt status.
     */
    return ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCINTOVF) & (1U << (uint16)adcIntNum)) != 0U);
}

/** \brief Clears ADC interrupt overflow sources.
 *
 *
 * This function clears the specified ADC interrupt overflow sources so that
 * they no longer assert. If software tries to clear the overflow in the same
 * cycle that hardware tries to set the overflow, then hardware has priority.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
 * \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express
 * which of the four interrupts of the ADC module should be cleared.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_clearInterruptOverflowStatus(uint32 base, uint16 adcIntNum)
{
    /*
     * Clear the specified interrupt overflow bit.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCINTOVFCLR, ((uint16)((uint16)1U << (uint16)adcIntNum)));
}

/** \brief Reads the conversion result.
 *
 *
 * This function returns the conversion result that corresponds to the base
 * address passed into \e resultBase and the SOC passed into \e socNumber.
 *
 * \note Take care that you are using a base address for the result registers
 * (ADCxRESULT_BASE) and not a base address for the control registers.
 *
 * \param[in] resultBase - base address of the ADC results.
 * \param[in] socNumber - number of the start-of-conversion
 * The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
 * from 0 to 15 specifying which SOC's result is to be read.
 * \return uint16
 * \retval Returns the conversion result.
 *
 *****************************************************************************/
static inline FUNC(uint16, ADC_CODE) ADC_readResult(uint32 resultBase, uint32 socNumber)
{
    /*
     * Return the ADC result for the selected SOC.
     */
    return (HW_RD_REG16(resultBase + MCAL_CSL_ADC_RESULT_ADCRESULT0 +
                        ((uint32)socNumber * MCAL_ADC_RESULT_ADCRESULTx_STEP)));
}

/** \brief Reads the address of the conversion result register.
 *
 *
 * This function returns the conversion result that corresponds to the base
 * address passed into \e resultBase and the SOC passed into \e socNumber.
 *
 * \note Take care that you are using a base address for the result registers
 * (ADCxRESULT_BASE) and not a base address for the control registers.
 *
 * \param[in] resultBase - base address of the ADC results.
 * \param[in] socNumber - number of the start-of-conversion
 * The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
 * from 0 to 15 specifying which SOC's result is to be read.
 * \return uint32
 * \retval Returns the conversion result.
 *
 *****************************************************************************/
static inline FUNC(uint32, ADC_CODE) ADC_readResultbaseaddr(uint32 resultBase, uint16 socNumber)
{
    /*
     * Return the ADC result for the selected SOC.
     */
    return (resultBase + MCAL_CSL_ADC_RESULT_ADCRESULT0 + ((uint32)socNumber * MCAL_ADC_RESULT_ADCRESULTx_STEP));
}

/** \brief Determines whether the ADC is busy or not.
 *
 *
 * This function allows the caller to determine whether or not the ADC is
 * busy and can sample another channel.
 *
 * \param[in] base - base address of the ADC.
 * \return boolean
 * \retval ADC_TRUE - if the ADC is sampling
 * \retval ADC_FALSE - if all samples are complete
 *
 *****************************************************************************/
static inline boolean ADC_isBusy(uint32 base)
{
    /*
     * Determine if the ADC is busy.
     */
    return ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCCTL1) & MCAL_CSL_ADC_ADCCTL1_ADCBSY_MASK) != 0U);
}

/** \brief Set SOC burst mode.
 *
 *
 * This function configures the burst trigger and burstSize of an ADC module.
 * Burst mode allows a single trigger to walk through the round-robin SOCs one
 * or more at a time. When burst mode is enabled, the trigger selected by the
 * ADC_setupSOC() API will no longer have an effect on the SOCs in round-robin
 * mode. Instead, the source specified through the \e trigger parameter will
 * cause a burst of \e burstSize conversions to occur.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] trigger - the source that will cause the burst conversion sequence.
 * The \e trigger parameter takes the same values as the ADC_setupSOC() API
 * \param[in] burstSize - the number of SOCs converted during a burst sequence.
 * The \e burstSize parameter should be a value between 1 and 16 inclusive.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setBurstModeConfig(uint32 base, Adc_mcalTrigger_t trigger, uint16 burstSize)
{
    uint16 regValue;

    /*
     * Check the arguments.
     */

    /*
     * Write the burst mode configuration to the register.
     */
    regValue = (uint16)trigger | ((burstSize - 1U) << MCAL_CSL_ADC_ADCBURSTCTL_BURSTSIZE_SHIFT);

    HW_WR_REG16(base + MCAL_CSL_ADC_ADCBURSTCTL,
                ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCBURSTCTL) &
                  ~((uint16)MCAL_CSL_ADC_ADCBURSTCTL_BURSTTRIGSEL_MASK | MCAL_CSL_ADC_ADCBURSTCTL_BURSTSIZE_MASK)) |
                 regValue));
}

/** \brief Enables SOC burst mode.
 *
 *
 * This function enables SOC burst mode operation of the ADC. Burst mode
 * allows a single trigger to walk through the round-robin SOCs one or more at
 * a time. When burst mode is enabled, the trigger selected by the
 * ADC_setupSOC() API will no longer have an effect on the SOCs in round-robin
 * mode. Use ADC_setBurstMode() to configure the burst trigger and size.
 *
 * \param[in] base - base address of the ADC.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_enableBurstMode(uint32 base)
{
    /*
     * Enable burst mode.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCBURSTCTL,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCBURSTCTL) | MCAL_CSL_ADC_ADCBURSTCTL_BURSTEN_MASK));
}

/** \brief Disables SOC burst mode.
 *
 *
 * This function disables SOC burst mode operation of the ADC. SOCs in
 * round-robin mode will be triggered by the trigger configured using the
 * ADC_setupSOC() API.
 *
 * \param[in] base - base address of the ADC.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_disableBurstMode(uint32 base)
{
    /*
     * Disable burst mode.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCBURSTCTL,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCBURSTCTL) & ~MCAL_CSL_ADC_ADCBURSTCTL_BURSTEN_MASK));
}

/** \brief Sets the priority mode of the SOCs.
 *
 *
 * This function sets the priority mode of the SOCs. There are three main
 * modes that can be passed in the \e priMode parameter
 *
 * - All SOCs are in round-robin mode. This means no SOC has an inherent
 * higher priority over another. This is selected by passing in the value
 * \b ADC_PRI_ALL_ROUND_ROBIN.
 * - All priorities are in high priority mode. This means that the priority of
 * the SOC is determined by its SOC number. This option is selected by passing
 * in the value \b ADC_PRI_ALL_HIPRI.
 * - A range of SOCs are assigned high priority, with all others in round
 * robin mode. High priority mode means that an SOC with high priority will
 * interrupt the round robin wheel and insert itself as the next conversion.
 * Passing in the value \b ADC_PRI_SOC0_HIPRI will make SOC0 highest priority,
 * \b ADC_PRI_THRU_SOC1_HIPRI will put SOC0 and SOC 1 in high priority, and so
 * on up to \b ADC_PRI_THRU_SOC14_HIPRI where SOCs 0 through 14 are in high
 * priority.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] priMode - priority mode of the SOCs.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setSOCPriority(uint32 base, uint16 priMode)
{
    /*
     * Set SOC priority
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCSOCPRICTL,
                ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCSOCPRICTL) & ~MCAL_CSL_ADC_ADCSOCPRICTL_SOCPRIORITY_MASK) |
                 (uint16)priMode));
}

/** \brief Configures a post-processing block (PPB) in the ADC.
 *
 *
 * This function associates a post-processing block with a SOC.
 *
 * \note You can have more that one PPB associated with the same SOC, but a
 * PPB can only be configured to correspond to one SOC at a time. Also note
 * that when you have multiple PPBs for the same SOC, the calibration offset
 * that actually gets applied will be that of the PPB with the highest number.
 * Since SOC0 is the default for all PPBs, look out for unintentional
 * overwriting of a lower numbered PPB's offset.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] ppbNumber - number of the post-processing block.
 * The \e ppbNumber is a value \b ADC_PPB_NUMBERX where X is a value from 1 to
 * 4 inclusive that identifies a PPB to be configured.
 * \param[in] socNumber - number of the start-of-conversion.
 * The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
 * from 0 to 15 specifying which SOC is to be configured on the ADC module
 * specified by \e base.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setupPPB(uint32 base, Adc_mcalPPBNumber_t ppbNumber, uint16 socNumber)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate PPB configuration register.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1CONFIG;

    /*
     * Write the configuration to the register.
     */
    HW_WR_REG16(base + ppbOffset, ((HW_RD_REG16(base + ppbOffset) & ~MCAL_CSL_ADC_ADCPPB1CONFIG_CONFIG_MASK) |
                                   ((uint16)socNumber & MCAL_CSL_ADC_ADCPPB1CONFIG_CONFIG_MASK)));
}

/** \brief Enables individual ADC PPB event sources.
 *
 *
 * This function enables the indicated ADC PPB event sources.  This will allow
 * the specified events to propagate through the X-BAR to a pin or to an ePWM
 * module.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] ppbNumber - number of the post-processing block.
 * \param[in] evtFlags - bit mask of the event sources to be enabled.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_enablePPBEvent(uint32 base, Adc_mcalPPBNumber_t ppbNumber, uint16 evtFlags)
{
    /*
     * Check the arguments.
     */

    /*
     * Enable the specified event.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCEVTSEL,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCEVTSEL) | (evtFlags << ((uint16)ppbNumber * 4U))));
}

/** \brief Disables individual ADC PPB event sources.
 *
 *
 * This function disables the indicated ADC PPB event sources.  This will stop
 * the specified events from propagating through the X-BAR to other modules.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] ppbNumber - number of the post-processing block.
 * \param[in] evtFlags - bit mask of the event sources to be disabled.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_disablePPBEvent(uint32 base, Adc_mcalPPBNumber_t ppbNumber, uint16 evtFlags)
{
    /*
     * Check the arguments.
     */

    /*
     * Disable the specified event.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCEVTSEL,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCEVTSEL) & ~(evtFlags << ((uint16)ppbNumber * 4U))));
}

/** \brief Enables individual ADC PPB event interrupt sources.
 *
 *
 * This function enables the indicated ADC PPB interrupt sources.  Only the
 * sources that are enabled can be reflected to the processor interrupt.
 * Disabled sources have no effect on the processor.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] ppbNumber - number of the post-processing block.
 * \param[in] intFlags - bit mask of the interrupt sources to be enabled.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE)
    ADC_enablePPBEventInterrupt(uint32 base, Adc_mcalPPBNumber_t ppbNumber, uint16 intFlags)
{
    /*
     * Check the arguments.
     */

    /*
     * Enable the specified event interrupts.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCEVTINTSEL,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCEVTINTSEL) | (intFlags << ((uint16)ppbNumber * 4U))));
}

/** \brief Disables individual ADC PPB event interrupt sources.
 *
 *
 * This function disables the indicated ADC PPB interrupt sources.  Only the
 * sources that are enabled can be reflected to the processor interrupt.
 * Disabled sources have no effect on the processor.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] ppbNumber - number of the post-processing block.
 * \param[in] intFlags - bit mask of the interrupt sources to be disabled.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE)
    ADC_disablePPBEventInterrupt(uint32 base, Adc_mcalPPBNumber_t ppbNumber, uint16 intFlags)
{
    /*
     * Check the arguments.
     */

    /*
     * Disable the specified event interrupts.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCEVTINTSEL,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCEVTINTSEL) & ~(intFlags << ((uint16)ppbNumber * 4U))));
}

/** \brief Gets the current ADC event status.
 *
 *
 * This function returns the event status for the analog-to-digital converter.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] ppbNumber - number of the post-processing block.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(uint16, ADC_CODE) ADC_getPPBEventStatus(uint32 base, Adc_mcalPPBNumber_t ppbNumber)
{
    /*
     * Get the event status for the specified post-processing block.
     */
    return ((HW_RD_REG16(base + MCAL_CSL_ADC_ADCEVTSTAT) >> ((uint16)ppbNumber * 4U)) & 0x7U);
}

/** \brief Clears ADC event flags.
 *
 *
 * This function clears the indicated ADC PPB event flags. After an event
 * occurs this function must be called to allow additional events to be
 * produced.
 *
 * \param[in] base - base address of the ADC.
 * \param[in] ppbNumber - number of the post-processing block.
 * \param[in] evtFlags - bit mask of the event source to be cleared.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_clearPPBEventStatus(uint32 base, Adc_mcalPPBNumber_t ppbNumber, uint16 evtFlags)
{
    /*
     * Check the arguments.
     */

    /*
     * Clear the specified event interrupts.
     */
    HW_WR_REG16(base + MCAL_CSL_ADC_ADCEVTCLR,
                (HW_RD_REG16(base + MCAL_CSL_ADC_ADCEVTCLR) | (evtFlags << ((uint16)ppbNumber * 4U))));
}

/** \brief Reads the processed conversion result from the PPB.
 *
 *
 * This function returns the processed conversion result that corresponds to
 * the base address passed into \e resultBase and the PPB passed into
 * \e ppbNumber.
 *
 * \note Take care that you are using a base address for the result registers
 * (ADCxRESULT_BASE) and not a base address for the control registers.
 *
 * \param[in] resultBase - base address of the ADC results.
 * \param[in] ppbNumber - number of the post-processing block.
 * \return sint32
 * \retval Returns the signed 32-bit conversion result.
 *
 *****************************************************************************/
static inline FUNC(sint32, ADC_CODE) ADC_readPPBResult(uint32 resultBase, Adc_mcalPPBNumber_t ppbNumber)
{
    /*
     * Return the result of selected PPB.
     */
    return ((sint32)HW_RD_REG32(resultBase + MCAL_CSL_ADC_RESULT_ADCPPB1RESULT +
                                (((uint8)ppbNumber * MCAL_ADC_RESULT_ADCPPBxRESULT_STEP))));
}

/** \brief Reads sample delay time stamp from a PPB.
 *
 *
 * This function returns the sample delay time stamp. This delay is the number
 * of system clock cycles between the SOC being triggered and when it began
 * converting.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * \return uint16
 * \retval Returns the delay time stamp.
 *
 *****************************************************************************/
static inline FUNC(uint16, ADC_CODE) ADC_getPPBDelayTimeStamp(uint32 base, Adc_mcalPPBNumber_t ppbNumber)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate delay.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1STAMP;

    /*
     * Return the delay time stamp.
     */
    return (HW_RD_REG16(base + ppbOffset) & MCAL_CSL_ADC_ADCPPB1STAMP_DLYSTAMP_MASK);
}

/** \brief Sets the post processing block offset correction.
 *
 *
 * This function sets the PPB offset correction value.  This value can be used
 * to digitally remove any system-level offset inherent in the ADCIN circuit
 * before it is stored in the appropriate result register. The \e offset
 * parameter is \b subtracted from the ADC output and is a signed value from
 * -512 to 511 inclusive. For example, when \e offset = 1, ADCRESULT = ADC
 * output - 1. When \e offset = -512, ADCRESULT = ADC output - (-512) or ADC
 * output + 512.
 *
 * Passing a zero in to the \e offset parameter will effectively disable the
 * calculation, allowing the raw ADC result to be passed unchanged into the
 * result register.
 *
 * \note If multiple PPBs are applied to the same SOC, the offset that will be
 * applied will be that of the PPB with the highest number.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * \param[in] offset - 10-bit signed value subtracted from ADC the output.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE)
    ADC_setPPBCalibrationOffset(uint32 base, Adc_mcalPPBNumber_t ppbNumber, sint16 offset)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate offset register.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1OFFCAL;

    /*
     * Write the offset amount.
     */
    HW_WR_REG16(base + ppbOffset, ((HW_RD_REG16(base + ppbOffset) & ~MCAL_CSL_ADC_ADCPPB1OFFCAL_OFFCAL_MASK) |
                                   ((uint16)offset & MCAL_CSL_ADC_ADCPPB1OFFCAL_OFFCAL_MASK)));
}

/** \brief Sets the post processing block reference offset.
 *
 *
 * This function sets the PPB reference offset value. This can be used to
 * either calculate the feedback error or convert a unipolar signal to bipolar
 * by subtracting a reference value. The result will be stored in the
 * appropriate PPB result register which can be read using ADC_readPPBResult().
 *
 * Passing a zero in to the \e offset parameter will effectively disable the
 * calculation and will pass the ADC result to the PPB result register
 * unchanged.
 *
 * \note If in 12-bit mode, you may only pass a 12-bit value into the \e offset
 * parameter.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * \param[in] offset - 12-bit unsigned value subtracted from ADC the output.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setPPBReferenceOffset(uint32 base, Adc_mcalPPBNumber_t ppbNumber, uint16 offset)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate offset register.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1OFFREF;

    /*
     * Write the offset amount.
     */
    HW_WR_REG16(base + ppbOffset, offset);
}

/** \brief Enables two's complement capability in the PPB.
 *
 *
 * This function enables two's complement in the post-processing block
 * specified by the \e ppbNumber parameter. When enabled, a two's complement
 * will be performed on the output of the offset subtraction before it is
 * stored in the appropriate PPB result register. In other words, the PPB
 * result will be the reference offset value minus the the ADC result value
 * (ADCPPBxRESULT = ADCSOCxOFFREF - ADCRESULTx).
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_enablePPBTwosComplement(uint32 base, Adc_mcalPPBNumber_t ppbNumber)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate PPB configuration register.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1CONFIG;

    /*
     * Enable the twos complement
     */
    HW_WR_REG16(base + ppbOffset, (HW_RD_REG16(base + ppbOffset) | MCAL_CSL_ADC_ADCPPB1CONFIG_TWOSCOMPEN_MASK));
}

/** \brief Disables two's complement capability in the PPB.
 *
 *
 * This function disables two's complement in the post-processing block
 * specified by the \e ppbNumber parameter. When disabled, a two's complement
 * will \b NOT be performed on the output of the offset subtraction before it
 * is stored in the appropriate PPB result register. In other words, the PPB
 * result will be the ADC result value minus the reference offset value
 * (ADCPPBxRESULT = ADCRESULTx - ADCSOCxOFFREF).
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_disablePPBTwosComplement(uint32 base, Adc_mcalPPBNumber_t ppbNumber)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate PPB configuration register.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1CONFIG;

    /*
     * Disable the twos complement
     */
    HW_WR_REG16(base + ppbOffset, (HW_RD_REG16(base + ppbOffset) & ~MCAL_CSL_ADC_ADCPPB1CONFIG_TWOSCOMPEN_MASK));
}

/** \brief Enables cycle-by-cycle clear of ADC PPB event flags.
 *
 *
 * This function enables the automatic cycle-by-cycle clear of ADC PPB event
 * flags. When enabled, the desired PPB event flags are automatically cleared
 * on the next PPBxRESULT load, unless a set condition is also occurring at
 * the same time, in which case the set takes precedence.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_enablePPBEventCBCClear(uint32 base, uint32 ppbNumber)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate PPB configuration register.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1CONFIG;

    /*
     * Set automatic cycle-by-cycle flag clear bit
     */
    HW_WR_REG16(base + ppbOffset, (HW_RD_REG16(base + ppbOffset) | MCAL_CSL_ADC_ADCPPB1CONFIG_CBCEN_MASK));
}

/** \brief Disables cycle-by-cycle clear of ADC PPB event flags.
 *
 *
 * This function disables the cycle-by-cycle clear of ADC PPB event flags. When
 * disabled, the desired PPB event flags are to be cleared explicitly in
 * software inorder to generate next set of interrupts/events
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_disablePPBEventCBCClear(uint32 base, uint32 ppbNumber)
{
    uint32 ppbOffset;

    /*
     * Get the offset to the appropriate PPB configuration register.
     */
    ppbOffset = (MCAL_ADC_ADCPPBx_STEP * (uint32)ppbNumber) + MCAL_CSL_ADC_ADCPPB1CONFIG;

    /*
     * Clear automatic cycle-by-cycle flag clear bit
     */
    HW_WR_REG16(base + ppbOffset, (HW_RD_REG16(base + ppbOffset) & ~MCAL_CSL_ADC_ADCPPB1CONFIG_CBCEN_MASK));
}

/** \brief Enables an ADC interrupt source.
 *
 *
 * This function enables the indicated ADC interrupt source.  Only the
 * sources that are enabled can be reflected to the processor interrupt.
 * Disabled sources have no effect on the processor.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum can take the value \b ADC_INT_NUMBER1, \b ADC_INT_NUMBER2,
 * \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express which of the four
 * interrupts of the ADC module should be enabled.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_enableInterrupt(uint32 base, uint16 adcIntNum)
{
    uint32 intRegAddr;
    uint16 shiftVal;

    /*
     * Each INTSEL register manages two interrupts. If the interrupt number is
     * even, we'll be accessing the upper byte and will need to shift.
     */
    intRegAddr = base + MCAL_CSL_ADC_ADCINTSEL1N2 + (((uint32)adcIntNum >> 1) * MCAL_ADC_ADCINTSELxNy_STEP);
    shiftVal   = ((uint16)adcIntNum & 0x1U) << 3U;

    /*
     * Enable the specified ADC interrupt.
     */
    HW_WR_REG16(intRegAddr, HW_RD_REG16(intRegAddr) | (MCAL_CSL_ADC_ADCINTSEL1N2_INT1E_MASK << shiftVal));
}

/** \brief Disables an ADC interrupt source.
 *
 *
 * This function disables the indicated ADC interrupt source.
 * Only the sources that are enabled can be reflected to the processor
 * interrupt. Disabled sources have no effect on the processor.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum can take the value \b ADC_INT_NUMBER1, \b ADC_INT_NUMBER2,
 * \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express which of the four
 * interrupts of the ADC module should be disabled.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_disableInterrupt(uint32 base, uint16 adcIntNum)
{
    uint32 intRegAddr;
    uint16 shiftVal;

    /*
     * Each INTSEL register manages two interrupts. If the interrupt number is
     * even, we'll be accessing the upper byte and will need to shift.
     */
    intRegAddr = base + MCAL_CSL_ADC_ADCINTSEL1N2 + (((uint32)adcIntNum >> 1) * MCAL_ADC_ADCINTSELxNy_STEP);
    shiftVal   = ((uint16)adcIntNum & 0x1U) << 3U;

    /*
     * Disable the specified ADC interrupt.
     */
    HW_WR_REG16(intRegAddr, HW_RD_REG16(intRegAddr) & ~(MCAL_CSL_ADC_ADCINTSEL1N2_INT1E_MASK << shiftVal));
}

/** \brief Sets the source EOC for an analog-to-digital converter interrupt.
 *
 *
 * This function sets which conversion is the source of an ADC interrupt.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum can take the value \b ADC_INT_NUMBER1, \b ADC_INT_NUMBER2,
 * \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express which of the four
 * interrupts of the ADC module is being configured.
 * \param[in] socNumber - number of the start-of-conversion.
 * The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
 * from 0 to 15 specifying which EOC is to be configured on the ADC module
 * specified by \e base.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_setInterruptSource(uint32 base, uint16 adcIntNum, uint16 socNumber)
{
    uint32 intRegAddr;
    uint16 shiftVal;

    /*
     * Each INTSEL register manages two interrupts. If the interrupt number is
     * even, we'll be accessing the upper byte and will need to shift.
     */
    intRegAddr = base + MCAL_CSL_ADC_ADCINTSEL1N2 + (((uint32)adcIntNum >> 1) * MCAL_ADC_ADCINTSELxNy_STEP);
    shiftVal   = ((uint16)adcIntNum & 0x1U) << 3U;

    /*
     * Set the specified ADC interrupt source.
     */
    HW_WR_REG16(intRegAddr, ((HW_RD_REG16(intRegAddr) & ~(MCAL_CSL_ADC_ADCINTSEL1N2_INT1SEL_MASK << shiftVal)) |
                             ((uint16)socNumber << shiftVal)));
}

/** \brief Enables continuous mode for an ADC interrupt.
 *
 *
 * This function enables continuous mode for the ADC interrupt passed into
 * \e adcIntNum. This means that pulses will be generated for the specified
 * ADC interrupt whenever an EOC pulse is generated irrespective of whether or
 * not the flag bit is set.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum can take the value \b ADC_INT_NUMBER1, \b ADC_INT_NUMBER2,
 * \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express which of the four
 * interrupts of the ADC module is being configured.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_enableContinuousMode(uint32 base, uint16 adcIntNum)
{
    uint32 intRegAddr;
    uint16 shiftVal;

    /*
     * Each INTSEL register manages two interrupts. If the interrupt number is
     * even, we'll be accessing the upper byte and will need to shift.
     */
    intRegAddr = base + MCAL_CSL_ADC_ADCINTSEL1N2 + (((uint32)adcIntNum >> 1) * MCAL_ADC_ADCINTSELxNy_STEP);
    shiftVal   = ((uint16)adcIntNum & 0x1U) << 3U;

    /*
     * Enable continuous mode for the specified ADC interrupt.
     */
    HW_WR_REG16(intRegAddr, HW_RD_REG16(intRegAddr) | (MCAL_CSL_ADC_ADCINTSEL1N2_INT1CONT_MASK << shiftVal));
}

/** \brief Disables continuous mode for an ADC interrupt.
 *
 *
 * This function disables continuous mode for the ADC interrupt passed into
 * \e adcIntNum. This means that pulses will not be generated for the
 * specified ADC interrupt until the corresponding interrupt flag for the
 * previous interrupt occurrence has been cleared using
 * ADC_clearInterruptStatus().
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] adcIntNum - interrupt number within the ADC wrapper.
 * \e adcIntNum can take the value \b ADC_INT_NUMBER1, \b ADC_INT_NUMBER2,
 * \b ADC_INT_NUMBER3, or \b ADC_INT_NUMBER4 to express which of the four
 * interrupts of the ADC module is being configured.
 * \return None
 * \retval None
 *
 *****************************************************************************/
static inline FUNC(void, ADC_CODE) ADC_disableContinuousMode(uint32 base, uint32 adcIntNum)
{
    uint32 intRegAddr;
    uint16 shiftVal;

    /*
     * Each INTSEL register manages two interrupts. If the interrupt number is
     * even, we'll be accessing the upper byte and will need to shift.
     */
    intRegAddr = base + MCAL_CSL_ADC_ADCINTSEL1N2 + (((uint32)adcIntNum >> 1) * MCAL_ADC_ADCINTSELxNy_STEP);
    shiftVal   = ((uint16)adcIntNum & 0x1U) << 3U;

    /*
     * Disable continuous mode for the specified ADC interrupt.
     */
    HW_WR_REG16(intRegAddr, HW_RD_REG16(intRegAddr) & ~(MCAL_CSL_ADC_ADCINTSEL1N2_INT1CONT_MASK << shiftVal));
}

/** \brief Configures the analog-to-digital converter resolution and signal mode.
 *
 *
 * This function configures the ADC module's conversion resolution and input
 * signal mode and ensures that the corresponding trims are loaded.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] resolution - resolution of the converter (12 bits).
 * The \e resolution parameter specifies the resolution of the conversion.
 * It can be 12-bit specified by \b ADC_RESOLUTION_12BIT
 * \param[in] signalMode - input signal mode of the converter.
 * The \e signalMode parameter specifies the signal mode. In single-ended
 * mode, which is indicated by \b ADC_MODE_SINGLE_ENDED, the input voltage is
 * sampled on a single pin referenced to VREFLO. In differential mode, which
 * is indicated by \b ADC_MODE_DIFFERENTIAL, the input voltage to the
 * converter is sampled on a pair of input pins, a positive and a negative.
 * \return None
 * \retval None
 *
 *****************************************************************************/
extern void ADC_setMode(uint32 base, Adc_mcalResolution_t resolution, Adc_mcalSignalMode_t signalMode);

/** \brief Sets the windowed trip limits for a PPB.
 *
 *
 * This function sets the windowed trip limits for a PPB. These values set
 * the digital comparator so that when one of the values is exceeded, either a
 * high or low trip event will occur. In 12-bit mode, only bits 12:0 will be
 * compared against bits 12:0 of the PPB result.
 *
 * \param[in] base - base address of the ADC module.
 * \param[in] ppbNumber - number of the post-processing block.
 * The \e ppbNumber is a value \b ADC_PPB_NUMBERX where X is a value from 1 to
 * 4 inclusive that identifies a PPB to be configured.
 * \param[in] tripHiLimit - value is the digital comparator trip high limit.
 * \param[in] tripLoLimit - value is the digital comparator trip low limit.
 * \return None
 * \retval None
 *
 *****************************************************************************/
extern void ADC_setPPBTripLimits(uint32 base, Adc_mcalPPBNumber_t ppbNumber, sint32 tripHiLimit, sint32 tripLoLimit);

/*****************************************************************************
 *
 * Mark the end of the C bindings section for C++ compilers.
 *
 *****************************************************************************/
/** \brief End Memory section tag */
#define ADC_STOP_SEC_CODE
#include "Adc_MemMap.h"

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ADC_V1_H_*/
