;-------------------------------------------------------------------------------
; sys_startup.asm
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

    .sect ".startup"
    .text
    .arm

    ; .cdecls C,LIST
    ;  %{
    ;      #include "sys_startup.h"
    ;      #include "sys_exception.h"
    ;      #include "sys_core.h"
    ;      #include "sys_vim.h"
    ;      #include "sys_pmu.h"
    ;  %}

    ; .include sys_startup.h
    ; .include sys_exception.h
    ; .include sys_core.h
    ; .include sys_vim.h
    ; .include sys_pmu.h

    .ref vimIrqDispatcher
    .ref moduleInit
    .ref sys_cUabort
    .ref sys_cPabort
    .ref sys_cDabort
    .ref sys_cSwiInt
    .ref system_init

M_ARM_MODE_SYS  .equ    (0x1FU)
gCacheL1dCacheLineSize  .equ    (32U)
MCAL_ENABLE_FPU_SAVE_RESTORE .equ (1) ; /* make this 0 to disable FPU context save/restore */
;-------------------------------------------------------------------------------
; Reset cause handler - Check the reset reason
;    (Reset Cause register and ESM status register -for Group3 fault)
;     - Power on reset, warm reset ( Watchdog/ SW trigerred/ External)
;     or CPU reset (STC )
; SourceId :
; DesignId :
; Requirements:

SYS_RST_CAUSE       .word     0x5320000c 
SYS_RST_CAUSE_CLR   .word     0x53200010
S_POWERON_RESET     .equ      0x41U      
S_WATCHDOG_0_RESET  .equ      0x42U      
S_WATCHDOG_1_RESET  .equ      0x44U      
S_WATCHDOG_2_RESET  .equ      0x48U      
S_WATCHDOG_3_RESET  .equ      0x50U      
S_SW_WARM_RESET     .equ      0x60U      
S_EXT_RESET         .equ      0x40U      
S_HSM_WDT_RESET     .equ      0xC0U      
S_DEBUGGER_RESET    .equ      0x140U     
S_TEMP0_RESET       .equ      0x240U     
S_TEMP1_RESET       .equ      0x440U     

TOPRCM_SPARE_RW0  .word     0x53200FD0


SYS_UDEFABT_DISP   .word     sys_udefAbtDisp
SYS_PREFABT_DISP   .word     sys_prefAbtDisp
SYS_DATAABT_DISP   .word     sys_dataAbtDisp
SYS_SWI_DISP       .word     sys_swiDisp

SYS_CUDEF_ABT      .word     sys_cUabort
SYS_CPREF_ABT      .word     sys_cPabort
SYS_CDATA_ABT      .word     sys_cDabort
SYS_CSWI_ABT       .word     sys_cSwiInt
SYS_IRQ_CALL       .word     vimIrqDispatcher

    .def     _sysResetCauseHandler_
    

_sysResetCauseHandler_

        ; Obtain the reset cause by reading the system reset cause register
        ldr     r6, SYS_RST_CAUSE
        ldr     r6, [r6]
        ; Check if reset cause has been cleared, skip if so
        cmp     r6, #0

        beq EXIT_RST_HNDL
            ; Store the reset cause in SPARE REG RW0
            ldr     r5, TOPRCM_SPARE_RW0
            ; Store the reset cause value
            str     r6, [r5]

            ; Clear the System reset cause
            ldr     r5, SYS_RST_CAUSE_CLR
            mov     r4, #0x7U
            str     r4, [r5]

EXIT_RST_HNDL:
        bx      lr
        

;/** ------------------------------------------------------------------------------
; * @name    _pbistTCMB_
; * @brief
; *
; */

TOPRCM_DFT_REG0 .word       0xFFFFE160
TOPRCM_DFT_REG1 .word       0xFFFFE164

PBIST_PACT      .word       0xFFFFE580
PBIST_LO        .word       0xFFFFE510
PBIST_ID        .word       0xFFFFE584
PBIST_OVR       .word       0xFFFFE588
PBIST_DLR       .word       0xFFFFE564
PBIST_ALGO      .word       0xFFFFE5C4
PBIST_RINFOL    .word       0xFFFFE5C8
PBIST_RINFOU    .word       0xFFFFE5CC
PBIST_ROM       .word       0xFFFFE5C0

PBIST_INTR_REG  .word       0xFFFFFE28
PBIST_INTR_VAL  .equ        0x00200000
PBIST_FSCR0_REG .word       0xFFFFE598
PBIST_FSCR1_REG .word       0xFFFFE59C

