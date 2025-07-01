/* ======================================================================
 *   Copyright (C) 2022 Texas Instruments Incorporated
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
 *  \file     Gpt_Priv.c
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Gpt.h"
#include "Gpt_Irq.h"
#include "soc.h"
#include "Gpt_Priv.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
#define GPT_START_SEC_CONST_32
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Gpt_MemMap.h"

/*The Array of pointers to the call notification Functions */
CONST(Gpt_IsrRefType, GPT_CONST)
Gpt_IsrNotifyFunctions[CHANNEL_MODES] = {
    Gpt_NotifContIsr,
    Gpt_NotifSingleIsr,
};

#define GPT_STOP_SEC_CONST_32
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Gpt_MemMap.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VAR(uint16, GPT_DATA) Gpt_CounterCfg[GPT_RTI_MODULES][GPT_RTI_COUNTERS];

extern VAR(Gpt_ChannelStateType, GPT_DATA) Gpt_ChannelState[GPT_RTI_MAX];
extern P2CONST(Gpt_ConfigType, GPT_DATA, GPT_PBCFG) Gpt_Config_pt;

extern VAR(uint16, GPT_DATA) Gpt_ChConfig_map[GPT_RTI_MAX];
extern VAR(uint32, GPT_DATA) Gpt_ChStartTime_map[GPT_RTI_MAX];
#define GPT_START_SEC_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
/*LDRA_INSPECTED 243 S : MISRAC_2012_D.4.10
 * "Reason - Memmap file cannot have include guard w.r.o autosar spec " */
#include "Gpt_MemMap.h"
static VAR(Gpt_NotifyType, GPT_DATA) Gpt_ChannelNotifyFunctions[GPT_RTI_MAX] = {(Gpt_NotifyType)NULL_PTR};
#define GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#define GPT_START_SEC_CODE
/*LDRA_INSPECTED 338 S : MISRAC_2012_R.20.1
 * "Reason - Required to comply with AUTOSAR memmap spec " */
#include "Gpt_MemMap.h"

uint32 Gpt_GetRTIChannelAddr(uint32 channelId)
{
    uint32 retVal;
    /* Channels (0, 1, 2, 4) => RTI MODULE1, ..., (12, 13, 14, 15) => RTI MODULE4 */
    uint32 modId = channelId / 4U;

    retVal = Gpt_RTIChannelAddr[modId];

    return (retVal);
}

void Gpt_RTIInit_Channel(rtiBASE_t *rtireg, Gpt_ChannelType ChannelId, uint32 tickVal)
{
    uint32 counterBlk = Gpt_Config_pt->ChannelConfig_pt[Gpt_ChConfig_map[ChannelId]].CounterBlk;
    /* Lower 2 bits determine the compare block - (0, 1, 2, 3) */
    uint32 compareBlk = (ChannelId & CH_COMP_MASK);

    /* Not checking for Gpt_CounterCfg[modId][counterBlk]) == 0U as it's always 0, before any
     * channel is started */
    /* Operation of counter block */
    CLEAR(uint32, rtireg->GCTRL, counterBlk);

    /** - Enable/Disable capture event sources for both counter blocks */
    rtireg->CAPCTRL = 0U | 0U;
    /* Clear RTI clock counter */
    rtireg->CNT[counterBlk].UCx = 0x00000000U;
    /* Prescaler clock */
    rtireg->CNT[counterBlk].CPUCx = tickVal;
    /** - Reset free running counter 0 */
    rtireg->CNT[counterBlk].FRCx = 0x00000000U;
    /** - Clear all pending interrupts */
    rtireg->INTFLAG = 0x0007000FU;
    /** - Disable all interrupts */
    rtireg->CLEARINTENA = 0x00070F0FU;

    /** - Clear corresponding pending interrupt */
    rtireg->INTFLAG = (uint32)(1U) << compareBlk;
    /** - Disable corresponding interrupt */
    rtireg->CLEARINTENA = (uint32)(1U) << compareBlk;

    /* Reset Update counter */
    rtireg->CMP[compareBlk].UDCPx = 0U;
    /* Register holds compare value */
    rtireg->CMP[compareBlk].COMPx = MAX_RESOLUTION;

    if (counterBlk == GPT_RTI_COUNTER0)
    {
        /* Connects compare block to counter block 0 */
        CLEAR(uint32, rtireg->COMPCTRL, (4U * compareBlk));
    }
    else
    {
        /* Connects compare block to counter block 1 */
        SET(uint32, rtireg->COMPCTRL, (4U * compareBlk));
    }
}

