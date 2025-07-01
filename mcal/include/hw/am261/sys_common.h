
/*
* Copyright (C) 2023 Texas Instruments Incorporated - TI web adress www.ti.com
*
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
*/


#ifndef SYS_COMMON_H
#define SYS_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

/*LDRA_NOANALYSIS*/
#include <stdint.h>
#include <stdbool.h>
#include "Platform_Types.h"
#include "mcal_hw_soc_defines.h"

/*LDRA_ANALYSIS*/

/*LDRA_INSPECTED 340 S : MISRAC_2012_D.4.9
 * "Reason - Macro cannot be avoided here" */
#define M_UNUSED(x)            ((x) = (x))

typedef volatile uint64        REG64;
typedef volatile uint32        REG32;
typedef volatile uint16        REG16;
typedef volatile uint8         REG8;

/*LDRA_INSPECTED 580 S : MISRAC_2012_R.20.4
 * "Reason - type definition of Macro used for ASR4 " */
/*! \brief
 * Registers Read/Write MACROS
 */
#define M_REG_WRITE8(w_addr, c_data)       (*((REG8  *)((w_addr)))) = ((uint8)((c_data)))
#define M_REG_WRITE16(w_addr, h_data)      (*((REG16 *)((w_addr)))) = ((uint16)((h_data)))
#define M_REG_WRITE32(w_addr, w_data)      (*((REG32 *)((w_addr)))) = ((uint32)((w_data)))
#define M_REG_WRITE64(w_addr, l_data)      (*((REG64 *)((w_addr)))) = ((uint64)((l_data)))

#define M_REG_READ8(w_addr)                (*((REG8  *)((w_addr))))
#define M_REG_READ16(w_addr)               (*((REG16 *)((w_addr))))
#define M_REG_READ32(w_addr)               (*((REG32 *)((w_addr))))
#define M_REG_READ64(w_addr)               (*((REG64 *)((w_addr))))

/*! \brief
 * Memory Read/Write MACROS
 */
#define M_MEM_WRITE8(w_addr, c_data)       (*((uint8  *)((w_addr)))) = ((uint8)((c_data)))
#define M_MEM_WRITE16(w_addr, h_data)      (*((uint16 *)((w_addr)))) = ((uint16)((h_data)))
#define M_MEM_WRITE32(w_addr, w_data)      (*((uint32 *)((w_addr)))) = ((uint32)((w_data)))
#define M_MEM_WRITE64(w_addr, l_data)      (*((uint64 *)((w_addr)))) = ((uint64)((l_data)))

#define M_MEM_READ8(w_addr)                (*((uint8  *)((w_addr))))
#define M_MEM_READ16(w_addr)               (*((uint16 *)((w_addr))))
#define M_MEM_READ32(w_addr)               (*((uint32 *)((w_addr))))
#define M_MEM_READ64(w_addr)               (*((uint64 *)((w_addr))))

/*! \brief
 * 32 bit register compare macro
 */
#define M_REG32_COMPARE(w_hwVal, w_swVal)  (((uint32)(w_swVal)) ^ ((uint32)(w_hwVal)))

/*! \brief
 * 32 bit register write and compare macro
 */
#define M_REG_SWRITE32(w_regAddr, w_regVal, regWrSts)   \
                do{ \
                      M_REG_WRITE32((&(w_regAddr)), (w_regVal)); \
                     (regWrSts) |= ((M_REG_READ32((&(w_regAddr)))) ^ (w_regVal)); \
                   }while(FALSE);

/*! \brief
 * 16 bit register write and compare macro
 */
#define M_REG_SWRITE16(w_regAddr, w_regVal, regWrSts)   \
                do{ \
                     M_REG_WRITE16((&(w_regAddr)), (w_regVal)); \
                     (regWrSts) |= ((M_REG_READ16((&(w_regAddr)))) ^ (w_regVal)); \
                   }while(FALSE);

/*! \brief
 * Register Structure member write and compare macro
 */