DFT0_CLK_EN     .equ        0xFFFF3FA
DFT1_CLK_EN     .equ        0xFFFF

    .def _pbistTCMB_
    

_pbistTCMB_

        ldr     r5, TOPRCM_DFT_REG0
        ; Setup Selftest Key, Active low reset contol bit during PBIST selftest
        str     r0, [r5]

        ;Enable Pbist Internal clocks
        ldr     r5, PBIST_PACT
        mov     r6, #0x3
        str     r6, [r5]

        ; Loop count
        ldr     r5, PBIST_LO
        mov     r6, #0x0
        str     r6, [r5]

        ; PBIST ID  - always �1�
        ldr     r5, PBIST_ID
        mov     r6, #0x1
        str     r6, [r5]

        ; overide � fixed programmation
        ldr     r5, PBIST_OVR
        mov     r6, #0xF
        str     r6, [r5]

        ; pbist controller settings
        ldr     r5, PBIST_DLR
        movw    r6, #((0x0 << 8) | (0x10))
        movt    r6, #((0x0 << 8) | (0x0))
        str     r6, [r5]

        ; Setup the Algo
        ldr     r5, PBIST_ALGO
        str     r1, [r5]

        ; To program the memory group � one hot coding
        ldr     r5, PBIST_RINFOL
        str     r2, [r5]

        ldr     r5, PBIST_RINFOU
        movw    r6, #((0x0 << 8) | (0x0))
        movt    r6, #((0x0 << 8) | (0x0))
        str     r6, [r5]

        ; re-program the override
        ldr     r5, PBIST_OVR
        str     r3, [r5]

        ; PBIST ID  - set to 0
        ldr     r5, PBIST_ID
        mov     r6, #0x0
        str     r6, [r5]

        ; Microcode location from the OnChip ROM default is onchip ROM
        ldr     r5, PBIST_ROM
        mov     r6, #0x3
        str     r6, [r5]

        ; To start the test
        ldr     r5, PBIST_DLR
        movw    r6, #((0x2 << 8) | (0x1C))
        movt    r6, #((0x0 << 8) | (0x0))
        str     r6, [r5]

        ; loop count for timeout
        mov     r6, #0
        ;Wait for PBIST interrupt - TBD
LOOP_PBIST_INTR:
        ;check for timeout
        tst     r6, #0x400000
        bne     PBIST_ERR
            ;increment the counter
            add     r6, r6, #1
            ldr     r5, PBIST_INTR_REG
            ldr     r5, [r5]
            tst     r5, #PBIST_INTR_VAL
            beq     LOOP_PBIST_INTR

PBIST_DONE:
        ; Clear the interrupt
        ldr     r6, PBIST_INTR_REG
        ldr     r7, [r6]
        orr     r7, r7, r5
        str     r7, [r6]
        ldr     r5, PBIST_FSCR0_REG
        ldr     r5, [r5]
        cmp     r5, #0
        bne     PBIST_ERR
            ldr     r5, PBIST_FSCR1_REG
            ldr     r5, [r5]
            cmp     r5, #0
            bne     PBIST_ERR
                mov     r0, #0      ; Success
                b       PBIST_STOP

PBIST_ERR:
        mov     r0, r5

PBIST_STOP:
        ; Reset the PBIST
        ldr     r5, TOPRCM_DFT_REG0
        mov     r6, #(0xA | (1 << 5))
        str     r6, [r5]

        ldr     r5, TOPRCM_DFT_REG1
        mov     r6, #0
        str     r6, [r5]

        ;Disable Pbist Internal clocks
        ;ldr     r5, PBIST_PACT
        ;mov     r6, #0x0
        ;str     r6, [r5]

        bx     lr

        


;/** ------------------------------------------------------------------------------
; * @name    _meminit_
; * @brief
; *
; */

MEM_INIT_START  .word   0xFFFFFF5c
MEM_INIT_DONE   .word   0xFFFFFF6c

MEM_INIT_KEY    .equ    0xAD
CR4TCMBMEM      .equ    (1 << 1)


    .def _meminit_
    

_meminit_

        ldr    r5, MEM_INIT_START
        movw   r6, #CR4TCMBMEM
        movt   r6, #((MEM_INIT_KEY << 8) | (0x0))
        str    r6, [r5]
LPCHECK:
        ldr    r5, MEM_INIT_DONE
        ldr    r6, [r5]
        tst    r6, #CR4TCMBMEM
        beq    LPCHECK

