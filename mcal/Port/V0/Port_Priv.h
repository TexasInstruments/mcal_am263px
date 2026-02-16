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

/**
 *  \file     Port_Priv.h
 *
 */

#ifndef PORT_PRIV_H_
#define PORT_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"
#include "hw_ctrl_core.h"
#include "soc.h"
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"
#include "sys_common.h"
#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#include "Port.h"
#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* #if (PORT_DEV_ERROR_DETECT == STD_ON) */

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_UP   (1U)
#define PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_DOWN (0U)

#define PORT_PAD_REGSETTING_SLEWCONTROL_FAST_SLEW (0U)
#define PORT_PAD_REGSETTING_SLEWCONTROL_SLOW_SLEW (1U)

#define PORT_PAD_REGSETTING_PULLINHIBIT_ENABLE  (0U)
#define PORT_PAD_REGSETTING_PULLINHIBIT_DISABLE (1U)

#define PORT_PAD_REGSETTING_NON_INVERSION_EN (0U)
#define PORT_PAD_REGSETTING_INVERSION_EN     (1U)

#define PORT_PAD_REGSETTING_SYNC_QUAL_EN         (0U)
#define PORT_PAD_REGSETTING_THREE_SAMPLE_QUAL_EN (1U)
#define PORT_PAD_REGSETTING_SIX_SAMPLE_QUAL_EN   (2U)
#define PORT_PAD_REGSETTING_ASYNC_QUAL_EN        (3U)

#define PORT_PAD_REGSETTING_DEFAULT (0xFFU)

#define PORT_DIO_INVALID_BASE_ADDR (0U)

#define PORT_UNLOCKPAD_IOCFGKICK0 0x83E70B13U
#define PORT_UNLOCKPAD_IOCFGKICK1 0x95A4F1E0U

#define PORT_LOCKPADVALUE (0x0U)

#define PORT_CLEAR_EDGE (0xFFFFFFFFU)

#define PORT_UTILS_ARRAYSIZE(array) ((sizeof(array) / sizeof((array)[0])))

/** \Number of pins per bank */
#define PORT_PINS_PER_BANK_SHIFT (4U)

/** \brief Number of pins per register */
#define PORT_PINS_PER_REG_SHIFT (5U)

/** \Returns the bank index based on pin number */
#define PORT_GET_BANK_INDEX(PinNum) (uint32)(((PinNum) >> PORT_PINS_PER_BANK_SHIFT))

/** \brief Returns the register index based on pin number */
#define PORT_GET_REG_INDEX(PinNum) (uint32)(((PinNum) >> PORT_PINS_PER_REG_SHIFT))

/** \brief Returns the Pin Bit Position based on pin number and register id */
#define PORT_GET_REG_BIT_POS(PinNum, PinBankRegID) (uint32)(((PinNum) - (PinBankRegID * 32U)))

