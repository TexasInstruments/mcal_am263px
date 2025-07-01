
/*
 * STACK SIZE MACRO DEFINITIONS
 */
#define M_USER_STACK_SIZE   0x1800   /* Multiple of 8 bytes - 6KB */
#define M_PREV_STACK_SIZE   0x10    /* Multiple of 8 bytes - 16B */

/*
 * LINKER OPTIONS
 */
--entry_point=_c_int000                   /* ENTRY POINT                   */
-stack  0x4000                            /* SOFTWARE STACK SIZE           */
-heap   0x4000                            /* HEAP AREA SIZE                */
--retain="*(.intvecs)"

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY{
PAGE 0:
    VECTORS  (X)  : origin=0x102EF000 length=0x00001000
    /*  Reset Vectors base address(RESET_VECTORS) should be 64 bytes aligned  */
    RESET_VECTORS (X) : origin=0x00000000 length=0x100
    /* RESET_VECTORS (X) : origin=0x00020000 length=0x100 */
    TCMA_RAM (RX) : origin=0x00000100 length=0x00003FC0
    TCMB_RAM (RW) : origin=0x00080000 length=0x00004000
    L2_RAM_BANK0 (RW) : origin=0x102A0000 length=0x00040000
    CPPI_DESC    (RW) : origin=0x102EB000 length=0x00004000 
    L3_RAM (RW)   : origin=0x88000000 length=0x00390000
    HWA_RAM (RW)  : origin=0x28000000 length=0x00020000
    RTOS_NORTOS_IPC_SHM_MEM : origin = 0xc5000000 length = 0x1F40

PAGE 1:
    L3_RAM (RW)   : origin=0x88000000 length=0x00390000
}

    --define=MCAL_CODE1=L2_RAM_BANK0
    --define=MCAL_CODE2=L2_RAM_BANK0
    --define=MCAL_DATA=L2_RAM_BANK0
    --define=MCAL_BSS=L2_RAM_BANK0
    --define=MCAL_NOINIT=L2_RAM_BANK0
    --define=MCAL_CONST=L2_RAM_BANK0
    --define FILL_PATTERN=0xFEAA55EF
    --define FILL_LENGTH=0x100

