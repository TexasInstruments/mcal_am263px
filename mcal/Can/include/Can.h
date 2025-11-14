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
 *  \file     Can.h
 *
 *  \brief    This file contains interface header for CAN MCAL driver
 *
 */

/*
 * Below are the global requirements which are met by this CAN
 * driver which can't be mapped to a particular source ID
 */
/*
 *Design: MCAL-17095, MCAL-16976
 */

/*Requirements :SWS_Can_00079 , SWS_Can_00077, SWS_Can_00284, SWS_Can_00385,
 * SWS_Can_00386, SWS_Can_00427, SWS_Can_00401, SWS_Can_00402, SWS_Can_00403,
 * SWS_Can_00060, SWS_Can_00497, SWS_Can_00462, SWS_Can_00202, SWS_Can_00110,
 * SWS_Can_00234, SWS_Can_00022, SWS_Can_00024, SWS_Can_00220, SWS_Can_00221
 * SWS_Can_00487  MCAL-200, MCAL-207, MCAL-213, MCAL-237, MCAL-244, MCAL-225 */
#ifndef CAN_H_
#define CAN_H_

/**
 *  \defgroup CAN Can
 *  @{
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Requirements :SWS_Can_00034, SWS_Can_00435, SWS_Can_00436, SWS_Can_00388,
 * SWS_Can_00035, SWS_Can_00390, SWS_Can_00391, SWS_Can_00397, SWS_Can_00429,
 * SWS_Can_00417, SWS_Can_00416, SWS_Can_00415, SWS_Can_00413, SWS_Can_00222,
 * SWS_Can_00439
 */
/*
 *Design: MCAL-17104, MCAL-16942, MCAL-17131, MCAL-16887
 */
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"
#include "Can_Irq.h"
#include "Os.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name Can Driver Module SW Version Info
 *
 *  Defines for CAN Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define CAN_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define CAN_SW_MINOR_VERSION (2U)
/** \brief  Driver Implementation Patch Version */
#define CAN_SW_PATCH_VERSION (1U)
/** @} */

/**
 *  \name Can Driver Module AUTOSAR Version Info
 *
 *  Defines for CAN Driver AUTOSAR version used for compatibility checks
 *  @{
 */
/** \brief  AUTOSAR Major version specification implemented by CanDriver*/
#define CAN_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief  AUTOSAR Minor  version specification implemented by CanDriver */
#define CAN_AR_RELEASE_MINOR_VERSION (3U)
/** \brief  AUTOSAR Patch version specification implemented by CanDriver*/
#define CAN_AR_RELEASE_REVISION_VERSION (1U)
/** @} */

/* Global Macros */
/**
 *  \name Can Driver ID Info
 *  @{
 */
/** \brief  Texas Instruments Vendor ID*/
#define CAN_VENDOR_ID (44U)
/** \brief  Can Driver Module ID       */
#define CAN_MODULE_ID (80U)
/** \brief CAN Driver Instance ID */
#define CAN_INSTANCE_ID (0U)
/** @} */

/**
 *  \name CAN Driver states.
 *  @{
 */
/** \brief  CAN Driver is NOT initialized */
#define CAN_UNINIT ((uint8)0U)
/** \brief CAN Driver is initialized */
#define CAN_READY ((uint8)1U)
/** @} */

/**
 *  \name Can Driver Service Id
 *
 *  The Service Id is one of the argument to Det_ReportError function and is
 *  used to identify the source of the error
 *  @{
 */
