/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     EthApp_utils.c
 *
 *  \brief    This file contains common utility functions used by the MCAL Eth
 *            apps
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"
#include "Std_Types.h"
#include "hw_types.h"
#include "app_utils.h"
#include "Eth.h"
#include "Eth_Irq.h"
#include "Eth_GeneralTypes.h"
#include "EthTrcv.h"
#include "app_utilsEth.h"
#include "hw_ctrl_core.h"
#include "EcuM_Cbk.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "trace.h"
#include "CacheP.h"
#include "sys_common.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                         Internal Function Declarations                     */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void AppUtils_ethPrintVersionInfo()
{
#if (ETH_VERSION_INFO_API == STD_ON) || (ETHTRCV_VERSION_INFO_API == STD_ON)
    Std_VersionInfoType versioninfo;
#endif /* #if (ETH_VERSION_INFO_API == STD_ON) */
#if (ETH_VERSION_INFO_API == STD_ON)
    /* Get and print version */
    Eth_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n");
    AppUtils_printf("\rETH MCAL Version Info\n");
    AppUtils_printf("\r---------------------\n");
    AppUtils_printf("\rVendor ID           : %d\n", versioninfo.vendorID);
    AppUtils_printf("\rModule ID           : %d\n", versioninfo.moduleID);
    AppUtils_printf("\rSW Major Version    : %d\n", versioninfo.sw_major_version);
    AppUtils_printf("\rSW Minor Version    : %d\n", versioninfo.sw_minor_version);
    AppUtils_printf("\rSW Patch Version    : %d\n", versioninfo.sw_patch_version);
    AppUtils_printf(" \n");
#endif /* #if (ETH_VERSION_INFO_API == STD_ON) */

#if (ETHTRCV_VERSION_INFO_API == STD_ON)
    /* Get and print version */
    EthTrcv_GetVersionInfo(&versioninfo);
    AppUtils_printf(" \n");
    AppUtils_printf("\rETH TRCV MCAL Version Info\n");
    AppUtils_printf("\r---------------------\n");
    AppUtils_printf("\rVendor ID           : %d\n", versioninfo.vendorID);
    AppUtils_printf("\rModule ID           : %d\n", versioninfo.moduleID);
    AppUtils_printf("\rSW Major Version    : %d\n", versioninfo.sw_major_version);
    AppUtils_printf("\rSW Minor Version    : %d\n", versioninfo.sw_minor_version);
    AppUtils_printf("\rSW Patch Version    : %d\n", versioninfo.sw_patch_version);
    AppUtils_printf(" \n");
#endif /* #if (ETH_VERSION_INFO_API == STD_ON) */
}

Std_ReturnType AppUtils_ethTrcvInit(EthTrcv_ConfigType *ethTrcvConfigPtr, uint8 trcvIdx)
{
    Std_ReturnType retVal = E_NOT_OK;
#if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API)
    EthTrcv_ModeType trcvMode;
#endif

    /* Do EthTrcv driver initialization */
    EthTrcv_Init(ethTrcvConfigPtr);

#if (STD_ON == ETHTRCV_STARTAUTONEGOTIATION_API)
    /* Start AutoNegotiation (Will not be needed in most of cases as
     * EthTrcv_TransceiverInit will also start auto negotiation. Only if config
     * changes (like speed, duplex etc.) then call below function). Adding here
     * for testing purpose.
     */
    if (ethTrcvConfigPtr->pController[trcvIdx]->enableAutoNeg == TRUE)
    {
        retVal = EthTrcv_StartAutoNegotiation(trcvIdx);
        if (E_OK != retVal)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV Initialization failed\n ");
        }
    }
#endif
#if (STD_ON == ETHTRCV_SETTRANSCEIVERMODE_API)
    retVal = EthTrcv_SetTransceiverMode(trcvIdx, ETHTRCV_MODE_ACTIVE);
#endif

#if (STD_ON == ETHTRCV_GETTRANSCEIVERMODE_API)
    retVal = EthTrcv_GetTransceiverMode(trcvIdx, &trcvMode);
    if (E_OK == retVal)
    {
        AppUtils_printf("\rETH_APP: EthTrcv Controller mode change - %s\n",
                        (trcvMode == ETHTRCV_MODE_ACTIVE) ? "ETHTRCV_MODE_ACTIVE" : "ETHTRCV_MODE_DOWN");
    }
#endif

#if (STD_ON == ETHTRCV_GETLINKSTATE_API)
    EthTrcv_LinkStateType linkState;

    retVal = EthTrcv_GetLinkState(trcvIdx, &linkState);
    if (E_OK == retVal)
    {
        if (ETHTRCV_LINK_STATE_ACTIVE == linkState)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV Link up\n");
        }
        else
        {
            AppUtils_printf("\rETH_APP:ETHTRCV link down\n");
        }
    }
