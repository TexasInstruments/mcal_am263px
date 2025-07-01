/*
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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
 *  \file     Cdd_I2c.h
 *
 *  \brief    This file contains interface header for CDD I2C driver
 *
 */

#ifndef CDD_I2C_H
#define CDD_I2C_H

/**
 * \defgroup CDD_I2C I2c API GUIDE Header file
 * @{
 */

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#include "Platform_Types.h"
#include "Std_Types.h"
#include "Cdd_I2c_Cfg.h"
#include "SchM_Cdd_I2c.h"
#include "sys_common.h"

/* ================================================================ */
/*                           Macros                                 */
/* ================================================================ */

/**
 *  \name CDD_I2C Driver Module SW Version Info
 *
 *  Defines for CDD_I2C Driver version used for compatibility checks
 *  @{
 */
/** \brief Driver Implementation Major Version */
#define CDD_I2C_SW_MAJOR_VERSION (10U)
/** \brief Driver Implementation Minor Version */
#define CDD_I2C_SW_MINOR_VERSION (1U)
/** \brief Driver Implementation Patch Version */
#define CDD_I2C_SW_PATCH_VERSION (0U)
/**   @} */

/**
 *  \name CDD_I2C Driver Module AUTOSAR Version Info
 *
 *  Defines for CDD_I2C Driver AUTOSAR version used for compatibility
 *   checks
 *  @{
 */
/** \brief AUTOSAR Major version specification implemented by CDD_I2C Driver */
#define CDD_I2C_AR_RELEASE_MAJOR_VERSION (4U)
/** \brief AUTOSAR Minor  version specification implemented by CDD_I2C Driver */
#define CDD_I2C_AR_RELEASE_MINOR_VERSION (3U)
/** \brief AUTOSAR Patch version specification implemented by CDD_I2C Driver */
#define CDD_I2C_AR_RELEASE_REVISION_VERSION (1U)
/**   @} */

/**
 *  \name CDD_I2C Driver ID Info
 *  @{
 */
/** \brief Texas Instruments Vendor ID */
#define CDD_I2C_VENDOR_ID ((uint16)44U)
/** \brief CDD_I2C Driver Module ID */
#define CDD_I2C_MODULE_ID ((uint16)255U)
/** \brief CDD_I2C Driver Instance ID */
#define CDD_I2C_INSTANCE_ID ((uint8)0U)
/**   @} */
/**
 *  \name CDD_I2C ISR category level
 *
 *  Defines for CDD_I2C Driver ISR ISR category level
 *  @{
 */
/** \brief void ISR type */
#define CDD_I2C_ISR_VOID (0x00U)
/** \brief Category 1 ISR type */
#define CDD_I2C_ISR_CAT1 (0x01U)
/** \brief Category 2 ISR type */
#define CDD_I2C_ISR_CAT2 (0x02U)
/**   @} */
/** \brief Maximum possible 10 bit address including read/write bit*/
#define CDD_I2C_10_MAX_BIT_ADDRESS ((uint16)2047U)

/**
 *  \name CDD_I2C Service Ids
 *
 *  The Service Id is one of the argument to Det_ReportError function
 and is used to identify the source of the error
 *  @{
 */
/** \brief Service ID Cdd_I2c_Init() */
#define CDD_I2C_SID_INIT (0x00u)
/** \brief  Service ID Cdd_I2c_DeInit() */
#define CDD_I2C_SID_DEINIT (0x01u)
/** \brief Service ID Cdd_I2c_GetVersionInfo() */
#define CDD_I2C_SID_GET_VERSION_INFO (0x02u)
/** \brief Service ID Cdd_I2c_SetupEB() */
#define CDD_I2C_SID_SETUP_EB (0x03u)
/** \brief Service ID Cdd_I2c_SetupDynamicEB() */
#define CDD_I2C_SID_SETUP_EB_DYNAMIC (0x04u)
/** \brief Service ID Cdd_I2c_AsyncTransmit() */
#define CDD_I2C_SID_ASYNC_TRANSMIT (0x05u)
/** \brief Service ID Cdd_I2c_Cancel() */
#define CDD_I2C_SID_CANCEL (0x06u)
/** \brief Service ID Cdd_I2c_GetResult() */
#define CDD_I2C_SID_GET_RESULT (0x07u)
/** \brief Service ID Cdd_I2c_GetSequenceResult() */
#define CDD_I2C_SID_GET_SEQUENCE_RESULT (0x08u)
/** \brief Service ID Cdd_I2c_MainFunction() */
#define CDD_I2C_SID_MAIN_FUNCTION (0x09u)
/** \brief Service ID Cdd_I2c_PollingModeProcessing() */
#define CDD_I2C_SID_POLLING_MODE_PROCESSING (0x0Au)
/** \brief Service ID Cdd_I2c_SetHandling() */
#define CDD_I2C_SID_SET_HANDLING (0x0Bu)
/** \brief Service ID Cdd_I2c_RegisterReadBack() */
#define CDD_I2C_SID_REGISTERREADBACK (0x0Cu)
/**   @} */

