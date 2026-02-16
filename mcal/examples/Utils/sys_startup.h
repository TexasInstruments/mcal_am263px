/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023 Texas Instruments Incorporated
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

#ifndef SYS_STARTUP_H
#define SYS_STARTUP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sys_common.h"

/* Bit Masks */
/*! \brief
 * ARM R4 system control register bitwise MACROs
 */
/*
 * [31] IE Identifies little or big instruction endianness in use:
 * 0 = little-endianness
 * 1 = big-endianness.
 * The primary input CFGIE defines the reset value. This bit is read-only.
 */
#define M_SCTRL_IE_SBIT  (31U)  /* Start Bit*/
#define M_SCTRL_IE_MBITS (0x1U) /* Mask Bits*/

/*
 * [30] TE Thumb exception enable:
 * 0 = enable ARM exception generation
 * 1 = enable Thumb exception generation.
 * The primary input TEINIT defines the reset value.
 */
#define M_SCTRL_TE_SBIT  (30U)  /* Start Bit*/
#define M_SCTRL_TE_MBITS (0x1U) /* Mask Bits*/

/*
 * [29, 28] bits reserved
 */

/*
 * [27] NMFI , non-maskable fast interrupt enable:
 * 0 = Software can disable FIQs
 * 1 = Software cannot disable FIQs.
 * This bit is read-only. The configuration input CFGNMFI defines its value.
 */
#define M_SCTRL_NMFI_SBIT  (27U)  /* Start Bit*/
#define M_SCTRL_NMFI_MBITS (0x1U) /* Mask Bits*/

/*
 * [26] reserved
 */

/*
 * [25] EE Determines how the E bit in the CPSR is set on an exception:
 * 0 = CPSR E bit is set to 0 on an exception
 * 1 = CPSR E bit is set to 1 on an exception.
 * The primary input CFGEE defines the reset value.
 */
#define M_SCTRL_EE_SBIT  (25U)  /* Start Bit*/
#define M_SCTRL_EE_MBITS (0x1U) /* Mask Bits*/

/*
 * [24] VE Configures vectored interrupt:
 * 0 = exception vector address for IRQ is 0x00000018 or 0xFFFF0018. See V bit.
 * 1 = VIC controller provides handler address for IRQ.
 * The reset value of this bit is 0.
 */
#define M_SCTRL_VE_SBIT  (24U)  /* Start Bit*/
#define M_SCTRL_VE_MBITS (0x1U) /* Mask Bits*/

/*
 * [23 - 20] reserved
 */

/*
 * [19] DZ Divide by zero:
 * 0 = do not generate an Undefined Instruction exception
 * 1 = generate an Undefined Instruction exception.
 * The reset value of this bit is 0.
 */
#define M_SCTRL_DZ_SBIT  (19U)  /* Start Bit*/
#define M_SCTRL_DZ_MBITS (0x1U) /* Mask Bits*/

/*
 * [18] reserved
 */

/*
 * [17] BR MPU background region enable.
 * 0 = Disable BR
 * 1 = Enabe BR
 */
#define M_SCTRL_BR_SBIT  (17U)  /* Start Bit*/
#define M_SCTRL_BR_MBITS (0x1U) /* Mask Bits*/

/*
 * [16-14] reserved
 */

/*
 * [13] V Determines the location of exception vectors:
 * 0 = normal exception vectors selected, address range = 0x00000000-0x0000001C
 * 1 = high exception vectors (HIVECS) selected, address range = 0xFFFF0000-0xFFFF001C.
 * The primary input VINITHI defines the reset value.
 */
#define M_SCTRL_V_SBIT  (13U)  /* Start Bit*/
#define M_SCTRL_V_MBITS (0x1U) /* Mask Bits*/

/*
 * [12-2] reserved
 */

/*
 * [1] A Enables strict alignment of data to detect alignment faults in data accesses:
 * 0 = strict alignment fault checking disabled. This is the reset value.
 * 1 = strict alignment fault checking enabled.
 */
#define M_SCTRL_A_SBIT  (1U)   /* Start Bit*/
#define M_SCTRL_A_MBITS (0x1U) /* Mask Bits*/

/*
 * [0] M Enables the MPU:
 * 0 = MPU disabled. This is the reset value.
 * 1 = MPU enabled.
 */
#define M_SCTRL_M_SBIT  (0U)   /* Start Bit*/
#define M_SCTRL_M_MBITS (0x1U) /* Mask Bits*/