/** \brief  Can_Init() */
#define CAN_INIT_ID (0x00U)
/** \brief  Can_MainFunction_Write()  */
#define CAN_MAINFCT_WRITE_ID (0x01U)
/** \brief  Can_SetControllerMode()  */
#define CAN_SETCTR_ID (0x03U)
/** \brief  Can_DisableControllerInterrupts() */
#define CAN_DIINT_ID (0x04U)
/** \brief  Can_EnableControllerInterrupts() */
#define CAN_ENINT_ID (0x05U)
/** \brief  Can_Write()  */
#define CAN_WRITE_ID (0x06U)
/** \brief  Can_GetVersionInfo() */
#define CAN_VERSION_ID (0x07U)
/** \brief  Can_MainFunction_Read() */
#define CAN_MAINFCT_READ_ID (0x08U)
/** \brief  Can_MainFunction_BusOff()  */
#define CAN_MAINFCT_BO_ID (0x09U)
/** \brief  Can_MainFunction_Wakeup() */
#define CAN_MAINFCT_WU_ID (0x0AU)
/** \brief  Can_CheckWakeup()         */
#define CAN_CKWAKEUP_ID (0x0BU)
/** \brief  Can_MainFunction_Mode()   */
#define CAN_MAINFCT_MODE_ID (0x0CU)
/** \brief  Can_SetBaudrate()         */
#define CAN_SETBAUDRATE_ID (0x0FU)
/** \brief  Can_DeInit()              */
#define CAN_DEINIT_ID (0x10U)
/** \brief  Can_GetControllerErrorState() */
#define CAN_GETCTRERRST_ID (0x11U)
/** \brief  Can_GetControllerMode() */
#define CAN_GETCTRMODE_ID (0x12U)
/** \brief  Can_RxProcess_Interrupt() */
#define CAN_RXPROCESS_ID_INTERRUPT (0x21U)
/** \brief  Can_RxProcess_Polling()   */
#define CAN_RXPROCESS_ID_POLLING (0x22U)
/** \brief Can_RegisterReadback() */
#define CAN_REGISTER_READBACK_ID (0x23U)
/** \brief  Can_TestLoopBackModeEnable() */
#define CAN_LOOPBACK_ENABLE_ID (0x14U)
/** \brief  Can_TestLoopBackModeDisable() */
#define CAN_LOOPBACK_DISABLE_ID (0x15U)
/** \brief Numerical value */
#define CAN_ZERO (0x00U)
/** @} */

/**
 *  \name Can Driver CallOut function id
 *
 *  The Service Id is one of the argument to Det_ReportError functiona and is
 *                     used to
 *  identify the source of the error
 *  @{
 */
/** \brief  CanIf_RxIndication callback */
#define CAN_RXINDI_ID (0x10U)
/** \brief  CanIf_TxConfirmation callback */
#define CAN_TXCNF_ID (0x11U)
/** \brief  Controller Wakeup indication callback */
#define CAN_CTRWAKEUP_ID (0x12U)
/** \brief  Controller Off indication callback */
#define CAN_CTRBUSOFF_ID (0x13U)
/** @} */
/**
 *  \name Can Error Codes
 *
 *  Error codes returned by Can functions
 *  @{
 */
#ifndef CAN_E_PARAM_POINTER
/** \brief  ERROR:NULL_PTR passed as parameter */
#define CAN_E_PARAM_POINTER (0x01U)
#endif
#ifndef CAN_E_PARAM_HANDLE
/** \brief  ERROR:Invalid Controller Handle */
#define CAN_E_PARAM_HANDLE (0x02U)
#endif
#ifndef CAN_E_PARAM_DATA_LENGTH
/** \brief  ERROR:Invalid length of msg */
#define CAN_E_PARAM_DATA_LENGTH (0x03U)
#endif
#ifndef CAN_E_PARAM_CONTROLLER
/** \brief  ERROR:Invalid controller id */
#define CAN_E_PARAM_CONTROLLER (0x04U)
#endif
#ifndef CAN_E_UNINIT
/** \brief  ERROR:Error due to API invoked without performing Can_Init() */
#define CAN_E_UNINIT (0x05U)
#endif
#ifndef CAN_E_TRANSITION
/** \brief  ERROR:Error during Controller state transition */
#define CAN_E_TRANSITION (0x06U)
#endif
#ifndef CAN_E_PARAM_BAUDRATE
/** \brief  ERROR:Invalid Baudrate configuration */
#define CAN_E_PARAM_BAUDRATE (0x07U)
#endif
#ifndef CAN_E_ICOM_CONFIG_INVALID
/** \brief  ERROR:Invalid config ID*/
#define CAN_E_ICOM_CONFIG_INVALID (0x08U)
#endif
#ifndef CAN_E_INIT_FAILED
/** \brief  ERROR:Timeout occured */
#define CAN_E_INIT_FAILED (0x09U)
#endif
#ifndef CAN_E_DATALOST
/** \brief  ERROR:Data lost/dropped . Runtime Error*/
#define CAN_E_DATALOST (0x01U)
#endif
/** @} */

/**
 *  \name CAN Config Ids
 *
 *  The Config Ids used for different
 *  CAN Configuration builds
 *  @{
 */