/*
 *Design: MCAL-14877, MCAL-14878, MCAL-14879, MCAL-14880
 */
/**
 *  \name CDD_I2C Error Codes
 *
 *  Error codes returned by CDD_I2C functions
 *  @{
 */
/** \brief No errors*/
#define CDD_I2C_E_NO_ERROR (0x00u)
/** \brief Error code for not initialized module*/
#define CDD_I2C_E_UNINIT (0x01u)
/** \brief  Init service called twice without DeInit*/
#define CDD_I2C_E_ALREADY_INITIALIZED (0x02u)
/** \brief Driver is busy*/
#define CDD_I2C_E_BUSY (0x03u)
/** \brief Channel out of bounds, exceeds the
 * maximum number of configured channels*/
#define CDD_I2C_E_PARAM_CHANNEL (0x04u)
/** \brief Sequence out of bounds, exceeds the
 * maximum number of configured sequences*/
#define CDD_I2C_E_PARAM_SEQUENCE (0x05u)
/** \brief Length out of bounds – a zero length
 * is not accepted. The total length is
 * limited to 65535*/
#define CDD_I2C_E_PARAM_LENGTH (0x06u)
/** \brief An invalid version info pointer has
 * been passed (a NULL_PTR)*/
#define CDD_I2C_E_PARAM_VINFO_PTR (0x07u)
/** \brief An invalid configuration has been
 * passed (a non NULL_PTR)*/
#define CDD_I2C_E_PARAM_CONFIG (0x08u)
/** \brief Two in-valid transmission buffers have
 * been passed (no NULL_PTR/ or both NULL_PTR)*/
#define CDD_I2C_E_PARAM_TRANS_BUFFER (0x09u)
/** \brief Address out of bounds, exceeds the
 * limit of the configured address range*/
#define CDD_I2C_E_PARAM_ADDRESS (0x0Au)
/** \brief Buffer direction conflicts with channel
 * direction set via EB*/
#define CDD_I2C_E_PARAM_DIRECTION (0x0Bu)
/** \brief Notify callback functions passed as
 * NULL_PTR*/
#define CDD_I2C_E_PARAM_NOTIFY_CALLBACK (0x0Cu)
/** \brief Bus error encountered during transmission
 * or reception*/
#define CDD_I2C_E_PARAM_TRANSMISSION_ERROR (0x0Du)
/** \brief Queue full*/
#define CDD_I2C_E_PARAM_QUEUE_FULL (0x0Eu)
/** \brief Timeout error*/
#define CDD_I2C_E_PARAM_TIMEOUT (0x0Fu)
/** \brief Hardware unit busy*/
#define CDD_I2C_E_HW_UNIT_BUSY (0x10u)
/** \brief Channel unit busy*/
#define CDD_I2C_E_CHANNEL_BUSY (0x11u)
/** \brief ARBITRATION_LOSS*/
#define CDD_I2C_E_ARBITRATION_LOSS (0x12u)
/** \brief NACK*/
#define CDD_I2C_E_NACK (0x13u)
/** \brief Receive shift register full*/
#define CDD_I2C_E_RECEIVE_SHIFT_REGISTER_FULL (0x14u)

/** \brief API servcie called with invalid data buffer pointer. */
#define CDD_I2C_E_PARAM_POINTER (0x15u)
/**   @} */

/** \brief CDD_I2C mask value for write action */
#define CDD_I2C_WRITE (0x00u)

/** \brief CDD_I2C mask value for read action */
#define CDD_I2C_READ (0x01u)

/**
 *  \name Mask values to clear, enable, disable or set
 * I2c specific interrupts
 *
 *  @{
 */
