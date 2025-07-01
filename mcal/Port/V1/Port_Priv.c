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
 *  \file     Port_Priv.c
 *
 */

#define PORT_PLATFORM_SOURCE (1)

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Port.h"
#include "Port_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */
/* ========================================================================== */
/*                           Staic function declartaions                                */
/* ========================================================================== */

static uint32 Port_GetMuxMode(Port_PinModeType Port_PinMode, const Port_PinModeConfigType *modeCfg,
                              uint32 Port_NumPortModes);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
#define PORT_START_SEC_CONST_32
#include "Port_MemMap.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/** \brief PORT driver object */
extern VAR(Port_ConfigType, PORT_VAR_ZERO_INIT) Port_DrvObj;

static CONST(uint32, PORT_CONST) Port_GPIOPortAddr[8] = {SOC_GIO_PORTA_BASE, SOC_GIO_PORTB_BASE, SOC_GIO_PORTC_BASE,
                                                         SOC_GIO_PORTD_BASE, SOC_GIO_PORTE_BASE, SOC_GIO_PORTF_BASE,
                                                         SOC_GIO_PORTG_BASE, SOC_GIO_PORTH_BASE};

#define PORT_STOP_SEC_CONST_32
#include "Port_MemMap.h"

#define PORT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"

/** \brief PORT Intrrupt object */
Port_IntrStatus Port_IntrObj;

#define PORT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void    Port_RcssPinNotificationISR_internal(Port_LevelTrig TrigValue, uint32 *Gio_Flg_value);
static void    Port_MssPinNotificationISR_internal(Port_LevelTrig TrigValue, uint32 *Gio_Flg_value);
static boolean Port_EnableIntr_Internal(uint8 idx, Port_PinType *pin, gpioBASE_t **gioBaseREG);

#define PORT_START_SEC_CODE
#include "Port_MemMap.h"

/** @fn void Port_UnlockPadConfig(pinMuxBase_t *pinMuxRegp)
 *   @brief Configure the key to enable the pinmuxing.
 *
 */

void Port_UnlockPadConfig(pinMuxBase_t *pinMuxRegp)
{
    /* Enable Pin Muxing */
    /* Value of pinMuxRegp can be pinMuxReg */
    pinMuxRegp->IOCFGKICK0 = 0x83E70B13U;
    pinMuxRegp->IOCFGKICK1 = 0x95A4F1E0U;
}

/** @fn void Port_LockPadConfig(pinMuxBase_t *pinMuxRegp)
 *   @brief Lock to disable the pinmuxing.
 *
 */

void Port_LockPadConfig(pinMuxBase_t *pinMuxRegp)
{
    /* Disable Pin Muxing */
    /* Value of pinMuxRegp can be pinMuxReg */
    pinMuxRegp->IOCFGKICK1 = 0x0U;
    pinMuxRegp->IOCFGKICK0 = 0x0U;
}

uint32 Port_GetGPIOPortAddr(uint32 regNum)
{
    uint32 retVal;

#if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (regNum >= PORT_UTILS_ARRAYSIZE(Port_GPIOPortAddr))
    {
        retVal = PORT_DIO_INVALID_BASE_ADDR;
    }
    else
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    {
        retVal = Port_GPIOPortAddr[regNum];
    }

    return (retVal);
}

void Port_GPIOPortInit(const gpioPORT_t *portAddr)
{
    uint32 regVal         = 0U;
    uint32 regWriteStatus = 0U;

    /** - Port output values */
    regWriteStatus = regWriteReadback(&portAddr->DOUT, M_THIRTY_ONE, M_ZERO, regVal);

    /** - Port direction */
    regWriteStatus |= regWriteReadback(&portAddr->DIR, M_THIRTY_ONE, M_ZERO, regVal);

    /** - Port open drain enable */
    regWriteStatus |= regWriteReadback(&portAddr->PDR, M_THIRTY_ONE, M_ZERO, regVal);

    /** - Port pullup / pulldown selection */
    regWriteStatus |= regWriteReadback(&portAddr->PSL, M_THIRTY_ONE, M_ZERO, regVal);

    /** - Port pullup / pulldown enable*/
    regWriteStatus |= regWriteReadback(&portAddr->PULDIS, M_THIRTY_ONE, M_ZERO, regVal);

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
}

void Port_GPIOInit(gpioBASE_t *gioBaseREG)
{
    uint32 regWriteStatus = 0U;

    /** bring GIO module out of reset */
    regWriteStatus = regWriteReadback(&gioBaseREG->GCR0, M_THIRTY_ONE, M_ZERO, 1U);
    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    gioBaseREG->ENACLR = 0xFFFFFFFFU;
    gioBaseREG->LVLCLR = 0xFFFFFFFFU;
}