/** \brief Config 0 (All configurations ON) */
#define CAN_CFG_ID_0 (0x01U)
/** \brief Config 1 (All configurations OFF).
 *         CAN_CFG_ID_1 is used only for compile check */
#define CAN_CFG_ID_1 (0x02U)
/** \brief Config 2 (All configurations ON except DET OFF) */
#define CAN_CFG_ID_2 (0x04U)
/** \brief Config 3 (Configurator auto generated file) */
#define CAN_CFG_ID_3 (0x08U)
/** \brief Config 4 (Configurator auto generated file MCAN
 *                  with pre-compile variant ON) */
#define CAN_CFG_ID_4 (0x10U)
/** \brief Config 5 (All configurations ON but used only for testing
 *                   WakeUp by external HW event and Performance tests) */
#define CAN_CFG_ID_5 (0x20U)

/** \brief Config 6 (Used for MCAN Testing) */
#define CAN_CFG_ID_6 (0x40U)

/** \brief Config 7 (Used for MCAN Testing) */
#define CAN_CFG_ID_7 (0x50U)
/** @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Typedef for error notification function pointer */
typedef P2FUNC(void, CAN_APPL_CODE, Can_ErrNotifyType)(uint32 canErrorType);

/** \brief Can Mailbox direction enum */
typedef enum
{
    /** \brief Mailbox is for receive */
    CAN_MAILBOX_DIRECTION_RX = 0x0U,
    /** \brief Mailbox is for transmit */
    CAN_MAILBOX_DIRECTION_TX = 0x1U
} Can_MailBoxDirectionType;

/** \brief Can Handle Type enum */
typedef enum
{
    /** \brief For only one L-PDU (identifier) is handled by the hardware object */
    CAN_FULL = 0x0U,
    /** \brief For several L-PDUs are handled by the hardware object */
    CAN_BASIC = 0x1U
} Can_HandleType;

/** \brief Can Tx/Rx processing enum */
typedef enum
{
    /** \brief Interrupt Mode of operation */
    CAN_TX_RX_PROCESSING_INTERRUPT = 0x0U,
    /** \brief Mixed Mode of operation */
    CAN_TX_RX_PROCESSING_MIXED = 0x1U,
    /** \brief Polling Mode of operation */
    CAN_TX_RX_PROCESSING_POLLING = 0x2U
} Can_TxRxProcessingType;

/** \brief Can Controller Error Types */
typedef enum
{
    /** \brief Parity Error */
    CAN_ECC_ERROR_TYPE_PARITY = 0x0U,
    /** \brief Single Bit Error Detected and corrected */
    CAN_ECC_ERROR_TYPE_SEC = 0x1U,
    /** \brief Double Bit Error Detected */
    CAN_ECC_ERROR_TYPE_DED = 0x2U
} Can_ECCErrorType;

/** \brief Can Controller State enum type */
typedef uint8 CanControllerState_Type;

/** \brief Can Interrupt Mask type */
typedef uint32 Can_InterruptMask_Type;

/** \brief Structure defining the filter mask to be used  */
typedef struct Can_MaskStruct
{
    /** \brief Filter mask value. */
    uint32 MaskValue;
} Can_MaskType;

/** \brief Structure defining the HW filter to be used */
typedef struct Can_HwFilterStruct
{
    /** \brief ID value extended will have MSB set */
    Can_IdType IDValue;
    /** \brief Mask for the RX filtering */
    uint32     Mask;
} Can_HwFilterType;

/** \brief Structure defining the CAN FD data phase baud rate configuration */
typedef struct Can_FdBaudConfigStruct
{
    /** \brief In Kbps */
    uint16  Baud;
    /** \brief Prop Segement value */
    uint8   PropSeg;
    /** \brief Phase Segment 1 */
    uint8   Pseg1;
    /** \brief Phase Segment 2 */
    uint8   Pseg2;
    /** \brief Sync jump width */
    uint8   Sjw;
    /** \brief Sum of all timing parameters * */
    uint16  TimingValues;
    /** \brief Controller BRP value for Baud **/
    uint16  BrpValue;
    /** \brief Specifies the Transceiver Delay Compensation Offset in ns **/
    uint16  TrcvCompDelay;
    /** \brief Specifies if the bit rate switching shall be used for transmissions.**/
    boolean BrsSwitch;
} Can_FdBaudConfigType;

