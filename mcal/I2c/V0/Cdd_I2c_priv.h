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
 *  \file     Cdd_I2c_priv.h
 *
 *  \brief    This file contains internal function implementations for CDD I2C
 *
 */

#ifndef CDD_I2C_PRIV_H_
#define CDD_I2C_PRIV_H_

/* ================================================================ */
/*                             Include Files                        */
/* ================================================================ */

#include "Platform_Types.h"

/* ================================================================ */
/*                           Macros                                 */
/* ================================================================ */

#define SEQUENCE_INITIALIZER (255U)
/*Macro defined to set initial value of sequence*/
#define CHANNEL_INITIALIZER (255U)
/*Macro defined to set initial value of channel*/

/* ================================================================ */
/*                Typedefs, Structures and enums                    */
/* ================================================================ */

/*None*/

/* ================================================================ */
/*                          Global variables                        */
/* ================================================================ */

/*None*/

/* ================================================================ */
/*                          Function Declarations                   */
/* ================================================================ */

/** \brief Service for Cdd_I2cReportDetError
 *  \verbatim
 *  Service name        : Cdd_I2cReportDetError
 *  Syntax              : void Cdd_I2cReportDetError(uint8 apiId, uint8 errorId)
 *  Parameters (in)     : uint8 apiId, pre defined Service ID's of API's in
 *                        the form of macros
 *  Parameters (in)     : uint8 errorId, pre defined error ID's,
 *                        passed as macros
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to report I2C specific development errors
 *  \endverbatim
 */
#if (STD_ON == CDD_I2C_DEV_ERROR_DETECT)
void Cdd_I2cReportDetError(uint8 apiId, uint8 errorId);
#endif

/** \brief Service for Cdd_I2c_Timeout
 *  \verbatim
 *  Service name        : Cdd_I2c_Timeout
 *  Syntax              : uint8 Cdd_I2c_Timeout(uint32 TimeoutPrevious, uint32 TimeoutPeriod)
 *  Parameters (in)     : uint32 TimeoutPrevious, Initial time period marking start of timing period
 *  Parameters (in)     : uint32 TimeoutPeriod, Timeout period
 *  Parameters (out)    : None
 *  Return value        : Timeout success or fail
 *  Description         : Service to report I2C timeouts
 *  \endverbatim
 */
uint8 Cdd_I2c_Timeout(uint32 TimeoutPrevious, uint32 TimeoutPeriod);

/** \brief Service for Cdd_I2c_Setup_HW_Unit_Clk
 *  \verbatim
 *  Service name        : Cdd_I2c_Setup_HW_Unit_Clk
 *  Syntax              : void Cdd_I2c_Setup_HW_Unit_Clk(uint8 HwInstance, uint32 BaudRate, uint32
 * Cdd_I2cHwUnitFrequency, uint32 SysClk) Parameters (in)     : uint8 HwInstance, pre defined
 * hardware instances in the form of macros, passed through the configurator for initialisation
 * purposes Parameters (in)     : uint32 BaudRate, pre defined baud rates, passed through the
 * configurator for I2C bus clock frequency initialisation Parameters (in)     : uint32
 * Cdd_I2cHwUnitFrequency, pre defined I2C HW unit frequency, passed through the configurator for
 * I2C HW unit frequency init Parameters (in)     : uint32 SysClk, pre defined system clock
 * frequency passed to I2c module, passed through the configurator Parameters (out)    : None Return
 * value        : None Description         : Service to initialise and set up I2C instance and
 * driver
 *  \endverbatim
 */
void Cdd_I2c_Setup_HW_Unit_Clk(uint8 HwInstance, uint32 BaudRate, uint32 Cdd_I2cHwUnitFrequency, uint32 SysClk);

/** \brief Service for Cdd_I2c_Clear_interrupts
 *  \verbatim
 *  Service name        : Cdd_I2c_Clear_interrupts
 *  Syntax              : void Cdd_I2c_Clear_interrupts(uint8 HwInstance, uint32 InterruptMask)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *                        for initialisation purposes
 *  Parameters (in)     : uint32 InterruptMask value passed to clear all interrupts
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to clear all I2C interrupts
 *  \endverbatim
 */
void Cdd_I2c_Clear_interrupts(uint8 HwInstance, uint16 InterruptMask);

/** \brief Service for Cdd_I2c_Disable_interrupts
 *  \verbatim
 *  Service name        : Cdd_I2c_Disable_interrupts
 *  Syntax              : void Cdd_I2c_Disable_interrupts(uint8 HwInstance, uint32 InterruptMask)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *                        for initialisation purposes
 *  Parameters (in)     : uint32 InterruptMask value passed to disable all interrupts
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to disable all I2C interrupts
 *  \endverbatim
 */