/*! \brief
 * ARM R4 Auxiliary system control register bitwise MACROs
 */
/*
 * [31] DICDIa Case C dual issue control:
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 * [30] DIB2DIa Case B2 dual issue control:
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 * [29] DIB1DIa Case B1 dual issue control:
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 * [28] DIADIa Case A dual issue control:
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 */
#define M_ASCTRL_DI_SBIT  (28U)  /* Start Bit*/
#define M_ASCTRL_DI_MBITS (0xFU) /* Mask Bits*/

/*
 * [27] B1TCMPCEN B1TCM parity or ECC check enable:
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input PARECCENRAM[2]b defines the reset value.
 * If the BTCM is configured with ECC, you must always set this bit to the same value as
 * B0TCMPCEN.
 * [26] B0TCMPCEN B0TCM parity or ECC check enable:
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input PARECCENRAM[1]b defines the reset value.
 * If the BTCM is configured with ECC, you must always set this bit to the same value as
 * B1TCMPCEN.
 */
#define M_ASCTRL_BTCMECC_SBIT  (26U)  /* Start Bit*/
#define M_ASCTRL_BTCMECC_MBITS (0x3U) /* Mask Bits*/

/*
 * [25] ATCMPCEN ATCM parity or ECC check enable:
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input PARECCENRAM[0]b defines the reset value.
 */
#define M_ASCTRL_ATCMECC_SBIT  (25U)  /* Start Bit*/
#define M_ASCTRL_ATCMECC_MBITS (0x1U) /* Mask Bits*/

/*
 * [24-23] reserved
 */

/*
 * [22] DILSM Disable Low Interrupt Latency (LIL) on load/store multiples:
 * 0 = Enable LIL on load/store multiples. This is the reset value.
 * 1 = Disable LIL on all load/store multiples.
 */
#define M_ASCTRL_DLILM_SBIT  (22U)  /* Start Bit*/
#define M_ASCTRL_DLILM_MBITS (0x1U) /* Mask Bits*/

/*
 * [21] DEOLP Disable end of loop prediction:
 * 0 = Enable loop prediction. This is the reset value.
 * 1 = Disable loop prediction.
 */
#define M_ASCTRL_DLP_SBIT  (21U)  /* Start Bit*/
#define M_ASCTRL_DLP_MBITS (0x1U) /* Mask Bits*/

/*
 * [20] DBHE Disable Branch History (BH) extension:
 * 0 = Enable the extension. This is the reset value.
 * 1 = Disable the extension.
 */
#define M_ASCTRL_DBH_SBIT  (20U)  /* Start Bit*/
#define M_ASCTRL_DBH_MBITS (0x1U) /* Mask Bits*/

/*
 * [19] FRCDIS Fetch rate control disable:
 * 0 = Normal fetch rate control operation. This is the reset value.
 * 1 = Fetch rate control disabled.
 */
#define M_ASCTRL_DFRC_SBIT  (19U)  /* Start Bit*/
#define M_ASCTRL_DFRC_MBITS (0x1U) /* Mask Bits*/

/*
 * [18] reserved
 */

/*
 * [17] RSDIS Return stack disable:
 * 0 = Normal return stack operation. This is the reset value.
 * 1 = Return stack disabled.
 */
#define M_ASCTRL_DRS_SBIT  (17U)  /* Start Bit*/
#define M_ASCTRL_DRS_MBITS (0x1U) /* Mask Bits*/

/*
 * [16:15] BP This field controls the branch prediction policy:
 * b00 = Normal operation. This is the reset value.
 * b01 = Branch always taken.
 * b10 = Branch always not taken.
 * b11 = Reserved. Behavior is Unpredictable if this field is set to b11.
 */
#define M_ASCTRL_BP_SBIT  (15U)  /* Start Bit*/
#define M_ASCTRL_BP_MBITS (0x3U) /* Mask Bits*/

/*
 * [14] DBWR Disable write burst in the AXI master:
 * 0 = Normal operation. This is the reset value.
 * 1 = Disable write burst optimization.
 */
#define M_ASCTRL_DAXIWB_SBIT  (14U)  /* Start Bit*/
#define M_ASCTRL_DAXIWB_MBITS (0x1U) /* Mask Bits*/

