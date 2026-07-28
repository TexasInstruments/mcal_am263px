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
 *  \file     Eth.c
 *
 *  \brief    This file contains ETH MCAL driver
 *
 */

/* Common Design ID's */

/*
 * Design:
 * MCAL-26527, MCAL-26596, MCAL-26544, MCAL-26487, MCAL-26490,
 * MCAL-26597, MCAL-26598, MCAL-26519, MCAL-26641, MCAL-26655,
 * MCAL-26553, MCAL-26542, MCAL-26501, MCAL-26573, MCAL-26528,
 * MCAL-26654, MCAL-26476, MCAL-26518, MCAL-26692, MCAL-26564,
 * MCAL-26469, MCAL-26602,
 * MCAL-26446, MCAL-26450, MCAL-26455, MCAL-26462, MCAL-26464,
 * MCAL-26472, MCAL-26478, MCAL-26480, MCAL-26483, MCAL-26488,
 * MCAL-26491, MCAL-26492, MCAL-26499, MCAL-26502, MCAL-26506,
 * MCAL-26509, MCAL-26511, MCAL-26513, MCAL-26521, MCAL-26536,
 * MCAL-26538, MCAL-26545, MCAL-26548, MCAL-26549, MCAL-26550,
 * MCAL-26551, MCAL-26554, MCAL-26556, MCAL-26557, MCAL-26558,
 * MCAL-26566, MCAL-26577, MCAL-26579, MCAL-26580, MCAL-26581,
 * MCAL-26584, MCAL-26592, MCAL-26595, MCAL-26603, MCAL-26607,
 * MCAL-26609, MCAL-26614, MCAL-26615, MCAL-26616, MCAL-26617,
 * MCAL-26619, MCAL-26622, MCAL-26635, MCAL-26639, MCAL-26642,
 * MCAL-26651, MCAL-26657, MCAL-26658, MCAL-26660, MCAL-26661,
 * MCAL-26663, MCAL-26665, MCAL-26670, MCAL-26673, MCAL-26674,
 * MCAL-26684, MCAL-26685, MCAL-26686, MCAL-26688, MCAL-26693,
 * MCAL-26699
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Eth.h"
#include "Eth_Cfg.h"
#include "EthIf_Cbk.h"
#if (STD_ON == ETH_DEV_ERROR_DETECT)
#include "Det.h"
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#include "Dem.h"
#include "Os.h"
#include "SchM_Eth.h"
#include "string.h"
#include "Std_Types.h"
#define ETH_START_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define ETH_STOP_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
#include "Eth_Priv.h"
#include "Cpsw.h"
#include "Cpsw_Mdio.h"
#include "Cpsw_Priv.h"
#include "Cpsw_Ale.h"
#include "Cpsw_Stats.h"
#include "Cpsw_Port.h"
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * Design: MCAL-26454
 */

/* AUTOSAR version information check has to match definition in header file */
#if ((ETH_AR_RELEASE_MAJOR_VERSION != (4U)) || (ETH_AR_RELEASE_MINOR_VERSION != (3U)) || \
     (ETH_AR_RELEASE_REVISION_VERSION != (1U)))
#error "Eth: AUTOSAR Version Numbers of Eth are different!!"
#endif

/* AUTOSAR version information check has to match definition in header file */

/*
 * Design: MCAL-26597
 */
#if ((ETH_SW_MAJOR_VERSION != (10U)) || (ETH_SW_MINOR_VERSION != (3U)) || (ETH_SW_PATCH_VERSION != (1U)))
#error "Eth: Software Version Numbers are inconsistent!!"
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
#if (ETH_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkSetControllerModeErrors(uint8 ctrlIdx);
#endif /*ETH_DEV_ERROR_DETECT == STD_ON*/