#define M_REG_STRUCT_SWRITE(w_hwRegStruct, w_regVal, regWrSts)   \
                do{ \
                       (w_hwRegStruct) = (w_regVal); \
                     (regWrSts) |= ((w_hwRegStruct) ^ (w_regVal)); \
                   }while(FALSE);

/*! \brief
 * 32 bit register field read - bit fields input
 */
#define M_REG_BITS_READ32(w_addr, c_ebit, c_sbit)   \
            (((M_REG_READ32((w_addr))) & (M_ONES((c_ebit), (c_sbit)))) >> (c_sbit))

/*! \brief
 * Generates a pattern of ones between end bit and start bit
 * M_ONES(7,4) will give 0x000000F0
 */
#define M_ONES(c_ebit, c_sbit) (((1U << (((c_ebit) - (c_sbit)) + 1U)) - 1U) << (c_sbit))

/*! \brief
 * Generates a pattern of zeros between end bit and start bit
 * M_MASK(7,4) will give 0xFFFFFF0F
 */
#define M_MASK(c_ebit, c_sbit) (~(M_ONES((c_ebit), (c_sbit))))

/*! \brief
 * Bounds the value before writing to register
 * M_VAL_BOUND(0x1F, 7, 4) will remove the extra bit resulting in 0xF
 * TODO: Generate a warning if extra bit found
 */
#define M_VAL_BOUND(val, c_ebit, c_sbit)   ((M_ONES((c_ebit), (c_sbit)) >> (c_sbit)) & (uint32)(val))

/*! \brief
 * 32 bit Read modify write - bit fields input
 */
#define M_REG_BITS_WRITE32(w_addr, c_ebit, c_sbit, w_valWrite)   \
            M_REG_WRITE32((w_addr), (M_REG_READ32((w_addr)) &\
            (M_MASK((c_ebit), (c_sbit))) |\
            ((M_VAL_BOUND((w_valWrite), (c_ebit), (c_sbit))) << (c_sbit))))

#define M_MEM_BITS_READ16(w_addr, c_ebit, c_sbit)   \
                (((M_MEM_READ16((w_addr))) & (M_ONES((c_ebit), (c_sbit)))) >> (c_sbit))

#define M_MEM_BITS_WRITE16(w_addr, c_ebit, c_sbit, w_valWrite)    \
             M_MEM_WRITE16((w_addr), (M_REG_READ16((w_addr)) &\
            (M_MASK((c_ebit), (c_sbit))) |\
            ((M_VAL_BOUND((w_valWrite), (c_ebit), (c_sbit))) << (c_sbit))))




#define M_ASSERT(test)      do { \
                                    if (FALSE == (uint8)(test)) \
                                    { \
                                        while(TRUE); \
                                    } \
                                } while (FALSE)

/** \brief Attribute */
#if defined(CLANG)
#define MCAL_INTERRUPT_ATTRIBUTE __attribute__((target("arm")))
#else
#define MCAL_INTERRUPT_ATTRIBUTE 
#endif

/** @enum config_value_type
*   @brief config type definition
*/
/** @typedef config_value_type_t
*   @brief config type Type Definition
*
*   This type is used to specify the Initial and Current value.
*/
typedef enum config_value_type
{
    InitialValue,
    CurrentValue
}config_value_type_t;



/** @def GET_BIT_VALUE
*   @brief Get multiple bit values from given location
*/
#define GET_BIT_VALUE(data, noOfBits, location)     ((((uint32)(data)) >> (location)) & (((uint32)((uint32)1U << (noOfBits))) - (uint32)1U))

#define MCAL_SW_DELAY(count)  (count = count - 1 )

#define DMA_CH_MAX  32U
/*
 * MSS VIM Priority Macro List
 */
#define VIM_PRIORITY_2           (2U)
#define VIM_PRIORITY_3           (3U)
#define VIM_PRIORITY_4           (4U)
#define VIM_PRIORITY_5           (5U)
#define VIM_PRIORITY_6           (6U)
#define VIM_PRIORITY_7           (7U)
#define VIM_PRIORITY_8           (8U)
#define VIM_PRIORITY_9           (9U)
#define VIM_PRIORITY_10          (10U)
#define VIM_PRIORITY_11          (11U)
#define VIM_PRIORITY_12          (12U)
#define VIM_PRIORITY_13          (13U)
#define VIM_PRIORITY_14          (14U)
#define VIM_PRIORITY_15          (15U)

