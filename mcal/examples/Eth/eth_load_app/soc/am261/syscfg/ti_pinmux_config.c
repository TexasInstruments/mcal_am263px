/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2021-2024 Texas Instruments Incorporated
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

/*
 * Auto generated file
 */
#include "ti_drivers_config.h"
#include <drivers/pinmux.h>

static Pinmux_PerCfg_t gPinMuxMainDomainCfg[] = {
    /* I2C0 pin config */
    /* I2C0_SCL -> GPIO135 (A13) */
    {PIN_GPIO135, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* I2C0 pin config */
    /* I2C0_SDA -> GPIO134 (B13) */
    {PIN_GPIO134, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},

    /* GPIO74 -> GPIO74 (R16) */
    {PIN_GPIO74, (PIN_MODE(7) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW | PIN_GPIO_R5SS0_0)},

    /* MDIO0 pin config */
    /* MDIO0_MDC -> GPIO42 (M17) */
    {PIN_GPIO42, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* MDIO0 pin config */
    /* MDIO0_MDIO -> GPIO41 (N16) */
    {PIN_GPIO41, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD0 -> GPIO31 (U17) */
    {PIN_GPIO31, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD1 -> GPIO32 (T17) */
    {PIN_GPIO32, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD2 -> GPIO33 (U18) */
    {PIN_GPIO33, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD3 -> GPIO34 (T18) */
    {PIN_GPIO34, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RXC -> GPIO29 (R17) */
    {PIN_GPIO29, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RX_CTL -> GPIO30 (R18) */
    {PIN_GPIO30, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD0 -> GPIO37 (P16) */
    {PIN_GPIO37, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD1 -> GPIO38 (P17) */
    {PIN_GPIO38, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD2 -> GPIO39 (P18) */
    {PIN_GPIO39, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD3 -> GPIO40 (N17) */
    {PIN_GPIO40, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TXC -> GPIO35 (N18) */
    {PIN_GPIO35, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TX_CTL -> GPIO36 (M18) */
    {PIN_GPIO36, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD0 -> GPIO93 (K17) */
    {PIN_GPIO93, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD1 -> GPIO94 (K18) */
    {PIN_GPIO94, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD2 -> GPIO95 (J18) */
    {PIN_GPIO95, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD3 -> GPIO96 (J17) */
    {PIN_GPIO96, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RXC -> GPIO91 (K15) */
    {PIN_GPIO91, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RX_CTL -> GPIO92 (K16) */
    {PIN_GPIO92, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD0 -> GPIO99 (M16) */
    {PIN_GPIO99, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD1 -> GPIO100 (M15) */
    {PIN_GPIO100, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD2 -> GPIO101 (H17) */
    {PIN_GPIO101, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD3 -> GPIO102 (H16) */
    {PIN_GPIO102, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TXC -> GPIO97 (H18) */
    {PIN_GPIO97, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TX_CTL -> GPIO98 (L16) */
    {PIN_GPIO98, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},

    /* UART0 pin config */
    /* UART0_RXD -> GPIO27 (A7) */
    {PIN_GPIO27, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* UART0 pin config */
    /* UART0_TXD -> GPIO28 (A6) */
    {PIN_GPIO28, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},

    {PINMUX_END, PINMUX_END}};

/*
 * Pinmux
 */

void Pinmux_init(void)
{
    Pinmux_config(gPinMuxMainDomainCfg, PINMUX_DOMAIN_ID_MAIN);
}
