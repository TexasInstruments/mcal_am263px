/*
 * Copyright (C) 2024 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 *   Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \defgroup DRV_CDD_EDMA_MODULE APIs for EDMA
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the EDMA.
 *
 *  @{
 */

/**
 *  \file Cdd_Dma_Priv.h
 *
 *  \brief This file contains the prototype of EDMA driver APIs
 *
 *  \details  Please find the below detailed description of edma dal.
 *            -# Programming sequence for initializing the edma controller
 *               -# Perform the clock configuration of channel controller and
 *                  transfer controllers.
 *               -# To perform initialization of controller use the
 *                  -# #CDD_EDMA_init with appropriate #CDD_EDMA_InitParams
 *                     which is part of the #CDD_EDMA_Attrs
 *            -# Programming sequence for setting up edma channel.
 *               -# To configure the PaRAM sets use #CDD_EDMA_setPaRAM. For
 *                  custom use
 *               -# To start transfer use #CDD_EDMA_enableTransferRegion.
 *               -# To stop transfer use #CDD_EDMA_disableTransferRegion.
 */

#ifndef CDD_DMA_PRIV_H_
#define CDD_DMA_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Std_Types.h"
#include "Cdd_Dma_edma.h"
#include "sys_common.h"
#define CDD_DMA_START_SEC_CODE
#include "Cdd_Dma_MemMap.h"
#include "hw_types.h" /* Map the static inline functions in this file as well */
#define CDD_DMA_STOP_SEC_CODE
#include "Cdd_Dma_MemMap.h"
#include "SchM_Cdd_Dma.h"

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/** @brief Number of DMA Channels */
#define CDD_EDMA_NUM_DMACH (64U)
/** @brief Number of PaRAM Sets available */
#define CDD_EDMA_NUM_PARAMSETS (256U)
/** @brief Number of Event Queues available */
#define CDD_EDMA_NUM_EVQUE (2U)
/** @brief Support for Channel to PaRAM Set mapping */
#define CDD_EDMA_CHMAPEXIST (1U)
/** @brief Number of EDMA Regions */
#define CDD_EDMA_NUM_REGIONS (8U)
/** @brief Support for Memory Protection */
#define CDD_EDMA_MEMPROTECT (1U)

/** \anchor CDD_EDMA_QUEUE_NUM_DEFS
 *   \name EDMA Queue Number Configuration.
 *  @{
 */
#define CDD_EDMACC_DMAQNUM_CLR(chNum) (~((uint32)0x7U << (((chNum) % 8U) * 4U)))
/**< DMAQNUM bits Clear */
#define CDD_EDMACC_DMAQNUM_SET(chNum, queNum) (((uint32)0x7U & (queNum)) << (((chNum) % 8U) * 4U))
/**< DMAQNUM bits Set */

/** @} */

/** \anchor CDD_EDMA_QDMA_MAPPING_DEFS
 *   \name EDMA Qdma Channel mapping Configuration.
 *  @{
 */
#define CDD_EDMACC_QCHMAP_PAENTRY_CLR ((uint32)(~((uint32)CDD_EDMA_TPCC_QCHMAPN_PAENTRY_MASK)))
/**< QCHMAP Param ID Clear */
#define CDD_EDMACC_QCHMAP_PAENTRY_SET(paRAMId)                                                 \
    (((CDD_EDMA_TPCC_QCHMAPN_PAENTRY_MASK >> CDD_EDMA_TPCC_QCHMAPN_PAENTRY_SHIFT) & (paRAMId)) \
     << CDD_EDMA_TPCC_QCHMAPN_PAENTRY_SHIFT) /**< QCHMAP-PaRAMEntry bitfield Set */
#define CDD_EDMACC_QCHMAP_TRWORD_CLR ((uint32)(~((uint32)CDD_EDMA_TPCC_QCHMAPN_TRWORD_MASK)))
/**< QCHMAP-TrigWord bitfield Clear */
#define CDD_EDMACC_QCHMAP_TRWORD_SET(paRAMId)                                                \
    (((CDD_EDMA_TPCC_QCHMAPN_TRWORD_MASK >> CDD_EDMA_TPCC_QCHMAPN_TRWORD_SHIFT) & (paRAMId)) \
     << CDD_EDMA_TPCC_QCHMAPN_TRWORD_SHIFT)
/**< QCHMAP-TrigWord bitfield Set */
/** @} */

/** \anchor CDD_EDMA_TRIGGER_MODE_DEFS
 *   \name EDMA Trigger Mode Configuration.
 *  @{
 */
#define CDD_EDMA_TRIG_MODE_MANUAL ((uint32)0U)
/**< Manually trigger EDMA transfer */
#define CDD_EDMA_TRIG_MODE_EVENT ((uint32)1U)
/**< Trigger EDMA transfer upon Event */
/** @} */

/** \anchor CDD_EDMA_CHANNEL_TYPE_DEFS
 *   \name EDMA channel type definitions.
 *  @{
 */
/** \brief Values that can be used for parameter chType in API's
 */
#define CDD_EDMA_CHANNEL_TYPE_DMA ((uint32)0U)
/**< Channel Typr DMA */
/** @} */

/** \anchor CDD_EDMA_EVENT_STATUS_DEFS
 *   \name EDMA event status definitions.
 *  @{
 */
/** \brief Values that can be used to specify different event status
 */
#define CDD_EDMA_XFER_COMPLETE ((uint32)0U)
/**< Transfer Complete */
#define CDD_EDMA_CC_DMA_EVT_MISS ((uint32)1U)
/**< DMA Event Miss */

/** @} */

/** \anchor CDD_EDMA_TRANSFER_TYPE_DEFS
 *   \name EDMA transfer type definitions.
 *  @{
 */
/**
 *   \brief Values that can be used to specify different
 *   synchronization events
 */
#define CDD_EDMA_SYNC_A ((uint32)0U)
/**< A Sync Transfer */
#define CDD_EDMA_SYNC_AB ((uint32)1U)
/** AB Sync Transfer */
/** @} */

/** \anchor CDD_EDMA_ADDRESSING_MODE_DEFS
 *   \name EDMA addressing modes definitions.
 *  @{
 */
/** \brief Values that can be used to specify different
 * addressing modes (relevant for SAM and DAM sub-fields in OPT field).
 */
#define CDD_EDMA_ADDRESSING_MODE_LINEAR ((uint32)0U)
/**< Incremental addressing (INCR), not FIFO */
#define CDD_EDMA_ADDRESSING_MODE_FIFO_WRAP ((uint32)1U)
/**< Constant addressing (CONST) within the FIFO array, wraps around upon
    reaching FIFO width */
/** @} */

/** \anchor CDD_EDMA_FIFO_WIDTH_DEFS
 *   \name EDMA FIFO width definitions.
 *  @{
 */
/** \brief Values that can be used to specify different FIFO widths (FWID in OPT field).
 */
#define CDD_EDMA_FIFO_WIDTH_8BIT ((uint32)CDD_EDMA_TPCC_OPT_FWID_FIFOWIDTH8BIT)
/**< 8-bit FIFO width */
#define CDD_EDMA_FIFO_WIDTH_16BIT ((uint32)CDD_EDMA_TPCC_OPT_FWID_FIFOWIDTH16BIT)
/**< 16-bit FIFO width */
#define CDD_EDMA_FIFO_WIDTH_32BIT ((uint32)CDD_EDMA_TPCC_OPT_FWID_FIFOWIDTH32BIT)
/**< 32-bit FIFO width */
#define CDD_EDMA_FIFO_WIDTH_64BIT ((uint32)CDD_EDMA_TPCC_OPT_FWID_FIFOWIDTH64BIT)
/**< 64-bit FIFO width */
#define CDD_EDMA_FIFO_WIDTH_128BIT ((uint32)CDD_EDMA_TPCC_OPT_FWID_FIFOWIDTH128BIT)
/**< 128-bit FIFO width */
#define CDD_EDMA_FIFO_WIDTH_256BIT ((uint32)DMA_TPCC_OPT_FWID_FIFOWIDTH256BIT)
/**< 256-bit FIFO width */
/** @} */

/** \anchor CDD_EDMA_CLEAR_CC_ERROR_DEFS
 *   \name EDMA Clear Channel controller Error.
 *  @{
 */
/** \brief Values that can be used to Clear any Channel controller Errors
 */
#define CDD_EDMACC_CLR_TCCERR ((uint32)CDD_EDMA_TPCC_CCERRCLR_TCERR_MASK)
/**< Cleat TCC Error */
#define CDD_EDMACC_CLR_QTHRQ0 ((uint32)CDD_EDMA_TPCC_CCERRCLR_QTHRXCD0_MASK)
/**< Cleat Queue threshold 0 Error */
#define CDD_EDMACC_CLR_QTHRQ1 ((uint32)CDD_EDMA_TPCC_CCERRCLR_QTHRXCD1_MASK)
/**< Cleat Queue threshold 1 Error */
/** @} */

/** \anchor CDD_EDMA_PARAM_OPT_FIELD_DEFS
 *   \name EDMA Param OPT fields.
 *  @{
 */
