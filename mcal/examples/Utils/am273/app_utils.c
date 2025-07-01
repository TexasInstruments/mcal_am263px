/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file     app_utils.c
 *
 *  \brief    This file contains common utility functions used by the MCAL apps
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"
#include "Std_Types.h"
#include "string.h"
/*LDRA_ANALYSIS*/
#include "Port.h"

#include "mcal_hw_soc_baseaddress.h"
#include "hw_ctrl_core.h"
#include "hal_stdtypes.h"
#include "soc.h"

#include "soc_rcm.h"
#include "reg_sci.h"
#include "sci.h"
#include "sys_core.h"

#include "app_utils.h"
#include "Os.h"
#include "hw_types.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define APP_UTILS_ARRAYSIZE(array) ((sizeof(array) / sizeof((array)[0])))

#define APP_UTILS_LINKER_FILL_LENGTH  (0x100U)
#define APP_UTILS_LINKER_FILL_PATTERN (0xFEAA55EFU)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

bool TIMEOUT_CODE_COVERAGE = FALSE;

extern uint32 __stack, __STACK_SIZE;
extern uint32 __linker_text_start, __linker_text_end, __linker_const_start, __linker_const_end, __linker_data_start,
    __linker_data_end, __linker_bss_start, __linker_bss_end;
extern uint32 __linker_gpt_text_start, __linker_gpt_text_end, __linker_gpt_const_start, __linker_gpt_const_end,
    __linker_gpt_init_start, __linker_gpt_init_end, __linker_gpt_no_init_start, __linker_gpt_no_init_end;
extern uint32 __linker_mcu_text_start, __linker_mcu_text_end, __linker_mcu_const_start, __linker_mcu_const_end,
    __linker_mcu_init_start, __linker_mcu_init_end, __linker_mcu_no_init_start, __linker_mcu_no_init_end;
extern uint32 __linker_port_text_start, __linker_port_text_end, __linker_port_const_start, __linker_port_const_end,
    __linker_port_init_start, __linker_port_init_end, __linker_port_no_init_start, __linker_port_no_init_end;
extern uint32 __linker_dio_text_start, __linker_dio_text_end, __linker_dio_const_start, __linker_dio_const_end,
    __linker_dio_init_start, __linker_dio_init_end, __linker_dio_no_init_start, __linker_dio_no_init_end;
extern uint32 __linker_wdg_text_start, __linker_wdg_text_end, __linker_wdg_const_start, __linker_wdg_const_end,
    __linker_wdg_init_start, __linker_wdg_init_end, __linker_wdg_no_init_start, __linker_wdg_no_init_end;
extern uint32 __linker_spi_text_start, __linker_spi_text_end, __linker_spi_const_start, __linker_spi_const_end,
    __linker_spi_init_start, __linker_spi_init_end, __linker_spi_no_init_start, __linker_spi_no_init_end;
extern uint32 __linker_cdd_text_start, __linker_cdd_text_end, __linker_cdd_const_start, __linker_cdd_const_end,
    __linker_cdd_init_start, __linker_cdd_init_end, __linker_cdd_no_init_start, __linker_cdd_no_init_end;
extern uint32 __linker_can_text_start, __linker_can_text_end, __linker_can_const_start, __linker_can_const_end,
    __linker_can_init_start, __linker_can_init_end, __linker_can_no_init_start, __linker_can_no_init_end;
extern uint32 __linker_pwm_text_start, __linker_pwm_text_end, __linker_pwm_const_start, __linker_pwm_const_end,
    __linker_pwm_init_start, __linker_pwm_init_end, __linker_pwm_no_init_start, __linker_pwm_no_init_end;
extern uint32 __linker_adc_text_start, __linker_adc_text_end, __linker_adc_const_start, __linker_adc_const_end,
    __linker_adc_init_start, __linker_adc_init_end, __linker_adc_no_init_start, __linker_adc_no_init_end;
extern uint32 __linker_eth_text_start, __linker_eth_text_end, __linker_eth_const_start, __linker_eth_const_end,
    __linker_eth_init_start, __linker_eth_init_end, __linker_eth_no_init_start, __linker_eth_no_init_end;
extern uint32 __linker_ethtrcv_text_start, __linker_ethtrcv_text_end, __linker_ethtrcv_const_start,
    __linker_ethtrcv_const_end, __linker_ethtrcv_init_start, __linker_ethtrcv_init_end, __linker_ethtrcv_no_init_start,
    __linker_ethtrcv_no_init_end;
extern uint32 __linker_fls_text_start, __linker_fls_text_end, __linker_fls_const_start, __linker_fls_const_end,
    __linker_fls_init_start, __linker_fls_init_end, __linker_fls_no_init_start, __linker_fls_no_init_end;