#if (STD_ON == PORT_ENABLE_INTR_API)
void Port_GPIOIntConfigure(gpioBASE_t *gioBaseREG, const Port_DioRegConfigType *DioRegConfig)
{
    uint8  Pin            = DioRegConfig->Port_DioPinNumber;
    uint32 regWriteStatus = 0U;

    if (DioRegConfig->Port_DioSubsystem == PORT_RCSS)
    {
        Pin = DioRegConfig->Port_DioPinNumber - 32U;

        Port_IntrObj.RcssIntrLevel |= ((uint32)(DioRegConfig->Port_DioLevelTrigger) << Pin);
    }
    else
    {
        Port_IntrObj.MssIntrLevel |= ((uint32)(DioRegConfig->Port_DioLevelTrigger) << Pin);
    }

    if (DioRegConfig->Port_DioEdgeTrigger == PORT_BOTH_EDGE)
    {
        regWriteStatus = regWriteReadback(&gioBaseREG->INTDET, M_THIRTY_ONE, M_ZERO, PORT_BIT_CONF(M_ONE, Pin));
    }
    else
    {
        regWriteStatus = regWriteReadback(&gioBaseREG->INTDET, M_THIRTY_ONE, M_ZERO, PORT_BIT_CONF(M_ZERO, Pin));
    }

    gioBaseREG->POL |= ((uint32)(DioRegConfig->Port_DioEdgeTrigger) << Pin);

    regWriteStatus |= regWriteReadback(&gioBaseREG->LVLSET, M_THIRTY_ONE, M_ZERO,
                                       PORT_BIT_CONF(DioRegConfig->Port_DioLevelTrigger, Pin));

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    HW_WR_REG32(&gioBaseREG->FLG, PORT_BIT_CONF(M_ONE, Pin));
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

/** @fn sint32 Port_ConfigOverrideCtrl(uint32 pinMuxBase, uint32 pin, uint32 outputCtrl, uint32
 * inputCtrl)
 *   @brief Configurations for the input and output override control.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] outputCtrl: Output control selection
 *               The parameter \e outputCtrl can be one of the following values:
 *                - \b OUTPUT_EN
 *                - \b OUTPUT_DIS
 *                - \b OUTEN_RETAIN_HW_CTRL
 *    @param[in] inputCtrl: Input control selection
 *               The parameter \e inputCtrl can be one of the following values:
 *                - \b INPUT_EN
 *                - \b INPUT_DIS
 *                - \b INPEN_RETAIN_HW_CTRL
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigOverrideCtrl(uint32 *pinMuxBase, uint32 pin, uint32 outputCtrl, uint32 inputCtrl)
{
    sint32 retVal           = 0;
    uint32 regWriteStatus   = 0U;
    uint32 overrideDefValue = 0xFU;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_SEVEN, M_FOUR, overrideDefValue);

    /* Setup the output control of the pin */
    if (OUTEN_RETAIN_HW_CTRL != outputCtrl)
    {
        pinMuxBase[(pin / 4U)] &= PIN_OUTEN_MASK;
        regWriteStatus         |= regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_SEVEN, M_SEVEN, outputCtrl);

        pinMuxBase[(pin / 4U)] |= OUTEN_OVRRIDE_EN;
    }
    else /* OUTEN_RETAIN_HW_CTRL */
    {
        pinMuxBase[(pin / 4U)] &= PIN_OUTEN_OVRRIDE_MASK;
    }

    /* Setup the input control of the pin */
    if (INPEN_RETAIN_HW_CTRL != inputCtrl)
    {
        pinMuxBase[(pin / 4U)] &= PIN_INPUTEN_MASK;
        regWriteStatus         |= regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_FIVE, M_FIVE, inputCtrl);

        pinMuxBase[(pin / 4U)] |= INPEN_OVRRIDE_EN;
    }
    /* INPEN_RETAIN_HW_CTRL */
    else
    {
        pinMuxBase[(pin / 4U)] &= PIN_INPEN_OVRRIDE_MASK;
    }

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

/** @fn sint32 Port_SelectFunc(uint32 *pinMuxBase, uint32 pin, uint32 func)
 *   @brief Setup the pin personality.
 *
 *   This function sets up the functional personality of the pin.
 *   The specified signal will be brought out on the pin.
 *   As there is no strict check on the parameters passed, the values passed
 *   must be from the macro specified in the header pinmux.h.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] func: Desired signal functionality to be muxed onto the pin
 */
