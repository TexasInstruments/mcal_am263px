/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2024 Texas Instruments Incorporated
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

#ifndef CDD_DMA_TRIG_XBAR_H_
#define CDD_DMA_TRIG_XBAR_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"

/**************************************************************************
 * Hardware Region  :
 **************************************************************************/

/**************************************************************************
    XBAR INPUT Macros
**************************************************************************/

#if defined(AM263X_PLATFORM) || defined(AM263PX_PLATFORM)
#define CDD_DMA_TRIG_XBAR_LIN0_RXDMA               0
#define CDD_DMA_TRIG_XBAR_LIN0_TXDMA               1
#define CDD_DMA_TRIG_XBAR_LIN1_RXDMA               2
#define CDD_DMA_TRIG_XBAR_LIN1_TXDMA               3
#define CDD_DMA_TRIG_XBAR_LIN2_RXDMA               4
#define CDD_DMA_TRIG_XBAR_LIN2_TXDMA               5
#define CDD_DMA_TRIG_XBAR_LIN3_RXDMA               6
#define CDD_DMA_TRIG_XBAR_LIN3_TXDMA               7
#define CDD_DMA_TRIG_XBAR_LIN4_RXDMA               8
#define CDD_DMA_TRIG_XBAR_LIN4_TXDMA               9
#define CDD_DMA_TRIG_XBAR_I2C0_TX                  10
#define CDD_DMA_TRIG_XBAR_I2C0_RX                  11
#define CDD_DMA_TRIG_XBAR_I2C1_TX                  12
#define CDD_DMA_TRIG_XBAR_I2C1_RX                  13
#define CDD_DMA_TRIG_XBAR_I2C2_TX                  14
#define CDD_DMA_TRIG_XBAR_I2C2_RX                  15
#define CDD_DMA_TRIG_XBAR_I2C3_TX                  16
#define CDD_DMA_TRIG_XBAR_I2C3_RX                  17
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_READ_REQ0       18
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_READ_REQ1       19
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_READ_REQ2       20
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_READ_REQ3       21
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_WRITE_REQ0      22
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_WRITE_REQ1      23
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_WRITE_REQ2      24
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_WRITE_REQ3      25
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_READ_REQ0       26
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_READ_REQ1       27
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_READ_REQ2       28
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_READ_REQ3       29
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_WRITE_REQ0      30
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_WRITE_REQ1      31
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_WRITE_REQ2      32
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_WRITE_REQ3      33
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_READ_REQ0       34
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_READ_REQ1       35
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_READ_REQ2       36
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_READ_REQ3       37
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_WRITE_REQ0      38
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_WRITE_REQ1      39
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_WRITE_REQ2      40
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_WRITE_REQ3      41
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_READ_REQ0       42
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_READ_REQ1       43
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_READ_REQ2       44
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_READ_REQ3       45
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_WRITE_REQ0      46
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_WRITE_REQ1      47
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_WRITE_REQ2      48
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_WRITE_REQ3      49
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_READ_REQ0       50
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_READ_REQ1       51
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_READ_REQ2       52
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_READ_REQ3       53
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_WRITE_REQ0      54
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_WRITE_REQ1      55
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_WRITE_REQ2      56
#define CDD_DMA_TRIG_XBAR_SPI4_DMA_WRITE_REQ3      57
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_0               58
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_1               59
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_2               60
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_3               61
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_0               62
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_1               63
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_2               64
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_3               65
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_0               66
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_1               67
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_2               68
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_3               69
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_0               70
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_1               71
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_2               72
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_3               73
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_0         74
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_1         75
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_2         76
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_3         77
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_0         78
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_1         79
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_2         80
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_3         81
#define CDD_DMA_TRIG_XBAR_MCANSS2_TX_DMA_0         82
#define CDD_DMA_TRIG_XBAR_MCANSS2_TX_DMA_1         83
#define CDD_DMA_TRIG_XBAR_MCANSS2_TX_DMA_2         84
#define CDD_DMA_TRIG_XBAR_MCANSS2_TX_DMA_3         85
#define CDD_DMA_TRIG_XBAR_MCANSS3_TX_DMA_0         86
#define CDD_DMA_TRIG_XBAR_MCANSS3_TX_DMA_1         87
#define CDD_DMA_TRIG_XBAR_MCANSS3_TX_DMA_2         88
#define CDD_DMA_TRIG_XBAR_MCANSS3_TX_DMA_3         89
#define CDD_DMA_TRIG_XBAR_USART0_DMA_0             90
#define CDD_DMA_TRIG_XBAR_USART0_DMA_1             91
#define CDD_DMA_TRIG_XBAR_USART1_DMA_0             92
#define CDD_DMA_TRIG_XBAR_USART1_DMA_1             93
#define CDD_DMA_TRIG_XBAR_USART2_DMA_0             94
#define CDD_DMA_TRIG_XBAR_USART2_DMA_1             95
#define CDD_DMA_TRIG_XBAR_USART3_DMA_0             96
#define CDD_DMA_TRIG_XBAR_USART3_DMA_1             97
#define CDD_DMA_TRIG_XBAR_USART4_DMA_0             98
#define CDD_DMA_TRIG_XBAR_USART4_DMA_1             99
#define CDD_DMA_TRIG_XBAR_USART5_DMA_0             100
#define CDD_DMA_TRIG_XBAR_USART5_DMA_1             101
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_0         102
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_1         103
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_2         104
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_3         105
#define CDD_DMA_TRIG_XBAR_QSPI_INTR                106
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_0      107
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_1      108
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_2      109
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_3      110
#define CDD_DMA_TRIG_XBAR_SOC_TIMESYNC_XBAR1_OUT_0 111
#define CDD_DMA_TRIG_XBAR_SOC_TIMESYNC_XBAR1_OUT_1 112
#define CDD_DMA_TRIG_XBAR_SOC_TIMESYNC_XBAR0_OUT_0 113
#define CDD_DMA_TRIG_XBAR_SOC_TIMESYNC_XBAR0_OUT_1 114
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_0           115
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_1           116
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_2           117
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_3           118
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_4           119
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_5           120
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_6           121
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_7           122
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_8           123
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_9           124
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_10          125
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_11          126
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_12          127
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_13          128
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_14          129
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_15          130
#define CDD_DMA_TRIG_XBAR_MMC_DMA_RD               131
#define CDD_DMA_TRIG_XBAR_MMC_DMA_WR               132
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ0        133
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ1        134
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ2        135
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ3        136
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ4        137
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ5        138
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ0        139
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ1        140
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ2        141
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ3        142
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ4        143
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ5        144
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ6        145
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ7        146
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_0             147
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_1             148
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_2             149
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_3             150
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_4             151
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_5             152
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_6             153
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_0             154
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_1             155
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_2             156
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_3             157
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_4             158
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_5             159
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_6             160
#define CDD_DMA_TRIG_XBAR_MCANSS2_FE_0             161
#define CDD_DMA_TRIG_XBAR_MCANSS2_FE_1             162
#define CDD_DMA_TRIG_XBAR_MCANSS2_FE_2             163
#define CDD_DMA_TRIG_XBAR_MCANSS2_FE_3             164
#define CDD_DMA_TRIG_XBAR_MCANSS2_FE_4             165
#define CDD_DMA_TRIG_XBAR_MCANSS2_FE_5             166
#define CDD_DMA_TRIG_XBAR_MCANSS2_FE_6             167
#define CDD_DMA_TRIG_XBAR_MCANSS3_FE_0             168
#define CDD_DMA_TRIG_XBAR_MCANSS3_FE_1             169
#define CDD_DMA_TRIG_XBAR_MCANSS3_FE_2             170
#define CDD_DMA_TRIG_XBAR_MCANSS3_FE_3             171
#define CDD_DMA_TRIG_XBAR_MCANSS3_FE_4             172
#define CDD_DMA_TRIG_XBAR_MCANSS3_FE_5             173
#define CDD_DMA_TRIG_XBAR_MCANSS3_FE_6             174
#define CDD_DMA_TRIG_XBAR_GPMC_SDMAREQ             175
#endif

