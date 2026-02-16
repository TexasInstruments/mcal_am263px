/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2018-2021 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

        .text

/* FUNCTION DEF: uint32_t HwiP_disable(void) */
        .global HwiP_disable
        .type HwiP_disable,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_disable:
        mrs     r0, cpsr
        orr     r12, r0, #0x80
        msr     cpsr_cf, r12
        bx      LR

/* FUNCTION DEF: uint32_t HwiP_disableFIQ(void) */
        .global HwiP_disableFIQ
        .type HwiP_disableFIQ,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_disableFIQ:
        mrs     r0, cpsr
        orr     r12, r0, #0x40
        msr     cpsr_cf, r12
        bx      LR

/* FUNCTION DEF: void HwiP_enable() */
        .global HwiP_enable
        .type HwiP_enable,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_enable:
        mrs     r0, cpsr
        bic     r12, r0, #0x80
        msr     cpsr_cf, r12
        bx      LR

/* FUNCTION DEF: void HwiP_enableFIQ() */
        .global HwiP_enableFIQ
        .type   HwiP_enableFIQ,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_enableFIQ:
        mrs     r0, cpsr
        bic     r12, r0, #0x40
        msr     cpsr_cf, r12
        bx      LR

/* FUNCTION DEF: void HwiP_restore(uint32_t oldIntState) */
        .global HwiP_restore
        .type   HwiP_restore,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_restore:
        msr     cpsr_cf, r0
        bx      LR

/* FUNCTION DEF: void HwiP_enableVIC() */
        .global HwiP_enableVIC
        .type   HwiP_enableVIC,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_enableVIC:
        MRC     p15, #0, r0, c1, c0, #0  /* Read SCTLR */
        ORR     r0, r0, #(1<<24)         /* Set VE mask (VIC controller provides handler address for IRQ) */
        MCR     p15, #0, r0, c1, c0, #0  /* Write modified SCTLR */
        bx      LR

/* FUNCTION DEF: void HwiP_disableVIC() */
        .global HwiP_disableVIC
        .type   HwiP_disableVIC,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_disableVIC:
        MRC     p15, #0, r0, c1, c0, #0  /* Read SCTLR */
        BIC     r0, r0, #(1<<24)         /* Clear VE mask (VIC controller provides handler address for IRQ) */
        MCR     p15, #0, r0, c1, c0, #0  /* Write modified SCTLR */
        bx      LR

/* FUNCTION DEF: void HwiP_getCPSR() */
        .global HwiP_getCPSR
        .type   HwiP_getCPSR,%function
        .section ".text.hwi","ax",%progbits
        .arm
        .align 2
HwiP_getCPSR:
        mrs     r0, cpsr
        bx      LR

	.end