void Gpt_RTI_DeInit(rtiBASE_t *rtireg, Gpt_ValueType channelId)
{
    uint32 counterBlk = Gpt_Config_pt->ChannelConfig_pt[Gpt_ChConfig_map[channelId]].CounterBlk;
    /* Lower 2 bits determine the compare block - (0, 1, 2, 3) */
    uint32 compareBlk = (channelId & CH_COMP_MASK);

    Gpt_RTI_StopTimer(rtireg, channelId);

    /* Not checking for Gpt_CounterCfg[modId][counterBlk]) == 0U as it's always 0, because no
     * channel can be running at this point */
    /* Clear RTI clock counter */
    rtireg->CNT[counterBlk].UCx = 0U;
    /* Prescaler clock */
    rtireg->CNT[counterBlk].CPUCx = 0U;
    /* Clear Free running counter */
    rtireg->CNT[counterBlk].FRCx = 0U;

    /*Clear Update Compare Register*/
    rtireg->CMP[compareBlk].UDCPx = 0U;
    /* Register holds compare value */
    rtireg->CMP[compareBlk].COMPx = 0U;

    /* Reset Interrupt Notification */
    rtireg->CLEARINTENA = (uint32)(1U) << compareBlk;
}

Gpt_ValueType Gpt_GetCounter_Values(const rtiBASE_t *rtireg, Gpt_ValueType channelId, Gpt_ValueType *UpdCompare,
                                    Gpt_ValueType *compare)
{
    uint32 retVal;

    uint32 counterBlk = Gpt_Config_pt->ChannelConfig_pt[Gpt_ChConfig_map[channelId]].CounterBlk;
    /* Lower 2 bits determine the compare block - (0, 1, 2, 3) */
    uint32 compareBlk = (channelId & CH_COMP_MASK);

    /* Free running counter value */
    retVal = rtireg->CNT[counterBlk].FRCx;
    /* Update counter value */
    *UpdCompare = rtireg->CMP[compareBlk].UDCPx;
    /* Compare register value */
    *compare = rtireg->CMP[compareBlk].COMPx;

    return (retVal);
}

/*LDRA_INSPECTED 65 D : MISRAC_2012_R.2.2
 * "Reason - Void function does have side effect. It is updating  GPT register "
 **/
FUNC(void, GPT_CODE) Gpt_SetRegStartTimer(Gpt_ChannelType channel, Gpt_ValueType value)
{
    Gpt_ChannelMode ChannelMode;
    uint32          tickFreq;
    uint32          Gpt_rtiChAddr;
    uint16          channelIdx = Gpt_ChConfig_map[channel];

    /*Read the Channel Id and channel mode from configured channel*/
    ChannelMode   = Gpt_Config_pt->ChannelConfig_pt[channelIdx].ChannelMode;
    tickFreq      = Gpt_Config_pt->ChannelConfig_pt[channelIdx].GptChannelTickFrequency;
    Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(channel);

    /*Configure the register with the tick frequency and the period value*/
    /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
     * "Reason - Cast for register address " */
    /*LDRA_INSPECTED 105 D : MISRAC_2012_R2.2
     * "Reason - Code inspected LDRA tool error " */
    Gpt_RTI_StartTimer((rtiBASE_t *)Gpt_rtiChAddr, channel, tickFreq, ChannelMode, value);
    /*Set the notify function pointer*/
    Gpt_ChannelNotifyFunctions[channel] = Gpt_Config_pt->ChannelConfig_pt[channelIdx].Notification_pt;
}

