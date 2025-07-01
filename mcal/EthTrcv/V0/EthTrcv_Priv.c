/* ======================================================================
 *   Copyright (C) 2022-2023 Texas Instruments Incorporated
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
 *  \file     EthTrcv.c
 *
 *  \brief    This file contains ETH TRANCEIVER MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "SchM_EthTrcv.h"
#include "EthTrcv.h"
#if (STD_ON == ETHTRCV_DEV_ERROR_DETECT)
#include "Det.h"
#endif /* #if (STD_ON == ETHTRCV_DEV_ERROR_DETECT) */
#include "Dem.h"
#include "string.h"
#include "Std_Types.h"

#define ETHTRCV_START_SEC_CODE
#include "EthTrcv_MemMap.h"

#include "hw_types.h"
#define ETHTRCV_STOP_SEC_CODE
#include "EthTrcv_MemMap.h"
#include "SchM_EthTrcv.h"
#include "Eth.h"
#include "EthTrcv_Priv.h"
#include "EthTrcv_Types.h"
#include "Os.h"
#include "SchM_EthTrcv.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define ETHTRCV_AUTONEGOTIATION_WAITSTATUS_RETRIES (1000000U)
#define ETHTRCV_FORCE_WAIT_RETRIES                 (50000U)
#define ETHTRCV_LINKSTATUS_RETRIES                 (50000U)
#define ETHTRCV_FORCE_RETRIES                      (20000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Returns the status of Auto Negotiation completion.
 *
 * \param   CtrlIdx     PHY device ID.
 * \param   trcvIdx     PHY device instance.
 *
 * \retval  TRUE        Auto negotiation is completed
 * \retval  FALSE       Auto negotiation is not completed
 */
static uint32 EthTrcv_getAutoNegStatus(uint8 CtrlIdx, uint8 trcvIdx);

/**
 * \brief   Reads the Link Partner Ability register of the PHY.
 *
 * \param   CtrlIdx       PHY device ID.
 * \param   trcvIdx       PHY device instance.
 * \param   pPartnerAblty Auto negotiation partner ability.
 * \param   isGigCapab    Gigabit capability of the PHY.
 *                        	TRUE - PHY is gigabit capable.
 *                        	FALSE - PHY is non-gigabit capable.
 *
 * \retval  E_OK      Link Partner Ability status read successful.
 * \retval  E_NOT_OK  Link Partner Ability status read failed.
 */
static Std_ReturnType EthTrcv_getPartnerAbility(uint8 CtrlIdx, uint8 trcvIdx, uint32 *pPartnerAblty, uint32 isGigCapab);
/**
 * \brief Delay function.
 *
 * \param  count - Halts execution depend upon the value of the variable.
 *
 * \return none
 */
static void           EthTrcv_delayExecution(TickType count);

/**
 * \brief   Writes a register with the input
 *
 * \param   CtrlIdx    PHY device ID.
 * \param   trcvIdx    PHY device instance.
 * \param   regAddr    Address of the register to be written.
 * \param   regVal     Value to be written.
 *
 * \retval E_OK        PHY register write successful.
 * \retval E_NOT_OK    PHY register write failed.
 */

static Std_ReturnType EthTrcv_checkPhyConfig(const EthTrcv_ConfigType *pEthTrcvCfg, uint32 forceRetries);

static void EthTrcv_setDuplexMode(const EthTrcv_ConfigType *pEthTrcvCfg, uint16 *regVal);

static void EthTrcv_updatePartnerAbility(uint32 *pPartnerAblty, uint16 regVal);

static void EthTrcv_setAutomaticNegotiationSpeedCapability(const EthTrcv_ConfigType *pEthTrcvCfg, uint16 *ptrData);

static Std_ReturnType EthTrcv_setAutoNeg(const EthTrcv_CtrlObjType *pEthTrcvObj, const EthTrcv_ConfigType *pEthTrcvCfg,
                                         uint16 *ptrData);

static uint32 EthTrcv_countautoNegRetries(const EthTrcv_CtrlObjType *pEthTrcvObj, uint32 autoNegRetries);

static Std_ReturnType EthTrcv_configsetBaudRateAndDuplexMode(EthTrcv_ConfigType *pEthTrcvCfg);
static Std_ReturnType EthTrcv_setBaudRateAndDuplexMode(const EthTrcv_CtrlObjType *pEthTrcvObj,
                                                       EthTrcv_ConfigType *pEthTrcvCfg, uint32 *ptrAutoNegRetries);

static Std_ReturnType EthTrcv_SetMiiMode(EthTrcv_CtrlObjType *pEthTrcvObj);

static Std_ReturnType EthTrcv_WriteMMDIndirect(uint8 ctrlIdx, uint8 trcvIdx, uint32 regIdx, uint16 regVal);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint32 EthTrcv_ControllerModeChangeFlag[ETHTRCV_MAX_CONTROLLER] = {(uint32)FALSE, (uint32)FALSE};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ETHTRCV_START_SEC_CODE
#include "EthTrcv_MemMap.h"

/**
 * \brief Initializes driver object for the GMACSW instance
 *
 * \param  instNum   Pointer to  GMACSW driver object to be initialised.
 */
void EthTrcv_resetDrvObj(EthTrcv_DrvObject *pEthTrcvDrvObj)
{
    pEthTrcvDrvObj->ctrlIdx = ETHTRCV_CONTROLLER_ID_0;
    /* clear transceiver object structure */
    (void)memset(&(pEthTrcvDrvObj->ethTrcvCtrlObj), 0, sizeof(pEthTrcvDrvObj->ethTrcvCtrlObj));
};

