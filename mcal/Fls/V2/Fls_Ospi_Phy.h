/*
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file     Fls_Ospi_Phy.h
 *
 *  \brief    This file contains Phy tuning interface for FLS MCAL driver
 *
 */

#ifndef FLS_OSPI_PHY_H_
#define FLS_OSPI_PHY_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "hw_ospi.h"
#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"
#include "hw_ctrl_core.h"
#include "Fls_Ospi.h"
#include "Fls_Brd_Nor.h"
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/*Size- defs */
#define OSPI_FLASH_ATTACK_VECTOR_SIZE (128U)

#define OSPI_PHY_TUNING_FREQ_RANGE (133333333U)

#define OSPI_PHY_OFFSET 0x80000U

/* PHY-config */
typedef enum
{
    FLS_PHY_MASTER_MODE,
    FLS_PHY_BYPASS_MODE
} Fls_PhyControlMode;

typedef enum
{
    FLS_PHY_DLL_FULL_CYCLE,
    FLS_PHY_DLL_HALF_CYCLE
} Fls_PhyDllLockMode;

/* Baud Rate Control*/
#define CSL_OSPI_BAUD_RATE_DIVISOR(x)              (((x) - 2U) >> 1U)
#define MAX_BAUDRATE_DIVIDER                       (32U)
#define CSL_OSPI_BAUD_RATE_DIVISOR_DEFAULT         (CSL_OSPI_BAUD_RATE_DIVISOR(MAX_BAUDRATE_DIVIDER))
#define OSPI_PHASE_DETECT_DLL_NUM_DELAY_ELEMENT(x) ((uint32)((x) - 1U))

#define MIN(x, y)           \
    ({                      \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        _x < _y ? _x : _y;  \
    })

#define MAX(x, y)           \
    ({                      \
        typeof(x) _x = (x); \
        typeof(y) _y = (y); \
        _x > _y ? _x : _y;  \
    })
#ifndef abs
#define abs(x) ((x) > 0 ? (x) : -(x))
#endif
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief OSPI PHY Tuning Window Parameters
 *
 *  These are input window parameters for OSPI PHY tuning algorithm. This data is usually SOC
 *  specific and is filled by SysConfig.
 *
 */
typedef struct
{
    int    txDllLowWindowStart;
    int    txDllLowWindowEnd;
    int    txDllHighWindowStart;
    int    txDllHighWindowEnd;
    int    rxLowSearchStart;
    int    rxLowSearchEnd;
    int    rxHighSearchStart;
    int    rxHighSearchEnd;
    int    txLowSearchStart;
    int    txLowSearchEnd;
    int    txHighSearchStart;
    int    txHighSearchEnd;
    int    txDLLSearchOffset;
    uint32 rxTxDLLSearchStep;
    uint32 rdDelayMin;
    uint32 rdDelayMax;
} OSPI_PhyWindowParams;

typedef struct
{
    int txDLL;
    int rxDLL;
    int rdDelay;
} Fls_Ospi_phyConfig;

typedef struct
{
    uint32               phaseDelayElement;
    Fls_PhyControlMode   phyControlMode;
    Fls_PhyDllLockMode   dllLockMode;
    OSPI_PhyWindowParams tuningWindowParams;
} Fls_Ospi_phyConfiguration;

extern uint32 readDataCaptureDelay;

Std_ReturnType Fls_Ospi_phyInit(void);
void           Fls_Ospi_phy_enable(void);
void           Fls_Ospi_phy_disable(void);

#ifdef __cplusplus
}
#endif
#endif /* #ifndef FLS_OSPI_PHY_H_ */

/** @} */
