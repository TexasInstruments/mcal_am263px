/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2022 Texas Instruments Incorporated
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
     uint32    QSPI0_CSN0;
     uint32    QSPI0_CSN1; 	  
     uint32    QSPI0_CLK;          	  
     uint32    QSPI0_D0;          	      
     uint32    QSPI0_D1;         	      
     uint32    QSPI0_D2;         	      
     uint32    QSPI0_D3;         	      
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
     uint32	   MDIO0_MDIO;             
     uint32	   MDIO0_MDC;             
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
     uint32	   EPWM10_A;                
     uint32	   EPWM10_B;                
     uint32	   EPWM11_A;                
     uint32	   EPWM11_B;                
     uint32	   EPWM12_A;                
     uint32	   EPWM12_B;                
     uint32	   EPWM13_A;                
     uint32	   EPWM13_B;                
     uint32	   EPWM14_A;                
     uint32	   EPWM14_B;                
     uint32	   EPWM15_A;                
     uint32	   EPWM15_B;	              
     uint32	   UART1_RXD;               
     uint32	   UART1_TXD;               
     uint32	   MMC0_CLK;                
     uint32	   MMC0_CMD;                
     uint32	   MMC0_D0;                
     uint32	   MMC0_D1;                
     uint32	   MMC0_D2;                
     uint32	   MMC0_D3;                
     uint32	   MMC0_WP;                
     uint32	   MMC0_CD;               
     uint32	   PR0_MDIO0_MDIO;          
     uint32	   PR0_MDIO0_MDC;          
     uint32	   PRU0_GIO5;          
     uint32	   PRU0_GIO9;          
     uint32	   PRU0_GIO10;          
     uint32	   PRU0_GIO8;          
     uint32	   PRU0_GIO6;          
     uint32	   PRU0_GIO4;          
     uint32	   PRU0_GIO0;          
     uint32	   PRU0_GIO1;          
     uint32	   PRU0_GIO2;          
     uint32	   PRU0_GIO3;          
     uint32	   PRU0_GIO16;          
     uint32	   PRU0_GIO15;          
     uint32	   PRU0_GIO11;          
     uint32	   PRU0_GIO12;          
     uint32	   PRU0_GIO13;          
     uint32	   PRU0_GIO14;        
     uint32	   PRU1_GIO5;	          
     uint32	   PRU1_GIO9;	          
     uint32	   PRU1_GIO10;    	      
     uint32	   PRU1_GIO8;           
     uint32	   PRU1_GIO6;       	  
     uint32	   PRU1_GIO4;         	  
     uint32	   PRU1_GIO0;             
     uint32	   PRU1_GIO1;        	  
     uint32	   PRU1_GIO2;     	      
     uint32	   PRU1_GIO3; 	          
     uint32	   PRU1_GIO16;      	      
     uint32	   PRU1_GIO15;             
     uint32	   PRU1_GIO11;       	  
     uint32	   PRU1_GIO12;      	      
     uint32	   PRU1_GIO13;  	          
     uint32	   PRU1_GIO14;    	      
     uint32	   PRU1_GIO19;         	  
     uint32	   PRU1_GIO18;             
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
     uint32	   EQEP0_S;        	  
     uint32	   EQEP0_I;             
     uint32	   I2C0_SDA;             
     uint32	   I2C0_SCL;             
     uint32	   MCAN2_TX;             
     uint32	   MCAN2_RX;             
     uint32	   CLKOUT0;             
     uint32	   WARMRSTN;             
     uint32	   SAFETY_ERRORN;           
     uint32	   TDI;           
     uint32	   TDO;      	  
     uint32	   TMS; 	      
     uint32	   TCK;        	  
     uint32	   QSPI0_CLKLB;  	      
     uint32    QUAL_GRP_CFG_REG[18];
     uint32    USER_MODE_EN;
     uint32    PADGLBL_CFG_REG;
     uint32    IOCFGKICK0;
     uint32    IOCFGKICK1;
} pinMuxBase_t;

/*---------------------------------------------------------------------------------------
 * MSS_TOPRCM_REGS
 *---------------------------------------------------------------------------------------
 */
typedef volatile struct {
     uint32 PID;                       /* PID register */
     uint32 WARM_RESET_CONFIG;
     uint32 WARM_RESET_REQ;
     uint32 WARM_RST_CAUSE;
     uint32 WARM_RST_CAUSE_CLR;
     uint32 RCOSC32K_CTRL;
     uint32 LIMP_MODE_EN;
     uint32 PLL_REF_CLK_SRC_SEL;
     uint32 PAD_XTAL_CTRL;
     uint32 SOP_MODE_VALUE;
     uint32 CLK_LOSS_STATUS;
     uint8 Resv_48[4];
     uint32 WARM_RSTTIME1;
     uint32 WARM_RSTTIME2;
     uint32 WARM_RSTTIME3;
     uint8 Resv_1024[964];
     uint32 PLL_CORE_PWRCTRL;
     uint32 PLL_CORE_CLKCTRL;
     uint32 PLL_CORE_TENABLE;
     uint32 PLL_CORE_TENABLEDIV;
     uint32 PLL_CORE_M2NDIV;
     uint32 PLL_CORE_MN2DIV;
     uint32 PLL_CORE_FRACDIV;
     uint32 PLL_CORE_BWCTRL;
     uint32 PLL_CORE_FRACCTRL;
     uint32 PLL_CORE_STATUS;
     uint32 PLL_CORE_HSDIVIDER;
     uint32 PLL_CORE_HSDIVIDER_CLKOUT0;
     uint32 PLL_CORE_HSDIVIDER_CLKOUT1;
     uint32 PLL_CORE_HSDIVIDER_CLKOUT2;
     uint8 Resv_1084[4];
     uint32 PLL_CORE_RSTCTRL;
     uint32 PLL_CORE_HSDIVIDER_RSTCTRL;
     uint8 Resv_1280[188];
     uint32 R5SS_CLK_SRC_SEL;
     uint32 R5SS_CLK_STATUS;
     uint8 Resv_1296[8];
     uint32 R5SS0_CLK_DIV_SEL;
     uint32 R5SS1_CLK_DIV_SEL;
     uint32 R5SS0_CLK_GATE;
     uint32 R5SS1_CLK_GATE;
     uint32 SYS_CLK_DIV_VAL;
     uint32 SYS_CLK_GATE;
     uint32 SYS_CLK_STATUS;
     uint8 Resv_2048[724];
     uint32 PLL_PER_PWRCTRL;
     uint32 PLL_PER_CLKCTRL;
     uint32 PLL_PER_TENABLE;
     uint32 PLL_PER_TENABLEDIV;
     uint32 PLL_PER_M2NDIV;
     uint32 PLL_PER_MN2DIV;
     uint32 PLL_PER_FRACDIV;
     uint32 PLL_PER_BWCTRL;
     uint32 PLL_PER_FRACCTRL;
     uint32 PLL_PER_STATUS;
     uint32 PLL_PER_HSDIVIDER;
     uint32 PLL_PER_HSDIVIDER_CLKOUT0;
     uint32 PLL_PER_HSDIVIDER_CLKOUT1;
     uint8 Resv_2108[8];
     uint32 PLL_PER_RSTCTRL;
     uint32 PLL_PER_HSDIVIDER_RSTCTRL;
     uint8 Resv_3072[956];
     uint32 CLKOUT0_CLK_SRC_SEL;
     uint32 CLKOUT1_CLK_SRC_SEL;
     uint32 CLKOUT0_DIV_VAL;
     uint32 CLKOUT1_DIV_VAL;
     uint32 CLKOUT0_CLK_GATE;
     uint32 CLKOUT1_CLK_GATE;
     uint32 CLKOUT0_CLK_STATUS;
     uint32 CLKOUT1_CLK_STATUS;
     uint32 TRCCLKOUT_CLK_SRC_SEL;
     uint32 TRCCLKOUT_DIV_VAL;
     uint32 TRCCLKOUT_CLK_GATE;
     uint32 TRCCLKOUT_CLK_STATUS;
     uint8 Resv_3328[208];
     uint32 DFT_DMLED_EXEC;
     uint32 DFT_DMLED_STATUS;
     uint8 Resv_3584[248];
     uint32 HW_REG0;
     uint32 HW_REG1;
     uint32 HW_REG2;
     uint32 HW_REG3;
     uint8 Resv_4048[448];
     uint32 HW_SPARE_RW0;
     uint32 HW_SPARE_RW1;
     uint32 HW_SPARE_RW2;
     uint32 HW_SPARE_RW3;
     uint32 HW_SPARE_RO0;
     uint32 HW_SPARE_RO1;
     uint32 HW_SPARE_RO2;
     uint32 HW_SPARE_RO3;
     uint32 HW_SPARE_WPH;
     uint32 HW_SPARE_REC;
     uint8 Resv_4104[16];
     uint32 LOCK0_KICK0;               /*  - KICK0 component */
     uint32 LOCK0_KICK1;               /*  - KICK1 component */
     uint32 INTR_RAW_STATUS;           /* Interrupt Raw Status/Set Register */
     uint32 INTR_ENABLED_STATUS_CLEAR;   /* Interrupt Enabled Status/Clear register */
     uint32 INTR_ENABLE;               /* Interrupt Enable register */
     uint32 INTR_ENABLE_CLEAR;         /* Interrupt Enable Clear register */
     uint32 EOI;                       /* EOI register */
     uint32 FAULT_ADDRESS;             /* Fault Address register */
     uint32 FAULT_TYPE_STATUS;         /* Fault Type Status register */
     uint32 FAULT_ATTR_STATUS;         /* Fault Attribute Status register */
     uint32 FAULT_CLEAR;               /* Fault Clear register */
} toprcmBASE_t;


/*---------------------------------------------------------------------------------------
 * MSS_RCM_REGS
 *---------------------------------------------------------------------------------------
 */
