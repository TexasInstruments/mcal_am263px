/*
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Eth.h
 *
 *  \brief    This file contains interface header for ETH MCAL driver
 *
 */

/**
 *  \defgroup MCAL_ETH_API Ethernet Driver API
 *
 *  The Eth Driver MCAL provides low level access to Ethernet peripheral
 *  present on AM263x/AM27x Device.<br>
 *  The Eth Driver implements a standardized interface specified in the
 *  AUTOSAR_SWS_EthDriver document.<br>
 *  The Eth Driver is part of the Communication Stack in the AUTOSAR
 *  Basic Software (BSW)<br>
 *  The Eth Hardware Unit controlled by Eth Driver combines one or several
 *  Eth controllers, which may be located on-chip or as external
 *  standalone devices of the same type, with common or separate
 *  Hardware Objects<br>
 *  @sa MCAL_ETH_CFG
 *  @{
 */

/*
 * Design: SITARA_MCU_MCAL-4813,SITARA_MCU_MCAL-4259
 */

#ifndef ETH_H_
#define ETH_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* Requirements : SWS_Eth_00148 */

/*
 * Design: SITARA_MCU_MCAL-2309
 */
#include "Eth_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Design: SITARA_MCU_MCAL-2417
 */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*                                None                                            */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name Eth Driver Module SW Version Info
 *
 *  Defines for ETH Driver version used for compatibility checks
 *  @{
 */
/* Requirements : SWS_Eth_00006 */

/*
 * Design: SITARA_MCU_MCAL-2421
 */
/** \brief Driver Implementation Major Version */
#define ETH_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define ETH_SW_MINOR_VERSION (1U)
/** \brief Driver Implementation Patch Version */
#define ETH_SW_PATCH_VERSION (0U)
/* @} */

/**
 *  \name Eth Driver Module AUTOSAR Version Info
 *
 *  Defines for ETH Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by Eth Driver */
#define ETH_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by Eth Driver */
#define ETH_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by Eth Driver */
#define ETH_AR_RELEASE_REVISION_VERSION (1U)
/* @} */

/**
 *  \name Eth Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define ETH_VENDOR_ID (44U)
/** \brief Eth Driver Module ID */
#define ETH_MODULE_ID (88U)
/** \brief Eth Driver Instance ID */
#define ETH_INSTANCE_ID (0U)
/* @} */

/**
 *  \name Eth Controller names.
 *
 *  Symbolic names for the EthControllerId.  Only 1 controller is supported.
 *  @{
 */
/* Requirements : SWS_Eth_00003 */
/** \brief Eth controller ID 0 Port 1 - donot change the macro value */
#define ETH_CONTROLLER_ID_0_PORT_0 (uint8)0U
#define ETH_CONTROLLER_ID_0_PORT_1 (uint8)1U
#define ETH_CONTROLLER_ID_0_PORT_2 (uint8)2U
/* @} */

/**
 *  \name Eth Driver ISR category level
 *
 *  Defines for Eth Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define ETH_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define ETH_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define ETH_ISR_CAT2 (0x02U)
/* @} */

/**
 *  \name Eth Error Codes
 *
 *  Error codes returned by Eth functions
 *  @{
 */

/*
 * Design: SITARA_MCU_MCAL-2413
 */
#ifndef ETH_E_INV_CTRL_IDX
/** \brief Invalid controller index */
#define ETH_E_INV_CTRL_IDX (0x01U)
#endif
#ifndef ETH_E_UNINIT
/** \brief Eth module was not initialized */
#define ETH_E_UNINIT (0x02U)
#endif
#ifndef ETH_E_PARAM_POINTER
/** \brief Invalid pointer in parameter list */
#define ETH_E_PARAM_POINTER (0x03U)
#endif
#ifndef ETH_E_INV_PARAM
/** \brief Invalid parameter */
#define ETH_E_INV_PARAM (0x04U)
#endif
#ifndef ETH_E_INV_MODE
/** \brief Invalid mode */
#define ETH_E_INV_MODE (0x05U)
#endif
/* @} */

/**
 *  \name Eth Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function and
 *  is used to identify the source of the error
 *  @{
 */
/** \brief Eth_Init() API Service ID */
#define ETH_SID_INIT (0x01U)

/** \brief Eth_SetControllerMode() API Service ID */
#define ETH_SID_SET_CONTROLLER_MODE (0x03U)

/** \brief Eth_GetControllerMode() API Service ID */
#define ETH_SID_GET_CONTROLLER_MODE (0x04U)

/** \brief Eth_WriteMii() API Service ID */
#define ETH_SID_WRITE_MII (0x05U)

/** \brief Eth_ReadMii() API Service ID */
#define ETH_SID_READ_MII (0x06U)

/** \brief Eth_GetPhysAddr() API Service ID */
#define ETH_SID_GET_PHYS_ADDR (0x08U)

/** \brief Eth_ProvideTxBuffer() API Service ID */
#define ETH_SID_PROVIDE_TX_BUFFER (0x09U)

/** \brief Eth_MainFunction() API Service ID */
#define ETH_SID_MAIN_FUNCTION (0x20U)

/** \brief Eth_Transmit() API Service ID */
#define ETH_SID_TRANSMIT (0x0AU)

/** \brief Eth_Receive() API Service ID */
#define ETH_SID_RECEIVE (0x0BU)

/** \brief Eth_TxConfirmation() API Service ID */
#define ETH_SID_TX_CONFIRMATION (0x0CU)

/** \brief Eth_GetVersionInfo() API Service ID */
#define ETH_SID_GET_VERSION_INFO (0x0DU)

/** \brief Eth_UpdatePhysAddrFilter() API Service ID */
#define ETH_SID_UPDATE_PHYS_ADDR_FILTER (0x12U)

/** \brief Eth_SetPhysAddr() API Service ID */
#define ETH_SID_SET_PHYS_ADDR (0x13U)

/** \brief Eth_GetCounterValues() API Service ID */
#define ETH_SID_GET_COUNTER_VALUES (0x14U)

/** \brief Eth_GetRxStats() API Service ID */
#define ETH_SID_GET_RX_STATS (0x15U)

/** \brief Eth_GetTxStats() API Service ID */
#define ETH_SID_GET_TX_STATS (0x1CU)

/** \brief Eth_GetTxErrorCounterValues() API Service ID */
#define ETH_SID_GET_TXERROR_COUNTERVALUES (0x1DU)

/** \brief Eth_GetCurrentTime() API Service ID */
#define ETH_SID_GET_CURRENT_TIME (0x16U)

/** \brief Eth_EnableEgressTimeStamp() API Service ID */
#define ETH_SID_ENABLE_EGRESS_TIMESTAMP (0x17U)

/** \brief Eth_GetEgressTimeStamp() API Service ID */
#define ETH_SID_GET_EGRESS_TIMESTAMP (0x18U)

/** \brief Eth_GetIngressTimeStamp() API Service ID */
#define ETH_SID_GET_INGRESS_TIMESTAMP (0x19U)

/** \brief Eth_RxIrqHdlr_<CtrlIdx>() API Service ID */
#define ETH_SID_RX_IRQ_HDLR (0x10U)

/** \brief Eth_TxIrqHdlr_<CtrlIdx>() API Service ID */
#define ETH_SID_TX_IRQ_HDLR (0x11U)

/** \brief Eth_RxThreshIrqHdlr_<CtrlIdx>() API Service ID */
#define ETH_SID_RXTHR_IRQ_HDLR (0x21U)

/** \brief Eth_SetBandwidthLimit() API Service ID */
#define ETH_SID_SET_BANDWIDTH_LIMIT (0x50U)

/** \brief Eth_GetBandwidthLimit() API Service ID */
#define ETH_SID_GET_BANDWIDTH_LIMIT (0x51U)

/* @} */

/**
 *  \name Eth Driver CallOut function id
 *
 *  The Service Id is one of the argument to Det_ReportError function and is
 *  used to identify the source of the error
 *  @{
 */
/** \brief EthIf_RxIndication callback ID */
#define ETH_SID_RXINDI ((uint8)0x1CU)
/** \brief EthIf_TxConfirmation callback ID */
#define ETH_SID_TXCNF ((uint8)0x1DU)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief This function initializes the driver.
 *
 *  \verbatim
 *  Service name      : Eth_Init
 *  Syntax            : void Eth_Init(
 *                          const Eth_ConfigType* CfgPtr
 *                      )
 *  Service ID[hex]   : 0x01
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CfPtr.
 *                      Pointer to driver configuration.
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Initializes the Ethernet Driver.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_Init(P2CONST(Eth_ConfigType, AUTOMATIC, ETH_PBCFG) CfgPtr);

/**
 *  \brief This function enables / disables the indexed controller.
 *
 *  \verbatim
 *  Service name      : Eth_SetControllerMode
 *  Syntax            : Std_ReturnType Eth_SetControllerMode(
 *                          uint8 CtrlIdx,
 *                          Eth_ModeType CtrlMode)
 *  Service ID[hex]   : 0x03
 *  Sync/Async        : Asynchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context
 *                               of the Ethernet Driver
 *                      CtrlMode.
 *                        ETH_MODE_DOWN: disable the controller
 *                        ETH_MODE_ACTIVE: enable the controller
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: controller mode could not be changed
 *  Description       : Enables / disables the indexed controller.
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_SetControllerMode(uint8 CtrlIdx, Eth_ModeType CtrlMode);

/**
 *  \brief This function obtains the state of the indexed controller.
 *
 *  \verbatim
 *  Service name      : Eth_GetControllerMode
 *  Syntax            : Std_ReturnType Eth_GetControllerMode(
 *                          uint8 CtrlIdx,
 *                          Eth_ModeType *CtrlModePtr
 *                      )
 *  Service ID[hex]   : 0x04
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context
 *                               of the Ethernet Driver
 *  Parameters (inout): CtrlModePtr
 *                        ETH_MODE_DOWN: the controller is disabled
 *                        ETH_MODE_ACTIVE: the controller is enabled
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: controller mode could not be obtained
 *  Description       : Obtains the state of the indexed controller.
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetControllerMode(uint8 CtrlIdx, P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr);

/**
 *  \brief This function obtains the physical source address used by the indexed
 *         controller
 *
 *  \verbatim
 *  Service name      : Eth_GetPhysAddr
 *  Syntax            : void Eth_GetPhysAddr(
 *                          uint8 CtrlIdx,
 *                          uint8 *PhysAddrPtr
 *                      )
 *  Service ID[hex]   : 0x08
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (inout):
 *  Parameters (out)  : PhysAddrPtr. Physical source address (MAC address) in
 *                                   network byte order
 *  Return value      : None
 *  Description       : Obtains the physical source address used by the indexed
 *                      controller.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_GetPhysAddr(uint8 CtrlIdx, P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

/**
 *  \brief This function sets the physical source address used by the indexed
 *         controller.
 *
 *  \verbatim
 *  Service name      : Eth_SetPhysAddr
 *  Syntax            : void Eth_SetPhysAddr(
 *                          uint8 CtrlIdx,
 *                          const uint8* PhysAddrPtr
 *                      )
 *  Service ID[hex]   : 0x13
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant for the same CtrlIdx, reentrant for
 *                      different.
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      PhysAddrPtr. Pointer to memory containing the physical
 *                                   source address (MAC address) in network
 *                                   byte order
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Sets the physical source address used by the indexed
 *                      controller.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_SetPhysAddr(uint8 CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

/**
 *  \brief This function updates the physical source address to/from the indexed
 *         controller filter.
 *
 *  \verbatim
 *  Service name      : Eth_UpdatePhysAddrFilter
 *  Syntax            : Std_ReturnType Eth_UpdatePhysAddrFilter(
 *                          uint8 CtrlIdx,
 *                          uint8* PhysAddrPtr,
 *                          Eth_FilterActionType Action
 *                      )
 *  Service ID[hex]   : 0x12
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant for the same CtrlIdx, reentrant for
 *                      different
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      PhysAddrPtr. Pointer to memory containing the physical
 *                                   source address (MAC address) in network
 *                                   byte order.
 *                      Action. Add or remove the address from the Ethernet
 *                              controllers filter
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType
 *                        E_OK: filter was successfully changed
 *                        E_NOT_OK: filter could not be changed
 *  Description       : Updates the physical source address to/from the indexed
 *                      controller filter. If the Ethernet Controller is not
 *                      capable to do the filtering, the software has to do this.
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_UpdatePhysAddrFilter(uint8                CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr,
                         Eth_FilterActionType Action);

#if (STD_ON == ETH_ENABLE_MII_API)
/**
 *  \brief This function configures a transceiver register or triggers a
 *         function offered by the receiver Service.
 *
 *  \verbatim
 *  Service name      : Eth_WriteMii
 *  Syntax            : Std_ReturnType Eth_WriteMii(
 *                          uint8 CtrlIdx,
 *                          uint8 TrcvIdx,
 *                          uint8 RegIdx,
 *                          uint16 RegVal
 *                      )
 *  Service ID[hex]   : 0x05
 *  Sync/Async        : Asynchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      TrcvIdx. Index of the transceiver on the MII
 *                      RegIdx.Index of the transceiver register on the MII
 *                      RegVal. Value to be written into the indexed register
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType
 *                        E_OK: Service accepted
 *                        E_NOT_OK: Service denied
 *                        ETH_E_NO_ACCESS: Ethernet transceiver access failure
 *  Description       : Configures a transceiver register or triggers a function
 *                      offered by the receiver.
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_WriteMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);

/**
 *  \brief This function reads a transceiver register.
 *
 *  \verbatim
 *  Service name      : Eth_ReadMii
 *  Syntax            : Std_ReturnType Eth_ReadMii(
 *                          uint8 CtrlIdx,
 *                          uint8 TrcvIdx,
 *                          uint8 RegIdx,
 *                          uint16* RegValPtr
 *                      )
 *  Service ID[hex]   : 0x06
 *  Sync/Async        : Asynchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      TrcvIdx. Index of the transceiver on the MII
 *                      RegIdx. Index of the transceiver register on the MII
 *                      RegVal. Value to be written into the indexed register
 *  Parameters (inout): None
 *  Parameters (out)  : RegValPtr. Filled with the register content of the
 *                                 indexed register
 *  Return value      : Std_ReturnType
 *                        E_OK: Service accepted
 *                        E_NOT_OK: Service denied
 *                        ETH_E_NO_ACCESS: Ethernet transceiver access failure
 *  Description       : Reads a transceiver register.
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_ReadMii(uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr);
#endif /* (STD_ON == ETH_ENABLE_MII_API) */

#if (ETH_GET_DROPCOUNT_API == STD_ON)
/**
 *  \brief This function reads a list with counter values of the
 *         corresponding controller.
 *
 *  \verbatim
 *  Service name      : Eth_GetCounterValues
 *  Syntax            : Std_ReturnType Eth_GetCounterValues(uint8 CtrlIdx,
 *                                                Eth_CounterType* CounterPtr);
 *  Service ID[hex]   : 0x14
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (out)  : CounterPtr. counter values according to IETF RFC 1757,
 *                                 RFC 1643 and RFC 2233. Refer to the \ref
 *                                 Eth_CounterType.
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: drop counter could not be obtained
 *  Description       : Reads a list with drop counter values of the
 *                      corresponding controller.
 *                      The meaning of these values is described at
 *                      Eth_CounterType.
 *  \endverbatim
 */

FUNC(Std_ReturnType, ETH_CODE)
Eth_GetCounterValues(uint8 CtrlIdx, Eth_CounterType* CounterPtr);
#endif /* (STD_ON == ETH_GET_DROPCOUNT_API) */

#if (STD_ON == ETH_GETETHERSTATS_API)
/**
 *  \brief This function reads a list with RX statistics values of the
 *          corresponding controller.
 *
 *  \verbatim
 *  Service name      : Eth_GetRxStats
 *  Syntax            : Std_ReturnType Eth_GetRxStats(
 *                          uint8 CtrlIdx,
 *                          Eth_RxStatsType* RxStats
 *                     )
 *  Mode              : Supervisor Mode (Privileged Mode)
 *  Service ID[hex]   : 0x15
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (inout): None
 *  Parameters (out)  : RxStats. List of values according to IETF RFC 2819
 *                              (Remote Network Monitoring Management
 *                              Information Base).
 *                               Refer to the \ref Eth_RxStatsType.
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: drop counter could not be obtained
 *  Description       :
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetRxStats(uint8 CtrlIdx, P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats);
#endif /* (STD_ON == ETH_GETETHERSTATS_API) */

#if (STD_ON == ETH_GETTX_STATS_API)
/**
 *  \brief This function reads a list with TX statistics values of the
 *          corresponding controller.
 *
 *  \verbatim
 *  Service name      : Eth_GetTxStats
 *  Syntax            : Std_ReturnType Eth_GetTxStats(
 *                          uint8 CtrlIdx,
 *                          Eth_TxStatsType* TxStats
 *                      )
 *  Service ID[hex]   : 0x15
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (inout): None
 *  Parameters (out)  : TxStats. List of values according to IETF RFC 2819
 *                      (Remote Network Monitoring Management Information Base).
 *                      Refer to the \ref Eth_TxStatsType.
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: drop counter could not be obtained
 *  Description       :
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetTxStats(uint8 CtrlIdx, P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats);
#endif /* (STD_ON == ETH_GETTX_STATS_API) */

#if (ETH_GETTXERROR_COUNTERVALUES_API == STD_ON)
/**
 *  \brief This function reads a list of values to read statistic error counter
 *         values for transmission for corresponding controller.
 *
 *  \verbatim
 *  Service name      : Eth_GetTxErrorCounterValues
 *  Syntax            : Eth_GetTxErrorCounterValues(uint8 CtrlIdx,
 *                           Eth_TxErrorCounterValuesType *TxErrorCounterValues)
 *  Service ID[hex]   : 0x15
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (inout): None
 *  Parameters (out)  : TxErrorCounterValues. List of values to read statistic
 *                      error counter values for transmission.
 *                      Refer to the \ref Eth_TxErrorCounterValuesType.
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: drop counter could not be obtained
 *  Description       :
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetTxErrorCounterValues(uint8 CtrlIdx,
                            P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues);
#endif /*ETH_GETTXERROR_COUNTERVALUES_API==STD_ON*/

#if (STD_ON == ETH_GLOBALTIMESUPPORT_API)
/**
 *  \brief This function returns a time value out of the HW registers.
 *
 *  \verbatim
 *  Service name      : Eth_GetCurrentTime
 *  Syntax            : Std_ReturnType Eth_GetCurrentTime(
 *                          uint8 CtrlIdx,
 *                          Eth_TimeStampQualType *timeQualPtr,
 *                          Eth_TimeStampType *timeStampPtr
 *                      )
 *  Service ID[hex]   : 0x16
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (inout): None
 *  Parameters (out)  : timeQualPtr. Quality of HW time stamp, e.g. based on
 *                                   current drift
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: failed
 *  Description       : Returns a time value out of the HW registers according
 *                      to the capability of the HW. Is the HW resolution is
 *                      lower than the Eth_TimeStampType resolution resp. range,
 *                      than an the remaining bits will be filled with 0.
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_GetCurrentTime(uint8 CtrlIdx, P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                   P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);

/**
 *  \brief This function activates egress time stamping on a dedicated message
 *         object.
 *
 *  \verbatim
 *  Service name      : Eth_EnableEgressTimeStamp
 *  Syntax            : void Eth_EnableEgressTimeStamp(
 *                          uint8 CtrlIdx,
 *                          uint8 BufIdx
 *                      )
 *  Service ID[hex]   : 0x17
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      BufIdx. Index of the message buffer, where Application
 *                              expects egress time stamping
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Activates egress time stamping on a dedicated message
 *                      object.
 *                      Some HW does store once the egress time stamp marker and
 *                      some HW needs it always before transmission. There will
 *                      be no disable functionality, due to the fact, that the
 *                      message type is always "time stamped" by network design.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_EnableEgressTimeStamp(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_BufIdxType, AUTOMATIC) BufIdx);

/**
 *  \brief This function reads back the egress time stamp on a dedicated message
 *         object.
 *
 *  \verbatim
 *  Service name      : Eth_GetEgressTimeStamp
 *  Syntax            : void Eth_GetEgressTimeStamp(
 *                          uint8 CtrlIdx,
 *                          uint8 BufIdx,
 *                          Eth_TimeStampQualType* timeQualPtr,
 *                          Eth_TimeStampType *timeStampPtr
 *                          )
 *  Service ID[hex]   : 0x18
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      BufIdx. Index of the message buffer, where Application
 *                              expects egress time stamping
 *  Parameters (inout): timeQualPtr. Quality of HW time stamp, e.g. based on
 *                                   current drift
 *                      timeStampPtr. Current time stamp
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Reads back the egress time stamp on a dedicated message
 *                      object.
 *                      It must be called within the TxConfirmation() function.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_GetEgressTimeStamp(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_BufIdxType, AUTOMATIC) BufIdx,
                       P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                       P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);

/**
 *  \brief This function reads back the ingress time stamp on a dedicated
 *         message object.
 *
 *  \verbatim
 *  Service name      : Eth_GetIngressTimeStamp
 *  Syntax            : void Eth_GetIngressTimeStamp(
 *                          uint8 CtrlIdx,
 *                          Eth_DataType* DataPtr,
 *                          Eth_TimeStampQualType* timeQualPtr,
 *                          Eth_TimeStampType *timeStampPtr
 *                      )
 *  Service ID[hex]   : 0x19
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      DataPtr. Pointer to the message buffer, where Application
 *                               expects ingress time stamping
 *  Parameters (inout): timeQualPtr. Quality of HW time stamp, e.g. based on
 *                                   current drift
 *                      timeStampPtr. Current time stamp
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Reads back the ingress time stamp on a dedicated message
 *                      object.
 *                      It must be called within the RxIndication() function.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_GetIngressTimeStamp(VAR(uint8, AUTOMATIC) CtrlIdx, P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
                        P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,
                        P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr);
#endif /* STD_ON == ETH_GLOBALTIMESUPPORT_API*/

/**
 *  \brief This function provides access to a transmit buffer of the specified
 *         controller.
 *
 *  \verbatim
 *  Service name      : Eth_ProvideTxBuffer
 *  Syntax            : BufReq_ReturnType Eth_ProvideTxBuffer(
 *                          uint8 CtrlIdx,
 *                          uint8 Priority,
 *                          uint8* BufIdxPtr,
 *                          uint8** BufPtr,
 *                          uint16* LenBytePtr
 *                      )
 *  Service ID[hex]   : 0x09
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (in)   : Priority. Frame priority for transmit buffer FIFO
 *                                selection
 *  Parameters (inout): LenBytePtr
 *                        In: desired length in bytes,
 *                        out: granted length in bytes
 *  Parameters (out)  : BufIdxPtr. Index to the granted buffer resource.
 *                                 To be used for subsequent requests
 *                      BufPtr. Pointer to the granted buffer
 *  Return value      : BufReq_ReturnType
 *                        BUFREQ_OK: success
 *                        BUFREQ_E_NOT_OK: development error detected
 *                        BUFREQ_E_BUSY: all buffers in use
 *                        BUFREQ_E_OVFL: requested buffer too large
 *  Description       : Provides access to a transmit buffer of the specified
 *                      controller.
 *  \endverbatim
 */
FUNC(BufReq_ReturnType, ETH_CODE)
Eth_ProvideTxBuffer(uint8 CtrlIdx, uint8 Priority, P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DAT) BufIdxPtr,
                    P2VAR(uint8, AUTOMATIC, ETH_APPL_DAT) * BufPtr, P2VAR(uint16, AUTOMATIC, ETH_APPL_DAT) LenBytePtr);

