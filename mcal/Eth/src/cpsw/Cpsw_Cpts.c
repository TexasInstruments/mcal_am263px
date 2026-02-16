/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *   \file  Cpsw_Cpts.c
 *
 *   CPTS module implementation
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Eth_Cfg.h"
#include "string.h"
#include "Std_Types.h"
#include "Cpsw_Hw.h"
#include "SchM_Eth.h"
#include "Eth_Priv.h"
#include "Cpsw_Priv.h"
#include "Cpsw.h"
#include "Cpsw_Cpts.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * Below are reset values used for VLAN tags which are used to configure
 * time stamping on VLAN enabled packets. INNER is first level tag and
 * OUTER is level2. If you want to use different, change below macros.
 */
#define CPSW_VLAN_LTYPE_VLAN_OUTER (0x000088A8U)
#define CPSW_VLAN_LTYPE_VLAN_INNER (0x00008100U)

/* Sequence ID offset and other configuration for PORT */
#define CPSW_P_TS_SEQ_ID_OFFSET (0x0000001EU)

/* Macros for time conversions */
#define NSEC_PER_SEC           (1000000000ULL)
#define TIME_SYNC_SECONDS_HIGH (0x100000000ULL)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void CpswCpts_configPort(CpswCpts_StateObj *pCptsStateObj, uint8 portNum);

static void CpswCpts_initEventQueue(CpswCpts_StateObj *pCptsStateObj);

static void CpswCpts_initHw(CpswCpts_StateObj *pCptsStateObj);

static uint64 CpswCpts_getTimestamp(uint32 baseAddr);

static uint64 CpswCpts_readHwTimestamp(CpswCpts_StateObj *pCptsStateObj);

static void CpswCpts_enableIntr(uint32 baseAddr);

static void CpswCpts_disableIntr(uint32 baseAddr);

static CpswCpts_Event *CpswCpts_lookupEvent(CpswCpts_StateObj *pCptsStateObj, const CpswCpts_Event *pEventTemplate);

static CpswCpts_Event *CpswCpts_getCurrentEventQueue(CpswCpts_StateObj *pCptsStateObj, uint8 eventType);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define ETH_START_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Std_ReturnType CpswCpts_init(uint32 baseAddr, CpswCpts_StateObj *pCptsStateObj, const Eth_CptsConfigType *pCptsConfig,
                             uint8 portIdx)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    /* Zero init the CpswCpts_StateObj structure */
    (void)memset((void *)pCptsStateObj, 0, (size_t)sizeof(CpswCpts_StateObj));

    pCptsStateObj->portNum = portIdx;

    (void)memcpy(&pCptsStateObj->cptsCfg, pCptsConfig, sizeof(Eth_CptsConfigType));

    /* Initialize the free event queue */
    CpswCpts_initEventQueue(pCptsStateObj);

    pCptsStateObj->cpswBaseAddr = baseAddr;

    /* Save the input frequency value */
    pCptsStateObj->cptsInputFreq = pCptsConfig->cptsInputFreq;

    /* Enable the CPTS module */
    CPTS_WR_FIELD(CONTROL, CPTS_EN, 1U);
    CPTS_WR_FIELD(CONTROL, MODE, 1U);
    CPTS_WR_FIELD(CONTROL, TSTAMP_EN, 0U);
    CPTS_WR_FIELD(TS_ADD_VAL, ADD_VAL, 4U);

    /* Enable the CPTS interrupt by setting the enable bit */
    CpswCpts_enableIntr(baseAddr);

    /* Enable the EVNT misc interrupt */
    Cpsw_enableMiscIntr(baseAddr, (uint32)CPSW_SS_MISC_EN_EVT_PEND);

    /* Init CPTS HW module with user provided configuration */
    CpswCpts_initHw(pCptsStateObj);

    return retVal;
}

void CpswCpts_deinit(uint32 baseAddr)
{
    /* Disable the EVNT misc interrupt in the wrapper module */
    Cpsw_disableMiscIntr(baseAddr, (uint32)CPSW_SS_MISC_EN_EVT_PEND);
    CpswCpts_disableIntr(baseAddr);

    /* Disable the CPTS Module */
    CPTS_WR_FIELD(CONTROL, CPTS_EN, 0U);
}