void Gpt_RTI_StartTimer(rtiBASE_t *rtireg, Gpt_ValueType channelId, Gpt_ValueType tickFreq, Gpt_ChannelMode ChannelMode,
                        Gpt_ValueType value)
{
    uint32        counterBlk = Gpt_Config_pt->ChannelConfig_pt[Gpt_ChConfig_map[channelId]].CounterBlk;
    /* Lower 2 bits determine the compare block - (0, 1, 2, 3) */
    uint32        compareBlk = (channelId & CH_COMP_MASK);
    /* Channels (0, 1, 2, 3) => RTI MODULE1, ..., (12, 13, 14, 15) => RTI MODULE4 */
    uint32        modId                = channelId / 4U;
    uint32        Gpt_rtiChAddr        = Gpt_GetRTIChannelAddr(channelId);
    Gpt_ValueType UpdCompare_t         = 0U;
    Gpt_ValueType Compare_t            = 0U;
    Gpt_ValueType FreeRunningCounter_t = 0U;

    /* First time initialization of counter block */
    if (Gpt_CounterCfg[modId][counterBlk] == 0U)
    {
        /* Reset Up counter */
        rtireg->CNT[counterBlk].UCx = 0U;
        /*Reset Free running counter*/
        rtireg->CNT[counterBlk].FRCx = 0U;
        /* Prescaler clock */
        /* Klocwork Inspected
         * MISRA.ETYPE.INAPPR.CAST.2012
         * Reason - Code Readability and space optimization
         */
        if (tickFreq == 0U)
        {
            rtireg->CNT[counterBlk].CPUCx = (tickFreq + 1U); /* Increment by 1 if 0 */
        }
        else
        {
            rtireg->CNT[counterBlk].CPUCx = tickFreq;
        }
    }
    else
    {
        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address " */
        /*LDRA_INSPECTED 91 D : MISRAC_2012_R4.7
         * "Reason - Return value used  " */
        FreeRunningCounter_t = Gpt_GetCounter_Values((rtiBASE_t *)Gpt_rtiChAddr, channelId, &UpdCompare_t, &Compare_t);
    }

    /* Klocwork Inspected
     * MISRA.ETYPE.ASSIGN.2012
     * Reason - Taking modulus using macro MAX_RESOLUTION which is 0xffffffff
     * (largest uint32) hence resulting value will be fitted into uint32.
     */
    rtireg->CMP[compareBlk].COMPx = (uint32)(((uint64)FreeRunningCounter_t + value) % MAX_RESOLUTION);
    /* Klocwork Inspected
     * MISRA.ETYPE.INAPPR.CAST.2012
     * Reason - Code Readability and space optimization
     */
    if (GPT_CH_MODE_ONESHOT != ChannelMode)
    {
        rtireg->CMP[compareBlk].UDCPx = (uint32)value; /* 0 if one shot mode */
    }
    else
    {
        rtireg->CMP[compareBlk].UDCPx = 0U; /* 0 if one shot mode */
    }

    /* First time initialization of counter block */
    if (Gpt_CounterCfg[modId][counterBlk] == 0U)
    {
        /* Start Counter */
        SET(uint32, rtireg->GCTRL, counterBlk);
    }

    /* Track timer channel against corresponding counter */
    SET(uint16, Gpt_CounterCfg[modId][counterBlk], compareBlk);

    Gpt_ChStartTime_map[channelId] = FreeRunningCounter_t;
}

void Gpt_RTI_StopTimer(rtiBASE_t *rtireg, Gpt_ValueType channelId)
{
    uint32 counterBlk = Gpt_Config_pt->ChannelConfig_pt[Gpt_ChConfig_map[channelId]].CounterBlk;
    /* Lower 2 bits determine the compare block - (0, 1, 2, 3) */
    uint32 compareBlk = (channelId & CH_COMP_MASK);
    /* Four Compare blocks are there for each instance */
    uint32 modId = channelId / (uint32)4U;

    CLEAR(uint16, Gpt_CounterCfg[modId][counterBlk], compareBlk);

    /* If all other associated channels are de-initialized */
    if ((Gpt_CounterCfg[modId][counterBlk] == (uint16)0U) &&
        ((GPT_STOPPED == Gpt_ChannelState[channelId]) || (GPT_UNINITIALIZED == Gpt_ChannelState[channelId]) ||
         (GPT_EXPIRED == Gpt_ChannelState[channelId])))
    {
        CLEAR(uint32, rtireg->GCTRL, counterBlk); /* Stop counter block */
    }
}

void Gpt_RTI_EnableNotification(rtiBASE_t *rtireg, Gpt_ValueType channelId)
{
    uint32 compareBlk = (channelId & CH_COMP_MASK); /* (0, 1, 2, 3) */

    rtireg->INTFLAG   = (uint32)(1U) << compareBlk; /* Reset Interrupt Flag */
    rtireg->SETINTENA = (uint32)(1U) << compareBlk; /* Set Interrupt */
}

