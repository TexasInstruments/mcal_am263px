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

/* -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *
 -------------------------------------------------------------------------------------------------------------------
 *         File:  Can.c
 *      Project:  MCAL driver
 *       Module:  CAN Driver
 *
 *  Description:    The CAN driver provides services for CAN communication

 *---------------------------------------------------------------------------------------------------------------------
 *********************************************************************************************************************/

/* Common Design ID's */
/*
 *Design: MCAL-17130, MCAL-17128, MCAL-16930, MCAL-17040, MCAL-17036, MCAL-16899, MCAL-16969
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include "SchM_Can.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include "EcuM_Cbk.h"
/* #include "Os.h" */

#include "Det.h"

#include "soc.h"
#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"
#include "Can_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* AUTOSAR version information check has to match definition in header file */
#if ((CAN_AR_RELEASE_MAJOR_VERSION != (4U)) || (CAN_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (CAN_AR_RELEASE_REVISION_VERSION != (1U)))
#error "CAN: AUTOSAR Version Numbers of CAN are different"
#endif

#if ((CAN_SW_MAJOR_VERSION != (10U)) || (CAN_SW_MINOR_VERSION != (2U)))
#error "Vendor specific version numbers of Can.c and Can.h are inconsistent"
#endif

#if ((CAN_CFG_MAJOR_VERSION != (10U)) || (CAN_CFG_MINOR_VERSION != (2U)))
#error "Version numbers of Can.c and Can_Cfg.h are inconsistent!"
#endif

/* FMEA requirement */
#if (STD_OFF == CAN_ECC_ENABLE)
/* TODO #warn "CAN parity check is not enabled " */
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
static boolean Can_CheckInitDet(const Can_ConfigType *ConfigPtr);
static boolean Can_CheckControllerConfig(const Can_ConfigType *ConfigPtr);
static boolean Can_CheckControllerList(const Can_ConfigType *ConfigPtr);
static boolean Can_CheckBaudrateCLConfig(const Can_ConfigType *ConfigPtr);
static boolean Can_CheckMbConfig(const Can_ConfigType *ConfigPtr);
static boolean Can_CheckWriteDet(const uint32 Hth, const Can_PduType *PduInfo, const Can_DriverObjType *canDrvObj);
static boolean Can_CheckWriteDetInternal(const Can_PduType *PduInfo, const Can_DriverObjType *canDrvObj,
                                         uint8 MsgCntrlr);
static boolean Can_CheckEnableDet(uint8 Controller, const Can_DriverObjType *canDrvObj);
static boolean Can_CheckDisableDet(uint8 Controller, const Can_DriverObjType *canDrvObj);
static boolean Can_CheckSetControllerModeDet(uint8 Controller, const Can_DriverObjType *canDrvObj);
static boolean Can_SetBaudrateDet(uint8 Controller, const Can_DriverObjType *canDrvObj);
static Std_ReturnType Can_Write_Internal(uint8 MsgCntrlr, Can_HwHandleType HwHandle, Can_HwHandleType Hth,
                                         const Can_PduType *PduInfo);
#endif

static void Can_resetDrvObj(Can_DriverObjType *drvObj);
static void Can_Initialization(uint8 controller_cntr);
static void Can_initDrvObj(Can_DriverObjType *drvObj, const Can_ConfigType *ConfigPtr);

/*******************************************************************************
 *  CONSTANT MACRO DEFINITION
 ******************************************************************************/

/* Interrupt source */
#define INT_IE0 (0x1U)
#define INT_IE1 (0x2U)

/**
 *  \brief CAN INVALID BASE ADDRESS
 */
#define CAN_INVALID_BASE_ADDR (0x00000000U)

#define CAN_ID_CAN_CONTROLLER_TYPE_MASK (0x40000000U)
#define CAN_ID_CAN_ID_TYPE_MASK         (0x80000000U)

/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *  LOCAL DATA DEFINITIONS
 ******************************************************************************/

#define CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"

/*LDRA_INSPECTED 94 S : MISRAC_2012_R.11.1
 * "Reason - NULL pointer is defined as void pointer to zero. " */
/*LDRA_INSPECTED 95 S : MISRAC_2012_R.11.4
 * "Reason - NULL pointer is defined as void pointer to zero. " */
VAR(Can_DriverObjType, CAN_VAR_NOINIT) Can_DriverObj;

#define CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Can_MemMap.h"

#define CAN_START_SEC_VAR_INIT_8
#include "Can_MemMap.h"

VAR(uint8, CAN_VAR_INIT) Can_DrvState = CAN_UNINIT;

#define CAN_STOP_SEC_VAR_INIT_8
#include "Can_MemMap.h"

#define CAN_START_SEC_CODE
#include "Can_MemMap.h"

/*Requirements :SWS_Can_00079 , SWS_Can_00077, SWS_Can_00284, SWS_Can_00385,
 * SWS_Can_00386, SWS_Can_00427, SWS_Can_00401, SWS_Can_00402, SWS_Can_00403,
 * SWS_Can_00060,
 * SWS_Can_00202, SWS_Can_00110, SWS_Can_00234,
 * SWS_Can_00022,
 * SWS_Can_00024, SWS_Can_00221
 * SWS_Can_00490, SWS_Can_00440, SWS_Can_00242, SWS_Can_00398, SWS_Can_00397,
 * SWS_Can_00390  */
/*
 *Design: MCAL-16988, MCAL-16947, MCAL-16993, MCAL-16876, MCAL-16995, MCAL-17095, MCAL-17095,
 *MCAL-16842, MCAL-16991, MCAL-17016, MCAL-16866, MCAL-16998, MCAL-17010, MCAL-17069, MCAL-17106,
 *MCAL-17019, MCAL-16893, MCAL-16871, MCAL-16883
 */
/* Optional Requirements which not implemented */
/* SWS_Can_00235, SWS_Can_00236, SWS_Can_00235, SWS_Can_00504, SWS_Can_00503 */

/* Not Applicable */
/* SWS_Can_00391, SWS_Can_00300, SWS_Can_00299, SWS_Can_00281 */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*******************************************************************************
 * Can_Initialization
 ******************************************************************************/
/*! \brief      This function will Initialise the Can controller.
 *
 *  \param[in]  uint8 controller_cntr count for Driver object.
 *
 *  \context
 ******************************************************************************/
/*
 *Design: MCAL-16915, MCAL-17111, MCAL-16964, MCAL-16865
 */