static Std_ReturnType EthTrcv_WriteMMDIndirect(uint8 ctrlIdx, uint8 trcvIdx, uint32 regIdx, uint16 regVal)
{
    Std_ReturnType retVal = E_OK;
    uint16         data;

    retVal = EthTrcv_regWrite(ctrlIdx, trcvIdx, 0x0D, 0x001F);

    retVal += EthTrcv_regWrite(ctrlIdx, trcvIdx, 0x0E, regIdx);

    retVal += EthTrcv_regWrite(ctrlIdx, trcvIdx, 0x0D, 0x401F);

    retVal += EthTrcv_regRead(ctrlIdx, trcvIdx, 0x0E, &data);

    retVal += EthTrcv_regWrite(ctrlIdx, trcvIdx, 0x0D, 0x401F);

    data = (data & ~regVal) | regVal;

    retVal += EthTrcv_regWrite(ctrlIdx, trcvIdx, 0x0E, data);

    if (((Std_ReturnType)E_OK) != retVal)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

static Std_ReturnType EthTrcv_SetMiiMode(EthTrcv_CtrlObjType *pEthTrcvObj)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    retVal = EthTrcv_WriteMMDIndirect(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, ETHTRCV_OP_MODE_DECODE,
                                      ETHTRCV_OP_MODE_DECODE_MII_MASK);

    if (((Std_ReturnType)E_OK) != retVal)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType EthTrcv_ConfigInit(EthTrcv_ConfigType *pEthTrcvCfg, EthTrcv_CtrlObjType *pEthTrcvObj)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;

    if (((uint32)MII) == pEthTrcvCfg->MiiSel)
    {
        retVal = EthTrcv_SetMiiMode(pEthTrcvObj);
    }

    if (retVal == (Std_ReturnType)E_OK)
    {
        if (((uint32)TRUE) == pEthTrcvCfg->enableAutoNeg)
        {
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
            if (0U != (pEthTrcvCfg->advertiseCapab & ETHERNET_ADV_CAPAB_1000_HALF))
            {
                /* Gigabit Half duplex is not supported */
                pEthTrcvCfg->advertiseCapab &= ~ETHERNET_ADV_CAPAB_1000_HALF;
            }
#endif /* #if(STD_ON == ETHTRCV_1000MBPS_MACRO) */
            if (0U != pEthTrcvCfg->advertiseCapab)
            {
                /*
                 * Auto negotiate and get the speed and duplex
                 * parameters.
                 */
                retVal = EthTrcv_configAndStartAutoNegotiation(pEthTrcvObj);
            }
            else
            {
                retVal = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
            if ((ETHTRCV_BAUD_RATE_1000MBIT == pEthTrcvCfg->baudRate) &&
                (ETHTRCV_DUPLEX_MODE_HALF == pEthTrcvCfg->duplexMode))
            {
                /* Gigabit Half duplex is not supported */
                retVal = (Std_ReturnType)E_NOT_OK;
            }
            else
#endif /* #if(STD_ON == ETHTRCV_1000MBPS_MACRO) */
            {
                retVal = EthTrcv_forceConfig(pEthTrcvObj);
            }
        }
    }

    return retVal;
}

Std_ReturnType EthTrcv_Initilization(uint8 TrcvIdx)
{
    EthTrcv_ConfigType  *pEthTrcvCfg = (EthTrcv_ConfigType *)NULL_PTR;
    EthTrcv_CtrlObjType *pEthTrcvObj = (EthTrcv_CtrlObjType *)NULL_PTR;
    Std_ReturnType       retVal      = (Std_ReturnType)E_NOT_OK;

    pEthTrcvObj = &(EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx]);
    pEthTrcvCfg = &(EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx].ethTrcvCfg);

    retVal = EthTrcv_resetController(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx);

    if (((Std_ReturnType)E_OK) == retVal)
    {
        retVal = EthTrcv_ConfigInit(pEthTrcvCfg, pEthTrcvObj);

        if (((uint32)TRUE) == pEthTrcvCfg->loopbackEnable)
        {
            retVal = EthTrcv_enableLoopBack(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint32)TRUE);
        }
        else
        {
            if ((uint32)FALSE == EthTrcv_getLinkStatus(EthTrcv_DrvObj.ctrlIdx, TrcvIdx))
            {
                /*
                 * SWS_EthTrcv_00040: check access to controller access
                 * and report production error ETHTRCV_E_ACCESS.
                 */
#ifdef ETHTRCV_E_ACCESS
                Dem_SetEventStatus(ETHTRCV_E_ACCESS, DEM_EVENT_STATUS_PREFAILED);
#endif /* #ifdef ETHTRCV_E_ACCESS */
                retVal = (Std_ReturnType)E_NOT_OK;
            }
        }
    }
    return retVal;
}

Std_ReturnType EthTrcv_configAndStartAutoNegotiation(EthTrcv_CtrlObjType *pEthTrcvObj)
{
    Std_ReturnType      retVal         = (Std_ReturnType)E_NOT_OK;
    uint32              autoNegRetries = ETHTRCV_AUTONEGOTIATION_WAITSTATUS_RETRIES;
    uint16              regVal         = 0U;
    uint16              dataBcr        = 0U;
    EthTrcv_ConfigType *pEthTrcvCfg    = &(pEthTrcvObj->ethTrcvCfg);

    if (NULL != pEthTrcvObj)
    {
        /* Performing Auto-Negotiation */
        retVal = EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_BMC, &dataBcr);

        if (((Std_ReturnType)E_OK) == retVal)
        {
            HW_SET_FIELD16(dataBcr, ETHTRCV_BMC_AUTONEG_ENABLE, ETHTRCV_BMC_AUTONEG_ENABLE);

            /* Set the configurations */
            retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_BMC, dataBcr);
        }

        if (((Std_ReturnType)E_OK) == retVal)
        {
            if ((Std_ReturnType)E_OK ==
                EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_AUTO_NEG_ADV, &regVal))
            {
                EthTrcv_setAutomaticNegotiationSpeedCapability(pEthTrcvCfg, &regVal);
                /* Set the configurations */
                retVal =
                    EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_AUTO_NEG_ADV, regVal);
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
                (void)EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_GENCFG1, &regVal);
                /* Disabling 1000 Mbps Half Duplex as controller does not support */
                regVal &= ETHTRCV_DISABLE_1000M_HALF_Duplex;
                retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_GENCFG1, regVal);
