/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

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
extern const struct Cdd_FsiRx_ConfigType_s CddFsiRxConfigSet_0;
extern const struct Cdd_FsiTx_ConfigType_s CddFsiTxConfigSet_0;
/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
void                                       _enable_interrupt_(void);
void                                       Cdd_FsiTxApp_Notification(Cdd_FsiTx_HWUnitType hwUnitId);
void                                       Cdd_FsiTxApp_OverRunNotification(Cdd_FsiTx_HWUnitType hwUnitId);
void                                       Cdd_FsiTxApp_UnderRunNotification(Cdd_FsiTx_HWUnitType hwUnitId);
void                                       Cdd_FsiRxApp_ResetNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void                                       Cdd_FsiRxApp_OverrunNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void                                       Cdd_FsiRxApp_UnderrunNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void                                       Cdd_FsiRxApp_PingReceivedNotification(Cdd_FsiRx_HWUnitType hwUnitId);
void                                       Cdd_FsiRxApp_dataReceivedNotification(Cdd_FsiRx_HWUnitType hwUnitId);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_FSI_RX_APP_H_ */