/*
 * MSS VIM Interrupt Mapping
 */
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_0      0
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1      1
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_2      2
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_3      3
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_4      4
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_5      5
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_6      6
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_7      7
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_RX_SOF_INTR_REQ_0     8
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_RX_SOF_INTR_REQ_1     9
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_TX_SOF_INTR_REQ_0     10
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_TX_SOF_INTR_REQ_1     11
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_0   12
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_1   13
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_2   14
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_3   15
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_4   16
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_5   17
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_6   18
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_7   19
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_8   20
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_9   21
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_10  22
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_11  23
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_12  24
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_13  25
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_14  26
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_15  27
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_0      28
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_1      29
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_2      30
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_3      31
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_4      32
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_5      33
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_6      34
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_HOST_INTR_PEND_7      35
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_RX_SOF_INTR_REQ_0     36
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_RX_SOF_INTR_REQ_1     37
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_TX_SOF_INTR_REQ_0     38
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_TX_SOF_INTR_REQ_1     39
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_0   40
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_1   41
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_2   42
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_3   43
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_4   44
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_5   45
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_6   46
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_7   47
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_8   48
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_9   49
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_10  50
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_11  51
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_12  52
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_13  53
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_14  54
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM1_PR1_IEP0_CMP_INTR_REQ_15  55
#define  CPSW_FH_INT                                                 56
#define  CPSW_TH_INT                                                 57
#define  CPSW_TH_THRESH_INT                                          58
#define  CPSW_MISC_INT                                               59
#define  CPSW_CPTS_COMP                                              60
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_LIN0_INTR_0                          61
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_LIN0_INTR_1                          62
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_LIN1_INTR_0                          63
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_LIN1_INTR_1                          64
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_LIN2_INTR_0                          65
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_LIN2_INTR_1                          66
#define  MCAN0_ROLLOVER_LVL_INT_0                                    67
#define  MCAN0_MCAN_LVL_INT_0                                        68
#define  MCAN0_MCAN_LVL_INT_1                                        69
#define  MCAN1_ROLLOVER_LVL_INT_0                                    70
#define  MCAN1_MCAN_LVL_INT_0                                        71
#define  MCAN1_MCAN_LVL_INT_1                                        72
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_UART0_IRQ                            73
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_UART1_IRQ                            74
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_UART2_IRQ                            75
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_UART3_IRQ                            76
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_UART4_IRQ                            77
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_UART5_IRQ                            78
#define  I2C0_IRQ                                                    79
#define  I2C1_IRQ                                                    80
#define  I2C2_IRQ                                                    81
#define  DTHE_SHA_S_INT                                              82
#define  DTHE_SHA_P_INT                                              83
#define  DTHE_TRNG_INT                                               84
#define  DTHE_PKEV4_INT                                              85
#define  DTHE_AES_S_INT                                              86
#define  DTHE_AES_P_INT                                              87
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_OSPI0_INT                            88
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTG                           89
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_0                          90
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_1                          91
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_2                          92
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_3                          93
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_4                          94
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_5                          95
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_6                          96
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_7                          97
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_ERRINT                         98
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_MPINT                          99
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPTC0_ERINT_0                        100
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPTC0_ERINT_1                        101
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MCRC0_INT                            102
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MPU_ADDR_ERRAGG                      103
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MPU_PROT_ERRAGG                      104
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_PBIST_DONE                           105
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTAGGR                        106
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_ERRAGGR                        107
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_DCC0_DONE                            108
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_DCC1_DONE                            109
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_DCC2_DONE                            110
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_DCC3_DONE                            111
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI0_INTR                          112
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR                          113
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI2_INTR                          114
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI3_INTR                          115
#define  MCAL_CSLR_USB20_MAIN0_INT                                        116
#define  MCAL_CSLR_USB20_MAIN1_INT                                        117
#define  MCAL_CSLR_USB20_MAIN2_INT                                        118
#define  MCAL_CSLR_USB20_MAIN3_INT                                        119
#define  MCAL_CSLR_USB20_MISC_INT                                         120
#define  MCAL_CSLR_USB20_PHY_WAKEUP_WUOUT                                 121
#define  MCAL_CSLR_USB20_SLVP_SWAKEUP                                     122
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MMC0_INTR                            123
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_0                          124
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_1                          125
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_2                          126
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_3                          127
#define  RTI0_OVERFLOW_INT0                                          128
#define  RTI0_OVERFLOW_INT1                                          129
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_0                          130
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_1                          131
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_2                          132
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_3                          133
#define  RTI1_OVERFLOW_INT0                                          134
#define  RTI1_OVERFLOW_INT1                                          135
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_0                          136
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_1                          137
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_2                          138
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_3                          139
#define  RTI2_OVERFLOW_INT0                                          140
#define  RTI2_OVERFLOW_INT1                                          141
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_0                          142
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_1                          143
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_2                          144
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_3                          145
#define  RTI3_OVERFLOW_INT0                                          146
#define  RTI3_OVERFLOW_INT1                                          147
#define  ESM_INT_CFG                                                 148
#define  ESM_INT_HI                                                  149
#define  ESM_INT_LO                                                  150
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_ERRPIN_MON_LVL_INTR                  151
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MMR_ACC_ERRAGG                       152
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_SW_IRQ                               153
#define  RTI_WDT0_NMI                                                154
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_DEBUGSS_TXDATA_AVAIL                 155
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TSENSE_H                             156
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_TSENSE_L                             157
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MBOX_READ_REQ                        158
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_MBOX_READ_ACK                        159
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_2              160
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_3              161
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_4              162
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_5              163
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_14                 164
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_15                 165
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_16                 166
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_17                 167
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_0                 168
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_1                 169
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_2                 170
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_3                 171
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_4                 172
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_5                 173
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_6                 174
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_7                 175
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_8                 176
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_9                 177
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_10                178
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_11                179
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_12                180
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_13                181
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_14                182
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_15                183
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_16                184
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_17                185
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_18                186
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_19                187
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_20                188
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_21                189
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_22                190
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_23                191
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_24                192
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_25                193
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_26                194
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_27                195
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_28                196
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_29                197
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_30                198
#define  MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_31                199
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_FSS_VBUSM_TIMEOUT                    200
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_OTFA_ERROR                           201
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_FOTA_STAT_INTR                  	 202
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_FOTA_STAT_ERR_INTR	                 203
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_COMMRX_0                       204
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_COMMTX_0                       205
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_CTI_INT                   206
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU1_CTI_INT                   207
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_VALFIQ                    208
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_VALIRQ                    209
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_LIVELOCK_1                     210
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS1_LIVELOCK_1                     211
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CORE0_FPU_EXP                  212
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_AHB_WRITE_ERR                        213
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_RL2_ERR_INTR              214
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU1_RL2_ERR_INTR              215
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_TMU_LVF                   216
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_TMU_LUF                   217
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_PMU_INT                   218
#define  MCAL_CSLR_R5FSS0_CORE0_GPMC_SINTR                                219
#define  MCAL_CSLR_R5FSS0_CORE0_ELM_SINTR                                 220
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_OSPI1_INT                            221
#define  MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU1_PMU_INT                   222

