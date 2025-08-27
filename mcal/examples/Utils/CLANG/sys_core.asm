;-------------------------------------------------------------------------------
; sys_core.asm
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

    .text
    .arm

    ; .cdecls C,LIST,"sys_startup.h"

    ; .include sys_startup.h

    .global __SP_USER_MODE
    .global __SP_SVC_MODE
    .global __SP_IRQ_MODE
    .global __SP_FIQ_MODE
    .global __SP_UDEF_MODE
    .global __SP_ABT_MODE

;-------------------------------------------------------------------------------
; Get CPSR Value
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _getCPSRValue_
    .def     _getCPSRValue_
    

_getCPSRValue_

        mrs   r0, CPSR
        bx    lr

    

;-------------------------------------------------------------------------------
; Take CPU to IDLE state
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _gotoCPUIdle_
    .def     _gotoCPUIdle_
    

_gotoCPUIdle_

        WFI
        nop
        nop
        nop
        nop
        bx    lr

    


;-------------------------------------------------------------------------------
; Enable VFP Unit
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreEnableVfp_
    .def     _coreEnableVfp_
    

_coreEnableVfp_

        mrc   p15,     #0x00,      r0,       c1, c0, #0x02
        orr   r0,      r0,         #0xF00000
        mcr   p15,     #0x00,      r0,       c1, c0, #0x02
        mov   r0,      #0x40000000
        fmxr  fpexc,   r0
        bx    lr

    

;-------------------------------------------------------------------------------
; Enable Event Bus Export
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreEnableEventBusExport_
    .def     _coreEnableEventBusExport_
    

_coreEnableEventBusExport_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c9, c12, #0x00
        orr   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Disable Event Bus Export
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreDisableEventBusExport_
    .def     _coreDisableEventBusExport_
    

_coreDisableEventBusExport_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c9, c12, #0x00
        bic   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Enable RAM ECC Support
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreEnableRamEcc_
    .def     _coreEnableRamEcc_
    

_coreEnableRamEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Disable RAM ECC Support
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreDisableRamEcc_
    .def     _coreDisableRamEcc_
    

_coreDisableRamEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Enable TCMA ECC Support
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreEnableTCMAEcc_
    .def     _coreEnableTCMAEcc_
    

_coreEnableTCMAEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x02000000
        dmb
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Disable TCMA ECC Support
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreDisableTCMAEcc_
    .def     _coreDisableTCMAEcc_
    

_coreDisableTCMAEcc_

        stmfd sp!, {r0}
        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x02000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Enable Offset via Vic controller
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreEnableIrqVicOffset_
    .def     _coreEnableIrqVicOffset_
    

_coreEnableIrqVicOffset_

        stmfd sp!, {r0}
        mrc   p15, #0, r0,         c1, c0,  #0
        orr   r0,  r0,    #0x01000000
        mcr   p15, #0, r0,         c1, c0,  #0
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Get data fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreGetDataFault_
    .def     _coreGetDataFault_
    

_coreGetDataFault_

        mrc   p15, #0, r0, c5, c0,  #0
        bx    lr

    


;-------------------------------------------------------------------------------
; Clear data fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreClearDataFault_
    .def     _coreClearDataFault_
    

_coreClearDataFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0,  #0
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Get instruction fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreGetInstructionFault_
    .def     _coreGetInstructionFault_
    

_coreGetInstructionFault_

        mrc   p15, #0, r0, c5, c0, #1
        bx    lr

    


;-------------------------------------------------------------------------------
; Clear instruction fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreClearInstructionFault_
    .def     _coreClearInstructionFault_
    

_coreClearInstructionFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0, #1
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Get data fault address register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreGetDataFaultAddress_
    .def     _coreGetDataFaultAddress_
    

_coreGetDataFaultAddress_

        mrc   p15, #0, r0, c6, c0,  #0
        bx    lr

    


;-------------------------------------------------------------------------------
; Clear data fault address register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreClearDataFaultAddress_
    .def     _coreClearDataFaultAddress_
    

_coreClearDataFaultAddress_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0,  #0
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Get instruction fault address register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreGetInstructionFaultAddress_
    .def     _coreGetInstructionFaultAddress_
    

_coreGetInstructionFaultAddress_

        mrc   p15, #0, r0, c6, c0, #2
        bx    lr

    


;-------------------------------------------------------------------------------
; Clear instruction fault address register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreClearInstructionFaultAddress_
    .def     _coreClearInstructionFaultAddress_
    

_coreClearInstructionFaultAddress_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0, #2
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Get auxiliary data fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreGetAuxiliaryDataFault_
    .def     _coreGetAuxiliaryDataFault_
    

_coreGetAuxiliaryDataFault_

        mrc   p15, #0, r0, c5, c1, #0
        bx    lr

    


;-------------------------------------------------------------------------------
; Clear auxiliary data fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreClearAuxiliaryDataFault_
    .def     _coreClearAuxiliaryDataFault_
    

_coreClearAuxiliaryDataFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mcr   p15, #0, r0, c5, c1, #0
        ldmfd sp!, {r0}
        bx    lr

    


;-------------------------------------------------------------------------------
; Get auxiliary instruction fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreGetAuxiliaryInstructionFault_
    .def     _coreGetAuxiliaryInstructionFault_
    

_coreGetAuxiliaryInstructionFault_

        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    

;-------------------------------------------------------------------------------
; Clear auxiliary instruction fault status register
; SourceId :
; DesignId :
; Requirements:

    .thumb
    .thumbfunc _coreClearAuxiliaryInstructionFault_
    .def     _coreClearAuxiliaryInstructionFault_
    

_coreClearAuxiliaryInstructionFault_

        stmfd sp!, {r0}
        mov   r0,  #0
        mrc   p15, #0, r0, c5, c1, #1
        ldmfd sp!, {r0}
        bx    lr

    

;-------------------------------------------------------------------------------
; Disable interrupts - R4 IRQ & FIQ
; SourceId :
; DesignId :
; Requirements:

        .thumb
        .thumbfunc _disable_interrupt_
        .def _disable_interrupt_
        

_disable_interrupt_

        cpsid if
        bx    lr

        

;-------------------------------------------------------------------------------
; Disable FIQ interrupt

        .thumb
        .thumbfunc _disable_FIQ_interrupt_
        .def _disable_FIQ_interrupt_
        

_disable_FIQ_interrupt_

        cpsid f
        bx    lr

        

;-------------------------------------------------------------------------------
; Disable FIQ interrupt

        .thumb
        .thumbfunc _disable_IRQ_interrupt_
        .def _disable_IRQ_interrupt_
        

_disable_IRQ_interrupt_

        cpsid i
        bx    lr

        

;-------------------------------------------------------------------------------
; Enable interrupts - R4 IRQ & FIQ

       .thumb
       .thumbfunc _enable_interrupt_
       .def _enable_interrupt_
       

_enable_interrupt_

        cpsie if
        bx    lr

        



;-------------------------------------------------------------------------------
; Delay routine using nop with 20ns resolution
; SourceId :
; DesignId :
; Requirements:
      .thumb
      .thumbfunc _sysDelay_
      .def    _sysDelay_
      

_sysDelay_
      ;nop
      ;nop
      ;subs     r0, r0, #5
      ;movls    r0, #4
_sysDelayLbl_:
     subs     r0, r0, #1
      bne      _sysDelayLbl_
      nop

      bx       lr

  
  
  

;-------------------------------------------------------------------------------