/** \brief Values that are used to Chain two specified channels */
#define CDD_EDMA_OPT_TCCHEN_MASK ((uint32)CDD_EDMA_TPCC_OPT_TCCHEN_MASK)
/**< Transfer Complete Chaining enable */
#define CDD_EDMA_OPT_ITCCHEN_MASK ((uint32)CDD_EDMA_TPCC_OPT_ITCCHEN_MASK)
/**< Intermediate Transfer Complete Chaining enable */
#define CDD_EDMA_OPT_TCINTEN_MASK ((uint32)CDD_EDMA_TPCC_OPT_TCINTEN_MASK)
/**< Transfer Complete Interrupt enable */
#define CDD_EDMA_OPT_ITCINTEN_MASK ((uint32)CDD_EDMA_TPCC_OPT_ITCINTEN_MASK)
/**< Intermediate Transfer Complete Interrupt enable */
#define CDD_EDMA_OPT_TCC_MASK ((uint32)CDD_EDMA_TPCC_OPT_TCC_MASK)
/**< Transfer Complete Code mask */
#define CDD_EDMA_OPT_TCC_SHIFT ((uint32)CDD_EDMA_TPCC_OPT_TCC_SHIFT)
/**< Transfer Complete Code shift */
#define CDD_EDMA_OPT_SYNCDIM_MASK ((uint32)CDD_EDMA_TPCC_OPT_SYNCDIM_MASK)
/**< Sync Type shift */
#define CDD_EDMA_OPT_SYNCDIM_SHIFT ((uint32)CDD_EDMA_TPCC_OPT_SYNCDIM_SHIFT)
/**< Sync Type mask */
#define CDD_EDMA_OPT_STATIC_MASK ((uint32)CDD_EDMA_TPCC_OPT_STATIC_MASK)
/**< Param Static mask */
#define CDD_EDMA_OPT_STATIC_SHIFT ((uint32)CDD_EDMA_TPCC_OPT_STATIC_SHIFT)
/**< Param Static mask */
#define CDD_EDMACC_OPT_TCC_CLR ((uint32)(~CDD_EDMA_TPCC_OPT_TCC_MASK))
/**< OPT-TCC bitfield Clear */
#define CDD_EDMACC_OPT_TCC_SET(tcc) \
    (((CDD_EDMA_TPCC_OPT_TCC_MASK >> CDD_EDMA_TPCC_OPT_TCC_SHIFT) & (tcc)) << CDD_EDMA_TPCC_OPT_TCC_SHIFT)
/**< OPT-TCC bitfield Set */
/** @} */

/** \anchor CDD_EDMA_PARAM_FIELD_DEFS
 *   \name EDMA Param fields.
 *  @{
 */
/** \brief PaRAMEntry Fields */
#define CDD_EDMACC_PARAM_ENTRY_OPT ((uint32)0x0U)
/**< The OPT field (Offset Address 0x0 Bytes) */
#define CDD_EDMACC_PARAM_ENTRY_SRC ((uint32)0x1U)
/**< The SRC field (Offset Address 0x4 Bytes)*/
#define CDD_EDMACC_PARAM_ENTRY_ACNT_BCNT ((uint32)0x2U)
/**< The (ACNT+BCNT) field (Offset Address 0x8 Bytes)*/
#define CDD_EDMACC_PARAM_ENTRY_DST ((uint32)0x3U)
/**< The DST field (Offset Address 0xC Bytes)*/
#define CDD_EDMACC_PARAM_ENTRY_SRC_DST_BIDX ((uint32)0x4U)
/**< The (SRCBIDX+DSTBIDX) field (Offset Address 0x10 Bytes)*/
#define CDD_EDMACC_PARAM_ENTRY_LINK_BCNTRLD ((uint32)0x5U)
/**< The (LINK+BCNTRLD) field (Offset Address 0x14 Bytes)*/
#define CDD_EDMACC_PARAM_ENTRY_SRC_DST_CIDX ((uint32)0x6U)
/**< The (SRCCIDX+DSTCIDX) field (Offset Address 0x18 Bytes)*/
#define CDD_EDMACC_PARAM_ENTRY_CCNT ((uint32)0x7U)
/**< The (CCNT+RSVD) field (Offset Address 0x1C Bytes)*/
#define CDD_EDMACC_PARAM_FIELD_OFFSET ((uint32)0x4U)
/**< The offset for each PaRAM Entry field */
#define CDD_EDMACC_PARAM_ENTRY_FIELDS ((uint32)0x8U)
/**< Number of PaRAM Entry fields.
 *   OPT, SRC, A_B_CNT, DST, SRC_DST_BIDX, LINK_BCNTRLD, SRC_DST_CIDX
 *   and CCNT
 */
#define CDD_EDMA_NUM_TCC ((uint32)CDD_EDMA_NUM_DMACH)
/**< Number of TCC's available */
/** @} */
#define CDD_EDMA_MAPPING_SHIFT 5U
#define CDD_EDMA_QUEUE_SHIFT   3U

/** \anchor CDD_EDMA_RESOURCE_TYPE_DEFS
 *   \name EDMA resource type definition used for resource allocation and freeing.
 *  @{
 */
/** \brief Values that can be used for parameter resType in API's
 */
#define CDD_EDMA_RESOURCE_TYPE_DMA ((uint32)0U)
/**< Resource Type DMA */
#define CDD_EDMA_RESOURCE_TYPE_TCC ((uint32)2U)
/**< Resource Type TCC */
#define CDD_EDMA_RESOURCE_TYPE_PARAM ((uint32)3U)
/**< Resource Type PARAM */
#define CDD_EDMA_RESOURCE_ALLOC_ANY ((uint32)0xFFFFU)
/**< Allocate any available resource */
/** @} */

#define CDD_EDMA_SET_ALL_BITS ((uint32)0xFFFFFFFFU)
/**< Used to set all Bits in a register */
#define CDD_EDMA_CLR_ALL_BITS ((uint32)0x00000000U)
/**< Used to clear all Bits in a register */
#define CDD_EDMACC_COMPL_HANDLER_RETRY_COUNT ((uint32)10U)
/**< Completion interrupt handler retry count */
#define CDD_EDMACC_ERR_HANDLER_RETRY_COUNT ((uint32)10U)
/**< Error interrupt handler retry count */

/* ========================================================================== */
/*                         Structures                                         */
/* ========================================================================== */

/**
 * \brief EDMA Parameter RAM Set in User Configurable format
 *        This is a mapping of the EDMA PaRAM set provided to the user
 *        for ease of modification of the individual fields
 */
typedef enum
{
    /* when transfer type is Uart Tx peripheral */
    CDD_DMA_TRANSFER_TYPE_UART_TX = 0x0U,
    /* when transfer type is Uart Rx peripheral */
    CDD_DMA_TRANSFER_TYPE_UART_RX = 0x1U,
    /* when transfer type is ADC peripheral */
    CDD_DMA_TRANSFER_TYPE_ADC = 0x2U,
    /* when transfer type is MC Spi peripheral */
    CDD_DMA_TRANSFER_TYPE_MCSPI = 0x3U,
    /* when transfer type is Memory transfer and not any peripheral using Dma */
    CDD_DMA_TRANSFER_TYPE_MEMORY_TRANSFER = 0x4U,
    /* when transfer type is Qspi peripheral */
    CDD_DMA_TRANSFER_TYPE_QSPI = 0x5U,
    /* when transfer type is Fls peripheral */
    CDD_DMA_TRANSFER_TYPE_FLS = 0x6U

} Cdd_Dma_TransferType;

typedef enum
{
    /* When transfer happens with single channel and single param set is linked with the channel */
    CDD_DMA_TRANSFER_MODE_NORMAL = 0x0U,
    /* When transfer happens with single channel and multiple param set is linked with the channel
     */
    CDD_DMA_TRANSFER_MODE_LINKING = 0x1U,
    /* When transfer happens with multiple channel and single param set is linked with the each
       channel */
    CDD_DMA_TRANSFER_MODE_CHAINING = 0x2U

} Cdd_Dma_TransferMode;

typedef struct
{
    /* \brief OPT field of PaRAM Set */
    uint32 opt;
    /**
     * \brief Starting byte address of Source
     * For FIFO mode, srcAddr must be a 256-bit aligned address.
     */
    uint32 srcAddr;
    /* \brief Number of bytes in each Array (ACNT) */
    uint16 aCnt;
    /* \brief Number of Arrays in each Frame (BCNT) */
    uint16 bCnt;
    /**
     * \brief Starting byte address of destination
     * For FIFO mode, destAddr must be a 256-bit aligned address.
     * i.e. 5 LSBs should be 0.
     */
    uint32 destAddr;
    /* \brief Index between consec. arrays of a Source Frame (SRCBIDX) */
    sint16 srcBIdx;
    /* \brief Index between consec. arrays of a Destination Frame (DSTBIDX) */
    sint16 destBIdx;
    /**
     * \brief Address for linking (AutoReloading of a PaRAM Set)
     * This must point to a valid aligned 32-byte PaRAM set
     * A value of 0xFFFF means no linking
     */
    uint16 linkAddr;
    /**
     * \brief Reload value of the numArrInFrame (BCNT)
     * Relevant only for A-sync transfers
     */
    uint16 bCntReload;
    /* \brief Index between consecutive frames of a Source Block (SRCCIDX) */
    sint16 srcCIdx;
    /* \brief Index between consecutive frames of a Dest Block (DSTCIDX) */
    sint16 destCIdx;
    /* \brief Number of Frames in a block (CCNT) */
    uint16 cCnt;
    /* \brief Reserved bit field (Should not be written with a non zero value) */
    uint16 reserved;

} __attribute__((packed)) CDD_EDMACCEDMACCPaRAMEntry;

typedef struct
{
    /* data */
    uint32 paramId;

} Cdd_Dma_ParamSets;

typedef struct
{
    /* Id of the channel or channel number */
    uint32              channelId;
    /* indicate the max number of param associated with the channel  */
    uint32              maxParam;
    /* Contain the group of param associated with the channel */
    Cdd_Dma_ParamSets **paramGroup;
} Cdd_Dma_ChannelGroup;

typedef struct
{
    /* indicate the max number of channel for that particular handle */
    uint32                 maxChannel;
    /* this will contain the channel group which is associated with the handle */
    Cdd_Dma_ChannelGroup **channelGroup;

} Cdd_Dma_ResourceObject;

