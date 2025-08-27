/*
 * Copyright (C) 2023 Texas Instruments Incorporated - TI web adress www.ti.com
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef SCI_H
#define SCI_H

#include "reg_sci.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @struct g_sciTransfer
 *   @brief Interrupt mode globals
 *
 */
typedef struct
{
    uint32 mode;      /* Used to check for TX interrupt Enable */
    uint32 tx_length; /* Transmit data length in number of Bytes */
    uint32 rx_length; /* Receive data length in number of Bytes */
    uint8 *tx_data;   /* Transmit data pointer */
    uint8 *rx_data;   /* Receive data pointer */
} g_sciTransfer_t;

#define SCI_CPU_DATA_LIMIT 260U

typedef enum loopBackType
{
    Digital_Lbk = 0U,
    Analog_Lbk  = 1U
} loopBackType_t;

/** @def SCI_FE_INT
 *   @brief Alias for framing error Interrupt Flag Definition
 *   @note This definition used with sciEnableNotification,
 *    sciDisableNotification
 */
#define SCI_FE_INT 0x04000000U

/** @def SCI_OE_INT
 *   @brief Alias for overrun error Interrupt Flag Definition
 */
#define SCI_OE_INT 0x02000000U

/** @def SCI_PE_INT
 *   @brief Alias for parity error Interrupt Flag Definition
 */
#define SCI_PE_INT 0x01000000U

/** @def SCI_RX_INT
 *   @brief Alias for receive buffer ready Interrupt Flag Definition
 */
#define SCI_RX_INT 0x00000200U

/** @def SCI_TX_INT
 *   @brief Alias for transmit buffer ready Interrupt Flag Definition
 */
#define SCI_TX_INT 0x00000100U

/** @def SCI_WAKE_INT
 *   @brief Alias for wakeup Interrupt Flag Definition
 */
#define SCI_WAKE_INT 0x00000002U

/** @def SCI_BREAK_INT
 *   @brief Alias for break detect Interrupt Flag Definition
 */
#define SCI_BREAK_INT 0x00000001U

/** @def SCI_IDLE
 *   @brief Alias name for the SCI IDLE Flag
 *
 *   This is an alias name for the SCI IDLE Flag.
 *
 */
#define SCI_IDLE 0x00000004U

/** @struct sciBase
 *   @brief SCI Register Definition
 *
 *   This structure is used to access the SCI module registers.
 */
/** @typedef sciBASE_t
 *   @brief SCI Register Frame Type Definition
 *
 *   This type is used to access the SCI Registers.
 */

enum sciPinSelect
{
    PIN_SCI_TX = 4U,
    PIN_SCI_RX = 2U
};

/* Configuration registers */
typedef struct sci_config_reg
{
    uint32 CONFIG_GCR0;
    uint32 CONFIG_GCR1;
    uint32 CONFIG_SETINT;
    uint32 CONFIG_SETINTLVL;
    uint32 CONFIG_FORMAT;
    uint32 CONFIG_BRS;
    uint32 CONFIG_PIO0;
    uint32 CONFIG_PIO1;
    uint32 CONFIG_PIO6;
    uint32 CONFIG_PIO7;
    uint32 CONFIG_PIO8;
} sci_config_reg_t;