typedef volatile struct {
    volatile uint32 RCM_PID;                       /* PID register */
    volatile uint8  RCM_Resv_16[12];
    volatile uint32 RCM_R5SS0_RST_STATUS;
    volatile uint32 RCM_R5SS0_RST_CAUSE_CLR;
    volatile uint32 RCM_R5SS0_DBG_RST_EN;
    volatile uint32 RCM_R5SS0_RST_ASSERDLY;
    volatile uint32 RCM_R5SS0_RST2ASSERTDLY;
    volatile uint32 RCM_R5SS0_RST_WFICHECK;
    volatile uint8  RCM_Resv_48[8];
    volatile uint32 RCM_R5SS1_RST_STATUS;
    volatile uint32 RCM_R5SS1_RST_CAUSE_CLR;
    volatile uint32 RCM_R5SS1_DBG_RST_EN;
    volatile uint32 RCM_R5SS1_RST_ASSERDLY;
    volatile uint32 RCM_R5SS1_RST2ASSERTDLY;
    volatile uint32 RCM_R5SS1_RST_WFICHECK;
    volatile uint8  RCM_Resv_256[184];
    volatile uint32 RCM_MCAN0_CLK_SRC_SEL;
    volatile uint32 RCM_MCAN1_CLK_SRC_SEL;
    volatile uint32 RCM_MCAN2_CLK_SRC_SEL;
    volatile uint32 RCM_MCAN3_CLK_SRC_SEL;
    volatile uint32 RCM_QSPI0_CLK_SRC_SEL;
    volatile uint32 RCM_RTI0_CLK_SRC_SEL;
    volatile uint32 RCM_RTI1_CLK_SRC_SEL;
    volatile uint32 RCM_RTI2_CLK_SRC_SEL;
    volatile uint32 RCM_RTI3_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_296[4];
    volatile uint32 RCM_WDT0_CLK_SRC_SEL;
    volatile uint32 RCM_WDT1_CLK_SRC_SEL;
    volatile uint32 RCM_WDT2_CLK_SRC_SEL;
    volatile uint32 RCM_WDT3_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_316[4];
    volatile uint32 RCM_MCSPI0_CLK_SRC_SEL;
    volatile uint32 RCM_MCSPI1_CLK_SRC_SEL;
    volatile uint32 RCM_MCSPI2_CLK_SRC_SEL;
    volatile uint32 RCM_MCSPI3_CLK_SRC_SEL;
    volatile uint32 RCM_MCSPI4_CLK_SRC_SEL;
    volatile uint32 RCM_MMC0_CLK_SRC_SEL;
    volatile uint32 RCM_ICSSM0_UART0_CLK_SRC_SEL;
    volatile uint32 RCM_CPTS_CLK_SRC_SEL;
    volatile uint32 RCM_GPMC_CLK_SRC_SEL;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_SRC_SEL;
    volatile uint32 RCM_I2C_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_372[12];
    volatile uint32 RCM_LIN0_UART0_CLK_SRC_SEL;
    volatile uint32 RCM_LIN1_UART1_CLK_SRC_SEL;
    volatile uint32 RCM_LIN2_UART2_CLK_SRC_SEL;
    volatile uint32 RCM_LIN3_UART3_CLK_SRC_SEL;
    volatile uint32 RCM_LIN4_UART4_CLK_SRC_SEL;
    volatile uint32 RCM_LIN5_UART5_CLK_SRC_SEL;
    volatile uint8  RCM_Resv_512[116];
    volatile uint32 RCM_MCAN0_CLK_DIV_VAL;
    volatile uint32 RCM_MCAN1_CLK_DIV_VAL;
    volatile uint32 RCM_MCAN2_CLK_DIV_VAL;
    volatile uint32 RCM_MCAN3_CLK_DIV_VAL;
    volatile uint32 RCM_QSPI0_CLK_DIV_VAL;
    volatile uint32 RCM_RTI0_CLK_DIV_VAL;
    volatile uint32 RCM_RTI1_CLK_DIV_VAL;
    volatile uint32 RCM_RTI2_CLK_DIV_VAL;
    volatile uint32 RCM_RTI3_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_552[4];
    volatile uint32 RCM_WDT0_CLK_DIV_VAL;
    volatile uint32 RCM_WDT1_CLK_DIV_VAL;
    volatile uint32 RCM_WDT2_CLK_DIV_VAL;
    volatile uint32 RCM_WDT3_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_572[4];
    volatile uint32 RCM_MCSPI0_CLK_DIV_VAL;
    volatile uint32 RCM_MCSPI1_CLK_DIV_VAL;
    volatile uint32 RCM_MCSPI2_CLK_DIV_VAL;
    volatile uint32 RCM_MCSPI3_CLK_DIV_VAL;
    volatile uint32 RCM_MCSPI4_CLK_DIV_VAL;
    volatile uint32 RCM_MMC0_CLK_DIV_VAL;
    volatile uint32 RCM_ICSSM0_UART_CLK_DIV_VAL;
    volatile uint32 RCM_CPTS_CLK_DIV_VAL;
    volatile uint32 RCM_GPMC_CLK_DIV_VAL;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_DIV_VAL;
    volatile uint32 RCM_I2C_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_628[12];
    volatile uint32 RCM_LIN0_UART0_CLK_DIV_VAL;
    volatile uint32 RCM_LIN1_UART1_CLK_DIV_VAL;
    volatile uint32 RCM_LIN2_UART2_CLK_DIV_VAL;
    volatile uint32 RCM_LIN3_UART3_CLK_DIV_VAL;
    volatile uint32 RCM_LIN4_UART4_CLK_DIV_VAL;
    volatile uint32 RCM_LIN5_UART5_CLK_DIV_VAL;
    volatile uint32 RCM_RGMII_250_CLK_DIV_VAL;
    volatile uint32 RCM_RGMII_50_CLK_DIV_VAL;
    volatile uint32 RCM_RGMII_5_CLK_DIV_VAL;
    volatile uint32 RCM_XTAL_MMC_32K_CLK_DIV_VAL;
    volatile uint32 RCM_XTAL_TEMPSENSE_32K_CLK_DIV_VAL;
    volatile uint32 RCM_MSS_ELM_CLK_DIV_VAL;
    volatile uint8  RCM_Resv_768[92];
    volatile uint32 RCM_MCAN0_CLK_GATE;
    volatile uint32 RCM_MCAN1_CLK_GATE;
    volatile uint32 RCM_MCAN2_CLK_GATE;
    volatile uint32 RCM_MCAN3_CLK_GATE;
    volatile uint32 RCM_QSPI0_CLK_GATE;
    volatile uint32 RCM_RTI0_CLK_GATE;
    volatile uint32 RCM_RTI1_CLK_GATE;
    volatile uint32 RCM_RTI2_CLK_GATE;
    volatile uint32 RCM_RTI3_CLK_GATE;
    volatile uint8  RCM_Resv_808[4];
    volatile uint32 RCM_WDT0_CLK_GATE;
    volatile uint32 RCM_WDT1_CLK_GATE;
    volatile uint32 RCM_WDT2_CLK_GATE;
    volatile uint32 RCM_WDT3_CLK_GATE;
    volatile uint8  RCM_Resv_828[4];
    volatile uint32 RCM_MCSPI0_CLK_GATE;
    volatile uint32 RCM_MCSPI1_CLK_GATE;
    volatile uint32 RCM_MCSPI2_CLK_GATE;
    volatile uint32 RCM_MCSPI3_CLK_GATE;
    volatile uint32 RCM_MCSPI4_CLK_GATE;
    volatile uint32 RCM_MMC0_CLK_GATE;
    volatile uint32 RCM_ICSSM0_UART_CLK_GATE;
    volatile uint32 RCM_CPTS_CLK_GATE;
    volatile uint32 RCM_GPMC_CLK_GATE;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_GATE;
    volatile uint32 RCM_I2C0_CLK_GATE;
    volatile uint32 RCM_I2C1_CLK_GATE;
    volatile uint32 RCM_I2C2_CLK_GATE;
    volatile uint32 RCM_I2C3_CLK_GATE;
    volatile uint32 RCM_LIN0_CLK_GATE;
    volatile uint32 RCM_LIN1_CLK_GATE;
    volatile uint32 RCM_LIN2_CLK_GATE;
    volatile uint32 RCM_LIN3_CLK_GATE;
    volatile uint32 RCM_LIN4_CLK_GATE;
    volatile uint8  RCM_Resv_908[4];
    volatile uint32 RCM_UART0_CLK_GATE;
    volatile uint32 RCM_UART1_CLK_GATE;
    volatile uint32 RCM_UART2_CLK_GATE;
    volatile uint32 RCM_UART3_CLK_GATE;
    volatile uint32 RCM_UART4_CLK_GATE;
    volatile uint32 RCM_UART5_CLK_GATE;
    volatile uint32 RCM_RGMII_250_CLK_GATE;
    volatile uint32 RCM_RGMII_50_CLK_GATE;
    volatile uint32 RCM_RGMII_5_CLK_GATE;
    volatile uint32 RCM_MMC0_32K_CLK_GATE;
    volatile uint32 RCM_TEMPSENSE_32K_CLK_GATE;
    volatile uint32 RCM_CPSW_CLK_GATE;
    volatile uint32 RCM_ICSSM0_IEP_CLK_GATE;
    volatile uint32 RCM_ICSSM0_CORE_CLK_GATE;
    volatile uint32 RCM_MSS_ICSSM_SYS_CLK_GATE;
    volatile uint32 RCM_MSS_ELM_CLK_GATE;
    volatile uint32 RCM_R5SS0_CORE0_GATE;
    volatile uint32 RCM_R5SS1_CORE0_GATE;
    volatile uint32 RCM_R5SS0_CORE1_GATE;
    volatile uint32 RCM_R5SS1_CORE1_GATE;
    volatile uint8  RCM_Resv_1024[36];
    volatile uint32 RCM_MCAN0_CLK_STATUS;
    volatile uint32 RCM_MCAN1_CLK_STATUS;
    volatile uint32 RCM_MCAN2_CLK_STATUS;
    volatile uint32 RCM_MCAN3_CLK_STATUS;
    volatile uint32 RCM_QSPI0_CLK_STATUS;
    volatile uint32 RCM_RTI0_CLK_STATUS;
    volatile uint32 RCM_RTI1_CLK_STATUS;
    volatile uint32 RCM_RTI2_CLK_STATUS;
    volatile uint32 RCM_RTI3_CLK_STATUS;
    volatile uint8  RCM_Resv_1064[4];
    volatile uint32 RCM_WDT0_CLK_STATUS;
    volatile uint32 RCM_WDT1_CLK_STATUS;
    volatile uint32 RCM_WDT2_CLK_STATUS;
    volatile uint32 RCM_WDT3_CLK_STATUS;
    volatile uint8  RCM_Resv_1084[4];
    volatile uint32 RCM_MCSPI0_CLK_STATUS;
    volatile uint32 RCM_MCSPI1_CLK_STATUS;
    volatile uint32 RCM_MCSPI2_CLK_STATUS;
    volatile uint32 RCM_MCSPI3_CLK_STATUS;
    volatile uint32 RCM_MCSPI4_CLK_STATUS;
    volatile uint32 RCM_MMC0_CLK_STATUS;
    volatile uint32 RCM_ICSSM0_UART_CLK_STATUS;
    volatile uint32 RCM_CPTS_CLK_STATUS;
    volatile uint32 RCM_GPMC_CLK_STATUS;
    volatile uint32 RCM_CONTROLSS_PLL_CLK_STATUS;
    volatile uint32 RCM_I2C_CLK_STATUS;
    volatile uint8  RCM_Resv_1140[12];
    volatile uint32 RCM_LIN0_UART0_CLK_STATUS;
    volatile uint32 RCM_LIN1_UART1_CLK_STATUS;
    volatile uint32 RCM_LIN2_UART2_CLK_STATUS;
    volatile uint32 RCM_LIN3_UART3_CLK_STATUS;
    volatile uint32 RCM_LIN4_UART4_CLK_STATUS;
    volatile uint32 RCM_LIN5_UART5_CLK_STATUS;
    volatile uint32 RCM_RGMII_250_CLK_STATUS;
    volatile uint32 RCM_RGMII_50_CLK_STATUS;
    volatile uint32 RCM_RGMII_5_CLK_STATUS;
    volatile uint8  RCM_Resv_1180[4];
    volatile uint32 RCM_MMC0_32K_CLK_STATUS;
    volatile uint32 RCM_TEMPSENSE_32K_CLK_STATUS;
    volatile uint32 RCM_MSS_ELM_CLK_STATUS;
    volatile uint8  RCM_Resv_1280[88];
    volatile uint32 RCM_R5SS0_POR_RST_CTRL;
    volatile uint32 RCM_R5SS1_POR_RST_CTRL;
    volatile uint32 RCM_R5SS0_CORE0_GRST_CTRL;
    volatile uint32 RCM_R5SS1_CORE0_GRST_CTRL;
    volatile uint32 RCM_R5SS0_CORE1_GRST_CTRL;
    volatile uint32 RCM_R5SS1_CORE1_GRST_CTRL;
    volatile uint32 RCM_R5SS0_CORE0_LRST_CTRL;
    volatile uint32 RCM_R5SS1_CORE0_LRST_CTRL;
    volatile uint32 RCM_R5SS0_CORE1_LRST_CTRL;
    volatile uint32 RCM_R5SS1_CORE1_LRST_CTRL;
    volatile uint32 RCM_R5SS0_VIM0_RST_CTRL;
    volatile uint32 RCM_R5SS1_VIM0_RST_CTRL;
    volatile uint32 RCM_R5SS0_VIM1_RST_CTRL;
    volatile uint32 RCM_R5SS1_VIM1_RST_CTRL;
    volatile uint32 RCM_MCRC0_RST_CTRL;
    volatile uint32 RCM_RTI0_RST_CTRL;
    volatile uint32 RCM_RTI1_RST_CTRL;
    volatile uint32 RCM_RTI2_RST_CTRL;
    volatile uint32 RCM_RTI3_RST_CTRL;
    volatile uint32 RCM_WDT0_RST_CTRL;
    volatile uint32 RCM_WDT1_RST_CTRL;
    volatile uint32 RCM_WDT2_RST_CTRL;
    volatile uint32 RCM_WDT3_RST_CTRL;
    volatile uint32 RCM_TOP_ESM_RST_CTRL;
    volatile uint32 RCM_DCC0_RST_CTRL;
    volatile uint32 RCM_DCC1_RST_CTRL;
    volatile uint32 RCM_DCC2_RST_CTRL;
    volatile uint32 RCM_DCC3_RST_CTRL;
    volatile uint32 RCM_MCSPI0_RST_CTRL;
    volatile uint32 RCM_MCSPI1_RST_CTRL;
    volatile uint32 RCM_MCSPI2_RST_CTRL;
    volatile uint32 RCM_MCSPI3_RST_CTRL;
    volatile uint32 RCM_MCSPI4_RST_CTRL;
    volatile uint32 RCM_QSPI0_RST_CTRL;
    volatile uint32 RCM_MCAN0_RST_CTRL;
    volatile uint32 RCM_MCAN1_RST_CTRL;
    volatile uint32 RCM_MCAN2_RST_CTRL;
    volatile uint32 RCM_MCAN3_RST_CTRL;
    volatile uint32 RCM_I2C0_RST_CTRL;
    volatile uint32 RCM_I2C1_RST_CTRL;
    volatile uint32 RCM_I2C2_RST_CTRL;
    volatile uint32 RCM_I2C3_RST_CTRL;
    volatile uint32 RCM_UART0_RST_CTRL;
    volatile uint32 RCM_UART1_RST_CTRL;
    volatile uint32 RCM_UART2_RST_CTRL;
    volatile uint32 RCM_UART3_RST_CTRL;
    volatile uint32 RCM_UART4_RST_CTRL;
    volatile uint32 RCM_UART5_RST_CTRL;
    volatile uint32 RCM_LIN0_RST_CTRL;
    volatile uint32 RCM_LIN1_RST_CTRL;
    volatile uint32 RCM_LIN2_RST_CTRL;
    volatile uint32 RCM_LIN3_RST_CTRL;
    volatile uint32 RCM_LIN4_RST_CTRL;
    volatile uint8  RCM_Resv_1496[4];
    volatile uint32 RCM_EDMA_RST_CTRL;
    volatile uint32 RCM_INFRA_RST_CTRL;
    volatile uint32 RCM_CPSW_RST_CTRL;
    volatile uint32 RCM_ICSSM0_RST_CTRL;
    volatile uint32 RCM_MMC0_RST_CTRL;
    volatile uint32 RCM_GPIO0_RST_CTRL;
    volatile uint32 RCM_GPIO1_RST_CTRL;
    volatile uint32 RCM_GPIO2_RST_CTRL;
    volatile uint32 RCM_GPIO3_RST_CTRL;
    volatile uint32 RCM_SPINLOCK0_RST_CTRL;
    volatile uint32 RCM_GPMC_RST_CTRL;
    volatile uint32 RCM_TEMPSENSE_32K_RST_CTRL;
    volatile uint32 RCM_MSS_ELM_RST_CTRL;
    volatile uint8  RCM_Resv_1792[244];
    volatile uint32 RCM_L2OCRAM_BANK0_PD_CTRL;
    volatile uint32 RCM_L2OCRAM_BANK1_PD_CTRL;
    volatile uint32 RCM_L2OCRAM_BANK2_PD_CTRL;
    volatile uint32 RCM_L2OCRAM_BANK3_PD_CTRL;
    volatile uint32 RCM_L2OCRAM_BANK0_PD_STATUS;
    volatile uint32 RCM_L2OCRAM_BANK1_PD_STATUS;
    volatile uint32 RCM_L2OCRAM_BANK2_PD_STATUS;
    volatile uint32 RCM_L2OCRAM_BANK3_PD_STATUS;
    volatile uint32 RCM_HW_REG0;
    volatile uint32 RCM_HW_REG1;
    volatile uint32 RCM_HW_REG2;
    volatile uint32 RCM_HW_REG3;
    volatile uint8  RCM_Resv_2048[208];
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
    volatile uint8  RCM_Resv_4048[1920];
    volatile uint32 RCM_HW_SPARE_RW0;
    volatile uint32 RCM_HW_SPARE_RW1;
    volatile uint32 RCM_HW_SPARE_RW2;
    volatile uint32 RCM_HW_SPARE_RW3;
    volatile uint32 RCM_HW_SPARE_RO0;
    volatile uint32 RCM_HW_SPARE_RO1;
    volatile uint32 RCM_HW_SPARE_RO2;
    volatile uint32 RCM_HW_SPARE_RO3;
    volatile uint32 RCM_HW_SPARE_WPH;
    volatile uint32 RCM_HW_SPARE_REC;
    volatile uint8  RCM_Resv_4104[16];
    volatile uint32 RCM_LOCK0_KICK0;               /*  - KICK0 component */
    volatile uint32 RCM_LOCK0_KICK1;               /*  - KICK1 component */
    volatile uint32 RCM_INTR_RAW_STATUS;           /* Interrupt Raw Status/Set Register */
    volatile uint32 RCM_INTR_ENABLED_STATUS_CLEAR;   /* Interrupt Enabled Status/Clear register */
    volatile uint32 RCM_INTR_ENABLE;               /* Interrupt Enable register */
    volatile uint32 RCM_INTR_ENABLE_CLEAR;         /* Interrupt Enable Clear register */
    volatile uint32 RCM_EOI;                       /* EOI register */
    volatile uint32 RCM_FAULT_ADDRESS;             /* Fault Address register */
    volatile uint32 RCM_FAULT_TYPE_STATUS;         /* Fault Type Status register */
    volatile uint32 RCM_FAULT_ATTR_STATUS;         /* Fault Attribute Status register */
    volatile uint32 RCM_FAULT_CLEAR;               /* Fault Clear register */
} mssrcmBASE_t;