typedef struct
{
    /* data */
    uint32                 compIntrNumber;
    /**< Completion interrupt number. */
    uint32                 intrAggEnableAddr;
    /**< Interrupt Aggregator enable address */
    uint32                 intrAggEnableMask;
    /**< Interrupt Aggregator enable mask */
    uint32                 intrAggStatusAddr;
    /**< Interrupt Aggregator enable address */
    uint32                 intrAggClearMask;
    /**< Interrupt Aggregator clear mask */
    uint32                 intrEnable;
    /**< Enable interrupt mode */
    uint32                 regionId;
    /**< EDMA region to be used */
    uint32                 queNum;
    /**< EDMA Event queue to be used for all channels */
    uint32                 tcc;
    /**< EDMA tcc to be used */
    Cdd_Dma_TransferType   transferType;
    /**< EDMA transfer type */
    Cdd_Dma_TransferMode   transferMode;
    /**< EDMA Transfer Mode which you need to used */
    Cdd_Dma_ResourceObject ownResource;
    /**< EDMA ownResources information regarding the channel and param */
} Cdd_Dma_InitHandleType;

typedef struct
{
    /* Revision Id  */
    uint32 revisionId;
} Cdd_Dma_RegisterReadbackType;

typedef struct
{
    /* Baseaddress of the dDma instance used */
    uint32                 baseAddr;
    /* Dma confif parameters from the configuration*/
    Cdd_Dma_InitHandleType edmaConfig;
} Cdd_Dma_Handler;

typedef struct Cdd_Dma_ConfigType_s
{
    /* pointer to the handler */
    Cdd_Dma_Handler **CddDmaDriverHandler;
} Cdd_Dma_ConfigType;

extern Cdd_Dma_ConfigType *Cdd_Dma_HandlerList;
extern uint32              Cdd_Dma_ChainingTcc[CDD_EDMA_NUM_DMACH][CDD_EDMA_NUM_DMACH];

/**
 * \brief EDMA interrupt callback function prototype
 */
typedef void (*Cdd_Edma_EventCallback)(void *appData);