void Cdd_I2c_Disable_interrupts(uint8 HwInstance, uint16 InterruptMask);

/** \brief Service for Cdd_I2c_Enable_master
 *  \verbatim
 *  Service name        : Cdd_I2c_Enable_master
 *  Syntax              : void Cdd_I2c_Enable_master(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *                        for initialisation purposes
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to initialise the I2C module in master mode,
 *                        free run and bring I2C out of reset
 *  \endverbatim
 */
void Cdd_I2c_Enable_master(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Set_Own_Address
 *  \verbatim
 *  Service name        : Cdd_I2c_Set_Own_Address
 *  Syntax              : void Cdd_I2c_Set_Own_Address(uint8 HwInstance, uint16 address)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *                        for initialisation purposes
 *  Parameters (in)     : uint16 address, I2C slave address of SOC
 *                        initialisation
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to set SOC address in case it is configured as slave, Currently
 * Driver does not support using SOC in slave mode
 *  \endverbatim
 */
void Cdd_I2c_Set_Own_Address(uint8 HwInstance, uint16 address);

/** \brief Service for Cdd_I2c_queue_init
 *  \verbatim
 *  Service name        : Cdd_I2c_queue_init
 *  Syntax              : void Cdd_I2c_queue_init(Cdd_I2c_Queue_obj *pQueue)
 *  Parameters (in)     : Cdd_I2c_Queue_obj *pQueue - pointer to Cdd_I2c Queue
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to initialise queue element values
 *  \endverbatim
 */
void Cdd_I2c_queue_init(Cdd_I2c_Queue_obj *pQueue);

/** \brief Service for Cdd_I2c_Disable_master
 *  \verbatim
 *  Service name        : Cdd_I2c_Disable_master
 *  Syntax              : void Cdd_I2c_Disable_master(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *                        for de-init purposes
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to de-init the I2C module and put HW unit in reset mode
 *  \endverbatim
 */
void Cdd_I2c_Disable_master(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Set_Slave_Addressing_mode
 *  \verbatim
 *  Service name        : Cdd_I2c_Set_Slave_Addressing_mode
 *  Syntax              : void Cdd_I2c_Set_Slave_Addressing_mode(uint8 HwInstance, uint8
 * SlaveAddressScheme) Parameters (in)     : uint8 HwInstance, pre defined hardware instances in the
 * form of macros, passed through the configurator Parameters (in)     : uint8 SlaveAddressScheme,
 * can be either 0 or 1 Parameters (out)    : None Return value        : None Description         :
 * Service to set the slave address mode (7 bit or 10 bit) with which SOC desires to communicate
 *  \endverbatim
 */
void Cdd_I2c_Set_Slave_Addressing_mode(uint8 HwInstance, uint8 SlaveAddressScheme);

/** \brief Service for Cdd_I2c_Set_Slave_Address
 *  \verbatim
 *  Service name        : Cdd_I2c_Set_Slave_Address
 *  Syntax              : void Cdd_I2c_Set_Slave_Address(uint8 HwInstance, Cdd_I2c_AddressType
SlaveAddress)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
*  Parameters (in)      : Cdd_I2c_AddressType SlaveAddress, Address of the slave device
                          with which the SOC desires to communicate
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to set the slave address with which SOC desires to communicate
 *  \endverbatim
*/
void Cdd_I2c_Set_Slave_Address(uint8 HwInstance, Cdd_I2c_AddressType SlaveAddress);

/** \brief Service for Cdd_I2c_Enable_interrupts
 *  \verbatim
 *  Service name        : Cdd_I2c_Enable_interrupts
 *  Syntax              : void Cdd_I2c_Enable_interrupts(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *                        for de-init purposes
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to enable the I2C interrupts
 *  \endverbatim
 */
void Cdd_I2c_Enable_interrupts(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Set_Master_Receive_Mode
 *  \verbatim
 *  Service name        : Cdd_I2c_Set_Master_Receive_Mode
 *  Syntax              : void Cdd_I2c_Set_Master_Receive_Mode(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to set the master(SOC) in receive mode
 *  \endverbatim
 */
void Cdd_I2c_Set_Master_Receive_Mode(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Set_Master_Transmit_Mode
 *  \verbatim
 *  Service name        : Cdd_I2c_Set_Master_Transmit_Mode
 *  Syntax              : void Cdd_I2c_Set_Master_Transmit_Mode(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to set the master(SOC) in transmit mode
 *  \endverbatim
 */
void Cdd_I2c_Set_Master_Transmit_Mode(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Data_Count
 *  \verbatim
 *  Service name        : Cdd_I2c_Data_Count
 *  Syntax              : void Cdd_I2c_Data_Count(uint8 HwInstance, uint16 DataLength)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (in)     : uint16 DataLength, value updated in setupEB function call
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to set the number of bytes to receive or transmit in register
 *  \endverbatim
 */
void Cdd_I2c_Data_Count(uint8 HwInstance, uint16 DataLength);

/** \brief Service for Cdd_I2c_Start
 *  \verbatim
 *  Service name        : Cdd_I2c_Start
 *  Syntax              : void Cdd_I2c_Start(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to send a start condition on I2C bus
 *  \endverbatim
 */
void Cdd_I2c_Start(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Isr_Check
 *  \verbatim
 *  Service name        : Cdd_I2c_Isr_Check
 *  Syntax              : uint16 Cdd_I2c_Isr_Check(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : uint16 register value
 *  Description         : Service to read the I2C status register
 *  \endverbatim
 */
uint16 Cdd_I2c_Isr_Check(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Arbitration_Loss
 *  \verbatim
 *  Service name        : Cdd_I2c_Arbitration_Loss
 *  Syntax              : void Cdd_I2c_Arbitration_Loss(uint8 ChannelId)
 *  Parameters (in)     : uint8 ChannelId, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to report arbitration loss and update channel result
 *  \endverbatim
 */
uint8 Cdd_I2c_Arbitration_Loss(uint8 ChannelId);

/** \brief Service for Cdd_I2c_Get_Sequence_Id
 *  \verbatim
 *  Service name        : Cdd_I2c_Get_Sequence_Id
 *  Syntax              : uint8 Cdd_I2c_Get_Sequence_Id(uint8 HwUnit)
 *  Parameters (in)     : uint8 HwUnit, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to return sequence ID in ISR context
 *  \endverbatim
 */
uint8 Cdd_I2c_Get_Sequence_Id(uint8 HwUnit);

/** \brief Service for Cdd_I2c_Get_Channel_Id
 *  \verbatim
 *  Service name        : Cdd_I2c_Get_Channel_Id
 *  Syntax              : uint8 Cdd_I2c_Get_Channel_Id(uint8 HwUnit, uint8 SequenceId)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (in)     : uint16 SequenceI
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to return Channel ID in ISR context
 *  \endverbatim
 */
uint8 Cdd_I2c_Get_Channel_Id(uint8 HwUnit, uint8 SequenceId);

/** \brief Service for Cdd_I2c_No_Ack
 *  \verbatim
 *  Service name        : Cdd_I2c_No_Ack
 *  Syntax              : void Cdd_I2c_No_Ack(uint8 ChannelId)
 *  Parameters (in)     : uint8 ChannelId, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to report NACK error and update channel result
 *  \endverbatim
 */
uint8 Cdd_I2c_No_Ack(uint8 ChannelId);

/** \brief Service for Cdd_I2c_Shift_Register_Full
 *  \verbatim
 *  Service name        : Cdd_I2c_Shift_Register_Full
 *  Syntax              : void Cdd_I2c_Shift_Register_Full(ChannelId)
 *  Parameters (in)     : uint8 ChannelId, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to report receive shift register full and update channel result
 *  \endverbatim
 */
uint8 Cdd_I2c_Shift_Register_Full(uint8 ChannelId);

/** \brief Service for Cdd_I2c_Stop
 *  \verbatim
 *  Service name        : Cdd_I2c_Stop
 *  Syntax              : void Cdd_I2c_Stop(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to generate a stop condition
 *  \endverbatim
 */
void Cdd_I2c_Stop(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Read
 *  \verbatim
 *  Service name        : Cdd_I2c_Read
 *  Syntax              : uint8 Cdd_I2c_Read(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : 8 bit Data read from I2C bus
 *  Description         : Service to read data from I2C bus
 *  \endverbatim
 */
uint8 Cdd_I2c_Read(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Write
 *  \verbatim
 *  Service name        : Cdd_I2c_Write
 *  Syntax              : void Cdd_I2c_Write(uint8 HwInstance, uint16 Data)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (in)     : uint8 data, Data to be transmitted across the I2C
 *                        bus
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to write data to I2C bus
 *  \endverbatim
 */
void Cdd_I2c_Write(uint8 HwInstance, uint8 Data);

/** \brief Service for Cdd_I2c_Enqueue
 *  \verbatim
 *  Service name        : Cdd_I2c_Enqueue
 *  Syntax              : void Cdd_I2c_Enqueue(uint8 sequenceId)
 *  Parameters (in)     : uint8 sequenceId, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to enqueue a sequence
 *  \endverbatim
 */
void Cdd_I2c_Enqueue(uint8 sequenceId);

/** \brief Service for Cdd_I2cBusCheck
 *  \verbatim
 *  Service name        : Cdd_I2cBusCheck
 *  Syntax              : uint8 Cdd_I2cBusCheck(uint8 HwInstance)
 *  Parameters (in)     : uint8 HwInstance, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : 8 bit bus status from I2C bus
 *  Description         : Service to check whether bus is busy or not
 *  \endverbatim
 */
uint8 Cdd_I2cBusCheck(uint8 HwInstance);

/** \brief Service for Cdd_I2c_Error_Specify
 *  \verbatim
 *  Service name        : Cdd_I2c_Error_Specify
 *  Syntax              : uint8 Cdd_I2c_Error_Specify(uint32 ErrStatus, uint8 ChannelId)
 *  Parameters (in)     : uint32 ErrStatus, return value of Cdd_I2c_Isr_Check API
 *  Parameters (in)     : uint8 ChannelId, pre configured channel passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to find error cause and update channel and sequence result
 * accordingly
 *  \endverbatim
 */
uint8 Cdd_I2c_Error_Specify(uint32 ErrStatus, uint8 ChannelId);

/** \brief Service for Cdd_I2c_Polling_Mode_Receive
 *  \verbatim
 *  Service name        : Cdd_I2c_Polling_Mode_Receive
 *  Syntax              : void Cdd_I2c_Polling_Mode_Receive(uint8 HwUnit, uint8 ChannelId, uint8
 * SequenceId) Parameters (in)     : uint8 HwUnit, Hardware instance of the SOC used, pre-configured
 * through the configurator Parameters (in)     : uint8 ChannelId, pre configured channel passed
 * through the configurator Parameters (in)     : uint8 SequenceId, pre configured sequence passed
 * through the configurator Parameters (out)    : None Return value        : None Description :
 * Service to receive messages in Polling Mode
 *  \endverbatim
 */
void Cdd_I2c_Polling_Mode_Receive(uint8 HwUnit, uint8 ChannelId, uint8 SequenceId);

/** \brief Service for Cdd_I2c_Error_Handler
 *  \verbatim
 *  Service name        : Cdd_I2c_Error_Handler
 *  Syntax              : void Cdd_I2c_Error_Handler(uint32 ErrStatus, uint8 ChannelId, uint8
 * HwUnit) Parameters (in)     : uint32 ErrStatus, value read from I2C ISR status register
 *  Parameters (in)     : uint8 ChannelId, pre configured channel passed through the configurator
 *  Parameters (in)     : uint8 HwUnit, Hardware instance of the SOC used, pre-configured through
 * the configurator Parameters (out)    : None Return value        : None Description         :
 * Service to Handle I2C errors during transmission/reception
 *  \endverbatim
 */
uint8 Cdd_I2c_Error_Handler(uint32 ErrStatus, uint8 ChannelId, uint8 HwUnit);

/** \brief Service for Cdd_I2c_PollingModeProcessingFromQueue
 *  \verbatim
 *  Service name        : Cdd_I2c_PollingModeProcessingFromQueue
 *  Syntax              : void Cdd_I2c_PollingModeProcessingFromQueue(uint8 SequenceId)
 *  Parameters (in)     : uint8 SequenceId, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to receive messages from queued sequences in case of polling mode
 *  \endverbatim
 */
#if (STD_ON == CDD_I2C_POLLING_MODE)
void Cdd_I2c_PollingModeProcessingFromQueue(uint8 SequenceId);
#endif

#if (STD_ON == CDD_I2C_REGISTER_READBACK_API)
FUNC(Std_ReturnType, SPI_CODE)
Cdd_I2c_HWRegisterReadback(uint8 HwInstance, P2VAR(Cdd_I2c_RegisterReadbackType, AUTOMATIC, CDDI2C_APPL_DATA) RegRbPtr);
/**
 *  \brief Returns the the HW object for the corresponding HW unit ID
 */
uint32 Cdd_I2c_getHwUnitObj(uint8 HwInstance);

void Cdd_I2cRegReadback(const uint32 hwUnitObj, Cdd_I2c_RegisterReadbackType *RegRbPtr);
#endif /* #if (STD_ON == CDD_I2C_REGISTER_READBACK_API) */

/** \brief Service for Cdd_I2c_Isr_Handler
 *  \verbatim
 *  Service name        : Cdd_I2c_Isr_Handler
 *  Syntax              : void Cdd_I2c_Isr_Handler(uint8 HwUnit)
 *  Parameters (in)     : uint8 HwUnit, pre defined hardware instances in
 *                        the form of macros, passed through the configurator
 *  Parameters (out)    : None
 *  Return value        : None
 *  Description         : Service to handle ISR
 *  \endverbatim
 */
#if (STD_OFF == CDD_I2C_POLLING_MODE)
void Cdd_I2c_Isr_Handler(uint8 HwUnit, uint8 *pDataReceiveBuffer, uint32 *pDataReceiveBufferIndex,
                         uint16 *pDataBufferLength);
#endif

#endif
