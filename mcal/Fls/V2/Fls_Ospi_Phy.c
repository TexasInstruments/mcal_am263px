/*
 *
 * Copyright (c) 2025 Texas Instruments Incorporated
 *
 * All rights reserved not granted herein.
 *
 * Limited License.
 *
 * Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 * license under copyrights and patents it now or hereafter owns or controls to make,
 * have made, use, import, offer to sell and sell ("Utilize") this software subject to the
 * terms herein.  With respect to the foregoing patent license, such license is granted
 * solely to the extent that any such patent is necessary to Utilize the software alone.
 * The patent license shall not apply to any combinations which include this software,
 * other than combinations with devices manufactured by or for TI ("TI Devices").
 * No hardware patent is licensed hereunder.
 *
 * Redistributions must preserve existing copyright notices and reproduce this license
 * (including the above copyright notice and the disclaimer and (if applicable) source
 * code license limitations below) in the documentation and/or other materials provided
 * with the distribution
 *
 * Redistribution and use in binary form, without modification, are permitted provided
 * that the following conditions are met:
 *
 * No reverse engineering, decompilation, or disassembly of this software is
 * permitted with respect to any software provided in binary form.
 *
 * any redistribution and use are licensed by TI for use only with TI Devices.
 *
 * Nothing shall obligate TI to provide you with source code for the software
 * licensed and provided to you in object code.
 *
 * If software source code is provided to you, modification and redistribution of the
 * source code are permitted provided that the following conditions are met:
 *
 * any redistribution and use of the source code, including any resulting derivative
 * works, are licensed by TI for use only with TI Devices.
 *
 * any redistribution and use of any object code compiled from the source code
 * and any resulting derivative works, are licensed by TI for use only with TI Devices.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of its suppliers
 *
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * DISCLAIMER.
 *
 * THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *  \file     Fls_Ospi_phy.c
 *
 *  This file contains FLS MCAL driver internal functions for OSPI Phy tuning
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Fls_Ospi_Phy.h"
#include "EcuM_Cbk.h"

#define FLS_START_SEC_VAR_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"
uint32         readDataCaptureDelay                                  = 0U;
Std_ReturnType phyInitStatus                                         = E_NOT_OK;
static uint8   gOspiFlashAttackVector[OSPI_FLASH_ATTACK_VECTOR_SIZE] = {
    0xFEU,  // 0b11111110 @ 0x00000400 1024 bytes
    0xFFU,  // 0b11111111 @ 0x00000401 1025 bytes
    // Even Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000000011
    0x01U,  // 0b00000001 @ 0x00000402 1026 bytes
    0x01U,  // 0b00000001 @ 0x00000403 1027 bytes
    0x01U,  // 0b00000001 @ 0x00000404 1028 bytes
    0x01U,  // 0b00000001 @ 0x00000405 1029 bytes
    0x01U,  // 0b00000001 @ 0x00000406 1030 bytes
    0x00U,  // 0b00000000 @ 0x00000407 1031 bytes
    0x00U,  // 0b00000000 @ 0x00000408 1032 bytes
    0xFEU,  // 0b11111110 @ 0x00000409 1033 bytes
    0xFEU,  // 0b11111110 @ 0x0000040A 1034 bytes
    // Odd  Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000000011
    0x01U,  // 0b00000001 @ 0x0000040B 1035 bytes
    0x01U,  // 0b00000001 @ 0x0000040C 1036 bytes
    0x01U,  // 0b00000001 @ 0x0000040D 1037 bytes
    0x01U,  // 0b00000001 @ 0x0000040E 1038 bytes
    0x00U,  // 0b00000000 @ 0x0000040F 1039 bytes
    0x00U,  // 0b00000000 @ 0x00000410 1040 bytes
    0xFEU,  // 0b11111110 @ 0x00000411 1041 bytes
    0xFEU,  // 0b11111110 @ 0x00000412 1042 bytes
    0x01U,  // 0b00000001 @ 0x00000413 1043 bytes
    // Even Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 111110011
    0xFFU,  // 0b11111111 @ 0x00000414 1044 bytes
    0xFFU,  // 0b11111111 @ 0x00000415 1045 bytes
    0xFFU,  // 0b11111111 @ 0x00000416 1046 bytes
    0xFFU,  // 0b11111111 @ 0x00000417 1047 bytes
    0xFFU,  // 0b11111111 @ 0x00000418 1048 bytes
    0x00U,  // 0b00000000 @ 0x00000419 1049 bytes
    0x00U,  // 0b00000000 @ 0x0000041A 1050 bytes
    0xFEU,  // 0b11111110 @ 0x0000041B 1051 bytes
    0xFEU,  // 0b11111110 @ 0x0000041C 1052 bytes
    // Odd  Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 111110011
    0xFFU,  // 0b11111111 @ 0x0000041D 1053 bytes
    0xFFU,  // 0b11111111 @ 0x0000041E 1054 bytes
    0xFFU,  // 0b11111111 @ 0x0000041F 1055 bytes
    0xFFU,  // 0b11111111 @ 0x00000420 1056 bytes
    0x00U,  // 0b00000000 @ 0x00000421 1057 bytes
    0x00U,  // 0b00000000 @ 0x00000422 1058 bytes
    0xFEU,  // 0b11111110 @ 0x00000423 1059 bytes
    0xFEU,  // 0b11111110 @ 0x00000424 1060 bytes
    0xFFU,  // 0b11111111 @ 0x00000425 1061 bytes
    // Even Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000001011
    0x01U,  // 0b00000001 @ 0x00000426 1062 bytes
    0x01U,  // 0b00000001 @ 0x00000427 1063 bytes
    0x01U,  // 0b00000001 @ 0x00000428 1064 bytes
    0x01U,  // 0b00000001 @ 0x00000429 1065 bytes
    0x01U,  // 0b00000001 @ 0x0000042A 1066 bytes
    0xFEU,  // 0b11111110 @ 0x0000042B 1067 bytes
    0x00U,  // 0b00000000 @ 0x0000042C 1068 bytes
    0xFEU,  // 0b11111110 @ 0x0000042D 1069 bytes
    0xFEU,  // 0b11111110 @ 0x0000042E 1070 bytes
    // Odd  Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000001011
    0x01U,  // 0b00000001 @ 0x0000042F 1071 bytes
    0x01U,  // 0b00000001 @ 0x00000430 1072 bytes
    0x01U,  // 0b00000001 @ 0x00000431 1073 bytes
    0x01U,  // 0b00000001 @ 0x00000432 1074 bytes
    0xFEU,  // 0b11111110 @ 0x00000433 1075 bytes
    0x00U,  // 0b00000000 @ 0x00000434 1076 bytes
    0xFEU,  // 0b11111110 @ 0x00000435 1077 bytes
    0xFEU,  // 0b11111110 @ 0x00000436 1078 bytes
    0x01U,  // 0b00000001 @ 0x00000437 1079 bytes
    // Even Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 111111011
    0xFFU,  // 0b11111111 @ 0x00000438 1080 bytes
    0xFFU,  // 0b11111111 @ 0x00000439 1081 bytes
    0xFFU,  // 0b11111111 @ 0x0000043A 1082 bytes
    0xFFU,  // 0b11111111 @ 0x0000043B 1083 bytes
    0xFFU,  // 0b11111111 @ 0x0000043C 1084 bytes
    0xFEU,  // 0b11111110 @ 0x0000043D 1085 bytes
    0x00U,  // 0b00000000 @ 0x0000043E 1086 bytes
    0xFEU,  // 0b11111110 @ 0x0000043F 1087 bytes
    0xFEU,  // 0b11111110 @ 0x00000440 1088 bytes
    // Odd  Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 111111011
    0xFFU,  // 0b11111111 @ 0x00000441 1089 bytes
    0xFFU,  // 0b11111111 @ 0x00000442 1090 bytes
    0xFFU,  // 0b11111111 @ 0x00000443 1091 bytes
    0xFFU,  // 0b11111111 @ 0x00000444 1092 bytes
    0xFEU,  // 0b11111110 @ 0x00000445 1093 bytes
    0x00U,  // 0b00000000 @ 0x00000446 1094 bytes
    0xFEU,  // 0b11111110 @ 0x00000447 1095 bytes
    0xFEU,  // 0b11111110 @ 0x00000448 1096 bytes
    0xFFU,  // 0b11111111 @ 0x00000449 1097 bytes
    // Even Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000000111
    0x01U,  // 0b00000001 @ 0x0000044A 1098 bytes
    0x01U,  // 0b00000001 @ 0x0000044B 1099 bytes
    0x01U,  // 0b00000001 @ 0x0000044C 1100 bytes
    0x01U,  // 0b00000001 @ 0x0000044D 1101 bytes
    0x01U,  // 0b00000001 @ 0x0000044E 1102 bytes
    0x00U,  // 0b00000000 @ 0x0000044F 1103 bytes
    0xFEU,  // 0b11111110 @ 0x00000450 1104 bytes
    0xFEU,  // 0b11111110 @ 0x00000451 1105 bytes
    0xFEU,  // 0b11111110 @ 0x00000452 1106 bytes
    // Odd  Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000000111
    0x01U,  // 0b00000001 @ 0x00000453 1107 bytes
    0x01U,  // 0b00000001 @ 0x00000454 1108 bytes
    0x01U,  // 0b00000001 @ 0x00000455 1109 bytes
    0x01U,  // 0b00000001 @ 0x00000456 1110 bytes
    0x00U,  // 0b00000000 @ 0x00000457 1111 bytes
    0xFEU,  // 0b11111110 @ 0x00000458 1112 bytes
    0xFEU,  // 0b11111110 @ 0x00000459 1113 bytes
    0xFEU,  // 0b11111110 @ 0x0000045A 1114 bytes
    0x01U,  // 0b00000001 @ 0x0000045B 1115 bytes
    // Even Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 111110111
    0xFFU,  // 0b11111111 @ 0x0000045C 1116 bytes
    0xFFU,  // 0b11111111 @ 0x0000045D 1117 bytes
    0xFFU,  // 0b11111111 @ 0x0000045E 1118 bytes
    0xFFU,  // 0b11111111 @ 0x0000045F 1119 bytes
    0xFFU,  // 0b11111111 @ 0x00000460 1120 bytes
    0x00U,  // 0b00000000 @ 0x00000461 1121 bytes
    0xFEU,  // 0b11111110 @ 0x00000462 1122 bytes
    0xFEU,  // 0b11111110 @ 0x00000463 1123 bytes
    0xFEU,  // 0b11111110 @ 0x00000464 1124 bytes
    // Odd  Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 111110111
    0xFFU,  // 0b11111111 @ 0x00000465 1125 bytes
    0xFFU,  // 0b11111111 @ 0x00000466 1126 bytes
    0xFFU,  // 0b11111111 @ 0x00000467 1127 bytes
    0xFFU,  // 0b11111111 @ 0x00000468 1128 bytes
    0x00U,  // 0b00000000 @ 0x00000469 1129 bytes
    0xFEU,  // 0b11111110 @ 0x0000046A 1130 bytes
    0xFEU,  // 0b11111110 @ 0x0000046B 1131 bytes
    0xFEU,  // 0b11111110 @ 0x0000046C 1132 bytes
    0xFFU,  // 0b11111111 @ 0x0000046D 1133 bytes
    // Even Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000001111
    0x01U,  // 0b00000001 @ 0x0000046E 1134 bytes
    0x01U,  // 0b00000001 @ 0x0000046F 1135 bytes
    0x01U,  // 0b00000001 @ 0x00000470 1136 bytes
    0x01U,  // 0b00000001 @ 0x00000471 1137 bytes
    0x01U,  // 0b00000001 @ 0x00000472 1138 bytes
    0xFEU,  // 0b11111110 @ 0x00000473 1139 bytes
    0xFEU,  // 0b11111110 @ 0x00000474 1140 bytes
    0xFEU,  // 0b11111110 @ 0x00000475 1141 bytes
    0xFEU,  // 0b11111110 @ 0x00000476 1142 bytes
    // Odd  Aligned Victim bit: 0U, vic time slice : 111110000, agr time slice : 000001111
    0x01U,  // 0b00000001 @ 0x00000477 1143 bytes
    0x01U,  // 0b00000001 @ 0x00000478 1144 bytes
    0x01U,  // 0b00000001 @ 0x00000479 1145 bytes
    0x01U,  // 0b00000001 @ 0x0000047A 1146 bytes
    0xFEU,  // 0b11111110 @ 0x0000047B 1147 bytes
    0xFEU,  // 0b11111110 @ 0x0000047C 1148 bytes
    0xFEU,  // 0b11111110 @ 0x0000047D 1149 bytes
    0xFEU,  // 0b11111110 @ 0x0000047E 1150 bytes
    0x01U   // 0b00000001 @ 0x0000047F 1151 bytes
};

uint32        phyReadDataCapDelay                                      = 0xFFU;
static uint32 gReadBuf[OSPI_FLASH_ATTACK_VECTOR_SIZE / sizeof(uint32)] = {0U};

Fls_Ospi_phyConfiguration Fls_Ospi_tuningWindowParams = {.phaseDelayElement  = 1U,
                                                         .phyControlMode     = FLS_OSPI_PHY_CONTROL_MODE,
                                                         .dllLockMode        = FLS_OSPI_PHY_DLL_LOCK_MODE,
                                                         .tuningWindowParams = {
                                                             .txDllLowWindowStart  = 0,
                                                             .txDllLowWindowEnd    = 48,
                                                             .txDllHighWindowStart = 20,
                                                             .txDllHighWindowEnd   = 96,
                                                             .rxLowSearchStart     = 0,
                                                             .rxLowSearchEnd       = 40,
                                                             .rxHighSearchStart    = 10,
                                                             .rxHighSearchEnd      = 127,
                                                             .txLowSearchStart     = 0,
                                                             .txLowSearchEnd       = 64,
                                                             .txHighSearchStart    = 20,
                                                             .txHighSearchEnd      = 127,
                                                             .txDLLSearchOffset    = 8,
                                                             .rxTxDLLSearchStep    = 4,
                                                             .rdDelayMin           = 1,
                                                             .rdDelayMax           = 3,
                                                         }};

#define FLS_STOP_SEC_VAR_INIT_UNSPECIFIED
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"

#define FLS_START_SEC_CODE
/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Fls_MemMap.h"
static Std_ReturnType Fls_Ospi_phyConfigBaudrate(uint32 baud);
static Std_ReturnType Fls_Ospi_phyGetBaudRateDivFromObj(uint32 *baudDiv);
static void           Fls_Ospi_phySetRdDataCaptureDelay(uint32 rdDataCapDelay);
static uint32         Fls_Ospi_phyGetRdDataCaptureDelay(void);
static Std_ReturnType Fls_Ospi_phyReadAttackVector(uint32 offset);
static void           Fls_Ospi_phyGetTuningData(uint32 *tuningData, uint32 *tuningDataSize);
static void           Fls_Ospi_phyBasicConfig(void);
static void           Fls_Ospi_phyResyncDLL(void);
static void           Fls_Ospi_phySetRdDelayTxRxDLL(const Fls_Ospi_phyConfig *configPoint);
static void           Fls_Ospi_phyFindRxLow(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result);
static void Fls_Ospi_phyFindRxHigh(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result);
static void Fls_Ospi_phyFindTxLow(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result);
static void Fls_Ospi_phyFindTxHigh(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result);
static Std_ReturnType Fls_Ospi_phyFindOTP1(uint32 flashOffset, Fls_Ospi_phyConfig *otp);
static Std_ReturnType Fls_Ospi_phyTuneDDR(uint32 flashOffset);

static Std_ReturnType Fls_Ospi_phyConfigBaudrate(uint32 baud)
{
    Std_ReturnType status = E_OK;

    if ((baud <= 32U) && (baud >= 2U) && ((baud % 2U) == 0U))
    {
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_MSTR_BAUD_DIV_FLD,
                      CSL_OSPI_BAUD_RATE_DIVISOR(baud));
    }
    else
    {
        status = E_NOT_OK;
    }

    return status;
}

static Std_ReturnType Fls_Ospi_phyGetBaudRateDivFromObj(uint32 *baudDiv)
{
    Std_ReturnType status = E_OK;
    if (NULL_PTR != baudDiv)
    {
        uint32 progBaudDiv =
            HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_MSTR_BAUD_DIV_FLD);

        progBaudDiv = (progBaudDiv << 1U) + 2U;
        *baudDiv    = progBaudDiv;
    }
    else
    {
        status = E_NOT_OK;
    }
    return status;
}

static void Fls_Ospi_phySetRdDataCaptureDelay(uint32 rdDataCapDelay)
{
    /* Set read capture delay */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD,
                  rdDataCapDelay);
}

