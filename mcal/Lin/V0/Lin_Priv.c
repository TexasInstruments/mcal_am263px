/*********************************************************************************************************************
 *  COPYRIGHT
 *  ------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *                 Property of Texas Instruments, Unauthorized reproduction and/or distribution
 *                 is strictly prohibited.  This product  is  protected  under  copyright  law
 *                 and  trade  secret law as an  unpublished work.
 *                 (C) Copyright 2022 Texas Instruments Inc.  All rights reserved.
 *
 *  \endverbatim
 *  ------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------
 *  File:       Lin_Priv.c
 *  Project:    AM263x MCAL
 *  Module:     Lin Driver
 *  Generator:  None
 *
 *  Description:  This file contains controller dependent local functions and private functions
 *                to be used in Lin.c.
 *
 *--------------------------------------------------------------------------------------------------------------------
 * Author:  Piyush Panditrao
 *--------------------------------------------------------------------------------------------------------------------
 * Revision History (top to bottom: first revision to last revision)
 *--------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *--------------------------------------------------------------------------------------------------------------------
 * 00.01.00       11Nov2012    Author's name        0000000000000    Initial version
 *
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Standard Header Files
 *********************************************************************************************************************/
#include "Lin.h"

/*********************************************************************************************************************
 * Other Header Files
 *********************************************************************************************************************/
#include "Lin_Priv.h"

/*********************************************************************************************************************
 * Version Check (if required)
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Preprocessor #define Constants
 *********************************************************************************************************************/
/** \brief  LIN IO DFT Key which when written in IODFTENA
 *          enables the User and Previledge mode Writes */
#define LIN_IO_DFT_KEY (0xAU)

/** \brief  LIN/SCI Wakeup signal is sent by sending an
 *          byte with value 0xF0 */
#define LIN_WAKEUP_KEY (0xF0U)

/** \brief  LIN/SCI Go To Sleep signal is sent by sending
 * commander request frame with identifier 0x3C (60),
 * with the first data field as 0x00 */
#define LIN_GOTOSLEEP_TD0KEY (0x00FFFFFFU)
#define LIN_GOTOSLEEP_TD1KEY (0xFFFFFFFFU)

/** \brief  Max data length of the LIN SDU */
#define LIN_MAX_DATA_LENGTH (8U)
/*********************************************************************************************************************
 * Local Preprocessor #define Macros
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Type Declarations
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Exported Object Definitions
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * Local Object Definitions
 *********************************************************************************************************************/
#define LIN_START_SEC_VAR_INIT_UNSPECIFIED
#include "Lin_MemMap.h"
STATIC P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_CONST) Lin_Drv_Config_Ptr = (Lin_ConfigType *)NULL_PTR;
#define LIN_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Lin_MemMap.h"

#define LIN_START_SEC_VAR_NO_INIT_8
#include "Lin_MemMap.h"
STATIC VAR(uint8, LIN_VAR) Lin_RxShadowBuffer[LIN_MAX_CHANNEL][LIN_MAX_DATA_LENGTH];
#define LIN_STOP_SEC_VAR_NO_INIT_8
#include "Lin_MemMap.h"

/*********************************************************************************************************************
 *  Local Function Prototypes
 *********************************************************************************************************************/
#define LIN_START_SEC_CODE
#include "Lin_MemMap.h"

/**
 * \brief   This API will disable Lin HW Unit.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_DisableHWUnit(uint32 base);

/**
 * \brief   This API will enable Lin HW Unit.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_EnableHWUnit(uint32 base);

/**
 * \brief   This API will make Lin enter software reset mode.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_EnterSoftwareReset(uint32 base);

/**
 * \brief   This API will make Lin exit software reset mode.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_ExitSoftwareReset(uint32 base);

/**
 * \brief   This API will configure the HW unit to run in Lin mode.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetLinMode(uint32 base);

/**
 * \brief   This API will configure Sync Field values.
 *
 * \param   base      Base address of Lin Instance.+
 * \param   syncBreak      Value of Sync Break to be configured
 * \param   delimiter      Value of delimiter to be configured
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetSyncFields(uint32 base, uint16 syncBreak, uint16 delimiter);

/**
 * \brief   This API will configure Tx mask for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   mask     Mask value to be configured
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetTxMask(uint32 base, uint16 mask);

/**
 * \brief   This API will configure Rx mask for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   mask     Mask value to be configured
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetRxMask(uint32 base, uint16 mask);

/**
 * \brief   This API will configure baudrate for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   baudrateConfig     Pointer to baudrate config
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE)
    Lin_SetBaudrateConfig(uint32 base, P2CONST(Lin_BaudRateConfigType, AUTOMATIC, LIN_APPL_CONST) baudrateConfig);

/**
 * \brief   This API will set framelength for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   length     Length of frame
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetFrameLength(uint32 base, uint16 length);

/**
 * \brief   This API will set checksum type for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   type     Type of checksum to be configured
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetChecksumType(uint32 base, Lin_FrameCsModelType type);

/**
 * \brief   This API will set ID byte type for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   identifier     ID Type to be configured.
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetIDByte(uint32 base, Lin_FramePidType identifier);

/**
 * \brief   This API will enable interrupts for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   intrLineNum    Interrupt line to be selected
 * \param   intFlags    Interrupts to be selected
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_EnableInterrupt(uint32 base, Lin_InterruptLineNum intrLineNum, uint32 intFlags);

/**
 * \brief   This API will disable interrupts for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   intFlags    Interrupts to be selected
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_DisableInterrupt(uint32 base, uint32 intFlags);

/**
 * \brief   This API will enable Transmit and Recieve bits for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 *
 * \return  None.
 *
 **/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetTxRxEnable(uint32 base);