/* Stack Sizes for various modes */
__IRQ_STACK_SIZE = 0x1000;
__FIQ_STACK_SIZE = 0x1000;
__ABORT_STACK_SIZE = 0x1000;
__UND_STACK_SIZE = 0x1000;
__SVC_STACK_SIZE = 0x1000;

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs       : {} palign(8)      > RESET_VECTORS
    .startup       : {} palign(8)      > TCMA_RAM
    .systcmsysvimRam :                 > TCMA_RAM

    /* TEXT SECTION - Executable Code */
    .text               :                    >  MCAL_CODE1, fill=FILL_PATTERN
    {
        .=align(4);
        __linker_text_start = .;
        . += FILL_LENGTH;
        *(.text)
        .=align(4);
        . += FILL_LENGTH;
        __linker_text_end = .;
    }
	
	GROUP {
	
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


    /* CONST SECTION - Initialized Global Variables */
    .const      : load > MCAL_CONST, fill=FILL_PATTERN
    {
        .=align(4);
        __linker_const_start = .;
        . += FILL_LENGTH;
        *(.const)
        .=align(4);
        . += FILL_LENGTH;
        __linker_const_end = .;
    }

    /* RODATA SECTION - Initialized Static Variables */
    .rodata      : load > MCAL_CONST, fill=FILL_PATTERN
    {
        .=align(4);
        __linker_rodata_start = .;
        . += FILL_LENGTH;
        *(.const)
        .=align(4);
        . += FILL_LENGTH;
        __linker_rodata_end = .;
    }

    /* DATA SECTION - Initialized Data */
    .data       : load > MCAL_DATA
    {
        .=align(4);
        __linker_data_start = .;
        . += FILL_LENGTH;
        *(.data)
        .=align(4);
        . += FILL_LENGTH;
        __linker_data_end = .;
    }

    /* BSS SECTION - Contains Uninitialized Global variables */
    .bss        : load > MCAL_BSS
                    RUN_START(__BSS_START)
                    RUN_END(__BSS_END)
    {
        .=align(4);
        __linker_bss_start = .;
        . += FILL_LENGTH;
        *(.bss)
        .=align(4);
        . += FILL_LENGTH;
        __linker_bss_end = .;
    }

    /* CINIT SECTION - Tables which initializes global variables */
    .cinit      : load > MCAL_DATA

    /* STACK - System Stack */
    .stack      : load > MCAL_DATA, fill=FILL_PATTERN

    /* SYSMEM - Heap Memory */
    .sysmem     : load > MCAL_DATA

    ipc_vring (NOLOAD) : {} > RTOS_NORTOS_IPC_SHM_MEM

     /* MCPI Log Buffer */
    .MCPILogBuffer : load > MCAL_DATA
    McalTextSection : fill=FILL_PATTERN, align=4, load > MCAL_CODE1
    {

        .=align(4);
        __linker_ipc_text_start = .;
        . += FILL_LENGTH;
        *(IPC_TEXT_SECTION)
        *(IPC_ISR_TEXT_SECTION)
        *(IPC_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ipc_text_end = .;

        .=align(4);
        __linker_i2c_text_start = .;
        . += FILL_LENGTH;
        *(I2C_TEXT_SECTION)
        *(I2C_ISR_TEXT_SECTION)
        *(I2C_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_i2c_text_end = .;

        .=align(4);
        __linker_dio_text_start = .;
        . += FILL_LENGTH;
        *(DIO_TEXT_SECTION)
        *(DIO_ISR_TEXT_SECTION)
        *(DIO_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_dio_text_end = .;

        .=align(4);
        __linker_gpt_text_start = .;
        . += FILL_LENGTH;
        *(GPT_TEXT_SECTION)
        *(GPT_ISR_TEXT_SECTION)
        *(GPT_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_gpt_text_end = .;

        .=align(4);
        __linker_mcu_text_start = .;
        . += FILL_LENGTH;
        *(MCU_TEXT_SECTION)
        *(MCU_ISR_TEXT_SECTION)
        *(MCU_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_mcu_text_end = .;

        .=align(4);
        __linker_port_text_start = .;
        . += FILL_LENGTH;
        *(PORT_TEXT_SECTION)
        *(PORT_ISR_TEXT_SECTION)
        *(PORT_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_port_text_end = .;

        .=align(4);
        __linker_wdg_text_start = .;
        . += FILL_LENGTH;
        *(WDG_TEXT_SECTION)
        *(WDG_ISR_TEXT_SECTION)
        *(WDG_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_wdg_text_end = .;

		.=align(4);
        __linker_spi_text_start = .;
        . += FILL_LENGTH;
        *(SPI_TEXT_SECTION)
        *(SPI_ISR_TEXT_SECTION)
        *(SPI_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_spi_text_end = .;

		.=align(4);
        __linker_cdd_text_start = .;
        . += FILL_LENGTH;
        *(CDD_TEXT_SECTION)
        *(CDD_ISR_TEXT_SECTION)
        *(CDD_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_cdd_text_end = .;

        .=align(4);
        __linker_can_text_start = .;
        . += FILL_LENGTH;
        *(CAN_TEXT_SECTION)
        *(CAN_ISR_TEXT_SECTION)
        *(CAN_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_can_text_end = .;

        .=align(4);
        __linker_pwm_text_start = .;
        . += FILL_LENGTH;
        *(PWM_TEXT_SECTION)
        *(PWM_ISR_TEXT_SECTION)
        *(PWM_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_pwm_text_end = .;

        .=align(4);
        __linker_adc_text_start = .;
        . += FILL_LENGTH;
        *(ADC_TEXT_SECTION)
        *(ADC_ISR_TEXT_SECTION)
        *(ADC_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_adc_text_end = .;
		
	    .=align(4);
        __linker_eth_text_start = .;
        . += FILL_LENGTH;
        *(ETH_TEXT_SECTION)
        *(ETH_ISR_TEXT_SECTION)
        *(ETH_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_eth_text_end = .;
		
	    .=align(4);
        __linker_ethtrcv_text_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_TEXT_SECTION)
        *(ETHTRCV_ISR_TEXT_SECTION)
        *(ETHTRCV_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ethtrcv_text_end = .;
		
        .=align(4);
        __linker_icu_text_start = .;
        . += FILL_LENGTH;
        *(ICU_TEXT_SECTION)
        *(ICU_ISR_TEXT_SECTION)
        *(ICU_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_icu_text_end = .;

         .=align(4);
        __linker_fls_text_start = .;
        . += FILL_LENGTH;
        *(FLS_TEXT_SECTION)
        *(FLS_ISR_TEXT_SECTION)
        *(FLS_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_fls_text_end = .;

         .=align(4);
        __linker_uart_text_start = .;
        . += FILL_LENGTH;
        *(UART_TEXT_SECTION)
        *(UART_ISR_TEXT_SECTION)
        *(UART_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_uart_text_end = .;
    }

    McalConstSection : fill=FILL_PATTERN, align=4, load > MCAL_CONST
    {
        .=align(4);
        __linker_ipc_const_start = .;
        . += FILL_LENGTH;
        *(IPC_CONST_32_SECTION)
        *(IPC_CONST_UNSPECIFIED_SECTION)
        *(IPC_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ipc_const_end = .;

        .=align(4);
        __linker_i2c_const_start = .;
        . += FILL_LENGTH;
        *(I2C_CONST_32_SECTION)
        *(I2C_CONST_UNSPECIFIED_SECTION)
        *(I2C_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_i2c_const_end = .;

        .=align(4);
        __linker_dio_const_start = .;
        . += FILL_LENGTH;
        *(DIO_CONST_UNSPECIFIED_SECTION)
        *(DIO_CONST_32_SECTION)
        *(DIO_CONST_16_SECTION)
        *(DIO_CONST_8_SECTION)
        *(DIO_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_dio_const_end = .;

        .=align(4);
        __linker_gpt_const_start = .;
        . += FILL_LENGTH;
        *(GPT_CONST_UNSPECIFIED_SECTION)
        *(GPT_CONST_32_SECTION)
        *(GPT_CONST_16_SECTION)
        *(GPT_CONST_8_SECTION)
        *(GPT_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_gpt_const_end = .;

        .=align(4);
        __linker_mcu_const_start = .;
        . += FILL_LENGTH;
        *(MCU_CONST_UNSPECIFIED_SECTION)
        *(MCU_CONST_32_SECTION)
        *(MCU_CONST_16_SECTION)
        *(MCU_CONST_8_SECTION)
        *(MCU_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_mcu_const_end = .;

        .=align(4);
        __linker_port_const_start = .;
        . += FILL_LENGTH;
        *(PORT_CONST_UNSPECIFIED_SECTION)
        *(PORT_CONST_32_SECTION)
        *(PORT_CONST_16_SECTION)
        *(PORT_CONST_8_SECTION)
        *(PORT_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_port_const_end = .;

        .=align(4);
        __linker_wdg_const_start = .;
        . += FILL_LENGTH;
        *(WDG_CONST_UNSPECIFIED_SECTION)
        *(WDG_CONST_32_SECTION)
        *(WDG_CONST_16_SECTION)
        *(WDG_CONST_8_SECTION)
        *(WDG_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_wdg_const_end = .;

		.=align(4);
        __linker_spi_const_start = .;
        . += FILL_LENGTH;
        *(SPI_CONST_UNSPECIFIED_SECTION)
        *(SPI_CONST_32_SECTION)
        *(SPI_CONST_16_SECTION)
        *(SPI_CONST_8_SECTION)
        *(SPI_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_spi_const_end = .;

		.=align(4);
        __linker_cdd_const_start = .;
        . += FILL_LENGTH;
        *(CDD_CONST_UNSPECIFIED_SECTION)
        *(CDD_CONST_32_SECTION)
        *(CDD_CONST_16_SECTION)
        *(CDD_CONST_8_SECTION)
        *(CDD_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_cdd_const_end = .;

        .=align(4);
        __linker_can_const_start = .;
        . += FILL_LENGTH;
        *(CAN_CONST_UNSPECIFIED_SECTION)
        *(CAN_CONST_32_SECTION)
        *(CAN_CONST_16_SECTION)
        *(CAN_CONST_8_SECTION)
        *(CAN_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_can_const_end = .;

        .=align(4);
        __linker_pwm_const_start = .;
        . += FILL_LENGTH;
        *(PWM_CONST_UNSPECIFIED_SECTION)
        *(PWM_CONST_32_SECTION)
        *(PWM_CONST_16_SECTION)
        *(PWM_CONST_8_SECTION)
        *(PWM_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_pwm_const_end = .;

        .=align(4);
        __linker_adc_const_start = .;
        . += FILL_LENGTH;
        *(ADC_CONST_UNSPECIFIED_SECTION)
        *(ADC_CONST_32_SECTION)
        *(ADC_CONST_16_SECTION)
        *(ADC_CONST_8_SECTION)
        *(ADC_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_adc_const_end = .;
		
	    .=align(4);
        __linker_eth_const_start = .;
        . += FILL_LENGTH;
        *(ETH_CONST_UNSPECIFIED_SECTION)
        *(ETH_CONST_32_SECTION)
        *(ETH_CONST_16_SECTION)
        *(ETH_CONST_8_SECTION)
        *(ETH_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_eth_const_end = .;
		
	    .=align(4);
        __linker_ethtrcv_const_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_CONST_UNSPECIFIED_SECTION)
        *(ETHTRCV_CONST_32_SECTION)
        *(ETHTRCV_CONST_16_SECTION)
        *(ETHTRCV_CONST_8_SECTION)
        *(ETHTRCV_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ethtrcv_const_end = .;
		
        .=align(4);
        __linker_icu_const_start = .;
        . += FILL_LENGTH;
        *(ICU_CONST_UNSPECIFIED_SECTION)
        *(ICU_CONST_32_SECTION)
        *(ICU_CONST_16_SECTION)
        *(ICU_CONST_8_SECTION)
        *(ICU_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_icu_const_end = .;

         .=align(4);
        __linker_fls_const_start = .;
        . += FILL_LENGTH;
        *(FLS_CONST_UNSPECIFIED_SECTION)
        *(FLS_CONST_32_SECTION)
        *(FLS_CONST_16_SECTION)
        *(FLS_CONST_8_SECTION)
        *(FLS_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_fls_const_end = .;

         .=align(4);
        __linker_uart_const_start = .;
        . += FILL_LENGTH;
        *(UART_CONST_UNSPECIFIED_SECTION)
        *(UART_CONST_32_SECTION)
        *(UART_CONST_16_SECTION)
        *(UART_CONST_8_SECTION)
        *(UART_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_uart_const_end = .;
    }

    McalInitSection : align=4, load > MCAL_DATA
    {
        .=align(4);
        __linker_ipc_init_start = .;
        . += FILL_LENGTH;
        *(IPC_DATA_INIT_UNSPECIFIED_SECTION)
        *(IPC_DATA_INIT_32_SECTION)
        *(IPC_DATA_INIT_16_SECTION)
        *(IPC_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ipc_init_end = .;

        .=align(4);
        __linker_i2c_init_start = .;
        . += FILL_LENGTH;
        *(I2C_DATA_INIT_UNSPECIFIED_SECTION)
        *(I2C_DATA_INIT_32_SECTION)
        *(I2C_DATA_INIT_16_SECTION)
        *(I2C_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_i2c_init_end = .;

        .=align(4);
        __linker_dio_init_start = .;
        . += FILL_LENGTH;
        *(DIO_DATA_INIT_UNSPECIFIED_SECTION)
        *(DIO_DATA_INIT_32_SECTION)
        *(DIO_DATA_INIT_16_SECTION)
        *(DIO_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_dio_init_end = .;

        .=align(4);
        __linker_gpt_init_start = .;
        . += FILL_LENGTH;
        *(GPT_DATA_INIT_UNSPECIFIED_SECTION)
        *(GPT_DATA_INIT_PTR_SECTION)
        *(GPT_DATA_INIT_32_SECTION)
        *(GPT_DATA_INIT_16_SECTION)
        *(GPT_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_gpt_init_end = .;

        .=align(4);
        __linker_mcu_init_start = .;
        . += FILL_LENGTH;
        *(MCU_DATA_INIT_UNSPECIFIED_SECTION)
        *(MCU_DATA_INIT_PTR_SECTION)
        *(MCU_DATA_INIT_32_SECTION)
        *(MCU_DATA_INIT_16_SECTION)
        *(MCU_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_mcu_init_end = .;

        .=align(4);
        __linker_port_init_start = .;
        . += FILL_LENGTH;
        *(PORT_DATA_INIT_UNSPECIFIED_SECTION)
        *(PORT_DATA_INIT_32_SECTION)
        *(PORT_DATA_INIT_16_SECTION)
        *(PORT_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_port_init_end = .;

        .=align(4);
        __linker_wdg_init_start = .;
        . += FILL_LENGTH;
        *(WDG_DATA_INIT_UNSPECIFIED_SECTION)
        *(WDG_DATA_INIT_32_SECTION)
        *(WDG_DATA_INIT_16_SECTION)
        *(WDG_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_wdg_init_end = .;

		 .=align(4);
        __linker_spi_init_start = .;
        . += FILL_LENGTH;
        *(SPI_DATA_INIT_UNSPECIFIED_SECTION)
        *(SPI_DATA_INIT_32_SECTION)
        *(SPI_DATA_INIT_16_SECTION)
        *(SPI_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_spi_init_end = .;

		.=align(4);
        __linker_cdd_init_start = .;
        . += FILL_LENGTH;
        *(CDD_DATA_INIT_UNSPECIFIED_SECTION)
        *(CDD_DATA_INIT_32_SECTION)
        *(CDD_DATA_INIT_16_SECTION)
        *(CDD_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_cdd_init_end = .;

        .=align(4);
        __linker_can_init_start = .;
        . += FILL_LENGTH;
        *(CAN_DATA_INIT_UNSPECIFIED_SECTION)
        *(CAN_DATA_INIT_32_SECTION)
        *(CAN_DATA_INIT_16_SECTION)
        *(CAN_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_can_init_end = .;

        .=align(4);
        __linker_pwm_init_start = .;
        . += FILL_LENGTH;
        *(PWM_DATA_INIT_UNSPECIFIED_SECTION)
        *(PWM_DATA_INIT_PTR_SECTION)
        *(PWM_DATA_INIT_32_SECTION)
        *(PWM_DATA_INIT_16_SECTION)
        *(PWM_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_pwm_init_end = .;

        .=align(4);
        __linker_adc_init_start = .;
        . += FILL_LENGTH;
        *(ADC_DATA_INIT_UNSPECIFIED_SECTION)
        *(ADC_DATA_INIT_32_SECTION)
        *(ADC_DATA_INIT_16_SECTION)
        *(ADC_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_adc_init_end = .;
		
        .=align(4);
        __linker_eth_init_start = .;
        . += FILL_LENGTH;
        *(ETH_DATA_INIT_UNSPECIFIED_SECTION)
        *(ETH_DATA_INIT_32_SECTION)
        *(ETH_DATA_INIT_16_SECTION)
        *(ETH_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_eth_init_end = .;
		
        .=align(4);
        __linker_ethtrcv_init_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_DATA_INIT_UNSPECIFIED_SECTION)
        *(ETHTRCV_DATA_INIT_32_SECTION)
        *(ETHTRCV_DATA_INIT_16_SECTION)
        *(ETHTRCV_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ethtrcv_init_end = .;

         .=align(4);
        __linker_icu_init_start = .;
        . += FILL_LENGTH;
        *(ICU_DATA_INIT_UNSPECIFIED_SECTION)
        *(ICU_DATA_INIT_32_SECTION)
        *(ICU_DATA_INIT_16_SECTION)
        *(ICU_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_icu_init_end = .;

         .=align(4);
        __linker_fls_init_start = .;
        . += FILL_LENGTH;
        *(FLS_DATA_INIT_UNSPECIFIED_SECTION)
        *(FLS_DATA_INIT_32_SECTION)
        *(FLS_DATA_INIT_16_SECTION)
        *(FLS_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_fls_init_end = .;

         .=align(4);
        __linker_uart_init_start = .;
        . += FILL_LENGTH;
        *(UART_DATA_INIT_UNSPECIFIED_SECTION)
        *(UART_DATA_INIT_32_SECTION)
        *(UART_DATA_INIT_16_SECTION)
        *(UART_DATA_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_uart_init_end = .;
    }

    McalNoInitSection : align=4, load > MCAL_NOINIT, type = NOINIT
    {
        .=align(4);
        __linker_dio_no_init_start = .;
        . += FILL_LENGTH;
        *(DIO_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(DIO_DATA_NO_INIT_32_SECTION)
        *(DIO_DATA_NO_INIT_16_SECTION)
        *(DIO_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_dio_no_init_end = .;

        .=align(4);
        __linker_ipc_no_init_start = .;
        . += FILL_LENGTH;
        *(IPC_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(IPC_DATA_NO_INIT_32_SECTION)
        *(IPC_DATA_NO_INIT_16_SECTION)
        *(IPC_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ipc_no_init_end = .;

        .=align(4);
        __linker_i2c_no_init_start = .;
        . += FILL_LENGTH;
        *(I2C_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(I2C_DATA_NO_INIT_32_SECTION)
        *(I2C_DATA_NO_INIT_16_SECTION)
        *(I2C_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_i2c_no_init_end = .;

        .=align(4);
        __linker_gpt_no_init_start = .;
        . += FILL_LENGTH;
        *(GPT_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(GPT_DATA_NO_INIT_32_SECTION)
        *(GPT_DATA_NO_INIT_16_SECTION)
        *(GPT_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_gpt_no_init_end = .;

        .=align(4);
        __linker_mcu_no_init_start = .;
        . += FILL_LENGTH;
        *(MCU_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(MCU_DATA_NO_INIT_32_SECTION)
        *(MCU_DATA_NO_INIT_16_SECTION)
        *(MCU_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_mcu_no_init_end = .;

        .=align(4);
        __linker_port_no_init_start = .;
        . += FILL_LENGTH;
        *(PORT_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(PORT_DATA_NO_INIT_32_SECTION)
        *(PORT_DATA_NO_INIT_16_SECTION)
        *(PORT_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_port_no_init_end = .;

        .=align(4);
        __linker_wdg_no_init_start = .;
        . += FILL_LENGTH;
        *(WDG_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(WDG_DATA_NO_INIT_32_SECTION)
        *(WDG_DATA_NO_INIT_16_SECTION)
        *(WDG_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_wdg_no_init_end = .;

		 .=align(4);
        __linker_spi_no_init_start = .;
        . += FILL_LENGTH;
        *(SPI_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(SPI_DATA_NO_INIT_32_SECTION)
        *(SPI_DATA_NO_INIT_16_SECTION)
        *(SPI_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_spi_no_init_end = .;

		.=align(4);
        __linker_cdd_no_init_start = .;
        . += FILL_LENGTH;
        *(CDD_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(CDD_DATA_NO_INIT_32_SECTION)
        *(CDD_DATA_NO_INIT_16_SECTION)
        *(CDD_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_cdd_no_init_end = .;

        .=align(4);
        __linker_can_no_init_start = .;
        . += FILL_LENGTH;
        *(CAN_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(CAN_DATA_NO_INIT_32_SECTION)
        *(CAN_DATA_NO_INIT_16_SECTION)
        *(CAN_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_can_no_init_end = .;

        .=align(4);
        __linker_pwm_no_init_start = .;
        . += FILL_LENGTH;
        *(PWM_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(PWM_DATA_NO_INIT_32_SECTION)
        *(PWM_DATA_NO_INIT_16_SECTION)
        *(PWM_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_pwm_no_init_end = .;

        .=align(4);
        __linker_adc_no_init_start = .;
        . += FILL_LENGTH;
        *(ADC_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ADC_DATA_NO_INIT_32_SECTION)
        *(ADC_DATA_NO_INIT_16_SECTION)
        *(ADC_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_adc_no_init_end = .;
		
        .=align(4);
        __linker_eth_no_init_start = .;
        . += FILL_LENGTH;
        *(ETH_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ETH_DATA_NO_INIT_32_SECTION)
        *(ETH_DATA_NO_INIT_16_SECTION)
        *(ETH_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_eth_no_init_end = .;
		
        __linker_ethtrcv_no_init_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ETHTRCV_DATA_NO_INIT_32_SECTION)
        *(ETHTRCV_DATA_NO_INIT_16_SECTION)
        *(ETHTRCV_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_ethtrcv_no_init_end = .;

        .=align(4);
        __linker_icu_no_init_start = .;
        . += FILL_LENGTH;
        *(ICU_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ICU_DATA_NO_INIT_32_SECTION)
        *(ICU_DATA_NO_INIT_16_SECTION)
        *(ICU_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_icu_no_init_end = .;

        .=align(4);
        __linker_fls_no_init_start = .;
        . += FILL_LENGTH;
        *(FLS_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(FLS_DATA_NO_INIT_32_SECTION)
        *(FLS_DATA_NO_INIT_16_SECTION)
        *(FLS_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_fls_no_init_end = .;

        .=align(4);
        __linker_uart_no_init_start = .;
        . += FILL_LENGTH;
        *(UART_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(UART_DATA_NO_INIT_32_SECTION)
        *(UART_DATA_NO_INIT_16_SECTION)
        *(UART_DATA_NO_INIT_8_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_uart_no_init_end = .;
    }

	.bss.ENET_CPPI_DESC  {*(.bss.ENET_CPPI_DESC)}  ALIGN (128) > CPPI_DESC
	

}