/** \brief Mask value for Arbitration lost  */
#define CDD_I2C_INT_ARBITRATION_LOST (0x01u)
/** \brief Mask value for No Acknowledgment  */
#define CDD_I2C_INT_NO_ACK (0x02u)
/** \brief Mask value for Address ready  */
#define CDD_I2C_INT_ADRR_READY_ACESS (0x04u)
/** \brief Mask value for Receive ready  */
#define CDD_I2C_INT_RECV_READY (0x08u)
/** \brief Mask value for Transmit Ready  */
#define CDD_I2C_INT_TRANSMIT_READY (0x10u)
/** \brief Mask value for Stop condition  */
#define CDD_I2C_INT_STOP_CONDITION (0x20u)
/** \brief Mask value for Zero Address  */
#define CDD_I2C_INT_ADRR_ZERO (0x100u)
/** \brief Mask value for Slave address  */
#define CDD_I2C_INT_ADRR_SLAVE (0x200u)
/** \brief Mask value for transmit under flow  */
#define CDD_I2C_INT_TRANSMIT_UNDER_FLOW (0x400u)
/** \brief Mask value for receive Over run  */
#define CDD_I2C_INT_RECV_OVER_RUN (0x800u)
/** \brief Mask value for bus busy  */
#define CDD_I2C_INT_BUS_BUSY (0x1000u)
/** \brief Mask value for No acknowledgment sent  */
#define CDD_I2C_INT_NO_ACK_SENT (0x2000u)
/** \brief Mask value for slave direction  */
#define CDD_I2C_INT_SLAVE_DIRECTION (0x4000u)
/** \brief Mask value to set all interrupts  */
#define CDD_I2C_ALL_INTERRUPTS                                                                \
    ((CDD_I2C_INT_ARBITRATION_LOST) | (CDD_I2C_INT_NO_ACK) | (CDD_I2C_INT_ADRR_READY_ACESS) | \
     (CDD_I2C_INT_RECV_READY) | (CDD_I2C_INT_TRANSMIT_READY) | (CDD_I2C_INT_STOP_CONDITION) | \
     (CDD_I2C_INT_ADRR_ZERO) | (CDD_I2C_INT_ADRR_SLAVE) | (CDD_I2C_INT_TRANSMIT_UNDER_FLOW) | \
     (CDD_I2C_INT_RECV_OVER_RUN) | (CDD_I2C_INT_BUS_BUSY) | (CDD_I2C_INT_NO_ACK_SENT) | (CDD_I2C_INT_SLAVE_DIRECTION))
/** \brief Mask value to clear all interrupts  */
#define CDD_I2C_ALL_INTERRUPTS_CLEAR                                                          \
    ((CDD_I2C_INT_ARBITRATION_LOST) | (CDD_I2C_INT_NO_ACK) | (CDD_I2C_INT_ADRR_READY_ACESS) | \
     (CDD_I2C_INT_RECV_READY) | (CDD_I2C_INT_STOP_CONDITION) | (CDD_I2C_INT_NO_ACK_SENT) |    \
     (CDD_I2C_INT_SLAVE_DIRECTION))
/**   @} */
/**
 *  \name Control register mask values
 *
 *  @{
 */
/** \brief Control Register mask value   */
#define CDD_I2C_OUT_OF_RESET (0x20u)
/** \brief Control Register mask value   */
#define CDD_I2C_MASTER_MODE (0x400u)
/** \brief Control Register mask value   */
#define CDD_I2C_FREE_RUN (0x4000u)
/**   @} */
/**
 *  \name System clock source frequencies
 *
 *  @{
 */
/** \brief 96MHz clock source frequency   */
#define CDD_I2C_MODULE_FUNC_CLK_96MHZ (96000000U)
/** \brief 200MHz clock source frequency   */
#define CDD_I2C_MODULE_FUNC_CLK_200MHZ (200000000U)
/**   @} */

/**
 *  \name I2C hardware unit frequencies
 *
 *  @{
 */
/** \brief 4MHz freq   */
#define CDD_I2C_MODULE_INTERNAL_CLK_4MHZ (4000000U)
/** \brief 12MHz freq   */
#define CDD_I2C_MODULE_INTERNAL_CLK_12MHZ (12000000U)
/**   @} */

/**
 *  \name I2C Status macros
 *
 *  @{
 */
/** \brief I2c status OK   */
#define CDD_I2C_OK (E_OK)
/** \brief I2c status Not Ok   */
#define CDD_I2C_NOT_OK (E_NOT_OK)
/**   @} */

/**
 * \name I2C Bus Status macros
 *
 *  @{
 */
/** \brief I2c bus free  */
#define CDD_I2C_BUS_FREE (0x03U)
/** \brief I2c bus busy  */
#define CDD_I2C_BUS_BUSY (0x04U)
/**   @} */

/**
 *  \name I2C Address scheme macros
 *
 *  @{
 */
/** \brief 7 bit address */
#define CDD_I2C_7_BIT_ADDRESS (0x00)
/** \brief 10 bit address */
#define CDD_I2C_10_BIT_ADDRESS (0x01)
/**   @} */