/*
 * [13] DLFO Disable linefill optimization in the AXI master:
 * 0 = Normal operation. This is the reset value.
 * 1 = Limits the number of outstanding data linefills to two.
 */
#define M_ASCTRL_DAXILF_SBIT  (13U)  /* Start Bit*/
#define M_ASCTRL_DAXILF_MBITS (0x1U) /* Mask Bits*/

/*
 * [12] reserved
 */

/*
 * [11] DNCH Disable data forwarding for Non-cacheable accesses in the AXI master:
 * 0 = Normal operation. This is the reset value.
 * 1 = Disable data forwarding for Non-cacheable accesses.
 */
#define M_ASCTRL_DAXIDF_SBIT  (11U)  /* Start Bit*/
#define M_ASCTRL_DAXIDF_MBITS (0x1U) /* Mask Bits*/

/*
 * [10-9] reserved
 */

/*
 * [8] FDSnS Force data side to not-shared when MPU is off:
 * 0 = Normal operation. This is the reset value.
 * 1 = Data side normal Non-cacheable forced to Non-shared when MPU is off.
 */
#define M_ASCTRL_FDNS_SBIT  (8U)   /* Start Bit*/
#define M_ASCTRL_FDNS_MBITS (0x1U) /* Mask Bits*/

/*
 * [7] sMOV sMOV of a divide does not complete out of order. No other instruction is
 * issued until the divide is finished.
 * 0 = Normal operation. This is the reset value.
 * 1 = sMOV out of order disabled.
 */
#define M_ASCTRL_SMOV_SBIT  (7U)   /* Start Bit*/
#define M_ASCTRL_SMOV_MBITS (0x1U) /* Mask Bits*/

/*
 * [6] DILS Disable low interrupt latency on all load/store instructions.
 * 0 = Enable LIL on all load/store instructions. This is the reset value.
 * 1 = Disable LIL on all load/store instructions.
 */
#define M_ASCTRL_DLIL_SBIT  (6U)   /* Start Bit*/
#define M_ASCTRL_DLIL_MBITS (0x1U) /* Mask Bits*/

/*
 * [5-3] reserved
 */

/*
 * [2] B1TCMECEN B1TCM external error enable:
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input ERRENRAM[2] defines the reset value.
 * [1] B0TCMECEN B0TCM external error enable:
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input ERRENRAM[1] defines the reset value.
 */
#define M_ASCTRL_BTCMEE_SBIT  (1U)   /* Start Bit*/
#define M_ASCTRL_BTCMEE_MBITS (0x3U) /* Mask Bits*/

/*
 * [0] ATCMECEN ATCM external error enable:
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input ERRENRAM[0] defines the reset value.
 */
#define M_ASCTRL_ATCMEE_SBIT  (0U)   /* Start Bit*/
#define M_ASCTRL_ATCMEE_MBITS (0x1U) /* Mask Bits*/

/*! \brief
 * ARM R4 Secondary Auxiliary system control register bitwise MACROs
 */
/*
 * [31-21] reserved
 */

/*
 * [20] DF6DI F6 dual issue control:c
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 * [19] DF2DI F2_Id/F2_st/F2D dual issue control:c
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 * [18] DDI F1/F3/F4dual issue control:c
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 */
#define M_ASCTRL1_DI_SBIT  (18U)  /* Start Bit*/
#define M_ASCTRL1_DI_MBITS (0x7U) /* Mask Bits*/

/*
 * [17] DOODPFP Out-of-order Double Precision Floating Point instruction control:c
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 * [16] DOOFMACS Out-of-order FMACS control:c
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 */
#define M_ASCTRL1_VFPOO_SBIT  (16U)  /* Start Bit*/
#define M_ASCTRL1_VFPOO_MBITS (0x3U) /* Mask Bits*/

/*
 * [15-14] reserved
 */

