/* ============================================================================
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
 * ========================================================================== */

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

#define M_ZERO       (0U)
#define M_FIVE       (5U)
#define M_SIX        (6U)
#define M_SEVEN      (7U)
#define M_EIGHT      (8U)
#define M_NINE       (9U)
#define M_TEN        (10U)
#define M_SIXTEEN    (16U)
#define M_SEVENTEEN  (17U)
#define M_EIGHTEEN   (18U)
#define M_NINETEEN   (19U)
#define M_TWENTY     (20U)
#define M_THIRTY     (30U)
#define M_THIRTY_ONE (31U)

/* ========================================================================== */
/*                           Static function declartions                               */
/* ========================================================================== */

static uint32 Port_GetMuxMode(Port_PinModeType Port_PinMode, const Port_PinModeConfigType *modeCfg,
                              uint32 Port_NumPortModes);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
#define PORT_START_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"
static const uint32 Port_GPIOPortAddr[5] = {
    PORT_GPIO_BASE + 0x10U, PORT_GPIO_BASE + 0x38U, PORT_GPIO_BASE + 0x60U,
    PORT_GPIO_BASE + 0x88U, PORT_GPIO_BASE + 0xB0U,
};
static const uint32 pull_typeselect_map[3] = {PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_DOWN,
                                              PORT_PAD_REGSETTING_PULLTYPESELECT_PULL_UP, PORT_PAD_REGSETTING_DEFAULT};

static const uint32 pull_inhibit_map[3] = {PORT_PAD_REGSETTING_PULLINHIBIT_ENABLE,
                                           PORT_PAD_REGSETTING_PULLINHIBIT_DISABLE, PORT_PAD_REGSETTING_DEFAULT};

static const uint32 slewcontrol_map[3]      = {PORT_PAD_REGSETTING_SLEWCONTROL_FAST_SLEW,
                                               PORT_PAD_REGSETTING_SLEWCONTROL_SLOW_SLEW, PORT_PAD_REGSETTING_DEFAULT};
static const uint32 inversion_select_map[3] = {
    PORT_PAD_REGSETTING_NON_INVERSION_EN,
    PORT_PAD_REGSETTING_INVERSION_EN,
    PORT_PAD_REGSETTING_DEFAULT,
};
static const uint32 qualifier_typeselect_map[5] = {
    PORT_PAD_REGSETTING_SYNC_QUAL_EN, PORT_PAD_REGSETTING_THREE_SAMPLE_QUAL_EN, PORT_PAD_REGSETTING_SIX_SAMPLE_QUAL_EN,
    PORT_PAD_REGSETTING_ASYNC_QUAL_EN, PORT_PAD_REGSETTING_DEFAULT};
#define PORT_STOP_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

#define PORT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"
/** \brief PORT Interrupt object */
Port_IntrStatus Port_IntrObj;
#define PORT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/** \brief PORT driver object */
extern VAR(Port_ConfigType, PORT_VAR_ZERO_INIT) Port_DrvObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

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
    pinMuxRegp->IOCFGKICK0 = PORT_UNLOCKPAD_IOCFGKICK0;
    pinMuxRegp->IOCFGKICK1 = PORT_UNLOCKPAD_IOCFGKICK1;
}

/** @fn void Port_LockPadConfig(pinMuxBase_t *pinMuxRegp)
 *   @brief Lock to disable the pinmuxing.
 *
 */

void Port_LockPadConfig(pinMuxBase_t *pinMuxRegp)
{
    /* Disable Pin Muxing */
    /* Value of pinMuxRegp can be pinMuxReg */
    pinMuxRegp->IOCFGKICK1 = PORT_LOCKPADVALUE;
    pinMuxRegp->IOCFGKICK0 = PORT_LOCKPADVALUE;
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
    uint32 reset_regVal_0 = 0xFFFFFFFFU, reset_regVal_2 = PORT_CLEAR_EDGE;
    uint32 reset_regVal_3 = 0U;
    uint32 regWriteStatus = 0U;

    /** - Port direction */
    regWriteStatus = regWriteReadback(&portAddr->DIR, M_THIRTY_ONE, M_ZERO, reset_regVal_0);

    /** - Port output values */
    regWriteStatus |= regWriteReadback(&portAddr->DOUT, M_THIRTY_ONE, M_ZERO, reset_regVal_3);

    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    HW_WR_REG32(&portAddr->CLR_RIS_TRIG, reset_regVal_2);

    HW_WR_REG32(&portAddr->CLR_FAL_TRIG, reset_regVal_2);
}

