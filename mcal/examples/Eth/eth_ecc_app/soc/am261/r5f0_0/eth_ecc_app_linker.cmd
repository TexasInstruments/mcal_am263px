
/* This is the stack that is used by code running within main()
 * In case of NORTOS,
 * - This means all the code outside of ISR uses this stack
 * In case of FreeRTOS
 * - This means all the code until vTaskStartScheduler() is called in main()
 *   uses this stack.
 * - After vTaskStartScheduler() each task created in FreeRTOS has its own stack
 */
--stack_size=8192
/* This is the heap size for malloc() API in NORTOS and FreeRTOS
 * This is also the heap used by pvPortMalloc in FreeRTOS
 */
--heap_size=8192
-e_vectors  /* This is the entry of the application, _vector MUST be plabed starting address 0x0 */

/* This is the size of stack when R5 is in IRQ mode
 * In NORTOS,
 * - Here interrupt nesting is disabled as of now
 * - This is the stack used by ISRs registered as type IRQ
 * In FreeRTOS,
 * - Here interrupt nesting is enabled
 * - This is stack that is used initally when a IRQ is received
 * - But then the mode is switched to SVC mode and SVC stack is used for all user ISR callbacks
 * - Hence in FreeRTOS, IRQ stack size is less and SVC stack size is more
 */
__IRQ_STACK_SIZE = 256;
/* This is the size of stack when R5 is in IRQ mode
 * - In both NORTOS and FreeRTOS nesting is disabled for FIQ
 */
__FIQ_STACK_SIZE = 256;
__SVC_STACK_SIZE = 4096; /* This is the size of stack when R5 is in SVC mode */
__ABORT_STACK_SIZE = 256;  /* This is the size of stack when R5 is in ABORT mode */
__UNDEFINED_STACK_SIZE = 256;  /* This is the size of stack when R5 is in UNDEF mode */

    --define=MCAL_CODE1=OCRAM
    --define=MCAL_CODE2=OCRAM
    --define=MCAL_DATA=OCRAM
    --define=MCAL_BSS=OCRAM
    --define=MCAL_NOINIT=OCRAM
    --define=MCAL_CONST=OCRAM
    --define FILL_PATTERN=0xFEAA55EF
    --define FILL_LENGTH=0x100