sint32 Port_SelectFunc(uint32 *pinMuxBase, uint32 pin, uint32 func)
{
    uint32 retVal = 0, muxmode_mask_value = 0xFFFFFFF0U;

    pinMuxBase[(pin / 4U)] = (func | (pinMuxBase[(pin / 4U)] & muxmode_mask_value));

    return retVal;
}

/** @fn sint32 Port_ConfigPulls(uint32 *pinMuxBase,uint32 pin, uint32 pullVal)
 *   @brief Configurations for the pulls on the pins.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] pullVal: Pull selection
 *               The parameter \e pullVal can be one of the following values:
 *                - \b PULLUP_EN
 *                - \b PULLDOWN_EN
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigPulls(uint32 *pinMuxBase, uint32 pin, uint32 pullVal)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the configured pull control of the pin */
    pinMuxBase[(pin / 4U)] &= PIN_PULL_SELECT_MASK;
    regWriteStatus          = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_NINE, M_NINE, pullVal);
    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

/** @fn sint32 Port_ConfigSlew(uint32 *pinMuxBase, uint32 pin, uint32 slewVal)
 *   @brief Configurations for the slew on the pins.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] slewVal: Slew selection
 *               The parameter \e slewVal can be one of the following values:
 *                - \b SLEW_LOW
 *                - \b SLEW_HIGH
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigSlew(uint32 *pinMuxBase, uint32 pin, uint32 slewVal)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the configured slew of the pin */
    pinMuxBase[(pin / 4U)] &= PIN_SLEW_CONTROL_MASK;
    regWriteStatus          = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_TEN, M_TEN, slewVal);
    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

/** @fn sint32 Port_ConfigPullInhibitEnable(uint32 *pinMuxBase, uint32 pin, uint32
 * pullInhibitEnableVal)
 *   @brief Configurations for the pullInhibit on the pins.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] slewVal: PIN_PULL_INHIBIT  selection
 *               The parameter \e PIN_PULL_INHIBIT can be one of the following values:
 *                - \b PIN_PULL_INHIBIT_DISABLE
 *                - \b PIN_PULL_INHIBIT_ENABLE
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigPullInhibitEnable(uint32 *pinMuxBase, uint32 pin, uint32 InhibitVal)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the configured pullInhibitEnable of the pin */
    pinMuxBase[(pin / 4U)] &= PIN_PULL_INHIBIT_MASK;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_EIGHT, M_EIGHT, InhibitVal);
    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

sint32 Port_resetPadConfig(uint32 *pinMuxBase, uint32 pin)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;
    /*Reset the value */
    uint32 regVal = 0x000002C1U;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_ELEVEN, M_ZERO, regVal);
    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

/*
 * \brief       Function to program the pad properties
 *
 *
 * \param[in]   baseAdd - Base address of pad config register
 * \param[in]       padConfig - property of the pad to be configured.
 *
 * \return           error status.If error has occured it returns a non zero
 *                   value.
 *                   If no error has occured then return status will be zero. .
 *
 */