typedef volatile struct {
    uint32 PID;                       /* PID register */
    uint8  Resv_32[28];
    uint32 R5SS0_CONTROL;
    uint32 R5SS0_CORE0_HALT;
    uint32 R5SS0_CORE1_HALT;
    uint32 R5SS0_STATUS_REG;
    uint32 R5SS0_CORE0_STAT;
    uint32 R5SS0_CORE1_STAT;
    uint32 R5SS0_FORCE_WFI;
    uint8  Resv_64[4];
    uint32 R5SS1_CONTROL;
    uint32 R5SS1_CORE0_HALT;
    uint32 R5SS1_CORE1_HALT;
    uint32 R5SS1_STATUS_REG;
    uint32 R5SS1_CORE0_STAT;
    uint32 R5SS1_CORE1_STAT;
    uint32 R5SS1_FORCE_WFI;
    uint8  Resv_128[36];
    uint32 R5SS0_ROM_ECLIPSE;
    uint8  Resv_144[12];
    uint32 R5SS0_TEINIT;
    uint32 R5SS1_TEINIT;
    uint32 R5SS0_AHB_EN;
    uint32 R5SS1_AHB_EN;
    uint32 R5SS0_CORE0_AHB_BASE;
    uint32 R5SS1_CORE0_AHB_BASE;
    uint32 R5SS0_CORE0_AHB_SIZE;
    uint32 R5SS1_CORE0_AHB_SIZE;
    uint32 R5SS0_CORE1_AHB_BASE;
    uint32 R5SS1_CORE1_AHB_BASE;
    uint32 R5SS0_CORE1_AHB_SIZE;
    uint32 R5SS1_CORE1_AHB_SIZE;
    uint32 R5SS0_TCM_EXT_ERR_EN;
    uint32 R5SS1_TCM_EXT_ERR_EN;
    uint32 R5SS0_TCM_ERR_EN;
    uint32 R5SS1_TCM_ERR_EN;
    uint32 R5SS0_INIT_TCM;
    uint32 R5SS1_INIT_TCM;
    uint32 R5SS0_TCM_ECC_WRENZ_EN;
    uint32 R5SS1_TCM_ECC_WRENZ_EN;
    uint8  Resv_256[32];
    uint32 BOOT_INFO_REG0;
    uint32 BOOT_INFO_REG1;
    uint32 BOOT_INFO_REG2;
    uint32 BOOT_INFO_REG3;
    uint32 BOOT_INFO_REG4;
    uint32 BOOT_INFO_REG5;
    uint32 BOOT_INFO_REG6;
    uint32 BOOT_INFO_REG7;
    uint8  Resv_512[224];
    uint32 R5SS0_ATCM_MEM_INIT;
    uint32 R5SS0_ATCM_MEM_INIT_DONE;
    uint32 R5SS0_ATCM_MEM_INIT_STATUS;
    uint8  Resv_528[4];
    uint32 R5SS0_BTCM_MEM_INIT;
    uint32 R5SS0_BTCM_MEM_INIT_DONE;
    uint32 R5SS0_BTCM_MEM_INIT_STATUS;
    uint8  Resv_544[4];
    uint32 R5SS1_ATCM_MEM_INIT;
    uint32 R5SS1_ATCM_MEM_INIT_DONE;
    uint32 R5SS1_ATCM_MEM_INIT_STATUS;
    uint8  Resv_560[4];
    uint32 R5SS1_BTCM_MEM_INIT;
    uint32 R5SS1_BTCM_MEM_INIT_DONE;
    uint32 R5SS1_BTCM_MEM_INIT_STATUS;
    uint8  Resv_576[4];
    uint32 L2IOCRAM_MEM_INIT;
    uint32 L2OCRAM_MEM_INIT_DONE;
    uint32 L2OCRAM_MEM_INIT_STATUS;
    uint8  Resv_592[4];
    uint32 MAILBOXRAM_MEM_INIT;
    uint32 MAILBOXRAM_MEM_INIT_DONE;
    uint32 MAILBOXRAM_MEM_INIT_STATUS;
    uint8  Resv_608[4];
    uint32 TPCC_MEM_INIT;
    uint32 TPCC_MEM_INIT_DONE;
    uint32 TPCC_MEMINIT_STATUS;
    uint8  Resv_768[148];
    uint32 TOP_PBIST_KEY_RST;
    uint32 TOP_PBIST_REG0;
    uint32 TOP_PBIST_REG1;
    uint32 TOP_PBIST_REG2;
    uint8  Resv_1024[240];
    uint32 R5SS0_CTI_TRIG_SEL;
    uint32 R5SS1_CTI_TRIG_SEL;
    uint32 DBGSS_CTI_TRIG_SEL;
    uint32 DEBUGSS_CSETB_FLUSH;
    uint32 DEBUGSS_STM_NSGUAREN;
    uint8  Resv_1056[12];
    uint32 MCAN0_HALTEN;
    uint32 MCAN1_HALTEN;
    uint32 MCAN2_HALTEN;
    uint32 MCAN3_HALTEN;
    uint32 LIN0_HALTEN;
    uint32 LIN1_HALTEN;
    uint32 LIN2_HALTEN;
    uint32 LIN3_HALTEN;
    uint32 LIN4_HALTEN;
    uint32 I2C0_HALTEN;
    uint32 I2C1_HALTEN;
    uint32 I2C2_HALTEN;
    uint32 I2C3_HALTEN;
    uint32 RTI0_HALTEN;
    uint32 RTI1_HALTEN;
    uint32 RTI2_HALTEN;
    uint32 RTI3_HALTEN;
    uint8  Resv_1140[16];
    uint32 CPSW_HALTEN;
    uint32 MCRC0_HALTEN;
    uint8  Resv_2048[900];
    uint32 TPTC_DBS_CONFIG;
    uint32 TPTC_BOUNDARY_CFG;
    uint32 TPTC_XID_REORDER_CFG;
    uint8  Resv_2064[4];
    uint32 CPSW_CONTROL;
    uint32 QSPI_CONFIG;
    uint32 ICSSM_IDLE_CONTROL;
    uint32 ICSSM_PRU0_GPI_SEL;
    uint32 ICSSM_PRU1_GPI_SEL;
    uint32 ICSSM_PRU0_GPIO_OUT_CTRL;
    uint32 ICSSM_PRU1_GPIO_OUT_CTRL;
    uint32 GPMC_CONTROL;
    uint32 TPCC0_INTAGG_MASK;
    uint32 TPCC0_INTAGG_STATUS;
    uint32 TPCC0_INTAGG_STATUS_RAW;
    uint8  Resv_4048[1940];
    uint32 HW_SPARE_RW0;
    uint32 HW_SPARE_RW1;
    uint32 HW_SPARE_RW2;
    uint32 HW_SPARE_RW3;
    uint32 HW_SPARE_RO0;
    uint32 HW_SPARE_RO1;
    uint32 HW_SPARE_RO2;
    uint32 HW_SPARE_RO3;
    uint32 HW_SPARE_REC;
    uint8  Resv_4104[20];
    uint32 LOCK0_KICK0;               /*  - KICK0 component */
    uint32 LOCK0_KICK1;               /*  - KICK1 component */
    uint32 INTR_RAW_STATUS;           /* Interrupt Raw Status/Set Register */
    uint32 INTR_ENABLED_STATUS_CLEAR;   /* Interrupt Enabled Status/Clear register */
    uint32 INTR_ENABLE;               /* Interrupt Enable register */
    uint32 INTR_ENABLE_CLEAR;         /* Interrupt Enable Clear register */
    uint32 EOI;                       /* EOI register */
    uint32 FAULT_ADDRESS;             /* Fault Address register */
    uint32 FAULT_TYPE_STATUS;         /* Fault Type Status register */
    uint32 FAULT_ATTR_STATUS;         /* Fault Attribute Status register */
    uint32 FAULT_CLEAR;               /* Fault Clear register */
    uint8  Resv_16384[12236];
    uint32 R5SS0_CORE0_MBOX_WRITE_DONE;
    uint32 R5SS0_CORE0_MBOX_READ_REQ;
    uint32 R5SS0_CORE0_MBOX_READ_DONE_ACK;
    uint32 R5SS0_CORE0_MBOX_READ_DONE;
    uint32 R5SS0_CORE0_SW_INT;
    uint8  Resv_16416[12];
    uint32 MPU_ADDR_ERRAGG_R5SS0_CPU0_MASK;
    uint32 MPU_ADDR_ERRAGG_R5SS0_CPU0_STATUS;
    uint32 MPU_ADDR_ERRAGG_R5SS0_CPU0_STATUS_RAW;
    uint8  Resv_16432[4];
    uint32 MPU_PROT_ERRAGG_R5SS0_CPU0_MASK;
    uint32 MPU_PROT_ERRAGG_R5SS0_CPU0_STATUS;
    uint32 MPU_PROT_ERRAGG_R5SS0_CPU0_STATUS_RAW;
    uint8  Resv_32768[16324];
    uint32 R5SS0_CORE1_MBOX_WRITE_DONE;
    uint32 R5SS0_CORE1_MBOX_READ_REQ;
    uint32 R5SS0_CORE1_MBOX_READ_DONE_ACK;
    uint32 R5SS0_CORE1_MBOX_READ_DONE;
    uint32 R5SS0_CORE1_SW_INT;
    uint8  Resv_32800[12];
    uint32 MPU_ADDR_ERRAGG_R5SS0_CPU1_MASK;
    uint32 MPU_ADDR_ERRAGG_R5SS0_CPU1_STATUS;
    uint32 MPU_ADDR_ERRAGG_R5SS0_CPU1_STATUS_RAW;
    uint8  Resv_32816[4];
    uint32 MPU_PROT_ERRAGG_R5SS0_CPU1_MASK;
    uint32 MPU_PROT_ERRAGG_R5SS0_CPU1_STATUS;
    uint32 MPU_PROT_ERRAGG_R5SS0_CPU1_STATUS_RAW;
    uint8  Resv_49152[16324];
    uint32 R5SS1_CORE0_MBOX_WRITE_DONE;
    uint32 R5SS1_CORE0_MBOX_READ_REQ;
    uint32 R5SS1_CORE0_MBOX_READ_DONE_ACK;
    uint32 R5SS1_CORE0_MBOX_READ_DONE;
    uint32 R5SS1_CORE0_SW_INT;
    uint8  Resv_49184[12];
    uint32 MPU_ADDR_ERRAGG_R5SS1_CPU0_MASK;
    uint32 MPU_ADDR_ERRAGG_R5SS1_CPU0_STATUS;
    uint32 MPU_ADDR_ERRAGG_R5SS1_CPU0_STATUS_RAW;
    uint8  Resv_49200[4];
    uint32 MPU_PROT_ERRAGG_R5SS1_CPU0_MASK;
    uint32 MPU_PROT_ERRAGG_R5SS1_CPU0_STATUS;
    uint32 MPU_PROT_ERRAGG_R5SS1_CPU0_STATUS_RAW;
    uint8  Resv_65536[16324];
    uint32 R5SS1_CORE1_MBOX_WRITE_DONE;
    uint32 R5SS1_CORE1_MBOX_READ_REQ;
    uint32 R5SS1_CORE1_MBOX_READ_DONE_ACK;
    uint32 R5SS1_CORE1_MBOX_READ_DONE;
    uint32 R5SS1_CORE1_SW_INT;
    uint8  Resv_65568[12];
    uint32 MPU_ADDR_ERRAGG_R5SS1_CPU1_MASK;
    uint32 MPU_ADDR_ERRAGG_R5SS1_CPU1_STATUS;
    uint32 MPU_ADDR_ERRAGG_R5SS1_CPU1_STATUS_RAW;
    uint8  Resv_65584[4];
    uint32 MPU_PROT_ERRAGG_R5SS1_CPU1_MASK;
    uint32 MPU_PROT_ERRAGG_R5SS1_CPU1_STATUS;
    uint32 MPU_PROT_ERRAGG_R5SS1_CPU1_STATUS_RAW;
    uint8  Resv_81920[16324];
    uint32 ICSSM_PRU0_MBOX_WRITE_DONE;
    uint32 ICSSM_PRU0_MBOX_READ_REQ;
    uint32 ICSSM_PRU0_MBOX_READ_DONE_ACK;
    uint32 ICSSM_PRU0_MBOX_READ_DONE;
    uint32 ICSSM_PRU1_MBOX_WRITE_DONE;
    uint32 ICSSM_PRU1_MBOX_READ_REQ;
    uint32 ICSSM_PRU1_MBOX_READ_DONE_ACK;
    uint32 ICSSM_PRU1_MBOX_READ_DONE;
    uint8  Resv_98304[16352];
    uint32 TPCC0_ERRAGG_MASK;
    uint32 TPCC0_ERRAGG_STATUS;
    uint32 TPCC0_ERRAGG_STATUS_RAW;
    uint8  Resv_98320[4];
    uint32 MMR_ACCESS_ERRAGG_MASK0;
    uint32 MMR_ACCESS_ERRAGG_STATUS0;
    uint32 MMR_ACCESS_ERRAGG_STATUS_RAW0;
    uint8  Resv_98432[100];
    uint32 R5SS0_CPU0_ECC_CORR_ERRAGG_MASK;
    uint32 R5SS0_CPU0_ECC_CORR_ERRAGG_STATUS;
    uint32 R5SS0_CPU0_ECC_CORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98448[4];
    uint32 R5SS0_CPU0_ECC_UNCORR_ERRAGG_MASK;
    uint32 R5SS0_CPU0_ECC_UNCORR_ERRAGG_STATUS;
    uint32 R5SS0_CPU0_ECC_UNCORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98464[4];
    uint32 R5SS0_CPU1_ECC_CORR_ERRAGG_MASK;
    uint32 R5SS0_CPU1_ECC_CORR_ERRAGG_STATUS;
    uint32 R5SS0_CPU1_ECC_CORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98480[4];
    uint32 R5SS0_CPU1_ECC_UNCORR_ERRAGG_MASK;
    uint32 R5SS0_CPU1_ECC_UNCORR_ERRAGG_STATUS;
    uint32 R5SS0_CPU1_ECC_UNCORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98496[4];
    uint32 R5SS1_CPU0_ECC_CORR_ERRAGG_MASK;
    uint32 R5SS1_CPU0_ECC_CORR_ERRAGG_STATUS;
    uint32 R5SS1_CPU0_ECC_CORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98512[4];
    uint32 R5SS1_CPU0_ECC_UNCORR_ERRAGG_MASK;
    uint32 R5SS1_CPU0_ECC_UNCORR_ERRAGG_STATUS;
    uint32 R5SS1_CPU0_ECC_UNCORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98528[4];
    uint32 R5SS1_CPU1_ECC_CORR_ERRAGG_MASK;
    uint32 R5SS1_CPU1_ECC_CORR_ERRAGG_STATUS;
    uint32 R5SS1_CPU1_ECC_CORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98544[4];
    uint32 R5SS1_CPU1_ECC_UNCORR_ERRAGG_MASK;
    uint32 R5SS1_CPU1_ECC_UNCORR_ERRAGG_STATUS;
    uint32 R5SS1_CPU1_ECC_UNCORR_ERRAGG_STATUS_RAW;
    uint8  Resv_98560[4];
    uint32 R5SS0_CPU0_TCM_ADDRPARITY_ERRAGG_MASK;
    uint32 R5SS0_CPU0_TCM_ADDRPARITY_ERRAGG_STATUS;
    uint32 R5SS0_CPU0_TCM_ADDRPARITY_ERRAGG_STATUS_RAW;
    uint8  Resv_98576[4];
    uint32 R5SS0_CPU1_TCM_ADDRPARITY_ERRAGG_MASK;
    uint32 R5SS0_CPU1_TCM_ADDRPARITY_ERRAGG_STATUS;
    uint32 R5SS0_CPU1_TCM_ADDRPARITY_ERRAGG_STATUS_RAW;
    uint8  Resv_98592[4];
    uint32 R5SS0_TCM_ADDRPARITY_CLR;
    uint32 R5SS0_CORE0_ADDRPARITY_ERR_ATCM;
    uint32 R5SS0_CORE1_ADDRPARITY_ERR_ATCM;
    uint32 R5SS0_CORE0_ERR_ADDRPARITY_B0TCM;
    uint32 R5SS0_CORE1_ERR_ADDRPARITY_B0TCM;
    uint32 R5SS0_CORE0_ERR_ADDRPARITY_B1TCM;
    uint32 R5SS0_CORE1_ERR_ADDRPARITY_B1TCM;
    uint32 R5SS0_TCM_ADDRPARITY_ERRFORCE;
    uint32 R5SS1_CPU0_TCM_ADDRPARITY_ERRAGG_MASK;
    uint32 R5SS1_CPU0_TCM_ADDRPARITY_ERRAGG_STATUS;
    uint32 R5SS1_CPU0_TCM_ADDRPARITY_ERRAGG_STATUS_RAW;
    uint8  Resv_98640[4];
    uint32 R5SS1_CPU1_TCM_ADDRPARITY_ERRAGG_MASK;
    uint32 R5SS1_CPU1_TCM_ADDRPARITY_ERRAGG_STATUS;
    uint32 R5SS1_CPU1_TCM_ADDRPARITY_ERRAGG_STATUS_RAW;
    uint8  Resv_98656[4];
    uint32 R5SS1_TCM_ADDRPARITY_CLR;
    uint32 R5SS1_CORE0_ADDRPARITY_ERR_ATCM;
    uint32 R5SS1_CORE1_ADDRPARITY_ERR_ATCM;
    uint32 R5SS1_CORE0_ERR_ADDRPARITY_B0TCM;
    uint32 R5SS1_CORE1_ERR_ADDRPARITY_B0TCM;
    uint32 R5SS1_CORE0_ERR_ADDRPARITY_B1TCM;
    uint32 R5SS1_CORE1_ERR_ADDRPARITY_B1TCM;
    uint32 R5SS1_TCM_ADDRPARITY_ERRFORCE;
    uint32 TPCC0_PARITY_CTRL;
    uint32 TPCC0_PARITY_STATUS;
    uint8  Resv_98816[120];
    uint32 BUS_SAFETY_CTRL;
    uint8  Resv_98848[28];
    uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_FI;
    uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_98880[8];
    uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_FI;
    uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_98912[8];
    uint32 R5SS1_CORE0_AXI_RD_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE0_AXI_RD_BUS_SAFETY_FI;
    uint32 R5SS1_CORE0_AXI_RD_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE0_AXI_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_98944[8];
    uint32 R5SS1_CORE1_AXI_RD_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE1_AXI_RD_BUS_SAFETY_FI;
    uint32 R5SS1_CORE1_AXI_RD_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE1_AXI_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_98976[8];
    uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_FI;
    uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS0_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99008[4];
    uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_FI;
    uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS0_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99040[4];
    uint32 R5SS1_CORE0_AXI_WR_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE0_AXI_WR_BUS_SAFETY_FI;
    uint32 R5SS1_CORE0_AXI_WR_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS1_CORE0_AXI_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99072[4];
    uint32 R5SS1_CORE1_AXI_WR_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE1_AXI_WR_BUS_SAFETY_FI;
    uint32 R5SS1_CORE1_AXI_WR_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS1_CORE1_AXI_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99104[4];
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_FI;
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS0_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_FI;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS0_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_FI;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS1_CORE0_AXI_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_FI;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS1_CORE1_AXI_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 TPTC00_RD_BUS_SAFETY_CTRL;
    uint32 TPTC00_RD_BUS_SAFETY_FI;
    uint32 TPTC00_RD_BUS_SAFETY_ERR;
    uint32 TPTC00_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 TPTC00_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 TPTC00_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_99264[8];
    uint32 TPTC01_RD_BUS_SAFETY_CTRL;
    uint32 TPTC01_RD_BUS_SAFETY_FI;
    uint32 TPTC01_RD_BUS_SAFETY_ERR;
    uint32 TPTC01_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 TPTC01_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 TPTC01_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_99296[8];
    uint32 TPTC00_WR_BUS_SAFETY_CTRL;
    uint32 TPTC00_WR_BUS_SAFETY_FI;
    uint32 TPTC00_WR_BUS_SAFETY_ERR;
    uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 TPTC00_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99328[4];
    uint32 TPTC01_WR_BUS_SAFETY_CTRL;
    uint32 TPTC01_WR_BUS_SAFETY_FI;
    uint32 TPTC01_WR_BUS_SAFETY_ERR;
    uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 TPTC01_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99360[4];
    uint32 HSM_TPTC0_RD_BUS_SAFETY_CTRL;
    uint32 HSM_TPTC0_RD_BUS_SAFETY_FI;
    uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR;
    uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 HSM_TPTC0_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_99392[8];
    uint32 HSM_TPTC1_RD_BUS_SAFETY_CTRL;
    uint32 HSM_TPTC1_RD_BUS_SAFETY_FI;
    uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR;
    uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR_STAT_CMD;
    uint32 HSM_TPTC1_RD_BUS_SAFETY_ERR_STAT_READ;
    uint8  Resv_99424[8];
    uint32 HSM_TPTC0_WR_BUS_SAFETY_CTRL;
    uint32 HSM_TPTC0_WR_BUS_SAFETY_FI;
    uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR;
    uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 HSM_TPTC0_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99456[4];
    uint32 HSM_TPTC1_WR_BUS_SAFETY_CTRL;
    uint32 HSM_TPTC1_WR_BUS_SAFETY_FI;
    uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR;
    uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_CMD;
    uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 HSM_TPTC1_WR_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_99488[4];
    uint32 QSPI0_BUS_SAFETY_CTRL;
    uint32 QSPI0_BUS_SAFETY_FI;
    uint32 QSPI0_BUS_SAFETY_ERR;
    uint32 QSPI0_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 QSPI0_BUS_SAFETY_ERR_STAT_CMD;
    uint32 QSPI0_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 QSPI0_BUS_SAFETY_ERR_STAT_READ;
    uint32 QSPI0_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 HSM_DTHE_BUS_SAFETY_CTRL;
    uint32 HSM_DTHE_BUS_SAFETY_FI;
    uint32 HSM_DTHE_BUS_SAFETY_ERR;
    uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_CMD;
    uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_READ;
    uint32 HSM_DTHE_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 MSS_CPSW_BUS_SAFETY_CTRL;
    uint32 MSS_CPSW_BUS_SAFETY_FI;
    uint32 MSS_CPSW_BUS_SAFETY_ERR;
    uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_CMD;
    uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_READ;
    uint32 MSS_CPSW_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 ICSSM_PDSP0_BUS_SAFETY_CTRL;
    uint32 ICSSM_PDSP0_BUS_SAFETY_FI;
    uint32 ICSSM_PDSP0_BUS_SAFETY_ERR;
    uint32 ICSSM_PDSP0_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 ICSSM_PDSP0_BUS_SAFETY_ERR_STAT_CMD;
    uint32 ICSSM_PDSP0_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 ICSSM_PDSP0_BUS_SAFETY_ERR_STAT_READ;
    uint32 ICSSM_PDSP0_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 ICSSM_PDSP1_BUS_SAFETY_CTRL;
    uint32 ICSSM_PDSP1_BUS_SAFETY_FI;
    uint32 ICSSM_PDSP1_BUS_SAFETY_ERR;
    uint32 ICSSM_PDSP1_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 ICSSM_PDSP1_BUS_SAFETY_ERR_STAT_CMD;
    uint32 ICSSM_PDSP1_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 ICSSM_PDSP1_BUS_SAFETY_ERR_STAT_READ;
    uint32 ICSSM_PDSP1_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 MCRC0_BUS_SAFETY_CTRL;
    uint32 MCRC0_BUS_SAFETY_FI;
    uint32 MCRC0_BUS_SAFETY_ERR;
    uint32 MCRC0_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 MCRC0_BUS_SAFETY_ERR_STAT_CMD;
    uint32 MCRC0_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 MCRC0_BUS_SAFETY_ERR_STAT_READ;
    uint32 MCRC0_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 SCRM2SCRP_0_BUS_SAFETY_CTRL;
    uint32 SCRM2SCRP_0_BUS_SAFETY_FI;
    uint32 SCRM2SCRP_0_BUS_SAFETY_ERR;
    uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_CMD;
    uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_READ;
    uint32 SCRM2SCRP_0_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 SCRM2SCRP_1_BUS_SAFETY_CTRL;
    uint32 SCRM2SCRP_1_BUS_SAFETY_FI;
    uint32 SCRM2SCRP_1_BUS_SAFETY_ERR;
    uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_CMD;
    uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_READ;
    uint32 SCRM2SCRP_1_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 HSM_M_BUS_SAFETY_CTRL;
    uint32 HSM_M_BUS_SAFETY_FI;
    uint32 HSM_M_BUS_SAFETY_ERR;
    uint32 HSM_M_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 HSM_M_BUS_SAFETY_ERR_STAT_CMD;
    uint32 HSM_M_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 HSM_M_BUS_SAFETY_ERR_STAT_READ;
    uint32 HSM_M_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 HSM_S_BUS_SAFETY_CTRL;
    uint32 HSM_S_BUS_SAFETY_FI;
    uint32 HSM_S_BUS_SAFETY_ERR;
    uint32 HSM_S_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 HSM_S_BUS_SAFETY_ERR_STAT_CMD;
    uint32 HSM_S_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 HSM_S_BUS_SAFETY_ERR_STAT_READ;
    uint32 HSM_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 ICSSM_S_BUS_SAFETY_CTRL;
    uint32 ICSSM_S_BUS_SAFETY_FI;
    uint32 ICSSM_S_BUS_SAFETY_ERR;
    uint32 ICSSM_S_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 ICSSM_S_BUS_SAFETY_ERR_STAT_CMD;
    uint32 ICSSM_S_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 ICSSM_S_BUS_SAFETY_ERR_STAT_READ;
    uint32 ICSSM_S_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 DAP_BUS_SAFETY_CTRL;
    uint32 DAP_BUS_SAFETY_FI;
    uint32 DAP_BUS_SAFETY_ERR;
    uint32 DAP_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 DAP_BUS_SAFETY_ERR_STAT_CMD;
    uint32 DAP_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 DAP_BUS_SAFETY_ERR_STAT_READ;
    uint32 DAP_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_CTRL;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_FI;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_CMD;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_READ;
    uint32 L2OCRAM_BANK0_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_CTRL;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_FI;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_CMD;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_READ;
    uint32 L2OCRAM_BANK1_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_CTRL;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_FI;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_CMD;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_READ;
    uint32 L2OCRAM_BANK2_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_CTRL;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_FI;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_ERR;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_ERR_STAT_CMD;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_ERR_STAT_READ;
    uint32 L2OCRAM_BANK3_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 MBOX_SRAM_BUS_SAFETY_CTRL;
    uint32 MBOX_SRAM_BUS_SAFETY_FI;
    uint32 MBOX_SRAM_BUS_SAFETY_ERR;
    uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_CMD;
    uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_READ;
    uint32 MBOX_SRAM_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 STM_STIM_BUS_SAFETY_CTRL;
    uint32 STM_STIM_BUS_SAFETY_FI;
    uint32 STM_STIM_BUS_SAFETY_ERR;
    uint32 STM_STIM_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 STM_STIM_BUS_SAFETY_ERR_STAT_CMD;
    uint32 STM_STIM_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 STM_STIM_BUS_SAFETY_ERR_STAT_READ;
    uint32 STM_STIM_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 MMC0_BUS_SAFETY_CTRL;
    uint32 MMC0_BUS_SAFETY_FI;
    uint32 MMC0_BUS_SAFETY_ERR;
    uint32 MMC0_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 MMC0_BUS_SAFETY_ERR_STAT_CMD;
    uint32 MMC0_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 MMC0_BUS_SAFETY_ERR_STAT_READ;
    uint32 MMC0_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 GPMC0_BUS_SAFETY_CTRL;
    uint32 GPMC0_BUS_SAFETY_FI;
    uint32 GPMC0_BUS_SAFETY_ERR;
    uint32 GPMC0_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 GPMC0_BUS_SAFETY_ERR_STAT_CMD;
    uint32 GPMC0_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 GPMC0_BUS_SAFETY_ERR_STAT_READ;
    uint32 GPMC0_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 MAIN_VBUSP_BUS_SAFETY_CTRL;
    uint32 MAIN_VBUSP_BUS_SAFETY_FI;
    uint32 MAIN_VBUSP_BUS_SAFETY_ERR;
    uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_CMD;
    uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_READ;
    uint32 MAIN_VBUSP_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_FI;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS0_CORE0_AHB_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_CTRL;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_FI;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS0_CORE1_AHB_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_FI;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS1_CORE0_AHB_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_CTRL;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_FI;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_ERR;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_ERR_STAT_CMD;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_ERR_STAT_READ;
    uint32 R5SS1_CORE1_AHB_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint32 PERI_VBUSP_BUS_SAFETY_CTRL;
    uint32 PERI_VBUSP_BUS_SAFETY_FI;
    uint32 PERI_VBUSP_BUS_SAFETY_ERR;
    uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_DATA0;
    uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_CMD;
    uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_WRITE;
    uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_READ;
    uint32 PERI_VBUSP_BUS_SAFETY_ERR_STAT_WRITERESP;
    uint8  Resv_100384[64];
    uint32 NERROR_MASK;
    uint32 MSS_BUS_SAFETY_SEC_ERR_STAT0;
    uint32 MSS_BUS_SAFETY_SEC_ERR_STAT1;
    uint8  Resv_100404[8];
    uint32 MSS_VBUSM_SAFETY_H_ERRAGG_MASK0;
    uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS0;
    uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS_RAW0;
    uint8  Resv_100420[4];
    uint32 MSS_VBUSM_SAFETY_H_ERRAGG_MASK1;
    uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS1;
    uint32 MSS_VBUSM_SAFETY_H_ERRAGG_STATUS_RAW1;
    uint8  Resv_100436[4];
    uint32 MSS_VBUSM_SAFETY_L_ERRAGG_MASK0;
    uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS0;
    uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS_RAW0;
    uint8  Resv_100452[4];
    uint32 MSS_VBUSM_SAFETY_L_ERRAGG_MASK1;
    uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS1;
    uint32 MSS_VBUSM_SAFETY_L_ERRAGG_STATUS_RAW1;
    uint8  Resv_100468[4];
    uint32 MSS_VBUSP_SAFETY_H_ERRAGG_MASK;
    uint32 MSS_VBUSP_SAFETY_H_ERRAGG_STATUS;
    uint32 MSS_VBUSP_SAFETY_H_ERRAGG_STATUS_RAW;
} ctrlBASE_t;