static uint32 gAppUtilsSecHoleAddrList[] = {
    ((uint32)&__linker_text_start),
    ((uint32)&__linker_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_const_start),
    ((uint32)&__linker_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_data_start),
    ((uint32)&__linker_data_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_bss_start),
    ((uint32)&__linker_bss_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_dio_text_start),
    ((uint32)&__linker_dio_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_dio_const_start),
    ((uint32)&__linker_dio_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_dio_init_start),
    ((uint32)&__linker_dio_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_dio_no_init_start),
    ((uint32)&__linker_dio_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_gpt_text_start),
    ((uint32)&__linker_gpt_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_gpt_const_start),
    ((uint32)&__linker_gpt_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_gpt_init_start),
    ((uint32)&__linker_gpt_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_gpt_no_init_start),
    ((uint32)&__linker_gpt_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_mcu_text_start),
    ((uint32)&__linker_mcu_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_mcu_const_start),
    ((uint32)&__linker_mcu_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_mcu_init_start),
    ((uint32)&__linker_mcu_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_mcu_no_init_start),
    ((uint32)&__linker_mcu_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_port_text_start),
    ((uint32)&__linker_port_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_port_const_start),
    ((uint32)&__linker_port_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_port_init_start),
    ((uint32)&__linker_port_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_port_no_init_start),
    ((uint32)&__linker_port_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_wdg_text_start),
    ((uint32)&__linker_wdg_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_wdg_const_start),
    ((uint32)&__linker_wdg_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_wdg_init_start),
    ((uint32)&__linker_wdg_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_wdg_no_init_start),
    ((uint32)&__linker_wdg_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_spi_text_start),
    ((uint32)&__linker_spi_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_spi_const_start),
    ((uint32)&__linker_spi_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_spi_init_start),
    ((uint32)&__linker_spi_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_spi_no_init_start),
    ((uint32)&__linker_spi_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_text_start),
    ((uint32)&__linker_cdd_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_const_start),
    ((uint32)&__linker_cdd_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_init_start),
    ((uint32)&__linker_cdd_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_no_init_start),
    ((uint32)&__linker_cdd_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_can_text_start),
    ((uint32)&__linker_can_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_can_const_start),
    ((uint32)&__linker_can_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_can_init_start),
    ((uint32)&__linker_can_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_can_no_init_start),
    ((uint32)&__linker_can_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_pwm_text_start),
    ((uint32)&__linker_pwm_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_pwm_const_start),
    ((uint32)&__linker_pwm_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_pwm_init_start),
    ((uint32)&__linker_pwm_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_pwm_no_init_start),
    ((uint32)&__linker_pwm_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_adc_text_start),
    ((uint32)&__linker_adc_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_adc_const_start),
    ((uint32)&__linker_adc_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_adc_init_start),
    ((uint32)&__linker_adc_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_adc_no_init_start),
    ((uint32)&__linker_adc_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_eth_text_start),
    ((uint32)&__linker_eth_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_eth_const_start),
    ((uint32)&__linker_eth_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_eth_init_start),
    ((uint32)&__linker_eth_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_eth_no_init_start),
    ((uint32)&__linker_eth_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_ethtrcv_text_start),
    ((uint32)&__linker_ethtrcv_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_ethtrcv_const_start),
    ((uint32)&__linker_ethtrcv_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_ethtrcv_init_start),
    ((uint32)&__linker_ethtrcv_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_ethtrcv_no_init_start),
    ((uint32)&__linker_ethtrcv_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fls_text_start),
    ((uint32)&__linker_fls_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fls_const_start),
    ((uint32)&__linker_fls_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fls_init_start),
    ((uint32)&__linker_fls_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fls_no_init_start),
    ((uint32)&__linker_fls_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
};

#define APP_UTILS_NUM_SEC_HOLES (sizeof(gAppUtilsSecHoleAddrList) / sizeof(gAppUtilsSecHoleAddrList[0]))

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APPUTILS_UART_INPUT (STD_ON)

/** brief Overflow count value for 32bit counter */
#define APPUTILS_COUNTER_MAX_COUNT (0xFFFFFFFFU)

#define pinMuxBase ((uint32 *)0x020C0000)

uint32 frc_ticks;

void AppUtils_SchM_Enter_EXCLUSIVE_AREA_0()
{
#ifdef DIAB
    __asm(" CPSID I");
#else
    asm(" CPSID I");
#endif
}

void AppUtils_SchM_Exit_EXCLUSIVE_AREA_0()
{
#ifdef DIAB
    __asm(" CPSIE I");
#else
    asm(" CPSIE I");
#endif
}
void *my_memset(void *s, int c, uint32 len)
{
    uint8 *p = (uint8 *)s;
    while (len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

#if defined(CLANG)
__size_t strnlen(const char *s, __size_t maxlen)
{
    __size_t len;

    for (len = 0; len < maxlen; len++, s++)
    {
        if (!*s)
        {
            break;
        }
    }
    return (len);
}
#endif

void my_memcpy(void *dest, void *src, uint32 n)
{
    uint32 i;
    // Typecast src and dest addresses to (int8 *)
    uint8 *csrc  = (uint8 *)src;
    uint8 *cdest = (uint8 *)dest;

    // Copy contents of src[] to dest[]
    for (i = 0; i < n; i++)
    {
        cdest[i] = csrc[i];
    }
}

void start_timer(void)
{
    /* Enables RTI0 timer*/
    HW_WR_REG32(0x02F7A000, 0x00000000);  // GCTRL
    HW_WR_REG32(0x02F7A008, 0x00000000);  // Capture Control
    HW_WR_REG32(0x02F7A00C, 0x00000000);  // COMP CTRL
    HW_WR_REG32(0x02F7A010, 0x00000000);  // FRC0
    HW_WR_REG32(0x02F7A014, 0x00000000);  // UP Counter
    HW_WR_REG32(0x02F7A018, 0x000000C7);  // Compare Up Counter
    HW_WR_REG32(0x02F7A084, 0x00070F0F);  // Clear Interrupt
    HW_WR_REG32(0x02F7A000, 0x00000001);  // GCTRL Start Timer
}

void stop_timer(void)
{
    HW_WR_REG32(0x02F7A000, 0x00000000);  // GCTRL Stop Timer
}

void AppUtils_TimerInit()
{
    start_timer();
}

void AppUtils_TimerDeinit()
{
    stop_timer();
}

uint32 AppUtils_ClockGetTicks(void)
{
    return (uint32)(HW_RD_REG32(0x02F7A010));
}

static uint32 AppUtils_checkSectionCorruption(uint32 secStartAddr)
{
    uint32  retVal      = E_OK, i;
    uint32 *secStartPtr = ((uint32 *)secStartAddr);
    uint32  fillPattern = APP_UTILS_LINKER_FILL_PATTERN;
    uint32  fillLength  = APP_UTILS_LINKER_FILL_LENGTH;

    i = 0U;
    while (i < fillLength)
    {
        if (*secStartPtr != fillPattern)
        {
            retVal = E_NOT_OK;
            break;
        }
        secStartPtr++;
        i += sizeof(uint32);
    }

    i = *secStartPtr;
    return (retVal);
}

uint32 AppUtils_checkStackAndSectionCorruption(void)
{
    uint32 retVal = E_OK, index;
    uint32 stackUsed, stackSize = ((uint32)&__STACK_SIZE);

    stackUsed = AppUtils_getStackUsage();
    if (stackUsed >= stackSize)
    {
        retVal = E_NOT_OK;
    }

    if (E_OK == retVal)
    {
        for (index = 0U; index < APP_UTILS_NUM_SEC_HOLES; index++)
        {
            retVal = AppUtils_checkSectionCorruption(gAppUtilsSecHoleAddrList[index]);
            if (E_OK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

static void AppUtils_memsetWord(uint32 *memPtr, uint32 pattern, uint32 length)
{
    while (length > 0U)
    {
        *memPtr = pattern;
        memPtr++;
        length--;
    }

    return;
}

void AppUtils_sectionInit(void)
{
    uint32 index;

    for (index = 0U; index < APP_UTILS_NUM_SEC_HOLES; index++)
    {
        AppUtils_memsetWord(((uint32 *)gAppUtilsSecHoleAddrList[index]), APP_UTILS_LINKER_FILL_PATTERN,
                            (APP_UTILS_LINKER_FILL_LENGTH / sizeof(uint32)));
    }

    return;
}

uint32 AppUtils_getStackUsage(void)
{
    uint32 *stackStart = &__stack;
    uint32  freeEntry, stackSize = ((uint32)&__STACK_SIZE);
    uint32  fillPattern = APP_UTILS_LINKER_FILL_PATTERN;

    freeEntry = 0U;
    while (1)
    {
        if (*stackStart != fillPattern)
        {
            break;
        }
        stackStart++;
        freeEntry += sizeof(uint32);
    }

    return (stackSize - freeEntry);
}

uint32 AppUtils_getCurTimeInMsec(void)
{
    uint32     timerCount, curTimeMsec = 0U;
    StatusType status;

    status = GetCounterValue(APP_UTILS_COUNTER_ID, &timerCount);
    if (E_OK == status)
    {
        curTimeMsec = (uint32)(((float32)timerCount * 1000.0) / APP_UTILS_COUNTER_FREQ);
    }

    return (curTimeMsec);
}

void Det_Timeout(bool time_status)
{
    TIMEOUT_CODE_COVERAGE = time_status;
}

uint32 AppUtils_getElapsedTimeInMsec(uint32 startTime)
{
    uint32     elapsedTimeMsec = 0U;
    uint32     startCount = 0U, tempCount = 0U, elapsedCount = 0U;
    StatusType status;

    startCount = (uint32)(((float32)startTime * APP_UTILS_COUNTER_FREQ) / 1000.0);

    /* Below API can change start time, so use temp variable */
    tempCount = startCount;
    status    = GetElapsedValue(APP_UTILS_COUNTER_ID, &tempCount, &elapsedCount);
    if (E_OK == status)
    {
        elapsedTimeMsec = (uint32)(((float32)elapsedCount * 1000.0) / APP_UTILS_COUNTER_FREQ);
    }

    return (elapsedTimeMsec);
}

void AppUtils_delay(uint32 msec)
{
    uint32 start = HW_RD_REG32(0x02F7A010);
    while ((msec * 1000) > (HW_RD_REG32(0x02F7A010) - start))
    {
    }
    return;
}

void AppUtils_printf(const char *pStr, ...)
{
    static char tempBuf[3000];
    va_list     vaArgP;

    /* Start the varargs processing. */
    va_start(vaArgP, pStr);

    vsnprintf(&tempBuf[0U], sizeof(tempBuf), pStr, vaArgP);

    // printf("%s", &tempBuf[0U]);

    message(sciAREG, (const uint8 *)&tempBuf);

    /* End the varargs processing. */
    va_end(vaArgP);

    return;
}

char AppUtils_getChar(void)
{
    char ch;

    getCharacter(sciAREG, (uint8 *)&ch, sizeof(char));

    return (ch);
}

sint32 AppUtils_getNum(void)
{
    sint32 value = 0;
    sint32 sign  = 1;
    char   rxByte;

    rxByte = AppUtils_getChar();

    /* Accounting for negative numbers.*/
    if ((sint8)'-' == rxByte)
    {
        sign = -1;
    }
    else
    {
        value = value * 10 + (rxByte - 0x30);
    }

    do
    {
        rxByte = (char)AppUtils_getChar();

        /*
        ** Checking if the entered character is a carriage return.
        ** Pressing the 'Enter' key on the keyboard executes a
        ** carriage return on the serial console.
        */
        if ((sint8)'\r' == rxByte)
        {
            break;
        }
        /*
        ** Subtracting 0x30 to convert the representation of the digit
        ** from ASCII to hexadecimal.
        */
        value = value * 10 + (rxByte - 0x30);
    } while (1);

    /* Accounting for the sign of the number.*/
    value = value * sign;

    return value;
}

void Apps_switch_to_system_mode(void)
{
#ifdef DIAB
    __asm("  MOV r0, #0 ");
    __asm("  SVC #0 ");
    __asm("  BX lr ");

#else
    asm("  MOV r0, #0 ");
    asm("  SVC #0 ");
    asm("  BX lr ");
#endif
}

void AppUtils_defaultInit(void)
{
    Apps_switch_to_system_mode();

    // Enable_Uart(SYS_CLOCK_FREQ_XTAL);

    // AppUtils_sectionInit();
}

void AppUtils_defaultInitDiab(void)
{
    // Apps_switch_to_system_mode();

    Enable_Uart(SYS_CLOCK_FREQ_XTAL);

    AppUtils_sectionInit();
}

/** @fn sint32 pinSelectFunc(uint32 pin, uint32 func)
 *   @brief Setup the pin personality.
 *
 *   This function sets up the functional personality of the pin.
 *   The specified signal will be brought out on the pin.
 *   As there is no strict check on the parameters passed, the values passed
 *   must be from the macro specified in the header pinmux.h.
 *
 *    @param[in] pin: Pin number to be configured
 *    @param[in] func: Desired signal functionality to be muxed onto the pin
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
sint32 app_utils_pinSelectFunc(uint32 pin, uint32 func)
{
    sint32 retVal;

    /* Check the validity of the pin number to be configured */
    if (pin > 0x19C)
    {
        /* Error in the pin number */
        retVal = -1;
    }
    else
    {
        /* Mask the existing functionality of the pin */
        pinMuxBase[(pin / 4U)] &= PIN_FUNCTION_SEL_MASK;

        /* Setup the required fucntionality */
        pinMuxBase[(pin / 4U)] |= (func & ~PIN_FUNCTION_SEL_MASK);

        retVal = 0;
    }
    return retVal;
}

/** @fn void pinmuxUnlock(pinMuxBase_t *pinMuxRegp)
 *   @brief Configure the key to enable the pinmuxing.
 *
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void app_utils_pinmuxUnlock(pinMuxBase_t *pinMuxRegp)
{
    /* Enable Pin Muxing */
    /* Value of pinMuxRegp can be pinMuxReg */
    pinMuxRegp->IOCFGKICK0 = 0x83E70B13U;
    pinMuxRegp->IOCFGKICK1 = 0x95A4F1E0U;
}

/** @fn void pinmuxLock(pinMuxBase_t *pinMuxRegp)
 *   @brief Lock to disable the pinmuxing.
 *
 */
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
void app_utils_pinmuxLock(pinMuxBase_t *pinMuxRegp)
{
    /* Disable Pin Muxing */
    /* Value of pinMuxRegp can be pinMuxReg */
    pinMuxRegp->IOCFGKICK1 = 0x0U;
    pinMuxRegp->IOCFGKICK0 = 0x0U;
}

/* Table populated from TPR12_ADPLLJ_Settings_1p0.xlsx.
 * Each entry corresponds to tab in the excel sheet
 */
static const SOC_RcmADPLLJConfig gSocRcmADPLLJConfigTbl[] = {
    /* DSP_900_40MHz  */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 900U,
        .M2    = 1U,
        .M     = 900U,
        .FracM = 0U,
    },
    /* CORE_DSP_800_40MHz */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 800U,
        .FracM = 0U,
    },
    /* CORE_DSP_800_40MHz */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 400U,
        .FracM = 0U,
    },
    /* CORE_DSP_2000_40MHz */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 2000U,
        .FracM = 0U,
    },
    /* CORE_DSP_2000_40MHz */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 1000U,
        .FracM = 0U,
    },
    /* CORE_PER_1728_40MHz */
    {
        .Finp  = 40U,
        .N     = 39U,
        .Fout  = 1728U,
        .M2    = 1U,
        .M     = 1728U,
        .FracM = 0U,
    },
    /* DSP_900_40MHz  */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 900U,
        .M2    = 1U,
        .M     = 450U,
        .FracM = 0U,
    },
    /* DSP_1800_40MHz  */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 900U,
        .FracM = 0U,
    },
    /* PER_1920_40MHz  */
    {
        .Finp  = 40U,
        .N     = 19U,
        .Fout  = 1920U,
        .M2    = 1U,
        .M     = 960U,
        .FracM = 0U,
    },
    /* CORE_DSP_800_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 400U,
        .FracM = 0U,
    },
    /* CORE_DSP_2000_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 1000U,
        .FracM = 0U,
    },
    /* DSP_1800_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 900U,
        .FracM = 0U,
    },
    /* PER_1920_50MHz  */
    {
        .Finp  = 50U,
        .N     = 24U,
        .Fout  = 1920U,
        .M2    = 1U,
        .M     = 960U,
        .FracM = 0U,
    },
    /* CORE_800_49152  */
    {
        .Finp  = 49U,
        .N     = 23U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 390U,
        .FracM = 163840U,
    },
    /* CORE_2000_49152  */
    {
        .Finp  = 49U,
        .N     = 21U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 895U,
        .FracM = 47787U,
    },
    /* DSP_1800_49152  */
    {
        .Finp  = 49U,
        .N     = 20U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 769U,
        .FracM = 11264U,
    },
    /* DSP_1728_49152  */
    {
        .Finp  = 49U,
        .N     = 19U,
        .Fout  = 1728U,
        .M2    = 1U,
        .M     = 703U,
        .FracM = 32768U,
    },
    /* PER_1966p08_49152  */
    {
        .Finp  = 49U,
        .N     = 19U,
        .Fout  = 1966U,
        .M2    = 1U,
        .M     = 800U,
        .FracM = 209715200U,
    },
    /* CORE_800_451584  */
    {
        .Finp  = 45U,
        .N     = 20U,
        .Fout  = 800U,
        .M2    = 1U,
        .M     = 372U,
        .FracM = 6242U,
    },
    /* CORE_2000_451584  */
    {
        .Finp  = 45U,
        .N     = 20U,
        .Fout  = 2000U,
        .M2    = 1U,
        .M     = 930U,
        .FracM = 15604U,
    },
    /* DSP_1800_451584  */
    {
        .Finp  = 45U,
        .N     = 20U,
        .Fout  = 1800U,
        .M2    = 1U,
        .M     = 837U,
        .FracM = 14043U,
    },
    /* DSP_1728_451584  */
    {
        .Finp  = 45U,
        .N     = 18U,
        .Fout  = 1728U,
        .M2    = 1U,
        .M     = 727U,
        .FracM = 10700U,
    },
    /* PER_1806p336_451584  */
    {
        .Finp  = 45U,
        .N     = 18U,
        .Fout  = 1806U,
        .M2    = 1U,
        .M     = 760U,
        .FracM = 0U,
    },
    /* PER_1699_40MHz  */
    {
        .Finp  = 40U,
        .N     = 16U,
        .Fout  = 1699U,
        .M2    = 1U,
        .M     = 722U,
        .FracM = 44032U,
    },
};