/** \brief Structure defining the CAN baud rate configuration */
typedef struct Can_BaudConfigStruct
{
    /** \brief In Kbps */
    uint16               Baud;
    /** \brief Prop Segement value */
    uint8                PropSeg;
    /** \brief Phase Segment 1 */
    uint8                Pseg1;
    /** \brief Phase Segment 2 */
    uint8                Pseg2;
    /** \brief Sync jump width */
    uint8                Sjw;
    /** \brief Sum of all timing parameters */
    uint16               TimingValues;
    /** \brief Controller BRP value for Baud */
    uint16               BrpValue;
    /** \brief List of available Data phase Baud rates for CAN FD */
    Can_FdBaudConfigType BaudFdRateConfig;
} Can_BaudConfigType;

/** \brief Can Controller Configuration definition */
typedef struct Can_ControllerStruct
{
    /** \brief pointer to default Baud structure */
    Can_BaudConfigType  *DefaultBaud;
    /** \brief List of available Baud rates */
    Can_BaudConfigType **BaudRateConfigList;
} Can_ControllerType;

/** \brief Can Controller Pre Compile Configuration definition */
typedef struct Can_ControllerStruct_PC
{
    /** \brief Id as provided by GUI **/
    uint8                  ControllerId;
    /** \brief Contoller is used=1 or not_used=0*/
    boolean                CntrActive;
    /** \brief Pointer to CanReg structure */
    uint32                 CntrAddr;
    /** \brief Automatic wakeup via bus activity */
    boolean                CanBusWakeupSupport;
    /** \brief Type can be Interrupt, Polling or Mixed */
    Can_TxRxProcessingType RxProcessingType;
    /** \brief Type can be Interrupt, Polling or Mixed */
    Can_TxRxProcessingType TxProcessingType;
    /** \brief TRUE = Interrupt FALSE = Polling */
    boolean                BusOffProcessingInterrupt;
    /** \brief TRUE = Interrupt FALSE = Polling */
    boolean                WakeupProcessingInterrupt;
    /** \brief TRUE = Disable Auto Retransmission */
    boolean                DisableAutoRetransmission;
    /** \brief Group end notification callback fxn pointer */
    Can_ErrNotifyType      Can_ErrorNotification;
    /** \brief Can Controller Instance **/
    Can_ControllerInstance CanControllerInst;
} Can_ControllerType_PC;

/** \brief Can mailbox configuration definition */
typedef struct Can_MailboxStruct
{
    /** \brief CanHandleType 0=Full, *1=Basic */
    uint8                        CanHandleType;
    /** \brief CanIdType 0=standard 1=Extended 2= Mixed */
    uint32                       MBIdType;
    /** \brief Mailbox - Hw object in the controller*/
    Can_HwHandleType             HwHandle;
    /** \brief Number of hardware objects used to implement one HOH*/
    uint16                       CanHwObjectCount;
    /** \brief CanObjectType - Direction of Mailbox @sa Can_MailBoxDirectionType */
    Can_MailBoxDirectionType     MBDir;
    /** \brief Reference to CAN Controller to which the HOH is associated to. */
    const Can_ControllerType_PC *Controller;
    /** \brief List of HW Filter */
    Can_HwFilterType           **HwFilterList;
    /** \brief HW Filter Count */
    uint32                       HwFilterCnt;
    /** \brief If PduInfo->SduLength does not match possible DLC values
     *   CanDrv will use the next higher valid DLC for transmission with
     *   initialization of unused bytes to the value of
     *   the corresponding CanFdPaddingValue.
     */
    uint8                        CanFdPaddingValue;
    /** \brief TRUE = Polling, FALSE = Interrupt */
    boolean                      CanHardwareObjectUsesPolling;
    /** \brief TRUE = Enable, FALSE = Disable */
    boolean                      CanTriggerTransmitEnable;
} Can_MailboxType;

/** \brief Can mailox Pre compile configuration definition */
typedef struct Can_MailboxStruct_PC
{
    /** \brief CanObjectId - Holds handle Id */
    uint16 CanObjectId;
} Can_MailboxType_PC;
/** \brief Can MCAL root configuration structure. */
/*
 *Design: MCAL-16886
 */
