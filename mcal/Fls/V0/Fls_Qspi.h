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
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * any redistribution and use of any object code compiled from the source code
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
 *  \file     Fls_Qspi.h
 *
 *  \brief    This file contains interface header for FLS MCAL driver
 *
 */

#ifndef FLS_QSPI_H_
#define FLS_QSPI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include "Platform_Types.h"
#include "hw_ctrl_core.h"
#include "hw_types.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*QSPI_ChipSelect*/
#define FLS_QSPI_CS0 (0U)
#define FLS_QSPI_CS1 (1U)
#define FLS_QSPI_CS2 (2U)
#define FLS_QSPI_CS3 (3U)
/** @} */

/**
 *  \anchor QSPI_CmdMacros
 */
#define FLS_QSPI_CMD_INVALID_OPCODE (0xFFU)
#define FLS_QSPI_CMD_INVALID_ADDR   (0xFFFFFFFFU)
#define FLS_QSPI_CMD_DELAY          20U
/** @} */
/**
 *  \anchor QSPI_TransferStatus
 *  \name Transfer Status Code
 *
 *  Status codes that are set by the QSPI driver
 *
 *  @{
 */
#define FLS_SPI_MAX_CONFIG_CNT (2U)

typedef enum SPI_Status_s
{
    SPI_TRANSFER_COMPLETED = 0,
    SPI_TRANSFER_STARTED,
    SPI_TRANSFER_CANCELED,
    SPI_TRANSFER_FAILED,
    SPI_TRANSFER_CSN_DEASSERT,
    SPI_TRANSFER_TIMEOUT
} SPI_Status;
/** @} */
/**
 *  \anchor QSPI_TransferLines
 *  \name Transfer Lines Number
 *
 *  Number of lines used for QSPI read transaction
 *
 *  @{
 */
/** @} */

/**
 *  \anchor QSPI_FrameFormat
 *  \name Frame Format
 *
 *  Definitions for various SPI data frame formats
 *
 *  POL0 = QSPICLK is held low during the INACTIVE state
 *  POL1 = QSPICLK is held high during the INACTIVE state
 *
 *  PHA0 = Data launch is on the falling edge of QSPICLK
 *  PHA1 = Data launch is on the rising edge of QSPICLK
 *
 *  @{
 */
#define FLS_QSPI_FF_POL0_PHA0                                                              \
    ((QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_FALLING_EDGE << QSPI_SPI_DC_REG_CKPH0_SHIFT) | \
     (QSPI_SPI_DC_REG_CKP0_DATA_INACTIVE << QSPI_SPI_DC_REG_CKP0_SHIFT))
#define FLS_QSPI_FF_POL0_PHA1                                                             \
    ((QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_RISING_EDGE << QSPI_SPI_DC_REG_CKPH0_SHIFT) | \
     (QSPI_SPI_DC_REG_CKP0_DATA_INACTIVE << QSPI_SPI_DC_REG_CKP0_SHIFT))
#define FLS_QSPI_FF_POL1_PHA0                                                             \
    ((QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_RISING_EDGE << QSPI_SPI_DC_REG_CKPH0_SHIFT) | \
     (QSPI_SPI_DC_REG_CKP0_DATA_ACTIVE << QSPI_SPI_DC_REG_CKP0_SHIFT))
#define FLS_QSPI_FF_POL1_PHA1                                                              \
    ((QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_FALLING_EDGE << QSPI_SPI_DC_REG_CKPH0_SHIFT) | \
     (QSPI_SPI_DC_REG_CKP0_DATA_ACTIVE << QSPI_SPI_DC_REG_CKP0_SHIFT))
/** @} */

/**
 *  \anchor QSPI_ChipSelectPolarity
 *  \name Chip select polarity
 *
 *  Polarity of Chip Select
 *
 *  @{
 */
#define FLS_QSPI_CS_POL_ACTIVE_LOW  (QSPI_SPI_DC_REG_CSP0_ACTIVE_LOW)
#define FLS_QSPI_CS_POL_ACTIVE_HIGH (QSPI_SPI_DC_REG_CSP0_ACTIVE_HIGH)
/** @} */

/**
 *  \anchor QSPI_DataDelay
 *  \name Data Delay
 *
 *  Value of delay in data output after CS goes active.
 *
 *  @{
 */
#define FLS_QSPI_DATA_DELAY_0 (QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_0)
#define FLS_QSPI_DATA_DELAY_1 (QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_1)
#define FLS_QSPI_DATA_DELAY_2 (QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_2)
#define FLS_QSPI_DATA_DELAY_3 (QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_3)
/** @} */

/* ========================================================================== */
/*                             Structure Definitions                          */
/* ========================================================================== */