typedef struct
{
    volatile uint32 pid;
    volatile uint32 mss_sw_int;
    volatile uint32 mss_capevnt_sel;
    volatile uint32 mss_dma_req_sel;
    volatile uint32 mss_dma1_req_sel;
    volatile uint32 mss_irq_req_sel;
    volatile uint32 mss_spi_trig_src;
    volatile uint32 mss_atcm_mem_init;
    volatile uint32 mss_atcm_mem_init_done;
    volatile uint32 mss_atcm_mem_init_status;
    volatile uint32 mss_btcm_mem_init;
    volatile uint32 mss_btcm_mem_init_done;
    volatile uint32 mss_btcm_mem_init_status;
    volatile uint32 mss_l2_mem_init;
    volatile uint32 mss_l2_mem_init_done;
    volatile uint32 mss_l2_mem_init_status;
    volatile uint32 mss_mailbox_mem_init;
    volatile uint32 mss_mailbox_mem_init_done;
    volatile uint32 mss_mailbox_mem_init_status;
    volatile uint32 mss_retram_mem_init;
    volatile uint32 mss_retram_mem_init_done;
    volatile uint32 mss_retram_mem_init_status;
    volatile uint32 mss_spia_mem_init;
    volatile uint32 mss_spia_mem_init_done;
    volatile uint32 mss_spia_mem_init_status;
    volatile uint32 mss_spib_mem_init;
    volatile uint32 mss_spib_mem_init_done;
    volatile uint32 mss_spib_mem_init_status;
    volatile uint32 mss_tpcc_meminit_start;
    volatile uint32 mss_tpcc_meminit_done;
    volatile uint32 mss_tpcc_meminit_status;
    volatile uint32 mss_gpadc_mem_init;
    volatile uint32 mss_gpadc_mem_init_done;
    volatile uint32 mss_gpadc_mem_init_status;
    volatile uint32 mss_spia_cfg;
    volatile uint32 mss_spib_cfg;
    volatile uint32 mss_epwm_cfg;
    volatile uint32 mss_gio_cfg;
    volatile uint32 mss_mcan_fe_select;
    volatile uint32 hw_spare_reg1;
    volatile uint32 mss_mcana_int_clr;
    volatile uint32 mss_mcana_int_mask;
    volatile uint32 mss_mcana_int_stat;
    volatile uint32 hw_spare_reg2;
    volatile uint32 ccc_err_status;
    volatile uint32 ccca_cfg0;
    volatile uint32 ccca_cfg1;
    volatile uint32 ccca_cfg2;
    volatile uint32 ccca_cfg3;
    volatile uint32 ccca_cntval;
    volatile uint32 cccb_cfg0;
    volatile uint32 cccb_cfg1;
    volatile uint32 cccb_cfg2;
    volatile uint32 cccb_cfg3;
    volatile uint32 cccb_cntval;
    volatile uint32 ccc_dcc_common;
    volatile uint32 r5_global_config;
    volatile uint32 r5_ahb_en;
    volatile uint32 r5a_ahb_base;
    volatile uint32 r5a_ahb_size;
    volatile uint32 r5b_ahb_base;
    volatile uint32 r5b_ahb_size;
    volatile uint32 r5_tcm_ext_err_en;
    volatile uint32 r5_tcm_err_en;
    volatile uint32 r5_init_tcm;
    volatile uint32 r5_tcm_ecc_wrenz_en;
    volatile uint32 esm_gating0;
    volatile uint32 esm_gating1;
    volatile uint32 esm_gating2;
    volatile uint32 esm_gating3;
    volatile uint32 esm_gating4;
    volatile uint32 esm_gating5;
    volatile uint32 esm_gating6;
    volatile uint32 esm_gating7;
    volatile uint32 err_parity_atcm0;
    volatile uint32 err_parity_atcm1;
    volatile uint32 err_parity_b0tcm0;
    volatile uint32 err_parity_b0tcm1;
    volatile uint32 err_parity_b1tcm0;
    volatile uint32 err_parity_b1tcm1;
    volatile uint32 tcm_parity_ctrl;
    volatile uint32 tcm_parity_errfrc;
    volatile uint32 hw_spare_reg3;
    volatile uint32 spia_io_cfg;
    volatile uint32 spib_io_cfg;
    volatile uint32 spi_host_irq;
    volatile uint32 tptc_dbs_config;
    volatile uint32 tpcc_parity_ctrl;
    volatile uint32 tpcc_parity_status;
    volatile uint32 mss_dbg_ack_ctl0;
    volatile uint32 mss_dbg_ack_ctl1;
    volatile uint32 cpsw_control;
    volatile uint32 mss_tpcc_a_erragg_mask;
    volatile uint32 mss_tpcc_a_erragg_status;
    volatile uint32 mss_tpcc_a_erragg_status_raw;
    volatile uint32 mss_tpcc_a_intagg_mask;
    volatile uint32 mss_tpcc_a_intagg_status;
    volatile uint32 mss_tpcc_a_intagg_status_raw;
    volatile uint32 mss_tpcc_b_erragg_mask;
    volatile uint32 mss_tpcc_b_erragg_status;
    volatile uint32 mss_tpcc_b_erragg_status_raw;
    volatile uint32 mss_tpcc_b_intagg_mask;
    volatile uint32 mss_tpcc_b_intagg_status;
    volatile uint32 mss_tpcc_b_intagg_status_raw;
    volatile uint32 mss_bus_safety_ctrl;
    volatile uint32 mss_cr5a_axi_rd_bus_safety_ctrl;
    volatile uint32 mss_cr5a_axi_rd_bus_safety_fi;
    volatile uint32 mss_cr5a_axi_rd_bus_safety_err;
    volatile uint32 mss_cr5a_axi_rd_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5a_axi_rd_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5a_axi_rd_bus_safety_err_stat_read;
    volatile uint32 mss_cr5b_axi_rd_bus_safety_ctrl;
    volatile uint32 mss_cr5b_axi_rd_bus_safety_fi;
    volatile uint32 mss_cr5b_axi_rd_bus_safety_err;
    volatile uint32 mss_cr5b_axi_rd_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5b_axi_rd_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5b_axi_rd_bus_safety_err_stat_read;
    volatile uint32 mss_cr5a_axi_wr_bus_safety_ctrl;
    volatile uint32 mss_cr5a_axi_wr_bus_safety_fi;
    volatile uint32 mss_cr5a_axi_wr_bus_safety_err;
    volatile uint32 mss_cr5a_axi_wr_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5a_axi_wr_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5a_axi_wr_bus_safety_err_stat_write;
    volatile uint32 mss_cr5a_axi_wr_bus_safety_err_stat_writeresp;
    volatile uint32 mss_cr5b_axi_wr_bus_safety_ctrl;
    volatile uint32 mss_cr5b_axi_wr_bus_safety_fi;
    volatile uint32 mss_cr5b_axi_wr_bus_safety_err;
    volatile uint32 mss_cr5b_axi_wr_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5b_axi_wr_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5b_axi_wr_bus_safety_err_stat_write;
    volatile uint32 mss_cr5b_axi_wr_bus_safety_err_stat_writeresp;
    volatile uint32 mss_cr5a_axi_s_bus_safety_ctrl;
    volatile uint32 mss_cr5a_axi_s_bus_safety_fi;
    volatile uint32 mss_cr5a_axi_s_bus_safety_err;
    volatile uint32 mss_cr5a_axi_s_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5a_axi_s_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5a_axi_s_bus_safety_err_stat_write;
    volatile uint32 mss_cr5a_axi_s_bus_safety_err_stat_read;
    volatile uint32 mss_cr5a_axi_s_bus_safety_err_stat_writeresp;
    volatile uint32 mss_cr5b_axi_s_bus_safety_ctrl;
    volatile uint32 mss_cr5b_axi_s_bus_safety_fi;
    volatile uint32 mss_cr5b_axi_s_bus_safety_err;
    volatile uint32 mss_cr5b_axi_s_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5b_axi_s_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5b_axi_s_bus_safety_err_stat_write;
    volatile uint32 mss_cr5b_axi_s_bus_safety_err_stat_read;
    volatile uint32 mss_cr5b_axi_s_bus_safety_err_stat_writeresp;
    volatile uint32 mss_tptc_a0_rd_bus_safety_ctrl;
    volatile uint32 mss_tptc_a0_rd_bus_safety_fi;
    volatile uint32 mss_tptc_a0_rd_bus_safety_err;
    volatile uint32 mss_tptc_a0_rd_bus_safety_err_stat_data0;
    volatile uint32 mss_tptc_a0_rd_bus_safety_err_stat_cmd;
    volatile uint32 mss_tptc_a0_rd_bus_safety_err_stat_read;
    volatile uint32 mss_tptc_a1_rd_bus_safety_ctrl;
    volatile uint32 mss_tptc_a1_rd_bus_safety_fi;
    volatile uint32 mss_tptc_a1_rd_bus_safety_err;
    volatile uint32 mss_tptc_a1_rd_bus_safety_err_stat_data0;
    volatile uint32 mss_tptc_a1_rd_bus_safety_err_stat_cmd;
    volatile uint32 mss_tptc_a1_rd_bus_safety_err_stat_read;
    volatile uint32 mss_tptc_b0_rd_bus_safety_ctrl;
    volatile uint32 mss_tptc_b0_rd_bus_safety_fi;
    volatile uint32 mss_tptc_b0_rd_bus_safety_err;
    volatile uint32 mss_tptc_b0_rd_bus_safety_err_stat_data0;
    volatile uint32 mss_tptc_b0_rd_bus_safety_err_stat_cmd;
    volatile uint32 mss_tptc_b0_rd_bus_safety_err_stat_read;
    volatile uint32 mss_tptc_a0_wr_bus_safety_ctrl;
    volatile uint32 mss_tptc_a0_wr_bus_safety_fi;
    volatile uint32 mss_tptc_a0_wr_bus_safety_err;
    volatile uint32 mss_tptc_a0_wr_bus_safety_err_stat_data0;
    volatile uint32 mss_tptc_a0_wr_bus_safety_err_stat_cmd;
    volatile uint32 mss_tptc_a0_wr_bus_safety_err_stat_write;
    volatile uint32 mss_tptc_a0_wr_bus_safety_err_stat_writeresp;
    volatile uint32 mss_tptc_a1_wr_bus_safety_ctrl;
    volatile uint32 mss_tptc_a1_wr_bus_safety_fi;
    volatile uint32 mss_tptc_a1_wr_bus_safety_err;
    volatile uint32 mss_tptc_a1_wr_bus_safety_err_stat_data0;
    volatile uint32 mss_tptc_a1_wr_bus_safety_err_stat_cmd;
    volatile uint32 mss_tptc_a1_wr_bus_safety_err_stat_write;
    volatile uint32 mss_tptc_a1_wr_bus_safety_err_stat_writeresp;
    volatile uint32 mss_tptc_b0_wr_bus_safety_ctrl;
    volatile uint32 mss_tptc_b0_wr_bus_safety_fi;
    volatile uint32 mss_tptc_b0_wr_bus_safety_err;
    volatile uint32 mss_tptc_b0_wr_bus_safety_err_stat_data0;
    volatile uint32 mss_tptc_b0_wr_bus_safety_err_stat_cmd;
    volatile uint32 mss_tptc_b0_wr_bus_safety_err_stat_write;
    volatile uint32 mss_tptc_b0_wr_bus_safety_err_stat_writeresp;
    volatile uint32 hsm_tptc_a0_rd_bus_safety_ctrl;
    volatile uint32 hsm_tptc_a0_rd_bus_safety_fi;
    volatile uint32 hsm_tptc_a0_rd_bus_safety_err;
    volatile uint32 hsm_tptc_a0_rd_bus_safety_err_stat_data0;
    volatile uint32 hsm_tptc_a0_rd_bus_safety_err_stat_cmd;
    volatile uint32 hsm_tptc_a0_rd_bus_safety_err_stat_read;
    volatile uint32 hsm_tptc_a1_rd_bus_safety_ctrl;
    volatile uint32 hsm_tptc_a1_rd_bus_safety_fi;
    volatile uint32 hsm_tptc_a1_rd_bus_safety_err;
    volatile uint32 hsm_tptc_a1_rd_bus_safety_err_stat_data0;
    volatile uint32 hsm_tptc_a1_rd_bus_safety_err_stat_cmd;
    volatile uint32 hsm_tptc_a1_rd_bus_safety_err_stat_read;
    volatile uint32 hsm_tptc_a0_wr_bus_safety_ctrl;
    volatile uint32 hsm_tptc_a0_wr_bus_safety_fi;
    volatile uint32 hsm_tptc_a0_wr_bus_safety_err;
    volatile uint32 hsm_tptc_a0_wr_bus_safety_err_stat_data0;
    volatile uint32 hsm_tptc_a0_wr_bus_safety_err_stat_cmd;
    volatile uint32 hsm_tptc_a0_wr_bus_safety_err_stat_write;
    volatile uint32 hsm_tptc_a0_wr_bus_safety_err_stat_writeresp;
    volatile uint32 hsm_tptc_a1_wr_bus_safety_ctrl;
    volatile uint32 hsm_tptc_a1_wr_bus_safety_fi;
    volatile uint32 hsm_tptc_a1_wr_bus_safety_err;
    volatile uint32 hsm_tptc_a1_wr_bus_safety_err_stat_data0;
    volatile uint32 hsm_tptc_a1_wr_bus_safety_err_stat_cmd;
    volatile uint32 hsm_tptc_a1_wr_bus_safety_err_stat_write;
    volatile uint32 hsm_tptc_a1_wr_bus_safety_err_stat_writeresp;
    volatile uint32 mss_qspi_bus_safety_ctrl;
    volatile uint32 mss_qspi_bus_safety_fi;
    volatile uint32 mss_qspi_bus_safety_err;
    volatile uint32 mss_qspi_bus_safety_err_stat_data0;
    volatile uint32 mss_qspi_bus_safety_err_stat_cmd;
    volatile uint32 mss_qspi_bus_safety_err_stat_write;
    volatile uint32 mss_qspi_bus_safety_err_stat_read;
    volatile uint32 mss_qspi_bus_safety_err_stat_writeresp;
    volatile uint32 hsm_dthe_bus_safety_ctrl;
    volatile uint32 hsm_dthe_bus_safety_fi;
    volatile uint32 hsm_dthe_bus_safety_err;
    volatile uint32 hsm_dthe_bus_safety_err_stat_data0;
    volatile uint32 hsm_dthe_bus_safety_err_stat_cmd;
    volatile uint32 hsm_dthe_bus_safety_err_stat_write;
    volatile uint32 hsm_dthe_bus_safety_err_stat_read;
    volatile uint32 hsm_dthe_bus_safety_err_stat_writeresp;
    volatile uint32 mss_cpsw_bus_safety_ctrl;
    volatile uint32 mss_cpsw_bus_safety_fi;
    volatile uint32 mss_cpsw_bus_safety_err;
    volatile uint32 mss_cpsw_bus_safety_err_stat_data0;
    volatile uint32 mss_cpsw_bus_safety_err_stat_cmd;
    volatile uint32 mss_cpsw_bus_safety_err_stat_write;
    volatile uint32 mss_cpsw_bus_safety_err_stat_read;
    volatile uint32 mss_cpsw_bus_safety_err_stat_writeresp;
    volatile uint32 mss_mcrc_bus_safety_ctrl;
    volatile uint32 mss_mcrc_bus_safety_fi;
    volatile uint32 mss_mcrc_bus_safety_err;
    volatile uint32 mss_mcrc_bus_safety_err_stat_data0;
    volatile uint32 mss_mcrc_bus_safety_err_stat_cmd;
    volatile uint32 mss_mcrc_bus_safety_err_stat_write;
    volatile uint32 mss_mcrc_bus_safety_err_stat_read;
    volatile uint32 mss_mcrc_bus_safety_err_stat_writeresp;
    volatile uint32 mss_pcr_bus_safety_ctrl;
    volatile uint32 mss_pcr_bus_safety_fi;
    volatile uint32 mss_pcr_bus_safety_err;
    volatile uint32 mss_pcr_bus_safety_err_stat_data0;
    volatile uint32 mss_pcr_bus_safety_err_stat_cmd;
    volatile uint32 mss_pcr_bus_safety_err_stat_write;
    volatile uint32 mss_pcr_bus_safety_err_stat_read;
    volatile uint32 mss_pcr_bus_safety_err_stat_writeresp;
    volatile uint32 mss_pcr2_bus_safety_ctrl;
    volatile uint32 mss_pcr2_bus_safety_fi;
    volatile uint32 mss_pcr2_bus_safety_err;
    volatile uint32 mss_pcr2_bus_safety_err_stat_data0;
    volatile uint32 mss_pcr2_bus_safety_err_stat_cmd;
    volatile uint32 mss_pcr2_bus_safety_err_stat_write;
    volatile uint32 mss_pcr2_bus_safety_err_stat_read;
    volatile uint32 mss_pcr2_bus_safety_err_stat_writeresp;
    volatile uint32 hsm_m_bus_safety_ctrl;
    volatile uint32 hsm_m_bus_safety_fi;
    volatile uint32 hsm_m_bus_safety_err;
    volatile uint32 hsm_m_bus_safety_err_stat_data0;
    volatile uint32 hsm_m_bus_safety_err_stat_cmd;
    volatile uint32 hsm_m_bus_safety_err_stat_write;
    volatile uint32 hsm_m_bus_safety_err_stat_read;
    volatile uint32 hsm_m_bus_safety_err_stat_writeresp;
    volatile uint32 hsm_s_bus_safety_ctrl;
    volatile uint32 hsm_s_bus_safety_fi;
    volatile uint32 hsm_s_bus_safety_err;
    volatile uint32 hsm_s_bus_safety_err_stat_data0;
    volatile uint32 hsm_s_bus_safety_err_stat_cmd;
    volatile uint32 hsm_s_bus_safety_err_stat_write;
    volatile uint32 hsm_s_bus_safety_err_stat_read;
    volatile uint32 hsm_s_bus_safety_err_stat_writeresp;
    volatile uint32 dap_r232_bus_safety_ctrl;
    volatile uint32 dap_r232_bus_safety_fi;
    volatile uint32 dap_r232_bus_safety_err;
    volatile uint32 dap_r232_bus_safety_err_stat_data0;
    volatile uint32 dap_r232_bus_safety_err_stat_cmd;
    volatile uint32 dap_r232_bus_safety_err_stat_write;
    volatile uint32 dap_r232_bus_safety_err_stat_read;
    volatile uint32 dap_r232_bus_safety_err_stat_writeresp;
    volatile uint32 mss_l2_a_bus_safety_ctrl;
    volatile uint32 mss_l2_a_bus_safety_fi;
    volatile uint32 mss_l2_a_bus_safety_err;
    volatile uint32 mss_l2_a_bus_safety_err_stat_data0;
    volatile uint32 mss_l2_a_bus_safety_err_stat_cmd;
    volatile uint32 mss_l2_a_bus_safety_err_stat_write;
    volatile uint32 mss_l2_a_bus_safety_err_stat_read;
    volatile uint32 mss_l2_a_bus_safety_err_stat_writeresp;
    volatile uint32 mss_l2_b_bus_safety_ctrl;
    volatile uint32 mss_l2_b_bus_safety_fi;
    volatile uint32 mss_l2_b_bus_safety_err;
    volatile uint32 mss_l2_b_bus_safety_err_stat_data0;
    volatile uint32 mss_l2_b_bus_safety_err_stat_cmd;
    volatile uint32 mss_l2_b_bus_safety_err_stat_write;
    volatile uint32 mss_l2_b_bus_safety_err_stat_read;
    volatile uint32 mss_l2_b_bus_safety_err_stat_writeresp;
    volatile uint32 mss_mbox_bus_safety_ctrl;
    volatile uint32 mss_mbox_bus_safety_fi;
    volatile uint32 mss_mbox_bus_safety_err;
    volatile uint32 mss_mbox_bus_safety_err_stat_data0;
    volatile uint32 mss_mbox_bus_safety_err_stat_cmd;
    volatile uint32 mss_mbox_bus_safety_err_stat_write;
    volatile uint32 mss_mbox_bus_safety_err_stat_read;
    volatile uint32 mss_mbox_bus_safety_err_stat_writeresp;
    volatile uint32 mss_swbuf_bus_safety_ctrl;
    volatile uint32 mss_swbuf_bus_safety_fi;
    volatile uint32 mss_swbuf_bus_safety_err;
    volatile uint32 mss_swbuf_bus_safety_err_stat_data0;
    volatile uint32 mss_swbuf_bus_safety_err_stat_cmd;
    volatile uint32 mss_swbuf_bus_safety_err_stat_write;
    volatile uint32 mss_swbuf_bus_safety_err_stat_read;
    volatile uint32 mss_swbuf_bus_safety_err_stat_writeresp;
    volatile uint32 mss_gpadc_bus_safety_ctrl;
    volatile uint32 mss_gpadc_bus_safety_fi;
    volatile uint32 mss_gpadc_bus_safety_err;
    volatile uint32 mss_gpadc_bus_safety_err_stat_data0;
    volatile uint32 mss_gpadc_bus_safety_err_stat_cmd;
    volatile uint32 mss_gpadc_bus_safety_err_stat_write;
    volatile uint32 mss_gpadc_bus_safety_err_stat_read;
    volatile uint32 mss_gpadc_bus_safety_err_stat_writeresp;
    volatile uint32 mss_bus_safety_sec_err_stat0;
    volatile uint32 mss_bus_safety_sec_err_stat1;
    volatile uint32 hw_reg0;
    volatile uint32 hw_reg1;
    volatile uint32 hw_reg2;
    volatile uint32 hw_reg3;
    volatile uint32 hw_reg4;
    volatile uint32 hw_reg5;
    volatile uint32 hw_reg6;
    volatile uint32 hw_reg7;
    volatile uint32 mss_dmm_bus_safety_ctrl;
    volatile uint32 mss_dmm_bus_safety_fi;
    volatile uint32 mss_dmm_bus_safety_err;
    volatile uint32 mss_dmm_bus_safety_err_stat_data0;
    volatile uint32 mss_dmm_bus_safety_err_stat_cmd;
    volatile uint32 mss_dmm_bus_safety_err_stat_write;
    volatile uint32 mss_dmm_bus_safety_err_stat_read;
    volatile uint32 mss_dmm_bus_safety_err_stat_writeresp;
    volatile uint32 mss_dmm_slv_bus_safety_ctrl;
    volatile uint32 mss_dmm_slv_bus_safety_fi;
    volatile uint32 mss_dmm_slv_bus_safety_err;
    volatile uint32 mss_dmm_slv_bus_safety_err_stat_data0;
    volatile uint32 mss_dmm_slv_bus_safety_err_stat_cmd;
    volatile uint32 mss_dmm_slv_bus_safety_err_stat_write;
    volatile uint32 mss_dmm_slv_bus_safety_err_stat_read;
    volatile uint32 mss_dmm_slv_bus_safety_err_stat_writeresp;
    volatile uint32 mss_to_mdo_bus_safety_ctrl;
    volatile uint32 mss_to_mdo_bus_safety_fi;
    volatile uint32 mss_to_mdo_bus_safety_err;
    volatile uint32 mss_to_mdo_bus_safety_err_stat_data0;
    volatile uint32 mss_to_mdo_bus_safety_err_stat_cmd;
    volatile uint32 mss_to_mdo_bus_safety_err_stat_write;
    volatile uint32 mss_to_mdo_bus_safety_err_stat_read;
    volatile uint32 mss_to_mdo_bus_safety_err_stat_writeresp;
    volatile uint32 mss_scrp_bus_safety_ctrl;
    volatile uint32 mss_scrp_bus_safety_fi;
    volatile uint32 mss_scrp_bus_safety_err;
    volatile uint32 mss_scrp_bus_safety_err_stat_data0;
    volatile uint32 mss_scrp_bus_safety_err_stat_cmd;
    volatile uint32 mss_scrp_bus_safety_err_stat_write;
    volatile uint32 mss_scrp_bus_safety_err_stat_read;
    volatile uint32 mss_scrp_bus_safety_err_stat_writeresp;
    volatile uint32 mss_cr5a_ahb_bus_safety_ctrl;
    volatile uint32 mss_cr5a_ahb_bus_safety_fi;
    volatile uint32 mss_cr5a_ahb_bus_safety_err;
    volatile uint32 mss_cr5a_ahb_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5a_ahb_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5a_ahb_bus_safety_err_stat_write;
    volatile uint32 mss_cr5a_ahb_bus_safety_err_stat_read;
    volatile uint32 mss_cr5a_ahb_bus_safety_err_stat_writeresp;
    volatile uint32 mss_cr5b_ahb_bus_safety_ctrl;
    volatile uint32 mss_cr5b_ahb_bus_safety_fi;
    volatile uint32 mss_cr5b_ahb_bus_safety_err;
    volatile uint32 mss_cr5b_ahb_bus_safety_err_stat_data0;
    volatile uint32 mss_cr5b_ahb_bus_safety_err_stat_cmd;
    volatile uint32 mss_cr5b_ahb_bus_safety_err_stat_write;
    volatile uint32 mss_cr5b_ahb_bus_safety_err_stat_read;
    volatile uint32 mss_cr5b_ahb_bus_safety_err_stat_writeresp;
    volatile uint32 dmm_ctrl_reg;
    volatile uint32 mss_cr5a_mbox_write_done;
    volatile uint32 mss_cr5a_mbox_read_req;
    volatile uint32 mss_cr5a_mbox_read_done;
    volatile uint32 mss_cr5b_mbox_write_done;
    volatile uint32 mss_cr5b_mbox_read_req;
    volatile uint32 mss_cr5b_mbox_read_done;
    volatile uint32 mss_pbist_key_rst;
    volatile uint32 mss_pbist_reg0;
    volatile uint32 mss_pbist_reg1;
    volatile uint32 mss_pbist_reg2;
    volatile uint32 mss_qspi_config;
    volatile uint32 mss_stc_control;
    volatile uint32 mss_cti_trig_sel;
    volatile uint32 mss_dbgss_cti_trig_sel;
    volatile uint32 mss_boot_info_reg0;
    volatile uint32 mss_boot_info_reg1;
    volatile uint32 mss_boot_info_reg2;
    volatile uint32 mss_boot_info_reg3;
    volatile uint32 mss_boot_info_reg4;
    volatile uint32 mss_boot_info_reg5;
    volatile uint32 mss_boot_info_reg6;
    volatile uint32 mss_boot_info_reg7;
    volatile uint32 mss_tptc_eccaggr_clk_cntrl;
    volatile uint32 mss_periph_erragg_mask0;
    volatile uint32 mss_periph_erragg_status0;
    volatile uint32 mss_periph_erragg_status_raw0;
    volatile uint32 mss_periph_erragg_mask1;
    volatile uint32 mss_periph_erragg_status1;
    volatile uint32 mss_periph_erragg_status_raw1;
    volatile uint32 mss_dmm_event0_reg;
    volatile uint32 mss_dmm_event1_reg;
    volatile uint32 mss_dmm_event2_reg;
    volatile uint32 mss_dmm_event3_reg;
    volatile uint32 mss_dmm_event4_reg;
    volatile uint32 mss_dmm_event5_reg;
    volatile uint32 mss_dmm_event6_reg;
    volatile uint32 mss_dmm_event7_reg;
    volatile uint32 mss_dmm_event8_reg;
    volatile uint32 mss_dmm_event9_reg;
    volatile uint32 mss_dmm_event10_reg;
    volatile uint32 mss_dmm_event11_reg;
    volatile uint32 mss_dmm_event12_reg;
    volatile uint32 mss_dmm_event13_reg;
    volatile uint32 mss_dmm_event14_reg;
    volatile uint32 mss_dmm_event15_reg;
    volatile uint32 mss_tptc_boundary_cfg;
    volatile uint32 mss_tptc_xid_reorder_cfg;
    volatile uint32 gpadc_ctrl;
    volatile uint32 hw_sync_fe_ctrl;
    volatile uint32 debugss_csetb_flush;
    volatile uint32 analog_wu_status_reg_polarity_inv;
    volatile uint32 analog_clk_status_reg_polarity_inv;
    volatile uint32 analog_wu_status_reg_grp1_mask;
    volatile uint32 analog_clk_status_reg_grp1_mask;
    volatile uint32 analog_wu_status_reg_grp2_mask;
    volatile uint32 analog_clk_status_reg_grp2_mask;
    volatile uint32 nerror_mask;
    volatile uint8  resv_2048[288];
    volatile uint32 r5_control;
    volatile uint32 r5_rom_eclipse;
    volatile uint32 r5_corea_halt;
    volatile uint32 r5_coreb_halt;
    volatile uint32 r5_status_reg;
    volatile uint8  resv_4048[1980];
    volatile uint32 hw_spare_rw0;
    volatile uint32 hw_spare_rw1;
    volatile uint32 hw_spare_rw2;
    volatile uint32 hw_spare_rw3;
    volatile uint32 hw_spare_ro0;
    volatile uint32 hw_spare_ro1;
    volatile uint32 hw_spare_ro2;
    volatile uint32 hw_spare_ro3;
    volatile uint32 mss_cr5a_b_mbox_read_done_ack;
    volatile uint32 hw_spare_rec;
    volatile uint8  resv_4104[16];
    volatile uint32 lock0_kick0;
    volatile uint32 lock0_kick1;
    volatile uint32 intr_raw_status;
    volatile uint32 intr_enabled_status_clear;
    volatile uint32 intr_enable;
    volatile uint32 intr_enable_clear;
    volatile uint32 eoi;
    volatile uint32 fault_address;
    volatile uint32 fault_type_status;
    volatile uint32 fault_attr_status;
    volatile uint32 fault_clear;
} Cdd_Dma_Csl_Mss_CtrlRegs;
/**
 * \brief EDMA interrupt configuration object. The object is passed to the
 *        #CDD_EDMA_registerIntr() function. This is held by the driver till the
 *        #CDD_EDMA_unregisterIntr() function is called with this obect. The
 *        application should not modify this object in between.
 *
 */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief   Clear a PaRAM Set .
 *
 *  \param   paramEntry               Parameter RAM set to be cleared.
 *
 */
