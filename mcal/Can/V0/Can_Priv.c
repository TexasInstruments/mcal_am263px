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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "string.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include "EcuM_Cbk.h"
/* #include "Os.h" */
#include "SchM_Can.h"
#include "Can_Priv.h"

#if (CAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "soc.h"
#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/* Memory mapping, done via MemMap.h: Code */
#define CAN_START_SEC_CODE
#include "Can_MemMap.h"
/*
 *Design: MCAL-17134
 */
void Can_mcanWkUp(Can_ControllerObjType *controllerObj)
{
    boolean         timeOut = (boolean)FALSE;
    uint32          baseAddr;
    volatile uint32 tempCount = CAN_TIMEOUT_DURATION;
    if (CAN_TIMEOUT_DURATION > 8U)
    {
        tempCount = CAN_TIMEOUT_DURATION / 8U;
    }

    baseAddr = controllerObj->canControllerConfig_PC.CntrAddr;
    /* Deactivate Local Power down */
    MCAN_addClockStopRequest(baseAddr, (uint32)FALSE);

    /* Wait for FSM to to come out of reset */
    while ((uint32)MCAN_CCCR_CSA_NO_ACK != MCAN_getClkStopAck(baseAddr))
    {
        /* Below API can change start time, so use temp variable */
        if (tempCount <= 0U)
        {
            /* timeout */
            timeOut = (boolean)TRUE;
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
    if (timeOut == (boolean)TRUE)
    {
#ifdef CAN_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus(CAN_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    controllerObj->canState = CAN_CS_STOPPED;
    CanIf_ControllerModeIndication(controllerObj->canControllerConfig_PC.ControllerId, CAN_CS_STOPPED);
    controllerObj->canBusOffRecoveryStatus = (boolean)FALSE;
}

/*******************************************************************************
 * Can_hwUnitStart
 ******************************************************************************/
/*! \brief      This function will start the CAN node.
 *
 ******************************************************************************/
/*Requirements: SWS_Can_00409,  */
Std_ReturnType Can_hwUnitStart(Can_ControllerObjType *controllerObj)
{
    Std_ReturnType retVal = E_NOT_OK;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    if (controllerObj->canState != CAN_CS_STOPPED)
    {
        retVal = E_NOT_OK;
        (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETCTR_ID,
                              (uint8)CAN_E_TRANSITION);
    }
    else
#endif

    {
        /* Need to call MCAN wake up before the START to take care if there
           was a SLEEP state before*/
        Can_mcanWkUp(controllerObj);
        retVal = Can_mcanStart(controllerObj);
    }
    return retVal;
}

/*******************************************************************************
 * Can_hwUnitStop
 ******************************************************************************/
/*! \brief      This function will stop the CAN node.
 *
 ******************************************************************************/
/*Requirements: SWS_Can_00263, SWS_Can_00410, SWS_Can_00264*/
Std_ReturnType Can_hwUnitStop(Can_ControllerObjType *controllerObj, Can_MailboxObjType *canMailbox,
                              Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (controllerObj->canState == CAN_CS_STOPPED)
    {
        CanIf_ControllerModeIndication(controllerObj->canControllerConfig_PC.ControllerId, CAN_CS_STOPPED);
        retVal = E_OK;
    }
    else
    {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        if ((controllerObj->canState == CAN_CS_STARTED) || (controllerObj->canState == CAN_CS_SLEEP))
        {
            retVal = Can_mcanStop(controllerObj, canMailbox, canTxMessageObj, maxMbCnt);
        }
        else
        {
            retVal = E_NOT_OK;
            (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETCTR_ID,
                                  (uint8)CAN_E_TRANSITION);
        }
#else
        {
            retVal = Can_mcanStop(controllerObj, canMailbox, canTxMessageObj, maxMbCnt);
        }
#endif
    }
    return retVal;
}

/*******************************************************************************
 * Can_hwUnitSleep
 ******************************************************************************/
/*! \brief      This function will sleep the CAN node.
 *
 ******************************************************************************/
/*Requirements: SWS_Can_00258, SWS_Can_00404, SWS_Can_00266, SWS_Can_00411*/
Std_ReturnType Can_hwUnitSleep(Can_ControllerObjType *controllerObj)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (controllerObj->canState == CAN_CS_SLEEP)
    {
        CanIf_ControllerModeIndication(controllerObj->canControllerConfig_PC.ControllerId, CAN_CS_SLEEP);
        retVal = E_OK;
    }
    else
    {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
        if (controllerObj->canState != CAN_CS_STOPPED)
        {
            retVal = E_NOT_OK;
            (void)Det_ReportError((uint16)CAN_MODULE_ID, (uint8)CAN_INSTANCE_ID, (uint8)CAN_SETCTR_ID,
                                  (uint8)CAN_E_TRANSITION);
        }
        else
#endif
        {
            retVal = Can_mcanSleep(controllerObj);
        }
    }

    return retVal;
}

Std_ReturnType Can_writeTxMailbox(const Can_MailboxType *mailboxCfg, Can_ControllerObjType *controllerObj,
                                  uint32 messageBox, const Can_PduType *PduInfo)
{
    Std_ReturnType status;
    status = Can_mcanWriteTxMailbox(mailboxCfg, controllerObj, messageBox, PduInfo);
    return status;
}

void Can_hwUnitDisableInterrupts(Can_ControllerObjType *controllerObj)
{
    Can_mcanDisableInterrupts(controllerObj);
}

void Can_hwUnitEnableInterrupts(Can_ControllerObjType *controllerObj)
{
    Can_mcanEnableInterrupts(controllerObj);
}

void Can_MainFunction_BusOffProcess(Can_ControllerObjType *controllerObj, Can_MailboxObjType *canMailbox,
                                    Can_MailboxObjTxType *canTxMessageObj, uint32 maxMbCnt)
{
    Can_mcanProcessBusOff(controllerObj, canMailbox, canTxMessageObj, maxMbCnt);
}

void Can_MainFunction_ModeProcess(Can_ControllerObjType *canController)
{
    Can_mcan_ModeProcess(canController);
}

Std_ReturnType Can_hwUnitTestLoopBackModeEnable(uint32 baseAddr, uint8 mode)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal;
    retVal = Can_mcanTestLoopBackModeEnable(baseAddr, mode);
    return retVal;
}

Std_ReturnType Can_hwUnitTestLoopBackModeDisable(uint32 baseAddr, uint8 mode)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal;

    retVal = Can_mcanTestLoopBackModeDisable(baseAddr, mode);
    return retVal;
}

