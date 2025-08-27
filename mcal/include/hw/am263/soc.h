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
 #ifndef SOC_H_
#define SOC_H_
#ifdef __cplusplus
extern "C"
{
#endif
#define SOC_GIO_REG_BASE         (0x52000000U)
/*MSS GIO Port Addresses*/
#define SOC_GPIO_PORTAB_BASE     (0x52000010U)
#define SOC_GPIO_PORTCD_BASE     (0x52000038U)
#define SOC_GPIO_PORTEF_BASE     (0x52000060U)
#define SOC_GPIO_PORTGH_BASE     (0x52000088U)
#define SOC_GPIO_PORTI_BASE      (0x520000B0U)


#define SOC_IOMUX_REG_BASE      (0x53100000U)
#define SOC_TOPRCM_REG_BASE     (0xFFFFE100U)
#define SOC_RCM_REG_BASE        (0xFFFFFF00U)
#define SOC_WDG_REG_BASE        (0x52100000U)
#define SOC_QSPI_ADDRSP0_BASE   (0xC8000000U)
#define SOC_MIBSPI1_BASE        (0x02F7E800U)
#define SOC_MIBSPI2_BASE        (0x02F7EA00U)
#define RCSS_SOC_MIBSPI1_BASE   (0x05F7E800U)
#define RCSS_SOC_MIBSPI2_BASE   (0x05F7EA00U)
#define SOC_MCSPI0_BASE        (0x52200000U)
#define SOC_MCSPI1_BASE        (0x52201000U)
#define SOC_MCSPI2_BASE        (0x52202000U)
#define SOC_MCSPI3_BASE        (0x52203000U)
#define SOC_MCSPI4_BASE        (0x52204000U)

#define SOC_QSPI_ADDRSP1_BASE   (0xC6000000U)
#define SOC_EPWM1_BASE          (0x03F78C00U)
#define SOC_EPWM2_BASE          (0x03F78D00U)
#define SOC_EPWM3_BASE          (0x03F78E00U)

#define SOC_MSS_TCMA_RAM_BASE   (0x00000040U)      /* TCM RAM-A */
#define SOC_MSS_TCMA_RAM_SIZE   (0x00007FC0U)
#define SOC_MSS_TCMB_RAM_BASE   (0x00080000U)     /* TCM RAM-B */
#define SOC_MSS_TCMB_RAM_SIZE   (0x00004000U)   

#define SOC_GLOB_MSS_TCMA_RAM_BASE     (0x78000000U)
#define SOC_GLOB_MSS_TCMB_RAM_BASE     (0x78100000U)

#define SOC_MSS_CPSW_BASE       (0x52800000U)
#define SOC_CONTROLSS_CTRL      (0x502F0000U)
#define SOC_MSS_CTRL_BASE       (0x50D00000U)

/*LDRA_ANALYSIS*/

#ifdef __cplusplus
}
#endif
#endif /* SOC_H_ */