#if (ETH_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetControllerModeErrors(uint8 ctrlIdx, const Eth_ModeType *ctrlModePtr);
#endif /*ETH_DEV_ERROR_DETECT == STD_ON*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetPhysAddrErrors(uint8 ctrlIdx, const uint8 *physAddrPtr);
#endif /*ETH_DEV_ERROR_DETECT == STD_ON*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkSetPhysAddrErrors(uint8 ctrlIdx, const uint8 *physAddrPtr);
#endif /*ETH_DEV_ERROR_DETECT == STD_ON*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkUpdatePhysAddrFilterErrors(uint8 ctrlIdx, const uint8 *physAddrPtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(BufReq_ReturnType, ETH_CODE) Eth_checkProvideTxBufferErrors(uint8 ctrlIdx, const Eth_BufIdxType *bufIdxPtr,
                                                                        uint8 **bufPtr, const uint16 *lenBytePtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkTransmitErrors(uint8 ctrlIdx, Eth_BufIdxType bufIdx, const uint8 *physAddrPtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkReceiveErrors(uint8 ctrlIdx, uint8 FifoIdx);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */

#if (STD_ON == ETH_ENABLE_MII_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkWriteMiiErrors(uint8 ctrlIdx);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_ENABLE_MII_API) */

#if (STD_ON == ETH_ENABLE_MII_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkReadMiiErrors(uint8 ctrlIdx, const uint16 *regValPtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_ENABLE_MII_API) */

#if (ETH_GET_DROPCOUNT_API == STD_ON)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetCounterValuesErrors(uint8 ctrlIdx, const Eth_CounterType *CounterPtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* ETH_GET_DROPCOUNT_API==STD_ON */

#if (ETH_GETETHERSTATS_API == STD_ON)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetRxStatsErrors(uint8 ctrlIdx, const Eth_RxStatsType *RxStats);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_GETETHERSTATS_API) */

#if (ETH_GETTX_STATS_API == STD_ON)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetTxStatsErrors(uint8 ctrlIdx, const Eth_TxStatsType *TxStats);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_GETTX_STATS_API) */

#if (STD_ON == ETH_GETTXERROR_COUNTERVALUES_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetTxErrorCounterValueErrors(uint8 ctrlIdx, const Eth_TxErrorCounterValuesType *TxErrorCounterValues);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* STD_ON == ETH_GETTXERROR_COUNTERVALUES_API */

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetCurrentTimeErrors(uint8 ctrlIdx, const Eth_TimeStampQualType *timeQualPtr,
                                  const Eth_TimeStampType *timeStampPtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkEnableEgressTimeStampErrors(uint8 ctrlIdx);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetEgressTimeStampErrors(uint8 ctrlIdx, const Eth_TimeStampQualType *timeQualPtr,
                                      const Eth_TimeStampType *timeStampPtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetIngressTimeStampErrors(uint8 ctrlIdx, const Eth_DataType *dataPtr,
                                       const Eth_TimeStampQualType *timeQualPtr, const Eth_TimeStampType *timeStampPtr);
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkTxConfirmationErrors(uint8 ctrlIdx);
#endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */

#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkSetBandwidthLimitErrors(uint8 ctrlIdx, uint8 queuePrio, uint32 bandwidthLimit);
#endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetBandwidthLimitErrors(uint8 ctrlIdx, uint8 queuePrio, const uint32 *BandwidthLimitPtr);
#endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
/** \brief ETH driver status */
/* Requirements : SWS_Eth_00159 */
volatile VAR(Eth_StateType, ETH_VAR_ZERO_INIT) Eth_DrvStatus = ETH_STATE_UNINIT;
#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

#define ETH_START_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if (ETH_VERSION_INFO_API == STD_ON)

/******************************************************************************
 * Eth_GetVersionInfo
 ******************************************************************************/

/** \brief      This function will return the version for this module.
 *
 *  \param[in]  None
 *
 *  \param[out] Std_VersionInfoType VersionInfo - the structure that will
 *              contain version info after fxn call.
 *
 *  \context    App
 ******************************************************************************/

/*
 * Design: MCAL-26680, MCAL-26597
 */
FUNC(void, ETH_CODE)
Eth_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfo)
{
#if (ETH_DEV_ERROR_DETECT == STD_ON)
    if (NULL_PTR == VersionInfo)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_VERSION_INFO, ETH_E_PARAM_POINTER);
    }
    else
#endif /* ETH_DEV_ERROR_DETECT == STD_ON */
    {
        VersionInfo->vendorID         = ETH_VENDOR_ID;
        VersionInfo->moduleID         = ETH_MODULE_ID;
        VersionInfo->sw_major_version = ETH_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version = ETH_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version = ETH_SW_PATCH_VERSION;
    }
}
#endif /*ETH_VERSION_INFO_API == STD_ON*/

/*******************************************************************************
 * Eth_Init
 ******************************************************************************/

/** \brief Initializes the Ethernet Driver
 *
 * \param[in] CfgPtr
 *
 * \param[out] None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26453, MCAL-26493, MCAL-26508, MCAL-26552, MCAL-26662,
 * MCAL-26454, MCAL-26505, MCAL-26677
 */
FUNC(void, ETH_CODE)
Eth_Init(P2CONST(Eth_ConfigType, AUTOMATIC, ETH_PBCFG) CfgPtr)
{
    const Eth_ConfigType *ConfigPtr       = CfgPtr;
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
#if (STD_ON == ETH_VARIANT_PRE_COMPILE)
        if (NULL_PTR == ConfigPtr)
        {
            ConfigPtr = &ETH_INIT_CONFIG_PC;
        }
#endif /* (STD_ON == ETH_VARIANT_PRE_COMPILE) */

#if (STD_ON == ETH_VARIANT_LINK_TIME)
        if (NULL_PTR == ConfigPtr)
        {
            ConfigPtr = (const Eth_ConfigType *)&Eth_Config;
        }
#endif /* (STD_ON == ETH_VARIANT_LINK_TIME) */

#if (STD_ON == ETH_DEV_ERROR_DETECT)
#if (STD_ON == ETH_VARIANT_POST_BUILD)
        if (NULL_PTR == ConfigPtr)
        {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_INIT, ETH_E_PARAM_POINTER);
            retVal = E_NOT_OK;
        }
        else
#endif /* (STD_ON == ETH_VARIANT_POST_BUILD) */
        {
            if (ETH_CONTROLLER_ID_0_PORT_0 != ConfigPtr->ctrlIdx)
            {
                (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_INIT, ETH_E_INV_PARAM);
                retVal = E_NOT_OK;
            }
        }
#endif /* STD_ON == ETH_DEV_ERROR_DETECT */
        if ((Std_ReturnType)E_OK == retVal)
        {
            retVal = Eth_cpswCheckHostErr();
        }

#if (STD_ON == ETH_DEV_ERROR_DETECT)
        /* rxThresh must be below ETH_NUM_RX_BUFFERS else threshold interrupt happens continuously*/
#if (STD_ON == ETH_QOS_MULTI_QUEUE_SUPPORT)
        if ((Std_ReturnType)E_OK == retVal)
        {
            uint32       i                                    = 0U;
            const uint32 rxBufferSize[ETH_PRIORITY_QUEUE_NUM] = {
                ETH_NUM_RX_BUFFERS_PRI_0, ETH_NUM_RX_BUFFERS_PRI_1, ETH_NUM_RX_BUFFERS_PRI_2, ETH_NUM_RX_BUFFERS_PRI_3,
                ETH_NUM_RX_BUFFERS_PRI_4, ETH_NUM_RX_BUFFERS_PRI_5, ETH_NUM_RX_BUFFERS_PRI_6, ETH_NUM_RX_BUFFERS_PRI_7};

            for (i = 0U; i < ETH_PRIORITY_QUEUE_NUM; i++)
            {
                if (0U != rxBufferSize[i])
                {
                    if (rxBufferSize[i] <= ConfigPtr->cpdmaCfg.rxThreshCount[i])
                    {
                        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_INIT, ETH_E_INV_PARAM);
                        retVal = E_NOT_OK;
                    }
                }
            }
        }
