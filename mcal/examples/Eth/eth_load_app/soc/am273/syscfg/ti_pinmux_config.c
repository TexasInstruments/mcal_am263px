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
    /* MSS_MDIO0 pin config */
    /* MSS_MDIO_DATA -> PAD_CM (P19) */
    {PIN_PAD_CM, (PIN_MODE(1) | PIN_PULL_DISABLE)},
    /* MSS_MDIO0 pin config */
    /* MSS_MDIO_CLK -> PAD_CN (R19) */
    {PIN_PAD_CN, (PIN_MODE(1) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_TCTL -> PAD_CA (J18) */
    {PIN_PAD_CA, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_RCTL -> PAD_CB (J17) */
    {PIN_PAD_CB, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_TD3 -> PAD_CC (K18) */
    {PIN_PAD_CC, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_TD2 -> PAD_CD (K16) */
    {PIN_PAD_CD, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_TD1 -> PAD_CE (L17) */
    {PIN_PAD_CE, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_TD0 -> PAD_CF (L18) */
    {PIN_PAD_CF, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_TCLK -> PAD_CG (K19) */
    {PIN_PAD_CG, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_RCLK -> PAD_CH (M19) */
    {PIN_PAD_CH, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_RD3 -> PAD_CI (L19) */
    {PIN_PAD_CI, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_RD2 -> PAD_CJ (M18) */
    {PIN_PAD_CJ, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_RD1 -> PAD_CK (N19) */
    {PIN_PAD_CK, (PIN_MODE(3) | PIN_PULL_DISABLE)},
    /* MSS_RGMII0 pin config */
    /* MSS_RGMII_RD0 -> PAD_CL (P18) */
    {PIN_PAD_CL, (PIN_MODE(3) | PIN_PULL_DISABLE)},

    /* MSS_UARTA pin config */
    /* MSS_UARTA_RX -> PAD_DA (U3) */
    {PIN_PAD_DA, (PIN_MODE(5) | PIN_PULL_DISABLE)},
    /* MSS_UARTA pin config */
    /* MSS_UARTA_TX -> PAD_DB (W2) */
    {PIN_PAD_DB, (PIN_MODE(5) | PIN_PULL_DISABLE)},

    {PINMUX_END, PINMUX_END}};

/*
 * Pinmux
 */

void Pinmux_init(void)
{
    Pinmux_config(gPinMuxMainDomainCfg, PINMUX_DOMAIN_ID_MAIN);
}
