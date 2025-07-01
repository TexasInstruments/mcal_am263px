/* ======================================================================
 *   Copyright (c) 2022-2023 Texas Instruments Incorporated
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
 *  \file     Dio_Priv.h
 *
 */

#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "hal_stdtypes.h"
#include "Dio.h"

#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"

#include "hw_ctrl_core.h"

#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/*LDRA_INSPECTED 340 S : MISRAC_2012_D.4.9
 * "Reason - Macro cannot be avoided here" */
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
uint32 Dio_GetGPIOPortAddr(uint32 regNum);

void          Dio_GpioBitToggle(gpioPORT_t *port, uint32 bit);
uint32        Dio_GpioGetPort(const gpioPORT_t *port);
uint32        Dio_GpioPortWrite(const gpioPORT_t *port, uint32 setBits);
void          Dio_GpioSetBit(gpioPORT_t *port, uint32 bit, uint32 value);
uint32        Dio_GpioGetDirection(const gpioPORT_t *port, uint32 bit);
uint32        Dio_GpioGetLogicLvl(const gpioPORT_t *port, uint32 bit);
Dio_LevelType Dio_PinRead(uint32 baseAddr, uint32 pinNumber);
void          Dio_GetGPIORegInfo(Dio_ChannelType channelId, uint32 *baseAddr, uint32 *pinNumber);
void          Dio_ChkDirWritePin(Dio_ChannelType ChannelId, Dio_LevelType Level);

void Dio_HwRegisterReadback(Dio_RegisterReadbackType *RegRbPtr);

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

#if (STD_ON == DIO_DEV_ERROR_DETECT)
Std_ReturnType Dio_CheckChannelValidity(Dio_ChannelType channelId);
#endif /* #if (STD_ON == DIO_DEV_ERROR_DETECT) */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DIO_PRIV_H_ */
