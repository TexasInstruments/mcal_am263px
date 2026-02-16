/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to
 * make, have made, use, import, offer to sell and sell ("Utilize") this software
 * subject to the terms herein. With respect to the foregoing patent license,
 * such license is granted solely to the extent that any such patent is necessary
 * to Utilize the software alone. The patent license shall not apply to any
 * combinations which include this software, other than combinations with devices
 * manufactured by or for TI ("TI Devices"). No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution.
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 * Any redistribution and use are licensed by TI for use only with TI Devices.
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 * Any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 * Any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S
 * LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file     Mcal_Lib_MemMap.h
 *
 *  \brief    This file contains memory map section definition for Mcal Lib
 *
 */


#ifdef __cplusplus
extern "C"
{
#endif

#define MEMMAP_ERROR

#if defined(MCAL_LIB_START_SEC_VAR_INIT_UNSPECIFIED)
#undef MCAL_LIB_START_SEC_VAR_INIT_UNSPECIFIED
#define START_SEC_COMMON_VAR_INIT_UNSPECIFIED

#elif defined(MCAL_LIB_START_SEC_VAR_INIT_32)
#undef MCAL_LIB_START_SEC_VAR_INIT_32
#define START_SEC_COMMON_VAR_INIT_32

#elif defined(MCAL_LIB_START_SEC_VAR_INIT_16)
#undef MCAL_LIB_START_SEC_VAR_INIT_16
#define START_SEC_COMMON_VAR_INIT_16

#elif defined(MCAL_LIB_START_SEC_VAR_INIT_8)
#undef MCAL_LIB_START_SEC_VAR_INIT_8
#define START_SEC_COMMON_VAR_INIT_8

#elif defined(MCAL_LIB_START_SEC_VAR_NO_INIT_UNSPECIFIED)
#undef MCAL_LIB_START_SEC_VAR_NO_INIT_UNSPECIFIED
#define START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED

#elif defined(MCAL_LIB_START_SEC_VAR_NO_INIT_32)
#undef MCAL_LIB_START_SEC_VAR_NO_INIT_32
#define START_SEC_COMMON_VAR_NO_INIT_32

#elif defined(MCAL_LIB_START_SEC_VAR_NO_INIT_16)
#undef MCAL_LIB_START_SEC_VAR_NO_INIT_16
#define START_SEC_COMMON_VAR_NO_INIT_16

#elif defined(MCAL_LIB_START_SEC_VAR_NO_INIT_8)
#undef MCAL_LIB_START_SEC_VAR_NO_INIT_8
#define START_SEC_COMMON_VAR_NO_INIT_8

#elif defined(MCAL_LIB_START_SEC_CONST_UNSPECIFIED)
#undef MCAL_LIB_START_SEC_CONST_UNSPECIFIED
#define START_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(MCAL_LIB_START_SEC_CONST_32)
#undef MCAL_LIB_START_SEC_CONST_32
#define START_SEC_COMMON_CONST_32
#elif defined(MCAL_LIB_START_SEC_CONST_16)
#undef MCAL_LIB_START_SEC_CONST_16
#define START_SEC_COMMON_CONST_16
#elif defined(MCAL_LIB_START_SEC_CONST_8)
#undef MCAL_LIB_START_SEC_CONST_8
#define START_SEC_COMMON_CONST_8
#elif defined(MCAL_LIB_START_SEC_CONFIG_DATA)
#undef MCAL_LIB_START_SEC_CONFIG_DATA
#define START_SEC_COMMON_CONFIG_DATA
#elif defined(MCAL_LIB_START_SEC_CODE)
#undef MCAL_LIB_START_SEC_CODE
#define START_SEC_COMMON_CODE
#elif defined(MCAL_LIB_START_SEC_ISR_CODE)
#undef MCAL_LIB_START_SEC_ISR_CODE
#define START_SEC_COMMON_ISR_CODE

#elif defined(MCAL_LIB_START_SEC_CALLOUT_CODE)
#undef MCAL_LIB_START_SEC_CALLOUT_CODE
#define START_SEC_COMMON_CALLOUT_CODE

#endif

#if defined(MCAL_LIB_STOP_SEC_VAR_INIT_UNSPECIFIED)
#undef MCAL_LIB_STOP_SEC_VAR_INIT_UNSPECIFIED
#define STOP_SEC_COMMON_VAR_INIT_UNSPECIFIED

#elif defined(MCAL_LIB_STOP_SEC_VAR_INIT_32)
#undef MCAL_LIB_STOP_SEC_VAR_INIT_32
#define STOP_SEC_COMMON_VAR_INIT_32

#elif defined(MCAL_LIB_STOP_SEC_VAR_INIT_16)
#undef MCAL_LIB_STOP_SEC_VAR_INIT_16
#define STOP_SEC_COMMON_VAR_INIT_16

#elif defined(MCAL_LIB_STOP_SEC_VAR_INIT_8)
#undef MCAL_LIB_STOP_SEC_VAR_INIT_8
#define STOP_SEC_COMMON_VAR_INIT_8

#elif defined(MCAL_LIB_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
#undef MCAL_LIB_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#define STOP_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED

#elif defined(MCAL_LIB_STOP_SEC_VAR_NO_INIT_32)
#undef MCAL_LIB_STOP_SEC_VAR_NO_INIT_32
#define STOP_SEC_COMMON_VAR_NO_INIT_32

#elif defined(MCAL_LIB_STOP_SEC_VAR_NO_INIT_16)
#undef MCAL_LIB_STOP_SEC_VAR_NO_INIT_16
#define STOP_SEC_COMMON_VAR_NO_INIT_16

#elif defined(MCAL_LIB_STOP_SEC_VAR_NO_INIT_8)
#undef MCAL_LIB_STOP_SEC_VAR_NO_INIT_8
#define STOP_SEC_COMMON_VAR_NO_INIT_8

#elif defined(MCAL_LIB_STOP_SEC_CONST_UNSPECIFIED)
#undef MCAL_LIB_STOP_SEC_CONST_UNSPECIFIED
#define STOP_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(MCAL_LIB_STOP_SEC_CONST_32)
#undef MCAL_LIB_STOP_SEC_CONST_32
#define STOP_SEC_COMMON_CONST_32
#elif defined(MCAL_LIB_STOP_SEC_CONST_16)
#undef MCAL_LIB_STOP_SEC_CONST_16
#define STOP_SEC_COMMON_CONST_16
#elif defined(MCAL_LIB_STOP_SEC_CONST_8)
#undef MCAL_LIB_STOP_SEC_CONST_8
#define STOP_SEC_COMMON_CONST_8
#elif defined(MCAL_LIB_STOP_SEC_CONFIG_DATA)
#undef MCAL_LIB_STOP_SEC_CONFIG_DATA
#define STOP_SEC_COMMON_CONFIG_DATA
#elif defined(MCAL_LIB_STOP_SEC_CODE)
#undef MCAL_LIB_STOP_SEC_CODE
#define STOP_SEC_COMMON_CODE
#elif defined(MCAL_LIB_STOP_SEC_ISR_CODE)
#undef MCAL_LIB_STOP_SEC_ISR_CODE
#define STOP_SEC_COMMON_ISR_CODE

#elif defined(MCAL_LIB_STOP_SEC_CALLOUT_CODE)
#undef MCAL_LIB_STOP_SEC_CALLOUT_CODE
#define STOP_SEC_COMMON_CALLOUT_CODE

#endif

#if defined(START_SEC_COMMON_VAR_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data.MCAL_LIB_DATA_INIT_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_INIT_UNSPECIFIED_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_UNSPECIFIED)
#elif defined(START_SEC_COMMON_VAR_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data.MCAL_LIB_DATA_INIT_32_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_INIT_32_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_32
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_32)

