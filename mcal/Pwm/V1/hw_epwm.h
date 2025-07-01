/* ======================================================================
 *   Copyright (c) 2021 Texas Instruments Incorporated
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

#ifndef HW_EPWM_H_
#define HW_EPWM_H_

/****************************************************************************************************
 * Field Definition Macros
 ****************************************************************************************************/
#define ETPWM1_TBCTL_CONFIGVALUE  ((uint16)((uint16)0U << 7U) | (uint16)((uint16)0U << 10U))
#define ETPWM1_TBPHS_CONFIGVALUE  0x00000000U
#define ETPWM1_TBPRD_CONFIGVALUE  74U
#define ETPWM1_CMPCTL_CONFIGVALUE 0x00000000U
#define ETPWM1_CMPA_CONFIGVALUE   38U
#define ETPWM1_CMPB_CONFIGVALUE   38U
#define ETPWM1_AQCTLA_CONFIGVALUE ((uint16)((uint16)ActionQual_Set << 0U) | (uint16)((uint16)ActionQual_Clear << 4U))
#define ETPWM1_AQCTLB_CONFIGVALUE ((uint16)((uint16)ActionQual_Set << 0U) | (uint16)((uint16)ActionQual_Clear << 8U))
#define ETPWM1_DBCTL_CONFIGVALUE                                                            \
    ((uint16)((uint16)0U << 5U) | (uint16)((uint16)0u << 4U) | (uint16)((uint16)0U << 3U) | \
     (uint16)((uint16)0U << 2U) | (uint16)((uint16)0U << 1U) | (uint16)((uint16)0U << 0U))
#define ETPWM1_DBRED_CONFIGVALUE 110U
#define ETPWM1_DBFED_CONFIGVALUE 110U
#define ETPWM1_TZSEL_CONFIGVALUE                                                                                   \
    (0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | \
     0x0000U)
#define ETPWM1_TZDCSEL_CONFIGVALUE 0x00000000U
#define ETPWM1_TZCTL_CONFIGVALUE   0x00000000U
#define ETPWM1_TZEINT_CONFIGVALUE  (0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U)
#define ETPWM1_ETPS_CONFIGVALUE    (1U | (uint16)((uint16)1U << 8U) | (uint16)((uint16)1U << 12U))
#define ETPWM1_PCCTL_CONFIGVALUE \
    ((uint16)((uint16)0U << 0U) | (uint16)((uint16)0U << 1U) | (uint16)((uint16)3U << 8U) | (uint16)((uint16)0U << 5U))
#define ETPWM1_DCTRIPSEL_CONFIGVALUE    0x00000000U
#define ETPWM1_DCACTL_CONFIGVALUE       0x00000000U
#define ETPWM1_DCBCTL_CONFIGVALUE       0x00000000U
#define ETPWM1_DCFCTL_CONFIGVALUE       0x00000000U
#define ETPWM1_DCCAPCTL_CONFIGVALUE     0x00000000U
#define ETPWM1_DCFWINDOW_CONFIGVALUE    0x00000000U
#define ETPWM1_DCFWINDOWCNT_CONFIGVALUE 0x00000000U

#define ETPWM2_TBCTL_CONFIGVALUE  ((uint16)((uint16)0U << 7U) | (uint16)((uint16)0U << 10U))
#define ETPWM2_TBPHS_CONFIGVALUE  0x00000000U
#define ETPWM2_TBPRD_CONFIGVALUE  74U
#define ETPWM2_CMPCTL_CONFIGVALUE 0x00000000U
#define ETPWM2_CMPA_CONFIGVALUE   38U
#define ETPWM2_CMPB_CONFIGVALUE   38U
#define ETPWM2_AQCTLA_CONFIGVALUE ((uint16)((uint16)ActionQual_Set << 0U) | (uint16)((uint16)ActionQual_Clear << 4U))
#define ETPWM2_AQCTLB_CONFIGVALUE ((uint16)((uint16)ActionQual_Set << 0U) | (uint16)((uint16)ActionQual_Clear << 8U))
#define ETPWM2_DBCTL_CONFIGVALUE                                                            \
    ((uint16)((uint16)0U << 5U) | (uint16)((uint16)0u << 4U) | (uint16)((uint16)0U << 3U) | \
     (uint16)((uint16)0U << 2U) | (uint16)((uint16)0U << 1U) | (uint16)((uint16)0U << 0U))
#define ETPWM2_DBRED_CONFIGVALUE 110U
#define ETPWM2_DBFED_CONFIGVALUE 110U
#define ETPWM2_TZSEL_CONFIGVALUE                                                                                   \
    (0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | \
     0x0000U)