/**
 *  \brief This function triggers transmission of a previously filled transmit
 *         buffer.
 *
 *  \verbatim
 *  Service name      : Eth_Transmit
 *  Syntax            : Std_ReturnType Eth_Transmit(
 *                          uint8 CtrlIdx,
 *                          uint8 BufIdx,
 *                          Eth_FrameType FrameType,
 *                          boolean TxConfirmation,
 *                          uint16 LenByte,
 *                          uint8 *PhysAddrPtr)
 *  Service ID[hex]   : 0xA
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *                      BufIdx. Index of the buffer resource
 *                      FrameType. Ethernet frame type
 *                      TxConfirmation. Activates transmission confirmation
 *                      LenByte. Data length in byte
 *                      PhysAddrPtr. Physical target address (MAC address) in
 *                                   network byte order
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : Std_ReturnType
 *                        E_OK: success
 *                        E_NOT_OK: transmission failed
 *  Description       : Triggers transmission of a previously filled transmit
 *                      buffer.
 *  \endverbatim
 */
FUNC(Std_ReturnType, ETH_CODE)
Eth_Transmit(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_BufIdxType, AUTOMATIC) BufIdx,
             VAR(Eth_FrameType, AUTOMATIC) FrameType, VAR(boolean, AUTOMATIC) TxConfirmation,
             VAR(uint16, AUTOMATIC) LenByte, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr);