static uint32 Fls_Ospi_phyGetRdDataCaptureDelay(void)
{
    uint32 readDataCapDelay1 =
        HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD);

    return readDataCapDelay1;
}

static Std_ReturnType Fls_Ospi_phyReadAttackVector(uint32 offset)
{
    Std_ReturnType status            = E_OK;
    uint32         flashDataBaseAddr = 0x60000000U;
    uint8         *src               = (uint8 *)(flashDataBaseAddr + offset);
    uint8         *dst               = (uint8 *)gReadBuf;
    uint32         count             = OSPI_FLASH_ATTACK_VECTOR_SIZE;

    /* Enable Direct Access Mode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_DIR_ACC_CTLR_FLD, 1);
    HW_WR_REG32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_IND_AHB_ADDR_TRIGGER_REG, 0x04000000U);

    while (count > 0U)
    {
        *dst = *src;
        dst++;
        src++;
        count--;
    }

    if (memcmp((const void *)gReadBuf, (const void *)gOspiFlashAttackVector, OSPI_FLASH_ATTACK_VECTOR_SIZE) != 0)
    {
        status = E_NOT_OK;
    }

    return status;
}

static void Fls_Ospi_phyGetTuningData(uint32 *tuningData, uint32 *tuningDataSize)
{
    *tuningData     = (uint32)&gOspiFlashAttackVector[0U];
    *tuningDataSize = OSPI_FLASH_ATTACK_VECTOR_SIZE;
}

void Fls_Ospi_phy_enable(void)
{
    uint32 phyEnable =
        HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_CONFIG_REG_PHY_MODE_ENABLE_FLD);
    if (phyEnable == FALSE)
    {
        /* Set dummyClks 1 less */
        uint32 dummyClks = (uint32)Fls_Config_SFDP_Ptr->protos.dummyClksCmd - 1U;

        /* Set new dummyClk */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                      OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD, dummyClks);

        if (phyReadDataCapDelay != 0xFFU)
        {
            /* Tuning is already done, set read capture delay */
            HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD,
                          phyReadDataCapDelay);
        }

        /* Enable PHY mode */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PHY_MODE_ENABLE_FLD, TRUE);
    }
