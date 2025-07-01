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
 *  \file     Dio_Priv.c
 *
 */

#define DIO_PRIV_SOURCE (1)

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "hal_stdtypes.h"
#include "Dio.h"
#include "Dio_Priv.h"
#include "hw_ctrl_core.h"
#include "sys_common.h"
#include "SchM_Dio.h"
#include "soc.h"
#include "hw_types.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DIO_NUM_GPIO_REGS (8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void Dio_PinWrite(uint32 baseAdd, uint32 pinNumber, Dio_LevelType level);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define DIO_START_SEC_CONST_32
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
#include "Dio_MemMap.h"

/*LDRA_INSPECTED 25 D : MISRAC_2012_R.8.9
 * "Reason - Need to place the variable global since #pragma to map to a
 * particular section doesn't work for variables inside a funtion." */

static CONST(uint32, DIO_CONST) Dio_GPIOPortAddr[DIO_NUM_GPIO_REGS] = {
    SOC_GIO_PORTA_BASE, SOC_GIO_PORTB_BASE, SOC_GIO_PORTC_BASE,
    SOC_GIO_PORTD_BASE,
#if defined(AM273X_PLATFORM) || defined(AM2732S_PLATFORM)
    SOC_GIO_PORTE_BASE, SOC_GIO_PORTF_BASE, SOC_GIO_PORTG_BASE,
    SOC_GIO_PORTH_BASE
#endif
};

#define DIO_STOP_SEC_CONST_32
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Dio_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define DIO_START_SEC_CODE
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Dio_MemMap.h"

uint32 Dio_GetGPIOPortAddr(uint32 regNum)
{
    uint32 retVal;

    retVal = Dio_GPIOPortAddr[regNum];

    return (retVal);
}

/** @fn uint32 Dio_GpioGetLogicLvl(gioPORT_t *port, uint32 bit)
 *   @brief Read Bit
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *   @param[in] bit number 0-7 that specifies the bit to be written to.
 *              - 0: LSB
 *              - 7: MSB
 *
 *   Reads a the current value from the specified pin of the given GIO port
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 Dio_GpioGetLogicLvl(const gpioPORT_t *port, uint32 bit)
{
    return (port->DIN >> bit) & 1U;
}

/** @fn uint32 Dio_GpioGetDirection(gioPORT_t *port, uint32 bit)
 *   @brief Read Bit
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *   @param[in] bit number 0-7 that specifies the bit to be written to.
 *              - 0: LSB
 *              - 7: MSB
 *
 *   Reads a the current value from the specified pin of the given GIO port
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 Dio_GpioGetDirection(const gpioPORT_t *port, uint32 bit)
{
    uint32 dataIn = port->DIR;

    return (dataIn >> bit) & 1U;
}

/** @fn uint32 Dio_GpioSetBit(gioPORT_t *port, uint32 bit, uint32 value)
 *   @brief Read Bit
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *   @param[in] bit number 0-7 that specifies the bit to be written to.
 *              - 0: LSB
 *              - 7: MSB
 *
 *   writes the current value from the specified pin of the given GIO port
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void Dio_GpioSetBit(gpioPORT_t *port, uint32 bit, uint32 value)
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

/** @fn uint32 Dio_GpioPortWrite(gioPORT_t *port, uint32 bit, uint32 value)
 *   @brief Read Bit
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *   @param[in] bit number 0-7 that specifies the bit to be written to.
 *              - 0: LSB
 *              - 7: MSB
 *
 *   Reads a the current value from the specified pin of the given GIO port
 */