#else
        if (((Std_ReturnType)E_OK == retVal) &&
            (0U != ConfigPtr->cpdmaCfg.rxThreshCount[ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM]) &&
            (ETH_NUM_RX_BUFFERS <= ConfigPtr->cpdmaCfg.rxThreshCount[ETH_CPDMA_DEFAULT_RX_CHANNEL_NUM]))
        {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_INIT, ETH_E_INV_PARAM);
            retVal = E_NOT_OK;
        }
#endif /* ETH_QOS_MULTI_QUEUE_SUPPORT */
#endif /* ETH_DEV_ERROR_DETECT */
        if ((Std_ReturnType)E_OK == retVal)
        {
#if (STD_OFF == ETH_VARIANT_PRE_COMPILE)
            Eth_CfgPtr = ConfigPtr; /* update configuration pointer of postbuild and linktime */
#endif
            Eth_initHw(ConfigPtr);
            /* Change driver state to initialized */
            Eth_DrvStatus = ETH_STATE_INIT;
        }
        else
        {
            /* Eth Driver not initialized*/
        }
    }
    else
    {
        /*Driver already Initialized*/
    }
}

/*******************************************************************************
 * Eth_SetControllerMode
 ******************************************************************************/

/** \brief Enables / disables the indexed controller
 *
 * \param[in] CtrlIdx
 *            CtrlMode
 *
 * \param[out] None
 *
 * \context App
 ******************************************************************************/

/*
 * Design:
 * MCAL-26467, MCAL-26533, MCAL-26481, MCAL-26638, MCAL-26514
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_SetControllerMode(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_ModeType, AUTOMATIC) CtrlMode)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkSetControllerModeErrors(CtrlIdx);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        retVal = Eth_cpswCheckHostErr();
    }

    if ((Std_ReturnType)E_OK == retVal)
    {
        retVal = Eth_setHwControllerMode(CtrlIdx, CtrlMode);
    }

    return retVal;
}

/*******************************************************************************
 * Eth_GetControllerMode
 ******************************************************************************/

/** \brief Reads a list with drop counter values of the corresponding
 *                controller. The meaning of these values is described at
 *                Eth_CounterType.
 *
 * \param[in] CtrlIdx
 *
 * \param[out] CtrlModePtr
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26486, MCAL-26683, MCAL-26529, MCAL-26664, MCAL-26456
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetControllerMode(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetControllerModeErrors(CtrlIdx, CtrlModePtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        *CtrlModePtr = Eth_DrvObj.ctrlMode;
    }

    return retVal;
}

/*******************************************************************************
 * Eth_GetPhysAddr
 ******************************************************************************/

/** \brief Obtains the physical source address used by the indexed
 *                controller.
 *
 * \param[in] CtrlIdx
 *
 * \param[out] PhysAddrPtr
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26485, MCAL-26515, MCAL-26623, MCAL-26512, MCAL-26675
 */
FUNC(void, ETH_CODE)
Eth_GetPhysAddr(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
    Std_ReturnType      retVal   = E_OK;
    Eth_PortConfigType *pPortCfg = (Eth_PortConfigType *)NULL_PTR;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetPhysAddrErrors(CtrlIdx, PhysAddrPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        /* Each port is considered as one controller */
        pPortCfg = &(Eth_DrvObj.portObj.portCfg);

        /* Copy MAC address into PhysAddrPtr variable */
        (void)memcpy(PhysAddrPtr, &pPortCfg->macCfg.macAddr[0U], ETH_MAC_ADDR_LEN);
    }
}

/*******************************************************************************
 * Eth_SetPhysAddr
 ******************************************************************************/

/** \brief Sets the physical source address used by the indexed controller.
 *
 * \param[in] CtrlIdx
 *            PhysAddrPtr
 *
 * \param[out] None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26634, MCAL-26681, MCAL-26612, MCAL-26644, MCAL-26656
 */
FUNC(void, ETH_CODE)
Eth_SetPhysAddr(VAR(uint8, AUTOMATIC) CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
    Std_ReturnType retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkSetPhysAddrErrors(CtrlIdx, PhysAddrPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_setHwPhysAddr(PhysAddrPtr);
    }
}

/*******************************************************************************
 * Eth_UpdatePhysAddrFilter
 ******************************************************************************/

/** \brief Update the physical source address to/from the indexed
 *                controller filter. If the Ethernet Controller is not capable to
 *                do the filtering, the software has to do this.
 *
 * \param[in]     CtrlIdx
 *                PhysAddrPtr
 *                Action
 *
 * \param[out] None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26618, MCAL-26682, MCAL-26668, MCAL-26468, MCAL-26448,
 * MCAL-26523, MCAL-26652, MCAL-26611, MCAL-26604, MCAL-26672
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_UpdatePhysAddrFilter(uint8                CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr,
                         Eth_FilterActionType Action)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkUpdatePhysAddrFilterErrors(CtrlIdx, PhysAddrPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        retVal = Eth_HwUpdatePhysAddrFilter(PhysAddrPtr, Action);
    }

    return retVal;
}

/*******************************************************************************
 * Eth_ProvideTxBuffer
 ******************************************************************************/

/** \brief Provides access to a transmit buffer of the FIFO related to the
 *                specified priority.
 *
 * \param[in]    CtrlIdx
 *               Priority
 *
 * \param[inout] LenBytePtr
 *
 * \param[out]   BufIdxPtr
 *               BufPtr
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26497, MCAL-26633, MCAL-26466, MCAL-26625, MCAL-26697,
 * MCAL-26503, MCAL-26451, MCAL-26449, MCAL-26648, MCAL-26461
 */