void Gpt_RTI_DisableNotification(rtiBASE_t *rtireg, Gpt_ValueType channelId)
{
    uint32 compareBlk = (channelId & CH_COMP_MASK); /* (0, 1, 2, 3) */

    rtireg->INTFLAG     = (uint32)(1U) << compareBlk; /* Reset Interrupt Flag */
    rtireg->CLEARINTENA = (uint32)(1U) << compareBlk; /* Clear Interrupt */
}

void Gpt_resetDrvObj(Gpt_DriverObjType *drvObj)
{
    Gpt_ChannelType ChannelIdx;
    for (ChannelIdx = 0U; ChannelIdx < drvObj->ChannelCount; ChannelIdx++)
    {
        drvObj->gChannelConfig_pt[ChannelIdx].Notification_pt         = (Gpt_NotifyType)NULL_PTR;
        drvObj->gChannelConfig_pt[ChannelIdx].tickValueMax            = 0U;
        drvObj->gChannelConfig_pt[ChannelIdx].GptChannelTickFrequency = 0U;
    }
}

Std_ReturnType Gpt_copyConfig(Gpt_DriverObjType *drvObj, const Gpt_ConfigType *cfgPtr)
{
    Gpt_ChannelType ChannelIdx;
    Gpt_ChannelType Gpt_Channel;
    uint32          retVal = E_OK;

    /* Channel Count of GPT module. */
    drvObj->ChannelCount = cfgPtr->ChannelCount;

    for (ChannelIdx = 0U; ChannelIdx < cfgPtr->ChannelCount; ChannelIdx++)
    {
        /* Load the GPT Channel Configuration. */
        drvObj->gChannelConfig_pt[ChannelIdx] = cfgPtr->ChannelConfig_pt[ChannelIdx];
        Gpt_Channel                           = drvObj->gChannelConfig_pt[ChannelIdx].ChannelId;
        if (Gpt_Channel > GPT_RTI_CH_MAX)
        {
#if (STD_ON == GPT_DEV_ERROR_DETECT)
            (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_INIT, GPT_E_INIT_FAILED);
#endif
            retVal = E_NOT_OK;
            break;
        }
    }

    return retVal;
}

void Gpt_ConfigHwChannel(Gpt_DriverObjType *drvObj, Gpt_ChannelStateType status)
{
    Gpt_ChannelType ChannelIdx;
    Gpt_ChannelType Gpt_Channel;
    uint32          tickFreq;
    uint32          Gpt_rtiChAddr;

    for (ChannelIdx = 0U; ChannelIdx < drvObj->ChannelCount; ChannelIdx++)
    {
        Gpt_Channel                   = drvObj->gChannelConfig_pt[ChannelIdx].ChannelId;
        Gpt_ChConfig_map[Gpt_Channel] = (uint16)ChannelIdx;
        Gpt_rtiChAddr                 = Gpt_GetRTIChannelAddr(Gpt_Channel);
        tickFreq                      = drvObj->gChannelConfig_pt[ChannelIdx].GptChannelTickFrequency;
        /*LDRA_INSPECTED 440 S : MISRAC_2012_R11.1
         * "Reason - Cast for register address " */
        /*LDRA_INSPECTED 105 D : MISRAC_2012_R2.2
         * "Reason - Code inspected LDRA tool error " */

        if (status == GPT_UNINITIALIZED)
        {
            Gpt_RTI_DeInit((rtiBASE_t *)Gpt_rtiChAddr, Gpt_Channel);
            Gpt_ChConfig_map[Gpt_Channel] = GPT_RTI_MAX;
        }
        else
        {
            Gpt_RTIInit_Channel((rtiBASE_t *)Gpt_rtiChAddr, Gpt_Channel, tickFreq);
        }

        Gpt_ChannelState[Gpt_Channel] = status;
    }
}

/***************************************************************************************************************
    Function name:  Gpt_NotifContIsr
 ***************************************************************************************************************/
/*  \Description: This Interrupt notification call function is called when timer channel is
 *configured in Continuous mode and interrupt notification should be enabled for the channel.
 *                Gpt_StartTimer is called with the referenced channel. Once the timer channel is
 *expired, interrupt is triggered which calls the Gpt_NotifContIsr call back function inside the
 *timer Isr.
 *  \param[in]:  ChannelID
 *  \return:     None
 *  \context:    Called by ISR.
 *****************************************************************************************************************/