#else /* #if(STD_ON == ETHTRCV_1000MBPS_MACRO) */

                (void)EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_GENCFG1, &regVal);
                regVal &= ETHTRCV_DISABLE_1000M;
                retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_GENCFG1, regVal);
#endif
            }
        }

        if (((Std_ReturnType)E_OK) == retVal)
        {
            retVal = EthTrcv_setAutoNeg(pEthTrcvObj, pEthTrcvCfg, &regVal);
        }

        if (((Std_ReturnType)E_OK) == retVal)
        {
            if ((Std_ReturnType)E_OK ==
                EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_BMC, &regVal))
            {
                HW_SET_FIELD16(regVal, ETHTRCV_BMC_RESTART_AUTONEG, ETHTRCV_BMC_RESTART_AUTONEG_ENABLE);

                /* Set the configurations */
                retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_BMC, regVal);
            }
        }
    }

    if (((Std_ReturnType)E_OK) == retVal)
    {
        retVal = EthTrcv_setBaudRateAndDuplexMode(pEthTrcvObj, pEthTrcvCfg, &autoNegRetries);
    }
    else
    {
        /* Auto-Negotiation configuration failed */
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType EthTrcv_forceConfig(const EthTrcv_CtrlObjType *pEthTrcvObj)
{
    uint32                    forceRetries = ETHTRCV_FORCE_WAIT_RETRIES;
    uint16                    regVal       = 0U;
    const EthTrcv_ConfigType *pEthTrcvCfg  = &(pEthTrcvObj->ethTrcvCfg);
    Std_ReturnType            retVal       = (Std_ReturnType)E_NOT_OK;

    if (NULL != pEthTrcvObj)
    {
        retVal = EthTrcv_resetController(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx);
    }
    if (((Std_ReturnType)E_OK) == retVal)
    {
        while ((uint32)0 != forceRetries)
        {
            EthTrcv_delayExecution((TickType)ETHTRCV_LINKSTATUS_WAITCOUNT_TICKS);

            /* Check if PHY link is there or not */
            if ((uint32)FALSE == EthTrcv_getLinkStatus(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx))
            {
                /* PHY Link is Down.*/
                break;
            }

            forceRetries--;
        }
    }
    else
    {
        /* PHY Reset Failed */
    }

    /* Performing Manual Configuration */

    if (((Std_ReturnType)E_OK) == retVal)
    {
        EthTrcv_setDuplexMode(pEthTrcvCfg, &regVal);
        /* Set the configurations */
        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_BMC, regVal);
    }

    if (((uint32)FALSE) == pEthTrcvCfg->loopbackEnable)
    {
        if (((Std_ReturnType)E_OK) == retVal)
        {
            volatile uint32 forceStatus = (uint32)FALSE;
            forceRetries                = ETHTRCV_FORCE_RETRIES;

            while (0U != forceRetries)
            {
                EthTrcv_delayExecution((TickType)ETHTRCV_LINKSTATUS_WAITCOUNT_TICKS);

                /* Check if PHY link is there or not */
                forceStatus = EthTrcv_getLinkStatus(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx);
                if (((uint32)TRUE) == forceStatus)
                {
                    break;
                }

                forceRetries--;
            }

            retVal = EthTrcv_checkPhyConfig(pEthTrcvCfg, forceRetries);
        }
    }

    /*Phy Configuration Not Successful. */
    /*PHY link connectivity failed for phyAddr */

    return retVal;
}

Std_ReturnType EthTrcv_enableLoopBack(uint8 CtrlIdx, uint8 trcvIdx, uint32 enableLoopBack)
{
    uint16         regVal = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

    if (((Std_ReturnType)E_OK) == EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, &regVal))
    {
        if (((uint32)TRUE) == enableLoopBack)
        {
            HW_SET_FIELD16(regVal, ETHTRCV_BMC_LOOPBACK, ETHTRCV_BMC_LOOPBACK_ENABLE);
        }
        else
        {
            HW_SET_FIELD16(regVal, ETHTRCV_BMC_LOOPBACK, ETHTRCV_BMC_LOOPBACK_DISABLE);
        }
        /*Disable Auto-negotiation */
        regVal &= (~ETHTRCV_BMC_AUTONEG_ENABLE_MASK);

        retVal = EthTrcv_regWrite(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, regVal);
    }

    return retVal;
}

Std_ReturnType EthTrcv_resetController(uint8 CtrlIdx, uint8 trcvIdx)
{
    uint16         regVal = 0U;
    uint16         count  = 0xFFFU;
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

    if ((Std_ReturnType)E_OK == EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, &regVal))
    {
        HW_SET_FIELD16(regVal, ETHTRCV_BMC_RESET, ETHTRCV_BMC_RESET_ENABLE);

        /* Reset the PHY. */
        retVal = EthTrcv_regWrite(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, regVal);
    }

    if (((Std_ReturnType)E_OK) == retVal)
    {
        retVal = EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, &regVal);
    }
    if (((Std_ReturnType)E_OK) == retVal)
    {
        /* wait till the reset bit is auto cleared. */
        while ((ETHTRCV_BMC_RESET_ENABLE == (uint32)HW_GET_FIELD(regVal, ETHTRCV_BMC_RESET)) && (0U != count))
        {
            retVal = EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, &regVal);
            if (((Std_ReturnType)E_OK) != retVal)
            {
                /* MDIO read failed*/
                retVal = (Std_ReturnType)E_NOT_OK;
                break;
            }
            count--;
        }
    }
    if (0U == count)
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