/**
 *  \brief Data structure used with \ref QSPI_Transfers - #QSPI_writeConfigMode,
 *  #QSPI_readMemMapMode
 *
 *  It indicates how many \ref QSPI_FrameFormat frames are sent and received
 *  from and to the buffer buf.
 */
typedef struct
{
    uint32 count;
    /**< [IN] Number of frames for this transaction */
    void  *buf;
    /**< [IN] void * to a buffer to receive/send data */
    uint32 addrOffset;
    /**< [IN] Address offset to write to an QSPI flash device. */
    uint32 status;
    /**< [OUT] \ref QSPI_TransferStatus code set by \ref QSPI_Transfers */
} QSPI_Transaction;

typedef struct
{
    uint8  cmd;
    /**< [IN] Command Opcode */
    uint32 cmdAddr;
    /**< Address required by the command. Usually needed in reading flash registers.
    Should be initialized to #FLS_QSPI_CMD_INVALID_ADDR if not used. */
    uint32 numAddrBytes;
    /**< [IN] Number of address bytes used to send cmd address */
    void  *txDataBuf;
    /**< [IN] Buffer containing command data */
    void  *rxDataBuf;
    /**< [OUT] Buffer to store response from flash */
    uint32 DataLen;
    /**< [IN] Length of response buffer */
} QSPI_CmdParams;

/**
 *  \brief QSPI Parameters
 *
 *  QSPI Parameters are used to with the #QSPI_open() call. Default values for
 *  these parameters are set using #QSPI_Params_init().
 *
 *  If NULL is passed for the parameters, #QSPI_open() uses default parameters.
 *
 *  \sa #QSPI_Params_init()
 */
/**
 *  \brief QSPI driver object
 */
typedef void *QSPI_Handle;

typedef struct
{
    QSPI_Handle       handle;
    /* Instance handle */
    uint32            transferMode;
    /* Polling, Blocking or Callback mode. */
    uint32            rxLines;
    /* Number of lines used for QSPI reading */
    uint8             readCmd;
    /* Transfer command to be used for reading from QSPI flash */
    uint8             writeCmd;
    /* Transfer command to be used for writing to QSPI flash */
    uint32            frmLength;
    /* Frame length of total transfer */
    uint32            numAddrBytes;
    /* Number of bytes used to represent address to be sent to flash. */
    uint32            numDummyBits;
    /* Number of dummy bits required while reading from flash */
    uint32            isOpen;
    /* Flag to indicate if the instance is already open */
    QSPI_Transaction *transaction;
    /* Pointer to current transaction struct */
} QSPI_Object;

typedef struct
{
    QSPI_Object *object;
    /**< Pointer to driver specific data object */
} QSPI_Config;

/** \brief Externally defined driver configuration array */

extern VAR(QSPI_Config, FLS_VAR_INIT) Fls_QspiConfig[1];
extern VAR(uint32, FLS_VAR_INIT) Fls_QspiConfigNum;

extern VAR(QSPI_Object, FLS_VAR_NO_INIT) Fls_QspiObjects[1];

/** \brief Externally defined driver configuration array size */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  This function initializes the QSPI module
 */
extern void Fls_QspiHwInit(void);

/**
 *  \brief  Initialize data structure with defaults
 *
 *  \param  qspiParams [out] Initialized parameters
 */
Std_ReturnType Fls_Qspi_ParamsInit(QSPI_CmdParams *QSPI_Params);

/**
 *  \brief  This function opens a given QSPI peripheral
 *
 *  \pre    QSPI controller has been initialized using #QSPI_init()
 *
 *  \param  index       Index of config to use in the *QSPI_Config* array
 *  \param  openParams  Pointer to parameters to open the driver with
 *
 *  \return A #QSPI_Handle on success or a NULL on an error or if it has been
 *          opened already
 *
 *  \sa     #QSPI_init()
 *  \sa     #QSPI_close()
 */
QSPI_Handle Fls_QspiOpen(uint32 index);
/**
 *  \brief  Function to close a QSPI peripheral specified by the QSPI handle
 *
 *  \pre    #QSPI_open() has to be called first
 *
 *  \param  handle      #QSPI_Handle returned from #QSPI_open()
 *
 *  \sa     #QSPI_open()
 */
void        Fls_QspiClose(QSPI_Handle handle);

/**
 *  \brief  Function to perform reads from the flash in memory mapped
 *          mode.
 *
 *  \param  handle      #QSPI_Handle returned from #QSPI_open()
 *  \param  trans       Pointer to a #QSPI_Transaction
 *
 *  \return #SystemP_SUCCESS on successful read; else error on failure
 *
 *  \sa     #QSPI_open
 */
Std_ReturnType Fls_Qspi_ReadMemMapMode(QSPI_Handle handle, QSPI_Transaction *trans);