/*
 * [13] IXC Floating-point inexact exception output mask::c
 * 0 = Mask floating-point inexact exception output. The output FPIXC is forced to zero. This
 * is the reset value.
 * 1 = Propagate floating point inexact exception flag FPSCR.IXC to output FPIXC.
 * [12] OFC Floating-point overflow exception output mask:c
 * 0 = Mask floating-point overflow exception output. The output FPOFC is forced to zero. This
 * is the reset value.
 * 1 = Propagate floating-point overflow exception flag FPSCR.OFC to output FPOFC.
 * [11] UFC Floating-point underflow exception output mask:c
 * 0 = Mask floating-point underflow exception output. The output FPUFC is forced to zero.
 * This is the reset value.
 * 1 = Propagate floating-point underflow exception flag FPSCR.UFC to output FPUFC.
 * [10] IOC Floating-point invalid operation exception output mask:c
 * 0 = Mask floating-point invalid operation exception output. The output FPIOC is forced to
 * zero. This is the reset value.
 * 1 = Propagate floating-point invalid operation exception flag FPSCR.IOC to output FPIOC.
 * [9] DZC Floating-point divide-by-zero exception output mask:c
 * 0 = Mask floating-point divide-by-zero exception output. The output FPDZC is forced to
 * zero. This is the reset value.
 * 1 = Propagate floating-point divide-by-zero exception flag FPSCR.DZC to output FPDZC.
 * [8] IDC Floating-point input denormal exception output mask:c
 * 0 = Mask floating-point input denormal exception output. The output FPIDC is forced to
 * zero. This is the reset value.
 * 1 = Propagate floating-point input denormal exception flag FPSCR.IDC to output FPIDC.
 */
#define M_ASCTRL1_VFPEO_SBIT  (8U)    /* Start Bit*/
#define M_ASCTRL1_VFPEO_MBITS (0x3FU) /* Mask Bits*/

/*
 * [7-4] reserved
 */

/*
 * [3] BTCMECC Correction for internal ECC logic on BTCM ports:d
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 */
#define M_ASCTRL1_BTCMECC_SBIT  (3U)   /* Start Bit*/
#define M_ASCTRL1_BTCMECC_MBITS (0x1U) /* Mask Bits*/

/*
 * [2] ATCMECC Correction for internal ECC logic on ATCM port:d
 * 0 = Enabled. This is the reset value.
 * 1 = Disabled.
 */
#define M_ASCTRL1_ATCMECC_SBIT  (2U)   /* Start Bit*/
#define M_ASCTRL1_ATCMECC_MBITS (0x1U) /* Mask Bits*/

/*
 * [1] BTCMRMW Enables 64-bit stores for the BTCMs. When enabled, the processor uses read-modify-
 * write to ensure that all reads and writes presented on the BTCM ports are 64 bits wide
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input RMWENRAM[1] defines the reset value.
 */
#define M_ASCTRL1_BTCMRMW_SBIT  (1U)   /* Start Bit*/
#define M_ASCTRL1_BTCMRMW_MBITS (0x1U) /* Mask Bits*/

/*
 * [0] ATCMRMW Enables 64-bit stores for the ATCM. When enabled, the processor uses read-modify-
 * write to ensure that all reads and writes presented on the ATCM port are 64 bits wide:e
 * 0 = Disabled
 * 1 = Enabled.
 * The primary input RMWENRAM[0] defines the reset value.
 */
#define M_ASCTRL1_ATCMRMW_SBIT  (0U)   /* Start Bit*/
#define M_ASCTRL1_ATCMRMW_MBITS (0x1U) /* Mask Bits*/

/*! \brief
 * ARM R4 Data Fault status registers bitwise MACROs
 */
/*
 * [31-13] Reserved
 */
/*
 * [12] SD Distinguishes between an AXI Decode or Slave error on an external abort. This bit is
 * only valid for external aborts. For all other aborts types of abort, this bit is set to zero:
 * 0 = AXI Decode error (DECERR) caused the abort
 * 1 = AXI Slave error (SLVERR, or OKAY in response to exclusive read transaction) caused the
 * abort.
 */
#define M_DFSR_SD_SBIT  (12U)  /* Start Bit*/
#define M_DFSR_SD_MBITS (0x1U) /* Mask Bits*/

/*
 * [11] RW Indicates whether a read or write access caused an abort:
 * 0 = read access caused the abort
 * 1 = write access caused the abort.
 */
#define M_DFSR_RW_SBIT  (11U)  /* Start Bit*/
#define M_DFSR_RW_MBITS (0x1U) /* Mask Bits*/

/*
 * [10]  S Part of the Status field.
 * [9-2] Reserved
 * [3:0] Status Indicates the type of fault generated. To determine the data fault, you must use
 * bit [12] and bit [10] in conjunction with bits [3:0].
 */
#define M_DFSR_STATE_SBIT  (0U)     /* Start Bit*/
#define M_DFSR_STATE_MBITS (0x40FU) /* Mask Bits*/

