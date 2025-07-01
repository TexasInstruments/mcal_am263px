/* ======================================================================
 *   Copyright (c) 2022 Texas Instruments Incorporated
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
 #ifndef SOC_H_
#define SOC_H_
#ifdef __cplusplus
extern "C"
{
#endif
#define SOC_GIO_REG_BASE        (0x02F7B400U)
#define SOC_RCSSGIO_REG_BASE    (0x05F7B400U)

/*MSS GIO Port Addresses*/
#define SOC_GIO_PORTA_BASE      (0x02F7B434U)
#define SOC_GIO_PORTB_BASE      (0x02F7B454U)
#define SOC_GIO_PORTC_BASE      (0x02F7B474U)
#define SOC_GIO_PORTD_BASE      (0x02F7B494U)

/*RCSS GIO Port Addresses*/
#define SOC_GIO_PORTE_BASE      (0x05F7B434U)
#define SOC_GIO_PORTF_BASE      (0x05F7B454U)
#define SOC_GIO_PORTG_BASE      (0x05F7B474U)
#define SOC_GIO_PORTH_BASE      (0x05F7B494U)

#define SOC_IOMUX_REG_BASE      (0x020C0000U)
#define SOC_TOPRCM_REG_BASE     (0xFFFFE100U)
#define SOC_RCM_REG_BASE        (0xFFFFFF00U)

#define SOC_WDG_REG_BASE        (0x02F7A300U)
#define SOC_QSPI_ADDRSP0_BASE   (0xC8000000U)
#define SOC_MIBSPI1_BASE        (0x02F7E800U)
#define SOC_MIBSPI2_BASE        (0x02F7EA00U)
#define RCSS_SOC_MIBSPI1_BASE   (0x05F7E800U)
#define RCSS_SOC_MIBSPI2_BASE   (0x05F7EA00U)

#define SOC_QSPI_ADDRSP1_BASE   (0xC6000000U)
#define SOC_EPWM1_BASE          (0x03F78C00U)
#define SOC_EPWM2_BASE          (0x03F78D00U)
#define SOC_EPWM3_BASE          (0x03F78E00U)


#define SOC_MSS_CPSW_BASE       (0x07000000U)
#define SOC_MSS_L2_U_BASE       (0x10200000U)
#define SOC_MSS_L2_U_SIZE       (0x000F0000U)
#define SOC_MSS_TCMA_RAM_BASE   (0x00000000U)      /* TCM RAM-A */
#define SOC_MSS_TCMA_RAM_SIZE   (0x00008000U)
#define SOC_MSS_TCMB_RAM_BASE   (0x00080000U)     /* TCM RAM-B */
#define SOC_MSS_TCMB_RAM_SIZE   (0x00008000U)   

#define SOC_GLOB_MSS_TCMA_RAM_BASE     (0xC1000000U)
#define SOC_GLOB_MSS_TCMB_RAM_BASE     (0xC1800000U)
#define SOC_GLOB_MSS_L2_RAM_BASE       (0xC0200000U)

#define SOC_MSS_CTRL_BASE       (0x02120000U)

#define SOC_GLOB_MSS_TCMA_RAM_BASE     (0xC1000000U)
#define SOC_GLOB_MSS_TCMB_RAM_BASE     (0xC1800000U)
#define SOC_GLOB_MSS_L2_RAM_BASE       (0xC0200000U)

#define SOC_MSS_CTRL_BASE       (0x02120000U)

/*LDRA_ANALYSIS*/

#ifdef __cplusplus
}
#endif
#endif /* SOC_H_ */