/**
 *  \brief  Gets the Interrupt Vector Offset for Line 0
 *
 *  \param base is the LIN module base address
 *
 *  In LIN and SCI mode, this function gets the offset for interrupt line 0.
 *  A read to the specified line register updates its value to the next highest
 *  priority pending interrupt in the flag register and clears the flag
 *  corresponding to the offset that was read.
 *
 *  \note The flags for the receive and the transmit interrupts cannot be
 *  cleared by reading the corresponding offset vector in this function.
 *
 *  The following are values that can be returned:
 *  - \b LIN_VECT_NONE    - No Interrupt
 *  - \b LIN_VECT_WAKEUP  - Wakeup
 *  - \b LIN_VECT_ISFE    - Inconsistent-sync-field Error
 *  - \b LIN_VECT_PE      - Parity Error
 *  - \b LIN_VECT_ID      - ID Interrupt
 *  - \b LIN_VECT_PBE     - Physical Bus Error
 *  - \b LIN_VECT_FE      - Frame Error
 *  - \b LIN_VECT_BREAK   - Break detect
 *  - \b LIN_VECT_CE      - Checksum Error
 *  - \b LIN_VECT_OE      - Overrun Error
 *  - \b LIN_VECT_BE      - Bit Error
 *  - \b LIN_VECT_RX      - Receive Interrupt
 *  - \b LIN_VECT_TX      - Transmit Interrupt
 *  - \b LIN_VECT_NRE     - No-response Error
 *  - \b LIN_VECT_TOAWUS  - Timeout after wakeup signal
 *  - \b LIN_VECT_TOA3WUS - Timeout after 3 wakeup signals
 *  - \b LIN_VECT_TO      - Timeout (Bus Idle)
 *
 *  \return Returns the value of the interrupt level register.
 *
 */
LOCAL_INLINE FUNC(uint16, LIN_CODE) LIN_getInterruptLine0Offset(uint32 base);

/**
 *  \brief  Gets the Interrupt Vector Offset for Line 1
 *
 *  \param base is the LIN module base address
 *
 *  In LIN and SCI mode, this function gets the offset for interrupt line 1.
 *  A read to the specified line register updates its value to the next highest
 *  priority pending interrupt in the flag register and clears the flag
 *  corresponding to the offset that was read.
 *
 *  \note The flags for the receive and the transmit interrupts cannot be
 *  cleared by reading the corresponding offset vector in this function.
 *
 *  The following are values that can be returned:
 *  - \b LIN_VECT_NONE    - No Interrupt
 *  - \b LIN_VECT_WAKEUP  - Wakeup
 *  - \b LIN_VECT_ISFE    - Inconsistent-sync-field Error
 *  - \b LIN_VECT_PE      - Parity Error
 *  - \b LIN_VECT_ID      - ID Interrupt
 *  - \b LIN_VECT_PBE     - Physical Bus Error
 *  - \b LIN_VECT_FE      - Frame Error
 *  - \b LIN_VECT_BREAK   - Break detect
 *  - \b LIN_VECT_CE      - Checksum Error
 *  - \b LIN_VECT_OE      - Overrun Error
 *  - \b LIN_VECT_BE      - Bit Error
 *  - \b LIN_VECT_RX      - Receive Interrupt
 *  - \b LIN_VECT_TX      - Transmit Interrupt
 *  - \b LIN_VECT_NRE     - No-response Error
 *  - \b LIN_VECT_TOAWUS  - Timeout after wakeup signal
 *  - \b LIN_VECT_TOA3WUS - Timeout after 3 wakeup signals
 *  - \b LIN_VECT_TO      - Timeout (Bus Idle)
 *
 *  \return Returns the interrupt vector offset for interrupt line 1.
 *
 */
LOCAL_INLINE FUNC(uint16, LIN_CODE) LIN_getInterruptLine1Offset(uint32 base);

/** \brief Lin_ServiceInterrupts - This API will Service Lin interrupts for selected Interrupt line
 *and will clear the interrupt flags.
 *
 * \param base      Base address of Lin Instance.
 * \param int_line      Interrupt line
 *
 * \return None
 *
 *
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_ServiceInterrupts(uint32 base, Lin_InterruptLineNum int_line);

/**
 * \brief   This API will set loopback mode for Lin instance.
 *
 * \param   base      Base address of Lin Instance.
 * \param   loopbackMode    Loopback mode to be selected
 *
 * \return  None.
 *
 **/
STATIC FUNC(void, LIN_CODE) Lin_SetLoopbackMode(uint32 base, Lin_LoopbackModeType loopbackMode);

/*********************************************************************************************************************
 *  External Functions Definition
 *********************************************************************************************************************/
FUNC(Std_ReturnType, LIN_CODE) Lin_HwUnitConfig(P2CONST(Lin_ChannelType, AUTOMATIC, LIN_APPL_DATA) linChannel)
{
    VAR(uint32, AUTOMATIC) lin_cnt_base_addr    = linChannel->linControllerConfig.CntrAddr;
    VAR(Std_ReturnType, AUTOMATIC) return_value = (Std_ReturnType)E_NOT_OK;

    if ((linChannel->linBaudConfig.BaudRate >= (uint32)1000U) && (linChannel->linBaudConfig.BaudRate <= (uint32)20000U))
    {
        /* Reset LIN HW Unit */
        Lin_DisableHWUnit(lin_cnt_base_addr);
        Lin_EnableHWUnit(lin_cnt_base_addr);

        /* Enter Software Reset State */
        Lin_EnterSoftwareReset(lin_cnt_base_addr);

        /* Enable Lin Mode and configure as Master Node */
        Lin_SetLinMode(lin_cnt_base_addr);

        /* Set Loopback Mode */
        Lin_SetLoopbackMode(lin_cnt_base_addr, linChannel->linControllerConfig.LoopbackMode);

        /* Set Baudrate */
        Lin_SetBaudrateConfig(lin_cnt_base_addr, &linChannel->linBaudConfig);

        /*
         * Configure sync field
         * Sync break (13 + 5 = 18 Tbits)
         * Sync delimiter (1 + 3 = 4 Tbits)
         */
        Lin_SetSyncFields(lin_cnt_base_addr, 5U, 3U);

        /* Exit Software Reset State */
        Lin_ExitSoftwareReset(lin_cnt_base_addr);
        return_value = E_OK;
    }
    else
    {
        /* Do Nothing. Return E_NOT_OK */
    }

    return return_value;
}

