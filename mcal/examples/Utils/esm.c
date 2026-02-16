/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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

/* Include Files */
#include "esm.h"
#include "sys_vim.h"
#include "sys_common.h"
#include "Compiler.h"
#include "hw_ctrl_core.h"

#define M_ZERO         (0U)
#define M_FIVE         (5U)
#define M_SIX          (6U)
#define M_SEVEN        (7U)
#define M_EIGHT        (8U)
#define M_NINE         (9U)
#define M_TEN          (10U)
#define M_SIXTEEN      (16U)
#define M_SEVENTEEN    (17U)
#define M_EIGHTEEN     (18U)
#define M_NINETEEN     (19U)
#define M_TWENTY       (20U)
#define M_TWENTY_THREE (23U)
#define M_THIRTY       (30U)
#define M_THIRTY_ONE   (31U)

/** @typedef t_esmGroup1funptr
 *   @brief FIQ Helper Function Pointer Type Definition
 *
 *   This type is used from the ESM high-priority interrupt handler.
 */
t_esmGroup1FuncPTR syst_esmGroup1funptr = 0;

/** @typedef t_esmGroup2funptr
 *   @brief FIQ Helper Function Pointer Type Definition
 *
 *   This type is used from the ESM high-priority interrupt handler.
 */
t_esmGroup2FuncPTR syst_esmGroup2funptr = 0;

/** @fn void esmInit(void)
 *   @brief Initializes Esm Driver
 *
 *   This function initializes the Esm driver.
 *
 */