void Port_GPIOInit(gpioBASE_t *gioBaseREG)
{
    uint32 regVal         = 0U;
    uint32 regWriteStatus = 0U;

    /** bring GPIO module Bank interrupt disabled */
    regWriteStatus = regWriteReadback(&gioBaseREG->BINTEN, M_THIRTY_ONE, M_ZERO, regVal);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
}

void Port_GPIOEdgTrigConfigure(const gpioPORT_t *portAddr, uint32 bit, Port_EdgeTrig TriEdge, boolean TriggerEn)
{
    uint32 regVal = 0U;

    if (TriggerEn == TRUE)
    {
        if (TriEdge == PORT_RISING_EDGE)
        {
            /* Only enable Rising edge detection*/

            regVal |= (uint32)1U << bit;

            M_REG_WRITE32(&portAddr->SET_RIS_TRIG, regVal);

            regVal |= (uint32)1U << bit;

            M_REG_WRITE32(&portAddr->CLR_FAL_TRIG, regVal);
        }

        else if (TriEdge == PORT_FALLING_EDGE)
        {
            /* Only enable Rising edge detection*/

            regVal |= (uint32)1U << bit;

            M_REG_WRITE32(&portAddr->SET_FAL_TRIG, regVal);

            regVal |= (uint32)1U << bit;

            M_REG_WRITE32(&portAddr->CLR_RIS_TRIG, regVal);
        }
        else
        {
            /* Enable both rising and falling edge*/
            regVal = M_REG_READ32(&portAddr->SET_FAL_TRIG);

            regVal |= (uint32)1U << bit;

            M_REG_WRITE32(&portAddr->SET_FAL_TRIG, regVal);

            regVal = M_REG_READ32(&portAddr->SET_RIS_TRIG);

            regVal |= (uint32)1U << bit;

            M_REG_WRITE32(&portAddr->SET_RIS_TRIG, regVal);
        }
    }
    else
    {
        regVal |= (uint32)1U << bit;

        M_REG_WRITE32(&portAddr->CLR_FAL_TRIG, regVal);

        regVal |= (uint32)1U << bit;

        M_REG_WRITE32(&portAddr->CLR_RIS_TRIG, regVal);
    }
}

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
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the output control of the pin */
    if (OUTEN_RETAIN_HW_CTRL != outputCtrl)
    {
        pinMuxBase[(pin / 4U)] &= PIN_OUTEN_MASK;
        regWriteStatus          = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_SEVEN, M_SEVEN, outputCtrl);

        pinMuxBase[(pin / 4U)] |= OUTEN_OVRRIDE_EN;
    }
    else /* OUTEN_RETAIN_HW_CTRL */
    {
        pinMuxBase[(pin / 4U)] &= PIN_OUTEN_OVRRIDE_MASK;
        pinMuxBase[(pin / 4U)] &= PIN_OUTEN_MASK;
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
        pinMuxBase[(pin / 4U)] &= PIN_INPUTEN_MASK;
    }

    if (regWriteStatus != (uint32)E_OK)
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

    pinMuxBase[(pin / 4U)] = (func | ((pinMuxBase[(pin / 4U)] & (uint32)muxmode_mask_value)));

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
    uint32 regWriteStatus = 0;

    /* Setup the configured pull control of the pin */

    pinMuxBase[(pin / 4U)] &= PIN_PULL_SELECT_MASK;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_NINE, M_NINE, pullVal);
    if (regWriteStatus != (uint32)E_OK)
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

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_TEN, M_TEN, slewVal);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    return retVal;
}

/** @fn sint32 Port_ConfigPullInhibitEnable(uint32 *pinMuxBase, uint32 pin,
 *                                            uint32 pullInhibitEnableVal)
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
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    return retVal;
}

sint32 Port_ResetPadConfig(uint32 *pinMuxBase, uint32 pin)
{
    sint32 retVal = 0;
    /*Reset the value */
    uint32 regVal = 0x000005F7U;

    HW_WR_REG32(&(pinMuxBase[(pin / 4U)]), regVal);

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

