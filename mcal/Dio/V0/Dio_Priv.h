/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Dio_priv.h
 *
 */

#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Dio.h"
#include "hw_ctrl_core.h"
#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"
#include "sys_common.h"
#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"
#include "SchM_Dio.h"
#include "soc.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define DIO_UTILS_ARRAYSIZE(array) ((sizeof(array) / sizeof((array)[0])))

/*
** \name Values used to configure the direction of GPIO pins.
* @{
*/
typedef enum
{
    DIO_DIR_INPUT  = 0x1U,
    DIO_DIR_OUTPUT = 0x0U
} Dio_DirectionType;
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
uint32 Dio_GetGPIOPortAddr(uint8 regNum);

void   Dio_GpioBitToggle(gpioPORT_t *port, uint32 bit);
uint32 Dio_GpioGetPort(const gpioPORT_t *port);
uint32 Dio_GpioPortWrite(const gpioPORT_t *port, uint32 setBits);
void   Dio_GpioSetBit(gpioPORT_t *port, uint32 bit, uint32 value);
uint32 Dio_GpioGetDirection(const gpioPORT_t *port, uint32 bit);
uint32 Dio_GpioGetLogicLvl(const gpioPORT_t *port, uint32 bit);

void Dio_GetGPIORegInfo(Dio_ChannelType channelId, uint32 *baseAddr, uint32 *pinNumber);

uint32 Dio_GetGPIOPortAddr(uint8 regNum);

Dio_LevelType Dio_PinRead(uint32 baseAddr, uint32 pinNumber);

void Dio_ChkDirWritePin(Dio_ChannelType ChannelId, Dio_LevelType Level);

#if (STD_ON == DIO_REGISTER_READBACK_API)
void Dio_HwRegisterReadback(Dio_RegisterReadbackType *RegRbPtr);
#endif

#if defined(DIO_WRITE_CHANNEL_EVENT_ID) && (STD_ON == DIO_SUPPORT_GIO)
Dio_StatusType Dio_CheckIO(Dio_ChannelType channelId, Dio_LevelType level);
#endif
#if (STD_ON == DIO_SUPPORT_GIO)
void DIO_GioGetDirection(Dio_ChannelType channelId, Dio_DirectionType *gioDirection);
#endif

#if (STD_ON == DIO_SUPPORT_GIO)
void Dio_GioReadPort(uint32 portId, uint32 *portVal);
void Dio_GioWritePort(uint32 portId, uint32 Level);
#endif

void Dio_ChkDirWritePin(Dio_ChannelType ChannelId, Dio_LevelType Level);

#if (STD_ON == DIO_DEV_ERROR_DETECT)

Std_ReturnType Dio_CheckChannelValidity(Dio_ChannelType channelId);

#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DIO_PRIV_H_ */
