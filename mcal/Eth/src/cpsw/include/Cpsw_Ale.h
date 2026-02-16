/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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
 *  \file       Cpsw_Ale.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              contains some abstraction layer for ALE module of CPSW
 *              subsystem.
 */

#ifndef CPSW_ALE_H_
#define CPSW_ALE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

/** \brief Enumerates types of Unicast ALE table entry. */
/**< Unicast address that is not ageable. */
#define CPSW_ALE_TBL_UNICAST_TYPE_NOT_AGEABLE (0x0U)

/**< Ageable unicast address that has not been touched. */
#define CPSW_ALE_TBL_UNICAST_TYPE_AGEABLE_UNTOUCH (0x1U)

/**< Non ageable OUI address. */
#define CPSW_ALE_TBL_UNICAST_TYPE_OUI (0x2U)

/**< Ageable unicast address that has been touched. */
#define CPSW_ALE_TBL_UNICAST_TYPE_AGEABLE_TOUCH (0x3U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Enumerates port state configuration values in address lookup engine.
 **/
typedef enum
{
    CPSW_ALE_PORT_STATE_DISABLED = 0x00U,
    /**< Port is disabled in address lookup engine. */
    CPSW_ALE_PORT_STATE_BLOCKED = 0x01U,
    /**< Port is blocked in address lookup engine. */
    CPSW_ALE_PORT_STATE_LEARN = 0x02U,
    /**< Port is configured for learning in address lookup engine. */
    CPSW_ALE_PORT_STATE_FWD = 0x03U,
    /**< Port is configured to forward in address lookup engine. */
} Eth_CpswAlePortState;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API initializes ALE. It clears the ALE table and enables packet
 *          processing by ALE.
 *
 * \param   baseAddr    Base address of the CPSW.
 */
void CpswAle_init(uint32 baseAddr);

/**
 * \brief   This API configures the port state for a given port in the ALE.
 *
 * \param   baseAddr    Base address of the CPSW.
 * \param   portNum     The port number
 * \param   portState   The port state takes values #Eth_CpswAlePortState.
 */
void CpswAle_setPortState(uint32 baseAddr, uint32 portNum, uint32 portState);

/**
 * \brief   Sets the Unknown VLAN Registered Multicast Flood Mask
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   rfmVal        Unknown VLAN Registered Multicast Flood Mask Value
 *
 * \return  None
 *
 **/
void CpswAle_setUnknownRegFloodMask(uint32 baseAddr, uint32 rfmVal);

/**
 * \brief   Sets the Unknown VLAN Unregistered Multicast Flood Mask
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   urfmVal       Unknown VLAN Unregistered Multicast Flood Mask Value
 *
 * \return  None
 *
 **/
void CpswAle_setUnknownUnregFloodMask(uint32 baseAddr, uint32 urfmVal);

/**
 * \brief   Sets the Unknown VLAN Member List
 *
 * \param   baseAddr      Base Address of the ALE module
 * \param   mlVal        Unknown VLAN UnRegistered Multicast Flood Mask Value
 *
 * \return  None
 *
 **/
void CpswAle_setUnknownMemberList(uint32 baseAddr, uint32 mlVal);

/**
 * \brief   This API enables/disables the bypassing of the ALE logic for all
 *          packets received on slave ports to the host port.
 *
 * \param   baseAddr     Base Address of the CPSW.
 * \param   enableBypass Bypass ALE logic configuration takes values
 *                       -# TRUE  - Enable bypass mode
 *                       -# FALSE - Disable bypass mode
 */
void CpswAle_enableBypass(uint32 baseAddr, uint32 enableBypass);

/**
 * \brief Adds an unicast entry in the ALE table.
 *
 * \param baseAddr      Base address of the CPSW.
 * \param pMacAddr      Ethernet address
 * \param vlanId        VLAN ID
 * \param portNum       The port number
 *
 * \retval index of the ALE entry added
 * \retval Max number of entry as invalid value if table entry is not free
 */
uint32 CpswAle_addUnicastEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint32 portNum);

/**
 * \brief Deletes an unicast entry in the ALE table.
 *
 * \param baseAddr   Base address of the CPSW.
 * \param pMacAddr   Ethernet address
 * \param vlanId     VLAN ID
 * \param portNum    The port number
 *
 * \retval index of the ALE entry deleted
 * \retval Max number of entry as invalid value if table entry is not present
 */
uint32 CpswAle_delUnicastEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint32 portNum);

/**
 * \brief Adds a multicast entry in the ALE table
 *
 * \param baseAddr        Base address of the CPSW.
 * \param pMacAddr        Ethernet Address
 * \param vlanId          VLAN ID
 * \param portNum         The port number
 *
 * \retval index of the ALE entry added
 * \retval Max number of entry as invalid value if table entry is not free
 */
uint32 CpswAle_addMulticastEntry(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint32 portMask);

/**
 * \brief Deletes a multicast entry in the ALE table
 *
 * \param baseAddr   Base address of the CPSW.
 * \param pMacAddr   Ethernet Address
 * \param vlanId     VLAN ID
 * \param portNum    The port number
 *
 * \retval index of the ALE entry deleted
 * \retval Max number of entry as invalid value
 */
uint32 CpswAle_delMulticastEntryPort(uint32 baseAddr, const uint8 macAddr[6], uint32 vlanId, uint8 portNum);

/**
 * \brief   This API clears the entries of address lookup table.
 *
 * \param   baseAddr    Base address of the CPSW.
 */
void CpswAle_clearTable(uint32 baseAddr);

/* ========================================================================== */
/*                        Deprecated Function Declarations                    */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CPSW_ALE_H_ */