void CpswCpts_handleEvents(CpswCpts_StateObj *pCptsStateObj)
{
    uint8           eventType   = CPTS_EVENT_INVALID;
    uint32          baseAddr    = pCptsStateObj->cpswBaseAddr;
    CpswCpts_Event *pEvent      = (CpswCpts_Event *)NULL_PTR;
    volatile uint32 eventFields = 0U;

    /* Read event info from CPTS hardware register */
    eventFields = CPTS_RD_REG(EVENT_1);

    /* Get event type */
    eventType = (uint8)CPTS_GET_FIELD(eventFields, EVENT_1, EVENT_TYPE);

    /* For Eth_getIngress/EgressTimestamp(), only handle RX, TX event */
    pEvent = CpswCpts_getCurrentEventQueue(pCptsStateObj, eventType);
    if (NULL_PTR != pEvent)
    {
        pEvent->eventType   = (uint8)CPTS_GET_FIELD(eventFields, EVENT_1, EVENT_TYPE);
        pEvent->messageType = (uint8)CPTS_GET_FIELD(eventFields, EVENT_1, MESSAGE_TYPE);
        pEvent->sequenceId  = (uint16)CPTS_GET_FIELD(eventFields, EVENT_1, SEQUENCE_ID);
        pEvent->portNumber  = (uint16)CPTS_GET_FIELD(eventFields, EVENT_1, PORT_NUMBER);

        /* Get timestamp */
        pEvent->timeStamp = CpswCpts_getTimestamp(baseAddr);

        /* Update valid flag */
        pEvent->valid = TRUE;
    }
    else
    {
        /* skip other CPTS event */
    }

    /* Set the EVENT_POP field (bit 0) of the CPTS_EVENT_POP register to pop the
     * previously read value off of the event FIFO. */
    CPTS_WR_FIELD(EVENT_POP, EVENT_POP, 1U);
}

