[!IF "as:modconf('Cdd_Pwm')[1]/IMPLEMENTATION_CONFIG_VARIANT = 'VariantPostBuild'"!]
/* ======================================================================
 *   Copyright (C) [!"text:split($date,'-')[1]"!] Texas Instruments Incorporated
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

 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cdd_Pwm_PBcfg.c
 *      Project:  TI Sitara MCU AM263Px
 *       Module:  Cdd_Pwm
 *    Generator:  EB Tresos
 *
 *********************************************************************************************************************/
[!MACRO "GetPeriodValue", "PwmFunctionalClock", "PwmHSClkPrescaler", "PwmClkPrescaler","PwmPeriodDefault","PwmCounter"!][!//
[!NOCODE!][!//  
[!IF "PwmPeriodDefault != num:f('0')"!]
[!VAR "Ticks" = "0"!]
[!VAR "Sys_ClkFreq" = "$PwmFunctionalClock"!]
[!VAR "Freq" = "(num:i(round(1 div num:f($PwmPeriodDefault))))"!]
[!VAR "HsPrescaler" = "(num:i(substring-after($PwmHSClkPrescaler,'CDD_PWM_HSCLOCK_DIVIDER_')))"!]
[!VAR "ClkPrescaler" = "(num:i(substring-after($PwmClkPrescaler,'CDD_PWM_CLOCK_DIVIDER_')))"!]
[!VAR "Prescalers" = "((num:i($ClkPrescaler)) * (num:i($HsPrescaler)))"!]
[!IF "$PwmCounter = 'CDD_PWM_COUNTER_MODE_UP_DOWN'"!]
[!VAR "Ticks" = " (((num:i($Sys_ClkFreq) div num:i($Prescalers)) div (num:i(round(1 div num:f($PwmPeriodDefault))))) div 2)"!]
[!ENDIF!]
[!IF "$PwmCounter = 'CDD_PWM_COUNTER_MODE_UP'"!]
[!VAR "Ticks" = " (((num:i($Sys_ClkFreq) div num:i($Prescalers)) div (num:i(round(1 div num:f($PwmPeriodDefault))))))"!]
[!ENDIF!]
[!IF "$PwmCounter = 'CDD_PWM_COUNTER_MODE_DOWN'"!]
[!VAR "Ticks" = " (((num:i($Sys_ClkFreq) div num:i($Prescalers)) div (num:i(round(1 div num:f($PwmPeriodDefault))))))"!]
[!ENDIF!]
[!IF "$PwmCounter = 'CDD_PWM_COUNTER_MODE_STOP_FREEZE'"!]
[!VAR "Ticks" = "0"!]
[!ENDIF!]
[!IF "(num:i($Ticks) > num:hextoint('0xffff'))"!][!ERROR "Configured Period is not possible or Invalid, please refer 'Configurable Interfaces' section in Pwm User guide for details!!"!][!ENDIF!]
[!IF "(num:f($Ticks) - floor(num:f($Ticks)))  > 0"!][!WARNING "Configured Period is not integer, please refer 'Configurable Interfaces' section in Pwm User guide for details"!][!ENDIF!]
[!ENDIF!][!CODE!][!"num:i($Ticks)"!][!ENDCODE!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetAddress", "ChannelNumber", "HWNumber"!][!//
[!NOCODE!][!//    
    [!VAR "BaseAddr" = "BaseAddr + 1342177280"!][!//
    [!VAR "Channeloffset" = "Channeloffset + 4096"!][!//
    [!VAR "HWunitOffset" = "HWunitOffset + 262144"!][!//
    [!VAR "bkId" = "num:i(substring-after($ChannelNumber,'CDD_PWM_CHANNEL_'))"!][!//  
    [!VAR "bkId1" = "num:i(substring-after($HWNumber,'CDD_PWM_CONTROLSS_G'))"!][!//  
    [!VAR "ChannelBase"  = "$Channeloffset*$bkId"!][!//  
    [!VAR "HWunitBase"   = "$HWunitOffset*$bkId1"!][!//    
    [!CODE!][!"num:inttohex($BaseAddr+$ChannelBase+$HWunitBase)"!][!ENDCODE!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpression", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_ZERO", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_ZERO[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_PERIOD", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_PERIOD[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_U_CMPA", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_U_CMPA[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_D_CMPA", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_D_CMPA[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_U_CMPB", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_U_CMPB[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_D_CMPB", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_D_CMPB[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_U_CMPC", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_U_CMPC[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_D_CMPC", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_D_CMPC[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_U_CMPD", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_U_CMPD[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_TBCTR_D_CMPD", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_TBCTR_D_CMPD[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!MACRO "GetBooleanExpressionMIX_DCAEVT1", "Parameter"!][!//
[!NOCODE!][!//    
    [!CODE!][!IF "$Parameter = 'true'"!]CDD_PWM_INT_MIX_DCAEVT1[!ELSE!]0U[!ENDIF!][!ENDCODE!][!// 
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
/**********************************************************************************************************************
    Project: [!"$project"!]

    This file is generated by EB Tresos
    Do not modify this file, otherwise the software may behave in unexpected way.
 *********************************************************************************************************************/

#include "Std_Types.h"

#include "Cdd_Pwm.h"
#ifdef __cplusplus

extern "C" {
#endif

[!AUTOSPACING!]

/* ---- Perform version checking  ----------------------------------------- */
 #if ((CDD_PWM_SW_MAJOR_VERSION != ([!"substring-before($moduleSoftwareVer,'.')"!]U))||(CDD_PWM_SW_MINOR_VERSION != ([!"substring-before(substring-after($moduleSoftwareVer,'.'),'.')"!]U)))
  #error "Version numbers of Cdd_Pwm_PBcfg.c and Cdd_Pwm_Cfg.h are inconsistent!"
#endif

#if ((CDD_PWM_CFG_MAJOR_VERSION != ([!"substring-before($moduleSoftwareVer,'.')"!]U))||(CDD_PWM_CFG_MINOR_VERSION != ([!"substring-before(substring-after($moduleSoftwareVer,'.'),'.')"!]U)))
  #error "Version numbers of Cdd_Pwm_PBcfg.c and Cdd_Pwm_Cfg.h are inconsistent!"
#endif

/*Requirements : SWS_Cdd_Pwm_60075*/
#define CDD_PWM_START_SEC_CONFIG_DATA
#include "Cdd_Pwm_MemMap.h"

[!NOCODE!][!// 
[!VAR "notifyFxnList" = "' '"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*/CddPwmChannel/*"!][!//
[!IF "not(node:empty(CddPwmNotification)) and not(text:match(CddPwmNotification,'NULL_PTR'))"!][!//
[!IF "not(node:containsValue(text:split($notifyFxnList),node:value(CddPwmNotification)))"!][!//
[!CODE!]
[!"concat('extern void ',CddPwmNotification,' (void);')"!][!//
[!ENDCODE!]
[!VAR "notifyFxnList" = "concat($notifyFxnList,' ',CddPwmNotification)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

[!NOCODE!][!// 
[!VAR "notifyFxnList" = "' '"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*/CddPwmChannel/*"!][!//
[!IF "not(node:empty(CddPwmTzNotification)) and not(text:match(CddPwmTzNotification,'NULL_PTR'))"!][!//
[!IF "not(node:containsValue(text:split($notifyFxnList),node:value(CddPwmTzNotification)))"!][!//
[!CODE!]
[!"concat('extern void ',CddPwmTzNotification,' (void);')"!][!//
[!ENDCODE!]
[!VAR "notifyFxnList" = "concat($notifyFxnList,' ',CddPwmTzNotification)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

[!VAR "Sys_ClkFreq" = "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmSystemClock"!]

[!VAR "Index1" = "0"!][!//
[!VAR "Index" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_timerBaseConfigType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_TimerBaseRef[CDD_PWM_TIMER_BASE_NUM_CHANNELS] =
{
    [!LOOP "CddPwmTimerBase/*"!][!/*Channel Loop */!][!//
    [[!"num:i($Index1)"!]] =
    {
       .channelPwmTimerBasePeriodGlobalLoad = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmTimerBaseGlobalLoad"!], 
       .channelPwmEmulationMode = [!"CddPwmEmulationMode"!],
       .channelPwmClockDivider = [!"CddPwmClockDivider"!], 
       .channelPwmHSClockDivider = [!"CddPwmHSClockDivider"!],
       .channelPwmTbPeriod = [!CALL "GetPeriodValue", "PwmFunctionalClock" = "$Sys_ClkFreq", "PwmHSClkPrescaler" = "CddPwmHSClockDivider", "PwmClkPrescaler" = "CddPwmClockDivider", "PwmPeriodDefault" = "CddPwmTbPeriod", "PwmCounter" = "CddPwmCounterMode"!]U - 1U,
       .channelPwmTbPeriodInitValue = [!"CddPwmTbPeriodInitValue"!],
       .channelPwmCounterMode = [!"CddPwmCounterMode"!],
       .channelPwmEnablePhaseShift = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmEnablePhaseShift"!],
       .channelPwmEnablePhaseShiftValue = [!"CddPwmEnablePhaseShiftValue"!]U,
       .channelPwmPeriodLoadMode = [!"CddPwmPeriodLoadMode"!],
       .channelPwmTbprdlink = [!"CddPwmTbprdlink"!],
    }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!][!//
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_TimerBaseRef Loop*/!][!//

[!VAR "Index1" = "0"!][!//
[!VAR "Index" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_CompareType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_CounterCompareRef[CDD_PWM_COUNTER_NUM_CHANNELS] =
{
    [!LOOP "CddPwmCounterCompare/*"!][!/*CddPwmCounterCompare Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           /* Compare A */
           .channelCddPwmCounterBlockA = [!"CddPwmCounterCompareA/CddPwmCounterBlockCmpA"!],
           .channelCddPwmCompareValueCmpA = [!"CddPwmCounterCompareA/CddPwmCompareValueCmpA"!]U,
           .channelCddPwmCounterCompareGlobalLoadCmpA = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareA/CddPwmCounterCompareGlobalLoadCmpA"!],
           .channelCddPwmCounterCompareShadowModeCmpA = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareA/CddPwmCounterCompareShadowModeCmpA"!],
           .channelCddPwmCounterCompareShadowEventCmpA = [!"CddPwmCounterCompareA/CddPwmCounterCompareShadowEventCmpA"!],
           .channelCddPwmTbprdlinkCmpA = [!"CddPwmCounterCompareA/CddPwmTbprdlinkCmpA"!],
           
           /* Compare B */
           .channelCddPwmCounterBlockB = [!"CddPwmCounterCompareB/CddPwmCounterBlockCmpB"!],
           .channelCddPwmCompareValueCmpB = [!"CddPwmCounterCompareB/CddPwmCompareValueCmpB"!]U,
           .channelCddPwmCounterCompareGlobalLoadCmpB = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareB/CddPwmCounterCompareGlobalLoadCmpB"!],
           .channelCddPwmCounterCompareShadowModeCmpB = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareB/CddPwmCounterCompareShadowModeCmpB"!],
           .channelCddPwmCounterCompareShadowEventCmpB = [!"CddPwmCounterCompareB/CddPwmCounterCompareShadowEventCmpB"!],
           .channelCddPwmTbprdlinkCmpB = [!"CddPwmCounterCompareB/CddPwmTbprdlinkCmpB"!],
                      
           /* Compare C */
           .channelCddPwmCounterBlockC = [!"CddPwmCounterCompareC/CddPwmCounterBlockCmpC"!],
           .channelCddPwmCompareValueCmpC = [!"CddPwmCounterCompareC/CddPwmCompareValueCmpC"!]U,
           .channelCddPwmCounterCompareGlobalLoadCmpC = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareC/CddPwmCounterCompareGlobalLoadCmpC"!],
           .channelCddPwmCounterCompareShadowModeCmpC = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareC/CddPwmCounterCompareShadowModeCmpC"!],
           .channelCddPwmCounterCompareShadowEventCmpC = [!"CddPwmCounterCompareC/CddPwmCounterCompareShadowEventCmpC"!],
           .channelCddPwmTbprdlinkCmpC = [!"CddPwmCounterCompareC/CddPwmTbprdlinkCmpC"!],
           
           /* Compare D */
           .channelCddPwmCounterBlockD = [!"CddPwmCounterCompareD/CddPwmCounterBlockCmpD"!],
           .channelCddPwmCompareValueCmpD = [!"CddPwmCounterCompareD/CddPwmCompareValueCmpD"!]U,
           .channelCddPwmCounterCompareGlobalLoadCmpD = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareD/CddPwmCounterCompareGlobalLoadCmpD"!],
           .channelCddPwmCounterCompareShadowModeCmpD = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCounterCompareD/CddPwmCounterCompareShadowModeCmpD"!],
           .channelCddPwmCounterCompareShadowEventCmpD = [!"CddPwmCounterCompareD/CddPwmCounterCompareShadowEventCmpD"!],
           .channelCddPwmTbprdlinkCmpD = [!"CddPwmCounterCompareD/CddPwmTbprdlinkCmpD"!],       
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_CounterCompareRef Loop*/!][!//

[!VAR "Index1" = "0"!][!//
[!VAR "Index" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_TimerBaseSync_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_TimerBaseSyncRef[CDD_PWM_TIMER_BASE_SYNC_NUM_CHANNELS] =
{
    [!LOOP "CddPwmTimerBaseSync/*"!][!/*CddPwmTimerBaseSync Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           .channelOneShotSyncOutTrigger      = [!"CddPwmOneShotSyncOutTrigger"!],
           .channelForceSync                  = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmForceSync"!],
           .channelTbprdlink                  = [!"CddPwmTbprdlink"!],
           .channelSyncOutPulseOnSoftware     = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnSoftware"!],
           .channelSyncOutPulseOnCntrZero     = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnCntrZero"!],
           .channelSyncOutPulseOnCntCmpB      = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnCntCmpB"!],
           .channelSyncOutPulseOnCntCmpC      = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnCntCmpC"!],
           .channelSyncOutPulseOnCntCmpD      = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnCntCmpD"!],
           .channelSyncOutPulseOnDCAEVT1SYNC  = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnDCAEVT1SYNC"!],
           .channelSyncOutPulseOnDCBEVT1SYNC  = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnDCBEVT1SYNC"!],
           .channelSyncOutPulseOnALL          = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmSyncOutPulseOn/CddPwmSyncOutPulseOnALL"!],
           .channelSyncOutPulseSource         = [!"CddPwmSyncOutPulseSource"!],
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_TimerBaseSyncRef Loop*/!][!//

[!VAR "Index1" = "0"!][!//
[!VAR "Index" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_ActionConfigType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_ActionQualifierRef[CDD_PWM_TIMER_AQ_NUM_CHANNELS] =
{
    [!LOOP "CddPwmActionQualifier/*"!][!/*CddPwmActionQualifier Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {           
            /* Actions for EPWMA  */
           .channelPwmOutptEPWMA = [!"CddPwmActionQualifierA/CddPwmOutptEPWMA"!],
           .channelPwmActionGlobalLoadEPWMA = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmActionQualifierA/CddPwmActionGlobalLoadEPWMA"!],
           .channelPwmActionShadowModeEPWMA = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmActionQualifierA/CddPwmActionShadowModeEPWMA"!],
           .channelPwmActionShadowEventEPWMA = [!"CddPwmActionQualifierA/CddPwmActionShadowEventEPWMA"!],
           .channelPwmT1TriggerSourceEPWMA = [!"CddPwmActionQualifierA/CddPwmT1TriggerSourceEPWMA"!],
           .channelPwmT2TriggerSourceEPWMA = [!"CddPwmActionQualifierA/CddPwmT2TriggerSourceEPWMA"!],
           .channelPwmActionQualifierOneTimeSwOutputEPWMA = [!"CddPwmActionQualifierA/CddPwmActionQualifierOneTimeSwOutputEPWMA"!],
           .channelPwmActionQualifierContinuousSwOutputEPWMA = [!"CddPwmActionQualifierA/CddPwmActionQualifierContinuousSwOutputEPWMA"!],
           .channelPwmAqOutputOnTimebaseZEROEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnTimebaseZEROEPWMA"!],
           .channelPwmAqOutputOnTimebasePERIODEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnTimebasePERIODEPWMA"!],
           .channelPwmAqOutputOnTimebaseUPCMPAEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnTimebaseUPCMPAEPWMA"!],
           .channelPwmAqOutputOnTimebaseDOWNCMPAEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnTimebaseDOWNCMPAEPWMA"!],
           .channelPwmAqOutputOnTimebaseUPCMPBEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnTimebaseUPCMPBEPWMA"!],
           .channelPwmAqOutputOnTimebaseDOWNCMPBEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnTimebaseDOWNCMPBEPWMA"!],
           .channelPwmAqOutputOnT1COUNTUPEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnT1COUNTUPEPWMA"!],
           .channelPwmAqOutputOnT1COUNTDOWNEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnT1COUNTDOWNEPWMA"!],
           .channelPwmAqOutputOnT2COUNTUPEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnT2COUNTUPEPWMA"!],
           .channelPwmAqOutputOnT2COUNTDOWNEPWMA = [!"CddPwmActionQualifierA/CddPwmAqOutputOnT2COUNTDOWNEPWMA"!],
           
           /* Actions for EPWMB  */
           .channelPwmOutptEPWMB = [!"CddPwmActionQualifierB/CddPwmOutptEPWMB"!],
           .channelPwmActionGlobalLoadEPWMB = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmActionQualifierB/CddPwmActionGlobalLoadEPWMB"!],
           .channelPwmActionShadowModeEPWMB = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmActionQualifierB/CddPwmActionShadowModeEPWMB"!],
           .channelPwmActionShadowEventEPWMB = [!"CddPwmActionQualifierB/CddPwmActionShadowEventEPWMB"!],
           .channelPwmT1TriggerSourceEPWMB = [!"CddPwmActionQualifierB/CddPwmT1TriggerSourceEPWMB"!],
           .channelPwmT2TriggerSourceEPWMB = [!"CddPwmActionQualifierB/CddPwmT2TriggerSourceEPWMB"!],
           .channelPwmActionQualifierOneTimeSwOutputEPWMB = [!"CddPwmActionQualifierB/CddPwmActionQualifierOneTimeSwOutputEPWMB"!],
           .channelPwmActionQualifierContinuousSwOutputEPWMB = [!"CddPwmActionQualifierB/CddPwmActionQualifierContinuousSwOutputEPWMB"!],
           .channelPwmAqOutputOnTimebaseZEROEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnTimebaseZEROEPWMB"!],
           .channelPwmAqOutputOnTimebasePERIODEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnTimebasePERIODEPWMB"!],
           .channelPwmAqOutputOnTimebaseUPCMPAEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnTimebaseUPCMPAEPWMB"!],
           .channelPwmAqOutputOnTimebaseDOWNCMPAEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnTimebaseDOWNCMPAEPWMB"!],
           .channelPwmAqOutputOnTimebaseUPCMPBEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnTimebaseUPCMPBEPWMB"!],
           .channelPwmAqOutputOnTimebaseDOWNCMPBEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnTimebaseDOWNCMPBEPWMB"!],
           .channelPwmAqOutputOnT1COUNTUPEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnT1COUNTUPEPWMB"!],
           .channelPwmAqOutputOnT1COUNTDOWNEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnT1COUNTDOWNEPWMB"!],
           .channelPwmAqOutputOnT2COUNTUPEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnT2COUNTUPEPWMB"!],
           .channelPwmAqOutputOnT2COUNTDOWNEPWMB = [!"CddPwmActionQualifierB/CddPwmAqOutputOnT2COUNTDOWNEPWMB"!],

        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of CddPwmActionQualifier Loop*/!][!//

[!VAR "Index1" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_EventConfigType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_EventTriggerRef[CDD_PWM_TIMER_EVENT_NUM_CHANNELS] =
{
    [!LOOP "CddPwmEventTrigger/*"!][!/*CddPwmEventTrigger Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           .channelPwmForceEventValue         = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmForceEventValue"!],
           .channelPwmEnableEventCountInitialValue = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmEnableEventCountInitialValue"!],
           .channelPwmEventCountInitialValue  = [!"CddPwmEventCountInitialValue"!],
           .channelPwmInterruptCount          = [!"CddPwmInterruptCount"!],
           .channelPwmInterruptEventSources   = [!"CddPwmInterruptEventSources"!], 
           .channelPwmInterruptMixedSources   = [!CALL "GetBooleanExpressionMIX_TBCTR_ZERO", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrZero"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_PERIOD", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrPeriod"!] |[!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPA", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrUCmpA"!] |[!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPA", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrDCmpA"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPB", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrUCmpB"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPB", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrDCmpB"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPC", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrUCmpC"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPC", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrDCmpC"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPD", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrUCmpD"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPD", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixTbctrDCmpD"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_DCAEVT1", "Parameter" = "CddPwmInterruptMixedSources/CddPwmIntMixDCAEvt1"!],
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of CddPwmEventTrigger Loop*/!][!//

[!VAR "Index1" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_AdcEventTriggerType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_AdcEventTriggerRefSoc[CDD_PWM_TIMER_ADC_EVENT_NUM_CHANNELS] =
{
    [!LOOP "CddPwmAdcEventTrigger/*"!][!/*CddPwmAdcEventTrigger Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           /* SOC A Event for ADC. */
           .channelPwmSocAEvent                   = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAEpwmEvent"!],
           .channelPwmSocAForceEventValue         = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAForceEventValue"!],
           .channelPwmSocAEventCountInitialValueEnable  = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAEventCountInitialValueEnable"!],
           .channelPwmSocAEventCountInitialValue  = [!"CddPwmAdcEventTriggerSocA/CddPwmSocAEventCountInitialValue"!],
           .channelPwmSocAInterruptCount          = [!"CddPwmAdcEventTriggerSocA/CddPwmSocAInterruptCount"!],
           .channelPwmSocAInterruptEventSources   = [!"CddPwmAdcEventTriggerSocA/CddPwmSocAInterruptEventSources"!],
           .channelPwmSocAMixedSources   = [!CALL "GetBooleanExpressionMIX_TBCTR_ZERO", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrZero"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_PERIOD", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrPeriod"!] |[!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPA", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrUCmpA"!] |[!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPA", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrDCmpA"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPB", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrUCmpB"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPB", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrDCmpB"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPC", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrUCmpC"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPC", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrDCmpC"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPD", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrUCmpD"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPD", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmIntSocAMixTbctrDCmpD"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_DCAEVT1", "Parameter" = "CddPwmAdcEventTriggerSocA/CddPwmSocAMixedSources/CddPwmSocAIntMixDCAEvt1"!],
           
           /* SOC B Event for ADC. */
           .channelPwmSocBEvent         = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBEpwmEvent"!],
           .channelPwmSocBForceEventValue         = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBForceEventValue"!],
           .channelPwmSocBEventCountInitialValueEnable  = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBEventCountInitialValueEnable"!],
           .channelPwmSocBEventCountInitialValue  = [!"CddPwmAdcEventTriggerSocB/CddPwmSocBEventCountInitialValue"!],
           .channelPwmSocBInterruptCount          = [!"CddPwmAdcEventTriggerSocB/CddPwmSocBInterruptCount"!],
           .channelPwmSocBInterruptEventSources   = [!"CddPwmAdcEventTriggerSocB/CddPwmSocBInterruptEventSources"!],
           .channelPwmSocBMixedSources   = [!CALL "GetBooleanExpressionMIX_TBCTR_ZERO", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrZero"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_PERIOD", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrPeriod"!] |[!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPA", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrUCmpA"!] |[!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPA", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrDCmpA"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPB", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrUCmpB"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPB", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrDCmpB"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPC", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrUCmpC"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPC", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrDCmpC"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_U_CMPD", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrUCmpD"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_TBCTR_D_CMPD", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmIntSocBMixTbctrDCmpD"!] | [!//
                                                [!CALL "GetBooleanExpressionMIX_DCAEVT1", "Parameter" = "CddPwmAdcEventTriggerSocB/CddPwmSocBMixedSources/CddPwmSocBIntMixDCAEvt1"!],           
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of CddPwmAdcEventTrigger Loop*/!][!//



[!VAR "Index1" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_TripZoneType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_TripZoneRef[CDD_PWM_TIMER_TRIP_ZONE_NUM_CHANNELS] =
{
    [!LOOP "CddPwmTripZone/*"!][!/*Cdd_Pwm_TripZoneRef Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           .channelPwmAdvancedTripZoneAction  = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAdvancedTripZoneAction"!],
           .channelPwmEvent                   = [!"CddPwmTZA/CddPwmTZAEvent"!],
           .channelPwmTZAEvent                = [!"CddPwmTZA/CddPwmTZAEvent"!],
           .channelPwmTZBEvent                = [!"CddPwmTZB/CddPwmTZBEvent"!],
           .channelPwmTZAAdvUEvent            = [!"CddPwmTZA/CddPwmTZAAdvUEvent"!],
           .channelPwmTZAAdvDEvent            = [!"CddPwmTZA/CddPwmTZAAdvDEvent"!],
           .channelPwmTZBAdvUEvent            = [!"CddPwmTZB/CddPwmTZBAdvUEvent"!],
           .channelPwmTZBAdvDEvent            = [!"CddPwmTZB/CddPwmTZBAdvDEvent"!],
           .channelPwmDCAEVT1Event            = [!"CddPwmDCA/CddPwmDCAEVT1Event"!],
           .channelPwmDCAEVT1AdvUEvent        = [!"CddPwmDCA/CddPwmDCAEVT1AdvUEvent"!],
           .channelPwmDCAEVT1AdvDEvent        = [!"CddPwmDCA/CddPwmDCAEVT1AdvDEvent"!],
           .channelPwmDCAEVT2Event            = [!"CddPwmDCA/CddPwmDCAEVT2Event"!],
           .channelPwmDCAEVT2AdvUEvent        = [!"CddPwmDCA/CddPwmDCAEVT2AdvUEvent"!],
           .channelPwmDCAEVT2AdvDEvent        = [!"CddPwmDCA/CddPwmDCAEVT2AdvDEvent"!],
           .channelPwmDCBEVT1Event            = [!"CddPwmDCB/CddPwmDCBEVT1Event"!],
           .channelPwmDCBEVT1AdvUEvent        = [!"CddPwmDCB/CddPwmDCBEVT1AdvUEvent"!],
           .channelPwmDCBEVT1AdvDEvent        = [!"CddPwmDCB/CddPwmDCBEVT1AdvDEvent"!],
           .channelPwmDCBEVT2Event            = [!"CddPwmDCB/CddPwmDCBEVT2Event"!],
           .channelPwmDCBEVT2AdvUEvent        = [!"CddPwmDCB/CddPwmDCBEVT2AdvUEvent"!],
           .channelPwmDCBEVT2AdvDEvent        = [!"CddPwmDCB/CddPwmDCBEVT2AdvDEvent"!],
           .channelPwmOneShotTZ1             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotTZ1"!],
           .channelPwmOneShotTZ2             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotTZ2"!],
           .channelPwmOneShotTZ3             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotTZ3"!],
           .channelPwmOneShotTZ4             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotTZ4"!],
           .channelPwmOneShotTZ5             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotTZ5"!],
           .channelPwmOneShotTZ6             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotTZ6"!],
           .channelPwmOneShotDCAEVT1             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotDCAEVT1"!],
           .channelPwmOneShotDCBEVT1             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmOneShotTZ/CddPwmOneShotDCBEVT1"!],
           .channelPwmCBCTZ1             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCTZ1"!],
           .channelPwmCBCTZ2             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCTZ2"!],
           .channelPwmCBCTZ3             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCTZ3"!],
           .channelPwmCBCTZ4             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCTZ4"!],
           .channelPwmCBCTZ5             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCTZ5"!],
           .channelPwmCBCTZ6             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCTZ6"!],
           .channelPwmDCAEVT2            = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCDCAEVT2"!],
           .channelPwmDCBEVT2            = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmCBCTZ/CddPwmCBCDCBEVT2"!],
           .channelPwmTZCBCInterrupt             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmInterrupt/CddPwmTZCBCInterrupt"!],
           .channelPwmTZOneShotInterrupt             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmInterrupt/CddPwmTZOneShotInterrupt"!],
           .channelPwmDCAEVT1Interrupt             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmInterrupt/CddPwmDCAEVT1Interrupt"!],
           .channelPwmDCAEVT2Interrupt             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmInterrupt/CddPwmDCAEVT2Interrupt"!],
           .channelPwmDCBEVT1Interrupt             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmInterrupt/CddPwmDCBEVT1Interrupt"!],
           .channelPwmDCBEVT2Interrupt             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmInterrupt/CddPwmDCBEVT2Interrupt"!],
           .channelPwmCycleByCycleTripZoneClearMode             = [!"CddPwmCycleByCycleTripZoneClearMode"!],
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_TripZoneRef Loop*/!][!//

[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmDigitalCompareEnable"!][!//
[!VAR "Index1" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_DigitalCompareType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_DigitalCompareRef[CDD_PWM_DIGITAL_COMPARE_NUM_CHANNELS] =
{
    [!LOOP "CddPwmDigitalCompare/*"!][!/*CddPwmDigitalCompareRef Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           .channelPwmDCAHigh                            = [!"CddPwmDigitalCompareAEVT/CddPwmDCAHigh"!],
           .channelPwmDCALow                             = [!"CddPwmDigitalCompareAEVT/CddPwmDCALow"!],
           .channelPwmDCAOutputHigh1A                    = [!"CddPwmDigitalCompareAEVT/CddPwmDCAOutputHigh1A"!],
           .channelPwmDCAOutputHigh2A                    = [!"CddPwmDigitalCompareAEVT/CddPwmDCAOutputHigh2A"!],/*enum MaCROS*/
           .channelPwmAdcSocEventA                       = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDigitalCompareAEVT/CddPwmAdcSocEventA"!],
           .channelPwmSyncOutEventA                      = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDigitalCompareAEVT/CddPwmSyncOutEventA"!],
           .channelPwmSyncModeAEVT1                      = [!"CddPwmDigitalCompareAEVT/CddPwmSyncModeAEVT1"!],
           .channelPwmSignalSoureAEVT1                   = [!"CddPwmDigitalCompareAEVT/CddPwmSignalSoureAEVT1"!],
           .channelPwmCBCLatchModeDCAEVT1                = [!"CddPwmDigitalCompareAEVT/CddPwmCBCLatchModeDCAEVT1"!],
           .channelPwmCBCLatchClearModeDCAEVT1           = [!"CddPwmDigitalCompareAEVT/CddPwmCBCLatchClearModeDCAEVT1"!],
           .channelPwmSyncModeAEVT2                      = [!"CddPwmDigitalCompareAEVT/CddPwmSyncModeAEVT2"!],
           .channelPwmSignalSoureAEVT2                   = [!"CddPwmDigitalCompareAEVT/CddPwmSignalSoureAEVT2"!],
           .channelPwmCBCLatchModeDCAEVT2                = [!"CddPwmDigitalCompareAEVT/CddPwmCBCLatchModeDCAEVT2"!],
           .channelPwmCBCLatchClearModeDCAEVT2           = [!"CddPwmDigitalCompareAEVT/CddPwmCBCLatchClearModeDCAEVT2"!],
           .channelPwmDCBHigh                            = [!"CddPwmDigitalCompareBEVT/CddPwmDCBHigh"!],
           .channelPwmDCBLow                             = [!"CddPwmDigitalCompareBEVT/CddPwmDCBLow"!],
           .channelPwmDCBOutputHigh1A                    = [!"CddPwmDigitalCompareBEVT/CddPwmDCBOutputHigh1B"!],
           .channelPwmDCBOutputHigh2A                    = [!"CddPwmDigitalCompareBEVT/CddPwmDCBOutputHigh2B"!],/*enum MaCROS*/
           .channelPwmAdcSocEventB                       = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDigitalCompareBEVT/CddPwmAdcSocEventB"!],
           .channelPwmSyncOutEventB                      = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDigitalCompareBEVT/CddPwmSyncOutEventB"!],
           .channelPwmSyncModeBEVT1                      = [!"CddPwmDigitalCompareBEVT/CddPwmSyncModeBEVT1"!],
           .channelPwmSignalSoureBEVT1                   = [!"CddPwmDigitalCompareBEVT/CddPwmSignalSoureBEVT1"!],
           .channelPwmCBCLatchModeDCBEVT1                = [!"CddPwmDigitalCompareBEVT/CddPwmCBCLatchModeDCBEVT1"!],
           .channelPwmCBCLatchClearModeDCBEVT1           = [!"CddPwmDigitalCompareBEVT/CddPwmCBCLatchClearModeDCBEVT1"!],
           .channelPwmSyncModeBEVT2                      = [!"CddPwmDigitalCompareBEVT/CddPwmSyncModeBEVT2"!],
           .channelPwmSignalSoureBEVT2                   = [!"CddPwmDigitalCompareBEVT/CddPwmSignalSoureBEVT2"!],
           .channelPwmCBCLatchModeDCBEVT2                = [!"CddPwmDigitalCompareBEVT/CddPwmCBCLatchModeDCBEVT2"!],
           .channelPwmCBCLatchClearModeDCBEVT2     = [!"CddPwmDigitalCompareBEVT/CddPwmCBCLatchClearModeDCBEVT2"!],
		   .channelPwmDcFilterInputEventSource           = [!"CddPwmDcFilterInputEventSource"!],
           .channelPwmCddPwmBlankingWindow               = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmUseBlankingWindow/CddPwmUseBlankingWindow"!],
           [!IF "CddPwmUseBlankingWindow/CddPwmUseBlankingWindow = 'true'"!][!//
           .channelPwmCddPwmBlankingWindowStartEvent     = [!"CddPwmUseBlankingWindow/BlankingWindowStartEvent"!],
           .channelPwmCddPwmBlankingWindowOffset         = [!"CddPwmUseBlankingWindow/BlankingWindowOffset"!],
           .channelPwmCddPwmBlankingWindowLength         = [!"CddPwmUseBlankingWindow/BlankingWindowLength"!], 
           [!IF "CddPwmUseBlankingWindow/BlankingWindowStartEvent = 'EPWM_DC_WINDOW_START_TBCTR_BLANK_PULSE_MIX'"!][!//
           .channelPwmCddPwmBlankingWindowMixedEvent     = [!"CddPwmUseBlankingWindow/BlankingWindowStartMixedEvent"!],
           [!ENDIF!][!//
           .channelPwmCddPwmDCCounterCapture             = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmUseDCCounterCapture/CddPwmUseDCCounterCapture"!],
           [!IF "CddPwmUseDCCounterCapture/CddPwmUseDCCounterCapture = 'true'"!][!//
           .channelPwmCddPwmDCCounterCaptureShadowMode   = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmUseDCCounterCapture/CddPwmDCCounterCaptureShadowMode"!],
           [!ENDIF!][!//
           .channelPwmCddPwmUseEdgeFilter                = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmUseEdgeFilter/CddPwmUseEdgeFilter"!],
            [!IF "CddPwmUseEdgeFilter/CddPwmUseEdgeFilter = 'true'"!][!//
           .channelPwmCddPwmEdgeFilterMode               = [!"CddPwmUseEdgeFilter/CddPwmEdgeFilterMode"!],
           .channelPwmCddPwmEdgeFilterCount              = [!"CddPwmUseEdgeFilter/CddPwmEdgeFilterCount"!],
           .channelPwmCddPwmEdgeFilterValleyCapture      = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmUseEdgeFilter/CddPwmEdgeFilterValleyCapture"!],
           .channelPwmDelayedOutputEdgeFilter            = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmUseEdgeFilter/CddPwmDelayedOutputEdgeFilter"!],
           [!IF "CddPwmUseEdgeFilter/CddPwmEdgeFilterValleyCapture = 'true'"!][!//
           .channelPwmEdgeFilterCounterCaptureSignal     = [!"CddPwmUseEdgeFilter/CddPwmUseEdgeFilterCounterCaptureSignal"!],
           .channelPwmStartValleyCaptureLogic            = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmUseEdgeFilter/CddPwmStartValleyCaptureLogic"!],
           .channelPwmStartValleyCapture                 = [!"CddPwmUseEdgeFilter/CddPwmStartValleyCapture"!],
           .channelPwmStopValleyCapture                  = [!"CddPwmUseEdgeFilter/CddPwmStopValleyCapture"!],
           [!ENDIF!][!//
           [!IF "CddPwmUseEdgeFilter/CddPwmDelayedOutputEdgeFilter = 'true'"!][!//
           .channelPwmSoftwareValleyDelayValue          = [!"CddPwmUseEdgeFilter/SoftwareValleyDelayValue"!],
           .channelPwmValleyDelayDivider                = [!"CddPwmUseEdgeFilter/CddPwmValleyDelayDivider"!],
           [!ENDIF!][!//
           [!ENDIF!][!//
           [!ENDIF!][!//   
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_DigitalCompare Loop*/!][!//       
[!ENDIF!][!//

[!VAR "Index1" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_DeadBandType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_DeadBandRef[CDD_PWM_TIMER_DEAD_BAND_NUM_CHANNELS] =
{
    [!LOOP "CddPwmDeadBand/*"!][!/*Cdd_Pwm_DeadBandRef Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           .channelDeadBandClockMode     =  [!"CddPwmDeadBandClockMode"!],
           .channelDeadBandGlobalLoad    =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDeadBandGlobalLoad"!],
           .channelDeadBandShadowMode    =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDeadBandShadowMode"!],
           .channelRedGlobalLoad         =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmRedSetting/CddPwmRedGlobalLoad"!],
           .channelRedShadowMode         =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmRedSetting/CddPwmRedShadowMode"!],
           .channelFedGlobalLoad         =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmFedSetting/CddPwmFedGlobalLoad"!],
           .channelFedShadowMode         =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmFedSetting/CddPwmFedShadowMode"!],
           .channelREDEnable             =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmRedSetting/CddPwmREDEnable"!],
           .channelFEDEnable             =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmFedSetting/CddPwmFEDEnable"!],
           .channelREDDelayValue         =  [!"CddPwmRedSetting/CddPwmREDDelayValue"!],
           .channelFEDDelayValue         =  [!"CddPwmFedSetting/CddPwmFEDDelayValue"!],
           .channelDeadBandSwapOutputA   =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDeadBandSwapOutputA"!],
           .channelDeadBandSwapOutputB   =  [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDeadBandSwapOutputB"!],
           .channelDeadBandDelayLoadMode =  [!"CddPwmDeadBandDelayLoadMode"!],
           .channelPwmRedDelayLoadMode =  [!"CddPwmRedSetting/CddPwmRedDelayLoadMode"!],
           .channelPwmFedDelayLoadMode =  [!"CddPwmFedSetting/CddPwmFedDelayLoadMode"!],
           .channelPwmRedBandPolarity      =  [!"CddPwmRedSetting/CddPwmRedBandPolarity"!],
           .channelPwmFedBandPolarity      =  [!"CddPwmFedSetting/CddPwmFedBandPolarity"!],
           .channelPwmREDDelayInput        =  [!"CddPwmRedSetting/CddPwmREDDelayInput"!],
           .channelPwmFEDDelayInput        =  [!"CddPwmFedSetting/CddPwmFEDDelayInput"!],
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_DeadBandRef Loop*/!][!//

[!VAR "Index1" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_ChopperType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_ChopperRef[CDD_PWM_TIMER_CHOPPER_NUM_CHANNELS] =
{
    [!LOOP "CddPwmChopper/*"!][!/*Cdd_Pwm_ChopperRef Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
           .channelChopperEnable          = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmChopperEnable"!],
           .channelChopperDuty            = [!"CddPwmChopperDuty"!],
           .channelChopperFreqency        = [!"CddPwmChopperFreqency"!],
           .channelChopperFirstPulseWidth = [!"CddPwmChopperFirstPulseWidth"!],
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_ChopperRef Loop*/!][!//


[!VAR "Index1" = "0"!][!//
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
static CONST(struct Cdd_Pwm_HrPwmType_s, CDD_PWM_CONFIG_DATA) 
Cdd_Pwm_HrPwmRef[CDD_PWM_TIMER_HRPWM_NUM_CHANNELS] =
{
    [!LOOP "CddPwmHighResolutionPwm/*"!][!/*Cdd_Pwm_HRPWMRef Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
            .channelHrPwmEnable              = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmEnableHRPWM"!],
            .channelAutoHRMStepScalingEnable = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmAutoHRMStepScaling"!],
            .channelHrCtrlModeEPWMA          = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmCtrlModeHRPWMA"!],
            .channelHrCtrlModeEPWMB          = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmCtrlModeHRPWMB"!],
            
            /* HPWM  Duty , Period  and Phase control */
            .channelHrSelEdgeModeEPWMA       = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmEdgeModeHRPWMA"!],
            .channelHrCmpHRPWMA              = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmCmpHRPWMA"!],
            .channelHrShadowActiveLoadPwmA   = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmShadowActiveLoadEventHRPWMA"!],
            
            .channelHrSelEdgeModeEPWMB       = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmEdgeModeHRPWMB"!],
            .channelHrCmpHRPWMB              = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmCmpHRPWMB"!],
            .channelHrShadowActiveLoadPwmB   = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmShadowActiveLoadEventHRPWMB"!],
            
            .channelHrPeriodCtrlEnable       = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDutyPeriodPhaseCtrl/CddPwmEnableHRPeriodCtrl"!],
            .channelHrPeriod                 = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmHRPeriod"!],
            
            .channelHrPhaseCtrlEnable        = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDutyPeriodPhaseCtrl/CddPwmEnableHRPhaseCtrl"!],
            .channelHrPhase                  = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmHRPhase"!],
            .channelPwmSyncSelect            = [!"CddPwmDutyPeriodPhaseCtrl/CddPwmPWMSyncSelect"!],
            
            /* HPWM  Deadband Control */
            .channelHrDeadbandEdgeMode       = [!"CddPwmDeadbandCtrl/CddPwmDeadbandEdgeMode"!],
            .channelHrRisEdgeDelay           = [!"CddPwmDeadbandCtrl/CddPwmRisingEdgeDelay"!],
            .channelHrDbRisShadowActiveLoad  = [!"CddPwmDeadbandCtrl/CddPwmRisEdgeShadowActiveLoad"!],
            
            .channelHrFalEdgeDelay           = [!"CddPwmDeadbandCtrl/CddPwmFallingEdgeDelay"!],
            .channelHrDbFalShadowActiveLoad  = [!"CddPwmDeadbandCtrl/CddPwmFalEdgeShadowActiveLoad"!],
            
            .channelHrSwapOutputCtrl         = [!CALL "GetBooleanExpression", "Parameter" = "CddPwmDeadbandCtrl/CddPwmSwapOutputCtrl"!],
            .channelHrOutputCtrl              = [!"CddPwmDeadbandCtrl/CddPwmHROutputCtrlPWMB"!],
            
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of Cdd_Pwm_HRPWMRef Loop*/!][!//


[!AUTOSPACING!]
[!VAR "Index" = "0"!][!//
[!VAR "Index1" = "0"!][!//
[!VAR "Ticks" = "0"!][!//
/* Cdd_Pwm Channel Configuration parameters */
[!LOOP "as:modconf('Cdd_Pwm')[1]/CddPwmConfigSet/*"!][!//
CONST(Cdd_Pwm_ConfigType, CDD_PWM_CONFIG_DATA)
     [!"@name"!] =
{
    .chCfg =
    {
    [!LOOP "CddPwmChannel/*"!][!/*Channel Loop */!][!//
        [[!"num:i($Index1)"!]] =
        {
#if (CDD_PWM_NOTIFICATION_SUPPORTED == STD_ON)
            .notificationHandler = (Cdd_Pwm_NotifyFuncType)[!IF "CddPwmNotification != ''"!] [!"CddPwmNotification"!][!ELSE!]NULL_PTR[!ENDIF!], /*Notification Function*/           
            [!IF "node:empty(CddPwmNotification) = 'true'"!][!ERROR "PwmNotification is not configured"!][!ENDIF!][!//
#endif
            .notificationTzHandler = (Cdd_Pwm_TzNotifyFuncType)[!IF "CddPwmTzNotification   != ''"!] [!"CddPwmTzNotification  "!][!ELSE!]NULL_PTR[!ENDIF!], /*Notification Function*/           
            [!IF "node:empty(CddPwmTzNotification  ) = 'true'"!][!ERROR "PwmTzNotification is not configured"!][!ENDIF!][!//
            .baseaddr = [!CALL "GetAddress", "ChannelNumber" = "CddPwmHwChannel", "HWNumber" = "CddPwmGroupUnit"!]UL,            
            .channelID = [!"CddPwmChannelId"!], /* CddPwmChannelId */       
            .channelHwID = CDD_PWM_[!"(substring-after(CddPwmGroupUnit,'CDD_PWM_CONTROLSS_'))"!]_[!"(substring-after(CddPwmHwChannel,'CDD_PWM_'))"!], /* CddPwmHwChannel */ 
            .outputCh = [!"CddPwmOutPutChannelSelection"!], /* CddPwmOutPutChannelSelection */ 
            .polarity = [!"CddPwmPolarity"!], /* CddPwmPolarity */ 
            [!IF "node:empty(CddPwmChannelTimerBaseRef) = 'true'"!][!ERROR "Pwm Channel Timer Base container is not configured or linked."!][!ENDIF!][!//           
            .channelTimerBase = &Cdd_Pwm_TimerBaseRef[[!"node:ref(./CddPwmChannelTimerBaseRef)/CddPwmTimerBaseId"!]], /* CddPwmChannelTimerBaseRef */      
            [!IF "node:empty(CddPwmCounterCompareRef) = 'true'"!][!ERROR "Pwm Channel Counter Compare container is not configured or linked."!][!ENDIF!][!//
            .channelCounterCompare = &Cdd_Pwm_CounterCompareRef[[!"node:ref(./CddPwmCounterCompareRef)/CddPwmCounterCompareId"!]], /* CddPwmCounterCompareRef */      
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmChannelTimerBaseSyncEnable"!][!//
            .channelTimerBaseSync = &Cdd_Pwm_TimerBaseSyncRef[[!"node:ref(./CddPwmChannelTimerBaseSyncRef)/CddPwmTimerBaseSyncId"!]], /* CddPwmChannelTimerBaseSyncRef */  
[!ELSE!][!//    
            .channelTimerBaseSync = NULL_PTR, /* CddPwmActionQualifierRef */        
[!ENDIF!][!//
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmActionQualifierEnable"!][!//
            .channelActionQualifier = &Cdd_Pwm_ActionQualifierRef[[!"node:ref(./CddPwmActionQualifierRef)/CddPwmActionQualifierId"!]], /* CddPwmActionQualifierRef */
[!ELSE!][!//    
            .channelActionQualifier = NULL_PTR, /* CddPwmActionQualifierRef */      
[!ENDIF!][!//
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmEventTriggerEnable"!][!//
            .channelEventTrigger = &Cdd_Pwm_EventTriggerRef[[!"node:ref(./CddPwmEventTriggerRef)/CddPwmEventTriggerId"!]], /* CddPwmEventTriggerRef */
[!ELSE!][!//    
            .channelEventTrigger = NULL_PTR, /* CddPwmEventTriggerRef */        
[!ENDIF!][!//
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmConfigurationOfOptionalApis/CddPwmSetAdcTriggerApi"!][!//
            .channelAdcEventTrigger = &Cdd_Pwm_AdcEventTriggerRefSoc[[!"node:ref(./CddPwmAdcEventTriggerRef)/CddPwmAdcEventTriggerId"!]], /* Cdd_Pwm_AdcEventTriggerRefSoc */
[!ELSE!][!//    
            .channelAdcEventTrigger = NULL_PTR, /* CddPwmEventTriggerRef */        
[!ENDIF!][!//Cdd_Pwm_AdcEventTriggerRefSoc
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmTripZoneEnable"!][!//
            .channelTripZone = &Cdd_Pwm_TripZoneRef[[!"node:ref(./CddPwmTripZoneRef)/CddPwmTripZoneId"!]], /* CddPwmTripZone */  
[!ELSE!][!//    
            .channelTripZone = NULL_PTR, /* CddPwmTripZoneRef */        
[!ENDIF!][!//
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmDigitalCompareEnable"!][!//
            .channelDigitalCompare = &Cdd_Pwm_DigitalCompareRef[[!"node:ref(./CddPwmDigitalCompareRef)/CddPwmDigitalCompareId"!]], /* CddDigitalCompare */  
[!ELSE!][!//    
            .channelDigitalCompare = NULL_PTR, /* CddPwmDigitalCompareRef */        
[!ENDIF!][!//
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmDeadBandEnable"!][!//
            .channelDeadBand = &Cdd_Pwm_DeadBandRef[[!"node:ref(./CddPwmDeadBandRef)/CddPwmDeadBandId"!]], /* CddPwmDeadBand */  
[!ELSE!][!//    
            .channelDeadBand = NULL_PTR, /* CddPwmDeadBandRef */        
[!ENDIF!][!//
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmChopperEnable"!][!//
            .channelChopper = &Cdd_Pwm_ChopperRef[[!"node:ref(./CddPwmChopperRef)/CddPwmChopperId"!]], /* CddPwmChopper */   
[!ELSE!][!//    
            .channelChopper = NULL_PTR, /* CddPwmChopperRef */     
[!ENDIF!][!//  
[!IF "as:modconf('Cdd_Pwm')[1]/CddPwmGeneral/CddPwmChannelHighResPwmEnable"!][!//
            .channelHrPwm = &Cdd_Pwm_HrPwmRef[[!"node:ref(./CddPwmHighResolutionPwmRef)/CddPwmHRPwmId"!]], /* CddPwmHrPwm - */   
[!ELSE!][!//    
            .channelHrPwm = NULL_PTR, /* CddPwmHrPwm */        
[!ENDIF!][!//
 
        }[!VAR "Index1" = "$Index1+1"!][!IF "not(node:islast())"!],[!ENDIF!][!CR!][!ENDLOOP!][!//
    }[!IF "not(node:islast())"!],[!ENDIF!][!CR!]
};
[!VAR "Index" = "$Index+1"!][!ENDLOOP!][!/*End of CddPwmConfigSet Loop*/!][!//

#ifdef __cplusplus
}
#endif

/*</CDD_PWM_CONFIGURATION>*/
#define CDD_PWM_STOP_SEC_CONFIG_DATA
#include "Cdd_Pwm_MemMap.h"

/**********************************************************************************************************************
 *  END OF FILE: Cdd_Pwm_PBcfg.c                                                                                          *
 *********************************************************************************************************************/
[!ELSE!]
/* The last generated configuration variant is not 
       PRECOMPILE variant. Refer Cdd_Pwm_Cfg.c */
[!ENDIF!]