#if defined(AM263PX_PLATFORM)
#define CDD_DMA_TRIG_XBAR_MCANSS4_TX_DMA_0    176
#define CDD_DMA_TRIG_XBAR_MCANSS4_TX_DMA_1    177
#define CDD_DMA_TRIG_XBAR_MCANSS4_TX_DMA_2    178
#define CDD_DMA_TRIG_XBAR_MCANSS4_TX_DMA_3    179
#define CDD_DMA_TRIG_XBAR_MCANSS5_TX_DMA_0    180
#define CDD_DMA_TRIG_XBAR_MCANSS5_TX_DMA_1    181
#define CDD_DMA_TRIG_XBAR_MCANSS5_TX_DMA_2    182
#define CDD_DMA_TRIG_XBAR_MCANSS5_TX_DMA_3    183
#define CDD_DMA_TRIG_XBAR_MCANSS6_TX_DMA_0    184
#define CDD_DMA_TRIG_XBAR_MCANSS6_TX_DMA_1    185
#define CDD_DMA_TRIG_XBAR_MCANSS6_TX_DMA_2    186
#define CDD_DMA_TRIG_XBAR_MCANSS6_TX_DMA_3    187
#define CDD_DMA_TRIG_XBAR_MCANSS7_TX_DMA_0    188
#define CDD_DMA_TRIG_XBAR_MCANSS7_TX_DMA_1    189
#define CDD_DMA_TRIG_XBAR_MCANSS7_TX_DMA_2    190
#define CDD_DMA_TRIG_XBAR_MCANSS7_TX_DMA_3    191
#define CDD_DMA_TRIG_XBAR_MCANSS4_FE_0        192
#define CDD_DMA_TRIG_XBAR_MCANSS4_FE_1        193
#define CDD_DMA_TRIG_XBAR_MCANSS4_FE_2        194
#define CDD_DMA_TRIG_XBAR_MCANSS4_FE_3        195
#define CDD_DMA_TRIG_XBAR_MCANSS4_FE_4        196
#define CDD_DMA_TRIG_XBAR_MCANSS4_FE_5        197
#define CDD_DMA_TRIG_XBAR_MCANSS4_FE_6        198
#define CDD_DMA_TRIG_XBAR_MCANSS5_FE_0        199
#define CDD_DMA_TRIG_XBAR_MCANSS5_FE_1        200
#define CDD_DMA_TRIG_XBAR_MCANSS5_FE_2        201
#define CDD_DMA_TRIG_XBAR_MCANSS5_FE_3        202
#define CDD_DMA_TRIG_XBAR_MCANSS5_FE_4        203
#define CDD_DMA_TRIG_XBAR_MCANSS5_FE_5        204
#define CDD_DMA_TRIG_XBAR_MCANSS5_FE_6        205
#define CDD_DMA_TRIG_XBAR_MCANSS6_FE_0        206
#define CDD_DMA_TRIG_XBAR_MCANSS6_FE_1        207
#define CDD_DMA_TRIG_XBAR_MCANSS6_FE_2        208
#define CDD_DMA_TRIG_XBAR_MCANSS6_FE_3        209
#define CDD_DMA_TRIG_XBAR_MCANSS6_FE_4        210
#define CDD_DMA_TRIG_XBAR_MCANSS6_FE_5        211
#define CDD_DMA_TRIG_XBAR_MCANSS6_FE_6        212
#define CDD_DMA_TRIG_XBAR_MCANSS7_FE_0        213
#define CDD_DMA_TRIG_XBAR_MCANSS7_FE_1        214
#define CDD_DMA_TRIG_XBAR_MCANSS7_FE_2        215
#define CDD_DMA_TRIG_XBAR_MCANSS7_FE_3        216
#define CDD_DMA_TRIG_XBAR_MCANSS7_FE_4        217
#define CDD_DMA_TRIG_XBAR_MCANSS7_FE_5        218
#define CDD_DMA_TRIG_XBAR_MCANSS7_FE_6        219
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_READ_REQ0  220
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_READ_REQ1  221
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_READ_REQ2  222
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_READ_REQ3  223
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_WRITE_REQ0 224
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_WRITE_REQ1 225
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_WRITE_REQ2 226
#define CDD_DMA_TRIG_XBAR_SPI5_DMA_WRITE_REQ3 227
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_READ_REQ0  228
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_READ_REQ1  229
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_READ_REQ2  230
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_READ_REQ3  231
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_WRITE_REQ0 232
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_WRITE_REQ1 233
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_WRITE_REQ2 234
#define CDD_DMA_TRIG_XBAR_SPI6_DMA_WRITE_REQ3 235
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_READ_REQ0  236
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_READ_REQ1  237
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_READ_REQ2  238
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_READ_REQ3  239
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_WRITE_REQ0 240
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_WRITE_REQ1 241
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_WRITE_REQ2 242
#define CDD_DMA_TRIG_XBAR_SPI7_DMA_WRITE_REQ3 243
#define CDD_DMA_TRIG_XBAR_RTI4_DMA_0          244
#define CDD_DMA_TRIG_XBAR_RTI4_DMA_1          245
#define CDD_DMA_TRIG_XBAR_RTI4_DMA_2          246
#define CDD_DMA_TRIG_XBAR_RTI4_DMA_3          247
#define CDD_DMA_TRIG_XBAR_RTI5_DMA_0          248
#define CDD_DMA_TRIG_XBAR_RTI5_DMA_1          249
#define CDD_DMA_TRIG_XBAR_RTI5_DMA_2          250
#define CDD_DMA_TRIG_XBAR_RTI5_DMA_3          251
#define CDD_DMA_TRIG_XBAR_RTI6_DMA_0          252
#define CDD_DMA_TRIG_XBAR_RTI6_DMA_1          253
#define CDD_DMA_TRIG_XBAR_RTI6_DMA_2          254
#define CDD_DMA_TRIG_XBAR_RTI6_DMA_3          255
#define CDD_DMA_TRIG_XBAR_RTI7_DMA_0          256
#define CDD_DMA_TRIG_XBAR_RTI7_DMA_1          257
#define CDD_DMA_TRIG_XBAR_RTI7_DMA_2          258
#define CDD_DMA_TRIG_XBAR_RTI7_DMA_3          259
#endif

