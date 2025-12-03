/*
 *  Copyright (C) 2023 Texas Instruments Incorporated
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
 */

#include "stdbool.h"
#include "stdint.h"
#include "Pwm_Sfo.h"
#define PWM_START_SEC_CODE
#include "Pwm_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define PWM_STOP_SEC_CODE
#include "Pwm_MemMap.h"

#define PWM_EPWM_O_HRCNFG   0x40
#define PWM_EPWM_O_HRCNFG2  0x4E
#define PWM_EPWM_O_HRPCTL   0x5A
#define PWM_EPWM_O_HRPWMREV 0x7E
#define PWM_EPWM_O_DBREDHR  0xA0
#define PWM_EPWM_O_DBRED    0xA2
#define PWM_EPWM_O_DBFEDHR  0xA4
#define PWM_EPWM_O_DBFED    0xA6
#define PWM_EPWM_O_TBPRDHR  0xC4
#define PWM_EPWM_O_TBPRD    0xC6
#define PWM_EPWM_O_CMPA     0xD4
#define PWM_EPWM_O_CMPB     0xD8

#define PWM_CSL_OTTOCAL_HRPWR   (0x00000042U)
#define PWM_CSL_OTTOCAL_HRCAL   (0x00000044U)
#define PWM_CSL_OTTOCAL_HRPRD   (0x00000046U)
#define PWM_CSL_OTTOCAL_HRCNT0  (0x00000048U)
#define PWM_CSL_OTTOCAL_HRCNT1  (0x0000004AU)
#define PWM_CSL_OTTOCAL_HRMSTEP (0x0000004CU)

/* The following are defines for the bit fields in the HRCNFG register */

#define PWM_EPWM_HRCNFG_EDGMODE_S 0U
#define PWM_EPWM_HRCNFG_EDGMODE_M 0x3U /* ePWMxA Edge Mode Select Bits*/
#define PWM_EPWM_HRCNFG_CTLMODE   0x4U /* ePWMxA Control Mode Select*/
                                       // Bits
#define PWM_EPWM_HRCNFG_HRLOAD_S 3U
#define PWM_EPWM_HRCNFG_HRLOAD_M 0x18U /* ePWMxA Shadow Mode Select */
                                       /* Bits*/
#define PWM_EPWM_HRCNFG_SELOUTB  0x20U /* EPWMB Output Selection Bit*/
#define PWM_EPWM_HRCNFG_AUTOCONV 0x40U /* Autoconversion Bit*/
#define PWM_EPWM_HRCNFG_SWAPAB   0x80U /* Swap EPWMA and EPWMB Outputs*/
                                       /* Bit*/
#define PWM_EPWM_HRCNFG_EDGMODEB_S 8U
#define PWM_EPWM_HRCNFG_EDGMODEB_M 0x300U /* ePWMxB Edge Mode Select Bits*/
#define PWM_EPWM_HRCNFG_CTLMODEB   0x400U /* ePWMxB Control Mode Select*/
                                          /* Bits*/
#define PWM_EPWM_HRCNFG_HRLOADB_S 11U
#define PWM_EPWM_HRCNFG_HRLOADB_M 0x1800U /* ePWMxB Shadow Mode Select */
                                          /* Bits */
#define PWM_EPWM_HRCNFG_LINESEL_S 14U
#define PWM_EPWM_HRCNFG_LINESEL_M 0xC000U /* Delay Line Selection bits */

/* The following are defines for the bit fields in the HRPWR register */

#define PWM_EPWM_HRPWR_CALSTART 0x4U  /* Calibration Start/Stop */
#define PWM_EPWM_HRPWR_CNTSEL   0x8U  /* Counter Select Bit */
#define PWM_EPWM_HRPWR_CALSTS   0x10U /* Calibration Status Bit */
#define PWM_EPWM_HRPWR_TESTSEL  0x20U /* Test Mode (Lump Delay) Select */
                                      /* Bit */
#define PWM_EPWM_HRPWR_CALSEL_S 6U
#define PWM_EPWM_HRPWR_CALSEL_M 0x3C0U  /* ePWM Delay Line Selection for */
                                        /* Calibration */
#define PWM_EPWM_HRPWR_CALPWRON 0x8000U /* Calibration Power On */

/* The following are defines for the bit fields in the HRCAL register */

#define PWM_EPWM_HRCAL_HRCAL_S 0U
#define PWM_EPWM_HRCAL_HRCAL_M 0xFFU /* Delay Line Calibration Value */
                                     /* Register.*/

/* The following are defines for the bit fields in the HRMSTEP register*/

#define PWM_EPWM_HRMSTEP_HRMSTEP_S 0U
#define PWM_EPWM_HRMSTEP_HRMSTEP_M 0xFFU /* High Resolution Micro Step */
                                         /* Value */

