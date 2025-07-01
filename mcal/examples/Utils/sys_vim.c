/** @file sys_vim.c
 *   @brief VIM Driver Implementation File
 *   @date 3.June.2020
 *   @version 02.00.00
 *
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
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF UE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "Std_Types.h"

/* Include Header Files */
#include "sys_vim.h"
#include "sys_common.h"
#include "hw_ctrl_core.h"
#include "hal_stdtypes.h"
#include "esm.h"

/* compile flag to enable or disable interrupt nesting */
#define MCAL_NESTED_INTERRUPTS_IRQ_ENABLE

extern void armR5EnableIrqFiq(void);
extern void CSL_armR5IntrEnableIrq(uint32 enable);
extern void CSL_armR5IntrEnableFiq(uint32 enable);
extern void CSL_armR5IntrEnableVic(uint32 enable);
typedef struct DrvVim_Stats_t
{
    /**
     * @brief   Spurious IRQ interrupt counter
     */
    uint32 spuriousIrqCnt;

    /**
     * @brief   Spurious FIQ interrupt counter
     */
    uint32 spuriousFiqCnt;

} DrvVim_Stats;

DrvVim_Stats gDrvVim_Stats = {0};

#if defined(CLANG) || defined(DIAB)
void vimFiqDispatcher(void) __attribute__((target("arm"))) __attribute__((section(".startup.vimFiqDispatcher")));
#else
#pragma CODE_STATE(vimFiqDispatcher, 32)
#pragma CODE_SECTION(vimFiqDispatcher, ".startup")
#endif

void vimFiqDispatcher(void)
{
    VIMRegs             *ptrVIMRegs;
    VIM_InterruptHandler interruptHandler;
    uint16               irqNum;
    uint8                groupIdx;
    uint8                bit;

    /* Get the VIM Base Address & RAM Address: */
    ptrVIMRegs = (VIMRegs *)vimREG;

    /* Get the interrupt vector : */
    interruptHandler = (VIM_InterruptHandler)(ptrVIMRegs->fiqVectorAddress);

    irqNum = (uint16)(ptrVIMRegs->activeFiq & 0x3FFU);

    /* Locate the group number and bit position */
    groupIdx = (uint8)(irqNum >> 5U);
    bit      = (uint8)(irqNum & 0x1FU);

    if ((ptrVIMRegs->group[groupIdx].type & ((uint32)0x1U << bit)) == ((uint32)VIM_INTTRIGTYPE_PULSE << bit))
    {
        /* Clear pulse interrupt */
        ptrVIMRegs->group[groupIdx].enabledStatusClear = (uint32)0x1U << bit;
    }

    if ((ptrVIMRegs->activeFiq & 0x80000000U) == 0U)
    {
        gDrvVim_Stats.spuriousFiqCnt++;
    }
    else
    {
        /* Get the interrupt handler: */
        if (interruptHandler != (VIM_InterruptHandler)NULL)
        {
            /* Call the interrupt handler:
              NOTE: clear interrupt at the source in this ISR function */
            (interruptHandler)();
        }
        else
        {
            /* Fatal error : valid interrupt, but invalid vector */
        }
    }
    if ((ptrVIMRegs->group[groupIdx].type & ((uint32)0x1U << bit)) == ((uint32)VIM_INTTRIGTYPE_LEVEL << bit))
    {
        /* Clear level interrupt */
        ptrVIMRegs->group[groupIdx].enabledStatusClear = (uint32)0x1U << bit;
    }

    /* Write any value to the irq vector address to allow the next interrupt */
    ptrVIMRegs->fiqVectorAddress = (uint32)bit;
}

#if defined(CLANG) || defined(DIAB)
void vimIrqDispatcher(void) __attribute__((target("arm"))) __attribute__((section(".startup.vimIrqDispatcher")));
#else
#pragma CODE_STATE(vimIrqDispatcher, 32)
#pragma CODE_SECTION(vimIrqDispatcher, ".startup")
#endif

