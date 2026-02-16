;
; TEXAS INSTRUMENTS TEXT FILE LICENSE
;
; Copyright (c) 2023 Texas Instruments Incorporated
;
; All rights reserved not granted herein.
;
; Limited License.
;
; Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
; license under copyrights and patents it now or hereafter owns or controls to
; make, have made, use, import, offer to sell and sell ("Utilize") this software
; subject to the terms herein. With respect to the foregoing patent license,
; such license is granted solely to the extent that any such patent is necessary
; to Utilize the software alone. The patent license shall not apply to any
; combinations which include this software, other than combinations with devices
; manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
;
; Redistributions must preserve existing copyright notices and reproduce this license
; (including the above copyright notice and the disclaimer and (if applicable) source
; code license limitations below) in the documentation and/or other materials provided
; with the distribution.
;
; Redistribution and use in binary form, without modification, are permitted provided
; that the following conditions are met:
; No reverse engineering, decompilation, or disassembly of this software is
; permitted with respect to any software provided in binary form.
; Any redistribution and use are licensed by TI for use only with TI Devices.
; Nothing shall obligate TI to provide you with source code for the software
; licensed and provided to you in object code.
;
; If software source code is provided to you, modification and redistribution of the
; source code are permitted provided that the following conditions are met:
; Any redistribution and use of the source code, including any resulting derivative
; works, are licensed by TI for use only with TI Devices.
; Any redistribution and use of any object code compiled from the source code
; and any resulting derivative works, are licensed by TI for use only with TI Devices.
;
; Neither the name of Texas Instruments Incorporated nor the names of its suppliers
; may be used to endorse or promote products derived from this software without
; specific prior written permission.
;
; DISCLAIMER.
;
; THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
; WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
; AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
; LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
; CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
; GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
; CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
; EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;

        .text

;* FUNCTION DEF: void MpuP_disableAsm(void)
        .global MpuP_disableAsm
        .sect ".text.mpu"
        .arm
        .align 2
MpuP_disableAsm:
        mrc     p15, #0, r0, c1, c0, #0  ;read SCTLR register
        bic     r0, r0, #0x1             ;clear bit 0 in r0
        dsb
        mcr     p15, #0, r0, c1, c0, #0  ;MPU disabled (bit 0 = 0)
        isb                              ;flush instruction pipeline
        bx      LR

;* FUNCTION DEF: void MpuP_disableBRAsm(void)
        .global MpuP_disableBRAsm
        .sect ".text.mpu"
        .arm
        .align 2
MpuP_disableBRAsm:
        mrc     p15, #0, r0, c1, c0, #0  ;read SCTLR register
        bic     r0, r0, #0x20000         ;clear bit 17 in r0
        mcr     p15, #0, r0, c1, c0, #0  ;disable background region
        bx      LR

;* FUNCTION DEF: void MpuP_enableAsm(void)
        .global MpuP_enableAsm
        .sect ".text.mpu"
        .arm
        .align 2
MpuP_enableAsm:
        mrc     p15, #0, r0, c1, c0, #0  ;read SCTLR register
        orr     r0, r0, #0x1             ;set bit 0 in r0
        dsb
        mcr     p15, #0, r0, c1, c0, #0  ;MPU enabled (bit 0 = 1)
        isb                              ;flush instruction pipeline
        bx      LR

;* FUNCTION DEF: void MpuP_enableBRAsm(void)
        .global MpuP_enableBRAsm
        .sect ".text.mpu"
        .arm
        .align 2
MpuP_enableBRAsm:
        mrc     p15, #0, r0, c1, c0, #0  ;read SCTLR register
        orr     r0, r0, #0x20000         ;set bit 17 in r0
        mcr     p15, #0, r0, c1, c0, #0  ;background region enabled
        bx      LR

;* FUNCTION DEF: uint32 MpuP_isEnableAsm(void)
        .global MpuP_isEnableAsm
        .sect ".text.mpu"
        .arm
        .align 2
MpuP_isEnableAsm:
        mov     r0, #0
        mrc     p15, #0, r1, c1, c0, #0  ;read SCTLR register to r1
        tst     r1, #0x1                 ;test bit 0
        movne   r0, #1                   ;if not 0, MPU is enabled
        bx      LR

;* FUNCTION DEF: uint32 MpuP_setRegionAsm(void)
        .global MpuP_setRegionAsm
        .sect ".text.mpu"
        .arm
        .align 2
MpuP_setRegionAsm:
        mcr     p15, #0, r0, c6, c2, #0  ;select MPU region
        mcr     p15, #0, r1, c6, c1, #0  ;set region base address
        mcr     p15, #0, r2, c6, c1, #2  ;set region size and enable it
        mcr     p15, #0, r3, c6, c1, #4  ;set protection attributes
        bx      LR

	.end