/**
 * \brief I2C Extended Address
 */
#define CDD_I2C_EXTENDED_ADDRESS_7F (0x7FU)

/**
 *  \name Baud rate macros
 *
 *  @{
 */
/** \brief 3.4MHz Baud rate */
#define CDD_I2C_3_4MHZ (3400000U)
/** \brief 1MHz Baud rate */
#define CDD_I2C_1MHZ (1000000U)
/** \brief 100KHz Baud rate */
#define CDD_I2C_100KHZ (100000U)
/** \brief 400KHz Baud rate */
#define CDD_I2C_400KHZ (400000U)
/** \brief 1MHz Baud rate */
#define CDD_I2C_1P0MHZ (1000000U)
/** \brief 3.4MHz Baud rate */
#define CDD_I2C_3P4MHZ (3400000U)
/**   @} */

/* ================================================================ */
/*                Typedefs, Structures and enums                    */
/* ================================================================ */
/*
 *Design: MCAL-14967, MCAL-14968, MCAL-14969, MCAL-14970, MCAL-14971, MCAL-14972, MCAL-14973,
 *MCAL-14974, MCAL-14975, MCAL-14977, MCAL-14978, MCAL-14979, MCAL-14986
 */
/** \brief Function pointer for sequence error notify*/
typedef void (*Cdd_I2c_SequenceErrorNotification)(uint8 ErrorCode);

/** \brief Function pointer for sequence complete notify*/
typedef void (*Cdd_I2c_SequenceEndNotification)(void);

/** \brief I2c_SequenceType used to pass Sequence ID*/
typedef uint8 Cdd_I2c_SequenceType;

/** \brief Cdd_I2c_AddressType used to pass addresss*/
typedef uint16 Cdd_I2c_AddressType;

/** \brief I2c_DataLengthType used to pass message size*/
typedef uint16 Cdd_I2c_DataLengthType;

/** \brief I2c_DataPtrType used to store Rx data address*/
typedef uint8* Cdd_I2c_DataPtrType;

/** \brief I2c_DataPtrType used to store Tx data address*/
typedef uint8* Cdd_I2c_DataConstPtrType;

/** \brief This is an enum containing the possible HW unit states states
 * The default HW unit state is CDD_I2C_HW_UNIT_FREE,
 */
typedef enum
{
    /** \brief I2C Hardware unit not in use by a sequence*/
    CDD_I2C_HW_UNIT_FREE,
    /** \brief I2C Hardware unit in use by a sequence*/
    CDD_I2C_HW_UNIT_BUSY
} Cdd_I2c_HwUnitStatus;

/** \brief This is an enum containing the possible driver states
 * The default driver state is CDD_I2C_UNINIT,
 * global variable used to access and update driver states is CddI2cDrvState
 */
typedef enum
{
    /** \brief I2C driver is uninitialized*/
    CDD_I2C_UNINIT,
    /** \brief I2C driver is idle*/
    CDD_I2C_IDLE,
    /** \brief I2C driver is busy*/
    CDD_I2C_BUSY
} Cdd_I2c_ComponentStatusType;

/** \brief This is an enum containing the possible variants
 * of arbitration loss timeout handling
 */
typedef enum
{
    /** \brief In case bus is busy detach from I2C bus*/
    CDD_I2C_BURST_MODE,
    /** \brief In case bus is busy try to recover I2C bus*/
    CDD_I2C_RECURRENT_MODE
} Cdd_I2c_HandlingType;

/** \brief  This is an enum containing all the possible channel results
 * The default channel state is CDD_I2C_CH_RESULT_OK
 */
typedef enum
{
    /** \brief I2C channel transmission not in progress*/
    CDD_I2C_CH_RESULT_OK,
    /** \brief I2C channel transmission is not OK*/
    CDD_I2C_CH_RESULT_NOT_OK,
    /** \brief I2C channel transmission is in progress*/
    CDD_I2C_CH_RESULT_IN_PROGRESS,
    /** \brief I2C channel transmission failed due to bus unavailability*/
    CDD_I2C_CH_RESULT_BUSFAIL,
    /** \brief I2C channel transmission failed due to arbitration loss*/
    CDD_I2C_CH_RESULT_ARBFAIL,
    /** \brief I2C channel transmission failed due to bus NACK*/
    CDD_I2C_CH_RESULT_NACKFAIL
} Cdd_I2c_ChannelResultType;

/** \brief  This is an enum containing all the possible results
 * The default sequence result is CDD_I2C_SEQ_OK
 */