#endif

#if (STD_ON == ETHTRCV_GETBAUDRATE_API)
    EthTrcv_BaudRateType baudRate;

    retVal = EthTrcv_GetBaudRate(trcvIdx, &baudRate);
    if (E_OK == retVal)
    {
        if (ETHTRCV_BAUD_RATE_10MBIT == baudRate)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV baud rate = 10Mbps\n");
        }
        else if (ETHTRCV_BAUD_RATE_100MBIT == baudRate)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV baud rate = 100Mbps\n");
        }
        else if (ETHTRCV_BAUD_RATE_1000MBIT == baudRate)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV baud rate = 1000Mbps\n");
        }
        else
        {
            /* not possible as check is done in function */
        }
    }
#endif

#if (STD_ON == ETHTRCV_GETDUPLEXMODE_API)
    EthTrcv_DuplexModeType duplexMode;

    retVal = EthTrcv_GetDuplexMode(trcvIdx, &duplexMode);
    if (E_OK == retVal)
    {
        if (ETHTRCV_DUPLEX_MODE_FULL == duplexMode)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV in full duplex mode\n");
        }
        else if (ETHTRCV_DUPLEX_MODE_HALF == duplexMode)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV in half duplex mode\n");
        }
        else
        {
            /* not possible as check is done in function */
        }
    }
#endif

    if (FALSE == ethTrcvConfigPtr->pController[trcvIdx]->loopbackEnable)
    {
        retVal = EthTrcv_SetPhyLoopbackMode(trcvIdx, ETHTRCV_PHYLOOPBACK_NONE);
    }

    if (E_OK == retVal)
    {
        AppUtils_printf("\rETH_APP:ETHTRCV Normal Operation\n");
    }
    else
    {
        AppUtils_printf("\rETH_APP:ETHTRCV Set to Normal operation failed\n");
    }

#if (STD_ON == ETHTRCV_SETPHYTXMODE_API)

    retVal = EthTrcv_SetPhyTxMode(ethTrcvConfigPtr->pController[trcvIdx]->trcvIdx, ETHTRCV_PHYTXMODE_NORMAL);

    if (E_OK == retVal)
    {
        AppUtils_printf("\rETH_APP:ETHTRCV Tx mode Normal\n");
    }
    else
    {
        AppUtils_printf("\rETH_APP:ETHTRCV Set to Tx mode Normal operation failed\n");
    }
#endif

#if (STD_ON == ETHTRCV_GETPHYIDENTIFIER_API)
    uint32 OrgUniqueIdPtr;
    uint8  ModelNrPtr;
    uint8  RevisionNrPtr;

    retVal = EthTrcv_GetPhyIdentifier(trcvIdx, &OrgUniqueIdPtr, &ModelNrPtr, &RevisionNrPtr);

    if (E_OK == retVal)
    {
        if ((OrgUniqueIdPtr == 0x080028) && (ModelNrPtr == 0x23) && (RevisionNrPtr == 0x01))
        {
            AppUtils_printf(
                "\rETH_APP:ETHTRCV PHY(DP83867E) ID is proper. OUI: 0x%x, Model No: 0x%x, Revision "
                "No: 0x%x\n",
                OrgUniqueIdPtr, ModelNrPtr, RevisionNrPtr);
        }
        else if ((OrgUniqueIdPtr == 0x080028) && (ModelNrPtr == 0xF) &&
                 ((RevisionNrPtr == 0x01) || (RevisionNrPtr == 0x03)))
        {
            AppUtils_printf(
                "\rETH_APP:ETHTRCV PHY(DP83869HM) ID is proper. OUI: 0x%x, Model No: 0x%x, "
                "Revision No: 0x%x\n",
                OrgUniqueIdPtr, ModelNrPtr, RevisionNrPtr);
        }
        else
        {
            AppUtils_printf(
                "\rETH_APP:ETHTRCV PHY ID is different. OUI: 0x%x, Model No: 0x%x, Revision No: "
                "0x%x\n",
                OrgUniqueIdPtr, ModelNrPtr, RevisionNrPtr);
        }
    }
#endif

#if (STD_ON == ETHTRCV_GETCABLEDIAGNOSTICSRESULT_API)
    EthTrcv_CableDiagResultType ResultPtr;

    retVal = EthTrcv_GetCableDiagnosticsResult(trcvIdx, &ResultPtr);

    if (E_OK == retVal)
    {
        if (ResultPtr == ETHTRCV_CABLEDIAG_OK)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV Cable Diagnostics Ok\n");
        }
        else if (ResultPtr == ETHTRCV_CABLEDIAG_ERROR)
        {
            AppUtils_printf("\rETH_APP:ETHTRCV Cable Diagnostics Error\n");
        }
        else
        {
            /*Do nothing*/
        }
    }
#endif

