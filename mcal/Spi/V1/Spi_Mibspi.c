/* ======================================================================
 *   Copyright (c) 2023-2024 Texas Instruments Incorporated
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

/**
 *  \file     Spi_Mibspi.c
 *
 *  \brief    This file contains SPI MCAL driver
 *
 */
/*  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Spi_Mibspi.c
 *    Component:  AM273X MCAL Driver
 *       Module:  SPI Driver/Handler
 *    Generator:  None
 *
 *  Description: This component provides services for initialization and control of the
 *microcontroller internal MIBSPI .
 *********************************************************************************************************************/

#define SPI_DLC_SOURCE 1

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Irq.h"
#include "hw_Mibspi.h"
#include "Spi_Priv.h"

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

#include "hw_ctrl_core.h"

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"

#include "hal_stdtypes.h"
#include "SchM_Spi.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* versions of all included header files shall be checked */
#if ((SPI_SW_MAJOR_VERSION != (10U)) || (SPI_SW_MINOR_VERSION != (1U)))
#error "Spi :Software Version Numbers are inconsistent!"
#endif
#if ((SPI_IRQ_MAJOR_VERSION != (10U)) || (SPI_IRQ_MINOR_VERSION != (1U)))
#error "Spi_Irq: Source and Header file are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define SPI_DLC_MAXOPT (2U)
#define SPI_DLC_STDOPT (0U)
#define SPI_DLC_RAMOPT (1U)

#define SPI_ANALOG_LOOPBACK_MASK  (0x00000A02U)
#define SPI_DIGITAL_LOOPBACK_MASK (0x00000A00U)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

/* we have to schedule one transfer group */
static VAR(Spi_DlcEventType, SPI_VAR_NOINIT) Spi_DlcEvent_t[SPI_DLC_MAXHWUNIT];

static VAR(Spi_DlcFunctionType, SPI_VAR_NOINIT) Spi_DlcOptionSelect[SPI_DLC_MAXOPT];

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_INIT_UNSPECIFIED

#include "Spi_MemMap.h"

/* for hardware unit mapping */
static VAR(Spi_HWUnitMapType, SPI_VAR_INIT) Spi_HWUnitMap_at[SPI_DLC_MAXHWUNIT] = {
    {(Spi_RegisterPtrType)NULL_PTR, (Spi_RamBufferPtrType)NULL_PTR, (Spi_HWUnitPropertyPtrType)NULL_PTR},
    {(Spi_RegisterPtrType)NULL_PTR, (Spi_RamBufferPtrType)NULL_PTR, (Spi_HWUnitPropertyPtrType)NULL_PTR},
    {(Spi_RegisterPtrType)NULL_PTR, (Spi_RamBufferPtrType)NULL_PTR, (Spi_HWUnitPropertyPtrType)NULL_PTR},
    {(Spi_RegisterPtrType)NULL_PTR, (Spi_RamBufferPtrType)NULL_PTR, (Spi_HWUnitPropertyPtrType)NULL_PTR},
    {(Spi_RegisterPtrType)NULL_PTR, (Spi_RamBufferPtrType)NULL_PTR, (Spi_HWUnitPropertyPtrType)NULL_PTR}};

#define SPI_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define SPI_START_SEC_CODE
#include "Spi_MemMap.h"

/* interface functions  are part of the Spi_Dlc.h */

/* derived functions with option Ram, the macro Spi_Dlc(Ram,Init) expands to Spi_DlcRamInit  */
static FUNC(void, SPI_CODE) Spi_dlcRamInit(uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_dlcRamClose(uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_dlcRamFillData(uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_dlcRamDrainData(uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_dlcRamTriggerData(uint32 HwUnit_u32);
/* functions of master class */
static FUNC(void, SPI_CODE) Spi_dlcConsumeEvent(uint32 HwUnit_u32);
static FUNC(void, SPI_CODE) Spi_dlcTransmit(uint32 HwUnit_u32);
static FUNC(uint16, SPI_CODE) Spi_dlcRamTransmit(uint32 HwUnit_u32);

static FUNC(Std_ReturnType, SPI_CODE)
    Spi_dlcSwitchChannel(P2VAR(volatile uint16, AUTOMATIC, SPI_VAR) Ctrl_pt,
                         P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) Ev_pt, Spi_DlcTxRxDefType Dir_t);

static FUNC(void, SPI_CODE) Spi_dlcError(uint32 HwUnit_u32);

static FUNC(Std_ReturnType, SPI_CODE)
    Spi_filldata(uint16 TgLen_u16, uint8 *const                                                         ChIDTx_u8,
                 P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) ChBufTx_pt, Spi_RamBufferPtrType MRam_pt,
                 uint16 *const TxPos_u16, uint16 *DataLoc_u16, uint16 *const DefData_u16, uint32 *const HwUnit_u32,
                 Spi_DlcEventPtrType DlcEv_pt);

static FUNC(void, SPI_CODE) Spi_checkTxTransferGroup(uint16 *TgLen_u16, Spi_DlcEventPtrType DlcEv_pt,
                                                     Spi_RamBufferPtrType MRam_pt, uint32 *HwUnit_u32);

static FUNC(void, SPI_CODE)
    Spi_check32bitMode(uint16 *const TgLen_u16, Spi_RamBufferPtrType MRam_pt, uint8 ChIDTx_u8, uint16 *DataLoc_u16,
                       P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) ChBufTx_pt, uint16 TxPos_u16);

static FUNC(void, SPI_CODE)
    Spi_checkRxTransferGroup(Spi_DlcEventPtrType DlcEv_pt, Spi_RamBufferPtrType MRam_pt, uint32 *HwUnit_u32);

static FUNC(Std_ReturnType, SPI_CODE)
    Spi_readyToDrain(Spi_DlcEventPtrType DlcEv_pt, uint32 *const HwUnit_u32, Spi_RamBufferPtrType MRam_pt,
                     P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) ChBufRx_pt, uint16 *RxPos_u16,
                     uint16 *TgLen_u16, uint8 *const ChIDRx_u8);

static FUNC(void, SPI_CODE) Spi_checkTxRxState(Spi_DlcEventPtrType DlcEv_pt, uint8 *const Ram_u8, uint32 *HwUnit_u32);

FUNC(void, SPI_CODE) Spi_checkNumberOfJobPending(Spi_DlcEventPtrType DlcEv_pt);

static FUNC(void, SPI_CODE) Spi_checkTxTransferGroup(uint16 *TgLen_u16, Spi_DlcEventPtrType DlcEv_pt,
                                                     Spi_RamBufferPtrType MRam_pt, uint32 *HwUnit_u32);
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

static uint32 MibSPI_GetIntVectReg(uint32 HwUnit_u32)
{
    Spi_RegisterPtrType MReg_pt  = (Spi_RegisterPtrType)NULL_PTR;
    uint32              intvect0 = 0U;

    MReg_pt = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;
    if (MReg_pt != NULL_PTR)
    {
        intvect0 = MReg_pt->Spi_TGINTVECT[0];
    }

    return (intvect0);
}

