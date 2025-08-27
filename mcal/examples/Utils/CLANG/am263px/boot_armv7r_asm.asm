;-------------------------------------------------------------------------------
; boot.asm
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

;****************************************************************************
;* BOOT.ASM
;*
;* THIS IS THE INITAL BOOT ROUTINE FOR TMS470 C++ PROGRAMS.
;* IT MUST BE LINKED AND LOADED WITH ALL C++ PROGRAMS.
;*
;* THIS MODULE PERFORMS THE FOLLOWING ACTIONS:
;*   1) ALLOCATES THE STACK AND INITIALIZES THE STACK POINTER
;*   2) CALLS AUTO-INITIALIZATION ROUTINE
;*   3) CALLS THE FUNCTION MAIN TO START THE C++ PROGRAM
;*   4) CALLS THE STANDARD EXIT ROUTINE
;*
;* THIS MODULE DEFINES THE FOLLOWING GLOBAL SYMBOLS:
;*   1) __stack     STACK MEMORY AREA
;*   2) _c_int00    BOOT ROUTINE
;*
;****************************************************************************
   .if  __TI_ARM_V7M__ | __TI_ARM_V6M0__
	.thumbfunc _c_int00
	.thumbfunc _resetvectors
	.thumbfunc HF
   .else
	.armfunc _c_int00
   .endif

;****************************************************************************
;*  16 BIT STATE BOOT ROUTINE                                               *
;****************************************************************************

   .if __TI_ARM_V7M__ | __TI_ARM_V6M0__
	.thumb
   .else
	.arm
   .endif

	.global	__stack

__stack:.usect	".stack", 0, 4

	.global	_c_int00