typedef enum
{
    /** \brief I2C sequence transmission not in progress*/
    CDD_I2C_SEQ_OK,
    /** \brief I2C sequence transmission is not OK*/
    CDD_I2C_SEQ_NOT_OK,
    /** \brief I2C sequence transmission in progress*/
    CDD_I2C_SEQ_PENDING,
    /** \brief I2C sequence transmission queued*/
    CDD_I2C_SEQ_QUEUED,
    /** \brief I2C sequence transmission failed due to NACK*/
    CDD_I2C_SEQ_NACK,
    /** \brief I2C sequence transmission failed*/
    CDD_I2C_SEQ_FAILED,
    /** \brief I2C sequence transmission cancelled from queue*/
    CDD_I2C_SEQ_CANCELLED
} Cdd_I2c_SeqResultType;

/** \brief  This is an enum containaining the possible restart
 * modes, the default mode is CDD_I2C_RESTART_MODE_NOSTOP
 */
typedef enum
{
    /** \brief I2C restart mode with stop at end of each transaction/channel write/read*/
    CDD_I2C_RESTART_MODE_STOP,
    /** \brief I2C restart mode with no stop at end of each transaction/channel write/read,
     * by default there is start at begining of each transaction*/
    CDD_I2C_RESTART_MODE_NOSTOP
} Cdd_I2c_RestartModeType;

/** \brief  This is a structure for CDD_I2C which contains the HW unit
initialization parameters */
typedef struct
{
    /** \brief This element points to which I2C hardware instance to use for
     * communication with slave, user configurable*/
    uint8  HwInstance;
    /** \brief This element is used to set the baud rate of the desired I2c
     * bus, user configurable*/
    uint32 BaudRate;
    /** \brief This unit is used set the I2c HW module frequency*/
    uint32 HwUnitFrequency;
    /** \brief This element contains the system clock frequency being used
     * by the I2c instance*/
    uint32 SysClk;
} Cdd_I2c_Hw_Cfg;

/** \brief This is a structure for CDD_I2C configuration which contains a pointer
 * to the user configured parameters for a specified I2C HW unit
 */
typedef struct Cdd_I2c_ConfigType_s
{
    /** \brief This element points to the I2c HW unit configurations set by the user*/
    Cdd_I2c_Hw_Cfg CddI2cHwCfgPtr[CDD_I2C_HW_UNITS_USED];
} Cdd_I2c_ConfigType;

/** \brief This is a structure for CDD_I2C sequence which serves as the primary
unit for I2C communication in this driver */
#ifdef MCAL_DYNAMIC_BUILD
typedef struct
#else
typedef struct __attribute__((packed))
#endif
{
    /** \brief This element points to which I2C hardware instance to use
     * for communication with slave, user configurable*/
    uint8                             HwInstance;
    /** \brief This element indicates the maximum number of channels in
     * the given sequence, user configurable*/
    uint32                            MaxChannels;
    /** \brief This element contains the sequence result*/
    Cdd_I2c_SeqResultType             SeqResult;
    /** \brief This element is a function pointer which points to the
     * address of user provided API, in case of successful sequence completion*/
    Cdd_I2c_SequenceEndNotification   SequenceCompleteNotify;
    /** \brief This element is a function pointer which points to the address
     * of user provided API, in case of unsuccessful sequence completion*/
    Cdd_I2c_SequenceErrorNotification SequenceErrorNotify;
    /** \brief This element indicates the channel numbers used by a sequence*/
    Cdd_I2c_SequenceType              ChannelList[CDD_I2C_MAXIMUM_CHANNEL_NUMBER];
    /** \brief This element indicates the transmission mode for the slave*/
    Cdd_I2c_RestartModeType           RestartMode;
} Cdd_I2c_Sequence_Config;

/** \brief This is a structure for CDD_I2C Channel which is a part of the sequence
 */
#ifdef MCAL_DYNAMIC_BUILD
typedef struct
#else
typedef struct __attribute__((packed))
#endif
{
    /** \brief This element indicates whether we read from or write to the slave,
     * initially assigned some random value updated during Cdd_I2c_SetupEB function call*/
    uint8                     Dir;
    /** \brief This element contains the address of the slave, user configurable*/
    Cdd_I2c_AddressType       SlaveAddress;
    /** \brief If this element is 0, the slave has a 7 bit address and
     * a 10 bit address if this element is 1, user configurable*/
    uint8                     SlaveAddressScheme;
    /** \brief This element contains the size of the data buffer, initially 0
     * will be updated after Cdd_I2c_SetupEB function call*/
    Cdd_I2c_DataLengthType    DataBufferLength;
    /** \brief This element contains a pointer to which initially points to NULL
     * but will be updated after Cdd_I2c_SetupEB function call*/
    Cdd_I2c_DataPtrType       DataBuffer;
    /** \brief This element contains the channel result*/
    Cdd_I2c_ChannelResultType ChannelResult;
} Cdd_I2c_Channel_Config;

