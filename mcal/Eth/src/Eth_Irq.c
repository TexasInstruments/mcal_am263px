/*
 * TEXAS INSTRUMENTS TEXT FILE LICENSE
 *
 * Copyright (c) 2023-2025 Texas Instruments Incorporated
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

/**
 *  \file     Eth_Irq.c
 *
 *  \brief    This file contains the ISR implementation of ETH MCAL driver
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Eth.h"
#include "Eth_Cfg.h"
#include "EthIf_Cbk.h"
#include "Eth_Irq.h"

#if (ETH_ENABLE_MII_API == STD_ON)
#include "EthTrcv.h"
#endif
#if (STD_ON == ETH_DEV_ERROR_DETECT)
#include "Det.h"
#endif
#include "Dem.h"
#include "SchM_Eth.h"
#include "Eth_Priv.h"
#include "Cpsw_Priv.h"
#include "Cpsw_Stats.h"
#include "Cpsw_Cpts.h"
#include "Cpsw.h"
#include "Cpsw_Mdio.h"
#include "Cpsw_Cpdma.h"
#include "Hw_Cpsw_Ss.h"
#include "Hw_Cpsw_Mdio.h"
#include "Cpsw_Hw.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if (ETH_ENABLE_MII_API == STD_ON)
#if (STD_ON == ETH_USR_MDIO_INTERRUPT)
static void Eth_miiIndication(uint32 regVal, uint16 dataVal);
#endif
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal Function Definitions                             */
/* ========================================================================== */

#define ETH_START_SEC_ISR_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"

#if (ETH_ENABLE_MII_API == STD_ON)
#if (STD_ON == ETH_USR_MDIO_INTERRUPT)
static void Eth_miiIndication(uint32 regVal, uint16 dataVal)
{
    uint32 command = 0U;
    uint8  regIdx = 0U, phyAddr = 0U;

    command = MDIO_GET_FIELD(regVal, USER_GROUP_USER_ACCESS, WRITE);
    regIdx  = (uint8)MDIO_GET_FIELD(regVal, USER_GROUP_USER_ACCESS, REGADR);
    phyAddr = (uint8)MDIO_GET_FIELD(regVal, USER_GROUP_USER_ACCESS, PHYADR);

    if (MDIO_USER_GROUP_USER_ACCESS_REG_WRITE == command)
    {
        EthTrcv_WriteMiiIndication(Eth_DrvObj.ctrlIdx, phyAddr, regIdx);
    }
    else
    {
        EthTrcv_ReadMiiIndication(Eth_DrvObj.ctrlIdx, phyAddr, regIdx, dataVal);
    }
}
#endif
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if (ETH_ENABLE_RX_INTERRUPT == STD_ON)
/**
 *  \brief      This is the ISR function for receive interrupt of ETH
 *              controller 0.
 *              The function shall clear the interrupt and read the frames of
 *              all filled receive buffers.
 *              The function passes each received frame to the Ethernet
 *              interface using the callback
 *              function EthIf_RxIndication.
 *
 *  \param[in]  void
 *
 *  \context    ISR
 */
/* Design :  */

/*
 * Requirements : SWS_Eth_00109, SWS_Eth_00110, SWS_Eth_00111, SWS_Eth_00112,
 *                SWS_Eth_00113
 */
MCAL_INTERRUPT_ATTRIBUTE
#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
FUNC(void, ETH_CODE_ISR) Eth_RxIrqHdlr_0(void)
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_RxIrqHdlr_0)
#endif
{
    uint32 rxIntFlags = 0U;
    uint32 channelNum = 0U, channelMask = 0U;
#if (STD_ON == ETH_DEV_ERROR_DETECT)
    uint32 cp = 0U;
#endif /* #if (STD_ON == ETH_DEV_ERROR_DETECT) */

    /* Read the Rx interrupt cause from WR_C0_RX_STAT */
    rxIntFlags = Cpsw_getChIntrStatus(Eth_DrvObj.baseAddr, CPSW_CH_INTR_RX);
#if (STD_ON == ETH_DEV_ERROR_DETECT)
    if (ETH_STATE_INIT != Eth_DrvStatus)
    {
        /*
         * If a crash occurs while interrupts were pending and the core is
         * restored (no system wide reset) we can end up here since the CPSW
         * ISRs are hooked before the driver has a chance to reset the HW.
         */
        for (channelNum = 0U; channelNum < ETH_PRIORITY_QUEUE_NUM; channelNum++)
        {
            /* Clear interrupts for this channel */
            cp = CpswCpdma_readRxChCp(Eth_DrvObj.baseAddr, channelNum);
            CpswCpdma_writeRxChCp(Eth_DrvObj.baseAddr, channelNum, cp);
        }

        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RX_IRQ_HDLR, ETH_E_UNINIT);
    }
    else
#endif
    {
        /* Look for receive interrupts from across all CPDMA Rx Channels */
        while ((uint32)0U != rxIntFlags)
        {
            channelMask = (uint32)0x1U << channelNum;

            if ((uint32)0U != (uint32)(rxIntFlags & channelMask))
            {
                Eth_processRxBuffDesc(Eth_DrvObj.ctrlIdx, channelNum);
            }

            /* Clear the channel flag for the channel just handled */
            rxIntFlags &= ~channelMask;
            channelNum++;
        }
    }

    /* Write the EOI register */
    CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_RX);
}
#endif