/** @fn sint32 Port_ConfigInversion(uint32 *pinMuxBase, uint32 pin, uint32 invVal)
 *   @brief Configurations for the inverted version of pad for input chip.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] invVal: pad inversion selection
 *               The parameter \e invVal can be one of the following values:
 *                - \b INVERSION
 *                - \b NON_INVERSION
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigInversion(uint32 *pinMuxBase, uint32 pin, uint32 invVal)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the configured inversion value of the pin */

    pinMuxBase[(pin / 4U)] &= INPUT_INVERSION_MASK;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_TWENTY, M_TWENTY, invVal);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    return retVal;
}

/** @fn sint32 Port_ConfigQualType(uint32 *pinMuxBase, uint32 pin, uint32 qualifierValue)
 *   @brief Configurations for the input qualifier type for pad.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] qualifierValue: input qualifier type
 *               The parameter \e qualifierValue can be one of the following values:
 *                - \b SYNC
 *                - \b THREE_SAMPLE_QUAL
 *                - \b SIX_SAMPLE_QUAL
 *                - \b ASYNC
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigQualType(uint32 *pinMuxBase, uint32 pin, uint32 qualifierValue)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the configured qualifiertype of the pin */

    pinMuxBase[(pin / 4U)] &= QUAL_TYPE_MASK;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_NINETEEN, M_EIGHTEEN, qualifierValue);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    return retVal;
}

/* R5F CPU ownership select for GPIO. 0 : GPO0, 1 :GPO1, 2 : GPO2, 3:GPO3 */
sint32 Port_ConfigGpioSel(uint32 *pinMuxBase, uint32 pin, uint8 gpioCoreSel)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the gpio R5F ownership of the pin */

    pinMuxBase[(pin / 4U)] &= GPIO_SEL_MASK;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_SEVENTEEN, M_SIXTEEN, gpioCoreSel);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    return retVal;
}

/** @fn sint32 Port_ConfigHSmaster(uint32 *pinMuxBase, uint32 pin, uint32 hsmasterValue)
 *   @brief Configurations for the HSMASTER pin incase of true I2C pads.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] hsmasterValue: hsmaster value
 *               The parameter \e hsmasterValue can be one of the following values:
 *                - \b TRUE
 *                - \b FALSE
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigHSmaster(uint32 *pinMuxBase, uint32 pin, uint32 hsmasterValue)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the configured hsmasterValue of the pin */

    pinMuxBase[(pin / 4U)] &= HSMASTER_MASK;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_THIRTY_ONE, M_THIRTY_ONE, hsmasterValue);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

/** @fn sint32 Port_ConfigHSmode(uint32 *pinMuxBase, uint32 pin, uint32 hsmodeValue)
 *   @brief Configurations for the HSMODE pin incase of true I2C pads.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] hsmodeValue: hsmode value
 *               The parameter \e hsmodeValue can be one of the following values:
 *                - \b TRUE
 *                - \b FALSE
 *
 *    @return Value < 0 - in case of error
 *            Value = 0 - success
 */
sint32 Port_ConfigHSmode(uint32 *pinMuxBase, uint32 pin, uint32 hsmodeValue)
{
    sint32 retVal         = 0;
    uint32 regWriteStatus = 0U;

    /* Setup the configured hsmodeValue of the pin */

    pinMuxBase[(pin / 4U)] &= HSMODE_MASK;

    regWriteStatus = regWriteReadback(&(pinMuxBase[(pin / 4U)]), M_THIRTY, M_THIRTY, hsmodeValue);
    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return retVal;
}