static const SOC_RcmXtalInfo gSocRcmXtalInfo[] = {
    [SOC_RcmXtalFreqId_CLK_40MHZ]      = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_40MHZ), .div2flag = 0},
    [SOC_RcmXtalFreqId_CLK_50MHZ]      = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_50MHZ), .div2flag = 0},
    [SOC_RcmXtalFreqId_CLK_49p152MHZ]  = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_49p152MHZ), .div2flag = 0},
    [SOC_RcmXtalFreqId_CLK_45p1584MHZ] = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_45p1584MHZ), .div2flag = 0},
    [SOC_RcmXtalFreqId_CLK_20MHZ]      = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_40MHZ), .div2flag = 1},
    [SOC_RcmXtalFreqId_CLK_25MHZ]      = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_50MHZ), .div2flag = 1},
    [SOC_RcmXtalFreqId_CLK_24p576MHZ]  = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_49p152MHZ), .div2flag = 1},
    [SOC_RcmXtalFreqId_CLK_22p5792MHZ] = {.Finp = SOC_RCM_FREQ_HZ2MHZ(SOC_RCM_XTAL_CLK_50MHZ), .div2flag = 1},
};

static uint32_t SOC_rcmMake8(uint8_t msb, uint8_t lsb, uint8_t val)
{
    uint32_t mask;
    uint8_t  bits;
    uint32_t newVal;

    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    newVal = (uint32_t)val & mask;

    return (newVal << lsb);
}

