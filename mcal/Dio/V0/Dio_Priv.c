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
 *
 */

#define DIO_PRIV_SOURCE (1)

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Dio_Priv.h"
#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DIO_NUM_GPIO_REGS (5U)

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

#define DIO_START_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"

STATIC CONST(uint32, DIO_CONST) Dio_GPIOPortAddr[DIO_NUM_GPIO_REGS] = {
    DIO_GPIO_BASE + 0x10U, DIO_GPIO_BASE + 0x38U, DIO_GPIO_BASE + 0x60U, DIO_GPIO_BASE + 0x88U, DIO_GPIO_BASE + 0xB0U,
};

#define DIO_STOP_SEC_CONST_UNSPECIFIED
#include "Dio_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"
uint32 Dio_GetGPIOPortAddr(uint8 regNum)
{
    uint32 retVal;

    /*Reading Baseaddress of the Port*/
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
    /*Getting the value of Gpio Pin*/
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

    /*Returing the Gpio pin Direction*/
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
    /*Setting  the Gpio Pin value*/
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
    uint32 regWrFailStatus = 0U;
    /*Writing the port value */
    regWrFailStatus |= regWriteReadback(&port->DOUT, M_THIRTY_ONE, M_ZERO, setBits);
    /* TI_COVERAGE_GAP_START Hardware register write failure cannot be recreated in test environment */
    if (regWrFailStatus != MCAL_REGWR_E_OK)
    {
#ifdef DIO_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus((Dem_EventIdType)DIO_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    /* TI_COVERAGE_GAP_STOP */

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
    /*Getting the value of the port*/
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

    /*Toggling the pin value */
    if ((dataIn & (uint32)((uint32)1U << bit)) != 0U)
    {
        port->DCLR = (uint32)1U << bit;
    }
    else
    {
        port->DSET = (uint32)1U << bit;
    }
}
/**
 * @fn
 */

void Dio_GetGPIORegInfo(Dio_ChannelType channelId, uint32 *baseAddr, uint32 *pinNumber)
{
    uint8 gpioRegNum;
    uint8 gpioPinNum;

    /*Calculating port number*/
    gpioRegNum = (uint8)(channelId / DIO_PORT_WIDTH);
    /*Calculating Pin number*/
    gpioPinNum = (uint8)(channelId % DIO_PORT_WIDTH);

    /*Assiging base address of the port*/
    *baseAddr = Dio_GetGPIOPortAddr(gpioRegNum);

    /*Assiging base address of the pin */
    *pinNumber = gpioPinNum;
}

#if (STD_ON == DIO_DEV_ERROR_DETECT)
Std_ReturnType Dio_CheckChannelValidity(Dio_ChannelType channelId)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    uint8          gpioRegNum, gpioPinNum;
    boolean        isChannelEnabled = (boolean)FALSE;

    gpioRegNum = (uint8)(channelId / DIO_PORT_WIDTH);
    gpioPinNum = (uint8)(channelId % DIO_PORT_WIDTH);

    /*Validating channel Id*/
    if (gpioRegNum < DIO_MAX_NO_OF_PORTS)
    {
        if (0U != ((uint32)(DioConfig_ValidChannelMask[gpioRegNum]) & (1U << gpioPinNum)))
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

/* Requirements : SWS_Dio_00105 */
void Dio_GioWritePort(uint32 portId, uint32 Level)
{
    uint32 baseAddr;
    baseAddr = Dio_GetGPIOPortAddr((uint8)portId);
    /* Requirements : SWS_Dio_00004, SWS_Dio_00035, SWS_Dio_00108  SWS_Dio_00007*/
    /* Requirements : SWS_Dio_00040 */
    /* Requirements : SWS_Dio_00024, SWS_Dio_00108,  SWS_Dio_00007*/
    /*Writing the Desired value on port */
    (void)Dio_GpioPortWrite((gpioPORT_t *)baseAddr, Level);
}

void Dio_GioReadPort(uint32 portId, uint32 *portVal)
{
    uint32 baseAddr;

    /*Getting base address of the Port*/
    baseAddr = Dio_GetGPIOPortAddr((uint8)portId);
    /* Requirements : SWS_Dio_00013 */
    /*Reading the Port value */
    *portVal = (uint32)Dio_GpioGetPort((const gpioPORT_t *)baseAddr);
}

/* Requirements : SWS_Dio_00051 */
static void Dio_PinWrite(uint32 baseAdd, uint32 pinNumber, Dio_LevelType level)
{
    /* Requirements : SWS_Dio_00089, SWS_Dio_00006 */
    if (((Dio_LevelType)STD_HIGH) == level)
    {
        /*Setting logic 1 to the pin */
        Dio_GpioSetBit((gpioPORT_t *)baseAdd, pinNumber, STD_HIGH);
    }
    else
    {
        /*Setting logic 0 to the pin */
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

    /*Reading the channel value */
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

    /*Getting the Direction of the Gpio pin */
    regval = Dio_GpioGetDirection((const gpioPORT_t *)baseAddr, pinNumber);
    if ((uint32)1U == regval)
    {
        *gioDirection = DIO_DIR_INPUT;
    }
    else
    {
        *gioDirection = DIO_DIR_OUTPUT;
    }
}

#endif

/**
 *
 */
Dio_LevelType Dio_PinRead(uint32 baseAddr, uint32 pinNumber)
{
    uint32        logiclvl;
    Dio_LevelType lvlret;

    /* Requirements : SWS_Dio_00051, SWS_Dio_00089 */

    /*Reading the value of the desired pin */
    logiclvl = Dio_GpioGetLogicLvl((const gpioPORT_t *)baseAddr, pinNumber);

    /* Requirements : SWS_Dio_00023 */
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

/*Checking the status of GIO register: refer trm*/
#if (STD_ON == DIO_REGISTER_READBACK_API)
void Dio_HwRegisterReadback(Dio_RegisterReadbackType *RegRbPtr)
{
    gpioBASE_t *gioBaseREGt = (gpioBASE_t *)DIO_GPIO_BASE;

    (void)memset(RegRbPtr, 0, sizeof(Dio_RegisterReadbackType));

    RegRbPtr->PID_REG    = HW_RD_REG32(&gioBaseREGt->PID);
    RegRbPtr->PCR_REG    = HW_RD_REG32(&gioBaseREGt->PCR);
    RegRbPtr->BINTEN_REG = HW_RD_REG32(&gioBaseREGt->BINTEN);
}
#endif

#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"
