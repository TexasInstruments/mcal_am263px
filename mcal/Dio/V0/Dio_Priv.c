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
#define M_ZERO            (0U)
#define M_THIRTY          (30U)
#define M_THIRTY_ONE      (31U)

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
    if (regWrFailStatus != (uint32)E_OK)
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