#if (STD_ON == ETHTRCV_SETPHYTESTMODE_API)

    retVal = EthTrcv_SetPhyTestMode(trcvIdx, ETHTRCV_PHYTESTMODE_NONE);

    if (E_OK == retVal)
    {
        AppUtils_printf("\rETH_APP:ETHTRCV Phy test mode Normal\n");
    }
    else
    {
        AppUtils_printf("\rETH_APP:ETHTRCV Set to Phy test mode Normal operation failed\n");
    }
#endif

    EthTrcv_MainFunction();

    return retVal;
}

/* Function to access Ethernet PHY MMD indirect registers. These registers
 * are access through sequence of writes through MII registers */
Std_ReturnType AppUtils_ethTrcvWriteMMDIndirect(uint8 ctrlIdx, uint8 trcvIdx, uint32 regIdx, uint16 regVal)
{
    Std_ReturnType retVal = E_OK;
#if (STD_ON == ETH_ENABLE_MII_API)
    retVal = Eth_WriteMii(ctrlIdx, trcvIdx, 0x0D, 0x001F);

    retVal += Eth_WriteMii(ctrlIdx, trcvIdx, 0x0E, regIdx);

    retVal += Eth_WriteMii(ctrlIdx, trcvIdx, 0x0D, 0x401F);

    retVal += Eth_WriteMii(ctrlIdx, trcvIdx, 0x0E, regVal);
#endif
    if (((Std_ReturnType)E_OK) != retVal)
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

/*******************************************************************************
 *
 * \brief PHY DP83869HM delay config function
 *
 *        This function is used for configuring the receive and transmit delays
 *        for DP83869HM PHY on Am263x.
 *        For PHY configuration, need to configure DP83869HM�s RGMII Control
 *        Register (RGMIICTL) for RGMII mode and RGMII Delay Control Register
 *        (RGMIIDCTL).
 *
 *******************************************************************************
 */
void AppUtils_ethAm263xPHYDelayConfig(Eth_ConfigType *pEthConfigPtr, uint32 phyAddr)
{
    uint32 regIdx;
    uint16 regVal;

    regVal = 0x8000;
    regIdx = 0x1F;
    AppUtils_ethTrcvWriteMMDIndirect(pEthConfigPtr->ctrlIdx, phyAddr, regIdx, regVal);
    AppUtils_delay(1000U);
    regVal = 0x11;
    regIdx = 0x86;
    AppUtils_ethTrcvWriteMMDIndirect(pEthConfigPtr->ctrlIdx, phyAddr, regIdx, regVal);
    AppUtils_delay(1000U);
    regVal = 0x0D0;
    regIdx = 0x32;
    AppUtils_ethTrcvWriteMMDIndirect(pEthConfigPtr->ctrlIdx, phyAddr, regIdx, regVal);
    AppUtils_delay(1000U);
    regVal = 0x61F;
    regIdx = 0x170;
    AppUtils_ethTrcvWriteMMDIndirect(pEthConfigPtr->ctrlIdx, phyAddr, regIdx, regVal);
    AppUtils_delay(1000U);
    regVal = 0x4000;
    regIdx = 0x1F;
    AppUtils_ethTrcvWriteMMDIndirect(pEthConfigPtr->ctrlIdx, phyAddr, regIdx, regVal);
    AppUtils_delay(1000U);
}

void EcuM_cacheInvalidate(uint8 *startAddress, uint32 byteCount)
{
    Mcal_CacheP_invL1d((uint32)startAddress, byteCount);
}

/* =========================Function separator========================= */

void EcuM_cacheWbInv(uint8 *startAddress, uint32 byteCount)
{
    Mcal_CacheP_wbInv((void *)startAddress, byteCount, Mcal_CacheP_TYPE_ALLD);
}

/* =========================Function separator========================= */

void SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */

void SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */

void SchM_Enter_EthTrcv_ETHTRCV_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Enter_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */

void SchM_Exit_EthTrcv_ETHTRCV_EXCLUSIVE_AREA_0(void)
{
    AppUtils_SchM_Exit_EXCLUSIVE_AREA_0();
}

/* =========================Function separator========================= */

void Eth_appPrint(uint32 txHostErrorCh, uint32 txHostErrorCode, uint32 rxHostErrorCh, uint32 rxHostErrorCode)
{
    AppUtils_printf("\r\nHost error..!!!");
    if (rxHostErrorCh)
    {
        AppUtils_printf("\r\n RX channel = %d, Host error Rx code = %d", rxHostErrorCh, rxHostErrorCode);
    }

    if (txHostErrorCh)
    {
        AppUtils_printf("\r\n Error TX channel = %d, error code = %d", txHostErrorCh, txHostErrorCode);
    }
}

/* =========================Function separator========================= */

#ifdef __cplusplus
}
#endif
