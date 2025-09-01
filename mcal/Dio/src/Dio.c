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
 *  \file     Dio.c
 *  \brief    This file contains Dio MCAL driver
 *
 */
/* Common Design ID's */
/*
 * Design:
 * MCAL-19941,MCAL-19930,MCAL-19933,MCAL-20854,MCAL-19929,MCAL-19958,MCAL-19913,MCAL-19914,MCAL-19916,MCAL-19917,MCAL-19918,MCAL-19919,MCAL-19779,MCAL-19915,MCAL-21114,MCAL-20979,MCAL-20978,MCAL-20969
 */

/* -----------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------
 *    File       :  Dio.c
 *    Component  :  AM263x MCAL driver
 *    Module     :  DioDriver
 *    Generator  :  -
 *
 *    Description: This DIO Driver provides services for reading and writing to/from
 *                        -   DIO Channels (Pins)
 *                        -   DIO Ports
 *                        -   DIO Channel Groups
 *
 *                This module works on pins and ports which are configured by the
 *                PORT driver for this purpose.For this reason there is no
 *                configuration and initialization of this port structure in the
 *                DIO Driver.
 *------------------------------------------------------------------------------*/
#define DIO_SOURCE

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Requirements : SWS_Dio_00117 */
#include "Dio.h"
#include "Dio_Priv.h"
/* Requirements : SWS_Dio_00117 */
#include "SchM_Dio.h"

/* Requirements : SWS_Dio_00117, SWS_Dio_00194 */
#if (DIO_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "sys_common.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((DIO_AR_RELEASE_MAJOR_VERSION != (0x04U)) || (DIO_AR_RELEASE_MINOR_VERSION != (0x03U)) || \
     (DIO_AR_RELEASE_REVISION_VERSION != (0x01U)))
#error "AUTOSAR Version Numbers of Dio are different"
#endif

#if ((DIO_SW_MAJOR_VERSION != (10U)) || (DIO_SW_MINOR_VERSION != (2U)))
#error "Version numbers of Dio.c and Dio.h are inconsistent!"
#endif

#if ((DIO_CFG_MAJOR_VERSION != (10U)) || (DIO_CFG_MINOR_VERSION != (2U)))
#error "Version numbers of Dio.c and Dio_Cfg.h are inconsistent!"
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (STD_ON == DIO_DEV_ERROR_DETECT)
static inline void Dio_ReportDetError(uint8 apiId, uint8 errorId);
#endif

#if (STD_ON == DIO_REGISTER_READBACK_API)
static FUNC(Std_ReturnType, DIO_CODE)
    Dio_RegReadback_Deterror(P2VAR(Dio_RegisterReadbackType, AUTOMATIC, DIO_APPL_DATA) RegRbPtr);
#endif

/* ========================================================================== */
/*                            Global Variable Declartions                     */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#define DIO_START_SEC_CODE
#include "Dio_MemMap.h"

#if (STD_ON == DIO_VERSION_INFO_API)
/* Design : DIO_DesignId_012 */
/* Requirements : SWS_Dio_00139, SWS_Dio_00131 */
/*
 * Design: MCAL-19937,MCAL-19930,MCAL-19933,MCAL-20854,MCAL-19929,MCAL-19958
 */
FUNC(void, DIO_CODE)
Dio_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) versioninfo)
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /*Version info pointer Validation*/
    if (NULL_PTR == versioninfo)
    {
        /*Version Info is Not Valid */
        Dio_ReportDetError(DIO_SID_GET_VERSION_INFO, DIO_E_PARAM_POINTER);
    }
    else
#endif
    {
        /*Adding Version Details */
        versioninfo->vendorID         = (uint16)DIO_VENDOR_ID;
        versioninfo->moduleID         = (uint16)DIO_MODULE_ID;
        versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
    }

    return;
}
#endif /*(STD_ON == DIO_VERSION_INFO_API)*/

/* Design : DIO_DesignId_005 */
/* Requirements : SWS_Dio_00133 */
/*
 * Design: MCAL-19928,MCAL-19930,MCAL-19933,MCAL-20854,MCAL-19929,MCAL-19958,MCAL-19934
 */
FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    uint32        baseAddr;
    uint32        pinNumber;
    /* Requirements : SWS_Dio_00118 */
    Dio_LevelType chLevelVal = (Dio_LevelType)DIO_RETURN_ZERO;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /*Checking Valid Channel or not*/
    if ((((Std_ReturnType)E_OK) != Dio_CheckChannelValidity(ChannelId)))
    {
        Dio_ReportDetError(DIO_SID_READ_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
#endif
    {
        /*Getting Hw Pin Number of the channel Id*/
        Dio_GetGPIORegInfo(ChannelId, &baseAddr, &pinNumber);

        /*Reading Channel Value*/
        chLevelVal = Dio_PinRead(baseAddr, pinNumber);
    }

    return (chLevelVal);
}

/* Design : DIO_DesignId_006 */
/* Requirements : SWS_Dio_00134, SWS_Dio_00109 */
/*
 * Design:
 * MCAL-19920,MCAL-19921,MCAL-19922,MCAL-19923,MCAL-19924,MCAL-19959,MCAL-19961,MCAL-19960,MCAL-19934
 */
FUNC(void, DIO_CODE) Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
#if defined(DIO_WRITE_CHANNEL_EVENT_ID)
    Dio_DirectionType gioDirection;
#endif

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /* Checking Valid channel or not */
    if ((((Std_ReturnType)E_OK) != Dio_CheckChannelValidity(ChannelId)))
    {
        /* ChannelId is NOT valid */
        Dio_ReportDetError(DIO_SID_WRITE_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    /* Requirements : SWS_Dio_00119 */
    else
#endif
    {
        Dio_ChkDirWritePin(ChannelId, Level);
#if defined(DIO_WRITE_CHANNEL_EVENT_ID)
        /*If the channel is not configured as input, IO check*/
        /*
         * Design: MCAL-19920,MCAL-19921
         */
        DIO_GioGetDirection(ChannelId, &gioDirection);
        if (DIO_DIR_OUTPUT == gioDirection)
        {
            if (((Std_ReturnType)E_NOT_OK) == Dio_CheckIO(ChannelId, Level))
            {
                /* Requirements : SWS_Dio_00131, SWS_Dio_00140 */
                (void)Dem_SetEventStatus((Dem_EventIdType)DIO_WRITE_CHANNEL_EVENT_ID, DEM_EVENT_STATUS_FAILED);
            }
        }
#endif
    }

    return;
}

/* Design : DIO_DesignId_007 */
/* Requirements : SWS_Dio_00135, SWS_Dio_00104 */
/*
 * Design: MCAL-19931,MCAL-19962,MCAL-19963,MCAL-19935
 */
FUNC(Dio_PortLevelType, DIO_CODE) Dio_ReadPort(Dio_PortType PortId)
{
    /* Requirements : SWS_Dio_00118, SWS_Dio_00031 */
    Dio_PortLevelType portVal = (Dio_PortLevelType)DIO_RETURN_ZERO;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /* Checking port is valid or not */
    if (0U == (DIO_ENABLED_PORT_MASK & (1U << PortId)))
    {
        /* PortId is NOT valid */
        Dio_ReportDetError(DIO_SID_READ_PORT, DIO_E_PARAM_INVALID_PORT_ID);
    }
    else
#endif
    {
        /*Getting Port Value*/
        Dio_GioReadPort(PortId, &portVal);
    }

    return (portVal);
}

/* Design : DIO_DesignId_008 */
/* Requirements : SWS_Dio_00136 */
/*
 * Design: MCAL-19925,MCAL-19965,MCAL-19964,MCAL-19926,MCAL-19967,MCAL-19966,MCAL-19935
 */
FUNC(void, DIO_CODE) Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /* Requirements : SWS_Dio_00075 */
    if (0U == (DIO_ENABLED_PORT_MASK & (1U << PortId)))
    {
        /* PortId is NOT valid  */
        Dio_ReportDetError(DIO_SID_WRITE_PORT, DIO_E_PARAM_INVALID_PORT_ID);
    }
    /* Requirements : SWS_Dio_00119 */
    else
#endif
    {
        /* Requirements : SWS_Dio_00005, SWS_Dio_00060 */
        SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_0();

        /* Writing the value to the Port */
        Dio_GioWritePort(PortId, Level);
        /* Requirements : SWS_Dio_00005, SWS_Dio_00060 */
        SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_0();
    }

    return;
}

/* Design : DIO_DesignId_009 */
/* Requirements : SWS_Dio_00137 */
/*
 * Design: MCAL-19968,MCAL-19969,MCAL-19932,MCAL-19970,MCAL-19936
 */
FUNC(Dio_PortLevelType, DIO_CODE)
Dio_ReadChannelGroup(Dio_ChannelGroupRefType ChannelGroupIdPtr)
{
    /* Requirements : SWS_Dio_00118 */
    Dio_PortLevelType portLevelVal = (Dio_PortLevelType)DIO_RETURN_ZERO;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /* Checking Channel Group Id is valid or not*/
    if (NULL_PTR == ChannelGroupIdPtr)
    {
        /* null pointer is referenced by the parameter */
        Dio_ReportDetError(DIO_SID_READ_CHL_GROUP, DIO_E_PARAM_INVALID_GROUP);
    }
    else
#endif
    {
        /*Reading Port Value*/
        Dio_GioReadPort(ChannelGroupIdPtr->port, &portLevelVal);

        /*Reading Channelgrp Value using mask */
        portLevelVal &= ChannelGroupIdPtr->mask;

        /* Getting accurate Channelgrp value */
        portLevelVal >>= ChannelGroupIdPtr->offset;
    }

    return (portLevelVal);
}

/* Design : DIO_DesignId_010 */
/* Requirements : SWS_Dio_00138 */
/*
 * Design: MCAL-19972,MCAL-19973,MCAL-19974,MCAL-19927,MCAL-19971,MCAL-19936
 */
FUNC(void, DIO_CODE)
Dio_WriteChannelGroup(Dio_ChannelGroupRefType ChannelGroupIdPtr, Dio_PortLevelType Level)
{
    uint32 portLevelVal;
    uint32 newValue;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /* Checking the Channelgrp ptr valid or not*/
    if (NULL_PTR == ChannelGroupIdPtr)
    {
        /* null pointer is referenced by the parameter */
        Dio_ReportDetError(DIO_SID_WRITE_CHL_GROUP, DIO_E_PARAM_INVALID_GROUP);
    }
    /* Requirements : SWS_Dio_00119 */
    else
#endif
    {
        uint8 groupoffset;

        /* Requirements : SWS_Dio_00005, SWS_Dio_00060 */
        SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_0();
        /*assiging ChannelId Offset*/
        groupoffset = ChannelGroupIdPtr->offset;

        /*making newlevel to write on the ChannelGrp*/
        newValue = ((Level << groupoffset) & ChannelGroupIdPtr->mask);

        /*Reading the Current values of the port*/
        Dio_GioReadPort(ChannelGroupIdPtr->port, &portLevelVal);

        /*Resetting the Values of the ChannelGrp*/
        portLevelVal &= (~ChannelGroupIdPtr->mask);

        /*storing the  the ChannelGrp values in a variable*/
        portLevelVal |= newValue;

        /*Writing the Desired value to the Channelgrp */
        Dio_GioWritePort(ChannelGroupIdPtr->port, portLevelVal);

        /* Requirements : SWS_Dio_00005, SWS_Dio_00060 */
        SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_0();
    }

    return;
}

/*
 * Design: MCAL-19976,MCAL-19977,MCAL-19978
 */
#if (STD_ON == DIO_FLIP_CHANNEL_API)
/* Design : DIO_DesignId_011 */
/* Requirements : SWS_Dio_00190, SWS_Dio_00192, SWS_Dio_00193 */
FUNC(Dio_LevelType, DIO_CODE) Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType channelVal = (Dio_LevelType)DIO_RETURN_ZERO;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    /*checking valid channel or not */
    if ((((Std_ReturnType)E_OK) != Dio_CheckChannelValidity(ChannelId)))
    {
        Dio_ReportDetError(DIO_SID_FLIP_CHANNEL, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    /* Requirements : SWS_Dio_00119 */
    else
#endif
    {
        Dio_DirectionType gioDirection;
        uint32            baseAddr, pinNumber;

        /*Getting the pin number for the ChannelId*/
        Dio_GetGPIORegInfo(ChannelId, &baseAddr, &pinNumber);

        /* Getting the Direction of the Channel */
        DIO_GioGetDirection(ChannelId, &gioDirection);

        if (DIO_DIR_OUTPUT == gioDirection)
        {
            /*Toggle the Channel value */
            Dio_GpioBitToggle((gpioPORT_t*)baseAddr, pinNumber);

            /*Reading the Channel value*/
            channelVal = Dio_PinRead(baseAddr, pinNumber);
        }
        else
        {
            Dio_LevelType flipValue;
            /*Read the channel value*/
            flipValue = Dio_PinRead(baseAddr, pinNumber);

            /* Input channel can't change value */
            channelVal = flipValue;
        }
    }
    return (channelVal);
}
#endif /*(STD_ON == DIO_FLIP_CHANNEL_API)*/

/*
 * Design: MCAL-19975,MCAL-19940,MCAL-19939,MCAL-19938
 */
#if (STD_ON == DIO_DEV_ERROR_DETECT)
static inline void Dio_ReportDetError(uint8 apiId, uint8 errorId)
{
    /* Requirements : SWS_Dio_00140 */
    (void)Det_ReportError(DIO_MODULE_ID, 0, apiId, errorId);
    return;
}
#endif /* #if (STD_ON == DIO_DEV_ERROR_DETECT) */

/**
 *\brief   This function is used to readback some critical DIO registers
 *
 */
/*
 * Design: MCAL-21114,MCAL-20979,MCAL-20978,MCAL-20969
 */

#if (STD_ON == DIO_REGISTER_READBACK_API)
FUNC(Std_ReturnType, DIO_CODE)
Dio_RegisterReadback(P2VAR(Dio_RegisterReadbackType, AUTOMATIC, DIO_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

#if (STD_ON == DIO_DEV_ERROR_DETECT)
    retVal = Dio_RegReadback_Deterror(RegRbPtr);
#endif

    /* Check if return value is correct. */
    if (retVal == E_OK)
    {
        /* Readback the register. */
        Dio_HwRegisterReadback(RegRbPtr);
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    /* Return the Value. */
    return (retVal);
}

#if (STD_ON == DIO_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, DIO_CODE)
    Dio_RegReadback_Deterror(P2VAR(Dio_RegisterReadbackType, AUTOMATIC, DIO_APPL_DATA) RegRbPtr)
{
    Std_ReturnType retVal = E_OK;

    if (NULL_PTR == RegRbPtr)
    {
        (void)Dio_ReportDetError(DIO_SID_REGISTER_READBACK, DIO_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }
    return retVal;
}
#endif
#endif /* #if (STD_ON == DIO_REGISTER_READBACK_API) */

#define DIO_STOP_SEC_CODE
#include "Dio_MemMap.h"
