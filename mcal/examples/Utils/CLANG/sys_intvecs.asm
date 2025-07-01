;-------------------------------------------------------------------------------
; sys_intvecs.asm
;
; Copyright (C) 2023 Texas Instruments Incorporated - TI web adress www.ti.com
;
;
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
;
;    Redistributions of source code must retain the above copyright
;    notice, this list of conditions and the following disclaimer.
;
;    Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the
;    documentation and/or other materials provided with the
;    distribution.
;
;    Neither the name of Texas Instruments Incorporated nor the names of
;    its contributors may be used to endorse or promote products derived
;    from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;
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