/** \Port bank mask value */
#define PORT_BANK_MASK (0x0000FFFFU)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Data type to define the pad configuration */
typedef struct
{
    uint32 pin_reg_offset;
    uint32 slewcontrol;
    uint32 pulludenable;
    uint32 pullinhibit;
    uint32 oe_n_override;
    uint32 oe_n_override_ctrl;
    uint32 ie_n_override;
    uint32 ie_n_override_ctrl;
    uint32 muxmode;
    uint32 HSmaster;
    uint32 HSmode;
    uint32 inversion;
    uint32 qualifiertype;
    uint8  gpiocoreowner;
} Port_PadRegSettingType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void    Port_UnlockPadConfig(pinMuxBase_t *pinMuxRegp);
void    Port_LockPadConfig(pinMuxBase_t *pinMuxRegp);
void    Port_ConfigurePadCore(uint32 baseAdd, CONSTP2CONST(Port_PadRegSettingType, AUTO, PORT_APPL_DATA) padRegSetting);
void    Port_GPIOPortInit(const gpioPORT_t *portAddr);
uint32  Port_GetGPIOPortAddr(uint32 regNum);
uint32  Port_ReadMuxMode(uint32 pin_reg_offset);
void    Port_GPIOInit(gpioBASE_t *gioBaseREG);
void    Port_ConfigurePad(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padCfg, Port_PinModeType pinMode);
void    Port_SetDirection(const gpioPORT_t *port, uint32 bit, uint32 dir);
void    Port_GPIOSetBit(gpioPORT_t *port, uint32 bit, uint32 value);
sint32  Port_ConfigOverrideCtrl(uint32 *pinMuxBase, uint32 pin, uint32 outputCtrl, uint32 inputCtrl);
sint32  Port_SelectFunc(uint32 *pinMuxBase, uint32 pin, uint32 func);
sint32  Port_ConfigPulls(uint32 *pinMuxBase, uint32 pin, uint32 pullVal);
sint32  Port_ConfigSlew(uint32 *pinMuxBase, uint32 pin, uint32 slewVal);
sint32  Port_ConfigPullInhibitEnable(uint32 *pinMuxBase, uint32 pin, uint32 InhibitVal);
sint32  Port_ResetPadConfig(uint32 *pinMuxBase, uint32 pin);
void    Port_GPIOEdgTrigConfigure(const gpioPORT_t *portAddr, uint32 bit, Port_EdgeTrig TriEdge, boolean TriggerEn);
sint32  Port_ConfigInversion(uint32 *pinMuxBase, uint32 pin, uint32 invVal);
sint32  Port_ConfigQualType(uint32 *pinMuxBase, uint32 pin, uint32 qualifierValue);
sint32  Port_ConfigHSmaster(uint32 *pinMuxBase, uint32 pin, uint32 hsmasterValue);
sint32  Port_ConfigHSmode(uint32 *pinMuxBase, uint32 pin, uint32 hsmodeValue);
uint32  Port_GetDioRegId(Port_PinModeType mode);
boolean Port_IsDioMode(Port_PinModeType mode);
sint32  Port_ConfigGpioSel(uint32 *pinMuxBase, uint32 pin, uint8 gpioCoreSel);

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_ConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType curMode,
                             Port_PinDirectionType Direction);

void Port_ConfigDioPin(const uint32 gpioPortAddr, uint32 dioChannelId, Port_PinDirectionType direction,
                       Port_PinLevelValueType level);
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API))   */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_ConfigDioPinDirection(const uint32 gpioPortAddr, uint32 dioChannelId, Port_PinDirectionType direction);

void Port_ConfigurePad(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padCfg, Port_PinModeType pinMode);

void Port_MapConfigToReg(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padConfig,
                         P2VAR(Port_PadRegSettingType, AUTO, PORT_APPL_DATA) padRegSetting, Port_PinModeType pinMode);
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) ||      \ \
          (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API))        */

void Port_DioInit(void);
void Port_DioConfigDir(void);
#if (STD_ON == PORT_SET_PIN_MODE_API)
void Port_SetPinConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType Mode);
#endif /*(STD_ON == PORT_SET_PIN_MODE_API)*/
void Port_HWConfigDioPinDirection(const uint32 gpioPortAddr, const Port_PinConfigType *pinConfig);

#if (STD_ON == PORT_DEV_ERROR_DETECT)
extern void Port_ReportDetError(uint8 apiId, uint8 errorId);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */

#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_DisableIntr(Port_PinType Pin);
void Port_EnableIntr(Port_PinType Pin);
void Port_GpioPinNotificationISR(uint32 portXbaroutPinInfo);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

#if (STD_ON == PORT_GET_INTR_ST_API)
uint32 Port_GetStatus(Port_PinType bankIdx);
#endif /* #if (STD_ON == PORT_GET_INTR_ST_API) */

void Port_ClearStatus(Port_PinType bankIdx, uint32 maskValue);

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef PORT_PRIV_H_ */
