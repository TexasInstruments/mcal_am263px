/* ======================================================================
 *   Copyright (c) 2022 Texas Instruments Incorporated
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
 *  \file     Can_MemMap.h
 *
 *  \brief    This file contains memory map section definition
 *
 */


#ifdef __cplusplus
extern "C"
{
#endif

#define MEMMAP_ERROR

/* CAN */
#if defined(CAN_START_SEC_VAR_INIT_UNSPECIFIED)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_INIT_UNSPECIFIED
#define START_SEC_COMMON_VAR_INIT_UNSPECIFIED

#elif defined(CAN_START_SEC_VAR_INIT_32)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_INIT_32
#define START_SEC_COMMON_VAR_INIT_32

#elif defined(CAN_START_SEC_VAR_INIT_16)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_INIT_16
#define START_SEC_COMMON_VAR_INIT_16

#elif defined(CAN_START_SEC_VAR_INIT_8)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_INIT_8
#define START_SEC_COMMON_VAR_INIT_8

#elif defined(CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#define START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED

#elif defined(CAN_START_SEC_VAR_NO_INIT_32)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_NO_INIT_32
#define START_SEC_COMMON_VAR_NO_INIT_32

#elif defined(CAN_START_SEC_VAR_NO_INIT_16)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_NO_INIT_16
#define START_SEC_COMMON_VAR_NO_INIT_16

#elif defined(CAN_START_SEC_VAR_NO_INIT_8)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_VAR_NO_INIT_8
#define START_SEC_COMMON_VAR_NO_INIT_8

#elif defined(CAN_START_SEC_CONST_UNSPECIFIED)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_CONST_UNSPECIFIED
#define START_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(CAN_START_SEC_CONST_32)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_CONST_32
#define START_SEC_COMMON_CONST_32
#elif defined(CAN_START_SEC_CONST_16)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_CONST_16
#define START_SEC_COMMON_CONST_16
#elif defined(CAN_START_SEC_CONST_8)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_CONST_8
#define START_SEC_COMMON_CONST_8
#elif defined(CAN_START_SEC_CONFIG_DATA)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_CONFIG_DATA
#define START_SEC_COMMON_CONFIG_DATA
#elif defined(CAN_START_SEC_CODE)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_CODE
#define START_SEC_COMMON_CODE
#elif defined(CAN_START_SEC_ISR_CODE)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_ISR_CODE
#define START_SEC_COMMON_ISR_CODE

#elif defined(CAN_START_SEC_CALLOUT_CODE)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_START_SEC_CALLOUT_CODE
#define START_SEC_COMMON_CALLOUT_CODE

#endif

#if defined(CAN_STOP_SEC_VAR_INIT_UNSPECIFIED)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_INIT_UNSPECIFIED
#define STOP_SEC_COMMON_VAR_INIT_UNSPECIFIED

#elif defined(CAN_STOP_SEC_VAR_INIT_32)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_INIT_32
#define STOP_SEC_COMMON_VAR_INIT_32

#elif defined(CAN_STOP_SEC_VAR_INIT_16)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_INIT_16
#define STOP_SEC_COMMON_VAR_INIT_16

#elif defined(CAN_STOP_SEC_VAR_INIT_8)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_INIT_8
#define STOP_SEC_COMMON_VAR_INIT_8

#elif defined(CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#define STOP_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED

#elif defined(CAN_STOP_SEC_VAR_NO_INIT_32)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_NO_INIT_32
#define STOP_SEC_COMMON_VAR_NO_INIT_32

#elif defined(CAN_STOP_SEC_VAR_NO_INIT_16)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_NO_INIT_16
#define STOP_SEC_COMMON_VAR_NO_INIT_16

#elif defined(CAN_STOP_SEC_VAR_NO_INIT_8)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_VAR_NO_INIT_8
#define STOP_SEC_COMMON_VAR_NO_INIT_8

#elif defined(CAN_STOP_SEC_CONST_UNSPECIFIED)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_CONST_UNSPECIFIED
#define STOP_SEC_COMMON_CONST_UNSPECIFIED
#elif defined(CAN_STOP_SEC_CONST_32)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_CONST_32
#define STOP_SEC_COMMON_CONST_32
#elif defined(CAN_STOP_SEC_CONST_16)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_CONST_16
#define STOP_SEC_COMMON_CONST_16
#elif defined(CAN_STOP_SEC_CONST_8)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_CONST_8
#define STOP_SEC_COMMON_CONST_8
#elif defined(CAN_STOP_SEC_CONFIG_DATA)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_CONFIG_DATA
#define STOP_SEC_COMMON_CONFIG_DATA
#elif defined(CAN_STOP_SEC_CODE)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_CODE
#define STOP_SEC_COMMON_CODE
#elif defined(CAN_STOP_SEC_ISR_CODE)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_ISR_CODE
#define STOP_SEC_COMMON_ISR_CODE

#elif defined(CAN_STOP_SEC_CALLOUT_CODE)
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef CAN_STOP_SEC_CALLOUT_CODE
#define STOP_SEC_COMMON_CALLOUT_CODE

#endif

#if defined(START_SEC_COMMON_VAR_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_INIT_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_INIT_UNSPECIFIED_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_UNSPECIFIED)
#elif defined(START_SEC_COMMON_VAR_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_INIT_32_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_INIT_32_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_INIT_32
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_32)

