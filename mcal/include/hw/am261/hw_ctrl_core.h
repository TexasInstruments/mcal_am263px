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

/*
 * hw_ctrl_core.h
 *
 * Register-level header file for CTRL_CORE
 */

#ifndef HW_CTRL_CORE_H_
#define HW_CTRL_CORE_H_

#include "sys_common.h"
#ifdef __cplusplus
extern "C"
{
#endif



/* Gpio Register Frame Definition */
/** @struct gpioBase
*   @brief GpIO Base Register Definition
*
*   This structure is used to access the GIO module registers.
*/
/** @typedef gioBASE_t
*   @brief GIO Register Frame Type Definition
*
*   This type is used to access the GIO Registers.
*/
typedef struct
{
    uint32 PID;
    uint32 PCR;
    uint32 BINTEN;
} gpioBASE_t;


/** @struct gioPort
*   This type is used to access the GIO Port Registers.
*/
typedef volatile struct
{	uint32 DIR;    /**< 0x0000: Data Direction Register */
    uint32 DOUT;   /**< 0x0004: Data Output Register */
    uint32 DSET;   /**< 0x0008: Data Output Set Register */
    uint32 DCLR;   /**< 0x00C: Data Output Clear Register */
    uint32 DIN;    /**< 0x0010: Data Input Register */
	uint32 SET_RIS_TRIG;
    uint32 CLR_RIS_TRIG;
    uint32 SET_FAL_TRIG;
    uint32 CLR_FAL_TRIG;
    uint32 INTSTAT;
    
} gpioPORT_t;

/*---------------------------------------------------------------------------------------
 * MSS_IOMUX_REGS
 *---------------------------------------------------------------------------------------
 */

/** @typedef pinMuxBase_t
*   @brief Pinmux Register Frame Type Definition
*
*   This type is used to access the Pinmux Registers.
*/
typedef volatile struct
{
     uint32    OSPI0_CSN0;
     uint32    OSPI0_CSN1; 	  
     uint32    OSPI0_CLK;          	  
     uint32    OSPI0_D0;          	      
     uint32    OSPI0_D1;         	      
     uint32    OSPI0_D2;         	      
     uint32    OSPI0_D3;         	      
     uint32    MCAN0_RX;  	              
     uint32    MCAN0_TX;  	              
     uint32    MCAN1_RX;  	              
     uint32	   MCAN1_TX;  	              
     uint32	   SPI0_CS0;     	          
     uint32	   SPI0_CLK;   	          
     uint32	   SPI0_D0;  	              
     uint32	   SPI0_D1; 	              
     uint32	   SPI1_CS0;      	          
     uint32	   SPI1_CLK; 	              
     uint32	   SPI1_D0; 	              
     uint32	   SPI1_D1; 	              
     uint32	   LIN1_RXD; 	              
     uint32	   LIN1_TXD; 	              
     uint32	   LIN2_RXD; 	              
     uint32	   LIN2_TXD; 	              
     uint32	   I2C1_SCL; 	              
     uint32	   I2C1_SDA ; 	              
     uint32	   UART0_RTSN;               
     uint32	   UART0_CTSN;              
     uint32	   UART0_RXD;             
     uint32	   UART0_TXD;                
     uint32	   RGMII1_RXC;               
     uint32	   RGMII1_RX_CTL;            
     uint32	   RGMII1_RD0;              
     uint32	   RGMII1_RD1;              
     uint32	   RGMII1_RD2;              
     uint32	   RGMII1_RD3;              
     uint32	   RGMII1_TXC;              
     uint32	   RGMII1_TX;             
     uint32	   RGMII1_TD0;              
     uint32	   RGMII1_TD1;              
     uint32	   RGMII1_TD2;             
     uint32	   RGMII1_TD3;             
     uint32	   MDIO_MDCMDIO;             
     uint32	   MDIO_MDC;             
     uint32	   EPWM0_A;             
     uint32	   EPWM0_B;              
     uint32	   EPWM1_A;                 
     uint32	   EPWM1_B;                 
     uint32	   EPWM2_A;                 
     uint32	   EPWM2_B;                 
     uint32	   EPWM3_A;                 
     uint32	   EPWM3_B;                 
     uint32	   EPWM4_A;                 
     uint32	   EPWM4_B;       	      
     uint32	   EPWM5_A;      	          
     uint32	   EPWM5_B;           	  
     uint32	   EPWM6_A;       	      
     uint32	   EPWM6_B;       	      
     uint32	   EPWM7_A;        	      
     uint32	   EPWM7_B;                 
     uint32	   EPWM8_A;                 
     uint32	   EPWM8_B;                 
     uint32	   EPWM9_A;                 
     uint32	   EPWM9_B; 
     uint32    GPIO63;
     uint32    GPIO64; 
     uint32    GPIO65; 
     uint32    GPIO66;  
     uint32    PR1_PRU0_GPIO0; 
     uint32    PR1_PRU0_GPIO1;
     uint32    PR1_PRU0_GPIO2;
     uint32    PR1_PRU0_GPIO9;
     uint32    PR1_PRU1_GPIO0;
     uint32    PR1_PRU1_GPIO1;
     uint32    PR1_PRU1_GPIO2;
     uint32    PR1_PRU1_GPIO9;              	              
     uint32	   UART1_RXD;               
     uint32	   UART1_TXD;               
     uint32	   MMC_CLK;                
     uint32	   MMC_CMD;                
     uint32	   MMC_DAT0;                
     uint32	   MMC_DAT1;                
     uint32	   MMC_DAT2;                
     uint32	   MMC_DAT3;                
     uint32	   MMC_SDWP;                
     uint32	   MMC_SDCD;               
     uint32	   PR0_MDIO_MDIO;          
     uint32	   PR0_MDIO_MDC;          
     uint32	   PR0_PRU0_GPIO5;          
     uint32	   PR0_PRU0_GPIO9;          
     uint32	   PR0_PRU0_GPIO10;          
     uint32	   PR0_PRU0_GPIO8;          
     uint32	   PR0_PRU0_GPIO6;          
     uint32	   PR0_PRU0_GPIO4;          
     uint32	   PR0_PRU0_GPIO0;          
     uint32	   PR0_PRU0_GPIO1;          
     uint32	   PR0_PRU0_GPIO2;          
     uint32	   PR0_PRU0_GPIO3;          
     uint32	   PR0_PRU0_GPIO16;          
     uint32	   PR0_PRU0_GPIO15;          
     uint32	   PR0_PRU0_GPIO11;          
     uint32	   PR0_PRU0_GPIO12;          
     uint32	   PR0_PRU0_GPIO13;          
     uint32	   PR0_PRU0_GPIO14;        
     uint32	   PR0_PRU1_GPIO5;	          
     uint32	   PR0_PRU1_GPIO9;	          
     uint32	   PR0_PRU1_GPIO10;    	      
     uint32	   PR0_PRU1_GPIO8;           
     uint32	   PR0_PRU1_GPIO6;       	  
     uint32	   PR0_PRU1_GPIO4;         	  
     uint32	   PR0_PRU1_GPIO0;             
     uint32	   PR0_PRU1_GPIO1;        	  
     uint32	   PR0_PRU1_GPIO2;     	      
     uint32	   PR0_PRU1_GPIO3; 	          
     uint32	   PR0_PRU1_GPIO16;      	      
     uint32	   PR0_PRU1_GPIO15;             
     uint32	   PR0_PRU1_GPIO11;       	  
     uint32	   PR0_PRU1_GPIO12;      	      
     uint32	   PR0_PRU1_GPIO13;  	          
     uint32	   PR0_PRU1_GPIO14;    	      
     uint32	   PR0_PRU1_GPIO19;         	  
     uint32	   PR0_PRU1_GPIO18;             
     uint32	   EXT_REFCLK0;             
     uint32	   SDFM0_CLK0;  	          
     uint32	   SDFM0_D0;  	          
     uint32	   SDFM0_CLK1;     	      
     uint32	   SDFM0_D1;             
     uint32	   SDFM0_CLK2;             
     uint32	   SDFM0_D2;             
     uint32	   SDFM0_CLK3;             
     uint32	   SDFM0_D3;             
     uint32	   EQEP0_A;            
     uint32	   EQEP0_B;        	  
     uint32	   EQEP0_STROBE;        	  
     uint32	   EQEP0_INDEX;             
     uint32	   I2C0_SDA;             
     uint32	   I2C0_SCL;             
     uint32    GPIO136;
     uint32    GPIO137;            
     uint32	   CLKOUT0;
     uint32    USB0_DP;
     uint32    USB0_DM;             
     uint32	   WARMRSTN;             
     uint32	   SAFETY_ERRORN;           
     uint32	   TDI;           
     uint32	   TDO;      	  
     uint32	   TMS; 	      
     uint32	   TCK;        	  
     uint32	   OSPI0_CLKLB;  
     uint32	   OSPI1_CLKLB;	      
     uint32    QUAL_GRP_0_CFG_REG;
     uint32    QUAL_GRP_1_CFG_REG;
     uint32    QUAL_GRP_2_CFG_REG;
     uint32    QUAL_GRP_3_CFG_REG;
     uint32    QUAL_GRP_4_CFG_REG;
     uint32    QUAL_GRP_5_CFG_REG;
     uint32    QUAL_GRP_6_CFG_REG;
     uint32    QUAL_GRP_7_CFG_REG;
     uint32    QUAL_GRP_8_CFG_REG;
     uint32    QUAL_GRP_9_CFG_REG;
     uint32    QUAL_GRP_10_CFG_REG;
     uint32    QUAL_GRP_11_CFG_REG;
     uint32    QUAL_GRP_12_CFG_REG;
     uint32    QUAL_GRP_13_CFG_REG;
     uint32    QUAL_GRP_14_CFG_REG;
     uint32    QUAL_GRP_15_CFG_REG;
     uint32    QUAL_GRP_16_CFG_REG;
     uint32    QUAL_GRP_17_CFG_REG;
     uint32    USER_MODE_EN;
     uint32    PADGLBL_CFG_REG;
     uint32    IOCFGKICK0;
     uint32    IOCFGKICK1;
} pinMuxBase_t;

/*---------------------------------------------------------------------------------------
 * MSS_TOPRCM_REGS
 *---------------------------------------------------------------------------------------
 */
typedef struct {
    volatile uint32	PID;
	volatile uint32	WARM_RST_CAUSE;
	volatile uint32	WARM_RST_CAUSE_CLR;
	volatile uint32	WARM_RESET_REQ;
	volatile uint32	WARM_RSTTIME1;
	volatile uint32	WARM_RSTTIME2;
	volatile uint32	WARM_RSTTIME3;
	volatile uint32	WARM_RESET_CONFIG_OV;
	volatile uint32	WARM_RESET_CONFIG_UV;
	volatile uint32	WARM_RESET_CONFIG_MISC;
	volatile uint32	WARM_RESET_CONFIG;
	volatile uint32	SW_POR;
	volatile uint8	Resv_144[96];
	volatile uint32	LIMP_MODE_EN;
	volatile uint32	CLK_LOSS_STATUS;
	volatile uint8	Resv_256[104];
	volatile uint32	RCOSC32K_CTRL;
	volatile uint32	PLL_REF_CLK_SRC_SEL;
	volatile uint32	PAD_XTAL_CTRL;
	volatile uint32	SOP_MODE_VALUE;
	volatile uint8	Resv_276[4];
	volatile uint32	VMON_CLK_GATE;
	volatile uint8	Resv_1024[744];
	volatile uint32	PLL_CORE_PWRCTRL;
	volatile uint32	PLL_CORE_CLKCTRL;
	volatile uint32	PLL_CORE_TENABLE;
	volatile uint32	PLL_CORE_TENABLEDIV;
	volatile uint32	PLL_CORE_M2NDIV;
	volatile uint32	PLL_CORE_MN2DIV;
	volatile uint32	PLL_CORE_FRACDIV;
	volatile uint32	PLL_CORE_BWCTRL;
	volatile uint32	PLL_CORE_FRACCTRL;
	volatile uint32	PLL_CORE_STATUS;
	volatile uint32	PLL_CORE_HSDIVIDER;
	volatile uint32	PLL_CORE_HSDIVIDER_CLKOUT0;
	volatile uint32	PLL_CORE_HSDIVIDER_CLKOUT1;
	volatile uint32	PLL_CORE_HSDIVIDER_CLKOUT2;
	volatile uint32	PLL_CORE_HSDIVIDER_CLKOUT3;
	volatile uint32	PLL_CORE_RSTCTRL;
	volatile uint32	PLL_CORE_HSDIVIDER_RSTCTRL;
	volatile uint8	Resv_1280[188];
	volatile uint32	R5SS_CLK_SRC_SEL;
	volatile uint32	R5SS_CLK_STATUS;
	volatile uint8	Resv_1296[8];
	volatile uint32	R5SS0_CLK_DIV_SEL;
	volatile uint8	Resv_1304[4];
	volatile uint32	R5SS0_CLK_GATE;
	volatile uint8	Resv_1312[4];
	volatile uint32	SYS_CLK_DIV_VAL;
	volatile uint32	SYS_CLK_GATE;
	volatile uint32	SYS_CLK_STATUS;
	volatile uint8	Resv_2048[724];
	volatile uint32	PLL_PER_PWRCTRL;
	volatile uint32	PLL_PER_CLKCTRL;
	volatile uint32	PLL_PER_TENABLE;
	volatile uint32	PLL_PER_TENABLEDIV;
	volatile uint32	PLL_PER_M2NDIV;
	volatile uint32	PLL_PER_MN2DIV;
	volatile uint32	PLL_PER_FRACDIV;
	volatile uint32	PLL_PER_BWCTRL;
	volatile uint32	PLL_PER_FRACCTRL;
	volatile uint32	PLL_PER_STATUS;
	volatile uint32	PLL_PER_HSDIVIDER;
	volatile uint32	PLL_PER_HSDIVIDER_CLKOUT0;
	volatile uint32	PLL_PER_HSDIVIDER_CLKOUT1;
	volatile uint32	PLL_PER_HSDIVIDER_CLKOUT2;
	volatile uint32	PLL_PER_HSDIVIDER_CLKOUT3;
	volatile uint32	PLL_PER_RSTCTRL;
	volatile uint32	PLL_PER_HSDIVIDER_RSTCTRL;
	volatile uint8	Resv_2304[188];
	volatile uint32	PLL_ETH_PWRCTRL;
	volatile uint32	PLL_ETH_CLKCTRL;
	volatile uint32	PLL_ETH_TENABLE;
	volatile uint32	PLL_ETH_TENABLEDIV;
	volatile uint32	PLL_ETH_M2NDIV;
	volatile uint32	PLL_ETH_MN2DIV;
	volatile uint32	PLL_ETH_FRACDIV;
	volatile uint32	PLL_ETH_BWCTRL;
	volatile uint32	PLL_ETH_FRACCTRL;
	volatile uint32	PLL_ETH_STATUS;
	volatile uint32	PLL_ETH_HSDIVIDER;
	volatile uint32	PLL_ETH_HSDIVIDER_CLKOUT0;
	volatile uint8	Resv_2356[4];
	volatile uint32	PLL_ETH_HSDIVIDER_CLKOUT2;
	volatile uint8	Resv_2364[4];
	volatile uint32	PLL_ETH_RSTCTRL;
	volatile uint32	PLL_ETH_HSDIVIDER_RSTCTRL;
	volatile uint8	Resv_3072[700];
	volatile uint32	CLKOUT0_CLK_SRC_SEL;
	volatile uint32	CLKOUT1_CLK_SRC_SEL;
	volatile uint32	CLKOUT0_DIV_VAL;
	volatile uint32	CLKOUT1_DIV_VAL;
	volatile uint32	CLKOUT0_CLK_GATE;
	volatile uint32	CLKOUT1_CLK_GATE;
	volatile uint32	CLKOUT0_CLK_STATUS;
	volatile uint32	CLKOUT1_CLK_STATUS;
	volatile uint32	TRCCLKOUT_CLK_SRC_SEL;
	volatile uint32	TRCCLKOUT_DIV_VAL;
	volatile uint32	TRCCLKOUT_CLK_GATE;
	volatile uint32	TRCCLKOUT_CLK_STATUS;
	volatile uint32	VMON_CLK_DIV_VAL;
	volatile uint32	VMON_CLK_STATUS;
	volatile uint8	Resv_3328[200];
	volatile uint32	DFT_DMLED_EXEC;
	volatile uint32	DFT_DMLED_STATUS;
	volatile uint8	Resv_3840[504];
	volatile uint32	HW_REG0;
	volatile uint32	HW_REG1;
	volatile uint32	HW_REG2;
	volatile uint32	HW_REG3;
	volatile uint8	Resv_3904[48];
	volatile uint32	HW_SPARE_RW0;
	volatile uint32	HW_SPARE_RW1;
	volatile uint32	HW_SPARE_RW2;
	volatile uint32	HW_SPARE_RW3;
	volatile uint8	Resv_3968[48];
	volatile uint32	HW_SPARE_RO0;
	volatile uint32	HW_SPARE_RO1;
	volatile uint32	HW_SPARE_RO2;
	volatile uint32	HW_SPARE_RO3;
	volatile uint8	Resv_4032[48];
	volatile uint32	HW_SPARE_WPH;
	volatile uint32	HW_SPARE_REC;
	volatile uint8	Resv_4104[64];
	volatile uint32	LOCK0_KICK0;
	volatile uint32	LOCK0_KICK1;
	volatile uint32	INTR_RAW_STATUS;
	volatile uint32	INTR_ENABLED_STATUS_CLEAR;
	volatile uint32	INTR_ENABLE;
	volatile uint32	INTR_ENABLE_CLEAR;
	volatile uint32	EOI;
	volatile uint32	FAULT_ADDRESS;
	volatile uint32	FAULT_TYPE_STATUS;
	volatile uint32	FAULT_ATTR_STATUS;
	volatile uint32	FAULT_CLEAR;
} toprcmBASE_t;


/*---------------------------------------------------------------------------------------
 * MSS_RCM_REGS
 *---------------------------------------------------------------------------------------
 */
typedef volatile struct {
    volatile uint32 RCM_PID;
    volatile uint8  RCM_Resv_16[12];
    volatile uint32 RCM_R5SS0_RST_STATUS;
    volatile uint8  RCM_Resv_32[12];
    volatile uint32 RCM_R5SS0_RST_CAUSE_CLR;
    volatile uint8  RCM_Resv_48[12];
    volatile uint32 RCM_R5SS0_DBG_RST_EN;
    volatile uint8  RCM_Resv_64[12];
    volatile uint32 RCM_R5SS0_RST_ASSERDLY;
    volatile uint8  RCM_Resv_80[12];
    volatile uint32 RCM_R5SS0_RST2ASSERTDLY;
    volatile uint8  RCM_Resv_96[12];
    volatile uint32 RCM_R5SS0_RST_WFICHECK;
    volatile uint8  RCM_Resv_256[156];
    volatile uint32 RCM_MCAN0_CLK_SRC_SEL;
    volatile uint32 RCM_MCAN1_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_320[56];
    volatile uint32 RCM_RTI0_CLK_SRC_SEL;
    volatile uint32 RCM_RTI1_CLK_SRC_SEL;
    volatile uint32 RCM_RTI2_CLK_SRC_SEL;
    volatile uint32 RCM_RTI3_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_384[48];
    volatile uint32 RCM_MCSPI0_CLK_SRC_SEL;
    volatile uint32 RCM_MCSPI1_CLK_SRC_SEL;
    volatile uint32 RCM_MCSPI2_CLK_SRC_SEL;
    volatile uint32 RCM_MCSPI3_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_448[48];
    volatile uint32 RCM_WDT0_CLK_SRC_SEL;
    volatile uint32 RCM_WDT1_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_480[24];
    volatile uint32 RCM_ICSSM0_UART0_CLK_SRC_SEL;
    volatile uint32 RCM_ICSSM1_UART0_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_496[8];
    volatile uint32 RCM_OSPI0_CLK_SRC_SEL;
	volatile uint32 RCM_OSPI1_CLK_SRC_SEL;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_SRC_SEL;
    volatile uint32 RCM_CPTS_CLK_SRC_SEL;
    volatile uint32 RCM_GPMC_CLK_SRC_SEL;
    volatile uint32 RCM_MMC0_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_544[24];
    volatile uint32 RCM_CPSW_5_50_250_CLK_MUX_CTRL;
    volatile uint32 RCM_I2C_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_612[60];
    volatile uint32 RCM_LIN0_UART0_CLK_SRC_SEL;
    volatile uint32 RCM_LIN1_UART1_CLK_SRC_SEL;
    volatile uint32 RCM_LIN2_UART2_CLK_SRC_SEL;
    volatile uint32 RCM_LIN3_UART3_CLK_SRC_SEL;
	volatile uint32 RCM_LIN4_UART4_CLK_SRC_SEL;		
	volatile uint32 RCM_LIN5_UART5_CLK_SRC_SEL;		
	volatile uint8  RCM_Resv_740[104];
	volatile uint32 RCM_ICSSM0_CORE_CLK_SRC_SEL;		
	volatile uint32 RCM_ICSSM1_CORE_CLK_SRC_SEL;		
	volatile uint8  RCM_Resv_768[20];
    volatile uint32 RCM_MCAN0_CLK_DIV_VAL;
    volatile uint32 RCM_MCAN1_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_832[56];
    volatile uint32 RCM_RTI0_CLK_DIV_VAL;
    volatile uint32 RCM_RTI1_CLK_DIV_VAL;
    volatile uint32 RCM_RTI2_CLK_DIV_VAL;
    volatile uint32 RCM_RTI3_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_896[48];
    volatile uint32 RCM_MCSPI0_CLK_DIV_VAL;
    volatile uint32 RCM_MCSPI1_CLK_DIV_VAL;
    volatile uint32 RCM_MCSPI2_CLK_DIV_VAL;
    volatile uint32 RCM_MCSPI3_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_960[48];
    volatile uint32 RCM_WDT0_CLK_DIV_VAL;
    volatile uint32 RCM_WDT1_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_992[24];
    volatile uint32 RCM_ICSSM0_UART_CLK_DIV_VAL;
    volatile uint32 RCM_ICSSM1_UART_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_1008[8];
    volatile uint32 RCM_OSPI0_CLK_DIV_VAL;
	volatile uint32 RCM_OSPI1_CLK_DIV_VAL;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_DIV_VAL;
    volatile uint32 RCM_CPTS_CLK_DIV_VAL;
    volatile uint32 RCM_GPMC_CLK_DIV_VAL;
    volatile uint32 RCM_MMC0_CLK_DIV_VAL;
    volatile uint32 RCM_MSS_ELM_CLK_DIV_VAL;
    volatile uint32 RCM_RGMII_5_CLK_DIV_VAL;
    volatile uint32 RCM_RGMII_50_CLK_DIV_VAL;
    volatile uint32 RCM_RGMII_250_CLK_DIV_VAL;
    volatile uint32 RCM_XTAL_MMC_32K_CLK_DIV_VAL;
    volatile uint32 RCM_XTAL_TEMPSENSE_32K_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_1060[4];
    volatile uint32 RCM_I2C_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_1124[60];
    volatile uint32 RCM_LIN0_UART0_CLK_DIV_VAL;
    volatile uint32 RCM_LIN1_UART1_CLK_DIV_VAL;
    volatile uint32 RCM_LIN2_UART2_CLK_DIV_VAL;
    volatile uint32 RCM_LIN3_UART3_CLK_DIV_VAL;
	volatile uint32 RCM_LIN4_UART4_CLK_DIV_VAL;		
	volatile uint32 RCM_LIN5_UART5_CLK_DIV_VAL;		
	volatile uint8  RCM_Resv_1252[104];
	volatile uint32 RCM_ICSSM0_CORE_CLK_DIV_VAL;		
	volatile uint32 RCM_ICSSM1_CORE_CLK_DIV_VAL;		
	volatile uint8  RCM_Resv_1280[20];
    volatile uint32 RCM_MCAN0_CLK_GATE;
    volatile uint32 RCM_MCAN1_CLK_GATE;
    volatile uint8  RCM_Resv_1344[56];
    volatile uint32 RCM_RTI0_CLK_GATE;
    volatile uint32 RCM_RTI1_CLK_GATE;
    volatile uint32 RCM_RTI2_CLK_GATE;
    volatile uint32 RCM_RTI3_CLK_GATE;
    volatile uint8  RCM_Resv_1408[48];
    volatile uint32 RCM_MCSPI0_CLK_GATE;
    volatile uint32 RCM_MCSPI1_CLK_GATE;
    volatile uint32 RCM_MCSPI2_CLK_GATE;
    volatile uint32 RCM_MCSPI3_CLK_GATE;
    volatile uint8  RCM_Resv_1472[48];
    volatile uint32 RCM_WDT0_CLK_GATE;
    volatile uint32 RCM_WDT1_CLK_GATE;
    volatile uint8  RCM_Resv_1504[24];
    volatile uint32 RCM_ICSSM0_UART_CLK_GATE;
    volatile uint32 RCM_ICSSM1_UART_CLK_GATE;
    volatile uint8  RCM_Resv_1520[8];
    volatile uint32 RCM_OSPI0_CLK_GATE;
	volatile uint32 RCM_OSPI1_CLK_GATE;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_GATE;
    volatile uint32 RCM_CPTS_CLK_GATE;
    volatile uint32 RCM_GPMC_CLK_GATE;
    volatile uint32 RCM_MMC0_CLK_GATE;
    volatile uint32 RCM_MSS_ELM_CLK_GATE;
    volatile uint32 RCM_RGMII_5_CLK_GATE;
    volatile uint32 RCM_RGMII_50_CLK_GATE;
    volatile uint32 RCM_RGMII_250_CLK_GATE;
    volatile uint32 RCM_MMC0_32K_CLK_GATE;
    volatile uint32 RCM_TEMPSENSE_32K_CLK_GATE;
    volatile uint32 RCM_CPSW_CLK_GATE;
    volatile uint32 RCM_I2C0_CLK_GATE;
    volatile uint32 RCM_I2C1_CLK_GATE;
    volatile uint32 RCM_I2C2_CLK_GATE;
    volatile uint8  RCM_Resv_1636[52];
    volatile uint32 RCM_LIN0_CLK_GATE;
    volatile uint32 RCM_LIN1_CLK_GATE;
    volatile uint32 RCM_LIN2_CLK_GATE;
    volatile uint8  RCM_Resv_1700[52];
    volatile uint32 RCM_UART0_CLK_GATE;
    volatile uint32 RCM_UART1_CLK_GATE;
    volatile uint32 RCM_UART2_CLK_GATE;
    volatile uint32 RCM_UART3_CLK_GATE;
	volatile uint32 RCM_UART4_CLK_GATE;		
	volatile uint32 RCM_UART5_CLK_GATE;		
	volatile uint8  RCM_Resv_1764[40];
	volatile uint32 RCM_MSS_ICSSM0_CORE_CLK_GATE;		
	volatile uint32 RCM_MSS_ICSSM1_CORE_CLK_GATE;		
	volatile uint8  RCM_Resv_1792[20];
    volatile uint32 RCM_R5SS0_CORE0_GATE;
    volatile uint8  RCM_Resv_1808[12];
    volatile uint32 RCM_R5SS0_CORE1_GATE;
    volatile uint8  RCM_Resv_1824[12];
    volatile uint32 RCM_ICSSM0_IEP_CLK_GATE;
    volatile uint32 RCM_ICSSM1_IEP_CLK_GATE;
	volatile uint8  RCM_Resv_1840[8];
    volatile uint32 RCM_MSS_ICSSM0_SYS_CLK_GATE;
    volatile uint32 RCM_MSS_ICSSM1_SYS_CLK_GATE;
	volatile uint8  RCM_Resv_1856[8];
    volatile uint32 RCM_USB_CLK_GATE;
    volatile uint32 RCM_USB_WKUP_CLK_GATE;
	volatile uint32 RCM_USB_XTAL_CLK_GATE;		
	volatile uint8  RCM_Resv_2048[180];
    volatile uint32 RCM_HSM_RTIA_CLK_SRC_SEL;
    volatile uint32 RCM_HSM_WDT_CLK_SRC_SEL;
    volatile uint32 RCM_HSM_RTC_CLK_SRC_SEL;
    volatile uint32 RCM_HSM_DMTA_CLK_SRC_SEL;
    volatile uint32 RCM_HSM_DMTB_CLK_SRC_SEL;
    volatile uint32 RCM_HSM_RTI_CLK_DIV_VAL;
    volatile uint32 RCM_HSM_WDT_CLK_DIV_VAL;
    volatile uint32 RCM_HSM_RTC_CLK_DIV_VAL;
    volatile uint32 RCM_HSM_DMTA_CLK_DIV_VAL;
    volatile uint32 RCM_HSM_DMTB_CLK_DIV_VAL;
    volatile uint32 RCM_HSM_RTI_CLK_GATE;
    volatile uint32 RCM_HSM_WDT_CLK_GATE;
    volatile uint32 RCM_HSM_RTC_CLK_GATE;
    volatile uint32 RCM_HSM_DMTA_CLK_GATE;
    volatile uint32 RCM_HSM_DMTB_CLK_GATE;
    volatile uint32 RCM_HSM_RTI_CLK_STATUS;
    volatile uint32 RCM_HSM_WDT_CLK_STATUS;
    volatile uint32 RCM_HSM_RTC_CLK_STATUS;
    volatile uint32 RCM_HSM_DMTA_CLK_STATUS;
    volatile uint32 RCM_HSM_DMTB_CLK_STATUS;
    volatile uint8  RCM_Resv_2304[176];
    volatile uint32 RCM_MCAN0_CLK_STATUS;
    volatile uint32 RCM_MCAN1_CLK_STATUS;
    volatile uint8  RCM_Resv_2368[56];
    volatile uint32 RCM_RTI0_CLK_STATUS;
    volatile uint32 RCM_RTI1_CLK_STATUS;
    volatile uint32 RCM_RTI2_CLK_STATUS;
    volatile uint32 RCM_RTI3_CLK_STATUS;
    volatile uint8  RCM_Resv_2432[48];
    volatile uint32 RCM_MCSPI0_CLK_STATUS;
    volatile uint32 RCM_MCSPI1_CLK_STATUS;
    volatile uint32 RCM_MCSPI2_CLK_STATUS;
    volatile uint32 RCM_MCSPI3_CLK_STATUS;
    volatile uint8  RCM_Resv_2496[48];
    volatile uint32 RCM_WDT0_CLK_STATUS;
    volatile uint32 RCM_WDT1_CLK_STATUS;
    volatile uint8  RCM_Resv_2528[24];
    volatile uint32 RCM_ICSSM0_UART_CLK_STATUS;
    volatile uint32 RCM_ICSSM1_UART_CLK_STATUS;
    volatile uint8  RCM_Resv_2544[8];
    volatile uint32 RCM_OSPI0_CLK_STATUS;
	volatile uint32 RCM_OSPI1_CLK_STATUS;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_STATUS;
    volatile uint32 RCM_CPTS_CLK_STATUS;
    volatile uint32 RCM_GPMC_CLK_STATUS;
    volatile uint32 RCM_MMC0_CLK_STATUS;
    volatile uint32 RCM_MSS_ELM_CLK_STATUS;
    volatile uint32 RCM_RGMII_5_CLK_STATUS;
    volatile uint32 RCM_RGMII_50_CLK_STATUS;
    volatile uint32 RCM_RGMII_250_CLK_STATUS;
    volatile uint32 RCM_MMC0_32K_CLK_STATUS;
    volatile uint32 RCM_TEMPSENSE_32K_CLK_STATUS;
	volatile uint32 RCM_CPSW_5_50_250_CLK_STATUS;
    volatile uint32 RCM_I2C_CLK_STATUS;
    volatile uint8  RCM_Resv_2660[60];
    volatile uint32 RCM_LIN0_UART0_CLK_STATUS;
    volatile uint32 RCM_LIN1_UART1_CLK_STATUS;
    volatile uint32 RCM_LIN2_UART2_CLK_STATUS;
    volatile uint32 RCM_LIN3_UART3_CLK_STATUS;
	volatile uint32 RCM_LIN4_UART4_CLK_STATUS;		
	volatile uint32 RCM_LIN5_UART5_CLK_STATUS;		
	volatile uint8  RCM_Resv_2788[104];
	volatile uint32 RCM_ICSSM0_CORE_CLK_STATUS;		
	volatile uint32 RCM_ICSSM1_CORE_CLK_STATUS;		
	volatile uint8  RCM_Resv_2816[20];
    volatile uint32 RCM_MCAN0_RST_CTRL;
    volatile uint32 RCM_MCAN1_RST_CTRL;
    volatile uint8  RCM_Resv_2880[56];
    volatile uint32 RCM_RTI0_RST_CTRL;
    volatile uint32 RCM_RTI1_RST_CTRL;
    volatile uint32 RCM_RTI2_RST_CTRL;
    volatile uint32 RCM_RTI3_RST_CTRL;
    volatile uint8  RCM_Resv_2944[48];
    volatile uint32 RCM_MCSPI0_RST_CTRL;
    volatile uint32 RCM_MCSPI1_RST_CTRL;
    volatile uint32 RCM_MCSPI2_RST_CTRL;
    volatile uint32 RCM_MCSPI3_RST_CTRL;
    volatile uint8  RCM_Resv_3008[48];
    volatile uint32 RCM_WDT0_RST_CTRL;
    volatile uint32 RCM_WDT1_RST_CTRL;
    volatile uint8  RCM_Resv_3040[24];
    volatile uint32 RCM_ICSSM0_RST_CTRL;
    volatile uint32 RCM_ICSSM1_RST_CTRL;
    volatile uint8  RCM_Resv_3056[8];
    volatile uint32 RCM_OSPI0_RST_CTRL;
	volatile uint32 RCM_OSPI1_RST_CTRL;		
	volatile uint8  RCM_Resv_3072[8];
    volatile uint32 RCM_GPMC_RST_CTRL;
    volatile uint32 RCM_MMC0_RST_CTRL;
    volatile uint32 RCM_MSS_ELM_RST_CTRL;
    volatile uint8  RCM_Resv_3100[16];
    volatile uint32 RCM_TEMPSENSE_32K_RST_CTRL;
    volatile uint32 RCM_CPSW_RST_CTRL;
    volatile uint32 RCM_I2C0_RST_CTRL;
    volatile uint32 RCM_I2C1_RST_CTRL;
    volatile uint32 RCM_I2C2_RST_CTRL;
    volatile uint8  RCM_RCM_Resv_3172[52];
    volatile uint32 RCM_LIN0_RST_CTRL;
    volatile uint32 RCM_LIN1_RST_CTRL;
    volatile uint32 RCM_LIN2_RST_CTRL;
    volatile uint8  RCM_Resv_3236[52];
    volatile uint32 RCM_UART0_RST_CTRL;
    volatile uint32 RCM_UART1_RST_CTRL;
    volatile uint32 RCM_UART2_RST_CTRL;
    volatile uint32 RCM_UART3_RST_CTRL;
	volatile uint32 RCM_UART4_RST_CTRL;		
	volatile uint32 RCM_UART5_RST_CTRL;		
	volatile uint8  RCM_Resv_3328[68];
    volatile uint32 RCM_R5SS0_POR_RST_CTRL;
    volatile uint8  RCM_Resv_3344[12];
    volatile uint32 RCM_R5SS0_CORE0_GRST_CTRL;
    volatile uint8  RCM_Resv_3360[12];
    volatile uint32 RCM_R5SS0_CORE1_GRST_CTRL;
    volatile uint8  RCM_Resv_3376[12];
    volatile uint32 RCM_R5SS0_CORE0_LRST_CTRL;
    volatile uint8  RCM_Resv_3392[12];
    volatile uint32 RCM_R5SS0_CORE1_LRST_CTRL;
    volatile uint8  RCM_Resv_3408[12];
    volatile uint32 RCM_R5SS0_VIM0_RST_CTRL;
    volatile uint8  RCM_Resv_3424[12];
    volatile uint32 RCM_R5SS0_VIM1_RST_CTRL;
    volatile uint8  RCM_Resv_3440[12];
    volatile uint32 RCM_GPIO0_RST_CTRL;
    volatile uint32 RCM_GPIO1_RST_CTRL;
    volatile uint8  RCM_Resv_3536[88];
    volatile uint32 RCM_EDMA_RST_CTRL;
    volatile uint32 RCM_INFRA_RST_CTRL;
    volatile uint32 RCM_SPINLOCK0_RST_CTRL;
    volatile uint32 RCM_USB_RST_CTRL;
    volatile uint32 RCM_MCRC0_RST_CTRL;
    volatile uint32 RCM_TOP_ESM_RST_CTRL;
    volatile uint32 RCM_DCC0_RST_CTRL;
    volatile uint32 RCM_DCC1_RST_CTRL;
    volatile uint32 RCM_DCC2_RST_CTRL;
    volatile uint32 RCM_DCC3_RST_CTRL;
    volatile uint8  RCM_Resv_3584[8];
    volatile uint32 RCM_L2OCRAM_BANK0_PD_CTRL;
    volatile uint32 RCM_L2OCRAM_BANK1_PD_CTRL;
    volatile uint32 RCM_L2OCRAM_BANK2_PD_CTRL;
    volatile uint8  RCM_Resv_3616[20];
    volatile uint32 RCM_L2OCRAM_BANK0_PD_STATUS;
    volatile uint32 RCM_L2OCRAM_BANK1_PD_STATUS;
    volatile uint32 RCM_L2OCRAM_BANK2_PD_STATUS;
    volatile uint8  RCM_Resv_3840[212];
    volatile uint32 RCM_HW_REG0;
    volatile uint32 RCM_HW_REG1;
    volatile uint32 RCM_HW_REG2;
    volatile uint32 RCM_HW_REG3;
    volatile uint8  RCM_Resv_3904[48];
    volatile uint32 RCM_HW_SPARE_RW0;
    volatile uint32 RCM_HW_SPARE_RW1;
    volatile uint32 RCM_HW_SPARE_RW2;
    volatile uint32 RCM_HW_SPARE_RW3;
    volatile uint8 RCM_Resv_3968[48];
    volatile uint32 RCM_HW_SPARE_RO0;
    volatile uint32 RCM_HW_SPARE_RO1;
    volatile uint32 RCM_HW_SPARE_RO2;
    volatile uint32 RCM_HW_SPARE_RO3;
    volatile uint8  RCM_Resv_4032[48];
    volatile uint32 RCM_HW_SPARE_WPH;
    volatile uint32 RCM_HW_SPARE_REC;
    volatile uint8  RCM_Resv_4104[64];
    volatile uint32 RCM_LOCK0_KICK0;
    volatile uint32 RCM_LOCK0_KICK1;
    volatile uint32 RCM_INTR_RAW_STATUS;
    volatile uint32 RCM_INTR_ENABLED_STATUS_CLEAR;
    volatile uint32 RCM_INTR_ENABLE;
    volatile uint32 RCM_INTR_ENABLE_CLEAR;
    volatile uint32 RCM_EOI;
    volatile uint32 RCM_FAULT_ADDRESS;
    volatile uint32 RCM_FAULT_TYPE_STATUS;
    volatile uint32 RCM_FAULT_ATTR_STATUS;
    volatile uint32 RCM_FAULT_CLEAR;
} mssrcmBASE_t;

typedef volatile struct {
     volatile uint32 PID;                       /* PID register */
    volatile uint8  Resv_32[28];
    volatile uint32 R5SS0_CONTROL;
    volatile uint8  Resv_40[4];
    volatile uint32 R5SS0_FORCE_WFI;
    volatile uint8  Resv_64[20];
    volatile uint32 R5SS0_CORE0_HALT;
    volatile uint32 R5SS0_CORE1_HALT;
    volatile uint8  Resv_100[28];
    volatile uint32 R5SS0_STATUS_REG;
    volatile uint8  Resv_128[24];
    volatile uint32 R5SS0_CORE0_STAT;
    volatile uint32 R5SS0_CORE1_STAT;
    volatile uint8  Resv_160[24];
    volatile uint32 R5SS0_INIT_TCM;
    volatile uint8  Resv_192[28];
    volatile uint32 R5SS0_AHB_EN;
    volatile uint8  Resv_200[4];
    volatile uint32 R5SS0_TCM_EXT_ERR_EN;
    volatile uint8  Resv_208[4];
    volatile uint32 R5SS0_TCM_ERR_EN;
    volatile uint8  Resv_216[4];
    volatile uint32 R5SS0_TCM_ECC_WRENZ_EN;
    volatile uint8  Resv_272[52];
    volatile uint32 R5SS0_CORE0_AHB_BASE;
    volatile uint8  Resv_280[4];
    volatile uint32 R5SS0_CORE0_AHB_SIZE;
    volatile uint8  Resv_288[4];
    volatile uint32 R5SS0_CORE1_AHB_BASE;
    volatile uint8  Resv_296[4];
    volatile uint32 R5SS0_CORE1_AHB_SIZE;
    volatile uint8  Resv_336[36];
    volatile uint32 R5SS0_TEINIT;
    volatile uint8  Resv_512[172];
    volatile uint32 BOOT_INFO_REG0;
    volatile uint32 BOOT_INFO_REG1;
    volatile uint32 BOOT_INFO_REG2;
    volatile uint32 BOOT_INFO_REG3;
    volatile uint32 BOOT_INFO_REG4;
    volatile uint32 BOOT_INFO_REG5;
    volatile uint32 BOOT_INFO_REG6;
    volatile uint32 BOOT_INFO_REG7;
    volatile uint8  Resv_768[224];
    volatile uint32 R5SS0_ATCM_MEM_INIT;
    volatile uint32 R5SS0_ATCM_MEM_INIT_DONE;
    volatile uint32 R5SS0_ATCM_MEM_INIT_STATUS;
    volatile uint32 R5SS0_BTCM_MEM_INIT;
    volatile uint32 R5SS0_BTCM_MEM_INIT_DONE;
    volatile uint32 R5SS0_BTCM_MEM_INIT_STATUS;
    volatile uint8  Resv_816[24];
    volatile uint32 L2IOCRAM_MEM_INIT;
    volatile uint32 L2OCRAM_MEM_INIT_DONE;
    volatile uint32 L2OCRAM_MEM_INIT_STATUS;
    volatile uint32 MAILBOXRAM_MEM_INIT;
    volatile uint32 MAILBOXRAM_MEM_INIT_DONE;
    volatile uint32 MAILBOXRAM_MEM_INIT_STATUS;
    volatile uint32 TPCC_MEM_INIT;
    volatile uint32 TPCC_MEM_INIT_DONE;
    volatile uint32 TPCC_MEMINIT_STATUS;
    volatile uint8  Resv_1024[172];
    volatile uint32 TOP_PBIST_KEY_RST;
    volatile uint32 TOP_PBIST_REG0;
    volatile uint32 TOP_PBIST_REG1;
    volatile uint32 TOP_PBIST_REG2;
    volatile uint8  Resv_1280[240];
    volatile uint32 R5SS0_CTI_TRIG_SEL;
    volatile uint8  Resv_1288[4];
    volatile uint32 DBGSS_CTI_TRIG_SEL;
    volatile uint8  Resv_1312[20];
    volatile uint32 MCAN0_HALTEN;
    volatile uint32 MCAN1_HALTEN;
    volatile uint8  Resv_1376[56];
    volatile uint32 LIN0_HALTEN;
    volatile uint32 LIN1_HALTEN;
    volatile uint32 LIN2_HALTEN;
    volatile uint8  Resv_1440[52];
    volatile uint32 I2C0_HALTEN;
    volatile uint32 I2C1_HALTEN;
    volatile uint32 I2C2_HALTEN;
    volatile uint8  Resv_1504[52];
    volatile uint32 RTI0_HALTEN;
    volatile uint32 RTI1_HALTEN;
    volatile uint32 RTI2_HALTEN;
    volatile uint32 RTI3_HALTEN;
    volatile uint8  Resv_1568[48];
    volatile uint32 CPSW_HALTEN;
    volatile uint32 MCRC0_HALTEN;
    volatile uint8  Resv_2048[472];
    volatile uint32 ICSSM0_PRU0_GPI_SEL;
    volatile uint32 ICSSM0_PRU1_GPI_SEL;
    volatile uint32 ICSSM1_PRU0_GPI_SEL;
    volatile uint32 ICSSM1_PRU1_GPI_SEL;
    volatile uint32 ICSSM0_PRU0_GPIO_OUT_CTRL;
    volatile uint32 ICSSM0_PRU1_GPIO_OUT_CTRL;
    volatile uint32 ICSSM1_PRU0_GPIO_OUT_CTRL;
    volatile uint32 ICSSM1_PRU1_GPIO_OUT_CTRL;
    volatile uint32 ICSSM0_RX_ERR_COUNTER;
    volatile uint32 ICSSM0_RX_ERR_COUNTER_CLR;
    volatile uint32 ICSSM1_RX_ERR_COUNTER;
    volatile uint32 ICSSM1_RX_ERR_COUNTER_CLR;
    volatile uint32 TPTC_BOUNDARY_CFG;
    volatile uint32 TPTC_XID_REORDER_CFG;
    volatile uint32 TPTC_DBS_CONFIG;
    volatile uint32 OSPI_CONFIG;
    volatile uint32 OSPI_BOOT_CONFIG_MASK;
    volatile uint32 OSPI_BOOT_CONFIG_SEG;
    volatile uint32 TPCC0_INTAGG_MASK;
    volatile uint32 TPCC0_INTAGG_STATUS;
    volatile uint32 TPCC0_INTAGG_STATUS_RAW;
    volatile uint32 ICSSM_IDLE_CONTROL;
    volatile uint32 GPMC_CONTROL;
    volatile uint32 INTERCONNECT_CLK_GATE_DYNAMIC_CONTROL;
    volatile uint32 CPSW_CONTROL;
    volatile uint32 ICSSM1_INPUT_INTR_SEL;
    volatile uint32 ICSSM_GPO_SEL;
    volatile uint32 DEBUGSS_CSETB_FLUSH;
    volatile uint32 DEBUGSS_STM_NSGUAREN;
    volatile uint32 CTRL_USB_CTRL;
    volatile uint32 CTRL_USB_STS;
    volatile uint8  Resv_2176[4];
    volatile uint32 USB_SLAVE_CONTROL;
    volatile uint32 USB_MASTER_STANDBY;
    volatile uint8  Resv_2188[4];
    volatile uint32 USB_UTMI_DRVVBUS_CONTROL;
    volatile uint8  Resv_2196[4];
    volatile uint32 CONTROL_USBOTGHS_CONTROL;
    volatile uint32 R5SS0_ROM_ECLIPSE;
    volatile uint32 FSS_OE_NEXT_EN;
    volatile uint32 OSPI1_CONFIG_CONTROL;
    volatile uint32 CTRLMMR_ICSSM0_CTRL0;
    volatile uint32 CTRLMMR_ICSSM0_CTRL1;
    volatile uint32 CTRLMMR_ICSSM1_CTRL0;
    volatile uint32 CTRLMMR_ICSSM1_CTRL1;
    volatile uint8  Resv_3904[1676];
    volatile uint32 HW_SPARE_RW0;
    volatile uint32 HW_SPARE_RW1;
    volatile uint32 HW_SPARE_RW2;
    volatile uint32 HW_SPARE_RW3;
    volatile uint8  Resv_3968[48];
    volatile uint32 HW_SPARE_RO0;
    volatile uint32 HW_SPARE_RO1;
    volatile uint32 HW_SPARE_RO2;
    volatile uint32 HW_SPARE_RO3;
    volatile uint8  Resv_4032[48];
    volatile uint32 HW_SPARE_REC;
    volatile uint8  Resv_4104[68];
    volatile uint32 LOCK0_KICK0;               /*  - KICK0 component */
    volatile uint32 LOCK0_KICK1;               /*  - KICK1 component */
    volatile uint32 INTR_RAW_STATUS;           /* Interrupt Raw Status/Set Register */
    volatile uint32 INTR_ENABLED_STATUS_CLEAR;   /* Interrupt Enabled Status/Clear register */
    volatile uint32 INTR_ENABLE;               /* Interrupt Enable register */
    volatile uint32 INTR_ENABLE_CLEAR;         /* Interrupt Enable Clear register */
    volatile uint32 EOI;                       /* EOI register */
    volatile uint32 FAULT_ADDRESS;             /* Fault Address register */
    volatile uint32 FAULT_TYPE_STATUS;         /* Fault Type Status register */
    volatile uint32 FAULT_ATTR_STATUS;         /* Fault Attribute Status register */
    volatile uint32 FAULT_CLEAR;               /* Fault Clear register */
    volatile uint8  Resv_16384[12236];
    volatile uint32 R5SS0_CORE0_MBOX_WRITE_DONE;
    volatile uint32 R5SS0_CORE0_MBOX_READ_REQ;
    volatile uint32 R5SS0_CORE0_MBOX_READ_DONE_ACK;
    volatile uint32 R5SS0_CORE0_MBOX_READ_DONE;
    volatile uint32 R5SS0_CORE0_SW_INT;
    volatile uint8  Resv_16416[12];
    volatile uint32 MPU_ADDR_ERRAGG_R5SS0_CPU0_MASK;
    volatile uint32 MPU_ADDR_ERRAGG_R5SS0_CPU0_STATUS;
    volatile uint32 MPU_ADDR_ERRAGG_R5SS0_CPU0_STATUS_RAW;
    volatile uint8  Resv_16432[4];
    volatile uint32 MPU_PROT_ERRAGG_R5SS0_CPU0_MASK;
    volatile uint32 MPU_PROT_ERRAGG_R5SS0_CPU0_STATUS;
    volatile uint32 MPU_PROT_ERRAGG_R5SS0_CPU0_STATUS_RAW;
    volatile uint8  Resv_32768[16324];
    volatile uint32 R5SS0_CORE1_MBOX_WRITE_DONE;
    volatile uint32 R5SS0_CORE1_MBOX_READ_REQ;
    volatile uint32 R5SS0_CORE1_MBOX_READ_DONE_ACK;
    volatile uint32 R5SS0_CORE1_MBOX_READ_DONE;
    volatile uint32 R5SS0_CORE1_SW_INT;
    volatile uint8  Resv_32800[12];
    volatile uint32 MPU_ADDR_ERRAGG_R5SS0_CPU1_MASK;
    volatile uint32 MPU_ADDR_ERRAGG_R5SS0_CPU1_STATUS;
    volatile uint32 MPU_ADDR_ERRAGG_R5SS0_CPU1_STATUS_RAW;
    volatile uint8  Resv_32816[4];
    volatile uint32 MPU_PROT_ERRAGG_R5SS0_CPU1_MASK;
    volatile uint32 MPU_PROT_ERRAGG_R5SS0_CPU1_STATUS;
    volatile uint32 MPU_PROT_ERRAGG_R5SS0_CPU1_STATUS_RAW;
    volatile uint8  Resv_81920[49092];
    volatile uint32 ICSSM0_PRU0_MBOX_WRITE_DONE;
    volatile uint32 ICSSM0_PRU0_MBOX_READ_REQ;
    volatile uint32 ICSSM0_PRU0_MBOX_READ_DONE_ACK;
    volatile uint32 ICSSM0_PRU0_MBOX_READ_DONE;
    volatile uint32 ICSSM0_PRU1_MBOX_WRITE_DONE;
    volatile uint32 ICSSM0_PRU1_MBOX_READ_REQ;
    volatile uint32 ICSSM0_PRU1_MBOX_READ_DONE_ACK;
    volatile uint32 ICSSM0_PRU1_MBOX_READ_DONE;
    volatile uint32 ICSSM1_PRU0_MBOX_WRITE_DONE;
    volatile uint32 ICSSM1_PRU0_MBOX_READ_REQ;
    volatile uint32 ICSSM1_PRU0_MBOX_READ_DONE_ACK;
    volatile uint32 ICSSM1_PRU0_MBOX_READ_DONE;
    volatile uint32 ICSSM1_PRU1_MBOX_WRITE_DONE;
    volatile uint32 ICSSM1_PRU1_MBOX_READ_REQ;
    volatile uint32 ICSSM1_PRU1_MBOX_READ_DONE_ACK;
    volatile uint32 ICSSM1_PRU1_MBOX_READ_DONE;
    volatile uint8  Resv_98304[16320];
    volatile uint32 TPCC0_ERRAGG_MASK;
    volatile uint32 TPCC0_ERRAGG_STATUS;
    volatile uint32 TPCC0_ERRAGG_STATUS_RAW;
    volatile uint32 MMR_ACCESS_ERRAGG_MASK0;
    volatile uint32 MMR_ACCESS_ERRAGG_STATUS0;
    volatile uint32 MMR_ACCESS_ERRAGG_STATUS_RAW0;
    volatile uint32 R5SS0_CPU0_ECC_CORR_ERRAGG_MASK;
    volatile uint32 R5SS0_CPU0_ECC_CORR_ERRAGG_STATUS;
    volatile uint32 R5SS0_CPU0_ECC_CORR_ERRAGG_STATUS_RAW;
    volatile uint32 R5SS0_CPU0_ECC_UNCORR_ERRAGG_MASK;
    volatile uint32 R5SS0_CPU0_ECC_UNCORR_ERRAGG_STATUS;
    volatile uint32 R5SS0_CPU0_ECC_UNCORR_ERRAGG_STATUS_RAW;
    volatile uint32 R5SS0_CPU1_ECC_CORR_ERRAGG_MASK;
    volatile uint32 R5SS0_CPU1_ECC_CORR_ERRAGG_STATUS;
    volatile uint32 R5SS0_CPU1_ECC_CORR_ERRAGG_STATUS_RAW;
    volatile uint32 R5SS0_CPU1_ECC_UNCORR_ERRAGG_MASK;
    volatile uint32 R5SS0_CPU1_ECC_UNCORR_ERRAGG_STATUS;
    volatile uint32 R5SS0_CPU1_ECC_UNCORR_ERRAGG_STATUS_RAW;
    volatile uint8  Resv_98424[48];
    volatile uint32 R5SS0_CPU0_TCM_ADDRPARITY_ERRAGG_MASK;
    volatile uint32 R5SS0_CPU0_TCM_ADDRPARITY_ERRAGG_STATUS;
    volatile uint32 R5SS0_CPU0_TCM_ADDRPARITY_ERRAGG_STATUS_RAW;
    volatile uint32 R5SS0_CPU1_TCM_ADDRPARITY_ERRAGG_MASK;
    volatile uint32 R5SS0_CPU1_TCM_ADDRPARITY_ERRAGG_STATUS;
    volatile uint32 R5SS0_CPU1_TCM_ADDRPARITY_ERRAGG_STATUS_RAW;
    volatile uint8  Resv_98560[112];
    volatile uint32 MSS_VBUSM_SAFETY_H_ERRAGG_MASK0;
    volatile uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS0;
    volatile uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS_RAW0;
    volatile uint32 MSS_VBUSM_SAFETY_H_ERRAGG_MASK1;
    volatile uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS1;
    volatile uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS_RAW1;
    volatile uint32 MSS_VBUSM_SAFETY_L_ERRAGG_MASK0;
    volatile uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS0;
    volatile uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS_RAW0;
    volatile uint32 MSS_VBUSM_SAFETY_L_ERRAGG_MASK1;
    volatile uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS1;
    volatile uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS_RAW1;
    volatile uint8  Resv_98688[80];
    volatile uint32 MSS_VBUSP_SAFETY_H_ERRAGG_MASK;
    volatile uint32 MSS_VBUSP_SAFETY_H_ERRAGG_STATUS;
    volatile uint32 MSS_VBUSP_SAFETY_H_ERRAGG_STATUS_RAW;
    volatile uint8  Resv_98816[116];
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 TPTC00_RD_BUS_SAFETY_CTRL;
    volatile uint32 TPTC00_RD_BUS_SAFETY_FI;
    volatile uint32 TPTC00_RD_BUS_SAFETY_ERR;
    volatile uint32 TPTC00_RD_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 TPTC00_RD_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 TPTC00_RD_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 TPTC01_RD_BUS_SAFETY_CTRL;
    volatile uint32 TPTC01_RD_BUS_SAFETY_FI;
    volatile uint32 TPTC01_RD_BUS_SAFETY_ERR;
    volatile uint32 TPTC01_RD_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 TPTC01_RD_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 TPTC01_RD_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 TPTC00_WR_BUS_SAFETY_CTRL;
    volatile uint32 TPTC00_WR_BUS_SAFETY_FI;
    volatile uint32 TPTC00_WR_BUS_SAFETY_ERR;
    volatile uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 TPTC01_WR_BUS_SAFETY_CTRL;
    volatile uint32 TPTC01_WR_BUS_SAFETY_FI;
    volatile uint32 TPTC01_WR_BUS_SAFETY_ERR;
    volatile uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 MSS_CPSW_BUS_SAFETY_CTRL;
    volatile uint32 MSS_CPSW_BUS_SAFETY_FI;
    volatile uint32 MSS_CPSW_BUS_SAFETY_ERR;
    volatile uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 DAP_BUS_SAFETY_CTRL;
    volatile uint32 DAP_BUS_SAFETY_FI;
    volatile uint32 DAP_BUS_SAFETY_ERR;
    volatile uint32 DAP_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 DAP_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 DAP_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 DAP_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 DAP_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_CTRL;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_FI;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_CTRL;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_FI;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_CTRL;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_FI;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_CTRL;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_FI;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_ERR;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 STM_STIM_BUS_SAFETY_CTRL;
    volatile uint32 STM_STIM_BUS_SAFETY_FI;
    volatile uint32 STM_STIM_BUS_SAFETY_ERR;
    volatile uint32 STM_STIM_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 STM_STIM_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 STM_STIM_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 STM_STIM_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 STM_STIM_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint8  Resv_99360[48];
    volatile uint32 HSM_TPTC0_RD_BUS_SAFETY_CTRL;
    volatile uint32 HSM_TPTC0_RD_BUS_SAFETY_FI;
    volatile uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR;
    volatile uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR_STAT_READ;
    volatile uint8  Resv_99392[8];
    volatile uint32 HSM_TPTC1_RD_BUS_SAFETY_CTRL;
    volatile uint32 HSM_TPTC1_RD_BUS_SAFETY_FI;
    volatile uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR;
    volatile uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR_STAT_READ;
    volatile uint8  Resv_99424[8];
    volatile uint32 HSM_TPTC0_WR_BUS_SAFETY_CTRL;
    volatile uint32 HSM_TPTC0_WR_BUS_SAFETY_FI;
    volatile uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR;
    volatile uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint8  Resv_99456[4];
    volatile uint32 HSM_TPTC1_WR_BUS_SAFETY_CTRL;
    volatile uint32 HSM_TPTC1_WR_BUS_SAFETY_FI;
    volatile uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR;
    volatile uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 OSPI0_BUS_SAFETY_CTRL;
    volatile uint32 OSPI0_BUS_SAFETY_FI;
    volatile uint32 OSPI0_BUS_SAFETY_ERR;
    volatile uint32 OSPI0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 OSPI0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 OSPI0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 OSPI0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 OSPI0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint8  Resv_99520[4];
    volatile uint32 HSM_DTHE_BUS_SAFETY_CTRL;
    volatile uint32 HSM_DTHE_BUS_SAFETY_FI;
    volatile uint32 HSM_DTHE_BUS_SAFETY_ERR;
    volatile uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 MMC0_BUS_SAFETY_CTRL;
    volatile uint32 MMC0_BUS_SAFETY_FI;
    volatile uint32 MMC0_BUS_SAFETY_ERR;
    volatile uint32 MMC0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 MMC0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 MMC0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 MMC0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 MMC0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_CTRL;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_FI;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_ERR;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_CTRL;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_FI;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_ERR;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 MCRC0_BUS_SAFETY_CTRL;
    volatile uint32 MCRC0_BUS_SAFETY_FI;
    volatile uint32 MCRC0_BUS_SAFETY_ERR;
    volatile uint32 MCRC0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 MCRC0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 MCRC0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 MCRC0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 MCRC0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_CTRL;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_FI;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 HSM_M_BUS_SAFETY_CTRL;
    volatile uint32 HSM_M_BUS_SAFETY_FI;
    volatile uint32 HSM_M_BUS_SAFETY_ERR;
    volatile uint32 HSM_M_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 HSM_M_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 HSM_M_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 HSM_M_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 HSM_M_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 HSM_S_BUS_SAFETY_CTRL;
    volatile uint32 HSM_S_BUS_SAFETY_FI;
    volatile uint32 HSM_S_BUS_SAFETY_ERR;
    volatile uint32 HSM_S_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 HSM_S_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 HSM_S_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 HSM_S_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 HSM_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 ICSSM0_S_BUS_SAFETY_CTRL;
    volatile uint32 ICSSM0_S_BUS_SAFETY_FI;
    volatile uint32 ICSSM0_S_BUS_SAFETY_ERR;
    volatile uint32 ICSSM0_S_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 ICSSM0_S_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 ICSSM0_S_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 ICSSM0_S_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 ICSSM0_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_CTRL;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_FI;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_ERR;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 ICSSM0_PDSP0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_CTRL;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_FI;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_ERR;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 ICSSM0_PDSP1_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_CTRL;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_FI;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_ERR;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 ICSSM1_PDSP0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_CTRL;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_FI;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_ERR;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 ICSSM1_PDSP1_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 ICSSM1_S_BUS_SAFETY_CTRL;
    volatile uint32 ICSSM1_S_BUS_SAFETY_FI;
    volatile uint32 ICSSM1_S_BUS_SAFETY_ERR;
    volatile uint32 ICSSM1_S_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 ICSSM1_S_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 ICSSM1_S_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 ICSSM1_S_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 ICSSM1_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 USBSS_RD_BUS_SAFETY_CTRL;
    volatile uint32 USBSS_RD_BUS_SAFETY_FI;
    volatile uint32 USBSS_RD_BUS_SAFETY_ERR;
    volatile uint32 USBSS_RD_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 USBSS_RD_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 USBSS_RD_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 USBSS_WR_BUS_SAFETY_CTRL;
    volatile uint32 USBSS_WR_BUS_SAFETY_FI;
    volatile uint32 USBSS_WR_BUS_SAFETY_ERR;
    volatile uint32 USBSS_WR_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 USBSS_WR_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 USBSS_WR_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 USBSS_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 GPMC0_BUS_SAFETY_CTRL;
    volatile uint32 GPMC0_BUS_SAFETY_FI;
    volatile uint32 GPMC0_BUS_SAFETY_ERR;
    volatile uint32 GPMC0_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 GPMC0_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 GPMC0_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 GPMC0_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 GPMC0_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint8  Resv_100096[12];
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_BRDG_READ;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_BRDG_READ;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_BRDG_WRITE;
    volatile uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_BRDG_WRITERESP;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_BRDG_WRITE;
    volatile uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_BRDG_WRITERESP;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_WRITE;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_READ;
    volatile uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_WRITERESP;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_WRITE;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_READ;
    volatile uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_BRDG_WRITERESP;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_BRDG_WRITE;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_BRDG_READ;
    volatile uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_BRDG_WRITERESP;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_BRDG_WRITE;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_BRDG_READ;
    volatile uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_BRDG_WRITERESP;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_BRDG_CMD;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_BRDG_WRITE;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_BRDG_READ;
    volatile uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_BRDG_WRITERESP;
    volatile uint8  Resv_100240[24];
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_CTRL;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_FI;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_ERR;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 MAIN_VBUSP_BUS_SAFETY_EP_ERR_STATUS;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_CTRL;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_FI;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_ERR;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_EP_ERR_STATUS_L;
    volatile uint32 PERI_VBUSP_BUS_SAFETY_EP_ERR_STATUS_H;
    volatile uint32 BUS_SAFETY_CTRL;
    volatile uint32 MSS_BUS_SAFETY_SEC_ERR_STAT0;
    volatile uint32 MSS_BUS_SAFETY_SEC_ERR_STAT1;
    volatile uint8  Resv_100352[24];
    volatile uint32 R5SS0_TCM_ADDRPARITY_CLR;
    volatile uint32 R5SS0_CORE0_ADDRPARITY_ERR_ATCM;
    volatile uint32 R5SS0_CORE1_ADDRPARITY_ERR_ATCM;
    volatile uint32 R5SS0_CORE0_ERR_ADDRPARITY_B0TCM;
    volatile uint32 R5SS0_CORE1_ERR_ADDRPARITY_B0TCM;
    volatile uint32 R5SS0_CORE0_ERR_ADDRPARITY_B1TCM;
    volatile uint32 R5SS0_CORE1_ERR_ADDRPARITY_B1TCM;
    volatile uint8  Resv_100404[24];
    volatile uint32 R5SS0_TCM_ADDRPARITY_ERRFORCE;
    volatile uint8  Resv_100416[8];
    volatile uint32 TPCC0_PARITY_CTRL;
    volatile uint32 TPCC0_PARITY_STATUS;
    volatile uint32 TMU_R5SS0_CORE0_ROM_PARITY_CTRL;
    volatile uint32 TMU_R5SS0_CORE0_ROM_PARITY_STATUS;
    volatile uint32 TMU_R5SS0_CORE1_ROM_PARITY_CTRL;
    volatile uint32 TMU_R5SS0_CORE1_ROM_PARITY_STATUS;
    volatile uint8  Resv_100456[16];
    volatile uint32 OSPI1_BUS_SAFETY_CTRL;
    volatile uint32 OSPI1_BUS_SAFETY_FI;
    volatile uint32 OSPI1_BUS_SAFETY_ERR;
    volatile uint32 OSPI1_BUS_SAFETY_ERR_STAT_DATA0;
    volatile uint32 OSPI1_BUS_SAFETY_ERR_STAT_CMD;
    volatile uint32 OSPI1_BUS_SAFETY_ERR_STAT_WRITE;
    volatile uint32 OSPI1_BUS_SAFETY_ERR_STAT_READ;
    volatile uint32 OSPI1_BUS_SAFETY_ERR_STAT_WRITERESP;
    volatile uint8  Resv_100608[120];
    volatile uint32 NERROR_MASK;
} ctrlBASE_t;

typedef volatile struct
{
 volatile uint32 PID;
    volatile uint32 INFO;
    volatile uint32 PRIIRQ;
    volatile uint32 PRIFIQ;
    volatile uint32 IRQGSTS;
    volatile uint32 FIQGSTS;
    volatile uint32 IRQVEC;
    volatile uint32 FIQVEC;
    volatile uint32 ACTIRQ;
    volatile uint32 ACTFIQ;
	volatile uint32 IRQPRIMSK;		
	volatile uint32 FIQPRIMSK;		
    volatile uint32 DEDVEC;
    volatile uint8  Resv_1024[972];
    volatile uint32 RAW;
    volatile uint32 STS;
    volatile uint32 INTR_EN_SET;
    volatile uint32 INTER_EN_CLR;
    volatile uint32 IRQSTS;
    volatile uint32 FIQSTS;
    volatile uint32 INTMAP;
    volatile uint32 INTTYPE;
    volatile uint32 RAW_1;
    volatile uint32 STS_1;
    volatile uint32 INTR_EN_SET_1;
    volatile uint32 INTER_EN_CLR_1;
    volatile uint32 IRQSTS_1;
    volatile uint32 FIQSTS_1;
    volatile uint32 INTMAP_1;
    volatile uint32 INTTYPE_1;
    volatile uint32 RAW_2;
    volatile uint32 STS_2;
    volatile uint32 INTR_EN_SET_2;
    volatile uint32 INTER_EN_CLR_2;
    volatile uint32 IRQSTS_2;
    volatile uint32 FIQSTS_2;
    volatile uint32 INTMAP_2;
    volatile uint32 INTTYPE_2;
    volatile uint32 RAW_3;
    volatile uint32 STS_3;
    volatile uint32 INTR_EN_SET_3;
    volatile uint32 INTER_EN_CLR_3;
    volatile uint32 IRQSTS_3;
    volatile uint32 FIQSTS_3;
    volatile uint32 INTMAP_3;
    volatile uint32 INTTYPE_3;
    volatile uint32 RAW_4;
    volatile uint32 STS_4;
    volatile uint32 INTR_EN_SET_4;
    volatile uint32 INTER_EN_CLR_4;
    volatile uint32 IRQSTS_4;
    volatile uint32 FIQSTS_4;
    volatile uint32 INTMAP_4;
    volatile uint32 INTTYPE_4;
    volatile uint32 RAW_5;
    volatile uint32 STS_5;
    volatile uint32 INTR_EN_SET_5;
    volatile uint32 INTER_EN_CLR_5;
    volatile uint32 IRQSTS_5;
    volatile uint32 FIQSTS_5;
    volatile uint32 INTMAP_5;
    volatile uint32 INTTYPE_5;
    volatile uint32 RAW_6;
    volatile uint32 STS_6;
    volatile uint32 INTR_EN_SET_6;
    volatile uint32 INTER_EN_CLR_6;
    volatile uint32 IRQSTS_6;
    volatile uint32 FIQSTS_6;
    volatile uint32 INTMAP_6;
    volatile uint32 INTTYPE_6;
    volatile uint32 RAW_7;
    volatile uint32 STS_7;
    volatile uint32 INTR_EN_SET_7;
    volatile uint32 INTER_EN_CLR_7;
    volatile uint32 IRQSTS_7;
    volatile uint32 FIQSTS_7;
    volatile uint32 INTMAP_7;
    volatile uint32 INTTYPE_7;
    volatile uint8  Resv_4096[2816];
    volatile uint32 INTPRIORITY;
    volatile uint32 INTPRIORITY_1;
    volatile uint32 INTPRIORITY_2;
    volatile uint32 INTPRIORITY_3;
    volatile uint32 INTPRIORITY_4;
    volatile uint32 INTPRIORITY_5;
    volatile uint32 INTPRIORITY_6;
    volatile uint32 INTPRIORITY_7;
    volatile uint32 INTPRIORITY_8;
    volatile uint32 INTPRIORITY_9;
    volatile uint32 INTPRIORITY_10;
    volatile uint32 INTPRIORITY_11;
    volatile uint32 INTPRIORITY_12;
    volatile uint32 INTPRIORITY_13;
    volatile uint32 INTPRIORITY_14;
    volatile uint32 INTPRIORITY_15;
    volatile uint32 INTPRIORITY_16;
    volatile uint32 INTPRIORITY_17;
    volatile uint32 INTPRIORITY_18;
    volatile uint32 INTPRIORITY_19;
    volatile uint32 INTPRIORITY_20;
    volatile uint32 INTPRIORITY_21;
    volatile uint32 INTPRIORITY_22;
    volatile uint32 INTPRIORITY_23;
    volatile uint32 INTPRIORITY_24;
    volatile uint32 INTPRIORITY_25;
    volatile uint32 INTPRIORITY_26;
    volatile uint32 INTPRIORITY_27;
    volatile uint32 INTPRIORITY_28;
    volatile uint32 INTPRIORITY_29;
    volatile uint32 INTPRIORITY_30;
    volatile uint32 INTPRIORITY_31;
    volatile uint32 INTPRIORITY_32;
    volatile uint32 INTPRIORITY_33;
    volatile uint32 INTPRIORITY_34;
    volatile uint32 INTPRIORITY_35;
    volatile uint32 INTPRIORITY_36;
    volatile uint32 INTPRIORITY_37;
    volatile uint32 INTPRIORITY_38;
    volatile uint32 INTPRIORITY_39;
    volatile uint32 INTPRIORITY_40;
    volatile uint32 INTPRIORITY_41;
    volatile uint32 INTPRIORITY_42;
    volatile uint32 INTPRIORITY_43;
    volatile uint32 INTPRIORITY_44;
    volatile uint32 INTPRIORITY_45;
    volatile uint32 INTPRIORITY_46;
    volatile uint32 INTPRIORITY_47;
    volatile uint32 INTPRIORITY_48;
    volatile uint32 INTPRIORITY_49;
    volatile uint32 INTPRIORITY_50;
    volatile uint32 INTPRIORITY_51;
    volatile uint32 INTPRIORITY_52;
    volatile uint32 INTPRIORITY_53;
    volatile uint32 INTPRIORITY_54;
    volatile uint32 INTPRIORITY_55;
    volatile uint32 INTPRIORITY_56;
    volatile uint32 INTPRIORITY_57;
    volatile uint32 INTPRIORITY_58;
    volatile uint32 INTPRIORITY_59;
    volatile uint32 INTPRIORITY_60;
    volatile uint32 INTPRIORITY_61;
    volatile uint32 INTPRIORITY_62;
    volatile uint32 INTPRIORITY_63;
    volatile uint32 INTPRIORITY_64;
    volatile uint32 INTPRIORITY_65;
    volatile uint32 INTPRIORITY_66;
    volatile uint32 INTPRIORITY_67;
    volatile uint32 INTPRIORITY_68;
    volatile uint32 INTPRIORITY_69;
    volatile uint32 INTPRIORITY_70;
    volatile uint32 INTPRIORITY_71;
    volatile uint32 INTPRIORITY_72;
    volatile uint32 INTPRIORITY_73;
    volatile uint32 INTPRIORITY_74;
    volatile uint32 INTPRIORITY_75;
    volatile uint32 INTPRIORITY_76;
    volatile uint32 INTPRIORITY_77;
    volatile uint32 INTPRIORITY_78;
    volatile uint32 INTPRIORITY_79;
    volatile uint32 INTPRIORITY_80;
    volatile uint32 INTPRIORITY_81;
    volatile uint32 INTPRIORITY_82;
    volatile uint32 INTPRIORITY_83;
    volatile uint32 INTPRIORITY_84;
    volatile uint32 INTPRIORITY_85;
    volatile uint32 INTPRIORITY_86;
    volatile uint32 INTPRIORITY_87;
    volatile uint32 INTPRIORITY_88;
    volatile uint32 INTPRIORITY_89;
    volatile uint32 INTPRIORITY_90;
    volatile uint32 INTPRIORITY_91;
    volatile uint32 INTPRIORITY_92;
    volatile uint32 INTPRIORITY_93;
    volatile uint32 INTPRIORITY_94;
    volatile uint32 INTPRIORITY_95;
    volatile uint32 INTPRIORITY_96;
    volatile uint32 INTPRIORITY_97;
    volatile uint32 INTPRIORITY_98;
    volatile uint32 INTPRIORITY_99;
    volatile uint32 INTPRIORITY_100;
    volatile uint32 INTPRIORITY_101;
    volatile uint32 INTPRIORITY_102;
    volatile uint32 INTPRIORITY_103;
    volatile uint32 INTPRIORITY_104;
    volatile uint32 INTPRIORITY_105;
    volatile uint32 INTPRIORITY_106;
    volatile uint32 INTPRIORITY_107;
    volatile uint32 INTPRIORITY_108;
    volatile uint32 INTPRIORITY_109;
    volatile uint32 INTPRIORITY_110;
    volatile uint32 INTPRIORITY_111;
    volatile uint32 INTPRIORITY_112;
    volatile uint32 INTPRIORITY_113;
    volatile uint32 INTPRIORITY_114;
    volatile uint32 INTPRIORITY_115;
    volatile uint32 INTPRIORITY_116;
    volatile uint32 INTPRIORITY_117;
    volatile uint32 INTPRIORITY_118;
    volatile uint32 INTPRIORITY_119;
    volatile uint32 INTPRIORITY_120;
    volatile uint32 INTPRIORITY_121;
    volatile uint32 INTPRIORITY_122;
    volatile uint32 INTPRIORITY_123;
    volatile uint32 INTPRIORITY_124;
    volatile uint32 INTPRIORITY_125;
    volatile uint32 INTPRIORITY_126;
    volatile uint32 INTPRIORITY_127;
    volatile uint32 INTPRIORITY_128;
    volatile uint32 INTPRIORITY_129;
    volatile uint32 INTPRIORITY_130;
    volatile uint32 INTPRIORITY_131;
    volatile uint32 INTPRIORITY_132;
    volatile uint32 INTPRIORITY_133;
    volatile uint32 INTPRIORITY_134;
    volatile uint32 INTPRIORITY_135;
    volatile uint32 INTPRIORITY_136;
    volatile uint32 INTPRIORITY_137;
    volatile uint32 INTPRIORITY_138;
    volatile uint32 INTPRIORITY_139;
    volatile uint32 INTPRIORITY_140;
    volatile uint32 INTPRIORITY_141;
    volatile uint32 INTPRIORITY_142;
    volatile uint32 INTPRIORITY_143;
    volatile uint32 INTPRIORITY_144;
    volatile uint32 INTPRIORITY_145;
    volatile uint32 INTPRIORITY_146;
    volatile uint32 INTPRIORITY_147;
    volatile uint32 INTPRIORITY_148;
    volatile uint32 INTPRIORITY_149;
    volatile uint32 INTPRIORITY_150;
    volatile uint32 INTPRIORITY_151;
    volatile uint32 INTPRIORITY_152;
    volatile uint32 INTPRIORITY_153;
    volatile uint32 INTPRIORITY_154;
    volatile uint32 INTPRIORITY_155;
    volatile uint32 INTPRIORITY_156;
    volatile uint32 INTPRIORITY_157;
    volatile uint32 INTPRIORITY_158;
    volatile uint32 INTPRIORITY_159;
    volatile uint32 INTPRIORITY_160;
    volatile uint32 INTPRIORITY_161;
    volatile uint32 INTPRIORITY_162;
    volatile uint32 INTPRIORITY_163;
    volatile uint32 INTPRIORITY_164;
    volatile uint32 INTPRIORITY_165;
    volatile uint32 INTPRIORITY_166;
    volatile uint32 INTPRIORITY_167;
    volatile uint32 INTPRIORITY_168;
    volatile uint32 INTPRIORITY_169;
    volatile uint32 INTPRIORITY_170;
    volatile uint32 INTPRIORITY_171;
    volatile uint32 INTPRIORITY_172;
    volatile uint32 INTPRIORITY_173;
    volatile uint32 INTPRIORITY_174;
    volatile uint32 INTPRIORITY_175;
    volatile uint32 INTPRIORITY_176;
    volatile uint32 INTPRIORITY_177;
    volatile uint32 INTPRIORITY_178;
    volatile uint32 INTPRIORITY_179;
    volatile uint32 INTPRIORITY_180;
    volatile uint32 INTPRIORITY_181;
    volatile uint32 INTPRIORITY_182;
    volatile uint32 INTPRIORITY_183;
    volatile uint32 INTPRIORITY_184;
    volatile uint32 INTPRIORITY_185;
    volatile uint32 INTPRIORITY_186;
    volatile uint32 INTPRIORITY_187;
    volatile uint32 INTPRIORITY_188;
    volatile uint32 INTPRIORITY_189;
    volatile uint32 INTPRIORITY_190;
    volatile uint32 INTPRIORITY_191;
    volatile uint32 INTPRIORITY_192;
    volatile uint32 INTPRIORITY_193;
    volatile uint32 INTPRIORITY_194;
    volatile uint32 INTPRIORITY_195;
    volatile uint32 INTPRIORITY_196;
    volatile uint32 INTPRIORITY_197;
    volatile uint32 INTPRIORITY_198;
    volatile uint32 INTPRIORITY_199;
    volatile uint32 INTPRIORITY_200;
    volatile uint32 INTPRIORITY_201;
    volatile uint32 INTPRIORITY_202;
    volatile uint32 INTPRIORITY_203;
    volatile uint32 INTPRIORITY_204;
    volatile uint32 INTPRIORITY_205;
    volatile uint32 INTPRIORITY_206;
    volatile uint32 INTPRIORITY_207;
    volatile uint32 INTPRIORITY_208;
    volatile uint32 INTPRIORITY_209;
    volatile uint32 INTPRIORITY_210;
    volatile uint32 INTPRIORITY_211;
    volatile uint32 INTPRIORITY_212;
    volatile uint32 INTPRIORITY_213;
    volatile uint32 INTPRIORITY_214;
    volatile uint32 INTPRIORITY_215;
    volatile uint32 INTPRIORITY_216;
    volatile uint32 INTPRIORITY_217;
    volatile uint32 INTPRIORITY_218;
    volatile uint32 INTPRIORITY_219;
    volatile uint32 INTPRIORITY_220;
    volatile uint32 INTPRIORITY_221;
    volatile uint32 INTPRIORITY_222;
    volatile uint32 INTPRIORITY_223;
    volatile uint32 INTPRIORITY_224;
    volatile uint32 INTPRIORITY_225;
    volatile uint32 INTPRIORITY_226;
    volatile uint32 INTPRIORITY_227;
    volatile uint32 INTPRIORITY_228;
    volatile uint32 INTPRIORITY_229;
    volatile uint32 INTPRIORITY_230;
    volatile uint32 INTPRIORITY_231;
    volatile uint32 INTPRIORITY_232;
    volatile uint32 INTPRIORITY_233;
    volatile uint32 INTPRIORITY_234;
    volatile uint32 INTPRIORITY_235;
    volatile uint32 INTPRIORITY_236;
    volatile uint32 INTPRIORITY_237;
    volatile uint32 INTPRIORITY_238;
    volatile uint32 INTPRIORITY_239;
    volatile uint32 INTPRIORITY_240;
    volatile uint32 INTPRIORITY_241;
    volatile uint32 INTPRIORITY_242;
    volatile uint32 INTPRIORITY_243;
    volatile uint32 INTPRIORITY_244;
    volatile uint32 INTPRIORITY_245;
    volatile uint32 INTPRIORITY_246;
    volatile uint32 INTPRIORITY_247;
    volatile uint32 INTPRIORITY_248;
    volatile uint32 INTPRIORITY_249;
    volatile uint32 INTPRIORITY_250;
    volatile uint32 INTPRIORITY_251;
    volatile uint32 INTPRIORITY_252;
    volatile uint32 INTPRIORITY_253;
    volatile uint32 INTPRIORITY_254;
    volatile uint32 INTPRIORITY_255;
    volatile uint8  Resv_8192[3072];
    volatile uint32 INTVECTOR;
    volatile uint32 INTVECTOR_1;
    volatile uint32 INTVECTOR_2;
    volatile uint32 INTVECTOR_3;
    volatile uint32 INTVECTOR_4;
    volatile uint32 INTVECTOR_5;
    volatile uint32 INTVECTOR_6;
    volatile uint32 INTVECTOR_7;
    volatile uint32 INTVECTOR_8;
    volatile uint32 INTVECTOR_9;
    volatile uint32 INTVECTOR_10;
    volatile uint32 INTVECTOR_11;
    volatile uint32 INTVECTOR_12;
    volatile uint32 INTVECTOR_13;
    volatile uint32 INTVECTOR_14;
    volatile uint32 INTVECTOR_15;
    volatile uint32 INTVECTOR_16;
    volatile uint32 INTVECTOR_17;
    volatile uint32 INTVECTOR_18;
    volatile uint32 INTVECTOR_19;
    volatile uint32 INTVECTOR_20;
    volatile uint32 INTVECTOR_21;
    volatile uint32 INTVECTOR_22;
    volatile uint32 INTVECTOR_23;
    volatile uint32 INTVECTOR_24;
    volatile uint32 INTVECTOR_25;
    volatile uint32 INTVECTOR_26;
    volatile uint32 INTVECTOR_27;
    volatile uint32 INTVECTOR_28;
    volatile uint32 INTVECTOR_29;
    volatile uint32 INTVECTOR_30;
    volatile uint32 INTVECTOR_31;
    volatile uint32 INTVECTOR_32;
    volatile uint32 INTVECTOR_33;
    volatile uint32 INTVECTOR_34;
    volatile uint32 INTVECTOR_35;
    volatile uint32 INTVECTOR_36;
    volatile uint32 INTVECTOR_37;
    volatile uint32 INTVECTOR_38;
    volatile uint32 INTVECTOR_39;
    volatile uint32 INTVECTOR_40;
    volatile uint32 INTVECTOR_41;
    volatile uint32 INTVECTOR_42;
    volatile uint32 INTVECTOR_43;
    volatile uint32 INTVECTOR_44;
    volatile uint32 INTVECTOR_45;
    volatile uint32 INTVECTOR_46;
    volatile uint32 INTVECTOR_47;
    volatile uint32 INTVECTOR_48;
    volatile uint32 INTVECTOR_49;
    volatile uint32 INTVECTOR_50;
    volatile uint32 INTVECTOR_51;
    volatile uint32 INTVECTOR_52;
    volatile uint32 INTVECTOR_53;
    volatile uint32 INTVECTOR_54;
    volatile uint32 INTVECTOR_55;
    volatile uint32 INTVECTOR_56;
    volatile uint32 INTVECTOR_57;
    volatile uint32 INTVECTOR_58;
    volatile uint32 INTVECTOR_59;
    volatile uint32 INTVECTOR_60;
    volatile uint32 INTVECTOR_61;
    volatile uint32 INTVECTOR_62;
    volatile uint32 INTVECTOR_63;
    volatile uint32 INTVECTOR_64;
    volatile uint32 INTVECTOR_65;
    volatile uint32 INTVECTOR_66;
    volatile uint32 INTVECTOR_67;
    volatile uint32 INTVECTOR_68;
    volatile uint32 INTVECTOR_69;
    volatile uint32 INTVECTOR_70;
    volatile uint32 INTVECTOR_71;
    volatile uint32 INTVECTOR_72;
    volatile uint32 INTVECTOR_73;
    volatile uint32 INTVECTOR_74;
    volatile uint32 INTVECTOR_75;
    volatile uint32 INTVECTOR_76;
    volatile uint32 INTVECTOR_77;
    volatile uint32 INTVECTOR_78;
    volatile uint32 INTVECTOR_79;
    volatile uint32 INTVECTOR_80;
    volatile uint32 INTVECTOR_81;
    volatile uint32 INTVECTOR_82;
    volatile uint32 INTVECTOR_83;
    volatile uint32 INTVECTOR_84;
    volatile uint32 INTVECTOR_85;
    volatile uint32 INTVECTOR_86;
    volatile uint32 INTVECTOR_87;
    volatile uint32 INTVECTOR_88;
    volatile uint32 INTVECTOR_89;
    volatile uint32 INTVECTOR_90;
    volatile uint32 INTVECTOR_91;
    volatile uint32 INTVECTOR_92;
    volatile uint32 INTVECTOR_93;
    volatile uint32 INTVECTOR_94;
    volatile uint32 INTVECTOR_95;
    volatile uint32 INTVECTOR_96;
    volatile uint32 INTVECTOR_97;
    volatile uint32 INTVECTOR_98;
    volatile uint32 INTVECTOR_99;
    volatile uint32 INTVECTOR_100;
    volatile uint32 INTVECTOR_101;
    volatile uint32 INTVECTOR_102;
    volatile uint32 INTVECTOR_103;
    volatile uint32 INTVECTOR_104;
    volatile uint32 INTVECTOR_105;
    volatile uint32 INTVECTOR_106;
    volatile uint32 INTVECTOR_107;
    volatile uint32 INTVECTOR_108;
    volatile uint32 INTVECTOR_109;
    volatile uint32 INTVECTOR_110;
    volatile uint32 INTVECTOR_111;
    volatile uint32 INTVECTOR_112;
    volatile uint32 INTVECTOR_113;
    volatile uint32 INTVECTOR_114;
    volatile uint32 INTVECTOR_115;
    volatile uint32 INTVECTOR_116;
    volatile uint32 INTVECTOR_117;
    volatile uint32 INTVECTOR_118;
    volatile uint32 INTVECTOR_119;
    volatile uint32 INTVECTOR_120;
    volatile uint32 INTVECTOR_121;
    volatile uint32 INTVECTOR_122;
    volatile uint32 INTVECTOR_123;
    volatile uint32 INTVECTOR_124;
    volatile uint32 INTVECTOR_125;
    volatile uint32 INTVECTOR_126;
    volatile uint32 INTVECTOR_127;
    volatile uint32 INTVECTOR_128;
    volatile uint32 INTVECTOR_129;
    volatile uint32 INTVECTOR_130;
    volatile uint32 INTVECTOR_131;
    volatile uint32 INTVECTOR_132;
    volatile uint32 INTVECTOR_133;
    volatile uint32 INTVECTOR_134;
    volatile uint32 INTVECTOR_135;
    volatile uint32 INTVECTOR_136;
    volatile uint32 INTVECTOR_137;
    volatile uint32 INTVECTOR_138;
    volatile uint32 INTVECTOR_139;
    volatile uint32 INTVECTOR_140;
    volatile uint32 INTVECTOR_141;
    volatile uint32 INTVECTOR_142;
    volatile uint32 INTVECTOR_143;
    volatile uint32 INTVECTOR_144;
    volatile uint32 INTVECTOR_145;
    volatile uint32 INTVECTOR_146;
    volatile uint32 INTVECTOR_147;
    volatile uint32 INTVECTOR_148;
    volatile uint32 INTVECTOR_149;
    volatile uint32 INTVECTOR_150;
    volatile uint32 INTVECTOR_151;
    volatile uint32 INTVECTOR_152;
    volatile uint32 INTVECTOR_153;
    volatile uint32 INTVECTOR_154;
    volatile uint32 INTVECTOR_155;
    volatile uint32 INTVECTOR_156;
    volatile uint32 INTVECTOR_157;
    volatile uint32 INTVECTOR_158;
    volatile uint32 INTVECTOR_159;
    volatile uint32 INTVECTOR_160;
    volatile uint32 INTVECTOR_161;
    volatile uint32 INTVECTOR_162;
    volatile uint32 INTVECTOR_163;
    volatile uint32 INTVECTOR_164;
    volatile uint32 INTVECTOR_165;
    volatile uint32 INTVECTOR_166;
    volatile uint32 INTVECTOR_167;
    volatile uint32 INTVECTOR_168;
    volatile uint32 INTVECTOR_169;
    volatile uint32 INTVECTOR_170;
    volatile uint32 INTVECTOR_171;
    volatile uint32 INTVECTOR_172;
    volatile uint32 INTVECTOR_173;
    volatile uint32 INTVECTOR_174;
    volatile uint32 INTVECTOR_175;
    volatile uint32 INTVECTOR_176;
    volatile uint32 INTVECTOR_177;
    volatile uint32 INTVECTOR_178;
    volatile uint32 INTVECTOR_179;
    volatile uint32 INTVECTOR_180;
    volatile uint32 INTVECTOR_181;
    volatile uint32 INTVECTOR_182;
    volatile uint32 INTVECTOR_183;
    volatile uint32 INTVECTOR_184;
    volatile uint32 INTVECTOR_185;
    volatile uint32 INTVECTOR_186;
    volatile uint32 INTVECTOR_187;
    volatile uint32 INTVECTOR_188;
    volatile uint32 INTVECTOR_189;
    volatile uint32 INTVECTOR_190;
    volatile uint32 INTVECTOR_191;
    volatile uint32 INTVECTOR_192;
    volatile uint32 INTVECTOR_193;
    volatile uint32 INTVECTOR_194;
    volatile uint32 INTVECTOR_195;
    volatile uint32 INTVECTOR_196;
    volatile uint32 INTVECTOR_197;
    volatile uint32 INTVECTOR_198;
    volatile uint32 INTVECTOR_199;
    volatile uint32 INTVECTOR_200;
    volatile uint32 INTVECTOR_201;
    volatile uint32 INTVECTOR_202;
    volatile uint32 INTVECTOR_203;
    volatile uint32 INTVECTOR_204;
    volatile uint32 INTVECTOR_205;
    volatile uint32 INTVECTOR_206;
    volatile uint32 INTVECTOR_207;
    volatile uint32 INTVECTOR_208;
    volatile uint32 INTVECTOR_209;
    volatile uint32 INTVECTOR_210;
    volatile uint32 INTVECTOR_211;
    volatile uint32 INTVECTOR_212;
    volatile uint32 INTVECTOR_213;
    volatile uint32 INTVECTOR_214;
    volatile uint32 INTVECTOR_215;
    volatile uint32 INTVECTOR_216;
    volatile uint32 INTVECTOR_217;
    volatile uint32 INTVECTOR_218;
    volatile uint32 INTVECTOR_219;
    volatile uint32 INTVECTOR_220;
    volatile uint32 INTVECTOR_221;
    volatile uint32 INTVECTOR_222;
    volatile uint32 INTVECTOR_223;
    volatile uint32 INTVECTOR_224;
    volatile uint32 INTVECTOR_225;
    volatile uint32 INTVECTOR_226;
    volatile uint32 INTVECTOR_227;
    volatile uint32 INTVECTOR_228;
    volatile uint32 INTVECTOR_229;
    volatile uint32 INTVECTOR_230;
    volatile uint32 INTVECTOR_231;
    volatile uint32 INTVECTOR_232;
    volatile uint32 INTVECTOR_233;
    volatile uint32 INTVECTOR_234;
    volatile uint32 INTVECTOR_235;
    volatile uint32 INTVECTOR_236;
    volatile uint32 INTVECTOR_237;
    volatile uint32 INTVECTOR_238;
    volatile uint32 INTVECTOR_239;
    volatile uint32 INTVECTOR_240;
    volatile uint32 INTVECTOR_241;
    volatile uint32 INTVECTOR_242;
    volatile uint32 INTVECTOR_243;
    volatile uint32 INTVECTOR_244;
    volatile uint32 INTVECTOR_245;
    volatile uint32 INTVECTOR_246;
    volatile uint32 INTVECTOR_247;
    volatile uint32 INTVECTOR_248;
    volatile uint32 INTVECTOR_249;
    volatile uint32 INTVECTOR_250;
    volatile uint32 INTVECTOR_251;
    volatile uint32 INTVECTOR_252;
    volatile uint32 INTVECTOR_253;
    volatile uint32 INTVECTOR_254;
    volatile uint32 INTVECTOR_255;
} vimBASE_t;


typedef volatile struct
{
    uint32 EEPAPR1;           /* 0x0000                 */
    uint32 DEPAPR1;           /* 0x0004                 */
    uint32 IESR1;             /* 0x0008                 */
    uint32 IECR1;             /* 0x000C                 */
    uint32 ILSR1;             /* 0x0010                 */
    uint32 ILCR1;             /* 0x0014                 */
    uint32 SR1[3U];           /* 0x0018, 0x001C, 0x0020 */
    uint32 EPSR;              /* 0x0024                 */
    uint32 IOFFHR;            /* 0x0028                 */
    uint32 IOFFLR;            /* 0x002C                 */
    uint32 LTCR;              /* 0x0030                 */
    uint32 LTCPR;             /* 0x0034                 */
    uint32 EKR;               /* 0x0038                 */
    uint32 SSR2;              /* 0x003C                 */
    uint32 IEPSR4;            /* 0x0040                 */
    uint32 IEPCR4;            /* 0x0044                 */
    uint32 IESR4;             /* 0x0048                 */
    uint32 IECR4;             /* 0x004C                 */
    uint32 ILSR4;             /* 0x0050                 */
    uint32 ILCR4;             /* 0x0054                 */
    uint32 SR4[3U];           /* 0x0058, 0x005C, 0x0060 */
    uint32 ESTATUS5EMU;       /* 0x0064                 */
    uint32 reserv1[6U];       /* 0x0068, 0x006C, 0x0070, 0x0074, 0x0078, 0x007C */
    uint32 IEPSR7;            /* 0x0080                 */
    uint32 IEPCR7;            /* 0x0084                 */
    uint32 IESR7;             /* 0x0088                 */
    uint32 IECR7;             /* 0x008C                 */
    uint32 ILSR7;             /* 0x0090                 */
    uint32 ILCR7;             /* 0x0094                 */
    uint32 SR7[3U];           /* 0x0098, 0x009C, 0x00A0 */
    uint32 ESTATUS8EMU;       /* 0x00A4                 */
    uint32 reserv2[6U];       /* 0x00A8, 0x00AC, 0x00B0, 0x00B4, 0x00B8, 0x00BC */
    uint32 IEPSR10;           /* 0x00C0                 */
    uint32 IEPCR10;           /* 0x00C4                 */
    uint32 IESR10;            /* 0x00C8                 */
    uint32 IECR10;            /* 0x00CC                 */
    uint32 ILSR10;            /* 0x00D0                 */
    uint32 ILCR10;            /* 0x00D4                 */
    uint32 SR10[3U];          /* 0x00D8, 0x00DC, 0x00E0 */
    uint32 ESTATUS10EMU;      /* 0x00E4                 */
} esmBASE_t;

typedef volatile struct
{
    uint32  CCCCFG0             ;        /* Offset = 0x0D0 */
    uint32  CCCCFG1             ;        /* Offset = 0x0D4 */
    uint32  CCCCFG2             ;        /* Offset = 0x0D8 */
    uint32  CCCCFG3             ;        /* Offset = 0x0DC */
} cccBASE_t;


/** @typedef rtiBASE_t
*   @brief RTI Register Frame Type Definition
*
*   This type is used to access the RTI Registers.
*/
typedef volatile struct
{
    uint32 GCTRL;          /**< 0x0000: Global Control Register   */
    uint32 TBCTRL;         /**< 0x0004: Timebase Control Register */
    uint32 CAPCTRL;        /**< 0x0008: Capture Control Register  */
    uint32 COMPCTRL;       /**< 0x000C: Compare Control Register  */
    struct
    {
        uint32 FRCx;       /**< 0x0010,0x0030: Free Running Counter x Register         */
        uint32 UCx;        /**< 0x0014,0x0034: Up Counter x Register                   */
        uint32 CPUCx;      /**< 0x0018,0x0038: Compare Up Counter x Register           */
        uint32   rsvd1;    /**< 0x001C,0x003C: Reserved                                */
        uint32 CAFRCx;     /**< 0x0020,0x0040: Capture Free Running Counter x Register */
        uint32 CAUCx;      /**< 0x0024,0x0044: Capture Up Counter x Register           */
        uint32   rsvd2[2U]; /**< 0x0028,0x0048: Reserved                                */
    } CNT[2U];               /**< Counter x selection:
                                    - 0: Counter 0
                                    - 1: Counter 1                                       */
    struct
    {
        uint32 COMPx;      /**< 0x0050,0x0058,0x0060,0x0068: Compare x Register        */
        uint32 UDCPx;      /**< 0x0054,0x005C,0x0064,0x006C: Update Compare x Register */
    } CMP[4U];               /**< Compare x selection:
                                    - 0: Compare 0
                                    - 1: Compare 1
                                    - 2: Compare 2
                                    - 3: Compare 3                                       */
    uint32 TBLCOMP;        /**< 0x0070: External Clock Timebase Low Compare Register   */
    uint32 TBHCOMP;        /**< 0x0074: External Clock Timebase High Compare Register  */
    uint32   rsvd3[2U];    /**< 0x0078: Reserved                                       */
    uint32 SETINTENA;      /**< 0x0080: Set/Status Interrupt Register                  */
    uint32 CLEARINTENA;    /**< 0x0084: Clear/Status Interrupt Register                */
    uint32 INTFLAG;        /**< 0x0088: Interrupt Flag Register                        */
    uint32   rsvd4;        /**< 0x008C: Reserved                                       */
    uint32 DWDCTRL;        /**< 0x0090: Digital Watchdog Control Register   */
    uint32 DWDPRLD;        /**< 0x0094: Digital Watchdog Preload Register */
    uint32 WDSTATUS;       /**< 0x0098: Watchdog Status Register  */
    uint32 WDKEY;          /**< 0x009C: Watchdog Key Register  */
    uint32 DWDCNTR;        /**< 0x00A0: Digital Watchdog Down Counter   */
    uint32 WWDRXNCTRL;     /**< 0x00A4: Digital Windowed Watchdog Reaction Control */
    uint32 WWDSIZECTRL;    /**< 0x00A8: Digital Windowed Watchdog Window Size Control  */
    uint32 INTCLRENABLE;   /**< 0x00AC: RTI Compare Interrupt Clear Enable Register  */
    uint32 COMP0CLR;       /**< 0x00B0: RTI Compare 0 Clear Register   */
    uint32 COMP1CLR;       /**< 0x00B4: RTI Compare 1 Clear Register */
    uint32 COMP2CLR;       /**< 0x00B8: RTI Compare 2 Clear Register  */
    uint32 COMP3CLR;       /**< 0x00BC: RTI Compare 3 Clear Register  */
} rtiBASE_t;

typedef volatile struct
{
    uint32 PID;
    uint32 rsvd1[3U];
    uint32 SYSCONFIG;
    uint32 rsvd2[3U];
    uint32 INTSTARAWSET;
    uint32 INTSTAENBCLR;
    uint32 INTENSET;
    uint32 INTENCLR;
    uint32 EOI;
    uint32 rsvd3[3U];
    uint32 SPICLKCTRL;
    uint32 SPIDC;
    uint32 SPICMD;
    uint32 SPISTATUS;
    uint32 SPIDATA;
    uint32 SPISTUP0;
    uint32 SPISTUP1;
    uint32 SPISTUP2;
    uint32 SPISTUP3;
    uint32 SPISWITCH;
    uint32 SPIDATA1;
    uint32 SPIDATA2;
    uint32 SPIDATA3;
} qspiBASE_t;

typedef volatile struct
{
    volatile uint32 INTMASK;       /* offset 0x00 */
    volatile uint32 rsvd1;
    volatile uint32 INTMASKSET;    /* offset 0x08 */
    volatile uint32 rsvd2;
    volatile uint32 INTMASKCLR;    /* offset 0x10 */
    volatile uint32 rsvd3;
    volatile uint32 INTSTSCLR;     /* offset 0x18 */
    volatile uint32 rsvd4;
    volatile uint32 INTACK;        /* offset 0x20 */
    volatile uint32 rsvd5;
    volatile uint32 INTTRIG;       /* offset 0x28 */
    volatile uint32 rsvd6;
    volatile uint32 INTSTSMSKD;    /* offset 0x30 */
    volatile uint32 rsvd7;
    volatile uint32 INTSTSRAW;     /* offset 0x38 */
    volatile uint32 rsvd8;
    volatile uint32 SEMAPHORE0;    /* offset 0x40 */
    volatile uint32 rsvd9;
    volatile uint32 SEMAPHORE1;    /* offset 0x48 */
} MailboxReg_t;

typedef volatile struct
{
    uint32      CTL;          /**< 0x0000: Control Register                       */
    uint32      ES;           /**< 0x0004: Error and Status Register              */
    uint32      EERC;         /**< 0x0008: Error Counter Register                 */
    uint32      BTR;          /**< 0x000C: Bit Timing Register                    */
    uint32      INT;          /**< 0x0010: Interrupt Register                     */
    uint32      TEST;         /**< 0x0014: Test Register                          */
    uint32      rsvd1;        /**< 0x0018: Reserved                               */
    uint32      PERR;         /**< 0x001C: Parity/SECDED Error Code Register      */
    uint32      REL; /**< 0x0020: Core Release Register */
    uint32      ECCDIAG;  /**< 0x0024: ECC Diagnostic Register                   */
    uint32      ECCDIADSTAT; /**< 0x0028: ECC Diagnostic Status Register        */
    uint32      ECCCS; /**< 0x002C: ECC Control and Status Register             */
    uint32      ECCSERR; /**< 0x0030: ECC Single Bit Error Code Register        */
    uint32      rsvd2[19];    /**< 0x0034 - 0x7C: Reserved                        */
    uint32      ABOTR;        /**< 0x0080: Auto Bus On Time Register              */
    uint32      TrnsRxReg;        /**< 0x0084: Transmission Request X Register        */
    uint32      TXRQx[4U];    /**< 0x0088-0x0094: Transmission Request Registers  */
    uint32      NewDataReg;       /**< 0x0098: New Data X Register                    */
    uint32      NWDATx[4U];   /**< 0x009C-0x00A8: New Data Registers              */
    uint32      IntrPend;      /**< 0x00AC: Interrupt Pending X Register           */
    uint32      INTPNDx[4U];  /**< 0x00B0-0x00BC: Interrupt Pending Registers     */
    uint32      MsgVal;      /**< 0x00C0: Message Valid X Register               */
    uint32      MSGVALx[4U];  /**< 0x00C4-0x00D0: Message Valid Registers         */
    uint32        rsvd3;      /**< 0x00D4: Reserved                               */
    uint32      INTMUXx[4U];  /**< 0x00D8-0x00E4: Interrupt Multiplexer Registers */
    uint32        rsvd4[6];   /**< 0x00E8: Reserved                               */
    uint8 IF1NO;              /**< 0x0100: IF1 Command Register, Msg Number       */
    uint8 IF1STAT;            /**< 0x0100: IF1 Command Register, Status           */
    uint8 IF1CMD;             /**< 0x0100: IF1 Command Register, Command          */
    uint8   rsvd9;            /**< 0x0100: IF1 Command Register, Reserved         */
    uint32      IF1MSK;       /**< 0x0104: IF1 Mask Register                      */
    uint32      IF1ARB;       /**< 0x0108: IF1 Arbitration Register               */
    uint32      IF1MCTL;      /**< 0x010C: IF1 Message Control Register           */
    uint8 IF1DATx[8U];        /**< 0x0110-0x0114: IF1 Data A and B Registers      */
    uint32        rsvd5[2];   /**< 0x0118: Reserved                               */
    uint8 IF2NO;              /**< 0x0120: IF2 Command Register, Msg No           */
    uint8 IF2STAT;            /**< 0x0120: IF2 Command Register, Status           */
    uint8 IF2CMD;             /**< 0x0120: IF2 Command Register, Command          */
    uint8   rsvd10;           /**< 0x0120: IF2 Command Register, Reserved         */
    uint32      IF2MSK;       /**< 0x0124: IF2 Mask Register                      */
    uint32      IF2ARB;       /**< 0x0128: IF2 Arbitration Register               */
    uint32      IF2MCTL;      /**< 0x012C: IF2 Message Control Register           */
    uint8 IF2DATx[8U];        /**< 0x0130-0x0134: IF2 Data A and B Registers      */
    uint32        rsvd6[2];   /**< 0x0138: Reserved                               */
    uint32      IF3OBS;       /**< 0x0140: IF3 Observation Register               */
    uint32      IF3MSK;       /**< 0x0144: IF3 Mask Register                      */
    uint32      IF3ARB;       /**< 0x0148: IF3 Arbitration Register               */
    uint32      IF3MCTL;      /**< 0x014C: IF3 Message Control Register           */
    uint8 IF3DATx[8U];        /**< 0x0150-0x0154: IF3 Data A and B Registers      */
    uint32        rsvd7[2];   /**< 0x0158: Reserved                               */
    uint32      IF3UEy[4U];   /**< 0x0160-0x016C: IF3 Update Enable Registers     */
    uint32        rsvd8[28];  /**< 0x0170: Reserved                               */
    uint32      TIOC;         /**< 0x01E0: TX IO Control Register                 */
    uint32      RIOC;         /**< 0x01E4: RX IO Control Register                 */
} dcanBASE_t;


/************************************************************************************/
/*                            PBIST registers                                       */
/************************************************************************************/
typedef volatile struct
{
    uint32 PADREG0;        /* AddrOffset = 0x000 */
    uint32 PADREG1;        /* AddrOffset = 0x004 */
    uint32 PADREG2;        /* AddrOffset = 0x008 */
    uint32 PADREG3;        /* AddrOffset = 0x00C */
    uint32 PADREG4;        /* AddrOffset = 0x010 */
    uint32 PADREG5;        /* AddrOffset = 0x014 */
    uint32 PADREG6;        /* AddrOffset = 0x018 */
    uint32 PADREG7;        /* AddrOffset = 0x01C */
    uint32 PADREG8;        /* AddrOffset = 0x020 */
    uint32 PADREG9;        /* AddrOffset = 0x024 */
    uint32 PADREG10;        /* AddrOffset = 0x028 */
    uint32 PADREG11;        /* AddrOffset = 0x02C */
    uint32 PADREG12;        /* AddrOffset = 0x030 */
    uint32 PADREG13;        /* AddrOffset = 0x034 */
    uint32 PADREG14;        /* AddrOffset = 0x038 */
    uint32 PADREG15;        /* AddrOffset = 0x03C */
    uint32 PADREG16;        /* AddrOffset = 0x040 */
    uint32 PADREG17;        /* AddrOffset = 0x044 */
    uint32 PADREG18;        /* AddrOffset = 0x048 */
    uint32 PADREG19;        /* AddrOffset = 0x04C */
    uint32 PADREG20;        /* AddrOffset = 0x050 */
    uint32 PADREG21;        /* AddrOffset = 0x054 */
    uint32 PADREG22;        /* AddrOffset = 0x058 */
    uint32 PADREG23;        /* AddrOffset = 0x05C */
    uint32 PADREG24;        /* AddrOffset = 0x060 */
    uint32 PADREG25;        /* AddrOffset = 0x064 */
    uint32 PADREG26;        /* AddrOffset = 0x068 */
    uint32 PADREG27;        /* AddrOffset = 0x06C */
    uint32 PADREG28;        /* AddrOffset = 0x070 */
    uint32 PADREG29;        /* AddrOffset = 0x074 */
    uint32 PADREG30;        /* AddrOffset = 0x078 */
    uint32 PADREG31;        /* AddrOffset = 0x07C */
    uint32 PADREG32;        /* AddrOffset = 0x080 */
    uint32 PADREG33;        /* AddrOffset = 0x084 */
    uint32 PADREG34;        /* AddrOffset = 0x088 */
    uint32 PADREG35;        /* AddrOffset = 0x08C */
    uint32 PADREG36;        /* AddrOffset = 0x090 */
    uint32 PADREG37;        /* AddrOffset = 0x094 */
    uint32 PADREG38;        /* AddrOffset = 0x098 */
    uint32 PADREG39;        /* AddrOffset = 0x09C */
    uint32 PADREG40;        /* AddrOffset = 0x0A0 */
    uint32 PADREG41;        /* AddrOffset = 0x0A4 */
    uint32 PADREG42;        /* AddrOffset = 0x0A8 */
    uint32 PADREG43;        /* AddrOffset = 0x0AC */
    uint32 PADREG44;        /* AddrOffset = 0x0B0 */
    uint32 PADREG45;        /* AddrOffset = 0x0B4 */
    uint32 PADREG46;        /* AddrOffset = 0x0B8 */
    uint32 PADREG47;        /* AddrOffset = 0x0BC */
    uint32 PADREG48;        /* AddrOffset = 0x0C0 */
    uint32 PADREG49;        /* AddrOffset = 0x0C4 */
    uint32 PADREG50;        /* AddrOffset = 0x0C8 */
    uint32 PADREG51;        /* AddrOffset = 0x0CC */
    uint32 PADREG52;        /* AddrOffset = 0x0D0 */
    uint32 PADREG53;        /* AddrOffset = 0x0D4 */
    uint32 PADREG54;        /* AddrOffset = 0x0D8 */
    uint32 PADREG55;        /* AddrOffset = 0x0DC */
    uint32 PADREG56;        /* AddrOffset = 0x0E0 */
    uint32 PADREG57;        /* AddrOffset = 0x0E4 */
    uint32 PADREG58;        /* AddrOffset = 0x0E8 */
    uint32 PADREG59;        /* AddrOffset = 0x0EC */
    uint32 PADREG60;        /* AddrOffset = 0x0F0 */
    uint32 PADREG61;        /* AddrOffset = 0x0F4 */
    uint32 PADREG62;        /* AddrOffset = 0x0F8 */
    uint32 PADREG63;        /* AddrOffset = 0x0FC */
    uint32 PBIST_A0;        /* AddrOffset = 0x100 */
    uint32 PBIST_A1;        /* AddrOffset = 0x104 */
    uint32 PBIST_A2;        /* AddrOffset = 0x108 */
    uint32 PBIST_A3;        /* AddrOffset = 0x10C */
    uint32 PBIST_L0;        /* AddrOffset = 0x110 */
    uint32 PBIST_L1;        /* AddrOffset = 0x114 */
    uint32 PBIST_L2;        /* AddrOffset = 0x118 */
    uint32 PBIST_L3;        /* AddrOffset = 0x11C */
    uint32 PBIST_DD10;      /* AddrOffset = 0x120 */
    uint32 PBIST_DE10;      /* AddrOffset = 0x124 */
    uint32 PADREG64;        /* AddrOffset = 0x128 */
    uint32 PADREG65;        /* AddrOffset = 0x12C */
    uint32 PBIST_CA0;       /* AddrOffset = 0x130 */
    uint32 PBIST_CA1;       /* AddrOffset = 0x134 */
    uint32 PBIST_CA2;       /* AddrOffset = 0x138 */
    uint32 PBIST_CA3;       /* AddrOffset = 0x13C */
    uint32 PBIST_CL0;       /* AddrOffset = 0x140 */
    uint32 PBIST_CL1;       /* AddrOffset = 0x144 */
    uint32 PBIST_CL2;       /* AddrOffset = 0x148 */
    uint32 PBIST_CL3;       /* AddrOffset = 0x14C */
    uint32 PBIST_CI0;       /* AddrOffset = 0x150 */
    uint32 PBIST_CI1;       /* AddrOffset = 0x154 */
    uint32 PBIST_CI2;       /* AddrOffset = 0x158 */
    uint32 PBIST_CI3;       /* AddrOffset = 0x15C */
    uint32 PBIST_RAMT;      /* AddrOffset = 0x160 */
    uint32 PBIST_DLR;       /* AddrOffset = 0x164 */
    uint32 PBIST_CMS;       /* AddrOffset = 0x168 */
    uint32 PBIST_PC;        /* AddrOffset = 0x16C */
    uint32 PBIST_SCR1;      /* AddrOffset = 0x170 */
    uint32 PBIST_SCR4;      /* AddrOffset = 0x174 */
    uint32 PBIST_CS;        /* AddrOffset = 0x178 */
    uint32 PBIST_FDLY;      /* AddrOffset = 0x17C */
    uint32 PBIST_PACT;      /* AddrOffset = 0x180 */
    uint32 PBIST_ID;        /* AddrOffset = 0x184 */
    uint32 PBIST_OVR;       /* AddrOffset = 0x188 */
    uint32 PADREG66;        /* AddrOffset = 0x18C */
    uint32 PBIST_FSFR0;     /* AddrOffset = 0x190 */
    uint32 PBIST_FSFR1;     /* AddrOffset = 0x194 */
    uint32 PBIST_FSRCR0;    /* AddrOffset = 0x198 */
    uint32 PBIST_FSRCR1;    /* AddrOffset = 0x19C */
    uint32 PBIST_FSRA0;     /* AddrOffset = 0x1A0 */
    uint32 PBIST_FSRA1;     /* AddrOffset = 0x1A4 */
    uint32 PBIST_FSRDL0;    /* AddrOffset = 0x1A8 */
    uint32 PADREG67;        /* AddrOffset = 0x1AC */
    uint32 PBIST_FSRDL1;    /* AddrOffset = 0x1B0 */
    uint32 PBIST_MARGIN;    /* AddrOffset = 0x1B4 */
    uint32 PBIST_WRENZ;     /* AddrOffset = 0x1B8 */
    uint32 PBIST_PGS;       /* AddrOffset = 0x1BC */
    uint32 PBIST_ROM;       /* AddrOffset = 0x1C0 */
    uint32 PBIST_ALGO;      /* AddrOffset = 0x1C4 */
    uint32 PBIST_RINFOL;    /* AddrOffset = 0x1C8 */
    uint32 PBIST_RINFOU;    /* AddrOffset = 0x1CC */
} pbistBASE_t;

/* Crc Register Frame Definition */
/** @struct crcBase
*   @brief CRC Register Frame Definition
*
*   This type is used to access the CRC Registers.
*/
/** @typedef crcBASE_t
*   @brief CRC Register Frame Type Definition
*
*   This type is used to access the CRC Registers.
*/
/*LDRA_INSPECTED 4 X : MISRAC_2012_R.5.7 */
/* "Reason - Tool issue " */
typedef volatile struct crcBaseReg
{
    uint32     CTRL0;           /**< 0x0000: Global Control Register 0                           */
    uint32     rvd1;            /**< 0x0004: reserved                                            */
    uint32     CTRL1;           /**< 0x0008: Global Control Register 1                           */
    uint32     rvd2;            /**< 0x000C: reserved                                            */
    uint32     CTRL2;           /**< 0x0010: Global Control Register 2                           */
    uint32     rvd3;            /**< 0x0014: reserved                                            */
    uint32     INTS;            /**< 0x0018: Interrupt Enable Set Register                       */
    uint32     rvd4;            /**< 0x001C: reserved                                            */
    uint32     INTR;            /**< 0x0020: Interrupt Enable Reset Register                     */
    uint32     rvd5;            /**< 0x0024: reserved                                            */
    uint32     STATUS;          /**< 0x0028: Interrupt Status Register                           */
    uint32     rvd6;            /**< 0x002C: reserved                                            */
    uint32     INT_OFFSET_REG;  /**< 0x0030: Interrupt Offset                                    */
    uint32     rvd7;            /**< 0x0034: reserved                                            */
    uint32     CRC_BUSY;        /**< 0x0038: CRC Busy Register                                   */
    uint32     rvd8;            /**< 0x003C: reserved                                            */
    uint32     PCOUNT_REG1;     /**< 0x0040: Pattern Counter Preload Register1                   */
    uint32     SCOUNT_REG1;     /**< 0x0044: Sector Counter Preload Register1                    */
    uint32     CURSEC_REG1;     /**< 0x0048: Current Sector Register 1                           */
    uint32     WDTOPLD1;        /**< 0x004C: Channel 1 Watchdog Timeout Preload Register A       */
    uint32     BCTOPLD1;        /**< 0x0050: Channel 1 Block Complete Timeout Preload Register B */
    uint32     rvd9[3];         /**< 0x0054: reserved                                            */
    uint32     PSA_SIGREGL1;    /**< 0x0060: Channel 1 PSA signature low register                */
    uint32     PSA_SIGREGH1;    /**< 0x0064: Channel 1 PSA signature high register               */
    uint32     REGL1;           /**< 0x0068: Channel 1 CRC value low register                    */
    uint32     REGH1;           /**< 0x006C: Channel 1 CRC value high register                   */
    uint32     PSA_SECSIGREGL1; /**< 0x0070: Channel 1 PSA sector signature low register         */
    uint32     PSA_SECSIGREGH1; /**< 0x0074: Channel 1 PSA sector signature high register        */
    uint32     RAW_DATAREGL1;   /**< 0x0078: Channel 1 Raw Data Low Register                     */
    uint32     RAW_DATAREGH1;   /**< 0x007C: Channel 1 Raw Data High Register                    */
    uint32     PCOUNT_REG2;     /**< 0x0080: CRC Pattern Counter Preload Register2               */
    uint32     SCOUNT_REG2;     /**< 0x0084: Sector Counter Preload Register2                    */
    uint32     CURSEC_REG2;     /**< 0x0088: Current Sector Register 2                           */
    uint32     WDTOPLD2;        /**< 0x008C: Channel 2 Watchdog Timeout Preload Register A       */
    uint32     BCTOPLD2;        /**< 0x0090: Channel 2 Block Complete Timeout Preload Register B */
    uint32     rvd10[3];        /**< 0x0094: reserved                                            */
    uint32     PSA_SIGREGL2;    /**< 0x00A0: Channel 2 PSA signature low register                */
    uint32     PSA_SIGREGH2;    /**< 0x00A4: Channel 2 PSA signature high register               */
    uint32     REGL2;           /**< 0x00A8: Channel 2 CRC value low register                    */
    uint32     REGH2;           /**< 0x00AC: Channel 2 CRC value high register                   */
    uint32     PSA_SECSIGREGL2; /**< 0x00B0: Channel 2 PSA sector signature low register         */
    uint32     PSA_SECSIGREGH2; /**< 0x00B4: Channel 2 PSA sector signature high register        */
    uint32     RAW_DATAREGL2;   /**< 0x00B8: Channel 2 Raw Data Low Register                     */
    uint32     RAW_DATAREGH2;   /**< 0x00BC: Channel 2 Raw Data High Register                    */
    uint32     PCOUNT_REG3;     /**< 0x00C0: CRC Pattern Counter Preload Register3               */
    uint32     SCOUNT_REG3;     /**< 0x00C4: Sector Counter Preload Register3                    */
    uint32     CURSEC_REG3;     /**< 0x00C8: Current Sector Register3                            */
    uint32     WDTOPLD3;        /**< 0x00CC: Channel 3 Watchdog Timeout Preload Register A       */
    uint32     BCTOPLD3;        /**< 0x00D0: Channel 3 Block Complete Timeout Preload Register B */
    uint32     rvd11[3];        /**< 0x00D4: reserved                                            */
    uint32     PSA_SIGREGL3;    /**< 0x00E0: Channel 3 PSA signature low register                */
    uint32     PSA_SIGREGH3;    /**< 0x00E4: Channel 3 PSA signature high register               */
    uint32     REGL3;           /**< 0x00E8: Channel 3 CRC value low register                    */
    uint32     REGH3;           /**< 0x00EC: Channel 3 CRC value high register                   */
    uint32     PSA_SECSIGREGL3; /**< 0x00F0: Channel 3 PSA sector signature low register         */
    uint32     PSA_SECSIGREGH3; /**< 0x00F4: Channel 3 PSA sector signature high register        */
    uint32     RAW_DATAREGL3;   /**< 0x00F8: Channel 3 Raw Data Low Register                     */
    uint32     RAW_DATAREGH3;   /**< 0x00FC: Channel 3 Raw Data High Register                    */
    uint32     PCOUNT_REG4;     /**< 0x0100: CRC Pattern Counter Preload Register4               */
    uint32     SCOUNT_REG4;     /**< 0x0104: Sector Counter Preload Register4                    */
    uint32     CURSEC_REG4;     /**< 0x0108: Current Sector Register4                            */
    uint32     WDTOPLD4;        /**< 0x010C: Channel 4 Watchdog Timeout Preload Register A       */
    uint32     BCTOPLD4;        /**< 0x0110: Channel 4 Block Complete Timeout Preload Register B */
    uint32     rvd12[3];        /**< 0x0114: reserved                                            */
    uint32     PSA_SIGREGL4;    /**< 0x0120: Channel 4 PSA signature low register                */
    uint32     PSA_SIGREGH4;    /**< 0x0124: Channel 4 PSA signature high register               */
    uint32     REGL4;           /**< 0x0128: Channel 4 CRC value low register                    */
    uint32     REGH4;           /**< 0x012C: Channel 4 CRC value high register                   */
    uint32     PSA_SECSIGREGL4; /**< 0x0130: Channel 4 PSA sector signature low register         */
    uint32     PSA_SECSIGREGH4; /**< 0x0134: Channel 4 PSA sector signature high register        */
    uint32     RAW_DATAREGL4;   /**< 0x0138: Channel 4 Raw Data Low Register                     */
    uint32     RAW_DATAREGH4;   /**< 0x013C: Channel 4 Raw Data High Register                    */
    uint32     BUS_SEL;         /**< 0x0140: CRC bus select                                      */

}crcBASE_t;

/** @typedef gpadcBASE_t
*   @brief GPADC Register Type Definition
*
*   This type is used to access the GPADC Registers.
*/
typedef volatile struct gpadcBaseReg
{
	uint32 r_Reg0;        /* Offset = 0x000 */
	uint32 r_Reg1;        /* Offset = 0x004 */
	uint32 r_Reg2;        /* Offset = 0x008 */
	uint32 r_Reg3;        /* Offset = 0x00C */
	uint32 r_PacketRamAdd[4];        /* Offset = 0x010 - 0x1C */
	uint32 r_Reg8;        /* Offset = 0x020 */
	uint32 r_Reg9;        /* Offset = 0x024 */
	uint32 r_Reg10;        /* Offset = 0x028 */
	uint32 r_Reg11;        /* Offset = 0x02C */
	uint32 r_Reg12;        /* Offset = 0x030 */
	uint32 r_Reg13;        /* Offset = 0x034 */
	uint32 r_Reg14;        /* Offset = 0x038 */
	uint32 r_Reg15;        /* Offset = 0x03C */
	uint32 r_Reg16;        /* Offset = 0x040 */
	uint32 r_Reg17;        /* Offset = 0x044 */
	uint32 r_Reg18;        /* Offset = 0x048 */
	uint32 r_Reg19;        /* Offset = 0x04C */
	uint32 r_Reg20;        /* Offset = 0x050 */
	uint32 r_Reg21;        /* Offset = 0x054 */
	uint32 r_Reg22;        /* Offset = 0x058 */
} gpadcBASE_t;

typedef struct {
    volatile uint32	PID;
	volatile uint8	Resv_16[12];
	volatile uint32	EFUSE_DIEID0;
	volatile uint32	EFUSE_DIEID1;
	volatile uint32	EFUSE_DIEID2;
	volatile uint32	EFUSE_DIEID3;
	volatile uint32	EFUSE_UID0;
	volatile uint32	EFUSE_UID1;
	volatile uint32	EFUSE_UID2;
	volatile uint32	EFUSE_UID3;
	volatile uint32	EFUSE_DEVICE_TYPE;
	volatile uint32	EFUSE_FROM0_CHECKSUM;
	volatile uint32	EFUSE_JTAG_USERCODE_ID;
	volatile uint8	Resv_1024[964];
	volatile uint32	EFUSE0_ROW_61;
	volatile uint32	EFUSE0_ROW_62;
	volatile uint32	EFUSE0_ROW_63;
	volatile uint32	EFUSE1_ROW_5;
	volatile uint32	EFUSE1_ROW_6;
	volatile uint32	EFUSE1_ROW_7;
	volatile uint32	EFUSE1_ROW_8;
	volatile uint32	EFUSE1_ROW_9;
	volatile uint32	EFUSE1_ROW_10;
	volatile uint32	EFUSE1_ROW_11;
	volatile uint32	EFUSE1_ROW_12;
	volatile uint32	EFUSE1_ROW_13;
	volatile uint32	EFUSE1_ROW_14;
	volatile uint32	EFUSE1_ROW_15;
	volatile uint32	EFUSE1_ROW_16;
	volatile uint32	EFUSE1_ROW_17;
	volatile uint32	EFUSE1_ROW_18;
	volatile uint32	EFUSE1_ROW_19;
	volatile uint32	EFUSE1_ROW_20;
	volatile uint32	EFUSE1_ROW_21;
	volatile uint32	EFUSE1_ROW_22;
	volatile uint32	EFUSE1_ROW_23;
	volatile uint32	EFUSE1_ROW_24;
	volatile uint32	EFUSE1_ROW_25;
	volatile uint32	EFUSE1_ROW_26;
	volatile uint32	EFUSE1_ROW_27;
	volatile uint32	EFUSE1_ROW_28;
	volatile uint32	EFUSE1_ROW_29;
	volatile uint32	EFUSE1_ROW_30;
	volatile uint32	EFUSE1_ROW_31;
	volatile uint32	EFUSE1_ROW_32;
	volatile uint32	EFUSE1_ROW_33;
	volatile uint32	EFUSE1_ROW_34;
	volatile uint32	EFUSE1_ROW_35;
	volatile uint32	EFUSE1_ROW_36;
	volatile uint32	EFUSE1_ROW_37;
	volatile uint32	EFUSE1_ROW_38;
	volatile uint32	EFUSE1_ROW_39;
	volatile uint32	EFUSE1_ROW_40;
	volatile uint32	EFUSE1_ROW_41;
	volatile uint32	EFUSE1_ROW_42;
	volatile uint32	EFUSE1_ROW_43;
	volatile uint32	EFUSE1_ROW_44;
	volatile uint32	EFUSE1_ROW_45;
	volatile uint32	EFUSE1_ROW_46;
	volatile uint32	EFUSE1_ROW_47;
	volatile uint32	EFUSE1_ROW_48;
	volatile uint32	EFUSE1_ROW_49;
	volatile uint32	EFUSE1_ROW_50;
	volatile uint32	EFUSE1_ROW_51;
	volatile uint32	EFUSE1_ROW_52;
	volatile uint32	EFUSE1_ROW_53;
	volatile uint32	EFUSE1_ROW_54;
	volatile uint32	EFUSE1_ROW_55;
	volatile uint32	EFUSE1_ROW_56;
	volatile uint8	Resv_1280[36];
	volatile uint32	MAC_ID0;
	volatile uint32	MAC_ID1;
	volatile uint8	Resv_1296[8];
	volatile uint32	TRIM_TEMP_M40C;
	volatile uint32	TRIM_TEMPSENSE_M40C0;
	volatile uint32	TRIM_TEMPSENSE_M40C1;
	volatile uint32	TRIM_TEMP_150C;
	volatile uint32	TRIM_TEMPSENSE_150C0;
	volatile uint32	TRIM_TEMPSENSE_150C1;
	volatile uint32	TRIM_TEMP_30C;
	volatile uint32	TRIM_TEMPSENSE_30C0;
	volatile uint32	TRIM_TEMPSENSE_30C1;
	volatile uint32	N_FACTOR_TEMPSENSE;
	volatile uint32	TSHUT_HOT;
	volatile uint32	TSHUT_COLD;
	volatile uint32	JTAG_ID;
	volatile uint8	Resv_2048[700];
	volatile uint32	EFUSE_OVERRIDE_HSM_HALT_ON_ROM_ECC_ERR_EN;
	volatile uint32	EFUSE_OVERRIDE_MARGINCTRL;
	volatile uint32	EFUSE_OVERRIDE_ADC0_TRIM;
	volatile uint32	EFUSE_OVERRIDE_ADC1_TRIM;
	volatile uint32	EFUSE_OVERRIDE_ADC2_TRIM;
	volatile uint8	Resv_2096[28];
	volatile uint32	EFUSE_OVERRIDE_ADC_CFG_CTRL;
	volatile uint32	EFUSE_OVERRIDE_ADC_CFG0;
	volatile uint32	EFUSE_OVERRIDE_ADC_CFG1;
	volatile uint32	EFUSE_OVERRIDE_ADC_CFG2;
	volatile uint8	Resv_2176[64];
	volatile uint32	EFUSE_OVERRIDE_CSSA0_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA0_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA1_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA1_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA2_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA2_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA3_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA3_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA4_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA4_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA5_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA5_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA6_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA6_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA7_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA7_TRIM;
	volatile uint32	EFUSE_OVERRIDE_CSSA8_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSSA8_TRIM;
	volatile uint8	Resv_2352[104];
	volatile uint32	EFUSE_OVERRIDE_CSS_CFG_CTRL;
	volatile uint32	EFUSE_OVERRIDE_CSS_CFG0;
	volatile uint8	Resv_2364[4];
	volatile uint32	EFUSE_OVERRIDE_DAC_TRIM;
	volatile uint32	EFUSE_OVERRIDE_DAC_CFG;
	volatile uint32	EFUSE_OVERRIDE_REFBUF0_TRIM;
	volatile uint32	EFUSE_OVERRIDE_REFBUF0_CFG;
	volatile uint8	Resv_2400[20];
	volatile uint32	EFUSE_OVERRIDE_PMU_CFG;
	volatile uint32	EFUSE_OVERRIDE_PMU_SPARE_TRIM;
	volatile uint32	EFUSE_OVERRIDE_LDO_TRIM;
	volatile uint32	EFUSE_OVERRIDE_BG_TRIM;
	volatile uint32	EFUSE_OVERRIDE_SFTYMON_THRHLD_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_SFTYMON_THRHLD_TRIM0;
	volatile uint32	EFUSE_OVERRIDE_SFTYMON_THRHLD_TRIM1;
	volatile uint32	EFUSE_SAFETYMON_SPARE;
	volatile uint32	EFUSE_OVERRIDE_TSENSE_TRIM_CTRL;
	volatile uint32	EFUSE_OVERRIDE_TSENSE_TRIM;
	volatile uint32	EFUSE_OVERRIDE_PLL_TRIM;
	volatile uint32	EFUSE_OVERRIDE_RCOSC_TRIM;
	volatile uint32	EFUSE_OVERRIDE_RCOSC_CFG;
	volatile uint32	EFUSE_OVERRIDE_HOPP_MUX;
	volatile uint8	Resv_2564[108];
	volatile uint32	EFUSE_SPARE_0;
	volatile uint32	EFUSE_SPARE_1;
	volatile uint32	EFUSE_SPARE_2;
	volatile uint8	Resv_2816[240];
	volatile uint32	ADC_REFBUF0_CTRL;
	volatile uint8	Resv_2832[12];
	volatile uint32	ADC_REF_COMP_CTRL_CTRL;
	volatile uint32	ADC_REF_GOOD_STATUS_STATUS;
	volatile uint32	ADC_REF_RNG_CTRL;
	volatile uint32	ADC0_OSD_CHEN;
	volatile uint32	ADC1_OSD_CHEN;
	volatile uint32	ADC2_OSD_CHEN;
	volatile uint8	Resv_2880[24];
	volatile uint32	ADC0_OSD_CTRL;
	volatile uint32	ADC1_OSD_CTRL;
	volatile uint32	ADC2_OSD_CTRL;
	volatile uint8	Resv_2912[20];
	volatile uint32	ADC_LOOPBACK_CTRL;
	volatile uint8	Resv_3072[156];
	volatile uint32	VMON_UV;
	volatile uint32	VMON_OV;
	volatile uint32	VMON_CONTROLLER;
	volatile uint32	VMON_CTRL;
	volatile uint32	VMON_STAT;
	volatile uint32	MASK_VMON_ERROR_ESM_H;
	volatile uint32	MASK_VMON_ERROR_ESM_L;
	volatile uint32	VMON_FILTER_CTRL;
	volatile uint32	PMU_COARSE_STAT;
	volatile uint32	PMU_CTRL_EXTREF;
	volatile uint8	Resv_3328[216];
	volatile uint32	TSENSE_CFG;
	volatile uint32	TSENSE_STATUS;
	volatile uint32	TSENSE_STATUS_RAW;
	volatile uint8	Resv_3344[4];
	volatile uint32	TSENSE0_TSHUT;
	volatile uint32	TSENSE0_ALERT;
	volatile uint32	TSENSE0_CNTL;
	volatile uint32	TSENSE0_RESULT;
	volatile uint32	TSENSE0_DATA0;
	volatile uint32	TSENSE0_DATA1;
	volatile uint32	TSENSE0_DATA2;
	volatile uint32	TSENSE0_DATA3;
	volatile uint32	TSENSE0_ACCU;
	volatile uint8	Resv_3392[12];
	volatile uint32	TSENSE1_TSHUT;
	volatile uint32	TSENSE1_ALERT;
	volatile uint32	TSENSE1_CNTL;
	volatile uint32	TSENSE1_RESULT;
	volatile uint32	TSENSE1_DATA0;
	volatile uint32	TSENSE1_DATA1;
	volatile uint32	TSENSE1_DATA2;
	volatile uint32	TSENSE1_DATA3;
	volatile uint32	TSENSE1_ACCU;
	volatile uint8	Resv_3452[24];
	volatile uint32	TSENSE2_RESULT;
	volatile uint8	Resv_3500[44];
	volatile uint32	TSENSE3_RESULT;
	volatile uint8	Resv_3520[16];
	volatile uint32	ICSSM1_GPIO_OUT_CTRL;
	volatile uint32	MASK_ANA_ISO;
	volatile uint32	CMPSSA_LOOPBACK_CTRL;
	volatile uint8	Resv_3584[52];
	volatile uint32	DFT_ATB_GLOBALEN_ADC_CSS;
	volatile uint32	DFT_ATB0_MASTEREN_ADC_CSS_DAC;
	volatile uint32	DFT_ATB1_MASTEREN_ADC_CSS_DAC;
	volatile uint32	DFT_PMU_REFSYS_SAFETY;
	volatile uint32	DFT_ANA_DTB_ENABLES;
	volatile uint32	DFT_ADC_CHSEL_OV_CTRL_VALUE;
	volatile uint32	DFT_DAC_CTRL;
	volatile uint32	DFT_CSS0_CTRL;
	volatile uint32	DFT_CSS1_CTRL;
	volatile uint32	DFT_CSS2_CTRL;
	volatile uint8	Resv_3632[8];
	volatile uint32	DFT_RAMP_DACL;
	volatile uint32	DFT_REFBUF_CTRL;
	volatile uint32	DFT_ODP_ATB_LOOPBACK_CTRL;
	volatile uint32	DFT_SOC_DTB_MUX_SEL;
	volatile uint32	DFT_TEMPSENSE_CTRL;
	volatile uint32	DFT_CTRL_1;
	volatile uint32	DFT_CTRL_2;
	volatile uint32	DFT_CTRL_3;
	volatile uint32	DFT_CTRL_4;
	volatile uint32	DFT_CTRL_5;
	volatile uint8	Resv_3680[8];
	volatile uint32	DFT_ADC0_CTRL;
	volatile uint32	DFT_ADC1_CTRL;
	volatile uint32	DFT_ADC2_CTRL;
	volatile uint32	DFT_SDADC_CLKBUF_CTRL;
	volatile uint32	DFT_SDADC_RESOLVEREF_SEL;
	volatile uint32	DFT_SDADC;
	volatile uint8	Resv_3844[140];
	volatile uint32	PROBE_BUS_SEL0;
	volatile uint32	PROBE_BUS_SEL1;
	volatile uint8	Resv_3904[52];
	volatile uint32	HW_SPARE_RW0;
	volatile uint32	HW_SPARE_RW1;
	volatile uint32	HW_SPARE_RW2;
	volatile uint32	HW_SPARE_RW3;
	volatile uint32	HW_SPARE_PORZ_RW0;
	volatile uint32	HW_SPARE_PORZ_RW1;
	volatile uint8	Resv_3968[40];
	volatile uint32	HW_SPARE_RO0;
	volatile uint32	HW_SPARE_RO1;
	volatile uint32	HW_SPARE_RO2;
	volatile uint32	HW_SPARE_RO3;
	volatile uint8	Resv_4032[48];
	volatile uint32	HW_SPARE_WPH;
	volatile uint32	HW_SPARE_REC;
	volatile uint32	HW_SPARE_REC0;
	volatile uint32	HW_SPARE_REC1;
	volatile uint32	EFUSE_VPP_EN;
	volatile uint8	Resv_4104[52];
	volatile uint32	LOCK0_KICK0;
	volatile uint32	LOCK0_KICK1;
	volatile uint32	INTR_RAW_STATUS;
	volatile uint32	INTR_ENABLED_STATUS_CLEAR;
	volatile uint32	INTR_ENABLE;
	volatile uint32	INTR_ENABLE_CLEAR;
	volatile uint32	EOI;
	volatile uint32	FAULT_ADDRESS;
	volatile uint32	FAULT_TYPE_STATUS;
	volatile uint32	FAULT_ATTR_STATUS;
	volatile uint32	FAULT_CLEAR;
} topCtrlBASE_t;
/************************************************************************************************/
/*                          Macro definitions                                                       */
/*                                                                                              */
/************************************************************************************************/


/************************************************************************************************/
/*              Register Base                                               */
/*                                                                                              */
/************************************************************************************************/
#define toprcmREG   ((toprcmBASE_t*)0x53200000U)
#define mssrcmREG   ((mssrcmBASE_t*)0x53208000)
#define ctrlREG     ((ctrlBASE_t*)0x50D00000)
#define vimREG      ((vimBASE_t *)0x50F00000U)
#define esmREG      ((esmBASE_t *)0x52D00000U)
#define cccAREG     ((cccBASE_t *)0xFFFFF8D0U)
#define cccBREG     ((cccBASE_t *)0xFFFFF8E0U)
#define qspiAREG    ((qspiBASE_t *)0xC0800000U)
#define pbistREG    ((pbistBASE_t *)0xFFFFE400U)
#define crcREG      ((crcBASE_t *)0xFE000000U)
#define gpadcREG    ((gpadcBASE_t *)0x3F79800U)
#define topctrlREG  ((topCtrlBASE_t *)0x50D80000U)

#define KICK0_UNLOCK_VAL                 (0x83E70B13U)
#define KICK1_UNLOCK_VAL                 (0x95A4F1E0U)

#define KICK0_LOCK_VAL_MCU               (0x00000000U)
#define KICK1_LOCK_VAL_MCU               (0x00000000U)
#define KICK0_UNLOCK_VAL_MCU             (0x01234567U)
#define KICK1_UNLOCK_VAL_MCU             (0x0FEDCBA8U)

#define MSS_CPSW_CONTROL_REG             (0x860U)
#define MSS_IOCFGKICK0                   (0x00001008U)
#define MSS_IOCFGKICK1                   (0x0000100CU)

/* PIN P1, OSPI0_CSN0 functionality */
#define PINP1_GPIO0                            0X000U


/* PIN R3, OSPI0_CSN1  functionality */
#define PINR3_GPIO1                            0X004U


/* PIN N2, OSPI0_CLK functionality */
#define PINN2_GPIO2                            0X008U
      

/* PIN N1, OSPI0_D0 functionality */
#define PINN1_GPIO3                            0X0CU

/* PIN N4,OSPI0_D1 functionality */
#define PINN4_GPIO4                             0X010U


/* PIN M4, OSPI0_D2 functionality */
#define PINM4_GPIO5                             0X14U


/* PIN P3, OSPI0_D3 functionality */
#define PINP3_GPIO6                             0X18U


/* PIN M1, MCAN0_RX functionality */
#define PINM1_GPIO7                          0X1CU

/* PIN L1, MCAN0_TX functionality */
#define PINL1_GPIO8                          0X20U


/* PIN L2, MCAN1_RX functionality */
#define PINL2_GPIO9                          0X24U


/* PIN K1, MCAN1_TX functionality */
#define PINK1_GPIO10                          0X28U


/* PIN C11, SPI0_CS0 functionality */
#define PINC11_GPIO11                       0X02CU

/* PIN A11, SPI0_CLK functionality */
#define PINA11_GPIO12                          0X030U

/*PIN C10, SPI0_D0 functionality */
#define PINC10_GPIO13                           0X034U

/* PIN B11, SPI0_D1 functionality */
#define PINB11_GPIO14                           0X38U

/* PIN C9, SPI1_CS0 functionality */
#define PINC9_GPIO15                           0X03CU

/* PIN A10, SPI1_CLK functionality */
#define PINA10_GPIO16                          0X40U

/* PIN B10, SPI1_D0 functionality */
#define PINB10_GPIO17                          0X44U

/* PIN D9, SPI1_D1 functionality */
#define PIND9_GPIO18                           0X48U

/* PIN A9, LIN1_RXD functionality */
#define PINA9_GPIO19                          0X4CU


/* PIN B9, LIN1_TXD functionality */
#define PINB9_GPIO20                         0X50U


/* PIN B8, LIN2_RXD functionality */
#define PINB8_GPIO21                       0X54U

/* PIN A8, LIN2_TXD functionality */
#define PINA8_GPIO22                          0X58U

/* PIN D7, I2C1_SCL functionality */
#define PIND7_GPIO23                          0X5CU

/* PIN C8, I2C1_SDA functionality */
#define PINC8_GPIO24                          0X060U

/* PIN C7, UART0_RTSN functionality */
#define PINC7_GPIO25                          0X064U

/* PIN B7, UART0_CTSN functionality */
#define PINB7_GPIO26                          0X068U

/* PIN A7, UART0_RXD functionality */
#define PINA7_GPIO27                          0X06CU

/* PIN A6, UART0_TXD functionality */
#define PINA6_GPIO28                          0X070U

/* PIN R17, RGMII1_RXC functionality */
#define PINR17_GPIO29                          0X074U

/* PIN R18, RGMII1_RX_CTL functionality */
#define PINR18_GPIO30                          0X78U

/* PIN U17, RGMII1_RD0 functionality */
#define PINU17_GPIO31                           0X07CU

/* PIN T17, RGMII1_RD1 functionality */
#define PINT17_GPIO32                           0X80U

/* PIN U18, RGMII1_RD2 functionality */
#define PINU18_GPIO33                          0X084U

/* PIN T18, RGMII1_RD3 functionality */
#define PINT18_GPIO34                          0X88U

/* PIN N18, RGMII1_TXC functionality */
#define PINN18_GPIO35                           0X08CU

/* PIN M18, RGMII1_TX_CTL functionality */
#define PINM18_GPIO36                           0X90U

/* PIN P16, RGMII1_TD0 functionality */
#define PINP16_GPIO37                          0X094U

/* PIN P17, RGMII1_TD1 functionality */
#define PINP17_GPIO38                          0X098U

/* PIN P18, RGMII1_TD2 functionality */
#define PINP18_GPIO39                           0X9CU

/* PIN N17, RGMII1_TD3 functionality */
#define PINN17_GPIO40                         0XA0U

/* PIN N16, MDIO_MDIO functionality */
#define PINN16_GPIO41                         0XA4U

/* PIN M17, MDIO_MDC functionality */
#define PINM17_GPIO42                          0XA8U

/* PIN B2, EPWM0_A functionality */
#define PINB2_GPIO43                           0XACU

/* PIN B1, EPWM0_B functionality */
#define PINB1_GPIO44                           0XB0U

/* PIN D3, EPWM1_A functionality */
#define PIND3_GPIO45                           0XB4U

/* PIN D2, EPWM1_B functionality */
#define PIND2_GPIO46                           0XB8U

/* PIN C2, EPWM2_A  functionality */
#define PINC2_GPIO47                            0XBCU

/* PIN C1, EPWM2_B functionality */
#define PINC1_GPIO48                           0XC0U

/* PIN E2, EPWM3_A functionality */
#define PINE2_GPIO49                          0XC4U

/* PIN E3, PADAI functionality */
#define PINE3_GPIO50                          0XC8U

/* PIN D1, EPWM4_A functionality */
#define PIND1_GPIO51                           0XCCU

/* PIN E4, EPWM4_B functionality */
#define PINE4_GPIO52                           0XD0U

/* PIN F2, EPWM5_A functionality */
#define PINF2_GPIO53                           0XD4U

/* PIN G2, EPWM5_B functionality */
#define PING2_GPIO54                           0XD8U

/* PIN E1, EPWM6_A functionality */
#define PINE1_GPIO55                           0XDCU

/* PIN F3, PADAO functionality */
#define PINF3_GPIO56                           0XE0U             

/* PIN F4, PADAP functionality */
#define PINF4_GPIO57                           0XE4U      

/* PIN F1, PADAQ functionality */
#define PINF1_GPIO58                           0XE8U

/* PIN G3, EPWM8_A functionality */
#define PING3_GPIO59                           0XECU

/* PIN H2, EPWM8_B functionality */
#define PINH2_GPIO60                           0XF0U

/* PIN G1, PADAT functionality */
#define PING1_GPIO61                           0XF4U

/* PIN J2,EPWM9_B functionality */
#define PINJ2_GPIO62                           0XF8U

/* PIN G4,GPIO63 functionality */
#define PING4_GPIO63                                  0XFCU

/* PIN J3,GPIO64 functionality */
#define PINJ3_GPIO64                                  0X100U

/* PIN H1,GPIO65 functionality */
#define PINH1_GPIO65                                  0X104U

/* PIN J1,GPIO66 functionality */
#define PINJ1_GPIO66                                  0X108U

/* PIN K2,PR1_PRU0_GPIO0 functionality */
#define   PINK2_GPIO67                        0X10CU         

/* PIN J4,PR1_PRU0_GPIO1 functionality */
#define   PINJ4_GPIO68                        0X110U

/* PIN K4,PR1_PRU0_GPIO2 functionality */
#define   PINK4_GPIO69                        0X114U

/* PIN K3,PR1_PRU0_GPIO9 functionality */
#define   PINK3_GPIO70                        0X118U

/* PIN V17,PR1_PRU1_GPIO0 functionality */
#define   PINV17_GPIO71                        0X11CU

/* PIN T16,PR1_PRU1_GPIO1 functionality */
#define   PINT16_GPIO72                        0X120U

/* PIN P15,PR1_PRU1_GPIO2 functionality */
#define   PINP15_GPIO73                        0X124U

/* PIN R16,PR1_PRU1_GPIO9 functionality */
#define   PINR16_GPIO74                        0X128U
/* PIN L3, UART1_RXD functionality */
#define PINL3_GPIO75                          0X12CU


/* PIN M3, UART1_TXD functionality */
#define PINM3_GPIO76                          0X0130U


/* PIN B6, MMC_CLK functionality */
#define PINB6_GPIO77                          0X134U

/* PIN A4, MMC_CMD functionality */
#define PINA4_GPIO78                          0X138U

/* PIN B5, MMC_DAT0 functionality */
#define PINB5_GPIO79                          0X13CU

/* PIN B4, MMC_DAT1 functionality */
#define PINB4_GPIO80                          0X140U

/* PIN A3, MMC_DAT2 functionality */
#define PINA3_GPIO81                          0X144U

/* PIN A2, MMC_DAT3 functionality */
#define PINA2_GPIO82                          0X148U

/* PIN C6, MMC_SDWP functionality */
#define PINC6_GPIO83                          0X14CU

/* PIN A5, MMC_SDCD functionality */
#define PINA5_GPIO84                          0X150U

/* PIN L17, PR0_MDIO_MDIO functionality */
#define PINL17_GPIO85                          0X154U

/* PIN L18, PR0_MDIO_MDC functionality */
#define PINL18_GPIO86                          0X158U

/* PIN G17, PADCR functionality */
#define PING17_GPIO87                          0X15CU

/* PIN F17, PADCU functionality */
#define PINF17_GPIO88                          0X160U

/* PIN G18, PADCV functionality */
#define PING18_GPIO89                          0X164U

/* PIN G15, PADCT functionality */
#define PING15_GPIO90                          0X168U

/* PIN K15, PADCS functionality */
#define PINK15_GPIO91                          0X16CU

/* PIN K16, PADCQ functionality */
#define PINK16_GPIO92                          0X170U

/* PIN K17, PADCM functionality */
#define PINK17_GPIO93                          0X174U

/* PIN K18, PADCN functionality */
#define PINK18_GPIO94                          0X178U

/* PIN J18, PADCO functionality */
#define PINJ18_GPIO95                          0X17CU

/* PIN J17, PADCP functionality */
#define PINJ17_GPIO96                          0X180U

/* PIN H18, PADDB functionality */
#define PINH18_GPIO97                           0X184U

/* PIN L16, PADDA functionality */
#define PINL16_GPIO98                           0X188U

/* PIN M16, PRU1_GPIO11 functionality */
#define PINM16_GPIO99                          0X18CU

/* PIN M15, PADCX functionality */
#define PINM15_GPIO100                          0X190U

/* PIN H17, PADCY functionality */
#define PINH17_GPIO101                          0X194U

/* PIN H16, PADCZ functionality */
#define PINH16_GPIO102                          0X198U

/* PIN F15, PADDH functionality */
#define PINF15_GPIO103                          0X19CU

/* PIN C18, PADDK functionality */
#define PINC18_GPIO104                          0X1A0U

/* PIN D17, PADDL functionality */
#define PIND17_GPIO105                          0X1A4U

/* PIN D18, PADDJ functionality */
#define PIND18_GPIO106                          0X1A8U

/* PIN E16, PADDI functionality */
#define PINE16_GPIO107                          0X1ACU

/* PIN F16, PADDG functionality */
#define PINF16_GPIO108                           0X1B0U

/* PIN F18, PADDC functionality */
#define PINF18_GPIO109                          0X1B4U

/* PIN G16, PADDD functionality */
#define PING16_GPIO110                          0X1B8U

/* PIN E17, PADDE functionality */
#define PINE17_GPIO111                           0X1BCU

/* PIN E18, PADDF functionality */
#define PINE18_GPIO112                           0X1C0U

/* PIN C16, PADDR functionality */
#define PINC16_GPIO113                          0X1C4U

/* PIN A17, PADDQ functionality */
#define PINA17_GPIO114                          0X1C8U

/* PIN B18, PADDM functionality */
#define PINB18_GPIO115                           0X1CCU

/* PIN B17, PADDN functionality */
#define PINB17_GPIO116                          0X1D0U

/* PIN D16, PADDO functionality */
#define PIND16_GPIO117                          0X1D4U

/* PIN C17, PADDP functionality */
#define PINC17_GPIO118                          0X1D8U

/* PIN D15, PADDT functionality */
#define PIND15_GPIO119                          0X1DCU

/* PIN C15, PADDS functionality */
#define PINC15_GPIO120                         0X1E0U

/* PIN P2, PADBL functionality */
#define PINP2_GPIO121                         0X1E4U

/* PIN B16, PADEP functionality */
#define PINB16_GPIO122                          0X01E8U

/* PIN D14, PADET functionality */
#define PIND14_GPIO123                           0X1ECU

/* PIN A16, PADEQ functionality */
#define PINA16_GPIO124                          0X01F0U

/* PIN D13, PADEU functionality */
#define PIND13_GPIO125                             0X1F4U

/* PIN B15, PADER functionality */
#define PINB15_GPIO126                          0X1F8U

/* PIN C13, PADEV functionality */
#define PINC13_GPIO127                            0X01FCU

/* PIN A15, PADES functionality */
#define PINA15_GPIO128                          0X200U

/* PIN C14, PADEW functionality */
#define PINC14_GPIO129                          0X0204U

/* PIN B14, PADBH functionality */
#define PINB14_GPIO130                           0X208U

/* PIN A14, PADBI functionality */
#define PINA14_GPIO131                           0X20CU

/* PIN C12, PADBK functionality */
#define PINC12_GPIO132                          0X210U

/* PIN D11, PADBJ functionality */
#define PIND11_GPIO133                          0X214U

/* PIN B13, PADBN functionality */
#define PINB13_GPIO134                          0X218U

/* PIN A13 PADBM functionality */
#define PINA13_GPIO135                          0X21CU
/* PIN B12 GPIO136 functionality */
#define   PINB12_GPIO136                                0X220U
/* PIN A12 GPIO137 functionality */
#define   PINA12_GPIO137                                0X224U
/* PIN M2 CLKOUT0 functionality */
#define   PINM2_GPIO138                                0X228U                  
/* PIN V2 USB0_DP functionality */
#define   PINV2_GPIO139                                0X22CU
/* PIN U3 USB0_DM functionality */
#define   PINU3_GPIO140                                0X230U

/* PIN C3, PADFP functionality */
#define PINC3_WARMRSTn                          0X0234U
            
/* PIN D4, PADEO functionality */
#define PIND4_SAFETY_ERRORn                        0X238U

/* PIN C5, PADFG functionality */
#define PINC5_TDI                             0X23CU

/* PIN C4, PADFE functionality */
#define PINC4_TDO                             0X240U

/* PIN B3, PADFF functionality */
#define PINB3_TCK                              0X248U

/* PIN D5, PADFI functionality */
#define PIND5_TMS                             0X244U


/* WARM_RST_CAUSE_CLR */
#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_MASK               (0x00000007U)
#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_SHIFT              (0x00000000U)
#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_RESETVAL           (0x00000000U)
#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_MAX                (0x00000007U)
#define TOP_RCM_WARM_RST_CAUSE_CLR_RESETVAL                 (0x00000000U)

/* General pin configurations */
#define PIN_SLEW_BITPOS                 10U
#define PIN_SLEW_CONTROL_MASK          (~(uint32)((uint32)0x1U << PIN_SLEW_BITPOS))
#define SLEW_HIGH                      ((uint32)((uint32)0x1U << PIN_SLEW_BITPOS))
#define SLEW_LOW                       ((uint32)((uint32)0x0U << PIN_SLEW_BITPOS))

#define PIN_PULL_BITPOS                 0x9U
#define PIN_PULL_SELECT_MASK            (~(uint32)((uint32)0x1U << PIN_PULL_BITPOS))
#define PULLUP_EN                       ((uint32)((uint32)0x1U << PIN_PULL_BITPOS))
#define PULLDOWN_EN                     ((uint32)((uint32)0x0U << PIN_PULL_BITPOS))


#define PIN_PULL_INHIBIT_BITPOS         0x8U
#define PIN_PULL_INHIBIT_MASK           (~(uint32)((uint32)0x1U << PIN_PULL_INHIBIT_BITPOS))
#define PIN_PULL_INHIBIT_DISABLE         ((uint32)((uint32)0x1U << PIN_PULL_INHIBIT_BITPOS))
#define PIN_PULL_INHIBIT_ENABLE        ((uint32)((uint32)0x0U << PIN_PULL_INHIBIT_BITPOS))

#define OUTPUT_EN_BITPOS                0x7U
#define PIN_OUTEN_MASK                  (~(uint32)((uint32)0x1U << OUTPUT_EN_BITPOS))
#define OUTPUT_EN                       ((uint32)((uint32)0x1U << OUTPUT_EN_BITPOS))
#define OUTPUT_DIS                      ((uint32)((uint32)0x0U << OUTPUT_EN_BITPOS))
#define OUTEN_RETAIN_HW_CTRL            0x2U

#define OUTEN_OVRRIDE_BITPOS            0x6U
#define PIN_OUTEN_OVRRIDE_MASK          (~(uint32)((uint32)0x1U << OUTEN_OVRRIDE_BITPOS))
#define OUTEN_OVRRIDE_EN                ((uint32)((uint32)0x1U << OUTEN_OVRRIDE_BITPOS))


#define INPUT_EN_BITPOS                 0x5U
#define PIN_INPUTEN_MASK                (~(uint32)((uint32)0x1U << INPUT_EN_BITPOS))
#define INPUT_EN                        ((uint32)((uint32)0x1U << INPUT_EN_BITPOS))
#define INPUT_DIS                       ((uint32)((uint32)0x0U << INPUT_EN_BITPOS))
#define INPEN_RETAIN_HW_CTRL            0x2U

#define INPEN_OVRRIDE_BITPOS            0x4U
#define PIN_INPEN_OVRRIDE_MASK          (~(uint32)((uint32)0x1U << INPEN_OVRRIDE_BITPOS))
#define INPEN_OVRRIDE_EN                ((uint32)((uint32)0x1U << INPEN_OVRRIDE_BITPOS))


#define PIN_FUNCTION_SEL_MASK          (~(uint32)((uint32)0xFU))

#define INPUT_INVERSION_BITPOS        20U
#define INPUT_INVERSION_MASK          (~(uint32)((uint32)0x1U << INPUT_INVERSION_BITPOS))
#define INVERSION                     0x1
#define NON_INVERSION                 0x0

/** QUAL_TYPE_BITPOS - 18 and 19 bit positions **/
#define QUAL_TYPE_BITPOS              18U
#define QUAL_TYPE_MASK                (~(uint32)((uint32)0x03U << QUAL_TYPE_BITPOS))
#define SYNC                          0x1
#define THREE_SAMPLE_QUAL             0x2
#define SIX_SAMPLE_QUAL               0x3
#define ASYNC                         0x4

#define HSMASTER_BITPOS               31U
#define HSMASTER_MASK                (~(uint32)((uint32)0x1U << HSMASTER_BITPOS))

#define HSMODE_BITPOS                 30U
#define HSMODE_MASK                   (~(uint32)((uint32)0x1U << HSMODE_BITPOS))

#define GPIO_SEL_BITPOS              16U
#define GPIO_SEL_MASK                (~(uint32)((uint32)0x03U << GPIO_SEL_BITPOS))
/*MCU Reset Reason Value*/

#define MCU_RST_CAUSE_NRST                  (uint32)0x09U
#define MCU_RST_CAUSE_EXT_WARM_RST          (uint32)0x08U
#define MCU_RST_CAUSE_MSS_WARM_RST          (uint32)0xAU
#define MCU_RST_CAUSE_SW_TRIG_WARM_RST      (uint32)0xCU
#define MCU_RST_CAUSE_POWER_ON_RST          (uint32)0x0U


/*! \brief
* SCI BAUD RATE CONST enum
* Baud value = (Clock/(16*(baud rate))) - 1
* 1e6/(30*16*baud_rate)*2^18
*/
#define M_SCI_BAUD_CONST_19200_S18      (28444U)
#define M_SCI_BAUD_CONST_38400_S18      (14222U)
#define M_SCI_BAUD_CONST_57600_S18      (9481U)
#define M_SCI_BAUD_CONST_115200_S18     (4741U)
#define M_SCI_BAUD_CONST_460800_S18     (1185U)
#define M_SCI_BAUD_CONST_921600_S18     (593U)


#define MIBSPI_START_MSG_WR_OFFSET           (0U)
#define FILETYPE_BSS_BUILD                   (0U)
#define FILETYPE_CALIB_DATA                  (1U)
#define FILETYPE_CONFIG_INFO                 (2U)
#define FILETYPE_MSS_BUILD                   (3U)

#define MAGIC_HEADER_BSS_ROM                 (0xB55A03D1U)
#define MAGIC_HEADER_BSS_PATCH               (0xB559A71FU)
#define MAGIC_HEADER_MSS_ROM                 (0x355A03D1U)
#define MAGIC_HEADER_MSS_PATCH               (0x3559A71FU)

#define MAGIC_HEADER_CALIB_DATA              (0xCA11BDA7U)
#define MAGIC_HEADER_CONFIG_INFO             (0xC0F1618FU)


#define MSG_RX_MAX_SIZE                (512U)

/*Clk Gate Enable and Disable Value*/
#define MSS_RCM_CLK_GATE_GATED_RESETVAL    (0x00000000U)
#define MSS_RCM_CLK_GATE_GATED_MASK        (0x00000007U)

#define TOP_RCM_CLK_GATE_GATED_RESETVAL    (0x00000000U)
#define TOP_RCM_CLK_GATE_GATED_MASK        (0x00000007U)

/* Memory initialization selections - MSS */
#define INIT_CR4TCMAMEM                         (uint32)((uint32)1U << 0U)
#define INIT_CR4TCMBMEM                         (uint32)((uint32)1U << 1U)
#define INIT_DMAMEM                             (uint32)((uint32)1U << 2U)
#define INIT_VIMMEM                             (uint32)((uint32)1U << 3U)
#define INIT_SPIAMEM                            (uint32)((uint32)1U << 4U)
#define INIT_SPIBMEM                            (uint32)((uint32)1U << 5U)
#define INIT_DCANMEM                            (uint32)((uint32)1U << 6U)
#define INIT_MSSMBOX4BSSMEM                     (uint32)((uint32)1U << 7U)
#define INIT_BSSMBOX4MSSMEM                     (uint32)((uint32)1U << 8U)
#define INIT_DMA2MEM                            (uint32)((uint32)1U << 9U)
#define INIT_DCANFDMEM                          (uint32)((uint32)1U << 10U)
#define INIT_GEMMBOX4BSSMEM                     (uint32)((uint32)1U << 14U)
#define INIT_GEMMBOX4MSSMEM                     (uint32)((uint32)1U << 15U)
#define INIT_MSSMBOX4GEMMEM                     (uint32)((uint32)1U << 16U)
#define INIT_BSSMBOX4GEMMEM                     (uint32)((uint32)1U << 17U)


#define SPANSION_DEV                  0x01U
#define MACRONIX_DEV                  0xC2U

/** @def QSPI clock control
*   @brief qspi dclock on off
*   @note This value used for clock settings
*/
#define QSPI_CLK_CTRL_CLKEN_DCLOCK_OFF        (0U)

/** @def QSPI_CLK_CTRL_CLKEN_DCLOCK_ON
*   @brief Alias for QSPI clock control dclock on
*/
#define QSPI_CLK_CTRL_CLKEN_DCLOCK_ON         (1U)

/** @def QSPI_CC_REG_DCLK_DIVISOR
*   @brief Alias for QSPI clock divisor
*   @note This value used for QSPI clock settings
*/
#define QSPI_CC_REG_DCLK_DIVISOR              (0x9U)  /* div value = div + 1 */


/** @def QSPI_WLEN_1_BIT
*   @brief Alias for QSPI data word length selection - 1 bit
*/
#define QSPI_WLEN_1_BIT    (0x0U)

/** @def QSPI_WLEN_8_BITS
*   @brief Alias for QSPI data word length selection - 8 bit
*/
#define QSPI_WLEN_8_BITS   (0x7U)

/** @def QSPI_WLEN_16_BITS
*   @brief Alias for QSPI data word length selection - 16 bit
*/
#define QSPI_WLEN_16_BITS  (0xFU)

/** @def QSPI_WLEN_24_BITS
*   @brief Alias for QSPI data word length selection - 24 bit
*/
#define QSPI_WLEN_24_BITS  (0x17U)

/** @def QSPI_WLEN_32_BITS
*   @brief Alias for QSPI data word length selection - 32 bit
*/
#define QSPI_WLEN_32_BITS  (0x1FU)

/** @def QSPI_WLEN_128_BITS
*   @brief Alias for QSPI data word length selection - 128 bit
*/
#define QSPI_WLEN_128_BITS (0x7FU)

/** @def TRANS_CMD_RSV
*   @brief Alias for QSPI PIN Mode Read-Write Command - Reserved
*/
#define TRANS_CMD_RSV      (0x0U)

/** @def TRANS_CMD_4RDS
*   @brief Alias for QSPI PIN Mode Read-Write Command - 4 Pin Read Single
*/
#define TRANS_CMD_4RDS     (0x1U)

/** @def TRANS_CMD_4WRS
*   @brief Alias for QSPI PIN Mode Read-Write Command - 4 Pin Write Single
*/
#define TRANS_CMD_4WRS     (0x2U)

/** @def TRANS_CMD_4RDD
*   @brief Alias for QSPI PIN Mode Read-Write Command - 4 Pin Read Dual
*/
#define TRANS_CMD_4RDD     (0x3U)

/** @def TRANS_CMD_RSV1
*   @brief Alias for QSPI PIN Mode Read-Write Command - Reserved
*/
#define TRANS_CMD_RSV1     (0x4U)

/** @def TRANS_CMD_3RDS
*   @brief Alias for QSPI PIN Mode Read-Write Command - 3 Pin Read Single
*/
#define TRANS_CMD_3RDS     (0x5U)

/** @def TRANS_CMD_3WRS
*   @brief Alias for QSPI PIN Mode Read-Write Command - 3 Pin Write Single
*/
#define TRANS_CMD_3WRS     (0x6U)

/** @def TRANS_CMD_6RDQ
*   @brief Alias for QSPI PIN Mode Read-Write Command - 3 Pin Write Single
*/
#define TRANS_CMD_6RDQ     (0x7U)

/** @def QSPI_FLEN_1_WORD
*   @brief Alias for QSPI data frame length selection - 1 word
*/
#define QSPI_FLEN_1_WORD  (0x0U)

/** @def QSPI_FLEN_2_WORDS
*   @brief Alias for QSPI data frame length selection - 2 word
*/
#define QSPI_FLEN_2_WORDS (0x1U)

/** @def QSPI_FLEN_3_WORDS
*   @brief Alias for QSPI data frame length selection - 3 word
*/
#define QSPI_FLEN_3_WORDS (0x2U)

/** @def QSPI_FLEN_4_WORDS
*   @brief Alias for QSPI data frame length selection - 4 word
*/
#define QSPI_FLEN_4_WORDS (0x3U)

/** @def QSPI_FLEN_5_WORDS
*   @brief Alias for QSPI data frame length selection - 5 word
*/
#define QSPI_FLEN_5_WORDS (0x4U)

/** @def QSPI_FLEN_6_WORDS
*   @brief Alias for QSPI data frame length selection - 6 word
*/
#define QSPI_FLEN_6_WORDS (0x5U)

/** @def QSPI_FLEN_7_WORDS
*   @brief Alias for QSPI data frame length selection - 7 word
*/
#define QSPI_FLEN_7_WORDS (0x6U)

/** @def QSPI_FLEN_8_WORDS
*   @brief Alias for QSPI data frame length selection - 8 word
*/
#define QSPI_FLEN_8_WORDS (0x7U)

/** @enum qspiAddressSpace
*   @brief qspi address space
*   @note This is used for config and memmap mode switch
*/
typedef enum qspiAddressSpace{
    QSPI_CFG_MODE = 0x0U,
    QSPI_MM_MODE  = 0x1U
}qspiAddressSpace_t;

/** @enum qspiRdWrWLen_t
*   @brief QSPI data transfer word length deff
*/
typedef enum{
    QSPI_RDWR_WLEN_1TO32     = 0x1U,
    QSPI_RDWR_WLEN_33TO64    = 0x2U,
    QSPI_RDWR_WLEN_65TO96    = 0x3U,
    QSPI_RDWR_WLEN_97TO128   = 0x4U
}qspiRdWrWLen_t;

/** @struct qspiMEMSETUP
*   @brief used to configure memorymap operation
*
*/
typedef struct
{
    uint32 NUMDBITS;    /* No of dummy bits */
    uint32 WRITECMD;    /* Write mode command */
    uint32 READTYP;        /* normal or dual or quad dead */
    uint32 NUMDBYTES;    /* No of dummy bytes */
    uint32 NUMABYTES;    /* No of address byte for fast read */
    uint32 READCMD;        /* Read mode command */
}qspiMMSetupReg_t;

/** @struct qspi_config_reg
*   @brief used to configure qspi
*
*/
typedef struct
{
    uint32 CONFIG_SPICLKCTRL;
    uint32 CONFIG_SPIDC;
} qspiConfigReg_t;

/** @def QSPI_SPICLKCTRL_CONFIGVALUE
*   @brief Alias for default registers configurations
*
*/
#define QSPI_SPICLKCTRL_CONFIGVALUE     (((uint32)((uint32)QSPI_CLK_CTRL_CLKEN_DCLOCK_ON << 31U)) \
                                        | ((uint32)QSPI_CC_REG_DCLK_DIVISOR))