FUNC(BufReq_ReturnType, ETH_CODE)
Eth_ProvideTxBuffer(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(uint8, AUTOMATIC) Priority,
                    P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr,
                    P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) * BufPtr, P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr)
{
    VAR(BufReq_ReturnType, AUTOMATIC) retVal = BUFREQ_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkProvideTxBufferErrors(CtrlIdx, BufIdxPtr, BufPtr, LenBytePtr);
    /* Return if a development error occurred */
#endif

#if (STD_ON == ETH_QOS_MULTI_QUEUE_SUPPORT)
    if (((BufReq_ReturnType)BUFREQ_OK == retVal) && (Priority >= (uint8)ETH_PRIORITY_QUEUE_NUM))
    {
#if (ETH_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDE_TX_BUFFER, ETH_E_INV_PARAM);
#endif
        retVal = BUFREQ_E_NOT_OK;
    }
#else
    if (((BufReq_ReturnType)BUFREQ_OK == retVal) && (Priority != (uint8)0))
    {
#if (ETH_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDE_TX_BUFFER, ETH_E_PARAM_POINTER);
#endif
        retVal = BUFREQ_E_NOT_OK;
    }
#endif /* ETH_QOS_MULTI_QUEUE_SUPPORT */

    if ((BufReq_ReturnType)BUFREQ_OK == retVal)
    {
#if (STD_ON == ETH_QOS_MULTI_QUEUE_SUPPORT)
        retVal = Eth_provideHwTxBuffer(Priority, BufIdxPtr, BufPtr, LenBytePtr);
#else
        retVal = Eth_provideHwTxBuffer(BufIdxPtr, BufPtr, LenBytePtr);
#endif
    }

    return retVal;
}

/*******************************************************************************
 * Eth_Transmit
 ******************************************************************************/

/** \brief Triggers transmission of a previously filled transmit buffer.
 *
 * \param[in]  CtrlIdx
 *             BufIdx
 *             FrameType
 *             TxConfirmation
 *             LenByte
 *             PhysAddrPtr
 *
 * \param[out] None
 *
 * \context App
 ******************************************************************************/

/*
 * Design:
 * MCAL-26532, MCAL-26459, MCAL-26689, MCAL-26646, MCAL-26540,
 * MCAL-26479, MCAL-26590, MCAL-26496, MCAL-26630
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_Transmit(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_BufIdxType, AUTOMATIC) BufIdx,
             VAR(Eth_FrameType, AUTOMATIC) FrameType, VAR(boolean, AUTOMATIC) TxConfirmation,
             VAR(uint16, AUTOMATIC) LenByte, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkTransmitErrors(CtrlIdx, BufIdx, PhysAddrPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        retVal = Eth_transmitHw(BufIdx, FrameType, TxConfirmation, LenByte, PhysAddrPtr);
    }

    return retVal;
}

/*******************************************************************************
 * Eth_Receive
 ******************************************************************************/

/** \brief Receive a frame from the related fifo.
 *
 * \param[in]  CtrlIdx
 *             FifoIdx
 *
 * \param[out] RxStatusPtr
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26667, MCAL-26561, MCAL-26517, MCAL-26572, MCAL-26591,
 * MCAL-26640
 */
FUNC(void, ETH_CODE)
Eth_Receive(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(uint8, AUTOMATIC) FifoIdx,
            P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkReceiveErrors(CtrlIdx, FifoIdx);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_receiveHw(FifoIdx, RxStatusPtr);
    }
}

/*******************************************************************************
 * Eth_WriteMii
 ******************************************************************************/

/** \brief Configures a transceiver register or triggers a function
 *                offered by the receiver.
 *
 * \param[in]     CtrlIdx
 *                TrcvIdx
 *                RegIdx
 *                RegVal
 *
 * \param[out] None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26650, MCAL-26465, MCAL-26631, MCAL-26601, MCAL-26649,
 * MCAL-26606
 */
#if (ETH_ENABLE_MII_API == STD_ON)
FUNC(Std_ReturnType, ETH_CODE)
Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == ETH_DEV_ERROR_DETECT)
    retVal = Eth_checkWriteMiiErrors(CtrlIdx);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        /*
         * Requirements SWS_Eth_00241
         * The function shall call EthTrcv_WriteMiiIndication when the MII
         * access finished.
         */
        CpswMdio_writePhyReg(Eth_DrvObj.baseAddr, TrcvIdx, RegIdx, RegVal);
        retVal = E_OK;
    }

    return retVal;
}
#endif /* #if (ETH_ENABLE_MII_API == STD_ON) */

/*******************************************************************************
 * Eth_ReadMii
 ******************************************************************************/

/** \brief Reads a transceiver register.
 *
 * \param[in]     CtrlIdx
 *                TrcvIdx
 *                RegIdx
 *
 * \param[out] RegValPtr
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26568, MCAL-26576, MCAL-26546, MCAL-26463, MCAL-26543,
 * MCAL-26574, MCAL-26477
 */
#if (ETH_ENABLE_MII_API == STD_ON)
FUNC(Std_ReturnType, ETH_CODE)
Eth_ReadMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == ETH_DEV_ERROR_DETECT)
    retVal = Eth_checkReadMiiErrors(CtrlIdx, RegValPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        /*
         * Requirements: SWS_Eth_00242
         * The function shall call EthTrcv_ReadMiiIndication when the MII
         * access finished.
         */
        CpswMdio_readPhyReg(Eth_DrvObj.baseAddr, TrcvIdx, RegIdx, RegValPtr);
        retVal = E_OK;
    }

    return retVal;
}
#endif /* #if (ETH_ENABLE_MII_API == STD_ON) */

/*******************************************************************************
 * Eth_GetCounterValues
 ******************************************************************************/

/** \brief Reads a list with drop counter values of the corresponding
 *                controller. The meaning of these values is described at
 *                Eth_CounterType.
 *
 * \param[in] uint8 CtrlIdx
 *
 * \param[out] CounterPtr
 *
 * \context App
 ******************************************************************************/

