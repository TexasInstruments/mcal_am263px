/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     Gpt_Priv.h
 *
 */

#ifndef GPT_PRIV_H_
#define GPT_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/

#include "Gpt.h"
#include "hw_ctrl_core.h"
#include "sys_common.h"
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/*LDRA_NOANALYSIS*/
#include "Det.h"
/*LDRA_ANALYSIS*/
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void          Gpt_RTIInit_Channel(rtiBASE_t *rtireg, Gpt_ChannelType ChannelId, uint32 tickVal);
void          Gpt_RTI_DeInit(rtiBASE_t *rtireg, Gpt_ValueType channelId);
Gpt_ValueType Gpt_GetCounter_Values(const rtiBASE_t *rtireg, Gpt_ValueType channelId, Gpt_ValueType *UpdCompare,
                                    Gpt_ValueType *compare);
void Gpt_RTI_StartTimer(rtiBASE_t *rtireg, Gpt_ValueType channelId, Gpt_ValueType tickFreq, Gpt_ChannelMode ChannelMode,
                        Gpt_ValueType value);
void Gpt_RTI_StopTimer(rtiBASE_t *rtireg, Gpt_ValueType channelId);
void Gpt_RTI_EnableNotification(rtiBASE_t *rtireg, Gpt_ValueType channelId);
void Gpt_RTI_DisableNotification(rtiBASE_t *rtireg, Gpt_ValueType channelId);
void Gpt_resetDrvObj(Gpt_DriverObjType *drvObj);
Std_ReturnType Gpt_copyConfig(Gpt_DriverObjType *drvObj, const Gpt_ConfigType *cfgPtr);
void           Gpt_ConfigHwChannel(Gpt_DriverObjType *drvObj, Gpt_ChannelStateType status);
void           Gpt_RTINotifyContIsr(rtiBASE_t *rtireg, Gpt_ValueType channelId);
void           Gpt_RTINotifySingleIsr(rtiBASE_t *rtireg, Gpt_ValueType channelId);
FUNC(void, GPT_CODE) Gpt_SetRegStartTimer(Gpt_ChannelType channel, Gpt_ValueType value);
/** \brief  Continuous notification ISR */
FUNC(void, GPT_CODE) Gpt_NotifContIsr(Gpt_ChannelType Channel);
/** \brief Singleshot notification ISR */
FUNC(void, GPT_CODE) Gpt_NotifSingleIsr(Gpt_ChannelType Channel);
uint32 Gpt_GetRTIChannelAddr(uint32 channelId);
#if (STD_ON == GPT_REGISTER_READBACK_API)
void Gpt_RegReadBack(const rtiBASE_t *rtireg, GptConfigReg *GptRegConf);
#endif

uint32 Mod_Difference(uint32 valueA, uint32 valueB);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef GPT_PRIV_H_ */