typedef struct Can_ConfigType_s
{
    /** \brief List of enabled Controllers */
    Can_ControllerType **CanControllerList;
    /** \brief MaxCount of Controller in Controller List */
    uint8                CanMaxControllerCount;
    /** \brief MB array for all controllers */
    Can_MailboxType    **MailBoxList;
    /** \brief MaxMbCount in MB list in all controller */
    uint32               MaxMbCnt;
    /** \brief Max Baud Config Index in BaudRateConfigList in all controller */
    uint32               MaxBaudConfigID[CAN_NUM_CONTROLLER];
} Can_ConfigType;

#if (STD_ON == CAN_REGISTER_READBACK_API)
/**
 * \brief  Register Readback Structure
 * The Safety API to readback CAN register vales will populate this structure
 */
typedef struct
{
    /** \brief MCANSS PID Register  */
    uint32 CanReadBackRegPID;
    /** \brief MCANSS STAT Register  */
    uint32 CanReadBackRegSTAT;
    /** \brief Auto Bus On Time Register  */
    uint32 CanReadBackRegCREL;
    /** \brief Endianess MCAN_TEST value Constant "0x8765 4321" */
    uint32 CanReadBackRegENDN;
    /** \brief MCAN CTRL Register */
    uint32 CanReadBackRegCTRL;
    /** \brief MCAN DBTB Register */
    uint32 CanReadBackRegDBTP;
    /** \brief MCAN RWD Register */
    uint32 CanReadBackRegRWD;
    /** \brief MCAN CCCR Register */
    uint32 CanReadBackRegCCCR;
    /** \brief MCAN NBTP Register */
    uint32 CanReadBackRegNBTP;
    /** \brief MCAN TDCR Register */
    uint32 CanReadBackRegTDCR;
    /** \brief MCAN GFC Register */
    uint32 CanReadBackRegGFC;
    /** \brief MCAN SIDFC Register */
    uint32 CanReadBackRegSIDFC;
    /** \brief MCAN XIDFC Register */
    uint32 CanReadBackRegXIDFC;
    /** \brief MCAN RXF0C Register */
    uint32 CanReadBackRegRXF0C;
    /** \brief MCAN RXBC Register */
    uint32 CanReadBackRegRXBC;
    /** \brief MCAN RXF1C Register */
    uint32 CanReadBackRegRXF1C;
    /** \brief MCAN TXBC Register */
    uint32 CanReadBackRegTXBC;
    /** \brief MCAN TXESC Register */
    uint32 CanReadBackRegTXESC;
    /** \brief MCAN TXEFC Register */
    uint32 CanReadBackRegTXEFC;
} Can_RegisterReadbackType;
#endif /* (STD_ON == CAN_REGISTER_READBACK_API) */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief Function returns the version information of this module.
 *
 * Service ID[hex]   : 0x07
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[out] versioninfo Pointer to where to store the version information of this module.
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (CAN_VERSION_INFO_API == STD_ON)
FUNC(void, CAN_CODE)
Can_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_APPL_DATA) Can_VersionInfo);
#endif

/** \brief This function initializes the module.
 * All the required initialization for the CAN driver and hardware is performed in this function.
 *
 * Service ID[hex]   : 0x00
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] CfgPtr Pointer to driver configuration.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_PBCFG) CfgPtr);

/** \brief This function performs software triggered state transitions of the CAN
 *          controller State machine.
 *
 * Service ID[hex]   : 0x03
 *
 * Sync/Async        : Asynchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Controller - CAN controller for which the status shall be changed
 * \param[in] Transition - Transition value to request new CAN controller state
 * \return Std_ReturnType
 * \retval E_OK: request accepted
 * \retval E_NOT_OK: request not accepted, a development error occurred
 *
 *****************************************************************************/
/*
 *Design: MCAL-16873
 */
FUNC(Std_ReturnType, CAN_CODE)
Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition);

/** \brief This function is called by CanIf to pass a CAN message to CanDrv for transmission.
 *
 * Service ID[hex]   : 0x06
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant (thread-safe)
 *
 * \param[in] Hth - Information which HW-transmit handle shall be used for
 *                  transmit. Implicitly this is also the information about
 *                  the controller to use because the Hth numbers are unique
 *                  inside one hardware unit.
 * \param[in] PduInfo - Pointer to SDU user memory, DLC and Identifier.
 * \return Std_ReturnType
 * \retval E_OK: Write command has been accepted
 * \retval E_NOT_OK: development error occurred
 * \retval CAN_BUSY: No TX hardware buffer available or pre-emptive call
 *                     of Can_Write that can't be implemented re-entrant
 *
 *****************************************************************************/