void CDD_EDMA_lld_ccParamEntry_Init(CDD_EDMACCEDMACCPaRAMEntry *paramEntry);

/**
 * \brief  Enable channel to Shadow region mapping
 *
 * This API allocates DMA/QDMA channels or TCCs, and the same resources are
 * enabled in the shadow region specific register (DRAE/DRAEH/QRAE).
 * Here only one shadow region is used since, there is only one Master.
 *
 *  \param   baseAddr     Memory address of the EDMA instance used.\n
 *
 *  \param   regionId     Region id to be used.
 *                        Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   chType       (DMA/QDMA) Channel
 *                        For Example: For DMA it is,
 *                        CDD_EDMA_CHANNEL_TYPE_DMA.\n
 *
 *  \param   chNum       Allocated channel number.
 *                       Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *                       Valid values are 0 to CDD_EDMA_NUM_QDMACH-1 for QDMA \n
 *  chType can have values
 *        CDD_EDMA_CHANNEL_TYPE_DMA\n
 *        CDD_EDMA_CHANNEL_TYPE_QDMA
 *
 */
void CDD_EDMA_lld_enableChInShadowRegRegion(uint32 baseAddr, uint32 regionId, uint32 chType, uint32 chNum);

/**
 * \brief  Disable channel to Shadow region mapping
 *
 * This API deallocates DMA/QDMA channels or TCCs, and the same resources are
 * disabled in the shadow region specific register (DRAE/DRAEH/QRAE).
 * Here only one shadow region is used since, there is only one Master.
 *
 * \param   baseAddr   Memory address of the EDMA instance used.\n
 *
 * \param   regionId     Region id to be used.
 *                        Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 * \param   chType      (DMA/QDMA) Channel
 *
 * \param   chNum       Allocated channel number.
 *                      Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *                      Valid values are 0 to CDD_EDMA_NUM_QDMACH-1 for QDMA \n
 *
 *
 *  chType can have values
 *        CDD_EDMA_CHANNEL_TYPE_DMA\n
 *        CDD_EDMA_CHANNEL_TYPE_QDMA
 *
 */