Std_ReturnType EthTrcv_SetTransceiverCtrlMode(uint8 TrcvIdx, EthTrcv_ModeType CtrlMode)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    /*
     * SWS_EthTrcv_00094: If the transceiver is already in the requested mode
     * E_OK shall be returned and no development error shall be raised.
     */

    /* Check if Ethernet Transceiver is present or not */
    if ((uint32)FALSE == EthTrcv_getLinkStatus(EthTrcv_DrvObj.ctrlIdx, TrcvIdx))
    {
        /*
         * check access to controller access and report
         * production error ETHTRCV_E_ACCESS.
         */
#ifdef ETHTRCV_E_ACCESS
        Dem_SetEventStatus(ETHTRCV_E_ACCESS, DEM_EVENT_STATUS_PREFAILED);
#endif /* #ifdef ETHTRCV_E_ACCESS */
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        /*
         * Disable the Ethernet transceiver controller
         */
        if (ETHTRCV_MODE_DOWN == CtrlMode)
        {
            retVal = EthTrcv_resetController(EthTrcv_DrvObj.ctrlIdx, TrcvIdx);
            if (((Std_ReturnType)E_OK) == retVal)
            {
                EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx].ctrlMode = ETHTRCV_MODE_DOWN;
            }
        }
        /*
         * Enable the Ethernet transceiver controller i.e. set to
         * ETHTRCV_MODE_ACTIVE
         */
        else
        {
            EthTrcv_DrvObj.ethTrcvCtrlObj[TrcvIdx].ctrlMode = ETHTRCV_MODE_ACTIVE;
        }
        EthTrcv_ControllerModeChangeFlag[TrcvIdx] = (uint32)TRUE;
    }

    return retVal;
}

uint32 EthTrcv_getLinkStatus(uint8 CtrlIdx, uint8 trcvIdx)
{
    uint16   regVal     = 0U;
    uint32   cnt        = ETHTRCV_LINKSTATUS_RETRIES;
    uint32   retVal     = (uint32)FALSE;
    TickType delayCount = (TickType)ETHTRCV_LINKSTATUS_WAITCOUNT_TICKS;

    while (0U != cnt)
    {
        /* First read the BSR of the PHY */
        if ((Std_ReturnType)E_OK == EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMS, &regVal))
        {
            if (ETHTRCV_BMS_LINKS_STS_UP == (uint32)HW_GET_FIELD(regVal, ETHTRCV_BMS_LINKS_STS))
            {
                retVal = (uint32)TRUE;
                break;
            }
        }
        EthTrcv_delayExecution(delayCount);

        cnt--;
    }

    return retVal;
}

