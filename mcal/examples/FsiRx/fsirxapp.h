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

/**
 *  \file     fsiRxapp.h
 *
 *  \brief    FsiRx App example header file
 */

#ifndef CDD_FSI_APP_H_
#define CDD_FSI_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Cdd_FsiRx_Types.h"
#include "Cdd_FsiTx_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* ========================================================================== */
/*                           Macros related to CDD FSI Register.                  */
/* ========================================================================== */
/* LOCK0_KICK0 */

/* IBAR0_G3 FSI XBAR INT ENABLE */
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX0_INT1 (0x0001U)
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX0_INT2 (0x0002U)
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX1_INT1 (0x0004U)
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX1_INT2 (0x0008U)
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX2_INT1 (0x0010U)
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX2_INT2 (0x0020U)
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX3_INT1 (0x0040U)
#define CSL_CDD_FSI_RX_IBAR_IBAR0_G3_FSIRX3_INT2 (0x0080U)

#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS0_INT1 (0x0100U)
#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS0_INT2 (0x0200U)
#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS1_INT1 (0x0400U)
#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS1_INT2 (0x0800U)
#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS2_INT1 (0x1000U)
#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS2_INT2 (0x2000U)
#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS3_INT1 (0x4000U)
#define CSL_CDD_FSI_IBAR_IBAR0_G3_FS3_INT2 (0x8000U)
#define CSL_CONTROLSS_IBAR_IBAR0_G3        (0x00000010CU)

#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_0  146U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_1  147U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_2  148U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_3  149U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_4  150U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_5  151U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_6  152U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_7  153U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_8  154U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_9  155U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_10 156U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_11 157U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_12 158U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_13 159U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_14 160U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_15 161U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_16 162U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_17 163U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_18 164U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_19 165U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_20 166U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_21 167U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_22 168U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_23 169U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_24 170U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_25 171U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_26 172U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_27 173U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_28 174U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_29 175U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_30 176U
#define CDD_FSI_CORE0_CONTROLSS_INTRXBAR0_OUT_31 177U

/* Application Name. */
#define CDD_FSI_APP_NAME "FSIRX_APP"
#define CDD_FSI_APP_BASE 0x50291000UL
/* ========================================================================== */
/*                         Glo and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void _enable_interrupt_(void);
void Cdd_FsiTxApp_Notification(Cdd_FsiTx_HWUnitType hwUnitId);
void Cdd_FsiTxApp_OverRunNotification(Cdd_FsiTx_HWUnitType hwUnitId);
void Cdd_FsiTxApp_UnderRunNotification(Cdd_FsiTx_HWUnitType hwUnitId);
void Cdd_FsiRxApp_ResetNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void Cdd_FsiRxApp_OverrunNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void Cdd_FsiRxApp_UnderrunNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void Cdd_FsiRxApp_PingReceivedNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void Cdd_FsiRxApp_dataReceivedNotification(Cdd_FsiRx_HWUnitType hwUnitId);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_FSI_RX_APP_H_ */