static uint32_t SOC_rcmMake16(uint8_t msb, uint8_t lsb, uint16_t val)
{
    uint32_t mask;
    uint8_t  bits;
    uint32_t newVal;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    newVal = (uint32_t)val & mask;

    return (newVal << lsb);
}

static uint32_t SOC_rcmMake32(uint8_t msb, uint8_t lsb, uint32_t val)
{
    uint32_t mask;
    uint8_t  bits;
    uint32_t newVal;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    newVal = val & mask;

    return (newVal << lsb);
}

static uint32_t SOC_rcmInsert8(volatile uint32_t reg, uint8_t msb, uint8_t lsb, uint8_t val)
{
    uint32_t mask;
    uint8_t  bits;
    uint32_t value;
    uint32_t tmp;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    value = (mask << lsb);
    tmp   = (reg & ~value);
    return (tmp | SOC_rcmMake8(msb, lsb, val));
}

static uint32_t SOC_rcmInsert16(volatile uint32_t reg, uint8_t msb, uint8_t lsb, uint16_t val)
{
    uint32_t mask;
    uint8_t  bits;
    uint32_t value;
    uint32_t tmp;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    value = (mask << lsb);
    tmp   = (reg & ~value);
    return (tmp | SOC_rcmMake16(msb, lsb, val));
}

