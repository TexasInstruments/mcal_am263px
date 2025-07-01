
/*
* Copyright (C) 2022 Texas Instruments Incorporated - TI web adress www.ti.com
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
/*LDRA_NOANALYSIS*/
#include <stdbool.h>
#include "Platform_Types.h"
#include "mcal_hw_soc_defines.h"
/*LDRA_ANALYSIS*/

#ifdef __cplusplus
extern "C" {
#endif

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
 * DMA Channel Mapping
 */
#define SPIA_RX_DMA_CH         (DMA_CH0 )    /* DMA Channel for SPI-A RX                   */
#define SPIA_TX_DMA_CH         (DMA_CH1 )    /* DMA Channel for SPI-A TX                   */
#define BSS_MSS_MB_CH          (DMA_CH2 )    /* DMA Channel for BSS-MSS MailBox            */
#define MSS_BSS_MB_CH          (DMA_CH3 )    /* DMA Channel for MSS-BSS MailBox            */
#define DSS_MSS_MB_CH          (DMA_CH4 )    /* DMA Channel for DSS-MSS Mailbox            */
#define MSS_DSS_MB_CH          (DMA_CH5 )    /* DMA Channel for DSS-MSS Mailbox            */
#define SCIA_RX_DMA_CH         (DMA_CH6 )    /* DMA Channel for SCI-A (UART) RX            */
#define SCIA_TX_DMA_CH         (DMA_CH7 )    /* DMA Channel for SCI-A (UART) TX            */
#define QSPI_TX_DMA_CH         (DMA_CH8 )    /* DMA Channel for QSPI TX                    */
#define QSPI_RX_DMA_CH         (DMA_CH9 )    /* DMA Channel for QSPI RX                    */
#define MEM_TX_DMA_CH          (DMA_CH10)    /* DMA Channel for Mem to Mem Transfer        */
#define SCIB_TX_DMA_CH         (DMA_CH11)    /* DMA Channel for SCI-B (UART) TX            */
#define MCRC_CH1_DMA_CH        (DMA_CH12)    /* DMA Channel for mCRC channel-1             */
#define MCRC_CH2_DMA_CH        (DMA_CH13)    /* DMA Channel for mCRC channel-2             */
#define SPIB_RX_DMA_CH         (DMA_CH14)    /* DMA Channel for SPI-B RX                   */
#define SPIB_TX_DMA_CH         (DMA_CH15)    /* DMA Channel for SPI-B TX                   */
#define MEM_TEST_TX_DMA_CH     (DMA_CH16)    /* DMA Channel for Safety Tests Mem to Mem Tr */

/*
 * DMA Request Line Mapping
 */
#define SPIA_RX_DMA_REQ          (0U)   /* SPI-A RX DMA Request Line                            */
#define SPIA_TX_DMA_REQ          (1U)   /* SPI-A TX DMA Request Line                            */
#define SPIB_RX_DMA_REQ          (2U)   /* SPI-B RX DMA Request Line                            */
#define SPIB_TX_DMA_REQ          (3U)   /* SPI-B TX DMA Request Line                            */
#define QSPI_DMA_REQ             (4U)   /* QSPI DMA Request Line                                */
#define I2C_RX_DMA_REQ           (10U)  /* Channel ID for I2C RX DMA Request                    */
#define I2C_TX_DMA_REQ           (11U)  /* Channel ID for I2C TX DMA Request                    */
#define RTI_COM0_DMA_REQ         (12U)  /* RTI DMA request  for Compare 0                       */
#define RTI_COM1_DMA_REQ         (13U)  /* RTI DMA request  for Compare 1                       */
#define RTI_COM2_DMA_REQ         (18U)  /* RTI DMA request for Compare 2                        */
#define RTI_COM3_DMA_REQ         (19U)  /* RTI DMA request for Compare 3                        */
#define WDT_DMA_REQ0             (20U)  /* WatchDog DMA Request 0                               */
#define WDT_DMA_REQ1             (21U)  /* WatchDog DMA Request 1                               */
#define WDT_DMA_REQ2             (24U)  /* WatchDog DMA Request 2                               */
#define WDT_DMA_REQ3             (25U)  /* WatchDog DMA Request 3                               */
#define CRC_CH1_DMA_REQ          (26U)  /* MCRC DMA Request For Channel 1                       */
#define CRC_CH2_DMA_REQ          (27U)  /* MCRC DMA Request For Channel 2                       */
#define SCIB_RX_DMA_REQ          (28U)  /* Channel ID for SCI2-B RX DMA Request                 */
#define SCIB_TX_DMA_REQ          (29U)  /* Channel ID for SCI-B TX DMA Request                  */
#define SCIA_RX_DMA_REQ          (30U)  /* Channel ID for SCI-A RX DMA Request                  */
#define SCIA_TX_DMA_REQ          (31U)  /* Channel ID for SCI-A TX DMA Request                  */

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
#define MSS_ESM_HI                  (0U)       /* ESM High Priority Interrupt                                                   */
#define MSS_ESM_LO                  (1U)       /* ESM Low Priority Interrupt                                                    */
#define CR5SS_STC_DONE              (2U)       /* Cortexr5ss subsystem STC complete interrupt                                   */
#define MSS_RTIA_INT0               (3U)       /* RTIA compare interrupt                                                        */
#define MSS_RTIA_INT1               (4U)       /* RTIA compare interrupt                                                        */
#define MSS_RTIA_INT2               (5U)       /* RTIA compare interrupt                                                        */
#define MSS_RTIA_INT3               (6U)       /* RTIA compare interrupt                                                        */
#define MSS_RTIA_OVERFLOW_INT0      (7U)       /* RTIA overflow interrupt                                                       */
#define MSS_RTIA_OVERFLOW_INT1      (8U)       /* RTIA overflow interrupt                                                       */
#define MSS_RTIB_INT0               (9U)       /* RTIB compare interrupt                                                        */
#define MSS_RTIB_INT1               (10U)      /* RTIB compare interrupt                                                        */
#define MSS_RTIB_OVERFLOW_INT0      (11U)      /* RTIB overflow interrupt                                                       */
#define MSS_RTIB_OVERFLOW_INT1      (12U)      /* RTIB overflow interrupt                                                       */
#define MSS_RTIC_INT0               (13U)      /* RTIC compare interrupt                                                        */
#define MSS_RTIC_INT1               (14U)      /* RTIC compare interrupt                                                        */
#define MSS_RTIC_OVERFLOW_INT0      (15U)      /* RTIC overflow interrupt                                                       */
#define MSS_RTIC_OVERFLOW_INT1      (16U)      /* RTIC overflow interrupt                                                       */
#define MSS_WDT_INT0                (17U)      /* WDT compare interrupt                                                         */
#define MSS_WDT_INT1                (18U)      /* WDT compare interrupt                                                         */
#define MSS_WDT_INT2                (19U)      /* WDT compare interrupt                                                         */
#define MSS_WDT_INT3                (20U)      /* WDT compare interrupt                                                         */
#define MSS_WDT_OVERFLOW_INT0       (21U)      /* WDT over flow interrupt                                                       */
#define MSS_WDT_OVERFLOW_INT1       (22U)      /* WDT over flow interrupt                                                       */
#define MSS_WDT_TB_INT              (23U)      /* WDT time base interrupt                                                       */
#define MSS_MCRC_INT                (24U)      /* Interrupt from MCRC                                                           */
#define MSS_DCCA_INT                (25U)      /* MSS_DCCA Clock compare done interrupt                                         */
#define MSS_DCCB_INT                (26U)      /* MSS_DCCB  Clock compare done interrupt                                        */
#define MSS_DCCC_INT                (27U)      /* MSS_DCCC  Clock compare done interrupt                                        */
#define MSS_DCCD_INT                (28U)      /* MSS_DCCD  Clock compare done interrupt                                        */
#define MSS_CCCA_INT                (29U)      /* MSS_CCCA dual clock compare done interrupt                                    */
#define MSS_CCCB_INT                (30U)      /* MSS_CCCB dual clock compare done interrupt                                    */
#define MSS_SPIA_INT0               (31U)      /* MSS_SPIA level 0 interrupt                                                    */
#define MSS_SPIA_INT1               (32U)      /* MSS_SPIA level 1 interrupt                                                    */
#define MSS_SPIB_INT0               (33U)      /* MSS_SPIB level 0 interrupt                                                    */
#define MSS_SPIB_INT1               (34U)      /* MSS_SPIB level 1 interrupt                                                    */
#define MSS_QSPI_INT                (35U)      /* MSS_QSPI interrupt                                                            */
#define MSS_GIO_INT0                (36U)      /* MSS_GIO high-level Interrupt                                                  */
#define MSS_GIO_INT1                (37U)      /* MSS_GIO low-level interrupt                                                   */
#define MSS_ETPWMA_INT0             (38U)      /* MSS_ETPWMA Interrupt  0 which is a output to pad                              */
#define MSS_ETPWMA_INT1             (39U)      /* MSS_ETPWMA Interrupt  1 which is a output to pad                              */
#define MSS_ETPWMB_INT0             (40U)      /* MSS_ETPWMB Interrupt  0 which is a output to pad                              */
#define MSS_ETPWMB_INT1             (41U)      /* MSS_ETPWMB Interrupt  1 which is a output to pad                              */
#define MSS_ETPWMC_INT0             (42U)      /* MSS_ETPWMC Interrupt  0 which is a output to pad                              */
#define MSS_ETPWMC_INT1             (43U)      /* MSS_ETPWMC Interrupt  1 which is a output to pad                              */
#define MSS_MCANA_INT0              (44U)      /* MSS_MCANA first interrupt                                                     */
#define MSS_MCANA_INT1              (45U)      /* MSS_MCANA second interrupt                                                    */
#define MSS_MCANA_FE_INT1           (46U)      /* MSS_MCANA message filter interrupt1                                           */
#define MSS_MCANA_FE_INT2           (47U)      /* MSS_MCANA message filter interrupt2                                           */
#define MSS_MCANB_INT0              (48U)      /* MSS_MCANB first interrupt                                                     */
#define MSS_MCANB_INT1              (49U)      /* MSS_MCANB second interrupt                                                    */
#define MSS_MCANB_FE_INT1           (50U)      /* MSS_MCANB message filter interrupt1                                           */
#define MSS_MCANB_FE_INT2           (51U)      /* MSS_MCANB message filter interrupt2                                           */
#define MSS_I2C_INT                 (52U)      /* MSS_I2C interrupt                                                             */
#define MSS_SCIA_INT0               (53U)      /* MSS_SCIA level0 input                                                         */
#define MSS_SCIA_INT1               (54U)      /* MSS_SCIA level1 input                                                         */
#define MSS_SCIB_INT0               (55U)      /* MSS_SCIB level0 input                                                         */
#define MSS_SCIB_INT1               (56U)      /* MSS_SCIB level1 input                                                         */
#define TOP_PBIST_DONE_INT          (57U)      /* TOP_PBIST done interrupt                                                      */
#define MSS_GIO_PAD_INT0            (58U)      /* Interrupt Triger from GIO[0][0]                                               */
#define MSS_GIO_PAD_INT1            (59U)      /* Interrupt Triger from GIO[0][1]                                               */
#define MSS_GIO_PAD_INT2            (60U)      /* Interrupt Triger from GIO[0][2]                                               */
#define MSS_GIO_PAD_INT3            (61U)      /* Interrupt Triger from GIO[0][3]                                               */
#define MSS_MCANA_FE_INT3           (62U)      /* MSS_MCANA message filter interrupt3                                           */
#define MSS_MCANA_FE_INT4           (63U)      /* MSS_MCANA message filter interrupt4                                           */
#define MSS_MCANA_FE_INT5           (64U)      /* MSS_MCANB message filter interrupt5                                           */
#define MSS_MCANA_FE_INT6           (65U)      /* MSS_MCANA message filter interrupt6                                           */
#define MSS_MCANA_FE_INT7           (66U)      /* MSS_MCANB message filter interrupt7                                           */
#define MSS_TPCC_A_INTAGG           (67U)      /* MSS_TPCC_A Aggregated Functional Interrupt                                    */
#define MSS_TPCC_B_INTAGG           (68U)      /* MSS_TPCC_B Aggregated Functional Interrupt                                    */
#define MSS_TPCC_A_ERRAGG           (69U)      /* MSS_TPCC_A Agregated Error Interrupt                                          */
#define MSS_TPCC_B_ERRAGG           (70U)      /* MSS_TPCC_B Agregated Error Interrupt                                          */
#define MSS_GPADC_IFM_DONE          (71U)      /* MSS_GPADC ifm done interrupt                                                  */
#define MSS_CPSW_TH_TRSH_INT        (72U)      /* MSS CPSW T-host threshold interrupt                                           */
#define MSS_CPSW_TH_INT             (73U)      /* MSS CPSW T-host interrupt                                                     */
#define MSS_CPSW_FH_INT             (74U)      /* MSS CPSW F-host interrupt                                                     */
#define MSS_CPSW_MISC_INT           (75U)      /* MSS CPSW interrupt                                                            */
#define MSS_GPADC_CTM_DONE          (76U)      /* GPADC CTM done interrupt                                                      */
#define MSS_CR5A_MBOX_RD_REQ      (77U)      /* Aggregated interrupt to MSS CR5A from other processor asking it to read       */
#define MSS_CR5A_MBOX_RD_ACK      (78U)      /* Aggregated interrupt to MSS CR5A from other processor, read from MBOX is done */
#define MSS_CR5B_MBOX_RD_REQ      (79U)      /* Aggregated interrupt to MSS CR5B from other processor asking it to read       */
#define MSS_CR5B_MBOX_RD_ACK      (80U)      /* Aggregated interrupt to MSS CR5B from other processor, read from MBOX is done */
#define TOP_DEBUGSS_TXDATA_AVAIL    (82U)      /* Interrupt from TOP_DEBUGSS                                                    */
#define MSS_CR5A_PMU_INT            (83U)      /* Pmu Interrupt from MSS_CR5A                                                   */
#define MSS_CR5B_PMU_INT            (84U)      /* Pmu Interrupt from MSS_CR5B                                                   */
#define MSS_CR5A_FPU_INT            (85U)      /* Floating point expection from MSS_CR5A                                        */
#define MSS_CR5B_FPU_INT            (86U)      /* Floating point expection from MSS_CR5B                                        */
#define CR5A_CTI_IRQ                (88U)      /* IRQ request from CTI module from CR5A                                         */
#define CR5B_CTI_IRQ                (89U)      /* IRQ request from CTI module from CR5B                                         */
#define MSS_SW_INT0                 (91U)      /* Software Interrupt from MSS_CTRL                                              */
#define MSS_SW_INT1                 (92U)      /* Software Interrupt from MSS_CTRL                                              */
#define MSS_SW_INT2                 (93U)      /* Software Interrupt from MSS_CTRL                                              */
#define MSS_SW_INT3                 (94U)      /* Software Interrupt from MSS_CTRL                                              */
#define MSS_SW_INT4                 (95U)      /* Software Interrupt from MSS_CTRL                                              */
#define MSS_PERIPH_ACCESS_ERRAGG    (97U)      /* Aggregation of all access-errros from mpu and control spaces                  */
#define MSS_CR5A_AHB_WR_ERR         (98U)      /* MSS_CR5A ahb brige getting write response as a error                          */
#define MSS_CR5B_AHB_WR_ERR         (99U)      /* MSS_CR5B ahb brige getting write response as a error                          */
#define DTHE_SHA_S_INT              (100U)     /* Interrupt from HSM_SHA                                                        */
#define DTHE_SHA_P_INT              (101U)     /* Interrupt from HSM_SHA                                                        */
#define DTHE_TRNG_INT               (102U)     /* Interrupt from HSM_TRNG                                                       */
#define DTHE_PKAE_INT               (103U)     /* Interrupt from HSM_PKAE                                                       */
#define DTHE_AES_S_INT              (104U)     /* Interrupt from HSM_AES                                                        */
#define DTHE_AES_P_INT              (105U)     /* Interrupt from HSM_AES                                                        */
#define MSS_RTIB_INT2               (107U)     /* RTIB compare interrupt                                                        */
#define MSS_RTIB_INT3               (108U)     /* RTIB compare interrupt                                                        */
#define MSS_RTIC_INT2               (109U)     /* RTIC compare interrupt                                                        */
#define MSS_RTIC_INT3               (110U)     /* RTIC compare interrupt                                                        */
#define MSS_MCANB_FE_INT3           (113U)     /* MSS_MCANB message filter interrupt3                                           */
#define MSS_MCANB_FE_INT4           (114U)     /* MSS_MCANB message filter interrupt4                                           */
#define MSS_MCANB_FE_INT5           (115U)     /* MSS_MCANB message filter interrupt5                                           */
#define MSS_MCANB_FE_INT6           (116U)     /* MSS_MCANB message filter interrupt6                                           */
#define MSS_MCANB_FE_INT7           (117U)     /* MSS_MCANB message filter interrupt7                                           */
#define DSS_TPCC_A_INTAGG           (120U)     /* DSS_TPCC_A Aggregated Functional Interrupt                                    */
#define DSS_TPCC_A_ERRAGG           (121U)     /* DSS_TPCC_A Agregated Error Interrupt                                          */
#define DSS_TPCC_B_INTAGG           (122U)     /* DSS_TPCC_B_Aggregated Functional Interrupt                                    */
#define DSS_TPCC_B_ERRAGG           (123U)     /* DSS_TPCC_B Agregated Error Interrupt                                          */
#define DSS_TPCC_C_INTAGG           (124U)     /* DSS_TPCC_C Aggregated Functional Interrupt                                    */
#define DSS_TPCC_C_ERRAGG           (125U)     /* DSS_TPCC_C Agregated Error Interrupt                                          */
#define DSS_DSP_PBIST_CTRL_DONE     (129U)     /* DSS DSP PBIST Controller Done Interrupt                                       */
#define DSS_SW_INT0                 (130U)     /* SW interrupt generated by writing 0x1 to register  DSS_CTRL.DSS_SW_INT[0]     */
#define DSS_SW_INT1                 (131U)     /* SW interrupt generated by writing 0x1 to register  DSS_CTRL.DSS_SW_INT[1]     */
#define DSS_SW_INT2                 (132U)     /* SW interrupt generated by writing 0x1 to register  DSS_CTRL.DSS_SW_INT[2]     */
#define DSS_SW_INT3                 (133U)     /* SW interrupt generated by writing 0x1 to register  DSS_CTRL.DSS_SW_INT[3]     */
#define DSS_MCRC_INT                (136U)     /* DSS MCRC Interrupt                                                            */
#define DSS_DSP_STC_DONE            (137U)     /* DSS DSP STC Done Interrupt                                                    */
#define DSS_DSP_PBIST_DONE          (138U)     /* DSS DSP PBIST Done Interrupt                                                  */
#define DSS_SCIA_INT0               (139U)     /* DSS SCIA Interrupt 0                                                          */
#define DSS_SCIA_INT1               (140U)     /* DSS SCIA Interrupt 1                                                          */
#define RCSS_SCIA_INT               (141U)     /* RCSS_SCIA Cominbed Interrupt from IP                                          */
#define RCSS_SCIA_ERR               (142U)     /* RCSS_SCIA Error Interrupt                                                     */
#define DSS_CBUFF_INT               (143U)     /* DSS CBUFF Interrupt                                                           */
#define DSS_CBUFF_INT_ERR           (144U)     /* DSS CBUFF Error Interrupt                                                     */
#define DSS_HWA_THREAD1_LOOP_INT    (145U)     /* DSS_HWA thread 1 Loop complete interrupt                                      */
#define DSS_HWA_PARAM_DONE_INTR1    (146U)     /* DSS_HWA Param done interrupt1                                                 */
#define RCSS_SPIA_INT0              (147U)     /* RCSS SPI A Interrupt 0                                                        */
#define RCSS_SPIA_INT1              (148U)     /* RCSS SPI A Interrupt 1                                                        */
#define RCSS_SPIB_INT0              (149U)     /* RCSS SPI B Interrupt 0                                                        */
#define RCSS_SPIB_INT1              (150U)     /* RCSS SPI B Interrupt 1                                                        */
#define RCSS_TPCC_A_INTAGG          (151U)     /* RCSS_TPCC_A Aggregated Functional Interrupt                                   */
#define RCSS_TPCC_A_ERRAGG          (152U)     /* RCSS_TPCC_A Aggregated Error Interrupt                                        */
#define RCSS_ECAP_INT               (153U)     /* RCSS ECAP Interrupt                                                           */
#define RCSS_MCASPA_TX_INT          (154U)     /* RCSS McASP A Tx Interrupt                                                     */
#define RCSS_MCASPB_TX_INT          (155U)     /* RCSS McASP B Tx Interrupt                                                     */
#define RCSS_MCASPC_TX_INT          (156U)     /* RCSS McASP C Tx Interrupt                                                     */
#define RCSS_MCASPA_RX_INT          (157U)     /* RCSS McASP A Rx Interrupt                                                     */
#define RCSS_MCASPB_RX_INT          (158U)     /* RCSS McASP B Rx Interrupt                                                     */
#define RCSS_MCASPC_RX_INT          (159U)     /* RCSS McASP C Rx Interrupt                                                     */
#define DSS_HWA_THREAD2_LOOP_INT    (160U)     /* DSS_HWA thread 2   Loop complete interrupt                                    */
#define DSS_HWA_PARAM_DONE_INTR2    (161U)     /* DSS_HWA Param done interrupt2                                                 */
#define DSS_WDT_TB_INT              (162U)     /* DSS WDT Time Base Interrupt                                                   */
#define DSS_HWA_LOCAL_RAM_ERR       (163U)     /* DSS_HWA Local RAM access error                                                */
#define DSS_DCCA_INT                (164U)     /* DSS DCCA Interrupt                                                            */
#define DSS_DCCB_INT                (165U)     /* DSS DCCB Interrupt                                                            */
#define DSS_RTIA_OVERFLOW_0         (166U)     /* DSS_RTIA Overflow 0                                                           */
#define DSS_RTIA_OVERFLOW_1         (167U)     /* DSS_RTIA Overflow 1                                                           */
#define DSS_RTIA_0                  (168U)     /* DSS_RTIA Interrupt 0                                                          */
#define DSS_RTIA_1                  (169U)     /* DSS_RTIA Interrupt 1                                                          */
#define DSS_RTIA_2                  (170U)     /* DSS_RTIA Interrupt 2                                                          */
#define DSS_RTIA_3                  (171U)     /* DSS_RTIA Interrupt 3                                                          */
#define DSS_RTIB_OVERFLOW_0         (172U)     /* DSS_RTIB Overflow 0                                                           */
#define DSS_RTIB_OVERFLOW_1         (173U)     /* DSS_RTIB Overflow 1                                                           */
#define DSS_RTIB_0                  (174U)     /* DSS_RTIB Interrupt 0                                                          */
#define DSS_RTIB_1                  (175U)     /* DSS_RTIB Interrupt 1                                                          */
#define DSS_RTIB_2                  (176U)     /* DSS_RTIB Interrupt 2                                                          */
#define DSS_RTIB_3                  (177U)     /* DSS_RTIB Interrupt 3                                                          */
#define DSS_WDT_OVERFLOW_0          (178U)     /* DSS_WDT Overflow 0                                                            */
#define DSS_WDT_OVERFLOW_1          (179U)     /* DSS_WDT Overflow 1                                                            */
#define DSS_WDT_0                   (180U)     /* DSS_WDT Interrupt 0                                                           */
#define DSS_WDT_1                   (181U)     /* DSS_WDT Interrupt 1                                                           */
#define DSS_WDT_2                   (182U)     /* DSS_WDT Interrupt 2                                                           */
#define DSS_WDT_3                   (183U)     /* DSS_WDT Interrupt 3                                                           */
#define RCSS_CSI2A_INT              (184U)     /* RCSS CSI2A Interrupt                                                          */
#define RCSS_CSI2A_EOL_INT          (185U)     /* RCSS CSI2A End of Line Interrupt (all contexts combined interrupt)            */
#define RCSS_CSI2A_SOF_INT0         (186U)     /* RCSS CSI2A Start of Frame Interrupt 0                                         */
#define RCSS_CSI2A_SOF_INT1         (187U)     /* RCSS CSI2A Start of Frame Interrupt 1                                         */
#define RCSS_CSI2B_INT              (188U)     /* RCSS CSI2B Interrupt                                                          */
#define RCSS_CSI2B_EOL_INT          (189U)     /* RCSS CSI2B End of Line Interrupt (all contexts combined interrupt)            */
#define RCSS_CSI2B_SOF_INT0         (190U)     /* RCSS CSI2B Start of Frame Interrupt 0                                         */
#define RCSS_CSI2B_SOF_INT1         (191U)     /* RCSS CSI2B Start of Frame Interrupt 1                                         */
#define RCSS_I2CA_INT               (192U)     /* RCSS I2C A Interrupt                                                          */
#define RCSS_I2CB_INT               (193U)     /* RCSS I2C B Interrupt                                                          */
#define RCSS_GIO_INT0               (194U)     /* RCSS_GIO high-level Interrupt                                                 */
#define RCSS_GIO_INT1               (195U)     /* RCSS_GIO low-level interrupt                                                  */
#define DSS_DSP_MBOX_READ_REQ       (196U)     /* DSS DSP Mailbox Read Request                                                  */
#define DSS_DSP_MBOX_READ_ACK       (197U)     /* DSS DSP Mailbox Read Acknowledge                                              */
#define MSS_DMM_A_INT0              (200U)     /* Interrupt from MSS_DMM_A                                                      */
#define MSS_DMM_A_INT1              (201U)     /* Interrupt from MSS_DMM_A                                                      */
#define MSS_DMM_B_INT0              (202U)     /* Interrupt from MSS_DMM_B                                                      */
#define MSS_DMM_B_INT1              (203U)     /* Interrupt from MSS_DMM_B                                                      */
#define RCSS_CSI2A_EOF_INT          (210U)     /* RCSS CSI2A End of Frame Interrupt(all contexts combined interrupt)            */
#define RCSS_CSI2A_EOL_CNTX0_INT    (211U)     /* RCSS_CSI2A End of Line Interrupt for Context 0                                */
#define RCSS_CSI2A_EOL_CNTX1_INT    (212U)     /* RCSS_CSI2A End of Line Interrupt for Context 1                                */
#define RCSS_CSI2A_EOL_CNTX2_INT    (213U)     /* RCSS_CSI2A End of Line Interrupt for Context 2                                */
#define RCSS_CSI2A_EOL_CNTX3_INT    (214U)     /* RCSS_CSI2A End of Line Interrupt for Context 3                                */
#define RCSS_CSI2A_EOL_CNTX4_INT    (215U)     /* RCSS_CSI2A End of Line Interrupt for Context 4                                */
#define RCSS_CSI2A_EOL_CNTX5_INT    (216U)     /* RCSS_CSI2A End of Line Interrupt for Context 5                                */
#define RCSS_CSI2A_EOL_CNTX6_INT    (217U)     /* RCSS_CSI2A End of Line Interrupt for Context 6                                */
#define RCSS_CSI2A_EOL_CNTX7_INT    (218U)     /* RCSS_CSI2A End of Line Interrupt for Context 7                                */
#define RCSS_CSI2B_EOF_INT          (219U)     /* RCSS CSI2B End of Frame Interrupt(all contexts combined interrupt)            */
#define RCSS_CSI2B_EOL_CNTX0_INT    (220U)     /* RCSS_CSI2B End of Line Interrupt for Context 0                                */
#define RCSS_CSI2B_EOL_CNTX1_INT    (221U)     /* RCSS_CSI2B End of Line Interrupt for Context 1                                */
#define RCSS_CSI2B_EOL_CNTX2_INT    (222U)     /* RCSS_CSI2B End of Line Interrupt for Context 2                                */
#define RCSS_CSI2B_EOL_CNTX3_INT    (223U)     /* RCSS_CSI2B End of Line Interrupt for Context 3                                */
#define RCSS_CSI2B_EOL_CNTX4_INT    (224U)     /* RCSS_CSI2B End of Line Interrupt for Context 4                                */
#define RCSS_CSI2B_EOL_CNTX5_INT    (225U)     /* RCSS_CSI2B End of Line Interrupt for Context 5                                */
#define RCSS_CSI2B_EOL_CNTX6_INT    (226U)     /* RCSS_CSI2B End of Line Interrupt for Context 6                                */
#define RCSS_CSI2B_EOL_CNTX7_INT    (227U)     /* RCSS_CSI2B End of Line Interrupt for Context 7                                */
#define MSS_GIO_PAD_INT4            (229U)     /* Interrupt Triger from MSS GIO[1][0]                                           */
#define MSS_GIO_PAD_INT5            (230U)     /* Interrupt Triger from MSS GIO[1][1]                                           */
#define MSS_GIO_PAD_INT6            (231U)     /* Interrupt Triger from MSS GIO[1][2]                                           */
#define MSS_GIO_PAD_INT7            (232U)     /* Interrupt Triger from MSS GIO[1][3]                                           */
#define TOP_AURORATX_INT            (233U)     /* TOP_AURORATX Interrupt                                                        */
#define TOP_AURORATX_ERR            (234U)     /* TOP_AURORATX Error Interrupt                                                  */
#define TOP_MDO_INFRA_INT           (235U)     /* TOP_MDO_INFRA Interrupt                                                       */


/*
 * MSS ESM Interrupt mapping
 */
/* Channels with configurable interrupt and error pin behavior  : ESM_ERROR_GP1 */
#define ANA_LIMP_MODE_SYNC_ESM       (63U)
#define DCCB_ERROR_ESM               (62U)
#define MSS_MBOX4BSS_UERR_ESM        (61U)
#define MSS_MBOX4BSS_SBERR_ESM       (60U)
#define BSS_MBOX4MSS_UERR_ESM        (59U)
#define BSS_MBOX4MSS_SBERR_ESM       (58U)
#define BSS_TO_MSS_TRIG_ESM          (57U)
#define BSS_TO_MSS_ESM               (56U)
#define EFC_ERROR_ESM                (40U)
#define VIM_SELFTEST_ERR_ESM         (39U)
#define GEM_IRQ_23_ESM               (36U)
#define GEM_IRQ_22_ESM               (35U)
#define CQDET_MODEERR_ESM            (34U)
#define CAN_SERR_ESM                 (33U)
#define ATCM_SINGLE_ERR_ESM          (32U)
#define CCMR4_ERROR_SELFTEST_ESM     (31U)
#define DCCA_ERROR_ESM               (30U)
#define GEM_IRQ_ESM                  (29U)
#define B1TCM_SINGLE_ERR_ESM         (28U)
#define STC_ERROR_ESM                (27U)
#define B0TCM_SINGLE_ERR_ESM         (26U)
#define SPIA_SERR_ESM                (25U)
#define FRC_COMP_ERR_ESM             (22U)
#define CAN_UERR_ESM                 (21U)
#define VIM_SERR_ESM                 (20U)
#define FRC_SELFTEST_ERR_ESM         (19U)
#define GEM_IRQ_20_ESM               (18U)
#define SPIA_UERR_ESM                (17U)
#define VIM_UERR_ESM                 (15U)
#define DMA_WRERR_INT_PLS_ESM        (13U)
#define GEM_IRQ_19_ESM               (9U )
#define GEM_IRQ_18_ESM               (8U )
#define GEM_IRQ_17_ESM               (7U )
#define GEM_IRQ_16_ESM               (6U )
#define DMA_UERR_ESM                 (3U )
#define DMA_MPV_ESM                  (2U )
#define NERROR_IN_SYNC_ESM           (0U )
#define VIM_COMPARE_ERROR_ESM        (25U)
#define WDT_NMI_REQ_ESM              (24U)
#define MSS_CR4_LIVELOCK_ESM         (16U)
#define B1TCM_PARITY_ERR_ESM         (8U )
#define B0TCM_PARITY_ERR_ESM         (6U )
#define ATCM_PARITY_ERR_ESM          (4U )
#define CCMR4_ERROR_COMPARE_ESM      (2U )
#define ATCM_UNCORR_ERR_ESM          (7U )
#define B1TCM_UNCORR_ERR_ESM         (5U )
#define B0TCM_UNCORR_ERR_ESM         (3U )
#define EFC_AUTOLOAD_ERROR_ESM       (1U )


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

#endif /* SYS_COMMON_H */