void Port_ConfigurePadCore(uint32 baseAdd, CONSTP2CONST(Port_PadRegSettingType, AUTO, PORT_APPL_DATA) padRegSetting)
{
    Port_UnlockPadConfig(((pinMuxBase_t *)baseAdd));

    Port_ResetPadConfig((uint32 *)baseAdd, padRegSetting->pin_reg_offset);

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

    if (padRegSetting->inversion != PORT_PAD_REGSETTING_DEFAULT)
    {
        (void)Port_ConfigInversion((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->inversion);
    }

    if (padRegSetting->qualifiertype != PORT_PAD_REGSETTING_DEFAULT)
    {
        (void)Port_ConfigQualType((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->qualifiertype);
    }

    (void)Port_ConfigGpioSel((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->gpiocoreowner);
    (void)Port_ConfigHSmaster((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->HSmaster);

    (void)Port_ConfigHSmode((uint32 *)baseAdd, padRegSetting->pin_reg_offset, padRegSetting->HSmode);

    Port_LockPadConfig(((pinMuxBase_t *)baseAdd));
}

uint32 Port_ReadMuxMode(uint32 pin_reg_offset)
{
    uint32 muxmode_val;
    uint32 pin_reg_addr;
    uint32 baseAdd = SOC_IOMUX_REG_BASE;

    Port_UnlockPadConfig((pinMuxBase_t *)baseAdd);

    pin_reg_addr = baseAdd + pin_reg_offset;

    muxmode_val = M_REG_READ32(pin_reg_addr);

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
    uint32 pinMask        = (uint32)1U << bit;
    uint32 oeRegVal       = 0U;
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

    if (regWriteStatus != (uint32)E_OK)
    {
#ifdef PORT_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)PORT_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
}

#if (STD_ON == PORT_DEV_ERROR_DETECT)
uint32 Port_GetDioRegId(Port_PinModeType mode)
{
    uint32 dioRegId = 0U;

    switch (mode)
    {
        case PORT_PIN_MODE_GPIOAB:
            dioRegId = 0U;
            break;
        case PORT_PIN_MODE_GPIOCD:
            dioRegId = 1U;
            break;
        case PORT_PIN_MODE_GPIOEF:
            dioRegId = 2U;
            break;
        case PORT_PIN_MODE_GPIOGH:
            dioRegId = 3U;
            break;

        case PORT_PIN_MODE_GPIOI:
            dioRegId = 4U;
            break;
        default:
            /*Do nothing*/
            break;
    }

    return dioRegId;
}

#endif /*PORT_DEV_ERROR_DETECT */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
boolean Port_IsDioMode(Port_PinModeType mode)
{
    boolean isDioMode;

    switch (mode)
    {
        case PORT_PIN_MODE_GPIOAB:
        case PORT_PIN_MODE_GPIOCD:
        case PORT_PIN_MODE_GPIOEF:
        case PORT_PIN_MODE_GPIOGH:
        case PORT_PIN_MODE_GPIOI:

            isDioMode = (boolean)TRUE;
            break;
        default:
            isDioMode = (boolean)FALSE;
            break;
    }
    return isDioMode;
}

#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) ||     \ \
         (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \ \
         (STD_ON == PORT_SET_PIN_DIRECTION_API))        */

static uint32 Port_GetMuxMode(Port_PinModeType Port_PinMode, const Port_PinModeConfigType *modeCfg,
                              uint32 Port_NumPortModes)
{
    uint32 muxmode = 0U;
    uint32 idx     = 0U;

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
    padRegSetting->muxmode = Port_GetMuxMode(pinMode, padConfig->Port_PinMode, padConfig->Port_NumPortModes);

    padRegSetting->pin_reg_offset = padConfig->Port_RegOffsetAddr;

    padRegSetting->pulludenable       = pull_typeselect_map[padConfig->Port_PullTypeSelect];
    padRegSetting->pullinhibit        = pull_inhibit_map[padConfig->Port_PullInhibitEnable];
    padRegSetting->oe_n_override_ctrl = padConfig->Port_OutputOverride_Ctrl;
    padRegSetting->slewcontrol        = slewcontrol_map[padConfig->Port_SlewControl];
    padRegSetting->ie_n_override_ctrl = padConfig->Port_InputOverride_Ctrl;

    padRegSetting->HSmaster      = padConfig->Port_PinHSmasterEnable;
    padRegSetting->HSmode        = padConfig->Port_PinHSmodeEnable;
    padRegSetting->inversion     = inversion_select_map[padConfig->Port_InversionSelect];
    padRegSetting->qualifiertype = qualifier_typeselect_map[padConfig->Port_QualifierTypeSelect];
    padRegSetting->gpiocoreowner = padConfig->Port_GpioOwnerCore;
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

void Port_ConfigurePad(P2CONST(Port_PinConfigType, AUTO, PORT_APPL_DATA) padCfg, Port_PinModeType pinMode)
{
    Port_PadRegSettingType padRegConfig;

    Port_MapConfigToReg(padCfg, &padRegConfig, pinMode);
    Port_ConfigurePadCore(SOC_IOMUX_REG_BASE, &padRegConfig);
}

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))

void Port_ConfigDioPinDirection(const uint32 gpioPortAddr, uint32 dioChannelId, Port_PinDirectionType direction)
{
    if (direction == PORT_PIN_OUT)
    {
        Port_SetDirection((gpioPORT_t *)gpioPortAddr, dioChannelId, 0);
    }
    else
    {
        Port_SetDirection((gpioPORT_t *)gpioPortAddr, dioChannelId, 1);
    }
}
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) ||      \ \
          (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API))        */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
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
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API))   */

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_ConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType curMode,
                             Port_PinDirectionType Direction)
{
    uint32 gpioRegAddr = 0U;

    if (Port_IsDioMode(curMode) == (boolean)TRUE)
    {
        gpioRegAddr = Port_GetGPIOPortAddr(pinConfig->Port_PinDioRegId);
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        if (PORT_DIO_INVALID_BASE_ADDR == gpioRegAddr)
        {
            Port_ReportDetError((uint8)PORT_SID_SET_PIN_DIR, (uint8)PORT_E_INVALID_GPIO_PORT_ADDRESS);
        }
        else
#endif /*(STD_ON == PORT_DEV_ERROR_DETECT)*/
        {
            Port_ConfigDioPin(gpioRegAddr, pinConfig->Port_PinDioChannelId, Direction, pinConfig->Port_PinLevelValue);
        }
    }

    Port_ConfigurePad(pinConfig, curMode);

    return;
}