/*! \brief
 * ARM R4 Aux Data Fault status registers bitwise MACROs
 */
/*
 * [31-24] Reserved
 */
/*
 * [23:22] Side The value returned in this field indicates the source of the error.
 * Possible values are:
 * b00 = Cache or AXI master interface
 * b01 = ATCM
 * b10 = BTCM
 * b11 = Reserved.
 */
#define M_ADFSR_SOURCE_SBIT  (22U)  /* Start Bit*/
#define M_ADFSR_SOURCE_MBITS (0x3U) /* Mask Bits*/

/*
 * [21] Recoverable error
 * The value returned in this field indicates if the error is recoverable:
 * 0 = Unrecoverable error.
 * 1 = Recoverable error. This includes all correctable parity/ECC errors and recoverable TCM
 * external errors.
 */
#define M_ADFSR_RECOV_SBIT  (21U)  /* Start Bit*/
#define M_ADFSR_RECOV_MBITS (0x1U) /* Mask Bits*/

/* c1, System Control Register Mask value */
#define SYS_CTRL_MASK                                                                    \
    ((M_SCTRL_IE_MBITS << M_SCTRL_IE_SBIT) | (M_SCTRL_TE_MBITS << M_SCTRL_TE_SBIT) |     \
     (M_SCTRL_NMFI_MBITS << M_SCTRL_NMFI_SBIT) | (M_SCTRL_EE_MBITS << M_SCTRL_EE_SBIT) | \
     (M_SCTRL_VE_MBITS << M_SCTRL_VE_SBIT) | (M_SCTRL_DZ_MBITS << M_SCTRL_DZ_SBIT) |     \
     (M_SCTRL_BR_MBITS << M_SCTRL_BR_SBIT) | (M_SCTRL_V_MBITS << M_SCTRL_V_SBIT) |       \
     (M_SCTRL_A_MBITS << M_SCTRL_A_SBIT) | (M_SCTRL_M_MBITS << M_SCTRL_M_SBIT))

/* c1, Auxiliary Control Register */
#define AUX_CTRL_MASK                                                                                    \
    ((M_ASCTRL_DI_MBITS << M_ASCTRL_DI_SBIT) | (M_ASCTRL_BTCMECC_MBITS << M_ASCTRL_BTCMECC_SBIT) |       \
     (M_ASCTRL_ATCMECC_MBITS << M_ASCTRL_ATCMECC_SBIT) | (M_ASCTRL_DLILM_MBITS << M_ASCTRL_DLILM_SBIT) | \
     (M_ASCTRL_DLP_MBITS << M_ASCTRL_DLP_SBIT) | (M_ASCTRL_DBH_MBITS << M_ASCTRL_DBH_SBIT) |             \
     (M_ASCTRL_DFRC_MBITS << M_ASCTRL_DFRC_SBIT) | (M_ASCTRL_DRS_MBITS << M_ASCTRL_DRS_SBIT) |           \
     (M_ASCTRL_BP_MBITS << M_ASCTRL_BP_SBIT) | (M_ASCTRL_DAXIWB_MBITS << M_ASCTRL_DAXIWB_SBIT) |         \
     (M_ASCTRL_DAXILF_MBITS << M_ASCTRL_DAXILF_SBIT) | (M_ASCTRL_DAXIDF_MBITS << M_ASCTRL_DAXIDF_SBIT) | \
     (M_ASCTRL_FDNS_MBITS << M_ASCTRL_FDNS_SBIT) | (M_ASCTRL_SMOV_MBITS << M_ASCTRL_SMOV_SBIT) |         \
     (M_ASCTRL_DLIL_MBITS << M_ASCTRL_DLIL_SBIT) | (M_ASCTRL_BTCMEE_MBITS << M_ASCTRL_BTCMEE_SBIT) |     \
     (M_ASCTRL_ATCMEE_MBITS << M_ASCTRL_ATCMEE_SBIT))

/* c15, Secondary Auxiliary Control Register */
#define SEC_AUX_CTRL_MASK                                                                                        \
    ((M_ASCTRL1_DI_MBITS << M_ASCTRL1_DI_SBIT) | (M_ASCTRL1_VFPOO_MBITS << M_ASCTRL1_VFPOO_SBIT) |               \
     (M_ASCTRL1_VFPEO_MBITS << M_ASCTRL1_VFPEO_SBIT) | (M_ASCTRL1_BTCMECC_MBITS << M_ASCTRL1_BTCMECC_SBIT) |     \
     (M_ASCTRL1_ATCMECC_MBITS << M_ASCTRL1_ATCMECC_SBIT) | (M_ASCTRL1_BTCMRMW_MBITS << M_ASCTRL1_BTCMRMW_SBIT) | \
     (M_ASCTRL1_ATCMRMW_MBITS << M_ASCTRL1_ATCMRMW_SBIT))

