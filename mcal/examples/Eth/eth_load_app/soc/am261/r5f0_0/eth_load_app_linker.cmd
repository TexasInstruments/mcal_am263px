

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
 --heap_size=1024
-e_vectors  /* This is the entry of the application, _vector MUST be placed starting address 0x0 */

/* This is the size of stack when R5 is in IRQ mode
 * In NORTOS,
 * - Here interrupt nesting is enabled
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



SECTIONS
{
    .vectors  : {
    } > R5F_VECS   , palign(8) 


    GROUP  :   {
    .text.hwi : {
    } palign(8)
    .text.cache : {
    } palign(8)
    .text.mpu : {
    } palign(8)
    .text.boot : {
    } palign(8)
    .text:abort : {
    } palign(8)
    } > OCRAM  


    GROUP  :   {
    .text : {
    } palign(8)
    .rodata : {
    } palign(8)
    } > OCRAM  


    GROUP  :   {
    .data : {
    } palign(8)
    } > OCRAM  


    GROUP  :   {
    .bss : {
    } palign(8)
    RUN_START(__BSS_START)
    RUN_END(__BSS_END)
    .sysmem : {
    } palign(8)
    .stack : {
    } palign(8)
    } > OCRAM  


    GROUP  :   {
    .irqstack : {
        . = . + __IRQ_STACK_SIZE;
    } align(8)
    RUN_START(__IRQ_STACK_START)
    RUN_END(__IRQ_STACK_END)
    .fiqstack : {
        . = . + __FIQ_STACK_SIZE;
    } align(8)
    RUN_START(__FIQ_STACK_START)
    RUN_END(__FIQ_STACK_END)
    .svcstack : {
        . = . + __SVC_STACK_SIZE;
    } align(8)
    RUN_START(__SVC_STACK_START)
    RUN_END(__SVC_STACK_END)
    .abortstack : {
        . = . + __ABORT_STACK_SIZE;
    } align(8)
    RUN_START(__ABORT_STACK_START)
    RUN_END(__ABORT_STACK_END)
    .undefinedstack : {
        . = . + __UNDEFINED_STACK_SIZE;
    } align(8)
    RUN_START(__UNDEFINED_STACK_START)
    RUN_END(__UNDEFINED_STACK_END)
    } > OCRAM  


    GROUP  :   {
    .ARM.exidx : {
    } palign(8)
    .init_array : {
    } palign(8)
    .fini_array : {
    } palign(8)
    } > OCRAM  

    .bss:ENET_CPPI_DESC (NOLOAD) : {
    } > CPPI_DESC   , align(128) 

    .bss:ENET_DMA_PKT_MEMPOOL (NOLOAD) : {
    } > OCRAM   , align(128) 


}


MEMORY
{
    R5F_VECS   : ORIGIN = 0x0 , LENGTH = 0x40 
    R5F_TCMA   : ORIGIN = 0x40 , LENGTH = 0x7FC0 
    R5F_TCMB   : ORIGIN = 0x80000 , LENGTH = 0x8000 
    CPPI_DESC   : ORIGIN = 0x70040000 , LENGTH = 0x4000 
    OCRAM   : ORIGIN = 0x70044000 , LENGTH = 0x13C000 
    SBL   : ORIGIN = 0x70000000 , LENGTH = 0x40000 
    FLASH   : ORIGIN = 0x60100000 , LENGTH = 0x80000 

    /* For memory Regions not defined in this core but shared by other cores with the current core */


}