/** @def QSPI_SPIDC_CONFIGVALUE
*   @brief Alias for
*/
#define QSPI_SPIDC_CONFIGVALUE          ((uint32)((uint32)0U << 27U) \
                                        | (uint32)((uint32)0U << 26U) \
                                        | (uint32)((uint32)0U << 25U) \
                                        | (uint32)((uint32)0U << 24U) \
                                        | (uint32)((uint32)0U << 19U) \
                                        | (uint32)((uint32)0U << 18U) \
                                        | (uint32)((uint32)0U << 17U) \
                                        | (uint32)((uint32)0U << 16U) \
                                        | (uint32)((uint32)0U << 11U) \
                                        | (uint32)((uint32)0U << 10U) \
                                        | (uint32)((uint32)0U << 9U) \
                                        | (uint32)((uint32)0U << 8U) \
                                        | (uint32)((uint32)0U << 3U) \
                                        | (uint32)((uint32)0U << 2U) \
                                        | (uint32)((uint32)0U << 1U) \
                                        | (uint32)((uint32)0U << 0 ))

/**************************************************************************
* Register Macros
**************************************************************************/

/* PID */
#define QSPI_PID                                            (0x0U)

/* SYSCONFIG */
#define QSPI_SYSCONFIG                                      (0x10U)