static void MibSPI_ClearFlagReg(uint32 HwUnit_u32)
{
    Spi_RegisterPtrType MReg_pt = (Spi_RegisterPtrType)NULL_PTR;

    MReg_pt = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;
    if (MReg_pt != NULL_PTR)
    {
        uint32 flg = MReg_pt->Spi_FLG & 0x1FU;

        MReg_pt->Spi_FLG |= flg;
    }
}

static uint8 CheckHwUnitId(Spi_HWUnitType hwUnitId)
{
    uint8  retVal             = 0U;
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/
    if (SPI_UNIT_MIBSPI1 == hwUnitId)
    {
        retVal             = 0U;
        Avoid_nesting_flag = 1U;
    }
    if ((Avoid_nesting_flag == 0U) && (SPI_UNIT_MIBSPI2 == hwUnitId))
    {
        retVal             = 1U;
        Avoid_nesting_flag = 1U;
    }
#if (SPI_UNIT_RCSS_MIBSPI1_ACTIVE == STD_ON)
    if ((Avoid_nesting_flag == 0U) && (RCSS_SPI_UNIT_MIBSPI1 == hwUnitId))
    {
        retVal             = 3U;
        Avoid_nesting_flag = 1U;
    }
#endif
#if (SPI_UNIT_RCSS_MIBSPI2_ACTIVE == STD_ON)
    if ((Avoid_nesting_flag == 0U) && (RCSS_SPI_UNIT_MIBSPI2 == hwUnitId))
    {
        retVal = 4U;
    }
#endif

    return (retVal);
}

/* SourceId : SPI_SourceId_048 */
/* DesignId : SPI_DesignId_003 */
/* Requirements : SWS_Spi_00437, SWS_Spi_00290, SWS_Spi_00289,SWS_Spi_00149,
                  SWS_Spi_00289,  SWS_Spi_00437, SWS_Spi_00028
 */
static FUNC(void, SPI_CODE) Spi_dlcRamFillData(uint32 HwUnit_u32)
{
    uint16 TgLen_u16; /* local transfer group length */

    Spi_DlcEventPtrType  DlcEv_pt;
    Spi_RamBufferPtrType MRam_pt = (Spi_RamBufferPtrType)NULL_PTR;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    MRam_pt  = Spi_HWUnitMap_at[HwUnit_u32].Ram_pt;
    if (MRam_pt != NULL_PTR)
    {
        if (DlcEv_pt->Guard_u8 == (uint8)SPI_DLC_G_PENDING)
        {
            DlcEv_pt->Guard_u8 = (uint8)SPI_DLC_G_ACTIVE;
        }
        if (DlcEv_pt->Guard_u8 == (uint8)SPI_DLC_G_ACTIVE)
        {
            /* mark the transfer group */
            TgLen_u16 = 0U;

            /* check i transfer group is full */
            Spi_checkTxTransferGroup(&TgLen_u16, DlcEv_pt, MRam_pt, &HwUnit_u32);
            ;
        }
    }
}

static FUNC(void, SPI_CODE) Spi_ChBufTXCheck(P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) ChBufTx_pt,
                                             uint16 *DefData_u16, uint8 *ChIDTx_u8)
{
    if (ChBufTx_pt == NULL_PTR)
    {
        *DefData_u16 = Spi_DrvObj.channelObj[*ChIDTx_u8].chCfg.defaultTxData;
    }
}

static FUNC(void, SPI_CODE) Spi_checkTxTransferGroup(uint16 *TgLen_u16, Spi_DlcEventPtrType DlcEv_pt,
                                                     Spi_RamBufferPtrType MRam_pt, uint32 *HwUnit_u32)
{
    uint16         DefData_u16 = (uint16)0U; /* local default data value, to prevent too many rom accesses */
    uint16         DataLoc_u16 = 0U;
    Std_ReturnType EVal_t      = E_OK;
    uint8          ChIDTx_u8   = 0U; /* channel identifier, Rx used as index */
    uint16         TxPos_u16   = 0U; /* buffer filled counter, increases with each successful write/read to MIB Ram */
    P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA)
    ChBufTx_pt                          = (Spi_DataBufferType *)NULL_PTR; /* pointer to Tx channel buffer */
    uint16               hflWrdLen      = 0U;
    Spi_NumberOfDataType Spi_TxRxLength = 0U;

    while (*TgLen_u16 < SPI_DLC_TG_LEN)
    {
        ChIDTx_u8 = DlcEv_pt->ID_u8[SPI_DLC_TX];
        TxPos_u16 = DlcEv_pt->Pos_u16[SPI_DLC_TX];
        /* handle buffers for Tx and Rx */
        ChBufTx_pt     = Spi_DrvObj.channelObj[ChIDTx_u8].txBufPtr;
        Spi_TxRxLength = Spi_DrvObj.channelObj[ChIDTx_u8].numWordsTxRx;
        hflWrdLen      = Spi_TxRxLength;
        /*
         * this loop transfers data from the channel(s) to RAM
         * and uses interrupts to transfer and reload the data
         */

        Spi_ChBufTXCheck(ChBufTx_pt, &DefData_u16, &ChIDTx_u8);

        if (Spi_DrvObj.channelObj[ChIDTx_u8].chCfg.dataWidth > 16U)
        {
            hflWrdLen = Spi_TxRxLength * 2U;
        }
        while (TxPos_u16 < hflWrdLen)
        {
            if (*TgLen_u16 == SPI_DLC_TG_LEN)
            {
                /* transfer group is full, write position back and leave */
                DlcEv_pt->Pos_u16[SPI_DLC_TX] = TxPos_u16;
                EVal_t                        = E_NOT_OK;
            }
            else
            {
                /* get Mib status */
                DlcEv_pt->RxStat_u16 = MRam_pt->Spi_RxBank[*TgLen_u16].RxStat;

                /* 32Bit mode selected */
                EVal_t = Spi_filldata(*TgLen_u16, &ChIDTx_u8, ChBufTx_pt, MRam_pt, &TxPos_u16, &DataLoc_u16,
                                      &DefData_u16, HwUnit_u32, DlcEv_pt);

                MRam_pt->Spi_TxBank[*TgLen_u16].TxData = DataLoc_u16;
                /* data filled, increase count */
                (TxPos_u16)++;
                (*TgLen_u16)++;
            }

            if (EVal_t == (Std_ReturnType)E_NOT_OK)
            {
                break;
            }
        }
        if ((EVal_t == (Std_ReturnType)E_OK) && (*TgLen_u16 != 0U))
        {
            EVal_t = Spi_dlcSwitchChannel(&MRam_pt->Spi_TxBank[(*TgLen_u16 - 1U)].TxCtrl, DlcEv_pt, SPI_DLC_TX);
        }

        if (EVal_t == (Std_ReturnType)E_NOT_OK)
        {
            /* all channels have been processed */
            break;
        }
    }
}