/**
 *  \brief  Function to perform writes to the flash in configuration mode.
 *
 *  \param  handle      #QSPI_Handle returned from #QSPI_open()
 *  \param  trans       Pointer to a #QSPI_Transaction
 *
 *  \return #SystemP_SUCCESS on successful write; else error on failure
 *
 *  \sa     #QSPI_open
 */
Std_ReturnType Fls_Qspi_WriteConfigMode(QSPI_Handle handle, QSPI_Transaction *trans);
/** @} */

/**
 *  \brief  Function to perform reads from the flash in configuration mode.
 *
 *  \param  handle      #QSPI_Handle returned from #QSPI_open()
 *  \param  trans       Pointer to a #QSPI_Transaction
 *
 *  \return #SystemP_SUCCESS on successful read; else error on failure
 *
 *  \sa     #QSPI_open
 */
Std_ReturnType Fls_Qspi_ReadConfigMode(QSPI_Handle handle, QSPI_Transaction *trans);
/** @} */

/**
 *  \brief  Function to initialize the #QSPI_Transaction structure
 *
 *
 *  \param  trans Pointer to a #QSPI_Transaction
 *
 */
void Fls_Qspi_TransactionInit(QSPI_Transaction *trans);

/**
 *  \brief  Function to send specific commands and receive related data from flash
 *
 *  \param  handle      #QSPI_Handle returned from #QSPI_open()
 *  \param  rdParams    Pointer to a #QSPI_ReadCmdParams
 *
 *  \return #SystemP_SUCCESS if command read was successful; else error on failure
 *
 *  \sa     #QSPI_open
 */
Std_ReturnType Fls_Qspi_ReadCmd(QSPI_Handle handle, QSPI_CmdParams *rdParams);

/**
 *  \brief  Function to read data from flash
 *
 *  \param  handle      #QSPI_Handle returned from #QSPI_open()
 *  \param  rdParams    Pointer to a #QSPI_ReadCmdParams
 *
 *  \return #SystemP_SUCCESS if command read was successful; else error on failure
 *
 *  \sa     #QSPI_open
 */
Std_ReturnType Fls_Qspi_QuadReadData(QSPI_Handle handle, QSPI_CmdParams *rdParams);

/**
 *  \brief  Function to send specific commands and related data to flash
 *
 *  \param  handle      #QSPI_Handle returned from #QSPI_open()
 *  \param  wrParams    Pointer to a #QSPI_WriteCmdParams
 *
 *  \return #SystemP_SUCCESS if command write was successful; else error on failure
 *
 *  \sa     #QSPI_open
 */
Std_ReturnType Fls_Qspi_WriteCmd(QSPI_Handle handle, QSPI_CmdParams *wrParams);

/**
 *  \brief  This function is used to enable word or frame complete interrupt.
 *
 *  \param   handle     A #QSPI_Handle returned from a #QSPI_open()
 *  \param   intFlag    Flag for enabling interrupt.
 *
 *  \return  #SystemP_SUCCESS on success, #SystemP_FAILURE otherwise
 */
void Fls_QspiIntEnable(uint32 intFlag);

/**
 *  \brief  This function is used to disable word or frame complete interrupt.
 *
 *  \param   handle     A #QSPI_Handle returned from a #QSPI_open()
 *  \param   intFlag    Flag for disabling interrupt.
 *
 *  \return  #SystemP_SUCCESS on success, #SystemP_FAILURE otherwise
 */
void Fls_QspiIntDisable(uint32 intFlag);

/**
 *  \brief  This function is used to clear word or frame complete interrupt.
 *
 *  \param   handle     A #QSPI_Handle returned from a #QSPI_open()
 *  \param   intFlag    Flag for clearing interrupt.
 *
 *  \return  #SystemP_SUCCESS on success, #SystemP_FAILURE otherwise
 */
void Fls_QspiIntClear(uint32 intFlag);

/**
 *  \brief    This function Disables and Clear Interrupt Register.
 */
void Fls_IntClearDisable(void);
/**
 *  \brief    This function check the Hardware interrupt status register.
 */
void Fls_Interrupt_Enable(void);

/**
 *  \brief   Set the QSPI clock register divider value.
 *
 *  \details This function sets the QSPI clock control register
 *           with serial data clock divider ratio (DCLK_DIV)
 *           according to the input clock provided and the output clock
 *           required.
 *           DCLK_DIV = ((input clock) / (output clock)) - 1.
 *           This function also enables the clock for QSPI module.
 *           This can only be done if QSPI module is not busy.
 *
 *  \param   handle           A #QSPI_Handle returned from a #QSPI_open()
 *
 *  \param   clkDividerVal    Clock divider value to be set.
 *
 *  \return  #SystemP_SUCCESS on success, #SystemP_FAILURE otherwise
 */
Std_ReturnType Fls_Qspi_SetPreScaler(QSPI_Handle handle, uint32 clkDividerVal);

void Fls_hwi(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef QSPI_H_ */

/** @} */
