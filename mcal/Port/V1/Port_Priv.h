/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Port_Priv.h
 *
 */

#ifndef PORT_PRIV_H_
#define PORT_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#include "hal_stdtypes.h"
#include "hw_types.h"
#include "soc.h"

#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

#include "hw_ctrl_core.h"

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#include "Port.h"
#include "Port_Irq.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* #if (PORT_DEV_ERROR_DETECT == STD_ON) */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_UP   (1U)
#define PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_DOWN (0U)

#define PORT_PAD_REGSETTING_SLEWCONTROL_FAST_SLEW (1U)
#define PORT_PAD_REGSETTING_SLEWCONTROL_SLOW_SLEW (0U)

#define PORT_PAD_REGSETTING_PULLINHIBIT_ENABLE  (0U)
#define PORT_PAD_REGSETTING_PULLINHIBIT_DISABLE (1U)
#define PORT_PAD_REGSETTING_DEFAULT             (0xFFU)

#define PORT_DIO_INVALID_BASE_ADDR (0U)

#define PORT_TWOFIFTYFIVE (0x255U)
#define PORT_ONE          (0x1U)
/** Maximum GPIO pins (MSS + RCSS) */
#define PORT_MAX_GPIO_PINS (64U)

#define PORT_BIT_CONF(Value, bit) ((uint32)Value << (uint32)bit)

#define PORT_FIFTH(n)  ((((n | 0x0000FFFFU) + 1U) >> 27) & 0x00000010U)
#define PORT_FOURTH(n) ((((n | 0x00FF00FFU) + 1U) >> 28) & 0x00000008U)
#define PORT_THIRD(n)  ((((n | 0x0F0F0F0FU) + 1U) >> 29) & 0x00000004U)
#define PORT_SECOND(n) ((((n | 0x33333333U) + 1U) >> 30) & 0x00000002U)
#define PORT_FIRST(n)  ((((n | 0X55555555U) + 1U) >> 31) & 0x00000001U)

#define PORT_GET_LOWER_INDEX(n) PORT_LOWER_INDEX((~n) | ((n) - (0x01U)))
#define PORT_LOWER_INDEX(n)     (PORT_FIFTH(n) | PORT_FOURTH(n) | PORT_THIRD(n) | PORT_SECOND(n) | PORT_FIRST(n))

/*Klocwork Inspected MISRAC_2012 Dir 4.9
 * Macro used for easire readability and uniformity with other modules. */
#define PORT_UTILS_ARRAYSIZE(array) ((sizeof(array) / sizeof((array)[0])))

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
} Port_PadRegSettingType;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void   Port_UnlockPadConfig(pinMuxBase_t *pinMuxRegp);
void   Port_LockPadConfig(pinMuxBase_t *pinMuxRegp);
void   Port_ConfigurePadCore(uint32 baseAdd, CONSTP2CONST(Port_PadRegSettingType, AUTO, PORT_APPL_DATA) padRegSetting);
void   Port_GPIOPortInit(const gpioPORT_t *portAddr);
uint32 Port_GetGPIOPortAddr(uint32 regNum);
uint32 Port_ReadMuxMode(uint32 pin_reg_offset);
void   Port_GPIOInit(gpioBASE_t *gioBaseREG);
void   Port_ConfigurePad(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padCfg, Port_PinModeType pinMode);

#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_GPIOIntConfigure(gpioBASE_t *gioBaseREG, const Port_DioRegConfigType *DioRegConfig);
#endif

void   Port_SetDirection(const gpioPORT_t *port, uint32 bit, uint32 dir);
void   Port_GPIOSetBit(gpioPORT_t *port, uint32 bit, uint32 value);
sint32 Port_ConfigOverrideCtrl(uint32 *pinMuxBase, uint32 pin, uint32 outputCtrl, uint32 inputCtrl);
sint32 Port_SelectFunc(uint32 *pinMuxBase, uint32 pin, uint32 func);
sint32 Port_ConfigPulls(uint32 *pinMuxBase, uint32 pin, uint32 pullVal);
sint32 Port_ConfigSlew(uint32 *pinMuxBase, uint32 pin, uint32 slewVal);
sint32 Port_ConfigPullInhibitEnable(uint32 *pinMuxBase, uint32 pin, uint32 InhibitVal);
sint32 Port_resetPadConfig(uint32 *pinMuxBase, uint32 pin);

#if (STD_ON == PORT_DEV_ERROR_DETECT)
extern void Port_ReportDetError(uint8 apiId, uint8 errorId);
uint32      Port_GetDioRegId(Port_PinModeType mode);

#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
boolean Port_IsDioMode(Port_PinModeType mode);
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) ||       \ \
          (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) ||  \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API)) */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_ConfigDioPinDirection(const uint32 gpioPortAddr, uint32 dioChannelId, Port_PinDirectionType direction);
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) ||         \ \
          (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) ||    \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API)) */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_ConfigDioPin(const uint32 gpioPortAddr, uint32 dioChannelId, Port_PinDirectionType direction,
                       Port_PinLevelValueType level);
void Port_ConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType curMode,
                             Port_PinDirectionType Direction);
void Port_SetPinConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType Mode);
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API)) */

void Port_DioInit(void);

void Port_MapConfigToReg(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padConfig,
                         P2VAR(Port_PadRegSettingType, AUTO, PORT_APPL_DATA) padRegSetting, Port_PinModeType pinMode);

void Port_DioConfigDir(void);
void Port_HWConfigDioPinDirection(const uint32 gpioPortAddr, const Port_PinConfigType *pinConfig);

#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_MssPinNotificationISR(Port_LevelTrig TrigValue);
void Port_RcssPinNotificationISR(Port_LevelTrig TrigValue);
void Port_DisableIntr(Port_PinType Pin);
void Port_EnableIntr(Port_PinType Pin);
#endif /* #if (STD_ON == PORT_ENABLE_INTR_API) */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef PORT_PRIV_H_ */