#if (STD_ON == FLS_OSPI_DAC_ENABLE)
    /* Enable PHY pipeline */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PIPELINE_PHY_FLD, TRUE);
#endif
}

static void Fls_Ospi_phyBasicConfig(void)
{
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_MASTER_CONTROL_REG,
                  OSPI_PHY_MASTER_CONTROL_REG_PHY_MASTER_LOCK_MODE_FLD, Fls_Ospi_tuningWindowParams.dllLockMode);

    /* Select the number of delay element to be inserted between
     * phase detect flip-flops.
     */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_MASTER_CONTROL_REG,
                  OSPI_PHY_MASTER_CONTROL_REG_PHY_MASTER_PHASE_DETECT_SELECTOR_FLD,
                  OSPI_PHASE_DETECT_DLL_NUM_DELAY_ELEMENT(Fls_Ospi_tuningWindowParams.phaseDelayElement));

    /* Configure PHY Control mode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_MASTER_CONTROL_REG,
                  OSPI_PHY_MASTER_CONTROL_REG_PHY_MASTER_BYPASS_MODE_FLD, Fls_Ospi_tuningWindowParams.phyControlMode);
}

static void Fls_Ospi_phyResyncDLL(void)
{
    uint32 idleFlag = 0U;

    /* Wait for Idle */
    while (idleFlag == 0U)
    {
        idleFlag = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_IDLE_FLD);
    }

    /* Disable OSPI Controller */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_SPI_FLD, FALSE);

    /* Clear the delay line resync bit */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_CONFIGURATION_REG,
                  OSPI_PHY_CONFIGURATION_REG_PHY_CONFIG_RESYNC_FLD, 0U);

    /* Reset DLL in master mode */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_CONFIGURATION_REG, OSPI_PHY_CONFIGURATION_REG_PHY_CONFIG_RESET_FLD,
                  0U);

    /* Set Initial delay for the master DLL */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_MASTER_CONTROL_REG,
                  OSPI_PHY_MASTER_CONTROL_REG_PHY_MASTER_INITIAL_DELAY_FLD, 0x03U);

    /* DLL out of reset */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_CONFIGURATION_REG, OSPI_PHY_CONFIGURATION_REG_PHY_CONFIG_RESET_FLD,
                  1U);

    /* Wait DLL lock done */
    while ((HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DLL_OBSERVABLE_LOWER_REG,
                          OSPI_DLL_OBSERVABLE_LOWER_REG_DLL_OBSERVABLE_LOWER_DLL_LOCK_FLD) == 0U))
    {
    }
    /* Wait DLL loopback lock done */
    while ((HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DLL_OBSERVABLE_LOWER_REG,
                          OSPI_DLL_OBSERVABLE_LOWER_REG_DLL_OBSERVABLE_LOWER_LOOPBACK_LOCK_FLD) == 0U))
    {
    }

    /* Resync the Slave DLLs */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_CONFIGURATION_REG,
                  OSPI_PHY_CONFIGURATION_REG_PHY_CONFIG_RESYNC_FLD, 1U);

    /* Enable the controller */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENB_SPI_FLD, TRUE);
}