#if (ETH_ENABLE_TX_INTERRUPT == STD_ON)
static void Eth_processTxIrqFlag(uint32 irqFlags)
{
    uint32 channelNum = 0U, channelMask = 0U;
    uint32 cp         = 0U;
    uint32 txIntFlags = irqFlags;

    /* Look for transmit interrupts from across all CPDMA Tx Channels */
    while ((uint32)0U != txIntFlags)
    {
        channelMask = (uint32)0x1U << channelNum;

        if ((uint32)0U != (uint32)(txIntFlags & channelMask))
        {
            cp = CpswCpdma_readTxChCp(Eth_DrvObj.baseAddr, channelNum);
            if (CPSW_CPDMA_TEAR_DWN_ACK != cp)
            {
                Eth_processTxBuffDesc(Eth_DrvObj.ctrlIdx, channelNum);
            }
            else
            {
                Eth_processTxTearDown(channelNum);
            }
        }

        /* Clear the channel flag for the channel just handled */
        txIntFlags &= ~channelMask;
        channelNum++;
    }
}

/**
 *  \brief      This is the ISR function for for transmit interrupt of ETH
 *              controller 0.
 *              This function shall clear the interrupt and check all filled
 *              transmit buffers for
 *              successful transmission. The function issues transmit
 *              confirmation for each
 *              transmitted frame using the callback function
 *              EthIf_TxConfirmation if requested by
 *              the previous call of Eth_Transmit service.
 *
 *  \param[in]  void
 *
 *  \context    ISR
 */
/* Design : */

/*
 * Requirements : SWS_Eth_00114, SWS_Eth_00115, SWS_Eth_00116, SWS_Eth_00117,
 *                SWS_Eth_00118
 */
MCAL_INTERRUPT_ATTRIBUTE
#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
FUNC(void, ETH_CODE_ISR) Eth_TxIrqHdlr_0(void)
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_TxIrqHdlr_0)
#endif
{
    uint32 txIntFlags = 0U;
#if (STD_ON == ETH_DEV_ERROR_DETECT)
    uint32 channelNum = 0U;
    uint32 cp         = 0U;
#endif
    /* Read the Tx interrupt cause from WR_C0_TX_STAT */
    txIntFlags = Cpsw_getChIntrStatus(Eth_DrvObj.baseAddr, CPSW_CH_INTR_TX);
#if (STD_ON == ETH_DEV_ERROR_DETECT)
    if (ETH_STATE_INIT != Eth_DrvStatus)
    {
        for (channelNum = 0U; channelNum < ETH_PRIORITY_QUEUE_NUM; channelNum++)
        {
            cp = CpswCpdma_readTxChCp(Eth_DrvObj.baseAddr, channelNum);
            CpswCpdma_writeTxChCp(Eth_DrvObj.baseAddr, channelNum, cp);
        }

        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_TX_IRQ_HDLR, ETH_E_UNINIT);
    }
    else
#endif
    {
        Eth_processTxIrqFlag(txIntFlags);
    }

    /* Write the EOI register */
    CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_TX);
}
#endif

/**
 *  \brief      This is the ISR function for for miscellaneous interrupts of ETH
 *              controller 0.
 *              This function is an ISR for combination of interrupts like time
 *              sync event, statistics, host error and MDIO interrupts.
 *
 *  \param[in]  void
 *
 *  \context    ISR
 */