static uint32_t SOC_rcmInsert32(volatile uint32_t reg, uint8_t msb, uint8_t lsb, uint32_t val)
{
    uint32_t mask;
    uint8_t  bits;
    uint32_t value;
    uint32_t tmp;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    value = (mask << lsb);
    tmp   = (reg & ~value);
    return (tmp | SOC_rcmMake32(msb, lsb, val));
}

static uint8_t SOC_rcmExtract8(volatile uint32_t reg, uint8_t msb, uint8_t lsb)
{
    uint32_t mask;
    uint8_t  bits;
    uint8_t  value;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    value = (uint8_t)((reg >> lsb) & mask);
    return value;
}

static uint16_t SOC_rcmExtract16(volatile uint32_t reg, uint8_t msb, uint8_t lsb)
{
    uint32_t mask;
    uint8_t  bits;
    uint16_t value;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    value = (uint16_t)((reg >> lsb) & mask);
    return value;
}

static uint32_t SOC_rcmExtract32(volatile uint32_t reg, uint8_t msb, uint8_t lsb)
{
    uint32_t mask;
    uint8_t  bits;
    uint32_t value;

    /* Compute the mask: */
    bits = (msb - lsb + 1U);
    mask = (uint32_t)((uint32_t)1U << bits);
    mask = mask - 1U;

    value = (reg >> lsb) & mask;
    return value;
}

