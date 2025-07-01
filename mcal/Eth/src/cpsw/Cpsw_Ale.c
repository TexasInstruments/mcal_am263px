/*
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *  \file   Cpsw_Ale.c
 *
 *  \brief  This file contains the device abstraction layer API implementation
 *          corresponding to Address Lookup Engine (ALE) module of CPSW
 *          subsystem.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cpsw_Priv.h"
#include "Cpsw_Ale.h"
#include "Cpsw_Hw.h"
#include "Dem.h"
#include "Os.h"
#include "sys_common.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/** \brief ALE entry length in words. */
#define CPSW_ALE_ENTRY_NUM_WORDS (3U)

/** \brief Broadcast MAC address byte mask. */
#define CPSW_ALE_BROADCAST_MAC_ADDR_MASK (0xFFU)

/** \brief Multicast MAC address upper byte mask. */
#define CPSW_ALE_MULTICAST_MAC_ADDR_MASK (0x01U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Enumerates types of ALE table entry. */
typedef enum
{
    CPSW_ALE_TBL_ENTRY_TYPE_FREE = 0x0U,
    /**< Free entry. */
    CPSW_ALE_TBL_ENTRY_TYPE_ADDR = 0x1U,
    /**< Address type ALE entry. */
    CPSW_ALE_TBL_ENTRY_TYPE_VLAN = 0x2U,
    /**< VLAN type ALE entry. */
    CPSW_ALE_TBL_ENTRY_TYPE_VLAN_ADDR = 0x3U,
    /**< VLAN Address type ALE entry. */
} Eth_CpswAleTblEntryType;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static uint32 CpswAle_getFreeEntry(uint32 baseAddr);

static uint32 CpswAle_getAddrEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId);

static void CpswAle_getTableEntry(uint32 baseAddr, uint32 aleTblIdx, uint32 aleEntry[CPSW_ALE_ENTRY_NUM_WORDS]);

static void CpswAle_setTableEntry(uint32 baseAddr, uint32 aleTblIdx, const uint32 aleEntry[CPSW_ALE_ENTRY_NUM_WORDS]);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#define ETH_START_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
void CpswAle_init(uint32 baseAddr)
{
    /* Clear entire ALE table first */
    CpswAle_clearTable(baseAddr);

    /* Enable address lookup engine. */
    ALE_WR_FIELD(CONTROL, ENABLE, 1U);

    /* Enable VLAN aware */
    ALE_WR_FIELD(CONTROL, VLAN_AWARE, 1U);
}

void CpswAle_setPortState(uint32 baseAddr, uint32 portNum, uint32 portState)
{
    ALE_WR_PORT_FIELD(PORT_CONTROL, portNum, PORT_STATE, portState);
}

void CpswAle_setUnknownRegFloodMask(uint32 baseAddr, uint32 rfmVal)
{
    ALE_WR_FIELD(UNKNOWN_REG_MCAST_FLOOD, MASK, rfmVal);
}

void CpswAle_setUnknownUnregFloodMask(uint32 baseAddr, uint32 urfmVal)
{
    ALE_WR_FIELD(UNKNOWN_MCAST_FLOOD, MASK, urfmVal);
}

void CpswAle_setUnknownMemberList(uint32 baseAddr, uint32 mlVal)
{
    ALE_WR_FIELD(UNKNOWN_VLAN, LIST, mlVal);
}

void CpswAle_enableBypass(uint32 baseAddr, uint32 enableBypass)
{
    if ((uint32)TRUE == enableBypass)
    {
        ALE_WR_FIELD(CONTROL, BYPASS, 1U);
    }
    else
    {
        ALE_WR_FIELD(CONTROL, BYPASS, 0U);
    }
}

