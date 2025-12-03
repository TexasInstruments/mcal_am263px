
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

#define MCAL_SW_DELAY(count)  (count = count - 1U )

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
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_0      (0U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_1      (1U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_2      (2U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_3      (3U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_4      (4U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_5      (5U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_6      (6U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_HOST_INTR_PEND_7      (7U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_RX_SOF_INTR_REQ_0     (8U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_RX_SOF_INTR_REQ_1     (9U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_TX_SOF_INTR_REQ_0     (10U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_TX_SOF_INTR_REQ_1     (11U)
#define CPSW_FH_INT                                                 (12U)      /* CPSW T-host threshold interrupt                                                        */
#define CPSW_TH_INT                                                 (13U)      /* CPSW T-host interrupt                                                     */
#define CPSW_TH_TRSH_INT                                            (14U)      /* CPSW F-host interrupt  */
#define CPSW_MISC_INT                                               (15U)      /* MCAL_CSLR_R5FSS0_CORE0_INTR_CPSW0_MISC_INTR interrupt  */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN0_INTR_0                          (16U)      /* LIN0 Interrupt 0 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN0_INTR_1                          (17U)      /* LIN0 Interrupt 1 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN1_INTR_0                          (18U)      /* LIN1 Interrupt 0 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN1_INTR_1                          (19U)      /* LIN1 Interrupt 1 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN2_INTR_0                          (20U)      /* LIN2 Interrupt 0 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN2_INTR_1                          (21U)      /* LIN2 Interrupt 1 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN3_INTR_0                          (22U)      /* LIN3 Interrupt 0 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN3_INTR_1                          (23U)      /* LIN3 Interrupt 1 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN4_INTR_0                          (24U)      /* LIN4 Interrupt 0 */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_LIN4_INTR_1                          (25U)      /* LIN4 Interrupt 1 */
#define MCAN0_ROLLOVER_LVL_INT_0                                    (26U)      /* MCAN0 External TS RollOver Interrupt                                          */
#define MCAN0_MCAN_LVL_INT_0                                        (27U)      /* MCAN0 Level Interrupt 0                                                       */
#define MCAN0_MCAN_LVL_INT_1                                        (28U)      /* MCAN0 Level Interrupt 1                                                       */
#define MCAN1_ROLLOVER_LVL_INT_0                                    (29U)      /* MCAN1 External TS RollOver Interrupt                                          */
#define MCAN1_MCAN_LVL_INT_0                                        (30U)      /* MCAN1 Level Interrupt 0                                                       */
#define MCAN1_MCAN_LVL_INT_1                                        (31U)      /* MCAN1 Level Interrupt 1                                                       */
#define MCAN2_ROLLOVER_LVL_INT_0                                    (32U)      /* MCAN2 External TS RollOver Interrupt                                          */
#define MCAN2_MCAN_LVL_INT_0                                        (33U)      /* MCAN2 Level Interrupt 0                                                       */
#define MCAN2_MCAN_LVL_INT_1                                        (34U)      /* MCAN2 Level Interrupt 1                                                       */
#define MCAN3_ROLLOVER_LVL_INT_0                                    (35U)      /* MCAN3 External TS RollOver Interrupt                                          */
#define MCAN3_MCAN_LVL_INT_0                                        (36U)      /* MCAN3 Level Interrupt 0                                                       */
#define MCAN3_MCAN_LVL_INT_1                                        (37U)      /* MCAN3 Level Interrupt 1                                                       */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_UART0_IRQ                            (38U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_UART1_IRQ                            (39U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_UART2_IRQ                            (40U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_UART3_IRQ                            (41U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_UART4_IRQ                            (42U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_UART5_IRQ                            (43U)
#define I2C0_INT                	                                (44U)      /* MSS_I2C interrupt															*/
#define I2C1_INT                	                	            (45U)      /* MSS_I2C interrupt															*/
#define I2C2_INT                 	                 	            (46U)      /* MSS_I2C interrupt															*/
#define I2C3_INT                                                	(47U)      /* MSS_I2C interrupt                                                            */
#define DTHE_SHA_S_INT                                              (48U)     /* Interrupt from HSM_SHA                                                        */
#define DTHE_SHA_P_INT                                              (49U)     /* Interrupt from HSM_SHA                                                        */
#define DTHE_TRNG_INT                                               (50U)     /* Interrupt from HSM_TRNG                                                       */
#define DTHE_PKAE_INT                                               (51U)     /* Interrupt from HSM_PKAE                                                       */
#define DTHE_AES_S_INT                                              (52U)     /* Interrupt from HSM_AES                                                        */
#define DTHE_AES_P_INT                                              (53U)     /* Interrupt from HSM_AES    */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_OSPI0_INT                            54
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTG                           55
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_0                          56
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_1                          57
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_2                          58
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_3                          59
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_4                          60
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_5                          61
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_6                          62
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INT_7                          63
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_ERRINT                         64
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_MPINT                          65
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPTC0_ERINT_0                        66
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPTC0_ERINT_1                        67
#define DSS_MCRC_INT                                                (68U)     /* MCAL_CSLR_R5FSS0_CORE0_INTR_MCRC0_INT Interrupt                                                            */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MPU_ADDR_ERRAGG                      69
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MPU_PROT_ERRAGG                      70
#define DSS_DSP_PBIST_DONE                                          (71U)     /* PBIST Done Interrupt                                                  */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_INTAGGR                        (72U)  /* EDMA Interrupt Aggregation */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TPCC0_ERRAGGR                        (73U)  /* EDMA Error Aggregation */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_DCC0_DONE                            (74U)      /* DCC0 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_DCC1_DONE                            (75U)      /* DCC1 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_DCC2_DONE                            (76U)      /* DCC2 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_DCC3_DONE                            (77U)      /* DCC3 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI0_INTR                          (78U)    /* MCSPI0 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI1_INTR                          (79U)    /* MCSPI1 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI2_INTR                          (80U)    /* MCSPI2 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI3_INTR                          (81U)    /* MCSPI3 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI4_INTR                          (82U)    /* MCSPI4 Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MMC0_INTR                            83
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_0                           (84U)       /* RTI0 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_1                           (85U)       /* RTI0 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_2                           (86U)       /* RTI0 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI0_INTR_3                           (87U)       /* RTI0 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RESERVED88                           88
#define RTI0_OVERFLOW_INT0                                          (89U)       /* RTI0 overflow interrupt                                                       */
#define RTI0_OVERFLOW_INT1                                          (90U)       /* RTI0 overflow interrupt                                                       */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_0                (91U)       /* RTI1 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_1                (92U)       /* RTI1 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_2                (93U)       /* RTI1 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI1_INTR_3                (94U)       /* RTI1 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RESERVED95                           95
#define RTI1_OVERFLOW_INT0                                          (96U)       /* RTI1 overflow interrupt                                                       */
#define RTI1_OVERFLOW_INT1                                          (97U)       /* RTI1 overflow interrupt                                                       */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_0                                                   (98U)       /* RTI2 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_1                                                   (99U)       /* RTI2 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_2                                                   (100U)       /* RTI2 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI2_INTR_3                                                   (101U)       /* RTI2 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RESERVED102                          102
#define RTI2_OVERFLOW_INT0                                          (103U)       /* RTI2 overflow interrupt                                                       */
#define RTI2_OVERFLOW_INT1                                          (104U)       /* RTI2 overflow interrupt                                                       */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_0                                                   (105U)       /* RTI3 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_1                                                   (106U)       /* RTI3 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_2                                                   (107U)       /* RTI3 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI3_INTR_3                                                   (108U)       /* RTI3 compare interrupt                                                        */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RESERVED109                          109
#define RTI3_OVERFLOW_INT0                                          (110U)       /* RTI3 overflow interrupt                                                       */
#define RTI3_OVERFLOW_INT1                                          (111U)       /* RTI3 overflow interrupt                                                       */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RESERVED112                          112
#define ESM_INT_CFG                                                 (113U)  /* MCAL_CSLR_R5FSS0_CORE0_INTR_ESM0_ESM_INT_CFG*/
#define MSS_ESM_HI                                                  (114U)     /* MCAL_CSLR_R5FSS0_CORE0_INTR_ESM0_ESM_INT_HI ESM High Priority Interrupt                                                   */
#define MSS_ESM_LO                                                  (115U)     /* MCAL_CSLR_R5FSS0_CORE0_INTR_ESM0_ESM_INT_LOW ESM Low Priority Interrupt                                                    */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_COMMRX_0                       (116U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_COMMTX_0                       (117U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_CTI_INT                   (118U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_VALFIQ                    (119U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_VALIRQ                    (120U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU1_CTI_INT                   (121U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS1_CPU0_PMU_INT                   (122U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS1_CPU1_PMU_INT                   (123U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MMR_ACC_ERRAGG                       (124U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_LIVELOCK_1                     (125U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS1_LIVELOCK_0                     (126U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS1_LIVELOCK_1                     (127U)
#define RTI_WDT0_NMI                                                (128U)
#define MSS_SW_INT0                                                 (129U)      /* Software Interrupt from MSS_CTRL                                              */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CORE0_FPU_EXP                  (130U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_DEBUGSS_TXDATA_AVAIL                 (131U)
#define CR5SS_STC_DONE                                              (132U)     /* Cortexr5ss subsystem STC complete interrupt                                   */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TSENSE_H                             (133U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_TSENSE_L                             (134U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_AHB_WRITE_ERR                        (135U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MBOX_READ_REQ                        (136U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MBOX_READ_ACK                        (137U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_2              (138U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_3              (139U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_4              (140U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_SOC_TIMESYNCXBAR1_OUT_5              (141U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_14                 (142U)     /* GPIO XBAR Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_15                 (143U)     /* GPIO XBAR Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_16                 (144U)     /* GPIO XBAR Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_INTR_GPIO_INTRXBAR_OUT_17                 (145U)     /* GPIO XBAR Interrupt */
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_0                 (146U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_1                 (147U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_2                 (148U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_3                 (149U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_4                 (150U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_5                 (151U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_6                 (152U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_7                 (153U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_8                 (154U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_9                 (155U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_10                (156U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_11                (157U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_12                (158U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_13                (159U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_14                (160U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_15                (161U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_16                (162U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_17                (163U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_18                (164U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_19                (165U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_20                (166U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_21                (167U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_22                (168U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_23                (169U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_24                (170U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_25                (171U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_26                (172U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_27                (173U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_28                (174U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_29                (175U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_30                (176U)
#define MCAL_CSLR_R5FSS0_CORE0_CONTROLSS_INTRXBAR0_OUT_31                (177U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_0   (178U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_1   (179U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_2   (180U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_3   (181U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_4   (182U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_5   (183U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_6   (184U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_7   (185U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_8   (186U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_9   (187U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_10  (188U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_11  (189U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_12  (190U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_13  (191U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_14  (192U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_PRU_ICSSM0_PR1_IEP0_CMP_INTR_REQ_15  (193U)
#define MCAL_CSLR_R5FSS0_CORE0_CPSW0_CPTS_COMP                           (194U)
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RESERVED195                          195
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RESERVED196                          196
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN4_EXT_TS_ROLLOVER_LVL_INT_0      197
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN4_MCAN_LVL_INT_0                 198
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN4_MCAN_LVL_INT_1                 199
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN5_EXT_TS_ROLLOVER_LVL_INT_0      200
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN5_MCAN_LVL_INT_0                 201
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN5_MCAN_LVL_INT_1                 202
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN6_EXT_TS_ROLLOVER_LVL_INT_0      203
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN6_MCAN_LVL_INT_0                 204
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN6_MCAN_LVL_INT_1                 205
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN7_EXT_TS_ROLLOVER_LVL_INT_0      206
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN7_MCAN_LVL_INT_0                 207
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCAN7_MCAN_LVL_INT_1                 208
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_TMU_LVF                   209
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_TMU_LUF                   210
#define MCAL_CSLR_R5FSS0_CORE0_INTR_HW_RESOLVER_INTR                     211
#define MCAL_CSLR_R5FSS0_CORE0_INTR_FSS_VBUSM_TIMEOUT                    212
#define MCAL_CSLR_R5FSS0_CORE0_INTR_OTFA_ERROR                           213
#define MCAL_CSLR_R5FSS0_CORE0_INTR_FOTA_STAT_INTR                  	 214
#define MCAL_CSLR_R5FSS0_CORE0_INTR_FOTA_STAT_ERR_INTR	                 215
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI5_INTR                          216
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI6_INTR                          217
#define MCAL_CSLR_R5FSS0_CORE0_INTR_MCSPI7_INTR                          218
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI4_INTR_0                          219
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI4_INTR_1                          220
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI4_INTR_2                          221
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI4_INTR_3                          222
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI4_OVERFLOW_INT0                   223
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI4_OVERFLOW_INT1                   224
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI5_INTR_0                          225
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI5_INTR_1                          226
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI5_INTR_2                          227
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI5_INTR_3                          228
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI5_OVERFLOW_INT0                   229
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI5_OVERFLOW_INT1                   230
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI6_INTR_0                          231
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI6_INTR_1                          232
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI6_INTR_2                          233
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI6_INTR_3                          234
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI6_OVERFLOW_INT0                   235
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI6_OVERFLOW_INT1                   236
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI7_INTR_0                          237
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI7_INTR_1                          238
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI7_INTR_2                          239
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI7_INTR_3                          240
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI7_OVERFLOW_INT0                   241
#define MCAL_CSLR_R5FSS0_CORE0_INTR_RTI7_OVERFLOW_INT1                   242
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU0_RL2_ERR_INTR              243
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS0_CPU1_RL2_ERR_INTR              244
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS1_CPU0_RL2_ERR_INTR              245
#define MCAL_CSLR_R5FSS0_CORE0_INTR_R5SS1_CPU1_RL2_ERR_INTR              246

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