#define HWREG(x)  (*((volatile uint32 *)(x)))
#define HWREGB(x) __byte((sint32 *)(x), 0)

#define MEP1          80
#define MEP2          200
#define COUNT         50
#define PRDVAL        65535 /* for all elements in testmode */
#define STOPCAL       0x0
#define STARTCAL      0x1
#define SELECT_HRCNT0 0x0
#define SELECT_HRCNT1 0x1

/* Globals */
#define PWM_START_SEC_VAR_NO_INIT_32
#include "Pwm_MemMap.h"
VAR(uint32, PWM_VAR_NO_INIT) Pwm_MEP_SF[(PWM_CH_MAX + 1)];
/* channel to calibrate to use, declare "extern sint SFO_CAL;" in source file
and call SFO() once before changing to select a channel.*/
VAR(uint32, PWM_VAR_NO_INIT) Pwm_SFO_Cal;
extern VAR(uint32, PWM_VAR_NO_INIT) Pwm_gOttoCal_base;
extern VAR(sint32, PWM_VAR_NO_INIT) Pwm_MEP_ScaleFactor;
#define PWM_STOP_SEC_VAR_NO_INIT_32
#include "Pwm_MemMap.h"

/******************************************************************************

 FUNCTION:    Pwm_SFO(void)
 DESCRIPTION: MEP calibration module (DCAL) result + channel calibration
              result(channel delay lines) -
              Updates MEP_ScaleFactor value
              for selected ePWM channel calibration if user wants to compare
              with "MEP calibration module" (DCAL) result for proper
              operation.  Only DCAL (n=0) can be run while HRPWM is enabled
              Individual channel calibration can only be run on a
              channel with HRPWM capabilities disabled-one channel at a time.

 PARAMETERS:  Pwm_SFO_Cal - ePWM channel # on which MEP_ScaleFactor will
                        be calculated (0 = DCAL channel)

             Pwm_gOttoCal_base - OTTOCAL calibration module instance

 RETURN:      1 - SFO calibration complete on selected channel.
              0 - SFO calibration incomplete on selected channel.

******************************************************************************/
#define PWM_START_SEC_CODE
#include "Pwm_MemMap.h"

