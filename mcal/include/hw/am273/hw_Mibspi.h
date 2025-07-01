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

#ifndef HW_MIBSPI_H
#define HW_MIBSPI_H
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Spi.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define SPI_DLC_MAJOR_VERSION    (1U)
#define SPI_DLC_MINOR_VERSION    (4U)
#define SPI_DLC_PATCH_VERSION    (0U)

#define SPI_REGISTER_BASE_0      (Spi_RegisterPtrType) (0x02F7E800U)
#define SPI_REGISTER_BASE_1      (Spi_RegisterPtrType) (0x02F7EA00U)
#define SPI_REGISTER_BASE_3      (Spi_RamBufferPtrType) (0x05F7E800U)/*RCSS*/
#define SPI_REGISTER_BASE_4      (Spi_RamBufferPtrType) (0x05F7EA00U)/*RCSS*/

#define SPI_RAM_BASE_0      (Spi_RamBufferPtrType) (0x02000000U) 
#define SPI_RAM_BASE_1      (Spi_RamBufferPtrType) (0x02020000U) 
#define SPI_RAM_BASE_3      (Spi_RamBufferPtrType) (0x05040000U) /* RCSS */
#define SPI_RAM_BASE_4      (Spi_RamBufferPtrType) (0x05060000U) /* RCSS */


/* driver uses no chip select */
#define SPI_NO_CHIP_SELECT    255U

#define SPI_BUF_REG			   ((uint32)0x40U)
/*define for SPIBUF RXEMPTY*/
#define SPI_BUFRXEMPTY_MASK		 ((uint32)0x80000000U)
#define SPI_BUFRXEMPTY_SHIFT     ((uint32)0x1FU)

/* define for SPIFLG */
#define SPI_BUFINIT          ((uint32)1u << 24)

#define SPIFMT_CHARLEN_MASK    (0x1FU)
/*---------------------------------------------------*/
/* MIBRAM Registers */
/*---------------------------------------------------*/
/* Spi_TXRAM register masks, RW                      */
/*---------------------------------------------------*/
#define TXRAMCTRL_DATA        (0x0000U)  /* bit 0-7  */    /* bit 0:15  */
#define TXRAMCTRL_CSNR        (0x0100U)  /* bit 8    */     /* bit 16:23 */
#define TXRAMCTRL_DFSEL       (0x0200U)  /* bit 9    */     /* bit 24:25 */
#define TXRAMCTRL_WDEL        (0x0400U)  /* bit 10   */    /* bit 26    */
#define TXRAMCTRL_LOCK        (0x0800U)  /* bit 11   */    /* bit 27    */
#define TXRAMCTRL_CSHOLD      (0x1000U)  /* bit 12   */    /* bit 28    */
#define TXRAMCTRL_BUFMODE     (0x2000U)  /* bit 13   */    /* bit 29:31 */
/*
 * Spi_RXRAM register masks, R with auto clear
 */
#define RXRAMCTRL_LCSNR         (0x0000U)  /* bit 0-7  */
#define RXRAMCTRL_DLENERR       (0x0100U)  /* bit 8    */
#define RXRAMCTRL_TIMEOUT       (0x0200U)  /* bit 9    */
#define RXRAMCTRL_PARITYERR     (0x0400U)  /* bit 10   */
#define RXRAMCTRL_DESYNC        (0x0800U)  /* bit 11   */
#define RXRAMCTRL_BITERR        (0x1000U)  /* bit 12   */
#define RXRAMCTRL_TXFULL        (0x2000U)  /* bit 13   */
#define RXRAMCTRL_RXOVR         (0x4000U)  /* bit 14   */
#define RXRAMCTRL_RXEMPTY       (0x8000U)  /* bit 15   */
/* special case , if (value & error mask) = 0, everything is fine */
#define RXRAMCTRL_ERRORMASK     0x5F000000U

/* maximum number of bytes for one transfer group */
#define SPI_DLC_TX_RAM_SHIFT    (7U)
/* number of available transfer groups*/
#define SPI_DLC_TG_NUM          (1U)

#define SPI_DLC_TG_LEN          (1U << SPI_DLC_TX_RAM_SHIFT)
/* oneshot mode = 0, time triggered mode = 1 */
#define SPI_DLC_MODE            (STD_OFF)
/* max priority of a job (ASR conform) */
#define SPI_MAX_JOB_PRIO        (3U)
#define SPI_DLC_MAXHWUNIT       (5U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/*---------------------------------------------------*/
/* Register bit mask definitions for MIB registers   */
/*---------------------------------------------------*/
/* naming of the macros is: [REGISTERNAME]_[REGISTERFLAG] */
/* val is the value to be set, bit if available is the bit to set */
/* i.e. TICKCNT_TICKVALUE_SET: set a the TICKCNT register with the TICKVALUE */

