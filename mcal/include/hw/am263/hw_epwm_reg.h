/********************************************************************
 * Copyright (c) 2023 Texas Instruments Incorporated.
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
 *  
*/

#ifndef HW_EPWM_REG_H_
#define HW_EPWM_REG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************
* Hardware Region  :
**************************************************************************/
#define PWM_USE_EPWM

/**************************************************************************
* HR PWM Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint8  Resv_66[66];
    volatile uint16 HRPWR;
    volatile uint16 HRCAL;
    volatile uint16 HRPRD;
    volatile uint16 HRCNT0;
    volatile uint16 HRCNT1;
    volatile uint16 HRMSTEP;
} Pwm_ottocalRegs;

/**************************************************************************
* Register Overlay Structure
**************************************************************************/

typedef struct {
    volatile uint16 TBCTL;
    volatile uint16 TBCTL2;
    volatile uint16 RESERVED_1;
    volatile uint16 EPWMSYNCINSEL;
    volatile uint16 TBCTR;
    volatile uint16 TBSTS;
    volatile uint16 EPWMSYNCOUTEN;
    volatile uint16 TBCTL3;
    volatile uint16 CMPCTL;
    volatile uint16 CMPCTL2;
    volatile uint16 RESERVED_2[2];
    volatile uint16 DBCTL;
    volatile uint16 DBCTL2;
    volatile uint16 RESERVED_3[2];
    volatile uint16 AQCTL;
    volatile uint16 AQTSRCSEL;
    volatile uint16 RESERVED_4[2];
    volatile uint16 PCCTL;
    volatile uint16 RESERVED_5[3];
    volatile uint16 VCAPCTL;
    volatile uint16 VCNTCFG;
    volatile uint16 RESERVED_6[6];
    volatile uint16 HRCNFG;
    volatile uint16 RESERVED_7;
    volatile uint16 RESERVED_8;
    volatile uint16 RESERVED_9;
    volatile uint16 RESERVED_10;
    volatile uint16 RESERVED_11;
    volatile uint16 RESERVED_12;
    volatile uint16 HRCNFG2;
    volatile uint16 RESERVED_13[5];
    volatile uint16 HRPCTL;
    volatile uint16 TRREM;
    volatile uint16 RESERVED_14[5];
    volatile uint16 GLDCTL;
    volatile uint16 GLDCFG;
    volatile uint16 RESERVED_15[2];
    volatile uint32 EPWMXLINK;
    volatile uint32 EPWMXLINK2;
    volatile uint16 RESERVED_16;
    volatile uint16 ETEST;
    volatile uint16 EPWMREV;
    volatile uint16 HRPWMREV;
    volatile uint16 AQCTLA;
    volatile uint16 AQCTLA2;
    volatile uint16 AQCTLB;
    volatile uint16 AQCTLB2;
    volatile uint16 RESERVED_17[3];
    volatile uint16 AQSFRC;
    volatile uint16 RESERVED_18;
    volatile uint16 AQCSFRC;
    volatile uint16 RESERVED_19[6];
    volatile uint16 DBREDHR;
    volatile uint16 DBRED;
    volatile uint16 DBFEDHR;
    volatile uint16 DBFED;
    volatile uint16 RESERVED_20[12];
    volatile uint32 TBPHS;
    volatile uint16 TBPRDHR;
    volatile uint16 TBPRD;
    volatile uint16 TBPRDHRB;
    volatile uint16 RESERVED_21[5];
    volatile uint32 CMPA;
    volatile uint32 CMPB;
    volatile uint16 RESERVED_22;
    volatile uint16 CMPC;
    volatile uint16 RESERVED_23;
    volatile uint16 CMPD;
    volatile uint16 RESERVED_24[2];
    volatile uint16 GLDCTL2;
    volatile uint16 RESERVED_25[2];
    volatile uint16 SWVDELVAL;
    volatile uint16 RESERVED_26[8];
    volatile uint16 TZSEL;
    volatile uint16 TZSEL2;
    volatile uint16 TZDCSEL;
    volatile uint16 RESERVED_27;
    volatile uint16 TZCTL;
    volatile uint16 TZCTL2;
    volatile uint16 TZCTLDCA;
    volatile uint16 TZCTLDCB;
    volatile uint16 RESERVED_28[5];
    volatile uint16 TZEINT;
    volatile uint16 RESERVED_29[5];
    volatile uint16 TZFLG;
    volatile uint16 TZCBCFLG;
    volatile uint16 TZOSTFLG;
    volatile uint16 RESERVED_30;
    volatile uint16 TZCLR;
    volatile uint16 TZCBCCLR;
    volatile uint16 TZOSTCLR;
    volatile uint16 RESERVED_31;
    volatile uint16 TZFRC;
    volatile uint16 RESERVED_32;
    volatile uint16 TZTRIPOUTSEL;
    volatile uint16 RESERVED_33[6];
    volatile uint16 ETSEL;
    volatile uint16 RESERVED_34;
    volatile uint16 ETPS;
    volatile uint16 RESERVED_35;
    volatile uint16 ETFLG;
    volatile uint16 RESERVED_36;
    volatile uint16 ETCLR;
    volatile uint16 RESERVED_37;
    volatile uint16 ETFRC;
    volatile uint16 RESERVED_38;
    volatile uint16 ETINTPS;
    volatile uint16 RESERVED_39;
    volatile uint16 ETSOCPS;
    volatile uint16 RESERVED_40;
    volatile uint16 ETCNTINITCTL;
    volatile uint16 RESERVED_41;
    volatile uint16 ETCNTINIT;
    volatile uint16 RESERVED_42;
    volatile uint16 ETINTMIXEN;
    volatile uint16 RESERVED_43;
    volatile uint16 ETSOCAMIXEN;
    volatile uint16 RESERVED_44;
    volatile uint16 ETSOCBMIXEN;
    volatile uint16 RESERVED_45[5];
    volatile uint16 DCTRIPSEL;
    volatile uint16 RESERVED_46[2];
    volatile uint16 DCACTL;
    volatile uint16 DCBCTL;
    volatile uint16 RESERVED_47[2];
    volatile uint16 DCFCTL;
    volatile uint16 DCCAPCTL;
    volatile uint16 DCFOFFSET;
    volatile uint16 DCFOFFSETCNT;
    volatile uint16 DCFWINDOW;
    volatile uint16 DCFWINDOWCNT;
    volatile uint16 BLANKPULSEMIXSEL;
    volatile uint16 DCCAPMIXSEL;
    volatile uint16 DCCAP;
    volatile uint16 RESERVED_48[2];
    volatile uint16 DCAHTRIPSEL;
    volatile uint16 DCALTRIPSEL;
    volatile uint16 DCBHTRIPSEL;
    volatile uint16 DCBLTRIPSEL;
    volatile uint16 CAPCTL;
    volatile uint16 CAPGATETRIPSEL;
    volatile uint16 CAPINTRIPSEL;
    volatile uint16 CAPTRIPSEL;
    volatile uint16 RESERVED_49[28];
    volatile uint16 SPARE1;
    volatile uint16 RESERVED_50;
    volatile uint16 SPARE2;
    volatile uint16 RESERVED_51;
    volatile uint32 EPWMLOCK;
    volatile uint16 RESERVED_52;
    volatile uint16 HWVDELVAL;
    volatile uint16 VCNTVAL;
    volatile uint16 RESERVED_53;
    volatile uint8  Resv_1024[512];
    volatile uint32 XCMPCTL1;
    volatile uint32 RESERVED_54[3];
    volatile uint32 XLOADCTL;
    volatile uint32 RESERVED_55;
    volatile uint32 XLOAD;
    volatile uint32 EPWMXLINKXLOAD;
    volatile uint32 XREGSHDW1STS;
    volatile uint32 RESERVED_56;
    volatile uint32 XREGSHDW2STS;
    volatile uint32 RESERVED_57;
    volatile uint32 XREGSHDW3STS;
    volatile uint32 RESERVED_58[115];
    volatile uint32 XCMP1_ACTIVE;
    volatile uint32 XCMP2_ACTIVE;
    volatile uint32 XCMP3_ACTIVE;
    volatile uint32 XCMP4_ACTIVE;
    volatile uint32 XCMP5_ACTIVE;
    volatile uint32 XCMP6_ACTIVE;
    volatile uint32 XCMP7_ACTIVE;
    volatile uint32 XCMP8_ACTIVE;
    volatile uint32 XTBPRD_ACTIVE;
    volatile uint32 RESERVED_59[3];
    volatile uint16 XAQCTLA_ACTIVE;
    volatile uint16 XAQCTLB_ACTIVE;
    volatile uint32 RESERVED_60[4];
    volatile uint32 XMINMAX_ACTIVE;
    volatile uint32 RESERVED_61[14];
    volatile uint32 XCMP1_SHDW1;
    volatile uint32 XCMP2_SHDW1;
    volatile uint32 XCMP3_SHDW1;
    volatile uint32 XCMP4_SHDW1;
    volatile uint32 XCMP5_SHDW1;
    volatile uint32 XCMP6_SHDW1;
    volatile uint32 XCMP7_SHDW1;
    volatile uint32 XCMP8_SHDW1;
    volatile uint32 XTBPRD_SHDW1;
    volatile uint32 RESERVED_62[3];
    volatile uint16 XAQCTLA_SHDW1;
    volatile uint16 XAQCTLB_SHDW1;
    volatile uint16 RESERVED_63[3];
    volatile uint16 CMPC_SHDW1;
    volatile uint16 RESERVED_64;
    volatile uint16 CMPD_SHDW1;
    volatile uint32 RESERVED_65;
    volatile uint32 XMINMAX_SHDW1;
    volatile uint32 RESERVED_66[14];
    volatile uint32 XCMP1_SHDW2;
    volatile uint32 XCMP2_SHDW2;
    volatile uint32 XCMP3_SHDW2;
    volatile uint32 XCMP4_SHDW2;
    volatile uint32 XCMP5_SHDW2;
    volatile uint32 XCMP6_SHDW2;
    volatile uint32 XCMP7_SHDW2;
    volatile uint32 XCMP8_SHDW2;
    volatile uint32 XTBPRD_SHDW2;
    volatile uint32 RESERVED_67[3];
    volatile uint16 XAQCTLA_SHDW2;
    volatile uint16 XAQCTLB_SHDW2;
    volatile uint16 RESERVED_68[3];
    volatile uint16 CMPC_SHDW2;
    volatile uint16 RESERVED_69;
    volatile uint16 CMPD_SHDW2;
    volatile uint32 RESERVED_70;
    volatile uint32 XMINMAX_SHDW2;
    volatile uint32 RESERVED_71[14];
    volatile uint32 XCMP1_SHDW3;
    volatile uint32 XCMP2_SHDW3;
    volatile uint32 XCMP3_SHDW3;
    volatile uint32 XCMP4_SHDW3;
    volatile uint32 XCMP5_SHDW3;
    volatile uint32 XCMP6_SHDW3;
    volatile uint32 XCMP7_SHDW3;
    volatile uint32 XCMP8_SHDW3;
    volatile uint32 XTBPRD_SHDW3;
    volatile uint32 RESERVED_72[3];
    volatile uint16 XAQCTLA_SHDW3;
    volatile uint16 XAQCTLB_SHDW3;
    volatile uint16 RESERVED_73[3];
    volatile uint16 CMPC_SHDW3;
    volatile uint16 RESERVED_74;
    volatile uint16 CMPD_SHDW3;
    volatile uint32 RESERVED_75;
    volatile uint32 XMINMAX_SHDW3;
    volatile uint32 RESERVED_76[14];
    volatile uint32 DECTL;
    volatile uint32 DECOMPSEL;
    volatile uint32 DEACTCTL;
    volatile uint32 DESTS;
    volatile uint32 DEFRC;
    volatile uint32 DECLR;
    volatile uint32 RESERVED_77[2];
    volatile uint32 DEMONCNT;
    volatile uint32 DEMONCTL;
    volatile uint32 DEMONSTEP;
    volatile uint32 DEMONTHRES;
    volatile uint32 RESERVED_78[4];
    volatile uint8  Resv_3072[960];
    volatile uint32 MINDBCFG;
    volatile uint32 MINDBDLY;
    volatile uint32 RESERVED_79[6];
    volatile uint32 LUTCTLA;
    volatile uint32 LUTCTLB;
    volatile uint32 RESERVED_80[6];
} Pwm_epwmRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

#define PWM_EPWM_TBCTL                                                         (0x00000000U)
#define PWM_EPWM_TBCTL2                                                        (0x00000002U)
#define PWM_EPWM_RESERVED_1                                                    (0x00000004U)
#define PWM_EPWM_EPWMSYNCINSEL                                                 (0x00000006U)
#define PWM_EPWM_TBCTR                                                         (0x00000008U)
#define PWM_EPWM_TBSTS                                                         (0x0000000AU)
#define PWM_EPWM_EPWMSYNCOUTEN                                                 (0x0000000CU)
#define PWM_EPWM_TBCTL3                                                        (0x0000000EU)
#define PWM_EPWM_CMPCTL                                                        (0x00000010U)
#define PWM_EPWM_CMPCTL2                                                       (0x00000012U)
#define PWM_EPWM_RESERVED_2(RESERVED_2)                                        (0x00000014U+((RESERVED_2)*0x2U))
#define PWM_EPWM_DBCTL                                                         (0x00000018U)
#define PWM_EPWM_DBCTL2                                                        (0x0000001AU)
#define PWM_EPWM_RESERVED_3(RESERVED_3)                                        (0x0000001CU+((RESERVED_3)*0x2U))
#define PWM_EPWM_AQCTL                                                         (0x00000020U)
#define PWM_EPWM_AQTSRCSEL                                                     (0x00000022U)
#define PWM_EPWM_RESERVED_4(RESERVED_4)                                        (0x00000024U+((RESERVED_4)*0x2U))
#define PWM_EPWM_PCCTL                                                         (0x00000028U)
#define PWM_EPWM_RESERVED_5(RESERVED_5)                                        (0x0000002AU+((RESERVED_5)*0x2U))
#define PWM_EPWM_VCAPCTL                                                       (0x00000030U)
#define PWM_EPWM_VCNTCFG                                                       (0x00000032U)
#define PWM_EPWM_RESERVED_6(RESERVED_6)                                        (0x00000034U+((RESERVED_6)*0x2U))
#define PWM_EPWM_HRCNFG                                                        (0x00000040U)
#define PWM_EPWM_RESERVED_7                                                    (0x00000042U)
#define PWM_EPWM_RESERVED_8                                                    (0x00000044U)
#define PWM_EPWM_RESERVED_9                                                    (0x00000046U)
#define PWM_EPWM_RESERVED_10                                                   (0x00000048U)
#define PWM_EPWM_RESERVED_11                                                   (0x0000004AU)
#define PWM_EPWM_RESERVED_12                                                   (0x0000004CU)
#define PWM_EPWM_HRCNFG2                                                       (0x0000004EU)
#define PWM_EPWM_RESERVED_13(RESERVED_13)                                      (0x00000050U+((RESERVED_13)*0x2U))
#define PWM_EPWM_HRPCTL                                                        (0x0000005AU)
#define PWM_EPWM_TRREM                                                         (0x0000005CU)
#define PWM_EPWM_RESERVED_14(RESERVED_14)                                      (0x0000005EU+((RESERVED_14)*0x2U))
#define PWM_EPWM_GLDCTL                                                        (0x00000068U)
#define PWM_EPWM_GLDCFG                                                        (0x0000006AU)
#define PWM_EPWM_RESERVED_15(RESERVED_15)                                      (0x0000006CU+((RESERVED_15)*0x2U))
#define PWM_EPWM_EPWMXLINK                                                     (0x00000070U)
#define PWM_EPWM_EPWMXLINK2                                                    (0x00000074U)
#define PWM_EPWM_RESERVED_16                                                   (0x00000078U)
#define PWM_EPWM_ETEST                                                         (0x0000007AU)
#define PWM_EPWM_EPWMREV                                                       (0x0000007CU)
#define PWM_EPWM_HRPWMREV                                                      (0x0000007EU)
#define PWM_EPWM_AQCTLA                                                        (0x00000080U)
#define PWM_EPWM_AQCTLA2                                                       (0x00000082U)
#define PWM_EPWM_AQCTLB                                                        (0x00000084U)
#define PWM_EPWM_AQCTLB2                                                       (0x00000086U)
#define PWM_EPWM_RESERVED_17(RESERVED_17)                                      (0x00000088U+((RESERVED_17)*0x2U))
#define PWM_EPWM_AQSFRC                                                        (0x0000008EU)
#define PWM_EPWM_RESERVED_18                                                   (0x00000090U)
#define PWM_EPWM_AQCSFRC                                                       (0x00000092U)
#define PWM_EPWM_RESERVED_19(RESERVED_19)                                      (0x00000094U+((RESERVED_19)*0x2U))
#define PWM_EPWM_DBREDHR                                                       (0x000000A0U)
#define PWM_EPWM_DBRED                                                         (0x000000A2U)
#define PWM_EPWM_DBFEDHR                                                       (0x000000A4U)
#define PWM_EPWM_DBFED                                                         (0x000000A6U)
#define PWM_EPWM_RESERVED_20(RESERVED_20)                                      (0x000000A8U+((RESERVED_20)*0x2U))
#define PWM_EPWM_TBPHS                                                         (0x000000C0U)
#define PWM_EPWM_TBPRDHR                                                       (0x000000C4U)
#define PWM_EPWM_TBPRD                                                         (0x000000C6U)
#define PWM_EPWM_TBPRDHRB                                                      (0x000000C8U)
#define PWM_EPWM_RESERVED_21(RESERVED_21)                                      (0x000000CAU+((RESERVED_21)*0x2U))
#define PWM_EPWM_CMPA                                                          (0x000000D4U)
#define PWM_EPWM_CMPB                                                          (0x000000D8U)
#define PWM_EPWM_RESERVED_22                                                   (0x000000DCU)
#define PWM_EPWM_CMPC                                                          (0x000000DEU)
#define PWM_EPWM_RESERVED_23                                                   (0x000000E0U)
#define PWM_EPWM_CMPD                                                          (0x000000E2U)
#define PWM_EPWM_RESERVED_24(RESERVED_24)                                      (0x000000E4U+((RESERVED_24)*0x2U))
#define PWM_EPWM_GLDCTL2                                                       (0x000000E8U)
#define PWM_EPWM_RESERVED_25(RESERVED_25)                                      (0x000000EAU+((RESERVED_25)*0x2U))
#define PWM_EPWM_SWVDELVAL                                                     (0x000000EEU)
#define PWM_EPWM_RESERVED_26(RESERVED_26)                                      (0x000000F0U+((RESERVED_26)*0x2U))
#define PWM_EPWM_TZSEL                                                         (0x00000100U)
#define PWM_EPWM_TZSEL2                                                        (0x00000102U)
#define PWM_EPWM_TZDCSEL                                                       (0x00000104U)
#define PWM_EPWM_RESERVED_27                                                   (0x00000106U)
#define PWM_EPWM_TZCTL                                                         (0x00000108U)
#define PWM_EPWM_TZCTL2                                                        (0x0000010AU)
#define PWM_EPWM_TZCTLDCA                                                      (0x0000010CU)
#define PWM_EPWM_TZCTLDCB                                                      (0x0000010EU)
#define PWM_EPWM_RESERVED_28(RESERVED_28)                                      (0x00000110U+((RESERVED_28)*0x2U))
#define PWM_EPWM_TZEINT                                                        (0x0000011AU)
#define PWM_EPWM_RESERVED_29(RESERVED_29)                                      (0x0000011CU+((RESERVED_29)*0x2U))
#define PWM_EPWM_TZFLG                                                         (0x00000126U)
#define PWM_EPWM_TZCBCFLG                                                      (0x00000128U)
#define PWM_EPWM_TZOSTFLG                                                      (0x0000012AU)
#define PWM_EPWM_RESERVED_30                                                   (0x0000012CU)
#define PWM_EPWM_TZCLR                                                         (0x0000012EU)
#define PWM_EPWM_TZCBCCLR                                                      (0x00000130U)
#define PWM_EPWM_TZOSTCLR                                                      (0x00000132U)
#define PWM_EPWM_RESERVED_31                                                   (0x00000134U)
#define PWM_EPWM_TZFRC                                                         (0x00000136U)
#define PWM_EPWM_RESERVED_32                                                   (0x00000138U)
#define PWM_EPWM_TZTRIPOUTSEL                                                  (0x0000013AU)
#define PWM_EPWM_RESERVED_33(RESERVED_33)                                      (0x0000013CU+((RESERVED_33)*0x2U))
#define PWM_EPWM_ETSEL                                                         (0x00000148U)
#define PWM_EPWM_RESERVED_34                                                   (0x0000014AU)
#define PWM_EPWM_ETPS                                                          (0x0000014CU)
#define PWM_EPWM_RESERVED_35                                                   (0x0000014EU)
#define PWM_EPWM_ETFLG                                                         (0x00000150U)
#define PWM_EPWM_RESERVED_36                                                   (0x00000152U)
#define PWM_EPWM_ETCLR                                                         (0x00000154U)
#define PWM_EPWM_RESERVED_37                                                   (0x00000156U)
#define PWM_EPWM_ETFRC                                                         (0x00000158U)
#define PWM_EPWM_RESERVED_38                                                   (0x0000015AU)
#define PWM_EPWM_ETINTPS                                                       (0x0000015CU)
#define PWM_EPWM_RESERVED_39                                                   (0x0000015EU)
#define PWM_EPWM_ETSOCPS                                                       (0x00000160U)
#define PWM_EPWM_RESERVED_40                                                   (0x00000162U)
#define PWM_EPWM_ETCNTINITCTL                                                  (0x00000164U)
#define PWM_EPWM_RESERVED_41                                                   (0x00000166U)
#define PWM_EPWM_ETCNTINIT                                                     (0x00000168U)
#define PWM_EPWM_RESERVED_42                                                   (0x0000016AU)
#define PWM_EPWM_ETINTMIXEN                                                    (0x0000016CU)
#define PWM_EPWM_RESERVED_43                                                   (0x0000016EU)
#define PWM_EPWM_ETSOCAMIXEN                                                   (0x00000170U)
#define PWM_EPWM_RESERVED_44                                                   (0x00000172U)
#define PWM_EPWM_ETSOCBMIXEN                                                   (0x00000174U)
#define PWM_EPWM_RESERVED_45(RESERVED_45)                                      (0x00000176U+((RESERVED_45)*0x2U))
#define PWM_EPWM_DCTRIPSEL                                                     (0x00000180U)
#define PWM_EPWM_RESERVED_46(RESERVED_46)                                      (0x00000182U+((RESERVED_46)*0x2U))
#define PWM_EPWM_DCACTL                                                        (0x00000186U)
#define PWM_EPWM_DCBCTL                                                        (0x00000188U)
#define PWM_EPWM_RESERVED_47(RESERVED_47)                                      (0x0000018AU+((RESERVED_47)*0x2U))
#define PWM_EPWM_DCFCTL                                                        (0x0000018EU)
#define PWM_EPWM_DCCAPCTL                                                      (0x00000190U)
#define PWM_EPWM_DCFOFFSET                                                     (0x00000192U)
#define PWM_EPWM_DCFOFFSETCNT                                                  (0x00000194U)
#define PWM_EPWM_DCFWINDOW                                                     (0x00000196U)
#define PWM_EPWM_DCFWINDOWCNT                                                  (0x00000198U)
#define PWM_EPWM_BLANKPULSEMIXSEL                                              (0x0000019AU)
#define PWM_EPWM_DCCAPMIXSEL                                                   (0x0000019CU)
#define PWM_EPWM_DCCAP                                                         (0x0000019EU)
#define PWM_EPWM_RESERVED_48(RESERVED_48)                                      (0x000001A0U+((RESERVED_48)*0x2U))
#define PWM_EPWM_DCAHTRIPSEL                                                   (0x000001A4U)
#define PWM_EPWM_DCALTRIPSEL                                                   (0x000001A6U)
#define PWM_EPWM_DCBHTRIPSEL                                                   (0x000001A8U)
#define PWM_EPWM_DCBLTRIPSEL                                                   (0x000001AAU)
#define PWM_EPWM_CAPCTL                                                        (0x000001ACU)
#define PWM_EPWM_CAPGATETRIPSEL                                                (0x000001AEU)
#define PWM_EPWM_CAPINTRIPSEL                                                  (0x000001B0U)
#define PWM_EPWM_CAPTRIPSEL                                                    (0x000001B2U)
#define PWM_EPWM_RESERVED_49(RESERVED_49)                                      (0x000001B4U+((RESERVED_49)*0x2U))
#define PWM_EPWM_SPARE1                                                        (0x000001ECU)
#define PWM_EPWM_RESERVED_50                                                   (0x000001EEU)
#define PWM_EPWM_SPARE2                                                        (0x000001F0U)
#define PWM_EPWM_RESERVED_51                                                   (0x000001F2U)
#define PWM_EPWM_EPWMLOCK                                                      (0x000001F4U)
#define PWM_EPWM_RESERVED_52                                                   (0x000001F8U)
#define PWM_EPWM_HWVDELVAL                                                     (0x000001FAU)
#define PWM_EPWM_VCNTVAL                                                       (0x000001FCU)
#define PWM_EPWM_RESERVED_53                                                   (0x000001FEU)
#define PWM_EPWM_XCMPCTL1                                                      (0x00000400U)
#define PWM_EPWM_RESERVED_54(RESERVED_54)                                      (0x00000404U+((RESERVED_54)*0x4U))
#define PWM_EPWM_XLOADCTL                                                      (0x00000410U)
#define PWM_EPWM_RESERVED_55                                                   (0x00000414U)
#define PWM_EPWM_XLOAD                                                         (0x00000418U)
#define PWM_EPWM_EPWMXLINKXLOAD                                                (0x0000041CU)
#define PWM_EPWM_XREGSHDW1STS                                                  (0x00000420U)
#define PWM_EPWM_RESERVED_56                                                   (0x00000424U)
#define PWM_EPWM_XREGSHDW2STS                                                  (0x00000428U)
#define PWM_EPWM_RESERVED_57                                                   (0x0000042CU)
#define PWM_EPWM_XREGSHDW3STS                                                  (0x00000430U)
#define PWM_EPWM_RESERVED_58(RESERVED_58)                                      (0x00000434U+((RESERVED_58)*0x4U))
#define PWM_EPWM_XCMP1_ACTIVE                                                  (0x00000600U)
#define PWM_EPWM_XCMP2_ACTIVE                                                  (0x00000604U)
#define PWM_EPWM_XCMP3_ACTIVE                                                  (0x00000608U)
#define PWM_EPWM_XCMP4_ACTIVE                                                  (0x0000060CU)
#define PWM_EPWM_XCMP5_ACTIVE                                                  (0x00000610U)
#define PWM_EPWM_XCMP6_ACTIVE                                                  (0x00000614U)
#define PWM_EPWM_XCMP7_ACTIVE                                                  (0x00000618U)
#define PWM_EPWM_XCMP8_ACTIVE                                                  (0x0000061CU)
#define PWM_EPWM_XTBPRD_ACTIVE                                                 (0x00000620U)
#define PWM_EPWM_RESERVED_59(RESERVED_59)                                      (0x00000624U+((RESERVED_59)*0x4U))
#define PWM_EPWM_XAQCTLA_ACTIVE                                                (0x00000630U)
#define PWM_EPWM_XAQCTLB_ACTIVE                                                (0x00000632U)
#define PWM_EPWM_RESERVED_60(RESERVED_60)                                      (0x00000634U+((RESERVED_60)*0x4U))
#define PWM_EPWM_XMINMAX_ACTIVE                                                (0x00000644U)
#define PWM_EPWM_RESERVED_61(RESERVED_61)                                      (0x00000648U+((RESERVED_61)*0x4U))
#define PWM_EPWM_XCMP1_SHDW1                                                   (0x00000680U)
#define PWM_EPWM_XCMP2_SHDW1                                                   (0x00000684U)
#define PWM_EPWM_XCMP3_SHDW1                                                   (0x00000688U)
#define PWM_EPWM_XCMP4_SHDW1                                                   (0x0000068CU)
#define PWM_EPWM_XCMP5_SHDW1                                                   (0x00000690U)
#define PWM_EPWM_XCMP6_SHDW1                                                   (0x00000694U)
#define PWM_EPWM_XCMP7_SHDW1                                                   (0x00000698U)
#define PWM_EPWM_XCMP8_SHDW1                                                   (0x0000069CU)
#define PWM_EPWM_XTBPRD_SHDW1                                                  (0x000006A0U)
#define PWM_EPWM_RESERVED_62(RESERVED_62)                                      (0x000006A4U+((RESERVED_62)*0x4U))
#define PWM_EPWM_XAQCTLA_SHDW1                                                 (0x000006B0U)
#define PWM_EPWM_XAQCTLB_SHDW1                                                 (0x000006B2U)
#define PWM_EPWM_RESERVED_63(RESERVED_63)                                      (0x000006B4U+((RESERVED_63)*0x2U))
#define PWM_EPWM_CMPC_SHDW1                                                    (0x000006BAU)
#define PWM_EPWM_RESERVED_64                                                   (0x000006BCU)
#define PWM_EPWM_CMPD_SHDW1                                                    (0x000006BEU)
#define PWM_EPWM_RESERVED_65                                                   (0x000006C0U)
#define PWM_EPWM_XMINMAX_SHDW1                                                 (0x000006C4U)
#define PWM_EPWM_RESERVED_66(RESERVED_66)                                      (0x000006C8U+((RESERVED_66)*0x4U))
#define PWM_EPWM_XCMP1_SHDW2                                                   (0x00000700U)
#define PWM_EPWM_XCMP2_SHDW2                                                   (0x00000704U)
#define PWM_EPWM_XCMP3_SHDW2                                                   (0x00000708U)
#define PWM_EPWM_XCMP4_SHDW2                                                   (0x0000070CU)
#define PWM_EPWM_XCMP5_SHDW2                                                   (0x00000710U)
#define PWM_EPWM_XCMP6_SHDW2                                                   (0x00000714U)
#define PWM_EPWM_XCMP7_SHDW2                                                   (0x00000718U)
#define PWM_EPWM_XCMP8_SHDW2                                                   (0x0000071CU)
#define PWM_EPWM_XTBPRD_SHDW2                                                  (0x00000720U)
#define PWM_EPWM_RESERVED_67(RESERVED_67)                                      (0x00000724U+((RESERVED_67)*0x4U))
#define PWM_EPWM_XAQCTLA_SHDW2                                                 (0x00000730U)
#define PWM_EPWM_XAQCTLB_SHDW2                                                 (0x00000732U)
#define PWM_EPWM_RESERVED_68(RESERVED_68)                                      (0x00000734U+((RESERVED_68)*0x2U))
#define PWM_EPWM_CMPC_SHDW2                                                    (0x0000073AU)
#define PWM_EPWM_RESERVED_69                                                   (0x0000073CU)
#define PWM_EPWM_CMPD_SHDW2                                                    (0x0000073EU)
#define PWM_EPWM_RESERVED_70                                                   (0x00000740U)
#define PWM_EPWM_XMINMAX_SHDW2                                                 (0x00000744U)
#define PWM_EPWM_RESERVED_71(RESERVED_71)                                      (0x00000748U+((RESERVED_71)*0x4U))
#define PWM_EPWM_XCMP1_SHDW3                                                   (0x00000780U)
#define PWM_EPWM_XCMP2_SHDW3                                                   (0x00000784U)
#define PWM_EPWM_XCMP3_SHDW3                                                   (0x00000788U)
#define PWM_EPWM_XCMP4_SHDW3                                                   (0x0000078CU)
#define PWM_EPWM_XCMP5_SHDW3                                                   (0x00000790U)
#define PWM_EPWM_XCMP6_SHDW3                                                   (0x00000794U)
#define PWM_EPWM_XCMP7_SHDW3                                                   (0x00000798U)
#define PWM_EPWM_XCMP8_SHDW3                                                   (0x0000079CU)
#define PWM_EPWM_XTBPRD_SHDW3                                                  (0x000007A0U)
#define PWM_EPWM_RESERVED_72(RESERVED_72)                                      (0x000007A4U+((RESERVED_72)*0x4U))
#define PWM_EPWM_XAQCTLA_SHDW3                                                 (0x000007B0U)
#define PWM_EPWM_XAQCTLB_SHDW3                                                 (0x000007B2U)
#define PWM_EPWM_RESERVED_73(RESERVED_73)                                      (0x000007B4U+((RESERVED_73)*0x2U))
#define PWM_EPWM_CMPC_SHDW3                                                    (0x000007BAU)
#define PWM_EPWM_RESERVED_74                                                   (0x000007BCU)
#define PWM_EPWM_CMPD_SHDW3                                                    (0x000007BEU)
#define PWM_EPWM_RESERVED_75                                                   (0x000007C0U)
#define PWM_EPWM_XMINMAX_SHDW3                                                 (0x000007C4U)
#define PWM_EPWM_RESERVED_76(RESERVED_76)                                      (0x000007C8U+((RESERVED_76)*0x4U))
#define PWM_EPWM_DECTL                                                         (0x00000800U)
#define PWM_EPWM_DECOMPSEL                                                     (0x00000804U)
#define PWM_EPWM_DEACTCTL                                                      (0x00000808U)
#define PWM_EPWM_DESTS                                                         (0x0000080CU)
#define PWM_EPWM_DEFRC                                                         (0x00000810U)
#define PWM_EPWM_DECLR                                                         (0x00000814U)
#define PWM_EPWM_RESERVED_77(RESERVED_77)                                      (0x00000818U+((RESERVED_77)*0x4U))
#define PWM_EPWM_DEMONCNT                                                      (0x00000820U)
#define PWM_EPWM_DEMONCTL                                                      (0x00000824U)
#define PWM_EPWM_DEMONSTEP                                                     (0x00000828U)
#define PWM_EPWM_DEMONTHRES                                                    (0x0000082CU)
#define PWM_EPWM_RESERVED_78(RESERVED_78)                                      (0x00000830U+((RESERVED_78)*0x4U))
#define PWM_EPWM_MINDBCFG                                                      (0x00000C00U)
#define PWM_EPWM_MINDBDLY                                                      (0x00000C04U)
#define PWM_EPWM_RESERVED_79(RESERVED_79)                                      (0x00000C08U+((RESERVED_79)*0x4U))
#define PWM_EPWM_LUTCTLA                                                       (0x00000C20U)
#define PWM_EPWM_LUTCTLB                                                       (0x00000C24U)
#define PWM_EPWM_RESERVED_80(RESERVED_80)                                      (0x00000C28U+((RESERVED_80)*0x4U))

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* TBCTL */

#define PWM_EPWM_TBCTL_CTRMODE_MASK                                            (0x0003U)
#define PWM_EPWM_TBCTL_CTRMODE_SHIFT                                           (0x0000U)
#define PWM_EPWM_TBCTL_CTRMODE_RESETVAL                                        (0x0003U)
#define PWM_EPWM_TBCTL_CTRMODE_MAX                                             (0x0003U)

#define PWM_EPWM_TBCTL_PHSEN_MASK                                              (0x0004U)
#define PWM_EPWM_TBCTL_PHSEN_SHIFT                                             (0x0002U)
#define PWM_EPWM_TBCTL_PHSEN_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TBCTL_PHSEN_MAX                                               (0x0001U)

#define PWM_EPWM_TBCTL_PRDLD_MASK                                              (0x0008U)
#define PWM_EPWM_TBCTL_PRDLD_SHIFT                                             (0x0003U)
#define PWM_EPWM_TBCTL_PRDLD_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TBCTL_PRDLD_MAX                                               (0x0001U)

#define PWM_EPWM_TBCTL_RESERVED_1_MASK                                         (0x0030U)
#define PWM_EPWM_TBCTL_RESERVED_1_SHIFT                                        (0x0004U)
#define PWM_EPWM_TBCTL_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TBCTL_RESERVED_1_MAX                                          (0x0003U)

#define PWM_EPWM_TBCTL_SWFSYNC_MASK                                            (0x0040U)
#define PWM_EPWM_TBCTL_SWFSYNC_SHIFT                                           (0x0006U)
#define PWM_EPWM_TBCTL_SWFSYNC_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TBCTL_SWFSYNC_MAX                                             (0x0001U)

#define PWM_EPWM_TBCTL_HSPCLKDIV_MASK                                          (0x0380U)
#define PWM_EPWM_TBCTL_HSPCLKDIV_SHIFT                                         (0x0007U)
#define PWM_EPWM_TBCTL_HSPCLKDIV_RESETVAL                                      (0x0001U)
#define PWM_EPWM_TBCTL_HSPCLKDIV_MAX                                           (0x0007U)

#define PWM_EPWM_TBCTL_CLKDIV_MASK                                             (0x1C00U)
#define PWM_EPWM_TBCTL_CLKDIV_SHIFT                                            (0x000AU)
#define PWM_EPWM_TBCTL_CLKDIV_RESETVAL                                         (0x0000U)
#define PWM_EPWM_TBCTL_CLKDIV_MAX                                              (0x0007U)

#define PWM_EPWM_TBCTL_PHSDIR_MASK                                             (0x2000U)
#define PWM_EPWM_TBCTL_PHSDIR_SHIFT                                            (0x000DU)
#define PWM_EPWM_TBCTL_PHSDIR_RESETVAL                                         (0x0000U)
#define PWM_EPWM_TBCTL_PHSDIR_MAX                                              (0x0001U)

#define PWM_EPWM_TBCTL_FREE_SOFT_MASK                                          (0xC000U)
#define PWM_EPWM_TBCTL_FREE_SOFT_SHIFT                                         (0x000EU)
#define PWM_EPWM_TBCTL_FREE_SOFT_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TBCTL_FREE_SOFT_MAX                                           (0x0003U)

#define PWM_EPWM_TBCTL_RESETVAL                                                (0x0083U)

/* TBCTL2 */

#define PWM_EPWM_TBCTL2_RESERVED_1_MASK                                        (0x001FU)
#define PWM_EPWM_TBCTL2_RESERVED_1_SHIFT                                       (0x0000U)
#define PWM_EPWM_TBCTL2_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TBCTL2_RESERVED_1_MAX                                         (0x001FU)

#define PWM_EPWM_TBCTL2_SELFCLRTRREM_MASK                                      (0x0020U)
#define PWM_EPWM_TBCTL2_SELFCLRTRREM_SHIFT                                     (0x0005U)
#define PWM_EPWM_TBCTL2_SELFCLRTRREM_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TBCTL2_SELFCLRTRREM_MAX                                       (0x0001U)

#define PWM_EPWM_TBCTL2_OSHTSYNCMODE_MASK                                      (0x0040U)
#define PWM_EPWM_TBCTL2_OSHTSYNCMODE_SHIFT                                     (0x0006U)
#define PWM_EPWM_TBCTL2_OSHTSYNCMODE_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TBCTL2_OSHTSYNCMODE_MAX                                       (0x0001U)

#define PWM_EPWM_TBCTL2_OSHTSYNC_MASK                                          (0x0080U)
#define PWM_EPWM_TBCTL2_OSHTSYNC_SHIFT                                         (0x0007U)
#define PWM_EPWM_TBCTL2_OSHTSYNC_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TBCTL2_OSHTSYNC_MAX                                           (0x0001U)

#define PWM_EPWM_TBCTL2_RESERVED_2_MASK                                        (0x0F00U)
#define PWM_EPWM_TBCTL2_RESERVED_2_SHIFT                                       (0x0008U)
#define PWM_EPWM_TBCTL2_RESERVED_2_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TBCTL2_RESERVED_2_MAX                                         (0x000FU)

#define PWM_EPWM_TBCTL2_RESERVED_3_MASK                                        (0x3000U)
#define PWM_EPWM_TBCTL2_RESERVED_3_SHIFT                                       (0x000CU)
#define PWM_EPWM_TBCTL2_RESERVED_3_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TBCTL2_RESERVED_3_MAX                                         (0x0003U)

#define PWM_EPWM_TBCTL2_PRDLDSYNC_MASK                                         (0xC000U)
#define PWM_EPWM_TBCTL2_PRDLDSYNC_SHIFT                                        (0x000EU)
#define PWM_EPWM_TBCTL2_PRDLDSYNC_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TBCTL2_PRDLDSYNC_MAX                                          (0x0003U)

#define PWM_EPWM_TBCTL2_RESETVAL                                               (0x0000U)

/* RESERVED_1 */

#define PWM_EPWM_RESERVED_1_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_1_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_1_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_1_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_1_RESETVAL                                           (0x0000U)

/* EPWMSYNCINSEL */

#define PWM_EPWM_EPWMSYNCINSEL_SEL_MASK                                        (0x007FU)
#define PWM_EPWM_EPWMSYNCINSEL_SEL_SHIFT                                       (0x0000U)
#define PWM_EPWM_EPWMSYNCINSEL_SEL_RESETVAL                                    (0x0001U)
#define PWM_EPWM_EPWMSYNCINSEL_SEL_MAX                                         (0x007FU)

#define PWM_EPWM_EPWMSYNCINSEL_RESERVED_1_MASK                                 (0xFF80U)
#define PWM_EPWM_EPWMSYNCINSEL_RESERVED_1_SHIFT                                (0x0007U)
#define PWM_EPWM_EPWMSYNCINSEL_RESERVED_1_RESETVAL                             (0x0000U)
#define PWM_EPWM_EPWMSYNCINSEL_RESERVED_1_MAX                                  (0x01FFU)

#define PWM_EPWM_EPWMSYNCINSEL_RESETVAL                                        (0x0001U)

/* TBCTR */

#define PWM_EPWM_TBCTR_TBCTR_MASK                                              (0xFFFFU)
#define PWM_EPWM_TBCTR_TBCTR_SHIFT                                             (0x0000U)
#define PWM_EPWM_TBCTR_TBCTR_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TBCTR_TBCTR_MAX                                               (0xFFFFU)

#define PWM_EPWM_TBCTR_RESETVAL                                                (0x0000U)

/* TBSTS */

#define PWM_EPWM_TBSTS_CTRDIR_MASK                                             (0x0001U)
#define PWM_EPWM_TBSTS_CTRDIR_SHIFT                                            (0x0000U)
#define PWM_EPWM_TBSTS_CTRDIR_RESETVAL                                         (0x0001U)
#define PWM_EPWM_TBSTS_CTRDIR_MAX                                              (0x0001U)

#define PWM_EPWM_TBSTS_SYNCI_MASK                                              (0x0002U)
#define PWM_EPWM_TBSTS_SYNCI_SHIFT                                             (0x0001U)
#define PWM_EPWM_TBSTS_SYNCI_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TBSTS_SYNCI_MAX                                               (0x0001U)

#define PWM_EPWM_TBSTS_CTRMAX_MASK                                             (0x0004U)
#define PWM_EPWM_TBSTS_CTRMAX_SHIFT                                            (0x0002U)
#define PWM_EPWM_TBSTS_CTRMAX_RESETVAL                                         (0x0000U)
#define PWM_EPWM_TBSTS_CTRMAX_MAX                                              (0x0001U)

#define PWM_EPWM_TBSTS_RESERVED_1_MASK                                         (0xFFF8U)
#define PWM_EPWM_TBSTS_RESERVED_1_SHIFT                                        (0x0003U)
#define PWM_EPWM_TBSTS_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TBSTS_RESERVED_1_MAX                                          (0x1FFFU)

#define PWM_EPWM_TBSTS_RESETVAL                                                (0x0001U)

/* EPWMSYNCOUTEN */

#define PWM_EPWM_EPWMSYNCOUTEN_SWEN_MASK                                       (0x0001U)
#define PWM_EPWM_EPWMSYNCOUTEN_SWEN_SHIFT                                      (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_SWEN_RESETVAL                                   (0x0001U)
#define PWM_EPWM_EPWMSYNCOUTEN_SWEN_MAX                                        (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_ZEROEN_MASK                                     (0x0002U)
#define PWM_EPWM_EPWMSYNCOUTEN_ZEROEN_SHIFT                                    (0x0001U)
#define PWM_EPWM_EPWMSYNCOUTEN_ZEROEN_RESETVAL                                 (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_ZEROEN_MAX                                      (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_CMPBEN_MASK                                     (0x0004U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPBEN_SHIFT                                    (0x0002U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPBEN_RESETVAL                                 (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPBEN_MAX                                      (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_CMPCEN_MASK                                     (0x0008U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPCEN_SHIFT                                    (0x0003U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPCEN_RESETVAL                                 (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPCEN_MAX                                      (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_CMPDEN_MASK                                     (0x0010U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPDEN_SHIFT                                    (0x0004U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPDEN_RESETVAL                                 (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_CMPDEN_MAX                                      (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_DCAEVT1EN_MASK                                  (0x0020U)
#define PWM_EPWM_EPWMSYNCOUTEN_DCAEVT1EN_SHIFT                                 (0x0005U)
#define PWM_EPWM_EPWMSYNCOUTEN_DCAEVT1EN_RESETVAL                              (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_DCAEVT1EN_MAX                                   (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_DCBEVT1EN_MASK                                  (0x0040U)
#define PWM_EPWM_EPWMSYNCOUTEN_DCBEVT1EN_SHIFT                                 (0x0006U)
#define PWM_EPWM_EPWMSYNCOUTEN_DCBEVT1EN_RESETVAL                              (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_DCBEVT1EN_MAX                                   (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_1_MASK                                 (0x0080U)
#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_1_SHIFT                                (0x0007U)
#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_1_RESETVAL                             (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_1_MAX                                  (0x0001U)

#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_2_MASK                                 (0xFF00U)
#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_2_SHIFT                                (0x0008U)
#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_2_RESETVAL                             (0x0000U)
#define PWM_EPWM_EPWMSYNCOUTEN_RESERVED_2_MAX                                  (0x00FFU)

#define PWM_EPWM_EPWMSYNCOUTEN_RESETVAL                                        (0x0001U)

/* TBCTL3 */

#define PWM_EPWM_TBCTL3_OSSFRCEN_MASK                                          (0x0001U)
#define PWM_EPWM_TBCTL3_OSSFRCEN_SHIFT                                         (0x0000U)
#define PWM_EPWM_TBCTL3_OSSFRCEN_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TBCTL3_OSSFRCEN_MAX                                           (0x0001U)

#define PWM_EPWM_TBCTL3_RESERVED_1_MASK                                        (0xFFFEU)
#define PWM_EPWM_TBCTL3_RESERVED_1_SHIFT                                       (0x0001U)
#define PWM_EPWM_TBCTL3_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TBCTL3_RESERVED_1_MAX                                         (0x7FFFU)

#define PWM_EPWM_TBCTL3_RESETVAL                                               (0x0000U)

/* CMPCTL */

#define PWM_EPWM_CMPCTL_LOADAMODE_MASK                                         (0x0003U)
#define PWM_EPWM_CMPCTL_LOADAMODE_SHIFT                                        (0x0000U)
#define PWM_EPWM_CMPCTL_LOADAMODE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_LOADAMODE_MAX                                          (0x0003U)

#define PWM_EPWM_CMPCTL_LOADBMODE_MASK                                         (0x000CU)
#define PWM_EPWM_CMPCTL_LOADBMODE_SHIFT                                        (0x0002U)
#define PWM_EPWM_CMPCTL_LOADBMODE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_LOADBMODE_MAX                                          (0x0003U)

#define PWM_EPWM_CMPCTL_SHDWAMODE_MASK                                         (0x0010U)
#define PWM_EPWM_CMPCTL_SHDWAMODE_SHIFT                                        (0x0004U)
#define PWM_EPWM_CMPCTL_SHDWAMODE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_SHDWAMODE_MAX                                          (0x0001U)

#define PWM_EPWM_CMPCTL_RESERVED_1_MASK                                        (0x0020U)
#define PWM_EPWM_CMPCTL_RESERVED_1_SHIFT                                       (0x0005U)
#define PWM_EPWM_CMPCTL_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL_RESERVED_1_MAX                                         (0x0001U)

#define PWM_EPWM_CMPCTL_SHDWBMODE_MASK                                         (0x0040U)
#define PWM_EPWM_CMPCTL_SHDWBMODE_SHIFT                                        (0x0006U)
#define PWM_EPWM_CMPCTL_SHDWBMODE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_SHDWBMODE_MAX                                          (0x0001U)

#define PWM_EPWM_CMPCTL_RESERVED_2_MASK                                        (0x0080U)
#define PWM_EPWM_CMPCTL_RESERVED_2_SHIFT                                       (0x0007U)
#define PWM_EPWM_CMPCTL_RESERVED_2_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL_RESERVED_2_MAX                                         (0x0001U)

#define PWM_EPWM_CMPCTL_SHDWAFULL_MASK                                         (0x0100U)
#define PWM_EPWM_CMPCTL_SHDWAFULL_SHIFT                                        (0x0008U)
#define PWM_EPWM_CMPCTL_SHDWAFULL_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_SHDWAFULL_MAX                                          (0x0001U)

#define PWM_EPWM_CMPCTL_SHDWBFULL_MASK                                         (0x0200U)
#define PWM_EPWM_CMPCTL_SHDWBFULL_SHIFT                                        (0x0009U)
#define PWM_EPWM_CMPCTL_SHDWBFULL_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_SHDWBFULL_MAX                                          (0x0001U)

#define PWM_EPWM_CMPCTL_LOADASYNC_MASK                                         (0x0C00U)
#define PWM_EPWM_CMPCTL_LOADASYNC_SHIFT                                        (0x000AU)
#define PWM_EPWM_CMPCTL_LOADASYNC_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_LOADASYNC_MAX                                          (0x0003U)

#define PWM_EPWM_CMPCTL_LOADBSYNC_MASK                                         (0x3000U)
#define PWM_EPWM_CMPCTL_LOADBSYNC_SHIFT                                        (0x000CU)
#define PWM_EPWM_CMPCTL_LOADBSYNC_RESETVAL                                     (0x0000U)
#define PWM_EPWM_CMPCTL_LOADBSYNC_MAX                                          (0x0003U)

#define PWM_EPWM_CMPCTL_RESERVED_3_MASK                                        (0x4000U)
#define PWM_EPWM_CMPCTL_RESERVED_3_SHIFT                                       (0x000EU)
#define PWM_EPWM_CMPCTL_RESERVED_3_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL_RESERVED_3_MAX                                         (0x0001U)

#define PWM_EPWM_CMPCTL_LINKDUTYHR_MASK                                        (0x8000U)
#define PWM_EPWM_CMPCTL_LINKDUTYHR_SHIFT                                       (0x000FU)
#define PWM_EPWM_CMPCTL_LINKDUTYHR_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL_LINKDUTYHR_MAX                                         (0x0001U)

#define PWM_EPWM_CMPCTL_RESETVAL                                               (0x0000U)

/* CMPCTL2 */

#define PWM_EPWM_CMPCTL2_LOADCMODE_MASK                                        (0x0003U)
#define PWM_EPWM_CMPCTL2_LOADCMODE_SHIFT                                       (0x0000U)
#define PWM_EPWM_CMPCTL2_LOADCMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL2_LOADCMODE_MAX                                         (0x0003U)

#define PWM_EPWM_CMPCTL2_LOADDMODE_MASK                                        (0x000CU)
#define PWM_EPWM_CMPCTL2_LOADDMODE_SHIFT                                       (0x0002U)
#define PWM_EPWM_CMPCTL2_LOADDMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL2_LOADDMODE_MAX                                         (0x0003U)

#define PWM_EPWM_CMPCTL2_SHDWCMODE_MASK                                        (0x0010U)
#define PWM_EPWM_CMPCTL2_SHDWCMODE_SHIFT                                       (0x0004U)
#define PWM_EPWM_CMPCTL2_SHDWCMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL2_SHDWCMODE_MAX                                         (0x0001U)

#define PWM_EPWM_CMPCTL2_RESERVED_1_MASK                                       (0x0020U)
#define PWM_EPWM_CMPCTL2_RESERVED_1_SHIFT                                      (0x0005U)
#define PWM_EPWM_CMPCTL2_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_CMPCTL2_RESERVED_1_MAX                                        (0x0001U)

#define PWM_EPWM_CMPCTL2_SHDWDMODE_MASK                                        (0x0040U)
#define PWM_EPWM_CMPCTL2_SHDWDMODE_SHIFT                                       (0x0006U)
#define PWM_EPWM_CMPCTL2_SHDWDMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL2_SHDWDMODE_MAX                                         (0x0001U)

#define PWM_EPWM_CMPCTL2_RESERVED_2_MASK                                       (0x0380U)
#define PWM_EPWM_CMPCTL2_RESERVED_2_SHIFT                                      (0x0007U)
#define PWM_EPWM_CMPCTL2_RESERVED_2_RESETVAL                                   (0x0000U)
#define PWM_EPWM_CMPCTL2_RESERVED_2_MAX                                        (0x0007U)

#define PWM_EPWM_CMPCTL2_LOADCSYNC_MASK                                        (0x0C00U)
#define PWM_EPWM_CMPCTL2_LOADCSYNC_SHIFT                                       (0x000AU)
#define PWM_EPWM_CMPCTL2_LOADCSYNC_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL2_LOADCSYNC_MAX                                         (0x0003U)

#define PWM_EPWM_CMPCTL2_LOADDSYNC_MASK                                        (0x3000U)
#define PWM_EPWM_CMPCTL2_LOADDSYNC_SHIFT                                       (0x000CU)
#define PWM_EPWM_CMPCTL2_LOADDSYNC_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CMPCTL2_LOADDSYNC_MAX                                         (0x0003U)

#define PWM_EPWM_CMPCTL2_RESERVED_3_MASK                                       (0xC000U)
#define PWM_EPWM_CMPCTL2_RESERVED_3_SHIFT                                      (0x000EU)
#define PWM_EPWM_CMPCTL2_RESERVED_3_RESETVAL                                   (0x0000U)
#define PWM_EPWM_CMPCTL2_RESERVED_3_MAX                                        (0x0003U)

#define PWM_EPWM_CMPCTL2_RESETVAL                                              (0x0000U)

/* RESERVED_2 */

#define PWM_EPWM_RESERVED_2_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_2_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_2_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_2_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_2_RESETVAL                                           (0x0000U)

/* DBCTL */

#define PWM_EPWM_DBCTL_OUT_MODE_MASK                                           (0x0003U)
#define PWM_EPWM_DBCTL_OUT_MODE_SHIFT                                          (0x0000U)
#define PWM_EPWM_DBCTL_OUT_MODE_RESETVAL                                       (0x0000U)
#define PWM_EPWM_DBCTL_OUT_MODE_MAX                                            (0x0003U)

#define PWM_EPWM_DBCTL_POLSEL_MASK                                             (0x000CU)
#define PWM_EPWM_DBCTL_POLSEL_SHIFT                                            (0x0002U)
#define PWM_EPWM_DBCTL_POLSEL_RESETVAL                                         (0x0000U)
#define PWM_EPWM_DBCTL_POLSEL_MAX                                              (0x0003U)

#define PWM_EPWM_DBCTL_IN_MODE_MASK                                            (0x0030U)
#define PWM_EPWM_DBCTL_IN_MODE_SHIFT                                           (0x0004U)
#define PWM_EPWM_DBCTL_IN_MODE_RESETVAL                                        (0x0000U)
#define PWM_EPWM_DBCTL_IN_MODE_MAX                                             (0x0003U)

#define PWM_EPWM_DBCTL_LOADREDMODE_MASK                                        (0x00C0U)
#define PWM_EPWM_DBCTL_LOADREDMODE_SHIFT                                       (0x0006U)
#define PWM_EPWM_DBCTL_LOADREDMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DBCTL_LOADREDMODE_MAX                                         (0x0003U)

#define PWM_EPWM_DBCTL_LOADFEDMODE_MASK                                        (0x0300U)
#define PWM_EPWM_DBCTL_LOADFEDMODE_SHIFT                                       (0x0008U)
#define PWM_EPWM_DBCTL_LOADFEDMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DBCTL_LOADFEDMODE_MAX                                         (0x0003U)

#define PWM_EPWM_DBCTL_SHDWDBREDMODE_MASK                                      (0x0400U)
#define PWM_EPWM_DBCTL_SHDWDBREDMODE_SHIFT                                     (0x000AU)
#define PWM_EPWM_DBCTL_SHDWDBREDMODE_RESETVAL                                  (0x0000U)
#define PWM_EPWM_DBCTL_SHDWDBREDMODE_MAX                                       (0x0001U)

#define PWM_EPWM_DBCTL_SHDWDBFEDMODE_MASK                                      (0x0800U)
#define PWM_EPWM_DBCTL_SHDWDBFEDMODE_SHIFT                                     (0x000BU)
#define PWM_EPWM_DBCTL_SHDWDBFEDMODE_RESETVAL                                  (0x0000U)
#define PWM_EPWM_DBCTL_SHDWDBFEDMODE_MAX                                       (0x0001U)

#define PWM_EPWM_DBCTL_OUTSWAP_MASK                                            (0x3000U)
#define PWM_EPWM_DBCTL_OUTSWAP_SHIFT                                           (0x000CU)
#define PWM_EPWM_DBCTL_OUTSWAP_RESETVAL                                        (0x0000U)
#define PWM_EPWM_DBCTL_OUTSWAP_MAX                                             (0x0003U)

#define PWM_EPWM_DBCTL_DEDB_MODE_MASK                                          (0x4000U)
#define PWM_EPWM_DBCTL_DEDB_MODE_SHIFT                                         (0x000EU)
#define PWM_EPWM_DBCTL_DEDB_MODE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DBCTL_DEDB_MODE_MAX                                           (0x0001U)

#define PWM_EPWM_DBCTL_HALFCYCLE_MASK                                          (0x8000U)
#define PWM_EPWM_DBCTL_HALFCYCLE_SHIFT                                         (0x000FU)
#define PWM_EPWM_DBCTL_HALFCYCLE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DBCTL_HALFCYCLE_MAX                                           (0x0001U)

#define PWM_EPWM_DBCTL_RESETVAL                                                (0x0000U)

/* DBCTL2 */

#define PWM_EPWM_DBCTL2_LOADDBCTLMODE_MASK                                     (0x0003U)
#define PWM_EPWM_DBCTL2_LOADDBCTLMODE_SHIFT                                    (0x0000U)
#define PWM_EPWM_DBCTL2_LOADDBCTLMODE_RESETVAL                                 (0x0000U)
#define PWM_EPWM_DBCTL2_LOADDBCTLMODE_MAX                                      (0x0003U)

#define PWM_EPWM_DBCTL2_SHDWDBCTLMODE_MASK                                     (0x0004U)
#define PWM_EPWM_DBCTL2_SHDWDBCTLMODE_SHIFT                                    (0x0002U)
#define PWM_EPWM_DBCTL2_SHDWDBCTLMODE_RESETVAL                                 (0x0000U)
#define PWM_EPWM_DBCTL2_SHDWDBCTLMODE_MAX                                      (0x0001U)

#define PWM_EPWM_DBCTL2_RESERVED_1_MASK                                        (0xFFF8U)
#define PWM_EPWM_DBCTL2_RESERVED_1_SHIFT                                       (0x0003U)
#define PWM_EPWM_DBCTL2_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DBCTL2_RESERVED_1_MAX                                         (0x1FFFU)

#define PWM_EPWM_DBCTL2_RESETVAL                                               (0x0000U)

/* RESERVED_3 */

#define PWM_EPWM_RESERVED_3_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_3_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_3_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_3_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_3_RESETVAL                                           (0x0000U)

/* AQCTL */

#define PWM_EPWM_AQCTL_LDAQAMODE_MASK                                          (0x0003U)
#define PWM_EPWM_AQCTL_LDAQAMODE_SHIFT                                         (0x0000U)
#define PWM_EPWM_AQCTL_LDAQAMODE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_AQCTL_LDAQAMODE_MAX                                           (0x0003U)

#define PWM_EPWM_AQCTL_LDAQBMODE_MASK                                          (0x000CU)
#define PWM_EPWM_AQCTL_LDAQBMODE_SHIFT                                         (0x0002U)
#define PWM_EPWM_AQCTL_LDAQBMODE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_AQCTL_LDAQBMODE_MAX                                           (0x0003U)

#define PWM_EPWM_AQCTL_SHDWAQAMODE_MASK                                        (0x0010U)
#define PWM_EPWM_AQCTL_SHDWAQAMODE_SHIFT                                       (0x0004U)
#define PWM_EPWM_AQCTL_SHDWAQAMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_AQCTL_SHDWAQAMODE_MAX                                         (0x0001U)

#define PWM_EPWM_AQCTL_RESERVED_1_MASK                                         (0x0020U)
#define PWM_EPWM_AQCTL_RESERVED_1_SHIFT                                        (0x0005U)
#define PWM_EPWM_AQCTL_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_AQCTL_RESERVED_1_MAX                                          (0x0001U)

#define PWM_EPWM_AQCTL_SHDWAQBMODE_MASK                                        (0x0040U)
#define PWM_EPWM_AQCTL_SHDWAQBMODE_SHIFT                                       (0x0006U)
#define PWM_EPWM_AQCTL_SHDWAQBMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_AQCTL_SHDWAQBMODE_MAX                                         (0x0001U)

#define PWM_EPWM_AQCTL_RESERVED_2_MASK                                         (0x0080U)
#define PWM_EPWM_AQCTL_RESERVED_2_SHIFT                                        (0x0007U)
#define PWM_EPWM_AQCTL_RESERVED_2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_AQCTL_RESERVED_2_MAX                                          (0x0001U)

#define PWM_EPWM_AQCTL_LDAQASYNC_MASK                                          (0x0300U)
#define PWM_EPWM_AQCTL_LDAQASYNC_SHIFT                                         (0x0008U)
#define PWM_EPWM_AQCTL_LDAQASYNC_RESETVAL                                      (0x0000U)
#define PWM_EPWM_AQCTL_LDAQASYNC_MAX                                           (0x0003U)

#define PWM_EPWM_AQCTL_LDAQBSYNC_MASK                                          (0x0C00U)
#define PWM_EPWM_AQCTL_LDAQBSYNC_SHIFT                                         (0x000AU)
#define PWM_EPWM_AQCTL_LDAQBSYNC_RESETVAL                                      (0x0000U)
#define PWM_EPWM_AQCTL_LDAQBSYNC_MAX                                           (0x0003U)

#define PWM_EPWM_AQCTL_RESERVED_3_MASK                                         (0xF000U)
#define PWM_EPWM_AQCTL_RESERVED_3_SHIFT                                        (0x000CU)
#define PWM_EPWM_AQCTL_RESERVED_3_RESETVAL                                     (0x0000U)
#define PWM_EPWM_AQCTL_RESERVED_3_MAX                                          (0x000FU)

#define PWM_EPWM_AQCTL_RESETVAL                                                (0x0000U)

/* AQTSRCSEL */

#define PWM_EPWM_AQTSRCSEL_T1SEL_MASK                                          (0x000FU)
#define PWM_EPWM_AQTSRCSEL_T1SEL_SHIFT                                         (0x0000U)
#define PWM_EPWM_AQTSRCSEL_T1SEL_RESETVAL                                      (0x0000U)
#define PWM_EPWM_AQTSRCSEL_T1SEL_MAX                                           (0x000FU)

#define PWM_EPWM_AQTSRCSEL_T2SEL_MASK                                          (0x00F0U)
#define PWM_EPWM_AQTSRCSEL_T2SEL_SHIFT                                         (0x0004U)
#define PWM_EPWM_AQTSRCSEL_T2SEL_RESETVAL                                      (0x0000U)
#define PWM_EPWM_AQTSRCSEL_T2SEL_MAX                                           (0x000FU)

#define PWM_EPWM_AQTSRCSEL_RESERVED_1_MASK                                     (0xFF00U)
#define PWM_EPWM_AQTSRCSEL_RESERVED_1_SHIFT                                    (0x0008U)
#define PWM_EPWM_AQTSRCSEL_RESERVED_1_RESETVAL                                 (0x0000U)
#define PWM_EPWM_AQTSRCSEL_RESERVED_1_MAX                                      (0x00FFU)

#define PWM_EPWM_AQTSRCSEL_RESETVAL                                            (0x0000U)

/* RESERVED_4 */

#define PWM_EPWM_RESERVED_4_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_4_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_4_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_4_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_4_RESETVAL                                           (0x0000U)

/* PCCTL */

#define PWM_EPWM_PCCTL_CHPEN_MASK                                              (0x0001U)
#define PWM_EPWM_PCCTL_CHPEN_SHIFT                                             (0x0000U)
#define PWM_EPWM_PCCTL_CHPEN_RESETVAL                                          (0x0000U)
#define PWM_EPWM_PCCTL_CHPEN_MAX                                               (0x0001U)

#define PWM_EPWM_PCCTL_OSHTWTH_MASK                                            (0x001EU)
#define PWM_EPWM_PCCTL_OSHTWTH_SHIFT                                           (0x0001U)
#define PWM_EPWM_PCCTL_OSHTWTH_RESETVAL                                        (0x0000U)
#define PWM_EPWM_PCCTL_OSHTWTH_MAX                                             (0x000FU)

#define PWM_EPWM_PCCTL_CHPFREQ_MASK                                            (0x00E0U)
#define PWM_EPWM_PCCTL_CHPFREQ_SHIFT                                           (0x0005U)
#define PWM_EPWM_PCCTL_CHPFREQ_RESETVAL                                        (0x0000U)
#define PWM_EPWM_PCCTL_CHPFREQ_MAX                                             (0x0007U)

#define PWM_EPWM_PCCTL_CHPDUTY_MASK                                            (0x0700U)
#define PWM_EPWM_PCCTL_CHPDUTY_SHIFT                                           (0x0008U)
#define PWM_EPWM_PCCTL_CHPDUTY_RESETVAL                                        (0x0000U)
#define PWM_EPWM_PCCTL_CHPDUTY_MAX                                             (0x0007U)

#define PWM_EPWM_PCCTL_RESERVED_1_MASK                                         (0xF800U)
#define PWM_EPWM_PCCTL_RESERVED_1_SHIFT                                        (0x000BU)
#define PWM_EPWM_PCCTL_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_PCCTL_RESERVED_1_MAX                                          (0x001FU)

#define PWM_EPWM_PCCTL_RESETVAL                                                (0x0000U)

/* RESERVED_5 */

#define PWM_EPWM_RESERVED_5_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_5_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_5_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_5_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_5_RESETVAL                                           (0x0000U)

/* VCAPCTL */

#define PWM_EPWM_VCAPCTL_VCAPE_MASK                                            (0x0001U)
#define PWM_EPWM_VCAPCTL_VCAPE_SHIFT                                           (0x0000U)
#define PWM_EPWM_VCAPCTL_VCAPE_RESETVAL                                        (0x0000U)
#define PWM_EPWM_VCAPCTL_VCAPE_MAX                                             (0x0001U)

#define PWM_EPWM_VCAPCTL_VCAPSTART_MASK                                        (0x0002U)
#define PWM_EPWM_VCAPCTL_VCAPSTART_SHIFT                                       (0x0001U)
#define PWM_EPWM_VCAPCTL_VCAPSTART_RESETVAL                                    (0x0000U)
#define PWM_EPWM_VCAPCTL_VCAPSTART_MAX                                         (0x0001U)

#define PWM_EPWM_VCAPCTL_TRIGSEL_MASK                                          (0x001CU)
#define PWM_EPWM_VCAPCTL_TRIGSEL_SHIFT                                         (0x0002U)
#define PWM_EPWM_VCAPCTL_TRIGSEL_RESETVAL                                      (0x0000U)
#define PWM_EPWM_VCAPCTL_TRIGSEL_MAX                                           (0x0007U)

#define PWM_EPWM_VCAPCTL_RESERVED_1_MASK                                       (0x0060U)
#define PWM_EPWM_VCAPCTL_RESERVED_1_SHIFT                                      (0x0005U)
#define PWM_EPWM_VCAPCTL_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_VCAPCTL_RESERVED_1_MAX                                        (0x0003U)

#define PWM_EPWM_VCAPCTL_VDELAYDIV_MASK                                        (0x0380U)
#define PWM_EPWM_VCAPCTL_VDELAYDIV_SHIFT                                       (0x0007U)
#define PWM_EPWM_VCAPCTL_VDELAYDIV_RESETVAL                                    (0x0000U)
#define PWM_EPWM_VCAPCTL_VDELAYDIV_MAX                                         (0x0007U)

#define PWM_EPWM_VCAPCTL_EDGEFILTDLYSEL_MASK                                   (0x0400U)
#define PWM_EPWM_VCAPCTL_EDGEFILTDLYSEL_SHIFT                                  (0x000AU)
#define PWM_EPWM_VCAPCTL_EDGEFILTDLYSEL_RESETVAL                               (0x0000U)
#define PWM_EPWM_VCAPCTL_EDGEFILTDLYSEL_MAX                                    (0x0001U)

#define PWM_EPWM_VCAPCTL_RESERVED_2_MASK                                       (0xF800U)
#define PWM_EPWM_VCAPCTL_RESERVED_2_SHIFT                                      (0x000BU)
#define PWM_EPWM_VCAPCTL_RESERVED_2_RESETVAL                                   (0x0000U)
#define PWM_EPWM_VCAPCTL_RESERVED_2_MAX                                        (0x001FU)

#define PWM_EPWM_VCAPCTL_RESETVAL                                              (0x0000U)

/* VCNTCFG */

#define PWM_EPWM_VCNTCFG_STARTEDGE_MASK                                        (0x000FU)
#define PWM_EPWM_VCNTCFG_STARTEDGE_SHIFT                                       (0x0000U)
#define PWM_EPWM_VCNTCFG_STARTEDGE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_VCNTCFG_STARTEDGE_MAX                                         (0x000FU)

#define PWM_EPWM_VCNTCFG_RESERVED_1_MASK                                       (0x0070U)
#define PWM_EPWM_VCNTCFG_RESERVED_1_SHIFT                                      (0x0004U)
#define PWM_EPWM_VCNTCFG_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_VCNTCFG_RESERVED_1_MAX                                        (0x0007U)

#define PWM_EPWM_VCNTCFG_STARTEDGESTS_MASK                                     (0x0080U)
#define PWM_EPWM_VCNTCFG_STARTEDGESTS_SHIFT                                    (0x0007U)
#define PWM_EPWM_VCNTCFG_STARTEDGESTS_RESETVAL                                 (0x0000U)
#define PWM_EPWM_VCNTCFG_STARTEDGESTS_MAX                                      (0x0001U)

#define PWM_EPWM_VCNTCFG_STOPEDGE_MASK                                         (0x0F00U)
#define PWM_EPWM_VCNTCFG_STOPEDGE_SHIFT                                        (0x0008U)
#define PWM_EPWM_VCNTCFG_STOPEDGE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_VCNTCFG_STOPEDGE_MAX                                          (0x000FU)

#define PWM_EPWM_VCNTCFG_RESERVED_2_MASK                                       (0x7000U)
#define PWM_EPWM_VCNTCFG_RESERVED_2_SHIFT                                      (0x000CU)
#define PWM_EPWM_VCNTCFG_RESERVED_2_RESETVAL                                   (0x0000U)
#define PWM_EPWM_VCNTCFG_RESERVED_2_MAX                                        (0x0007U)

#define PWM_EPWM_VCNTCFG_STOPEDGESTS_MASK                                      (0x8000U)
#define PWM_EPWM_VCNTCFG_STOPEDGESTS_SHIFT                                     (0x000FU)
#define PWM_EPWM_VCNTCFG_STOPEDGESTS_RESETVAL                                  (0x0000U)
#define PWM_EPWM_VCNTCFG_STOPEDGESTS_MAX                                       (0x0001U)

#define PWM_EPWM_VCNTCFG_RESETVAL                                              (0x0000U)

/* RESERVED_6 */

#define PWM_EPWM_RESERVED_6_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_6_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_6_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_6_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_6_RESETVAL                                           (0x0000U)

/* HRCNFG */

#define PWM_EPWM_HRCNFG_EDGMODE_MASK                                           (0x0003U)
#define PWM_EPWM_HRCNFG_EDGMODE_SHIFT                                          (0x0000U)
#define PWM_EPWM_HRCNFG_EDGMODE_RESETVAL                                       (0x0000U)
#define PWM_EPWM_HRCNFG_EDGMODE_MAX                                            (0x0003U)

#define PWM_EPWM_HRCNFG_CTLMODE_MASK                                           (0x0004U)
#define PWM_EPWM_HRCNFG_CTLMODE_SHIFT                                          (0x0002U)
#define PWM_EPWM_HRCNFG_CTLMODE_RESETVAL                                       (0x0000U)
#define PWM_EPWM_HRCNFG_CTLMODE_MAX                                            (0x0001U)

#define PWM_EPWM_HRCNFG_HRLOAD_MASK                                            (0x0018U)
#define PWM_EPWM_HRCNFG_HRLOAD_SHIFT                                           (0x0003U)
#define PWM_EPWM_HRCNFG_HRLOAD_RESETVAL                                        (0x0000U)
#define PWM_EPWM_HRCNFG_HRLOAD_MAX                                             (0x0003U)

#define PWM_EPWM_HRCNFG_SELOUTB_MASK                                           (0x0020U)
#define PWM_EPWM_HRCNFG_SELOUTB_SHIFT                                          (0x0005U)
#define PWM_EPWM_HRCNFG_SELOUTB_RESETVAL                                       (0x0000U)
#define PWM_EPWM_HRCNFG_SELOUTB_MAX                                            (0x0001U)

#define PWM_EPWM_HRCNFG_AUTOCONV_MASK                                          (0x0040U)
#define PWM_EPWM_HRCNFG_AUTOCONV_SHIFT                                         (0x0006U)
#define PWM_EPWM_HRCNFG_AUTOCONV_RESETVAL                                      (0x0000U)
#define PWM_EPWM_HRCNFG_AUTOCONV_MAX                                           (0x0001U)

#define PWM_EPWM_HRCNFG_SWAPAB_MASK                                            (0x0080U)
#define PWM_EPWM_HRCNFG_SWAPAB_SHIFT                                           (0x0007U)
#define PWM_EPWM_HRCNFG_SWAPAB_RESETVAL                                        (0x0000U)
#define PWM_EPWM_HRCNFG_SWAPAB_MAX                                             (0x0001U)

#define PWM_EPWM_HRCNFG_EDGMODEB_MASK                                          (0x0300U)
#define PWM_EPWM_HRCNFG_EDGMODEB_SHIFT                                         (0x0008U)
#define PWM_EPWM_HRCNFG_EDGMODEB_RESETVAL                                      (0x0000U)
#define PWM_EPWM_HRCNFG_EDGMODEB_MAX                                           (0x0003U)

#define PWM_EPWM_HRCNFG_CTLMODEB_MASK                                          (0x0400U)
#define PWM_EPWM_HRCNFG_CTLMODEB_SHIFT                                         (0x000AU)
#define PWM_EPWM_HRCNFG_CTLMODEB_RESETVAL                                      (0x0000U)
#define PWM_EPWM_HRCNFG_CTLMODEB_MAX                                           (0x0001U)

#define PWM_EPWM_HRCNFG_HRLOADB_MASK                                           (0x1800U)
#define PWM_EPWM_HRCNFG_HRLOADB_SHIFT                                          (0x000BU)
#define PWM_EPWM_HRCNFG_HRLOADB_RESETVAL                                       (0x0000U)
#define PWM_EPWM_HRCNFG_HRLOADB_MAX                                            (0x0003U)

#define PWM_EPWM_HRCNFG_RESERVED_1_MASK                                        (0x2000U)
#define PWM_EPWM_HRCNFG_RESERVED_1_SHIFT                                       (0x000DU)
#define PWM_EPWM_HRCNFG_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_HRCNFG_RESERVED_1_MAX                                         (0x0001U)

#define PWM_EPWM_HRCNFG_LINESEL_MASK                                           (0xC000U)
#define PWM_EPWM_HRCNFG_LINESEL_SHIFT                                          (0x000EU)
#define PWM_EPWM_HRCNFG_LINESEL_RESETVAL                                       (0x0000U)
#define PWM_EPWM_HRCNFG_LINESEL_MAX                                            (0x0003U)

#define PWM_EPWM_HRCNFG_RESETVAL                                               (0x0000U)

/* RESERVED_7 */

#define PWM_EPWM_RESERVED_7_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_7_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_7_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_7_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_7_RESETVAL                                           (0x0000U)

/* RESERVED_8 */

#define PWM_EPWM_RESERVED_8_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_8_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_8_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_8_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_8_RESETVAL                                           (0x0000U)

/* RESERVED_9 */

#define PWM_EPWM_RESERVED_9_UNNAMED_MASK                                       (0x0001U)
#define PWM_EPWM_RESERVED_9_UNNAMED_SHIFT                                      (0x0000U)
#define PWM_EPWM_RESERVED_9_UNNAMED_RESETVAL                                   (0x0000U)
#define PWM_EPWM_RESERVED_9_UNNAMED_MAX                                        (0x0001U)

#define PWM_EPWM_RESERVED_9_RESETVAL                                           (0x0000U)

/* RESERVED_10 */

#define PWM_EPWM_RESERVED_10_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_10_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_10_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_10_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_10_RESETVAL                                          (0x0000U)

/* RESERVED_11 */

#define PWM_EPWM_RESERVED_11_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_11_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_11_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_11_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_11_RESETVAL                                          (0x0000U)

/* RESERVED_12 */

#define PWM_EPWM_RESERVED_12_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_12_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_12_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_12_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_12_RESETVAL                                          (0x0000U)

/* HRCNFG2 */

#define PWM_EPWM_HRCNFG2_EDGMODEDB_MASK                                        (0x0003U)
#define PWM_EPWM_HRCNFG2_EDGMODEDB_SHIFT                                       (0x0000U)
#define PWM_EPWM_HRCNFG2_EDGMODEDB_RESETVAL                                    (0x0000U)
#define PWM_EPWM_HRCNFG2_EDGMODEDB_MAX                                         (0x0003U)

#define PWM_EPWM_HRCNFG2_CTLMODEDBRED_MASK                                     (0x000CU)
#define PWM_EPWM_HRCNFG2_CTLMODEDBRED_SHIFT                                    (0x0002U)
#define PWM_EPWM_HRCNFG2_CTLMODEDBRED_RESETVAL                                 (0x0000U)
#define PWM_EPWM_HRCNFG2_CTLMODEDBRED_MAX                                      (0x0003U)

#define PWM_EPWM_HRCNFG2_CTLMODEDBFED_MASK                                     (0x0030U)
#define PWM_EPWM_HRCNFG2_CTLMODEDBFED_SHIFT                                    (0x0004U)
#define PWM_EPWM_HRCNFG2_CTLMODEDBFED_RESETVAL                                 (0x0000U)
#define PWM_EPWM_HRCNFG2_CTLMODEDBFED_MAX                                      (0x0003U)

#define PWM_EPWM_HRCNFG2_RESERVED_1_MASK                                       (0x3FC0U)
#define PWM_EPWM_HRCNFG2_RESERVED_1_SHIFT                                      (0x0006U)
#define PWM_EPWM_HRCNFG2_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_HRCNFG2_RESERVED_1_MAX                                        (0x00FFU)

#define PWM_EPWM_HRCNFG2_DELLOADFRC_MASK                                       (0x4000U)
#define PWM_EPWM_HRCNFG2_DELLOADFRC_SHIFT                                      (0x000EU)
#define PWM_EPWM_HRCNFG2_DELLOADFRC_RESETVAL                                   (0x0000U)
#define PWM_EPWM_HRCNFG2_DELLOADFRC_MAX                                        (0x0001U)

#define PWM_EPWM_HRCNFG2_NOBYPASS_MASK                                         (0x8000U)
#define PWM_EPWM_HRCNFG2_NOBYPASS_SHIFT                                        (0x000FU)
#define PWM_EPWM_HRCNFG2_NOBYPASS_RESETVAL                                     (0x0000U)
#define PWM_EPWM_HRCNFG2_NOBYPASS_MAX                                          (0x0001U)

#define PWM_EPWM_HRCNFG2_RESETVAL                                              (0x0000U)

/* RESERVED_13 */

#define PWM_EPWM_RESERVED_13_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_13_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_13_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_13_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_13_RESETVAL                                          (0x0000U)

/* HRPCTL */

#define PWM_EPWM_HRPCTL_HRPE_MASK                                              (0x0001U)
#define PWM_EPWM_HRPCTL_HRPE_SHIFT                                             (0x0000U)
#define PWM_EPWM_HRPCTL_HRPE_RESETVAL                                          (0x0000U)
#define PWM_EPWM_HRPCTL_HRPE_MAX                                               (0x0001U)

#define PWM_EPWM_HRPCTL_PWMSYNCSEL_MASK                                        (0x0002U)
#define PWM_EPWM_HRPCTL_PWMSYNCSEL_SHIFT                                       (0x0001U)
#define PWM_EPWM_HRPCTL_PWMSYNCSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_HRPCTL_PWMSYNCSEL_MAX                                         (0x0001U)

#define PWM_EPWM_HRPCTL_TBPHSHRLOADE_MASK                                      (0x0004U)
#define PWM_EPWM_HRPCTL_TBPHSHRLOADE_SHIFT                                     (0x0002U)
#define PWM_EPWM_HRPCTL_TBPHSHRLOADE_RESETVAL                                  (0x0000U)
#define PWM_EPWM_HRPCTL_TBPHSHRLOADE_MAX                                       (0x0001U)

#define PWM_EPWM_HRPCTL_HRPSYNCE_MASK                                          (0x0008U)
#define PWM_EPWM_HRPCTL_HRPSYNCE_SHIFT                                         (0x0003U)
#define PWM_EPWM_HRPCTL_HRPSYNCE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_HRPCTL_HRPSYNCE_MAX                                           (0x0001U)

#define PWM_EPWM_HRPCTL_PWMSYNCSELX_MASK                                       (0x0070U)
#define PWM_EPWM_HRPCTL_PWMSYNCSELX_SHIFT                                      (0x0004U)
#define PWM_EPWM_HRPCTL_PWMSYNCSELX_RESETVAL                                   (0x0000U)
#define PWM_EPWM_HRPCTL_PWMSYNCSELX_MAX                                        (0x0007U)

#define PWM_EPWM_HRPCTL_RESERVED_1_MASK                                        (0xFF80U)
#define PWM_EPWM_HRPCTL_RESERVED_1_SHIFT                                       (0x0007U)
#define PWM_EPWM_HRPCTL_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_HRPCTL_RESERVED_1_MAX                                         (0x01FFU)

#define PWM_EPWM_HRPCTL_RESETVAL                                               (0x0000U)

/* TRREM */

#define PWM_EPWM_TRREM_TRREM_MASK                                              (0x07FFU)
#define PWM_EPWM_TRREM_TRREM_SHIFT                                             (0x0000U)
#define PWM_EPWM_TRREM_TRREM_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TRREM_TRREM_MAX                                               (0x07FFU)

#define PWM_EPWM_TRREM_RESERVED_1_MASK                                         (0xF800U)
#define PWM_EPWM_TRREM_RESERVED_1_SHIFT                                        (0x000BU)
#define PWM_EPWM_TRREM_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TRREM_RESERVED_1_MAX                                          (0x001FU)

#define PWM_EPWM_TRREM_RESETVAL                                                (0x0000U)

/* RESERVED_14 */

#define PWM_EPWM_RESERVED_14_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_14_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_14_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_14_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_14_RESETVAL                                          (0x0000U)

/* GLDCTL */

#define PWM_EPWM_GLDCTL_GLD_MASK                                               (0x0001U)
#define PWM_EPWM_GLDCTL_GLD_SHIFT                                              (0x0000U)
#define PWM_EPWM_GLDCTL_GLD_RESETVAL                                           (0x0000U)
#define PWM_EPWM_GLDCTL_GLD_MAX                                                (0x0001U)

#define PWM_EPWM_GLDCTL_GLDMODE_MASK                                           (0x001EU)
#define PWM_EPWM_GLDCTL_GLDMODE_SHIFT                                          (0x0001U)
#define PWM_EPWM_GLDCTL_GLDMODE_RESETVAL                                       (0x0000U)
#define PWM_EPWM_GLDCTL_GLDMODE_MAX                                            (0x000FU)

#define PWM_EPWM_GLDCTL_OSHTMODE_MASK                                          (0x0020U)
#define PWM_EPWM_GLDCTL_OSHTMODE_SHIFT                                         (0x0005U)
#define PWM_EPWM_GLDCTL_OSHTMODE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_GLDCTL_OSHTMODE_MAX                                           (0x0001U)

#define PWM_EPWM_GLDCTL_RESERVED_1_MASK                                        (0x0040U)
#define PWM_EPWM_GLDCTL_RESERVED_1_SHIFT                                       (0x0006U)
#define PWM_EPWM_GLDCTL_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_GLDCTL_RESERVED_1_MAX                                         (0x0001U)

#define PWM_EPWM_GLDCTL_GLDPRD_MASK                                            (0x0380U)
#define PWM_EPWM_GLDCTL_GLDPRD_SHIFT                                           (0x0007U)
#define PWM_EPWM_GLDCTL_GLDPRD_RESETVAL                                        (0x0000U)
#define PWM_EPWM_GLDCTL_GLDPRD_MAX                                             (0x0007U)

#define PWM_EPWM_GLDCTL_GLDCNT_MASK                                            (0x1C00U)
#define PWM_EPWM_GLDCTL_GLDCNT_SHIFT                                           (0x000AU)
#define PWM_EPWM_GLDCTL_GLDCNT_RESETVAL                                        (0x0000U)
#define PWM_EPWM_GLDCTL_GLDCNT_MAX                                             (0x0007U)

#define PWM_EPWM_GLDCTL_RESERVED_2_MASK                                        (0xE000U)
#define PWM_EPWM_GLDCTL_RESERVED_2_SHIFT                                       (0x000DU)
#define PWM_EPWM_GLDCTL_RESERVED_2_RESETVAL                                    (0x0000U)
#define PWM_EPWM_GLDCTL_RESERVED_2_MAX                                         (0x0007U)

#define PWM_EPWM_GLDCTL_RESETVAL                                               (0x0000U)

/* GLDCFG */

#define PWM_EPWM_GLDCFG_TBPRD_TBPRDHR_MASK                                     (0x0001U)
#define PWM_EPWM_GLDCFG_TBPRD_TBPRDHR_SHIFT                                    (0x0000U)
#define PWM_EPWM_GLDCFG_TBPRD_TBPRDHR_RESETVAL                                 (0x0000U)
#define PWM_EPWM_GLDCFG_TBPRD_TBPRDHR_MAX                                      (0x0001U)

#define PWM_EPWM_GLDCFG_CMPA_CMPAHR_MASK                                       (0x0002U)
#define PWM_EPWM_GLDCFG_CMPA_CMPAHR_SHIFT                                      (0x0001U)
#define PWM_EPWM_GLDCFG_CMPA_CMPAHR_RESETVAL                                   (0x0000U)
#define PWM_EPWM_GLDCFG_CMPA_CMPAHR_MAX                                        (0x0001U)

#define PWM_EPWM_GLDCFG_CMPB_CMPBHR_MASK                                       (0x0004U)
#define PWM_EPWM_GLDCFG_CMPB_CMPBHR_SHIFT                                      (0x0002U)
#define PWM_EPWM_GLDCFG_CMPB_CMPBHR_RESETVAL                                   (0x0000U)
#define PWM_EPWM_GLDCFG_CMPB_CMPBHR_MAX                                        (0x0001U)

#define PWM_EPWM_GLDCFG_CMPC_MASK                                              (0x0008U)
#define PWM_EPWM_GLDCFG_CMPC_SHIFT                                             (0x0003U)
#define PWM_EPWM_GLDCFG_CMPC_RESETVAL                                          (0x0000U)
#define PWM_EPWM_GLDCFG_CMPC_MAX                                               (0x0001U)

#define PWM_EPWM_GLDCFG_CMPD_MASK                                              (0x0010U)
#define PWM_EPWM_GLDCFG_CMPD_SHIFT                                             (0x0004U)
#define PWM_EPWM_GLDCFG_CMPD_RESETVAL                                          (0x0000U)
#define PWM_EPWM_GLDCFG_CMPD_MAX                                               (0x0001U)

#define PWM_EPWM_GLDCFG_DBRED_DBREDHR_MASK                                     (0x0020U)
#define PWM_EPWM_GLDCFG_DBRED_DBREDHR_SHIFT                                    (0x0005U)
#define PWM_EPWM_GLDCFG_DBRED_DBREDHR_RESETVAL                                 (0x0000U)
#define PWM_EPWM_GLDCFG_DBRED_DBREDHR_MAX                                      (0x0001U)

#define PWM_EPWM_GLDCFG_DBFED_DBFEDHR_MASK                                     (0x0040U)
#define PWM_EPWM_GLDCFG_DBFED_DBFEDHR_SHIFT                                    (0x0006U)
#define PWM_EPWM_GLDCFG_DBFED_DBFEDHR_RESETVAL                                 (0x0000U)
#define PWM_EPWM_GLDCFG_DBFED_DBFEDHR_MAX                                      (0x0001U)

#define PWM_EPWM_GLDCFG_DBCTL_MASK                                             (0x0080U)
#define PWM_EPWM_GLDCFG_DBCTL_SHIFT                                            (0x0007U)
#define PWM_EPWM_GLDCFG_DBCTL_RESETVAL                                         (0x0000U)
#define PWM_EPWM_GLDCFG_DBCTL_MAX                                              (0x0001U)

#define PWM_EPWM_GLDCFG_AQCTLA_AQCTLA2_MASK                                    (0x0100U)
#define PWM_EPWM_GLDCFG_AQCTLA_AQCTLA2_SHIFT                                   (0x0008U)
#define PWM_EPWM_GLDCFG_AQCTLA_AQCTLA2_RESETVAL                                (0x0000U)
#define PWM_EPWM_GLDCFG_AQCTLA_AQCTLA2_MAX                                     (0x0001U)

#define PWM_EPWM_GLDCFG_AQCTLB_AQCTLB2_MASK                                    (0x0200U)
#define PWM_EPWM_GLDCFG_AQCTLB_AQCTLB2_SHIFT                                   (0x0009U)
#define PWM_EPWM_GLDCFG_AQCTLB_AQCTLB2_RESETVAL                                (0x0000U)
#define PWM_EPWM_GLDCFG_AQCTLB_AQCTLB2_MAX                                     (0x0001U)

#define PWM_EPWM_GLDCFG_AQCSFRC_MASK                                           (0x0400U)
#define PWM_EPWM_GLDCFG_AQCSFRC_SHIFT                                          (0x000AU)
#define PWM_EPWM_GLDCFG_AQCSFRC_RESETVAL                                       (0x0000U)
#define PWM_EPWM_GLDCFG_AQCSFRC_MAX                                            (0x0001U)

#define PWM_EPWM_GLDCFG_RESERVED_1_MASK                                        (0xF800U)
#define PWM_EPWM_GLDCFG_RESERVED_1_SHIFT                                       (0x000BU)
#define PWM_EPWM_GLDCFG_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_GLDCFG_RESERVED_1_MAX                                         (0x001FU)

#define PWM_EPWM_GLDCFG_RESETVAL                                               (0x0000U)

/* RESERVED_15 */

#define PWM_EPWM_RESERVED_15_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_15_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_15_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_15_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_15_RESETVAL                                          (0x0000U)

/* EPWMXLINK */

#define PWM_EPWM_EPWMXLINK_TBPRDLINK_MASK                                      (0x0000001FU)
#define PWM_EPWM_EPWMXLINK_TBPRDLINK_SHIFT                                     (0x00000000U)
#define PWM_EPWM_EPWMXLINK_TBPRDLINK_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_EPWMXLINK_TBPRDLINK_MAX                                       (0x0000001FU)

#define PWM_EPWM_EPWMXLINK_CMPALINK_MASK                                       (0x000003E0U)
#define PWM_EPWM_EPWMXLINK_CMPALINK_SHIFT                                      (0x00000005U)
#define PWM_EPWM_EPWMXLINK_CMPALINK_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_EPWMXLINK_CMPALINK_MAX                                        (0x0000001FU)

#define PWM_EPWM_EPWMXLINK_CMPBLINK_MASK                                       (0x00007C00U)
#define PWM_EPWM_EPWMXLINK_CMPBLINK_SHIFT                                      (0x0000000AU)
#define PWM_EPWM_EPWMXLINK_CMPBLINK_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_EPWMXLINK_CMPBLINK_MAX                                        (0x0000001FU)

#define PWM_EPWM_EPWMXLINK_RESERVED_1_MASK                                     (0x00008000U)
#define PWM_EPWM_EPWMXLINK_RESERVED_1_SHIFT                                    (0x0000000FU)
#define PWM_EPWM_EPWMXLINK_RESERVED_1_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_EPWMXLINK_RESERVED_1_MAX                                      (0x00000001U)

#define PWM_EPWM_EPWMXLINK_CMPCLINK_MASK                                       (0x001F0000U)
#define PWM_EPWM_EPWMXLINK_CMPCLINK_SHIFT                                      (0x00000010U)
#define PWM_EPWM_EPWMXLINK_CMPCLINK_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_EPWMXLINK_CMPCLINK_MAX                                        (0x0000001FU)

#define PWM_EPWM_EPWMXLINK_CMPDLINK_MASK                                       (0x03E00000U)
#define PWM_EPWM_EPWMXLINK_CMPDLINK_SHIFT                                      (0x00000015U)
#define PWM_EPWM_EPWMXLINK_CMPDLINK_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_EPWMXLINK_CMPDLINK_MAX                                        (0x0000001FU)

#define PWM_EPWM_EPWMXLINK_GLDCTL2LINK_MASK                                    (0x7C000000U)
#define PWM_EPWM_EPWMXLINK_GLDCTL2LINK_SHIFT                                   (0x0000001AU)
#define PWM_EPWM_EPWMXLINK_GLDCTL2LINK_RESETVAL                                (0x00000000U)
#define PWM_EPWM_EPWMXLINK_GLDCTL2LINK_MAX                                     (0x0000001FU)

#define PWM_EPWM_EPWMXLINK_RESERVED_2_MASK                                     (0x80000000U)
#define PWM_EPWM_EPWMXLINK_RESERVED_2_SHIFT                                    (0x0000001FU)
#define PWM_EPWM_EPWMXLINK_RESERVED_2_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_EPWMXLINK_RESERVED_2_MAX                                      (0x00000001U)

#define PWM_EPWM_EPWMXLINK_RESETVAL                                            (0x00000000U)

/* EPWMXLINK2 */

#define PWM_EPWM_EPWMXLINK2_DBREDLINK_MASK                                     (0x0000001FU)
#define PWM_EPWM_EPWMXLINK2_DBREDLINK_SHIFT                                    (0x00000000U)
#define PWM_EPWM_EPWMXLINK2_DBREDLINK_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_EPWMXLINK2_DBREDLINK_MAX                                      (0x0000001FU)

#define PWM_EPWM_EPWMXLINK2_DBFEDLINK_MASK                                     (0x000003E0U)
#define PWM_EPWM_EPWMXLINK2_DBFEDLINK_SHIFT                                    (0x00000005U)
#define PWM_EPWM_EPWMXLINK2_DBFEDLINK_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_EPWMXLINK2_DBFEDLINK_MAX                                      (0x0000001FU)

#define PWM_EPWM_EPWMXLINK2_RESERVED_1_MASK                                    (0xFFFFFC00U)
#define PWM_EPWM_EPWMXLINK2_RESERVED_1_SHIFT                                   (0x0000000AU)
#define PWM_EPWM_EPWMXLINK2_RESERVED_1_RESETVAL                                (0x00000000U)
#define PWM_EPWM_EPWMXLINK2_RESERVED_1_MAX                                     (0x003FFFFFU)

#define PWM_EPWM_EPWMXLINK2_RESETVAL                                           (0x00000000U)

/* RESERVED_16 */

#define PWM_EPWM_RESERVED_16_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_16_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_16_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_16_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_16_RESETVAL                                          (0x0000U)

/* ETEST */

#define PWM_EPWM_ETEST_CMPFIX_OVERRIDE_MASK                                    (0x0001U)
#define PWM_EPWM_ETEST_CMPFIX_OVERRIDE_SHIFT                                   (0x0000U)
#define PWM_EPWM_ETEST_CMPFIX_OVERRIDE_RESETVAL                                (0x0001U)
#define PWM_EPWM_ETEST_CMPFIX_OVERRIDE_MAX                                     (0x0001U)

#define PWM_EPWM_ETEST_RESERVED_1_MASK                                         (0xFFFEU)
#define PWM_EPWM_ETEST_RESERVED_1_SHIFT                                        (0x0001U)
#define PWM_EPWM_ETEST_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETEST_RESERVED_1_MAX                                          (0x7FFFU)

#define PWM_EPWM_ETEST_RESETVAL                                                (0x0001U)

/* EPWMREV */

#define PWM_EPWM_EPWMREV_REV_MASK                                              (0x00FFU)
#define PWM_EPWM_EPWMREV_REV_SHIFT                                             (0x0000U)
#define PWM_EPWM_EPWMREV_REV_RESETVAL                                          (0x0000U)
#define PWM_EPWM_EPWMREV_REV_MAX                                               (0x00FFU)

#define PWM_EPWM_EPWMREV_TYPE_MASK                                             (0xFF00U)
#define PWM_EPWM_EPWMREV_TYPE_SHIFT                                            (0x0008U)
#define PWM_EPWM_EPWMREV_TYPE_RESETVAL                                         (0x0005U)
#define PWM_EPWM_EPWMREV_TYPE_MAX                                              (0x00FFU)

#define PWM_EPWM_EPWMREV_RESETVAL                                              (0x0500U)

/* HRPWMREV */

#define PWM_EPWM_HRPWMREV_REV_MASK                                             (0x00FFU)
#define PWM_EPWM_HRPWMREV_REV_SHIFT                                            (0x0000U)
#define PWM_EPWM_HRPWMREV_REV_RESETVAL                                         (0x0000U)
#define PWM_EPWM_HRPWMREV_REV_MAX                                              (0x00FFU)

#define PWM_EPWM_HRPWMREV_TYPE_MASK                                            (0xFF00U)
#define PWM_EPWM_HRPWMREV_TYPE_SHIFT                                           (0x0008U)
#define PWM_EPWM_HRPWMREV_TYPE_RESETVAL                                        (0x0003U)
#define PWM_EPWM_HRPWMREV_TYPE_MAX                                             (0x00FFU)

#define PWM_EPWM_HRPWMREV_RESETVAL                                             (0x0300U)

/* AQCTLA */

#define PWM_EPWM_AQCTLA_ZRO_MASK                                               (0x0003U)
#define PWM_EPWM_AQCTLA_ZRO_SHIFT                                              (0x0000U)
#define PWM_EPWM_AQCTLA_ZRO_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLA_ZRO_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLA_PRD_MASK                                               (0x000CU)
#define PWM_EPWM_AQCTLA_PRD_SHIFT                                              (0x0002U)
#define PWM_EPWM_AQCTLA_PRD_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLA_PRD_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLA_CAU_MASK                                               (0x0030U)
#define PWM_EPWM_AQCTLA_CAU_SHIFT                                              (0x0004U)
#define PWM_EPWM_AQCTLA_CAU_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLA_CAU_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLA_CAD_MASK                                               (0x00C0U)
#define PWM_EPWM_AQCTLA_CAD_SHIFT                                              (0x0006U)
#define PWM_EPWM_AQCTLA_CAD_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLA_CAD_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLA_CBU_MASK                                               (0x0300U)
#define PWM_EPWM_AQCTLA_CBU_SHIFT                                              (0x0008U)
#define PWM_EPWM_AQCTLA_CBU_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLA_CBU_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLA_CBD_MASK                                               (0x0C00U)
#define PWM_EPWM_AQCTLA_CBD_SHIFT                                              (0x000AU)
#define PWM_EPWM_AQCTLA_CBD_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLA_CBD_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLA_RESERVED_1_MASK                                        (0xF000U)
#define PWM_EPWM_AQCTLA_RESERVED_1_SHIFT                                       (0x000CU)
#define PWM_EPWM_AQCTLA_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_AQCTLA_RESERVED_1_MAX                                         (0x000FU)

#define PWM_EPWM_AQCTLA_RESETVAL                                               (0x0000U)

/* AQCTLA2 */

#define PWM_EPWM_AQCTLA2_T1U_MASK                                              (0x0003U)
#define PWM_EPWM_AQCTLA2_T1U_SHIFT                                             (0x0000U)
#define PWM_EPWM_AQCTLA2_T1U_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLA2_T1U_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLA2_T1D_MASK                                              (0x000CU)
#define PWM_EPWM_AQCTLA2_T1D_SHIFT                                             (0x0002U)
#define PWM_EPWM_AQCTLA2_T1D_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLA2_T1D_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLA2_T2U_MASK                                              (0x0030U)
#define PWM_EPWM_AQCTLA2_T2U_SHIFT                                             (0x0004U)
#define PWM_EPWM_AQCTLA2_T2U_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLA2_T2U_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLA2_T2D_MASK                                              (0x00C0U)
#define PWM_EPWM_AQCTLA2_T2D_SHIFT                                             (0x0006U)
#define PWM_EPWM_AQCTLA2_T2D_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLA2_T2D_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLA2_RESERVED_1_MASK                                       (0xFF00U)
#define PWM_EPWM_AQCTLA2_RESERVED_1_SHIFT                                      (0x0008U)
#define PWM_EPWM_AQCTLA2_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_AQCTLA2_RESERVED_1_MAX                                        (0x00FFU)

#define PWM_EPWM_AQCTLA2_RESETVAL                                              (0x0000U)

/* AQCTLB */

#define PWM_EPWM_AQCTLB_ZRO_MASK                                               (0x0003U)
#define PWM_EPWM_AQCTLB_ZRO_SHIFT                                              (0x0000U)
#define PWM_EPWM_AQCTLB_ZRO_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLB_ZRO_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLB_PRD_MASK                                               (0x000CU)
#define PWM_EPWM_AQCTLB_PRD_SHIFT                                              (0x0002U)
#define PWM_EPWM_AQCTLB_PRD_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLB_PRD_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLB_CAU_MASK                                               (0x0030U)
#define PWM_EPWM_AQCTLB_CAU_SHIFT                                              (0x0004U)
#define PWM_EPWM_AQCTLB_CAU_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLB_CAU_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLB_CAD_MASK                                               (0x00C0U)
#define PWM_EPWM_AQCTLB_CAD_SHIFT                                              (0x0006U)
#define PWM_EPWM_AQCTLB_CAD_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLB_CAD_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLB_CBU_MASK                                               (0x0300U)
#define PWM_EPWM_AQCTLB_CBU_SHIFT                                              (0x0008U)
#define PWM_EPWM_AQCTLB_CBU_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLB_CBU_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLB_CBD_MASK                                               (0x0C00U)
#define PWM_EPWM_AQCTLB_CBD_SHIFT                                              (0x000AU)
#define PWM_EPWM_AQCTLB_CBD_RESETVAL                                           (0x0000U)
#define PWM_EPWM_AQCTLB_CBD_MAX                                                (0x0003U)

#define PWM_EPWM_AQCTLB_RESERVED_1_MASK                                        (0xF000U)
#define PWM_EPWM_AQCTLB_RESERVED_1_SHIFT                                       (0x000CU)
#define PWM_EPWM_AQCTLB_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_AQCTLB_RESERVED_1_MAX                                         (0x000FU)

#define PWM_EPWM_AQCTLB_RESETVAL                                               (0x0000U)

/* AQCTLB2 */

#define PWM_EPWM_AQCTLB2_T1U_MASK                                              (0x0003U)
#define PWM_EPWM_AQCTLB2_T1U_SHIFT                                             (0x0000U)
#define PWM_EPWM_AQCTLB2_T1U_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLB2_T1U_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLB2_T1D_MASK                                              (0x000CU)
#define PWM_EPWM_AQCTLB2_T1D_SHIFT                                             (0x0002U)
#define PWM_EPWM_AQCTLB2_T1D_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLB2_T1D_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLB2_T2U_MASK                                              (0x0030U)
#define PWM_EPWM_AQCTLB2_T2U_SHIFT                                             (0x0004U)
#define PWM_EPWM_AQCTLB2_T2U_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLB2_T2U_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLB2_T2D_MASK                                              (0x00C0U)
#define PWM_EPWM_AQCTLB2_T2D_SHIFT                                             (0x0006U)
#define PWM_EPWM_AQCTLB2_T2D_RESETVAL                                          (0x0000U)
#define PWM_EPWM_AQCTLB2_T2D_MAX                                               (0x0003U)

#define PWM_EPWM_AQCTLB2_RESERVED_1_MASK                                       (0xFF00U)
#define PWM_EPWM_AQCTLB2_RESERVED_1_SHIFT                                      (0x0008U)
#define PWM_EPWM_AQCTLB2_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_AQCTLB2_RESERVED_1_MAX                                        (0x00FFU)

#define PWM_EPWM_AQCTLB2_RESETVAL                                              (0x0000U)

/* RESERVED_17 */

#define PWM_EPWM_RESERVED_17_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_17_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_17_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_17_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_17_RESETVAL                                          (0x0000U)

/* AQSFRC */

#define PWM_EPWM_AQSFRC_ACTSFA_MASK                                            (0x0003U)
#define PWM_EPWM_AQSFRC_ACTSFA_SHIFT                                           (0x0000U)
#define PWM_EPWM_AQSFRC_ACTSFA_RESETVAL                                        (0x0000U)
#define PWM_EPWM_AQSFRC_ACTSFA_MAX                                             (0x0003U)

#define PWM_EPWM_AQSFRC_OTSFA_MASK                                             (0x0004U)
#define PWM_EPWM_AQSFRC_OTSFA_SHIFT                                            (0x0002U)
#define PWM_EPWM_AQSFRC_OTSFA_RESETVAL                                         (0x0000U)
#define PWM_EPWM_AQSFRC_OTSFA_MAX                                              (0x0001U)

#define PWM_EPWM_AQSFRC_ACTSFB_MASK                                            (0x0018U)
#define PWM_EPWM_AQSFRC_ACTSFB_SHIFT                                           (0x0003U)
#define PWM_EPWM_AQSFRC_ACTSFB_RESETVAL                                        (0x0000U)
#define PWM_EPWM_AQSFRC_ACTSFB_MAX                                             (0x0003U)

#define PWM_EPWM_AQSFRC_OTSFB_MASK                                             (0x0020U)
#define PWM_EPWM_AQSFRC_OTSFB_SHIFT                                            (0x0005U)
#define PWM_EPWM_AQSFRC_OTSFB_RESETVAL                                         (0x0000U)
#define PWM_EPWM_AQSFRC_OTSFB_MAX                                              (0x0001U)

#define PWM_EPWM_AQSFRC_RLDCSF_MASK                                            (0x00C0U)
#define PWM_EPWM_AQSFRC_RLDCSF_SHIFT                                           (0x0006U)
#define PWM_EPWM_AQSFRC_RLDCSF_RESETVAL                                        (0x0000U)
#define PWM_EPWM_AQSFRC_RLDCSF_MAX                                             (0x0003U)

#define PWM_EPWM_AQSFRC_RESERVED_1_MASK                                        (0xFF00U)
#define PWM_EPWM_AQSFRC_RESERVED_1_SHIFT                                       (0x0008U)
#define PWM_EPWM_AQSFRC_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_AQSFRC_RESERVED_1_MAX                                         (0x00FFU)

#define PWM_EPWM_AQSFRC_RESETVAL                                               (0x0000U)

/* RESERVED_18 */

#define PWM_EPWM_RESERVED_18_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_18_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_18_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_18_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_18_RESETVAL                                          (0x0000U)

/* AQCSFRC */

#define PWM_EPWM_AQCSFRC_CSFA_MASK                                             (0x0003U)
#define PWM_EPWM_AQCSFRC_CSFA_SHIFT                                            (0x0000U)
#define PWM_EPWM_AQCSFRC_CSFA_RESETVAL                                         (0x0000U)
#define PWM_EPWM_AQCSFRC_CSFA_MAX                                              (0x0003U)

#define PWM_EPWM_AQCSFRC_CSFB_MASK                                             (0x000CU)
#define PWM_EPWM_AQCSFRC_CSFB_SHIFT                                            (0x0002U)
#define PWM_EPWM_AQCSFRC_CSFB_RESETVAL                                         (0x0000U)
#define PWM_EPWM_AQCSFRC_CSFB_MAX                                              (0x0003U)

#define PWM_EPWM_AQCSFRC_RESERVED_1_MASK                                       (0xFFF0U)
#define PWM_EPWM_AQCSFRC_RESERVED_1_SHIFT                                      (0x0004U)
#define PWM_EPWM_AQCSFRC_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_AQCSFRC_RESERVED_1_MAX                                        (0x0FFFU)

#define PWM_EPWM_AQCSFRC_RESETVAL                                              (0x0000U)

/* RESERVED_19 */

#define PWM_EPWM_RESERVED_19_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_19_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_19_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_19_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_19_RESETVAL                                          (0x0000U)

/* DBREDHR */

#define PWM_EPWM_DBREDHR_RESERVED_1_MASK                                       (0x0001U)
#define PWM_EPWM_DBREDHR_RESERVED_1_SHIFT                                      (0x0000U)
#define PWM_EPWM_DBREDHR_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_DBREDHR_RESERVED_1_MAX                                        (0x0001U)

#define PWM_EPWM_DBREDHR_DBREDHR_DELAY_MASK                                    (0x00FEU)
#define PWM_EPWM_DBREDHR_DBREDHR_DELAY_SHIFT                                   (0x0001U)
#define PWM_EPWM_DBREDHR_DBREDHR_DELAY_RESETVAL                                (0x0000U)
#define PWM_EPWM_DBREDHR_DBREDHR_DELAY_MAX                                     (0x007FU)

#define PWM_EPWM_DBREDHR_RESERVED_2_MASK                                       (0x0100U)
#define PWM_EPWM_DBREDHR_RESERVED_2_SHIFT                                      (0x0008U)
#define PWM_EPWM_DBREDHR_RESERVED_2_RESETVAL                                   (0x0000U)
#define PWM_EPWM_DBREDHR_RESERVED_2_MAX                                        (0x0001U)

#define PWM_EPWM_DBREDHR_DBREDHR_MASK                                          (0xFE00U)
#define PWM_EPWM_DBREDHR_DBREDHR_SHIFT                                         (0x0009U)
#define PWM_EPWM_DBREDHR_DBREDHR_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DBREDHR_DBREDHR_MAX                                           (0x007FU)

#define PWM_EPWM_DBREDHR_RESETVAL                                              (0x0000U)

/* DBRED */

#define PWM_EPWM_DBRED_DBRED_MASK                                              (0x3FFFU)
#define PWM_EPWM_DBRED_DBRED_SHIFT                                             (0x0000U)
#define PWM_EPWM_DBRED_DBRED_RESETVAL                                          (0x0000U)
#define PWM_EPWM_DBRED_DBRED_MAX                                               (0x3FFFU)

#define PWM_EPWM_DBRED_RESERVED_1_MASK                                         (0xC000U)
#define PWM_EPWM_DBRED_RESERVED_1_SHIFT                                        (0x000EU)
#define PWM_EPWM_DBRED_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_DBRED_RESERVED_1_MAX                                          (0x0003U)

#define PWM_EPWM_DBRED_RESETVAL                                                (0x0000U)

/* DBFEDHR */

#define PWM_EPWM_DBFEDHR_RESERVED_1_MASK                                       (0x0001U)
#define PWM_EPWM_DBFEDHR_RESERVED_1_SHIFT                                      (0x0000U)
#define PWM_EPWM_DBFEDHR_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_DBFEDHR_RESERVED_1_MAX                                        (0x0001U)

#define PWM_EPWM_DBFEDHR_DBFEDHR_DELAY_MASK                                    (0x00FEU)
#define PWM_EPWM_DBFEDHR_DBFEDHR_DELAY_SHIFT                                   (0x0001U)
#define PWM_EPWM_DBFEDHR_DBFEDHR_DELAY_RESETVAL                                (0x0000U)
#define PWM_EPWM_DBFEDHR_DBFEDHR_DELAY_MAX                                     (0x007FU)

#define PWM_EPWM_DBFEDHR_RESERVED_2_MASK                                       (0x0100U)
#define PWM_EPWM_DBFEDHR_RESERVED_2_SHIFT                                      (0x0008U)
#define PWM_EPWM_DBFEDHR_RESERVED_2_RESETVAL                                   (0x0000U)
#define PWM_EPWM_DBFEDHR_RESERVED_2_MAX                                        (0x0001U)

#define PWM_EPWM_DBFEDHR_DBFEDHR_MASK                                          (0xFE00U)
#define PWM_EPWM_DBFEDHR_DBFEDHR_SHIFT                                         (0x0009U)
#define PWM_EPWM_DBFEDHR_DBFEDHR_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DBFEDHR_DBFEDHR_MAX                                           (0x007FU)

#define PWM_EPWM_DBFEDHR_RESETVAL                                              (0x0000U)

/* DBFED */

#define PWM_EPWM_DBFED_DBFED_MASK                                              (0x3FFFU)
#define PWM_EPWM_DBFED_DBFED_SHIFT                                             (0x0000U)
#define PWM_EPWM_DBFED_DBFED_RESETVAL                                          (0x0000U)
#define PWM_EPWM_DBFED_DBFED_MAX                                               (0x3FFFU)

#define PWM_EPWM_DBFED_RESERVED_1_MASK                                         (0xC000U)
#define PWM_EPWM_DBFED_RESERVED_1_SHIFT                                        (0x000EU)
#define PWM_EPWM_DBFED_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_DBFED_RESERVED_1_MAX                                          (0x0003U)

#define PWM_EPWM_DBFED_RESETVAL                                                (0x0000U)

/* RESERVED_20 */

#define PWM_EPWM_RESERVED_20_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_20_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_20_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_20_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_20_RESETVAL                                          (0x0000U)

/* TBPHS */

#define PWM_EPWM_TBPHS_TBPHSHR_MASK                                            (0x0000FFFFU)
#define PWM_EPWM_TBPHS_TBPHSHR_SHIFT                                           (0x00000000U)
#define PWM_EPWM_TBPHS_TBPHSHR_RESETVAL                                        (0x00000000U)
#define PWM_EPWM_TBPHS_TBPHSHR_MAX                                             (0x0000FFFFU)

#define PWM_EPWM_TBPHS_TBPHS_MASK                                              (0xFFFF0000U)
#define PWM_EPWM_TBPHS_TBPHS_SHIFT                                             (0x00000010U)
#define PWM_EPWM_TBPHS_TBPHS_RESETVAL                                          (0x00000000U)
#define PWM_EPWM_TBPHS_TBPHS_MAX                                               (0x0000FFFFU)

#define PWM_EPWM_TBPHS_RESETVAL                                                (0x00000000U)

/* TBPRDHR */

#define PWM_EPWM_TBPRDHR_TBPRDHR_MASK                                          (0xFFFFU)
#define PWM_EPWM_TBPRDHR_TBPRDHR_SHIFT                                         (0x0000U)
#define PWM_EPWM_TBPRDHR_TBPRDHR_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TBPRDHR_TBPRDHR_MAX                                           (0xFFFFU)

#define PWM_EPWM_TBPRDHR_RESETVAL                                              (0x0000U)

/* TBPRD */

#define PWM_EPWM_TBPRD_TBPRD_MASK                                              (0xFFFFU)
#define PWM_EPWM_TBPRD_TBPRD_SHIFT                                             (0x0000U)
#define PWM_EPWM_TBPRD_TBPRD_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TBPRD_TBPRD_MAX                                               (0xFFFFU)

#define PWM_EPWM_TBPRD_RESETVAL                                                (0x0000U)

/* TBPRDHRB */

#define PWM_EPWM_TBPRDHRB_TBPRDHRB_DELAY_MASK                                  (0x00FFU)
#define PWM_EPWM_TBPRDHRB_TBPRDHRB_DELAY_SHIFT                                 (0x0000U)
#define PWM_EPWM_TBPRDHRB_TBPRDHRB_DELAY_RESETVAL                              (0x0000U)
#define PWM_EPWM_TBPRDHRB_TBPRDHRB_DELAY_MAX                                   (0x00FFU)

#define PWM_EPWM_TBPRDHRB_TBPRDHRB_MASK                                        (0xFF00U)
#define PWM_EPWM_TBPRDHRB_TBPRDHRB_SHIFT                                       (0x0008U)
#define PWM_EPWM_TBPRDHRB_TBPRDHRB_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TBPRDHRB_TBPRDHRB_MAX                                         (0x00FFU)

#define PWM_EPWM_TBPRDHRB_RESETVAL                                             (0x0000U)

/* RESERVED_21 */

#define PWM_EPWM_RESERVED_21_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_21_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_21_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_21_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_21_RESETVAL                                          (0x0000U)

/* CMPA */

#define PWM_EPWM_CMPA_CMPAHR_MASK                                              (0x0000FFFFU)
#define PWM_EPWM_CMPA_CMPAHR_SHIFT                                             (0x00000000U)
#define PWM_EPWM_CMPA_CMPAHR_RESETVAL                                          (0x00000000U)
#define PWM_EPWM_CMPA_CMPAHR_MAX                                               (0x0000FFFFU)

#define PWM_EPWM_CMPA_CMPA_MASK                                                (0xFFFF0000U)
#define PWM_EPWM_CMPA_CMPA_SHIFT                                               (0x00000010U)
#define PWM_EPWM_CMPA_CMPA_RESETVAL                                            (0x00000000U)
#define PWM_EPWM_CMPA_CMPA_MAX                                                 (0x0000FFFFU)

#define PWM_EPWM_CMPA_RESETVAL                                                 (0x00000000U)

/* CMPB */

#define PWM_EPWM_CMPB_CMPBHR_MASK                                              (0x0000FFFFU)
#define PWM_EPWM_CMPB_CMPBHR_SHIFT                                             (0x00000000U)
#define PWM_EPWM_CMPB_CMPBHR_RESETVAL                                          (0x00000000U)
#define PWM_EPWM_CMPB_CMPBHR_MAX                                               (0x0000FFFFU)

#define PWM_EPWM_CMPB_CMPB_MASK                                                (0xFFFF0000U)
#define PWM_EPWM_CMPB_CMPB_SHIFT                                               (0x00000010U)
#define PWM_EPWM_CMPB_CMPB_RESETVAL                                            (0x00000000U)
#define PWM_EPWM_CMPB_CMPB_MAX                                                 (0x0000FFFFU)

#define PWM_EPWM_CMPB_RESETVAL                                                 (0x00000000U)

/* RESERVED_22 */

#define PWM_EPWM_RESERVED_22_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_22_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_22_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_22_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_22_RESETVAL                                          (0x0000U)

/* CMPC */

#define PWM_EPWM_CMPC_CMPC_MASK                                                (0xFFFFU)
#define PWM_EPWM_CMPC_CMPC_SHIFT                                               (0x0000U)
#define PWM_EPWM_CMPC_CMPC_RESETVAL                                            (0x0000U)
#define PWM_EPWM_CMPC_CMPC_MAX                                                 (0xFFFFU)

#define PWM_EPWM_CMPC_RESETVAL                                                 (0x0000U)

/* RESERVED_23 */

#define PWM_EPWM_RESERVED_23_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_23_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_23_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_23_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_23_RESETVAL                                          (0x0000U)

/* CMPD */

#define PWM_EPWM_CMPD_CMPD_MASK                                                (0xFFFFU)
#define PWM_EPWM_CMPD_CMPD_SHIFT                                               (0x0000U)
#define PWM_EPWM_CMPD_CMPD_RESETVAL                                            (0x0000U)
#define PWM_EPWM_CMPD_CMPD_MAX                                                 (0xFFFFU)

#define PWM_EPWM_CMPD_RESETVAL                                                 (0x0000U)

/* RESERVED_24 */

#define PWM_EPWM_RESERVED_24_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_24_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_24_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_24_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_24_RESETVAL                                          (0x0000U)

/* GLDCTL2 */

#define PWM_EPWM_GLDCTL2_OSHTLD_MASK                                           (0x0001U)
#define PWM_EPWM_GLDCTL2_OSHTLD_SHIFT                                          (0x0000U)
#define PWM_EPWM_GLDCTL2_OSHTLD_RESETVAL                                       (0x0000U)
#define PWM_EPWM_GLDCTL2_OSHTLD_MAX                                            (0x0001U)

#define PWM_EPWM_GLDCTL2_GFRCLD_MASK                                           (0x0002U)
#define PWM_EPWM_GLDCTL2_GFRCLD_SHIFT                                          (0x0001U)
#define PWM_EPWM_GLDCTL2_GFRCLD_RESETVAL                                       (0x0000U)
#define PWM_EPWM_GLDCTL2_GFRCLD_MAX                                            (0x0001U)

#define PWM_EPWM_GLDCTL2_RESERVED_1_MASK                                       (0xFFFCU)
#define PWM_EPWM_GLDCTL2_RESERVED_1_SHIFT                                      (0x0002U)
#define PWM_EPWM_GLDCTL2_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_GLDCTL2_RESERVED_1_MAX                                        (0x3FFFU)

#define PWM_EPWM_GLDCTL2_RESETVAL                                              (0x0000U)

/* RESERVED_25 */

#define PWM_EPWM_RESERVED_25_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_25_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_25_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_25_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_25_RESETVAL                                          (0x0000U)

/* SWVDELVAL */

#define PWM_EPWM_SWVDELVAL_SWVDELVAL_MASK                                      (0xFFFFU)
#define PWM_EPWM_SWVDELVAL_SWVDELVAL_SHIFT                                     (0x0000U)
#define PWM_EPWM_SWVDELVAL_SWVDELVAL_RESETVAL                                  (0x0000U)
#define PWM_EPWM_SWVDELVAL_SWVDELVAL_MAX                                       (0xFFFFU)

#define PWM_EPWM_SWVDELVAL_RESETVAL                                            (0x0000U)

/* RESERVED_26 */

#define PWM_EPWM_RESERVED_26_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_26_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_26_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_26_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_26_RESETVAL                                          (0x0000U)

/* TZSEL */

#define PWM_EPWM_TZSEL_CBC1_MASK                                               (0x0001U)
#define PWM_EPWM_TZSEL_CBC1_SHIFT                                              (0x0000U)
#define PWM_EPWM_TZSEL_CBC1_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZSEL_CBC1_MAX                                                (0x0001U)

#define PWM_EPWM_TZSEL_CBC2_MASK                                               (0x0002U)
#define PWM_EPWM_TZSEL_CBC2_SHIFT                                              (0x0001U)
#define PWM_EPWM_TZSEL_CBC2_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZSEL_CBC2_MAX                                                (0x0001U)

#define PWM_EPWM_TZSEL_CBC3_MASK                                               (0x0004U)
#define PWM_EPWM_TZSEL_CBC3_SHIFT                                              (0x0002U)
#define PWM_EPWM_TZSEL_CBC3_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZSEL_CBC3_MAX                                                (0x0001U)

#define PWM_EPWM_TZSEL_CBC4_MASK                                               (0x0008U)
#define PWM_EPWM_TZSEL_CBC4_SHIFT                                              (0x0003U)
#define PWM_EPWM_TZSEL_CBC4_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZSEL_CBC4_MAX                                                (0x0001U)

#define PWM_EPWM_TZSEL_CBC5_MASK                                               (0x0010U)
#define PWM_EPWM_TZSEL_CBC5_SHIFT                                              (0x0004U)
#define PWM_EPWM_TZSEL_CBC5_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZSEL_CBC5_MAX                                                (0x0001U)

#define PWM_EPWM_TZSEL_CBC6_MASK                                               (0x0020U)
#define PWM_EPWM_TZSEL_CBC6_SHIFT                                              (0x0005U)
#define PWM_EPWM_TZSEL_CBC6_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZSEL_CBC6_MAX                                                (0x0001U)

#define PWM_EPWM_TZSEL_DCAEVT2_MASK                                            (0x0040U)
#define PWM_EPWM_TZSEL_DCAEVT2_SHIFT                                           (0x0006U)
#define PWM_EPWM_TZSEL_DCAEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZSEL_DCAEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZSEL_DCBEVT2_MASK                                            (0x0080U)
#define PWM_EPWM_TZSEL_DCBEVT2_SHIFT                                           (0x0007U)
#define PWM_EPWM_TZSEL_DCBEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZSEL_DCBEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZSEL_OSHT1_MASK                                              (0x0100U)
#define PWM_EPWM_TZSEL_OSHT1_SHIFT                                             (0x0008U)
#define PWM_EPWM_TZSEL_OSHT1_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZSEL_OSHT1_MAX                                               (0x0001U)

#define PWM_EPWM_TZSEL_OSHT2_MASK                                              (0x0200U)
#define PWM_EPWM_TZSEL_OSHT2_SHIFT                                             (0x0009U)
#define PWM_EPWM_TZSEL_OSHT2_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZSEL_OSHT2_MAX                                               (0x0001U)

#define PWM_EPWM_TZSEL_OSHT3_MASK                                              (0x0400U)
#define PWM_EPWM_TZSEL_OSHT3_SHIFT                                             (0x000AU)
#define PWM_EPWM_TZSEL_OSHT3_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZSEL_OSHT3_MAX                                               (0x0001U)

#define PWM_EPWM_TZSEL_OSHT4_MASK                                              (0x0800U)
#define PWM_EPWM_TZSEL_OSHT4_SHIFT                                             (0x000BU)
#define PWM_EPWM_TZSEL_OSHT4_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZSEL_OSHT4_MAX                                               (0x0001U)

#define PWM_EPWM_TZSEL_OSHT5_MASK                                              (0x1000U)
#define PWM_EPWM_TZSEL_OSHT5_SHIFT                                             (0x000CU)
#define PWM_EPWM_TZSEL_OSHT5_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZSEL_OSHT5_MAX                                               (0x0001U)

#define PWM_EPWM_TZSEL_OSHT6_MASK                                              (0x2000U)
#define PWM_EPWM_TZSEL_OSHT6_SHIFT                                             (0x000DU)
#define PWM_EPWM_TZSEL_OSHT6_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZSEL_OSHT6_MAX                                               (0x0001U)

#define PWM_EPWM_TZSEL_DCAEVT1_MASK                                            (0x4000U)
#define PWM_EPWM_TZSEL_DCAEVT1_SHIFT                                           (0x000EU)
#define PWM_EPWM_TZSEL_DCAEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZSEL_DCAEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZSEL_DCBEVT1_MASK                                            (0x8000U)
#define PWM_EPWM_TZSEL_DCBEVT1_SHIFT                                           (0x000FU)
#define PWM_EPWM_TZSEL_DCBEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZSEL_DCBEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZSEL_RESETVAL                                                (0x0000U)

/* TZSEL2 */

#define PWM_EPWM_TZSEL2_CAPEVTCBC_MASK                                         (0x0001U)
#define PWM_EPWM_TZSEL2_CAPEVTCBC_SHIFT                                        (0x0000U)
#define PWM_EPWM_TZSEL2_CAPEVTCBC_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZSEL2_CAPEVTCBC_MAX                                          (0x0001U)

#define PWM_EPWM_TZSEL2_RESERVED_1_MASK                                        (0x00FEU)
#define PWM_EPWM_TZSEL2_RESERVED_1_SHIFT                                       (0x0001U)
#define PWM_EPWM_TZSEL2_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZSEL2_RESERVED_1_MAX                                         (0x007FU)

#define PWM_EPWM_TZSEL2_CAPEVTOST_MASK                                         (0x0100U)
#define PWM_EPWM_TZSEL2_CAPEVTOST_SHIFT                                        (0x0008U)
#define PWM_EPWM_TZSEL2_CAPEVTOST_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZSEL2_CAPEVTOST_MAX                                          (0x0001U)

#define PWM_EPWM_TZSEL2_RESERVED_2_MASK                                        (0xFE00U)
#define PWM_EPWM_TZSEL2_RESERVED_2_SHIFT                                       (0x0009U)
#define PWM_EPWM_TZSEL2_RESERVED_2_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZSEL2_RESERVED_2_MAX                                         (0x007FU)

#define PWM_EPWM_TZSEL2_RESETVAL                                               (0x0000U)

/* TZDCSEL */

#define PWM_EPWM_TZDCSEL_DCAEVT1_MASK                                          (0x0007U)
#define PWM_EPWM_TZDCSEL_DCAEVT1_SHIFT                                         (0x0000U)
#define PWM_EPWM_TZDCSEL_DCAEVT1_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZDCSEL_DCAEVT1_MAX                                           (0x0007U)

#define PWM_EPWM_TZDCSEL_DCAEVT2_MASK                                          (0x0038U)
#define PWM_EPWM_TZDCSEL_DCAEVT2_SHIFT                                         (0x0003U)
#define PWM_EPWM_TZDCSEL_DCAEVT2_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZDCSEL_DCAEVT2_MAX                                           (0x0007U)

#define PWM_EPWM_TZDCSEL_DCBEVT1_MASK                                          (0x01C0U)
#define PWM_EPWM_TZDCSEL_DCBEVT1_SHIFT                                         (0x0006U)
#define PWM_EPWM_TZDCSEL_DCBEVT1_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZDCSEL_DCBEVT1_MAX                                           (0x0007U)

#define PWM_EPWM_TZDCSEL_DCBEVT2_MASK                                          (0x0E00U)
#define PWM_EPWM_TZDCSEL_DCBEVT2_SHIFT                                         (0x0009U)
#define PWM_EPWM_TZDCSEL_DCBEVT2_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZDCSEL_DCBEVT2_MAX                                           (0x0007U)

#define PWM_EPWM_TZDCSEL_RESERVED_1_MASK                                       (0xF000U)
#define PWM_EPWM_TZDCSEL_RESERVED_1_SHIFT                                      (0x000CU)
#define PWM_EPWM_TZDCSEL_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_TZDCSEL_RESERVED_1_MAX                                        (0x000FU)

#define PWM_EPWM_TZDCSEL_RESETVAL                                              (0x0000U)

/* RESERVED_27 */

#define PWM_EPWM_RESERVED_27_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_27_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_27_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_27_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_27_RESETVAL                                          (0x0000U)

/* TZCTL */

#define PWM_EPWM_TZCTL_TZA_MASK                                                (0x0003U)
#define PWM_EPWM_TZCTL_TZA_SHIFT                                               (0x0000U)
#define PWM_EPWM_TZCTL_TZA_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZCTL_TZA_MAX                                                 (0x0003U)

#define PWM_EPWM_TZCTL_TZB_MASK                                                (0x000CU)
#define PWM_EPWM_TZCTL_TZB_SHIFT                                               (0x0002U)
#define PWM_EPWM_TZCTL_TZB_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZCTL_TZB_MAX                                                 (0x0003U)

#define PWM_EPWM_TZCTL_DCAEVT1_MASK                                            (0x0030U)
#define PWM_EPWM_TZCTL_DCAEVT1_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZCTL_DCAEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCTL_DCAEVT1_MAX                                             (0x0003U)

#define PWM_EPWM_TZCTL_DCAEVT2_MASK                                            (0x00C0U)
#define PWM_EPWM_TZCTL_DCAEVT2_SHIFT                                           (0x0006U)
#define PWM_EPWM_TZCTL_DCAEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCTL_DCAEVT2_MAX                                             (0x0003U)

#define PWM_EPWM_TZCTL_DCBEVT1_MASK                                            (0x0300U)
#define PWM_EPWM_TZCTL_DCBEVT1_SHIFT                                           (0x0008U)
#define PWM_EPWM_TZCTL_DCBEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCTL_DCBEVT1_MAX                                             (0x0003U)

#define PWM_EPWM_TZCTL_DCBEVT2_MASK                                            (0x0C00U)
#define PWM_EPWM_TZCTL_DCBEVT2_SHIFT                                           (0x000AU)
#define PWM_EPWM_TZCTL_DCBEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCTL_DCBEVT2_MAX                                             (0x0003U)

#define PWM_EPWM_TZCTL_RESERVED_1_MASK                                         (0xF000U)
#define PWM_EPWM_TZCTL_RESERVED_1_SHIFT                                        (0x000CU)
#define PWM_EPWM_TZCTL_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZCTL_RESERVED_1_MAX                                          (0x000FU)

#define PWM_EPWM_TZCTL_RESETVAL                                                (0x0000U)

/* TZCTL2 */

#define PWM_EPWM_TZCTL2_TZAU_MASK                                              (0x0007U)
#define PWM_EPWM_TZCTL2_TZAU_SHIFT                                             (0x0000U)
#define PWM_EPWM_TZCTL2_TZAU_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZCTL2_TZAU_MAX                                               (0x0007U)

#define PWM_EPWM_TZCTL2_TZAD_MASK                                              (0x0038U)
#define PWM_EPWM_TZCTL2_TZAD_SHIFT                                             (0x0003U)
#define PWM_EPWM_TZCTL2_TZAD_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZCTL2_TZAD_MAX                                               (0x0007U)

#define PWM_EPWM_TZCTL2_TZBU_MASK                                              (0x01C0U)
#define PWM_EPWM_TZCTL2_TZBU_SHIFT                                             (0x0006U)
#define PWM_EPWM_TZCTL2_TZBU_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZCTL2_TZBU_MAX                                               (0x0007U)

#define PWM_EPWM_TZCTL2_TZBD_MASK                                              (0x0E00U)
#define PWM_EPWM_TZCTL2_TZBD_SHIFT                                             (0x0009U)
#define PWM_EPWM_TZCTL2_TZBD_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZCTL2_TZBD_MAX                                               (0x0007U)

#define PWM_EPWM_TZCTL2_RESERVED_1_MASK                                        (0x7000U)
#define PWM_EPWM_TZCTL2_RESERVED_1_SHIFT                                       (0x000CU)
#define PWM_EPWM_TZCTL2_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTL2_RESERVED_1_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTL2_ETZE_MASK                                              (0x8000U)
#define PWM_EPWM_TZCTL2_ETZE_SHIFT                                             (0x000FU)
#define PWM_EPWM_TZCTL2_ETZE_RESETVAL                                          (0x0000U)
#define PWM_EPWM_TZCTL2_ETZE_MAX                                               (0x0001U)

#define PWM_EPWM_TZCTL2_RESETVAL                                               (0x0000U)

/* TZCTLDCA */

#define PWM_EPWM_TZCTLDCA_DCAEVT1U_MASK                                        (0x0007U)
#define PWM_EPWM_TZCTLDCA_DCAEVT1U_SHIFT                                       (0x0000U)
#define PWM_EPWM_TZCTLDCA_DCAEVT1U_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCA_DCAEVT1U_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCA_DCAEVT1D_MASK                                        (0x0038U)
#define PWM_EPWM_TZCTLDCA_DCAEVT1D_SHIFT                                       (0x0003U)
#define PWM_EPWM_TZCTLDCA_DCAEVT1D_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCA_DCAEVT1D_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCA_DCAEVT2U_MASK                                        (0x01C0U)
#define PWM_EPWM_TZCTLDCA_DCAEVT2U_SHIFT                                       (0x0006U)
#define PWM_EPWM_TZCTLDCA_DCAEVT2U_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCA_DCAEVT2U_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCA_DCAEVT2D_MASK                                        (0x0E00U)
#define PWM_EPWM_TZCTLDCA_DCAEVT2D_SHIFT                                       (0x0009U)
#define PWM_EPWM_TZCTLDCA_DCAEVT2D_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCA_DCAEVT2D_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCA_RESERVED_1_MASK                                      (0xF000U)
#define PWM_EPWM_TZCTLDCA_RESERVED_1_SHIFT                                     (0x000CU)
#define PWM_EPWM_TZCTLDCA_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TZCTLDCA_RESERVED_1_MAX                                       (0x000FU)

#define PWM_EPWM_TZCTLDCA_RESETVAL                                             (0x0000U)

/* TZCTLDCB */

#define PWM_EPWM_TZCTLDCB_DCBEVT1U_MASK                                        (0x0007U)
#define PWM_EPWM_TZCTLDCB_DCBEVT1U_SHIFT                                       (0x0000U)
#define PWM_EPWM_TZCTLDCB_DCBEVT1U_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCB_DCBEVT1U_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCB_DCBEVT1D_MASK                                        (0x0038U)
#define PWM_EPWM_TZCTLDCB_DCBEVT1D_SHIFT                                       (0x0003U)
#define PWM_EPWM_TZCTLDCB_DCBEVT1D_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCB_DCBEVT1D_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCB_DCBEVT2U_MASK                                        (0x01C0U)
#define PWM_EPWM_TZCTLDCB_DCBEVT2U_SHIFT                                       (0x0006U)
#define PWM_EPWM_TZCTLDCB_DCBEVT2U_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCB_DCBEVT2U_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCB_DCBEVT2D_MASK                                        (0x0E00U)
#define PWM_EPWM_TZCTLDCB_DCBEVT2D_SHIFT                                       (0x0009U)
#define PWM_EPWM_TZCTLDCB_DCBEVT2D_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZCTLDCB_DCBEVT2D_MAX                                         (0x0007U)

#define PWM_EPWM_TZCTLDCB_RESERVED_1_MASK                                      (0xF000U)
#define PWM_EPWM_TZCTLDCB_RESERVED_1_SHIFT                                     (0x000CU)
#define PWM_EPWM_TZCTLDCB_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TZCTLDCB_RESERVED_1_MAX                                       (0x000FU)

#define PWM_EPWM_TZCTLDCB_RESETVAL                                             (0x0000U)

/* RESERVED_28 */

#define PWM_EPWM_RESERVED_28_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_28_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_28_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_28_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_28_RESETVAL                                          (0x0000U)

/* TZEINT */

#define PWM_EPWM_TZEINT_RESERVED_1_MASK                                        (0x0001U)
#define PWM_EPWM_TZEINT_RESERVED_1_SHIFT                                       (0x0000U)
#define PWM_EPWM_TZEINT_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZEINT_RESERVED_1_MAX                                         (0x0001U)

#define PWM_EPWM_TZEINT_CBC_MASK                                               (0x0002U)
#define PWM_EPWM_TZEINT_CBC_SHIFT                                              (0x0001U)
#define PWM_EPWM_TZEINT_CBC_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZEINT_CBC_MAX                                                (0x0001U)

#define PWM_EPWM_TZEINT_OST_MASK                                               (0x0004U)
#define PWM_EPWM_TZEINT_OST_SHIFT                                              (0x0002U)
#define PWM_EPWM_TZEINT_OST_RESETVAL                                           (0x0000U)
#define PWM_EPWM_TZEINT_OST_MAX                                                (0x0001U)

#define PWM_EPWM_TZEINT_DCAEVT1_MASK                                           (0x0008U)
#define PWM_EPWM_TZEINT_DCAEVT1_SHIFT                                          (0x0003U)
#define PWM_EPWM_TZEINT_DCAEVT1_RESETVAL                                       (0x0000U)
#define PWM_EPWM_TZEINT_DCAEVT1_MAX                                            (0x0001U)

#define PWM_EPWM_TZEINT_DCAEVT2_MASK                                           (0x0010U)
#define PWM_EPWM_TZEINT_DCAEVT2_SHIFT                                          (0x0004U)
#define PWM_EPWM_TZEINT_DCAEVT2_RESETVAL                                       (0x0000U)
#define PWM_EPWM_TZEINT_DCAEVT2_MAX                                            (0x0001U)

#define PWM_EPWM_TZEINT_DCBEVT1_MASK                                           (0x0020U)
#define PWM_EPWM_TZEINT_DCBEVT1_SHIFT                                          (0x0005U)
#define PWM_EPWM_TZEINT_DCBEVT1_RESETVAL                                       (0x0000U)
#define PWM_EPWM_TZEINT_DCBEVT1_MAX                                            (0x0001U)

#define PWM_EPWM_TZEINT_DCBEVT2_MASK                                           (0x0040U)
#define PWM_EPWM_TZEINT_DCBEVT2_SHIFT                                          (0x0006U)
#define PWM_EPWM_TZEINT_DCBEVT2_RESETVAL                                       (0x0000U)
#define PWM_EPWM_TZEINT_DCBEVT2_MAX                                            (0x0001U)

#define PWM_EPWM_TZEINT_CAPEVT_MASK                                            (0x0080U)
#define PWM_EPWM_TZEINT_CAPEVT_SHIFT                                           (0x0007U)
#define PWM_EPWM_TZEINT_CAPEVT_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZEINT_CAPEVT_MAX                                             (0x0001U)

#define PWM_EPWM_TZEINT_RESERVED_2_MASK                                        (0xFF00U)
#define PWM_EPWM_TZEINT_RESERVED_2_SHIFT                                       (0x0008U)
#define PWM_EPWM_TZEINT_RESERVED_2_RESETVAL                                    (0x0000U)
#define PWM_EPWM_TZEINT_RESERVED_2_MAX                                         (0x00FFU)

#define PWM_EPWM_TZEINT_RESETVAL                                               (0x0000U)

/* RESERVED_29 */

#define PWM_EPWM_RESERVED_29_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_29_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_29_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_29_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_29_RESETVAL                                          (0x0000U)

/* TZFLG */

#define PWM_EPWM_TZFLG_INT_MASK                                                (0x0001U)
#define PWM_EPWM_TZFLG_INT_SHIFT                                               (0x0000U)
#define PWM_EPWM_TZFLG_INT_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZFLG_INT_MAX                                                 (0x0001U)

#define PWM_EPWM_TZFLG_CBC_MASK                                                (0x0002U)
#define PWM_EPWM_TZFLG_CBC_SHIFT                                               (0x0001U)
#define PWM_EPWM_TZFLG_CBC_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZFLG_CBC_MAX                                                 (0x0001U)

#define PWM_EPWM_TZFLG_OST_MASK                                                (0x0004U)
#define PWM_EPWM_TZFLG_OST_SHIFT                                               (0x0002U)
#define PWM_EPWM_TZFLG_OST_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZFLG_OST_MAX                                                 (0x0001U)

#define PWM_EPWM_TZFLG_DCAEVT1_MASK                                            (0x0008U)
#define PWM_EPWM_TZFLG_DCAEVT1_SHIFT                                           (0x0003U)
#define PWM_EPWM_TZFLG_DCAEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFLG_DCAEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZFLG_DCAEVT2_MASK                                            (0x0010U)
#define PWM_EPWM_TZFLG_DCAEVT2_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZFLG_DCAEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFLG_DCAEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZFLG_DCBEVT1_MASK                                            (0x0020U)
#define PWM_EPWM_TZFLG_DCBEVT1_SHIFT                                           (0x0005U)
#define PWM_EPWM_TZFLG_DCBEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFLG_DCBEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZFLG_DCBEVT2_MASK                                            (0x0040U)
#define PWM_EPWM_TZFLG_DCBEVT2_SHIFT                                           (0x0006U)
#define PWM_EPWM_TZFLG_DCBEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFLG_DCBEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZFLG_CAPEVT_MASK                                             (0x0080U)
#define PWM_EPWM_TZFLG_CAPEVT_SHIFT                                            (0x0007U)
#define PWM_EPWM_TZFLG_CAPEVT_RESETVAL                                         (0x0000U)
#define PWM_EPWM_TZFLG_CAPEVT_MAX                                              (0x0001U)

#define PWM_EPWM_TZFLG_RESERVED_1_MASK                                         (0xFF00U)
#define PWM_EPWM_TZFLG_RESERVED_1_SHIFT                                        (0x0008U)
#define PWM_EPWM_TZFLG_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZFLG_RESERVED_1_MAX                                          (0x00FFU)

#define PWM_EPWM_TZFLG_RESETVAL                                                (0x0000U)

/* TZCBCFLG */

#define PWM_EPWM_TZCBCFLG_CBC1_MASK                                            (0x0001U)
#define PWM_EPWM_TZCBCFLG_CBC1_SHIFT                                           (0x0000U)
#define PWM_EPWM_TZCBCFLG_CBC1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCFLG_CBC1_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCFLG_CBC2_MASK                                            (0x0002U)
#define PWM_EPWM_TZCBCFLG_CBC2_SHIFT                                           (0x0001U)
#define PWM_EPWM_TZCBCFLG_CBC2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCFLG_CBC2_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCFLG_CBC3_MASK                                            (0x0004U)
#define PWM_EPWM_TZCBCFLG_CBC3_SHIFT                                           (0x0002U)
#define PWM_EPWM_TZCBCFLG_CBC3_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCFLG_CBC3_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCFLG_CBC4_MASK                                            (0x0008U)
#define PWM_EPWM_TZCBCFLG_CBC4_SHIFT                                           (0x0003U)
#define PWM_EPWM_TZCBCFLG_CBC4_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCFLG_CBC4_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCFLG_CBC5_MASK                                            (0x0010U)
#define PWM_EPWM_TZCBCFLG_CBC5_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZCBCFLG_CBC5_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCFLG_CBC5_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCFLG_CBC6_MASK                                            (0x0020U)
#define PWM_EPWM_TZCBCFLG_CBC6_SHIFT                                           (0x0005U)
#define PWM_EPWM_TZCBCFLG_CBC6_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCFLG_CBC6_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCFLG_DCAEVT2_MASK                                         (0x0040U)
#define PWM_EPWM_TZCBCFLG_DCAEVT2_SHIFT                                        (0x0006U)
#define PWM_EPWM_TZCBCFLG_DCAEVT2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZCBCFLG_DCAEVT2_MAX                                          (0x0001U)

#define PWM_EPWM_TZCBCFLG_DCBEVT2_MASK                                         (0x0080U)
#define PWM_EPWM_TZCBCFLG_DCBEVT2_SHIFT                                        (0x0007U)
#define PWM_EPWM_TZCBCFLG_DCBEVT2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZCBCFLG_DCBEVT2_MAX                                          (0x0001U)

#define PWM_EPWM_TZCBCFLG_CAPEVT_MASK                                          (0x0100U)
#define PWM_EPWM_TZCBCFLG_CAPEVT_SHIFT                                         (0x0008U)
#define PWM_EPWM_TZCBCFLG_CAPEVT_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZCBCFLG_CAPEVT_MAX                                           (0x0001U)

#define PWM_EPWM_TZCBCFLG_RESERVED_1_MASK                                      (0xFE00U)
#define PWM_EPWM_TZCBCFLG_RESERVED_1_SHIFT                                     (0x0009U)
#define PWM_EPWM_TZCBCFLG_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TZCBCFLG_RESERVED_1_MAX                                       (0x007FU)

#define PWM_EPWM_TZCBCFLG_RESETVAL                                             (0x0000U)

/* TZOSTFLG */

#define PWM_EPWM_TZOSTFLG_OST1_MASK                                            (0x0001U)
#define PWM_EPWM_TZOSTFLG_OST1_SHIFT                                           (0x0000U)
#define PWM_EPWM_TZOSTFLG_OST1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTFLG_OST1_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTFLG_OST2_MASK                                            (0x0002U)
#define PWM_EPWM_TZOSTFLG_OST2_SHIFT                                           (0x0001U)
#define PWM_EPWM_TZOSTFLG_OST2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTFLG_OST2_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTFLG_OST3_MASK                                            (0x0004U)
#define PWM_EPWM_TZOSTFLG_OST3_SHIFT                                           (0x0002U)
#define PWM_EPWM_TZOSTFLG_OST3_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTFLG_OST3_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTFLG_OST4_MASK                                            (0x0008U)
#define PWM_EPWM_TZOSTFLG_OST4_SHIFT                                           (0x0003U)
#define PWM_EPWM_TZOSTFLG_OST4_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTFLG_OST4_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTFLG_OST5_MASK                                            (0x0010U)
#define PWM_EPWM_TZOSTFLG_OST5_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZOSTFLG_OST5_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTFLG_OST5_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTFLG_OST6_MASK                                            (0x0020U)
#define PWM_EPWM_TZOSTFLG_OST6_SHIFT                                           (0x0005U)
#define PWM_EPWM_TZOSTFLG_OST6_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTFLG_OST6_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTFLG_DCAEVT1_MASK                                         (0x0040U)
#define PWM_EPWM_TZOSTFLG_DCAEVT1_SHIFT                                        (0x0006U)
#define PWM_EPWM_TZOSTFLG_DCAEVT1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZOSTFLG_DCAEVT1_MAX                                          (0x0001U)

#define PWM_EPWM_TZOSTFLG_DCBEVT1_MASK                                         (0x0080U)
#define PWM_EPWM_TZOSTFLG_DCBEVT1_SHIFT                                        (0x0007U)
#define PWM_EPWM_TZOSTFLG_DCBEVT1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZOSTFLG_DCBEVT1_MAX                                          (0x0001U)

#define PWM_EPWM_TZOSTFLG_CAPEVT_MASK                                          (0x0100U)
#define PWM_EPWM_TZOSTFLG_CAPEVT_SHIFT                                         (0x0008U)
#define PWM_EPWM_TZOSTFLG_CAPEVT_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZOSTFLG_CAPEVT_MAX                                           (0x0001U)

#define PWM_EPWM_TZOSTFLG_RESERVED_1_MASK                                      (0xFE00U)
#define PWM_EPWM_TZOSTFLG_RESERVED_1_SHIFT                                     (0x0009U)
#define PWM_EPWM_TZOSTFLG_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TZOSTFLG_RESERVED_1_MAX                                       (0x007FU)

#define PWM_EPWM_TZOSTFLG_RESETVAL                                             (0x0000U)

/* RESERVED_30 */

#define PWM_EPWM_RESERVED_30_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_30_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_30_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_30_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_30_RESETVAL                                          (0x0000U)

/* TZCLR */

#define PWM_EPWM_TZCLR_INT_MASK                                                (0x0001U)
#define PWM_EPWM_TZCLR_INT_SHIFT                                               (0x0000U)
#define PWM_EPWM_TZCLR_INT_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZCLR_INT_MAX                                                 (0x0001U)

#define PWM_EPWM_TZCLR_CBC_MASK                                                (0x0002U)
#define PWM_EPWM_TZCLR_CBC_SHIFT                                               (0x0001U)
#define PWM_EPWM_TZCLR_CBC_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZCLR_CBC_MAX                                                 (0x0001U)

#define PWM_EPWM_TZCLR_OST_MASK                                                (0x0004U)
#define PWM_EPWM_TZCLR_OST_SHIFT                                               (0x0002U)
#define PWM_EPWM_TZCLR_OST_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZCLR_OST_MAX                                                 (0x0001U)

#define PWM_EPWM_TZCLR_DCAEVT1_MASK                                            (0x0008U)
#define PWM_EPWM_TZCLR_DCAEVT1_SHIFT                                           (0x0003U)
#define PWM_EPWM_TZCLR_DCAEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCLR_DCAEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZCLR_DCAEVT2_MASK                                            (0x0010U)
#define PWM_EPWM_TZCLR_DCAEVT2_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZCLR_DCAEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCLR_DCAEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZCLR_DCBEVT1_MASK                                            (0x0020U)
#define PWM_EPWM_TZCLR_DCBEVT1_SHIFT                                           (0x0005U)
#define PWM_EPWM_TZCLR_DCBEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCLR_DCBEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZCLR_DCBEVT2_MASK                                            (0x0040U)
#define PWM_EPWM_TZCLR_DCBEVT2_SHIFT                                           (0x0006U)
#define PWM_EPWM_TZCLR_DCBEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCLR_DCBEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZCLR_CAPEVT_MASK                                             (0x0080U)
#define PWM_EPWM_TZCLR_CAPEVT_SHIFT                                            (0x0007U)
#define PWM_EPWM_TZCLR_CAPEVT_RESETVAL                                         (0x0000U)
#define PWM_EPWM_TZCLR_CAPEVT_MAX                                              (0x0001U)

#define PWM_EPWM_TZCLR_RESERVED_1_MASK                                         (0x3F00U)
#define PWM_EPWM_TZCLR_RESERVED_1_SHIFT                                        (0x0008U)
#define PWM_EPWM_TZCLR_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZCLR_RESERVED_1_MAX                                          (0x003FU)

#define PWM_EPWM_TZCLR_CBCPULSE_MASK                                           (0xC000U)
#define PWM_EPWM_TZCLR_CBCPULSE_SHIFT                                          (0x000EU)
#define PWM_EPWM_TZCLR_CBCPULSE_RESETVAL                                       (0x0000U)
#define PWM_EPWM_TZCLR_CBCPULSE_MAX                                            (0x0003U)

#define PWM_EPWM_TZCLR_RESETVAL                                                (0x0000U)

/* TZCBCCLR */

#define PWM_EPWM_TZCBCCLR_CBC1_MASK                                            (0x0001U)
#define PWM_EPWM_TZCBCCLR_CBC1_SHIFT                                           (0x0000U)
#define PWM_EPWM_TZCBCCLR_CBC1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCCLR_CBC1_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCCLR_CBC2_MASK                                            (0x0002U)
#define PWM_EPWM_TZCBCCLR_CBC2_SHIFT                                           (0x0001U)
#define PWM_EPWM_TZCBCCLR_CBC2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCCLR_CBC2_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCCLR_CBC3_MASK                                            (0x0004U)
#define PWM_EPWM_TZCBCCLR_CBC3_SHIFT                                           (0x0002U)
#define PWM_EPWM_TZCBCCLR_CBC3_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCCLR_CBC3_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCCLR_CBC4_MASK                                            (0x0008U)
#define PWM_EPWM_TZCBCCLR_CBC4_SHIFT                                           (0x0003U)
#define PWM_EPWM_TZCBCCLR_CBC4_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCCLR_CBC4_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCCLR_CBC5_MASK                                            (0x0010U)
#define PWM_EPWM_TZCBCCLR_CBC5_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZCBCCLR_CBC5_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCCLR_CBC5_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCCLR_CBC6_MASK                                            (0x0020U)
#define PWM_EPWM_TZCBCCLR_CBC6_SHIFT                                           (0x0005U)
#define PWM_EPWM_TZCBCCLR_CBC6_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZCBCCLR_CBC6_MAX                                             (0x0001U)

#define PWM_EPWM_TZCBCCLR_DCAEVT2_MASK                                         (0x0040U)
#define PWM_EPWM_TZCBCCLR_DCAEVT2_SHIFT                                        (0x0006U)
#define PWM_EPWM_TZCBCCLR_DCAEVT2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZCBCCLR_DCAEVT2_MAX                                          (0x0001U)

#define PWM_EPWM_TZCBCCLR_DCBEVT2_MASK                                         (0x0080U)
#define PWM_EPWM_TZCBCCLR_DCBEVT2_SHIFT                                        (0x0007U)
#define PWM_EPWM_TZCBCCLR_DCBEVT2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZCBCCLR_DCBEVT2_MAX                                          (0x0001U)

#define PWM_EPWM_TZCBCCLR_CAPEVT_MASK                                          (0x0100U)
#define PWM_EPWM_TZCBCCLR_CAPEVT_SHIFT                                         (0x0008U)
#define PWM_EPWM_TZCBCCLR_CAPEVT_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZCBCCLR_CAPEVT_MAX                                           (0x0001U)

#define PWM_EPWM_TZCBCCLR_RESERVED_1_MASK                                      (0xFE00U)
#define PWM_EPWM_TZCBCCLR_RESERVED_1_SHIFT                                     (0x0009U)
#define PWM_EPWM_TZCBCCLR_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TZCBCCLR_RESERVED_1_MAX                                       (0x007FU)

#define PWM_EPWM_TZCBCCLR_RESETVAL                                             (0x0000U)

/* TZOSTCLR */

#define PWM_EPWM_TZOSTCLR_OST1_MASK                                            (0x0001U)
#define PWM_EPWM_TZOSTCLR_OST1_SHIFT                                           (0x0000U)
#define PWM_EPWM_TZOSTCLR_OST1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTCLR_OST1_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTCLR_OST2_MASK                                            (0x0002U)
#define PWM_EPWM_TZOSTCLR_OST2_SHIFT                                           (0x0001U)
#define PWM_EPWM_TZOSTCLR_OST2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTCLR_OST2_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTCLR_OST3_MASK                                            (0x0004U)
#define PWM_EPWM_TZOSTCLR_OST3_SHIFT                                           (0x0002U)
#define PWM_EPWM_TZOSTCLR_OST3_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTCLR_OST3_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTCLR_OST4_MASK                                            (0x0008U)
#define PWM_EPWM_TZOSTCLR_OST4_SHIFT                                           (0x0003U)
#define PWM_EPWM_TZOSTCLR_OST4_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTCLR_OST4_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTCLR_OST5_MASK                                            (0x0010U)
#define PWM_EPWM_TZOSTCLR_OST5_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZOSTCLR_OST5_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTCLR_OST5_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTCLR_OST6_MASK                                            (0x0020U)
#define PWM_EPWM_TZOSTCLR_OST6_SHIFT                                           (0x0005U)
#define PWM_EPWM_TZOSTCLR_OST6_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZOSTCLR_OST6_MAX                                             (0x0001U)

#define PWM_EPWM_TZOSTCLR_DCAEVT1_MASK                                         (0x0040U)
#define PWM_EPWM_TZOSTCLR_DCAEVT1_SHIFT                                        (0x0006U)
#define PWM_EPWM_TZOSTCLR_DCAEVT1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZOSTCLR_DCAEVT1_MAX                                          (0x0001U)

#define PWM_EPWM_TZOSTCLR_DCBEVT1_MASK                                         (0x0080U)
#define PWM_EPWM_TZOSTCLR_DCBEVT1_SHIFT                                        (0x0007U)
#define PWM_EPWM_TZOSTCLR_DCBEVT1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZOSTCLR_DCBEVT1_MAX                                          (0x0001U)

#define PWM_EPWM_TZOSTCLR_CAPEVT_MASK                                          (0x0100U)
#define PWM_EPWM_TZOSTCLR_CAPEVT_SHIFT                                         (0x0008U)
#define PWM_EPWM_TZOSTCLR_CAPEVT_RESETVAL                                      (0x0000U)
#define PWM_EPWM_TZOSTCLR_CAPEVT_MAX                                           (0x0001U)

#define PWM_EPWM_TZOSTCLR_RESERVED_1_MASK                                      (0xFE00U)
#define PWM_EPWM_TZOSTCLR_RESERVED_1_SHIFT                                     (0x0009U)
#define PWM_EPWM_TZOSTCLR_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TZOSTCLR_RESERVED_1_MAX                                       (0x007FU)

#define PWM_EPWM_TZOSTCLR_RESETVAL                                             (0x0000U)

/* RESERVED_31 */

#define PWM_EPWM_RESERVED_31_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_31_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_31_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_31_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_31_RESETVAL                                          (0x0000U)

/* TZFRC */

#define PWM_EPWM_TZFRC_RESERVED_1_MASK                                         (0x0001U)
#define PWM_EPWM_TZFRC_RESERVED_1_SHIFT                                        (0x0000U)
#define PWM_EPWM_TZFRC_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZFRC_RESERVED_1_MAX                                          (0x0001U)

#define PWM_EPWM_TZFRC_CBC_MASK                                                (0x0002U)
#define PWM_EPWM_TZFRC_CBC_SHIFT                                               (0x0001U)
#define PWM_EPWM_TZFRC_CBC_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZFRC_CBC_MAX                                                 (0x0001U)

#define PWM_EPWM_TZFRC_OST_MASK                                                (0x0004U)
#define PWM_EPWM_TZFRC_OST_SHIFT                                               (0x0002U)
#define PWM_EPWM_TZFRC_OST_RESETVAL                                            (0x0000U)
#define PWM_EPWM_TZFRC_OST_MAX                                                 (0x0001U)

#define PWM_EPWM_TZFRC_DCAEVT1_MASK                                            (0x0008U)
#define PWM_EPWM_TZFRC_DCAEVT1_SHIFT                                           (0x0003U)
#define PWM_EPWM_TZFRC_DCAEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFRC_DCAEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZFRC_DCAEVT2_MASK                                            (0x0010U)
#define PWM_EPWM_TZFRC_DCAEVT2_SHIFT                                           (0x0004U)
#define PWM_EPWM_TZFRC_DCAEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFRC_DCAEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZFRC_DCBEVT1_MASK                                            (0x0020U)
#define PWM_EPWM_TZFRC_DCBEVT1_SHIFT                                           (0x0005U)
#define PWM_EPWM_TZFRC_DCBEVT1_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFRC_DCBEVT1_MAX                                             (0x0001U)

#define PWM_EPWM_TZFRC_DCBEVT2_MASK                                            (0x0040U)
#define PWM_EPWM_TZFRC_DCBEVT2_SHIFT                                           (0x0006U)
#define PWM_EPWM_TZFRC_DCBEVT2_RESETVAL                                        (0x0000U)
#define PWM_EPWM_TZFRC_DCBEVT2_MAX                                             (0x0001U)

#define PWM_EPWM_TZFRC_CAPEVT_MASK                                             (0x0080U)
#define PWM_EPWM_TZFRC_CAPEVT_SHIFT                                            (0x0007U)
#define PWM_EPWM_TZFRC_CAPEVT_RESETVAL                                         (0x0000U)
#define PWM_EPWM_TZFRC_CAPEVT_MAX                                              (0x0001U)

#define PWM_EPWM_TZFRC_RESERVED_2_MASK                                         (0xFF00U)
#define PWM_EPWM_TZFRC_RESERVED_2_SHIFT                                        (0x0008U)
#define PWM_EPWM_TZFRC_RESERVED_2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZFRC_RESERVED_2_MAX                                          (0x00FFU)

#define PWM_EPWM_TZFRC_RESETVAL                                                (0x0000U)

/* RESERVED_32 */

#define PWM_EPWM_RESERVED_32_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_32_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_32_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_32_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_32_RESETVAL                                          (0x0000U)

/* TZTRIPOUTSEL */

#define PWM_EPWM_TZTRIPOUTSEL_OST_MASK                                         (0x0001U)
#define PWM_EPWM_TZTRIPOUTSEL_OST_SHIFT                                        (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_OST_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_OST_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_CBC_MASK                                         (0x0002U)
#define PWM_EPWM_TZTRIPOUTSEL_CBC_SHIFT                                        (0x0001U)
#define PWM_EPWM_TZTRIPOUTSEL_CBC_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_CBC_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_TZ1_MASK                                         (0x0004U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ1_SHIFT                                        (0x0002U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ1_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_TZ2_MASK                                         (0x0008U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ2_SHIFT                                        (0x0003U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ2_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_TZ3_MASK                                         (0x0010U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ3_SHIFT                                        (0x0004U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ3_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ3_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_TZ4_MASK                                         (0x0020U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ4_SHIFT                                        (0x0005U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ4_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ4_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_TZ5_MASK                                         (0x0040U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ5_SHIFT                                        (0x0006U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ5_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ5_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_TZ6_MASK                                         (0x0080U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ6_SHIFT                                        (0x0007U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ6_RESETVAL                                     (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_TZ6_MAX                                          (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT1_MASK                                     (0x0100U)
#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT1_SHIFT                                    (0x0008U)
#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT1_RESETVAL                                 (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT1_MAX                                      (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT2_MASK                                     (0x0200U)
#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT2_SHIFT                                    (0x0009U)
#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT2_RESETVAL                                 (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_DCAEVT2_MAX                                      (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT1_MASK                                     (0x0400U)
#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT1_SHIFT                                    (0x000AU)
#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT1_RESETVAL                                 (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT1_MAX                                      (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT2_MASK                                     (0x0800U)
#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT2_SHIFT                                    (0x000BU)
#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT2_RESETVAL                                 (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_DCBEVT2_MAX                                      (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_CAPEVT_MASK                                      (0x1000U)
#define PWM_EPWM_TZTRIPOUTSEL_CAPEVT_SHIFT                                     (0x000CU)
#define PWM_EPWM_TZTRIPOUTSEL_CAPEVT_RESETVAL                                  (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_CAPEVT_MAX                                       (0x0001U)

#define PWM_EPWM_TZTRIPOUTSEL_RESERVED_1_MASK                                  (0xE000U)
#define PWM_EPWM_TZTRIPOUTSEL_RESERVED_1_SHIFT                                 (0x000DU)
#define PWM_EPWM_TZTRIPOUTSEL_RESERVED_1_RESETVAL                              (0x0000U)
#define PWM_EPWM_TZTRIPOUTSEL_RESERVED_1_MAX                                   (0x0007U)

#define PWM_EPWM_TZTRIPOUTSEL_RESETVAL                                         (0x0000U)

/* RESERVED_33 */

#define PWM_EPWM_RESERVED_33_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_33_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_33_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_33_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_33_RESETVAL                                          (0x0000U)

/* ETSEL */

#define PWM_EPWM_ETSEL_INTSEL_MASK                                             (0x0007U)
#define PWM_EPWM_ETSEL_INTSEL_SHIFT                                            (0x0000U)
#define PWM_EPWM_ETSEL_INTSEL_RESETVAL                                         (0x0000U)
#define PWM_EPWM_ETSEL_INTSEL_MAX                                              (0x0007U)

#define PWM_EPWM_ETSEL_INTEN_MASK                                              (0x0008U)
#define PWM_EPWM_ETSEL_INTEN_SHIFT                                             (0x0003U)
#define PWM_EPWM_ETSEL_INTEN_RESETVAL                                          (0x0000U)
#define PWM_EPWM_ETSEL_INTEN_MAX                                               (0x0001U)

#define PWM_EPWM_ETSEL_SOCASELCMP_MASK                                         (0x0010U)
#define PWM_EPWM_ETSEL_SOCASELCMP_SHIFT                                        (0x0004U)
#define PWM_EPWM_ETSEL_SOCASELCMP_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETSEL_SOCASELCMP_MAX                                          (0x0001U)

#define PWM_EPWM_ETSEL_SOCBSELCMP_MASK                                         (0x0020U)
#define PWM_EPWM_ETSEL_SOCBSELCMP_SHIFT                                        (0x0005U)
#define PWM_EPWM_ETSEL_SOCBSELCMP_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETSEL_SOCBSELCMP_MAX                                          (0x0001U)

#define PWM_EPWM_ETSEL_INTSELCMP_MASK                                          (0x0040U)
#define PWM_EPWM_ETSEL_INTSELCMP_SHIFT                                         (0x0006U)
#define PWM_EPWM_ETSEL_INTSELCMP_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSEL_INTSELCMP_MAX                                           (0x0001U)

#define PWM_EPWM_ETSEL_RESERVED_1_MASK                                         (0x0080U)
#define PWM_EPWM_ETSEL_RESERVED_1_SHIFT                                        (0x0007U)
#define PWM_EPWM_ETSEL_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETSEL_RESERVED_1_MAX                                          (0x0001U)

#define PWM_EPWM_ETSEL_SOCASEL_MASK                                            (0x0700U)
#define PWM_EPWM_ETSEL_SOCASEL_SHIFT                                           (0x0008U)
#define PWM_EPWM_ETSEL_SOCASEL_RESETVAL                                        (0x0000U)
#define PWM_EPWM_ETSEL_SOCASEL_MAX                                             (0x0007U)

#define PWM_EPWM_ETSEL_SOCAEN_MASK                                             (0x0800U)
#define PWM_EPWM_ETSEL_SOCAEN_SHIFT                                            (0x000BU)
#define PWM_EPWM_ETSEL_SOCAEN_RESETVAL                                         (0x0000U)
#define PWM_EPWM_ETSEL_SOCAEN_MAX                                              (0x0001U)

#define PWM_EPWM_ETSEL_SOCBSEL_MASK                                            (0x7000U)
#define PWM_EPWM_ETSEL_SOCBSEL_SHIFT                                           (0x000CU)
#define PWM_EPWM_ETSEL_SOCBSEL_RESETVAL                                        (0x0000U)
#define PWM_EPWM_ETSEL_SOCBSEL_MAX                                             (0x0007U)

#define PWM_EPWM_ETSEL_SOCBEN_MASK                                             (0x8000U)
#define PWM_EPWM_ETSEL_SOCBEN_SHIFT                                            (0x000FU)
#define PWM_EPWM_ETSEL_SOCBEN_RESETVAL                                         (0x0000U)
#define PWM_EPWM_ETSEL_SOCBEN_MAX                                              (0x0001U)

#define PWM_EPWM_ETSEL_RESETVAL                                                (0x0000U)

/* RESERVED_34 */

#define PWM_EPWM_RESERVED_34_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_34_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_34_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_34_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_34_RESETVAL                                          (0x0000U)

/* ETPS */

#define PWM_EPWM_ETPS_INTPRD_MASK                                              (0x0003U)
#define PWM_EPWM_ETPS_INTPRD_SHIFT                                             (0x0000U)
#define PWM_EPWM_ETPS_INTPRD_RESETVAL                                          (0x0000U)
#define PWM_EPWM_ETPS_INTPRD_MAX                                               (0x0003U)

#define PWM_EPWM_ETPS_INTCNT_MASK                                              (0x000CU)
#define PWM_EPWM_ETPS_INTCNT_SHIFT                                             (0x0002U)
#define PWM_EPWM_ETPS_INTCNT_RESETVAL                                          (0x0000U)
#define PWM_EPWM_ETPS_INTCNT_MAX                                               (0x0003U)

#define PWM_EPWM_ETPS_INTPSSEL_MASK                                            (0x0010U)
#define PWM_EPWM_ETPS_INTPSSEL_SHIFT                                           (0x0004U)
#define PWM_EPWM_ETPS_INTPSSEL_RESETVAL                                        (0x0000U)
#define PWM_EPWM_ETPS_INTPSSEL_MAX                                             (0x0001U)

#define PWM_EPWM_ETPS_SOCPSSEL_MASK                                            (0x0020U)
#define PWM_EPWM_ETPS_SOCPSSEL_SHIFT                                           (0x0005U)
#define PWM_EPWM_ETPS_SOCPSSEL_RESETVAL                                        (0x0000U)
#define PWM_EPWM_ETPS_SOCPSSEL_MAX                                             (0x0001U)

#define PWM_EPWM_ETPS_RESERVED_1_MASK                                          (0x00C0U)
#define PWM_EPWM_ETPS_RESERVED_1_SHIFT                                         (0x0006U)
#define PWM_EPWM_ETPS_RESERVED_1_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETPS_RESERVED_1_MAX                                           (0x0003U)

#define PWM_EPWM_ETPS_SOCAPRD_MASK                                             (0x0300U)
#define PWM_EPWM_ETPS_SOCAPRD_SHIFT                                            (0x0008U)
#define PWM_EPWM_ETPS_SOCAPRD_RESETVAL                                         (0x0000U)
#define PWM_EPWM_ETPS_SOCAPRD_MAX                                              (0x0003U)

#define PWM_EPWM_ETPS_SOCACNT_MASK                                             (0x0C00U)
#define PWM_EPWM_ETPS_SOCACNT_SHIFT                                            (0x000AU)
#define PWM_EPWM_ETPS_SOCACNT_RESETVAL                                         (0x0000U)
#define PWM_EPWM_ETPS_SOCACNT_MAX                                              (0x0003U)

#define PWM_EPWM_ETPS_SOCBPRD_MASK                                             (0x3000U)
#define PWM_EPWM_ETPS_SOCBPRD_SHIFT                                            (0x000CU)
#define PWM_EPWM_ETPS_SOCBPRD_RESETVAL                                         (0x0000U)
#define PWM_EPWM_ETPS_SOCBPRD_MAX                                              (0x0003U)

#define PWM_EPWM_ETPS_SOCBCNT_MASK                                             (0xC000U)
#define PWM_EPWM_ETPS_SOCBCNT_SHIFT                                            (0x000EU)
#define PWM_EPWM_ETPS_SOCBCNT_RESETVAL                                         (0x0000U)
#define PWM_EPWM_ETPS_SOCBCNT_MAX                                              (0x0003U)

#define PWM_EPWM_ETPS_RESETVAL                                                 (0x0000U)

/* RESERVED_35 */

#define PWM_EPWM_RESERVED_35_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_35_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_35_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_35_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_35_RESETVAL                                          (0x0000U)

/* ETFLG */

#define PWM_EPWM_ETFLG_INT_MASK                                                (0x0001U)
#define PWM_EPWM_ETFLG_INT_SHIFT                                               (0x0000U)
#define PWM_EPWM_ETFLG_INT_RESETVAL                                            (0x0000U)
#define PWM_EPWM_ETFLG_INT_MAX                                                 (0x0001U)

#define PWM_EPWM_ETFLG_RESERVED_1_MASK                                         (0x0002U)
#define PWM_EPWM_ETFLG_RESERVED_1_SHIFT                                        (0x0001U)
#define PWM_EPWM_ETFLG_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETFLG_RESERVED_1_MAX                                          (0x0001U)

#define PWM_EPWM_ETFLG_SOCA_MASK                                               (0x0004U)
#define PWM_EPWM_ETFLG_SOCA_SHIFT                                              (0x0002U)
#define PWM_EPWM_ETFLG_SOCA_RESETVAL                                           (0x0000U)
#define PWM_EPWM_ETFLG_SOCA_MAX                                                (0x0001U)

#define PWM_EPWM_ETFLG_SOCB_MASK                                               (0x0008U)
#define PWM_EPWM_ETFLG_SOCB_SHIFT                                              (0x0003U)
#define PWM_EPWM_ETFLG_SOCB_RESETVAL                                           (0x0000U)
#define PWM_EPWM_ETFLG_SOCB_MAX                                                (0x0001U)

#define PWM_EPWM_ETFLG_RESERVED_2_MASK                                         (0xFFF0U)
#define PWM_EPWM_ETFLG_RESERVED_2_SHIFT                                        (0x0004U)
#define PWM_EPWM_ETFLG_RESERVED_2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETFLG_RESERVED_2_MAX                                          (0x0FFFU)

#define PWM_EPWM_ETFLG_RESETVAL                                                (0x0000U)

/* RESERVED_36 */

#define PWM_EPWM_RESERVED_36_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_36_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_36_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_36_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_36_RESETVAL                                          (0x0000U)

/* ETCLR */

#define PWM_EPWM_ETCLR_INT_MASK                                                (0x0001U)
#define PWM_EPWM_ETCLR_INT_SHIFT                                               (0x0000U)
#define PWM_EPWM_ETCLR_INT_RESETVAL                                            (0x0000U)
#define PWM_EPWM_ETCLR_INT_MAX                                                 (0x0001U)

#define PWM_EPWM_ETCLR_RESERVED_1_MASK                                         (0x0002U)
#define PWM_EPWM_ETCLR_RESERVED_1_SHIFT                                        (0x0001U)
#define PWM_EPWM_ETCLR_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETCLR_RESERVED_1_MAX                                          (0x0001U)

#define PWM_EPWM_ETCLR_SOCA_MASK                                               (0x0004U)
#define PWM_EPWM_ETCLR_SOCA_SHIFT                                              (0x0002U)
#define PWM_EPWM_ETCLR_SOCA_RESETVAL                                           (0x0000U)
#define PWM_EPWM_ETCLR_SOCA_MAX                                                (0x0001U)

#define PWM_EPWM_ETCLR_SOCB_MASK                                               (0x0008U)
#define PWM_EPWM_ETCLR_SOCB_SHIFT                                              (0x0003U)
#define PWM_EPWM_ETCLR_SOCB_RESETVAL                                           (0x0000U)
#define PWM_EPWM_ETCLR_SOCB_MAX                                                (0x0001U)

#define PWM_EPWM_ETCLR_RESERVED_2_MASK                                         (0xFFF0U)
#define PWM_EPWM_ETCLR_RESERVED_2_SHIFT                                        (0x0004U)
#define PWM_EPWM_ETCLR_RESERVED_2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETCLR_RESERVED_2_MAX                                          (0x0FFFU)

#define PWM_EPWM_ETCLR_RESETVAL                                                (0x0000U)

/* RESERVED_37 */

#define PWM_EPWM_RESERVED_37_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_37_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_37_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_37_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_37_RESETVAL                                          (0x0000U)

/* ETFRC */

#define PWM_EPWM_ETFRC_INT_MASK                                                (0x0001U)
#define PWM_EPWM_ETFRC_INT_SHIFT                                               (0x0000U)
#define PWM_EPWM_ETFRC_INT_RESETVAL                                            (0x0000U)
#define PWM_EPWM_ETFRC_INT_MAX                                                 (0x0001U)

#define PWM_EPWM_ETFRC_RESERVED_1_MASK                                         (0x0002U)
#define PWM_EPWM_ETFRC_RESERVED_1_SHIFT                                        (0x0001U)
#define PWM_EPWM_ETFRC_RESERVED_1_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETFRC_RESERVED_1_MAX                                          (0x0001U)

#define PWM_EPWM_ETFRC_SOCA_MASK                                               (0x0004U)
#define PWM_EPWM_ETFRC_SOCA_SHIFT                                              (0x0002U)
#define PWM_EPWM_ETFRC_SOCA_RESETVAL                                           (0x0000U)
#define PWM_EPWM_ETFRC_SOCA_MAX                                                (0x0001U)

#define PWM_EPWM_ETFRC_SOCB_MASK                                               (0x0008U)
#define PWM_EPWM_ETFRC_SOCB_SHIFT                                              (0x0003U)
#define PWM_EPWM_ETFRC_SOCB_RESETVAL                                           (0x0000U)
#define PWM_EPWM_ETFRC_SOCB_MAX                                                (0x0001U)

#define PWM_EPWM_ETFRC_RESERVED_2_MASK                                         (0xFFF0U)
#define PWM_EPWM_ETFRC_RESERVED_2_SHIFT                                        (0x0004U)
#define PWM_EPWM_ETFRC_RESERVED_2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETFRC_RESERVED_2_MAX                                          (0x0FFFU)

#define PWM_EPWM_ETFRC_RESETVAL                                                (0x0000U)

/* RESERVED_38 */

#define PWM_EPWM_RESERVED_38_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_38_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_38_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_38_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_38_RESETVAL                                          (0x0000U)

/* ETINTPS */

#define PWM_EPWM_ETINTPS_INTPRD2_MASK                                          (0x000FU)
#define PWM_EPWM_ETINTPS_INTPRD2_SHIFT                                         (0x0000U)
#define PWM_EPWM_ETINTPS_INTPRD2_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETINTPS_INTPRD2_MAX                                           (0x000FU)

#define PWM_EPWM_ETINTPS_INTCNT2_MASK                                          (0x00F0U)
#define PWM_EPWM_ETINTPS_INTCNT2_SHIFT                                         (0x0004U)
#define PWM_EPWM_ETINTPS_INTCNT2_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETINTPS_INTCNT2_MAX                                           (0x000FU)

#define PWM_EPWM_ETINTPS_RESERVED_1_MASK                                       (0xFF00U)
#define PWM_EPWM_ETINTPS_RESERVED_1_SHIFT                                      (0x0008U)
#define PWM_EPWM_ETINTPS_RESERVED_1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_ETINTPS_RESERVED_1_MAX                                        (0x00FFU)

#define PWM_EPWM_ETINTPS_RESETVAL                                              (0x0000U)

/* RESERVED_39 */

#define PWM_EPWM_RESERVED_39_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_39_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_39_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_39_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_39_RESETVAL                                          (0x0000U)

/* ETSOCPS */

#define PWM_EPWM_ETSOCPS_SOCAPRD2_MASK                                         (0x000FU)
#define PWM_EPWM_ETSOCPS_SOCAPRD2_SHIFT                                        (0x0000U)
#define PWM_EPWM_ETSOCPS_SOCAPRD2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETSOCPS_SOCAPRD2_MAX                                          (0x000FU)

#define PWM_EPWM_ETSOCPS_SOCACNT2_MASK                                         (0x00F0U)
#define PWM_EPWM_ETSOCPS_SOCACNT2_SHIFT                                        (0x0004U)
#define PWM_EPWM_ETSOCPS_SOCACNT2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETSOCPS_SOCACNT2_MAX                                          (0x000FU)

#define PWM_EPWM_ETSOCPS_SOCBPRD2_MASK                                         (0x0F00U)
#define PWM_EPWM_ETSOCPS_SOCBPRD2_SHIFT                                        (0x0008U)
#define PWM_EPWM_ETSOCPS_SOCBPRD2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETSOCPS_SOCBPRD2_MAX                                          (0x000FU)

#define PWM_EPWM_ETSOCPS_SOCBCNT2_MASK                                         (0xF000U)
#define PWM_EPWM_ETSOCPS_SOCBCNT2_SHIFT                                        (0x000CU)
#define PWM_EPWM_ETSOCPS_SOCBCNT2_RESETVAL                                     (0x0000U)
#define PWM_EPWM_ETSOCPS_SOCBCNT2_MAX                                          (0x000FU)

#define PWM_EPWM_ETSOCPS_RESETVAL                                              (0x0000U)

/* RESERVED_40 */

#define PWM_EPWM_RESERVED_40_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_40_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_40_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_40_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_40_RESETVAL                                          (0x0000U)

/* ETCNTINITCTL */

#define PWM_EPWM_ETCNTINITCTL_RESERVED_1_MASK                                  (0x03FFU)
#define PWM_EPWM_ETCNTINITCTL_RESERVED_1_SHIFT                                 (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_RESERVED_1_RESETVAL                              (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_RESERVED_1_MAX                                   (0x03FFU)

#define PWM_EPWM_ETCNTINITCTL_INTINITFRC_MASK                                  (0x0400U)
#define PWM_EPWM_ETCNTINITCTL_INTINITFRC_SHIFT                                 (0x000AU)
#define PWM_EPWM_ETCNTINITCTL_INTINITFRC_RESETVAL                              (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_INTINITFRC_MAX                                   (0x0001U)

#define PWM_EPWM_ETCNTINITCTL_SOCAINITFRC_MASK                                 (0x0800U)
#define PWM_EPWM_ETCNTINITCTL_SOCAINITFRC_SHIFT                                (0x000BU)
#define PWM_EPWM_ETCNTINITCTL_SOCAINITFRC_RESETVAL                             (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_SOCAINITFRC_MAX                                  (0x0001U)

#define PWM_EPWM_ETCNTINITCTL_SOCBINITFRC_MASK                                 (0x1000U)
#define PWM_EPWM_ETCNTINITCTL_SOCBINITFRC_SHIFT                                (0x000CU)
#define PWM_EPWM_ETCNTINITCTL_SOCBINITFRC_RESETVAL                             (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_SOCBINITFRC_MAX                                  (0x0001U)

#define PWM_EPWM_ETCNTINITCTL_INTINITEN_MASK                                   (0x2000U)
#define PWM_EPWM_ETCNTINITCTL_INTINITEN_SHIFT                                  (0x000DU)
#define PWM_EPWM_ETCNTINITCTL_INTINITEN_RESETVAL                               (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_INTINITEN_MAX                                    (0x0001U)

#define PWM_EPWM_ETCNTINITCTL_SOCAINITEN_MASK                                  (0x4000U)
#define PWM_EPWM_ETCNTINITCTL_SOCAINITEN_SHIFT                                 (0x000EU)
#define PWM_EPWM_ETCNTINITCTL_SOCAINITEN_RESETVAL                              (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_SOCAINITEN_MAX                                   (0x0001U)

#define PWM_EPWM_ETCNTINITCTL_SOCBINITEN_MASK                                  (0x8000U)
#define PWM_EPWM_ETCNTINITCTL_SOCBINITEN_SHIFT                                 (0x000FU)
#define PWM_EPWM_ETCNTINITCTL_SOCBINITEN_RESETVAL                              (0x0000U)
#define PWM_EPWM_ETCNTINITCTL_SOCBINITEN_MAX                                   (0x0001U)

#define PWM_EPWM_ETCNTINITCTL_RESETVAL                                         (0x0000U)

/* RESERVED_41 */

#define PWM_EPWM_RESERVED_41_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_41_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_41_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_41_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_41_RESETVAL                                          (0x0000U)

/* ETCNTINIT */

#define PWM_EPWM_ETCNTINIT_INTINIT_MASK                                        (0x000FU)
#define PWM_EPWM_ETCNTINIT_INTINIT_SHIFT                                       (0x0000U)
#define PWM_EPWM_ETCNTINIT_INTINIT_RESETVAL                                    (0x0000U)
#define PWM_EPWM_ETCNTINIT_INTINIT_MAX                                         (0x000FU)

#define PWM_EPWM_ETCNTINIT_SOCAINIT_MASK                                       (0x00F0U)
#define PWM_EPWM_ETCNTINIT_SOCAINIT_SHIFT                                      (0x0004U)
#define PWM_EPWM_ETCNTINIT_SOCAINIT_RESETVAL                                   (0x0000U)
#define PWM_EPWM_ETCNTINIT_SOCAINIT_MAX                                        (0x000FU)

#define PWM_EPWM_ETCNTINIT_SOCBINIT_MASK                                       (0x0F00U)
#define PWM_EPWM_ETCNTINIT_SOCBINIT_SHIFT                                      (0x0008U)
#define PWM_EPWM_ETCNTINIT_SOCBINIT_RESETVAL                                   (0x0000U)
#define PWM_EPWM_ETCNTINIT_SOCBINIT_MAX                                        (0x000FU)

#define PWM_EPWM_ETCNTINIT_RESERVED_1_MASK                                     (0xF000U)
#define PWM_EPWM_ETCNTINIT_RESERVED_1_SHIFT                                    (0x000CU)
#define PWM_EPWM_ETCNTINIT_RESERVED_1_RESETVAL                                 (0x0000U)
#define PWM_EPWM_ETCNTINIT_RESERVED_1_MAX                                      (0x000FU)

#define PWM_EPWM_ETCNTINIT_RESETVAL                                            (0x0000U)

/* RESERVED_42 */

#define PWM_EPWM_RESERVED_42_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_42_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_42_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_42_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_42_RESETVAL                                          (0x0000U)

/* ETINTMIXEN */

#define PWM_EPWM_ETINTMIXEN_ZRO_MASK                                           (0x0001U)
#define PWM_EPWM_ETINTMIXEN_ZRO_SHIFT                                          (0x0000U)
#define PWM_EPWM_ETINTMIXEN_ZRO_RESETVAL                                       (0x0001U)
#define PWM_EPWM_ETINTMIXEN_ZRO_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_PRD_MASK                                           (0x0002U)
#define PWM_EPWM_ETINTMIXEN_PRD_SHIFT                                          (0x0001U)
#define PWM_EPWM_ETINTMIXEN_PRD_RESETVAL                                       (0x0001U)
#define PWM_EPWM_ETINTMIXEN_PRD_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CAU_MASK                                           (0x0004U)
#define PWM_EPWM_ETINTMIXEN_CAU_SHIFT                                          (0x0002U)
#define PWM_EPWM_ETINTMIXEN_CAU_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CAU_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CAD_MASK                                           (0x0008U)
#define PWM_EPWM_ETINTMIXEN_CAD_SHIFT                                          (0x0003U)
#define PWM_EPWM_ETINTMIXEN_CAD_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CAD_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CBU_MASK                                           (0x0010U)
#define PWM_EPWM_ETINTMIXEN_CBU_SHIFT                                          (0x0004U)
#define PWM_EPWM_ETINTMIXEN_CBU_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CBU_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CBD_MASK                                           (0x0020U)
#define PWM_EPWM_ETINTMIXEN_CBD_SHIFT                                          (0x0005U)
#define PWM_EPWM_ETINTMIXEN_CBD_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CBD_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CCU_MASK                                           (0x0040U)
#define PWM_EPWM_ETINTMIXEN_CCU_SHIFT                                          (0x0006U)
#define PWM_EPWM_ETINTMIXEN_CCU_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CCU_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CCD_MASK                                           (0x0080U)
#define PWM_EPWM_ETINTMIXEN_CCD_SHIFT                                          (0x0007U)
#define PWM_EPWM_ETINTMIXEN_CCD_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CCD_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CDU_MASK                                           (0x0100U)
#define PWM_EPWM_ETINTMIXEN_CDU_SHIFT                                          (0x0008U)
#define PWM_EPWM_ETINTMIXEN_CDU_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CDU_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_CDD_MASK                                           (0x0200U)
#define PWM_EPWM_ETINTMIXEN_CDD_SHIFT                                          (0x0009U)
#define PWM_EPWM_ETINTMIXEN_CDD_RESETVAL                                       (0x0000U)
#define PWM_EPWM_ETINTMIXEN_CDD_MAX                                            (0x0001U)

#define PWM_EPWM_ETINTMIXEN_DCAEVT1_MASK                                       (0x0400U)
#define PWM_EPWM_ETINTMIXEN_DCAEVT1_SHIFT                                      (0x000AU)
#define PWM_EPWM_ETINTMIXEN_DCAEVT1_RESETVAL                                   (0x0000U)
#define PWM_EPWM_ETINTMIXEN_DCAEVT1_MAX                                        (0x0001U)

#define PWM_EPWM_ETINTMIXEN_RESERVED_1_MASK                                    (0xF800U)
#define PWM_EPWM_ETINTMIXEN_RESERVED_1_SHIFT                                   (0x000BU)
#define PWM_EPWM_ETINTMIXEN_RESERVED_1_RESETVAL                                (0x0000U)
#define PWM_EPWM_ETINTMIXEN_RESERVED_1_MAX                                     (0x001FU)

#define PWM_EPWM_ETINTMIXEN_RESETVAL                                           (0x0003U)

/* RESERVED_43 */

#define PWM_EPWM_RESERVED_43_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_43_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_43_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_43_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_43_RESETVAL                                          (0x0000U)

/* ETSOCAMIXEN */

#define PWM_EPWM_ETSOCAMIXEN_ZRO_MASK                                          (0x0001U)
#define PWM_EPWM_ETSOCAMIXEN_ZRO_SHIFT                                         (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_ZRO_RESETVAL                                      (0x0001U)
#define PWM_EPWM_ETSOCAMIXEN_ZRO_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_PRD_MASK                                          (0x0002U)
#define PWM_EPWM_ETSOCAMIXEN_PRD_SHIFT                                         (0x0001U)
#define PWM_EPWM_ETSOCAMIXEN_PRD_RESETVAL                                      (0x0001U)
#define PWM_EPWM_ETSOCAMIXEN_PRD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CAU_MASK                                          (0x0004U)
#define PWM_EPWM_ETSOCAMIXEN_CAU_SHIFT                                         (0x0002U)
#define PWM_EPWM_ETSOCAMIXEN_CAU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CAU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CAD_MASK                                          (0x0008U)
#define PWM_EPWM_ETSOCAMIXEN_CAD_SHIFT                                         (0x0003U)
#define PWM_EPWM_ETSOCAMIXEN_CAD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CAD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CBU_MASK                                          (0x0010U)
#define PWM_EPWM_ETSOCAMIXEN_CBU_SHIFT                                         (0x0004U)
#define PWM_EPWM_ETSOCAMIXEN_CBU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CBU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CBD_MASK                                          (0x0020U)
#define PWM_EPWM_ETSOCAMIXEN_CBD_SHIFT                                         (0x0005U)
#define PWM_EPWM_ETSOCAMIXEN_CBD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CBD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CCU_MASK                                          (0x0040U)
#define PWM_EPWM_ETSOCAMIXEN_CCU_SHIFT                                         (0x0006U)
#define PWM_EPWM_ETSOCAMIXEN_CCU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CCU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CCD_MASK                                          (0x0080U)
#define PWM_EPWM_ETSOCAMIXEN_CCD_SHIFT                                         (0x0007U)
#define PWM_EPWM_ETSOCAMIXEN_CCD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CCD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CDU_MASK                                          (0x0100U)
#define PWM_EPWM_ETSOCAMIXEN_CDU_SHIFT                                         (0x0008U)
#define PWM_EPWM_ETSOCAMIXEN_CDU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CDU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_CDD_MASK                                          (0x0200U)
#define PWM_EPWM_ETSOCAMIXEN_CDD_SHIFT                                         (0x0009U)
#define PWM_EPWM_ETSOCAMIXEN_CDD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_CDD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_DCAEVT1_MASK                                      (0x0400U)
#define PWM_EPWM_ETSOCAMIXEN_DCAEVT1_SHIFT                                     (0x000AU)
#define PWM_EPWM_ETSOCAMIXEN_DCAEVT1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_DCAEVT1_MAX                                       (0x0001U)

#define PWM_EPWM_ETSOCAMIXEN_RESERVED_1_MASK                                   (0xF800U)
#define PWM_EPWM_ETSOCAMIXEN_RESERVED_1_SHIFT                                  (0x000BU)
#define PWM_EPWM_ETSOCAMIXEN_RESERVED_1_RESETVAL                               (0x0000U)
#define PWM_EPWM_ETSOCAMIXEN_RESERVED_1_MAX                                    (0x001FU)

#define PWM_EPWM_ETSOCAMIXEN_RESETVAL                                          (0x0003U)

/* RESERVED_44 */

#define PWM_EPWM_RESERVED_44_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_44_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_44_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_44_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_44_RESETVAL                                          (0x0000U)

/* ETSOCBMIXEN */

#define PWM_EPWM_ETSOCBMIXEN_ZRO_MASK                                          (0x0001U)
#define PWM_EPWM_ETSOCBMIXEN_ZRO_SHIFT                                         (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_ZRO_RESETVAL                                      (0x0001U)
#define PWM_EPWM_ETSOCBMIXEN_ZRO_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_PRD_MASK                                          (0x0002U)
#define PWM_EPWM_ETSOCBMIXEN_PRD_SHIFT                                         (0x0001U)
#define PWM_EPWM_ETSOCBMIXEN_PRD_RESETVAL                                      (0x0001U)
#define PWM_EPWM_ETSOCBMIXEN_PRD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CAU_MASK                                          (0x0004U)
#define PWM_EPWM_ETSOCBMIXEN_CAU_SHIFT                                         (0x0002U)
#define PWM_EPWM_ETSOCBMIXEN_CAU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CAU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CAD_MASK                                          (0x0008U)
#define PWM_EPWM_ETSOCBMIXEN_CAD_SHIFT                                         (0x0003U)
#define PWM_EPWM_ETSOCBMIXEN_CAD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CAD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CBU_MASK                                          (0x0010U)
#define PWM_EPWM_ETSOCBMIXEN_CBU_SHIFT                                         (0x0004U)
#define PWM_EPWM_ETSOCBMIXEN_CBU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CBU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CBD_MASK                                          (0x0020U)
#define PWM_EPWM_ETSOCBMIXEN_CBD_SHIFT                                         (0x0005U)
#define PWM_EPWM_ETSOCBMIXEN_CBD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CBD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CCU_MASK                                          (0x0040U)
#define PWM_EPWM_ETSOCBMIXEN_CCU_SHIFT                                         (0x0006U)
#define PWM_EPWM_ETSOCBMIXEN_CCU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CCU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CCD_MASK                                          (0x0080U)
#define PWM_EPWM_ETSOCBMIXEN_CCD_SHIFT                                         (0x0007U)
#define PWM_EPWM_ETSOCBMIXEN_CCD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CCD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CDU_MASK                                          (0x0100U)
#define PWM_EPWM_ETSOCBMIXEN_CDU_SHIFT                                         (0x0008U)
#define PWM_EPWM_ETSOCBMIXEN_CDU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CDU_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_CDD_MASK                                          (0x0200U)
#define PWM_EPWM_ETSOCBMIXEN_CDD_SHIFT                                         (0x0009U)
#define PWM_EPWM_ETSOCBMIXEN_CDD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_CDD_MAX                                           (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_DCBEVT1_MASK                                      (0x0400U)
#define PWM_EPWM_ETSOCBMIXEN_DCBEVT1_SHIFT                                     (0x000AU)
#define PWM_EPWM_ETSOCBMIXEN_DCBEVT1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_DCBEVT1_MAX                                       (0x0001U)

#define PWM_EPWM_ETSOCBMIXEN_RESERVED_1_MASK                                   (0xF800U)
#define PWM_EPWM_ETSOCBMIXEN_RESERVED_1_SHIFT                                  (0x000BU)
#define PWM_EPWM_ETSOCBMIXEN_RESERVED_1_RESETVAL                               (0x0000U)
#define PWM_EPWM_ETSOCBMIXEN_RESERVED_1_MAX                                    (0x001FU)

#define PWM_EPWM_ETSOCBMIXEN_RESETVAL                                          (0x0003U)

/* RESERVED_45 */

#define PWM_EPWM_RESERVED_45_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_45_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_45_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_45_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_45_RESETVAL                                          (0x0000U)

/* DCTRIPSEL */

#define PWM_EPWM_DCTRIPSEL_DCAHCOMPSEL_MASK                                    (0x000FU)
#define PWM_EPWM_DCTRIPSEL_DCAHCOMPSEL_SHIFT                                   (0x0000U)
#define PWM_EPWM_DCTRIPSEL_DCAHCOMPSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCTRIPSEL_DCAHCOMPSEL_MAX                                     (0x000FU)

#define PWM_EPWM_DCTRIPSEL_DCALCOMPSEL_MASK                                    (0x00F0U)
#define PWM_EPWM_DCTRIPSEL_DCALCOMPSEL_SHIFT                                   (0x0004U)
#define PWM_EPWM_DCTRIPSEL_DCALCOMPSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCTRIPSEL_DCALCOMPSEL_MAX                                     (0x000FU)

#define PWM_EPWM_DCTRIPSEL_DCBHCOMPSEL_MASK                                    (0x0F00U)
#define PWM_EPWM_DCTRIPSEL_DCBHCOMPSEL_SHIFT                                   (0x0008U)
#define PWM_EPWM_DCTRIPSEL_DCBHCOMPSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCTRIPSEL_DCBHCOMPSEL_MAX                                     (0x000FU)

#define PWM_EPWM_DCTRIPSEL_DCBLCOMPSEL_MASK                                    (0xF000U)
#define PWM_EPWM_DCTRIPSEL_DCBLCOMPSEL_SHIFT                                   (0x000CU)
#define PWM_EPWM_DCTRIPSEL_DCBLCOMPSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCTRIPSEL_DCBLCOMPSEL_MAX                                     (0x000FU)

#define PWM_EPWM_DCTRIPSEL_RESETVAL                                            (0x0000U)

/* RESERVED_46 */

#define PWM_EPWM_RESERVED_46_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_46_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_46_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_46_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_46_RESETVAL                                          (0x0000U)

/* DCACTL */

#define PWM_EPWM_DCACTL_EVT1SRCSEL_MASK                                        (0x0001U)
#define PWM_EPWM_DCACTL_EVT1SRCSEL_SHIFT                                       (0x0000U)
#define PWM_EPWM_DCACTL_EVT1SRCSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCACTL_EVT1SRCSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCACTL_EVT1FRCSYNCSEL_MASK                                    (0x0002U)
#define PWM_EPWM_DCACTL_EVT1FRCSYNCSEL_SHIFT                                   (0x0001U)
#define PWM_EPWM_DCACTL_EVT1FRCSYNCSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCACTL_EVT1FRCSYNCSEL_MAX                                     (0x0001U)

#define PWM_EPWM_DCACTL_EVT1SOCE_MASK                                          (0x0004U)
#define PWM_EPWM_DCACTL_EVT1SOCE_SHIFT                                         (0x0002U)
#define PWM_EPWM_DCACTL_EVT1SOCE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCACTL_EVT1SOCE_MAX                                           (0x0001U)

#define PWM_EPWM_DCACTL_EVT1SYNCE_MASK                                         (0x0008U)
#define PWM_EPWM_DCACTL_EVT1SYNCE_SHIFT                                        (0x0003U)
#define PWM_EPWM_DCACTL_EVT1SYNCE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_DCACTL_EVT1SYNCE_MAX                                          (0x0001U)

#define PWM_EPWM_DCACTL_EVT1LATSEL_MASK                                        (0x0010U)
#define PWM_EPWM_DCACTL_EVT1LATSEL_SHIFT                                       (0x0004U)
#define PWM_EPWM_DCACTL_EVT1LATSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCACTL_EVT1LATSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCACTL_EVT1LATCLRSEL_MASK                                     (0x0060U)
#define PWM_EPWM_DCACTL_EVT1LATCLRSEL_SHIFT                                    (0x0005U)
#define PWM_EPWM_DCACTL_EVT1LATCLRSEL_RESETVAL                                 (0x0000U)
#define PWM_EPWM_DCACTL_EVT1LATCLRSEL_MAX                                      (0x0003U)

#define PWM_EPWM_DCACTL_EVT1LAT_MASK                                           (0x0080U)
#define PWM_EPWM_DCACTL_EVT1LAT_SHIFT                                          (0x0007U)
#define PWM_EPWM_DCACTL_EVT1LAT_RESETVAL                                       (0x0000U)
#define PWM_EPWM_DCACTL_EVT1LAT_MAX                                            (0x0001U)

#define PWM_EPWM_DCACTL_EVT2SRCSEL_MASK                                        (0x0100U)
#define PWM_EPWM_DCACTL_EVT2SRCSEL_SHIFT                                       (0x0008U)
#define PWM_EPWM_DCACTL_EVT2SRCSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCACTL_EVT2SRCSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCACTL_EVT2FRCSYNCSEL_MASK                                    (0x0200U)
#define PWM_EPWM_DCACTL_EVT2FRCSYNCSEL_SHIFT                                   (0x0009U)
#define PWM_EPWM_DCACTL_EVT2FRCSYNCSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCACTL_EVT2FRCSYNCSEL_MAX                                     (0x0001U)

#define PWM_EPWM_DCACTL_RESERVED_1_MASK                                        (0x0C00U)
#define PWM_EPWM_DCACTL_RESERVED_1_SHIFT                                       (0x000AU)
#define PWM_EPWM_DCACTL_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCACTL_RESERVED_1_MAX                                         (0x0003U)

#define PWM_EPWM_DCACTL_EVT2LATSEL_MASK                                        (0x1000U)
#define PWM_EPWM_DCACTL_EVT2LATSEL_SHIFT                                       (0x000CU)
#define PWM_EPWM_DCACTL_EVT2LATSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCACTL_EVT2LATSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCACTL_EVT2LATCLRSEL_MASK                                     (0x6000U)
#define PWM_EPWM_DCACTL_EVT2LATCLRSEL_SHIFT                                    (0x000DU)
#define PWM_EPWM_DCACTL_EVT2LATCLRSEL_RESETVAL                                 (0x0000U)
#define PWM_EPWM_DCACTL_EVT2LATCLRSEL_MAX                                      (0x0003U)

#define PWM_EPWM_DCACTL_EVT2LAT_MASK                                           (0x8000U)
#define PWM_EPWM_DCACTL_EVT2LAT_SHIFT                                          (0x000FU)
#define PWM_EPWM_DCACTL_EVT2LAT_RESETVAL                                       (0x0000U)
#define PWM_EPWM_DCACTL_EVT2LAT_MAX                                            (0x0001U)

#define PWM_EPWM_DCACTL_RESETVAL                                               (0x0000U)

/* DCBCTL */

#define PWM_EPWM_DCBCTL_EVT1SRCSEL_MASK                                        (0x0001U)
#define PWM_EPWM_DCBCTL_EVT1SRCSEL_SHIFT                                       (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1SRCSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1SRCSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCBCTL_EVT1FRCSYNCSEL_MASK                                    (0x0002U)
#define PWM_EPWM_DCBCTL_EVT1FRCSYNCSEL_SHIFT                                   (0x0001U)
#define PWM_EPWM_DCBCTL_EVT1FRCSYNCSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1FRCSYNCSEL_MAX                                     (0x0001U)

#define PWM_EPWM_DCBCTL_EVT1SOCE_MASK                                          (0x0004U)
#define PWM_EPWM_DCBCTL_EVT1SOCE_SHIFT                                         (0x0002U)
#define PWM_EPWM_DCBCTL_EVT1SOCE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1SOCE_MAX                                           (0x0001U)

#define PWM_EPWM_DCBCTL_EVT1SYNCE_MASK                                         (0x0008U)
#define PWM_EPWM_DCBCTL_EVT1SYNCE_SHIFT                                        (0x0003U)
#define PWM_EPWM_DCBCTL_EVT1SYNCE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1SYNCE_MAX                                          (0x0001U)

#define PWM_EPWM_DCBCTL_EVT1LATSEL_MASK                                        (0x0010U)
#define PWM_EPWM_DCBCTL_EVT1LATSEL_SHIFT                                       (0x0004U)
#define PWM_EPWM_DCBCTL_EVT1LATSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1LATSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCBCTL_EVT1LATCLRSEL_MASK                                     (0x0060U)
#define PWM_EPWM_DCBCTL_EVT1LATCLRSEL_SHIFT                                    (0x0005U)
#define PWM_EPWM_DCBCTL_EVT1LATCLRSEL_RESETVAL                                 (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1LATCLRSEL_MAX                                      (0x0003U)

#define PWM_EPWM_DCBCTL_EVT1LAT_MASK                                           (0x0080U)
#define PWM_EPWM_DCBCTL_EVT1LAT_SHIFT                                          (0x0007U)
#define PWM_EPWM_DCBCTL_EVT1LAT_RESETVAL                                       (0x0000U)
#define PWM_EPWM_DCBCTL_EVT1LAT_MAX                                            (0x0001U)

#define PWM_EPWM_DCBCTL_EVT2SRCSEL_MASK                                        (0x0100U)
#define PWM_EPWM_DCBCTL_EVT2SRCSEL_SHIFT                                       (0x0008U)
#define PWM_EPWM_DCBCTL_EVT2SRCSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCBCTL_EVT2SRCSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCBCTL_EVT2FRCSYNCSEL_MASK                                    (0x0200U)
#define PWM_EPWM_DCBCTL_EVT2FRCSYNCSEL_SHIFT                                   (0x0009U)
#define PWM_EPWM_DCBCTL_EVT2FRCSYNCSEL_RESETVAL                                (0x0000U)
#define PWM_EPWM_DCBCTL_EVT2FRCSYNCSEL_MAX                                     (0x0001U)

#define PWM_EPWM_DCBCTL_RESERVED_1_MASK                                        (0x0C00U)
#define PWM_EPWM_DCBCTL_RESERVED_1_SHIFT                                       (0x000AU)
#define PWM_EPWM_DCBCTL_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCBCTL_RESERVED_1_MAX                                         (0x0003U)

#define PWM_EPWM_DCBCTL_EVT2LATSEL_MASK                                        (0x1000U)
#define PWM_EPWM_DCBCTL_EVT2LATSEL_SHIFT                                       (0x000CU)
#define PWM_EPWM_DCBCTL_EVT2LATSEL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCBCTL_EVT2LATSEL_MAX                                         (0x0001U)

#define PWM_EPWM_DCBCTL_EVT2LATCLRSEL_MASK                                     (0x6000U)
#define PWM_EPWM_DCBCTL_EVT2LATCLRSEL_SHIFT                                    (0x000DU)
#define PWM_EPWM_DCBCTL_EVT2LATCLRSEL_RESETVAL                                 (0x0000U)
#define PWM_EPWM_DCBCTL_EVT2LATCLRSEL_MAX                                      (0x0003U)

#define PWM_EPWM_DCBCTL_EVT2LAT_MASK                                           (0x8000U)
#define PWM_EPWM_DCBCTL_EVT2LAT_SHIFT                                          (0x000FU)
#define PWM_EPWM_DCBCTL_EVT2LAT_RESETVAL                                       (0x0000U)
#define PWM_EPWM_DCBCTL_EVT2LAT_MAX                                            (0x0001U)

#define PWM_EPWM_DCBCTL_RESETVAL                                               (0x0000U)

/* RESERVED_47 */

#define PWM_EPWM_RESERVED_47_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_47_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_47_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_47_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_47_RESETVAL                                          (0x0000U)

/* DCFCTL */

#define PWM_EPWM_DCFCTL_SRCSEL_MASK                                            (0x0003U)
#define PWM_EPWM_DCFCTL_SRCSEL_SHIFT                                           (0x0000U)
#define PWM_EPWM_DCFCTL_SRCSEL_RESETVAL                                        (0x0000U)
#define PWM_EPWM_DCFCTL_SRCSEL_MAX                                             (0x0003U)

#define PWM_EPWM_DCFCTL_BLANKE_MASK                                            (0x0004U)
#define PWM_EPWM_DCFCTL_BLANKE_SHIFT                                           (0x0002U)
#define PWM_EPWM_DCFCTL_BLANKE_RESETVAL                                        (0x0000U)
#define PWM_EPWM_DCFCTL_BLANKE_MAX                                             (0x0001U)

#define PWM_EPWM_DCFCTL_BLANKINV_MASK                                          (0x0008U)
#define PWM_EPWM_DCFCTL_BLANKINV_SHIFT                                         (0x0003U)
#define PWM_EPWM_DCFCTL_BLANKINV_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCFCTL_BLANKINV_MAX                                           (0x0001U)

#define PWM_EPWM_DCFCTL_PULSESEL_MASK                                          (0x0030U)
#define PWM_EPWM_DCFCTL_PULSESEL_SHIFT                                         (0x0004U)
#define PWM_EPWM_DCFCTL_PULSESEL_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCFCTL_PULSESEL_MAX                                           (0x0003U)

#define PWM_EPWM_DCFCTL_EDGEFILTSEL_MASK                                       (0x0040U)
#define PWM_EPWM_DCFCTL_EDGEFILTSEL_SHIFT                                      (0x0006U)
#define PWM_EPWM_DCFCTL_EDGEFILTSEL_RESETVAL                                   (0x0000U)
#define PWM_EPWM_DCFCTL_EDGEFILTSEL_MAX                                        (0x0001U)

#define PWM_EPWM_DCFCTL_RESERVED_1_MASK                                        (0x0080U)
#define PWM_EPWM_DCFCTL_RESERVED_1_SHIFT                                       (0x0007U)
#define PWM_EPWM_DCFCTL_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCFCTL_RESERVED_1_MAX                                         (0x0001U)

#define PWM_EPWM_DCFCTL_EDGEMODE_MASK                                          (0x0300U)
#define PWM_EPWM_DCFCTL_EDGEMODE_SHIFT                                         (0x0008U)
#define PWM_EPWM_DCFCTL_EDGEMODE_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCFCTL_EDGEMODE_MAX                                           (0x0003U)

#define PWM_EPWM_DCFCTL_EDGECOUNT_MASK                                         (0x1C00U)
#define PWM_EPWM_DCFCTL_EDGECOUNT_SHIFT                                        (0x000AU)
#define PWM_EPWM_DCFCTL_EDGECOUNT_RESETVAL                                     (0x0000U)
#define PWM_EPWM_DCFCTL_EDGECOUNT_MAX                                          (0x0007U)

#define PWM_EPWM_DCFCTL_EDGESTATUS_MASK                                        (0xE000U)
#define PWM_EPWM_DCFCTL_EDGESTATUS_SHIFT                                       (0x000DU)
#define PWM_EPWM_DCFCTL_EDGESTATUS_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCFCTL_EDGESTATUS_MAX                                         (0x0007U)

#define PWM_EPWM_DCFCTL_RESETVAL                                               (0x0000U)

/* DCCAPCTL */

#define PWM_EPWM_DCCAPCTL_CAPE_MASK                                            (0x0001U)
#define PWM_EPWM_DCCAPCTL_CAPE_SHIFT                                           (0x0000U)
#define PWM_EPWM_DCCAPCTL_CAPE_RESETVAL                                        (0x0000U)
#define PWM_EPWM_DCCAPCTL_CAPE_MAX                                             (0x0001U)

#define PWM_EPWM_DCCAPCTL_SHDWMODE_MASK                                        (0x0002U)
#define PWM_EPWM_DCCAPCTL_SHDWMODE_SHIFT                                       (0x0001U)
#define PWM_EPWM_DCCAPCTL_SHDWMODE_RESETVAL                                    (0x0000U)
#define PWM_EPWM_DCCAPCTL_SHDWMODE_MAX                                         (0x0001U)

#define PWM_EPWM_DCCAPCTL_RESERVED_1_MASK                                      (0x1FFCU)
#define PWM_EPWM_DCCAPCTL_RESERVED_1_SHIFT                                     (0x0002U)
#define PWM_EPWM_DCCAPCTL_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_DCCAPCTL_RESERVED_1_MAX                                       (0x07FFU)

#define PWM_EPWM_DCCAPCTL_CAPSTS_MASK                                          (0x2000U)
#define PWM_EPWM_DCCAPCTL_CAPSTS_SHIFT                                         (0x000DU)
#define PWM_EPWM_DCCAPCTL_CAPSTS_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPCTL_CAPSTS_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPCTL_CAPCLR_MASK                                          (0x4000U)
#define PWM_EPWM_DCCAPCTL_CAPCLR_SHIFT                                         (0x000EU)
#define PWM_EPWM_DCCAPCTL_CAPCLR_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPCTL_CAPCLR_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPCTL_CAPMODE_MASK                                         (0x8000U)
#define PWM_EPWM_DCCAPCTL_CAPMODE_SHIFT                                        (0x000FU)
#define PWM_EPWM_DCCAPCTL_CAPMODE_RESETVAL                                     (0x0000U)
#define PWM_EPWM_DCCAPCTL_CAPMODE_MAX                                          (0x0001U)

#define PWM_EPWM_DCCAPCTL_RESETVAL                                             (0x0000U)

/* DCFOFFSET */

#define PWM_EPWM_DCFOFFSET_DCFOFFSET_MASK                                      (0xFFFFU)
#define PWM_EPWM_DCFOFFSET_DCFOFFSET_SHIFT                                     (0x0000U)
#define PWM_EPWM_DCFOFFSET_DCFOFFSET_RESETVAL                                  (0x0000U)
#define PWM_EPWM_DCFOFFSET_DCFOFFSET_MAX                                       (0xFFFFU)

#define PWM_EPWM_DCFOFFSET_RESETVAL                                            (0x0000U)

/* DCFOFFSETCNT */

#define PWM_EPWM_DCFOFFSETCNT_DCFOFFSETCNT_MASK                                (0xFFFFU)
#define PWM_EPWM_DCFOFFSETCNT_DCFOFFSETCNT_SHIFT                               (0x0000U)
#define PWM_EPWM_DCFOFFSETCNT_DCFOFFSETCNT_RESETVAL                            (0x0000U)
#define PWM_EPWM_DCFOFFSETCNT_DCFOFFSETCNT_MAX                                 (0xFFFFU)

#define PWM_EPWM_DCFOFFSETCNT_RESETVAL                                         (0x0000U)

/* DCFWINDOW */

#define PWM_EPWM_DCFWINDOW_DCFWINDOW_MASK                                      (0xFFFFU)
#define PWM_EPWM_DCFWINDOW_DCFWINDOW_SHIFT                                     (0x0000U)
#define PWM_EPWM_DCFWINDOW_DCFWINDOW_RESETVAL                                  (0x0000U)
#define PWM_EPWM_DCFWINDOW_DCFWINDOW_MAX                                       (0xFFFFU)

#define PWM_EPWM_DCFWINDOW_RESETVAL                                            (0x0000U)

/* DCFWINDOWCNT */

#define PWM_EPWM_DCFWINDOWCNT_DCFWINDOWCNT_MASK                                (0xFFFFU)
#define PWM_EPWM_DCFWINDOWCNT_DCFWINDOWCNT_SHIFT                               (0x0000U)
#define PWM_EPWM_DCFWINDOWCNT_DCFWINDOWCNT_RESETVAL                            (0x0000U)
#define PWM_EPWM_DCFWINDOWCNT_DCFWINDOWCNT_MAX                                 (0xFFFFU)

#define PWM_EPWM_DCFWINDOWCNT_RESETVAL                                         (0x0000U)

/* BLANKPULSEMIXSEL */

#define PWM_EPWM_BLANKPULSEMIXSEL_ZRO_MASK                                     (0x0001U)
#define PWM_EPWM_BLANKPULSEMIXSEL_ZRO_SHIFT                                    (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_ZRO_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_ZRO_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_PRD_MASK                                     (0x0002U)
#define PWM_EPWM_BLANKPULSEMIXSEL_PRD_SHIFT                                    (0x0001U)
#define PWM_EPWM_BLANKPULSEMIXSEL_PRD_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_PRD_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CAU_MASK                                     (0x0004U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CAU_SHIFT                                    (0x0002U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CAU_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CAU_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CAD_MASK                                     (0x0008U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CAD_SHIFT                                    (0x0003U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CAD_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CAD_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CBU_MASK                                     (0x0010U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CBU_SHIFT                                    (0x0004U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CBU_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CBU_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CBD_MASK                                     (0x0020U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CBD_SHIFT                                    (0x0005U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CBD_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CBD_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CCU_MASK                                     (0x0040U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CCU_SHIFT                                    (0x0006U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CCU_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CCU_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CCD_MASK                                     (0x0080U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CCD_SHIFT                                    (0x0007U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CCD_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CCD_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CDU_MASK                                     (0x0100U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CDU_SHIFT                                    (0x0008U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CDU_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CDU_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_CDD_MASK                                     (0x0200U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CDD_SHIFT                                    (0x0009U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CDD_RESETVAL                                 (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_CDD_MAX                                      (0x0001U)

#define PWM_EPWM_BLANKPULSEMIXSEL_RESERVED_1_MASK                              (0xFC00U)
#define PWM_EPWM_BLANKPULSEMIXSEL_RESERVED_1_SHIFT                             (0x000AU)
#define PWM_EPWM_BLANKPULSEMIXSEL_RESERVED_1_RESETVAL                          (0x0000U)
#define PWM_EPWM_BLANKPULSEMIXSEL_RESERVED_1_MAX                               (0x003FU)

#define PWM_EPWM_BLANKPULSEMIXSEL_RESETVAL                                     (0x0000U)

/* DCCAPMIXSEL */

#define PWM_EPWM_DCCAPMIXSEL_ZRO_MASK                                          (0x0001U)
#define PWM_EPWM_DCCAPMIXSEL_ZRO_SHIFT                                         (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_ZRO_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_ZRO_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_PRD_MASK                                          (0x0002U)
#define PWM_EPWM_DCCAPMIXSEL_PRD_SHIFT                                         (0x0001U)
#define PWM_EPWM_DCCAPMIXSEL_PRD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_PRD_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CAU_MASK                                          (0x0004U)
#define PWM_EPWM_DCCAPMIXSEL_CAU_SHIFT                                         (0x0002U)
#define PWM_EPWM_DCCAPMIXSEL_CAU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CAU_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CAD_MASK                                          (0x0008U)
#define PWM_EPWM_DCCAPMIXSEL_CAD_SHIFT                                         (0x0003U)
#define PWM_EPWM_DCCAPMIXSEL_CAD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CAD_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CBU_MASK                                          (0x0010U)
#define PWM_EPWM_DCCAPMIXSEL_CBU_SHIFT                                         (0x0004U)
#define PWM_EPWM_DCCAPMIXSEL_CBU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CBU_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CBD_MASK                                          (0x0020U)
#define PWM_EPWM_DCCAPMIXSEL_CBD_SHIFT                                         (0x0005U)
#define PWM_EPWM_DCCAPMIXSEL_CBD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CBD_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CCU_MASK                                          (0x0040U)
#define PWM_EPWM_DCCAPMIXSEL_CCU_SHIFT                                         (0x0006U)
#define PWM_EPWM_DCCAPMIXSEL_CCU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CCU_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CCD_MASK                                          (0x0080U)
#define PWM_EPWM_DCCAPMIXSEL_CCD_SHIFT                                         (0x0007U)
#define PWM_EPWM_DCCAPMIXSEL_CCD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CCD_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CDU_MASK                                          (0x0100U)
#define PWM_EPWM_DCCAPMIXSEL_CDU_SHIFT                                         (0x0008U)
#define PWM_EPWM_DCCAPMIXSEL_CDU_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CDU_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_CDD_MASK                                          (0x0200U)
#define PWM_EPWM_DCCAPMIXSEL_CDD_SHIFT                                         (0x0009U)
#define PWM_EPWM_DCCAPMIXSEL_CDD_RESETVAL                                      (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_CDD_MAX                                           (0x0001U)

#define PWM_EPWM_DCCAPMIXSEL_RESERVED_1_MASK                                   (0xFC00U)
#define PWM_EPWM_DCCAPMIXSEL_RESERVED_1_SHIFT                                  (0x000AU)
#define PWM_EPWM_DCCAPMIXSEL_RESERVED_1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCCAPMIXSEL_RESERVED_1_MAX                                    (0x003FU)

#define PWM_EPWM_DCCAPMIXSEL_RESETVAL                                          (0x0000U)

/* DCCAP */

#define PWM_EPWM_DCCAP_DCCAP_MASK                                              (0xFFFFU)
#define PWM_EPWM_DCCAP_DCCAP_SHIFT                                             (0x0000U)
#define PWM_EPWM_DCCAP_DCCAP_RESETVAL                                          (0x0000U)
#define PWM_EPWM_DCCAP_DCCAP_MAX                                               (0xFFFFU)

#define PWM_EPWM_DCCAP_RESETVAL                                                (0x0000U)

/* RESERVED_48 */

#define PWM_EPWM_RESERVED_48_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_48_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_48_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_48_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_48_RESETVAL                                          (0x0000U)

/* DCAHTRIPSEL */

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT1_MASK                                   (0x0001U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT1_SHIFT                                  (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT1_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT2_MASK                                   (0x0002U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT2_SHIFT                                  (0x0001U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT2_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT2_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT3_MASK                                   (0x0004U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT3_SHIFT                                  (0x0002U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT3_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT3_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT4_MASK                                   (0x0008U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT4_SHIFT                                  (0x0003U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT4_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT4_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT5_MASK                                   (0x0010U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT5_SHIFT                                  (0x0004U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT5_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT5_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT6_MASK                                   (0x0020U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT6_SHIFT                                  (0x0005U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT6_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT6_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT7_MASK                                   (0x0040U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT7_SHIFT                                  (0x0006U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT7_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT7_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT8_MASK                                   (0x0080U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT8_SHIFT                                  (0x0007U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT8_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT8_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT9_MASK                                   (0x0100U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT9_SHIFT                                  (0x0008U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT9_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT9_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT10_MASK                                  (0x0200U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT10_SHIFT                                 (0x0009U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT10_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT10_MAX                                   (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT11_MASK                                  (0x0400U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT11_SHIFT                                 (0x000AU)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT11_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT11_MAX                                   (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT12_MASK                                  (0x0800U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT12_SHIFT                                 (0x000BU)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT12_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT12_MAX                                   (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT13_MASK                                  (0x1000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT13_SHIFT                                 (0x000CU)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT13_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT13_MAX                                   (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT14_MASK                                  (0x2000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT14_SHIFT                                 (0x000DU)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT14_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT14_MAX                                   (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT15_MASK                                  (0x4000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT15_SHIFT                                 (0x000EU)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT15_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_TRIPINPUT15_MAX                                   (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_RESERVED_1_MASK                                   (0x8000U)
#define PWM_EPWM_DCAHTRIPSEL_RESERVED_1_SHIFT                                  (0x000FU)
#define PWM_EPWM_DCAHTRIPSEL_RESERVED_1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCAHTRIPSEL_RESERVED_1_MAX                                    (0x0001U)

#define PWM_EPWM_DCAHTRIPSEL_RESETVAL                                          (0x0000U)

/* DCALTRIPSEL */

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT1_MASK                                   (0x0001U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT1_SHIFT                                  (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT1_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT2_MASK                                   (0x0002U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT2_SHIFT                                  (0x0001U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT2_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT2_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT3_MASK                                   (0x0004U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT3_SHIFT                                  (0x0002U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT3_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT3_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT4_MASK                                   (0x0008U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT4_SHIFT                                  (0x0003U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT4_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT4_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT5_MASK                                   (0x0010U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT5_SHIFT                                  (0x0004U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT5_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT5_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT6_MASK                                   (0x0020U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT6_SHIFT                                  (0x0005U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT6_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT6_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT7_MASK                                   (0x0040U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT7_SHIFT                                  (0x0006U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT7_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT7_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT8_MASK                                   (0x0080U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT8_SHIFT                                  (0x0007U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT8_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT8_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT9_MASK                                   (0x0100U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT9_SHIFT                                  (0x0008U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT9_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT9_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT10_MASK                                  (0x0200U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT10_SHIFT                                 (0x0009U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT10_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT10_MAX                                   (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT11_MASK                                  (0x0400U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT11_SHIFT                                 (0x000AU)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT11_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT11_MAX                                   (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT12_MASK                                  (0x0800U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT12_SHIFT                                 (0x000BU)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT12_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT12_MAX                                   (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT13_MASK                                  (0x1000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT13_SHIFT                                 (0x000CU)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT13_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT13_MAX                                   (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT14_MASK                                  (0x2000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT14_SHIFT                                 (0x000DU)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT14_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT14_MAX                                   (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT15_MASK                                  (0x4000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT15_SHIFT                                 (0x000EU)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT15_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_TRIPINPUT15_MAX                                   (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_RESERVED_1_MASK                                   (0x8000U)
#define PWM_EPWM_DCALTRIPSEL_RESERVED_1_SHIFT                                  (0x000FU)
#define PWM_EPWM_DCALTRIPSEL_RESERVED_1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCALTRIPSEL_RESERVED_1_MAX                                    (0x0001U)

#define PWM_EPWM_DCALTRIPSEL_RESETVAL                                          (0x0000U)

/* DCBHTRIPSEL */

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT1_MASK                                   (0x0001U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT1_SHIFT                                  (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT1_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT2_MASK                                   (0x0002U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT2_SHIFT                                  (0x0001U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT2_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT2_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT3_MASK                                   (0x0004U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT3_SHIFT                                  (0x0002U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT3_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT3_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT4_MASK                                   (0x0008U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT4_SHIFT                                  (0x0003U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT4_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT4_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT5_MASK                                   (0x0010U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT5_SHIFT                                  (0x0004U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT5_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT5_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT6_MASK                                   (0x0020U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT6_SHIFT                                  (0x0005U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT6_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT6_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT7_MASK                                   (0x0040U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT7_SHIFT                                  (0x0006U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT7_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT7_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT8_MASK                                   (0x0080U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT8_SHIFT                                  (0x0007U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT8_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT8_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT9_MASK                                   (0x0100U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT9_SHIFT                                  (0x0008U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT9_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT9_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT10_MASK                                  (0x0200U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT10_SHIFT                                 (0x0009U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT10_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT10_MAX                                   (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT11_MASK                                  (0x0400U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT11_SHIFT                                 (0x000AU)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT11_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT11_MAX                                   (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT12_MASK                                  (0x0800U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT12_SHIFT                                 (0x000BU)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT12_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT12_MAX                                   (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT13_MASK                                  (0x1000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT13_SHIFT                                 (0x000CU)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT13_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT13_MAX                                   (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT14_MASK                                  (0x2000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT14_SHIFT                                 (0x000DU)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT14_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT14_MAX                                   (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT15_MASK                                  (0x4000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT15_SHIFT                                 (0x000EU)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT15_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_TRIPINPUT15_MAX                                   (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_RESERVED_1_MASK                                   (0x8000U)
#define PWM_EPWM_DCBHTRIPSEL_RESERVED_1_SHIFT                                  (0x000FU)
#define PWM_EPWM_DCBHTRIPSEL_RESERVED_1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBHTRIPSEL_RESERVED_1_MAX                                    (0x0001U)

#define PWM_EPWM_DCBHTRIPSEL_RESETVAL                                          (0x0000U)

/* DCBLTRIPSEL */

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT1_MASK                                   (0x0001U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT1_SHIFT                                  (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT1_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT2_MASK                                   (0x0002U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT2_SHIFT                                  (0x0001U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT2_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT2_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT3_MASK                                   (0x0004U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT3_SHIFT                                  (0x0002U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT3_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT3_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT4_MASK                                   (0x0008U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT4_SHIFT                                  (0x0003U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT4_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT4_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT5_MASK                                   (0x0010U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT5_SHIFT                                  (0x0004U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT5_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT5_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT6_MASK                                   (0x0020U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT6_SHIFT                                  (0x0005U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT6_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT6_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT7_MASK                                   (0x0040U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT7_SHIFT                                  (0x0006U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT7_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT7_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT8_MASK                                   (0x0080U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT8_SHIFT                                  (0x0007U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT8_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT8_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT9_MASK                                   (0x0100U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT9_SHIFT                                  (0x0008U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT9_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT9_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT10_MASK                                  (0x0200U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT10_SHIFT                                 (0x0009U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT10_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT10_MAX                                   (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT11_MASK                                  (0x0400U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT11_SHIFT                                 (0x000AU)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT11_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT11_MAX                                   (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT12_MASK                                  (0x0800U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT12_SHIFT                                 (0x000BU)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT12_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT12_MAX                                   (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT13_MASK                                  (0x1000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT13_SHIFT                                 (0x000CU)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT13_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT13_MAX                                   (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT14_MASK                                  (0x2000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT14_SHIFT                                 (0x000DU)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT14_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT14_MAX                                   (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT15_MASK                                  (0x4000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT15_SHIFT                                 (0x000EU)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT15_RESETVAL                              (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_TRIPINPUT15_MAX                                   (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_RESERVED_1_MASK                                   (0x8000U)
#define PWM_EPWM_DCBLTRIPSEL_RESERVED_1_SHIFT                                  (0x000FU)
#define PWM_EPWM_DCBLTRIPSEL_RESERVED_1_RESETVAL                               (0x0000U)
#define PWM_EPWM_DCBLTRIPSEL_RESERVED_1_MAX                                    (0x0001U)

#define PWM_EPWM_DCBLTRIPSEL_RESETVAL                                          (0x0000U)

/* CAPCTL */

#define PWM_EPWM_CAPCTL_SRCSEL_MASK                                            (0x0001U)
#define PWM_EPWM_CAPCTL_SRCSEL_SHIFT                                           (0x0000U)
#define PWM_EPWM_CAPCTL_SRCSEL_RESETVAL                                        (0x0000U)
#define PWM_EPWM_CAPCTL_SRCSEL_MAX                                             (0x0001U)

#define PWM_EPWM_CAPCTL_CAPGATEPOL_MASK                                        (0x0006U)
#define PWM_EPWM_CAPCTL_CAPGATEPOL_SHIFT                                       (0x0001U)
#define PWM_EPWM_CAPCTL_CAPGATEPOL_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CAPCTL_CAPGATEPOL_MAX                                         (0x0003U)

#define PWM_EPWM_CAPCTL_CAPINPOL_MASK                                          (0x0008U)
#define PWM_EPWM_CAPCTL_CAPINPOL_SHIFT                                         (0x0003U)
#define PWM_EPWM_CAPCTL_CAPINPOL_RESETVAL                                      (0x0000U)
#define PWM_EPWM_CAPCTL_CAPINPOL_MAX                                           (0x0001U)

#define PWM_EPWM_CAPCTL_PULSECTL_MASK                                          (0x0010U)
#define PWM_EPWM_CAPCTL_PULSECTL_SHIFT                                         (0x0004U)
#define PWM_EPWM_CAPCTL_PULSECTL_RESETVAL                                      (0x0000U)
#define PWM_EPWM_CAPCTL_PULSECTL_MAX                                           (0x0001U)

#define PWM_EPWM_CAPCTL_RESERVED_1_MASK                                        (0x00E0U)
#define PWM_EPWM_CAPCTL_RESERVED_1_SHIFT                                       (0x0005U)
#define PWM_EPWM_CAPCTL_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CAPCTL_RESERVED_1_MAX                                         (0x0007U)

#define PWM_EPWM_CAPCTL_FRCLOAD_MASK                                           (0x0100U)
#define PWM_EPWM_CAPCTL_FRCLOAD_SHIFT                                          (0x0008U)
#define PWM_EPWM_CAPCTL_FRCLOAD_RESETVAL                                       (0x0000U)
#define PWM_EPWM_CAPCTL_FRCLOAD_MAX                                            (0x0001U)

#define PWM_EPWM_CAPCTL_RESERVED_2_MASK                                        (0xFE00U)
#define PWM_EPWM_CAPCTL_RESERVED_2_SHIFT                                       (0x0009U)
#define PWM_EPWM_CAPCTL_RESERVED_2_RESETVAL                                    (0x0000U)
#define PWM_EPWM_CAPCTL_RESERVED_2_MAX                                         (0x007FU)

#define PWM_EPWM_CAPCTL_RESETVAL                                               (0x0000U)

/* CAPGATETRIPSEL */

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT1_MASK                                (0x0001U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT1_SHIFT                               (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT1_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT1_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT2_MASK                                (0x0002U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT2_SHIFT                               (0x0001U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT2_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT2_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT3_MASK                                (0x0004U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT3_SHIFT                               (0x0002U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT3_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT3_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT4_MASK                                (0x0008U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT4_SHIFT                               (0x0003U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT4_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT4_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT5_MASK                                (0x0010U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT5_SHIFT                               (0x0004U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT5_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT5_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT6_MASK                                (0x0020U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT6_SHIFT                               (0x0005U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT6_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT6_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT7_MASK                                (0x0040U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT7_SHIFT                               (0x0006U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT7_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT7_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT8_MASK                                (0x0080U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT8_SHIFT                               (0x0007U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT8_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT8_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT9_MASK                                (0x0100U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT9_SHIFT                               (0x0008U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT9_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT9_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT10_MASK                               (0x0200U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT10_SHIFT                              (0x0009U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT10_RESETVAL                           (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT10_MAX                                (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT11_MASK                               (0x0400U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT11_SHIFT                              (0x000AU)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT11_RESETVAL                           (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT11_MAX                                (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT12_MASK                               (0x0800U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT12_SHIFT                              (0x000BU)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT12_RESETVAL                           (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT12_MAX                                (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT13_MASK                               (0x1000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT13_SHIFT                              (0x000CU)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT13_RESETVAL                           (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT13_MAX                                (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT14_MASK                               (0x2000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT14_SHIFT                              (0x000DU)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT14_RESETVAL                           (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT14_MAX                                (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT15_MASK                               (0x4000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT15_SHIFT                              (0x000EU)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT15_RESETVAL                           (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_TRIPINPUT15_MAX                                (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_RESERVED_1_MASK                                (0x8000U)
#define PWM_EPWM_CAPGATETRIPSEL_RESERVED_1_SHIFT                               (0x000FU)
#define PWM_EPWM_CAPGATETRIPSEL_RESERVED_1_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPGATETRIPSEL_RESERVED_1_MAX                                 (0x0001U)

#define PWM_EPWM_CAPGATETRIPSEL_RESETVAL                                       (0x0000U)

/* CAPINTRIPSEL */

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT1_MASK                                  (0x0001U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT1_SHIFT                                 (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT1_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT1_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT2_MASK                                  (0x0002U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT2_SHIFT                                 (0x0001U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT2_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT2_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT3_MASK                                  (0x0004U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT3_SHIFT                                 (0x0002U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT3_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT3_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT4_MASK                                  (0x0008U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT4_SHIFT                                 (0x0003U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT4_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT4_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT5_MASK                                  (0x0010U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT5_SHIFT                                 (0x0004U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT5_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT5_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT6_MASK                                  (0x0020U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT6_SHIFT                                 (0x0005U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT6_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT6_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT7_MASK                                  (0x0040U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT7_SHIFT                                 (0x0006U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT7_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT7_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT8_MASK                                  (0x0080U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT8_SHIFT                                 (0x0007U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT8_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT8_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT9_MASK                                  (0x0100U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT9_SHIFT                                 (0x0008U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT9_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT9_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT10_MASK                                 (0x0200U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT10_SHIFT                                (0x0009U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT10_RESETVAL                             (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT10_MAX                                  (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT11_MASK                                 (0x0400U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT11_SHIFT                                (0x000AU)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT11_RESETVAL                             (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT11_MAX                                  (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT12_MASK                                 (0x0800U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT12_SHIFT                                (0x000BU)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT12_RESETVAL                             (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT12_MAX                                  (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT13_MASK                                 (0x1000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT13_SHIFT                                (0x000CU)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT13_RESETVAL                             (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT13_MAX                                  (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT14_MASK                                 (0x2000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT14_SHIFT                                (0x000DU)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT14_RESETVAL                             (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT14_MAX                                  (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT15_MASK                                 (0x4000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT15_SHIFT                                (0x000EU)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT15_RESETVAL                             (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_TRIPINPUT15_MAX                                  (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_RESERVED_1_MASK                                  (0x8000U)
#define PWM_EPWM_CAPINTRIPSEL_RESERVED_1_SHIFT                                 (0x000FU)
#define PWM_EPWM_CAPINTRIPSEL_RESERVED_1_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPINTRIPSEL_RESERVED_1_MAX                                   (0x0001U)

#define PWM_EPWM_CAPINTRIPSEL_RESETVAL                                         (0x0000U)

/* CAPTRIPSEL */

#define PWM_EPWM_CAPTRIPSEL_CAPINCOMPSEL_MASK                                  (0x000FU)
#define PWM_EPWM_CAPTRIPSEL_CAPINCOMPSEL_SHIFT                                 (0x0000U)
#define PWM_EPWM_CAPTRIPSEL_CAPINCOMPSEL_RESETVAL                              (0x0000U)
#define PWM_EPWM_CAPTRIPSEL_CAPINCOMPSEL_MAX                                   (0x000FU)

#define PWM_EPWM_CAPTRIPSEL_CAPGATECOMPSEL_MASK                                (0x00F0U)
#define PWM_EPWM_CAPTRIPSEL_CAPGATECOMPSEL_SHIFT                               (0x0004U)
#define PWM_EPWM_CAPTRIPSEL_CAPGATECOMPSEL_RESETVAL                            (0x0000U)
#define PWM_EPWM_CAPTRIPSEL_CAPGATECOMPSEL_MAX                                 (0x000FU)

#define PWM_EPWM_CAPTRIPSEL_RESERVED_1_MASK                                    (0xFF00U)
#define PWM_EPWM_CAPTRIPSEL_RESERVED_1_SHIFT                                   (0x0008U)
#define PWM_EPWM_CAPTRIPSEL_RESERVED_1_RESETVAL                                (0x0000U)
#define PWM_EPWM_CAPTRIPSEL_RESERVED_1_MAX                                     (0x00FFU)

#define PWM_EPWM_CAPTRIPSEL_RESETVAL                                           (0x0000U)

/* RESERVED_49 */

#define PWM_EPWM_RESERVED_49_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_49_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_49_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_49_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_49_RESETVAL                                          (0x0000U)

/* SPARE1 */

#define PWM_EPWM_SPARE1_SPARE1_BITS_MASK                                       (0x00FFU)
#define PWM_EPWM_SPARE1_SPARE1_BITS_SHIFT                                      (0x0000U)
#define PWM_EPWM_SPARE1_SPARE1_BITS_RESETVAL                                   (0x0000U)
#define PWM_EPWM_SPARE1_SPARE1_BITS_MAX                                        (0x00FFU)

#define PWM_EPWM_SPARE1_RESERVED_1_MASK                                        (0xFF00U)
#define PWM_EPWM_SPARE1_RESERVED_1_SHIFT                                       (0x0008U)
#define PWM_EPWM_SPARE1_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_SPARE1_RESERVED_1_MAX                                         (0x00FFU)

#define PWM_EPWM_SPARE1_RESETVAL                                               (0x0000U)

/* RESERVED_50 */

#define PWM_EPWM_RESERVED_50_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_50_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_50_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_50_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_50_RESETVAL                                          (0x0000U)

/* SPARE2 */

#define PWM_EPWM_SPARE2_SPARE2_BITS_MASK                                       (0x00FFU)
#define PWM_EPWM_SPARE2_SPARE2_BITS_SHIFT                                      (0x0000U)
#define PWM_EPWM_SPARE2_SPARE2_BITS_RESETVAL                                   (0x0000U)
#define PWM_EPWM_SPARE2_SPARE2_BITS_MAX                                        (0x00FFU)

#define PWM_EPWM_SPARE2_RESERVED_1_MASK                                        (0xFF00U)
#define PWM_EPWM_SPARE2_RESERVED_1_SHIFT                                       (0x0008U)
#define PWM_EPWM_SPARE2_RESERVED_1_RESETVAL                                    (0x0000U)
#define PWM_EPWM_SPARE2_RESERVED_1_MAX                                         (0x00FFU)

#define PWM_EPWM_SPARE2_RESETVAL                                               (0x0000U)

/* RESERVED_51 */

#define PWM_EPWM_RESERVED_51_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_51_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_51_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_51_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_51_RESETVAL                                          (0x0000U)

/* EPWMLOCK */

#define PWM_EPWM_EPWMLOCK_HRLOCK_MASK                                          (0x00000001U)
#define PWM_EPWM_EPWMLOCK_HRLOCK_SHIFT                                         (0x00000000U)
#define PWM_EPWM_EPWMLOCK_HRLOCK_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_EPWMLOCK_HRLOCK_MAX                                           (0x00000001U)

#define PWM_EPWM_EPWMLOCK_GLLOCK_MASK                                          (0x00000002U)
#define PWM_EPWM_EPWMLOCK_GLLOCK_SHIFT                                         (0x00000001U)
#define PWM_EPWM_EPWMLOCK_GLLOCK_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_EPWMLOCK_GLLOCK_MAX                                           (0x00000001U)

#define PWM_EPWM_EPWMLOCK_TZCFGLOCK_MASK                                       (0x00000004U)
#define PWM_EPWM_EPWMLOCK_TZCFGLOCK_SHIFT                                      (0x00000002U)
#define PWM_EPWM_EPWMLOCK_TZCFGLOCK_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_EPWMLOCK_TZCFGLOCK_MAX                                        (0x00000001U)

#define PWM_EPWM_EPWMLOCK_TZCLRLOCK_MASK                                       (0x00000008U)
#define PWM_EPWM_EPWMLOCK_TZCLRLOCK_SHIFT                                      (0x00000003U)
#define PWM_EPWM_EPWMLOCK_TZCLRLOCK_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_EPWMLOCK_TZCLRLOCK_MAX                                        (0x00000001U)

#define PWM_EPWM_EPWMLOCK_DCLOCK_MASK                                          (0x00000010U)
#define PWM_EPWM_EPWMLOCK_DCLOCK_SHIFT                                         (0x00000004U)
#define PWM_EPWM_EPWMLOCK_DCLOCK_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_EPWMLOCK_DCLOCK_MAX                                           (0x00000001U)

#define PWM_EPWM_EPWMLOCK_RESERVED_1_MASK                                      (0x0000FFE0U)
#define PWM_EPWM_EPWMLOCK_RESERVED_1_SHIFT                                     (0x00000005U)
#define PWM_EPWM_EPWMLOCK_RESERVED_1_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_EPWMLOCK_RESERVED_1_MAX                                       (0x000007FFU)

#define PWM_EPWM_EPWMLOCK_KEY_MASK                                             (0xFFFF0000U)
#define PWM_EPWM_EPWMLOCK_KEY_SHIFT                                            (0x00000010U)
#define PWM_EPWM_EPWMLOCK_KEY_RESETVAL                                         (0x00000000U)
#define PWM_EPWM_EPWMLOCK_KEY_MAX                                              (0x0000FFFFU)

#define PWM_EPWM_EPWMLOCK_RESETVAL                                             (0x00000000U)

/* RESERVED_52 */

#define PWM_EPWM_RESERVED_52_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_52_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_52_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_52_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_52_RESETVAL                                          (0x0000U)

/* HWVDELVAL */

#define PWM_EPWM_HWVDELVAL_HWVDELVAL_MASK                                      (0xFFFFU)
#define PWM_EPWM_HWVDELVAL_HWVDELVAL_SHIFT                                     (0x0000U)
#define PWM_EPWM_HWVDELVAL_HWVDELVAL_RESETVAL                                  (0x0000U)
#define PWM_EPWM_HWVDELVAL_HWVDELVAL_MAX                                       (0xFFFFU)

#define PWM_EPWM_HWVDELVAL_RESETVAL                                            (0x0000U)

/* VCNTVAL */

#define PWM_EPWM_VCNTVAL_VCNTVAL_MASK                                          (0xFFFFU)
#define PWM_EPWM_VCNTVAL_VCNTVAL_SHIFT                                         (0x0000U)
#define PWM_EPWM_VCNTVAL_VCNTVAL_RESETVAL                                      (0x0000U)
#define PWM_EPWM_VCNTVAL_VCNTVAL_MAX                                           (0xFFFFU)

#define PWM_EPWM_VCNTVAL_RESETVAL                                              (0x0000U)

/* RESERVED_53 */

#define PWM_EPWM_RESERVED_53_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_53_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_53_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_53_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_53_RESETVAL                                          (0x0000U)

/* XCMPCTL1 */

#define PWM_EPWM_XCMPCTL1_XCMPEN_MASK                                          (0x00000001U)
#define PWM_EPWM_XCMPCTL1_XCMPEN_SHIFT                                         (0x00000000U)
#define PWM_EPWM_XCMPCTL1_XCMPEN_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_XCMPCTL1_XCMPEN_MAX                                           (0x00000001U)

#define PWM_EPWM_XCMPCTL1_XCMPSPLIT_MASK                                       (0x00000002U)
#define PWM_EPWM_XCMPCTL1_XCMPSPLIT_SHIFT                                      (0x00000001U)
#define PWM_EPWM_XCMPCTL1_XCMPSPLIT_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_XCMPCTL1_XCMPSPLIT_MAX                                        (0x00000001U)

#define PWM_EPWM_XCMPCTL1_RESERVED_1_MASK                                      (0x0000000CU)
#define PWM_EPWM_XCMPCTL1_RESERVED_1_SHIFT                                     (0x00000002U)
#define PWM_EPWM_XCMPCTL1_RESERVED_1_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XCMPCTL1_RESERVED_1_MAX                                       (0x00000003U)

#define PWM_EPWM_XCMPCTL1_XCMPA_ALLOC_MASK                                     (0x000000F0U)
#define PWM_EPWM_XCMPCTL1_XCMPA_ALLOC_SHIFT                                    (0x00000004U)
#define PWM_EPWM_XCMPCTL1_XCMPA_ALLOC_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_XCMPCTL1_XCMPA_ALLOC_MAX                                      (0x0000000FU)

#define PWM_EPWM_XCMPCTL1_XCMPB_ALLOC_MASK                                     (0x00000F00U)
#define PWM_EPWM_XCMPCTL1_XCMPB_ALLOC_SHIFT                                    (0x00000008U)
#define PWM_EPWM_XCMPCTL1_XCMPB_ALLOC_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_XCMPCTL1_XCMPB_ALLOC_MAX                                      (0x0000000FU)

#define PWM_EPWM_XCMPCTL1_RESERVED_2_MASK                                      (0xFFFFF000U)
#define PWM_EPWM_XCMPCTL1_RESERVED_2_SHIFT                                     (0x0000000CU)
#define PWM_EPWM_XCMPCTL1_RESERVED_2_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XCMPCTL1_RESERVED_2_MAX                                       (0x000FFFFFU)

#define PWM_EPWM_XCMPCTL1_RESETVAL                                             (0x00000000U)

/* RESERVED_54 */

#define PWM_EPWM_RESERVED_54_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_54_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_54_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_54_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_54_RESETVAL                                          (0x00000000U)

/* XLOADCTL */

#define PWM_EPWM_XLOADCTL_RESERVED_1_MASK                                      (0x00000003U)
#define PWM_EPWM_XLOADCTL_RESERVED_1_SHIFT                                     (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_1_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_1_MAX                                       (0x00000003U)

#define PWM_EPWM_XLOADCTL_LOADMODE_MASK                                        (0x00000004U)
#define PWM_EPWM_XLOADCTL_LOADMODE_SHIFT                                       (0x00000002U)
#define PWM_EPWM_XLOADCTL_LOADMODE_RESETVAL                                    (0x00000000U)
#define PWM_EPWM_XLOADCTL_LOADMODE_MAX                                         (0x00000001U)

#define PWM_EPWM_XLOADCTL_RESERVED_2_MASK                                      (0x00000008U)
#define PWM_EPWM_XLOADCTL_RESERVED_2_SHIFT                                     (0x00000003U)
#define PWM_EPWM_XLOADCTL_RESERVED_2_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_2_MAX                                       (0x00000001U)

#define PWM_EPWM_XLOADCTL_SHDWLEVEL_MASK                                       (0x00000030U)
#define PWM_EPWM_XLOADCTL_SHDWLEVEL_SHIFT                                      (0x00000004U)
#define PWM_EPWM_XLOADCTL_SHDWLEVEL_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_XLOADCTL_SHDWLEVEL_MAX                                        (0x00000003U)

#define PWM_EPWM_XLOADCTL_RESERVED_3_MASK                                      (0x000000C0U)
#define PWM_EPWM_XLOADCTL_RESERVED_3_SHIFT                                     (0x00000006U)
#define PWM_EPWM_XLOADCTL_RESERVED_3_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_3_MAX                                       (0x00000003U)

#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADONCE_MASK                             (0x00000300U)
#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADONCE_SHIFT                            (0x00000008U)
#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADONCE_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADONCE_MAX                              (0x00000003U)

#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADMULTIPLE_MASK                         (0x00000C00U)
#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADMULTIPLE_SHIFT                        (0x0000000AU)
#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADMULTIPLE_RESETVAL                     (0x00000000U)
#define PWM_EPWM_XLOADCTL_SHDWBUFPTR_LOADMULTIPLE_MAX                          (0x00000003U)

#define PWM_EPWM_XLOADCTL_RESERVED_4_MASK                                      (0x0000F000U)
#define PWM_EPWM_XLOADCTL_RESERVED_4_SHIFT                                     (0x0000000CU)
#define PWM_EPWM_XLOADCTL_RESERVED_4_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_4_MAX                                       (0x0000000FU)

#define PWM_EPWM_XLOADCTL_RPTBUF2PRD_MASK                                      (0x00070000U)
#define PWM_EPWM_XLOADCTL_RPTBUF2PRD_SHIFT                                     (0x00000010U)
#define PWM_EPWM_XLOADCTL_RPTBUF2PRD_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RPTBUF2PRD_MAX                                       (0x00000007U)

#define PWM_EPWM_XLOADCTL_RESERVED_5_MASK                                      (0x00080000U)
#define PWM_EPWM_XLOADCTL_RESERVED_5_SHIFT                                     (0x00000013U)
#define PWM_EPWM_XLOADCTL_RESERVED_5_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_5_MAX                                       (0x00000001U)

#define PWM_EPWM_XLOADCTL_RPTBUF2CNT_MASK                                      (0x00700000U)
#define PWM_EPWM_XLOADCTL_RPTBUF2CNT_SHIFT                                     (0x00000014U)
#define PWM_EPWM_XLOADCTL_RPTBUF2CNT_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RPTBUF2CNT_MAX                                       (0x00000007U)

#define PWM_EPWM_XLOADCTL_RESERVED_6_MASK                                      (0x00800000U)
#define PWM_EPWM_XLOADCTL_RESERVED_6_SHIFT                                     (0x00000017U)
#define PWM_EPWM_XLOADCTL_RESERVED_6_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_6_MAX                                       (0x00000001U)

#define PWM_EPWM_XLOADCTL_RPTBUF3PRD_MASK                                      (0x07000000U)
#define PWM_EPWM_XLOADCTL_RPTBUF3PRD_SHIFT                                     (0x00000018U)
#define PWM_EPWM_XLOADCTL_RPTBUF3PRD_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RPTBUF3PRD_MAX                                       (0x00000007U)

#define PWM_EPWM_XLOADCTL_RESERVED_7_MASK                                      (0x08000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_7_SHIFT                                     (0x0000001BU)
#define PWM_EPWM_XLOADCTL_RESERVED_7_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_7_MAX                                       (0x00000001U)

#define PWM_EPWM_XLOADCTL_RPTBUF3CNT_MASK                                      (0x70000000U)
#define PWM_EPWM_XLOADCTL_RPTBUF3CNT_SHIFT                                     (0x0000001CU)
#define PWM_EPWM_XLOADCTL_RPTBUF3CNT_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RPTBUF3CNT_MAX                                       (0x00000007U)

#define PWM_EPWM_XLOADCTL_RESERVED_8_MASK                                      (0x80000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_8_SHIFT                                     (0x0000001FU)
#define PWM_EPWM_XLOADCTL_RESERVED_8_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_XLOADCTL_RESERVED_8_MAX                                       (0x00000001U)

#define PWM_EPWM_XLOADCTL_RESETVAL                                             (0x00000000U)

/* RESERVED_55 */

#define PWM_EPWM_RESERVED_55_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_55_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_55_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_55_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_55_RESETVAL                                          (0x00000000U)

/* XLOAD */

#define PWM_EPWM_XLOAD_STARTLD_MASK                                            (0x00000001U)
#define PWM_EPWM_XLOAD_STARTLD_SHIFT                                           (0x00000000U)
#define PWM_EPWM_XLOAD_STARTLD_RESETVAL                                        (0x00000000U)
#define PWM_EPWM_XLOAD_STARTLD_MAX                                             (0x00000001U)

#define PWM_EPWM_XLOAD_FRCLD_MASK                                              (0x00000002U)
#define PWM_EPWM_XLOAD_FRCLD_SHIFT                                             (0x00000001U)
#define PWM_EPWM_XLOAD_FRCLD_RESETVAL                                          (0x00000000U)
#define PWM_EPWM_XLOAD_FRCLD_MAX                                               (0x00000001U)

#define PWM_EPWM_XLOAD_RESERVED_1_MASK                                         (0xFFFFFFFCU)
#define PWM_EPWM_XLOAD_RESERVED_1_SHIFT                                        (0x00000002U)
#define PWM_EPWM_XLOAD_RESERVED_1_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_XLOAD_RESERVED_1_MAX                                          (0x3FFFFFFFU)

#define PWM_EPWM_XLOAD_RESETVAL                                                (0x00000000U)

/* EPWMXLINKXLOAD */

#define PWM_EPWM_EPWMXLINKXLOAD_XLOADLINK_MASK                                 (0x0000001FU)
#define PWM_EPWM_EPWMXLINKXLOAD_XLOADLINK_SHIFT                                (0x00000000U)
#define PWM_EPWM_EPWMXLINKXLOAD_XLOADLINK_RESETVAL                             (0x00000000U)
#define PWM_EPWM_EPWMXLINKXLOAD_XLOADLINK_MAX                                  (0x0000001FU)

#define PWM_EPWM_EPWMXLINKXLOAD_RESERVED_1_MASK                                (0xFFFFFFE0U)
#define PWM_EPWM_EPWMXLINKXLOAD_RESERVED_1_SHIFT                               (0x00000005U)
#define PWM_EPWM_EPWMXLINKXLOAD_RESERVED_1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_EPWMXLINKXLOAD_RESERVED_1_MAX                                 (0x07FFFFFFU)

#define PWM_EPWM_EPWMXLINKXLOAD_RESETVAL                                       (0x00000000U)

/* XREGSHDW1STS */

#define PWM_EPWM_XREGSHDW1STS_XCMP1_SHDW1FULL_MASK                             (0x00000001U)
#define PWM_EPWM_XREGSHDW1STS_XCMP1_SHDW1FULL_SHIFT                            (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP1_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP1_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XCMP2_SHDW1FULL_MASK                             (0x00000002U)
#define PWM_EPWM_XREGSHDW1STS_XCMP2_SHDW1FULL_SHIFT                            (0x00000001U)
#define PWM_EPWM_XREGSHDW1STS_XCMP2_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP2_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XCMP3_SHDW1FULL_MASK                             (0x00000004U)
#define PWM_EPWM_XREGSHDW1STS_XCMP3_SHDW1FULL_SHIFT                            (0x00000002U)
#define PWM_EPWM_XREGSHDW1STS_XCMP3_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP3_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XCMP4_SHDW1FULL_MASK                             (0x00000008U)
#define PWM_EPWM_XREGSHDW1STS_XCMP4_SHDW1FULL_SHIFT                            (0x00000003U)
#define PWM_EPWM_XREGSHDW1STS_XCMP4_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP4_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XCMP5_SHDW1FULL_MASK                             (0x00000010U)
#define PWM_EPWM_XREGSHDW1STS_XCMP5_SHDW1FULL_SHIFT                            (0x00000004U)
#define PWM_EPWM_XREGSHDW1STS_XCMP5_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP5_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XCMP6_SHDW1FULL_MASK                             (0x00000020U)
#define PWM_EPWM_XREGSHDW1STS_XCMP6_SHDW1FULL_SHIFT                            (0x00000005U)
#define PWM_EPWM_XREGSHDW1STS_XCMP6_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP6_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XCMP7_SHDW1FULL_MASK                             (0x00000040U)
#define PWM_EPWM_XREGSHDW1STS_XCMP7_SHDW1FULL_SHIFT                            (0x00000006U)
#define PWM_EPWM_XREGSHDW1STS_XCMP7_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP7_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XCMP8_SHDW1FULL_MASK                             (0x00000080U)
#define PWM_EPWM_XREGSHDW1STS_XCMP8_SHDW1FULL_SHIFT                            (0x00000007U)
#define PWM_EPWM_XREGSHDW1STS_XCMP8_SHDW1FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XCMP8_SHDW1FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XTBPRD_SHDW1FULL_MASK                            (0x00000100U)
#define PWM_EPWM_XREGSHDW1STS_XTBPRD_SHDW1FULL_SHIFT                           (0x00000008U)
#define PWM_EPWM_XREGSHDW1STS_XTBPRD_SHDW1FULL_RESETVAL                        (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XTBPRD_SHDW1FULL_MAX                             (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_CMPC_SHDW1FULL_MASK                              (0x00000200U)
#define PWM_EPWM_XREGSHDW1STS_CMPC_SHDW1FULL_SHIFT                             (0x00000009U)
#define PWM_EPWM_XREGSHDW1STS_CMPC_SHDW1FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_CMPC_SHDW1FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_CMPD_SHDW1FULL_MASK                              (0x00000400U)
#define PWM_EPWM_XREGSHDW1STS_CMPD_SHDW1FULL_SHIFT                             (0x0000000AU)
#define PWM_EPWM_XREGSHDW1STS_CMPD_SHDW1FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_CMPD_SHDW1FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XAQCTLA_SHDW1FULL_MASK                           (0x00000800U)
#define PWM_EPWM_XREGSHDW1STS_XAQCTLA_SHDW1FULL_SHIFT                          (0x0000000BU)
#define PWM_EPWM_XREGSHDW1STS_XAQCTLA_SHDW1FULL_RESETVAL                       (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XAQCTLA_SHDW1FULL_MAX                            (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XAQCTLB_SHDW1FULL_MASK                           (0x00001000U)
#define PWM_EPWM_XREGSHDW1STS_XAQCTLB_SHDW1FULL_SHIFT                          (0x0000000CU)
#define PWM_EPWM_XREGSHDW1STS_XAQCTLB_SHDW1FULL_RESETVAL                       (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XAQCTLB_SHDW1FULL_MAX                            (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XMAX_SHDW1FULL_MASK                              (0x00002000U)
#define PWM_EPWM_XREGSHDW1STS_XMAX_SHDW1FULL_SHIFT                             (0x0000000DU)
#define PWM_EPWM_XREGSHDW1STS_XMAX_SHDW1FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XMAX_SHDW1FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_XMIN_SHDW1FULL_MASK                              (0x00004000U)
#define PWM_EPWM_XREGSHDW1STS_XMIN_SHDW1FULL_SHIFT                             (0x0000000EU)
#define PWM_EPWM_XREGSHDW1STS_XMIN_SHDW1FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_XMIN_SHDW1FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW1STS_RESERVED_1_MASK                                  (0xFFFF8000U)
#define PWM_EPWM_XREGSHDW1STS_RESERVED_1_SHIFT                                 (0x0000000FU)
#define PWM_EPWM_XREGSHDW1STS_RESERVED_1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XREGSHDW1STS_RESERVED_1_MAX                                   (0x0001FFFFU)

#define PWM_EPWM_XREGSHDW1STS_RESETVAL                                         (0x00000000U)

/* RESERVED_56 */

#define PWM_EPWM_RESERVED_56_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_56_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_56_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_56_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_56_RESETVAL                                          (0x00000000U)

/* XREGSHDW2STS */

#define PWM_EPWM_XREGSHDW2STS_XCMP1_SHDW2FULL_MASK                             (0x00000001U)
#define PWM_EPWM_XREGSHDW2STS_XCMP1_SHDW2FULL_SHIFT                            (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP1_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP1_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XCMP2_SHDW2FULL_MASK                             (0x00000002U)
#define PWM_EPWM_XREGSHDW2STS_XCMP2_SHDW2FULL_SHIFT                            (0x00000001U)
#define PWM_EPWM_XREGSHDW2STS_XCMP2_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP2_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XCMP3_SHDW2FULL_MASK                             (0x00000004U)
#define PWM_EPWM_XREGSHDW2STS_XCMP3_SHDW2FULL_SHIFT                            (0x00000002U)
#define PWM_EPWM_XREGSHDW2STS_XCMP3_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP3_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XCMP4_SHDW2FULL_MASK                             (0x00000008U)
#define PWM_EPWM_XREGSHDW2STS_XCMP4_SHDW2FULL_SHIFT                            (0x00000003U)
#define PWM_EPWM_XREGSHDW2STS_XCMP4_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP4_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XCMP5_SHDW2FULL_MASK                             (0x00000010U)
#define PWM_EPWM_XREGSHDW2STS_XCMP5_SHDW2FULL_SHIFT                            (0x00000004U)
#define PWM_EPWM_XREGSHDW2STS_XCMP5_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP5_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XCMP6_SHDW2FULL_MASK                             (0x00000020U)
#define PWM_EPWM_XREGSHDW2STS_XCMP6_SHDW2FULL_SHIFT                            (0x00000005U)
#define PWM_EPWM_XREGSHDW2STS_XCMP6_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP6_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XCMP7_SHDW2FULL_MASK                             (0x00000040U)
#define PWM_EPWM_XREGSHDW2STS_XCMP7_SHDW2FULL_SHIFT                            (0x00000006U)
#define PWM_EPWM_XREGSHDW2STS_XCMP7_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP7_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XCMP8_SHDW2FULL_MASK                             (0x00000080U)
#define PWM_EPWM_XREGSHDW2STS_XCMP8_SHDW2FULL_SHIFT                            (0x00000007U)
#define PWM_EPWM_XREGSHDW2STS_XCMP8_SHDW2FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XCMP8_SHDW2FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XTBPRD_SHDW2FULL_MASK                            (0x00000100U)
#define PWM_EPWM_XREGSHDW2STS_XTBPRD_SHDW2FULL_SHIFT                           (0x00000008U)
#define PWM_EPWM_XREGSHDW2STS_XTBPRD_SHDW2FULL_RESETVAL                        (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XTBPRD_SHDW2FULL_MAX                             (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_CMPC_SHDW2FULL_MASK                              (0x00000200U)
#define PWM_EPWM_XREGSHDW2STS_CMPC_SHDW2FULL_SHIFT                             (0x00000009U)
#define PWM_EPWM_XREGSHDW2STS_CMPC_SHDW2FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_CMPC_SHDW2FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_CMPD_SHDW2FULL_MASK                              (0x00000400U)
#define PWM_EPWM_XREGSHDW2STS_CMPD_SHDW2FULL_SHIFT                             (0x0000000AU)
#define PWM_EPWM_XREGSHDW2STS_CMPD_SHDW2FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_CMPD_SHDW2FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XAQCTLA_SHDW2FULL_MASK                           (0x00000800U)
#define PWM_EPWM_XREGSHDW2STS_XAQCTLA_SHDW2FULL_SHIFT                          (0x0000000BU)
#define PWM_EPWM_XREGSHDW2STS_XAQCTLA_SHDW2FULL_RESETVAL                       (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XAQCTLA_SHDW2FULL_MAX                            (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XAQCTLB_SHDW2FULL_MASK                           (0x00001000U)
#define PWM_EPWM_XREGSHDW2STS_XAQCTLB_SHDW2FULL_SHIFT                          (0x0000000CU)
#define PWM_EPWM_XREGSHDW2STS_XAQCTLB_SHDW2FULL_RESETVAL                       (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XAQCTLB_SHDW2FULL_MAX                            (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XMAX_SHDW2FULL_MASK                              (0x00002000U)
#define PWM_EPWM_XREGSHDW2STS_XMAX_SHDW2FULL_SHIFT                             (0x0000000DU)
#define PWM_EPWM_XREGSHDW2STS_XMAX_SHDW2FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XMAX_SHDW2FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_XMIN_SHDW2FULL_MASK                              (0x00004000U)
#define PWM_EPWM_XREGSHDW2STS_XMIN_SHDW2FULL_SHIFT                             (0x0000000EU)
#define PWM_EPWM_XREGSHDW2STS_XMIN_SHDW2FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_XMIN_SHDW2FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW2STS_RESERVED_1_MASK                                  (0xFFFF8000U)
#define PWM_EPWM_XREGSHDW2STS_RESERVED_1_SHIFT                                 (0x0000000FU)
#define PWM_EPWM_XREGSHDW2STS_RESERVED_1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XREGSHDW2STS_RESERVED_1_MAX                                   (0x0001FFFFU)

#define PWM_EPWM_XREGSHDW2STS_RESETVAL                                         (0x00000000U)

/* RESERVED_57 */

#define PWM_EPWM_RESERVED_57_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_57_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_57_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_57_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_57_RESETVAL                                          (0x00000000U)

/* XREGSHDW3STS */

#define PWM_EPWM_XREGSHDW3STS_XCMP1_SHDW3FULL_MASK                             (0x00000001U)
#define PWM_EPWM_XREGSHDW3STS_XCMP1_SHDW3FULL_SHIFT                            (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP1_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP1_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XCMP2_SHDW3FULL_MASK                             (0x00000002U)
#define PWM_EPWM_XREGSHDW3STS_XCMP2_SHDW3FULL_SHIFT                            (0x00000001U)
#define PWM_EPWM_XREGSHDW3STS_XCMP2_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP2_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XCMP3_SHDW3FULL_MASK                             (0x00000004U)
#define PWM_EPWM_XREGSHDW3STS_XCMP3_SHDW3FULL_SHIFT                            (0x00000002U)
#define PWM_EPWM_XREGSHDW3STS_XCMP3_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP3_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XCMP4_SHDW3FULL_MASK                             (0x00000008U)
#define PWM_EPWM_XREGSHDW3STS_XCMP4_SHDW3FULL_SHIFT                            (0x00000003U)
#define PWM_EPWM_XREGSHDW3STS_XCMP4_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP4_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XCMP5_SHDW3FULL_MASK                             (0x00000010U)
#define PWM_EPWM_XREGSHDW3STS_XCMP5_SHDW3FULL_SHIFT                            (0x00000004U)
#define PWM_EPWM_XREGSHDW3STS_XCMP5_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP5_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XCMP6_SHDW3FULL_MASK                             (0x00000020U)
#define PWM_EPWM_XREGSHDW3STS_XCMP6_SHDW3FULL_SHIFT                            (0x00000005U)
#define PWM_EPWM_XREGSHDW3STS_XCMP6_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP6_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XCMP7_SHDW3FULL_MASK                             (0x00000040U)
#define PWM_EPWM_XREGSHDW3STS_XCMP7_SHDW3FULL_SHIFT                            (0x00000006U)
#define PWM_EPWM_XREGSHDW3STS_XCMP7_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP7_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XCMP8_SHDW3FULL_MASK                             (0x00000080U)
#define PWM_EPWM_XREGSHDW3STS_XCMP8_SHDW3FULL_SHIFT                            (0x00000007U)
#define PWM_EPWM_XREGSHDW3STS_XCMP8_SHDW3FULL_RESETVAL                         (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XCMP8_SHDW3FULL_MAX                              (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XTBPRD_SHDW3FULL_MASK                            (0x00000100U)
#define PWM_EPWM_XREGSHDW3STS_XTBPRD_SHDW3FULL_SHIFT                           (0x00000008U)
#define PWM_EPWM_XREGSHDW3STS_XTBPRD_SHDW3FULL_RESETVAL                        (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XTBPRD_SHDW3FULL_MAX                             (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_CMPC_SHDW3FULL_MASK                              (0x00000200U)
#define PWM_EPWM_XREGSHDW3STS_CMPC_SHDW3FULL_SHIFT                             (0x00000009U)
#define PWM_EPWM_XREGSHDW3STS_CMPC_SHDW3FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_CMPC_SHDW3FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_CMPD_SHDW3FULL_MASK                              (0x00000400U)
#define PWM_EPWM_XREGSHDW3STS_CMPD_SHDW3FULL_SHIFT                             (0x0000000AU)
#define PWM_EPWM_XREGSHDW3STS_CMPD_SHDW3FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_CMPD_SHDW3FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XAQCTLA_SHDW3FULL_MASK                           (0x00000800U)
#define PWM_EPWM_XREGSHDW3STS_XAQCTLA_SHDW3FULL_SHIFT                          (0x0000000BU)
#define PWM_EPWM_XREGSHDW3STS_XAQCTLA_SHDW3FULL_RESETVAL                       (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XAQCTLA_SHDW3FULL_MAX                            (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XAQCTLB_SHDW3FULL_MASK                           (0x00001000U)
#define PWM_EPWM_XREGSHDW3STS_XAQCTLB_SHDW3FULL_SHIFT                          (0x0000000CU)
#define PWM_EPWM_XREGSHDW3STS_XAQCTLB_SHDW3FULL_RESETVAL                       (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XAQCTLB_SHDW3FULL_MAX                            (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XMAX_SHDW3FULL_MASK                              (0x00002000U)
#define PWM_EPWM_XREGSHDW3STS_XMAX_SHDW3FULL_SHIFT                             (0x0000000DU)
#define PWM_EPWM_XREGSHDW3STS_XMAX_SHDW3FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XMAX_SHDW3FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_XMIN_SHDW3FULL_MASK                              (0x00004000U)
#define PWM_EPWM_XREGSHDW3STS_XMIN_SHDW3FULL_SHIFT                             (0x0000000EU)
#define PWM_EPWM_XREGSHDW3STS_XMIN_SHDW3FULL_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_XMIN_SHDW3FULL_MAX                               (0x00000001U)

#define PWM_EPWM_XREGSHDW3STS_RESERVED_1_MASK                                  (0xFFFF8000U)
#define PWM_EPWM_XREGSHDW3STS_RESERVED_1_SHIFT                                 (0x0000000FU)
#define PWM_EPWM_XREGSHDW3STS_RESERVED_1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XREGSHDW3STS_RESERVED_1_MAX                                   (0x0001FFFFU)

#define PWM_EPWM_XREGSHDW3STS_RESETVAL                                         (0x00000000U)

/* RESERVED_58 */

#define PWM_EPWM_RESERVED_58_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_58_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_58_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_58_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_58_RESETVAL                                          (0x00000000U)

/* XCMP1_ACTIVE */

#define PWM_EPWM_XCMP1_ACTIVE_XCMP1HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP1_ACTIVE_XCMP1HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP1_ACTIVE_XCMP1HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP1_ACTIVE_XCMP1HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP1_ACTIVE_XCMP1_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP1_ACTIVE_XCMP1_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP1_ACTIVE_XCMP1_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP1_ACTIVE_XCMP1_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP1_ACTIVE_RESETVAL                                         (0x00000000U)

/* XCMP2_ACTIVE */

#define PWM_EPWM_XCMP2_ACTIVE_XCMP2HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP2_ACTIVE_XCMP2HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP2_ACTIVE_XCMP2HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP2_ACTIVE_XCMP2HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP2_ACTIVE_XCMP2_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP2_ACTIVE_XCMP2_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP2_ACTIVE_XCMP2_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP2_ACTIVE_XCMP2_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP2_ACTIVE_RESETVAL                                         (0x00000000U)

/* XCMP3_ACTIVE */

#define PWM_EPWM_XCMP3_ACTIVE_XCMP3HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP3_ACTIVE_XCMP3HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP3_ACTIVE_XCMP3HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP3_ACTIVE_XCMP3HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP3_ACTIVE_XCMP3_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP3_ACTIVE_XCMP3_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP3_ACTIVE_XCMP3_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP3_ACTIVE_XCMP3_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP3_ACTIVE_RESETVAL                                         (0x00000000U)

/* XCMP4_ACTIVE */

#define PWM_EPWM_XCMP4_ACTIVE_XCMP4HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP4_ACTIVE_XCMP4HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP4_ACTIVE_XCMP4HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP4_ACTIVE_XCMP4HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP4_ACTIVE_XCMP4_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP4_ACTIVE_XCMP4_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP4_ACTIVE_XCMP4_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP4_ACTIVE_XCMP4_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP4_ACTIVE_RESETVAL                                         (0x00000000U)

/* XCMP5_ACTIVE */

#define PWM_EPWM_XCMP5_ACTIVE_XCMP5HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP5_ACTIVE_XCMP5HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP5_ACTIVE_XCMP5HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP5_ACTIVE_XCMP5HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP5_ACTIVE_XCMP5_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP5_ACTIVE_XCMP5_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP5_ACTIVE_XCMP5_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP5_ACTIVE_XCMP5_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP5_ACTIVE_RESETVAL                                         (0x00000000U)

/* XCMP6_ACTIVE */

#define PWM_EPWM_XCMP6_ACTIVE_XCMP6HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP6_ACTIVE_XCMP6HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP6_ACTIVE_XCMP6HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP6_ACTIVE_XCMP6HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP6_ACTIVE_XCMP6_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP6_ACTIVE_XCMP6_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP6_ACTIVE_XCMP6_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP6_ACTIVE_XCMP6_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP6_ACTIVE_RESETVAL                                         (0x00000000U)

/* XCMP7_ACTIVE */

#define PWM_EPWM_XCMP7_ACTIVE_XCMP7HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP7_ACTIVE_XCMP7HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP7_ACTIVE_XCMP7HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP7_ACTIVE_XCMP7HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP7_ACTIVE_XCMP7_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP7_ACTIVE_XCMP7_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP7_ACTIVE_XCMP7_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP7_ACTIVE_XCMP7_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP7_ACTIVE_RESETVAL                                         (0x00000000U)

/* XCMP8_ACTIVE */

#define PWM_EPWM_XCMP8_ACTIVE_XCMP8HR_ACTIVE_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XCMP8_ACTIVE_XCMP8HR_ACTIVE_SHIFT                             (0x00000000U)
#define PWM_EPWM_XCMP8_ACTIVE_XCMP8HR_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XCMP8_ACTIVE_XCMP8HR_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XCMP8_ACTIVE_XCMP8_ACTIVE_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XCMP8_ACTIVE_XCMP8_ACTIVE_SHIFT                               (0x00000010U)
#define PWM_EPWM_XCMP8_ACTIVE_XCMP8_ACTIVE_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP8_ACTIVE_XCMP8_ACTIVE_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP8_ACTIVE_RESETVAL                                         (0x00000000U)

/* XTBPRD_ACTIVE */

#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRDHR_ACTIVE_MASK                            (0x0000FFFFU)
#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRDHR_ACTIVE_SHIFT                           (0x00000000U)
#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRDHR_ACTIVE_RESETVAL                        (0x00000000U)
#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRDHR_ACTIVE_MAX                             (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRD_ACTIVE_MASK                              (0xFFFF0000U)
#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRD_ACTIVE_SHIFT                             (0x00000010U)
#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRD_ACTIVE_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XTBPRD_ACTIVE_XTBPRD_ACTIVE_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_ACTIVE_RESETVAL                                        (0x00000000U)

/* RESERVED_59 */

#define PWM_EPWM_RESERVED_59_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_59_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_59_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_59_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_59_RESETVAL                                          (0x00000000U)

/* XAQCTLA_ACTIVE */

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP1_MASK                                     (0x0003U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP1_SHIFT                                    (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP1_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP1_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP2_MASK                                     (0x000CU)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP2_SHIFT                                    (0x0002U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP2_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP2_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP3_MASK                                     (0x0030U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP3_SHIFT                                    (0x0004U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP3_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP3_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP4_MASK                                     (0x00C0U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP4_SHIFT                                    (0x0006U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP4_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP4_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP5_MASK                                     (0x0300U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP5_SHIFT                                    (0x0008U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP5_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP5_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP6_MASK                                     (0x0C00U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP6_SHIFT                                    (0x000AU)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP6_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP6_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP7_MASK                                     (0x3000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP7_SHIFT                                    (0x000CU)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP7_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP7_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP8_MASK                                     (0xC000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP8_SHIFT                                    (0x000EU)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP8_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLA_ACTIVE_XCMP8_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLA_ACTIVE_RESETVAL                                       (0x0000U)

/* XAQCTLB_ACTIVE */

#define PWM_EPWM_XAQCTLB_ACTIVE_RESERVED_1_MASK                                (0x00FFU)
#define PWM_EPWM_XAQCTLB_ACTIVE_RESERVED_1_SHIFT                               (0x0000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_RESERVED_1_RESETVAL                            (0x0000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_RESERVED_1_MAX                                 (0x00FFU)

#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP5_MASK                                     (0x0300U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP5_SHIFT                                    (0x0008U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP5_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP5_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP6_MASK                                     (0x0C00U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP6_SHIFT                                    (0x000AU)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP6_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP6_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP7_MASK                                     (0x3000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP7_SHIFT                                    (0x000CU)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP7_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP7_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP8_MASK                                     (0xC000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP8_SHIFT                                    (0x000EU)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP8_RESETVAL                                 (0x0000U)
#define PWM_EPWM_XAQCTLB_ACTIVE_XCMP8_MAX                                      (0x0003U)

#define PWM_EPWM_XAQCTLB_ACTIVE_RESETVAL                                       (0x0000U)

/* RESERVED_60 */

#define PWM_EPWM_RESERVED_60_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_60_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_60_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_60_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_60_RESETVAL                                          (0x00000000U)

/* XMINMAX_ACTIVE */

#define PWM_EPWM_XMINMAX_ACTIVE_XMAX_ACTIVE_MASK                               (0x0000FFFFU)
#define PWM_EPWM_XMINMAX_ACTIVE_XMAX_ACTIVE_SHIFT                              (0x00000000U)
#define PWM_EPWM_XMINMAX_ACTIVE_XMAX_ACTIVE_RESETVAL                           (0x00000000U)
#define PWM_EPWM_XMINMAX_ACTIVE_XMAX_ACTIVE_MAX                                (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_ACTIVE_XMIN_ACTIVE_MASK                               (0xFFFF0000U)
#define PWM_EPWM_XMINMAX_ACTIVE_XMIN_ACTIVE_SHIFT                              (0x00000010U)
#define PWM_EPWM_XMINMAX_ACTIVE_XMIN_ACTIVE_RESETVAL                           (0x00000000U)
#define PWM_EPWM_XMINMAX_ACTIVE_XMIN_ACTIVE_MAX                                (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_ACTIVE_RESETVAL                                       (0x00000000U)

/* RESERVED_61 */

#define PWM_EPWM_RESERVED_61_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_61_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_61_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_61_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_61_RESETVAL                                          (0x00000000U)

/* XCMP1_SHDW1 */

#define PWM_EPWM_XCMP1_SHDW1_XCMP1HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP1_SHDW1_XCMP1HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW1_XCMP1HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW1_XCMP1HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP1_SHDW1_XCMP1_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP1_SHDW1_XCMP1_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP1_SHDW1_XCMP1_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW1_XCMP1_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP1_SHDW1_RESETVAL                                          (0x00000000U)

/* XCMP2_SHDW1 */

#define PWM_EPWM_XCMP2_SHDW1_XCMP2HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP2_SHDW1_XCMP2HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW1_XCMP2HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW1_XCMP2HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP2_SHDW1_XCMP2_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP2_SHDW1_XCMP2_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP2_SHDW1_XCMP2_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW1_XCMP2_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP2_SHDW1_RESETVAL                                          (0x00000000U)

/* XCMP3_SHDW1 */

#define PWM_EPWM_XCMP3_SHDW1_XCMP3HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP3_SHDW1_XCMP3HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW1_XCMP3HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW1_XCMP3HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP3_SHDW1_XCMP3_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP3_SHDW1_XCMP3_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP3_SHDW1_XCMP3_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW1_XCMP3_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP3_SHDW1_RESETVAL                                          (0x00000000U)

/* XCMP4_SHDW1 */

#define PWM_EPWM_XCMP4_SHDW1_XCMP4HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP4_SHDW1_XCMP4HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW1_XCMP4HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW1_XCMP4HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP4_SHDW1_XCMP4_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP4_SHDW1_XCMP4_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP4_SHDW1_XCMP4_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW1_XCMP4_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP4_SHDW1_RESETVAL                                          (0x00000000U)

/* XCMP5_SHDW1 */

#define PWM_EPWM_XCMP5_SHDW1_XCMP5HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP5_SHDW1_XCMP5HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW1_XCMP5HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW1_XCMP5HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP5_SHDW1_XCMP5_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP5_SHDW1_XCMP5_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP5_SHDW1_XCMP5_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW1_XCMP5_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP5_SHDW1_RESETVAL                                          (0x00000000U)

/* XCMP6_SHDW1 */

#define PWM_EPWM_XCMP6_SHDW1_XCMP6HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP6_SHDW1_XCMP6HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW1_XCMP6HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW1_XCMP6HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP6_SHDW1_XCMP6_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP6_SHDW1_XCMP6_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP6_SHDW1_XCMP6_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW1_XCMP6_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP6_SHDW1_RESETVAL                                          (0x00000000U)

/* XCMP7_SHDW1 */

#define PWM_EPWM_XCMP7_SHDW1_XCMP7HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP7_SHDW1_XCMP7HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW1_XCMP7HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW1_XCMP7HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP7_SHDW1_XCMP7_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP7_SHDW1_XCMP7_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP7_SHDW1_XCMP7_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW1_XCMP7_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP7_SHDW1_RESETVAL                                          (0x00000000U)

/* XCMP8_SHDW1 */

#define PWM_EPWM_XCMP8_SHDW1_XCMP8HR_SHDW1_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP8_SHDW1_XCMP8HR_SHDW1_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW1_XCMP8HR_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW1_XCMP8HR_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP8_SHDW1_XCMP8_SHDW1_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP8_SHDW1_XCMP8_SHDW1_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP8_SHDW1_XCMP8_SHDW1_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW1_XCMP8_SHDW1_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP8_SHDW1_RESETVAL                                          (0x00000000U)

/* XTBPRD_SHDW1 */

#define PWM_EPWM_XTBPRD_SHDW1_XTBPRDHR_SHDW1_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XTBPRD_SHDW1_XTBPRDHR_SHDW1_SHIFT                             (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW1_XTBPRDHR_SHDW1_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW1_XTBPRDHR_SHDW1_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_SHDW1_XTBPRD_SHDW1_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XTBPRD_SHDW1_XTBPRD_SHDW1_SHIFT                               (0x00000010U)
#define PWM_EPWM_XTBPRD_SHDW1_XTBPRD_SHDW1_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW1_XTBPRD_SHDW1_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_SHDW1_RESETVAL                                         (0x00000000U)

/* RESERVED_62 */

#define PWM_EPWM_RESERVED_62_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_62_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_62_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_62_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_62_RESETVAL                                          (0x00000000U)

/* XAQCTLA_SHDW1 */

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP1_MASK                                      (0x0003U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP1_SHIFT                                     (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP1_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP2_MASK                                      (0x000CU)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP2_SHIFT                                     (0x0002U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP2_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP2_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP3_MASK                                      (0x0030U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP3_SHIFT                                     (0x0004U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP3_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP3_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP4_MASK                                      (0x00C0U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP4_SHIFT                                     (0x0006U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP4_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP4_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP5_MASK                                      (0x0300U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP5_SHIFT                                     (0x0008U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP5_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP5_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP6_MASK                                      (0x0C00U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP6_SHIFT                                     (0x000AU)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP6_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP6_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP7_MASK                                      (0x3000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP7_SHIFT                                     (0x000CU)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP7_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP7_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_XCMP8_MASK                                      (0xC000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP8_SHIFT                                     (0x000EU)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP8_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW1_XCMP8_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW1_RESETVAL                                        (0x0000U)

/* XAQCTLB_SHDW1 */

#define PWM_EPWM_XAQCTLB_SHDW1_RESERVED_1_MASK                                 (0x00FFU)
#define PWM_EPWM_XAQCTLB_SHDW1_RESERVED_1_SHIFT                                (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW1_RESERVED_1_RESETVAL                             (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW1_RESERVED_1_MAX                                  (0x00FFU)

#define PWM_EPWM_XAQCTLB_SHDW1_XCMP5_MASK                                      (0x0300U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP5_SHIFT                                     (0x0008U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP5_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP5_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW1_XCMP6_MASK                                      (0x0C00U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP6_SHIFT                                     (0x000AU)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP6_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP6_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW1_XCMP7_MASK                                      (0x3000U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP7_SHIFT                                     (0x000CU)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP7_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP7_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW1_XCMP8_MASK                                      (0xC000U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP8_SHIFT                                     (0x000EU)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP8_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW1_XCMP8_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW1_RESETVAL                                        (0x0000U)

/* RESERVED_63 */

#define PWM_EPWM_RESERVED_63_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_63_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_63_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_63_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_63_RESETVAL                                          (0x0000U)

/* CMPC_SHDW1 */

#define PWM_EPWM_CMPC_SHDW1_CMPC_SHDW1_MASK                                    (0xFFFFU)
#define PWM_EPWM_CMPC_SHDW1_CMPC_SHDW1_SHIFT                                   (0x0000U)
#define PWM_EPWM_CMPC_SHDW1_CMPC_SHDW1_RESETVAL                                (0x0000U)
#define PWM_EPWM_CMPC_SHDW1_CMPC_SHDW1_MAX                                     (0xFFFFU)

#define PWM_EPWM_CMPC_SHDW1_RESETVAL                                           (0x0000U)

/* RESERVED_64 */

#define PWM_EPWM_RESERVED_64_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_64_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_64_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_64_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_64_RESETVAL                                          (0x0000U)

/* CMPD_SHDW1 */

#define PWM_EPWM_CMPD_SHDW1_CMPD_SHDW1_MASK                                    (0xFFFFU)
#define PWM_EPWM_CMPD_SHDW1_CMPD_SHDW1_SHIFT                                   (0x0000U)
#define PWM_EPWM_CMPD_SHDW1_CMPD_SHDW1_RESETVAL                                (0x0000U)
#define PWM_EPWM_CMPD_SHDW1_CMPD_SHDW1_MAX                                     (0xFFFFU)

#define PWM_EPWM_CMPD_SHDW1_RESETVAL                                           (0x0000U)

/* RESERVED_65 */

#define PWM_EPWM_RESERVED_65_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_65_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_65_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_65_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_65_RESETVAL                                          (0x00000000U)

/* XMINMAX_SHDW1 */

#define PWM_EPWM_XMINMAX_SHDW1_XMAX_SHDW1_MASK                                 (0x0000FFFFU)
#define PWM_EPWM_XMINMAX_SHDW1_XMAX_SHDW1_SHIFT                                (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW1_XMAX_SHDW1_RESETVAL                             (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW1_XMAX_SHDW1_MAX                                  (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_SHDW1_XMIN_SHDW1_MASK                                 (0xFFFF0000U)
#define PWM_EPWM_XMINMAX_SHDW1_XMIN_SHDW1_SHIFT                                (0x00000010U)
#define PWM_EPWM_XMINMAX_SHDW1_XMIN_SHDW1_RESETVAL                             (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW1_XMIN_SHDW1_MAX                                  (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_SHDW1_RESETVAL                                        (0x00000000U)

/* RESERVED_66 */

#define PWM_EPWM_RESERVED_66_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_66_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_66_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_66_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_66_RESETVAL                                          (0x00000000U)

/* XCMP1_SHDW2 */

#define PWM_EPWM_XCMP1_SHDW2_XCMP1HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP1_SHDW2_XCMP1HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW2_XCMP1HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW2_XCMP1HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP1_SHDW2_XCMP1_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP1_SHDW2_XCMP1_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP1_SHDW2_XCMP1_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW2_XCMP1_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP1_SHDW2_RESETVAL                                          (0x00000000U)

/* XCMP2_SHDW2 */

#define PWM_EPWM_XCMP2_SHDW2_XCMP2HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP2_SHDW2_XCMP2HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW2_XCMP2HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW2_XCMP2HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP2_SHDW2_XCMP2_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP2_SHDW2_XCMP2_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP2_SHDW2_XCMP2_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW2_XCMP2_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP2_SHDW2_RESETVAL                                          (0x00000000U)

/* XCMP3_SHDW2 */

#define PWM_EPWM_XCMP3_SHDW2_XCMP3HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP3_SHDW2_XCMP3HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW2_XCMP3HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW2_XCMP3HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP3_SHDW2_XCMP3_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP3_SHDW2_XCMP3_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP3_SHDW2_XCMP3_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW2_XCMP3_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP3_SHDW2_RESETVAL                                          (0x00000000U)

/* XCMP4_SHDW2 */

#define PWM_EPWM_XCMP4_SHDW2_XCMP4HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP4_SHDW2_XCMP4HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW2_XCMP4HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW2_XCMP4HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP4_SHDW2_XCMP4_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP4_SHDW2_XCMP4_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP4_SHDW2_XCMP4_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW2_XCMP4_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP4_SHDW2_RESETVAL                                          (0x00000000U)

/* XCMP5_SHDW2 */

#define PWM_EPWM_XCMP5_SHDW2_XCMP5HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP5_SHDW2_XCMP5HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW2_XCMP5HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW2_XCMP5HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP5_SHDW2_XCMP5_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP5_SHDW2_XCMP5_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP5_SHDW2_XCMP5_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW2_XCMP5_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP5_SHDW2_RESETVAL                                          (0x00000000U)

/* XCMP6_SHDW2 */

#define PWM_EPWM_XCMP6_SHDW2_XCMP6HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP6_SHDW2_XCMP6HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW2_XCMP6HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW2_XCMP6HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP6_SHDW2_XCMP6_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP6_SHDW2_XCMP6_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP6_SHDW2_XCMP6_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW2_XCMP6_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP6_SHDW2_RESETVAL                                          (0x00000000U)

/* XCMP7_SHDW2 */

#define PWM_EPWM_XCMP7_SHDW2_XCMP7HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP7_SHDW2_XCMP7HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW2_XCMP7HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW2_XCMP7HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP7_SHDW2_XCMP7_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP7_SHDW2_XCMP7_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP7_SHDW2_XCMP7_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW2_XCMP7_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP7_SHDW2_RESETVAL                                          (0x00000000U)

/* XCMP8_SHDW2 */

#define PWM_EPWM_XCMP8_SHDW2_XCMP8HR_SHDW2_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP8_SHDW2_XCMP8HR_SHDW2_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW2_XCMP8HR_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW2_XCMP8HR_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP8_SHDW2_XCMP8_SHDW2_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP8_SHDW2_XCMP8_SHDW2_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP8_SHDW2_XCMP8_SHDW2_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW2_XCMP8_SHDW2_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP8_SHDW2_RESETVAL                                          (0x00000000U)

/* XTBPRD_SHDW2 */

#define PWM_EPWM_XTBPRD_SHDW2_XTBPRDHR_SHDW2_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XTBPRD_SHDW2_XTBPRDHR_SHDW2_SHIFT                             (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW2_XTBPRDHR_SHDW2_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW2_XTBPRDHR_SHDW2_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_SHDW2_XTBPRD_SHDW2_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XTBPRD_SHDW2_XTBPRD_SHDW2_SHIFT                               (0x00000010U)
#define PWM_EPWM_XTBPRD_SHDW2_XTBPRD_SHDW2_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW2_XTBPRD_SHDW2_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_SHDW2_RESETVAL                                         (0x00000000U)

/* RESERVED_67 */

#define PWM_EPWM_RESERVED_67_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_67_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_67_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_67_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_67_RESETVAL                                          (0x00000000U)

/* XAQCTLA_SHDW2 */

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP1_MASK                                      (0x0003U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP1_SHIFT                                     (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP1_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP2_MASK                                      (0x000CU)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP2_SHIFT                                     (0x0002U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP2_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP2_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP3_MASK                                      (0x0030U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP3_SHIFT                                     (0x0004U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP3_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP3_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP4_MASK                                      (0x00C0U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP4_SHIFT                                     (0x0006U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP4_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP4_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP5_MASK                                      (0x0300U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP5_SHIFT                                     (0x0008U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP5_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP5_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP6_MASK                                      (0x0C00U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP6_SHIFT                                     (0x000AU)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP6_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP6_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP7_MASK                                      (0x3000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP7_SHIFT                                     (0x000CU)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP7_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP7_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_XCMP8_MASK                                      (0xC000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP8_SHIFT                                     (0x000EU)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP8_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW2_XCMP8_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW2_RESETVAL                                        (0x0000U)

/* XAQCTLB_SHDW2 */

#define PWM_EPWM_XAQCTLB_SHDW2_RESERVED_1_MASK                                 (0x00FFU)
#define PWM_EPWM_XAQCTLB_SHDW2_RESERVED_1_SHIFT                                (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW2_RESERVED_1_RESETVAL                             (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW2_RESERVED_1_MAX                                  (0x00FFU)

#define PWM_EPWM_XAQCTLB_SHDW2_XCMP5_MASK                                      (0x0300U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP5_SHIFT                                     (0x0008U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP5_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP5_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW2_XCMP6_MASK                                      (0x0C00U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP6_SHIFT                                     (0x000AU)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP6_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP6_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW2_XCMP7_MASK                                      (0x3000U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP7_SHIFT                                     (0x000CU)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP7_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP7_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW2_XCMP8_MASK                                      (0xC000U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP8_SHIFT                                     (0x000EU)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP8_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW2_XCMP8_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW2_RESETVAL                                        (0x0000U)

/* RESERVED_68 */

#define PWM_EPWM_RESERVED_68_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_68_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_68_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_68_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_68_RESETVAL                                          (0x0000U)

/* CMPC_SHDW2 */

#define PWM_EPWM_CMPC_SHDW2_CMPC_SHDW2_MASK                                    (0xFFFFU)
#define PWM_EPWM_CMPC_SHDW2_CMPC_SHDW2_SHIFT                                   (0x0000U)
#define PWM_EPWM_CMPC_SHDW2_CMPC_SHDW2_RESETVAL                                (0x0000U)
#define PWM_EPWM_CMPC_SHDW2_CMPC_SHDW2_MAX                                     (0xFFFFU)

#define PWM_EPWM_CMPC_SHDW2_RESETVAL                                           (0x0000U)

/* RESERVED_69 */

#define PWM_EPWM_RESERVED_69_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_69_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_69_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_69_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_69_RESETVAL                                          (0x0000U)

/* CMPD_SHDW2 */

#define PWM_EPWM_CMPD_SHDW2_CMPD_SHDW2_MASK                                    (0xFFFFU)
#define PWM_EPWM_CMPD_SHDW2_CMPD_SHDW2_SHIFT                                   (0x0000U)
#define PWM_EPWM_CMPD_SHDW2_CMPD_SHDW2_RESETVAL                                (0x0000U)
#define PWM_EPWM_CMPD_SHDW2_CMPD_SHDW2_MAX                                     (0xFFFFU)

#define PWM_EPWM_CMPD_SHDW2_RESETVAL                                           (0x0000U)

/* RESERVED_70 */

#define PWM_EPWM_RESERVED_70_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_70_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_70_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_70_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_70_RESETVAL                                          (0x00000000U)

/* XMINMAX_SHDW2 */

#define PWM_EPWM_XMINMAX_SHDW2_XMAX_SHDW2_MASK                                 (0x0000FFFFU)
#define PWM_EPWM_XMINMAX_SHDW2_XMAX_SHDW2_SHIFT                                (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW2_XMAX_SHDW2_RESETVAL                             (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW2_XMAX_SHDW2_MAX                                  (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_SHDW2_XMIN_SHDW2_MASK                                 (0xFFFF0000U)
#define PWM_EPWM_XMINMAX_SHDW2_XMIN_SHDW2_SHIFT                                (0x00000010U)
#define PWM_EPWM_XMINMAX_SHDW2_XMIN_SHDW2_RESETVAL                             (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW2_XMIN_SHDW2_MAX                                  (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_SHDW2_RESETVAL                                        (0x00000000U)

/* RESERVED_71 */

#define PWM_EPWM_RESERVED_71_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_71_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_71_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_71_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_71_RESETVAL                                          (0x00000000U)

/* XCMP1_SHDW3 */

#define PWM_EPWM_XCMP1_SHDW3_XCMP1HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP1_SHDW3_XCMP1HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW3_XCMP1HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW3_XCMP1HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP1_SHDW3_XCMP1_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP1_SHDW3_XCMP1_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP1_SHDW3_XCMP1_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP1_SHDW3_XCMP1_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP1_SHDW3_RESETVAL                                          (0x00000000U)

/* XCMP2_SHDW3 */

#define PWM_EPWM_XCMP2_SHDW3_XCMP2HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP2_SHDW3_XCMP2HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW3_XCMP2HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW3_XCMP2HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP2_SHDW3_XCMP2_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP2_SHDW3_XCMP2_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP2_SHDW3_XCMP2_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP2_SHDW3_XCMP2_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP2_SHDW3_RESETVAL                                          (0x00000000U)

/* XCMP3_SHDW3 */

#define PWM_EPWM_XCMP3_SHDW3_XCMP3HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP3_SHDW3_XCMP3HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW3_XCMP3HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW3_XCMP3HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP3_SHDW3_XCMP3_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP3_SHDW3_XCMP3_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP3_SHDW3_XCMP3_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP3_SHDW3_XCMP3_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP3_SHDW3_RESETVAL                                          (0x00000000U)

/* XCMP4_SHDW3 */

#define PWM_EPWM_XCMP4_SHDW3_XCMP4HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP4_SHDW3_XCMP4HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW3_XCMP4HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW3_XCMP4HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP4_SHDW3_XCMP4_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP4_SHDW3_XCMP4_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP4_SHDW3_XCMP4_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP4_SHDW3_XCMP4_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP4_SHDW3_RESETVAL                                          (0x00000000U)

/* XCMP5_SHDW3 */

#define PWM_EPWM_XCMP5_SHDW3_XCMP5HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP5_SHDW3_XCMP5HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW3_XCMP5HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW3_XCMP5HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP5_SHDW3_XCMP5_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP5_SHDW3_XCMP5_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP5_SHDW3_XCMP5_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP5_SHDW3_XCMP5_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP5_SHDW3_RESETVAL                                          (0x00000000U)

/* XCMP6_SHDW3 */

#define PWM_EPWM_XCMP6_SHDW3_XCMP6HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP6_SHDW3_XCMP6HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW3_XCMP6HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW3_XCMP6HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP6_SHDW3_XCMP6_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP6_SHDW3_XCMP6_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP6_SHDW3_XCMP6_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP6_SHDW3_XCMP6_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP6_SHDW3_RESETVAL                                          (0x00000000U)

/* XCMP7_SHDW3 */

#define PWM_EPWM_XCMP7_SHDW3_XCMP7HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP7_SHDW3_XCMP7HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW3_XCMP7HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW3_XCMP7HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP7_SHDW3_XCMP7_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP7_SHDW3_XCMP7_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP7_SHDW3_XCMP7_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP7_SHDW3_XCMP7_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP7_SHDW3_RESETVAL                                          (0x00000000U)

/* XCMP8_SHDW3 */

#define PWM_EPWM_XCMP8_SHDW3_XCMP8HR_SHDW3_MASK                                (0x0000FFFFU)
#define PWM_EPWM_XCMP8_SHDW3_XCMP8HR_SHDW3_SHIFT                               (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW3_XCMP8HR_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW3_XCMP8HR_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XCMP8_SHDW3_XCMP8_SHDW3_MASK                                  (0xFFFF0000U)
#define PWM_EPWM_XCMP8_SHDW3_XCMP8_SHDW3_SHIFT                                 (0x00000010U)
#define PWM_EPWM_XCMP8_SHDW3_XCMP8_SHDW3_RESETVAL                              (0x00000000U)
#define PWM_EPWM_XCMP8_SHDW3_XCMP8_SHDW3_MAX                                   (0x0000FFFFU)

#define PWM_EPWM_XCMP8_SHDW3_RESETVAL                                          (0x00000000U)

/* XTBPRD_SHDW3 */

#define PWM_EPWM_XTBPRD_SHDW3_XTBPRDHR_SHDW3_MASK                              (0x0000FFFFU)
#define PWM_EPWM_XTBPRD_SHDW3_XTBPRDHR_SHDW3_SHIFT                             (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW3_XTBPRDHR_SHDW3_RESETVAL                          (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW3_XTBPRDHR_SHDW3_MAX                               (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_SHDW3_XTBPRD_SHDW3_MASK                                (0xFFFF0000U)
#define PWM_EPWM_XTBPRD_SHDW3_XTBPRD_SHDW3_SHIFT                               (0x00000010U)
#define PWM_EPWM_XTBPRD_SHDW3_XTBPRD_SHDW3_RESETVAL                            (0x00000000U)
#define PWM_EPWM_XTBPRD_SHDW3_XTBPRD_SHDW3_MAX                                 (0x0000FFFFU)

#define PWM_EPWM_XTBPRD_SHDW3_RESETVAL                                         (0x00000000U)

/* RESERVED_72 */

#define PWM_EPWM_RESERVED_72_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_72_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_72_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_72_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_72_RESETVAL                                          (0x00000000U)

/* XAQCTLA_SHDW3 */

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP1_MASK                                      (0x0003U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP1_SHIFT                                     (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP1_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP1_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP2_MASK                                      (0x000CU)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP2_SHIFT                                     (0x0002U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP2_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP2_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP3_MASK                                      (0x0030U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP3_SHIFT                                     (0x0004U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP3_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP3_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP4_MASK                                      (0x00C0U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP4_SHIFT                                     (0x0006U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP4_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP4_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP5_MASK                                      (0x0300U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP5_SHIFT                                     (0x0008U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP5_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP5_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP6_MASK                                      (0x0C00U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP6_SHIFT                                     (0x000AU)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP6_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP6_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP7_MASK                                      (0x3000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP7_SHIFT                                     (0x000CU)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP7_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP7_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_XCMP8_MASK                                      (0xC000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP8_SHIFT                                     (0x000EU)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP8_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLA_SHDW3_XCMP8_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLA_SHDW3_RESETVAL                                        (0x0000U)

/* XAQCTLB_SHDW3 */

#define PWM_EPWM_XAQCTLB_SHDW3_RESERVED_1_MASK                                 (0x00FFU)
#define PWM_EPWM_XAQCTLB_SHDW3_RESERVED_1_SHIFT                                (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW3_RESERVED_1_RESETVAL                             (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW3_RESERVED_1_MAX                                  (0x00FFU)

#define PWM_EPWM_XAQCTLB_SHDW3_XCMP5_MASK                                      (0x0300U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP5_SHIFT                                     (0x0008U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP5_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP5_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW3_XCMP6_MASK                                      (0x0C00U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP6_SHIFT                                     (0x000AU)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP6_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP6_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW3_XCMP7_MASK                                      (0x3000U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP7_SHIFT                                     (0x000CU)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP7_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP7_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW3_XCMP8_MASK                                      (0xC000U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP8_SHIFT                                     (0x000EU)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP8_RESETVAL                                  (0x0000U)
#define PWM_EPWM_XAQCTLB_SHDW3_XCMP8_MAX                                       (0x0003U)

#define PWM_EPWM_XAQCTLB_SHDW3_RESETVAL                                        (0x0000U)

/* RESERVED_73 */

#define PWM_EPWM_RESERVED_73_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_73_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_73_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_73_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_73_RESETVAL                                          (0x0000U)

/* CMPC_SHDW3 */

#define PWM_EPWM_CMPC_SHDW3_CMPC_SHDW3_MASK                                    (0xFFFFU)
#define PWM_EPWM_CMPC_SHDW3_CMPC_SHDW3_SHIFT                                   (0x0000U)
#define PWM_EPWM_CMPC_SHDW3_CMPC_SHDW3_RESETVAL                                (0x0000U)
#define PWM_EPWM_CMPC_SHDW3_CMPC_SHDW3_MAX                                     (0xFFFFU)

#define PWM_EPWM_CMPC_SHDW3_RESETVAL                                           (0x0000U)

/* RESERVED_74 */

#define PWM_EPWM_RESERVED_74_UNNAMED_MASK                                      (0x0001U)
#define PWM_EPWM_RESERVED_74_UNNAMED_SHIFT                                     (0x0000U)
#define PWM_EPWM_RESERVED_74_UNNAMED_RESETVAL                                  (0x0000U)
#define PWM_EPWM_RESERVED_74_UNNAMED_MAX                                       (0x0001U)

#define PWM_EPWM_RESERVED_74_RESETVAL                                          (0x0000U)

/* CMPD_SHDW3 */

#define PWM_EPWM_CMPD_SHDW3_CMPD_SHDW3_MASK                                    (0xFFFFU)
#define PWM_EPWM_CMPD_SHDW3_CMPD_SHDW3_SHIFT                                   (0x0000U)
#define PWM_EPWM_CMPD_SHDW3_CMPD_SHDW3_RESETVAL                                (0x0000U)
#define PWM_EPWM_CMPD_SHDW3_CMPD_SHDW3_MAX                                     (0xFFFFU)

#define PWM_EPWM_CMPD_SHDW3_RESETVAL                                           (0x0000U)

/* RESERVED_75 */

#define PWM_EPWM_RESERVED_75_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_75_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_75_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_75_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_75_RESETVAL                                          (0x00000000U)

/* XMINMAX_SHDW3 */

#define PWM_EPWM_XMINMAX_SHDW3_XMAX_SHDW3_MASK                                 (0x0000FFFFU)
#define PWM_EPWM_XMINMAX_SHDW3_XMAX_SHDW3_SHIFT                                (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW3_XMAX_SHDW3_RESETVAL                             (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW3_XMAX_SHDW3_MAX                                  (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_SHDW3_XMIN_SHDW3_MASK                                 (0xFFFF0000U)
#define PWM_EPWM_XMINMAX_SHDW3_XMIN_SHDW3_SHIFT                                (0x00000010U)
#define PWM_EPWM_XMINMAX_SHDW3_XMIN_SHDW3_RESETVAL                             (0x00000000U)
#define PWM_EPWM_XMINMAX_SHDW3_XMIN_SHDW3_MAX                                  (0x0000FFFFU)

#define PWM_EPWM_XMINMAX_SHDW3_RESETVAL                                        (0x00000000U)

/* RESERVED_76 */

#define PWM_EPWM_RESERVED_76_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_76_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_76_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_76_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_76_RESETVAL                                          (0x00000000U)

/* DECTL */

#define PWM_EPWM_DECTL_ENABLE_MASK                                             (0x00000001U)
#define PWM_EPWM_DECTL_ENABLE_SHIFT                                            (0x00000000U)
#define PWM_EPWM_DECTL_ENABLE_RESETVAL                                         (0x00000000U)
#define PWM_EPWM_DECTL_ENABLE_MAX                                              (0x00000001U)

#define PWM_EPWM_DECTL_MODE_MASK                                               (0x00000002U)
#define PWM_EPWM_DECTL_MODE_SHIFT                                              (0x00000001U)
#define PWM_EPWM_DECTL_MODE_RESETVAL                                           (0x00000000U)
#define PWM_EPWM_DECTL_MODE_MAX                                                (0x00000001U)

#define PWM_EPWM_DECTL_RESERVED_1_MASK                                         (0x000000FCU)
#define PWM_EPWM_DECTL_RESERVED_1_SHIFT                                        (0x00000002U)
#define PWM_EPWM_DECTL_RESERVED_1_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_DECTL_RESERVED_1_MAX                                          (0x0000003FU)

#define PWM_EPWM_DECTL_REENTRYDLY_MASK                                         (0x0000FF00U)
#define PWM_EPWM_DECTL_REENTRYDLY_SHIFT                                        (0x00000008U)
#define PWM_EPWM_DECTL_REENTRYDLY_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_DECTL_REENTRYDLY_MAX                                          (0x000000FFU)

#define PWM_EPWM_DECTL_RESERVED_2_MASK                                         (0xFFFF0000U)
#define PWM_EPWM_DECTL_RESERVED_2_SHIFT                                        (0x00000010U)
#define PWM_EPWM_DECTL_RESERVED_2_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_DECTL_RESERVED_2_MAX                                          (0x0000FFFFU)

#define PWM_EPWM_DECTL_RESETVAL                                                (0x00000000U)

/* DECOMPSEL */

#define PWM_EPWM_DECOMPSEL_TRIPL_MASK                                          (0x0000003FU)
#define PWM_EPWM_DECOMPSEL_TRIPL_SHIFT                                         (0x00000000U)
#define PWM_EPWM_DECOMPSEL_TRIPL_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_DECOMPSEL_TRIPL_MAX                                           (0x0000003FU)

#define PWM_EPWM_DECOMPSEL_RESERVED_1_MASK                                     (0x0000FFC0U)
#define PWM_EPWM_DECOMPSEL_RESERVED_1_SHIFT                                    (0x00000006U)
#define PWM_EPWM_DECOMPSEL_RESERVED_1_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_DECOMPSEL_RESERVED_1_MAX                                      (0x000003FFU)

#define PWM_EPWM_DECOMPSEL_TRIPH_MASK                                          (0x003F0000U)
#define PWM_EPWM_DECOMPSEL_TRIPH_SHIFT                                         (0x00000010U)
#define PWM_EPWM_DECOMPSEL_TRIPH_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_DECOMPSEL_TRIPH_MAX                                           (0x0000003FU)

#define PWM_EPWM_DECOMPSEL_RESERVED_2_MASK                                     (0xFFC00000U)
#define PWM_EPWM_DECOMPSEL_RESERVED_2_SHIFT                                    (0x00000016U)
#define PWM_EPWM_DECOMPSEL_RESERVED_2_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_DECOMPSEL_RESERVED_2_MAX                                      (0x000003FFU)

#define PWM_EPWM_DECOMPSEL_RESETVAL                                            (0x00000000U)

/* DEACTCTL */

#define PWM_EPWM_DEACTCTL_PWMA_MASK                                            (0x00000003U)
#define PWM_EPWM_DEACTCTL_PWMA_SHIFT                                           (0x00000000U)
#define PWM_EPWM_DEACTCTL_PWMA_RESETVAL                                        (0x00000000U)
#define PWM_EPWM_DEACTCTL_PWMA_MAX                                             (0x00000003U)

#define PWM_EPWM_DEACTCTL_TRIPSELA_MASK                                        (0x00000004U)
#define PWM_EPWM_DEACTCTL_TRIPSELA_SHIFT                                       (0x00000002U)
#define PWM_EPWM_DEACTCTL_TRIPSELA_RESETVAL                                    (0x00000000U)
#define PWM_EPWM_DEACTCTL_TRIPSELA_MAX                                         (0x00000001U)

#define PWM_EPWM_DEACTCTL_RESERVED_1_MASK                                      (0x00000008U)
#define PWM_EPWM_DEACTCTL_RESERVED_1_SHIFT                                     (0x00000003U)
#define PWM_EPWM_DEACTCTL_RESERVED_1_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_DEACTCTL_RESERVED_1_MAX                                       (0x00000001U)

#define PWM_EPWM_DEACTCTL_PWMB_MASK                                            (0x00000030U)
#define PWM_EPWM_DEACTCTL_PWMB_SHIFT                                           (0x00000004U)
#define PWM_EPWM_DEACTCTL_PWMB_RESETVAL                                        (0x00000000U)
#define PWM_EPWM_DEACTCTL_PWMB_MAX                                             (0x00000003U)

#define PWM_EPWM_DEACTCTL_TRIPSELB_MASK                                        (0x00000040U)
#define PWM_EPWM_DEACTCTL_TRIPSELB_SHIFT                                       (0x00000006U)
#define PWM_EPWM_DEACTCTL_TRIPSELB_RESETVAL                                    (0x00000000U)
#define PWM_EPWM_DEACTCTL_TRIPSELB_MAX                                         (0x00000001U)

#define PWM_EPWM_DEACTCTL_RESERVED_2_MASK                                      (0x0000FF80U)
#define PWM_EPWM_DEACTCTL_RESERVED_2_SHIFT                                     (0x00000007U)
#define PWM_EPWM_DEACTCTL_RESERVED_2_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_DEACTCTL_RESERVED_2_MAX                                       (0x000001FFU)

#define PWM_EPWM_DEACTCTL_TRIPENABLE_MASK                                      (0x00010000U)
#define PWM_EPWM_DEACTCTL_TRIPENABLE_SHIFT                                     (0x00000010U)
#define PWM_EPWM_DEACTCTL_TRIPENABLE_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_DEACTCTL_TRIPENABLE_MAX                                       (0x00000001U)

#define PWM_EPWM_DEACTCTL_RESERVED_3_MASK                                      (0xFFFE0000U)
#define PWM_EPWM_DEACTCTL_RESERVED_3_SHIFT                                     (0x00000011U)
#define PWM_EPWM_DEACTCTL_RESERVED_3_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_DEACTCTL_RESERVED_3_MAX                                       (0x00007FFFU)

#define PWM_EPWM_DEACTCTL_RESETVAL                                             (0x00000000U)

/* DESTS */

#define PWM_EPWM_DESTS_DEACTIVE_MASK                                           (0x00000001U)
#define PWM_EPWM_DESTS_DEACTIVE_SHIFT                                          (0x00000000U)
#define PWM_EPWM_DESTS_DEACTIVE_RESETVAL                                       (0x00000000U)
#define PWM_EPWM_DESTS_DEACTIVE_MAX                                            (0x00000001U)

#define PWM_EPWM_DESTS_RESERVED_1_MASK                                         (0xFFFFFFFEU)
#define PWM_EPWM_DESTS_RESERVED_1_SHIFT                                        (0x00000001U)
#define PWM_EPWM_DESTS_RESERVED_1_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_DESTS_RESERVED_1_MAX                                          (0x7FFFFFFFU)

#define PWM_EPWM_DESTS_RESETVAL                                                (0x00000000U)

/* DEFRC */

#define PWM_EPWM_DEFRC_DEACTIVE_MASK                                           (0x00000001U)
#define PWM_EPWM_DEFRC_DEACTIVE_SHIFT                                          (0x00000000U)
#define PWM_EPWM_DEFRC_DEACTIVE_RESETVAL                                       (0x00000000U)
#define PWM_EPWM_DEFRC_DEACTIVE_MAX                                            (0x00000001U)

#define PWM_EPWM_DEFRC_RESERVED_1_MASK                                         (0xFFFFFFFEU)
#define PWM_EPWM_DEFRC_RESERVED_1_SHIFT                                        (0x00000001U)
#define PWM_EPWM_DEFRC_RESERVED_1_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_DEFRC_RESERVED_1_MAX                                          (0x7FFFFFFFU)

#define PWM_EPWM_DEFRC_RESETVAL                                                (0x00000000U)

/* DECLR */

#define PWM_EPWM_DECLR_DEACTIVE_MASK                                           (0x00000001U)
#define PWM_EPWM_DECLR_DEACTIVE_SHIFT                                          (0x00000000U)
#define PWM_EPWM_DECLR_DEACTIVE_RESETVAL                                       (0x00000000U)
#define PWM_EPWM_DECLR_DEACTIVE_MAX                                            (0x00000001U)

#define PWM_EPWM_DECLR_RESERVED_1_MASK                                         (0xFFFFFFFEU)
#define PWM_EPWM_DECLR_RESERVED_1_SHIFT                                        (0x00000001U)
#define PWM_EPWM_DECLR_RESERVED_1_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_DECLR_RESERVED_1_MAX                                          (0x7FFFFFFFU)

#define PWM_EPWM_DECLR_RESETVAL                                                (0x00000000U)

/* RESERVED_77 */

#define PWM_EPWM_RESERVED_77_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_77_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_77_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_77_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_77_RESETVAL                                          (0x00000000U)

/* DEMONCNT */

#define PWM_EPWM_DEMONCNT_CNT_MASK                                             (0x0000FFFFU)
#define PWM_EPWM_DEMONCNT_CNT_SHIFT                                            (0x00000000U)
#define PWM_EPWM_DEMONCNT_CNT_RESETVAL                                         (0x00000000U)
#define PWM_EPWM_DEMONCNT_CNT_MAX                                              (0x0000FFFFU)

#define PWM_EPWM_DEMONCNT_RESERVED_1_MASK                                      (0xFFFF0000U)
#define PWM_EPWM_DEMONCNT_RESERVED_1_SHIFT                                     (0x00000010U)
#define PWM_EPWM_DEMONCNT_RESERVED_1_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_DEMONCNT_RESERVED_1_MAX                                       (0x0000FFFFU)

#define PWM_EPWM_DEMONCNT_RESETVAL                                             (0x00000000U)

/* DEMONCTL */

#define PWM_EPWM_DEMONCTL_ENABLE_MASK                                          (0x00000001U)
#define PWM_EPWM_DEMONCTL_ENABLE_SHIFT                                         (0x00000000U)
#define PWM_EPWM_DEMONCTL_ENABLE_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_DEMONCTL_ENABLE_MAX                                           (0x00000001U)

#define PWM_EPWM_DEMONCTL_RESERVED_1_MASK                                      (0xFFFFFFFEU)
#define PWM_EPWM_DEMONCTL_RESERVED_1_SHIFT                                     (0x00000001U)
#define PWM_EPWM_DEMONCTL_RESERVED_1_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_DEMONCTL_RESERVED_1_MAX                                       (0x7FFFFFFFU)

#define PWM_EPWM_DEMONCTL_RESETVAL                                             (0x00000000U)

/* DEMONSTEP */

#define PWM_EPWM_DEMONSTEP_INCSTEP_MASK                                        (0x000000FFU)
#define PWM_EPWM_DEMONSTEP_INCSTEP_SHIFT                                       (0x00000000U)
#define PWM_EPWM_DEMONSTEP_INCSTEP_RESETVAL                                    (0x00000000U)
#define PWM_EPWM_DEMONSTEP_INCSTEP_MAX                                         (0x000000FFU)

#define PWM_EPWM_DEMONSTEP_RESERVED_1_MASK                                     (0x0000FF00U)
#define PWM_EPWM_DEMONSTEP_RESERVED_1_SHIFT                                    (0x00000008U)
#define PWM_EPWM_DEMONSTEP_RESERVED_1_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_DEMONSTEP_RESERVED_1_MAX                                      (0x000000FFU)

#define PWM_EPWM_DEMONSTEP_DECSTEP_MASK                                        (0x00FF0000U)
#define PWM_EPWM_DEMONSTEP_DECSTEP_SHIFT                                       (0x00000010U)
#define PWM_EPWM_DEMONSTEP_DECSTEP_RESETVAL                                    (0x00000000U)
#define PWM_EPWM_DEMONSTEP_DECSTEP_MAX                                         (0x000000FFU)

#define PWM_EPWM_DEMONSTEP_RESERVED_2_MASK                                     (0xFF000000U)
#define PWM_EPWM_DEMONSTEP_RESERVED_2_SHIFT                                    (0x00000018U)
#define PWM_EPWM_DEMONSTEP_RESERVED_2_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_DEMONSTEP_RESERVED_2_MAX                                      (0x000000FFU)

#define PWM_EPWM_DEMONSTEP_RESETVAL                                            (0x00000000U)

/* DEMONTHRES */

#define PWM_EPWM_DEMONTHRES_THRESHOLD_MASK                                     (0x0000FFFFU)
#define PWM_EPWM_DEMONTHRES_THRESHOLD_SHIFT                                    (0x00000000U)
#define PWM_EPWM_DEMONTHRES_THRESHOLD_RESETVAL                                 (0x00000000U)
#define PWM_EPWM_DEMONTHRES_THRESHOLD_MAX                                      (0x0000FFFFU)

#define PWM_EPWM_DEMONTHRES_RESERVED_1_MASK                                    (0xFFFF0000U)
#define PWM_EPWM_DEMONTHRES_RESERVED_1_SHIFT                                   (0x00000010U)
#define PWM_EPWM_DEMONTHRES_RESERVED_1_RESETVAL                                (0x00000000U)
#define PWM_EPWM_DEMONTHRES_RESERVED_1_MAX                                     (0x0000FFFFU)

#define PWM_EPWM_DEMONTHRES_RESETVAL                                           (0x00000000U)

/* RESERVED_78 */

#define PWM_EPWM_RESERVED_78_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_78_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_78_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_78_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_78_RESETVAL                                          (0x00000000U)

/* MINDBCFG */

#define PWM_EPWM_MINDBCFG_ENABLEA_MASK                                         (0x00000001U)
#define PWM_EPWM_MINDBCFG_ENABLEA_SHIFT                                        (0x00000000U)
#define PWM_EPWM_MINDBCFG_ENABLEA_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_MINDBCFG_ENABLEA_MAX                                          (0x00000001U)

#define PWM_EPWM_MINDBCFG_RESERVED_1_MASK                                      (0x00000002U)
#define PWM_EPWM_MINDBCFG_RESERVED_1_SHIFT                                     (0x00000001U)
#define PWM_EPWM_MINDBCFG_RESERVED_1_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_MINDBCFG_RESERVED_1_MAX                                       (0x00000001U)

#define PWM_EPWM_MINDBCFG_INVERTA_MASK                                         (0x00000004U)
#define PWM_EPWM_MINDBCFG_INVERTA_SHIFT                                        (0x00000002U)
#define PWM_EPWM_MINDBCFG_INVERTA_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_MINDBCFG_INVERTA_MAX                                          (0x00000001U)

#define PWM_EPWM_MINDBCFG_SELBLOCKA_MASK                                       (0x00000008U)
#define PWM_EPWM_MINDBCFG_SELBLOCKA_SHIFT                                      (0x00000003U)
#define PWM_EPWM_MINDBCFG_SELBLOCKA_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_MINDBCFG_SELBLOCKA_MAX                                        (0x00000001U)

#define PWM_EPWM_MINDBCFG_SELA_MASK                                            (0x000000F0U)
#define PWM_EPWM_MINDBCFG_SELA_SHIFT                                           (0x00000004U)
#define PWM_EPWM_MINDBCFG_SELA_RESETVAL                                        (0x00000000U)
#define PWM_EPWM_MINDBCFG_SELA_MAX                                             (0x0000000FU)

#define PWM_EPWM_MINDBCFG_POLSELA_MASK                                         (0x00000100U)
#define PWM_EPWM_MINDBCFG_POLSELA_SHIFT                                        (0x00000008U)
#define PWM_EPWM_MINDBCFG_POLSELA_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_MINDBCFG_POLSELA_MAX                                          (0x00000001U)

#define PWM_EPWM_MINDBCFG_RESERVED_2_MASK                                      (0x0000FE00U)
#define PWM_EPWM_MINDBCFG_RESERVED_2_SHIFT                                     (0x00000009U)
#define PWM_EPWM_MINDBCFG_RESERVED_2_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_MINDBCFG_RESERVED_2_MAX                                       (0x0000007FU)

#define PWM_EPWM_MINDBCFG_ENABLEB_MASK                                         (0x00010000U)
#define PWM_EPWM_MINDBCFG_ENABLEB_SHIFT                                        (0x00000010U)
#define PWM_EPWM_MINDBCFG_ENABLEB_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_MINDBCFG_ENABLEB_MAX                                          (0x00000001U)

#define PWM_EPWM_MINDBCFG_RESERVED_3_MASK                                      (0x00020000U)
#define PWM_EPWM_MINDBCFG_RESERVED_3_SHIFT                                     (0x00000011U)
#define PWM_EPWM_MINDBCFG_RESERVED_3_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_MINDBCFG_RESERVED_3_MAX                                       (0x00000001U)

#define PWM_EPWM_MINDBCFG_INVERTB_MASK                                         (0x00040000U)
#define PWM_EPWM_MINDBCFG_INVERTB_SHIFT                                        (0x00000012U)
#define PWM_EPWM_MINDBCFG_INVERTB_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_MINDBCFG_INVERTB_MAX                                          (0x00000001U)

#define PWM_EPWM_MINDBCFG_SELBLOCKB_MASK                                       (0x00080000U)
#define PWM_EPWM_MINDBCFG_SELBLOCKB_SHIFT                                      (0x00000013U)
#define PWM_EPWM_MINDBCFG_SELBLOCKB_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_MINDBCFG_SELBLOCKB_MAX                                        (0x00000001U)

#define PWM_EPWM_MINDBCFG_SELB_MASK                                            (0x00F00000U)
#define PWM_EPWM_MINDBCFG_SELB_SHIFT                                           (0x00000014U)
#define PWM_EPWM_MINDBCFG_SELB_RESETVAL                                        (0x00000000U)
#define PWM_EPWM_MINDBCFG_SELB_MAX                                             (0x0000000FU)

#define PWM_EPWM_MINDBCFG_POLSELB_MASK                                         (0x01000000U)
#define PWM_EPWM_MINDBCFG_POLSELB_SHIFT                                        (0x00000018U)
#define PWM_EPWM_MINDBCFG_POLSELB_RESETVAL                                     (0x00000000U)
#define PWM_EPWM_MINDBCFG_POLSELB_MAX                                          (0x00000001U)

#define PWM_EPWM_MINDBCFG_RESERVED_4_MASK                                      (0xFE000000U)
#define PWM_EPWM_MINDBCFG_RESERVED_4_SHIFT                                     (0x00000019U)
#define PWM_EPWM_MINDBCFG_RESERVED_4_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_MINDBCFG_RESERVED_4_MAX                                       (0x0000007FU)

#define PWM_EPWM_MINDBCFG_RESETVAL                                             (0x00000000U)

/* MINDBDLY */

#define PWM_EPWM_MINDBDLY_DELAYA_MASK                                          (0x0000FFFFU)
#define PWM_EPWM_MINDBDLY_DELAYA_SHIFT                                         (0x00000000U)
#define PWM_EPWM_MINDBDLY_DELAYA_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_MINDBDLY_DELAYA_MAX                                           (0x0000FFFFU)

#define PWM_EPWM_MINDBDLY_DELAYB_MASK                                          (0xFFFF0000U)
#define PWM_EPWM_MINDBDLY_DELAYB_SHIFT                                         (0x00000010U)
#define PWM_EPWM_MINDBDLY_DELAYB_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_MINDBDLY_DELAYB_MAX                                           (0x0000FFFFU)

#define PWM_EPWM_MINDBDLY_RESETVAL                                             (0x00000000U)

/* RESERVED_79 */

#define PWM_EPWM_RESERVED_79_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_79_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_79_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_79_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_79_RESETVAL                                          (0x00000000U)

/* LUTCTLA */

#define PWM_EPWM_LUTCTLA_BYPASS_MASK                                           (0x00000001U)
#define PWM_EPWM_LUTCTLA_BYPASS_SHIFT                                          (0x00000000U)
#define PWM_EPWM_LUTCTLA_BYPASS_RESETVAL                                       (0x00000001U)
#define PWM_EPWM_LUTCTLA_BYPASS_MAX                                            (0x00000001U)

#define PWM_EPWM_LUTCTLA_RESERVED_1_MASK                                       (0x0000000EU)
#define PWM_EPWM_LUTCTLA_RESERVED_1_SHIFT                                      (0x00000001U)
#define PWM_EPWM_LUTCTLA_RESERVED_1_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_LUTCTLA_RESERVED_1_MAX                                        (0x00000007U)

#define PWM_EPWM_LUTCTLA_SELXBAR_MASK                                          (0x000000F0U)
#define PWM_EPWM_LUTCTLA_SELXBAR_SHIFT                                         (0x00000004U)
#define PWM_EPWM_LUTCTLA_SELXBAR_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_SELXBAR_MAX                                           (0x0000000FU)

#define PWM_EPWM_LUTCTLA_RESERVED_2_MASK                                       (0x0000FF00U)
#define PWM_EPWM_LUTCTLA_RESERVED_2_SHIFT                                      (0x00000008U)
#define PWM_EPWM_LUTCTLA_RESERVED_2_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_LUTCTLA_RESERVED_2_MAX                                        (0x000000FFU)

#define PWM_EPWM_LUTCTLA_LUTDEC0_MASK                                          (0x00010000U)
#define PWM_EPWM_LUTCTLA_LUTDEC0_SHIFT                                         (0x00000010U)
#define PWM_EPWM_LUTCTLA_LUTDEC0_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC0_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_LUTDEC1_MASK                                          (0x00020000U)
#define PWM_EPWM_LUTCTLA_LUTDEC1_SHIFT                                         (0x00000011U)
#define PWM_EPWM_LUTCTLA_LUTDEC1_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC1_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_LUTDEC2_MASK                                          (0x00040000U)
#define PWM_EPWM_LUTCTLA_LUTDEC2_SHIFT                                         (0x00000012U)
#define PWM_EPWM_LUTCTLA_LUTDEC2_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC2_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_LUTDEC3_MASK                                          (0x00080000U)
#define PWM_EPWM_LUTCTLA_LUTDEC3_SHIFT                                         (0x00000013U)
#define PWM_EPWM_LUTCTLA_LUTDEC3_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC3_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_LUTDEC4_MASK                                          (0x00100000U)
#define PWM_EPWM_LUTCTLA_LUTDEC4_SHIFT                                         (0x00000014U)
#define PWM_EPWM_LUTCTLA_LUTDEC4_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC4_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_LUTDEC5_MASK                                          (0x00200000U)
#define PWM_EPWM_LUTCTLA_LUTDEC5_SHIFT                                         (0x00000015U)
#define PWM_EPWM_LUTCTLA_LUTDEC5_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC5_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_LUTDEC6_MASK                                          (0x00400000U)
#define PWM_EPWM_LUTCTLA_LUTDEC6_SHIFT                                         (0x00000016U)
#define PWM_EPWM_LUTCTLA_LUTDEC6_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC6_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_LUTDEC7_MASK                                          (0x00800000U)
#define PWM_EPWM_LUTCTLA_LUTDEC7_SHIFT                                         (0x00000017U)
#define PWM_EPWM_LUTCTLA_LUTDEC7_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLA_LUTDEC7_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLA_RESERVED_3_MASK                                       (0xFF000000U)
#define PWM_EPWM_LUTCTLA_RESERVED_3_SHIFT                                      (0x00000018U)
#define PWM_EPWM_LUTCTLA_RESERVED_3_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_LUTCTLA_RESERVED_3_MAX                                        (0x000000FFU)

#define PWM_EPWM_LUTCTLA_RESETVAL                                              (0x00000001U)

/* LUTCTLB */

#define PWM_EPWM_LUTCTLB_BYPASS_MASK                                           (0x00000001U)
#define PWM_EPWM_LUTCTLB_BYPASS_SHIFT                                          (0x00000000U)
#define PWM_EPWM_LUTCTLB_BYPASS_RESETVAL                                       (0x00000001U)
#define PWM_EPWM_LUTCTLB_BYPASS_MAX                                            (0x00000001U)

#define PWM_EPWM_LUTCTLB_RESERVED_1_MASK                                       (0x0000000EU)
#define PWM_EPWM_LUTCTLB_RESERVED_1_SHIFT                                      (0x00000001U)
#define PWM_EPWM_LUTCTLB_RESERVED_1_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_LUTCTLB_RESERVED_1_MAX                                        (0x00000007U)

#define PWM_EPWM_LUTCTLB_SELXBAR_MASK                                          (0x000000F0U)
#define PWM_EPWM_LUTCTLB_SELXBAR_SHIFT                                         (0x00000004U)
#define PWM_EPWM_LUTCTLB_SELXBAR_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_SELXBAR_MAX                                           (0x0000000FU)

#define PWM_EPWM_LUTCTLB_RESERVED_2_MASK                                       (0x0000FF00U)
#define PWM_EPWM_LUTCTLB_RESERVED_2_SHIFT                                      (0x00000008U)
#define PWM_EPWM_LUTCTLB_RESERVED_2_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_LUTCTLB_RESERVED_2_MAX                                        (0x000000FFU)

#define PWM_EPWM_LUTCTLB_LUTDEC0_MASK                                          (0x00010000U)
#define PWM_EPWM_LUTCTLB_LUTDEC0_SHIFT                                         (0x00000010U)
#define PWM_EPWM_LUTCTLB_LUTDEC0_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC0_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_LUTDEC1_MASK                                          (0x00020000U)
#define PWM_EPWM_LUTCTLB_LUTDEC1_SHIFT                                         (0x00000011U)
#define PWM_EPWM_LUTCTLB_LUTDEC1_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC1_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_LUTDEC2_MASK                                          (0x00040000U)
#define PWM_EPWM_LUTCTLB_LUTDEC2_SHIFT                                         (0x00000012U)
#define PWM_EPWM_LUTCTLB_LUTDEC2_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC2_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_LUTDEC3_MASK                                          (0x00080000U)
#define PWM_EPWM_LUTCTLB_LUTDEC3_SHIFT                                         (0x00000013U)
#define PWM_EPWM_LUTCTLB_LUTDEC3_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC3_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_LUTDEC4_MASK                                          (0x00100000U)
#define PWM_EPWM_LUTCTLB_LUTDEC4_SHIFT                                         (0x00000014U)
#define PWM_EPWM_LUTCTLB_LUTDEC4_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC4_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_LUTDEC5_MASK                                          (0x00200000U)
#define PWM_EPWM_LUTCTLB_LUTDEC5_SHIFT                                         (0x00000015U)
#define PWM_EPWM_LUTCTLB_LUTDEC5_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC5_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_LUTDEC6_MASK                                          (0x00400000U)
#define PWM_EPWM_LUTCTLB_LUTDEC6_SHIFT                                         (0x00000016U)
#define PWM_EPWM_LUTCTLB_LUTDEC6_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC6_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_LUTDEC7_MASK                                          (0x00800000U)
#define PWM_EPWM_LUTCTLB_LUTDEC7_SHIFT                                         (0x00000017U)
#define PWM_EPWM_LUTCTLB_LUTDEC7_RESETVAL                                      (0x00000000U)
#define PWM_EPWM_LUTCTLB_LUTDEC7_MAX                                           (0x00000001U)

#define PWM_EPWM_LUTCTLB_RESERVED_3_MASK                                       (0xFF000000U)
#define PWM_EPWM_LUTCTLB_RESERVED_3_SHIFT                                      (0x00000018U)
#define PWM_EPWM_LUTCTLB_RESERVED_3_RESETVAL                                   (0x00000000U)
#define PWM_EPWM_LUTCTLB_RESERVED_3_MAX                                        (0x000000FFU)

#define PWM_EPWM_LUTCTLB_RESETVAL                                              (0x00000001U)

/* RESERVED_80 */

#define PWM_EPWM_RESERVED_80_UNNAMED_MASK                                      (0x00000001U)
#define PWM_EPWM_RESERVED_80_UNNAMED_SHIFT                                     (0x00000000U)
#define PWM_EPWM_RESERVED_80_UNNAMED_RESETVAL                                  (0x00000000U)
#define PWM_EPWM_RESERVED_80_UNNAMED_MAX                                       (0x00000001U)

#define PWM_EPWM_RESERVED_80_RESETVAL                                          (0x00000000U)

/**************************************************************************
* Register Macros
**************************************************************************/

#define PWM_OTTOCAL_HRPWR                                                      (0x00000042U)
#define PWM_OTTOCAL_HRCAL                                                      (0x00000044U)
#define PWM_OTTOCAL_HRPRD                                                      (0x00000046U)
#define PWM_OTTOCAL_HRCNT0                                                     (0x00000048U)
#define PWM_OTTOCAL_HRCNT1                                                     (0x0000004AU)
#define PWM_OTTOCAL_HRMSTEP                                                    (0x0000004CU)

/**************************************************************************
* Field Definition Macros
**************************************************************************/


/* HRPWR */

#define PWM_OTTOCAL_HRPWR_CALMODE_MASK                                         (0x0003U)
#define PWM_OTTOCAL_HRPWR_CALMODE_SHIFT                                        (0x0000U)
#define PWM_OTTOCAL_HRPWR_CALMODE_RESETVAL                                     (0x0000U)
#define PWM_OTTOCAL_HRPWR_CALMODE_MAX                                          (0x0003U)

#define PWM_OTTOCAL_HRPWR_CALSTART_MASK                                        (0x0004U)
#define PWM_OTTOCAL_HRPWR_CALSTART_SHIFT                                       (0x0002U)
#define PWM_OTTOCAL_HRPWR_CALSTART_RESETVAL                                    (0x0000U)
#define PWM_OTTOCAL_HRPWR_CALSTART_MAX                                         (0x0001U)

#define PWM_OTTOCAL_HRPWR_CNTSEL_MASK                                          (0x0008U)
#define PWM_OTTOCAL_HRPWR_CNTSEL_SHIFT                                         (0x0003U)
#define PWM_OTTOCAL_HRPWR_CNTSEL_RESETVAL                                      (0x0000U)
#define PWM_OTTOCAL_HRPWR_CNTSEL_MAX                                           (0x0001U)

#define PWM_OTTOCAL_HRPWR_CALSTS_MASK                                          (0x0010U)
#define PWM_OTTOCAL_HRPWR_CALSTS_SHIFT                                         (0x0004U)
#define PWM_OTTOCAL_HRPWR_CALSTS_RESETVAL                                      (0x0000U)
#define PWM_OTTOCAL_HRPWR_CALSTS_MAX                                           (0x0001U)

#define PWM_OTTOCAL_HRPWR_TESTSEL_MASK                                         (0x0020U)
#define PWM_OTTOCAL_HRPWR_TESTSEL_SHIFT                                        (0x0005U)
#define PWM_OTTOCAL_HRPWR_TESTSEL_RESETVAL                                     (0x0000U)
#define PWM_OTTOCAL_HRPWR_TESTSEL_MAX                                          (0x0001U)

#define PWM_OTTOCAL_HRPWR_CALSEL_MASK                                          (0x03C0U)
#define PWM_OTTOCAL_HRPWR_CALSEL_SHIFT                                         (0x0006U)
#define PWM_OTTOCAL_HRPWR_CALSEL_RESETVAL                                      (0x0000U)
#define PWM_OTTOCAL_HRPWR_CALSEL_MAX                                           (0x000FU)

#define PWM_OTTOCAL_HRPWR_RESERVED_1_MASK                                      (0x7C00U)
#define PWM_OTTOCAL_HRPWR_RESERVED_1_SHIFT                                     (0x000AU)
#define PWM_OTTOCAL_HRPWR_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_OTTOCAL_HRPWR_RESERVED_1_MAX                                       (0x001FU)

#define PWM_OTTOCAL_HRPWR_CALPWRON_MASK                                        (0x8000U)
#define PWM_OTTOCAL_HRPWR_CALPWRON_SHIFT                                       (0x000FU)
#define PWM_OTTOCAL_HRPWR_CALPWRON_RESETVAL                                    (0x0000U)
#define PWM_OTTOCAL_HRPWR_CALPWRON_MAX                                         (0x0001U)

#define PWM_OTTOCAL_HRPWR_RESETVAL                                             (0x0000U)

/* HRCAL */

#define PWM_OTTOCAL_HRCAL_HRCAL_MASK                                           (0x00FFU)
#define PWM_OTTOCAL_HRCAL_HRCAL_SHIFT                                          (0x0000U)
#define PWM_OTTOCAL_HRCAL_HRCAL_RESETVAL                                       (0x0000U)
#define PWM_OTTOCAL_HRCAL_HRCAL_MAX                                            (0x00FFU)

#define PWM_OTTOCAL_HRCAL_RESERVED_1_MASK                                      (0xFF00U)
#define PWM_OTTOCAL_HRCAL_RESERVED_1_SHIFT                                     (0x0008U)
#define PWM_OTTOCAL_HRCAL_RESERVED_1_RESETVAL                                  (0x0000U)
#define PWM_OTTOCAL_HRCAL_RESERVED_1_MAX                                       (0x00FFU)

#define PWM_OTTOCAL_HRCAL_RESETVAL                                             (0x0000U)

/* HRPRD */

#define PWM_OTTOCAL_HRPRD_HRPRD_MASK                                           (0xFFFFU)
#define PWM_OTTOCAL_HRPRD_HRPRD_SHIFT                                          (0x0000U)
#define PWM_OTTOCAL_HRPRD_HRPRD_RESETVAL                                       (0x0000U)
#define PWM_OTTOCAL_HRPRD_HRPRD_MAX                                            (0xFFFFU)

#define PWM_OTTOCAL_HRPRD_RESETVAL                                             (0x0000U)

/* HRCNT0 */

#define PWM_OTTOCAL_HRCNT0_HRCNT0_MASK                                         (0xFFFFU)
#define PWM_OTTOCAL_HRCNT0_HRCNT0_SHIFT                                        (0x0000U)
#define PWM_OTTOCAL_HRCNT0_HRCNT0_RESETVAL                                     (0x0000U)
#define PWM_OTTOCAL_HRCNT0_HRCNT0_MAX                                          (0xFFFFU)

#define PWM_OTTOCAL_HRCNT0_RESETVAL                                            (0x0000U)

/* HRCNT1 */

#define PWM_OTTOCAL_HRCNT1_HRCNT1_MASK                                         (0xFFFFU)
#define PWM_OTTOCAL_HRCNT1_HRCNT1_SHIFT                                        (0x0000U)
#define PWM_OTTOCAL_HRCNT1_HRCNT1_RESETVAL                                     (0x0000U)
#define PWM_OTTOCAL_HRCNT1_HRCNT1_MAX                                          (0xFFFFU)

#define PWM_OTTOCAL_HRCNT1_RESETVAL                                            (0x0000U)

/* HRMSTEP */

#define PWM_OTTOCAL_HRMSTEP_HRMSTEP_MASK                                       (0x00FFU)
#define PWM_OTTOCAL_HRMSTEP_HRMSTEP_SHIFT                                      (0x0000U)
#define PWM_OTTOCAL_HRMSTEP_HRMSTEP_RESETVAL                                   (0x0000U)
#define PWM_OTTOCAL_HRMSTEP_HRMSTEP_MAX                                        (0x00FFU)

#define PWM_OTTOCAL_HRMSTEP_RESERVED_1_MASK                                    (0xFF00U)
#define PWM_OTTOCAL_HRMSTEP_RESERVED_1_SHIFT                                   (0x0008U)
#define PWM_OTTOCAL_HRMSTEP_RESERVED_1_RESETVAL                                (0x0000U)
#define PWM_OTTOCAL_HRMSTEP_RESERVED_1_MAX                                     (0x00FFU)

#define PWM_OTTOCAL_HRMSTEP_RESETVAL                                           (0x0000U)

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CSL_EPWM_TBCTL                                            (0x0U)
#define CSL_EPWM_TBSTS                                            (0x2U)
#define CSL_EPWM_RESERVED_1								          (0x4U)
#define CSL_EPWM_TBPHS                                            (0x6U)
#define CSL_EPWM_TBCTR                                            (0x8U)
#define CSL_EPWM_TBPRD                                            (0xaU)
#define CSL_EPWM_RESERVED_2    							          (0xcU)
#define CSL_EPWM_CMPCTL                                           (0xeU)
#define CSL_EPWM_RESERVED_3    							          (0x10U)
#define CSL_EPWM_CMPA                                             (0x12U)
#define CSL_EPWM_CMPB                                             (0x14U)
#define CSL_EPWM_AQCTLA                                           (0x16U)
#define CSL_EPWM_AQCTLB                                           (0x18U)
#define CSL_EPWM_AQSFRC                                           (0x1aU)
#define CSL_EPWM_AQCSFRC                                          (0x1cU)
#define CSL_EPWM_DBCTL                                            (0x1eU)
#define CSL_EPWM_DBRED                                            (0x20U)
#define CSL_EPWM_DBFED                                            (0x22U)
#define CSL_EPWM_TZSEL                                            (0x24U)
#define CSL_EPWM_TZDCSEL								          (0x26U)
#define CSL_EPWM_TZCTL                                            (0x28U)
#define CSL_EPWM_TZEINT                                           (0x2aU)
#define CSL_EPWM_TZFLG                                            (0x2cU)
#define CSL_EPWM_TZCLR                                            (0x2eU)
#define CSL_EPWM_TZFRC                                            (0x30U)
#define CSL_EPWM_ETSEL                                            (0x32U)
#define CSL_EPWM_ETPS                                             (0x34U)
#define CSL_EPWM_ETFLG                                            (0x36U)
#define CSL_EPWM_ETCLR                                            (0x38U)
#define CSL_EPWM_ETFRC                                            (0x3aU)
#define CSL_EPWM_PCCTL                                            (0x3cU)
#define CSL_EPWM_RESERVED_4                                   	  (0x3EU)
#define CSL_EPWM_RESERVED_5 [16U]                          		  (0x40U)
#define CSL_EPWM_DCTRIPSEL									      (0x60U)
#define CSL_EPWM_DCACTL				    				   		  (0x62U)
#define CSL_EPWM_DCBCTL									    	  (0x64U)
#define CSL_EPWM_DCFCTL									    	  (0x66U)
#define CSL_EPWM_DCCAPCTL										  (0x68U)
#define CSL_EPWM_DCFOFFSET										  (0x6AU)
#define CSL_EPWM_DCFOFFSETCNT									  (0x6CU)
#define CSL_EPWM_DCFWINDOW										  (0x6EU)
#define CSL_EPWM_DCFWINDOWCNT									  (0x70U)
#define CSL_EPWM_DCCAP								        	  (0x72U)


                 
                      
/****************************************************************************************************                                                                                                    
* Field Definition Macros
****************************************************************************************************/

#define CSL_EPWM_AQCTLA_ZRO_SHIFT                                                       (0U)
#define CSL_EPWM_AQCTLA_ZRO_MASK                                                        (0x00000003U)
#define CSL_EPWM_AQCTLA_ZRO_CLEAR                                                       (1U)
#define CSL_EPWM_AQCTLA_ZRO_SET                                                         (2U)
#define CSL_EPWM_AQCTLA_ZRO_DISABLED                                                    (0U)
#define CSL_EPWM_AQCTLA_ZRO_TOGGLE                                                      (3U)

#define CSL_EPWM_AQCTLA_PRD_SHIFT                                                       (2U)
#define CSL_EPWM_AQCTLA_PRD_MASK                                                        (0x0000000cU)
#define CSL_EPWM_AQCTLA_PRD_CLEAR                                                       (1U)
#define CSL_EPWM_AQCTLA_PRD_SET                                                         (2U)
#define CSL_EPWM_AQCTLA_PRD_DISABLED                                                    (0U)
#define CSL_EPWM_AQCTLA_PRD_TOGGLE                                                      (3U)

#define CSL_EPWM_AQCTLA_CAU_SHIFT                                                       (4U)
#define CSL_EPWM_AQCTLA_CAU_MASK                                                        (0x00000030U)
#define CSL_EPWM_AQCTLA_CAU_DISABLED                                                    (0U)
#define CSL_EPWM_AQCTLA_CAU_CLEAR                                                       (1U)
#define CSL_EPWM_AQCTLA_CAU_SET                                                         (2U)
#define CSL_EPWM_AQCTLA_CAU_TOGGLE                                                      (3U)

#define CSL_EPWM_AQCTLA_CAD_SHIFT                                                       (6U)
#define CSL_EPWM_AQCTLA_CAD_MASK                                                        (0x000000c0U)
#define CSL_EPWM_AQCTLA_CAD_CLEAR                                                       (1U)
#define CSL_EPWM_AQCTLA_CAD_SET                                                         (2U)
#define CSL_EPWM_AQCTLA_CAD_DISABLED                                                    (0U)
#define CSL_EPWM_AQCTLA_CAD_TOGGLE                                                      (3U)

#define CSL_EPWM_AQCTLA_CBU_SHIFT                                                       (8U)
#define CSL_EPWM_AQCTLA_CBU_MASK                                                        (0x00000300U)
#define CSL_EPWM_AQCTLA_CBU_DISABLED                                                    (0U)
#define CSL_EPWM_AQCTLA_CBU_CLEAR                                                       (1U)
#define CSL_EPWM_AQCTLA_CBU_SET                                                         (2U)
#define CSL_EPWM_AQCTLA_CBU_TOGGLE                                                      (3U)

#define CSL_EPWM_AQCTLA_CBD_SHIFT                                                      (10U)
#define CSL_EPWM_AQCTLA_CBD_MASK                                                       (0x00000c00U)
#define CSL_EPWM_AQCTLA_CBD_CLEAR                                                      (1U)
#define CSL_EPWM_AQCTLA_CBD_SET                                                        (2U)
#define CSL_EPWM_AQCTLA_CBD_DISABLED                                                   (0U)
#define CSL_EPWM_AQCTLA_CBD_TOGGLE                                                     (3U)
																					   
#define CSL_EPWM_CMPCTL_LOADAMODE_SHIFT                                                (0U)
#define CSL_EPWM_CMPCTL_LOADAMODE_MASK												   (0x00000003U)
#define CSL_EPWM_CMPCTL_LOADAMODE_CTR_PRD                                              (1U)
#define CSL_EPWM_CMPCTL_LOADAMODE_CTR_0_OR_PRD                                         (2U)
#define CSL_EPWM_CMPCTL_LOADAMODE_CTR_0                                                (0U)
#define CSL_EPWM_CMPCTL_LOADAMODE_FREEZE                                               (3U)
																					
#define CSL_EPWM_CMPCTL_LOADBMODE_SHIFT                                               (2U)
#define CSL_EPWM_CMPCTL_LOADBMODE_MASK                                                (0x0000000cU)
#define CSL_EPWM_CMPCTL_LOADBMODE_CTR_PRD                                             (1U)
#define CSL_EPWM_CMPCTL_LOADBMODE_CTR_0_OR_PRD                                        (2U)
#define CSL_EPWM_CMPCTL_LOADBMODE_CTR_0                                               (0U)
#define CSL_EPWM_CMPCTL_LOADBMODE_FREEZE                                              (3U)
																					
#define CSL_EPWM_CMPCTL_SHDWAMODE_SHIFT                                               (4U)
#define CSL_EPWM_CMPCTL_SHDWAMODE_MASK                                                (0x00000010U)
#define CSL_EPWM_CMPCTL_SHDWAMODE_SHADOW                                              (0U)                                                                                                                                                                  
#define CSL_EPWM_CMPCTL_SHDWAMODE_IMMEDIATE                                           (1U)
																					
#define CSL_EPWM_CMPCTL_SHDWBMODE_SHIFT                                               (6U)
#define CSL_EPWM_CMPCTL_SHDWBMODE_MASK                                                (0x00000040U)
#define CSL_EPWM_CMPCTL_SHDWBMODE_SHADOW                                              (0U)
#define CSL_EPWM_CMPCTL_SHDWBMODE_IMMEDIATE                                           (1U)
																					
#define CSL_EPWM_CMPCTL_SHDWAFULL_SHIFT                                               (8U)
#define CSL_EPWM_CMPCTL_SHDWAFULL_MASK                                                (0x00000100U)
#define CSL_EPWM_CMPCTL_SHDWAFULL_FIFO_FULL                                           (1U)                                                                                                                                                                            
#define CSL_EPWM_CMPCTL_SHDWAFULL_FIFO_NOT_FULL                                       (0U)
																					
#define CSL_EPWM_CMPCTL_SHDWBFULL_SHIFT                                               (9U)
#define CSL_EPWM_CMPCTL_SHDWBFULL_MASK                                                (0x00000200U)
#define CSL_EPWM_CMPCTL_SHDWBFULL_FIFO_NOT_FULL                                       (0U)                                                                                                                                                                          
#define CSL_EPWM_CMPCTL_SHDWBFULL_FIFO_FULL                                           (1U)
                                                                                                                                                                    
#define CSL_EPWM_DBFED_DEL_SHIFT                                                      (0U)                                                                                                                                                                    
#define CSL_EPWM_DBFED_DEL_MASK                                                       (0x000003ffU)
																					
#define CSL_EPWM_PCCTL_CHPEN_SHIFT                                                    (0U)
#define CSL_EPWM_PCCTL_CHPEN_MASK                                                     (0x00000001U)
#define CSL_EPWM_PCCTL_CHPEN_DISABLE                                                  (0U)
#define CSL_EPWM_PCCTL_CHPEN_ENABLE                                                   (1U)
																					
#define CSL_EPWM_PCCTL_OSHTWTH_SHIFT                                                  (1U)
#define CSL_EPWM_PCCTL_OSHTWTH_MASK                                                   (0x0000001eU)
#define CSL_EPWM_PCCTL_OSHTWTH_2_X_SYSCLOCKOUT_BY_8_WIDE                              (1U)
#define CSL_EPWM_PCCTL_OSHTWTH_16_X_SYSCLOCKOUT_BY_8_WIDE                             (15U)
#define CSL_EPWM_PCCTL_OSHTWTH_1_X_SYSCLOCKOUT_BY_8_WIDE                              (0U)
#define CSL_EPWM_PCCTL_OSHTWTH_4_X_SYSCLOCKOUT_BY_8_WIDE                              (3U)
#define CSL_EPWM_PCCTL_OSHTWTH_3_X_SYSCLOCKOUT_BY_8_WIDE                              (2U)
																					
#define CSL_EPWM_PCCTL_CHPFREQ_SHIFT                                                  (5U)
                                                                                                                                                                           
#define CSL_EPWM_PCCTL_CHPFREQ_MASK                                                   (0x000000e0U)
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_6                                                  (5U)                                                                                                                                                                   
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_3                                                  (2U)
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_2                                                  (1U)
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_8                                                  (7U)
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_4                                                  (3U)
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_1                                                  (0U)
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_7                                                  (6U)
#define CSL_EPWM_PCCTL_CHPFREQ_DIV_5                                                  (4U)
																					
#define CSL_EPWM_PCCTL_CHPDUTY_SHIFT                                                 (8U)
#define CSL_EPWM_PCCTL_CHPDUTY_MASK                                                  (0x00000700U)
#define CSL_EPWM_PCCTL_CHPDUTY_DUTY_87_5                                             (6U)                                                                                                                                                                           
#define CSL_EPWM_PCCTL_CHPDUTY_EN_0X7                                                (7U)
#define CSL_EPWM_PCCTL_CHPDUTY_DUTY_25                                               (1U)
#define CSL_EPWM_PCCTL_CHPDUTY_DUTY_75                                               (5U)
#define CSL_EPWM_PCCTL_CHPDUTY_DUTY_62_5                                             (4U)
#define CSL_EPWM_PCCTL_CHPDUTY_DUTY_50                                               (3U)
#define CSL_EPWM_PCCTL_CHPDUTY_DUTY_37_5                                             (2U)
#define CSL_EPWM_PCCTL_CHPDUTY_DUTY_12_5                                             (0U)
                                                                                                                                                                     
																					
#define CSL_EPWM_DBRED_DEL_SHIFT                                                     (0U)
#define CSL_EPWM_DBRED_DEL_MASK                                                      (0x000003ffU)
																					
#define CSL_EPWM_TBCTR_SHIFT                                                         (0U)
                                                                                                                                                                   
#define CSL_EPWM_TBCTR_MASK                                                          (0x0000ffffU)
																					
#define CSL_EPWM_ETSEL_INTSEL_SHIFT                                                  (0U)
#define CSL_EPWM_ETSEL_INTSEL_MASK                                                   (0x00000007U)
#define CSL_EPWM_ETSEL_INTSEL_CTR_CMPB_INCR                                          (6U)
#define CSL_EPWM_ETSEL_INTSEL_CTR_CMPA_DECR                                          (5U)
#define CSL_EPWM_ETSEL_INTSEL_CTR_0                                                  (1U)
#define CSL_EPWM_ETSEL_INTSEL_CTR_PERIOD                                             (2U)
#define CSL_EPWM_ETSEL_INTSEL_CTR_CMPA_INCR                                          (4U)
#define CSL_EPWM_ETSEL_INTSEL_CTR_CMPB_DECR                                          (7U)
																					
#define CSL_EPWM_ETSEL_INTEN_SHIFT                                                   (3U)
#define CSL_EPWM_ETSEL_INTEN_MASK                                                    (0x00000008U)
#define CSL_EPWM_ETSEL_INTEN_DISABLE                                                 (0U)
#define CSL_EPWM_ETSEL_INTEN_ENABLE                                                  (1U)
																					
#define CSL_EPWM_TZEINT_CBC_SHIFT                                                    (1U)
#define CSL_EPWM_TZEINT_CBC_MASK                                                     (0x00000002U)
#define CSL_EPWM_TZEINT_CBC_DISABLE                                                   (0U)
#define CSL_EPWM_TZEINT_CBC_ENABLE                                                    (1U)
																					
#define CSL_EPWM_TZEINT_OST_SHIFT                                                    (2U)
#define CSL_EPWM_TZEINT_OST_MASK                                                     (0x00000004U)
#define CSL_EPWM_TZEINT_OST_DISABLE                                                   (0U)
#define CSL_EPWM_TZEINT_OST_ENABLE                                                    (1U)
																					
#define CSL_EPWM_AQSFRC_ACTSFA_SHIFT                                                 (0U)
#define CSL_EPWM_AQSFRC_ACTSFA_MASK                                                  (0x00000003U)
#define CSL_EPWM_AQSFRC_ACTSFA_SET                                                   (2U)
#define CSL_EPWM_AQSFRC_ACTSFA_CLEAR                                                 (1U)
#define CSL_EPWM_AQSFRC_ACTSFA_DISABLED                                              (0U)
#define CSL_EPWM_AQSFRC_ACTSFA_TOGGLE                                                (3U)
																					
#define CSL_EPWM_AQSFRC_OTSFA_SHIFT                                                  (2U)
#define CSL_EPWM_AQSFRC_OTSFA_MASK                                                   (0x00000004U)
#define CSL_EPWM_AQSFRC_OTSFA_NO_EFFECT                                              (0U)
#define CSL_EPWM_AQSFRC_OTSFA_SW_EVENT                                               (1U)
																					
#define CSL_EPWM_AQSFRC_ACTSFB_SHIFT                                                 (3U)
#define CSL_EPWM_AQSFRC_ACTSFB_MASK                                                  (0x00000018U)
#define CSL_EPWM_AQSFRC_ACTSFB_DISABLED                                              (0U)
#define CSL_EPWM_AQSFRC_ACTSFB_SET                                                   (2U)
#define CSL_EPWM_AQSFRC_ACTSFB_CLEAR                                                 (1U)
#define CSL_EPWM_AQSFRC_ACTSFB_TOGGLE                                                (3U)
																					
#define CSL_EPWM_AQSFRC_OTSFB_SHIFT                                                  (5U)
#define CSL_EPWM_AQSFRC_OTSFB_MASK                                                   (0x00000020U)
#define CSL_EPWM_AQSFRC_OTSFB_NO_EFFECT                                               (0U)
#define CSL_EPWM_AQSFRC_OTSFB_SW_EVENT                                                (1U)
																					
#define CSL_EPWM_AQSFRC_RLDCSF_SHIFT                                                 (6U)
#define CSL_EPWM_AQSFRC_RLDCSF_MASK                                                  (0x000000c0U)
#define CSL_EPWM_AQSFRC_RLDCSF_CTR_0_OR_PERIOD                                       (2U)
#define CSL_EPWM_AQSFRC_RLDCSF_CTR_0                                                 (0U)
#define CSL_EPWM_AQSFRC_RLDCSF_CTR_PERIOD                                            (1U)
#define CSL_EPWM_AQSFRC_RLDCSF_IMMEDIATE                                             (3U)
																					
#define CSL_EPWM_ETPS_INTPRD_SHIFT                                                   (0U)
#define CSL_EPWM_ETPS_INTPRD_MASK                                                    (0x00000003U)
#define CSL_EPWM_ETPS_INTPRD_DISABLE                                                 (0U)
#define CSL_EPWM_ETPS_INTPRD_GEN_THIRD_EVT                                           (3U)
#define CSL_EPWM_ETPS_INTPRD_GEN_SECOND_EVT                                          (2U)
#define CSL_EPWM_ETPS_INTPRD_GEN_FIRST_EVT                                           (1U)
																					
#define CSL_EPWM_ETPS_INTCNT_SHIFT                                                   (2U)
#define CSL_EPWM_ETPS_INTCNT_MASK                                                    (0x0000000cU)
#define CSL_EPWM_ETPS_INTCNT_EVT_3                                                   (3U)
#define CSL_EPWM_ETPS_INTCNT_NO_EVT                                                  (0U)
#define CSL_EPWM_ETPS_INTCNT_EVT_1                                                   (1U)
#define CSL_EPWM_ETPS_INTCNT_EVT_2                                                   (2U)
																					
#define CSL_EPWM_CMPA_SHIFT                                                          (0U)
                                                                                                                                                                    
#define CSL_EPWM_CMPA_MASK                                                           (0x0000ffffU)
																					
#define CSL_EPWM_ETCLR_INT_SHIFT                                                     (0U)
#define CSL_EPWM_ETCLR_INT_MASK                                                      (0x00000001U)
#define CSL_EPWM_ETCLR_INT_NO_EFFECT                                                  (0U)
                                                                                                                                                                    
#define CSL_EPWM_ETCLR_INT_CLEAR                                                      (1U)
																					
#define CSL_EPWM_AQCSFRC_CSFA_SHIFT                                                  (0U)
#define CSL_EPWM_AQCSFRC_CSFA_MASK                                                   (0x00000003U)
#define CSL_EPWM_AQCSFRC_CSFA_HIGH_OUTPUT                                            (2U)
#define CSL_EPWM_AQCSFRC_CSFA_DISABLED                                               (0U)
#define CSL_EPWM_AQCSFRC_CSFA_LOW_OUTPUT                                             (1U)
#define CSL_EPWM_AQCSFRC_CSFA_NO_EFFECT                                              (3U)
																					
#define CSL_EPWM_AQCSFRC_CSFB_SHIFT                                                  (2U)
#define CSL_EPWM_AQCSFRC_CSFB_MASK                                                   (0x0000000cU)
#define CSL_EPWM_AQCSFRC_CSFB_LOW_OUTPUT                                             (1U)
#define CSL_EPWM_AQCSFRC_CSFB_DISABLED                                               (0U)
#define CSL_EPWM_AQCSFRC_CSFB_NO_EFFECT                                              (3U)
#define CSL_EPWM_AQCSFRC_CSFB_HIGH_OUTPUT                                            (2U)
																					
#define CSL_EPWM_AQCTLB_ZRO_SHIFT                                                    (0U)
#define CSL_EPWM_AQCTLB_ZRO_MASK                                                     (0x00000003U)
#define CSL_EPWM_AQCTLB_ZRO_CLEAR                                                    (1U)
#define CSL_EPWM_AQCTLB_ZRO_DISABLED                                                 (0U)
#define CSL_EPWM_AQCTLB_ZRO_TOGGLE                                                   (3U)
#define CSL_EPWM_AQCTLB_ZRO_SET                                                      (2U)
																					
#define CSL_EPWM_AQCTLB_PRD_SHIFT                                                    (2U)
#define CSL_EPWM_AQCTLB_PRD_MASK                                                     (0x0000000cU)
#define CSL_EPWM_AQCTLB_PRD_CLEAR                                                    (1U)
#define CSL_EPWM_AQCTLB_PRD_DISABLED                                                 (0U)
#define CSL_EPWM_AQCTLB_PRD_TOGGLE                                                   (3U)
#define CSL_EPWM_AQCTLB_PRD_SET                                                      (2U)
																					
#define CSL_EPWM_AQCTLB_CAU_SHIFT                                                    (4U)
#define CSL_EPWM_AQCTLB_CAU_MASK                                                     (0x00000030U)
#define CSL_EPWM_AQCTLB_CAU_CLEAR                                                    (1U)
#define CSL_EPWM_AQCTLB_CAU_DISABLED                                                 (0U)
#define CSL_EPWM_AQCTLB_CAU_TOGGLE                                                   (3U)
#define CSL_EPWM_AQCTLB_CAU_SET                                                      (2U)
																					
#define CSL_EPWM_AQCTLB_CAD_SHIFT                                                    (6U)
#define CSL_EPWM_AQCTLB_CAD_MASK                                                     (0x000000c0U)
#define CSL_EPWM_AQCTLB_CAD_CLEAR                                                    (1U)
#define CSL_EPWM_AQCTLB_CAD_DISABLED                                                 (0U)
#define CSL_EPWM_AQCTLB_CAD_TOGGLE                                                   (3U)
#define CSL_EPWM_AQCTLB_CAD_SET                                                      (2U)
																					
#define CSL_EPWM_AQCTLB_CBU_SHIFT                                                    (8U)
#define CSL_EPWM_AQCTLB_CBU_MASK                                                     (0x00000300U)
#define CSL_EPWM_AQCTLB_CBU_TOGGLE                                                   (3U)
#define CSL_EPWM_AQCTLB_CBU_CLEAR                                                    (1U)
#define CSL_EPWM_AQCTLB_CBU_DISABLED                                                 (0U)
#define CSL_EPWM_AQCTLB_CBU_SET                                                      (2U)
																					
#define CSL_EPWM_AQCTLB_CBD_SHIFT                                                    (10U)
#define CSL_EPWM_AQCTLB_CBD_MASK                                                     (0x00000c00U)
#define CSL_EPWM_AQCTLB_CBD_CLEAR                                                    (1U)
#define CSL_EPWM_AQCTLB_CBD_DISABLED                                                 (0U)
#define CSL_EPWM_AQCTLB_CBD_TOGGLE                                                   (3U)
#define CSL_EPWM_AQCTLB_CBD_SET                                                      (2U)
																					
#define CSL_EPWM_TBCTL_CTRMODE_SHIFT                                                 (0U)
#define CSL_EPWM_TBCTL_CTRMODE_MASK                                                  (0x00000003U)
#define CSL_EPWM_TBCTL_CTRMODE_STOP_FREEZE                                           (3U)
#define CSL_EPWM_TBCTL_CTRMODE_DOWN_COUNT                                            (1U)
#define CSL_EPWM_TBCTL_CTRMODE_UP_COUNT                                              (0U)
#define CSL_EPWM_TBCTL_CTRMODE_UP_DOWN_COUNT                                         (2U)
																					
#define CSL_EPWM_TBCTL_PHSEN_SHIFT                                                   (2U)
#define CSL_EPWM_TBCTL_PHSEN_MASK                                                    (0x00000004U)
#define CSL_EPWM_TBCTL_PHSEN_DO_NOT_LOAD                                             (0U)
#define CSL_EPWM_TBCTL_PHSEN_LOAD                                                    (1U)
																					
#define CSL_EPWM_TBCTL_PRDLD_SHIFT                                                   (3U)
#define CSL_EPWM_TBCTL_PRDLD_MASK                                                    (0x00000008U)
#define CSL_EPWM_TBCTL_PRDLD_LOAD_IMMEDIATELY                                         (1U)
#define CSL_EPWM_TBCTL_PRDLD_LOAD_FROM_SHADOW                                         (0U)
																					
#define CSL_EPWM_TBCTL_SYNCOSEL_SHIFT                                                (4U)
#define CSL_EPWM_TBCTL_SYNCOSEL_MASK                                                 (0x00000030U)
#define CSL_EPWM_TBCTL_SYNCOSEL_CTR_0                                                (1U)
#define CSL_EPWM_TBCTL_SYNCOSEL_CTR_CPMB                                             (2U)
#define CSL_EPWM_TBCTL_SYNCOSEL_EPWMXSYNC                                            (0U)
#define CSL_EPWM_TBCTL_SYNCOSEL_DISABLE_EPWMXSYNCO                                   (3U)
																					
#define CSL_EPWM_TBCTL_SWFSYNC_SHIFT                                                 (6U)
#define CSL_EPWM_TBCTL_SWFSYNC_MASK                                                  (0x00000040U)
#define CSL_EPWM_TBCTL_SWFSYNC_FORCE_SYNC                                            (1U)
#define CSL_EPWM_TBCTL_SWFSYNC_NO_EFFECT                                             (0U)
																					
#define CSL_EPWM_TBCTL_HSPCLKDIV_SHIFT                                               (7U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_MASK                                                (0x00000380U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_8                                               (4U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_10                                              (5U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_2                                               (1U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_1                                               (0U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_4                                               (2U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_6                                               (3U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_12                                              (6U)
#define CSL_EPWM_TBCTL_HSPCLKDIV_DIV_14                                              (7U)
																					
#define CSL_EPWM_TBCTL_CLKDIV_SHIFT                                                  (10U)
#define CSL_EPWM_TBCTL_CLKDIV_MASK                                                   (0x00001c00U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_2                                                  (1U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_8                                                  (3U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_32                                                 (5U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_64                                                 (6U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_16                                                 (4U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_4                                                  (2U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_1                                                  (0U)
#define CSL_EPWM_TBCTL_CLKDIV_DIV_128                                                (7U)
																					
#define CSL_EPWM_TBCTL_PHSDIR_SHIFT                                                  (13U)                                                                                                                                                                         
#define CSL_EPWM_TBCTL_PHSDIR_MASK                                                   (0x00002000U)
#define CSL_EPWM_TBCTL_PHSDIR_COUNT_DOWN                                              (0U)                                                                                                                                                                   
#define CSL_EPWM_TBCTL_PHSDIR_COUNT_UP                                                (1U)
																					
#define CSL_EPWM_TBCTL_FREE_SOFT_SHIFT                                               (14U)
#define CSL_EPWM_TBCTL_FREE_SOFT_MASK                                                (0x0000c000U)
#define CSL_EPWM_TBCTL_FREE_SOFT_RUN3                                                (3U)
#define CSL_EPWM_TBCTL_FREE_SOFT_STOP_AFTER_NEXT_CTR                                 (0U)                                                                                                                                                                     
#define CSL_EPWM_TBCTL_FREE_SOFT_RUN2                                                (2U)
#define CSL_EPWM_TBCTL_FREE_SOFT_STOP_AFTER_CYCLE                                    (1U)
																					
#define CSL_EPWM_TZFRC_CBC_SHIFT                                                     (1U)
#define CSL_EPWM_TZFRC_CBC_MASK                                                      (0x00000002U)
#define CSL_EPWM_TZFRC_CBC_FORCE_TRIP                                                 (1U)                                                                                                                                                                      
#define CSL_EPWM_TZFRC_CBC_IGNORE                                                     (0U)
																					
#define CSL_EPWM_TZFRC_OST_SHIFT                                                     (2U)
#define CSL_EPWM_TZFRC_OST_MASK                                                      (0x00000004U)                                                                                                                                                                       
#define CSL_EPWM_TZFRC_OST_FORCE_TRIP                                                 (1U)                                                                                                                                                                   
#define CSL_EPWM_TZFRC_OST_IGNORE                                                     (0U)
																					
#define CSL_EPWM_TZCTL_TZA_SHIFT                                                     (0U)
#define CSL_EPWM_TZCTL_TZA_MASK                                                      (0x00000003U)
#define CSL_EPWM_TZCTL_TZA_LOW_STATE                                                 (2U)
#define CSL_EPWM_TZCTL_TZA_HIGH_IMPEDANCE                                            (0U)
#define CSL_EPWM_TZCTL_TZA_HIGH_STATE                                                (1U)
#define CSL_EPWM_TZCTL_TZA_DO_NOTHING                                                (3U)
																					
#define CSL_EPWM_TZCTL_TZB_SHIFT                                                     (2U)
#define CSL_EPWM_TZCTL_TZB_MASK                                                      (0x0000000cU)
#define CSL_EPWM_TZCTL_TZB_LOW_STATE                                                 (2U)
#define CSL_EPWM_TZCTL_TZB_DO_NOTHING                                                (3U)
#define CSL_EPWM_TZCTL_TZB_HIGH_IMPEDANCE                                             (0U)
#define CSL_EPWM_TZCTL_TZB_HIGH_STATE                                                 (1U)
																					
#define CSL_EPWM_TBSTS_CTRDIR_SHIFT                                                  (0U)
#define CSL_EPWM_TBSTS_CTRDIR_MASK                                                   (0x00000001U)
#define CSL_EPWM_TBSTS_CTRDIR_COUNTING_DOWN                                          (0U)
#define CSL_EPWM_TBSTS_CTRDIR_COUNTING_UP                                            (1U)
																					
#define CSL_EPWM_TBSTS_SYNCI_SHIFT                                                   (1U)
#define CSL_EPWM_TBSTS_SYNCI_MASK                                                    (0x00000002U)
#define CSL_EPWM_TBSTS_SYNCI_EXTERNAL_SYNC                                           (1U)
#define CSL_EPWM_TBSTS_SYNCI_NO_EFFECT                                               (0U)
																					
#define CSL_EPWM_TBSTS_CTRMAX_SHIFT                                                  (2U)
#define CSL_EPWM_TBSTS_CTRMAX_MASK                                                   (0x00000004U)
#define CSL_EPWM_TBSTS_CTRMAX_MAX_VALUE_REACHED                                      (1U)
#define CSL_EPWM_TBSTS_CTRMAX_MAX_VALUE_NOT_REACHED                                  (0U)
																					
#define CSL_EPWM_ETFRC_INT_SHIFT                                                     (0U)
#define CSL_EPWM_ETFRC_INT_MASK                                                      (0x00000001U)
#define CSL_EPWM_ETFRC_INT_IGNORED                                                    (0U)
#define CSL_EPWM_ETFRC_INT_GENERATE_INTR                                              (1U)
																					
#define CSL_EPWM_TBPHS_SHIFT                                                         (0U)                                                                                                                                                                   
#define CSL_EPWM_TBPHS_MASK                                                          (0x0000ffffU)
																					
#define CSL_EPWM_TZSEL_CBCN_SHIFT                                                    (0U)
#define CSL_EPWM_TZSEL_CBCN_MASK                                                     (0x000000ffU)
#define CSL_EPWM_TZSEL_CBCN_ENABLE                                                   (1U)
#define CSL_EPWM_TZSEL_CBCN_DISABLE                                                  (0U)
																					
#define CSL_EPWM_TZSEL_OSHTN_SHIFT                                                   (8U)
#define CSL_EPWM_TZSEL_OSHTN_MASK                                                    (0x0000ff00U)
#define CSL_EPWM_TZSEL_OSHTN_ENABLE                                                  (1U)
#define CSL_EPWM_TZSEL_OSHTN_DISABLE                                                 (0U)
																					
#define CSL_EPWM_ETFLG_INT_SHIFT                                                     (0U)                                                                                                                                                                          
#define CSL_EPWM_ETFLG_INT_MASK                                                      (0x00000001U)
#define CSL_EPWM_ETFLG_INT_INTR_GENERATED                                            (1U)                                                                                                                                                       
#define CSL_EPWM_ETFLG_INT_NO_EVT                                                    (0U)
																					
#define CSL_EPWM_DBCTL_OUT_MODE_SHIFT                                                (0U)
#define CSL_EPWM_DBCTL_OUT_MODE_MASK                                                 (0x00000003U)
#define CSL_EPWM_DBCTL_OUT_MODE_ENABLED                                              (3U)
#define CSL_EPWM_DBCTL_OUT_MODE_DISABLED                                             (0U)
#define CSL_EPWM_DBCTL_OUT_MODE_DISABLE_FALLING_EDGE                                 (2U)
#define CSL_EPWM_DBCTL_OUT_MODE_DISABLE_RISING_EDGE                                  (1U)
																					
#define CSL_EPWM_DBCTL_POLSEL_SHIFT                                                  (2U)
#define CSL_EPWM_DBCTL_POLSEL_MASK                                                   (0x0000000cU)
#define CSL_EPWM_DBCTL_POLSEL_ACTIVE_HIGH_COMPLEMENTARY                              (2U)
#define CSL_EPWM_DBCTL_POLSEL_ACTIVE_LOW                                             (3U)
#define CSL_EPWM_DBCTL_POLSEL_ACTIVE_HIGH                                            (0U)
#define CSL_EPWM_DBCTL_POLSEL_ACTIVE_LOW_COMPLEMENTARY                               (1U)
																					
#define CSL_EPWM_DBCTL_IN_MODE_SHIFT                                                 (4U)
#define CSL_EPWM_DBCTL_IN_MODE_MASK                                                  (0x00000030U)
#define CSL_EPWM_DBCTL_IN_MODE_SRC_ARED_AFED                                         (0U)
#define CSL_EPWM_DBCTL_IN_MODE_SRC_ARED_BFED                                         (2U)
#define CSL_EPWM_DBCTL_IN_MODE_SRC_BRED_AFED                                         (1U)
#define CSL_EPWM_DBCTL_IN_MODE_SRC_BRED_BFED                                         (3U)
																					
#define CSL_EPWM_TZFLG_INT_SHIFT                                                     (0U)
#define CSL_EPWM_TZFLG_INT_MASK                                                      (0x00000001U)
#define CSL_EPWM_TZFLG_INT_GENERATED                                                 (1U)
#define CSL_EPWM_TZFLG_INT_NOT_GENERATED                                             (0U)
																					
#define CSL_EPWM_TZFLG_CBC_SHIFT                                                     (1U)
#define CSL_EPWM_TZFLG_CBC_MASK                                                      (0x00000002U)
#define CSL_EPWM_TZFLG_CBC_NO_TRIP                                                   (0U)
#define CSL_EPWM_TZFLG_CBC_TRIP                                                      (1U)
																					
#define CSL_EPWM_TZFLG_OST_SHIFT                                                     (2U)
#define CSL_EPWM_TZFLG_OST_MASK                                                      (0x00000004U)
#define CSL_EPWM_TZFLG_OST_NO_TRIP                                                   (0U)
#define CSL_EPWM_TZFLG_OST_TRIP                                                      (1U)
																					
#define CSL_EPWM_TBPRD_SHIFT                                                         (0U)                                                                                                                                                                         
#define CSL_EPWM_TBPRD_MASK                                                          (0x0000ffffU)
#define CSL_EPWM_CMPB_SHIFT                                                          (0U)                                                                                                                                                                            
#define CSL_EPWM_CMPB_MASK                                                           (0x0000ffffU)
																					
#define CSL_EPWM_TZCLR_INT_SHIFT                                                     (0U)
#define CSL_EPWM_TZCLR_INT_MASK                                                      (0x00000001U)
#define CSL_EPWM_TZCLR_INT_CLEAR                                                     (1U)
#define CSL_EPWM_TZCLR_INT_NO_EFFECT                                                 (0U)
																					
#define CSL_EPWM_TZCLR_CBC_SHIFT                                                     (1U)
#define CSL_EPWM_TZCLR_CBC_MASK                                                      (0x00000002U)
#define CSL_EPWM_TZCLR_CBC_NO_EFFECT                                                 (0U)
#define CSL_EPWM_TZCLR_CBC_CLEAR                                                     (1U)
																					
#define CSL_EPWM_TZCLR_OST_SHIFT                                                     (2U)
#define CSL_EPWM_TZCLR_OST_MASK                                                      (0x00000004U)
#define CSL_EPWM_TZCLR_OST_NO_EFFECT                                                 (0U)
#define CSL_EPWM_TZCLR_OST_CLEAR                                                     (1U)
																					
#define CSL_EPWM_DCTRIPSEL_DCAHCOMPSEL_MASK                             			 (0x0000000FU)
#define CSL_EPWM_DCTRIPSEL_DCAHCOMPSEL_SHIFT                            			 (0x00U)
																					
#define CSL_EPWM_DCTRIPSEL_DCALCOMPSEL_MASK                            				 (0x000000F0U)
#define CSL_EPWM_DCTRIPSEL_DCALCOMPSEL_SHIFT                           				 (0x04U)
																					
#define CSL_EPWM_DCTRIPSEL_DCBHCOMPSEL_MASK                            				 (0x00000F00U)
#define CSL_EPWM_DCTRIPSEL_DCBHCOMPSEL_SHIFT                           				 (0x08U)
																					
#define CSL_EPWM_DCTRIPSEL_DCBLCOMPSEL_MASK                            				 (0x0000F000U)
#define CSL_EPWM_DCTRIPSEL_DCBLCOMPSEL_SHIFT                           				 (0x0CU)
																					
#define CSL_EPWM_DCACTL_EVT1SRCSEL_MASK                             				 (0x00000001U)
#define CSL_EPWM_DCACTL_EVT1SRCSEL_SHIFT                             				 (0x00U)
																					
#define CSL_EPWM_DCACTL_EVT1FRC_SYNCSEL_MASK                             			 (0x00000002U)
#define CSL_EPWM_DCACTL_EVT1FRC_SYNCSEL_SHIFT                             			 (0x01U)
																					
																					
#define CSL_EPWM_DCACTL_EVT1SOCE_MASK                             					 (0x00000004U)
#define CSL_EPWM_DCACTL_EVT1SOCE_SHIFT                           					 (0x02U)
																					
#define CSL_EPWM_DCACTL_EVT1SYNCE_MASK                           					 (0x00000008U)
#define CSL_EPWM_DCACTL_EVT1SYNCE_SHIFT                             				 (0x03U)
																					
#define CSL_EPWM_DCACTL_RESERVED_1_MASK                             				(0x000000F0U)
#define CSL_EPWM_DCACTL_RESERVED_1_SHIFT                             				(0x04U)
																					
#define CSL_EPWM_DCACTL_EVT2SRCSEL_MASK                             				(0x00000100U)
#define CSL_EPWM_DCACTL_EVT2SRCSEL_SHIFT                             				(0x08U)
																					
																					
#define CSL_EPWM_DCACTL_EVT2FRC_SYNCSEL_MASK                             			(0x00000200U)
#define CSL_EPWM_DCACTL_EVT2FRC_SYNCSEL_SHIFT                             			(0x09U)
																					
#define CSL_EPWM_DCACTL_RESERVED_2_MASK                             				(0x0000FC00U)
#define CSL_EPWM_DCACTL_RESERVED_2_SHIFT                             				(0x0AU)
																					
																					
#define CSL_EPWM_DCFCTL_SRCSEL_MASK                             					(0x00000003U)
#define CSL_EPWM_DCFCTL_SRCSEL_SHIFT                        	  					(0x00U)
																					
																					
#define CSL_EPWM_DCFCTL_BLANKE_MASK                             					(0x00000004U)
#define CSL_EPWM_DCFCTL_BLANKE_SHIFT                        	    				(0x02U)
																					
#define CSL_EPWM_DCFCTL_BLANKINV_MASK                             					(0x0008U)
#define CSL_EPWM_DCFCTL_BLANKINV_SHIFT                        	  					(0x03U)
																					
																					
#define CSL_EPWM_DCFCTL_PULSESEL_MASK                             					(0x00000030U)
#define CSL_EPWM_DCFCTL_PULSESEL_SHIFT                        	    				(0x04U)
																					
																					
#define CSL_EPWM_DCFCTL_RESERVED_1_MASK                             				(0x00000040U)
#define CSL_EPWM_DCFCTL_RESERVED_1_SHIFT                        	  				(0x06U)
																					
#define CSL_EPWM_DCFCTL_RESERVED_2_MASK                             				(0x00000080U)
#define CSL_EPWM_DCFCTL_RESERVED_2_SHIFT                        	    			(0x07U)
																					
#define CSL_EPWM_DCFCTL_RESERVED_3_MASK                             				(0x00001F00U)
#define CSL_EPWM_DCFCTL_RESERVED_3_SHIFT                        	  				(0x08U)
																					
#define CSL_EPWM_DCFCTL_RESERVED_4_MASK                             				(0x0000E000U)
#define CSL_EPWM_DCFCTL_RESERVED_4_SHIFT                        	    			(0x0DU)
																					
																					
#define CSL_EPWM_DCCAPCTL_CAPE_MASK                      	    					(0x0000001U)
#define CSL_EPWM_DCCAPCTL_CAPE_SHIFT                    		 					(0x00U)
																					
																					
#define CSL_EPWM_DCCAPCTL_SHDWMODE_MASK                      	    				(0x0000002U)
#define CSL_EPWM_DCCAPCTL_SHDWMODE_SHIFT                    		 				(0x01U)
																					
																					
#define CSL_EPWM_DCCAPCTL_RESERVED_1_MASK                      	       				(0x000FFFCU)
#define CSL_EPWM_DCCAPCTL_RESERVED_1_SHIFT                    		 				(0x02U)
																					
#define CSL_EPWM_DCFWINDOW_MASK                      	   							(0x00000FFU)
#define CSL_EPWM_DCFWINDOW_SHIFT                    								(0x00U)
																					
																					
#define CSL_EPWM_DCFWINDOW_RESERVED_MASK                      	   					(0x000FF00U)
#define CSL_EPWM_DCFWINDOW_RESERVED_SHIFT                    						(0x08U)
																					
#define CSL_EPWM_DCFOFFSETCNT_MASK                      							(0x000FFFFU)
#define CSL_EPWM_DCFOFFSETCNT_SHIFT                    								(0x00U)
																					
																					
#define CSL_EPWM_DCCAP_MASK                     		 							(0x000FFFFU)
#define CSL_EPWM_DCCAP_SHIFT                   										(0x00U)
																					
#define CSL_EPWM_DCFWINDOWCNT_MASK                     								(0x00000FFU)
#define CSL_EPWM_DCFWINDOWCNT_SHIFT                   								(0x00U)
																					
																					
#define CSL_EPWM_DCFWINDOWCNT_RESERVED_MASK                     					(0x000FF00U)
#define CSL_EPWM_DCFWINDOWCNT_RESERVED_SHIFT                   						(0x08U)


#ifdef __cplusplus
}
#endif
#endif