void Port_ConfigurePadCore(uint32 baseAdd, CONSTP2CONST(Port_PadRegSettingType, AUTO, PORT_APPL_DATA) padRegSetting)
{
    Port_UnlockPadConfig(((pinMuxBase_t *)baseAdd));

    Port_resetPadConfig((uint32 *)baseAdd, padRegSetting->pin_reg_offset);

    (void)Port_ConfigOverrideCtrl((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->oe_n_override_ctrl,
                                  padRegSetting->ie_n_override_ctrl);

    if (padRegSetting->muxmode != PORT_PAD_REGSETTING_DEFAULT)
    {
        (void)Port_SelectFunc((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->muxmode);
    }
    if (padRegSetting->pullinhibit != PORT_PAD_REGSETTING_DEFAULT)
    {
        (void)Port_ConfigPullInhibitEnable((uint32 *)baseAdd, padRegSetting->pin_reg_offset,
                                           padRegSetting->pullinhibit);
    }
    if (padRegSetting->pulludenable != PORT_PAD_REGSETTING_DEFAULT)
    {
        (void)Port_ConfigPulls((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->pulludenable);
    }

    if (padRegSetting->slewcontrol != PORT_PAD_REGSETTING_DEFAULT)
    {
        (void)Port_ConfigSlew((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->slewcontrol);
    }

    Port_LockPadConfig(((pinMuxBase_t *)baseAdd));
}

uint32 Port_ReadMuxMode(uint32 pin_reg_offset)
{
    uint32 muxmode_val;
    uint32 pin_reg_addr;
    uint32 baseAdd = SOC_IOMUX_REG_BASE;

    Port_UnlockPadConfig((pinMuxBase_t *)baseAdd);

    pin_reg_addr = baseAdd + pin_reg_offset;
    muxmode_val  = M_REG_READ32(pin_reg_addr);

    Port_LockPadConfig((pinMuxBase_t *)baseAdd);

    /*Get the function select [3:0] from the register value*/
    muxmode_val = (uint32)((uint32)muxmode_val & 0xFU);

    return muxmode_val;
}

/** @fn void Port_GPIOSetBit(gioPORT_t *port, uint32 bit, uint32 value)
 *   @brief Write Bit
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *   @param[in] bit number 0-7 that specifies the bit to be written to.
 *              - 0: LSB
 *              - 7: MSB
 *   @param[in] value binary value to write to bit
 *
 *   Writes a value to the specified pin of the given GIO port
 */
void Port_GPIOSetBit(gpioPORT_t *port, uint32 bit, uint32 value)
{
    if (value != 0U)
    {
        port->DSET = (uint32)1U << bit;
    }
    else
    {
        port->DCLR = (uint32)1U << bit;
    }
}

/** @fn void Port_SetPinDirection(gioPORT_t *port, uint32 dir)
 *   @brief Set Port Direction
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *   @param[in] dir value to write to DIR register
 *
 *   Set the direction of GIO pins at runtime.
 */
void Port_SetDirection(const gpioPORT_t *port, uint32 bit, uint32 dir)
{
    uint32 pinMask = (uint32)1U << bit;
    uint32 oeRegVal;
    uint32 regWriteStatus = 0U;

    oeRegVal = M_REG_READ32(&port->DIR);

    if (dir != 0U)
    {
        oeRegVal       |= pinMask;
        regWriteStatus  = regWriteReadback(&port->DIR, M_THIRTY_ONE, M_ZERO, oeRegVal);
    }
    else
    {
        oeRegVal       &= ~pinMask;
        regWriteStatus  = regWriteReadback(&port->DIR, M_THIRTY_ONE, M_ZERO, oeRegVal);
    }

    if (regWriteStatus != MCAL_REGWR_E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
}

#if (STD_ON == PORT_DEV_ERROR_DETECT)
uint32 Port_GetDioRegId(Port_PinModeType mode)
{
    uint32 dioRegId = 0;

    switch (mode)
    {
        case PORT_PIN_MODE_MSS_GPIOA:
            dioRegId = 0U;
            break;
        case PORT_PIN_MODE_MSS_GPIOB:
            dioRegId = 1U;
            break;
        case PORT_PIN_MODE_MSS_GPIOC:
            dioRegId = 2U;
            break;
        case PORT_PIN_MODE_MSS_GPIOD:
            dioRegId = 3U;
            break;
        case PORT_PIN_MODE_RCSS_GPIOA:
            dioRegId = 4U;
            break;
        case PORT_PIN_MODE_RCSS_GPIOB:
            dioRegId = 5U;
            break;
        case PORT_PIN_MODE_RCSS_GPIOC:
            dioRegId = 6U;
            break;
        case PORT_PIN_MODE_RCSS_GPIOD:
            dioRegId = 7U;
            break;
        default:
            /*Do nothing*/
            break;
    }
    return dioRegId;
}
#endif /* PORT_DEV_ERROR_DETECT */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
boolean Port_IsDioMode(Port_PinModeType mode)
{
    boolean isDioMode;

    switch (mode)
    {
        case PORT_PIN_MODE_MSS_GPIOA:
        case PORT_PIN_MODE_MSS_GPIOB:
        case PORT_PIN_MODE_MSS_GPIOC:
        case PORT_PIN_MODE_MSS_GPIOD:
        case PORT_PIN_MODE_RCSS_GPIOA:
        case PORT_PIN_MODE_RCSS_GPIOB:
        case PORT_PIN_MODE_RCSS_GPIOC:
        case PORT_PIN_MODE_RCSS_GPIOD:
            isDioMode = (boolean)TRUE;
            break;
        default:
            isDioMode = (boolean)FALSE;
            break;
    }
    return isDioMode;
}
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) ||   \ \
    (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) ||    \ \
    (STD_ON == PORT_SET_PIN_DIRECTION_API))          */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_ConfigDioPinDirection(const uint32 gpioPortAddr, uint32 dioChannelId, Port_PinDirectionType direction)
{
    if (direction == PORT_PIN_OUT)
    {
        Port_SetDirection((gpioPORT_t *)gpioPortAddr, dioChannelId, 1);
    }
    else
    {
        Port_SetDirection((gpioPORT_t *)gpioPortAddr, dioChannelId, 0);
    }
}

void Port_ConfigDioPin(const uint32 gpioPortAddr, uint32 dioChannelId, Port_PinDirectionType direction,
                       Port_PinLevelValueType level)
{
    if (direction == PORT_PIN_OUT)
    {
        /* For output pin set output latch level and then enable OE */
        if (level == PORT_PIN_LEVEL_HIGH)
        {
            Port_GPIOSetBit((gpioPORT_t *)gpioPortAddr, dioChannelId, 1);
        }
        else
        {
            Port_GPIOSetBit((gpioPORT_t *)gpioPortAddr, dioChannelId, 0);
        }
    }
    Port_ConfigDioPinDirection(gpioPortAddr, dioChannelId, direction);
}
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) ||          \ \
    (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \           \
    (STD_ON == PORT_SET_PIN_DIRECTION_API)) */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))