static void Can_Initialization(uint8 controller_cntr)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if ((Can_DriverObj.canController[controller_cntr].canState != CAN_CS_UNINIT) || (Can_DrvState != CAN_UNINIT))
    {
        /* Can controller is in not in UNINT state */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_INIT_ID,
                              (uint8)CAN_E_TRANSITION);
    }
    else
#endif
    {
        /* If Controller is active then only do initialization */
        if (Can_DriverObj.canController[controller_cntr].canControllerConfig_PC.CntrActive == (boolean)TRUE)
        {
            /* Init individual controller (may be moved to
             * SetControllerMode(start state)) */
            Can_hwUnitConfig(&Can_DriverObj.canController[controller_cntr], &Can_DriverObj.canMailbox[0U],
                             &Can_DriverObj.canTxMessageObj[0U], Can_DriverObj.maxMbCnt);
            /* initialize the interrupt counter to zero */
            Can_DriverObj.canController[controller_cntr].canInterruptCounter = 0U;
            /* change the state to stopped from the UNINIT state */
            Can_DriverObj.canController[controller_cntr].canState = CAN_CS_STOPPED;
            /* Update BusOff Recovery status */
            Can_DriverObj.canController[controller_cntr].canBusOffRecoveryStatus = (boolean)FALSE;
        }
    }
}

/*******************************************************************************
 * Can_resetDrvObj
 ******************************************************************************/
/*! \brief      This function will reset default  Config structure.
 *
 *  \param[in]  Can_DriverObjType drvObj Pointer to Driver Config structure.
 *
 *  \context
 ******************************************************************************/
static void Can_resetDrvObj(Can_DriverObjType *drvObj)
{
    uint32 controllerIndx, mbIndx;
    for (controllerIndx = 0U; controllerIndx < (uint32)CAN_NUM_CONTROLLER; controllerIndx++)
    {
        if (Can_DrvState == CAN_UNINIT)
        {
            drvObj->canController[controllerIndx].canState = CAN_CS_UNINIT;
        }
        drvObj->canController[controllerIndx].canBaud                 = 0U;
        drvObj->canController[controllerIndx].canBusOffRecoveryStatus = (boolean)FALSE;
        drvObj->canController[controllerIndx].canInterruptCounter     = (uint8)0U;
        drvObj->canController[controllerIndx].canInterruptMask        = (uint32)0U;
        for (mbIndx = 0U; mbIndx < (uint32)CAN_FD_PAYLOAD_MAX_BYTES; mbIndx++)
        {
            drvObj->canController[controllerIndx].canSduPtr[mbIndx] = (uint8)0U;
        }
        drvObj->canController[controllerIndx].canFDMsgRamConfig.stdFilterNum = 0U;
        drvObj->canController[controllerIndx].canFDMsgRamConfig.extFilterNum = 0U;
    }
    for (mbIndx = 0U; mbIndx < (uint32)CAN_NUM_TX_MAILBOXES; mbIndx++)
    {
        drvObj->canTxMessageObj[mbIndx].freeHwObjectCount = 0U;
        drvObj->canTxMessageObj[mbIndx].lowerBuffIdx      = 0U;
        drvObj->canTxMessageObj[mbIndx].higherBuffIdx     = 0U;
    }
    return;
}

/*******************************************************************************
 * Can_initDrvObj
 ******************************************************************************/
/*! \brief      This function will initialize Driver Config structure.
 *
 *  \param[in]  Can_DriverObjType drvObj Pointer to Driver Config structure.
 *  \param[in]  Can_ConfigType ConfigPtr Pointer to Can controllers
 *              Config structure.
 *
 *  \context
 ******************************************************************************/
/*
 *Design: MCAL-17012
 */
static void Can_initDrvObj(Can_DriverObjType *drvObj, const Can_ConfigType *ConfigPtr)
{
    uint32                    controllerIndx, mbIndx;
    uint32                    htrh;
    const Can_MailboxType    *mailboxCfg;
    const Can_MailboxObjType *mailBoxCfgList;
    Can_MailboxObjTxType     *canTxMessageObj;
    uint16                    hth;
    uint32                    maxMbCnt;
    for (controllerIndx = 0U; controllerIndx < (uint32)CAN_NUM_CONTROLLER; controllerIndx++)
    {
        (void)memcpy(&drvObj->canController[controllerIndx].canControllerConfig,
                     ConfigPtr->CanControllerList[controllerIndx], sizeof(Can_ControllerType));
        (void)memcpy(&drvObj->canController[controllerIndx].canControllerConfig_PC,
                     CanConfigSet_CanController_List_PC[controllerIndx], sizeof(Can_ControllerType_PC));
        drvObj->canController[controllerIndx].maxBaudConfigID = ConfigPtr->MaxBaudConfigID[controllerIndx];
        drvObj->controllerIDMap[CanConfigSet_CanController_List_PC[controllerIndx]->CanControllerInst] = controllerIndx;
    }
    for (mbIndx = 0U; mbIndx < (uint32)CAN_NUM_MAILBOXES; mbIndx++)
    {
        (void)memcpy(&drvObj->canMailbox[mbIndx].mailBoxConfig, ConfigPtr->MailBoxList[mbIndx],
                     sizeof(Can_MailboxType));
        (void)memcpy(&drvObj->canMailbox[mbIndx].mailBoxConfig_PC, CanConfigSet_CanHardwareObject_List_PC[mbIndx],
                     sizeof(Can_MailboxType_PC));
    }
    drvObj->canMaxControllerCount = ConfigPtr->CanMaxControllerCount;
    drvObj->maxMbCnt              = ConfigPtr->MaxMbCnt;

    mailBoxCfgList  = &drvObj->canMailbox[0U];
    canTxMessageObj = &drvObj->canTxMessageObj[0];
    maxMbCnt        = drvObj->maxMbCnt;
    /* Initialize Can_MailboxObjTxType params according to configured mailboxes */
    for (htrh = 0U; htrh < maxMbCnt; htrh++)
    {
        mailboxCfg = &mailBoxCfgList[htrh].mailBoxConfig;

        if (CAN_MAILBOX_DIRECTION_TX == mailboxCfg->MBDir)
        {
            hth                                    = mailboxCfg->HwHandle;
            canTxMessageObj[hth].freeHwObjectCount = mailboxCfg->CanHwObjectCount;
        }
    }
}

/*******************************************************************************
 * Can_SetBaudrateDet
 ******************************************************************************/
/*! \brief      This function will check DET for Can_ChangeBaudrate API.
 *
 *  \param[in]  uint8 Controller Controller Number in the can hardware its 0-3
 *
 *  \context
 ******************************************************************************/
/*
 *Design: MCAL-21538, MCAL-16933
 */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
