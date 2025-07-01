/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Auto generated file
 */
#include "ti_drivers_config.h"
#include <drivers/pinmux.h>

static Pinmux_PerCfg_t gPinMuxMainDomainCfg[] = {
    /* I2C0 pin config */
    /* I2C0_SCL -> I2C0_SCL (A13) */
    {PIN_I2C0_SCL, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* I2C0 pin config */
    /* I2C0_SDA -> I2C0_SDA (B13) */
    {PIN_I2C0_SDA, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* I2C2 pin config */
    /* I2C2_SCL -> UART0_RTSn (C7) */
    {PIN_UART0_RTSN, (PIN_MODE(1) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* I2C2 pin config */
    /* I2C2_SDA -> UART0_CTSn (B7) */
    {PIN_UART0_CTSN, (PIN_MODE(1) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},

    /* MDIO pin config */
    /* MDIO_MDIO -> MDIO_MDIO (N16) */
    {PIN_MDIO_MDIO, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
    /* MDIO pin config */
    /* MDIO_MDC -> MDIO_MDC (M17) */
    {PIN_MDIO_MDC, (PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW)},
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
