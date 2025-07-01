/*
 *
 * Copyright (c) 2024-2025 Texas Instruments Incorporated
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
 * *       No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * *       any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * *       Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * *       any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * *       any redistribution and use of any object code compiled from the source code
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
 *  \file     Cpsw_Hw.h
 *
 *  \brief    This file contains macros to access CPSW hardware register.
 */

#ifndef CPSW_HW_H_
#define CPSW_HW_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Hw_Cpsw_Ale.h"
#include "Hw_Cpsw_Cpdma.h"
#include "Hw_Cpsw_Cpts.h"
#include "Hw_Cpsw.h"
#include "Hw_Cpsw_Mdio.h"
#include "Hw_Cpsw_Port.h"
#include "Hw_Cpsw_Ss.h"
#include "Hw_Cpsw_Stats.h"

/* There are static inline functions in hw_types.h file. Map them as well */
#define ETH_START_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

#include "hw_types.h"

#define ETH_STOP_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/* CPTS macros */
#define CPTS_WR_REG(reg, val) HW_WR_REG32(baseAddr + CPSW_CPTS_##reg##_REG, val)

#define CPTS_WR_FIELD(reg, field, val) \
    HW_WR_FIELD32(baseAddr + CPSW_CPTS_##reg##_REG, CPSW_CPTS_##reg##_REG_##field, val)

#define CPTS_RD_REG(reg) HW_RD_REG32(baseAddr + CPSW_CPTS_##reg##_REG)

#define CPTS_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + CPSW_CPTS_##reg##_REG, CPSW_CPTS_##reg##_REG_##field)

#define CPTS_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, CPSW_CPTS_##reg##_REG_##field)

/* ALE macros */
#define ALE_WR_REG(reg, val) HW_WR_REG32(baseAddr + CPSW_ALE_##reg##_REG, val)

#define ALE_WR_FIELD(reg, field, val) HW_WR_FIELD32(baseAddr + CPSW_ALE_##reg##_REG, CPSW_ALE_##reg##_REG_##field, val)

#define ALE_WR_PORT_FIELD(reg, portNum, field, val) \
    HW_WR_FIELD32(baseAddr + CPSW_ALE_##reg##_REG(portNum), CPSW_ALE_##reg##_REG_##field, val)

#define ALE_RD_REG(reg) HW_RD_REG32(baseAddr + CPSW_ALE_##reg##_REG)

#define ALE_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + CPSW_ALE_##reg##_REG, CPSW_ALE_##reg##_REG_##field)

#define ALE_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, CPSW_ALE_##reg##_REG_##field)

#define ALE_SET_FIELD(regVal, reg, field, fieldVal) HW_SET_FIELD32(regVal, CPSW_ALE_##reg##_REG_##field, fieldVal)

/* MDIO macros */
#define MDIO_WR_REG(reg, val) HW_WR_REG32(baseAddr + MDIO_##reg##_REG, val)

#define MDIO_WR_OFFSET_REG(reg, offset, val) HW_WR_REG32(baseAddr + MDIO_##reg##_REG + offset, val)

#define MDIO_WR_FIELD(reg, field, val) HW_WR_FIELD32(baseAddr + MDIO_##reg##_REG, MDIO_##reg##_REG_##field, val)

#define MDIO_WR_OFFSET_FIELD(reg, offset, field, val) \
    HW_WR_FIELD32(baseAddr + MDIO_##reg##_REG + offset, MDIO_##reg##_REG_##field, val)

#define MDIO_RD_REG(reg) HW_RD_REG32(baseAddr + MDIO_##reg##_REG)

#define MDIO_RD_OFFSET_REG(reg, offset) HW_RD_REG32(baseAddr + MDIO_##reg##_REG + offset)

#define MDIO_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + MDIO_##reg##_REG, MDIO_##reg##_REG_##field)

#define MDIO_RD_OFFSET_FIELD(reg, offset, field) \
    HW_RD_FIELD32(baseAddr + MDIO_##reg##_REG + offset, MDIO_##reg##_REG_##field)

#define MDIO_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, MDIO_##reg##_REG_##field)

#define MDIO_SET_FIELD(regVal, reg, field, fieldVal) HW_SET_FIELD32(regVal, MDIO_##reg##_REG_##field, fieldVal)

/* CPDMA macros */
#define CPDMA_WR_REG(reg, val) HW_WR_REG32(baseAddr + CPSW_CPDMA_##reg##_REG, val)

#define CPDMA_WR_CH_REG(reg, chNum, val) HW_WR_REG32(baseAddr + CPSW_CPDMA_##reg##_REG(chNum), val)

#define CPDMA_WR_FIELD(reg, field, val) HW_WR_FIELD32(baseAddr + CPSW_CPDMA_##reg##_REG, CPSW_CPDMA_##field, val)

#define CPDMA_RD_REG(reg) HW_RD_REG32(baseAddr + CPSW_CPDMA_##reg##_REG)

#define CPDMA_RD_CH_REG(reg, chNum) HW_RD_REG32(baseAddr + CPSW_CPDMA_##reg##_REG(chNum))

#define CPDMA_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + CPSW_CPDMA_##reg##_REG, CPSW_CPDMA_##field)

#define CPDMA_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, CPSW_CPDMA_##field)

#define CPDMA_SET_FIELD(regVal, field, fieldVal) HW_SET_FIELD32(regVal, CPSW_CPDMA_##field, fieldVal)

/* CPPI macros */
#define CPPI_WR_REG(reg, val) HW_WR_REG32(baseAddr + CPSW_CPPI_##reg##_REG, val)

#define CPPI_WR_PRIORITY_REG(reg, priority, val) HW_WR_REG32(baseAddr + CPSW_CPPI_##reg##_REG(priority), val)

#define CPPI_WR_FIELD(reg, field, val) \
    HW_WR_FIELD32(baseAddr + CPSW_CPPI_##reg##_REG, CPSW_CPPI_##reg##_REG_##field, val)

#define CPPI_WR_PRIORITY_FIELD(reg, priority, field, val) \
    HW_WR_FIELD32(baseAddr + CPSW_CPPI_##reg##_REG(priority), CPSW_CPPI_##reg##_REG_##field, val)

#define CPPI_RD_REG(reg) HW_RD_REG32(baseAddr + CPSW_CPPI_##reg##_REG)

#define CPPI_RD_PRIORITY_REG(reg, priority) HW_RD_REG32(baseAddr + CPSW_CPPI_##reg##_REG(priority))

#define CPPI_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + CPSW_CPPI_##reg##_REG, CPSW_CPPI_##reg##_REG_##field)

#define CPPI_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, CPSW_CPPI_##reg##_REG_##field)

#define CPPI_SET_FIELD(regVal, reg, field, fieldVal) HW_SET_FIELD32(regVal, CPSW_CPPI_##reg##_REG_##field, fieldVal)

/* ETH_PN macros */
#define ETH_PN_WR_REG(reg, val) HW_WR_REG32(baseAddr + CPSW_ETH_PN##reg##_REG, val)

#define ETH_PN_WR_PORT_REG(reg, portNum, val) \
    HW_WR_REG32(baseAddr + CPSW_ETH_PN_##reg##_REG + CPSW_PN_OFFSET(portNum), val)

#define ETH_PN_WR_FIELD(reg, field, val) \
    HW_WR_FIELD32(baseAddr + CPSW_ETH_PN_##reg##_REG, CPSW_ETH_PN_##reg##_REG_##field, val)

#define ETH_PN_WR_PORT_FIELD(reg, portNum, field, val) \
    HW_WR_FIELD32(baseAddr + CPSW_ETH_PN_##reg##_REG + CPSW_PN_OFFSET(portNum), CPSW_ETH_PN_##reg##_REG_##field, val)

#define ETH_PN_RD_REG(reg) HW_RD_REG32(baseAddr + CPSW_ETH_PN_##reg##_REG)

#define ETH_PN_RD_PORT_REG(reg, portNum) HW_RD_REG32(baseAddr + CPSW_ETH_PN_##reg##_REG + CPSW_PN_OFFSET(portNum))

#define ETH_PN_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + CPSW_ETH_PN_##reg##_REG, CPSW_ETH_PN_##reg##_REG_##field)

#define ETH_PN_RD_PORT_FIELD(reg, portNum, field) \
    HW_RD_FIELD32(baseAddr + CPSW_ETH_PN_##reg##_REG + CPSW_PN_OFFSET(portNum), CPSW_ETH_PN_##reg##_REG_##field)

#define ETH_PN_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, CPSW_ETH_PN_##reg##_REG_##field)

#define ETH_PN_SET_FIELD(regVal, reg, field, fieldVal) HW_SET_FIELD32(regVal, CPSW_ETH_PN_##reg##_REG_##field, fieldVal)

/* CPSW_SS macros */
#define CPSW_SS_WR_REG(reg, val) HW_WR_REG32(baseAddr + CPSW_SS_##reg##_REG, val)

#define CPSW_SS_WR_FIELD(reg, field, val) \
    HW_WR_FIELD32(baseAddr + CPSW_SS_##reg##_REG, CPSW_SS_##reg##_REG_##field, val)

#define CPSW_SS_RD_REG(reg) HW_RD_REG32(baseAddr + CPSW_SS_##reg##_REG)

#define CPSW_SS_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + CPSW_SS_##reg##_REG, CPSW_SS_##reg##_REG_##field)

#define CPSW_SS_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, CPSW_SS_##reg##_REG_##field)

#define CPSW_SS_SET_FIELD(regVal, reg, field, fieldVal) HW_SET_FIELD32(regVal, CPSW_SS_##reg##_REG_##field, fieldVal)

/* CPSW macros */
#define CPSW_WR_REG(reg, val) HW_WR_REG32(baseAddr + CPSW_##reg##_REG, val)

#define CPSW_WR_FIELD(reg, field, val) HW_WR_FIELD32(baseAddr + CPSW_##reg##_REG, CPSW_##reg##_REG_##field, val)

#define CPSW_RD_REG(reg) HW_RD_REG32(baseAddr + CPSW_##reg##_REG)

#define CPSW_RD_FIELD(reg, field) HW_RD_FIELD32(baseAddr + CPSW_##reg##_REG, CPSW_##reg##_REG_##field)

#define CPSW_GET_FIELD(regVal, reg, field) HW_GET_FIELD(regVal, CPSW_##reg##_REG_##field)

#define CPSW_SET_FIELD(regVal, reg, field, fieldVal) HW_SET_FIELD32(regVal, CPSW_##reg##_REG_##field, fieldVal)

#ifdef __cplusplus
}
#endif
#endif /* CPSW_HW_H_ */