/* This register contains the raw interrupt status as defined in HL0.8 */
#define QSPI_INTR_STATUS_RAW_SET                            (0x20U)

/* Interrupt Status Enabled/Clear Register This register contains the enabled
 * interrupt status as defined in HL0.8 */
#define QSPI_INTR_STATUS_ENABLED_CLEAR                      (0x24U)

/* Interrupt Enable/Set Register This register contains the enable status as
 * defined in HL0.8 */
#define QSPI_INTR_ENABLE_SET_REG                            (0x28U)

/* Interrupt Enable/Clear Register This register contains the enable status as
 * defined in HL0.8 */
#define QSPI_INTR_ENABLE_CLEAR_REG                          (0x2CU)

/* INTC EOI Register This register contains the EOI vector register contents
 * as defined by HL0.8 */
#define QSPI_INTC_EOI_REG                                   (0x30U)

/* SPI Clock Control (SPICC) Register */
#define QSPI_SPI_CLOCK_CNTRL_REG                            (0x40U)

/* SPI Device Control (SPIDC) */
#define QSPI_SPI_DC_REG                                     (0x44U)

/* SPI Command Register (SPICR) */
#define QSPI_SPI_CMD_REG                                    (0x48U)

/* SPI Status Register (SPISR) */
#define QSPI_SPI_STATUS_REG                                 (0x4CU)