FUNC(sint32, PWM_CODE) Pwm_SFO(void)
{
    static uint16 hrc1, hrc2; /* holds HRCNT0 count in 65535 HRCNT1 counts */
    static uint16 TaskPtr = 0U;

    sint16  status;
    float32 Denom;
    uint16  Numer;
    uint32  scale_factor;

    status = PWM_SFO_INCOMPLETE; /* status remains 0 until SFO completes */

    /* SFO MEP Calibration State Machine */

    switch (TaskPtr)
    {
        case 0: /* General Initialization */

            /*Clear all bits */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR, 0x0U);

            /* Set the counter period */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPRD, PRDVAL);

            /* Eliminate delay in counter start(CNTSEL = 1), enable lump delay
            (TESTSEL = 1) & turn on the calibration logic(CALPWRON = 1) */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) |
                         (PWM_EPWM_HRPWR_CNTSEL | PWM_EPWM_HRPWR_TESTSEL)));

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) | PWM_EPWM_HRPWR_CALPWRON));
            /*Initialize variables */

            /*Pwm_SFO_Cal = 0;*/
            hrc1    = 0;
            hrc2    = 0;
            TaskPtr = 1;
            break;

        case 1: /* Initialization for 1st run*/

            /* The logic should be reinitialized before every calibration run. */
            /* Clear all bits in HRPWR */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR, ((uint16)0X0));
            /*AM263x: Fix for missing initialization (other than in task 0) of HRPRD for other
             * OTTOCALs*/

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPRD, PRDVAL);

            /*Configure # MEP steps A (1st point) in DCAL mode. This should be
              done before powering the CAL logic on */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCAL, MEP1);

            /* Eliminate delay in counter start(CNTSEL = 1), enable lump delay
            (TESTSEL = 1) & turn on the calibration logic(CALPWRON = 1)*/

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) |
                         (PWM_EPWM_HRPWR_CNTSEL | PWM_EPWM_HRPWR_TESTSEL)));

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) | PWM_EPWM_HRPWR_CALPWRON));
            /* Add some delay(23 cycles) after power off. Unrolled the loop
            to make it interruptable. Use asm(" RPT #20 || NOP");
             to make it uninterruptable */

            /* Manually clear HRCNT0 & HRCNT1 to be safe */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCNT0, 0x0U);
            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCNT1, 0x0U);

            /* Start calibration*/

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) | PWM_EPWM_HRPWR_CALSTART));
            /* Update task pointer to next case for next SFO call.*/

            TaskPtr = 2;

            break;

        case 2: /* Wait for 1st run to complete */

            /* If calibration is not complete, exit SFO() and check again
            in next function call. CALSTS becomes zero when HRCNT1 value
             equals HRPRD value or 0xFFFFU.*/

            if (((HW_RD_REG16((Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) & PWM_EPWM_HRPWR_CALSTS)) == 0x0U)
            {
                /* Stop calibration. This bit is NOT automatically cleared.*/

                HW_WR_REG16((Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR),
                            ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) & ~PWM_EPWM_HRPWR_CALSTART));

                /* Get 1st count in HRCNT0 (# of ring osc oscillations) */

                hrc1 = HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCNT0);

                /*Update task pointer to next case for next SFO call.*/
                TaskPtr = 3;

                /* Power down the calibration logic*/

                HW_WR_REG16((Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR),
                            ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) & ~PWM_EPWM_HRPWR_CALPWRON));

                /* Add some delay(23 cycles) after power off. Unrolled the loop
                 to make it interruptable. Use asm(" RPT #20 || NOP");
                 to make it uninterruptable.*/
            }

            break;

        case 3: /* Initialization for 2nd run */

            /* Clear all bits in HRPWR */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR, 0x0U);

            /* Configure # MEP steps B (2nd point) in DCAL mode. This
             should be done before powering the CAL logic on */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCAL, MEP2);

            /* Eliminate delay in counter start(CNTSEL = 1), enable lump delay
             (TESTSEL = 1) & turn on the calibration logic(CALPWRON = 1) */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) |
                         (PWM_EPWM_HRPWR_CNTSEL | PWM_EPWM_HRPWR_TESTSEL)));

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) | PWM_EPWM_HRPWR_CALPWRON));
            /* Add some delay(23 cycles) after power off. Unrolled the loop
             to make it interruptable. Use asm(" RPT #20 || NOP");
             to make it uninterruptable.
            */

            /* Manually clear HRCNT0 & HRCNT1 to be safe  */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCNT0, 0x0U);
            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCNT1, 0x0U);

            /* Start calibration */

            HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR,
                        ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) | PWM_EPWM_HRPWR_CALSTART));
            /* Move to next case when SFO() is called the next time */
            TaskPtr = 4;
            break;

        case 4: /* Wait for 2nd run to complete*/

            /* If calibration is not complete, exit SFO() and check again next
               function call*/

            if ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR) & PWM_EPWM_HRPWR_CALSTS) == 0x0U)

            {
                /*Stop calibration. This bit is NOT automatically cleared*/

                HW_WR_REG16((Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR),
                            ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) & ~PWM_EPWM_HRPWR_CALSTART));

                /* Get the count from HRCNT0 (# of ring osc oscillations)*/

                hrc2 = HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRCNT0);

                /*  Move to next case when SFO() is called the next time*/

                TaskPtr = 5;

                /*Power down the calibration logic*/

                HW_WR_REG16((Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR),
                            ((HW_RD_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRPWR)) & ~PWM_EPWM_HRPWR_CALPWRON));

                /* Add some delay(23 cycles) after power-off. Unrolled the loop
                 to make it interruptable. Use asm(" RPT #20 || NOP");
                to make it uninterruptable.*/
            }

            break;

        case 5: /* Process diagnostics data*/

            /* Calculate MEP delay time in 1 SYSCLK cycles*/
            Denom = (((((float32)1) / (float32)hrc2) - (((float32)1) / (float32)hrc1)) * ((float32)0xFFFF));

            /* Calculate # of MEP steps*/

            Numer = (MEP2 - MEP1) * 2;

            /* Calculate MEP scale factor */
            scale_factor            = ((((float32)Numer) / Denom) + ((float32)0.5));
            Pwm_MEP_SF[Pwm_SFO_Cal] = scale_factor;
            Pwm_MEP_ScaleFactor     = Pwm_MEP_SF[0];

            /* Update the task pointer to MEP1 calibration initialization task
             for next call.*/
            TaskPtr = 1;

            /* Update status & assign scale factor value to HRMSTEP register */
            if (Pwm_MEP_ScaleFactor > ((sint32)255U))
            {
                status = PWM_SFO_ERROR;
            }
            else
            {
                /* Update HRMSTEP register only with DCAL result*/

                HW_WR_REG16(Pwm_gOttoCal_base + PWM_CSL_OTTOCAL_HRMSTEP, Pwm_MEP_SF[0]);
                status = PWM_SFO_COMPLETE;
            }

            break;
        default:
            break;
    }
    return status;
}
#define PWM_STOP_SEC_CODE
#include "Pwm_MemMap.h"