static void Fls_Ospi_phySetRdDelayTxRxDLL(const Fls_Ospi_phyConfig *configPoint)
{
    uint32 rdDelay = (uint32)configPoint->rdDelay;
    uint32 txDLL   = (uint32)configPoint->txDLL;
    uint32 rxDLL   = (uint32)configPoint->rxDLL;

    /* Set the read delay */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD, rdDelay);

    /* Set the PHY rxDLL and txDLL */
    uint32 dtrEnable =
        HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_ENABLE_DTR_PROTOCOL_FLD);

    /* Sampled on rising edge of clock */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_SAMPLE_EDGE_SEL_FLD,
                  OSPI_RD_DATA_CAPTURE_REG_SAMPLE_EDGE_SEL_FLD_MAX);

    /* If DTR is enabled, enable DQS */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DQS_ENABLE_FLD,
                  dtrEnable);

    /* Set TX DLL delay */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_CONFIGURATION_REG,
                  OSPI_PHY_CONFIGURATION_REG_PHY_CONFIG_TX_DLL_DELAY_FLD, txDLL);
    /* Set RX DLL delay */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_PHY_CONFIGURATION_REG,
                  OSPI_PHY_CONFIGURATION_REG_PHY_CONFIG_RX_DLL_DELAY_FLD, rxDLL);
    /* Re-sync DLL */
    Fls_Ospi_phyResyncDLL();
}

static void Fls_Ospi_phyFindRxLow(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result)
{
    Std_ReturnType        rdAttackStatus = E_OK;
    OSPI_PhyWindowParams *gPhyTuneWindowParams =
        (OSPI_PhyWindowParams *)&Fls_Ospi_tuningWindowParams.tuningWindowParams;

    result->txDLL   = start->txDLL;
    result->rxDLL   = start->rxDLL;
    result->rdDelay = start->rdDelay;

    Fls_Ospi_phySetRdDelayTxRxDLL(result);

    rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);

    while (rdAttackStatus == E_NOT_OK)
    {
        result->rxDLL += (int32_t)gPhyTuneWindowParams->rxTxDLLSearchStep;
        if (result->rxDLL > gPhyTuneWindowParams->rxLowSearchEnd)
        {
            result->rxDLL = 128;
            break;
        }
        Fls_Ospi_phySetRdDelayTxRxDLL(result);
        rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);
    }
}

static void Fls_Ospi_phyFindRxHigh(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result)
{
    Std_ReturnType        rdAttackStatus = E_OK;
    OSPI_PhyWindowParams *gPhyTuneWindowParams =
        (OSPI_PhyWindowParams *)&Fls_Ospi_tuningWindowParams.tuningWindowParams;

    result->txDLL   = start->txDLL;
    result->rxDLL   = start->rxDLL;
    result->rdDelay = start->rdDelay;

    Fls_Ospi_phySetRdDelayTxRxDLL(result);

    rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);

    while (rdAttackStatus == E_NOT_OK)
    {
        result->rxDLL -= (int32_t)gPhyTuneWindowParams->rxTxDLLSearchStep;
        if (result->rxDLL < gPhyTuneWindowParams->rxHighSearchStart)
        {
            result->rxDLL = 128;
            break;
        }
        Fls_Ospi_phySetRdDelayTxRxDLL(result);
        rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);
    }
}

static void Fls_Ospi_phyFindTxLow(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result)
{
    Std_ReturnType        rdAttackStatus = E_OK;
    OSPI_PhyWindowParams *gPhyTuneWindowParams =
        (OSPI_PhyWindowParams *)&Fls_Ospi_tuningWindowParams.tuningWindowParams;

    result->txDLL   = start->txDLL;
    result->rxDLL   = start->rxDLL;
    result->rdDelay = start->rdDelay;

    Fls_Ospi_phySetRdDelayTxRxDLL(result);

    rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);

    while (rdAttackStatus == E_NOT_OK)
    {
        result->txDLL += (int32_t)gPhyTuneWindowParams->rxTxDLLSearchStep;
        if (result->txDLL > gPhyTuneWindowParams->txLowSearchEnd)
        {
            result->txDLL = 128;
            break;
        }
        Fls_Ospi_phySetRdDelayTxRxDLL(result);
        rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);
    }
}

static void Fls_Ospi_phyFindTxHigh(const Fls_Ospi_phyConfig *start, uint32 offset, Fls_Ospi_phyConfig *result)
{
    Std_ReturnType        rdAttackStatus = E_OK;
    OSPI_PhyWindowParams *gPhyTuneWindowParams =
        (OSPI_PhyWindowParams *)&Fls_Ospi_tuningWindowParams.tuningWindowParams;

    result->txDLL   = start->txDLL;
    result->rxDLL   = start->rxDLL;
    result->rdDelay = start->rdDelay;

    Fls_Ospi_phySetRdDelayTxRxDLL(result);

    rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);

    while (rdAttackStatus == E_NOT_OK)
    {
        result->txDLL -= (int32_t)gPhyTuneWindowParams->rxTxDLLSearchStep;
        if (result->txDLL < gPhyTuneWindowParams->txHighSearchStart)
        {
            result->txDLL = 128;
            break;
        }
        Fls_Ospi_phySetRdDelayTxRxDLL(result);
        rdAttackStatus = Fls_Ospi_phyReadAttackVector(offset);
    }
}