void Port_ConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType curMode,
                             Port_PinDirectionType Direction)
{
    uint32 gpioRegAddr;

    if (Port_IsDioMode(curMode) == (boolean)TRUE)
    {
        gpioRegAddr = Port_GetGPIOPortAddr(pinConfig->Port_PinDioRegId);
        Port_ConfigDioPin(gpioRegAddr, pinConfig->Port_PinDioChannelId, Direction, pinConfig->Port_PinLevelValue);
    }

    Port_ConfigurePad(pinConfig, curMode);

    return;
}

void Port_SetPinConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType Mode)
{
    uint32 gpioPortAddr;
    if (Port_IsDioMode(Mode) == (boolean)TRUE)
    {
        gpioPortAddr = Port_GetGPIOPortAddr(pinConfig->Port_PinDioRegId);
        Port_ConfigDioPin(gpioPortAddr, pinConfig->Port_PinDioChannelId, pinConfig->Port_PinDirection,
                          pinConfig->Port_PinLevelValue);
    }
    Port_ConfigurePad(pinConfig, Mode);

    return;
}

#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API))   */

void Port_DioInit(void)
{
    uint32 idx;
    uint32 gpioPortAddr;

    Port_GPIOInit(((gpioBASE_t *)SOC_GIO_REG_BASE));

    /*Initialise the RCSS_GIO module*/
    Port_GPIOInit(((gpioBASE_t *)SOC_RCSSGIO_REG_BASE));

    /** Fill the IntrIdxNum */
    for (idx = 0; idx < PORT_MAX_GPIO_PINS; idx++)
    {
        Port_IntrObj.IntrIdxNum[idx] = 255U;
    }
    Port_IntrObj.MssIntrLevel   = 0U;
    Port_IntrObj.RcssIntrLevel  = 0U;
    Port_IntrObj.MssIntrEnable  = 0U;
    Port_IntrObj.RcssIntrEnable = 0U;

    for (idx = 0U; idx < Port_DrvObj.NumberOfGPIORegs; idx++)
    {
        gpioPortAddr = Port_GetGPIOPortAddr(Port_DrvObj.DioConfig_pt[idx].Port_DioRegId);
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        if (PORT_DIO_INVALID_BASE_ADDR == gpioPortAddr)
        {
            Port_ReportDetError((uint8)PORT_SID_INIT, (uint8)PORT_E_INIT_FAILED);
        }
        else
#endif /*(STD_ON == PORT_DEV_ERROR_DETECT)*/
        {
            Port_GPIOPortInit((gpioPORT_t *)gpioPortAddr);
        }

#if (STD_ON == PORT_ENABLE_INTR_API)
        if ((Port_DrvObj.DioConfig_pt[idx].Port_DioSubsystem == PORT_MSS))
        {
            Port_GPIOIntConfigure(((gpioBASE_t *)SOC_GIO_REG_BASE),
                                  (Port_DioRegConfigType *)&Port_DrvObj.DioConfig_pt[idx]);
        }
        else
        {
            Port_GPIOIntConfigure(((gpioBASE_t *)SOC_RCSSGIO_REG_BASE),
                                  (Port_DioRegConfigType *)&Port_DrvObj.DioConfig_pt[idx]);
        }
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
    }

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
    Port_DioConfigDir();
#endif /*#if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API)) */
}

