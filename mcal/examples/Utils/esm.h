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

#ifndef ESM_H
#define ESM_H

// #include "reg_esm.h"
#include "hw_ctrl_core.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @enum esmSelfTestFlag
 *   @brief ESM Self-Test Status Type Definition
 *
 *   This type is used to represent ESM Self-Test Status.
 */
typedef enum esmSelfTestFlag
{
    esmSelfTest_Passed     = 0U,
    esmSelfTest_Active     = 1U,
    esmSelfTest_NotStarted = 2U,
    esmSelfTest_Failed     = 3U
} esmSelfTestFlag_t;

/* Configuration registers */
typedef struct esm_config_reg
{
    uint32 CONFIG_EEPAPR1;
    uint32 CONFIG_IESR1;
    uint32 CONFIG_ILSR1;
    uint32 CONFIG_LTCPR;
    uint32 CONFIG_EKR;
    uint32 CONFIG_IEPSR4;
    uint32 CONFIG_IESR4;
    uint32 CONFIG_ILSR4;
} esm_config_reg_t;

/* Configuration registers initial value */
/** @def ESM_EEPAPR1_CONFIGVALUE
 *   @brief Alias name for ESM enable ERROR Pin Register value for Group 1 errors
 */
#define ESM_EEPAPR1_CONFIGVALUE                                                                \
    ((uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) | \
     (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) | \
     (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) | \
     (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) | \
     (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) | \
     (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) | \
     (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) | \
     (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |   \
     (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |    \
     (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |    \
     (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U))

/** @def ESM_IESR1_CONFIGVALUE
 *   @brief Alias name for ESM Interrupt Enable Set Registers for Group 1 errors
 */
#define ESM_IESR1_CONFIGVALUE                                                                  \
    ((uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) | \
     (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) | \
     (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) | \
     (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) | \
     (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) | \
     (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) | \
     (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) | \
     (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |   \
     (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |    \
     (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |    \
     (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U))

/** @def ESM_ILSR1_CONFIGVALUE
 *   @brief Alias name for ESM Interrupt Level Set Registers for Group 1 errors
 */
#define ESM_ILSR1_CONFIGVALUE                                                                  \
    ((uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) | \
     (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) | \
     (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) | \
     (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) | \
     (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) | \
     (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) | \
     (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) | \
     (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |   \
     (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |    \
     (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |    \
     (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U))

/** @def ESM_LTCPR_CONFIGVALUE
 *   @brief Alias name for ESM Low-Time Counter Preload Register value
 */
#define ESM_LTCPR_CONFIGVALUE (uint32)(16384U - 1U)

/** @def ESM_EKR_CONFIGVALUE
 *   @brief Alias name for ESM Error Key Register value
 */
#define ESM_EKR_CONFIGVALUE 0U

/** @def ESM_IEPSR4_CONFIGVALUE
 *   @brief Alias name for ESM influence ERROR Pin Register value for Group 1 high errors
 */
#define ESM_IEPSR4_CONFIGVALUE                                                                 \
    ((uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) | \
     (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) | \
     (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) | \
     (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) | \
     (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) | \
     (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) | \
     (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) | \
     (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |   \
     (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |    \
     (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |    \
     (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U))

/** @def ESM_IESR4_CONFIGVALUE
 *   @brief Alias name for ESM Interrupt Enable Set Register value for Group 1 high errors
 */
#define ESM_IESR4_CONFIGVALUE                                                                  \
    ((uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) | \
     (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) | \
     (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) | \
     (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) | \
     (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) | \
     (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) | \
     (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) | \
     (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |   \
     (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |    \
     (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |    \
     (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U))

/** @def ESM_ILSR4_CONFIGVALUE
 *   @brief Alias name for ESM Interrupt Level Set Register value for Group 1 high errors
 */
#define ESM_ILSR4_CONFIGVALUE                                                                  \
    ((uint32)((uint32)0U << 31U) | (uint32)((uint32)0U << 30U) | (uint32)((uint32)0U << 29U) | \
     (uint32)((uint32)0U << 28U) | (uint32)((uint32)0U << 27U) | (uint32)((uint32)0U << 26U) | \
     (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | (uint32)((uint32)0U << 23U) | \
     (uint32)((uint32)0U << 22U) | (uint32)((uint32)0U << 21U) | (uint32)((uint32)0U << 20U) | \
     (uint32)((uint32)0U << 19U) | (uint32)((uint32)0U << 18U) | (uint32)((uint32)0U << 17U) | \
     (uint32)((uint32)0U << 16U) | (uint32)((uint32)0U << 15U) | (uint32)((uint32)0U << 14U) | \
     (uint32)((uint32)0U << 13U) | (uint32)((uint32)0U << 12U) | (uint32)((uint32)0U << 11U) | \
     (uint32)((uint32)0U << 10U) | (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) |   \
     (uint32)((uint32)0U << 7U) | (uint32)((uint32)0U << 6U) | (uint32)((uint32)0U << 5U) |    \
     (uint32)((uint32)0U << 4U) | (uint32)((uint32)0U << 3U) | (uint32)((uint32)0U << 2U) |    \
     (uint32)((uint32)0U << 1U) | (uint32)((uint32)0U << 0U))

/**
 *  @defgroup ESM ESM
 *  @brief Error Signaling Module.
 *
 *  The ESM module aggregates device errors and provides internal and external error response based
 * on error severity.
 *
 * Related Files
 *   - reg_esm.h
 *   - esm.h
 *   - esm.c
 *  @addtogroup ESM
 *  @{
 */

/* Esm Interface Functions */
void   esmInit(void);
uint32 esmError(esmBASE_t *esmBaseREG);
void   esmEnableError(esmBASE_t *esmBaseREG, uint64 channels);
void   esmDisableError(esmBASE_t *esmBaseREG, uint64 channels);
void   esmTriggerErrorPinReset(esmBASE_t *esmBaseREG);
void   esmActivateNormalOperation(esmBASE_t *esmBaseREG);
void   esmEnableInterrupt(esmBASE_t *esmBaseREG, uint64 channels);
void   esmDisableInterrupt(esmBASE_t *esmBaseREG, uint64 channels);
void   esmSetInterruptLevel(esmBASE_t *esmBaseREG, uint64 channels, uint64 flags);
void   esmClearStatus(esmBASE_t *esmBaseREG, uint32 group, uint64 channels);
void   esmClearStatusBuffer(esmBASE_t *esmBaseREG, uint64 channels);
void   esmSetCounterPreloadValue(esmBASE_t *esmBaseREG, uint32 value);

uint64 esmGetStatus(esmBASE_t *esmBaseREG, uint32 group, uint64 channels);
uint64 esmGetStatusBuffer(esmBASE_t *esmBaseREG, uint64 channels);

esmSelfTestFlag_t esmEnterSelfTest(esmBASE_t *esmBaseREG);
esmSelfTestFlag_t esmSelfTestStatus(esmBASE_t *esmBaseREG);

void esmHighInterrupt(void);

void esmGetConfigValue(esm_config_reg_t *config_reg, config_value_type_t type);

typedef void (*t_esmGroup1FuncPTR)(uint32 channel);
typedef void (*t_esmGroup2FuncPTR)(uint32 channel);

/** @fn void setNotification(t_esmGroup1FuncPTR group1func, t_esmGroup2FuncPTR group2func)
 *   @brief Set Interrupt callback
 *   @param[in] group1func - Group 1 channel callback
 *              group2func - Group 2 channel callback
 *
 * This is a function which populates the function pointers
 * with callback that is provided by the test application
 */
void setNotification(t_esmGroup1FuncPTR group1func, t_esmGroup2FuncPTR group2func);

/**@}*/

#ifdef __cplusplus
}
#endif /*extern "C" */

#endif