void EthTrcv_regRead_Status(void)
{
    volatile uint32 tempCount = ETHTRCV_TIMEOUT_DURATION;
    if (ETHTRCV_TIMEOUT_DURATION > 8U)
    {
        tempCount = ETHTRCV_TIMEOUT_DURATION / 8U;
    }
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    while (((uint32)TRUE) != EthTrcv_MdioRdCmdComplete)
    {
        if (tempCount <= 0U)
        {
#ifdef ETHTRCV_E_HARDWARE_ERROR
            Dem_SetEventStatus(ETHTRCV_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif /* #ifdef ETHTRCV_E_HARDWARE_ERROR */
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
}
/**
 * \brief   Reads a register from the the EthTrcv
 *
 * \param   CtrlIdx  Base Address of the MDIO Module Registers.
 * \param   trcvIdx       EthTrcv Adress.
 * \param   regIdx        Index of the register to be read
 * \param   regValAdr     address where value of the register will be written
 *
 * \return  status of the read
 *
 **/
Std_ReturnType EthTrcv_regRead(uint8 CtrlIdx, uint8 trcvIdx, uint8 regIdx, uint16 *RegValPtr)
{
    Std_ReturnType fnRetVal = E_NOT_OK;
    Std_ReturnType retVal   = E_NOT_OK;
#if (STD_ON == ETH_ENABLE_MII_API)
    EthTrcv_ConfigType *pTrcvCfg = (EthTrcv_ConfigType *)NULL_PTR;
    pTrcvCfg                     = &(EthTrcv_DrvObj.ethTrcvCtrlObj[trcvIdx].ethTrcvCfg);
#endif
    SchM_Enter_EthTrcv_ETHTRCV_EXCLUSIVE_AREA_0();
    EthTrcv_MdioRdCmdComplete = (uint32)FALSE;
    SchM_Exit_EthTrcv_ETHTRCV_EXCLUSIVE_AREA_0();

    /* Pass phyaddress as transeiver index */
#if (STD_ON == ETH_ENABLE_MII_API)
    fnRetVal = Eth_ReadMii(CtrlIdx, pTrcvCfg->phyAddr, regIdx, RegValPtr);
#endif
    if (((Std_ReturnType)E_OK) == fnRetVal)
    {
        EthTrcv_regRead_Status();
        /* Wait till MDIO command completed interrupt  */
        /* Below API can change start time, so use temp variable */
        /* timeout */
        *RegValPtr = EthTrcv_MdioRdVal;
        retVal     = (Std_ReturnType)E_OK;
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

void EthTrcv_regWrite_Status(void)
{
    volatile uint32 tempCount = ETHTRCV_TIMEOUT_DURATION;
    if (ETHTRCV_TIMEOUT_DURATION > 9U)
    {
        tempCount = ETHTRCV_TIMEOUT_DURATION / 9U;
    }
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    while (((uint32)TRUE) != EthTrcv_MdioWrCmdComplete)
    {
        /* Wait till MDIO command completed interrupt */
        /* Below API can change start time, so use temp variable */
        if (tempCount <= 0U)
        {
            /* timeout */
#ifdef ETHTRCV_E_HARDWARE_ERROR
            Dem_SetEventStatus(ETHTRCV_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif /* #ifdef ETHTRCV_E_HARDWARE_ERROR  */
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
}

/**
 * \brief   Writes a register with the input
 *
 * \param   CtrlIdx       Base Address of the MDIO Module Registers.
 * \param   trcvIdx       EthTrcv Address.
 * \param   regIdx        Index of the register to be read
 * \param   regValAdr     value to be written
 *
 * \return  None
 *
 **/
Std_ReturnType EthTrcv_regWrite(uint8 CtrlIdx, uint8 trcvIdx, uint8 regIdx, uint16 regVal)
{
    Std_ReturnType fnRetVal = E_NOT_OK;
    Std_ReturnType retVal   = E_NOT_OK;
#if (STD_ON == ETH_ENABLE_MII_API)
    EthTrcv_ConfigType *pTrcvCfg;
    pTrcvCfg = &(EthTrcv_DrvObj.ethTrcvCtrlObj[trcvIdx].ethTrcvCfg);
#endif
    SchM_Enter_EthTrcv_ETHTRCV_EXCLUSIVE_AREA_0();
    EthTrcv_MdioWrCmdComplete = (uint32)FALSE;
    SchM_Exit_EthTrcv_ETHTRCV_EXCLUSIVE_AREA_0();
    /* Pass PHY addresses as transceiver index */
#if (STD_ON == ETH_ENABLE_MII_API)
    fnRetVal = Eth_WriteMii(CtrlIdx, pTrcvCfg->phyAddr, regIdx, regVal);
#endif
    if (((Std_ReturnType)E_OK) == fnRetVal)
    {
        EthTrcv_regWrite_Status();
        retVal = (Std_ReturnType)E_OK;
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

/* ========================================================================== */
/*                        Internal Function Definitions                       */
/* ========================================================================== */

static uint32 EthTrcv_getAutoNegStatus(uint8 CtrlIdx, uint8 trcvIdx)
{
    uint16 regVal = 0U;
    uint32 retVal = (uint32)FALSE;

    if ((Std_ReturnType)E_OK == EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_BMS, (uint16 *)&regVal))
    {
        /* Auto negotiation completion status */
        if (ETHTRCV_BMS_AUTONEG_PROCESS_COMPLETE == (uint32)HW_GET_FIELD(regVal, ETHTRCV_BMS_AUTONEG_PROCESS))
        {
            retVal = (uint32)TRUE;
        }
    }

    return retVal;
}
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
static void EthTrcv_updatePartnerAbility(uint32 *pPartnerAblty, uint16 regVal)
{
    if (ETHTRCV_STS1_LINK_1000_HALF_CAPABLE == (uint32)HW_GET_FIELD(regVal, ETHTRCV_STS1_LINK_1000_HALF))
    {
        *pPartnerAblty |= ETHERNET_ADV_CAPAB_1000_HALF;
    }

    if (ETHTRCV_STS1_LINK_1000_FULL_CAPABLE == (uint32)HW_GET_FIELD(regVal, ETHTRCV_STS1_LINK_1000_FULL))
    {
        *pPartnerAblty |= ETHERNET_ADV_CAPAB_1000_FULL;
    }
    return;
}
#endif /* #if (STD_ON == ETHTRCV_1000MBPS_MACRO) */
static Std_ReturnType EthTrcv_getPartnerAbility(uint8 CtrlIdx, uint8 trcvIdx, uint32 *pPartnerAblty, uint32 isGigCapab)
{
    uint16         regVal = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

    *pPartnerAblty = 0U;

    if ((Std_ReturnType)E_OK ==
        EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY, &regVal))
    {
        retVal = (Std_ReturnType)E_OK;

        if (ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_HALF_CAPABLE ==
            (uint32)HW_GET_FIELD(regVal, ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_HALF))
        {
            *pPartnerAblty |= ETHERNET_ADV_CAPAB_10_HALF;
        }

        if (ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_FULL_CAPABLE ==
            (uint32)HW_GET_FIELD(regVal, ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_10_T_FULL))
        {
            *pPartnerAblty |= ETHERNET_ADV_CAPAB_10_FULL;
        }

        if (ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_HALF_CAPABLE ==
            (uint32)HW_GET_FIELD(regVal, ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_HALF))
        {
            *pPartnerAblty |= ETHERNET_ADV_CAPAB_100_HALF;
        }

        if (ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_FULL_CAPABLE ==
            (uint32)HW_GET_FIELD(regVal, ETHTRCV_AUTO_NEG_LINK_PARTNER_ABILITY_100_TX_FULL))
        {
            *pPartnerAblty |= ETHERNET_ADV_CAPAB_100_FULL;
        }
    }
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
    if ((((Std_ReturnType)E_OK) == retVal) && (((uint32)TRUE) == isGigCapab))
    {
        if ((Std_ReturnType)E_OK == EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_STS1, &regVal))
        {
            retVal = (Std_ReturnType)E_OK;
            EthTrcv_updatePartnerAbility(pPartnerAblty, regVal);
        }
    }
#endif /* #if (STD_ON == ETHTRCV_1000MBPS_MACRO) */
    return retVal;
}

static void EthTrcv_delayExecution(TickType count)
{
    volatile uint32 tempCount = count;
    if (count > 9U)
    {
        tempCount = count / 9U;
    }
    /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
    do
    {
        /* Below API can change start time, so use temp variable */
        MCAL_SW_DELAY(tempCount);
    } while (tempCount <= 0U);
}

static void EthTrcv_setDuplexMode(const EthTrcv_ConfigType *pEthTrcvCfg, uint16 *regVal)
{
    if (ETHTRCV_DUPLEX_MODE_FULL == pEthTrcvCfg->duplexMode)
    {
        HW_SET_FIELD16(*regVal, ETHTRCV_BMC_DUPLEX_MODE, ETHTRCV_BMC_DUPLEX_MODE_FULL);
    }
    else
    {
        /* Half Duplex */
        HW_SET_FIELD16(*regVal, ETHTRCV_BMC_DUPLEX_MODE, ETHTRCV_BMC_DUPLEX_MODE_HALF);
    }

    if (ETHTRCV_BAUD_RATE_10MBIT == pEthTrcvCfg->baudRate)
    {
        HW_SET_FIELD16(*regVal, ETHTRCV_BMC_SPEED, ETHTRCV_BMC_SPEED_10);
    }
    else if (ETHTRCV_BAUD_RATE_100MBIT == pEthTrcvCfg->baudRate)
    {
        HW_SET_FIELD16(*regVal, ETHTRCV_BMC_SPEED, ETHTRCV_BMC_SPEED_100);
    }
    else
    {
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
        HW_SET_FIELD16(*regVal, ETHTRCV_BMC_SPEED, ETHTRCV_BMC_SPEED_1000);
#endif /* #if (STD_ON == ETHTRCV_1000MBPS_MACRO) */
    }
}

static Std_ReturnType EthTrcv_checkPhyConfig(const EthTrcv_ConfigType *pEthTrcvCfg, uint32 forceRetries)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    if (0U != forceRetries)
    {
        retVal = (Std_ReturnType)E_OK;
        /* Phy Configuration Successful. */
        /* PHY link verified for phyAddr */
    }
    else
    {
        /*Phy Configuration not Successful. */
        /*PHY link connectivity failed for phyAddr */
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    return retVal;
}

static void EthTrcv_setAutomaticNegotiationSpeedCapability(const EthTrcv_ConfigType *pEthTrcvCfg, uint16 *ptrData)
{
    if (0U != (pEthTrcvCfg->advertiseCapab & ETHERNET_ADV_CAPAB_10_HALF))
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_10_T_HALF, ETHTRCV_AUTO_NEG_ADV_10_T_HALF_CAPABLE);
    }
    else
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_10_T_HALF, ETHTRCV_AUTO_NEG_ADV_10_T_HALF_NOT_CAPABLE);
    }

    if (0U != (pEthTrcvCfg->advertiseCapab & ETHERNET_ADV_CAPAB_10_FULL))
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_10_T_FULL, ETHTRCV_AUTO_NEG_ADV_10_T_FULL_CAPABLE);
    }
    else
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_10_T_FULL, ETHTRCV_AUTO_NEG_ADV_10_T_FULL_NOT_CAPABLE);
    }

    if (0U != (pEthTrcvCfg->advertiseCapab & ETHERNET_ADV_CAPAB_100_HALF))
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_100_TX_HALF, ETHTRCV_AUTO_NEG_ADV_100_TX_HALF_CAPABLE);
    }
    else
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_100_TX_HALF, ETHTRCV_AUTO_NEG_ADV_100_TX_HALF_NOT_CAPABLE);
    }

    if (0U != (pEthTrcvCfg->advertiseCapab & ETHERNET_ADV_CAPAB_100_FULL))
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_100_TX_FULL, ETHTRCV_AUTO_NEG_ADV_100_TX_FULL_CAPABLE);
    }
    else
    {
        HW_SET_FIELD16(*ptrData, ETHTRCV_AUTO_NEG_ADV_100_TX_FULL, ETHTRCV_AUTO_NEG_ADV_100_TX_FULL_NOT_CAPABLE);
    }
    return;
}