/**
 * \brief Return status when the API execution was successful
 */
#define MCAL_SystemP_SUCCESS   ((sint32 )0)

/**
 * \brief Return status when the API execution was not successful due to a failure
 */
#define MCAL_SystemP_FAILURE   ((sint32)-1)

/**
 * \brief Return status when the API execution failed due to a time out
 */
#define MCAL_SystemP_TIMEOUT   ((sint32)-2)

/**
 * \brief Return status when the API execution failed due invalid parameters
 */
#define MCAL_SystemP_INVALID_PARAM   ((sint32)-3)

/**
 * \brief Value to use when needing a timeout of infinity or wait forver until resource is available
 */
#define MCAL_SystemP_WAIT_FOREVER   ((uint32)-1)

/**
 * \brief Return status when the API execution failed due to driver busy
 */
#define MCAL_SystemP_BUSY   ((sint32)-4)

/**
 * \brief Return status when the API execution failed due to invalid LLD state
 */
#define MCAL_SystemP_INVALID_STATE  ((sint32)-5)

#define MCAL_LLD_PARAM_CHECK_ENABLED
#ifdef MCAL_LLD_PARAM_CHECK_ENABLED
#ifdef MCAL_LLD_PARAM_CHECK_DEBUG_ASSERT
static inline void MCAL_Param_check_lld(sint32 expression, const sint8 *file, const sint8 *function, sint32 line, const sint8 *expressionString);