#define ETPWM2_TZDCSEL_CONFIGVALUE 0x00000000U
#define ETPWM2_TZCTL_CONFIGVALUE   0x00000000U
#define ETPWM2_TZEINT_CONFIGVALUE  (0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U)
#define ETPWM2_ETSEL_CONFIGVALUE                                                                             \
    ((((uint16)NO_EVENT == 0U) ? 0x0000U : 0x0008U) | (uint16)NO_EVENT | (uint16)0x0000U | (uint16)0x0000U | \
     (uint16)((uint16)DCAEVT1 << 8U) | (uint16)((uint16)DCBEVT1 << 12U))
#define ETPWM2_ETPS_CONFIGVALUE (1U | (uint16)((uint16)1U << 8U) | (uint16)((uint16)1U << 12U))
#define ETPWM2_PCCTL_CONFIGVALUE \
    ((uint16)((uint16)0U << 0U) | (uint16)((uint16)0U << 1U) | (uint16)((uint16)3U << 8U) | (uint16)((uint16)0U << 5U))
#define ETPWM2_DCTRIPSEL_CONFIGVALUE    0x00000000U
#define ETPWM2_DCACTL_CONFIGVALUE       0x00000000U
#define ETPWM2_DCBCTL_CONFIGVALUE       0x00000000U
#define ETPWM2_DCFCTL_CONFIGVALUE       0x00000000U
#define ETPWM2_DCCAPCTL_CONFIGVALUE     0x00000000U
#define ETPWM2_DCFWINDOW_CONFIGVALUE    0x00000000U
#define ETPWM2_DCFWINDOWCNT_CONFIGVALUE 0x00000000U

#define ETPWM3_TBCTL_CONFIGVALUE  ((uint16)((uint16)0U << 7U) | (uint16)((uint16)0U << 10U))
#define ETPWM3_TBPHS_CONFIGVALUE  0x00000000U
#define ETPWM3_TBPRD_CONFIGVALUE  74U
#define ETPWM3_CMPCTL_CONFIGVALUE 0x00000000U
#define ETPWM3_CMPA_CONFIGVALUE   38U
#define ETPWM3_CMPB_CONFIGVALUE   38U
#define ETPWM3_AQCTLA_CONFIGVALUE ((uint16)((uint16)ActionQual_Set << 0U) | (uint16)((uint16)ActionQual_Clear << 4U))
#define ETPWM3_AQCTLB_CONFIGVALUE ((uint16)((uint16)ActionQual_Set << 0U) | (uint16)((uint16)ActionQual_Clear << 8U))
#define ETPWM3_DBCTL_CONFIGVALUE                                                            \
    ((uint16)((uint16)0U << 5U) | (uint16)((uint16)0u << 4U) | (uint16)((uint16)0U << 3U) | \
     (uint16)((uint16)0U << 2U) | (uint16)((uint16)0U << 1U) | (uint16)((uint16)0U << 0U))
#define ETPWM3_DBRED_CONFIGVALUE 110U
#define ETPWM3_DBFED_CONFIGVALUE 110U
#define ETPWM3_TZSEL_CONFIGVALUE                                                                                   \
    (0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | \
     0x0000U)
#define ETPWM3_TZDCSEL_CONFIGVALUE 0x00000000U
#define ETPWM3_TZCTL_CONFIGVALUE   0x00000000U
#define ETPWM3_TZEINT_CONFIGVALUE  (0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U | 0x0000U)
#define ETPWM3_ETSEL_CONFIGVALUE                                                                             \
    ((((uint16)NO_EVENT == 0U) ? 0x0000U : 0x0008U) | (uint16)NO_EVENT | (uint16)0x0000U | (uint16)0x0000U | \
     (uint16)((uint16)DCAEVT1 << 8U) | (uint16)((uint16)DCBEVT1 << 12U))
#define ETPWM3_ETPS_CONFIGVALUE (1U | (uint16)((uint16)1U << 8U) | (uint16)((uint16)1U << 12U))
#define ETPWM3_PCCTL_CONFIGVALUE \
    ((uint16)((uint16)0U << 0U) | (uint16)((uint16)0U << 1U) | (uint16)((uint16)3U << 8U) | (uint16)((uint16)0U << 5U))