void Port_DioConfigDir(void)
{
    const Port_PinConfigType *pinConfig;
    uint32                    idx          = 0U;
    uint32                    gpioPortAddr = 0U;

    for (idx = 0U; idx < Port_DrvObj.NumberOfPortPins; idx++)
    {
        /* Set all registers to configured values */
        pinConfig = &Port_DrvObj.PinConfig_pt[idx];
        /* If direction is not changeable,pin direction must be refreshed*/
        if (Port_IsDioMode(pinConfig->Port_PinInitialMode) == (boolean)TRUE)
        {
            gpioPortAddr = Port_GetGPIOPortAddr(pinConfig->Port_PinDioRegId);
#if (STD_ON == PORT_DEV_ERROR_DETECT)
            if (PORT_DIO_INVALID_BASE_ADDR == gpioPortAddr)
            {
                Port_ReportDetError((uint8)PORT_SID_INIT, (uint8)PORT_E_INVALID_GPIO_PORT_ADDRESS);
            }
            else
#endif /*(STD_ON == PORT_DEV_ERROR_DETECT)*/
            {
                Port_ConfigDioPin(gpioPortAddr, pinConfig->Port_PinDioChannelId, pinConfig->Port_PinDirection,
                                  pinConfig->Port_PinLevelValue);
            }
        }
    }
}
#endif /* #if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API))   */

void Port_DioInit(void)
{
    uint32 idx = 0U, pin = 0U;
    uint32 gpioPortAddr = 0U, portBankRegID = 0U;

#if (STD_ON == PORT_ENABLE_INTR_API)
    uint32 portBankIdx = 0U;
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

    Port_GPIOInit(((gpioBASE_t *)PORT_GPIO_BASE));

    /** Fill the IntrIdxNum */
    for (idx = 0; idx < PORT_INTR_BUF_SIZE; idx++)
    {
        Port_IntrObj.IntrIdxNum[idx] = PORT_INTR_ERROR_ID;
    }

    for (idx = 0U; idx < Port_DrvObj.NumberOfGPIORegs; idx++)
    {
        pin           = Port_DrvObj.DioConfig_pt[idx].Port_DioPinNumber;
        portBankRegID = PORT_GET_REG_INDEX(pin);

        gpioPortAddr = Port_GetGPIOPortAddr(portBankRegID);
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        if ((PORT_DIO_INVALID_BASE_ADDR == gpioPortAddr) || (pin >= PORT_MAX_GPIO_PINS))
        {
            Port_ReportDetError((uint8)PORT_SID_INIT, (uint8)PORT_E_INVALID_GPIO_PORT_ADDRESS);
        }
        else
#endif /*(STD_ON == PORT_DEV_ERROR_DETECT)*/
        {
            Port_GPIOPortInit((gpioPORT_t *)gpioPortAddr);
        }

#if (STD_ON == PORT_ENABLE_INTR_API)
        Port_IntrObj.IntrIdxNum[pin] = (uint8)idx;
        if (Port_DrvObj.DioConfig_pt[idx].Port_PinSelectInterruptType == PORT_BANK_INTR)
        {
            portBankIdx                          = (PORT_GPIO_BANK_SUFFIX + (PORT_GET_BANK_INDEX(pin)));
            Port_IntrObj.IntrIdxNum[portBankIdx] = (uint8)idx;
        }
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */
    }

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_SET_PIN_DIRECTION_API))
    Port_DioConfigDir();