/**
 *  \brief This function triggers frame reception.
 *
 *  \verbatim
 *  Service name      : Eth_Receive
 *  Syntax            : void Eth_Receive(
 *                          uint8 CtrlIdx,
 *                          uint8 FifoIdx,
 *                          Eth_RxStatusType* RxStatusPtr
 *                      )
 *  Service ID[hex]   : 0xB
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (in)   : FifoIdx. Specifies the related fifo
 *  Parameters (inout): None
 *  Parameters (out)  : RxStatusPtr. Indicates whether a frame has been received
 *                                   and if so, whether more frames are available
 *                                   or frames got lost
 *  Return value      : None
 *  Description       : Triggers frame reception.
 *  \endverbatim
 */

/*
 * Design: SITARA_MCU_MCAL-2242
 */
FUNC(void, ETH_CODE)
Eth_Receive(uint8 CtrlIdx, uint8 FifoIdx, P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DAT) RxStatusPtr);

/**
 *  \brief This function triggers frame transmission confirmation.
 *
 *  \verbatim
 *  Service name      : Eth_TxConfirmation
 *  Syntax            : void Eth_TxConfirmation(
 *                          uint8 CtrlIdx
 *                      )
 *  Service ID[hex]   : 0xC
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of
 *                               the Ethernet Driver
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : Triggers frame transmission confirmation.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_TxConfirmation(uint8 CtrlIdx);

#if (STD_ON == ETH_VERSION_INFO_API)
/**
 *  \brief Function returns the version information of this module.
 *
 *  \verbatim
 *  Service name      : Eth_GetVersionInfo
 *  Syntax            : void Eth_GetVersionInfo(
 *                          Std_VersionInfoType* versioninfo
 *                      )
 *  Service ID[hex]   : 0xD
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Reentrant
 *  Parameters (in)   : None
 *  Parameters (inout): None
 *  Parameters (out)  : VersionInfoPtr. Pointer to where to store the version
 *                      information of this module
 *  Return value      : None
 *  Description       : Returns the version information of this module.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfo);
#endif /* (STD_ON == ETH_VERSION_INFO_API) */