uint32 Dio_GpioPortWrite(const gpioPORT_t *port, uint32 setBits)
{
    uint32 regWrFailStatus  = 0U;
    regWrFailStatus        |= regWriteReadback(&port->DOUT, M_SEVEN, M_ZERO, setBits);
    if (regWrFailStatus != MCAL_REGWR_E_OK)
    {
#ifdef DIO_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)DIO_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }

    return (regWrFailStatus);
}

/** @fn uint32 Dio_GpioGetPort(gioPORT_t *port)
 *   @brief Read Port Value
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *
 *   Reads a the current value of a given GIO port
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
uint32 Dio_GpioGetPort(const gpioPORT_t *port)
{
    return (port->DIN);
}

/** @fn void Dio_GpioBitToggle(gioPORT_t *port, uint32 bit)
 *   @brief Write Bit
 *   @param[in] port pointer to GIO port:
 *              - gioPORTA: PortA pointer
 *              - gioPORTB: PortB pointer
 *              - gioPORTC: PortC pointer
 *              - gioPORTD: PortD pointer
 *   @param[in] bit number 0-7 that specifies the bit to be written to.
 *              - 0: LSB
 *              - 7: MSB
 *
 *   Toggle a value to the specified pin of the given GIO port
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void Dio_GpioBitToggle(gpioPORT_t *port, uint32 bit)
{
    uint32 dataIn = port->DIN;

    if ((dataIn & (uint32)((uint32)1U << bit)) != 0U)
    {
        port->DCLR = (uint32)1U << bit;
    }
    else
    {
        port->DSET = (uint32)1U << bit;
    }
}

Dio_LevelType Dio_PinRead(uint32 baseAddr, uint32 pinNumber)
{
    uint32        logiclvl;
    Dio_LevelType lvlret;

    /* Requirements : SWS_Dio_00051, SWS_Dio_00089 */
    /* Design : AUTORADAR_MCAL-568, AUTORADAR_MCAL-582 */
    /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
     * "Reason - Cast for register address " */
    logiclvl = Dio_GpioGetLogicLvl((const gpioPORT_t *)baseAddr, pinNumber);

    /* Requirements : SWS_Dio_00023 */
    /* Design : AUTORADAR_MCAL-556 */
    if (logiclvl != 0U)
    {
        lvlret = (Dio_LevelType)STD_HIGH;
    }
    else
    {
        lvlret = (Dio_LevelType)STD_LOW;
    }

    return (lvlret);
}

/**
 * @fn
 */

void Dio_GetGPIORegInfo(Dio_ChannelType channelId, uint32 *baseAddr, uint32 *pinNumber)
{
    uint8 gpioRegNum;
    uint8 gpioPinNum;

    gpioRegNum = (uint8)(channelId / DIO_PORT_WIDTH);
    gpioPinNum = (uint8)(channelId % DIO_PORT_WIDTH);
    *baseAddr  = (uint32)Dio_GetGPIOPortAddr(gpioRegNum);
    *pinNumber = gpioPinNum;
}

void Dio_ChkDirWritePin(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    uint32            baseAddr;
    uint32            pinNumber;
    Dio_DirectionType gioDirection;

    Dio_GetGPIORegInfo(ChannelId, &baseAddr, &pinNumber);
    /* Requirements : SWS_Dio_00005,SWS_Dio_00060 */
    SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_0();

    /* Requirements : SWS_Dio_00128, SWS_Dio_00064, SWS_Dio_00070 */
    /* Requirements : SWS_Dio_00028 */
    DIO_GioGetDirection(ChannelId, &gioDirection);
    if (DIO_DIR_OUTPUT == gioDirection)
    {
        /* Write to Channel if direction is OUTPUT. */
        Dio_PinWrite(baseAddr, pinNumber, Level);
    }
    /* Requirements : SWS_Dio_00029, SWS_Dio_00079 */
    /* else case for input channel : Do Nothing */
    /* Requirements : SWS_Dio_00005 */
    SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_0();

    return;
}

static void Dio_PinWrite(uint32 baseAdd, uint32 pinNumber, Dio_LevelType level)
{
    /* Requirements : SWS_Dio_00089, SWS_Dio_00006 */
    /* Design : AUTORADAR_MCAL-582, AUTORADAR_MCAL-543 */
    if (((Dio_LevelType)STD_HIGH) == level)
    {
        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address" */
        Dio_GpioSetBit((gpioPORT_t *)baseAdd, pinNumber, STD_HIGH);
    }
    else
    {
        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address" */
        Dio_GpioSetBit((gpioPORT_t *)baseAdd, pinNumber, STD_LOW);
    }

    return;
}

#if defined(DIO_WRITE_CHANNEL_EVENT_ID) && (STD_ON == DIO_SUPPORT_GIO)
Dio_StatusType Dio_CheckIO(Dio_ChannelType channelId, Dio_LevelType level)
{
    Dio_LevelType  newLevel;
    Dio_StatusType Status;

    Status = (Std_ReturnType)E_OK;

    newLevel = Dio_ReadChannel(channelId);
    if (level != newLevel)
    {
        Status = (Std_ReturnType)E_NOT_OK;
    }

    return (Status);
}
#endif