#elif defined(START_SEC_COMMON_VAR_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data.MCAL_LIB_DATA_INIT_16_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_INIT_16_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_16
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_16)

#elif defined(START_SEC_COMMON_VAR_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data.MCAL_LIB_DATA_INIT_8_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_INIT_8_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_8
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_8)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss.MCAL_LIB_DATA_NO_INIT_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_NO_INIT_UNSPECIFIED_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_UNSPECIFIED)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss.MCAL_LIB_DATA_NO_INIT_32_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_NO_INIT_32_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_32
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_32)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss.MCAL_LIB_DATA_NO_INIT_16_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_NO_INIT_16_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_16
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_16)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss.MCAL_LIB_DATA_NO_INIT_8_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_DATA_NO_INIT_8_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_8
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_8)

#elif defined(START_SEC_COMMON_CONST_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata.MCAL_LIB_CONST_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_CONST_UNSPECIFIED_SECTION")
#endif
#undef START_SEC_COMMON_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_UNSPECIFIED)

#elif defined(START_SEC_COMMON_CONST_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata.MCAL_LIB_CONST_32_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_CONST_32_SECTION")
#endif
#undef START_SEC_COMMON_CONST_32
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_32)

#elif defined(START_SEC_COMMON_CONST_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata.MCAL_LIB_CONST_16_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_CONST_16_SECTION")
#endif
#undef START_SEC_COMMON_CONST_16
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_16)