FUNC(void, LIN_CODE) Lin_SetDriverCfgPtr(P2CONST(Lin_ConfigType, AUTOMATIC, LIN_APPL_DATA) drvObj)
{
    Lin_Drv_Config_Ptr = drvObj;
}

FUNC(Std_ReturnType, LIN_CODE)
Lin_SendData(P2CONST(Lin_ChannelType, AUTOMATIC, LIN_APPL_DATA) linChannel,
             P2VAR(Lin_ChannelActivityStatusType, AUTOMATIC, LIN_APPL_DATA) linChannelActivityStatus,
             P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) pduInfoPtr)
{
    uint32         lin_cnt_base_addr = linChannel->linControllerConfig.CntrAddr;
    uint8         *p_data            = (uint8 *)NULL_PTR;
    uint8          length            = pduInfoPtr->Dl;
    sint8          i                 = 0;
    Std_ReturnType return_value      = E_NOT_OK;

    if (LIN_CHANNEL_IDLE != *linChannelActivityStatus)
    {
        Lin_AbortTransmission(lin_cnt_base_addr);
        *linChannelActivityStatus = LIN_CHANNEL_IDLE;
    }
    else
    {
        /* Do Nothing */
    }

    /* Set Checksum Type*/
    Lin_SetChecksumType(lin_cnt_base_addr, pduInfoPtr->Cs);

    if (LIN_MASTER_RESPONSE == pduInfoPtr->Drc)
    {
        /* Enable transmit bit. */
        HW_WR_REG32_RAW((lin_cnt_base_addr + CSL_LIN_SCIGCR1),
                        HW_RD_REG32_RAW(lin_cnt_base_addr + CSL_LIN_SCIGCR1) | CSL_LIN_SCIGCR1_TXENA_MASK);

        /* Enable receive bit. */
        HW_WR_REG32_RAW((lin_cnt_base_addr + CSL_LIN_SCIGCR1),
                        HW_RD_REG32_RAW(lin_cnt_base_addr + CSL_LIN_SCIGCR1) | CSL_LIN_SCIGCR1_RXENA_MASK);

        /* Set Mask ID for TX */
        Lin_SetTxMask(lin_cnt_base_addr, pduInfoPtr->Pid);

        /* Set Mask ID for RX to not accept any message as we don't need to read the message */
        Lin_SetRxMask(lin_cnt_base_addr, 0x00U);

        /*
         * Set the message ID to initiate a header transmission.
         * This causes the ID to be written to the bus followed by the
         * data in the transmit buffers.
         */
        Lin_SetIDByte(lin_cnt_base_addr, pduInfoPtr->Pid);
        /*
         * Set the frame length (number of bytes to be transmitted)
         */
        Lin_SetFrameLength(lin_cnt_base_addr, length);

        p_data = ((uint8 *)pduInfoPtr->SduPtr + length);

        /* Shift each 8-bit piece of data into the correct register. */
        for (i = length; i >= 0; i--)
        {
            HW_WR_REG8_RAW(lin_cnt_base_addr + CSL_LIN_LINTD0 + ((uint8)i ^ 3U), *p_data);
            p_data--;
        }

        *linChannelActivityStatus = LIN_CHANNEL_TX_STARTED;
        return_value              = E_OK;
    }
    else if (LIN_SLAVE_RESPONSE == pduInfoPtr->Drc)
    {
        /* Enable transmit bit. */
        HW_WR_REG32_RAW((lin_cnt_base_addr + CSL_LIN_SCIGCR1),
                        HW_RD_REG32_RAW(lin_cnt_base_addr + CSL_LIN_SCIGCR1) | CSL_LIN_SCIGCR1_TXENA_MASK);

        /* Enable receive bit. */
        HW_WR_REG32_RAW((lin_cnt_base_addr + CSL_LIN_SCIGCR1),
                        HW_RD_REG32_RAW(lin_cnt_base_addr + CSL_LIN_SCIGCR1) | CSL_LIN_SCIGCR1_RXENA_MASK);

        /*
         * Set the frame length (number of bytes to be received)
         */
        Lin_SetFrameLength(lin_cnt_base_addr, length);

        /* Set Mask ID for TX to not Send any message*/
        Lin_SetTxMask(lin_cnt_base_addr, 0x00U);

        /* Set Mask ID for RX */
        Lin_SetRxMask(lin_cnt_base_addr, pduInfoPtr->Pid);

        /*
         * Set the message ID to initiate a header transmission.
         * This causes the ID to be written to the bus followed by the
         * data in the transmit buffers.
         */
        Lin_SetIDByte(lin_cnt_base_addr, pduInfoPtr->Pid);

        *linChannelActivityStatus = LIN_CHANNEL_RX_STARTED;
        return_value              = E_OK;
    }
    else
    {
        /* Enable transmit bit. */
        HW_WR_REG32_RAW((lin_cnt_base_addr + CSL_LIN_SCIGCR1),
                        HW_RD_REG32_RAW(lin_cnt_base_addr + CSL_LIN_SCIGCR1) | CSL_LIN_SCIGCR1_TXENA_MASK);

        /* Enable receive bit. */
        HW_WR_REG32_RAW((lin_cnt_base_addr + CSL_LIN_SCIGCR1),
                        HW_RD_REG32_RAW(lin_cnt_base_addr + CSL_LIN_SCIGCR1) | CSL_LIN_SCIGCR1_RXENA_MASK);

        /* Set Mask ID for RX to not accept any message as we don't need to read the message */
        Lin_SetRxMask(lin_cnt_base_addr, 0x00U);

        /*
         * Set the message ID to initiate a header transmission.
         * This causes the ID to be written to the bus followed by the
         * data in the transmit buffers.
         */
        Lin_SetIDByte(lin_cnt_base_addr, pduInfoPtr->Pid);

        return_value = E_OK;
    }

    return return_value;
}