static toprcmBASE_t *SOC_rcmGetBaseAddressTOPRCM(void)
{
    return (toprcmBASE_t *)MCAL_CSL_MSS_TOPRCM_U_BASE;
}

static topCtrlBASE_t *SOC_rcmGetBaseAddressTOPCTRL(void)
{
    return (topCtrlBASE_t *)MCAL_CSL_TOP_CTRL_U_BASE;
}

static inline mssrcmBASE_t *CSL_RCM_getBaseAddress(void)
{
    return (mssrcmBASE_t *)MCAL_CSL_MSS_RCM_U_BASE;
}

static uint8_t SOC_rcmReadXtalFreqScale(const topCtrlBASE_t *ptrTopCtrlRegs)
{
    return (SOC_rcmExtract8(ptrTopCtrlRegs->EFUSE1_ROW_10, SOC_RCM_XTAL_FREQ_SCALE_END_BIT,
                            SOC_RCM_XTAL_FREQ_SCALE_START_BIT));
}

static SOC_RcmXtalFreqId SOC_rcmGetXtalFrequency(void)
{
    toprcmBASE_t     *ptrTopRCMRegs;
    topCtrlBASE_t    *ptrTopCtrlRegs;
    uint32_t          xtalRegVal;
    SOC_RcmXtalFreqId freq;
    uint8_t           xtalFreqScale;

    ptrTopRCMRegs  = SOC_rcmGetBaseAddressTOPRCM();
    ptrTopCtrlRegs = SOC_rcmGetBaseAddressTOPCTRL();

    /* read the register bits corresponding to XTAL Frequency */
    xtalRegVal = SOC_rcmExtract32(ptrTopRCMRegs->ANA_REG_WU_MODE_REG_LOWV, 6U, 5U);
    /* read the register bits corresponding to XTAL Frequency Scale */
    xtalFreqScale = SOC_rcmReadXtalFreqScale(ptrTopCtrlRegs);

    if (xtalFreqScale == 1U)
    {
        if (xtalRegVal == 0U)
        {
            freq = SOC_RcmXtalFreqId_CLK_20MHZ;
        }
        else if (xtalRegVal == 1U)
        {
            freq = SOC_RcmXtalFreqId_CLK_22p5792MHZ;
        }
        else if (xtalRegVal == 2U)
        {
            freq = SOC_RcmXtalFreqId_CLK_24p576MHZ;
        }
        else
        {
            freq = SOC_RcmXtalFreqId_CLK_25MHZ;
        }
    }
    else
    {
        if (xtalRegVal == 0U)
        {
            freq = SOC_RcmXtalFreqId_CLK_40MHZ;
        }
        else if (xtalRegVal == 1U)
        {
            freq = SOC_RcmXtalFreqId_CLK_45p1584MHZ;
        }
        else if (xtalRegVal == 2U)
        {
            freq = SOC_RcmXtalFreqId_CLK_49p152MHZ;
        }
        else
        {
            freq = SOC_RcmXtalFreqId_CLK_50MHZ;
        }
    }

    return (freq);
}