void vimIrqDispatcher(void)
{
    VIMRegs             *ptrVIMRegs;
    VIM_InterruptHandler interruptHandler;
    uint16               irqNum;
    uint8                groupIdx;
    uint8                bit;

    /* Get the VIM Base Address & RAM Address: */
    ptrVIMRegs = (VIMRegs *)vimREG;

    /* Get the interrupt vector : */
    interruptHandler = (VIM_InterruptHandler)(ptrVIMRegs->irqVectorAddress);

    irqNum = (uint16)(ptrVIMRegs->activeIrq & 0x3FFU);

    /* Locate the group number and bit position */
    groupIdx = (uint8)(irqNum >> 5U);
    bit      = (uint8)(irqNum & 0x1FU);

    if ((ptrVIMRegs->group[groupIdx].type & ((uint32)0x1U << bit)) == ((uint32)VIM_INTTRIGTYPE_PULSE << bit))
    {
        /* Clear pulse interrupt */
        ptrVIMRegs->group[groupIdx].enabledStatusClear = (uint32)0x1U << bit;
    }
    if ((ptrVIMRegs->activeIrq & 0x80000000U) == 0U)
    {
        gDrvVim_Stats.spuriousIrqCnt++;
    }
    else
    {
#ifdef MCAL_NESTED_INTERRUPTS_IRQ_ENABLE
        /* allow nesting of interrupts */
        enableDisableIrqFiq(1);
#endif
        /* Get the interrupt handler: */
        if (interruptHandler != (VIM_InterruptHandler)NULL)
        {
            /* Call the interrupt handler:
              NOTE: clear interrupt at the source in this ISR function */
            (interruptHandler)();
        }
        else
        {
            /* Fatal error : valid interrupt, but invalid vector */
        }
        /* disallow nesting of interrupts */
        enableDisableIrqFiq(4);
    }
    if ((ptrVIMRegs->group[groupIdx].type & ((uint32)0x1U << bit)) == ((uint32)VIM_INTTRIGTYPE_LEVEL << bit))
    {
        /* Clear level interrupt */
        ptrVIMRegs->group[groupIdx].enabledStatusClear = (uint32)0x1U << bit;
    }

    /* Write any value to the irq vector address to allow the next interrupt */
    ptrVIMRegs->irqVectorAddress = (uint32)bit;
}

/** @fn void vimInit(void)
 *   @brief Initializes VIM module
 *
 *   This function initializes VIM registers
 */
/* SourceId : VIM_SourceId_001 */
/* DesignId : VIM_DesignId_001 */
/* Requirements : HL_SR100 */
void vimInit(void)
{
    VIMRegs *ptrVIMRegs;
    uint32   numInts;
    uint32   intIdx;
    uint32   grpIdx;

    /* Disable the IRQ/FIQ Interrupts */
    CSL_armR5IntrEnableFiq(1);
    CSL_armR5IntrEnableIrq(1);
    CSL_armR5IntrEnableVic(0);
    /* Get base address of VIM module */
    ptrVIMRegs = (VIMRegs *)vimREG;

    /* The number of supported interrupts is read from the VIM info register */
    numInts = ptrVIMRegs->info & 0x7FFU;

    /* Disable all interrupts */
    vimInterruptsInit();

    /* Program the DED vector */
    ptrVIMRegs->ded = (uint32)&sysphantomInterrupt;

    /* Initialize vim group registers with following defaults:
       - interrupt trigger type: level
       - interrupt type : IRQ
    */
    for (grpIdx = 0U; grpIdx < CSL_VIM_NUM_GROUPS; grpIdx++)
    {
        ptrVIMRegs->group[grpIdx].type = 0U;
        ptrVIMRegs->group[grpIdx].map  = 0U;
    }

    /* Initialize the vector(NULL) and priority registers , keep prioriy as lowest level(15) */
    for (intIdx = 0U; intIdx < numInts; intIdx++)
    {
        ptrVIMRegs->vecAddr[intIdx]  = (uint32)NULL;
        ptrVIMRegs->priority[intIdx] = 15U;
    }
}