static boolean Can_SetBaudrateDet(uint8 Controller, const Can_DriverObjType *canDrvObj)
{
    boolean returnstatus = (boolean)TRUE;
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETBAUDRATE_ID,
                              (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else if (Controller >= (canDrvObj->canMaxControllerCount))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETBAUDRATE_ID,
                              (uint8)CAN_E_PARAM_CONTROLLER);
        returnstatus = (boolean)FALSE;
    }
    else if (canDrvObj->canController[Controller].canState != CAN_CS_STOPPED)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETBAUDRATE_ID,
                              (uint8)CAN_E_TRANSITION);
        returnstatus = (boolean)FALSE;
    }
    else
    {
        /* MISRA C Compliance */
    }
    return returnstatus;
}

#endif

/*******************************************************************************
 * Can_CheckInitDet
 ******************************************************************************/
/*! \brief      This function will check for NULL pointers for Config structure.
 *
 *  \param[in]  Can_ConfigType ConfigPtr Pointer to Driver Config structure.
 *
 *  \context
 ******************************************************************************/
/*
 *Design: MCAL-16980
 */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
static boolean Can_CheckInitDet(const Can_ConfigType *ConfigPtr)
{
    boolean returnstatus = (boolean)TRUE;

    returnstatus = Can_CheckControllerConfig(ConfigPtr);
    if ((boolean)TRUE == returnstatus)
    {
        returnstatus = Can_CheckMbConfig(ConfigPtr);
    }

    return returnstatus;
}

static boolean Can_CheckControllerConfig(const Can_ConfigType *ConfigPtr)
{
    boolean returnstatus = (boolean)TRUE;

    returnstatus = Can_CheckControllerList(ConfigPtr);
    if ((boolean)TRUE == returnstatus)
    {
        returnstatus = Can_CheckBaudrateCLConfig(ConfigPtr);
    }

    return returnstatus;
}

static boolean Can_CheckControllerList(const Can_ConfigType *ConfigPtr)
{
    boolean returnstatus = (boolean)TRUE;
    uint32  loopCnt;

    for (loopCnt = 0U; loopCnt < CAN_NUM_CONTROLLER; loopCnt++)
    {
        if ((NULL_PTR == ConfigPtr->CanControllerList[loopCnt]) ||
            (NULL_PTR == ConfigPtr->CanControllerList[loopCnt]->DefaultBaud))
        {
            returnstatus = (boolean)FALSE;
        }
        else if (CAN_INVALID_BASE_ADDR == CanConfigSet_CanController_List_PC[loopCnt]->CntrAddr)
        {
            returnstatus = (boolean)FALSE;
        }
        else
        {
            /*Do Nothing*/
        }

        if (returnstatus == (boolean)FALSE)
        {
            break;
        }
    }

    return returnstatus;
}

static boolean Can_CheckBaudrateCLConfig(const Can_ConfigType *ConfigPtr)
{
    boolean returnstatus = (boolean)TRUE;
    uint32  loopCnt      = 0, cnt;

    for (cnt = 0U; cnt <= ConfigPtr->MaxBaudConfigID[loopCnt]; cnt++)
    {
        if (NULL_PTR == ConfigPtr->CanControllerList[loopCnt]->BaudRateConfigList[cnt])
        {
            returnstatus = (boolean)FALSE;
        }

        if (returnstatus == (boolean)FALSE)
        {
            break;
        }
    }

    return returnstatus;
}

static boolean Can_CheckMbConfig(const Can_ConfigType *ConfigPtr)
{
    boolean returnstatus = (boolean)TRUE;
    uint32  loopCnt;

    for (loopCnt = 0U; loopCnt < CAN_NUM_MAILBOXES; loopCnt++)
    {
        if (NULL_PTR == ConfigPtr->MailBoxList[loopCnt])
        {
            returnstatus = (boolean)FALSE;
        }
        else if (NULL_PTR == ConfigPtr->MailBoxList[loopCnt]->Controller)
        {
            returnstatus = (boolean)FALSE;
        }
        else
        {
            /*Do Nothing*/
        }

        if (returnstatus == (boolean)FALSE)
        {
            break;
        }
    }
    return returnstatus;
}
#endif

/*******************************************************************************
 * Can_CheckSetControllerModeDet
 ******************************************************************************/
/*! \brief      This function will check DET for SetControllerMode API.
 *
 *  \param[in]  uint8 Controller Controller Number in the can hardware its 0-3
 *
 *  \context
 ******************************************************************************/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
/*
 *Design: MCAL-16977, MCAL-16994
 */
static boolean Can_CheckSetControllerModeDet(uint8 Controller, const Can_DriverObjType *canDrvObj)
{
    boolean returnstatus;
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETCTR_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else if (Controller >= (canDrvObj->canMaxControllerCount))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETCTR_ID,
                              (uint8)CAN_E_PARAM_CONTROLLER);
        returnstatus = (boolean)FALSE;
    }
    else if (canDrvObj->canController[Controller].canControllerConfig_PC.CntrActive == (boolean)FALSE)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETCTR_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else
    {
        /* MISRA C Compliance */
        returnstatus = (boolean)TRUE;
    }
    return returnstatus;
}

#endif

/*******************************************************************************
 * Can_CheckDisableDet
 ******************************************************************************/
/*! \brief      This function will check DET for Disable API.
 *
 *  \param[in]  uint8 Controller Controller Number in the can hardware its 0-3
 *
 *  \context
 ******************************************************************************/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
/*
 *Design: MCAL-16944
 */
static boolean Can_CheckDisableDet(uint8 Controller, const Can_DriverObjType *canDrvObj)
{
    boolean returnstatus;
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_DIINT_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else if (Controller >= (canDrvObj->canMaxControllerCount))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_DIINT_ID,
                              (uint8)CAN_E_PARAM_CONTROLLER);
        returnstatus = (boolean)FALSE;
    }
    else if (canDrvObj->canController[Controller].canControllerConfig_PC.CntrActive == (boolean)FALSE)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_DIINT_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else
    {
        returnstatus = (boolean)TRUE;
        /* MISRA C Compliance */
    }
    return returnstatus;
}

#endif

/*******************************************************************************
 * Can_CheckEnableDet
 ******************************************************************************/
/*! \brief      This function will check DET for Enable API.
 *
 *  \param[in]  uint8 Controller Controller Number in the can hardware its 0-3
 *
 *  \context
 ******************************************************************************/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
