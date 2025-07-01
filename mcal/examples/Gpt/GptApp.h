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
 *  \file     GptApp.h
 *
 *  \brief    GPT example header file
 *
 */

#ifndef GPT_APP_H_
#define GPT_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_NAME "GPT_APP"

/* \brief: GP Timer ticks for 1 minutes
 *         As all GP timers receive 40Mhz sys clock default one tick corresponds
 *         to 5ns. so 1 minute = 1,200,000,000 ticks.
 */
#define GPTIMER_COUNT_1MINUTE (0x47868C00)

/* \brief: Count value passed to Gpt_StartTimer function.
 *         Currently configured to 6 seconds, change divider for changing count
 *         value
 */
#define GPTIMER_COUNT_VALUE (GPTIMER_COUNT_1MINUTE / 10U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void Gpt_Channel_Notify1(void);
void Gpt_Channel_Notify2(void);
void Gpt_Channel_Notify3(void);
void Gpt_Channel_Notify4(void);
void Gpt_Channel_Notify5(void);
void Gpt_Channel_Notify6(void);
void Gpt_Channel_Notify7(void);
void Gpt_Channel_Notify8(void);
void Gpt_Channel_Notify9(void);
void Gpt_Channel_Notify10(void);
void Gpt_Channel_Notify11(void);
void Gpt_Channel_Notify12(void);
void Gpt_Channel_Notify13(void);
void Gpt_Channel_Notify14(void);
void Gpt_Channel_Notify15(void);
void Gpt_Channel_Notify16(void);
void Gpt_Channel_Notify17(void);
void Gpt_Channel_Notify18(void);
void Gpt_Channel_Notify19(void);
void Gpt_Channel_Notify20(void);
void Gpt_Channel_Notify21(void);
void Gpt_Channel_Notify22(void);
void Gpt_Channel_Notify23(void);
void Gpt_Channel_Notify24(void);
void Gpt_Channel_Notify25(void);
void Gpt_Channel_Notify26(void);
void Gpt_Channel_Notify27(void);
void Gpt_Channel_Notify28(void);
void Gpt_Channel_Notify29(void);
void Gpt_Channel_Notify30(void);
void Gpt_Channel_Notify31(void);
void Gpt_Channel_Notify32(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef GPT_APP_H_ */