static Std_ReturnType EthTrcv_setAutoNeg(const EthTrcv_CtrlObjType *pEthTrcvObj, const EthTrcv_ConfigType *pEthTrcvCfg,
                                         uint16 *ptrData)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    if (((uint32)TRUE) == pEthTrcvCfg->isGigCapab)
    {
        if ((Std_ReturnType)E_OK ==
            EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_GENCFG1, ptrData))
        {
            if (0U != (pEthTrcvCfg->advertiseCapab & ETHERNET_ADV_CAPAB_1000_HALF))
            {
                HW_SET_FIELD16(*ptrData, ETHTRCV_GENCFG1_ADV_1000_HALF, ETHTRCV_GENCFG1_ADV_1000_HALF_CAPABLE);
            }
            else
            {
                HW_SET_FIELD16(*ptrData, ETHTRCV_GENCFG1_ADV_1000_HALF, ETHTRCV_GENCFG1_ADV_1000_HALF_NOT_CAPABLE);
            }
            if (0U != (pEthTrcvCfg->advertiseCapab & ETHERNET_ADV_CAPAB_1000_FULL))
            {
                HW_SET_FIELD16(*ptrData, ETHTRCV_GENCFG1_ADV_1000_FULL, ETHTRCV_GENCFG1_ADV_1000_FULL_CAPABLE);
            }
            else
            {
                HW_SET_FIELD16(*ptrData, ETHTRCV_GENCFG1_ADV_1000_FULL, ETHTRCV_GENCFG1_ADV_1000_FULL_NOT_CAPABLE);
            }
            retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, (uint8)ETHTRCV_GENCFG1, *ptrData);
        }
    }
    return retVal;
}

static uint32 EthTrcv_countautoNegRetries(const EthTrcv_CtrlObjType *pEthTrcvObj, uint32 autoNegRetries)
{
    uint32 tmpAutoNegRetries = autoNegRetries;
    while (0U != tmpAutoNegRetries)
    {
        /* Wait for configured amount of time */
        EthTrcv_delayExecution((TickType)ETHTRCV_AUTONEG_STATUS_WAITCOUNT_TICKS);

        if ((uint32)TRUE == EthTrcv_getAutoNegStatus(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx))
        {
            break;
        }
        tmpAutoNegRetries--;
    }

    return tmpAutoNegRetries;
}