Std_ReturnType CpswCpts_readEthEventTimestamp(CpswCpts_StateObj *pCptsStateObj, uint64 *tsVal,
                                              const CpswCpts_Event *pEeventTemplate)
{
    Std_ReturnType  retVal = (Std_ReturnType)E_OK;
    CpswCpts_Event *pEvent = (CpswCpts_Event *)NULL_PTR;

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

    if ((uint32)0U != CpswCpts_getEventPendStatus(pCptsStateObj->cpswBaseAddr))
    {
        /* Pop the event into SW queue to be returned to when
         * Eth_GetIngressTimeStamp is called from EthIf_RxIndication */
        CpswCpts_handleEvents(pCptsStateObj);
    }

    pEvent = CpswCpts_lookupEvent(pCptsStateObj, pEeventTemplate);
    if (NULL_PTR != pEvent)
    {
        *tsVal = pEvent->timeStamp;
    }
    else
    {
        *tsVal = 0U;
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    return retVal;
}

Std_ReturnType CpswCpts_readTimestamp(CpswCpts_StateObj *pCptsStateObj, uint64 *tsVal)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    /* read timestamp value */
    *tsVal = CpswCpts_readHwTimestamp(pCptsStateObj);

    if ((uint64)0U == *tsVal)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

void CpswCpts_getSysTime(const uint64 *nsec, Eth_TimeStampType *pTimestamp)
{
    uint64 temp64bit = 0ULL;

    pTimestamp->nanoseconds = (uint32)((*nsec % NSEC_PER_SEC));
    temp64bit               = *nsec / NSEC_PER_SEC;
    pTimestamp->seconds     = (uint32)(temp64bit % TIME_SYNC_SECONDS_HIGH);
    pTimestamp->secondsHi   = (uint16)(temp64bit / TIME_SYNC_SECONDS_HIGH);
}

uint32 CpswCpts_getEventPendStatus(uint32 baseAddr)
{
    /* Check pending event interrupt
     * Note - To check multiple events, application should wait for an amount
     * of time greater than four CPTS_RFT_CLK periods plus four MAIN_CLK periods */
    return CPTS_RD_FIELD(INTSTAT_RAW, TS_PEND_RAW);
}

/* ========================================================================== */
/*                    Static Function Definitions                             */
/* ========================================================================== */

static void CpswCpts_initEventQueue(CpswCpts_StateObj *pCptsStateObj)
{
    uint32 eventIdx;

    for (eventIdx = 0u; eventIdx < ETH_CPTS_EVENT_CNT; ++eventIdx)
    {
        pCptsStateObj->rxQueue.event[eventIdx].valid = FALSE;
        pCptsStateObj->txQueue.event[eventIdx].valid = FALSE;
    }
    pCptsStateObj->rxQueue.idx = 0U;
    pCptsStateObj->txQueue.idx = 0U;
}

static CpswCpts_Event *CpswCpts_getCurrentEventQueue(CpswCpts_StateObj *pCptsStateObj, uint8 eventType)
{
    CpswCpts_Event *pEvent = (CpswCpts_Event *)NULL_PTR;

    if (CPTS_EVENT_ETHERNET_RECEIVE == eventType)
    {
        /* Get current free event pointer */
        pEvent = &pCptsStateObj->rxQueue.event[pCptsStateObj->rxQueue.idx];

        /* Next event index */
        pCptsStateObj->rxQueue.idx++;
        pCptsStateObj->rxQueue.idx %= ETH_CPTS_EVENT_CNT;
    }
    else if (CPTS_EVENT_ETHERNET_TRANSMIT == eventType)
    {
        /* Get current free cache pointer */
        pEvent = &pCptsStateObj->txQueue.event[pCptsStateObj->txQueue.idx];

        /* Next event index */
        pCptsStateObj->txQueue.idx++;
        pCptsStateObj->txQueue.idx %= ETH_CPTS_EVENT_CNT;
    }
    else
    {
        /* nothing */
    }

    return pEvent;
}

static uint8 CpswCpts_getEventType(uint32 baseAddr)
{
    /* Read event info from CPTS hardware register */
    return (uint8)CPTS_RD_FIELD(EVENT_1, EVENT_TYPE);
}

static void CpswCpts_configPort(CpswCpts_StateObj *pCptsStateObj, uint8 portNum)
{
    Eth_CptsConfigType *pCptsCfg = &pCptsStateObj->cptsCfg;
    uint32              baseAddr = pCptsStateObj->cpswBaseAddr;

    /* Enable all message types */
    if ((uint32)ETH_CPTS_MESSAGE_ALL == pCptsCfg->msgTypeCfg)
    {
        ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_MSG_TYPE_EN, CPSW_ETH_PN_TS_CTL_REG_TS_MSG_TYPE_EN_MAX);
    }
    else
    {
        ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_MSG_TYPE_EN, pCptsCfg->msgTypeCfg);
    }

    /* Make sure Sequence ID offset is correct */
    ETH_PN_WR_PORT_FIELD(TS_SEQ_LTYPE, portNum, TS_SEQ_ID_OFFSET, CPSW_P_TS_SEQ_ID_OFFSET);

    ETH_PN_WR_PORT_FIELD(TS_SEQ_LTYPE, portNum, TS_LTYPE1, CPSW_ETHTYPE_PTP1588);

    /* Enable Annex F of 1588v2 */
    ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_TX_ANNEX_F_EN, 1U);

    ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_RX_ANNEX_F_EN, 1U);
    ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_RX_ANNEX_D_EN, 1U);
    ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_TX_ANNEX_D_EN, 1U);
    ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_RX_ANNEX_E_EN, 1U);
    ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_TX_ANNEX_E_EN, 1U);
    ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_TX_HOST_TS_EN, 0U);

    if (ETH_CPTS_VLAN_TYPE_NONE != pCptsCfg->vlanType)
    {
        /* Configure VLAN LTYPE1 */
        ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_RX_VLAN_LTYPE1_EN, 1U);
        ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_TX_VLAN_LTYPE1_EN, 1U);

        if (ETH_CPTS_VLAN_TYPE_STACKED_TAGS == pCptsCfg->vlanType)
        {
            /* Configure VLAN LTYPE2 */
            ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_RX_VLAN_LTYPE2_EN, 1U);
            ETH_PN_WR_PORT_FIELD(TS_CTL, portNum, TS_TX_VLAN_LTYPE2_EN, 1U);
        }
    }
}