/*
 * Design:
 * MCAL-26594, MCAL-26498, MCAL-26671, MCAL-26555, MCAL-26583,
 * MCAL-26567
 */
#if (ETH_GET_DROPCOUNT_API == STD_ON)
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetCounterValues(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) CounterPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetCounterValuesErrors(CtrlIdx, CounterPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_getHwCounterValues(CounterPtr);
        retVal = E_OK;
    }

    return retVal;
}
#endif /* #if (ETH_GET_DROPCOUNT_API == STD_ON) */

/*******************************************************************************
 * Eth_GetRxStats
 ******************************************************************************/

/** \brief Returns the following list according to IETF RFC2819, where the
 *                maximal possible value shall denote an invalid value.
 *
 * \param[in] CtrlIdx
 *
 * \param[out] RxStats
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26698, MCAL-26593, MCAL-26537, MCAL-26516, MCAL-26659
 */
#if (ETH_GETETHERSTATS_API == STD_ON)
FUNC(Std_ReturnType, ETH_CODE_FAST)
Eth_GetRxStats(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetRxStatsErrors(CtrlIdx, RxStats);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_getHwRxStats(RxStats);
        retVal = E_OK;
    }

    return retVal;
}
#endif /*ETH_GETETHERSTATS_API == STD_ON*/

/*******************************************************************************
 * Eth_GetTxStats
 ******************************************************************************/

/** \brief Returns the list of Transmission Statistics out of IETF RFC1213
 *                defined with Eth_TxStatsType, where the maximal possible value
 *                shall denote an invalid value, e.g. this counter is not
 *                available.
 *
 *
 * \param[in] CtrlIdx
 *
 * \param[out] TxStats
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26571, MCAL-26534, MCAL-26510, MCAL-26575, MCAL-26489
 */
#if (ETH_GETTX_STATS_API == STD_ON)
FUNC(Std_ReturnType, ETH_CODE_FAST)
Eth_GetTxStats(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetTxStatsErrors(CtrlIdx, TxStats);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_getHwTxStats(TxStats);
        retVal = E_OK;
    }

    return retVal;
}
#endif /* ETH_GETTX_STATS_API==STD_ON */

/*******************************************************************************
 * Eth_GetTxErrorCounterValues
 ******************************************************************************/

/** \brief Returns the list of Transmission Error Counters out of IETF
 *                RFC1213 and RFC1643 defined with Eth_TxErrorCounterValuesType,
 *                where the maximal possible value shall denote an invalid value,
 *                e.g. this counter is not available.
 *
 *
 * \param[in] CtrlIdx
 *
 * \param[out] TxErrorCounterValues
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26458, MCAL-26653, MCAL-26541, MCAL-26585, MCAL-26452
 */
#if (ETH_GETTXERROR_COUNTERVALUES_API == STD_ON)
FUNC(Std_ReturnType, ETH_CODE_FAST)
Eth_GetTxErrorCounterValues(VAR(uint8, AUTOMATIC) CtrlIdx,
                            P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetTxErrorCounterValueErrors(CtrlIdx, TxErrorCounterValues);
#endif
    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_HwGetTxErrorCounterValues(TxErrorCounterValues);
        retVal = E_OK;
    }

    return retVal;
}
#endif /* ETH_GETTXERROR_COUNTERVALUES_API == STD_ON */

/*******************************************************************************
 * Eth_GetCurrentTime
 ******************************************************************************/

/** \brief Returns a time value out of the HW registers according to the
 *                capability of the HW. Is the HW resolution is lower than the
 *                Eth_TimeStampType resolution resp. range, than an the remaining
 *                bits will be filled with 0.
 *
 * \param[in] uint8 CtrlIdx
 *
 * \param[out]     timeQualPtr
 *                 timeStampPtr
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26696, MCAL-26569, MCAL-26531, MCAL-26447, MCAL-26608
 */
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetCurrentTime(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                   P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetCurrentTimeErrors(CtrlIdx, timeQualPtr, timeStampPtr);
#endif

    (void)memset(timeStampPtr, 0, sizeof(Eth_TimeStampType));

    if (((Std_ReturnType)E_OK == retVal) && (ETH_MODE_ACTIVE == Eth_DrvObj.ctrlMode))
    {
        uint64             nsec          = 0U;
        CpswCpts_StateObj *pCptsStateObj = &Eth_DrvObj.cptsObj;

        retVal = CpswCpts_readTimestamp(pCptsStateObj, &nsec);

        if ((Std_ReturnType)E_NOT_OK != retVal)
        {
            CpswCpts_getSysTime(&nsec, timeStampPtr);
            /* Quality information not supported, the value always Valid. */
            *timeQualPtr = ETH_VALID;
        }
    }
    else
    {
        *timeQualPtr = ETH_INVALID;
    }

    return retVal;
}

/*******************************************************************************
 * Eth_EnableEgressTimeStamp
 ******************************************************************************/

/** \brief Activates egress time stamping on a dedicated message object.
 *                Some HW does store once the egress time stamp marker and some
 *                HW needs it always before transmission. There will be no
 *                "disable" functionality, due to the fact, that the message type
 *                is always "time stamped" by network design.
 *
 * \param[in]  CtrlIdx
 *             BufIdx
 *
 * \param[out] None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26624, MCAL-26690, MCAL-26637, MCAL-26500
 */
FUNC(void, ETH_CODE)
Eth_EnableEgressTimeStamp(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_BufIdxType, AUTOMATIC) BufIdx)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkEnableEgressTimeStampErrors(CtrlIdx);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        /* time stamping is always enabled */
        Eth_TxBufObjType *pTempBufObj      = &(Eth_DrvObj.portObj.txBufObjArray[BufIdx]);
        pTempBufObj->enableEgressTimeStamp = (boolean)TRUE;
    }
}

/*******************************************************************************
 * Eth_GetEgressTimeStamp
 ******************************************************************************/

