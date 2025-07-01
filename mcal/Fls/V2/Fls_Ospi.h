
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
 *  \file     Fls_Ospi.h
 *
 *  \brief    This file contains interface header for FLS MCAL driver
 *
 */

#ifndef FLS_OSPI_H_
#define FLS_OSPI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include "Std_Types.h"
#include "hw_ospi.h"
#include "hw_types.h"
#include "hw_ctrl_core.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief A handle that is returned from a #OSPI_open() call */
typedef void *OSPI_Handle;

#define OSPI_NOR_CMD_RDSFDP (0x5AU)
#define OSPI_NOR_SFDP_DC    (8U)
/**
 *  \anchor OSPI_TransferStatus
 *  \name Transfer Status Code
 *
 *  Status codes that are set by the OSPI driver
 *
 *  @{
 */
#define OSPI_TRANSFER_COMPLETED    (0U)
#define OSPI_TRANSFER_STARTED      (1U)
#define OSPI_TRANSFER_CANCELLED    (2U)
#define OSPI_TRANSFER_FAILED       (3U)
#define OSPI_TRANSFER_CSN_DEASSERT (4U)
#define OSPI_TRANSFER_TIMEOUT      (5U)
/** @} */

/**
 *  \anchor OSPI_TransferMode
 *  \name Transfer Mode
 *
 *  This determines whether the driver operates synchronously or asynchronously
 *
 *  In #OSPI_TRANSFER_MODE_BLOCKING \ref OSPI_Transfers block code
 *  execution until the transaction has completed
 *
 *  In #OSPI_TRANSFER_MODE_CALLBACK OSPI_Transfers does not block code
 *  execution and instead calls a callback function when the
 *  transaction has completed
 *
 *  @{
 */
/**
 *  \brief \ref OSPI_Transfers blocks execution. This mode can only be used
 *  when called within a Task context and is interrupt based
 */
#define OSPI_TRANSFER_MODE_BLOCKING (0U)
/**
 *  \brief \ref OSPI_Transfers does not block code execution and will call a
 *  callback function. This mode can be used in a Task, Swi, or Hwi context
 */
#define OSPI_TRANSFER_MODE_CALLBACK (1U)
/**
 *  \brief \ref OSPI_Transfers blocks execution. This mode can only be used
 *  when called within a Task context and is polling based.
 */
#define OSPI_TRANSFER_MODE_POLLING (2U)
/** @} */

/**
 *  \anchor OSPI_FrameFormat
 *  \name Frame Format
 *
 *  Definitions for various SPI data frame formats
 *
 *  POL0 = OSPICLK is held low during the INACTIVE state
 *  POL1 = OSPICLK is held high during the INACTIVE state
 *
 *  PHA0 = Data launch is on the falling edge of OSPICLK
 *  PHA1 = Data launch is on the rising edge of OSPICLK
 *
 *  @{
 */
#define OSPI_FF_POL0_PHA0 (0U)
#define OSPI_FF_POL0_PHA1 (OSPI_CONFIG_REG_SEL_CLK_PHASE_FLD_MASK | 0U)
#define OSPI_FF_POL1_PHA0 (0U | OSPI_CONFIG_REG_SEL_CLK_POL_FLD_MASK)
#define OSPI_FF_POL1_PHA1 (OSPI_CONFIG_REG_SEL_CLK_PHASE_FLD_MASK | OSPI_CONFIG_REG_SEL_CLK_POL_FLD_MASK)
/** @} */

/**
 *  \anchor OSPI_CmdMacros
 *  \name Macros for invalid commands
 *
 *  Macros for invalid commands
 *
 *  @{
 */
#define OSPI_CMD_INVALID_OPCODE (0xFFU)
#define OSPI_CMD_INVALID_DUMMY  (0xFFU)
#define OSPI_CMD_INVALID_ADDR   (0xFFFFFFFFU)
/** @} */

/**
 *  \anchor OSPI_CmdExtTypes
 *  \name Macros for command extension types
 *
 *  Macros for command extension types
 *
 *  @{
 */
#define OSPI_CMD_EXT_TYPE_REPEAT  (0x00U)
#define OSPI_CMD_EXT_TYPE_INVERSE (0x01U)
#define OSPI_CMD_EXT_TYPE_NONE    (0x02U)
/** @} */