uint32 CpswAle_addUnicastEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint32 portNum)
{
    uint32 aleEntry[CPSW_ALE_ENTRY_NUM_WORDS] = {0U, 0U, 0U};
    uint32 idx                                = 0U;

    idx = CpswAle_getAddrEntry(baseAddr, &macAddr[0U], vlanId);
    if (Eth_GetMaxAleEntry() == idx)
    {
        idx = CpswAle_getFreeEntry(baseAddr);
    }
    else
    {
        CpswAle_getTableEntry(baseAddr, idx, aleEntry);
    }

    if (Eth_GetMaxAleEntry() != idx)
    {
        /* Configure input params to entry array */
        if ((uint32)0U == vlanId)
        {
            ALE_SET_FIELD(aleEntry[1U], TBLW1, ENTRY_TYPE, (uint32)CPSW_ALE_TBL_ENTRY_TYPE_ADDR);
        }
        else
        {
            ALE_SET_FIELD(aleEntry[1U], TBLW1, ENTRY_TYPE, CPSW_ALE_TBL_ENTRY_TYPE_VLAN_ADDR);
        }
        ALE_SET_FIELD(aleEntry[1U], TBLW1, ENTRY_VLAN_ID, vlanId);

        ALE_SET_FIELD(aleEntry[1U], TBLW1, UNI_ADDR_TYPE, CPSW_ALE_TBL_UNICAST_TYPE_NOT_AGEABLE);

        ALE_SET_FIELD(aleEntry[1U], TBLW1, MACADDR_0, macAddr[0U]);
        ALE_SET_FIELD(aleEntry[1U], TBLW1, MACADDR_1, macAddr[1U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_2, macAddr[2U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_3, macAddr[3U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_4, macAddr[4U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_5, macAddr[5U]);

        ALE_SET_FIELD(aleEntry[2U], TBLW2, UNI_ADDR_PORT_NUM, portNum);
        ALE_SET_FIELD(aleEntry[2U], TBLW2, UNI_ADDR_SECURE, 0U);
        ALE_SET_FIELD(aleEntry[2U], TBLW2, UNI_ADDR_BLOCK, 0U);
        ALE_SET_FIELD(aleEntry[2U], TBLW2, UNI_ADDR_DLR, 0U);

        /* Write entry array to ALE table registers */
        CpswAle_setTableEntry(baseAddr, idx, aleEntry);
    }

    return idx;
}

uint32 CpswAle_delUnicastEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint32 portNum)
{
    const uint32 freeAleEntry[CPSW_ALE_ENTRY_NUM_WORDS] = {0U, 0U, 0U};
    uint32       idx                                    = 0U;

    idx = CpswAle_getAddrEntry(baseAddr, &macAddr[0U], vlanId);
    if (Eth_GetMaxAleEntry() != idx)
    {
        CpswAle_setTableEntry(baseAddr, idx, freeAleEntry);
    }

    return idx;
}

uint32 CpswAle_addMulticastEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint32 portMask)
{
    uint32 aleEntry[CPSW_ALE_ENTRY_NUM_WORDS] = {0U, 0U, 0U};
    uint32 idx                                = 0U;
    uint32 regFieldVal;

    idx = CpswAle_getAddrEntry(baseAddr, &macAddr[0U], vlanId);
    if (Eth_GetMaxAleEntry() == idx)
    {
        idx = CpswAle_getFreeEntry(baseAddr);
    }

    if (Eth_GetMaxAleEntry() != idx)
    {
        CpswAle_getTableEntry(baseAddr, idx, aleEntry);

        if ((uint32)0U == vlanId)
        {
            ALE_SET_FIELD(aleEntry[1U], TBLW1, ENTRY_TYPE, CPSW_ALE_TBL_ENTRY_TYPE_ADDR);
        }
        else
        {
            ALE_SET_FIELD(aleEntry[1U], TBLW1, ENTRY_TYPE, CPSW_ALE_TBL_ENTRY_TYPE_VLAN_ADDR);
        }
        ALE_SET_FIELD(aleEntry[1U], TBLW1, ENTRY_VLAN_ID, vlanId);

        ALE_SET_FIELD(aleEntry[1U], TBLW1, MACADDR_0, macAddr[0U]);
        ALE_SET_FIELD(aleEntry[1U], TBLW1, MACADDR_1, macAddr[1U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_2, macAddr[2U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_3, macAddr[3U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_4, macAddr[4U]);
        ALE_SET_FIELD(aleEntry[0U], TBLW0, MACADDR_5, macAddr[5U]);

        regFieldVal  = ALE_GET_FIELD(aleEntry[2U], TBLW2, MULTI_ADDR_PORT_MASK);
        regFieldVal |= portMask;
        ALE_SET_FIELD(aleEntry[2U], TBLW2, MULTI_ADDR_PORT_MASK, regFieldVal);

        ALE_SET_FIELD(aleEntry[1U], TBLW1, MULTI_ADDR_FWD_STATE, (uint32)CPSW_ALE_PORT_STATE_FWD);

        ALE_SET_FIELD(aleEntry[2U], TBLW2, MULTI_ADDR_SUPER, 0U);

        /* Write entry array to ALE table registers */
        CpswAle_setTableEntry(baseAddr, idx, aleEntry);
    }

    return idx;
}

uint32 CpswAle_delMulticastEntryPort(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint8 portNum)
{
    uint32       aleEntry[CPSW_ALE_ENTRY_NUM_WORDS]     = {0U, 0U, 0U};
    const uint32 freeAleEntry[CPSW_ALE_ENTRY_NUM_WORDS] = {0U, 0U, 0U};
    uint32       idx                                    = 0U;
    uint32       regFieldVal                            = 0U;

    idx = CpswAle_getAddrEntry(baseAddr, &macAddr[0U], vlanId);

    if (Eth_GetMaxAleEntry() != idx)
    {
        CpswAle_getTableEntry(baseAddr, idx, aleEntry);

        regFieldVal  = ALE_GET_FIELD(aleEntry[2U], TBLW2, MULTI_ADDR_PORT_MASK);
        regFieldVal &= ~((uint32)1U << (uint32)portNum);

        if ((uint32)0U == regFieldVal)
        {
            CpswAle_setTableEntry(baseAddr, idx, freeAleEntry);
        }
        else
        {
            ALE_SET_FIELD(aleEntry[2U], TBLW2, MULTI_ADDR_PORT_MASK, regFieldVal);
            CpswAle_setTableEntry(baseAddr, idx, aleEntry);
        }
    }

    return idx;
}

void CpswAle_clearTable(uint32 baseAddr)
{
    volatile uint32 tempCount = ETH_TIMEOUT_DURATION;

    /* Clear address lookup engine table. */
    ALE_WR_FIELD(CONTROL, CLEAR_TABLE, 1U);

    /* Wait till the lookup engine table is cleared. Access to all ALE
     * registers will be blocked (wait states) until the 64 clocks
     * have completed */
    while (1U == ALE_RD_FIELD(CONTROL, CLEAR_TABLE))
    {
        if (0U == tempCount)
        {
#ifdef ETH_E_HARDWARE_ERROR
            (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        else
        {
            tempCount = tempCount - 1U;
        }
    }
}

/******************************************************************************/
/*                      Internal Functions                                    */
/******************************************************************************/

/**
 * \brief   This API sets an ALE table entry at given index.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   aleTblIdx    The Index of the table entry.
 * \param   pAleEntryPtr The address of the entry to be set.
 */
static void CpswAle_setTableEntry(uint32 baseAddr, uint32 aleTblIdx, const uint32 aleEntry[CPSW_ALE_ENTRY_NUM_WORDS])
{
    uint32 regVal = 0U;

    ALE_WR_REG(TBLW0, aleEntry[0]);
    ALE_WR_REG(TBLW1, aleEntry[1]);
    ALE_WR_REG(TBLW2, aleEntry[2]);

    ALE_SET_FIELD(regVal, TABLE_CONTROL, ENTRY_POINTER, aleTblIdx);
    ALE_SET_FIELD(regVal, TABLE_CONTROL, WRITE_RDZ, 1U);
    ALE_WR_REG(TABLE_CONTROL, regVal);
}

/**
 * \brief   This API reads an ALE table entry at given index.
 *
 * \param   baseAddr     Base address of the CPSW.
 * \param   aleTblIdx    The Index of the table entry.
 * \param   pAleEntryPtr The address where the ALE entry to be read.
 */
static void CpswAle_getTableEntry(uint32 baseAddr, uint32 aleTblIdx, uint32 aleEntry[CPSW_ALE_ENTRY_NUM_WORDS])
{
    ALE_WR_REG(TABLE_CONTROL, aleTblIdx);

    aleEntry[0] = ALE_RD_REG(TBLW0);
    aleEntry[1] = ALE_RD_REG(TBLW1);
    aleEntry[2] = ALE_RD_REG(TBLW2);
}

/**
 * \brief   Gives the index of the ALE entry which is free
 *
 * \param   baseAddr Base address of the CPSW.
 *
 * \retval  Maximum number of entry as invalid value if not found
 * \retval  index    Index of the ALE entry which is free.
 */
static uint32 CpswAle_getFreeEntry(uint32 baseAddr)
{
    uint32 aleEntry[CPSW_ALE_ENTRY_NUM_WORDS];
    uint32 idx = 0U;

    /* Check which ALE entry is free starting from 0th entry */
    for (idx = 0U; idx < Eth_GetMaxAleEntry(); idx++)
    {
        CpswAle_getTableEntry(baseAddr, idx, aleEntry);

        /* Break if the table entry is free */
        if ((uint32)CPSW_ALE_TBL_ENTRY_TYPE_FREE == ALE_GET_FIELD(aleEntry[1U], TBLW1, ENTRY_TYPE))
        {
            break;
        }
    }

    return idx;
}

/**
 * \brief  Gives the index of the ALE entry which match address of VLAN
 *
 * \param  baseAddr  Base address of the CPSW.
 * \param  pMacAddr  Ethernet address
 * \param  vlanId    VLAN ID
 *
 * \retval index of the ALE entry which match address of VLAN
 * \retval Maximum number of entry as invalid value if not found
 */
static uint32 CpswAle_getAddrEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId)
{
    uint32  aleEntry[CPSW_ALE_ENTRY_NUM_WORDS];
    uint32  entryType;
    uint32  idx          = 0U;
    boolean checkSameMac = FALSE;

    /* Check which ALE entry is free starting from 0th entry */
    for (idx = 0U; idx < Eth_GetMaxAleEntry(); idx++)
    {
        CpswAle_getTableEntry(baseAddr, idx, aleEntry);

        entryType = ALE_GET_FIELD(aleEntry[1U], TBLW1, ENTRY_TYPE);

        /* Goto next entry if the ale entry is not valid address */
        checkSameMac = FALSE;
        if ((uint32)CPSW_ALE_TBL_ENTRY_TYPE_ADDR == entryType)
        {
            checkSameMac = TRUE;
        }
        else if (((uint32)CPSW_ALE_TBL_ENTRY_TYPE_VLAN_ADDR == entryType) &&
                 (ALE_GET_FIELD(aleEntry[1U], TBLW1, ENTRY_VLAN_ID) == vlanId))
        {
            checkSameMac = TRUE;
        }
        else
        {
            /* nothing */
        }

        if (TRUE == checkSameMac)
        {
            if ((macAddr[0U] == (uint8)ALE_GET_FIELD(aleEntry[1U], TBLW1, MACADDR_0)) &&
                (macAddr[1U] == (uint8)ALE_GET_FIELD(aleEntry[1U], TBLW1, MACADDR_1)) &&
                (macAddr[2U] == (uint8)ALE_GET_FIELD(aleEntry[0U], TBLW0, MACADDR_2)) &&
                (macAddr[3U] == (uint8)ALE_GET_FIELD(aleEntry[0U], TBLW0, MACADDR_3)) &&
                (macAddr[4U] == (uint8)ALE_GET_FIELD(aleEntry[0U], TBLW0, MACADDR_4)) &&
                (macAddr[5U] == (uint8)ALE_GET_FIELD(aleEntry[0U], TBLW0, MACADDR_5)))
            {
                break; /* Found address entry with current idx */
            }
            else
            {
                /* nothing */
            }
        }
        else
        {
            /* nothing */
        }
    }

    return idx;
}

#define ETH_STOP_SEC_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