#if defined(AM261X_PLATFORM)
#define CDD_DMA_TRIG_XBAR_LIN0_RXDMA                    0
#define CDD_DMA_TRIG_XBAR_LIN0_TXDMA                    1
#define CDD_DMA_TRIG_XBAR_LIN1_RXDMA                    2
#define CDD_DMA_TRIG_XBAR_LIN1_TXDMA                    3
#define CDD_DMA_TRIG_XBAR_LIN2_RXDMA                    4
#define CDD_DMA_TRIG_XBAR_LIN2_TXDMA                    5
#define CDD_DMA_TRIG_XBAR_I2C0_TX                       6
#define CDD_DMA_TRIG_XBAR_I2C0_RX                       7
#define CDD_DMA_TRIG_XBAR_I2C1_TX                       8
#define CDD_DMA_TRIG_XBAR_I2C1_RX                       9
#define CDD_DMA_TRIG_XBAR_I2C2_TX                       10
#define CDD_DMA_TRIG_XBAR_I2C2_RX                       11
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_READ_REQ0            12
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_READ_REQ1            13
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_WRITE_REQ0           14
#define CDD_DMA_TRIG_XBAR_SPI0_DMA_WRITE_REQ1           15
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_READ_REQ0            16
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_READ_REQ1            17
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_WRITE_REQ0           18
#define CDD_DMA_TRIG_XBAR_SPI1_DMA_WRITE_REQ1           19
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_READ_REQ0            20
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_READ_REQ1            21
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_WRITE_REQ0           22
#define CDD_DMA_TRIG_XBAR_SPI2_DMA_WRITE_REQ1           23
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_READ_REQ0            24
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_READ_REQ1            25
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_WRITE_REQ0           14
#define CDD_DMA_TRIG_XBAR_SPI3_DMA_WRITE_REQ1           15
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_0                    28
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_1                    29
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_2                    30
#define CDD_DMA_TRIG_XBAR_RTI0_DMA_3                    31
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_0                    32
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_1                    33
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_2                    34
#define CDD_DMA_TRIG_XBAR_RTI1_DMA_3                    35
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_0                    36
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_1                    37
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_2                    38
#define CDD_DMA_TRIG_XBAR_RTI2_DMA_3                    39
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_0                    40
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_1                    41
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_2                    42
#define CDD_DMA_TRIG_XBAR_RTI3_DMA_3                    43
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_0              44
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_1              45
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_2              46
#define CDD_DMA_TRIG_XBAR_MCANSS0_TX_DMA_3              47
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_0              48
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_1              49
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_2              50
#define CDD_DMA_TRIG_XBAR_MCANSS1_TX_DMA_3              51
#define CDD_DMA_TRIG_XBAR_USART0_DMA_0                  52
#define CDD_DMA_TRIG_XBAR_USART0_DMA_1                  53
#define CDD_DMA_TRIG_XBAR_USART1_DMA_0                  54
#define CDD_DMA_TRIG_XBAR_USART1_DMA_1                  55
#define CDD_DMA_TRIG_XBAR_USART2_DMA_0                  56
#define CDD_DMA_TRIG_XBAR_USART2_DMA_1                  57
#define CDD_DMA_TRIG_XBAR_USART3_DMA_0                  58
#define CDD_DMA_TRIG_XBAR_USART3_DMA_1                  59
#define CDD_DMA_TRIG_XBAR_USART4_DMA_0                  60
#define CDD_DMA_TRIG_XBAR_USART4_DMA_1                  61
#define CDD_DMA_TRIG_XBAR_USART5_DMA_0                  62
#define CDD_DMA_TRIG_XBAR_USART5_DMA_1                  63
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_0              64
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_1              65
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_2              66
#define CDD_DMA_TRIG_XBAR_MCRC_DMA_EVENT_3              67
#define CDD_DMA_TRIG_XBAR_OSPI0_INTR                    68
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_4           69
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_5           70
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_6           71
#define CDD_DMA_TRIG_XBAR_GPIO_INT_XBAR_OUT_7           72
#define CDD_DMA_TRIG_XBAR_SOC_TIMESYNC_XBAR_OUT_0       73
#define CDD_DMA_TRIG_XBAR_SOC_TIMESYNC_XBAR_OUT_1       74
#define CDD_DMA_TRIG_XBAR_CONTROLSS_TIMESYNC_XBAR_OUT_0 75
#define CDD_DMA_TRIG_XBAR_CONTROLSS_TIMESYNC_XBAR_OUT_1 76
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_0                77
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_1                78
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_2                79
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_3                80
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_4                81
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_5                82
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_6                83
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_7                84
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_8                85
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_9                86
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_10               87
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_11               88
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_12               89
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_13               90
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_14               91
#define CDD_DMA_TRIG_XBAR_DMA_XBAR_OUT_15               92
#define CDD_DMA_TRIG_XBAR_MMC_DMA_RD                    93
#define CDD_DMA_TRIG_XBAR_MMC_DMA_WR                    94
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ0             95
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ1             96
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ2             97
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ3             98
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ4             99
#define CDD_DMA_TRIG_XBAR_DTHE_SHA_DMA_REQ5             100
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ0             101
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ1             102
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ2             103
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ3             104
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ4             105
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ5             106
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ6             107
#define CDD_DMA_TRIG_XBAR_DTHE_AES_DMA_REQ7             108
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_0                  109
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_1                  110
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_2                  111
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_3                  112
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_4                  113
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_5                  114
#define CDD_DMA_TRIG_XBAR_MCANSS0_FE_6                  115
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_0                  116
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_1                  117
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_2                  118
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_3                  119
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_4                  120
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_5                  121
#define CDD_DMA_TRIG_XBAR_MCANSS1_FE_6                  122
#define CDD_DMA_TRIG_XBAR_GPMC_SDMAREQ                  123
#define CDD_DMA_TRIG_XBAR_OSPI1_INTR                    124
#endif