#if (STD_ON == ETH_TRAFFIC_SHAPING_API)
/**
 *  \brief This function set bandwidth for a specific transmitsion queue
 *
 *  \verbatim
 *  Service name      : Eth_SetBandwidthLimit
 *  Syntax            : FUNC(Std_ReturnType, ETH_CODE) Eth_SetBandwidthLimit(
 *                            uint8   CtrlIdx,
 *                            uint8   QueuePrio,
 *                            uint32  BandwidthLimit
 *                      );
 *  Mode              : User Mode (Non-Privileged Mode)
 *  Service ID[hex]   : 0x2C
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of the
 *                               Ethernet Driver
 *  Parameters (in)   : QueuePrio. Specifies the related fifo
 *                      BandwidthLimit. Bandwidth value
 *  Parameters (inout): None
 *  Parameters (out)  : None
 *  Return value      : None
 *  Description       : This function set bandwidth for a specific transmitsion queue.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_SetBandwidthLimit(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(uint8, AUTOMATIC) QueuePrio,
                      VAR(uint32, AUTOMATIC) BandwidthLimit);

/**
 *  \brief This function get bandwidth for a specific transmitsion queue
 *
 *  \verbatim
 *  Service name      : Eth_GetBandwidthLimit
 *  Syntax            : FUNC(Std_ReturnType, ETH_CODE) Eth_GetBandwidthLimit(
 *                          uint8              CtrlIdx,
 *                          uint8              QueuePrio,
 *                          P2VAR(uint32, AUTOMATIC, ETH_APPL_DAT)  BandwidthLimitPtr
 *                      );
 *  Mode              : User Mode (None-Privileged Mode)
 *  Service ID[hex]   : 0x2D
 *  Sync/Async        : Synchronous
 *  Reentrancy        : Non Reentrant
 *  Parameters (in)   : CtrlIdx. Index of the controller within the context of the
 *                               Ethernet Driver
 *  Parameters (in)   : QueuePrio. Specifies the related fifo
 *  Parameters (inout): BandwidthLimitPtr Pointer to where to store the currently configured
 * bandwidth limit (in [bit/s])
 *
 *  Return value      : None
 *  Description       : This function get bandwidth for a specific transmitsion queue.
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_GetBandwidthLimit(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(uint8, AUTOMATIC) QueuePrio,
                      P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) BandwidthLimitPtr);
#endif /* (STD_ON == ETH_TRAFFIC_SHAPING_API) */

/**
 *  \brief The function checks for controller errors and lost frames. Used for
 *         polling state changes. Calls EthIf_CtrlModeIndication when the
 *         controller mode changed.
 *
 *  \verbatim
 *  Service name      : Eth_MainFunction
 *  Syntax            : void Eth_MainFunction(
 *                          void
 *                      )
 *  Mode              : Supervisor Mode (Privileged Mode)
 *  Service ID[hex]   : 0x0A
 *  Description       : The function checks for controller errors and lost frames.
 *                      Used for polling state changes. Calls
 *                      EthIf_CtrlModeIndication when the controller mode
 *                      changed.
 *
 *  \endverbatim
 */
FUNC(void, ETH_CODE)
Eth_MainFunction(void);

#ifdef __cplusplus
}
#endif

#endif /* ETH_H */
/* @} */