;***************************************************************
;* FUNCTION DEF: _c_int00
;***************************************************************
_c_int00:

        ; Disable FIQ and IRQ
        mrs     r0, cpsr
        orr     r0, r0, #0xC0
        msr     cpsr_cf, r0
	.if __TI_NEON_SUPPORT__ | __TI_VFP_SUPPORT__
        ;*------------------------------------------------------
	;* SETUP PRIVILEGED AND USER MODE ACCESS TO COPROCESSORS
	;* 10 AND 11, REQUIRED TO ENABLE NEON/VFP
	;* COPROCESSOR ACCESS CONTROL REG
	;* BITS [23:22] - CP11, [21:20] - CP10
	;* SET TO 0b11 TO ENABLE USER AND PRIV MODE ACCESS
        ;*------------------------------------------------------
	MRC      p15,#0x0,r0,c1,c0,#2
        MOV      r3,#0xf00000
	ORR      r0,r0,r3
        MCR      p15,#0x0,r0,c1,c0,#2

        ;*------------------------------------------------------
	; SET THE EN BIT, FPEXC[30] TO ENABLE NEON AND VFP
        ;*------------------------------------------------------
	MOV      r0,#0x40000000
        FMXR     FPEXC,r0
        .endif ; __ARM_FP
        
        ;*------------------------------------------------------
        ;* SET TO IRQ MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x12  ; SET IRQ MODE
        MSR     cpsr_cf, r0

        ;*------------------------------------------------------
        ;* INITIALIZE THE IRQ MODE STACK
        ;*------------------------------------------------------
        .if __TI_AVOID_EMBEDDED_CONSTANTS
        MOVW    sp, __IRQ_STACK_END
        MOVT    sp, __IRQ_STACK_END
        .else
        LDR     sp, c_IRQ_STACK_END
        .endif

        ;*------------------------------------------------------
        ;* SET TO FIQ MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x11  ; SET FRQ MODE
        MSR     cpsr_cf, r0

        ;*------------------------------------------------------
        ;* INITIALIZE THE FIQ MODE STACK
        ;*------------------------------------------------------
        .if __TI_AVOID_EMBEDDED_CONSTANTS
        MOVW    sp, __FIQ_STACK_END
        MOVT    sp, __FIQ_STACK_END
        .else
        LDR     sp, c_FIQ_STACK_END
        .endif

        ;*------------------------------------------------------
        ;* SET TO ABORT` MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x17  ; SET ABORT MODE
        MSR     cpsr_cf, r0

        ;*------------------------------------------------------
        ;* INITIALIZE THE ABORT MODE STACK
        ;*------------------------------------------------------
        .if __TI_AVOID_EMBEDDED_CONSTANTS
        MOVW    sp, __ABORT_STACK_END
        MOVT    sp, __ABORT_STACK_END
        .else
        LDR     sp, c_ABORT_STACK_END
        .endif

        ;*------------------------------------------------------
        ;* SET TO UNDEFINED MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x1B  ; SET UNDEFINED MODE
        MSR     cpsr_cf, r0

        ;*------------------------------------------------------
        ;* INITIALIZE THE UNDEFINED MODE STACK
        ;*------------------------------------------------------
        .if __TI_AVOID_EMBEDDED_CONSTANTS
        MOVW    sp, __UNDEFINED_STACK_END
        MOVT    sp, __UNDEFINED_STACK_END
        .else
        LDR     sp, c_UNDEFINED_STACK_END
        .endif

        ;*------------------------------------------------------
        ;* SET TO SUPERVISOR MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x13  ; SET SUPERVISOR MODE
        MSR     cpsr_cf, r0

        ;*------------------------------------------------------
        ;* INITIALIZE THE SUPERVISOR MODE STACK
        ;*------------------------------------------------------
        .if __TI_AVOID_EMBEDDED_CONSTANTS
        MOVW    sp, __SVC_STACK_END
        MOVT    sp, __SVC_STACK_END
        .else
        LDR     sp, c_SVC_STACK_END
        .endif

        ;*------------------------------------------------------
        ;* SET TO SYSTEM MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x1F  ; SET SYSTEM MODE
        MSR     cpsr_cf, r0

        ;*------------------------------------------------------
        ;* INITIALIZE THE USER MODE STACK
        ;*------------------------------------------------------
        .if __TI_AVOID_EMBEDDED_CONSTANTS
        MOVW    sp, :lower16:__STACK_END
        MOVT    sp, :upper16:__STACK_END
        .else
        LDR     sp, c_STACK_END
        .endif

        ; Call the __mpu_init hook function.
        BL      __mpu_init
 
        ;*------------------------------------------------------
        ;* Init .bss section to zero, this needs .bss to be
        ;* defined as below in the linker command file.
        ;*
        ;* .bss:    {} palign(8)
        ;* RUN_START(__BSS_START)
        ;* RUN_END(__BSS_END)
        ;*
        ;* We do this after __mpu_init, since now cache is
        ;* enabled and there memset speed will be optimal
        ;*
        ;* Perform all the required initializations when
        ;* _system_pre_init() returns non-zero:
        ;*   - Process BINIT Table
        ;*   - Perform C auto initialization
        ;*   - Call global constructors
        ;*------------------------------------------------------
        BL      _system_pre_init
        CMP     R0, #0
        BEQ     bypass_auto_init
        BL      __TI_auto_init
bypass_auto_init:

        ;*------------------------------------------------------
        ;* CALL APPLICATION
        ;*------------------------------------------------------
        BL      main

        ;*------------------------------------------------------
        ;* IF APPLICATION DIDN'T CALL EXIT, CALL EXIT(1)
        ;*------------------------------------------------------
        MOV     R0, #1
        BL      exit

        ;*------------------------------------------------------
        ;* DONE, LOOP FOREVER
        ;*------------------------------------------------------
L1:     B       L1

;***************************************************************
;* CONSTANTS USED BY THIS MODULE
;***************************************************************
        .if !__TI_AVOID_EMBEDDED_CONSTANTS
c_STACK_END: .long __STACK_END
c_IRQ_STACK_END: .long __IRQ_STACK_END
c_FIQ_STACK_END: .long __FIQ_STACK_END
c_SVC_STACK_END: .long __SVC_STACK_END
c_ABORT_STACK_END: .long __ABORT_STACK_END
c_UNDEFINED_STACK_END: .long __UNDEFINED_STACK_END
        .endif

;******************************************************
;* UNDEFINED REFERENCES                               *
;******************************************************
        .global __STACK_END
        .global __FIQ_STACK_END
        .global __IRQ_STACK_END
        .global __SVC_STACK_END
        .global __ABORT_STACK_END
        .global __UNDEFINED_STACK_END
        .global _system_pre_init
        .global __TI_auto_init
        .global main
        .global exit
        .global __mpu_init
        .global __bss_init

        .end