void CDD_EDMA_lld_disableChInShadowRegRegion(uint32 baseAddr, uint32 regionId, uint32 chType, uint32 chNum);

/**
 *  \brief   This function maps DMA channel to any of the PaRAM sets
 *           in the PaRAM memory map.
 *
 *  \param   baseAddr   Memory address of the EDMA instance used.
 *
 *  \param   channel   The DMA channel number required to be mapped.
 *
 *  \param   paramSet  It specifies the paramSet to which DMA channel
 *                     required to be mapped.
 *                     Valid values are 0 to CDD_EDMA_NUM_PARAMSETS-1
 *
 */
void CDD_EDMA_lld_channelToParamMap(uint32 baseAddr, uint32 channel, uint32 paramSet);

/**
 *  \brief  Map channel to Event Queue
 *
 *  This API maps DMA/QDMA channels to the Event Queue
 *
 *  \param  baseAddr    Memory address of the EDMA instance used.\n
 *
 *  \param  chType     (DMA/QDMA) Channel
 *                     For Example: For QDMA it is
 *                     CDD_EDMA_CHANNEL_TYPE_QDMA.\n
 *
 *  \param   chNum     Allocated channel number.
 *                     Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *                     Valid values are 0 to CDD_EDMA_NUM_QDMACH-1 for QDMA \n
 *
 *  \param  evtQNum    Event Queue Number to which the channel
 *                     will be mapped (valid only for the
 *                     Master Channel (DMA/QDMA) request).\n
 *
 *  chtype can have values
 *        CDD_EDMA_CHANNEL_TYPE_DMA\n
 *        CDD_EDMA_CHANNEL_TYPE_QDMA
 *
 */
void CDD_EDMA_lld_mapChToEvtQ(uint32 baseAddr, uint32 chType, uint32 chNum, uint32 evtQNum);

/**
 *  \brief  Remove Mapping of channel to Event Queue
 *
 *  This API Unmaps DMA/QDMA channels from the Event Queue allocated
 *
 *  \param  baseAddr    Memory address of the EDMA instance used.\n
 *
 *  \param  chType     (DMA/QDMA) Channel
 *                     For Example: For DMA it is
 *                     CDD_EDMA_CHANNEL_TYPE_DMA.\n
 *
 *  \param   chNum     Allocated channel number.
 *                     Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *                     Valid values are 0 to CDD_EDMA_NUM_QDMACH-1 for QDMA \n
 *
 *  chtype can have values
 *        CDD_EDMA_CHANNEL_TYPE_DMA\n
 *        CDD_EDMA_CHANNEL_TYPE_QDMA
 *
 */
void CDD_EDMA_lld_unmapChToEvtQ(uint32 baseAddr, uint32 chType, uint32 chNum);

/**
 *  \brief  Enables the user to map a QDMA channel to PaRAM set
 *          This API Needs to be called before programming the paRAM sets for
 *          the QDMA Channels.Application needs to maitain the paRAMId
 *          provided by this API.This paRAMId is used to set paRAM and get
 *          paRAM. Refer corresponding API's for more details.
 *
 *  \param  baseAddr                  Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                    Allocated channel number.
 *                                    Valid values are 0 to CDD_EDMA_NUM_QDMACH-1 for QDMA \n
 *
 *  \param  paRAMId                  PaRAM Id to which the QDMA channel will be
 *                                   mapped to.
 *                                   mapped to.
 *
 *  Note : The PaRAMId requested must be greater than 32(CDD_EDMA_NUM_DMACH).
 *         and lesser than CDD_EDMA_NUM_DMACH + chNum  Because, the first
 *         32 PaRAM's are directly mapped to first 32 DMA channels and (32 - 38)
 *         for QDMA Channels. (32 - 38) is assigned by driver in this API.
 *
 */
void CDD_EDMA_lld_mapQdmaChToPaRAM(uint32 baseAddr, uint32 chNum, const uint32 *paRAMId);

/**
 *  \brief   Enables the user to Clear any missed event
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   chNum                  Allocated channel number.\n
 *                                  Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 */
void CDD_EDMA_lld_clrMissEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum);

/**
 *  \brief   Enables the user to Clear any Channel controller Errors
 *
 *  \param   baseAddr              Memory address of the EDMA instance used.\n
 *
 *  \param   flags                Masks to be passed.\n
 *
 *  flags can have values:
 *
 *  CDD_EDMACC_CLR_TCCERR            Clears the TCCERR bit in the EDMACC
 *                                ERR Reg\n
 *  CDD_EDMACC_CLR_QTHRQ0            Queue threshold error clear for queue 0.\n
 *  CDD_EDMACC_CLR_QTHRQ1            Queue threshold error clear for queue 1.
 *
 */
void CDD_EDMA_lld_clrCCErr(uint32 baseAddr, uint32 flags);