/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_WRITEVAL(reg, val)  ((reg) = (val))
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_READVAL(var, reg)   ((var) = (reg))
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_SETVAL16(reg, val)    ((reg) |= (uint16)(val))
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_GETVAL16(reg, mask)   ((reg) &  (uint16)(mask))
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_CLRVAL16(reg, val)    ((reg) &= (~(uint16)(val)))

/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_SETVAL32(reg, val)    ((reg) |= (uint32)(val))
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_GETVAL32(reg, mask)   ((reg) &  (uint32)(mask))
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPI_CLRVAL32(reg, val)    ((reg) &= (~(uint32)(val)))

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TICKCNT register masks, RW */
/*---------------------------------------------------*/
/* set: set a value to the specified register bit */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TICKCNT_TICKVALUE(val)    ((uint32)(val) << 0U)       /* bit 0:15  */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TICKCNT_CLKCTRL(val)      ((uint32)(val) << 28U)      /* bit 28:29 */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TICKCNT_RELOAD(val)       ((uint32)(val) << 30U)      /* bit 30    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TICKCNT_TICKENA(val)      ((uint32)(val) << 31U)      /* bit 31    */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_LTGPEND register masks, RW       */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define LTGPEND_LPEND(val)        ((uint32)(val) << 8U)       /* bit 8:14   */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define LTGPEND_TGINSERVICE(val)  ((uint32)(val) << 24U)      /* bit 24:28  */

/*---------------------------------------------------*/
/* Spi_TGINTVECT[x] register masks, read only        */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGINTVECT_SUSPEND(val)    ((uint32)(val) << 0U)       /* bit 0     */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGINTVECT_INTVEC(val)     ((uint32)(val) << 1U)       /* bit 1:5   */

/*---------------------------------------------------*/
/* Spi_EN register masks, RW                         */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define MIBSPIE_EN(val)           ((uint32)(val) << 0U)       /* bit 0     */

/*---------------------------------------------------*/
/* Spi_GCR1 register masks, RW                       */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define MIBSPIEGCR1_MASTER(val)   ((uint32)(val)<< 0U)       /* bit 0     */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define MIBSPIEGCR1_CLKMOD(val)   ((uint32)(val)<< 1U)       /* bit 1     */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define MIBSPIEGCR1_SPIEN(val)    ((uint32)(val)<< 24U)      /* bit 24    */
#define MIBSPIEGCR1_LOOPBACK(val)    ((uint32)(val)<< 16U)      /* bit 16    */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITENST register masks, RW      */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGITENST_SETINTENRDY(val,bit)    ((uint32)(val) << (bit))      /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITENCR register masks, RW      */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGITENCR_CLRINTENRDY(val,bit)    ((uint32)(val) << (bit))      /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITLVST register masks, RW      */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGITLVST_SETINTLEVEL(val,bit)    ((uint32)(val) << (bit))     /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.Spi_TGITLVCR register masks, RW      */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGITLVCR_SETINTLEVEL(val,bit)    ((uint32)(val) << (bit))      /* bit y from 0:31 */

/*---------------------------------------------------*/
/* Spi_RegTGCTL.TGCTRL register masks, RW      */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_PCURRENT(val)    ((uint32)(val) << 0U)     /* bit 0:6   */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_PSTART(val)      ((uint32)(val) << 8U)     /* bit 8:14  */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_TRIGSRC(val)     ((uint32)(val) << 16U)    /* bit 16:19 */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_TRIGEVT(val)     ((uint32)(val) << 20U)    /* bit 20:23 */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_TGTD(val)        ((uint32)(val) << 28U)    /* bit 28    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_PRST(val)        ((uint32)(val) << 29U)    /* bit 29    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_TGONESHOT(val)   ((uint32)(val) << 30U)    /* bit 30    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define TGCTRL_TGENA(val)       ((uint32)(val) << 31U)    /* bit 31    */

/*---------------------------------------------------*/
/* Spi_RegFMT register masks, RW      */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_CHARLEN(val)    ((uint32)(val) << 0U)     /* bit 0:4   */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_PRESCALE(val)   ((uint32)(val) << 8U)     /* bit 8:15  */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_PHASE(val)      ((uint32)(val) << 16U)    /* bit 16    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_POLARITY(val)   ((uint32)(val) << 17U)    /* bit 17    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_DISCSTIMER(val) ((uint32)(val) << 18U)    /* bit 18    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_SHIFTDIR(val)   ((uint32)(val) << 20U)    /* bit 20    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_WAITENA(val)    ((uint32)(val) << 21U)    /* bit 21    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_PARITYENA(val)  ((uint32)(val) << 22U)    /* bit 22    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_PARPOL(val)     ((uint32)(val) << 23U)    /* bit 23    */
/*LDRA_INSPECTED 340 S MR:19.7 Reason : "Register operations" */
#define SPIFMT_WDELAY(val)     ((uint32)(val) << 24U)    /* bit 24:29 */