static Std_ReturnType EthTrcv_configsetBaudRateAndDuplexMode(EthTrcv_ConfigType *pEthTrcvCfg)
{
    Std_ReturnType retVal = (Std_ReturnType)E_OK;
    if (0U !=
#if (STD_ON == ETHTRCV_1000MBPS_MACRO)
        ((pEthTrcvCfg->advertiseCapab & pEthTrcvCfg->linkPartCapab) & ETHERNET_ADV_CAPAB_1000_FULL))
    {
        pEthTrcvCfg->baudRate   = ETHTRCV_BAUD_RATE_1000MBIT;
        pEthTrcvCfg->duplexMode = ETHTRCV_DUPLEX_MODE_FULL;
    }
    else if (0U != ((pEthTrcvCfg->advertiseCapab & pEthTrcvCfg->linkPartCapab) & ETHERNET_ADV_CAPAB_1000_HALF))
    {
        pEthTrcvCfg->baudRate   = ETHTRCV_BAUD_RATE_1000MBIT;
        pEthTrcvCfg->duplexMode = ETHTRCV_DUPLEX_MODE_HALF;
    }
    else if (0U !=
#endif /* #if (STD_ON == ETHTRCV_1000MBPS_MACRO) */
             ((pEthTrcvCfg->advertiseCapab & pEthTrcvCfg->linkPartCapab) & ETHERNET_ADV_CAPAB_100_FULL))
    {
        pEthTrcvCfg->baudRate   = ETHTRCV_BAUD_RATE_100MBIT;
        pEthTrcvCfg->duplexMode = ETHTRCV_DUPLEX_MODE_FULL;
    }
    else if (0U != (pEthTrcvCfg->advertiseCapab & pEthTrcvCfg->linkPartCapab & ETHERNET_ADV_CAPAB_100_HALF))
    {
        pEthTrcvCfg->baudRate   = ETHTRCV_BAUD_RATE_100MBIT;
        pEthTrcvCfg->duplexMode = ETHTRCV_DUPLEX_MODE_HALF;
    }
    else if (0U != (pEthTrcvCfg->advertiseCapab & pEthTrcvCfg->linkPartCapab & ETHERNET_ADV_CAPAB_10_FULL))
    {
        pEthTrcvCfg->baudRate   = ETHTRCV_BAUD_RATE_10MBIT;
        pEthTrcvCfg->duplexMode = ETHTRCV_DUPLEX_MODE_FULL;
    }
    else if (0U != (pEthTrcvCfg->advertiseCapab & pEthTrcvCfg->linkPartCapab & ETHERNET_ADV_CAPAB_10_HALF))
    {
        pEthTrcvCfg->baudRate   = ETHTRCV_BAUD_RATE_10MBIT;
        pEthTrcvCfg->duplexMode = ETHTRCV_DUPLEX_MODE_HALF;
    }
    else
    {
        retVal = (Std_ReturnType)E_NOT_OK;
    }
    return retVal;
}

static Std_ReturnType EthTrcv_setBaudRateAndDuplexMode(const EthTrcv_CtrlObjType *pEthTrcvObj,
                                                       EthTrcv_ConfigType *pEthTrcvCfg, uint32 *ptrAutoNegRetries)
{
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;
    *ptrAutoNegRetries    = EthTrcv_countautoNegRetries(pEthTrcvObj, *ptrAutoNegRetries);
    if (0U != (*ptrAutoNegRetries))
    {
        /* Auto-Negotiation Successful. */

        retVal = EthTrcv_getPartnerAbility(EthTrcv_DrvObj.ctrlIdx, pEthTrcvObj->trcvIdx, &(pEthTrcvCfg->linkPartCapab),
                                           pEthTrcvCfg->isGigCapab);

        if (((Std_ReturnType)E_OK) == retVal)
        {
            retVal = EthTrcv_configsetBaudRateAndDuplexMode(pEthTrcvCfg);

            /* Transfer Mode : 1000 Mbps Full Duplex. */
            /* Transfer Mode : 1000 Mbps Half Duplex. */
            /* Transfer Mode : 100 Mbps Full Duplex. */
            /* Transfer Mode : 100 Mbps Half Duplex. */
            /* Transfer Mode : 10 Mbps Full Duplex. */
            /* Transfer Mode : 10 Mbps Half Duplex. */
        }
    }
    else
    {
        /* Auto-Negotiation Not Successful. */
        retVal = (Std_ReturnType)E_NOT_OK;
    }

    return retVal;
}

#if (STD_ON == ETHTRCV_SETPHYTXMODE_API)
Std_ReturnType EthTrcvSettingStatusPhyTxMode(uint8 trcvIdx, EthTrcv_PhyTxModeType ModeVal)
{
    uint16         regVal = 0U;
    Std_ReturnType retVal = E_NOT_OK;

    if (ModeVal == ETHTRCV_PHYTXMODE_NORMAL)
    {
        HW_SET_FIELD16(regVal, ETHTRCV_TX_CONFIG_SCR_DIS, ETHTRCV_TX_CONFIG_SCR_NORMAL);
        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_TX_CONFIG, regVal);
    }
    else if (ModeVal == ETHTRCV_PHYTXMODE_SCRAMBLER_OFF)
    {
        HW_SET_FIELD16(regVal, ETHTRCV_TX_CONFIG_SCR_DIS, ETHTRCV_TX_CONFIG_SCR_DISABLE);
        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_TX_CONFIG, regVal);
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_SETPHYTXMODE_API) */