/** \brief Reads back the egress time stamp on a dedicated message object.
 *                It must be called within the TxConfirmation() function
 *
 * \param[in]     CtrlIdx
 *                BufIdx
 *
 * \param[out]     timeQualPtr
 *                timeStampPtr
 *
 * \context App
 ******************************************************************************/

/*
 * Design:
 * MCAL-26645, MCAL-26676, MCAL-26562, MCAL-26605, MCAL-26475
 */
FUNC(void, ETH_CODE)
Eth_GetEgressTimeStamp(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_BufIdxType, AUTOMATIC) BufIdx,
                       P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                       P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetEgressTimeStampErrors(CtrlIdx, timeQualPtr, timeStampPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_getHwEgressTimeStamp(BufIdx, timeQualPtr, timeStampPtr);
    }
}

/*******************************************************************************
 * Eth_GetIngressTimeStamp
 ******************************************************************************/

/** \brief Reads back the ingress time stamp on a dedicated message object.
 *                It must be called within the RxIndication() function
 *
 * \param[in]     CtrlIdx
 *                DataPtr
 *
 * \param[out]     timeQualPtr
 *                timeStampPtr
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26524, MCAL-26525, MCAL-26457, MCAL-26643, MCAL-26687
 */
FUNC(void, ETH_CODE)
Eth_GetIngressTimeStamp(VAR(uint8, AUTOMATIC) CtrlIdx, P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
                        P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                        P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetIngressTimeStampErrors(CtrlIdx, DataPtr, timeQualPtr, timeStampPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        Eth_getHwIngressTimeStamp(DataPtr, timeQualPtr, timeStampPtr);
    }
}
#endif /* ETH_GLOBALTIMESUPPORT_API == STD_ON */

/*******************************************************************************
 * Eth_TxConfirmation
 ******************************************************************************/

/** \brief Triggers frame transmission confirmation.
 *
 * \param[in]     CtrlIdx
 *
 * \param[out]     None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26539, MCAL-26632, MCAL-26504, MCAL-26560, MCAL-26530,
 * MCAL-26494
 */
FUNC(void, ETH_CODE) Eth_TxConfirmation(VAR(uint8, AUTOMATIC) CtrlIdx)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkTxConfirmationErrors(CtrlIdx);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_0();

        /* check all filled transmit buffers for successful transmission */
        Eth_processTxBuffDesc(Eth_DrvObj.ctrlIdx, ETH_CPDMA_DEFAULT_TX_CHANNEL_NUM);

        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_0();
    }
}

/*******************************************************************************
 * Eth_SetBandwidthLimit
 ******************************************************************************/

/** \brief Set bandwidth limit for traffic shaping.
 *
 * \param[in]     CtrlIdx
 *                QueuePrio
 *                BandwidthLimit
 *
 * \param[out]     None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26535
 */
#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
FUNC(void, ETH_CODE)
Eth_SetBandwidthLimit(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(uint8, AUTOMATIC) QueuePrio,
                      VAR(uint32, AUTOMATIC) BandwidthLimit)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkSetBandwidthLimitErrors(CtrlIdx, QueuePrio, BandwidthLimit);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        retVal = CpswPort_setBandwidthLimit(Eth_DrvObj.baseAddr, Eth_DrvObj.portObj.portNum, QueuePrio,
                                            Eth_DrvObj.ethConfig.cpdmaCfg.pacingClkFreq, BandwidthLimit);
#if (STD_ON == ETH_DEV_ERROR_DETECT)
        if (E_NOT_OK == retVal)
        {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_BANDWIDTH_LIMIT, ETH_E_INV_PARAM);
        }
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
    }
}

/*******************************************************************************
 * Eth_GetBandwidthLimit
 ******************************************************************************/

/** \brief Get bandwidth limit for traffic shaping.
 *
 * \param[in]     CtrlIdx
 *                QueuePrio
 *                BandwidthLimitPtr
 *
 * \param[out]     None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26535
 */
FUNC(void, ETH_CODE)
Eth_GetBandwidthLimit(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(uint8, AUTOMATIC) QueuePrio,
                      P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) BandwidthLimitPtr)
{
    VAR(Std_ReturnType, AUTOMATIC) retVal = E_OK;

#if (ETH_DEV_ERROR_DETECT == STD_ON)
    retVal = Eth_checkGetBandwidthLimitErrors(CtrlIdx, QueuePrio, BandwidthLimitPtr);
#endif

    if ((Std_ReturnType)E_OK == retVal)
    {
        CpswPort_getBandwidthLimit(Eth_DrvObj.baseAddr, Eth_DrvObj.portObj.portNum, QueuePrio,
                                   Eth_DrvObj.ethConfig.cpdmaCfg.pacingClkFreq, BandwidthLimitPtr);
    }
}
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

/*******************************************************************************
 * Eth_MainFunction
 ******************************************************************************/

/** \brief The function checks for controller errors and lost frames.
 *                Used for polling state changes. Calls EthIf_CtrlModeIndication
 *                when the controller mode changed.
 *
 * \param[in]     None
 *
 * \param[out]     None
 *
 ******************************************************************************/

/*
 * Design:
 * MCAL-26626, MCAL-26570, MCAL-26666
 */
FUNC(void, ETH_CODE_FAST) Eth_MainFunction(void)
{
    Eth_ModeType   ctrlMode;
    Std_ReturnType retVal = E_NOT_OK;

#if (STD_ON == ETH_DEV_ERROR_DETECT)
    if (ETH_STATE_UNINIT == Eth_DrvStatus)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_MAIN_FUNCTION, ETH_E_UNINIT);
    }
    else
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
    {
        ctrlMode = Eth_DrvObj.ctrlMode;
        if (ETH_MODE_DOWN != ctrlMode)
        {
            retVal = Eth_cpswCheckHostErr();
            if ((Std_ReturnType)E_OK == retVal)
            {
                Eth_checkHwCtrlErrors();
            }
        }

        if (TRUE == Eth_ControllerModeChangeFlag)
        {
            EthIf_CtrlModeIndication(Eth_DrvObj.ctrlIdx, ctrlMode);
            Eth_ControllerModeChangeFlag = FALSE;
        }
    }
}

