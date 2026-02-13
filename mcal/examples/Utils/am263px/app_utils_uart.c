/* ======================================================================
 *   Copyright (C) 2023 Texas Instruments Incorporated
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
 *  \file     app_utils_uart.c
 *
 *  \brief    This file contains common utility functions used for logger
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdio.h"
#include "stdarg.h"
#include "stdlib.h"

#include "hw_ctrl_core.h"
#include "soc.h"
#include "reg_sci.h"
#include "sci.h"
#include "app_utils.h"

#define UART_BUFF_SIZE 512
static uint8 logUartBuff[UART_BUFF_SIZE];

void Enable_Uart(void)
{
    uint32 div = 0U;
    /*Enable the SCI */
    sciAInit();
    div = 25;
    sciSetBaudrateValue(sciAREG, div);
}

//*****************************************************************************
//
//!    Outputs a character string to the console
//!
//! \param str is the pointer to the string to be printed
//!
//! This function
//!        1. prints the input string character by character on to the console.
//!
//! \return none
//
//*****************************************************************************
void message(sciBASE_t *sci, const uint8 *str)
{
    uint32       dataLen = 0U;
    const uint8 *strLcl  = str;
    if (str != NULL_PTR)
    {
        while (*strLcl != '\0')
        {
            dataLen++;
            strLcl++;
        }
        sciDisableNotification(sci, SCI_TX_INT);
        sciSend(sci, dataLen, (uint8 *)str);
    }
}

void getCharacter(sciBASE_t *sci, uint8 *str, uint8 len)
{
    sciReceive(sci, len, str);
}

/**
 *  A simple UART based printf function supporting \%c, \%d, \%p, \%s, \%u,
 *  \%x, and \%X.
 *
 *  \param pcString is the format string.
 *  \param ... are the optional arguments, which depend on the contents of the
 *  format string.
 *
 *  This function is very similar to the C library <tt>fprintf()</tt> function.
 *  All of its output will be sent to the UART.  Only the following formatting
 *  characters are supported:
 *
 *  - \%c to print a character
 *  - \%d to print a decimal value
 *  - \%s to print a string
 *  - \%u to print an unsigned decimal value
 *  - \%x to print a hexadecimal value using lower case letters
 *  - \%X to print a hexadecimal value using lower case letters (not upper case
 *  letters as would typically be used)
 *  - \%p to print a pointer as a hexadecimal value
 *  - \%\% to print out a \% character
 *
 *  For \%s, \%d, \%u, \%p, \%x, and \%X, an optional number may reside
 *  between the \% and the format character, which specifies the minimum number
 *  of characters to use for that value; if preceded by a 0 then the extra
 *  characters will be filled with zeros instead of spaces.  For example,
 *  ``\%8d'' will use eight characters to print the decimal value with spaces
 *  added to reach eight; ``\%08d'' will use eight characters as well but will
 *  add zeroes instead of spaces.
 *
 *  The type of the arguments after \e pcString must match the requirements of
 *  the format string.  For example, if an integer was passed where a string
 *  was expected, an error of some kind will most likely occur.
 *
 *  \return None.
 */
void UARTPrintf(const char *pcFormat, ...)
{
    uint8  *pcTemp = (uint8 *)NULL_PTR;
    va_list list;

    sint32 iRet = 0;

    pcTemp = &logUartBuff[0U];

    while (TRUE)
    {
        va_start(list, pcFormat);
        iRet = vsnprintf((char *)pcTemp, UART_BUFF_SIZE, (const char *)pcFormat, list);
        va_end(list);
        if ((iRet > -1) && (iRet < UART_BUFF_SIZE))
        {
            break;
        }
        else
        {
            printf("Msg length is exceeded %d", UART_BUFF_SIZE);
        }
    }
    *(pcTemp + iRet) = '\0';
    message(sciAREG, pcTemp);

    return;
}