#if (STD_ON == ETHTRCV_GETCABLEDIAGNOSTICSRESULT_API)
Std_ReturnType EthTrcv_ReadCableDiagResult(uint8 TrcvIdx, EthTrcv_CableDiagResultType *ResultVal)
{
    uint16         regVal = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

    /*TDR Start*/
    HW_SET_FIELD16(regVal, ETHTRCV_CAB_DIAG_CTRL_TDR_START, ETHTRCV_CAB_DIAG_CTRL_TDR_START_ENABLE);

    retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, TrcvIdx, (uint8)ETHTRCV_DIAGNOSTICS_CTRL, regVal);

    if (retVal == E_OK)
    {
        /*TDR Done*/
        retVal = EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, TrcvIdx, (uint8)ETHTRCV_DIAGNOSTICS_CTRL, &regVal);
    }

    if (retVal == E_OK)
    {
        if ((regVal & ETHTRCV_TDR_FAIL) == ETHTRCV_TDR_FAIL)
        {
            *ResultVal = ETHTRCV_CABLEDIAG_ERROR;
        }
        else if ((regVal & ETHTRCV_TDR_DONE) == ETHTRCV_TDR_DONE)
        {
            *ResultVal = ETHTRCV_CABLEDIAG_OK;
        }
        else
        {
            retVal = E_NOT_OK;
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETCABLEDIAGNOSTICSRESULT_API) */

Std_ReturnType EthTrcv_ConfigSetPhyLoopbackMode(uint8 trcvIdx, EthTrcv_PhyLoopbackModeType ModeType)
{
    uint16         regVal = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

    if (ModeType == ETHTRCV_PHYLOOPBACK_NONE)
    {
        if ((Std_ReturnType)E_OK == EthTrcv_regRead(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, &regVal))
        {
            HW_SET_FIELD16(regVal, ETHTRCV_CFG_NORMAL_MODE, ETHTRCV_CFG_NORMAL_MODE_OPERATION);
            retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_BMC, regVal);
        }
    }
    else if (ModeType == ETHTRCV_PHYLOOPBACK_EXTERNAL)
    {
        HW_SET_FIELD16(regVal, ETHTRCV_CFG_LOOPBACK_MODE, ETHTRCV_CFG_LOOPBACK_MODE_EXTERNAL);

        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_CFG, regVal);
    }
    else if (ModeType == ETHTRCV_PHYLOOPBACK_INTERNAL)
    {
#if (ETHTRCV_PHYLOOPBACK_INTERNAL_TYPE == ETHTRCV_PHYLOOPBACK_INTERNAL_ANALOG)

        HW_SET_FIELD16(regVal, ETHTRCV_CFG_LOOPBACK_MODE, ETHTRCV_CFG_LOOPBACK_MODE_INTERNAL_ANALOG);

        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_CFG, regVal);

#elif (ETHTRCV_PHYLOOPBACK_INTERNAL_TYPE == ETHTRCV_PHYLOOPBACK_INTERNAL_DIGITAL)

        HW_SET_FIELD16(regVal, ETHTRCV_CFG_LOOPBACK_MODE, ETHTRCV_CFG_LOOPBACK_MODE_INTERNAL_DIGITAL);

        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_CFG, regVal);

#else
        retVal = E_NOT_OK;
#endif /* #if (ETHTRCV_PHYLOOPBACK_INTERNAL_TYPE == ETHTRCV_PHYLOOPBACK_INTERNAL_ANALOG) */
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

#if (STD_ON == ETHTRCV_GETPHYIDENTIFIER_API)
Std_ReturnType EthTrcv_GetPhyIdentifierRead(uint8 trcvIdx, uint32 *OrgUniqId, uint8 *MdlNmbr, uint8 *RevNmbr)
{
    Std_ReturnType retVal  = (Std_ReturnType)E_NOT_OK;
    Std_ReturnType retVal1 = (Std_ReturnType)E_NOT_OK;
    Std_ReturnType retVal2 = (Std_ReturnType)E_NOT_OK;

    uint16 PhyIdr1 = 0U;
    uint16 PhyIdr2 = 0U;
    uint8  CtrlIdx = 0U;

    CtrlIdx = EthTrcv_DrvObj.ethTrcvCtrlObj[0].ethTrcvCfg.ctrlIdx;

    retVal1 = EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_ID1, &PhyIdr1);
    retVal2 = EthTrcv_regRead(CtrlIdx, trcvIdx, (uint8)ETHTRCV_ID2, &PhyIdr2);

    if ((retVal1 == E_OK) && (retVal2 == E_OK))
    {
        *OrgUniqId = (((uint32)HW_GET_FIELD(PhyIdr1, ETHTRCV_ID1_OUI_MSB)) << 6) |
                     ((uint32)HW_GET_FIELD(PhyIdr2, ETHTRCV_ID2_OUI_LSB));

        *MdlNmbr = (uint8)HW_GET_FIELD(PhyIdr2, ETHTRCV_ID2_MDL);
        *RevNmbr = (uint8)HW_GET_FIELD(PhyIdr2, ETHTRCV_ID2_MDL_REV);
        retVal   = E_OK;
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_GETPHYIDENTIFIER_API) */

#if (STD_ON == ETHTRCV_SETPHYTESTMODE_API)
Std_ReturnType EthTrcv_HwSetPhyTestMode(uint8 trcvIdx, EthTrcv_PhyTestModeType Mode)
{
    uint16         regVal = 0U;
    Std_ReturnType retVal = (Std_ReturnType)E_NOT_OK;

    if (Mode == ETHTRCV_PHYTESTMODE_NONE)
    {
        HW_SET_FIELD16(regVal, ETHTRCV_TEST_MODE, ETHTRCV_TEST_MODE_NORMAL);
        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_GENCFG1, regVal);
    }
    else if (Mode == ETHTRCV_PHYTESTMODE_2)
    {
        HW_SET_FIELD16(regVal, ETHTRCV_TEST_MODE, ETHTRCV_TEST_MODE_JITTER_MASTER);

        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_GENCFG1, regVal);
    }
    else if (Mode == ETHTRCV_PHYTESTMODE_3)
    {
        HW_SET_FIELD16(regVal, ETHTRCV_TEST_MODE, ETHTRCV_TEST_MODE_JITTER_SLAVE);
        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_GENCFG1, regVal);
    }
    else
    {
        HW_SET_FIELD16(regVal, ETHTRCV_TEST_MODE, ETHTRCV_TEST_MODE_TRANSMIT_DISTORTION);
        retVal = EthTrcv_regWrite(EthTrcv_DrvObj.ctrlIdx, trcvIdx, (uint8)ETHTRCV_GENCFG1, regVal);
    }

    return retVal;
}
#endif /* #if (STD_ON == ETHTRCV_SETPHYTESTMODE_API) */

#define ETHTRCV_STOP_SEC_CODE
#include "EthTrcv_MemMap.h"