/* SPI Data Register (SPIDR) */
#define QSPI_SPI_DATA_REG                                   (0x50U)

/* Memory Mapped SPI Setup0 Register */
#define QSPI_SPI_SETUP0_REG                                 (0x54U)

/* Memory Mapped SPI Switch Register */
#define QSPI_SPI_SWITCH_REG                                 (0x64U)

/* Memory Mapped SPI Setup1 Register */
#define QSPI_SPI_SETUP1_REG                                 (0x58U)

/* Memory Mapped SPI Setup2 Register */
#define QSPI_SPI_SETUP2_REG                                 (0x5CU)

/* Memory Mapped SPI Setup3 Register */
#define QSPI_SPI_SETUP3_REG                                 (0x60U)

/* SPI Data1 Register (SPIDR1) */
#define QSPI_SPI_DATA_REG_1                                 (0x68U)

/* SPI Data2 Register (SPIDR2) */
#define QSPI_SPI_DATA_REG_2                                 (0x6CU)

/* SPI Data3 Register (SPIDR3) */
#define QSPI_SPI_DATA_REG_3                                 (0x70U)

#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK          (0x00000001U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK          (0x00000002U)

#define QSPI_INTR_STATUS_MASK              					(0x00000003U)

#define QSPI_PID_MINOR_MASK                                 (0x0000003FU)
#define QSPI_PID_MINOR_SHIFT                                (0U)
#define QSPI_PID_MINOR_RESETVAL                             (0x00000000U)
#define QSPI_PID_MINOR_MAX                                  (0x0000003fU)