static FUNC(Std_ReturnType, SPI_CODE)
    Spi_filldata(uint16 TgLen_u16, uint8 *const                                                         ChIDTx_u8,
                 P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) ChBufTx_pt, Spi_RamBufferPtrType MRam_pt,
                 uint16 *const TxPos_u16, uint16 *DataLoc_u16, uint16 *const DefData_u16, uint32 *const HwUnit_u32,
                 Spi_DlcEventPtrType DlcEv_pt)
{
    Std_ReturnType EVal_t = E_OK;
    /* ready to fill */
    /* the ram buffer should only be filled if the flag is zero, otherwise the data was not
     * transmitted */
    if (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_TXFULL))
    {
        Spi_dlcError(*HwUnit_u32);
        EVal_t = E_NOT_OK;
    }
    else
    {
        /* setup data */
        MRam_pt->Spi_TxBank[TgLen_u16].TxCtrl = DlcEv_pt->TxCtrl_u16;
        if (ChBufTx_pt == NULL)
        {
            /* write default data */
            *DataLoc_u16 = *DefData_u16;
        }
        else
        {
            /* write bytes to the channel */
            if (Spi_DrvObj.channelObj[*ChIDTx_u8].chCfg.dataWidth == 8U)
            {
                /* use uint8 buffer mode */
                *DataLoc_u16 = ((Spi_DlcFrame8PtrType)ChBufTx_pt)[*TxPos_u16];
            }
            else
            {
                /* use uint16 buffer mode */
                *DataLoc_u16 = ((Spi_DlcFrame16PtrType)ChBufTx_pt)[*TxPos_u16];
                Spi_check32bitMode(&TgLen_u16, MRam_pt, *ChIDTx_u8, DataLoc_u16, ChBufTx_pt, *TxPos_u16);
            }
        }
    }
    return (EVal_t);
}

static FUNC(void, SPI_CODE)
    Spi_check32bitMode(uint16 *const TgLen_u16, Spi_RamBufferPtrType MRam_pt, uint8 ChIDTx_u8, uint16 *DataLoc_u16,
                       P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) ChBufTx_pt, uint16 TxPos_u16)
{
    if (Spi_DrvObj.channelObj[ChIDTx_u8].chCfg.dataWidth == 32U)
    {
        /* First 16 bits of 32 word? */
        if (0U == (*TgLen_u16 % 2U))
        {
            /* Enable CSHOLD */
            SPI_SETVAL16(MRam_pt->Spi_TxBank[*TgLen_u16].TxCtrl, TXRAMCTRL_CSHOLD);
            /* Disable WDEL */

            /* The while (TgLen_u16 < SPI_DLC_TG_LEN) protects the TgLen_u16 to not go beyond
             * SPI_DLC_TG_LEN ie 128
             */
            SPI_CLRVAL16(MRam_pt->Spi_TxBank[*TgLen_u16].TxCtrl, TXRAMCTRL_WDEL);
            /* If LSB selected, invert 16bit words */
            if (Spi_DrvObj.channelObj[ChIDTx_u8].chCfg.transferType == SPI_LSB)
            {
                *DataLoc_u16 = ((Spi_DlcFrame16PtrType)ChBufTx_pt)[TxPos_u16 + 1U];
            }
        }
        else
        {
            /* If LSB selected, invert 16bit words */
            if (Spi_DrvObj.channelObj[ChIDTx_u8].chCfg.transferType == SPI_LSB)
            {
                *DataLoc_u16 = ((Spi_DlcFrame16PtrType)ChBufTx_pt)[TxPos_u16 - 1U];
            }
        }
    }
}

/*
 * Requirements : SWS_Spi_00289, SWS_Spi_00290, SWS_Spi_00437, SWS_Spi_00036,
 *                SWS_Spi_00030
 */
static FUNC(void, SPI_CODE) Spi_dlcRamDrainData(uint32 HwUnit_u32)
{
    Spi_RamBufferPtrType MRam_pt = (Spi_RamBufferPtrType)NULL_PTR;
    uint8                Guard   = 0U;

    MRam_pt = Spi_HWUnitMap_at[HwUnit_u32].Ram_pt;
    if (MRam_pt != NULL_PTR)
    {
        Guard = Spi_DlcEvent_t[HwUnit_u32].Guard_u8;
        switch (Guard)
        {
            case SPI_DLC_G_ACTIVE:
            case SPI_DLC_G_FINISHED:
                Spi_checkRxTransferGroup(&Spi_DlcEvent_t[HwUnit_u32], MRam_pt, &HwUnit_u32);
                break;

            default:
                /*Do Nothing*/
                break;
        }
    }
}
static FUNC(void, SPI_CODE)
    Spi_checkRxTransferGroup(Spi_DlcEventPtrType DlcEv_pt, Spi_RamBufferPtrType MRam_pt, uint32 *HwUnit_u32)
{
    uint16 TgLen_u16 = 0U; /* local transfer group length */
    uint8  ChIDRx_u8 = 0U; /* channel identifier, used as index */
    uint16 RxPos_u16 = 0U; /* buffer filled counter, increases with each successful write/read to MIB Ram */
    P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA)
    ChBufRx_pt                          = (Spi_DataBufferType *)NULL_PTR; /* pointer to Tx channel buffer */
    Spi_NumberOfDataType Spi_TxRxLength = 0U;
    uint16               hlfWdLen       = 0U;
    Std_ReturnType       EVal_t         = E_OK; /* evaluate return value of Spi_dlcSwitchChannel */
    /* mark the transfer group */
    TgLen_u16 = 0U;
    while (TgLen_u16 < SPI_DLC_TG_LEN)
    {
        ChIDRx_u8 = DlcEv_pt->ID_u8[SPI_DLC_RX];
        RxPos_u16 = DlcEv_pt->Pos_u16[SPI_DLC_RX];
        /* handle buffers for Rx */

        ChBufRx_pt     = Spi_DrvObj.channelObj[ChIDRx_u8].rxBufPtr;
        Spi_TxRxLength = Spi_DrvObj.channelObj[ChIDRx_u8].numWordsTxRx;
        hlfWdLen       = Spi_TxRxLength;

        if (Spi_DrvObj.channelObj[ChIDRx_u8].chCfg.dataWidth > 16U)
        {
            hlfWdLen = Spi_TxRxLength * 2U;
        }
        /* this loop drains data from MIB ram to the channel(s)*/
        while (RxPos_u16 < hlfWdLen)
        {
            if (TgLen_u16 >= SPI_DLC_TG_LEN)
            {
                /* transfer group is full, write position back and leave */
                DlcEv_pt->Pos_u16[SPI_DLC_RX] = RxPos_u16;
                EVal_t                        = E_NOT_OK;
            }
            else
            {
                /* access MIB ram */
                /* read of this register resets the RX flag to 1 */
                DlcEv_pt->RxStat_u16 = MRam_pt->Spi_RxBank[TgLen_u16].RxStat;
                /* ready to drain ? */
                EVal_t =
                    Spi_readyToDrain(DlcEv_pt, HwUnit_u32, MRam_pt, ChBufRx_pt, &RxPos_u16, &TgLen_u16, &ChIDRx_u8);
            }
            if (EVal_t == (Std_ReturnType)E_NOT_OK)
            {
                break;
            }
        }
        /* all bytes in a channel have been treated, select next channel */
        if (EVal_t == (Std_ReturnType)E_OK)
        {
            /* one channel received, prepare next */
            EVal_t = Spi_dlcSwitchChannel((volatile uint16 *)NULL_PTR, DlcEv_pt, SPI_DLC_RX);
        }

        if (EVal_t == (Std_ReturnType)E_NOT_OK)
        {
            /* all channels have been processed */
            break;
        }
    }
}