typedef volatile struct
{
    uint32 PID;
    uint32 INFO;
    uint32 PRIIRQ;
    uint32 PRIFIQ;
    uint32 IRQGSTS;
    uint32 FIQGSTS;
    uint32 IRQVEC;
    uint32 FIQVEC;
    uint32 ACTIRQ;
    uint32 ACTFIQ;
    uint8  Resv_48[8];
    uint32 DEDVEC;
    uint8  Resv_1024[972];
    uint32 RAW;
    uint32 STS;
    uint32 INTR_EN_SET;
    uint32 INTER_EN_CLR;
    uint32 IRQSTS;
    uint32 FIQSTS;
    uint32 INTMAP;
    uint32 INTTYPE;
    uint32 RAW_1;
    uint32 STS_1;
    uint32 INTR_EN_SET_1;
    uint32 INTER_EN_CLR_1;
    uint32 IRQSTS_1;
    uint32 FIQSTS_1;
    uint32 INTMAP_1;
    uint32 INTTYPE_1;
    uint32 RAW_2;
    uint32 STS_2;
    uint32 INTR_EN_SET_2;
    uint32 INTER_EN_CLR_2;
    uint32 IRQSTS_2;
    uint32 FIQSTS_2;
    uint32 INTMAP_2;
    uint32 INTTYPE_2;
    uint32 RAW_3;
    uint32 STS_3;
    uint32 INTR_EN_SET_3;
    uint32 INTER_EN_CLR_3;
    uint32 IRQSTS_3;
    uint32 FIQSTS_3;
    uint32 INTMAP_3;
    uint32 INTTYPE_3;
    uint32 RAW_4;
    uint32 STS_4;
    uint32 INTR_EN_SET_4;
    uint32 INTER_EN_CLR_4;
    uint32 IRQSTS_4;
    uint32 FIQSTS_4;
    uint32 INTMAP_4;
    uint32 INTTYPE_4;
    uint32 RAW_5;
    uint32 STS_5;
    uint32 INTR_EN_SET_5;
    uint32 INTER_EN_CLR_5;
    uint32 IRQSTS_5;
    uint32 FIQSTS_5;
    uint32 INTMAP_5;
    uint32 INTTYPE_5;
    uint32 RAW_6;
    uint32 STS_6;
    uint32 INTR_EN_SET_6;
    uint32 INTER_EN_CLR_6;
    uint32 IRQSTS_6;
    uint32 FIQSTS_6;
    uint32 INTMAP_6;
    uint32 INTTYPE_6;
    uint32 RAW_7;
    uint32 STS_7;
    uint32 INTR_EN_SET_7;
    uint32 INTER_EN_CLR_7;
    uint32 IRQSTS_7;
    uint32 FIQSTS_7;
    uint32 INTMAP_7;
    uint32 INTTYPE_7;
	uint32 RAW_8;
    uint32 STS_8;
    uint32 INTR_EN_SET_8;
    uint32 INTER_EN_CLR_8;
    uint32 IRQSTS_8;
    uint32 FIQSTS_8;
    uint32 INTMAP_8;
    uint32 INTTYPE_8;
	uint32 RAW_9;
    uint32 STS_9;
    uint32 INTR_EN_SET_9;
    uint32 INTER_EN_CLR_9;
    uint32 IRQSTS_9;
    uint32 FIQSTS_9;
    uint32 INTMAP_9;
    uint32 INTTYPE_9;
	uint32 RAW_10;
    uint32 STS_10;
    uint32 INTR_EN_SET_10;
    uint32 INTER_EN_CLR_10;
    uint32 IRQSTS_10;
    uint32 FIQSTS_10;
    uint32 INTMAP_10;
    uint32 INTTYPE_10;
	uint32 RAW_11;
    uint32 STS_11;
    uint32 INTR_EN_SET_11;
    uint32 INTER_EN_CLR_11;
    uint32 IRQSTS_11;
    uint32 FIQSTS_11;
    uint32 INTMAP_11;
    uint32 INTTYPE_11;
	uint32 RAW_12;
    uint32 STS_12;
    uint32 INTR_EN_SET_12;
    uint32 INTER_EN_CLR_12;
    uint32 IRQSTS_12;
    uint32 FIQSTS_12;
    uint32 INTMAP_12;
    uint32 INTTYPE_12;
	uint32 RAW_13;
    uint32 STS_13;
    uint32 INTR_EN_SET_13;
    uint32 INTER_EN_CLR_13;
    uint32 IRQSTS_13;
    uint32 FIQSTS_13;
    uint32 INTMAP_13;
    uint32 INTTYPE_13;
	uint32 RAW_14;
    uint32 STS_14;
    uint32 INTR_EN_SET_14;
    uint32 INTER_EN_CLR_14;
    uint32 IRQSTS_14;
    uint32 FIQSTS_14;
    uint32 INTMAP_14;
    uint32 INTTYPE_14;
	uint32 RAW_15;
    uint32 STS_15;
    uint32 INTR_EN_SET_15;
    uint32 INTER_EN_CLR_15;
    uint32 IRQSTS_15;
    uint32 FIQSTS_15;
    uint32 INTMAP_15;
    uint32 INTTYPE_15;	
    uint8  Resv_4096[2560];
    uint32 INTPRIORITY;
    uint32 INTPRIORITY_1;
    uint32 INTPRIORITY_2;
    uint32 INTPRIORITY_3;
    uint32 INTPRIORITY_4;
    uint32 INTPRIORITY_5;
    uint32 INTPRIORITY_6;
    uint32 INTPRIORITY_7;
    uint32 INTPRIORITY_8;
    uint32 INTPRIORITY_9;
    uint32 INTPRIORITY_10;
    uint32 INTPRIORITY_11;
    uint32 INTPRIORITY_12;
    uint32 INTPRIORITY_13;
    uint32 INTPRIORITY_14;
    uint32 INTPRIORITY_15;
    uint32 INTPRIORITY_16;
    uint32 INTPRIORITY_17;
    uint32 INTPRIORITY_18;
    uint32 INTPRIORITY_19;
    uint32 INTPRIORITY_20;
    uint32 INTPRIORITY_21;
    uint32 INTPRIORITY_22;
    uint32 INTPRIORITY_23;
    uint32 INTPRIORITY_24;
    uint32 INTPRIORITY_25;
    uint32 INTPRIORITY_26;
    uint32 INTPRIORITY_27;
    uint32 INTPRIORITY_28;
    uint32 INTPRIORITY_29;
    uint32 INTPRIORITY_30;
    uint32 INTPRIORITY_31;
    uint32 INTPRIORITY_32;
    uint32 INTPRIORITY_33;
    uint32 INTPRIORITY_34;
    uint32 INTPRIORITY_35;
    uint32 INTPRIORITY_36;
    uint32 INTPRIORITY_37;
    uint32 INTPRIORITY_38;
    uint32 INTPRIORITY_39;
    uint32 INTPRIORITY_40;
    uint32 INTPRIORITY_41;
    uint32 INTPRIORITY_42;
    uint32 INTPRIORITY_43;
    uint32 INTPRIORITY_44;
    uint32 INTPRIORITY_45;
    uint32 INTPRIORITY_46;
    uint32 INTPRIORITY_47;
    uint32 INTPRIORITY_48;
    uint32 INTPRIORITY_49;
    uint32 INTPRIORITY_50;
    uint32 INTPRIORITY_51;
    uint32 INTPRIORITY_52;
    uint32 INTPRIORITY_53;
    uint32 INTPRIORITY_54;
    uint32 INTPRIORITY_55;
    uint32 INTPRIORITY_56;
    uint32 INTPRIORITY_57;
    uint32 INTPRIORITY_58;
    uint32 INTPRIORITY_59;
    uint32 INTPRIORITY_60;
    uint32 INTPRIORITY_61;
    uint32 INTPRIORITY_62;
    uint32 INTPRIORITY_63;
    uint32 INTPRIORITY_64;
    uint32 INTPRIORITY_65;
    uint32 INTPRIORITY_66;
    uint32 INTPRIORITY_67;
    uint32 INTPRIORITY_68;
    uint32 INTPRIORITY_69;
    uint32 INTPRIORITY_70;
    uint32 INTPRIORITY_71;
    uint32 INTPRIORITY_72;
    uint32 INTPRIORITY_73;
    uint32 INTPRIORITY_74;
    uint32 INTPRIORITY_75;
    uint32 INTPRIORITY_76;
    uint32 INTPRIORITY_77;
    uint32 INTPRIORITY_78;
    uint32 INTPRIORITY_79;
    uint32 INTPRIORITY_80;
    uint32 INTPRIORITY_81;
    uint32 INTPRIORITY_82;
    uint32 INTPRIORITY_83;
    uint32 INTPRIORITY_84;
    uint32 INTPRIORITY_85;
    uint32 INTPRIORITY_86;
    uint32 INTPRIORITY_87;
    uint32 INTPRIORITY_88;
    uint32 INTPRIORITY_89;
    uint32 INTPRIORITY_90;
    uint32 INTPRIORITY_91;
    uint32 INTPRIORITY_92;
    uint32 INTPRIORITY_93;
    uint32 INTPRIORITY_94;
    uint32 INTPRIORITY_95;
    uint32 INTPRIORITY_96;
    uint32 INTPRIORITY_97;
    uint32 INTPRIORITY_98;
    uint32 INTPRIORITY_99;
    uint32 INTPRIORITY_100;
    uint32 INTPRIORITY_101;
    uint32 INTPRIORITY_102;
    uint32 INTPRIORITY_103;
    uint32 INTPRIORITY_104;
    uint32 INTPRIORITY_105;
    uint32 INTPRIORITY_106;
    uint32 INTPRIORITY_107;
    uint32 INTPRIORITY_108;
    uint32 INTPRIORITY_109;
    uint32 INTPRIORITY_110;
    uint32 INTPRIORITY_111;
    uint32 INTPRIORITY_112;
    uint32 INTPRIORITY_113;
    uint32 INTPRIORITY_114;
    uint32 INTPRIORITY_115;
    uint32 INTPRIORITY_116;
    uint32 INTPRIORITY_117;
    uint32 INTPRIORITY_118;
    uint32 INTPRIORITY_119;
    uint32 INTPRIORITY_120;
    uint32 INTPRIORITY_121;
    uint32 INTPRIORITY_122;
    uint32 INTPRIORITY_123;
    uint32 INTPRIORITY_124;
    uint32 INTPRIORITY_125;
    uint32 INTPRIORITY_126;
    uint32 INTPRIORITY_127;
    uint32 INTPRIORITY_128;
    uint32 INTPRIORITY_129;
    uint32 INTPRIORITY_130;
    uint32 INTPRIORITY_131;
    uint32 INTPRIORITY_132;
    uint32 INTPRIORITY_133;
    uint32 INTPRIORITY_134;
    uint32 INTPRIORITY_135;
    uint32 INTPRIORITY_136;
    uint32 INTPRIORITY_137;
    uint32 INTPRIORITY_138;
    uint32 INTPRIORITY_139;
    uint32 INTPRIORITY_140;
    uint32 INTPRIORITY_141;
    uint32 INTPRIORITY_142;
    uint32 INTPRIORITY_143;
    uint32 INTPRIORITY_144;
    uint32 INTPRIORITY_145;
    uint32 INTPRIORITY_146;
    uint32 INTPRIORITY_147;
    uint32 INTPRIORITY_148;
    uint32 INTPRIORITY_149;
    uint32 INTPRIORITY_150;
    uint32 INTPRIORITY_151;
    uint32 INTPRIORITY_152;
    uint32 INTPRIORITY_153;
    uint32 INTPRIORITY_154;
    uint32 INTPRIORITY_155;
    uint32 INTPRIORITY_156;
    uint32 INTPRIORITY_157;
    uint32 INTPRIORITY_158;
    uint32 INTPRIORITY_159;
    uint32 INTPRIORITY_160;
    uint32 INTPRIORITY_161;
    uint32 INTPRIORITY_162;
    uint32 INTPRIORITY_163;
    uint32 INTPRIORITY_164;
    uint32 INTPRIORITY_165;
    uint32 INTPRIORITY_166;
    uint32 INTPRIORITY_167;
    uint32 INTPRIORITY_168;
    uint32 INTPRIORITY_169;
    uint32 INTPRIORITY_170;
    uint32 INTPRIORITY_171;
    uint32 INTPRIORITY_172;
    uint32 INTPRIORITY_173;
    uint32 INTPRIORITY_174;
    uint32 INTPRIORITY_175;
    uint32 INTPRIORITY_176;
    uint32 INTPRIORITY_177;
    uint32 INTPRIORITY_178;
    uint32 INTPRIORITY_179;
    uint32 INTPRIORITY_180;
    uint32 INTPRIORITY_181;
    uint32 INTPRIORITY_182;
    uint32 INTPRIORITY_183;
    uint32 INTPRIORITY_184;
    uint32 INTPRIORITY_185;
    uint32 INTPRIORITY_186;
    uint32 INTPRIORITY_187;
    uint32 INTPRIORITY_188;
    uint32 INTPRIORITY_189;
    uint32 INTPRIORITY_190;
    uint32 INTPRIORITY_191;
    uint32 INTPRIORITY_192;
    uint32 INTPRIORITY_193;
    uint32 INTPRIORITY_194;
    uint32 INTPRIORITY_195;
    uint32 INTPRIORITY_196;
    uint32 INTPRIORITY_197;
    uint32 INTPRIORITY_198;
    uint32 INTPRIORITY_199;
    uint32 INTPRIORITY_200;
    uint32 INTPRIORITY_201;
    uint32 INTPRIORITY_202;
    uint32 INTPRIORITY_203;
    uint32 INTPRIORITY_204;
    uint32 INTPRIORITY_205;
    uint32 INTPRIORITY_206;
    uint32 INTPRIORITY_207;
    uint32 INTPRIORITY_208;
    uint32 INTPRIORITY_209;
    uint32 INTPRIORITY_210;
    uint32 INTPRIORITY_211;
    uint32 INTPRIORITY_212;
    uint32 INTPRIORITY_213;
    uint32 INTPRIORITY_214;
    uint32 INTPRIORITY_215;
    uint32 INTPRIORITY_216;
    uint32 INTPRIORITY_217;
    uint32 INTPRIORITY_218;
    uint32 INTPRIORITY_219;
    uint32 INTPRIORITY_220;
    uint32 INTPRIORITY_221;
    uint32 INTPRIORITY_222;
    uint32 INTPRIORITY_223;
    uint32 INTPRIORITY_224;
    uint32 INTPRIORITY_225;
    uint32 INTPRIORITY_226;
    uint32 INTPRIORITY_227;
    uint32 INTPRIORITY_228;
    uint32 INTPRIORITY_229;
    uint32 INTPRIORITY_230;
    uint32 INTPRIORITY_231;
    uint32 INTPRIORITY_232;
    uint32 INTPRIORITY_233;
    uint32 INTPRIORITY_234;
    uint32 INTPRIORITY_235;
    uint32 INTPRIORITY_236;
    uint32 INTPRIORITY_237;
    uint32 INTPRIORITY_238;
    uint32 INTPRIORITY_239;
    uint32 INTPRIORITY_240;
    uint32 INTPRIORITY_241;
    uint32 INTPRIORITY_242;
    uint32 INTPRIORITY_243;
    uint32 INTPRIORITY_244;
    uint32 INTPRIORITY_245;
    uint32 INTPRIORITY_246;
    uint32 INTPRIORITY_247;
    uint32 INTPRIORITY_248;
    uint32 INTPRIORITY_249;
    uint32 INTPRIORITY_250;
    uint32 INTPRIORITY_251;
    uint32 INTPRIORITY_252;
    uint32 INTPRIORITY_253;
    uint32 INTPRIORITY_254;
    uint32 INTPRIORITY_255;
    uint8  Resv_8192[3072];
    uint32 INTVECTOR;
    uint32 INTVECTOR_1;
    uint32 INTVECTOR_2;
    uint32 INTVECTOR_3;
    uint32 INTVECTOR_4;
    uint32 INTVECTOR_5;
    uint32 INTVECTOR_6;
    uint32 INTVECTOR_7;
    uint32 INTVECTOR_8;
    uint32 INTVECTOR_9;
    uint32 INTVECTOR_10;
    uint32 INTVECTOR_11;
    uint32 INTVECTOR_12;
    uint32 INTVECTOR_13;
    uint32 INTVECTOR_14;
    uint32 INTVECTOR_15;
    uint32 INTVECTOR_16;
    uint32 INTVECTOR_17;
    uint32 INTVECTOR_18;
    uint32 INTVECTOR_19;
    uint32 INTVECTOR_20;
    uint32 INTVECTOR_21;
    uint32 INTVECTOR_22;
    uint32 INTVECTOR_23;
    uint32 INTVECTOR_24;
    uint32 INTVECTOR_25;
    uint32 INTVECTOR_26;
    uint32 INTVECTOR_27;
    uint32 INTVECTOR_28;
    uint32 INTVECTOR_29;
    uint32 INTVECTOR_30;
    uint32 INTVECTOR_31;
    uint32 INTVECTOR_32;
    uint32 INTVECTOR_33;
    uint32 INTVECTOR_34;
    uint32 INTVECTOR_35;
    uint32 INTVECTOR_36;
    uint32 INTVECTOR_37;
    uint32 INTVECTOR_38;
    uint32 INTVECTOR_39;
    uint32 INTVECTOR_40;
    uint32 INTVECTOR_41;
    uint32 INTVECTOR_42;
    uint32 INTVECTOR_43;
    uint32 INTVECTOR_44;
    uint32 INTVECTOR_45;
    uint32 INTVECTOR_46;
    uint32 INTVECTOR_47;
    uint32 INTVECTOR_48;
    uint32 INTVECTOR_49;
    uint32 INTVECTOR_50;
    uint32 INTVECTOR_51;
    uint32 INTVECTOR_52;
    uint32 INTVECTOR_53;
    uint32 INTVECTOR_54;
    uint32 INTVECTOR_55;
    uint32 INTVECTOR_56;
    uint32 INTVECTOR_57;
    uint32 INTVECTOR_58;
    uint32 INTVECTOR_59;
    uint32 INTVECTOR_60;
    uint32 INTVECTOR_61;
    uint32 INTVECTOR_62;
    uint32 INTVECTOR_63;
    uint32 INTVECTOR_64;
    uint32 INTVECTOR_65;
    uint32 INTVECTOR_66;
    uint32 INTVECTOR_67;
    uint32 INTVECTOR_68;
    uint32 INTVECTOR_69;
    uint32 INTVECTOR_70;
    uint32 INTVECTOR_71;
    uint32 INTVECTOR_72;
    uint32 INTVECTOR_73;
    uint32 INTVECTOR_74;
    uint32 INTVECTOR_75;
    uint32 INTVECTOR_76;
    uint32 INTVECTOR_77;
    uint32 INTVECTOR_78;
    uint32 INTVECTOR_79;
    uint32 INTVECTOR_80;
    uint32 INTVECTOR_81;
    uint32 INTVECTOR_82;
    uint32 INTVECTOR_83;
    uint32 INTVECTOR_84;
    uint32 INTVECTOR_85;
    uint32 INTVECTOR_86;
    uint32 INTVECTOR_87;
    uint32 INTVECTOR_88;
    uint32 INTVECTOR_89;
    uint32 INTVECTOR_90;
    uint32 INTVECTOR_91;
    uint32 INTVECTOR_92;
    uint32 INTVECTOR_93;
    uint32 INTVECTOR_94;
    uint32 INTVECTOR_95;
    uint32 INTVECTOR_96;
    uint32 INTVECTOR_97;
    uint32 INTVECTOR_98;
    uint32 INTVECTOR_99;
    uint32 INTVECTOR_100;
    uint32 INTVECTOR_101;
    uint32 INTVECTOR_102;
    uint32 INTVECTOR_103;
    uint32 INTVECTOR_104;
    uint32 INTVECTOR_105;
    uint32 INTVECTOR_106;
    uint32 INTVECTOR_107;
    uint32 INTVECTOR_108;
    uint32 INTVECTOR_109;
    uint32 INTVECTOR_110;
    uint32 INTVECTOR_111;
    uint32 INTVECTOR_112;
    uint32 INTVECTOR_113;
    uint32 INTVECTOR_114;
    uint32 INTVECTOR_115;
    uint32 INTVECTOR_116;
    uint32 INTVECTOR_117;
    uint32 INTVECTOR_118;
    uint32 INTVECTOR_119;
    uint32 INTVECTOR_120;
    uint32 INTVECTOR_121;
    uint32 INTVECTOR_122;
    uint32 INTVECTOR_123;
    uint32 INTVECTOR_124;
    uint32 INTVECTOR_125;
    uint32 INTVECTOR_126;
    uint32 INTVECTOR_127;
    uint32 INTVECTOR_128;
    uint32 INTVECTOR_129;
    uint32 INTVECTOR_130;
    uint32 INTVECTOR_131;
    uint32 INTVECTOR_132;
    uint32 INTVECTOR_133;
    uint32 INTVECTOR_134;
    uint32 INTVECTOR_135;
    uint32 INTVECTOR_136;
    uint32 INTVECTOR_137;
    uint32 INTVECTOR_138;
    uint32 INTVECTOR_139;
    uint32 INTVECTOR_140;
    uint32 INTVECTOR_141;
    uint32 INTVECTOR_142;
    uint32 INTVECTOR_143;
    uint32 INTVECTOR_144;
    uint32 INTVECTOR_145;
    uint32 INTVECTOR_146;
    uint32 INTVECTOR_147;
    uint32 INTVECTOR_148;
    uint32 INTVECTOR_149;
    uint32 INTVECTOR_150;
    uint32 INTVECTOR_151;
    uint32 INTVECTOR_152;
    uint32 INTVECTOR_153;
    uint32 INTVECTOR_154;
    uint32 INTVECTOR_155;
    uint32 INTVECTOR_156;
    uint32 INTVECTOR_157;
    uint32 INTVECTOR_158;
    uint32 INTVECTOR_159;
    uint32 INTVECTOR_160;
    uint32 INTVECTOR_161;
    uint32 INTVECTOR_162;
    uint32 INTVECTOR_163;
    uint32 INTVECTOR_164;
    uint32 INTVECTOR_165;
    uint32 INTVECTOR_166;
    uint32 INTVECTOR_167;
    uint32 INTVECTOR_168;
    uint32 INTVECTOR_169;
    uint32 INTVECTOR_170;
    uint32 INTVECTOR_171;
    uint32 INTVECTOR_172;
    uint32 INTVECTOR_173;
    uint32 INTVECTOR_174;
    uint32 INTVECTOR_175;
    uint32 INTVECTOR_176;
    uint32 INTVECTOR_177;
    uint32 INTVECTOR_178;
    uint32 INTVECTOR_179;
    uint32 INTVECTOR_180;
    uint32 INTVECTOR_181;
    uint32 INTVECTOR_182;
    uint32 INTVECTOR_183;
    uint32 INTVECTOR_184;
    uint32 INTVECTOR_185;
    uint32 INTVECTOR_186;
    uint32 INTVECTOR_187;
    uint32 INTVECTOR_188;
    uint32 INTVECTOR_189;
    uint32 INTVECTOR_190;
    uint32 INTVECTOR_191;
    uint32 INTVECTOR_192;
    uint32 INTVECTOR_193;
    uint32 INTVECTOR_194;
    uint32 INTVECTOR_195;
    uint32 INTVECTOR_196;
    uint32 INTVECTOR_197;
    uint32 INTVECTOR_198;
    uint32 INTVECTOR_199;
    uint32 INTVECTOR_200;
    uint32 INTVECTOR_201;
    uint32 INTVECTOR_202;
    uint32 INTVECTOR_203;
    uint32 INTVECTOR_204;
    uint32 INTVECTOR_205;
    uint32 INTVECTOR_206;
    uint32 INTVECTOR_207;
    uint32 INTVECTOR_208;
    uint32 INTVECTOR_209;
    uint32 INTVECTOR_210;
    uint32 INTVECTOR_211;
    uint32 INTVECTOR_212;
    uint32 INTVECTOR_213;
    uint32 INTVECTOR_214;
    uint32 INTVECTOR_215;
    uint32 INTVECTOR_216;
    uint32 INTVECTOR_217;
    uint32 INTVECTOR_218;
    uint32 INTVECTOR_219;
    uint32 INTVECTOR_220;
    uint32 INTVECTOR_221;
    uint32 INTVECTOR_222;
    uint32 INTVECTOR_223;
    uint32 INTVECTOR_224;
    uint32 INTVECTOR_225;
    uint32 INTVECTOR_226;
    uint32 INTVECTOR_227;
    uint32 INTVECTOR_228;
    uint32 INTVECTOR_229;
    uint32 INTVECTOR_230;
    uint32 INTVECTOR_231;
    uint32 INTVECTOR_232;
    uint32 INTVECTOR_233;
    uint32 INTVECTOR_234;
    uint32 INTVECTOR_235;
    uint32 INTVECTOR_236;
    uint32 INTVECTOR_237;
    uint32 INTVECTOR_238;
    uint32 INTVECTOR_239;
    uint32 INTVECTOR_240;
    uint32 INTVECTOR_241;
    uint32 INTVECTOR_242;
    uint32 INTVECTOR_243;
    uint32 INTVECTOR_244;
    uint32 INTVECTOR_245;
    uint32 INTVECTOR_246;
    uint32 INTVECTOR_247;
    uint32 INTVECTOR_248;
    uint32 INTVECTOR_249;
    uint32 INTVECTOR_250;
    uint32 INTVECTOR_251;
    uint32 INTVECTOR_252;
    uint32 INTVECTOR_253;
    uint32 INTVECTOR_254;
    uint32 INTVECTOR_255;
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
    uint32 PID;
    uint32 MDO_CTRL;
    uint32 PROBE_BUS_SEL0;
    uint32 PROBE_BUS_SEL1;
    uint8  Resv_512[496];
    uint32 EFUSE_DIEID0;
    uint32 EFUSE_DIEID1;
    uint32 EFUSE_DIEID2;
    uint32 EFUSE_DIEID3;
    uint32 EFUSE_UID0;
    uint32 EFUSE_UID1;
    uint32 EFUSE_UID2;
    uint32 EFUSE_UID3;
    uint32 EFUSE_DEVICE_TYPE;
    uint32 EFUSE_FROM0_CHECKSUM;
    uint32 EFUSE_ROM_SEQ_UPDATE0;
    uint32 EFUSE_ROM_SEQ_UPDATE1;
    uint32 EFUSE_ROM_SEQ_UPDATE2;
    uint32 EFUSE_ROM_SEQ_UPDATE3;
    uint32 EFUSE_ROM_SEQ_UPDATE4;
    uint32 EFUSE_ROM_SEQ_UPDATE5;
    uint32 EFUSE_ROM_SEQ_UPDATE6;
    uint32 EFUSE_ROM_SEQ_UPDATE7;
    uint32 EFUSE_ROM_SEQ_UPDATE8;
    uint8  Resv_1024[436];
    uint32 EFUSE0_ROW_61;
    uint32 EFUSE0_ROW_62;
    uint32 EFUSE0_ROW_63;
    uint32 EFUSE1_ROW_5;
    uint32 EFUSE1_ROW_6;
    uint32 EFUSE1_ROW_7;
    uint32 EFUSE1_ROW_8;
    uint32 EFUSE1_ROW_9;
    uint32 EFUSE1_ROW_10;
    uint32 EFUSE1_ROW_11;
    uint32 EFUSE1_ROW_12;
    uint32 EFUSE1_ROW_13;
    uint32 EFUSE1_ROW_14;
    uint32 EFUSE1_ROW_15;
    uint32 EFUSE1_ROW_16;
    uint32 EFUSE1_ROW_17;
    uint32 EFUSE1_ROW_18;
    uint32 EFUSE1_ROW_19;
    uint32 EFUSE1_ROW_20;
    uint32 EFUSE1_ROW_21;
    uint32 EFUSE1_ROW_22;
    uint32 EFUSE1_ROW_23;
    uint32 EFUSE1_ROW_24;
    uint32 EFUSE1_ROW_25;
    uint32 EFUSE1_ROW_26;
    uint32 EFUSE1_ROW_27;
    uint32 EFUSE1_ROW_28;
    uint32 EFUSE1_ROW_29;
    uint32 EFUSE1_ROW_30;
    uint32 EFUSE1_ROW_31;
    uint32 EFUSE1_ROW_32;
    uint32 EFUSE1_ROW_33;
    uint32 EFUSE1_ROW_34;
    uint32 EFUSE1_ROW_35;
    uint32 EFUSE1_ROW_36;
    uint32 EFUSE1_ROW_37;
    uint32 EFUSE1_ROW_38;
    uint32 EFUSE1_ROW_39;
    uint32 EFUSE1_ROW_40;
    uint32 EFUSE1_ROW_41;
    uint32 EFUSE1_ROW_42;
    uint32 EFUSE1_ROW_43;
    uint8  Resv_2048[856];
    uint32 EFUSE_OVERRIDE_HSM_HALT_ON_ROM_ECC_ERR_EN;
    uint32 EFUSE_OVERRIDE_MEM_MARGINCTRL;
    uint32 EFUSE_OVERRIDE_LVDS_BGAP_TRIM;
    uint32 EFUSE_OVERRIDE_XTAL_STABLIZATION_WAIT;
    uint32 EFUSE_OVERRIDE_SLICER_BIAS_RTRIM;
    uint32 EFUSE_OVERRIDE_XO_OUTPUT_DRIVE;
    uint32 EFUSE_OVERRIDE_RCOSC_TRIM_CODE;
    uint32 EFUSE_OVERRIDE_IP1_BG1_RTRIM;
    uint32 EFUSE_OVERRIDE_IP1_BG1_SLOPE;
    uint32 EFUSE_OVERRIDE_IP1_BG1_MAG;
    uint32 EFUSE_OVERRIDE_RS232_CLKMODE;
    uint32 EFUSE_OVERRIDE_VMON_VDD_OV_UV_TRIM;
    uint32 EFUSE_OVERRIDE_VMON_VDDS_3P3_UV_TRIM;
    uint32 EFUSE_OVERRIDE_VMON_VDDA_OSC_TRIM;
    uint32 EFUSE_OVERRIDE_VDD_VT_DET;
    uint32 EFUSE_OVERRIDE_MASK_CPU_CLK_OUT_CTRL_LOWV_VAL;
    uint32 EFUSE_OVERRIDE_MASK_CPU_CLK_OUT_CTRL_LOWV_SEL;
    uint32 EFUSE_OVERRIDE_EN_VOL_MON_FUNC;
    uint32 EFUSE_OVERRIDE_BYPASS_HOLDBUFFER_ENABLE;
    uint8  Resv_4048[1924];
    uint32 HW_SPARE_RW0;
    uint32 HW_SPARE_RW1;
    uint32 HW_SPARE_RW2;
    uint32 HW_SPARE_RW3;
    uint32 HW_SPARE_RO0;
    uint32 HW_SPARE_RO1;
    uint32 HW_SPARE_RO2;
    uint32 HW_SPARE_RO3;
    uint32 HW_SPARE_WPH;
    uint32 HW_SPARE_REC;
    uint8  Resv_4104[16];
    uint32 LOCK0_KICK0;
    uint32 LOCK0_KICK1;
    uint32 INTR_RAW_STATUS;
    uint32 INTR_ENABLED_STATUS_CLEAR;
    uint32 INTR_ENABLE;
    uint32 INTR_ENABLE_CLEAR;
    uint32 EOI;
    uint32 FAULT_ADDRESS;
    uint32 FAULT_TYPE_STATUS;
    uint32 FAULT_ATTR_STATUS;
    uint32 FAULT_CLEAR;
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

/* PIN LB, PADDVWfunctionality */
#define PINLB_CLKLB                          0X244U
#define PINLB_CLKLB_QSPI0_CLKLB              0X0U

#define MSS_CPSW_CONTROL_REG             (0x810U)
#define MSS_IOCFGKICK0                   (0x00001008U)
#define MSS_IOCFGKICK1                   (0x0000100CU)
/* PIN P1, QSPI0_CSN0 functionality */
#define PINP1_QSPI0_CSN0                          0X000U
#define PINP1_QSPI0_CSN0_QSPI0_CSn0               0X0U
#define PINP1_QSPI0_CSN0_GPIOAB_0                   0X7U

/* PIN R3, QSPI0_CSN1  functionality */
#define PINR3_QSPI0_CSN1                          0X004U
#define PINR3_QSPI0_CSN1_QSPI0_CSn1               0X0U
#define PINR3_QSPI0_CSN1_XBAROUT0                 0X5U
#define PINR3_QSPI0_CSN1_GPIOAB_1                   0X7U


/* PIN N2, QSPI0_CLK functionality */
#define PINN2_QSPI0_CLK                          0X008U
#define PINN2_QSPI0_CLK_QSPI0_CLK                0X0U
#define PINN2_QSPI0_CLK_GPIOAB_2                   0X7U

/* PIN N1, QSPI0_D0 functionality */
#define PINN1_QSPI0_D0                          0X0CU
#define PINN1_QSPI0_D0_QSPI0_D0                 0X0U
#define PINN1_QSPI0_D0_GPIOAB_3                   0X7U

/* PIN N4,QSPI0_D1 functionality */
#define PINN4_QSPI0_D1                          0X010U
#define PINN4_QSPI0_D1_QSPI0_D1                  0X0U
#define PINN4_QSPI0_D1_GPIOAB_4                    0X7U


/* PIN M4, QSPI0_D2 functionality */
#define PINN4_QSPI0_D2                           0X14U
#define PINN4_QSPI0_D2_QSPI0_D2                  0X0U
#define PINN4_QSPI0_D2_GPIOAB_5                    0X7U

/* PIN P3, QSPI0_D3 functionality */
#define PINN4_QSPI0_D3                           0X18U
#define PINN4_QSPI0_D3_QSPI0_D3                  0X0U
#define PINN4_QSPI0_D3_GPIOAB_6                    0X7U

/* PIN M1, MCAN0_RX functionality */
#define PINM1_MCAN0_RX                          0X1CU
#define PINM1_MCAN0_RX_MCAN0_RX                 0X0U
#define PINM1_MCAN0_RX_SPI4_CS0                 0X1U
#define PINM1_MCAN0_RX_GPIOAB_7                    0X7U


/* PIN L1, MCAN0_TX functionality */
#define PINL1_MCAN0_TX                          0X20U
#define PINL1_MCAN0_TX_MCAN0_TX                 0X0U
#define PINL1_MCAN0_TX_SPI4_CLK                 0X1U
#define PINL1_MCAN0_TX_GPIOAB_8                   0X7U


/* PIN L2, MCAN1_RX functionality */
#define PINL2_MCAN1_RX                          0X24U
#define PINL2_MCAN1_RX_MCAN1_RX                 0X0U
#define PINL2_MCAN1_RX_SPI4_D0                  0X1U
#define PINL2_MCAN1_RX_GPIOAB_9                   0X7U

/* PIN K1, MCAN1_TX functionality */
#define PINK1_MCAN1_TX                          0X28U
#define PINK1_MCAN1_TX_MCAN1_TX                 0X0U
#define PINK1_MCAN1_TX_SPI4_D1                  0X1U
#define PINK1_MCAN1_TX_GPIOAB_10                  0X7U


/* PIN C11, SPI0_CS0 functionality */
#define PINC11_SPI0_CS0                       0X02CU
#define PINC11_SPI0_CS0_SPI0_CS0                0X0U
#define PINC11_SPI0_CS0_UART3_RXD               0X1U
#define PINC11_SPI0_CS0_LIN3_RXD                0X2U
#define PINC11_SPI0_CS0_GPIOAB_11                 0X7U



/* PIN A11, SPI0_CLK functionality */
#define PINA11_SPI0_CLK                          0X030U
#define PINA11_SPI0_CLK_SPI0_CLK                 0X0U
#define PINA11_SPI0_CLK_UART3_TXD                0X1U
#define PINA11_SPI0_CLK_LIN3_TXD                 0X2U
#define PINA11_SPI0_CLK_FSITX0_CLK               0X6U
#define PINA11_SPI0_CLK_GPIOAB_12                  0X7U

/*PIN C10, SPI0_D0 functionality */
#define PINC10_SPI0_D0                           0X034U
#define PINC10_SPI0_D0_SPI0_D0                   0X0U
#define PINC10_SPI0_D0_FSITX0_DATA0              0X6U
#define PINC10_SPI0_D0_GPIOAB_13                   0X7U

/* PIN B11, SPI0_D1 functionality */
#define PINB11_SPI0_D1                           0X38U
#define PINB11_SPI0_D1_SPI0_D0                   0X0U
#define PINB11_SPI0_D1_FSITX0_DATA0              0X6U
#define PINB11_SPI0_D1_GPIOAB_14                   0X7U

/* PIN C9, SPI1_CS0 functionality */
#define PINC9_SPI1_CS0                           0X03CU
#define PINRC9_PADFC_SPI1_CS0                    0X0U
#define PINC9_SPI1_CS0_UART4_TXD                 0X1U
#define PINC9_SPI1_CS0_LIN4_TXD                  0X2U
#define PINC9_SPI1_CS0_XBAROUT1                  0X6U
#define PINC9_SPI1_CS0_GPIOAB_15                   0X7U

/* PIN A10, SPI1_CLK functionality */
#define PINA10_SPI1_CLK                          0X40U
#define PINA10_SPI1_CLK_SPI1_CLK                 0X0U
#define PINA10_SPI1_CLK_UART4_RXD                0X1U
#define PINA10_SPI1_CLK_LIN4_RXD                 0X2U
#define PINA10_SPI1_CLK_XBAROUT2                 0X5U
#define PINA10_SPI1_CLK_FSIRX0_CLK               0X6U
#define PINA10_SPI1_CLK_GPIOAB_16                  0X7U


/* PIN B10, SPI1_D0 functionality */
#define PINB10_SPI1_D0                          0X44U
#define PINB10_SPI1_D0_SPI1_D0                  0X0U
#define PINB10_SPI1_D0_UART5_TXD                0X1U
#define PINB10_SPI1_D0_XBAROUT3                 0X5U
#define PINB10_SPI1_D0_FSIRX0_DATA0             0X6U
#define PINB10_SPI1_D0_GPIOAB_17                  0X7U

/* PIN D9, SPI1_D1 functionality */
#define PIND9_SPI1_D1                           0X48U
#define PIND9_SPI1_D1_SPI1_D1                   0X0U
#define PIND9_SPI1_D1_UART5_RXD                 0X1U
#define PIND9_SPI1_D1_XBAROUT4                  0X5U
#define PIND9_SPI1_D1_FSIRX0_DATA1              0X6U
#define PIND9_SPI1_D1_GPIOAB_18                   0X7U

/* PIN A9, LIN1_RXD functionality */
#define PINA9_LIN1_RXD                          0X4CU
#define PINA9_LIN1_RXD_LIN1_RXD                  0X0U
#define PINA9_LIN1_RXD_UART1_RXD                 0X1U
#define PINA9_LIN1_RXD_SPI2_CS0                  0X2U
#define PINA9_LIN1_RXD_GPIOAB_19                   0X7U
#define PINA9_LIN1_RXD_XBAROUT5                  0X5U 

/* PIN B9, LIN1_TXD functionality */
#define PINB9_LIN1_TXD                         0X50U
#define PINB9_LIN1_TXD_LIN1_TXD                0X0U
#define PINB9_LIN1_TXD_UART1_TXD               0X1U
#define PINB9_LIN1_TXD_SPI2_CLK                0X2U
#define PINB9_LIN1_TXD_XBAROUT6                0X5U
#define PINB9_LIN1_TXD_GPIOAB_20                 0X7U

/* PIN B8, LIN2_RXD functionality */
#define PINB8_LIN2_RXD                       0X54U
#define PINB8_LIN2_RXD_LIN2_RXD              0X0U
#define PINB8_LIN2_RXD_UART2_RXD             0X1U
#define PINB8_LIN2_RXD_SPI2_D0               0X2U
#define PINB8_LIN2_RXD_GPIOAB_21               0X7U

/* PIN A8, LIN2_TXD functionality */
#define PINA8_LIN2_TXD                          0X58U
#define PINA8_LIN2_TXD_LIN2_TXD                 0X0U
#define PINA8_LIN2_TXD_UART2_TXD                0X1U
#define PINA8_LIN2_TXD_SPI2_D1                  0X2U
#define PINA8_LIN2_TXD_GPIOAB_22                  0X7U

/* PIN D7, I2C1_SCL functionality */
#define PIND7_I2C1_SCL                          0X5CU
#define PIND7_I2C1_SCL_I2C1_SCL                 0X0U
#define PIND7_I2C1_SCL_SPI3_CS0                 0X2U
#define PIND7_I2C1_SCL_XBAROUT7                 0X5U
#define PIND7_I2C1_SCL_GPIOAB_23                  0X7U

/* PIN C8, I2C1_SDA functionality */
#define PINC8_I2C1_SDA                          0X060U
#define PINC8_I2C1_SDA_I2C1_SDA                 0X0U
#define PINC8_I2C1_SDA_SPI3_CLK                 0X2U
#define PINC8_I2C1_SDA_XBAROUT8                 0X5U
#define PINC8_I2C1_SDA_GPIOAB_24                  0X7U


/* PIN C7, UART0_RTSN functionality */
#define PINC7_UART0_RTSN                          0X064U
#define PINC7_UART0_RTSN_UART0_RTSn               0X0U
#define PINC7_UART0_RTSN_I2C2_SCL                 0X1U
#define PINC7_UART0_RTSN_SPI3_D0                  0X2U
#define PINC7_UART0_RTSN_MCAN3_TX                 0X3U
#define PINC7_UART0_RTSN_XBAROUT9                 0X5U
#define PINC7_UART0_RTSN_GPIOAB_25                  0X7U

/* PIN B7, UART0_CTSn functionality */
#define PINB7_UART0_CTSn                          0X068U
#define PINB7_UART0_CTSn_UART0_CTSn               0X0U
#define PINB7_UART0_CTSn_I2C2_SDA                 0X1U
#define PINB7_UART0_CTSn_SPI3_D1                  0X2U
#define PINB7_UART0_CTSn_MCAN3_RX                 0X3U
#define PINB7_UART0_CTSn_SPI0_CS1                 0X4U
#define PINB7_UART0_CTSn_XBAROUT10                0X5U
#define PINB7_UART0_CTSn_GPIOAB_26                  0X7U

/* PIN A7, UART0_RXD functionality */
#define PINA7_UART0_RXD                          0X06CU
#define PINA7_UART0_RXD_UART0_RXD                0X0U
#define PINA7_UART0_RXD_LIN0_RXD                 0X1U
#define PINA7_UART0_RXD_GPIOAB_27                  0X7U


/* PIN A6, UART0_TXD functionality */
#define PINA6_UART0_TXD                          0X070U
#define PINA6_UART0_TXD_UART0_TXD                0X0U
#define PINA6_UART0_TXD_LIN0_TXD                 0X1U
#define PINA6_UART0_TXD_GPIOAB_28                  0X7U


/* PIN R17, RGMII1_RXC functionality */
#define PINR17_RGMII1_RXC                          0X074U
#define PINR17_RGMII1_RXC_RGMII1_RXC               0X0U
#define PINR17_RGMII1_RXC_RMII1_REF_CLK            0X1U
#define PINR17_RGMII1_RXC_MII1_RXCLK               0X2U
#define PINR17_RGMII1_RXC_FSITX0_CLK               0X6U
#define PINR17_RGMII1_RXC_GPIOAB_29                       0X7U
#define PINR17_RGMII1_RXC_EQEP2_A                  0X8U


/* PIN R18, RGMII1_RX_CTL functionality */
#define PINR18_RGMII1_RX_CTL                          0X78U
#define PINR18_RGMII1_RX_CTL_RGMII1_RX_CTL            0X0U
#define PINR18_RGMII1_RX_CTL_RMII1_RX_ER              0X1U
#define PINR18_RGMII1_RX_CTL_MII1_RXDV                0X2U
#define PINR18_RGMII1_RX_CTL_FSITX0_DATA0             0X6U
#define PINR18_RGMII1_RX_CTL_GPIOAB_30                  0X7U
#define PINR18_RGMII1_RX_CTL_EQEP2_B                  0X8U


/* PIN U17, RGMII1_RD0 functionality */
#define PINU17_RGMII1_RD0                           0X07CU
#define PINU17_RGMII1_RD0_RGMII1_RD0                0X0U
#define PINU17_RGMII1_RD0_RMII1_RXD0                0X1U
#define PINU17_RGMII1_RD0_MII1_RXD0                 0X2U
#define PINU17_RGMII1_RD0_FSITX0_DATA1              0X6U
#define PINU17_RGMII1_RD0_GPIOAB_31                   0X7U
#define PINU17_RGMII1_RD0_EQEP2_S                   0X8U

/* PIN T17, RGMII1_RD1 functionality */
#define PINT17_RGMII1_RD1                           0X80U
#define PINT17_RGMII1_RD1_RGMII1_RD1                0X0U
#define PINT17_RGMII1_RD1_RMII1_RXD1                0X1U
#define PINT17_RGMII1_RD1_MII1_RXD1                 0X2U
#define PINT17_RGMII1_RD1_FSIRX0_CLK                0X6U
#define PINT17_RGMII1_RD1_GPIOCD_32                   0X7U
#define PINT17_RGMII1_RD1_EQEP2_I                   0X8U

/* PIN U18, RGMII1_RD2 functionality */
#define PINU18_RGMII1_RD2                          0X084U
#define PINU18_RGMII1_RD2_RGMII1_RD2               0X0U
#define PINU18_RGMII1_RD2_MII1_RXD3                0X2U
#define PINU18_RGMII1_RD2_EQEP0_A                  0X8U
#define PINU18_RGMII1_RD2_FSIRX0_DATA1             0X6U
#define PINE16_PADEI_GPIOCD_33                       0X7U


/* PIN T18, RGMII1_RD3 functionality */
#define PINT18_RGMII1_RD3                          0X88U
#define PINT18_RGMII1_RD3_RGMII1_RD3               0X0U
#define PINT18_RGMII1_RD3_MII1_RXD3                0X2U
#define PINT18_RGMII1_RD3_FSIRX0_DATA1             0X6U
#define PIND18_PADEJ_GPIOCD_34                       0X7U
#define PIND18_PADEJ_EQEP0_B                       0X8U

/* PIN N18, RGMII1_TXC functionality */
#define PINN18_RGMII1_TXC                           0X08CU
#define PINN18_RGMII1_TXC_RGMII1_TXC                0X0U
#define PINN18_RGMII1_TXC_MII1_TXCLK                0X2U
#define PINN18_RGMII1_TXC_EQEP0_I                   0X8U
#define PINN18_RGMII1_TXC_FSITX1_CLK                0X6U
#define PINN18_RGMII1_TXC_GPIOCD_35                   0X7U


/* PIN M18, RGMII1_TX_CTL functionality */
#define PINM18_RGMII1_TX_CTL                           0X90U
#define PINM18_RGMII1_TX_CTL_RGMII1_TX_CTL             0X0U
#define PINM18_RGMII1_TX_CTL_RMII1_TX_EN               0X1U
#define PINM18_RGMII1_TX_CTL_MII1_TX_EN                0X2U
#define PINM18_RGMII1_TX_CTL_FSITX1_DATA0              0X6U
#define PINM18_RGMII1_TX_CTL_GPIOCD_36                   0X7U
#define PINM18_RGMII1_TX_CTL_EQEP0_S                   0X8U



/* PIN P16, RGMII1_TD0 functionality */
#define PINP16_RGMII1_TD0                          0X094U
#define PINP16_RGMII1_TD0_RGMII1_TD0               0X0U
#define PINP16_RGMII1_TD0_RMII1_TXD0               0X1U
#define PINP16_RGMII1_TD0_MII1_TXD0                0X2U
#define PINP16_RGMII1_TD0_FSIRX1_DATA1             0X6U
#define PINP16_RGMII1_TD0_GPIOCD_37                  0X7U
#define PINP16_RGMII1_TD0_EQEP1_A                  0X8U

/* PIN P17, RGMII1_TD1 functionality */
#define PINP17_RGMII1_TD1                          0X098U
#define PINP17_RGMII1_TD1_RGMII1_TD1               0X0U
#define PINP17_RGMII1_TD1_RMII1_TXD1               0X1U
#define PINP17_RGMII1_TD1_MII1_TXD1                0X2U
#define PINP17_RGMII1_TD1_FSIRX1_CLK               0X6U
#define PINP17_RGMII1_TD1_GPIOCD_38                  0X7U
#define PINP17_RGMII1_TD1_EQEP1_B                  0X8U

/* PIN P18, RGMII1_TD2 functionality */
#define PINP18_RGMII1_TD2                           0X9CU
#define PINP18_RGMII1_TD2_RGMII1_TD2                0X0U
#define PINP18_RGMII1_TD2_RMII1_CRS_DV              0X1U
#define PINP18_RGMII1_TD2_MII1_TXD2                 0X2U
#define PINP18_RGMII1_TD2_FSIRX1_DATA0              0X6U
#define PINP18_RGMII1_TD2_GPIOCD_39                   0X7U
#define PINP18_RGMII1_TD2_EQEP1_S                   0X8U

/* PIN N17, RGMII1_TD3 functionality */
#define PINN17_RGMII1_TD3                         0X0A0U
#define PINN17_RGMII1_TD3_RGMII1_TD3              0X0U
#define PINN17_RGMII1_TD3_MII1_TXD3               0X2U
#define PINN17_RGMII1_TD3_EQEP1_I                 0X8U
#define PINN17_RGMII1_TD3_FSIRX1_DATA1                       0X6U
#define PINN17_RGMII1_TD3_GPIOCD_40                 0X7U

/* PIN N16, MDIO0_MDIO functionality */
#define PINN16_MDIO0_MDIO                         0XA4U
#define  PINN16_MDIO0_MDIO_MDIO0_MDIO             0X0U
#define  PINN16_MDIO0_MDIO_GPIOCD_41                0X7U

/* PIN M17, MDIO0_MDC functionality */
#define PINM17_MDIO0_MDC                          0XA8U
#define PINM17_MDIO0_MDC_MDIO0_MDC                0X0U
#define PINM17_MDIO0_MDC_GPIOCD_42                  0X7U



/* PIN B2, EPWM0_A functionality */
#define PINB2_EPWM0_A                           0XACU
#define PINB2_EPWM0_A_EPWM0_A                   0X0U
#define PINB2_EPWM0_A_GPIOCD_43                   0X7U
               

/* PIN B1, EPWM0_B functionality */
#define PINB1_EPWM0_B                           0XB0U
#define PINB1_EPWM0_BEPWM0_B                    0X0U
#define PINB1_EPWM0_B_GPIOCD_44                   0X7U


/* PIN D3, EPWM1_A functionality */
#define PIND3_EPWM1_A                           0XB4U
#define PIND3_EPWM1_A_GPIOCD_45                   0X7U
#define PIND3_EPWM1_A_EPWM1_A                   0X0U


/* PIN D2, EPWM1_B functionality */
#define PIND2_EPWM1_B                           0XB8U
#define PIND2_EPWM1_B_GPIOCD_46                   0X7U
#define PIND2_EPWM1_B_EPWM1_B                   0X0U


/* PIN C2, EPWM2_A  functionality */
#define PINC2_EPWM2_A                            0XBCU
#define PINC2_EPWM2_A_GPIOCD_47                    0X7U
#define PINC2_EPWM2_A_EPWM2_A                    0X0U

/* PIN C1, EPWM2_B functionality */
#define PINC1_EPWM2_B                           0XC0U
#define PINC1_EPWM2_B_GPIOCD_48                   0X7U
#define PINC1_EPWM2_B_EPWM2_B                   0X0U
              

/* PIN E2, EPWM3_A functionality */
#define PINE2_EPWM3_A                          0XC4U
#define PINE2_EPWM3_A_GPIOCD_49                  0X07U
#define PINE2_EPWM3_A_EPWM3_A                  0X0U


/* PIN E3, PADAI functionality */
#define PINE3_EPWM3_B                          0XC8U
#define PINE3_EPWM3_B_EPWM3_B                  0X0U
#define PINE3_EPWM3_B_GPIOCD_50                  0X7U


/* PIN D1, EPWM4_A functionality */
#define PIND1_EPWM4_A                           0XCCU
#define PIND1_EPWM4_A_GPIOCD_51                   0X07U
#define PIND1_EPWM4_A_EPWM4_A                   0X00U


/* PIN E4, EPWM4_B functionality */
#define PINE4_EPWM4_B                           0XD0U
#define PINE4_EPWM4_B_GPIOCD_52                   0X07U
#define PINE4_EPWM4_B_EPWM4_B                   0X00U
#define PINE4_EPWM4_B_FSITX1_CLK                0x06U

/* PIN F2, EPWM5_A functionality */
#define PINF2_EPWM5_A                           0XD4U
#define PINF2_EPWM5_A_GPIOCD_53                   0X07U
#define PINF2_EPWM5_A_EPWM5_A                    0X0U
#define PINF2_EPWM5_A_FSITX1_DATA0               0X6U

/* PIN G2, EPWM5_B functionality */
#define PING2_EPWM5_B                           0XD8U
#define PING2_EPWM5_B_GPIOCD_54                    0X7U
#define PING2_EPWM5_B_EPWM5_B                    0X0U
#define PING2_EPWM5_B_FSITX1_DATA1              0X6U


/* PIN E1, EPWM6_A functionality */
#define PINE1_EPWM6_A                           0XDCU
#define PINE1_EPWM6_A_GPIOCD_55                   0X07U
#define PINE1_EPWM6_A_EPWM6_A                   0X0U
#define PINE1_EPWM6_A_FSIRX1_CLK                0X6U                  

/* PIN F3, PADAO functionality */
#define PINF3_EPWM6_B                           0XE0U
#define PINF3_EPWM6_B_GPIOCD_56                   0X7U
#define PINF3_EPWM6_B_EPWM6_B                   0X0U
#define PINF3_EPWM6_B_FSITX1_DATA0               0X6U                

/* PIN F4, PADAP functionality */
#define PINF4_EPWM7_A                           0XE4U
#define PINF4_EPWM7_A_GPIOCD_57                    0X07U
#define PINF4_EPWM7_A_EPWM7_A                    0X0U
#define PINF4_EPWM7_A_FSIRX1_DATA1               0X6U         


/* PIN F1, PADAQ functionality */
#define PINF1_EPWM7_B                           0XE8U
#define PINF1_EPWM7_B_GPIOCD_58                    0X7U
#define PINF1_EPWM7_B_EPWM7_B                    0X0U


/* PIN G3, EPWM8_A functionality */
#define PING3_EPWM8_A                           0XECU
#define PING3_EPWM8_A_EPWM8_A                   0X0U
#define PING3_EPWM8_A_UART4_TXD                 0X1U
#define PING3_EPWM8_A_I2C3_SDA                  0X2U
#define PING3_EPWM8_A_FSITX2_CLK                0X6U
#define PING3_EPWM8_A_GPIOCD_59                   0X7U

/* PIN H2, EPWM8_B functionality */
#define PINH2_EPWM8_B                           0XF0U
#define PINH2_EPWM8_B_EPWM8_B                   0X0U            
#define PINH2_EPWM8_B_UART4_RXD                 0X1U       
#define PINH2_EPWM8_B_I2C3_SCL                  0X2U           
#define PINH2_EPWM8_B_FSITX2_DATA0                0X6U          
#define PINH2_EPWM8_B_GPIOCD_60                   0X7U

/* PIN G1, PADAT functionality */
#define PING1_EPWM9_A                           0XF4U
#define PING1_EPWM9_A_EPWM9_A                   0X0U                  
#define PING1_EPWM9_A_FSITX2_DATA1                0X6U                    
#define PING1_EPWM9_A_GPIOCD_61                   0X7U                                   

/* PIN J2,EPWM9_B functionality */
#define PINJ2_EPWM9_B                           0XF8U
#define PINJ2_EPWM9_B_EPWM9_B               0X0U
#define PINJ2_EPWM9_B_UART1_RTSn                 0X1U
#define PINJ2_EPWM9_B_FSITX2_CLK                 0X6U
#define PINJ2_EPWM9_B_GPIOCD_62                    0X7U

/* PIN G4, EPWM10_A functionality */
#define PING4_EPWM10_A                           0XFCU
#define PING4_EPWM10_A_EPWM10_A                 0X0U
#define PING4_EPWM10_A_UART1_CTSn                 0X1U
#define PING4_EPWM10_A_FSITX2_DATA0               0X6U
#define PING4_EPWM10_A_GPIOCD_63                     0X7U

/* PIN J3, EPWM10_B functionality */
#define PINJ3_EPWM10_B                           0X100U
#define PINJ3_EPWM10_B_EPWM10_B                   0X0U
#define PINJ3_EPWM10_B_UART2_RTSn                 0X1U
#define PINJ3_EPWM10_B_FSITX2_DATA1               0X6U
#define PINJ3_EPWM10_B_GPIOEF_64                     0X7U


/* PIN H1, EPWM11_A functionality */
#define PINH1_EPWM11_A                           0X104U
#define PINH1_EPWM11_A_EPWM11_A                  0X0U
#define PINH1_EPWM11_A_UART2_CTSn                 0X1U
#define PINH1_EPWM11_A_GPMC0_CLKLB                0X6U
#define PINH1_EPWM11_A_GPIOEF_65                     0X7U


/* PIN J1, EPWM11_B functionality */
#define PINJ1_EPWM11_B                           0X108U
#define PINJ1_EPWM11_B_EPWM11_B                  0X0U
#define PINJ1_EPWM11_B_UART3_RTSn                0X1U
#define PINJ1_EPWM11_B_GPMC0_OEn_REn             0X6U
#define PINJ1_EPWM11_B_GPIOEF_66                    0X7U

/* PIN K2, EPWM12_A functionality */
#define PINK2_EPWM12_A                           0X10CU
#define PINK2_EPWM12_A_EPWM12_A                   0X0U
#define PINK2_EPWM12_A_UART3_CTSn                 0X1U
#define PINK2_EPWM12_A_SPI4_CS1                   0X2U
#define PINK2_EPWM12_A_GPMC0_WEn                  0X6U
#define PINK2_EPWM12_A_GPIOEF_67                     0X7U


/* PIN J4, EPWM12_B functionality */
#define PINJ4_EPWM12_B                           0X110U
#define PINJ4_EPWM12_B_EPWM12_B                   0X0U
#define PINJ4_EPWM12_B_URT1_DCDn                  0X1U
#define PINJ4_EPWM12_B_GPMC0_CSn0                 0X6U
#define PINJ4_EPWM12_B_GPIOEF_68                     0X7U


/* PIN K4, EPWM13_A functionality */
#define PINK4_EPWM13_A                           0X114U
#define PINK4_EPWM13_A_EPWM13_A                   0X0U
#define PINK4_EPWM13_A_UART1_RIn                  0X1U
#define PINK4_EPWM13_A_GPMC0_AD0                  0X6U
#define PINK4_EPWM13_A_GPIOEF_69                     0X7U


/* PIN K3, PADBC functionality */
#define PINK3_EPWM13_B                          0X118U
#define PINK3_EPWM13_B_EPWM13_B                  0X0U
#define PINK3_EPWM13_B_UART1_DTRn                0X1U
#define PINK3_EPWM13_B_GPMC0_AD1                 0X6U
#define PINK3_EPWM13_B_GPIOEF_70                    0X7U


/* PIN V17, EPWM14_A functionality */
#define PINV17_EPWM14_A                           0X11CU
#define PINV17_EPWM14_A_EPWM14_A                   0X0U
#define PINV17_EPWM14_A_UART1_DSRn                 0X1U
#define PINV17_EPWM14_A_GPMC0_AD2                  0X6U
#define PINV17_EPWM14_A_GPIOEF_71                     0X7U


/* PIN T16, EPWM14_B functionality */
#define PINT16_EPWM14_B                               0X120U
#define PINT16_EPWM14_B_EPWM14_B                      0X0U
#define PINT16_EPWM14_B_MII1_RX_ER                    0X2U
#define PINT16_EPWM14_B_GPMC0_AD3                     0X6U
#define PINT16_EPWM14_B_GPIOEF_72                        0X7U



/* PIN P15,EPWM15_A functionality */
#define PINP15_EPWM15_A                          0X124U
#define PINP15_EPWM15_A_EPWM15_A                 0X0U
#define PINP15_EPWM15_A_UART5_TXD                  0X1U
#define PINP15_EPWM15_A_MII1_COL                  0X2U
#define PINP15_EPWM15_A_GPMC0_AD4                 0X6U
#define PINP15_EPWM15_A_GPIOEF_73                    0X7U


/* PIN R16, PADBG functionality */
#define PINR16_EPWM15_B                          0X128U
#define PINR16_EPWM15_B_EPWM15_B                 0X0U
#define PINR16_EPWM15_B_UART5_RXD                0X1U
#define PINR16_EPWM15_B_MII1_CRS                 0X2U
#define PINR16_EPWM15_B_GPMC0_AD5                0X6U
#define PINR16_EPWM15_B_GPIOEF_74                  0X7U

/* PIN L3, UART1_RXD functionality */
#define PINL3_UART1_RXD                          0X12CU
#define PINL3_UART1_RXD_UART1_RXD                0X0U
#define PINL3_UART1_RXD_LIN1_RXD                 0X1U
#define PINL3_UART1_RXD_EPWM16_A                 0X5U
#define PINL3_UART1_RXD_GPMC0_AD6                0X6U
#define PINL3_UART1_RXD_GPIOEF_75                  0X7U

/* PIN M3, UART1_TXD functionality */
#define PINM3_UART1_TXD                          0X0130U
#define PINM3_UART1_TXD_UART1_TXD                0X0U
#define PINM3_UART1_TXD_LIN1_TXD                 0X1U
#define PINM3_UART1_TXD_EPWM16_B                 0X5U
#define PINM3_UART1_TXD_GPMC0_AD7                0X6U
#define PINM3_UART1_TXD_GPIOEF_76                  0X7U

/* PIN B6, MMC0_CLK functionality */
#define PINB6_MMC0_CLK                          0X134U
#define PINB6_MMC0_CLK_MMC0_CLK                 0X0U
#define PINB6_MMC0_CLK_UART0_RXD                0X1U
#define PINB6_MMC0_CLK_LIN0_RXD                 0X2U
#define PINB6_MMC0_CLK_EPWM17_A                 0X5U
#define PINB6_MMC0_CLK_GPMC0_AD8                0X6U
#define PINB6_MMC0_CLK_GPIOEF_77                  0X7U
#define PINB6_MMC0_CLK_SDFM1_CLK0               0X8U


/* PIN A4, MMC0_CMD functionality */
#define PINA4_MMC0_CMD                          0X138U
#define PINA4_MMC0_CMD_MMC0_CMD                 0X0U
#define PINA4_MMC0_CMD_UART0_TXD                0X1U
#define PINA4_MMC0_CMD_LIN0_TXD                  0X2U
#define PINA4_MMC0_CMD_EPWM17_B                 0X5U
#define PINA4_MMC0_CMD_GPMC0_AD9                0X6U
#define PINA4_MMC0_CMD_GPIOEF_78                  0X7U
#define PINA4_MMC0_CMD_SDFM1_D0                 0X8U


/* PIN B5, MMC0_D0 functionality */
#define PINB5_MMC0_D0                          0X13CU
#define PINB5_MMC0_D0_MMC0_D0                  0X0U
#define PINB5_MMC0_D0_UART2_RXD                0X1U
#define PINB5_MMC0_D0_I2C1_SCL                 0X2U
#define PINB5_MMC0_D0_EPWM18_A                 0X5U
#define PINB5_MMC0_D0_GPMC0_AD10               0X6U
#define PINB5_MMC0_D0_GPIOEF_79                  0X7U
#define PINB5_MMC0_D0_SDFM1_CLK1               0X8U



/* PIN B4, MMC0_D1 functionality */
#define PINB4_MMC0_D1                          0X140U
#define PINB4_MMC0_D1_MMC0_D1                  0X0U
#define PINB4_MMC0_D1_EPWM18_B                 0X5U
#define PINB4_MMC0_D1_GPMC0_AD11               0X6U
#define PINB4_MMC0_D1_GPIOEF_80                  0X7U
#define PINB4_MMC0_D1_SDFM1_D1                 0X8U

/* PIN A3, MMC0_D2 functionality */
#define PINA3_MMC0_D2                          0X144U
#define PINA3_MMC0_D2_MMC0_D2                  0X0U
#define PINA3_MMC0_D2_UART2_TXD                0X1U
#define PINA3_MMC0_D2_I2C1_SDA                 0X2U
#define PINA3_MMC0_D2_EPWM19_A                 0X5U
#define PINA3_MMC0_D2_GPMC0_AD12               0X6U
#define PINA3_MMC0_D2_GPIOEF_81                  0X7U
#define PINA3_MMC0_D2_SDFM1_CLK2               0X8U

/* PIN A2, MMC0_D3 functionality */
#define PINA2_MMC0_D3                          0X148U
#define PINA2_MMC0_D3_MMC0_D3                  0X0U
#define PINA2_MMC0_D3_UART3_RTSn               0X1U
#define PINA2_MMC0_D3_EPWM19_B                 0X5U
#define PINA2_MMC0_D3_GPMC0_AD13               0X6U
#define PINA2_MMC0_D3_GPIOEF_82                  0X7U
#define PINA2_MMC0_D3_SDFM1_D2                 0X8U

/* PIN C6, MMC0_WP functionality */
#define PINC6_MMC0_WP                          0X14CU
#define PINC6_MMC0_WP_MMC0_WP                  0X0U
#define PINC6_MMC0_WP_UART0_RTSn               0X1U
#define PINC6_MMC0_WP_I2C2_SCL                 0X2U
#define PINC6_MMC0_WP_EPWM20_A                 0X5U
#define PINC6_MMC0_WP_GPMC0_AD14               0X6U
#define PINC6_MMC0_WP_GPIOEF_83                  0X7U
#define PINC6_MMC0_WP_SDFM1_CLK3               0X8U

/* PIN A5, MMC0_CD functionality */
#define PINA5_MMC0_CD                          0X150U
#define PINA5_MMC0_CD_MMC0_CD                  0X0U
#define PINA5_MMC0_CD_UART0_CTSn               0X1U
#define PINA5_MMC0_CD_I2C2_SDA                 0X2U
#define PINA5_MMC0_CD_EPWM20_B                 0X5U
#define PINA5_MMC0_CD_GPMC0_AD15               0X6U
#define PINA5_MMC0_CD_GPIOEF_84                  0X7U
#define PINA5_MMC0_CD_SDFM1_D3                 0X8U


/* PIN L17, PR0_MDIO0_MDIO functionality */
#define PINL17_PR0_MDIO0_MDIO                          0X154U
#define PINL17_PR0_MDIO0_MDIO_PR0_MDIO0_MDIO           0X0U
#define PINL17_PR0_MDIO0_MDIO_EPWM21_A                 0X5U
#define PINL17_PR0_MDIO0_MDIO_GPMC0_CSn2               0X6U
#define PINL17_PR0_MDIO0_MDIO_GPIOEF_85                  0X7U


/* PIN L18, PR0_MDIO0_MDC functionality */
#define PINL18_PR0_MDIO0_MDC                          0X158U
#define PINL18_PR0_MDIO0_MDC_PR0_MDIO0_MDC            0X0U
#define PINL18_PR0_MDIO0_MDC_EPWM21_B                 0X5U
#define PINL18_PR0_MDIO0_MDC_GPMC0_CSn3               0X6U
#define PINL18_PR0_MDIO0_MDC_GPIOEF_86                  0X7U

/* PIN G17, PADCR functionality */
#define PING17_PRU0_GIO5                          0X15CU
#define PING17_PRU0_GIO5_PRU0_GIO5                0X0U
#define PING17_PRU0_GIO5_RMII2_RX_ER              0X2U
#define PING17_PRU0_GIO5_MII2_RX_ER               0X4U
#define PING17_PRU0_GIO5_EPWM22_A                 0X5U
#define PING17_PRU0_GIO5_GPMC0_DIR                0X6U
#define PING17_PRU0_GIO5_GPIOEF_87                  0X7U

/* PIN F17, PADCU functionality */
#define PINF17_PRU0_GIO9                          0X160U
#define PINF17_PRU0_GIO9_PRU0_GIO9                0X0U
#define PINF17_PRU0_GIO9_PR0_UART0_CTSn           0X3U
#define PINF17_PRU0_GIO9_MII2_COL                 0X4U
#define PINF17_PRU0_GIO9_EPWM22_B                 0X5U
#define PINF17_PRU0_GIO9_GPMC0_CLK                0X6U
#define PINF17_PRU0_GIO9_GPIOEF_88                  0X7U

/* PIN G18, PADCV functionality */
#define PING18_PRU0_GIO10                          0X164U
#define PING18_PRU0_GIO10_PRU0_GIO10               0X0U
#define PING18_PRU0_GIO10_RMII2_CRS_DV             0X2U
#define PING18_PRU0_GIO10_PR0_UART0_RTSn           0X3U
#define PING18_PRU0_GIO10_MII2_CRS                 0X4U
#define PING18_PRU0_GIO10_EPWM23_A                 0X5U
#define PING18_PRU0_GIO10_GPMC0_WAIT0              0X6U
#define PING18_PRU0_GIO10_GPIOEF_89                  0X7U



/* PIN G15, PADCT functionality */
#define PING15_PRU0_GIO8                          0X168U
#define PING15_PRU0_GIO8_PRU0_GIO8                0X0U
#define PING15_PRU0_GIO8_EPWM23_B                 0X5U
#define PING15_PRU0_GIO8_GPMC0_WPn                0X6U
#define PING15_PRU0_GIO8_GPIOEF_90                  0X7U

/* PIN K15, PADCS functionality */
#define PINK15_PRU0_GIO6                          0X16CU
#define PINK15_PRU0_GIO6_PRU0_GIO6                0X0U
#define PINK15_PRU0_GIO6_RMII2_REF_CLK            0X2U
#define PINK15_PRU0_GIO6_RGMII2_RXC               0X3U
#define PINK15_PRU0_GIO6_MII2_RXCLK               0X4U
#define PINK15_PRU0_GIO6_EPWM24_A                 0x5U
#define PINK15_PRU0_GIO6_GPMC0_CSn1               0X6U
#define PINK15_PRU0_GIO6_GPIOEF_91                  0X7U

/* PIN K16, PADCQ functionality */
#define PINK16_PRU0_GIO4                          0X170U
#define PINK16_PRU0_GIO4_PRU0_GIO4                0X0U
#define PINK16_PRU0_GIO4_RGMII2_RX_CTL       0X3U
#define PINK16_PRU0_GIO4_MII2_RXDV                0X4U
#define PINK16_PRU0_GIO4_EPWM24_B                 0x5U
#define PINK16_PRU0_GIO4_GPMC0_A0                 0X6U
#define PINK16_PRU0_GIO4_GPIOEF_92                  0X7U

/* PIN K17, PADCM functionality */
#define PINK17_PRU0_GIO0                          0X174U
#define PINK17_PRU0_GIO0_PRU0_GIO0                0X0U
#define PINK17_PRU0_GIO0_RMII2_RXD0               0X2U
#define PINK17_PRU0_GIO0_RGMII2_RD0               0X3U
#define PINK17_PRU0_GIO0_MII2_RXD0                0X4U
#define PINK17_PRU0_GIO0_EPWM25_A                 0x5U
#define PINK17_PRU0_GIO0_GPMC0_A1                 0X6U
#define PINK17_PRU0_GIO0_GPIOEF_93                   0X7U

/* PIN K18, PADCN functionality */
#define PINK18_PRU0_GIO1                          0X178U
#define PINK18_PRU0_GIO1_PRU0_GIO1                0X0U
#define PINK18_PRU0_GIO1_RMII2_RXD1               0X2U
#define PINK18_PRU0_GIO1_RGMII2_RD1          0X3U
#define PINK18_PRU0_GIO1_MII2_RXD1           0X4U
#define PINK18_PRU0_GIO1_EPWM25_B                 0x5U
#define PINK18_PRU0_GIO1_GPMC0_A2            0X6U
#define PINK18_PRU0_GIO1_GPIOEF_94             0X7U

/* PIN J18, PADCO functionality */
#define PINJ18_PRU0_GIO2                          0X17CU
#define PINJ18_PRU0_GIO2_PRU0_GIO2                0X0U
#define PINJ18_PRU0_GIO2_RGMII2_RD2               0X3U
#define PINJ18_PRU0_GIO2_MII2_RXD2                0X4U
#define PINJ18_PRU0_GIO2_EPWM26_A                 0x5U
#define PINJ18_PRU0_GIO2_GPMC0_A3                 0X6U
#define PINJ18_PRU0_GIO2_GPIOEF_95                  0X7U

/* PIN J17, PADCP functionality */
#define PINJ17_PRU0_GIO3                          0X180U
#define PINJ17_PRU0_GIO3_PRU0_GIO3                0X0U
#define PINJ17_PRU0_GIO3_RGMII2_RD3               0X3U
#define PINJ17_PRU0_GIO3_MII2_RXD3                0X4U
#define PINJ17_PRU0_GIO3_EPWM26_B                 0x5U
#define PINJ17_PRU0_GIO3_GPMC0_A4                 0X6U
#define PINJ17_PRU0_GIO3_GPIOGH_96                  0X7U

/* PIN H18, PADDB functionality */
#define PINH18_PRU0_GIO16                           0X184U
#define PINH18_PRU0_GIO16_PRU0_GIO16                0X0U
#define PINH18_PRU0_GIO16_RGMII2_TXC                0X3U
#define PINH18_PRU0_GIO16_MII2_TXCLK                0X4U
#define PINH18_PRU0_GIO16_EPWM27_A                  0x5U
#define PINH18_PRU0_GIO16_GPMC0_A5                  0X6U
#define PINH18_PRU0_GIO16_GPIOGH_97                   0X7U

/* PIN L16, PADDA functionality */
#define PINL16_PRU0_GIO15                           0X188U
#define PINL16_PRU0_GIO15_PRU0_GIO15                0X0U
#define PINL16_PRU0_GIO15_RMII2_TX_EN               0X2U
#define PINL16_PRU0_GIO15_RGMII2_TX_CTL             0X3U
#define PINL16_PRU0_GIO15_MII2_TX_EN                0X4U
#define PINL16_PRU0_GIO15_EPWM27_B                  0x5U
#define PINL16_PRU0_GIO15_GPMC0_A6                  0X6U
#define PINL16_PRU0_GIO15_GPIOGH_98                   0X7U



/* PIN M16, PRU0_GIO11 functionality */
#define PINM16_PRU0_GIO11                          0X18CU
#define PINM16_PRU0_GIO11_PRU0_GIO11               0X0U
#define PINM16_PRU0_GIO11_RMII2_TXD0               0X2U
#define PINM16_PRU0_GIO11_RGMII2_TD0               0X3U
#define PINM16_PRU0_GIO11_MII2_TXD0                0X4U
#define PINM16_PRU0_GIO11_EPWM28_A                 0x5U
#define PINM16_PRU0_GIO11_GPMC0_A7                 0X6U
#define PINM16_PRU0_GIO11_GPIOGH_99                  0X7U

/* PIN M15, PADCX functionality */
#define PINM15_PRU0_GIO12                          0X190U
#define PINM15_PRU0_GIO12_PRU0_GIO12                0X0U
#define PINM15_PRU0_GIO12_RMII2_TXD1               0X2U
#define PINM15_PRU0_GIO12_RGMII2_TD1               0X3U
#define PINM15_PRU0_GIO12_MII2_TXD1                0X4U
#define PINM15_PRU0_GIO12_EPWM28_B                 0x5U
#define PINM15_PRU0_GIO12_GPMC0_A8                 0X6U                  
#define PINM15_PRU0_GIO12_GPIOGH_100                 0X7U

/* PIN H17, PADCY functionality */
#define PINH17_PRU0_GIO13                          0X194U
#define PINH17_PRU0_GIO13_PRU0_GIO13               0X0U
#define PINH17_PRU0_GIO13_RGMII2_TD2               0X3U
#define PINH17_PRU0_GIO13_MII2_TXD2                0X4U
#define PINH17_PRU0_GIO13_EPWM29_A                 0x5U
#define PINH17_PRU0_GIO13_GPMC0_A9                 0X6U
#define PINH17_PRU0_GIO13_GPIOGH_101                 0X7U

/* PIN H16, PADCZ functionality */
#define PINH16_PRU0_GIO14                          0X198U
#define PINH16_PRU0_GIO14_PRU0_GIO14               0X0U
#define PINH16_PRU0_GIO14_RGMII2_TD3               0X3U
#define PINH16_PRU0_GIO14_MII2_TXD3                0X4U
#define PINH16_PRU0_GIO14_EPWM29_B                 0x5U
#define PINH16_PRU0_GIO14_GPMC0_A10                0X6U
#define PINH16_PRU0_GIO14_GPIOGH_102                 0X7U




/* PIN F15, PADDH functionality */
#define PINF15_PRU1_GIO5                          0X19CU
#define PINF15_PRU1_GIO5_PRU1_GIO5                0X0U
#define PINF15_PRU1_GIO5_TRC_DATA0                0X4U
#define PINF15_PRU1_GIO5_EPWM30_A                 0x5U
#define PINF15_PRU1_GIO5_GPMC0_OEn_REn            0X6U
#define PINF15_PRU1_GIO5_GPIOGH_103                 0X7U

/* PIN C18, PADDK functionality */
#define PINC18_PRU1_GIO9                          0X1A0U
#define PINC18_PRU1_GIO9_PRU1_GIO9                0X0U
#define PINC18_PRU1_GIO9_PR0_UART0_RXD            0X3U
#define PINC18_PRU1_GIO9_TRC_DATA1                0X4U
#define PINC18_PRU1_GIO9_EPWM30_B                 0x5U
#define PINC18_PRU1_GIO9_GPMC0_BE0n_CLE           0X6U
#define PINC18_PRU1_GIO9_GPIOGH_104                 0X7U

/* PIN D17, PADDL functionality */
#define PIND17_PRU1_GIO10                          0X1A4U
#define PIND17_PRU1_GIO10_PRU1_GIO10               0X0U
#define PIND17_PRU1_GIO10_PR0_UART0_TXD            0X3U
#define PIND17_PRU1_GIO10_TRC_DATA2                0X4U
#define PIND17_PRU1_GIO10_EPWM31_A                 0x5U
#define PIND17_PRU1_GIO10_GPMC0_BE1n               0X6U
#define PIND17_PRU1_GIO10_GPIOGH_105                 0X7U

/* PIN D18, PADDJ functionality */
#define PIND18_PRU1_GIO8                          0X1A8U
#define PIND18_PRU1_GIO8_PRU1_GIO8                0X0U
#define PIND18_PRU1_GIO8_TRC_DATA3                0X4U
#define PIND18_PRU1_GIO8_EPWM31_B                 0x5U
#define PIND18_PRU1_GIO8_GPMC0_WEn                0X6U
#define PIND18_PRU1_GIO8_GPIOGH_106                 0X7U


/* PIN E16, PADDI functionality */
#define PINE16_PRU1_GIO6                          0X1ACU
#define PINE16_PRU1_GIO6_PRU1_GIO6                0X0U
#define PINE16_PRU1_GIO6_FSITX2_CLK               0X3U
#define PINE16_PRU1_GIO6_TRC_DATA4                0X4U
#define PINE16_PRU1_GIO6_GPMC0_A11                0X6U
#define PINE16_PRU1_GIO6_GPIOGH_107                 0X7U

/* PIN F16, PADDG functionality */
#define PINF16_PRU1_GIO4                           0X1B0U
#define PINF16_PRU1_GIO4_PRU1_GIO4                 0X0U
#define PINF16_PRU1_GIO4_FSITX2_DATA0              0X3U
#define PINF16_PRU1_GIO4_TRC_DATA5                 0X4U
#define PINF16_PRU1_GIO4_GPMC0_A12                 0X6U
#define PINF16_PRU1_GIO4_GPIOGH_108                  0X7U



/* PIN F18, PADDC functionality */
#define PINF18_PRU1_GIO0                          0X1B4U
#define PINF18_PRU1_GIO0_PRU1_GIO0                0X0U
#define PINF18_PRU1_GIO0_FSITX2_DATA1             0X3U
#define PINF18_PRU1_GIO0_TRC_DATA6                0X4U
#define PINF18_PRU1_GIO0_GPMC0_A13                0X6U
#define PINF18_PRU1_GIO0_GPIOGH_109                 0X7U

/* PIN G16, PADDD functionality */
#define PING16_PRU1_GIO1                          0X1B8U
#define PING16_PRU1_GIO1_PRU1_GIO1                0X0U
#define PING16_PRU1_GIO1_FSIRX2_CLK               0X3U
#define PING16_PRU1_GIO1_TRC_DATA7                0X4U
#define PING16_PRU1_GIO1_GPMC0_A14                0X6U
#define PING16_PRU1_GIO1_GPIOGH_110                 0X7U


/* PIN E17, PADDE functionality */
#define PINE17_PRU1_GIO2                           0X1BCU
#define PINE17_PRU1_GIO2_PRU1_GIO2                 0X0U
#define PINE17_PRU1_GIO2_FSIRX2_DATA0              0X3U
#define PINE17_PRU1_GIO2_TRC_DATA8                 0X4U
#define PINE17_PRU1_GIO2_GPMC0_A15                 0X6U
#define PINE17_PRU1_GIO2_GPIOGH_111                  0X7U

/* PIN E18, PADDF functionality */
#define PINE18_PRU1_GIO3                           0X1C0U
#define PINE18_PRU1_GIO3_PRU1_GIO3                 0X0U
#define PINE18_PRU1_GIO3_FSIRX2_DATA1              0X3U
#define PINE18_PRU1_GIO3_TRC_DATA9                 0X4U
#define PINE18_PRU1_GIO3_GPMC0_A16                 0X6U
#define PINE18_PRU1_GIO3_GPIOGH_112                  0X7U


/* PIN C16, PADDR functionality */
#define PINC16_PRU1_GIO16                          0X1C4U
#define PINC16_PRU1_GIO16_PRU1_GIO16               0X0U
#define PINC16_PRU1_GIO16_FSITX3_CLK               0X3U
#define PINC16_PRU1_GIO16_TRC_DATA10               0X4U
#define PINC16_PRU1_GIO16_GPMC0_A17                0X6U
#define PINC16_PRU1_GIO16_GPIOGH_113                 0X7U


/* PIN A17, PADDQ functionality */
#define PINA17_PRU1_GIO15                          0X1C8U
#define PINA17_PRU1_GIO15_PRU1_GIO15               0X0U
#define PINA17_PRU1_GIO15_FSITX3_DATA0             0X3U
#define PINA17_PRU1_GIO15_TRC_DATA11               0X4U
#define PINA17_PRU1_GIO15_GPMC0_A18                0X6U
#define PINA17_PRU1_GIO15_GPIOGH_114                 0X7U


/* PIN B18, PADDM functionality */
#define PINB18_PRU1_GIO11                           0X1CCU
#define PINB18_PRU1_GIO11_PRU1_GIO11                0X0U
#define PINB18_PRU1_GIO11_FSITX3_DATA1              0X3U
#define PINB18_PRU1_GIO11_TRC_DATA12                0X4U
#define PINB18_PRU1_GIO11_GPMC0_A19                 0X6U
#define PIND16_PADDM_GPIOGH_115                       0X7U




/* PIN B17, PADDN functionality */
#define PINB17_PRU1_GIO12                          0X1D0U
#define PINB17_PRU1_GIO12_PRU1_GIO12               0X0U
#define PINB17_PRU1_GIO12_FSIRX3_CLK               0X3U
#define PINB17_PRU1_GIO12_TRC_DATA13               0X4U
#define PINB17_PRU1_GIO12_GPMC0_A20                0X6U
#define PINB17_PRU1_GIO12_GPIOGH_116                 0X7U

/* PIN D16, PADDO functionality */
#define PIND16_PRU1_GIO13                          0X1D4U
#define PIND16_PRU1_GIO13_PRU1_GIO13               0X0U
#define PIND16_PRU1_GIO13_FSIRX3_DATA0             0X3U
#define PIND16_PRU1_GIO13_TRC_DATA14               0X4U
#define PIND16_PRU1_GIO13_XBAROUT11                0X5U
#define PIND16_PRU1_GIO13_GPMC0_A21                0X6U
#define PIND16_PRU1_GIO13_GPIOGH_117                 0X7U

/* PIN C17, PADDP functionality */
#define PINC17_PRU1_GIO14                          0X1D8U
#define PINC17_PRU1_GIO14_PRU1_GIO14               0X0U
#define PINC17_PRU1_GIO14_FSIRX3_DATA1             0X3U
#define PINC17_PRU1_GIO14_TRC_DATA15               0X4U
#define PINC17_PRU1_GIO14_XBAROUT12                0X5U
#define PINC17_PRU1_GIO14_GPMC0_CSn0               0X6U
#define PINC17_PRU1_GIO14_GPIOGH_118                 0X7U

/* PIN D15, PADDT functionality */
#define PIND15_PRU1_GIO19                          0X1DCU
#define PIND15_PRU1_GIO19_PRU1_GIO19               0X0U
#define PIND15_PRU1_GIO19_RCSS_UART3_RXD           0X2U
#define PIND15_PRU1_GIO19_PR0_IEP0_EDC_SYNC_OUT0   0X3U
#define PIND15_PRU1_GIO19_TRC_CLK                  0X4U
#define PIND15_PRU1_GIO19_XBAROUT13                0X5U
#define PIND15_PRU1_GIO19_GPIOGH_119                 0X7U
#define PIND15_PRU1_GIO19_EQEP1_A                  0X9U



/* PIN C15, PADDS functionality */
#define PINC15_PRU1_GIO18                                  0X1E0U
#define PINC15_PRU1_GIO18_PRU1_GIO18                       0X0U
#define PINC15_PRU1_GIO18_UART3_TXD                        0X2U
#define PINC15_PRU1_GIO18_PR0_IEP0_EDIO_DATA_IN_OUT31      0X3U
#define PINC15_PRU1_GIO18_TRC_CTL                          0X4U
#define PINC15_PRU1_GIO18_XBAROUT14                        0X5U
#define PINC15_PRU1_GIO18_GPMC0_WAIT1                      0X6U
#define PINC15_PRU1_GIO18_GPIOGH_120                         0X7U
#define PINC15_PRU1_GIO18_EQEP1_B                          0X9U


/* PIN P2, PADBL functionality */
#define PINP2_EXT_REFCLK0                         0X1E4U
#define PINP2_EXT_REFCLK0_EXT_REFCLK0              0X0U
#define PINP2_EXT_REFCLK0_XBAROUT15                0X5U
#define PINP2_EXT_REFCLK0_GPIOGH_121                 0X7U
#define PINP2_EXT_REFCLK0_EQEP1_I                   0X9U


/* PIN B16, PADEP functionality */
#define PINB16_SDFM0_CLK0                          0X01E8U
#define PINB16_SDFM0_CLK0_CLKOUT1                   0X0U
#define PINB16_SDFM0_CLK0_GPIOGH_122                  0X7U
#define PINB16_SDFM0_CLK0_SDFM0_CLK0                0X8U
#define PINB16_SDFM0_CLK0_EQEP1_S                   0X9U

/* PIN D14, PADET functionality */
#define PIND14_SDFM0_D0                           0X1ECU
#define PIND14_SDFM0_D0_ECAP0_APWM_OUT               0X0U
#define PIND14_SDFM0_D0_GPIOGH_123                   0X7U
#define PIND14_SDFM0_D0_SDFM0_D0                   0X8U



/* PIN A16, PADEQ functionality */
#define PINA16_SDFM0_CLK1                          0X01F0U
#define PINA16_SDFM0_CLK1_PRU1_GIO7                0X0U
#define PINA16_SDFM0_CLK1_CPTS0_TS_SYNC            0X1U
#define PINA16_SDFM0_CLK1_UART5_RTSn               0X2U
#define PINA16_SDFM0_CLK1_PR0_IEP0_EDC_SYNC_OUT1   0X3U
#define PINA16_SDFM0_CLK1_GPIOGH_124                 0X7U
#define PINA16_SDFM0_CLK1_I2C3_SDA                 0X5U
#define PINA16_SDFM0_CLK1_SDFM0_CLK1               0X8U

/* PIN D13, PADEU functionality */
#define PIND13_SDFM0_D1                             0X1F4U
#define PIND13_SDFM0_D1_PRU1_GIO17                  0X0U
#define PIND13_SDFM0_D1_UART5_CTSn                  0X2U
#define PIND13_SDFM0_D1_PR0_IEP0_EDIO_DATA_IN_OUT30 0X3U
#define PIND13_SDFM0_D1_GPIOGH_125                    0X7U
#define PIND13_SDFM0_D1_SDFM0_D1        

/* PIN B15, PADER functionality */
#define PINB15_SDFM0_CLK2                          0X1F8U
#define PINB15_SDFM0_CLK2_UART5_TXD                0X0U
#define PINB15_SDFM0_CLK2_I2C3_SCL                 0X5U
#define PINB15_SDFM0_CLK2_SDFM0_CLK2               0X8U
#define PINB15_SDFM0_CLK2_GPMC0_ADVn_ALE           0X6U
#define PINB15_SDFM0_CLK2_GPIOGH_126                 0X7U

/* PIN C13, PADEV functionality */
#define PINC13_SDFM0_D2                            0X01FCU
#define PINC13_SDFM0_D2_UART5_RXD                  0X0U
#define PINC13_SDFM0_D2_GPIOGH_127                   0X7U
#define PINC13_SDFM0_D2_SDFM0_D2                   0X8U

/* PIN A15, PADES functionality */
#define PINA15_SDFM0_CLK3                          0X200U
#define PINA15_SDFM0_CLK3_MCAN3_TX                 0X0U
#define PINA15_SDFM0_CLK3_UART5_RXD                0X1U
#define PINA15_SDFM0_CLK3_GPIOI_128                 0X7U
#define PINA15_SDFM0_CLK3_SDFM0_CLK3               0X8U

/* PIN C14, PADEW functionality */
#define PINC14_SDFM0_D3                          0X0204U
#define PINC14_SDFM0_D3_MCAN3_RX                 0X0U
#define PINC14_SDFM0_D3_GPIOI_129                 0X7U
#define PINC14_SDFM0_D3_SDFM0_D3                 0X8U

/* PIN B14, PADBH functionality */
#define PINB14_EQEP0_A                           0X208U
#define PINN14_EQEP0_A _UART4_RTSn               0X0U
#define PINB14_EQEP0_A_SPI4_CLK                  0X3U
#define PINB14_EQEP0_A_GPIOI_130                  0X7U
#define PINB14_EQEP0_A_EQEP0_A                   0X8U
#define PINB14_EQEP0_A_SDFM1_CLK0                0X9U


/* PIN A14, PADBI functionality */
#define PINA14_EQEP0_B                           0X20CU
#define PINA14_EQEP0_B_UART4_CTSn                0X0U
#define PINA14_EQEP0_B_SPI4_CS0                  0X3U
#define PINA14_EQEP0_B_GPIOI_131                  0X7U
#define PINA14_EQEP0_B_EQEP0_B                   0X8U
#define PINA14_EQEP0_B_SDFM1_D0                  0X9U

/* PIN C12, PADBK functionality */
#define PINC12_EQEP0_S                          0X210U
#define PINC12_EQEP0_S_UART4_TXD                0X0U
#define PINC12_EQEP0_S_LIN4_TXD                 0X1U
#define PINC12_EQEP0_S_SPI4_D0            0X3U
#define PINC12_EQEP0_S_GPIOI_132                 0X7U
#define PINC12_EQEP0_S_EQEP0_S                  0X8U
#define PINC12_EQEP0_S_SDFM1_CLK1               0X9U


/* PIN D11, PADBJ functionality */
#define PIND11_EQEP0_I                          0X214U
#define PIND11_EQEP0_I_UART4_RXD                0X0U
#define PIND11_EQEP0_I_LIN4_RXD                 0X1U
#define PIND11_EQEP0_I_SPI4_D1                  0X3U
#define PIND11_EQEP0_I_GPIOI_133                 0X7U
#define PIND11_EQEP0_I_EQEP0_I                  0X8U
#define PIND11_EQEP0_I_SDFM1_D1                 0X9U


/* PIN B13, PADBN functionality */
#define PINB13_I2C0_SDA                          0X218U
#define PINB13_I2C0_SDA_I2C0_SDA                 0X0U
#define PINB13_I2C0_SDA_GPIOI_134                 0X7U
#define PINB13_I2C0_SDA_EQEP2_A                  0X8U
#define PINB13_I2C0_SDA_SDFM1_CLK2               0X9U


/* PIN A13 PADBM functionality */
#define PINA13_I2C0_SCL                          0X21CU
#define PINA13_I2C0_SCL_I2C0_SCL                 0X0U
#define PINA13_I2C0_SCL_GPIOI_135                  0X7U
#define PINA13_I2C0_SCL_EQEP2_B                  0X8U
#define PINA13_I2C0_SCL_SDFM1_CLK3                0X9U


/* PIN B12, PADBZ functionality */
#define PINB12_MCAN2_TX                          0X220U
#define PINB12_MCAN2_TX_MCAN2_TX                 0X0U
#define PINB12_MCAN2_TX_UART1_RTSn               0X1U
#define PINB12_MCAN2_TX_GPIOI_136                 0X7U
#define PINB12_MCAN2_TX_EQEP2_S                  0X8U
#define PINB12_MCAN2_TX_SDFM1_D2                 0X9U

/* PIN A12, PADBY functionality */
#define PINA12_MCAN2_RX                          0X224U
#define PINA12_MCAN2_RX_MCAN2_RX                 0X0U
#define PINA12_MCAN2_RX_UART2_RTSn               0X1U
#define PINA12_MCAN2_RX_GPIOI_137                  0X7U
#define PINA12_MCAN2_RX_EQEP2_I                  0X8U
#define PINA12_MCAN2_RX_SDFM1_D3                 0X9U

/* PIN M2, CLKOUT0 functionality */
#define PINM2_CLKOUT0                        0X0228U
#define PINM2_CLKOUT0_CLKOUT0                   0X0U
#define PINM2_CLKOUT0_GPIOI_138                  0X7U

/* PIN C3, PADFP functionality */
#define PINC3_WARMRSTN                          0X022CU
#define PINC3_WARMRSTN_WARMRSTn                 0X0U
            
/* PIN D4, PADEO functionality */
#define PIND4_SAFETY_ERRORN                        0X230U
#define PIND4_SAFETY_ERRORN_SAFETY_ERRORn           0X0U


/* PIN C5, PADFG functionality */
#define PINC5_PADTDI                             0X234U
#define PINC5_PADTDI_TDI                          0X0U


/* PIN C4, PADFE functionality */
#define PINC4_PADTDO                             0X238U
#define PINC4_PADTDO_TDO                           0X0U


/* PIN B3, PADFF functionality */
#define PINB3_PADTCK                              0X0240CU
#define PINB3_PADTCK_TCK                             0X0U


/* PIN D5, PADFI functionality */
#define PIND5_PIND5_TMS                             0X23CU
#define PIND5_PIND5_TMS_TMS                          0X0U


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

/* WARM_RST_CAUSE_CLR */

#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_MASK               (0x00000007U)
#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_SHIFT              (0x00000000U)
#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_RESETVAL           (0x00000000U)
#define TOP_RCM_WARM_RST_CAUSE_CLR_CLEAR_MAX                (0x00000007U)

#define TOP_RCM_WARM_RST_CAUSE_CLR_RESETVAL                 (0x00000000U)

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