MEMINIT_DONE:
         bx     lr
        

;/** ------------------------------------------------------------------------------
; * @name    _generateNERROR_
; * @brief  Force the generation of NERROR to indicate a fatal error to host.
; *
; */
ESMEPSR                 .word   0xFFFFF524
ESMEKR                  .word   0xFFFFF538
NERROR_FORCE            .equ    0xA

    .def     _generateNERROR_
    

_generateNERROR_
        ; Report NError to host
        ldr     r6, ESMEPSR
        ldr     r6, [r6]
        tst     r6, #1
        beq     LOOPERR
            ; Force the NError generation
            ldr     r6, ESMEKR
            mov     r7, #NERROR_FORCE
            str     r7, [r6]

        ; Done, loop forever
LOOPERR:
        b      LOOPERR

        



;-------------------------------------------------------------------------------
; ARM Cortex R4 Reset handler - startup code
; SourceId :
; DesignId :
; Requirements:

TOPRCM_EFUSEREGROW10    .word   0xFFFFE214
TOPRCM_EFUSEREGROW12    .word   0xFFFFE21C
BSSGPCFG_EFUSEROW17RD   .word   0x43F7F09C
TOPRCM_RS232BITINTRVL   .word   0xFFFFE264
MSSRCM_CLKSRCSEL1       .word   0xFFFFFF44
TOPRCM_BSSCTL           .word   0xFFFFE108
TOPRCM_MISCCAPT         .word   0xFFFFE134
ESM_ESMSR4              .word   0xFFFFF558
MBX_REG                 .word   0xF0608018
MBX_DAT                 .word   0xF0601000
BSS_ROM                 .word   0x40000000
TOPRCM_SPARE_REG1       .word   0xFFFFE1F0

STC_ROM_MEMCLK          .equ    ((0xA) | (0x1 << 19))
MARCH13_ALGO            .equ    (0x1 << 10)
STC_ROM_MEM             .equ    (0x1 << 17)
PBIST_ROM_MEM           .equ    (0x1 << 16)
STC_ROM_ALGO            .equ    (0x1 << 2)
PBIST_ROM_ALGO          .equ    (0x1 << 12)
STC_PBIST_ROM_MEM       .equ    (STC_ROM_MEM | PBIST_ROM_MEM)
MSS_TCMB_MEMCLK         .equ    ((0xA) | (0x1 << 12))
MSS_TCMB_MEM            .equ    (0x1 << 24)
BSS_RESETREL_UNGATECLK  .equ    (0xAD000000)

    .def     _sysResetEntry_
    

_sysResetEntry_
    .global _c_int00
        bl  _c_int00

        ; Done, loop forever
LOOP0:
        b      LOOP0
        

;-------------------------------------------------------------------------------
; Temporary exception infinite loop
; SourceId :
; DesignId :
; Requirements:

    .def     _sysLoop_
    

_sysLoop_
LOOP1:
        b      LOOP1
        

;-------------------------------------------------------------------------------
; ARM undefined exception handler
; SourceId :
; DesignId :
; Requirements:

    .def     _sysUndefEntry_
    

_sysUndefEntry_
        srsdb    sp!, #M_ARM_MODE_SYS     ; Save LR_irq and SPSR_irq to System mode stack
        cps      #M_ARM_MODE_SYS          ; Switch to System mode
        push     {r0-r3, r12, lr}         ; Store normal scratch registers
        ldr      r0, SYS_UDEFABT_DISP
        bx       r0
        

;-------------------------------------------------------------------------------
; ARM supervisory call handler
; SourceId :
; DesignId :
; Requirements:

    .def     _sysSvcEntry_
    

_sysSvcEntry_
        srsdb    sp!, #M_ARM_MODE_SYS     ; Save LR_irq and SPSR_irq to System mode stack
        cps      #M_ARM_MODE_SYS          ; Switch to System mode
        push     {r0-r3, r12, lr}         ; Store normal scratch registers
        ldr      r1, SYS_SWI_DISP
        bx       r1
        

;-------------------------------------------------------------------------------
; ARM Prefetch exception handler
; SourceId :
; DesignId :
; Requirements:

    .def     _sysPrefetchEntry_
    

_sysPrefetchEntry_
        srsdb    sp!, #M_ARM_MODE_SYS     ; Save LR_irq and SPSR_irq to System mode stack
        cps      #M_ARM_MODE_SYS          ; Switch to System mode
        push     {r0-r3, r12, lr}         ; Store normal scratch registers
        ldr      r0, SYS_PREFABT_DISP
        bx       r0

        