#define ETPWM3_DCTRIPSEL_CONFIGVALUE    0x00000000U
#define ETPWM3_DCACTL_CONFIGVALUE       0x00000000U
#define ETPWM3_DCBCTL_CONFIGVALUE       0x00000000U
#define ETPWM3_DCFCTL_CONFIGVALUE       0x00000000U
#define ETPWM3_DCCAPCTL_CONFIGVALUE     0x00000000U
#define ETPWM3_DCFWINDOW_CONFIGVALUE    0x00000000U
#define ETPWM3_DCFWINDOWCNT_CONFIGVALUE 0x00000000U

/****************************************************************************************************
 * Register Definitions
 ****************************************************************************************************/

/* ETPWM Register Frame Definition */
/** @struct etpwmBASE
 *   @brief ETPWM Register Frame Definition
 *
 *   This type is used to access the ETPWM Registers.
 */
/** @typedef etpwmBASE_t
 *   @brief ETPWM Register Frame Type Definition
 *
 *   This type is used to access the ETPWM Registers.
 */

#if !defined(__ARM_BIG_ENDIAN)
typedef volatile struct PWM_Obj_t
{
    uint16 TBCTL;        /**<  0x0000 Time-Base Control Register*/
    uint16 TBSTS;        /**<  0x0002 Time-Base Status Register*/
    uint16 rsvd1;        /**<  0x0004 Reserved*/
    uint16 TBPHS;        /**<  0x0006 Time-Base Phase Register*/
    uint16 TBCTR;        /**<  0x0008 Time-Base Counter Register*/
    uint16 TBPRD;        /**<  0x000A Time-Base Period Register*/
    uint16 rsvd2;        /**<  0x000C Reserved*/
    uint16 CMPCTL;       /**<  0x000E Counter-Compare Control Register*/
    uint16 rsvd3;        /**<  0x0010 Reserved*/
    uint16 CMPA;         /**<  0x0012 Counter-Compare A Register*/
    uint16 CMPB;         /**<  0x0014 Counter-Compare B Register*/
    uint16 AQCTLA;       /**<  0x0016 Action-Qualifier Control Register for Output A (ETPWMxA)*/
    uint16 AQCTLB;       /**<  0x0018 Action-Qualifier Control Register for Output B (ETPWMxB)*/
    uint16 AQSFRC;       /**<  0x001A Action-Qualifier Software Force Register*/
    uint16 AQCSFRC;      /**<  0x001C Action-Qualifier Continuous S/W Force Register Set*/
    uint16 DBCTL;        /**<  0x001E Dead-Band Generator Control Register*/
    uint16 DBRED;        /**<  0x0020 Dead-Band Generator Rising Edge Delay Count Register*/
    uint16 DBFED;        /**<  0x0022 Dead-Band Generator Falling Edge Delay Count Register*/
    uint16 TZSEL;        /**<  0x0024 Trip-Zone Select Register*/
    uint16 TZDCSEL;      /**<  0x0026 Trip Zone Digital Compare Select Register*/
    uint16 TZCTL;        /**<  0x0028 Trip-Zone Control Register*/
    uint16 TZEINT;       /**<  0x002A Trip-Zone Enable Interrupt Register*/
    uint16 TZFLG;        /**<  0x002C Trip-Zone Flag Register*/
    uint16 TZCLR;        /**<  0x002E Trip-Zone Clear Register*/
    uint16 TZFRC;        /**<  0x0030 Trip-Zone Force Register*/
    uint16 ETSEL;        /**<  0x0032 Event-Trigger Selection Register*/
    uint16 ETPS;         /**<  0x0034 Event-Trigger Pre-Scale Register*/
    uint16 ETFLG;        /**<  0x0036 Event-Trigger Flag Register*/
    uint16 ETCLR;        /**<  0x0038 Event-Trigger Clear Register*/
    uint16 ETFRC;        /**<  0x003A Event-Trigger Force Register*/
    uint16 PCCTL;        /**<  0x003C PWM-Chopper Control Register*/
    uint16 rsvd4;        /**<  0x003E Reserved*/
    uint16 rsvd5[16U];   /**<  0x0040 Reserved*/
    uint16 DCTRIPSEL;    /**<  0x0060 Digital Compare Trip Select Register*/
    uint16 DCACTL;       /**<  0x0062 Digital Compare A Control Register*/
    uint16 DCBCTL;       /**<  0x0064 Digital Compare B Control Register*/
    uint16 DCFCTL;       /**<  0x0066 Digital Compare Filter Control Register*/
    uint16 DCCAPCTL;     /**<  0x0068 Digital Compare Capture Control Register*/
    uint16 DCFOFFSET;    /**<  0x006A Digital Compare Filter Offset Register*/
    uint16 DCFOFFSETCNT; /**<  0x006C Digital Compare Filter Offset Counter Register*/
    uint16 DCFWINDOW;    /**<  0x006E Digital Compare Filter Window Register*/
    uint16 DCFWINDOWCNT; /**<  0x0070 Digital Compare Filter Window Counter Register*/
    uint16 DCCAP;        /**<  0x0072 Digital Compare Counter Capture Register*/
} PWM_Obj;