#endif /*#if ((STD_ON == PORT_SET_PIN_MODE_API) || \ \
          (STD_ON == PORT_SET_PIN_DIRECTION_API)) */
}
#if (STD_ON == PORT_SET_PIN_MODE_API)
void Port_SetPinConfigPadAndDioPin(const Port_PinConfigType *pinConfig, Port_PinModeType Mode)
{
    uint32 gpioPortAddr = 0U;
    if (Port_IsDioMode(Mode) == (boolean)TRUE)
    {
        gpioPortAddr = Port_GetGPIOPortAddr(pinConfig->Port_PinDioRegId);
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        if (PORT_DIO_INVALID_BASE_ADDR == gpioPortAddr)
        {
            Port_ReportDetError((uint8)PORT_SID_SET_PIN_MODE, (uint8)PORT_E_INVALID_GPIO_PORT_ADDRESS);
        }
        else
#endif /*(STD_ON == PORT_DEV_ERROR_DETECT)*/
        {
            Port_ConfigDioPin(gpioPortAddr, pinConfig->Port_PinDioChannelId, pinConfig->Port_PinDirection,
                              pinConfig->Port_PinLevelValue);
        }
    }
    Port_ConfigurePad(pinConfig, Mode);

    return;
}
#endif /*#if (STD_ON == PORT_SET_PIN_MODE_API)*/

#if ((STD_ON == PORT_SET_PIN_MODE_API) || (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \
     (STD_ON == PORT_SET_PIN_DIRECTION_API))
void Port_HWConfigDioPinDirection(const uint32 gpioPortAddr, const Port_PinConfigType *pinConfig)
{
    Port_ConfigDioPinDirection(gpioPortAddr, pinConfig->Port_PinDioChannelId, pinConfig->Port_PinDirection);
}
#endif /*#if ((STD_ON == PORT_SET_PIN_MODE_API) ||          \ \
        (STD_ON == PORT_REFRESH_PORT_DIRECTION_API) || \      \
        (STD_ON == PORT_SET_PIN_DIRECTION_API))*/

#if (STD_ON == PORT_ENABLE_INTR_API)
/*
 * \brief - Enable Interrupt Functionality
 *
 * Pin --> GPIO Pin Numbers
 *
 */
