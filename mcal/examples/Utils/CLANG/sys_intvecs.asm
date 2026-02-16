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

    .sect ".intvecs"
    .arm

;-------------------------------------------------------------------------------
; import reference for interrupt routines

    .ref _sysResetEntry_
    .ref _sysUndefEntry_
    .ref _sysSvcEntry_
    .ref _sysPrefetchEntry_
    .ref _sysDAbortEntry_
    .ref _sysIrqEntry_
    .ref vimFiqDispatcher

MCAL_FIQ_ENABLE_FPU_SAVE_RESTORE .equ (1) ; /* make this 0 to disable FPU context save/restore */
    .def _c_int000


;-------------------------------------------------------------------------------
; interrupt vectors


_c_int000
        b   _sysResetEntry_
undefEntry
        b   _sysUndefEntry_
svcEntry
        b   _sysSvcEntry_
prefetchEntry
        b   _sysPrefetchEntry_
dabortEntry
        b   _sysDAbortEntry_
        b   #-8
irqEntry
        b   _sysIrqEntry_

; Placing the FIQ handler here to avoid the branching

       .def _sysFiqEntry_
_sysFiqEntry_

        sub      lr, lr, #4
        srsdb    sp!, #0x1FU              ; Save LR_irq and SPSR_irq to System mode stack
        cps      #0x1FU                   ; Switch to System mode
        push     {r0-r4, r12, lr}         ; Store normal scratch registers
        .if MCAL_FIQ_ENABLE_FPU_SAVE_RESTORE
        fmrx  r0, fpscr
        vpush {d0-d15}
        push  {r0}            ; /* vpush {d16-d31} */
        .endif
        blx      vimFiqDispatcher         ; jump to the handler
        .if MCAL_FIQ_ENABLE_FPU_SAVE_RESTORE
        pop   {r0}
        vpop  {d0-d15}        ;     /* vpop {d16-d31} */
        vmsr  fpscr, r0
        .endif
        pop      {r0-r4, r12, lr}         ; Restore registers
        rfeia    sp!                      ; Return using RFE from System mode stack



.end


;-------------------------------------------------------------------------------

