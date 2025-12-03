/********************************************************************
 * Copyright (C) 2024 Texas Instruments Incorporated.
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
 *
 *  Name        : Cdd_Dma_xbar.h
 */

#ifndef CDD_DMA_XBAR_H
#define CDD_DMA_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "Cdd_Dma_trig_xbar.h"
#include "Cdd_Dma_dmaxbar.h"
#include "Std_Types.h"
#define CDD_DMA_START_SEC_CODE
#include "Cdd_Dma_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CDD_DMA_STOP_SEC_CODE
#include "Cdd_Dma_MemMap.h"

/**
 *  \defgroup DRV_SOC_XBAR_MODULE APIs for SOC Xbars
 *  \ingroup DRV_SOC_MODULE
 *
 * For more details and example usage, see \ref DRIVERS_SOC_PAGE
 *
 *  @{
 */

/**************************************************************************
     Macros
**************************************************************************/

#define CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP \
    (CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR1_GSEL - CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_GSEL)

/**
 * \brief Trip & Sync xbar: API to select input source of DMA XBar
 *
 * \param base [in] DMA XBar base address
 * \param out [in] Instance of DMA XBar
 * \param group0_muxctl [in] Mux control to select input from group 0 mux
 * \param group1_muxctl [in] Mux control to select input from group 1 mux
 * \param group2_muxctl [in] Mux control to select input from group 2 mux
 * \param group3_muxctl [in] Mux control to select input from group 3 mux
 * \param group4_muxctl [in] Mux control to select input from group 4 mux
 * \param group5_muxctl [in] Mux control to select input from group 5 mux
 * \param group_select [in] Mux control to select group 0/1/2/3/4/5
 *
 */

/* ========================================================================== */
/*                             Inline function definition                     */
/* ========================================================================== */
static inline void Cdd_Dma_Soc_xbarSelectDmaXBarInputSource(uint32 base, uint8 out, uint8 group_select,
                                                            uint8 group0_muxctl, uint8 group1_muxctl,
                                                            uint8 group2_muxctl, uint8 group3_muxctl,
                                                            uint8 group4_muxctl, uint8 group5_muxctl)
{
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_GSEL,
                (uint32)group_select & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_GSEL_GSEL_MASK);
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G0,
                (uint32)group0_muxctl & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G0_SEL_MASK);
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G1,
                (uint32)group1_muxctl & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G1_SEL_MASK);
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G2,
                (uint32)group2_muxctl & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G2_SEL_MASK);
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G3,
                (uint32)group3_muxctl & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G3_SEL_MASK);
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G4,
                (uint32)group4_muxctl & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G4_SEL_MASK);
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G5,
                (uint32)group5_muxctl & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G5_SEL_MASK);
}

#if defined(AM263PX_PLATFORM)
static inline void Cdd_Dma_Soc_xbarSelectDmaXBarInputSourceExt(uint32 base, uint8 out, uint8 group_select,
                                                               uint8 group0_muxctl, uint8 group1_muxctl,
                                                               uint8 group2_muxctl, uint8 group3_muxctl,
                                                               uint8 group4_muxctl, uint8 group5_muxctl,
                                                               uint8 group6_muxctl)
{
    Cdd_Dma_Soc_xbarSelectDmaXBarInputSource(base, out, group_select, group0_muxctl, group1_muxctl, group2_muxctl,
                                             group3_muxctl, group4_muxctl, group5_muxctl);
    HW_WR_REG32(base + (out * CDD_DMA_CSL_CONTROLSS_DMAXBAR_STEP) + CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G6,
                (uint32)group6_muxctl & CDD_DMA_CSL_CONTROLSS_DMAXBAR_DMAXBAR0_G6_SEL_MASK);
}
#endif

/**
 * \brief SoC level xbars: API to select input source of EDMA Trigger XBar
 *
 * \param base [in] EDMA Trigger XBar base address
 * \param out [in] Instance of EDMA Trigger XBar
 * \param mux_control [in] Mux control to select input source
 *
 */
static inline void Cdd_Dma_Soc_xbarSelectEdmaTrigXbarInputSource(uint32 base, uint8 out, uint8 mux_control)
{
    HW_WR_REG32(base + CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL(out),
                (CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_INT_ENABLE_MASK) |
                    (mux_control & CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_ENABLE_MASK));
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif  // SOC_XBAR_AM263X_H_