/**
 *  \anchor OSPI_NorProtocolTypes
 *  \name Macros for OSPI protocol types
 *
 *  Macros for protocol types
 *
 *  @{
 */
#define OSPI_NOR_PROTOCOL(cmd, addr, data, dtr) \
    (uint32)(((uint32)(dtr) << 24) | ((uint32)(cmd) << 16) | ((uint32)(addr) << 8) | ((uint32)(data) << 0))
#define OSPI_NOR_PROTOCOL_INVALID (uint32)(0xFFFFFFFF)
/** @} */

/**
 *  \anchor OSPI_ChipSelect
 *  \name Chip Selects
 *
 *  Chip selects
 *
 *  @{
 */
#define OSPI_CS0 (0U)
#define OSPI_CS1 (1U)
#define OSPI_CS2 (2U)
#define OSPI_CS3 (3U)

#define OSPI_CHIP_SELECT(x) ((~((1U) << (x))) & 0xFU)
/** @} */

#define OSPI_RESETPIN_DQ3       (0U)
#define OSPI_RESETPIN_DEDICATED (1U)

/**
 *  \anchor OSPI_DecChipSelect
 *  \name Decoder Chip Selects
 *
 *  Decoder Chip selects
 *
 *  @{
 */
#define OSPI_DECODER_SELECT4  ((uint32)0U)
#define OSPI_DECODER_SELECT16 ((uint32)1U)

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/*Ospi Number of Instances*/
#define OSPI_NUM_INSTANCES (1U)

/** \brief    OSPI DMA related macros */
#define OSPI_DMA_COPY_LOWER_LIMIT    (1024U)
#define OSPI_DMA_COPY_SRC_ALIGNMENT  (32U)
#define OSPI_DMA_COPY_SIZE_ALIGNMENT (32U)

/** \brief    OSPI Command default Length */
#define OSPI_CMD_LEN_DEFAULT  (1U) /*In bytes */
#define OSPI_CMD_LEN_EXTENDED (5U) /*In bytes */

/** \brief    OSPI operation timeout value */
#define OSPI_POLL_IDLE_TIMEOUT (5000U) /* in millisecond */
#define OSPI_POLL_IDLE_DELAY   (1U)    /* in millisecond */
#define OSPI_POLL_IDLE_RETRY   (3U)
#define OSPI_REG_RETRY         (10U)
#define OSPI_FIFO_WIDTH        (4U)

/** \brief OSPI Chip select macro */
#define OSPI_CHIP_SELECT(x) ((~((1U) << (x))) & 0xFU)

/**
 * \brief   OSPI controller controller mode baud rate divisor.
 *          OSPI baud rate = controller_ref_clk/BD, where BD is:
 *          0000 = /2
 *          0001 = /4
 *          0010 = /6
 *          ...
 *          1111 = /32
 */
#define OSPI_BAUD_RATE_DIVISOR(x)      (((x) - 2U) >> 1U)
#define OSPI_BAUD_RATE_DIVISOR_DEFAULT (OSPI_BAUD_RATE_DIVISOR(32U))

/**
 *  \brief   OSPI device delay parameter array size.
 */
#define OSPI_DEV_DELAY_ARRAY_SIZE (4U)

/** \brief   OSPI device delays in cycles of OSPI controller ref clock */
#define OSPI_DEV_DELAY_CSSOT  (46U)  /* Chip Select Start of Transfer Delay */
#define OSPI_DEV_DELAY_CSEOT  (46U)  /* Chip Select End of Transfer Delay */
#define OSPI_DEV_DELAY_CSDADS (192U) /* Chip Select De-Assert Different Peripheral Delay */
#define OSPI_DEV_DELAY_CSDA   (192U) /* Chip Select De-Assert Delay */

/** \brief  SRAM partition configuration definitions */
/** size of the indirect read/write partition in the SRAM,
    in units of SRAM locations */
#define OSPI_SRAM_SIZE_WORDS   (128U)
#define OSPI_SRAM_PARTITION_RD (64U)
#define OSPI_SRAM_PARTITION_WR (OSPI_SRAM_SIZE_WORDS - OSPI_SRAM_PARTITION_RD)
/* Default value for SRAM PARTITION register */
#define OSPI_SRAM_PARTITION_DEFAULT (OSPI_SRAM_PARTITION_RD - 1U)

