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
 *  \file     Cdd_Cmpss_Soc.h
 *
 *  \brief    This file contains SOC specific macros and defines for CDD CMPSS
 *
 */

#ifndef CDD_CMPSS_SOC_H_
#define CDD_CMPSS_SOC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "cslr_cmpssa.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Check if max user configuration is correct for the SOC */
#if (CDD_CMPSS_MAX > 9U)
#error "This SOC supports only up to 9 instances of CMPSS"
#endif

/**
 *  \name CMPSS base address
 *
 *  Base address of different HW units present in the SOC
 *  @{
 */
/** \brief CMPSSA0 base address */
#define CSL_CONTROLSS_CMPSSA0_U_BASE (0x50200000U)
/** \brief CMPSSA1 base address */
#define CSL_CONTROLSS_CMPSSA1_U_BASE (0x50201000U)
/** \brief CMPSSA2 base address */
#define CSL_CONTROLSS_CMPSSA2_U_BASE (0x50202000U)
/** \brief CMPSSA3 base address */
#define CSL_CONTROLSS_CMPSSA3_U_BASE (0x50203000U)
/** \brief CMPSSA4 base address */
#define CSL_CONTROLSS_CMPSSA4_U_BASE (0x50204000U)
/** \brief CMPSSA5 base address */
#define CSL_CONTROLSS_CMPSSA5_U_BASE (0x50205000U)
/** \brief CMPSSA6 base address */
#define CSL_CONTROLSS_CMPSSA6_U_BASE (0x50206000U)
/** \brief CMPSSA7 base address */
#define CSL_CONTROLSS_CMPSSA7_U_BASE (0x50207000U)
/** \brief CMPSSA8 base address */
#define CSL_CONTROLSS_CMPSSA8_U_BASE (0x50208000U)
/** @} */

/** \brief Base address array for all modules present in the device */
#define CDD_CMPSS_BASEADDR_ARRAY                                                                  \
    CSL_CONTROLSS_CMPSSA0_U_BASE, CSL_CONTROLSS_CMPSSA1_U_BASE, CSL_CONTROLSS_CMPSSA2_U_BASE,     \
        CSL_CONTROLSS_CMPSSA3_U_BASE, CSL_CONTROLSS_CMPSSA4_U_BASE, CSL_CONTROLSS_CMPSSA5_U_BASE, \
        CSL_CONTROLSS_CMPSSA6_U_BASE, CSL_CONTROLSS_CMPSSA7_U_BASE, CSL_CONTROLSS_CMPSSA8_U_BASE,

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* CDD_CMPSS_SOC_H_ */
