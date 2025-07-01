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
 *  \file     Cdd_FsiRx_MemMap.h
 *
 *  \brief    This file contains memory map section definition
 *
 */


#ifdef __cplusplus
extern "C"
{
#endif

//#define MEMMAP_ERROR

/* CDD */
#if defined(CDD_FSIRX_START_SEC_VAR_INIT_UNSPECIFIED)
#undef CDD_FSIRX_START_SEC_VAR_INIT_UNSPECIFIED
#define START_SEC_COMMON_VAR_INIT_UNSPECIFIED

#elif defined(CDD_FSIRX_START_SEC_VAR_INIT_32)
#undef CDD_FSIRX_START_SEC_VAR_INIT_32
#define START_SEC_COMMON_VAR_INIT_32

#elif defined(CDD_FSIRX_START_SEC_VAR_INIT_16)
#undef CDD_FSIRX_START_SEC_VAR_INIT_16
#define START_SEC_COMMON_VAR_INIT_16

#elif defined(CDD_FSIRX_START_SEC_VAR_INIT_8)
#undef CDD_FSIRX_START_SEC_VAR_INIT_8
#define START_SEC_COMMON_VAR_INIT_8

#elif defined(CDD_FSIRX_START_SEC_VAR_NO_INIT_UNSPECIFIED)
#undef CDD_FSIRX_START_SEC_VAR_NO_INIT_UNSPECIFIED
#define START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED

#elif defined(CDD_FSIRX_START_SEC_VAR_NO_INIT_32)
#undef CDD_FSIRX_START_SEC_VAR_NO_INIT_32
#define START_SEC_COMMON_VAR_NO_INIT_32

#elif defined(CDD_FSIRX_START_SEC_VAR_NO_INIT_16)
#undef CDD_FSIRX_START_SEC_VAR_NO_INIT_16
#define START_SEC_COMMON_VAR_NO_INIT_16

#elif defined(CDD_FSIRX_START_SEC_VAR_NO_INIT_8)
#undef CDD_FSIRX_START_SEC_VAR_NO_INIT_8
#define START_SEC_COMMON_VAR_NO_INIT_8

#elif defined(CDD_FSIRX_START_SEC_CONST_UNSPECIFIED)
#undef CDD_FSIRX_START_SEC_CONST_UNSPECIFIED
#define START_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(CDD_FSIRX_START_SEC_CONST_32)
#undef CDD_FSIRX_START_SEC_CONST_32
#define START_SEC_COMMON_CONST_32
#elif defined(CDD_FSIRX_START_SEC_CONST_16)
#undef CDD_FSIRX_START_SEC_CONST_16
#define START_SEC_COMMON_CONST_16
#elif defined(CDD_FSIRX_START_SEC_CONST_8)
#undef CDD_FSIRX_START_SEC_CONST_8
#define START_SEC_COMMON_CONST_8
#elif defined(CDD_FSIRX_START_SEC_CONFIG_DATA)
#undef CDD_FSIRX_START_SEC_CONFIG_DATA
#define START_SEC_COMMON_CONFIG_DATA
#elif defined(CDD_FSIRX_START_SEC_CODE)
#undef CDD_FSIRX_START_SEC_CODE
#define START_SEC_COMMON_CODE
#elif defined(CDD_FSIRX_START_SEC_ISR_CODE)
#undef CDD_FSIRX_START_SEC_ISR_CODE
#define START_SEC_COMMON_ISR_CODE

#elif defined(CDD_FSIRX_START_SEC_CALLOUT_CODE)
#undef CDD_FSIRX_START_SEC_CALLOUT_CODE
#define START_SEC_COMMON_CALLOUT_CODE

#endif

#if defined(CDD_FSIRX_STOP_SEC_VAR_INIT_UNSPECIFIED)
#undef CDD_FSIRX_STOP_SEC_VAR_INIT_UNSPECIFIED
#define STOP_SEC_COMMON_VAR_INIT_UNSPECIFIED

#elif defined(CDD_FSIRX_STOP_SEC_VAR_INIT_32)
#undef CDD_FSIRX_STOP_SEC_VAR_INIT_32
#define STOP_SEC_COMMON_VAR_INIT_32

#elif defined(CDD_FSIRX_STOP_SEC_VAR_INIT_16)
#undef CDD_FSIRX_STOP_SEC_VAR_INIT_16
#define STOP_SEC_COMMON_VAR_INIT_16

#elif defined(CDD_FSIRX_STOP_SEC_VAR_INIT_8)
#undef CDD_FSIRX_STOP_SEC_VAR_INIT_8
#define STOP_SEC_COMMON_VAR_INIT_8

#elif defined(CDD_FSIRX_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
#undef CDD_FSIRX_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#define STOP_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED

#elif defined(CDD_FSIRX_STOP_SEC_VAR_NO_INIT_32)
#undef CDD_FSIRX_STOP_SEC_VAR_NO_INIT_32
#define STOP_SEC_COMMON_VAR_NO_INIT_32

#elif defined(CDD_FSIRX_STOP_SEC_VAR_NO_INIT_16)
#undef CDD_FSIRX_STOP_SEC_VAR_NO_INIT_16
#define STOP_SEC_COMMON_VAR_NO_INIT_16

#elif defined(CDD_FSIRX_STOP_SEC_VAR_NO_INIT_8)
#undef CDD_FSIRX_STOP_SEC_VAR_NO_INIT_8
#define STOP_SEC_COMMON_VAR_NO_INIT_8

#elif defined(CDD_FSIRX_STOP_SEC_CONST_UNSPECIFIED)
#undef CDD_FSIRX_STOP_SEC_CONST_UNSPECIFIED
#define STOP_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(CDD_FSIRX_STOP_SEC_CONST_32)
#undef CDD_FSIRX_STOP_SEC_CONST_32
#define STOP_SEC_COMMON_CONST_32
#elif defined(CDD_FSIRX_STOP_SEC_CONST_16)
#undef CDD_FSIRX_STOP_SEC_CONST_16
#define STOP_SEC_COMMON_CONST_16
#elif defined(CDD_FSIRX_STOP_SEC_CONST_8)
#undef CDD_FSIRX_STOP_SEC_CONST_8
#define STOP_SEC_COMMON_CONST_8
#elif defined(CDD_FSIRX_STOP_SEC_CONFIG_DATA)
#undef CDD_FSIRX_STOP_SEC_CONFIG_DATA
#define STOP_SEC_COMMON_CONFIG_DATA
#elif defined(CDD_FSIRX_STOP_SEC_CODE)
#undef CDD_FSIRX_STOP_SEC_CODE
#define STOP_SEC_COMMON_CODE
#elif defined(CDD_FSIRX_STOP_SEC_ISR_CODE)
#undef CDD_FSIRX_STOP_SEC_ISR_CODE
#define STOP_SEC_COMMON_ISR_CODE

#elif defined(CDD_FSIRX_STOP_SEC_CALLOUT_CODE)
#undef CDD_FSIRX_STOP_SEC_CALLOUT_CODE
#define STOP_SEC_COMMON_CALLOUT_CODE

#endif

#if defined(START_SEC_COMMON_VAR_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_INIT_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_INIT_UNSPECIFIED_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_UNSPECIFIED)
#elif defined(START_SEC_COMMON_VAR_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_INIT_32_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_INIT_32_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_32
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_32)