static inline void MCAL_Param_check_lld(sint32 expression, const sint8 *file, const sint8 *function, sint32 line, const sint8 *expressionString)
{

    _DebugP_assert(expression, file, function, line, expressionString);
}
#define MCAL_LLD_PARAMS_CHECK(expression) MCAL_Param_check_lld(expression, \
            __FILE__, __FUNCTION__, __LINE__, #expression)
#else
#define MCAL_LLD_PARAMS_CHECK(expression) \
if (status == MCAL_SystemP_SUCCESS) { \
    if(!(expression)) { \
        status = MCAL_SystemP_INVALID_PARAM; \
    } \
}
#endif /*! MCAL_LLD_PARAM_CHECK_DEBUG_ASSERT */
#else
#define MCAL_LLD_PARAMS_CHECK(expression)
#endif /*! MCAL_LLD_PARAM_CHECK_ENABLED */

#ifndef MCAL_DYNAMIC_BUILD
/** @fn uint32 regWriteReadback(volatile uint32 *regAddr, uint32 endBit, uint32 startBit, uint32 wrValue)
*   @brief Write a register and Readback function
*   @return error flag
*
*   This function writes a register and reads back and compares the written values
*/
/* SourceId :  */
/* DesignId :  */
/* Requirements :  */
static inline uint32 registerReadWrite_local(volatile uint32 *regAddr, uint32 endBit, \
                              uint32 startBit, uint32 wrValue)
{
    uint32 readVal = 0U;
    uint32 wrStatus = 0U;
    uint32 maskedWrValue;
    uint32 maskVal = 0U;
    uint32 boundVal = 0U;


    if ((endBit == 31U) && (startBit == 0U))
    {
        /* Write */
        M_REG_WRITE32(regAddr, wrValue);

        /* Read Back */
        readVal = M_REG_READ32(regAddr);

        /* Set Status */
        wrStatus = readVal ^ wrValue;
    }
    else
    {
        /* Read Register */
        readVal = M_REG_READ32(regAddr);
        maskVal = M_MASK(endBit, startBit);
        boundVal = (uint32)M_VAL_BOUND(wrValue, endBit, startBit);
        maskedWrValue = (readVal & maskVal) | (boundVal << startBit);
        /* Write */
        M_REG_WRITE32(regAddr, maskedWrValue);

/*LDRA_INSPECTED 87 S : MISRAC_2012_R18.4
 * "Reason - Safety feature readback option of the register" */
        readVal = (uint32)M_REG_BITS_READ32(regAddr, endBit, startBit);

        /* Set Status */
        wrStatus = readVal ^ wrValue;

    }

    return wrStatus;
}
#else
uint32 registerReadWrite_local(volatile uint32 *regAddr, uint32 endBit, \
                              uint32 startBit, uint32 wrValue);
#endif

#define regWriteReadback(reg, end, start, wr) \
        ((uint32)(registerReadWrite_local((volatile uint32 *)reg, (uint32) end, \
                              (uint32) start, (uint32) wr)))


#ifdef __cplusplus
}
#endif




#endif /* SYS_COMMON_H */

