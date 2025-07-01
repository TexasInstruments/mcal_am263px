/** @file sys_vim.h
 *   @brief Vectored Interrupt Module Header File
 *   @date 16.Mar.2015
 *   @version 01.00.00
 *
 *   This file contains:
 *   - VIM Type Definitions
 *   - VIM General Definitions
 *   .
 *   which are relevant for Vectored Interrupt Controller.
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

#ifndef SYS_VIM_H
#define SYS_VIM_H

#include "sys_common.h"

#define CSL_VIM_NUM_GROUPS          (16U)
#define CSL_VIM_NUM_INTS_PER_GROUPS (32U)
#define CSL_VIM_MAX_NUM_INTERRUPTS  (256U)

/**
 * @brief
 *  VIM group
 *
 * @details
 *  The structure defines the registers for a vim group.
 *
 */
typedef struct VIMGrp_t
{
    uint32 rawStatusSet;          /**< @brief 0x0000 Interrupt raw status/set register */
    uint32 enabledStatusClear;    /**< @brief 0x0004 Interrupt enabled status/clear register */
    uint32 enabledSet;            /**< @brief 0x0008 Interrupt enabled set register */
    uint32 enabledClear;          /**< @brief 0x000c Interrupt enabled clear register */
    uint32 irqEnabledStatusClear; /**< @brief 0x0010 Interrupt IRQ enabled status/clear register */
    uint32 fiqEnabledStatusClear; /**< @brief 0x0014 Interrupt FIQ enabled status/clear register */
    uint32 map;                   /**< @brief 0x0018 Interrupt map register */
    uint32 type;                  /**< @brief 0x001c Interrupt type register */
} VIMGrp;

/**
 * @brief
 *  VIM Register Layer
 *
 * @details
 *  The structure defines the layout of the registers for the VIM module.
 *  The structure includes the ECC related and control registers.
 *
 *  \ingroup CSL_REGISTER_LAYER
 */
typedef volatile struct VIMRegs_t
{
    uint32 revision;         /**< 0x0000 Revision register */
    uint32 info;             /**< 0x0004 Info register */
    uint32 prioritizedIrq;   /**< 0x0008 Prioritized IRQ register */
    uint32 prioritizedFiq;   /**< 0x000c Prioritized FIQ register */
    uint32 irqGroupStatus;   /**< 0x0010 IRQ group status regsiter */
    uint32 fiqGroupStatus;   /**< 0x0014 FIQ group status register */
    uint32 irqVectorAddress; /**< 0x0018 IRQ vector address register */
    uint32 fiqVectorAddress; /**< 0x001c FIQ vector address register */
    uint32 activeIrq;        /**< 0x0020 Active IRQ register */
    uint32 activeFiq;        /**< 0x0024 Active FIQ register */
    uint32 rsvd0[2];         /**< 0x0028 Reserved */
    uint32 ded;              /**< 0x0030 DED vector address register */
    uint32 rsvd1[243];       /**< <0x0034 reserved */

    VIMGrp group[CSL_VIM_NUM_GROUPS]; /**< 0x0400 Group configuration */
    uint32 rsvd2[640];                /**< 0x0500 Reserved */

    uint32 priority[CSL_VIM_MAX_NUM_INTERRUPTS]; /**< 0x1000 Interrupt priority register */
    uint32 rsvd3[768];
    uint32 vecAddr[CSL_VIM_MAX_NUM_INTERRUPTS]; /**< 0x2000 Interrupt vector register */
} VIMRegs;

/* VIM Type Definitions */

/** @typedef VIM_InterruptHandler
 *   @brief ISR Function Pointer Type Definition
 *
 *   This type is used to access the ISR handler.
 */
typedef void (*VIM_InterruptHandler)(void);

/** @typedef Vim_IntType
 *  @brief VIM interrupt type
 *
 *  @details
     Enumeration which describes the mapping of a VIM interrupt (IRQ or FIQ)
 */
typedef enum Vim_IntType_e
{
    /**
     * @brief   IRQ type interrupt
     */
    VIM_INTTYPE_IRQ = 0,

    /**
     * @brief   FIQ type interrupt
     */
    VIM_INTTYPE_FIQ = 1
} Vim_IntType;

/**
 * @brief VIM interrupt trigger type (level or pulse)
 *
 * @details
    Enumeration which describes the type of trigger for a VIM interrupt
 */
typedef enum Vim_IntTrigType_e
{
    /**
     * @brief   Level triggered interrupt
     */
    VIM_INTTRIGTYPE_LEVEL = 0U,

    /**
     * @brief   Pulse triggered interrupt
     */
    VIM_INTTRIGTYPE_PULSE = 1U
} Vim_IntTrigType;

/**
 * @brief VIM interrupt configuration
 *
 * @details
    Structure which holds the configuration for a VIM interrupt
 */
typedef struct Vim_IntCfg_t
{
    /**
     * @brief   Interrupt vector number
     */
    uint32 intNum;

    /**
     * @brief   Interrupt map type (IRQ or FIQ)
     */
    Vim_IntType map;

    /**
     * @brief   Interrupt trigger type (Level or Pulse)
     */
    Vim_IntTrigType type;

    /**
     * @brief   Interrupt priority (0 = highest, 15 = lowest)
     */
    uint32 priority;

    /**
     * @brief   Pointer to the interrupt handler. Must be 4 byte aligned
     */
    VIM_InterruptHandler handler;
} Vim_IntCfg;

/* Interrupt Handlers */

void sysphantomInterrupt(void);

/**
 * @defgroup VIM VIM
 * @brief Vectored Interrupt Manager
 *
 * The vectored interrupt manager (VIM) provides hardware assistance for prioritizing and
 * controlling the many interrupt sources present on a device. Interrupts are caused by events
 * outside of the normal flow of program execution.
 *
 * Related files:
 * - reg_vim.h
 * - sys_vim.h
 * - sys_vim.c
 *
 * @addtogroup VIM
 * @{
 */
/*VIM Interface functions*/
void vimInit(void);
void vimInterruptsInit(void);
void vimRegisterInterrupt(const Vim_IntCfg *intCfg);
void vimEnableInterrupt(uint32 intNum);
void vimDisableInterrupt(uint32 intNum);
void vimTriggerSoftInt(uint32 intNum);
void vimIrqDispatcher(void);
void vimFiqDispatcher(void);
void enableDisableIrqFiq(uint32 option);

/*@}*/
#endif