/* Design :CAN_DesignId_006*/
static boolean Can_CheckEnableDet(uint8 Controller, const Can_DriverObjType *canDrvObj)
{
    boolean returnstatus;
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_ENINT_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else if (Controller >= (canDrvObj->canMaxControllerCount))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_ENINT_ID,
                              (uint8)CAN_E_PARAM_CONTROLLER);
        returnstatus = (boolean)FALSE;
    }
    else if (canDrvObj->canController[Controller].canControllerConfig_PC.CntrActive == (boolean)FALSE)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_ENINT_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else
    {
        returnstatus = (boolean)TRUE;
        /* MISRA C Compliance */
    }
    return returnstatus;
}

#endif

/*******************************************************************************
 * Can_CheckWriteDet
 ******************************************************************************/
/*! \brief      This function will check DET for WriteAPI.
 *
 *  \param[in]  uint8 Hth - Hardware Handle
 *              const Can_PduType *PduInfo - pointer to pdu.
 *
 *  \context
 ******************************************************************************/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
/*
 *Design: MCAL-17092, MCAL-16863, MCAL-16854, MCAL-17021
 */
static boolean Can_CheckWriteDet(const uint32 Hth, const Can_PduType *PduInfo, const Can_DriverObjType *canDrvObj)
{
    boolean returnstatus = (boolean)FALSE;
    uint8   MsgCntrlr    = 0U;
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_WRITE_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else if ((canDrvObj->maxMbCnt <= Hth) ||
             (Can_DriverObj.canMailbox[Hth].mailBoxConfig.MBDir != CAN_MAILBOX_DIRECTION_TX))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_WRITE_ID,
                              (uint8)CAN_E_PARAM_HANDLE);
        returnstatus = (boolean)FALSE;
    }
    else if ((PduInfo == NULL_PTR) || ((PduInfo->sdu == NULL_PTR) &&
                                       (Can_DriverObj.canMailbox[Hth].mailBoxConfig.CanTriggerTransmitEnable == FALSE)))
    {
        /* Can config pointer is not valid */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_WRITE_ID,
                              (uint8)CAN_E_PARAM_POINTER);
        returnstatus = (boolean)FALSE;
    }
    else
    {
        MsgCntrlr    = canDrvObj->canMailbox[Hth].mailBoxConfig.Controller->ControllerId;
        returnstatus = (boolean)TRUE;
    }
    if (returnstatus == (boolean)TRUE)
    {
        returnstatus = Can_CheckWriteDetInternal(PduInfo, &Can_DriverObj, MsgCntrlr);
    }
    return returnstatus;
}
/*
 *Design: MCAL-16860
 */
static boolean Can_CheckWriteDetInternal(const Can_PduType *PduInfo, const Can_DriverObjType *canDrvObj,
                                         uint8 MsgCntrlr)
{
    boolean returnstatus = (boolean)FALSE;
    if (PduInfo->length > 64U)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_WRITE_ID,
                              (uint8)CAN_E_PARAM_DATA_LENGTH);
        returnstatus = (boolean)FALSE;
    }
    else if ((PduInfo->length > 8U) &&
             (CAN_ID_CAN_CONTROLLER_TYPE_MASK != (CAN_ID_CAN_CONTROLLER_TYPE_MASK & PduInfo->id)))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_WRITE_ID,
                              (uint8)CAN_E_PARAM_DATA_LENGTH);
        returnstatus = (boolean)FALSE;
    }
    else if (canDrvObj->canController[MsgCntrlr].canControllerConfig_PC.CntrActive == (boolean)FALSE)
    {
        /* Can controller is not valid */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_WRITE_ID, (uint8)CAN_E_UNINIT);
        returnstatus = (boolean)FALSE;
    }
    else
    {
        /* MISRA C Compliance */
        returnstatus = (boolean)TRUE;
    }
    return returnstatus;
}

#endif

static Std_ReturnType Can_Write_Internal(uint8 MsgCntrlr, Can_HwHandleType HwHandle, Can_HwHandleType Hth,
                                         const Can_PduType *PduInfo)
{
    uint32         messageBox;
    Std_ReturnType status = E_OK;

    Can_DriverObj.canController[MsgCntrlr].canBusOffRecoveryStatus = (boolean)FALSE;
    /* Enter Critical Section */
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0();
    messageBox =
        Can_writeGetFreeMsgObj(&Can_DriverObj.canController[MsgCntrlr], &Can_DriverObj.canTxMessageObj[HwHandle]);

    status = Can_writeTxMailbox(&Can_DriverObj.canMailbox[Hth].mailBoxConfig, &Can_DriverObj.canController[MsgCntrlr],
                                messageBox, PduInfo);
    if (status == E_OK)
    {
        /* Decreases the Hardware Object Count. */
        Can_DriverObj.canTxMessageObj[HwHandle].freeHwObjectCount--;
    }
    /* Exit Critical Section */
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0();
    return status;
}

/*******************************************************************************
 *  API DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * Can_Init
 ******************************************************************************/
/*Requirements: SWS_Can_00291, SWS_Can_00021, SWS_Can_00250, SWS_Can_00053,
 * SWS_Can_00259, SWS_Can_00174, SWS_Can_00408, SWS_Can_00245,
 * SWS_Can_00407, SWS_Can_00104, SWS_Can_00026, SWS_Can_00056, SWS_Can_00255,
 *  SWS_Can_00246, SWS_Can_00238, SWS_Can_00220
 * SWS_Can_00239, SWS_Can_00240, SWS_Can_00244, SWS_Can_00419, SWS_Can_00091,
 * SWS_Can_00089, SWS_Can_00223, SWS_Can_00174, SWS_Can_00408, SWS_Can_00103,
 */
/*
 *Design : MCAL-16846, MCAL-16968, MCAL-16973, MCAL-16928, MCAL-17070, MCAL-16949, MCAL-17078,
 *MCAL-16918, MCAL-17015, MCAL-17059, MCAL-17108, MCAL-17115, MCAL-16938, MCAL-16935, MCAL-17056,
 *MCAL-16828, MCAL-16888, MCAL-17088
 */