void Port_EnableIntr(Port_PinType Pin)
{
    uint32      portBankRegID = 0U, portBankBitPos = 0U, portBankIdx = 0U, idx = 0U;
    gpioBASE_t *gioBaseREG  = (gpioBASE_t *)NULL_PTR;
    gpioPORT_t *gioPortAddr = (gpioPORT_t *)NULL_PTR;

    if (Pin >= PORT_MAX_GPIO_PINS)
    {
        /** Invalid channel Number **/
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        Port_ReportDetError(PORT_SID_ENABLE_INTR, PORT_E_PARAM_PIN);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
    else
    {
        if (Port_IntrObj.IntrIdxNum[Pin] != PORT_INTR_ERROR_ID)
        {
            idx        = Port_IntrObj.IntrIdxNum[Pin];
            gioBaseREG = (gpioBASE_t *)PORT_GPIO_BASE;

            portBankIdx    = (uint32)(PORT_GET_BANK_INDEX((uint32)Pin));
            portBankRegID  = (uint32)PORT_GET_REG_INDEX((uint32)Pin);
            portBankBitPos = PORT_GET_REG_BIT_POS(Pin, portBankRegID);
            gioPortAddr    = (gpioPORT_t *)Port_GPIOPortAddr[portBankRegID];

            /** Set up the Intr Registers **/
            Port_GPIOEdgTrigConfigure(gioPortAddr, portBankBitPos,
                                      Port_DrvObj.DioConfig_pt[idx].Port_PinSelectEdgeTrigger, TRUE);

            /** Enable the Interrupt **/
            gioBaseREG->BINTEN |= (uint32)((uint32)0x01U << (uint32)portBankIdx);
        }
    }
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#if (STD_ON == PORT_ENABLE_INTR_API)
/*
 * \brief - Disable Interrupt Functionality
 *
 * Pin --> GPIO Pin Numbers
 *
 */
void Port_DisableIntr(Port_PinType Pin)
{
    uint32      portBankRegID = 0U, portBankBitPos = 0U, portBankIdx = 0U, idx = 0U;
    gpioBASE_t *gioBaseREG  = (gpioBASE_t *)NULL_PTR;
    gpioPORT_t *gioPortAddr = (gpioPORT_t *)NULL_PTR;

    if (Pin >= PORT_MAX_GPIO_PINS)
    {
        /** Invalid channel Number **/
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        Port_ReportDetError(PORT_SID_DISABLE_INTR, PORT_E_PARAM_PIN);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
    else
    {
        if (Port_IntrObj.IntrIdxNum[Pin] != PORT_INTR_ERROR_ID)
        {
            idx        = (Port_IntrObj.IntrIdxNum[Pin]);
            gioBaseREG = (gpioBASE_t *)PORT_GPIO_BASE;

            portBankIdx    = (uint32)(PORT_GET_BANK_INDEX((uint32)Pin));
            portBankRegID  = (uint32)(PORT_GET_REG_INDEX((uint32)Pin));
            portBankBitPos = (uint32)(PORT_GET_REG_BIT_POS(Pin, portBankRegID));
            gioPortAddr    = (gpioPORT_t *)Port_GPIOPortAddr[portBankRegID];

            /** Set up the Intr Registers **/
            Port_GPIOEdgTrigConfigure(gioPortAddr, portBankBitPos,
                                      Port_DrvObj.DioConfig_pt[idx].Port_PinSelectEdgeTrigger, FALSE);

            if (Port_DrvObj.DioConfig_pt[idx].Port_PinSelectInterruptType == PORT_BANK_INTR)
            {
                /** Disable the Interrupt **/
                gioBaseREG->BINTEN &= (~(0x1U << portBankIdx));
            }
        }
    }
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#if (STD_ON == PORT_GET_INTR_ST_API)
/*
 * \brief Read bank Interrupt Status Register
 *
 * Input : bankIdx --> GPIO bank Number
 *
 * Return value : uint32 --> INTSTAT Register Value
 *
 */
uint32 Port_GetStatus(Port_PinType bankIdx)
{
    uint32      portBankRegID = 0U, regValue = 0U;
    uint16      pin         = 0U;
    gpioPORT_t *gioPortAddr = (gpioPORT_t *)NULL_PTR;

    if (bankIdx >= PORT_MAX_GPIO_BANKS)
    {
        /** Invalid bank ID */
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        Port_ReportDetError(PORT_SID_GET_INTR_ST, PORT_E_PARAM_PIN);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
    else
    {
        /** Get Pin Number by bank index */
        pin           = (bankIdx * PORT_CHANNELS_PER_BANK);
        portBankRegID = PORT_GET_REG_INDEX((uint32)pin);
        gioPortAddr   = (gpioPORT_t *)Port_GPIOPortAddr[portBankRegID];

        regValue = gioPortAddr->INTSTAT;
    }

    return regValue;
}
#endif /* #if (STD_ON == PORT_GET_INTR_ST_API) */
/*
 * \brief Clear bank Interrupt Status Register
 *
 * Input : bankIdx --> GPIO bank Number
 *         maskValue --> bit mask value
 *
 */
void Port_ClearStatus(Port_PinType bankIdx, uint32 maskValue)
{
    uint32      portBankRegID = 0U, pin = 0U;
    uint32      Internal_Mask = maskValue;
    gpioPORT_t *gioPortAddr   = (gpioPORT_t *)NULL_PTR;

    if (bankIdx >= PORT_MAX_GPIO_BANKS)
    {
        /** Invalid bank ID */
#if (STD_ON == PORT_DEV_ERROR_DETECT)
        Port_ReportDetError(PORT_SID_CLR_INTR_ST, PORT_E_PARAM_PIN);
#endif /* #if (STD_ON == PORT_DEV_ERROR_DETECT) */
    }
    else
    {
        /** Get Pin Number by bank index */
        pin           = (uint16)(bankIdx * PORT_CHANNELS_PER_BANK);
        portBankRegID = PORT_GET_REG_INDEX(pin);
        gioPortAddr   = (gpioPORT_t *)Port_GPIOPortAddr[portBankRegID];

        /* check for odd bank number */
        if ((bankIdx & 0x01U) == TRUE)
        {
            Internal_Mask = (maskValue << PORT_CHANNELS_PER_BANK);
        }

        HW_WR_REG32(&gioPortAddr->INTSTAT, Internal_Mask);
    }
}

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#define PORT_START_SEC_ISR_CODE
#include "Port_MemMap.h"

#if (STD_ON == PORT_ENABLE_INTR_API)
/*
 * \brief - Interrupt Subroutine for Notification for GPIO pins
 *
 *  portXbaroutPinInfo --> GPIO Pin / GPIO Bank Information
 *
 */
void Port_GpioPinNotificationISR(uint32 portXbaroutPinInfo)
{
    uint32        idx = PORT_INTR_ERROR_ID, portBankBitPos = PORT_INTR_ERROR_ID;
    uint32        gpioBankNum = PORT_INTR_ERROR_ID, gpioBankChNum = PORT_INTR_ERROR_ID;
    Port_EdgeTrig trigValue     = PORT_RISING_EDGE;
    uint32        portBankRegID = PORT_INTR_ERROR_ID;
    uint32        maskValue     = PORT_BANK_MASK;

    Port_IsrNotificationType portNotification = (Port_IsrNotificationType)NULL_PTR;
    gpioPORT_t              *gioPortAddr      = (gpioPORT_t *)NULL_PTR;

    if (portXbaroutPinInfo != PORT_INTR_ERROR_ID)
    {
        idx = Port_IntrObj.IntrIdxNum[portXbaroutPinInfo];

        if ((portXbaroutPinInfo >= ((uint32)PORT_GPIO_BANK_SUFFIX + (uint32)PORT_GPIO_BANK_0)) &&
            ((uint32)portXbaroutPinInfo <= ((uint32)PORT_GPIO_BANK_SUFFIX + (uint32)PORT_GPIO_BANK_8)))
        {
            gpioBankNum = (portXbaroutPinInfo - PORT_GPIO_BANK_SUFFIX);
        }
        else
        {
            gpioBankChNum = portXbaroutPinInfo;
            gpioBankNum   = PORT_GET_BANK_INDEX(gpioBankChNum);
        }

        if (Port_IntrObj.IntrIdxNum[portXbaroutPinInfo] != PORT_INTR_ERROR_ID)
        {
            trigValue        = Port_DrvObj.DioConfig_pt[idx].Port_PinSelectEdgeTrigger;
            portNotification = (Port_IsrNotificationType)Port_DrvObj.DioConfig_pt[idx].Port_DioInterruptNotification;

            /* Call Back function */
            if (portNotification != NULL_PTR)
            {
                portNotification((uint8)gpioBankNum, (uint8)gpioBankChNum, (Port_EdgeTrig)trigValue);
            }

            /* Clear interrupt status */
            if ((portXbaroutPinInfo >= ((uint32)PORT_GPIO_BANK_SUFFIX + (uint32)PORT_GPIO_BANK_0)) &&
                (portXbaroutPinInfo <= ((uint32)PORT_GPIO_BANK_SUFFIX + (uint32)PORT_GPIO_BANK_8)))
            {
                /* clear bank */
                Port_ClearStatus((Port_PinType)gpioBankNum, maskValue);
            }
            else
            {
                /* clear channel  */
                gpioBankNum    = PORT_GET_BANK_INDEX(gpioBankChNum);
                portBankRegID  = PORT_GET_REG_INDEX(gpioBankChNum);
                portBankBitPos = PORT_GET_REG_BIT_POS(gpioBankChNum, portBankRegID);

                gioPortAddr = (gpioPORT_t *)Port_GPIOPortAddr[portBankRegID];

                maskValue = (uint32)((uint32)0x1U << (uint32)portBankBitPos);

                HW_WR_REG32(&gioPortAddr->INTSTAT, maskValue);
            }
        }
    }
}
#endif /** #if (STD_ON == PORT_ENABLE_INTR_API) */

#define PORT_STOP_SEC_ISR_CODE
#include "Port_MemMap.h"