static uint32 Port_GetMuxMode(Port_PinModeType Port_PinMode, const Port_PinModeConfigType *modeCfg,
                              uint32 Port_NumPortModes)
{
    uint32 muxmode = 0;
    uint32 idx;

    for (idx = 0U; idx < Port_NumPortModes; idx++)
    {
        if (Port_PinMode == modeCfg[idx].mode)
        {
            muxmode = modeCfg[idx].muxmode;
            break;
        }
    }
    if (idx == Port_NumPortModes)
    {
        muxmode = PORT_PAD_REGSETTING_DEFAULT;
    }

    return (muxmode);
}

/*
 * \brief Function to program all the pad. Get called at boot-up time
 *
 *
 * \param[in]   pad_array - List of pad to be configured at boot time
 *
 * \return              none
 *
 */
void Port_MapConfigToReg(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padConfig,
                         P2VAR(Port_PadRegSettingType, AUTO, PORT_APPL_DATA) padRegSetting, Port_PinModeType pinMode)
{
    const uint32 pull_typeselect_map[3] = {PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_DOWN,
                                           PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_UP, PORT_PAD_REGSETTING_DEFAULT};

    const uint32 pull_inhibit_map[3] = {PORT_PAD_REGSETTING_PULLINHIBIT_ENABLE, PORT_PAD_REGSETTING_PULLINHIBIT_DISABLE,
                                        PORT_PAD_REGSETTING_DEFAULT};

    const uint32 slewcontrol_map[3] = {PORT_PAD_REGSETTING_SLEWCONTROL_SLOW_SLEW,
                                       PORT_PAD_REGSETTING_SLEWCONTROL_FAST_SLEW, PORT_PAD_REGSETTING_DEFAULT};

    padRegSetting->muxmode = Port_GetMuxMode(pinMode, padConfig->Port_PinMode, padConfig->Port_NumPortModes);

    padRegSetting->pin_reg_offset = padConfig->Port_RegOffsetAddr;

    padRegSetting->pulludenable       = pull_typeselect_map[padConfig->Port_PullTypeSelect];
    padRegSetting->pullinhibit        = pull_inhibit_map[padConfig->Port_PullInhibitEnable];
    padRegSetting->oe_n_override_ctrl = padConfig->Port_OutputOverride_Ctrl;
    padRegSetting->slewcontrol        = slewcontrol_map[padConfig->Port_SlewControl];
    padRegSetting->ie_n_override_ctrl = padConfig->Port_InputOverride_Ctrl;
}

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_DioConfigDir(void)
{
    const Port_PinConfigType *pinConfig;
    uint32                    idx;
    uint32                    gpioPortAddr;

    for (idx = 0U; idx < Port_DrvObj.NumberOfPortPins; idx++)
    {
        /* Set all registers to configured values */
        pinConfig = &Port_DrvObj.PinConfig_pt[idx];
        /* If direction is not changeable,pin direction must be refreshed*/
        if (Port_IsDioMode(pinConfig->Port_PinInitialMode) == (boolean)TRUE)
        {
            gpioPortAddr = Port_GetGPIOPortAddr(pinConfig->Port_PinDioRegId);

            Port_ConfigDioPin(gpioPortAddr, pinConfig->Port_PinDioChannelId, pinConfig->Port_PinDirection,
                              pinConfig->Port_PinLevelValue);
        }
    }
}

#endif /*#if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API)) */

/*
 * \brief Function to program all the pad. Get called at boot-up time
 *
 *
 * \param[in]   pad_array - List of pad to be configured at boot time
 *
 * \return              none
 *
 */
void Port_ConfigurePad(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padCfg, Port_PinModeType pinMode)
{
    Port_PadRegSettingType padRegConfig;

    Port_MapConfigToReg(padCfg, &padRegConfig, pinMode);
    Port_ConfigurePadCore(SOC_IOMUX_REG_BASE, &padRegConfig);
}

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_HWConfigDioPinDirection(const uint32 gpioPortAddr, const Port_PinConfigType *pinConfig)
{
    Port_ConfigDioPinDirection(gpioPortAddr, pinConfig->Port_PinDioChannelId, pinConfig->Port_PinDirection);
}
#endif /*#if ((STD_ON == PORT_SET_PIN_MODE_API) ||          \ \
        (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \      \
        (STD_ON == PORT_SET_PIN_DIRECTION_API))*/

