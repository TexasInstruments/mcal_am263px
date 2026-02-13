
/* ======================================================================
 *   Copyright (C) 2022 Texas Instruments Incorporated
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