/*---------------------------------------------------*/
/* get, set: low/high word of a uint32               */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_LOWWORD_SET(val)     (((uint32)(val) & 0x0000FFFFU) << 0U)   /* bit 0:15   */
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_HIGHWORD_SET(val)    (((uint32)(val) & 0x0000FFFFU) << 16U)  /* bit 16:31  */

/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_LOWWORD_GET(val)     (uint16)(((uint32)(val) & 0x0000FFFFU))   /* bit 0:15   */
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_HIGHWORD_GET(val)    (uint16)(((uint32)(val) & 0xFFFF0000U) >> 16U)  /* bit 16:31  */

/*---------------------------------------------------*/
/* for tx control field                              */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_TXCTRL_BUFMOD(val)    (uint16) ((val) << 13U)
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_TXCTRL_CSHOLD(val)    (uint16) ((val) << 12U)
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_TXCTRL_DFSEL(val)     (uint16) ((val) << 8U)

/*---------------------------------------------------*/
/* get, set: low/high byte of a uint16               */
/*---------------------------------------------------*/
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_LOWBYTE_SET(val)     (uint16)(((uint32)(val) & (uint32)0x00FFU) << 0U)  /* bit 0:7   */
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_HIGHBYTE_SET(val)    (uint16)(((uint32)(val) & (uint32)0x00FFU) << 8U)  /* bit 8:15  */

/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_LOWBYTE_GET(val)     ((uint8)(((uint32)(val) & (uint32)0x00FFU)))       /* bit 0:8   */
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_HIGHBYTE_GET(val)    ((uint8)(((uint32)(val) & (uint32)0xFF00U) >> 8U)) /* bit 8:15  */

/* define bit masks */
#define SPI_DLC_BITCLR    0x00000000U
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_CHECK_BIT08(val,bit)  ((uint8) (val) & (1U << (bit))) == (1U << (bit))
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_CHECK_BIT16(val,bit)  ((uint16)(val) & (1U << (bit))) == (1U << (bit))
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_CHECK_BIT32(val,bit)  ((uint32)(val) & (1U << (bit))) == (1U << (bit))
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_CHECK_HEX08(val,bval) (((uint8) (val) & (bval)) == (bval))
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_CHECK_HEX16(val,bval) (((uint16)(val) & (bval)) == (bval))
/*LDRA_INSPECTED 340 S MR:19.7 <INSPECTED> "Register handling macros*/
#define SPI_DLC_CHECK_HEX32(val,bval) (((uint32)(val) & (bval)) == (bval))

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* type for Register Readback */
typedef enum
{
    SPI_GCR0_RB = 0U,
    SPI_GCR1_RB,
    SPI_DEF_RB,
    SPI_EN_RB
} Spi_DlcRegRdbkType;

typedef struct
{
    volatile uint32 Spi_FMT[4U] ;
} Spi_FMTRegType;

typedef P2CONST(Spi_HWUnitPropertyType, AUTOMATIC, SPI_CONST) Spi_HWUnitPropertyPtrType;

typedef struct
{
    Spi_RegisterPtrType Reg_pt;        /* pointer to unit registers */
    Spi_RamBufferPtrType Ram_pt;       /* pointer to unit ram (NULL_PTR) if unit has no ram */
    Spi_HWUnitPropertyPtrType Prop_pt; /* pointer to unit properties */
}Spi_HWUnitMapType;

typedef P2VAR(Spi_HWUnitMapType, AUTOMATIC, SPI_VAR_NOINIT) Spi_HWUnitMapPtrType;

/* state for guard operations */
enum
{
    SPI_DLC_G_IDLE = 0U,
    SPI_DLC_G_PENDING = 1U,
    SPI_DLC_G_ACTIVE = 2U,
    SPI_DLC_G_FINISHED = 3U
};

typedef enum
{
    SPI_DLC_TX = 0U,
    SPI_DLC_RX = 1U
}Spi_DlcTxRxDefType;

typedef enum
{
    SPI_DLC_FRAME08 = 0U,
    SPI_DLC_FRAME16 = 1U
}Spi_DlcFrameDefType;

typedef enum
{
    SPI_DLC_STDUNIT = 0U,
    SPI_DLC_MIBUNIT = 1U
}Spi_DlcOptionDefType;