;-------------------------------------------------------------------------------
; ARM Data abort handler
; SourceId :
; DesignId :
; Requirements:

    .def     _sysDAbortEntry_
    

_sysDAbortEntry_
        srsdb    sp!, #M_ARM_MODE_SYS     ; Save LR_irq and SPSR_irq to System mode stack
        cps      #M_ARM_MODE_SYS          ; Switch to System mode
        push     {r0-r3, r12, lr}         ; Store normal scratch registers
        ldr      r0, SYS_DATAABT_DISP
        bx       r0

        

;-------------------------------------------------------------------------------
; ARM IRQ interrupt handler
; SourceId :
; DesignId :
; Requirements:

       .def _sysIrqEntry_
_sysIrqEntry_:  

    SUB     lr, lr, #4    ; Return to the interrupted instruction

    PUSH    {lr}          ;  Push the return address and SPSR.
    MRS     lr, SPSR
    PUSH    {lr}

    CPS  #M_ARM_MODE_SYS  ; /* Change to supervisor mode to allow reentry. */

    PUSH    {r0-r4, r12}  ; /* Push used registers. */

    .if MCAL_ENABLE_FPU_SAVE_RESTORE
    FMRX  R0, FPSCR
    VPUSH {D0-D15}
    PUSH  {R0}            ; /* VPUSH {D16-D31} */
    .endif

    MOV     r2, sp
    AND     r2, r2, #4
    SUB     sp, sp, r2

    PUSH    {r0-r4, lr}   ; /* Call the interrupt handler. */
    LDR     r1, SYS_IRQ_CALL
    BLX     r1
    POP     {r0-r4, lr}
    ADD     sp, sp, r2

    CPSID   i             ;     /* disable IRQ */
    DSB
    ISB

    .if MCAL_ENABLE_FPU_SAVE_RESTORE
    POP   {R0}
    VPOP  {D0-D15}        ;     /* VPOP {D16-D31} */
    VMSR  FPSCR, R0
    .endif

    POP     {r0-r4, r12}
    CPS     #0x12
    POP     {LR}
    MSR     SPSR_cxsf, LR
    POP     {LR}
    MOVS    PC, LR

.end


;-------------------------------------------------------------------------------
; ARM Undef instruction exception handler
; SourceId :
; DesignId :
; Requirements:

  .def sys_udefAbtDisp
sys_udefAbtDisp:  

    add      r2, sp, #24              ; get address of LR_abt
    ldmia    r2!, {r0, r1}            ; r0 - LR_abt, r1 - SPSR_abt, r2 - SP
    sub      r0, r0, #4               ; aborted instruction address
    ldr      r3, SYS_CUDEF_ABT        ; passing params r0, r1, r2
    blx      r3
    pop      {r0-r3, r12, lr}         ; Restore registers
    rfeia    sp!                      ; Return using RFE from System mode stack

  

;-------------------------------------------------------------------------------
; ARM prefetch exception handler
; SourceId :
; DesignId :
; Requirements:

  .def sys_prefAbtDisp
sys_prefAbtDisp:  

    add      r2, sp, #24              ; get address of LR_abt
    ldmia    r2!, {r0, r1}            ; r0 - LR_abt, r1 - SPSR_abt, r2 - SP
    ldr      r3, SYS_CPREF_ABT        ; passing params r0, r1, r2
    blx      r3
    pop      {r0-r3, r12, lr}         ; Restore registers
    rfeia    sp!                      ; Return using RFE from System mode stack
  

;-------------------------------------------------------------------------------
; ARM data exception handler
; SourceId :
; DesignId :
; Requirements:

  .def sys_dataAbtDisp
sys_dataAbtDisp:  

    add      r2, sp, #24              ; get address of LR_abt
    ldmia    r2!, {r0, r1}            ; r0 - LR_abt, r1 - SPSR_abt, r2 - SP
    ldr      r3, SYS_CDATA_ABT        ; passing params r0, r1, r2
    blx      r3
    pop      {r0-r3, r12, lr}         ; Restore registers
    rfeia    sp!                      ; Return using RFE from System mode stack
  

;-------------------------------------------------------------------------------
; ARM Software Interrupt SVC handler
; SourceId :
; DesignId :
; Requirements:


  .def sys_swiDisp