#define OSPI_READ_WRITE_TIMEOUT (500000U)
#define OSPI_CHECK_IDLE_DELAY   (10U)
#define OSPI_CALIBRATE_DELAY    (20U)
#define OSPI_XIP_SETUP_DELAY    (250U)

/**  \brief  SRAM fill level watermark */
/* Read watermark fill level in words, will generate DMA request or
   interrupt when the SRAM fill level is above the watermark */
#define OSPI_SRAM_WARERMARK_RD_LVL (OSPI_SRAM_PARTITION_RD / 4U)
/* Write watermark fill level in words, will generate DMA request or
   interrupt when the SRAM fill level is below the watermark */
#define OSPI_SRAM_WATERMARK_WR_LVL (OSPI_SRAM_PARTITION_WR / 4U)

#define OSPI_INTR_MASK_IND_XFER                                                                                \
    (OSPI_IRQ_STATUS_REG_INDIRECT_OP_DONE_FLD_MASK | OSPI_IRQ_STATUS_REG_INDIRECT_XFER_LEVEL_BREACH_FLD_MASK | \
     OSPI_IRQ_STATUS_REG_INDRD_SRAM_FULL_FLD_MASK)

#define OSPI_INTR_MASK_ALL                                                                                    \
    (OSPI_IRQ_STATUS_REG_MODE_M_FAIL_FLD_MASK | OSPI_IRQ_STATUS_REG_UNDERFLOW_DET_FLD_MASK |                  \
     OSPI_IRQ_STATUS_REG_INDIRECT_OP_DONE_FLD_MASK | OSPI_IRQ_STATUS_REG_INDIRECT_READ_REJECT_FLD_MASK |      \
     OSPI_IRQ_STATUS_REG_PROT_WR_ATTEMPT_FLD_MASK | OSPI_IRQ_STATUS_REG_ILLEGAL_ACCESS_DET_FLD_MASK |         \
     OSPI_IRQ_STATUS_REG_INDIRECT_XFER_LEVEL_BREACH_FLD_MASK | OSPI_IRQ_STATUS_REG_INDRD_SRAM_FULL_FLD_MASK | \
     OSPI_IRQ_STATUS_REG_POLL_EXP_INT_FLD_MASK)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief LUT table for log2 calculation using DeBruijn sequence */
static const uint8 gTable[32] = {0, 9,  1,  10, 13, 21, 2,  29, 11, 14, 16, 18, 22, 25, 3, 30,
                                 8, 12, 20, 28, 15, 17, 24, 7,  19, 27, 23, 6,  26, 5,  4, 31};
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32 count;
    /**< [IN] Number of frames for this transaction */
    void  *buf;
    /**< [IN] void * to a buffer to receive/send data */
    uint32 addrOffset;
    /**< [IN] Address offset to write to an OSPI flash device. */
    uint32 status;
    /**< [OUT] \ref OSPI_TransferStatus code set by \ref OSPI_Transfers */
    uint32 transferTimeout;
    /**< [IN] Timeout of the specific transfer */
} OSPI_Transaction;

typedef struct
{
    OSPI_Handle       handle;
    /* Instance handle */
    uint32            transferMode;
    /* Polling, Blocking or Callback mode. */
    uint32            currentprotocol;
    /**< Protocol for OSPI reading/writing. 32 bit integer with
     * byte0 -> data lines
     * byte1 -> addr lines
     * byte2 -> cmd lines
     * byte3 -> STR/DTR (0 = STR, 1 = DTR)
     * */
    uint32            rdDummyCycles;
    /**< Number of dummy cycles needed for read */
    uint32            cmdDummyCycles;
    /**< Number of dummy cycles needed for cmd */
    uint32            rdDataCapDelay;
    /**< Read data capture delays needed */
    uint32            phyRdDataCapDelay;
    /**< Read data capture delays needed when phy is enabled*/
    uint32            numAddrBytes;
    /**< Number of bytes used to represent address to be sent to flash.
    This is the actual number of bytes used. The code to be programmed to
    registers is this value-1. That is, for 4-byte addressing mode, register
    should be programmed as 3 */
    uint32            cmdExtType;
    /**< In dual byte opcode mode, the extended opcode can vary depending on flash
    This variable should be populated from the flash driver using the \ref OSPI_setCmdExtType API */
    uint32            isOpen;
    /* Flag to indicate if the instance is already open */
    OSPI_Transaction *transaction;
    /* Pointer to current transaction struct */
} OSPI_Object;