FUNC(void, CAN_CODE) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_PBCFG) CfgPtr)
{
    uint8                 controller_cntr;
    const Can_ConfigType *ConfigPtr = CfgPtr;
#if (STD_ON == CAN_VARIANT_PRE_COMPILE)
    if (NULL_PTR == ConfigPtr)
    {
        ConfigPtr = &CAN_INIT_CONFIG_PC;
    }
#endif /* (STD_ON == CAN_VARIANT_PRE_COMPILE) */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if ((NULL_PTR == ConfigPtr) || (Can_CheckInitDet(ConfigPtr) == (boolean)FALSE))
    {
        /* Can config pointer is NOT valid */
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_INIT_ID,
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
    {
        Can_resetDrvObj(&Can_DriverObj);
        Can_initDrvObj(&Can_DriverObj, ConfigPtr);
        for (controller_cntr = 0U; controller_cntr < Can_DriverObj.canMaxControllerCount; controller_cntr++)
        {
            Can_Initialization(controller_cntr);
        }
        Can_DrvState = CAN_READY;
    }
}

#if (CAN_VERSION_INFO_API == STD_ON)
/*******************************************************************************
 * Can_GetVersionInfo
 ******************************************************************************/
/*Requirements: SWS_Can_00224, SWS_Can_00177 */
/*
 *Design: MCAL-17112
 */
FUNC(void, CAN_CODE)
Can_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) Can_VersionInfo)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_VersionInfo == NULL_PTR)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_VERSION_ID,
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif
    {
        Can_VersionInfo->vendorID         = (uint16)CAN_VENDOR_ID;
        Can_VersionInfo->moduleID         = (uint16)CAN_MODULE_ID;
        Can_VersionInfo->sw_major_version = (uint8)CAN_SW_MAJOR_VERSION;
        Can_VersionInfo->sw_minor_version = (uint8)CAN_SW_MINOR_VERSION;
        Can_VersionInfo->sw_patch_version = (uint8)CAN_SW_PATCH_VERSION;
    }
}
#endif

/*******************************************************************************
 * Can_SetBaudrate
 ******************************************************************************/
/*
 *Design : MCAL-17063, MCAL-17090, MCAL-17055, MCAL-16978, MCAL-17107, MCAL-17091
 */
/*Requirements: SWS_Can_00493,SWS_Can_00500, SWS_Can_00256,
 *SWS_Can_00062, SWS_Can_00260 , SWS_Can_00422*/
#if (CAN_SET_BAUDRATE_API == STD_ON)
FUNC(Std_ReturnType, CAN_CODE) Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    const Can_ControllerType_PC *canControllerCfg_PC;
    Std_ReturnType               status = E_NOT_OK;
    Can_BaudConfigType          *setBaud;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_SetBaudrateDet(Controller, &Can_DriverObj) == (boolean)FALSE)
    {
        /* Det Error is already reported */
    }
    else
#endif
    {
        SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0();
        canControllerCfg_PC = &Can_DriverObj.canController[Controller].canControllerConfig_PC;
        setBaud = Can_DriverObj.canController[Controller].canControllerConfig.BaudRateConfigList[BaudRateConfigID];

        if ((uint32)BaudRateConfigID > (Can_DriverObj.canController[Controller].maxBaudConfigID))
        {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETBAUDRATE_ID,
                                  (uint8)CAN_E_PARAM_BAUDRATE);
#endif
        }
        else
        {
            Can_mcanSetBaudrate(canControllerCfg_PC, setBaud);
            status = (Std_ReturnType)E_OK;
        }

        SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0();
    }
    return status;
}
#endif

/*******************************************************************************
 * Can_SetControllerMode
 ******************************************************************************/
/*Requirements: SWS_Can_00261, SWS_Can_00262, SWS_Can_00257, SWS_Can_00265 ,
 * SWS_Can_00267, SWS_Can_00230
 * SWS_Can_00017, SWS_Can_00384, SWS_Can_00196, SWS_Can_00425, SWS_Can_00197,
 * SWS_Can_00426, SWS_Can_00198,
 * SWS_Can_00199, SWS_Can_00200, SWS_Can_00039*/
/*
 *Design : MCAL-16897, MCAL-16952, MCAL-16981, MCAL-16835, MCAL-17024, MCAL-16946, MCAL-17073,
 *MCAL-16956, MCAL-17101, MCAL-17043, MCAL-17009, MCAL-17048, MCAL-17081, MCAL-16845, MCAL-17014,
 *MCAL-17050, MCAL-16851, MCAL-16992, MCAL-17099, MCAL-16990, MCAL-16937
 */
FUNC(Std_ReturnType, CAN_CODE)
Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*check for the validity of the controller parameter if det is enabled*/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_CheckSetControllerModeDet(Controller, &Can_DriverObj) == (boolean)FALSE)
    {
        /* Det Error is already reported */
    }
    else
#endif
    {
        switch (Transition)
        {
            case CAN_CS_STARTED:
            {
                retVal = Can_hwUnitStart(&Can_DriverObj.canController[Controller]);
                break;
            }

            case CAN_CS_STOPPED:
            {
                retVal = Can_hwUnitStop(&Can_DriverObj.canController[Controller], &Can_DriverObj.canMailbox[0],
                                        &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
                break;
            }

            case CAN_CS_SLEEP:
            {
                retVal = Can_hwUnitSleep(&Can_DriverObj.canController[Controller]);
                break;
            }

            default:
            {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
                retVal = E_NOT_OK;
                (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETCTR_ID,
                                      (uint8)CAN_E_TRANSITION);
#endif
                break;
            }
        }
    }

    return retVal;
}

/*******************************************************************************
 * Can_Write
 ******************************************************************************/
/*Requirements: SWS_Can_00233, SWS_Can_00059, SWS_Can_00276, SWS_Can_00011,
 * SWS_Can_00212, SWS_Can_00213, SWS_Can_00501
 * SWS_Can_00214, SWS_Can_00275, SWS_Can_00216, SWS_Can_00217, SWS_Can_00218,
 * SWS_Can_00219, SWS_Can_00505, SWS_Can_00506, SWS_Can_00486, SWS_Can_00502
 * */
/*
 *Design : MCAL-16996, MCAL-17037, MCAL-16983, MCAL-16884, MCAL-17086, MCAL-17066, MCAL-16907,
 *MCAL-17065, MCAL-17028, MCAL-16881, MCAL-17052, MCAL-17123, MCAL-17109, MCAL-16898, MCAL-17093,
 *MCAL-16940
 */
FUNC(Std_ReturnType, CAN_CODE) Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
    Std_ReturnType   status = E_OK;
    uint8            MsgCntrlr;
    Can_HwHandleType HwHandle;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_CheckWriteDet((uint32)Hth, PduInfo, &Can_DriverObj) == (boolean)FALSE)
    {
        status = E_NOT_OK;
    }
    else
