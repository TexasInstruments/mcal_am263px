/* ======================================================================
 *   Copyright (c) 2025 Texas Instruments Incorporated
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
 *  \file     Cdd_Flc_MemMap.h
 *
 *  \brief    This file contains memory map section definition
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif

#define MEMMAP_ERROR

/* Start sections */
#if defined(CDD_FLC_START_SEC_CONST_UNSPECIFIED)
#undef CDD_FLC_START_SEC_CONST_UNSPECIFIED
#define START_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(CDD_FLC_START_SEC_CODE)
#undef CDD_FLC_START_SEC_CODE
#define START_SEC_COMMON_CODE
#endif

/* Stop sections */
#if defined(CDD_FLC_STOP_SEC_CONST_UNSPECIFIED)
#undef CDD_FLC_STOP_SEC_CONST_UNSPECIFIED
#define STOP_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(CDD_FLC_STOP_SEC_CODE)
#undef CDD_FLC_STOP_SEC_CODE
#define STOP_SEC_COMMON_CODE
#endif

/* Start sections - mapping */
#if defined(START_SEC_COMMON_CONST_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata.CDD_FLC_CONST_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("CDD_FLC_CONST_UNSPECIFIED_SECTION")
#endif
#undef START_SEC_COMMON_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CONST_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CONST_SECTION (CONST_UNSPECIFIED)
#elif defined(START_SEC_COMMON_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text.CDD_FLC_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("CDD_FLC_TEXT_SECTION")
#endif
#undef START_SEC_COMMON_CODE
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE)
#endif

/* Stop sections - mapping */
#if defined(STOP_SEC_COMMON_CONST_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section rodata=".rodata"
#else
#pragma SET_DATA_SECTION()
#endif
#undef STOP_SEC_COMMON_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_CONST_SECTION) || \
    (MEMMAP_ACTIVE_CONST_SECTION != CONST_UNSPECIFIED))
#error "STOP keyword not matching start"
#endif
#undef MEMMAP_ACTIVE_CONST_SECTION
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
#endif

#ifdef MEMMAP_ERROR
#error "Cdd_Flc_MemMap.h pragma error"
#endif

#ifdef __cplusplus
}
#endif