/**************************************************************************
    XBAR OUTPUT Macros
**************************************************************************/

#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_0  0
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_1  1
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_2  2
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_3  3
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_4  4
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_5  5
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_6  6
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_7  7
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_8  8
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_9  9
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_10 10
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_11 11
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_12 12
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_13 13
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_14 14
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_15 15
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_16 16
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_17 17
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_18 18
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_19 19
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_20 20
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_21 21
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_22 22
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_23 23
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_24 24
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_25 25
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_26 26
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_27 27
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_28 28
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_29 29
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_30 30
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_31 31
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_32 32
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_33 33
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_34 34
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_35 35
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_36 36
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_37 37
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_38 38
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_39 39
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_40 40
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_41 41
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_42 42
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_43 43
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_44 44
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_45 45
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_46 46
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_47 47
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_48 48
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_49 49
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_50 50
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_51 51
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_52 52
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_53 53
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_54 54
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_55 55
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_56 56
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_57 57
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_58 58
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_59 59
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_60 60
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_61 61
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_62 62
#define CDD_DMA_TRIG_XBAR_EDMA_MODULE_63 63

/**************************************************************************
 * Register Macros
 **************************************************************************/

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID              (0x00000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL(MUXCNTL) (0x00000004U + ((MUXCNTL) * 0x4U))

/**************************************************************************
 * Field Definition Macros
 **************************************************************************/

/* PID */

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_SCHEME_MASK     (0xC0000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_SCHEME_SHIFT    (0x0000001EU)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_SCHEME_RESETVAL (0x00000001U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_SCHEME_MAX      (0x00000003U)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_BU_MASK     (0x30000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_BU_SHIFT    (0x0000001CU)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_BU_RESETVAL (0x00000002U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_BU_MAX      (0x00000003U)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_FUNCTION_MASK     (0x0FFF0000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_FUNCTION_SHIFT    (0x00000010U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_FUNCTION_RESETVAL (0x00000694U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_FUNCTION_MAX      (0x00000FFFU)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_RTLVER_MASK     (0x0000F800U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_RTLVER_SHIFT    (0x0000000BU)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_RTLVER_RESETVAL (0x00000010U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_RTLVER_MAX      (0x0000001FU)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MAJREV_MASK     (0x00000700U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MAJREV_SHIFT    (0x00000008U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MAJREV_RESETVAL (0x00000001U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MAJREV_MAX      (0x00000007U)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_CUSTOM_MASK     (0x000000C0U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_CUSTOM_SHIFT    (0x00000006U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_CUSTOM_RESETVAL (0x00000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_CUSTOM_MAX      (0x00000003U)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MINREV_MASK     (0x0000003FU)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MINREV_SHIFT    (0x00000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MINREV_RESETVAL (0x00000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_MINREV_MAX      (0x0000003FU)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_PID_RESETVAL (0x66948100U)

/* MUXCNTL */

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_INT_ENABLE_MASK     (0x00010000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_INT_ENABLE_SHIFT    (0x00000010U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_INT_ENABLE_RESETVAL (0x00000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_INT_ENABLE_MAX      (0x00000001U)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_ENABLE_MASK     (0x000000FFU)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_ENABLE_SHIFT    (0x00000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_ENABLE_RESETVAL (0x00000000U)
#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_ENABLE_MAX      (0x000000FFU)

#define CDD_DMA_CSL_EDMA_TRIG_XBAR_MUXCNTL_RESETVAL (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