/* Configuration registers initial value for SCI*/
/** @def SCI_GCR0_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_GCR0_CONFIGVALUE 0x00000001U

/** @def SCI_GCR1_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_GCR1_CONFIGVALUE                                                                       \
    ((uint32)((uint32)1U << 5U) | (uint32)((uint32)(1U - 1U) << 4U) | (uint32)((uint32)0U << 3U) | \
     (uint32)((uint32)0U << 2U) | (uint32)((uint32)1U << 1U) | (uint32)((uint32)0U << 2U) | (uint32)(0x03000080U))

/** @def SCI_SETINTLVL_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_SETINTLVL_CONFIGVALUE                                                              \
    ((uint32)((uint32)0U << 26U) | (uint32)((uint32)0U << 25U) | (uint32)((uint32)0U << 24U) | \
     (uint32)((uint32)0U << 9U) | (uint32)((uint32)0U << 8U) | (uint32)((uint32)0U << 1U) |    \
     (uint32)((uint32)0U << 0U))

/** @def SCI_SETINT_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_SETINT_CONFIGVALUE                                                                 \
    ((uint32)((uint32)1U << 26U) | (uint32)((uint32)1U << 25U) | (uint32)((uint32)1U << 24U) | \
     (uint32)((uint32)1U << 9U) | (uint32)((uint32)1U << 1U) | (uint32)((uint32)1U << 0U))

/** @def SCI_FORMAT_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_FORMAT_CONFIGVALUE (8U - 1U)

/** @def SCI_BRS_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_BRS_CONFIGVALUE (520U)

/** @def SCI_PIO0_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_PIO0_CONFIGVALUE ((uint32)((uint32)1U << 2U) | (uint32)((uint32)1U << 1U))

/** @def SCI_PIO1_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_PIO1_CONFIGVALUE ((uint32)((uint32)0U << 2U) | (uint32)((uint32)0U << 1U))

/** @def SCI_PIO6_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_PIO6_CONFIGVALUE ((uint32)((uint32)0U << 2U) | (uint32)((uint32)0U << 1U))

/** @def SCI_PIO7_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_PIO7_CONFIGVALUE ((uint32)((uint32)0U << 2U) | (uint32)((uint32)0U << 1U))

/** @def SCI_PIO8_CONFIGVALUE
 *   @brief Alias for
 */
#define SCI_PIO8_CONFIGVALUE ((uint32)((uint32)1U << 2U) | (uint32)((uint32)1U << 1U))

/**
 *  @defgroup SCI SCI
 *  @brief Serial Communication Interface Module.
 *
 *  The SCI module is a universal asynchronous receiver-transmitter that implements the standard
 * nonreturn to zero format. The SCI can be used to communicate, for example, through an RS-232 port
 * or over a K-line.
 *
 *  Related Files
 *   - reg_sci.h
 *   - sci.h
 *   - sci.c
 *  @addtogroup SCI
 *  @{
 */

/* SCI Interface Functions */
void   sciAInit(void);
void   sciBInit(void);
void   sciSetFunctional(sciBASE_t *sciBaseAddr, uint32 port);
void   sciSetBaudrate(sciBASE_t *sciBaseAddr, uint32 baud);
void   sciSetBaudrateValue(sciBASE_t *sciBaseAddr, uint32 baud);
uint32 sciIsTxReady(sciBASE_t *sciBaseAddr);
void   sciSendByte(sciBASE_t *sciBaseAddr, uint8 byte);
void   sciSend(sciBASE_t *sciBaseAddr, uint32 length, uint8 *data);
uint32 sciIsRxReady(sciBASE_t *sciBaseAddr);
uint32 sciIsIdleDetected(sciBASE_t *sciBaseAddr);
uint32 sciRxError(sciBASE_t *sciBaseAddr);
uint32 sciReceiveByte(sciBASE_t *sciBaseAddr);
void   sciReceive(sciBASE_t *sciBaseAddr, uint32 length, uint8 *data);
void   sciEnableNotification(sciBASE_t *sciBaseAddr, uint32 flags);
void   sciDisableNotification(sciBASE_t *sciBaseAddr, uint32 flags);
void   sciEnableLoopback(sciBASE_t *sciBaseAddr, loopBackType_t Loopbacktype);
void   sciDisableLoopback(sciBASE_t *sciBaseAddr);
void   sciGetConfigValue(sciBASE_t *sciBaseAddr, sci_config_reg_t *config_reg, config_value_type_t type);

/**@}*/
#ifdef __cplusplus
}
#endif

#endif
