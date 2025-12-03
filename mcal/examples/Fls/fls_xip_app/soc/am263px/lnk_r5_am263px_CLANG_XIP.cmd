/*
 * LINKER OPTIONS
 */
--entry_point=_c_int000                   /* ENTRY POINT                   */
-stack  0x4000                            /* SOFTWARE STACK SIZE           */
-heap   0x4000                            /* HEAP AREA SIZE                */
--retain="*(.intvecs)"

/* SPECIFY THE SYSTEM MEMORY MAP */
MEMORY
{
    /*  Reset Vectors base address(RESET_VECTORS) should be 64 bytes aligned  */
    RESET_VECTORS           (X)     : origin=0x00000000 length=0x00000100
    TCMA_RAM                (RX)    : origin=0x00000100 length=0x00003F00
    TCMB_RAM                (RW)    : origin=0x00080000 length=0x00004000
    FLASH					(RX)	: origin=0x60100000 length=0x00100000
    L2_RAM_BANK0            (RW)    : origin=0x70040000 length=0x00100000
    CPPI_DESC               (RW)    : origin=0x70180000 length=0x00004000
    /* MSS mailbox memory is used as shared memory, we don't use bottom 32*12 bytes, since its used as SW queue by ipc_notify */
    RTOS_NORTOS_IPC_SHM_MEM (RW)    : origin=0x72000000 length=0x00003E80
}

/* Alias for MCAL library sections */
--define=MCAL_CODE=L2_RAM_BANK0
--define=MCAL_ISR_CODE=L2_RAM_BANK0
--define=MCAL_DATA=L2_RAM_BANK0
--define=MCAL_BSS=L2_RAM_BANK0
--define=MCAL_NOINIT=L2_RAM_BANK0
--define=MCAL_CONST=L2_RAM_BANK0

/* Alias for MCAL application sections */
--define=APP_CODE=L2_RAM_BANK0
--define=APP_ISR_CODE=L2_RAM_BANK0
--define=APP_DATA=L2_RAM_BANK0
--define=APP_BSS=L2_RAM_BANK0
--define=APP_NOINIT=L2_RAM_BANK0
--define=APP_CONST=L2_RAM_BANK0

--define FILL_PATTERN=0xFEAA55EF
--define FILL_LENGTH=0x100

/* Stack Sizes for various modes */
__IRQ_STACK_SIZE   = 0x1000;
__FIQ_STACK_SIZE   = 0x1000;
__ABORT_STACK_SIZE = 0x1000;
__UND_STACK_SIZE   = 0x1000;
__SVC_STACK_SIZE   = 0x1000;

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */
SECTIONS
{
    /*
     * Special sections
     */
    .intvecs        : {} palign(8)      > RESET_VECTORS
    .startup        : {} palign(8)      > TCMA_RAM
    ipc_vring       : {}                > RTOS_NORTOS_IPC_SHM_MEM
    .tcma_buff      : {}                > TCMA_RAM
    .tcmb_buff      : {}                > TCMB_RAM
    .bss.ENET_CPPI_DESC  {*(.bss.ENET_CPPI_DESC)}  ALIGN (128) > CPPI_DESC

    /*
     * MCAL Library sections
     */
    /* Do this first before TEXT section */
    MCAL_ISR_CODE_SECTION:
    {
        .=align(8);
        __linker_mcal_isr_text_start = .;
        . += FILL_LENGTH;
       /* *(.*ISR_TEXT*) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcal_isr_text_end = .;
    } > MCAL_ISR_CODE, palign(8)
    MCAL_CODE_SECTION:
    {
        .=align(8);
        __linker_mcal_text_start = .;
        . += FILL_LENGTH;
        /* *(.*TEXT*) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcal_text_end = .;
    } > MCAL_CODE, palign(8)
    MCAL_CONST_SECTION:
    {
        .=align(8);
        __linker_mcal_const_start = .;
        . += FILL_LENGTH;
        *(.*CONST*)
        *(.*CONFIG*)
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcal_const_end = .;
    } > MCAL_CONST, palign(8)
    MCAL_DATA_SECTION:
    {
        .=align(8);
        __linker_mcal_data_start = .;
        . += FILL_LENGTH;
        /* *(.*DATA_INIT*) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcal_data_end = .;
    } > MCAL_DATA, palign(8)
    MCAL_BSS_SECTION:
    {
        .=align(8);
        __linker_mcal_bss_start = .;
        . += FILL_LENGTH;
        /* *(.*DATA_NO_INIT*) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcal_bss_end = .;
    } > MCAL_BSS, palign(8)

    /*
     * Common known library sections
     */
    GROUP {
        .text.cache : palign(8)
        .text.mpu   : palign(8)
        .text.boot  : palign(8)
    } > MCAL_CODE
    GROUP
    {
        .irqstack: {. = . + __IRQ_STACK_SIZE;} palign(8)
        RUN_START(__IRQ_STACK_START)
        RUN_END(__IRQ_STACK_END)
        .fiqstack: {. = . + __FIQ_STACK_SIZE;} palign(8)
        RUN_START(__FIQ_STACK_START)
        RUN_END(__FIQ_STACK_END)
        .svcstack: {. = . + __SVC_STACK_SIZE;} palign(8)
        RUN_START(__SVC_STACK_START)
        RUN_END(__SVC_STACK_END)
        .abortstack: {. = . + __ABORT_STACK_SIZE;} palign(8)
        RUN_START(__ABORT_STACK_START)
        RUN_END(__ABORT_STACK_END)
        .undefinedstack: {. = . + __UND_STACK_SIZE;} palign(8)
        RUN_START(__UNDEFINED_STACK_START)
        RUN_END(__UNDEFINED_STACK_END)
    } > L2_RAM_BANK0

    /*
     * Required for dynamic coverage
     */
    GROUP : > L2_RAM_BANK0
    {
        __llvm_prf_cnts
        __llvm_prf_bits
    }

    /*
     * Default sections at the end
     */
    .cinit          : load      > APP_DATA
    .stack          : load      > APP_DATA, fill=FILL_PATTERN
    .sysmem         : load      > APP_DATA

    .text.ospi_flash_xip_crc_test :
    {
        *(.text.ospi_flash_xip_crc_test)
        *(.text.ospi_flash_xip_crc_test.*)
    } > FLASH
    .text           : palign(8) > APP_CODE, fill=FILL_PATTERN
    {
        .=align(8);
        __linker_text_start = .;
        . += FILL_LENGTH;
        /* *(.text) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_text_end = .;
    }
    .rodata         : palign(8) load > APP_CONST, fill=FILL_PATTERN
    {
        .=align(8);
        __linker_const_start = .;
        . += FILL_LENGTH;
        /* *(.rodata) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_const_end = .;
    }
    .data           : palign(8) load > APP_DATA, fill=FILL_PATTERN
    {
        .=align(8);
        __linker_data_start = .;
        . += FILL_LENGTH;
        /* *(.data) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_data_end = .;
    }
    .bss            : palign(8) load > APP_BSS, fill=FILL_PATTERN
                      RUN_START(__BSS_START)
                      RUN_END(__BSS_END)
    {
        .=align(8);
        __linker_bss_start = .;
        . += FILL_LENGTH;
        /* *(.bss) */
        .=align(8);
        . += FILL_LENGTH;
        __linker_bss_end = .;
    }
}