static uint32_t SOC_rcmGetADPLLJFout(uint32_t Finp, uint32_t N, uint32_t M, uint32_t M2, uint32_t FracM,
                                     uint32_t div2flag)
{
    uint32_t i;
    uint32_t FOut;
    uint32_t Nmatch;

    if (div2flag)
    {
        Nmatch = ((N + 1) * 2) - 1;
    }
    else
    {
        Nmatch = N;
    }
    for (i = 0; i < SOC_RCM_UTILS_ARRAYSIZE(gSocRcmADPLLJConfigTbl); i++)
    {
        if ((gSocRcmADPLLJConfigTbl[i].Finp == Finp) && (gSocRcmADPLLJConfigTbl[i].FracM == FracM) &&
            (gSocRcmADPLLJConfigTbl[i].M == M) && (gSocRcmADPLLJConfigTbl[i].M2 == M2) &&
            (gSocRcmADPLLJConfigTbl[i].N == Nmatch))
        {
            break;
        }
    }
    if (i < SOC_RCM_UTILS_ARRAYSIZE(gSocRcmADPLLJConfigTbl))
    {
        FOut = SOC_RCM_FREQ_MHZ2HZ(gSocRcmADPLLJConfigTbl[i].Fout);
    }
    else
    {
        FOut = 0;
    }
    return FOut;
}

static uint32_t SOC_rcmGetCoreFout(uint32_t Finp, uint32_t div2flag)
{
    uint8_t       pllSwitchFlag;
    toprcmBASE_t *ptrTopRCMRegs;
    uint32_t      FOut;

    ptrTopRCMRegs = SOC_rcmGetBaseAddressTOPRCM();
    /* read the Core PLL Lock status */
    pllSwitchFlag = SOC_rcmExtract8(ptrTopRCMRegs->PLL_CORE_STATUS, 10U, 10U);
    if (pllSwitchFlag)
    {
        uint32_t M, N, M2, FracM;

        N     = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_M2NDIV, MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_N);
        M2    = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_M2NDIV, MSS_TOPRCM_PLL_CORE_M2NDIV_PLL_CORE_M2NDIV_M2);
        M     = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_MN2DIV, MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_M);
        FracM = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_FRACDIV, MSS_TOPRCM_PLL_CORE_FRACDIV_PLL_CORE_FRACDIV_FRACTIONALM);
        FOut  = SOC_rcmGetADPLLJFout(Finp, N, M, M2, FracM, div2flag);
    }
    else
    {
        uint32_t ULOWCLKEN =
            CSL_FEXT(ptrTopRCMRegs->PLL_CORE_CLKCTRL, MSS_TOPRCM_PLL_CORE_CLKCTRL_PLL_CORE_CLKCTRL_ULOWCLKEN);
        if (ULOWCLKEN == 0)
        {
            uint32_t N2;

            N2   = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_MN2DIV, MSS_TOPRCM_PLL_CORE_MN2DIV_PLL_CORE_MN2DIV_N2);
            FOut = Finp / (N2 + 1);
        }
        else
        {
            FOut = Finp;
        }
    }
    return FOut;
}

static uint32_t SOC_rcmGetCoreHsDivOut(uint32_t Finp, uint32_t div2flag, SOC_RcmPllHsDivOutId hsDivOut)
{
    uint32_t      FOut;
    uint32_t      clkDiv;
    toprcmBASE_t *ptrTopRCMRegs;

    ptrTopRCMRegs = SOC_rcmGetBaseAddressTOPRCM();
    FOut          = SOC_rcmGetCoreFout(Finp, div2flag);
    switch (hsDivOut)
    {
        case SOC_RcmPllHsDivOutId_0:
        {
            clkDiv = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_HSDIVIDER_CLKOUT0,
                              MSS_TOPRCM_PLL_CORE_HSDIVIDER_CLKOUT0_PLL_CORE_HSDIVIDER_CLKOUT0_DIV);
            break;
        }
        case SOC_RcmPllHsDivOutId_1:
        {
            clkDiv = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_HSDIVIDER_CLKOUT1,
                              MSS_TOPRCM_PLL_CORE_HSDIVIDER_CLKOUT1_PLL_CORE_HSDIVIDER_CLKOUT1_DIV);
            break;
        }
        case SOC_RcmPllHsDivOutId_2:
        {
            clkDiv = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_HSDIVIDER_CLKOUT2,
                              MSS_TOPRCM_PLL_CORE_HSDIVIDER_CLKOUT2_PLL_CORE_HSDIVIDER_CLKOUT2_DIV);
            break;
        }
        case SOC_RcmPllHsDivOutId_3:
        {
            clkDiv = CSL_FEXT(ptrTopRCMRegs->PLL_CORE_HSDIVIDER_CLKOUT3,
                              MSS_TOPRCM_PLL_CORE_HSDIVIDER_CLKOUT3_PLL_CORE_HSDIVIDER_CLKOUT3_DIV);
            break;
        }
        default:
        {
            clkDiv = 0;
            break;
        }
    }
    return (FOut / (clkDiv + 1));
}