static FUNC(Std_ReturnType, SPI_CODE)
    Spi_readyToDrain(Spi_DlcEventPtrType DlcEv_pt, uint32 *const HwUnit_u32, Spi_RamBufferPtrType MRam_pt,
                     P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) ChBufRx_pt, uint16 *RxPos_u16,
                     uint16 *TgLen_u16, uint8 *const ChIDRx_u8)
{
    uint16         DataLoc_u16 = 0U; /* local data value from MIB Ram register */
    Std_ReturnType EVal_t      = E_OK;
    if (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_RXEMPTY))
    {
        /* this should not happen! */
        Spi_dlcError(*HwUnit_u32);
        EVal_t = E_NOT_OK;
    }
    else
    {
        /* Klocwork Inspected. Buffer overflow-array index out of bounds.
        The while (TgLen_u16 < SPI_DLC_TG_LEN) protects the TgLen_u16 to not go beyond
        SPI_DLC_TG_LEN ie 128
        */
        DataLoc_u16 = MRam_pt->Spi_RxBank[*TgLen_u16].RxData;
        if (ChBufRx_pt == NULL_PTR)
        {
            /* skip any data, but data must be read to clear the flag, see line above */
        }
        else
        {
            /* read bytes to the channel */
            if (Spi_DrvObj.channelObj[*ChIDRx_u8].chCfg.dataWidth == (uint8)8U)
            {
                /* use uint8 buffer mode */

                ((Spi_DlcFrame8PtrType)ChBufRx_pt)[*RxPos_u16] = (uint8)DataLoc_u16;
            }
            else
            {
                /* use uint16 buffer mode */
                ((Spi_DlcFrame16PtrType)ChBufRx_pt)[*RxPos_u16] = DataLoc_u16;
            }
        }
        /* data drained, increase count */
        (*RxPos_u16)++;
        (*TgLen_u16)++;
    }
    return (EVal_t);
}

static FUNC(void, SPI_CODE) Spi_dlcRamTriggerData(uint32 HwUnit_u32)
{
    /* transfer group is ready for transfer, trigger interrupt generation */
    Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] |= TGCTRL_TGENA(1U);
}

static FUNC(void, SPI_CODE) Spi_dlcConsumeEvent(uint32 HwUnit_u32)
{
    uint8 Ram_u8 = 0U; /* temporary parameter for RamUsed ON/OFF */

    Ram_u8 = Spi_HWUnitMap_at[HwUnit_u32].Prop_pt->Spi_RamUsed;

    Spi_dlcTransmit(HwUnit_u32);
    Spi_DrvObj.hwUnitObj[HwUnit_u32].hwUnitResult = SPI_HW_UNIT_PENDING;

    Spi_DlcOptionSelect[Ram_u8].FillData(HwUnit_u32);
    /* this triggers the normal data transfer */
    Spi_DlcOptionSelect[Ram_u8].Trigger(HwUnit_u32);
}

/*
 * Requirements : SWS_Spi_00267
 */
static FUNC(void, SPI_CODE) Spi_dlcError(uint32 HwUnit_u32)
{
    Spi_DlcEventPtrType DlcEv_pt     = NULL_PTR;
    uint32              HwUnit_u32_1 = 0U;
    uint16              Error_u16    = 0U; /* local error level */
    uint8               JobIDLoc_u8  = 0U; /* job identifier, used as index */
                                           /* set the simulated job, error and HW unit */
    JobIDLoc_u8               = SPI_DLC_LOWBYTE_GET(HwUnit_u32);
    HwUnit_u32_1              = Spi_DrvObj.jobObj[JobIDLoc_u8].jobCfg.hwUnitId;
    uint32 Avoid_nesting_flag = 0U; /*Used to solve METRICS.E.HIS_Metrics___Max_nesting_level_LEVEL issue*/

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32_1];
    /* this value if not zero, indicates that the error function was called from Fill/Drain function
     */
    if (DlcEv_pt->RxStat_u16 != 0U)
    {
        if (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_TXFULL))
        {
#ifdef SPI_E_TXSTALL_ERROR
            /* the transmit function has been called, but the sequencer still has not processed the
             * buffer */
            Dem_SetEventStatus(SPI_E_TXSTALL_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }
        else if (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_RXEMPTY))
        {
#ifdef SPI_E_RXSTALL_ERROR
            /* the receive function has been called, but the sequencer still has not processed the
             * buffer */
            Dem_SetEventStatus(SPI_E_RXSTALL_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }
        else
        {
            /* no action */
        }
    }
    else
    {
        if (Spi_HWUnitMap_at[HwUnit_u32_1].Prop_pt->Spi_RamUsed == (uint8)STD_ON)
        {
            /* the overrun value ranges from 0x200 - 0x3FC, so we have to subtract an offset */
            Error_u16 = (uint16)(Spi_HWUnitMap_at[HwUnit_u32_1].Reg_pt->Spi_RXOVRN_ADDR - (uint16)SPI_DLC_MIBTXSIZE);

            DlcEv_pt->RxStat_u16 = Spi_HWUnitMap_at[HwUnit_u32_1].Ram_pt->Spi_RxBank[Error_u16].RxStat;
        }
        else
        {
            DlcEv_pt->RxStat_u16 = Spi_HWUnitMap_at[HwUnit_u32_1].Reg_pt->Spi_BUF.RxStat;
        }
        /* report to DEM */
        if (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_BITERR))
        {
#ifdef SPI_E_BIT_ERROR
            /* bit error*/
            Dem_SetEventStatus(SPI_E_BIT_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_DESYNC)))
        {
#ifdef SPI_E_DESYNC_ERROR
            /* desynch error*/
            Dem_SetEventStatus(SPI_E_DESYNC_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_TIMEOUT)))
        {
#ifdef SPI_E_TO_ERROR
            /* timeout error */
            Dem_SetEventStatus(SPI_E_TO_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_DLENERR)))
        {
#ifdef SPI_E_DLEN_ERROR
            /* data length error */
            Dem_SetEventStatus(SPI_E_DLEN_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            Avoid_nesting_flag = 1U;
        }
        if ((Avoid_nesting_flag == 0U) && (SPI_DLC_CHECK_HEX16(DlcEv_pt->RxStat_u16, RXRAMCTRL_RXOVR)))
        {
#ifdef SPI_E_DOVR_ERROR
            /* overwrite occurred, Rx */
            Dem_SetEventStatus(SPI_E_DOVR_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
        }
    }

    /* release job */
    DlcEv_pt->RxStat_u16                            = 0U;
    DlcEv_pt->Guard_u8                              = (uint8)SPI_DLC_G_IDLE;
    DlcEv_pt->Event_u8                              = (uint8)SPI_DLC_EV_CONSUMED;
    Spi_DrvObj.hwUnitObj[HwUnit_u32_1].hwUnitResult = SPI_HW_UNIT_FAILED;
}