#if (STD_ON == DIO_SUPPORT_GIO)
void DIO_GioGetDirection(Dio_ChannelType channelId, Dio_DirectionType *gioDirection)
{
    uint32 baseAddr;
    uint32 pinNumber;
    uint32 regval;

    Dio_GetGPIORegInfo(channelId, &baseAddr, &pinNumber);
    /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
     * "Reason - Cast for register address " */
    regval = Dio_GpioGetDirection((const gpioPORT_t *)baseAddr, pinNumber);
    if ((uint32)1U != regval)
    {
        *gioDirection = DIO_DIR_INPUT;
    }
    else
    {
        *gioDirection = DIO_DIR_OUTPUT;
    }
}

void Dio_GioReadPort(uint32 portId, uint32 *portVal)
{
    uint32 baseAddr;

    baseAddr = Dio_GetGPIOPortAddr((uint8)portId);
    /* Requirements : SWS_Dio_00013 */
    /* Design : AUTORADAR_MCAL-548 */
    /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
     * "Reason - Cast for register address " */
    *portVal = (uint32)Dio_GpioGetPort((const gpioPORT_t *)baseAddr);
}

/* Requirements : SWS_Dio_00105 */
/* Design : AUTORADAR_MCAL-590 */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA not able to analyse the code properly " */
void Dio_GioWritePort(uint32 portId, uint32 Level)
{
    uint32 baseAddr;
    baseAddr = Dio_GetGPIOPortAddr((uint8)portId);
    /* Requirements : SWS_Dio_00004, SWS_Dio_00035, SWS_Dio_00108  SWS_Dio_00007*/
    /* Design : AUTORADAR_MCAL-541, AUTORADAR_MCAL-564, AUTORADAR_MCAL-591  AUTORADAR_MCAL-544*/
    /* Requirements : SWS_Dio_00040 */
    /* Design : AUTORADAR_MCAL-567 */
    /* Requirements : SWS_Dio_00024, SWS_Dio_00108,  SWS_Dio_00007*/
    /* Design : AUTORADAR_MCAL-557, AUTORADAR_MCAL-591,  AUTORADAR_MCAL-544*/
    /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
     * "Reason - Cast for register address " */
    Dio_GpioPortWrite((gpioPORT_t *)baseAddr, Level);
}

#if (STD_ON == DIO_DEV_ERROR_DETECT)
Std_ReturnType Dio_CheckChannelValidity(Dio_ChannelType channelId)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    uint8          gpioRegNum, gpioPinNum;
    boolean        isChannelEnabled = (boolean)FALSE;

    gpioRegNum = (uint8)(channelId / DIO_PORT_WIDTH);
    gpioPinNum = (uint8)(channelId % DIO_PORT_WIDTH);
    if (gpioRegNum < DIO_MAX_NO_OF_PORTS)
    {
        if (0U != ((uint8)(gDioConfigValidChannelMask[gpioRegNum]) & (1U << gpioPinNum)))
        {
            isChannelEnabled = (boolean)TRUE;
        }

        if ((((boolean)TRUE) == isChannelEnabled))
        {
            retVal = (Std_ReturnType)E_OK;
        }
    }
    return (retVal);
}
#endif

#endif

/*Checking the status of base address of MSS and RCSS GIO register: refer trm*/
#if (STD_ON == DIO_REGISTER_READBACK_API)
void Dio_HwRegisterReadback(Dio_RegisterReadbackType *RegRbPtr)
{
    (void)memset(RegRbPtr, 0, sizeof(Dio_RegisterReadbackType));

    uint32 *gioMSSBaseREGt  = (uint32 *)SOC_GIO_REG_BASE;
    uint32 *gioRCSSBaseREGt = (uint32 *)SOC_RCSSGIO_REG_BASE;

    RegRbPtr->mssBaseAddr  = HW_RD_REG32(&gioMSSBaseREGt);
    RegRbPtr->rcssBaseAddr = HW_RD_REG32(&gioRCSSBaseREGt);
}
#endif

/*LDRA_INSPECTED 580 S : MISRAC_2012_R.20.4
 * "Reason - macro is undefined in other file,but LDRA is not able to analyse
 *this " */
#define DIO_STOP_SEC_CODE
/*LDRA_INSPECTED 243 S : MISRAC_2012_11.4
 * "Reason - Memmap file can't have include guard. " */
#include "Dio_MemMap.h"