static Std_ReturnType Fls_Ospi_phyFindOTP1(uint32 flashOffset, Fls_Ospi_phyConfig *otp)
{
    Std_ReturnType        status = E_OK;
    OSPI_PhyWindowParams *gPhyTuneWindowParams =
        (OSPI_PhyWindowParams *)&Fls_Ospi_tuningWindowParams.tuningWindowParams;
    Fls_Ospi_phyConfig searchPoint;
    Fls_Ospi_phyConfig bottomLeft = {0, 0, 0}, topRight = {0, 0, 0};
    Fls_Ospi_phyConfig gapLow = {0, 0, 0}, gapHigh = {0, 0, 0};
    Fls_Ospi_phyConfig rxLow = {0, 0, 0}, rxHigh = {0, 0, 0};
    Fls_Ospi_phyConfig txLow = {0, 0, 0}, txHigh = {0, 0, 0};
    Fls_Ospi_phyConfig backupPoint = {0, 0, 0}, backupCornerPoint = {0, 0, 0};
    Fls_Ospi_phyConfig sec_rxLow = {0, 0, 0}, sec_rxHigh = {0, 0, 0};
    float32            slope;

    /*
     * Finding RxDLL fails at some of the TxDLL values based on the HW platform.
     * A window of TxDLL values is used to find the RxDLL without errors.
     * This can increase the number of CPU cycles taken for the PHY tuning
     * in the cases where more TxDLL values need to be parsed to find a stable RxDLL.
     */

    /***************************** GOLDEN Primary Rx_Low Search **************/
    /*
     * To find the RxDLL boundaries, we fix a valid TxDLL and search through RxDLL range, rdDelay values
     * As we are not sure of a valid TxDLL we use a window of TxDLL values to find the RxDLL boundaries.
     */

    searchPoint.txDLL = gPhyTuneWindowParams->txDllLowWindowStart;

    while (searchPoint.txDLL <= gPhyTuneWindowParams->txDllLowWindowEnd)
    {
        searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMin;
        searchPoint.rxDLL   = gPhyTuneWindowParams->rxLowSearchStart;
        Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &rxLow);

        while (rxLow.rxDLL == 128)
        {
            searchPoint.rdDelay++;
            if (searchPoint.rdDelay > (int32_t)gPhyTuneWindowParams->rdDelayMax)
            {
                if (searchPoint.txDLL >= gPhyTuneWindowParams->txDllLowWindowEnd)
                {
                    status = E_NOT_OK;
                    return status;
                }
                else
                {
                    break;
                }
            }

            Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &rxLow);
        }

        if (rxLow.rxDLL != 128)
        {
            break;
        }

        searchPoint.txDLL += (int32_t)gPhyTuneWindowParams->rxTxDLLSearchStep;
    }

    /***************************** GOLDEN Secondary Rx_Low Search *****************************/
    /* Search for one more rxLow at different txDll*/
    if (searchPoint.txDLL <= (gPhyTuneWindowParams->txDllLowWindowEnd - gPhyTuneWindowParams->txDLLSearchOffset))
    {
        searchPoint.txDLL += gPhyTuneWindowParams->txDLLSearchOffset;
    }
    else
    {
        searchPoint.txDLL = gPhyTuneWindowParams->txDllLowWindowEnd;
    }

    searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMin;
    searchPoint.rxDLL   = gPhyTuneWindowParams->rxLowSearchStart;

    Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &sec_rxLow);
    while (sec_rxLow.rxDLL == 128)
    {
        searchPoint
            .rdDelay++; /* For each TxDLL in the window, go through all the valid rdDelays until we find the RxLow */
        if (searchPoint.rdDelay > (int32_t)gPhyTuneWindowParams->rdDelayMax)
        {
            if (searchPoint.txDLL >= gPhyTuneWindowParams->txDllLowWindowEnd)
            {
                status = E_NOT_OK;
                return status; /* Not able to find RxLow as there is no valid TxDLL in the TxDLL window */
            }
            else
            {
                break;
            }
        }

        Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &sec_rxLow);
    }

    rxLow.rxDLL   = MIN(rxLow.rxDLL, sec_rxLow.rxDLL);
    rxLow.rdDelay = MIN(rxLow.rdDelay, sec_rxLow.rdDelay);

    /*
     * Reset the search point txDLL to continue the Rx_High search
     */
    searchPoint.txDLL = rxLow.txDLL;

    /***************************** GOLDEN Primary Rx_High Search *********************/
    /*
     * To find rxHigh we use the txDLL values of rxLow
     * Start the rdDelay (Read delay) from maximum and decrement it.
     * As these are valid values and rxHigh rdDelay is always >= rxLow rdDelay
     */

    searchPoint.rxDLL   = gPhyTuneWindowParams->rxHighSearchEnd;
    searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMax;
    Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &rxHigh);
    while (rxHigh.rxDLL == 128)
    {
        searchPoint.rdDelay--;
        if (searchPoint.rdDelay < (int32_t)gPhyTuneWindowParams->rdDelayMin)
        {
            status = E_NOT_OK;
            break;
        }
        Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &rxHigh);
    }

    /***************************** GOLDEN Secondary Rx_High Search *********************/
    /*
     * To find Secondary rxHigh we use the txDLL + Search_offset value of rxLow
     * Start the rdDelay (Read delay) from maximum and decrement it.
     * As these are valid values and rxHigh rdDelay is always >= rxLow rdDelay
     */
    if (searchPoint.txDLL <= (gPhyTuneWindowParams->txDllLowWindowEnd - gPhyTuneWindowParams->txDLLSearchOffset))
    {
        searchPoint.txDLL += gPhyTuneWindowParams->txDLLSearchOffset;
    }
    else
    {
        searchPoint.txDLL = gPhyTuneWindowParams->txDllLowWindowEnd;
    }

    searchPoint.rxDLL   = gPhyTuneWindowParams->rxHighSearchEnd;
    searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMax;

    Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &sec_rxHigh);

    while (sec_rxHigh.rxDLL == 128)
    {
        searchPoint.rdDelay--;
        if (searchPoint.rdDelay < (int32_t)gPhyTuneWindowParams->rdDelayMin)
        {
            status = E_NOT_OK;
            break;
            /*
             * If we don't find a valid Secondary Rx_High, Don't return from tuning function
             * Check whether we have a valid Primary Rx_High and then take decision.
             */
        }
        Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &sec_rxHigh);
    }

    if (sec_rxHigh.rxDLL != 128)
    {
        if (rxHigh.rxDLL == 128)
        {
            rxHigh = sec_rxHigh;
        }
        else
        {
            if (sec_rxHigh.rxDLL > rxHigh.rxDLL)
            {
                rxHigh = sec_rxHigh;
            }
        }
    }
    else
    {
        if (rxHigh.rxDLL == 128)
        {
            status = E_NOT_OK;
            return status;
        }
    }
    /*
     * Check a different point if the rxLow and rxHigh are on the same rdDelay.
     * This avoids mistaking the metastability gap for an rxDLL boundary
     */
    if (rxLow.rdDelay == rxHigh.rdDelay)
    {
        /***************************** BACKUP Primary Rx_Low Search *********************/
        /*
         * Find the rxDLL boundaries using the TxDLL window at the higher end .
         * we start the window_end and decrement the TxDLL value until we find the valid point.
         */

        searchPoint.txDLL = gPhyTuneWindowParams->txDllHighWindowEnd;

        /* Find rxDLL Min */
        while (searchPoint.txDLL >= gPhyTuneWindowParams->txDllHighWindowStart)
        {
            searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMin;
            searchPoint.rxDLL   = gPhyTuneWindowParams->rxLowSearchStart;
            Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &backupPoint);

            while (backupPoint.rxDLL == 128)
            {
                searchPoint.rdDelay++;
                if (searchPoint.rdDelay > (int32_t)gPhyTuneWindowParams->rdDelayMax)
                {
                    if (searchPoint.txDLL <= gPhyTuneWindowParams->txDllHighWindowStart)
                    {
                        status = E_NOT_OK;
                        return status;
                    }
                    else
                    {
                        break;
                    }
                }
                Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &backupPoint);
            }

            if (backupPoint.rxDLL != (int32_t)128)
            {
                break;
            }

            searchPoint.txDLL -= (int32_t)gPhyTuneWindowParams->rxTxDLLSearchStep;
        }

        /***************************** BACKUP Secondary Rx_Low Search *********************/
        /* Search for one more rxLow at different txDll*/
        if (searchPoint.txDLL >= (gPhyTuneWindowParams->txDllHighWindowStart + gPhyTuneWindowParams->txDLLSearchOffset))
        {
            searchPoint.txDLL -= gPhyTuneWindowParams->txDLLSearchOffset;
        }
        else
        {
            searchPoint.txDLL = gPhyTuneWindowParams->txDllHighWindowStart;
        }

        searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMin;
        searchPoint.rxDLL   = gPhyTuneWindowParams->rxLowSearchStart;
        Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &sec_rxLow);
        while (sec_rxLow.rxDLL == 128)
        {
            searchPoint.rdDelay++; /* For each TxDLL in the window, go through all the valid rdDelays until we find the
                                      RxLow */
            if (searchPoint.rdDelay > (int32_t)gPhyTuneWindowParams->rdDelayMax)
            {
                if (searchPoint.txDLL <= gPhyTuneWindowParams->txDllHighWindowStart)
                {
                    status = E_NOT_OK;
                    return status; /* Not able to find RxLow as there is no valid TxDLL in the TxDLL window */
                }
                else
                {
                    break;
                }
            }
            Fls_Ospi_phyFindRxLow(&searchPoint, flashOffset, &sec_rxLow);
        }

        backupPoint.rxDLL   = MIN(backupPoint.rxDLL, sec_rxLow.rxDLL);
        backupPoint.rdDelay = MIN(backupPoint.rdDelay, sec_rxLow.rdDelay);

        if (backupPoint.rxDLL < rxLow.rxDLL)
        {
            rxLow = backupPoint;
        }

        /*
         * Reset the search point txDLL to continue the Rx_High search
         */
        searchPoint.txDLL = backupPoint.txDLL;

        /***************************** BACKUP Primary Rx_High Search *********************/
        /*
         * Find rxDLL Max
         * Start the rdDelay (Read delay) from maximum and decrement it.
         */

        searchPoint.rxDLL   = gPhyTuneWindowParams->rxHighSearchEnd;
        searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMax;
        Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &backupPoint);

        while (backupPoint.rxDLL == 128)
        {
            searchPoint.rdDelay--;
            if (searchPoint.rdDelay < (int32_t)gPhyTuneWindowParams->rdDelayMin)
            {
                status = E_NOT_OK;
                break;
            }
            Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &backupPoint);
        }

        /***************************** BACKUP Secondary Rx_High Search *********************/
        /*
         * Find rxDLL Max
         * Start the rdDelay (Read delay) from maximum and decrement it.
         */

        if (searchPoint.txDLL >= (gPhyTuneWindowParams->txDllHighWindowStart + gPhyTuneWindowParams->txDLLSearchOffset))
        {
            searchPoint.txDLL -= gPhyTuneWindowParams->txDLLSearchOffset;
        }
        else
        {
            searchPoint.txDLL = gPhyTuneWindowParams->txDllHighWindowStart;
        }

        searchPoint.rxDLL   = gPhyTuneWindowParams->rxHighSearchEnd;
        searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMax;
        Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &sec_rxHigh);

        while (sec_rxHigh.rxDLL == 128)
        {
            searchPoint.rdDelay--;
            if (searchPoint.rdDelay < (int32_t)gPhyTuneWindowParams->rdDelayMin)
            {
                status = E_NOT_OK;
                break;
            }
            Fls_Ospi_phyFindRxHigh(&searchPoint, flashOffset, &sec_rxHigh);
        }

        /*
         * Compare the Primary and Secondary point
         * Pick the point which has passing maximum rxDll
         */

        if (sec_rxHigh.rxDLL != 128)
        {
            if (backupPoint.rxDLL == 128)
            {
                backupPoint = sec_rxHigh;
            }
            else
            {
                if (sec_rxHigh.rxDLL > backupPoint.rxDLL)
                {
                    backupPoint = sec_rxHigh;
                }
            }
        }
        else
        {
            if (backupPoint.rxDLL == 128)
            {
                status = E_NOT_OK;
                return status;
            }
        }

        if (backupPoint.rxDLL > rxHigh.rxDLL)
        {
            rxHigh = backupPoint;
        }
    }

    /***************************** GOLDEN Tx_Low Search *********************/
    /*
     * Look for txDLL boundaries at 1/4 of rxDLL window
     * Find txDLL Min
     */

    searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMin;
    searchPoint.rxDLL   = rxLow.rxDLL + ((rxHigh.rxDLL - rxLow.rxDLL) / 4);
    searchPoint.txDLL   = gPhyTuneWindowParams->txLowSearchStart;
    Fls_Ospi_phyFindTxLow(&searchPoint, flashOffset, &txLow);

    while (txLow.txDLL == 128)
    {
        searchPoint.rdDelay++;
        Fls_Ospi_phyFindTxLow(&searchPoint, flashOffset, &txLow);

        if (searchPoint.rdDelay > (int32_t)gPhyTuneWindowParams->rdDelayMax)
        {
            status = E_NOT_OK;

            return status;
        }
    }
    /***************************** GOLDEN Tx_High Search *********************/
    /*
     * Find txDLL Max
     * Start the rdDelay (Read delay) from maximum and decrement it.
     */
    searchPoint.txDLL   = gPhyTuneWindowParams->txHighSearchEnd;
    searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMax;
    Fls_Ospi_phyFindTxHigh(&searchPoint, flashOffset, &txHigh);

    while (txHigh.txDLL == 128)
    {
        searchPoint.rdDelay--;
        Fls_Ospi_phyFindTxHigh(&searchPoint, flashOffset, &txHigh);

        if (searchPoint.rdDelay < (int32_t)gPhyTuneWindowParams->rdDelayMin)
        {
            status = E_NOT_OK;
            return status;
        }
    }

    /*
     * Check a different point if the txLow and txHigh are on the same rdDelay.
     * This avoids mistaking the metastability gap for a txDLL boundary
     */
    if (txLow.rdDelay == txHigh.rdDelay)
    {
        /***************************** BACKUP Tx_Low Search *********************/
        /* Look for txDLL boundaries at 3/4 of rxDLL window */
        /* Find txDLL Min */

        searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMin;
        searchPoint.rxDLL   = rxLow.rxDLL + ((3 * (rxHigh.rxDLL - rxLow.rxDLL)) / 4);
        searchPoint.txDLL   = gPhyTuneWindowParams->txLowSearchStart;
        Fls_Ospi_phyFindTxLow(&searchPoint, flashOffset, &backupPoint);
        while (backupPoint.txDLL == 128)
        {
            searchPoint.rdDelay++;
            Fls_Ospi_phyFindTxLow(&searchPoint, flashOffset, &backupPoint);
            if (searchPoint.rdDelay > (int32_t)gPhyTuneWindowParams->rdDelayMax)
            {
                status = E_NOT_OK;
                return status;
            }
        }
        if (backupPoint.txDLL < txLow.txDLL)
        {
            txLow = backupPoint;
        }

        /***************************** BACKUP Tx_High Search *********************/
        /*
         * Find txDLL Max
         * Start the rdDelay (Read delay) from maximum and decrement it.
         */

        searchPoint.txDLL   = gPhyTuneWindowParams->txHighSearchEnd;
        searchPoint.rdDelay = (int32_t)gPhyTuneWindowParams->rdDelayMax;
        Fls_Ospi_phyFindTxHigh(&searchPoint, flashOffset, &backupPoint);
        while (backupPoint.txDLL == 128)
        {
            searchPoint.rdDelay--;
            Fls_Ospi_phyFindTxHigh(&searchPoint, flashOffset, &backupPoint);
            if (searchPoint.rdDelay < (int32_t)gPhyTuneWindowParams->rdDelayMin)
            {
                status = E_NOT_OK;
                return status;
            }
        }
        if (backupPoint.txDLL > txHigh.txDLL)
        {
            txHigh = backupPoint;
        }
    }

    /*
     * Set bottom left and top right right corners.  These are theoretical corners. They may not actually be "good"
     * points. But the longest diagonal of the shmoo will be between these corners.
     */

    /* Bottom Left */
    bottomLeft.txDLL = txLow.txDLL;
    bottomLeft.rxDLL = rxLow.rxDLL;

    if (txLow.rdDelay <= rxLow.rdDelay)
    {
        bottomLeft.rdDelay = txLow.rdDelay;
    }
    else
    {
        bottomLeft.rdDelay = rxLow.rdDelay;
    }

    backupCornerPoint        = bottomLeft;
    backupCornerPoint.txDLL += 4;
    backupCornerPoint.rxDLL += 4;

    Fls_Ospi_phySetRdDelayTxRxDLL(&backupCornerPoint);

    status = Fls_Ospi_phyReadAttackVector(flashOffset);

    if (status == E_NOT_OK)
    {
        backupCornerPoint.rdDelay--;
        Fls_Ospi_phySetRdDelayTxRxDLL(&backupCornerPoint);
        status = Fls_Ospi_phyReadAttackVector(flashOffset);
    }

    if (status == E_OK)
    {
        bottomLeft.rdDelay = backupCornerPoint.rdDelay;
    }

    topRight.txDLL = txHigh.txDLL;
    topRight.rxDLL = rxHigh.rxDLL;

    if (txHigh.rdDelay > rxHigh.rdDelay)
    {
        topRight.rdDelay = txHigh.rdDelay;
    }
    else
    {
        topRight.rdDelay = rxHigh.rdDelay;
    }

    backupCornerPoint        = topRight;
    backupCornerPoint.txDLL -= 4;
    backupCornerPoint.rxDLL -= 4;

    Fls_Ospi_phySetRdDelayTxRxDLL(&backupCornerPoint);

    status = Fls_Ospi_phyReadAttackVector(flashOffset);

    if (status == E_NOT_OK)
    {
        backupCornerPoint.rdDelay++;
        Fls_Ospi_phySetRdDelayTxRxDLL(&backupCornerPoint);
        status = Fls_Ospi_phyReadAttackVector(flashOffset);
    }

    if (status == E_OK)
    {
        topRight.rdDelay = backupCornerPoint.rdDelay;
    }

    /* Find the equation of diagonal between topRight and bottomLeft */

    /* Slope and Intercept*/
    slope =
        ((float32)topRight.rxDLL - (float32)bottomLeft.rxDLL) / ((float32)topRight.txDLL - (float32)bottomLeft.txDLL);
    /* Binary Search */
    Fls_Ospi_phyConfig left, right;
    /* Search along the diagonal between corners */
    left                = bottomLeft;
    right               = topRight;
    searchPoint.txDLL   = left.txDLL + ((right.txDLL - left.txDLL) / 2);
    searchPoint.rxDLL   = left.rxDLL + ((right.rxDLL - left.rxDLL) / 2);
    searchPoint.rdDelay = left.rdDelay;

    do
    {
        Fls_Ospi_phySetRdDelayTxRxDLL(&searchPoint);

        status = Fls_Ospi_phyReadAttackVector(flashOffset);
        if (status == E_NOT_OK)
        {
            /*
             * As the read failed, we go to the lower half for finding the gap low
             */
            right.txDLL = searchPoint.txDLL;
            right.rxDLL = searchPoint.rxDLL;

            searchPoint.txDLL = left.txDLL + ((searchPoint.txDLL - left.txDLL) / 2);
            searchPoint.rxDLL = left.rxDLL + ((searchPoint.rxDLL - left.rxDLL) / 2);
        }
        else
        {
            /*
             * As the read is a success we go to the upper half for finding the gap low
             */
            left.txDLL = searchPoint.txDLL;
            left.rxDLL = searchPoint.rxDLL;

            searchPoint.txDLL = searchPoint.txDLL + ((right.txDLL - searchPoint.txDLL) / 2);
            searchPoint.rxDLL = searchPoint.rxDLL + ((right.rxDLL - searchPoint.rxDLL) / 2);
        }
        /* Break the loop if the window has closed. */
    } while (((right.txDLL - left.txDLL) >= 2) && ((right.rxDLL - left.rxDLL) >= 2));

    gapLow = searchPoint;

    /* If there's only one segment, put tuning point in the middle and adjust for temperature */
    if (bottomLeft.rdDelay == topRight.rdDelay)
    {
        /* Start of the metastability gap is a good approximation for the topRight */
        topRight            = gapLow;
        searchPoint.rdDelay = bottomLeft.rdDelay;
        searchPoint.txDLL   = (bottomLeft.txDLL + topRight.txDLL) / 2;
        searchPoint.rxDLL   = (bottomLeft.rxDLL + topRight.rxDLL) / 2;

        /* TODO: Temperature adjustment */
    }
    else
    {
        /* If there are two segments, find the start and end of the second one */
        left                = bottomLeft;
        right               = topRight;
        searchPoint.txDLL   = left.txDLL + ((right.txDLL - left.txDLL) / 2);
        searchPoint.rxDLL   = left.rxDLL + ((right.rxDLL - left.rxDLL) / 2);
        searchPoint.rdDelay = right.rdDelay;
        do
        {
            Fls_Ospi_phySetRdDelayTxRxDLL(&searchPoint);
            status = Fls_Ospi_phyReadAttackVector(flashOffset);
            if (status == E_NOT_OK)
            {
                /*
                 * As the read failed, we go to the upper half for finding the gap high
                 */
                left.txDLL = searchPoint.txDLL;
                left.rxDLL = searchPoint.rxDLL;

                searchPoint.txDLL = searchPoint.txDLL + ((right.txDLL - searchPoint.txDLL) / 2);
                searchPoint.rxDLL = searchPoint.rxDLL + ((right.rxDLL - searchPoint.rxDLL) / 2);
            }
            else
            {
                /*
                 * As the read is a success we go to the lower half for finding the gap high
                 */
                right.txDLL = searchPoint.txDLL;
                right.rxDLL = searchPoint.rxDLL;

                searchPoint.txDLL = left.txDLL + ((searchPoint.txDLL - left.txDLL) / 2);
                searchPoint.rxDLL = left.rxDLL + ((searchPoint.rxDLL - left.rxDLL) / 2);
            }
            /* Break the loop if the window has closed. */
        } while (((right.txDLL - left.txDLL) >= 2) && ((right.rxDLL - left.rxDLL) >= 2));
        gapHigh = searchPoint;

        /* Place the final tuning point of the PHY in the corner furthest from the gap */
        int32_t len1 = (FLS_PHY_ABS(gapLow.txDLL - bottomLeft.txDLL)) + (FLS_PHY_ABS(gapLow.rxDLL - bottomLeft.rxDLL));
        int32_t len2 = (FLS_PHY_ABS(gapHigh.txDLL - topRight.txDLL)) + (FLS_PHY_ABS(gapHigh.rxDLL - topRight.rxDLL));

        if (len2 > len1)
        {
            int32_t delta       = (topRight.txDLL - gapHigh.txDLL) / 2;
            searchPoint         = topRight;
            searchPoint.txDLL  -= delta;
            float32 deltaFloat  = (float32)delta;
            float32 product     = deltaFloat * slope;
            searchPoint.rxDLL  -= (int32_t)(product);
        }
        else
        {
            int32_t delta       = (gapLow.txDLL - bottomLeft.txDLL) / 2;
            searchPoint         = bottomLeft;
            searchPoint.txDLL  += delta;
            float32 deltaFloat  = (float32)delta;
            float32 product     = deltaFloat * slope;
            searchPoint.rxDLL  += (int32_t)(product);
        }
    }

    Fls_Ospi_phySetRdDelayTxRxDLL(&searchPoint);

    status = Fls_Ospi_phyReadAttackVector(flashOffset);

    if (status == E_OK)
    {
        otp->rxDLL   = searchPoint.rxDLL;
        otp->txDLL   = searchPoint.txDLL;
        otp->rdDelay = searchPoint.rdDelay;
    }
    else
    {
        otp->rxDLL   = 0;
        otp->txDLL   = 0;
        otp->rdDelay = 0;
    }

    return status;
}