FUNC(void, LIN_CODE)
Lin_GetData(uint32 channelID, uint32 base, P2VAR(uint8 *, AUTOMATIC, LIN_APPL_CONST) sduPtr)
{
    uint8  i;
    uint32 length;

    /* Set Sdu pointer to the address of corresponding shadow buffer */
    *sduPtr = Lin_RxShadowBuffer[channelID];

    /* Get the length from the SCIFORMAT register. */
    length =
        ((HW_RD_REG32_RAW(base + CSL_LIN_SCIFORMAT) & CSL_LIN_SCIFORMAT_LENGTH_MASK) >> CSL_LIN_SCIFORMAT_LENGTH_SHIFT);

    /* Read each 8-bit piece of data. */
    for (i = 0U; i <= length; i++)
    {
        Lin_RxShadowBuffer[channelID][i] = HW_RD_REG8_RAW(base + CSL_LIN_LINRD0 + ((uint32)i ^ 3U));
    }
}

FUNC(Lin_StatusType, LIN_CODE) Lin_FetchTxStatus(uint32 base)
{
    Lin_StatusType return_value = LIN_TX_BUSY;
    uint32         reg_val      = HW_RD_REG32_RAW(base + CSL_LIN_SCIFLR);

    if (((reg_val & CSL_LIN_SCIFLR_PBE_MASK) == CSL_LIN_SCIFLR_PBE_MASK))
    {
        return_value = LIN_TX_HEADER_ERROR;
    }
    else if ((reg_val & CSL_LIN_SCIFLR_BE_MASK) == CSL_LIN_SCIFLR_BE_MASK)
    {
        return_value = LIN_TX_ERROR;
    }
    else if ((reg_val & CSL_LIN_SCIFLR_TXEMPTY_MASK) == CSL_LIN_SCIFLR_TXEMPTY_MASK)
    {
        return_value = LIN_TX_OK;
    }
    else
    {
        /* Do Nothing */
    }

    /* Clear status bits after read */
    HW_WR_REG32_RAW((base + CSL_LIN_SCIFLR), reg_val);

    return return_value;
}

FUNC(Lin_StatusType, LIN_CODE) Lin_FetchRxStatus(uint32 base)
{
    Lin_StatusType return_value = LIN_RX_BUSY;
    uint32         reg_val      = HW_RD_REG32_RAW(base + CSL_LIN_SCIFLR);

    if ((reg_val & CSL_LIN_SCIFLR_NRE_MASK) == CSL_LIN_SCIFLR_NRE_MASK)
    {
        return_value = LIN_RX_NO_RESPONSE;
    }
    else if (((reg_val & CSL_LIN_SCIFLR_CE_MASK) == CSL_LIN_SCIFLR_CE_MASK) ||
             ((reg_val & CSL_LIN_SCIFLR_OE_MASK) == CSL_LIN_SCIFLR_OE_MASK) ||
             ((reg_val & CSL_LIN_SCIFLR_PE_MASK) == CSL_LIN_SCIFLR_PE_MASK))
    {
        return_value = LIN_RX_ERROR;
    }
    else if ((reg_val & CSL_LIN_SCIFLR_RXRDY_MASK) == CSL_LIN_SCIFLR_RXRDY_MASK)
    {
        return_value = LIN_RX_OK;
    }
    else
    {
        /* Do Nothing */
    }

    /* Clear status bits after read */
    HW_WR_REG32_RAW((base + CSL_LIN_SCIFLR), reg_val);

    return return_value;
}

FUNC(void, LIN_CODE) Lin_SendWakeupSignal(uint32 base)
{
    /* Set key in Byte 0 (MSB) of transmit buffer 0 register */
    HW_WR_FIELD32_RAW((base + CSL_LIN_LINTD0), CSL_LIN_LINTD0_TD0_MASK, CSL_LIN_LINTD0_TD0_MASK,
                      (uint16)LIN_WAKEUP_KEY);

    /* Transmit TDO for wakeup */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR2), CSL_LIN_SCIGCR2_GENWU_MASK, CSL_LIN_SCIGCR2_GENWU_SHIFT, TRUE);
}

FUNC(void, LIN_CODE) Lin_EnterLowPowerMode(uint32 base, boolean enable)
{
    /* Entering Powerdown */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR2), CSL_LIN_SCIGCR2_POWERDOWN_MASK, CSL_LIN_SCIGCR2_POWERDOWN_SHIFT,
                      enable);
}

FUNC(boolean, LIN_CODE) Lin_CheckWakeupStatus(uint32 base)
{
    boolean wakeup_status =
        ((HW_RD_REG32_RAW(base + CSL_LIN_SCIGCR2) & CSL_LIN_SCIGCR2_POWERDOWN_MASK) != CSL_LIN_SCIGCR2_POWERDOWN_MASK);

    /* Clear wakeup */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIFLR_WAKEUP_MASK, CSL_LIN_SCIFLR_WAKEUP_SHIFT, TRUE);

    return wakeup_status;
}