static FUNC(Std_ReturnType, SPI_CODE)
    Spi_dlcSwitchChannel(P2VAR(volatile uint16, AUTOMATIC, SPI_VAR) Ctrl_pt,
                         P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) Ev_pt, Spi_DlcTxRxDefType Dir_t)
{
    uint8          ChIDTxRx_u8; /* channel identifier, used as index */
    uint8          ChIdx_u8;    /* channel index of a channel list */
    Std_ReturnType RVal = E_OK;

    /* one channel transferred, prepare next */
    Ev_pt->Num_u8[Dir_t]++;
    /* all channels in a job transferred ? */
    if (Ev_pt->Num_u8[Dir_t] >= Spi_DrvObj.jobObj[Ev_pt->JobID_u8].jobCfg.channelPerJob)
    {
        /* execute this only if CS handling is selected as active and in TX mode */
        if ((Ev_pt->DFSel_u8[0U] != SPI_NO_CHIP_SELECT) && (Ctrl_pt != NULL_PTR))
        {
            /* finish job, and deactivate CS */
            SPI_CLRVAL16(*Ctrl_pt, TXRAMCTRL_CSHOLD);
        }
        else
        {
            /* no action */
        }
        /* all channels in a job transmitted */
        if (Dir_t == SPI_DLC_TX)
        {
            /* if tx direction detects a end of all channels, the state is finished */
            Ev_pt->Guard_u8 = (uint8)SPI_DLC_G_FINISHED;
        }
        else
        {
            /* if rx direction detects a end of all channels, the state is idle, because
             * all data has been transmitted and received
             * */
            Ev_pt->Guard_u8 = (uint8)SPI_DLC_G_IDLE;
        }
        RVal = E_NOT_OK;
    }
    else
    {
        /* get next channel to receive */
        Ev_pt->Pos_u16[Dir_t] = (uint16)0U;
        ChIdx_u8              = Ev_pt->Num_u8[Dir_t];
        ChIDTxRx_u8           = Spi_DrvObj.jobObj[Ev_pt->JobID_u8].jobCfg.channelList[ChIdx_u8];
        Ev_pt->ID_u8[Dir_t]   = ChIDTxRx_u8;
    }
    return (RVal);
}
/* SourceId : SPI_SourceId_052 */
/* DesignId : SPI_DesignId_003 */

static FUNC(void, SPI_CODE) Spi_dlcTransmit(uint32 HwUnit_u32)
{
    uint32 TGReg_u32 = 0U;    /* local register mirror */
    uint32 CSVal_u32 = 0U;    /* local value for chip select */
    uint8  ExtDev_u8 = 0U;    /* local external device, used as index  */
    uint8  TMS_SpiModeWA[4U]; /* the modes of the TMS Spi do not match the Spi Mode Matrix, so they
                                 have to be converted */
    uint8  JobIDLoc_u8 = 0U;  /* job identifier, used as index */
    uint8  ChIDTxRx_u8 = 0U;  /* channel identifier, used as index */

    Spi_DlcEventPtrType DlcEv_pt                                                = NULL_PTR;
    P2CONST(Spi_MibspiExternalDeviceConfigType, AUTOMATIC, SPI_PBCFG) DevCfg_pt = NULL_PTR;
    P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_PBCFG) ChCfg_pt               = NULL_PTR;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];

    TGReg_u32 = 0U;

    TMS_SpiModeWA[0U] = 1U; /* the index is the real Spi mode, the contents the TMS Spi mode */
    TMS_SpiModeWA[1U] = 0U;
    TMS_SpiModeWA[2U] = 3U;
    TMS_SpiModeWA[3U] = 2U;

    /* start with high prio job, IdxLev0_uloc is the TG index, equal to the job priority  */
    JobIDLoc_u8 = DlcEv_pt->JobID_u8;
    /* external device assigned to a job */
    ExtDev_u8 = Spi_DrvObj.jobObj[JobIDLoc_u8].jobCfg.externalDeviceCfgId;
    /* the guard signals the job to be transmitted */
    if (DlcEv_pt->Guard_u8 == (uint8)SPI_DLC_G_PENDING)
    {
        /* start with first channel in a job */
        /* the assignment starts with index 1, index 0 is the number of channels */
        DlcEv_pt->Num_u8[SPI_DLC_TX] = 0U;
        DlcEv_pt->Num_u8[SPI_DLC_RX] = 0U;
        /* get first channel ID in a job */
        ChIDTxRx_u8 = Spi_DrvObj.jobObj[JobIDLoc_u8].jobCfg.channelList[0U];
        /* save ChID for later transmit */
        DlcEv_pt->ID_u8[SPI_DLC_TX] = ChIDTxRx_u8;
        DlcEv_pt->ID_u8[SPI_DLC_RX] = ChIDTxRx_u8;
        /* reset channel pointer for Tx,Rx  */
        DlcEv_pt->Pos_u16[SPI_DLC_TX]     = 0U;
        DlcEv_pt->Pos_u16[SPI_DLC_RX]     = 0U;
        DlcEv_pt->Default_u16[SPI_DLC_TX] = (uint16)Spi_DrvObj.channelObj[ChIDTxRx_u8].chCfg.transferType;
        DlcEv_pt->Default_u16[SPI_DLC_RX] = 0U; /* us a memory location to store and trash data */

        DevCfg_pt = &Spi_DrvObj.extDevCfg[ExtDev_u8].mibspi;
        ChCfg_pt  = &Spi_DrvObj.channelObj[ChIDTxRx_u8].chCfg;
        /* set other data related parameters                               */

        /* set clock polarity (clock idle level) and */
        /* set phase (data shift edge), apply the TMS WA */
        SPI_SETVAL32(TGReg_u32, SPIFMT_PHASE(TMS_SpiModeWA[DevCfg_pt->Spi_Mode]));
        /* this register holds the data format word, which is vital for transmission */
        Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_FMT[0U] = TGReg_u32;
        /* For every channel we need to update the data format word */
        /* set new char length (here 8bit) */
        if (8U >= (ChCfg_pt->dataWidth))
        {
            SPI_SETVAL32(TGReg_u32, SPIFMT_CHARLEN(8U));
        }
        else
        {
            SPI_SETVAL32(TGReg_u32, SPIFMT_CHARLEN(16U));
        }
        /* set shift dir (LSB or MSB) */

        SPI_SETVAL32(TGReg_u32, SPIFMT_SHIFTDIR(ChCfg_pt->transferType));
        /* set WDELAY */

        SPI_SETVAL32(TGReg_u32, SPIFMT_WDELAY(DevCfg_pt->Spi_CsIdleTime));
        /* values set, update the register */
        SPI_SETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_FMT[0U], TGReg_u32);
        /* set baud rate */
        SPI_SETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_EXT_PRESCALE1, DevCfg_pt->Spi_Baudrate);

        DlcEv_pt->TxCtrl_u16 =
            Spi_DlcOptionSelect[Spi_HWUnitMap_at[HwUnit_u32].Prop_pt->Spi_RamUsed].Transmit(HwUnit_u32);
        if (DevCfg_pt->Spi_CsMode == SPI_CONTINUOUS)
        {
            SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, TXRAMCTRL_CSHOLD);
        }
        else
        {
            SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, TXRAMCTRL_WDEL);
        }
        /* get the chip select */
        CSVal_u32 = (uint32)DevCfg_pt->Spi_DioPin;
        /* set Tx control field with the default value of Spi_Def register */
        SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, SPI_DLC_LOWWORD_GET(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_DEF));
        /* execute this only if CS handling is selected as active */
        if (CSVal_u32 != (uint32)SPI_NO_CHIP_SELECT)
        {
            /* low byte holds the CS idle level */

            if (SPI_DLC_LOWBYTE_GET(DevCfg_pt->Spi_CsProperty) == (uint8)1U)
            {
                SPI_CLRVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_DEF, ((uint32)1U << CSVal_u32));
                SPI_SETVAL16(DlcEv_pt->TxCtrl_u16, ((uint32)1U << CSVal_u32));
            }
            else
            {
                SPI_SETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_DEF, ((uint32)1U << CSVal_u32));
                SPI_CLRVAL16(DlcEv_pt->TxCtrl_u16, ((uint32)1U << CSVal_u32));
            }
        }
        else
        {
            /* no action */
        }
        /* save the CS ID */
        DlcEv_pt->DFSel_u8[0U] = (uint8)CSVal_u32;
        /* save the external device */
        DlcEv_pt->DFSel_u8[1U] = ExtDev_u8;

        /* setup timings CS2_CLK[31..24], CLK_2CS[23..16], CS2_ENA[15..8], ENA_2CS[7..0] */
        Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_DELAY[0U] = DevCfg_pt->Spi_ClkDelays[0U];
        Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_DELAY[1U] = DevCfg_pt->Spi_ClkDelays[1U];
    }
    else
    {
        /* no action */
    }
}