/*
 *Design: MCAL-17125
 */
FUNC(Std_ReturnType, CAN_CODE) Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);
#if (CAN_WAKEUP_FUNCTIONALITY_API == STD_ON)

/** \brief This function checks if a wakeup has occurred for the given controller.
 *
 * Service ID[hex]   : 0x0b
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non Reentrant
 *
 * \param[in] Controller - Controller to be checked for a wakeup.
 * \return Std_ReturnType
 * \retval E_OK: if wakeup is detected.
 * \retval E_NOT_OK: if Wakeup is not detected
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CAN_CODE) Can_CheckWakeup(uint8 Controller);
#endif

/** \brief This function disables all interrupts for this CAN controller
 * Basically it will Disable the CAN interrupts(reset bit 1 in CTL reg(IE0=0)).
 *
 * Service ID[hex]   : 0x04
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_DisableControllerInterrupts(uint8 Controller);

/** \brief This function will Enable the interrupts for the Controller
 * desired. It will restore the interrupts that were defined in the configuration.
 * Basically it will enable the CAN interrupts.
 *
 * Service ID[hex]   : 0x05
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] Controller - CAN controller for which interrupts shall be enabled.
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_EnableControllerInterrupts(uint8 Controller);

/* polling functions (always available for non polled systems also)*/

/** \brief This function performs the polling of TX confirmation when
 *                     CAN_TX_PROCESSING is set to POLLING.
 *
 * Service ID[hex]   : 0x01
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_MainFunction_Write(void);

/** \brief This function performs the polling of bus-off events that are
 *                     configured statically as 'to be polled'
 *
 * Service ID[hex]   : 0x09
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_MainFunction_BusOff(void);

/** \brief This function performs the polling of RX indications when
 *                     CAN_RX_PROCESSING is set to POLLING
 *
 * Service ID[hex]   : 0x08
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_MainFunction_Read(void);

/** \brief This function performs the polling of wake-up events that are
 *                     configured statically as 'to be polled
 *
 * Service ID[hex]   : 0x0A
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_MainFunction_Wakeup(void);

/** \brief This function performs the polling of CAN controller mode transitions
 * This will indicate only the CanController SW state and cannot
 * indicate any HW state as there is no HW state exposed from the Can Controller.
 *
 * Service ID[hex]   : 0x0C
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_MainFunction_Mode(void);

#if (CAN_LOOPBACK_ENABLE == STD_ON)
/** \brief This service will enable CAN loopback mode.
 *
 * Service ID[hex]   : 0x0f
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] Controller - CAN Controller to enable loopback mode
 * \param[in] Loopback mode - # 0 - Digital Loopback, # 1 - Analog  Loopback
 * \return Std_ReturnType
 * \retval E_OK: Loopback mode enabled in the CAN Controller
 * \retval E_NOT_OK: Loopback mode enable failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CAN_CODE) Can_TestLoopBackModeEnable(uint8 controller, uint8 mode);

/** \brief This service will disable CAN loopback mode.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] Controller - CAN Controller to disable loopback mode
 * \param[in] Loopback mode - # 0 - Digital Loopback, # 1 - Analog  Loopback
 * \return Std_ReturnType
 * \retval E_OK: Loopback mode disabled in the CAN Controller
 * \retval E_NOT_OK: Loopback mode disable failed
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CAN_CODE) Can_TestLoopBackModeDisable(uint8 controller, uint8 mode);
#endif

#if defined(CAN_CONTROLLER_MCAN0)

/** \brief This function is the ISR for CAN controller 0/INT 0
 * This function should be invoked either by OS Interrupt frame handler
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 0. All the
 * Interrupts are hooked to MCAN0INT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the received message.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_0_Int0ISR_Fun(void);

/** \brief This function is the ISR for CAN controller 0/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 0 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_0_Int1ISR_Fun(void);
#endif

#if defined(CAN_CONTROLLER_MCAN1)

/** \brief This function is the ISR for CAN controller 1/INT 0 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 1. All the
 * Interrupts are hooked to MCAN1INT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the received message.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_1_Int0ISR_Fun(void);

/** \brief This function is the ISR for CAN controller 1/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 1 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_1_Int1ISR_Fun(void);
#endif

#if defined(CAN_CONTROLLER_MCAN2)

/** \brief This function is the ISR for CAN controller 2/INT 0 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 2. All the
 * Interrupts are hooked to MCAN2INT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the received message.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_2_Int0ISR_Fun(void);

/* #if (STD_ON == CAN_ECC_ENABLE) */

