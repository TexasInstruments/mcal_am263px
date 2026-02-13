/** @file sys_core.h
 *   @brief System Core Header File
 *   @date 17.Nov.2014
 *   @version 04.02.00
 *
 *   This file contains:
 *   - Core Interface Functions
 *   .
 *   which are relevant for the System driver.
 */

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

#ifndef SYS_CORE_H
#define SYS_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

/** @def sysDELAY_MIN_CHECK
 *   @brief Checks if argument to delay routine is higher than min value
 *
 *   If the value is lower the minimum value then it substitutes with min value
 */
#define sysDELAY_MIN_CHECK(value) ((value) > (5U) ? (value) : (5U))

/** @def sysDELAY
 *   @brief Delay Macro
 *
 *   This macro provides delay in resolution of 20ns
 *   Minimum delay is ~150ns
 *   e.g sysDELAY(50) gives a delay of 50*20ns = 1us
 *   Delay can be off by ~100ns
 */
#define sysDELAY(delayValue) _sysDelay_(sysDELAY_MIN_CHECK(delayValue))

/*! \brief
 * Software abort type
 */
typedef enum
{
    E_FAULT_UDEF_INSTR   = 0x0,
    E_FAULT_PREF_ABORT   = 0x1,
    E_FAULT_DATA_ABORT   = 0x2,
    E_FAULT_SW_FATAL_ERR = 0x3,
    E_FAULT_INVALID      = 0xFF
} E_FW_FAULT_TYPE;

typedef enum
{
    E_FSR_BACKGROUND_ERR   = 0x000U,
    E_FSR_ALIGNMENT_ERR    = 0x001U,
    E_FSR_DEBUG_EVENT      = 0x002U,
    E_FSR_PERMISSION_ERR   = 0x00DU,
    E_FSR_SYNCH_EXTER_ERR  = 0x008U,
    E_FSR_ASYNCH_EXTER_ERR = 0x406U,
    E_FSR_SYNCH_ECC_ERR    = 0x409U,
    E_FSR_ASYNCH_ECC_ERR   = 0x408U,
    E_FSR_ST_INVALID       = 0xFFFFU
} E_DIFSR_ERR_STATUS;

/*! \brief
 * ARM R4 Aux Fault status registers bitwise enum values
 */
typedef enum
{
    E_FSR_ERR_SOURCE_AXI_MASTER = 0x0U,
    E_FSR_ERR_SOURCE_ATCM       = 0x1U,
    E_FSR_ERR_SOURCE_BTCM       = 0x2U,
    E_FSR_SRC_INVALID           = 0xFFU
} E_ADIFSR_ERR_SOURCE;

/*! \brief
 * ARM R4 Fault status registers bitwise enum values
 */
typedef enum
{
    E_FSR_SD_AXI_DECOD_ERR = 0x0U,
    E_FSR_SD_AXI_SLAVE_ERR = 0x1U,
    E_FSR_SD_INVALID       = 0xFFU
} E_DIFSR_SD;

typedef enum
{
    E_DFSR_RW_READ_ERR  = 0x0U,
    E_DFSR_RW_WRITE_ERR = 0x1U,
    E_FSR_RW_INVALID    = 0xFFU
} E_DFSR_RW;

typedef enum
{
    E_FSR_ERR_UNRECOVERY = 0x0U,
    E_FSR_ERR_RECOVERY   = 0x1U,
    E_FSR_RECO_INVALID   = 0xFFU
} E_ADIFSR_ERR_RECOV;

#define M_ASM_STATEMENT(statement) asm(statement)

/* System Core Interface Functions */

/** @fn void _coreInitRegisters_(void)
 *   @brief Initialize Core register
 */
void _coreInitRegisters_(void);

/** @fn void _coreInitStackPointer_(void)
 *   @brief Initialize Core stack pointer
 */
void _coreInitStackPointer_(void);

/** @fn void _getCPSRValue_(void)
 *   @brief Get CPSR Value
 */
uint32 _getCPSRValue_(void);

/** @fn void _gotoCPUIdle_(void)
 *   @brief Take CPU to Idle state
 */
void _gotoCPUIdle_(void);

/** @fn void _coreEnableIrqVicOffset_(void)
 *   @brief Enable Irq offset propagation via Vic controller
 */
void _coreEnableIrqVicOffset_(void);

/** @fn void _coreEnableVfp_(void)
 *   @brief Enable vector floating point unit
 */
void _coreEnableVfp_(void);

/** @fn void _coreEnableEventBusExport_(void)
 *   @brief Enable event bus export for external monitoring modules
 *   @note It is required to enable event bus export to process ecc issues.
 *
 *   This function enables event bus exports to external monitoring modules
 *   like tightly coupled RAM wrapper, Flash wrapper and error signaling module.
 */
