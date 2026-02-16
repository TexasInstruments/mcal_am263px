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
 *  \file     Gpt_Irq.h
 *
 *  \brief    This file contains ISR function declaration for GPT MCAL driver
 *
 */

#ifndef GPT_IRQ_H_
#define GPT_IRQ_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Gpt.h"
#include "sys_common.h"
#if (GPT_ISR_TYPE == GPT_ISR_CAT2)
#include "Os.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************************
 * INCLUDES
 ********************************************************************************************************************/

/********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ********************************************************************************************************************/

/* Version identification */
#define GPT_IRQ_MAJOR_VERSION (10U)
#define GPT_IRQ_MINOR_VERSION (1U)
#define GPT_IRQ_PATCH_VERSION (0U)

#define CHANNEL_MODES 2U
/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/**
 *  \name GPT Driver ISR category level
 *
 *  Defines for GPT Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define GPT_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define GPT_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define GPT_ISR_CAT2 (0x02U)
/* @} */

/** \brief Typedef for the ISR Function Array */
typedef void (*Gpt_IsrRefType)(Gpt_ChannelType channel);

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/** \brief The Index for the ISR_Function Array*/
extern VAR(uint32, GPT_DATA) Gpt_IsrIndex[GPT_RTI_MAX];

/** \brief The Index for the notification Function Array*/
extern CONST(Gpt_IsrRefType, GPT_CONST) Gpt_IsrNotifyFunctions[CHANNEL_MODES];

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/** \brief Interrupt Functions */

#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 0 interrupt service routine */
void Gpt_Ch0Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch0Isr);
#endif /* GPT_ISR_TYPE */

#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 1 interrupt service routine */
void Gpt_Ch1Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch1Isr);
#endif /* GPT_ISR_TYPE */

#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 2 interrupt service routine */
void Gpt_Ch2Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch2Isr);
#endif /* GPT_ISR_TYPE */

#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 3 interrupt service routine */
void Gpt_Ch3Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch3Isr);
#endif /* GPT_ISR_TYPE */

#if defined(GPT_CHANNEL_4)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 4 interrupt service routine */
void Gpt_Ch4Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch4Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_5)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 5 interrupt service routine */
void Gpt_Ch5Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch5Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_6)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 6 interrupt service routine */
void Gpt_Ch6Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch6Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_7)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 7 interrupt service routine */
void Gpt_Ch7Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch7Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_8)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 8 interrupt service routine */
void Gpt_Ch8Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch8Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_9)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 9 interrupt service routine */
void Gpt_Ch9Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch9Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_10)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 10 interrupt service routine */
void Gpt_Ch10Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch10Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_11)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 11 interrupt service routine */
void Gpt_Ch11Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch11Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_12)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 12 interrupt service routine */
void Gpt_Ch12Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch12Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_13)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 13 interrupt service routine */
void Gpt_Ch13Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch13Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_14)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 14 interrupt service routine */
void Gpt_Ch14Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch14Isr);
#endif /* GPT_ISR_TYPE */
#endif
#if defined(GPT_CHANNEL_15)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 15 interrupt service routine */
void Gpt_Ch15Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch15Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_16)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 16 interrupt service routine */
void Gpt_Ch16Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch16Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_17)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 17 interrupt service routine */
void Gpt_Ch17Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch17Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_18)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 18 interrupt service routine */
void Gpt_Ch18Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch18Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_19)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 19 interrupt service routine */
void Gpt_Ch19Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch19Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_20)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 20 interrupt service routine */
void Gpt_Ch20Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch20Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_21)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 21 interrupt service routine */
void Gpt_Ch21Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch21Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_22)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 22 interrupt service routine */
void Gpt_Ch22Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch22Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_23)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 23 interrupt service routine */
void Gpt_Ch23Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch23Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_24)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 24 interrupt service routine */
void Gpt_Ch24Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch24Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_25)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 25 interrupt service routine */
void Gpt_Ch25Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch25Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_26)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 26 interrupt service routine */
void Gpt_Ch26Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch26Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_27)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 27 interrupt service routine */
void Gpt_Ch27Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch27Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_28)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 28 interrupt service routine */
void Gpt_Ch28Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch28Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_29)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 29 interrupt service routine */
void Gpt_Ch29Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch29Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_30)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 30 interrupt service routine */
void Gpt_Ch30Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch30Isr);
#endif /* GPT_ISR_TYPE */
#endif

#if defined(GPT_CHANNEL_31)
#if ((GPT_ISR_TYPE == GPT_ISR_CAT1) || (GPT_ISR_TYPE == GPT_ISR_VOID))
/** \brief Channel 31 interrupt service routine */
void Gpt_Ch31Isr(void);
#elif (GPT_ISR_TYPE == GPT_ISR_CAT2)
ISR(Gpt_Ch31Isr);
#endif /* GPT_ISR_TYPE */
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef GPT_IRQ_H_ */

/* @} */