/***********************************************************************************************************************
 *  specialization Spi_dlcRamTransmit
 **********************************************************************************************************************/
/*! \brief      This function triggers SPI transmission.
 *  \param[in]  HwUnit_u32              SPI HW Unit
 *  \param[out] inOut                   none
 *  \return     uint16                  buffer mode of the spi
 *  \pre        none
 *  \context    transmission startup
 **********************************************************************************************************************/

static FUNC(uint16, SPI_CODE) Spi_dlcRamTransmit(uint32 HwUnit_u32)
{
    /* set Transfer group as Software Triggered with ONESHOT*/
    /* start transfer every time the TG_ENA is set */
    Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] = TGCTRL_TRIGSRC(0x0U) | TGCTRL_TRIGEVT(0x7U);
    /* enable oneshot */
    SPI_SETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U], TGCTRL_TGONESHOT(1U));

    /* buffer mode 3 */
    return (SPI_DLC_TXCTRL_BUFMOD(3U));
}

static FUNC(void, SPI_CODE) Spi_dlcRamInit(uint32 HwUnit_u32)
{
    Spi_RegisterPtrType MRam_pt   = (Spi_RegisterPtrType)NULL_PTR;
    uint32              txmibsz   = 0U;
    volatile uint32     tempCount = SPI_MAX_TIMEOUT_DURATION;
    if (SPI_MAX_TIMEOUT_DURATION > 9U)
    {
        /* each unit of SW_delay equals to 9 clockcycle, so divided by 9U*/
        tempCount = SPI_MAX_TIMEOUT_DURATION / 9U;
    }

    MRam_pt = Spi_HWUnitMap_at[HwUnit_u32].Reg_pt;

    /* verify that the MIB ram finished auto initialization */

    while (SPI_DLC_CHECK_HEX32(MRam_pt->Spi_FLG, SPI_BUFINIT))
    {
        /* Below API can change start time, so use temp variable */
        if (tempCount <= 0U)
        {
#ifdef SPI_E_HARDWARE_ERROR
            /* timeout */
            Dem_SetEventStatus(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
#endif
            break;
        }
        MCAL_SW_DELAY(tempCount);
    }
    /* prepare TG(x) ctrl register */
    /* set PStart to 0, we use the whole MIB RAM as one TG */
    MRam_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] = 0U;
    /* store end address in LTGPEND register bit 14::8 */
    MRam_pt->Spi_RegTGCTL.Spi_TGCTRL[1U] = LTGPEND_LPEND(SPI_DLC_MIBTXSIZE);
    /* store end address in LTGPEND register bit 14::8 */
    txmibsz = (uint32)(SPI_DLC_MIBTXSIZE - 1U);

    MRam_pt->Spi_RegTGCTL.Spi_LTGPEND = (uint32)LTGPEND_LPEND(txmibsz);
    /* set Irq parameters            */
    /* map the TG[0] transfer end interrupts to the INT1 line */
    /* map the TG[0] transfer error interrupts to the INT0 line */
    MRam_pt->Spi_RegTGCTL.Spi_TGITLVST = TGITLVST_SETINTLEVEL(1U, 16U);
    /* enable the TG[0] interrupt generation (Value, bit for TG enable Irq) */
    MRam_pt->Spi_RegTGCTL.Spi_TGITENST = TGITENST_SETINTENRDY(1U, 16U) | TGITENST_SETINTENRDY(1U, 0U);
}

static FUNC(void, SPI_CODE) Spi_dlcRamClose(uint32 HwUnit_u32)
{
    uint32              MibIdx_u32 = 0U; /* index in MIBRAM */
    Spi_RegisterPtrType MReg_pt    = (Spi_RegisterPtrType)NULL_PTR;

    MReg_pt                              = Spi_HWUnit_at[HwUnit_u32];
    MReg_pt->Spi_RegTGCTL.Spi_TGCTRL[0U] = (uint32)SPI_DLC_BITCLR;

    MReg_pt->Spi_RegTGCTL.Spi_TICKCNT = (uint32)SPI_DLC_BITCLR;

    MReg_pt->Spi_RegTGCTL.Spi_LTGPEND = (uint32)SPI_DLC_BITCLR;

    MReg_pt->Spi_RegTGCTL.Spi_TGITLVST = (uint32)SPI_DLC_BITCLR;

    MReg_pt->Spi_RegTGCTL.Spi_TGITENCR = (uint32)SPI_DLC_BITCLR;
    for (MibIdx_u32 = 0U; MibIdx_u32 < SPI_DLC_MIBRXSIZE; MibIdx_u32++)
    {
        /* read whole MIBRAM to reset all status flags */
        Spi_RamUnit_at[HwUnit_u32]->Spi_RxBank[MibIdx_u32].RxStat;

        Spi_RamUnit_at[HwUnit_u32]->Spi_RxBank[MibIdx_u32].RxData;
    }
    /* clear MIBSPI enable bit, this must be done at last */
    /* the bit works as switch to enable access to the MIBSPI registers */
    SPI_CLRVAL32(MReg_pt->Spi_EN, MIBSPIE_EN(1U));
}