sys_swiDisp:  

    ; mov      r1, #SVC_TYPES.SVC_SWITCH_ARM_MODE
    mov      r1, #0x0U
    cmp      r0, r1                   ; if svc num is 0 then switch arm mode
    beq      SWM
    ldr      r3, SYS_CSWI_ABT         ; passing param r0 - contains SVC number
    blx      r3
    b        RTN
SWM:
    add      r2, sp, #28              ; get address of SPSR_svc
    ldr      r0, [r2]
    bic      r0, r0, #0x0000001F      ; clear mode bits
    orr      r0, r0, #M_ARM_MODE_SYS  ; modify spsr mode bits to system mode
    str      r0, [r2]
RTN:
    pop      {r0-r3, r12, lr}         ; Restore registers
    rfeia    sp!                      ; Return using RFE from System mode stack

  



irq_fiq_set_mask .word 0xFFFFFF3F
irq_fiq_clear_mask .word 0x000000C0
;//==============================================================================
;//   void CSL_armR5EnableIrqFiq( uintptr_t cookie );
;//==============================================================================
    .global CSL_armR5EnableIrqFiq
CSL_armR5EnableIrqFiq:
    LDR     r2, irq_fiq_set_mask         ; Mask out other bits than IRQ and FIQ
    MRS     r1, CPSR                     ; Read CPSR
    AND     r1, r1, r2
    LDR     r2, irq_fiq_clear_mask       ; Mask out other bits than IRQ and FIQ
    AND     r0, r0, r2                   ; set/clear IRQ and FIQ bits
    ORR     r1, r1, r0
    MSR     CPSR_c, r1                   ; Write CPSR (bits 7:6 only)
    BX      lr

;//==============================================================================
;//   void CSL_armR5IntrEnableFiq( uint32 enable )
;//==============================================================================
    .global CSL_armR5IntrEnableFiq
CSL_armR5IntrEnableFiq:
    MRS     r1, CPSR                        ; Read CPSR
    CMP     r0, #0
    BEQ     armR5IntrEnableFiq_disable
    BIC     r1, r1, #(1<<6)                 ;Clear FIQ mask (exception is not masked (is enabled))
    B       armR5IntrEnableFiq_00
armR5IntrEnableFiq_disable:
    ORR     r1, r1, #(1<<6)                 ;Set FIQ mask (exception is masked (is disabled))
armR5IntrEnableFiq_00:
    MSR     CPSR_c, r1                      ;Write CPSR (bits 7:0 only)
    BX      lr

;//==============================================================================
;//   void CSL_armR5IntrEnableIrq( uint32 enable )
;//==============================================================================
    .global CSL_armR5IntrEnableIrq
CSL_armR5IntrEnableIrq:
    MRS     r1, CPSR                        ; Read CPSR
    CMP     r0, #0
    BEQ     armR5IntrEnableIrq_disable
    BIC     r1, r1, #(1<<7)                 ;Clear IRQ mask (exception is not masked (is enabled))
    B       armR5IntrEnableIrq_00
armR5IntrEnableIrq_disable:
    ORR     r1, r1, #(1<<7)                 ;Set IRQ mask (exception is masked (is disabled))
armR5IntrEnableIrq_00:
    MSR     CPSR_c, r1                      ;Write CPSR (bits 7:0 only)
    BX      lr

;//==============================================================================
;//   uint32 CSL_armR5ReadMpidrReg(void)
;//==============================================================================
    .global CSL_armR5ReadMpidrReg
    .arm
CSL_armR5ReadMpidrReg:
    DMB
	MRC     p15, #0, r0, c0, c0, #5 ;Read MPIDR
	BX      lr
	
;//==============================================================================
;//   void CSL_armR5IntrEnableVic( uint32 enable )
;//==============================================================================
    .global CSL_armR5IntrEnableVic
CSL_armR5IntrEnableVic:
    MRC     p15, #0, r1, c1, c0, #0         ; Read SCTLR
    CMP     r0, #0
    BEQ     armR5IntrEnableVic_disable
    ORR     r1, r1, #(1<<24)                ; Set VE mask (VIC controller provides handler address for IRQ)
    B       armR5IntrEnableVic_00
armR5IntrEnableVic_disable:
    BIC     r1, r1, #(1<<24)                ; Clear VE mask (exception vector address for IRQ is 0x00000018 or 0xFFFF0018)
armR5IntrEnableVic_00:
    DSB
    MCR     p15, #0, r1, c1, c0, #0         ; Write modified SCTLR
    BX      lr
;/*
; * END OF sys_startup.asm FILE
; */