#elif defined(START_SEC_COMMON_CONST_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata.MCAL_LIB_CONST_8_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_CONST_8_SECTION")
#endif
#undef START_SEC_COMMON_CONST_8
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_8)

#elif defined(START_SEC_COMMON_CONFIG_DATA)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata.MCAL_LIB_CONFIG_SECTION"
#else
#pragma SET_DATA_SECTION("MCAL_LIB_CONFIG_SECTION")
#endif
#undef START_SEC_COMMON_CONFIG_DATA
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONFIG_DATA)

#elif defined(START_SEC_COMMON_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text.MCAL_LIB_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("MCAL_LIB_TEXT_SECTION")
#endif
#undef START_SEC_COMMON_CODE
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE)

#elif defined(START_SEC_COMMON_ISR_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text.MCAL_LIB_ISR_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("MCAL_LIB_ISR_TEXT_SECTION")
#endif
#undef START_SEC_COMMON_ISR_CODE
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE_ISR)

#elif defined(START_SEC_COMMON_CALLOUT_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text.MCAL_LIB_CALLOUT_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("MCAL_LIB_CALLOUT_TEXT_SECTION")
#endif
#undef START_SEC_COMMON_CALLOUT_CODE
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE_CALLOUT)

#endif

#if defined(STOP_SEC_COMMON_VAR_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_UNSPECIFIED))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_INIT_32
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_32))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_INIT_16
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_16))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_INIT_8
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_8))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_UNSPECIFIED))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_NO_INIT_32
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_32))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_NO_INIT_16
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_16))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section bss=".bss"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_VAR_NO_INIT_8
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_8))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_UNSPECIFIED))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_CONST_32
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_32))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_CONST_16
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_16))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_CONST_8
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_8))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONFIG_DATA)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_CONFIG_DATA
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONFIG_DATA))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text"
#else
#pragma SET_CODE_SECTION()
#endif
#undef STOP_SEC_COMMON_CODE
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_CODE_SECTION) || \
    (MEMMAP_ACTIVE_CODE_SECTION != CODE))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_CODE_SECTION

#elif defined(STOP_SEC_COMMON_ISR_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text"
#else
#pragma SET_CODE_SECTION()
#endif
#undef STOP_SEC_COMMON_ISR_CODE
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_CODE_SECTION) || \
    (MEMMAP_ACTIVE_CODE_SECTION != CODE_ISR))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_CODE_SECTION

#elif defined(STOP_SEC_COMMON_CALLOUT_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text"
#else
#pragma SET_CODE_SECTION()
#endif
#undef STOP_SEC_COMMON_CALLOUT_CODE
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_CODE_SECTION) || \
    (MEMMAP_ACTIVE_CODE_SECTION != CODE_CALLOUT))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_CODE_SECTION

#endif

#ifdef MEMMAP_ERROR
#error "MCAL_LIB_Memmap.h pragma error"
#endif

#ifdef __cplusplus
}
#endif