#define QSPI_PID_CUSTOM_MASK                                (0x000000C0U)
#define QSPI_PID_CUSTOM_SHIFT                               (6U)
#define QSPI_PID_CUSTOM_RESETVAL                            (0x00000000U)
#define QSPI_PID_CUSTOM_MAX                                 (0x00000003U)

#define QSPI_PID_MAJOR_MASK                                 (0x00000700U)
#define QSPI_PID_MAJOR_SHIFT                                (8U)
#define QSPI_PID_MAJOR_RESETVAL                             (0x00000000U)
#define QSPI_PID_MAJOR_MAX                                  (0x00000007U)

#define QSPI_PID_RTL_VERSION_MASK                           (0x0000F800U)
#define QSPI_PID_RTL_VERSION_SHIFT                          (11U)
#define QSPI_PID_RTL_VERSION_RESETVAL                       (0x00000000U)
#define QSPI_PID_RTL_VERSION_MAX                            (0x0000001fU)

#define QSPI_PID_FUNC_MASK                                  (0x0FFF0000U)
#define QSPI_PID_FUNC_SHIFT                                 (16U)
#define QSPI_PID_FUNC_RESETVAL                              (0x00000f40U)
#define QSPI_PID_FUNC_MAX                                   (0x00000fffU)

#define QSPI_PID_RSVD_MASK                                  (0x30000000U)
#define QSPI_PID_RSVD_SHIFT                                 (28U)
#define QSPI_PID_RSVD_RESETVAL                              (0x00000000U)
#define QSPI_PID_RSVD_MAX                                   (0x00000003U)