/* System registers initial value */
/* c1, System Control Register value */
/*
 * The default setting of SYCTRL reg for MSS module
 * IE = little endian (0)
 * TE = ARM (0)
 * NMFI = FIQ (0)
 * EE = little endian (0)
 * VE = VIC disable (0)
 * DZ = enable (1)
 * BR = disable (0)
 * V = normal (0)
 * A = strict alignment (1)
 * M = MPU disabled (0)
 */
#define SYS_CTRL_VAL                                                                                             \
    ((0) | (0 << M_SCTRL_IE_SBIT) | (0 << M_SCTRL_TE_SBIT) | (0 << M_SCTRL_NMFI_SBIT) | (0 << M_SCTRL_EE_SBIT) | \
     (0 << M_SCTRL_VE_SBIT) | (1 << M_SCTRL_DZ_SBIT) | (0 << M_SCTRL_BR_SBIT) | (0 << M_SCTRL_V_SBIT) |          \
     (1 << M_SCTRL_A_SBIT) | (0 << M_SCTRL_M_SBIT))

/* c1, Auxiliary Control Register */
/*
 * The defualt setting of ASYCTRL reg for MSS module
 * DI = enabled (0)
 * BTCMECC = disabled (0)
 * ATCMECC = disabled (0)
 * LILM = enabled (0)
 * LP = enabled (0)
 * BH = enable (0)
 * FRC = enabled (0)
 * RS = enabled (0)
 * BP = normal (0)
 * AXIWB = enabled (0)
 * LF = enabled (0)
 * DF = normal (0)
 * FDNS = normal (0)
 * SMOV = normal (0)
 * LIL = enabled (0)
 * BTCMEE = enabled (1)
 * ATCMEE = enabled (1)
 */
#define AUX_CTRL_VAL                                                                                                   \
    ((0) | (0 << M_ASCTRL_DI_SBIT) | (0 << M_ASCTRL_BTCMECC_SBIT) | (0 << M_ASCTRL_ATCMECC_SBIT) |                     \
     (0 << M_ASCTRL_DLILM_SBIT) | (0 << M_ASCTRL_DLP_SBIT) | (0 << M_ASCTRL_DBH_SBIT) | (0 << M_ASCTRL_DFRC_SBIT) |    \
     (0 << M_ASCTRL_DRS_SBIT) | (0 << M_ASCTRL_BP_SBIT) | (0 << M_ASCTRL_DAXIWB_SBIT) | (0 << M_ASCTRL_DAXILF_SBIT) |  \
     (0 << M_ASCTRL_DAXIDF_SBIT) | (0 << M_ASCTRL_FDNS_SBIT) | (0 << M_ASCTRL_SMOV_SBIT) | (0 << M_ASCTRL_DLIL_SBIT) | \
     (1 << M_ASCTRL_BTCMEE_SBIT) | (1 << M_ASCTRL_ATCMEE_SBIT))

/* c15, Secondary Auxiliary Control Register */
/*
 * The defualt setting of ASYCTRL1 reg for BSS module
 * DI = enabled (0)
 * VFPOO = enabled(0)
 * VFPEO = disabled(0)
 * BTCMECC = enabled(0)
 * ATCMECC = enabled(0)
 * BTCMRMW = enabled(1)
 * ATCMRMW = enabled(1)
 */
#define SEC_AUX_CTRL_VAL                                                                             \
    ((0) | (0 << M_ASCTRL1_DI_SBIT) | (0 << M_ASCTRL1_VFPOO_SBIT) | (0 << M_ASCTRL1_VFPEO_SBIT) |    \
     (0 << M_ASCTRL1_BTCMECC_SBIT) | (0 << M_ASCTRL1_ATCMECC_SBIT) | (1 << M_ASCTRL1_BTCMRMW_SBIT) | \
     (1 << M_ASCTRL1_ATCMRMW_SBIT))

#ifdef __cplusplus
}
#endif

#endif