static void Port_MssPinNotificationISR_internal(Port_LevelTrig TrigValue, uint32 *Gio_Flg_value)
{
    uint32                   idx = 0U, Pin = 0U;
    Port_IsrNotificationType portNotification = (Port_IsrNotificationType)NULL_PTR;

    Pin = (uint32)(PORT_GET_LOWER_INDEX(*Gio_Flg_value));
    idx = (uint32)Port_IntrObj.IntrIdxNum[Pin];

    if ((((Port_IntrObj.MssIntrEnable >> Pin) & 0x1U) != 0U) &&
        (((Port_IntrObj.MssIntrLevel >> Pin) & 0x1U) == (uint32)TrigValue) && (idx != 255U))
    {
        portNotification = Port_DrvObj.DioConfig_pt[idx].Port_DioIntrNotification;

        if (portNotification != NULL_PTR)
        {
            portNotification(Pin, TrigValue);
        }
    }
}

#if (STD_ON == PORT_ENABLE_INTR_API)

/*
 * \brief Interrupt Subroutine for Notification for MSS_GPIO pins
 *
 * TrigValue --> High-Level/Low-Level
 *
 */
void Port_MssPinNotificationISR(Port_LevelTrig TrigValue)
{
    uint32      Gio_Flg_value = 0U;
    uint32      Pin           = 0U;
    gpioBASE_t *gioBaseREG    = (gpioBASE_t *)SOC_GIO_REG_BASE;

    Gio_Flg_value = gioBaseREG->FLG;

    if ((Gio_Flg_value > 0U) && (Gio_Flg_value <= 0xFFFFFFFFU))
    {
        while ((Gio_Flg_value != 0U))
        {
            Port_MssPinNotificationISR_internal(TrigValue, &Gio_Flg_value);

            /** Clear the Intr. flag for particular GPIO pin */
            Pin = (uint32)(PORT_GET_LOWER_INDEX(Gio_Flg_value));
            HW_WR_REG32(&gioBaseREG->FLG, PORT_BIT_CONF(M_ONE, Pin));
            Gio_Flg_value = (Gio_Flg_value & (~(0x1U << Pin)));

            if (Gio_Flg_value == 0U)
            {
                break;
            }
        }
    }
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

static void Port_RcssPinNotificationISR_internal(Port_LevelTrig TrigValue, uint32 *Gio_Flg_value)
{
    uint32                   idx = 0U, Pin = 0U;
    Port_IsrNotificationType portNotification = (Port_IsrNotificationType)NULL_PTR;

    Pin = ((uint32)(PORT_GET_LOWER_INDEX(*Gio_Flg_value)));
    idx = Port_IntrObj.IntrIdxNum[(uint32)Pin + (uint32)32];

    if (((((Port_IntrObj.RcssIntrEnable >> Pin) & 0x1U) != 0U) &&
         (((Port_IntrObj.RcssIntrLevel >> Pin) & 0x1U) == (uint32)TrigValue) && (idx != 255U)))
    {
        portNotification = Port_DrvObj.DioConfig_pt[idx].Port_DioIntrNotification;

        if (portNotification != NULL_PTR)
        {
            portNotification((Pin + (uint32)32), TrigValue);
        }
    }
}
#if (STD_ON == PORT_ENABLE_INTR_API)

/*
 * \brief Interrupt Subroutine for Notification for RCSS_GPIO pins
 *
 * TrigValue --> High-Level/Low-Level
 *
 */

void Port_RcssPinNotificationISR(Port_LevelTrig TrigValue)
{
    uint32      Gio_Flg_value = 0U;
    uint32      Pin           = 0U;
    gpioBASE_t *gioBaseREG    = (gpioBASE_t *)SOC_RCSSGIO_REG_BASE;

    Gio_Flg_value = gioBaseREG->FLG;

    if ((Gio_Flg_value > 0U) && (Gio_Flg_value <= 0xFFFFFFFFU))
    {
        while ((Gio_Flg_value != 0U))
        {
            Port_RcssPinNotificationISR_internal(TrigValue, &Gio_Flg_value);

            /** Clear the Intr. flag for particular GPIO pin */
            Pin = (uint32)(PORT_GET_LOWER_INDEX(Gio_Flg_value));
            HW_WR_REG32(&gioBaseREG->FLG, PORT_BIT_CONF(M_ONE, Pin));
            Gio_Flg_value = (Gio_Flg_value & (~(0x1U << Pin)));

            if (Gio_Flg_value == 0U)
            {
                break;
            }
        }
    }
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#if (STD_ON == PORT_ENABLE_INTR_API)
static boolean Port_EnableIntr_Internal(uint8 idx, Port_PinType *pin, gpioBASE_t **gioBaseREG)
{
    boolean      flg    = FALSE;
    Port_PinType pinNum = *pin;

    if ((Port_DrvObj.DioConfig_pt[idx].Port_DioSubsystem == PORT_MSS))
    {
        Port_GPIOIntConfigure(((gpioBASE_t *)SOC_GIO_REG_BASE),
                              (Port_DioRegConfigType *)&Port_DrvObj.DioConfig_pt[idx]);

        Port_IntrObj.MssIntrEnable      |= (0x1U << pinNum);
        Port_IntrObj.IntrIdxNum[pinNum]  = idx;

        flg         = (boolean)TRUE;
        *gioBaseREG = (gpioBASE_t *)SOC_GIO_REG_BASE;
    }
    else
    {
        Port_GPIOIntConfigure(((gpioBASE_t *)SOC_RCSSGIO_REG_BASE),
                              (Port_DioRegConfigType *)&Port_DrvObj.DioConfig_pt[idx]);

        Port_IntrObj.IntrIdxNum[pinNum]  = idx;
        *pin                             = (*pin) - 32U;
        Port_IntrObj.RcssIntrEnable     |= (0x1U << *pin);

        flg         = (boolean)TRUE;
        *gioBaseREG = (gpioBASE_t *)SOC_RCSSGIO_REG_BASE;
    }

    return flg;
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#if (STD_ON == PORT_ENABLE_INTR_API)
/*
 * \brief Enable Interrupt Functionality
 *
 * Pin --> MSS/RCSS GPIO Pin Numbers (0 to 63)
 *
 */
void Port_EnableIntr(Port_PinType Pin)
{
    uint8        idx            = 0U;
    boolean      Flg            = FALSE;
    uint32       regWriteStatus = 0U;
    gpioBASE_t  *gioBaseREG     = (gpioBASE_t *)NULL_PTR;
    Port_PinType Temp_Pin       = Pin;

    if ((Pin > 63U) && (Port_DrvObj.DioConfig_pt == (Port_DioRegConfigType *)NULL_PTR))
    {
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        Port_ReportDetError(PORT_SID_ENABLE_INTR, PORT_E_PARAM_PIN);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
    else
    {
        /** Set up the Intr Registers **/
        for (idx = 0; idx < Port_DrvObj.NumberOfGPIORegs; idx++)
        {
            if ((Port_DrvObj.DioConfig_pt[idx].Port_DioPinNumber == Temp_Pin))
            {
                Flg = Port_EnableIntr_Internal(idx, &Temp_Pin, &gioBaseREG);
            }

            if (Flg == TRUE)
            {
                break;
            }
        }
    }

    if (Flg == TRUE)
    {
        /** Clear interrupt flag **/
        HW_WR_REG32(&gioBaseREG->FLG, PORT_BIT_CONF(M_ONE, Temp_Pin));

        /** Enable the interrupt **/
        regWriteStatus = regWriteReadback(&gioBaseREG->ENASET, M_THIRTY_ONE, M_ZERO, PORT_BIT_CONF(M_ONE, Temp_Pin));
        if (regWriteStatus != MCAL_REGWR_E_OK)
        {
#ifdef PORT_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }
    }
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#if (STD_ON == PORT_ENABLE_INTR_API)
/*
 * \brief Disable Interrupt Functionality
 *
 * Pin --> MSS/RCSS GPIO Pin Numbers (0 to 63)
 *
 */
void Port_DisableIntr(Port_PinType Pin)
{
    gpioBASE_t  *gioBaseREG = (gpioBASE_t *)NULL_PTR;
    Port_PinType Temp_Pin   = 0;

    /** MSS/RCSS Pin selection */
    if (Pin < 32U)
    {
        Temp_Pin   = Pin;
        gioBaseREG = (gpioBASE_t *)SOC_GIO_REG_BASE;

        Port_IntrObj.MssIntrEnable &= (~(0x1U << Pin));
    }
    else if ((Pin > 31U) && (Pin < 64U))
    {
        Temp_Pin   = Pin - 32U;
        gioBaseREG = (gpioBASE_t *)SOC_RCSSGIO_REG_BASE;

        Port_IntrObj.RcssIntrEnable &= (~(0x1U << Temp_Pin));
    }
    else
    {
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        Port_ReportDetError(PORT_SID_DISABLE_INTR, PORT_E_PARAM_PIN);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    }

    /** Disable the interrupt **/
    HW_WR_REG32(&gioBaseREG->ENACLR, PORT_BIT_CONF(M_ONE, Temp_Pin));

    /** Clear interrupt flag **/
    HW_WR_REG32(&gioBaseREG->FLG, PORT_BIT_CONF(M_ONE, Temp_Pin));
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"