/**
 *  \brief   Enables the user to Set an event. This API helps user to manually
 *           set events to initiate DMA transfer requests.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.\n
 *
 *  \param   chNum                  Allocated channel number.
 *                                  Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  Note :   This API is generally used during Manual transfers.\n
 */
void CDD_EDMA_lld_setEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum);

/**
 *  \brief   Enables the user to Clear an event.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   chNum                  Allocated channel number.\n
 *                                  Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  Note :   This API is generally used during Manual transfers.\n
 */
void CDD_EDMA_lld_clrEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum);

/**
 *  \brief   Enables the user to enable an DMA event.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   chNum                  Allocated channel number.
 *                                  Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  Note :   Writes of 1 to the bits in EESR sets the corresponding event
 *           bits in EER. This is generally used for Event Based transfers.\n
 */
void CDD_EDMA_lld_enableDmaEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum);

/**
 *  \brief   Enables the user to Disable an DMA event.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   chNum                  Allocated channel number.
 *                                  Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  Note :   Writes of 1 to the bits in EECR clear the corresponding event bits
 *           in EER; writes of 0 have no effect.. This is generally used for
 *           Event Based transfers.\n
 */
void CDD_EDMA_lld_disableDmaEvtRegion(uint32 baseAddr, uint32 regionId, uint32 chNum);

/**
 *  \brief   This function returns interrupts status of those events
 *           which is less than 32.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 * \return   Interrupt status register value
 *
 **/
uint32 CDD_EDMA_lld_getIntrStatusRegion(uint32 baseAddr, uint32 regionId);

/**
 *  \brief   Enables the user to enable the transfer completion interrupt
 *           generation by the EDMACC for all DMA/QDMA channels.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   chNum                  Allocated channel number.
 *                                  Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  Note :   To set any interrupt bit in IER, a 1 must be written to the
 *           corresponding interrupt bit in the interrupt enable set register.
 */
void CDD_EDMA_lld_enableEvtIntrRegion(uint32 baseAddr, uint32 regionId, uint32 chNum);

/**
 *  \brief   Enables the user to clear CC interrupts
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   chNum                  Allocated channel number.
 *                                  Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  Note :   Writes of 1 to the bits in IECR clear the corresponding interrupt
 *           bits in the interrupt enable registers (IER); writes of 0 have
 *           no effect.\n
 */
void CDD_EDMA_lld_disableEvtIntrRegion(uint32 baseAddr, uint32 regionId, uint32 chNum);

/**
 *  \brief   Enables the user to Clear an Interrupt.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.
 *
 *  \param   regionId               Region id to be used.
 *                                  Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param   value                  Value to be set to clear the Interrupt
 *                                  Status.
 *
 */
void CDD_EDMA_lld_clrIntrRegion(uint32 baseAddr, uint32 regionId, uint32 value);

/**
 *  \brief   Retrieve existing PaRAM set associated with specified logical
 *           channel (DMA/Link).
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   paRAMId                paRAMset ID whose parameter set is
 *                                  requested.
 *                                  Valid values are 0 to CDD_EDMA_NUM_PARAMSETS-1\n
 *
 *  \param   currPaRAM              User gets the existing PaRAM here.\n
 *
 */
void CDD_EDMA_lld_getPaRAM(uint32 baseAddr, uint32 paRAMId, CDD_EDMACCEDMACCPaRAMEntry *currPaRAM);

/**
 * \brief   Copy the user specified PaRAM Set onto the PaRAM Set associated
 *          with the logical channel (DMA/Link).
 *
 * This API takes a PaRAM Set as input and copies it onto the actual PaRAM Set
 * associated with the logical channel. OPT field of the PaRAM Set is written
 * first and the CCNT field is written last.
 *
 *
 * \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 * \param   paRAMId                paRAMset ID whose parameter set has to be
 *                                 updated
 *                                 Valid values are 0 to CDD_EDMA_NUM_PARAMSETS-1
 *
 * \param   newPaRAM               Parameter RAM set to be copied onto existing
 *                                 PaRAM.\n
 *
 */
void CDD_EDMA_lld_setPaRAM(uint32 baseAddr, uint32 paRAMId, const CDD_EDMACCEDMACCPaRAMEntry *newPaRAM);

/**
 *  \brief Request a DMA/QDMA/Link channel.
 *
 *  Each channel (DMA/QDMA/Link) must be requested  before initiating a DMA
 *  transfer on that channel.
 *
 *  This API is used to allocate a logical channel (DMA/QDMA/Link) along with
 *  the associated resources. For DMA and QDMA channels, TCC and PaRAM Set are
 *  also allocated along with the requested channel.
 *
 *  User can request a specific logical channel by passing the channel number
 *  in 'chNum'.
 *
 *  For DMA/QDMA channels, after allocating all the EDMA resources, this API
 *  sets the TCC field of the OPT PaRAM Word with the allocated TCC. It also
 *  sets the event queue for the channel allocated. The event queue needs to
 *  be specified by the user.
 *
 *  For DMA channel, it also sets the DCHMAP register.
 *
 *  For QDMA channel, it sets the QCHMAP register and CCNT as trigger word and
 *  enables the QDMA channel by writing to the QEESR register.
 *
 *  \param  baseAddr                  Memory address of the EDMA instance used.\n
 *
 *  \param   regionId                 Region id to be used.
 *                                    Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param  chType                   (DMA/QDMA) Channel
 *                                    For Example: For DMA it is
 *                                    CDD_EDMA_CHANNEL_TYPE_DMA.\n
 *
 *  \param  chNum                    This is the channel number requested for a
 *                                   particular event.
 *                                   Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *                                   Valid values are 0 to CDD_EDMA_NUM_QDMACH-1 for QDMA \n
 *
 *  \param  tccNum                   The tcc number on which the
 *                                   completion/error interrupt is generated.
 *                                   Not used if user requested for a Link
 *                                   channel.\n
 *
 *  \param  paramId                  The param number currosponding to the
 *                                   DMA/QDMA channel.\n
 *
 *  \param  evtQNum                  Event Queue Number to which the channel
 *                                   will be mapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  \return  TRUE if parameters are valid, else FALSE
 */
uint32 CDD_EDMA_lld_configureChannelRegion(uint32 baseAddr, uint32 regionId, uint32 chType, uint32 chNum, uint32 tccNum,
                                           uint32 paramId, uint32 evtQNum);

/**
 *  \brief    Free the specified channel (DMA/QDMA/Link) and its associated
 *            resources (PaRAM Set, TCC etc) and removes various mappings.
 *
 *  For Link channels, this API only frees the associated PaRAM Set.
 *
 *  For DMA/QDMA channels, it does the following operations:
 *  1) Disable any ongoing transfer on the channel,\n
 *  2) Remove the channel to Event Queue mapping,\n
 *  3) For DMA channels, clear the DCHMAP register, if available\n
 *  4) For QDMA channels, clear the QCHMAP register,\n
 *  5) Frees the DMA/QDMA channel in the end.\n
 *
 *  \param  baseAddr                  Memory address of the EDMA instance used.\n
 *
 *  \param   regionId                 Region id to be used.
 *                                    Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param  chType                    (DMA/QDMA) Channel
 *                                      For Example: For QDMA it is,
 *                                      CDD_EDMA_CHANNEL_TYPE_QDMA.\n
 *
 *  \param  chNum                    This is the channel number requested for a
 *                                   particular event.
 *                                   Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *                                   Valid values are 0 to CDD_EDMA_NUM_QDMACH-1 for QDMA \n
 *
 *  \param  trigMode                 Mode of triggering start of transfer.\n
 *
 *  \param  tccNum                   The channel number on which the
 *                                   completion/error interrupt is generated.
 *                                   Not used if user requested for a Link
 *                                   channel.\n
 *
 *  \param  evtQNum                  Event Queue Number to which the channel
 *                                   will be unmapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  trigMode can have values:
 *        CDD_EDMA_TRIG_MODE_MANUAL\n
 *        CDD_EDMA_TRIG_MODE_QDMA\n
 *        CDD_EDMA_TRIG_MODE_EVENT
 *
 *  \return  TRUE if parameters are valid else return FALSE
 */
uint32 CDD_EDMA_lld_freeChannelRegion(uint32 baseAddr, uint32 regionId, uint32 chType, uint32 chNum, uint32 trigMode,
                                      uint32 tccNum, uint32 evtQNum);

/**
 *  \brief    Start EDMA transfer on the specified channel.
 *
 *  There are multiple ways to trigger an EDMA transfer. The triggering mode
 *  option allows choosing from the available triggering modes: Event,
 *  Manual or QDMA.
 *
 *  In event triggered, a peripheral or an externally generated event triggers
 *  the transfer. This API clears the Event and Event Miss Register and then
 *  enables the DMA channel by writing to the EESR.
 *
 *  In manual triggered mode, CPU manually triggers a transfer by writing a 1
 *  in the Event Set Register ESR. This API writes to the ESR to start the
 *  transfer.
 *
 *  In QDMA triggered mode, a QDMA transfer is triggered when a CPU (or other
 *  EDMA programmer) writes to the trigger word of the QDMA channel PaRAM set
 *  (auto-triggered) or when the EDMACC performs a link update on a PaRAM set
 *  that has been mapped to a QDMA channel (link triggered). This API enables
 *  the QDMA channel by writing to the QEESR register.
 *
 *  \param  baseAddr         Memory address of the EDMA instance used.\n
 *
 *  \param   regionId       Region id to be used.
 *                           Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param  chNum           Channel being used to enable transfer.
 *                          Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  \param  trigMode        Mode of triggering start of transfer (Manual,
 *                          QDMA or Event).\n
 *
 *  trigMode can have values:
 *        CDD_EDMA_TRIG_MODE_MANUAL\n
 *        CDD_EDMA_TRIG_MODE_QDMA\n
 *        CDD_EDMA_TRIG_MODE_EVENT\n
 *
 *  \return  retVal         TRUE or FALSE depending on the param passed.\n
 *
 */