#if (ETH_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkSetControllerModeErrors(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_CONTROLLER_MODE, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }
    else if (ctrlIdx != ETH_CONTROLLER_ID_0_PORT_0)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_CONTROLLER_MODE, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (ETH_DEV_ERROR_DETECT == STD_ON)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetControllerModeErrors(uint8 ctrlIdx, const Eth_ModeType *ctrlModePtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_CONTROLLER_MODE, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_CONTROLLER_MODE, ETH_E_INV_CTRL_IDX);
    }
    else if (ctrlModePtr == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_CONTROLLER_MODE, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetPhysAddrErrors(uint8 ctrlIdx, const uint8 *physAddrPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_PHYS_ADDR, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_PHYS_ADDR, ETH_E_INV_CTRL_IDX);
    }
    else if (physAddrPtr == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_PHYS_ADDR, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkSetPhysAddrErrors(uint8 ctrlIdx, const uint8 *physAddrPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_PHYS_ADDR, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_PHYS_ADDR, ETH_E_INV_CTRL_IDX);
    }
    else if (physAddrPtr == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_PHYS_ADDR, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkUpdatePhysAddrFilterErrors(uint8 ctrlIdx, const uint8 *physAddrPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_UPDATE_PHYS_ADDR_FILTER, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_UPDATE_PHYS_ADDR_FILTER, ETH_E_INV_CTRL_IDX);
    }
    else if (physAddrPtr == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_UPDATE_PHYS_ADDR_FILTER, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(BufReq_ReturnType, ETH_CODE) Eth_checkProvideTxBufferErrors(uint8 ctrlIdx, const Eth_BufIdxType *bufIdxPtr,
                                                                        uint8 **bufPtr, const uint16 *lenBytePtr)
{
    VAR(BufReq_ReturnType, AUTOMATIC) retVal = BUFREQ_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDE_TX_BUFFER, ETH_E_UNINIT);
        retVal = BUFREQ_E_NOT_OK;
    }

    if ((ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx) && (retVal == BUFREQ_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDE_TX_BUFFER, ETH_E_INV_CTRL_IDX);
        retVal = BUFREQ_E_NOT_OK;
    }

    if ((bufIdxPtr == NULL_PTR) && (retVal == BUFREQ_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDE_TX_BUFFER, ETH_E_PARAM_POINTER);
        /* ETH_INV_POINTER */
        retVal = BUFREQ_E_NOT_OK;
    }

    if ((bufPtr == NULL_PTR) && (retVal == BUFREQ_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDE_TX_BUFFER, ETH_E_PARAM_POINTER);
        /* ETH_INV_POINTER */
        retVal = BUFREQ_E_NOT_OK;
    }

    if ((lenBytePtr == NULL_PTR) && (retVal == BUFREQ_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_PROVIDE_TX_BUFFER, ETH_E_PARAM_POINTER);
        /* ETH_INV_POINTER */
        retVal = BUFREQ_E_NOT_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkTransmitErrors(uint8 ctrlIdx, Eth_BufIdxType bufIdx, const uint8 *physAddrPtr)
{
    Std_ReturnType retVal = E_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }

#if (STD_ON == ETH_QOS_MULTI_QUEUE_SUPPORT)
    /* Mask Priority at upper byte */
    if (((bufIdx & ETH_BUFFER_IDX_MASK) >= ETH_NUM_TX_BUFFERS) && (retVal == (Std_ReturnType)E_OK))
#else
    if ((bufIdx >= ETH_NUM_TX_BUFFERS) && (retVal == (Std_ReturnType)E_OK))
#endif
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_INV_PARAM);
        retVal = E_NOT_OK;
    }

#if (STD_ON == ETH_QOS_MULTI_QUEUE_SUPPORT)
    /* Mask Priority at upper byte */
    if (((bufIdx / ETH_PRIORITY_IDX_BASE) >= ETH_PRIORITY_QUEUE_NUM) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_INV_PARAM);
        retVal = E_NOT_OK;
    }
#endif

    if ((Eth_DrvObj.ctrlMode != ETH_MODE_ACTIVE) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_INV_MODE);
        retVal = E_NOT_OK;
    }

    if ((physAddrPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TRANSMIT, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkReceiveErrors(uint8 ctrlIdx, uint8 FifoIdx)
{
    Std_ReturnType retVal = E_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RECEIVE, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ctrlIdx != ETH_CONTROLLER_ID_0_PORT_0) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RECEIVE, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }

    if ((Eth_DrvObj.ctrlMode != ETH_MODE_ACTIVE) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RECEIVE, ETH_E_INV_MODE);
        retVal = E_NOT_OK;
    }

#if (STD_ON == ETH_QOS_MULTI_QUEUE_SUPPORT)
    if ((FifoIdx >= (uint8)ETH_PRIORITY_QUEUE_NUM) && (retVal == (Std_ReturnType)E_OK))
#else
    /* Priority is not supported and app should always pass it as 0 */
    if ((FifoIdx != (uint8)0) && (retVal == (Std_ReturnType)E_OK))
#endif
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RECEIVE, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/

#if (STD_ON == ETH_ENABLE_MII_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkWriteMiiErrors(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_WRITE_MII, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_WRITE_MII, ETH_E_INV_CTRL_IDX);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /*STD_ON == ETH_ENABLE_MII_API*/

#if (STD_ON == ETH_ENABLE_MII_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkReadMiiErrors(uint8 ctrlIdx, const uint16 *regValPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_READ_MII, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_READ_MII, ETH_E_INV_CTRL_IDX);
    }
    else if (NULL_PTR == regValPtr)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_READ_MII, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /* (STD_ON == ETH_ENABLE_MII_API) */