/** \brief This is a structure for Cdd_I2c queue implementation
 */
struct Cdd_I2c_Queue_obj_
{
    /** \brief This element contains the sequence ID to be executed*/
    Cdd_I2c_SequenceType       sequenceId;
    /** \brief This element is used to create a linked list implementation
     * of the queue*/
    struct Cdd_I2c_Queue_obj_* pNext;
};

typedef struct Cdd_I2c_Queue_obj_ Cdd_I2c_Queue_obj;

/** \brief Pointer type to Cdd_I2c_ConfigType*/
typedef Cdd_I2c_ConfigType* Cdd_I2c_ConfigPtrType;

/** \brief I2c_DataType used to store Tx/Rx data*/
typedef uint8 Cdd_I2c_DataType;

/** \brief I2c_ChannelType used to pass Channel ID*/
typedef uint8 Cdd_I2c_ChannelType;

/* ================================================================ */
/*                          Global variables                        */
/* ================================================================ */

extern VAR(Cdd_I2c_HwUnitStatus, CDD_I2C_VAR_INIT) CddI2cHwUnitStatus[CDD_I2C_HW_UNITS_MAX];
extern VAR(Cdd_I2c_ComponentStatusType, CDD_I2C_VAR_INIT) CddI2cDrvState;
extern VAR(Cdd_I2c_Sequence_Config, CDD_I2C_VAR_INIT) Cdd_I2cSequenceContainerLocal[CDD_I2C_MAXIMUM_SEQUENCE_NUMBER];
extern VAR(Cdd_I2c_Channel_Config, CDD_I2C_VAR_INIT) Cdd_I2cChannelContainerLocal[CDD_I2C_MAXIMUM_CHANNEL_NUMBER];

/** \brief Cdd I2c global initialization parameter pointer */
extern CONST(Cdd_I2c_ConfigPtrType, CDD_I2C_CONFIG_DATA) pCddI2cInitParams;

/** \brief Cdd I2c global sequence array */
extern CONST(Cdd_I2c_Sequence_Config, CDD_I2C_CONFIG_DATA) Cdd_I2cSequenceContainer[CDD_I2C_MAXIMUM_SEQUENCE_NUMBER];

/** \brief Cdd I2c HW unit base address array */
extern CONST(uint32, CDD_I2C_CONST) CddI2cHwUnitBaseAddr[CDD_I2C_HW_UNITS_MAX];

/** \brief Cdd I2c queue array */
extern VAR(Cdd_I2c_Queue_obj, CDD_I2C_VAR_INIT) CddI2cTransmissionQueue[CDD_I2C_MAX_QUEUE_SIZE];

/** \brief Pointer to Cdd I2c queue array[0] */
extern VAR(Cdd_I2c_Queue_obj*, CDD_I2C_VAR_INIT) pCddI2cTransmissionQueue;

/** \brief Arbitration loss parameter*/
extern CONST(Cdd_I2c_HandlingType, CDD_I2C_CONFIG_DATA) CddI2cArbitrationLossParam;

/** \brief I2c Channel configuration variables*/
extern VAR(Cdd_I2c_Channel_Config, CDD_I2C_CONFIG_DATA) Cdd_I2cChannelContainer[CDD_I2C_MAXIMUM_CHANNEL_NUMBER];

#if (STD_OFF == CDD_I2C_POLLING_MODE)
#if defined(USED_CDD_I2C_HW_UNIT_0)
extern uint8  DataReceiveBufferHwUnit0[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE];
extern uint32 DataReceiveBufferIndexHwUnit0;
#endif

#if defined(USED_CDD_I2C_HW_UNIT_1)
extern uint8  DataReceiveBufferHwUnit1[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE];
extern uint32 DataReceiveBufferIndexHwUnit1;
#endif

#if defined(USED_CDD_I2C_HW_UNIT_2)
extern uint8  DataReceiveBufferHwUnit2[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE];
extern uint32 DataReceiveBufferIndexHwUnit2;
#endif

#if defined(USED_CDD_I2C_HW_UNIT_3)
extern uint8  DataReceiveBufferHwUnit3[CDD_I2C_TX_RX_BUFFER_MAXIMUM_SIZE];
extern uint32 DataReceiveBufferIndexHwUnit3;
#endif