FUNC(void, LIN_CODE) Lin_AbortTransmission(uint32 base)
{
    /* NOTE: Current Lin IP doesn't support aborting communication once message transmission /
     * reception is started. */

    /* Disable transmit bit. */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_TXENA_MASK, CSL_LIN_SCIGCR1_TXENA_SHIFT, FALSE);

    /* Disable receive bit. */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_RXENA_MASK, CSL_LIN_SCIGCR1_RXENA_SHIFT, FALSE);
}

FUNC(void, LIN_CODE)
Lin_EnableWakeupDetection(P2CONST(Lin_ChannelType, AUTOMATIC, LIN_APPL_CONST) linChannel, boolean enable)
{
    if (TRUE == enable)
    {
        Lin_EnableInterrupt(linChannel->linControllerConfig.CntrAddr, linChannel->linControllerConfig.IntrLineNum,
                            LIN_INT_WAKEUP);
    }
    else
    {
        Lin_DisableInterrupt(linChannel->linControllerConfig.CntrAddr, LIN_INT_WAKEUP);
    }
}

FUNC(void, LIN_CODE) Lin_ProcessISR(uint32 channelID)
{
    uint32               lin_cnt_base_addr = Lin_Drv_Config_Ptr->linChannelCfg[channelID].linControllerConfig.CntrAddr;
    Lin_InterruptLineNum int_line = Lin_Drv_Config_Ptr->linChannelCfg[channelID].linControllerConfig.IntrLineNum;

    if ((TRUE == Lin_Drv_Config_Ptr->linChannelCfg[channelID].linChannelWakeupSupport) &&
        (((HW_RD_REG32_RAW(lin_cnt_base_addr + CSL_LIN_SCIFLR) & CSL_LIN_SCIFLR_WAKEUP_MASK) ==
          CSL_LIN_SCIFLR_WAKEUP_MASK)))
    {
        /* Come out of low power mode */
        Lin_EnterLowPowerMode(lin_cnt_base_addr, FALSE);

        /* Service Interrupt */
        Lin_ServiceInterrupts(lin_cnt_base_addr, int_line);

        /* Notify EcuM */
        EcuM_CheckWakeup(Lin_Drv_Config_Ptr->linChannelCfg[channelID].linWakeupSource);
    }
    else
    {
        /* Do Nothing */
    }
}

FUNC(Std_ReturnType, LIN_CODE) Lin_WakeupProcess(uint8 linChannel, Lin_ChannelStatusType *lindrvr_Channel_Status)
{
    Std_ReturnType ret_value          = E_NOT_OK;
    uint32         lin_base_cntr_addr = Lin_Drv_Config_Ptr->linChannelCfg[linChannel].linControllerConfig.CntrAddr;

    /* Perform LIN channel Wakeup, only if LIN Channel is not in operational state */
    if ((uint8)LIN_CHANNEL_OPERATIONAL != lindrvr_Channel_Status->linChannelNetworkStatus)
    {
        /* Disable Low Power Mode */
        Lin_EnterLowPowerMode(lin_base_cntr_addr, FALSE);
        /* Set LIN Channel to operational state */
        lindrvr_Channel_Status->linChannelNetworkStatus = LIN_CHANNEL_OPERATIONAL;
        /* Set Mask ID for TX to not Send any message*/
        Lin_SetTxMask(lin_base_cntr_addr, 0x00U);

        /* Enable transmit and receive bits. */
        Lin_SetTxRxEnable(lin_base_cntr_addr);

        /* Set Mask ID for RX */
        Lin_SetRxMask(lin_base_cntr_addr, 0x00U);

        /*
         * Set the message ID to initiate a header transmission.
         * This causes the ID to be written to the bus followed by the
         * data in the transmit buffers.
         */
        Lin_SetIDByte(lin_base_cntr_addr, LIN_WAKEUP_ID);

        ret_value = E_OK;
    }
    else
    {
        /* Do Nothing */
    }
    return (ret_value);
}

/*
 * Design : MCAL-25680
 */
FUNC(Std_ReturnType, LIN_CODE) Lin_SendGoToSleepSignal(uint32 base)
{
    Std_ReturnType return_value = E_NOT_OK;
#ifdef LIN_TIMEOUT_DURATION
    VAR(uint32, AUTOMATIC) timeout_duration = LIN_TIMEOUT_DURATION;
#endif

    /* Enable transmit and receive bits. */
    Lin_SetTxRxEnable(base);

    /* Set Mask ID for TX for GoToSleep Command*/
    Lin_SetTxMask(base, 0x3CU);

    /* Set Mask ID for RX to not accept any message as we don't need to read the message */
    Lin_SetRxMask(base, 0x00U);

    /*
     * Set the frame length (number of bytes to be transmitted)
     */
    Lin_SetFrameLength(base, 0x8U);

    /* Set key in Byte 0 (MSB) of transmit buffer 0 register
     * For Go to Sleep Command, the first Byte should be 0 and remaining byte Should be 0xFF
     */
    HW_WR_REG32((base + CSL_LIN_LINTD1), (uint32)LIN_GOTOSLEEP_TD1KEY);
    HW_WR_REG32((base + CSL_LIN_LINTD0), (uint32)LIN_GOTOSLEEP_TD0KEY);
    /*
     * Set the message ID as 60 OR 0x3C to initiate a header transmission.
     * This causes the ID to be written to the bus followed by the
     * data in the transmit buffers.
     */
    Lin_SetIDByte(base, 0x3CU);

#ifdef LIN_TIMEOUT_DURATION
    while (timeout_duration > 0U)
    {
        regVal = HW_RD_REG32(base + CSL_LIN_SCIFLR);
        if ((regVal & LIN_CSL_LIN_SCIFLR_TXEMPTY_MASK) == LIN_SCIFLR_TXEMPTY)
        {
            return_value = E_OK;
            break;
        }
        else
        {
            // McalLib_Delay(LIN_MCAL_LIB_DELAY);
            timeout_duration--;
            /* Wait for TX Ready flag */
        }
    }
#else
    return_value = E_OK;
#endif

    return return_value;
}
/*********************************************************************************************************************
 *  Local Functions Definition
 *********************************************************************************************************************/