static uint32_t SOC_rcmGetModuleClkDivRegVal(uint32_t moduleClkDivVal)
{
    uint32_t moduleClkDivRegVal;

    moduleClkDivRegVal = (moduleClkDivVal & 0xF) | ((moduleClkDivVal & 0xF) << 4) | ((moduleClkDivVal & 0xF) << 8);
    return moduleClkDivRegVal;
}

static uint32_t SOC_rcmGetModuleClkDivVal(uint32_t inFreq, uint32_t outFreq)
{
    uint32_t moduleClkDivVal;

    moduleClkDivVal = inFreq / outFreq;
    moduleClkDivVal--;
    return moduleClkDivVal;
}

void SOC_rcmConfigEthMacIf(void)
{
    mssrcmBASE_t     *ptrMSSRCMRegs;
    uint32_t          clkFreq = 0U;
    SOC_RcmXtalFreqId clkFreqId;
    uint32_t          Finp;
    uint32_t          clkDivisor;
    uint32_t          mii10ClkDivVal;

    clkFreqId = SOC_rcmGetXtalFrequency();
    Finp      = gSocRcmXtalInfo[clkFreqId].Finp;

    ptrMSSRCMRegs = CSL_RCM_getBaseAddress();
    clkFreq       = SOC_rcmGetCoreHsDivOut(Finp, gSocRcmXtalInfo[clkFreqId].div2flag, SOC_RcmPllHsDivOutId_1);
    clkDivisor    = SOC_rcmGetModuleClkDivVal(clkFreq, SOC_RCM_FREQ_MHZ2HZ(50U));
    ptrMSSRCMRegs->MSS_MII100_CLK_DIV_VAL =
        SOC_rcmInsert16(ptrMSSRCMRegs->MSS_MII100_CLK_DIV_VAL, 11U, 0U, SOC_rcmGetModuleClkDivRegVal(clkDivisor));
    clkDivisor     = SOC_rcmGetModuleClkDivVal(clkFreq, SOC_RCM_FREQ_MHZ2HZ(5U));
    mii10ClkDivVal = (clkDivisor & 0xFF) | ((clkDivisor & 0xFF) << 8) | ((clkDivisor & 0xFF) << 16);
    ptrMSSRCMRegs->MSS_MII10_CLK_DIV_VAL =
        SOC_rcmInsert32(ptrMSSRCMRegs->MSS_MII10_CLK_DIV_VAL, 23U, 0U, mii10ClkDivVal);
    clkDivisor = SOC_rcmGetModuleClkDivVal(clkFreq, SOC_RCM_FREQ_MHZ2HZ(50U));
    ptrMSSRCMRegs->MSS_RGMII_CLK_DIV_VAL =
        SOC_rcmInsert16(ptrMSSRCMRegs->MSS_RGMII_CLK_DIV_VAL, 11U, 0U, SOC_rcmGetModuleClkDivRegVal(clkDivisor));
}

void AppUtils_logTestResult(uint32 testResult)
{
    /*  AppUtils_printf("Test Result Status: %d\n\r", testResult); */ /* unused-parameter */
}

#ifdef __cplusplus
extern "C" {
#endif

void sys_cDabort(uint32 abortLR, uint32 abortSpsr, uint32 abortSp)
{
    volatile uint32 loopCnt = 1U;
    while (loopCnt != 0U)
    {
        ;
    }
}

void sys_cPabort(uint32 abortLR, uint32 abortSpsr, uint32 abortSp)
{
    volatile uint32 loopCnt = 1U;
    while (loopCnt != 0U)
    {
        ;
    }
}

void sys_cUabort(uint32 abortLR, uint32 abortSpsr, uint32 abortSp)
{
    volatile uint32 loopCnt = 1U;
    while (loopCnt != 0U)
    {
        ;
    }
}

#ifdef __cplusplus
}
#endif

void sys_cSwiInt(uint8 svcNum)
{
    /*
     * Service all software requests
     */
    switch (svcNum)
    {
        case SVC_TEST_SWI:
        {
            /*
             * For testing SWI interrupt, remove later - DKS
             */
            break;
        }
        /*
         * ARM mode switch is supported with SVC num 0 in asm sys_swiEntry function by bypassing
         * call to this C function
         */
        case SVC_SWITCH_ARM_MODE:
        /* Default handler */
        default:
        {
            // M_ASSERT(M_ZERO);
            break;
        }
    }
}

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
typedef struct
{
    uint32                    numEntries;
    const Port_PinConfigType *pinConfig;
} AppUtilsPinMux_ModuleEnablePortSettingType;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

Std_ReturnType AppUtilsPort_RefreshPortDrirection(void)
{
    Std_ReturnType retVal = E_OK;

#if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API)
    Port_RefreshPortDirection();
#endif /*#if (STD_ON == PORT_REFRESH_PORT_DIRECTION_API)*/

    return retVal;
}