static void CpswCpts_initHw(CpswCpts_StateObj *pCptsStateObj)
{
    Eth_CptsConfigType *pCptsCfg = &pCptsStateObj->cptsCfg;
    uint8               portIdx  = pCptsStateObj->portNum;
    uint32              baseAddr = pCptsStateObj->cpswBaseAddr;

    /* Set the TS LTYPE to the IEEE 1588 Annex F value */
    ETH_PN_WR_PORT_FIELD(TS_VLAN_LTYPE, portIdx, TS_VLAN_LTYPE1, CPSW_VLAN_LTYPE_VLAN_INNER);

    /* Set the VLAN LTYPE to the standard 802.1Q VLAN EtherType */
    if (ETH_CPTS_VLAN_TYPE_NONE != pCptsCfg->vlanType)
    {
        CPSW_WR_FIELD(VLAN_LTYPE, VLAN_LTYPE_INNER, CPSW_VLAN_LTYPE_VLAN_INNER);
        if (ETH_CPTS_VLAN_TYPE_STACKED_TAGS == pCptsCfg->vlanType)
        {
            CPSW_WR_FIELD(VLAN_LTYPE, VLAN_LTYPE_OUTER, CPSW_VLAN_LTYPE_VLAN_OUTER);
        }
    }

    CpswCpts_configPort(pCptsStateObj, pCptsStateObj->portNum);
}

static CpswCpts_Event *CpswCpts_lookupEvent(CpswCpts_StateObj *pCptsStateObj, const CpswCpts_Event *pEventTemplate)
{
    CpswCpts_Event *pEvent   = (CpswCpts_Event *)NULL_PTR;
    uint32          eventIdx = 0U;

    /* Get pointer to start of event queue type */
    switch (pEventTemplate->eventType)
    {
        case CPTS_EVENT_ETHERNET_RECEIVE:
            pEvent = &pCptsStateObj->rxQueue.event[0];
            break;

        case CPTS_EVENT_ETHERNET_TRANSMIT:
            pEvent = &pCptsStateObj->txQueue.event[0];
            break;

        default:
            break;
    }

    /* Find event matching with template */
    if (NULL_PTR != pEvent)
    {
        for (eventIdx = 0U; eventIdx < ETH_CPTS_EVENT_CNT; ++eventIdx)
        {
            /* Check if template match */
            if ((TRUE == pEvent->valid) && (pEventTemplate->messageType == pEvent->messageType) &&
                (pEventTemplate->sequenceId == pEvent->sequenceId))
            {
                break;
            }
            pEvent++;
        }

        if (eventIdx >= ETH_CPTS_EVENT_CNT) /* Not found */
        {
            pEvent = (CpswCpts_Event *)NULL_PTR;
        }
        else
        {
            pEvent->valid = FALSE; /* Change valid flag to mark event processed */
        }
    }
    else
    {
        /* Nothing */
    }

    return pEvent;
}

static uint64 CpswCpts_getTimestamp(uint32 baseAddr)
{
    uint64 timestamp      = 0U;
    uint32 upperTimestamp = CPTS_RD_REG(EVENT_3);
    uint32 lowerTimestamp = CPTS_RD_REG(EVENT_0);

    timestamp  = (uint64)upperTimestamp << 32U;
    timestamp += lowerTimestamp;

    return timestamp;
}

static void CpswCpts_enableIntr(uint32 baseAddr)
{
    /* Unmask the interrupts */
    CPTS_WR_FIELD(INT_ENABLE, TS_PEND_EN, 1U);
}

static void CpswCpts_disableIntr(uint32 baseAddr)
{
    /* Mask the interrupts */
    CPTS_WR_FIELD(INT_ENABLE, TS_PEND_EN, 0U);
}

static uint64 CpswCpts_readHwTimestamp(CpswCpts_StateObj *pCptsStateObj)
{
    uint64 timeStamp    = 0U;
    uint32 forceRetries = 50U;
    uint32 baseAddr     = pCptsStateObj->cpswBaseAddr;

    SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

    /* Send TS_PUSH to CPTS */
    CPTS_WR_FIELD(TS_PUSH, TS_PUSH, 1U);

    /* We handle TS_PUSH event by ourself instead of in ISR.
     * DO NOT ENABLE interrupts till event is handled */
    while ((uint32)0U != forceRetries)
    {
        /* Check till event is returned */
        if ((uint32)1U == CpswCpts_getEventPendStatus(baseAddr))
        {
            if (CPTS_EVENT_TIME_STAMP_PUSH == CpswCpts_getEventType(baseAddr))
            {
                timeStamp = CpswCpts_getTimestamp(baseAddr);

                /* Set the EVENT_POP field (bit 0) of the CPTS_EVENT_POP register
                 * to pop the previously read value off of the event FIFO */
                CPTS_WR_FIELD(EVENT_POP, EVENT_POP, 1U);
                break;
            }
            else /* Handle other event to store event in queue */
            {
                CpswCpts_handleEvents(pCptsStateObj);
            }
        }

        forceRetries--;
    }
    SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();

    return timeStamp;
}

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