MCAL_INTERRUPT_ATTRIBUTE
#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
FUNC(void, ETH_CODE_ISR) Eth_MiscIrqHdlr_0(void)
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_MiscIrqHdlr_0)
#endif
{
    uint32 intFlags = 0;
    uint32 retVal   = 0U;
    uint32 baseAddr = Eth_DrvObj.baseAddr;

    /* Read the Misc interrupt cause from WR_C0_MISC_STAT */
    intFlags = Cpsw_getMiscIntrStatus(baseAddr);

    /* Look for Statistics Interrupt */
    if (0U != CPSW_SS_GET_FIELD(intFlags, MISC_STATUS, STAT_PEND))
    {
#if (ETH_STATS_INTERRUPT == STD_ON)
        /* Update the driver statistics structure */
        CpswStats_update(baseAddr, &Eth_DrvObj.statsObj);
        CpswStats_clearHostPortStats(baseAddr);
#endif
    }
    /* Look for CPTS Event Interrupt */
    else if (0U != CPSW_SS_GET_FIELD(intFlags, MISC_STATUS, EVNT_PEND))
    {
#if (ETH_GLOBALTIMESUPPORT_API == STD_ON)
        /* Check till event is returned*/
        while ((uint32)1U == CpswCpts_getEventPendStatus(baseAddr))
        {
            /* Call the CPTS module to handle all CPTS event interrupts */
            CpswCpts_handleEvents(&Eth_DrvObj.cptsObj);
        }
#endif
    }
    /* Look for CPDMA Host Error Interrupt */
    else if (0U != CPSW_SS_GET_FIELD(intFlags, MISC_STATUS, HOST_PEND))
    {
#ifdef ETH_E_HARDWARE_ERROR
        (void)Dem_SetEventStatus(ETH_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
    }
    else
    {
        retVal = 1U;
    }

    if (retVal == (uint32)1U)
    {
#if (STD_ON == ETH_USR_MDIO_INTERRUPT)
        if (0U != CPSW_SS_GET_FIELD(intFlags, MISC_STATUS, MDIO_USERINT))
        {
#if (ETH_ENABLE_MII_API == STD_ON)
            /* Store the data if the read is acknowledged */
            uint16 dataVal = 0U;
            uint32 regVal  = 0U;
            uint32 phy     = 0U;
            uint32 offset  = 0U;
            phy            = MDIO_RD_REG(USER_INT_MASKED);
            if ((phy & MDIO_USER_INT_MASKED_REG_MAX) == MDIO_USER_INT_MASKED_REG_MAX)
            {
                offset = MDIO_USER_GROUP_USER_OFFSET;
            }

            regVal = MDIO_RD_OFFSET_REG(USER_GROUP_USER_ACCESS, offset);

            if (MDIO_USER_GROUP_USER_ACCESS_REG_ACK_PASS == (uint32)MDIO_GET_FIELD(regVal, USER_GROUP_USER_ACCESS, ACK))
            {
                dataVal = (uint16)MDIO_GET_FIELD(regVal, USER_GROUP_USER_ACCESS, DATA);
            }
            else
            {
                /*
                 * Nothing to do. As no way to indicate error to
                 * Transceiver.
                 */
                dataVal = 0U;
            }

            /* Indicate command read/write completion to TRCV */
            Eth_miiIndication(regVal, dataVal);
#endif
            CpswMdio_clearUsrIntr(baseAddr);
        }
#endif
    }

    /* Write the EOI register */
    CpswCpdma_writeEoiVector(baseAddr, CPSW_WR_INTR_LINE_MISC);
}

#if (ETH_ENABLE_RX_INTERRUPT == STD_ON)
/**
 *  @b HwIntRxThres
 *  @n
 *      CPSW Receive Threshold ISR.
 *
 *  \param[in]  void
 *
 *  \retval
 *      void
 */
MCAL_INTERRUPT_ATTRIBUTE
#if ((ETH_ISR_TYPE == ETH_ISR_CAT1) || (ETH_ISR_TYPE == ETH_ISR_VOID))
FUNC(void, ETH_CODE_ISR) Eth_RxThreshIrqHdlr_0(void)
#elif (ETH_ISR_TYPE == ETH_ISR_CAT2)
ISR(Eth_RxThreshIrqHdlr_0)
#endif
{
    uint32 threshIntFlags = 0U;
    uint32 channelNum = 0U, channelMask = 0U;
#if (STD_ON == ETH_DEV_ERROR_DETECT)
    uint32 cp = 0U;
#endif /* #if (STD_ON == ETH_DEV_ERROR_DETECT) */

    /* Read the RX_THRESH interrupt cause from WR_C0_RX_THRESH_STAT */
    threshIntFlags = Cpsw_getChIntrStatus(Eth_DrvObj.baseAddr, CPSW_CH_INTR_RX_THR);
#if (STD_ON == ETH_DEV_ERROR_DETECT)
    if (ETH_STATE_INIT != Eth_DrvStatus)
    {
        /*
         * If a crash occurs while interrupts were pending and the core is
         * restored (no system wide reset) we can end up here since the CPSW
         * ISRs are hooked before the driver has a chance to reset the HW.
         */
        for (channelNum = 0U; channelNum < ETH_PRIORITY_QUEUE_NUM; channelNum++)
        {
            /* Clear interrupts for this channel */
            cp = CpswCpdma_readRxChCp(Eth_DrvObj.baseAddr, channelNum);
            CpswCpdma_writeRxChCp(Eth_DrvObj.baseAddr, channelNum, cp);
        }

        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SID_RXTHR_IRQ_HDLR, ETH_E_UNINIT);
    }
    else
#endif
    {
        /*
         * Look for receive threshold interrupts from across all CPDMA Rx
         * Channels.
         */
        while ((uint32)0U != threshIntFlags)
        {
            channelMask = (uint32)0x1U << channelNum;

            if ((uint32)0U != (uint32)(threshIntFlags & channelMask))
            {
                Eth_processRxBuffDesc(Eth_DrvObj.ctrlIdx, channelNum);
            }

            /* Clear the channel flags for the channel just handled */
            threshIntFlags &= ~channelMask;
            channelNum++;
        }
    }

    /* Write the EOI register */
    CpswCpdma_writeEoiVector(Eth_DrvObj.baseAddr, CPSW_WR_INTR_LINE_RX_THR);
}
#endif

#define ETH_STOP_SEC_ISR_CODE

/* MISRAC_2012_R.20.1
 * "Reason - This is the format to use for specifying memory sections " */
#include "Eth_MemMap.h"