extern uint16 DataBufferLengthHwUnit[CDD_I2C_HW_UNITS_MAX];
#endif

/* ================================================================ */
/*                          Function Declarations                   */
/* ================================================================ */

/** \brief Service for CDD_I2C initialization
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] CfgPtr Pointer to configuration set
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_I2C_CODE) Cdd_I2c_Init(Cdd_I2c_ConfigType* configPtr);

/** \brief CDD_I2C De-initialization function
 *
 *
 * This function de-initializes the module I2c. During de-initialization
 * the module is shut down. The module is put into its power-on
 * reset state.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return Std_ReturnType
 * \retval CDD_I2C status type
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_DeInit(void);

/** \brief Returns the version information
 *
 *
 * Cdd_I2c_GetVersionInfo() returns version information, vendor ID
 * and AUTOSAR module ID of the component.
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[out] versionInfoPtr - pointer to version information, this must not
 * be NULL
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == CDD_I2C_VERSION_INFO_API) /*STD_ON == CDD_I2C_VERSION_INFO_API*/
FUNC(void, CDD_I2C_CODE) Cdd_I2c_GetVersionInfo(Std_VersionInfoType* versionInfoPtr);
#endif /*<STD_ON == CDD_I2C_VERSION_INFO_API>*/

/** \brief Setup external buffer
 *
 *
 * The service takes over the given parameters, and prepares a channel for
 * transmission (transmit buffer) and reception (receive buffer).
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] channelId -  ChannelId of the I2C channel.
 * \param[in] txDataBufferPtr - Pointer to a buffer containing data for transmission
 * \param[in] length - Number of bytes which shall be transmit/received
 * \param[out] rxDataBufferPtr - Pointer to a buffer provided for receiving data
 * \return Std_ReturnType
 * \retval External buffer setup result
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_SetupEB(Cdd_I2c_ChannelType channelId, Cdd_I2c_DataConstPtrType txDataBufferPtr,
                Cdd_I2c_DataPtrType rxDataBufferPtr, Cdd_I2c_DataLengthType length);

/** \brief Dynamically setup external buffer
 *
 *
 * The service takes over the given parameters, and prepares a channel for
 * transmission (transmit buffer) and reception (receive buffer). This
 * service does not use the channel's configured address for
 * transmission/reception, but the given address parameter
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] channelId -  ChannelId of the I2C channel.
 * \param[in] Address - Address given by the service's caller, used for
 * the transmission/reception
 * \param[in] txDataBufferPtr - Pointer to a buffer containing data for transmission
 * \param[in] length - Number of bytes which shall be transmit/received
 * \param[out] rxDataBufferPtr - Pointer to a buffer provided for receiving data
 * \return Std_ReturnType
 * \retval External buffer setup result
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_SetupEBDynamic(Cdd_I2c_ChannelType channelId, Cdd_I2c_AddressType address,
                       Cdd_I2c_DataConstPtrType txDataBufferPtr, Cdd_I2c_DataPtrType rxDataBufferPtr,
                       Cdd_I2c_DataLengthType length);

/** \brief Asynchronous data transmission
 *
 *
 * This service executes a data exchange with the prepared channels.
 * Only channels of the given sequence are affected of the data transmission
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] sequenceId - Sequence Id of specified I2c Channel
 * \return Std_ReturnType
 * \retval Transmit sequence result
 *
 *****************************************************************************/
FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_AsyncTransmit(Cdd_I2c_SequenceType sequenceId);

/** \brief Cancel a transmission
 *
 *
 * A request that is already in transmission progress, is cancelled
 * by finishing the current sequence. This is done to achieve a stable
 * state with no undefined data. A queued transmission request is cancelled
 * at once.
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \param[in] sequenceId - Sequence Id of specified I2c Channel
 * \return Std_ReturnType
 * \retval Cancel sequence transmission result
 *
 *****************************************************************************/
#if (STD_ON == CDD_I2C_CANCEL_API) /*STD_ON == CDD_I2C_CANCEL_API*/
FUNC(Std_ReturnType, CDD_I2C_CODE) Cdd_I2c_Cancel(Cdd_I2c_SequenceType sequenceId);
#endif /*STD_ON == CDD_I2C_CANCEL_API*/