SECTIONS
{
    /* This has the R5F entry point and vector table, this MUST be at 0x0 */
    .vectors:{} palign(8) > R5F_VECS

    /* This has the R5F boot code until MPU is enabled,  this MUST be at a address < 0x80000000
     * i.e this cannot be placed in DDR
     */
    GROUP {
        .text.hwi: palign(8)
        .text.cache: palign(8)
        .text.mpu: palign(8)
        .text.boot: palign(8)
        .text:abort: palign(8) /* this helps in loading symbols when using XIP mode */
    } > OCRAM

    /* This is rest of code. This can be placed in DDR if DDR is available and needed */
    GROUP {
        .text:   {} palign(8)   /* This is where code resides */
        .rodata: {} palign(8)   /* This is where const's go */
    } > OCRAM

    /* This is rest of initialized data. This can be placed in DDR if DDR is available and needed */
    GROUP {

        .data:   {} palign(8)   /* This is where initialized globals and static go */
    } > OCRAM

    /* This is rest of uninitialized data. This can be placed in DDR if DDR is available and needed */
    GROUP {
        .bss:    {} palign(8)   /* This is where uninitialized globals go */
        RUN_START(__BSS_START)
        RUN_END(__BSS_END)
        .sysmem: {} palign(8)   /* This is where the malloc heap goes */
        .stack:  {} palign(8)   /* This is where the main() stack goes */
    } > OCRAM

    /* This is where the stacks for different R5F modes go */
    GROUP {
        .irqstack: {. = . + __IRQ_STACK_SIZE;} align(8)
        RUN_START(__IRQ_STACK_START)
        RUN_END(__IRQ_STACK_END)
        .fiqstack: {. = . + __FIQ_STACK_SIZE;} align(8)
        RUN_START(__FIQ_STACK_START)
        RUN_END(__FIQ_STACK_END)
        .svcstack: {. = . + __SVC_STACK_SIZE;} align(8)
        RUN_START(__SVC_STACK_START)
        RUN_END(__SVC_STACK_END)
        .abortstack: {. = . + __ABORT_STACK_SIZE;} align(8)
        RUN_START(__ABORT_STACK_START)
        RUN_END(__ABORT_STACK_END)
        .undefinedstack: {. = . + __UNDEFINED_STACK_SIZE;} align(8)
        RUN_START(__UNDEFINED_STACK_START)
        RUN_END(__UNDEFINED_STACK_END)
    } > OCRAM

    /* Sections needed for C++ projects */
    GROUP {
        .ARM.exidx:  {} palign(8)   /* Needed for C++ exception handling */
        .init_array: {} palign(8)   /* Contains function pointers called before main */
        .fini_array: {} palign(8)   /* Contains function pointers called after main */
    } > OCRAM

McalTextSection : fill=FILL_PATTERN, palign(8) load > MCAL_CODE1
    {
        .=align(8);
        __linker_dio_text_start = .;
        . += FILL_LENGTH;
        *(DIO_TEXT_SECTION)
        *(DIO_ISR_TEXT_SECTION)
        *(DIO_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dio_text_end = .;

        .=align(8);
        __linker_gpt_text_start = .;
        . += FILL_LENGTH;
        *(GPT_TEXT_SECTION)
        *(GPT_ISR_TEXT_SECTION)
        *(GPT_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_gpt_text_end = .;

        .=align(8);
        __linker_mcu_text_start = .;
        . += FILL_LENGTH;
        *(MCU_TEXT_SECTION)
        *(MCU_ISR_TEXT_SECTION)
        *(MCU_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcu_text_end = .;

        .=align(8);
        __linker_port_text_start = .;
        . += FILL_LENGTH;
        *(PORT_TEXT_SECTION)
        *(PORT_ISR_TEXT_SECTION)
        *(PORT_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_port_text_end = .;

        .=align(8);
        __linker_wdg_text_start = .;
        . += FILL_LENGTH;
        *(WDG_TEXT_SECTION)
        *(WDG_ISR_TEXT_SECTION)
        *(WDG_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_wdg_text_end = .;

        .=align(8);
        __linker_spi_text_start = .;
        . += FILL_LENGTH;
        *(SPI_TEXT_SECTION)
        *(SPI_ISR_TEXT_SECTION)
        *(SPI_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_spi_text_end = .;

        .=align(8);
        __linker_can_text_start = .;
        . += FILL_LENGTH;
        *(CAN_TEXT_SECTION)
        *(CAN_ISR_TEXT_SECTION)
        *(CAN_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_can_text_end = .;

        .=align(8);
        __linker_lin_text_start = .;
        . += FILL_LENGTH;
        *(LIN_TEXT_SECTION)
        *(LIN_ISR_TEXT_SECTION)
        *(LIN_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_lin_text_end = .;

        .=align(8);
        __linker_pwm_text_start = .;
        . += FILL_LENGTH;
        *(PWM_TEXT_SECTION)
        *(PWM_ISR_TEXT_SECTION)
        *(PWM_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_pwm_text_end = .;

          .=align(8);
        __linker_icu_text_start = .;
        . += FILL_LENGTH;
        *(ICU_TEXT_SECTION)
        *(ICU_ISR_TEXT_SECTION)
        *(ICU_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_icu_text_end = .;

        .=align(8);
        __linker_adc_text_start = .;
        . += FILL_LENGTH;
        *(ADC_TEXT_SECTION)
        *(ADC_ISR_TEXT_SECTION)
        *(ADC_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_adc_text_end = .;

        .=align(8);
        __linker_fsirx_text_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_RX_TEXT_SECTION)
        *(CDD_FSI_RX_ISR_TEXT_SECTION)
        *(CDD_FSI_RX_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsirx_text_end = .;

        .=align(8);
        __linker_fsitx_text_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_TX_TEXT_SECTION)
        *(CDD_FSI_TX_ISR_TEXT_SECTION)
        *(CDD_FSI_TX_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsitx_text_end = .;
        
        .=align(8);
        __linker_ipc_text_start = .;
        . += FILL_LENGTH;
        *(IPC_TEXT_SECTION)
        *(IPC_ISR_TEXT_SECTION)
        *(IPC_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ipc_text_end = .;
        
        .=align(8);
        __linker_eth_text_start = .;
        . += FILL_LENGTH;
        *(ETH_TEXT_SECTION)
        *(ETH_ISR_TEXT_SECTION)
        *(ETH_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_eth_text_end = .;
    
        .=align(8);
        __linker_ethtrcv_text_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_TEXT_SECTION)
        *(ETHTRCV_ISR_TEXT_SECTION)
        *(ETHTRCV_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ethtrcv_text_end = .;
    
        .=align(4);
        __linker_uart_text_start = .;
        . += FILL_LENGTH;
        *(UART_TEXT_SECTION)
        *(UART_ISR_TEXT_SECTION)
        *(UART_CALLOUT_TEXT_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_uart_text_end = .;

        .=align(8);
        __linker_fls_text_start = .;
        . += FILL_LENGTH;
        *(FLS_TEXT_SECTION)
        *(FLS_ISR_TEXT_SECTION)
        *(FLS_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fls_text_end = .;
        
        
        
        .=align(8);
        __linker_dma_text_start = .;
        . += FILL_LENGTH;
        *(CDD_DMA_TEXT_SECTION)
        *(CDD_DMA_TEXT_SECTION)
        *(CDD_DMA_CALLOUT_TEXT_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dma_text_end = .;
    }

    McalConstSection : fill=FILL_PATTERN, palign(8) load > MCAL_CONST
    {
        .=align(8);
        __linker_dio_const_start = .;
        . += FILL_LENGTH;
        *(DIO_CONST_UNSPECIFIED_SECTION)
        *(DIO_CONST_32_SECTION)
        *(DIO_CONST_16_SECTION)
        *(DIO_CONST_8_SECTION)
        *(DIO_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dio_const_end = .;

        .=align(8);
        __linker_gpt_const_start = .;
        . += FILL_LENGTH;
        *(GPT_CONST_UNSPECIFIED_SECTION)
        *(GPT_CONST_32_SECTION)
        *(GPT_CONST_16_SECTION)
        *(GPT_CONST_8_SECTION)
        *(GPT_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_gpt_const_end = .;

        .=align(8);
        __linker_mcu_const_start = .;
        . += FILL_LENGTH;
        *(MCU_CONST_UNSPECIFIED_SECTION)
        *(MCU_CONST_32_SECTION)
        *(MCU_CONST_16_SECTION)
        *(MCU_CONST_8_SECTION)
        *(MCU_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcu_const_end = .;

        .=align(8);
        __linker_port_const_start = .;
        . += FILL_LENGTH;
        *(PORT_CONST_UNSPECIFIED_SECTION)
        *(PORT_CONST_32_SECTION)
        *(PORT_CONST_16_SECTION)
        *(PORT_CONST_8_SECTION)
        *(PORT_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_port_const_end = .;

        .=align(8);
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

        .=align(8);
        __linker_spi_const_start = .;
        . += FILL_LENGTH;
        *(SPI_CONST_UNSPECIFIED_SECTION)
        *(SPI_CONST_32_SECTION)
        *(SPI_CONST_16_SECTION)
        *(SPI_CONST_8_SECTION)
        *(SPI_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_spi_const_end = .;

        .=align(8);
        __linker_can_const_start = .;
        . += FILL_LENGTH;
        *(CAN_CONST_UNSPECIFIED_SECTION)
        *(CAN_CONST_32_SECTION)
        *(CAN_CONST_16_SECTION)
        *(CAN_CONST_8_SECTION)
        *(CAN_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_can_const_end = .;

        .=align(8);
        __linker_lin_const_start = .;
        . += FILL_LENGTH;
        *(LIN_CONST_UNSPECIFIED_SECTION)
        *(LIN_CONST_32_SECTION)
        *(LIN_CONST_16_SECTION)
        *(LIN_CONST_8_SECTION)
        *(LIN_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_lin_const_end = .;

        .=align(8);
        __linker_pwm_const_start = .;
        . += FILL_LENGTH;
        *(PWM_CONST_UNSPECIFIED_SECTION)
        *(PWM_CONST_32_SECTION)
        *(PWM_CONST_16_SECTION)
        *(PWM_CONST_8_SECTION)
        *(PWM_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_pwm_const_end = .;

        .=align(8);
        __linker_icu_const_start = .;
        . += FILL_LENGTH;
        *(ICU_CONST_UNSPECIFIED_SECTION)
        *(ICU_CONST_32_SECTION)
        *(ICU_CONST_16_SECTION)
        *(ICU_CONST_8_SECTION)
        *(ICU_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_icu_const_end = .;

        .=align(8);
        __linker_adc_const_start = .;
        . += FILL_LENGTH;
        *(ADC_CONST_UNSPECIFIED_SECTION)
        *(ADC_CONST_32_SECTION)
        *(ADC_CONST_16_SECTION)
        *(ADC_CONST_8_SECTION)
        *(ADC_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_adc_const_end = .;

        .=align(8);
        __linker_fsirx_const_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_RX_CONST_UNSPECIFIED_SECTION)
        *(CDD_FSI_RX_CONST_32_SECTION)
        *(CDD_FSI_RX_CONST_16_SECTION)
        *(CDD_FSI_RX_CONST_8_SECTION)
        *(CDD_FSI_RX_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsirx_const_end = .;

        .=align(8);
        __linker_fsitx_const_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_TX_CONST_UNSPECIFIED_SECTION)
        *(CDD_FSI_TX_CONST_32_SECTION)
        *(CDD_FSI_TX_CONST_16_SECTION)
        *(CDD_FSI_TX_CONST_8_SECTION)
        *(CDD_FSI_TX_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsitx_const_end = .;

        .=align(8);
        __linker_ipc_const_start = .;
        . += FILL_LENGTH;
        *(IPC_CONST_32_SECTION)
        *(IPC_CONST_UNSPECIFIED_SECTION)
        *(IPC_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ipc_const_end = .;
        
        .=align(8);
        __linker_eth_const_start = .;
        . += FILL_LENGTH;
        *(ETH_CONST_UNSPECIFIED_SECTION)
        *(ETH_CONST_32_SECTION)
        *(ETH_CONST_16_SECTION)
        *(ETH_CONST_8_SECTION)
        *(ETH_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_eth_const_end = .;
    
        .=align(8);
        __linker_ethtrcv_const_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_CONST_UNSPECIFIED_SECTION)
        *(ETHTRCV_CONST_32_SECTION)
        *(ETHTRCV_CONST_16_SECTION)
        *(ETHTRCV_CONST_8_SECTION)
        *(ETHTRCV_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ethtrcv_const_end = .;

        .=align(4);
        __linker_uart_const_start = .;
        . += FILL_LENGTH;
        *(UART_CONST_32_SECTION)
        *(UART_CONST_UNSPECIFIED_SECTION)
        *(UART_CONFIG_SECTION)
        .=align(4);
        . += FILL_LENGTH;
        __linker_uart_const_end = .;
    
            .=align(8);
        __linker_fls_const_start = .;
        . += FILL_LENGTH;
        *(FLS_CONST_32_SECTION)
        *(FLS_CONST_UNSPECIFIED_SECTION)
        *(FLS_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fls_const_end = .; 
        

        .=align(8);
        __linker_dma_const_start = .;
        . += FILL_LENGTH;
        *(CDD_DMA_CONST_UNSPECIFIED_SECTION)
        *(CDD_DMA_CONST_32_SECTION)
        *(CDD_DMA_CONST_16_SECTION)
        *(CDD_DMA_CONST_8_SECTION)
        *(CDD_DMA_CONFIG_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dma_const_end = .;
    }

    McalInitSection : palign(8) load > MCAL_DATA
    {
        .=align(8);
        __linker_dio_init_start = .;
        . += FILL_LENGTH;
        *(DIO_DATA_INIT_UNSPECIFIED_SECTION)
        *(DIO_DATA_INIT_32_SECTION)
        *(DIO_DATA_INIT_16_SECTION)
        *(DIO_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dio_init_end = .;

        .=align(8);
        __linker_gpt_init_start = .;
        . += FILL_LENGTH;
        *(GPT_DATA_INIT_UNSPECIFIED_SECTION)
        *(GPT_DATA_INIT_32_SECTION)
        *(GPT_DATA_INIT_16_SECTION)
        *(GPT_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_gpt_init_end = .;

        .=align(8);
        __linker_mcu_init_start = .;
        . += FILL_LENGTH;
        *(MCU_DATA_INIT_UNSPECIFIED_SECTION)
        *(MCU_DATA_INIT_32_SECTION)
        *(MCU_DATA_INIT_16_SECTION)
        *(MCU_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcu_init_end = .;

        .=align(8);
        __linker_port_init_start = .;
        . += FILL_LENGTH;
        *(PORT_DATA_INIT_UNSPECIFIED_SECTION)
        *(PORT_DATA_INIT_32_SECTION)
        *(PORT_DATA_INIT_16_SECTION)
        *(PORT_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_port_init_end = .;

        .=align(8);
        __linker_wdg_init_start = .;
        . += FILL_LENGTH;
        *(WDG_DATA_INIT_UNSPECIFIED_SECTION)
        *(WDG_DATA_INIT_32_SECTION)
        *(WDG_DATA_INIT_16_SECTION)
        *(WDG_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_wdg_init_end = .;

         .=align(8);
        __linker_spi_init_start = .;
        . += FILL_LENGTH;
        *(SPI_DATA_INIT_UNSPECIFIED_SECTION)
        *(SPI_DATA_INIT_32_SECTION)
        *(SPI_DATA_INIT_16_SECTION)
        *(SPI_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_spi_init_end = .;

        .=align(8);
        __linker_can_init_start = .;
        . += FILL_LENGTH;
        *(CAN_DATA_INIT_UNSPECIFIED_SECTION)
        *(CAN_DATA_INIT_32_SECTION)
        *(CAN_DATA_INIT_16_SECTION)
        *(CAN_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_can_init_end = .;

        .=align(8);
        __linker_lin_init_start = .;
        . += FILL_LENGTH;
        *(LIN_DATA_INIT_UNSPECIFIED_SECTION)
        *(LIN_DATA_INIT_32_SECTION)
        *(LIN_DATA_INIT_16_SECTION)
        *(LIN_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_lin_init_end = .;

        .=align(8);
        __linker_pwm_init_start = .;
        . += FILL_LENGTH;
        *(PWM_DATA_INIT_UNSPECIFIED_SECTION)
        *(PWM_DATA_INIT_32_SECTION)
        *(PWM_DATA_INIT_16_SECTION)
        *(PWM_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_pwm_init_end = .;

         .=align(8);
        __linker_icu_init_start = .;
        . += FILL_LENGTH;
        *(ICU_DATA_INIT_UNSPECIFIED_SECTION)
        *(ICU_DATA_INIT_32_SECTION)
        *(ICU_DATA_INIT_16_SECTION)
        *(ICU_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_icu_init_end = .;

        .=align(8);
        __linker_adc_init_start = .;
        . += FILL_LENGTH;
        *(ADC_DATA_INIT_UNSPECIFIED_SECTION)
        *(ADC_DATA_INIT_32_SECTION)
        *(ADC_DATA_INIT_16_SECTION)
        *(ADC_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_adc_init_end = .;

        .=align(8);
        __linker_fsirx_init_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_RX_DATA_INIT_UNSPECIFIED_SECTION)
        *(CDD_FSI_RX_DATA_INIT_32_SECTION)
        *(CDD_FSI_RX_DATA_INIT_16_SECTION)
        *(CDD_FSI_RX_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsirx_init_end = .;

         .=align(8);
        __linker_fsitx_init_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_TX_DATA_INIT_UNSPECIFIED_SECTION)
        *(CDD_FSI_TX_DATA_INIT_32_SECTION)
        *(CDD_FSI_TX_DATA_INIT_16_SECTION)
        *(CDD_FSI_TX_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsitx_init_end = .;

        .=align(8);
        __linker_ipc_init_start = .;
        . += FILL_LENGTH;
        *(IPC_DATA_INIT_UNSPECIFIED_SECTION)
        *(IPC_DATA_INIT_32_SECTION)
        *(IPC_DATA_INIT_16_SECTION)
        *(IPC_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ipc_init_end = .;
        
          .=align(8);
        __linker_eth_init_start = .;
        . += FILL_LENGTH;
        *(ETH_DATA_INIT_UNSPECIFIED_SECTION)
        *(ETH_DATA_INIT_32_SECTION)
        *(ETH_DATA_INIT_16_SECTION)
        *(ETH_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_eth_init_end = .;
    
          .=align(8);
        __linker_ethtrcv_init_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_DATA_INIT_UNSPECIFIED_SECTION)
        *(ETHTRCV_DATA_INIT_32_SECTION)
        *(ETHTRCV_DATA_INIT_16_SECTION)
        *(ETHTRCV_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ethtrcv_init_end = .;
    
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

        .=align(8);
        __linker_fls_init_start = .;
        . += FILL_LENGTH;
        *(FLS_DATA_INIT_32_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fls_init_end = .;
        
        

        .=align(8);
        __linker_dma_init_start = .;
        . += FILL_LENGTH;
        *(CDD_DMA_DATA_INIT_UNSPECIFIED_SECTION)
        *(CDD_DMA_DATA_INIT_32_SECTION)
        *(CDD_DMA_DATA_INIT_16_SECTION)
        *(CDD_DMA_DATA_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dma_init_end = .;
    }

    McalNoInitSection : palign(8) load > MCAL_NOINIT, type = NOINIT
    {
        .=align(8);
        __linker_dio_no_init_start = .;
        . += FILL_LENGTH;
        *(DIO_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(DIO_DATA_NO_INIT_32_SECTION)
        *(DIO_DATA_NO_INIT_16_SECTION)
        *(DIO_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dio_no_init_end = .;

        .=align(8);
        __linker_gpt_no_init_start = .;
        . += FILL_LENGTH;
        *(GPT_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(GPT_DATA_NO_INIT_32_SECTION)
        *(GPT_DATA_NO_INIT_16_SECTION)
        *(GPT_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_gpt_no_init_end = .;

        .=align(8);
        __linker_mcu_no_init_start = .;
        . += FILL_LENGTH;
        *(MCU_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(MCU_DATA_NO_INIT_32_SECTION)
        *(MCU_DATA_NO_INIT_16_SECTION)
        *(MCU_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_mcu_no_init_end = .;

        .=align(8);
        __linker_port_no_init_start = .;
        . += FILL_LENGTH;
        *(PORT_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(PORT_DATA_NO_INIT_32_SECTION)
        *(PORT_DATA_NO_INIT_16_SECTION)
        *(PORT_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_port_no_init_end = .;

        .=align(8);
        __linker_wdg_no_init_start = .;
        . += FILL_LENGTH;
        *(WDG_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(WDG_DATA_NO_INIT_32_SECTION)
        *(WDG_DATA_NO_INIT_16_SECTION)
        *(WDG_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_wdg_no_init_end = .;

         .=align(8);
        __linker_spi_no_init_start = .;
        . += FILL_LENGTH;
        *(SPI_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(SPI_DATA_NO_INIT_32_SECTION)
        *(SPI_DATA_NO_INIT_16_SECTION)
        *(SPI_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_spi_no_init_end = .;

        .=align(8);
        __linker_can_no_init_start = .;
        . += FILL_LENGTH;
        *(CAN_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(CAN_DATA_NO_INIT_32_SECTION)
        *(CAN_DATA_NO_INIT_16_SECTION)
        *(CAN_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_can_no_init_end = .;

        .=align(8);
        __linker_lin_no_init_start = .;
        . += FILL_LENGTH;
        *(LIN_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(LIN_DATA_NO_INIT_32_SECTION)
        *(LIN_DATA_NO_INIT_16_SECTION)
        *(LIN_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_lin_no_init_end = .;

        .=align(8);
        __linker_pwm_no_init_start = .;
        . += FILL_LENGTH;
        *(PWM_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(PWM_DATA_NO_INIT_32_SECTION)
        *(PWM_DATA_NO_INIT_16_SECTION)
        *(PWM_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_pwm_no_init_end = .;

        .=align(8);
        __linker_icu_no_init_start = .;
        . += FILL_LENGTH;
        *(ICU_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ICU_DATA_NO_INIT_32_SECTION)
        *(ICU_DATA_NO_INIT_16_SECTION)
        *(ICU_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_icu_no_init_end = .;

        .=align(8);
        __linker_adc_no_init_start = .;
        . += FILL_LENGTH;
        *(ADC_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ADC_DATA_NO_INIT_32_SECTION)
        *(ADC_DATA_NO_INIT_16_SECTION)
        *(ADC_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_adc_no_init_end = .;

        .=align(8);
        __linker_fsirx_no_init_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_RX_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(CDD_FSI_RX_DATA_NO_INIT_32_SECTION)
        *(CDD_FSI_RX_DATA_NO_INIT_16_SECTION)
        *(CDD_FSI_RX_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsirx_no_init_end = .;

        .=align(8);
        __linker_fsitx_no_init_start = .;
        . += FILL_LENGTH;
        *(CDD_FSI_TX_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(CDD_FSI_TX_DATA_NO_INIT_32_SECTION)
        *(CDD_FSI_TX_DATA_NO_INIT_16_SECTION)
        *(CDD_FSI_TX_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fsitx_no_init_end = .;

        .=align(8);
        __linker_ipc_no_init_start = .;
        . += FILL_LENGTH;
        *(IPC_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(IPC_DATA_NO_INIT_32_SECTION)
        *(IPC_DATA_NO_INIT_16_SECTION)
        *(IPC_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ipc_no_init_end = .;
        
             .=align(8);
        __linker_eth_no_init_start = .;
        . += FILL_LENGTH;
        *(ETH_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ETH_DATA_NO_INIT_32_SECTION)
        *(ETH_DATA_NO_INIT_16_SECTION)
        *(ETH_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_eth_no_init_end = .;
    
             .=align(8);
        __linker_ethtrcv_no_init_start = .;
        . += FILL_LENGTH;
        *(ETHTRCV_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(ETHTRCV_DATA_NO_INIT_32_SECTION)
        *(ETHTRCV_DATA_NO_INIT_16_SECTION)
        *(ETHTRCV_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_ethtrcv_no_init_end = .;   
        
    
             .=align(8);
        __linker_dma_no_init_start = .;
        . += FILL_LENGTH;
        *(CDD_DMA_DATA_NO_INIT_UNSPECIFIED_SECTION)
        *(CDD_DMA_DATA_NO_INIT_32_SECTION)
        *(CDD_DMA_DATA_NO_INIT_16_SECTION)
        *(CDD_DMA_DATA_NO_INIT_8_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_dma_no_init_end = .;
    
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

        .=align(8);
        __linker_fls_no_init_start = .;
        . += FILL_LENGTH;
        *(FLS_DATA_NO_INIT_UNSPECIFIED_SECTION)
        .=align(8);
        . += FILL_LENGTH;
        __linker_fls_no_init_end = .;
    }
    
    /* For NDK packet memory*/
    .bss.ENET_CPPI_DESC  {*(.bss.ENET_CPPI_DESC)}  ALIGN (128) > CPPI_DESC
    .bss:ENET_DMA_PKT_MEMPOOL  (NOLOAD) {} ALIGN (128) > OCRAM
}

/*
NOTE: Below memory is reserved for DMSC usage
 - During Boot till security handoff is complete
   0x701E0000 - 0x701FFFFF (128KB)
 - After "Security Handoff" is complete (i.e at run time)
   0x701FC000 - 0x701FFFFF (16KB)

 Security handoff is complete when this message is sent to the DMSC,
   TISCI_MSG_SEC_HANDOVER

 This should be sent once all cores are loaded and all application
 specific firewall calls are setup.
*/

MEMORY
{
    R5F_VECS  : ORIGIN = 0x00000000 , LENGTH = 0x00000040
    R5F_TCMA  : ORIGIN = 0x00000040 , LENGTH = 0x00007FC0
    R5F_TCMB  : ORIGIN = 0x00080000 , LENGTH = 0x00008000

    /* CPPI descriptor memory */
    CPPI_DESC : ORIGIN = 0x70140000 , LENGTH = 0x00004000
    
    /* when using multi-core application's i.e more than one R5F/M4F active, make sure
     * this memory does not overlap with other R5F's
     */
    OCRAM     : ORIGIN = 0x70040000 , LENGTH = 0x100000

    /* This section can be used to put XIP section of the application in flash, make sure this does not overlap with
     * other CPUs. Also make sure to add a MPU entry for this section and mark it as cached and code executable
     */
    FLASH     : ORIGIN = 0x60100000 , LENGTH = 0x80000 }