/** \brief This function is the ISR for CAN controller 2/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 2 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_2_Int1ISR_Fun(void);
/* #endif */
#endif

#if defined(CAN_CONTROLLER_MCAN3)

/** \brief This function is the ISR for CAN controller 3/INT 0 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 3. All the
 * Interrupts are hooked to MCAN3INT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the received message.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_3_Int0ISR_Fun(void);

/* #if (STD_ON == CAN_ECC_ENABLE) */

/** \brief This function is the ISR for CAN controller 3/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 4 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_3_Int1ISR_Fun(void);
/* #endif */
#endif
#if defined(CAN_CONTROLLER_MCAN4)

/** \brief This function is the ISR for CAN controller 4/INT 0 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 4. All the
 * Interrupts are hooked to MCAN4NT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the received message.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_4_Int0ISR_Fun(void);

/* #if (STD_ON == CAN_ECC_ENABLE) */

/** \brief This function is the ISR for CAN controller 4/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 4 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_4_Int1ISR_Fun(void);
/* #endif */
#endif
#if defined(CAN_CONTROLLER_MCAN5)

/** \brief This function is the ISR for CAN controller 5/INT 0 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 5. All the
 * Interrupts are hooked to MCAN5INT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the received message.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_5_Int0ISR_Fun(void);

/* #if (STD_ON == CAN_ECC_ENABLE) */

/** \brief This function is the ISR for CAN controller 5/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 5 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_5_Int1ISR_Fun(void);
/* #endif */
#endif
#if defined(CAN_CONTROLLER_MCAN6)

/** \brief This function is the ISR for CAN controller 6/INT 0 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 6. All the
 * Interrupts are hooked to MCAN6INT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the received message.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_6_Int0ISR_Fun(void);

/* #if (STD_ON == CAN_ECC_ENABLE) */

/** \brief This function is the ISR for CAN controller 6/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 6 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_6_Int1ISR_Fun(void);
/* #endif */
#endif
#if defined(CAN_CONTROLLER_MCAN7)

/** \brief This function is the ISR for CAN controller 7/INT 0 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 7. All the
 * Interrupts are hooked to MCAN7INT.
 * This ISR sends the TX confirmation for the successful tx msg.
 * This ISR will call the RX processing function for the receivedmessage.
 * This ISR will call the Error processing function in case of any error interrupts.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_7_Int0ISR_Fun(void);

/* #if (STD_ON == CAN_ECC_ENABLE) */

/** \brief This function is the ISR for CAN controller 7/INT 1 <br>
 * This function should be invoked either by OS Interrupt frame handler <br>
 * CAN Interrupt frame handler for Category 1 ISR
 *
 * This is the ISR function for the MCAN controller 7 ECC Error.
 * This ISR will clear and report the ECC Error through call back function.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_7_Int1ISR_Fun(void);
/* #endif */
#endif

/** \brief This function Sets Can controller baud rate selected by BaudRateConfigID
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] Controller - Controller whose Baud Rate is being set
 * \param[in] BaudRateConfigID - ID number corresponding to a Baud Rate Configuration
 * \return Std_ReturnType
 * \retval E_OK: Service request accepted, setting of (new) baud rate started
 * \retval E_NOT_OK: Service request not accepted
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CAN_CODE) Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);

#if (STD_ON == CAN_REGISTER_READBACK_API)

/** \brief This service will readback CAN registers
 * This is the function for checking the configuration registers.
 * This API can be called by higher layers to check if configuration is correct
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Reentrant
 *
 * \param[in] Controller - CAN Controller to readback registers
 * \param[in,out] RegRbPtr - Pointer to where to store the readback values.
 *                           If this pointer is NULL_PTR, then the API will return E_NOT_OK.
 * \return Std_ReturnType
 * \retval E_OK: Register readback successful
 * \retval E_NOT_OK: Register readback failed
 *
 *****************************************************************************/
Std_ReturnType Can_RegisterReadback(VAR(uint8, AUTOMATIC) Controller,
                                    P2VAR(Can_RegisterReadbackType, AUTOMATIC, CAN_APPL_DATA) RegRbPtr);
#endif

#if (STD_ON == CAN_ECC_ENABLE)