void Fls_Ospi_phy_disable(void)
{
    uint32 phyEnable = HW_RD_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PHY_MODE_ENABLE_FLD);
#if (STD_ON == FLS_OSPI_DAC_ENABLE)
    /* Disable PHY pipeline */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PIPELINE_PHY_FLD, FALSE);
#endif
    if (phyEnable == TRUE)
    {
        uint32 dummyClks = (uint32)Fls_Config_SFDP_Ptr->protos.dummyClksCmd - 1U;
        /* Set new dummyClk */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_DEV_INSTR_RD_CONFIG_REG,
                      OSPI_DEV_INSTR_RD_CONFIG_REG_DUMMY_RD_CLK_CYCLES_FLD, dummyClks);

        /* Set the non-PHY read delay */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_RD_DATA_CAPTURE_REG, OSPI_RD_DATA_CAPTURE_REG_DELAY_FLD,
                      readDataCaptureDelay);

        /* Disable PHY mode */
        HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PHY_MODE_ENABLE_FLD, FALSE);
    }
}

static Std_ReturnType Fls_Ospi_phyTuneDDR(uint32 flashOffset)
{
    Std_ReturnType     status = E_OK;
    Fls_Ospi_phyConfig otp;

    /* Enable PHY */
    Fls_Ospi_phy_enable();
    /* keep phy pipeline disabled */
    HW_WR_FIELD32(FLS_OSPI_CTRL_BASE_ADDR + OSPI_CONFIG_REG, OSPI_CONFIG_REG_PIPELINE_PHY_FLD, FALSE);
    /* Perform the Basic PHY configuration for the OSPI controller */
    Fls_Ospi_phyBasicConfig();

    /* Use the normal algorithm */
    status = Fls_Ospi_phyFindOTP1(flashOffset, &otp);
    /* Configure phy for the optimal tuning point */

    Fls_Ospi_phySetRdDelayTxRxDLL(&otp);
    /* Update the phyRdDelay book-keeping. This is needed when we enable PHY later */

    phyReadDataCapDelay = (uint32)otp.rdDelay;

    /* Disable PHY */
    Fls_Ospi_phy_disable();

    return status;
}