void _coreEnableEventBusExport_(void);

/** @fn void _coreDisableEventBusExport_(void)
 *   @brief Disable event bus export for external monitoring modules
 *
 *   This function disables event bus exports to external monitoring modules
 *   like tightly coupled RAM wrapper, Flash wrapper and error signaling module.
 */
void _coreDisableEventBusExport_(void);

/** @fn void _coreEnableRamEcc_(void)
 *   @brief Enable external ecc error for RAM odd and even bank
 *   @note It is required to enable event bus export to process ecc issues.
 */
void _coreEnableRamEcc_(void);

/** @fn void _coreDisableRamEcc_(void)
 *   @brief Disable external ecc error for RAM odd and even bank
 */
void _coreDisableRamEcc_(void);

/** @fn void _coreEnableTCMAEcc_(void)
 *   @brief Enable external ecc error for the Flash
 *   @note It is required to enable event bus export to process ecc issues.
 */
void _coreEnableTCMAEcc_(void);

/** @fn void _coreDisableTCMAEcc_(void)
 *   @brief Disable external ecc error for the Flash
 */
void _coreDisableTCMAEcc_(void);

/** @fn uint32 _coreGetDataFault_(void)
 *   @brief Get core data fault status register
 *   @return The function will return the data fault status register value:
 *           - bit [10,3..0]:
 *                            - 0b00001: Alignment                -> address is valid
 *                            - 0b00000: Background               -> address is valid
 *                            - 0b01101: Permission               -> address is valid
 *                            - 0b01000: Precise External Abort   -> address is valid
 *                            - 0b10110: Imprecise External Abort -> address is unpredictable
 *                            - 0b11001: Precise ECC Error        -> address is valid
 *                            - 0b11000: Imprecise ECC Error      -> address is unpredictable
 *                            - 0b00010: Debug                    -> address is unchanged
 *           - bit [11]:
 *                            - 0: Read
 *                            - 1: Write
 *           - bit [12]:
 *                            - 0: AXI Decode Error (DECERR)
 *                            - 1: AXI Slave Error (SLVERR)
 */
uint32 _coreGetDataFault_(void);

/** @fn void _coreClearDataFault_(void)
 *   @brief Clear core data fault status register
 */
void _coreClearDataFault_(void);

/** @fn uint32 _coreGetInstructionFault_(void)
 *   @brief Get core instruction fault status register
 *   @return The function will return the instruction fault status register value:
 *           - bit [10,3..0]:
 *                            - 0b00001: Alignment                -> address is valid
 *                            - 0b00000: Background               -> address is valid
 *                            - 0b01101: Permission               -> address is valid
 *                            - 0b01000: Precise External Abort   -> address is valid
 *                            - 0b10110: Imprecise External Abort -> address is unpredictable
 *                            - 0b11001: Precise ECC Error        -> address is valid
 *                            - 0b11000: Imprecise ECC Error      -> address is unpredictable
 *                            - 0b00010: Debug                    -> address is unchanged
 *           - bit [12]:
 *                            - 0: AXI Decode Error (DECERR)
 *                            - 1: AXI Slave Error (SLVERR)
 */
uint32 _coreGetInstructionFault_(void);

/** @fn void _coreClearInstructionFault_(void)
 *   @brief Clear core instruction fault status register
 */
void _coreClearInstructionFault_(void);

/** @fn uint32 _coreGetDataFaultAddress_(void)
 *   @brief Get core data fault address register
 *   @return The function will return the data fault address:
 */
uint32 _coreGetDataFaultAddress_(void);

/** @fn void _coreClearDataFaultAddress_(void)
 *   @brief Clear core data fault address register
 */
void _coreClearDataFaultAddress_(void);

/** @fn uint32 _coreGetInstructionFaultAddress_(void)
 *   @brief Get core instruction fault address register
 *   @return The function will return the instruction fault address:
 */
uint32 _coreGetInstructionFaultAddress_(void);

/** @fn void _coreClearInstructionFaultAddress_(void)
 *   @brief Clear core instruction fault address register
 */
void _coreClearInstructionFaultAddress_(void);

/** @fn uint32 _coreGetAuxiliaryDataFault_(void)
 *   @brief Get core auxiliary data fault status register
 *   @return The function will return the auxiliary data fault status register value:
 *           - bit [13..5]:
 *                            - Index value for access giving error
 *           - bit [21]:
 *                            - 0: Unrecoverable error
 *                            - 1: Recoverable error
 *           - bit [23..22]:
 *                            - 0: Side cache
 *                            - 1: Side ATCM (Flash)
 *                            - 2: Side BTCM (RAM)
 *                            - 3: Reserved
 *           - bit [27..24]:
 *                            - Cache way or way in which error occurred
 */