#define QSPI_PID_SCHEME_MASK                                (0xC0000000U)
#define QSPI_PID_SCHEME_SHIFT                               (30U)
#define QSPI_PID_SCHEME_RESETVAL                            (0x00000001U)
#define QSPI_PID_SCHEME_MAX                                 (0x00000003U)

#define QSPI_PID_RESETVAL                                   (0x4f400000U)

/* SYSCONFIG */

#define QSPI_SYSCONFIG_RSVD_1_MASK                          (0x00000003U)
#define QSPI_SYSCONFIG_RSVD_1_SHIFT                         (0U)
#define QSPI_SYSCONFIG_RSVD_1_RESETVAL                      (0x00000000U)
#define QSPI_SYSCONFIG_RSVD_1_MAX                           (0x00000003U)

#define QSPI_SYSCONFIG_IDLE_MODE_MASK                       (0x0000000CU)
#define QSPI_SYSCONFIG_IDLE_MODE_SHIFT                      (2U)
#define QSPI_SYSCONFIG_IDLE_MODE_RESETVAL                   (0x00000002U)
#define QSPI_SYSCONFIG_IDLE_MODE_FORCE_IDLE                 (0x00000000U)
#define QSPI_SYSCONFIG_IDLE_MODE_NO_IDLE                    (0x00000001U)
#define QSPI_SYSCONFIG_IDLE_MODE_SMART_IDLE                 (0x00000002U)
#define QSPI_SYSCONFIG_IDLE_MODE_SMART_IDLE_WAKEUP_CAPABLE  (0x00000003U)