#elif defined(START_SEC_COMMON_VAR_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_INIT_16_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_INIT_16_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_16
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_16)

#elif defined(START_SEC_COMMON_VAR_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_INIT_8_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_INIT_8_SECTION")
#endif
#undef START_SEC_COMMON_VAR_INIT_8
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_8)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_NO_INIT_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_NO_INIT_UNSPECIFIED_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_UNSPECIFIED)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_NO_INIT_32_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_NO_INIT_32_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_32
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_32)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_NO_INIT_16_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_NO_INIT_16_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_16
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_16)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_DATA_NO_INIT_8_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_DATA_NO_INIT_8_SECTION")
#endif
#undef START_SEC_COMMON_VAR_NO_INIT_8
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_8)

#elif defined(START_SEC_COMMON_CONST_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_CONST_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_CONST_UNSPECIFIED_SECTION")
#endif
#undef START_SEC_COMMON_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_UNSPECIFIED)

#elif defined(START_SEC_COMMON_CONST_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_CONST_32_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_CONST_32_SECTION")
#endif
#undef START_SEC_COMMON_CONST_32
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_32)

#elif defined(START_SEC_COMMON_CONST_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_CONST_16_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_CONST_16_SECTION")
#endif
#undef START_SEC_COMMON_CONST_16
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_16)

#elif defined(START_SEC_COMMON_CONST_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_CONST_8_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_CONST_8_SECTION")
#endif
#undef START_SEC_COMMON_CONST_8
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_8)

#elif defined(START_SEC_COMMON_CONFIG_DATA)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CDD_FSIRX_CONFIG_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FSIRX_CONFIG_SECTION")
#endif
#undef START_SEC_COMMON_CONFIG_DATA
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONFIG_DATA)

#elif defined(START_SEC_COMMON_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text.CDD_FSIRX_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("CDD_FSIRX_TEXT_SECTION")
#endif
#undef START_SEC_COMMON_CODE
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE)

#elif defined(START_SEC_COMMON_ISR_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text.CDD_FSIRX_ISR_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("CDD_FSIRX_ISR_TEXT_SECTION")
#endif
#undef START_SEC_COMMON_ISR_CODE
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE_ISR)

#elif defined(START_SEC_COMMON_CALLOUT_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text:CDD_FSIRX_CALLOUT_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("CDD_FSIRX_CALLOUT_TEXT_SECTION")
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
#pragma clang section data=".data"
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
    #error "Cdd_FsiRx_Memmap.h pragma error"
#endif

#ifdef __cplusplus
}
#endif