uint32 _coreGetAuxiliaryDataFault_(void);

/** @fn void _coreClearAuxiliaryDataFault_(void)
 *   @brief Clear core auxiliary data fault status register
 */
void _coreClearAuxiliaryDataFault_(void);

/** @fn uint32 _coreGetAuxiliaryInstructionFault_(void)
 *   @brief Get core auxiliary instruction fault status register
 *   @return The function will return the auxiliary instruction fault status register value:
 *           - bit [13..5]:
 *                            - Index value for access giving error
 *           - bit [21]:
 *                            - 0: Unrecoverable error
 *                            - 1: Recoverable error
 *           - bit [23..22]:
 *                            - 0: Side cache
 *                            - 1: Side ATCM (Flash)
 *                            - 2: Side BTCM (RAM)
 *                            - 3: Reserved
 *           - bit [27..24]:
 *                            - Cache way or way in which error occurred
 */
uint32 _coreGetAuxiliaryInstructionFault_(void);

/** @fn void _coreClearAuxiliaryInstructionFault_(void)
 *   @brief Clear core auxiliary instruction fault status register
 */
void _coreClearAuxiliaryInstructionFault_(void);

/** @fn void _disable_interrupt_(void)
 *   @brief Disable IRQ and FIQ Interrupt mode in CPSR register
 *
 *   This function disables IRQ and FIQ Interrupt mode in CPSR register.
 */
void _disable_interrupt_(void);

/** @fn void _disable_IRQ_interrupt_(void)
 *   @brief Disable IRQ Interrupt mode in CPSR register
 *
 *   This function disables IRQ Interrupt mode in CPSR register.
 */
void _disable_IRQ_interrupt_(void);

/** @fn void _disable_FIQ_interrupt_(void)
 *   @brief Disable FIQ Interrupt mode in CPSR register
 *
 *   This function disables IRQ Interrupt mode in CPSR register.
 */
void _disable_FIQ_interrupt_(void);

/** @fn void _enable_interrupt_(void)
 *   @brief Enable IRQ and FIQ Interrupt mode in CPSR register
 *
 *   This function Enables IRQ and FIQ Interrupt mode in CPSR register.
 *   User must call this function to enable Interrupts in non-OS environments.
 */
void _enable_interrupt_(void);

/** @fn void _esmCcmErrorsClear_(void)
 *   @brief Clears ESM Error caused due to CCM Errata in RevA Silicon
 *
 *   This function Clears ESM Error caused due to CCM Errata
 *   in RevA Silicon immediately after powerup.
 */
void _esmCcmErrorsClear_(void);

/** @fn void _errata_CORTEXR4_66_(void)
 *   @brief Work Around for Errata CORTEX-R4#66
 *
 *   This function Disable out-of-order completion for divide
 *   instructions in Auxiliary Control register.
 */
void _errata_CORTEXR4_66_(void);

/** @fn void _errata_CORTEXR4_57_(void)
 *   @brief Work Around for Errata CORTEX-R4#57
 *
 *   Disable out-of-order single-precision floating point
 *   multiply-accumulate instruction completion.
 */
void _errata_CORTEXR4_57_(void);

/** @fn void _sysSCTRLRegWrite_(void)
 *   @brief This function writes value into masked location from the start bit
 *          for system control register
 *   @note  Assumes  :   r0 - start bit
 *                       r1 - mask
 *                       r2 - value
 *
 */
void _sysSCTRLRegWrite_(void);

/** @fn void _sysAuxCTRLRegWrite_(void)
 *   @brief This function writes value into masked location from the start bit
 *          for auxilary control register
 *   @note  Assumes  :   r0 - start bit
 *                       r1 - mask
 *                       r2 - value
 *
 */
void _sysAuxCTRLRegWrite_(void);

/** @fn void _sysSecAuxCTRLRegWrite_(void)
 *   @brief This function writes value into masked location from the start bit
 *          for secondary auxilary control register
 *   @note  Assumes  :   r0 - start bit
 *                       r1 - mask
 *                       r2 - value
 *
 */
void _sysSecAuxCTRLRegWrite_(void);

/** @fn void _sysDelay_(uint32 delay20ns)
 *   @brief This function is used for generating delays using nop
 *   @note  Assumes  :   r0 - delay value in 20ns resolution
 *                       Value should be greater than 5
 *
 */
void _sysDelay_(uint32 delay20ns);

#ifdef __cplusplus
}
#endif

#endif