#define QSPI_SYSCONFIG_RSVD_3_MASK                          (0x00000030U)
#define QSPI_SYSCONFIG_RSVD_3_SHIFT                         (4U)
#define QSPI_SYSCONFIG_RSVD_3_RESETVAL                      (0x00000002U)
#define QSPI_SYSCONFIG_RSVD_3_MAX                           (0x00000003U)

#define QSPI_SYSCONFIG_RSVD_2_MASK                          (0xFFFFFFC0U)
#define QSPI_SYSCONFIG_RSVD_2_SHIFT                         (6U)
#define QSPI_SYSCONFIG_RSVD_2_RESETVAL                      (0x00000000U)
#define QSPI_SYSCONFIG_RSVD_2_MAX                           (0x03ffffffU)

#define QSPI_SYSCONFIG_RESETVAL                             (0x00000028U)

/* INTR_STATUS_RAW_SET */

#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_MASK              (0x00000001U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_SHIFT             (0U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_RESETVAL          (0x00000000U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_READ_INACTIVE     (0x00000000U)
#define QSPI_INTR_STATUS_RAW_SET_FIRQ_RAW_READ_ACTIVE       (0x00000001U)

#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_MASK              (0x00000002U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_SHIFT             (1U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_RESETVAL          (0x00000000U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_READ_INACTIVE     (0x00000000U)
#define QSPI_INTR_STATUS_RAW_SET_WIRQ_RAW_READ_ACTIVE       (0x00000001U)

#define QSPI_INTR_STATUS_RAW_SET_RSVD_MASK                  (0xFFFFFFFCU)
#define QSPI_INTR_STATUS_RAW_SET_RSVD_SHIFT                 (2U)
#define QSPI_INTR_STATUS_RAW_SET_RSVD_RESETVAL              (0x00000000U)
#define QSPI_INTR_STATUS_RAW_SET_RSVD_MAX                   (0x3fffffffU)

#define QSPI_INTR_STATUS_RAW_SET_RESETVAL                   (0x00000000U)
#define QSPI_INTR_STATUS_MASK              					(0x00000003U)
/* INTR_STATUS_ENABLED_CLEAR */

#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_MASK        (0x00000001U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_SHIFT       (0U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_RESETVAL    (0x00000000U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_INACTIVE    (0x00000000U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_FIRQ_ENA_ACTIVE      (0x00000001U)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_MASK        (0x00000002U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_SHIFT       (1U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_RESETVAL    (0x00000000U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_INACTIVE    (0x00000000U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_WIRQ_ENA_ACTIVE      (0x00000001U)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_MASK            (0xFFFFFFFCU)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_SHIFT           (2U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_RESETVAL        (0x00000000U)
#define QSPI_INTR_STATUS_ENABLED_CLEAR_RSVD_MAX             (0x3fffffffU)

#define QSPI_INTR_STATUS_ENABLED_CLEAR_RESETVAL             (0x00000000U)

/* INTR_ENABLE_SET_REG */

#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK          (0x00000001U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_SHIFT         (0U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_RESETVAL      (0x00000000U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_INACTIVE      (0x00000000U)
#define QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_ACTIVE        (0x00000001U)

#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK          (0x00000002U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_SHIFT         (1U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_RESETVAL      (0x00000000U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_INACTIVE      (0x00000000U)
#define QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_ACTIVE        (0x00000001U)

#define QSPI_INTR_ENABLE_SET_REG_RSVD_MASK                  (0xFFFFFFFCU)
#define QSPI_INTR_ENABLE_SET_REG_RSVD_SHIFT                 (2U)
#define QSPI_INTR_ENABLE_SET_REG_RSVD_RESETVAL              (0x00000000U)
#define QSPI_INTR_ENABLE_SET_REG_RSVD_MAX                   (0x3fffffffU)

#define QSPI_INTR_ENABLE_SET_REG_RESETVAL                   (0x00000000U)

/* INTR_ENABLE_CLEAR_REG */

#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_MASK        (0x00000001U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_SHIFT       (0U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_RESETVAL    (0x00000000U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_INACTIVE    (0x00000000U)
#define QSPI_INTR_ENABLE_CLEAR_REG_FIRQ_ENA_CLR_ACTIVE      (0x00000001U)

#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_MASK        (0x00000002U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_SHIFT       (1U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_RESETVAL    (0x00000000U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_INACTIVE    (0x00000000U)
#define QSPI_INTR_ENABLE_CLEAR_REG_WIRQ_ENA_CLR_ACTIVE      (0x00000001U)

#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_MASK                (0xFFFFFFFCU)
#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_SHIFT               (2U)
#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_RESETVAL            (0x00000000U)
#define QSPI_INTR_ENABLE_CLEAR_REG_RSVD_MAX                 (0x3fffffffU)

#define QSPI_INTR_ENABLE_CLEAR_REG_RESETVAL                 (0x00000000U)

/* INTC_EOI_REG */

#define QSPI_INTC_EOI_REG_EOI_VECTOR_MASK                   (0xFFFFFFFFU)
#define QSPI_INTC_EOI_REG_EOI_VECTOR_SHIFT                  (0U)
#define QSPI_INTC_EOI_REG_EOI_VECTOR_RESETVAL               (0x00000000U)
#define QSPI_INTC_EOI_REG_EOI_VECTOR_MAX                    (0xffffffffU)

#define QSPI_INTC_EOI_REG_RESETVAL                          (0x00000000U)

/* SPI_CLOCK_CNTRL_REG */

#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_MASK              (0x0000FFFFU)
#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_SHIFT             (0U)
#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_RESETVAL          (0x00000000U)
#define QSPI_SPI_CLOCK_CNTRL_REG_DCLK_DIV_MAX               (0x0000ffffU)

#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_MASK                  (0x7FFF0000U)
#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_SHIFT                 (16U)
#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_RESETVAL              (0x00000000U)
#define QSPI_SPI_CLOCK_CNTRL_REG_RSVD_MAX                   (0x00007fffU)

#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_MASK                 (0x80000000U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_SHIFT                (31U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_RESETVAL             (0x00000000U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_ON            (0x00000001U)
#define QSPI_SPI_CLOCK_CNTRL_REG_CLKEN_DCLOCK_OFF           (0x00000000U)

#define QSPI_SPI_CLOCK_CNTRL_REG_RESETVAL                   (0x00000000U)

/* SPI_DC_REG */

#define QSPI_SPI_DC_REG_CKP0_MASK                           (0x00000001U)
#define QSPI_SPI_DC_REG_CKP0_SHIFT                          (0U)
#define QSPI_SPI_DC_REG_CKP0_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CKP0_DATA_ACTIVE                    (0x00000001U)
#define QSPI_SPI_DC_REG_CKP0_DATA_INACTIVE                  (0x00000000U)

#define QSPI_SPI_DC_REG_CSP0_MASK                           (0x00000002U)
#define QSPI_SPI_DC_REG_CSP0_SHIFT                          (1U)
#define QSPI_SPI_DC_REG_CSP0_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CSP0_ACTIVE_LOW                     (0x00000000U)
#define QSPI_SPI_DC_REG_CSP0_ACTIVE_HIGH                    (0x00000001U)

#define QSPI_SPI_DC_REG_CKPH0_MASK                          (0x00000004U)
#define QSPI_SPI_DC_REG_CKPH0_SHIFT                         (2U)
#define QSPI_SPI_DC_REG_CKPH0_RESETVAL                      (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_FALLING_EDGE  (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_0_SHIFT_OUT_RISING_EDGE   (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_FALLING_EDGE  (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH0_CKP_1_SHIFT_OUT_RISING_EDGE   (0x00000000U)

#define QSPI_SPI_DC_REG_DD0_MASK                            (0x00000018U)
#define QSPI_SPI_DC_REG_DD0_SHIFT                           (3U)
#define QSPI_SPI_DC_REG_DD0_RESETVAL                        (0x00000000U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_0              (0x00000000U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_1              (0x00000001U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_2              (0x00000002U)
#define QSPI_SPI_DC_REG_DD0_CS_TO_DATA_DELAY_3              (0x00000003U)

#define QSPI_SPI_DC_REG_RSVD_0_MASK                         (0x000000E0U)
#define QSPI_SPI_DC_REG_RSVD_0_SHIFT                        (5U)
#define QSPI_SPI_DC_REG_RSVD_0_RESETVAL                     (0x00000000U)
#define QSPI_SPI_DC_REG_RSVD_0_MAX                          (0x00000007U)

#define QSPI_SPI_DC_REG_CKP1_MASK                           (0x00000100U)
#define QSPI_SPI_DC_REG_CKP1_SHIFT                          (8U)
#define QSPI_SPI_DC_REG_CKP1_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CKP1_DATA_ACTIVE                    (0x00000001U)
#define QSPI_SPI_DC_REG_CKP1_DATA_INACTIVE                  (0x00000000U)

#define QSPI_SPI_DC_REG_CSP1_MASK                           (0x00000200U)
#define QSPI_SPI_DC_REG_CSP1_SHIFT                          (9U)
#define QSPI_SPI_DC_REG_CSP1_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CSP1_ACTIVE_LOW                     (0x00000000U)
#define QSPI_SPI_DC_REG_CSP1_ACTIVE_HIGH                    (0x00000001U)

#define QSPI_SPI_DC_REG_CKPH1_MASK                          (0x00000400U)
#define QSPI_SPI_DC_REG_CKPH1_SHIFT                         (10U)
#define QSPI_SPI_DC_REG_CKPH1_RESETVAL                      (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_0_SHIFT_OUT_FALLING_EDGE  (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_0_SHIFT_OUT_RISING_EDGE   (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_1_SHIFT_OUT_FALLING_EDGE  (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH1_CKP_1_SHIFT_OUT_RISING_EDGE   (0x00000000U)

#define QSPI_SPI_DC_REG_DD1_MASK                            (0x00001800U)
#define QSPI_SPI_DC_REG_DD1_SHIFT                           (11U)
#define QSPI_SPI_DC_REG_DD1_RESETVAL                        (0x00000000U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_0              (0x00000000U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_1              (0x00000001U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_2              (0x00000002U)
#define QSPI_SPI_DC_REG_DD1_CS_TO_DATA_DELAY_3              (0x00000003U)