#endif
    {
        HwHandle  = Can_DriverObj.canMailbox[Hth].mailBoxConfig.HwHandle;
        MsgCntrlr = Can_DriverObj.canMailbox[Hth].mailBoxConfig.Controller->ControllerId;
        Can_mcanCancelledMessagesReset(&Can_DriverObj.canController[MsgCntrlr], &Can_DriverObj.canMailbox[0],
                                       &Can_DriverObj.canTxMessageObj[0]);
        if (Can_DriverObj.canTxMessageObj[HwHandle].freeHwObjectCount == 0U)
        {
            status = CAN_BUSY;
        }
        else
        {
            /* CanSM has triggered a new write after L1 timeout. Stop the BusOff
             * recovery.
             * CanSM will trigger a new bus off recovery sequence. */

            if (MsgCntrlr < CAN_NUM_CONTROLLER)
            {
                status = Can_Write_Internal(MsgCntrlr, HwHandle, Hth, PduInfo);
            }
            else
            {
                status = E_NOT_OK;
            }
        }
    }
    return status;
}

/*******************************************************************************
 * Can_DisableControllerInterrupts
 ******************************************************************************/
/*Requirements: SWS_Can_00231, SWS_Can_00049, SWS_Can_00205, SWS_Can_00206,
 *SWS_Can_00204*/
/*
 *Design : MCAL-16963, MCAL-16838, MCAL-16853, MCAL-17030,
 */
FUNC(void, CAN_CODE) Can_DisableControllerInterrupts(uint8 Controller)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_CheckDisableDet(Controller, &Can_DriverObj) == (boolean)FALSE)
    {
        /* Det Error is already reported */
    }
    else
#endif
    {
        SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0();
#if (CAN_DEV_ERROR_DETECT == STD_ON)

        if ((Can_DriverObj.canController[Controller].canControllerConfig_PC.RxProcessingType ==
             CAN_TX_RX_PROCESSING_POLLING) &&
            (Can_DriverObj.canController[Controller].canControllerConfig_PC.TxProcessingType ==
             CAN_TX_RX_PROCESSING_POLLING))
        {
            (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_DIINT_ID,
                                  (uint8)CAN_E_PARAM_CONTROLLER);
        }
        else
#endif
        {
            Can_hwUnitDisableInterrupts(&Can_DriverObj.canController[Controller]);
        }
        SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0();
    }
}

/*******************************************************************************
 * Can_EnableControllerInterrupts
 ******************************************************************************/
/*Requirements: SWS_Can_00232, SWS_Can_00050, SWS_Can_00208, SWS_Can_00209,
 *SWS_Can_00210, SWS_Can_00033 */
/*
 *Design : MCAL-16982, MCAL-16894, MCAL-16908, MCAL-16979
 */
FUNC(void, CAN_CODE) Can_EnableControllerInterrupts(uint8 Controller)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_CheckEnableDet(Controller, &Can_DriverObj) == (boolean)FALSE)
    {
        /* Det Error is already reported */
    }
    else
#endif
    {
        SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0();
        Can_hwUnitEnableInterrupts(&Can_DriverObj.canController[Controller]);
        SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0();
    }
}

/*******************************************************************************
 * Can_MainFunction_Write
 ******************************************************************************/
/*Requirements: SWS_Can_00058, SWS_Can_00016, SWS_Can_00225, SWS_Can_00031,
 *SWS_Can_00178,SWS_Can_00179,SWS_Can_00441 */
/*
 *Design : MCAL-16910, MCAL-17083, MCAL-17068, MCAL-17082, MCAL-16844, MCAL-17067, MCAL-16911
 */
#if (CAN_TX_POLLING == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_Write(void)
{
    uint8                  ctlrIndx;
    Can_TxRxProcessingType txProcessingType;
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0();
    for (ctlrIndx = 0U; ctlrIndx < (uint8)CAN_NUM_CONTROLLER; ctlrIndx++)
    {
        txProcessingType = Can_DriverObj.canController[ctlrIndx].canControllerConfig_PC.TxProcessingType;
        /* only for the Tx Mailbox */
        if (txProcessingType != CAN_TX_RX_PROCESSING_INTERRUPT)
        {
            if (Can_DriverObj.canController[ctlrIndx].canControllerConfig_PC.CntrActive == (boolean)TRUE)
            {
                Can_mcanProcessTx(&Can_DriverObj.canController[ctlrIndx], &Can_DriverObj.canMailbox[0U],
                                  &Can_DriverObj.canTxMessageObj[0], POLLING_MASK);
            }
        }
    }
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0();
}
#endif

/*******************************************************************************
 * Can_CheckWakeup
 ******************************************************************************/
/*Requirements: SWS_Can_00360, SWS_Can_00361, SWS_Can_00362, SWS_Can_00363,
 *SWS_Can_00485 */
/* Design : CAN_DesignId_011 */
#if (CAN_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(Std_ReturnType, CAN_CODE) Can_CheckWakeup(uint8 Controller)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    return retVal;
}
#endif

/*******************************************************************************
 * Can_MainFunction_Wakeup
 ******************************************************************************/
/*Requirements: SWS_Can_00270, SWS_Can_00271, SWS_Can_00269, SWS_Can_00228,
 *SWS_Can_00112, SWS_Can_00185, SWS_Can_00186*/
/* Design : CAN_DesignId_017 */
#if (CAN_WAKEUP_POLLING == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_Wakeup(void)
{ /*Dummy Function*/
}
#endif /* #if (CAN_WAKEUP_POLLING == STD_ON) */

/*******************************************************************************
 * Can_MainFunction_BusOff
 ******************************************************************************/
/*Requirements:SWS_Can_00280, SWS_Can_00007, SWS_Can_00227, SWS_Can_00109,
 *SWS_Can_00183, SWS_Can_00184 */
/*
 *Design : MCAL-16965, MCAL-16857, MCAL-16864, MCAL-17094, MCAL-16904, MCAL-17062, MCAL-16840,
 *MCAL-17113, MCAL-16939, MCAL-17072, MCAL-17017, MCAL-17105
 */