#elif defined(START_SEC_COMMON_VAR_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_INIT_16_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_INIT_16_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_INIT_16
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_16)

#elif defined(START_SEC_COMMON_VAR_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_INIT_8_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_INIT_8_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_INIT_8
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_INIT_8)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_NO_INIT_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_NO_INIT_UNSPECIFIED_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_UNSPECIFIED)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_NO_INIT_32_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_NO_INIT_32_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_NO_INIT_32
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_32)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_NO_INIT_16_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_NO_INIT_16_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_NO_INIT_16
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_16)

#elif defined(START_SEC_COMMON_VAR_NO_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_DATA_NO_INIT_8_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_DATA_NO_INIT_8_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_VAR_NO_INIT_8
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_NO_INIT_8)

#elif defined(START_SEC_COMMON_CONST_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_CONST_UNSPECIFIED_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_CONST_UNSPECIFIED_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_CONST_UNSPECIFIED
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_UNSPECIFIED)

#elif defined(START_SEC_COMMON_CONST_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_CONST_32_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_CONST_32_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_CONST_32
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_32)

#elif defined(START_SEC_COMMON_CONST_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_CONST_16_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_CONST_16_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_CONST_16
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_16)

#elif defined(START_SEC_COMMON_CONST_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_CONST_8_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_CONST_8_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_CONST_8
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONST_8)

#elif defined(START_SEC_COMMON_CONFIG_DATA)
/*LDRA_INSPECTED 69 S : MISRAC_2012_D1.1
 * "Reason - Pragma usage is required here to allocate
 *  Code and Data memory sections to certain RAM area" */
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data:CAN_CONFIG_SECTION"
#else
#pragma SET_DATA_SECTION("CAN_CONFIG_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_CONFIG_DATA
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_DATA_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_DATA_SECTION (VAR_CONFIG_DATA)

#elif defined(START_SEC_COMMON_CODE)
/*LDRA_INSPECTED 69 S : MISRAC_2012_D1.1
 * "Reason - Pragma usage is required here to allocate
 *  Code and Data memory sections to certain RAM area" */
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text:CAN_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("CAN_TEXT_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_CODE
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE)

#elif defined(START_SEC_COMMON_ISR_CODE)
/*LDRA_INSPECTED 69 S : MISRAC_2012_D1.1
 * "Reason - Pragma usage is required here to allocate
 *  Code and Data memory sections to certain RAM area" */
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text:CAN_ISR_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("CAN_ISR_TEXT_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_ISR_CODE
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#ifdef MEMMAP_ACTIVE_CODE_SECTION
#error "SECTION start keyword not matching"
#endif
#define MEMMAP_ACTIVE_CODE_SECTION (CODE_ISR)

#elif defined(START_SEC_COMMON_CALLOUT_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text:CAN_CALLOUT_TEXT_SECTION"
#else
#pragma SET_CODE_SECTION("CAN_CALLOUT_TEXT_SECTION")
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef START_SEC_COMMON_CALLOUT_CODE
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
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
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_INIT_UNSPECIFIED
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_UNSPECIFIED))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_INIT_32
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_32))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_INIT_16
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_16))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_INIT_8
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_INIT_8))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_NO_INIT_UNSPECIFIED
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_UNSPECIFIED))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_NO_INIT_32
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_32))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_NO_INIT_16
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_16))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_VAR_NO_INIT_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_VAR_NO_INIT_8
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_NO_INIT_8))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_UNSPECIFIED)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_CONST_UNSPECIFIED
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_UNSPECIFIED))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_32)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_CONST_32
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_32))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_16)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_CONST_16
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_16))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONST_8)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_CONST_8
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONST_8))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CONFIG_DATA)
#if (defined CLANG) || (defined DIAB)
#pragma clang section data=".data"
#else
#pragma SET_DATA_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_CONFIG_DATA
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_DATA_SECTION) || \
    (MEMMAP_ACTIVE_DATA_SECTION != VAR_CONFIG_DATA))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_DATA_SECTION

#elif defined(STOP_SEC_COMMON_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text"
#else
#pragma SET_CODE_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_CODE
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_CODE_SECTION) || \
    (MEMMAP_ACTIVE_CODE_SECTION != CODE))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_CODE_SECTION

#elif defined(STOP_SEC_COMMON_ISR_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text"
#else
#pragma SET_CODE_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_ISR_CODE
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_CODE_SECTION) || \
    (MEMMAP_ACTIVE_CODE_SECTION != CODE_ISR))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_CODE_SECTION

#elif defined(STOP_SEC_COMMON_CALLOUT_CODE)
#if (defined CLANG) || (defined DIAB)
#pragma clang section text=".text"
#else
#pragma SET_CODE_SECTION()
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef STOP_SEC_COMMON_CALLOUT_CODE
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ERROR
#if (!defined(MEMMAP_ACTIVE_CODE_SECTION) || \
    (MEMMAP_ACTIVE_CODE_SECTION != CODE_CALLOUT))
#error "STOP keyword not matching start"
#endif
/*LDRA_INSPECTED 68 S : MISRAC_2012_R20.5
 * "Reason - Undef usage is required here
 * to define this memory section again" */
#undef MEMMAP_ACTIVE_CODE_SECTION

#endif

#ifdef MEMMAP_ERROR
#error "Can_Memmap.h pragma error"
#endif

#ifdef __cplusplus
}
#endif