/** \brief This function Enables/Disables Parity
 * This function used to test ECC/Parity error.
 * ramInitEnable should be set to TRUE if ECC enabled for normal operations
 * otherwise pass false if it is diagnostic purpose.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] Controller - Controller Id
 * \param[in] flag - Enable/Disable Parity
 * \param[in] ramInitEnable - Enable/Disable Ram Init
 * \return Std_ReturnType
 * \retval E_OK: Parity enabled
 * \retval E_NOT_OK: Parity enable failed
 *
 *****************************************************************************/
Std_ReturnType Can_EccParityEnable(VAR(uint8, AUTOMATIC) controller, uint8 flag, uint8 ramInitEnable);

/** \brief This function returns corrupted mailbox number
 * This function returns mailbox number whose RAM is Corrupted
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] controller - Controller Id
 * \param[in,out] msgBox - Message number which caused ECC error.
 * \return Std_ReturnType
 * \retval E_OK: Request successful
 * \retval E_NOT_OK: Request failed
 *
 *****************************************************************************/
Std_ReturnType Can_EccDiagnosticGetErrMsgBoxNum(VAR(uint8, AUTOMATIC) controller, uint8 *msgBox);

/** \brief This function Sets ECC diagnostic mode
 * This function used to test Single bit ECC correction
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] controller - Controller Id
 * \param[in] flag - Enable/Disable Parity
 * \return Std_ReturnType
 * \retval E_OK: ECC diagnostic mode enabled
 * \retval E_NOT_OK: ECC diagnostic mode failed
 *
 *****************************************************************************/
Std_ReturnType Can_EccDiagnosticModeEnable(VAR(uint8, AUTOMATIC) controller, uint8 flag);

/** \brief This API will read the ECC error status information of MCAN controller
 * This function used to test Double bit error detection
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] controller - Controller Id
 * \param[in,out] ecccErrStatus - ECC error status
 * \return Std_ReturnType
 * \retval E_OK: Get ECC error status successful
 * \retval E_NOT_OK: Get ECC error status failed
 *
 *****************************************************************************/
Std_ReturnType Can_EccGetErrStatus(uint8 controller, uint32 *ecccErrStatus);

/** \brief This API clears the ECC error status register
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] controller - Controller Id
 * \return Std_ReturnType
 * \retval E_OK: Clear ECC error status successful
 * \retval E_NOT_OK: Clear ECC error status failed
 *
 *****************************************************************************/
Std_ReturnType Can_EccClrErrStatus(uint8 controller);
#endif /* (STD_ON == CAN_ECC_ENABLE) */

#if (CAN_DEINIT_API == STD_ON)

/** \brief This service is only used for UT testing and not for app use.
 * This API is not standard AUTOSAR API. This service sets the internal Can Controller state to
 * UNINIT state so that Can_Init can be invoked again.
 * This is required for UT test cases with diff Config.
 *
 * Service ID[hex]   : N/A
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] None
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CAN_CODE) Can_DeInit(void);

#endif /* (STD_ON == CAN_DEINIT_API) */

/** \brief This function get the error state of the controller.
 *
 * Service ID[hex]   : 0x11
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] ControllerId - ID of the CAN controller whose error state is requested.
 * \param[out] ErrorStatePtr - Pointer where the error state is updated.
 * \return Std_ReturnType
 * \retval E_OK: Error state request accepted
 * \retval E_NOT_OK: Error state request not accepted
 *
 *****************************************************************************/
/*
 *Design: MCAL-17027
 */
FUNC(Std_ReturnType, CAN_CODE)
Can_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr);

/** \brief This service reports about the current status of the requested CAN controller.
 *
 * Service ID[hex]   : 0x12
 *
 * Sync/Async        : Synchronous
 *
 * Reentrancy        : Non-Reentrant
 *
 * \param[in] Controller - CAN controller for which the status shall be changed
 * \param[out] ControllerModePtr - Pointer to a memory location where the current mode
 *                                 of the CAN controller will be stored.
 * \return Std_ReturnType
 * \retval E_OK: request accepted
 * \retval E_NOT_OK: request not accepted
 *
 *****************************************************************************/
/*
 *Design: MCAL-16873
 */
FUNC(Std_ReturnType, CAN_CODE)
Can_GetControllerMode(uint8 Controller, Can_ControllerStateType *ControllerModePtr);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* CAN_H_ end file*/
/*  End of File: Can.h */