typedef struct
{
    uint8  cmd;
    /**< [IN] Command Opcode */
    uint32 cmdAddr;
    /**< [IN] Address required by the command. Usually needed in writing to flash registers.
    Should be initialized to #OSPI_CMD_INVALID_ADDR if not used. */
    uint8  numAddrBytes;
    /**< [IN] Number of address bytes used to send cmd address */
    void  *txDataBuf;
    /**< [IN] Buffer containing command data */
    uint32 txDataLen;
    /**< [IN] Length of response buffer */
} OSPI_WriteCmdParams;

typedef struct
{
    uint8  cmd;
    /**< [IN] Command Opcode */
    uint32 cmdAddr;
    /**< Address required by the command. Usually needed in reading flash registers.
    Should be initialized to #OSPI_CMD_INVALID_ADDR if not used. */
    uint8  numAddrBytes;
    /**< [IN] Number of address bytes used to send cmd address */
    uint8  dummyBits;
    /**< [IN] Number dummyClks needed for the command */
    void  *rxDataBuf;
    /**< [OUT] Buffer to store response from flash */
    uint16 rxDataLen;
    /**< [IN] Length of response buffer */
} OSPI_ReadCmdParams;

typedef struct
{
    OSPI_Object *object;
    /**< Pointer to driver specific data object */
} OSPI_Config;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** @} */

/**
 *  \brief  Function to initialize the #OSPI_Transaction structure
 *
 *
 *  \param  trans Pointer to a #OSPI_Transaction
 *
 */
void           Fls_Ospi_TransactionInit(OSPI_Transaction *trans);
/**
 *  \brief  This function executes the read and write command operation
 */
static uint32  Fls_Ospi_ExecCmd(void);
/**
 *  \brief  Function to send specific commands and receive related data from flash
 *
 *  \param  handle      #OSPI_Handle returned from #OSPI_open()
 *  \param  rdParams    Pointer to a #OSPI_ReadCmdParams
 *
 *  \return #SystemP_SUCCESS if command read was successful; else error on failure
 */
Std_ReturnType Fls_Ospi_ReadCmd(OSPI_Handle handle, OSPI_ReadCmdParams *rdParams);
/**
 *  \brief  Function to read from flash in DAC mod
 *
 *  \param  handle      #OSPI_Handle returned from #OSPI_open()
 *  \param  trans       Pointer to a #OSPI_Transaction
 *
 *  \return #SystemP_SUCCESS if read was successful; else error on failure
 */
Std_ReturnType Fls_Ospi_readDirect(OSPI_Handle handle, OSPI_Transaction *trans);
/**
 *  \brief  Function to read from flash in INDAC mode
 *
 *  \param  handle      #OSPI_Handle returned from #OSPI_open()
 *  \param  trans       Pointer to a #OSPI_Transaction
 *
 *  \return #SystemP_SUCCESS if read was successful; else error on failure
 */
Std_ReturnType Fls_Ospi_readIndirect(OSPI_Handle handle, OSPI_Transaction *trans);
/**
 *  \brief  Function to send specific commands and related data to flash
 *
 *  \param  handle      #OSPI_Handle returned from #OSPI_open()
 *  \param  wrParams    Pointer to a #OSPI_WriteCmdParams
 *
 *  \return #SystemP_SUCCESS if command write was successful; else error on failure
 */
Std_ReturnType Fls_Ospi_WriteCmd(OSPI_Handle handle, OSPI_WriteCmdParams *wrParams);
/**
 *  \brief  Function to write in DAC mode
 *
 *  \param  handle      #OSPI_Handle returned from #OSPI_open()
 *  \param  trans       Pointer to a #OSPI_Transaction
 *
 *  \return #SystemP_SUCCESS if write was successful; else error on failure
 */
Std_ReturnType Fls_Ospi_writeDirect(OSPI_Handle handle, OSPI_Transaction *trans);
/**
 *  \brief  Function to write in INDAC mode
 *
 *  \param  handle      #OSPI_Handle returned from #OSPI_open()
 *  \param  trans       Pointer to a #OSPI_Transaction
 *
 *  \return #SystemP_SUCCESS if write was successful; else error on failure
 */