#if (CAN_BUSOFF_POLLING == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_BusOff(void)
{
    uint8 controller_cntr;

    for (controller_cntr = 0U; controller_cntr < Can_DriverObj.canMaxControllerCount; controller_cntr++)
    {
        /* If the controller is not activated just skip its checking */
        if (Can_DriverObj.canController[controller_cntr].canControllerConfig_PC.CntrActive == (boolean)TRUE)
        {
            Can_MainFunction_BusOffProcess(&Can_DriverObj.canController[controller_cntr], &Can_DriverObj.canMailbox[0U],
                                           &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
        }
    }
}
#endif /* #if (CAN_BUSOFF_POLLING == STD_ON) */

/*******************************************************************************
 * Can_MainFunction_Mode
 ******************************************************************************/
/*Requirements:SWS_Can_00370, SWS_Can_00373, SWS_Can_00368, SWS_Can_00369,
 * SWS_Can_00379, SWS_Can_00372 */
/*
 *Design : MCAL-16974, MCAL-16999, MCAL-16975, MCAL-16957
 */
FUNC(void, CAN_CODE) Can_MainFunction_Mode(void)
{
    uint8 controller_cntr;

    for (controller_cntr = 0U; controller_cntr < Can_DriverObj.canMaxControllerCount; controller_cntr++)
    {
        Can_MainFunction_ModeProcess(&Can_DriverObj.canController[controller_cntr]);
    }
}

/*******************************************************************************
 * Can_MainFunction_Read
 ******************************************************************************/
/*Requirements: SWS_Can_00396, SWS_Can_00395, SWS_Can_00007, SWS_Can_00226,
 * SWS_Can_00108, SWS_Can_00180, SWS_Can_00181
 * SWS_Can_00442 , SWS_Can_00423 */
/*
 *Design : MCAL-16960, MCAL-17074, MCAL-16859, MCAL-17118, MCAL-16874, MCAL-17120, MCAL-17045
 */
#if (CAN_RX_POLLING == STD_ON)
FUNC(void, CAN_CODE) Can_MainFunction_Read(void)
{
    SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0();
    uint32                 loopCnt;
    Can_TxRxProcessingType rxProcessingType;

    for (loopCnt = 0U; loopCnt < CAN_NUM_CONTROLLER; loopCnt++)
    {
        rxProcessingType = Can_DriverObj.canController[loopCnt].canControllerConfig_PC.RxProcessingType;
        /* only for the Tx Mailbox */
        if (rxProcessingType != CAN_TX_RX_PROCESSING_INTERRUPT)
        {
            if (Can_DriverObj.canController[loopCnt].canControllerConfig_PC.CntrActive == (boolean)TRUE)
            {
                /* Read Messages stored in  buffers */
                Can_mcanReadRxBuff(&Can_DriverObj.canController[loopCnt], (uint32)POLLING_MASK);
                /* Empty FIFO messages */
                Can_mcanReadRxFIFO(&Can_DriverObj.canController[loopCnt], MCAN_RX_FIFO_NUM_1);
            }
        }
    }
    SchM_Exit_Can_CAN_EXCLUSIVE_AREA_0();
}
#endif /* #if (CAN_RX_POLLING == STD_ON) */

#if (CAN_LOOPBACK_ENABLE == STD_ON)
/*******************************************************************************
 * Can_TestLoopBackModeEnable
 ******************************************************************************/
/*
 *Design: MCAL-17136
 */
FUNC(Std_ReturnType, CAN_CODE) Can_TestLoopBackModeEnable(uint8 controller, uint8 mode)
{
    uint32 baseAddr;
    VAR(Std_ReturnType, AUTOMATIC) retVal;

    retVal = (Std_ReturnType)E_NOT_OK;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_DrvState == CAN_READY)
#endif
    {
        if ((controller < (Can_DriverObj.canMaxControllerCount)) && (mode < 2U))
        {
            baseAddr = Can_DriverObj.canController[controller].canControllerConfig_PC.CntrAddr;
            retVal   = Can_hwUnitTestLoopBackModeEnable(baseAddr, mode);
        }
    }
    return (retVal);
}

/*******************************************************************************
 * Can_TestLoopBackModeDisable
 ******************************************************************************/
/*
 *Design : MCAL-23125
 */
FUNC(Std_ReturnType, CAN_CODE) Can_TestLoopBackModeDisable(uint8 controller, uint8 mode)
{
    uint32 baseAddr;
    VAR(Std_ReturnType, AUTOMATIC) retVal;

    retVal = (Std_ReturnType)E_NOT_OK;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_DrvState == CAN_READY)
#endif
    {
        if ((controller < (Can_DriverObj.canMaxControllerCount)) && (mode < 2U))
        {
            baseAddr = Can_DriverObj.canController[controller].canControllerConfig_PC.CntrAddr;
            retVal   = Can_hwUnitTestLoopBackModeDisable(baseAddr, mode);
        }
    }
    return (retVal);
}
#endif

/*******************************************************************************
 * Can_RegisterReadback
 ******************************************************************************/
/*
 * Design: MCAL-21536, MCAL-21537, MCAL-23132
 */
#if (STD_ON == CAN_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CAN_CODE)
Can_RegisterReadback(VAR(uint8, AUTOMATIC) Controller,
                     P2VAR(Can_RegisterReadbackType, AUTOMATIC, CAN_APPL_DATA) RegRbPtr)
{
    uint32         baseAddr;
    Std_ReturnType retVal;
    retVal = (Std_ReturnType)E_NOT_OK;
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_REGISTER_READBACK_ID,
                              (uint8)CAN_UNINIT);
    }
    else if (NULL_PTR == RegRbPtr)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_REGISTER_READBACK_ID,
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif /* #if (STD_ON == CAN_DEV_ERROR_DETECT) */
    {
        if (Controller < (Can_DriverObj.canMaxControllerCount))
        {
            baseAddr = Can_DriverObj.canController[Controller].canControllerConfig_PC.CntrAddr;
            retVal   = Can_HWRegisterReadback(RegRbPtr, baseAddr);
        }
    }
    return (retVal);
}
#endif

/*
 *Design : MCAL-16936, MCAL-17000, MCAL-17026, MCAL-17140
 */
#if (CAN_DEINIT_API == STD_ON)
/* [SWS_Can_91002],[SWS_Can_ 91009],[SWS_Can_91010],[SWS_Can_91011] */
FUNC(void, CAN_CODE) Can_DeInit(void)
{
    uint8 controllerIdx;
    uint8 tmpStatus = (uint8)E_OK;
#if (STD_ON == CAN_DEV_ERROR_DETECT)
    if (Can_DrvState != CAN_READY)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_DEINIT_ID,
                              (uint8)CAN_E_TRANSITION);
    }
    else
#endif /* #if (STD_ON == CAN_DEV_ERROR_DETECT) */
    {
        /* Check if any of the CAN controllers is in state STARTED */
        for (controllerIdx = 0U; controllerIdx < Can_DriverObj.canMaxControllerCount; controllerIdx++)
        {
            if (Can_DriverObj.canController[controllerIdx].canState == CAN_CS_STARTED)
            {
                tmpStatus = (uint8)E_NOT_OK;
                break;
            }
        }
        if (tmpStatus == (uint8)E_OK)
        {
            for (controllerIdx = 0U; controllerIdx < Can_DriverObj.canMaxControllerCount; controllerIdx++)
            {
                Can_DriverObj.canController[controllerIdx].canState = CAN_CS_UNINIT;
                Can_hwDeInit(&Can_DriverObj.canController[controllerIdx]);
            }
            Can_DrvState = CAN_UNINIT;
            Can_resetDrvObj(&Can_DriverObj);
        }
        else
        {
#if (STD_ON == CAN_DEV_ERROR_DETECT)
            (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_DEINIT_ID,
                                  (uint8)CAN_E_TRANSITION);
#endif /* #if (STD_ON == CAN_DEV_ERROR_DETECT) */
        }
    }
}
#endif /* (CAN_DEINIT_API == STD_ON) */