Std_ReturnType Fls_Ospi_phyInit(void)
{
    Std_ReturnType status             = E_OK;
    Std_ReturnType attackVectorStatus = E_NOT_OK;

    uint32 phyTuningOffset             = OSPI_PHY_OFFSET;
    uint32 origBaudRateDiv             = 0U;
    bool   readCapDelayModReq          = false;
    uint32 initialReadDataCaptureDelay = 0U;

    (void)Fls_Ospi_phyGetBaudRateDivFromObj(&origBaudRateDiv);

    /*Configure to max baudrate to read attack vector*/
    (void)Fls_Ospi_phyConfigBaudrate(MAX_BAUDRATE_DIVIDER);

    /* Reading the readcapture delay set by Fls Driver */
    readDataCaptureDelay        = Fls_Ospi_phyGetRdDataCaptureDelay();
    initialReadDataCaptureDelay = readDataCaptureDelay;

    attackVectorStatus = Fls_Ospi_phyReadAttackVector(phyTuningOffset);

    (void)Fls_Ospi_phyConfigBaudrate(origBaudRateDiv);

    /* Check if attack vector status is successful over the readCaptureDelay sweep */
    if (attackVectorStatus != E_OK)
    {
        readDataCaptureDelay = 8U;
        while ((attackVectorStatus != E_OK) && (readDataCaptureDelay > 0U))
        {
            Fls_Ospi_phySetRdDataCaptureDelay(readDataCaptureDelay);
            attackVectorStatus = Fls_Ospi_phyReadAttackVector(phyTuningOffset);
            readDataCaptureDelay--;
        }
    }

    if (attackVectorStatus != E_OK)
    {
        /* Flash the attack vector to the last block if the attack vector is not already written in the flash.
         * This step ensures that the PHY tuning data is available for proper operation of the OSPI interface.
         * Without this, the system may fail to achieve optimal performance or encounter communication issues.
         */
        attackVectorStatus           = E_NOT_OK;
        uint32         phyTuningData = 0U, phyTuningDataSize = 0U;
        Std_ReturnType retVal = E_NOT_OK;
        OSPI_Handle    handle = Fls_DrvObj.spiHandle;
        Fls_Ospi_phyGetTuningData(&phyTuningData, &phyTuningDataSize);

        /* Setting to a known readcapturedelay value so that first attack vector
         * read after write will pass most probably
         * */
        readDataCaptureDelay = initialReadDataCaptureDelay;
        Fls_Ospi_phySetRdDataCaptureDelay(readDataCaptureDelay);
        retVal = Fls_norSectorErase(handle, OSPI_PHY_OFFSET);

        /* If erase has passed */
        if (E_OK == retVal)
        {
            retVal = Nor_OspiWrite(handle, OSPI_PHY_OFFSET, (uint8 *)phyTuningData, phyTuningDataSize);
        }

        /* If write has passed */
        if (E_OK == retVal)
        {
            attackVectorStatus = Fls_Ospi_phyReadAttackVector(phyTuningOffset);

            /* Attempting a readCaptureDelay sweep to find the new readCapDelay */
            readDataCaptureDelay = 8U;
            while ((attackVectorStatus != E_OK) && (readDataCaptureDelay > 0U))
            {
                Fls_Ospi_phySetRdDataCaptureDelay(readDataCaptureDelay);
                attackVectorStatus = Fls_Ospi_phyReadAttackVector(phyTuningOffset);
                readDataCaptureDelay--;
                readCapDelayModReq = true;
            }

            /*
             * If readCapdelay needs to be changed after attack vector writing and reading (above example) then the
             * variable needs to be updated for bookkeeping. This is done above. Else we are reverting to old and known
             * readCaptureDelay.
             */
            if (false == readCapDelayModReq)
            {
                readDataCaptureDelay = initialReadDataCaptureDelay;
                Fls_Ospi_phySetRdDataCaptureDelay(readDataCaptureDelay);
            }
        }
    }

    if (attackVectorStatus == E_OK)
    {
        status += Fls_Ospi_phyTuneDDR(phyTuningOffset);
    }
    else
    {
        status = E_NOT_OK;
    }

    if (status == E_OK)
    {
        phyInitStatus = E_OK;
    }
    else
    {
        /* If failed by any means, then reverting readCapturedelay to a know value */
        readDataCaptureDelay = initialReadDataCaptureDelay;
        Fls_Ospi_phySetRdDataCaptureDelay(readDataCaptureDelay);
    }

    return phyInitStatus;
}
#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

/*******************************************************************************
 *  End of File: Fls_Ospi_Phy.c
 ******************************************************************************/