/** @fn void vimInterruptsInit(void)
 *   @brief Initialise the VIM channels
 *
 *
 *   This function will initialise the vim channels.
 *
 */
/* SourceId : */
/* DesignId : */
/* Requirements : */
void vimInterruptsInit(void)
{
    VIMRegs *ptrVIMRegs;
    uint32   numInts;
    uint32   grpIdx;
    uint32   intIdx, j;
    uint32   mask;

    ptrVIMRegs = (VIMRegs *)vimREG;

    /* The number of supported interrupts is read from the VIM info register */
    numInts = ptrVIMRegs->info & 0x7FFU;

    intIdx = 0;

    /* Disable all interrupts in all groups with 32 interrupts in each group */
    for (grpIdx = 0U; grpIdx < CSL_VIM_NUM_GROUPS; grpIdx++)
    {
        mask = 0U;
        for (j = 0U; (j < 32U) && (intIdx < numInts); j++)
        {
            mask = (mask << 1U) | 1U;

            intIdx++;
        }
        ptrVIMRegs->group[grpIdx].enabledClear = mask;
    }
}

/** @fn void vimRegisterInterrupt(const Vim_IntCfg *intCfg)
 *   @brief The function is used to configure and enable an interrupt
 *
 *   @param[in] intCfg       Interrupt confuration
 *
 */
/* SourceId : VIM_SourceId_002 */
/* DesignId : VIM_DesignId_002 */
/* Requirements : HL_SR101 */
void vimRegisterInterrupt(const Vim_IntCfg *intCfg)
{
    VIMRegs *ptrVIMRegs;
    uint32   groupIdx;
    uint8    bit;

    /* Get base address of VIM module */
    ptrVIMRegs = (VIMRegs *)vimREG;

    /* Locate the group number and bit position */
    groupIdx = intCfg->intNum >> 5U;
    bit      = (uint8)(intCfg->intNum & 0x1FU);

    /* Clear the enable */
    ptrVIMRegs->group[groupIdx].enabledClear = ((uint32)0x1U << bit);

    /* Map setup (fiq vs irq) */
    regWriteReadback(&ptrVIMRegs->group[groupIdx].map, bit, bit, (uint32)intCfg->map);

    /* Type setup (level vs pulse) */
    regWriteReadback(&ptrVIMRegs->group[groupIdx].type, bit, bit, (uint32)intCfg->type);

    /* Priority setup */
    ptrVIMRegs->priority[intCfg->intNum] = intCfg->priority;

    /* Vector base */
    ptrVIMRegs->vecAddr[intCfg->intNum] = (uint32)intCfg->handler;

    /* Set the enable bit*/
    ptrVIMRegs->group[groupIdx].enabledSet = ((uint32)0x1U << bit);
}

/** @fn void vimEnableInterrupt(uint32 intNum)
 *   @brief Enable interrupt for the the selected channel
 *
 *    @param[in] intNum: VIM interrupt number 2..256
 *
 *   This function will enable interrupt for the selected intrrupt
 *
 */
/* SourceId : VIM_SourceId_003 */
/* DesignId : VIM_DesignId_003 */
/* Requirements : HL_SR102 */
void vimEnableInterrupt(uint32 intNum)
{
    VIMRegs *ptrVIMRegs;
    uint32   groupIdx;
    uint32   bit;

    /* Get base address of VIM module */
    ptrVIMRegs = (VIMRegs *)vimREG;

    /* Locate the group number and bit position */
    groupIdx = intNum >> 5U;
    bit      = (intNum & 0x1FU);

    /* Set the enable bit*/
    ptrVIMRegs->group[groupIdx].enabledSet = ((uint32)0x1U << bit);
}