/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmInit(void)
{
    uint32 regWrFailStatus, regVal;
    uint32 esmepsr = esmREG->EPSR;

    /** - Disable error pin channels */
    esmREG->DEPAPR1 = 0xFFFFFFFFU;
    esmREG->IEPCR4  = 0xFFFFFFFFU;

    /** - Disable interrupts */
    esmREG->IECR1 = 0xFFFFFFFFU;
    esmREG->IECR4 = 0xFFFFFFFFU;

    /** - Clear error status flags */
    esmREG->DEPAPR1     = 0xFFFFFFFFU;
    esmREG->IEPCR4      = 0xFFFFFFFFU;
    esmREG->SSR2        = 0xFFFFFFFFU;
    esmREG->SR1[2U]     = 0xFFFFFFFFU;
    esmREG->SR4[0U]     = 0xFFFFFFFFU;
    esmREG->SR4[1U]     = 0xFFFFFFFFU;
    esmREG->ESTATUS5EMU = 0xFFFFFFFFU;
    esmREG->SR4[2U]     = 0xFFFFFFFFU;

    /** - Setup LPC preload */
    regWrFailStatus = regWriteReadback(&esmREG->LTCPR, M_THIRTY_ONE, M_ZERO, (uint32)(16384U - 1U));

    /** - Reset error pin */
    if ((esmepsr & 0xFFFFFFFFU) != 0x0U)
    {
        esmREG->EKR = 0x0U;
    }
    else
    {
        esmREG->EKR = 0x5U;
    }

    /** - Clear interrupt level */
    esmREG->ILCR1 = 0xFFFFFFFFU;
    esmREG->ILCR4 = 0xFFFFFFFFU;

    /** - Set interrupt level */
    regVal = (uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) |
             (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) |
             (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) |
             (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) |
             (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) |
             (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) |
             (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) |
             (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |
             (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |
             (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |
             (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U);
    regWrFailStatus |= regWriteReadback(&esmREG->ILSR1, M_THIRTY_ONE, M_ZERO, regVal);

    regVal = (uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) |
             (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) |
             (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) |
             (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) |
             (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) |
             (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) |
             (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) |
             (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |
             (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |
             (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |
             (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U);
    regWrFailStatus |= regWriteReadback(&esmREG->ILSR4, M_THIRTY_ONE, M_ZERO, regVal);

    /** - Enable error pin channels */
    regVal = (uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) |
             (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) |
             (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) |
             (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) |
             (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) |
             (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) |
             (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) |
             (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |
             (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |
             (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |
             (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U);
    regWrFailStatus |= regWriteReadback(&esmREG->EEPAPR1, M_THIRTY_ONE, M_ZERO, regVal);

    regVal = (uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) |
             (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) |
             (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) |
             (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) |
             (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) |
             (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) |
             (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) |
             (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |
             (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |
             (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |
             (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U);
    regWrFailStatus |= regWriteReadback(&esmREG->IEPSR4, M_THIRTY_ONE, M_ZERO, regVal);

    /** - Enable interrupts */
    regVal = (uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) |
             (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) |
             (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) |
             (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) |
             (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) |
             (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) |
             (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) |
             (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |
             (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |
             (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |
             (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U);
    regWrFailStatus |= regWriteReadback(&esmREG->IESR1, M_THIRTY_ONE, M_ZERO, regVal);

    regVal = (uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) |
             (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) |
             (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) |
             (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) |
             (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) |
             (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) |
             (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) |
             (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |
             (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |
             (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |
             (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U);
    regWrFailStatus |= regWriteReadback(&esmREG->IESR4, M_THIRTY_ONE, M_ZERO, regVal);

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn uint32 esmError(esmBASE_t *esmBaseREG)
 *   @brief Return Error status
 *
 *   @return The error status
 *
 *   Returns the error status.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 esmError(esmBASE_t *esmBaseREG)
{
    uint32 status = esmBaseREG->EPSR;

    return status;
}

/** @fn void esmEnableError(esmBASE_t *esmBaseREG, uint64 channels)
 *   @brief Enable Group 1 Channels Error Signals propagation
 *
 *   @param[in] channels - Channel mask
 *
 *   Enable Group 1 Channels Error Signals propagation to the error pin.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmEnableError(esmBASE_t *esmBaseREG, uint64 channels)
{
    uint32 regWrFailStatus;

    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    regWrFailStatus =
        regWriteReadback(&esmBaseREG->IEPSR4, M_THIRTY_ONE, M_ZERO, (uint32)((channels >> 32U) & 0xFFFFFFFFU));
    regWrFailStatus |= regWriteReadback(&esmBaseREG->EEPAPR1, M_THIRTY_ONE, M_ZERO, (uint32)0xFFFFFFFFU);

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void esmDisableError(uint64 channels)
 *   @brief Disable Group 1 Channels Error Signals propagation
 *
 *   @param[in] channels - Channel mask
 *
 *   Disable Group 1 Channels Error Signals propagation to the error pin.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmDisableError(esmBASE_t *esmBaseREG, uint64 channels)
{
    uint32 regWrFailStatus;

    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    regWrFailStatus =
        regWriteReadback(&esmBaseREG->IEPCR4, M_THIRTY_ONE, M_ZERO, (uint32)((channels >> 32U) & 0xFFFFFFFFU));
    regWrFailStatus |= regWriteReadback(&esmBaseREG->DEPAPR1, M_THIRTY_ONE, M_ZERO, (uint32)0xFFFFFFFFU);

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void esmTriggerErrorPinReset(void)
 *   @brief Trigger error pin reset and switch back to normal operation
 *
 *   Trigger error pin reset and switch back to normal operation.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmTriggerErrorPinReset(esmBASE_t *esmBaseREG)
{
    esmBaseREG->EKR = 0x5U;
}

/** @fn void esmActivateNormalOperation(void)
 *   @brief Activate normal operation
 *
 *   Activates normal operation mode.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmActivateNormalOperation(esmBASE_t *esmBaseREG)
{
    uint32 regWrFailStatus;

    regWrFailStatus = regWriteReadback(&esmBaseREG->EKR, M_THIRTY_ONE, M_ZERO, (uint32)0x0U);

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void esmEnableInterrupt(uint64 channels)
 *   @brief Enable Group 1 Channels Interrupts
 *
 *   @param[in] channels - Channel mask
 *
 *   Enable Group 1 Channels Interrupts.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmEnableInterrupt(esmBASE_t *esmBaseREG, uint64 channels)
{
    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    esmBaseREG->IESR4 = (uint32)((uint32)(channels >> 32U) & 0xFFFFFFFFU);
    esmBaseREG->IESR1 = (uint32)((uint32)channels & 0xFFFFFFFFU);
}

/** @fn void esmDisableInterrupt(uint64 channels)
 *   @brief Disable Group 1 Channels Interrupts
 *
 *   @param[in] channels - Channel mask
 *
 *   Disable Group 1 Channels Interrupts.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmDisableInterrupt(esmBASE_t *esmBaseREG, uint64 channels)
{
    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    esmBaseREG->IECR4 = (uint32)((uint32)(channels >> 32U) & 0xFFFFFFFFU);
    esmBaseREG->IECR1 = (uint32)((uint32)channels & 0xFFFFFFFFU);
}

/** @fn void esmSetInterruptLevel(uint64 channels, uint64 flags)
 *   @brief Set Group 1 Channels Interrupt Levels
 *
 *   @param[in] channels - Channel mask
 *   @param[in] flags - Level mask: - 0: Low priority interrupt
 *                                  - 1: High priority interrupt
 *
 *   Set Group 1 Channels Interrupts levels.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmSetInterruptLevel(esmBASE_t *esmBaseREG, uint64 channels, uint64 flags)
{
    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    esmBaseREG->ILCR4 = (uint32)((uint32)((channels & (~flags)) >> 32U) & 0xFFFFFFFFU);
    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    esmBaseREG->ILSR4 = (uint32)((uint32)((channels & flags) >> 32U) & 0xFFFFFFFFU);
    esmBaseREG->ILCR1 = (uint32)((uint32)((channels & (~flags)) & 0xFFFFFFFFU));
    esmBaseREG->ILSR1 = (uint32)((uint32)((channels & flags) & 0xFFFFFFFFU));
}

/** @fn void esmClearStatus(uint32 group, uint64 channels)
 *   @brief Clear Group error status
 *
 *   @param[in] group    - Error group
 *   @param[in] channels - Channel mask
 *
 *   Clear Group error status.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmClearStatus(esmBASE_t *esmBaseREG, uint32 group, uint64 channels)
{
    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    esmREG->SR4[0U] = (uint32)((channels >> 32U) & 0xFFFFFFFFU);
    esmREG->SR1[0U] = (uint32)(channels & 0xFFFFFFFFU);
}

/** @fn void esmClearStatusBuffer(uint64 channels)
 *   @brief Clear Group 2 error status buffer
 *
 *   @param[in] channels - Channel mask
 *
 *   Clear Group 2 error status buffer.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmClearStatusBuffer(esmBASE_t *esmBaseREG, uint64 channels)
{
    uint32 regWrFailStatus;

    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to get 32-bit from 64-bit parameter" */
    /*LDRA_INSPECTED 51 S */
    regWrFailStatus =
        regWriteReadback(&esmBaseREG->ESTATUS5EMU, M_THIRTY_ONE, M_ZERO, (uint32)((channels >> 32U) & 0xFFFFFFFFU));
    regWrFailStatus |= regWriteReadback(&esmBaseREG->SSR2, M_THIRTY_ONE, M_ZERO, (uint32)0xFFFFFFFFU);

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn void esmSetCounterPreloadValue(uint32 value)
 *   @brief Set counter preload value
 *
 *   @param[in] value - Counter preload value
 *
 *   Set counter preload value.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmSetCounterPreloadValue(esmBASE_t *esmBaseREG, uint32 value)
{
    uint32 regWrFailStatus;

    regWrFailStatus = regWriteReadback(&esmBaseREG->LTCPR, M_THIRTY_ONE, M_ZERO, (uint32)(value & 0xC000U));

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}

/** @fn uint64 esmGetStatus(uint32 group, uint64 channels)
 *   @brief Return Error status
 *
 *   @param[in] group   - Error group
 *   @param[in] channels - Error Channels
 *
 *   @return The channels status of selected group
 *
 *   Returns the channels status of selected group.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint64 esmGetStatus(esmBASE_t *esmBaseREG, uint32 group, uint64 channels)
{
    uint64 status;

    uint32 ESM_ESTATUS4 = esmBaseREG->SR4[group];
    uint32 ESM_ESTATUS1 = esmBaseREG->SR1[group];

    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to change 32-bit to 64-bit parameter"
     */
    /*LDRA_INSPECTED 51 S */
    status = (((uint64)(ESM_ESTATUS4) << 32U) | (uint64)ESM_ESTATUS1) & channels;

    return status;
}

/** @fn uint64 esmGetStatusBuffer(uint64 channels)
 *   @brief Return Group 2 channel x Error status buffer
 *
 *   @param[in] channels - Error Channels
 *
 *   @return The channels status
 *
 *   Returns the group 2 buffered status of selected channels.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint64 esmGetStatusBuffer(esmBASE_t *esmBaseREG, uint64 channels)
{
    uint64 status;
    uint32 esmestatusemu = esmBaseREG->ESTATUS5EMU;
    uint32 esmssr2       = esmBaseREG->SSR2;

    /*AR_CODE_REVIEW MR:R.12.8 <REVIEWED> "Shifting required to change 32-bit to 64-bit parameter"
     */
    /*LDRA_INSPECTED 51 S */
    status = (((uint64)(esmestatusemu) << 32U) | (uint64)esmssr2) & channels;

    return status;
}

/** @fn esmSelfTestFlag_t esmEnterSelfTest(void)
 *   @brief Return ESM Self test status
 *
 *   @return ESM Self test status
 *
 *   Returns the ESM Self test status.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
esmSelfTestFlag_t esmEnterSelfTest(esmBASE_t *esmBaseREG)
{
    esmSelfTestFlag_t status;
    uint32            esmepsr    = esmBaseREG->EPSR;
    uint32            errPinStat = esmepsr & 0x1U;
    uint32            esmKeyReg  = esmBaseREG->EKR;
    if ((errPinStat == 0x0U) && (esmKeyReg == 0x0U))
    {
        status = esmSelfTest_NotStarted;
    }
    else
    {
        esmBaseREG->EKR = 0xAU;
        if ((esmepsr & 0x1U) != 0x0U)
        {
            status = esmSelfTest_Failed;
        }
        else
        {
            status = esmSelfTest_Active;
        }
        esmBaseREG->EKR = 0x5U;
    }

    return status;
}

/** @fn esmSelfTestFlag_t esmSelfTestStatus(void)
 *   @brief Return ESM Self test status
 *
 *   Returns the ESM Self test status.
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
esmSelfTestFlag_t esmSelfTestStatus(esmBASE_t *esmBaseREG)
{
    esmSelfTestFlag_t status;
    uint32            esmepsr = esmBaseREG->EPSR;
    uint32            esmekr  = esmBaseREG->EKR;

    if ((esmepsr & 0x1U) == 0x0U)
    {
        if (esmekr == 0x5U)
        {
            status = esmSelfTest_Active;
        }
        else
        {
            status = esmSelfTest_Failed;
        }
    }
    else
    {
        status = esmSelfTest_Passed;
    }

    return status;
}

/** @fn void esmGetConfigValue(esm_config_reg_t *config_reg, config_value_type_t type)
 *   @brief Get the initial or current values of the configuration registers
 *   @param[in] *config_reg: pointer to the struct to which the initial or current
 *   value of the configuration registers need to be stored
 *   @param[in] type: whether initial or current value of the configuration registers need to be
 * stored
 *        - InitialValue: initial value of the configuration registers will be stored
 *        in the struct pointed by config_reg
 *        - CurrentValue: initial value of the configuration registers will be stored
 *        in the struct pointed by config_reg
 *
 *        This function will copy the initial or current value (depending on the parameter 'type')
 *   of the configuration registers to the struct pointed by config_reg
 *
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmGetConfigValue(esm_config_reg_t *config_reg, config_value_type_t type)
{
    uint32 esmeepapr1 = esmREG->EEPAPR1;
    uint32 esmiesr1   = esmREG->IESR1;
    uint32 esmilsr1   = esmREG->ILSR1;
    uint32 esmltcpr   = esmREG->LTCPR;
    uint32 esmekr     = esmREG->EKR;
    uint32 esmiepsr4  = esmREG->IEPSR4;
    uint32 esmiesr4   = esmREG->IESR4;
    uint32 esmilsr4   = esmREG->ILSR4;
    if (type == InitialValue)
    {
        config_reg->CONFIG_EEPAPR1 = ESM_EEPAPR1_CONFIGVALUE;
        config_reg->CONFIG_IESR1   = ESM_IESR1_CONFIGVALUE;
        config_reg->CONFIG_ILSR1   = ESM_ILSR1_CONFIGVALUE;
        config_reg->CONFIG_LTCPR   = ESM_LTCPR_CONFIGVALUE;
        config_reg->CONFIG_EKR     = ESM_EKR_CONFIGVALUE;
        config_reg->CONFIG_IEPSR4  = ESM_IEPSR4_CONFIGVALUE;
        config_reg->CONFIG_IESR4   = ESM_IESR4_CONFIGVALUE;
        config_reg->CONFIG_ILSR4   = ESM_ILSR4_CONFIGVALUE;
    }
    else
    {
        /*AR_CODE_REVIEW MR:R.12.2 Reason : "LDRA Tool issue" */
        /*LDRA_INSPECTED 134 S */
        config_reg->CONFIG_EEPAPR1 = esmeepapr1;
        config_reg->CONFIG_IESR1   = esmiesr1;
        config_reg->CONFIG_ILSR1   = esmilsr1;
        config_reg->CONFIG_LTCPR   = esmltcpr;
        config_reg->CONFIG_EKR     = esmekr;
        config_reg->CONFIG_IEPSR4  = esmiepsr4;
        config_reg->CONFIG_IESR4   = esmiesr4;
        config_reg->CONFIG_ILSR4   = esmilsr4;
    }
}

/** @fn void setNotification(t_esmGroup1FuncPTR group1func, t_esmGroup2FuncPTR group2func)
 *   @brief Set Interrupt callback
 *
 *   @Sets the Interrupt callback
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void setNotification(t_esmGroup1FuncPTR group1func, t_esmGroup2FuncPTR group2func)
{
    syst_esmGroup1funptr = group1func;
    syst_esmGroup2funptr = group2func;
}

/** @fn void esmHighInterrupt(void)
 *   @brief High Level Interrupt for ESM
 */
/* #pragma CODE_STATE(esmHighInterrupt, 32) */
/* #pragma INTERRUPT(esmHighInterrupt, FIQ) */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void esmHighInterrupt(void)
{
    uint32 esmioffhr = esmREG->IOFFHR;
    uint32 vec       = esmioffhr - 1U;
    uint32 regWrFailStatus;

    if (vec < 32U)
    {
        regWrFailStatus = regWriteReadback(&esmREG->SR1[0U], M_THIRTY_ONE, M_ZERO, (uint32)1U << vec);
        if (syst_esmGroup1funptr != NULL_PTR)
        {
            (*syst_esmGroup1funptr)(vec);
        }
    }
    else if (vec < 64U)
    {
        regWrFailStatus = regWriteReadback(&esmREG->SR1[1U], M_THIRTY_ONE, M_ZERO, (uint32)1U << (vec - 32U));
        if (syst_esmGroup2funptr != NULL_PTR)
        {
            (*syst_esmGroup2funptr)(vec - 32U);
        }
    }
    else if (vec < 96U)
    {
        regWrFailStatus = regWriteReadback(&esmREG->SR4[0U], M_THIRTY_ONE, M_ZERO, (uint32)1U << (vec - 64U));
        if (syst_esmGroup1funptr != NULL_PTR)
        {
            (*syst_esmGroup1funptr)(vec - 32U);
        }
    }
    else if (vec < 128U)
    {
        regWrFailStatus = regWriteReadback(&esmREG->SR4[1U], M_THIRTY_ONE, M_ZERO, (uint32)1U << (vec - 96U));
        if (syst_esmGroup2funptr != NULL_PTR)
        {
            (*syst_esmGroup2funptr)(vec - 64U);
        }
    }
    else
    {
        regWrFailStatus  = regWriteReadback(&esmREG->SR4[1U], M_THIRTY_ONE, M_ZERO, (uint32)0xFFFFFFFFU);
        regWrFailStatus |= regWriteReadback(&esmREG->SR4[0U], M_THIRTY_ONE, M_ZERO, (uint32)0xFFFFFFFFU);
        regWrFailStatus |= regWriteReadback(&esmREG->SR1[1U], M_THIRTY_ONE, M_ZERO, (uint32)0xFFFFFFFFU);
        regWrFailStatus |= regWriteReadback(&esmREG->SR1[0U], M_THIRTY_ONE, M_ZERO, (uint32)0xFFFFFFFFU);
    }

    /* Raise a fatal error if any of above register writes and comparison failed */
    /* AR_CODE_REVIEW MR:R.2.1 <INSPECTED> "Infinite loop only on error" */
    /* LDRA_INSPECTED 28 D */
    M_ASSERT(M_ZERO == regWrFailStatus);
}