#else

typedef volatile struct PWM_Obj_t
{
    uint16 TBSTS;        /**<  0x0000 Time-Base Status Register*/
    uint16 TBCTL;        /**<  0x0002 Time-Base Control Register*/
    uint16 TBPHS;        /**<  0x0004 Time-Base Phase Register*/
    uint16 rsvd1;        /**<  0x0006 Reserved*/
    uint16 TBPRD;        /**<  0x0008 Time-Base Period Register*/
    uint16 TBCTR;        /**<  0x000A Time-Base Counter Register*/
    uint16 CMPCTL;       /**<  0x000C Counter-Compare Control Register*/
    uint16 rsvd2;        /**<  0x000E Reserved*/
    uint16 CMPA;         /**<  0x0010 Counter-Compare A Register*/
    uint16 rsvd3;        /**<  0x0012 Reserved*/
    uint16 AQCTLA;       /**<  0x0014 Action-Qualifier Control Register for Output A (ETPWMxA)*/
    uint16 CMPB;         /**<  0x0016 Counter-Compare B Register*/
    uint16 AQSFRC;       /**<  0x0018 Action-Qualifier Software Force Register*/
    uint16 AQCTLB;       /**<  0x001A Action-Qualifier Control Register for Output B (ETPWMxB)*/
    uint16 DBCTL;        /**<  0x001C Dead-Band Generator Control Register*/
    uint16 AQCSFRC;      /**<  0x001E Action-Qualifier Continuous S/W Force Register Set*/
    uint16 DBFED;        /**<  0x0020 Dead-Band Generator Falling Edge Delay Count Register*/
    uint16 DBRED;        /**<  0x0022 Dead-Band Generator Rising Edge Delay Count Register*/
    uint16 TZDCSEL;      /**<  0x0024 Trip Zone Digital Compare Select Register*/
    uint16 TZSEL;        /**<  0x0026 Trip-Zone Select Register*/
    uint16 TZEINT;       /**<  0x0028 Trip-Zone Enable Interrupt Register*/
    uint16 TZCTL;        /**<  0x002A Trip-Zone Control Register*/
    uint16 TZCLR;        /**<  0x002C Trip-Zone Clear Register*/
    uint16 TZFLG;        /**<  0x002E Trip-Zone Flag Register*/
    uint16 ETSEL;        /**<  0x0030 Event-Trigger Selection Register*/
    uint16 TZFRC;        /**<  0x0032 Trip-Zone Force Register*/
    uint16 ETFLG;        /**<  0x0034 Event-Trigger Flag Register*/
    uint16 ETPS;         /**<  0x0036 Event-Trigger Pre-Scale Register*/
    uint16 ETFRC;        /**<  0x0038 Event-Trigger Force Register*/
    uint16 ETCLR;        /**<  0x003A Event-Trigger Clear Register*/
    uint16 rsvd4;        /**<  0x003C Reserved*/
    uint16 PCCTL;        /**<  0x003E PWM-Chopper Control Register*/
    uint16 rsvd5[16U];   /**<  0x0040 Reserved*/
    uint16 DCACTL;       /**<  0x0060 Digital Compare A Control Register*/
    uint16 DCTRIPSEL;    /**<  0x0062 Digital Compare Trip Select Register*/
    uint16 DCFCTL;       /**<  0x0064 Digital Compare Filter Control Register*/
    uint16 DCBCTL;       /**<  0x0066 Digital Compare B Control Register*/
    uint16 DCFOFFSET;    /**<  0x0068 Digital Compare Filter Offset Register*/
    uint16 DCCAPCTL;     /**<  0x006A Digital Compare Capture Control Register*/
    uint16 DCFWINDOW;    /**<  0x006C Digital Compare Filter Window Register*/
    uint16 DCFOFFSETCNT; /**<  0x006E Digital Compare Filter Offset Counter Register*/
    uint16 DCCAP;        /**<  0x0070 Digital Compare Counter Capture Register*/
    uint16 DCFWINDOWCNT; /**<  0x0072 Digital Compare Filter Window Counter Register*/
} PWM_Obj;

#endif

#endif /*__HW_EPWM_H__ */