/** \brief Returns the requested channel's result
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] channelId - ChannelId of the I2C channel.
 * \return Cdd_I2c_ChannelResultType
 * \retval CDD_I2C_CH_RESULT_OK - I2C channel transmission not in progress
 * \retval CDD_I2C_CH_RESULT_NOT_OK - I2C channel transmission is not OK
 * \retval CDD_I2C_CH_RESULT_IN_PROGRESS - I2C channel transmission is in progress
 * \retval CDD_I2C_CH_RESULT_BUSFAIL - I2C channel transmission failed due to bus
 * unavailability
 * \retval CDD_I2C_CH_RESULT_ARBFAIL - I2C channel transmission failed due to
 * arbitration loss
 * \retval CDD_I2C_CH_RESULT_NACKFAIL - I2C channel transmission failed due to bus NACK
 *
 *****************************************************************************/
FUNC(Cdd_I2c_ChannelResultType, CDD_I2C_CODE) Cdd_I2c_GetResult(Cdd_I2c_ChannelType channelId);

/** \brief Returns the requested sequence's result
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] sequenceId -  Sequence Id of specified I2c Channel
 * \return Cdd_I2c_SeqResultType
 * \retval CDD_I2C_SEQ_OK - I2C sequence transmission not in progress
 * \retval CDD_I2C_SEQ_NOT_OK - I2C sequence transmission is not OK
 * \retval CDD_I2C_SEQ_PENDING - I2C sequence transmission in progress
 * \retval CDD_I2C_SEQ_QUEUED - I2C sequence transmission queued
 * \retval CDD_I2C_SEQ_NACK - I2C sequence transmission failed due to NACK
 * \retval CDD_I2C_SEQ_FAILED - I2C sequence transmission failed
 * \retval CDD_I2C_SEQ_CANCELLED  - I2C sequence transmission cancelled from queue
 *
 *****************************************************************************/
FUNC(Cdd_I2c_SeqResultType, CDD_I2C_CODE)
Cdd_I2c_GetSequenceResult(Cdd_I2c_SequenceType sequenceId);

/** \brief The components MainFunction is responsible for processing
 * the sequence queue and for updating the components status
 *
 *
 * Sync/Async - Asynchronous
 *
 * Reentrancy - Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_I2C_CODE) Cdd_I2c_MainFunction(void);

/** \brief Ensures proper processing of I2c communication in the case of
 * disabled interrupts
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Non Reentrant
 *
 * \return None
 * \retval None
 *
 *****************************************************************************/
#if (STD_ON == CDD_I2C_POLLING_MODE) /*STD_ON == CDD_I2C_POLLING_MODE*/
FUNC(void, CDD_I2C_CODE) Cdd_I2c_PollingModeProcessing(void);
#endif /*STD_ON == CDD_I2C_POLLING_MODE*/

/** \brief This service sets the timeout handling
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in] handling - BURST_MODE: In case of an timeout the I2c module does
 *                                   not perform any further actions, but
 *                                   detaches from the bus.
 *                     - RECURRENT_MODE: In case of an timeout the I2c module
 *                                       sends stop signals on the bus
 * \return None
 * \retval None
 *
 *****************************************************************************/
FUNC(void, CDD_I2C_CODE) Cdd_I2c_SetHandling(Cdd_I2c_HandlingType handling);

/** \brief Returns the module's status
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \return Cdd_I2c_ComponentStatusType
 * \retval CDD_I2C_UNINIT - I2C driver is uninitialized
 * \retval CDD_I2C_IDLE - I2C driver is idle
 * \retval CDD_I2C_BUSY - I2C driver is busy
 *
 *****************************************************************************/
#if (STD_ON == CDD_I2C_GET_STATUS_API) /*STD_ON == CDD_I2C_GET_STATUS_API*/
FUNC(Cdd_I2c_ComponentStatusType, CDD_I2C_CODE) Cdd_I2c_GetStatus(void);
#endif /*STD_ON == CDD_I2C_GET_STATUS_API*/

/** \brief Returns the Register Readback Result
 *
 *
 * Sync/Async - Synchronous
 *
 * Reentrancy - Reentrant
 *
 * \param[in]  HwInstance - Hardware unit
 * \param[out] RegRbPtr - Pointer to where to store the readback values.
 * If this pointer is NULL, then the API will return CDD_I2C_NOT_OK.
 * \return Std_ReturnType
 * \retval Register readback result
 *
 *****************************************************************************/
#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
FUNC(Std_ReturnType, CDD_I2C_CODE)
Cdd_I2c_RegisterReadback(uint8 HwInstance, P2VAR(Cdd_I2c_RegisterReadbackType, AUTOMATIC, CDDI2C_APPL_DATA) RegRbPtr);
#endif /* #if (STD_ON == CDD_I2C_REGISTER_READBACK_API) */

/**
 * @}
 */

#endif