FUNC(void, SPI_CODE) Spi_SetValIfCSActive(Spi_RegisterPtrType MReg_pt, uint32 CSVal_u32)
{
    /* execute this only if CS handling is selected as active */
    if (CSVal_u32 != SPI_NO_CHIP_SELECT)
    {
        SPI_SETVAL32(MReg_pt->Spi_DEF, ((uint32)1U << CSVal_u32));
    }
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/
/* Requirements : SWS_Spi_00040 */
FUNC(void, SPI_CODE) Spi_DlcInit(void)
{
    uint32 CSVal_u32     = 0U; /* local value for chip select */
    uint32 ExtDevIdx_u32 = 0U; /* external device index to set the levels as configured */

    P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) DlcEv_pt;

    P2CONST(Spi_HWUnitPropertyType, AUTOMATIC, SPI_VAR) PropLoc_pt; /* pointer to unit properties */
    Spi_RegisterPtrType MReg_pt;
    uint8               UnitIdx_u8; /* hardware unit index of generated unit arrays */
    uint8               HWUnit_u8;  /* local value for hardware unit */

    uint8 idx = 0U;

    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Init      = Spi_dlcRamInit;
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Close     = Spi_dlcRamClose;
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].FillData  = Spi_dlcRamFillData;
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].DrainData = Spi_dlcRamDrainData;
    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Trigger   = Spi_dlcRamTriggerData;

    Spi_DlcOptionSelect[SPI_DLC_RAMOPT].Transmit = Spi_dlcRamTransmit;

    /*
     * set HW unit parameters
     */

    for (idx = 0U; idx < Spi_DrvObj.Spi_MaxDlcs; idx++)
    {
        if (NULL_PTR != Spi_HWUnit_at[idx])
        {
            UnitIdx_u8 = CheckHwUnitId(Spi_DrvObj.hwUnitObj[idx].hwUnitCfg.hwUnitId);
            PropLoc_pt = &Spi_UnitProperty_at[UnitIdx_u8];

            HWUnit_u8                           = PropLoc_pt->Spi_UnitID;
            Spi_HWUnitMap_at[HWUnit_u8].Reg_pt  = Spi_HWUnit_at[UnitIdx_u8];
            Spi_HWUnitMap_at[HWUnit_u8].Ram_pt  = Spi_RamUnit_at[UnitIdx_u8];
            Spi_HWUnitMap_at[HWUnit_u8].Prop_pt = PropLoc_pt;

            DlcEv_pt = &Spi_DlcEvent_t[HWUnit_u8];

            DlcEv_pt->Event_u8 = (uint8)SPI_DLC_EV_CONSUMED;
            DlcEv_pt->Guard_u8 = (uint8)SPI_DLC_G_IDLE;

            MReg_pt = Spi_HWUnitMap_at[HWUnit_u8].Reg_pt;
            /* Bring SPI out of RESET state */

            MReg_pt->Spi_GCR0 = 1U;

            /* set master, external clk, enable SPI  */

            MReg_pt->Spi_GCR1 = MIBSPIEGCR1_MASTER(1U) | MIBSPIEGCR1_CLKMOD(1U) | MIBSPIEGCR1_SPIEN(1U);
            /* added below so that BUF init is initiated much earlier */

            if ((PropLoc_pt->Spi_RamUsed == STD_ON))
            {
                /* enable MIB spi to get access to the MIB registers */

                SPI_SETVAL32(MReg_pt->Spi_EN, MIBSPIE_EN(1U));
            }
            for (ExtDevIdx_u32 = 0U; ExtDevIdx_u32 < Spi_DrvObj.maxExtDevCfg; ExtDevIdx_u32++)
            {
                /* get the chip select */
                CSVal_u32 = (uint32)Spi_DrvObj.extDevCfg[ExtDevIdx_u32].mibspi.Spi_DioPin;

                Spi_SetValIfCSActive(MReg_pt, CSVal_u32);

                SPI_SETVAL32(MReg_pt->Spi_PC.Spi_FUN, 0x01010E0FU);

                SPI_SETVAL32(MReg_pt->Spi_PC.Spi_PDIS, 0x0U);

                SPI_SETVAL32(MReg_pt->Spi_PC.Spi_PSEL, 0xF01U);
            }
            /* if hardware unit has no RAM so it runs in standard mode, the MIB features will not be
             * initialized */
            Spi_DlcOptionSelect[PropLoc_pt->Spi_RamUsed].Init(HWUnit_u8);
        }
    }
}

FUNC(void, SPI_CODE) Spi_DlcClose(void)
{
    uint32              HwUnit_u32; /* hardware unit index     */
    uint32              OptSel_u32; /* option selector (Std or Ram) */
    Spi_RegisterPtrType MReg_pt;

    /* clear registers               */
    for (HwUnit_u32 = 0U; HwUnit_u32 < Spi_DrvObj.Spi_MaxDlcs; HwUnit_u32++)
    {
        if (NULL_PTR != Spi_HWUnit_at[HwUnit_u32])
        {
            MReg_pt    = Spi_HWUnit_at[HwUnit_u32];
            OptSel_u32 = Spi_UnitProperty_at[HwUnit_u32].Spi_RamUsed;
            Spi_DlcOptionSelect[OptSel_u32].Close(HwUnit_u32);
            /* power on default is 1 for each CS line */

            MReg_pt->Spi_DEF     = (uint32)0x0FU;
            MReg_pt->Spi_FMT[0U] = (uint32)SPI_DLC_BITCLR;

            MReg_pt->Spi_GCR1 = (uint32)SPI_DLC_BITCLR;
        }
    }
}
/* Design : : SPI_DesignId_007 */
/*
 * Requirements : SWS_Spi_00267, SWS_Spi_00383, SWS_Spi_00384, SWS_Spi_00385
 *                SWS_Spi_00386, SWS_Spi_00195
 */
FUNC(Spi_JobResultType, SPI_CODE)
Spi_DlcSetEvent(P2CONST(Spi_DlcEventType, AUTOMATIC, SPI_VAR_NOINIT) Dlc_Event_pt)
{
    Spi_JobResultType dlc_set_event_return = SPI_JOB_FAILED;
    uint32            HwUnit_u32; /* index of hardware unit */

    Spi_DlcEventPtrType DlcEv_pt;
    Spi_HwUnitObjType  *hwUnitObj;

    HwUnit_u32 = Spi_DrvObj.jobObj[Dlc_Event_pt->JobID_u8].jobCfg.hwUnitId;

    hwUnitObj = Spi_getHwUnitObj((Spi_HWUnitType)HwUnit_u32);

    SchM_Enter_Spi_SPI_EXCLUSIVE_AREA_0();
    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    /* check if a job starts transmission */
    /* check if a job is waiting for transmit, do not queue him again */
    if (NULL_PTR != hwUnitObj)
    {
        if (hwUnitObj->lpbkEnable == (boolean)TRUE)
        {
            Spi_DlcEnableLpbk((uint8)HwUnit_u32, SPI_DIGITAL_LPBK);
        }
    }

    if (DlcEv_pt->Event_u8 != (uint8)SPI_DLC_EV_CONSUMED)
    {
        /* stop critical section */
        SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
    }
    else
    {
        if (DlcEv_pt->Guard_u8 == (uint8)SPI_DLC_G_FINISHED)
        {
            dlc_set_event_return = SPI_JOB_OK;

            /* stop critical section */
            SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
        }
        else
        {
            /* used for transmission mode */
            DlcEv_pt->Event_u8 = Dlc_Event_pt->Event_u8;
            /* high prio jobs are queued at pos 0, low prio jobs at pos. 3*/
            DlcEv_pt->JobID_u8 = Dlc_Event_pt->JobID_u8;
            DlcEv_pt->Guard_u8 = (uint8)SPI_DLC_G_PENDING;

            /* stop critical section */
            SchM_Exit_Spi_SPI_EXCLUSIVE_AREA_0();
            Spi_dlcConsumeEvent(HwUnit_u32);
            /* Set return value */
            dlc_set_event_return = SPI_JOB_OK;
        }
    }

    return (dlc_set_event_return);
}