/** @fn void vimDisableInterrupt(uint32 intNum)
 *   @brief Disable interrupt for the the selected channel
 *
 *    @param[in] channel: VIM interrupt number 2..256
 *
 *   This function will disable interrupt for the selected channel.
 *
 */
/* SourceId : VIM_SourceId_004 */
/* DesignId : VIM_DesignId_004 */
/* Requirements : HL_SR103 */
void vimDisableInterrupt(uint32 intNum)
{
    VIMRegs *ptrVIMRegs;
    uint32   groupIdx;
    uint32   bit;

    /* Get base address of VIM module */
    ptrVIMRegs = (VIMRegs *)vimREG;

    /* Locate the group number and bit position */
    groupIdx = intNum >> 5U;
    bit      = (intNum & 0x1FU);

    /* Clear the enable */
    ptrVIMRegs->group[groupIdx].enabledClear = ((uint32)0x1U << bit);
}

/** @fn void vimTriggerSoftInt(uint32 intNum)
 *   @brief Trigger Software interrupt for given channel
 *
 *   @param[in] intNum: vim interrupt number
 *
 *   This function will trigger software interrupt
 *
 */
/* SourceId :  */
/* DesignId : */
/* Requirements : */
void vimTriggerSoftInt(uint32 intNum)
{
    VIMRegs *ptrVIMRegs;
    uint32   groupIdx;
    uint32   bit;

    /* Get base address of VIM module */
    ptrVIMRegs = (VIMRegs *)vimREG;

    /* Locate the group number and bit position */
    groupIdx = intNum >> 5U;
    bit      = (intNum & 0x1FU);

    /* Set the raw status bit */
    ptrVIMRegs->group[groupIdx].rawStatusSet = ((uint32)0x1U << bit);
}

/** @fn void sysphantomInterrupt(void)
 *   @brief This ISR is a default phanthom ISR routine, when
 *                       VIM fails to read right channel or index is not updated
 *                       it fetches the RAM 0, that is phantom interrupt
 *
 *
 */
/* SourceId : */
/* DesignId :  */
/* Requirements : */
void sysphantomInterrupt(void)
{
    /*
     * Dummy phantom intrrupt routine - just return.
     */
}
#ifndef DIAB
/** @fn void enableDisableIrqFiq(uint32 option)
 *   @brief This is C function is to enable or disable the interrupts.
 *
 *    @param[in] option: Input to enable/disable interrupts
 *
 */
/* SourceId : */
/* DesignId :  */
/* Requirements : */
void enableDisableIrqFiq(uint32 option)
{
    switch (option)
    {
        case 1U:
            /* enable IRQ interrupt */
            asm(" mrs   r0, cpsr");
            asm(" bic   r12, r0, #0x80");
            asm(" msr   cpsr_cf, r12");
            break;

        case 2U:
            /* enable FIQ interrupt */
            asm(" mrs   r0, cpsr");
            asm(" bic   r12, r0, #0x40");
            asm(" msr   cpsr_cf, r12");
            break;

        case 3U:
            /* enable both interrupts */
            asm(" mrs   r0, cpsr");
            asm(" bic   r12, r0, #0xC0");
            asm(" msr   cpsr_cf, r12");
            break;

        case 4U:
            /* disable IRQ interrupt */
            asm(" mrs   r0, cpsr");
            asm(" orr   r12, r0, #0x80");
            asm(" msr   cpsr_cf, r12");
            break;

        case 5U:
            /* disable FIQ interrupt */
            asm(" mrs   r0, cpsr");
            asm(" orr   r12, r0, #0x40");
            asm(" msr   cpsr_cf, r12");
            break;
        case 6U:
            /* disable both interrupts */
            asm(" mrs   r0, cpsr");
            asm(" orr   r12, r0, #0xC0");
            asm(" msr   cpsr_cf, r12");
            break;
        default:
            /* not a valid interrupt */
            break;
    }
}
#endif
