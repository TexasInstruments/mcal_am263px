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
    /* I2C1 pin config */
    /* I2C1_SCL -> I2C1_SCL (D7) */
    {PIN_I2C1_SCL, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* I2C1 pin config */
    /* I2C1_SDA -> I2C1_SDA (C8) */
    {PIN_I2C1_SDA, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},

    /* GPIO105 -> PR0_PRU1_GPIO10 (D17) */
    {PIN_PR0_PRU1_GPIO10, (PIN_MODE(7) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW | PIN_GPIO_R5SS0_0)},

    /* MDIO pin config */
    /* MDIO_MDC -> MDIO_MDC (M17) */
    {PIN_MDIO_MDC, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* MDIO pin config */
    /* MDIO_MDIO -> MDIO_MDIO (N16) */
    {PIN_MDIO_MDIO, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD0 -> RGMII1_RD0 (U17) */
    {PIN_RGMII1_RD0, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD1 -> RGMII1_RD1 (T17) */
    {PIN_RGMII1_RD1, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD2 -> RGMII1_RD2 (U18) */
    {PIN_RGMII1_RD2, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RD3 -> RGMII1_RD3 (T18) */
    {PIN_RGMII1_RD3, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RXC -> RGMII1_RXC (R17) */
    {PIN_RGMII1_RXC, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_RX_CTL -> RGMII1_RX_CTL (R18) */
    {PIN_RGMII1_RX_CTL, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD0 -> RGMII1_TD0 (P16) */
    {PIN_RGMII1_TD0, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD1 -> RGMII1_TD1 (P17) */
    {PIN_RGMII1_TD1, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD2 -> RGMII1_TD2 (P18) */
    {PIN_RGMII1_TD2, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TD3 -> RGMII1_TD3 (N17) */
    {PIN_RGMII1_TD3, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TXC -> RGMII1_TXC (N18) */
    {PIN_RGMII1_TXC, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII1 pin config */
    /* RGMII1_TX_CTL -> RGMII1_TX_CTL (M18) */
    {PIN_RGMII1_TX_CTL, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD0 -> PR0_PRU0_GPIO0 (K17) */
    {PIN_PR0_PRU0_GPIO0, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD1 -> PR0_PRU0_GPIO1 (K18) */
    {PIN_PR0_PRU0_GPIO1, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD2 -> PR0_PRU0_GPIO2 (J18) */
    {PIN_PR0_PRU0_GPIO2, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RD3 -> PR0_PRU0_GPIO3 (J17) */
    {PIN_PR0_PRU0_GPIO3, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RXC -> PR0_PRU0_GPIO6 (K15) */
    {PIN_PR0_PRU0_GPIO6, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_RX_CTL -> PR0_PRU0_GPIO4 (K16) */
    {PIN_PR0_PRU0_GPIO4, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD0 -> PR0_PRU0_GPIO11 (M16) */
    {PIN_PR0_PRU0_GPIO11, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD1 -> PR0_PRU0_GPIO12 (M15) */
    {PIN_PR0_PRU0_GPIO12, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD2 -> PR0_PRU0_GPIO13 (H17) */
    {PIN_PR0_PRU0_GPIO13, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TD3 -> PR0_PRU0_GPIO14 (H16) */
    {PIN_PR0_PRU0_GPIO14, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TXC -> PR0_PRU0_GPIO16 (H18) */
    {PIN_PR0_PRU0_GPIO16, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* RGMII2 pin config */
    /* RGMII2_TX_CTL -> PR0_PRU0_GPIO15 (L16) */
    {PIN_PR0_PRU0_GPIO15, (PIN_MODE(3) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},

    /* UART0 pin config */
    /* UART0_RXD -> UART0_RXD (A7) */
    {PIN_UART0_RXD, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* UART0 pin config */
    /* UART0_TXD -> UART0_TXD (A6) */
    {PIN_UART0_TXD, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},

    {PINMUX_END, PINMUX_END}};

/*
 * Pinmux
 */

void Pinmux_init(void)
{
    Pinmux_config(gPinMuxMainDomainCfg, PINMUX_DOMAIN_ID_MAIN);
}