LOCAL_INLINE FUNC(void, LIN_CODE) Lin_DisableHWUnit(uint32 base)
{
    /* Disable TX and RX pin control functionality. */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIPIO0), CSL_LIN_SCIPIO0_RXFUNC_MASK, CSL_LIN_SCIPIO0_RXFUNC_SHIFT, FALSE);
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIPIO0), CSL_LIN_SCIPIO0_TXFUNC_MASK, CSL_LIN_SCIPIO0_TXFUNC_SHIFT, FALSE);

    /* Reset reset bit. */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR0), CSL_LIN_SCIGCR0_RESET_MASK, CSL_LIN_SCIGCR0_RESET_SHIFT, FALSE);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_EnableHWUnit(uint32 base)
{
    /* Set reset bit. */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR0), CSL_LIN_SCIGCR0_RESET_MASK, CSL_LIN_SCIGCR0_RESET_SHIFT, TRUE);

    /* Enable TX and RX pin control functionality. */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIPIO0), CSL_LIN_SCIPIO0_RXFUNC_MASK, CSL_LIN_SCIPIO0_RXFUNC_SHIFT, TRUE);
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIPIO0), CSL_LIN_SCIPIO0_TXFUNC_MASK, CSL_LIN_SCIPIO0_TXFUNC_SHIFT, TRUE);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_EnterSoftwareReset(uint32 base)
{
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_SWNRST_MASK, CSL_LIN_SCIGCR1_SWNRST_SHIFT, FALSE);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_ExitSoftwareReset(uint32 base)
{
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_SWNRST_MASK, CSL_LIN_SCIGCR1_SWNRST_SHIFT, TRUE);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetLinMode(uint32 base)
{
    /* Disable SCI communications mode */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_CLK_MASTER_MASK, CSL_LIN_SCIGCR1_CLK_MASTER_SHIFT,
                      FALSE);

    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_TIMINGMODE_MASK, CSL_LIN_SCIGCR1_TIMINGMODE_SHIFT,
                      FALSE);

    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_LINMODE_MASK, CSL_LIN_SCIGCR1_LINMODE_SHIFT, TRUE);

    /* Program LIN Mode to Master */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_CLK_MASTER_MASK, CSL_LIN_SCIGCR1_CLK_MASTER_SHIFT,
                      TRUE);

    /* Disable Automatic Baudrate Adjustment */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_ADAPT_MASK, CSL_LIN_SCIGCR1_ADAPT_SHIFT, FALSE);

    /* Write communication mode selection to the appropriate bit - will use the length set during
     * Lin_SendFrame */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_COMMMODE_MASK, CSL_LIN_SCIGCR1_COMMMODE_SHIFT, FALSE);

    /* Set Debug Suspend mode - Complete Tx/Rx before Freezing*/
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_CONT_MASK, CSL_LIN_SCIGCR1_CONT_SHIFT, TRUE);

    /* Sets the message filtering type - Filtering uses LIN message ID Byte */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_HGENCTRL_MASK, CSL_LIN_SCIGCR1_HGENCTRL_SHIFT, FALSE);

    /* Enable Multi-buffer Mode */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_MBUFMODE_MASK, CSL_LIN_SCIGCR1_MBUFMODE_SHIFT, TRUE);

    /* Enable the parity mode */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_PARITYENA_MASK, CSL_LIN_SCIGCR1_PARITYENA_SHIFT, TRUE);

    /* Comparing the Check Sum */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR2), CSL_LIN_SCIGCR2_CC_MASK, CSL_LIN_SCIGCR2_CC_SHIFT, TRUE);

    /* Set LIN interrupts to disabled */
    Lin_DisableInterrupt(base, LIN_INT_ALL);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetSyncFields(uint32 base, uint16 syncBreak, uint16 delimiter)
{
    /* Clear sync values and set new values */
    HW_WR_FIELD32_RAW((base + CSL_LIN_LINCOMP), (CSL_LIN_LINCOMP_SDEL_MASK | CSL_LIN_LINCOMP_SBREAK_MASK),
                      CSL_LIN_LINCOMP_SDEL_SHIFT, ((uint32)syncBreak | ((uint32)delimiter - 1U)));
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetTxMask(uint32 base, uint16 mask)
{
    /* Clear previous mask value and set new mask */
    HW_WR_FIELD32_RAW((base + CSL_LIN_LINMASK), CSL_LIN_LINMASK_TXIDMASK_MASK, CSL_LIN_LINMASK_TXIDMASK_SHIFT,
                      (uint32)mask);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetRxMask(uint32 base, uint16 mask)
{
    /* Clear previous mask value and set new mask */
    HW_WR_FIELD32_RAW((base + CSL_LIN_LINMASK), CSL_LIN_LINMASK_RXIDMASK_MASK, CSL_LIN_LINMASK_RXIDMASK_SHIFT,
                      (uint32)mask);
}

LOCAL_INLINE FUNC(void, LIN_CODE)
    Lin_SetBaudrateConfig(uint32 base, P2CONST(Lin_BaudRateConfigType, AUTOMATIC, LIN_APPL_CONST) baudrateConfig)
{
    /* Set baud rate prescaler and divider. */
    HW_WR_REG32_RAW((base + CSL_LIN_BRSR),
                    (baudrateConfig->Prescalar | (baudrateConfig->FractionalDivider << CSL_LIN_BRSR_M_SHIFT)));
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetFrameLength(uint32 base, uint16 length)
{
    /* Clear and set frame length value */
    HW_WR_FIELD32_RAW((base + CSL_LIN_SCIFORMAT), CSL_LIN_SCIFORMAT_LENGTH_MASK, CSL_LIN_SCIFORMAT_LENGTH_SHIFT,
                      ((uint32)length - (uint32)1U));
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetChecksumType(uint32 base, Lin_FrameCsModelType type)
{
    /* Set checksum type. */
    if (LIN_ENHANCED_CS == type)
    {
        HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_CTYPE_MASK, CSL_LIN_SCIGCR1_CTYPE_SHIFT, (uint32)1);
    }
    else
    {
        HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_CTYPE_MASK, CSL_LIN_SCIGCR1_CTYPE_SHIFT, (uint32)0);
    }
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetIDByte(uint32 base, Lin_FramePidType identifier)
{
    HW_WR_FIELD32_RAW((base + CSL_LIN_LINID), CSL_LIN_LINID_IDBYTE_MASK, CSL_LIN_LINID_IDBYTE_SHIFT,
                      (uint32)identifier);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_EnableInterrupt(uint32 base, Lin_InterruptLineNum intrLineNum, uint32 intFlags)
{
    /* Set Interrupt Flags */
    HW_WR_REG32((base + CSL_LIN_SCISETINT), HW_RD_REG32_RAW(base + CSL_LIN_SCISETINT) | intFlags);

    if (LIN_INTERRUPT_LINE_NUM_1 == intrLineNum)
    {
        /* Set interrupt levels to 1 */
        HW_WR_REG32((base + CSL_LIN_SCISETINTLVL), HW_RD_REG32_RAW(base + CSL_LIN_SCISETINTLVL) | intFlags);
        /* Enable global LIN interrupt for interrupt line number 1 */
        HW_WR_REG32((base + CSL_LIN_LIN_GLB_INT_EN),
                    HW_RD_REG32_RAW(base + CSL_LIN_LIN_GLB_INT_EN) |
                        (CSL_LIN_LIN_GLB_INT_FLG_INT0_FLG_MASK << (uint32)intrLineNum));
        /* Clear global LIN interrupt status for interrupt line number 1 */
        HW_WR_REG32((base + CSL_LIN_LIN_GLB_INT_CLR), (CSL_LIN_LIN_GLB_INT_FLG_INT0_FLG_MASK << (uint32)intrLineNum));
    }
    else
    {
        /* Set interrupt levels to 0 */
        HW_WR_REG32((base + CSL_LIN_SCICLEARINTLVL), intFlags);
        /* Enable global LIN interrupt for interrupt line number 0 */
        HW_WR_REG32((base + CSL_LIN_LIN_GLB_INT_EN),
                    HW_RD_REG32_RAW(base + CSL_LIN_LIN_GLB_INT_EN) |
                        (CSL_LIN_LIN_GLB_INT_FLG_INT0_FLG_MASK << (uint32)intrLineNum));
        /* Clear global LIN interrupt status for interrupt line number 0 */
        HW_WR_REG32((base + CSL_LIN_LIN_GLB_INT_CLR), (CSL_LIN_LIN_GLB_INT_FLG_INT0_FLG_MASK << (uint32)intrLineNum));
    }
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_DisableInterrupt(uint32 base, uint32 intFlags)
{
    /* Clear Interrupt Flags */
    HW_WR_REG32_RAW((base + CSL_LIN_SCICLEARINT), intFlags);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_SetTxRxEnable(uint32 base)
{
    uint32 regVal  = 0U;
    regVal         = (uint32)HW_RD_REG32(base + CSL_LIN_SCIGCR1);
    regVal        |= (uint32)CSL_LIN_SCIGCR1_TXENA_MASK | (uint32)CSL_LIN_SCIGCR1_RXENA_MASK;
    HW_WR_REG32((base + CSL_LIN_SCIGCR1), regVal);
}

LOCAL_INLINE FUNC(void, LIN_CODE) Lin_ServiceInterrupts(uint32 base, Lin_InterruptLineNum int_line)
{
    /* Read the interrupt vector priority */
    if (int_line == LIN_INTERRUPT_LINE_NUM_0)
    {
        /* Read Interrupt Status Flag */
        LIN_getInterruptLine0Offset(base);
    }
    else
    {
        /* Read Interrupt Status Flag */
        LIN_getInterruptLine1Offset(base);
    }

    /* Clear All the Interrupt Flags in SCIFLR */
    HW_WR_REG32((base + CSL_LIN_SCIFLR), LIN_INT_ALL);

    /* Clear Global Interrupt Flag Bit */
    HW_WR_REG32((base + CSL_LIN_LIN_GLB_INT_CLR),
                (uint32)CSL_LIN_LIN_GLB_INT_CLR_INT0_FLG_CLR_MASK << (uint8)(int_line));
}

LOCAL_INLINE FUNC(uint16, LIN_CODE) LIN_getInterruptLine0Offset(uint32 base)
{
    /* Read and return the flag register */
    return (HW_RD_REG32_RAW(base + CSL_LIN_SCIINTVECT0) & CSL_LIN_SCIINTVECT0_INTVECT0_MASK);
}

LOCAL_INLINE FUNC(uint16, LIN_CODE) LIN_getInterruptLine1Offset(uint32 base)
{
    /* Read and return the flag register */
    return (HW_RD_REG32_RAW(base + CSL_LIN_SCIINTVECT1) & CSL_LIN_SCIINTVECT1_INTVECT1_MASK);
}

STATIC FUNC(void, LIN_CODE) Lin_SetLoopbackMode(uint32 base, Lin_LoopbackModeType loopbackMode)
{
    switch (loopbackMode)
    {
        case LIN_LOOPBACK_DISABLED:

            /* Disable Internal Loopback */
            HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_LOOPBACK_MASK, CSL_LIN_SCIGCR1_LOOPBACK_SHIFT,
                              FALSE);

            /* Disable External Loopback */
            HW_WR_FIELD32_RAW((base + CSL_LIN_IODFTCTRL), CSL_LIN_IODFTCTRL_LPBENA_MASK, CSL_LIN_IODFTCTRL_LPBENA_SHIFT,
                              FALSE);

            /* Set Analog Loopback Path */
            HW_WR_FIELD32_RAW((base + CSL_LIN_IODFTCTRL), CSL_LIN_IODFTCTRL_RXPENA_MASK, CSL_LIN_IODFTCTRL_RXPENA_SHIFT,
                              FALSE);

            break;

        case LIN_LOOPBACK_INTERNAL:

            /* Enable Internal Loopback */
            HW_WR_FIELD32_RAW((base + CSL_LIN_SCIGCR1), CSL_LIN_SCIGCR1_LOOPBACK_MASK, CSL_LIN_SCIGCR1_LOOPBACK_SHIFT,
                              TRUE);

            break;

        case LIN_LOOPBACK_EXTERNAL:

            /* Clear the IO DFT Enable Key */
            HW_WR_FIELD32_RAW((base + CSL_LIN_IODFTCTRL), CSL_LIN_IODFTCTRL_IODFTENA_MASK,
                              CSL_LIN_IODFTCTRL_IODFTENA_SHIFT, LIN_IO_DFT_KEY);

            /* Enable Digital External Loopback */
            HW_WR_FIELD32_RAW((base + CSL_LIN_IODFTCTRL), CSL_LIN_IODFTCTRL_LPBENA_MASK, CSL_LIN_IODFTCTRL_LPBENA_SHIFT,
                              FALSE);

            /* Set Analog Loopback Path */
            HW_WR_FIELD32_RAW((base + CSL_LIN_IODFTCTRL), CSL_LIN_IODFTCTRL_RXPENA_MASK, CSL_LIN_IODFTCTRL_RXPENA_SHIFT,
                              FALSE);

            break;

        default:
            break;
    }
}

#if (STD_ON == LIN_REGISTER_READBACK_API)
/******************************************************************************
 *  Lin_HwRegisterReadback
 ******************************************************************************/
/*! \brief      This method is Lin_HwRegisterReadback Api.
 *  \param[inout]  RegRbPtr - Pointer to where to store the readback
 *                        values. If this pointer is NULL_PTR, then the API
 *                        will return E_NOT_OK.
 *  \return     void
 *  \context    Function could be called from from task level
 ******************************************************************************/
FUNC(void, LIN_CODE) Lin_HwRegisterReadback(uint8 Channel, Lin_RegisterReadbackType *RegRbPtr)
{
    uint32 lin_cnt_base_addr = Lin_Drv_Config_Ptr->linChannelCfg[Channel].linControllerConfig.CntrAddr;

    RegRbPtr->Scigcr0 = HW_RD_REG32(lin_cnt_base_addr + CSL_LIN_SCIGCR0);
    RegRbPtr->Scigcr1 = HW_RD_REG32(lin_cnt_base_addr + CSL_LIN_SCIGCR1);
    RegRbPtr->Scigcr2 = HW_RD_REG32(lin_cnt_base_addr + CSL_LIN_SCIGCR2);
}
#endif

FUNC(void, LIN_CODE) Lin_DeinitInternal(void)
{
    uint8 channel_idx = (uint8)0;

    for (channel_idx = 0; channel_idx < LIN_MAX_CHANNEL; channel_idx++)
    {
        uint32 lin_cnt_base_addr      = Lin_Drv_Config_Ptr->linChannelCfg[channel_idx].linControllerConfig.CntrAddr;
        Lin_InterruptLineNum int_line = Lin_Drv_Config_Ptr->linChannelCfg[channel_idx].linControllerConfig.IntrLineNum;
        /* ---------------------- */
        /* 1. Disable interrupts  */
        /* ---------------------- */
        /* Clear All the Interrupt Flags in SCIFLR */
        HW_WR_REG32((lin_cnt_base_addr + CSL_LIN_SCIFLR), LIN_INT_ALL);

        /* Clear Global Interrupt Flag Bit */
        HW_WR_REG32((lin_cnt_base_addr + CSL_LIN_LIN_GLB_INT_CLR),
                    (uint32)CSL_LIN_LIN_GLB_INT_CLR_INT0_FLG_CLR_MASK << (uint8)(int_line));

        /* ---------------------- */
        /* 2. Put module to reset */
        /* ---------------------- */
        HW_WR_REG32(lin_cnt_base_addr + CSL_LIN_SCIGCR0, CSL_LIN_SCIGCR0_RESET_MASK);

        /* ------------------------------ */
        /* 3. Restore registers to default */
        /* ------------------------------ */
        HW_WR_REG32(lin_cnt_base_addr + CSL_LIN_SCIGCR1, 0x00000000);
        HW_WR_REG32(lin_cnt_base_addr + CSL_LIN_SCIGCR2, 0x00000000);
        HW_WR_REG32(lin_cnt_base_addr + CSL_LIN_SCIPIO0, 0x00000000);
        HW_WR_REG32(lin_cnt_base_addr + CSL_LIN_SCIPIO1, 0x00000000);
        HW_WR_REG32(lin_cnt_base_addr + CSL_LIN_SCICLEARINT, 0xFFFFFFFF);
        HW_WR_REG32(lin_cnt_base_addr + CSL_LIN_LINCOMP, 0x00000000);
    }
}
#define LIN_STOP_SEC_CODE
#include "Lin_MemMap.h"
/*********************************************************************************************************************
 *  End of File: Lin_Priv.c
 *********************************************************************************************************************/