#if (ETH_GET_DROPCOUNT_API == STD_ON)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetCounterValuesErrors(uint8 ctrlIdx, const Eth_CounterType *CounterPtr)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_COUNTER_VALUES, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_COUNTER_VALUES, ETH_E_INV_CTRL_IDX);
    }
    else if (CounterPtr == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_COUNTER_VALUES, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /*ETH_GET_DROPCOUNT_API==STD_ON*/

#if (ETH_GETETHERSTATS_API == STD_ON)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetRxStatsErrors(uint8 ctrlIdx, const Eth_RxStatsType *RxStats)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_RX_STATS, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_RX_STATS, ETH_E_INV_CTRL_IDX);
    }
    else if (RxStats == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_RX_STATS, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /* (STD_ON == ETH_GETETHERSTATS_API) */

#if (ETH_GETTX_STATS_API == STD_ON)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkGetTxStatsErrors(uint8 ctrlIdx, const Eth_TxStatsType *TxStats)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_TX_STATS, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_TX_STATS, ETH_E_INV_CTRL_IDX);
    }
    else if (TxStats == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_TX_STATS, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /* (STD_ON == ETH_GETTX_STATS_API) */

#if (STD_ON == ETH_GETTXERROR_COUNTERVALUES_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetTxErrorCounterValueErrors(uint8 ctrlIdx, const Eth_TxErrorCounterValuesType *TxErrorCounterValues)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_TXERROR_COUNTERVALUES, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_TXERROR_COUNTERVALUES, ETH_E_INV_CTRL_IDX);
    }
    else if (TxErrorCounterValues == NULL_PTR)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_TXERROR_COUNTERVALUES, ETH_E_PARAM_POINTER);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /*STD_ON == ETH_GETTXERROR_COUNTERVALUES_API*/

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetCurrentTimeErrors(uint8 ctrlIdx, const Eth_TimeStampQualType *timeQualPtr,
                                  const Eth_TimeStampType *timeStampPtr)
{
    Std_ReturnType retVal = E_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_CURRENT_TIME, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_CURRENT_TIME, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }

    if ((timeQualPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_CURRENT_TIME, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    if ((timeStampPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_CURRENT_TIME, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkEnableEgressTimeStampErrors(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_ENABLE_EGRESS_TIMESTAMP, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_ENABLE_EGRESS_TIMESTAMP, ETH_E_INV_CTRL_IDX);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetEgressTimeStampErrors(uint8 ctrlIdx, const Eth_TimeStampQualType *timeQualPtr,
                                      const Eth_TimeStampType *timeStampPtr)
{
    Std_ReturnType retVal = E_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_EGRESS_TIMESTAMP, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_EGRESS_TIMESTAMP, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }

    if ((timeQualPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_EGRESS_TIMESTAMP, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    if ((timeStampPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_EGRESS_TIMESTAMP, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetIngressTimeStampErrors(uint8 ctrlIdx, const Eth_DataType *dataPtr,
                                       const Eth_TimeStampQualType *timeQualPtr, const Eth_TimeStampType *timeStampPtr)
{
    Std_ReturnType retVal = E_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_INGRESS_TIMESTAMP, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_INGRESS_TIMESTAMP, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }

    if ((dataPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_INGRESS_TIMESTAMP, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    if ((timeQualPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_INGRESS_TIMESTAMP, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    if ((timeStampPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_INGRESS_TIMESTAMP, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /*STD_ON == ETH_DEV_ERROR_DETECT*/
#endif /* (STD_ON == ETH_GLOBALTIMESUPPORT_API) */

#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE) Eth_checkTxConfirmationErrors(uint8 ctrlIdx)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*  ETH_NOT_INITIALIZED */
    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TX_CONFIRMATION, ETH_E_UNINIT);
    }
    else if (ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TX_CONFIRMATION, ETH_E_INV_CTRL_IDX);
    }
    else if (Eth_DrvObj.ctrlMode != ETH_MODE_ACTIVE)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TX_CONFIRMATION, ETH_E_INV_MODE);
    }
    else
    {
        retVal = E_OK;
    }

    return retVal;
}
#endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */

#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkSetBandwidthLimitErrors(uint8 ctrlIdx, uint8 queuePrio, uint32 bandwidthLimit)
{
    Std_ReturnType retVal = E_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_BANDWIDTH_LIMIT, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_BANDWIDTH_LIMIT, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }

    if ((queuePrio >= ETH_PRIORITY_QUEUE_NUM) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_SET_BANDWIDTH_LIMIT, ETH_E_INV_PARAM);
        retVal = E_NOT_OK;
    }

    (void)bandwidthLimit;

    return retVal;
}
#endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
#if (STD_ON == ETH_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, ETH_CODE)
    Eth_checkGetBandwidthLimitErrors(uint8 ctrlIdx, uint8 queuePrio, const uint32 *BandwidthLimitPtr)
{
    Std_ReturnType retVal = E_OK;

    if (Eth_DrvStatus == ETH_STATE_UNINIT)
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_BANDWIDTH_LIMIT, ETH_E_UNINIT);
        retVal = E_NOT_OK;
    }

    if ((ETH_CONTROLLER_ID_0_PORT_0 != ctrlIdx) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_BANDWIDTH_LIMIT, ETH_E_INV_CTRL_IDX);
        retVal = E_NOT_OK;
    }

    if ((queuePrio >= ETH_PRIORITY_QUEUE_NUM) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_BANDWIDTH_LIMIT, ETH_E_INV_PARAM);
        retVal = E_NOT_OK;
    }

    if ((BandwidthLimitPtr == NULL_PTR) && (retVal == (Std_ReturnType)E_OK))
    {
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_GET_BANDWIDTH_LIMIT, ETH_E_PARAM_POINTER);
        retVal = E_NOT_OK;
    }

    return retVal;
}
#endif /* (STD_ON == ETH_DEV_ERROR_DETECT) */
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