/* event definitions of the spi job state machine */
typedef enum
{
    SPI_DLC_EV_SYNCTX = 0U,
    SPI_DLC_EV_ASYNCTX = 1U,
    SPI_DLC_EV_CONSUMED = 2U
} Spi_DlcEventDefType;

typedef enum
{
    SPI_DLC_ST_OK = 0U,
    SPI_DLC_ST_PENDING = 1U,
    SPI_DLC_ST_FAILED = 2U,
    SPI_DLC_ST_FINISHED = 3U,
    SPI_DLC_ST_CANCELED = 4U
}Spi_DlcChannelStateType;

typedef  P2FUNC(void, SPI_CODE ,Dlcfunc)(uint32 HwUnit_u32);
typedef P2FUNC(uint16, SPI_CODE , DlcfuncTransmit)(uint32 HwUnit_u32);

typedef struct
{
    Dlcfunc Init;
    Dlcfunc Close;
    Dlcfunc FillData;
    Dlcfunc DrainData;
    Dlcfunc Trigger;
    DlcfuncTransmit Transmit;
    Dlcfunc Error;
}Spi_DlcFunctionType;


/* event object definitions of the spi job state machine */
typedef struct
{
    /* the first three entries are part of the Interface and shall not be changed */
    volatile uint8 Event_u8;
    volatile uint8 Guard_u8 ;  /* used for fill status of buffer*/
    uint8  JobID_u8 ;      /* ID of the job */
    uint8  Res_u8   ;      /* dummy */

    uint16 Pos_u16[2U] ;   /* position in a channel [0=Tx, 1=Rx] */
    uint8  ID_u8[2U]  ;    /* ID of the Channel [0=Tx, 1=Rx] */
    uint8  Num_u8[2U] ;    /* number of Channels [0=Tx, 1=Rx] */

    uint16 TxCtrl_u16 ;    /* for transmit control */
    uint16 RxStat_u16 ;    /* for receive status   */
    uint16 Default_u16[2U]; /* default data */
    uint16 Data_u16;       /* valid data */
    uint8  DFSel_u8[2U] ;   /* data format word [0=CS_ID ,1=ExtDev]*/
} Spi_DlcEventType;

typedef P2VAR(Spi_DlcEventType, AUTOMATIC, SPI_VAR) Spi_DlcEventPtrType;
typedef uint32 Spi_DlcInstType;
typedef uint32 Spi_DlcIsrType;

/* pointer types for 8, 16 bit frame transfer */
typedef P2VAR(uint8, AUTOMATIC,  SPI_APPL_DATA) Spi_DlcFrame8PtrType;
typedef P2VAR(uint16, AUTOMATIC, SPI_APPL_DATA) Spi_DlcFrame16PtrType;

/* type for LoopbackMode */
typedef enum
{
    SPI_DIGITAL_LPBK = 0U,
    SPI_ANALOG_LPBK = 1U
} Spi_LoopbackModeType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* common platform interface */
FUNC(void, SPI_CODE) Spi_DlcInit(void) ;
FUNC(void, SPI_CODE) Spi_DlcClose(void) ;
FUNC(Spi_JobResultType, SPI_CODE) Spi_DlcSetEvent
(
    P2CONST(Spi_DlcEventType, AUTOMATIC, SPI_VAR_NOINIT) Dlc_Event_pt
);
/*LDRA_INSPECTED 63 D : MISRAC_2012_R8.6
    Reason : ISR function used in case of MibSPI */
FUNC(void, SPI_CODE) Spi_IrqTxRxERR(uint32 HwUnit_u32) ;
/*LDRA_INSPECTED 63 D : MISRAC_2012_R8.6
    Reason : ISR function used in case of MibSPI */
FUNC(void, SPI_CODE) Spi_IrqTxRx(uint32 HwUnit_u32) ;

/*LDRA_INSPECTED 63 D : MISRAC_2012_R8.6
    Reason : loopback function used in case of MibSPI */
FUNC(void, SPI_CODE) Spi_DlcEnableLpbk(uint8 HwUnit, Spi_LoopbackModeType LbMode);
/*LDRA_INSPECTED 63 D : MISRAC_2012_R8.6
    Reason : loopback function used in case of MibSPI */
FUNC(void, SPI_CODE) Spi_DlcDisableLpbk(uint8 HwUnit);

FUNC(void, SPI_CODE) Spi_DlcRegisterRdbk(uint8 HwUnit, Spi_RegisterReadbackType *RegRbPtr);

#endif /* HW_MIBSPI_H*/

/**********************************************************************************************************************
 *  END OF FILE: hw_Mibspi.h
 *********************************************************************************************************************/
