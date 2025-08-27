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

#include "hw_ctrl_core.h"
#include "hal_stdtypes.h"
#include "soc.h"

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
extern uint32 __linker_can_text_start, __linker_can_text_end, __linker_can_const_start, __linker_can_const_end,
    __linker_can_init_start, __linker_can_init_end, __linker_can_no_init_start, __linker_can_no_init_end;
extern uint32 __linker_cdd_cmpss_text_start, __linker_cdd_cmpss_text_end, __linker_cdd_cmpss_const_start,
    __linker_cdd_cmpss_const_end;
extern uint32 __linker_cdd_flc_text_start, __linker_cdd_flc_text_end, __linker_cdd_flc_const_start,
    __linker_cdd_flc_const_end;
extern uint32 __linker_eth_text_start, __linker_eth_text_end, __linker_eth_const_start, __linker_eth_const_end,
    __linker_eth_init_start, __linker_eth_init_end, __linker_eth_no_init_start, __linker_eth_no_init_end;
extern uint32 __linker_ethtrcv_text_start, __linker_ethtrcv_text_end, __linker_ethtrcv_const_start,
    __linker_ethtrcv_const_end, __linker_ethtrcv_init_start, __linker_ethtrcv_init_end, __linker_ethtrcv_no_init_start,
    __linker_ethtrcv_no_init_end;
extern uint32 __linker_fls_text_start, __linker_fls_text_end, __linker_fls_const_start, __linker_fls_const_end,
    __linker_fls_init_start, __linker_fls_init_end, __linker_fls_no_init_start, __linker_fls_no_init_end;
extern uint32 __linker_fsirx_text_start, __linker_fsirx_text_end, __linker_fsirx_const_start, __linker_fsirx_const_end,
    __linker_fsirx_init_start, __linker_fsirx_init_end, __linker_fsirx_no_init_start, __linker_fsirx_no_init_end;
extern uint32 __linker_fsitx_text_start, __linker_fsitx_text_end, __linker_fsitx_const_start, __linker_fsitx_const_end,
    __linker_fsitx_init_start, __linker_fsitx_init_end, __linker_fsitx_no_init_start, __linker_fsitx_no_init_end;

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
    ((uint32)&__linker_can_text_start),
    ((uint32)&__linker_can_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_can_const_start),
    ((uint32)&__linker_can_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_can_init_start),
    ((uint32)&__linker_can_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_can_no_init_start),
    ((uint32)&__linker_can_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_cmpss_text_start),
    ((uint32)&__linker_cdd_cmpss_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_cmpss_const_start),
    ((uint32)&__linker_cdd_cmpss_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_flc_text_start),
    ((uint32)&__linker_cdd_flc_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_cdd_flc_const_start),
    ((uint32)&__linker_cdd_flc_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
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
    ((uint32)&__linker_fsirx_text_start),
    ((uint32)&__linker_fsirx_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fsirx_const_start),
    ((uint32)&__linker_fsirx_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fsirx_init_start),
    ((uint32)&__linker_fsirx_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fsirx_no_init_start),
    ((uint32)&__linker_fsirx_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fsitx_text_start),
    ((uint32)&__linker_fsitx_text_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fsitx_const_start),
    ((uint32)&__linker_fsitx_const_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fsitx_init_start),
    ((uint32)&__linker_fsitx_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
    ((uint32)&__linker_fsitx_no_init_start),
    ((uint32)&__linker_fsitx_no_init_end) - APP_UTILS_LINKER_FILL_LENGTH,
};

#define APP_UTILS_NUM_SEC_HOLES (sizeof(gAppUtilsSecHoleAddrList) / sizeof(gAppUtilsSecHoleAddrList[0]))

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APPUTILS_UART_INPUT (STD_ON)

/** brief Overflow count value for 32bit counter */
#define APPUTILS_COUNTER_MAX_COUNT (0xFFFFFFFFU)

#define pinMuxBase ((uint32 *)0x53100000U)

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
    uint8 *p = s;
    while (len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

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

void stop_timer(void)
{
    HW_WR_REG32(0x52180000, 0x00000000);  // GCTRL Stop Timer
}

void start_timer(void)
{
    /* Enables RTI0 timer*/
    HW_WR_REG32(0x52180000, 0x00000000);  // GCTRL
    HW_WR_REG32(0x52180008, 0x00000000);  // Capture Control
    HW_WR_REG32(0x5218000C, 0x00000000);  // COMP CTRL
    HW_WR_REG32(0x52180010, 0x00000000);  // FRC0
    HW_WR_REG32(0x52180014, 0x00000000);  // UP Counter
    HW_WR_REG32(0x52180018, 0x000000C7);  // Compare Up Counter
    HW_WR_REG32(0x52180084, 0x00070F0F);  // Clear Interrupt
    HW_WR_REG32(0x52180000, 0x00000001);  // GCTRL Start Timer
}

void AppUtils_TimerInit()
{
    start_timer();
}

void AppUtils_TimerDeinit()
{
    stop_timer();
}

uint32 Get_Ticks(void)
{
    frc_ticks = HW_RD_REG32(0x52180010);
    return (uint32)(frc_ticks);
}

void Det_Timeout(bool time_status)
{
    TIMEOUT_CODE_COVERAGE = time_status;
}

static uint32 AppUtils_checkSectionCorruption(uint32 secStartAddr)
{
    uint32  retVal      = E_OK, num;
    uint32 *secStartPtr = ((uint32 *)secStartAddr);
    uint32  fillPattern = APP_UTILS_LINKER_FILL_PATTERN;
    uint32  fillLength  = APP_UTILS_LINKER_FILL_LENGTH;

    num = 0U;
    while (num < fillLength)
    {
        if (*secStartPtr != fillPattern)
        {
            retVal = E_NOT_OK;
            break;
        }
        secStartPtr++;
        num += sizeof(uint32);
    }

    num = *secStartPtr;
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

    status = GetCounterValue(APP_UTILS_CFG_COUNTER_ID, &timerCount);
    if (E_OK == status)
    {
        curTimeMsec = (uint32)(((float32)timerCount * 1000.0) / APP_UTILS_CFG_COUNTER_FREQ);
    }

    return (curTimeMsec);
}

uint32 AppUtils_getElapsedTimeInMsec(uint32 startTime)
{
    uint32     elapsedTimeMsec = 0U;
    uint32     startCount = 0U, tempCount = 0U, elapsedCount = 0U;
    StatusType status;

    startCount = (uint32)(((float32)startTime * APP_UTILS_CFG_COUNTER_FREQ) / 1000.0);

    /* Below API can change start time, so use temp variable */
    tempCount = startCount;
    status    = GetElapsedValue(APP_UTILS_CFG_COUNTER_ID, &tempCount, &elapsedCount);
    if (E_OK == status)
    {
        elapsedTimeMsec = (uint32)(((float32)elapsedCount * 1000.0) / APP_UTILS_CFG_COUNTER_FREQ);
    }

    return (elapsedTimeMsec);
}

void AppUtils_delay(uint32 msec)
{
    uint32 start = HW_RD_REG32(0x52180010);
    while ((msec * 1000) > (HW_RD_REG32(0x52180010) - start))
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
}

void AppUtils_defaultInitDiab(void)
{
    Apps_switch_to_system_mode();

    Enable_Uart();

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

void AppUtils_logTestResult(uint32 testResult)
{
}

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