/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is called from ISR  " */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA tool error " */
FUNC(void, GPT_CODE) Gpt_NotifContIsr(Gpt_ChannelType Channel)
{
    uint32 Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(Channel);
    if (NULL_PTR != (Gpt_ChannelNotifyFunctions[Channel]))
    {
        /* Call notification callback */
        /* Requirements : SWS_Gpt_00233, SWS_Gpt_00086 */
        Gpt_ChannelNotifyFunctions[Channel]();
    }
    Gpt_RTINotifyContIsr((rtiBASE_t *)Gpt_rtiChAddr, Channel);

} /* Gpt_NotifContIsr */

void Gpt_RTINotifyContIsr(rtiBASE_t *rtireg, Gpt_ValueType channelId)
{
    uint32 compareBlk = (channelId & CH_COMP_MASK); /* (0, 1, 2, 3) */
    rtireg->INTFLAG   = (uint32)(1U) << compareBlk; /* Reset the Interrupt Flag */
}

/*****************************************************************************************************************
    Function name:  Gpt_NotifSingleIsr
 *****************************************************************************************************************/
/*  \Description: This Interrupt notification callback function is called when timer channel is
 *configured in Single mode and interrupt notification should be enabled for the channel.
 *                Gpt_StartTimer should be called with the referenced channel. Once the timer
 *channel is expired, interrupt is triggered and Gpt_NotifSingleIsr call back function is called
 *inside the subroutine. This call back function will stop the timer channel in One shot mode.
 *  \param[in]:  ChannelID
 *  \return:      None
 *  \context:     Called by ISR.
 *****************************************************************************************************************/
/* Requirements : SWS_Gpt_00206, SWS_Gpt_00209*/
/*LDRA_INSPECTED 76 D : MISRAC_2012_R.8.7
 * "Reason - This is called from ISR " */
/*LDRA_INSPECTED 8 D : MISRAC_2012_R2.2
 * "Reason - Code inspected LDRA tool error " */
FUNC(void, GPT_CODE) Gpt_NotifSingleIsr(Gpt_ChannelType Channel)
{
    uint32 Gpt_rtiChAddr = Gpt_GetRTIChannelAddr(Channel);

    /* Mark the channel as inactive */
    /* Requirements: SWS_Gpt_00185 */
    Gpt_ChannelState[Channel] = GPT_EXPIRED;
    if (NULL_PTR != (Gpt_ChannelNotifyFunctions[Channel]))
    {
        /* Call notification callback */
        /* Requirements: SWS_Gpt_00331 */
        Gpt_ChannelNotifyFunctions[Channel]();
    }
    Gpt_RTINotifySingleIsr((rtiBASE_t *)Gpt_rtiChAddr, Channel);

} /* Gpt_NotifSingleIsr */

void Gpt_RTINotifySingleIsr(rtiBASE_t *rtireg, Gpt_ValueType channelId)
{
    uint32 compareBlk = (channelId & CH_COMP_MASK); /* (0, 1, 2, 3) */

    /* After reaching the target time, the timer stops automatically */
    Gpt_RTI_StopTimer(rtireg, channelId);
    Gpt_RTI_DisableNotification(rtireg, channelId);

    rtireg->INTFLAG = (uint32)(1U) << compareBlk; /* Reset the Interrupt Flag */
}

#if (STD_ON == GPT_REGISTER_READBACK_API)
void Gpt_RegReadBack(const rtiBASE_t *rtireg, GptConfigReg *GptRegConf)
{
    GptRegConf->GPT_GCTRL    = rtireg->GCTRL;
    GptRegConf->GPT_TBCTRL   = rtireg->TBCTRL;
    GptRegConf->GPT_COMPCTRL = rtireg->COMPCTRL;
    GptRegConf->GPT_UDCP0    = rtireg->CMP[0].UDCPx;
    GptRegConf->GPT_UDCP1    = rtireg->CMP[1].UDCPx;
    GptRegConf->GPT_UDCP2    = rtireg->CMP[2].UDCPx;
    GptRegConf->GPT_UDCP3    = rtireg->CMP[3].UDCPx;
}
#endif

uint32 Mod_Difference(uint32 valueA, uint32 valueB)
{
    return (uint32)(((uint64)(valueA) + (uint64)(MAX_RESOLUTION)-valueB) % MAX_RESOLUTION);
}

/*LDRA_INSPECTED 580 S : MISRAC_2012_R.20.4
 * "Reason - macro is undefined in memmap.h file,but LDRA is not able to analyse
 *this " */
#define GPT_STOP_SEC_CODE
#include "Gpt_MemMap.h"