uint32 CDD_EDMA_lld_enableTransferRegion(uint32 baseAddr, uint32 regionId, uint32 chNum, uint32 trigMode);

/**
 *  \brief   Disable DMA transfer on the specified channel
 *
 *  There are multiple ways by which an EDMA transfer could be triggered.
 *  The triggering mode option allows choosing from the available triggering
 *  modes.
 *
 *  To disable a channel which was previously triggered in manual mode,
 *  this API clears the Secondary Event Register and Event Miss Register,
 *  if set, for the specific DMA channel.
 *
 *  To disable a channel which was previously triggered in QDMA mode, this
 *  API clears the QDMA Event Enable Register, for the specific QDMA channel.
 *
 *  To disable a channel which was previously triggered in event mode, this API
 *  clears the Event Enable Register, Event Register, Secondary Event Register
 *  and Event Miss Register, if set, for the specific DMA channel.
 *
 *
 *  \param  baseAddr         Memory address of the EDMA instance used.\n
 *
 *  \param   regionId       Region id to be used.
 *                          Valid values are 0 to CDD_EDMA_NUM_REGIONS-1 \n
 *
 *  \param  chNum           Channel being used to enable transfer.
 *                          Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  \param  trigMode        Mode of triggering start of transfer (Manual,
 *                          QDMA or Event).\n
 *  \return  retVal         TRUE or FALSE depending on the param passed.\n
 *
 */
uint32 CDD_EDMA_lld_disableTransferRegion(uint32 baseAddr, uint32 regionId, uint32 chNum, uint32 trigMode);

/**
 *  \brief   This function returns interrupt status of those events
 *           which are greater than 32.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId                Region id to be used.\n
 *
 *  \return  value                   Status of the Interrupt Pending High Register
 *
 **/
uint32 CDD_EDMA_lld_intrStatusHighGetRegion(uint32 baseAddr, uint32 regionId);

/**
 *  \brief   This function reads interrupt status.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   regionId                Region id to be used.\n
 *
 *  \param   tccNum                  The channel number on which the
 *                                   completion/error interrupt is generated.
 *
 *  \return  value                   Status of the Interrupt Pending register
 *
 **/
uint32 CDD_EDMA_lld_readIntrStatusRegion(uint32 baseAddr, uint32 regionId, uint32 tccNum);

/**
 *  \brief   This function returns status of those events
 *           which are less than 32.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 * \return   value                   Event pending status register value
 *
 **/
uint32 CDD_EDMA_lld_getEventStatus(uint32 baseAddr);

/**
 *  \brief   This function returns status of those events
 *           which are greater than 32.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \return  value                   Status of the Event Pending High Register
 *
 **/
uint32 CDD_EDMA_lld_getEventStatusHigh(uint32 baseAddr);

/**
 *  \brief   This function reads Event pending status.
 *
 *  \param   baseAddr                Memory address of the EDMA instance used.\n
 *
 *  \param   chNum                   Channel being used for transfer.
 *                                   Valid values are 0 to CDD_EDMA_NUM_DMACH-1 for DMA
 *
 *  \return  value                   Status of the Event Pending register
 *
 **/
uint32 CDD_EDMA_lld_readEventStatusRegion(uint32 baseAddr, uint32 chNum);

/**
 *  \brief  Chain the two specified channels
 *
 *  This API is used to chain a DMA channel to a previously allocated DMA/QDMA
 *  channel
 *
 *  Chaining is different from Linking. The EDMA link feature reloads the
 *  current channel parameter set with the linked parameter set. The EDMA
 *  chaining feature does not modify or update any channel parameter set;
 *  it provides a synchronization event (or trigger) to the chained DMA channel,
 *  as soon as the transfer (final or intermediate) completes on the main
 *  DMA/QDMA channel.
 *
 *  \param  baseAddr         Memory address of the EDMA instance used.\n
 *
 *  \param  paRAMId1        PaRAM set ID of physical channel1 to which
 *                          particular paRAM set will be chained
 *                          or
 *                          PaRAM set ID in case another PaRAM set is being
 *                          chained to this PaRAM set
 *
 *  \param  chId2           DMA channel which needs to be chained to
 *                          the first DMA/QDMA channel.
 *
 *  \param   chainOptions   combination of the following masks which control
 *                          individual PaRAM OPT fields related to
 *                          intermediate/final completion chaining and
 *                          intermediate/final completion interrupt :
 *                            - CDD_EDMA_OPT_TCCHEN_MASK
 *                            - CDD_EDMA_OPT_ITCCHEN_MASK
 *                            - CDD_EDMA_OPT_TCINTEN_MASK
 *                            - CDD_EDMA_OPT_ITCINTEN_MASK
 *                          e.g to enable final completion chaining and enable
 *                          interrupt only for intermediate completion,
 *                          set chainOptions as :
 *                          CDD_EDMA_OPT_TCCHEN_MASK | CDD_EDMA_OPT_ITCINTEN_MASK
 *
 */
void CDD_EDMA_lld_chainChannel(uint32 baseAddr, uint32 paRAMId1, uint32 chId2, uint32 chainOptions);

/**
 *  \brief  Link two channels.
 *
 *  This API is used to link two previously allocated logical (DMA/QDMA/Link)
 *  channels.
 *
 *  It sets the Link field of the PaRAM set associated with first
 *  channel (chId1) to point it to the PaRAM set associated with second
 *  channel (chId2).
 *
 *  It also sets the TCC field of PaRAM set of second channel to the
 *  same as that of the first channel.
 *
 *  \param  baseAddr         Memory address of the EDMA instance used.\n
 *
 *  \param  paRAMId1        PaRAM set ID of physical channel1 to which
 *                          particular paRAM set will be linked
 *                          or
 *                          PaRAM set ID in case another PaRAM set is being
 *                          linked to this PaRAM set
 *
 *  \param  paRAMId2        PaRAM set ID which is linked to
 *                          channel with parameter ID paRAMId1
 *
 *                          After the transfer based on the PaRAM set
 *                          of channel1 is over, the PaRAM set paRAMId2 will
 *                          be copied to the PaRAM set of channel1 and
 *                          transfer will resume.
 *                          For DMA channels, another sync event is
 *                          required to initiate the transfer on the
 *                          Link channel.
 *
 */
void CDD_EDMA_lld_linkChannel(uint32 baseAddr, uint32 paRAMId1, uint32 paRAMId2);

/**
 *  \brief  This function initializes the EDMA instance
 *
 *  \param  hEdma      HandleList to the EDMA instance used
 */
void CDD_EDMA_lld_init(Cdd_Dma_ConfigType *hEdmaList);

/**
 *  \brief  This function Deinitializes the EDMA instance
 *
 *  \param  hEdma      HandleList to the EDMA instance used
 */
void CDD_EDMA_lld_deInit(Cdd_Dma_ConfigType *hEdmaList);
/**
 *  \brief  Function to register callback function for a TCC
 *
 *  \pre    #CDD_EDMA_open() has to be called first
 *
 *  \param  hEdma      #Cdd_EDMALLD_Handle returned from #CDD_EDMA_open()
 *  \param appdata     #data associated with it
 *  \param callback    #registered callback which will be called on interupt
 *
 *  \return #E_OK if started successfully; else error on failure
 *
 *  \sa     #CDD_EDMA_open()
 */

Std_ReturnType CDD_EDMA_lld_registerIntr(Cdd_Dma_Handler *hEdma, void *appdata, Cdd_Edma_EventCallback callback,
                                         uint32 handleId);
/**
 *  \brief  Function to unregister callback function for a TCC
 *
 *  \pre    #CDD_EDMA_registerIntr() has to be called first
 *
 *  \param  hEdma      #Cdd_EDMALLD_Handle returned from #CDD_EDMA_open()
 *
 *
 *  \return #E_OK if started successfully; else error on failure
 *
 *  \sa     #CDD_EDMA_open()
 *  \sa     #CDD_EDMA_registerIntr()
 */
sint32         CDD_EDMA_lld_unregisterIntr(Cdd_Dma_Handler *hEdma);
/**
 *  \brief  Function which will be called on the interrupt comes, will act as master ISR function
 *
 *
 *  \return #void
 *
 *  \sa     #CDD_EDMA_open()
 */
void           CDD_EDMA_TransferCompletion_MasterIsr(void);
/**
 *  \brief  Function used to get the dummy TCC in case of chaining
 *
 *
 *  \return #void
 *
 *  \sa     #CDD_EDMA_open()
 */
void           CDD_EDMA_lld_GetTcc(uint32 handleId, uint32 channelIdx);
/**
 *  \brief  Function used to have channel configure region in case of chaining for multiple channels
 *
 *
 *  \return #void
 *
 *  \sa     #CDD_EDMA_open()
 */
void           CDD_EDMA_lld_chainingConfigureChannelRegion(Cdd_Dma_Handler *hEdma, uint32 handleId);
/**
 *  \brief  Function used for convertion of address from virtaul to physical address
 *
 *
 *  \return #uint64 - phy address
 *
 *  \sa     #CDD_EDMA_open()
 */
uint64         Cdd_Dma_Soc_VirtToPhy(void *virtAddr);
/**
 *  \brief  Function used for unregistering callback associated with the particular handle
 *
 *
 *  \return #void
 *
 *  \sa     #CDD_EDMA_open()
 */
void           Cdd_Dma_CbkUnregister(uint32 handleId);
/**
 *  \brief  Function used for register read back
 *
 *
 *  \return #void
 *
 */
void           Cdd_Dma_ReadBack(Cdd_Dma_RegisterReadbackType *RegRbPtr, uint32 baseAddr);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef CDD_DMA_EDMA_V0_H_ */

/** @} */
