/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2021 Texas Instruments Incorporated
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