Std_ReturnType Fls_Ospi_writeIndirect(OSPI_Handle handle, OSPI_Transaction *trans);

/**
 *  \brief  This function opens a given OSPI peripheral
 *
 *  \pre    OSPI controller has been initialized using #OSPI_init()
 *
 *  \return A #OSPI_Handle on success or a NULL_PTR on an error or if it has been
 *          opened already
 */
OSPI_Handle           Fls_Ospi_Open(void);
/**
 *  \brief  Function to close a OSPI peripheral specified by the OSPI handle
 *
 *  \pre    #OSPI_open() has to be called first
 *
 *  \param  handle      #OSPI_Handle returned from #OSPI_open()
 */
void                  Fls_Ospi_Close(OSPI_Handle handle);
/**
 *  \brief  Function to configure OSPI Parameter such as OSPI pin and baudrate
 *
 *  \param  OSPI Config
 *
 *  \return #SystemP_SUCCESS if all configuration are successfully done
 */
static Std_ReturnType Fls_Ospi_ProgramInstance(OSPI_Config *config);
static uint32         OSPI_utilLog2(uint32 num);
/**
 *   \brief  This function sets the protocol for single/quad/octal read/write
 *   according to user config
 *
 *   \param  handle   #OSPI_Handle returned from #OSPI_open()
 *   \param  protocol  user selected mode for read and write transfer
 *
 */
Std_ReturnType        Fls_Ospi_setProtocol(OSPI_Handle handle, uint32 protocol);
/**
 *  \Function Name: Fls_Ospi_SetProtocolCmds
 *
 *   This function sets the command, data and address lines for the
 *   configured protocol
 *
 */
void                  Fls_Ospi_SetProtocolCmds(OSPI_Handle handle, uint32 cmd, uint32 addr, uint32 data, uint32 dtr);
/**
 *   \brief  This function set the transfer code for read and write
 *
 *   \param  handle   #OSPI_Handle returned from #OSPI_open()
 *   \param  readcmd  command to be set for read
 *   \param  pageProgCmd  command to be set for write
 */
void                  Fls_Ospi_setXferOpCodes(OSPI_Handle handle, uint8 readCmd, uint8 pageProgCmd);
/**
 *   \brief  Function to set mode cmd and dummy cycles
 *
 *   \param  handle   #OSPI_Handle returned from #OSPI_open()
 *
 *   \return #SystemP_SUCCESS if command was set successfully
 */
Std_ReturnType        Fls_Ospi_SetModeDummy(OSPI_Handle handle);
/**
 *  \brief  This function is used to enable word or frame complete interrupt.
 */
void                  Fls_OspiIntEnable(void);
/**
 *  \brief    This function Disables and Clear Interrupt Register.
 */
void                  Fls_IntClearDisable(void);
/**
 *  \brief    This function check the Hardware interrupt status register.
 */
void                  Fls_Interrupt_Enable(void);
/**
 *  \brief   This function handles the jobs in interrupt mode
 */
void                  Fls_hwi(void);
/**
 *  \Function Name: Fls_set888mode
 *
 *   This function is used to set register read and write commands for 888 mode.
 *
 */
Std_ReturnType        Fls_set888mode(OSPI_Handle handle, uint8 seq);
/**
 *  \Function Name: Fls_set444mode
 *
 *   This function is used to set register read and write commands for 444 mode.
 *
 */
Std_ReturnType        Fls_set444mode(OSPI_Handle handle, uint8 seq);

/**
 *  \Function Name: Fls_set111mode
 *
 *   This function is used to set register read and write commands for 111 mode.
 *
 */
Std_ReturnType Fls_set111mode(OSPI_Handle handle, uint8 rdCmd, uint8 wrCmd, uint8 eraseCmd);

/**
 *  \Function Name: Nor_FlsReadSfdp
 *
 *   This function is used to read sfdp related values.
 *
 */
Std_ReturnType Nor_FlsReadSfdp(OSPI_Handle handle, uint32 offset, uint8 *buf, uint32 len);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef OSPI_H_ */

/*******************************************************************************
 *  End of File: Fls_Ospi.h
 *  ******************************************************************************/