#if (STD_ON == CAN_REGISTER_READBACK_API)
Std_ReturnType Can_HWRegisterReadback(Can_RegisterReadbackType *RegRbPtr, uint32 baseAddr)
{
    Std_ReturnType retVal;
    /* Read configuration registers value */
    RegRbPtr->CanReadBackRegPID   = HW_RD_REG32(baseAddr + (uint32)MCAN_MCANSS_PID);
    RegRbPtr->CanReadBackRegSTAT  = HW_RD_REG32(baseAddr + (uint32)MCAN_MCANSS_STAT);
    RegRbPtr->CanReadBackRegCREL  = HW_RD_REG32(baseAddr + (uint32)MCAN_CREL);
    RegRbPtr->CanReadBackRegENDN  = HW_RD_REG32(baseAddr + (uint32)MCAN_ENDN);
    RegRbPtr->CanReadBackRegCTRL  = HW_RD_REG32(baseAddr + (uint32)MCAN_MCANSS_CTRL);
    RegRbPtr->CanReadBackRegDBTP  = HW_RD_REG32(baseAddr + (uint32)MCAN_DBTP);
    RegRbPtr->CanReadBackRegRWD   = HW_RD_REG32(baseAddr + (uint32)MCAN_RWD);
    RegRbPtr->CanReadBackRegCCCR  = HW_RD_REG32(baseAddr + (uint32)MCAN_CCCR);
    RegRbPtr->CanReadBackRegNBTP  = HW_RD_REG32(baseAddr + (uint32)MCAN_NBTP);
    RegRbPtr->CanReadBackRegTDCR  = HW_RD_REG32(baseAddr + (uint32)MCAN_TDCR);
    RegRbPtr->CanReadBackRegGFC   = HW_RD_REG32(baseAddr + (uint32)MCAN_GFC);
    RegRbPtr->CanReadBackRegSIDFC = HW_RD_REG32(baseAddr + (uint32)MCAN_SIDFC);
    RegRbPtr->CanReadBackRegXIDFC = HW_RD_REG32(baseAddr + (uint32)MCAN_XIDFC);
    RegRbPtr->CanReadBackRegRXF0C = HW_RD_REG32(baseAddr + (uint32)MCAN_RXF0C);
    RegRbPtr->CanReadBackRegRXBC  = HW_RD_REG32(baseAddr + (uint32)MCAN_RXBC);
    RegRbPtr->CanReadBackRegRXF1C = HW_RD_REG32(baseAddr + (uint32)MCAN_RXF1C);
    RegRbPtr->CanReadBackRegTXBC  = HW_RD_REG32(baseAddr + (uint32)MCAN_TXBC);
    RegRbPtr->CanReadBackRegTXESC = HW_RD_REG32(baseAddr + (uint32)MCAN_TXESC);
    RegRbPtr->CanReadBackRegTXEFC = HW_RD_REG32(baseAddr + (uint32)MCAN_TXEFC);
    retVal                        = (Std_ReturnType)E_OK;

    return retVal;
}
#endif

#if (CAN_DEINIT_API == STD_ON)
void Can_hwDeInit(const Can_ControllerObjType *canController)
{
    Can_mcanHwDeInit(canController);
}
#endif

/* Memory mapping, done via MemMap.h: Code */
#define CAN_STOP_SEC_CODE
#include "Can_MemMap.h"
/*******************************************************************************
 *  End of File: Can_priv.c
 ******************************************************************************/