/* [SWS_Can_91004], [SWS_Can_91005], [SWS_Can_91006], [SWS_Can_91007],
   [SWS_Can_91008] */
/*
 *Design: MCAL-16917, MCAL-16889, MCAL-16927, MCAL-16997, MCAL-17098, MCAL-17141
 */
/*******************************************************************************
 * Can_GetControllerErrorState
 ******************************************************************************/
FUNC(Std_ReturnType, CAN_CODE)
Can_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr)
{
    Std_ReturnType     retVal = (Std_ReturnType)E_NOT_OK;
    Can_ErrorStateType errorState;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_GETCTRERRST_ID,
                              (uint8)CAN_E_UNINIT);
    }
    else if (ControllerId >= (Can_DriverObj.canMaxControllerCount))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_GETCTRERRST_ID,
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }
    else if (ErrorStatePtr == NULL_PTR)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_GETCTRERRST_ID,
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif
    {
        retVal         = (Std_ReturnType)E_OK;
        errorState     = Can_mcanGetProtocolStatus(&Can_DriverObj.canController[ControllerId]);
        *ErrorStatePtr = errorState;
    }

    return retVal;
}

/*******************************************************************************
 * Can_GetControllerMode
 ******************************************************************************/
/* [SWS_Can_91014][SWS_Can_91015],[SWS_Can_91016],[SWS_Can_91017],
   [SWS_Can_91018] */
/*
 *Design: MCAL-16966, MCAL-17143, MCAL-16903, MCAL-17142, MCAL-16986
 */
FUNC(Std_ReturnType, CAN_CODE)
Can_GetControllerMode(uint8 Controller, Can_ControllerStateType *ControllerModePtr)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (Can_DrvState == CAN_UNINIT)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_GETCTRMODE_ID,
                              (uint8)CAN_E_UNINIT);
    }
    else if (Controller >= (Can_DriverObj.canMaxControllerCount))
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_GETCTRMODE_ID,
                              (uint8)CAN_E_PARAM_CONTROLLER);
    }
    else if (ControllerModePtr == NULL_PTR)
    {
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_GETCTRMODE_ID,
                              (uint8)CAN_E_PARAM_POINTER);
    }
    else
#endif
    {
        retVal             = (Std_ReturnType)E_OK;
        *ControllerModePtr = Can_DriverObj.canController[Controller].canState;
    }

    return retVal;
}

#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"
/*******************************************************************************
 * INTERRUPT SERVICE ROUTINES
 ******************************************************************************/
/*
 *Design: MCAL-17116, MCAL-16882
 */
#define CAN_START_SEC_ISR_CODE
#include "Can_MemMap.h"
#if defined(CAN_CONTROLLER_MCAN0)
/*******************************************************************************
 * Can_0_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_0_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN0];

    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

#if (STD_ON == CAN_ECC_ENABLE)
/*******************************************************************************
 * Can_0_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/*
 *Design : CAN_DesignId_026
 */
FUNC(void, CAN_CODE) Can_0_Int1ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN0];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
}
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN1)
/*******************************************************************************
 * Can_1_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_1_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN1];
    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

#if (STD_ON == CAN_ECC_ENABLE)
/*******************************************************************************
 * Can_1_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/*Requirements : SWS_Can_00033*/
/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_1_Int1ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN1];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
}
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN2)
/*******************************************************************************
 * Can_2_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_2_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN2];

    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

#if (STD_ON == CAN_ECC_ENABLE)
/*******************************************************************************
 * Can_2_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_2_Int1ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN2];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
}
#endif
#endif

#if defined(CAN_CONTROLLER_MCAN3)
/*******************************************************************************
 * Can_3_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_3_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN3];

    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

#if (STD_ON == CAN_ECC_ENABLE)
/*******************************************************************************
 * Can_3_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_3_Int1ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN3];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
}
#endif
#endif
#if defined(CAN_CONTROLLER_MCAN4)
/*******************************************************************************
 * Can_4_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_4_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN4];

    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

/*******************************************************************************
 * Can_4_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_4_Int1ISR_Fun(void)
{
#if (STD_ON == CAN_ECC_ENABLE)
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN4];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
#endif
}
#endif
#if defined(CAN_CONTROLLER_MCAN5)
/*******************************************************************************
 * Can_5_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_5_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN5];

    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

/*******************************************************************************
 * Can_5_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_5_Int1ISR_Fun(void)
{
#if (STD_ON == CAN_ECC_ENABLE)
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN5];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
#endif
}
#endif
#if defined(CAN_CONTROLLER_MCAN6)
/*******************************************************************************
 * Can_6_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_6_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN6];

    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

/*******************************************************************************
 * Can_6_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_6_Int1ISR_Fun(void)
{
#if (STD_ON == CAN_ECC_ENABLE)
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN6];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
#endif
}
#endif
#if defined(CAN_CONTROLLER_MCAN7)
/*******************************************************************************
 * Can_7_Int0ISR_Fun
 ******************************************************************************/

/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_7_Int0ISR_Fun(void)
{
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN7];

    Can_mcanProcessISR(&Can_DriverObj.canController[ctrlId], &Can_DriverObj.canMailbox[0],
                       &Can_DriverObj.canTxMessageObj[0], Can_DriverObj.maxMbCnt);
}

/*******************************************************************************
 * Can_7_Int1ISR_Fun
 ******************************************************************************/

/*Requirements : SWS_Can_00033*/
/* Design : CAN_DesignId_026 */
FUNC(void, CAN_CODE) Can_7_Int1ISR_Fun(void)
{
#if (STD_ON == CAN_ECC_ENABLE)
    uint32 ctrlId = Can_DriverObj.controllerIDMap[CAN_CONTROLLER_INSTANCE_MCAN7];
    Can_mcanProcessECCISR(&Can_DriverObj.canController[ctrlId]);
#endif
}
#endif

#define CAN_STOP_SEC_ISR_CODE
#include "Can_MemMap.h"

/*******************************************************************************
 *  End of File: Can.c
 ******************************************************************************/