#define QSPI_SPI_DC_REG_RSVD_1_MASK                         (0x0000E000U)
#define QSPI_SPI_DC_REG_RSVD_1_SHIFT                        (13U)
#define QSPI_SPI_DC_REG_RSVD_1_RESETVAL                     (0x00000000U)
#define QSPI_SPI_DC_REG_RSVD_1_MAX                          (0x00000007U)

#define QSPI_SPI_DC_REG_CKP2_MASK                           (0x00010000U)
#define QSPI_SPI_DC_REG_CKP2_SHIFT                          (16U)
#define QSPI_SPI_DC_REG_CKP2_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CKP2_DATA_ACTIVE                    (0x00000001U)
#define QSPI_SPI_DC_REG_CKP2_DATA_INACTIVE                  (0x00000000U)

#define QSPI_SPI_DC_REG_CSP2_MASK                           (0x00020000U)
#define QSPI_SPI_DC_REG_CSP2_SHIFT                          (17U)
#define QSPI_SPI_DC_REG_CSP2_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CSP2_ACTIVE_LOW                     (0x00000000U)
#define QSPI_SPI_DC_REG_CSP2_ACTIVE_HIGH                    (0x00000001U)

#define QSPI_SPI_DC_REG_CKPH2_MASK                          (0x00040000U)
#define QSPI_SPI_DC_REG_CKPH2_SHIFT                         (18U)
#define QSPI_SPI_DC_REG_CKPH2_RESETVAL                      (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_0_SHIFT_OUT_FALLING_EDGE  (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_0_SHIFT_OUT_RISING_EDGE   (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_1_SHIFT_OUT_FALLING_EDGE  (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH2_CKP_1_SHIFT_OUT_RISING_EDGE   (0x00000000U)

#define QSPI_SPI_DC_REG_DD2_MASK                            (0x00180000U)
#define QSPI_SPI_DC_REG_DD2_SHIFT                           (19U)
#define QSPI_SPI_DC_REG_DD2_RESETVAL                        (0x00000000U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_0              (0x00000000U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_1              (0x00000001U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_2              (0x00000002U)
#define QSPI_SPI_DC_REG_DD2_CS_TO_DATA_DELAY_3              (0x00000003U)

#define QSPI_SPI_DC_REG_RSVD_2_MASK                         (0x00E00000U)
#define QSPI_SPI_DC_REG_RSVD_2_SHIFT                        (21U)
#define QSPI_SPI_DC_REG_RSVD_2_RESETVAL                     (0x00000000U)
#define QSPI_SPI_DC_REG_RSVD_2_MAX                          (0x00000007U)

#define QSPI_SPI_DC_REG_CKP3_MASK                           (0x01000000U)
#define QSPI_SPI_DC_REG_CKP3_SHIFT                          (24U)
#define QSPI_SPI_DC_REG_CKP3_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CKP3_DATA_ACTIVE                    (0x00000001U)
#define QSPI_SPI_DC_REG_CKP3_DATA_INACTIVE                  (0x00000000U)

#define QSPI_SPI_DC_REG_CSP3_MASK                           (0x02000000U)
#define QSPI_SPI_DC_REG_CSP3_SHIFT                          (25U)
#define QSPI_SPI_DC_REG_CSP3_RESETVAL                       (0x00000000U)
#define QSPI_SPI_DC_REG_CSP3_ACTIVE_LOW                     (0x00000000U)
#define QSPI_SPI_DC_REG_CSP3_ACTIVE_HIGH                    (0x00000001U)

#define QSPI_SPI_DC_REG_CKPH3_MASK                          (0x04000000U)
#define QSPI_SPI_DC_REG_CKPH3_SHIFT                         (26U)
#define QSPI_SPI_DC_REG_CKPH3_RESETVAL                      (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_0_SHIFT_OUT_FALLING_EDGE  (0x00000000U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_0_SHIFT_OUT_RISING_EDGE   (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_1_SHIFT_OUT_FALLING_EDGE  (0x00000001U)
#define QSPI_SPI_DC_REG_CKPH3_CKP_1_SHIFT_OUT_RISING_EDGE   (0x00000000U)

#define QSPI_SPI_DC_REG_DD3_MASK                            (0x18000000U)
#define QSPI_SPI_DC_REG_DD3_SHIFT                           (27U)
#define QSPI_SPI_DC_REG_DD3_RESETVAL                        (0x00000000U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_0              (0x00000000U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_1              (0x00000001U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_2              (0x00000002U)
#define QSPI_SPI_DC_REG_DD3_CS_TO_DATA_DELAY_3              (0x00000003U)

#define QSPI_SPI_DC_REG_RSVD_3_MASK                         (0xE0000000U)
#define QSPI_SPI_DC_REG_RSVD_3_SHIFT                        (29U)
#define QSPI_SPI_DC_REG_RSVD_3_RESETVAL                     (0x00000000U)
#define QSPI_SPI_DC_REG_RSVD_3_MAX                          (0x00000007U)

#define QSPI_SPI_DC_REG_RESETVAL                            (0x00000000U)

/* SPI_CMD_REG */

#define QSPI_SPI_CMD_REG_FLEN_MASK                          (0x00000FFFU)
#define QSPI_SPI_CMD_REG_FLEN_SHIFT                         (0U)
#define QSPI_SPI_CMD_REG_FLEN_RESETVAL                      (0x00000000U)
#define QSPI_SPI_CMD_REG_FLEN_MAX                           (0x00000fffU)

#define QSPI_SPI_CMD_REG_RSVD_MASK                          (0x00003000U)
#define QSPI_SPI_CMD_REG_RSVD_SHIFT                         (12U)
#define QSPI_SPI_CMD_REG_RSVD_RESETVAL                      (0x00000000U)
#define QSPI_SPI_CMD_REG_RSVD_MAX                           (0x00000003U)

#define QSPI_SPI_CMD_REG_WIRQ_MASK                          (0x00004000U)
#define QSPI_SPI_CMD_REG_WIRQ_SHIFT                         (14U)
#define QSPI_SPI_CMD_REG_WIRQ_RESETVAL                      (0x00000000U)
#define QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_ENABLE         (0x00000001U)
#define QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE        (0x00000000U)

#define QSPI_SPI_CMD_REG_FIRQ_MASK                          (0x00008000U)
#define QSPI_SPI_CMD_REG_FIRQ_SHIFT                         (15U)
#define QSPI_SPI_CMD_REG_FIRQ_RESETVAL                      (0x00000000U)
#define QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_ENABLE        (0x00000001U)
#define QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE       (0x00000000U)

#define QSPI_SPI_CMD_REG_CMD_MASK                           (0x00070000U)
#define QSPI_SPI_CMD_REG_CMD_SHIFT                          (16U)
#define QSPI_SPI_CMD_REG_CMD_RESETVAL                       (0x00000000U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE           (0x00000001U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE          (0x00000002U)
#define QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL             (0x00000003U)
#define QSPI_SPI_CMD_REG_CMD_THREE_PIN_READ_SINGLE          (0x00000005U)
#define QSPI_SPI_CMD_REG_CMD_THREE_PIN_WRITE_SINGLE         (0x00000006U)
#define QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD              (0x00000007U)

#ifdef MODIFICATION
#define QSPI_SPI_CMD_REG_WLEN_MASK                          (0x00F80000U)
#else
#define QSPI_SPI_CMD_REG_WLEN_MASK                          (0x03F80000U)
#endif
#define QSPI_SPI_CMD_REG_WLEN_SHIFT                         (19U)
#define QSPI_SPI_CMD_REG_WLEN_RESETVAL                      (0x00000000U)
#define QSPI_SPI_CMD_REG_WLEN_MAX                           (0x0000001fU)

#define QSPI_SPI_CMD_REG_RSVD_2_MASK                        (0x0F000000U)
#define QSPI_SPI_CMD_REG_RSVD_2_SHIFT                       (24U)
#define QSPI_SPI_CMD_REG_RSVD_2_RESETVAL                    (0x00000000U)
#define QSPI_SPI_CMD_REG_RSVD_2_MAX                         (0x0000000fU)

#define QSPI_SPI_CMD_REG_CSNUM_MASK                         (0x30000000U)
#define QSPI_SPI_CMD_REG_CSNUM_SHIFT                        (28U)
#define QSPI_SPI_CMD_REG_CSNUM_RESETVAL                     (0x00000000U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_0                         (0x00000000U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_1                         (0x00000001U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_2                         (0x00000002U)
#define QSPI_SPI_CMD_REG_CSNUM_CS_3                         (0x00000003U)

#define QSPI_SPI_CMD_REG_RSVD_3_MASK                        (0xC0000000U)
#define QSPI_SPI_CMD_REG_RSVD_3_SHIFT                       (30U)
#define QSPI_SPI_CMD_REG_RSVD_3_RESETVAL                    (0x00000000U)
#define QSPI_SPI_CMD_REG_RSVD_3_MAX                         (0x00000003U)

#define QSPI_SPI_CMD_REG_RESETVAL                           (0x00000000U)

/* SPI_STATUS_REG */

#define QSPI_SPI_STATUS_REG_BUSY_MASK                       (0x00000001U)
#define QSPI_SPI_STATUS_REG_BUSY_SHIFT                      (0U)
#define QSPI_SPI_STATUS_REG_BUSY_RESETVAL                   (0x00000000U)
#define QSPI_SPI_STATUS_REG_BUSY_IDLE                       (0x00000000U)
#define QSPI_SPI_STATUS_REG_BUSY_BUSY                       (0x00000001U)

#define QSPI_SPI_STATUS_REG_WC_MASK                         (0x00000002U)
#define QSPI_SPI_STATUS_REG_WC_SHIFT                        (1U)
#define QSPI_SPI_STATUS_REG_WC_RESETVAL                     (0x00000000U)
#define QSPI_SPI_STATUS_REG_WC_WORD_TRANSFER_NOT_COMPLETE   (0x00000000U)
#define QSPI_SPI_STATUS_REG_WC_WORD_TRANSFER_COMPLETE       (0x00000001U)

#define QSPI_SPI_STATUS_REG_FC_MASK                         (0x00000004U)
#define QSPI_SPI_STATUS_REG_FC_SHIFT                        (2U)
#define QSPI_SPI_STATUS_REG_FC_RESETVAL                     (0x00000000U)
#define QSPI_SPI_STATUS_REG_FC_FRAME_TRANSFER_NOT_COMPLETE  (0x00000000U)
#define QSPI_SPI_STATUS_REG_FC_FRAME_TRANSFER_COMPLETE      (0x00000001U)

#define QSPI_SPI_STATUS_REG_RSVD_MASK                       (0x0000FFF8U)
#define QSPI_SPI_STATUS_REG_RSVD_SHIFT                      (3U)
#define QSPI_SPI_STATUS_REG_RSVD_RESETVAL                   (0x00000000U)
#define QSPI_SPI_STATUS_REG_RSVD_MAX                        (0x00001fffU)

#define QSPI_SPI_STATUS_REG_WDCNT_MASK                      (0x0FFF0000U)
#define QSPI_SPI_STATUS_REG_WDCNT_SHIFT                     (16U)
#define QSPI_SPI_STATUS_REG_WDCNT_RESETVAL                  (0x00000000U)
#define QSPI_SPI_STATUS_REG_WDCNT_MAX                       (0x00000fffU)

#define QSPI_SPI_STATUS_REG_RSVD_2_MASK                     (0xF0000000U)
#define QSPI_SPI_STATUS_REG_RSVD_2_SHIFT                    (28U)
#define QSPI_SPI_STATUS_REG_RSVD_2_RESETVAL                 (0x00000000U)
#define QSPI_SPI_STATUS_REG_RSVD_2_MAX                      (0x0000000fU)

#define QSPI_SPI_STATUS_REG_RESETVAL                        (0x00000000U)

/* SPI_DATA_REG */

#define QSPI_SPI_DATA_REG_DATA_MASK                         (0xFFFFFFFFU)
#define QSPI_SPI_DATA_REG_DATA_SHIFT                        (0U)
#define QSPI_SPI_DATA_REG_DATA_RESETVAL                     (0x00000000U)
#define QSPI_SPI_DATA_REG_DATA_MAX                          (0xffffffffU)

#define QSPI_SPI_DATA_REG_RESETVAL                          (0x00000000U)

/* SPI_SETUP0_REG */

#define QSPI_SPI_SETUP0_REG_RCMD_MASK                       (0x000000FFU)
#define QSPI_SPI_SETUP0_REG_RCMD_SHIFT                      (0U)
#define QSPI_SPI_SETUP0_REG_RCMD_RESETVAL                   (0x00000003U)
#define QSPI_SPI_SETUP0_REG_RCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_MASK                (0x00000300U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_SHIFT               (8U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_RESETVAL            (0x00000002U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_ONE_BYTE            (0x00000000U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_TWO_BYTES           (0x00000001U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_THREE_BYTES         (0x00000002U)
#define QSPI_SPI_SETUP0_REG_NUM_A_BYTES_FOUR_BYTES          (0x00000003U)

#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_MASK                (0x00000C00U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_SHIFT               (10U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_RESETVAL            (0x00000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS      (0x00000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS          (0x00000001U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_16_BITS         (0x00000002U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_24_BITS         (0x00000003U)

#define QSPI_SPI_SETUP0_REG_READ_TYPE_MASK                  (0x00003000U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_SHIFT                 (12U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_RESETVAL              (0x00000000U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ           (0x00000000U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ             (0x00000001U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ_TYPE      (0x00000002U)
#define QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ             (0x00000003U)

#define QSPI_SPI_SETUP0_REG_RSVD_1_MASK                     (0x0000C000U)
#define QSPI_SPI_SETUP0_REG_RSVD_1_SHIFT                    (14U)
#define QSPI_SPI_SETUP0_REG_RSVD_1_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP0_REG_RSVD_1_MAX                      (0x00000003U)

#define QSPI_SPI_SETUP0_REG_WCMD_MASK                       (0x00FF0000U)
#define QSPI_SPI_SETUP0_REG_WCMD_SHIFT                      (16U)
#define QSPI_SPI_SETUP0_REG_WCMD_RESETVAL                   (0x00000002U)
#define QSPI_SPI_SETUP0_REG_WCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP0_REG_RSVD_2_MASK                     (0xE0000000U)
#define QSPI_SPI_SETUP0_REG_RSVD_2_SHIFT                    (29U)
#define QSPI_SPI_SETUP0_REG_RSVD_2_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP0_REG_RSVD_2_MAX                      (0x00000007U)

#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_MASK                 (0x1F000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_SHIFT                (24U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_RESETVAL             (0x00000000U)
#define QSPI_SPI_SETUP0_REG_NUM_D_BITS_MAX                  (0x0000001fU)

#define QSPI_SPI_SETUP0_REG_RESETVAL                        (0x00020203U)

/* SPI_SWITCH_REG */

#define QSPI_SPI_SWITCH_REG_MMPT_S_MASK                     (0x00000001U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_SHIFT                    (0U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT             (0x00000000U)
#define QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT              (0x00000001U)

#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MASK                  (0x00000002U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_SHIFT                 (1U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_RESETVAL              (0x00000000U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MM_MODE_INTR_DISABLED  (0x00000000U)
#define QSPI_SPI_SWITCH_REG_MM_INT_EN_MM_MODE_INTR_ENABLED  (0x00000001U)

#define QSPI_SPI_SWITCH_REG_RSVD_MASK                       (0xFFFFFFFCU)
#define QSPI_SPI_SWITCH_REG_RSVD_SHIFT                      (2U)
#define QSPI_SPI_SWITCH_REG_RSVD_RESETVAL                   (0x00000000U)
#define QSPI_SPI_SWITCH_REG_RSVD_MAX                        (0x3fffffffU)

#define QSPI_SPI_SWITCH_REG_RESETVAL                        (0x00000000U)

/* SPI_SETUP1_REG */

#define QSPI_SPI_SETUP1_REG_RCMD_MASK                       (0x000000FFU)
#define QSPI_SPI_SETUP1_REG_RCMD_SHIFT                      (0U)
#define QSPI_SPI_SETUP1_REG_RCMD_RESETVAL                   (0x00000003U)
#define QSPI_SPI_SETUP1_REG_RCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_MASK                (0x00000300U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_SHIFT               (8U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_RESETVAL            (0x00000002U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_ONE_BYTE            (0x00000000U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_TWO_BYTES           (0x00000001U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_THREE_BYTES         (0x00000002U)
#define QSPI_SPI_SETUP1_REG_NUM_A_BYTES_FOUR_BYTES          (0x00000003U)

#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_MASK                (0x00000C00U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_SHIFT               (10U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_RESETVAL            (0x00000000U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_NUM_D_BITS      (0x00000000U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_8_BITS          (0x00000001U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_16_BITS         (0x00000002U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BYTES_USE_24_BITS         (0x00000003U)

#define QSPI_SPI_SETUP1_REG_READ_TYPE_MASK                  (0x00003000U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_SHIFT                 (12U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_RESETVAL              (0x00000000U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_NORMAL_READ           (0x00000000U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_DUAL_READ             (0x00000001U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_NORMAL_READ_TYPE      (0x00000002U)
#define QSPI_SPI_SETUP1_REG_READ_TYPE_QUAD_READ             (0x00000003U)

#define QSPI_SPI_SETUP1_REG_RSVD_1_MASK                     (0x0000C000U)
#define QSPI_SPI_SETUP1_REG_RSVD_1_SHIFT                    (14U)
#define QSPI_SPI_SETUP1_REG_RSVD_1_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP1_REG_RSVD_1_MAX                      (0x00000003U)

#define QSPI_SPI_SETUP1_REG_WCMD_MASK                       (0x00FF0000U)
#define QSPI_SPI_SETUP1_REG_WCMD_SHIFT                      (16U)
#define QSPI_SPI_SETUP1_REG_WCMD_RESETVAL                   (0x00000002U)
#define QSPI_SPI_SETUP1_REG_WCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP1_REG_RSVD_2_MASK                     (0xE0000000U)
#define QSPI_SPI_SETUP1_REG_RSVD_2_SHIFT                    (29U)
#define QSPI_SPI_SETUP1_REG_RSVD_2_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP1_REG_RSVD_2_MAX                      (0x00000007U)

#define QSPI_SPI_SETUP1_REG_NUM_D_BITS_MASK                 (0x1F000000U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BITS_SHIFT                (24U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BITS_RESETVAL             (0x00000000U)
#define QSPI_SPI_SETUP1_REG_NUM_D_BITS_MAX                  (0x0000001fU)

#define QSPI_SPI_SETUP1_REG_RESETVAL                        (0x00020203U)

/* SPI_SETUP2_REG */

#define QSPI_SPI_SETUP2_REG_RCMD_MASK                       (0x000000FFU)
#define QSPI_SPI_SETUP2_REG_RCMD_SHIFT                      (0U)
#define QSPI_SPI_SETUP2_REG_RCMD_RESETVAL                   (0x00000003U)
#define QSPI_SPI_SETUP2_REG_RCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_MASK                (0x00000300U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_SHIFT               (8U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_RESETVAL            (0x00000002U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_ONE_BYTE            (0x00000000U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_TWO_BYTES           (0x00000001U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_THREE_BYTES         (0x00000002U)
#define QSPI_SPI_SETUP2_REG_NUM_A_BYTES_FOUR_BYTES          (0x00000003U)

#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_MASK                (0x00000C00U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_SHIFT               (10U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_RESETVAL            (0x00000000U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_NUM_D_BITS      (0x00000000U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_8_BITS          (0x00000001U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_16_BITS         (0x00000002U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BYTES_USE_24_BITS         (0x00000003U)

#define QSPI_SPI_SETUP2_REG_READ_TYPE_MASK                  (0x00003000U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_SHIFT                 (12U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_RESETVAL              (0x00000000U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_NORMAL_READ           (0x00000000U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_DUAL_READ             (0x00000001U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_NORMAL_READ_TYPE      (0x00000002U)
#define QSPI_SPI_SETUP2_REG_READ_TYPE_QUAD_READ             (0x00000003U)

#define QSPI_SPI_SETUP2_REG_RSVD_1_MASK                     (0x0000C000U)
#define QSPI_SPI_SETUP2_REG_RSVD_1_SHIFT                    (14U)
#define QSPI_SPI_SETUP2_REG_RSVD_1_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP2_REG_RSVD_1_MAX                      (0x00000003U)

#define QSPI_SPI_SETUP2_REG_WCMD_MASK                       (0x00FF0000U)
#define QSPI_SPI_SETUP2_REG_WCMD_SHIFT                      (16U)
#define QSPI_SPI_SETUP2_REG_WCMD_RESETVAL                   (0x00000002U)
#define QSPI_SPI_SETUP2_REG_WCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP2_REG_RSVD_2_MASK                     (0xE0000000U)
#define QSPI_SPI_SETUP2_REG_RSVD_2_SHIFT                    (29U)
#define QSPI_SPI_SETUP2_REG_RSVD_2_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP2_REG_RSVD_2_MAX                      (0x00000007U)

#define QSPI_SPI_SETUP2_REG_NUM_D_BITS_MASK                 (0x1F000000U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BITS_SHIFT                (24U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BITS_RESETVAL             (0x00000000U)
#define QSPI_SPI_SETUP2_REG_NUM_D_BITS_MAX                  (0x0000001fU)

#define QSPI_SPI_SETUP2_REG_RESETVAL                        (0x00020203U)

/* SPI_SETUP3_REG */

#define QSPI_SPI_SETUP3_REG_RCMD_MASK                       (0x000000FFU)
#define QSPI_SPI_SETUP3_REG_RCMD_SHIFT                      (0U)
#define QSPI_SPI_SETUP3_REG_RCMD_RESETVAL                   (0x00000003U)
#define QSPI_SPI_SETUP3_REG_RCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_MASK                (0x00000300U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_SHIFT               (8U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_RESETVAL            (0x00000002U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_ONE_BYTE            (0x00000000U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_TWO_BYTES           (0x00000001U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_THREE_BYTES         (0x00000002U)
#define QSPI_SPI_SETUP3_REG_NUM_A_BYTES_FOUR_BYTES          (0x00000003U)

#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_MASK                (0x00000C00U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_SHIFT               (10U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_RESETVAL            (0x00000000U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_NUM_D_BITS      (0x00000000U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_8_BITS          (0x00000001U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_16_BITS         (0x00000002U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BYTES_USE_24_BITS         (0x00000003U)

#define QSPI_SPI_SETUP3_REG_READ_TYPE_MASK                  (0x00003000U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_SHIFT                 (12U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_RESETVAL              (0x00000000U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_NORMAL_READ           (0x00000000U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_DUAL_READ             (0x00000001U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_NORMAL_READ_TYPE      (0x00000002U)
#define QSPI_SPI_SETUP3_REG_READ_TYPE_QUAD_READ             (0x00000003U)

#define QSPI_SPI_SETUP3_REG_RSVD_1_MASK                     (0x0000C000U)
#define QSPI_SPI_SETUP3_REG_RSVD_1_SHIFT                    (14U)
#define QSPI_SPI_SETUP3_REG_RSVD_1_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP3_REG_RSVD_1_MAX                      (0x00000003U)

#define QSPI_SPI_SETUP3_REG_WCMD_MASK                       (0x00FF0000U)
#define QSPI_SPI_SETUP3_REG_WCMD_SHIFT                      (16U)
#define QSPI_SPI_SETUP3_REG_WCMD_RESETVAL                   (0x00000002U)
#define QSPI_SPI_SETUP3_REG_WCMD_MAX                        (0x000000ffU)

#define QSPI_SPI_SETUP3_REG_RSVD_2_MASK                     (0xE0000000U)
#define QSPI_SPI_SETUP3_REG_RSVD_2_SHIFT                    (29U)
#define QSPI_SPI_SETUP3_REG_RSVD_2_RESETVAL                 (0x00000000U)
#define QSPI_SPI_SETUP3_REG_RSVD_2_MAX                      (0x00000007U)

#define QSPI_SPI_SETUP3_REG_NUM_D_BITS_MASK                 (0x1F000000U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BITS_SHIFT                (24U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BITS_RESETVAL             (0x00000000U)
#define QSPI_SPI_SETUP3_REG_NUM_D_BITS_MAX                  (0x0000001fU)

#define QSPI_SPI_SETUP3_REG_RESETVAL                        (0x00020203U)

/* SPI_DATA_REG_1 */

#define QSPI_SPI_DATA_REG_1_DATA_MASK                       (0xFFFFFFFFU)
#define QSPI_SPI_DATA_REG_1_DATA_SHIFT                      (0U)
#define QSPI_SPI_DATA_REG_1_DATA_RESETVAL                   (0x00000000U)
#define QSPI_SPI_DATA_REG_1_DATA_MAX                        (0xffffffffU)

#define QSPI_SPI_DATA_REG_1_RESETVAL                        (0x00000000U)

/* SPI_DATA_REG_2 */

#define QSPI_SPI_DATA_REG_2_DATA_MASK                       (0xFFFFFFFFU)
#define QSPI_SPI_DATA_REG_2_DATA_SHIFT                      (0U)
#define QSPI_SPI_DATA_REG_2_DATA_RESETVAL                   (0x00000000U)
#define QSPI_SPI_DATA_REG_2_DATA_MAX                        (0xffffffffU)

#define QSPI_SPI_DATA_REG_2_RESETVAL                        (0x00000000U)

/* SPI_DATA_REG_3 */

#define QSPI_SPI_DATA_REG_3_DATA_MASK                       (0xFFFFFFFFU)
#define QSPI_SPI_DATA_REG_3_DATA_SHIFT                      (0U)
#define QSPI_SPI_DATA_REG_3_DATA_RESETVAL                   (0x00000000U)
#define QSPI_SPI_DATA_REG_3_DATA_MAX                        (0xffffffffU)

#define QSPI_SPI_DATA_REG_3_RESETVAL                        (0x00000000U)

#define INTR_STATUS_RAW_SET  								(0x20U)
#define SYSCONFIG 											(0x10U)
#define SPI_DC_REG 											(0x44U)
#define SPI_CLOCK_CNTRL_REG 								(0x40U)
#define SPI_STATUS_REG										(0x4CU)
#define SPI_SWITCH_REG										(0x64U)
#define INTR_ENABLE_SET_REG									(0x28U)
#define INTR_ENABLE_CLEAR_REG								(0x2CU)
#define INTR_STATUS_ENABLED_CLEAR							(0x24U)
#define INTC_EOI_REG										(0x30U)
#define SPI_DATA_REG										(0x50U)
#define SPI_DATA_REG_1										(0x68U)
#define SPI_DATA_REG_2										(0x6CU)
#define SPI_DATA_REG_3										(0x70U)
#define SPI_CMD_REG											(0x48U)
#define SPI_SETUP0_REG										(0x54U)


#ifdef __cplusplus
}
#endif
#endif  /* HW_CTRL_CORE_H_ */