/* SourceId : SPI_SourceId_044 */
/* DesignId : SPI_DesignId_023 */
FUNC(void, SPI_CODE) Spi_IrqTxRxERR(uint32 HwUnit_u32)
{
    uint32 TGErr_u32; /* value for error check */

    P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) DlcEv_pt;

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    /* check if a error is pending, get value */
    TGErr_u32 = SPI_GETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_TGINTVECT[0U], TGINTVECT_INTVEC(0x1FU));
    /* reset value, used in DlcError function */
    DlcEv_pt->RxStat_u16 = 0U;
    /* bit five in the value signals a pending error */
    if (SPI_DLC_CHECK_BIT32(TGErr_u32, 6U))
    {
        /* we caught an error, handle it */
        Spi_dlcError(HwUnit_u32);
    }
}

/* SourceId : SPI_SourceId_045 */
/* DesignId : SPI_DesignId_022 */
FUNC(void, SPI_CODE) Spi_IrqTxRx(uint32 HwUnit_u32)
{
    volatile uint16      TGIdx_u16 = 0U; /* index of transfergroup*/
    Spi_DlcEventPtrType  DlcEv_pt  = (Spi_DlcEventPtrType)NULL_PTR;
    Spi_HWUnitMapPtrType MUnit_pt  = (Spi_HWUnitMapPtrType)NULL_PTR;

    uint8 Ram_u8 = 0U; /* temporary parameter for RamUsed ON/OFF */

    (void)MibSPI_GetIntVectReg(HwUnit_u32);

    MibSPI_ClearFlagReg(HwUnit_u32);

    MUnit_pt = &Spi_HWUnitMap_at[HwUnit_u32];
    /* check the TG which caused the IRQ    */
    /* and clear the interrupt flag by read */

    Ram_u8 = MUnit_pt->Prop_pt->Spi_RamUsed;
    if (Ram_u8 == (uint8)STD_ON)
    {
        TGIdx_u16 =
            (uint16)(SPI_GETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_TGINTVECT[1U], TGINTVECT_INTVEC(0x1FU)) >>
                     1U) -
            1U;
        /* TG(ENA) is cleared by one shot option, so the timer does not trigger this TG again */
    }
    else
    {
        TGIdx_u16 = (uint16)(SPI_GETVAL32(Spi_HWUnitMap_at[HwUnit_u32].Reg_pt->Spi_FLG, 0x3FFU));
        /* just read the flag */
        TGIdx_u16 = TGIdx_u16 + 0U;
    }

    (void)Spi_DlcOptionSelect[Ram_u8].DrainData(HwUnit_u32);

    DlcEv_pt = &Spi_DlcEvent_t[HwUnit_u32];
    /* check state if  finished or idle */
    Spi_checkTxRxState(DlcEv_pt, &Ram_u8, &HwUnit_u32);
}

static FUNC(void, SPI_CODE) Spi_checkTxRxState(Spi_DlcEventPtrType DlcEv_pt, uint8 *const Ram_u8, uint32 *HwUnit_u32)
{
    Spi_RegisterPtrType MStd_pt = (Spi_RegisterPtrType)NULL_PTR;
    if (DlcEv_pt->Guard_u8 == (uint8)SPI_DLC_G_IDLE)
    {
        /* close DLC, report the job which has finished */
        MStd_pt = Spi_HWUnitMap_at[*HwUnit_u32].Reg_pt;

        DlcEv_pt->Event_u8 = (uint8)SPI_DLC_EV_CONSUMED;

        SPI_CLRVAL16(MStd_pt->Spi_DAT1.TxCtrl, TXRAMCTRL_CSHOLD);
        Spi_checkNumberOfJobPending(DlcEv_pt);
    }
    else
    {
        /* transfer group is ready for transfer, trigger interrupt generation */

        Spi_DlcOptionSelect[*Ram_u8].FillData(*HwUnit_u32);
        Spi_DlcOptionSelect[*Ram_u8].Trigger(*HwUnit_u32);
    }
}

FUNC(void, SPI_CODE) Spi_checkNumberOfJobPending(Spi_DlcEventPtrType DlcEv_pt)
{
    Spi_HwUnitObjType *temp_hwUnitObj = (Spi_HwUnitObjType *)NULL_PTR;
    if (Spi_DrvObj.jobObj[DlcEv_pt->JobID_u8].seqObj->numJobsPending > 0U)
    {
        Spi_DrvObj.jobObj[DlcEv_pt->JobID_u8].jobResult = SPI_JOB_OK;
        if (NULL_PTR != Spi_DrvObj.jobObj[DlcEv_pt->JobID_u8].jobCfg.Spi_JobEndNotification)
        {
            Spi_DrvObj.jobObj[DlcEv_pt->JobID_u8].jobCfg.Spi_JobEndNotification();
        }

        temp_hwUnitObj = Spi_getHwUnitObj(Spi_DrvObj.jobObj[DlcEv_pt->JobID_u8].hwUnitObj->hwUnitCfg.hwUnitId);

        if (NULL_PTR != temp_hwUnitObj)
        {
            temp_hwUnitObj->hwUnitResult = SPI_HW_UNIT_OK;
        }
        Spi_DrvStatus = SPI_IDLE;
        Spi_processJobCompletion(
            &Spi_DrvObj.jobObj[DlcEv_pt->JobID_u8],
            &Spi_DrvObj.hwUnitObj[Spi_DrvObj.jobObj[DlcEv_pt->JobID_u8].hwUnitObj->hwUnitCfg.hwUnitId], SPI_JOB_OK);
    }
}

FUNC(void, SPI_CODE) Spi_DlcEnableLpbk(uint8 HwUnit, Spi_LoopbackModeType LbMode)
{
    if (SPI_ANALOG_LPBK == LbMode)
    {
        SPI_SETVAL32(Spi_HWUnit_at[HwUnit]->Spi_IOLPBTSTCR, SPI_ANALOG_LOOPBACK_MASK);
    }
    else
    {
        SPI_CLRVAL32(Spi_HWUnit_at[HwUnit]->Spi_IOLPBTSTCR, SPI_ANALOG_LOOPBACK_MASK);

        SPI_SETVAL32(Spi_HWUnit_at[HwUnit]->Spi_IOLPBTSTCR, SPI_DIGITAL_LOOPBACK_MASK);
    }
}

void Spi_DlcRegisterRdbk(uint8 HwUnit, Spi_RegisterReadbackType *RegRbPtr)
{
    RegRbPtr->Spi_GCR0 = Spi_HWUnit_at[HwUnit]->Spi_GCR0;
    RegRbPtr->Spi_GCR1 = Spi_HWUnit_at[HwUnit]->Spi_GCR1;
    RegRbPtr->Spi_DEF  = Spi_HWUnit_at[HwUnit]->Spi_DEF;
    RegRbPtr->Spi_EN   = Spi_HWUnit_at[HwUnit]->Spi_EN;
}

#define SPI_STOP_SEC_CODE
#include "Spi_MemMap.h"

/**********************************************************************************************************************
 *  END OF FILE: SPI_DLC.C
 **********************************************************************************************************************/
